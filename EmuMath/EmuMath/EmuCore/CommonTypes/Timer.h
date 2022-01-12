#ifndef EMU_CORE_TIMER_H_INC_
#define EMU_CORE_TIMER_H_INC_ 1

#include <chrono>
#include <limits>
#include <type_traits>
#include "../TMPHelpers/TimeTMP.h"
#include "../TMPHelpers/Values.h"

namespace EmuCore
{
	/// <summary>
	/// <para> Wrapper for using std::chrono::steady_clock to mark points in time and use them to create a duration. </para>
	/// </summary>
	template<class DefaultRatio_ = EmuCore::TMP::ratio_micro>
	class Timer
	{
	public:
		/// <summary> This type of this Timer instance. </summary>
		using this_type = Timer<DefaultRatio_>;
		/// <summary> Type of clock used to form time points via this timer. </summary>
		using clock_type = std::chrono::steady_clock;
		/// <summary> Type used to store internal time_points within this timer. </summary>
		using time_point = std::chrono::steady_clock::time_point;

		/// <summary> Ratio alias used to represent a picosecond, relative to seconds. </summary>
		using ratio_pico = EmuCore::TMP::ratio_pico;
		/// <summary> Ratio alias used to represent a nanosecond, relative to seconds. </summary>
		using ratio_nano = EmuCore::TMP::ratio_nano;
		/// <summary> Ratio alias used to represent a microsecond, relative to seconds. </summary>
		using ratio_micro = EmuCore::TMP::ratio_micro;
		/// <summary> Ratio alias used to represent a millisecond, relative to seconds. </summary>
		using ratio_milli = EmuCore::TMP::ratio_milli;
		/// <summary> Ratio alias used to represent a second, relative to seconds. </summary>
		using ratio_second = EmuCore::TMP::ratio_second;
		/// <summary> Ratio alias used to represent a minute, relative to seconds. </summary>
		using ratio_minute = EmuCore::TMP::ratio_minute;
		/// <summary> Ratio alias used to represent an hour, relative to seconds. </summary>
		using ratio_hour = EmuCore::TMP::ratio_hour;
		/// <summary> Ratio alias used to represent a day, relative to seconds. </summary>
		using ratio_day = EmuCore::TMP::ratio_day;
		/// <summary> Ratio alias used to represent a week, relative to seconds. </summary>
		using ratio_week = EmuCore::TMP::ratio_week;
		/// <summary> Ratio used by default when no alternative argument is provided. </summary>
		using ratio_default = DefaultRatio_;

		/// <summary> Shorthand for this timer's clock_type::now() static function. </summary>
		/// <returns>Result of this_type::clock_type::now().</returns>
		[[nodiscard]] static inline time_point now() noexcept
		{
			return clock_type::now();
		}

		inline Timer() noexcept : begin(), end(), has_started(false)
		{
			_reset();
		}

		explicit inline Timer(bool start_timer_) noexcept : begin(), end(), has_started(start_timer_)
		{
			if (start_timer_)
			{
				_reset();
			}
		}

		Timer(const this_type& to_copy_, bool start_timer_) noexcept :
			begin(to_copy_.begin),
			end(to_copy_.end),
			has_started(start_timer_)
		{
		}
		Timer(const this_type& to_copy_) noexcept : Timer(to_copy_, to_copy_.has_started)
		{
		}

		Timer(this_type&& to_move_, bool start_timer_) noexcept :
			begin(std::move<time_point>(to_move_.begin)),
			end(std::move<time_point>(to_move_.end)),
			has_started(start_timer_)
		{
		}
		Timer(this_type&& to_move_) noexcept : Timer(std::forward<this_type>(to_move_), to_move_.has_started)
		{
		}

		/// <summary>
		/// <para> Restarts this timer, updating the begin-point and unfreezing the end point. </para>
		/// <para> 
		///		May optionally output the currently stored duration if the provided Out_ template parameter is a non-void type, with an optional custom duration ratio.
		/// </para>
		/// <para> If the provided Out_ type is void, no duration will be generated. </para>
		/// <para> If the provided Out_ type is a std::chrono::duration instance, OutRatio_ will not be used. </para>
		/// <para> If the provided Out_ type is none of the above, it must be valid for use in std::chrono::duration&lt;Out_, OutRatio_&gt;.</para>
		/// </summary>
		/// <typeparam name="Out_">Type to output the saved duration as, or void if no output is desired.</typeparam>
		/// <typeparam name="OutRatio_">Ratio to measure the output time in if an output should be generated. Unused if Out_ is a std::chrono::duration instance.</typeparam>
		/// <returns>Duration before restart represeneted as the provided Out_ type using a relevant ratio. No return if Out_ is void.</returns>
		template<class Out_ = void, class OutRatio_ = ratio_default>
		inline Out_ Restart() noexcept
		{
			if constexpr (!std::is_same_v<Out_, void>)
			{
				Out_ out_ = Get<Out_, OutRatio_>();
				_reset();
				has_started = true;
				return out_;
			}
			else
			{
				_reset();
				has_started = true;
			}
		}

		/// <summary>
		/// <para> Updates the end-point of this timer if it is capable to do so, and freezes it at that point until resumed or restarted. </para>
		/// <para> May optionally output the stored duration if the provided Out_ template parameter is a non-void type, with an optional custom duration ratio. </para>
		/// <para> If the provided Out_ type is void, no duration will be generated. </para>
		/// <para> If the provided Out_ type is a std::chrono::duration instance, OutRatio_ will not be used. </para>
		/// <para> If the provided Out_ type is none of the above, it must be valid for use in std::chrono::duration&lt;Out_, OutRatio_&gt;.</para>
		/// </summary>
		/// <typeparam name="Out_">Type to output the saved duration as, or void if no output is desired.</typeparam>
		/// <typeparam name="OutRatio_">Ratio to measure the output time in if an output should be generated. Unused if Out_ is a std::chrono::duration instance.</typeparam>
		/// <returns>Duration represeneted as the provided Out_ type using a relevant ratio. No return if Out_ is void.</returns>
		template<class Out_ = void, class OutRatio_ = ratio_default>
		inline Out_ Pause() noexcept
		{
			if (has_started)
			{
				end = now();
				has_started = false;
			}
			if constexpr (!std::is_same_v<Out_, void>)
			{
				return Get<Out_, OutRatio_>();
			}
		}

		/// <summary> 
		/// <para> Unfreezes the end-point of this timer. </para>
		/// <para> 
		///		Note that this will add on any time that the timer has been paused for.
		///		(e.g. if a timer was paused at 12ms, and is resumed 20ms later, an immediate Get() would lead to a ~32ms result)
		/// </para>
		/// </summary>
		inline void Resume()
		{
			has_started = true;
		}

		/// <summary>
		/// <para> Returns the time between this timer's begin- and end-points, represented as the provided Out_ type with an optional ratio in terms of seconds. </para>
		/// <para> If the end-point of this timer is currently unfrozen, this will not freeze it. For such behaviour, use Pause with the same template arguments. </para>
		/// <para> If the provided Out_ type is a std::chrono::duration instance, OutRatio_ will not be used. </para>
		/// <para> If the provided Out_ type is none of the above, it must be valid for use in std::chrono::duration&lt;Out_, OutRatio_&gt;.</para>
		/// </summary>
		/// <typeparam name="Out_">Type to output the saved duration as.</typeparam>
		/// <typeparam name="OutRatio_">Ratio to measure the output time in. Unused if Out_ is a std::chrono::duration instance.</typeparam>
		/// <returns>Duration represeneted as the provided Out_ type using a relevant ratio.</returns>
		template<class Out_ = double, class OutRatio_ = ratio_default>
		[[nodiscard]] inline Out_ Get() const noexcept
		{
			if constexpr (EmuCore::TMP::is_duration_v<Out_>)
			{
				if (has_started)
				{
					return _peek_duration<Out_>();
				}
				else
				{
					return _get_duration<Out_>();
				}
			}
			else if constexpr (std::is_integral_v<Out_>)
			{
				// Handle integer rounding manually, just to ensure clamp in a valid range
				using count_type = long double;
				const count_type count_ = Get<count_type, OutRatio_>();
				constexpr Out_ min_result = std::numeric_limits<Out_>::lowest();
				constexpr Out_ max_result = std::numeric_limits<Out_>::max();

				if (count_ <= min_result)
				{
					return min_result;
				}
				else if (count_ >= max_result)
				{
					return max_result;
				}
				else
				{
					return static_cast<Out_>(count_);
				}
			}
			else
			{
				using duration_type = std::chrono::duration<Out_, OutRatio_>;
				if (has_started)
				{
					return _peek_duration<duration_type>().count();
				}
				else
				{
					return _get_duration<duration_type>().count();
				}
			}
		}

		/// <summary> Returns this timer's stored begin-point. </summary>
		/// <returns>A copy of the time_point saved when this Timer was last started.</returns>
		[[nodiscard]] inline time_point GetBegin() const noexcept
		{
			return begin;
		}

		/// <summary> Returns this timer's current end-point. </summary>
		/// <returns>A copy of the time_point saved when this Timer was last paused, or now() if the end-point is not currently frozen.</returns>
		[[nodiscard]] inline time_point GetEnd() const noexcept
		{
			if (has_started)
			{
				return now();
			}
			else
			{
				return end;
			}
		}

		/// <summary> 
		/// <para> Shorthand to get this timer's current duration in nanoseconds. See Get for more details. </para>
		/// <para> Note that output will not be in nanoseconds if the provided Out_ type is a non-nanosecond std::chrono::duration instance. </para>
		/// </summary>
		/// <typeparam name="Out_">Type to output the determined duration as.</typeparam>
		/// <returns>The duration between this timer's begin- and end-points, measured in nanoseconds if possible.</returns>
		template<class Out_ = double>
		[[nodiscard]] inline Out_ GetNano() const noexcept
		{
			return Get<Out_, ratio_nano>();
		}
		/// <summary> 
		/// <para> Shorthand to get this timer's current duration in microseconds. See Get for more details. </para>
		/// <para> Note that output will not be in microseconds if the provided Out_ type is a non-microsecond std::chrono::duration instance. </para>
		/// </summary>
		/// <typeparam name="Out_">Type to output the determined duration as.</typeparam>
		/// <returns>The duration between this timer's begin- and end-points, measured in microseconds if possible.</returns>
		template<class Out_ = double>
		[[nodiscard]] inline Out_ GetMicro() const noexcept
		{
			return Get<Out_, ratio_micro>();
		}
		/// <summary> 
		/// <para> Shorthand to get this timer's current duration in milliseconds. See Get for more details. </para>
		/// <para> Note that output will not be in milliseconds if the provided Out_ type is a non-millisecond std::chrono::duration instance. </para>
		/// </summary>
		/// <typeparam name="Out_">Type to output the determined duration as.</typeparam>
		/// <returns>The duration between this timer's begin- and end-points, measured in milliseconds if possible.</returns>
		template<class Out_ = double>
		[[nodiscard]] inline Out_ GetMilli() const noexcept
		{
			return Get<Out_, ratio_milli>();
		}
		/// <summary> 
		/// <para> Shorthand to get this timer's current duration in seconds. See Get for more details. </para>
		/// <para> Note that output will not be in seconds if the provided Out_ type is a non-second std::chrono::duration instance. </para>
		/// </summary>
		/// <typeparam name="Out_">Type to output the determined duration as.</typeparam>
		/// <returns>The duration between this timer's begin- and end-points, measured in seconds if possible.</returns>
		template<class Out_ = double>
		[[nodiscard]] inline Out_ GetSeconds() const noexcept
		{
			return Get<Out_, ratio_second>();
		}
		/// <summary> 
		/// <para> Shorthand to get this timer's current duration in minutes. See Get for more details. </para>
		/// <para> Note that output will not be in minutes if the provided Out_ type is a non-minute std::chrono::duration instance. </para>
		/// </summary>
		/// <typeparam name="Out_">Type to output the determined duration as.</typeparam>
		/// <returns>The duration between this timer's begin- and end-points, measured in minutes if possible.</returns>
		template<class Out_ = double>
		[[nodiscard]] inline Out_ GetMinutes() const noexcept
		{
			return Get<Out_, ratio_minute>();
		}
		/// <summary> 
		/// <para> Shorthand to get this timer's current duration in hours. See Get for more details. </para>
		/// <para> Note that output will not be in hours if the provided Out_ type is a non-hour std::chrono::duration instance. </para>
		/// </summary>
		/// <typeparam name="Out_">Type to output the determined duration as.</typeparam>
		/// <returns>The duration between this timer's begin- and end-points, measured in hours if possible.</returns>
		template<class Out_ = double>
		[[nodiscard]] inline Out_ GetHours() const noexcept
		{
			return Get<Out_, ratio_hour>();
		}

	private:
		inline void _reset() noexcept
		{
			begin = now();
		}

		template<class Duration_>
		[[nodiscard]] inline Duration_ _get_duration() const noexcept
		{
			if constexpr (EmuCore::TMP::is_duration_v<Duration_>)
			{
				return Duration_(end - begin);
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<Duration_>(), "Attempted to retrieve an EmuCore::Timer duration with a type that is not an instance of std::chrono::duration.");
			}
		}

		template<class Duration_>
		[[nodiscard]] inline Duration_ _peek_duration() const noexcept
		{
			if constexpr (EmuCore::TMP::is_duration_v<Duration_>)
			{
				return Duration_(now() - begin);
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<Duration_>(), "Attempted to peek at an EmuCore::Timer duration with a type that is not an instance of std::chrono::duration.");
			}
		}

		time_point begin;
		time_point end;
		bool has_started;
	};
}

#endif
