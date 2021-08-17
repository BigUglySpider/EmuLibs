#ifndef EMU_MATH_GENERAL_MATH_H_INC_
#define EMU_MATH_GENERAL_MATH_H_INC_ 1

#include "../EmuCore/TMPHelpers/TypeComparators.h"
#include <limits>
#include <type_traits>

namespace EmuMath
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
				static_assert(false, "Attempted to use EmuMath SqrtConstexpr with an output type that is not a floating point.");
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
				static_assert(false, "Attempted to use EmuMath SqrtConstexpr with an input type that is neither floating point nor integral.");
			}
		}
		else
		{
			static_assert(false, "Attempted to use EmuMath SqrtConstexpr with an output type that is not a floating point.");
		}
	}

	template<typename FloatingPoint_>
	FloatingPoint_ DoCorrectStandardSqrt(const FloatingPoint_ val_)
	{
		if constexpr (std::is_floating_point_v<FloatingPoint_>)
		{
			if constexpr (std::is_same_v<FloatingPoint_, float>)
			{
				return sqrtf(val_);
			}
			else if constexpr (std::is_same_v<FloatingPoint_, double>)
			{
				return sqrt(val_);
			}
			else
			{
				return static_cast<FloatingPoint_>(sqrtl(static_cast<long double>(val_)));
			}
		}
		else
		{
			static_assert(false, "Passed a non-floating-point type to EmuMath::DoCorrectStandardSqrt. This behaviour is blocked.");
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
			// Cannot be rounded, so return a copy of val_.
			return val_;
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
			// Cannot be rounded, so return a copy of val_.
			return val_;
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
			// Cannot be rounded, so return a copy of val_.
			return val_;
		}
	}

	struct Pi
	{
		Pi() = delete;

		template<typename T>
		static constexpr T PI = T(3.141592653589793238462643383279502884197169399375105820974944592307816406286208998628034825342117067982148086513282306647093844);
		template<typename T>
		static constexpr T PI_DIV_180 = PI<T> / T(180);
		template<typename T>
		static constexpr T HUNDRED80_DIV_PI = T(180) / PI<T>;
		template<typename T>
		static constexpr T SQRT_PI = EmuMath::SqrtConstexpr<T, T>(PI<T>);
		template<typename T>
		static constexpr T PI_SQR = PI<T> * PI<T>;
		template<typename T>
		static constexpr T PI_CUBE = PI<T> * PI<T> * PI<T>;

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
		/// <summary> Alias of the EmuMath::Pi struct. </summary>
		using Pi_ = Pi;

		CommonConstants() = delete;

		/// <summary> Square root of the provided value N_ stores as the type OutT. </summary>
		template<typename OutT, typename N, N N_>
		static constexpr OutT SQRT_N = EmuMath::SqrtConstexpr<OutT, N>(N_);
		/// <summary> Square root of 2 stored as the provided type. </summary>
		template<typename T>
		static constexpr T SQRT_2 = SQRT_N<T, std::uint8_t, 2>;
		/// <summary> Square root of 3 stored as the provided type. </summary>
		template<typename T>
		static constexpr T SQRT_3 = SQRT_N<T, std::uint8_t, 3>;
	};

	/// <summary>
	/// <para> Functor which may be used to perform linear interpolations. </para>
	/// <para> Takes 3 type arguments, however only one or two may be passed. Type arguments not passed will be the same type as A_. </para>
	/// <para> Types should be considered for the equation A_ + ((B_ - A_) * T_). </para>
	/// <para> do_lerp&lt;void&gt;, do_lerp&lt;void, void&gt;, and do_lerp&lt;void, void, void&gt; are reserved for a generic specialisation of do_lerp. </para>
	/// </summary>
	/// <typeparam name="A_">Type used to represent a in the equation a + ((b - a) * t).</typeparam>
	/// <typeparam name="B_">Type used to represent b in the equation a + ((b - a) * t).</typeparam>
	/// <typeparam name="T_">Type used to represent t in the equation a + ((b - a) * t).</typeparam>
	template<class A_, class B_ = A_, class T_ = A_>
	struct do_lerp
	{
		constexpr do_lerp()
		{
		}
		[[nodiscard]] constexpr inline A_ operator()(const A_& a_, const B_& b_, const T_& t_) const
		{
			return static_cast<A_>(a_ + static_cast<A_>((b_ - a_) * t_));
		}
	};
	/// <summary>
	/// <para> Reserved generic specialisation of do_lerp. </para>
	/// <para> Determines the specialisation to make use of when the function operator() is called, based on the 3 arguments when called. </para>
	/// </summary>
	template<>
	struct do_lerp<void, void, void>
	{
		constexpr do_lerp()
		{
		}
		template<class A_, class B_, class T_>
		[[nodiscard]] constexpr inline auto operator()(const A_& a_, const B_& b_, const T_& t_) const
		{
			return do_lerp<A_, B_, T_>()(a_, b_, t_);
		}
	};

	template<typename T_>
	struct do_sqrt_constexpr
	{
		using Out_ = std::conditional_t<std::is_floating_point_v<T_>, T_, double>;

		constexpr do_sqrt_constexpr()
		{
		}
		[[nodiscard]] constexpr inline Out_ operator()(T_ val_) const
		{
			return SqrtConstexpr<Out_, T_>(val_);
		}
	};
	template<>
	struct do_sqrt_constexpr<void>
	{
		constexpr do_sqrt_constexpr()
		{
		}
		template<typename T_>
		[[nodiscard]] constexpr inline auto operator()(T_ val_) const
		{
			return do_sqrt_constexpr<T_>()(val_);
		}
	};

	template<typename T_>
	struct do_sqrt
	{
	private:
		using floating_point_ = std::conditional_t<std::is_floating_point_v<T_>, T_, double>;

	public:
		constexpr do_sqrt()
		{
		}
		[[nodiscard]] inline floating_point_ operator()(T_ val_) const
		{
			if constexpr (std::is_same_v<T_, floating_point_>)
			{
				return DoCorrectStandardSqrt<T_>(val_);
			}
			else
			{
				return DoCorrectStandardSqrt<floating_point_>(static_cast<floating_point_>(val_));
			}
		}
	};
	template<>
	struct do_sqrt<void>
	{
		constexpr do_sqrt()
		{
		}
		template<typename T_>
		[[nodiscard]] inline auto operator()(T_ val_) const
		{
			return do_sqrt<T_>()(val_);
		}
	};

	template<typename T_>
	struct do_floor
	{
		constexpr do_floor()
		{
		}
		[[nodiscard]] constexpr inline T_ operator()(const T_ val_) const
		{
			return DoCorrectFloor<T_>(val_);
		}
	};
	template<>
	struct do_floor<void>
	{
		constexpr do_floor()
		{
		}
		template<typename T_>
		[[nodiscard]] constexpr inline auto operator()(const T_ val_) const
		{
			return do_floor<T_>()(val_);
		}
	};

	template<typename T_>
	struct do_ceil
	{
		constexpr do_ceil()
		{
		}
		[[nodiscard]] constexpr inline T_ operator()(const T_ val_) const
		{
			return DoCorrectCeil<T_>(val_);
		}
	};
	template<>
	struct do_ceil<void>
	{
		constexpr do_ceil()
		{
		}
		template<typename T_>
		[[nodiscard]] constexpr inline auto operator()(const T_ val_) const
		{
			return do_ceil<T_>()(val_);
		}
	};

	template<typename T_>
	struct do_trunc
	{
		constexpr do_trunc()
		{
		}
		[[nodiscard]] constexpr inline T_ operator()(const T_ val_) const
		{
			return DoCorrectTrunc<T_>(val_);
		}
	};
	template<>
	struct do_trunc<void>
	{
		constexpr do_trunc()
		{
		}
		template<typename T_>
		[[nodiscard]] constexpr inline auto operator()(const T_ val_) const
		{
			return do_trunc<T_>()(val_);
		}
	};

	template<typename T_>
	struct do_left_shift
	{
		constexpr do_left_shift()
		{
		}
		constexpr inline T_ operator()(const T_ val_, const std::size_t num_shifts_) const
		{
			return val_ << num_shifts_;
		}
	};
	template<>
	struct do_left_shift<void>
	{
		constexpr do_left_shift()
		{
		}
		template<typename T_>
		constexpr inline T_ operator()(T_&& val_, std::size_t&& num_shifts_) const
		{
			return do_left_shift<T_>()(std::forward(val_), std::forward(num_shifts_));
		}
	};

	template<typename T_>
	struct do_right_shift
	{
		constexpr do_right_shift()
		{
		}
		constexpr inline T_ operator()(const T_ val_, const std::size_t num_shifts_) const
		{
			return val_ >> num_shifts_;
		}
	};
	template<>
	struct do_right_shift<void>
	{
		constexpr do_right_shift()
		{
		}
		template<typename T_>
		constexpr inline T_ operator()(T_&& val_, std::size_t&& num_shifts_) const
		{
			return do_right_shift<T_>()(std::forward(val_), std::forward(num_shifts_));
		}
	};
}

#endif
