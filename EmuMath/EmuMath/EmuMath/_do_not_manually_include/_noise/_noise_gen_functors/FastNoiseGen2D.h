#ifndef EMU_MATH_FAST_NOISE_GEN_FUNCTOR_2D_H_INC_
#define EMU_MATH_FAST_NOISE_GEN_FUNCTOR_2D_H_INC_ 1

#include "_common_fast_noise_gen_functors_includes.h"
#include "../../../../EmuSIMD/SIMDHelpers.h"
#include "../../../../EmuCore/TMPHelpers/Values.h"

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
			static_assert(EmuCore::TMP::get_false<Reg_>(), "Provided an unsupported register for fast_noise_2d. There is only support for the following floating-point SIMD registers: __m128.");
			return false;
		}
	}
}

namespace EmuMath::Functors
{
	template<EmuMath::NoiseType NoiseType_, class Register_ = __m128>
	struct make_fast_noise_2d
	{
		static_assert(EmuMath::Validity::assert_valid_noise_type<NoiseType_>(), "Invalid NoiseType_ argument provided to EmuMath::Functors::make_fast_noise_2d.");
		static_assert(EmuMath::Validity::_assert_fast_noise_2d_valid_register<Register_>(), "Invalid Register_ type argument provided to EmuMath::Functors::make_fast_noise_2d.");
		constexpr make_fast_noise_2d()
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to construct a make_fast_noise_2d instance for a NoiseType that has not been implemented.");
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
			std::size_t mask_ = static_cast<std::size_t>(permutations_.HighestStoredValue());

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
			std::size_t mask_ = static_cast<std::size_t>(permutations_.HighestStoredValue());
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

	template<>
	struct make_fast_noise_2d<EmuMath::NoiseType::PERLIN, __m128>
	{
		using gradients = EmuMath::Functors::_underlying_noise_gen::perlin_gradients<2, __m128>;

		/// <summary> Gradients for calculation. Z index contains a duplicate of X; W index contains a duplicate of Y. </summary>
		const typename gradients::register_array _gradients_128;
		static constexpr EmuMath::Vector<2, std::size_t> _duplicate_gradient_indices = EmuMath::Vector<2, std::size_t>(0, 1);

		inline make_fast_noise_2d() : 
			smooth_t(),
			_gradients_128(gradients::init_registers<_duplicate_gradient_indices.at<0>(), _duplicate_gradient_indices.at<1>()>())
		{
		}

		[[nodiscard]] inline __m128 operator()
		(
			__m128 points_x_,
			__m128 points_y_,
			__m128 freq_,
			__m128i permutations_mask_128_,
			const EmuMath::NoisePermutations& permutations_
		)
		{
			points_x_ = EmuSIMD::mul_all(points_x_, freq_);
			points_y_ = EmuSIMD::mul_all(points_y_, freq_);

			// Start of weightings and indices
			__m128 tx_0_ = EmuSIMD::floor(points_x_);
			__m128 ty_0_ = EmuSIMD::floor(points_y_);
			__m128i ix_0_128_ = _mm_cvtps_epi32(tx_0_);
			__m128i iy_0_128_ = _mm_cvtps_epi32(ty_0_);

			// Finish off weightings
			__m128i one_128i_ = EmuSIMD::set1<__m128i>(1);
			__m128 one_128f_ = _mm_cvtepi32_ps(one_128i_);
			tx_0_ = EmuSIMD::sub(points_x_, tx_0_);
			__m128 tx_1_ = EmuSIMD::sub(tx_0_, one_128f_);
			ty_0_ = EmuSIMD::sub(points_y_, ty_0_);
			__m128 ty_1_ = EmuSIMD::sub(ty_0_, one_128f_);

			// Finish off indices
			ix_0_128_ = EmuSIMD::bitwise_and(ix_0_128_, permutations_mask_128_);
			__m128i ix_1_128_ = EmuSIMD::bitwise_and(EmuSIMD::add<32>(ix_0_128_, one_128i_), permutations_mask_128_);
			iy_0_128_ = EmuSIMD::bitwise_and(iy_0_128_, permutations_mask_128_);
			__m128i iy_1_128_ = EmuSIMD::bitwise_and(EmuSIMD::add<32>(iy_0_128_, one_128i_), permutations_mask_128_);

			int ix_0_[4];
			int ix_1_[4];
			int iy_0_[4];
			int iy_1_[4];
			EmuSIMD::store(ix_0_128_, ix_0_);
			EmuSIMD::store(ix_1_128_, ix_1_);
			EmuSIMD::store(iy_0_128_, iy_0_);
			EmuSIMD::store(iy_1_128_, iy_1_);

			std::size_t perms_00_[4];
			std::size_t perms_01_[4];
			std::size_t perms_10_[4];
			std::size_t perms_11_[4];
			std::size_t perm_mask_ = permutations_.HighestStoredValue();

			for (std::size_t i = 0; i < 4; ++i)
			{
				std::size_t perm_0_ = static_cast<std::size_t>(permutations_[ix_0_[i]]);
				std::size_t perm_1_ = static_cast<std::size_t>(permutations_[ix_1_[i]]);
				perms_00_[i] = permutations_[(perm_0_ + iy_0_[i]) & perm_mask_] & gradients::mask;
				perms_01_[i] = permutations_[(perm_0_ + iy_1_[i]) & perm_mask_] & gradients::mask;
				perms_10_[i] = permutations_[(perm_1_ + iy_0_[i]) & perm_mask_] & gradients::mask;
				perms_11_[i] = permutations_[(perm_1_ + iy_1_[i]) & perm_mask_] & gradients::mask;
			}

			// 00
			__m128 gradient_0_ = _gradients_128[perms_00_[0]];
			__m128 gradient_1_ = _gradients_128[perms_00_[1]];
			__m128 gradient_2_ = _gradients_128[perms_00_[2]];
			__m128 gradient_3_ = _gradients_128[perms_00_[3]];

			// X - prepare Y to be shuffled in next segment too
			__m128 temp_0_ = EmuSIMD::shuffle<0, 1, 0, 1>(gradient_0_, gradient_1_);
			__m128 temp_1_ = EmuSIMD::shuffle<0, 1, 0, 1>(gradient_2_, gradient_3_);
			__m128 row_ = EmuSIMD::shuffle<0, 2, 0, 2>(temp_0_, temp_1_);
			__m128 vals_00_ = EmuSIMD::mul_all(row_, tx_0_);

			// Y
			row_ = EmuSIMD::shuffle<1, 3, 1, 3>(temp_0_, temp_1_);
			vals_00_ = EmuSIMD::add(vals_00_, EmuSIMD::mul_all(row_, ty_0_));

			// ABOVE COMMENTS APPLY TO SUBSEQUENT OUTPUTS
			// 01
			gradient_0_ = _gradients_128[perms_01_[0]];
			gradient_1_ = _gradients_128[perms_01_[1]];
			gradient_2_ = _gradients_128[perms_01_[2]];
			gradient_3_ = _gradients_128[perms_01_[3]];

			// X
			temp_0_ = EmuSIMD::shuffle<0, 1, 0, 1>(gradient_0_, gradient_1_);
			temp_1_ = EmuSIMD::shuffle<0, 1, 0, 1>(gradient_2_, gradient_3_);
			row_ = EmuSIMD::shuffle<0, 2, 0, 2>(temp_0_, temp_1_);
			__m128 vals_01_ = EmuSIMD::mul_all(row_, tx_0_);

			// Y
			row_ = EmuSIMD::shuffle<1, 3, 1, 3>(temp_0_, temp_1_);
			vals_01_ = EmuSIMD::add(vals_01_, EmuSIMD::mul_all(row_, ty_1_));

			// 10
			gradient_0_ = _gradients_128[perms_10_[0]];
			gradient_1_ = _gradients_128[perms_10_[1]];
			gradient_2_ = _gradients_128[perms_10_[2]];
			gradient_3_ = _gradients_128[perms_10_[3]];

			// X
			temp_0_ = EmuSIMD::shuffle<0, 1, 0, 1>(gradient_0_, gradient_1_);
			temp_1_ = EmuSIMD::shuffle<0, 1, 0, 1>(gradient_2_, gradient_3_);
			row_ = EmuSIMD::shuffle<0, 2, 0, 2>(temp_0_, temp_1_);
			__m128 vals_10_ = EmuSIMD::mul_all(row_, tx_1_);

			// Y
			row_ = EmuSIMD::shuffle<1, 3, 1, 3>(temp_0_, temp_1_);
			vals_10_ = EmuSIMD::add(vals_10_, EmuSIMD::mul_all(row_, ty_0_));

			// 11
			gradient_0_ = _gradients_128[perms_11_[0]];
			gradient_1_ = _gradients_128[perms_11_[1]];
			gradient_2_ = _gradients_128[perms_11_[2]];
			gradient_3_ = _gradients_128[perms_11_[3]];

			// X
			temp_0_ = EmuSIMD::shuffle<0, 1, 0, 1>(gradient_0_, gradient_1_);
			temp_1_ = EmuSIMD::shuffle<0, 1, 0, 1>(gradient_2_, gradient_3_);
			row_ = EmuSIMD::shuffle<0, 2, 0, 2>(temp_0_, temp_1_);
			__m128 vals_11_ = EmuSIMD::mul_all(row_, tx_1_);

			// Y
			row_ = EmuSIMD::shuffle<1, 3, 1, 3>(temp_0_, temp_1_);
			vals_11_ = EmuSIMD::add(vals_11_, EmuSIMD::mul_all(row_, ty_1_));

			// Lerp gradients
			tx_0_ = smooth_t(tx_0_);
			__m128 lerp_0_ = EmuSIMD::fused_lerp(vals_00_, vals_10_, tx_0_);
			__m128 lerp_1_ = EmuSIMD::fused_lerp(vals_01_, vals_11_, tx_0_);
			return EmuSIMD::fused_lerp(lerp_0_, lerp_1_, smooth_t(ty_0_));
		}

		EmuMath::Functors::_underlying_noise_gen::_fast_smooth_t<__m128> smooth_t;
	};
}


#endif
