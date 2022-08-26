#ifndef EMU_MATH_COMMON_FAST_MATRIX_ARITHMETIC_H_INC_
#define EMU_MATH_COMMON_FAST_MATRIX_ARITHMETIC_H_INC_ 1

#include "_common_fast_matrix_helper_includes.h"

namespace EmuMath::Helpers
{
	template<class LhsMatrix_, class RhsMatrix_>
	requires EmuConcepts::EmuFastMatrixMultPair<LhsMatrix_, RhsMatrix_>
	[[nodiscard]] constexpr inline auto fast_matrix_multiply(LhsMatrix_&& lhs_matrix_, RhsMatrix_&& rhs_matrix_)
	{
		using _rhs_mat_uq = typename EmuCore::TMP::remove_ref_cv<RhsMatrix_>::type;
		return _fast_matrix_underlying::_std_multiply
		(
			lhs_matrix_,
			rhs_matrix_,
			std::make_index_sequence<_rhs_mat_uq::num_major_elements>()
		);
	}
}

#endif
