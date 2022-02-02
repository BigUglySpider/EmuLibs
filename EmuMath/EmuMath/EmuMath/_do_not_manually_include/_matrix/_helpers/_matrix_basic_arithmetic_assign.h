#ifndef EMU_MATH_MATRIX_BASIC_ARITHMETIC_ASSIGN_H_INC_
#define EMU_MATH_MATRIX_BASIC_ARITHMETIC_ASSIGN_H_INC_ 1

#include "_common_matrix_helper_includes.h"

// CONTAINS:
// --- add_assign
// --- add_assign_range

namespace EmuMath::Helpers
{
#pragma region ADD_ASSIGN
	/// <summary>
	/// <para> Performs an arithmetic add assign (e.g. operator+=) on the passed lhs_matrix_ with the provided rhs_ argument. </para>
	/// <para> If Rhs_ is an EmuMath Matrix: Respective indices in each Matrix will be added. </para>
	/// <para> If Rhs_ is none of the above: All index additions will use the rhs_ directly. </para>
	/// </summary>
	/// <param name="lhs_matrix_">: EmuMath Matrix appearing on the left of add-assignment.</param>
	/// <param name="rhs_">: Scalar or EmuMath Matrix appearing on the right of addition.</param>
	template<bool ColumnMajorOrder_, class Rhs_, std::size_t LhsNumColumns_, std::size_t LhsNumRows_, typename LhsT_, bool LhsColumnMajor_>
	constexpr inline void matrix_add_assign(EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>& lhs_matrix_, Rhs_&& rhs_)
	{
		EMU_MATH_MATRIX_MUTATE_INVOKE_ONLY_TEMPLATE(EmuCore::do_add_assign, 0, LhsNumColumns_, 0, LhsNumRows_, ColumnMajorOrder_)
		(
			lhs_matrix_,
			std::forward<Rhs_>(rhs_)
		);
	}

	template<class Rhs_, std::size_t LhsNumColumns_, std::size_t LhsNumRows_, typename LhsT_, bool LhsColumnMajor_>
	constexpr inline void matrix_add_assign(EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>& lhs_matrix_, Rhs_&& rhs_)
	{
		EMU_MATH_MATRIX_MUTATE_INVOKE_ONLY_TEMPLATE(EmuCore::do_add_assign, 0, LhsNumColumns_, 0, LhsNumRows_, LhsColumnMajor_)
		(
			lhs_matrix_,
			std::forward<Rhs_>(rhs_)
		);
	}
#pragma endregion

#pragma region ADD_ASSIGN_RANGE
	/// <summary>
	/// <para> Performs an arithmetic add assign (e.g. operator+=) on the passed lhs_matrix_ with the provided rhs_ argument. </para>
	/// <para> Operations will only be performed for indices within the provided range. </para>
	/// <para> If Rhs_ is an EmuMath Matrix: Respective indices in each Matrix will be added. </para>
	/// <para> If Rhs_ is none of the above: All index additions will use the rhs_ directly. </para>
	/// </summary>
	/// <param name="lhs_matrix_">: EmuMath Matrix appearing on the left of add-assignment.</param>
	/// <param name="rhs_">: Scalar or EmuMath Matrix appearing on the right of addition.</param>
	template
	<
		std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_, bool ColumnMajorOrder_,
		class Rhs_, std::size_t LhsNumColumns_, std::size_t LhsNumRows_, typename LhsT_, bool LhsColumnMajor_
	>
	constexpr inline void matrix_add_assign_range(EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>& lhs_matrix_, Rhs_&& rhs_)
	{
		EMU_MATH_MATRIX_MUTATE_INVOKE_ONLY_TEMPLATE(EmuCore::do_add_assign, BeginColumn_, EndColumn_, BeginRow_, EndRow_, ColumnMajorOrder_)
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
	constexpr inline void matrix_add_assign_range(EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>& lhs_matrix_, Rhs_&& rhs_)
	{
		EMU_MATH_MATRIX_MUTATE_INVOKE_ONLY_TEMPLATE(EmuCore::do_add_assign, BeginColumn_, EndColumn_, BeginRow_, EndRow_, LhsColumnMajor_)
		(
			lhs_matrix_,
			std::forward<Rhs_>(rhs_)
		);
	}
#pragma endregion
}

#endif
