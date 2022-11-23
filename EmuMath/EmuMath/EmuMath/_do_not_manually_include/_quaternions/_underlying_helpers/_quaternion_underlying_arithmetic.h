#ifndef EMU_MATH_QUATERNION_UNDERLYING_ARITHMETIC_H_INC_
#define EMU_MATH_QUATERNION_UNDERLYING_ARITHMETIC_H_INC_ 1

#include "_quaternion_tmp.h"
#include "_quaternion_underlying_get.h"

namespace EmuMath::Helpers::_quaternion_underlying
{
#pragma region VALIDITY_CHECKS
	template<bool Assigning_, typename LhsT_, typename OutT_, typename RhsT_, bool OutputVector_, bool StaticAssert_>
	[[nodiscard]] constexpr inline bool _can_quaternion_add()
	{
		using out_quaternion = EmuMath::Quaternion<OutT_>;
		using lhs_uq = EmuMath::Quaternion<LhsT_>;
		using rhs_uq = EmuMath::Quaternion<RhsT_>;
		using lhs_fp = typename lhs_uq::preferred_floating_point;
		using rhs_fp = typename rhs_uq::preferred_floating_point;
		using calc_fp = typename EmuCore::TMP::largest_floating_point<lhs_fp, rhs_fp, typename out_quaternion::preferred_floating_point>::type;
		using add_func = EmuCore::do_add<calc_fp, calc_fp>;

		using lhs_ref = typename std::conditional<Assigning_, EmuMath::Quaternion<LhsT_>&, const EmuMath::Quaternion<LhsT_>&>::type;
		using rhs_ref = const EmuMath::Quaternion<RhsT_>&;
		if constexpr (!EmuCore::TMP::is_static_castable_v<decltype(_get_x(std::declval<lhs_ref>())), calc_fp>)
		{
			static_assert(!StaticAssert_, "Unable to add two EmuMath Quaternions as the left-hand Quaternion cannot have its components cast to the determined calculation type.");
			return false;
		}
		else if constexpr (!EmuCore::TMP::is_static_castable_v<decltype(_get_x(std::declval<rhs_ref>())), calc_fp>)
		{
			static_assert(!StaticAssert_, "Unable to add two EmuMath Quaternions as the right-hand Quaternion cannot have its components cast to the determined calculation type.");
			return false;
		}
		else if constexpr(!std::is_invocable_v<add_func, calc_fp, calc_fp>)
		{
			static_assert(!StaticAssert_, "Unable to add two EmuMath Quaternions as the determined addition function cannot be invoked with two arguments of the determined calculation type.");
			return false;
		}
		else
		{
			using add_result = typename std::invoke_result<add_func, calc_fp, calc_fp>::type;
			if constexpr (Assigning_)
			{
				using lhs_value_uq = typename lhs_uq::value_type_uq;
				if constexpr (!EmuCore::TMP::valid_assign_direct_or_cast<lhs_value_uq, add_result, decltype(_get_x(std::declval<lhs_ref>()))>())
				{
					static_assert(!StaticAssert_, "Unable to add two EmuMath Quaternions and assign to the left-hand operand as the left-hand Quaternion's components cannot be successfully assigned via the addition results for respective components.");
					return false;
				}
				else
				{
					return true;
				}
			}
			else
			{
				using out_type = typename std::conditional<OutputVector_, typename out_quaternion::vector_type, out_quaternion>::type;
				if constexpr (!std::is_constructible_v<out_type, add_result&&, add_result&&, add_result&&, add_result&&>)
				{
					static_assert(!StaticAssert_, "Unable to add two EmuMath Quaternions as the output cannot be successfully constructed via the addition results for respective components.");
					return false;
				}
				else
				{
					return true;
				}
			}
		}
	}

	template<bool Assigning_, typename LhsT_, typename OutT_, typename RhsT_, bool OutputVector_, bool StaticAssert_>
	[[nodiscard]] constexpr inline bool _can_quaternion_subtract()
	{
		using out_quaternion = EmuMath::Quaternion<OutT_>;
		using lhs_uq = EmuMath::Quaternion<LhsT_>;
		using rhs_uq = EmuMath::Quaternion<RhsT_>;
		using lhs_fp = typename lhs_uq::preferred_floating_point;
		using rhs_fp = typename rhs_uq::preferred_floating_point;
		using calc_fp = typename EmuCore::TMP::largest_floating_point<lhs_fp, rhs_fp, typename out_quaternion::preferred_floating_point>::type;
		using sub_func = EmuCore::do_subtract<calc_fp, calc_fp>;

		using lhs_ref = typename std::conditional<Assigning_, EmuMath::Quaternion<LhsT_>&, const EmuMath::Quaternion<LhsT_>&>::type;
		using rhs_ref = const EmuMath::Quaternion<RhsT_>&;
		if constexpr (!EmuCore::TMP::is_static_castable_v<decltype(_get_x(std::declval<lhs_ref>())), calc_fp>)
		{
			static_assert(!StaticAssert_, "Unable to subtract two EmuMath Quaternions as the left-hand Quaternion cannot have its components cast to the determined calculation type.");
			return false;
		}
		else if constexpr (!EmuCore::TMP::is_static_castable_v<decltype(_get_x(std::declval<rhs_ref>())), calc_fp>)
		{
			static_assert(!StaticAssert_, "Unable to subtract two EmuMath Quaternions as the right-hand Quaternion cannot have its components cast to the determined calculation type.");
			return false;
		}
		else if constexpr(!std::is_invocable_v<sub_func, calc_fp, calc_fp>)
		{
			static_assert(!StaticAssert_, "Unable to subtract two EmuMath Quaternions as the determined subtraction function cannot be invoked with two arguments of the determined calculation type.");
			return false;
		}
		else
		{
			using sub_result = typename std::invoke_result<sub_func, calc_fp, calc_fp>::type;
			if constexpr (Assigning_)
			{
				using lhs_value_uq = typename lhs_uq::value_type_uq;
				if constexpr (!EmuCore::TMP::valid_assign_direct_or_cast<lhs_value_uq, sub_result&&, decltype(_get_x(std::declval<lhs_ref>()))>())
				{
					static_assert(!StaticAssert_, "Unable to subtract two EmuMath Quaternions and assign to the left-hand operand as the left-hand Quaternion's components cannot be successfully assigned via the subtraction results for respective components.");
					return false;
				}
				else
				{
					return true;
				}
			}
			else
			{
				using out_type = typename std::conditional<OutputVector_, typename out_quaternion::vector_type, out_quaternion>::type;
				if constexpr (!std::is_constructible_v<out_type, sub_result&&, sub_result&&, sub_result&&, sub_result&&>)
				{
					static_assert(!StaticAssert_, "Unable to subtract two EmuMath Quaternions as the output cannot be successfully constructed via the subtraction results for respective components.");
					return false;
				}
				else
				{
					return true;
				}
			}
		}
	}

	template<bool Assigning_, typename LhsT_, typename OutT_, bool OutputVector_, bool StaticAssert_>
	[[nodiscard]] constexpr inline bool _can_quaternion_negate()
	{
		using out_quaternion = EmuMath::Quaternion<OutT_>;
		using lhs_uq = EmuMath::Quaternion<LhsT_>;
		using lhs_fp = typename lhs_uq::preferred_floating_point;
		using calc_fp = typename EmuCore::TMP::largest_floating_point<lhs_fp, typename out_quaternion::preferred_floating_point>::type;
		using negate_func = EmuCore::do_negate<calc_fp>;

		using lhs_ref = typename std::conditional<Assigning_, EmuMath::Quaternion<LhsT_>&, const EmuMath::Quaternion<LhsT_>&>::type;
		if constexpr (!EmuCore::TMP::is_static_castable_v<decltype(_get_x(std::declval<lhs_ref>())), calc_fp>)
		{
			static_assert(!StaticAssert_, "Unable to negate an EmuMath Quaternion as the Quaternion cannot have its components cast to the determined calculation type.");
			return false;
		}
		else if constexpr(!std::is_invocable_v<negate_func, calc_fp>)
		{
			static_assert(!StaticAssert_, "Unable to negate an EmuMath Quaternion as the determined negation function cannot be invoked with one argument of the determined calculation type.");
			return false;
		}
		else
		{
			using negate_result = typename std::invoke_result<negate_func, calc_fp>::type;
			if constexpr (Assigning_)
			{
				using lhs_value_uq = typename lhs_uq::value_type_uq;
				if constexpr (!EmuCore::TMP::valid_assign_direct_or_cast<lhs_value_uq, negate_result&&, decltype(_get_x(std::declval<lhs_ref>()))>())
				{
					static_assert(!StaticAssert_, "Unable to negate an EmuMath Quaternion and assign to the left-hand operand as the left-hand Quaternion's components cannot be successfully assigned via the negation results for respective components.");
					return false;
				}
				else
				{
					return true;
				}
			}
			else
			{
				using out_type = typename std::conditional<OutputVector_, typename out_quaternion::vector_type, out_quaternion>::type;
				if constexpr (!std::is_constructible_v<out_type, negate_result&&, negate_result&&, negate_result&&, negate_result&&>)
				{
					static_assert(!StaticAssert_, "Unable to negate an EmuMath Quaternion as the output cannot be successfully constructed via the negation results for respective components.");
					return false;
				}
				else
				{
					return true;
				}
			}
		}
	}

	template<bool Assigning_, class QuaternionT_, typename OutT_, typename Rhs_, bool OutputVector_, bool StaticAssert_>
	[[nodiscard]] constexpr inline bool _can_scalar_divide()
	{
		using out_quaternion = EmuMath::Quaternion<OutT_>;
		using quat_type = EmuMath::Quaternion<QuaternionT_>;
		using quat_fp = typename quat_type::preferred_floating_point;
		using div_func = EmuCore::do_multiply<typename quat_type::value_type_uq, quat_fp>;
		using quat_value_ref = const typename quat_type::value_type&;
		
		if constexpr (EmuMath::TMP::is_emu_quaternion_v<typename EmuCore::TMP::remove_ref_cv<Rhs_>::type>)
		{
			static_assert(!StaticAssert_, "Unable to scalar divide an EmuMath Quaternion as the passed scalar argument is also an EmuMath Quaternion.");
			return false;
		}
		else
		{
			if constexpr (!EmuCore::TMP::is_static_castable_v<typename EmuCore::TMP::forward_result<Rhs_>::type, quat_fp>)
			{
				static_assert(!StaticAssert_, "Unable to scalar divide an EmuMath Quaternion as the passed scalar cannot be converted to the passed Quaternions preferred_floating_point type.");
				return false;
			}
			else
			{
				if constexpr (!std::is_invocable_v<div_func, quat_value_ref, quat_fp>)
				{
					static_assert(!StaticAssert_, "Unable to scalar divide an EmuMath Quaternion as the determined division function cannot be invoked with 2 arguments, being 1: A constant reference to the Quaternion's value_type, 2: The Quaternion's preferred_floating_point type.");
					return false;
				}
				else
				{
					using div_result = typename std::invoke_result<div_func, quat_value_ref, quat_fp>::type;
					if constexpr (Assigning_)
					{
						using quat_ref = EmuMath::Quaternion<QuaternionT_>&;
						using quat_value_uq = typename EmuMath::Quaternion<QuaternionT_>::value_type_uq;
						constexpr bool all_assignable = EmuCore::TMP::valid_assign_direct_or_cast<quat_value_uq, div_result, decltype(_get_x(std::declval<quat_ref>()))>();
						if constexpr (!all_assignable)
						{
							static_assert(!StaticAssert_, "Unable to scalar divide-assign an EmuMath Quaternion as the output Quaternion's values cannot be assigned to from the results of respective divisions.");
							return false;
						}
						else
						{
							return true;
						}
					}
					else
					{
						// Split this into a constexpr branch just to avoid the reliance on `vector_type` where it isn't needed
						if constexpr (OutputVector_)
						{
							if constexpr (!std::is_constructible_v<typename out_quaternion::vector_type, div_result, div_result, div_result, div_result>)
							{
								static_assert(!StaticAssert_, "Unable to scalar divide an EmuMath Quaternion as the underlying vector_type cannot be constructed from 4 instances of the result of the determined diivision function.");
								return false;
							}
							else
							{
								return true;
							}
						}
						else
						{
							if constexpr (!std::is_constructible_v<out_quaternion, div_result, div_result, div_result, div_result>)
							{
								// Fallback to vector_type deferred construction
								using out_vector = typename out_quaternion::vector_type;
								if constexpr (!(std::is_constructible_v<out_quaternion, out_vector&&> && std::is_constructible_v<out_vector, div_result, div_result, div_result, div_result>))
								{
									static_assert(!StaticAssert_, "Unable to scalar divide an EmuMath Quaternion as the output Quaternion cannot be constructed from 4 instances of the result of the determined diivision function, and neither can its vector_type (or the Quaternion cannot be constructed from an rvalue of its vector_type).");
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

	template<bool Assigning_, class QuaternionT_, typename OutT_, typename Rhs_, bool OutputVector_, bool StaticAssert_>
	[[nodiscard]] constexpr inline bool _can_scalar_multiply()
	{
		using out_quaternion = EmuMath::Quaternion<OutT_>;
		using quat_type = EmuMath::Quaternion<QuaternionT_>;
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
					if constexpr (Assigning_)
					{
						using quat_ref = EmuMath::Quaternion<QuaternionT_>&;
						using quat_value_uq = typename EmuMath::Quaternion<QuaternionT_>::value_type_uq;
						constexpr bool all_assignable = EmuCore::TMP::valid_assign_direct_or_cast<quat_value_uq, mul_result, decltype(_get_x(std::declval<quat_ref>()))>();
						if constexpr (!all_assignable)
						{
							static_assert(!StaticAssert_, "Unable to scalar multiply-assign an EmuMath Quaternion as the output Quaternion's values cannot be assigned to from the results of respective multiplications.");
							return false;
						}
						else
						{
							return true;
						}
					}
					else
					{
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
	}

	template<bool Assigning_, typename OutT_, class Lhs_, class Rhs_, bool OutputVector_, bool Fused_, bool StaticAssert_>
	[[nodiscard]] constexpr inline bool _can_quaternion_multiply()
	{
		using lhs_quat_uq = typename EmuCore::TMP::remove_ref_cv<Lhs_>::type;
		using rhs_quat_uq = typename EmuCore::TMP::remove_ref_cv<Rhs_>::type;
		if constexpr (!EmuMath::TMP::is_emu_quaternion_v<lhs_quat_uq>)
		{
			static_assert(!StaticAssert_, "Unable to multiply two EmuMath Quaternions as the passed Lhs_ type is not recognised as an EmuMath Quaternion.");
			return false;
		}
		else if constexpr (!EmuMath::TMP::is_emu_quaternion_v<rhs_quat_uq>)
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
						static_assert(!StaticAssert_, "Unable to multiply two EmuMath Quaternions as the determined addition function cannot be invoked with two arguments of the determined calculation type while also outputting either the determined calculation type or a type implicitly castable to it.");
						return false;
					}
					else if constexpr(!std::is_invocable_r_v<calc_fp, sub_func, calc_fp, calc_fp>)
					{
						static_assert(!StaticAssert_, "Unable to multiply two EmuMath Quaternions as the determined subtraction function cannot be invoked with two arguments of the determined calculation type while also outputting either the determined calculation type or a type implicitly castable to it.");
						return false;
					}
					else if constexpr (!std::is_invocable_r_v<calc_fp, mul_func, calc_fp, calc_fp>)
					{
						static_assert(!StaticAssert_, "Unable to multiply two EmuMath Quaternions as the determined multiplication function cannot be invoked with two arguments of the determined calculation type while also outputting either the determined calculation type or a type implicitly castable to it.");
						return false;
					}
					else
					{
						if constexpr (Fused_)
						{
							using fmadd_func = EmuCore::do_fmadd<calc_fp, calc_fp, calc_fp>;
							using fmsub_func = EmuCore::do_fmadd<calc_fp, calc_fp, calc_fp>;
							if constexpr (!std::is_invocable_r_v<calc_fp, fmadd_func, calc_fp, calc_fp, calc_fp>)
							{
								static_assert(!StaticAssert_, "Unable to multiply two EmuMath Quaternions (WITH fused operations) as the determined fused multiply-add function cannot be invoked with three arguments of the determined calculation type while also outputting either the determined calculation type or a type implicitly castable to it.");
								return false;
							}
							else if constexpr (!std::is_invocable_r_v<calc_fp, fmsub_func, calc_fp, calc_fp, calc_fp>)
							{
								static_assert(!StaticAssert_, "Unable to multiply two EmuMath Quaternions (WITH fused operations) as the determined fused multiply-subtract function cannot be invoked with three arguments of the determined calculation type while also outputting either the determined calculation type or a type implicitly castable to it.");
								return false;
							}
						}

						if constexpr (Assigning_)
						{
							if constexpr (std::is_const_v<Lhs_>)
							{
								static_assert(!StaticAssert_, "Unable to multiply two EmuMath Quaternions and assign to the left-hand operand as it is const-qualified.");
								return false;
							}
							else
							{
								using lhs_value_uq = typename lhs_quat_uq::value_type_uq;
								constexpr bool all_assignable = EmuCore::TMP::valid_assign_direct_or_cast<lhs_value_uq, calc_fp&&, decltype(_get_x(std::declval<Lhs_>()))>();
								if constexpr (!all_assignable)
								{
									static_assert(!StaticAssert_, "Unable to multiply two EmuMath Quaternions and assign to the left-hand operand as not all indices in the left-hand Quaternion could be assigned by an rvalue of the determined calculation type.");
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
							// Split this into a constexpr branch just to avoid the reliance on `vector_type` where it isn't needed
							using out_quaternion = EmuMath::Quaternion<OutT_>;
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
					typename out_quaternion::vector_type
					(
						std::forward<X_>(x_),
						std::forward<Y_>(y_),
						std::forward<Z_>(w_),
						std::forward<W_>(z_)
					)
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
		if constexpr(_can_scalar_multiply<false, LhsT_, OutT_, Rhs_, OutputVector_, true>())
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

	template<typename LhsT_, class Rhs_>
	[[nodiscard]] constexpr inline void _multiply_assign_quaternion_by_scalar(EmuMath::Quaternion<LhsT_>& lhs_, Rhs_&& rhs_scalar_)
	{
		if constexpr(_can_scalar_multiply<false, LhsT_, LhsT_, Rhs_, false, true>())
		{
			using lhs_quaternion_uq = EmuMath::Quaternion<LhsT_>;
			using calc_fp = typename lhs_quaternion_uq::preferred_floating_point;
			using mul_func = EmuCore::do_multiply<typename lhs_quaternion_uq::value_type_uq, calc_fp>;
			using lhs_value_uq = typename lhs_quaternion_uq::value_type_uq;

			const calc_fp rhs = static_cast<calc_fp>(std::forward<Rhs_>(rhs_scalar_));
			EmuCore::TMP::assign_direct_or_cast<lhs_value_uq>(_get_x(lhs_), mul_func()(_get_x(lhs_), rhs));
			EmuCore::TMP::assign_direct_or_cast<lhs_value_uq>(_get_y(lhs_), mul_func()(_get_y(lhs_), rhs));
			EmuCore::TMP::assign_direct_or_cast<lhs_value_uq>(_get_z(lhs_), mul_func()(_get_z(lhs_), rhs));
			EmuCore::TMP::assign_direct_or_cast<lhs_value_uq>(_get_w(lhs_), mul_func()(_get_w(lhs_), rhs));
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<LhsT_>(), "Failed to multiply an EmuMath Quaternion by a scalar Rhs_ argument. See other static assert messages for more info.");
		}
	}

	template<bool Assigning_, bool OutputVector_, bool Fused_, typename OutT_, class Lhs_, class Rhs_>
	[[nodiscard]] static constexpr inline auto _multiply_quaternion_by_quaternion(Lhs_& lhs_, Rhs_&& rhs_quaternion_)
		-> typename std::conditional
			<
				Assigning_,
				void,
				typename std::conditional<OutputVector_, typename EmuMath::Quaternion<OutT_>::vector_type, EmuMath::Quaternion<OutT_>>::type
			>::type
	{
		if constexpr(_can_quaternion_multiply<Assigning_, OutT_, Lhs_, Rhs_, OutputVector_, Fused_, true>())
		{
			using lhs_uq = typename EmuCore::TMP::remove_ref_cv<Lhs_>::type;
			using rhs_uq = typename EmuCore::TMP::remove_ref_cv<Rhs_>::type;
			using out_quaternion = EmuMath::Quaternion<OutT_>;
			using calc_fp = typename EmuCore::TMP::largest_floating_point
			<
				typename lhs_uq::preferred_floating_point, typename out_quaternion::preferred_floating_point, typename rhs_uq::preferred_floating_point
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

			// Prepare x, y, z, w as first right-hand subtraction operand for respective components 
			calc_fp x = mul_func()(lhs_z, rhs_y);
			calc_fp y = mul_func()(lhs_x, rhs_z);
			calc_fp z = mul_func()(lhs_y, rhs_x);
			calc_fp w = mul_func()(lhs_x, rhs_x);
			if constexpr (Fused_)
			{
				using fmadd_func = EmuCore::do_fmadd<calc_fp, calc_fp, calc_fp>;
				using fmsub_func = EmuCore::do_fmsub<calc_fp, calc_fp, calc_fp>;
				x = fmsub_func()(lhs_y, rhs_z, x);
				x = fmadd_func()(lhs_x, rhs_w, x);
				x = fmadd_func()(lhs_w, rhs_x, x);

				y = fmsub_func()(lhs_z, rhs_x, y);
				y = fmadd_func()(lhs_y, rhs_w, y);
				y = fmadd_func()(lhs_w, rhs_y, y);

				z = fmsub_func()(lhs_x, rhs_y, z);
				z = fmadd_func()(lhs_z, rhs_w, z);
				z = fmadd_func()(lhs_w, rhs_z, z);

				w = fmsub_func()(lhs_w, rhs_w, w);
				w = sub_func()(w, mul_func()(lhs_y, rhs_y));
				w = sub_func()(w, mul_func()(lhs_z, rhs_z)); 
			}
			else
			{
				x = sub_func()(mul_func()(lhs_y, rhs_z), x);
				x = add_func()(mul_func()(lhs_x, rhs_w), x);
				x = add_func()(mul_func()(lhs_w, rhs_x), x);

				y = sub_func()(mul_func()(lhs_z, rhs_x), y);
				y = add_func()(mul_func()(lhs_y, rhs_w), y);
				y = add_func()(mul_func()(lhs_w, rhs_y), y);

				z = sub_func()(mul_func()(lhs_x, rhs_y), z);
				z = add_func()(mul_func()(lhs_z, rhs_w), z);
				z = add_func()(mul_func()(lhs_w, rhs_z), z);

				w = sub_func()(mul_func()(lhs_w, rhs_w), w);
				w = sub_func()(w, mul_func()(lhs_y, rhs_y));
				w = sub_func()(w, mul_func()(lhs_z, rhs_z));
			}

			if constexpr (Assigning_)
			{
				using lhs_value_uq = typename lhs_uq::value_type_uq;
				EmuCore::TMP::assign_direct_or_cast<lhs_value_uq>(_get_x(lhs_), std::move(x));
				EmuCore::TMP::assign_direct_or_cast<lhs_value_uq>(_get_y(lhs_), std::move(y));
				EmuCore::TMP::assign_direct_or_cast<lhs_value_uq>(_get_z(lhs_), std::move(z));
				EmuCore::TMP::assign_direct_or_cast<lhs_value_uq>(_get_w(lhs_), std::move(w));
			}
			else
			{
				return _output_multiply_results<OutputVector_, OutT_>(std::move(x), std::move(y), std::move(z), std::move(w));
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<OutT_>(), "Failed to multiply two EmuMath Quaternions. See other static assert messages for more info.");
		}
	}
#pragma endregion

#pragma region ADDITION_FUNCS
	template<bool OutputVector_, typename OutT_, typename LhsT_, typename RhsT_>
	[[nodiscard]] constexpr inline auto _add_quaternions(const EmuMath::Quaternion<LhsT_>& lhs_, const EmuMath::Quaternion<RhsT_>& rhs_)
		-> typename std::conditional<OutputVector_, typename EmuMath::Quaternion<OutT_>::vector_type, EmuMath::Quaternion<OutT_>>::type
	{
		if constexpr (_can_quaternion_add<false, LhsT_, OutT_, RhsT_, OutputVector_, true>())
		{
			using out_quaternion = EmuMath::Quaternion<OutT_>;
			using lhs_uq = EmuMath::Quaternion<LhsT_>;
			using rhs_uq = EmuMath::Quaternion<RhsT_>;
			using lhs_fp = typename lhs_uq::preferred_floating_point;
			using rhs_fp = typename rhs_uq::preferred_floating_point;
			using calc_fp = typename EmuCore::TMP::largest_floating_point<lhs_fp, rhs_fp, typename out_quaternion::preferred_floating_point>::type;
			using add_func = EmuCore::do_add<calc_fp, calc_fp>;

			return typename std::conditional<OutputVector_, typename out_quaternion::vector_type, out_quaternion>::type
			(
				add_func()(static_cast<calc_fp>(_get_x(lhs_)), static_cast<calc_fp>(_get_x(rhs_))),
				add_func()(static_cast<calc_fp>(_get_y(lhs_)), static_cast<calc_fp>(_get_y(rhs_))),
				add_func()(static_cast<calc_fp>(_get_z(lhs_)), static_cast<calc_fp>(_get_z(rhs_))),
				add_func()(static_cast<calc_fp>(_get_w(lhs_)), static_cast<calc_fp>(_get_w(rhs_)))
			);
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<OutT_>(), "Failed to add two EmuMath Quaternions. See other static assert messages for more info");
		}
	}

	template<typename LhsT_, typename RhsT_>
	[[nodiscard]] constexpr inline void _add_assign_quaternions(EmuMath::Quaternion<LhsT_>& lhs_, const EmuMath::Quaternion<RhsT_>& rhs_)
	{
		if constexpr (_can_quaternion_add<true, LhsT_, LhsT_, RhsT_, false, true>())
		{
			using lhs_uq = EmuMath::Quaternion<LhsT_>;
			using rhs_uq = EmuMath::Quaternion<RhsT_>;
			using lhs_fp = typename lhs_uq::preferred_floating_point;
			using rhs_fp = typename rhs_uq::preferred_floating_point;
			using calc_fp = typename EmuCore::TMP::largest_floating_point<lhs_fp, rhs_fp>::type;
			using add_func = EmuCore::do_add<calc_fp, calc_fp>;
			using lhs_value_uq = typename lhs_uq::value_type_uq;

			EmuCore::TMP::assign_direct_or_cast<lhs_value_uq>(_get_x(lhs_), add_func()(static_cast<calc_fp>(_get_x(lhs_)), static_cast<calc_fp>(_get_x(rhs_))));
			EmuCore::TMP::assign_direct_or_cast<lhs_value_uq>(_get_y(lhs_), add_func()(static_cast<calc_fp>(_get_y(lhs_)), static_cast<calc_fp>(_get_y(rhs_))));
			EmuCore::TMP::assign_direct_or_cast<lhs_value_uq>(_get_z(lhs_), add_func()(static_cast<calc_fp>(_get_z(lhs_)), static_cast<calc_fp>(_get_z(rhs_))));
			EmuCore::TMP::assign_direct_or_cast<lhs_value_uq>(_get_w(lhs_), add_func()(static_cast<calc_fp>(_get_w(lhs_)), static_cast<calc_fp>(_get_w(rhs_))));
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<LhsT_>(), "Failed to add two EmuMath Quaternions and assign the results to the left-hand operand. See other static assert messages for more info");
		}
	}
#pragma endregion

#pragma region NEGATION_FUNCS
	template<bool OutputVector_, typename OutT_, typename LhsT_>
	[[nodiscard]] constexpr inline auto _negate_quaternion(const EmuMath::Quaternion<LhsT_>& lhs_)
		-> typename std::conditional<OutputVector_, typename EmuMath::Quaternion<OutT_>::vector_type, EmuMath::Quaternion<OutT_>>::type
	{
		if constexpr (_can_quaternion_negate<false, LhsT_, OutT_, OutputVector_, true>())
		{
			using out_quaternion = EmuMath::Quaternion<OutT_>;
			using lhs_uq = EmuMath::Quaternion<LhsT_>;
			using lhs_fp = typename lhs_uq::preferred_floating_point;
			using calc_fp = typename EmuCore::TMP::largest_floating_point<lhs_fp, typename out_quaternion::preferred_floating_point>::type;
			using negate_func = EmuCore::do_negate<calc_fp>;

			return typename std::conditional<OutputVector_, typename out_quaternion::vector_type, out_quaternion>::type
			(
				negate_func()(static_cast<calc_fp>(_get_x(lhs_))),
				negate_func()(static_cast<calc_fp>(_get_y(lhs_))),
				negate_func()(static_cast<calc_fp>(_get_z(lhs_))),
				negate_func()(static_cast<calc_fp>(_get_w(lhs_)))
			);
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<OutT_>(), "Failed to negate an EmuMath Quaternion. See other static assert messages for more info");
		}
	}

	template<typename LhsT_>
	[[nodiscard]] constexpr inline void _negate_assign_quaternion(EmuMath::Quaternion<LhsT_>& lhs_)
	{
		if constexpr (_can_quaternion_negate<true, LhsT_, LhsT_, false, true>())
		{
			using lhs_uq = EmuMath::Quaternion<LhsT_>;
			using lhs_fp = typename lhs_uq::preferred_floating_point;
			using calc_fp = typename EmuCore::TMP::largest_floating_point<lhs_fp>::type;
			using negate_func = EmuCore::do_negate<calc_fp>;
			using lhs_value_uq = typename lhs_uq::value_type_uq;

			EmuCore::TMP::assign_direct_or_cast<lhs_value_uq>(_get_x(lhs_), negate_func()(static_cast<calc_fp>(_get_x(lhs_))));
			EmuCore::TMP::assign_direct_or_cast<lhs_value_uq>(_get_y(lhs_), negate_func()(static_cast<calc_fp>(_get_y(lhs_))));
			EmuCore::TMP::assign_direct_or_cast<lhs_value_uq>(_get_z(lhs_), negate_func()(static_cast<calc_fp>(_get_z(lhs_))));
			EmuCore::TMP::assign_direct_or_cast<lhs_value_uq>(_get_w(lhs_), negate_func()(static_cast<calc_fp>(_get_w(lhs_))));
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<LhsT_>(), "Failed to negate and assign to an EmuMath Quaternion. See other static assert messages for more info");
		}
	}
#pragma endregion

#pragma region SUBTRACTION_FUNCS
	template<bool OutputVector_, typename OutT_, typename LhsT_, typename RhsT_>
	[[nodiscard]] constexpr inline auto _subtract_quaternions(const EmuMath::Quaternion<LhsT_>& lhs_, const EmuMath::Quaternion<RhsT_>& rhs_)
		-> typename std::conditional<OutputVector_, typename EmuMath::Quaternion<OutT_>::vector_type, EmuMath::Quaternion<OutT_>>::type
	{
		if constexpr (_can_quaternion_subtract<false, LhsT_, OutT_, RhsT_, OutputVector_, true>())
		{
			using out_quaternion = EmuMath::Quaternion<OutT_>;
			using lhs_uq = EmuMath::Quaternion<LhsT_>;
			using rhs_uq = EmuMath::Quaternion<RhsT_>;
			using lhs_fp = typename lhs_uq::preferred_floating_point;
			using rhs_fp = typename rhs_uq::preferred_floating_point;
			using calc_fp = typename EmuCore::TMP::largest_floating_point<lhs_fp, rhs_fp, typename out_quaternion::preferred_floating_point>::type;
			using sub_func = EmuCore::do_subtract<calc_fp, calc_fp>;

			return typename std::conditional<OutputVector_, typename out_quaternion::vector_type, out_quaternion>::type
			(
				sub_func()(static_cast<calc_fp>(_get_x(lhs_)), static_cast<calc_fp>(_get_x(rhs_))),
				sub_func()(static_cast<calc_fp>(_get_y(lhs_)), static_cast<calc_fp>(_get_y(rhs_))),
				sub_func()(static_cast<calc_fp>(_get_z(lhs_)), static_cast<calc_fp>(_get_z(rhs_))),
				sub_func()(static_cast<calc_fp>(_get_w(lhs_)), static_cast<calc_fp>(_get_w(rhs_)))
			);
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<OutT_>(), "Failed to subtract two EmuMath Quaternions. See other static assert messages for more info");
		}
	}

	template<typename LhsT_, typename RhsT_>
	[[nodiscard]] constexpr inline void _subtract_assign_quaternions(EmuMath::Quaternion<LhsT_>& lhs_, const EmuMath::Quaternion<RhsT_>& rhs_)
	{
		if constexpr (_can_quaternion_subtract<true, LhsT_, LhsT_, RhsT_, false, true>())
		{
			using lhs_uq = EmuMath::Quaternion<LhsT_>;
			using rhs_uq = EmuMath::Quaternion<RhsT_>;
			using lhs_fp = typename lhs_uq::preferred_floating_point;
			using rhs_fp = typename rhs_uq::preferred_floating_point;
			using calc_fp = typename EmuCore::TMP::largest_floating_point<lhs_fp, rhs_fp>::type;
			using sub_func = EmuCore::do_subtract<calc_fp, calc_fp>;
			using lhs_value_uq = typename lhs_uq::value_type_uq;

			EmuCore::TMP::assign_direct_or_cast<lhs_value_uq>(_get_x(lhs_), sub_func()(static_cast<calc_fp>(_get_x(lhs_)), static_cast<calc_fp>(_get_x(rhs_))));
			EmuCore::TMP::assign_direct_or_cast<lhs_value_uq>(_get_y(lhs_), sub_func()(static_cast<calc_fp>(_get_y(lhs_)), static_cast<calc_fp>(_get_y(rhs_))));
			EmuCore::TMP::assign_direct_or_cast<lhs_value_uq>(_get_z(lhs_), sub_func()(static_cast<calc_fp>(_get_z(lhs_)), static_cast<calc_fp>(_get_z(rhs_))));
			EmuCore::TMP::assign_direct_or_cast<lhs_value_uq>(_get_w(lhs_), sub_func()(static_cast<calc_fp>(_get_w(lhs_)), static_cast<calc_fp>(_get_w(rhs_))));
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<LhsT_>(), "Failed to subtract two EmuMath Quaternions and assign the results to the left-hand operand. See other static assert messages for more info");
		}
	}
#pragma endregion

#pragma region DIVISION_FUNCS
	template<bool OutputVector_, typename OutT_, typename LhsT_, class Rhs_>
	[[nodiscard]] constexpr inline auto _divide_quaternion(const EmuMath::Quaternion<LhsT_>& lhs_, Rhs_&& rhs_scalar_)
		-> typename std::conditional<OutputVector_, typename EmuMath::Quaternion<OutT_>::vector_type, EmuMath::Quaternion<OutT_>>::type
	{
		if constexpr(_can_scalar_divide<false, LhsT_, OutT_, Rhs_, OutputVector_, true>())
		{
			using lhs_quaternion_uq = EmuMath::Quaternion<LhsT_>;
			using out_quaternion = EmuMath::Quaternion<OutT_>;
			using calc_fp = typename lhs_quaternion_uq::preferred_floating_point;
			using div_func = EmuCore::do_divide<typename lhs_quaternion_uq::value_type_uq, calc_fp>;

			const calc_fp rhs = static_cast<calc_fp>(std::forward<Rhs_>(rhs_scalar_));
			return _output_multiply_results<OutputVector_, OutT_>
			(
				div_func()(_get_x(lhs_), rhs),
				div_func()(_get_y(lhs_), rhs),
				div_func()(_get_z(lhs_), rhs),
				div_func()(_get_w(lhs_), rhs)
			);
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<OutT_>(), "Failed to divide an EmuMath Quaternion by a scalar Rhs_ argument. See other static assert messages for more info.");
		}
	}

	template<typename LhsT_, class Rhs_>
	[[nodiscard]] constexpr inline void _divide_assign_quaternion(EmuMath::Quaternion<LhsT_>& lhs_, Rhs_&& rhs_scalar_)
	{
		if constexpr(_can_scalar_divide<false, LhsT_, LhsT_, Rhs_, false, true>())
		{
			using lhs_quaternion_uq = EmuMath::Quaternion<LhsT_>;
			using calc_fp = typename lhs_quaternion_uq::preferred_floating_point;
			using div_func = EmuCore::do_divide<typename lhs_quaternion_uq::value_type_uq, calc_fp>;
			using lhs_value_uq = typename lhs_quaternion_uq::value_type_uq;

			const calc_fp rhs = static_cast<calc_fp>(std::forward<Rhs_>(rhs_scalar_));
			EmuCore::TMP::assign_direct_or_cast<lhs_value_uq>(_get_x(lhs_), div_func()(_get_x(lhs_), rhs));
			EmuCore::TMP::assign_direct_or_cast<lhs_value_uq>(_get_y(lhs_), div_func()(_get_y(lhs_), rhs));
			EmuCore::TMP::assign_direct_or_cast<lhs_value_uq>(_get_z(lhs_), div_func()(_get_z(lhs_), rhs));
			EmuCore::TMP::assign_direct_or_cast<lhs_value_uq>(_get_w(lhs_), div_func()(_get_w(lhs_), rhs));
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<LhsT_>(), "Failed to divide an EmuMath Quaternion by a scalar Rhs_ argument. See other static assert messages for more info.");
		}
	}
#pragma endregion
}

#endif
