#ifndef EMU_CORE_ARITHMETIC_FUNCTORS_H_INC_
#define EMU_CORE_ARITHMETIC_FUNCTORS_H_INC_

#include "../ArithmeticHelpers/CommonMath.h"
#include <cstddef>
#include <functional>

namespace EmuCore
{
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
		[[nodiscard]] inline auto operator()(const T_& val_) const
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

	template<typename T_, typename Shifts_>
	struct do_left_shift
	{
		constexpr do_left_shift()
		{
		}
		constexpr inline T_ operator()(const T_& val_, const Shifts_& num_shifts_) const
		{
			if constexpr (std::is_arithmetic_v<T_>)
			{
				return val_ << static_cast<std::size_t>(num_shifts_);
			}
			else
			{
				return val_ << num_shifts_;
			}
		}
	};
	template<>
	struct do_left_shift<void, void>
	{
		constexpr do_left_shift()
		{
		}
		template<typename T_, typename Shifts_>
		constexpr inline T_ operator()(const T_& val_, const Shifts_& num_shifts_) const
		{
			return do_left_shift<T_>()(val_, num_shifts_);
		}
	};

	template<typename T_, typename Shifts_>
	struct do_right_shift
	{
		constexpr do_right_shift()
		{
		}
		constexpr inline T_ operator()(const T_& val_, const Shifts_& num_shifts_) const
		{
			if constexpr (std::is_arithmetic_v<T_>)
			{
				return val_ >> static_cast<std::size_t>(num_shifts_);
			}
			else
			{
				return val_ >> num_shifts_;
			}
		}
	};
	template<>
	struct do_right_shift<void, void>
	{
		constexpr do_right_shift()
		{
		}
		template<typename T_, typename Shifts_>
		constexpr inline T_ operator()(const T_& val_, const Shifts_& num_shifts_) const
		{
			return do_right_shift<T_, Shifts_>()(val_, num_shifts_);
		}
	};

	template<typename Lhs_, typename Rhs_ = Lhs_>
	struct do_add
	{
	private:
		const std::plus<void> adder_;

	public:
		constexpr do_add()
		{
		}
		constexpr inline auto operator()(const Lhs_& lhs_, const Rhs_& rhs_) const
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
		constexpr inline auto operator()(const Lhs_& lhs_, const Rhs_& rhs_) const
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
		constexpr do_subtract()
		{
		}
		constexpr inline auto operator()(const Lhs_& lhs_, const Rhs_& rhs_) const
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
		constexpr inline auto operator()(const Lhs_& lhs_, const Rhs_& rhs_) const
		{
			return do_subtract<Lhs_, Rhs_>()(lhs_, rhs_);
		}
	};

	template<typename Lhs_, typename Rhs_ = Lhs_>
	struct do_multiply
	{
	private:
		const std::multiplies<void> mutliplier_;

	public:
		constexpr do_multiply()
		{
		}
		constexpr inline auto operator()(const Lhs_& lhs_, const Rhs_& rhs_) const
		{
			return mutliplier_(lhs_, rhs_);
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
		constexpr inline auto operator()(const Lhs_& lhs_, const Rhs_& rhs_) const
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
		constexpr do_divide()
		{
		}
		constexpr inline auto operator()(const Lhs_& lhs_, const Rhs_& rhs_) const
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
		constexpr inline auto operator()(const Lhs_& lhs_, const Rhs_& rhs_) const
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
		constexpr do_negate()
		{
		}
		constexpr inline auto operator()(const T_& val_) const
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
		constexpr inline auto operator()(const T_& val_) const
		{
			return do_negate<T_>()(val_);
		}
	};
}

#endif