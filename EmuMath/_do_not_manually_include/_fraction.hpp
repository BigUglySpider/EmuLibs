#ifndef EMU_MATH_FRACTION_IMPL_HPP_INC_
#define EMU_MATH_FRACTION_IMPL_HPP_INC_ 1

#include "../../EmuCore/CommonConcepts/Arithmetic.h"
#include "../../EmuCore/CommonConcepts/CommonRequirements.h"
#include "../../EmuCore/Functors/Arithmetic.h"
#include "../../EmuCore/Functors/Comparators.h"

#include <cmath>
#include <ostream>
#include <type_traits>

namespace EmuMath
{
	template<EmuConcepts::Integer T>
	class Fraction
	{
	public:
		using integer_type = T;
		using integer_value_type = typename std::remove_cvref<integer_type>::type;
		using default_floating_point_type = typename std::conditional
		<
			sizeof(integer_value_type) < sizeof(float),
			float,
			double
		>::type;
		static constexpr bool default_conversion_fraction_only = false;

	private:
		template<class FP_>
		[[nodiscard]] static constexpr decltype(auto) _floor(const FP_& value_) noexcept
		{
			return EmuCore::do_floor_constexpr<typename std::remove_cvref<FP_>::type>{}(value_);
		}

		template<class FP_>
		[[nodiscard]] static constexpr decltype(auto) _trunc(const FP_& value_) noexcept
		{
			return EmuCore::do_trunc_constexpr<typename std::remove_cvref<FP_>::type>{}(value_);
		}

		template<class FP_>
		[[nodiscard]] static constexpr decltype(auto) _round(const FP_& value_) noexcept
		{
			return _floor(value_ + FP_{ 0.5f });
		}

		[[nodiscard]] static constexpr auto _greatest_common_divisor(integer_value_type a, integer_value_type b) noexcept
		{
			return EmuCore::do_gcd<integer_value_type, integer_value_type>{}(a, b);
		}

		[[nodiscard]] static constexpr integer_value_type _get_conversion_precision() noexcept
		{
			if constexpr (sizeof(integer_value_type) >= 8)
			{
				return integer_value_type{ 1000000000 };
			}
			else if constexpr (sizeof(integer_value_type) >= 4)
			{
				return integer_value_type{ 1000000000 };
			}
			else if constexpr (sizeof(integer_value_type) >= 2)
			{
				return integer_value_type{ 10000 };
			}
			else
			{
				return integer_value_type{ 100 };
			}
		}

		template<bool FractionOnly, EmuConcepts::FloatingPoint InT >
		constexpr void _set_from_fp(const InT& floating_point_) noexcept
		{
			constexpr integer_value_type precision = _get_conversion_precision();
			auto integer{ _trunc(floating_point_) };
			auto fraction{ floating_point_ - integer };
			if (fraction == InT{})
			{
				if constexpr (FractionOnly)
				{
					top = static_cast<integer_value_type>(integer > InT{});
				}
				else
				{
					top = static_cast<integer_value_type>(integer);
				}
				bottom = integer_value_type{ 1 };
			}
			else
			{
				auto scaled_fraction = static_cast<integer_value_type>(_round(fraction * precision));
				auto gcd{ _greatest_common_divisor(scaled_fraction, precision) };
				top = scaled_fraction / gcd;
				bottom = (precision / gcd);
				if constexpr (!FractionOnly)
				{
					top += (bottom * static_cast<integer_value_type>(integer));
				}
			}
		}

	public:
		constexpr Fraction() noexcept :
			top{ 0 },
			bottom{ 1 }
		{
		}
		constexpr Fraction(Fraction<T> const&) noexcept(std::is_nothrow_copy_constructible_v<T>)
		requires(std::is_copy_constructible_v<T>) = default;
		constexpr Fraction(Fraction<T>&&) noexcept(std::is_nothrow_move_constructible_v<T>)
		requires(std::is_move_constructible_v<T>) = default;
		
		constexpr Fraction<T>& operator=(Fraction<T> const&) noexcept(std::is_nothrow_copy_assignable_v<T>)
		requires(std::is_copy_assignable_v<T>) = default;
		constexpr Fraction<T>& operator=(Fraction<T>&&) noexcept(std::is_nothrow_move_assignable_v<T>)
		requires(std::is_move_assignable_v<T>) = default;

		explicit constexpr Fraction<T>(integer_value_type top_, integer_value_type bottom_) noexcept :
			top{ top_ },
			bottom{ bottom_ }
		{
		}
		template<EmuConcepts::FloatingPoint InFP>
		explicit constexpr Fraction<T>(const InFP& floating_point_) noexcept
		{
			_set_from_fp<default_conversion_fraction_only>(floating_point_);
		}

		template<bool FractionOnly_, EmuConcepts::FloatingPoint OutT = default_floating_point_type>
		[[nodiscard]] constexpr OutT ToFloatingPoint() const noexcept(!FractionOnly_)
		{
			if constexpr (FractionOnly_)
			{
				integer_value_type fraction_top{ top };
				fraction_top -= (top / bottom) * bottom;
				return static_cast<OutT>(fraction_top) / static_cast<OutT>(bottom);
			}
			else
			{
				return static_cast<OutT>(top) / static_cast<OutT>(bottom);
			}
		}
		template<EmuConcepts::FloatingPoint OutT = default_floating_point_type>
		[[nodiscard]] constexpr OutT ToFloatingPoint() const noexcept(!default_conversion_fraction_only)
		{
			return ToFloatingPoint<default_conversion_fraction_only, OutT>();
		}

		template<bool FractionOnly_ = default_conversion_fraction_only, EmuConcepts::FloatingPoint InFP>
		constexpr Fraction<T>& operator=(const InFP& floating_point_) noexcept
		{
			_set_from_fp<FractionOnly_>(floating_point_);
			return *this;
		}

		[[nodiscard]] constexpr integer_type Top() const noexcept
		{
			return top;
		}

		[[nodiscard]] constexpr integer_type Bottom() const noexcept
		{
			return bottom;
		}

		constexpr Fraction<T>& Set(integer_value_type top_, integer_value_type bottom_) noexcept
		{
			top = top_;
			bottom = bottom_;
			return *this;
		}
		template<bool FractionOnly_ = default_conversion_fraction_only, EmuConcepts::FloatingPoint InFP>
		constexpr Fraction<T>& Set(const InFP& floating_point_) noexcept
		{
			_set_from_fp<FractionOnly_>(floating_point_);
			return *this;
		}

	private:
		integer_type top;
		integer_type bottom;
	};

	template<EmuConcepts::Integer Top, EmuConcepts::Integer Bottom>
	Fraction(Top, Bottom) -> Fraction<typename std::conditional<(sizeof(Top) >= sizeof(Bottom)), Top, Bottom>::type>;
}

static constexpr auto gdlnkfj = EmuMath::Fraction<int32_t>{ 1, 2 };
static constexpr auto bcv = gdlnkfj.ToFloatingPoint();
static constexpr auto fgblkjn = EmuMath::Fraction<int64_t>{ 21470000.f };

template<EmuConcepts::Arithmetic FracT, class StrElem_, class StrTraits_>
static std::basic_ostream<StrElem_, StrTraits_>& operator<<(std::basic_ostream<StrElem_, StrTraits_>& str, const EmuMath::Fraction<FracT>& fraction)
{
	if constexpr (sizeof(FracT) == 1)
	{
		str << static_cast<int>(fraction.Top()) << '/' << static_cast<int>(fraction.Bottom());
	}
	else
	{
		str << fraction.Top() << '/' << fraction.Bottom();
	}
	return str;
}

#endif
