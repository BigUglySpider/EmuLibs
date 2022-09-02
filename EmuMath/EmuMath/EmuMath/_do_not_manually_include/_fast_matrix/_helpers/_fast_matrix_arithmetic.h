#ifndef EMU_MATH_FAST_MATRIX_ARITHMETIC_H_INC_
#define EMU_MATH_FAST_MATRIX_ARITHMETIC_H_INC_ 1

#include "_common_fast_matrix_helper_includes.h"

namespace EmuMath::Helpers
{
#pragma region BASIC_ADD
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
	[[nodiscard]] constexpr inline auto fast_matrix_add(LhsFastMatrix_&& lhs_, RhsFastMatrix_&& rhs_)
		-> typename EmuCore::TMP::remove_ref_cv<LhsFastMatrix_>::type
	{
		using _lhs_fast_mat_uq = typename EmuCore::TMP::remove_ref_cv<LhsFastMatrix_>::type;
		using _major_indices = std::make_index_sequence<_lhs_fast_mat_uq::num_major_elements>;
		using _register_indices = std::make_index_sequence<_lhs_fast_mat_uq::num_registers_per_major>;
		using _func = _fast_matrix_underlying::_basic_add_func<_lhs_fast_mat_uq>;
		return _fast_matrix_underlying::_basic_func_for_matrix<true, _func, _lhs_fast_mat_uq>
		(
			_major_indices(),
			_register_indices(),
			std::forward<LhsFastMatrix_>(lhs_),
			std::forward<RhsFastMatrix_>(rhs_)
		);
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
	[[nodiscard]] constexpr inline auto fast_matrix_add(LhsFastMatrix_&& lhs_, RhsMajorFastVector_&& rhs_all_majors_)
		-> typename EmuCore::TMP::remove_ref_cv<LhsFastMatrix_>::type
	{
		using _lhs_fast_mat_uq = typename EmuCore::TMP::remove_ref_cv<LhsFastMatrix_>::type;
		using _major_indices = std::make_index_sequence<_lhs_fast_mat_uq::num_major_elements>;
		using _register_indices = std::make_index_sequence<_lhs_fast_mat_uq::num_registers_per_major>;
		using _func = _fast_matrix_underlying::_basic_add_func<_lhs_fast_mat_uq>;
		return _fast_matrix_underlying::_basic_func_for_matrix<true, _func, _lhs_fast_mat_uq>
		(
			_major_indices(),
			_register_indices(),
			std::forward<LhsFastMatrix_>(lhs_),
			std::forward<RhsMajorFastVector_>(rhs_all_majors_)
		);
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
	[[nodiscard]] constexpr inline auto fast_matrix_add(LhsFastMatrix_&& lhs_, RhsRegisterForAll_&& rhs_all_registers_)
		-> typename EmuCore::TMP::remove_ref_cv<LhsFastMatrix_>::type
	{
		using _lhs_fast_mat_uq = typename EmuCore::TMP::remove_ref_cv<LhsFastMatrix_>::type;
		using _major_indices = std::make_index_sequence<_lhs_fast_mat_uq::num_major_elements>;
		using _register_indices = std::make_index_sequence<_lhs_fast_mat_uq::num_registers_per_major>;
		using _func = _fast_matrix_underlying::_basic_add_func<_lhs_fast_mat_uq>;
		return _fast_matrix_underlying::_basic_func_for_matrix<true, _func, _lhs_fast_mat_uq>
		(
			_major_indices(),
			_register_indices(),
			std::forward<LhsFastMatrix_>(lhs_),
			std::forward<RhsRegisterForAll_>(rhs_all_registers_)
		);
	}

	/// <summary>
	/// <para> Performs a basic addition operation of the passed FastMatrix and scalar, outputting the result as a FastMatrix of the left-hand type. </para>
	/// </summary>
	/// <param name="lhs_">FastMatrix appearing on the left-hand side of addition. The output type will be the same as this FastMatrix type.</param>
	/// <param name="rhs_">Scalar to create a register of and add to all of the passed Matrix's indices.</param>
	/// <returns>FastMatrix resulting from adding the passed scalar value to all indices of the passed Matrix.</returns>
	template<EmuConcepts::EmuFastMatrix LhsFastMatrix_, EmuConcepts::Arithmetic RhsScalarForAll_>
	requires EmuConcepts::EmuFastMatrixBasicOpCompatible<LhsFastMatrix_, RhsScalarForAll_>
	[[nodiscard]] constexpr inline auto fast_matrix_add(LhsFastMatrix_&& lhs_, RhsScalarForAll_&& rhs_all_)
		-> typename EmuCore::TMP::remove_ref_cv<LhsFastMatrix_>::type
	{
		using _lhs_fast_mat_uq = typename EmuCore::TMP::remove_ref_cv<LhsFastMatrix_>::type;
		using _major_indices = std::make_index_sequence<_lhs_fast_mat_uq::num_major_elements>;
		using _register_indices = std::make_index_sequence<_lhs_fast_mat_uq::num_registers_per_major>;
		using _func = _fast_matrix_underlying::_basic_add_func<_lhs_fast_mat_uq>;
		return _fast_matrix_underlying::_basic_func_for_matrix<true, _func, _lhs_fast_mat_uq>
		(
			_major_indices(),
			_register_indices(),
			std::forward<LhsFastMatrix_>(lhs_),
			std::forward<RhsScalarForAll_>(rhs_all_)
		);
	}
#pragma endregion

#pragma region BASIC_SUBTRACT
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
	[[nodiscard]] constexpr inline auto fast_matrix_subtract(LhsFastMatrix_&& lhs_, RhsFastMatrix_&& rhs_)
		-> typename EmuCore::TMP::remove_ref_cv<LhsFastMatrix_>::type
	{
		using _lhs_fast_mat_uq = typename EmuCore::TMP::remove_ref_cv<LhsFastMatrix_>::type;
		using _major_indices = std::make_index_sequence<_lhs_fast_mat_uq::num_major_elements>;
		using _register_indices = std::make_index_sequence<_lhs_fast_mat_uq::num_registers_per_major>;
		using _func = _fast_matrix_underlying::_basic_sub_func<_lhs_fast_mat_uq>;
		return _fast_matrix_underlying::_basic_func_for_matrix<true, _func, _lhs_fast_mat_uq>
		(
			_major_indices(),
			_register_indices(),
			std::forward<LhsFastMatrix_>(lhs_),
			std::forward<RhsFastMatrix_>(rhs_)
		);
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
	[[nodiscard]] constexpr inline auto fast_matrix_subtract(LhsFastMatrix_&& lhs_, RhsMajorFastVector_&& rhs_all_majors_)
		-> typename EmuCore::TMP::remove_ref_cv<LhsFastMatrix_>::type
	{
		using _lhs_fast_mat_uq = typename EmuCore::TMP::remove_ref_cv<LhsFastMatrix_>::type;
		using _major_indices = std::make_index_sequence<_lhs_fast_mat_uq::num_major_elements>;
		using _register_indices = std::make_index_sequence<_lhs_fast_mat_uq::num_registers_per_major>;
		using _func = _fast_matrix_underlying::_basic_sub_func<_lhs_fast_mat_uq>;
		return _fast_matrix_underlying::_basic_func_for_matrix<true, _func, _lhs_fast_mat_uq>
		(
			_major_indices(),
			_register_indices(),
			std::forward<LhsFastMatrix_>(lhs_),
			std::forward<RhsMajorFastVector_>(rhs_all_majors_)
		);
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
	[[nodiscard]] constexpr inline auto fast_matrix_subtract(LhsFastMatrix_&& lhs_, RhsRegisterForAll_&& rhs_all_registers_)
		-> typename EmuCore::TMP::remove_ref_cv<LhsFastMatrix_>::type
	{
		using _lhs_fast_mat_uq = typename EmuCore::TMP::remove_ref_cv<LhsFastMatrix_>::type;
		using _major_indices = std::make_index_sequence<_lhs_fast_mat_uq::num_major_elements>;
		using _register_indices = std::make_index_sequence<_lhs_fast_mat_uq::num_registers_per_major>;
		using _func = _fast_matrix_underlying::_basic_sub_func<_lhs_fast_mat_uq>;
		return _fast_matrix_underlying::_basic_func_for_matrix<true, _func, _lhs_fast_mat_uq>
		(
			_major_indices(),
			_register_indices(),
			std::forward<LhsFastMatrix_>(lhs_),
			std::forward<RhsRegisterForAll_>(rhs_all_registers_)
		);
	}

	/// <summary>
	/// <para> Performs a basic subtraction operation of the passed FastMatrix and scalar, outputting the result as a FastMatrix of the left-hand type. </para>
	/// </summary>
	/// <param name="lhs_">FastMatrix appearing on the left-hand side of subtraction. The output type will be the same as this FastMatrix type.</param>
	/// <param name="rhs_">Scalar to create a register of and subtract from all of the passed Matrix's indices.</param>
	/// <returns>FastMatrix resulting from subtracting the passed scalar value to all indices of the passed Matrix.</returns>
	template<EmuConcepts::EmuFastMatrix LhsFastMatrix_, EmuConcepts::Arithmetic RhsScalarForAll_>
	requires EmuConcepts::EmuFastMatrixBasicOpCompatible<LhsFastMatrix_, RhsScalarForAll_>
	[[nodiscard]] constexpr inline auto fast_matrix_subtract(LhsFastMatrix_&& lhs_, RhsScalarForAll_&& rhs_all_)
		-> typename EmuCore::TMP::remove_ref_cv<LhsFastMatrix_>::type
	{
		using _lhs_fast_mat_uq = typename EmuCore::TMP::remove_ref_cv<LhsFastMatrix_>::type;
		using _major_indices = std::make_index_sequence<_lhs_fast_mat_uq::num_major_elements>;
		using _register_indices = std::make_index_sequence<_lhs_fast_mat_uq::num_registers_per_major>;
		using _func = _fast_matrix_underlying::_basic_sub_func<_lhs_fast_mat_uq>;
		return _fast_matrix_underlying::_basic_func_for_matrix<true, _func, _lhs_fast_mat_uq>
		(
			_major_indices(),
			_register_indices(),
			std::forward<LhsFastMatrix_>(lhs_),
			std::forward<RhsScalarForAll_>(rhs_all_)
		);
	}
#pragma endregion

#pragma region BASIC_MULTIPLY
	/// <summary>
	/// <para> Performs a basic multiplication operation of the two passed FastMatrix instances, outputting the result as a FastMatrix of the left-hand type. </para>
	/// <para> The right-hand Matrix may be any size, but must encapsulate the same type with the same register width, and share the same major order. </para>
	/// <para> If the right-hand Matrix does not contain respective registers to the left-hand Matrix, indices will be zeroed as if multiplied by 0. </para>
	/// </summary>
	/// <param name="lhs_">FastMatrix appearing on the left-hand side of basic multiplication. The output type will be the same as this FastMatrix type.</param>
	/// <param name="rhs_">
	///		FastMatrix appearing on the right-hand side of basic multiplication, 
	///		which shares encapsulated type, register width, and major order with the left-hand operand.
	/// </param>
	/// <returns>FastMatrix resulting from multiplying respective indices in the passed two FastMatrix instances.</returns>
	template<EmuConcepts::EmuFastMatrix LhsFastMatrix_, EmuConcepts::EmuFastMatrix RhsFastMatrix_>
	requires EmuConcepts::EmuFastMatrixBasicOpCompatible<LhsFastMatrix_, RhsFastMatrix_>
	[[nodiscard]] constexpr inline auto fast_matrix_basic_multiply(LhsFastMatrix_&& lhs_, RhsFastMatrix_&& rhs_)
		-> typename EmuCore::TMP::remove_ref_cv<LhsFastMatrix_>::type
	{
		using _lhs_fast_mat_uq = typename EmuCore::TMP::remove_ref_cv<LhsFastMatrix_>::type;
		using _major_indices = std::make_index_sequence<_lhs_fast_mat_uq::num_major_elements>;
		using _register_indices = std::make_index_sequence<_lhs_fast_mat_uq::num_registers_per_major>;
		using _func = _fast_matrix_underlying::_basic_mul_func<_lhs_fast_mat_uq>;
		return _fast_matrix_underlying::_basic_func_for_matrix<true, _func, _lhs_fast_mat_uq>
		(
			_major_indices(),
			_register_indices(),
			std::forward<LhsFastMatrix_>(lhs_),
			std::forward<RhsFastMatrix_>(rhs_)
		);
	}

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
	[[nodiscard]] constexpr inline auto fast_matrix_basic_multiply(LhsFastMatrix_&& lhs_, RhsMajorFastVector_&& rhs_all_majors_)
		-> typename EmuCore::TMP::remove_ref_cv<LhsFastMatrix_>::type
	{
		using _lhs_fast_mat_uq = typename EmuCore::TMP::remove_ref_cv<LhsFastMatrix_>::type;
		using _major_indices = std::make_index_sequence<_lhs_fast_mat_uq::num_major_elements>;
		using _register_indices = std::make_index_sequence<_lhs_fast_mat_uq::num_registers_per_major>;
		using _func = _fast_matrix_underlying::_basic_mul_func<_lhs_fast_mat_uq>;
		return _fast_matrix_underlying::_basic_func_for_matrix<true, _func, _lhs_fast_mat_uq>
		(
			_major_indices(),
			_register_indices(),
			std::forward<LhsFastMatrix_>(lhs_),
			std::forward<RhsMajorFastVector_>(rhs_all_majors_)
		);
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
	[[nodiscard]] constexpr inline auto fast_matrix_basic_multiply(LhsFastMatrix_&& lhs_, RhsRegisterForAll_&& rhs_all_registers_)
		-> typename EmuCore::TMP::remove_ref_cv<LhsFastMatrix_>::type
	{
		using _lhs_fast_mat_uq = typename EmuCore::TMP::remove_ref_cv<LhsFastMatrix_>::type;
		using _major_indices = std::make_index_sequence<_lhs_fast_mat_uq::num_major_elements>;
		using _register_indices = std::make_index_sequence<_lhs_fast_mat_uq::num_registers_per_major>;
		using _func = _fast_matrix_underlying::_basic_mul_func<_lhs_fast_mat_uq>;
		return _fast_matrix_underlying::_basic_func_for_matrix<true, _func, _lhs_fast_mat_uq>
		(
			_major_indices(),
			_register_indices(),
			std::forward<LhsFastMatrix_>(lhs_),
			std::forward<RhsRegisterForAll_>(rhs_all_registers_)
		);
	}

	/// <summary>
	/// <para> Performs a basic multiplication operation of the passed FastMatrix and scalar, outputting the result as a FastMatrix of the left-hand type. </para>
	/// </summary>
	/// <param name="lhs_">FastMatrix appearing on the left-hand side of multiplication. The output type will be the same as this FastMatrix type.</param>
	/// <param name="rhs_">Scalar to create a register of and multiply all of the passed Matrix's indices by.</param>
	/// <returns>FastMatrix resulting from multiplying all indices of the passed Matrix by the passed scalar value.</returns>
	template<EmuConcepts::EmuFastMatrix LhsFastMatrix_, EmuConcepts::Arithmetic RhsScalarForAll_>
	requires EmuConcepts::EmuFastMatrixBasicOpCompatible<LhsFastMatrix_, RhsScalarForAll_>
	[[nodiscard]] constexpr inline auto fast_matrix_basic_multiply(LhsFastMatrix_&& lhs_, RhsScalarForAll_&& rhs_all_)
		-> typename EmuCore::TMP::remove_ref_cv<LhsFastMatrix_>::type
	{
		using _lhs_fast_mat_uq = typename EmuCore::TMP::remove_ref_cv<LhsFastMatrix_>::type;
		using _major_indices = std::make_index_sequence<_lhs_fast_mat_uq::num_major_elements>;
		using _register_indices = std::make_index_sequence<_lhs_fast_mat_uq::num_registers_per_major>;
		using _func = _fast_matrix_underlying::_basic_mul_func<_lhs_fast_mat_uq>;
		return _fast_matrix_underlying::_basic_func_for_matrix<true, _func, _lhs_fast_mat_uq>
		(
			_major_indices(),
			_register_indices(),
			std::forward<LhsFastMatrix_>(lhs_),
			std::forward<RhsScalarForAll_>(rhs_all_)
		);
	}
#pragma endregion

#pragma region BASIC_DIVIDE
	/// <summary>
	/// <para> Performs a basic division operation of the two passed FastMatrix instances, outputting the result as a FastMatrix of the left-hand type. </para>
	/// <para> The right-hand Matrix may be any size, but must encapsulate the same type with the same register width, and share the same major order. </para>
	/// <para> 
	///		If the right-hand Matrix does not contain respective registers to the left-hand Matrix, 
	///		indices will be copied directly from `lhs_`, as a divide by the implied 0 would result in likely unwanted NaNs. 
	/// </para>
	/// </summary>
	/// <param name="lhs_">FastMatrix appearing on the left-hand side of basic division. The output type will be the same as this FastMatrix type.</param>
	/// <param name="rhs_">
	///		FastMatrix appearing on the right-hand side of basic division, 
	///		which shares encapsulated type, register width, and major order with the left-hand operand.
	/// </param>
	/// <returns>FastMatrix resulting from dividing respective indices in the passed two FastMatrix instances.</returns>
	template<EmuConcepts::EmuFastMatrix LhsFastMatrix_, EmuConcepts::EmuFastMatrix RhsFastMatrix_>
	requires EmuConcepts::EmuFastMatrixBasicOpCompatible<LhsFastMatrix_, RhsFastMatrix_>
	[[nodiscard]] constexpr inline auto fast_matrix_basic_divide(LhsFastMatrix_&& lhs_, RhsFastMatrix_&& rhs_)
		-> typename EmuCore::TMP::remove_ref_cv<LhsFastMatrix_>::type
	{
		using _lhs_fast_mat_uq = typename EmuCore::TMP::remove_ref_cv<LhsFastMatrix_>::type;
		using _major_indices = std::make_index_sequence<_lhs_fast_mat_uq::num_major_elements>;
		using _register_indices = std::make_index_sequence<_lhs_fast_mat_uq::num_registers_per_major>;
		using _func = _fast_matrix_underlying::_basic_div_func<_lhs_fast_mat_uq>;
		return _fast_matrix_underlying::_basic_func_for_matrix<true, _func, _lhs_fast_mat_uq>
		(
			_major_indices(),
			_register_indices(),
			std::forward<LhsFastMatrix_>(lhs_),
			std::forward<RhsFastMatrix_>(rhs_)
		);
	}

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
	[[nodiscard]] constexpr inline auto fast_matrix_basic_divide(LhsFastMatrix_&& lhs_, RhsMajorFastVector_&& rhs_all_majors_)
		-> typename EmuCore::TMP::remove_ref_cv<LhsFastMatrix_>::type
	{
		using _lhs_fast_mat_uq = typename EmuCore::TMP::remove_ref_cv<LhsFastMatrix_>::type;
		using _major_indices = std::make_index_sequence<_lhs_fast_mat_uq::num_major_elements>;
		using _register_indices = std::make_index_sequence<_lhs_fast_mat_uq::num_registers_per_major>;
		using _func = _fast_matrix_underlying::_basic_div_func<_lhs_fast_mat_uq>;
		return _fast_matrix_underlying::_basic_func_for_matrix<true, _func, _lhs_fast_mat_uq>
		(
			_major_indices(),
			_register_indices(),
			std::forward<LhsFastMatrix_>(lhs_),
			std::forward<RhsMajorFastVector_>(rhs_all_majors_)
		);
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
	[[nodiscard]] constexpr inline auto fast_matrix_basic_divide(LhsFastMatrix_&& lhs_, RhsRegisterForAll_&& rhs_all_registers_)
		-> typename EmuCore::TMP::remove_ref_cv<LhsFastMatrix_>::type
	{
		using _lhs_fast_mat_uq = typename EmuCore::TMP::remove_ref_cv<LhsFastMatrix_>::type;
		using _major_indices = std::make_index_sequence<_lhs_fast_mat_uq::num_major_elements>;
		using _register_indices = std::make_index_sequence<_lhs_fast_mat_uq::num_registers_per_major>;
		using _func = _fast_matrix_underlying::_basic_div_func<_lhs_fast_mat_uq>;
		return _fast_matrix_underlying::_basic_func_for_matrix<true, _func, _lhs_fast_mat_uq>
		(
			_major_indices(),
			_register_indices(),
			std::forward<LhsFastMatrix_>(lhs_),
			std::forward<RhsRegisterForAll_>(rhs_all_registers_)
		);
	}

	/// <summary>
	/// <para> Performs a basic division operation of the passed FastMatrix and scalar, outputting the result as a FastMatrix of the left-hand type. </para>
	/// </summary>
	/// <param name="lhs_">FastMatrix appearing on the left-hand side of division. The output type will be the same as this FastMatrix type.</param>
	/// <param name="rhs_">Scalar to create a register of and divide all of the passed Matrix's indices by.</param>
	/// <returns>FastMatrix resulting from dividing all indices of the passed Matrix by the passed scalar value.</returns>
	template<EmuConcepts::EmuFastMatrix LhsFastMatrix_, EmuConcepts::Arithmetic RhsScalarForAll_>
	requires EmuConcepts::EmuFastMatrixBasicOpCompatible<LhsFastMatrix_, RhsScalarForAll_>
	[[nodiscard]] constexpr inline auto fast_matrix_basic_divide(LhsFastMatrix_&& lhs_, RhsScalarForAll_&& rhs_all_)
		-> typename EmuCore::TMP::remove_ref_cv<LhsFastMatrix_>::type
	{
		using _lhs_fast_mat_uq = typename EmuCore::TMP::remove_ref_cv<LhsFastMatrix_>::type;
		using _major_indices = std::make_index_sequence<_lhs_fast_mat_uq::num_major_elements>;
		using _register_indices = std::make_index_sequence<_lhs_fast_mat_uq::num_registers_per_major>;
		using _func = _fast_matrix_underlying::_basic_div_func<_lhs_fast_mat_uq>;
		return _fast_matrix_underlying::_basic_func_for_matrix<true, _func, _lhs_fast_mat_uq>
		(
			_major_indices(),
			_register_indices(),
			std::forward<LhsFastMatrix_>(lhs_),
			std::forward<RhsScalarForAll_>(rhs_all_)
		);
	}
#pragma endregion

#pragma region BASIC_MOD
	/// <summary>
	/// <para> Performs a basic modulo division operation of the two passed FastMatrix instances, outputting the result as a FastMatrix of the left-hand type. </para>
	/// <para> The right-hand Matrix may be any size, but must encapsulate the same type with the same register width, and share the same major order. </para>
	/// <para> 
	///		If the right-hand Matrix does not contain respective registers to the left-hand Matrix, 
	///		indices will be copied directly from `lhs_`, as a divide by the implied 0 would result in likely unwanted NaNs. 
	/// </para>
	/// </summary>
	/// <param name="lhs_">FastMatrix appearing on the left-hand side of basic modulo division. The output type will be the same as this FastMatrix type.</param>
	/// <param name="rhs_">
	///		FastMatrix appearing on the right-hand side of basic modulo division, 
	///		which shares encapsulated type, register width, and major order with the left-hand operand.
	/// </param>
	/// <returns>FastMatrix resulting from modulo dividing respective indices in the passed two FastMatrix instances.</returns>
	template<EmuConcepts::EmuFastMatrix LhsFastMatrix_, EmuConcepts::EmuFastMatrix RhsFastMatrix_>
	requires EmuConcepts::EmuFastMatrixBasicOpCompatible<LhsFastMatrix_, RhsFastMatrix_>
	[[nodiscard]] constexpr inline auto fast_matrix_basic_mod(LhsFastMatrix_&& lhs_, RhsFastMatrix_&& rhs_)
		-> typename EmuCore::TMP::remove_ref_cv<LhsFastMatrix_>::type
	{
		using _lhs_fast_mat_uq = typename EmuCore::TMP::remove_ref_cv<LhsFastMatrix_>::type;
		using _major_indices = std::make_index_sequence<_lhs_fast_mat_uq::num_major_elements>;
		using _register_indices = std::make_index_sequence<_lhs_fast_mat_uq::num_registers_per_major>;
		using _func = _fast_matrix_underlying::_basic_mod_func<_lhs_fast_mat_uq>;
		return _fast_matrix_underlying::_basic_func_for_matrix<true, _func, _lhs_fast_mat_uq>
		(
			_major_indices(),
			_register_indices(),
			std::forward<LhsFastMatrix_>(lhs_),
			std::forward<RhsFastMatrix_>(rhs_)
		);
	}

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
	[[nodiscard]] constexpr inline auto fast_matrix_basic_mod(LhsFastMatrix_&& lhs_, RhsMajorFastVector_&& rhs_all_majors_)
		-> typename EmuCore::TMP::remove_ref_cv<LhsFastMatrix_>::type
	{
		using _lhs_fast_mat_uq = typename EmuCore::TMP::remove_ref_cv<LhsFastMatrix_>::type;
		using _major_indices = std::make_index_sequence<_lhs_fast_mat_uq::num_major_elements>;
		using _register_indices = std::make_index_sequence<_lhs_fast_mat_uq::num_registers_per_major>;
		using _func = _fast_matrix_underlying::_basic_mod_func<_lhs_fast_mat_uq>;
		return _fast_matrix_underlying::_basic_func_for_matrix<true, _func, _lhs_fast_mat_uq>
		(
			_major_indices(),
			_register_indices(),
			std::forward<LhsFastMatrix_>(lhs_),
			std::forward<RhsMajorFastVector_>(rhs_all_majors_)
		);
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
	[[nodiscard]] constexpr inline auto fast_matrix_basic_mod(LhsFastMatrix_&& lhs_, RhsRegisterForAll_&& rhs_all_registers_)
		-> typename EmuCore::TMP::remove_ref_cv<LhsFastMatrix_>::type
	{
		using _lhs_fast_mat_uq = typename EmuCore::TMP::remove_ref_cv<LhsFastMatrix_>::type;
		using _major_indices = std::make_index_sequence<_lhs_fast_mat_uq::num_major_elements>;
		using _register_indices = std::make_index_sequence<_lhs_fast_mat_uq::num_registers_per_major>;
		using _func = _fast_matrix_underlying::_basic_mod_func<_lhs_fast_mat_uq>;
		return _fast_matrix_underlying::_basic_func_for_matrix<true, _func, _lhs_fast_mat_uq>
		(
			_major_indices(),
			_register_indices(),
			std::forward<LhsFastMatrix_>(lhs_),
			std::forward<RhsRegisterForAll_>(rhs_all_registers_)
		);
	}

	/// <summary>
	/// <para> Performs a basic modulo division operation of the passed FastMatrix and scalar, outputting the result as a FastMatrix of the left-hand type. </para>
	/// </summary>
	/// <param name="lhs_">FastMatrix appearing on the left-hand side of modulo division. The output type will be the same as this FastMatrix type.</param>
	/// <param name="rhs_">Scalar to create a register of and modulo divide all of the passed Matrix's indices by.</param>
	/// <returns>FastMatrix resulting from modulo dividing all indices of the passed Matrix by the passed scalar value.</returns>
	template<EmuConcepts::EmuFastMatrix LhsFastMatrix_, EmuConcepts::Arithmetic RhsScalarForAll_>
	requires EmuConcepts::EmuFastMatrixBasicOpCompatible<LhsFastMatrix_, RhsScalarForAll_>
	[[nodiscard]] constexpr inline auto fast_matrix_basic_mod(LhsFastMatrix_&& lhs_, RhsScalarForAll_&& rhs_all_)
		-> typename EmuCore::TMP::remove_ref_cv<LhsFastMatrix_>::type
	{
		using _lhs_fast_mat_uq = typename EmuCore::TMP::remove_ref_cv<LhsFastMatrix_>::type;
		using _major_indices = std::make_index_sequence<_lhs_fast_mat_uq::num_major_elements>;
		using _register_indices = std::make_index_sequence<_lhs_fast_mat_uq::num_registers_per_major>;
		using _func = _fast_matrix_underlying::_basic_mod_func<_lhs_fast_mat_uq>;
		return _fast_matrix_underlying::_basic_func_for_matrix<true, _func, _lhs_fast_mat_uq>
		(
			_major_indices(),
			_register_indices(),
			std::forward<LhsFastMatrix_>(lhs_),
			std::forward<RhsScalarForAll_>(rhs_all_)
		);
	}
#pragma endregion

#pragma region BASIC_FMADD
	/// <summary>
	/// <para> Performs a basic multiplication operation of the two passed FastMatrix instances, outputting the result as a FastMatrix of the left-hand type. </para>
	/// <para> Intermediate multiplication results will have the passed `to_add_` Matrix added as part of a fused-multiply-add operation. </para>
	/// <para> The other Matrices may be any size, but must encapsulate the same type with the same register width, and share the same major order. </para>
	/// <para> If the right-hand Matrix does not contain respective registers to the left-hand Matrix, indices will be zeroed as if multiplied by 0. </para>
	/// <para> If the `to_add_` Matrix does not contain a respective register to the left-hand Matrix, only a basic multiply will be performed for it. </para>
	/// </summary>
	/// <param name="lhs_">FastMatrix appearing on the left-hand side of basic multiplication. The output type will be the same as this FastMatrix type.</param>
	/// <param name="rhs_">
	///		FastMatrix appearing on the right-hand side of basic multiplication, 
	///		which shares encapsulated type, register width, and major order with the left-hand operand.
	/// </param>
	/// <param name="to_add_">
	///		FastMatrix to add to the intermediate multiplication result, 
	///		which shares encapsulated type, register width, and major order with the left-hand operand.
	/// </param>
	/// <returns>
	///		FastMatrix resulting from multiplying respective indices in the passed `lhs_` and `rhs_` FastMatrix instances, 
	///		and adding respective indices in `to_add_` to the intermediate multiplication results.
	/// </returns>
	template<EmuConcepts::EmuFastMatrix LhsFastMatrix_, EmuConcepts::EmuFastMatrix RhsFastMatrix_, EmuConcepts::EmuFastMatrix ToAddFastMatrix_>
	[[nodiscard]] constexpr inline auto fast_matrix_basic_fmadd(LhsFastMatrix_&& lhs_, RhsFastMatrix_&& rhs_, ToAddFastMatrix_&& to_add_)
		-> typename EmuCore::TMP::remove_ref_cv<LhsFastMatrix_>::type
	{
		using _lhs_fast_mat_uq = typename EmuCore::TMP::remove_ref_cv<LhsFastMatrix_>::type;
		using _major_indices = std::make_index_sequence<_lhs_fast_mat_uq::num_major_elements>;
		using _register_indices = std::make_index_sequence<_lhs_fast_mat_uq::num_registers_per_major>;
		using _func = _fast_matrix_underlying::_basic_fmadd_func<_lhs_fast_mat_uq>;
		return _fast_matrix_underlying::_basic_func_for_matrix<true, _func, _lhs_fast_mat_uq>
		(
			_major_indices(),
			_register_indices(),
			std::forward<LhsFastMatrix_>(lhs_),
			std::forward<RhsFastMatrix_>(rhs_),
			std::forward<ToAddFastMatrix_>(to_add_)
		);
	}
#pragma endregion

#pragma region BASIC_FMSUB
	/// <summary>
	/// <para> Performs a basic multiplication operation of the two passed FastMatrix instances, outputting the result as a FastMatrix of the left-hand type. </para>
	/// <para> Intermediate multiplication results will have the passed `to_subtract_` Matrix subtracted as part of a fused-multiply-subtract operation. </para>
	/// <para> The other Matrices may be any size, but must encapsulate the same type with the same register width, and share the same major order. </para>
	/// <para> If the right-hand Matrix does not contain respective registers to the left-hand Matrix, indices will be zeroed as if multiplied by 0. </para>
	/// <para> If the `to_subtract_` Matrix does not contain a respective register to the left-hand Matrix, only a basic multiply will be performed for it. </para>
	/// </summary>
	/// <param name="lhs_">FastMatrix appearing on the left-hand side of basic multiplication. The output type will be the same as this FastMatrix type.</param>
	/// <param name="rhs_">
	///		FastMatrix appearing on the right-hand side of basic multiplication, 
	///		which shares encapsulated type, register width, and major order with the left-hand operand.
	/// </param>
	/// <param name="to_subtract_">
	///		FastMatrix to subtract from the intermediate multiplication result, 
	///		which shares encapsulated type, register width, and major order with the left-hand operand.
	/// </param>
	/// <returns>
	///		FastMatrix resulting from multiplying respective indices in the passed `lhs_` and `rhs_` FastMatrix instances, 
	///		and subtracting respective indices in `to_subtract_` from the intermediate multiplication results.
	/// </returns>
	template<EmuConcepts::EmuFastMatrix LhsFastMatrix_, EmuConcepts::EmuFastMatrix RhsFastMatrix_, EmuConcepts::EmuFastMatrix ToSubtractFastMatrix_>
	requires EmuConcepts::EmuFastMatrixBasicOpCompatible<LhsFastMatrix_, RhsFastMatrix_, ToSubtractFastMatrix_>
	[[nodiscard]] constexpr inline auto fast_matrix_basic_fmsub(LhsFastMatrix_&& lhs_, RhsFastMatrix_&& rhs_, ToSubtractFastMatrix_&& to_subtract_)
		-> typename EmuCore::TMP::remove_ref_cv<LhsFastMatrix_>::type
	{
		using _lhs_fast_mat_uq = typename EmuCore::TMP::remove_ref_cv<LhsFastMatrix_>::type;
		using _major_indices = std::make_index_sequence<_lhs_fast_mat_uq::num_major_elements>;
		using _register_indices = std::make_index_sequence<_lhs_fast_mat_uq::num_registers_per_major>;
		using _func = _fast_matrix_underlying::_basic_fmsub_func<_lhs_fast_mat_uq>;
		return _fast_matrix_underlying::_basic_func_for_matrix<true, _func, _lhs_fast_mat_uq>
		(
			_major_indices(),
			_register_indices(),
			std::forward<LhsFastMatrix_>(lhs_),
			std::forward<RhsFastMatrix_>(rhs_),
			std::forward<ToSubtractFastMatrix_>(to_subtract_)
		);
	}
#pragma endregion

#pragma region STD_MULTIPLY
	/// <summary>
	/// <para> Standard Matrix * Matrix multiplication function for use with instances of EmuMath::FastMatrix. </para>
	/// <para> This is only available where the two passed Matrices encapsulate data that is exactly valid for a standard Matrix multiplication. </para>
	/// </summary>
	/// <param name="lhs_fast_matrix_">FastMatrix appearing on the left-hand side of standard Matrix multiplication.</param>
	/// <param name="rhs_fast_matrix_">FastMatrix appearing on the right-hand side of standard Matrix multiplication.</param>
	/// <returns>EmuMath FastMatrix resulting from a standard Matrix multiplication of the two passed operands.</returns>
	template<EmuConcepts::EmuFastMatrix LhsFastMatrix_, EmuConcepts::EmuFastMatrix RhsFastMatrix_>
	requires EmuConcepts::EmuFastMatrixMultPair<LhsFastMatrix_, RhsFastMatrix_>
	[[nodiscard]] constexpr inline auto fast_matrix_multiply(LhsFastMatrix_&& lhs_fast_matrix_, RhsFastMatrix_&& rhs_fast_matrix_)
		-> typename EmuMath::TMP::fast_matrix_multiply_result<LhsFastMatrix_, RhsFastMatrix_>::type
	{
		using _lhs_fast_mat_uq = typename EmuCore::TMP::remove_ref_cv<LhsFastMatrix_>::type;
		using _rhs_fast_mat_uq = typename EmuCore::TMP::remove_ref_cv<RhsFastMatrix_>::type;
		if constexpr (_lhs_fast_mat_uq::is_column_major)
		{
			constexpr std::size_t lhs_used_size =
			(
				_lhs_fast_mat_uq::num_rows < _lhs_fast_mat_uq::num_columns ?
				_lhs_fast_mat_uq::num_rows :
				_lhs_fast_mat_uq::num_columns
			);

			using rhs_column_indices = std::make_index_sequence<_rhs_fast_mat_uq::num_columns>;
			using lhs_column_indices_except_0 = EmuCore::TMP::make_offset_index_sequence<1, lhs_used_size - 1>;
			return _fast_matrix_underlying::_do_multiply_cm_any
			(
				EmuCore::TMP::const_lval_ref_cast<LhsFastMatrix_>(std::forward<LhsFastMatrix_>(lhs_fast_matrix_)),
				EmuCore::TMP::const_lval_ref_cast<RhsFastMatrix_>(std::forward<RhsFastMatrix_>(rhs_fast_matrix_)),
				rhs_column_indices(),
				lhs_column_indices_except_0()
			);
		}
		else
		{
			constexpr std::size_t rhs_used_size =
			(
				_rhs_fast_mat_uq::num_columns < _rhs_fast_mat_uq::num_rows ?
				_rhs_fast_mat_uq::num_columns :
				_rhs_fast_mat_uq::num_rows
			);

			using lhs_row_indices = std::make_index_sequence<_lhs_fast_mat_uq::num_rows>;
			using rhs_row_indices_except_0 = EmuCore::TMP::make_offset_index_sequence<1, rhs_used_size - 1>;
			return _fast_matrix_underlying::_do_multiply_rm_rm
			(
				EmuCore::TMP::const_lval_ref_cast<LhsFastMatrix_>(std::forward<LhsFastMatrix_>(lhs_fast_matrix_)),
				EmuCore::TMP::const_lval_ref_cast<RhsFastMatrix_>(std::forward<RhsFastMatrix_>(rhs_fast_matrix_)),
				lhs_row_indices(),
				rhs_row_indices_except_0()
			);
		}
	}

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
	[[nodiscard]] constexpr inline auto fast_matrix_multiply(LhsFastMatrix_&& lhs_, RhsMajorFastVector_&& rhs_all_majors_)
		-> typename EmuCore::TMP::remove_ref_cv<LhsFastMatrix_>::type
	{
		using _lhs_fast_mat_uq = typename EmuCore::TMP::remove_ref_cv<LhsFastMatrix_>::type;
		using _major_indices = std::make_index_sequence<_lhs_fast_mat_uq::num_major_elements>;
		using _register_indices = std::make_index_sequence<_lhs_fast_mat_uq::num_registers_per_major>;
		using _func = _fast_matrix_underlying::_basic_mul_func<_lhs_fast_mat_uq>;
		return _fast_matrix_underlying::_basic_func_for_matrix<true, _func, _lhs_fast_mat_uq>
		(
			_major_indices(),
			_register_indices(),
			std::forward<LhsFastMatrix_>(lhs_),
			std::forward<RhsMajorFastVector_>(rhs_all_majors_)
		);
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
	[[nodiscard]] constexpr inline auto fast_matrix_multiply(LhsFastMatrix_&& lhs_, RhsRegisterForAll_&& rhs_all_registers_)
		-> typename EmuCore::TMP::remove_ref_cv<LhsFastMatrix_>::type
	{
		using _lhs_fast_mat_uq = typename EmuCore::TMP::remove_ref_cv<LhsFastMatrix_>::type;
		using _major_indices = std::make_index_sequence<_lhs_fast_mat_uq::num_major_elements>;
		using _register_indices = std::make_index_sequence<_lhs_fast_mat_uq::num_registers_per_major>;
		using _func = _fast_matrix_underlying::_basic_mul_func<_lhs_fast_mat_uq>;
		return _fast_matrix_underlying::_basic_func_for_matrix<true, _func, _lhs_fast_mat_uq>
		(
			_major_indices(),
			_register_indices(),
			std::forward<LhsFastMatrix_>(lhs_),
			std::forward<RhsRegisterForAll_>(rhs_all_registers_)
		);
	}

	/// <summary>
	/// <para> Performs a basic multiplication operation of the passed FastMatrix and scalar, outputting the result as a FastMatrix of the left-hand type. </para>
	/// </summary>
	/// <param name="lhs_">FastMatrix appearing on the left-hand side of multiplication. The output type will be the same as this FastMatrix type.</param>
	/// <param name="rhs_">Scalar to create a register of and multiply all of the passed Matrix's indices by.</param>
	/// <returns>FastMatrix resulting from multiplying all indices of the passed Matrix by the passed scalar value.</returns>
	template<EmuConcepts::EmuFastMatrix LhsFastMatrix_, EmuConcepts::Arithmetic RhsScalarForAll_>
	requires EmuConcepts::EmuFastMatrixBasicOpCompatible<LhsFastMatrix_, RhsScalarForAll_>
	[[nodiscard]] constexpr inline auto fast_matrix_multiply(LhsFastMatrix_&& lhs_, RhsScalarForAll_&& rhs_all_)
		-> typename EmuCore::TMP::remove_ref_cv<LhsFastMatrix_>::type
	{
		using _lhs_fast_mat_uq = typename EmuCore::TMP::remove_ref_cv<LhsFastMatrix_>::type;
		using _major_indices = std::make_index_sequence<_lhs_fast_mat_uq::num_major_elements>;
		using _register_indices = std::make_index_sequence<_lhs_fast_mat_uq::num_registers_per_major>;
		using _func = _fast_matrix_underlying::_basic_mul_func<_lhs_fast_mat_uq>;
		return _fast_matrix_underlying::_basic_func_for_matrix<true, _func, _lhs_fast_mat_uq>
		(
			_major_indices(),
			_register_indices(),
			std::forward<LhsFastMatrix_>(lhs_),
			std::forward<RhsScalarForAll_>(rhs_all_)
		);
	}
#pragma endregion
}

#endif
