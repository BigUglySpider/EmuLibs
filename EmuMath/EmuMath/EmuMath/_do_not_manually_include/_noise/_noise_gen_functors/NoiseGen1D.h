#ifndef EMU_MATH_NOISE_GEN_FUNCTOR_1D_H_INC_
#define EMU_MATH_NOISE_GEN_FUNCTOR_1D_H_INC_ 1

#include "../_noise_info/NoiseType.h"
#include "../../../../EmuCore/TMPHelpers/TypeComparators.h"

namespace EmuMath::Functors
{
	template<EmuMath::NoiseType NoiseType_>
	struct make_noise_1d
	{
		static_assert(EmuMath::Validity::AssertValidNoiseType<NoiseType_>(), "Invalid NoiseType_ argument provided to EmuMath::Functors::make_noise_1d.");
	};
	template<>
	struct make_noise_1d<EmuMath::NoiseType::VALUE>
	{
		constexpr make_noise_1d()
		{
		}
		constexpr inline float operator()(float point_, float freq_) const
		{

		}
	};
}

#endif
