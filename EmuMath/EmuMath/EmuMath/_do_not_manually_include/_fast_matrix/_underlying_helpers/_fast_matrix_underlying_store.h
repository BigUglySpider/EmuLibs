#ifndef EMU_MATH_FAST_MATRIX_UNDERLYING_STORE_H_INC_
#define EMU_MATH_FAST_MATRIX_UNDERLYING_STORE_H_INC_ 1

#include "_fast_matrix_tmp.h"

namespace EmuMath::Helpers::_fast_matrix_underlying
{
	template<EmuConcepts::EmuFastMatrix FastMatrix_, std::size_t...MajorIndices_>
	constexpr inline void _dump_data
	(
		FastMatrix_&& fast_matrix_,
		typename EmuCore::TMP::remove_ref_cv_t<FastMatrix_>::value_type* p_out_,
		std::index_sequence<MajorIndices_...> major_index_sequence_
	)
	{
		using _fast_mat_uq = typename EmuCore::TMP::remove_ref_cv<FastMatrix_>::type;

		// Variadically output to all required indices
		// --- False-positive warning silenced as correct use will never have repeated index accesses
#pragma warning(push)
#pragma warning(disable: 26800)
		(
			(
				std::forward<FastMatrix_>(fast_matrix_).major_vectors[MajorIndices_].template Store<false>
				(
					p_out_ + (MajorIndices_ * _fast_mat_uq::full_width_size_per_major)
				)
			), ...
		);
#pragma warning(pop)
	}

	template<std::size_t ColumnIndex_, std::size_t RowIndex_, EmuConcepts::EmuMatrix OutMatrix_, EmuConcepts::EmuFastMatrix FastMatrix_, class Data_>
	[[nodiscard]] constexpr inline decltype(auto) _get_raw_arg_for_scalar_matrix_from_dump_data(Data_* p_data_)
	{
		using _fast_mat_uq = typename EmuCore::TMP::remove_ref_cv<FastMatrix_>::type;
		if constexpr (ColumnIndex_ < _fast_mat_uq::num_columns && RowIndex_ < _fast_mat_uq::num_rows)
		{
			constexpr std::size_t major_index = _fast_mat_uq::is_column_major ? ColumnIndex_ : RowIndex_;
			constexpr std::size_t non_major_index = _fast_mat_uq::is_column_major ? RowIndex_ : ColumnIndex_;

			// Offset major index by full register size as we dump all data from a major for better efficiency
			constexpr std::size_t flattened_index = (major_index * _fast_mat_uq::full_width_size_per_major) + non_major_index;
			return std::move(*(p_data_ + flattened_index));
		}
		else
		{
			using _out_mat_uq = typename EmuCore::TMP::remove_ref_cv<OutMatrix_>::type;
			return _out_mat_uq::get_implied_zero();
		}
	}

	template<EmuConcepts::EmuMatrix OutMatrix_, EmuConcepts::EmuFastMatrix FastMatrix_, typename Data_, std::size_t...ColumnIndices_, std::size_t...RowIndices_>
	[[nodiscard]] constexpr inline auto _make_scalar_matrix_from_dump_data
	(
		Data_* p_data_,
		std::index_sequence<ColumnIndices_...> column_indices_,
		std::index_sequence<RowIndices_...> row_indices_
	) -> typename EmuCore::TMP::remove_ref_cv<OutMatrix_>::type
	{
		// We won't be moving the same index of the pointed-to memory twice, so silence this warning for its false positives
#pragma warning(push)
#pragma warning(disable: 26800)
		return typename EmuCore::TMP::remove_ref_cv<OutMatrix_>::type
		(
			_get_raw_arg_for_scalar_matrix_from_dump_data<ColumnIndices_, RowIndices_, OutMatrix_, FastMatrix_>
			(
				p_data_
			)...
		);
#pragma warning(pop)
	}
}

#endif
