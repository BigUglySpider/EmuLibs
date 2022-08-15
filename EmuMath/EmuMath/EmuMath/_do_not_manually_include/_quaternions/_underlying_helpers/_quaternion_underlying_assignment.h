#ifndef EMU_MATH_QUATERNION_UNDERLYING_ASSIGNMENT_H_INC_
#define EMU_MATH_QUATERNION_UNDERLYING_ASSIGNMENT_H_INC_ 1

#include "_quaternion_tmp.h"
#include "_quaternion_underlying_get.h"

namespace EmuMath::Helpers::_quaternion_underlying
{
#pragma region VALIDITY_CHECKS
	template<typename LhsT_, typename RhsT_>
	[[nodiscard]] constexpr inline bool _can_const_convert_assign()
	{
		using lhs_quat = EmuMath::Quaternion<LhsT_>&;
		using rhs_quat = const EmuMath::Quaternion<RhsT_>&;
		using lhs_value_uq = typename EmuMath::Quaternion<LhsT_>::value_type_uq;
		return EmuCore::TMP::valid_assign_direct_or_cast
		<
			lhs_value_uq,
			decltype(_get_x(std::declval<rhs_quat>())),
			decltype(_get_x(std::declval<lhs_quat>()))
		>();
	}

	template<typename LhsT_, typename RhsT_>
	[[nodiscard]] constexpr inline bool _can_non_const_convert_assign()
	{
		using lhs_quat = EmuMath::Quaternion<LhsT_>&;
		using rhs_quat = EmuMath::Quaternion<RhsT_>&;
		using lhs_value_uq = typename EmuMath::Quaternion<LhsT_>::value_type_uq;
		return EmuCore::TMP::valid_assign_direct_or_cast
		<
			lhs_value_uq,
			decltype(_get_x(std::declval<rhs_quat>())),
			decltype(_get_x(std::declval<lhs_quat>()))
		>();
	}

	template<typename LhsT_, typename RhsT_>
	[[nodiscard]] constexpr inline bool _can_move_convert_assign()
	{
		using lhs_quat = EmuMath::Quaternion<LhsT_>&;
		using rhs_quat = EmuMath::Quaternion<RhsT_>&&;
		using lhs_value_uq = typename EmuMath::Quaternion<LhsT_>::value_type_uq;
		return EmuCore::TMP::valid_assign_direct_or_cast
		<
			lhs_value_uq,
			decltype(std::move(_get_x(std::declval<rhs_quat>()))),
			decltype(_get_x(std::declval<lhs_quat>()))
		>();
	}
#pragma endregion

#pragma region CONVERSION_FUNCS
	template<typename LhsT_, typename RhsT_>
	[[nodiscard]] constexpr inline void _convert_assign(EmuMath::Quaternion<LhsT_>& lhs_, const EmuMath::Quaternion<RhsT_>& rhs_)
	{
		if constexpr (_can_const_convert_assign<LhsT_, RhsT_>())
		{
			using lhs_value_uq = typename EmuMath::Quaternion<LhsT_>::value_type_uq;
			EmuCore::TMP::assign_direct_or_cast<lhs_value_uq>(_get_x(lhs_), _get_x(rhs_));
			EmuCore::TMP::assign_direct_or_cast<lhs_value_uq>(_get_y(lhs_), _get_y(rhs_));
			EmuCore::TMP::assign_direct_or_cast<lhs_value_uq>(_get_z(lhs_), _get_z(rhs_));
			EmuCore::TMP::assign_direct_or_cast<lhs_value_uq>(_get_w(lhs_), _get_w(rhs_));
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<LhsT_, RhsT_>(), "Unable to const convert-assign to an EmuMath Quaternion as it cannot have its components assigned via respective components of a const-qualified Quaternion of a potentially different type.");
		}
	}

	template<typename LhsT_, typename RhsT_>
	[[nodiscard]] constexpr inline void _convert_assign(EmuMath::Quaternion<LhsT_>& lhs_, EmuMath::Quaternion<RhsT_>& rhs_)
	{
		if constexpr (_can_non_const_convert_assign<LhsT_, RhsT_>())
		{
			using lhs_value_uq = typename EmuMath::Quaternion<LhsT_>::value_type_uq;
			EmuCore::TMP::assign_direct_or_cast<lhs_value_uq>(_get_x(lhs_), _get_x(rhs_));
			EmuCore::TMP::assign_direct_or_cast<lhs_value_uq>(_get_y(lhs_), _get_y(rhs_));
			EmuCore::TMP::assign_direct_or_cast<lhs_value_uq>(_get_z(lhs_), _get_z(rhs_));
			EmuCore::TMP::assign_direct_or_cast<lhs_value_uq>(_get_w(lhs_), _get_w(rhs_));
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<LhsT_, RhsT_>(), "Unable to non-const convert-assign to an EmuMath Quaternion as it cannot have its components assigned via respective components of a const-qualified Quaternion of a potentially different type.");
		}
	}

	template<typename LhsT_, typename RhsT_>
	[[nodiscard]] constexpr inline void _convert_assign(EmuMath::Quaternion<LhsT_>& lhs_, EmuMath::Quaternion<RhsT_>&& rhs_)
	{
		if constexpr (_can_move_convert_assign<LhsT_, RhsT_>())
		{
			// Warning disabled as we are only ever moving separate indices in a well-formed specialisation
#pragma warning(push)
#pragma warning(disable: 26800)
			using lhs_value_uq = typename EmuMath::Quaternion<LhsT_>::value_type_uq;
			EmuCore::TMP::assign_direct_or_cast<lhs_value_uq>(_get_x(lhs_), std::move(_get_x(std::forward<EmuMath::Quaternion<RhsT_>>(rhs_))));
			EmuCore::TMP::assign_direct_or_cast<lhs_value_uq>(_get_y(lhs_), std::move(_get_y(std::forward<EmuMath::Quaternion<RhsT_>>(rhs_))));
			EmuCore::TMP::assign_direct_or_cast<lhs_value_uq>(_get_z(lhs_), std::move(_get_z(std::forward<EmuMath::Quaternion<RhsT_>>(rhs_))));
			EmuCore::TMP::assign_direct_or_cast<lhs_value_uq>(_get_w(lhs_), std::move(_get_w(std::forward<EmuMath::Quaternion<RhsT_>>(rhs_))));
#pragma warning(pop)
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<LhsT_, RhsT_>(), "Unable to move convert-assign to an EmuMath Quaternion as it cannot have its components assigned via respective components of a const-qualified Quaternion of a potentially different type.");
		}
	}
#pragma endregion
}

#endif
