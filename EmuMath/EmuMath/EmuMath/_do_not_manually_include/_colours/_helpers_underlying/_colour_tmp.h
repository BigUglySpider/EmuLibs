#ifndef EMU_MATH_COLOUR_TMP_H_INC_
#define EMU_MATH_COLOUR_TMP_H_INC_ 1

#include "../../../../EmuCore/TMPHelpers/TypeConvertors.h"
#include <type_traits>

namespace EmuMath
{
	template<typename Channel_, bool ContainsAlpha_>
	struct Colour;
}

namespace EmuMath::TMP
{
	template<class T_>
	struct is_emu_colour
	{
		static constexpr bool value = std::conditional_t
		<
			// This is a recursive check to make sure that T_ does not have modifiers that may lead to false negatives
			std::is_same_v<T_, typename EmuCore::TMP::remove_ref_cv<T_>::type>,
			std::false_type,
			is_emu_colour<typename EmuCore::TMP::remove_ref_cv<T_>::type>
		>::value;
	};
	template<typename T_, bool ContainsAlpha_>
	struct is_emu_colour<EmuMath::Colour<T_, ContainsAlpha_>>
	{
		static constexpr bool value = true;
	};
	template<class T_>
	static constexpr bool is_emu_colour_v = is_emu_colour<T_>::value;
}

#endif
