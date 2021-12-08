#ifndef EMU_CORE_TIME_TMP_H_INC_
#define EMU_CORE_TIME_TMP_H_INC_ 1

#include <chrono>
#include <type_traits>
#include "TypeComparators.h"
#include "TypeConvertors.h"

namespace EmuCore::TMP
{
	/// <summary> Ratio alias used to represent a picosecond, relative to seconds. </summary>
	using ratio_pico = std::pico;
	/// <summary> Ratio alias used to represent a nanosecond, relative to seconds. </summary>
	using ratio_nano = std::nano;
	/// <summary> Ratio alias used to represent a microsecond, relative to seconds. </summary>
	using ratio_micro = std::micro;
	/// <summary> Ratio alias used to represent a millisecond, relative to seconds. </summary>
	using ratio_milli = std::milli;
	/// <summary> Ratio alias used to represent a second, relative to seconds. </summary>
	using ratio_second = std::ratio<1, 1>;
	/// <summary> Ratio alias used to represent a minute, relative to seconds. </summary>
	using ratio_minute = std::ratio<60, 1>;
	/// <summary> Ratio alias used to represent an hour, relative to seconds. </summary>
	using ratio_hour = std::ratio<60 * 60, 1>;
	/// <summary> Ratio alias used to represent a day, relative to seconds. </summary>
	using ratio_day = std::ratio<60 * 60 * 24, 1>;
	/// <summary> Ratio alias used to represent a week, relative to seconds. </summary>
	using ratio_week = std::ratio<60 * 60 * 24 * 7, 1>;

	template<class T_>
	struct is_duration
	{
		static constexpr bool value = std::conditional_t
		<
			std::is_same_v<T_, EmuCore::TMP::remove_ref_cv_t<T_>>,
			std::false_type,
			is_duration<EmuCore::TMP::remove_ref_cv_t<T_>>
		>::value;
	};
	template<class Rep_, class Period_>
	struct is_duration<std::chrono::duration<Rep_, Period_>>
	{
		static constexpr bool value = true;
	};
	template<class T_>
	static constexpr bool is_duration_v = is_duration<T_>::value;
}

#endif
