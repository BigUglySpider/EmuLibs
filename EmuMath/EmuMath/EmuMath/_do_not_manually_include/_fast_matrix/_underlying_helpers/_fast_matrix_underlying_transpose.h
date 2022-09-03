#ifndef EMU_MATH_FAST_MATRIX_UNDERLYING_TRANSPOSE_H_INC_
#define EMU_MATH_FAST_MATRIX_UNDERLYING_TRANSPOSE_H_INC_ 1

#include "_fast_matrix_tmp.h"
#include "_fast_matrix_underlying_store.h"

namespace EmuMath::Helpers::_fast_matrix_underlying
{
	template<EmuConcepts::EmuFastMatrix FastMatUq_>
	[[nodiscard]] constexpr inline bool _valid_for_4x4_square_transpose_32bit()
	{
		return
		(
			FastMatUq_::num_major_elements == 4 &&
			FastMatUq_::num_registers_per_major == 1 &&
			FastMatUq_::register_width == 128 &&
			FastMatUq_::num_columns == FastMatUq_::num_rows &&
			FastMatUq_::per_element_width == 32 &&
			std::is_floating_point_v<typename FastMatUq_::value_type>
		);
	}

	template<EmuConcepts::EmuFastMatrix FastMatrix_>
	[[nodiscard]] constexpr inline auto _make_transpose_same_major_4x4_32bit(const FastMatrix_& in_matrix_)
		-> typename EmuMath::TMP::fast_matrix_transpose_result<FastMatrix_>::type
	{
		using _fast_mat_uq = typename EmuCore::TMP::remove_ref_cv<FastMatrix_>::type;
		typename _fast_mat_uq::register_type major_0011_hi = EmuSIMD::shuffle<2, 3, 2, 3>(in_matrix_.major_chunks[0], in_matrix_.major_chunks[1]);
		typename _fast_mat_uq::register_type major_2233_hi = EmuSIMD::shuffle<2, 3, 2, 3>(in_matrix_.major_chunks[2], in_matrix_.major_chunks[3]);
		typename _fast_mat_uq::register_type major_0011_lo = EmuSIMD::shuffle<0, 1, 0, 1>(in_matrix_.major_chunks[0], in_matrix_.major_chunks[1]);
		typename _fast_mat_uq::register_type major_2233_lo = EmuSIMD::shuffle<0, 1, 0, 1>(in_matrix_.major_chunks[2], in_matrix_.major_chunks[3]);

		return typename EmuMath::TMP::fast_matrix_transpose_result<FastMatrix_>::type
		(
			EmuSIMD::shuffle<0, 2, 0, 2>(major_0011_lo, major_2233_lo),
			EmuSIMD::shuffle<1, 3, 1, 3>(major_0011_lo, major_2233_lo),
			EmuSIMD::shuffle<0, 2, 0, 2>(major_0011_hi, major_2233_hi),
			EmuSIMD::shuffle<1, 3, 1, 3>(major_0011_hi, major_2233_hi)
		);
	}

	template<EmuConcepts::EmuFastMatrix InFastMatrix_, typename InData_, std::size_t...MajorIndices_, std::size_t...NonMajorIndices_>
	[[nodiscard]] constexpr inline auto _make_transpose_from_stored_data
	(
		InData_* p_in_data_,
		std::index_sequence<MajorIndices_...> major_indices_,
		std::index_sequence<NonMajorIndices_...> non_major_indices_
	) -> typename EmuMath::TMP::fast_matrix_transpose_result<InFastMatrix_>::type
	{
		using _in_fast_mat_uq = typename EmuCore::TMP::remove_ref_cv<InFastMatrix_>::type;
		return typename EmuMath::TMP::fast_matrix_transpose_result<InFastMatrix_>::type
		(
			(*(p_in_data_ + (NonMajorIndices_ * _in_fast_mat_uq::num_non_major_elements) + MajorIndices_))...
		);
	}

	template<EmuConcepts::EmuFastMatrix FastMatrix_>
	[[nodiscard]] constexpr inline auto _make_transpose_same_major(FastMatrix_&& in_matrix_)
		-> typename EmuMath::TMP::fast_matrix_transpose_result<FastMatrix_>::type
	{
		using _fast_mat_uq = typename EmuCore::TMP::remove_ref_cv<FastMatrix_>::type;
		if constexpr (_valid_for_4x4_square_transpose_32bit<_fast_mat_uq>())
		{
			return _make_transpose_same_major_4x4_32bit
			(
				EmuCore::TMP::const_lval_ref_cast<FastMatrix_>(std::forward<FastMatrix_>(in_matrix_))
			);
		}
		else
		{
			// Generic approach, we do a `store -> set` to transpose instead of a SIMD shuffle approach
			using major_indices = std::make_index_sequence<_fast_mat_uq::num_major_elements>;
			using register_indices = std::make_index_sequence<_fast_mat_uq::num_registers_per_major>;

			constexpr std::size_t data_dump_size = _fast_mat_uq::expected_count_for_default_load_pointer;
			typename _fast_mat_uq::value_type data_dump[data_dump_size];
			_store_to_data_pointer<false>(std::forward<FastMatrix_>(in_matrix_), data_dump, major_indices(), register_indices());

			using index_sequences = EmuMath::TMP::make_ranged_matrix_index_sequences
			<
				0,
				_fast_mat_uq::num_columns,
				0,
				_fast_mat_uq::num_rows,
				!_fast_mat_uq::is_column_major
			>;
			using column_indices = typename index_sequences::column_index_sequence;
			using row_indices = typename index_sequences::row_index_sequence;
			using out_major_indices = typename std::conditional<_fast_mat_uq::is_column_major, row_indices, column_indices>::type;
			using out_non_major_indices = typename std::conditional<_fast_mat_uq::is_column_major, column_indices, row_indices>::type;

#pragma warning(push)
#pragma warning(disable: 26800)
			// We pass major and non-major in reverse since that will be the case for the output Matrix
			return _make_transpose_from_stored_data<FastMatrix_>(data_dump, out_major_indices(), out_non_major_indices());
#pragma warning(pop)
		}
	}
}

#endif
