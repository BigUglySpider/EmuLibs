#ifndef EMU_MATH_FAST_MATRIX_UNDERLYING_ROUNDS_H_INC_
#define EMU_MATH_FAST_MATRIX_UNDERLYING_ROUNDS_H_INC_ 1

#include "_fast_matrix_tmp.h"
#include "_fast_matrix_underlying_mutation.h"

namespace EmuMath::Helpers::_fast_matrix_underlying
{
	template<bool Assigning_, EmuConcepts::EmuFastMatrix FastMatrix_>
	[[nodiscard]] constexpr inline decltype(auto) _fast_matrix_floor(FastMatrix_&& matrix_)
	{
		return _fast_matrix_mutate<Assigning_, false>
		(
			std::forward<FastMatrix_>(matrix_),
			[](auto&& register_) { return EmuSIMD::floor(register_); }
		);
	}
	
	template<bool Assigning_, EmuConcepts::EmuFastMatrix FastMatrix_>
	[[nodiscard]] constexpr inline decltype(auto) _fast_matrix_ceil(FastMatrix_&& matrix_)
	{
		return _fast_matrix_mutate<Assigning_, false>
		(
			std::forward<FastMatrix_>(matrix_),
			[](auto&& register_) { return EmuSIMD::ceil(register_); }
		);
	}
	
	template<bool Assigning_, EmuConcepts::EmuFastMatrix FastMatrix_>
	[[nodiscard]] constexpr inline decltype(auto) _fast_matrix_trunc(FastMatrix_&& matrix_)
	{
		return _fast_matrix_mutate<Assigning_, false>
		(
			std::forward<FastMatrix_>(matrix_),
			[](auto&& register_) { return EmuSIMD::trunc(register_); }
		);
	}
	
	template<int RoundingFlag_, bool Assigning_, EmuConcepts::EmuFastMatrix FastMatrix_>
	[[nodiscard]] constexpr inline decltype(auto) _fast_matrix_round(FastMatrix_&& matrix_)
	{
		return _fast_matrix_mutate<Assigning_, false>
		(
			std::forward<FastMatrix_>(matrix_),
			[](auto&& register_) { return EmuSIMD::round<RoundingFlag_>(register_); }
		);
	}
}

#endif
