#ifndef EMU_MATH_MATRIX_HELPERS_H_INC_
#define EMU_MATH_MATRIX_HELPERS_H_INC_ 1

#include "_helpers/_common_matrix_helper_includes.h"
#include "_helpers/_matrix_arithmetic.h"
#include "_helpers/_matrix_bitwise.h"
#include "_helpers/_matrix_comparisons.h"
#include "_helpers/_matrix_gets.h"
#include "_helpers/_matrix_operations.h"
#include "_helpers/matrix_projections_.h"
#include "_helpers/_matrix_reinterpretations.h"
#include "_helpers/_matrix_sets.h"
#include "_helpers/_matrix_transformations.h"

#include "../../../EmuCore/Functors/Arithmetic.h"

namespace EmuCore
{
	template<std::size_t NumColumns_, std::size_t NumRows_, typename T_, bool ColumnMajor_, class Rhs_>
	struct do_multiply<EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>, Rhs_>
	{
		constexpr do_multiply()
		{
		}
		constexpr inline auto operator()(const EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>& lhs_, const Rhs_& rhs_) const
		{
			return EmuMath::Helpers::MatrixMultiply(lhs_, rhs_);
		}
	};
}

#endif
