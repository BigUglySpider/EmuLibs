#ifndef EMU_MATH__UNDERLYING_MATRIX_VALIDITY_CHECKS_H_INC_
#define EMU_MATH__UNDERLYING_MATRIX_VALIDITY_CHECKS_H_INC_ 1

#include "_common_underlying_matrix_helper_includes.h"

namespace EmuMath::Helpers::_underlying_matrix_funcs
{
	template<std::size_t ColumnIndex_, std::size_t RowIndex_, class Matrix_>
	[[nodiscard]] constexpr inline bool _valid_matrix_indices()
	{
		return ColumnIndex_ < Matrix_::num_columns && RowIndex_ < Matrix_::num_rows;
	}
	template<std::size_t ColumnIndex_, std::size_t RowIndex_, class Matrix_>
	[[nodiscard]] constexpr inline bool _valid_matrix_indices(const Matrix_& matrix_)
	{
		return _valid_matrix_indices<ColumnIndex_, RowIndex_, Matrix_>();
	}

	template<class Matrix_>
	[[nodiscard]] constexpr inline bool _valid_matrix_indices(const std::size_t column_index_, const std::size_t row_index_)
	{
		return column_index_ < Matrix_::num_columns && row_index_ < Matrix_::num_rows;
	}
	template<class Matrix_>
	[[nodiscard]] constexpr inline bool _valid_matrix_indices(const std::size_t column_index_, const std::size_t row_index_, const Matrix_& matrix_)
	{
		return _valid_matrix_indices<Matrix_>(column_index_, row_index_);
	}
}

#endif
