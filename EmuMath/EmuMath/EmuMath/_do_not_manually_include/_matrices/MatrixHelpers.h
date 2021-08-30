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
	constexpr inline auto& MatrixGet(const Matrix_& matrix_)
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
#pragma endregion
}

#endif
