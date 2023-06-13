#ifndef EMU_MATH_MATRIX_BITWISE_ARITHMETIC_XOR_H_INC_
#define EMU_MATH_MATRIX_BITWISE_ARITHMETIC_XOR_H_INC_ 1

#include "../_common_matrix_helper_includes.h"

// CONTAINS:
// --- bitwise_xor
// --- bitwise_xor_range
// --- bitwise_xor_range_no_copy

namespace EmuMath::Helpers
{
#pragma region XOR_CUSTOM_COLUMN_MAJOR_OUT
	/// <summary>
	/// <para>
	///		Outputs the result of bitwise XORing the provided lhs_matrix_ and rhs_ arguments as an EmuMath Matrix with the specified template arguments, 
	///		with size/column-major arguments matching those of lhs_matrix_ if not provided, and value_type_uq for its T_ argument if OutT_ is not provided.
	/// </para>
	/// <para> If Rhs_ is an EmuMath Matrix: Respective indices in each Matrix will be bitwise XORed. </para>
	/// <para> If Rhs_ is none of the above: All index bitwise operations will use the rhs_ directly. </para>
	/// </summary>
	/// <param name="lhs_matrix_">: EmuMath Matrix appearing on the left-hand side of this bitwise operation.</param>
	/// <param name="rhs_">: Scalar or EmuMath Matrix appearing on the right-hand side of this bitwise operation.</param>
	/// <returns>EmuMath Matrix containing the results of this bitwise operation in respective indices.</returns>
	template
	<
		std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, bool OutColumnMajor_,
		typename LhsT_, std::size_t LhsNumColumns_, std::size_t LhsNumRows_, bool LhsColumnMajor_, class Rhs_
	>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_> matrix_bitwise_xor
	(
		const EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>& lhs_matrix_,
		Rhs_&& rhs_
	)
	{
		using lhs_mat_ref = const EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>&;
		return EMU_MATH_MATRIX_MUTATE_COPY_TEMPLATE(EmuCore::do_bitwise_xor, OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_, lhs_mat_ref, 0, 0)
		(
			lhs_matrix_,
			lhs_matrix_,
			std::forward<Rhs_>(rhs_)
		);
	}

	template
	<
		typename OutT_, bool OutColumnMajor_,
		typename LhsT_, std::size_t LhsNumColumns_, std::size_t LhsNumRows_, bool LhsColumnMajor_, class Rhs_
	>
	[[nodiscard]] constexpr inline EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, OutT_, OutColumnMajor_> matrix_bitwise_xor
	(
		const EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>&  lhs_matrix_,
		Rhs_&& rhs_
	)
	{
		using lhs_mat_ref = const EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>&;
		return EMU_MATH_MATRIX_MUTATE_COPY_TEMPLATE(EmuCore::do_bitwise_xor, LhsNumColumns_, LhsNumRows_, OutT_, OutColumnMajor_, lhs_mat_ref, 0, 0)
		(
			lhs_matrix_,
			lhs_matrix_,
			std::forward<Rhs_>(rhs_)
		);
	}

	template
	<
		std::size_t OutNumColumns_, std::size_t OutNumRows_, bool OutColumnMajor_,
		typename LhsT_, std::size_t LhsNumColumns_, std::size_t LhsNumRows_, bool LhsColumnMajor_, class Rhs_
	>
	[[nodiscard]] constexpr inline EmuMath::Matrix
	<
		OutNumColumns_,
		OutNumRows_,
		typename EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>::value_type_uq,
		OutColumnMajor_
	>
	matrix_bitwise_xor(const EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>& lhs_matrix_, Rhs_&& rhs_)
	{
		using lhs_mat_ref = const EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>&;
		using lhs_value_uq = typename EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>::value_type_uq;
		return EMU_MATH_MATRIX_MUTATE_COPY_TEMPLATE(EmuCore::do_bitwise_xor, OutNumColumns_, OutNumRows_, lhs_value_uq, OutColumnMajor_, lhs_mat_ref, 0, 0)
		(
			lhs_matrix_,
			lhs_matrix_,
			std::forward<Rhs_>(rhs_)
		);
	}

	template<bool OutColumnMajor_, typename LhsT_, std::size_t LhsNumColumns_, std::size_t LhsNumRows_, bool LhsColumnMajor_, class Rhs_>
	[[nodiscard]] constexpr inline EmuMath::Matrix
	<
		LhsNumColumns_,
		LhsNumRows_,
		typename EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>::value_type_uq,
		OutColumnMajor_
	>
	matrix_bitwise_xor(const EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>& lhs_matrix_, Rhs_&& rhs_)
	{
		using lhs_mat_ref = const EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>&;
		using lhs_value_uq = typename EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>::value_type_uq;
		return EMU_MATH_MATRIX_MUTATE_COPY_TEMPLATE(EmuCore::do_bitwise_xor, LhsNumColumns_, LhsNumRows_, lhs_value_uq, OutColumnMajor_, lhs_mat_ref, 0, 0)
		(
			lhs_matrix_,
			lhs_matrix_,
			std::forward<Rhs_>(rhs_)
		);
	}
#pragma endregion

#pragma region XOR_MATCHING_COLUMN_MAJOR_OUT
	template
	<
		std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_,
		typename LhsT_, std::size_t LhsNumColumns_, std::size_t LhsNumRows_, bool LhsColumnMajor_, class Rhs_
	>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, LhsColumnMajor_> matrix_bitwise_xor
	(
		const EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>& lhs_matrix_,
		Rhs_&& rhs_
	)
	{
		using lhs_mat_ref = const EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>&;
		return EMU_MATH_MATRIX_MUTATE_COPY_TEMPLATE(EmuCore::do_bitwise_xor, OutNumColumns_, OutNumRows_, OutT_, LhsColumnMajor_, lhs_mat_ref, 0, 0)
		(
			lhs_matrix_,
			lhs_matrix_,
			std::forward<Rhs_>(rhs_)
		);
	}

	template<typename OutT_, typename LhsT_, std::size_t LhsNumColumns_, std::size_t LhsNumRows_, bool LhsColumnMajor_, class Rhs_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, OutT_, LhsColumnMajor_> matrix_bitwise_xor
	(
		const EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>& lhs_matrix_,
		Rhs_&& rhs_
	)
	{
		using lhs_mat_ref = const EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>&;
		return EMU_MATH_MATRIX_MUTATE_COPY_TEMPLATE(EmuCore::do_bitwise_xor, LhsNumColumns_, LhsNumRows_, OutT_, LhsColumnMajor_, lhs_mat_ref, 0, 0)
		(
			lhs_matrix_,
			lhs_matrix_,
			std::forward<Rhs_>(rhs_)
		);
	}

	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename LhsT_, std::size_t LhsNumColumns_, std::size_t LhsNumRows_, bool LhsColumnMajor_, class Rhs_>
	[[nodiscard]] constexpr inline EmuMath::Matrix
	<
		OutNumColumns_,
		OutNumRows_,
		typename EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>::value_type_uq,
		LhsColumnMajor_
	>
	matrix_bitwise_xor(const EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>& lhs_matrix_, Rhs_&& rhs_)
	{
		using lhs_mat_ref = const EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>&;
		using lhs_value_uq = typename EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>::value_type_uq;
		return EMU_MATH_MATRIX_MUTATE_COPY_TEMPLATE(EmuCore::do_bitwise_xor, OutNumColumns_, OutNumRows_, lhs_value_uq, LhsColumnMajor_, lhs_mat_ref, 0, 0)
		(
			lhs_matrix_,
			lhs_matrix_,
			std::forward<Rhs_>(rhs_)
		);
	}

	template<typename LhsT_, std::size_t LhsNumColumns_, std::size_t LhsNumRows_, bool LhsColumnMajor_, class Rhs_>
	[[nodiscard]] constexpr inline EmuMath::Matrix
	<
		LhsNumColumns_,
		LhsNumRows_,
		typename EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>::value_type_uq,
		LhsColumnMajor_
	>
	matrix_bitwise_xor(const EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>& lhs_matrix_, Rhs_&& rhs_)
	{
		using lhs_mat_ref = const EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>&;
		using lhs_value_uq = typename EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>::value_type_uq;
		return EMU_MATH_MATRIX_MUTATE_COPY_TEMPLATE(EmuCore::do_bitwise_xor, LhsNumColumns_, LhsNumRows_, lhs_value_uq, LhsColumnMajor_, lhs_mat_ref, 0, 0)
		(
			lhs_matrix_,
			lhs_matrix_,
			std::forward<Rhs_>(rhs_)
		);
	}
#pragma endregion

#pragma region XOR_RANGE_CUSTOM_COLUMN_MAJOR_OUT
	/// <summary>
	/// <para>
	///		Outputs the result of bitwise XORing the provided lhs_matrix_ and rhs_ arguments as an EmuMath Matrix with the specified template arguments, 
	///		with size/column-major arguments matching those of lhs_matrix_ if not provided, and value_type_uq for its T_ argument if OutT_ is not provided.
	/// </para>
	/// <para> Indices within the provided range will contain results of respective this bitwise operation operations. </para>
	/// <para> Indices outside of the provided range will be copies of the respective indices in lhs_matrix_. </para>
	/// <para> If Rhs_ is an EmuMath Matrix: Respective indices in each Matrix will be bitwise XORed. </para>
	/// <para> If Rhs_ is none of the above: All index bitwise operations will use the rhs_ directly. </para>
	/// </summary>
	/// <param name="lhs_matrix_">: EmuMath Matrix appearing on the left-hand side of this bitwise operation.</param>
	/// <param name="rhs_">: Scalar or EmuMath Matrix appearing on the right-hand side of this bitwise operation.</param>
	/// <returns>EmuMath Matrix containing the results of this bitwise operation in respective indices within the provided range, and copied respective elements elsewhere.</returns>
	template
	<
		std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_,
		std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, bool OutColumnMajor_,
		typename LhsT_, std::size_t LhsNumColumns_, std::size_t LhsNumRows_, bool LhsColumnMajor_, class Rhs_
	>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_> matrix_bitwise_xor_range
	(
		const EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>& lhs_matrix_,
		Rhs_&& rhs_
	)
	{
		using lhs_mat_ref = const EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>&;
		return EMU_MATH_MATRIX_MUTATE_COPY_RANGE_TEMPLATE
		(
			EmuCore::do_bitwise_xor, OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_, lhs_mat_ref, BeginColumn_, EndColumn_, BeginRow_, EndRow_, 0, 0
		)(lhs_matrix_, lhs_matrix_, std::forward<Rhs_>(rhs_));
	}

	template
	<
		std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_, typename OutT_, bool OutColumnMajor_,
		typename LhsT_, std::size_t LhsNumColumns_, std::size_t LhsNumRows_, bool LhsColumnMajor_, class Rhs_
	>
	[[nodiscard]] constexpr inline EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, OutT_, OutColumnMajor_> matrix_bitwise_xor_range
	(
		const EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>& lhs_matrix_,
		Rhs_&& rhs_
	)
	{
		using lhs_mat_ref = const EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>&;
		return EMU_MATH_MATRIX_MUTATE_COPY_RANGE_TEMPLATE
		(
			EmuCore::do_bitwise_xor, LhsNumColumns_, LhsNumRows_, OutT_, OutColumnMajor_, lhs_mat_ref, BeginColumn_, EndColumn_, BeginRow_, EndRow_, 0, 0
		)(lhs_matrix_, lhs_matrix_, std::forward<Rhs_>(rhs_));
	}

	template
	<
		std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_, std::size_t OutNumColumns_, std::size_t OutNumRows_, bool OutColumnMajor_,
		typename LhsT_, std::size_t LhsNumColumns_, std::size_t LhsNumRows_, bool LhsColumnMajor_, class Rhs_
	>
	[[nodiscard]] constexpr inline EmuMath::Matrix
	<
		OutNumColumns_,
		OutNumRows_,
		typename EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>::value_type_uq,
		OutColumnMajor_
	>
	matrix_bitwise_xor_range(const EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>& lhs_matrix_, Rhs_&& rhs_)
	{
		using lhs_mat_ref = const EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>&;
		using lhs_value_uq = typename EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>::value_type_uq;
		return EMU_MATH_MATRIX_MUTATE_COPY_RANGE_TEMPLATE
		(
			EmuCore::do_bitwise_xor, OutNumColumns_, OutNumRows_, lhs_value_uq, OutColumnMajor_, lhs_mat_ref, BeginColumn_, EndColumn_, BeginRow_, EndRow_, 0, 0
		)(lhs_matrix_, lhs_matrix_, std::forward<Rhs_>(rhs_));
	}

	template
	<
		std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_, bool OutColumnMajor_,
		typename LhsT_, std::size_t LhsNumColumns_, std::size_t LhsNumRows_, bool LhsColumnMajor_, class Rhs_
	>
	[[nodiscard]] constexpr inline EmuMath::Matrix
	<
		LhsNumColumns_,
		LhsNumRows_,
		typename EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>::value_type_uq,
		OutColumnMajor_
	>
	matrix_bitwise_xor_range(const EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>& lhs_matrix_, Rhs_&& rhs_)
	{
		using lhs_mat_ref = const EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>&;
		using lhs_value_uq = typename EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>::value_type_uq;
		return EMU_MATH_MATRIX_MUTATE_COPY_RANGE_TEMPLATE
		(
			EmuCore::do_bitwise_xor, LhsNumColumns_, LhsNumRows_, lhs_value_uq, OutColumnMajor_, lhs_mat_ref, BeginColumn_, EndColumn_, BeginRow_, EndRow_, 0, 0
		)(lhs_matrix_, lhs_matrix_, std::forward<Rhs_>(rhs_));
	}
#pragma endregion

#pragma region XOR_RANGE_MATCHING_COLUMN_MAJOR_OUT
	template
	<
		std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_,
		std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_,
		typename LhsT_, std::size_t LhsNumColumns_, std::size_t LhsNumRows_, bool LhsColumnMajor_, class Rhs_
	>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, LhsColumnMajor_> matrix_bitwise_xor_range
	(
		const EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>& lhs_matrix_,
		Rhs_&& rhs_
	)
	{
		using lhs_mat_ref = const EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>&;
		return EMU_MATH_MATRIX_MUTATE_COPY_RANGE_TEMPLATE
		(
			EmuCore::do_bitwise_xor, OutNumColumns_, OutNumRows_, OutT_, LhsColumnMajor_, lhs_mat_ref, BeginColumn_, EndColumn_, BeginRow_, EndRow_, 0, 0
		)(lhs_matrix_, lhs_matrix_, std::forward<Rhs_>(rhs_));
	}

	template
	<
		std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_, typename OutT_,
		typename LhsT_, std::size_t LhsNumColumns_, std::size_t LhsNumRows_, bool LhsColumnMajor_, class Rhs_
	>
	[[nodiscard]] constexpr inline EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, OutT_, LhsColumnMajor_> matrix_bitwise_xor_range
	(
		const EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>& lhs_matrix_,
		Rhs_&& rhs_
	)
	{
		using lhs_mat_ref = const EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>&;
		return EMU_MATH_MATRIX_MUTATE_COPY_RANGE_TEMPLATE
		(
			EmuCore::do_bitwise_xor, LhsNumColumns_, LhsNumRows_, OutT_, LhsColumnMajor_, lhs_mat_ref, BeginColumn_, EndColumn_, BeginRow_, EndRow_, 0, 0
		)(lhs_matrix_, lhs_matrix_, std::forward<Rhs_>(rhs_));
	}

	template
	<
		std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_, std::size_t OutNumColumns_, std::size_t OutNumRows_,
		typename LhsT_, std::size_t LhsNumColumns_, std::size_t LhsNumRows_, bool LhsColumnMajor_, class Rhs_
	>
	[[nodiscard]] constexpr inline EmuMath::Matrix
	<
		OutNumColumns_,
		OutNumRows_,
		typename EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>::value_type_uq,
		LhsColumnMajor_
	>
	matrix_bitwise_xor_range(const EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>& lhs_matrix_, Rhs_&& rhs_)
	{
		using lhs_mat_ref = const EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>&;
		using lhs_value_uq = typename EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>::value_type_uq;
		return EMU_MATH_MATRIX_MUTATE_COPY_RANGE_TEMPLATE
		(
			EmuCore::do_bitwise_xor, OutNumColumns_, OutNumRows_, lhs_value_uq, LhsColumnMajor_, lhs_mat_ref, BeginColumn_, EndColumn_, BeginRow_, EndRow_, 0, 0
		)(lhs_matrix_, lhs_matrix_, std::forward<Rhs_>(rhs_));
	}

	template
	<
		std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_,
		typename LhsT_, std::size_t LhsNumColumns_, std::size_t LhsNumRows_, bool LhsColumnMajor_, class Rhs_
	>
	[[nodiscard]] constexpr inline EmuMath::Matrix
	<
		LhsNumColumns_,
		LhsNumRows_,
		typename EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>::value_type_uq,
		LhsColumnMajor_
	>
	matrix_bitwise_xor_range(const EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>& lhs_matrix_, Rhs_&& rhs_)
	{
		using lhs_mat_ref = const EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>&;
		using lhs_value_uq = typename EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>::value_type_uq;
		return EMU_MATH_MATRIX_MUTATE_COPY_RANGE_TEMPLATE
		(
			EmuCore::do_bitwise_xor, LhsNumColumns_, LhsNumRows_, lhs_value_uq, LhsColumnMajor_, lhs_mat_ref, BeginColumn_, EndColumn_, BeginRow_, EndRow_, 0, 0
		)(lhs_matrix_, lhs_matrix_, std::forward<Rhs_>(rhs_));
	}
#pragma endregion

#pragma region XOR_RANGE_NO_COPY_CUSTOM_COLUMN_MAJOR_OUT
	/// <summary>
	/// <para>
	///		Outputs the result of bitwise XORing the provided lhs_matrix_ and rhs_ arguments as an EmuMath Matrix with the specified template arguments, 
	///		with size/column-major arguments matching those of lhs_matrix_ if not provided, and value_type_uq for its T_ argument if OutT_ is not provided.
	/// </para>
	/// <para> Indices within the provided range will contain results of respective this bitwise operation operations. </para>
	/// <para> Indices outside of the provided range will be defaulted. </para>
	/// <para> If Rhs_ is an EmuMath Matrix: Respective indices in each Matrix will be bitwise XORed. </para>
	/// <para> If Rhs_ is none of the above: All index bitwise operations will use the rhs_ directly. </para>
	/// </summary>
	/// <param name="lhs_matrix_">: EmuMath Matrix appearing on the left-hand side of this bitwise operation.</param>
	/// <param name="rhs_">: Scalar or EmuMath Matrix appearing on the right-hand side of this bitwise operation.</param>
	/// <returns>EmuMath Matrix containing the results of this bitwise operation in respective indices within the provided range, and default-constructed elements elsewhere.</returns>
	template
	<
		std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_,
		std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, bool OutColumnMajor_,
		std::size_t LhsNumColumns_, std::size_t LhsNumRows_, typename LhsT_, bool LhsColumnMajor_, class Rhs_
	>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_> matrix_bitwise_xor_range_no_copy
	(
		const EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>& lhs_matrix_,
		Rhs_&& rhs_
	)
	{
		return EMU_MATH_MATRIX_MUTATE_TEMPLATE(EmuCore::do_bitwise_xor, OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_, BeginColumn_, EndColumn_, BeginRow_, EndRow_)
		(
			lhs_matrix_,
			std::forward<Rhs_>(rhs_)
		);
	}

	template
	<
		std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_, typename OutT_, bool OutColumnMajor_,
		std::size_t LhsNumColumns_, std::size_t LhsNumRows_, typename LhsT_, bool LhsColumnMajor_, class Rhs_
	>
	[[nodiscard]] constexpr inline EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, OutT_, OutColumnMajor_> matrix_bitwise_xor_range_no_copy
	(
		const EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>& lhs_matrix_,
		Rhs_&& rhs_
	)
	{
		return EMU_MATH_MATRIX_MUTATE_TEMPLATE(EmuCore::do_bitwise_xor, LhsNumColumns_, LhsNumRows_, OutT_, OutColumnMajor_, BeginColumn_, EndColumn_, BeginRow_, EndRow_)
		(
			lhs_matrix_,
			std::forward<Rhs_>(rhs_)
		);
	}

	template
	<
		std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_,
		std::size_t OutNumColumns_, std::size_t OutNumRows_, bool OutColumnMajor_,
		std::size_t LhsNumColumns_, std::size_t LhsNumRows_, typename LhsT_, bool LhsColumnMajor_, class Rhs_
	>
	[[nodiscard]] constexpr inline EmuMath::Matrix
	<
		OutNumColumns_,
		OutNumRows_,
		typename EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>::value_type_uq,
		OutColumnMajor_
	> 
	matrix_bitwise_xor_range_no_copy(const EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>& lhs_matrix_, Rhs_&& rhs_)
	{
		using lhs_value_uq = typename EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>::value_type_uq;
		return EMU_MATH_MATRIX_MUTATE_TEMPLATE(EmuCore::do_bitwise_xor, OutNumColumns_, OutNumRows_, lhs_value_uq, OutColumnMajor_, BeginColumn_, EndColumn_, BeginRow_, EndRow_)
		(
			lhs_matrix_,
			std::forward<Rhs_>(rhs_)
		);
	}

	template
	<
		std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_, bool OutColumnMajor_,
		std::size_t LhsNumColumns_, std::size_t LhsNumRows_, typename LhsT_, bool LhsColumnMajor_, class Rhs_
	>
	[[nodiscard]] constexpr inline EmuMath::Matrix
	<
		LhsNumColumns_,
		LhsNumRows_,
		typename EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>::value_type_uq,
		OutColumnMajor_
	> 
	matrix_bitwise_xor_range_no_copy(const EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>& lhs_matrix_, Rhs_&& rhs_)
	{
		using lhs_value_uq = typename EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>::value_type_uq;
		return EMU_MATH_MATRIX_MUTATE_TEMPLATE(EmuCore::do_bitwise_xor, LhsNumColumns_, LhsNumRows_, lhs_value_uq, OutColumnMajor_, BeginColumn_, EndColumn_, BeginRow_, EndRow_)
		(
			lhs_matrix_,
			std::forward<Rhs_>(rhs_)
		);
	}
#pragma endregion

#pragma region XOR_RANGE_NO_COPY_MATCHING_COLUMN_MAJOR_OUT
	template
	<
		std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_,
		std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_,
		std::size_t LhsNumColumns_, std::size_t LhsNumRows_, typename LhsT_, bool LhsColumnMajor_, class Rhs_
	>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, LhsColumnMajor_> matrix_bitwise_xor_range_no_copy
	(
		const EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>& lhs_matrix_,
		Rhs_&& rhs_
	)
	{
		return EMU_MATH_MATRIX_MUTATE_TEMPLATE(EmuCore::do_bitwise_xor, OutNumColumns_, OutNumRows_, OutT_, LhsColumnMajor_, BeginColumn_, EndColumn_, BeginRow_, EndRow_)
		(
			lhs_matrix_,
			std::forward<Rhs_>(rhs_)
		);
	}

	template
	<
		std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_, typename OutT_,
		std::size_t LhsNumColumns_, std::size_t LhsNumRows_, typename LhsT_, bool LhsColumnMajor_, class Rhs_
	>
	[[nodiscard]] constexpr inline EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, OutT_, LhsColumnMajor_> matrix_bitwise_xor_range_no_copy
	(
		const EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>& lhs_matrix_,
		Rhs_&& rhs_
	)
	{
		return EMU_MATH_MATRIX_MUTATE_TEMPLATE(EmuCore::do_bitwise_xor, LhsNumColumns_, LhsNumRows_, OutT_, LhsColumnMajor_, BeginColumn_, EndColumn_, BeginRow_, EndRow_)
		(
			lhs_matrix_,
			std::forward<Rhs_>(rhs_)
		);
	}

	template
	<
		std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_,
		std::size_t OutNumColumns_, std::size_t OutNumRows_,
		std::size_t LhsNumColumns_, std::size_t LhsNumRows_, typename LhsT_, bool LhsColumnMajor_, class Rhs_
	>
	[[nodiscard]] constexpr inline EmuMath::Matrix
	<
		OutNumColumns_,
		OutNumRows_,
		typename EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>::value_type_uq,
		LhsColumnMajor_
	> 
	matrix_bitwise_xor_range_no_copy(const EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>& lhs_matrix_, Rhs_&& rhs_)
	{
		using lhs_value_uq = typename EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>::value_type_uq;
		return EMU_MATH_MATRIX_MUTATE_TEMPLATE(EmuCore::do_bitwise_xor, OutNumColumns_, OutNumRows_, lhs_value_uq, LhsColumnMajor_, BeginColumn_, EndColumn_, BeginRow_, EndRow_)
		(
			lhs_matrix_,
			std::forward<Rhs_>(rhs_)
		);
	}

	template
	<
		std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_,
		std::size_t LhsNumColumns_, std::size_t LhsNumRows_, typename LhsT_, bool LhsColumnMajor_, class Rhs_
	>
	[[nodiscard]] constexpr inline EmuMath::Matrix
	<
		LhsNumColumns_,
		LhsNumRows_,
		typename EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>::value_type_uq,
		LhsColumnMajor_
	> 
	matrix_bitwise_xor_range_no_copy(const EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>& lhs_matrix_, Rhs_&& rhs_)
	{
		using lhs_value_uq = typename EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>::value_type_uq;
		return EMU_MATH_MATRIX_MUTATE_TEMPLATE(EmuCore::do_bitwise_xor, LhsNumColumns_, LhsNumRows_, lhs_value_uq, LhsColumnMajor_, BeginColumn_, EndColumn_, BeginRow_, EndRow_)
		(
			lhs_matrix_,
			std::forward<Rhs_>(rhs_)
		);
	}
#pragma endregion

#pragma region XOR_OUTPUT_ASSIGNED_VARIANTS
	/// <summary>
	/// <para> Outputs the result of bitwise XORing the provided lhs_matrix_ and rhs_ arguments to the provided out_matrix_. </para>
	/// <para> If Rhs_ is an EmuMath Matrix: Respective indices in each Matrix will be bitwise XORed. </para>
	/// <para> If Rhs_ is none of the above: All index bitwise operations will use the rhs_ directly. </para>
	/// </summary>
	/// <param name="out_matrix_">: EmuMath Matrix to output to.</param>
	/// <param name="lhs_matrix_">: EmuMath Matrix appearing on the left-hand side of this bitwise operation.</param>
	/// <param name="rhs_">: Scalar or EmuMath Matrix appearing on the right-hand side of this bitwise operation.</param>
	template
	<
		class Rhs_, typename LhsT_, std::size_t LhsNumColumns_, std::size_t LhsNumRows_, bool LhsColumnMajor_,
		std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, bool OutColumnMajor_
	>
	constexpr inline void matrix_bitwise_xor
	(
		EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>& out_matrix_,
		const EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>& lhs_matrix_,
		Rhs_&& rhs_
	)
	{
		using lhs_mat_ref = const EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>&;
		EMU_MATH_MATRIX_MUTATE_COPY_ASSIGN_TEMPLATE(EmuCore::do_bitwise_xor, lhs_mat_ref, 0, OutNumColumns_, 0, OutNumRows_, 0, 0)
		(
			out_matrix_,
			lhs_matrix_,
			lhs_matrix_,
			std::forward<Rhs_>(rhs_)
		);
	}

	/// <summary>
	/// <para> Outputs the result of bitwise XORing the provided lhs_matrix_ and rhs_ to the provided out_matrix_ </para>
	/// <para> Indices within the provided range will contain results of respective this bitwise operation operations. </para>
	/// <para> Indices outside of the provided range will be copies of the respective indices in lhs_matrix_. </para>
	/// <para> If Rhs_ is an EmuMath Matrix: Respective indices in each Matrix will be bitwise XORed. </para>
	/// <para> If Rhs_ is none of the above: All index bitwise operations will use the rhs_ directly. </para>
	/// </summary>
	/// <param name="out_matrix_">: EmuMath Matrix to output to.</param>
	/// <param name="lhs_matrix_">: EmuMath Matrix appearing on the left-hand side of this bitwise operation.</param>
	/// <param name="rhs_">: Scalar or EmuMath Matrix appearing on the right-hand side of this bitwise operation.</param>
	template
	<
		std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_,
		class Rhs_, typename LhsT_, std::size_t LhsNumColumns_, std::size_t LhsNumRows_, bool LhsColumnMajor_,
		std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, bool OutColumnMajor_
	>
	constexpr inline void matrix_bitwise_xor_range
	(
		EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>& out_matrix_,
		const EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>& lhs_matrix_,
		Rhs_&& rhs_
	)
	{
		using lhs_mat_ref = const EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>&;
		EMU_MATH_MATRIX_MUTATE_COPY_ASSIGN_RANGE_TEMPLATE(EmuCore::do_bitwise_xor, lhs_mat_ref, BeginColumn_, EndColumn_, BeginRow_, EndRow_, 0, 0)
		(
			out_matrix_,
			lhs_matrix_,
			lhs_matrix_,
			std::forward<Rhs_>(rhs_)
		);
	}

	/// <summary>
	/// <para> Outputs the result of bitwise XORing the provided lhs_matrix_ and rhs_ arguments to the provided out_matrix_. </para>
	/// <para> Indices within the provided range will contain results of respective this bitwise operation operations. </para>
	/// <para> Indices outside of the provided range will not be modified. </para>
	/// <para> If Rhs_ is an EmuMath Matrix: Respective indices in each Matrix will be bitwise XORed. </para>
	/// <para> If Rhs_ is none of the above: All index bitwise operations will use the rhs_ directly. </para>
	/// </summary>
	/// <param name="out_matrix_">: EmuMath Matrix to output to.</param>
	/// <param name="lhs_matrix_">: EmuMath Matrix appearing on the left-hand side of this bitwise operation.</param>
	/// <param name="rhs_">: Scalar or EmuMath Matrix appearing on the right-hand side of this bitwise operation.</param>
	template
	<
		std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_,
		class Rhs_, typename LhsT_, std::size_t LhsNumColumns_, std::size_t LhsNumRows_, bool LhsColumnMajor_,
		std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, bool OutColumnMajor_
	>
	constexpr inline void matrix_bitwise_xor_range_no_copy
	(
		EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>& out_matrix_,
		const EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>& lhs_matrix_,
		Rhs_&& rhs_
	)
	{
		EMU_MATH_MATRIX_MUTATE_ASSIGN_TEMPLATE(EmuCore::do_bitwise_xor, BeginColumn_, EndColumn_, BeginRow_, EndRow_, 0, 0)
		(
			out_matrix_,
			lhs_matrix_,
			std::forward<Rhs_>(rhs_)
		);
	}
#pragma endregion
}

#endif
