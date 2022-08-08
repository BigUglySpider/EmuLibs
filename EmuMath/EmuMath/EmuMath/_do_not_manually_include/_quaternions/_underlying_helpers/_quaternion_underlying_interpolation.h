#ifndef EMU_MATH_QUATERNION_UNDERLYING_INTERPOLATION_H_INC_
#define EMU_MATH_QUATERNION_UNDERLYING_INTERPOLATION_H_INC_ 1

#include "_quaternion_tmp.h"
#include "_quaternion_underlying_get.h"

namespace EmuMath::Helpers::_quaternion_underlying
{
#pragma region VALIDITY_CHECKS
	template
	<
		bool VectorOut_, bool Fused_, typename OutT_, typename AX_, typename AY_, typename AZ_, typename AW_,
		typename BX_, typename BY_, typename BZ_, typename BW_, class ArgT_, bool StaticAssert_
	>
	[[nodiscard]] static constexpr inline bool _valid_lerp_args()
	{
		using out_quaternion = EmuMath::Quaternion<OutT_>;
		using ax_uq = typename EmuCore::TMP::remove_ref_cv<AX_>::type;
		using ay_uq = typename EmuCore::TMP::remove_ref_cv<AY_>::type;
		using az_uq = typename EmuCore::TMP::remove_ref_cv<AZ_>::type;
		using aw_uq = typename EmuCore::TMP::remove_ref_cv<AW_>::type;
		using bx_uq = typename EmuCore::TMP::remove_ref_cv<BX_>::type;
		using by_uq = typename EmuCore::TMP::remove_ref_cv<BY_>::type;
		using bz_uq = typename EmuCore::TMP::remove_ref_cv<BZ_>::type;
		using bw_uq = typename EmuCore::TMP::remove_ref_cv<BW_>::type;
		using t_uq = typename EmuCore::TMP::remove_ref_cv<ArgT_>::type;
		using out_t_uq = typename EmuCore::TMP::remove_ref_cv<OutT_>::type;
		using out_fp = typename out_quaternion::preferred_floating_point;
		using t_fp_arg = typename std::conditional<EmuMath::TMP::is_emu_vector_v<t_uq>, out_fp, t_uq>::type; // Don't use ArgT_ if non-scalar
		using calc_fp = typename EmuCore::TMP::largest_floating_point
		<
			ax_uq, ay_uq, az_uq, aw_uq, bx_uq, by_uq, bz_uq, bw_uq, t_fp_arg, out_t_uq, out_fp
		>::type;

		if constexpr (!EmuCore::TMP::are_all_static_castable_v<calc_fp, AX_&&, AY_&&, AZ_&&, AW_&&>)
		{
			static_assert(!StaticAssert_, "Unable to Lerp two EmuMath Quaternions as at least one index of Quaternion A could not be converted to the determined calculation type.");
			return false;
		}
		else
		{
			if constexpr (!EmuCore::TMP::are_all_static_castable_v<calc_fp, BX_&&, BY_&&, BZ_&&, BW_&&>)
			{
				static_assert(!StaticAssert_, "Unable to Lerp two EmuMath Quaternions as at least one index of Quaternion B could not be converted to the determined calculation type.");
				return false;
			}
			else
			{
				constexpr bool t_valid = 
				(
					_valid_get_generic_quaternion_arg<calc_fp, 0, ArgT_, StaticAssert_>() &&
					_valid_get_generic_quaternion_arg<calc_fp, 1, ArgT_, StaticAssert_>() &&
					_valid_get_generic_quaternion_arg<calc_fp, 2, ArgT_, StaticAssert_>() &&
					_valid_get_generic_quaternion_arg<calc_fp, 3, ArgT_, StaticAssert_>()
				);
				if constexpr (!t_valid)
				{
					return false; // static_assert handled by _valid_get_generic_arg calls in finding t_valid
				}
				else
				{
					using lerp_func = typename std::conditional<Fused_, EmuCore::do_fused_lerp<calc_fp, calc_fp, calc_fp>, EmuCore::do_lerp<calc_fp, calc_fp, calc_fp>>::type;
					using lerp_result = typename std::invoke_result<lerp_func, calc_fp, calc_fp, calc_fp>::type;
					using out_type = typename std::conditional<VectorOut_, typename out_quaternion::vector_type, out_quaternion>::type;
					if constexpr (!std::is_constructible_v<out_type, lerp_result, lerp_result, lerp_result, lerp_result>)
					{
						static_assert(!StaticAssert_, "Unable to Lerp two EmuMath Quaternions as the output Quaternion could not be constructed from the linear interpolation results for all 4 components.");
						return false;
					}
					else
					{
						return true;
					}
				}
			}
		}
	}

	template<bool VectorOut_, bool Fused_, typename OutT_, typename AT_, typename BT_, typename T_, bool StaticAssert_>
	[[nodiscard]] constexpr inline bool _valid_lerp_args()
	{
		using a = const EmuMath::Quaternion<AT_>&;
		using b = const EmuMath::Quaternion<BT_>&;
		using ax = decltype(_get_x(std::declval<a>()));
		using ay = decltype(_get_y(std::declval<a>()));
		using az = decltype(_get_z(std::declval<a>()));
		using aw = decltype(_get_w(std::declval<a>()));
		using bx = decltype(_get_x(std::declval<b>()));
		using by = decltype(_get_y(std::declval<b>()));
		using bz = decltype(_get_z(std::declval<b>()));
		using bw = decltype(_get_w(std::declval<b>()));
		using forward_t = typename EmuCore::TMP::forward_result<T_>::type;
		return _valid_lerp_args<VectorOut_, Fused_, OutT_, ax, ay, az, aw, bx, by, bz, bw, forward_t, StaticAssert_>();
	}

	template
	<
		bool VectorOut_, bool Fused_, bool IsConstexpr_, typename OutT_, typename AX_, typename AY_, typename AZ_, typename AW_,
		typename BX_, typename BY_, typename BZ_, typename BW_, class ArgT_, bool StaticAssert_
	>
	[[nodiscard]] constexpr inline bool _valid_slerp_args()
	{
		using out_quaternion = EmuMath::Quaternion<OutT_>;
		using ax_uq = typename EmuCore::TMP::remove_ref_cv<AX_>::type;
		using ay_uq = typename EmuCore::TMP::remove_ref_cv<AY_>::type;
		using az_uq = typename EmuCore::TMP::remove_ref_cv<AZ_>::type;
		using aw_uq = typename EmuCore::TMP::remove_ref_cv<AW_>::type;
		using bx_uq = typename EmuCore::TMP::remove_ref_cv<BX_>::type;
		using by_uq = typename EmuCore::TMP::remove_ref_cv<BY_>::type;
		using bz_uq = typename EmuCore::TMP::remove_ref_cv<BZ_>::type;
		using bw_uq = typename EmuCore::TMP::remove_ref_cv<BW_>::type;
		using t_uq = typename EmuCore::TMP::remove_ref_cv<ArgT_>::type;
		using out_t_uq = typename EmuCore::TMP::remove_ref_cv<OutT_>::type;
		using out_fp = typename out_quaternion::preferred_floating_point;
		using t_fp_arg = typename std::conditional<EmuMath::TMP::is_emu_vector_v<t_uq>, out_fp, t_uq>::type; // Don't use ArgT_ if non-scalar
		using calc_fp = typename EmuCore::TMP::largest_floating_point
		<
			ax_uq, ay_uq, az_uq, aw_uq, bx_uq, by_uq, bz_uq, bw_uq, t_fp_arg, out_t_uq, out_fp
		>::type;

		constexpr bool a_valid =
		(
			EmuCore::TMP::is_static_castable_v<typename EmuCore::TMP::forward_result<AX_>::type, calc_fp> &&
			EmuCore::TMP::is_static_castable_v<typename EmuCore::TMP::forward_result<AY_>::type, calc_fp> &&
			EmuCore::TMP::is_static_castable_v<typename EmuCore::TMP::forward_result<AZ_>::type, calc_fp> &&
			EmuCore::TMP::is_static_castable_v<typename EmuCore::TMP::forward_result<AW_>::type, calc_fp>
		);
		if constexpr (!a_valid)
		{
			static_assert(!StaticAssert_, "Unable to perform spherical linear interpolation of two EmuMath Quaternions as at least one of the components of Quaternion A cannot be converted to the determined calculation type.");
			return false;
		}
		else
		{
			constexpr bool b_valid =
			(
				EmuCore::TMP::is_static_castable_v<typename EmuCore::TMP::forward_result<BX_>::type, calc_fp> &&
				EmuCore::TMP::is_static_castable_v<typename EmuCore::TMP::forward_result<BY_>::type, calc_fp> &&
				EmuCore::TMP::is_static_castable_v<typename EmuCore::TMP::forward_result<BZ_>::type, calc_fp> &&
				EmuCore::TMP::is_static_castable_v<typename EmuCore::TMP::forward_result<BW_>::type, calc_fp>
			);
			if constexpr (!b_valid)
			{
				static_assert(!StaticAssert_, "Unable to perform spherical linear interpolation of two EmuMath Quaternions as at least one of the components of Quaternion B cannot be converted to the determined calculation type.");
				return false;
			}
			else if constexpr(!EmuCore::TMP::is_static_castable_v<typename EmuCore::TMP::forward_result<ArgT_>::type, calc_fp>)
			{
				static_assert(!StaticAssert_, "Unable to perform spherical linear interpolation of two EmuMath Quaternions as the argument for T cannot be converted to the determined calculation type.");
				return false;
			}
			else
			{
				using acos_func = typename std::conditional<IsConstexpr_, EmuCore::do_acos_constexpr<calc_fp>, EmuCore::do_acos<calc_fp>>::type;
				using sin_func = typename std::conditional<IsConstexpr_, EmuCore::do_sin_constexpr<calc_fp>, EmuCore::do_sin<calc_fp>>::type;
				if constexpr (!std::is_invocable_r_v<calc_fp, acos_func, calc_fp>)
				{
					static_assert(!StaticAssert_, "Unable to perform a spherical linear interpolation of two EmuMath Quaternions as the determined acos function cannot be invoked with the determined calculation type while also returning a value that is either the determined calculation type or implicitly castable to it.");
					return false;
				}
				else if constexpr(!std::is_invocable_r_v<calc_fp, sin_func, calc_fp>)
				{
					static_assert(!StaticAssert_, "Unable to perform a spherical linear interpolation of two EmuMath Quaternions as the determined sin function cannot be invoked with the determined calculation type while also returning a value that is either the determined calculation type or implicitly castable to it.");
					return false;
				}
				else
				{
					using sub_func = EmuCore::do_subtract<calc_fp, calc_fp>;
					using mul_func = EmuCore::do_multiply<calc_fp, calc_fp>;
					using div_func = EmuCore::do_divide<calc_fp, calc_fp>;
					if constexpr (!std::is_invocable_r_v<calc_fp, sub_func, calc_fp, calc_fp>)
					{
						static_assert(!StaticAssert_, "Unable to perform a spherical linear interpolation of two EmuMath Quaternions as the determined subtraction function cannot be invoked with two arguments of the determined calculation type while also returning a value that is either the determined calculation type or implicitly castable to it.");
						return false;
					}
					else if constexpr(!std::is_invocable_r_v<calc_fp, mul_func, calc_fp, calc_fp>)
					{
						static_assert(!StaticAssert_, "Unable to perform a spherical linear interpolation of two EmuMath Quaternions as the determined multiplication function cannot be invoked with two arguments of the determined calculation type while also returning a value that is either the determined calculation type or implicitly castable to it.");
						return false;
					}
					else if constexpr (!std::is_invocable_r_v<calc_fp, div_func, calc_fp, calc_fp>)
					{
						static_assert(!StaticAssert_, "Unable to perform a spherical linear interpolation of two EmuMath Quaternions as the determined division function cannot be invoked with two arguments of the determined calculation type while also returning a value that is either the determined calculation type or implicitly castable to it.");
						return false;
					}
					else
					{
						using out_type = typename std::conditional<VectorOut_, typename out_quaternion::vector_type, out_quaternion>::type;
						if constexpr (Fused_)
						{
							using fmadd_func = EmuCore::do_fmadd<calc_fp, calc_fp, calc_fp>;
							if constexpr (!std::is_invocable_v<fmadd_func, calc_fp, calc_fp, calc_fp>)
							{
								static_assert(!StaticAssert_, "Unable to perform a spherical linear interpolation of two EmuMath Quaternions (WITH fused operations) as the determined fused multiply-add function cannot be invoked with three arguments of the determined calculation type.");
								return false;
							}
							else
							{
								using fmadd_result = typename std::invoke_result<fmadd_func, calc_fp, calc_fp, calc_fp>::type;
								if constexpr (!std::is_constructible_v<out_type, fmadd_result, fmadd_result, fmadd_result, fmadd_result>)
								{
									static_assert(!StaticAssert_, "Unable to perform a spherical linear interpolation of two EmuMath Quaternions (WITH fused operations) as the output cannot be constructed from 4 results from the determined fused multiply-add function (when said function is invoked with three arguments of the determined calculation type).");
									return false;
								}
								else
								{
									return true;
								}
							}
						}
						else
						{
							using add_func = EmuCore::do_add<calc_fp, calc_fp>;
							if constexpr (!std::is_invocable_v<add_func, calc_fp, calc_fp>)
							{
								static_assert(!StaticAssert_, "Unable to perform a spherical linear interpolation of two EmuMath Quaternions (WITHOUT fused operations) as the determined addition function cannot be invoked with two arguments of the determined calculation type.");
								return false;
							}
							else
							{
								using add_result = typename std::invoke_result<add_func, calc_fp, calc_fp>::type;
								if constexpr (!std::is_constructible_v<out_type, add_result, add_result, add_result, add_result>)
								{
									static_assert(!StaticAssert_, "Unable to perform a spherical linear interpolation of two EmuMath Quaternions (WITHOUT fused operations) as the output cannot be constructed from 4 results from the determined addition function (when said function is invoked with two arguments of the determined calculation type).");
									return false;
								}
								else
								{
									return true;
								}
							}
						}
					}
				}
			}
		}
	}

	template<bool VectorOut_, bool Fused_, bool IsConstexpr_, typename OutT_, typename AT_, typename BT_, typename T_, bool StaticAssert_>
	[[nodiscard]] constexpr inline bool _valid_slerp_args()
	{
		using a = const EmuMath::Quaternion<AT_>&;
		using b = const EmuMath::Quaternion<BT_>&;
		using ax = decltype(_get_x(std::declval<a>()));
		using ay = decltype(_get_y(std::declval<a>()));
		using az = decltype(_get_z(std::declval<a>()));
		using aw = decltype(_get_w(std::declval<a>()));
		using bx = decltype(_get_x(std::declval<b>()));
		using by = decltype(_get_y(std::declval<b>()));
		using bz = decltype(_get_z(std::declval<b>()));
		using bw = decltype(_get_w(std::declval<b>()));
		using forward_t = typename EmuCore::TMP::forward_result<T_>::type;
		return _valid_slerp_args<VectorOut_, Fused_, IsConstexpr_, OutT_, ax, ay, az, aw, bx, by, bz, bw, forward_t, StaticAssert_>();
	}
#pragma endregion

#pragma region LERP_FUNCS
	template<bool VectorOut_, bool Fused_, typename OutT_, typename AX_, typename AY_, typename AZ_, typename AW_, typename BX_, typename BY_, typename BZ_, typename BW_, class ArgT_>
	[[nodiscard]] static constexpr inline auto _make_lerp(AX_&& ax_, AY_&& ay_, AZ_&& az_, AW_&& aw_, BX_&& bx_, BY_&& by_, BZ_&& bz_, BW_&& bw_, ArgT_&& t_)
		-> typename std::conditional<VectorOut_, typename EmuMath::Quaternion<OutT_>::vector_type, EmuMath::Quaternion<OutT_>>::type
	{
		if constexpr(_valid_lerp_args<VectorOut_, Fused_, OutT_, AX_, AY_, AZ_, AW_, BX_, BY_, BZ_, BW_, ArgT_, true>())
		{
			using out_quaternion = EmuMath::Quaternion<OutT_>;
			using ax_uq = typename EmuCore::TMP::remove_ref_cv<AX_>::type;
			using ay_uq = typename EmuCore::TMP::remove_ref_cv<AY_>::type;
			using az_uq = typename EmuCore::TMP::remove_ref_cv<AZ_>::type;
			using aw_uq = typename EmuCore::TMP::remove_ref_cv<AW_>::type;
			using bx_uq = typename EmuCore::TMP::remove_ref_cv<BX_>::type;
			using by_uq = typename EmuCore::TMP::remove_ref_cv<BY_>::type;
			using bz_uq = typename EmuCore::TMP::remove_ref_cv<BZ_>::type;
			using bw_uq = typename EmuCore::TMP::remove_ref_cv<BW_>::type;
			using t_uq = typename EmuCore::TMP::remove_ref_cv<ArgT_>::type;
			using out_t_uq = typename EmuCore::TMP::remove_ref_cv<OutT_>::type;
			using out_fp = typename out_quaternion::preferred_floating_point;
			using t_fp_arg = typename std::conditional<EmuMath::TMP::is_emu_vector_v<t_uq>, out_fp, t_uq>::type; // Don't use ArgT_ if non-scalar
			using calc_fp = typename EmuCore::TMP::largest_floating_point
			<
				ax_uq, ay_uq, az_uq, aw_uq, bx_uq, by_uq, bz_uq, bw_uq, t_fp_arg, out_t_uq, out_fp
			>::type;

			// Warning disabled as we are only ever moving separate indices, if any
#pragma warning(push)
#pragma warning(disable: 26800)
			using sub_func = EmuCore::do_subtract<calc_fp, calc_fp>;
			using lerp_func = typename std::conditional<Fused_, EmuCore::do_fused_lerp<calc_fp, calc_fp, calc_fp>, EmuCore::do_lerp<calc_fp, calc_fp, calc_fp>>::type;
			using out_type = typename std::conditional<VectorOut_, typename out_quaternion::vector_type, out_quaternion>::type;
			return out_type
			(
				lerp_func()(static_cast<calc_fp>(std::forward<AX_>(ax_)), static_cast<calc_fp>(std::forward<BX_>(bx_)), _get_generic_quaternion_x<calc_fp>(std::forward<ArgT_>(t_))),
				lerp_func()(static_cast<calc_fp>(std::forward<AY_>(ay_)), static_cast<calc_fp>(std::forward<BY_>(by_)), _get_generic_quaternion_y<calc_fp>(std::forward<ArgT_>(t_))),
				lerp_func()(static_cast<calc_fp>(std::forward<AZ_>(az_)), static_cast<calc_fp>(std::forward<BZ_>(bz_)), _get_generic_quaternion_z<calc_fp>(std::forward<ArgT_>(t_))),
				lerp_func()(static_cast<calc_fp>(std::forward<AW_>(aw_)), static_cast<calc_fp>(std::forward<BW_>(bw_)), _get_generic_quaternion_w<calc_fp>(std::forward<ArgT_>(t_)))
			);
#pragma warning(pop)
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<OutT_>(), "Failed to perform a linear interpolation (lerp) of two EmuMath Quaternions. See other static assert messages for more info.");
		}
	}

	template<bool VectorOut_, bool Fused_, typename OutT_, typename AT_, typename BT_, typename T_>
	[[nodiscard]] constexpr inline decltype(auto) _make_lerp(const EmuMath::Quaternion<AT_>& a_, const EmuMath::Quaternion<BT_>& b_, T_&& t_)
	{
		return _make_lerp<VectorOut_, Fused_, OutT_>
		(
			_get_x(a_),
			_get_y(a_),
			_get_z(a_),
			_get_w(a_),
			_get_x(b_),
			_get_y(b_),
			_get_z(b_),
			_get_w(b_),
			std::forward<T_>(t_)
		);
	}
#pragma endregion

#pragma region SLERP_FUNCS
	template
	<
		bool VectorOut_, bool Fused_, bool IsConstexpr_, typename OutT_,
		typename AX_, typename AY_, typename AZ_, typename AW_, typename BX_, typename BY_, typename BZ_, typename BW_, class ArgT_
	>
	[[nodiscard]] static constexpr inline auto _make_slerp(AX_&& ax_, AY_&& ay_, AZ_&& az_, AW_&& aw_, BX_&& bx_, BY_&& by_, BZ_&& bz_, BW_&& bw_, ArgT_&& t_)
		-> typename std::conditional<VectorOut_, typename EmuMath::Quaternion<OutT_>::vector_type, EmuMath::Quaternion<OutT_>>::type
	{
		if constexpr(_valid_slerp_args<VectorOut_, Fused_, IsConstexpr_, OutT_, AX_, AY_, AZ_, AW_, BX_, BY_, BZ_, BW_, ArgT_, true>())
		{
			using out_quaternion = EmuMath::Quaternion<OutT_>;
			using ax_uq = typename EmuCore::TMP::remove_ref_cv<AX_>::type;
			using ay_uq = typename EmuCore::TMP::remove_ref_cv<AY_>::type;
			using az_uq = typename EmuCore::TMP::remove_ref_cv<AZ_>::type;
			using aw_uq = typename EmuCore::TMP::remove_ref_cv<AW_>::type;
			using bx_uq = typename EmuCore::TMP::remove_ref_cv<BX_>::type;
			using by_uq = typename EmuCore::TMP::remove_ref_cv<BY_>::type;
			using bz_uq = typename EmuCore::TMP::remove_ref_cv<BZ_>::type;
			using bw_uq = typename EmuCore::TMP::remove_ref_cv<BW_>::type;
			using t_uq = typename EmuCore::TMP::remove_ref_cv<ArgT_>::type;
			using out_t_uq = typename EmuCore::TMP::remove_ref_cv<OutT_>::type;
			using out_fp = typename out_quaternion::preferred_floating_point;
			using t_fp_arg = typename std::conditional<EmuMath::TMP::is_emu_vector_v<t_uq>, out_fp, t_uq>::type; // Don't use ArgT_ if non-scalar
			using calc_fp = typename EmuCore::TMP::largest_floating_point
			<
				ax_uq, ay_uq, az_uq, aw_uq, bx_uq, by_uq, bz_uq, bw_uq, t_fp_arg, out_t_uq, out_fp
			>::type;

			calc_fp ax = static_cast<calc_fp>(std::forward<AX_>(ax_));
			calc_fp ay = static_cast<calc_fp>(std::forward<AY_>(ay_));
			calc_fp az = static_cast<calc_fp>(std::forward<AZ_>(az_));
			calc_fp aw = static_cast<calc_fp>(std::forward<AW_>(aw_));
			calc_fp bx = static_cast<calc_fp>(std::forward<BX_>(bx_));
			calc_fp by = static_cast<calc_fp>(std::forward<BY_>(by_));
			calc_fp bz = static_cast<calc_fp>(std::forward<BZ_>(bz_));
			calc_fp bw = static_cast<calc_fp>(std::forward<BW_>(bw_));

			// Calculate Dot
			using mul_func = EmuCore::do_multiply<calc_fp, calc_fp>;
			calc_fp omega = mul_func()(ax, bx);
			if constexpr (Fused_)
			{
				using fmadd_func = EmuCore::do_fmadd<calc_fp, calc_fp, calc_fp>;
				omega = fmadd_func()(ay, by, omega);
				omega = fmadd_func()(az, bz, omega);
				omega = fmadd_func()(aw, bw, omega);
			}
			else
			{
				using add_func = EmuCore::do_add<calc_fp, calc_fp>;
				omega = add_func()(omega, mul_func()(ay, by));
				omega = add_func()(omega, mul_func()(az, bz));
				omega = add_func()(omega, mul_func()(aw, bw));
			}

			// Saturate to -1:1 range, and retrieve acos of saturated dot
			using clamp_func = EmuCore::do_clamp<calc_fp, calc_fp, calc_fp, calc_fp>;
			using acos_func = typename std::conditional<IsConstexpr_, EmuCore::do_acos_constexpr<calc_fp>, EmuCore::do_acos<calc_fp>>::type;
			omega = acos_func()(clamp_func()(omega, calc_fp(-1), calc_fp(1)));

			// Calculate weightings
			using sin_func = typename std::conditional<IsConstexpr_, EmuCore::do_sin_constexpr<calc_fp>, EmuCore::do_sin<calc_fp>>::type;
			using div_func = EmuCore::do_divide<calc_fp, calc_fp>;
			using sub_func = EmuCore::do_subtract<calc_fp, calc_fp>;
			calc_fp weighting_divisor = sin_func()(omega);
			calc_fp t = static_cast<calc_fp>(std::forward<ArgT_>(t_));
			calc_fp ta = div_func()(sin_func()(mul_func()(sub_func()(calc_fp(1), t), omega)), weighting_divisor);
			calc_fp tb = div_func()(sin_func()(mul_func()(t, omega)), weighting_divisor);

			// Perform interpolation
			using out_type = typename std::conditional<VectorOut_, typename out_quaternion::vector_type, out_quaternion>::type;
			if constexpr (Fused_)
			{
				using fmadd_func = EmuCore::do_fmadd<calc_fp, calc_fp, calc_fp>;
				return out_type
				(
					fmadd_func()(ax, ta, mul_func()(bx, tb)),
					fmadd_func()(ay, ta, mul_func()(by, tb)),
					fmadd_func()(az, ta, mul_func()(bz, tb)),
					fmadd_func()(aw, ta, mul_func()(bw, tb))
				);
			}
			else
			{
				using add_func = EmuCore::do_add<calc_fp, calc_fp>;
				return out_type
				(
					add_func()(mul_func()(ax, ta), mul_func()(bx, tb)),
					add_func()(mul_func()(ay, ta), mul_func()(by, tb)),
					add_func()(mul_func()(az, ta), mul_func()(bz, tb)),
					add_func()(mul_func()(aw, ta), mul_func()(bw, tb))
				);
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<OutT_>(), "Failed to perform a spherical linear interpolation (slerp) of two EmuMath Quaternions. See other static assert messages for more info.");
		}
	}

	template<bool VectorOut_, bool Fused_, bool IsConstexpr_, typename OutT_, typename AT_, typename BT_, typename T_>
	[[nodiscard]] constexpr inline decltype(auto) _make_slerp(const EmuMath::Quaternion<AT_>& a_, const EmuMath::Quaternion<BT_>& b_, T_&& t_)
	{
		return _make_slerp<VectorOut_, Fused_, IsConstexpr_, OutT_>
		(
			_get_x(a_),
			_get_y(a_),
			_get_z(a_),
			_get_w(a_),
			_get_x(b_),
			_get_y(b_),
			_get_z(b_),
			_get_w(b_),
			std::forward<T_>(t_)
		);
	}
#pragma endregion
}

#endif