#ifndef EMU_MATH_FAST_MATRIX_UNDERLYING_MISC_ARITHMETIC_H_INC_
#define EMU_MATH_FAST_MATRIX_UNDERLYING_MISC_ARITHMETIC_H_INC_ 1

#include "_fast_matrix_tmp.h"
#include "_fast_matrix_underlying_mutation.h"
#include "_fast_matrix_underlying_set.h"

namespace EmuMath::Helpers::_fast_matrix_underlying
{
	template<bool Assigning_, EmuConcepts::EmuFastMatrix FastMatrix_>
	[[nodiscard]] constexpr inline decltype(auto) _fast_matrix_abs(FastMatrix_&& matrix_)
	{
		using _fast_mat_uq = typename std::remove_cvref<FastMatrix_>::type;
		constexpr std::size_t per_element_width = _fast_mat_uq::per_element_width;
		constexpr bool is_signed = _fast_mat_uq::is_signed;
		return _fast_matrix_mutate<Assigning_, false>
		(
			std::forward<FastMatrix_>(matrix_),
			[](auto&& register_) { return EmuSIMD::abs<per_element_width, is_signed>(register_); }
		);
	}

	// Logic is identical for Min/Max, just calling different functions, 
	// so to keep things consistent (especially with potential future optimisations) we do both here and just select functions based on template arg IsMax_
	template<bool IsMax_, bool Assigning_, EmuConcepts::EmuFastMatrix FastMatrix_>
	[[nodiscard]] constexpr inline decltype(auto) _fast_matrix_min_or_max(FastMatrix_&& matrix_)
	{
		using _fast_mat_uq = typename std::remove_cvref<FastMatrix_>::type;
		using _register_type = typename _fast_mat_uq::register_type;
		constexpr std::size_t per_element_width = _fast_mat_uq::per_element_width;
		constexpr bool is_signed = _fast_mat_uq::is_signed;

		// If assigning, we can use the 0th register of the output matrix directly (which may also help with cache locality)
		using _min_register_type = typename std::conditional<Assigning_, _register_type&, _register_type>::type;
		_min_register_type min_or_max = std::forward<FastMatrix_>(matrix_).template GetRegister<0, 0>();

		// Prepare index sequences; skip [0, 0] as we don't need to compare that register with itself
		using base_index_sequences = EmuMath::TMP::fast_matrix_full_register_sequences<_fast_mat_uq>;
		using trimmed_major_indices = typename EmuCore::TMP::slice_integer_sequence<1, typename base_index_sequences::major_index_sequence>::right;
		using trimmed_register_indices = typename EmuCore::TMP::slice_integer_sequence<1, typename base_index_sequences::register_index_sequence>::right;

		// Calculate vertical min
		if constexpr (_fast_mat_uq::majors_require_partial_register)
		{
			// Need to mask unused elements so that they aren't included for the min
			// --- NOTE: There are certainly ways that this can be optimised for specific layouts, but for now this approach is used
			constexpr std::size_t num_elements_in_partial_register = _fast_mat_uq::num_elements_in_partial_registers;
			_register_type used_mask = EmuSIMD::make_index_mask_for_first_x_elements<_register_type, num_elements_in_partial_register, per_element_width>();
			_register_type ignored_values_register;
			if constexpr (IsMax_)
			{
				ignored_values_register = EmuSIMD::set1<_register_type, per_element_width>(std::numeric_limits<_fast_mat_uq::value_type>::lowest());
			}
			else
			{
				ignored_values_register = EmuSIMD::set1<_register_type, per_element_width>(std::numeric_limits<_fast_mat_uq::value_type>::max());
			}
			ignored_values_register = EmuSIMD::bitwise_andnot(used_mask, ignored_values_register);
			_fast_matrix_mutate_mask_major_ends<false, false, true>
			(
				std::forward<FastMatrix_>(matrix_),
				[&min_or_max](auto&& rhs_register_)
				{
					if constexpr (IsMax_)
					{
						min_or_max = EmuSIMD::max<per_element_width, is_signed>(min_or_max, std::forward<decltype(rhs_register_)>(rhs_register_));
					}
					else
					{
						min_or_max = EmuSIMD::min<per_element_width, is_signed>(min_or_max, std::forward<decltype(rhs_register_)>(rhs_register_));
					}
				},
				used_mask,
				trimmed_major_indices(),
				trimmed_register_indices()
			);
		}
		else
		{
			_fast_matrix_mutate<false, true>
			(
				std::forward<FastMatrix_>(matrix_),
				[&min_or_max](auto&& rhs_register_)
				{
					if constexpr (IsMax_)
					{
						min_or_max = EmuSIMD::max<per_element_width, is_signed>(min_or_max, std::forward<decltype(rhs_register_)>(rhs_register_));
					}
					else
					{
						min_or_max = EmuSIMD::min<per_element_width, is_signed>(min_or_max, std::forward<decltype(rhs_register_)>(rhs_register_));
					}
				},
				trimmed_major_indices(),
				trimmed_register_indices()
			);
		}

		// Horizontal min/max will have a full register of the overall min/max value
		if constexpr (IsMax_)
		{
			min_or_max = EmuSIMD::horizontal_max<per_element_width, is_signed>(min_or_max);
		}
		else
		{
			min_or_max = EmuSIMD::horizontal_min<per_element_width, is_signed>(min_or_max);
		}

		// Populate either existing matrix via assignment or new matrix via set1 construction
		using full_major_index_sequence = typename base_index_sequences::major_index_sequence;
		using full_register_index_sequence = typename base_index_sequences::register_index_sequence;
		if constexpr (Assigning_)
		{
			_fast_matrix_mutate<true, true>
			(
				std::forward<FastMatrix_>(matrix_),
				[&min_or_max](auto&& rhs_register_) { return min_or_max; },
				full_major_index_sequence(),
				full_register_index_sequence()
			);
		}
		else
		{
			return _fast_matrix_set1_from_register<typename std::remove_cvref<FastMatrix_>::type>
			(
				min_or_max,
				full_major_index_sequence(),
				full_register_index_sequence()
			);
		}
	}
}

#endif
