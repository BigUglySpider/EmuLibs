#ifndef EMU_MATH_QUATERNION_CONVERSION_TO_EULER_H_INC_
#define EMU_MATH_QUATERNION_CONVERSION_TO_EULER_H_INC_ 1

#include "../_common_quaternion_helper_includes.h"


namespace EmuMath::Helpers
{
#pragma region VALIDITY_CHECKS
	/// <summary>
	/// <para> Check to see if a Quaternion can be converted to a 3D Euler Vector using the given arguments. </para>
	/// <para> If StaticAssert_ is true, this will trigger a static assertion in cases where it returns false. </para>
	/// </summary>
	/// <returns>True if a Quaternion-to-Euler conversion is valid with the given arguments, and a 3D EmuMath Vector with typearg OutT_ can be created from it.</returns>
	template<bool OutRads_, typename OutT_, typename T_, typename Epsilon_, bool StaticAssert_ = false>
	[[nodiscard]] constexpr inline bool quaternion_can_convert_to_euler()
	{
		return _quaternion_underlying::_valid_convert_to_euler_args<false, OutT_, false, OutRads_, T_, Epsilon_, StaticAssert_>();
	}

	template<bool OutRads_, typename OutT_, typename T_, bool StaticAssert_ = false>
	[[nodiscard]] constexpr inline bool quaternion_can_convert_to_euler()
	{
		return _quaternion_underlying::_valid_convert_to_euler_args<false, OutT_, false, OutRads_, T_, StaticAssert_>();
	}

	template<typename OutT_, typename T_, typename Epsilon_, bool StaticAssert_ = false>
	[[nodiscard]] constexpr inline bool quaternion_can_convert_to_euler()
	{
		return _quaternion_underlying::_valid_convert_to_euler_args<false, OutT_, false, true, T_, Epsilon_, StaticAssert_>();
	}

	template<typename OutT_, typename T_, bool StaticAssert_ = false>
	[[nodiscard]] constexpr inline bool quaternion_can_convert_to_euler()
	{
		return _quaternion_underlying::_valid_convert_to_euler_args<false, OutT_, false, true, T_, StaticAssert_>();
	}

	/// <summary>
	/// <para> Check to see if a Quaternion can be converted to a 3D Euler Vector using the given arguments, using fused operations where possible. </para>
	/// <para> If StaticAssert_ is true, this will trigger a static assertion in cases where it returns false. </para>
	/// </summary>
	/// <returns>True if a Quaternion-to-Euler conversion is valid with the given arguments, and a 3D EmuMath Vector with typearg OutT_ can be created from it.</returns>
	template<bool OutRads_, typename OutT_, typename T_, typename Epsilon_, bool StaticAssert_ = false>
	[[nodiscard]] constexpr inline bool quaternion_can_convert_to_euler_fused()
	{
		return _quaternion_underlying::_valid_convert_to_euler_args<true, OutT_, false, OutRads_, T_, Epsilon_, StaticAssert_>();
	}

	template<bool OutRads_, typename OutT_, typename T_, bool StaticAssert_ = false>
	[[nodiscard]] constexpr inline bool quaternion_can_convert_to_euler_fused()
	{
		return _quaternion_underlying::_valid_convert_to_euler_args<true, OutT_, false, OutRads_, T_, StaticAssert_>();
	}

	template<typename OutT_, typename T_, typename Epsilon_, bool StaticAssert_ = false>
	[[nodiscard]] constexpr inline bool quaternion_can_convert_to_euler_fused()
	{
		return _quaternion_underlying::_valid_convert_to_euler_args<true, OutT_, false, true, T_, Epsilon_, StaticAssert_>();
	}

	template<typename OutT_, typename T_, bool StaticAssert_ = false>
	[[nodiscard]] constexpr inline bool quaternion_can_convert_to_euler_fused()
	{
		return _quaternion_underlying::_valid_convert_to_euler_args<true, OutT_, false, true, T_, StaticAssert_>();
	}

	/// <summary>
	/// <para> Check to see if a Quaternion can be converted to a 3D Euler Vector using the given arguments (in a context aiming to be constexpr-evaluable). </para>
	/// <para> If StaticAssert_ is true, this will trigger a static assertion in cases where it returns false. </para>
	/// </summary>
	/// <returns>True if a Quaternion-to-Euler conversion is valid with the given arguments, and a 3D EmuMath Vector with typearg OutT_ can be created from it.</returns>
	template<bool OutRads_, typename OutT_, typename T_, typename Epsilon_, bool StaticAssert_ = false>
	[[nodiscard]] constexpr inline bool quaternion_can_convert_to_euler_constexpr()
	{
		return _quaternion_underlying::_valid_convert_to_euler_args<false, OutT_, true, OutRads_, T_, Epsilon_, StaticAssert_>();
	}

	template<bool OutRads_, typename OutT_, typename T_, bool StaticAssert_ = false>
	[[nodiscard]] constexpr inline bool quaternion_can_convert_to_euler_constexpr()
	{
		return _quaternion_underlying::_valid_convert_to_euler_args<false, OutT_, true, OutRads_, T_, StaticAssert_>();
	}

	template<typename OutT_, typename T_, typename Epsilon_, bool StaticAssert_ = false>
	[[nodiscard]] constexpr inline bool quaternion_can_convert_to_euler_constexpr()
	{
		return _quaternion_underlying::_valid_convert_to_euler_args<false, OutT_, true, true, T_, Epsilon_, StaticAssert_>();
	}

	template<typename OutT_, typename T_, bool StaticAssert_ = false>
	[[nodiscard]] constexpr inline bool quaternion_can_convert_to_euler_constexpr()
	{
		return _quaternion_underlying::_valid_convert_to_euler_args<false, OutT_, true, true, T_, StaticAssert_>();
	}
#pragma endregion

#pragma region CONVERT_TO_EULER_FUNCS
	/// <summary>
	/// <para> Converts the passed Quaternion to a 3D EmuMath Vector of Euler angles. </para>
	/// <para> May optionally output as either radians or degrees. If `OutRads_` is omitted, it will be treated as `true` and thus output will be in radians. </para>
	/// <para> May provide an optional Epsilon value for floating-point near-equality checks. If not passed, a default epsilon based on calculation type will be chosen. </para>
	/// <para> 
	///		Note that the same Quaternion can be represented by multiple Euler rotations; 
	///		as such, it is not uncommon for a Quaternion created from Euler angles to output a different set of angles compared to what it received as input.
	/// </para>
	/// </summary>
	/// <param name="quaternion_">Quaternion to convert to a 3D Euler Vector.</param>
	/// <param name="epsilon_">Optional epsilon value to use for floating-point near-equal comparisons. Will default to a suitable epsilon for calculations if omitted.</param>
	/// <returns>3D EmuMath Vector of Euler angles X, Y, Z represented by the passed Quaternion.</returns>
	template<bool OutRads_, typename OutT_, typename Epsilon_, typename T_>
	[[nodiscard]] constexpr inline auto quaternion_to_euler(const EmuMath::Quaternion<T_>& quaternion_, Epsilon_&& epsilon_)
		-> std::enable_if_t<quaternion_can_convert_to_euler<OutRads_, OutT_, T_, Epsilon_, false>(), EmuMath::Vector<3, OutT_>>
	{
		return _quaternion_underlying::_convert_to_euler_vector<false, OutT_, false, OutRads_>(quaternion_, std::forward<Epsilon_>(epsilon_));
	}

	template<bool OutRads_, typename OutT_, typename T_>
	[[nodiscard]] constexpr inline auto quaternion_to_euler(const EmuMath::Quaternion<T_>& quaternion_)
		-> std::enable_if_t<quaternion_can_convert_to_euler<OutRads_, OutT_, T_, false>(), EmuMath::Vector<3, OutT_>>
	{
		return _quaternion_underlying::_convert_to_euler_vector<false, OutT_, false, OutRads_>(quaternion_);
	}

	template<typename OutT_, typename Epsilon_, typename T_>
	[[nodiscard]] constexpr inline auto quaternion_to_euler(const EmuMath::Quaternion<T_>& quaternion_, Epsilon_&& epsilon_)
		-> std::enable_if_t<quaternion_can_convert_to_euler<true, OutT_, T_, Epsilon_, false>(), EmuMath::Vector<3, OutT_>>
	{
		return _quaternion_underlying::_convert_to_euler_vector<false, OutT_, false, true>(quaternion_, std::forward<Epsilon_>(epsilon_));
	}

	template<typename OutT_, typename T_>
	[[nodiscard]] constexpr inline auto quaternion_to_euler(const EmuMath::Quaternion<T_>& quaternion_)
		-> std::enable_if_t<quaternion_can_convert_to_euler<true, OutT_, T_, false>(), EmuMath::Vector<3, OutT_>>
	{
		return _quaternion_underlying::_convert_to_euler_vector<false, OutT_, false, true>(quaternion_);
	}

	/// <summary>
	/// <para> Converts the passed Quaternion to a 3D EmuMath Vector of Euler angles. </para>
	/// <para> May optionally output as either radians or degrees. If `OutRads_` is omitted, it will be treated as `true` and thus output will be in radians. </para>
	/// <para> May provide an optional Epsilon value for floating-point near-equality checks. If not passed, a default epsilon based on calculation type will be chosen. </para>
	/// <para> 
	///		Note that the same Quaternion can be represented by multiple Euler rotations; 
	///		as such, it is not uncommon for a Quaternion created from Euler angles to output a different set of angles compared to what it received as input.
	/// </para>
	/// <para>
	///		This function will attempt to take advantage of fused instructions (such as FMADD) if possible, or emulate them otherwise. 
	///		Use of such instructions may improve accuracy and/or performance.
	/// </para>
	/// </summary>
	/// <param name="quaternion_">Quaternion to convert to a 3D Euler Vector.</param>
	/// <param name="epsilon_">Optional epsilon value to use for floating-point near-equal comparisons. Will default to a suitable epsilon for calculations if omitted.</param>
	/// <returns>3D EmuMath Vector of Euler angles X, Y, Z represented by the passed Quaternion.</returns>
	template<bool OutRads_, typename OutT_, typename Epsilon_, typename T_>
	[[nodiscard]] constexpr inline auto quaternion_to_euler_fused(const EmuMath::Quaternion<T_>& quaternion_, Epsilon_&& epsilon_)
		-> std::enable_if_t<quaternion_can_convert_to_euler_fused<OutRads_, OutT_, T_, Epsilon_, false>(), EmuMath::Vector<3, OutT_>>
	{
		return _quaternion_underlying::_convert_to_euler_vector<true, OutT_, false, OutRads_>(quaternion_, std::forward<Epsilon_>(epsilon_));
	}

	template<bool OutRads_, typename OutT_, typename T_>
	[[nodiscard]] constexpr inline auto quaternion_to_euler_fused(const EmuMath::Quaternion<T_>& quaternion_)
		-> std::enable_if_t<quaternion_can_convert_to_euler_fused<OutRads_, OutT_, T_, false>(), EmuMath::Vector<3, OutT_>>
	{
		return _quaternion_underlying::_convert_to_euler_vector<true, OutT_, false, OutRads_>(quaternion_);
	}

	template<typename OutT_, typename Epsilon_, typename T_>
	[[nodiscard]] constexpr inline auto quaternion_to_euler_fused(const EmuMath::Quaternion<T_>& quaternion_, Epsilon_&& epsilon_)
		-> std::enable_if_t<quaternion_can_convert_to_euler_fused<true, OutT_, T_, Epsilon_, false>(), EmuMath::Vector<3, OutT_>>
	{
		return _quaternion_underlying::_convert_to_euler_vector<true, OutT_, false, true>(quaternion_, std::forward<Epsilon_>(epsilon_));
	}

	template<typename OutT_, typename T_>
	[[nodiscard]] constexpr inline auto quaternion_to_euler_fused(const EmuMath::Quaternion<T_>& quaternion_)
		-> std::enable_if_t<quaternion_can_convert_to_euler_fused<true, OutT_, T_, false>(), EmuMath::Vector<3, OutT_>>
	{
		return _quaternion_underlying::_convert_to_euler_vector<true, OutT_, false, true>(quaternion_);
	}

	/// <summary>
	/// <para> Converts the passed Quaternion to a 3D EmuMath Vector of Euler angles. </para>
	/// <para> May optionally output as either radians or degrees. If `OutRads_` is omitted, it will be treated as `true` and thus output will be in radians. </para>
	/// <para> May provide an optional Epsilon value for floating-point near-equality checks. If not passed, a default epsilon based on calculation type will be chosen. </para>
	/// <para> 
	///		Note that the same Quaternion can be represented by multiple Euler rotations; 
	///		as such, it is not uncommon for a Quaternion created from Euler angles to output a different set of angles compared to what it received as input.
	/// </para>
	/// <para> This function will attempt to be constexpr-evaluable, which may have an effect on accuracy and/or performance. </para>
	/// </summary>
	/// <param name="quaternion_">Quaternion to convert to a 3D Euler Vector.</param>
	/// <param name="epsilon_">Optional epsilon value to use for floating-point near-equal comparisons. Will default to a suitable epsilon for calculations if omitted.</param>
	/// <returns>3D EmuMath Vector of Euler angles X, Y, Z represented by the passed Quaternion.</returns>
	template<bool OutRads_, typename OutT_, typename Epsilon_, typename T_>
	[[nodiscard]] constexpr inline auto quaternion_to_euler_constexpr(const EmuMath::Quaternion<T_>& quaternion_, Epsilon_&& epsilon_)
		-> std::enable_if_t<quaternion_can_convert_to_euler_constexpr<OutRads_, OutT_, T_, Epsilon_, false>(), EmuMath::Vector<3, OutT_>>
	{
		return _quaternion_underlying::_convert_to_euler_vector<false, OutT_, true, OutRads_>(quaternion_, std::forward<Epsilon_>(epsilon_));
	}

	template<bool OutRads_, typename OutT_, typename T_>
	[[nodiscard]] constexpr inline auto quaternion_to_euler_constexpr(const EmuMath::Quaternion<T_>& quaternion_)
		-> std::enable_if_t<quaternion_can_convert_to_euler_constexpr<OutRads_, OutT_, T_, false>(), EmuMath::Vector<3, OutT_>>
	{
		return _quaternion_underlying::_convert_to_euler_vector<false, OutT_, true, OutRads_>(quaternion_);
	}

	template<typename OutT_, typename Epsilon_, typename T_>
	[[nodiscard]] constexpr inline auto quaternion_to_euler_constexpr(const EmuMath::Quaternion<T_>& quaternion_, Epsilon_&& epsilon_)
		-> std::enable_if_t<quaternion_can_convert_to_euler_constexpr<true, OutT_, T_, Epsilon_, false>(), EmuMath::Vector<3, OutT_>>
	{
		return _quaternion_underlying::_convert_to_euler_vector<false, OutT_, true, true>(quaternion_, std::forward<Epsilon_>(epsilon_));
	}

	template<typename OutT_, typename T_>
	[[nodiscard]] constexpr inline auto quaternion_to_euler_constexpr(const EmuMath::Quaternion<T_>& quaternion_)
		-> std::enable_if_t<quaternion_can_convert_to_euler_constexpr<true, OutT_, T_, false>(), EmuMath::Vector<3, OutT_>>
	{
		return _quaternion_underlying::_convert_to_euler_vector<false, OutT_, true, true>(quaternion_);
	}
#pragma endregion
}

#endif
