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
	public:
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
			using in_x = decltype(std::declval<in_vector>().template AtTheoretical<ReadOffset_>());
			using in_y = decltype(std::declval<in_vector>().template AtTheoretical<ReadOffset_ + 1>());
			using in_z = decltype(std::declval<in_vector>().template AtTheoretical<ReadOffset_ + 2>());
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
					euler_cvt_default_read_offset,
					IsConst_,
					euler_cvt_default_constexpr_iterations,
					euler_cvt_default_constexpr_mod,
					euler_cvt_default_prefer_multiplies,
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
				euler_cvt_default_is_rads,
				false
			>();
		}
#pragma endregion

#pragma region CONSTRUCTOR_HELPERS
	private:
		template<bool IsRads_, bool PreferMultiplies_, std::size_t ConstexprIterations_, bool ConstexprMod_, typename X_, typename Y_, typename Z_>
		[[nodiscard]] static constexpr inline vector_type _make_vector_from_euler(X_&& euler_x_, Y_&& euler_y_, Z_&& euler_z_)
		{
			if constexpr (_valid_euler_conversion_args<X_, Y_, Z_, ConstexprIterations_, ConstexprMod_, PreferMultiplies_, IsRads_, true>())
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
			return _make_vector_from_euler<IsRads_, PreferMultiplies_, ConstexprIterations_, ConstexprMod_>
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
			return _make_vector_from_euler<IsRads_, PreferMultiplies_, ConstexprIterations_, ConstexprMod_>
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
			return _make_vector_from_euler<IsRads_, PreferMultiplies_, ConstexprIterations_, ConstexprMod_>
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
		constexpr inline Quaternion() : data(vector_type::get_implied_zero(), vector_type::get_implied_zero(), vector_type::get_implied_zero(), value_type_uq(1))
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
					euler_cvt_default_is_rads,
					euler_cvt_default_prefer_multiplies,
					euler_cvt_default_constexpr_iterations,
					euler_cvt_default_constexpr_mod,
					euler_cvt_default_read_offset
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
					euler_cvt_default_is_rads,
					euler_cvt_default_prefer_multiplies,
					euler_cvt_default_constexpr_iterations,
					euler_cvt_default_constexpr_mod,
					euler_cvt_default_read_offset
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
					euler_cvt_default_is_rads,
					euler_cvt_default_prefer_multiplies,
					euler_cvt_default_constexpr_iterations,
					euler_cvt_default_constexpr_mod,
					euler_cvt_default_read_offset
				>(std::move(euler_vector_))
			)
		{
		}

		template<typename X_, typename Y_, typename Z_, typename = std::enable_if_t<valid_euler_conversion_construction_args<X_, Y_, Z_>()>>
		constexpr inline Quaternion(X_&& euler_x_, Y_&& euler_y_, Z_&& euler_z_) :
			data
			(
				_make_vector_from_euler
				<
					euler_cvt_default_is_rads,
					euler_cvt_default_prefer_multiplies,
					euler_cvt_default_constexpr_iterations,
					euler_cvt_default_constexpr_mod
				>(std::forward<X_>(euler_x_), std::forward<Y_>(euler_y_), std::forward<Z_>(euler_z_))
			)
		{
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
		template<bool IsRads_ = euler_cvt_default_is_rads, bool PreferMultiplies_ = euler_cvt_default_prefer_multiplies, typename X_, typename Y_, typename Z_>
		[[nodiscard]] static constexpr inline auto from_euler(X_&& euler_x_, Y_&& euler_y_, Z_&& euler_z_)
			-> std::enable_if_t<_valid_euler_conversion_args<X_, Y_, Z_, 0, false, PreferMultiplies_, IsRads_, false>(), EmuMath::Quaternion<T_>>
		{
			return EmuMath::Quaternion<T_>
			(
				_make_vector_from_euler<IsRads_, PreferMultiplies_, 0, false>
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
			bool IsRads_ = euler_cvt_default_is_rads, bool PreferMultiplies_ = euler_cvt_default_prefer_multiplies, std::size_t ReadOffset_ = 0,
			typename VecT_, std::size_t VecSize_
		>
		[[nodiscard]] static constexpr inline auto from_euler(const EmuMath::Vector<VecSize_, VecT_>& euler_xyz_)
			-> std::enable_if_t
			<
				_valid_euler_vector_lvalue_conversion_arg<VecSize_, VecT_, ReadOffset_, true, 0, false, PreferMultiplies_, IsRads_, false>(),
				EmuMath::Quaternion<T_>
			>
		{
			return EmuMath::Quaternion<T_>
			(
				_make_vector_from_euler<IsRads_, PreferMultiplies_, 0, false, ReadOffset_>(euler_xyz_)
			);
		}
		
		template
		<
			bool IsRads_ = euler_cvt_default_is_rads, bool PreferMultiplies_ = euler_cvt_default_prefer_multiplies, std::size_t ReadOffset_ = 0,
			typename VecT_, std::size_t VecSize_
		>
		[[nodiscard]] static constexpr inline auto from_euler(EmuMath::Vector<VecSize_, VecT_>& euler_xyz_)
			-> std::enable_if_t
			<
				_valid_euler_vector_lvalue_conversion_arg<VecSize_, VecT_, ReadOffset_, false, 0, false, PreferMultiplies_, IsRads_, false>(),
				EmuMath::Quaternion<T_>
			>
		{
			return EmuMath::Quaternion<T_>
			(
				_make_vector_from_euler<IsRads_, PreferMultiplies_, 0, false, ReadOffset_>(euler_xyz_)
			);
		}

		template
		<
			bool IsRads_ = euler_cvt_default_is_rads, bool PreferMultiplies_ = euler_cvt_default_prefer_multiplies, std::size_t ReadOffset_ = 0,
			typename VecT_, std::size_t VecSize_
		>
		[[nodiscard]] static constexpr inline auto from_euler(EmuMath::Vector<VecSize_, VecT_>&& euler_xyz_)
			-> std::enable_if_t
			<
				_valid_euler_vector_rvalue_conversion_arg<VecSize_, VecT_, ReadOffset_, 0, false, PreferMultiplies_, IsRads_, false>(),
				EmuMath::Quaternion<T_>
			>
		{
			return EmuMath::Quaternion<T_>
			(
				_make_vector_from_euler<IsRads_, PreferMultiplies_, 0, false, ReadOffset_>(std::forward<decltype(euler_xyz_)>(euler_xyz_))
			);
		}

		/// <summary>
		/// <para> Creates a new Quaternion of this type, which converts the rotation depicted by the passed euler representation. </para>
		/// <para> Makes use of alternative approaches to trigonometric functions to allow the conversion to be calculated in a constexpr context. </para>
		/// <para> `TrigIterations_` is the number of iterations to perform for trigonometric functions. This cannot be 0, and defaults to 3. </para>
		/// <para> 
		///		`TrigMod_` is a boolean flag indicating if a floating-point modulo operation should be performed to ensure angles are within 360 degree constraints,
		///		for the purpose of calculating trignometric functions. This defaults to true, but can safely be set to false if you know a mod is not required for a value.
		/// </para>
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
			bool IsRads_ = euler_cvt_default_is_rads, std::size_t TrigIterations_ = 3, bool TrigMod_ = true,
			bool PreferMultiplies_ = euler_cvt_default_prefer_multiplies, typename X_, typename Y_, typename Z_
		>
		[[nodiscard]] static constexpr inline auto from_euler_constexpr(X_&& euler_x_, Y_&& euler_y_, Z_&& euler_z_)
			-> std::enable_if_t
			<
				TrigIterations_ != 0 && _valid_euler_conversion_args<X_, Y_, Z_, TrigIterations_, TrigMod_, PreferMultiplies_, IsRads_, false>(),
				EmuMath::Quaternion<T_>
			>
		{
			return EmuMath::Quaternion<T_>
			(
				_make_vector_from_euler<IsRads_, PreferMultiplies_, TrigIterations_, TrigMod_>
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
		/// <para> `TrigIterations_` is the number of iterations to perform for trigonometric functions. This cannot be 0, and defaults to 3. </para>
		/// <para> 
		///		`TrigMod_` is a boolean flag indicating if a floating-point modulo operation should be performed to ensure angles are within 360 degree constraints,
		///		for the purpose of calculating trignometric functions. This defaults to true, but can safely be set to false if you know a mod is not required for a value.
		/// </para>
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
			bool IsRads_ = euler_cvt_default_is_rads, std::size_t TrigIterations_ = 3, bool TrigMod_ = true,
			bool PreferMultiplies_ = euler_cvt_default_prefer_multiplies, std::size_t ReadOffset_ = 0, typename VecT_, std::size_t VecSize_
		>
		[[nodiscard]] static constexpr inline auto from_euler_constexpr(const EmuMath::Vector<VecSize_, VecT_>& euler_xyz_)
			-> std::enable_if_t
			<
				TrigIterations_ != 0 && _valid_euler_vector_lvalue_conversion_arg<VecSize_, VecT_, ReadOffset_, true, TrigIterations_, TrigMod_, PreferMultiplies_, IsRads_, false>(),
				EmuMath::Quaternion<T_>
			>
		{
			return EmuMath::Quaternion<T_>
			(
				_make_vector_from_euler<IsRads_, PreferMultiplies_, TrigIterations_, TrigMod_, ReadOffset_>(euler_xyz_)
			);
		}

		template
		<
			bool IsRads_ = euler_cvt_default_is_rads, std::size_t TrigIterations_ = 3, bool TrigMod_ = true,
			bool PreferMultiplies_ = euler_cvt_default_prefer_multiplies, std::size_t ReadOffset_ = 0, typename VecT_, std::size_t VecSize_
		>
		[[nodiscard]] static constexpr inline auto from_euler_constexpr(EmuMath::Vector<VecSize_, VecT_>& euler_xyz_)
			-> std::enable_if_t
			<
				TrigIterations_ != 0 && _valid_euler_vector_lvalue_conversion_arg<VecSize_, VecT_, ReadOffset_, false, TrigIterations_, TrigMod_, PreferMultiplies_, IsRads_, false>(),
				EmuMath::Quaternion<T_>
			>
		{
			return EmuMath::Quaternion<T_>
			(
				_make_vector_from_euler<IsRads_, PreferMultiplies_, TrigIterations_, TrigMod_, ReadOffset_>(euler_xyz_)
			);
		}

		template
		<
			bool IsRads_ = euler_cvt_default_is_rads, std::size_t TrigIterations_ = 3, bool TrigMod_ = true,
			bool PreferMultiplies_ = euler_cvt_default_prefer_multiplies, std::size_t ReadOffset_ = 0, typename VecT_, std::size_t VecSize_
		>
		[[nodiscard]] static constexpr inline auto from_euler_constexpr(EmuMath::Vector<VecSize_, VecT_>&& euler_xyz_)
			-> std::enable_if_t
			<
				TrigIterations_ != 0 && _valid_euler_vector_rvalue_conversion_arg<VecSize_, VecT_, ReadOffset_, TrigIterations_, TrigMod_, PreferMultiplies_, IsRads_, false>(),
				EmuMath::Quaternion<T_>
			>
		{
			return EmuMath::Quaternion<T_>
			(
				_make_vector_from_euler<IsRads_, PreferMultiplies_, TrigIterations_, TrigMod_, ReadOffset_>(std::forward<decltype(euler_xyz_)>(euler_xyz_))
			);
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
