#ifndef EMU_MATH_FAST_MATRIX_STORE_H_INC_
#define EMU_MATH_FAST_MATRIX_STORE_H_INC_ 1

#include "_common_fast_matrix_helper_includes.h"

namespace EmuMath::Helpers
{
	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, bool OutColumnMajor_ = true, class FastMatrix_>
	requires EmuConcepts::EmuFastMatrix<FastMatrix_>
	[[nodiscard]] constexpr inline auto fast_matrix_store(FastMatrix_&& fast_matrix_)
		-> EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>
	{
		using _out_mat = EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>;
		using _fast_mat_uq = typename EmuCore::TMP::remove_ref_cv<FastMatrix_>::type;
		
		// Determine dump size - If the output has less of whatever the input major is, we can skip unnecessary stores to memory
		constexpr std::size_t in_major_size_for_out = _fast_mat_uq::is_column_major ? _out_mat::num_columns : _out_mat::num_rows;
		constexpr std::size_t majors_in_dump = EmuCore::TMP::smallest_constant_v<std::size_t, in_major_size_for_out, _fast_mat_uq::num_major_elements>;

		// Contiguous dump of required majors for output
		typename _fast_mat_uq::value_type data_dump[majors_in_dump * _fast_mat_uq::full_width_size_per_major];
		_fast_matrix_underlying::_dump_data(std::forward<FastMatrix_>(fast_matrix_), data_dump, std::make_index_sequence<majors_in_dump>());

		using out_indices = EmuMath::TMP::make_full_matrix_index_sequences<_out_mat>;
		using out_column_indices = typename out_indices::column_index_sequence;
		using out_row_indices = typename out_indices::row_index_sequence;
		return _fast_matrix_underlying::_make_scalar_matrix_from_dump_data<EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>, FastMatrix_>
		(
			data_dump,
			out_column_indices(),
			out_row_indices()
		);
	}
}

#endif
