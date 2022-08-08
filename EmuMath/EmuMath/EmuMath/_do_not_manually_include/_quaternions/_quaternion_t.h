#ifndef EMU_MATH_QUATERNION_T_H_INC_
#define EMU_MATH_QUATERNION_T_H_INC_ 1

#include "_helpers/_all_helpers.h"
#include <ostream>

namespace EmuMath
{
	template<typename T_>
	struct Quaternion
	{
#pragma region COMMON_ALIASES
	public:
		template<typename OtherT_> friend struct Quaternion;

		using this_type = Quaternion<T_>;
		/// <summary> The type used to represent this Quaternion exactly as a Vector. </summary>
		using vector_type = EmuMath::Vector<4, T_>;
		/// <summary> The type used to represent this Quaternion as a Euler Angles Vector. </summary>
		using euler_type = EmuMath::Vector<3, T_>;

		/// <summary> The type of values stored in this Quaternion. </summary>
		using stored_type = typename vector_type::stored_type;
		/// <summary> The qualified type used by this Quaternion's common interface. </summary>
		using value_type = typename vector_type::value_type;
		/// <summary> The unqualified form of the type used by this Quaternion's common interface. </summary>
		using value_type_uq = typename vector_type::value_type_uq;
		/// <summary> The preferred floating point for this Quaternion to prefer the use of based on its value type, should it not be integral. </summary>
		using preferred_floating_point = typename vector_type::preferred_floating_point;
#pragma endregion

#pragma region COMMON_INFO
	public:
		static constexpr std::size_t euler_cvt_default_read_offset = 0;
		static constexpr std::size_t euler_cvt_default_constexpr_iterations = 0;
		static constexpr bool euler_cvt_default_constexpr_mod = false;
		static constexpr bool euler_cvt_default_prefer_multiplies = false;
		static constexpr bool euler_cvt_default_is_rads = true;
		static constexpr bool euler_cvt_default_normalise = true;

		static constexpr bool contains_ref = vector_type::contains_ref;
		static constexpr bool contains_const_ref = vector_type::contains_const_ref;
		static constexpr bool contains_non_const_ref = vector_type::contains_non_const_ref;
#pragma endregion

#pragma region GET_HELPERS
	private:
		template<std::size_t Index_, std::size_t VecSize_, typename VecT_>
		[[nodiscard]] static constexpr inline decltype(auto) _conditional_vector_move_get(EmuMath::Vector<VecSize_, VecT_>&& vector_)
		{
			if constexpr (EmuMath::Vector<VecSize_, VecT_>::contains_ref || (Index_ >= VecSize_))
			{
				return vector_.template AtTheoretical<Index_>();
			}
			else
			{
				return std::move(vector_.template at<Index_>());
			}
		}

		template<std::size_t Index_, class Arg_>
		[[nodiscard]] static constexpr inline decltype(auto) _get_generic_arg(Arg_&& arg_)
		{
			using arg_uq = typename EmuCore::TMP::remove_ref_cv<Arg_>::type;
			if constexpr (EmuMath::TMP::is_emu_quaternion_v<arg_uq>)
			{
				if constexpr (!std::is_lvalue_reference_v<Arg_> && !arg_uq::contains_ref)
				{
					return std::move(arg_.template at<Index_>());
				}
				else
				{
					return arg_.template at<Index_>();
				}
			}
			else if constexpr(EmuMath::TMP::is_emu_vector_v<arg_uq>)
			{
				if constexpr (!std::is_lvalue_reference_v<Arg_> && Index_ < arg_uq::size && !arg_uq::contains_ref)
				{
					return std::move(arg_.template at<Index_>());
				}
				else
				{
					return arg_.template AtTheoretical<Index_>();
				}
			}
			else
			{
				return std::forward<Arg_>(arg_);
			}
		}

		template<typename Out_, std::size_t Index_, class Arg_, bool StaticAssert_>
		[[nodiscard]] static constexpr inline bool _valid_get_generic_arg()
		{
			if constexpr (std::is_same_v<Arg_, Out_>)
			{
				return true;
			}
			else
			{
				if constexpr (!EmuCore::TMP::is_static_castable_v<decltype(_get_generic_arg<Index_>(std::declval<Arg_>())), Out_>)
				{
					static_assert(!StaticAssert_, "Unable to retrieve a generic argument for an EmuMath Quaternion as a successful conversion to the required type cannot be performed.");
					return false;
				}
				else
				{
					return true;
				}
			}
		}

		template<typename Out_, std::size_t Index_, class Arg_>
		[[nodiscard]] static constexpr inline decltype(auto) _get_generic_arg(Arg_&& arg_)
		{
			if constexpr (std::is_same_v<Arg_, Out_>)
			{
				return std::forward<Arg_>(arg_);
			}
			else
			{
				return static_cast<Out_>(_get_generic_arg<Index_>(std::forward<Arg_>(arg_)));
			}
		}
#pragma endregion

#pragma region ARITHMETIC_VALIDITY_CHECKS
	public:
		template<typename OutT_ = preferred_floating_point>
		[[nodiscard]] static constexpr inline bool can_scalar_multiply()
		{
			return EmuMath::Helpers::quaternion_can_scalar_multiply<T_, preferred_floating_point, OutT_, false>();
		}

		template<typename RhsT_, typename OutT_ = preferred_floating_point>
		[[nodiscard]] static constexpr inline bool can_quaternion_multiply()
		{
			return EmuMath::Helpers::quaternion_can_quaternion_multiply<T_, RhsT_, OutT_, false>();
		}
#pragma endregion

#pragma region CONVERSION_VALIDITY_CHECKS		
	private:
		template
		<
			typename X_, typename Y_, typename Z_,
			std::size_t ConstexprIterations_, bool ConstexprMod_, bool PreferMultiplies_, bool Normalise_, bool IsRads_, bool StaticAssert_
		>
		[[nodiscard]] static constexpr inline bool _valid_euler_conversion_args()
		{
			// Indentation in this gets a bit crazy due to the static_assert messages
			using x_uq = typename EmuCore::TMP::remove_ref_cv<X_>::type;
			using y_uq = typename EmuCore::TMP::remove_ref_cv<Y_>::type;
			using z_uq = typename EmuCore::TMP::remove_ref_cv<Z_>::type;
			using calc_fp = typename EmuCore::TMP::largest_floating_point<x_uq, y_uq, z_uq, preferred_floating_point>::type;

			constexpr bool x_is_valid = EmuCore::TMP::is_static_castable_v<X_, calc_fp>;
			if constexpr (!x_is_valid)
			{
				static_assert
				(
					!StaticAssert_,
					"Unable to perform a Euler -> Quaternion conversion as the X argument cannot be reliably used as a suitable floating-point based on other values."
				);
				return false;
			}
			else
			{
				constexpr bool y_is_valid = EmuCore::TMP::is_static_castable_v<Y_, calc_fp>;
				if constexpr (!y_is_valid)
				{
					static_assert
					(
						!StaticAssert_,
						"Unable to perform a Euler -> Quaternion conversion as the Y argument cannot be reliably used as a suitable floating-point based on other values."
					);
					return false;
				}
				else
				{
					constexpr bool z_is_valid = EmuCore::TMP::is_static_castable_v<Z_, calc_fp>;
					if constexpr (!z_is_valid)
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
							constexpr bool is_constexpr = ConstexprIterations_ > 0;
							using cos_func_type = typename std::conditional
							<
								is_constexpr,
								EmuCore::do_cos_constexpr<calc_fp, ConstexprIterations_, ConstexprMod_>,
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
									is_constexpr,
									EmuCore::do_sin_constexpr<calc_fp, ConstexprIterations_, ConstexprMod_>,
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
													if constexpr (Normalise_)
													{
														using sqrt_func = typename std::conditional<is_constexpr, EmuCore::do_sqrt_constexpr<calc_fp>, EmuCore::do_sqrt<calc_fp>>::type;
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
																if constexpr (!std::is_constructible_v<vector_type, div_result, div_result, div_result, div_result>)
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
														if constexpr (!std::is_constructible_v<vector_type, move_fp_result, move_fp_result, move_fp_result, move_fp_result>)
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
			}
		}

		template
		<
			std::size_t VecSize_, typename VecT_, std::size_t ReadOffset_, bool IsConst_,
			std::size_t ConstexprIterations_, bool ConstexprMod_, bool PreferMultiplies_, bool Normalise_, bool IsRads_, bool StaticAssert_
		>
		[[nodiscard]] static constexpr inline bool _valid_euler_vector_lvalue_conversion_arg()
		{
			using in_vector = typename std::conditional<IsConst_, const EmuMath::Vector<VecSize_, VecT_>&, EmuMath::Vector<VecSize_, VecT_>&>::type;
			using in_x = decltype(std::declval<in_vector>().template AtTheoretical<ReadOffset_>());
			using in_y = decltype(std::declval<in_vector>().template AtTheoretical<ReadOffset_ + 1>());
			using in_z = decltype(std::declval<in_vector>().template AtTheoretical<ReadOffset_ + 2>());
			return _valid_euler_conversion_args<in_x, in_y, in_z, ConstexprIterations_, ConstexprMod_, PreferMultiplies_, Normalise_, IsRads_, StaticAssert_>();
		}

		template
		<
			std::size_t VecSize_, typename VecT_, std::size_t ReadOffset_, std::size_t ConstexprIterations_, bool ConstexprMod_,
			bool PreferMultiplies_, bool Normalise_, bool IsRads_, bool StaticAssert_
		>
		[[nodiscard]] static constexpr inline bool _valid_euler_vector_rvalue_conversion_arg()
		{
			using in_vector = EmuMath::Vector<VecSize_, VecT_>&&;
			using in_x = decltype(_conditional_vector_move_get<ReadOffset_>(std::forward<in_vector>(std::declval<in_vector>())));
			using in_y = decltype(_conditional_vector_move_get<ReadOffset_ + 1>(std::forward<in_vector>(std::declval<in_vector>())));
			using in_z = decltype(_conditional_vector_move_get<ReadOffset_ + 2>(std::forward<in_vector>(std::declval<in_vector>())));
			return _valid_euler_conversion_args<in_x, in_y, in_z, ConstexprIterations_, ConstexprMod_, PreferMultiplies_, Normalise_, IsRads_, StaticAssert_>();
		}
#pragma endregion

#pragma region CONSTRUCTOR_VALIDITY_CHECKS
	private:
		template<std::size_t VecSize_, typename VecT_, bool IsConst_>
		[[nodiscard]] static constexpr inline bool _valid_euler_vector_lvalue_conversion_constructor_arg()
		{
			if constexpr (VecSize_ <= 3)
			{
				return _valid_euler_vector_lvalue_conversion_arg
				<
					VecSize_,
					VecT_,
					euler_cvt_default_read_offset,
					IsConst_,
					euler_cvt_default_constexpr_iterations,
					euler_cvt_default_constexpr_mod,
					euler_cvt_default_prefer_multiplies,
					euler_cvt_default_normalise,
					euler_cvt_default_is_rads,
					false
				>();
			}
			else
			{
				return false;
			}
		}

		template<std::size_t VecSize_, typename VecT_>
		[[nodiscard]] static constexpr inline bool _valid_euler_vector_rvalue_conversion_constructor_arg()
		{
			if constexpr (VecSize_ <= 3)
			{
				return _valid_euler_vector_rvalue_conversion_arg
				<
					VecSize_,
					VecT_,
					euler_cvt_default_read_offset,
					euler_cvt_default_constexpr_iterations,
					euler_cvt_default_constexpr_mod,
					euler_cvt_default_prefer_multiplies,
					euler_cvt_default_normalise,
					euler_cvt_default_is_rads,
					false
				>();
			}
			else
			{
				return false;
			}
		}

	public:
		template<std::size_t Unused_ = 0>
		[[nodiscard]] static constexpr inline bool is_default_constructible()
		{
			using implied_zero = decltype(vector_type::get_implied_zero());
			return std::is_constructible_v<vector_type, implied_zero, implied_zero, implied_zero, value_type_uq&&>;
		}

		template<std::size_t Unused_ = 0>
		[[nodiscard]] static constexpr inline bool is_const_copy_constructible()
		{
			return std::is_constructible_v<vector_type, const vector_type&>;
		}

		template<std::size_t Unused_ = 0>
		[[nodiscard]] static constexpr inline bool is_non_const_copy_constructible()
		{
			return std::is_constructible_v<vector_type, vector_type&>;
		}

		template<std::size_t Unused_ = 0>
		[[nodiscard]] static constexpr inline bool is_move_constructible()
		{
			return std::is_constructible_v<vector_type, vector_type&&>;
		}

		template<typename X_, typename Y_, typename Z_, typename W_>
		[[nodiscard]] static constexpr inline bool is_custom_constructible()
		{
			return std::is_constructible_v
			<
				vector_type,
				typename EmuCore::TMP::forward_result<X_>::type,
				typename EmuCore::TMP::forward_result<Y_>::type,
				typename EmuCore::TMP::forward_result<Z_>::type,
				typename EmuCore::TMP::forward_result<W_>::type
			>;
		}

		template<std::size_t Unused_ = 0>
		[[nodiscard]] static constexpr inline bool is_vector_const_copy_constructible()
		{
			return std::is_constructible_v<vector_type, const vector_type&>;
		}

		template<std::size_t Unused_ = 0>
		[[nodiscard]] static constexpr inline bool is_vector_non_const_copy_constructible()
		{
			return std::is_constructible_v<vector_type, vector_type&>;
		}

		template<std::size_t Unused_ = 0>
		[[nodiscard]] static constexpr inline bool is_vector_move_constructible()
		{
			return std::is_constructible_v<vector_type, vector_type&&>;
		}

		template<std::size_t VecSize_, typename VecT_>
		[[nodiscard]] static constexpr inline bool valid_euler_vector_const_ref_conversion_constructor_arg()
		{
			return _valid_euler_vector_lvalue_conversion_constructor_arg<VecSize_, VecT_, true>();
		}

		template<std::size_t VecSize_, typename VecT_>
		[[nodiscard]] static constexpr inline bool valid_euler_vector_ref_conversion_constructor_arg()
		{
			return _valid_euler_vector_lvalue_conversion_constructor_arg<VecSize_, VecT_, false>();
		}

		template<std::size_t VecSize_, typename VecT_>
		[[nodiscard]] static constexpr inline bool valid_euler_vector_move_conversion_constructor_arg()
		{
			return _valid_euler_vector_rvalue_conversion_constructor_arg<VecSize_, VecT_>();
		}

		template<typename X_, typename Y_, typename Z_>
		[[nodiscard]] static constexpr inline bool valid_euler_conversion_construction_args()
		{
			return _valid_euler_conversion_args
			<
				X_,
				Y_,
				Z_,
				euler_cvt_default_constexpr_iterations,
				euler_cvt_default_constexpr_mod,
				euler_cvt_default_prefer_multiplies,
				euler_cvt_default_normalise,
				euler_cvt_default_is_rads,
				false
			>();
		}
#pragma endregion

#pragma region CONSTRUCTOR_HELPERS
	private:
		template<bool IsRads_, bool PreferMultiplies_, bool Normalise_, std::size_t ConstexprIterations_, bool ConstexprMod_, typename X_, typename Y_, typename Z_>
		[[nodiscard]] static constexpr inline vector_type _make_vector_from_euler(X_&& euler_x_, Y_&& euler_y_, Z_&& euler_z_)
		{
			if constexpr (_valid_euler_conversion_args<X_, Y_, Z_, ConstexprIterations_, ConstexprMod_, PreferMultiplies_, Normalise_, IsRads_, true>())
			{
				// Common info
				// --- We use the largest floating-point type for calculation (including preferred fp type),
				// --- as passing greater-accuracy fp suggests a desire for greater-accuracy calculation results
				using x_uq = typename EmuCore::TMP::remove_ref_cv<X_>::type;
				using y_uq = typename EmuCore::TMP::remove_ref_cv<Y_>::type;
				using z_uq = typename EmuCore::TMP::remove_ref_cv<Z_>::type;
				using calc_fp = typename EmuCore::TMP::largest_floating_point<x_uq, y_uq, z_uq, preferred_floating_point>::type;
				constexpr bool is_constexpr = ConstexprIterations_ > 0;
				
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
					is_constexpr,
					EmuCore::do_cos_constexpr<calc_fp, ConstexprIterations_, ConstexprMod_>,
					EmuCore::do_cos<calc_fp>
				>::type;
				using sin_func = typename std::conditional
				<
					is_constexpr,
					EmuCore::do_sin_constexpr<calc_fp, ConstexprIterations_, ConstexprMod_>,
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
				calc_fp x = roll_cos_MUL_pitch_sin * yaw_cos - roll_sin_MUL_pitch_cos * yaw_sin;
				calc_fp y = roll_cos_MUL_pitch_cos * yaw_sin + roll_sin_MUL_pitch_sin * yaw_cos;
				calc_fp z = roll_sin_MUL_pitch_cos * yaw_cos - roll_cos_MUL_pitch_sin * yaw_sin;
				calc_fp w = roll_cos_MUL_pitch_cos * yaw_cos + roll_sin_MUL_pitch_sin * yaw_sin;

				if constexpr (Normalise_)
				{
					calc_fp norm = mul_func()(x, x);
					norm = add_func()(norm, mul_func()(y, y));
					norm = add_func()(norm, mul_func()(z, z));
					norm = add_func()(norm, mul_func()(w, w));

					using sqrt_func = typename std::conditional<is_constexpr, EmuCore::do_sqrt_constexpr<calc_fp>, EmuCore::do_sqrt<calc_fp>>::type;
					norm = sqrt_func()(norm);

					if constexpr (PreferMultiplies_)
					{
						using reciprocal_func = EmuCore::do_reciprocal<calc_fp>;
						norm = reciprocal_func()(norm);
					}

					return vector_type
					(
						div_func()(x, norm),
						div_func()(y, norm),
						div_func()(z, norm),
						div_func()(w, norm)
					);
				}
				else
				{
					return vector_type(std::move(x), std::move(y), std::move(z), std::move(w));
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
			bool IsRads_, bool PreferMultiplies_, bool Normalise_, std::size_t ConstexprIterations_, bool ConstexprMod_,
			std::size_t ReadOffset_, std::size_t VecSize_, typename VecT_
		>
		[[nodiscard]] static constexpr inline vector_type _make_vector_from_euler(const EmuMath::Vector<VecSize_, VecT_>& euler_vector_)
		{
			return _make_vector_from_euler<IsRads_, PreferMultiplies_, Normalise_, ConstexprIterations_, ConstexprMod_>
			(
				euler_vector_.template AtTheoretical<ReadOffset_>(),
				euler_vector_.template AtTheoretical<ReadOffset_ + 1>(),
				euler_vector_.template AtTheoretical<ReadOffset_ + 2>()
			);
		}

		template
		<
			bool IsRads_, bool PreferMultiplies_, bool Normalise_, std::size_t ConstexprIterations_, bool ConstexprMod_,
			std::size_t ReadOffset_, std::size_t VecSize_, typename VecT_
		>
		[[nodiscard]] static constexpr inline vector_type _make_vector_from_euler(EmuMath::Vector<VecSize_, VecT_>& euler_vector_)
		{
			return _make_vector_from_euler<IsRads_, PreferMultiplies_, Normalise_, ConstexprIterations_, ConstexprMod_>
			(
				euler_vector_.template AtTheoretical<ReadOffset_>(),
				euler_vector_.template AtTheoretical<ReadOffset_ + 1>(),
				euler_vector_.template AtTheoretical<ReadOffset_ + 2>()
			);
		}

		template
		<
			bool IsRads_, bool PreferMultiplies_, bool Normalise_, std::size_t ConstexprIterations_, bool ConstexprMod_,
			std::size_t ReadOffset_, std::size_t VecSize_, typename VecT_
		>
		[[nodiscard]] static constexpr inline vector_type _make_vector_from_euler(EmuMath::Vector<VecSize_, VecT_>&& euler_vector_)
		{
			using in_vector = EmuMath::Vector<VecSize_, VecT_>;

			// Warning disabled as we are only ever moving separate indices
#pragma warning(push)
#pragma warning(disable: 26800)
			return _make_vector_from_euler<IsRads_, PreferMultiplies_, Normalise_, ConstexprIterations_, ConstexprMod_>
			(
				_conditional_vector_move_get<ReadOffset_>(std::forward<in_vector>(euler_vector_)),
				_conditional_vector_move_get<ReadOffset_ + 1>(std::forward<in_vector>(euler_vector_)),
				_conditional_vector_move_get<ReadOffset_ + 2>(std::forward<in_vector>(euler_vector_))
			);
#pragma warning(pop)
		}
#pragma endregion

#pragma region CONSTRUCTORS
	public:
		/// <summary>
		/// <para> Creates a default rotation quaternion, where x = y = z = 0, and w = 1. </para>
		/// </summary>
		template<std::size_t Unused_ = 0, typename = std::enable_if_t<is_default_constructible<Unused_>()>>
		constexpr inline Quaternion() : data(vector_type::get_implied_zero(), vector_type::get_implied_zero(), vector_type::get_implied_zero(), value_type_uq(1))
		{
		}

		/// <summary>
		/// <para> Creates a const-copy of the passed Quaternion. </para>
		/// </summary>
		/// <param name="to_copy_">Quaternion of the same type to copy.</param>
		template<std::size_t Unused_ = 0, typename = std::enable_if_t<is_const_copy_constructible<Unused_>()>>
		constexpr inline Quaternion(const Quaternion<T_>& to_copy_) : data(to_copy_.data)
		{
		}

		/// <summary>
		/// <para> Creates a copy of the passed Quaternion. </para>
		/// </summary>
		/// <param name="to_copy_">Quaternion of the same type to copy.</param>
		template<std::size_t Unused_ = 0, typename = std::enable_if_t<is_copy_constructible<Unused_>()>>
		constexpr inline Quaternion(Quaternion<T_>& to_copy_) : data(to_copy_.data)
		{
		}

		/// <summary>
		/// <para> Moves the data of the passed Quaternion of the same type into a new Quaternion. </para>
		/// </summary>
		/// <param name="to_mmove_">Quaternion of the same type to move.</param>
		template<std::size_t Unused_ = 0, typename = std::enable_if_t<is_move_constructible<Unused_>()>>
		constexpr inline Quaternion(Quaternion<T_>&& to_move_) noexcept : data(std::move(to_move_.data))
		{
		}

		/// <summary>
		/// <para> Creates a new Quaternion with custom X, Y, Z, and W components. Note that W is the real component of the Quaternion. </para>
		/// <para> This does not guarantee that the constructed Quaternion will be valid; this is the responsibility of the caller. </para>
		/// <para> If you do not well understand Quaternions, it is recommended to create one through a different approach. </para>
		/// </summary>
		/// <param name="x_">First imaginary component of the Quaternion.</param>
		/// <param name="y_">Second imaginary component of the Quaternion.</param>
		/// <param name="z_">Third imaginary component of the Quaternion.</param>
		/// <param name="w_">Real component of the Quaternion.</param>
		template<typename X_, typename Y_, typename Z_, typename W_, typename = std::enable_if_t<is_custom_constructible<X_, Y_, Z_, W_>()>>
		constexpr inline Quaternion(X_&& x_, Y_&& y_, Z_&& z_, W_&& w_) :
			data(std::forward<X_>(x_), std::forward<Y_>(y_), std::forward<Z_>(z_), std::forward<W_>(w_))
		{
		}

		/// <summary>
		/// <para> Performs a const-copy of the passed Vector, treating it as a Quaternion. </para>
		/// </summary>
		/// <param name="quaternion_as_vector_">Vector representing a Quaternion to copy.</param>
		template<std::size_t Unused_ = 0, typename = std::enable_if_t<is_vector_const_copy_constructible<Unused_>()>>
		constexpr inline Quaternion(const vector_type& quaternion_as_vector_) : data(quaternion_as_vector_)
		{
		}

		/// <summary>
		/// <para> Performs a copy of the passed Vector, treating it as a Quaternion. </para>
		/// </summary>
		/// <param name="quaternion_as_vector_">Vector representing a Quaternion to copy.</param>
		template<std::size_t Unused_ = 0, typename = std::enable_if_t<is_vector_non_const_copy_constructible<Unused_>()>>
		constexpr inline Quaternion(vector_type& quaternion_as_vector_) : data(quaternion_as_vector_)
		{
		}

		/// <summary>
		/// <para> Performs a move of the passed Vector into a new Quaternion's underlying data, treating it as a Quaternion. </para>
		/// </summary>
		/// <param name="quaternion_as_vector_">Vector representing a Quaternion to move.</param>
		template<std::size_t Unused_ = 0, typename = std::enable_if_t<is_vector_move_constructible<Unused_>()>>
		constexpr inline Quaternion(vector_type&& quaternion_as_vector_) noexcept : data(std::move(quaternion_as_vector_))
		{
		}

		/// <summary>
		/// <para> Creates a Quaternion representing the passed Euler Vector. </para>
		/// <para> Note that the passed Vector will be treated as a Quaternion if it is the same type as this Quaternion's `vector_type`. </para>
		/// </summary>
		/// <param name="euler_vector_">Const reference to a Vector to treat as a Euler representation of a rotation.</param>
		template<std::size_t VecSize_, typename VecT_, typename = std::enable_if_t<valid_euler_vector_const_ref_conversion_constructor_arg<VecSize_, VecT_>()>>
		constexpr inline Quaternion(const EmuMath::Vector<VecSize_, VecT_>& euler_vector_) : 
			data
			(
				_make_vector_from_euler
				<
					euler_cvt_default_is_rads,
					euler_cvt_default_prefer_multiplies,
					euler_cvt_default_normalise,
					euler_cvt_default_constexpr_iterations,
					euler_cvt_default_constexpr_mod,
					euler_cvt_default_read_offset
				>(euler_vector_)
			)
		{
		}

		/// <summary>
		/// <para> Creates a Quaternion representing the passed Euler Vector. </para>
		/// <para> Note that the passed Vector will be treated as a Quaternion if it is the same type as this Quaternion's `vector_type`. </para>
		/// </summary>
		/// <param name="euler_vector_">Reference to a Vector to treat as a Euler representation of a rotation.</param>
		template<std::size_t VecSize_, typename VecT_, typename = std::enable_if_t<valid_euler_vector_ref_conversion_constructor_arg<VecSize_, VecT_>()>>
		constexpr inline Quaternion(EmuMath::Vector<VecSize_, VecT_>& euler_vector_) : 
			data
			(
				_make_vector_from_euler
				<
					euler_cvt_default_is_rads,
					euler_cvt_default_prefer_multiplies,
					euler_cvt_default_normalise,
					euler_cvt_default_constexpr_iterations,
					euler_cvt_default_constexpr_mod,
					euler_cvt_default_read_offset
				>(euler_vector_)
			)
		{
		}

		/// <summary>
		/// <para> Creates a Quaternion representing the passed Euler Vector. </para>
		/// <para> Note that the passed Vector will be treated as a Quaternion if it is the same type as this Quaternion's `vector_type`. </para>
		/// </summary>
		/// <param name="euler_vector_">Vector to treat as a Euler representation of a rotation.</param>
		template<std::size_t VecSize_, typename VecT_, typename = std::enable_if_t<valid_euler_vector_ref_conversion_constructor_arg<VecSize_, VecT_>()>>
		constexpr inline Quaternion(EmuMath::Vector<VecSize_, VecT_>&& euler_vector_) : 
			data
			(
				_make_vector_from_euler
				<
					euler_cvt_default_is_rads,
					euler_cvt_default_prefer_multiplies,
					euler_cvt_default_normalise,
					euler_cvt_default_constexpr_iterations,
					euler_cvt_default_constexpr_mod,
					euler_cvt_default_read_offset
				>(std::move(euler_vector_))
			)
		{
		}

		/// <summary>
		/// <para> Creates a Quaternion representing a Euler rotation formed of the passed components. </para>
		/// </summary>
		/// <param name="euler_x_">First value within the Euler Vector.</param>
		/// <param name="euler_y_">Second value within the Euler Vector.</param>
		/// <param name="euler_z_">Third value within the Euler Vector.</param>
		template<typename X_, typename Y_, typename Z_, typename = std::enable_if_t<valid_euler_conversion_construction_args<X_, Y_, Z_>()>>
		constexpr inline Quaternion(X_&& euler_x_, Y_&& euler_y_, Z_&& euler_z_) :
			data
			(
				_make_vector_from_euler
				<
					euler_cvt_default_is_rads,
					euler_cvt_default_prefer_multiplies,
					euler_cvt_default_normalise,
					euler_cvt_default_constexpr_iterations,
					euler_cvt_default_constexpr_mod
				>(std::forward<X_>(euler_x_), std::forward<Y_>(euler_y_), std::forward<Z_>(euler_z_))
			)
		{
		}
#pragma endregion

#pragma region ACCESS_OPERATORS
	public:
		/// <summary>
		/// <para> Retrieves a reference to the element at the provided index within this Quaternion. </para>
		/// <para> No bounds checks are performed with this operator. </para>
		/// <para> Valid indices are 0, 1, 2, and 3, which correlate to this Quaternion's X, Y, Z, and W components respectively. </para>
		/// </summary>
		/// <returns>Reference to the item at the specified index within this Quaternion.</returns>
		[[nodiscard]] constexpr inline value_type& operator[](const std::size_t index_)
		{
			return data[index_];
		}

		[[nodiscard]] constexpr inline const value_type& operator[](const std::size_t index_) const
		{
			return data[index_];
		}
#pragma endregion

#pragma region COMPARISON_OPERATORS
	public:
		/// <summary>
		/// <para> Compares this Quaternion to the right-hand-side Quaternion and returns true if they are equal. </para>
		/// <para> For comparisons where a margin of error may exist between otherwise identical Quaternions, it is recommended to use `CmpNear` instead. </para>
		/// </summary>
		/// <param name="rhs_">Quaternion to compare this one to.</param>
		/// <returns>True if this Quaternion is exactly equal to `rhs_`; otherwise false.</returns>
		template<typename RhsT_>
		[[nodiscard]] constexpr inline bool operator==(const Quaternion<RhsT_>& rhs_) const
		{
			return data.CmpAllEqual(rhs_.data);
		}

		/// <summary>
		/// <para> Compares this Quaternion to the right-hand-side Quaternion and returns true if any component is not equal. </para>
		/// <para> For comparisons where a margin of error may exist between otherwise identical Quaternions, it is recommended to use `CmpNotNear` instead. </para>
		/// </summary>
		/// <param name="rhs_">Quaternion to compare this one to.</param>
		/// <returns>True if this Quaternion is not exactly equal to `rhs_`; otherwise false.</returns>
		template<typename RhsT_>
		[[nodiscard]] constexpr inline bool operator!=(const Quaternion<RhsT_>& rhs_) const
		{
			return data.CmpAnyNotEqual(rhs_.data);
		}
#pragma endregion

#pragma region CONST_ARITHMETIC_OPERATORS
	public:
		template<typename OutT_ = preferred_floating_point>
		[[nodiscard]] constexpr inline auto operator*(const preferred_floating_point& rhs_scalar_) const
			-> std::enable_if_t<can_scalar_multiply<OutT_>(), EmuMath::Quaternion<OutT_>>
		{
			return EmuMath::Helpers::quaternion_multiply_by_scalar<OutT_>(*this, rhs_scalar_);
		}

		template<typename OutT_ = preferred_floating_point, typename RhsT_>
		[[nodiscard]] constexpr inline auto operator*(const EmuMath::Quaternion<RhsT_>& rhs_quaternion_) const
			-> std::enable_if_t<can_quaternion_multiply<RhsT_, OutT_>(), EmuMath::Quaternion<OutT_>>
		{
			return EmuMath::Helpers::quaternion_multiply_by_quaternion<OutT_>(*this, rhs_quaternion_);
		}
#pragma endregion

#pragma region GET_VALIDITY_CHECKS
	public:
		/// <summary>
		/// <para> Compile-time function to evaluate if a provided `OutT_` is valid when calling `ImaginaryVector` on an instance of this Quaternion type. </para>
		/// <para> `QuaternionIsConst_` identifies if the Quaternion is const-qualified at the time of calling `ImaginaryVector`. </para>
		/// </summary>
		/// <returns>True if a call to `ImaginaryVector` is valid with the given output type on a Quaternion in the given const state; otherwise false.</returns>
		template<typename OutT_, bool QuaternionIsConst_>
		[[nodiscard]] static constexpr inline bool valid_out_imaginary_vector_typearg()
		{
			using vector_ref_type = typename std::conditional<QuaternionIsConst_, const vector_type&, vector_type&>::type;
			return std::is_constructible_v
			<
				EmuMath::Vector<3, OutT_>,
				decltype(std::declval<vector_ref_type>().template at<0>()),
				decltype(std::declval<vector_ref_type>().template at<1>()),
				decltype(std::declval<vector_ref_type>().template at<2>())
			>;
		}

		/// <summary>
		/// <para> Compile-time function to evaluate if a provided `OutT_` is valid when calling `RealScalar` on an instance of this Quaternion type. </para>
		/// <para> `QuaternionIsConst_` identifies if the Quaternion is const-qualified at the time of calling `RealScalar`. </para>
		/// </summary>
		/// <returns>True if a call to `RealScalar` is valid with the given output type on a Quaternion in the given const state; otherwise false.</returns>
		template<typename Out_, bool QuaternionIsConst_>
		[[nodiscard]] static constexpr inline bool valid_out_real_scalar_typearg()
		{
			using vector_ref_type = typename std::conditional<QuaternionIsConst_, const vector_type&, vector_type&>::type;
			return std::is_constructible_v<Out_, decltype(std::declval<vector_ref_type>().template at<3>())>;
		}
#pragma endregion

#pragma region GETTERS
	public:
		/// <summary>
		/// <para> Retrieves a reference to the element at the provided index within this Quaternion. </para>
		/// <para> A compile-time bounds check is performed for this call, and a static assertion will be triggered if Index_ is invalid. </para>
		/// <para> Valid indices are 0, 1, 2, and 3, which correlate to this Quaternion's X, Y, Z, and W components respectively. </para>
		/// </summary>
		/// <returns>Reference to the item at the specified index within this Quaternion.</returns>
		template<std::size_t Index_>
		[[nodiscard]] constexpr inline value_type& at()
		{
			if constexpr (Index_ <= 3)
			{
				return data.template at<Index_>();
			}
			else
			{
				static_assert
				(
					EmuCore::TMP::get_false<Index_>(),
					"Attempted to access an index greater than 3 within a Quaternion. Only 0, 1, 2, and 3 are valid indices in a Quaternion, where 0, 1, 2 are the imaginary component X, Y, Z, and 3 is the real component W."
				);
			}
		}
		template<std::size_t Index_>
		[[nodiscard]] constexpr inline const value_type& at() const
		{
			return const_cast<this_type*>(this)->template at<Index_>();
		}

		/// <summary>
		/// <para> Retrieves a reference to the element at the provided index within this Quaternion. </para>
		/// <para> A runtime bounds check is performed for this call, and a std::out_of_range exception will be thrown if index_ is invalid. </para>
		/// <para> Valid indices are 0, 1, 2, and 3, which correlate to this Quaternion's X, Y, Z, and W components respectively. </para>
		/// </summary>
		/// <returns>Reference to the item at the specified index within this Quaternion.</returns>
		[[nodiscard]] constexpr inline value_type& at(const std::size_t index_)
		{
			if (index_ <= 3)
			{
				return data[index_];
			}
			else
			{
				if constexpr (EmuCore::TMP::feature_constexpr_dynamic_memory())
				{
					// We can provide some extra information if we have access to constexpr strings
					// --- This is to allow `at(index_)` to still satisfy constexpr constraints in standards before C++20
					std::string out_str_;
					out_str_.reserve(150); // Reserves enough space for all literal chars, alongside some extra for index_ after conversion.
					out_str_ += "Attempted to access an invalid contained index of an EmuMath Quaternion.\nProvided index: ";
					out_str_ += std::to_string(index_);
					out_str_ += "\nInclusive valid index range: 0:3";
					throw std::out_of_range(out_str_);
				}
				else
				{
					throw std::out_of_range("Attempted to access an invalid contained index of an EmuMath Quaternion.\nInclusive valid index range: 0:3");
				}
			}
		}

		[[nodiscard]] constexpr inline const value_type& at(const std::size_t index_) const
		{
			return const_cast<this_type*>(this)->at(index_);
		}

		/// <summary>
		/// <para> Outputs a Vector representing the imaginary component (i.e. XYZ) of this Quaternion. </para>
		/// <para> The output Vector may contain any valid conversion type, including references, and defaults to this Quaternion's `value_type_uq`. </para>
		/// </summary>
		/// <returns>3D EmuMath Vector containing the imaginary component of this Quaternion, with X, Y, and Z at indices 0, 1, and 2 respectively.</returns>
		template<typename OutT_ = value_type_uq>
		[[nodiscard]] constexpr inline auto ImaginaryVector()
			-> std::enable_if_t<valid_out_imaginary_vector_typearg<OutT_, false>(), EmuMath::Vector<3, OutT_>>
		{
			return EmuMath::Vector<3, OutT_>(data.at<0>(), data.at<1>(), data.at<2>());
		}

		template<typename OutT_ = value_type_uq>
		[[nodiscard]] constexpr inline auto ImaginaryVector() const
			-> std::enable_if_t<valid_out_imaginary_vector_typearg<OutT_, true>(), EmuMath::Vector<3, OutT_>>
		{
			return EmuMath::Vector<3, OutT_>(data.at<0>(), data.at<1>(), data.at<2>());
		}

		/// <summary>
		/// <para> Outputs a the real component (i.e. W) of this Quaternion. </para>
		/// <para> The output type may be any valid conversion type, including references, and defaults to this Quaternion's `value_type_uq`. </para>
		/// </summary>
		/// <returns>Item of the specified output type constructed with this Quaternion's real, scalar component (W).</returns>
		template<typename Out_ = value_type_uq>
		[[nodiscard]] constexpr inline auto RealScalar()
			-> std::enable_if_t<valid_out_real_scalar_typearg<Out_, false>(), Out_>
		{
			return Out_(data.at<3>());
		}

		template<typename Out_ = value_type_uq>
		[[nodiscard]] constexpr inline auto RealScalar() const
			-> std::enable_if_t<valid_out_real_scalar_typearg<Out_, true>(), Out_>
		{
			return Out_(data.at<3>());
		}
#pragma endregion

#pragma region COMPARISON_FUNCS
	public:
		/// <summary>
		/// <para> Compares this Quaternion to the right-hand-side Quaternion and returns true if they are equal. </para>
		/// <para> For comparisons where a margin of error may exist between otherwise identical Quaternions, it is recommended to use `CmpNear` instead. </para>
		/// </summary>
		/// <param name="rhs_">Quaternion to compare this one to.</param>
		/// <returns>True if this Quaternion is exactly equal to `rhs_`; otherwise false.</returns>
		template<typename RhsT_>
		[[nodiscard]] constexpr inline bool CmpEqual(const Quaternion<RhsT_>& rhs_) const
		{
			return data.CmpAllEqual(rhs_.data);
		}

		/// <summary>
		/// <para> Compares this Quaternion to the right-hand-side Quaternion and returns true if any component is not equal. </para>
		/// <para> For comparisons where a margin of error may exist between otherwise identical Quaternions, it is recommended to use `CmpNotNear` instead. </para>
		/// </summary>
		/// <param name="rhs_">Quaternion to compare this one to.</param>
		/// <returns>True if this Quaternion is not exactly equal to `rhs_`; otherwise false.</returns>
		template<typename RhsT_>
		[[nodiscard]] constexpr inline bool CmpNotEqual(const Quaternion<RhsT_>& rhs_) const
		{
			return data.CmpAnyNotEqual(rhs_.data);
		}

		/// <summary>
		/// <para> Compares this Quaternion to the right-hand-side Quaternion and returns true if they are near-equal. </para>
		/// <para> This comparison considers a potential margin of error due to floating-point precision errors. </para>
		/// </summary>
		/// <param name="rhs_">Quaternion to compare this one to.</param>
		/// <returns>True if this Quaternion is near-equal to `rhs_`; otherwise false.</returns>
		template<typename RhsT_>
		[[nodiscard]] constexpr inline bool CmpNear(const Quaternion<RhsT_>& rhs_) const
		{
			return data.CmpAllNear(rhs_.data);
		}

		/// <summary>
		/// <para> Compares this Quaternion to the right-hand-side Quaternion and returns true if they are near-equal. </para>
		/// <para> This comparison considers a potential margin of error due to floating-point precision errors. </para>
		/// </summary>
		/// <param name="rhs_">Quaternion to compare this one to.</param>
		/// <returns>True if this Quaternion is not near-equal to `rhs_`; otherwise false.</returns>
		template<typename RhsT_>
		[[nodiscard]] constexpr inline bool CmpNotNear(const Quaternion<RhsT_>& rhs_) const
		{
			return data.CmpAnyNotNear(rhs_.data);
		}
#pragma endregion

#pragma region STATIC_GENERATORS
	public:
		/// <summary>
		/// <para> Creates a new Quaternion of this type, which converts the rotation depicted by the passed euler representation. </para>
		/// <para> Input may be radians or degrees, and defaults to being considered radians. If passing degrees, pass `false` for the `IsRads_` template argument. </para>
		/// <para>
		///		Provides an optional preference for multiplications via `PreferMultiplies_`, which defaults to this type's `euler_cvt_default_prefer_multiplies` value. 
		///		When multiplies are preferred, execution may be more performant when emulating divides but there is a chance of reduced accuracy. 
		///		It should be noted that regardless of preference, the compiler may also optimise divisions into multiplications regardless.
		/// </para>
		/// </summary>
		/// <param name="euler_x_">X-component of the euler rotation to convert into a Quaternion.</param>
		/// <param name="euler_y_">Y-component of the euler rotation to convert into a Quaternion.</param>
		/// <param name="euler_z_">Z-component of the euler rotation to convert into a Quaternion.</param>
		/// <returns>Quaternion representation of the passed Euler rotation.</returns>
		template
		<
			bool IsRads_ = euler_cvt_default_is_rads, bool Normalise_ = euler_cvt_default_normalise, bool PreferMultiplies_ = euler_cvt_default_prefer_multiplies,
			typename X_, typename Y_, typename Z_
		>
		[[nodiscard]] static constexpr inline auto from_euler(X_&& euler_x_, Y_&& euler_y_, Z_&& euler_z_)
			-> std::enable_if_t<_valid_euler_conversion_args<X_, Y_, Z_, 0, false, PreferMultiplies_, Normalise_, IsRads_, false>(), EmuMath::Quaternion<T_>>
		{
			return EmuMath::Quaternion<T_>
			(
				_make_vector_from_euler<IsRads_, PreferMultiplies_, Normalise_, 0, false>
				(
					std::forward<X_>(euler_x_),
					std::forward<Y_>(euler_y_),
					std::forward<Z_>(euler_z_)
				)
			);
		}

		/// <summary>
		/// <para> Creates a new Quaternion of this type, which converts the rotation depicted by the passed euler representation. </para>
		/// <para> Input may be radians or degrees, and defaults to being considered radians. If passing degrees, pass `false` for the `IsRads_` template argument. </para>
		/// <para>
		///		Provides an optional preference for multiplications via `PreferMultiplies_`, which defaults to this type's `euler_cvt_default_prefer_multiplies` value. 
		///		When multiplies are preferred, execution may be more performant when emulating divides but there is a chance of reduced accuracy. 
		///		It should be noted that regardless of preference, the compiler may also optimise divisions into multiplications regardless.
		/// </para>
		/// <para> May provide an optional `ReadOffset_` from which to start reading the input Vector. This defaults to 0 (i.e. no offset). </para>
		/// </summary>
		/// <param name="euler_xyz_">EmuMath Vector containing the euler rotation components xyz at indices ReadOffset_, ReadOffset_ + 1, and ReadOffset_ + 2 respectively.</param>
		/// <returns>Quaternion representation of the passed Euler rotation.</returns>
		template
		<
			bool IsRads_ = euler_cvt_default_is_rads, bool Normalise_ = euler_cvt_default_normalise, bool PreferMultiplies_ = euler_cvt_default_prefer_multiplies,
			std::size_t ReadOffset_ = 0, typename VecT_, std::size_t VecSize_
		>
		[[nodiscard]] static constexpr inline auto from_euler(const EmuMath::Vector<VecSize_, VecT_>& euler_xyz_)
			-> std::enable_if_t
			<
				_valid_euler_vector_lvalue_conversion_arg<VecSize_, VecT_, ReadOffset_, true, 0, false, PreferMultiplies_, Normalise_, IsRads_, false>(),
				EmuMath::Quaternion<T_>
			>
		{
			return EmuMath::Quaternion<T_>
			(
				_make_vector_from_euler<IsRads_, PreferMultiplies_, Normalise_, 0, false, ReadOffset_>(euler_xyz_)
			);
		}
		
		template
		<
			bool IsRads_ = euler_cvt_default_is_rads, bool Normalise_ = euler_cvt_default_normalise, bool PreferMultiplies_ = euler_cvt_default_prefer_multiplies,
			std::size_t ReadOffset_ = 0, typename VecT_, std::size_t VecSize_
		>
		[[nodiscard]] static constexpr inline auto from_euler(EmuMath::Vector<VecSize_, VecT_>& euler_xyz_)
			-> std::enable_if_t
			<
				_valid_euler_vector_lvalue_conversion_arg<VecSize_, VecT_, ReadOffset_, false, 0, false, PreferMultiplies_, Normalise_, IsRads_, false>(),
				EmuMath::Quaternion<T_>
			>
		{
			return EmuMath::Quaternion<T_>
			(
				_make_vector_from_euler<IsRads_, PreferMultiplies_, Normalise_, 0, false, ReadOffset_>(euler_xyz_)
			);
		}

		template
		<
			bool IsRads_ = euler_cvt_default_is_rads, bool Normalise_ = euler_cvt_default_normalise, bool PreferMultiplies_ = euler_cvt_default_prefer_multiplies,
			std::size_t ReadOffset_ = 0, typename VecT_, std::size_t VecSize_
		>
		[[nodiscard]] static constexpr inline auto from_euler(EmuMath::Vector<VecSize_, VecT_>&& euler_xyz_)
			-> std::enable_if_t
			<
				_valid_euler_vector_rvalue_conversion_arg<VecSize_, VecT_, ReadOffset_, 0, false, PreferMultiplies_, Normalise_, IsRads_, false>(),
				EmuMath::Quaternion<T_>
			>
		{
			return EmuMath::Quaternion<T_>
			(
				_make_vector_from_euler<IsRads_, PreferMultiplies_, Normalise_, 0, false, ReadOffset_>(std::forward<decltype(euler_xyz_)>(euler_xyz_))
			);
		}

		/// <summary>
		/// <para> Creates a new Quaternion of this type, which converts the rotation depicted by the passed euler representation. </para>
		/// <para> Makes use of alternative approaches to trigonometric functions to allow the conversion to be calculated in a constexpr context. </para>
		/// <para> Input may be radians or degrees, and defaults to being considered radians. If passing degrees, pass `false` for the `IsRads_` template argument. </para>
		/// <para>
		///		Provides an optional preference for multiplications via `PreferMultiplies_`, which defaults to this type's `euler_cvt_default_prefer_multiplies` value. 
		///		When multiplies are preferred, execution may be more performant when emulating divides but there is a chance of reduced accuracy. 
		///		It should be noted that regardless of preference, the compiler may also optimise divisions into multiplications regardless.
		/// </para>
		/// </summary>
		/// <param name="euler_x_">X-component of the euler rotation to convert into a Quaternion.</param>
		/// <param name="euler_y_">Y-component of the euler rotation to convert into a Quaternion.</param>
		/// <param name="euler_z_">Z-component of the euler rotation to convert into a Quaternion.</param>
		/// <returns>Quaternion representation of the passed Euler rotation.</returns>
		template
		<
			bool IsRads_ = euler_cvt_default_is_rads, bool Normalise_ = euler_cvt_default_normalise, bool PreferMultiplies_ = euler_cvt_default_prefer_multiplies,
			typename X_, typename Y_, typename Z_
		>
		[[nodiscard]] static constexpr inline auto from_euler_constexpr(X_&& euler_x_, Y_&& euler_y_, Z_&& euler_z_)
			-> std::enable_if_t
			<
				_valid_euler_conversion_args<X_, Y_, Z_, 3, true, PreferMultiplies_, Normalise_, IsRads_, false>(),
				EmuMath::Quaternion<T_>
			>
		{
			return EmuMath::Quaternion<T_>
			(
				_make_vector_from_euler<IsRads_, PreferMultiplies_, Normalise_, 3, true>
				(
					std::forward<X_>(euler_x_),
					std::forward<Y_>(euler_y_),
					std::forward<Z_>(euler_z_)
				)
			);
		}

		/// <summary>
		/// <para> Creates a new Quaternion of this type, which converts the rotation depicted by the passed euler representation. </para>
		/// <para> Makes use of alternative approaches to trigonometric functions to allow the conversion to be calculated in a constexpr context. </para>
		/// <para> Input may be radians or degrees, and defaults to being considered radians. If passing degrees, pass `false` for the `IsRads_` template argument. </para>
		/// <para>
		///		Provides an optional preference for multiplications via `PreferMultiplies_`, which defaults to this type's `euler_cvt_default_prefer_multiplies` value. 
		///		When multiplies are preferred, execution may be more performant when emulating divides but there is a chance of reduced accuracy. 
		///		It should be noted that regardless of preference, the compiler may also optimise divisions into multiplications regardless.
		/// </para>
		/// <para> May provide an optional `ReadOffset_` from which to start reading the input Vector. This defaults to 0 (i.e. no offset). </para>
		/// </summary>
		/// <param name="euler_xyz_">EmuMath Vector containing the euler rotation components xyz at indices ReadOffset_, ReadOffset_ + 1, and ReadOffset_ + 2 respectively.</param>
		/// <returns>Quaternion representation of the passed Euler rotation.</returns>
		template
		<
			bool IsRads_ = euler_cvt_default_is_rads, bool Normalise_ = euler_cvt_default_normalise, bool PreferMultiplies_ = euler_cvt_default_prefer_multiplies,
			std::size_t ReadOffset_ = 0, typename VecT_, std::size_t VecSize_
		>
		[[nodiscard]] static constexpr inline auto from_euler_constexpr(const EmuMath::Vector<VecSize_, VecT_>& euler_xyz_)
			-> std::enable_if_t
			<
				_valid_euler_vector_lvalue_conversion_arg<VecSize_, VecT_, ReadOffset_, true, 3, true, PreferMultiplies_, Normalise_, IsRads_, false>(),
				EmuMath::Quaternion<T_>
			>
		{
			return EmuMath::Quaternion<T_>
			(
				_make_vector_from_euler<IsRads_, PreferMultiplies_, Normalise_, 3, true, ReadOffset_>(euler_xyz_)
			);
		}

		template
		<
			bool IsRads_ = euler_cvt_default_is_rads, bool Normalise_ = euler_cvt_default_normalise, bool PreferMultiplies_ = euler_cvt_default_prefer_multiplies,
			std::size_t ReadOffset_ = 0, typename VecT_, std::size_t VecSize_
		>
		[[nodiscard]] static constexpr inline auto from_euler_constexpr(EmuMath::Vector<VecSize_, VecT_>& euler_xyz_)
			-> std::enable_if_t
			<
				_valid_euler_vector_lvalue_conversion_arg<VecSize_, VecT_, ReadOffset_, false, 3, true, PreferMultiplies_, Normalise_, IsRads_, false>(),
				EmuMath::Quaternion<T_>
			>
		{
			return EmuMath::Quaternion<T_>
			(
				_make_vector_from_euler<IsRads_, PreferMultiplies_, Normalise_, 3, true, ReadOffset_>(euler_xyz_)
			);
		}

		template
		<
			bool IsRads_ = euler_cvt_default_is_rads, bool Normalise_ = euler_cvt_default_normalise, bool PreferMultiplies_ = euler_cvt_default_prefer_multiplies,
			std::size_t ReadOffset_ = 0, typename VecT_, std::size_t VecSize_
		>
		[[nodiscard]] static constexpr inline auto from_euler_constexpr(EmuMath::Vector<VecSize_, VecT_>&& euler_xyz_)
			-> std::enable_if_t
			<
				_valid_euler_vector_rvalue_conversion_arg<VecSize_, VecT_, ReadOffset_, 3, true, PreferMultiplies_, Normalise_, IsRads_, false>(),
				EmuMath::Quaternion<T_>
			>
		{
			return EmuMath::Quaternion<T_>
			(
				_make_vector_from_euler<IsRads_, PreferMultiplies_, Normalise_, 3, true, ReadOffset_>(std::forward<decltype(euler_xyz_)>(euler_xyz_))
			);
		}
#pragma endregion

#pragma region MEMBER_CONVERSIONS
	private:
		template<typename OutT_, bool IsConstexpr_, bool OutRads_, class X_, class Y_, class Z_, class W_, typename Epsilon_>
		[[nodiscard]] static constexpr inline EmuMath::Vector<3, OutT_> _convert_to_euler_vector(X_&& x_, Y_&& y_, Z_&& z_, W_&& w_, Epsilon_&& epsilon_)
		{
			// Prepare type aliases
			using x_uq = typename EmuCore::TMP::remove_ref_cv<X_>::type;
			using y_uq = typename EmuCore::TMP::remove_ref_cv<Y_>::type;
			using z_uq = typename EmuCore::TMP::remove_ref_cv<Z_>::type;
			using w_uq = typename EmuCore::TMP::remove_ref_cv<W_>::type;
			using epsilon_uq = typename EmuCore::TMP::remove_ref_cv<Epsilon_>::type;
			using calc_fp = typename EmuCore::TMP::largest_floating_point<OutT_, x_uq, y_uq, z_uq, w_uq, epsilon_uq, preferred_floating_point>::type;

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
			calc_fp out_y = mul_func()(w, y);
			out_y = sub_func()(out_y, mul_func()(x, z));
			out_y = mul_func()(two, out_y);
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
				calc_fp out_z = atan2_func()
				(
					mul_func()(two, add_func()(mul_func()(x, y), mul_func()(w, z))),
					add_func()(sub_func()(sub_func()(sqx, sqy), sqz), sqw)
				);
				
				// X
				calc_fp out_x = atan2_func()
				(
					mul_func()(two, add_func()(mul_func()(w, x), mul_func()(y, z))),
					add_func()(sub_func()(sub_func()(sqw, sqx), sqy), sqz)
				);

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
				calc_fp out_z = mul_func()(two, mul_func()(y, z));
				out_z = atan2_func()
				(
					sub_func()(out_z, mul_func()(two, mul_func()(x, w))),
					add_func()(mul_func()(two, mul_func()(x, z)), mul_func()(two, mul_func()(y, w)))
				);
			
				// Negate Z (based on pi instead of 0) if yaw is negative
				bool neg_yaw = y < 0;
				out_z = add_func()
				(
					mul_func()(calc_fp(neg_yaw), sub_func()(EmuCore::Pi::PI<calc_fp>, out_z)),
					mul_func()(calc_fp(!neg_yaw), neg_yaw)
				);
			
				// Convert to degrees if needed
				if constexpr (!OutRads_)
				{
					out_y = mul_func()(out_y, EmuCore::Pi::HUNDRED80_DIV_PI<calc_fp>);
					out_z = mul_func()(out_z, EmuCore::Pi::HUNDRED80_DIV_PI<calc_fp>);
				}
			
				return EmuMath::Vector<3, OutT_>(0, std::move(out_y), std::move(out_z));
			}
		}

	public:
		/// <summary>
		/// <para> Outputs a 3D EmuMath Vector containing a Euler representation of this Quaternion. </para>
		/// <para>
		///		Note that if this Quaternion was formed from a Euler representation, the output Euler angles may not be the same as the input Euler angles. 
		///		This is because multiple combinations of Euler angles may represent the same Quaternion.
		/// </para>
		/// <para> May optionally output in degrees or radians, defaulting to radians. To output as degrees, pass `false` for the `OutRads_` template argument. </para>
		/// <para> The output Vector may have its type argument customised, and defaults to this Quaternion's `preferred_floating_point`. </para>
		/// <para>
		///		May pass a custom epsilon for epsilon-based tests. If omitted, the default epsilon for this Quaternion's `preferred_floating_point` will be used, 
		///		via EmuCore::epsilon.
		/// </para>
		/// </summary>
		/// <param name="epsilon_">
		///		Optional custom epsilon for comparison tests.
		///		If omitted, the used epsilon will be `EmuCore::epsilon::get` for this Quaternion's `preferred_floating_point`.
		/// </param>
		/// <returns>EmuMath Vector containing one potential Euler representation of this Quaternion.</returns>
		template<bool OutRads_, typename OutT_ = preferred_floating_point, typename Epsilon_>
		[[nodiscard]] constexpr inline EmuMath::Vector<3, OutT_> ToEuler(Epsilon_&& epsilon_) const
		{
			return _convert_to_euler_vector<OutT_, false, OutRads_>(data.at<0>(), data.at<1>(), data.at<2>(), data.at<3>(), std::forward<Epsilon_>(epsilon_));
		}

		template<typename OutT_ = preferred_floating_point, typename Epsilon_>
		[[nodiscard]] constexpr inline EmuMath::Vector<3, OutT_> ToEuler(Epsilon_&& epsilon_) const
		{
			return _convert_to_euler_vector<OutT_, false, true>(data.at<0>(), data.at<1>(), data.at<2>(), data.at<3>(), std::forward<Epsilon_>(epsilon_));
		}

		template<bool OutRads_, typename OutT_ = preferred_floating_point>
		[[nodiscard]] constexpr inline EmuMath::Vector<3, OutT_> ToEuler() const
		{
			return _convert_to_euler_vector<OutT_, false, OutRads_>(data.at<0>(), data.at<1>(), data.at<2>(), data.at<3>(), EmuCore::epsilon<preferred_floating_point>::get());
		}

		template<typename OutT_ = preferred_floating_point>
		[[nodiscard]] constexpr inline EmuMath::Vector<3, OutT_> ToEuler() const
		{
			return _convert_to_euler_vector<OutT_, false, true>(data.at<0>(), data.at<1>(), data.at<2>(), data.at<3>(), EmuCore::epsilon<preferred_floating_point>::get());
		}

		/// <summary>
		/// <para> Outputs a 3D EmuMath Vector containing a Euler representation of this Quaternion. </para>
		/// <para> Relevant operations will be done under a constexpr-evaluable context if possible. This may affect precision and/or performance. </para>
		/// <para>
		///		Note that if this Quaternion was formed from a Euler representation, the output Euler angles may not be the same as the input Euler angles. 
		///		This is because multiple combinations of Euler angles may represent the same Quaternion.
		/// </para>
		/// <para> May optionally output in degrees or radians, defaulting to radians. To output as degrees, pass `false` for the `OutRads_` template argument. </para>
		/// <para> The output Vector may have its type argument customised, and defaults to this Quaternion's `preferred_floating_point`. </para>
		/// <para>
		///		May pass a custom epsilon for epsilon-based tests. If omitted, the default epsilon for this Quaternion's `preferred_floating_point` will be used, 
		///		via EmuCore::epsilon.
		/// </para>
		/// </summary>
		/// <param name="epsilon_">
		///		Optional custom epsilon for comparison tests.
		///		If omitted, the used epsilon will be `EmuCore::epsilon::get` for this Quaternion's `preferred_floating_point`.
		/// </param>
		/// <returns>EmuMath Vector containing one potential Euler representation of this Quaternion.</returns>
		template<bool OutRads_, typename OutT_ = preferred_floating_point, typename Epsilon_>
		[[nodiscard]] constexpr inline EmuMath::Vector<3, OutT_> ToEulerConstexpr(Epsilon_&& epsilon_) const
		{
			return _convert_to_euler_vector<OutT_, true, OutRads_>(data.at<0>(), data.at<1>(), data.at<2>(), data.at<3>(), std::forward<Epsilon_>(epsilon_));
		}

		template<typename OutT_ = preferred_floating_point, typename Epsilon_>
		[[nodiscard]] constexpr inline EmuMath::Vector<3, OutT_> ToEulerConstexpr(Epsilon_&& epsilon_) const
		{
			return _convert_to_euler_vector<OutT_, true, true>(data.at<0>(), data.at<1>(), data.at<2>(), data.at<3>(), std::forward<Epsilon_>(epsilon_));
		}

		template<bool OutRads_, typename OutT_ = preferred_floating_point>
		[[nodiscard]] constexpr inline EmuMath::Vector<3, OutT_> ToEulerConstexpr() const
		{
			return _convert_to_euler_vector<OutT_, true, OutRads_>(data.at<0>(), data.at<1>(), data.at<2>(), data.at<3>(), EmuCore::epsilon<preferred_floating_point>::get());
		}

		template<typename OutT_ = preferred_floating_point>
		[[nodiscard]] constexpr inline EmuMath::Vector<3, OutT_> ToEulerConstexpr() const
		{
			return _convert_to_euler_vector<OutT_, true, true>(data.at<0>(), data.at<1>(), data.at<2>(), data.at<3>(), EmuCore::epsilon<preferred_floating_point>::get());
		}
#pragma endregion

#pragma region VECTOR_BASED_OPERATIONS
	public:
		/// <summary>
		/// <para> Outputs the Unit form of this Quaternion (aka: its normalised form). </para>
		/// </summary>
		/// <returns>A normalised copy of this Quaternion.</returns>
		template<typename OutT_ = preferred_floating_point>
		[[nodiscard]] constexpr inline EmuMath::Quaternion<OutT_> Unit() const
		{
			return data.Normalise<OutT_>();
		}

		/// <summary>
		/// <para> Outputs the Unit form of this Quaternion (aka: its normalised form). </para>
		/// <para> Relevant operations will be executed under a constexpr-evaluable context where possible. This may affect accuracy and/or performance. </para>
		/// </summary>
		/// <returns>A normalised copy of this Quaternion.</returns>
		template<typename OutT_ = preferred_floating_point>
		[[nodiscard]] constexpr inline EmuMath::Quaternion<OutT_> UnitConstexpr() const
		{
			return data.NormaliseConstexpr<OutT_>();
		}

		/// <summary>
		/// <para> Normalises this Quaternion into its Unit form. </para>
		/// </summary>
		constexpr inline void NormaliseSelf()
		{
			data = data.Normalise<T_>();
		}

		/// <summary>
		/// <para> Normalises this Quaternion into its Unit form. </para>
		/// <para> Relevant operations will be executed under a constexpr-evaluable context where possible. This may affect accuracy and/or performance. </para>
		/// </summary>
		constexpr inline void NormaliseSelfConstexpr()
		{
			data = data.NormaliseConstexpr<T_>();
		}
#pragma endregion

#pragma region QUATERNION_OPERATIONS
	public:		
		/// <summary>
		/// <para> Outputs the squared Norm (aka: Length) of this Quaternion as the specified type (defaulting to this Quaternion's `preferred_floating_point`). </para>
		/// </summary>
		/// <returns>The squared Norm of this Quaternion.</returns>
		template<typename Out_ = preferred_floating_point>
		[[nodiscard]] constexpr inline auto SquareNorm() const
			-> std::enable_if_t<EmuMath::Helpers::quaternion_can_make_square_norm<T_, Out_, false>(), Out_>
		{
			return EmuMath::Helpers::quaternion_square_norm<Out_>(*this);
		}

		/// <summary>
		/// <para> Outputs the squared Norm (aka: Length) of this Quaternion as the specified type (defaulting to this Quaternion's `preferred_floating_point`). </para>
		/// <para>
		///		This function will attempt to take advantage of fused instructions (such as FMADD) if possible, or emulate them otherwise. 
		///		Use of such instructions may improve accuracy and/or performance.
		/// </para>
		/// </summary>
		/// <returns>The squared Norm of this Quaternion.</returns>
		template<typename Out_ = preferred_floating_point>
		[[nodiscard]] constexpr inline auto FusedSquareNorm() const
			-> std::enable_if_t<EmuMath::Helpers::quaternion_can_make_fused_square_norm<T_, Out_, false>(), Out_>
		{
			return EmuMath::Helpers::quaternion_fused_square_norm<Out_>(*this);
		}

		/// <summary>
		/// <para> Outputs the Norm (aka: Length) of this Quaternion as the specified type (defaulting to this Quaternion's `preferred_floating_point`). </para>
		/// </summary>
		/// <returns>The Norm of this Quaternion.</returns>
		template<typename Out_ = preferred_floating_point>
		[[nodiscard]] constexpr inline auto Norm() const
			-> std::enable_if_t<EmuMath::Helpers::quaternion_can_make_norm<T_, Out_, false>(), Out_>
		{
			return EmuMath::Helpers::quaternion_norm<Out_>(*this);
		}

		/// <summary>
		/// <para> Outputs the Norm (aka: Length) of this Quaternion as the specified type (defaulting to this Quaternion's `preferred_floating_point`). </para>
		/// <para>
		///		This function will attempt to take advantage of fused instructions (such as FMADD) if possible, or emulate them otherwise. 
		///		Use of such instructions may improve accuracy and/or performance.
		/// </para>
		/// </summary>
		/// <returns>The Norm of this Quaternion.</returns>
		template<typename Out_ = preferred_floating_point>
		[[nodiscard]] constexpr inline auto FusedNorm() const
			-> std::enable_if_t<EmuMath::Helpers::quaternion_can_make_fused_norm<T_, Out_, false>(), Out_>
		{
			return EmuMath::Helpers::quaternion_fused_norm<Out_>(*this);
		}

		/// <summary>
		/// <para> Outputs the Norm (aka: Length) of this Quaternion as the specified type (defaulting to this Quaternion's `preferred_floating_point`). </para>
		/// <para> This function will attempt to be constexpr-evaluable, which may have an effect on accuracy and/or performance. </para>
		/// </summary>
		/// <returns>The Norm of this Quaternion.</returns>
		template<typename Out_ = preferred_floating_point>
		[[nodiscard]] constexpr inline auto NormConstexpr() const
			-> std::enable_if_t<EmuMath::Helpers::quaternion_can_make_norm_constexpr<T_, Out_, true>(), Out_>
		{
			return EmuMath::Helpers::quaternion_norm_constexpr<Out_>(*this);
		}

		/// <summary>
		/// <para> Outputs a new Quaternion that is the result of linearly interpolating this Quaternion with Quaternion b_ and a weighting of t_. </para>
		/// <para> Typically, Slerp (Spherical linear interpolation) is likely to be preferred for smoother interpolations. </para>
		/// <para> The resulting Quaternion is not automatically normalised, so arguments that may result in a non-unit Quaternion should be considered. </para>
		/// </summary>
		/// <param name="b_">Quaternion to linearly interpolate this Quaternion with.</param>
		/// <param name="t_">Weighting for interpolation, which may be either this Quternion's `preferred_floating_point` or an EmuMath Vector of respective weightings.</param>
		/// <returns>Quaternion resulting from the linear interpolation.</returns>
		template<typename OutT_ = preferred_floating_point, typename BT_>
		[[nodiscard]] constexpr inline auto Lerp(const EmuMath::Quaternion<BT_>& b_, const preferred_floating_point& t_) const
			-> std::enable_if_t<EmuMath::Helpers::quaternion_lerp_valid_args<T_, BT_, const preferred_floating_point&, OutT_, false>(), EmuMath::Quaternion<OutT_>>
		{
			return EmuMath::Helpers::quaternion_lerp<OutT_>(*this, b_, t_);
		}

		template<typename OutT_ = preferred_floating_point, typename BT_, std::size_t TArgSize_, typename TArgT_>
		[[nodiscard]] constexpr inline auto Lerp(const EmuMath::Quaternion<BT_>& b_, const EmuMath::Vector<TArgSize_, TArgT_>& t_) const
			-> std::enable_if_t
			<
				EmuMath::Helpers::quaternion_lerp_valid_args<T_, BT_, const EmuMath::Vector<TArgSize_, TArgT_>&, OutT_, false>(),
				EmuMath::Quaternion<OutT_>
			>
		{
			return EmuMath::Helpers::quaternion_lerp<OutT_>(*this, b_, t_);
		}
		
		/// <summary>
		/// <para> Outputs a new Quaternion that is the result of linearly interpolating this Quaternion with Quaternion b_ and a weighting of t_. </para>
		/// <para> Typically, Slerp (Spherical linear interpolation) is likely to be preferred for smoother interpolations. </para>
		/// <para> The resulting Quaternion is not automatically normalised, so arguments that may result in a non-unit Quaternion should be considered. </para>
		/// <para>
		///		This function will take advantage of fused instructions (such as FMADD) if possible, or emulate them otherwise. 
		///		Use of such instructions may improve accuracy and/or performance.
		/// </para>
		/// </summary>
		/// <param name="b_">Quaternion to linearly interpolate this Quaternion with.</param>
		/// <param name="t_">Weighting for interpolation, which may be either this Quternion's `preferred_floating_point` or an EmuMath Vector of respective weightings.</param>
		/// <returns>Quaternion resulting from the linear interpolation.</returns>
		template<typename OutT_ = preferred_floating_point, typename BT_>
		[[nodiscard]] constexpr inline auto FusedLerp(const EmuMath::Quaternion<BT_>& b_, const preferred_floating_point& t_) const
			-> std::enable_if_t<EmuMath::Helpers::quaternion_fused_lerp_valid_args<T_, BT_, const preferred_floating_point&, OutT_, false>(), EmuMath::Quaternion<OutT_>>
		{
			return EmuMath::Helpers::quaternion_fused_lerp<OutT_>(*this, b_, t_);
		}

		template<typename OutT_ = preferred_floating_point, typename BT_, std::size_t TArgSize_, typename TArgT_>
		[[nodiscard]] constexpr inline auto FusedLerp(const EmuMath::Quaternion<BT_>& b_, const EmuMath::Vector<TArgSize_, TArgT_>& t_) const
			-> std::enable_if_t
			<
				EmuMath::Helpers::quaternion_fused_lerp_valid_args<T_, BT_, const EmuMath::Vector<TArgSize_, TArgT_>&, OutT_, false>(),
				EmuMath::Quaternion<OutT_>
			>
		{
			return EmuMath::Helpers::quaternion_fused_lerp<OutT_>(*this, b_, t_);
		}

		/// <summary>
		/// <para> Outputs a new Quaternion that is the result of a spherical linear interpolation of this Quaternion with Quaternion b_ and a weighting of t_. </para>
		/// <para> Typically, this is likely to be preferred over a plain Lerp for smoother interpolations. </para>
		/// <para> The resulting Quaternion is not automatically normalised, so arguments that may result in a non-unit Quaternion should be considered. </para>
		/// </summary>
		/// <param name="b_">Quaternion to spherically linearly interpolate this Quaternion with.</param>
		/// <param name="t_">Weighting for interpolation.</param>
		/// <returns>Quaternion resulting from the spherical linear interpolation.</returns>
		template<typename OutT_ = preferred_floating_point, typename BT_>
		[[nodiscard]] constexpr inline auto Slerp(const EmuMath::Quaternion<BT_>& b_, const preferred_floating_point& t_) const
			-> std::enable_if_t<EmuMath::Helpers::quaternion_slerp_valid_args<T_, BT_, const preferred_floating_point&, OutT_, false>(), EmuMath::Quaternion<OutT_>>
		{
			return EmuMath::Helpers::quaternion_slerp<OutT_>(*this, b_, t_);
		}

		/// <summary>
		/// <para> Outputs a new Quaternion that is the result of a spherical linear interpolation of this Quaternion with Quaternion b_ and a weighting of t_. </para>
		/// <para> Typically, this is likely to be preferred over a plain Lerp for smoother interpolations. </para>
		/// <para> The resulting Quaternion is not automatically normalised, so arguments that may result in a non-unit Quaternion should be considered. </para>
		/// <para> Relevant functions will aim to be constexpr-evaluable if possible. </para>
		/// </summary>
		/// <param name="b_">Quaternion to spherically linearly interpolate this Quaternion with.</param>
		/// <param name="t_">Weighting for interpolation.</param>
		/// <returns>Quaternion resulting from the spherical linear interpolation.</returns>
		template<typename OutT_ = preferred_floating_point, typename BT_>
		[[nodiscard]] constexpr inline auto SlerpConstexpr(const EmuMath::Quaternion<BT_>& b_, const preferred_floating_point& t_) const
			-> std::enable_if_t<EmuMath::Helpers::quaternion_slerp_constexpr_valid_args<T_, BT_, preferred_floating_point, OutT_, false>(), EmuMath::Quaternion<OutT_>>
		{
			return EmuMath::Helpers::quaternion_slerp_constexpr<OutT_>(*this, b_, t_);
		}

		/// <summary>
		/// <para> Outputs a new Quaternion that is the result of a spherical linear interpolation of this Quaternion with Quaternion b_ and a weighting of t_. </para>
		/// <para> Typically, this is likely to be preferred over a plain Lerp for smoother interpolations. </para>
		/// <para> The resulting Quaternion is not automatically normalised, so arguments that may result in a non-unit Quaternion should be considered. </para>
		/// <para>
		///		This function will take advantage of fused instructions (such as FMADD) if possible, or emulate them otherwise. 
		///		Use of such instructions may improve accuracy and/or performance.
		/// </para>
		/// </summary>
		/// <param name="b_">Quaternion to spherically linearly interpolate this Quaternion with.</param>
		/// <param name="t_">Weighting for interpolation.</param>
		/// <returns>Quaternion resulting from the spherical linear interpolation.</returns>
		template<typename OutT_ = preferred_floating_point, typename BT_>
		[[nodiscard]] constexpr inline auto FusedSlerp(const EmuMath::Quaternion<BT_>& b_, const preferred_floating_point& t_) const
			-> std::enable_if_t<EmuMath::Helpers::quaternion_fused_slerp_valid_args<T_, BT_, preferred_floating_point, OutT_, false>(), EmuMath::Quaternion<OutT_>>
		{
			return EmuMath::Helpers::quaternion_fused_slerp<OutT_>(*this, b_, t_);
		}

		/// <summary>
		/// <para> Returns the form of this Quaternion with its imaginary component (i.e. X, Y, Z) negated. </para>
		/// <para> The type of the output Quaternion may be customised, and defaults to this Quaternion's `preferred_floating_point`. </para>
		/// </summary>
		/// <returns>Quaternion representing this Quaternion's conjugate.</returns>
		template<typename OutT_ = preferred_floating_point>
		[[nodiscard]] constexpr inline auto Conjugate() const
			-> std::enable_if_t<EmuMath::Helpers::quaternion_can_make_conjugate<T_, OutT_, false>(), EmuMath::Quaternion<OutT_>>
		{
			return EmuMath::Helpers::quaternion_conjugate<OutT_>(*this);
		}

		/// <summary>
		/// <para> Returns the inverse form of this Quaternion, which is equivalent to its Conjugate normalised. </para>
		/// <para>
		///		If this Quaternion is known to have a length of 1, this is mathematically identical to `Conjugate`, 
		///		although floating-point errors may produce different results.
		/// </para>
		/// <para> May optionally choose reciprocal multiplication instead of division for normalisation. If `PreferMultiplies_` is omitted, it will be considered `false`. </para>
		/// </summary>
		/// <returns>Quaternion representing the inverse of this Quaternion.</returns>
		template<bool PreferMultiplies_, typename OutT_ = preferred_floating_point >
		[[nodiscard]] constexpr inline auto Inverse() const
			-> std::enable_if_t<EmuMath::Helpers::quaternion_can_make_inverse<PreferMultiplies_, T_, OutT_, false>(), EmuMath::Quaternion<OutT_>>
		{
			return EmuMath::Helpers::quaternion_inverse<PreferMultiplies_, OutT_>(*this);
		}

		template<typename OutT_ = preferred_floating_point >
		[[nodiscard]] constexpr inline auto Inverse() const
			-> std::enable_if_t<EmuMath::Helpers::quaternion_can_make_inverse<false, T_, OutT_, false>(), EmuMath::Quaternion<OutT_>>
		{
			return EmuMath::Helpers::quaternion_inverse<false, OutT_>(*this);
		}

		/// <summary>
		/// <para> Returns the inverse form of this Quaternion, which is equivalent to its Conjugate normalised. </para>
		/// <para>
		///		If this Quaternion is known to have a length of 1, this is mathematically identical to `Conjugate`, 
		///		although floating-point errors may produce different results.
		/// </para>
		/// <para> May optionally choose reciprocal multiplication instead of division for normalisation. If `PreferMultiplies_` is omitted, it will be considered `false`. </para>
		/// <para>
		///		This function will attempt to take advantage of fused instructions (such as FMADD) if possible, or emulate them otherwise. 
		///		Use of such instructions may improve accuracy and/or performance.
		/// </para>
		/// </summary>
		/// <returns>Quaternion representing the inverse of this Quaternion.</returns>
		template<bool PreferMultiplies_, typename OutT_ = preferred_floating_point >
		[[nodiscard]] constexpr inline auto FusedInverse() const
			-> std::enable_if_t<EmuMath::Helpers::quaternion_can_make_fused_inverse<PreferMultiplies_, T_, OutT_, false>(), EmuMath::Quaternion<OutT_>>
		{
			return EmuMath::Helpers::quaternion_fused_inverse<PreferMultiplies_, OutT_>(*this);
		}

		template<typename OutT_ = preferred_floating_point >
		[[nodiscard]] constexpr inline auto FusedInverse() const
			-> std::enable_if_t<EmuMath::Helpers::quaternion_can_make_fused_inverse<false, T_, OutT_, false>(), EmuMath::Quaternion<OutT_>>
		{
			return EmuMath::Helpers::quaternion_fused_inverse<false, OutT_>(*this);
		}

		/// <summary>
		/// <para> Returns the inverse form of this Quaternion, which is equivalent to its Conjugate normalised. </para>
		/// <para>
		///		If this Quaternion is known to have a length of 1, this is mathematically identical to `Conjugate`, 
		///		although floating-point errors may produce different results.
		/// </para>
		/// <para> May optionally choose reciprocal multiplication instead of division for normalisation. If `PreferMultiplies_` is omitted, it will be considered `false`. </para>
		/// <para> If possible, this expression will aim to be constexpr-evaluable. This may affect accuracy and/or performance. </para>
		/// </summary>
		/// <returns>Quaternion representing the inverse of this Quaternion.</returns>
		template<bool PreferMultiplies_, typename OutT_ = preferred_floating_point >
		[[nodiscard]] constexpr inline auto InverseConstexpr() const
			-> std::enable_if_t<EmuMath::Helpers::quaternion_can_make_inverse_constexpr<PreferMultiplies_, T_, OutT_, false>(), EmuMath::Quaternion<OutT_>>
		{
			return EmuMath::Helpers::quaternion_inverse_constexpr<PreferMultiplies_, OutT_>(*this);
		}

		template<typename OutT_ = preferred_floating_point >
		[[nodiscard]] constexpr inline auto InverseConstexpr() const
			-> std::enable_if_t<EmuMath::Helpers::quaternion_can_make_inverse_constexpr<false, T_, OutT_, false>(), EmuMath::Quaternion<OutT_>>
		{
			return EmuMath::Helpers::quaternion_inverse_constexpr<false, OutT_>(*this);
		}
#pragma endregion

#pragma region CONST_ARITHMETIC
	public:
		template<typename OutT_ = preferred_floating_point>
		[[nodiscard]] constexpr inline auto Multiply(const preferred_floating_point& rhs_scalar_) const
			-> std::enable_if_t<can_scalar_multiply<OutT_>(), EmuMath::Quaternion<OutT_>>
		{
			return EmuMath::Helpers::quaternion_multiply_by_scalar<OutT_>(*this, rhs_scalar_);
		}

		template<typename OutT_ = preferred_floating_point, typename RhsT_>
		[[nodiscard]] constexpr inline auto Multiply(const EmuMath::Quaternion<RhsT_>& rhs_quaternion_) const
			-> std::enable_if_t<can_quaternion_multiply<RhsT_, OutT_>(), EmuMath::Quaternion<OutT_>>
		{
			return EmuMath::Helpers::quaternion_multiply_by_quaternion<OutT_>(*this, rhs_quaternion_);
		}
#pragma endregion

#pragma region UNDERLYING_DATA
	public:
		/// <summary>
		/// <para> The underlying data of this Quaternion, represented as a Vector. </para>
		/// <para> This should not be modified directly unless you are sure that you know what you're doing. </para>
		/// </summary>
		vector_type data;
#pragma endregion
	};
}

template<typename T_>
inline std::ostream& operator<<(std::ostream& str_, const EmuMath::Quaternion<T_>& quaternion_)
{
	str_ << quaternion_.data;
	return str_;
}

template<typename T_>
inline std::wostream& operator<<(std::wostream& w_str_, const EmuMath::Quaternion<T_>& quaternion_)
{
	w_str_ << quaternion_.data;
	return w_str_;
}

#endif
