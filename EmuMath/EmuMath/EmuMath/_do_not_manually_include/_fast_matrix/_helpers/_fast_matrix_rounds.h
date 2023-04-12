#ifndef EMU_MATH_FAST_MATRIX_ROUNDS_H_INC_
#define EMU_MATH_FAST_MATRIX_ROUNDS_H_INC_ 1

#include "_common_fast_matrix_helper_includes.h"

namespace EmuMath::Helpers
{
#pragma region ROUNDS
	template<EmuConcepts::EmuFastMatrix FastMatrix_>
	[[nodiscard]] constexpr inline auto fast_matrix_floor(FastMatrix_&& fast_matrix_)
		-> typename std::remove_cvref<FastMatrix_>::type
	{
		return _fast_matrix_underlying::_fast_matrix_floor<false>(std::forward<FastMatrix_>(fast_matrix_));
	}
	
	template<EmuConcepts::EmuFastMatrix FastMatrix_>
	[[nodiscard]] constexpr inline auto fast_matrix_ceil(FastMatrix_&& fast_matrix_)
		-> typename std::remove_cvref<FastMatrix_>::type
	{
		return _fast_matrix_underlying::_fast_matrix_ceil<false>(std::forward<FastMatrix_>(fast_matrix_));
	}
	
	template<EmuConcepts::EmuFastMatrix FastMatrix_>
	[[nodiscard]] constexpr inline auto fast_matrix_trunc(FastMatrix_&& fast_matrix_)
		-> typename std::remove_cvref<FastMatrix_>::type
	{
		return _fast_matrix_underlying::_fast_matrix_trunc<false>(std::forward<FastMatrix_>(fast_matrix_));
	}
	
	template<int RoundingFlag_, EmuConcepts::EmuFastMatrix FastMatrix_>
	[[nodiscard]] constexpr inline auto fast_matrix_round(FastMatrix_&& fast_matrix_)
		-> typename std::remove_cvref<FastMatrix_>::type
	{
		return _fast_matrix_underlying::_fast_matrix_round<RoundingFlag_, false>(std::forward<FastMatrix_>(fast_matrix_));
	}
#pragma endregion

#pragma region ROUND_ASSIGNS
	template<EmuConcepts::EmuFastMatrix FastMatrix_>
	[[nodiscard]] constexpr inline void fast_matrix_floor_assign(FastMatrix_&& fast_matrix_)
	{
		_fast_matrix_underlying::_fast_matrix_floor<true>(std::forward<FastMatrix_>(fast_matrix_));
	}

	template<EmuConcepts::EmuFastMatrix FastMatrix_>
	[[nodiscard]] constexpr inline void fast_matrix_ceil_assign(FastMatrix_&& fast_matrix_)
	{
		_fast_matrix_underlying::_fast_matrix_ceil<true>(std::forward<FastMatrix_>(fast_matrix_));
	}

	template<EmuConcepts::EmuFastMatrix FastMatrix_>
	[[nodiscard]] constexpr inline void fast_matrix_trunc_assign(FastMatrix_&& fast_matrix_)
	{
		_fast_matrix_underlying::_fast_matrix_trunc<true>(std::forward<FastMatrix_>(fast_matrix_));
	}

	template<int RoundingFlag_, EmuConcepts::EmuFastMatrix FastMatrix_>
	[[nodiscard]] constexpr inline void fast_matrix_round_assign(FastMatrix_&& fast_matrix_)
	{
		_fast_matrix_underlying::_fast_matrix_round<RoundingFlag_, true>(std::forward<FastMatrix_>(fast_matrix_));
	}
#pragma endregion
}

#endif
