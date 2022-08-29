#ifndef EMU_MATH_FAST_MATRIX_STORE_H_INC_
#define EMU_MATH_FAST_MATRIX_STORE_H_INC_ 1

#include "_common_fast_matrix_helper_includes.h"

namespace EmuMath::Helpers
{
	template<bool ZeroNonEncapsulated_ = true, EmuConcepts::EmuFastMatrix FastMatrix_, EmuConcepts::EmuMatrix OutMatrix_>
	requires (!std::is_const_v<OutMatrix_>)
	constexpr inline void fast_matrix_store(FastMatrix_&& in_fast_matrix_, OutMatrix_& out_scalar_matrix_)
	{
		using _fast_mat_uq = typename EmuCore::TMP::remove_ref_cv<FastMatrix_>::type;
		using _out_mat_uq = typename EmuCore::TMP::remove_ref_cv<OutMatrix_>::type;
		constexpr std::size_t out_matching_major_count = _fast_mat_uq::is_column_major ? _out_mat_uq::num_columns : _out_mat_uq::num_rows;
		constexpr std::size_t majors_to_store = EmuCore::TMP::smallest_constant_v<std::size_t, _fast_mat_uq::num_major_elements, out_matching_major_count>;
		constexpr std::size_t register_size = _fast_mat_uq::num_elements_per_register;
		constexpr std::size_t out_register_fill_count =
		(
			(_out_mat_uq::num_non_major_elements / register_size) +
			((_out_mat_uq::num_non_major_elements % register_size) == 0 ? 0 : 1)
		);
		constexpr std::size_t registers_per_major = _fast_mat_uq::num_registers_per_major;
		constexpr std::size_t registers_to_store_per_major = EmuCore::TMP::smallest_constant_v<std::size_t, registers_per_major, out_register_fill_count>;

		using major_index_sequence = std::make_index_sequence<majors_to_store>;
		using register_index_sequence = std::make_index_sequence<registers_to_store_per_major>;
		_fast_matrix_underlying::_store_to_scalar_matrix
		(
			out_scalar_matrix_,
			std::forward<FastMatrix_>(in_fast_matrix_),
			major_index_sequence(),
			register_index_sequence()
		);

		if constexpr (ZeroNonEncapsulated_)
		{
			// Separate branch if we have both columns and rows instead of merging both branches to avoid a duplicate index
			if constexpr (_out_mat_uq::num_columns > _fast_mat_uq::num_columns && _out_mat_uq::num_rows > _fast_mat_uq::num_rows)
			{
				using column_index_sequences = EmuMath::TMP::make_ranged_matrix_index_sequences
				<
					_fast_mat_uq::num_columns,
					_out_mat_uq::num_columns,
					0,
					_out_mat_uq::num_rows,
					_out_mat_uq::is_column_major
				>;
				using columns_column_sequence = typename column_index_sequences::column_index_sequence;
				using columns_row_sequence = typename column_index_sequences::row_index_sequence;
				_fast_matrix_underlying::_zero_scalar_range(out_scalar_matrix_, columns_column_sequence(), columns_row_sequence());

				using row_index_sequences = EmuMath::TMP::make_ranged_matrix_index_sequences
				<
					0,
					_out_mat_uq::num_columns - 1,
					_fast_mat_uq::num_rows,
					_out_mat_uq::num_rows,
					_out_mat_uq::is_column_major
				>;
				using rows_column_sequence = typename row_index_sequences::column_index_sequence;
				using rows_row_sequence = typename row_index_sequences::row_index_sequence;
				_fast_matrix_underlying::_zero_scalar_range(out_scalar_matrix_, rows_column_sequence(), rows_row_sequence());
			}
			else if constexpr (_out_mat_uq::num_columns > _fast_mat_uq::num_columns)
			{
				using index_sequences = EmuMath::TMP::make_ranged_matrix_index_sequences
				<
					_fast_mat_uq::num_columns,
					_out_mat_uq::num_columns,
					0,
					_out_mat_uq::num_rows,
					_out_mat_uq::is_column_major
				>;
				using column_sequence = typename index_sequences::column_index_sequence;
				using row_sequence = typename index_sequences::row_index_sequence;
				_fast_matrix_underlying::_zero_scalar_range(out_scalar_matrix_, column_sequence(), row_sequence());
			}
			else if constexpr (_out_mat_uq::num_rows > _fast_mat_uq::num_rows)
			{
				using index_sequences = EmuMath::TMP::make_ranged_matrix_index_sequences
				<
					0,
					_out_mat_uq::num_columns,
					_fast_mat_uq::num_rows,
					_out_mat_uq::num_rows,
					_out_mat_uq::is_column_major
				>;
				using column_sequence = typename index_sequences::column_index_sequence;
				using row_sequence = typename index_sequences::row_index_sequence;
				_fast_matrix_underlying::_zero_scalar_range(out_scalar_matrix_, column_sequence(), row_sequence());
			}
		}
	}
}

#endif
