#ifndef EMU_MATH_FAST_MATRIX_UNDERLYING_STORE_H_INC_
#define EMU_MATH_FAST_MATRIX_UNDERLYING_STORE_H_INC_ 1

#include "_fast_matrix_tmp.h"

namespace EmuMath::Helpers::_fast_matrix_underlying
{
	template<EmuConcepts::EmuFastMatrix FastMatrix_, typename Data_, std::size_t...MajorIndices_>
	constexpr inline void _dump_data
	(
		FastMatrix_&& fast_matrix_,
		Data_* p_out_,
		std::index_sequence<MajorIndices_...> major_index_sequence_
	)
	{
		if constexpr(!std::is_const_v<Data_>)
		{
			using _fast_mat_uq = typename EmuCore::TMP::remove_ref_cv<FastMatrix_>::type;

			// Variadically output to all required indices
			// --- False-positive warning silenced as correct use will never have repeated index accesses
#pragma warning(push)
#pragma warning(disable: 26800)
			(
				(
					std::forward<FastMatrix_>(fast_matrix_).major_vectors[MajorIndices_].template Store<true>
					(
						p_out_ + (MajorIndices_ * _fast_mat_uq::full_width_size_per_major)
					)
				), ...
			);
#pragma warning(pop)
		}
		else
		{
			static_assert
			(
				EmuCore::TMP::get_false<Data_>(),
				"Unable to dump data from an EmuMath FastMatrix as the output pointer is const-qualified."
			);
		}
	}

	template<std::size_t MajorIndex_, std::size_t OutputSize_, std::size_t OutputNumNonMajors_, EmuConcepts::EmuFastMatrix FastMatrix_, typename OutData_>
	constexpr inline void _dump_data_from_major_index_contained_only
	(
		FastMatrix_&& fast_matrix_,
		OutData_* p_out_
	)
	{
		if constexpr (!std::is_const_v<OutData_>)
		{
			using _fast_mat_uq = typename EmuCore::TMP::remove_ref_cv<FastMatrix_>::type;
			using out_uq = typename EmuCore::TMP::remove_ref_cv<OutData_>::type;
			constexpr std::size_t current_begin_index = MajorIndex_ * OutputNumNonMajors_;
			constexpr std::size_t required_size_for_direct_load = current_begin_index + _fast_mat_uq::full_width_size_per_major;

			if constexpr (std::is_same_v<out_uq, typename _fast_mat_uq::value_type> && OutputSize_ >= required_size_for_direct_load)
			{
				// We can do an unconstrained load in this scenario, so prefer that
				std::forward<FastMatrix_>(fast_matrix_).major_vectors[MajorIndex_].template Store<true>
				(
					p_out_ + current_begin_index
				);
			}
			else
			{
				// We need to constrain the load, so some performance is lost here
				std::forward<FastMatrix_>(fast_matrix_).major_vectors[MajorIndex_].template Store<false>
				(
					p_out_ + current_begin_index
				);
			}
		}
		else
		{
			static_assert
			(
				EmuCore::TMP::get_false<OutData_>,
				"Unable to dump data from an EmuMath FastMatrix's Major Vector as the output pointer is const-qualified."
			);
		}
	}

	template<std::size_t OutputSize_, std::size_t OutputNumNonMajors_, EmuConcepts::EmuFastMatrix FastMatrix_, typename OutData_, std::size_t...MajorIndices_>
	constexpr inline void _dump_data_contained_only
	(
		FastMatrix_&& fast_matrix_,
		OutData_* p_out_,
		std::index_sequence<MajorIndices_...> major_index_sequence_
	)
	{
#pragma warning(push)
#pragma warning(disable: 26800)
		(
			(
				_dump_data_from_major_index_contained_only<MajorIndices_, OutputSize_, OutputNumNonMajors_>
				(
					std::forward<FastMatrix_>(fast_matrix_), 
					p_out_
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

	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, bool OutColumnMajor_, std::size_t...ColumnIndices_, std::size_t...RowIndices_>
	constexpr inline void _zero_scalar_matrix
	(
		EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>& out_matrix_,
		std::index_sequence<ColumnIndices_...> column_indices_,
		std::index_sequence<RowIndices_...> row_indices_
	)
	{
		(
			(
				out_matrix_.template at<ColumnIndices_, RowIndices_>() = EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>::get_implied_zero()
			), ...
		);
	}

	template
	<
		std::size_t ColumnIndex_, std::size_t RowIndex_, EmuConcepts::EmuFastMatrix FastMatrix_, typename Data_,
		std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, bool OutColumnMajor_
	>
	constexpr inline void _move_dump_index_to_scalar_matrix(EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>& out_matrix_, Data_* p_data_)
	{
		using _fast_mat_uq = typename EmuCore::TMP::remove_ref_cv<FastMatrix_>::type;
		if constexpr (ColumnIndex_ < _fast_mat_uq::num_columns && RowIndex_ < _fast_mat_uq::num_rows)
		{
			constexpr std::size_t major_index = _fast_mat_uq::is_column_major ? ColumnIndex_ : RowIndex_;
			constexpr std::size_t non_major_index = _fast_mat_uq::is_column_major ? RowIndex_ : ColumnIndex_;

			// Offset major index by full register size as we dump all data from a major for better efficiency
			constexpr std::size_t flattened_index = (major_index * _fast_mat_uq::full_width_size_per_major) + non_major_index;
			EmuCore::TMP::assign_direct_or_cast<typename EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>::value_type_uq>
			(
				out_matrix_,
				std::move(*(p_data_ + flattened_index))
			);
		}
		else
		{
			out_matrix_.template at<ColumnIndex_, RowIndex_>() = EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>::get_implied_zero();
		}
	}

	template
	<
		EmuConcepts::EmuFastMatrix FastMatrix_, std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, bool OutColumnMajor_,
		typename Data_, std::size_t...ColumnIndices_, std::size_t...RowIndices_
	>
	constexpr inline void _move_dump_to_scalar_matrix
	(
		EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>& out_matrix_,
		Data_* p_data_,
		std::index_sequence<ColumnIndices_...> column_indices_,
		std::index_sequence<RowIndices_...> row_indices_
	)
	{
		(
			_move_dump_index_to_scalar_matrix<ColumnIndices_, RowIndices_, FastMatrix>
			(
				out_matrix_,
				p_data_
			), ...
		);
	}
}

#endif
