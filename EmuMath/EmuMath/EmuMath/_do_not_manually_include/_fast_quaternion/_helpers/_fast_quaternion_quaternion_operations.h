#ifndef EMU_MATH_FAST_QUATERNION_QUATERNION_OPERATIONS_H_INC_
#define EMU_MATH_FAST_QUATERNION_QUATERNION_OPERATIONS_H_INC_ 1

#include "_common_fast_quaternion_includes.h"

namespace EmuMath::Helpers
{
#pragma region SCALAR_NORM_FUNCS
	template<EmuConcepts::Arithmetic OutT_, EmuConcepts::EmuFastQuaternion FastQuaternion_>
	[[nodiscard]] constexpr inline auto fast_quaternion_square_norm_scalar(FastQuaternion_&& fast_quaternion_)
		-> OutT_
	{
		return _fast_quaternion_underlying::_fast_quaternion_calculate_norm<true, true, OutT_>
		(
			std::forward<FastQuaternion_>(fast_quaternion_)
		);
	}
	
	template<EmuConcepts::EmuFastQuaternion FastQuaternion_>
	[[nodiscard]] constexpr inline auto fast_quaternion_square_norm_scalar(FastQuaternion_&& fast_quaternion_)
		-> typename std::remove_cvref_t<FastQuaternion_>::preferred_floating_point
	{
		using preferred_floating_point = typename std::remove_cvref_t<FastQuaternion_>::preferred_floating_point;
		return _fast_quaternion_underlying::_fast_quaternion_calculate_norm<true, true, preferred_floating_point>
		(
			std::forward<FastQuaternion_>(fast_quaternion_)
		);
	}

	template<EmuConcepts::Arithmetic OutT_, EmuConcepts::EmuFastQuaternion FastQuaternion_>
	[[nodiscard]] constexpr inline auto fast_quaternion_norm_scalar(FastQuaternion_&& fast_quaternion_)
		-> OutT_
	{
		return _fast_quaternion_underlying::_fast_quaternion_calculate_norm<true, false, OutT_>
		(
			std::forward<FastQuaternion_>(fast_quaternion_)
		);
	}
	
	template<EmuConcepts::EmuFastQuaternion FastQuaternion_>
	[[nodiscard]] constexpr inline auto fast_quaternion_norm_scalar(FastQuaternion_&& fast_quaternion_)
		-> typename std::remove_cvref_t<FastQuaternion_>::preferred_floating_point
	{
		using preferred_floating_point = typename std::remove_cvref_t<FastQuaternion_>::preferred_floating_point;
		return _fast_quaternion_underlying::_fast_quaternion_calculate_norm<true, false, preferred_floating_point>
		(
			std::forward<FastQuaternion_>(fast_quaternion_)
		);
	}
#pragma endregion

#pragma region REGISTER_NORM_FUNCS
	template<EmuConcepts::EmuFastQuaternion FastQuaternion_>
	[[nodiscard]] constexpr inline auto fast_quaternion_square_norm(FastQuaternion_&& fast_quaternion_)
		-> typename std::remove_cvref_t<FastQuaternion_>::register_type
	{
		return _fast_quaternion_underlying::_fast_quaternion_calculate_norm<false, true>
		(
			std::forward<FastQuaternion_>(fast_quaternion_)
		);
	}
	
	template<EmuConcepts::EmuFastQuaternion FastQuaternion_>
	[[nodiscard]] constexpr inline auto fast_quaternion_norm(FastQuaternion_&& fast_quaternion_)
		-> typename std::remove_cvref_t<FastQuaternion_>::register_type
	{
		return _fast_quaternion_underlying::_fast_quaternion_calculate_norm<false, false>
		(
			std::forward<FastQuaternion_>(fast_quaternion_)
		);
	}
#pragma endregion
}

#endif
