#ifndef EMU_CORE_COMMON_CONCEPTS_STD_TYPES_H_INC_
#define EMU_CORE_COMMON_CONCEPTS_STD_TYPES_H_INC_ 1

#include "../TMPHelpers/TypeComparators.h"
#include "../TMPHelpers/TypeConvertors.h"
#include <concepts>

namespace EmuCore::Concepts
{
	template<typename T_>
	concept StdTuple = EmuCore::TMP::is_tuple_v<typename EmuCore::TMP::remove_ref_cv<T_>::type>;

	template<typename T_>
	concept StdArray = EmuCore::TMP::is_std_array_v<typename EmuCore::TMP::remove_ref_cv<T_>::type>;
}

namespace EmuConcepts
{
	using namespace EmuCore::Concepts;
}

#endif
