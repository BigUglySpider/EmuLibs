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

	template<>
	struct make_fast_noise_2d<EmuMath::NoiseType::VALUE_SMOOTH, __m128>
	{
		inline make_fast_noise_2d() : smooth_t()
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
			points_x_ = EmuSIMD::mul_all(points_x_, freq_);
			points_y_ = EmuSIMD::mul_all(points_y_, freq_);

			// Get weightings and start of indices
			__m128 tx_ = EmuSIMD::floor(points_x_);
			__m128i ix_0_128_ = EmuSIMD::bitwise_and(_mm_cvtps_epi32(tx_), permutations_mask_128_);
			tx_ = smooth_t(EmuSIMD::sub(points_x_, tx_));

			__m128 ty_ = EmuSIMD::floor(points_y_);
			__m128i iy_0_128_ = EmuSIMD::bitwise_and(_mm_cvtps_epi32(ty_), permutations_mask_128_);
			ty_ = smooth_t(EmuSIMD::sub(points_y_, ty_));

			// Finish indices
			__m128i one_128i_ = EmuSIMD::set1<__m128i, 32>(1);
			__m128i ix_1_128_ = EmuSIMD::bitwise_and(EmuSIMD::add<32>(ix_0_128_, one_128i_), permutations_mask_128_);
			__m128i iy_1_128_ = EmuSIMD::bitwise_and(EmuSIMD::add<32>(iy_0_128_, one_128i_), permutations_mask_128_);

			int ix_0_[4];
			int ix_1_[4];
			int iy_0_[4];
			int iy_1_[4];
			EmuSIMD::store(ix_0_128_, ix_0_);
			EmuSIMD::store(ix_1_128_, ix_1_);
			EmuSIMD::store(iy_0_128_, iy_0_);
			EmuSIMD::store(iy_1_128_, iy_1_);

			float perms_00_[4];
			float perms_01_[4];
			float perms_10_[4];
			float perms_11_[4];
			std::size_t mask_ = static_cast<std::size_t>(permutations_.MaxValue());
			for (std::size_t i = 0; i < 4; ++i)
			{
				std::size_t perm_0_ = static_cast<std::size_t>(permutations_[ix_0_[i]]);
				std::size_t perm_1_ = static_cast<std::size_t>(permutations_[ix_1_[i]]);

				perms_00_[i] = static_cast<float>(permutations_[(perm_0_ + iy_0_[i]) & mask_]);
				perms_01_[i] = static_cast<float>(permutations_[(perm_0_ + iy_1_[i]) & mask_]);
				perms_10_[i] = static_cast<float>(permutations_[(perm_1_ + iy_0_[i]) & mask_]);
				perms_11_[i] = static_cast<float>(permutations_[(perm_1_ + iy_1_[i]) & mask_]);
			}

			__m128 lerp_0_ = EmuSIMD::fused_lerp(EmuSIMD::load<__m128>(perms_00_), EmuSIMD::load<__m128>(perms_10_), tx_);
			__m128 lerp_1_ = EmuSIMD::fused_lerp(EmuSIMD::load<__m128>(perms_01_), EmuSIMD::load<__m128>(perms_11_), tx_);
			return EmuSIMD::div(EmuSIMD::fused_lerp(lerp_0_, lerp_1_, ty_), _mm_cvtepi32_ps(permutations_mask_128_));
		}

		EmuMath::Functors::_underlying_noise_gen::_fast_smooth_t<__m128> smooth_t;
	};
}

#endif
