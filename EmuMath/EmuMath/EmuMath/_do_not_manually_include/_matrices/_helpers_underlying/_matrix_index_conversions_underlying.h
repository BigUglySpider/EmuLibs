#ifndef EMU_MATH__UNDERLYING_MATRIX_INDEX_CONVERSIONS_H_INC_
#define EMU_MATH__UNDERLYING_MATRIX_INDEX_CONVERSIONS_H_INC_ 1

#include "_common_underlying_matrix_helper_includes.h"

namespace EmuMath::Helpers::_underlying_matrix_funcs
{
	template<std::size_t Index_, class Matrix_>
	constexpr inline std::size_t _matrix_major_order_index_to_column_index()
	{
		if constexpr (Matrix_::is_column_major)
		{
			return Index_ / Matrix_::num_columns;
		}
		else
		{
			return Index_ % Matrix_::num_columns;
		}
	}
	template<class Matrix_>
	constexpr inline std::size_t _matrix_major_order_index_to_column_index(const std::size_t index_)
	{
		if constexpr (Matrix_::is_column_major)
		{
			return index_ / Matrix_::num_columns;
		}
		else
		{
			return index_ % Matrix_::num_columns;
		}
	}

	template<std::size_t Index_, class Matrix_>
	constexpr inline std::size_t _matrix_major_order_index_to_row_index()
	{
		if constexpr (Matrix_::is_row_major)
		{
			return Index_ / Matrix_::num_rows;
		}
		else
		{
			return Index_ % Matrix_::num_rows;
		}
	}
	template<class Matrix_>
	constexpr inline std::size_t _matrix_major_order_index_to_row_index(const std::size_t index_)
	{
		if constexpr (Matrix_::is_row_major)
		{
			return index_ / Matrix_::num_rows;
		}
		else
		{
			return index_ % Matrix_::num_rows;
		}
	}
}

#endif
