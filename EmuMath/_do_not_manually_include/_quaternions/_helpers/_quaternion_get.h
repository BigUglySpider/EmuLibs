#ifndef EMU_MATH_QUATERNION_GET_H_INC_
#define EMU_MATH_QUATERNION_GET_H_INC_ 1

#include "_common_quaternion_helper_includes.h"

namespace EmuMath::Helpers
{
#pragma region GET_INDEX
	template<std::size_t Index_, typename T_>
	[[nodiscard]] constexpr inline decltype(auto) quaternion_get(EmuMath::Quaternion<T_>& quaternion_)
	{
		return _quaternion_underlying::_get_index<Index_>(quaternion_);
	}

	template<std::size_t Index_, typename T_>
	[[nodiscard]] constexpr inline decltype(auto) quaternion_get(const EmuMath::Quaternion<T_>& quaternion_)
	{
		return _quaternion_underlying::_get_index<Index_>(quaternion_);
	}

	template<std::size_t Index_, typename T_>
	[[nodiscard]] constexpr inline decltype(auto) quaternion_get(EmuMath::Quaternion<T_>&& quaternion_)
	{
		return _quaternion_underlying::_get_index<Index_>(std::forward<EmuMath::Quaternion<T_>>(quaternion_));
	}
#pragma endregion

#pragma region GET_X
	template<std::size_t Index_, typename T_>
	[[nodiscard]] constexpr inline decltype(auto) quaternion_get_x(EmuMath::Quaternion<T_>& quaternion_)
	{
		return _quaternion_underlying::_get_x(quaternion_);
	}

	template<std::size_t Index_, typename T_>
	[[nodiscard]] constexpr inline decltype(auto) quaternion_get_x(const EmuMath::Quaternion<T_>& quaternion_)
	{
		return _quaternion_underlying::_get_x(quaternion_);
	}

	template<std::size_t Index_, typename T_>
	[[nodiscard]] constexpr inline decltype(auto) quaternion_get_x(EmuMath::Quaternion<T_>&& quaternion_)
	{
		return _quaternion_underlying::_get_x(std::forward<EmuMath::Quaternion<T_>>(quaternion_));
	}
#pragma endregion

#pragma region GET_Y
	template<std::size_t Index_, typename T_>
	[[nodiscard]] constexpr inline decltype(auto) quaternion_get_y(EmuMath::Quaternion<T_>& quaternion_)
	{
		return _quaternion_underlying::_get_y(quaternion_);
	}

	template<std::size_t Index_, typename T_>
	[[nodiscard]] constexpr inline decltype(auto) quaternion_get_y(const EmuMath::Quaternion<T_>& quaternion_)
	{
		return _quaternion_underlying::_get_y(quaternion_);
	}

	template<std::size_t Index_, typename T_>
	[[nodiscard]] constexpr inline decltype(auto) quaternion_get_y(EmuMath::Quaternion<T_>&& quaternion_)
	{
		return _quaternion_underlying::_get_y(std::forward<EmuMath::Quaternion<T_>>(quaternion_));
	}
#pragma endregion

#pragma region GET_Z
	template<std::size_t Index_, typename T_>
	[[nodiscard]] constexpr inline decltype(auto) quaternion_get_z(EmuMath::Quaternion<T_>& quaternion_)
	{
		return _quaternion_underlying::_get_z(quaternion_);
	}

	template<std::size_t Index_, typename T_>
	[[nodiscard]] constexpr inline decltype(auto) quaternion_get_z(const EmuMath::Quaternion<T_>& quaternion_)
	{
		return _quaternion_underlying::_get_z(quaternion_);
	}

	template<std::size_t Index_, typename T_>
	[[nodiscard]] constexpr inline decltype(auto) quaternion_get_z(EmuMath::Quaternion<T_>&& quaternion_)
	{
		return _quaternion_underlying::_get_z(std::forward<EmuMath::Quaternion<T_>>(quaternion_));
	}
#pragma endregion

#pragma region GET_W
	template<std::size_t Index_, typename T_>
	[[nodiscard]] constexpr inline decltype(auto) quaternion_get_w(EmuMath::Quaternion<T_>& quaternion_)
	{
		return _quaternion_underlying::_get_w(quaternion_);
	}

	template<std::size_t Index_, typename T_>
	[[nodiscard]] constexpr inline decltype(auto) quaternion_get_w(const EmuMath::Quaternion<T_>& quaternion_)
	{
		return _quaternion_underlying::_get_w(quaternion_);
	}

	template<std::size_t Index_, typename T_>
	[[nodiscard]] constexpr inline decltype(auto) quaternion_get_w(EmuMath::Quaternion<T_>&& quaternion_)
	{
		return _quaternion_underlying::_get_w(std::forward<EmuMath::Quaternion<T_>>(quaternion_));
	}
#pragma endregion
}

#endif
