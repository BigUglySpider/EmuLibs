#ifndef EMU_MATH_FAST_MATRIX_MISC_ARITHMETIC_H_INC_
#define EMU_MATH_FAST_MATRIX_MISC_ARITHMETIC_H_INC_ 1

#include "_common_fast_matrix_helper_includes.h"

namespace EmuMath::Helpers
{
#pragma region ROUNDS
	template<EmuConcepts::EmuFastMatrix FastMatrix_>
	[[nodiscard]] constexpr inline auto fast_matrix_abs(FastMatrix_&& fast_matrix_)
		-> typename std::remove_cvref<FastMatrix_>::type
	{
		return _fast_matrix_underlying::_fast_matrix_abs<false>(std::forward<FastMatrix_>(fast_matrix_));
	}
#pragma endregion
}

#endif
