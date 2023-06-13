#ifndef EMU_CORE_STD_FEATURE_CHECKS_H_INC_
#define EMU_CORE_STD_FEATURE_CHECKS_H_INC_ 1

#include <type_traits>

namespace EmuCore::TMP
{
	/// <summary>
	/// <para> Boolean indicating if the current C++ Standard supports concepts. </para>
	/// </summary>
	[[nodiscard]] constexpr inline bool feature_concepts()
	{
#ifdef __cpp_concepts
		return true;
#else
		return false;
#endif
	}

	/// <summary>
	/// <para> Boolean indicating if the current C++ Standard supports constexpr dynamic memory allocation (such as constexpr std::string). </para>
	/// </summary>
	[[nodiscard]] constexpr inline bool feature_constexpr_dynamic_memory()
	{
#ifdef __cpp_constexpr_dynamic_alloc
		return true;
#else
		return false;
#endif
	}
}

#endif
