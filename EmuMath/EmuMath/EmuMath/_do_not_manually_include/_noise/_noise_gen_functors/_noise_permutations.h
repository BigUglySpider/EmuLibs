#ifndef EMU_MATH_NOISE_PERMUTATIONS_H_INC_
#define EMU_MATH_NOISE_PERMUTATIONS_H_INC_ 1

#include "../../../Random.h"

namespace EmuMath
{
	using NoisePermutationValue = std::size_t;
	/// <summary> Integer sequence used as noise permutations for default-defined EmuMath noise generation functors. </summary>
	using NoisePermutations = EmuMath::ShuffledIntSequence<NoisePermutationValue>;
}

#endif
