#ifndef EMU_MATH_MATRIX_BASIC_ARITHMETIC_ASSIGN_H_INC_
#define EMU_MATH_MATRIX_BASIC_ARITHMETIC_ASSIGN_H_INC_ 1

#include "_common_matrix_helper_includes.h"

// CONTAINS:
// --- add_assign
// --- add_assign_range
// --- subtract_assign
// --- subtract_assign_range
// --- multiply_basic_assign
// --- multiply_basic_assign_range
// --- divide_assign
// --- divide_assign_range
// --- mod_assign
// --- mod_assign_range
// --- multiply_assign
// --- square_assign

namespace EmuMath::Helpers
{
#pragma region ADD_ASSIGN
	/// <summary>
	/// <para> Performs an arithmetic add-assign (e.g. operator+=) on the passed lhs_matrix_ with the provided rhs_ argument. </para>
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
	/// <para> Performs an arithmetic add-assign (e.g. operator+=) on the passed lhs_matrix_ with the provided rhs_ argument. </para>
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

#pragma region SUBTRACT_ASSIGN
	/// <summary>
	/// <para> Performs an arithmetic subtract-assign (e.g. operator-=) on the passed lhs_matrix_ with the provided rhs_ argument. </para>
	/// <para> If Rhs_ is an EmuMath Matrix: Respective indices in each Matrix will be subtracted. </para>
	/// <para> If Rhs_ is none of the above: All index subtractions will use the rhs_ directly. </para>
	/// </summary>
	/// <param name="lhs_matrix_">: EmuMath Matrix appearing on the left of subtract-assignment.</param>
	/// <param name="rhs_">: Scalar or EmuMath Matrix appearing on the right of subtraction.</param>
	template<bool ColumnMajorOrder_, class Rhs_, std::size_t LhsNumColumns_, std::size_t LhsNumRows_, typename LhsT_, bool LhsColumnMajor_>
	constexpr inline void matrix_subtract_assign(EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>& lhs_matrix_, Rhs_&& rhs_)
	{
		EMU_MATH_MATRIX_MUTATE_INVOKE_ONLY_TEMPLATE(EmuCore::do_subtract_assign, 0, LhsNumColumns_, 0, LhsNumRows_, ColumnMajorOrder_)
		(
			lhs_matrix_,
			std::forward<Rhs_>(rhs_)
		);
	}

	template<class Rhs_, std::size_t LhsNumColumns_, std::size_t LhsNumRows_, typename LhsT_, bool LhsColumnMajor_>
	constexpr inline void matrix_subtract_assign(EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>& lhs_matrix_, Rhs_&& rhs_)
	{
		EMU_MATH_MATRIX_MUTATE_INVOKE_ONLY_TEMPLATE(EmuCore::do_subtract_assign, 0, LhsNumColumns_, 0, LhsNumRows_, LhsColumnMajor_)
		(
			lhs_matrix_,
			std::forward<Rhs_>(rhs_)
		);
	}
#pragma endregion

#pragma region SUBTRACT_ASSIGN_RANGE
	/// <summary>
	/// <para> Performs an arithmetic subtract-assign (e.g. operator-=) on the passed lhs_matrix_ with the provided rhs_ argument. </para>
	/// <para> Operations will only be performed for indices within the provided range. </para>
	/// <para> If Rhs_ is an EmuMath Matrix: Respective indices in each Matrix will be subtracted. </para>
	/// <para> If Rhs_ is none of the above: All index subtractions will use the rhs_ directly. </para>
	/// </summary>
	/// <param name="lhs_matrix_">: EmuMath Matrix appearing on the left of subtract-assignment.</param>
	/// <param name="rhs_">: Scalar or EmuMath Matrix appearing on the right of subtraction.</param>
	template
	<
		std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_, bool ColumnMajorOrder_,
		class Rhs_, std::size_t LhsNumColumns_, std::size_t LhsNumRows_, typename LhsT_, bool LhsColumnMajor_
	>
	constexpr inline void matrix_subtract_assign_range(EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>& lhs_matrix_, Rhs_&& rhs_)
	{
		EMU_MATH_MATRIX_MUTATE_INVOKE_ONLY_TEMPLATE(EmuCore::do_subtract_assign, BeginColumn_, EndColumn_, BeginRow_, EndRow_, ColumnMajorOrder_)
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
	constexpr inline void matrix_subtract_assign_range(EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>& lhs_matrix_, Rhs_&& rhs_)
	{
		EMU_MATH_MATRIX_MUTATE_INVOKE_ONLY_TEMPLATE(EmuCore::do_subtract_assign, BeginColumn_, EndColumn_, BeginRow_, EndRow_, LhsColumnMajor_)
		(
			lhs_matrix_,
			std::forward<Rhs_>(rhs_)
		);
	}
#pragma endregion

#pragma region MULTIPLY_BASIC_ASSIGN
	/// <summary>
	/// <para> Performs an arithmetic multiply-assign (e.g. operator*=) on the passed lhs_matrix_ with the provided rhs_ argument. </para>
	/// <para>
	///		This is a basic, non-standard Matrix multiplication. 
	///		If Rhs_ is a Matrix it will not perform a standard Matrix multiplication using dot products of columns and rows. 
	///		For a standard Matrix multiplication, use `matrix_multiply_assign` instead.
	/// </para>
	/// <para> If Rhs_ is an EmuMath Matrix: Respective indices in each Matrix will be multiplied. </para>
	/// <para> If Rhs_ is none of the above: All index multiplications will use the rhs_ directly. </para>
	/// </summary>
	/// <param name="lhs_matrix_">: EmuMath Matrix appearing on the left of multiply-assignment.</param>
	/// <param name="rhs_">: Scalar or EmuMath Matrix appearing on the right of multiplication.</param>
	template<bool ColumnMajorOrder_, class Rhs_, std::size_t LhsNumColumns_, std::size_t LhsNumRows_, typename LhsT_, bool LhsColumnMajor_>
	constexpr inline void matrix_multiply_basic_assign(EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>& lhs_matrix_, Rhs_&& rhs_)
	{
		EMU_MATH_MATRIX_MUTATE_INVOKE_ONLY_TEMPLATE(EmuCore::do_multiply_assign, 0, LhsNumColumns_, 0, LhsNumRows_, ColumnMajorOrder_)
		(
			lhs_matrix_,
			std::forward<Rhs_>(rhs_)
		);
	}

	template<class Rhs_, std::size_t LhsNumColumns_, std::size_t LhsNumRows_, typename LhsT_, bool LhsColumnMajor_>
	constexpr inline void matrix_multiply_basic_assign(EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>& lhs_matrix_, Rhs_&& rhs_)
	{
		EMU_MATH_MATRIX_MUTATE_INVOKE_ONLY_TEMPLATE(EmuCore::do_multiply_assign, 0, LhsNumColumns_, 0, LhsNumRows_, LhsColumnMajor_)
		(
			lhs_matrix_,
			std::forward<Rhs_>(rhs_)
		);
	}
#pragma endregion

#pragma region MULTIPLY_BASIC_ASSIGN_RANGE
	/// <summary>
	/// <para> Performs an arithmetic multiply-assign (e.g. operator*=) on the passed lhs_matrix_ with the provided rhs_ argument. </para>
	/// <para>
	///		This is a basic, non-standard Matrix multiplication. 
	///		If Rhs_ is a Matrix it will not perform a standard Matrix multiplication using dot products of columns and rows. 
	///		For a standard Matrix multiplication, use `matrix_multiply` instead. 
	///		Range-based standard variants as this function is used are not available.
	/// </para>
	/// <para> Operations will only be performed for indices within the provided range. </para>
	/// <para> If Rhs_ is an EmuMath Matrix: Respective indices in each Matrix will be multiplied. </para>
	/// <para> If Rhs_ is none of the above: All index multiplications will use the rhs_ directly. </para>
	/// </summary>
	/// <param name="lhs_matrix_">: EmuMath Matrix appearing on the left of multiply-assignment.</param>
	/// <param name="rhs_">: Scalar or EmuMath Matrix appearing on the right of multiplication.</param>
	template
	<
		std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_, bool ColumnMajorOrder_,
		class Rhs_, std::size_t LhsNumColumns_, std::size_t LhsNumRows_, typename LhsT_, bool LhsColumnMajor_
	>
	constexpr inline void matrix_multiply_basic_assign_range(EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>& lhs_matrix_, Rhs_&& rhs_)
	{
		EMU_MATH_MATRIX_MUTATE_INVOKE_ONLY_TEMPLATE(EmuCore::do_multiply_assign, BeginColumn_, EndColumn_, BeginRow_, EndRow_, ColumnMajorOrder_)
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
	constexpr inline void matrix_multiply_basic_assign_range(EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>& lhs_matrix_, Rhs_&& rhs_)
	{
		EMU_MATH_MATRIX_MUTATE_INVOKE_ONLY_TEMPLATE(EmuCore::do_multiply_assign, BeginColumn_, EndColumn_, BeginRow_, EndRow_, LhsColumnMajor_)
		(
			lhs_matrix_,
			std::forward<Rhs_>(rhs_)
		);
	}
#pragma endregion

#pragma region DIVIDE_ASSIGN
	/// <summary>
	/// <para> Performs an arithmetic divide-assign (e.g. operator/=) on the passed lhs_matrix_ with the provided rhs_ argument. </para>
	/// <para>
	///		This is a basic, non-standard Matrix division. As a standard division is mathemtically undefined, there is no alternative. 
	///		To create an effect similar to what could be considered standard division when rhs_ is a Matrix, consider multiplying lhs_matrix_ by the inverse of rhs_.
	/// </para>
	/// <para> If Rhs_ is an EmuMath Matrix: Respective indices in each Matrix will be divided. </para>
	/// <para> If Rhs_ is none of the above: All index divisions will use the rhs_ directly. </para>
	/// </summary>
	/// <param name="lhs_matrix_">: EmuMath Matrix appearing on the left of divide-assignment.</param>
	/// <param name="rhs_">: Scalar or EmuMath Matrix appearing on the right of division.</param>
	template<bool ColumnMajorOrder_, class Rhs_, std::size_t LhsNumColumns_, std::size_t LhsNumRows_, typename LhsT_, bool LhsColumnMajor_>
	constexpr inline void matrix_divide_assign(EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>& lhs_matrix_, Rhs_&& rhs_)
	{
		EMU_MATH_MATRIX_MUTATE_INVOKE_ONLY_TEMPLATE(EmuCore::do_divide_assign, 0, LhsNumColumns_, 0, LhsNumRows_, ColumnMajorOrder_)
		(
			lhs_matrix_,
			std::forward<Rhs_>(rhs_)
		);
	}

	template<class Rhs_, std::size_t LhsNumColumns_, std::size_t LhsNumRows_, typename LhsT_, bool LhsColumnMajor_>
	constexpr inline void matrix_divide_assign(EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>& lhs_matrix_, Rhs_&& rhs_)
	{
		EMU_MATH_MATRIX_MUTATE_INVOKE_ONLY_TEMPLATE(EmuCore::do_divide_assign, 0, LhsNumColumns_, 0, LhsNumRows_, LhsColumnMajor_)
		(
			lhs_matrix_,
			std::forward<Rhs_>(rhs_)
		);
	}
#pragma endregion

#pragma region DIVIDE_ASSIGN_RANGE
	/// <summary>
	/// <para> Performs an arithmetic divide-assign (e.g. operator/=) on the passed lhs_matrix_ with the provided rhs_ argument. </para>
	/// <para>
	///		This is a basic, non-standard Matrix division. As a standard division is mathemtically undefined, there is no alternative. 
	///		To create an effect similar to what could be considered standard division when rhs_ is a Matrix, consider multiplying lhs_matrix_ by the inverse of rhs_.
	/// </para>
	/// <para> Operations will only be performed for indices within the provided range. </para>
	/// <para> If Rhs_ is an EmuMath Matrix: Respective indices in each Matrix will be divided. </para>
	/// <para> If Rhs_ is none of the above: All index divisions will use the rhs_ directly. </para>
	/// </summary>
	/// <param name="lhs_matrix_">: EmuMath Matrix appearing on the left of divide-assignment.</param>
	/// <param name="rhs_">: Scalar or EmuMath Matrix appearing on the right of division.</param>
	template
	<
		std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_, bool ColumnMajorOrder_,
		class Rhs_, std::size_t LhsNumColumns_, std::size_t LhsNumRows_, typename LhsT_, bool LhsColumnMajor_
	>
	constexpr inline void matrix_divide_assign_range(EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>& lhs_matrix_, Rhs_&& rhs_)
	{
		EMU_MATH_MATRIX_MUTATE_INVOKE_ONLY_TEMPLATE(EmuCore::do_divide_assign, BeginColumn_, EndColumn_, BeginRow_, EndRow_, ColumnMajorOrder_)
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
	constexpr inline void matrix_divide_assign_range(EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>& lhs_matrix_, Rhs_&& rhs_)
	{
		EMU_MATH_MATRIX_MUTATE_INVOKE_ONLY_TEMPLATE(EmuCore::do_divide_assign, BeginColumn_, EndColumn_, BeginRow_, EndRow_, LhsColumnMajor_)
		(
			lhs_matrix_,
			std::forward<Rhs_>(rhs_)
		);
	}
#pragma endregion

#pragma region MOD_ASSIGN
	/// <summary>
	/// <para> Performs an arithmetic mod-assign (e.g. operator%=) on the passed lhs_matrix_ with the provided rhs_ argument. </para>
	/// <para> This is a basic, non-standard Matrix modulo-division. As a standard modulo-division is mathemtically undefined, there is no alternative. </para>
	/// <para> If Rhs_ is an EmuMath Matrix: Respective indices in each Matrix will be divided. </para>
	/// <para> If Rhs_ is none of the above: All index divisions will use the rhs_ directly. </para>
	/// </summary>
	/// <param name="lhs_matrix_">: EmuMath Matrix appearing on the left of mod-assignment.</param>
	/// <param name="rhs_">: Scalar or EmuMath Matrix appearing on the right of modulo-division.</param>
	template<bool ColumnMajorOrder_, class Rhs_, std::size_t LhsNumColumns_, std::size_t LhsNumRows_, typename LhsT_, bool LhsColumnMajor_>
	constexpr inline void matrix_mod_assign(EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>& lhs_matrix_, Rhs_&& rhs_)
	{
		EMU_MATH_MATRIX_MUTATE_INVOKE_ONLY_TEMPLATE(EmuCore::do_mod_assign, 0, LhsNumColumns_, 0, LhsNumRows_, ColumnMajorOrder_)
		(
			lhs_matrix_,
			std::forward<Rhs_>(rhs_)
		);
	}

	template<class Rhs_, std::size_t LhsNumColumns_, std::size_t LhsNumRows_, typename LhsT_, bool LhsColumnMajor_>
	constexpr inline void matrix_mod_assign(EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>& lhs_matrix_, Rhs_&& rhs_)
	{
		EMU_MATH_MATRIX_MUTATE_INVOKE_ONLY_TEMPLATE(EmuCore::do_mod_assign, 0, LhsNumColumns_, 0, LhsNumRows_, LhsColumnMajor_)
		(
			lhs_matrix_,
			std::forward<Rhs_>(rhs_)
		);
	}
#pragma endregion

#pragma region MOD_ASSIGN_RANGE
	/// <summary>
	/// <para> Performs an arithmetic mod-assign (e.g. operator%=) on the passed lhs_matrix_ with the provided rhs_ argument. </para>
	/// <para> This is a basic, non-standard Matrix modulo-division. As a standard modulo-division is mathemtically undefined, there is no alternative. </para>
	/// <para> Operations will only be performed for indices within the provided range. </para>
	/// <para> If Rhs_ is an EmuMath Matrix: Respective indices in each Matrix will be divided. </para>
	/// <para> If Rhs_ is none of the above: All index divisions will use the rhs_ directly. </para>
	/// </summary>
	/// <param name="lhs_matrix_">: EmuMath Matrix appearing on the left of mod-assignment.</param>
	/// <param name="rhs_">: Scalar or EmuMath Matrix appearing on the right of modulo-division.</param>
	template
	<
		std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_, bool ColumnMajorOrder_,
		class Rhs_, std::size_t LhsNumColumns_, std::size_t LhsNumRows_, typename LhsT_, bool LhsColumnMajor_
	>
	constexpr inline void matrix_mod_assign_range(EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>& lhs_matrix_, Rhs_&& rhs_)
	{
		EMU_MATH_MATRIX_MUTATE_INVOKE_ONLY_TEMPLATE(EmuCore::do_mod_assign, BeginColumn_, EndColumn_, BeginRow_, EndRow_, ColumnMajorOrder_)
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
	constexpr inline void matrix_mod_assign_range(EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>& lhs_matrix_, Rhs_&& rhs_)
	{
		EMU_MATH_MATRIX_MUTATE_INVOKE_ONLY_TEMPLATE(EmuCore::do_mod_assign, BeginColumn_, EndColumn_, BeginRow_, EndRow_, LhsColumnMajor_)
		(
			lhs_matrix_,
			std::forward<Rhs_>(rhs_)
		);
	}
#pragma endregion

#pragma region MULTIPLY_ASSIGN
	template<std::size_t LhsNumColumns_, std::size_t LhsNumRows_, typename LhsT_, bool LhsColumnMajor_, std::size_t RhsSize_, typename RhsT_>
	[[nodiscard]] constexpr inline bool is_valid_matrix_multiply_assign_rhs_vector()
	{
		return _matrix_underlying::_matrix_std_multiply_assign_mat_vector_is_valid<RhsSize_, RhsT_, LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_, false>();
	}

	template<std::size_t LhsNumColumns_, std::size_t LhsNumRows_, typename LhsT_, bool LhsColumnMajor_, std::size_t RhsSize_, typename RhsT_>
	[[nodiscard]] constexpr inline bool assert_valid_matrix_multiply_assign_rhs_vector()
	{
		return _matrix_underlying::_matrix_std_multiply_assign_mat_vector_is_valid<RhsSize_, RhsT_, LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_, true>();
	}

	/// <summary>
	/// <para> Performs an arithmetic multiply-assign (e.g. operator*=) on the passed lhs_matrix_ with the provided rhs_ argument. </para>
	/// <para> 
	///		This function will only be available for rhs-arguments which are NOT specialised for standard multiplication 
	///		(unlike Matrices and Vectors, which are specialised). 
	/// </para>
	/// </summary>
	/// <param name="lhs_matrix_">: EmuMath Matrix appearing on the left of multiply-assignment.</param>
	/// <param name="rhs_">: Unspecialised item appearing on the right of Matrix multiplication.</param>
	template
	<
		bool ColumnMajorOrder_, class Rhs_, std::size_t LhsNumColumns_, std::size_t LhsNumRows_, typename LhsT_, bool LhsColumnMajor_,
		typename = std::enable_if_t<!EmuMath::TMP::is_specialised_matrix_multiply_arg<Rhs_>()>
	>
	constexpr inline void matrix_multiply_assign(EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>& lhs_matrix_, Rhs_&& rhs_)
	{
		EMU_MATH_MATRIX_MUTATE_INVOKE_ONLY_TEMPLATE(EmuCore::do_multiply_assign, 0, LhsNumColumns_, 0, LhsNumRows_, ColumnMajorOrder_)
		(
			lhs_matrix_,
			std::forward<Rhs_>(rhs_)
		);
	}

	template
	<
		class Rhs_, std::size_t LhsNumColumns_, std::size_t LhsNumRows_, typename LhsT_, bool LhsColumnMajor_,
		typename = std::enable_if_t<!EmuMath::TMP::is_specialised_matrix_multiply_arg<Rhs_>()>
	>
	constexpr inline void matrix_multiply_assign(EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>& lhs_matrix_, Rhs_&& rhs_)
	{
		EMU_MATH_MATRIX_MUTATE_INVOKE_ONLY_TEMPLATE(EmuCore::do_multiply_assign, 0, LhsNumColumns_, 0, LhsNumRows_, LhsColumnMajor_)
		(
			lhs_matrix_,
			std::forward<Rhs_>(rhs_)
		);
	}

	/// <summary>
	/// <para> Interprets the left-hand Vector as a Matrix with a single row of the Vector's size and multiplies it with the right-hand Matrix. </para>
	/// <para> The left-hand Vector must have a size equal to the Matrix's number of columns (or its columns - 1, where the missing index is an implicit 1). </para>
	/// </summary>
	/// <param name="lhs_vector_">EmuMath Vector to interpret as a Row Matrix on the left-hand side of multiplication.</param>
	/// <param name="rhs_matrix_">EmuMath Matrix appearing on the right-hand side of multiplication.</param>
	template<EmuMath::TMP::EmuMatrix Matrix_, std::size_t LhsSize_, typename LhsT_>
	[[nodiscard]] constexpr inline void matrix_multiply_assign
	(
		EmuMath::Vector<LhsSize_, LhsT_>& lhs_vector_,
		Matrix_&& rhs_matrix_
	)
	{
		_matrix_underlying::_matrix_std_multiply_assign_vector_mat(lhs_vector_, std::forward<Matrix_>(rhs_matrix_));
	}

	/// <summary>
	/// <para> Performs a multiply-assign operation (e.g. operator*=) between the passed EmuMath Matrix and EmuMath Vector. </para>
	/// <para> Unlike most arithmetic-assign operations, this will assign to the right-hand operand, as the result will be a Vector of equal size instead of a Matrix. </para>
	/// <para> If needed, a copy of the provided Vector will be formed automatically to prevent invalid results developing from its assignment. </para>
	/// <para> The passed Vector will be treated as a single-column Matrix, and must meet constraint A or B: </para>
	/// <para> A: The Vector's size is equal to the number of rows stored in the left-hand Matrix. </para>
	/// <para> B: The Vector's size + 1 is equal to the number of rows stored in the left-hand Matrix. In this case, the non-contained coordinate will be treated as 1. </para>
	/// <para> NOTE: ColumnMajorOrder_ is not used by this function, and is only present to allow consistency for use in templates. </para>
	/// </summary>
	/// <param name="lhs_matrix_">: EmuMath Matrix to multiply the passed Vector via. This will not be modified, and as such const-qualified Matrices are valid. </param>
	/// <param name="rhs_vector_">: EmuMath Vector to multiply with the passed Matrix, and to output results to. This may not be const-qualified due to use for output.</param>
	template
	<
		bool ColumnMajorOrder_, std::size_t RhsSize_, typename RhsT_, std::size_t LhsNumColumns_, std::size_t LhsNumRows_, typename LhsT_, bool LhsColumnMajor_
	>
	constexpr inline void matrix_multiply_assign
	(
		const EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>& lhs_matrix_,
		EmuMath::Vector<RhsSize_, RhsT_>& rhs_vector_
	)
	{
		_matrix_underlying::_matrix_std_multiply_assign_mat_vector(lhs_matrix_, rhs_vector_);
	}

	template
	<
		typename RhsT_, std::size_t RhsSize_, std::size_t LhsNumColumns_, std::size_t LhsNumRows_, typename LhsT_, bool LhsColumnMajor_
	>
	constexpr inline void matrix_multiply_assign
	(
		const EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>& lhs_matrix_,
		EmuMath::Vector<RhsSize_, RhsT_>& rhs_vector_
	)
	{
		_matrix_underlying::_matrix_std_multiply_assign_mat_vector(lhs_matrix_, rhs_vector_);
	}

	/// <summary>
	/// <para> Performs a multiply-assign operation (e.g. operator*=) between the two passed EmuMath Matrices. </para>
	/// <para> A copy of the provided lhs_matrix_ will be formed automatically to prevent invalid results developing from its assignment. </para>
	/// </summary>
	/// <param name="lhs_matrix_">: EmuMath Matrix to assign to, and appearing on the left of multiplication.</param>
	/// <param name="rhs_matrix_">: EmuMath Matrix appearing on the right of multiplication.</param>
	template
	<
		bool ColumnMajorOrder_, std::size_t RhsNumColumns_, std::size_t RhsNumRows_, typename RhsT_, bool RhsColumnMajor_,
		std::size_t LhsNumColumns_, std::size_t LhsNumRows_, typename LhsT_, bool LhsColumnMajor_
	>
	constexpr inline void matrix_multiply_assign
	(
		EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>& lhs_matrix_,
		const EmuMath::Matrix<RhsNumColumns_, RhsNumRows_, RhsT_, RhsColumnMajor_>& rhs_matrix_
	)
	{
		_matrix_underlying::_matrix_std_multiply_assign_mat_mat<ColumnMajorOrder_>(lhs_matrix_, rhs_matrix_);
	}

	template
	<
		typename RhsT_, std::size_t RhsNumColumns_, std::size_t RhsNumRows_, bool RhsColumnMajor_,
		typename LhsT_, std::size_t LhsNumColumns_, std::size_t LhsNumRows_, bool LhsColumnMajor_
	>
	constexpr inline void matrix_multiply_assign
	(
		EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>& lhs_matrix_,
		const EmuMath::Matrix<RhsNumColumns_, RhsNumRows_, RhsT_, RhsColumnMajor_>& rhs_matrix_
	)
	{
		_matrix_underlying::_matrix_std_multiply_assign_mat_mat<LhsColumnMajor_>(lhs_matrix_, rhs_matrix_);
	}
#pragma endregion

#pragma region MISC_ARITHMETIC_ASSIGNS
	/// <summary>
	/// <para> Alternative to matrix_multiply_assign to easily multiply an EmuMath Matrix by itself. Usual rules of matrix_multiply_assign apply. </para>
	/// <para> Additionally, it must be possible for a copy of the provided matrix_ to be created, using its value_type_uq as a type argument. </para>
	/// </summary>
	/// <param name="matrix_">: EmuMath Matrix to multiply by itself and assign the results to.</param>
	template<bool ColumnMajorOrder_, std::size_t NumColumns_, std::size_t NumRows_, typename T_, bool ColumnMajor_>
	constexpr inline void matrix_square_assign(EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>& matrix_)
	{
		using in_matrix = EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>;
		using mat_copy_out_major = EmuMath::Matrix<NumColumns_, NumRows_, typename in_matrix::value_type_uq, ColumnMajorOrder_>;
		if constexpr (std::is_constructible_v<mat_copy_out_major, in_matrix&>)
		{
			mat_copy_out_major matrix_copy_(matrix_);
			return _matrix_underlying::_matrix_std_multiply_assign_mat_mat<ColumnMajorOrder_>(matrix_, matrix_copy_, matrix_copy_);
		}
		else
		{
			using mat_copy_matching_major = EmuMath::Matrix<NumColumns_, NumRows_, typename in_matrix::value_type_uq, ColumnMajor_>;
			if constexpr (std::is_constructible_v<mat_copy_matching_major, in_matrix&>)
			{
				mat_copy_matching_major matrix_copy_(matrix_);
				return _matrix_underlying::_matrix_std_multiply_assign_mat_mat<ColumnMajorOrder_>(matrix_, matrix_copy_, matrix_copy_);
			}
			else
			{
				static_assert
				(
					EmuCore::TMP::get_false<in_matrix>(),
					"Attempted to assign the square of an EmuMath Matrix to itself, but a copy could not successfully be created to allow correct results to be assigned."
				);
			}
		}
	}
#pragma endregion
}

#endif
