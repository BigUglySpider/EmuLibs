#ifndef EMU_MATH_MATRIX_HELPERS_REINTERPRETATIONS_H_INC_
#define EMU_MATH_MATRIX_HELPERS_REINTERPRETATIONS_H_INC_ 1

#include "_common_matrix_helper_includes.h"

namespace EmuMath::Helpers
{
// These reinterpretations are specifically those related to matrices, that would only act as pointless noise if included without matrices.
#pragma region VECTOR_REINTERPRETATIONS
	/// <summary>
	/// <para> Converts the passed EmuMath vector to an EmuMath matrix as though it represents a single column. </para>
	/// <para>
	///		The vector data will be stored as columns regardless of the ColumnMajor_ argument. 
	///		To store the vector as a row matrix instead, use vector_to_row_matrix.
	/// </para>
	/// </summary>
	/// <typeparam name="Vector_">Type of EmuMath vector to convert to a column matrix.</typeparam>
	/// <typeparam name="out_contained_type">Type to be contained within the output matrix.</typeparam>
	/// <param name="vector_">EmuMath vector to convert to a column matrix.</param>
	/// <returns>Column matrix containing a copy of the passed vector's data. The matrix will be a single column which contains the full data of the passed vector.</returns>
	template<typename out_contained_type, bool ColumnMajor_ = true, class Vector_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<1, Vector_::size, out_contained_type, ColumnMajor_> vector_to_column_matrix(const Vector_& vector_)
	{
		if constexpr (EmuMath::TMP::is_emu_vector_v<Vector_>)
		{
			return _underlying_matrix_funcs::_vector_to_matrix<Vector_, EmuMath::Matrix<1, Vector_::size, out_contained_type, ColumnMajor_>>
			(
				vector_
			);
		}
		else
		{
			static_assert(false, "Attempted to convert a vector to a column matrix, but the provided argument was not an EmuMath vector.");
		}
	}
	template<bool ColumnMajor_ = true, class Vector_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<1, Vector_::size, typename Vector_::value_type, ColumnMajor_> vector_to_column_matrix(const Vector_& vector_)
	{
		return vector_to_column_matrix<typename Vector_::value_type, ColumnMajor_, Vector_>(vector_);
	}

	/// <summary>
	/// <para> Converts the passed EmuMath vector to an EmuMath matrix as though it represents a single row. </para>
	/// <para>
	///		The vector data will be stored as rows regardless of the ColumnMajor_ argument. 
	///		To store the vector as a column matrix instead, use vector_to_column_matrix.
	/// </para>
	/// </summary>
	/// <typeparam name="Vector_">Type of EmuMath vector to convert to a row matrix.</typeparam>
	/// <typeparam name="out_contained_type">Type to be contained within the output matrix.</typeparam>
	/// <param name="vector_">EmuMath vector to convert to a row matrix.</param>
	/// <returns>Row matrix containing a copy of the passed vector's data. The matrix will be a single row which contains the full data of the passed vector.</returns>
	template<typename out_contained_type, bool ColumnMajor_ = true, class Vector_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<Vector_::size, 1, out_contained_type, ColumnMajor_> vector_to_row_matrix(const Vector_& vector_)
	{
		if constexpr (EmuMath::TMP::is_emu_vector_v<Vector_>)
		{
			return _underlying_matrix_funcs::_vector_to_matrix<Vector_, EmuMath::Matrix<Vector_::size, 1, out_contained_type, ColumnMajor_>>
			(
				vector_
			);
		}
		else
		{
			static_assert(false, "Attempted to convert a vector to a row matrix, but the provided argument was not an EmuMath vector.");
		}
	}
	template<bool ColumnMajor_ = true, class Vector_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<Vector_::size, 1, typename Vector_::value_type, ColumnMajor_> vector_to_row_matrix(const Vector_& vector_)
	{
		return vector_to_row_matrix<typename Vector_::value_type, ColumnMajor_, Vector_>(vector_);
	}

	/// <summary>
	/// <para> Creates an EmuMath vector one item larger than the passed vector, containing a copy of the passed vector_ in existing indices and 1 in the new index. </para>
	/// <para> This process allows an X-dimensional vector to be transformed by an (X+1)x(X+1) transformation matrix. </para>
	/// <para> Note that if the vector's dimension is equal to the square transformation matrix's dimension (e.g. 4D vector and 4x4 matrix), this is not required. </para>
	/// </summary>
	/// <typeparam name="out_contained_type">Type to be contained within the output vector.</typeparam>
	/// <typeparam name="Vector_">Type of EmuMath vector to prepare for transformation.</typeparam>
	/// <param name="vector_">EmuMath vector to prepare for transformation.</param>
	/// <returns>Copy of the provided vector_, with one additional element appended to the end set to 1.</returns>
	template<typename out_contained_type, class Vector_>
	[[nodiscard]] constexpr inline EmuMath::Vector<Vector_::size + 1, out_contained_type> vector_prepare_to_transform(const Vector_& vector_)
	{
		if constexpr (EmuMath::TMP::is_emu_vector_v<Vector_>)
		{
			EmuMath::Vector<Vector_::size + 1, out_contained_type> out_(vector_);
			out_.at<Vector_::size>() = out_contained_type(1.0);
			return out_;
		}
		else
		{
			static_assert(false, "Attempted to prepare a vector to be transformed by a matrix, but the provided argument was not an EmuMath vector.");
		}
	}
	template<class Vector_>
	[[nodiscard]] constexpr inline EmuMath::Vector<Vector_::size + 1, typename Vector_::value_type> vector_prepare_to_transform(const Vector_& vector_)
	{
		return vector_prepare_to_transform<typename Vector_::value_type, Vector_>(vector_);
	}

	/// <summary>
	/// <para> Returns a copy of the passed EmuMath matrix cast to the provided type of EmuMath matrix. </para>
	/// <para> Template arguments follow the same ordering as instantiating an EmuMath::Matrix type. </para>
	/// <para> Arguments may be omitted to use the same argument as the passed matrix. </para>
	/// <para> For elements in the output cast that do not exist in the input matrix: values will be default constructed elements. </para>
	/// <para> For elements in the input matrix that cannot fit into the output cast: values will be ignored. </para>
	/// </summary>
	/// <typeparam name="out_contained_type">Type to be contained in the output matrix.</typeparam>
	/// <typeparam name="Matrix_">Type of matrix to cast from.</typeparam>
	/// <param name="matrix_">Matrix to cast into the desired matrix type.</param>
	/// <returns>Copy of the passed matrix cast to a matrix with the desired template arguments on instantiation.</returns>
	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename out_contained_type, bool OutColumnMajor_, class Matrix_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, out_contained_type, OutColumnMajor_> matrix_as(const Matrix_& matrix_)
	{
		if constexpr (EmuMath::TMP::is_emu_matrix_v<Matrix_>)
		{
			return _underlying_matrix_funcs::_matrix_as
			<
				EmuMath::Matrix<OutNumColumns_, OutNumRows_, out_contained_type, OutColumnMajor_>,
				Matrix_
			>(matrix_);
		}
		else
		{
			static_assert(false, "Attempted to cast a matrix to a different kind of EmuMath matrix, but the provided matrix_ was not an EmuMath matrix.");
		}
	}
	template<typename out_contained_type, bool OutColumnMajor_, class Matrix_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<Matrix_::num_columns, Matrix_::num_rows, out_contained_type, OutColumnMajor_> matrix_as(const Matrix_& matrix_)
	{
		return matrix_as<Matrix_::num_columns, Matrix_::num_rows, out_contained_type, OutColumnMajor_, Matrix_>(matrix_);
	}
	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, bool OutColumnMajor_, class Matrix_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, typename Matrix_::value_type, OutColumnMajor_> matrix_as(const Matrix_& matrix_)
	{
		return matrix_as<OutNumColumns_, OutNumRows_, typename Matrix_::value_type, OutColumnMajor_, Matrix_>(matrix_);
	}
	template<bool OutColumnMajor_, class Matrix_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<Matrix_::num_columns, Matrix_::num_rows, typename Matrix_::value_type, OutColumnMajor_> matrix_as(const Matrix_& matrix_)
	{
		return matrix_as<Matrix_::num_columns, Matrix_::num_rows, typename Matrix_::value_type, OutColumnMajor_, Matrix_>(matrix_);
	}
	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename out_contained_type, class Matrix_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, out_contained_type, Matrix_::is_column_major> matrix_as(const Matrix_& matrix_)
	{
		return matrix_as<OutNumColumns_, OutNumRows_, out_contained_type, Matrix_::is_column_major, Matrix_>(matrix_);
	}
	template<typename out_contained_type, class Matrix_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<Matrix_::num_columns, Matrix_::num_rows, out_contained_type, Matrix_::is_column_major> matrix_as(const Matrix_& matrix_)
	{
		return matrix_as<Matrix_::num_columns, Matrix_::num_rows, out_contained_type, Matrix_::is_column_major, Matrix_>(matrix_);
	}
	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, class Matrix_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, typename Matrix_::value_type, Matrix_::is_column_major> matrix_as(const Matrix_& matrix_)
	{
		return matrix_as<OutNumColumns_, OutNumRows_, typename Matrix_::value_type, Matrix_::is_column_major, Matrix_>(matrix_);
	}
#pragma endregion
}

#endif
