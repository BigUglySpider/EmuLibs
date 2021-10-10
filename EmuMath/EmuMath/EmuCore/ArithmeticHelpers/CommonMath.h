#ifndef EMU_CORE_COMMON_MATH_H_INC_
#define EMU_CORE_COMMON_MATH_H_INC_ 1

#include "../TMPHelpers/TypeComparators.h"
#include <cstddef>
#include <cstdint>
#include <limits>
#include <type_traits>

namespace EmuCore
{
	namespace _underlying_general_funcs
	{
		template<typename Out_, typename In_>
		constexpr Out_ _sqrt_constexpr(In_ in_, Out_ current_, Out_ prev_)
		{
			constexpr Out_ half_ = Out_(0.5);

			if constexpr (std::is_floating_point_v<Out_>)
			{
				if (current_ == prev_)
				{
					return current_;
				}
				else
				{
					return _sqrt_constexpr<Out_, In_>(in_, half_ * (current_ + static_cast<Out_>(in_) / current_), current_);
				}
			}
			else
			{
				static_assert(false, "Attempted to use EmuCore SqrtConstexpr with an output type that is not a floating point.");
			}
		}
	}

	/// <summary>
	/// <para> Compile-time evaluable square root functionality using Newton Raphson Iteration. Must be output as a floating point type. </para>
	/// <para> It is recommended to only use this when compile-time constants are needed, as the standard sqrt (and variants) is much faster (albeit not constexpr). </para>
	/// </summary>
	/// <typeparam name="In_">Type being passed to the function.</typeparam>
	/// <typeparam name="OutFP_">Type to output as the square root. Must be a floating point.</typeparam>
	/// <param name="in_">Value to find the square root of.</param>
	/// <returns>Passed OutFP_ floating point representation of the square root of the passed value in_.</returns>
	template<typename OutFP_ = float, typename In_ = OutFP_>
	constexpr OutFP_ SqrtConstexpr(In_ in_)
	{
		if constexpr (std::is_floating_point_v<OutFP_>)
		{
			if constexpr (std::is_floating_point_v<In_>)
			{
				if (in_ >= 0 && in_ < std::numeric_limits<In_>::infinity())
				{
					return _underlying_general_funcs::_sqrt_constexpr<OutFP_, In_>(in_, static_cast<OutFP_>(in_), OutFP_());
				}
				else
				{
					return std::numeric_limits<OutFP_>::quiet_NaN();
				}
			}
			else if constexpr (std::is_integral_v<In_>)
			{
				if constexpr (std::is_signed_v<In_>)
				{
					if (in_ < 0)
					{
						return std::numeric_limits<OutFP_>::quiet_NaN();
					}
					else
					{
						return _underlying_general_funcs::_sqrt_constexpr<OutFP_, In_>(in_, static_cast<OutFP_>(in_), OutFP_());
					}
				}
				else
				{
					return _underlying_general_funcs::_sqrt_constexpr<OutFP_, In_>(in_, static_cast<OutFP_>(in_), OutFP_());
				}
			}
			else
			{
				static_assert(false, "Attempted to use EmuCore::SqrtConstexpr with an input type that is neither floating point nor integral. Did you mean to use the do_sqrt_constexpr functor?");
			}
		}
		else
		{
			static_assert(false, "Attempted to use EmuCore::SqrtConstexpr with an output type that is not a floating point.");
		}
	}

	template<typename FloatingPointOut_ = float, typename FloatingPointIn_>
	FloatingPointOut_ DoMatchingCos(const FloatingPointIn_ val_)
	{
		if constexpr (std::is_floating_point_v<FloatingPointOut_>)
		{
			if constexpr (std::is_same_v<FloatingPointIn_, float>)
			{
				return static_cast<FloatingPointOut_>(cosf(val_));
			}
			else if constexpr (std::is_same_v<FloatingPointIn_, double>)
			{
				return static_cast<FloatingPointOut_>(cos(val_));
			}
			else if constexpr(std::is_same_v<FloatingPointIn_, long double>)
			{
				return static_cast<FloatingPointOut_>(cosl(static_cast<long double>(val_)));
			}
			else if constexpr(std::is_convertible_v<FloatingPointIn_, float>)
			{
				return DoMatchingCos<FloatingPointOut_, float>(static_cast<float>(val_));
			}
			else if constexpr (std::is_convertible_v<FloatingPointIn_, double>)
			{
				return DoMatchingCos<FloatingPointOut_, double>(static_cast<double>(val_));
			}
			else if constexpr (std::is_constructible_v<FloatingPointIn_, long double>)
			{
				return DoMatchingCos<FloatingPointOut_, long double>(static_cast<long double>(val_));
			}
			else
			{
				static_assert(false, "Passed a non-floating-point input type (that cannot be cast to a floating point) to EmuCore::DoMatchingCos.");
			}
		}
		else
		{
			static_assert(false, "Passed a non-floating-point output type to EmuCore::DoMatchingCos. Did you mean to use the do_cos functor?");
		}
	}
	template<typename FloatingPointOut_ = float, typename FloatingPointIn_>
	FloatingPointOut_ DoMatchingAcos(const FloatingPointIn_ val_)
	{
		if constexpr (std::is_floating_point_v<FloatingPointOut_>)
		{
			if constexpr (std::is_same_v<FloatingPointIn_, float>)
			{
				return static_cast<FloatingPointOut_>(acosf(val_));
			}
			else if constexpr (std::is_same_v<FloatingPointIn_, double>)
			{
				return static_cast<FloatingPointOut_>(acos(val_));
			}
			else if constexpr (std::is_same_v<FloatingPointIn_, long double>)
			{
				return static_cast<FloatingPointOut_>(acosl(static_cast<long double>(val_)));
			}
			else if constexpr (std::is_convertible_v<FloatingPointIn_, float>)
			{
				return DoMatchingAcos<FloatingPointOut_, float>(static_cast<float>(val_));
			}
			else if constexpr (std::is_convertible_v<FloatingPointIn_, double>)
			{
				return DoMatchingAcos<FloatingPointOut_, double>(static_cast<double>(val_));
			}
			else if constexpr (std::is_constructible_v<FloatingPointIn_, long double>)
			{
				return DoMatchingAcos<FloatingPointOut_, long double>(static_cast<long double>(val_));
			}
			else
			{
				static_assert(false, "Passed a non-floating-point input type (that cannot be cast to a floating point) to EmuCore::DoMatchingAcos.");
			}
		}
		else
		{
			static_assert(false, "Passed a non-floating-point output type to EmuCore::DoMatchingAcos. Did you mean to use the do_acos functor?");
		}
	}

	template<typename FloatingPointOut_ = float, typename FloatingPointIn_>
	FloatingPointOut_ DoMatchingSin(const FloatingPointIn_ val_)
	{
		if constexpr (std::is_floating_point_v<FloatingPointOut_>)
		{
			if constexpr (std::is_same_v<FloatingPointIn_, float>)
			{
				return static_cast<FloatingPointOut_>(sinf(val_));
			}
			else if constexpr (std::is_same_v<FloatingPointIn_, double>)
			{
				return static_cast<FloatingPointOut_>(sin(val_));
			}
			else if constexpr (std::is_same_v<FloatingPointIn_, long double>)
			{
				return static_cast<FloatingPointOut_>(sinl(static_cast<long double>(val_)));
			}
			else if constexpr (std::is_convertible_v<FloatingPointIn_, float>)
			{
				return DoMatchingSin<FloatingPointOut_, float>(static_cast<float>(val_));
			}
			else if constexpr (std::is_convertible_v<FloatingPointIn_, double>)
			{
				return DoMatchingSin<FloatingPointOut_, double>(static_cast<double>(val_));
			}
			else if constexpr (std::is_constructible_v<FloatingPointIn_, long double>)
			{
				return DoMatchingSin<FloatingPointOut_, long double>(static_cast<long double>(val_));
			}
			else
			{
				static_assert(false, "Passed a non-floating-point input type (that cannot be cast to a floating point) to EmuCore::DoMatchingSin.");
			}
		}
		else
		{
			static_assert(false, "Passed a non-floating-point output type to EmuCore::DoMatchingSin. Did you mean to use the do_sin functor?");
		}
	}
	template<typename FloatingPointOut_ = float, typename FloatingPointIn_>
	FloatingPointOut_ DoMatchingAsin(const FloatingPointIn_ val_)
	{
		if constexpr (std::is_floating_point_v<FloatingPointOut_>)
		{
			if constexpr (std::is_same_v<FloatingPointIn_, float>)
			{
				return static_cast<FloatingPointOut_>(asinf(val_));
			}
			else if constexpr (std::is_same_v<FloatingPointIn_, double>)
			{
				return static_cast<FloatingPointOut_>(asin(val_));
			}
			else if constexpr (std::is_same_v<FloatingPointIn_, long double>)
			{
				return static_cast<FloatingPointOut_>(asinl(static_cast<long double>(val_)));
			}
			else if constexpr (std::is_convertible_v<FloatingPointIn_, float>)
			{
				return DoMatchingAsin<FloatingPointOut_, float>(static_cast<float>(val_));
			}
			else if constexpr (std::is_convertible_v<FloatingPointIn_, double>)
			{
				return DoMatchingAsin<FloatingPointOut_, double>(static_cast<double>(val_));
			}
			else if constexpr (std::is_constructible_v<FloatingPointIn_, long double>)
			{
				return DoMatchingAsin<FloatingPointOut_, long double>(static_cast<long double>(val_));
			}
			else
			{
				static_assert(false, "Passed a non-floating-point input type (that cannot be cast to a floating point) to EmuCore::DoMatchingAsin.");
			}
		}
		else
		{
			static_assert(false, "Passed a non-floating-point output type to EmuCore::DoMatchingAsin. Did you mean to use the do_asin functor?");
		}
	}

	template<typename FloatingPointOut_ = float, typename FloatingPointIn_>
	FloatingPointOut_ DoMatchingTan(const FloatingPointIn_ val_)
	{
		if constexpr (std::is_floating_point_v<FloatingPointOut_>)
		{
			if constexpr (std::is_same_v<FloatingPointIn_, float>)
			{
				return static_cast<FloatingPointOut_>(tanf(val_));
			}
			else if constexpr (std::is_same_v<FloatingPointIn_, double>)
			{
				return static_cast<FloatingPointOut_>(tan(val_));
			}
			else if constexpr (std::is_same_v<FloatingPointIn_, long double>)
			{
				return static_cast<FloatingPointOut_>(tanl(static_cast<long double>(val_)));
			}
			else if constexpr (std::is_convertible_v<FloatingPointIn_, float>)
			{
				return DoMatchingTan<FloatingPointOut_, float>(static_cast<float>(val_));
			}
			else if constexpr (std::is_convertible_v<FloatingPointIn_, double>)
			{
				return DoMatchingTan<FloatingPointOut_, double>(static_cast<double>(val_));
			}
			else if constexpr (std::is_constructible_v<FloatingPointIn_, long double>)
			{
				return DoMatchingTan<FloatingPointOut_, long double>(static_cast<long double>(val_));
			}
			else
			{
				static_assert(false, "Passed a non-floating-point input type (that cannot be cast to a floating point) to EmuCore::DoMatchingTan.");
			}
		}
		else
		{
			static_assert(false, "Passed a non-floating-point output type to EmuCore::DoMatchingTan. Did you mean to use the do_tan functor?");
		}
	}
	template<typename FloatingPointOut_ = float, typename FloatingPointIn_>
	FloatingPointOut_ DoMatchingAtan(const FloatingPointIn_ val_)
	{
		if constexpr (std::is_floating_point_v<FloatingPointOut_>)
		{
			if constexpr (std::is_same_v<FloatingPointIn_, float>)
			{
				return static_cast<FloatingPointOut_>(atanf(val_));
			}
			else if constexpr (std::is_same_v<FloatingPointIn_, double>)
			{
				return static_cast<FloatingPointOut_>(atan(val_));
			}
			else if constexpr (std::is_same_v<FloatingPointIn_, long double>)
			{
				return static_cast<FloatingPointOut_>(atanl(static_cast<long double>(val_)));
			}
			else if constexpr (std::is_convertible_v<FloatingPointIn_, float>)
			{
				return DoMatchingAtan<FloatingPointOut_, float>(static_cast<float>(val_));
			}
			else if constexpr (std::is_convertible_v<FloatingPointIn_, double>)
			{
				return DoMatchingAtan<FloatingPointOut_, double>(static_cast<double>(val_));
			}
			else if constexpr (std::is_constructible_v<FloatingPointIn_, long double>)
			{
				return DoMatchingAtan<FloatingPointOut_, long double>(static_cast<long double>(val_));
			}
			else
			{
				static_assert(false, "Passed a non-floating-point input type (that cannot be cast to a floating point) to EmuCore::DoMatchingAtan.");
			}
		}
		else
		{
			static_assert(false, "Passed a non-floating-point output type to EmuCore::DoMatchingAtan. Did you mean to use the do_atan functor?");
		}
	}

	template<std::size_t Val_, typename T_>
	struct factorial
	{
		constexpr factorial()
		{
		}

		static constexpr T_ value = static_cast<T_>(Val_) * factorial<Val_ - 1, T_>::value;
		constexpr inline operator T_() const
		{
			return value;
		}
	};
	template<typename T_>
	struct factorial<1, T_>
	{
		static constexpr T_ value = static_cast<T_>(1);
	};
	template<typename T_>
	struct factorial<0, T_>
	{
		static constexpr T_ value = T_();
	};
	template<std::size_t Val_, typename T_>
	static constexpr T_ factorial_v = factorial<Val_, T_>::value;

	template<typename FloatingPointOut_ = float, typename FloatingPointIn_>
	FloatingPointOut_ DoMatchingStandardSqrt(const FloatingPointIn_ val_)
	{
		if constexpr (std::is_floating_point_v<FloatingPointIn_>)
		{
			if constexpr (std::is_same_v<FloatingPointIn_, float>)
			{
				return static_cast<FloatingPointOut_>(sqrtf(val_));
			}
			else if constexpr (std::is_same_v<FloatingPointIn_, double>)
			{
				return static_cast<FloatingPointOut_>(sqrt(val_));
			}
			else
			{
				return static_cast<FloatingPointOut_>(sqrtl(static_cast<long double>(val_)));
			}
		}
		else
		{
			static_assert(false, "Passed a non-floating-point output type to EmuCore::DoMatchingStandardSqrt. Did you mean to use the do_sqrt functor?");
		}
	}

	template<typename T_>
	T_ DoCorrectFloor(const T_ val_)
	{
		if constexpr (std::is_floating_point_v<T_>)
		{
			if constexpr (std::is_same_v<T_, float>)
			{
				return floorf(val_);
			}
			else if constexpr (std::is_same_v<T_, double>)
			{
				return floor(val_);
			}
			else
			{
				return static_cast<T_>(floorl(static_cast<long double>(val_)));
			}
		}
		else
		{
			if constexpr (std::is_arithmetic_v<T_>)
			{
				// Already integral, so return a copy of val_.
				return val_;
			}
			else
			{
				static_assert(false, "Attempted to perform EmuCore::DoCorrectFloor with a non-arithmetic type. Did you mean to use the do_floor functor?");
			}
		}
	}
	template<typename T_>
	T_ DoCorrectCeil(const T_ val_)
	{
		if constexpr (std::is_floating_point_v<T_>)
		{
			if constexpr (std::is_same_v<T_, float>)
			{
				return ceilf(val_);
			}
			else if constexpr (std::is_same_v<T_, double>)
			{
				return ceil(val_);
			}
			else
			{
				return static_cast<T_>(ceill(static_cast<long double>(val_)));
			}
		}
		else
		{
			if constexpr (std::is_arithmetic_v<T_>)
			{
				// Already integral, so return a copy of val_.
				return val_;
			}
			else
			{
				static_assert(false, "Attempted to perform EmuCore::DoCorrectCeil with a non-arithmetic type. Did you mean to use the do_ceil functor?");
			}
		}
	}
	template<typename T_>
	T_ DoCorrectTrunc(const T_ val_)
	{
		if constexpr (std::is_floating_point_v<T_>)
		{
			if constexpr (std::is_same_v<T_, float>)
			{
				return truncf(val_);
			}
			else if constexpr (std::is_same_v<T_, double>)
			{
				return trunc(val_);
			}
			else
			{
				return static_cast<T_>(truncl(static_cast<long double>(val_)));
			}
		}
		else
		{
			if constexpr (std::is_arithmetic_v<T_>)
			{
				// Already integral, so return a copy of val_.
				return val_;
			}
			else
			{
				static_assert(false, "Attempted to perform EmuCore::DoCorrectTrunc with a non-arithmetic type. Did you mean to use the do_trunc functor?");
			}
		}
	}

	template<typename T_, std::size_t Power_>
	struct do_pow
	{
		constexpr do_pow()
		{
		}
		[[nodiscard]] constexpr inline T_ operator()(const T_& val_)
		{
			return val_ * do_pow<T_, Power_ - 1>()(val_);
		}
	};
	template<typename T_>
	struct do_pow<T_, 1>
	{
		constexpr do_pow()
		{
		}
		[[nodiscard]] constexpr inline T_ operator()(const T_& val_)
		{
			// x^1 always == x
			return val_;
		}
	};
	template<typename T_>
	struct do_pow<T_, 0>
	{
		constexpr do_pow()
		{
		}
		[[nodiscard]] constexpr inline T_ operator()(const T_& val_)
		{
			// x^0 always == 1
			return T_(1);
		}
	};

	/// <summary> Variant of fmod which may be used to calculate floating-point modulo at compile time. </summary>
	/// <typeparam name="Lhs_">Type of lhs argument. Should ideally be floating-point considering the use of this function.</typeparam>
	/// <typeparam name="Rhs_">Type of rhs argument.</typeparam>
	/// <param name="lhs_">Value to divide, acting as lhs_ in the expression lhs_ % rhs_. This should be a floating-point value due to the nature of this function.</param>
	/// <param name="rhs_">Value to divide by, acting as rhs_ in the expression lhs_ % rhs_.</param>
	/// <returns>Floating-point mod of the provided arguments, expressed as the type Lhs_.</returns>
	template<typename Lhs_, typename Rhs_>
	constexpr inline Lhs_ FmodConstexpr(const Lhs_& lhs_, const Rhs_& rhs_)
	{
		return static_cast<Lhs_>(lhs_ - (static_cast<std::int64_t>(lhs_ / rhs_) * rhs_));
	}

	struct Pi
	{
		Pi() = delete;

		/// <summary> Approximation of pi represented as the provided type T. </summary>
		template<typename T>
		static constexpr T PI = T(3.141592653589793238462643383279502884197169399375105820974944592307816406286208998628034825342117067982148086513282306647093844L);
		/// <summary> Approximation of pi / 180, which may be used to convert degree units to radian units. </summary>
		template<typename T>
		static constexpr T PI_DIV_180 = PI<T> / T(180);
		/// <summary> Approximation of 180 / pi, which may be used to convert radian units to degree units. </summary>
		template<typename T>
		static constexpr T HUNDRED80_DIV_PI = T(180) / PI<T>;
		template<typename T>
		static constexpr T SQRT_PI = EmuCore::SqrtConstexpr<T, T>(PI<T>);
		template<typename T_, std::size_t Power_>
		static constexpr T_ PI_POW = do_pow<T_, Power_>()(PI<T_>);
		template<typename T>
		static constexpr T PI_SQR = PI_POW<T, 2>;
		template<typename T>
		static constexpr T PI_CUBE = PI_POW<T, 3>;

		template<typename T>
		static constexpr T RadsToDegs(const T rads_)
		{
			return rads_ * HUNDRED80_DIV_PI<T>;
		}
		template<typename T>
		static constexpr T DegsToRads(const T degs_)
		{
			return degs_ * PI_DIV_180<T>;
		}
		template<typename OutT, typename InT, InT rads_>
		static constexpr OutT RadsToDegs_v = RadsToDegs<OutT>(static_cast<OutT>(rads_));
		template<typename OutT, typename InT, InT degs_>
		static constexpr OutT DegsToRads_v = DegsToRads<OutT>(static_cast<OutT>(degs_));
	};

	struct CommonConstants
	{
		/// <summary> Alias of the EmuCore::Pi struct. </summary>
		using Pi_ = Pi;

		CommonConstants() = delete;

		/// <summary> Square root of the provided value N_ stores as the type OutT. </summary>
		template<typename OutT, typename N, N N_>
		static constexpr OutT SQRT_N = EmuCore::SqrtConstexpr<OutT, N>(N_);
		/// <summary> Square root of 2 stored as the provided type. </summary>
		template<typename T>
		static constexpr T SQRT_2 = SQRT_N<T, std::uint8_t, 2>;
		/// <summary> Square root of 3 stored as the provided type. </summary>
		template<typename T>
		static constexpr T SQRT_3 = SQRT_N<T, std::uint8_t, 3>;
	};

	/// <summary>
	/// <para> Performs Newton's Method for a specified number of iterations, using the provided. </para>
	/// <para> Each iteration can be summarised as: y_ = y_ * (constant_ - (x_ * y_ * y_)). </para>
	/// <para> After the final iteration of this calculation, the value of y_ is returned. </para>
	/// </summary>
	/// <typeparam name="OutT_">Type to output the result as.</typeparam>
	/// <typeparam name="InX_">Type used for the x_ argument.</typeparam>
	/// <typeparam name="InY_">Type used for the y_ argument.</typeparam>
	/// <typeparam name="ConstantT_">Type used for the constant_ argument.</typeparam>
	/// <param name="x_">Value that will be constantly used as x_ in the described calculation every iteration.</param>
	/// <param name="y_">Initial value of y_ before iterating the described calculation.</param>
	/// <param name="constant_">Value used as constant_ in the described calculation every iteration.</param>
	/// <returns>Result of Newton's Method being performed for the provided number of iterations with the provided operands.</returns>
	template<std::size_t NumIterations_, typename OutT_ = float, typename InX_, typename InY_, typename ConstantT_, std::size_t CurrentIteration_ = 0>
	constexpr inline OutT_ NewtonsMethod(const InX_ x_, const InY_ y_, const ConstantT_ constant_)
	{
		if constexpr (CurrentIteration_ < NumIterations_)
		{
			return NewtonsMethod<NumIterations_, OutT_, InX_, InY_, ConstantT_, CurrentIteration_ + 1>(x_, static_cast<InY_>(y_ * (constant_ - (x_ * y_ * y_))), constant_);
		}
		else
		{
			return static_cast<OutT_>(y_);
		}
	}

	/// <summary>
	/// <para> Calculates the reciprocal to the square root of the passed in_ value, represented as the provided OutFloatingPoint_ type. </para>
	/// <para> By default, performs 1 Newton's Method iteration to improve accuracy. More iterations may be requested to increase accuracy. </para>
	/// <para> A magic constant is used for some bit manipulation. It is recommended to only change this from the default (0x5F3759DF) if you know what you are doing. </para>
	/// <para> More information regarding the algorithm may be found here: https://en.wikipedia.org/wiki/Fast_inverse_square_root#Overview_of_the_code </para>
	/// </summary>
	/// <typeparam name="InT_">Type being input to find the reciprocal to the square root of.</typeparam>
	/// <typeparam name="OutFloatingPoint_">Type to output the reciprocal as.</typeparam>
	/// <param name="in_">Value to find the reciprocal to the square root of.</param>
	/// <returns>
	///		Close approximation of the reciprocal to the provided in_ value's square root, represented as the provided OutFloatingPoint_. 
	///		The accuracy of this value increases with more newton iterations.
	/// </returns>
	template<typename OutFloatingPoint_ = float, std::size_t NumNewtonIterations_ = 1, std::int32_t MagicConstant_ = 0x5F3759DF, typename InT_>
	inline OutFloatingPoint_ Q_rsqrt(const InT_ in_)
	{
		if constexpr (std::is_floating_point_v<OutFloatingPoint_>)
		{
			using int_type = std::int32_t;

			float y_ = static_cast<float>(in_);
			float x_ = y_ * 0.5f;
			int_type i_ = *reinterpret_cast<const int_type*>(&y_);
			i_ = MagicConstant_ - (i_ >> 1);
			y_ = *reinterpret_cast<const float*>(&i_);
			return NewtonsMethod<NumNewtonIterations_, OutFloatingPoint_, float, float, float>(x_, y_, 1.5f);
		}
		else
		{
			static_assert(false, "Attempted to perform Q_rsqrt with a non-floating-point output type.");
		}
	}

	template<typename T_>
	constexpr inline T_ AbsConstexpr(const T_ val_)
	{
		return val_ > T_() ? val_ : -val_;
	}
	template<>
	constexpr inline std::int8_t AbsConstexpr(const std::int8_t val_)
	{
		return (val_ + (val_ >> 7)) ^ (val_ >> 7);
	}
	template<>
	constexpr inline std::int16_t AbsConstexpr(const std::int16_t val_)
	{
		return (val_ + (val_ >> 15)) ^ (val_ >> 15);
	}
	template<>
	constexpr inline std::int32_t AbsConstexpr(const std::int32_t val_)
	{
		return (val_ + (val_ >> 31)) ^ (val_ >> 31);
	}
	template<>
	constexpr inline std::int64_t AbsConstexpr(const std::int64_t val_)
	{
		return (val_ + (val_ >> 63)) ^ (val_ >> 63);
	}

	template<typename FP_>
	constexpr inline bool FpNearEqual(FP_ lhs_, FP_ rhs_, FP_ epsilon_ = std::numeric_limits<FP_>::epsilon())
	{
		FP_ delta_ = lhs_ - rhs_;
		return AbsConstexpr<FP_>(delta_) <= epsilon_;
	}
}

#endif
