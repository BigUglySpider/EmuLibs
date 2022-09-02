#ifndef EMU_MATH_FAST_MATRIX_OPERATORS_H_INC_
#define EMU_MATH_FAST_MATRIX_OPERATORS_H_INC_ 1

#include "_fast_matrix_t.h"

// Only includes `+` and `-` with all-Matrix inputs as these are the only operations that don't suggest another possible std operation
// --- Although `mat0 / mat1` is not defined for matrices, it can easily be inferred as `lhs * inv(rhs)`, so it is also omitted for `lhs / rhs` and `lhs % rhs`

#pragma region BASIC_ADD_OPERATORS
/// <summary>
/// <para> Performs a basic addition operation on this Matrix using the passed right-hand operand. </para>
/// <para> `Rhs_` will be treated in one of the following ways: </para>
/// <para> --- 1: Where it is a FastMatrix of the same `register_type`, `value_type` and major-order, respective registers will be used. </para>
/// <para> 
///		--- 2: Where it is a FastVector of the same `register_type` and `value_type`, it will be treated as a major chunk, 
///		and registers in all major chunks will be used with the respective register of the FastVector.
/// </para>
/// <para> --- 3: Where it is a SIMD register recognised by EmuSIMD, all calculations will use that register. </para>
/// <para> --- 4: Where is is an arithmetic scalar, all indices will use that value. An intermediate register will be set to achieve this. </para>
/// </summary>
/// <param name="lhs_">FastMatrix appearing on the left-hand side of basic addition. The output type will be the same as this FastMatrix type.</param>
/// <param name="rhs_">One of the several described argument types, appearing on the right-hand side of basic addition.</param>
/// <returns>FastMatrix of the `lhs_` type containing the result of a basic addition operation with the passed operands.</returns>
template<EmuConcepts::EmuFastMatrix LhsFastMatrix_, class Rhs_>
requires (EmuConcepts::EmuFastMatrixBasicOpCompatible<LhsFastMatrix_, Rhs_>)
[[nodiscard]] constexpr inline auto operator+(LhsFastMatrix_&& lhs_, Rhs_&& rhs_)
	-> typename EmuCore::TMP::remove_ref_cv<LhsFastMatrix_>::type
{
	return EmuMath::Helpers::fast_matrix_add(std::forward<LhsFastMatrix_>(lhs_), std::forward<Rhs_>(rhs_));
}
#pragma endregion

#pragma region BASIC_SUBTRACT_OPERATORS
/// <summary>
/// <para> Performs a basic subtraction operation on this Matrix using the passed right-hand operand. </para>
/// <para> `Rhs_` will be treated in one of the following ways: </para>
/// <para> --- 1: Where it is a FastMatrix of the same `register_type`, `value_type` and major-order, respective registers will be used. </para>
/// <para> 
///		--- 2: Where it is a FastVector of the same `register_type` and `value_type`, it will be treated as a major chunk, 
///		and registers in all major chunks will be used with the respective register of the FastVector.
/// </para>
/// <para> --- 3: Where it is a SIMD register recognised by EmuSIMD, all calculations will use that register. </para>
/// <para> --- 4: Where is is an arithmetic scalar, all indices will use that value. An intermediate register will be set to achieve this. </para>
/// </summary>
/// <param name="lhs_">FastMatrix appearing on the left-hand side of basic subtraction. The output type will be the same as this FastMatrix type.</param>
/// <param name="rhs_">One of the several described argument types, appearing on the right-hand side of basic subtraction.</param>
/// <returns>FastMatrix of the `lhs_` type containing the result of a basic subtraction operation with the passed operands.</returns>
template<EmuConcepts::EmuFastMatrix LhsFastMatrix_, class Rhs_>
requires (EmuConcepts::EmuFastMatrixBasicOpCompatible<LhsFastMatrix_, Rhs_>)
[[nodiscard]] constexpr inline auto operator-(LhsFastMatrix_&& lhs_, Rhs_&& rhs_)
	-> typename EmuCore::TMP::remove_ref_cv<LhsFastMatrix_>::type
{
	return EmuMath::Helpers::fast_matrix_subtract(std::forward<LhsFastMatrix_>(lhs_), std::forward<Rhs_>(rhs_));
}
#pragma endregion

#pragma region BASIC_MULTIPLY_OPERATORS
/// <summary>
/// <para> Performs a basic multiplication operation on this Matrix using the passed right-hand operand. </para>
/// <para> This cannot be used to perform a basic, non-standard multiplication by a Matrix. </para>
/// <para> `Rhs_` will be treated in one of the following ways: </para>
/// <para> 
///		--- 1: Where it is a FastVector of the same `register_type` and `value_type`, it will be treated as a major chunk, 
///		and registers in all major chunks will be used with the respective register of the FastVector.
/// </para>
/// <para> --- 2: Where it is a SIMD register recognised by EmuSIMD, all calculations will use that register. </para>
/// <para> --- 3: Where is is an arithmetic scalar, all indices will use that value. An intermediate register will be set to achieve this. </para>
/// </summary>
/// <param name="lhs_">FastMatrix appearing on the left-hand side of basic multiplication. The output type will be the same as this FastMatrix type.</param>
/// <param name="rhs_">One of the several described argument types, appearing on the right-hand side of basic multiplication.</param>
/// <returns>FastMatrix of the `lhs_` type containing the result of a basic multiplication operation with the passed operands.</returns>
template<EmuConcepts::EmuFastMatrix LhsFastMatrix_, class Rhs_>
requires (!(EmuConcepts::EmuFastMatrix<Rhs_>) && (EmuConcepts::EmuFastMatrixBasicOpCompatible<LhsFastMatrix_, Rhs_>))
constexpr inline auto operator*(LhsFastMatrix_&& lhs_, Rhs_&& rhs_)
	-> typename EmuCore::TMP::remove_ref_cv<LhsFastMatrix_>::type
{
	return EmuMath::Helpers::fast_matrix_multiply(std::forward<LhsFastMatrix_>(lhs_), std::forward<Rhs_>(rhs_));
}
#pragma endregion

#pragma region BASIC_DIVIDE_OPERATORS
/// <summary>
/// <para> Performs a basic division operation on this Matrix using the passed right-hand operand. </para>
/// <para> `Rhs_` will be treated in one of the following ways: </para>
/// <para> --- 1: Where it is a FastMatrix of the same `register_type`, `value_type` and major-order, respective registers will be used. </para>
/// <para> 
///		--- 2: Where it is a FastVector of the same `register_type` and `value_type`, it will be treated as a major chunk, 
///		and registers in all major chunks will be used with the respective register of the FastVector.
/// </para>
/// <para> --- 3: Where it is a SIMD register recognised by EmuSIMD, all calculations will use that register. </para>
/// <para> --- 4: Where is is an arithmetic scalar, all indices will use that value. An intermediate register will be set to achieve this. </para>
/// </summary>
/// <param name="lhs_">FastMatrix appearing on the left-hand side of basic division. The output type will be the same as this FastMatrix type.</param>
/// <param name="rhs_">One of the several described argument types, appearing on the right-hand side of basic division.</param>
/// <returns>FastMatrix of the `lhs_` type containing the result of a basic division operation with the passed operands.</returns>
template<EmuConcepts::EmuFastMatrix LhsFastMatrix_, class Rhs_>
requires (!(EmuConcepts::EmuFastMatrix<Rhs_>) && EmuConcepts::EmuFastMatrixBasicOpCompatible<LhsFastMatrix_, Rhs_>)
[[nodiscard]] constexpr inline auto operator/(LhsFastMatrix_&& lhs_, Rhs_&& rhs_)
	-> typename EmuCore::TMP::remove_ref_cv<LhsFastMatrix_>::type
{
	return EmuMath::Helpers::fast_matrix_basic_divide(std::forward<LhsFastMatrix_>(lhs_), std::forward<Rhs_>(rhs_));
}
#pragma endregion

#pragma region BASIC_MOD_OPERATORS
/// <summary>
/// <para> Performs a basic modulo-division operation on this Matrix using the passed right-hand operand. </para>
/// <para> `Rhs_` will be treated in one of the following ways: </para>
/// <para> --- 1: Where it is a FastMatrix of the same `register_type`, `value_type` and major-order, respective registers will be used. </para>
/// <para> 
///		--- 2: Where it is a FastVector of the same `register_type` and `value_type`, it will be treated as a major chunk, 
///		and registers in all major chunks will be used with the respective register of the FastVector.
/// </para>
/// <para> --- 3: Where it is a SIMD register recognised by EmuSIMD, all calculations will use that register. </para>
/// <para> --- 4: Where is is an arithmetic scalar, all indices will use that value. An intermediate register will be set to achieve this. </para>
/// </summary>
/// <param name="lhs_">FastMatrix appearing on the left-hand side of basic modulo-division. The output type will be the same as this FastMatrix type.</param>
/// <param name="rhs_">One of the several described argument types, appearing on the right-hand side of basic modulo-division.</param>
/// <returns>FastMatrix of the `lhs_` type containing the result of a basic modulo-division operation with the passed operands.</returns>
template<EmuConcepts::EmuFastMatrix LhsFastMatrix_, class Rhs_>
requires (!(EmuConcepts::EmuFastMatrix<Rhs_>) && EmuConcepts::EmuFastMatrixBasicOpCompatible<LhsFastMatrix_, Rhs_>)
[[nodiscard]] constexpr inline auto operator%(LhsFastMatrix_&& lhs_, Rhs_&& rhs_)
	-> typename EmuCore::TMP::remove_ref_cv<LhsFastMatrix_>::type
{
	return EmuMath::Helpers::fast_matrix_basic_mod(std::forward<LhsFastMatrix_>(lhs_), std::forward<Rhs_>(rhs_));
}
#pragma endregion

#pragma region STD_ARTIHMETIC_OPERATORS
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
#pragma endregion

#pragma region BASIC_ADD_ASSIGN_OPERATORS
/// <summary>
/// <para> Performs a basic addition operation on this Matrix using the passed right-hand operand. </para>
/// <para> `Rhs_` will be treated in one of the following ways: </para>
/// <para> --- 1: Where it is a FastMatrix of the same `register_type`, `value_type` and major-order, respective registers will be used. </para>
/// <para> 
///		--- 2: Where it is a FastVector of the same `register_type` and `value_type`, it will be treated as a major chunk, 
///		and registers in all major chunks will be used with the respective register of the FastVector.
/// </para>
/// <para> --- 3: Where it is a SIMD register recognised by EmuSIMD, all calculations will use that register. </para>
/// <para> --- 4: Where is is an arithmetic scalar, all indices will use that value. An intermediate register will be set to achieve this. </para>
/// </summary>
/// <param name="lhs_">FastMatrix appearing on the left-hand side of basic addition. Results are assigned to this Matrix.</param>
/// <param name="rhs_">One of the several described argument types, appearing on the right-hand side of basic addition.</param>
template<EmuConcepts::EmuFastMatrix LhsFastMatrix_, class Rhs_>
requires ((EmuConcepts::EmuFastMatrixBasicOpCompatible<LhsFastMatrix_, Rhs_>) && !std::is_const_v<LhsFastMatrix_>)
[[nodiscard]] constexpr inline LhsFastMatrix_& operator+=(LhsFastMatrix_& lhs_, Rhs_&& rhs_)
{
	EmuMath::Helpers::fast_matrix_add_assign(lhs_, std::forward<Rhs_>(rhs_));
	return lhs_;
}
#pragma endregion

#pragma region BASIC_SUBTRACT_ASSIGN_OPERATORS
/// <summary>
/// <para> Performs a basic subtraction operation on this Matrix using the passed right-hand operand. </para>
/// <para> `Rhs_` will be treated in one of the following ways: </para>
/// <para> --- 1: Where it is a FastMatrix of the same `register_type`, `value_type` and major-order, respective registers will be used. </para>
/// <para> 
///		--- 2: Where it is a FastVector of the same `register_type` and `value_type`, it will be treated as a major chunk, 
///		and registers in all major chunks will be used with the respective register of the FastVector.
/// </para>
/// <para> --- 3: Where it is a SIMD register recognised by EmuSIMD, all calculations will use that register. </para>
/// <para> --- 4: Where is is an arithmetic scalar, all indices will use that value. An intermediate register will be set to achieve this. </para>
/// </summary>
/// <param name="lhs_">FastMatrix appearing on the left-hand side of basic subtraction. Results are assigned to this Matrix.</param>
/// <param name="rhs_">One of the several described argument types, appearing on the right-hand side of basic subtraction.</param>
template<EmuConcepts::EmuFastMatrix LhsFastMatrix_, class Rhs_>
requires ((EmuConcepts::EmuFastMatrixBasicOpCompatible<LhsFastMatrix_, Rhs_>) && !std::is_const_v<LhsFastMatrix_>)
[[nodiscard]] constexpr inline LhsFastMatrix_& operator-=(LhsFastMatrix_& lhs_, Rhs_&& rhs_)
{
	EmuMath::Helpers::fast_matrix_subtract_assign(lhs_, std::forward<Rhs_>(rhs_));
	return lhs_;
}
#pragma endregion

#pragma region BASIC_MULTIPLY_ASSIGN_OPERATORS
/// <summary>
/// <para> Performs a basic multiplication operation on this Matrix using the passed right-hand operand. </para>
/// <para> `Rhs_` will be treated in one of the following ways: </para>
/// <para> --- 1: Where it is a FastMatrix of the same `register_type`, `value_type` and major-order, respective registers will be used. </para>
/// <para> 
///		--- 2: Where it is a FastVector of the same `register_type` and `value_type`, it will be treated as a major chunk, 
///		and registers in all major chunks will be used with the respective register of the FastVector.
/// </para>
/// <para> --- 3: Where it is a SIMD register recognised by EmuSIMD, all calculations will use that register. </para>
/// <para> --- 4: Where is is an arithmetic scalar, all indices will use that value. An intermediate register will be set to achieve this. </para>
/// </summary>
/// <param name="lhs_">FastMatrix appearing on the left-hand side of basic multiplication. Results are assigned to this Matrix.</param>
/// <param name="rhs_">One of the several described argument types, appearing on the right-hand side of basic multiplication.</param>
template<EmuConcepts::EmuFastMatrix LhsFastMatrix_, class Rhs_>
requires ((EmuConcepts::EmuFastMatrixBasicOpCompatible<LhsFastMatrix_, Rhs_>) && !std::is_const_v<LhsFastMatrix_>)
[[nodiscard]] constexpr inline LhsFastMatrix_& operator*=(LhsFastMatrix_& lhs_, Rhs_&& rhs_)
{
	EmuMath::Helpers::fast_matrix_multiply_assign(lhs_, std::forward<Rhs_>(rhs_));
	return lhs_;
}
#pragma endregion

#pragma region BASIC_DIVIDE_ASSIGN_OPERATORS
/// <summary>
/// <para> Performs a basic division operation on this Matrix using the passed right-hand operand. </para>
/// <para> `Rhs_` will be treated in one of the following ways: </para>
/// <para> --- 1: Where it is a FastMatrix of the same `register_type`, `value_type` and major-order, respective registers will be used. </para>
/// <para> 
///		--- 2: Where it is a FastVector of the same `register_type` and `value_type`, it will be treated as a major chunk, 
///		and registers in all major chunks will be used with the respective register of the FastVector.
/// </para>
/// <para> --- 3: Where it is a SIMD register recognised by EmuSIMD, all calculations will use that register. </para>
/// <para> --- 4: Where is is an arithmetic scalar, all indices will use that value. An intermediate register will be set to achieve this. </para>
/// </summary>
/// <param name="lhs_">FastMatrix appearing on the left-hand side of basic division. Results are assigned to this Matrix.</param>
/// <param name="rhs_">One of the several described argument types, appearing on the right-hand side of basic division.</param>
template<EmuConcepts::EmuFastMatrix LhsFastMatrix_, class Rhs_>
requires ((EmuConcepts::EmuFastMatrixBasicOpCompatible<LhsFastMatrix_, Rhs_>) && !std::is_const_v<LhsFastMatrix_>)
[[nodiscard]] constexpr inline LhsFastMatrix_& operator/=(LhsFastMatrix_& lhs_, Rhs_&& rhs_)
{
	EmuMath::Helpers::fast_matrix_basic_divide_assign(lhs_, std::forward<Rhs_>(rhs_));
	return lhs_;
}
#pragma endregion

#pragma region BASIC_MOD_ASSIGN_OPERATORS
/// <summary>
/// <para> Performs a basic modulodivision operation on this Matrix using the passed right-hand operand. </para>
/// <para> `Rhs_` will be treated in one of the following ways: </para>
/// <para> --- 1: Where it is a FastMatrix of the same `register_type`, `value_type` and major-order, respective registers will be used. </para>
/// <para> 
///		--- 2: Where it is a FastVector of the same `register_type` and `value_type`, it will be treated as a major chunk, 
///		and registers in all major chunks will be used with the respective register of the FastVector.
/// </para>
/// <para> --- 3: Where it is a SIMD register recognised by EmuSIMD, all calculations will use that register. </para>
/// <para> --- 4: Where is is an arithmetic scalar, all indices will use that value. An intermediate register will be set to achieve this. </para>
/// </summary>
/// <param name="lhs_">FastMatrix appearing on the left-hand side of basic modulodivision. Results are assigned to this Matrix.</param>
/// <param name="rhs_">One of the several described argument types, appearing on the right-hand side of basic modulodivision.</param>
template<EmuConcepts::EmuFastMatrix LhsFastMatrix_, class Rhs_>
requires ((EmuConcepts::EmuFastMatrixBasicOpCompatible<LhsFastMatrix_, Rhs_>) && !std::is_const_v<LhsFastMatrix_>)
[[nodiscard]] constexpr inline LhsFastMatrix_& operator%=(LhsFastMatrix_& lhs_, Rhs_&& rhs_)
{
	EmuMath::Helpers::fast_matrix_basic_mod_assign(lhs_, std::forward<Rhs_>(rhs_));
	return lhs_;
}
#pragma endregion

#pragma region STD_MULTIPLY_ASSIGN_OPERATORS
/// <summary>
/// <para> Standard Matrix * Matrix multiplication function for use with instances of EmuMath::FastMatrix. </para>
/// <para> This is only available where the two passed Matrices encapsulate data that is exactly valid for a standard Matrix multiplication. </para>
/// <para> Furthermore, the resulting Matrix type of the given multiplication must be the same type as the `lhs_` Matrix. </para>
/// </summary>
/// <param name="lhs_fast_matrix_">FastMatrix appearing on the left-hand side of standard Matrix multiplication. Results will be assigned to this.</param>
/// <param name="rhs_fast_matrix_">FastMatrix appearing on the right-hand side of standard Matrix multiplication.</param>
template<EmuConcepts::EmuFastMatrix LhsFastMatrix_, EmuConcepts::EmuFastMatrix RhsFastMatrix_>
requires
(
	(EmuConcepts::EmuFastMatrixMultPair<LhsFastMatrix_, RhsFastMatrix_>) &&
	!std::is_const_v<LhsFastMatrix_> &&
	std::is_same_v
	<
		typename EmuCore::TMP::remove_ref_cv<LhsFastMatrix_>::type,
		typename EmuMath::TMP::fast_matrix_multiply_result<LhsFastMatrix_, RhsFastMatrix_>::type
	>
)
constexpr inline LhsFastMatrix_& operator*=(LhsFastMatrix_& lhs_fast_matrix_, RhsFastMatrix_&& rhs_fast_matrix_)
{
	EmuMath::Helpers::fast_matrix_multiply_assign(lhs_fast_matrix_, std::forward<RhsFastMatrix_>(rhs_fast_matrix_));
	return lhs_fast_matrix_;;
}
#pragma endregion

#endif
