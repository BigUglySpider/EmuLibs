#ifndef EMU_MATH_MATRIX_BITWISE_ARITHMETIC_ASSIGN_H_INC_
#define EMU_MATH_MATRIX_BITWISE_ARITHMETIC_ASSIGN_H_INC_ 1

#include "_common_matrix_helper_includes.h"

// CONTAINS:
// --- bitwise_and_assign
// --- bitwise_and_assign_range

namespace EmuMath::Helpers
{
#pragma region AND_ASSIGN
	/// <summary>
	/// <para> Performs a bitwise AND-assign on the passed lhs_matrix_ with the provided rhs_ argument. </para>
	/// <para> If Rhs_ is an EmuMath Matrix: Respective indices in each Matrix will be ANDed. </para>
	/// <para> If Rhs_ is none of the above: All index operations will use the rhs_ directly. </para>
	/// </summary>
	/// <param name="lhs_matrix_">: EmuMath Matrix appearing on the left of bitwise-assignment operations.</param>
	/// <param name="rhs_">: Scalar or EmuMath Matrix appearing on the right of the bitwise operation.</param>
	template<bool ColumnMajorOrder_, class Rhs_, std::size_t LhsNumColumns_, std::size_t LhsNumRows_, typename LhsT_, bool LhsColumnMajor_>
	constexpr inline void matrix_bitwise_and_assign(EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>& lhs_matrix_, Rhs_&& rhs_)
	{
		EMU_MATH_MATRIX_MUTATE_INVOKE_ONLY_TEMPLATE(EmuCore::do_bitwise_and_assign, 0, LhsNumColumns_, 0, LhsNumRows_, ColumnMajorOrder_)
		(
			lhs_matrix_,
			std::forward<Rhs_>(rhs_)
		);
	}

	template<class Rhs_, std::size_t LhsNumColumns_, std::size_t LhsNumRows_, typename LhsT_, bool LhsColumnMajor_>
	constexpr inline void matrix_bitwise_and_assign(EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>& lhs_matrix_, Rhs_&& rhs_)
	{
		EMU_MATH_MATRIX_MUTATE_INVOKE_ONLY_TEMPLATE(EmuCore::do_bitwise_and_assign, 0, LhsNumColumns_, 0, LhsNumRows_, LhsColumnMajor_)
		(
			lhs_matrix_,
			std::forward<Rhs_>(rhs_)
		);
	}
#pragma endregion

#pragma region AND_ASSIGN_RANGE
	/// <summary>
	/// <para> Performs a bitwise AND-assign on the passed lhs_matrix_ with the provided rhs_ argument. </para>
	/// <para> Operations will only be performed for indices within the provided range. </para>
	/// <para> If Rhs_ is an EmuMath Matrix: Respective indices in each Matrix will be ANDed. </para>
	/// <para> If Rhs_ is none of the above: All index operations will use the rhs_ directly. </para>
	/// </summary>
	/// <param name="lhs_matrix_">: EmuMath Matrix appearing on the left of bitwise-assignment operations.</param>
	/// <param name="rhs_">: Scalar or EmuMath Matrix appearing on the right of the bitwise operation.</param>
	template
	<
		std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_, bool ColumnMajorOrder_,
		class Rhs_, std::size_t LhsNumColumns_, std::size_t LhsNumRows_, typename LhsT_, bool LhsColumnMajor_
	>
	constexpr inline void matrix_bitwise_and_assign_range(EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>& lhs_matrix_, Rhs_&& rhs_)
	{
		EMU_MATH_MATRIX_MUTATE_INVOKE_ONLY_TEMPLATE(EmuCore::do_bitwise_and_assign, BeginColumn_, EndColumn_, BeginRow_, EndRow_, ColumnMajorOrder_)
		(
			lhs_matrix_,
			std::forward<Rhs_>(rhs_)
		);
	}

	template
	<
		std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_,
		class Rhs_, std::size_t LhsNumColumns_, std::size_t LhsNumRows_, typename LhsT_, bool LhsColumnMajor_
	>
	constexpr inline void matrix_bitwise_and_assign_range(EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>& lhs_matrix_, Rhs_&& rhs_)
	{
		EMU_MATH_MATRIX_MUTATE_INVOKE_ONLY_TEMPLATE(EmuCore::do_bitwise_and_assign, BeginColumn_, EndColumn_, BeginRow_, EndRow_, LhsColumnMajor_)
		(
			lhs_matrix_,
			std::forward<Rhs_>(rhs_)
		);
	}
#pragma endregion

#pragma region OR_ASSIGN
	/// <summary>
	/// <para> Performs a bitwise AND-assign on the passed lhs_matrix_ with the provided rhs_ argument. </para>
	/// <para> If Rhs_ is an EmuMath Matrix: Respective indices in each Matrix will be ORed. </para>
	/// <para> If Rhs_ is none of the above: All index operations will use the rhs_ directly. </para>
	/// </summary>
	/// <param name="lhs_matrix_">: EmuMath Matrix appearing on the left of bitwise-assignment operations.</param>
	/// <param name="rhs_">: Scalar or EmuMath Matrix appearing on the right of the bitwise operation.</param>
	template<bool ColumnMajorOrder_, class Rhs_, std::size_t LhsNumColumns_, std::size_t LhsNumRows_, typename LhsT_, bool LhsColumnMajor_>
	constexpr inline void matrix_bitwise_or_assign(EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>& lhs_matrix_, Rhs_&& rhs_)
	{
		EMU_MATH_MATRIX_MUTATE_INVOKE_ONLY_TEMPLATE(EmuCore::do_bitwise_or_assign, 0, LhsNumColumns_, 0, LhsNumRows_, ColumnMajorOrder_)
		(
			lhs_matrix_,
			std::forward<Rhs_>(rhs_)
		);
	}

	template<class Rhs_, std::size_t LhsNumColumns_, std::size_t LhsNumRows_, typename LhsT_, bool LhsColumnMajor_>
	constexpr inline void matrix_bitwise_or_assign(EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>& lhs_matrix_, Rhs_&& rhs_)
	{
		EMU_MATH_MATRIX_MUTATE_INVOKE_ONLY_TEMPLATE(EmuCore::do_bitwise_or_assign, 0, LhsNumColumns_, 0, LhsNumRows_, LhsColumnMajor_)
		(
			lhs_matrix_,
			std::forward<Rhs_>(rhs_)
		);
	}
#pragma endregion

#pragma region OR_ASSIGN_RANGE
	/// <summary>
	/// <para> Performs a bitwise OR-assign on the passed lhs_matrix_ with the provided rhs_ argument. </para>
	/// <para> Operations will only be performed for indices within the provided range. </para>
	/// <para> If Rhs_ is an EmuMath Matrix: Respective indices in each Matrix will be ORed. </para>
	/// <para> If Rhs_ is none of the above: All index operations will use the rhs_ directly. </para>
	/// </summary>
	/// <param name="lhs_matrix_">: EmuMath Matrix appearing on the left of bitwise-assignment operations.</param>
	/// <param name="rhs_">: Scalar or EmuMath Matrix appearing on the right of the bitwise operation.</param>
	template
	<
		std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_, bool ColumnMajorOrder_,
		class Rhs_, std::size_t LhsNumColumns_, std::size_t LhsNumRows_, typename LhsT_, bool LhsColumnMajor_
	>
	constexpr inline void matrix_bitwise_or_assign_range(EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>& lhs_matrix_, Rhs_&& rhs_)
	{
		EMU_MATH_MATRIX_MUTATE_INVOKE_ONLY_TEMPLATE(EmuCore::do_bitwise_or_assign, BeginColumn_, EndColumn_, BeginRow_, EndRow_, ColumnMajorOrder_)
		(
			lhs_matrix_,
			std::forward<Rhs_>(rhs_)
		);
	}

	template
	<
		std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_,
		class Rhs_, std::size_t LhsNumColumns_, std::size_t LhsNumRows_, typename LhsT_, bool LhsColumnMajor_
	>
	constexpr inline void matrix_bitwise_or_assign_range(EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>& lhs_matrix_, Rhs_&& rhs_)
	{
		EMU_MATH_MATRIX_MUTATE_INVOKE_ONLY_TEMPLATE(EmuCore::do_bitwise_or_assign, BeginColumn_, EndColumn_, BeginRow_, EndRow_, LhsColumnMajor_)
		(
			lhs_matrix_,
			std::forward<Rhs_>(rhs_)
		);
	}
#pragma endregion

#pragma region XOR_ASSIGN
	/// <summary>
	/// <para> Performs a bitwise AND-assign on the passed lhs_matrix_ with the provided rhs_ argument. </para>
	/// <para> If Rhs_ is an EmuMath Matrix: Respective indices in each Matrix will be XORed. </para>
	/// <para> If Rhs_ is none of the above: All index operations will use the rhs_ directly. </para>
	/// </summary>
	/// <param name="lhs_matrix_">: EmuMath Matrix appearing on the left of bitwise-assignment operations.</param>
	/// <param name="rhs_">: Scalar or EmuMath Matrix appearing on the right of the bitwise operation.</param>
	template<bool ColumnMajorOrder_, class Rhs_, std::size_t LhsNumColumns_, std::size_t LhsNumRows_, typename LhsT_, bool LhsColumnMajor_>
	constexpr inline void matrix_bitwise_xor_assign(EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>& lhs_matrix_, Rhs_&& rhs_)
	{
		EMU_MATH_MATRIX_MUTATE_INVOKE_ONLY_TEMPLATE(EmuCore::do_bitwise_xor_assign, 0, LhsNumColumns_, 0, LhsNumRows_, ColumnMajorOrder_)
		(
			lhs_matrix_,
			std::forward<Rhs_>(rhs_)
		);
	}

	template<class Rhs_, std::size_t LhsNumColumns_, std::size_t LhsNumRows_, typename LhsT_, bool LhsColumnMajor_>
	constexpr inline void matrix_bitwise_xor_assign(EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>& lhs_matrix_, Rhs_&& rhs_)
	{
		EMU_MATH_MATRIX_MUTATE_INVOKE_ONLY_TEMPLATE(EmuCore::do_bitwise_xor_assign, 0, LhsNumColumns_, 0, LhsNumRows_, LhsColumnMajor_)
		(
			lhs_matrix_,
			std::forward<Rhs_>(rhs_)
		);
	}
#pragma endregion

#pragma region XOR_ASSIGN_RANGE
	/// <summary>
	/// <para> Performs a bitwise XOR-assign on the passed lhs_matrix_ with the provided rhs_ argument. </para>
	/// <para> Operations will only be performed for indices within the provided range. </para>
	/// <para> If Rhs_ is an EmuMath Matrix: Respective indices in each Matrix will be XORed. </para>
	/// <para> If Rhs_ is none of the above: All index operations will use the rhs_ directly. </para>
	/// </summary>
	/// <param name="lhs_matrix_">: EmuMath Matrix appearing on the left of bitwise-assignment operations.</param>
	/// <param name="rhs_">: Scalar or EmuMath Matrix appearing on the right of the bitwise operation.</param>
	template
	<
		std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_, bool ColumnMajorOrder_,
		class Rhs_, std::size_t LhsNumColumns_, std::size_t LhsNumRows_, typename LhsT_, bool LhsColumnMajor_
	>
	constexpr inline void matrix_bitwise_xor_assign_range(EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>& lhs_matrix_, Rhs_&& rhs_)
	{
		EMU_MATH_MATRIX_MUTATE_INVOKE_ONLY_TEMPLATE(EmuCore::do_bitwise_xor_assign, BeginColumn_, EndColumn_, BeginRow_, EndRow_, ColumnMajorOrder_)
		(
			lhs_matrix_,
			std::forward<Rhs_>(rhs_)
		);
	}

	template
	<
		std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_,
		class Rhs_, std::size_t LhsNumColumns_, std::size_t LhsNumRows_, typename LhsT_, bool LhsColumnMajor_
	>
	constexpr inline void matrix_bitwise_xor_assign_range(EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>& lhs_matrix_, Rhs_&& rhs_)
	{
		EMU_MATH_MATRIX_MUTATE_INVOKE_ONLY_TEMPLATE(EmuCore::do_bitwise_xor_assign, BeginColumn_, EndColumn_, BeginRow_, EndRow_, LhsColumnMajor_)
		(
			lhs_matrix_,
			std::forward<Rhs_>(rhs_)
		);
	}
#pragma endregion

#pragma region LEFT_SHIFT_ASSIGN
	/// <summary>
	/// <para> Performs a bitwise left-shift-assign on the passed lhs_matrix_ with the provided rhs_ argument. </para>
	/// <para> If Rhs_ is an EmuMath Matrix: Respective indices in each Matrix will be used for shifts. </para>
	/// <para> If Rhs_ is none of the above: All index operations will use the rhs_ directly. </para>
	/// </summary>
	/// <param name="lhs_matrix_">: EmuMath Matrix appearing on the left of shift-assignment operations.</param>
	/// <param name="rhs_">: Scalar or EmuMath Matrix appearing on the right of the shift operation.</param>
	template<bool ColumnMajorOrder_, class Rhs_, std::size_t LhsNumColumns_, std::size_t LhsNumRows_, typename LhsT_, bool LhsColumnMajor_>
	constexpr inline void matrix_shift_left_assign(EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>& lhs_matrix_, Rhs_&& rhs_)
	{
		EMU_MATH_MATRIX_MUTATE_INVOKE_ONLY_TEMPLATE(EmuCore::do_left_shift, 0, LhsNumColumns_, 0, LhsNumRows_, ColumnMajorOrder_)
		(
			lhs_matrix_,
			std::forward<Rhs_>(rhs_)
		);
	}

	template<class Rhs_, std::size_t LhsNumColumns_, std::size_t LhsNumRows_, typename LhsT_, bool LhsColumnMajor_>
	constexpr inline void matrix_shift_left_assign(EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>& lhs_matrix_, Rhs_&& rhs_)
	{
		EMU_MATH_MATRIX_MUTATE_INVOKE_ONLY_TEMPLATE(EmuCore::do_left_shift, 0, LhsNumColumns_, 0, LhsNumRows_, LhsColumnMajor_)
		(
			lhs_matrix_,
			std::forward<Rhs_>(rhs_)
		);
	}
#pragma endregion

#pragma region LEFT_SHIFT_ASSIGN_RANGE
	/// <summary>
	/// <para> Performs a bitwise left-shift-assign on the passed lhs_matrix_ with the provided rhs_ argument. </para>
	/// <para> Operations will only be performed for indices within the provided range. </para>
	/// <para> If Rhs_ is an EmuMath Matrix: Respective indices in each Matrix will be used for shifts. </para>
	/// <para> If Rhs_ is none of the above: All index operations will use the rhs_ directly. </para>
	/// </summary>
	/// <param name="lhs_matrix_">: EmuMath Matrix appearing on the left of shift-assignment operations.</param>
	/// <param name="rhs_">: Scalar or EmuMath Matrix appearing on the right of the shift operation.</param>
	template
	<
		std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_, bool ColumnMajorOrder_,
		class Rhs_, std::size_t LhsNumColumns_, std::size_t LhsNumRows_, typename LhsT_, bool LhsColumnMajor_
	>
	constexpr inline void matrix_shift_left_assign_range(EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>& lhs_matrix_, Rhs_&& rhs_)
	{
		EMU_MATH_MATRIX_MUTATE_INVOKE_ONLY_TEMPLATE(EmuCore::do_left_shift, BeginColumn_, EndColumn_, BeginRow_, EndRow_, ColumnMajorOrder_)
		(
			lhs_matrix_,
			std::forward<Rhs_>(rhs_)
		);
	}

	template
	<
		std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_,
		class Rhs_, std::size_t LhsNumColumns_, std::size_t LhsNumRows_, typename LhsT_, bool LhsColumnMajor_
	>
	constexpr inline void matrix_shift_left_assign_range(EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>& lhs_matrix_, Rhs_&& rhs_)
	{
		EMU_MATH_MATRIX_MUTATE_INVOKE_ONLY_TEMPLATE(EmuCore::do_left_shift, BeginColumn_, EndColumn_, BeginRow_, EndRow_, LhsColumnMajor_)
		(
			lhs_matrix_,
			std::forward<Rhs_>(rhs_)
		);
	}
#pragma endregion

#pragma region RIGHT_SHIFT_ASSIGN
	/// <summary>
	/// <para> Performs a bitwise right-shift-assign on the passed lhs_matrix_ with the provided rhs_ argument. </para>
	/// <para> If Rhs_ is an EmuMath Matrix: Respective indices in each Matrix will be used for shifts. </para>
	/// <para> If Rhs_ is none of the above: All index operations will use the rhs_ directly. </para>
	/// </summary>
	/// <param name="lhs_matrix_">: EmuMath Matrix appearing on the left of shift-assignment operations.</param>
	/// <param name="rhs_">: Scalar or EmuMath Matrix appearing on the right of the shift operation.</param>
	template<bool ColumnMajorOrder_, class Rhs_, std::size_t LhsNumColumns_, std::size_t LhsNumRows_, typename LhsT_, bool LhsColumnMajor_>
	constexpr inline void matrix_shift_right_assign(EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>& lhs_matrix_, Rhs_&& rhs_)
	{
		EMU_MATH_MATRIX_MUTATE_INVOKE_ONLY_TEMPLATE(EmuCore::do_right_shift, 0, LhsNumColumns_, 0, LhsNumRows_, ColumnMajorOrder_)
		(
			lhs_matrix_,
			std::forward<Rhs_>(rhs_)
		);
	}

	template<class Rhs_, std::size_t LhsNumColumns_, std::size_t LhsNumRows_, typename LhsT_, bool LhsColumnMajor_>
	constexpr inline void matrix_shift_right_assign(EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>& lhs_matrix_, Rhs_&& rhs_)
	{
		EMU_MATH_MATRIX_MUTATE_INVOKE_ONLY_TEMPLATE(EmuCore::do_right_shift, 0, LhsNumColumns_, 0, LhsNumRows_, LhsColumnMajor_)
		(
			lhs_matrix_,
			std::forward<Rhs_>(rhs_)
		);
	}
#pragma endregion

#pragma region RIGHT_SHIFT_ASSIGN_RANGE
	/// <summary>
	/// <para> Performs a bitwise right-shift-assign on the passed lhs_matrix_ with the provided rhs_ argument. </para>
	/// <para> Operations will only be performed for indices within the provided range. </para>
	/// <para> If Rhs_ is an EmuMath Matrix: Respective indices in each Matrix will be used for shifts. </para>
	/// <para> If Rhs_ is none of the above: All index operations will use the rhs_ directly. </para>
	/// </summary>
	/// <param name="lhs_matrix_">: EmuMath Matrix appearing on the left of shift-assignment operations.</param>
	/// <param name="rhs_">: Scalar or EmuMath Matrix appearing on the right of the shift operation.</param>
	template
	<
		std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_, bool ColumnMajorOrder_,
		class Rhs_, std::size_t LhsNumColumns_, std::size_t LhsNumRows_, typename LhsT_, bool LhsColumnMajor_
	>
	constexpr inline void matrix_shift_right_assign_range(EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>& lhs_matrix_, Rhs_&& rhs_)
	{
		EMU_MATH_MATRIX_MUTATE_INVOKE_ONLY_TEMPLATE(EmuCore::do_right_shift, BeginColumn_, EndColumn_, BeginRow_, EndRow_, ColumnMajorOrder_)
		(
			lhs_matrix_,
			std::forward<Rhs_>(rhs_)
		);
	}

	template
	<
		std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_,
		class Rhs_, std::size_t LhsNumColumns_, std::size_t LhsNumRows_, typename LhsT_, bool LhsColumnMajor_
	>
	constexpr inline void matrix_shift_right_assign_range(EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>& lhs_matrix_, Rhs_&& rhs_)
	{
		EMU_MATH_MATRIX_MUTATE_INVOKE_ONLY_TEMPLATE(EmuCore::do_right_shift, BeginColumn_, EndColumn_, BeginRow_, EndRow_, LhsColumnMajor_)
		(
			lhs_matrix_,
			std::forward<Rhs_>(rhs_)
		);
	}
#pragma endregion
}
#endif