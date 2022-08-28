#ifndef EMU_MATH_FAST_MATRIX_ARITHMETIC_H_INC_
#define EMU_MATH_FAST_MATRIX_ARITHMETIC_H_INC_ 1

#include "_common_fast_matrix_helper_includes.h"

namespace EmuMath::Helpers
{
	template<EmuConcepts::EmuFastMatrix LhsFastMatrix_, EmuConcepts::EmuFastMatrix RhsFastMatrix_>
	requires EmuConcepts::EmuFastMatrixMultPair<LhsFastMatrix_, RhsFastMatrix_>
	[[nodiscard]] constexpr inline auto fast_matrix_multiply(LhsFastMatrix_&& lhs_fast_matrix_, RhsFastMatrix_&& rhs_fast_matrix_)
		-> typename EmuMath::TMP::fast_matrix_multiply_result<LhsFastMatrix_, RhsFastMatrix_>::type
	{
		using _lhs_fast_mat_uq = typename EmuCore::TMP::remove_ref_cv<LhsFastMatrix_>::type;
		using _rhs_fast_mat_uq = typename EmuCore::TMP::remove_ref_cv<RhsFastMatrix_>::type;
		if constexpr (_lhs_fast_mat_uq::is_column_major)
		{
			constexpr std::size_t lhs_used_size =
			(
				_lhs_fast_mat_uq::num_rows < _lhs_fast_mat_uq::num_columns ?
				_lhs_fast_mat_uq::num_rows :
				_lhs_fast_mat_uq::num_columns
			);

			using rhs_column_indices = std::make_index_sequence<_rhs_fast_mat_uq::num_columns>;
			using lhs_column_indices_except_0 = EmuCore::TMP::make_offset_index_sequence<1, lhs_used_size - 1>;
			return _fast_matrix_underlying::_do_multiply_cm_any
			(
				std::forward<LhsFastMatrix_>(lhs_fast_matrix_),
				std::forward<RhsFastMatrix_>(rhs_fast_matrix_),
				rhs_column_indices(),
				lhs_column_indices_except_0()
			);
		}
		else
		{
			constexpr std::size_t rhs_used_size =
			(
				_rhs_fast_mat_uq::num_columns < _rhs_fast_mat_uq::num_rows ?
				_rhs_fast_mat_uq::num_columns :
				_rhs_fast_mat_uq::num_rows
			);

			using lhs_row_indices = std::make_index_sequence<_lhs_fast_mat_uq::num_rows>;
			using rhs_row_indices_except_0 = EmuCore::TMP::make_offset_index_sequence<1, rhs_used_size - 1>;
			return _fast_matrix_underlying::_do_multiply_rm_rm
			(
				std::forward<LhsFastMatrix_>(lhs_fast_matrix_),
				std::forward<RhsFastMatrix_>(rhs_fast_matrix_),
				lhs_row_indices(),
				rhs_row_indices_except_0()
			);
		}
	}
}

#endif
