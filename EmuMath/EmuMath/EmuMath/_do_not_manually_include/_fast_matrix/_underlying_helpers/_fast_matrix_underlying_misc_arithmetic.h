#ifndef EMU_MATH_FAST_MATRIX_UNDERLYING_MISC_ARITHMETIC_H_INC_
#define EMU_MATH_FAST_MATRIX_UNDERLYING_MISC_ARITHMETIC_H_INC_ 1

#include "_fast_matrix_tmp.h"
#include "_fast_matrix_underlying_mutation.h"

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

	template<bool Assigning_, EmuConcepts::EmuFastMatrix FastMatrix_>
	[[nodiscard]] constexpr inline decltype(auto) _fast_matrix_min(FastMatrix_&& matrix_)
	{
		using _fast_mat_uq = typename std::remove_cvref<FastMatrix_>::type;
		using _register_type = typename _fast_mat_uq::register_type;
		constexpr std::size_t per_element_width = _fast_mat_uq::per_element_width;
		constexpr bool is_signed = _fast_mat_uq::is_signed;

		// If assigning, we can use the 0th register of the output matrix directly (which may also help with cache locality)
		using _min_register_type = typename std::conditional<Assigning_, _register_type&, _register_type>::type;
		_min_register_type min = std::forward<FastMatrix_>(matrix_).template GetRegister<0, 0>();

		// Prepare index sequences; skip [0, 0] as we don't need to compare that register with itself
		using base_index_sequences = EmuMath::TMP::fast_matrix_full_register_sequences<_fast_mat_uq>;
		using major_indices = typename EmuCore::TMP::slice_integer_sequence<1, typename base_index_sequences::major_index_sequence>::right;
		using register_indices = typename EmuCore::TMP::slice_integer_sequence<1, typename base_index_sequences::register_index_sequence>::right;

		// Calculate vertical min
		_fast_matrix_mutate<false, true>
		(
			std::forward<FastMatrix_>(matrix_),
			[&](auto&& rhs_register_)
			{
				min = EmuSIMD::min<per_element_width, is_signed>(min, std::forward<decltype(rhs_register_)>(rhs_register_));
			}
		);

		// Calculate horizontal min from what's left
		// TODO
	}
}

#endif
