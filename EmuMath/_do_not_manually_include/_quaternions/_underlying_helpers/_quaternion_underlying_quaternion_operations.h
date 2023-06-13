#ifndef EMU_MATH_QUATERNION_UNDERLYING_QUATERNION_OPERATIONS_H_INC_
#define EMU_MATH_QUATERNION_UNDERLYING_QUATERNION_OPERATIONS_H_INC_ 1

#include "_quaternion_tmp.h"
#include "_quaternion_underlying_get.h"

namespace EmuMath::Helpers::_quaternion_underlying
{
#pragma region VALIDITY_CHECKS
	template<bool VectorOut_, typename OutT_, typename X_, typename Y_, typename Z_, typename W_, bool StaticAssert_>
	[[nodiscard]] constexpr inline bool _valid_conjugate_args()
	{
		using out_quaternion = EmuMath::Quaternion<OutT_>;
		using x_uq = typename EmuCore::TMP::remove_ref_cv<X_>::type;
		using y_uq = typename EmuCore::TMP::remove_ref_cv<Y_>::type;
		using z_uq = typename EmuCore::TMP::remove_ref_cv<Z_>::type;
		using w_uq = typename EmuCore::TMP::remove_ref_cv<W_>::type;
		using out_t_uq = typename EmuCore::TMP::remove_ref_cv<OutT_>::type;
		using calc_fp = typename EmuCore::TMP::largest_floating_point
		<
			out_t_uq, x_uq, y_uq, z_uq, w_uq, typename out_quaternion::preferred_floating_point
		>::type;

		constexpr bool all_castable =
		(
			EmuCore::TMP::is_static_castable_v<typename EmuCore::TMP::forward_result<X_>::type, calc_fp> &&
			EmuCore::TMP::is_static_castable_v<typename EmuCore::TMP::forward_result<Y_>::type, calc_fp> &&
			EmuCore::TMP::is_static_castable_v<typename EmuCore::TMP::forward_result<Z_>::type, calc_fp> &&
			EmuCore::TMP::is_static_castable_v<typename EmuCore::TMP::forward_result<W_>::type, calc_fp>
		);

		if constexpr (!all_castable)
		{
			static_assert
			(
				!StaticAssert_,
				"Invalid Quaternion Conjugate arguments: At least one item out of the X, Y, Z, and W components cannot be converted to the determined calculation type."
			);
			return false;
		}
		else
		{
			using negate_func = EmuCore::do_negate<calc_fp>;
			if constexpr (!std::is_invocable_v<negate_func, calc_fp>)
			{
				static_assert
				(
					!StaticAssert_,
					"Invalid Quaternion Conjugate operation: The determined negation function cannot be invoked with an argument of the determined calculation type."
				);
				return false;
			}
			else
			{
				using negate_result = typename std::invoke_result<negate_func, calc_fp>::type;
				if constexpr (std::is_void_v<negate_result>)
				{
					static_assert
					(
						!StaticAssert_,
						"Invalid Quaternion Conjugate operation: The determined negation function returns `void` when invoked with an argument of the determined calculation type."
					);
					return false;
				}
				else
				{
					using out_type = typename std::conditional<VectorOut_, typename out_quaternion::vector_type, out_quaternion>::type;
					if constexpr (!std::is_constructible_v<out_type, negate_result, negate_result, negate_result, typename EmuCore::TMP::forward_result<W_>::type>)
					{
						static_assert
						(
							!StaticAssert_,
							"Invalid Quaternion Conjugate output type: The output data cannot be constructed with negated X, Y, Z, and the passed W component, in the order XYZW."
						);
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

	template<bool VectorOut_, typename T_, typename OutT_, bool StaticAssert_>
	[[nodiscard]] constexpr inline bool _valid_conjugate_args()
	{
		using in_ref = const EmuMath::Quaternion<T_>&;
		return _valid_conjugate_args
		<
			VectorOut_,
			OutT_,
			decltype(_get_x(std::declval<in_ref>())),
			decltype(_get_y(std::declval<in_ref>())),
			decltype(_get_z(std::declval<in_ref>())),
			decltype(_get_w(std::declval<in_ref>())),
			StaticAssert_
		>();
	}

	template<bool VectorOut_, bool PreferMultiplies_, typename OutT_, typename X_, typename Y_, typename Z_, typename W_, typename Norm_, bool StaticAssert_ >
	[[nodiscard]] constexpr inline bool _valid_inverse_args()
	{
		using out_quaternion = EmuMath::Quaternion<OutT_>;
		using x_uq = typename EmuCore::TMP::remove_ref_cv<X_>::type;
		using y_uq = typename EmuCore::TMP::remove_ref_cv<Y_>::type;
		using z_uq = typename EmuCore::TMP::remove_ref_cv<Z_>::type;
		using w_uq = typename EmuCore::TMP::remove_ref_cv<W_>::type;
		using norm_uq = typename EmuCore::TMP::remove_ref_cv<Norm_>::type;
		using out_t_uq = typename EmuCore::TMP::remove_ref_cv<OutT_>::type;
		using calc_fp = typename EmuCore::TMP::largest_floating_point
		<
			out_t_uq, x_uq, y_uq, z_uq, w_uq, norm_uq, typename out_quaternion::preferred_floating_point
		>::type;

		constexpr bool all_castable =
		(
			EmuCore::TMP::is_static_castable_v<typename EmuCore::TMP::forward_result<X_>::type, calc_fp> &&
			EmuCore::TMP::is_static_castable_v<typename EmuCore::TMP::forward_result<Y_>::type, calc_fp> &&
			EmuCore::TMP::is_static_castable_v<typename EmuCore::TMP::forward_result<Z_>::type, calc_fp> &&
			EmuCore::TMP::is_static_castable_v<typename EmuCore::TMP::forward_result<W_>::type, calc_fp> &&
			EmuCore::TMP::is_static_castable_v<typename EmuCore::TMP::forward_result<Norm_>::type, calc_fp>
		);

		if constexpr (!all_castable)
		{
			static_assert
			(
				!StaticAssert_,
				"Invalid Quaternion Inverse arguments: At least one item out of the X, Y, Z, and W components and/or the Norm cannot be converted to the determined calculation type."
			);
			return false;
		}
		else
		{
			using negate_func = EmuCore::do_negate<calc_fp>;
			if constexpr (!std::is_invocable_v<negate_func, calc_fp>)
			{
				static_assert
				(
					!StaticAssert_,
					"Invalid Quaternion Inverse operation: The determined negation function cannot be invoked with an argument of the determined calculation type."
				);
				return false;
			}
			else
			{
				using negate_result = typename std::invoke_result<negate_func, calc_fp>::type;
				if constexpr (std::is_void_v<negate_result>)
				{
					static_assert
					(
						!StaticAssert_,
						"Invalid Quaternion Inverse operation: The determined negation function returns `void` when invoked with an argument of the determined calculation type."
					);
					return false;
				}
				else
				{
					if constexpr (PreferMultiplies_)
					{
						using reciprocal_func = EmuCore::do_reciprocal<calc_fp>;
						if constexpr (!std::is_invocable_v<reciprocal_func, calc_fp>)
						{
							static_assert
							(
								!StaticAssert_,
								"Invalid Quaternion Inverse operation (With PreferMultiplies_ = true): The determined reciprocal function cannot be invoked with an argument of the determined calculation type."
							);
							return false;
						}
						else
						{
							using reciprocal_result = typename std::invoke_result<reciprocal_func, calc_fp>::type;
							if constexpr (std::is_void_v<reciprocal_result>)
							{
								static_assert
								(
									!StaticAssert_,
									"Invalid Quaternion Inverse operation (With PreferMultiplies_ = true): The determined reciprocal function returns `void` when invoked with an argument of the determined calculation type."
								);
								return false;
							}
							else
							{
								using mul_func = EmuCore::do_multiply<calc_fp, calc_fp>;
								if constexpr (!std::is_invocable_v<mul_func, calc_fp, calc_fp>)
								{
									static_assert
									(
										!StaticAssert_,
										"Invalid Quaternion Inverse operation (With PreferMultiplies_ = true): The determined multiplication function cannot be invoked with two arguments of the determined calculation type."
									);
									return false;
								}
								else
								{
									using mul_result = typename std::invoke_result<mul_func, calc_fp, calc_fp>::type;
									if constexpr (std::is_void_v<mul_result>)
									{
										static_assert
										(
											!StaticAssert_,
											"Invalid Quaternion Inverse operation (With PreferMultiplies_ = true): The determined multiplication function returns `void` when invoked with an argument of the determined calculation type."
										);
										return false;
									}
									else
									{
										using out_type = typename std::conditional<VectorOut_, typename out_quaternion::vector_type, out_quaternion>::type;
										if constexpr (!std::is_constructible_v<out_type, mul_result, mul_result, mul_result, mul_result>)
										{
											static_assert
											(
												!StaticAssert_,
												"Invalid Quaternion Inverse Operation (With PreferMultiplies_ = true): The output type cannot be constructed from 4 results of the determined reciprocal multiplication function, representing X, Y, Z, and W respectively."
											);
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
					else
					{
						using div_func = EmuCore::do_divide<calc_fp, calc_fp>;
						if constexpr (!std::is_invocable_v<div_func, calc_fp, calc_fp>)
						{
							static_assert
							(
								!StaticAssert_,
								"Invalid Quaternion Inverse operation (With PreferMultiplies_ = false): The determined division function cannot be invoked with two arguments of the determined calculation type."
							);
							return false;
						}
						else
						{
							using div_result = typename std::invoke_result<div_func, calc_fp, calc_fp>::type;
							if constexpr (std::is_void_v<div_result>)
							{
								static_assert
								(
									!StaticAssert_,
									"Invalid Quaternion Inverse operation (With PreferMultiplies_ = false): The determined division function returns `void` when invoked with an argument of the determined calculation type."
								);
								return false;
							}
							else
							{
								using out_type = typename std::conditional<VectorOut_, typename out_quaternion::vector_type, out_quaternion>::type;
								if constexpr (!std::is_constructible_v<out_type, div_result, div_result, div_result, div_result>)
								{
									static_assert
									(
										!StaticAssert_,
										"Invalid Quaternion Inverse Operation (With PreferMultiplies_ = false): The output type cannot be constructed from 4 results of the determined division function, representing X, Y, Z, and W respectively."
									);
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

	template<bool Fused_, typename T_, typename Out_, bool StaticAssert_>
	[[nodiscard]] constexpr inline bool _valid_square_norm_args()
	{
		using out_uq = typename EmuCore::TMP::remove_ref_cv<Out_>::type;
		using calc_fp = typename EmuCore::TMP::largest_floating_point<typename EmuMath::Quaternion<T_>::preferred_floating_point, out_uq>::type;
		using in_ref = const EmuMath::Quaternion<T_>&;
		
		constexpr bool valid_cast =
		(
			EmuCore::TMP::is_static_castable_v<decltype(_get_x(std::declval<in_ref>())), calc_fp> &&
			EmuCore::TMP::is_static_castable_v<decltype(_get_y(std::declval<in_ref>())), calc_fp> &&
			EmuCore::TMP::is_static_castable_v<decltype(_get_z(std::declval<in_ref>())), calc_fp> &&
			EmuCore::TMP::is_static_castable_v<decltype(_get_w(std::declval<in_ref>())), calc_fp>
		);
		if constexpr (!valid_cast)
		{
			static_assert(!StaticAssert_, "Unable to calculate the Squared Norm of an EmuMath Quaternion, as at least one of its components (X, Y, Z, and/or W) cannot be cast to the determined calculation type.");
			return false;
		}
		else
		{
			using mul_func = EmuCore::do_multiply<calc_fp, calc_fp>;
			if constexpr (!std::is_invocable_r_v<calc_fp, mul_func, calc_fp, calc_fp>)
			{
				static_assert(!StaticAssert_, "Unable to calculate the Squared Norm of an EmuMath Quaternion, as the determined multiplication function cannot be invoked with two arguments of the determined calculation type while also returning a type that is either the determined calculation type or a type implicitly castable to it.");
				return false;
			}
			else
			{
				if constexpr (Fused_)
				{
					using fmadd_func = EmuCore::do_fmadd<calc_fp, calc_fp, calc_fp>;
					if constexpr (!std::is_invocable_r_v<calc_fp, fmadd_func, calc_fp, calc_fp, calc_fp>)
					{
						static_assert(!StaticAssert_, "Unable to calculate the Squared Norm of an EmuMath Quaternion (WITH fused operations), as the determined fused multiply-add function cannot be invoked with three arguments of the determined calculation type while also returning a type that is either the determined calculation type or a type implicitly castable to it.");
						return false;
					}
					else
					{
						if constexpr (!(EmuCore::TMP::is_static_castable_v<calc_fp&&, Out_> || std::is_same_v<Out_, calc_fp>))
						{
							static_assert(!StaticAssert_, "Unable to calculate the Squared Norm of an EmuMath Quaternion (WITH fused operations), as the output type is neither the exact same type as the determined calculation type nor castable to from an rvalue reference to it.");
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
					if constexpr (!std::is_invocable_r_v<calc_fp, add_func, calc_fp, calc_fp>)
					{
						static_assert(!StaticAssert_, "Unable to calculate the Squared Norm of an EmuMath Quaternion (WITHOUT fused operations), as the determined addition function cannot be invoked with two arguments of the determined calculation type while also returning a type that is either the determined calculation type or a type implicitly castable to it.");
						return false;
					}
					else
					{
						if constexpr (!(EmuCore::TMP::is_static_castable_v<calc_fp&&, Out_> || std::is_same_v<Out_, calc_fp>))
						{
							static_assert(!StaticAssert_, "Unable to calculate the Squared Norm of an EmuMath Quaternion (WITHOUT fused operations), as the output type is neither the exact same type as the determined calculation type nor castable to from an rvalue reference to it.");
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

	template<bool Fused_, bool IsConstexpr_, typename T_, typename Out_, bool StaticAssert_>
	[[nodiscard]] constexpr inline bool _valid_norm_args()
	{
		using out_uq = typename EmuCore::TMP::remove_ref_cv<Out_>::type;
		using calc_fp = typename EmuCore::TMP::largest_floating_point<typename EmuMath::Quaternion<T_>::preferred_floating_point, out_uq>::type;
		if constexpr (_valid_square_norm_args<Fused_, T_, Out_, StaticAssert_>())
		{
			using sqrt_func = typename std::conditional<IsConstexpr_, EmuCore::do_sqrt_constexpr<calc_fp>, EmuCore::do_sqrt<calc_fp>>::type;
			if constexpr (!std::is_invocable_v<sqrt_func, calc_fp>)
			{
				static_assert(!StaticAssert_, "Unable to calculate the Norm of an EmuMath Quaternion, as the determined sqrt function cannot be invoked with an argument of the deterined calculation type.");
				return false;
			}
			else
			{
				using sqrt_result = typename std::invoke_result<sqrt_func, calc_fp>::type;
				if constexpr (!std::is_constructible_v<Out_, sqrt_result>)
				{
					static_assert(!StaticAssert_, "Unable to calculate the Norm of an EmuMath Quaternion, as the output type cannot be constructed from the result of the determined sqrt function.");
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
			static_assert(!StaticAssert_, "Unable to calculate the Norm of an EmuMath Quaternion as the Squared Norm cannot be calculated. See other static assert messages for more info.");
			return false;
		}
	}

	template<bool VectorOut_, bool PreferMultiplies_, bool Fused_, bool IsConstexpr_, typename T_, typename OutT_, bool StaticAssert_>
	[[nodiscard]] constexpr inline bool _valid_inverse_args()
	{
		using in_ref = const EmuMath::Quaternion<T_>&;
		using out_quaternion = EmuMath::Quaternion<OutT_>;
		using x_uq = typename EmuCore::TMP::remove_ref_cv<decltype(_get_x(std::declval<in_ref>()))>::type;
		using y_uq = typename EmuCore::TMP::remove_ref_cv<decltype(_get_y(std::declval<in_ref>()))>::type;
		using z_uq = typename EmuCore::TMP::remove_ref_cv<decltype(_get_z(std::declval<in_ref>()))>::type;
		using w_uq = typename EmuCore::TMP::remove_ref_cv<decltype(_get_w(std::declval<in_ref>()))>::type;
		using out_t_uq = typename EmuCore::TMP::remove_ref_cv<OutT_>::type;
		using calc_fp = typename EmuCore::TMP::largest_floating_point
		<
			out_t_uq, x_uq, y_uq, z_uq, w_uq, typename out_quaternion::preferred_floating_point
		>::type;
		if constexpr (_valid_norm_args<Fused_, IsConstexpr_, T_, calc_fp, StaticAssert_>())
		{
			return _valid_inverse_args
			<
				VectorOut_,
				PreferMultiplies_,
				OutT_,
				decltype(_get_x(std::declval<in_ref>())),
				decltype(_get_y(std::declval<in_ref>())),
				decltype(_get_z(std::declval<in_ref>())),
				decltype(_get_w(std::declval<in_ref>())),
				calc_fp,
				StaticAssert_
			>();
		}
		else
		{
			static_assert
			(
				!StaticAssert_,
				"Unable to calculate the normalised inverse of an EmuMath Quaternion as the Norm cannot successfully be calculated. See other static assert messages for more info."
			);
		}
	}

	template<bool Assigning_, bool VectorOut_, bool Fused_, bool IsConstexpr_, bool PreferMultiplies_, typename OutT_, typename T_, bool StaticAssert_>
	[[nodiscard]] constexpr inline bool _valid_unit_args()
	{
		using in_ref = typename std::conditional<Assigning_, EmuMath::Quaternion<T_>&, const EmuMath::Quaternion<T_>&>::type;
		using out_quaternion = EmuMath::Quaternion<OutT_>;
		using x_uq = typename EmuCore::TMP::remove_ref_cv<decltype(_get_x(std::declval<in_ref>()))>::type;
		using y_uq = typename EmuCore::TMP::remove_ref_cv<decltype(_get_y(std::declval<in_ref>()))>::type;
		using z_uq = typename EmuCore::TMP::remove_ref_cv<decltype(_get_z(std::declval<in_ref>()))>::type;
		using w_uq = typename EmuCore::TMP::remove_ref_cv<decltype(_get_w(std::declval<in_ref>()))>::type;
		using out_t_uq = typename EmuCore::TMP::remove_ref_cv<OutT_>::type;
		using calc_fp = typename EmuCore::TMP::largest_floating_point
		<
			out_t_uq, x_uq, y_uq, z_uq, w_uq, typename out_quaternion::preferred_floating_point
		>::type;

		if constexpr (_valid_norm_args<Fused_, IsConstexpr_, T_, calc_fp, StaticAssert_>())
		{
			using div_func = typename std::conditional<PreferMultiplies_, EmuCore::do_multiply<calc_fp, calc_fp>, EmuCore::do_divide<calc_fp, calc_fp>>::type;
			if constexpr (PreferMultiplies_)
			{
				using reciprocal_func = EmuCore::do_reciprocal<calc_fp>;
				if constexpr (!std::is_invocable_r_v<calc_fp, reciprocal_func, calc_fp>)
				{
					static_assert(!StaticAssert_, "Unable to calculate a Unit Quaternion (with PreferMultiplies_ = true) as the determined reciprocal function cannot be invoked with an argument of the determined calculation type while also returning said type.");
					return false;
				}
			}

			if constexpr (!std::is_invocable_v<div_func, calc_fp, calc_fp>)
			{
				static_assert(!StaticAssert_, "Unable to calculate a Unit Quaternion as the determined division function cannot be invoked with two arguments of the determined calculation type.");
				return false;
			}
			else
			{
				using div_result = typename std::invoke_result<div_func, calc_fp, calc_fp>::type;
				using out_type = typename std::conditional<VectorOut_, typename out_quaternion::vector_type, out_quaternion>::type;
				if constexpr (Assigning_)
				{
					using out_value_uq = typename out_type::value_type_uq;
					constexpr bool all_assignable =  EmuCore::TMP::valid_assign_direct_or_cast<out_value_uq, div_result, decltype(_get_x(std::declval<in_ref>()))>();
					if constexpr (!all_assignable)
					{
						static_assert(!StaticAssert_, "Unable to calculate a Unit Quaternion as the output Quaternion cannot have its X, Y, Z, and W components individually assigned from the result of respective invocations of the determined division function.");
						return false;
					}
					else
					{
						return true;
					}
				}
				else
				{
					if constexpr (!std::is_constructible_v<out_type, div_result, div_result, div_result, div_result>)
					{
						static_assert(!StaticAssert_, "Unable to calculate a Unit Quaternion as the output data cannot be constructed from 4 results of invoking the determined division function, with arguments representing the X, Y, Z, and W components respectively.");
						return false;
					}
					else
					{
						return true;
					}
				}
			}
		}
		else
		{
			static_assert
			(
				!StaticAssert_,
				"Unable to calculate a Unit Quaternion as the input Quaternion's norm cannot be calculated. See other static assert messages for more info."
			);
			return false;
		}
	}
#pragma endregion

#pragma region CONJUGATE_FUNCS
	template<bool VectorOut_, typename OutT_, typename X_, typename Y_, typename Z_, typename W_>
	[[nodiscard]] constexpr inline auto _make_conjugate(X_&& x_, Y_&& y_, Z_&& z_, W_&& w_)
		-> typename std::conditional<VectorOut_, typename EmuMath::Quaternion<OutT_>::vector_type, EmuMath::Quaternion<OutT_>>::type
	{
		if constexpr (_valid_conjugate_args<VectorOut_, OutT_, X_, Y_, Z_, W_, true>())
		{
			using out_quaternion = EmuMath::Quaternion<OutT_>;
			using x_uq = typename EmuCore::TMP::remove_ref_cv<X_>::type;
			using y_uq = typename EmuCore::TMP::remove_ref_cv<Y_>::type;
			using z_uq = typename EmuCore::TMP::remove_ref_cv<Z_>::type;
			using w_uq = typename EmuCore::TMP::remove_ref_cv<W_>::type;
			using out_t_uq = typename EmuCore::TMP::remove_ref_cv<OutT_>::type;
			using calc_fp = typename EmuCore::TMP::largest_floating_point
			<
				out_t_uq, x_uq, y_uq, z_uq, w_uq, typename out_quaternion::preferred_floating_point
			>::type;

			calc_fp x = static_cast<calc_fp>(std::forward<X_>(x_));
			calc_fp y = static_cast<calc_fp>(std::forward<Y_>(y_));
			calc_fp z = static_cast<calc_fp>(std::forward<Z_>(z_));

			using negate_func = EmuCore::do_negate<calc_fp>;
			using out_type = typename std::conditional<VectorOut_, typename out_quaternion::vector_type, out_quaternion>::type;
			return out_type
			(
				negate_func()(x),
				negate_func()(y),
				negate_func()(z),
				std::forward<W_>(w_)
			);
		}
		else
		{
			static_assert
			(
				EmuCore::TMP::get_false<OutT_, X_, Y_, Z_, W_>(),
				"Invalid Quaternion Conjugate operation. See other static assertion messages for more information."
			);
		}
	}

	template<bool VectorOut_, typename OutT_, typename T_>
	[[nodiscard]] constexpr inline auto _make_conjugate(const EmuMath::Quaternion<T_>& quaternion_)
		-> typename std::conditional<VectorOut_, typename EmuMath::Quaternion<OutT_>::vector_type, EmuMath::Quaternion<OutT_>>::type
	{
		return _make_conjugate<VectorOut_, OutT_>
		(
			_get_x(quaternion_),
			_get_y(quaternion_),
			_get_z(quaternion_),
			_get_w(quaternion_)
		);
	}
#pragma endregion

#pragma region NORM_FUNCS
	template<bool Fused_, typename Out_, typename T_>
	[[nodiscard]] constexpr inline Out_ _make_square_norm(const EmuMath::Quaternion<T_>& quaternion_)
	{
		if constexpr (_valid_square_norm_args<Fused_, T_, Out_, true>())
		{
			using out_uq = typename EmuCore::TMP::remove_ref_cv<Out_>::type;
			using calc_fp = typename EmuCore::TMP::largest_floating_point<typename EmuMath::Quaternion<T_>::preferred_floating_point, out_uq>::type;
			calc_fp x = static_cast<calc_fp>(_get_x(quaternion_));
			calc_fp y = static_cast<calc_fp>(_get_y(quaternion_));
			calc_fp z = static_cast<calc_fp>(_get_z(quaternion_));

			using mul_func = EmuCore::do_multiply<calc_fp, calc_fp>;
			calc_fp sqr_norm = static_cast<calc_fp>(_get_w(quaternion_));
			sqr_norm = mul_func()(sqr_norm, sqr_norm);

			if constexpr (Fused_)
			{
				using fmadd_func = EmuCore::do_fmadd<calc_fp, calc_fp, calc_fp>;
				sqr_norm = fmadd_func()(x, x, sqr_norm);
				sqr_norm = fmadd_func()(y, y, sqr_norm);
				sqr_norm = fmadd_func()(z, z, sqr_norm);
			}
			else
			{
				using add_func = EmuCore::do_add<calc_fp, calc_fp>;
				sqr_norm = add_func()(sqr_norm, mul_func()(x, x));
				sqr_norm = add_func()(sqr_norm, mul_func()(y, y));
				sqr_norm = add_func()(sqr_norm, mul_func()(z, z));
			}

			if constexpr (std::is_same_v<calc_fp, Out_>)
			{
				return sqr_norm;
			}
			else
			{
				return static_cast<Out_>(std::move(sqr_norm));
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<T_>(), "Invalid Quaternion Square Norm operation. See other static assert messages for more information.");
		}
	}

	template<bool Fused_, bool IsConstexpr_, typename Out_, typename T_>
	[[nodiscard]] constexpr inline Out_ _make_norm(const EmuMath::Quaternion<T_>& quaternion_)
	{
		using out_uq = typename EmuCore::TMP::remove_ref_cv<Out_>::type;
		using calc_fp = typename EmuCore::TMP::largest_floating_point<typename EmuMath::Quaternion<T_>::preferred_floating_point, out_uq>::type;
		if constexpr (_valid_norm_args<Fused_, IsConstexpr_, T_, Out_, true>())
		{
			using sqrt_func = typename std::conditional<IsConstexpr_, EmuCore::do_sqrt_constexpr<calc_fp>, EmuCore::do_sqrt<calc_fp>>::type;
			return Out_(sqrt_func()(_make_square_norm<Fused_, calc_fp>(quaternion_)));
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Out_>(), "Invalid Quaternion Norm operation. See other static assert messages for more information.");
		}
	}
#pragma endregion

#pragma region INVERSE_FUNCS
	template<bool VectorOut_, bool PreferMultiplies_, typename OutT_, typename X_, typename Y_, typename Z_, typename W_, typename Norm_ >
	[[nodiscard]] constexpr inline auto _make_inverse(X_&& x_, Y_&& y_, Z_&& z_, W_&& w_, Norm_&& norm_)
		-> typename std::conditional<VectorOut_, typename EmuMath::Quaternion<OutT_>::vector_type, EmuMath::Quaternion<OutT_>>::type
	{
		if constexpr(_valid_inverse_args<VectorOut_, PreferMultiplies_, OutT_, X_, Y_, Z_, W_, Norm_, true>())
		{
			using out_quaternion = EmuMath::Quaternion<OutT_>;
			using x_uq = typename EmuCore::TMP::remove_ref_cv<X_>::type;
			using y_uq = typename EmuCore::TMP::remove_ref_cv<Y_>::type;
			using z_uq = typename EmuCore::TMP::remove_ref_cv<Z_>::type;
			using w_uq = typename EmuCore::TMP::remove_ref_cv<W_>::type;
			using norm_uq = typename EmuCore::TMP::remove_ref_cv<Norm_>::type;
			using out_t_uq = typename EmuCore::TMP::remove_ref_cv<OutT_>::type;
			using calc_fp = typename EmuCore::TMP::largest_floating_point
			<
				out_t_uq, x_uq, y_uq, z_uq, w_uq, norm_uq, typename out_quaternion::preferred_floating_point
			>::type;

			using negate_func = EmuCore::do_negate<calc_fp>;
			using out_type = typename std::conditional<VectorOut_, typename out_quaternion::vector_type, out_quaternion>::type;
			if constexpr (PreferMultiplies_)
			{
				using mul_func = EmuCore::do_multiply<calc_fp, calc_fp>;
				using reciprocal_func = EmuCore::do_reciprocal<calc_fp>;
				calc_fp norm_reciprocal = reciprocal_func()(static_cast<calc_fp>(std::forward<Norm_>(norm_)));
				return out_type
				(
					mul_func()(norm_reciprocal, negate_func()(static_cast<calc_fp>(std::forward<X_>(x_)))),
					mul_func()(norm_reciprocal, negate_func()(static_cast<calc_fp>(std::forward<Y_>(y_)))),
					mul_func()(norm_reciprocal, negate_func()(static_cast<calc_fp>(std::forward<Z_>(z_)))),
					mul_func()(norm_reciprocal, static_cast<calc_fp>(std::forward<W_>(w_)))
				);
			}
			else
			{
				using div_func = EmuCore::do_divide<calc_fp, calc_fp>;
				calc_fp norm = static_cast<calc_fp>(std::forward<Norm_>(norm_));
				return out_type
				(
					div_func()(negate_func()(static_cast<calc_fp>(std::forward<X_>(x_))), norm),
					div_func()(negate_func()(static_cast<calc_fp>(std::forward<Y_>(y_))), norm),
					div_func()(negate_func()(static_cast<calc_fp>(std::forward<Z_>(z_))), norm),
					div_func()(static_cast<calc_fp>(std::forward<W_>(w_)), norm)
				);
			}
		}
		else
		{
			static_assert
			(
				EmuCore::TMP::get_false<OutT_, X_, Y_, Z_, W_>(),
				"Invalid Quaternion Inverse operation. See other static assertion messages for more information."
			);
		}
	}

	template<bool VectorOut_, bool PreferMultiplies_, bool Fused_, bool IsConstexpr_, typename OutT_, typename T_>
	[[nodiscard]] constexpr inline EmuMath::Quaternion<OutT_> _make_inverse(const EmuMath::Quaternion<T_>& quaternion_)
	{
		using in_ref = const EmuMath::Quaternion<T_>&;
		using out_quaternion = EmuMath::Quaternion<OutT_>;
		using x_uq = typename EmuCore::TMP::remove_ref_cv<decltype(_get_x(quaternion_))>::type;
		using y_uq = typename EmuCore::TMP::remove_ref_cv<decltype(_get_y(quaternion_))>::type;
		using z_uq = typename EmuCore::TMP::remove_ref_cv<decltype(_get_z(quaternion_))>::type;
		using w_uq = typename EmuCore::TMP::remove_ref_cv<decltype(_get_w(quaternion_))>::type;
		using out_t_uq = typename EmuCore::TMP::remove_ref_cv<OutT_>::type;
		using calc_fp = typename EmuCore::TMP::largest_floating_point
		<
			out_t_uq, x_uq, y_uq, z_uq, w_uq, typename out_quaternion::preferred_floating_point
		>::type;
		return _make_inverse<VectorOut_, PreferMultiplies_, OutT_>
		(
			_get_x(quaternion_),
			_get_y(quaternion_),
			_get_z(quaternion_),
			_get_w(quaternion_),
			_make_norm<Fused_, IsConstexpr_, calc_fp>(quaternion_)
		);
	}
#pragma endregion

#pragma region UNIT_FUNCS
	template<bool Assigning_, bool VectorOut_, bool Fused_, bool IsConstexpr_, bool PreferMultiplies_, typename OutT_, typename InQuaternion_>
	constexpr inline auto _make_unit_impl(InQuaternion_& quaternion_) // Accepts any lval, but explicit const+typearg may be needed in calls
		-> typename std::conditional
		<
			Assigning_,
			void,
			typename std::conditional<VectorOut_, typename EmuMath::Quaternion<OutT_>::vector_type, EmuMath::Quaternion<OutT_>>::type
		>::type
	{
		using in_uq = typename EmuCore::TMP::remove_ref_cv<InQuaternion_>::type;
		using in_t = typename EmuCore::TMP::type_argument<in_uq>::type;
		if constexpr(!Assigning_ || !std::is_const_v<InQuaternion_>)
		{
			if constexpr (_valid_unit_args<Assigning_, VectorOut_, Fused_, IsConstexpr_, Assigning_, OutT_, in_t, true>())
			{
				using out_quaternion = EmuMath::Quaternion<OutT_>;
				using x_uq = typename EmuCore::TMP::remove_ref_cv<decltype(_get_x(std::forward<InQuaternion_>(quaternion_)))>::type;
				using y_uq = typename EmuCore::TMP::remove_ref_cv<decltype(_get_y(std::forward<InQuaternion_>(quaternion_)))>::type;
				using z_uq = typename EmuCore::TMP::remove_ref_cv<decltype(_get_z(std::forward<InQuaternion_>(quaternion_)))>::type;
				using w_uq = typename EmuCore::TMP::remove_ref_cv<decltype(_get_w(std::forward<InQuaternion_>(quaternion_)))>::type;
				using out_t_uq = typename EmuCore::TMP::remove_ref_cv<OutT_>::type;
				using calc_fp = typename EmuCore::TMP::largest_floating_point
				<
					out_t_uq, x_uq, y_uq, z_uq, w_uq, typename out_quaternion::preferred_floating_point
				>::type;
				calc_fp norm = _make_norm<Fused_, IsConstexpr_, calc_fp>(std::forward<InQuaternion_>(quaternion_));
				if constexpr (PreferMultiplies_)
				{
					norm = EmuCore::do_reciprocal<calc_fp>()(norm);
				}

				using div_func = typename std::conditional<PreferMultiplies_, EmuCore::do_multiply<calc_fp, calc_fp>, EmuCore::do_divide<calc_fp, calc_fp>>::type;
				if constexpr (Assigning_)
				{
					using in_value_uq = typename in_uq::value_type_uq;
					EmuCore::TMP::assign_direct_or_cast<in_value_uq>(_get_x(quaternion_), div_func()(_get_x(quaternion_), norm));
					EmuCore::TMP::assign_direct_or_cast<in_value_uq>(_get_y(quaternion_), div_func()(_get_y(quaternion_), norm));
					EmuCore::TMP::assign_direct_or_cast<in_value_uq>(_get_z(quaternion_), div_func()(_get_z(quaternion_), norm));
					EmuCore::TMP::assign_direct_or_cast<in_value_uq>(_get_w(quaternion_), div_func()(_get_w(quaternion_), norm));
				}
				else
				{
					using out_type = typename std::conditional<VectorOut_, typename out_quaternion::vector_type, out_quaternion>::type;
					return out_type
					(
						div_func()(_get_x(quaternion_), norm),
						div_func()(_get_y(quaternion_), norm),
						div_func()(_get_z(quaternion_), norm),
						div_func()(_get_w(quaternion_), norm)
					);
				}
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<OutT_>(), "Failed to calculate a Unit Quaternion. See other static assert messages for more info.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<InQuaternion_>(), "Failed to calculate a Unit Quaternion as it was indicated to output to the input Quaternion, but the Quaternion does not match the requirements (it must be a lvalue, non-const reference).");
		}
	}

	template<bool VectorOut_, bool Fused_, bool IsConstexpr_, bool PreferMultiplies_, typename OutT_, typename T_>
	[[nodiscard]] constexpr inline decltype(auto) _make_unit(const EmuMath::Quaternion<T_>& quaternion_)
	{
		return _make_unit_impl<false, VectorOut_, Fused_, IsConstexpr_, PreferMultiplies_, OutT_, const EmuMath::Quaternion<T_>>(quaternion_);
	}

	template<bool Fused_, bool IsConstexpr_, bool PreferMultiplies_, typename T_>
	constexpr inline void _assign_unit(EmuMath::Quaternion<T_>& quaternion_)
	{
		_make_unit_impl<true, false, Fused_, IsConstexpr_, PreferMultiplies_, T_, EmuMath::Quaternion<T_>>(quaternion_);
	}
#pragma endregion
}

#endif
