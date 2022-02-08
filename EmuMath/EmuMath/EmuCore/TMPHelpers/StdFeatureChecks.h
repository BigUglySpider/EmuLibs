#ifndef EMU_CORE_STD_FEATURE_CHECKS_H_INC_
#define EMU_CORE_STD_FEATURE_CHECKS_H_INC_ 1

#include <type_traits>

namespace EmuCore::TMP
{
	/// <summary>
	/// <para> Boolean indicating if the current C++ Standard supports constexpr dynamic memory allocation (such as constexpr std::string). </para>
	/// <para> Under MSVC, will always be false without the /Zc:__cplusplus switch enabled, as of 2022/02/07. </para>
	/// </summary>
	[[nodiscard]] constexpr inline bool feature_constexpr_dynamic_memory()
	{
		return __cplusplus >= 201907L;
	}
}

#endif
