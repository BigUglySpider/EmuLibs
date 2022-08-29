#ifndef EMU_MATH_FAST_MATRIX_OPERATORS_H_INC_
#define EMU_MATH_FAST_MATRIX_OPERATORS_H_INC_ 1

#include "_fast_matrix_t.h"

/// <summary>
/// <para> Standard MAT*MAT multiplication operator to multiply two EmuMath FastMatrix instances. </para>
/// <para> This is not available where `lhs * rhs` is an invalid matrix multiplication operation. </para>
/// </summary>
/// <param name="lhs_fast_matrix_">FastMatrix appearing on the left-hand side of Matrix multiplication.</param>
/// <param name="rhs_fast_matrix_">FastMatrix appearing on the right-hand side of Matrix multiplication.</param>
/// <returns>EmuMath FastMatrix containing resulting from multiply the two passed Matrices.</returns>
template<EmuConcepts::EmuFastMatrix LhsFastMatrix_, EmuConcepts::EmuFastMatrix RhsFastMatrix_>
requires EmuConcepts::EmuFastMatrixMultPair<LhsFastMatrix_, RhsFastMatrix_>
[[nodiscard]] constexpr inline auto operator*(LhsFastMatrix_&& lhs_fast_matrix_, RhsFastMatrix_&& rhs_fast_matrix_)
	-> typename EmuMath::TMP::fast_matrix_multiply_result<LhsFastMatrix_, RhsFastMatrix_>::type
{
	return EmuMath::Helpers::fast_matrix_multiply(std::forward<LhsFastMatrix_>(lhs_fast_matrix_), std::forward<RhsFastMatrix_>(rhs_fast_matrix_));
}

#endif
