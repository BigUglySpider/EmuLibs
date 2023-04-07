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

#pragma region LERPS
	template<EmuConcepts::EmuFastQuaternion FastQuaternionA_, EmuConcepts::EmuFastQuaternionLerpArg<FastQuaternionA_> B_, EmuConcepts::EmuFastQuaternionLerpArg<FastQuaternionA_> T_>
	[[nodiscard]] constexpr inline auto fast_quaternion_lerp(FastQuaternionA_&& a_, B_&& b_, T_&& t_)
		-> typename std::remove_cvref<FastQuaternionA_>::type
	{
		return _fast_quaternion_underlying::_fast_quaternion_lerp<false>
		(
			std::forward<FastQuaternionA_>(a_),
			std::forward<B_>(b_),
			std::forward<T_>(t_)
		);
	}
	
	template<EmuConcepts::EmuFastQuaternion FastQuaternionA_, EmuConcepts::EmuFastQuaternionLerpArg<FastQuaternionA_> B_, EmuConcepts::EmuFastQuaternionLerpArg<FastQuaternionA_> T_>
	[[nodiscard]] constexpr inline auto fast_quaternion_fused_lerp(FastQuaternionA_&& a_, B_&& b_, T_&& t_)
		-> typename std::remove_cvref<FastQuaternionA_>::type
	{
		return _fast_quaternion_underlying::_fast_quaternion_lerp<true>
		(
			std::forward<FastQuaternionA_>(a_),
			std::forward<B_>(b_),
			std::forward<T_>(t_)
		);
	}
#pragma endregion

#pragma region SLERPS
	template<EmuConcepts::EmuFastQuaternion FastQuaternionA_, EmuConcepts::EmuFastQuaternion FastQuaternionB_, EmuConcepts::EmuFastQuaternionLerpArg<FastQuaternionA_> T_>
	requires(std::is_same_v<typename std::remove_cvref<FastQuaternionA_>::type, typename std::remove_cvref<FastQuaternionB_>::type>)
	[[nodiscard]] constexpr inline auto fast_quaternion_slerp(FastQuaternionA_&& a_, FastQuaternionB_&& b_, T_&& t_)
		-> typename std::remove_cvref<FastQuaternionA_>::type
	{
		return _fast_quaternion_underlying::_fast_quaternion_slerp<false>
		(
			std::forward<FastQuaternionA_>(a_),
			std::forward<FastQuaternionB_>(b_),
			std::forward<T_>(t_)
		);
	}
	
	template<EmuConcepts::EmuFastQuaternion FastQuaternionA_, EmuConcepts::EmuFastQuaternion FastQuaternionB_, EmuConcepts::EmuFastQuaternionLerpArg<FastQuaternionA_> T_>
	requires(std::is_same_v<typename std::remove_cvref<FastQuaternionA_>::type, typename std::remove_cvref<FastQuaternionB_>::type>)
	[[nodiscard]] constexpr inline auto fast_quaternion_fused_slerp(FastQuaternionA_&& a_, FastQuaternionB_&& b_, T_&& t_)
		-> typename std::remove_cvref<FastQuaternionA_>::type
	{
		return _fast_quaternion_underlying::_fast_quaternion_slerp<true>
		(
			std::forward<FastQuaternionA_>(a_),
			std::forward<FastQuaternionB_>(b_),
			std::forward<T_>(t_)
		);
	}
#pragma endregion
}

#endif
