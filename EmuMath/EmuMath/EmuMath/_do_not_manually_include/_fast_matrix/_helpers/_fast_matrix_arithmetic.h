#ifndef EMU_MATH_FAST_MATRIX_ARITHMETIC_H_INC_
#define EMU_MATH_FAST_MATRIX_ARITHMETIC_H_INC_ 1

#include "_common_fast_matrix_helper_includes.h"

namespace EmuMath::Helpers
{
#pragma region BASIC_ADD
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
	[[nodiscard]] constexpr inline auto fast_matrix_add(LhsFastMatrix_&& lhs_, Rhs_&& rhs_)
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
			std::forward<Rhs_>(rhs_)
		);
	}

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
	constexpr inline void fast_matrix_add_assign(LhsFastMatrix_& lhs_, Rhs_&& rhs_)
	{
		using _lhs_fast_mat_uq = typename EmuCore::TMP::remove_ref_cv<LhsFastMatrix_>::type;
		using _major_indices = std::make_index_sequence<_lhs_fast_mat_uq::num_major_elements>;
		using _register_indices = std::make_index_sequence<_lhs_fast_mat_uq::num_registers_per_major>;
		using _func = _fast_matrix_underlying::_basic_add_func<_lhs_fast_mat_uq>;
		_fast_matrix_underlying::_basic_func_assign_for_matrix<true, _func>
		(
			lhs_,
			_major_indices(),
			_register_indices(),
			lhs_,
			std::forward<Rhs_>(rhs_)
		);
	}
#pragma endregion

#pragma region BASIC_SUBTRACT
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
	[[nodiscard]] constexpr inline auto fast_matrix_subtract(LhsFastMatrix_&& lhs_, Rhs_&& rhs_)
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
			std::forward<Rhs_>(rhs_)
		);
	}

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
	constexpr inline void fast_matrix_subtract_assign(LhsFastMatrix_& lhs_, Rhs_&& rhs_)
	{
		using _lhs_fast_mat_uq = typename EmuCore::TMP::remove_ref_cv<LhsFastMatrix_>::type;
		using _major_indices = std::make_index_sequence<_lhs_fast_mat_uq::num_major_elements>;
		using _register_indices = std::make_index_sequence<_lhs_fast_mat_uq::num_registers_per_major>;
		using _func = _fast_matrix_underlying::_basic_sub_func<_lhs_fast_mat_uq>;
		_fast_matrix_underlying::_basic_func_assign_for_matrix<true, _func>
		(
			lhs_,
			_major_indices(),
			_register_indices(),
			lhs_,
			std::forward<Rhs_>(rhs_)
		);
	}
#pragma endregion

#pragma region BASIC_MULTIPLY
	/// <summary>
	/// <para> Performs a basic multiplication operation on this Matrix using the passed right-hand operand. </para>
	/// <para> This cannot be used to perform a standard multiplication by a Matrix. Use `fast_matrix_multiply` to allow such behaviour. </para>
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
	requires (EmuConcepts::EmuFastMatrixBasicOpCompatible<LhsFastMatrix_, Rhs_>)
	[[nodiscard]] constexpr inline auto fast_matrix_basic_multiply(LhsFastMatrix_&& lhs_, Rhs_&& rhs_)
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
			std::forward<Rhs_>(rhs_)
		);
	}

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
	constexpr inline void fast_matrix_basic_multiply_assign(LhsFastMatrix_& lhs_, Rhs_&& rhs_)
	{
		using _lhs_fast_mat_uq = typename EmuCore::TMP::remove_ref_cv<LhsFastMatrix_>::type;
		using _major_indices = std::make_index_sequence<_lhs_fast_mat_uq::num_major_elements>;
		using _register_indices = std::make_index_sequence<_lhs_fast_mat_uq::num_registers_per_major>;
		using _func = _fast_matrix_underlying::_basic_mul_func<_lhs_fast_mat_uq>;
		_fast_matrix_underlying::_basic_func_assign_for_matrix<true, _func>
		(
			lhs_,
			_major_indices(),
			_register_indices(),
			lhs_,
			std::forward<Rhs_>(rhs_)
		);
	}
#pragma endregion

#pragma region BASIC_DIVIDE
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
	requires (EmuConcepts::EmuFastMatrixBasicOpCompatible<LhsFastMatrix_, Rhs_>)
	[[nodiscard]] constexpr inline auto fast_matrix_basic_divide(LhsFastMatrix_&& lhs_, Rhs_&& rhs_)
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
			std::forward<Rhs_>(rhs_)
		);
	}

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
	constexpr inline void fast_matrix_basic_divide_assign(LhsFastMatrix_& lhs_, Rhs_&& rhs_)
	{
		using _lhs_fast_mat_uq = typename EmuCore::TMP::remove_ref_cv<LhsFastMatrix_>::type;
		using _major_indices = std::make_index_sequence<_lhs_fast_mat_uq::num_major_elements>;
		using _register_indices = std::make_index_sequence<_lhs_fast_mat_uq::num_registers_per_major>;
		using _func = _fast_matrix_underlying::_basic_div_func<_lhs_fast_mat_uq>;
		_fast_matrix_underlying::_basic_func_assign_for_matrix<true, _func>
		(
			lhs_,
			_major_indices(),
			_register_indices(),
			lhs_,
			std::forward<Rhs_>(rhs_)
		);
	}
#pragma endregion

#pragma region BASIC_MOD
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
	requires (EmuConcepts::EmuFastMatrixBasicOpCompatible<LhsFastMatrix_, Rhs_>)
	[[nodiscard]] constexpr inline auto fast_matrix_basic_mod(LhsFastMatrix_&& lhs_, Rhs_&& rhs_)
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
			std::forward<Rhs_>(rhs_)
		);
	}

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
	constexpr inline void fast_matrix_basic_mod_assign(LhsFastMatrix_& lhs_, Rhs_&& rhs_)
	{
		using _lhs_fast_mat_uq = typename EmuCore::TMP::remove_ref_cv<LhsFastMatrix_>::type;
		using _major_indices = std::make_index_sequence<_lhs_fast_mat_uq::num_major_elements>;
		using _register_indices = std::make_index_sequence<_lhs_fast_mat_uq::num_registers_per_major>;
		using _func = _fast_matrix_underlying::_basic_mod_func<_lhs_fast_mat_uq>;
		_fast_matrix_underlying::_basic_func_assign_for_matrix<true, _func>
		(
			lhs_,
			_major_indices(),
			_register_indices(),
			lhs_,
			std::forward<Rhs_>(rhs_)
		);
	}
#pragma endregion

#pragma region BASIC_FMADD
	/// <summary>
	/// <para>
	///		Performs a basic fused-multiply-add operation on the `lhs_` FastMatrix, 
	///		multiplying it by `rhs_` and adding `to_add_` to the intermediate multiplication result.
	/// </para>
	/// <para> `Rhs_` and `ToAdd_` will be treated in one of the following ways: </para>
	/// <para> --- 1: Where it is a FastMatrix of the same `register_type`, `value_type` and major-order, respective registers will be multiplied/added. </para>
	/// <para> 
	///		--- 2: Where it is a FastVector of the same `register_type` and `value_type`, it will be treated as a major chunk, 
	///		and registers in all major chunks will be used with the respective register of the FastVector.
	/// </para>
	/// <para> --- 3: Where it is a SIMD register recognised by EmuSIMD, all calculations will use that register. </para>
	/// <para> --- 4: Where is is an arithmetic scalar, all indices will use that value. An intermediate register will be set to achieve this. </para>
	/// </summary>
	/// <param name="lhs_">FastMatrix appearing on the left-hand side of basic multiplication. The output type will be the same as this FastMatrix type.</param>
	/// <param name="rhs_">One of the several described argument types, appearing on the right-hand side of basic multiplication.</param>
	/// <param name="to_add_">One of the several described argument types, which will be added to intermediate multiplication results.</param>
	/// <returns>FastMatrix of the input `lhs_` type containing the results of a fused-multiply-add operation with the provided operands.</returns>
	template<EmuConcepts::EmuFastMatrix LhsFastMatrix_, class Rhs_, class ToAdd_>
	requires EmuConcepts::EmuFastMatrixBasicOpCompatible<LhsFastMatrix_, Rhs_, ToAdd_>
	[[nodiscard]] constexpr inline auto fast_matrix_basic_fmadd(LhsFastMatrix_&& lhs_, Rhs_&& rhs_, ToAdd_&& to_add_)
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
			std::forward<Rhs_>(rhs_),
			std::forward<ToAdd_>(to_add_)
		);
	}

	/// <summary>
	/// <para>
	///		Performs a basic fused-multiply-add operation on the `lhs_` FastMatrix, 
	///		multiplying it by `rhs_` and adding `to_add_` to the intermediate multiplication result.
	/// </para>
	/// <para> `Rhs_` and `ToAdd_` will be treated in one of the following ways: </para>
	/// <para> --- 1: Where it is a FastMatrix of the same `register_type`, `value_type` and major-order, respective registers will be multiplied/added. </para>
	/// <para> 
	///		--- 2: Where it is a FastVector of the same `register_type` and `value_type`, it will be treated as a major chunk, 
	///		and registers in all major chunks will be used with the respective register of the FastVector.
	/// </para>
	/// <para> --- 3: Where it is a SIMD register recognised by EmuSIMD, all calculations will use that register. </para>
	/// <para> --- 4: Where is is an arithmetic scalar, all indices will use that value. An intermediate register will be set to achieve this. </para>
	/// </summary>
	/// <param name="lhs_">FastMatrix appearing on the left-hand side of basic multiplication. Results are assigned to this Matrix.</param>
	/// <param name="rhs_">One of the several described argument types, appearing on the right-hand side of basic multiplication.</param>
	/// <param name="to_add_">One of the several described argument types, which will be added to intermediate multiplication results.</param>
	template<EmuConcepts::EmuFastMatrix LhsFastMatrix_, class Rhs_, class ToAdd_>
	requires ((EmuConcepts::EmuFastMatrixBasicOpCompatible<LhsFastMatrix_, Rhs_, ToAdd_>) && !std::is_const_v<LhsFastMatrix_>)
	constexpr inline void fast_matrix_basic_fmadd_assign(LhsFastMatrix_& lhs_, Rhs_&& rhs_, ToAdd_&& to_add_)
	{
		using _lhs_fast_mat_uq = typename EmuCore::TMP::remove_ref_cv<LhsFastMatrix_>::type;
		using _major_indices = std::make_index_sequence<_lhs_fast_mat_uq::num_major_elements>;
		using _register_indices = std::make_index_sequence<_lhs_fast_mat_uq::num_registers_per_major>;
		using _func = _fast_matrix_underlying::_basic_fmadd_func<_lhs_fast_mat_uq>;
		_fast_matrix_underlying::_basic_func_assign_for_matrix<true, _func>
		(
			lhs_,
			_major_indices(),
			_register_indices(),
			lhs_,
			std::forward<Rhs_>(rhs_),
			std::forward<ToAdd_>(to_add_)
		);
	}
#pragma endregion

#pragma region BASIC_FMSUB
	/// <summary>
	/// <para>
	///		Performs a basic fused-multiply-subtract operation on the `lhs_` FastMatrix, 
	///		multiplying it by `rhs_` and subtracting `to_subtract_` from the intermediate multiplication result.
	/// </para>
	/// <para> `Rhs_` and `ToSubtract_` will be treated in one of the following ways: </para>
	/// <para> --- 1: Where it is a FastMatrix of the same `register_type`, `value_type` and major-order, respective registers will be multiplied/subtracted. </para>
	/// <para> 
	///		--- 2: Where it is a FastVector of the same `register_type` and `value_type`, it will be treated as a major chunk, 
	///		and registers in all major chunks will be used with the respective register of the FastVector.
	/// </para>
	/// <para> --- 3: Where it is a SIMD register recognised by EmuSIMD, all calculations will use that register. </para>
	/// <para> --- 4: Where is is an arithmetic scalar, all indices will use that value. An intermediate SIMD register will be set to achieve this. </para>
	/// </summary>
	/// <param name="lhs_">FastMatrix appearing on the left-hand side of basic multiplication. The output type will be the same as this FastMatrix type.</param>
	/// <param name="rhs_">One of the several described argument types, appearing on the right-hand side of basic multiplication.</param>
	/// <param name="to_subtract_">One of the several described argument types, which will be subtracted from intermediate multiplication results.</param>
	/// <returns>FastMatrix of the input `lhs_` type containing the results of a fused-multiply-subtract operation with the provided operands.</returns>
	template<EmuConcepts::EmuFastMatrix LhsFastMatrix_, class Rhs_, class ToSubtract_>
	requires EmuConcepts::EmuFastMatrixBasicOpCompatible<LhsFastMatrix_, Rhs_, ToSubtract_>
	[[nodiscard]] constexpr inline auto fast_matrix_basic_fmsub(LhsFastMatrix_&& lhs_, Rhs_&& rhs_, ToSubtract_&& to_subtract_)
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
			std::forward<Rhs_>(rhs_),
			std::forward<ToSubtract_>(to_subtract_)
		);
	}

	/// <summary>
	/// <para>
	///		Performs a basic fused-multiply-subtract operation on the `lhs_` FastMatrix, 
	///		multiplying it by `rhs_` and adding `to_subtract_` to the intermediate multiplication result.
	/// </para>
	/// <para> `Rhs_` and `ToAdd_` will be treated in one of the following ways: </para>
	/// <para> --- 1: Where it is a FastMatrix of the same `register_type`, `value_type` and major-order, respective registers will be used </para>
	/// <para> 
	///		--- 2: Where it is a FastVector of the same `register_type` and `value_type`, it will be treated as a major chunk, 
	///		and registers in all major chunks will be used with the respective register of the FastVector.
	/// </para>
	/// <para> --- 3: Where it is a SIMD register recognised by EmuSIMD, all calculations will use that register. </para>
	/// <para> --- 4: Where is is an arithmetic scalar, all indices will use that value. An intermediate register will be set to achieve this. </para>
	/// </summary>
	/// <param name="lhs_">FastMatrix appearing on the left-hand side of basic multiplication. Results are assigned to this Matrix.</param>
	/// <param name="rhs_">One of the several described argument types, appearing on the right-hand side of basic multiplication.</param>
	/// <param name="to_subtract_">One of the several described argument types, which will be subtracted from intermediate multiplication results.</param>
	template<EmuConcepts::EmuFastMatrix LhsFastMatrix_, class Rhs_, class ToAdd_>
	requires ((EmuConcepts::EmuFastMatrixBasicOpCompatible<LhsFastMatrix_, Rhs_, ToAdd_>) && !std::is_const_v<LhsFastMatrix_>)
	constexpr inline void fast_matrix_basic_fmsub_assign(LhsFastMatrix_& lhs_, Rhs_&& rhs_, ToAdd_&& to_subtract_)
	{
		using _lhs_fast_mat_uq = typename EmuCore::TMP::remove_ref_cv<LhsFastMatrix_>::type;
		using _major_indices = std::make_index_sequence<_lhs_fast_mat_uq::num_major_elements>;
		using _register_indices = std::make_index_sequence<_lhs_fast_mat_uq::num_registers_per_major>;
		using _func = _fast_matrix_underlying::_basic_fmsub_func<_lhs_fast_mat_uq>;
		_fast_matrix_underlying::_basic_func_assign_for_matrix<true, _func>
		(
			lhs_,
			_major_indices(),
			_register_indices(),
			lhs_,
			std::forward<Rhs_>(rhs_),
			std::forward<ToAdd_>(to_subtract_)
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
	constexpr inline void fast_matrix_multiply_assign(LhsFastMatrix_& lhs_fast_matrix_, RhsFastMatrix_&& rhs_fast_matrix_)
	{
		lhs_fast_matrix_ = EmuMath::Helpers::fast_matrix_multiply(lhs_fast_matrix_, std::forward<RhsFastMatrix_>(rhs_fast_matrix_));
	}

	/// <summary>
	/// <para> Performs a basic multiplication operation on this Matrix using the passed right-hand operand. </para>
	/// <para>  This cannot be used to perform a basic, non-standard multiplication by a Matrix. Use `fast_matrix_basic_multiply` to allow such behaviour. </para>
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
	[[nodiscard]] constexpr inline auto fast_matrix_multiply(LhsFastMatrix_&& lhs_, Rhs_&& rhs_)
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
			std::forward<Rhs_>(rhs_)
		);
	}

	/// <summary>
	/// <para> Performs a basic multiplication operation on this Matrix using the passed right-hand operand. </para>
	/// <para> 
	///		This cannot be used to perform a basic, non-standard multiplication by a Matrix. 
	///		Use `fast_matrix_basic_multiply_assign` to allow such behaviour.
	/// </para>
	/// <para> `Rhs_` will be treated in one of the following ways: </para>
	/// <para> 
	///		--- 1: Where it is a FastVector of the same `register_type` and `value_type`, it will be treated as a major chunk, 
	///		and registers in all major chunks will be used with the respective register of the FastVector.
	/// </para>
	/// <para> --- 2: Where it is a SIMD register recognised by EmuSIMD, all calculations will use that register. </para>
	/// <para> --- 3: Where is is an arithmetic scalar, all indices will use that value. An intermediate register will be set to achieve this. </para>
	/// </summary>
	/// <param name="lhs_">FastMatrix appearing on the left-hand side of basic multiplication. Results are assigned to this Matrix.</param>
	/// <param name="rhs_">One of the several described argument types, appearing on the right-hand side of basic multiplication.</param>
	template<EmuConcepts::EmuFastMatrix LhsFastMatrix_, class Rhs_>
	requires (!(EmuConcepts::EmuFastMatrix<Rhs_>) && (EmuConcepts::EmuFastMatrixBasicOpCompatible<LhsFastMatrix_, Rhs_>) && !std::is_const_v<LhsFastMatrix_>)
	constexpr inline void fast_matrix_multiply_assign(LhsFastMatrix_& lhs_, Rhs_&& rhs_)
	{
		using _lhs_fast_mat_uq = typename EmuCore::TMP::remove_ref_cv<LhsFastMatrix_>::type;
		using _major_indices = std::make_index_sequence<_lhs_fast_mat_uq::num_major_elements>;
		using _register_indices = std::make_index_sequence<_lhs_fast_mat_uq::num_registers_per_major>;
		using _func = _fast_matrix_underlying::_basic_mul_func<_lhs_fast_mat_uq>;
		_fast_matrix_underlying::_basic_func_assign_for_matrix<true, _func>
		(
			lhs_,
			_major_indices(),
			_register_indices(),
			lhs_,
			std::forward<Rhs_>(rhs_)
		);
	}
#pragma endregion
}

#endif
