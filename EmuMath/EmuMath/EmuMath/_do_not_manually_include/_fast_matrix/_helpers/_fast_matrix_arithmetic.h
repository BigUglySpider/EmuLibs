#ifndef EMU_MATH_COMMON_FAST_MATRIX_ARITHMETIC_H_INC_
#define EMU_MATH_COMMON_FAST_MATRIX_ARITHMETIC_H_INC_ 1

#include "_common_fast_matrix_helper_includes.h"

namespace EmuMath::Helpers
{
	template<class LhsMatrix_, class RhsMatrix_>
	requires EmuConcepts::EmuFastMatrixMultPair<LhsMatrix_, RhsMatrix_>
	[[nodiscard]] constexpr inline auto fast_matrix_multiply(LhsMatrix_&& lhs_matrix_, RhsMatrix_&& rhs_matrix_)
	{
		// TODO: MULTIPLY
		using _lhs_mat_uq = typename EmuCore::TMP::remove_ref_cv<LhsMatrix_>::type;
		using _rhs_mat_uq = typename EmuCore::TMP::remove_ref_cv<RhsMatrix_>::type;

		if constexpr (true)
		{
			return _fast_matrix_underlying::_updated_multiply
			(
				lhs_matrix_,
				rhs_matrix_,
				std::make_index_sequence<_rhs_mat_uq::num_major_elements>()
			);
		}
		else
		{ // NAIVE BRANCH
			if constexpr (_lhs_mat_uq::is_row_major)
			{
				if constexpr (_rhs_mat_uq::is_column_major)
				{
					constexpr std::size_t out_columns = _lhs_mat_uq::num_columns;
					constexpr std::size_t out_rows = _rhs_mat_uq::num_rows;
					constexpr std::size_t register_width = _lhs_mat_uq::register_width;
					constexpr bool cm = false;
					using _out_mat = EmuMath::FastMatrix<out_columns, out_rows, typename _lhs_mat_uq::value_type, cm, register_width>;
					using out_indices = EmuMath::TMP::make_full_matrix_index_sequences<EmuMath::Matrix<out_columns, out_rows, typename _lhs_mat_uq::value_type, !cm>>;
					using out_column_indices = typename out_indices::column_index_sequence;
					using out_row_indices = typename out_indices::row_index_sequence;

					return _fast_matrix_underlying::_naive_multiply_impl_rm_cm<_out_mat>
					(
						std::forward<LhsMatrix_>(lhs_matrix_),
						std::forward<RhsMatrix_>(rhs_matrix_),
						out_column_indices(),
						out_row_indices()
					);
				}
				else
				{
					static_assert(EmuCore::TMP::get_false<RhsMatrix_>(), "Not implemented FastMat multiply with rhs row-major");
				}
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<RhsMatrix_>(), "Not implemented FastMat multiply with lhs column-major");
			}
		}
	}
}

#endif
