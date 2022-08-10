#ifndef EMU_MATH_QUATERNION_UNDERLYING_CONVERSIONS_TO_EULER
#define EMU_MATH_QUATERNION_UNDERLYING_CONVERSIONS_TO_EULER 1

#include "../_quaternion_tmp.h"
#include "../_quaternion_underlying_get.h"
#include "../../../../Vector.h"

namespace EmuMath::Helpers::_quaternion_underlying
{
#pragma region VALIDITY_CHECKS
	template<bool Fused_, typename OutT_, bool IsConstexpr_, bool OutRads_, class X_, class Y_, class Z_, class W_, typename Epsilon_, bool StaticAssert_>
	[[nodiscard]] constexpr inline bool _valid_convert_to_euler_args()
	{
		using x_uq = typename EmuCore::TMP::remove_ref_cv<X_>::type;
		using y_uq = typename EmuCore::TMP::remove_ref_cv<Y_>::type;
		using z_uq = typename EmuCore::TMP::remove_ref_cv<Z_>::type;
		using w_uq = typename EmuCore::TMP::remove_ref_cv<W_>::type;
		using epsilon_uq = typename EmuCore::TMP::remove_ref_cv<Epsilon_>::type;
		using out_preferred_fp = typename EmuMath::Vector<3, OutT_>::preferred_floating_point;
		using calc_fp = typename EmuCore::TMP::largest_floating_point<OutT_, x_uq, y_uq, z_uq, w_uq, epsilon_uq, out_preferred_fp>::type;

		using mul_func = EmuCore::do_multiply<calc_fp, calc_fp>;
		using add_func = EmuCore::do_add<calc_fp, calc_fp>;
		using sub_func = EmuCore::do_subtract<calc_fp, calc_fp>;
		using asin_func = typename std::conditional<IsConstexpr_, EmuCore::do_asin_constexpr<calc_fp>, EmuCore::do_asin<calc_fp>>::type;
		using atan2_func = typename std::conditional<IsConstexpr_, EmuCore::do_atan2_constexpr<calc_fp>, EmuCore::do_atan2<calc_fp>>::type;
		using cmp_greater_func = EmuCore::do_cmp_greater<calc_fp, calc_fp>;
		using abs_func = EmuCore::do_abs<calc_fp>;

		if constexpr (!std::is_invocable_r_v<calc_fp, mul_func, calc_fp, calc_fp>)
		{
			static_assert(!StaticAssert_, "Unable to convert an EmuMath Quaternion to a Euler Vector as the determined multiplication function cannot be invoked with two arguments of the determined calculation type while also returning said type (or a type implicitly convertible).");
			return false;
		}
		else if constexpr (!std::is_invocable_r_v<calc_fp, add_func, calc_fp, calc_fp>)
		{
			static_assert(!StaticAssert_, "Unable to convert an EmuMath Quaternion to a Euler Vector as the determined addition function cannot be invoked with two arguments of the determined calculation type while also returning said type (or a type implicitly convertible).");
			return false;
		}
		else if constexpr (!std::is_invocable_r_v<calc_fp, sub_func, calc_fp, calc_fp>)
		{
			static_assert(!StaticAssert_, "Unable to convert an EmuMath Quaternion to a Euler Vector as the determined subtraction function cannot be invoked with two arguments of the determined calculation type while also returning said type (or a type implicitly convertible).");
			return false;
		}
		else if constexpr (!std::is_invocable_r_v<calc_fp, asin_func, calc_fp>)
		{
			static_assert(!StaticAssert_, "Unable to convert an EmuMath Quaternion to a Euler Vector as the determined sin function cannot be invoked with one argument of the determined calculation type while also returning said type (or a type implicitly convertible).");
			return false;
		}
		else if constexpr (!std::is_invocable_r_v<calc_fp, atan2_func, calc_fp, calc_fp>)
		{
			static_assert(!StaticAssert_, "Unable to convert an EmuMath Quaternion to a Euler Vector as the determined atan2 function cannot be invoked with two arguments of the determined calculation type while also returning said type (or a type implicitly convertible).");
			return false;
		}
		else if constexpr (!std::is_invocable_r_v<bool, cmp_greater_func, calc_fp, calc_fp>)
		{
			static_assert(!StaticAssert_, "Unable to convert an EmuMath Quaternion to a Euler Vector as the determined greater-than comparison (>) function cannot be invoked with two arguments of the determined calculation type while also returning a bool (or a type implicitly convertible).");
			return false;
		}
		else
		{
			if constexpr (Fused_)
			{
				using fmadd_func = EmuCore::do_fmadd<calc_fp, calc_fp, calc_fp>;
				using fmsub_func = EmuCore::do_fmsub<calc_fp, calc_fp, calc_fp>;
				if constexpr (!std::is_invocable_r_v<calc_fp, fmadd_func, calc_fp, calc_fp, calc_fp>)
				{
					static_assert(!StaticAssert_, "Unable to convert an EmuMath Quaternion to a Euler Vector (WITH fused operations) as the determined fused multiply-add function cannot be invoked with three arguments of the determined calculation type while also returning said type (or a type implicitly convertible).");
					return false;
				}
				else if constexpr (!std::is_invocable_r_v<calc_fp, fmsub_func, calc_fp, calc_fp, calc_fp>)
				{
					static_assert(!StaticAssert_, "Unable to convert an EmuMath Quaternion to a Euler Vector (WITH fused operations) as the determined fused multiply-subtract function cannot be invoked with three arguments of the determined calculation type while also returning said type (or a type implicitly convertible).");
					return false;
				}
			}

			if constexpr (!std::is_constructible_v<EmuMath::Vector<3, OutT_>, calc_fp&&, calc_fp&&, calc_fp&&>)
			{
				static_assert(!StaticAssert_, "Unable to convert an EmuMath Quaternion to a Euler Vector as the output Vector type cannot be constructed from 3 rvalues of the determined calculation type, representing X, Y, Z respectively.");
				return false;
			}
			else
			{
				return true;
			}
		}
	}

	template<bool Fused_, typename OutT_, bool IsConstexpr_, bool OutRads_, class X_, class Y_, class Z_, class W_, bool StaticAssert_>
	[[nodiscard]] constexpr inline bool _valid_convert_to_euler_args()
	{
		using x_uq = typename EmuCore::TMP::remove_ref_cv<X_>::type;
		using y_uq = typename EmuCore::TMP::remove_ref_cv<Y_>::type;
		using z_uq = typename EmuCore::TMP::remove_ref_cv<Z_>::type;
		using w_uq = typename EmuCore::TMP::remove_ref_cv<W_>::type;
		using out_preferred_fp = typename EmuMath::Vector<3, OutT_>::preferred_floating_point;
		using calc_fp = typename EmuCore::TMP::largest_floating_point<OutT_, x_uq, y_uq, z_uq, w_uq, out_preferred_fp>::type;
		using epsilon_type = decltype(EmuCore::epsilon<calc_fp>::get());
		return _valid_convert_to_euler_args<Fused_, OutT_, IsConstexpr_, OutRads_, X_, Y_, Z_, W_, epsilon_type, StaticAssert_>();
	}

	template<bool Fused_, typename OutT_, bool IsConstexpr_, bool OutRads_, typename T_, typename Epsilon_, bool StaticAssert_>
	[[nodiscard]] constexpr inline bool _valid_convert_to_euler_args()
	{
		using quat_ref = const EmuMath::Quaternion<T_>&;
		return _valid_convert_to_euler_args
		<
			Fused_,
			OutT_,
			IsConstexpr_,
			OutRads_,
			decltype(_get_x(std::declval<quat_ref>())),
			decltype(_get_y(std::declval<quat_ref>())),
			decltype(_get_z(std::declval<quat_ref>())),
			decltype(_get_w(std::declval<quat_ref>())),
			Epsilon_,
			StaticAssert_
		>();
	}

	template<bool Fused_, typename OutT_, bool IsConstexpr_, bool OutRads_, typename T_, bool StaticAssert_>
	[[nodiscard]] constexpr inline bool _valid_convert_to_euler_args()
	{
		using quat_ref = const EmuMath::Quaternion<T_>&;
		return _valid_convert_to_euler_args
		<
			Fused_,
			OutT_,
			IsConstexpr_,
			OutRads_,
			decltype(_get_x(std::declval<quat_ref>())),
			decltype(_get_y(std::declval<quat_ref>())),
			decltype(_get_z(std::declval<quat_ref>())),
			decltype(_get_w(std::declval<quat_ref>())),
			StaticAssert_
		>();
	}
#pragma endregion

#pragma region TO_EULER_FUNCS
	template<bool Fused_, typename OutT_, bool IsConstexpr_, bool OutRads_, class X_, class Y_, class Z_, class W_, typename Epsilon_>
	[[nodiscard]] constexpr inline EmuMath::Vector<3, OutT_> _convert_to_euler_vector(X_&& x_, Y_&& y_, Z_&& z_, W_&& w_, Epsilon_&& epsilon_)
	{
		// Prepare type aliases
		using x_uq = typename EmuCore::TMP::remove_ref_cv<X_>::type;
		using y_uq = typename EmuCore::TMP::remove_ref_cv<Y_>::type;
		using z_uq = typename EmuCore::TMP::remove_ref_cv<Z_>::type;
		using w_uq = typename EmuCore::TMP::remove_ref_cv<W_>::type;
		using epsilon_uq = typename EmuCore::TMP::remove_ref_cv<Epsilon_>::type;
		using out_preferred_fp = typename EmuMath::Vector<3, OutT_>::preferred_floating_point;
		using calc_fp = typename EmuCore::TMP::largest_floating_point<OutT_, x_uq, y_uq, z_uq, w_uq, epsilon_uq, out_preferred_fp>::type;

		// Prepare functor aliases
		using mul_func = EmuCore::do_multiply<calc_fp, calc_fp>;
		using asin_func = typename std::conditional<IsConstexpr_, EmuCore::do_asin_constexpr<calc_fp>, EmuCore::do_asin<calc_fp>>::type;
		using atan2_func = typename std::conditional<IsConstexpr_, EmuCore::do_atan2_constexpr<calc_fp>, EmuCore::do_atan2<calc_fp>>::type;
		using sub_func = EmuCore::do_subtract<calc_fp, calc_fp>;
		using add_func = EmuCore::do_add<calc_fp, calc_fp>;
		using cmp_greater_func = EmuCore::do_cmp_greater<calc_fp, calc_fp>;
		using abs_func = EmuCore::do_abs<calc_fp>;
		
		// Common values
		calc_fp two = calc_fp(2);
		calc_fp x = static_cast<calc_fp>(std::forward<X_>(x_));
		calc_fp y = static_cast<calc_fp>(std::forward<Y_>(y_));
		calc_fp z = static_cast<calc_fp>(std::forward<Z_>(z_));
		calc_fp w = static_cast<calc_fp>(std::forward<W_>(w_));	

		// Y
		calc_fp out_y = calc_fp();
		if constexpr (Fused_)
		{
			using fmsub_func = EmuCore::do_fmsub<calc_fp, calc_fp, calc_fp>;
			out_y = fmsub_func()(w, y, mul_func()(x, z));
			out_y = mul_func()(two, out_y);
		}
		else
		{
			out_y = sub_func()(mul_func()(w, y), mul_func()(x, z));
			out_y = mul_func()(two, out_y);
		}
		out_y = asin_func()(out_y);
		
		// Calculation varies depending on the yaw's magnitude's proximity to pi/2
		if (cmp_greater_func()(sub_func()(EmuCore::Pi::HALF_PI<calc_fp>, abs_func()(out_y)), static_cast<calc_fp>(std::forward<Epsilon_>(epsilon_))))
		{
			// Common values to use
			calc_fp sqx = mul_func()(x, x);
			calc_fp sqy = mul_func()(y, y);
			calc_fp sqz = mul_func()(z, z);
			calc_fp sqw = mul_func()(w, w);
		
			// Z
			//calc_fp out_z = atan2_func()
			//(
			//	mul_func()(two, add_func()(mul_func()(x, y), mul_func()(w, z))),
			//	add_func()(sub_func()(sub_func()(sqx, sqy), sqz), sqw)
			//);
			//
			//// X
			//calc_fp out_x = atan2_func()
			//(
			//	mul_func()(two, add_func()(mul_func()(w, x), mul_func()(y, z))),
			//	add_func()(sub_func()(sub_func()(sqw, sqx), sqy), sqz)
			//);

			// Set x and z to the `x` arguments for atan2
			// --- x = sqw - sqx - sqy + sqz
			// --- z = sqx - sqy - sqz + sqw
			calc_fp out_x = add_func()(sub_func()(sub_func()(sqw, sqx), sqy), sqz);
			calc_fp out_z = add_func()(sub_func()(sub_func()(sqx, sqy), sqz), sqw);

			if constexpr (Fused_)
			{
				using fmadd_func = EmuCore::do_fmadd<calc_fp, calc_fp, calc_fp>;
				out_x = atan2_func()
				(
					mul_func()(two, fmadd_func()(w, x, mul_func()(y, z))),
					out_x
				);
				out_z = atan2_func()
				(
					mul_func()(two, fmadd_func()(x, y, mul_func()(w, z))),
					out_z
				);
			}
			else
			{
				out_x = atan2_func()
				(
					mul_func()(two, add_func()(mul_func()(w, x), mul_func()(y, z))),
					out_x
				);
				out_z = atan2_func()
				(
					mul_func()(two, add_func()(mul_func()(x, y), mul_func()(w, z))),
					out_z
				);
			}

			// Convert to degrees if needed
			if constexpr (!OutRads_)
			{
				out_x = mul_func()(out_x, EmuCore::Pi::HUNDRED80_DIV_PI<calc_fp>);
				out_y = mul_func()(out_y, EmuCore::Pi::HUNDRED80_DIV_PI<calc_fp>);
				out_z = mul_func()(out_z, EmuCore::Pi::HUNDRED80_DIV_PI<calc_fp>);
			}
		
			return EmuMath::Vector<3, OutT_>(std::move(out_x), std::move(out_y), std::move(out_z));
		}
		else
		{
			// Z
			//calc_fp out_z = mul_func()(two, mul_func()(y, z));
			//out_z = atan2_func()
			//(
			//	sub_func()(out_z, mul_func()(two, mul_func()(x, w))),
			//	add_func()(mul_func()(two, mul_func()(x, z)), mul_func()(two, mul_func()(y, w)))
			//);
			//
			//// Negate Z (based on pi instead of 0) if yaw is negative
			//bool neg_yaw = y < 0;
			//out_z = add_func()
			//(
			//	mul_func()(calc_fp(neg_yaw), sub_func()(EmuCore::Pi::PI<calc_fp>, out_z)),
			//	mul_func()(calc_fp(!neg_yaw), neg_yaw)
			//);

			// Initially set z to y*z, which is part of forming the atan2 `y` arg (2 * y * z) - (2 * x * w)
			calc_fp out_z = mul_func()(y, z);
			if constexpr (Fused_)
			{
				using fmadd_func = EmuCore::do_fmadd<calc_fp, calc_fp, calc_fp>;
				using fmsub_func = EmuCore::do_fmsub<calc_fp, calc_fp, calc_fp>;
				out_z = fmsub_func()(two, out_z, mul_func()(two, mul_func()(x, w)));
				out_z = atan2_func()
				(
					out_z,
					fmadd_func()(two, mul_func()(x, z), mul_func()(two, mul_func()(y, w))) // `x` arg = (2 * x * z) + (2 * y * w)
				);

				// Negate Z based on pi if yaw < 0
				bool neg_yaw = cmp_greater_func()(calc_fp(0), y);
				out_z = fmadd_func()
				(
					calc_fp(neg_yaw),
					sub_func()(EmuCore::Pi::PI<calc_fp>, out_z),
					mul_func()(calc_fp(!neg_yaw), out_z)
				);
			}
			else
			{
				out_z = sub_func()(mul_func()(two, out_z), mul_func()(two, mul_func()(x, w)));
				out_z = atan2_func()
				(
					out_z,
					add_func()(mul_func()(two, mul_func()(x, z)), mul_func()(two, mul_func()(y, w)))
				);

				// Negate Z based on pi if yaw < 0
				bool neg_yaw = cmp_greater_func()(calc_fp(0), y);
				out_z = add_func()
				(
					mul_func()(calc_fp(neg_yaw), sub_func()(EmuCore::Pi::PI<calc_fp>, out_z)),
					mul_func()(calc_fp(!neg_yaw), out_z)
				);
			}
		
			// Convert to degrees if needed
			if constexpr (!OutRads_)
			{
				out_y = mul_func()(out_y, EmuCore::Pi::HUNDRED80_DIV_PI<calc_fp>);
				out_z = mul_func()(out_z, EmuCore::Pi::HUNDRED80_DIV_PI<calc_fp>);
			}
		
			return EmuMath::Vector<3, OutT_>(calc_fp(0), std::move(out_y), std::move(out_z));
		}
	}

	template<bool Fused_, typename OutT_, bool IsConstexpr_, bool OutRads_, class X_, class Y_, class Z_, class W_>
	[[nodiscard]] constexpr inline EmuMath::Vector<3, OutT_> _convert_to_euler_vector(X_&& x_, Y_&& y_, Z_&& z_, W_&& w_)
	{
		using x_uq = typename EmuCore::TMP::remove_ref_cv<X_>::type;
		using y_uq = typename EmuCore::TMP::remove_ref_cv<Y_>::type;
		using z_uq = typename EmuCore::TMP::remove_ref_cv<Z_>::type;
		using w_uq = typename EmuCore::TMP::remove_ref_cv<W_>::type;
		using out_preferred_fp = typename EmuMath::Vector<3, OutT_>::preferred_floating_point;
		using calc_fp = typename EmuCore::TMP::largest_floating_point<OutT_, x_uq, y_uq, z_uq, w_uq, out_preferred_fp>::type;
		return _convert_to_euler_vector<Fused_, OutT_, IsConstexpr_, OutRads_>
		(
			std::forward<X_>(x_),
			std::forward<Y_>(y_),
			std::forward<Z_>(z_),
			std::forward<W_>(w_),
			EmuCore::epsilon<calc_fp>::get()
		);
	}

	template<bool Fused_, typename OutT_, bool IsConstexpr_, bool OutRads_, typename Epsilon_, typename T_>
	[[nodiscard]] constexpr inline EmuMath::Vector<3, OutT_> _convert_to_euler_vector(const EmuMath::Quaternion<T_>& quaternion_, Epsilon_&& epsilon_)
	{
		return _convert_to_euler_vector<Fused_, OutT_, IsConstexpr_, OutRads_>
		(
			_get_x(quaternion_),
			_get_y(quaternion_),
			_get_z(quaternion_),
			_get_w(quaternion_),
			std::forward<Epsilon_>(epsilon_)
		);
	}

	template<bool Fused_, typename OutT_, bool IsConstexpr_, bool OutRads_, typename T_>
	[[nodiscard]] constexpr inline EmuMath::Vector<3, OutT_> _convert_to_euler_vector(const EmuMath::Quaternion<T_>& quaternion_)
	{
		using x_uq = typename EmuCore::TMP::remove_ref_cv<decltype(_get_x(quaternion_))>::type;
		using y_uq = typename EmuCore::TMP::remove_ref_cv<decltype(_get_y(quaternion_))>::type;
		using z_uq = typename EmuCore::TMP::remove_ref_cv<decltype(_get_z(quaternion_))>::type;
		using w_uq = typename EmuCore::TMP::remove_ref_cv<decltype(_get_w(quaternion_))>::type;
		using out_preferred_fp = typename EmuMath::Vector<3, OutT_>::preferred_floating_point;
		using calc_fp = typename EmuCore::TMP::largest_floating_point<OutT_, x_uq, y_uq, z_uq, w_uq, out_preferred_fp>::type;
		return _convert_to_euler_vector<Fused_, OutT_, IsConstexpr_, OutRads_>
		(
			_get_x(quaternion_),
			_get_y(quaternion_),
			_get_z(quaternion_),
			_get_w(quaternion_),
			EmuCore::epsilon<calc_fp>::get()
		);
	}
#pragma endregion
}

#endif
