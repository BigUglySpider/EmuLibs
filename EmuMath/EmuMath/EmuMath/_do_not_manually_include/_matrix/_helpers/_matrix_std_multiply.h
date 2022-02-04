#ifndef EMU_MATH_MATRIX_STD_MULTIPLY_H_INC_
#define EMU_MATH_MATRIX_STD_MULTIPLY_H_INC_ 1

#include "_common_matrix_helper_includes.h"

// CONTAINS:
// --- multiply (Unspecialised arg)
// --- multiply (Vector arg)
// --- multiply (Matrix arg)

namespace EmuMath::Helpers
{
#pragma region MULTIPLY_WITH_UNSPECIALISED_RHS
	/// <summary>
	/// <para> Outputs an EmuMath Matrix resulting from basic multiplication of the provided lhs_matrix_ with the provided Rhs_ argument. </para>
	/// <para> 
	///		This function will only be available for rhs-arguments which are NOT specialised for standard multiplication 
	///		(unlike Matrices and Vectors, which are specialised). 
	/// </para>
	/// <para> To always perform basic multiplication regardless of argument type, use `matrix_multiply_basic` instead. </para>
	/// </summary>
	/// <param name="lhs_matrix_">: EmuMath Matrix appearing on the left of multiplication.</param>
	/// <param name="rhs_">: Unspecialised argument appearing on the right of multiplication.</param>
	/// <returns>EmuMath Matrix containing the results of basic multiplication in respective indices.</returns>
	template
	<
		class OutT_, bool OutColumnMajor_, std::size_t LhsNumColumns_, std::size_t LhsNumRows_, typename LhsT_, bool LhsColumnMajor_, class Rhs_,
		typename = std::enable_if_t<!EmuMath::TMP::is_specialised_matrix_multiply_arg<Rhs_>()>
	>
	[[nodiscard]] constexpr inline EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, OutT_, OutColumnMajor_> matrix_multiply
	(
		const EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>& lhs_matrix_,
		Rhs_&& rhs_
	)
	{
		return EMU_MATH_MATRIX_MUTATE_TEMPLATE(EmuCore::do_multiply, LhsNumColumns_, LhsNumRows_, OutT_, OutColumnMajor_, 0, LhsNumColumns_, 0, LhsNumRows_)
		(
			lhs_matrix_,
			std::forward<Rhs_>(rhs_)
		);
	}

	template
	<
		bool OutColumnMajor_, std::size_t LhsNumColumns_, std::size_t LhsNumRows_, typename LhsT_, bool LhsColumnMajor_, class Rhs_,
		typename = std::enable_if_t<!EmuMath::TMP::is_specialised_matrix_multiply_arg<Rhs_>()>
	>
	[[nodiscard]] constexpr inline EmuMath::Matrix
	<
		LhsNumColumns_,
		LhsNumRows_,
		typename EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>::value_type_uq,
		OutColumnMajor_
	>
	matrix_multiply(const EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>& lhs_matrix_, Rhs_&& rhs_)
	{
		using lhs_value_uq = typename EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>::value_type_uq;
		return EMU_MATH_MATRIX_MUTATE_TEMPLATE(EmuCore::do_multiply, LhsNumColumns_, LhsNumRows_, lhs_value_uq, OutColumnMajor_, 0, LhsNumColumns_, 0, LhsNumRows_)
		(
			lhs_matrix_,
			std::forward<Rhs_>(rhs_)
		);
	}

	template
	<
		class OutT_, std::size_t LhsNumColumns_, std::size_t LhsNumRows_, typename LhsT_, bool LhsColumnMajor_, class Rhs_,
		typename = std::enable_if_t<!EmuMath::TMP::is_specialised_matrix_multiply_arg<Rhs_>()>
	>
	[[nodiscard]] constexpr inline EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, OutT_, LhsColumnMajor_> matrix_multiply
	(
		const EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>& lhs_matrix_,
		Rhs_&& rhs_
	)
	{
		return EMU_MATH_MATRIX_MUTATE_TEMPLATE(EmuCore::do_multiply, LhsNumColumns_, LhsNumRows_, OutT_, LhsColumnMajor_, 0, LhsNumColumns_, 0, LhsNumRows_)
		(
			lhs_matrix_,
			std::forward<Rhs_>(rhs_)
		);
	}

	template
	<
		std::size_t LhsNumColumns_, std::size_t LhsNumRows_, typename LhsT_, bool LhsColumnMajor_, class Rhs_,
		typename = std::enable_if_t<!EmuMath::TMP::is_specialised_matrix_multiply_arg<Rhs_>()>
	>
	[[nodiscard]] constexpr inline EmuMath::Matrix
	<
		LhsNumColumns_,
		LhsNumRows_,
		typename EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>::value_type_uq,
		LhsColumnMajor_
	>
	matrix_multiply(const EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>& lhs_matrix_, Rhs_&& rhs_)
	{
		using lhs_value_uq = typename EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>::value_type_uq;
		return EMU_MATH_MATRIX_MUTATE_TEMPLATE(EmuCore::do_multiply, LhsNumColumns_, LhsNumRows_, lhs_value_uq, LhsColumnMajor_, 0, LhsNumColumns_, 0, LhsNumRows_)
		(
			lhs_matrix_,
			std::forward<Rhs_>(rhs_)
		);
	}

	template
	<
		class Rhs_, std::size_t LhsNumColumns_, std::size_t LhsNumRows_, typename LhsT_, bool LhsColumnMajor_,
		std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, bool OutColumnMajor_,
		typename = std::enable_if_t<!EmuMath::TMP::is_specialised_matrix_multiply_arg<Rhs_>()>
	>
	constexpr inline void matrix_multiply
	(
		EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>& out_matrix_,
		const EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>& lhs_matrix_,
		Rhs_&& rhs_
	)
	{
		return EMU_MATH_MATRIX_MUTATE_ASSIGN_TEMPLATE(EmuCore::do_multiply, 0, OutNumColumns_, 0, OutNumRows_, 0, 0)
		(
			out_matrix_,
			lhs_matrix_,
			std::forward<Rhs_>(rhs_)
		);
	}
#pragma endregion

#pragma region MULTIPLY_WITH_VECTOR_RHS
	/// <summary>
	/// <para> Outputs an EmuMath Vector resulting from a multiplication with the provided Matrix. The Vector will be treated as a single-column Matrix. </para>
	/// <para> The Vector must meet constraint A or B: </para>
	/// <para> A: The Vector's size is equal to the number of rows in the provided Matrix. </para>
	/// <para> B: The Vector's size is equal to the number of rows in the provided Matrix - 1. In this case, the non-contained index will be treated as 1. </para>
	/// <para> NOTE: OutColumnMajor_ is unused in this function. It is only present to allow a consistent interface for templates. </para>
	/// </summary>
	/// <param name="lhs_matrix_">: EmuMath Matrix to multiply a Vector via.</param>
	/// <param name="rhs_vector_">: EmuMath Vector to multiply via the provided Matrix.</param>
	/// <returns>EmuMath Vector resulting from a multiplication of the provided Matrix and Vector.</returns>
	template<class OutT_, bool OutColumnMajor_, std::size_t LhsNumColumns_, std::size_t LhsNumRows_, typename LhsT_, bool LhsColumnMajor_, std::size_t RhsSize_, typename RhsT_>
	[[nodiscard]] constexpr inline EmuMath::Vector<RhsSize_, OutT_> matrix_multiply
	(
		const EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>& lhs_matrix_,
		const EmuMath::Vector<RhsSize_, RhsT_>& rhs_vector_
	)
	{
		return _matrix_underlying::_matrix_std_multiply_mat_vector<OutT_>(lhs_matrix_, rhs_vector_);
	}

	template<bool OutColumnMajor_, std::size_t LhsNumColumns_, std::size_t LhsNumRows_, typename LhsT_, bool LhsColumnMajor_, std::size_t RhsSize_, typename RhsT_>
	[[nodiscard]] constexpr inline EmuMath::Vector<RhsSize_, typename EmuMath::Vector<RhsSize_, RhsT_>::preferred_floating_point> matrix_multiply
	(
		const EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>& lhs_matrix_,
		const EmuMath::Vector<RhsSize_, RhsT_>& rhs_vector_
	)
	{
		using rhs_fp = typename EmuMath::Vector<RhsSize_, RhsT_>::preferred_floating_point;
		return _matrix_underlying::_matrix_std_multiply_mat_vector<rhs_fp>(lhs_matrix_, rhs_vector_);
	}

	template<class OutT_, std::size_t LhsNumColumns_, std::size_t LhsNumRows_, typename LhsT_, bool LhsColumnMajor_, std::size_t RhsSize_, typename RhsT_>
	[[nodiscard]] constexpr inline EmuMath::Vector<RhsSize_, OutT_> matrix_multiply
	(
		const EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>& lhs_matrix_,
		const EmuMath::Vector<RhsSize_, RhsT_>& rhs_vector_
	)
	{
		return _matrix_underlying::_matrix_std_multiply_mat_vector<OutT_>(lhs_matrix_, rhs_vector_);
	}

	template<std::size_t LhsNumColumns_, std::size_t LhsNumRows_, typename LhsT_, bool LhsColumnMajor_, std::size_t RhsSize_, typename RhsT_>
	[[nodiscard]] constexpr inline EmuMath::Vector<RhsSize_, typename EmuMath::Vector<RhsSize_, RhsT_>::preferred_floating_point> matrix_multiply
	(
		const EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>& lhs_matrix_,
		const EmuMath::Vector<RhsSize_, RhsT_>& rhs_vector_
	)
	{
		using rhs_fp = typename EmuMath::Vector<RhsSize_, RhsT_>::preferred_floating_point;
		return _matrix_underlying::_matrix_std_multiply_mat_vector<rhs_fp>(lhs_matrix_, rhs_vector_);
	}

	template
	<
		std::size_t LhsNumColumns_, std::size_t LhsNumRows_, typename LhsT_, bool LhsColumnMajor_, std::size_t RhsSize_, typename RhsT_, std::size_t OutSize_, typename OutT_
	>
	[[nodiscard]] constexpr inline void matrix_multiply
	(
		EmuMath::Vector<OutSize_, OutT_>& out_vector_,
		const EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>& lhs_matrix_,
		const EmuMath::Vector<RhsSize_, RhsT_>& rhs_vector_
	)
	{
		_matrix_underlying::_matrix_std_multiply_assign_mat_vector(out_vector_, lhs_matrix_, rhs_vector_);
	}
#pragma endregion

#pragma region MULTIPLY_WITH_MATRIX_RHS
	/// <summary>
	/// <para> Outputs the result of a standard Matrix multiplication with the two provided Matrices. </para>
	/// <para> The output Matrix will have a number of columns equal to that of rhs_matrix_, and a number of rows equal to that of lhs_matrix_. </para>
	/// <para> The number of columns in lhs_matrix_ must be equal to the number of rows in rhs_matrix_. </para>
	/// <para>
	///		Output indices will be the dot product of the row in lhs_matrix_ and the column in rhs_matrix_. 
	///		For example, out(1, 3) would be (in pseudocode) dot(lhs_matrix_.Rows[3], rhs_matrix_.Columns[1]).
	/// </para>
	/// </summary>
	/// <param name="lhs_matrix_">: EmuMath Matrix appearing on the left of Matrix multiplication.</param>
	/// <param name="rhs_matrix_">: EmuMath Matrix appearing on the right of Matrix multiplication.</param>
	/// <returns>EmuMath Matrix resulting from a standard Matrix multiplication of the two provided Matrices.</returns>
	template
	<
		typename OutT_, bool OutColumnMajor_,
		std::size_t LhsNumColumns_, std::size_t LhsNumRows_, typename LhsT_, bool LhsColumnMajor_,
		std::size_t RhsNumColumns_, std::size_t RhsNumRows_, typename RhsT_, bool RhsColumnMajor_
	>
	[[nodiscard]] constexpr inline EmuMath::Matrix<RhsNumColumns_, LhsNumRows_, OutT_, OutColumnMajor_> matrix_multiply
	(
		const EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>& lhs_matrix_,
		const EmuMath::Matrix<RhsNumColumns_, RhsNumRows_, RhsT_, RhsColumnMajor_>& rhs_matrix_
	)
	{
		return _matrix_underlying::_matrix_std_multiply_mat_mat<OutT_, OutColumnMajor_>(lhs_matrix_, rhs_matrix_);
	}

	template
	<
		bool OutColumnMajor_,
		std::size_t LhsNumColumns_, std::size_t LhsNumRows_, typename LhsT_, bool LhsColumnMajor_,
		std::size_t RhsNumColumns_, std::size_t RhsNumRows_, typename RhsT_, bool RhsColumnMajor_
	>
	[[nodiscard]] constexpr inline EmuMath::Matrix
	<
		RhsNumColumns_,
		LhsNumRows_,
		typename EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>::preferred_floating_point,
		OutColumnMajor_
	>
	matrix_multiply
	(
		const EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>& lhs_matrix_,
		const EmuMath::Matrix<RhsNumColumns_, RhsNumRows_, RhsT_, RhsColumnMajor_>& rhs_matrix_
	)
	{
		using lhs_fp = typename EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>::preferred_floating_point;
		return _matrix_underlying::_matrix_std_multiply_mat_mat<lhs_fp, OutColumnMajor_>(lhs_matrix_, rhs_matrix_);
	}

	template
	<
		typename OutT_,
		std::size_t LhsNumColumns_, std::size_t LhsNumRows_, typename LhsT_, bool LhsColumnMajor_,
		std::size_t RhsNumColumns_, std::size_t RhsNumRows_, typename RhsT_, bool RhsColumnMajor_
	>
	[[nodiscard]] constexpr inline EmuMath::Matrix<RhsNumColumns_, LhsNumRows_, OutT_, LhsColumnMajor_> matrix_multiply
	(
		const EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>& lhs_matrix_,
		const EmuMath::Matrix<RhsNumColumns_, RhsNumRows_, RhsT_, RhsColumnMajor_>& rhs_matrix_
	)
	{
		return _matrix_underlying::_matrix_std_multiply_mat_mat<OutT_, LhsColumnMajor_>(lhs_matrix_, rhs_matrix_);
	}

	template
	<
		std::size_t LhsNumColumns_, std::size_t LhsNumRows_, typename LhsT_, bool LhsColumnMajor_,
		std::size_t RhsNumColumns_, std::size_t RhsNumRows_, typename RhsT_, bool RhsColumnMajor_
	>
	[[nodiscard]] constexpr inline EmuMath::Matrix
	<
		RhsNumColumns_,
		LhsNumRows_,
		typename EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>::preferred_floating_point,
		LhsColumnMajor_
	>
	matrix_multiply
	(
		const EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>& lhs_matrix_,
		const EmuMath::Matrix<RhsNumColumns_, RhsNumRows_, RhsT_, RhsColumnMajor_>& rhs_matrix_
	)
	{
		using lhs_fp = typename EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>::preferred_floating_point;
		return _matrix_underlying::_matrix_std_multiply_mat_mat<lhs_fp, LhsColumnMajor_>(lhs_matrix_, rhs_matrix_);
	}

	template
	<
		std::size_t LhsNumColumns_, std::size_t LhsNumRows_, typename LhsT_, bool LhsColumnMajor_,
		std::size_t RhsNumColumns_, std::size_t RhsNumRows_, typename RhsT_, bool RhsColumnMajor_,
		std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, bool OutColumnMajor_
	>
	constexpr inline void matrix_multiply
	(
		EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>& out_matrix_,
		const EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>& lhs_matrix_,
		const EmuMath::Matrix<RhsNumColumns_, RhsNumRows_, RhsT_, RhsColumnMajor_>& rhs_matrix_
	)
	{
		_matrix_underlying::_matrix_std_multiply_assign_mat_mat<OutColumnMajor_>(out_matrix_, lhs_matrix_, rhs_matrix_);
	}
#pragma endregion
}

#endif
