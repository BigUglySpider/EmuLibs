#ifndef EMU_MATH_QUATERNION_UNDERLYING_CONVERSIONS_H_INC_
#define EMU_MATH_QUATERNION_UNDERLYING_CONVERSIONS_H_INC_ 1

#include "_quaternion_tmp.h"
#include "_quaternion_underlying_get.h"

namespace EmuMath::Helpers::_quaternion_underlying
{
#pragma region VALIDITY_CHECKS
	template
	<
		bool VectorOut_, typename OutT_, typename X_, typename Y_, typename Z_,
		bool PreferMultiplies_, bool Normalise_, bool IsRads_, bool Fused_, bool IsConstexpr_, bool StaticAssert_
	>
	[[nodiscard]] static constexpr inline bool _valid_euler_conversion_args()
	{
		// Indentation in this gets a bit crazy due to the static_assert messages
		using out_quaternion = EmuMath::Quaternion<OutT_>;
		using x_uq = typename EmuCore::TMP::remove_ref_cv<X_>::type;
		using y_uq = typename EmuCore::TMP::remove_ref_cv<Y_>::type;
		using z_uq = typename EmuCore::TMP::remove_ref_cv<Z_>::type;
		using calc_fp = typename EmuCore::TMP::largest_floating_point<x_uq, y_uq, z_uq, typename out_quaternion::preferred_floating_point>::type;

		if constexpr (!EmuCore::TMP::is_static_castable_v<typename EmuCore::TMP::forward_result<X_>::type, calc_fp>)
		{
			static_assert
			(
				!StaticAssert_,
				"Unable to perform a Euler -> Quaternion conversion as the X argument cannot be reliably used as a suitable floating-point based on other values."
			);
			return false;
		}
		else if constexpr (!EmuCore::TMP::is_static_castable_v<typename EmuCore::TMP::forward_result<Y_>::type, calc_fp>)
		{
			static_assert
			(
				!StaticAssert_,
				"Unable to perform a Euler -> Quaternion conversion as the Y argument cannot be reliably used as a suitable floating-point based on other values."
			);
			return false;
		}
		else if constexpr (!EmuCore::TMP::is_static_castable_v<typename EmuCore::TMP::forward_result<Z_>::type, calc_fp>)
		{
			static_assert
			(
				!StaticAssert_,
				"Unable to perform a Euler -> Quaternion conversion as the Z argument cannot be reliably used as a suitable floating-point based on other values."
			);
			return false;
		}
		else
		{
			using division_func_type = typename std::conditional
			<
				PreferMultiplies_,
				EmuCore::do_multiply<calc_fp, calc_fp>,
				EmuCore::do_divide<calc_fp, calc_fp>
			>::type;
			if constexpr (!std::is_invocable_r_v<calc_fp, division_func_type&, calc_fp, calc_fp>)
			{
				static_assert
				(
					!StaticAssert_,
					"Unable to perform a Euler -> Quaternion conversion as the determined function for dividing cannot successfully be invoked."
				);
				return false;
			}
			else
			{
				using cos_func_type = typename std::conditional
				<
					IsConstexpr_,
					EmuCore::do_cos_constexpr<calc_fp>,
					EmuCore::do_cos<calc_fp>
				>::type;

				if constexpr (!std::is_invocable_r_v<calc_fp, cos_func_type&, calc_fp>)
				{
					static_assert
					(
						!StaticAssert_,
						"Unable to perform a Euler -> Quaternion conversion as the determined cosine function cannot successfully be invoked."
					);
					return false;
				}
				else
				{
					using sin_func_type = typename std::conditional
					<
						IsConstexpr_,
						EmuCore::do_sin_constexpr<calc_fp>,
						EmuCore::do_sin<calc_fp>
					>::type;
					if constexpr (!std::is_invocable_r_v<calc_fp, sin_func_type&, calc_fp>)
					{
						static_assert
						(
							!StaticAssert_,
							"Unable to perform a Euler -> Quaternion conversion as the determined sine function cannot successfully be invoked."
						);
						return false;
					}
					else
					{
						using mul_func_type = EmuCore::do_multiply<calc_fp, calc_fp>;
						if constexpr (!std::is_invocable_r_v<calc_fp, mul_func_type&, calc_fp, calc_fp>)
						{
							static_assert
							(
								!StaticAssert_,
								"Unable to perform a Euler -> Quaternion conversion as the determined multiplication function cannot successfully be invoked."
							);
							return false;
						}
						else
						{
							using add_func_type = EmuCore::do_add<calc_fp, calc_fp>;
							if constexpr (!std::is_invocable_r_v<calc_fp, add_func_type, calc_fp, calc_fp>)
							{
								static_assert
								(
									!StaticAssert_,
									"Unable to perform a Euler -> Quaternion conversion as the determined addition function cannot successfully be invoked."
								);
								return false;
							}
							else
							{
								if constexpr (Fused_)
								{
									using fmadd_func = EmuCore::do_fmadd<calc_fp, calc_fp, calc_fp>;
									if constexpr (!std::is_invocable_r_v<calc_fp, fmadd_func, calc_fp, calc_fp, calc_fp>)
									{
										static_assert
										(
											!StaticAssert_,
											"Unable to perform a Euler -> Quaternion conversion (WITH fused operations) as the determined fused multiply-add function cannot successfully be invoked."
										);
										return false;
									}
									else
									{
										using fmsub_func = EmuCore::do_fmsub<calc_fp, calc_fp, calc_fp>;
										if constexpr (!std::is_invocable_r_v<calc_fp, fmsub_func, calc_fp, calc_fp, calc_fp>)
										{
											static_assert
											(
												!StaticAssert_,
												"Unable to perform a Euler -> Quaternion conversion (WITH fused operations) as the determined fused multiply-subtract function cannot successfully be invoked."
											);
											return false;
										}
									}
								}

								constexpr bool can_get_rads_if_needed = 
								(
									IsRads_ ||
									std::is_invocable_r_v<calc_fp, decltype(EmuCore::Pi::DegsToRads<calc_fp>), calc_fp>
								);
								if constexpr (!can_get_rads_if_needed)
								{
									static_assert
									(
										!StaticAssert_,
										"Unable to perform a Euler -> Quaternion conversion as the passed Euler angles have been identified as degrees, but cannot successfully be converted to radians."
									);
									return false;
								}
								else
								{
									using sub_func_type = EmuCore::do_subtract<calc_fp, calc_fp>;
									if constexpr (!std::is_invocable_r_v<calc_fp, sub_func_type&, calc_fp, calc_fp>)
									{
										static_assert
										(
											!StaticAssert_,
											"Unable to perform a Euler -> Quaternion conversion as the determined subtraction function cannot successfully be invoked."
										);
										return false;
									}
									else
									{
										using out_type = typename std::conditional<VectorOut_, typename out_quaternion::vector_type, out_quaternion>::type;
										if constexpr (Normalise_)
										{
											using sqrt_func = typename std::conditional<IsConstexpr_, EmuCore::do_sqrt_constexpr<calc_fp>, EmuCore::do_sqrt<calc_fp>>::type;
											if constexpr (!std::is_invocable_r_v<calc_fp, sqrt_func, calc_fp>)
											{
												static_assert
												(
													!StaticAssert_,
													"Unable to perform a Euler -> Quaternion conversion (WITH normalisation) as the determined sqrt function cannot successfully be invoked."
												);
												return false;
											}
											else
											{
												if constexpr (PreferMultiplies_)
												{
													using reciprocal_func = EmuCore::do_reciprocal<calc_fp>;
													if constexpr (!std::is_invocable_r_v<calc_fp, reciprocal_func, calc_fp>)
													{
														static_assert
														(
															!StaticAssert_,
															"Unable to perform a Euler -> Quaternion conversion (WITH normalisation AND a preference for multiplication) as the determined reciprocal function cannot successfully be invoked."
														);
														return false;
													}															
												}
												else
												{
													using div_result = typename std::invoke_result<division_func_type, calc_fp, calc_fp>::type;
													if constexpr (!std::is_constructible_v<out_type, div_result, div_result, div_result, div_result>)
													{
														static_assert
														(
															!StaticAssert_,
															"Unable to perform a Euler -> Quaternion conversion (WITHOUT normalisation) as the underlying data cannot be constructed from 4 results of the determined division function type."
														);
														return false;;
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
											using move_fp_result = decltype(std::move(std::declval<calc_fp>()));
											if constexpr (!std::is_constructible_v<out_type, move_fp_result, move_fp_result, move_fp_result, move_fp_result>)
											{
												static_assert
												(
													!StaticAssert_,
													"Unable to perform a Euler -> Quaternion conversion (WITHOUT normalisation) as the underlying data cannot be constructed from 4 rvalues of the determined calculation type."
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
			}
		}
	}

	template
	<
		bool VectorOut_, typename OutT_, std::size_t VecSize_, typename VecT_, std::size_t ReadOffset_, bool IsConst_,
		bool PreferMultiplies_, bool Normalise_, bool IsRads_, bool Fused_, bool IsConstexpr_, bool StaticAssert_
	>
	[[nodiscard]] static constexpr inline bool _valid_euler_vector_lvalue_conversion_arg()
	{
		using in_vector = typename std::conditional<IsConst_, const EmuMath::Vector<VecSize_, VecT_>&, EmuMath::Vector<VecSize_, VecT_>&>::type;
		using in_x = decltype(std::declval<in_vector>().template AtTheoretical<ReadOffset_>());
		using in_y = decltype(std::declval<in_vector>().template AtTheoretical<ReadOffset_ + 1>());
		using in_z = decltype(std::declval<in_vector>().template AtTheoretical<ReadOffset_ + 2>());
		return _valid_euler_conversion_args<VectorOut_, OutT_, in_x, in_y, in_z, PreferMultiplies_, Normalise_, IsRads_, Fused_, IsConstexpr_, StaticAssert_>();
	}

	template
	<
		bool VectorOut_, typename OutT_, std::size_t VecSize_, typename VecT_, std::size_t ReadOffset_,
		bool PreferMultiplies_, bool Normalise_, bool IsRads_, bool Fused_, bool IsConstexpr_, bool StaticAssert_
	>
	[[nodiscard]] static constexpr inline bool _valid_euler_vector_rvalue_conversion_arg()
	{
		using in_vector = EmuMath::Vector<VecSize_, VecT_>&&;
		using in_x = decltype(_conditional_quaternion_vector_move_get<ReadOffset_>(std::forward<in_vector>(std::declval<in_vector>())));
		using in_y = decltype(_conditional_quaternion_vector_move_get<ReadOffset_ + 1>(std::forward<in_vector>(std::declval<in_vector>())));
		using in_z = decltype(_conditional_quaternion_vector_move_get<ReadOffset_ + 2>(std::forward<in_vector>(std::declval<in_vector>())));
		return _valid_euler_conversion_args<VectorOut_, OutT_, in_x, in_y, in_z, PreferMultiplies_, Normalise_, IsRads_, Fused_, IsConstexpr_, StaticAssert_>();
	}
#pragma endregion

#pragma region FROM_EULER_CONVERSION_FUNCS
	template
	<
		bool VectorOut_, bool IsRads_, bool PreferMultiplies_, bool Normalise_, bool Fused_, bool IsConstexpr_,
		typename OutT_, typename X_, typename Y_, typename Z_
	>
	[[nodiscard]] static constexpr inline auto _make_from_euler(X_&& euler_x_, Y_&& euler_y_, Z_&& euler_z_)
		-> typename std::conditional<VectorOut_, typename EmuMath::Quaternion<OutT_>::vector_type, EmuMath::Quaternion<OutT_>>::type
	{
		if constexpr (_valid_euler_conversion_args<VectorOut_, OutT_, X_, Y_, Z_, PreferMultiplies_, Normalise_, IsRads_, Fused_, IsConstexpr_, true>())
		{
			// Common info
			// --- We use the largest floating-point type for calculation (including preferred fp type),
			// --- as passing greater-accuracy fp suggests a desire for greater-accuracy calculation results
			using out_quaternion = EmuMath::Quaternion<OutT_>;
			using x_uq = typename EmuCore::TMP::remove_ref_cv<X_>::type;
			using y_uq = typename EmuCore::TMP::remove_ref_cv<Y_>::type;
			using z_uq = typename EmuCore::TMP::remove_ref_cv<Z_>::type;
			using calc_fp = typename EmuCore::TMP::largest_floating_point<x_uq, y_uq, z_uq, typename out_quaternion::preferred_floating_point>::type;
			
			// --- START of common function types determination
			// Prepare division function - If `PreferMultiplies_` is true, this will be intended for use as a reciprocal multiplication
			using div_func = typename std::conditional
			<
				PreferMultiplies_,
				EmuCore::do_multiply<calc_fp, calc_fp>,
				EmuCore::do_divide<calc_fp, calc_fp>
			>::type;

			// Prepare trivial functions
			using add_func = EmuCore::do_add<calc_fp, calc_fp>;
			using sub_func = EmuCore::do_subtract<calc_fp, calc_fp>;
			using mul_func = EmuCore::do_multiply<calc_fp, calc_fp>;

			// Prepare trig functions
			using cos_func = typename std::conditional
			<
				IsConstexpr_,
				EmuCore::do_cos_constexpr<calc_fp>,
				EmuCore::do_cos<calc_fp>
			>::type;
			using sin_func = typename std::conditional
			<
				IsConstexpr_,
				EmuCore::do_sin_constexpr<calc_fp>,
				EmuCore::do_sin<calc_fp>
			>::type;

			// --- END of common function types determination
			// --- START of common calculations
			// Convert values to calculation type
			calc_fp pitch_sin = static_cast<calc_fp>(std::forward<X_>(euler_x_));
			calc_fp yaw_sin = static_cast<calc_fp>(std::forward<Y_>(euler_y_));
			calc_fp roll_sin = static_cast<calc_fp>(std::forward<Z_>(euler_z_));

			// Deg->Rad if needed
			if constexpr (!IsRads_)
			{
				pitch_sin = EmuCore::Pi::DegsToRads(pitch_sin);
				yaw_sin = EmuCore::Pi::DegsToRads(yaw_sin);
				roll_sin = EmuCore::Pi::DegsToRads(roll_sin);
			}

			// Set these values to angle / 2
			constexpr calc_fp div_by_2_rhs = PreferMultiplies_ ? calc_fp(0.5) : calc_fp(2);
			pitch_sin = div_func()(pitch_sin, div_by_2_rhs);
			yaw_sin = div_func()(yaw_sin, div_by_2_rhs);
			roll_sin = div_func()(roll_sin, div_by_2_rhs);

			// Find cosines
			calc_fp pitch_cos = cos_func()(pitch_sin);
			calc_fp yaw_cos = cos_func()(yaw_sin);
			calc_fp roll_cos = cos_func()(roll_sin);

			// Finally set these vars to their names by finding sines
			pitch_sin = sin_func()(pitch_sin);
			yaw_sin = sin_func()(yaw_sin);
			roll_sin = sin_func()(roll_sin);

			// Common values used in component calculations - avoids extra multiplies
			// --- We cache roll * pitch calculations only for consistency in formatting to make code more readable
			calc_fp roll_sin_MUL_pitch_sin = mul_func()(roll_sin, pitch_sin);
			calc_fp roll_cos_MUL_pitch_cos = mul_func()(roll_cos, pitch_cos);
			calc_fp roll_sin_MUL_pitch_cos = mul_func()(roll_sin, pitch_cos);
			calc_fp roll_cos_MUL_pitch_sin = mul_func()(roll_cos, pitch_sin);

			// --- END of common calculations
			// --- START of quaternion components
			calc_fp x = mul_func()(roll_sin_MUL_pitch_cos, yaw_sin);
			calc_fp y = mul_func()(roll_sin_MUL_pitch_sin, yaw_cos);
			calc_fp z = mul_func()(roll_cos_MUL_pitch_sin, yaw_sin);
			calc_fp w = mul_func()(roll_sin_MUL_pitch_sin, yaw_sin);

			if constexpr (Fused_)
			{
				using fmadd_func = EmuCore::do_fmadd<calc_fp, calc_fp, calc_fp>;
				using fmsub_func = EmuCore::do_fmsub<calc_fp, calc_fp, calc_fp>;
				x = fmsub_func()(roll_cos_MUL_pitch_sin, yaw_cos, x);
				y = fmadd_func()(roll_cos_MUL_pitch_cos, yaw_sin, y);
				z = fmsub_func()(roll_sin_MUL_pitch_cos, yaw_cos, z);
				w = fmadd_func()(roll_cos_MUL_pitch_cos, yaw_cos, w);
			}
			else
			{
				x = sub_func()(mul_func()(roll_cos_MUL_pitch_sin, yaw_cos), x);
				y = add_func()(mul_func()(roll_cos_MUL_pitch_cos, yaw_sin), y);
				z = sub_func()(mul_func()(roll_sin_MUL_pitch_cos, yaw_cos), z);
				w = add_func()(mul_func()(roll_cos_MUL_pitch_cos, yaw_cos), w);
			}

			using out_type = typename std::conditional<VectorOut_, typename out_quaternion::vector_type, out_quaternion>::type;
			if constexpr (Normalise_)
			{
				calc_fp norm = mul_func()(x, x);

				if constexpr (Fused_)
				{
					using fmadd_func = EmuCore::do_fmadd<calc_fp, calc_fp, calc_fp>;
					norm = fmadd_func()(y, y, norm);
					norm = fmadd_func()(z, z, norm);
					norm = fmadd_func()(w, w, norm);
				}
				else
				{
					norm = add_func()(norm, mul_func()(y, y));
					norm = add_func()(norm, mul_func()(z, z));
					norm = add_func()(norm, mul_func()(w, w));
				}

				using sqrt_func = typename std::conditional<IsConstexpr_, EmuCore::do_sqrt_constexpr<calc_fp>, EmuCore::do_sqrt<calc_fp>>::type;
				norm = sqrt_func()(norm);

				if constexpr (PreferMultiplies_)
				{
					using reciprocal_func = EmuCore::do_reciprocal<calc_fp>;
					norm = reciprocal_func()(norm);
				}

				return out_type
				(
					div_func()(x, norm),
					div_func()(y, norm),
					div_func()(z, norm),
					div_func()(w, norm)
				);
			}
			else
			{
				return out_type(std::move(x), std::move(y), std::move(z), std::move(w));
			}
		}
		else
		{
			static_assert
			(
				EmuCore::TMP::get_false<X_, Y_, Z_>(),
				"Unable to performa Euler -> Quaternion conversion. Review other static assertion messages for further detail."
			);
		}
	}

	template
	<
		bool VectorOut_, bool IsRads_, bool PreferMultiplies_, bool Normalise_, bool Fused_, bool IsConstexpr_, typename OutT_,
		std::size_t ReadOffset_, std::size_t VecSize_, typename VecT_
	>
	[[nodiscard]] static constexpr inline auto _make_from_euler_vector(const EmuMath::Vector<VecSize_, VecT_>& euler_vector_)
		-> typename std::conditional<VectorOut_, typename EmuMath::Quaternion<OutT_>::vector_type, EmuMath::Quaternion<OutT_>>::type
	{
		return _make_from_euler<VectorOut_, IsRads_, PreferMultiplies_, Normalise_, Fused_, IsConstexpr_, OutT_>
		(
			euler_vector_.template AtTheoretical<ReadOffset_>(),
			euler_vector_.template AtTheoretical<ReadOffset_ + 1>(),
			euler_vector_.template AtTheoretical<ReadOffset_ + 2>()
		);
	}

	template
	<
		bool VectorOut_, bool IsRads_, bool PreferMultiplies_, bool Normalise_, bool Fused_, bool IsConstexpr_, typename OutT_,
		std::size_t ReadOffset_, std::size_t VecSize_, typename VecT_
	>
	[[nodiscard]] static constexpr inline auto _make_from_euler_vector(EmuMath::Vector<VecSize_, VecT_>& euler_vector_)
		-> typename std::conditional<VectorOut_, typename EmuMath::Quaternion<OutT_>::vector_type, EmuMath::Quaternion<OutT_>>::type
	{
		return _make_from_euler<VectorOut_, IsRads_, PreferMultiplies_, Normalise_, Fused_, IsConstexpr_, OutT_>
		(
			euler_vector_.template AtTheoretical<ReadOffset_>(),
			euler_vector_.template AtTheoretical<ReadOffset_ + 1>(),
			euler_vector_.template AtTheoretical<ReadOffset_ + 2>()
		);
	}

	template
	<
		bool VectorOut_, bool IsRads_, bool PreferMultiplies_, bool Normalise_, bool Fused_, bool IsConstexpr_, typename OutT_,
		std::size_t ReadOffset_, std::size_t VecSize_, typename VecT_
	>
	[[nodiscard]] static constexpr inline auto _make_from_euler_vector(EmuMath::Vector<VecSize_, VecT_>&& euler_vector_)
		-> typename std::conditional<VectorOut_, typename EmuMath::Quaternion<OutT_>::vector_type, EmuMath::Quaternion<OutT_>>::type
	{
		using in_vector = EmuMath::Vector<VecSize_, VecT_>;

		// Warning disabled as we are only ever moving separate indices
#pragma warning(push)
#pragma warning(disable: 26800)
		return _make_from_euler<VectorOut_, IsRads_, PreferMultiplies_, Normalise_, Fused_, IsConstexpr_, OutT_>
		(
			_conditional_quaternion_vector_move_get<ReadOffset_>(std::forward<in_vector>(euler_vector_)),
			_conditional_quaternion_vector_move_get<ReadOffset_ + 1>(std::forward<in_vector>(euler_vector_)),
			_conditional_quaternion_vector_move_get<ReadOffset_ + 2>(std::forward<in_vector>(euler_vector_))
		);
#pragma warning(pop)
	}
#pragma endregion
}

#endif
