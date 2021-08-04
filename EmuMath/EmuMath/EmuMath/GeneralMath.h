#ifndef EMU_MATH_GENERAL_MATH_H_INC_
#define EMU_MATH_GENERAL_MATH_H_INC_

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
}

#endif
