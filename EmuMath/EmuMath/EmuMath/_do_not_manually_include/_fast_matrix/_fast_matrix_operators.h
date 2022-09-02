#ifndef EMU_MATH_FAST_MATRIX_OPERATORS_H_INC_
#define EMU_MATH_FAST_MATRIX_OPERATORS_H_INC_ 1

#include "_fast_matrix_t.h"

// Only includes `+` and `-` with all-Matrix inputs as these are the only operations that don't suggest another possible std operation
// --- Although `mat0 / mat1` is not defined for matrices, it can easily be inferred as `lhs * inv(rhs)`, so it is also omitted for `lhs / rhs` and `lhs % rhs`

#pragma region BASIC_ADD_OPERATORS
/// <summary>
/// <para> Performs a basic addition operation of the two passed FastMatrix instances, outputting the result as a FastMatrix of the left-hand type. </para>
/// <para> The right-hand Matrix may be any size, but must encapsulate the same type with the same register width, and share the same major order. </para>
/// <para> If the right-hand Vector does not contain respective registers to the left-hand Matrix, indices will be copied directly from `lhs_`. </para>
/// </summary>
/// <param name="lhs_">FastMatrix appearing on the left-hand side of addition. The output type will be the same as this FastMatrix type.</param>
/// <param name="rhs_">
///		FastMatrix appearing on the right-hand side of addition, 
///		which shares encapsulated type, register width, and major order with the left-hand operand.
/// </param>
/// <returns>FastMatrix resulting from adding respective indices in the passed two FastMatrix instances.</returns>
template<EmuConcepts::EmuFastMatrix LhsFastMatrix_, EmuConcepts::EmuFastMatrix RhsFastMatrix_>
requires EmuConcepts::EmuFastMatrixBasicOpCompatible<LhsFastMatrix_, RhsFastMatrix_>
[[nodiscard]] constexpr inline auto operator+(LhsFastMatrix_&& lhs_, RhsFastMatrix_&& rhs_)
	-> typename EmuCore::TMP::remove_ref_cv<LhsFastMatrix_>::type
{
	return EmuMath::Helpers::fast_matrix_add(std::forward<LhsFastMatrix_>(lhs_), std::forward<RhsFastMatrix_>(rhs_));
}

/// <summary>
/// <para> Performs a basic addition operation of the passed FastMatrix and FastVector, outputting the result as a FastMatrix of the left-hand type. </para>
/// <para> The right-hand Vector may be any size, but must encapsulate the same type with the same register width. </para>
/// <para> If the right-hand Matrix does not contain respective registers to the left-hand Matrix, indices will be copied directly from `lhs_`. </para>
/// </summary>
/// <param name="lhs_">FastMatrix appearing on the left-hand side of addition. The output type will be the same as this FastMatrix type.</param>
/// <param name="rhs_">
///		FastVector representing a major chunk, which will be added to all major chunks within the left-hand Matrix, 
///		which shares encapsulated type and register type with the left-hand operand.
/// </param>
/// <returns>FastMatrix resulting from adding respective indices in the passed FastMatrix's major chunks and the passed FastVector.</returns>
template<EmuConcepts::EmuFastMatrix LhsFastMatrix_, EmuConcepts::EmuFastVector RhsMajorFastVector_>
requires EmuConcepts::EmuFastMatrixBasicOpCompatible<LhsFastMatrix_, RhsMajorFastVector_>
[[nodiscard]] constexpr inline auto operator+(LhsFastMatrix_&& lhs_, RhsMajorFastVector_&& rhs_all_majors_)
	-> typename EmuCore::TMP::remove_ref_cv<LhsFastMatrix_>::type
{
	return EmuMath::Helpers::fast_matrix_add(std::forward<LhsFastMatrix_>(lhs_), std::forward<RhsMajorFastVector_>(rhs_all_majors_));
}

/// <summary>
/// <para> Performs a basic addition operation of the passed FastMatrix and SIMD register, outputting the result as a FastMatrix of the left-hand type. </para>
/// <para> The passed register must be the same as the passed Matrix's `register_type`. </para>
/// </summary>
/// <param name="lhs_">FastMatrix appearing on the left-hand side of addition. The output type will be the same as this FastMatrix type.</param>
/// <param name="rhs_">SIMD register of `lhs_`'s `register_type`, to add to all of the passed Matrix's registers.</param>
/// <returns>FastMatrix resulting from adding respective registers in the passed Matrix and the passed register.</returns>
template<EmuConcepts::EmuFastMatrix LhsFastMatrix_, EmuConcepts::KnownSIMD RhsRegisterForAll_>
requires EmuConcepts::EmuFastMatrixBasicOpCompatible<LhsFastMatrix_, RhsRegisterForAll_>
[[nodiscard]] constexpr inline auto operator+(LhsFastMatrix_&& lhs_, RhsRegisterForAll_&& rhs_all_registers_)
	-> typename EmuCore::TMP::remove_ref_cv<LhsFastMatrix_>::type
{
	return EmuMath::Helpers::fast_matrix_add(std::forward<LhsFastMatrix_>(lhs_), std::forward<RhsRegisterForAll_>(rhs_all_registers_));
}

/// <summary>
/// <para> Performs a basic addition operation of the passed FastMatrix and scalar, outputting the result as a FastMatrix of the left-hand type. </para>
/// </summary>
/// <param name="lhs_">FastMatrix appearing on the left-hand side of addition. The output type will be the same as this FastMatrix type.</param>
/// <param name="rhs_">Scalar to create a register of and add to all of the passed Matrix's indices.</param>
/// <returns>FastMatrix resulting from adding passed scalar value to all indices of the passed Matrix.</returns>
template<EmuConcepts::EmuFastMatrix LhsFastMatrix_, EmuConcepts::Arithmetic RhsScalarForAll_>
requires EmuConcepts::EmuFastMatrixBasicOpCompatible<LhsFastMatrix_, RhsScalarForAll_>
[[nodiscard]] constexpr inline auto operator+(LhsFastMatrix_&& lhs_, RhsScalarForAll_&& rhs_all_)
	-> typename EmuCore::TMP::remove_ref_cv<LhsFastMatrix_>::type
{
	return EmuMath::Helpers::fast_matrix_add(std::forward<LhsFastMatrix_>(lhs_), std::forward<RhsScalarForAll_>(rhs_all_));
}
#pragma endregion

#pragma region BASIC_SUBTRACT_OPERATORS
	/// <summary>
	/// <para> Performs a basic subtraction operation of the two passed FastMatrix instances, outputting the result as a FastMatrix of the left-hand type. </para>
	/// <para> The right-hand Matrix may be any size, but must encapsulate the same type with the same register width, and share the same major order. </para>
	/// <para> If the right-hand Matrix does not contain respective registers to the left-hand Matrix, indices will be copied directly from `lhs_`. </para>
	/// </summary>
	/// <param name="lhs_">FastMatrix appearing on the left-hand side of subtraction. The output type will be the same as this FastMatrix type.</param>
	/// <param name="rhs_">
	///		FastMatrix appearing on the right-hand side of subtraction, 
	///		which shares encapsulated type, register width, and major order with the left-hand operand.
	/// </param>
	/// <returns>FastMatrix resulting from subtracting respective indices in the passed two FastMatrix instances.</returns>
	template<EmuConcepts::EmuFastMatrix LhsFastMatrix_, EmuConcepts::EmuFastMatrix RhsFastMatrix_>
	requires EmuConcepts::EmuFastMatrixBasicOpCompatible<LhsFastMatrix_, RhsFastMatrix_>
	[[nodiscard]] constexpr inline auto operator-(LhsFastMatrix_&& lhs_, RhsFastMatrix_&& rhs_)
		-> typename EmuCore::TMP::remove_ref_cv<LhsFastMatrix_>::type
	{
		return EmuMath::Helpers::fast_matrix_subtract(std::forward<LhsFastMatrix_>(lhs_), std::forward<RhsFastMatrix_>(rhs_));
	}

	/// <summary>
	/// <para> Performs a basic subtraction operation of the passed FastMatrix and FastVector, outputting the result as a FastMatrix of the left-hand type. </para>
	/// <para> The right-hand Vector may be any size, but must encapsulate the same type with the same register width. </para>
	/// <para> If the right-hand Vector does not contain respective registers to the left-hand Matrix, indices will be copied directly from `lhs_`. </para>
	/// </summary>
	/// <param name="lhs_">FastMatrix appearing on the left-hand side of subtraction. The output type will be the same as this FastMatrix type.</param>
	/// <param name="rhs_">
	///		FastVector representing a major chunk, which will be subtracted from all major chunks within the left-hand Matrix, 
	///		which shares encapsulated type and register type with the left-hand operand.
	/// </param>
	/// <returns>FastMatrix resulting from subtracting respective indices in the passed FastMatrix's major chunks and the passed FastVector.</returns>
	template<EmuConcepts::EmuFastMatrix LhsFastMatrix_, EmuConcepts::EmuFastVector RhsMajorFastVector_>
	requires EmuConcepts::EmuFastMatrixBasicOpCompatible<LhsFastMatrix_, RhsMajorFastVector_>
	[[nodiscard]] constexpr inline auto operator-(LhsFastMatrix_&& lhs_, RhsMajorFastVector_&& rhs_all_majors_)
		-> typename EmuCore::TMP::remove_ref_cv<LhsFastMatrix_>::type
	{
		return EmuMath::Helpers::fast_matrix_subtract(std::forward<LhsFastMatrix_>(lhs_), std::forward<RhsMajorFastVector_>(rhs_all_majors_));
	}

	/// <summary>
	/// <para> Performs a basic subtraction operation of the passed FastMatrix and SIMD register, outputting the result as a FastMatrix of the left-hand type. </para>
	/// <para> The passed register must be the same as the passed Matrix's `register_type`. </para>
	/// </summary>
	/// <param name="lhs_">FastMatrix appearing on the left-hand side of subtraction. The output type will be the same as this FastMatrix type.</param>
	/// <param name="rhs_">SIMD register of `lhs_`'s `register_type`, to subtract from all of the passed Matrix's registers.</param>
	/// <returns>FastMatrix resulting from subtracting respective registers in the passed Matrix and the passed register.</returns>
	template<EmuConcepts::EmuFastMatrix LhsFastMatrix_, EmuConcepts::KnownSIMD RhsRegisterForAll_>
	requires EmuConcepts::EmuFastMatrixBasicOpCompatible<LhsFastMatrix_, RhsRegisterForAll_>
	[[nodiscard]] constexpr inline auto operator-(LhsFastMatrix_&& lhs_, RhsRegisterForAll_&& rhs_all_registers_)
		-> typename EmuCore::TMP::remove_ref_cv<LhsFastMatrix_>::type
	{
		return EmuMath::Helpers::fast_matrix_subtract(std::forward<LhsFastMatrix_>(lhs_), std::forward<RhsRegisterForAll_>(rhs_all_registers_));
	}

	/// <summary>
	/// <para> Performs a basic subtraction operation of the passed FastMatrix and scalar, outputting the result as a FastMatrix of the left-hand type. </para>
	/// </summary>
	/// <param name="lhs_">FastMatrix appearing on the left-hand side of subtraction. The output type will be the same as this FastMatrix type.</param>
	/// <param name="rhs_">Scalar to create a register of and subtract from all of the passed Matrix's indices.</param>
	/// <returns>FastMatrix resulting from subtracting the passed scalar value to all indices of the passed Matrix.</returns>
	template<EmuConcepts::EmuFastMatrix LhsFastMatrix_, EmuConcepts::Arithmetic RhsScalarForAll_>
	requires EmuConcepts::EmuFastMatrixBasicOpCompatible<LhsFastMatrix_, RhsScalarForAll_>
	[[nodiscard]] constexpr inline auto operator-(LhsFastMatrix_&& lhs_, RhsScalarForAll_&& rhs_all_)
		-> typename EmuCore::TMP::remove_ref_cv<LhsFastMatrix_>::type
	{
		return EmuMath::Helpers::fast_matrix_subtract(std::forward<LhsFastMatrix_>(lhs_), std::forward<RhsScalarForAll_>(rhs_all_));
	}
#pragma endregion

#pragma region BASIC_MULTIPLY_OPERATORS
	/// <summary>
	/// <para> Performs a basic multiplication operation of the passed FastMatrix and FastVector, outputting the result as a FastMatrix of the left-hand type. </para>
	/// <para> The right-hand Vector may be any size, but must encapsulate the same type with the same register width. </para>
	/// <para> If the right-hand Vector does not contain respective registers to the left-hand Matrix, indices will be zeroed as if multiplied by 0. </para>
	/// </summary>
	/// <param name="lhs_">FastMatrix appearing on the left-hand side of basic multiplication. The output type will be the same as this FastMatrix type.</param>
	/// <param name="rhs_">
	///		FastVector representing a major chunk to multiply all major chunks within the left-hand Matrix by, 
	///		which shares encapsulated type and register type with the left-hand operand.
	/// </param>
	/// <returns>FastMatrix resulting from multiplying respective indices in the passed FastMatrix's major chunks and the passed FastVector.</returns>
	template<EmuConcepts::EmuFastMatrix LhsFastMatrix_, EmuConcepts::EmuFastVector RhsMajorFastVector_>
	requires EmuConcepts::EmuFastMatrixBasicOpCompatible<LhsFastMatrix_, RhsMajorFastVector_>
	[[nodiscard]] constexpr inline auto operator*(LhsFastMatrix_&& lhs_, RhsMajorFastVector_&& rhs_all_majors_)
		-> typename EmuCore::TMP::remove_ref_cv<LhsFastMatrix_>::type
	{
		return EmuMath::Helpers::fast_matrix_basic_multiply(std::forward<LhsFastMatrix_>(lhs_), std::forward<RhsMajorFastVector_>(rhs_all_majors_));
	}

	/// <summary>
	/// <para> Performs a basic multiplication operation of the passed FastMatrix and SIMD register, outputting the result as a FastMatrix of the left-hand type. </para>
	/// <para> The passed register must be the same as the passed Matrix's `register_type`. </para>
	/// </summary>
	/// <param name="lhs_">FastMatrix appearing on the left-hand side of basic multiplication. The output type will be the same as this FastMatrix type.</param>
	/// <param name="rhs_">SIMD register of `lhs_`'s `register_type`, to multiply all of the passed Matrix's registers by.</param>
	/// <returns>FastMatrix resulting from multiplying respective registers in the passed Matrix and the passed register.</returns>
	template<EmuConcepts::EmuFastMatrix LhsFastMatrix_, EmuConcepts::KnownSIMD RhsRegisterForAll_>
	requires EmuConcepts::EmuFastMatrixBasicOpCompatible<LhsFastMatrix_, RhsRegisterForAll_>
	[[nodiscard]] constexpr inline auto operator*(LhsFastMatrix_&& lhs_, RhsRegisterForAll_&& rhs_all_registers_)
		-> typename EmuCore::TMP::remove_ref_cv<LhsFastMatrix_>::type
	{
		return EmuMath::Helpers::fast_matrix_basic_multiply(std::forward<LhsFastMatrix_>(lhs_), std::forward<RhsRegisterForAll_>(rhs_all_registers_));
	}

	/// <summary>
	/// <para> Performs a basic multiplication operation of the passed FastMatrix and scalar, outputting the result as a FastMatrix of the left-hand type. </para>
	/// </summary>
	/// <param name="lhs_">FastMatrix appearing on the left-hand side of multiplication. The output type will be the same as this FastMatrix type.</param>
	/// <param name="rhs_">Scalar to create a register of and multiply all of the passed Matrix's indices by.</param>
	/// <returns>FastMatrix resulting from multiplying all indices of the passed Matrix by the passed scalar value.</returns>
	template<EmuConcepts::EmuFastMatrix LhsFastMatrix_, EmuConcepts::Arithmetic RhsScalarForAll_>
	requires EmuConcepts::EmuFastMatrixBasicOpCompatible<LhsFastMatrix_, RhsScalarForAll_>
	[[nodiscard]] constexpr inline auto operator*(LhsFastMatrix_&& lhs_, RhsScalarForAll_&& rhs_all_)
		-> typename EmuCore::TMP::remove_ref_cv<LhsFastMatrix_>::type
	{
		return EmuMath::Helpers::fast_matrix_basic_multiply(std::forward<LhsFastMatrix_>(lhs_), std::forward<RhsScalarForAll_>(rhs_all_));
	}
#pragma endregion

#pragma region BASIC_DIVIDE_OPERATORS
	/// <summary>
	/// <para> Performs a basic division operation of the passed FastMatrix and FastVector, outputting the result as a FastMatrix of the left-hand type. </para>
	/// <para> The right-hand Vector may be any size, but must encapsulate the same type with the same register width. </para>
	/// <para>
	///		If the right-hand Vector does not contain respective registers to the left-hand Matrix, 
	///		indices will be copied directly from `lhs_`, as a divide by the implied 0 would result in likely unwanted NaNs. </para>
	/// </summary>
	/// <param name="lhs_">FastMatrix appearing on the left-hand side of basic division. The output type will be the same as this FastMatrix type.</param>
	/// <param name="rhs_">
	///		FastVector representing a major chunk to divide all major chunks within the left-hand Matrix by, 
	///		which shares encapsulated type and register type with the left-hand operand.
	/// </param>
	/// <returns>FastMatrix resulting from dividing respective indices in the passed FastMatrix's major chunks and the passed FastVector.</returns>
	template<EmuConcepts::EmuFastMatrix LhsFastMatrix_, EmuConcepts::EmuFastVector RhsMajorFastVector_>
	requires EmuConcepts::EmuFastMatrixBasicOpCompatible<LhsFastMatrix_, RhsMajorFastVector_>
	[[nodiscard]] constexpr inline auto operator/(LhsFastMatrix_&& lhs_, RhsMajorFastVector_&& rhs_all_majors_)
		-> typename EmuCore::TMP::remove_ref_cv<LhsFastMatrix_>::type
	{
		return EmuMath::Helpers::fast_matrix_basic_divide(std::forward<LhsFastMatrix_>(lhs_), std::forward<RhsMajorFastVector_>(rhs_all_majors_));
	}

	/// <summary>
	/// <para> Performs a basic division operation of the passed FastMatrix and SIMD register, outputting the result as a FastMatrix of the left-hand type. </para>
	/// <para> The passed register must be the same as the passed Matrix's `register_type`. </para>
	/// </summary>
	/// <param name="lhs_">FastMatrix appearing on the left-hand side of basic division. The output type will be the same as this FastMatrix type.</param>
	/// <param name="rhs_">SIMD register of `lhs_`'s `register_type`, to divide all of the passed Matrix's registers by.</param>
	/// <returns>FastMatrix resulting from dividing respective registers in the passed Matrix and the passed register.</returns>
	template<EmuConcepts::EmuFastMatrix LhsFastMatrix_, EmuConcepts::KnownSIMD RhsRegisterForAll_>
	requires EmuConcepts::EmuFastMatrixBasicOpCompatible<LhsFastMatrix_, RhsRegisterForAll_>
	[[nodiscard]] constexpr inline auto operator/(LhsFastMatrix_&& lhs_, RhsRegisterForAll_&& rhs_all_registers_)
		-> typename EmuCore::TMP::remove_ref_cv<LhsFastMatrix_>::type
	{
		return EmuMath::Helpers::fast_matrix_basic_divide(std::forward<LhsFastMatrix_>(lhs_), std::forward<RhsRegisterForAll_>(rhs_all_registers_));
	}

	/// <summary>
	/// <para> Performs a basic division operation of the passed FastMatrix and scalar, outputting the result as a FastMatrix of the left-hand type. </para>
	/// </summary>
	/// <param name="lhs_">FastMatrix appearing on the left-hand side of division. The output type will be the same as this FastMatrix type.</param>
	/// <param name="rhs_">Scalar to create a register of and divide all of the passed Matrix's indices by.</param>
	/// <returns>FastMatrix resulting from dividing all indices of the passed Matrix by the passed scalar value.</returns>
	template<EmuConcepts::EmuFastMatrix LhsFastMatrix_, EmuConcepts::Arithmetic RhsScalarForAll_>
	requires EmuConcepts::EmuFastMatrixBasicOpCompatible<LhsFastMatrix_, RhsScalarForAll_>
	[[nodiscard]] constexpr inline auto operator/(LhsFastMatrix_&& lhs_, RhsScalarForAll_&& rhs_all_)
		-> typename EmuCore::TMP::remove_ref_cv<LhsFastMatrix_>::type
	{
		return EmuMath::Helpers::fast_matrix_basic_divide(std::forward<LhsFastMatrix_>(lhs_), std::forward<RhsScalarForAll_>(rhs_all_));
	}
#pragma endregion

#pragma region BASIC_MOD_OPERATORS
	/// <summary>
	/// <para> Performs a basic modulo division operation of the passed FastMatrix and FastVector, outputting the result as a FastMatrix of the left-hand type. </para>
	/// <para> The right-hand Vector may be any size, but must encapsulate the same type with the same register width. </para>
	/// <para>
	///		If the right-hand Vector does not contain respective registers to the left-hand Matrix, 
	///		indices will be copied directly from `lhs_`, as a divide by the implied 0 would result in likely unwanted NaNs. </para>
	/// </summary>
	/// <param name="lhs_">FastMatrix appearing on the left-hand side of basic modulo division. The output type will be the same as this FastMatrix type.</param>
	/// <param name="rhs_">
	///		FastVector representing a major chunk to divide all major chunks within the left-hand Matrix by, 
	///		which shares encapsulated type and register type with the left-hand operand.
	/// </param>
	/// <returns>FastMatrix resulting from modulo division of respective indices in the passed FastMatrix's major chunks and the passed FastVector.</returns>
	template<EmuConcepts::EmuFastMatrix LhsFastMatrix_, EmuConcepts::EmuFastVector RhsMajorFastVector_>
	requires EmuConcepts::EmuFastMatrixBasicOpCompatible<LhsFastMatrix_, RhsMajorFastVector_>
	[[nodiscard]] constexpr inline auto operator%(LhsFastMatrix_&& lhs_, RhsMajorFastVector_&& rhs_all_majors_)
		-> typename EmuCore::TMP::remove_ref_cv<LhsFastMatrix_>::type
	{
		return EmuMath::Helpers::fast_matrix_basic_mod(std::forward<LhsFastMatrix_>(lhs_), std::forward<RhsMajorFastVector_>(rhs_all_majors_));
	}

	/// <summary>
	/// <para> Performs a basic modulo division operation of the passed FastMatrix and SIMD register, outputting the result as a FastMatrix of the left-hand type. </para>
	/// <para> The passed register must be the same as the passed Matrix's `register_type`. </para>
	/// </summary>
	/// <param name="lhs_">FastMatrix appearing on the left-hand side of basic modulo division. The output type will be the same as this FastMatrix type.</param>
	/// <param name="rhs_">SIMD register of `lhs_`'s `register_type`, to divide all of the passed Matrix's registers by.</param>
	/// <returns>FastMatrix resulting from modulo division of respective registers in the passed Matrix and the passed register.</returns>
	template<EmuConcepts::EmuFastMatrix LhsFastMatrix_, EmuConcepts::KnownSIMD RhsRegisterForAll_>
	requires EmuConcepts::EmuFastMatrixBasicOpCompatible<LhsFastMatrix_, RhsRegisterForAll_>
	[[nodiscard]] constexpr inline auto operator%(LhsFastMatrix_&& lhs_, RhsRegisterForAll_&& rhs_all_registers_)
		-> typename EmuCore::TMP::remove_ref_cv<LhsFastMatrix_>::type
	{
		return EmuMath::Helpers::fast_matrix_basic_mod(std::forward<LhsFastMatrix_>(lhs_), std::forward<RhsRegisterForAll_>(rhs_all_registers_));
	}

	/// <summary>
	/// <para> Performs a basic modulo division operation of the passed FastMatrix and scalar, outputting the result as a FastMatrix of the left-hand type. </para>
	/// </summary>
	/// <param name="lhs_">FastMatrix appearing on the left-hand side of modulo division. The output type will be the same as this FastMatrix type.</param>
	/// <param name="rhs_">Scalar to create a register of and modulo divide all of the passed Matrix's indices by.</param>
	/// <returns>FastMatrix resulting from modulo dividing all indices of the passed Matrix by the passed scalar value.</returns>
	template<EmuConcepts::EmuFastMatrix LhsFastMatrix_, EmuConcepts::Arithmetic RhsScalarForAll_>
	requires EmuConcepts::EmuFastMatrixBasicOpCompatible<LhsFastMatrix_, RhsScalarForAll_>
	[[nodiscard]] constexpr inline auto operator%(LhsFastMatrix_&& lhs_, RhsScalarForAll_&& rhs_all_)
		-> typename EmuCore::TMP::remove_ref_cv<LhsFastMatrix_>::type
	{
		return EmuMath::Helpers::fast_matrix_basic_mod(std::forward<LhsFastMatrix_>(lhs_), std::forward<RhsScalarForAll_>(rhs_all_));
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

#endif
