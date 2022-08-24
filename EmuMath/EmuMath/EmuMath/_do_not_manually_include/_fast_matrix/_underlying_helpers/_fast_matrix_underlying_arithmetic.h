#ifndef EMU_MATH_FAST_MATRIX_UNDERLYING_ARITHMETIC_H_INC_
#define EMU_MATH_FAST_MATRIX_UNDERLYING_ARITHMETIC_H_INC_ 1

#include "_fast_matrix_tmp.h"
#include "../../../Matrix.h"

namespace EmuMath::Helpers::_fast_matrix_underlying
{
	template<std::size_t ColumnIndex_, std::size_t RowIndex_, EmuConcepts::EmuFastMatrix OutMatrix_, class LhsMatrix_, class RhsMatrix_>
	requires EmuConcepts::EmuFastMatrixMultPair<LhsMatrix_, RhsMatrix_>
	[[nodiscard]] constexpr inline decltype(auto) _naive_multiply_index_rm_cm(LhsMatrix_&& lhs_, RhsMatrix_&& rhs_)
	{
		return lhs_.major_vectors[ColumnIndex_].DotScalar(rhs_.major_vectors[RowIndex_]);
	}

	template<EmuConcepts::EmuFastMatrix OutMatrix_, class LhsMatrix_, class RhsMatrix_, std::size_t...ColumnIndices_, std::size_t...RowIndices_>
	requires EmuConcepts::EmuFastMatrixMultPair<LhsMatrix_, RhsMatrix_>
	[[nodiscard]] constexpr inline auto _naive_multiply_impl_rm_cm
	(
		LhsMatrix_&& lhs_,
		RhsMatrix_&& rhs_,
		std::index_sequence<ColumnIndices_...>,
		std::index_sequence<RowIndices_...>
	)
	{
		return OutMatrix_
		(
			typename OutMatrix_::matrix_type
			(
				_naive_multiply_index_rm_cm<ColumnIndices_, RowIndices_, OutMatrix_>
				(
					std::forward<LhsMatrix_>(lhs_),
					std::forward<RhsMatrix_>(rhs_)
				)...
			)
		);
	}
}

#endif
