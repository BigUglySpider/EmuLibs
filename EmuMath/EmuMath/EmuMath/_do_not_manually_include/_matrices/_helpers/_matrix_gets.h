#ifndef EMU_MATH_MATRIX_HELPERS_GETS_H_INC_
#define EMU_MATH_MATRIX_HELPERS_GETS_H_INC_ 1

#include "_common_matrix_helper_includes.h"

namespace EmuMath::Helpers
{
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
}

#endif
