#ifndef EMU_MATH_QUATERNION_TMP_H_INC_
#define EMU_MATH_QUATERNION_TMP_H_INC_ 1

#include "../../__common/_common_math_tmp.h"
#include "../../../Vector.h"

namespace EmuMath
{
	template<typename T_>
	struct Quaternion;
}

namespace EmuMath::TMP
{
	template<typename T_>
	struct is_emu_quaternion<EmuMath::Quaternion<T_>>
	{
		static constexpr bool value = true;
	};
}

#endif
