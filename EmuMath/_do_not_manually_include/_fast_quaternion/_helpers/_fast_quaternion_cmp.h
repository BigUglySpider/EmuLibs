#ifndef EMU_MATH_FAST_QUATERNION_CMP_H_INC_
#define EMU_MATH_FAST_QUATERNION_CMP_H_INC_ 1

#include "_common_fast_quaternion_includes.h"

namespace EmuMath::Helpers
{
	template<typename T_, std::size_t RegisterWidth_>
	[[nodiscard]] constexpr inline auto fast_quaternion_cmp_equal
	(
		const EmuMath::FastQuaternion<T_, RegisterWidth_>& lhs_,
		const EmuMath::FastQuaternion<T_, RegisterWidth_>& rhs_
	) -> bool
	{
		constexpr std::size_t per_element_width = EmuMath::FastQuaternion<T_, RegisterWidth_>::per_element_width;
		constexpr bool is_signed = EmuMath::FastQuaternion<T_, RegisterWidth_>::is_signed;

		if constexpr (EmuMath::FastQuaternion<T_, RegisterWidth_>::num_registers > 1)
		{
			return
			(
				EmuSIMD::cmp_all_eq<per_element_width, is_signed>(lhs_.data[0], rhs_.data[0]) &&
				EmuSIMD::cmp_all_eq<per_element_width, is_signed>(lhs_.data[1], rhs_.data[1])
			);
		}
		else
		{
			// Extra effort required on compilation side if we need to ignore register indices for an accurate comparison result
			constexpr std::size_t elements_per_register = EmuMath::FastQuaternion<T_, RegisterWidth_>::elements_per_register;
			if constexpr (elements_per_register > 4)
			{
				return EmuSIMD::cmp_firstx_all_eq<4, per_element_width, is_signed>(lhs_.data, rhs_.data);
			}
			else
			{
				return EmuSIMD::cmp_all_eq<per_element_width, is_signed>(lhs_.data, rhs_.data);
			}
		}
	}

	template<typename T_, std::size_t RegisterWidth_>
	[[nodiscard]] constexpr inline auto fast_quaternion_cmp_not_equal
	(
		const EmuMath::FastQuaternion<T_, RegisterWidth_>& lhs_,
		const EmuMath::FastQuaternion<T_, RegisterWidth_>& rhs_
	) -> bool
	{
		constexpr std::size_t per_element_width = EmuMath::FastQuaternion<T_, RegisterWidth_>::per_element_width;
		constexpr bool is_signed = EmuMath::FastQuaternion<T_, RegisterWidth_>::is_signed;

		if constexpr (EmuMath::FastQuaternion<T_, RegisterWidth_>::num_registers > 1)
		{
			return
			(
				EmuSIMD::cmp_any_neq<per_element_width, is_signed>(lhs_.data[0], rhs_.data[0]) ||
				EmuSIMD::cmp_any_neq<per_element_width, is_signed>(lhs_.data[1], rhs_.data[1])
			);
		}
		else
		{
			// Extra effort required on compilation side if we need to ignore register indices for an accurate comparison result
			constexpr std::size_t elements_per_register = EmuMath::FastQuaternion<T_, RegisterWidth_>::elements_per_register;
			if constexpr (elements_per_register > 4)
			{
				return EmuSIMD::cmp_firstx_any_neq<4, per_element_width, is_signed>(lhs_.data, rhs_.data);
			}
			else
			{
				return EmuSIMD::cmp_any_neq<per_element_width, is_signed>(lhs_.data, rhs_.data);
			}
		}
	}

	template<typename T_, std::size_t RegisterWidth_>
	[[nodiscard]] constexpr inline auto fast_quaternion_cmp_near
	(
		const EmuMath::FastQuaternion<T_, RegisterWidth_>& lhs_,
		const EmuMath::FastQuaternion<T_, RegisterWidth_>& rhs_
	) -> bool
	{
		constexpr std::size_t per_element_width = EmuMath::FastQuaternion<T_, RegisterWidth_>::per_element_width;
		constexpr bool is_signed = EmuMath::FastQuaternion<T_, RegisterWidth_>::is_signed;

		if constexpr (EmuMath::FastQuaternion<T_, RegisterWidth_>::num_registers > 1)
		{
			return
			(
				EmuSIMD::cmp_all_near<per_element_width, is_signed>(lhs_.data[0], rhs_.data[0]) &&
				EmuSIMD::cmp_all_near<per_element_width, is_signed>(lhs_.data[1], rhs_.data[1])
			);
		}
		else
		{
			// Extra effort required on compilation side if we need to ignore register indices for an accurate comparison result
			constexpr std::size_t elements_per_register = EmuMath::FastQuaternion<T_, RegisterWidth_>::elements_per_register;
			if constexpr (elements_per_register > 4)
			{
				return EmuSIMD::cmp_firstx_all_near<4, per_element_width, is_signed>(lhs_.data, rhs_.data);
			}
			else
			{
				return EmuSIMD::cmp_all_near<per_element_width, is_signed>(lhs_.data, rhs_.data);
			}
		}
	}

	template<typename T_, std::size_t RegisterWidth_>
	[[nodiscard]] constexpr inline auto fast_quaternion_cmp_near
	(
		const EmuMath::FastQuaternion<T_, RegisterWidth_>& lhs_,
		const EmuMath::FastQuaternion<T_, RegisterWidth_>& rhs_,
		const EmuMath::FastQuaternion<T_, RegisterWidth_>& epsilon_
	) -> bool
	{
		constexpr std::size_t per_element_width = EmuMath::FastQuaternion<T_, RegisterWidth_>::per_element_width;
		constexpr bool is_signed = EmuMath::FastQuaternion<T_, RegisterWidth_>::is_signed;

		if constexpr (EmuMath::FastQuaternion<T_, RegisterWidth_>::num_registers > 1)
		{
			return
			(
				EmuSIMD::cmp_all_near<per_element_width, is_signed>(lhs_.data[0], rhs_.data[0], epsilon_.data[0]) &&
				EmuSIMD::cmp_all_near<per_element_width, is_signed>(lhs_.data[1], rhs_.data[1], epsilon_.data[1])
			);
		}
		else
		{
			// Extra effort required on compilation side if we need to ignore register indices for an accurate comparison result
			constexpr std::size_t elements_per_register = EmuMath::FastQuaternion<T_, RegisterWidth_>::elements_per_register;
			if constexpr (elements_per_register > 4)
			{
				return EmuSIMD::cmp_firstx_all_near<4, per_element_width, is_signed>(lhs_.data, rhs_.data, epsilon_.data);
			}
			else
			{
				return EmuSIMD::cmp_all_near<per_element_width, is_signed>(lhs_.data, rhs_.data, epsilon_.data);
			}
		}
	}

	template<typename T_, std::size_t RegisterWidth_>
	[[nodiscard]] constexpr inline auto fast_quaternion_cmp_near
	(
		const EmuMath::FastQuaternion<T_, RegisterWidth_>& lhs_,
		const EmuMath::FastQuaternion<T_, RegisterWidth_>& rhs_,
		typename EmuMath::FastQuaternion<T_, RegisterWidth_>::register_arg_type epsilon_
	) -> bool
	{
		constexpr std::size_t per_element_width = EmuMath::FastQuaternion<T_, RegisterWidth_>::per_element_width;
		constexpr bool is_signed = EmuMath::FastQuaternion<T_, RegisterWidth_>::is_signed;

		if constexpr (EmuMath::FastQuaternion<T_, RegisterWidth_>::num_registers > 1)
		{
			return
			(
				EmuSIMD::cmp_all_near<per_element_width, is_signed>(lhs_.data[0], rhs_.data[0], epsilon_) &&
				EmuSIMD::cmp_all_near<per_element_width, is_signed>(lhs_.data[1], rhs_.data[1], epsilon_)
			);
		}
		else
		{
			// Extra effort required on compilation side if we need to ignore register indices for an accurate comparison result
			constexpr std::size_t elements_per_register = EmuMath::FastQuaternion<T_, RegisterWidth_>::elements_per_register;
			if constexpr (elements_per_register > 4)
			{
				return EmuSIMD::cmp_firstx_all_near<4, per_element_width, is_signed>(lhs_.data, rhs_.data, epsilon_);
			}
			else
			{
				return EmuSIMD::cmp_all_near<per_element_width, is_signed>(lhs_.data, rhs_.data, epsilon_);
			}
		}
	}
}

#endif
