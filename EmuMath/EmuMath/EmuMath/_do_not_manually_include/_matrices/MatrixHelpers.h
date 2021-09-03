#ifndef EMU_MATH_MATRIX_HELPERS_H_INC_
#define EMU_MATH_MATRIX_HELPERS_H_INC_ 1

#include "MatrixHelpersUnderlying.h"

namespace EmuMath::Helpers
{
#pragma region INDEX_CONVERSIONS
	/// <summary>
	/// <para> Converts the provided MajorOrderIndex_ to a column index within the provided Matrix_ type. </para>
	/// <para> The provided MajorOrderIndex_ should be an index within contiguous order of how each element is stored within the matrix. </para>
	/// </summary>
	/// <typeparam name="Matrix_">Matrix type to determine the column index of.</typeparam>
	/// <returns>Column index required to access the given element index within the provided Matrix_ type.</returns>
	template<std::size_t MajorOrderIndex_, class Matrix_>
	constexpr inline std::size_t MatrixMajorOrderIndexToColumnIndex()
	{
		if constexpr (EmuMath::TMP::is_emu_matrix_v<Matrix_>)
		{
			if constexpr (MajorOrderIndex_ < Matrix_::size)
			{
				return _underlying_matrix_funcs::_matrix_major_order_index_to_column_index<MajorOrderIndex_, Matrix_>();
			}
			else
			{
				static_assert(false, "Attempted to get the column index for a matrix via a major-order index, but the provided major-order index exceeds the maximum index of the provided matrix.");
			}
		}
		else
		{
			static_assert(false, "Attempted to get the column index for a matrix via a major-order index, but the provided Matrix_ type was not an EmuMath matrix.");
		}
	}
	template<std::size_t MajorOrderIndex_, class Matrix_>
	constexpr inline std::size_t MatrixMajorOrderIndexToColumnIndex(const Matrix_& matrix_)
	{
		return MatrixMajorOrderIndexToColumnIndex<MajorOrderIndex_, Matrix_>();
	}

	/// <summary>
	/// <para> Converts the provided MajorOrderIndex_ to a column index within the provided Matrix_ type. </para>
	/// <para> The passed majorOrderIndex_ should be an index within contiguous order of how each element is stored within the matrix. </para>
	/// </summary>
	/// <typeparam name="Matrix_">Matrix type to determine the column index of.</typeparam>
	/// <param name="majorOrderIndex_">Index of a specific element in contiguous space within the matrix of the provided type to determine the column index of.</param>
	/// <returns>Column index required to access the passed majorOrderIndex_ within the provided Matrix_ type.</returns>
	template<class Matrix_>
	constexpr inline std::size_t MatrixMajorOrderIndexToColumnIndex(const std::size_t majorOrderIndex_)
	{
		if constexpr (EmuMath::TMP::is_emu_matrix_v<Matrix_>)
		{
			return _underlying_matrix_funcs::_matrix_major_order_index_to_column_index<Matrix_>(majorOrderIndex_);
		}
		else
		{
			static_assert(false, "Attempted to get the column index for a matrix via a major-order index, but the provided Matrix_ type was not an EmuMath matrix.");
		}
	}
	template<class Matrix_>
	constexpr inline std::size_t MatrixMajorOrderIndexToColumnIndex(const std::size_t majorOrderIndex_, const Matrix_& matrix_)
	{
		return MatrixMajorOrderIndexToColumnIndex<Matrix_>(majorOrderIndex_);
	}

	/// <summary>
	/// <para> Converts the provided MajorOrderIndex_ to a row index within the provided Matrix_ type. </para>
	/// <para> The provided MajorOrderIndex_ should be an index within contiguous order of how each element is stored within the matrix. </para>
	/// </summary>
	/// <typeparam name="Matrix_">Matrix type to determine the row index of.</typeparam>
	/// <returns>Row index required to access the given element index within the provided Matrix_ type.</returns>
	template<std::size_t MajorOrderIndex_, class Matrix_>
	constexpr inline std::size_t MatrixMajorOrderIndexToRowIndex()
	{
		if constexpr (EmuMath::TMP::is_emu_matrix_v<Matrix_>)
		{
			if constexpr (MajorOrderIndex_ < Matrix_::size)
			{
				return _underlying_matrix_funcs::_matrix_major_order_index_to_row_index<MajorOrderIndex_, Matrix_>();
			}
			else
			{
				static_assert(false, "Attempted to get the row index for a matrix via a major-order index, but the provided major-order index exceeds the maximum index of the provided matrix.");
			}
		}
		else
		{
			static_assert(false, "Attempted to get the row index for a matrix via a major-order index, but the provided Matrix_ type was not an EmuMath matrix.");
		}
	}
	template<std::size_t MajorOrderIndex_, class Matrix_>
	constexpr inline std::size_t MatrixMajorOrderIndexToRowIndex(const Matrix_& matrix_)
	{
		return MatrixMajorOrderIndexToRowIndex<MajorOrderIndex_, Matrix_>();
	}

	/// <summary>
	/// <para> Converts the provided MajorOrderIndex_ to a row index within the provided Matrix_ type. </para>
	/// <para> The passed majorOrderIndex_ should be an index within contiguous order of how each element is stored within the matrix. </para>
	/// </summary>
	/// <typeparam name="Matrix_">Matrix type to determine the row index of.</typeparam>
	/// <param name="majorOrderIndex_">Index of a specific element in contiguous space within the matrix of the provided type to determine the row index of.</param>
	/// <returns>Row index required to access the passed majorOrderIndex_ within the provided Matrix_ type.</returns>
	template<class Matrix_>
	constexpr inline std::size_t MatrixMajorOrderIndexToRowIndex(const std::size_t majorOrderIndex_)
	{
		if constexpr (EmuMath::TMP::is_emu_matrix_v<Matrix_>)
		{
			return _underlying_matrix_funcs::_matrix_major_order_index_to_row_index<Matrix_>(majorOrderIndex_);
		}
		else
		{
			static_assert(false, "Attempted to get the row index for a matrix via a major-order index, but the provided Matrix_ type was not an EmuMath matrix.");
		}
	}
	template<class Matrix_>
	constexpr inline std::size_t MatrixMajorOrderIndexToRowIndex(const std::size_t majorOrderIndex_, const Matrix_& matrix_)
	{
		return MatrixMajorOrderIndexToRowIndex<Matrix_>(majorOrderIndex_);
	}
#pragma endregion

#pragma region GETS
	/// <summary> Returns a reference to the element at the specified Column and Row indices within the passed vector. </summary>
	/// <typeparam name="Matrix_">Type of EmuMath matrix to retrieve an element of.</typeparam>
	/// <param name="matrix_">EmuMath matrix to retrieve an element of.</param>
	/// <returns>Reference to the element at the specified column+row index within the passed matrix.</returns>
	template<std::size_t ColumnIndex_, std::size_t RowIndex_, class Matrix_>
	constexpr inline auto& MatrixGet(Matrix_& matrix_)
	{
		if constexpr (EmuMath::TMP::is_emu_matrix_v<Matrix_>)
		{
			return _underlying_matrix_funcs::_get_matrix_data<ColumnIndex_, RowIndex_, Matrix_>(matrix_);
		}
		else
		{
			static_assert(false, "Attempted to get an Column+Row indexed element from a matrix, but provided a non-EmuMath-matrix argument.");
		}
	}
	template<std::size_t ColumnIndex_, std::size_t RowIndex_, class Matrix_>
	constexpr inline const auto& MatrixGet(const Matrix_& matrix_)
	{
		if constexpr (EmuMath::TMP::is_emu_matrix_v<Matrix_>)
		{
			return _underlying_matrix_funcs::_get_matrix_data<ColumnIndex_, RowIndex_, Matrix_>(matrix_);
		}
		else
		{
			static_assert(false, "Attempted to get an Column+Row indexed element from a matrix, but provided a non-EmuMath-matrix argument.");
		}
	}
	template<class Matrix_>
	constexpr inline auto& MatrixGet(Matrix_& matrix_, const std::size_t column_index_, const std::size_t row_index_)
	{
		if constexpr (EmuMath::TMP::is_emu_matrix_v<Matrix_>)
		{
			return _underlying_matrix_funcs::_get_matrix_data<Matrix_>(matrix_, column_index_, row_index_);
		}
		else
		{
			static_assert(false, "Attempted to get an Column+Row indexed element from a matrix, but provided a non-EmuMath-matrix argument.");
		}
	}
	template<class Matrix_>
	constexpr inline auto& MatrixGet(const Matrix_& matrix_, const std::size_t column_index_, const std::size_t row_index_)
	{
		if constexpr (EmuMath::TMP::is_emu_matrix_v<Matrix_>)
		{
			return _underlying_matrix_funcs::_get_matrix_data<Matrix_>(matrix_, column_index_, row_index_);
		}
		else
		{
			static_assert(false, "Attempted to get an Column+Row indexed element from a matrix, but provided a non-EmuMath-matrix argument.");
		}
	}

	/// <summary> 
	/// <para> Returns a reference to the element at the specified MajorOrder index within the passed vector. </para>
	/// <para> MajorOrder indices refer to contiguous elements, and their 2D translations depend on the major order of the matrix. </para>
	/// <para>
	///		For a better understanding of where a matrix's MajorOrderIndex_ will translate to, consider reviewing the results of 
	///		MatrixMajorOrderIndexToColumnIndex and MatrixMajorOrderIndexToRowIndex.
	/// </para>
	/// </summary>
	/// <typeparam name="Matrix_">Type of EmuMath matrix to retrieve an element of.</typeparam>
	/// <param name="matrix_">EmuMath matrix to retrieve an element of.</param>
	/// <returns>Reference to the element at the specified column+row index within the passed matrix.</returns>
	template<std::size_t MajorOrderIndex_, class Matrix_>
	constexpr inline auto& MatrixGet(Matrix_& matrix_)
	{
		if constexpr (EmuMath::TMP::is_emu_matrix_v<Matrix_>)
		{
			return _underlying_matrix_funcs::_get_matrix_data<MajorOrderIndex_, Matrix_>(matrix_);
		}
		else
		{
			static_assert(false, "Attempted to get a Major-order indexed element from a matrix, but provided a non-EmuMath-matrix argument.");
		}
	}
	template<std::size_t MajorOrderIndex_, class Matrix_>
	constexpr inline auto& MatrixGet(const Matrix_& matrix_)
	{
		if constexpr (EmuMath::TMP::is_emu_matrix_v<Matrix_>)
		{
			return _underlying_matrix_funcs::_get_matrix_data<MajorOrderIndex_, Matrix_>(matrix_);
		}
		else
		{
			static_assert(false, "Attempted to get a Major-order indexed element from a matrix, but provided a non-EmuMath-matrix argument.");
		}
	}
	template<class Matrix_>
	constexpr inline auto& MatrixGet(Matrix_& matrix_, const std::size_t major_order_index_)
	{
		if constexpr (EmuMath::TMP::is_emu_matrix_v<Matrix_>)
		{
			return _underlying_matrix_funcs::_get_matrix_data<Matrix_>(matrix_, major_order_index_);
		}
		else
		{
			static_assert(false, "Attempted to get a Major-order indexed element from a matrix, but provided a non-EmuMath-matrix argument.");
		}
	}
	template<class Matrix_>
	constexpr inline auto& MatrixGet(const Matrix_& matrix_, const std::size_t major_order_index_)
	{
		if constexpr (EmuMath::TMP::is_emu_matrix_v<Matrix_>)
		{
			return _underlying_matrix_funcs::_get_matrix_data<Matrix_>(matrix_, major_order_index_);
		}
		else
		{
			static_assert(false, "Attempted to get a Major-order indexed element from a matrix, but provided a non-EmuMath-matrix argument.");
		}
	}

	/// <summary> Returns a vector which references the requested column within the passed matrix, regardless of its major order. </summary>
	/// <typeparam name="Matrix_">type of EmuMath matrix to return the requested column of.</typeparam>
	/// <param name="matrix_">EmuMath matrix to return the requested column of.</param>
	/// <returns>EmuMath reference vector which may be used to interact with a column in the passed matrix regardless of its major order.</returns>
	template<std::size_t Index_, class Matrix_>
	constexpr inline auto MatrixGetColumn(Matrix_& matrix_)
	{
		if constexpr (EmuMath::TMP::is_emu_matrix_v<Matrix_>)
		{
			if constexpr (Index_ < Matrix_::num_columns)
			{
				return _underlying_matrix_funcs::_get_matrix_column<Index_, Matrix_>(matrix_);
			}
			else
			{
				static_assert(false, "Attempted to get a column from an EmuMath matrix using an invalid column index.");
			}
		}
		else
		{
			static_assert(false, "Attempted to get a column from a matrix, but the provided argument was not an EmuMath matrix.");
		}
	}
	template<std::size_t Index_, class Matrix_>
	constexpr inline auto MatrixGetColumn(const Matrix_& matrix_)
	{
		if constexpr (EmuMath::TMP::is_emu_matrix_v<Matrix_>)
		{
			if constexpr (Index_ < Matrix_::num_columns)
			{
				return _underlying_matrix_funcs::_get_matrix_column<Index_, const Matrix_>(matrix_);
			}
			else
			{
				static_assert(false, "Attempted to get a column from an EmuMath matrix using an invalid column index.");
			}
		}
		else
		{
			static_assert(false, "Attempted to get a column from a matrix, but the provided argument was not an EmuMath matrix.");
		}
	}

	/// <summary> Returns a vector which references the requested row within the passed matrix, regardless of its major order. </summary>
	/// <typeparam name="Matrix_">type of EmuMath matrix to return the requested row of.</typeparam>
	/// <param name="matrix_">EmuMath matrix to return the requested row of.</param>
	/// <returns>EmuMath reference vector which may be used to interact with a row in the passed matrix regardless of its major order.</returns>
	template<std::size_t Index_, class Matrix_>
	constexpr inline auto MatrixGetRow(Matrix_& matrix_)
	{
		if constexpr (EmuMath::TMP::is_emu_matrix_v<Matrix_>)
		{
			if constexpr (Index_ < Matrix_::num_rows)
			{
				return _underlying_matrix_funcs::_get_matrix_row<Index_, Matrix_>(matrix_);
			}
			else
			{
				static_assert(false, "Attempted to get a row from an EmuMath matrix using an invalid row index.");
			}
		}
		else
		{
			static_assert(false, "Attempted to get a row from a matrix, but the provided argument was not an EmuMath matrix.");
		}
	}
	template<std::size_t Index_, class Matrix_>
	constexpr inline auto MatrixGetRow(const Matrix_& matrix_)
	{
		if constexpr (EmuMath::TMP::is_emu_matrix_v<Matrix_>)
		{
			if constexpr (Index_ < Matrix_::num_rows)
			{
				return _underlying_matrix_funcs::_get_matrix_row<Index_, const Matrix_>(matrix_);
			}
			else
			{
				static_assert(false, "Attempted to get a row from an EmuMath matrix using an invalid row index.");
			}
		}
		else
		{
			static_assert(false, "Attempted to get a row from a matrix, but the provided argument was not an EmuMath matrix.");
		}
	}

	template<std::size_t ColumnIndex_, std::size_t RowIndex_, class Matrix_>
	constexpr inline typename EmuMath::TMP::emu_matrix_theoretical_data<ColumnIndex_, RowIndex_, Matrix_>::type MatrixGetTheoretical(const Matrix_& matrix_)
	{
		if constexpr (EmuMath::TMP::is_emu_matrix_v<Matrix_>)
		{
			return _underlying_matrix_funcs::_get_matrix_theoretical_data<ColumnIndex_, RowIndex_, Matrix_>(matrix_);
		}
		else
		{
			static_assert(false, "Attempted to get the theoretical value of an index within a matrix, but the provided argument was not an EmuMath matrix.");
		}
	}
	template<std::size_t MajorOrderIndex_, class Matrix_>
	constexpr inline typename EmuMath::TMP::emu_matrix_theoretical_major_order_index_data<MajorOrderIndex_, Matrix_>::type MatrixGetTheoretical(const Matrix_& matrix_)
	{
		if constexpr (EmuMath::TMP::is_emu_matrix_v<Matrix_>)
		{
			return _underlying_matrix_funcs::_get_matrix_theoretical_data<MajorOrderIndex_, Matrix_>(matrix_);
		}
		else
		{
			static_assert(false, "Attempted to get the theoretical value of an index within a matrix, but the provided argument was not an EmuMath matrix.");
		}
	}
#pragma endregion

	// These reinterpretations are specifically those related to matrices, that would only act as pointless noise if included without matrices.
#pragma region VECTOR_REINTERPRETATIONS
	/// <summary>
	/// <para> Converts the passed EmuMath vector to an EmuMath matrix as though it represents a single column. </para>
	/// <para>
	///		The vector data will be stored as columns regardless of the ColumnMajor_ argument. 
	///		To store the vector as a row matrix instead, use VectorToRowMatrix.
	/// </para>
	/// </summary>
	/// <typeparam name="Vector_">Type of EmuMath vector to convert to a column matrix.</typeparam>
	/// <typeparam name="out_contained_type">Type to be contained within the output matrix.</typeparam>
	/// <param name="vector_">EmuMath vector to convert to a column matrix.</param>
	/// <returns>Column matrix containing a copy of the passed vector's data. The matrix will be a single column which contains the full data of the passed vector.</returns>
	template<typename out_contained_type, bool ColumnMajor_ = true, class Vector_>
	constexpr inline EmuMath::Matrix<1, Vector_::size, out_contained_type, ColumnMajor_> VectorToColumnMatrix(const Vector_& vector_)
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
	constexpr inline EmuMath::Matrix<1, Vector_::size, typename Vector_::value_type, ColumnMajor_> VectorToColumnMatrix(const Vector_& vector_)
	{
		return VectorToColumnMatrix<typename Vector_::value_type, ColumnMajor_, Vector_>(vector_);
	}

	/// <summary>
	/// <para> Converts the passed EmuMath vector to an EmuMath matrix as though it represents a single row. </para>
	/// <para>
	///		The vector data will be stored as rows regardless of the ColumnMajor_ argument. 
	///		To store the vector as a column matrix instead, use VectorToColumnMatrix.
	/// </para>
	/// </summary>
	/// <typeparam name="Vector_">Type of EmuMath vector to convert to a row matrix.</typeparam>
	/// <typeparam name="out_contained_type">Type to be contained within the output matrix.</typeparam>
	/// <param name="vector_">EmuMath vector to convert to a row matrix.</param>
	/// <returns>Row matrix containing a copy of the passed vector's data. The matrix will be a single row which contains the full data of the passed vector.</returns>
	template<typename out_contained_type, bool ColumnMajor_ = true, class Vector_>
	constexpr inline EmuMath::Matrix<Vector_::size, 1, out_contained_type, ColumnMajor_> VectorToRowMatrix(const Vector_& vector_)
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
	constexpr inline EmuMath::Matrix<Vector_::size, 1, typename Vector_::value_type, ColumnMajor_> VectorToRowMatrix(const Vector_& vector_)
	{
		return VectorToRowMatrix<typename Vector_::value_type, ColumnMajor_, Vector_>(vector_);
	}

	/// <summary>
	/// <para> Creates an EmuMath vector one item larger than the passed vector, containing a copy of the passed vector_ in existing indices and 1 in the new index. </para>
	/// <para> This process allows an X-dimensional vector to be transformed by an (X+1)x(X+1) transformation matrix. </para>
	/// </summary>
	/// <typeparam name="out_contained_type">Type to be contained within the output vector.</typeparam>
	/// <typeparam name="Vector_">Type of EmuMath vector to prepare for transformation.</typeparam>
	/// <param name="vector_">EmuMath vector to prepare for transformation.</param>
	/// <returns>Copy of the provided vector_, with one additional element appended to the end set to 1.</returns>
	template<typename out_contained_type, class Vector_>
	constexpr inline EmuMath::Vector<Vector_::size + 1, out_contained_type> VectorPrepareToTransform(const Vector_& vector_)
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
	constexpr inline EmuMath::Vector<Vector_::size + 1, typename Vector_::value_type> VectorPrepareToTransform(const Vector_& vector_)
	{
		return VectorPrepareToTransform<typename Vector_::value_type, Vector_>(vector_);
	}
#pragma endregion

#pragma region ARITHMETIC
	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename out_contained_type, bool OutColumnMajor_, class LhsMatrix_, class Rhs_, class Func_>
	constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, out_contained_type, OutColumnMajor_> MatrixLhsRhsOperation
	(
		const LhsMatrix_& lhs_,
		const Rhs_& rhs_,
		Func_ func_
	)
	{
		if constexpr (EmuMath::TMP::is_emu_matrix_v<LhsMatrix_>)
		{
			return _underlying_matrix_funcs::_matrix_lhs_rhs_operation
			<
				EmuMath::Matrix<OutNumColumns_, OutNumRows_, out_contained_type, OutColumnMajor_>,
				LhsMatrix_,
				Rhs_,
				Func_&
			>(lhs_, rhs_, func_);
		}
		else
		{
			static_assert(false, "Attempting to perform an operation on an EmuMath matrix which takes a rhs_ argument, but the lhs_ argument was not an EmuMath matrix.");
		}
	}
	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename out_contained_type, bool OutColumnMajor_, class LhsMatrix_, class Rhs_, class Func_>
	constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, out_contained_type, OutColumnMajor_> MatrixLhsRhsOperation
	(
		const LhsMatrix_& lhs_,
		const Rhs_& rhs_
	)
	{
		Func_ func_ = Func_();
		return MatrixLhsRhsOperation<OutNumColumns_, OutNumRows_, out_contained_type, OutColumnMajor_, LhsMatrix_, Rhs_, Func_&>(lhs_, rhs_, func_);
	}
	template<typename out_contained_type, bool OutColumnMajor_ , class LhsMatrix_, class Rhs_, class Func_>
	constexpr inline EmuMath::Matrix<LhsMatrix_::num_columns, LhsMatrix_::num_rows, out_contained_type, OutColumnMajor_> MatrixLhsRhsOperation
	(
		const LhsMatrix_& lhs_,
		const Rhs_& rhs_,
		Func_ func_
	)
	{
		return MatrixLhsRhsOperation<LhsMatrix_::num_columns, LhsMatrix_::num_rows, out_contained_type, OutColumnMajor_, LhsMatrix_, Rhs_, Func_&>(lhs_, rhs_, func_);
	}
	template<typename out_contained_type, bool OutColumnMajor_, class LhsMatrix_, class Rhs_, class Func_>
	constexpr inline EmuMath::Matrix<LhsMatrix_::num_columns, LhsMatrix_::num_rows, out_contained_type, OutColumnMajor_> MatrixLhsRhsOperation
	(
		const LhsMatrix_& lhs_,
		const Rhs_& rhs_
	)
	{
		return MatrixLhsRhsOperation<LhsMatrix_::num_columns, LhsMatrix_::num_rows, out_contained_type, OutColumnMajor_, LhsMatrix_, Rhs_, Func_>(lhs_, rhs_);
	}
	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, bool OutColumnMajor_, class LhsMatrix_, class Rhs_, class Func_>
	constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, typename LhsMatrix_::value_type, OutColumnMajor_> MatrixLhsRhsOperation
	(
		const LhsMatrix_& lhs_,
		const Rhs_& rhs_,
		Func_ func_
	)
	{
		return MatrixLhsRhsOperation<OutNumColumns_, OutNumRows_, typename LhsMatrix_::value_type, OutColumnMajor_, LhsMatrix_, rhs_, Func_&>(lhs_, rhs_, func_);
	}
	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, bool OutColumnMajor_, class LhsMatrix_, class Rhs_, class Func_>
	constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, typename LhsMatrix_::value_type, OutColumnMajor_> MatrixLhsRhsOperation
	(
		const LhsMatrix_& lhs_,
		const Rhs_& rhs_
	)
	{
		return MatrixLhsRhsOperation<OutNumColumns_, OutNumRows_, typename LhsMatrix_::value_type, OutColumnMajor_, LhsMatrix_, rhs_, Func_>(lhs_, rhs_);
	}
	template<bool OutColumnMajor_, class LhsMatrix_, class Rhs_, class Func_>
	constexpr inline EmuMath::Matrix<LhsMatrix_::num_columns, LhsMatrix_::num_rows, typename LhsMatrix_::value_type, OutColumnMajor_> MatrixLhsRhsOperation
	(
		const LhsMatrix_& lhs_,
		const Rhs_& rhs_,
		Func_ func_
	)
	{
		return MatrixLhsRhsOperation<LhsMatrix_::num_columns, LhsMatrix_::num_rows, typename LhsMatrix_::value_type, OutColumnMajor_, LhsMatrix_, Rhs_, Func_&>
		(
			lhs_,
			rhs_,
			func_
		);
	}
	template<bool OutColumnMajor_, class LhsMatrix_, class Rhs_, class Func_>
	constexpr inline EmuMath::Matrix<LhsMatrix_::num_columns, LhsMatrix_::num_rows, typename LhsMatrix_::value_type, OutColumnMajor_> MatrixLhsRhsOperation
	(
		const LhsMatrix_& lhs_,
		const Rhs_& rhs_
	)
	{
		return MatrixLhsRhsOperation<LhsMatrix_::num_columns, LhsMatrix_::num_rows, typename LhsMatrix_::value_type, OutColumnMajor_, LhsMatrix_, Rhs_, Func_>
		(
			lhs_,
			rhs_
		);
	}
	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename out_contained_type, class LhsMatrix_, class Rhs_, class Func_>
	constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, out_contained_type, LhsMatrix_::is_column_major> MatrixLhsRhsOperation
	(
		const LhsMatrix_& lhs_,
		const Rhs_& rhs_,
		Func_ func_
	)
	{
		return MatrixLhsRhsOperation<OutNumColumns_, OutNumColumns_, out_contained_type, LhsMatrix_::is_column_major, LhsMatrix_, Rhs_, Func_&>(lhs_, rhs_, func_);
	}
	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename out_contained_type, class LhsMatrix_, class Rhs_, class Func_>
	constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, out_contained_type, LhsMatrix_::is_column_major> MatrixLhsRhsOperation
	(
		const LhsMatrix_& lhs_,
		const Rhs_& rhs_
	)
	{
		return MatrixLhsRhsOperation<OutNumColumns_, OutNumRows_, out_contained_type, LhsMatrix_::is_column_major, LhsMatrix_, Rhs_, Func_>(lhs_, rhs_);
	}
	template<typename out_contained_type, class LhsMatrix_, class Rhs_, class Func_>
	constexpr inline EmuMath::Matrix<LhsMatrix_::num_columns, LhsMatrix_::num_rows, out_contained_type, LhsMatrix_::is_column_major> MatrixLhsRhsOperation
	(
		const LhsMatrix_& lhs_,
		const Rhs_& rhs_,
		Func_ func_
	)
	{
		return MatrixLhsRhsOperation<LhsMatrix_::num_columns, LhsMatrix_::num_rows, out_contained_type, LhsMatrix_::is_column_major, LhsMatrix_, Rhs_, Func_&>
		(
			lhs_,
			rhs_,
			func_
		);
	}
	template<typename out_contained_type, class LhsMatrix_, class Rhs_, class Func_>
	constexpr inline EmuMath::Matrix<LhsMatrix_::num_columns, LhsMatrix_::num_rows, out_contained_type, LhsMatrix_::is_column_major> MatrixLhsRhsOperation
	(
		const LhsMatrix_& lhs_,
		const Rhs_& rhs_
	)
	{
		return MatrixLhsRhsOperation<LhsMatrix_::num_columns, LhsMatrix_::num_rows, out_contained_type, LhsMatrix_::is_column_major, LhsMatrix_, Rhs_, Func_>
		(
			lhs_,
			rhs_
		);
	}
	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, class LhsMatrix_, class Rhs_, class Func_>
	constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, typename LhsMatrix_::value_type, LhsMatrix_::is_column_major> MatrixLhsRhsOperation
	(
		const LhsMatrix_& lhs_,
		const Rhs_& rhs_,
		Func_ func_
	)
	{
		return MatrixLhsRhsOperation<OutNumColumns_, OutNumRows_, typename LhsMatrix_::value_type, LhsMatrix_::is_column_major, LhsMatrix_, Rhs_, Func_&>
		(
			lhs_,
			rhs_,
			func_
		);
	}
	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, class LhsMatrix_, class Rhs_, class Func_>
	constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, typename LhsMatrix_::value_type, LhsMatrix_::is_column_major> MatrixLhsRhsOperation
	(
		const LhsMatrix_& lhs_,
		const Rhs_& rhs_
	)
	{
		return MatrixLhsRhsOperation<OutNumColumns_, OutNumRows_, typename LhsMatrix_::value_type, LhsMatrix_::is_column_major, LhsMatrix_, Rhs_, Func_>
		(
			lhs_,
			rhs_
		);
	}
	template<class LhsMatrix_, class Rhs_, class Func_>
	constexpr inline EmuMath::Matrix<LhsMatrix_::num_columns, LhsMatrix_::num_rows, typename LhsMatrix_::value_type, LhsMatrix_::is_column_major> MatrixLhsRhsOperation
	(
		const LhsMatrix_& lhs_,
		const Rhs_& rhs_,
		Func_ func_
	)
	{
		return MatrixLhsRhsOperation<LhsMatrix_::num_columns, LhsMatrix_::num_rows, typename LhsMatrix_::value_type, LhsMatrix_::is_column_major, LhsMatrix_, Rhs_, Func_&>
		(
			lhs_,
			rhs_,
			func_
		);
	}
	template<class LhsMatrix_, class Rhs_, class Func_>
	constexpr inline EmuMath::Matrix<LhsMatrix_::num_columns, LhsMatrix_::num_rows, typename LhsMatrix_::value_type, LhsMatrix_::is_column_major> MatrixLhsRhsOperation
	(
		const LhsMatrix_& lhs_,
		const Rhs_& rhs_
	)
	{
		return MatrixLhsRhsOperation<LhsMatrix_::num_columns, LhsMatrix_::num_rows, typename LhsMatrix_::value_type, LhsMatrix_::is_column_major, LhsMatrix_, Rhs_, Func_>
		(
			lhs_,
			rhs_
		);
	}

	/// <summary>
	/// <para> Performs an addition operation on the passed lhs_ matrix using the passed rhs_. </para>
	/// <para> If the passed rhs_ is a matrix, respective indices in each matrix will be added. Otherwise, each index in the lhs_ matrix will have Rhs_ added to it. </para>
	/// <para> Additions are performed using EmuCore::do_add&lt;LhsMatrix_::value_type, Rhs_ (or Rhs_::value_type if it is a matrix)&gt;. </para>
	/// </summary>
	/// <typeparam name="out_contained_type">Type to be contained within the result matrix.</typeparam>
	/// <typeparam name="LhsMatrix_">Type of matrix appearing on the left-hand side of addition.</typeparam>
	/// <typeparam name="Rhs_">Type of matrix or scalar appearing on the right-hand side of addition.</typeparam>
	/// <param name="lhs_">EmuMath matrix appearing on the left-hand side of addition.</param>
	/// <param name="rhs_">EmuMath matrix or scalar appearing on the right-hand side of addition.</param>
	/// <returns>Matrix containing the results of adding rhs_ to the lhs_ matrix.</returns>
	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename out_contained_type, bool OutColumnMajor_, class LhsMatrix_, class Rhs_>
	constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, out_contained_type, OutColumnMajor_> MatrixAdd(const LhsMatrix_& lhs_, const Rhs_& rhs_)
	{
		if constexpr (EmuMath::TMP::is_emu_matrix_v<LhsMatrix_>)
		{
			if constexpr (EmuMath::TMP::is_emu_matrix_v<Rhs_>)
			{
				using adder_type = EmuCore::do_add<typename LhsMatrix_::value_type, typename Rhs_::value_type>;
				return _underlying_matrix_funcs::_matrix_lhs_rhs_operation
				<
					EmuMath::Matrix<OutNumColumns_, OutNumRows_, out_contained_type, OutColumnMajor_>,
					LhsMatrix_,
					Rhs_,
					adder_type
				>(lhs_, rhs_);
			}
			else
			{
				using adder_type = EmuCore::do_add<typename LhsMatrix_::value_type, Rhs_>;
				return _underlying_matrix_funcs::_matrix_lhs_rhs_operation
				<
					EmuMath::Matrix<OutNumColumns_, OutNumRows_, out_contained_type, OutColumnMajor_>,
					LhsMatrix_,
					Rhs_,
					adder_type
				>(lhs_, rhs_);
			}
		}
		else
		{
			static_assert(false, "Attempted to perform matrix addition, but provided a non-EmuMath-matrix lhs_ argument.");
		}
	}
	template<typename out_contained_type, bool OutColumnMajor_, class LhsMatrix_, class Rhs_>
	constexpr inline EmuMath::Matrix<LhsMatrix_::num_columns, LhsMatrix_::num_rows, out_contained_type, OutColumnMajor_> MatrixAdd(const LhsMatrix_& lhs_, const Rhs_& rhs_)
	{
		return MatrixAdd<LhsMatrix_::num_columns, LhsMatrix_::num_rows, out_contained_type, OutColumnMajor_, LhsMatrix_, Rhs_>(lhs_, rhs_);
	}
	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, bool OutColumnMajor_, class LhsMatrix_, class Rhs_>
	constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, typename LhsMatrix_::value_type, OutColumnMajor_> MatrixAdd(const LhsMatrix_& lhs_, const Rhs_& rhs_)
	{
		return MatrixAdd<OutNumColumns_, OutNumRows_, typename LhsMatrix_::value_type, OutColumnMajor_, LhsMatrix_, Rhs_>(lhs_, rhs_);
	}
	template<bool OutColumnMajor_, class LhsMatrix_, class Rhs_>
	constexpr inline EmuMath::Matrix<LhsMatrix_::num_columns, LhsMatrix_::num_rows, typename LhsMatrix_::value_type, OutColumnMajor_> MatrixAdd
	(
		const LhsMatrix_& lhs_,
		const Rhs_& rhs_
	)
	{
		return MatrixAdd<LhsMatrix_::num_columns, LhsMatrix_::num_rows, typename LhsMatrix_::value_type, OutColumnMajor_, LhsMatrix_, Rhs_>(lhs_, rhs_);
	}

	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename out_contained_type, class LhsMatrix_, class Rhs_>
	constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, out_contained_type, LhsMatrix_::is_column_major> MatrixAdd(const LhsMatrix_& lhs_, const Rhs_& rhs_)
	{
		return MatrixAdd<OutNumColumns_, OutNumRows_, out_contained_type, LhsMatrix_::is_column_major, LhsMatrix_, Rhs_>(lhs_, rhs_);
	}
	template<typename out_contained_type, class LhsMatrix_, class Rhs_>
	constexpr inline EmuMath::Matrix<LhsMatrix_::num_columns, LhsMatrix_::num_rows, out_contained_type, LhsMatrix_::is_column_major> MatrixAdd
	(
		const LhsMatrix_& lhs_,
		const Rhs_& rhs_
	)
	{
		return MatrixAdd<LhsMatrix_::num_columns, LhsMatrix_::num_rows, out_contained_type, LhsMatrix_::is_column_major, LhsMatrix_, Rhs_>(lhs_, rhs_);
	}
	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, class LhsMatrix_, class Rhs_>
	constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, typename LhsMatrix_::value_type, LhsMatrix_::is_column_major> MatrixAdd
	(
		const LhsMatrix_& lhs_,
		const Rhs_& rhs_
	)
	{
		return MatrixAdd<OutNumColumns_, OutNumRows_, typename LhsMatrix_::value_type, LhsMatrix_::is_column_major, LhsMatrix_, Rhs_>(lhs_, rhs_);
	}
	template<class LhsMatrix_, class Rhs_>
	constexpr inline EmuMath::Matrix<LhsMatrix_::num_columns, LhsMatrix_::num_rows, typename LhsMatrix_::value_type, LhsMatrix_::is_column_major> MatrixAdd
	(
		const LhsMatrix_& lhs_,
		const Rhs_& rhs_
	)
	{
		return MatrixAdd<LhsMatrix_::num_columns, LhsMatrix_::num_rows, typename LhsMatrix_::value_type, LhsMatrix_::is_column_major, LhsMatrix_, Rhs_>(lhs_, rhs_);
	}

	/// <summary>
	/// <para> Performs an subtraction operation on the passed lhs_ matrix using the passed rhs_. </para>
	/// <para>
	///		If the passed rhs_ is a matrix, respective indices in each matrix will be subtracted. 
	/// Otherwise, each index in the lhs_ matrix will have Rhs_ subtracted from it.
	/// </para>
	/// <para> Subtractions are performed using EmuCore::do_subtract&lt;LhsMatrix_::value_type, Rhs_ (or Rhs_::value_type if it is a matrix)&gt;. </para>
	/// </summary>
	/// <typeparam name="out_contained_type">Type to be contained within the result matrix.</typeparam>
	/// <typeparam name="LhsMatrix_">Type of matrix appearing on the left-hand side of subtraction.</typeparam>
	/// <typeparam name="Rhs_">Type of matrix or scalar appearing on the right-hand side of subtraction.</typeparam>
	/// <param name="lhs_">EmuMath matrix appearing on the left-hand side of subtraction.</param>
	/// <param name="rhs_">EmuMath matrix or scalar appearing on the right-hand side of subtraction.</param>
	/// <returns>Matrix containing the results of subtracting rhs_ from the lhs_ matrix.</returns>
	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename out_contained_type, bool OutColumnMajor_, class LhsMatrix_, class Rhs_>
	constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, out_contained_type, OutColumnMajor_> MatrixSubtract(const LhsMatrix_& lhs_, const Rhs_& rhs_)
	{
		if constexpr (EmuMath::TMP::is_emu_matrix_v<LhsMatrix_>)
		{
			if constexpr (EmuMath::TMP::is_emu_matrix_v<Rhs_>)
			{
				using subtractor_type = EmuCore::do_subtract<typename LhsMatrix_::value_type, typename Rhs_::value_type>;
				return _underlying_matrix_funcs::_matrix_lhs_rhs_operation
				<
					EmuMath::Matrix<OutNumColumns_, OutNumRows_, out_contained_type, OutColumnMajor_>,
					LhsMatrix_,
					Rhs_,
					subtractor_type
				>(lhs_, rhs_);
			}
			else
			{
				using subtractor_type = EmuCore::do_subtract<typename LhsMatrix_::value_type, Rhs_>;
				return _underlying_matrix_funcs::_matrix_lhs_rhs_operation
				<
					EmuMath::Matrix<OutNumColumns_, OutNumRows_, out_contained_type, OutColumnMajor_>,
					LhsMatrix_,
					Rhs_,
					subtractor_type
				>(lhs_, rhs_);
			}
		}
		else
		{
			static_assert(false, "Attempted to perform matrix subtraction, but provided a non-EmuMath-matrix lhs_ argument.");
		}
	}
	template<typename out_contained_type, bool OutColumnMajor_, class LhsMatrix_, class Rhs_>
	constexpr inline EmuMath::Matrix<LhsMatrix_::num_columns, LhsMatrix_::num_rows, out_contained_type, OutColumnMajor_> MatrixSubtract(const LhsMatrix_& lhs_, const Rhs_& rhs_)
	{
		return MatrixSubtract<LhsMatrix_::num_columns, LhsMatrix_::num_rows, out_contained_type, OutColumnMajor_, LhsMatrix_, Rhs_>(lhs_, rhs_);
	}
	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, bool OutColumnMajor_, class LhsMatrix_, class Rhs_>
	constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, typename LhsMatrix_::value_type, OutColumnMajor_> MatrixSubtract(const LhsMatrix_& lhs_, const Rhs_& rhs_)
	{
		return MatrixSubtract<OutNumColumns_, OutNumRows_, typename LhsMatrix_::value_type, OutColumnMajor_, LhsMatrix_, Rhs_>(lhs_, rhs_);
	}
	template<bool OutColumnMajor_, class LhsMatrix_, class Rhs_>
	constexpr inline EmuMath::Matrix<LhsMatrix_::num_columns, LhsMatrix_::num_rows, typename LhsMatrix_::value_type, OutColumnMajor_> MatrixSubtract
	(
		const LhsMatrix_& lhs_,
		const Rhs_& rhs_
	)
	{
		return MatrixSubtract<LhsMatrix_::num_columns, LhsMatrix_::num_rows, typename LhsMatrix_::value_type, OutColumnMajor_, LhsMatrix_, Rhs_>(lhs_, rhs_);
	}

	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename out_contained_type, class LhsMatrix_, class Rhs_>
	constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, out_contained_type, LhsMatrix_::is_column_major> MatrixSubtract(const LhsMatrix_& lhs_, const Rhs_& rhs_)
	{
		return MatrixSubtract<OutNumColumns_, OutNumRows_, out_contained_type, LhsMatrix_::is_column_major, LhsMatrix_, Rhs_>(lhs_, rhs_);
	}
	template<typename out_contained_type, class LhsMatrix_, class Rhs_>
	constexpr inline EmuMath::Matrix<LhsMatrix_::num_columns, LhsMatrix_::num_rows, out_contained_type, LhsMatrix_::is_column_major> MatrixSubtract
	(
		const LhsMatrix_& lhs_,
		const Rhs_& rhs_
	)
	{
		return MatrixSubtract<LhsMatrix_::num_columns, LhsMatrix_::num_rows, out_contained_type, LhsMatrix_::is_column_major, LhsMatrix_, Rhs_>(lhs_, rhs_);
	}
	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, class LhsMatrix_, class Rhs_>
	constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, typename LhsMatrix_::value_type, LhsMatrix_::is_column_major> MatrixSubtract
	(
		const LhsMatrix_& lhs_,
		const Rhs_& rhs_
	)
	{
		return MatrixSubtract<OutNumColumns_, OutNumRows_, typename LhsMatrix_::value_type, LhsMatrix_::is_column_major, LhsMatrix_, Rhs_>(lhs_, rhs_);
	}
	template<class LhsMatrix_, class Rhs_>
	constexpr inline EmuMath::Matrix<LhsMatrix_::num_columns, LhsMatrix_::num_rows, typename LhsMatrix_::value_type, LhsMatrix_::is_column_major> MatrixSubtract
	(
		const LhsMatrix_& lhs_,
		const Rhs_& rhs_
	)
	{
		return MatrixSubtract<LhsMatrix_::num_columns, LhsMatrix_::num_rows, typename LhsMatrix_::value_type, LhsMatrix_::is_column_major, LhsMatrix_, Rhs_>(lhs_, rhs_);
	}

	/// <summary>
	/// <para> Performs a basic multiplication operation on lhs_ using the passed rhs_. </para>
	/// <para>
	///		If the passed rhs_ is a matrix, respective indices in each matrix will be multiplied. 
	///		Otherwise, each index in the lhs_ matrix will be multiplied by rhs_.
	/// </para>
	/// <para> Multiplications are performed using EmuCore::do_multiply&lt;LhsMatrix_::value_type, Rhs_ (or Rhs_::value_type if it is a matrix)&gt;. </para>
	/// <para> NOTE: This is NOT a standard matrix multiplication operation. For such behaviour, use MatrixMultiply instead. </para>
	/// </summary>
	/// <typeparam name="out_contained_type">Type to be contained within the result matrix.</typeparam>
	/// <typeparam name="LhsMatrix_">Type of matrix appearing on the left-hand side of multiplication.</typeparam>
	/// <typeparam name="Rhs_">Type of matrix or scalar appearing on the right-hand side of multiplication.</typeparam>
	/// <param name="lhs_">EmuMath matrix appearing on the left-hand side of multiplication.</param>
	/// <param name="rhs_">EmuMath matrix or scalar appearing on the right-hand side of multiplication.</param>
	/// <returns>Matrix containing the results of performing a basic multiplication on the lhs_ matrix by the provided rhs_.</returns>
	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename out_contained_type, bool OutColumnMajor_, class LhsMatrix_, class Rhs_>
	constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, out_contained_type, OutColumnMajor_> MatrixMultiplyBasic(const LhsMatrix_& lhs_, const Rhs_& rhs_)
	{
		if constexpr (EmuMath::TMP::is_emu_matrix_v<LhsMatrix_>)
		{
			if constexpr (EmuMath::TMP::is_emu_matrix_v<Rhs_>)
			{
				using multiplier_type = EmuCore::do_multiply<typename LhsMatrix_::value_type, typename Rhs_::value_type>;
				return _underlying_matrix_funcs::_matrix_lhs_rhs_operation
				<
					EmuMath::Matrix<OutNumColumns_, OutNumRows_, out_contained_type, OutColumnMajor_>,
					LhsMatrix_,
					Rhs_,
					multiplier_type
				>(lhs_, rhs_);
			}
			else
			{
				using multiplier_type = EmuCore::do_multiply<typename LhsMatrix_::value_type, Rhs_>;
				return _underlying_matrix_funcs::_matrix_lhs_rhs_operation
				<
					EmuMath::Matrix<OutNumColumns_, OutNumRows_, out_contained_type, OutColumnMajor_>,
					LhsMatrix_,
					Rhs_,
					multiplier_type
				>(lhs_, rhs_);
			}
		}
		else
		{
			static_assert(false, "Attempted to perform basic matrix multiplication, but provided a non-EmuMath-matrix lhs_ argument.");
		}
	}
	template<typename out_contained_type, bool OutColumnMajor_, class LhsMatrix_, class Rhs_>
	constexpr inline EmuMath::Matrix<LhsMatrix_::num_columns, LhsMatrix_::num_rows, out_contained_type, OutColumnMajor_> MatrixMultiplyBasic
	(
		const LhsMatrix_& lhs_,
		const Rhs_& rhs_
	)
	{
		return MatrixMultiplyBasic<LhsMatrix_::num_columns, LhsMatrix_::num_rows, out_contained_type, OutColumnMajor_, LhsMatrix_, Rhs_>(lhs_, rhs_);
	}
	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, bool OutColumnMajor_, class LhsMatrix_, class Rhs_>
	constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, typename LhsMatrix_::value_type, OutColumnMajor_> MatrixMultiplyBasic
	(
		const LhsMatrix_& lhs_,
		const Rhs_& rhs_
	)
	{
		return MatrixMultiplyBasic<OutNumColumns_, OutNumRows_, typename LhsMatrix_::value_type, OutColumnMajor_, LhsMatrix_, Rhs_>(lhs_, rhs_);
	}
	template<bool OutColumnMajor_, class LhsMatrix_, class Rhs_>
	constexpr inline EmuMath::Matrix<LhsMatrix_::num_columns, LhsMatrix_::num_rows, typename LhsMatrix_::value_type, OutColumnMajor_> MatrixMultiplyBasic
	(
		const LhsMatrix_& lhs_,
		const Rhs_& rhs_
	)
	{
		return MatrixMultiplyBasic<LhsMatrix_::num_columns, LhsMatrix_::num_rows, typename LhsMatrix_::value_type, OutColumnMajor_, LhsMatrix_, Rhs_>(lhs_, rhs_);
	}

	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename out_contained_type, class LhsMatrix_, class Rhs_>
	constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, out_contained_type, LhsMatrix_::is_column_major> MatrixMultiplyBasic(const LhsMatrix_& lhs_, const Rhs_& rhs_)
	{
		return MatrixMultiplyBasic<OutNumColumns_, OutNumRows_, out_contained_type, LhsMatrix_::is_column_major, LhsMatrix_, Rhs_>(lhs_, rhs_);
	}
	template<typename out_contained_type, class LhsMatrix_, class Rhs_>
	constexpr inline EmuMath::Matrix<LhsMatrix_::num_columns, LhsMatrix_::num_rows, out_contained_type, LhsMatrix_::is_column_major> MatrixMultiplyBasic
	(
		const LhsMatrix_& lhs_,
		const Rhs_& rhs_
	)
	{
		return MatrixMultiplyBasic<LhsMatrix_::num_columns, LhsMatrix_::num_rows, out_contained_type, LhsMatrix_::is_column_major, LhsMatrix_, Rhs_>(lhs_, rhs_);
	}
	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, class LhsMatrix_, class Rhs_>
	constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, typename LhsMatrix_::value_type, LhsMatrix_::is_column_major> MatrixMultiplyBasic
	(
		const LhsMatrix_& lhs_,
		const Rhs_& rhs_
	)
	{
		return MatrixMultiplyBasic<OutNumColumns_, OutNumRows_, typename LhsMatrix_::value_type, LhsMatrix_::is_column_major, LhsMatrix_, Rhs_>(lhs_, rhs_);
	}
	template<class LhsMatrix_, class Rhs_>
	constexpr inline EmuMath::Matrix<LhsMatrix_::num_columns, LhsMatrix_::num_rows, typename LhsMatrix_::value_type, LhsMatrix_::is_column_major> MatrixMultiplyBasic
	(
		const LhsMatrix_& lhs_,
		const Rhs_& rhs_
	)
	{
		return MatrixMultiplyBasic<LhsMatrix_::num_columns, LhsMatrix_::num_rows, typename LhsMatrix_::value_type, LhsMatrix_::is_column_major, LhsMatrix_, Rhs_>(lhs_, rhs_);
	}

	/// <summary>
	/// <para> Performs a basic division operation on lhs_ using the passed rhs_. </para>
	/// <para>
	///		If the passed rhs_ is a matrix, respective indices in each matrix will be divided. 
	///		Otherwise, each index in the lhs_ matrix will be divided by rhs_.
	/// </para>
	/// <para> Divisions are performed using EmuCore::do_divide&lt;LhsMatrix_::value_type, Rhs_ (or Rhs_::value_type if it is a matrix)&gt;. </para>
	/// <para> NOTE: This is NOT a standard matrix division operation. Such behaviour is mathematically undefined. </para>
	/// </summary>
	/// <typeparam name="out_contained_type">Type to be contained within the result matrix.</typeparam>
	/// <typeparam name="LhsMatrix_">Type of matrix appearing on the left-hand side of division.</typeparam>
	/// <typeparam name="Rhs_">Type of matrix or scalar appearing on the right-hand side of division.</typeparam>
	/// <param name="lhs_">EmuMath matrix appearing on the left-hand side of division.</param>
	/// <param name="rhs_">EmuMath matrix or scalar appearing on the right-hand side of division.</param>
	/// <returns>Matrix containing the results of performing a basic division on the lhs_ matrix by the provided rhs_.</returns>
	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename out_contained_type, bool OutColumnMajor_, class LhsMatrix_, class Rhs_>
	constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, out_contained_type, OutColumnMajor_> MatrixDivideBasic(const LhsMatrix_& lhs_, const Rhs_& rhs_)
	{
		if constexpr (EmuMath::TMP::is_emu_matrix_v<LhsMatrix_>)
		{
			if constexpr (EmuMath::TMP::is_emu_matrix_v<Rhs_>)
			{
				using divider_type = EmuCore::do_divide<typename LhsMatrix_::value_type, typename Rhs_::value_type>;
				return _underlying_matrix_funcs::_matrix_lhs_rhs_operation
				<
					EmuMath::Matrix<OutNumColumns_, OutNumRows_, out_contained_type, OutColumnMajor_>,
					LhsMatrix_,
					Rhs_,
					divider_type
				>(lhs_, rhs_);
			}
			else
			{
				using divider_type = EmuCore::do_divide<typename LhsMatrix_::value_type, Rhs_>;
				return _underlying_matrix_funcs::_matrix_lhs_rhs_operation
				<
					EmuMath::Matrix<OutNumColumns_, OutNumRows_, out_contained_type, OutColumnMajor_>,
					LhsMatrix_,
					Rhs_,
					divider_type
				>(lhs_, rhs_);
			}
		}
		else
		{
			static_assert(false, "Attempted to perform basic matrix division, but provided a non-EmuMath-matrix lhs_ argument.");
		}
	}
	template<typename out_contained_type, bool OutColumnMajor_, class LhsMatrix_, class Rhs_>
	constexpr inline EmuMath::Matrix<LhsMatrix_::num_columns, LhsMatrix_::num_rows, out_contained_type, OutColumnMajor_> MatrixDivideBasic
	(
		const LhsMatrix_& lhs_,
		const Rhs_& rhs_
	)
	{
		return MatrixDivideBasic<LhsMatrix_::num_columns, LhsMatrix_::num_rows, out_contained_type, OutColumnMajor_, LhsMatrix_, Rhs_>(lhs_, rhs_);
	}
	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, bool OutColumnMajor_, class LhsMatrix_, class Rhs_>
	constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, typename LhsMatrix_::value_type, OutColumnMajor_> MatrixDivideBasic
	(
		const LhsMatrix_& lhs_,
		const Rhs_& rhs_
	)
	{
		return MatrixDivideBasic<OutNumColumns_, OutNumRows_, typename LhsMatrix_::value_type, OutColumnMajor_, LhsMatrix_, Rhs_>(lhs_, rhs_);
	}
	template<bool OutColumnMajor_, class LhsMatrix_, class Rhs_>
	constexpr inline EmuMath::Matrix<LhsMatrix_::num_columns, LhsMatrix_::num_rows, typename LhsMatrix_::value_type, OutColumnMajor_> MatrixDivideBasic
	(
		const LhsMatrix_& lhs_,
		const Rhs_& rhs_
	)
	{
		return MatrixDivideBasic<LhsMatrix_::num_columns, LhsMatrix_::num_rows, typename LhsMatrix_::value_type, OutColumnMajor_, LhsMatrix_, Rhs_>(lhs_, rhs_);
	}

	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename out_contained_type, class LhsMatrix_, class Rhs_>
	constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, out_contained_type, LhsMatrix_::is_column_major> MatrixDivideBasic(const LhsMatrix_& lhs_, const Rhs_& rhs_)
	{
		return MatrixDivideBasic<OutNumColumns_, OutNumRows_, out_contained_type, LhsMatrix_::is_column_major, LhsMatrix_, Rhs_>(lhs_, rhs_);
	}
	template<typename out_contained_type, class LhsMatrix_, class Rhs_>
	constexpr inline EmuMath::Matrix<LhsMatrix_::num_columns, LhsMatrix_::num_rows, out_contained_type, LhsMatrix_::is_column_major> MatrixDivideBasic
	(
		const LhsMatrix_& lhs_,
		const Rhs_& rhs_
	)
	{
		return MatrixDivideBasic<LhsMatrix_::num_columns, LhsMatrix_::num_rows, out_contained_type, LhsMatrix_::is_column_major, LhsMatrix_, Rhs_>(lhs_, rhs_);
	}
	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, class LhsMatrix_, class Rhs_>
	constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, typename LhsMatrix_::value_type, LhsMatrix_::is_column_major> MatrixDivideBasic
	(
		const LhsMatrix_& lhs_,
		const Rhs_& rhs_
	)
	{
		return MatrixDivideBasic<OutNumColumns_, OutNumRows_, typename LhsMatrix_::value_type, LhsMatrix_::is_column_major, LhsMatrix_, Rhs_>(lhs_, rhs_);
	}
	template<class LhsMatrix_, class Rhs_>
	constexpr inline EmuMath::Matrix<LhsMatrix_::num_columns, LhsMatrix_::num_rows, typename LhsMatrix_::value_type, LhsMatrix_::is_column_major> MatrixDivideBasic
	(
		const LhsMatrix_& lhs_,
		const Rhs_& rhs_
	)
	{
		return MatrixDivideBasic<LhsMatrix_::num_columns, LhsMatrix_::num_rows, typename LhsMatrix_::value_type, LhsMatrix_::is_column_major, LhsMatrix_, Rhs_>(lhs_, rhs_);
	}

	/// <summary>
	/// <para> Performs a multiplication operation on lhs_ using the passed rhs_. </para>
	/// <para>
	///		If the passed rhs_ is a matrix, the resulting matrix will be that of a standard matrix multiplication.
	///		Otherwise, each index in the lhs_ matrix will be multiplied by rhs_.
	/// </para>
	/// <para> If rhs_ is a scalar, multiplications are performed using EmuCore::do_multiply&lt;LhsMatrix_::value_type, Rhs_ (or Rhs_::value_type if it is a matrix)&gt;. </para>
	/// <para> NOTE: This is a standard matrix multiplication operation. To instead multiply respective matrix indices, use MatrixMultiplyBasic. </para>
	/// </summary>
	/// <typeparam name="out_contained_type">Type to be contained within the result matrix.</typeparam>
	/// <typeparam name="LhsMatrix_">Type of matrix appearing on the left-hand side of multiplication.</typeparam>
	/// <typeparam name="Rhs_">Type of matrix or scalar appearing on the right-hand side of multiplication.</typeparam>
	/// <param name="lhs_">EmuMath matrix appearing on the left-hand side of multiplication.</param>
	/// <param name="rhs_">EmuMath matrix or scalar appearing on the right-hand side of multiplication.</param>
	/// <returns>Matrix containing the results of performing multiplication on the lhs_ matrix by the provided rhs_.</returns>
	template<typename out_contained_type, bool OutColumnMajor_, class LhsMatrix_, class Rhs_>
	constexpr inline typename EmuMath::TMP::emu_matrix_multiplication_result<out_contained_type, OutColumnMajor_, LhsMatrix_, Rhs_>::type MatrixMultiply
	(
		const LhsMatrix_& lhs_,
		const Rhs_& rhs_
	)
	{
		if constexpr (EmuMath::TMP::is_emu_matrix_v<LhsMatrix_>)
		{
			if constexpr(!std::is_same_v<typename EmuMath::TMP::emu_matrix_multiplication_result<out_contained_type, OutColumnMajor_, LhsMatrix_, Rhs_>::type, void>)
			{
				return _underlying_matrix_funcs::_matrix_std_multiply
				<
					typename EmuMath::TMP::emu_matrix_multiplication_result<out_contained_type, OutColumnMajor_, LhsMatrix_, Rhs_>::type,
					LhsMatrix_,
					Rhs_
				>(lhs_, rhs_);
			}
			else
			{
				static_assert(false, "Attempted to multiply two EmuMath matrices which can not be multiplied together. When multiplying matrices, the left-hand matrix must have the same number of columns as the right-hand matrix's number of rows.");
			}
		}
		else
		{
			static_assert(false, "Attempted to perform matrix multiplication with a lhs_ argument that is not an EmuMath matrix.");
		}
	}
	template<typename out_contained_type, class LhsMatrix_, class Rhs_>
	constexpr inline typename EmuMath::TMP::emu_matrix_multiplication_result<out_contained_type, LhsMatrix_::is_column_major, LhsMatrix_, Rhs_>::type MatrixMultiply
	(
		const LhsMatrix_& lhs_,
		const Rhs_& rhs_
	)
	{
		return MatrixMultiply<out_contained_type, LhsMatrix_::is_column_major, LhsMatrix_, Rhs_>(lhs_, rhs_);
	}
	template<bool OutColumnMajor_, class LhsMatrix_, class Rhs_>
	constexpr inline typename EmuMath::TMP::emu_matrix_multiplication_result<typename LhsMatrix_::value_type, OutColumnMajor_, LhsMatrix_, Rhs_>::type MatrixMultiply
	(
		const LhsMatrix_& lhs_,
		const Rhs_& rhs_
	)
	{
		return MatrixMultiply<typename LhsMatrix_::value_type, OutColumnMajor_, LhsMatrix_, Rhs_>(lhs_, rhs_);
	}
	template<class LhsMatrix_, class Rhs_>
	constexpr inline typename EmuMath::TMP::emu_matrix_multiplication_result<typename LhsMatrix_::value_type, LhsMatrix_::is_column_major, LhsMatrix_, Rhs_>::type MatrixMultiply
	(
		const LhsMatrix_& lhs_,
		const Rhs_& rhs_
	)
	{
		return MatrixMultiply<typename LhsMatrix_::value_type, LhsMatrix_::is_column_major, LhsMatrix_, Rhs_>(lhs_, rhs_);
	}
#pragma endregion

#pragma region MATRIX_OPERATIONS
	/// <summary>
	/// <para> Determines the identity matrix of an EmuMath matrix with the provided dimensions. </para>
	/// <para> Instead of passing dimensions and other matrix focused data, a matrix type may be provided as a template argument to determine defaults. </para>
	/// <para> If a specific matrix's identity is desired, but the type is unknown, the matrix itself may be passed to this function to determine default arguments. </para>
	/// </summary>
	/// <typeparam name="out_contained_type">Type to be contained in the output identity matrix.</typeparam>
	/// <returns>Identity matrix of the provided size, where all elements are 0 excluding the main diagonal, along which all elements are 1.</returns>
	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename out_contained_type, bool OutColumnMajor_ = true>
	constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, out_contained_type, OutColumnMajor_> MatrixIdentity()
	{
		if constexpr (OutNumColumns_ == OutNumRows_)
		{
			return _underlying_matrix_funcs::_make_identity_matrix<EmuMath::Matrix<OutNumColumns_, OutNumRows_, out_contained_type, OutColumnMajor_>>();
		}
		else
		{
			static_assert(false, "Attempted to acquire an EmuMath identity matrix, but the provided matrix dimensions were non-square. An identity matrix must be square.");
		}
	}
	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename out_contained_type, bool OutColumnMajor_, class Matrix_>
	constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, out_contained_type, OutColumnMajor_> MatrixIdentity()
	{
		if constexpr (EmuMath::TMP::is_emu_matrix_v<Matrix_>)
		{
			return MatrixIdentity<OutNumColumns_, OutNumRows_, out_contained_type, OutColumnMajor_>();
		}
		else
		{
			static_assert(false, "Attempted to acquire an EmuMath identity matrix, but provided a non-EmuMath-matrix type to determine the identity of.");
		}
	}
	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename out_contained_type, bool OutColumnMajor_, class Matrix_>
	constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, out_contained_type, OutColumnMajor_> MatrixIdentity(const Matrix_& matrix_)
	{
		if constexpr (EmuMath::TMP::is_emu_matrix_v<Matrix_>)
		{
			return MatrixIdentity<OutNumColumns_, OutNumRows_, out_contained_type, OutColumnMajor_>();
		}
		else
		{
			static_assert(false, "Attempted to acquire an EmuMath identity matrix, but provided a non-EmuMath-matrix type to determine the identity of.");
		}
	}
	template<typename out_contained_type, bool OutColumnMajor_, class Matrix_>
	constexpr inline EmuMath::Matrix<Matrix_::num_columns, Matrix_::num_rows, out_contained_type, OutColumnMajor_> MatrixIdentity()
	{
		if constexpr (EmuMath::TMP::is_emu_matrix_v<Matrix_>)
		{
			return MatrixIdentity<Matrix_::num_columns, Matrix_::num_rows, out_contained_type, OutColumnMajor_>();
		}
		else
		{
			static_assert(false, "Attempted to acquire an EmuMath identity matrix, but provided a non-EmuMath-matrix type to determine the identity of.");
		}
	}
	template<typename out_contained_type, bool OutColumnMajor_, class Matrix_>
	constexpr inline EmuMath::Matrix<Matrix_::num_columns, Matrix_::num_rows, out_contained_type, OutColumnMajor_> MatrixIdentity(const Matrix_& matrix_)
	{
		if constexpr (EmuMath::TMP::is_emu_matrix_v<Matrix_>)
		{
			return MatrixIdentity<Matrix_::num_columns, Matrix_::num_rows, out_contained_type, OutColumnMajor_>();
		}
		else
		{
			static_assert(false, "Attempted to acquire an EmuMath identity matrix, but provided a non-EmuMath-matrix type to determine the identity of.");
		}
	}
	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, bool OutColumnMajor_, class Matrix_>
	constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, typename Matrix_::value_type, OutColumnMajor_> MatrixIdentity()
	{
		if constexpr (EmuMath::TMP::is_emu_matrix_v<Matrix_>)
		{
			return MatrixIdentity<OutNumColumns_, OutNumRows_, typename Matrix_::value_type, OutColumnMajor_>();
		}
		else
		{
			static_assert(false, "Attempted to acquire an EmuMath identity matrix, but provided a non-EmuMath-matrix type to determine the identity of.");
		}
	}
	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, bool OutColumnMajor_, class Matrix_>
	constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, typename Matrix_::value_type, OutColumnMajor_> MatrixIdentity(const Matrix_& matrix_)
	{
		if constexpr (EmuMath::TMP::is_emu_matrix_v<Matrix_>)
		{
			return MatrixIdentity<OutNumColumns_, OutNumRows_, typename Matrix_::value_type, OutColumnMajor_>();
		}
		else
		{
			static_assert(false, "Attempted to acquire an EmuMath identity matrix, but provided a non-EmuMath-matrix type to determine the identity of.");
		}
	}
	template<bool OutColumnMajor_, class Matrix_>
	constexpr inline EmuMath::Matrix<Matrix_::num_columns, Matrix_::num_rows, typename Matrix_::value_type, OutColumnMajor_> MatrixIdentity()
	{
		if constexpr (EmuMath::TMP::is_emu_matrix_v<Matrix_>)
		{
			return MatrixIdentity<Matrix_::num_columns, Matrix_::num_rows, typename Matrix_::value_type, OutColumnMajor_>();
		}
		else
		{
			static_assert(false, "Attempted to acquire an EmuMath identity matrix, but provided a non-EmuMath-matrix type to determine the identity of.");
		}
	}
	template<bool OutColumnMajor_, class Matrix_>
	constexpr inline EmuMath::Matrix<Matrix_::num_columns, Matrix_::num_rows, typename Matrix_::value_type, OutColumnMajor_> MatrixIdentity(const Matrix_& matrix_)
	{
		if constexpr (EmuMath::TMP::is_emu_matrix_v<Matrix_>)
		{
			return MatrixIdentity<Matrix_::num_columns, Matrix_::num_rows, typename Matrix_::value_type, OutColumnMajor_>();
		}
		else
		{
			static_assert(false, "Attempted to acquire an EmuMath identity matrix, but provided a non-EmuMath-matrix type to determine the identity of.");
		}
	}
	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename out_contained_type, class Matrix_>
	constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, out_contained_type, Matrix_::is_column_major> MatrixIdentity()
	{
		if constexpr (EmuMath::TMP::is_emu_matrix_v<Matrix_>)
		{
			return MatrixIdentity<OutNumColumns_, OutNumRows_, out_contained_type, Matrix_::is_column_major>();
		}
		else
		{
			static_assert(false, "Attempted to acquire an EmuMath identity matrix, but provided a non-EmuMath-matrix type to determine the identity of.");
		}
	}
	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename out_contained_type, class Matrix_>
	constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, out_contained_type, Matrix_::is_column_major> MatrixIdentity(const Matrix_& matrix_)
	{
		if constexpr (EmuMath::TMP::is_emu_matrix_v<Matrix_>)
		{
			return MatrixIdentity<OutNumColumns_, OutNumRows_, out_contained_type, Matrix_::is_column_major>();
		}
		else
		{
			static_assert(false, "Attempted to acquire an EmuMath identity matrix, but provided a non-EmuMath-matrix type to determine the identity of.");
		}
	}
	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, class Matrix_>
	constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, typename Matrix_::value_type, Matrix_::is_column_major> MatrixIdentity()
	{
		if constexpr (EmuMath::TMP::is_emu_matrix_v<Matrix_>)
		{
			return MatrixIdentity<OutNumColumns_, OutNumRows_, typename Matrix_::value_type, Matrix_::is_column_major>();
		}
		else
		{
			static_assert(false, "Attempted to acquire an EmuMath identity matrix, but provided a non-EmuMath-matrix type to determine the identity of.");
		}
	}
	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, class Matrix_>
	constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, typename Matrix_::value_type, Matrix_::is_column_major> MatrixIdentity(const Matrix_& matrix_)
	{
		if constexpr (EmuMath::TMP::is_emu_matrix_v<Matrix_>)
		{
			return MatrixIdentity<OutNumColumns_, OutNumRows_, typename Matrix_::value_type, Matrix_::is_column_major>();
		}
		else
		{
			static_assert(false, "Attempted to acquire an EmuMath identity matrix, but provided a non-EmuMath-matrix type to determine the identity of.");
		}
	}
	template<typename out_contained_type, class Matrix_>
	constexpr inline EmuMath::Matrix<Matrix_::num_columns, Matrix_::num_rows, out_contained_type, Matrix_::is_column_major> MatrixIdentity()
	{
		if constexpr (EmuMath::TMP::is_emu_matrix_v<Matrix_>)
		{
			return MatrixIdentity<Matrix_::num_columns, Matrix_::num_rows, out_contained_type, Matrix_::is_column_major>();
		}
		else
		{
			static_assert(false, "Attempted to acquire an EmuMath identity matrix, but provided a non-EmuMath-matrix type to determine the identity of.");
		}
	}
	template<typename out_contained_type, class Matrix_>
	constexpr inline EmuMath::Matrix<Matrix_::num_columns, Matrix_::num_rows, out_contained_type, Matrix_::is_column_major> MatrixIdentity(const Matrix_& matrix_)
	{
		if constexpr (EmuMath::TMP::is_emu_matrix_v<Matrix_>)
		{
			return MatrixIdentity<Matrix_::num_columns, Matrix_::num_rows, out_contained_type, Matrix_::is_column_major>();
		}
		else
		{
			static_assert(false, "Attempted to acquire an EmuMath identity matrix, but provided a non-EmuMath-matrix type to determine the identity of.");
		}
	}
	template<class Matrix_>
	constexpr inline EmuMath::Matrix<Matrix_::num_columns, Matrix_::num_rows, typename Matrix_::value_type, Matrix_::is_column_major> MatrixIdentity()
	{
		if constexpr (EmuMath::TMP::is_emu_matrix_v<Matrix_>)
		{
			return MatrixIdentity<Matrix_::num_columns, Matrix_::num_rows, typename Matrix_::value_type, Matrix_::is_column_major>();
		}
		else
		{
			static_assert(false, "Attempted to acquire an EmuMath identity matrix, but provided a non-EmuMath-matrix type to determine the identity of.");
		}
	}
	template<class Matrix_>
	constexpr inline EmuMath::Matrix<Matrix_::num_columns, Matrix_::num_rows, typename Matrix_::value_type, Matrix_::is_column_major> MatrixIdentity(const Matrix_& matrix_)
	{
		if constexpr (EmuMath::TMP::is_emu_matrix_v<Matrix_>)
		{
			return MatrixIdentity<Matrix_::num_columns, Matrix_::num_rows, typename Matrix_::value_type, Matrix_::is_column_major>();
		}
		else
		{
			static_assert(false, "Attempted to acquire an EmuMath identity matrix, but provided a non-EmuMath-matrix type to determine the identity of.");
		}
	}

	/// <summary>
	/// <para> Transposes the passed matrix, effectively turning columns into rows and vice versa. </para>
	/// <para> The output matrix will always be of dimensions [Y, X] when provided an input matrix of dimensions [X, Y]. </para>
	/// </summary>
	/// <typeparam name="out_contained_type">Type to be contained in the output transpose matrix.</typeparam>
	/// <typeparam name="Matrix_">Type of matrix to tranpose.</typeparam>
	/// <param name="matrix_">EmuMath matrix to transpose.</param>
	/// <returns>Tranposed form of the passed EmuMath matrix.</returns>
	template<typename out_contained_type, bool OutColumnMajor_, class Matrix_>
	constexpr inline typename EmuMath::TMP::emu_matrix_transpose<out_contained_type, OutColumnMajor_, Matrix_>::type MatrixTranspose(const Matrix_& matrix_)
	{
		if constexpr (EmuMath::TMP::is_emu_matrix_v<Matrix_>)
		{
			return _underlying_matrix_funcs::_transpose_matrix
			<
				typename EmuMath::TMP::emu_matrix_transpose<out_contained_type, OutColumnMajor_, Matrix_>::type,
				Matrix_
			>(matrix_);
		}
		else
		{
			static_assert(false, "Attempted to form the transpose of a matrix, but the passed argument was not an EmuMath matrix.");
		}
	}
	template<typename out_contained_type, class Matrix_>
	constexpr inline typename EmuMath::TMP::emu_matrix_transpose<out_contained_type, Matrix_::is_column_major, Matrix_>::type MatrixTranspose(const Matrix_& matrix_)
	{
		return MatrixTranspose<out_contained_type, Matrix_::is_column_major, Matrix_>(matrix_);
	}
	template<bool OutColumnMajor_, class Matrix_>
	constexpr inline typename EmuMath::TMP::emu_matrix_transpose<typename Matrix_::value_type, OutColumnMajor_, Matrix_>::type MatrixTranspose(const Matrix_& matrix_)
	{
		return MatrixTranspose<typename Matrix_::value_type, OutColumnMajor_, Matrix_>(matrix_);
	}
	template<class Matrix_>
	constexpr inline typename EmuMath::TMP::emu_matrix_transpose<typename Matrix_::value_type, Matrix_::is_column_major, Matrix_>::type MatrixTranspose(const Matrix_& matrix_)
	{
		return MatrixTranspose<typename Matrix_::value_type, Matrix_::is_column_major, Matrix_>(matrix_);
	}

	/// <summary>
	/// <para> Calculates the trace of the passed matrix (i.e. the sum of all diagonal elements from the top-left to the bottom right). </para>
	/// <para> The trace is only defined for a square matrix, and as such this function may only be validly executed on square matrices. </para>
	/// </summary>
	/// <typeparam name="OutT_">Type to output the trace as.</typeparam>
	/// <typeparam name="Matrix_">Type of matrix to calculate the trace of.</typeparam>
	/// <param name="matrix_">EmuMath matrix to calculate the trace of.</param>
	/// <returns>Trace of the passed matrix, represented as the provided OutT_.</returns>
	template<typename OutT_, class Matrix_>
	constexpr inline OutT_ MatrixTrace(const Matrix_& matrix_)
	{
		if constexpr (EmuMath::TMP::is_emu_matrix_v<Matrix_>)
		{
			if constexpr (Matrix_::is_square)
			{
				return _underlying_matrix_funcs::_calculate_matrix_trace<OutT_, Matrix_>(matrix_);
			}
			else
			{
				static_assert(false, "Attempted to calculate the trace of an EmuMath matrix that is not square. Only square matrices have a mathematically defined trace.");
			}
		}
		else
		{
			static_assert(false, "Attempted to calculate the trace of a matrix, but a non-EmuMath-matrix argument was passed.");
		}
	}
	template<class Matrix_>
	constexpr inline typename Matrix_::value_type MatrixTrace(const Matrix_& matrix_)
	{
		return MatrixTrace<typename Matrix_::value_type, Matrix_>(matrix_);
	}

	/// <summary>
	/// <para> Retrieves a smaller matrix from within the passed matrix, which is formed of all elements excluding those in the provided row and column. </para>
	/// <para> This will always yield a matrix of size [X-1, Y-1] when performed on a matrix of size [X, Y]. </para>
	/// </summary>
	/// <typeparam name="out_contained_type">Type to be contained in the output submatrix.</typeparam>
	/// <typeparam name="Matrix_">Type of matrix to retrieve a submatrix from.</typeparam>
	/// <param name="matrix_">EmuMath matrix to retrieve the specified submatrix from.</param>
	/// <returns>Copy of the submatrix within the passed EmuMath matrix, formed of all elements excluding those in the provided column or row indices.</returns>
	template<std::size_t ExcludeColumn_, std::size_t ExcludeRow_, typename out_contained_type, bool OutColumnMajor_, class Matrix_>
	constexpr inline typename EmuMath::TMP::emu_matrix_submatrix_excluding_element_region<out_contained_type, OutColumnMajor_, Matrix_>::type
		MatrixExclusiveSubmatrix
		(
			Matrix_& matrix_
		)
	{
		if constexpr (EmuMath::TMP::is_emu_matrix_v<Matrix_>)
		{
			if constexpr (!std::is_same_v<typename EmuMath::TMP::emu_matrix_submatrix_excluding_element_region<out_contained_type, OutColumnMajor_, Matrix_>::type, void>)
			{
				if constexpr (ExcludeColumn_ < Matrix_::num_columns)
				{
					if constexpr (ExcludeRow_ < Matrix_::num_rows)
					{
						return _underlying_matrix_funcs::_get_submatrix_excluding_element_region
							<
							ExcludeColumn_,
							ExcludeRow_,
							typename EmuMath::TMP::emu_matrix_submatrix_excluding_element_region<out_contained_type, OutColumnMajor_, Matrix_>::type,
							Matrix_
							>(matrix_);
					}
					else
					{
						static_assert(false, "Attempted to retrieve a submatrix excluding an element's regions within an EmuMath matrix, but the provided row index to ignore exceeded the range of the passed matrix's rows.");
					}
				}
				else
				{
					static_assert(false, "Attempted to retrieve a submatrix excluding an element's regions within an EmuMath matrix, but the provided column index to ignore exceeded the range of the passed matrix's columns.");
				}
			}
			else
			{
				static_assert(false, "Attempted to retrieve a submatrix excluding an element's regions with an EmuMath matrix, but the provided matrix cannot supply a submatrix.");
			}
		}
		else
		{
			static_assert(false, "Attempted to retrieve a submatrix excluding an element's regions within a matrix, but the provided argument was not an EmuMath matrix.");
		}
	}
	template<std::size_t ExcludeColumn_, std::size_t ExcludeRow_, typename out_contained_type, class Matrix_>
	constexpr inline typename EmuMath::TMP::emu_matrix_submatrix_excluding_element_region<out_contained_type, Matrix_::is_column_major, Matrix_>::type
		MatrixExclusiveSubmatrix
		(
			Matrix_& matrix_
		)
	{
		return MatrixExclusiveSubmatrix<ExcludeColumn_, ExcludeRow_, out_contained_type, Matrix_::is_column_major, Matrix_>(matrix_);
	}
	template<std::size_t ExcludeColumn_, std::size_t ExcludeRow_, typename out_contained_type, class Matrix_>
	constexpr inline typename EmuMath::TMP::emu_matrix_submatrix_excluding_element_region<out_contained_type, Matrix_::is_column_major, Matrix_>::type
		MatrixExclusiveSubmatrix
		(
			const Matrix_& matrix_
		)
	{
		return MatrixExclusiveSubmatrix<ExcludeColumn_, ExcludeRow_, out_contained_type, const Matrix_::is_column_major, Matrix_>(matrix_);
	}
	template<std::size_t ExcludeColumn_, std::size_t ExcludeRow_, bool OutColumnMajor_, class Matrix_>
	constexpr inline typename EmuMath::TMP::emu_matrix_submatrix_excluding_element_region<typename Matrix_::value_type, OutColumnMajor_, Matrix_>::type
		MatrixExclusiveSubmatrix
		(
			Matrix_& matrix_
		)
	{
		return MatrixExclusiveSubmatrix<ExcludeColumn_, ExcludeRow_, typename Matrix_::value_type, OutColumnMajor_, Matrix_>(matrix_);
	}
	template<std::size_t ExcludeColumn_, std::size_t ExcludeRow_, bool OutColumnMajor_, class Matrix_>
	constexpr inline typename EmuMath::TMP::emu_matrix_submatrix_excluding_element_region<typename Matrix_::value_type, OutColumnMajor_, Matrix_>::type
		MatrixExclusiveSubmatrix
		(
			const Matrix_& matrix_
		)
	{
		return MatrixExclusiveSubmatrix<ExcludeColumn_, ExcludeRow_, typename Matrix_::value_type, OutColumnMajor_, const Matrix_>(matrix_);
	}
	template<std::size_t ExcludeColumn_, std::size_t ExcludeRow_, class Matrix_>
	constexpr inline typename EmuMath::TMP::emu_matrix_submatrix_excluding_element_region<typename Matrix_::value_type, Matrix_::is_column_major, Matrix_>::type
		MatrixExclusiveSubmatrix
		(
			Matrix_& matrix_
		)
	{
		return MatrixExclusiveSubmatrix<ExcludeColumn_, ExcludeRow_, typename Matrix_::value_type, Matrix_::is_column_major, Matrix_>(matrix_);
	}
	template<std::size_t ExcludeColumn_, std::size_t ExcludeRow_, class Matrix_>
	constexpr inline typename EmuMath::TMP::emu_matrix_submatrix_excluding_element_region<typename Matrix_::value_type, Matrix_::is_column_major, Matrix_>::type
		MatrixExclusiveSubmatrix
		(
			const Matrix_& matrix_
		)
	{
		return MatrixExclusiveSubmatrix<ExcludeColumn_, ExcludeRow_, typename Matrix_::value_type, Matrix_::is_column_major, const Matrix_>(matrix_);
	}

	/// <summary>
	/// <para> Calculates the determinant of the passed matrix using Laplace Expansion. </para>
	/// <para> NOTE: Laplace Expansion grows exponentially more expensive as the size of a matrix increases. </para>
	/// </summary>
	/// <typeparam name="OutDet_">Type to output the passed matrix's determinant as.</typeparam>
	/// <typeparam name="Matrix_">Type of matrix to calculate the determinant of.</typeparam>
	/// <param name="matrix_">EmuMath matrix to calculate the determinant of.</param>
	/// <returns>Determinant of the passed EmuMath matrix, represented as the provided OutDet_ type.</returns>
	template<typename OutDet_, class Matrix_>
	constexpr inline OutDet_ MatrixDeterminantLaplace(const Matrix_& matrix_)
	{
		if constexpr (EmuMath::TMP::is_emu_matrix_v<Matrix_>)
		{
			if constexpr (Matrix_::is_square)
			{
				return _underlying_matrix_funcs::_calculate_matrix_determinant_laplace<OutDet_, Matrix_>(matrix_);
			}
			else
			{
				static_assert(false, "Attempted to calculate the determinant of an EmuMath matrix that is not square. Only square matrices have a mathematically defined determinant.");
			}
		}
		else
		{
			static_assert(false, "Attempted to calculate a matrix's determinant, but a non-EmuMath-matrix argument was passed.");
		}
	}
	template<class Matrix_>
	constexpr inline typename Matrix_::preferred_floating_point MatrixDeterminantLaplace(const Matrix_& matrix_)
	{
		return MatrixDeterminantLaplace<typename Matrix_::preferred_floating_point, Matrix_>(matrix_);
	}

	/// <summary>
	/// <para> Calculates the matrix of minors to the passed matrix using Laplace Expansion. </para>
	/// <para> Each element in the output matrix may be summarised as the determinant of the submatrix which excludes said element's column and row. </para>
	/// <para> NOTE: Laplace Expansion grows exponentially more expensive as the size of a matrix increases. </para>
	/// </summary>
	/// <typeparam name="out_contained_type">Type to be contained in the output minor matrix.</typeparam>
	/// <typeparam name="Matrix_">Matrix to calculate the matrix of minors to.</typeparam>
	/// <param name="matrix_">EmuMath matrix to find the matrix of minors to.</param>
	/// <returns>Matrix of minors to the passed EmuMath matrix.</returns>
	template<typename out_contained_type, bool OutColumnMajor_, class Matrix_>
	constexpr inline EmuMath::Matrix<Matrix_::num_columns, Matrix_::num_rows, out_contained_type, OutColumnMajor_> MatrixOfMinorsLaplace(const Matrix_& matrix_)
	{
		if constexpr (EmuMath::TMP::is_emu_matrix_v<Matrix_>)
		{
			if constexpr (Matrix_::is_square)
			{
				return _underlying_matrix_funcs::_calculate_matrix_of_minors_laplace
				<
					EmuMath::Matrix<Matrix_::num_columns, Matrix_::num_rows, out_contained_type, OutColumnMajor_>,
					Matrix_
				>(matrix_);
			}
			else
			{
				static_assert(false, "Attempted to calculate a matrix of minors, but provided a non-square EmuMath matrix. Only square matrices are valid for this operation.");
			}
		}
		else
		{
			static_assert(false, "Attempted to calculate a matrix of minors, but provided a non-EmuMath-matrix argument.");
		}
	}
	template<bool OutColumnMajor_, class Matrix_>
	constexpr inline EmuMath::Matrix<Matrix_::num_columns, Matrix_::num_rows, typename Matrix_::value_type, OutColumnMajor_> MatrixOfMinorsLaplace(const Matrix_& matrix_)
	{
		return MatrixOfMinorsLaplace<typename Matrix_::value_type, OutColumnMajor_, Matrix_>(matrix_);
	}
	template<typename out_contained_type, class Matrix_>
	constexpr inline EmuMath::Matrix<Matrix_::num_columns, Matrix_::num_rows, out_contained_type, Matrix_::is_column_major> MatrixOfMinorsLaplace(const Matrix_& matrix_)
	{
		return MatrixOfMinorsLaplace<out_contained_type, Matrix_::is_column_major, Matrix_>(matrix_);
	}
	template<class Matrix_>
	constexpr inline EmuMath::Matrix<Matrix_::num_columns, Matrix_::num_rows, typename Matrix_::value_type, Matrix_::is_column_major> MatrixOfMinorsLaplace(const Matrix_& matrix_)
	{
		return MatrixOfMinorsLaplace<typename Matrix_::value_type, Matrix_::is_column_major, Matrix_>(matrix_);
	}

	/// <summary>
	/// <para> Calculates the matrix of cofactors to the passed matrix using Laplace Expansion. </para>
	/// <para> NOTE: Laplace Expansion grows exponentially more expensive as the size of a matrix increases. </para>
	/// </summary>
	/// <typeparam name="out_contained_type">Type to be contained in the output cofactor matrix.</typeparam>
	/// <typeparam name="Matrix_">Matrix to calculate the matrix of cofactors to.</typeparam>
	/// <param name="matrix_">EmuMath matrix to find the matrix of cofactors to.</param>
	/// <returns>Matrix of cofactors to the passed EmuMath matrix.</returns>
	template<typename out_contained_type, bool OutColumnMajor_, class Matrix_>
	constexpr inline EmuMath::Matrix<Matrix_::num_columns, Matrix_::num_rows, out_contained_type, OutColumnMajor_> MatrixOfCofactorsLaplace(const Matrix_& matrix_)
	{
		if constexpr (EmuMath::TMP::is_emu_matrix_v<Matrix_>)
		{
			if constexpr (Matrix_::is_square)
			{
				return _underlying_matrix_funcs::_calculate_matrix_of_cofactors_laplace
				<
					EmuMath::Matrix<Matrix_::num_columns, Matrix_::num_rows, out_contained_type, OutColumnMajor_>,
					Matrix_
				>(matrix_);
			}
			else
			{
				static_assert(false, "Attempted to calculate a matrix of cofactors, but provided a non-square EmuMath matrix. Only square matrices are valid for this operation.");
			}
		}
		else
		{
			static_assert(false, "Attempted to calculate a matrix of cofactors, but provided a non-EmuMath-matrix argument.");
		}
	}
	template<bool OutColumnMajor_, class Matrix_>
	constexpr inline EmuMath::Matrix<Matrix_::num_columns, Matrix_::num_rows, typename Matrix_::value_type, OutColumnMajor_> MatrixOfCofactorsLaplace(const Matrix_& matrix_)
	{
		return MatrixOfCofactorsLaplace<typename Matrix_::value_type, OutColumnMajor_, Matrix_>(matrix_);
	}
	template<typename out_contained_type, class Matrix_>
	constexpr inline EmuMath::Matrix<Matrix_::num_columns, Matrix_::num_rows, out_contained_type, Matrix_::is_column_major> MatrixOfCofactorsLaplace(const Matrix_& matrix_)
	{
		return MatrixOfCofactorsLaplace<out_contained_type, Matrix_::is_column_major, Matrix_>(matrix_);
	}
	template<class Matrix_>
	constexpr inline EmuMath::Matrix<Matrix_::num_columns, Matrix_::num_rows, typename Matrix_::value_type, Matrix_::is_column_major> MatrixOfCofactorsLaplace(const Matrix_& matrix_)
	{
		return MatrixOfCofactorsLaplace<typename Matrix_::value_type, Matrix_::is_column_major, Matrix_>(matrix_);
	}

	/// <summary>
	/// <para> Calculates the adjugate matrix to the passed matrix using Laplace Expansion. </para>
	/// <para> This matrix can be summarised as the transpose to the passed matrix's matrix of cofactors. </para>
	/// <para> NOTE: Laplace Expansion grows exponentially more expensive as the size of a matrix increases. </para>
	/// </summary>
	/// <typeparam name="out_contained_type">Type to be contained in the output adjugate matrix.</typeparam>
	/// <typeparam name="Matrix_">Matrix to calculate the adjugate to.</typeparam>
	/// <param name="matrix_">EmuMath matrix to find the adjugate to.</param>
	/// <returns>Adjugate matrix to the passed EmuMath matrix.</returns>
	template<typename out_contained_type, bool OutColumnMajor_, class Matrix_>
	constexpr inline typename EmuMath::TMP::emu_matrix_transpose<out_contained_type, OutColumnMajor_, Matrix_>::type MatrixAdjugateLaplace(const Matrix_& matrix_)
	{
		if constexpr (EmuMath::TMP::is_emu_matrix_v<Matrix_>)
		{
			if constexpr (Matrix_::is_square)
			{
				return _underlying_matrix_funcs::_calculate_matrix_adjugate_laplace
				<
					typename EmuMath::TMP::emu_matrix_transpose<out_contained_type, OutColumnMajor_, Matrix_>::type,
					Matrix_
				>(matrix_);
			}
			else
			{
				static_assert(false, "Attempted to calculate an adjugate matrix, but provided a non-square EmuMath matrix. Only square matrices are valid for this operation.");
			}
		}
		else
		{
			static_assert(false, "Attempted to calculate an adjugate matrix, but provided a non-EmuMath-matrix argument.");
		}
	}
	template<bool OutColumnMajor_, class Matrix_>
	constexpr inline typename EmuMath::TMP::emu_matrix_transpose<typename Matrix_::value_type, OutColumnMajor_, Matrix_>::type MatrixAdjugateLaplace(const Matrix_& matrix_)
	{
		return MatrixAdjugateLaplace<typename Matrix_::value_type, OutColumnMajor_, Matrix_>(matrix_);
	}
	template<typename out_contained_type, class Matrix_>
	constexpr inline typename EmuMath::TMP::emu_matrix_transpose<out_contained_type, Matrix_::is_column_major, Matrix_>::type MatrixAdjugateLaplace(const Matrix_& matrix_)
	{
		return MatrixAdjugateLaplace<out_contained_type, Matrix_::is_column_major, Matrix_>(matrix_);
	}
	template<class Matrix_>
	constexpr inline typename EmuMath::TMP::emu_matrix_transpose<typename Matrix_::value_type, Matrix_::is_column_major, Matrix_>::type MatrixAdjugateLaplace(const Matrix_& matrix_)
	{
		return MatrixAdjugateLaplace<typename Matrix_::value_type, Matrix_::is_column_major, Matrix_>(matrix_);
	}

	/// <summary>
	/// <para> Calculates the inverse to the passed matrix using Laplace Expansion. May optionally output the matrix's determinant as a customisable type. </para>
	/// <para>
	///		Note that this operation does not check that the matrix's determinant is not 0. As matrices with a determinant of 0 have no inverse,
	///		it is recommended to use the outDeterminant argument to test if the output matrix is valid if there is a chance that the passed matrix's determinant will be 0.
	/// </para>
	/// <para> NOTE: Laplace Expansion grows exponentially more expensive as the size of a matrix increases. </para>
	/// </summary>
	/// <typeparam name="out_contained_type">Type to be contained in the output inverse matrix.</typeparam>
	/// <typeparam name="Matrix_">Type of matrix to find the inverse of.</typeparam>
	/// <typeparam name="OutDeterminant_">Type to optionally output the matrix's determinant as.</typeparam>
	/// <param name="matrix_">EmuMath matrix to find the inverse of.</param>
	/// <param name="outDeterminant_">
	///		Optional reference to output the passed matrix's determinant to. 
	///		Useful to test if the determinant is 0 in cases where a non-invertible matrix may potentially be passed.
	/// </param>
	/// <returns>Inverted version of this matrix if it is invertible. Otherwise, a matrix containing the results of multiplying by (1/0).</returns>
	template<typename out_contained_type, bool OutColumnMajor_, class Matrix_, typename OutDeterminant_>
	constexpr inline typename EmuMath::TMP::emu_matrix_transpose<out_contained_type, OutColumnMajor_, Matrix_>::type MatrixInverseLaplace
	(
		const Matrix_& matrix_,
		OutDeterminant_& outDeterminant_
	)
	{
		if constexpr (EmuMath::TMP::is_emu_matrix_v<Matrix_>)
		{
			if constexpr (Matrix_::is_square)
			{
				return _underlying_matrix_funcs::_calculate_matrix_inverse_laplace
				<
					typename EmuMath::TMP::emu_matrix_transpose<out_contained_type, OutColumnMajor_, Matrix_>::type,
					Matrix_,
					OutDeterminant_
				>(matrix_, outDeterminant_);
			}
			else
			{
				static_assert(false, "Attempted to calculate an inverse matrix, but provided a non-square EmuMath matrix. Only square matrices are valid for this operation.");
			}
		}
		else
		{
			static_assert(false, "Attempted to calculate an inverse matrix, but provided a non-EmuMath-matrix argument.");
		}
	}
	template<bool OutColumnMajor_, class Matrix_, typename OutDeterminant_>
	constexpr inline typename EmuMath::TMP::emu_matrix_transpose<typename Matrix_::value_type, OutColumnMajor_, Matrix_>::type MatrixInverseLaplace
	(
		const Matrix_& matrix_,
		OutDeterminant_& outDeterminant_
	)
	{
		return MatrixInverseLaplace<typename Matrix_::value_type, OutColumnMajor_, Matrix_, OutDeterminant_>(matrix_, outDeterminant_);
	}
	template<typename out_contained_type, class Matrix_, typename OutDeterminant_>
	constexpr inline typename EmuMath::TMP::emu_matrix_transpose<out_contained_type, Matrix_::is_column_major, Matrix_>::type MatrixInverseLaplace
	(
		const Matrix_& matrix_,
		OutDeterminant_& outDeterminant_
	)
	{
		return MatrixInverseLaplace<out_contained_type, Matrix_::is_column_major, Matrix_, OutDeterminant_>(matrix_, outDeterminant_);
	}
	template<class Matrix_, typename OutDeterminant_>
	constexpr inline typename EmuMath::TMP::emu_matrix_transpose<typename Matrix_::value_type, Matrix_::is_column_major, Matrix_>::type MatrixInverseLaplace
	(
		const Matrix_& matrix_,
		OutDeterminant_& outDeterminant_
	)
	{
		return MatrixInverseLaplace<typename Matrix_::value_type, Matrix_::is_column_major, Matrix_, OutDeterminant_>(matrix_, outDeterminant_);
	}
	template<typename out_contained_type, bool OutColumnMajor_, class Matrix_>
	constexpr inline typename EmuMath::TMP::emu_matrix_transpose<out_contained_type, OutColumnMajor_, Matrix_>::type MatrixInverseLaplace
	(
		const Matrix_& matrix_
	)
	{
		using dummy_output_type = float;
		dummy_output_type reciprocal_dummy_output_ = 0.0f;
		return MatrixInverseLaplace<out_contained_type, OutColumnMajor_, Matrix_, dummy_output_type>(matrix_, reciprocal_dummy_output_);
	}
	template<bool OutColumnMajor_, class Matrix_>
	constexpr inline typename EmuMath::TMP::emu_matrix_transpose<typename Matrix_::value_type, OutColumnMajor_, Matrix_>::type MatrixInverseLaplace
	(
		const Matrix_& matrix_
	)
	{
		return MatrixInverseLaplace<typename Matrix_::value_type, OutColumnMajor_, Matrix_>(matrix_);
	}
	template<typename out_contained_type, class Matrix_>
	constexpr inline typename EmuMath::TMP::emu_matrix_transpose<out_contained_type, Matrix_::is_column_major, Matrix_>::type MatrixInverseLaplace
	(
		const Matrix_& matrix_
	)
	{
		return MatrixInverseLaplace<out_contained_type, Matrix_::is_column_major, Matrix_>(matrix_);
	}
	template<class Matrix_>
	constexpr inline typename EmuMath::TMP::emu_matrix_transpose<typename Matrix_::value_type, Matrix_::is_column_major, Matrix_>::type MatrixInverseLaplace
	(
		const Matrix_& matrix_
	)
	{
		return MatrixInverseLaplace<typename Matrix_::value_type, Matrix_::is_column_major, Matrix_>(matrix_);
	}
#pragma endregion

#pragma region TRANSFORMATIONS
	/// <summary>
	/// <para> Creates a 4x4 transformation matrix which may be used to perform a translation of x_ in the X-dimension, y_ in the Y-dimension, and z_ in the Z-dimension. </para>
	/// <para> x_, y_, and z_ may be any types, but they must be convertible to the output matrix's contained type (provided as the out_contained_type argument). </para>
	/// </summary>
	/// <typeparam name="out_contained_type">Type to be contained within the output matrix.</typeparam>
	/// <typeparam name="X_">Type use for the argument representing the translation in the X-dimension.</typeparam>
	/// <typeparam name="Y_">Type use for the argument representing the translation in the Y-dimension.</typeparam>
	/// <typeparam name="Z_">Type use for the argument representing the translation in the Z-dimension.</typeparam>
	/// <param name="x_">Distance to translate in the X-dimension.</param>
	/// <param name="y_">Distance to translate in the Y-dimension.</param>
	/// <param name="z_">Distance to translate in the Z-dimension.</param>
	/// <returns>4x4 EmuMath matrix which may be used to perform a translation of the specified amounts in respective dimensions.</returns>
	template<typename out_contained_type = float, bool OutColumnMajor_ = true, typename X_, typename Y_, typename Z_>
	constexpr inline EmuMath::Matrix<4, 4, out_contained_type, OutColumnMajor_> MatrixTranslation(const X_& x_, const Y_& y_, const Z_& z_)
	{
		return _underlying_matrix_funcs::_make_translation_matrix<EmuMath::Matrix<4, 4, out_contained_type, OutColumnMajor_>, X_, Y_, Z_>(x_, y_, z_);
	}
#pragma endregion
}

#endif
