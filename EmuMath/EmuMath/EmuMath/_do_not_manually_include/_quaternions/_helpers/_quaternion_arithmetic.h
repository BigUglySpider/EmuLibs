#ifndef EMU_MATH_QUATERNION_ARITHMETIC_H_INC_
#define EMU_MATH_QUATERNION_ARITHMETIC_H_INC_ 1

#include "_common_quaternion_helper_includes.h"

namespace EmuMath::Helpers
{
#pragma region VALIDITY_CHECKS
	/// <summary>
	/// <para> Check to see if a `Quaternion * Scalar` multiplication can be performed with the provided circumstances. </para>
	/// <para> If StaticAssert_ is true, this will trigger a static assertion in cases where it returns false. </para>
	/// </summary>
	/// <returns>
	///		True if multiplication can be successfully performed with a Quaternion with the passed typearg,
	///		using a scalar of Rhs_ type, with the desired OutT_ for the output Quaternion.
	/// </returns>
	template<typename QuaternionT_, class Rhs_, typename OutT_, bool StaticAssert_ = false>
	[[nodiscard]] constexpr inline bool quaternion_can_scalar_multiply()
	{
		return _quaternion_underlying::_can_scalar_multiply<QuaternionT_, OutT_, typename EmuCore::TMP::forward_result<Rhs_>::type, false, StaticAssert_>();
	}

	/// <summary>
	/// <para> Check to see if a `Quaternion * Quaternion` multiplication can be performed with the provided circumstances. </para>
	/// <para> If StaticAssert_ is true, this will trigger a static assertion in cases where it returns false. </para>
	/// </summary>
	/// <returns>
	///		True if multiplication can be successfully performed with a Quaternion with the passed respective typearg,
	///		using a right-hand Quaternion with the passed respective typearg, with the desired OutT_ for the output Quaternion.
	/// </returns>
	template<typename LhsT_, typename RhsT_, typename OutT_, bool StaticAssert_ = false>
	[[nodiscard]] constexpr inline bool quaternion_can_quaternion_multiply()
	{
		return _quaternion_underlying::_can_quaternion_multiply<OutT_, const EmuMath::Quaternion<LhsT_>&, const EmuMath::Quaternion<RhsT_>&, false, StaticAssert_>();
	}

	/// <summary>
	/// <para> Check to see if a generic, adaptive Quaternion multiplication can be performed with the provided circumstances. </para>
	/// <para> If Rhs_ is an EmuMath Quaternion, this will check for a successful `Quaternion * Quaternion` multiplication. </para>
	/// <para> If Rhs_ is NOT an EmuMath Quaternion, this will check for a successful `Quaternion * Scalar` multiplication. </para>
	/// <para> If StaticAssert_ is true, this will trigger a static assertion in cases where it returns false. </para>
	/// </summary>
	/// <returns>
	///		True if multiplication can be successfully performed with a Quaternion with the passed typearg,
	///		using the passed right-hand argument, with the desired OutT_ for the output Quaternion.
	/// </returns>
	template<typename LhsT_, typename Rhs_, typename OutT_, bool StaticAssert_>
	[[nodiscard]] constexpr inline bool quaternion_can_multiply()
	{
		using rhs_uq = typename EmuCore::TMP::remove_ref_cv<Rhs_>::type;
		if constexpr (EmuMath::TMP::is_emu_quaternion_v<rhs_uq>)
		{
			return quaternion_can_quaternion_multiply<const EmuMath::Quaternion<LhsT_>&, typename EmuCore::TMP::forward_result<Rhs_>::type, OutT_, StaticAssert_>();
		}
		else
		{
			return quaternion_can_scalar_multiply<LhsT_, typename EmuCore::TMP::forward_result<Rhs_>::type, OutT_, StaticAssert_>();
		}
	}
#pragma endregion

#pragma region MULTIPLICATION_FUNCS
	/// <summary>
	/// <para> Adaptive Quaternion multiplication function which will change behaviour based on the passed right-hand argument. </para>
	/// <para> If Rhs_ is an EmuMath Quaternion, this will perform a `Quaternion * Quaternion` multiplication. </para>
	/// <para> If Rhs_ is NOT an EmuMath Quaternion, this will perform a `Quaternion * Scalar` multiplication. </para>
	/// <para> Be aware that `Quaternion * Quaternion` multiplication is non-commutative. </para>
	/// </summary>
	/// <param name="lhs_">EmuMath Quaternion on the left-hand side of multiplication.</param>
	/// <param name="rhs_">Scalar or EmuMath Quaternion on the right-hand side of multiplication.</param>
	/// <returns>EmuMath Quaternion containing the results of the selected multiplication operation.</returns>
	template<typename OutT_, typename LhsT_, class Rhs_>
	[[nodiscard]] constexpr inline auto quaternion_multiply(const EmuMath::Quaternion<LhsT_>& lhs_, Rhs_&& rhs_)
		-> std::enable_if_t<quaternion_can_multiply<LhsT_, Rhs_, OutT_, false>(), EmuMath::Quaternion<OutT_>>
	{
		using rhs_uq = typename EmuCore::TMP::remove_ref_cv<Rhs_>::type;
		if constexpr (EmuMath::TMP::is_emu_quaternion_v<rhs_uq>)
		{
			return _quaternion_underlying::_multiply_quaternion_by_quaternion<false, OutT_>(lhs_, std::forward<Rhs_>(rhs_));
		}
		else
		{
			return _quaternion_underlying::_multiply_quaternion_by_scalar<false, OutT_>(lhs_, std::forward<Rhs_>(rhs_));
		}
	}

	/// <summary>
	/// <para> Multiplies the `lhs_` Quaternion by the `rhs_` scalar. </para>
	/// </summary>
	/// <param name="lhs_">EmuMath Quaternion on the left-hand side of multiplication.</param>
	/// <param name="rhs_">Scalar on the right-hand side of multiplication.</param>
	/// <returns>EmuMath Quaternion containing the results of the selected multiplication operation.</returns>
	template<typename OutT_, typename LhsT_, typename Rhs_>
	[[nodiscard]] constexpr inline auto quaternion_multiply_by_scalar(const EmuMath::Quaternion<LhsT_>& lhs_, Rhs_&& rhs_)
		-> std::enable_if_t<quaternion_can_scalar_multiply<LhsT_, Rhs_, OutT_, false>(), EmuMath::Quaternion<OutT_>>
	{
		return _quaternion_underlying::_multiply_quaternion_by_scalar<false, OutT_>(lhs_, std::forward<Rhs_>(rhs_));
	}

	/// <summary>
	/// <para> Multiplies the `lhs_` Quaternion with the `rhs_` Quaternion. </para>
	/// <para> Be aware that `Quaternion * Quaternion` multiplication is non-commutative. </para>
	/// </summary>
	/// <param name="lhs_">EmuMath Quaternion on the left-hand side of multiplication.</param>
	/// <param name="rhs_">EmuMath Quaternion on the right-hand side of multiplication.</param>
	/// <returns>EmuMath Quaternion containing the results of the selected multiplication operation.</returns>
	template<typename OutT_, typename LhsT_, typename RhsT_>
	[[nodiscard]] constexpr inline auto quaternion_multiply_by_quaternion(const EmuMath::Quaternion<LhsT_>& lhs_, const EmuMath::Quaternion<RhsT_>& rhs_)
		-> std::enable_if_t<quaternion_can_quaternion_multiply<LhsT_, RhsT_, OutT_, false>(), EmuMath::Quaternion<OutT_>>
	{
		return _quaternion_underlying::_multiply_quaternion_by_quaternion<false, OutT_>(lhs_, rhs_);
	}
#pragma endregion
}

#endif
