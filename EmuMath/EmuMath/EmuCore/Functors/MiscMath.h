#ifndef EMU_CORE_MISC_MATH_FUNCTORS_H_INC_
#define EMU_CORE_MISC_MATH_FUNCTORS_H_INC_ 1

#include "Comparators.h"
#include "../ArithmeticHelpers/CommonMath.h"
#include "../TMPHelpers/TypeComparators.h"
#include <cstddef>
#include <functional>

namespace EmuCore
{
	template<class Value_, class Min_ = Value_>
	struct do_clamp_min
	{
	private:
		EmuCore::do_cmp_less<Value_, Min_> cmp_less;

	public:
		constexpr do_clamp_min() : cmp_less(), min_val()
		{
		}
		template<class...MinConstructionArgs_, typename = std::enable_if_t<std::is_constructible_v<Min_, MinConstructionArgs_...>>>
		constexpr do_clamp_min(MinConstructionArgs_&&... min_construction_args_) : 
			min_val(std::forward<MinConstructionArgs_>(min_construction_args_)...),
			cmp_less()
		{
		}

		constexpr inline Value_ operator()(const Value_& value_) const
		{
			return cmp_less(value_, min_val) ? static_cast<Value_>(min_val) : value_;
		}
		constexpr inline Value_ operator()(const Value_& value_, const Min_& custom_min_) const
		{
			return cmp_less(value_, custom_min_) ? static_cast<Value_>(custom_min_) : value_;
		}

		Min_ min_val;
	};
	template<>
	struct do_clamp_min<void, void>
	{
		constexpr do_clamp_min()
		{
		}
		template<class Value_, class Min_>
		constexpr inline Value_ operator()(const Value_& val_, const Min_& min_) const
		{
			return do_clamp_min<Value_, Min_>()(val_, min_);
		}
	};

	template<class Value_, class Max_ = Value_>
	struct do_clamp_max
	{
	private:
		EmuCore::do_cmp_greater<Value_, Max_> cmp_greater;

	public:
		constexpr do_clamp_max() : cmp_greater(), max_val()
		{
		}
		template<class...MaxConstructionArgs_, typename = std::enable_if_t<std::is_constructible_v<Max_, MaxConstructionArgs_...>>>
		constexpr do_clamp_max(MaxConstructionArgs_&&... min_construction_args_) :
			max_val(std::forward<MaxConstructionArgs_>(min_construction_args_)...),
			cmp_greater()
		{
		}

		constexpr inline Value_ operator()(const Value_& value_) const
		{
			return cmp_greater(value_, max_val) ? static_cast<Value_>(max_val) : value_;
		}
		constexpr inline Value_ operator()(const Value_& value_, const Max_& custom_max_) const
		{
			return cmp_greater(value_, custom_max_) ? static_cast<Value_>(custom_max_) : value_;
		}

		Max_ max_val;
	};
	template<>
	struct do_clamp_max<void, void>
	{
		constexpr do_clamp_max()
		{
		}
		template<class Value_, class Min_>
		constexpr inline Value_ operator()(const Value_& val_, const Min_& min_) const
		{
			return do_clamp_max<Value_, Min_>()(val_, min_);
		}
	};

	template<class Value_, class Min_ = Value_, class Max_ = Min_>
	struct do_clamp
	{
	private:
		EmuCore::do_cmp_less<Value_, Min_> cmp_less_min;
		EmuCore::do_cmp_greater<Value_, Max_> cmp_greater_max;

	public:
		constexpr do_clamp() : cmp_less_min(), cmp_greater_max(), min_value(), max_value()
		{
		}
		constexpr do_clamp(const Min_& min_value_, const Max_& max_value_) : cmp_less_min(), cmp_greater_max(), min_value(min_value_), max_value(max_value_)
		{
		}

		constexpr inline Value_ operator()(const Value_& value_) const
		{
			return
			(
				cmp_less_min(value_, min_value) ? static_cast<Value_>(min_value) :
				cmp_greater_max(value_, max_value) ? static_cast<Value_>(max_value) :
				value_
			);
		}
		constexpr inline Value_ operator()(const Value_& value_, const Min_& custom_min_, const Max_& custom_max_) const
		{
			return
			(
				cmp_less_min(value_, custom_min_) ? static_cast<Value_>(custom_min_) :
				cmp_greater_max(value_, custom_max_) ? static_cast<Value_>(custom_max_) :
				value_
			);
		}

		Min_ min_value;
		Max_ max_value;
	};
	template<>
	struct do_clamp<void, void, void>
	{
		constexpr do_clamp()
		{
		}
		template<class Value_, class Min_, class Max_>
		constexpr inline Value_ operator()(const Value_& val_, const Min_& min_, const Max_& max_) const
		{
			return do_clamp<Value_, Min_>()(val_, min_, max_);
		}
	};
}

#endif
