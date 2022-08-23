#ifndef EMU_MATH_FAST_MATRIX_STORE_H_INC_
#define EMU_MATH_FAST_MATRIX_STORE_H_INC_ 1

#include "_common_fast_matrix_helper_includes.h"

namespace EmuMath::Helpers
{
	/// <summary>
	/// <para> Stores the data of the passed FastMatrix to a normal EmuMath Matrix of the specified type. </para>
	/// <para> 
	///		All arguments for the output Matrix type may be omitted, in which case they will match that of the passed FastMatrix 
	///		(except for `T_`, which will instead be the passed FastMatrix's `value_type`).
	/// </para>
	/// <para> Indices that the passed FastMatrix does not encapsulate will be zeroed. </para>
	/// <para> This may not be used to output references. </para>
	/// </summary>
	/// <param name="fast_matrix_">EmuMath Fast Matrix to retrieve data from.</param>
	/// <returns>EmuMath Matrix of the specified type containing respective data of the passed Matrix's registers.</returns>
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

	/// <summary>
	/// <para> Stores the data of the passed FastMatrix to the passed normal EmuMath Matrix. </para>
	/// <para>
	///		Where possible, data will be stored directly to contiguous chunks of the output Matrix without an intermediate. 
	///		This requires that the output Matrix's `stored_type` is the same as the passed FastMatrix's `value_type`, 
	///		and that is shares the same major storage order.
	/// </para>
	/// <para> Indices that the passed FastMatrix does not encapsulate will be zeroed. </para>
	/// </summary>
	/// <param name="fast_matrix_">EmuMath Fast Matrix to retrieve data from.</param>
	/// <param name="out_matrix_">EmuMath Matrix reference to output respective data to.</param>
	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, bool OutColumnMajor_, class FastMatrix_>
	requires EmuConcepts::EmuFastMatrix<FastMatrix_>
	constexpr inline void fast_matrix_store(FastMatrix_&& fast_matrix_, EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>& out_matrix_)
	{
		using _fast_mat_uq = typename EmuCore::TMP::remove_ref_cv<FastMatrix_>::type;
		if constexpr (OutColumnMajor_ == _fast_mat_uq::is_column_major)
		{
			// We can potentially store directly into the output
			constexpr std::size_t out_size = OutNumColumns_ * OutNumRows_;
			constexpr std::size_t out_num_non_majors = EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>::num_non_major_elements;
			constexpr std::size_t out_num_majors = EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>::num_major_elements;
			constexpr std::size_t num_majors_to_dump = EmuCore::TMP::smallest_constant_v<std::size_t, out_num_majors, _fast_mat_uq::num_major_elements>;
			_fast_matrix_underlying::_dump_data_contained_only<out_size, out_num_non_majors>
			(
				std::forward<FastMatrix_>(fast_matrix_),
				out_matrix_.data(),
				std::make_index_sequence<num_majors_to_dump>()
			);

			// Zero indices that the input Matrix doesn't contain (including those outside of the encapsulated range but contained in registers)
			// --- We have the 3 separate branches as we need to change one index sequence to avoid duplicate indices where the 2 missing segments collide
			// --- in cases where both columns and rows need zeroing
			constexpr bool needs_columns_zeroed = _fast_mat_uq::num_columns < OutNumColumns_;
			constexpr bool needs_rows_zeroed = _fast_mat_uq::num_rows < OutNumRows_;
			if constexpr (needs_columns_zeroed && needs_rows_zeroed)
			{
				// Go all the way with columns, but only do rows up until they collide with columns
				using missing_columns = EmuMath::TMP::make_ranged_matrix_index_sequences<_fast_mat_uq::num_columns, OutNumColumns_, 0, OutNumRows_, OutColumnMajor_>;				
				using missing_columns_column_sequence = typename missing_columns::column_index_sequence;
				using missing_columns_row_sequence = typename missing_columns::row_index_sequence;
				_fast_matrix_underlying::_zero_scalar_matrix(out_matrix_, missing_columns_column_sequence(), missing_columns_row_sequence());

				using missing_rows = EmuMath::TMP::make_ranged_matrix_index_sequences<0, _fast_mat_uq::num_columns, _fast_mat_uq::num_rows, OutNumRows_, OutColumnMajor_>;
				using missing_rows_column_sequence = typename missing_rows::column_index_sequence;
				using missing_rows_row_sequence = typename missing_rows::row_index_sequence;
				_fast_matrix_underlying::_zero_scalar_matrix(out_matrix_, missing_rows_column_sequence(), missing_rows_row_sequence());
			}
			else if constexpr (needs_columns_zeroed)
			{
				using missing_columns = EmuMath::TMP::make_ranged_matrix_index_sequences<_fast_mat_uq::num_columns, OutNumColumns_, 0, OutNumRows_, OutColumnMajor_>;
				using missing_column_sequence = typename missing_columns::column_index_sequence;
				using missing_row_sequence = typename missing_columns::row_index_sequence;
				_fast_matrix_underlying::_zero_scalar_matrix(out_matrix_, missing_column_sequence(), missing_row_sequence());
			}
			else if constexpr (needs_rows_zeroed)
			{
				using missing_rows = EmuMath::TMP::make_ranged_matrix_index_sequences<0, OutNumColumns_, _fast_mat_uq::num_rows, OutNumRows_, OutColumnMajor_>;
				using missing_column_sequence = typename missing_rows::column_index_sequence;
				using missing_row_sequence = typename missing_rows::row_index_sequence;
				_fast_matrix_underlying::_zero_scalar_matrix(out_matrix_, missing_column_sequence(), missing_row_sequence());
			}
		}
		else
		{
			// Can't store directly, so do an intermediate dump
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
			_fast_matrix_underlying::_move_dump_to_scalar_matrix(out_matrix_, data_dump, out_column_indices(), out_row_indices());
		}
	}
}

#endif
