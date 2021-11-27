#ifndef EMU_MATH_FAST_NOISE_GEN_FUNCTOR_2D_H_INC_
#define EMU_MATH_FAST_NOISE_GEN_FUNCTOR_2D_H_INC_ 1

#include "_common_fast_noise_gen_functors_includes.h"
#include "../../../../EmuSIMD/SIMDHelpers.h"

namespace EmuMath::Validity
{
	template<class Reg_>
	[[nodiscard]] static constexpr inline bool _assert_fast_noise_2d_valid_register()
	{
		if constexpr (std::is_same_v<__m128, Reg_>)
		{
			return true;
		}
		else
		{
			static_assert(false, "Provided an unsupported register for fast_noise_2d. There is only support for the following floating-point SIMD registers: __m128.");
			return false;
		}
	}
}

namespace EmuMath::Functors
{
	template<EmuMath::NoiseType NoiseType_, class Register_ = __m128>
	struct make_fast_noise_2d
	{
		static_assert(EmuMath::Validity::AssertValidNoiseType<NoiseType_>(), "Invalid NoiseType_ argument provided to EmuMath::Functors::make_fast_noise_2d.");
		static_assert(EmuMath::Validity::_assert_fast_noise_2d_valid_register<Register_>(), "Invalid Register_ type argument provided to EmuMath::Functors::make_fast_noise_2d.");
		constexpr make_fast_noise_2d()
		{
			static_assert(false, "Attempted to construct a make_fast_noise_2d instance for a NoiseType that has not been implemented.");
		}
	};

	template<>
	struct make_fast_noise_2d<EmuMath::NoiseType::VALUE, __m128>
	{
		inline make_fast_noise_2d()
		{
		}

		[[nodiscard]] inline __m128 operator()
		(
			__m128 points_x_,
			__m128 points_y_,
			__m128 points_z_,
			__m128 freq_,
			__m128i permutations_mask_128_,
			const EmuMath::NoisePermutations& permutations_
		)
		{
			points_x_ = EmuSIMD::floor(EmuSIMD::mul_all(points_x_, freq_));
			points_y_ = EmuSIMD::floor(EmuSIMD::mul_all(points_y_, freq_));

			__m128i ix_128_ = EmuSIMD::bitwise_and(_mm_cvtps_epi32(points_x_), permutations_mask_128_);
			__m128i iy_128_ = EmuSIMD::bitwise_and(_mm_cvtps_epi32(points_y_), permutations_mask_128_);
			int ix_[4];
			int iy_[4];
			EmuSIMD::store(iy_128_, iy_);
			EmuSIMD::store(ix_128_, ix_);
			float perms_[4];
			std::size_t mask_ = static_cast<std::size_t>(permutations_.MaxValue());

			for (std::size_t i = 0; i < 4; ++i)
			{
				perms_[i] = static_cast<float>(permutations_[(static_cast<std::size_t>(permutations_[ix_[i]]) + iy_[i]) & mask_]);
			}
			return EmuSIMD::div(EmuSIMD::load<__m128>(perms_), _mm_cvtepi32_ps(permutations_mask_128_));
		}
	};
}

#endif
