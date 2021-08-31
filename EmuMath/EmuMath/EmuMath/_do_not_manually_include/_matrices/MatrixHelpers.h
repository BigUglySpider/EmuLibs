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
	/// <typeparam name="out_contained_type"></typeparam>
	/// <returns></returns>
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
#pragma endregion
}

#endif
