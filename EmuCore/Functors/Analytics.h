#ifndef EMU_CORE_ANALYTIC_FUNCTORS_H_INC_
#define EMU_CORE_ANALYTIC_FUNCTORS_H_INC_ 1

#include <limits>

namespace EmuCore
{
	/// <summary> Analytic functor for tracking a minimum value. May be used for tasks such as iterating over containers. </summary>
	template<typename Min_>
	struct analytic_track_min
	{
		using value_type = Min_;
		static constexpr value_type _reset_value = std::numeric_limits<value_type>::max();

		constexpr analytic_track_min() : min_value(_reset_value)
		{
		}

		inline void Reset()
		{
			min_value = _reset_value;
		}

		template<typename Val_>
		constexpr inline void operator()(const Val_& val_)
		{
			if (val_ < min_value)
			{
				min_value = val_;
			}
		}

		value_type min_value;
	};

	/// <summary> Analytic functor for tracking a maximum value. May be used for tasks such as iterating over containers. </summary>
	template<typename Max_>
	struct analytic_track_max
	{
		using value_type = Max_;
		static constexpr value_type _reset_value = std::numeric_limits<value_type>::lowest();

		constexpr analytic_track_max() : max_value(_reset_value)
		{
		}

		inline void Reset()
		{
			max_value = _reset_value;
		}

		template<typename Val_>
		constexpr inline void operator()(const Val_& val_)
		{
			if (val_ > max_value)
			{
				max_value = val_;
			}
		}

		value_type max_value;
	};

	/// <summary> Analytic functor for tracking a number of calls. Every time this is called, it will increment an internal counter. </summary>
	template<typename Counter_>
	struct analytic_count
	{
		using value_type = Counter_;
		static constexpr value_type _increment_value = value_type(1);
		static constexpr value_type _reset_value = value_type(0);

		constexpr analytic_count() : total_calls(_reset_value)
		{
		}

		inline void Reset()
		{
			total_calls = _reset_value;
		}

		template<typename...Args_>
		constexpr inline void operator()(Args_&&...dummy_args_)
		{
			total_calls = total_calls + _increment_value;
		}

		value_type total_calls;
	};

	/// <summary> Analytic functor for tracking a total sum of values. May be used for tasks such as iterating over containers. </summary>
	template<typename Sum_>
	struct analytic_sum
	{
		using value_type = Sum_;
		static constexpr value_type _reset_value = value_type(0);

		constexpr analytic_sum() : total_sum(_reset_value)
		{
		}

		inline void Reset()
		{
			total_sum = _reset_value;
		}

		template<typename T_>
		constexpr inline void operator()(T_ val_)
		{
			total_sum = total_sum + static_cast<value_type>(val_);
		}

		value_type total_sum;
	};
}

#endif
