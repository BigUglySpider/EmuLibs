#ifndef EMU_MATH__UNDERLYING_MATRIX_VALIDITY_CHECKS_H_INC_
#define EMU_MATH__UNDERLYING_MATRIX_VALIDITY_CHECKS_H_INC_ 1

#include "_common_matrix_helper_includes.h"

namespace EmuMath::Helpers::_underlying_matrix_funcs
{
	template<std::size_t ColumnIndex_, std::size_t RowIndex_, class Matrix_>
	constexpr inline bool _valid_matrix_indices()
	{
		return ColumnIndex_ < Matrix_::num_columns && RowIndex_ < Matrix_::num_rows;
	}
	template<std::size_t MajorOrderIndex_, class Matrix_>
	constexpr inline bool _valid_matrix_major_order_index()
	{
		return MajorOrderIndex_ < Matrix_::size;
	}
}

#endif
