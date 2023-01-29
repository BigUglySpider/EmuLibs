#ifndef EMU_CORE_STOPWATCH_H_INC_
#define EMU_CORE_STOPWATCH_H_INC_ 1

#include <chrono>
#include <limits>
#include <type_traits>
#include "Timer.h"
#include "../TMPHelpers/TimeTMP.h"

namespace EmuCore
{
	/// <summary>
	/// <para> Timer wrapper that may be used as a stopwatch to combine several timed segments. </para>
	/// </summary>
	template<class DefaultRatio_ = EmuCore::TMP::ratio_micro>
	class Stopwatch
	{
	public:
		/// <summary> This type of this Stopwatch instance. </summary>
		using this_type = Stopwatch<DefaultRatio_>;
		/// <summary> The underlying Timer used to support this Stopwatch. </summary>
		using timer_type = EmuCore::Timer<DefaultRatio_>;

		/// <summary> Type of clock used to form time points via this stopwatch's underlying timer. </summary>
		using clock_type = typename timer_type::clock_type;
		/// <summary> Type used to store internal time_points within this stopwatch's underlying timer. </summary>
		using time_point = typename timer_type::time_point;

		/// <summary> Ratio alias used to represent a picosecond, relative to seconds. </summary>
		using ratio_pico = typename timer_type::ratio_pico;
		/// <summary> Ratio alias used to represent a nanosecond, relative to seconds. </summary>
		using ratio_nano = typename timer_type::ratio_nano;
		/// <summary> Ratio alias used to represent a microsecond, relative to seconds. </summary>
		using ratio_micro = typename timer_type::ratio_micro;
		/// <summary> Ratio alias used to represent a millisecond, relative to seconds. </summary>
		using ratio_milli = typename timer_type::ratio_milli;
		/// <summary> Ratio alias used to represent a second, relative to seconds. </summary>
		using ratio_second = typename timer_type::ratio_second;
		/// <summary> Ratio alias used to represent a minute, relative to seconds. </summary>
		using ratio_minute = typename timer_type::ratio_minute;
		/// <summary> Ratio alias used to represent an hour, relative to seconds. </summary>
		using ratio_hour = typename timer_type::ratio_hour;
		/// <summary> Ratio alias used to represent a day, relative to seconds. </summary>
		using ratio_day = typename timer_type::ratio_day;
		/// <summary> Ratio alias used to represent a week, relative to seconds. </summary>
		using ratio_week = typename timer_type::ratio_week;
		/// <summary> Ratio used by default when no alternative argument is provided. </summary>
		using ratio_default = typename timer_type::ratio_default;

		/// <summary> Primitive type representative of durations calculates by this stopwatch. </summary>
		using count_type = double;
		/// <summary> Instance of std::chrono::duration used by this stopwatch to calculatie durations. </summary>
		using duration_type = std::chrono::duration<count_type, ratio_default>;

		/// <summary> Constant used to set one of this Stopwatch's duration_types to zero. </summary>
		static constexpr duration_type zero_time = duration_type(count_type(0));

		Stopwatch() noexcept : 
			timer(),
			current_time(zero_time),
			is_active(false)
		{
		}

		explicit Stopwatch(bool start_stopwatch_) noexcept : 
			timer(start_stopwatch_),
			current_time(zero_time),
			is_active(start_stopwatch_)
		{
		}

		Stopwatch(const this_type& to_copy_) noexcept : 
			timer(),
			current_time(to_copy_.current_time),
			is_active(false)
		{
		}
		Stopwatch(const this_type& to_copy_, bool start_stopwatch_) noexcept :
			timer(start_stopwatch_),
			current_time(to_copy_.current_time),
			is_active(start_stopwatch_)
		{
		}

		Stopwatch(this_type&& to_move_) noexcept :
			timer(),
			current_time(std::move(to_move_.current_time)),
			is_active(false)
		{
		}
		Stopwatch(this_type&& to_move_, bool start_stopwatch_) noexcept :
			timer(start_stopwatch_),
			current_time(std::move(to_move_.current_time)),
			is_active(start_stopwatch_)
		{
		}

		/// <summary>
		/// <para> Starts a timed segment for this stopwatch. </para>
		/// <para> This will not reset the currently counted time. For such behaviour, use Restart instead. </para>
		/// </summary>
		inline void Start() noexcept
		{
			is_active = true;
			timer.Restart();
		}

		/// <summary>
		/// <para> Sets the counted time for this stopwatch to zero, and commences a new timed segment. </para>
		/// <para> To start a new timed segment without reseting the total counted time, use Start instead. </para>
		/// <para> May additionally output the total counted time before reset if the provided Out_ template argument is a non-void type. </para>
		/// </summary>
		/// <typeparam name="Out_">Type to output the total counted time before reset as, or void to indicate that no output should be generated.</typeparam>
		/// <typeparam name="OutRatio_">Ratio to output the total counted time as. If Out_ is an instance of std::chrono::duration, this will not be used.</typeparam>
		/// <returns>Total counted time before restart, represented with the provided Out_ type and relevant ratio. No return if Out_ is void.</returns>
		template<class Out_ = void, class OutRatio_ = ratio_default>
		inline Out_ Restart() noexcept
		{
			if constexpr (!std::is_same_v<Out_, void>)
			{
				Out_ out_ = Get<Out_, OutRatio_>();
				current_time = zero_time;
				Start();
				return out_;
			}
			else
			{
				current_time = zero_time;
				Start();
			}
		}

		/// <summary>
		/// <para> Stops the current timed segment, preventing any additional ticks being appended to this stopwatch until it is started again. </para>
		/// <para> May additionally output the total counted time if the provided Out_ template argument is a non-void type. </para>
		/// </summary>
		/// <typeparam name="Out_">Type to output the total counted time as, or void to indicate that no output should be generated.</typeparam>
		/// <typeparam name="OutRatio_">Ratio to output the total counted time as. If Out_ is an instance of std::chrono::duration, this will not be used.</typeparam>
		/// <returns>Total counted time after stopping, represented with the provided Out_ type and relevant ratio. No return if Out_ is void.</returns>
		template<class Out_ = void, class OutRatio_ = ratio_default>
		inline Out_ Stop() noexcept
		{
			if (is_active)
			{
				current_time += timer.template Pause<duration_type>();
				is_active = false;
			}

			if constexpr (!std::is_same_v<Out_, void>)
			{
				return Get<Out_, OutRatio_>();
			}
		}

		/// <summary>
		/// <para> Gets the total counted time within this stopwatch, including the currently active segment if there is one. </para>
		/// <para> To retrieve only the total of completed segments, use GetCompleteSegmentsOnly with the same template arguments instead. </para>
		/// </summary>
		/// <typeparam name="Out_">Type to output the total counted time as.</typeparam>
		/// <typeparam name="OutRatio_">Ratio to output the total counted time as. If Out_ is an instance of std::chrono::duration, this will not be used.</typeparam>
		/// <returns>Total counted time including the currently active segment, represented with the provided Out_ type and relevant ratio.</returns>
		template<class Out_ = count_type, class OutRatio_ = ratio_default>
		[[nodiscard]] inline Out_ Get() const noexcept
		{
			if (is_active)
			{
				return _convert_to_output<Out_, OutRatio_>(current_time + timer.template Get<duration_type>());
			}
			else
			{
				return _convert_to_output<Out_, OutRatio_>(current_time);
			}
		}

		/// <summary>
		/// <para> Gets the total counted time within this stopwatch, excluding the currently active segment if there is one. </para>
		/// <para> To include the currently active segment in the output count, use Get with the same template arguments instead. </para>
		/// </summary>
		/// <typeparam name="Out_">Type to output the total counted time as.</typeparam>
		/// <typeparam name="OutRatio_">Ratio to output the total counted time as. If Out_ is an instance of std::chrono::duration, this will not be used.</typeparam>
		/// <returns>Total counted time excluding the currently active segment, represented with the provided Out_ type and relevant ratio.</returns>
		template<class Out_ = count_type, class OutRatio_ = ratio_default>
		[[nodiscard]] inline Out_ GetCompleteSegmentsOnly() const noexcept
		{
			return _convert_to_output<Out_, OutRatio_>(current_time);
		}

		/// <summary>
		/// <para> Gets the total time that has been counted within the current segment. </para>
		/// <para> If this stopwatch is currently active, this will be the length of the most recent segment. </para>
		/// </summary>
		/// <typeparam name="Out_">Type to output the current segment's time as.</typeparam>
		/// <typeparam name="OutRatio_">Ratio to output the current segment's time as. If Out_ is an instance of std::chrono::duration, this will not be used.</typeparam>
		/// <returns>The time of the currently active segment (or most recent segment if stopped), represented with the provided Out_ type and relevant ratio.</returns>
		template<class Out_ = count_type, class OutRatio_ = ratio_default>
		[[nodiscard]] inline Out_ GetCurrentSegment() const noexcept
		{
			return timer.template Get<Out_, OutRatio_>();
		}

		/// <summary> Returns a boolean indicating if this stopwatch is currently active. </summary>
		/// <returns>True if a segment is currently being timed, otherwise false.</returns>
		[[nodiscard]] inline bool IsActive() const noexcept
		{
			return is_active;
		}

		/// <summary>
		/// <para> Shorthand to get this stopwatch's current total time in nanoseconds. See Get for more details. </para>
		/// <para> Note that output will not be in nanoseconds if the provided Out_ type is a non-nanosecond std::chrono::duration instance. </para>
		/// </summary>
		/// <typeparam name="Out_">Type to output this stopwatch's current total time as.</typeparam>
		/// <returns>The current total time counted within this stopwatch, measured in nanoseconds if possible.</returns>
		template<class Out_ = double>
		[[nodiscard]] inline Out_ GetNano() const noexcept
		{
			return Get<Out_, ratio_nano>();
		}
		/// <summary>
		/// <para> Shorthand to get this stopwatch's current total time in microseconds. See Get for more details. </para>
		/// <para> Note that output will not be in microseconds if the provided Out_ type is a non-microsecond std::chrono::duration instance. </para>
		/// </summary>
		/// <typeparam name="Out_">Type to output this stopwatch's current total time as.</typeparam>
		/// <returns>The current total time counted within this stopwatch, measured in microseconds if possible.</returns>
		template<class Out_ = double>
		[[nodiscard]] inline Out_ GetMicro() const noexcept
		{
			return Get<Out_, ratio_micro>();
		}
		/// <summary>
		/// <para> Shorthand to get this stopwatch's current total time in milliseconds. See Get for more details. </para>
		/// <para> Note that output will not be in milliseconds if the provided Out_ type is a non-millisecond std::chrono::duration instance. </para>
		/// </summary>
		/// <typeparam name="Out_">Type to output this stopwatch's current total time as.</typeparam>
		/// <returns>The current total time counted within this stopwatch, measured in milliseconds if possible.</returns>
		template<class Out_ = double>
		[[nodiscard]] inline Out_ GetMilli() const noexcept
		{
			return Get<Out_, ratio_milli>();
		}
		/// <summary>
		/// <para> Shorthand to get this stopwatch's current total time in seconds. See Get for more details. </para>
		/// <para> Note that output will not be in seconds if the provided Out_ type is a non-second std::chrono::duration instance. </para>
		/// </summary>
		/// <typeparam name="Out_">Type to output this stopwatch's current total time as.</typeparam>
		/// <returns>The current total time counted within this stopwatch, measured in seconds if possible.</returns>
		template<class Out_ = double>
		[[nodiscard]] inline Out_ GetSeconds() const noexcept
		{
			return Get<Out_, ratio_second>();
		}
		/// <summary>
		/// <para> Shorthand to get this stopwatch's current total time in minutes. See Get for more details. </para>
		/// <para> Note that output will not be in minutes if the provided Out_ type is a non-minute std::chrono::duration instance. </para>
		/// </summary>
		/// <typeparam name="Out_">Type to output this stopwatch's current total time as.</typeparam>
		/// <returns>The current total time counted within this stopwatch, measured in minutes if possible.</returns>
		template<class Out_ = double>
		[[nodiscard]] inline Out_ GetMinutes() const noexcept
		{
			return Get<Out_, ratio_minute>();
		}
		/// <summary>
		/// <para> Shorthand to get this stopwatch's current total time in hours. See Get for more details. </para>
		/// <para> Note that output will not be in hours if the provided Out_ type is a non-hour std::chrono::duration instance. </para>
		/// </summary>
		/// <typeparam name="Out_">Type to output this stopwatch's current total time as.</typeparam>
		/// <returns>The current total time counted within this stopwatch, measured in hours if possible.</returns>
		template<class Out_ = double>
		[[nodiscard]] inline Out_ GetHours() const noexcept
		{
			return Get<Out_, ratio_hour>();
		}

		/// <summary>
		/// <para> Shorthand to get this stopwatch's current total time in nanoseconds, excluding the current segment. See GetCompleteSegmentsOnly for more details. </para>
		/// <para> Note that output will not be in nanoseconds if the provided Out_ type is a non-nanosecond std::chrono::duration instance. </para>
		/// </summary>
		/// <typeparam name="Out_">Type to output this stopwatch's current total time (excluding the current segment) as.</typeparam>
		/// <returns>The current total time (excluding the current segment) counted within this stopwatch, measured in nanoseconds if possible.</returns>
		template<class Out_ = double>
		[[nodiscard]] inline Out_ GetCompleteSegmentsOnlyNano() const noexcept
		{
			return GetCompleteSegmentsOnly<Out_, ratio_nano>();
		}
		/// <summary>
		/// <para> Shorthand to get this stopwatch's current total time in microseconds, excluding the current segment. See GetCompleteSegmentsOnly for more details. </para>
		/// <para> Note that output will not be in microseconds if the provided Out_ type is a non-microsecond std::chrono::duration instance. </para>
		/// </summary>
		/// <typeparam name="Out_">Type to output this stopwatch's current total time (excluding the current segment) as.</typeparam>
		/// <returns>The current total time (excluding the current segment) counted within this stopwatch, measured in microseconds if possible.</returns>
		template<class Out_ = double>
		[[nodiscard]] inline Out_ GetCompleteSegmentsOnlyMicro() const noexcept
		{
			return GetCompleteSegmentsOnly<Out_, ratio_micro>();
		}
		/// <summary>
		/// <para> Shorthand to get this stopwatch's current total time in milliseconds, excluding the current segment. See GetCompleteSegmentsOnly for more details. </para>
		/// <para> Note that output will not be in milliseconds if the provided Out_ type is a non-millisecond std::chrono::duration instance. </para>
		/// </summary>
		/// <typeparam name="Out_">Type to output this stopwatch's current total time (excluding the current segment) as.</typeparam>
		/// <returns>The current total time (excluding the current segment) counted within this stopwatch, measured in milliseconds if possible.</returns>
		template<class Out_ = double>
		[[nodiscard]] inline Out_ GetCompleteSegmentsOnlyMilli() const noexcept
		{
			return GetCompleteSegmentsOnly<Out_, ratio_milli>();
		}
		/// <summary>
		/// <para> Shorthand to get this stopwatch's current total time in seconds, excluding the current segment. See GetCompleteSegmentsOnly for more details. </para>
		/// <para> Note that output will not be in seconds if the provided Out_ type is a non-second std::chrono::duration instance. </para>
		/// </summary>
		/// <typeparam name="Out_">Type to output this stopwatch's current total time (excluding the current segment) as.</typeparam>
		/// <returns>The current total time (excluding the current segment) counted within this stopwatch, measured in seconds if possible.</returns>
		template<class Out_ = double>
		[[nodiscard]] inline Out_ GetCompleteSegmentsOnlySeconds() const noexcept
		{
			return GetCompleteSegmentsOnly<Out_, ratio_second>();
		}
		/// <summary>
		/// <para> Shorthand to get this stopwatch's current total time in minutes, excluding the current segment. See GetCompleteSegmentsOnly for more details. </para>
		/// <para> Note that output will not be in minutes if the provided Out_ type is a non-minute std::chrono::duration instance. </para>
		/// </summary>
		/// <typeparam name="Out_">Type to output this stopwatch's current total time (excluding the current segment) as.</typeparam>
		/// <returns>The current total time (excluding the current segment) counted within this stopwatch, measured in minutes if possible.</returns>
		template<class Out_ = double>
		[[nodiscard]] inline Out_ GetCompleteSegmentsOnlyMinutes() const noexcept
		{
			return GetCompleteSegmentsOnly<Out_, ratio_minute>();
		}
		/// <summary>
		/// <para> Shorthand to get this stopwatch's current total time in hours, excluding the current segment. See GetCompleteSegmentsOnly for more details. </para>
		/// <para> Note that output will not be in hours if the provided Out_ type is a non-hour std::chrono::duration instance. </para>
		/// </summary>
		/// <typeparam name="Out_">Type to output this stopwatch's current total time (excluding the current segment) as.</typeparam>
		/// <returns>The current total time (excluding the current segment) counted within this stopwatch, measured in hours if possible.</returns>
		template<class Out_ = double>
		[[nodiscard]] inline Out_ GetCompleteSegmentsOnlyHours() const noexcept
		{
			return GetCompleteSegmentsOnly<Out_, ratio_hour>();
		}

		/// <summary>
		/// <para> Shorthand to get this stopwatch's current segment's time in nanoseconds. See GetCurrentSegment for more details. </para>
		/// <para> Note that output will not be in nanoseconds if the provided Out_ type is a non-nanosecond std::chrono::duration instance. </para>
		/// </summary>
		/// <typeparam name="Out_">Type to output this stopwatch's current segment's time as.</typeparam>
		/// <returns>The current segment's time counted within this stopwatch, measured in nanoseconds if possible.</returns>
		template<class Out_ = double>
		[[nodiscard]] inline Out_ GetCurrentSegmentNano() const noexcept
		{
			return GetCurrentSegment<Out_, ratio_nano>();
		}
		/// <summary>
		/// <para> Shorthand to get this stopwatch's current segment's time in microseconds. See GetCurrentSegment for more details. </para>
		/// <para> Note that output will not be in microseconds if the provided Out_ type is a non-microsecond std::chrono::duration instance. </para>
		/// </summary>
		/// <typeparam name="Out_">Type to output this stopwatch's current segment's time as.</typeparam>
		/// <returns>The current segment's time counted within this stopwatch, measured in microseconds if possible.</returns>
		template<class Out_ = double>
		[[nodiscard]] inline Out_ GetCurrentSegmentMicro() const noexcept
		{
			return GetCurrentSegment<Out_, ratio_micro>();
		}
		/// <summary>
		/// <para> Shorthand to get this stopwatch's current segment's time in milliseconds. See GetCurrentSegment for more details. </para>
		/// <para> Note that output will not be in milliseconds if the provided Out_ type is a non-millisecond std::chrono::duration instance. </para>
		/// </summary>
		/// <typeparam name="Out_">Type to output this stopwatch's current segment's time as.</typeparam>
		/// <returns>The current segment's time counted within this stopwatch, measured in milliseconds if possible.</returns>
		template<class Out_ = double>
		[[nodiscard]] inline Out_ GetCurrentSegmentMilli() const noexcept
		{
			return GetCurrentSegment<Out_, ratio_milli>();
		}
		/// <summary>
		/// <para> Shorthand to get this stopwatch's current segment's time in seconds. See GetCurrentSegment for more details. </para>
		/// <para> Note that output will not be in seconds if the provided Out_ type is a non-second std::chrono::duration instance. </para>
		/// </summary>
		/// <typeparam name="Out_">Type to output this stopwatch's current segment's time as.</typeparam>
		/// <returns>The current segment's time counted within this stopwatch, measured in seconds if possible.</returns>
		template<class Out_ = double>
		[[nodiscard]] inline Out_ GetCurrentSegmentSeconds() const noexcept
		{
			return GetCurrentSegment<Out_, ratio_second>();
		}
		/// <summary>
		/// <para> Shorthand to get this stopwatch's current segment's time in minutes. See GetCurrentSegment for more details. </para>
		/// <para> Note that output will not be in minutes if the provided Out_ type is a non-minute std::chrono::duration instance. </para>
		/// </summary>
		/// <typeparam name="Out_">Type to output this stopwatch's current segment's time as.</typeparam>
		/// <returns>The current segment's time counted within this stopwatch, measured in minutes if possible.</returns>
		template<class Out_ = double>
		[[nodiscard]] inline Out_ GetCurrentSegmentMinutes() const noexcept
		{
			return GetCurrentSegment<Out_, ratio_minute>();
		}
		/// <summary>
		/// <para> Shorthand to get this stopwatch's current segment's time in hours. See GetCurrentSegment for more details. </para>
		/// <para> Note that output will not be in hours if the provided Out_ type is a non-hour std::chrono::duration instance. </para>
		/// </summary>
		/// <typeparam name="Out_">Type to output this stopwatch's current segment's time as.</typeparam>
		/// <returns>The current segment's time counted within this stopwatch, measured in hours if possible.</returns>
		template<class Out_ = double>
		[[nodiscard]] inline Out_ GetCurrentSegmentHours() const noexcept
		{
			return GetCurrentSegment<Out_, ratio_hour>();
		}

	private:
		timer_type timer;
		duration_type current_time;
		bool is_active;

		template<class Out_, class OutRatio_>
		[[nodiscard]] static inline Out_ _convert_to_output(const duration_type& duration_) noexcept
		{
			if constexpr (EmuCore::TMP::is_duration_v<Out_>)
			{
				return std::chrono::duration_cast<Out_>(duration_);
			}
			else if constexpr (std::is_integral_v<Out_>)
			{
				const count_type count_ = _convert_to_output<count_type, OutRatio_>(duration_);
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
				using out_duration_type = std::chrono::duration<Out_, OutRatio_>;
				return std::chrono::duration_cast<out_duration_type>(duration_).count();
			}
		}
	};
}

#endif
