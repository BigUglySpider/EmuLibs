#ifndef EMU_MATH_MATRIX_VECTOR_EXTENSIONS_H_INC_
#define EMU_MATH_MATRIX_VECTOR_EXTENSIONS_H_INC_ 1

#include "_helpers/_all_matrix_helpers.h"
#include "_matrix_t.h"

namespace EmuMath::Helpers
{
#pragma region MULTIPLY_VALIDITY
	template<std::size_t LhsSize_, typename LhsT_, EmuConcepts::EmuMatrix Matrix_, bool StaticAssert_ = false>
	[[nodiscard]] constexpr inline bool valid_vector_mul_matrix_args()
	{
		using _in_mat_uq = typename EmuCore::TMP::remove_ref_cv<Matrix_>::type;

		if constexpr (LhsSize_ == _in_mat_uq::num_columns || LhsSize_ == (_in_mat_uq::num_columns - 1))
		{
			return true;
		}
		else
		{
			static_assert
			(
				!StaticAssert_,
				"Unable to multiply a Vector by a Matrix (VEC * MAT) as the input left-hand Vector does not have a size equal to the number of columns in the right-hand Matrix, or its number of columns - 1."
			);
			return false;
		}
	}

	template<EmuConcepts::EmuMatrix Matrix_, std::size_t RhsSize_, typename RhsT_, bool StaticAssert_ = false>
	[[nodiscard]] constexpr inline bool valid_matrix_mul_vector_args()
	{
		using _in_mat_uq = typename EmuCore::TMP::remove_ref_cv<Matrix_>::type;

		if constexpr (RhsSize_ == _in_mat_uq::num_rows || RhsSize_ == (_in_mat_uq::num_rows - 1))
		{
			return true;
		}
		else
		{
			static_assert
			(
				!StaticAssert_,
				"Unable to multiply a Matrix by a Vector (MAT * VEC) as the input right-hand Vector does not have a size equal to the number of rows in the left-hand Matrix, or its number of rows - 1."
			);
			return false;
		}
	}
#pragma endregion

#pragma region STD_MULTIPLY
	/// <summary>
	/// <para> Matrix extension allowing a left-hand row-Vector to be multiplied by a right-hand Column Matrix. </para>
	/// <para> The left-hand Vector is treated as a single-row Matrix, and must have as many elements as the right-hand Matrix has columns. </para>
	/// <para> 
	///		Alternatively, the left-hand Vector may have a number of elements equal to the Matrix's number of columns - 1. 
	///		In this case, the missing element is treated as 1 for common uses such as transforming 3D Vectors by 4x4 Matrices.
	/// </para>
	/// <para>
	///		Note that Vector multiplication is non-commutative, in that A*B != B*A (with some exceptions). 
	///		If you are using this to transform Vectors from EmuMath utilities, EmuMath Transformation Matrices are designed to be the right-hand argument by default.
	/// </para>
	/// </summary>
	/// <param name="lhs_vector_">Vector appearing on the left-hand side of multiplication, interpreted as a single-row Matrix.</param>
	/// <param name="rhs_matrix_">Matrix appearing on the right-hand side of multiplication.</param>
	/// <returns>Vector resulting from multiplying the VEC * MAT operation, with the passed Vector treated as a single-row Matrix.</returns>
	template<typename OutT_, EmuConcepts::EmuMatrix Matrix_, typename LhsT_, std::size_t LhsSize_>
	[[nodiscard]] constexpr inline auto vector_multiply(const EmuMath::Vector<LhsSize_, LhsT_>& lhs_vector_, Matrix_&& rhs_matrix_)
		-> std::enable_if_t<valid_vector_mul_matrix_args<LhsSize_, LhsT_, Matrix_, false>(), EmuMath::Vector<LhsSize_, OutT_>>
	{
		return _matrix_underlying::_matrix_std_multiply_vector_mat<OutT_>(lhs_vector_, std::forward<Matrix_>(rhs_matrix_));
	}

	/// <summary>
	/// <para> Matrix extension allowing a left-hand column-Vector to be multiplied by a right-hand Row Matrix. </para>
	/// <para> The left-hand Vector is treated as a single-column Matrix, and must have as many elements as the right-hand Matrix has rows. </para>
	/// <para> 
	///		Alternatively, the left-hand Vector may have a number of elements equal to the Matrix's number of rows - 1. 
	///		In this case, the missing element is treated as 1 for common uses such as transforming 3D Vectors by 4x4 Matrices.
	/// </para>
	/// <para>
	///		Note that Vector multiplication is non-commutative, in that A*B != B*A (with some exceptions). 
	///		If you are using this to transform Vectors from EmuMath utilities, EmuMath Transformation Matrices are designed to be the right-hand argument by default.
	/// </para>
	/// </summary>
	/// <param name="rhs_matrix_">Matrix appearing on the left-hand side of multiplication.</param>
	/// <param name="rhs_vector_">Vector appearing on the right-hand side of multiplication, interpreted as a single-column Matrix.</param>
	/// <returns>Vector resulting from multiplying the MAT * VEC operation, with the passed Vector treated as a single-column Matrix.</returns>
	template<typename OutT_, EmuConcepts::EmuMatrix LhsMatrix_, typename RhsT_, std::size_t RhsSize_>
	[[nodiscard]] constexpr inline auto vector_multiply(LhsMatrix_&& lhs_matrix_, const EmuMath::Vector<RhsSize_, RhsT_>& rhs_vector_)
		-> std::enable_if_t<valid_matrix_mul_vector_args<LhsMatrix_, RhsSize_, RhsT_>, EmuMath::Vector<RhsSize_, OutT_>>
	{
		return _matrix_underlying::_matrix_std_multiply_mat_vector<OutT_>(std::forward<LhsMatrix_>(lhs_matrix_), rhs_vector_);
	}
#pragma endregion
}

#pragma region VECTOR_MUL_MAT_OPERATORS
/// <summary>
/// <para> Matrix extension to the multiply operator, allowing a left-hand row-Vector to be multiplied by a right-hand Column Matrix. </para>
/// <para> The left-hand Vector is treated as a single-row Matrix, and must have as many elements as the right-hand Matrix has columns. </para>
/// <para> 
///		Alternatively, the left-hand Vector may have a number of elements equal to the Matrix's number of columns - 1. 
///		In this case, the missing element is treated as 1 for common uses such as transforming 3D Vectors by 4x4 Matrices.
/// </para>
/// <para>
///		Note that Vector multiplication is non-commutative, in that A*B != B*A (with some exceptions). 
///		If you are using this to transform Vectors from EmuMath utilities, EmuMath Transformation Matrices are designed to be the right-hand argument by default.
/// </para>
/// </summary>
/// <param name="lhs_vector_">Vector appearing on the left-hand side of multiplication, interpreted as a single-row Matrix.</param>
/// <param name="rhs_matrix_">Matrix appearing on the right-hand side of multiplication.</param>
/// <returns>Vector resulting from multiplying the VEC * MAT operation, with the passed Vector treated as a single-row Matrix.</returns>
template<EmuConcepts::EmuMatrix Matrix_, typename LhsT_, std::size_t LhsSize_>
[[nodiscard]] constexpr inline auto operator*(const EmuMath::Vector<LhsSize_, LhsT_>& lhs_vector_, Matrix_&& rhs_matrix_)
	-> std::enable_if_t
	<
		EmuMath::Helpers::valid_vector_mul_matrix_args<LhsSize_, LhsT_, Matrix_, false>(),
		EmuMath::Vector<LhsSize_, typename EmuMath::Vector<LhsSize_, LhsT_>::value_type_uq>
	>
{
	return EmuMath::Helpers::_matrix_underlying::_matrix_std_multiply_vector_mat<typename EmuMath::Vector<LhsSize_,LhsT_>::value_type_uq>
	(
		lhs_vector_,
		std::forward<Matrix_>(rhs_matrix_)
	);
}

/// <summary>
/// <para> Matrix extension to the multiply-assign operator, allowing a left-hand row-Vector to be multiplied by a right-hand Column Matrix. </para>
/// <para> The left-hand Vector is treated as a single-row Matrix, and must have as many elements as the right-hand Matrix has columns. </para>
/// <para> 
///		Alternatively, the left-hand Vector may have a number of elements equal to the Matrix's number of columns - 1. 
///		In this case, the missing element is treated as 1 for common uses such as transforming 3D Vectors by 4x4 Matrices.
/// </para>
/// <para>
///		Note that Vector multiplication is non-commutative, in that A*B != B*A (with some exceptions). 
///		If you are using this to transform Vectors from EmuMath utilities, EmuMath Transformation Matrices are designed to be the right-hand argument by default.
/// </para>
/// </summary>
/// <param name="lhs_vector_">
///		Vector appearing on the left-hand side of multiplication, interpreted as a single-row Matrix, and to which results are assigned. 
///		Be aware that a copy of this may be created to perform the operation correctly.
/// </param>
/// <param name="rhs_matrix_">Matrix appearing on the right-hand side of multiplication.</param>
/// <returns>Reference to the left-hand Vector.</returns>
template<EmuConcepts::EmuMatrix Matrix_, typename LhsT_, std::size_t LhsSize_>
constexpr inline auto operator*=(EmuMath::Vector<LhsSize_, LhsT_>& lhs_vector_, Matrix_&& rhs_matrix_)
	-> std::enable_if_t<EmuMath::Helpers::valid_vector_mul_matrix_args<LhsSize_, LhsT_, Matrix_, false>(), EmuMath::Vector<LhsSize_, LhsT_>&>
{
	EmuMath::Helpers::_matrix_underlying::_matrix_std_multiply_assign_vector_mat(lhs_vector_, std::forward<Matrix_>(rhs_matrix_));
	return lhs_vector_;
}
#pragma endregion

#endif
