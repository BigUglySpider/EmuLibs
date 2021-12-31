#ifndef EMU_CORE_MISC_MATH_FUNCTORS_H_INC_
#define EMU_CORE_MISC_MATH_FUNCTORS_H_INC_ 1

#include "Comparators.h"
#include "../TMPHelpers/TypeComparators.h"
#include "../TMPHelpers/Values.h"

namespace EmuCore
{
	template<class Value_, class Min_ = Value_, typename Out_ = EmuCore::TMP::remove_ref_cv_t<Value_>>
	struct do_clamp_min
	{
	private:
		using _cmp_greater_equal = EmuCore::do_cmp_greater_equal<Value_, Min_>;

	public:
		constexpr do_clamp_min()
		{
		}
		constexpr inline Out_ operator()(const Value_& value_, const Min_& min_) const
		{
			if (_cmp_greater_equal()(value_, min_))
			{
				// value_ >= min_
				if constexpr (std::is_constructible_v<Out_, const Value_&>)
				{
					return Out_(value_);
				}
				else if constexpr(std::is_convertible_v<const Value_&, Out_>)
				{
					return static_cast<Out_>(value_);
				}
				else
				{
					static_assert
					(
						EmuCore::TMP::get_false<Out_>(),
						"Attempted to perform a min-value clamp via EmuCore::do_clamp_min, but the provided Value_ type cannot be output as the desired Out_ type."
					);
				}
			}
			else
			{
				// value_ < min_
				if constexpr (std::is_constructible_v<Out_, const Min_&>)
				{
					return Out_(min_);
				}
				else if constexpr (std::is_convertible_v<const Min_&, Out_>)
				{
					return static_cast<Out_>(min_);
				}
				else
				{
					static_assert
					(
						EmuCore::TMP::get_false<Out_>(),
						"Attempted to perform a min-value clamp via EmuCore::do_clamp_min, but the provided Min_ type cannot be output as the desired Out_ type."
					);
				}
			}
		}
	};
	template<>
	struct do_clamp_min<void, void, void>
	{
		constexpr do_clamp_min()
		{
		}
		template<class Value_, class Min_, class Out_ = EmuCore::TMP::remove_ref_cv_t<Value_>>
		constexpr inline std::invoke_result_t<do_clamp_min<Value_, Min_, Out_>, const Value_&, const Min_&> operator()(const Value_& val_, const Min_& min_) const
		{
			return do_clamp_min<Value_, Min_, Out_>()(val_, min_);
		}
	};
	template<typename Out_>
	struct do_clamp_min<void, void, Out_>
	{
		constexpr do_clamp_min()
		{
		}
		template<class Value_, class Min_>
		constexpr inline std::invoke_result_t<do_clamp_min<Value_, Min_, Out_>, const Value_&, const Min_&> operator()(const Value_& val_, const Min_& min_) const
		{
			return do_clamp_min<Value_, Min_, Out_>()(val_, min_);
		}
	};

	template<class Value_, class Max_ = Value_, typename Out_ = EmuCore::TMP::remove_ref_cv_t<Value_>>
	struct do_clamp_max
	{
	private:
		using _cmp_less_equal = EmuCore::do_cmp_less_equal<Value_, Max_>;

	public:
		constexpr do_clamp_max()
		{
		}
		constexpr inline Out_ operator()(const Value_& value_, const Max_& max_) const
		{
			if (_cmp_less_equal()(value_, max_))
			{
				// value_ <= max_
				if constexpr (std::is_constructible_v<Out_, const Value_&>)
				{
					return Out_(value_);
				}
				else if constexpr(std::is_convertible_v<const Value_&, Out_>)
				{
					return static_cast<Out_>(value_);
				}
				else
				{
					static_assert
					(
						EmuCore::TMP::get_false<Out_>(),
						"Attempted to perform a max-value clamp via EmuCore::do_clamp_max, but the provided Value_ type cannot be output as the desired Out_ type."
					);
				}
			}
			else
			{
				// value_ > max_
				if constexpr (std::is_constructible_v<Out_, const Max_&>)
				{
					return Out_(max_);
				}
				else if constexpr (std::is_convertible_v<const Max_&, Out_>)
				{
					return static_cast<Out_>(max_);
				}
				else
				{
					static_assert
					(
						EmuCore::TMP::get_false<Out_>(),
						"Attempted to perform a max-value clamp via EmuCore::do_clamp_max, but the provided Max_ type cannot be output as the desired Out_ type."
					);
				}
			}
		}
	};
	template<>
	struct do_clamp_max<void, void, void>
	{
		constexpr do_clamp_max()
		{
		}
		template<class Value_, class Max_, class Out_ = EmuCore::TMP::remove_ref_cv_t<Value_>>
		constexpr inline std::invoke_result_t<do_clamp_max<Value_, Max_, Out_>, const Value_&, const Max_&> operator()(const Value_& val_, const Max_& max_) const
		{
			return do_clamp_max<Value_, Max_, Out_>()(val_, max_);
		}
	};
	template<typename Out_>
	struct do_clamp_max<void, void, Out_>
	{
		constexpr do_clamp_max()
		{
		}
		template<class Value_, class Max_>
		constexpr inline std::invoke_result_t<do_clamp_max<Value_, Max_, Out_>, const Value_&, const Max_&> operator()(const Value_& val_, const Max_& max_) const
		{
			return do_clamp_max<Value_, Max_, Out_>()(val_, max_);
		}
	};

	template<class Value_, class Min_ = Value_, class Max_ = Min_, class Out_ = EmuCore::TMP::remove_ref_cv_t<Value_>>
	struct do_clamp
	{
	private:
		using _cmp_less_min = EmuCore::do_cmp_less<Value_, Min_>;
		using _cmp_greater_max = EmuCore::do_cmp_greater<Value_, Max_>;

	public:
		constexpr do_clamp()
		{
		}

		constexpr inline Value_ operator()(const Value_& value_, const Min_& min_, const Max_& max_) const
		{
			if (_cmp_less_min()(value_, min_))
			{
				// value_ < min_
				if constexpr (std::is_constructible_v<Out_, const Min_&>)
				{
					return Out_(min_);
				}
				else if constexpr(std::is_convertible_v<const Min_&, Out_>)
				{
					return static_cast<Out_>(min_);
				}
				else
				{
					static_assert
					(
						EmuCore::TMP::get_false<Out_>(),
						"Attempted to perform a min-max-value clamp via EmuCore::do_clamp, but the provided Min_ type cannot be output as the desired Out_ type."
					);
				}
			}
			else if (_cmp_greater_max()(value_, max_))
			{
				// value_ > max_
				if constexpr (std::is_constructible_v<Out_, const Max_&>)
				{
					return Out_(max_);
				}
				else if constexpr(std::is_convertible_v<const Max_&, Out_>)
				{
					return static_cast<Out_>(max_);
				}
				else
				{
					static_assert
					(
						EmuCore::TMP::get_false<Out_>(),
						"Attempted to perform a min-max-value clamp via EmuCore::do_clamp, but the provided Max_ type cannot be output as the desired Out_ type."
					);
				}
			}
			else
			{
				// value_ >= min_ && value_ <= max_
				if constexpr (std::is_constructible_v<Out_, const Value_&>)
				{
					return Out_(value_);
				}
				else if constexpr(std::is_convertible_v<const Value_&, Out_>)
				{
					return static_cast<Out_>(value_);
				}
				else
				{
					static_assert
					(
						EmuCore::TMP::get_false<Out_>(),
						"Attempted to perform a min-max-value clamp via EmuCore::do_clamp, but the provided Value_ type cannot be output as the desired Out_ type."
					);
				}
			}
		}
	};
	template<>
	struct do_clamp<void, void, void, void>
	{
		constexpr do_clamp()
		{
		}
		template<class Value_, class Min_, class Max_, class Out_ = EmuCore::TMP::remove_ref_cv_t<Value_>>
		constexpr inline std::invoke_result_t<do_clamp<Value_, Min_, Max_, Out_>, const Value_&, const Min_&, const Max_&> operator()
		(
			const Value_& val_,
			const Min_& min_,
			const Max_& max_
		) const
		{
			return do_clamp<Value_, Min_, Max_, Out_>()(val_, min_, max_);
		}
	};
	template<class Out_>
	struct do_clamp<void, void, void, Out_>
	{
		constexpr do_clamp()
		{
		}
		template<class Value_, class Min_, class Max_>
		constexpr inline std::invoke_result_t<do_clamp<Value_, Min_, Max_, Out_>, const Value_&, const Min_&, const Max_&> operator()
		(
			const Value_& val_,
			const Min_& min_,
			const Max_& max_
		) const
		{
			return do_clamp<Value_, Min_, Max_, Out_>()(val_, min_, max_);
		}
	};
}

#endif
