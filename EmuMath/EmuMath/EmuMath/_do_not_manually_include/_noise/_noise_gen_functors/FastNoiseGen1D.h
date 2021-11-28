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

	template<>
	struct make_fast_noise_1d<EmuMath::NoiseType::VALUE, __m128>
	{
		[[nodiscard]] inline __m128 operator()
		(
			__m128 points_x_,
			__m128 freq_,
			__m128i permutations_mask_128_,
			const EmuMath::NoisePermutations& permutations_
		)
		{
			points_x_ = EmuSIMD::floor(EmuSIMD::mul_all(points_x_, freq_));
			int i_[4];
			EmuSIMD::store(EmuSIMD::bitwise_and(_mm_cvtps_epi32(points_x_), permutations_mask_128_), i_);
			__m128 perms_ = EmuSIMD::set<__m128>(permutations_[i_[3]], permutations_[i_[2]], permutations_[i_[1]], permutations_[i_[0]]);
			return EmuSIMD::div(perms_, _mm_cvtepi32_ps(permutations_mask_128_));
		}
	};

	template<>
	struct make_fast_noise_1d<EmuMath::NoiseType::VALUE_SMOOTH, __m128>
	{
		inline make_fast_noise_1d() : smooth_t()
		{
		}

		[[nodiscard]] inline __m128 operator()
		(
			__m128 points_x_,
			__m128 freq_,
			__m128i permutations_mask_128_,
			const EmuMath::NoisePermutations& permutations_
		)
		{
			points_x_ = EmuSIMD::mul_all(points_x_, freq_);
			__m128 t_ = EmuSIMD::floor(points_x_);
			__m128i i0_128_ = EmuSIMD::bitwise_and(_mm_cvtps_epi32(t_), permutations_mask_128_);
			t_ = EmuSIMD::sub(points_x_, t_);
			__m128i i1_128_ = EmuSIMD::bitwise_and(EmuSIMD::add<32>(i0_128_, EmuSIMD::set1<__m128i, 32>(1)), permutations_mask_128_);

			int i0_[4];
			int i1_[4];
			EmuSIMD::store(i0_128_, i0_);
			EmuSIMD::store(i1_128_, i1_);

			float perms_0_[4];
			float perms_1_[4];
			for (std::size_t i = 0; i < 4; ++i)
			{
				perms_0_[i] = static_cast<float>(permutations_[i0_[i]]);
				perms_1_[i] = static_cast<float>(permutations_[i1_[i]]);
			}

			__m128 lerped_ = EmuSIMD::fused_lerp(EmuSIMD::load<__m128>(perms_0_), EmuSIMD::load<__m128>(perms_1_), smooth_t(t_));
			return EmuSIMD::div(lerped_, _mm_cvtepi32_ps(permutations_mask_128_));
		}

		EmuMath::Functors::_underlying_noise_gen::_fast_smooth_t<__m128> smooth_t;
	};

	template<>
	struct make_fast_noise_1d<EmuMath::NoiseType::PERLIN, __m128>
	{
		using gradients = EmuMath::Functors::_underlying_noise_gen::perlin_gradients<1, __m128>;

		inline make_fast_noise_1d() : smooth_t()
		{
		}

		[[nodiscard]] inline __m128 operator()
		(
			__m128 points_x_,
			__m128 freq_,
			__m128i permutations_mask_128_,
			const EmuMath::NoisePermutations& permutations_
		)
		{
			// Start weightings and indices
			points_x_ = EmuSIMD::mul_all(points_x_, freq_);
			__m128 t0_ = EmuSIMD::floor(points_x_);
			__m128i i0_128_ = EmuSIMD::bitwise_and(_mm_cvtps_epi32(t0_), permutations_mask_128_);

			// Finish weightings
			t0_ = EmuSIMD::sub(points_x_, t0_);
			__m128 one_ = EmuSIMD::set1<__m128>(1.0f);
			__m128 t1_ = EmuSIMD::sub(t0_, one_);

			// Finish indices
			__m128i i1_128_ = EmuSIMD::bitwise_and(EmuSIMD::add<32>(i0_128_, _mm_cvtps_epi32(one_)), permutations_mask_128_);
			int i0_[4];
			int i1_[4];
			EmuSIMD::store(i0_128_, i0_);
			EmuSIMD::store(i1_128_, i1_);

			std::size_t perms_0_[4];
			std::size_t perms_1_[4];
			for (std::size_t i = 0; i < 4; ++i)
			{
				perms_0_[i] = permutations_[i0_[i]] & gradients::mask;
				perms_1_[i] = permutations_[i1_[i]] & gradients::mask;
			}

			__m128 gradients_0_ = gradients::init_registers(perms_0_[0], perms_0_[1], perms_0_[2], perms_0_[3]);
			__m128 gradients_1_ = gradients::init_registers(perms_1_[0], perms_1_[1], perms_1_[2], perms_1_[3]);
			gradients_0_ = EmuSIMD::mul_all(gradients_0_, t0_);
			gradients_1_ = EmuSIMD::mul_all(gradients_1_, t1_);
			
			return EmuSIMD::fused_lerp(gradients_0_, gradients_1_, smooth_t(t0_));
		}

		EmuMath::Functors::_underlying_noise_gen::_fast_smooth_t<__m128> smooth_t;
	};
}

#endif
