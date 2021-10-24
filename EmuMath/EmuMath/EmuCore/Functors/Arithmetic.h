#ifndef EMU_CORE_ARITHMETIC_FUNCTORS_H_INC_
#define EMU_CORE_ARITHMETIC_FUNCTORS_H_INC_ 1

#include "../ArithmeticHelpers/CommonMath.h"
#include "../TMPHelpers/TypeComparators.h"
#include <cstddef>
#include <functional>

namespace EmuCore
{
	/// <summary>
	/// <para> Functor which may be used to perform linear interpolations. </para>
	/// <para> Takes 3 type arguments, however only one or two may be passed. B_ will be the same type as A_ if omitted. T_ will be float if omitted. </para>
	/// <para> Types should be considered for the equation A_ + ((B_ - A_) * T_). </para>
	/// <para> do_lerp&lt;void&gt;, do_lerp&lt;void, void&gt;, and do_lerp&lt;void, void, void&gt; are reserved for a generic specialisation of do_lerp. </para>
	/// </summary>
	/// <typeparam name="A_">Type used to represent a in the equation a + ((b - a) * t).</typeparam>
	/// <typeparam name="B_">Type used to represent b in the equation a + ((b - a) * t).</typeparam>
	/// <typeparam name="T_">Type used to represent t in the equation a + ((b - a) * t).</typeparam>
	template<class A_, class B_ = A_, class T_ = float>
	struct do_lerp
	{
		constexpr do_lerp()
		{
		}
		[[nodiscard]] constexpr inline auto operator()(const A_& a_, const B_& b_, const T_& t_) const
		{
			if constexpr
			(
				EmuCore::TMPHelpers::is_any_floating_point_v<A_, B_, T_> &&
				!EmuCore::TMPHelpers::are_all_comparisons_true<std::is_same, A_, B_, T_>::value
			)
			{
				using floating_point = typename EmuCore::TMPHelpers::largest_floating_point<A_, B_, T_>::type;
				floating_point a_cast_ = static_cast<floating_point>(a_);
				return a_cast_ + ((static_cast<floating_point>(b_) - a_cast_) * static_cast<floating_point>(t_));
			}
			else
			{
				return (a_ + ((b_ - a_) * t_));
			}
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
		[[nodiscard]] constexpr inline Out_ operator()(const T_& val_) const
		{
			return EmuCore::SqrtConstexpr<Out_, T_>(val_);
		}
	};
	template<>
	struct do_sqrt_constexpr<void>
	{
		constexpr do_sqrt_constexpr()
		{
		}
		template<typename T_>
		[[nodiscard]] constexpr inline auto operator()(const T_& val_) const
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
		[[nodiscard]] inline floating_point_ operator()(const T_& val_) const
		{
			if constexpr (std::is_same_v<T_, floating_point_>)
			{
				return DoMatchingStandardSqrt<T_>(val_);
			}
			else
			{
				return DoMatchingStandardSqrt<floating_point_>(static_cast<floating_point_>(val_));
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
		[[nodiscard]] inline auto operator()(const T_& val_) const
		{
			return do_sqrt<T_>()(val_);
		}
	};

	/// <summary> 
	/// <para> Constexpr flooring functor. </para>
	/// <para> Unless specialised, the valid range for values this can take is min(int64_t):max(uint64_t). </para>
	/// </summary>
	template<typename T_>
	struct do_floor_constexpr
	{
		constexpr do_floor_constexpr()
		{
		}
		[[nodiscard]] constexpr inline T_ operator()(const T_& val_) const
		{
			if constexpr (std::is_integral_v<T_>)
			{
				return val_;
			}
			else
			{
				if (val_ < T_(0))
				{
					// If trunc is different, we will have done a ceil since negative trunc == negative ceil
					// --- As such, we need to subtract 1 from the truncated value if we do need to perform a round
					T_ truncated_ = static_cast<T_>(static_cast<std::int64_t>(val_));
					return (truncated_ == val_) ? val_ : (truncated_ - T_(1));
				}
				else
				{
					// Can take advantage of a higher range from an unsigned int if we know we're positive
					// --- Additionally, positive trunc == positive floor
					return static_cast<T_>(static_cast<std::uint64_t>(val_));
				}
			}
		}
	};
	template<>
	struct do_floor_constexpr<void>
	{
		constexpr do_floor_constexpr()
		{
		}
		template<typename T_>
		[[nodiscard]] constexpr inline T_ operator()(const T_& val_) const
		{
			return do_floor_constexpr<T_>()(val_);
		}
	};

	/// <summary> 
	/// <para> Constexpr ceiling functor. </para>
	/// <para> Unless specialised, the valid range for values this can take is min(int64_t):max(uint64_t). </para>
	/// </summary>
	template<typename T_>
	struct do_ceil_constexpr
	{
		constexpr do_ceil_constexpr()
		{
		}
		[[nodiscard]] constexpr inline T_ operator()(const T_& val_) const
		{
			if constexpr (std::is_integral_v<T_>)
			{
				return val_;
			}
			else
			{
				if (val_ < T_(0))
				{
					// Negative trunc == negative ceil
					return static_cast<T_>(static_cast<std::int64_t>(val_));
				}
				else
				{
					// When truncated, a positive value is equal to its floored value
					// --- As such, when a truncation indicates a round should occur, we need to add 1 to the truncated value when positive
					T_ truncated_ = static_cast<T_>(static_cast<std::uint64_t>(val_));
					return (truncated_ == val_) ? val_ : (truncated_ + T_(1));
				}
			}
		}
	};
	template<>
	struct do_ceil_constexpr<void>
	{
		constexpr do_ceil_constexpr()
		{
		}
		template<typename T_>
		[[nodiscard]] constexpr inline T_ operator()(const T_& val_) const
		{
			return do_ceil_constexpr<T_>()(val_);
		}
	};

	/// <summary> 
	/// <para> Constexpr flooring functor. </para>
	/// <para> Unless specialised, the valid range for values this can take is min(int64_t):max(int64_t). </para>
	/// </summary>
	template<typename T_>
	struct do_trunc_constexpr
	{
		constexpr do_trunc_constexpr()
		{
		}
		[[nodiscard]] constexpr inline T_ operator()(const T_& val_) const
		{
			if constexpr (std::is_integral_v<T_>)
			{
				return val_;
			}
			else
			{
				return static_cast<T_>(static_cast<std::int64_t>(val_));
			}
		}
	};
	template<>
	struct do_trunc_constexpr<void>
	{
		constexpr do_trunc_constexpr()
		{
		}
		template<typename T_>
		[[nodiscard]] constexpr inline T_ operator()(const T_& val_) const
		{
			return do_trunc_constexpr<T_>()(val_);
		}
	};

	template<typename T_>
	struct do_floor
	{
		constexpr do_floor()
		{
		}
		[[nodiscard]] constexpr inline T_ operator()(const T_& val_) const
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
		[[nodiscard]] constexpr inline auto operator()(const T_& val_) const
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
		[[nodiscard]] constexpr inline T_ operator()(const T_& val_) const
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
		[[nodiscard]] constexpr inline auto operator()(const T_& val_) const
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
		[[nodiscard]] constexpr inline T_ operator()(const T_& val_) const
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
		[[nodiscard]] constexpr inline auto operator()(const T_& val_) const
		{
			return do_trunc<T_>()(val_);
		}
	};

	template<typename Lhs_, typename Rhs_ = Lhs_>
	struct do_add
	{
	private:
		const std::plus<void> adder_;

	public:
		constexpr do_add() : adder_()
		{
		}
		[[nodiscard]] constexpr inline auto operator()(const Lhs_& lhs_, const Rhs_& rhs_) const
		{
			return adder_(lhs_, rhs_);
		}
	};
	template<>
	struct do_add<void, void>
	{
	public:
		constexpr do_add()
		{
		}
		template<typename Lhs_, typename Rhs_>
		[[nodiscard]] constexpr inline auto operator()(const Lhs_& lhs_, const Rhs_& rhs_) const
		{
			return do_add<Lhs_, Rhs_>()(lhs_, rhs_);
		}
	};

	template<typename Lhs_, typename Rhs_ = Lhs_>
	struct do_subtract
	{
	private:
		const std::minus<void> subtractor_;

	public:
		constexpr do_subtract() : subtractor_()
		{
		}
		[[nodiscard]] constexpr inline auto operator()(const Lhs_& lhs_, const Rhs_& rhs_) const
		{
			return subtractor_(lhs_, rhs_);
		}
	};
	template<>
	struct do_subtract<void, void>
	{
	public:
		constexpr do_subtract()
		{
		}
		template<typename Lhs_, typename Rhs_>
		[[nodiscard]] constexpr inline auto operator()(const Lhs_& lhs_, const Rhs_& rhs_) const
		{
			return do_subtract<Lhs_, Rhs_>()(lhs_, rhs_);
		}
	};

	template<typename Lhs_, typename Rhs_ = Lhs_>
	struct do_multiply
	{
	private:
		const std::multiplies<void> multiplier_;

	public:
		constexpr do_multiply() : multiplier_()
		{
		}
		[[nodiscard]] constexpr inline auto operator()(const Lhs_& lhs_, const Rhs_& rhs_) const
		{
			return multiplier_(lhs_, rhs_);
		}
	};
	template<>
	struct do_multiply<void, void>
	{
	public:
		constexpr do_multiply()
		{
		}
		template<typename Lhs_, typename Rhs_>
		[[nodiscard]] constexpr inline auto operator()(const Lhs_& lhs_, const Rhs_& rhs_) const
		{
			return do_multiply<Lhs_, Rhs_>()(lhs_, rhs_);
		}
	};

	template<typename Lhs_, typename Rhs_ = Lhs_>
	struct do_divide
	{
	private:
		const std::divides<void> divider_;

	public:
		constexpr do_divide() : divider_()
		{
		}
		[[nodiscard]] constexpr inline auto operator()(const Lhs_& lhs_, const Rhs_& rhs_) const
		{
			return divider_(lhs_, rhs_);
		}
	};
	template<>
	struct do_divide<void, void>
	{
	public:
		constexpr do_divide()
		{
		}
		template<typename Lhs_, typename Rhs_>
		[[nodiscard]] constexpr inline auto operator()(const Lhs_& lhs_, const Rhs_& rhs_) const
		{
			return do_divide<Lhs_, Rhs_>()(lhs_, rhs_);
		}
	};

	template<typename T_>
	struct do_negate
	{
	private:
		const std::negate<void> negator_;

	public:
		constexpr do_negate() : negator_()
		{
		}
		[[nodiscard]] constexpr inline auto operator()(const T_& val_) const
		{
			return negator_(val_);
		}
	};
	template<>
	struct do_negate<void>
	{
	public:
		constexpr do_negate()
		{
		}
		template<typename T_>
		[[nodiscard]] constexpr inline auto operator()(const T_& val_) const
		{
			return do_negate<T_>()(val_);
		}
	};

	template<typename T_>
	struct do_cos
	{
		using out_t = typename EmuCore::TMPHelpers::first_floating_point<T_, float>::type;
		constexpr do_cos()
		{
		}
		[[nodiscard]] constexpr inline out_t operator()(const T_& t_) const
		{
			return EmuCore::DoMatchingCos<out_t, T_>(t_);
		}
	};
	template<>
	struct do_cos<void>
	{
		constexpr do_cos()
		{
		}
		template<typename T_>
		[[nodiscard]] constexpr inline auto operator()(const T_& t_) const
		{
			return do_cos<T_>()(t_);
		}
	};

	template<typename T_>
	struct do_acos
	{
		using out_t = typename EmuCore::TMPHelpers::first_floating_point<T_, float>::type;
		constexpr do_acos()
		{
		}
		[[nodiscard]] constexpr inline out_t operator()(const T_& t_) const
		{
			return EmuCore::DoMatchingAcos<out_t, T_>(t_);
		}
	};
	template<>
	struct do_acos<void>
	{
		constexpr do_acos()
		{
		}
		template<typename T_>
		[[nodiscard]] constexpr inline auto operator()(const T_& t_) const
		{
			return do_acos<T_>()(t_);
		}
	};

	template<typename T_>
	struct do_sin
	{
		using out_t = typename EmuCore::TMPHelpers::first_floating_point<T_, float>::type;
		constexpr do_sin()
		{
		}
		[[nodiscard]] constexpr inline out_t operator()(const T_& t_) const
		{
			return EmuCore::DoMatchingSin<out_t, T_>(t_);
		}
	};
	template<>
	struct do_sin<void>
	{
		constexpr do_sin()
		{
		}
		template<typename T_>
		[[nodiscard]] constexpr inline auto operator()(const T_& t_) const
		{
			return do_sin<T_>()(t_);
		}
	};

	template<typename T_>
	struct do_asin
	{
		using out_t = typename EmuCore::TMPHelpers::first_floating_point<T_, float>::type;
		constexpr do_asin()
		{
		}
		[[nodiscard]] constexpr inline out_t operator()(const T_& t_) const
		{
			return EmuCore::DoMatchingAsin<out_t, T_>(t_);
		}
	};
	template<>
	struct do_asin<void>
	{
		constexpr do_asin()
		{
		}
		template<typename T_>
		[[nodiscard]] constexpr inline auto operator()(const T_& t_) const
		{
			return do_asin<T_>()(t_);
		}
	};

	template<typename T_>
	struct do_tan
	{
		using out_t = typename EmuCore::TMPHelpers::first_floating_point<T_, float>::type;
		constexpr do_tan()
		{
		}
		[[nodiscard]] constexpr inline out_t operator()(const T_& t_) const
		{
			return EmuCore::DoMatchingTan<out_t, T_>(t_);
		}
	};
	template<>
	struct do_tan<void>
	{
		constexpr do_tan()
		{
		}
		template<typename T_>
		[[nodiscard]] constexpr inline auto operator()(const T_& t_) const
		{
			return do_tan<T_>()(t_);
		}
	};

	template<typename T_>
	struct do_atan
	{
		using out_t = typename EmuCore::TMPHelpers::first_floating_point<T_, float>::type;
		constexpr do_atan()
		{
		}
		[[nodiscard]] constexpr inline out_t operator()(const T_& t_) const
		{
			return EmuCore::DoMatchingAtan<out_t, T_>(t_);
		}
	};
	template<>
	struct do_atan<void>
	{
		constexpr do_atan()
		{
		}
		template<typename T_>
		[[nodiscard]] constexpr inline auto operator()(const T_& t_) const
		{
			return do_atan<T_>()(t_);
		}
	};

	template<typename T_>
	struct do_degs_to_rads
	{
		constexpr do_degs_to_rads()
		{
		}
		[[nodiscard]] constexpr inline T_ operator()(const T_& val_) const
		{
			return EmuCore::Pi::DegsToRads<T_>(val_);
		}
	};
	template<>
	struct do_degs_to_rads<void>
	{
		constexpr do_degs_to_rads()
		{
		}
		template<typename T_>
		[[nodiscard]] constexpr inline T_ operator()(const T_& val_) const
		{
			return do_degs_to_rads<T_>()(val_);
		}
	};

	template<typename T_>
	struct do_rads_to_degs
	{
		constexpr do_rads_to_degs()
		{
		}
		[[nodiscard]] constexpr inline T_ operator()(const T_& val_) const
		{
			return EmuCore::Pi::RadsToDegs<T_>(val_);
		}
	};
	template<>
	struct do_rads_to_degs<void>
	{
		constexpr do_rads_to_degs()
		{
		}
		template<typename T_>
		[[nodiscard]] constexpr inline T_ operator()(const T_& val_) const
		{
			return do_rads_to_degs<T_>()(val_);
		}
	};

	template<typename Lhs_, typename Rhs_>
	struct do_mod
	{
	private:
		std::modulus<void> modder_;

	public:
		constexpr do_mod() : modder_()
		{
		}
		constexpr inline auto operator()(const Lhs_& lhs_, const Rhs_& rhs_) const
		{
			return modder_(lhs_, rhs_);
		}
	};
	template<>
	struct do_mod<void, void>
	{
		constexpr do_mod()
		{
		}
		template<typename Lhs_, typename Rhs_>
		constexpr inline auto operator()(const Lhs_& lhs_, const Rhs_& rhs_) const
		{
			return do_mod<Lhs_, Rhs_>()(lhs_, rhs_);
		}
	};
	template<typename Rhs_>
	struct do_mod<float, Rhs_>
	{
		constexpr do_mod()
		{
		}
		constexpr inline auto operator()(const float& lhs_, const Rhs_& rhs_) const
		{
			return FmodConstexpr<float, Rhs_>(lhs_, rhs_);
		}
	};
	template<typename Rhs_>
	struct do_mod<double, Rhs_>
	{
		constexpr do_mod()
		{
		}
		constexpr inline auto operator()(const double& lhs_, const Rhs_& rhs_) const
		{
			return FmodConstexpr<double, Rhs_>(lhs_, rhs_);
		}
	};
	template<typename Rhs_>
	struct do_mod<long double, Rhs_>
	{
		constexpr do_mod()
		{
		}
		constexpr inline auto operator()(const long double& lhs_, const Rhs_& rhs_) const
		{
			return FmodConstexpr<long double, Rhs_>(lhs_, rhs_);
		}
	};

	/// <summary>
	/// <para> Functor to calculate cosine (radian units) at compile time using Taylor Series, using the specified number of iterations of said series to do so. </para>
	/// <para>
	///		DoMod_ is true by default, and will only have an effect on values greater than 6.28319. 
	///		In cases where input ranges are unknown, it is recommended to keep it as true.
	///		In cases where you know inputs will not exceed the provided range, it will do nothing and thus setting the argument to false will avoid a useless fmod operation.
	/// </para>
	/// </summary>
	/// <typeparam name="T_"></typeparam>
	template<typename T_, std::size_t NumIterations_ = 3, bool DoMod_ = true>
	struct do_cos_constexpr
	{
	public:
		static_assert(NumIterations_ != 0, "Attempted to create an EmuCore::do_cos_constexpr instance with 0 iterations. At least 1 iteration is required.");

		using out_t = std::conditional_t
		<
			std::is_arithmetic_v<T_>,
			EmuCore::TMPHelpers::first_floating_point_t<T_, float>,
			T_
		>;
		static constexpr out_t full_circle = EmuCore::Pi::DegsToRads_v<out_t, int, 360>;

		constexpr do_cos_constexpr() : add_(), sub_(), mul_(), div_(), mod_()
		{
		}
		constexpr inline out_t operator()(T_ val_) const
		{
			if constexpr (DoMod_)
			{
				out_t rounded_ = static_cast<out_t>(mod_(static_cast<out_t>(val_), full_circle));
				return _calculate_taylor_series<NumIterations_>(rounded_);
			}
			else
			{
				if constexpr (std::is_same_v<T_, out_t>)
				{
					return _calculate_taylor_series<NumIterations_>(val_);
				}
				else
				{
					out_t val_as_out_t_ = static_cast<out_t>(val_);
					return _calculate_taylor_series<NumIterations_>(val_as_out_t_);
				}
			}
		}
	private:
		using Add_ = EmuCore::do_add<out_t, out_t>;
		using Sub_ = EmuCore::do_subtract<out_t, out_t>;
		using Mul_ = EmuCore::do_multiply<out_t, out_t>;
		using Div_ = EmuCore::do_divide<out_t, out_t>;
		using Mod_ = EmuCore::do_mod<out_t, out_t>;
		Add_ add_;
		Sub_ sub_;
		Mul_ mul_;
		Div_ div_;
		Mod_ mod_;

		template<std::size_t NumIterations_>
		constexpr inline out_t _calculate_taylor_series(const out_t& in_) const
		{
			out_t out_ = out_t(1);
			out_t pow_ = out_t(1);
			out_t in_sqr_ = mul_(in_, in_);
			_calculate_taylor_series<0, NumIterations_, 2>(in_sqr_, out_, pow_);
			return out_;
		}
		template<std::size_t Iteration_, std::size_t End_, std::size_t PowExponent_>
		constexpr inline void _calculate_taylor_series(const out_t& in_sqr_, out_t& out_, out_t& pow_) const
		{
			if constexpr (Iteration_ < End_)
			{
				pow_ = mul_(in_sqr_, pow_);
				const out_t derivative_ = div_(pow_, EmuCore::factorial_v<PowExponent_, out_t>);
				if constexpr (Iteration_ & 1)
				{
					out_ = add_(out_, derivative_);
				}
				else
				{
					out_ = sub_(out_, derivative_);
				}
				_calculate_taylor_series<Iteration_ + 1, End_, PowExponent_ + 2>(in_sqr_, out_, pow_);
			}
		}
	};
	template<std::size_t NumIterations_, bool DoMod_>
	struct do_cos_constexpr<void, NumIterations_, DoMod_>
	{
		constexpr do_cos_constexpr()
		{
		}
		template<bool DoMod_ = true, typename T_>
		constexpr inline auto operator()(const T_& val_) const
		{
			return do_cos_constexpr<T_, NumIterations_, DoMod_>()(val_);
		}
	};

	template<typename T_, std::size_t NumIterations_ = 3, bool DoMod_ = true>
	struct do_sin_constexpr
	{
		static_assert(NumIterations_ != 0, "Attempted to create an EmuCore::do_sin_constexpr instance with 0 iterations. At least 1 iteration is required.");

		using out_t = std::conditional_t
		<
			std::is_arithmetic_v<T_>,
			EmuCore::TMPHelpers::first_floating_point_t<T_, float>,
			T_
		>;
		static constexpr out_t full_circle = EmuCore::Pi::DegsToRads_v<out_t, int, 360>;

		constexpr do_sin_constexpr() : add_(), sub_(), mul_(), div_(), mod_()
		{
		}
		constexpr inline out_t operator()(T_ val_) const
		{
			if constexpr (DoMod_)
			{
				out_t rounded_ = mod_(static_cast<out_t>(val_), full_circle);
				return _calculate_taylor_series<NumIterations_>(rounded_);
			}
			else
			{
				if constexpr (std::is_same_v<T_, out_t>)
				{
					return _calculate_taylor_series<NumIterations_>(val_);
				}
				else
				{
					out_t val_as_out_t_ = static_cast<out_t>(val_);
					return _calculate_taylor_series<NumIterations_>(val_as_out_t_);
				}
			}
		}

	private:
		using Add_ = EmuCore::do_add<out_t, out_t>;
		using Sub_ = EmuCore::do_subtract<out_t, out_t>;
		using Mul_ = EmuCore::do_multiply<out_t, out_t>;
		using Div_ = EmuCore::do_divide<out_t, out_t>;
		using Mod_ = EmuCore::do_mod<out_t, out_t>;
		Add_ add_;
		Sub_ sub_;
		Mul_ mul_;
		Div_ div_;
		Mod_ mod_;

		template<std::size_t NumIterations_>
		constexpr inline out_t _calculate_taylor_series(const out_t& in_) const
		{
			out_t out_ = in_;
			out_t pow_ = in_;
			out_t in_sqr_ = mul_(in_, in_);
			_calculate_taylor_series<0, NumIterations_, 3>(in_sqr_, out_, pow_);
			return out_;
		}
		template<std::size_t Iteration_, std::size_t End_, std::size_t PowExponent_>
		constexpr inline void _calculate_taylor_series(const out_t& in_sqr_, out_t& out_, out_t& pow_) const
		{
			if constexpr (Iteration_ < End_)
			{
				pow_ = mul_(in_sqr_, pow_);
				const out_t derivative_ = div_(pow_, EmuCore::factorial_v<PowExponent_, out_t>);
				if constexpr (Iteration_ & 1)
				{
					out_ = add_(out_, derivative_);
				}
				else
				{
					out_ = sub_(out_, derivative_);
				}
				_calculate_taylor_series<Iteration_ + 1, End_, PowExponent_ + 2>(in_sqr_, out_, pow_);
			}
		}
	};
	template<std::size_t NumIterations_, bool DoMod_>
	struct do_sin_constexpr<void, NumIterations_, DoMod_>
	{
		constexpr do_sin_constexpr()
		{
		}
		template<typename T_>
		constexpr inline auto operator()(const T_& val_) const
		{
			return do_sin_constexpr<T_, NumIterations_, DoMod_>()(val_);
		}
	};

	template<typename T_, std::size_t NumIterations_ = 3, bool DoMod_ = true>
	struct do_tan_constexpr
	{
	public:
		static_assert(NumIterations_ != 0, "Attempted to create an EmuCore::do_tan_constexpr instance with 0 iterations. At least 1 iteration is required.");

		using out_t = std::conditional_t
		<
			std::is_arithmetic_v<T_>,
			EmuCore::TMPHelpers::first_floating_point_t<T_, float>,
			T_
		>;
		static constexpr out_t full_circle = EmuCore::Pi::DegsToRads_v<out_t, int, 360>;

		constexpr do_tan_constexpr() : cos_(), sin_(), div_(), mod_()
		{
		}
		constexpr inline out_t operator()(const T_& val_) const
		{
			if constexpr (DoMod_)
			{
				out_t rounded_ = mod_(static_cast<out_t>(val_), full_circle);
				cos_t cosine_ = cos_(val_);
				sin_t sine_ = sin_(val_);
				return static_cast<out_t>(div_(sine_, cosine_));
			}
			else
			{
				cos_t cosine_ = cos_(val_);
				sin_t sine_ = sin_(val_);
				return static_cast<out_t>(div_(sine_, cosine_));
			}
		}

	private:
		using cos_sin_passed_type = std::conditional_t<DoMod_, out_t, T_>;
		using cos_calc = do_cos_constexpr<cos_sin_passed_type, NumIterations_, false>;
		using sin_calc = do_sin_constexpr<cos_sin_passed_type, NumIterations_, false>;
		using cos_t = typename cos_calc::out_t;
		using sin_t = typename sin_calc::out_t;
		using divider = do_divide<sin_t, cos_t>;
		using modder = do_mod<out_t, out_t>;

		cos_calc cos_;
		sin_calc sin_;
		divider div_;
		modder mod_;

	};
	template<std::size_t NumIterations_, bool DoMod_>
	struct do_tan_constexpr<void, NumIterations_, DoMod_>
	{
		constexpr do_tan_constexpr()
		{
		}
		template<typename T_>
		constexpr inline auto operator()(const T_& val_) const
		{
			return do_tan_constexpr<T_, NumIterations_, DoMod_>()(val_);
		}
	};

	template<typename T_>
	struct do_abs
	{
		constexpr do_abs()
		{
		}

		constexpr inline T_ operator()(const T_& val_) const
		{
			return EmuCore::AbsConstexpr<T_>(val_);
		}
	};

	/// <summary> 
	/// <para> Functor for wrapping values that are assumed to lie in a normalised range 0:1, where -0.1 is wrapped to 0.9, and 1.1 wrapped to 1.1. </para>
	/// <para> Default, non-specialised forms of this functor are presented in a branchless manner. </para>
	/// <para> If WrapToOne_ is TRUE: non-zero whole numbers will be wrapped to 1. </para>
	/// <para> If WrapToOne_ is FALSE: non-zero whole numbers will be wrapped to 0. </para>
	/// </summary>
	template<typename T_, bool WrapToOne_>
	struct do_normalised_wrap
	{
		constexpr do_normalised_wrap()
		{
		}

		[[nodiscard]] constexpr inline T_ operator()(T_ val_) const
		{
			constexpr T_ zero_ = T_(0);
			if constexpr (std::is_integral_v<T_>)
			{
				// Any non-zero integer will wrap to 1, so we just return whatever any non-zero would wrap to in that case
				if constexpr (WrapToOne_)
				{
					return static_cast<T_>(val_ != zero_);
				}
				else
				{
					return zero_;
				}
			}
			else
			{
				// More complex with non-integral types as we need to invert magnitude and direction of the fractions
				// --- E.g. -0.8 would wrap around to +0.2, so we need to perform that transformation
				constexpr T_ one_ = T_(1);
				if constexpr (!WrapToOne_)
				{
					// Subtraction of a trunc brings us into the non-inclusive range -1:1
					val_ = val_ - EmuCore::do_trunc_constexpr<T_>()(val_);

					// Value will be wrapped if positive, but we need to invert the magnitude if negative
					// --- This can be done by adding 1 (i.e. -0.9 -> 0.1)
					return val_ + (one_ * (val_ < zero_));
				}
				else
				{
					// Same as above, but addition of 1 is done if result is negative OR 0
					// --- This OR 0 only applies to the wrapped variant if it did not start at 0
					bool started_not_zero_ = val_ != zero_;
					val_ = val_ - EmuCore::do_trunc_constexpr<T_>()(val_);
					return val_ + (one_ * ((val_ <= zero_) && started_not_zero_));
				}
			}
		}
	};
}

#endif
