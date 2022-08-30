#ifndef EMU_MATH_FAST_MATRIX_ARITHMETIC_H_INC_
#define EMU_MATH_FAST_MATRIX_ARITHMETIC_H_INC_ 1

#include "_common_fast_matrix_helper_includes.h"

namespace EmuMath::Helpers
{
	/// <summary>
	/// <para> Performs a basic addition operation of the two passed FastMatrix instances, outputting the result as a FastMatrix of the left-hand type. </para>
	/// <para> The right-hand Matrix may be any size, but must encapsulate the same type with the same register width, and share the same major order. </para>
	/// <para> If the right-hand Matrix does not contain respective registers to the left-hand Matrix, indices will be copied directly from `lhs_`. </para>
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
		return _fast_matrix_underlying::_basic_func_for_matrix
		<
			true,
			_fast_matrix_underlying::_basic_add_func<_lhs_fast_mat_uq>,
			_lhs_fast_mat_uq
		>(_major_indices(), _register_indices(), std::forward<LhsFastMatrix_>(lhs_), std::forward<RhsFastMatrix_>(rhs_));
	}

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
		return _fast_matrix_underlying::_basic_func_for_matrix
		<
			true,
			_fast_matrix_underlying::_basic_sub_func<_lhs_fast_mat_uq>,
			_lhs_fast_mat_uq
		>(_major_indices(), _register_indices(), std::forward<LhsFastMatrix_>(lhs_), std::forward<RhsFastMatrix_>(rhs_));
	}

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
		return _fast_matrix_underlying::_basic_func_for_matrix
		<
			true,
			_fast_matrix_underlying::_basic_mul_func<_lhs_fast_mat_uq>,
			_lhs_fast_mat_uq
		>(_major_indices(), _register_indices(), std::forward<LhsFastMatrix_>(lhs_), std::forward<RhsFastMatrix_>(rhs_));
	}

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
		return _fast_matrix_underlying::_basic_func_for_matrix
		<
			true,
			_fast_matrix_underlying::_basic_div_func<_lhs_fast_mat_uq>,
			_lhs_fast_mat_uq
		>(_major_indices(), _register_indices(), std::forward<LhsFastMatrix_>(lhs_), std::forward<RhsFastMatrix_>(rhs_));
	}

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
		return _fast_matrix_underlying::_basic_func_for_matrix
		<
			true,
			_fast_matrix_underlying::_basic_mod_func<_lhs_fast_mat_uq>,
			_lhs_fast_mat_uq
		>(_major_indices(), _register_indices(), std::forward<LhsFastMatrix_>(lhs_), std::forward<RhsFastMatrix_>(rhs_));
	}

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
}

#endif
