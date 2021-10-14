#ifndef EMU_MATH_COMMON_NOISE_GEN_FUNCTOR_INCLUDES_H_INC_
#define EMU_MATH_COMMON_NOISE_GEN_FUNCTOR_INCLUDES_H_INC_ 1

#include "../_noise_info/NoiseType.h"
#include "../../../Random.h"
#include "../../../../EmuCore/TMPHelpers/TypeComparators.h"

namespace EmuMath::Functors::_underlying_noise_gen
{
	inline float SmoothT(float t_)
	{
		return t_ * t_ * t_ * (t_ * (t_ * 6.0f - 15.0f) + 10.0f);
	}
}

#endif
