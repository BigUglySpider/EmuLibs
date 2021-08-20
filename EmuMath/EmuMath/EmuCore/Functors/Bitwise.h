#ifndef EMU_CORE_BITWISE_FUNCTORS_H_INC_
#define EMU_CORE_BITWISE_FUNCTORS_H_INC_ 1

#include <cstddef>
#include <functional>

namespace EmuCore
{
	template<typename Lhs_, typename Rhs_ = Lhs_>
	struct do_bitwise_and
	{
	private:
		const std::bit_and<void> ander_;

	public:
		constexpr do_bitwise_and()
		{
		}
		[[nodiscard]] constexpr inline Lhs_ operator()(const Lhs_& lhs_, const Rhs_& rhs_)
		{
			return static_cast<Lhs_>(ander_(lhs_, rhs_));
		}
	};
	template<>
	struct do_bitwise_and<void, void>
	{
		constexpr do_bitwise_and()
		{
		}
		template<typename Lhs_, typename Rhs_>
		[[nodiscard]] constexpr inline Lhs_ operator()(const Lhs_& lhs_, const Rhs_& rhs_)
		{
			return do_bitwise_and<Lhs_, Rhs_>()(lhs_, rhs_);
		}
	};

	template<typename Lhs_, typename Rhs_ = Lhs_>
	struct do_bitwise_or
	{
	private:
		const std::bit_or<void> orer_;

	public:
		constexpr do_bitwise_or()
		{
		}
		[[nodiscard]] constexpr inline Lhs_ operator()(const Lhs_& lhs_, const Rhs_& rhs_)
		{
			return static_cast<Lhs_>(orer_(lhs_, rhs_));
		}
	};
	template<>
	struct do_bitwise_or<void, void>
	{
		constexpr do_bitwise_or()
		{
		}
		template<typename Lhs_, typename Rhs_>
		[[nodiscard]] constexpr inline Lhs_ operator()(const Lhs_& lhs_, const Rhs_& rhs_)
		{
			return do_bitwise_or<Lhs_, Rhs_>()(lhs_, rhs_);
		}
	};

	template<typename Lhs_, typename Rhs_ = Lhs_>
	struct do_bitwise_xor
	{
	private:
		const std::bit_xor<void> xorer_;

	public:
		constexpr do_bitwise_xor()
		{
		}
		[[nodiscard]] constexpr inline Lhs_ operator()(const Lhs_& lhs_, const Rhs_& rhs_)
		{
			return static_cast<Lhs_>(xorer_(lhs_, rhs_));
		}
	};
	template<>
	struct do_bitwise_xor<void, void>
	{
		constexpr do_bitwise_xor()
		{
		}
		template<typename Lhs_, typename Rhs_>
		[[nodiscard]] constexpr inline Lhs_ operator()(const Lhs_& lhs_, const Rhs_& rhs_)
		{
			return do_bitwise_xor<Lhs_, Rhs_>()(lhs_, rhs_);
		}
	};

	template<typename T_>
	struct do_bitwise_not
	{
	private:
		const std::bit_not<void> notter_;

	public:
		constexpr do_bitwise_not()
		{
		}
		[[nodiscard]] constexpr inline T_ operator()(const T_& val_)
		{
			return static_cast<T_>(notter_(val_));
		}
	};
	template<>
	struct do_bitwise_not<void>
	{
		constexpr do_bitwise_not()
		{
		}
		template<typename T_>
		[[nodiscard]] constexpr inline T_ operator()(const T_& val_)
		{
			return do_bitwise_not<T_>()(val_);
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
				if constexpr (std::is_integral_v<T_>)
				{
					return val_ << static_cast<std::size_t>(num_shifts_);
				}
				else
				{
					static_assert(false, "Attempted to left-shift an unspecialised non-integral arithmetic type via EmuCore::do_left_shift.");
				}
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
			return do_left_shift<T_, Shifts_>()(val_, num_shifts_);
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
				if constexpr (std::is_integral_v<T_>)
				{
					return val_ >> static_cast<std::size_t>(num_shifts_);
				}
				else
				{
					static_assert(false, "Attempted to right-shift an unspecialised non-integral arithmetic type via EmuCore::do_right_shift.");
				}
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
}

#endif
