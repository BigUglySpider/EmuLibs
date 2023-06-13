#ifndef EMU_MATH_QUATERNION_INTERPOLATION_H_INC_
#define EMU_MATH_QUATERNION_INTERPOLATION_H_INC_ 1

#include "_common_quaternion_helper_includes.h"

namespace EmuMath::Helpers
{
#pragma region VALIDITY_CHECKS
	/// <summary>
	/// <para> Check to see if two Quaternions can be linearly interpolated to result in a desired output type. </para>
	/// <para> If StaticAssert_ is true, this will trigger a static assertion in cases where it returns false. </para>
	/// </summary>
	/// <returns>
	///		True if a basic linear interplation with Quaternions A and B with the respective typeargs and T_ of the provided type may be performed,
	///		and the results of said operation may be output as a Quaternion with the provided OutT_ argument.
	/// </returns>
	template<typename AT_, typename BT_, typename T_, typename OutT_, bool StaticAssert_ = false>
	[[nodiscard]] constexpr inline bool quaternion_lerp_valid_args()
	{
		return _quaternion_underlying::_valid_lerp_args<false, false, OutT_, AT_, BT_, T_, StaticAssert_>();
	}

	/// <summary>
	/// <para> Check to see if two Quaternions can be linearly interpolated to result in a desired output type, using fused operations where possible. </para>
	/// <para> If StaticAssert_ is true, this will trigger a static assertion in cases where it returns false. </para>
	/// </summary>
	/// <returns>
	///		True if a basic linear interplation (using fused operations) with Quaternions A and B with the respective typeargs, and T_ of the provided type may be performed,
	///		and the results of said operation may be output as a Quaternion with the provided OutT_ argument.
	/// </returns>
	template<typename AT_, typename BT_, typename T_, typename OutT_, bool StaticAssert_ = false>
	[[nodiscard]] constexpr inline bool quaternion_fused_lerp_valid_args()
	{
		return _quaternion_underlying::_valid_lerp_args<false, true, OutT_, AT_, BT_, T_, StaticAssert_>();
	}

	/// <summary>
	/// <para> Check to see if two Quaternions can be spherically linearly interpolated to result in a desired output type. </para>
	/// <para> If StaticAssert_ is true, this will trigger a static assertion in cases where it returns false. </para>
	/// </summary>
	/// <returns>
	///		True if a spherical linear interplation with Quaternions A and B with the respective typeargs and T_ of the provided type may be performed,
	///		and the results of said operation may be output as a Quaternion with the provided OutT_ argument.
	/// </returns>
	template<typename AT_, typename BT_, typename T_, typename OutT_, bool StaticAssert_ = false>
	[[nodiscard]] constexpr inline bool quaternion_slerp_valid_args()
	{
		return _quaternion_underlying::_valid_slerp_args<false, false, false, OutT_, AT_, BT_, T_, StaticAssert_>();
	}

	/// <summary>
	/// <para> Check to see if two Quaternions can be spherically linearly interpolated to result in a desired output type, using fused operations where possible.. </para>
	/// <para> If StaticAssert_ is true, this will trigger a static assertion in cases where it returns false. </para>
	/// </summary>
	/// <returns>
	///		True if a spherical linear interplation (using fused operations) with Quaternions A and B with the respective typeargs and T_ of the provided type may be performed,
	///		and the results of said operation may be output as a Quaternion with the provided OutT_ argument.
	/// </returns>
	template<typename AT_, typename BT_, typename T_, typename OutT_, bool StaticAssert_ = false>
	[[nodiscard]] constexpr inline bool quaternion_fused_slerp_valid_args()
	{
		return _quaternion_underlying::_valid_slerp_args<false, true, false, OutT_, AT_, BT_, T_, StaticAssert_>();
	}

	/// <summary>
	/// <para> Check to see if two Quaternions can be spherically linearly interpolated (in a context aiming to be constexpr-evaluable) to result in a desired output type. </para>
	/// <para> If StaticAssert_ is true, this will trigger a static assertion in cases where it returns false. </para>
	/// <para> Note that this does not determine if the call will be constexpr-evaluable. </para>
	/// </summary>
	/// <returns>
	///		True if a spherical linear interplation with Quaternions A and B with the respective typeargs and T_ of the provided type may be performed,
	///		and the results of said operation may be output as a Quaternion with the provided OutT_ argument, all in a context aiming to be constexpr-evaluable.
	/// </returns>
	template<typename AT_, typename BT_, typename T_, typename OutT_, bool StaticAssert_ = false>
	[[nodiscard]] constexpr inline bool quaternion_slerp_constexpr_valid_args()
	{
		return _quaternion_underlying::_valid_slerp_args<false, false, true, OutT_, AT_, BT_, T_, StaticAssert_>();
	}
#pragma endregion

#pragma region LERP_FUNCS
	/// <summary>
	/// <para> Outputs a new Quaternion that is the result of linearly interpolating Quaternion a_ with Quaternion b_, using a weighting of t_. </para>
	/// <para> Typically, `quaternion_slerp` (Spherical linear interpolation) is likely to be preferred for smoother interpolations. </para>
	/// <para> The resulting Quaternion is not automatically normalised, so arguments that may result in a non-unit Quaternion should be considered. </para>
	/// </summary>
	/// <param name="a_">Quaternion to interpolate from.</param>
	/// <param name="b_">Quaternion to interpolate toward.</param>
	/// <param name="t_">Weighting for interpolation, which may be either a scalar for all weightings or an EmuMath Vector of respective weightings.</param>
	/// <returns>Quaternion resulting from the linear interpolation.</returns>
	template<typename OutT_, typename AT_, typename BT_, typename T_>
	[[nodiscard]] constexpr inline auto quaternion_lerp(const EmuMath::Quaternion<AT_>& a_, const EmuMath::Quaternion<BT_>& b_, T_&& t_)
		-> std::enable_if_t<quaternion_lerp_valid_args<AT_, BT_, T_, OutT_, false>(), EmuMath::Quaternion<OutT_>>
	{
		return _quaternion_underlying::_make_lerp<false, false, OutT_>(a_, b_, std::forward<T_>(t_));
	}

	/// <summary>
	/// <para> Outputs a new Quaternion that is the result of linearly interpolating Quaternion a_ with Quaternion b_, using a weighting of t_. </para>
	/// <para> Typically, `quaternion_slerp` (Spherical linear interpolation) is likely to be preferred for smoother interpolations. </para>
	/// <para> The resulting Quaternion is not automatically normalised, so arguments that may result in a non-unit Quaternion should be considered. </para>
	/// <para>
	///		This function will attempt to take advantage of fused instructions (such as FMADD) if possible, or emulate them otherwise. 
	///		Use of such instructions may improve accuracy and/or performance.
	/// </para>
	/// </summary>
	/// <param name="a_">Quaternion to interpolate from.</param>
	/// <param name="b_">Quaternion to interpolate toward.</param>
	/// <param name="t_">Weighting for interpolation, which may be either a scalar for all weightings or an EmuMath Vector of respective weightings.</param>
	/// <returns>Quaternion resulting from the linear interpolation.</returns>
	template<typename OutT_, typename AT_, typename BT_, typename T_>
	[[nodiscard]] constexpr inline auto quaternion_fused_lerp(const EmuMath::Quaternion<AT_>& a_, const EmuMath::Quaternion<BT_>& b_, T_&& t_)
		-> std::enable_if_t<quaternion_fused_lerp_valid_args<AT_, BT_, T_, OutT_, false>(), EmuMath::Quaternion<OutT_>>
	{
		return _quaternion_underlying::_make_lerp<false, true, OutT_>(a_, b_, std::forward<T_>(t_));
	}
#pragma endregion

#pragma region SLERP_FUNCS
	/// <summary>
	/// <para> Outputs a new Quaternion that is the result of a spherical linear interpolation of Quaternion a_ with Quaternion b_, using a weighting of t_. </para>
	/// <para> Typically, this is likely to be preferred over a plain `quaternion_lerp` for smoother interpolations. </para>
	/// <para> The resulting Quaternion is not automatically normalised, so arguments that may result in a non-unit Quaternion should be considered. </para>
	/// </summary>
	/// <param name="a_">Quaternion to interpolate from.</param>
	/// <param name="b_">Quaternion to interpolate toward.</param>
	/// <param name="t_">Weighting for interpolation, which is expected to be a scalar.</param>
	/// <returns>Quaternion resulting from the spherical linear interpolation.</returns>
	template<typename OutT_, typename AT_, typename BT_, typename T_>
	[[nodiscard]] constexpr inline auto quaternion_slerp(const EmuMath::Quaternion<AT_>& a_, const EmuMath::Quaternion<BT_>& b_, T_&& t_)
		-> std::enable_if_t<quaternion_slerp_valid_args<AT_, BT_, T_, OutT_, false>(), EmuMath::Quaternion<OutT_>>
	{
		return _quaternion_underlying::_make_slerp<false, false, false, OutT_>(a_, b_, std::forward<T_>(t_));
	}

	/// <summary>
	/// <para> Outputs a new Quaternion that is the result of a spherical linear interpolation of Quaternion a_ with Quaternion b_, using a weighting of t_. </para>
	/// <para> Typically, this is likely to be preferred over a plain `quaternion_lerp` for smoother interpolations. </para>
	/// <para> The resulting Quaternion is not automatically normalised, so arguments that may result in a non-unit Quaternion should be considered. </para>
	/// <para>
	///		This function will attempt to take advantage of fused instructions (such as FMADD) if possible, or emulate them otherwise. 
	///		Use of such instructions may improve accuracy and/or performance.
	/// </para>
	/// </summary>
	/// <param name="a_">Quaternion to interpolate from.</param>
	/// <param name="b_">Quaternion to interpolate toward.</param>
	/// <param name="t_">Weighting for interpolation, which is expected to be a scalar.</param>
	/// <returns>Quaternion resulting from the spherical linear interpolation.</returns>
	template<typename OutT_, typename AT_, typename BT_, typename T_>
	[[nodiscard]] constexpr inline auto quaternion_fused_slerp(const EmuMath::Quaternion<AT_>& a_, const EmuMath::Quaternion<BT_>& b_, T_&& t_)
		-> std::enable_if_t<quaternion_fused_slerp_valid_args<AT_, BT_, T_, OutT_, false>(), EmuMath::Quaternion<OutT_>>
	{
		return _quaternion_underlying::_make_slerp<false, true, false, OutT_>(a_, b_, std::forward<T_>(t_));
	}

	/// <summary>
	/// <para> Outputs a new Quaternion that is the result of a spherical linear interpolation of Quaternion a_ with Quaternion b_, using a weighting of t_. </para>
	/// <para> Typically, this is likely to be preferred over a plain `quaternion_lerp` for smoother interpolations. </para>
	/// <para> The resulting Quaternion is not automatically normalised, so arguments that may result in a non-unit Quaternion should be considered. </para>
	/// <para> This function will attempt to be constexpr-evaluable, which may have an effect on accuracy and/or performance. </para>
	/// </summary>
	/// <param name="a_">Quaternion to interpolate from.</param>
	/// <param name="b_">Quaternion to interpolate toward.</param>
	/// <param name="t_">Weighting for interpolation, which is expected to be a scalar.</param>
	/// <returns>Quaternion resulting from the spherical linear interpolation.</returns>
	template<typename OutT_, typename AT_, typename BT_, typename T_>
	[[nodiscard]] constexpr inline auto quaternion_slerp_constexpr(const EmuMath::Quaternion<AT_>& a_, const EmuMath::Quaternion<BT_>& b_, T_&& t_)
		-> std::enable_if_t<quaternion_slerp_constexpr_valid_args<AT_, BT_, T_, OutT_, false>(), EmuMath::Quaternion<OutT_>>
	{
		return _quaternion_underlying::_make_slerp<false, false, true, OutT_>(a_, b_, std::forward<T_>(t_));
	}
#pragma endregion
}

#endif
