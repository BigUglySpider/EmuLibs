#ifndef EMU_MATH_UNDERLYING_MATRIX_STREAM_APPEND_H_INC_
#define EMU_MATH_UNDERLYING_MATRIX_STREAM_APPEND_H_INC_ 1

#include "_matrix_tmp.h"

namespace EmuMath::Helpers::_matrix_underlying
{
	template<bool IsWide_, class Str_>
	constexpr inline void _matrix_append_to_stream_open_major_chunk(Str_& str_)
	{
		if constexpr (IsWide_)
		{
			str_ << L"{ ";
		}
		else
		{
			str_ << "{ ";
		}
	}

	template<std::size_t MajorIndex_, std::size_t MajorSize_, bool IsWide_, class Str_>
	constexpr inline void _matrix_append_to_stream_close_major_chunk(Str_& str_)
	{
		if constexpr (IsWide_)
		{
			if constexpr ((MajorIndex_ + 1) < MajorSize_)
			{
				str_ << L" },\n";
			}
			else
			{
				str_ << L" }";
			}
		}
		else
		{
			if constexpr ((MajorIndex_ + 1) < MajorSize_)
			{
				str_ << " },\n";
			}
			else
			{
				str_ << " }";
			}
		}
	}

	template<bool IsWide_, class Str_>
	constexpr inline void _matrix_append_to_stream_element_separation(Str_& str_)
	{
		if constexpr (IsWide_)
		{
			str_ << L", ";
		}
		else
		{
			str_ << ", ";
		}
	}

	template
	<
		std::size_t ColumnIndex_,
		std::size_t RowIndex_,
		bool IsWide_,
		bool AppendAsRows_,
		class Str_,
		std::size_t NumColumns_,
		std::size_t NumRows_,
		typename T_,
		bool IsColumnMajor_
	>
	constexpr inline void _matrix_append_to_stream(Str_& str_, const EmuMath::Matrix<NumColumns_, NumRows_, T_, IsColumnMajor_>& matrix_)
	{
		if constexpr (AppendAsRows_)
		{
			// APPENDING AS ROWS
			if constexpr (RowIndex_ < NumRows_)
			{
				if constexpr (ColumnIndex_ < NumColumns_)
				{
					// Append opener if needed
					if constexpr (ColumnIndex_ == 0)
					{
						_matrix_append_to_stream_open_major_chunk<IsWide_>(str_);
					}

					str_ << matrix_.template at<ColumnIndex_, RowIndex_>();

					// Append separator or closer as needed, and move on to next iteration
					// --- If more remains of the row, increment the column index and maintain row index
					// --- Otherwise, increment the row index and reset column index to 0
					if constexpr ((ColumnIndex_ + 1) < NumColumns_)
					{
						_matrix_append_to_stream_element_separation<IsWide_>(str_);
						_matrix_append_to_stream<ColumnIndex_ + 1, RowIndex_, IsWide_, AppendAsRows_>(str_, matrix_);
					}
					else
					{
						_matrix_append_to_stream_close_major_chunk<RowIndex_, NumRows_, IsWide_>(str_);
						_matrix_append_to_stream<0, RowIndex_ + 1, IsWide_, AppendAsRows_>(str_, matrix_);
					}
				}
				else
				{
					_matrix_append_to_stream<0, RowIndex_ + 1, IsWide_, AppendAsRows_>(str_, matrix_);
				}
			}
		}
		else
		{
			// APPENDING AS COLUMNS
			if constexpr (ColumnIndex_ < NumColumns_)
			{
				if constexpr (RowIndex_ < NumRows_)
				{
					// Append opener if needed
					if constexpr (RowIndex_ == 0)
					{
						_matrix_append_to_stream_open_major_chunk<IsWide_>(str_);
					}

					str_ << matrix_.template at<ColumnIndex_, RowIndex_>();

					// Append separator or closer as needed, and move on to next iteration
					// --- If more remains of the column, maintain column index and increment the row index
					// --- Otherwise, increment the column index and reset the row index to 0
					if constexpr ((RowIndex_ + 1) < NumRows_)
					{
						_matrix_append_to_stream_element_separation<IsWide_>(str_);
						_matrix_append_to_stream<ColumnIndex_, RowIndex_ + 1, IsWide_, AppendAsRows_>(str_, matrix_);
					}
					else
					{
						_matrix_append_to_stream_close_major_chunk<ColumnIndex_, NumColumns_, IsWide_>(str_);
						_matrix_append_to_stream<ColumnIndex_ + 1, 0, IsWide_, AppendAsRows_>(str_, matrix_);
					}
				}
				else
				{
					_matrix_append_to_stream<ColumnIndex_ + 1, 0, IsWide_, AppendAsRows_>(str_, matrix_);
				}
			}
		}
	}

	template<bool IsWide_, bool AppendAsRows_, class Str_, std::size_t NumColumns_, std::size_t NumRows_, typename T_, bool IsColumnMajor_>
	constexpr inline Str_& _matrix_append_to_stream(Str_& str_, const EmuMath::Matrix<NumColumns_, NumRows_, T_, IsColumnMajor_>& matrix_)
	{
		_matrix_append_to_stream<0, 0, IsWide_, AppendAsRows_>(str_, matrix_);
		return str_;
	}
}

#endif
