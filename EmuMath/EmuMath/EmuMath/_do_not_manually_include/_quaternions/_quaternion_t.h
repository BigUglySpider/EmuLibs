#ifndef EMU_MATH_QUATERNION_T_H_INC_
#define EMU_MATH_QUATERNION_T_H_INC_ 1

#include "_underlying_helpers/_quaternion_tmp.h"
#include <ostream>

namespace EmuMath
{
	template<typename T_>
	struct Quaternion
	{
#pragma region COMMON_ALIASES
	public:
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
		static constexpr std::size_t euler_cvt_constructor_read_offset = 0;
		static constexpr std::size_t euler_cvt_constructor_constexpr_iterations = 0;
		static constexpr bool euler_cvt_constructor_constexpr_mod = false;
		static constexpr bool euler_cvt_constructor_prefer_multiplies = false;
		static constexpr bool euler_cvt_constructor_is_rads = true;
#pragma endregion

#pragma region GET_HELPERS
	private:
		template<std::size_t Index_, std::size_t VecSize_, typename VecT_>
		[[nodiscard]] static constexpr inline decltype(auto) _conditional_vector_move_get(EmuMath::Vector<VecSize_, VecT_>&& vector_)
		{
			if constexpr (EmuMath::Vector<VecSize_, VecT_>::contains_ref || (Index_ >= VecSize_))
			{
				return vector_.template AtTheoretial<Index_>();
			}
			else
			{
				return std::move(vector_.template at<Index_>());
			}
		}
#pragma endregion

#pragma region CONVERSION_VALIDITY_CHECKS		
	private:
		template
		<
			typename X_, typename Y_, typename Z_,
			std::size_t ConstexprIterations_, bool ConstexprMod_, bool PreferMultiplies_, bool IsRads_, bool StaticAssert_
		>
		[[nodiscard]] static constexpr inline bool _valid_euler_conversion_args()
		{
			// Indentation in this gets a bit crazy due to the static_assert messages
			using x_uq = typename EmuCore::TMP::remove_ref_cv<X_>::type;
			using y_uq = typename EmuCore::TMP::remove_ref_cv<Y_>::type;
			using z_uq = typename EmuCore::TMP::remove_ref_cv<Z_>::type;
			using largest_fp = typename EmuCore::TMP::largest_floating_point<x_uq, y_uq, z_uq, preferred_floating_point>::type;

			constexpr bool x_is_valid = EmuCore::TMP::is_static_castable_v<X_, largest_fp>;
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
				constexpr bool y_is_valid = EmuCore::TMP::is_static_castable_v<Y_, largest_fp>;
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
					constexpr bool z_is_valid = EmuCore::TMP::is_static_castable_v<Z_, largest_fp>;
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
							EmuCore::do_multiply<largest_fp, largest_fp>,
							EmuCore::do_divide<largest_fp, largest_fp>
						>::type;
						if constexpr (!std::is_invocable_r_v<largest_fp, division_func_type&, largest_fp, largest_fp>)
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
								EmuCore::do_cos_constexpr<largest_fp, ConstexprIterations_, ConstexprMod_>,
								EmuCore::do_cos<largest_fp>
							>::type;

							if constexpr (!std::is_invocable_r_v<largest_fp, cos_func_type&, largest_fp>)
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
									EmuCore::do_sin_constexpr<largest_fp, ConstexprIterations_, ConstexprMod_>,
									EmuCore::do_sin<largest_fp>
								>::type;
								if constexpr (!std::is_invocable_r_v<largest_fp, sin_func_type&, largest_fp>)
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
									using mul_func_type = EmuCore::do_multiply<largest_fp, largest_fp>;
									if constexpr (!std::is_invocable_r_v<largest_fp, mul_func_type&, largest_fp, largest_fp>)
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
										using add_func_type = EmuCore::do_add<largest_fp, largest_fp>;
										if constexpr (!std::is_invocable_r_v<largest_fp, add_func_type, largest_fp, largest_fp>)
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
												std::is_invocable_r_v<largest_fp, decltype(EmuCore::Pi::DegsToRads<largest_fp>), largest_fp>
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
												using sub_func_type = EmuCore::do_subtract<largest_fp, largest_fp>;
												if constexpr (!std::is_invocable_r_v<largest_fp, sub_func_type&, largest_fp, largest_fp>)
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
													using move_fp_result = decltype(std::move(std::declval<largest_fp>()));
													if constexpr (!std::is_constructible_v<vector_type, move_fp_result, move_fp_result, move_fp_result, move_fp_result>)
													{
														static_assert
														(
															!StaticAssert_,
															"Unable to perform a Euler -> Quaternion conversion as the underlying data cannot be constructed from 4 rvalues of the determined calculation type."
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

		template
		<
			std::size_t VecSize_, typename VecT_, std::size_t ReadOffset_, bool IsConst_,
			std::size_t ConstexprIterations_, bool ConstexprMod_, bool PreferMultiplies_, bool IsRads_, bool StaticAssert_
		>
		[[nodiscard]] static constexpr inline bool _valid_euler_vector_lvalue_conversion_arg()
		{
			using in_vector = typename std::conditional<IsConst_, const EmuMath::Vector<VecSize_, VecT_>&, EmuMath::Vector<VecSize_, VecT_>&>::type;
			using in_x = decltype(std::declval<in_vector>().template AtTheoretial<ReadOffset_>());
			using in_y = decltype(std::declval<in_vector>().template AtTheoretial<ReadOffset_ + 1>());
			using in_z = decltype(std::declval<in_vector>().template AtTheoretial<ReadOffset_ + 2>());
			return _valid_euler_conversion_args<in_x, in_y, in_z, ConstexprIterations_, ConstexprMod_, PreferMultiplies_, IsRads_, StaticAssert_>();
		}

		template
		<
			std::size_t VecSize_, typename VecT_, std::size_t ReadOffset_, std::size_t ConstexprIterations_, bool ConstexprMod_,
			bool PreferMultiplies_, bool IsRads_, bool StaticAssert_
		>
		[[nodiscard]] static constexpr inline bool _valid_euler_vector_rvalue_conversion_arg()
		{
			using in_vector = EmuMath::Vector<VecSize_, VecT_>&&;
			using in_x = decltype(_conditional_vector_move_get<ReadOffset_>(std::forward<in_vector>(std::declval<in_vector>())));
			using in_y = decltype(_conditional_vector_move_get<ReadOffset_ + 1>(std::forward<in_vector>(std::declval<in_vector>())));
			using in_z = decltype(_conditional_vector_move_get<ReadOffset_ + 2>(std::forward<in_vector>(std::declval<in_vector>())));
			return _valid_euler_conversion_args<in_x, in_y, in_z, ConstexprIterations_, ConstexprMod_, PreferMultiplies_, IsRads_, StaticAssert_>();
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
					euler_cvt_constructor_read_offset,
					IsConst_,
					euler_cvt_constructor_constexpr_iterations,
					euler_cvt_constructor_constexpr_mod,
					euler_cvt_constructor_prefer_multiplies,
					euler_cvt_constructor_is_rads,
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
					euler_cvt_constructor_read_offset,
					euler_cvt_constructor_constexpr_iterations,
					euler_cvt_constructor_constexpr_mod,
					euler_cvt_constructor_prefer_multiplies,
					euler_cvt_constructor_is_rads,
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
			return vector_type::is_default_constructible();
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

		template<typename Pitch_, typename Yaw_, typename Roll_>
		[[nodiscard]] static constexpr inline bool valid_euler_conversion_construction_args()
		{
			return _valid_euler_conversion_args
			<
				Pitch_,
				Yaw_,
				Roll_,
				euler_cvt_constructor_constexpr_iterations,
				euler_cvt_constructor_constexpr_mod,
				euler_cvt_constructor_prefer_multiplies,
				euler_cvt_constructor_is_rads,
				false
			>();
		}
#pragma endregion

#pragma region CONSTRUCTOR_HELPERS
	private:
		template<bool IsRads_, bool PreferMultiplies_, std::size_t ConstexprIterations_, bool ConstexprMod_, typename X_, typename Y_, typename Z_>
		[[nodiscard]] static constexpr inline vector_type _make_vector_from_euler(X_&& euler_pitch_, Y_&& euler_yaw_, Z_&& euler_roll_)
		{
			if constexpr (_valid_euler_conversion_args<X_, Y_, Z_, ConstexprIterations_, ConstexprMod_, PreferMultiplies_, IsRads_, true>())
			{
				// Common info
				using x_uq = typename EmuCore::TMP::remove_ref_cv<X_>::type;
				using y_uq = typename EmuCore::TMP::remove_ref_cv<Y_>::type;
				using z_uq = typename EmuCore::TMP::remove_ref_cv<Z_>::type;
				using largest_fp = typename EmuCore::TMP::largest_floating_point<x_uq, y_uq, z_uq, preferred_floating_point>::type;
				constexpr bool is_constexpr = ConstexprIterations_ > 0;
				
				// --- START of common function types determination
				// Prepare division function - If `PreferMultiplies_` is true, this will be intended for use as a reciprocal multiplication
				using div_func = typename std::conditional
				<
					PreferMultiplies_,
					EmuCore::do_multiply<largest_fp, largest_fp>,
					EmuCore::do_divide<largest_fp, largest_fp>
				>::type;

				// Prepare trivial functions
				using add_func = EmuCore::do_add<largest_fp, largest_fp>;
				using sub_func = EmuCore::do_subtract<largest_fp, largest_fp>;
				using mul_func = EmuCore::do_multiply<largest_fp, largest_fp>;

				// Prepare trig functions
				using cos_func = typename std::conditional
				<
					is_constexpr,
					EmuCore::do_cos_constexpr<largest_fp, ConstexprIterations_, ConstexprMod_>,
					EmuCore::do_cos<largest_fp>
				>::type;
				using sin_func = typename std::conditional
				<
					is_constexpr,
					EmuCore::do_sin_constexpr<largest_fp, ConstexprIterations_, ConstexprMod_>,
					EmuCore::do_sin<largest_fp>
				>::type;

				// --- END of common function types determination
				// --- START of common calculations
				// Convert values to calculation type
				largest_fp pitch_div_2_sin = static_cast<largest_fp>(std::forward<X_>(euler_pitch_));
				largest_fp yaw_div_2_sin = static_cast<largest_fp>(std::forward<Y_>(euler_yaw_));
				largest_fp roll_div_2_sin = static_cast<largest_fp>(std::forward<Z_>(euler_roll_));

				// Deg->Rad if needed
				if constexpr (!IsRads_)
				{
					pitch_div_2_sin = EmuCore::Pi::DegsToRads(pitch_div_2_sin);
					yaw_div_2_sin = EmuCore::Pi::DegsToRads(yaw_div_2_sin);
					roll_div_2_sin = EmuCore::Pi::DegsToRads(roll_div_2_sin);
				}

				// Set these values to angle / 2
				constexpr largest_fp div_by_2_rhs = PreferMultiplies_ ? largest_fp(0.5) : largest_fp(2);
				pitch_div_2_sin = div_func()(pitch_div_2_sin, div_by_2_rhs);
				yaw_div_2_sin = div_func()(yaw_div_2_sin, div_by_2_rhs);
				roll_div_2_sin = div_func()(roll_div_2_sin, div_by_2_rhs);

				// Find cosines
				largest_fp pitch_div_2_cos = cos_func()(pitch_div_2_sin);
				largest_fp yaw_div_2_cos = cos_func()(yaw_div_2_sin);
				largest_fp roll_div_2_cos = cos_func()(roll_div_2_sin);

				// Finally set these vars to their names by finding sines
				pitch_div_2_sin = sin_func()(pitch_div_2_sin);
				yaw_div_2_sin = sin_func()(yaw_div_2_sin);
				roll_div_2_sin = sin_func()(roll_div_2_sin);

				// Common values used in component calculations - avoids extra multiplies
				largest_fp sin_roll_mul_sin_pitch = mul_func()(roll_div_2_sin, pitch_div_2_sin);
				largest_fp cos_roll_mul_cos_pitch = mul_func()(roll_div_2_cos, pitch_div_2_cos);
				largest_fp sin_roll_mul_cos_pitch = mul_func()(roll_div_2_sin, pitch_div_2_cos);
				largest_fp cos_roll_mul_sin_pitch = mul_func()(roll_div_2_cos, pitch_div_2_sin);
				
				// --- END of common calculations
				// --- START of component calculations
				// X = (SIN_ROLL * COS_PITCH * COS_YAW) - (COS_ROLL * SIN_PITCH * SIN_YAW);
				largest_fp temp_rhs = mul_func()(cos_roll_mul_sin_pitch, yaw_div_2_sin); // COS_ROLL * SIN_PITCH * SIN_YAW
				largest_fp x = mul_func()(sin_roll_mul_cos_pitch, yaw_div_2_cos); // SIN_ROLL * COS_PITCH * COS_YAW
				x = sub_func()(x, temp_rhs);

				// Y = (COS_ROLL * SIN_PITCH * COS_YAW) + (SIN_ROLL * COS_PITCH * SIN_YAW);
				largest_fp y = mul_func()(cos_roll_mul_sin_pitch, yaw_div_2_cos); // COS_ROLL * SIN_PITCH * COS_YAW
				temp_rhs = mul_func()(sin_roll_mul_cos_pitch, yaw_div_2_sin); // SIN_ROLL * COS_PITCH * SIN_YAW
				y = add_func()(y, temp_rhs);

				// Z = (COS_ROLL * COS_PITCH * SIN_YAW) - (SIN_ROLL * SIN_PITCH * COS_YAW);
				largest_fp z = mul_func()(cos_roll_mul_cos_pitch, yaw_div_2_sin); // COS_ROLL * COS_PITCH * SIN_YAW
				temp_rhs = mul_func()(sin_roll_mul_sin_pitch, yaw_div_2_cos); // SIN_ROLL * SIN_PITCH * COS_YAW
				z = sub_func()(z, temp_rhs);

				// W = (COS_ROLL * COS_PITCH * COS_YAW) + (SIN_ROLL * SIN_PITCH * SIN_YAW);
				largest_fp w = mul_func()(cos_roll_mul_cos_pitch, yaw_div_2_cos);
				temp_rhs = mul_func()(sin_roll_mul_sin_pitch, yaw_div_2_sin);
				w = add_func()(w, temp_rhs);

				return vector_type(std::move(x), std::move(y), std::move(z), std::move(w));
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
			bool IsRads_, bool PreferMultiplies_, std::size_t ConstexprIterations_, bool ConstexprMod_,
			std::size_t ReadOffset_, std::size_t VecSize_, typename VecT_
		>
		[[nodiscard]] static constexpr inline vector_type _make_vector_from_euler(const EmuMath::Vector<VecSize_, VecT_>& euler_vector_)
		{
			return _make_vector_from_euler
			(
				euler_vector_.template AtTheoretical<ReadOffset_>(),
				euler_vector_.template AtTheoretical<ReadOffset_ + 1>(),
				euler_vector_.template AtTheoretical<ReadOffset_ + 2>()
			);
		}

		template
		<
			bool IsRads_, bool PreferMultiplies_, std::size_t ConstexprIterations_, bool ConstexprMod_,
			std::size_t ReadOffset_, std::size_t VecSize_, typename VecT_
		>
		[[nodiscard]] static constexpr inline vector_type _make_vector_from_euler(EmuMath::Vector<VecSize_, VecT_>& euler_vector_)
		{
			return _make_vector_from_euler
			(
				euler_vector_.template AtTheoretical<ReadOffset_>(),
				euler_vector_.template AtTheoretical<ReadOffset_ + 1>(),
				euler_vector_.template AtTheoretical<ReadOffset_ + 2>()
			);
		}

		template
		<
			bool IsRads_, bool PreferMultiplies_, std::size_t ConstexprIterations_, bool ConstexprMod_,
			std::size_t ReadOffset_, std::size_t VecSize_, typename VecT_
		>
		[[nodiscard]] static constexpr inline vector_type _make_vector_from_euler(EmuMath::Vector<VecSize_, VecT_>&& euler_vector_)
		{
			using in_vector = EmuMath::Vector<VecSize_, VecT_>;
			return _make_vector_from_euler
			(
				_conditional_vector_move_get<ReadOffset_>(std::forward<in_vector>(euler_vector_)),
				_conditional_vector_move_get<ReadOffset_ + 1>(std::forward<in_vector>(euler_vector_)),
				_conditional_vector_move_get<ReadOffset_ + 2>(std::forward<in_vector>(euler_vector_))
			);
		}
#pragma endregion

#pragma region CONSTRUCTORS
	public:
		template<std::size_t Unused_ = 0, typename = std::enable_if_t<is_default_constructible<Unused_>()>>
		constexpr inline Quaternion() : data()
		{
		}

		template<std::size_t Unused_ = 0, typename = std::enable_if_t<is_vector_const_copy_constructible<Unused_>()>>
		constexpr inline Quaternion(const vector_type& quaternion_as_vector_) : data(quaternion_as_vector_)
		{
		}

		template<std::size_t Unused_ = 0, typename = std::enable_if_t<is_vector_non_const_copy_constructible<Unused_>()>>
		constexpr inline Quaternion(vector_type& quaternion_as_vector_) : data(quaternion_as_vector_)
		{
		}

		template<std::size_t Unused_ = 0, typename = std::enable_if_t<is_vector_move_constructible<Unused_>()>>
		constexpr inline Quaternion(vector_type&& quaternion_as_vector_) : data(std::move(quaternion_as_vector_))
		{
		}

		template<std::size_t VecSize_, typename VecT_, typename = std::enable_if_t<valid_euler_vector_const_ref_conversion_constructor_arg<VecSize_, VecT_>()>>
		constexpr inline Quaternion(const EmuMath::Vector<VecSize_, VecT_>& euler_vector_) : 
			data
			(
				_make_vector_from_euler
				<
					euler_cvt_constructor_is_rads,
					euler_cvt_constructor_prefer_multiplies,
					euler_cvt_constructor_constexpr_iterations,
					euler_cvt_constructor_constexpr_mod,
					euler_cvt_constructor_read_offset
				>(euler_vector_)
			)
		{
		}

		template<std::size_t VecSize_, typename VecT_, typename = std::enable_if_t<valid_euler_vector_ref_conversion_constructor_arg<VecSize_, VecT_>()>>
		constexpr inline Quaternion(EmuMath::Vector<VecSize_, VecT_>& euler_vector_) : 
			data
			(
				_make_vector_from_euler
				<
					euler_cvt_constructor_is_rads,
					euler_cvt_constructor_prefer_multiplies,
					euler_cvt_constructor_constexpr_iterations,
					euler_cvt_constructor_constexpr_mod,
					euler_cvt_constructor_read_offset
				>(euler_vector_)
			)
		{
		}

		template<std::size_t VecSize_, typename VecT_, typename = std::enable_if_t<valid_euler_vector_ref_conversion_constructor_arg<VecSize_, VecT_>()>>
		constexpr inline Quaternion(EmuMath::Vector<VecSize_, VecT_>&& euler_vector_) : 
			data
			(
				_make_vector_from_euler
				<
					euler_cvt_constructor_is_rads,
					euler_cvt_constructor_prefer_multiplies,
					euler_cvt_constructor_constexpr_iterations,
					euler_cvt_constructor_constexpr_mod,
					euler_cvt_constructor_read_offset
				>(std::move(euler_vector_))
			)
		{
		}

		template<typename Pitch_, typename Yaw_, typename Roll_, typename = std::enable_if_t<valid_euler_conversion_construction_args<Pitch_, Yaw_, Roll_>()>>
		constexpr inline Quaternion(Pitch_&& euler_pitch_, Yaw_&& euler_yaw_, Roll_&& euler_roll_) :
			data
			(
				_make_vector_from_euler
				<
					euler_cvt_constructor_is_rads,
					euler_cvt_constructor_prefer_multiplies,
					euler_cvt_constructor_constexpr_iterations,
					euler_cvt_constructor_constexpr_mod
				>(std::forward<Pitch_>(euler_pitch_), std::forward<Yaw_>(euler_yaw_), std::forward<Roll_>(euler_roll_))
			)
		{
		}
#pragma endregion

#pragma region UNDERLYING_DATA
	public:
		/// <summary>
		/// <para> The underlying data of this Quaternion, represented as a Vector. </para>
		/// <para> This should not be modified directly unless you are sure what you are doing. </para>
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
