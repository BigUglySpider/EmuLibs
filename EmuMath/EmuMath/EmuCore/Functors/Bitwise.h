#ifndef EMU_CORE_BITWISE_FUNCTORS_H_INC_
#define EMU_CORE_BITWISE_FUNCTORS_H_INC_ 1

#include "../TMPHelpers/TypeConvertors.h"
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
		constexpr do_bitwise_and() : ander_()
		{
		}
		[[nodiscard]] constexpr inline Lhs_ operator()(const Lhs_& lhs_, const Rhs_& rhs_) const
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
		[[nodiscard]] constexpr inline Lhs_ operator()(const Lhs_& lhs_, const Rhs_& rhs_) const
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
		constexpr do_bitwise_or() : orer_()
		{
		}
		[[nodiscard]] constexpr inline Lhs_ operator()(const Lhs_& lhs_, const Rhs_& rhs_) const
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
		[[nodiscard]] constexpr inline Lhs_ operator()(const Lhs_& lhs_, const Rhs_& rhs_) const
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
		constexpr do_bitwise_xor() : xorer_()
		{
		}
		[[nodiscard]] constexpr inline Lhs_ operator()(const Lhs_& lhs_, const Rhs_& rhs_) const
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
		[[nodiscard]] constexpr inline Lhs_ operator()(const Lhs_& lhs_, const Rhs_& rhs_) const
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
		constexpr do_bitwise_not() : notter_()
		{
		}
		[[nodiscard]] constexpr inline T_ operator()(const T_& val_) const
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
		[[nodiscard]] constexpr inline T_ operator()(const T_& val_) const
		{
			return do_bitwise_not<T_>()(val_);
		}
	};
	template<>
	struct do_bitwise_not<float>
	{
		constexpr do_bitwise_not()
		{
		}
		[[nodiscard]] inline float operator()(const float val_) const
		{
			using uint_type = EmuCore::TMP::uint_of_size_t<sizeof(float)>;
			if constexpr (!std::is_same_v<uint_type, std::false_type>)
			{
				const uint_type as_uint_ = ~(*reinterpret_cast<const uint_type*>(&val_));
				return *reinterpret_cast<const float*>(&as_uint_);
			}
			else
			{
				static_assert(!std::is_same_v<uint_type, std::false_type>, "Attempted to perform bitwise NOT on a float, but there is no valid uint reinterpretation for a float on this system.");
			}
		}
	};
	template<>
	struct do_bitwise_not<double>
	{
		constexpr do_bitwise_not()
		{
		}
		[[nodiscard]] inline double operator()(const double val_) const
		{
			using uint_type = EmuCore::TMP::uint_of_size_t<sizeof(double)>;
			if constexpr (!std::is_same_v<uint_type, std::false_type>)
			{
				const uint_type as_uint_ = ~(*reinterpret_cast<const uint_type*>(&val_));
				return *reinterpret_cast<const double*>(&as_uint_);
			}
			else
			{
				static_assert(!std::is_same_v<uint_type, std::false_type>, "Attempted to perform bitwise NOT on a double, but there is no valid uint reinterpretation for a float on this system.");
			}
		}
	};
	template<>
	struct do_bitwise_not<long double>
	{
		constexpr do_bitwise_not()
		{
		}
		[[nodiscard]] inline long double operator()(const long double val_) const
		{
			using uint_type = EmuCore::TMP::uint_of_size_t<sizeof(long double)>;
			if constexpr (!std::is_same_v<uint_type, std::false_type>)
			{
				const uint_type as_uint_ = ~(*reinterpret_cast<const uint_type*>(&val_));
				return *reinterpret_cast<const long double*>(&as_uint_);
			}
			else
			{
				static_assert(!std::is_same_v<uint_type, std::false_type>, "Attempted to perform bitwise NOT on a long double, but there is no valid uint reinterpretation for a float on this system.");
			}
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
	template<typename Shifts_>
	struct do_left_shift<float, Shifts_>
	{
		constexpr do_left_shift()
		{
		}
		inline float operator()(const float val_, const Shifts_& num_shifts_) const
		{
			using uint_type = EmuCore::TMP::uint_of_size_t<sizeof(float)>;
			if constexpr (!std::is_same_v<uint_type, std::false_type>)
			{
				const uint_type as_uint_ = (*reinterpret_cast<const uint_type*>(&val_)) << static_cast<std::size_t>(num_shifts_);
				return *reinterpret_cast<const float*>(&as_uint_);
			}
			else
			{
				static_assert(!std::is_same_v<uint_type, std::false_type>, "Attempted to perform bitwise shift left on a float, but there is no valid uint reinterpretation for a float on this system.");
			}
		}
	};
	template<typename Shifts_>
	struct do_left_shift<double, Shifts_>
	{
		constexpr do_left_shift()
		{
		}
		inline double operator()(const double val_, const Shifts_& num_shifts_) const
		{
			using uint_type = EmuCore::TMP::uint_of_size_t<sizeof(double)>;
			if constexpr (!std::is_same_v<uint_type, std::false_type>)
			{
				const uint_type as_uint_ = (*reinterpret_cast<const uint_type*>(&val_)) << static_cast<std::size_t>(num_shifts_);
				return *reinterpret_cast<const double*>(&as_uint_);
			}
			else
			{
				static_assert(!std::is_same_v<uint_type, std::false_type>, "Attempted to perform bitwise shift left on a double, but there is no valid uint reinterpretation for a float on this system.");
			}
		}
	};
	template<typename Shifts_>
	struct do_left_shift<long double, Shifts_>
	{
		constexpr do_left_shift()
		{
		}
		inline double operator()(const long double val_, const Shifts_& num_shifts_) const
		{
			using uint_type = EmuCore::TMP::uint_of_size_t<sizeof(long double)>;
			if constexpr (!std::is_same_v<uint_type, std::false_type>)
			{
				const uint_type as_uint_ = (*reinterpret_cast<const uint_type*>(&val_)) << static_cast<std::size_t>(num_shifts_);
				return *reinterpret_cast<const long double*>(&as_uint_);
			}
			else
			{
				static_assert(!std::is_same_v<uint_type, std::false_type>, "Attempted to perform bitwise shift left on a long double, but there is no valid uint reinterpretation for a float on this system.");
			}
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
	template<typename Shifts_>
	struct do_right_shift<float, Shifts_>
	{
		constexpr do_right_shift()
		{
		}
		inline float operator()(const float val_, const Shifts_& num_shifts_) const
		{
			using uint_type = EmuCore::TMP::uint_of_size_t<sizeof(float)>;
			if constexpr (!std::is_same_v<uint_type, std::false_type>)
			{
				const uint_type as_uint_ = (*reinterpret_cast<const uint_type*>(&val_)) >> static_cast<std::size_t>(num_shifts_);
				return *reinterpret_cast<const float*>(&as_uint_);
			}
			else
			{
				static_assert(!std::is_same_v<uint_type, std::false_type>, "Attempted to perform bitwise shift right on a float, but there is no valid uint reinterpretation for a float on this system.");
			}
		}
	};
	template<typename Shifts_>
	struct do_right_shift<double, Shifts_>
	{
		constexpr do_right_shift()
		{
		}
		inline double operator()(const double val_, const Shifts_& num_shifts_) const
		{
			using uint_type = EmuCore::TMP::uint_of_size_t<sizeof(double)>;
			if constexpr (!std::is_same_v<uint_type, std::false_type>)
			{
				const uint_type as_uint_ = (*reinterpret_cast<const uint_type*>(&val_)) >> static_cast<std::size_t>(num_shifts_);
				return *reinterpret_cast<const double*>(&as_uint_);
			}
			else
			{
				static_assert(!std::is_same_v<uint_type, std::false_type>, "Attempted to perform bitwise shift right on a double, but there is no valid uint reinterpretation for a float on this system.");
			}
		}
	};
	template<typename Shifts_>
	struct do_right_shift<long double, Shifts_>
	{
		constexpr do_right_shift()
		{
		}
		inline double operator()(const long double val_, const Shifts_& num_shifts_) const
		{
			using uint_type = EmuCore::TMP::uint_of_size_t<sizeof(long double)>;
			if constexpr (!std::is_same_v<uint_type, std::false_type>)
			{
				const uint_type as_uint_ = (*reinterpret_cast<const uint_type*>(&val_)) >> static_cast<std::size_t>(num_shifts_);
				return *reinterpret_cast<const long double*>(&as_uint_);
			}
			else
			{
				static_assert(!std::is_same_v<uint_type, std::false_type>, "Attempted to perform bitwise shift right on a long double, but there is no valid uint reinterpretation for a float on this system.");
			}
		}
	};
}

#endif
