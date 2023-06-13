#ifndef EMU_MATH_UNDERLYING_MATRIX_STREAM_APPEND_H_INC_
#define EMU_MATH_UNDERLYING_MATRIX_STREAM_APPEND_H_INC_ 1

#include "_matrix_tmp.h"

namespace EmuMath::Helpers::_matrix_underlying
{
	template<bool IsWide_, class Stream_>
	inline void _append_matrix_chunk_opener(Stream_& str_)
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

	template<bool IsWide_, class Stream_>
	inline void _append_matrix_chunk_closer(Stream_& str_)
	{
		if constexpr (IsWide_)
		{
			str_ << L" }";
		}
		else
		{
			str_ << " }";
		}
	}

	template<bool IsWide_, class Stream_>
	inline void _append_matrix_empty_chunk(Stream_& str_)
	{
		if constexpr (IsWide_)
		{
			str_ << L"{ }";
		}
		else
		{
			str_ << "{ }";
		}
	}

	template<bool IsWide_, class Stream_>
	inline void _append_matrix_new_line_for_chunk(Stream_& str_)
	{
		if constexpr (IsWide_)
		{
			str_ << L",\n";
		}
		else
		{
			str_ << ",\n";
		}
	}

	template<bool IsWide_, class Stream_>
	inline void _append_matrix_value_separator(Stream_& str_)
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

	template<std::size_t ChunkIndex_, std::size_t IndexInChunk_, bool IsWide_, bool ChunkIsRow_, bool AppendSeparatorAfterValue_, std::size_t NumColumns_, std::size_t NumRows_, typename T_, bool InColumnMajor_, class Stream_>
	inline void _append_matrix_chunk_value_to_stream(Stream_& str_, const EmuMath::Matrix<NumColumns_, NumRows_, T_, InColumnMajor_>& matrix_)
	{
		constexpr std::size_t column_index = ChunkIsRow_ ? IndexInChunk_ : ChunkIndex_;
		constexpr std::size_t row_index = ChunkIsRow_ ? ChunkIndex_ : IndexInChunk_;
		str_ << matrix_.template at<column_index, row_index>();

		if constexpr (AppendSeparatorAfterValue_)
		{
			_append_matrix_value_separator<IsWide_>(str_);
		}
	}

	template<std::size_t ChunkIndex_, bool IsWide_, bool ChunkIsRow_, bool AppendNewLineAtStart_, std::size_t NumColumns_, std::size_t NumRows_, typename T_, bool InColumnMajor_, class Stream_, std::size_t...IndicesInChunk_>
	inline void _append_matrix_chunk_to_stream
	(
		Stream_& str_,
		const EmuMath::Matrix<NumColumns_, NumRows_, T_, InColumnMajor_>& matrix_,
		std::index_sequence<IndicesInChunk_...> indices_in_chunk_
	)
	{
		if constexpr (AppendNewLineAtStart_)
		{
			_append_matrix_new_line_for_chunk<IsWide_>(str_);
		}

		if constexpr (sizeof...(IndicesInChunk_) == 0)
		{
			_append_matrix_empty_chunk<IsWide_>(str_);
		}
		else
		{
			constexpr std::size_t chunk_end_index = sizeof...(IndicesInChunk_) - 1;
			_append_matrix_chunk_opener<IsWide_>(str_);

			(
				_append_matrix_chunk_value_to_stream<ChunkIndex_, IndicesInChunk_, IsWide_, ChunkIsRow_, (IndicesInChunk_ != chunk_end_index)>
				(
					str_,
					matrix_
				), ...
			);

			_append_matrix_chunk_closer<IsWide_>(str_);
		}
	}

	template<bool IsWide_, bool PrintAsRows_, std::size_t NumColumns_, std::size_t NumRows_, typename T_, bool InColumnMajor_, class Stream_, std::size_t...ColumnIndices_, std::size_t...RowIndices_>
	inline void _append_matrix_to_stream
	(
		Stream_& str_,
		const EmuMath::Matrix<NumColumns_, NumRows_, T_, InColumnMajor_>& matrix_,
		std::index_sequence<ColumnIndices_...> column_indices_,
		std::index_sequence<RowIndices_...> row_indices_
	)
	{
		if constexpr (NumRows_ == 0 || NumColumns_ == 0)
		{
			_append_matrix_empty_chunk<IsWide_>(str_);
		}
		else
		{
			if constexpr (PrintAsRows_)
			{
				(
					_append_matrix_chunk_to_stream<RowIndices_, IsWide_, true, (RowIndices_ != 0)>
					(
						str_,
						matrix_,
						std::index_sequence<ColumnIndices_...>()
					), ...
				);
			}
			else
			{
				(
					_append_matrix_chunk_to_stream<ColumnIndices_, IsWide_, true, (ColumnIndices_ != 0)>
					(
						str_,
						matrix_,
						std::index_sequence<RowIndices_...>()
					), ...
				);
			}
		}
	}

	template<bool IsWide_, bool PrintAsRows_, std::size_t NumColumns_, std::size_t NumRows_, typename T_, bool InColumnMajor_, class Stream_>
	inline Stream_& _append_matrix_to_stream(Stream_& str_, const EmuMath::Matrix<NumColumns_, NumRows_, T_, InColumnMajor_>& matrix_)
	{
		using column_indices = std::make_index_sequence<NumColumns_>;
		using row_indices = std::make_index_sequence<NumRows_>;
		_append_matrix_to_stream<IsWide_, PrintAsRows_>(str_, matrix_, column_indices(), row_indices());
		return str_;
	}
}

#endif
