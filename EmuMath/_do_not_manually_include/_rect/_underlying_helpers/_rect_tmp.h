#ifndef EMU_MATH_RECT_TMP_H_IN_
#define EMU_MATH_RECT_TMP_H_IN_ 1

#include "../../__common/_common_math_tmp.h"
#include "../../../Vector.h"

namespace EmuMath
{
	template<typename T_>
	struct Rect;
}

namespace EmuMath::TMP
{
	template<typename T_>
	struct is_emu_rect<EmuMath::Rect<T_>>
	{
		static constexpr bool value = true;
	};
}

#endif
