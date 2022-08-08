#ifndef EMU_MATH_QUATERNION_UNDERLYING_ARITHMETIC_H_INC_
#define EMU_MATH_QUATERNION_UNDERLYING_ARITHMETIC_H_INC_ 1

#include "_quaternion_tmp.h"
#include "_quaternion_underlying_get.h"

namespace EmuMath::Helpers::_quaternion_underlying
{
#pragma region VALIDITY_CHECKS
	template<class QuaternionT_, typename OutT_, typename Rhs_, bool OutputVector_, bool StaticAssert_>
	[[nodiscard]] constexpr inline bool _can_scalar_multiply()
	{
		using quat_type = EmuMath::Quaternion<OutT_>;
		using quat_fp = typename quat_type::preferred_floating_point;
		using mul_func = EmuCore::do_multiply<typename quat_type::value_type_uq, quat_fp>;
		using quat_value_ref = const typename quat_type::value_type&;
		
		if constexpr (EmuMath::TMP::is_emu_quaternion_v<typename EmuCore::TMP::remove_ref_cv<Rhs_>::type>)
		{
			static_assert(!StaticAssert_, "Unable to scalar multiply an EmuMath Quaternion as the passed scalar argument is also an EmuMath Quaternion.");
			return false;
		}
		else
		{
			if constexpr (!EmuCore::TMP::is_static_castable_v<typename EmuCore::TMP::forward_result<Rhs_>::type, quat_fp>)
			{
				static_assert(!StaticAssert_, "Unable to scalar multiply an EmuMath Quaternion as the passed scalar cannot be converted to the passed Quaternions preferred_floating_point type.");
				return false;
			}
			else
			{
				if constexpr (!std::is_invocable_v<mul_func, quat_value_ref, quat_fp>)
				{
					static_assert(!StaticAssert_, "Unable to scalar multiply an EmuMath Quaternion as the determined multiplication function cannot be invoked with 2 arguments, being 1: A constant reference to the Quaternion's value_type, 2: The Quaternion's preferred_floating_point type.");
					return false;
				}
				else
				{
					using mul_result = typename std::invoke_result<mul_func, quat_value_ref, quat_fp>::type;
					using out_quaternion = EmuMath::Quaternion<OutT_>;

					// Split this into a constexpr branch just to avoid the reliance on `vector_type` where it isn't needed
					if constexpr (OutputVector_)
					{
						if constexpr (!std::is_constructible_v<typename out_quaternion::vector_type, mul_result, mul_result, mul_result, mul_result>)
						{
							static_assert(!StaticAssert_, "Unable to scalar multiply an EmuMath Quaternion as the underlying vector_type cannot be constructed from 4 instances of the result of the determined multiplication function.");
							return false;
						}
						else
						{
							return true;
						}
					}
					else
					{
						if constexpr (!std::is_constructible_v<out_quaternion, mul_result, mul_result, mul_result, mul_result>)
						{
							// Fallback to vector_type deferred construction
							using out_vector = typename out_quaternion::vector_type;
							if constexpr (!(std::is_constructible_v<out_quaternion, out_vector&&> && std::is_constructible_v<out_vector, mul_result, mul_result, mul_result, mul_result>))
							{
								static_assert(!StaticAssert_, "Unable to scalar multiply an EmuMath Quaternion as the output Quaternion cannot be constructed from 4 instances of the result of the determined multiplication function, and neither can its vector_type (or the Quaternion cannot be constructed from an rvalue of its vector_type).");
								return false;
							}
							else
							{
								return true;
							}
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

	template<typename OutT_, class Lhs_, class Rhs_, bool OutputVector_, bool StaticAssert_>
	[[nodiscard]] constexpr inline bool _can_quaternion_multiply()
	{
		using rhs_quat_uq = typename EmuCore::TMP::remove_ref_cv<Rhs_>::type;
		if constexpr (!EmuMath::TMP::is_emu_quaternion_v<rhs_quat_uq>)
		{
			static_assert(!StaticAssert_, "Unable to multiply two EmuMath Quaternions as the passed Rhs_ type is not recognised as an EmuMath Quaternion.");
			return false;
		}
		else
		{
			using lhs_quat_uq = typename EmuCore::TMP::remove_ref_cv<Lhs_>::type;
			using out_quat = EmuMath::Quaternion<OutT_>;
			using calc_fp = typename EmuCore::TMP::largest_floating_point
			<
				typename lhs_quat_uq::preferred_floating_point, typename out_quat::preferred_floating_point, typename rhs_quat_uq::preferred_floating_point
			>::type;

			constexpr bool lhs_castable =
			(
				EmuCore::TMP::is_static_castable_v<decltype(_get_x(std::declval<Lhs_>())), calc_fp> &&
				EmuCore::TMP::is_static_castable_v<decltype(_get_y(std::declval<Lhs_>())), calc_fp> &&
				EmuCore::TMP::is_static_castable_v<decltype(_get_z(std::declval<Lhs_>())), calc_fp> &&
				EmuCore::TMP::is_static_castable_v<decltype(_get_w(std::declval<Lhs_>())), calc_fp>
			);
			if constexpr (!lhs_castable)
			{
				static_assert(!StaticAssert_, "Unable to multiply two EmuMath Quaternions as the left-hand Quaternion's values cannot be cast to the determined calculation type.");
				return false;
			}
			else
			{
				constexpr bool rhs_castable =
				(
					EmuCore::TMP::is_static_castable_v<decltype(_get_x(std::declval<Rhs_>())), calc_fp> &&
					EmuCore::TMP::is_static_castable_v<decltype(_get_y(std::declval<Rhs_>())), calc_fp> &&
					EmuCore::TMP::is_static_castable_v<decltype(_get_z(std::declval<Rhs_>())), calc_fp> &&
					EmuCore::TMP::is_static_castable_v<decltype(_get_w(std::declval<Rhs_>())), calc_fp>
				);
				if constexpr (!rhs_castable)
				{
					static_assert(!StaticAssert_, "Unable to multiply two EmuMath Quaternions as the right-hand Quaternion's values cannot be cast to the determined calculation type.");
					return false;
				}
				else
				{
					using add_func = EmuCore::do_add<calc_fp, calc_fp>;
					using sub_func = EmuCore::do_subtract<calc_fp, calc_fp>;
					using mul_func = EmuCore::do_multiply<calc_fp, calc_fp>;

					if constexpr (!std::is_invocable_r_v<calc_fp, add_func, calc_fp, calc_fp>)
					{
						static_assert(!StaticAssert_, "Unable to multiply two EmuMath Quaternions as the determined addition function cannot be invoked with two arguments of the determined calculation type while also outputting the either the determined calculation type or a type implicitly castable to it.");
						return false;
					}
					else if constexpr(!std::is_invocable_r_v<calc_fp, sub_func, calc_fp, calc_fp>)
					{
						static_assert(!StaticAssert_, "Unable to multiply two EmuMath Quaternions as the determined subtraction function cannot be invoked with two arguments of the determined calculation type while also outputting the either the determined calculation type or a type implicitly castable to it.");
						return false;
					}
					else if constexpr (!std::is_invocable_r_v<calc_fp, mul_func, calc_fp, calc_fp>)
					{
						static_assert(!StaticAssert_, "Unable to multiply two EmuMath Quaternions as the determined multiplication function cannot be invoked with two arguments of the determined calculation type while also outputting the either the determined calculation type or a type implicitly castable to it.");
						return false;
					}
					else
					{
						using out_quaternion = EmuMath::Quaternion<OutT_>;

						// Split this into a constexpr branch just to avoid the reliance on `vector_type` where it isn't needed
						if constexpr (OutputVector_)
						{
							if constexpr (!std::is_constructible_v<typename out_quaternion::vector_type, calc_fp&&, calc_fp&&, calc_fp&&, calc_fp&&>)
							{
								static_assert(!StaticAssert_, "Unable to multiply two EmuMath Quaternions as the underlying vector_type cannot be constructed from 4 rvalues of the determined calculation type.");
								return false;
							}
							else
							{
								return true;
							}
						}
						else
						{
							if constexpr (!std::is_constructible_v<out_quaternion, calc_fp&&, calc_fp&&, calc_fp&&, calc_fp&&>)
							{
								// Fallback to vector_type deferred construction
								using out_vector = typename out_quaternion::vector_type;
								constexpr bool vector_constructible = std::is_constructible_v<out_vector, calc_fp&&, calc_fp&&, calc_fp&&, calc_fp&&>;
								if constexpr (!(std::is_constructible_v<out_quaternion, out_vector&&> && vector_constructible))
								{
									static_assert(!StaticAssert_, "Unable to multiply two EmuMath Quaternions as the output Quaternion cannot be constructed from 4 rvalues of the determined calculation type, and neither can its vector_type (or the Quaternion cannot be constructed from an rvalue of its vector_type).");
									return false;
								}
								else
								{
									return true;
								}
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
#pragma endregion

#pragma region COMMON_OUTPUT_FUNCS
	template<bool OutputVector_, typename OutT_, typename X_, typename Y_, typename Z_, typename W_>
	[[nodiscard]] constexpr inline auto _output_multiply_results(X_&& x_, Y_&& y_, Z_&& z_, W_&& w_)
		-> typename std::conditional<OutputVector_, typename EmuMath::Quaternion<OutT_>::vector_type, EmuMath::Quaternion<OutT_>>::type
	{
		using out_quaternion = EmuMath::Quaternion<OutT_>;
		if constexpr (OutputVector_)
		{
			return typename out_quaternion::vector_type
			(
				std::forward<X_>(x_),
				std::forward<Y_>(y_),
				std::forward<Z_>(z_),
				std::forward<W_>(w_)
			);
		}
		else
		{
			if constexpr (std::is_constructible_v<out_quaternion, X_&&, Y_&&, Z_&&, W_&&>)
			{
				return out_quaternion
				(
					std::forward<X_>(x_),
					std::forward<Y_>(y_),
					std::forward<Z_>(z_),
					std::forward<W_>(w_)
				);
			}
			else
			{
				// Fallback to construction by vector_type
				return out_quaternion
				(
					std::forward<X_>(x_),
					std::forward<Y_>(y_),
					std::forward<Z_>(w_),
					std::forward<W_>(z_)
				);
			}
		}
	}
#pragma endregion

#pragma region MULTIPLICATION_FUNCS
	template<bool OutputVector_, typename OutT_, typename LhsT_, class Rhs_>
	[[nodiscard]] constexpr inline auto _multiply_quaternion_by_scalar(const EmuMath::Quaternion<LhsT_>& lhs_, Rhs_&& rhs_scalar_)
		-> typename std::conditional<OutputVector_, typename EmuMath::Quaternion<OutT_>::vector_type, EmuMath::Quaternion<OutT_>>::type
	{
		if constexpr(_can_scalar_multiply<OutT_, OutputVector_, true>())
		{
			using lhs_quaternion_uq = EmuMath::Quaternion<LhsT_>;
			using out_quaternion = EmuMath::Quaternion<OutT_>;
			using calc_fp = typename lhs_quaternion_uq::preferred_floating_point;
			using mul_func = EmuCore::do_multiply<typename lhs_quaternion_uq::value_type_uq, calc_fp>;

			const calc_fp rhs = static_cast<calc_fp>(std::forward<Rhs_>(rhs_scalar_));
			return _output_multiply_results<OutputVector_, OutT_>
			(
				mul_func()(_get_x(lhs_), rhs),
				mul_func()(_get_y(lhs_), rhs),
				mul_func()(_get_z(lhs_), rhs),
				mul_func()(_get_w(lhs_), rhs)
			);
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<OutT_>(), "Failed to multiply an EmuMath Quaternion by a scalar Rhs_ argument. See other static assert messages for more info.");
		}
	}

	template<bool OutputVector_, typename OutT_, typename LhsT_, class Rhs_>
	[[nodiscard]] static constexpr inline auto _multiply_quaternion_by_quaternion(const EmuMath::Quaternion<LhsT_>& lhs_, Rhs_&& rhs_quaternion_)
		-> typename std::conditional<OutputVector_, typename EmuMath::Quaternion<OutT_>::vector_type, EmuMath::Quaternion<OutT_>>::type
	{
		using lhs_quat = const EmuMath::Quaternion<LhsT_>&;
		using rhs_uq = typename EmuCore::TMP::remove_ref_cv<Rhs_>::type;
		if constexpr(_can_quaternion_multiply<OutT_, lhs_quat, Rhs_, OutputVector_, true>())
		{
			using out_quaternion = EmuMath::Quaternion<OutT_>;
			using calc_fp = typename EmuCore::TMP::largest_floating_point
			<
				typename EmuMath::Quaternion<LhsT_>::preferred_floating_point, typename out_quaternion::preferred_floating_point, typename rhs_uq::preferred_floating_point
			>::type;

			calc_fp lhs_x = static_cast<calc_fp>(_get_x(lhs_));
			calc_fp lhs_y = static_cast<calc_fp>(_get_y(lhs_));
			calc_fp lhs_z = static_cast<calc_fp>(_get_z(lhs_));
			calc_fp lhs_w = static_cast<calc_fp>(_get_w(lhs_));
			calc_fp rhs_x = _get_generic_quaternion_x<calc_fp>(std::forward<Rhs_>(rhs_quaternion_));
			calc_fp rhs_y = _get_generic_quaternion_y<calc_fp>(std::forward<Rhs_>(rhs_quaternion_));
			calc_fp rhs_z = _get_generic_quaternion_z<calc_fp>(std::forward<Rhs_>(rhs_quaternion_));
			calc_fp rhs_w = _get_generic_quaternion_w<calc_fp>(std::forward<Rhs_>(rhs_quaternion_));

			using add_func = EmuCore::do_add<calc_fp, calc_fp>;
			using sub_func = EmuCore::do_subtract<calc_fp, calc_fp>;
			using mul_func = EmuCore::do_multiply<calc_fp, calc_fp>;
			calc_fp x = sub_func()(mul_func()(lhs_y, rhs_z), mul_func()(lhs_z, rhs_y));
			x = add_func()(x, mul_func()(lhs_x, rhs_w));
			x = add_func()(x, mul_func()(lhs_w, rhs_x));

			calc_fp y = sub_func()(mul_func()(lhs_z, rhs_x), mul_func()(lhs_x, rhs_z));
			y = add_func()(y, mul_func()(lhs_y, rhs_w));
			y = add_func()(y, mul_func()(lhs_w, rhs_y));

			calc_fp z = sub_func()(mul_func()(lhs_x, rhs_y), mul_func()(lhs_y, rhs_x));
			z = add_func()(z, mul_func()(lhs_z, rhs_w));
			z = add_func()(z, mul_func()(lhs_w, rhs_z));

			calc_fp w = sub_func()(mul_func()(lhs_w, rhs_w), mul_func()(lhs_x, rhs_x));
			w = sub_func()(w, mul_func()(lhs_y, rhs_y));
			w = sub_func()(w, mul_func()(lhs_z, rhs_z));

			return _output_multiply_results<OutputVector_, OutT_>(std::move(x), std::move(y), std::move(z), std::move(w));
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<OutT_>(), "Failed to multiply two EmuMath Quaternions. See other static assert messages for more info.");
		}
	}
#pragma endregion
}

#endif
