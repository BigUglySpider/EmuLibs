#ifndef EMU_MATH_QUATERNION_CONVERSIONS_H_INC_
#define EMU_MATH_QUATERNION_CONVERSIONS_H_INC_ 1

#include "_common_quaternion_helper_includes.h"

namespace EmuMath::Helpers
{
#pragma region VALIDITY_CHECKS
	/// <summary>
	/// <para> Check to see if a Quaternion can be created as a conversion of the passed X_/Y_/Z_ types from euler angles. </para>
	/// <para> If StaticAssert_ is true, this will trigger a static assertion in cases where it returns false. </para>
	/// </summary>
	/// <returns>True if a Euler-to-Quaternion conversion is valid with the given arguments, and a Quaternion with typearg OutT_ can be created from it.</returns>
	template<bool IsRads_, bool Normalise_, bool PreferMultiplies_, typename OutT_, typename X_, typename Y_, typename Z_, bool StaticAssert_ = false>
	[[nodiscard]] constexpr inline bool quaternion_can_convert_from_euler()
	{
		return _quaternion_underlying::_valid_euler_conversion_args<false, OutT_, X_, Y_, Z_, PreferMultiplies_, Normalise_, IsRads_, false, false, StaticAssert_>();
	}

	template<bool IsRads_, bool Normalise_, typename OutT_, typename X_, typename Y_, typename Z_, bool StaticAssert_ = false>
	[[nodiscard]] constexpr inline bool quaternion_can_convert_from_euler()
	{
		return _quaternion_underlying::_valid_euler_conversion_args<false, OutT_, X_, Y_, Z_, false, Normalise_, IsRads_, false, false, StaticAssert_>();
	}

	template<bool IsRads_, typename OutT_, typename X_, typename Y_, typename Z_, bool StaticAssert_ = false>
	[[nodiscard]] constexpr inline bool quaternion_can_convert_from_euler()
	{
		return _quaternion_underlying::_valid_euler_conversion_args<false, OutT_, X_, Y_, Z_, false, true, IsRads_, false, false, StaticAssert_>();
	}

	/// <summary>
	/// <para> Check to see if a Quaternion can be created as a conversion of the passed X_/Y_/Z_ types from euler angles, using fused operations where possible. </para>
	/// <para> If StaticAssert_ is true, this will trigger a static assertion in cases where it returns false. </para>
	/// </summary>
	/// <returns>True if a Euler-to-Quaternion conversion is valid with the given arguments, and a Quaternion with typearg OutT_ can be created from it.</returns>
	template<bool IsRads_, bool Normalise_, bool PreferMultiplies_, typename OutT_, typename X_, typename Y_, typename Z_, bool StaticAssert_ = false>
	[[nodiscard]] constexpr inline bool quaternion_can_convert_from_euler_fused()
	{
		return _quaternion_underlying::_valid_euler_conversion_args<false, OutT_, X_, Y_, Z_, PreferMultiplies_, Normalise_, IsRads_, true, false, StaticAssert_>();
	}

	template<bool IsRads_, bool Normalise_, typename OutT_, typename X_, typename Y_, typename Z_, bool StaticAssert_ = false>
	[[nodiscard]] constexpr inline bool quaternion_can_convert_from_euler_fused()
	{
		return _quaternion_underlying::_valid_euler_conversion_args<false, OutT_, X_, Y_, Z_, false, Normalise_, IsRads_, true, false, StaticAssert_>();
	}

	template<bool IsRads_, typename OutT_, typename X_, typename Y_, typename Z_, bool StaticAssert_ = false>
	[[nodiscard]] constexpr inline bool quaternion_can_convert_from_euler_fused()
	{
		return _quaternion_underlying::_valid_euler_conversion_args<false, OutT_, X_, Y_, Z_, false, true, IsRads_, true, false, StaticAssert_>();
	}

	/// <summary>
	/// <para> Check to see if a Quaternion can be created as a conversion of the passed X_/Y_/Z_ types from euler angles (in a context aiming to be constexpr-evaluable). </para>
	/// <para> If StaticAssert_ is true, this will trigger a static assertion in cases where it returns false. </para>
	/// </summary>
	/// <returns>True if a Euler-to-Quaternion conversion is valid with the given arguments, and a Quaternion with typearg OutT_ can be created from it.</returns>
	template<bool IsRads_, bool Normalise_, bool PreferMultiplies_, typename OutT_, typename X_, typename Y_, typename Z_, bool StaticAssert_ = false>
	[[nodiscard]] constexpr inline bool quaternion_can_convert_from_euler_constexpr()
	{
		return _quaternion_underlying::_valid_euler_conversion_args<false, OutT_, X_, Y_, Z_, PreferMultiplies_, Normalise_, IsRads_, false, true, StaticAssert_>();
	}

	template<bool IsRads_, bool Normalise_, typename OutT_, typename X_, typename Y_, typename Z_, bool StaticAssert_ = false>
	[[nodiscard]] constexpr inline bool quaternion_can_convert_from_euler_constexpr()
	{
		return _quaternion_underlying::_valid_euler_conversion_args<false, OutT_, X_, Y_, Z_, false, Normalise_, IsRads_, false, true, StaticAssert_>();
	}

	template<bool IsRads_, typename OutT_, typename X_, typename Y_, typename Z_, bool StaticAssert_ = false>
	[[nodiscard]] constexpr inline bool quaternion_can_convert_from_euler_constexpr()
	{
		return _quaternion_underlying::_valid_euler_conversion_args<false, OutT_, X_, Y_, Z_, false, true, IsRads_, false, true, StaticAssert_>();
	}

	/// <summary>
	/// <para> Check to see if a Quaternion can be created as a conversion of a const-qualified Euler Vector. </para>
	/// <para> If StaticAssert_ is true, this will trigger a static assertion in cases where it returns false. </para>
	/// </summary>
	/// <returns>True if a EulerVector-to-Quaternion conversion is valid with the given arguments, and a Quaternion with typearg OutT_ can be created from it.</returns>
	template<bool IsRads_, bool Normalise_, bool PreferMultiplies_, typename OutT_, std::size_t VecSize_, typename VecT_, std::size_t ReadOffset_ = 0, bool StaticAssert_ = false>
	[[nodiscard]] constexpr inline bool quaternion_can_convert_from_const_euler_vector()
	{
		return _quaternion_underlying::_valid_euler_vector_lvalue_conversion_arg
		<
			false,
			OutT_,
			VecSize_,
			VecT_,
			ReadOffset_,
			true,
			PreferMultiplies_,
			Normalise_,
			IsRads_,
			false,
			false,
			StaticAssert_
		>();
	}

	template<bool IsRads_, bool Normalise_, typename OutT_, std::size_t VecSize_, typename VecT_, std::size_t ReadOffset_ = 0, bool StaticAssert_ = false>
	[[nodiscard]] constexpr inline bool quaternion_can_convert_from_const_euler_vector()
	{
		return _quaternion_underlying::_valid_euler_vector_lvalue_conversion_arg
		<
			false,
			OutT_,
			VecSize_,
			VecT_,
			ReadOffset_,
			true,
			false,
			Normalise_,
			IsRads_,
			false,
			false,
			StaticAssert_
		>();
	}

	template<bool IsRads_, typename OutT_, std::size_t VecSize_, typename VecT_, std::size_t ReadOffset_ = 0, bool StaticAssert_ = false>
	[[nodiscard]] constexpr inline bool quaternion_can_convert_from_const_euler_vector()
	{
		return _quaternion_underlying::_valid_euler_vector_lvalue_conversion_arg
		<
			false,
			OutT_,
			VecSize_,
			VecT_,
			ReadOffset_,
			true,
			false,
			true,
			IsRads_,
			false,
			false,
			StaticAssert_
		>();
	}

	/// <summary>
	/// <para> Check to see if a Quaternion can be created as a conversion of a const-qualified Euler Vector, using fused operations where possible. </para>
	/// <para> If StaticAssert_ is true, this will trigger a static assertion in cases where it returns false. </para>
	/// </summary>
	/// <returns>True if a EulerVector-to-Quaternion conversion is valid with the given arguments, and a Quaternion with typearg OutT_ can be created from it.</returns>
	template<bool IsRads_, bool Normalise_, bool PreferMultiplies_, typename OutT_, std::size_t VecSize_, typename VecT_, std::size_t ReadOffset_ = 0, bool StaticAssert_ = false>
	[[nodiscard]] constexpr inline bool quaternion_can_convert_from_const_euler_vector_fused()
	{
		return _quaternion_underlying::_valid_euler_vector_lvalue_conversion_arg
		<
			false,
			OutT_,
			VecSize_,
			VecT_,
			ReadOffset_,
			true,
			PreferMultiplies_,
			Normalise_,
			IsRads_,
			true,
			false,
			StaticAssert_
		>();
	}

	template<bool IsRads_, bool Normalise_, typename OutT_, std::size_t VecSize_, typename VecT_, std::size_t ReadOffset_ = 0, bool StaticAssert_ = false>
	[[nodiscard]] constexpr inline bool quaternion_can_convert_from_const_euler_vector_fused()
	{
		return _quaternion_underlying::_valid_euler_vector_lvalue_conversion_arg
		<
			false,
			OutT_,
			VecSize_,
			VecT_,
			ReadOffset_,
			true,
			false,
			Normalise_,
			IsRads_,
			true,
			false,
			StaticAssert_
		>();
	}

	template<bool IsRads_, typename OutT_, std::size_t VecSize_, typename VecT_, std::size_t ReadOffset_ = 0, bool StaticAssert_ = false>
	[[nodiscard]] constexpr inline bool quaternion_can_convert_from_const_euler_vector_fused()
	{
		return _quaternion_underlying::_valid_euler_vector_lvalue_conversion_arg
		<
			false,
			OutT_,
			VecSize_,
			VecT_,
			ReadOffset_,
			true,
			false,
			true,
			IsRads_,
			true,
			false,
			StaticAssert_
		>();
	}

	/// <summary>
	/// <para> Check to see if a Quaternion can be created as a conversion of a const-qualified Euler Vector (in a context aiming to be constexpr-evaluable). </para>
	/// <para> If StaticAssert_ is true, this will trigger a static assertion in cases where it returns false. </para>
	/// </summary>
	/// <returns>True if a EulerVector-to-Quaternion conversion is valid with the given arguments, and a Quaternion with typearg OutT_ can be created from it.</returns>
	template<bool IsRads_, bool Normalise_, bool PreferMultiplies_, typename OutT_, std::size_t VecSize_, typename VecT_, std::size_t ReadOffset_ = 0, bool StaticAssert_ = false>
	[[nodiscard]] constexpr inline bool quaternion_can_convert_from_const_euler_vector_constexpr()
	{
		return _quaternion_underlying::_valid_euler_vector_lvalue_conversion_arg
		<
			false,
			OutT_,
			VecSize_,
			VecT_,
			ReadOffset_,
			true,
			PreferMultiplies_,
			Normalise_,
			IsRads_,
			false,
			true,
			StaticAssert_
		>();
	}

	template<bool IsRads_, bool Normalise_, typename OutT_, std::size_t VecSize_, typename VecT_, std::size_t ReadOffset_ = 0, bool StaticAssert_ = false>
	[[nodiscard]] constexpr inline bool quaternion_can_convert_from_const_euler_vector_constexpr()
	{
		return _quaternion_underlying::_valid_euler_vector_lvalue_conversion_arg
		<
			false,
			OutT_,
			VecSize_,
			VecT_,
			ReadOffset_,
			true,
			false,
			Normalise_,
			IsRads_,
			false,
			true,
			StaticAssert_
		>();
	}

	template<bool IsRads_, typename OutT_, std::size_t VecSize_, typename VecT_, std::size_t ReadOffset_ = 0, bool StaticAssert_ = false>
	[[nodiscard]] constexpr inline bool quaternion_can_convert_from_const_euler_vector_constexpr()
	{
		return _quaternion_underlying::_valid_euler_vector_lvalue_conversion_arg
		<
			false,
			OutT_,
			VecSize_,
			VecT_,
			ReadOffset_,
			true,
			false,
			true,
			IsRads_,
			false,
			true,
			StaticAssert_
		>();
	}

	/// <summary>
	/// <para> Check to see if a Quaternion can be created as a conversion of a non-const-qualified Euler Vector. </para>
	/// <para> If StaticAssert_ is true, this will trigger a static assertion in cases where it returns false. </para>
	/// </summary>
	/// <returns>True if a EulerVector-to-Quaternion conversion is valid with the given arguments, and a Quaternion with typearg OutT_ can be created from it.</returns>
	template<bool IsRads_, bool Normalise_, bool PreferMultiplies_, typename OutT_, std::size_t VecSize_, typename VecT_, std::size_t ReadOffset_ = 0, bool StaticAssert_ = false>
	[[nodiscard]] constexpr inline bool quaternion_can_convert_from_euler_vector()
	{
		return _quaternion_underlying::_valid_euler_vector_lvalue_conversion_arg
		<
			false,
			OutT_,
			VecSize_,
			VecT_,
			ReadOffset_,
			false,
			PreferMultiplies_,
			Normalise_,
			IsRads_,
			false,
			false,
			StaticAssert_
		>();
	}

	template<bool IsRads_, bool Normalise_, typename OutT_, std::size_t VecSize_, typename VecT_, std::size_t ReadOffset_ = 0, bool StaticAssert_ = false>
	[[nodiscard]] constexpr inline bool quaternion_can_convert_from_euler_vector()
	{
		return _quaternion_underlying::_valid_euler_vector_lvalue_conversion_arg
		<
			false,
			OutT_,
			VecSize_,
			VecT_,
			ReadOffset_,
			false,
			false,
			Normalise_,
			IsRads_,
			false,
			false,
			StaticAssert_
		>();
	}

	template<bool IsRads_, typename OutT_, std::size_t VecSize_, typename VecT_, std::size_t ReadOffset_ = 0, bool StaticAssert_ = false>
	[[nodiscard]] constexpr inline bool quaternion_can_convert_from_euler_vector()
	{
		return _quaternion_underlying::_valid_euler_vector_lvalue_conversion_arg
		<
			false,
			OutT_,
			VecSize_,
			VecT_,
			ReadOffset_,
			false,
			false,
			true,
			IsRads_,
			false,
			false,
			StaticAssert_
		>();
	}

	/// <summary>
	/// <para> Check to see if a Quaternion can be created as a conversion of a non-const-qualified Euler Vector, using fused operations where possible. </para>
	/// <para> If StaticAssert_ is true, this will trigger a static assertion in cases where it returns false. </para>
	/// </summary>
	/// <returns>True if a EulerVector-to-Quaternion conversion is valid with the given arguments, and a Quaternion with typearg OutT_ can be created from it.</returns>
	template<bool IsRads_, bool Normalise_, bool PreferMultiplies_, typename OutT_, std::size_t VecSize_, typename VecT_, std::size_t ReadOffset_ = 0, bool StaticAssert_ = false>
	[[nodiscard]] constexpr inline bool quaternion_can_convert_from_euler_vector_fused()
	{
		return _quaternion_underlying::_valid_euler_vector_lvalue_conversion_arg
		<
			false,
			OutT_,
			VecSize_,
			VecT_,
			ReadOffset_,
			false,
			PreferMultiplies_,
			Normalise_,
			IsRads_,
			true,
			false,
			StaticAssert_
		>();
	}

	template<bool IsRads_, bool Normalise_, typename OutT_, std::size_t VecSize_, typename VecT_, std::size_t ReadOffset_ = 0, bool StaticAssert_ = false>
	[[nodiscard]] constexpr inline bool quaternion_can_convert_from_euler_vector_fused()
	{
		return _quaternion_underlying::_valid_euler_vector_lvalue_conversion_arg
		<
			false,
			OutT_,
			VecSize_,
			VecT_,
			ReadOffset_,
			false,
			false,
			Normalise_,
			IsRads_,
			true,
			false,
			StaticAssert_
		>();
	}

	template<bool IsRads_, typename OutT_, std::size_t VecSize_, typename VecT_, std::size_t ReadOffset_ = 0, bool StaticAssert_ = false>
	[[nodiscard]] constexpr inline bool quaternion_can_convert_from_euler_vector_fused()
	{
		return _quaternion_underlying::_valid_euler_vector_lvalue_conversion_arg
		<
			false,
			OutT_,
			VecSize_,
			VecT_,
			ReadOffset_,
			false,
			false,
			true,
			IsRads_,
			true,
			false,
			StaticAssert_
		>();
	}

	/// <summary>
	/// <para> Check to see if a Quaternion can be created as a conversion of a non-const-qualified Euler Vector (in a context aiming to be constexpr-evaluable). </para>
	/// <para> If StaticAssert_ is true, this will trigger a static assertion in cases where it returns false. </para>
	/// </summary>
	/// <returns>True if a EulerVector-to-Quaternion conversion is valid with the given arguments, and a Quaternion with typearg OutT_ can be created from it.</returns>
	template<bool IsRads_, bool Normalise_, bool PreferMultiplies_, typename OutT_, std::size_t VecSize_, typename VecT_, std::size_t ReadOffset_ = 0, bool StaticAssert_ = false>
	[[nodiscard]] constexpr inline bool quaternion_can_convert_from_euler_vector_constexpr()
	{
		return _quaternion_underlying::_valid_euler_vector_lvalue_conversion_arg
		<
			false,
			OutT_,
			VecSize_,
			VecT_,
			ReadOffset_,
			false,
			PreferMultiplies_,
			Normalise_,
			IsRads_,
			false,
			true,
			StaticAssert_
		>();
	}

	template<bool IsRads_, bool Normalise_, typename OutT_, std::size_t VecSize_, typename VecT_, std::size_t ReadOffset_ = 0, bool StaticAssert_ = false>
	[[nodiscard]] constexpr inline bool quaternion_can_convert_from_euler_vector_constexpr()
	{
		return _quaternion_underlying::_valid_euler_vector_lvalue_conversion_arg
		<
			false,
			OutT_,
			VecSize_,
			VecT_,
			ReadOffset_,
			false,
			false,
			Normalise_,
			IsRads_,
			false,
			true,
			StaticAssert_
		>();
	}

	template<bool IsRads_, typename OutT_, std::size_t VecSize_, typename VecT_, std::size_t ReadOffset_ = 0, bool StaticAssert_ = false>
	[[nodiscard]] constexpr inline bool quaternion_can_convert_from_euler_vector_constexpr()
	{
		return _quaternion_underlying::_valid_euler_vector_lvalue_conversion_arg
		<
			false,
			OutT_,
			VecSize_,
			VecT_,
			ReadOffset_,
			false,
			false,
			true,
			IsRads_,
			false,
			true,
			StaticAssert_
		>();
	}

	/// <summary>
	/// <para> Check to see if a Quaternion can be created as a conversion of a rvalue Euler Vector. </para>
	/// <para> If StaticAssert_ is true, this will trigger a static assertion in cases where it returns false. </para>
	/// </summary>
	/// <returns>True if a EulerVector-to-Quaternion conversion is valid with the given arguments, and a Quaternion with typearg OutT_ can be created from it.</returns>
	template<bool IsRads_, bool Normalise_, bool PreferMultiplies_, typename OutT_, std::size_t VecSize_, typename VecT_, std::size_t ReadOffset_ = 0, bool StaticAssert_ = false>
	[[nodiscard]] constexpr inline bool quaternion_can_convert_from_rvalue_euler_vector()
	{
		return _quaternion_underlying::_valid_euler_vector_rvalue_conversion_arg
		<
			false,
			OutT_,
			VecSize_,
			VecT_,
			ReadOffset_,
			PreferMultiplies_,
			Normalise_,
			IsRads_,
			false,
			false,
			StaticAssert_
		>();
	}

	template<bool IsRads_, bool Normalise_, typename OutT_, std::size_t VecSize_, typename VecT_, std::size_t ReadOffset_ = 0, bool StaticAssert_ = false>
	[[nodiscard]] constexpr inline bool quaternion_can_convert_from_rvalue_euler_vector()
	{
		return _quaternion_underlying::_valid_euler_vector_rvalue_conversion_arg
		<
			false,
			OutT_,
			VecSize_,
			VecT_,
			ReadOffset_,
			false,
			Normalise_,
			IsRads_,
			false,
			false,
			StaticAssert_
		>();
	}

	template<bool IsRads_, typename OutT_, std::size_t VecSize_, typename VecT_, std::size_t ReadOffset_ = 0, bool StaticAssert_ = false>
	[[nodiscard]] constexpr inline bool quaternion_can_convert_from_rvalue_euler_vector()
	{
		return _quaternion_underlying::_valid_euler_vector_rvalue_conversion_arg
		<
			false,
			OutT_,
			VecSize_,
			VecT_,
			ReadOffset_,
			false,
			true,
			IsRads_,
			false,
			false,
			StaticAssert_
		>();
	}

	/// <summary>
	/// <para> Check to see if a Quaternion can be created as a conversion of a rvalue Euler Vector, using fused operations where possible. </para>
	/// <para> If StaticAssert_ is true, this will trigger a static assertion in cases where it returns false. </para>
	/// </summary>
	/// <returns>True if a EulerVector-to-Quaternion conversion is valid with the given arguments, and a Quaternion with typearg OutT_ can be created from it.</returns>
	template<bool IsRads_, bool Normalise_, bool PreferMultiplies_, typename OutT_, std::size_t VecSize_, typename VecT_, std::size_t ReadOffset_ = 0, bool StaticAssert_ = false>
	[[nodiscard]] constexpr inline bool quaternion_can_convert_from_rvalue_euler_vector_fused()
	{
		return _quaternion_underlying::_valid_euler_vector_rvalue_conversion_arg
		<
			false,
			OutT_,
			VecSize_,
			VecT_,
			ReadOffset_,
			PreferMultiplies_,
			Normalise_,
			IsRads_,
			true,
			false,
			StaticAssert_
		>();
	}

	template<bool IsRads_, bool Normalise_, typename OutT_, std::size_t VecSize_, typename VecT_, std::size_t ReadOffset_ = 0, bool StaticAssert_ = false>
	[[nodiscard]] constexpr inline bool quaternion_can_convert_from_rvalue_euler_vector_fused()
	{
		return _quaternion_underlying::_valid_euler_vector_rvalue_conversion_arg
		<
			false,
			OutT_,
			VecSize_,
			VecT_,
			ReadOffset_,
			false,
			Normalise_,
			IsRads_,
			true,
			false,
			StaticAssert_
		>();
	}

	template<bool IsRads_, typename OutT_, std::size_t VecSize_, typename VecT_, std::size_t ReadOffset_ = 0, bool StaticAssert_ = false>
	[[nodiscard]] constexpr inline bool quaternion_can_convert_from_rvalue_euler_vector_fused()
	{
		return _quaternion_underlying::_valid_euler_vector_rvalue_conversion_arg
		<
			false,
			OutT_,
			VecSize_,
			VecT_,
			ReadOffset_,
			false,
			true,
			IsRads_,
			true,
			false,
			StaticAssert_
		>();
	}

	/// <summary>
	/// <para> Check to see if a Quaternion can be created as a conversion of a rvalue Euler Vector (in a context aiming to be constexpr-evaluable). </para>
	/// <para> If StaticAssert_ is true, this will trigger a static assertion in cases where it returns false. </para>
	/// </summary>
	/// <returns>True if a EulerVector-to-Quaternion conversion is valid with the given arguments, and a Quaternion with typearg OutT_ can be created from it.</returns>
	template<bool IsRads_, bool Normalise_, bool PreferMultiplies_, typename OutT_, std::size_t VecSize_, typename VecT_, std::size_t ReadOffset_ = 0, bool StaticAssert_ = false>
	[[nodiscard]] constexpr inline bool quaternion_can_convert_from_rvalue_euler_vector_constexpr()
	{
		return _quaternion_underlying::_valid_euler_vector_rvalue_conversion_arg
		<
			false,
			OutT_,
			VecSize_,
			VecT_,
			ReadOffset_,
			PreferMultiplies_,
			Normalise_,
			IsRads_,
			false,
			true,
			StaticAssert_
		>();
	}

	template<bool IsRads_, bool Normalise_, typename OutT_, std::size_t VecSize_, typename VecT_, std::size_t ReadOffset_ = 0, bool StaticAssert_ = false>
	[[nodiscard]] constexpr inline bool quaternion_can_convert_from_rvalue_euler_vector_constexpr()
	{
		return _quaternion_underlying::_valid_euler_vector_rvalue_conversion_arg
		<
			false,
			OutT_,
			VecSize_,
			VecT_,
			ReadOffset_,
			false,
			Normalise_,
			IsRads_,
			false,
			true,
			StaticAssert_
		>();
	}

	template<bool IsRads_, typename OutT_, std::size_t VecSize_, typename VecT_, std::size_t ReadOffset_ = 0, bool StaticAssert_ = false>
	[[nodiscard]] constexpr inline bool quaternion_can_convert_from_rvalue_euler_vector_constexpr()
	{
		return _quaternion_underlying::_valid_euler_vector_rvalue_conversion_arg
		<
			false,
			OutT_,
			VecSize_,
			VecT_,
			ReadOffset_,
			false,
			true,
			IsRads_,
			false,
			true,
			StaticAssert_
		>();
	}
#pragma endregion

#pragma region FROM_EULER_SCALARS_CONVERSION_FUNCS
	/// <summary>
	/// <para> Creates a Quaternion form of the passed Euler angles. </para>
	/// <para> May optionally instruct the input angles to be interpreted as radians or degrees. If `IsRads_` is omitted, it will be treated as `true`. </para>
	/// <para> May optionally normalise the output Quaternion. If `Normalise_` is omitted, it will be treated as `true`. </para>
	/// <para> May optionally choose to prefer reciprocal multiplication over division. If `PreferMultiplies_` is omitted, it will be treated as `false`. </para>
	/// </summary>
	/// <param name="x_">Euler angle rotation in the X-axis, as either radians or degrees (depending on IsRads_).</param>
	/// <param name="y_">Euler angle rotation in the Y-axis, as either radians or degrees (depending on IsRads_).</param>
	/// <param name="z_">Euler angle rotation in the Z-axis, as either radians or degrees (depending on IsRads_).</param>
	/// <returns>Quaternion resulting from a conversion of the passed Euler angles.</returns>
	template<bool IsRads_, bool Normalise_, bool PreferMultiplies_, typename OutT_, typename X_, typename Y_, typename Z_>
	[[nodiscard]] constexpr inline auto quaternion_from_euler(X_&& x_, Y_&& y_, Z_&& z_)
		-> std::enable_if_t<quaternion_can_convert_from_euler<IsRads_, Normalise_, PreferMultiplies_, OutT_, X_, Y_, Z_, false>(), EmuMath::Quaternion<OutT_>>
	{
		return _quaternion_underlying::_make_from_euler<false, IsRads_, PreferMultiplies_, Normalise_, false, false, OutT_>
		(
			std::forward<X_>(x_),
			std::forward<Y_>(y_),
			std::forward<Z_>(z_)
		);
	}

	template<bool IsRads_, bool Normalise_, typename OutT_, typename X_, typename Y_, typename Z_>
	[[nodiscard]] constexpr inline auto quaternion_from_euler(X_&& x_, Y_&& y_, Z_&& z_)
		-> std::enable_if_t<quaternion_can_convert_from_euler<IsRads_, Normalise_, false, OutT_, X_, Y_, Z_, false>(), EmuMath::Quaternion<OutT_>>
	{
		return _quaternion_underlying::_make_from_euler<false, IsRads_, false, Normalise_, false, false, OutT_>
		(
			std::forward<X_>(x_),
			std::forward<Y_>(y_),
			std::forward<Z_>(z_)
		);
	}

	template<bool IsRads_, typename OutT_, typename X_, typename Y_, typename Z_>
	[[nodiscard]] constexpr inline auto quaternion_from_euler(X_&& x_, Y_&& y_, Z_&& z_)
		-> std::enable_if_t<quaternion_can_convert_from_euler<IsRads_, true, false, OutT_, X_, Y_, Z_, false>(), EmuMath::Quaternion<OutT_>>
	{
		return _quaternion_underlying::_make_from_euler<false, IsRads_, false, true, false, false, OutT_>
		(
			std::forward<X_>(x_),
			std::forward<Y_>(y_),
			std::forward<Z_>(z_)
		);
	}

	template<typename OutT_, typename X_, typename Y_, typename Z_>
	[[nodiscard]] constexpr inline auto quaternion_from_euler(X_&& x_, Y_&& y_, Z_&& z_)
		-> std::enable_if_t<quaternion_can_convert_from_euler<true, true, false, OutT_, X_, Y_, Z_, false>(), EmuMath::Quaternion<OutT_>>
	{
		return _quaternion_underlying::_make_from_euler<false, true, false, true, false, false, OutT_>
		(
			std::forward<X_>(x_),
			std::forward<Y_>(y_),
			std::forward<Z_>(z_)
		);
	}

	/// <summary>
	/// <para> Creates a Quaternion form of the passed Euler angles. </para>
	/// <para> May optionally instruct the input angles to be interpreted as radians or degrees. If `IsRads_` is omitted, it will be treated as `true`. </para>
	/// <para> May optionally normalise the output Quaternion. If `Normalise_` is omitted, it will be treated as `true`. </para>
	/// <para> May optionally choose to prefer reciprocal multiplication over division. If `PreferMultiplies_` is omitted, it will be treated as `false`. </para>
	/// <para>
	///		This function will attempt to take advantage of fused instructions (such as FMADD) if possible, or emulate them otherwise. 
	///		Use of such instructions may improve accuracy and/or performance.
	/// </para>
	/// </summary>
	/// <param name="x_">Euler angle rotation in the X-axis, as either radians or degrees (depending on IsRads_).</param>
	/// <param name="y_">Euler angle rotation in the Y-axis, as either radians or degrees (depending on IsRads_).</param>
	/// <param name="z_">Euler angle rotation in the Z-axis, as either radians or degrees (depending on IsRads_).</param>
	/// <returns>Quaternion resulting from a conversion of the passed Euler angles.</returns>
	template<bool IsRads_, bool Normalise_, bool PreferMultiplies_, typename OutT_, typename X_, typename Y_, typename Z_>
	[[nodiscard]] constexpr inline auto quaternion_from_euler_fused(X_&& x_, Y_&& y_, Z_&& z_)
		-> std::enable_if_t<quaternion_can_convert_from_euler_fused<IsRads_, Normalise_, PreferMultiplies_, OutT_, X_, Y_, Z_, false>(), EmuMath::Quaternion<OutT_>>
	{
		return _quaternion_underlying::_make_from_euler<false, IsRads_, PreferMultiplies_, Normalise_, true, false, OutT_>
		(
			std::forward<X_>(x_),
			std::forward<Y_>(y_),
			std::forward<Z_>(z_)
		);
	}

	template<bool IsRads_, bool Normalise_, typename OutT_, typename X_, typename Y_, typename Z_>
	[[nodiscard]] constexpr inline auto quaternion_from_euler_fused(X_&& x_, Y_&& y_, Z_&& z_)
		-> std::enable_if_t<quaternion_can_convert_from_euler_fused<IsRads_, Normalise_, false, OutT_, X_, Y_, Z_, false>(), EmuMath::Quaternion<OutT_>>
	{
		return _quaternion_underlying::_make_from_euler<false, IsRads_, false, Normalise_, true, false, OutT_>
		(
			std::forward<X_>(x_),
			std::forward<Y_>(y_),
			std::forward<Z_>(z_)
		);
	}

	template<bool IsRads_, typename OutT_, typename X_, typename Y_, typename Z_>
	[[nodiscard]] constexpr inline auto quaternion_from_euler_fused(X_&& x_, Y_&& y_, Z_&& z_)
		-> std::enable_if_t<quaternion_can_convert_from_euler_fused<IsRads_, true, false, OutT_, X_, Y_, Z_, false>(), EmuMath::Quaternion<OutT_>>
	{
		return _quaternion_underlying::_make_from_euler<false, IsRads_, false, true, true, false, OutT_>
		(
			std::forward<X_>(x_),
			std::forward<Y_>(y_),
			std::forward<Z_>(z_)
		);
	}

	template<typename OutT_, typename X_, typename Y_, typename Z_>
	[[nodiscard]] constexpr inline auto quaternion_from_euler_fused(X_&& x_, Y_&& y_, Z_&& z_)
		-> std::enable_if_t<quaternion_can_convert_from_euler_fused<true, true, false, OutT_, X_, Y_, Z_, false>(), EmuMath::Quaternion<OutT_>>
	{
		return _quaternion_underlying::_make_from_euler<false, true, false, true, true, false, OutT_>
		(
			std::forward<X_>(x_),
			std::forward<Y_>(y_),
			std::forward<Z_>(z_)
		);
	}

	/// <summary>
	/// <para> Creates a Quaternion form of the passed Euler angles. </para>
	/// <para> May optionally instruct the input angles to be interpreted as radians or degrees. If `IsRads_` is omitted, it will be treated as `true`. </para>
	/// <para> May optionally normalise the output Quaternion. If `Normalise_` is omitted, it will be treated as `true`. </para>
	/// <para> May optionally choose to prefer reciprocal multiplication over division. If `PreferMultiplies_` is omitted, it will be treated as `false`. </para>
	/// <para> This function will attempt to be constexpr-evaluable, which may have an effect on accuracy and/or performance. </para>
	/// </summary>
	/// <param name="x_">Euler angle rotation in the X-axis, as either radians or degrees (depending on IsRads_).</param>
	/// <param name="y_">Euler angle rotation in the Y-axis, as either radians or degrees (depending on IsRads_).</param>
	/// <param name="z_">Euler angle rotation in the Z-axis, as either radians or degrees (depending on IsRads_).</param>
	/// <returns>Quaternion resulting from a conversion of the passed Euler angles.</returns>
	template<bool IsRads_, bool Normalise_, bool PreferMultiplies_, typename OutT_, typename X_, typename Y_, typename Z_>
	[[nodiscard]] constexpr inline auto quaternion_from_euler_constexpr(X_&& x_, Y_&& y_, Z_&& z_)
		-> std::enable_if_t<quaternion_can_convert_from_euler_constexpr<IsRads_, Normalise_, PreferMultiplies_, OutT_, X_, Y_, Z_, false>(), EmuMath::Quaternion<OutT_>>
	{
		return _quaternion_underlying::_make_from_euler<false, IsRads_, PreferMultiplies_, Normalise_, false, true, OutT_>
		(
			std::forward<X_>(x_),
			std::forward<Y_>(y_),
			std::forward<Z_>(z_)
		);
	}

	template<bool IsRads_, bool Normalise_, typename OutT_, typename X_, typename Y_, typename Z_>
	[[nodiscard]] constexpr inline auto quaternion_from_euler_constexpr(X_&& x_, Y_&& y_, Z_&& z_)
		-> std::enable_if_t<quaternion_can_convert_from_euler_constexpr<IsRads_, Normalise_, false, OutT_, X_, Y_, Z_, false>(), EmuMath::Quaternion<OutT_>>
	{
		return _quaternion_underlying::_make_from_euler<false, IsRads_, false, Normalise_, false, true, OutT_>
		(
			std::forward<X_>(x_),
			std::forward<Y_>(y_),
			std::forward<Z_>(z_)
		);
	}

	template<bool IsRads_, typename OutT_, typename X_, typename Y_, typename Z_>
	[[nodiscard]] constexpr inline auto quaternion_from_euler_constexpr(X_&& x_, Y_&& y_, Z_&& z_)
		-> std::enable_if_t<quaternion_can_convert_from_euler_constexpr<IsRads_, true, false, OutT_, X_, Y_, Z_, false>(), EmuMath::Quaternion<OutT_>>
	{
		return _quaternion_underlying::_make_from_euler<false, IsRads_, false, true, false, true, OutT_>
		(
			std::forward<X_>(x_),
			std::forward<Y_>(y_),
			std::forward<Z_>(z_)
		);
	}

	template<typename OutT_, typename X_, typename Y_, typename Z_>
	[[nodiscard]] constexpr inline auto quaternion_from_euler_constexpr(X_&& x_, Y_&& y_, Z_&& z_)
		-> std::enable_if_t<quaternion_can_convert_from_euler_constexpr<true, true, false, OutT_, X_, Y_, Z_, false>(), EmuMath::Quaternion<OutT_>>
	{
		return _quaternion_underlying::_make_from_euler<false, true, false, true, false, true, OutT_>
		(
			std::forward<X_>(x_),
			std::forward<Y_>(y_),
			std::forward<Z_>(z_)
		);
	}
#pragma endregion

#pragma region FROM_EULER_CONST_VECTOR_CONVERSION_FUNCS
	/// <summary>
	/// <para> Creates a Quaternion form of the passed Euler Vector (interpreted as a 3D Vector). </para>
	/// <para> May optionally instruct the input angles to be interpreted as radians or degrees. If `IsRads_` is omitted, it will be treated as `true`. </para>
	/// <para> May optionally normalise the output Quaternion. If `Normalise_` is omitted, it will be treated as `true`. </para>
	/// <para> May optionally choose to prefer reciprocal multiplication over division. If `PreferMultiplies_` is omitted, it will be treated as `false`. </para>
	/// </summary>
	/// <param name="euler_vector_">EmuMath Vector to be interpreted as a 3D Vector of Euler angles to convert.</param>
	/// <returns>Quaternion resulting from a conversion of the passed Euler Vector.</returns>
	template<bool IsRads_, bool Normalise_, bool PreferMultiplies_, typename OutT_, std::size_t ReadOffset_ = 0, std::size_t VecSize_, typename VecT_>
	[[nodiscard]] constexpr inline auto quaternion_from_euler(const EmuMath::Vector<VecSize_, VecT_>& euler_vector_)
		-> std::enable_if_t
		<
			quaternion_can_convert_from_const_euler_vector<IsRads_, Normalise_, PreferMultiplies_, OutT_, VecSize_, VecT_, ReadOffset_, false>(),
			EmuMath::Quaternion<OutT_>
		>
	{
		return _quaternion_underlying::_make_from_euler_vector<false, IsRads_, PreferMultiplies_, Normalise_, false, false, OutT_, ReadOffset_>(euler_vector_);
	}

	template<bool IsRads_, bool Normalise_, typename OutT_, std::size_t ReadOffset_ = 0, std::size_t VecSize_, typename VecT_>
	[[nodiscard]] constexpr inline auto quaternion_from_euler(const EmuMath::Vector<VecSize_, VecT_>& euler_vector_)
		-> std::enable_if_t
		<
			quaternion_can_convert_from_const_euler_vector<IsRads_, Normalise_, false, OutT_, VecSize_, VecT_, ReadOffset_, false>(),
			EmuMath::Quaternion<OutT_>
		>
	{
		return _quaternion_underlying::_make_from_euler_vector<false, IsRads_, false, Normalise_, false, false, OutT_, ReadOffset_>(euler_vector_);
	}

	template<bool IsRads_, typename OutT_, std::size_t ReadOffset_ = 0, std::size_t VecSize_, typename VecT_>
	[[nodiscard]] constexpr inline auto quaternion_from_euler(const EmuMath::Vector<VecSize_, VecT_>& euler_vector_)
		-> std::enable_if_t
		<
			quaternion_can_convert_from_const_euler_vector<IsRads_, true, false, OutT_, VecSize_, VecT_, ReadOffset_, false>(),
			EmuMath::Quaternion<OutT_>
		>
	{
		return _quaternion_underlying::_make_from_euler_vector<false, IsRads_, false, true, false, false, OutT_, ReadOffset_>(euler_vector_);
	}

	template<typename OutT_, std::size_t ReadOffset_ = 0, std::size_t VecSize_, typename VecT_>
	[[nodiscard]] constexpr inline auto quaternion_from_euler(const EmuMath::Vector<VecSize_, VecT_>& euler_vector_)
		-> std::enable_if_t
		<
			quaternion_can_convert_from_const_euler_vector<true, true, false, OutT_, VecSize_, VecT_, ReadOffset_, false>(),
			EmuMath::Quaternion<OutT_>
		>
	{
		return _quaternion_underlying::_make_from_euler_vector<false, true, false, true, false, false, OutT_, ReadOffset_>(euler_vector_);
	}

	/// <summary>
	/// <para> Creates a Quaternion form of the passed Euler Vector (interpreted as a 3D Vector). </para>
	/// <para> May optionally instruct the input angles to be interpreted as radians or degrees. If `IsRads_` is omitted, it will be treated as `true`. </para>
	/// <para> May optionally normalise the output Quaternion. If `Normalise_` is omitted, it will be treated as `true`. </para>
	/// <para> May optionally choose to prefer reciprocal multiplication over division. If `PreferMultiplies_` is omitted, it will be treated as `false`. </para>
	/// <para>
	///		This function will attempt to take advantage of fused instructions (such as FMADD) if possible, or emulate them otherwise. 
	///		Use of such instructions may improve accuracy and/or performance.
	/// </para>
	/// </summary>
	/// <param name="euler_vector_">EmuMath Vector to be interpreted as a 3D Vector of Euler angles to convert.</param>
	/// <returns>Quaternion resulting from a conversion of the passed Euler Vector.</returns>
	template<bool IsRads_, bool Normalise_, bool PreferMultiplies_, typename OutT_, std::size_t ReadOffset_ = 0, std::size_t VecSize_, typename VecT_>
	[[nodiscard]] constexpr inline auto quaternion_from_euler_fused(const EmuMath::Vector<VecSize_, VecT_>& euler_vector_)
		-> std::enable_if_t
		<
			quaternion_can_convert_from_const_euler_vector_fused<IsRads_, Normalise_, PreferMultiplies_, OutT_, VecSize_, VecT_, ReadOffset_, false>(),
			EmuMath::Quaternion<OutT_>
		>
	{
		return _quaternion_underlying::_make_from_euler_vector<false, IsRads_, PreferMultiplies_, Normalise_, true, false, OutT_, ReadOffset_>(euler_vector_);
	}

	template<bool IsRads_, bool Normalise_, typename OutT_, std::size_t ReadOffset_ = 0, std::size_t VecSize_, typename VecT_>
	[[nodiscard]] constexpr inline auto quaternion_from_euler_fused(const EmuMath::Vector<VecSize_, VecT_>& euler_vector_)
		-> std::enable_if_t
		<
			quaternion_can_convert_from_const_euler_vector_fused<IsRads_, Normalise_, false, OutT_, VecSize_, VecT_, ReadOffset_, false>(),
			EmuMath::Quaternion<OutT_>
		>
	{
		return _quaternion_underlying::_make_from_euler_vector<false, IsRads_, false, Normalise_, true, false, OutT_, ReadOffset_>(euler_vector_);
	}

	template<bool IsRads_, typename OutT_, std::size_t ReadOffset_ = 0, std::size_t VecSize_, typename VecT_>
	[[nodiscard]] constexpr inline auto quaternion_from_euler_fused(const EmuMath::Vector<VecSize_, VecT_>& euler_vector_)
		-> std::enable_if_t
		<
		quaternion_can_convert_from_const_euler_vector_fused<IsRads_, true, false, OutT_, VecSize_, VecT_, ReadOffset_, false>(),
			EmuMath::Quaternion<OutT_>
		>
	{
		return _quaternion_underlying::_make_from_euler_vector<false, IsRads_, false, true, true, false, OutT_, ReadOffset_>(euler_vector_);
	}

	template<typename OutT_, std::size_t ReadOffset_ = 0, std::size_t VecSize_, typename VecT_>
	[[nodiscard]] constexpr inline auto quaternion_from_euler_fused(const EmuMath::Vector<VecSize_, VecT_>& euler_vector_)
		-> std::enable_if_t
		<
			quaternion_can_convert_from_const_euler_vector_fused<true, true, false, OutT_, VecSize_, VecT_, ReadOffset_, false>(),
			EmuMath::Quaternion<OutT_>
		>
	{
		return _quaternion_underlying::_make_from_euler_vector<false, true, false, true, true, false, OutT_, ReadOffset_>(euler_vector_);
	}

	/// <summary>
	/// <para> Creates a Quaternion form of the passed Euler Vector (interpreted as a 3D Vector). </para>
	/// <para> May optionally instruct the input angles to be interpreted as radians or degrees. If `IsRads_` is omitted, it will be treated as `true`. </para>
	/// <para> May optionally normalise the output Quaternion. If `Normalise_` is omitted, it will be treated as `true`. </para>
	/// <para> May optionally choose to prefer reciprocal multiplication over division. If `PreferMultiplies_` is omitted, it will be treated as `false`. </para>
	/// <para> This function will attempt to be constexpr-evaluable, which may have an effect on accuracy and/or performance. </para>
	/// </summary>
	/// <param name="euler_vector_">EmuMath Vector to be interpreted as a 3D Vector of Euler angles to convert.</param>
	/// <returns>Quaternion resulting from a conversion of the passed Euler Vector.</returns>
	template<bool IsRads_, bool Normalise_, bool PreferMultiplies_, typename OutT_, std::size_t ReadOffset_ = 0, std::size_t VecSize_, typename VecT_>
	[[nodiscard]] constexpr inline auto quaternion_from_euler_constexpr(const EmuMath::Vector<VecSize_, VecT_>& euler_vector_)
		-> std::enable_if_t
		<
			quaternion_can_convert_from_const_euler_vector_constexpr<IsRads_, Normalise_, PreferMultiplies_, OutT_, VecSize_, VecT_, ReadOffset_, false>(),
			EmuMath::Quaternion<OutT_>
		>
	{
		return _quaternion_underlying::_make_from_euler_vector<false, IsRads_, PreferMultiplies_, Normalise_, false, true, OutT_, ReadOffset_>(euler_vector_);
	}

	template<bool IsRads_, bool Normalise_, typename OutT_, std::size_t ReadOffset_ = 0, std::size_t VecSize_, typename VecT_>
	[[nodiscard]] constexpr inline auto quaternion_from_euler_constexpr(const EmuMath::Vector<VecSize_, VecT_>& euler_vector_)
		-> std::enable_if_t
		<
			quaternion_can_convert_from_const_euler_vector_constexpr<IsRads_, Normalise_, false, OutT_, VecSize_, VecT_, ReadOffset_, false>(),
			EmuMath::Quaternion<OutT_>
		>
	{
		return _quaternion_underlying::_make_from_euler_vector<false, IsRads_, false, Normalise_, false, true, OutT_, ReadOffset_>(euler_vector_);
	}

	template<bool IsRads_, typename OutT_, std::size_t ReadOffset_ = 0, std::size_t VecSize_, typename VecT_>
	[[nodiscard]] constexpr inline auto quaternion_from_euler_constexpr(const EmuMath::Vector<VecSize_, VecT_>& euler_vector_)
		-> std::enable_if_t
		<
			quaternion_can_convert_from_const_euler_vector_constexpr<IsRads_, true, false, OutT_, VecSize_, VecT_, ReadOffset_, false>(),
			EmuMath::Quaternion<OutT_>
		>
	{
		return _quaternion_underlying::_make_from_euler_vector<false, IsRads_, false, true, false, true, OutT_, ReadOffset_>(euler_vector_);
	}

	template<typename OutT_, std::size_t ReadOffset_ = 0, std::size_t VecSize_, typename VecT_>
	[[nodiscard]] constexpr inline auto quaternion_from_euler_constexpr(const EmuMath::Vector<VecSize_, VecT_>& euler_vector_)
		-> std::enable_if_t
		<
			quaternion_can_convert_from_const_euler_vector_constexpr<true, true, false, OutT_, VecSize_, VecT_, ReadOffset_, false>(),
			EmuMath::Quaternion<OutT_>
		>
	{
		return _quaternion_underlying::_make_from_euler_vector<false, true, false, true, false, true, OutT_, ReadOffset_>(euler_vector_);
	}
#pragma endregion

#pragma region FROM_EULER_NON_CONST_VECTOR_CONVERSION_FUNCS
	/// <summary>
	/// <para> Creates a Quaternion form of the passed Euler Vector (interpreted as a 3D Vector). </para>
	/// <para> May optionally instruct the input angles to be interpreted as radians or degrees. If `IsRads_` is omitted, it will be treated as `true`. </para>
	/// <para> May optionally normalise the output Quaternion. If `Normalise_` is omitted, it will be treated as `true`. </para>
	/// <para> May optionally choose to prefer reciprocal multiplication over division. If `PreferMultiplies_` is omitted, it will be treated as `false`. </para>
	/// </summary>
	/// <param name="euler_vector_">EmuMath Vector to be interpreted as a 3D Vector of Euler angles to convert.</param>
	/// <returns>Quaternion resulting from a conversion of the passed Euler Vector.</returns>
	template<bool IsRads_, bool Normalise_, bool PreferMultiplies_, typename OutT_, std::size_t ReadOffset_ = 0, std::size_t VecSize_, typename VecT_>
	[[nodiscard]] constexpr inline auto quaternion_from_euler(EmuMath::Vector<VecSize_, VecT_>& euler_vector_)
		-> std::enable_if_t
		<
			quaternion_can_convert_from_euler_vector<IsRads_, Normalise_, PreferMultiplies_, OutT_, VecSize_, VecT_, ReadOffset_, false>(),
			EmuMath::Quaternion<OutT_>
		>
	{
		return _quaternion_underlying::_make_from_euler_vector<false, IsRads_, PreferMultiplies_, Normalise_, false, false, OutT_, ReadOffset_>(euler_vector_);
	}

	template<bool IsRads_, bool Normalise_, typename OutT_, std::size_t ReadOffset_ = 0, std::size_t VecSize_, typename VecT_>
	[[nodiscard]] constexpr inline auto quaternion_from_euler(EmuMath::Vector<VecSize_, VecT_>& euler_vector_)
		-> std::enable_if_t
		<
			quaternion_can_convert_from_euler_vector<IsRads_, Normalise_, false, OutT_, VecSize_, VecT_, ReadOffset_, false>(),
			EmuMath::Quaternion<OutT_>
		>
	{
		return _quaternion_underlying::_make_from_euler_vector<false, IsRads_, false, Normalise_, false, false, OutT_, ReadOffset_>(euler_vector_);
	}

	template<bool IsRads_, typename OutT_, std::size_t ReadOffset_ = 0, std::size_t VecSize_, typename VecT_>
	[[nodiscard]] constexpr inline auto quaternion_from_euler(EmuMath::Vector<VecSize_, VecT_>& euler_vector_)
		-> std::enable_if_t
		<
			quaternion_can_convert_from_euler_vector<IsRads_, true, false, OutT_, VecSize_, VecT_, ReadOffset_, false>(),
			EmuMath::Quaternion<OutT_>
		>
	{
		return _quaternion_underlying::_make_from_euler_vector<false, IsRads_, false, true, false, false, OutT_, ReadOffset_>(euler_vector_);
	}

	template<typename OutT_, std::size_t ReadOffset_ = 0, std::size_t VecSize_, typename VecT_>
	[[nodiscard]] constexpr inline auto quaternion_from_euler(EmuMath::Vector<VecSize_, VecT_>& euler_vector_)
		-> std::enable_if_t
		<
			quaternion_can_convert_from_euler_vector<true, true, false, OutT_, VecSize_, VecT_, ReadOffset_, false>(),
			EmuMath::Quaternion<OutT_>
		>
	{
		return _quaternion_underlying::_make_from_euler_vector<false, true, false, true, false, false, OutT_, ReadOffset_>(euler_vector_);
	}

	/// <summary>
	/// <para> Creates a Quaternion form of the passed Euler Vector (interpreted as a 3D Vector). </para>
	/// <para> May optionally instruct the input angles to be interpreted as radians or degrees. If `IsRads_` is omitted, it will be treated as `true`. </para>
	/// <para> May optionally normalise the output Quaternion. If `Normalise_` is omitted, it will be treated as `true`. </para>
	/// <para> May optionally choose to prefer reciprocal multiplication over division. If `PreferMultiplies_` is omitted, it will be treated as `false`. </para>
	/// <para>
	///		This function will attempt to take advantage of fused instructions (such as FMADD) if possible, or emulate them otherwise. 
	///		Use of such instructions may improve accuracy and/or performance.
	/// </para>
	/// </summary>
	/// <param name="euler_vector_">EmuMath Vector to be interpreted as a 3D Vector of Euler angles to convert.</param>
	/// <returns>Quaternion resulting from a conversion of the passed Euler Vector.</returns>
	template<bool IsRads_, bool Normalise_, bool PreferMultiplies_, typename OutT_, std::size_t ReadOffset_ = 0, std::size_t VecSize_, typename VecT_>
	[[nodiscard]] constexpr inline auto quaternion_from_euler_fused(EmuMath::Vector<VecSize_, VecT_>& euler_vector_)
		-> std::enable_if_t
		<
			quaternion_can_convert_from_euler_vector_fused<IsRads_, Normalise_, PreferMultiplies_, OutT_, VecSize_, VecT_, ReadOffset_, false>(),
			EmuMath::Quaternion<OutT_>
		>
	{
		return _quaternion_underlying::_make_from_euler_vector<false, IsRads_, PreferMultiplies_, Normalise_, true, false, OutT_, ReadOffset_>(euler_vector_);
	}

	template<bool IsRads_, bool Normalise_, typename OutT_, std::size_t ReadOffset_ = 0, std::size_t VecSize_, typename VecT_>
	[[nodiscard]] constexpr inline auto quaternion_from_euler_fused(EmuMath::Vector<VecSize_, VecT_>& euler_vector_)
		-> std::enable_if_t
		<
			quaternion_can_convert_from_euler_vector_fused<IsRads_, Normalise_, false, OutT_, VecSize_, VecT_, ReadOffset_, false>(),
			EmuMath::Quaternion<OutT_>
		>
	{
		return _quaternion_underlying::_make_from_euler_vector<false, IsRads_, false, Normalise_, true, false, OutT_, ReadOffset_>(euler_vector_);
	}

	template<bool IsRads_, typename OutT_, std::size_t ReadOffset_ = 0, std::size_t VecSize_, typename VecT_>
	[[nodiscard]] constexpr inline auto quaternion_from_euler_fused(EmuMath::Vector<VecSize_, VecT_>& euler_vector_)
		-> std::enable_if_t
		<
			quaternion_can_convert_from_euler_vector_fused<IsRads_, true, false, OutT_, VecSize_, VecT_, ReadOffset_, false>(),
			EmuMath::Quaternion<OutT_>
		>
	{
		return _quaternion_underlying::_make_from_euler_vector<false, IsRads_, false, true, true, false, OutT_, ReadOffset_>(euler_vector_);
	}

	template<typename OutT_, std::size_t ReadOffset_ = 0, std::size_t VecSize_, typename VecT_>
	[[nodiscard]] constexpr inline auto quaternion_from_euler_fused(EmuMath::Vector<VecSize_, VecT_>& euler_vector_)
		-> std::enable_if_t
		<
			quaternion_can_convert_from_euler_vector_fused<true, true, false, OutT_, VecSize_, VecT_, ReadOffset_, false>(),
			EmuMath::Quaternion<OutT_>
		>
	{
		return _quaternion_underlying::_make_from_euler_vector<false, true, false, true, true, false, OutT_, ReadOffset_>(euler_vector_);
	}

	/// <summary>
	/// <para> Creates a Quaternion form of the passed Euler Vector (interpreted as a 3D Vector). </para>
	/// <para> May optionally instruct the input angles to be interpreted as radians or degrees. If `IsRads_` is omitted, it will be treated as `true`. </para>
	/// <para> May optionally normalise the output Quaternion. If `Normalise_` is omitted, it will be treated as `true`. </para>
	/// <para> May optionally choose to prefer reciprocal multiplication over division. If `PreferMultiplies_` is omitted, it will be treated as `false`. </para>
	/// <para> This function will attempt to be constexpr-evaluable, which may have an effect on accuracy and/or performance. </para>
	/// </summary>
	/// <param name="euler_vector_">EmuMath Vector to be interpreted as a 3D Vector of Euler angles to convert.</param>
	/// <returns>Quaternion resulting from a conversion of the passed Euler Vector.</returns>
	template<bool IsRads_, bool Normalise_, bool PreferMultiplies_, typename OutT_, std::size_t ReadOffset_ = 0, std::size_t VecSize_, typename VecT_>
	[[nodiscard]] constexpr inline auto quaternion_from_euler_constexpr(EmuMath::Vector<VecSize_, VecT_>& euler_vector_)
		-> std::enable_if_t
		<
			quaternion_can_convert_from_euler_vector_constexpr<IsRads_, Normalise_, PreferMultiplies_, OutT_, VecSize_, VecT_, ReadOffset_, false>(),
			EmuMath::Quaternion<OutT_>
		>
	{
		return _quaternion_underlying::_make_from_euler_vector<false, IsRads_, PreferMultiplies_, Normalise_, false, true, OutT_, ReadOffset_>(euler_vector_);
	}

	template<bool IsRads_, bool Normalise_, typename OutT_, std::size_t ReadOffset_ = 0, std::size_t VecSize_, typename VecT_>
	[[nodiscard]] constexpr inline auto quaternion_from_euler_constexpr(EmuMath::Vector<VecSize_, VecT_>& euler_vector_)
		-> std::enable_if_t
		<
			quaternion_can_convert_from_euler_vector_constexpr<IsRads_, Normalise_, false, OutT_, VecSize_, VecT_, ReadOffset_, false>(),
			EmuMath::Quaternion<OutT_>
		>
	{
		return _quaternion_underlying::_make_from_euler_vector<false, IsRads_, false, Normalise_, false, true, OutT_, ReadOffset_>(euler_vector_);
	}

	template<bool IsRads_, typename OutT_, std::size_t ReadOffset_ = 0, std::size_t VecSize_, typename VecT_>
	[[nodiscard]] constexpr inline auto quaternion_from_euler_constexpr(EmuMath::Vector<VecSize_, VecT_>& euler_vector_)
		-> std::enable_if_t
		<
			quaternion_can_convert_from_euler_vector_constexpr<IsRads_, true, false, OutT_, VecSize_, VecT_, ReadOffset_, false>(),
			EmuMath::Quaternion<OutT_>
		>
	{
		return _quaternion_underlying::_make_from_euler_vector<false, IsRads_, false, true, false, true, OutT_, ReadOffset_>(euler_vector_);
	}

	template<typename OutT_, std::size_t ReadOffset_ = 0, std::size_t VecSize_, typename VecT_>
	[[nodiscard]] constexpr inline auto quaternion_from_euler_constexpr(EmuMath::Vector<VecSize_, VecT_>& euler_vector_)
		-> std::enable_if_t
		<
			quaternion_can_convert_from_euler_vector_constexpr<true, true, false, OutT_, VecSize_, VecT_, ReadOffset_, false>(),
			EmuMath::Quaternion<OutT_>
		>
	{
		return _quaternion_underlying::_make_from_euler_vector<false, true, false, true, false, true, OutT_, ReadOffset_>(euler_vector_);
	}
#pragma endregion

#pragma region FROM_EULER_RVALUE_VECTOR_CONVERSION_FUNCS
	/// <summary>
	/// <para> Creates a Quaternion form of the passed Euler Vector (interpreted as a 3D Vector). </para>
	/// <para> May optionally instruct the input angles to be interpreted as radians or degrees. If `IsRads_` is omitted, it will be treated as `true`. </para>
	/// <para> May optionally normalise the output Quaternion. If `Normalise_` is omitted, it will be treated as `true`. </para>
	/// <para> May optionally choose to prefer reciprocal multiplication over division. If `PreferMultiplies_` is omitted, it will be treated as `false`. </para>
	/// </summary>
	/// <param name="euler_vector_">EmuMath Vector to be interpreted as a 3D Vector of Euler angles to convert.</param>
	/// <returns>Quaternion resulting from a conversion of the passed Euler Vector.</returns>
	template<bool IsRads_, bool Normalise_, bool PreferMultiplies_, typename OutT_, std::size_t ReadOffset_ = 0, std::size_t VecSize_, typename VecT_>
	[[nodiscard]] constexpr inline auto quaternion_from_euler(EmuMath::Vector<VecSize_, VecT_>&& euler_vector_)
		-> std::enable_if_t
		<
			quaternion_can_convert_from_rvalue_euler_vector<IsRads_, Normalise_, PreferMultiplies_, OutT_, VecSize_, VecT_, ReadOffset_, false>(),
			EmuMath::Quaternion<OutT_>
		>
	{
		using vector_type = EmuMath::Vector<VecSize_, VecT_>;
		return _quaternion_underlying::_make_from_euler_vector<false, IsRads_, PreferMultiplies_, Normalise_, false, false, OutT_, ReadOffset_>
		(
			std::forward<vector_type>(euler_vector_)
		);
	}

	template<bool IsRads_, bool Normalise_, typename OutT_, std::size_t ReadOffset_ = 0, std::size_t VecSize_, typename VecT_>
	[[nodiscard]] constexpr inline auto quaternion_from_euler(EmuMath::Vector<VecSize_, VecT_>&& euler_vector_)
		-> std::enable_if_t
		<
			quaternion_can_convert_from_rvalue_euler_vector<IsRads_, Normalise_, false, OutT_, VecSize_, VecT_, ReadOffset_, false>(),
			EmuMath::Quaternion<OutT_>
		>
	{
		using vector_type = EmuMath::Vector<VecSize_, VecT_>;
		return _quaternion_underlying::_make_from_euler_vector<false, IsRads_, false, Normalise_, false, false, OutT_, ReadOffset_>
		(
			std::forward<vector_type>(euler_vector_)
		);
	}

	template<bool IsRads_, typename OutT_, std::size_t ReadOffset_ = 0, std::size_t VecSize_, typename VecT_>
	[[nodiscard]] constexpr inline auto quaternion_from_euler(EmuMath::Vector<VecSize_, VecT_>&& euler_vector_)
		-> std::enable_if_t
		<
			quaternion_can_convert_from_rvalue_euler_vector<IsRads_, true, false, OutT_, VecSize_, VecT_, ReadOffset_, false>(),
			EmuMath::Quaternion<OutT_>
		>
	{
		using vector_type = EmuMath::Vector<VecSize_, VecT_>;
		return _quaternion_underlying::_make_from_euler_vector<false, IsRads_, false, true, false, false, OutT_, ReadOffset_>
		(
			std::forward<vector_type>(euler_vector_)
		);
	}

	template<typename OutT_, std::size_t ReadOffset_ = 0, std::size_t VecSize_, typename VecT_>
	[[nodiscard]] constexpr inline auto quaternion_from_euler(EmuMath::Vector<VecSize_, VecT_>&& euler_vector_)
		-> std::enable_if_t
		<
			quaternion_can_convert_from_rvalue_euler_vector<true, true, false, OutT_, VecSize_, VecT_, ReadOffset_, false>(),
			EmuMath::Quaternion<OutT_>
		>
	{
		using vector_type = EmuMath::Vector<VecSize_, VecT_>;
		return _quaternion_underlying::_make_from_euler_vector<false, true, false, true, false, false, OutT_, ReadOffset_>
		(
			std::forward<vector_type>(euler_vector_)
		);
	}

	/// <summary>
	/// <para> Creates a Quaternion form of the passed Euler Vector (interpreted as a 3D Vector). </para>
	/// <para> May optionally instruct the input angles to be interpreted as radians or degrees. If `IsRads_` is omitted, it will be treated as `true`. </para>
	/// <para> May optionally normalise the output Quaternion. If `Normalise_` is omitted, it will be treated as `true`. </para>
	/// <para> May optionally choose to prefer reciprocal multiplication over division. If `PreferMultiplies_` is omitted, it will be treated as `false`. </para>
	/// <para>
	///		This function will attempt to take advantage of fused instructions (such as FMADD) if possible, or emulate them otherwise. 
	///		Use of such instructions may improve accuracy and/or performance.
	/// </para>
	/// </summary>
	/// <param name="euler_vector_">EmuMath Vector to be interpreted as a 3D Vector of Euler angles to convert.</param>
	/// <returns>Quaternion resulting from a conversion of the passed Euler Vector.</returns>
	template<bool IsRads_, bool Normalise_, bool PreferMultiplies_, typename OutT_, std::size_t ReadOffset_ = 0, std::size_t VecSize_, typename VecT_>
	[[nodiscard]] constexpr inline auto quaternion_from_euler_fused(EmuMath::Vector<VecSize_, VecT_>&& euler_vector_)
		-> std::enable_if_t
		<
			quaternion_can_convert_from_rvalue_euler_vector_fused<IsRads_, Normalise_, PreferMultiplies_, OutT_, VecSize_, VecT_, ReadOffset_, false>(),
			EmuMath::Quaternion<OutT_>
		>
	{
		using vector_type = EmuMath::Vector<VecSize_, VecT_>;
		return _quaternion_underlying::_make_from_euler_vector<false, IsRads_, PreferMultiplies_, Normalise_, true, false, OutT_, ReadOffset_>
		(
			std::forward<vector_type>(euler_vector_)
		);
	}

	template<bool IsRads_, bool Normalise_, typename OutT_, std::size_t ReadOffset_ = 0, std::size_t VecSize_, typename VecT_>
	[[nodiscard]] constexpr inline auto quaternion_from_euler_fused(EmuMath::Vector<VecSize_, VecT_>&& euler_vector_)
		-> std::enable_if_t
		<
			quaternion_can_convert_from_rvalue_euler_vector_fused<IsRads_, Normalise_, false, OutT_, VecSize_, VecT_, ReadOffset_, false>(),
			EmuMath::Quaternion<OutT_>
		>
	{
		using vector_type = EmuMath::Vector<VecSize_, VecT_>;
		return _quaternion_underlying::_make_from_euler_vector<false, IsRads_, false, Normalise_, true, false, OutT_, ReadOffset_>
		(
			std::forward<vector_type>(euler_vector_)
		);
	}

	template<bool IsRads_, typename OutT_, std::size_t ReadOffset_ = 0, std::size_t VecSize_, typename VecT_>
	[[nodiscard]] constexpr inline auto quaternion_from_euler_fused(EmuMath::Vector<VecSize_, VecT_>&& euler_vector_)
		-> std::enable_if_t
		<
			quaternion_can_convert_from_rvalue_euler_vector_fused<IsRads_, true, false, OutT_, VecSize_, VecT_, ReadOffset_, false>(),
			EmuMath::Quaternion<OutT_>
		>
	{
		using vector_type = EmuMath::Vector<VecSize_, VecT_>;
		return _quaternion_underlying::_make_from_euler_vector<false, IsRads_, false, true, true, false, OutT_, ReadOffset_>
		(
			std::forward<vector_type>(euler_vector_)
		);
	}

	template<typename OutT_, std::size_t ReadOffset_ = 0, std::size_t VecSize_, typename VecT_>
	[[nodiscard]] constexpr inline auto quaternion_from_euler_fused(EmuMath::Vector<VecSize_, VecT_>&& euler_vector_)
		-> std::enable_if_t
		<
			quaternion_can_convert_from_rvalue_euler_vector_fused<true, true, false, OutT_, VecSize_, VecT_, ReadOffset_, false>(),
			EmuMath::Quaternion<OutT_>
		>
	{
		using vector_type = EmuMath::Vector<VecSize_, VecT_>;
		return _quaternion_underlying::_make_from_euler_vector<false, true, false, true, true, false, OutT_, ReadOffset_>
		(
			std::forward<vector_type>(euler_vector_)
		);
	}

	/// <summary>
	/// <para> Creates a Quaternion form of the passed Euler Vector (interpreted as a 3D Vector). </para>
	/// <para> May optionally instruct the input angles to be interpreted as radians or degrees. If `IsRads_` is omitted, it will be treated as `true`. </para>
	/// <para> May optionally normalise the output Quaternion. If `Normalise_` is omitted, it will be treated as `true`. </para>
	/// <para> May optionally choose to prefer reciprocal multiplication over division. If `PreferMultiplies_` is omitted, it will be treated as `false`. </para>
	/// <para> This function will attempt to be constexpr-evaluable, which may have an effect on accuracy and/or performance. </para>
	/// </summary>
	/// <param name="euler_vector_">EmuMath Vector to be interpreted as a 3D Vector of Euler angles to convert.</param>
	/// <returns>Quaternion resulting from a conversion of the passed Euler Vector.</returns>
	template<bool IsRads_, bool Normalise_, bool PreferMultiplies_, typename OutT_, std::size_t ReadOffset_ = 0, std::size_t VecSize_, typename VecT_>
	[[nodiscard]] constexpr inline auto quaternion_from_euler_constexpr(EmuMath::Vector<VecSize_, VecT_>&& euler_vector_)
		-> std::enable_if_t
		<
			quaternion_can_convert_from_rvalue_euler_vector_constexpr<IsRads_, Normalise_, PreferMultiplies_, OutT_, VecSize_, VecT_, ReadOffset_, false>(),
			EmuMath::Quaternion<OutT_>
		>
	{
		using vector_type = EmuMath::Vector<VecSize_, VecT_>;
		return _quaternion_underlying::_make_from_euler_vector<false, IsRads_, PreferMultiplies_, Normalise_, false, true, OutT_, ReadOffset_>
		(
			std::forward<vector_type>(euler_vector_)
		);
	}

	template<bool IsRads_, bool Normalise_, typename OutT_, std::size_t ReadOffset_ = 0, std::size_t VecSize_, typename VecT_>
	[[nodiscard]] constexpr inline auto quaternion_from_euler_constexpr(EmuMath::Vector<VecSize_, VecT_>&& euler_vector_)
		-> std::enable_if_t
		<
			quaternion_can_convert_from_rvalue_euler_vector_constexpr<IsRads_, Normalise_, false, OutT_, VecSize_, VecT_, ReadOffset_, false>(),
			EmuMath::Quaternion<OutT_>
		>
	{
		using vector_type = EmuMath::Vector<VecSize_, VecT_>;
		return _quaternion_underlying::_make_from_euler_vector<false, IsRads_, false, Normalise_, false, true, OutT_, ReadOffset_>
		(
			std::forward<vector_type>(euler_vector_)
		);
	}

	template<bool IsRads_, typename OutT_, std::size_t ReadOffset_ = 0, std::size_t VecSize_, typename VecT_>
	[[nodiscard]] constexpr inline auto quaternion_from_euler_constexpr(EmuMath::Vector<VecSize_, VecT_>&& euler_vector_)
		-> std::enable_if_t
		<
			quaternion_can_convert_from_rvalue_euler_vector_constexpr<IsRads_, true, false, OutT_, VecSize_, VecT_, ReadOffset_, false>(),
			EmuMath::Quaternion<OutT_>
		>
	{
		using vector_type = EmuMath::Vector<VecSize_, VecT_>;
		return _quaternion_underlying::_make_from_euler_vector<false, IsRads_, false, true, false, true, OutT_, ReadOffset_>
		(
			std::forward<vector_type>(euler_vector_)
		);
	}

	template<typename OutT_, std::size_t ReadOffset_ = 0, std::size_t VecSize_, typename VecT_>
	[[nodiscard]] constexpr inline auto quaternion_from_euler_constexpr(EmuMath::Vector<VecSize_, VecT_>&& euler_vector_)
		-> std::enable_if_t
		<
			quaternion_can_convert_from_rvalue_euler_vector_constexpr<true, true, false, OutT_, VecSize_, VecT_, ReadOffset_, false>(),
			EmuMath::Quaternion<OutT_>
		>
	{
		using vector_type = EmuMath::Vector<VecSize_, VecT_>;
		return _quaternion_underlying::_make_from_euler_vector<false, true, false, true, false, true, OutT_, ReadOffset_>
		(
			std::forward<vector_type>(euler_vector_)
		);
	}
#pragma endregion
}

#endif
