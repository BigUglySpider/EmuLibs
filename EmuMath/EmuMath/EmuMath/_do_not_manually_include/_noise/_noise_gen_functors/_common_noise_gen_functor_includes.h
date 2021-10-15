#ifndef EMU_MATH_COMMON_NOISE_GEN_FUNCTOR_INCLUDES_H_INC_
#define EMU_MATH_COMMON_NOISE_GEN_FUNCTOR_INCLUDES_H_INC_ 1

#include "../_noise_info/NoiseType.h"
#include "../../../Random.h"
#include "../../../Vector.h"
#include "../../../../EmuCore/TMPHelpers/TypeComparators.h"

namespace EmuMath
{
	/// <summary> Integer sequence used as noise permutations for default-defined EmuMath noise generation functors. </summary>
	using NoisePermutations = EmuMath::ShuffledIntSequence<std::int32_t>;
}

namespace EmuMath::Functors::_underlying_noise_gen
{
	/// <summary>Function applied to t_ to smooth it for smooth noise generation algorithms defined in EmuMath. </summary>
	/// <returns>Smoothed float t_, resulting from 6(t^5) - 15(t^4) + 10(t^3) (where t^x == t to the power of x).</returns>
	inline float SmoothT(float t_)
	{
		return t_ * t_ * t_ * (t_ * (t_ * 6.0f - 15.0f) + 10.0f);
	}
}

#endif
