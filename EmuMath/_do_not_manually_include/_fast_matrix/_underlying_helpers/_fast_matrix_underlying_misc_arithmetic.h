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
			[](auto&& register_) { return EmuSIMD::abs<per_element_width, is_signed>(std::forward<decltype(register_)>(register_)); }
		);
	}

	template<bool IsMax_, bool Assigning_, EmuConcepts::EmuFastMatrix FastMatrixA_, class B_>
	[[nodiscard]] constexpr inline decltype(auto) _fast_matrix_min_or_max(FastMatrixA_&& lhs_matrix_, B_&& rhs_)
	{
		using _fast_mat_uq = typename std::remove_cvref<FastMatrixA_>::type;
		constexpr std::size_t per_element_width = _fast_mat_uq::per_element_width;
		constexpr bool is_signed = _fast_mat_uq::is_signed;
		using index_sequences = EmuMath::TMP::fast_matrix_full_register_sequences<_fast_mat_uq>;
		using major_indices = typename index_sequences::major_index_sequence;
		using register_indices = typename index_sequences::register_index_sequence;
		return _fast_matrix_mutate_with_extra_args<Assigning_, false, false>
		(
			std::forward<FastMatrixA_>(lhs_matrix_),
			[](auto&& lhs_register_, auto&& rhs_register_)
			{
				if constexpr (IsMax_)
				{
					return EmuSIMD::max<per_element_width, is_signed>
					(
						std::forward<decltype(lhs_register_)>(lhs_register_),
						std::forward<decltype(rhs_register_)>(rhs_register_)
					);
				}
				else
				{
					return EmuSIMD::min<per_element_width, is_signed>
					(
						std::forward<decltype(lhs_register_)>(lhs_register_),
						std::forward<decltype(rhs_register_)>(rhs_register_)
					);
				}
			},
			major_indices(),
			register_indices(),
			std::forward<B_>(rhs_)
		);
	}

	template<bool Assigning_, bool Fused_, EmuConcepts::EmuFastMatrix FastMatrixA_, class B_, class Weighting_>
	[[nodiscard]] constexpr inline decltype(auto) _fast_matrix_lerp(FastMatrixA_&& lhs_matrix_, B_&& b_, Weighting_&& t_)
	{
		using _fast_mat_uq = typename std::remove_cvref<FastMatrixA_>::type;
		constexpr std::size_t per_element_width = _fast_mat_uq::per_element_width;
		using index_sequences = EmuMath::TMP::fast_matrix_full_register_sequences<_fast_mat_uq>;
		using major_indices = typename index_sequences::major_index_sequence;
		using register_indices = typename index_sequences::register_index_sequence;
		return _fast_matrix_mutate_with_extra_args<Assigning_, false, false>
		(
			std::forward<FastMatrixA_>(lhs_matrix_),
			[](auto&& lhs_register_, auto&& b_register_, auto&& c_register_)
			{
				if constexpr (Fused_)
				{
					return EmuSIMD::fused_lerp<per_element_width>
					(
						std::forward<decltype(lhs_register_)>(lhs_register_),
						std::forward<decltype(b_register_)>(b_register_),
						std::forward<decltype(c_register_)>(c_register_)
					);
				}
				else
				{
					return EmuSIMD::lerp<per_element_width>
					(
						std::forward<decltype(lhs_register_)>(lhs_register_),
						std::forward<decltype(b_register_)>(b_register_),
						std::forward<decltype(c_register_)>(c_register_)
					);
				}
			},
			major_indices(),
			register_indices(),
			std::forward<B_>(b_),
			std::forward<Weighting_>(t_)
		);
	}

	template<bool IsMax_, bool Assigning_, EmuConcepts::EmuFastMatrix FastMatrixA_, class MinOrMax_>
	[[nodiscard]] constexpr inline decltype(auto) _fast_matrix_clamp_min_or_max(FastMatrixA_&& in_matrix_, MinOrMax_&& min_or_max_)
	{
		using _fast_mat_uq = typename std::remove_cvref<FastMatrixA_>::type;
		constexpr std::size_t per_element_width = _fast_mat_uq::per_element_width;
		constexpr bool is_signed = _fast_mat_uq::is_signed;
		using index_sequences = EmuMath::TMP::fast_matrix_full_register_sequences<_fast_mat_uq>;
		using major_indices = typename index_sequences::major_index_sequence;
		using register_indices = typename index_sequences::register_index_sequence;
		return _fast_matrix_mutate_with_extra_args<Assigning_, false, false>
		(
			std::forward<FastMatrixA_>(in_matrix_),
			[](auto&& in_register_, auto&& min_or_max_register_)
			{
				if constexpr (IsMax_)
				{
					return EmuSIMD::clamp_max<per_element_width, is_signed>
					(
						std::forward<decltype(in_register_)>(in_register_),
						std::forward<decltype(min_or_max_register_)>(min_or_max_register_)
					);
				}
				else
				{
					return EmuSIMD::clamp_min<per_element_width, is_signed>
					(
						std::forward<decltype(in_register_)>(in_register_),
						std::forward<decltype(min_or_max_register_)>(min_or_max_register_)
					);
				}
			},
			major_indices(),
			register_indices(),
			std::forward<MinOrMax_>(min_or_max_)
		);
	}

	template<bool Assigning_, EmuConcepts::EmuFastMatrix FastMatrixA_, class Min_, class Max_>
	[[nodiscard]] constexpr inline decltype(auto) _fast_matrix_clamp(FastMatrixA_&& in_matrix_, Min_&& min_, Max_&& max_)
	{
		using _fast_mat_uq = typename std::remove_cvref<FastMatrixA_>::type;
		constexpr std::size_t per_element_width = _fast_mat_uq::per_element_width;
		constexpr bool is_signed = _fast_mat_uq::is_signed;
		using index_sequences = EmuMath::TMP::fast_matrix_full_register_sequences<_fast_mat_uq>;
		using major_indices = typename index_sequences::major_index_sequence;
		using register_indices = typename index_sequences::register_index_sequence;
		return _fast_matrix_mutate_with_extra_args<Assigning_, false, false>
		(
			std::forward<FastMatrixA_>(in_matrix_),
			[](auto&& in_register_, auto&& min_register_, auto&& max_register_)
			{
				return EmuSIMD::clamp<per_element_width, is_signed>
				(
					std::forward<decltype(in_register_)>(in_register_),
					std::forward<decltype(min_register_)>(min_register_),
					std::forward<decltype(max_register_)>(max_register_)
				);
			},
			major_indices(),
			register_indices(),
			std::forward<Min_>(min_),
			std::forward<Max_>(max_)
		);
	}

	// Logic is identical for Min/Max, just calling different functions, 
	// so to keep things consistent (especially with potential future optimisations) we do both here and just select functions based on template arg IsMax_
	// --- AltOutputType is used to select a scalar output type instead of the input Matrix
	template<bool IsMax_, bool Assigning_, typename ScalarOutputType = void, EmuConcepts::EmuFastMatrix FastMatrix_>
	[[nodiscard]] constexpr inline decltype(auto) _fast_matrix_min_or_max(FastMatrix_&& matrix_)
	{
		using _fast_mat_uq = typename std::remove_cvref<FastMatrix_>::type;
		using _register_type = typename _fast_mat_uq::register_type;
		constexpr std::size_t per_element_width = _fast_mat_uq::per_element_width;
		constexpr bool is_signed = _fast_mat_uq::is_signed;
		constexpr bool output_scalar = !std::is_void_v<ScalarOutputType>;

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
				ignored_values_register = EmuSIMD::set1<_register_type, per_element_width>(std::numeric_limits<typename _fast_mat_uq::value_type>::lowest());
			}
			else
			{
				ignored_values_register = EmuSIMD::set1<_register_type, per_element_width>(std::numeric_limits<typename _fast_mat_uq::value_type>::max());
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
				ignored_values_register,
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
		// --- This is the exit point when returning a scalar as `EmuSIMD` provides specialised algorithms for horizontal max with scalar output
		if constexpr (IsMax_)
		{
			if constexpr (output_scalar)
			{
				return EmuSIMD::horizontal_max_scalar<ScalarOutputType>(min_or_max);
			}
			else
			{
				min_or_max = EmuSIMD::horizontal_max_fill<per_element_width, is_signed>(min_or_max);
			}
		}
		else
		{
			if constexpr (output_scalar)
			{
				return EmuSIMD::horizontal_min_scalar<ScalarOutputType>(min_or_max);
			}
			else
			{
				min_or_max = EmuSIMD::horizontal_min_fill<per_element_width, is_signed>(min_or_max);
			}
		}

		// Populate either existing matrix via assignment or new matrix via set1 construction
		if constexpr(!output_scalar)
		{
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
}

#endif
