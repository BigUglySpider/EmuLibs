#ifndef EMU_MATH_QUATERNION_ASSIGNMENT_H_INC_
#define EMU_MATH_QUATERNION_ASSIGNMENT_H_INC_ 1

#include "_common_quaternion_helper_includes.h"

namespace EmuMath::Helpers
{
#pragma region VALIDITY_CHECKS
	/// <summary>
	/// <para> Check to see if a Quaternion with typearg RhsT_ can be converted and assigned to a Quaternion with typearg LhsT_. </para>
	/// <para> This check is performed under the context of a const-qualified right-hand lvalue reference. </para>
	/// </summary>
	/// <returns>
	///		True if a const-qualified lvalue reference to a Quaternion with RhsT_ as its typearg can be converted to assign to a 
	///		non-const-qualified lvalue reference to a Quaternion with LhsT_ as its typearg.
	/// </returns>
	template<typename LhsT_, typename RhsT_>
	[[nodiscard]] constexpr inline bool quaternion_can_const_convert_assign()
	{
		return _quaternion_underlying::_can_const_convert_assign<LhsT_, RhsT_>();
	}

	/// <summary>
	/// <para> Check to see if a Quaternion with typearg RhsT_ can be converted and assigned to a Quaternion with typearg LhsT_. </para>
	/// <para> This check is performed under the context of a non-const-qualified right-hand lvalue reference. </para>
	/// </summary>
	/// <returns>
	///		True if a non-const-qualified lvalue reference to a Quaternion with RhsT_ as its typearg can be converted to assign to a 
	///		non-const-qualified lvalue reference to a Quaternion with LhsT_ as its typearg.
	/// </returns>
	template<typename LhsT_, typename RhsT_>
	[[nodiscard]] constexpr inline bool quaternion_can_non_const_convert_assign()
	{
		return _quaternion_underlying::_can_non_const_convert_assign<LhsT_, RhsT_>();
	}

	/// <summary>
	/// <para> Check to see if a Quaternion with typearg RhsT_ can be converted and assigned to a Quaternion with typearg LhsT_. </para>
	/// <para> This check is performed under the context of a right-hand rvalue reference. </para>
	/// </summary>
	/// <returns>
	///		True if a rvalue reference to a Quaternion with RhsT_ as its typearg can be converted to assign to a 
	///		non-const-qualified lvalue reference to a Quaternion with LhsT_ as its typearg.
	/// </returns>
	template<typename LhsT_, typename RhsT_>
	[[nodiscard]] constexpr inline bool quaternion_can_move_convert_assign()
	{
		return _quaternion_underlying::_can_move_convert_assign<LhsT_, RhsT_>();
	}
#pragma endregion

#pragma region ASSIGNMENT_FUNCS
	template<typename LhsT_, typename RhsT_>
	[[nodiscard]] constexpr inline auto quaternion_convert_assign(EmuMath::Quaternion<LhsT_>& lhs_, const EmuMath::Quaternion<RhsT_>& rhs_)
		-> std::enable_if_t<quaternion_can_const_convert_assign<LhsT_, RhsT_>(), void>
	{
		_quaternion_underlying::_convert_assign(lhs_, rhs_);
	}

	template<typename LhsT_, typename RhsT_>
	[[nodiscard]] constexpr inline auto quaternion_convert_assign(EmuMath::Quaternion<LhsT_>& lhs_, EmuMath::Quaternion<RhsT_>& rhs_)
		-> std::enable_if_t<quaternion_can_non_const_convert_assign<LhsT_, RhsT_>(), void>
	{
		_quaternion_underlying::_convert_assign(lhs_, rhs_);
	}

	template<typename LhsT_, typename RhsT_>
	[[nodiscard]] constexpr inline auto quaternion_convert_assign(EmuMath::Quaternion<LhsT_>& lhs_, EmuMath::Quaternion<RhsT_>&& rhs_)
		-> std::enable_if_t<quaternion_can_move_convert_assign<LhsT_, RhsT_>(), void>
	{
		_quaternion_underlying::_convert_assign(lhs_, std::forward<EmuMath::Quaternion<RhsT_>>(rhs_));
	}
#pragma endregion
}

#endif
