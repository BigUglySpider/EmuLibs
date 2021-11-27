#ifndef EMU_MATH_FAST_NOISE_GEN_FUNCTOR_1D_H_INC_
#define EMU_MATH_FAST_NOISE_GEN_FUNCTOR_1D_H_INC_ 1

#include "_common_fast_noise_gen_functors_includes.h"
#include "../../../../EmuSIMD/SIMDHelpers.h"

namespace EmuMath::Validity
{
	template<class Reg_>
	[[nodiscard]] static constexpr inline bool _assert_fast_noise_1d_valid_register()
	{
		if constexpr (std::is_same_v<__m128, Reg_>)
		{
			return true;
		}
		else
		{
			static_assert(false, "Provided an unsupported register for fast_noise_1d. There is only support for the following floating-point SIMD registers: __m128.");
			return false;
		}
	}
}

namespace EmuMath::Functors
{
	template<EmuMath::NoiseType NoiseType_, class Register_ = __m128>
	struct make_fast_noise_1d
	{
		static_assert(EmuMath::Validity::AssertValidNoiseType<NoiseType_>(), "Invalid NoiseType_ argument provided to EmuMath::Functors::make_fast_noise_1d.");
		static_assert(EmuMath::Validity::_assert_fast_noise_1d_valid_register<Register_>(), "Invalid Register_ type argument provided to EmuMath::Functors::make_fast_noise_1d.");
		constexpr make_fast_noise_1d()
		{
			static_assert(false, "Attempted to construct a make_fast_noise_1d instance for a NoiseType that has not been implemented.");
		}
	};
}

#endif
