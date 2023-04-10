#ifndef EMU_MATH_FAST_QUATERNION_TMP_H_INC_
#define EMU_MATH_FAST_QUATERNION_TMP_H_INC_ 1

#include "../../__common/_common_math_tmp.h"
#include "../../../../EmuCore/TMPHelpers/TypeConvertors.h"
#include "../../../../EmuSIMD/SIMDHelpers.h"
#include <functional>
#include <type_traits>

namespace EmuMath
{
	template<typename T_, std::size_t RegisterWidth_ = 128>
	struct FastQuaternion;
}

namespace EmuMath::TMP
{
	template<typename T_, std::size_t RegisterWidth_>
	struct is_emu_fast_quaternion<EmuMath::FastQuaternion<T_, RegisterWidth_>>
	{
		static constexpr bool value = true;
	};
}

#endif
