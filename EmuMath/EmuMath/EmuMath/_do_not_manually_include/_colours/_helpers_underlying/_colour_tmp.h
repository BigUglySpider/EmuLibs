#ifndef EMU_MATH_COLOUR_TMP_H_INC_
#define EMU_MATH_COLOUR_TMP_H_INC_ 1

#include "../../__common/_common_math_tmp.h"
#include "../../../../EmuCore/TMPHelpers/TypeConvertors.h"
#include <type_traits>

namespace EmuMath
{
	template<typename Channel_, bool ContainsAlpha_>
	struct Colour;
}

namespace EmuMath::TMP
{
	template<typename T_, bool ContainsAlpha_>
	struct is_emu_colour<EmuMath::Colour<T_, ContainsAlpha_>>
	{
		static constexpr bool value = true;
	};;
}

#endif
