#ifndef EMU_MATH__UNDERLYING_MATRIX_SETS_H_INC_
#define EMU_MATH__UNDERLYING_MATRIX_SETS_H_INC_ 1

#include "_common_matrix_helper_includes.h"

namespace EmuMath::Helpers::_underlying_matrix_funcs
{
	
	template<std::size_t ColumnIndex_, std::size_t RowIndex_, class Matrix_, typename Arg_>
	constexpr inline Matrix_& _matrix_set(Matrix_& matrix_, Arg_& arg_)
	{
		if constexpr (Matrix_::is_column_major)
		{
			auto& column_ = matrix_.template GetMajor<ColumnIndex_>();
			column_.template Set<RowIndex_>(arg_);
		}
		else
		{
			auto& row_ = matrix_.template GetMajor<RowIndex_>();
			row_.template Set<ColumnIndex_>(arg_);
		}
		return matrix_;
	}
	template<std::size_t ColumnIndex_, std::size_t RowIndex_, class Matrix_, typename Arg_>
	constexpr inline Matrix_& _matrix_set(Matrix_& matrix_, const Arg_& arg_)
	{
		if constexpr (Matrix_::is_column_major)
		{
			auto& column_ = matrix_.template GetMajor<ColumnIndex_>();
			column_.template Set<RowIndex_>(arg_);
		}
		else
		{
			auto& row_ = matrix_.template GetMajor<RowIndex_>();
			row_.template Set<ColumnIndex_>(arg_);
		}
		return matrix_;
	}

	template<std::size_t Index_, class Matrix_, typename Arg_>
	constexpr inline Matrix_& _matrix_set_trace_region(Matrix_& matrix_,  Arg_& arg_)
	{
		if constexpr ((Index_ < Matrix_::num_columns) && (Index_ < Matrix_::num_rows))
		{
			matrix_.template GetMajor<Index_>().template Set<Index_>(arg_);
			_matrix_set_trace_region<Index_ + 1, Matrix_, Arg_>(matrix_, arg_);
		}
		return matrix_;
	}
	template<std::size_t Index_, class Matrix_, typename Arg_>
	constexpr inline Matrix_& _matrix_set_trace_region(Matrix_& matrix_, const Arg_& arg_)
	{
		if constexpr ((Index_ < Matrix_::num_columns) && (Index_ < Matrix_::num_rows))
		{
			matrix_.template GetMajor<Index_>().template Set<Index_>(arg_);
			_matrix_set_trace_region<Index_ + 1, Matrix_, Arg_>(matrix_, arg_);
		}
		return matrix_;
	}
}

#endif
