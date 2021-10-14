#ifndef EMU_MATH_NOISE_GEN_FUNCTOR_1D_H_INC_
#define EMU_MATH_NOISE_GEN_FUNCTOR_1D_H_INC_ 1

#include "_common_noise_gen_functor_includes.h"

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
		inline float operator()(float point_, float freq_, const EmuMath::ShuffledIntSequence<std::int32_t>& permutations_) const
		{
			std::int32_t mask_ = permutations_.MaxValue();
			point_ *= freq_;
			std::int32_t i = static_cast<std::int32_t>(floorf(point_));
			i &= mask_;

			return permutations_[i] * (1.0f / mask_);
		}
	};

	template<>
	struct make_noise_1d<EmuMath::NoiseType::VALUE_SMOOTH>
	{
		constexpr make_noise_1d()
		{
		}
		inline float operator()(float point_, float freq_, const EmuMath::ShuffledIntSequence<std::int32_t>& permutations_) const
		{
			std::int32_t mask_ = permutations_.MaxValue();
			point_ *= freq_;

			std::int32_t i0 = static_cast<std::int32_t>(floorf(point_));
			float t_ = EmuMath::Functors::_underlying_noise_gen::SmoothT(point_ - i0);
			i0 &= mask_;
			std::int32_t i1 = i0 + 1;

			std::int32_t perm_0_ = permutations_[i0];
			std::int32_t perm_1_ = permutations_[i1];

			float a_ = static_cast<float>(perm_0_);
			float b_ = static_cast<float>(perm_1_) - a_;
			return a_ + b_ * t_;

		}
	};

	template<>
	struct make_noise_1d<EmuMath::NoiseType::PERLIN>
	{
		static constexpr std::size_t _num_gradients = 2;
		static constexpr float _gradients[_num_gradients] = { 1.0f, -1.0f };
		static constexpr std::int32_t _gradient_mask = 1;

		constexpr make_noise_1d()
		{
		}
		inline float operator()(float point_, float freq_, const EmuMath::ShuffledIntSequence<std::int32_t>& permutations_) const
		{
			std::int32_t mask_ = permutations_.MaxValue();
			point_ *= freq_;
			std::int32_t i0 = static_cast<std::int32_t>(floorf(point_));
			float t0_ = point_ - static_cast<float>(i0);
			float t1_ = t0_ - 1.0f;
			i0 &= mask_;
			std::int32_t i1 = i0 + 1;

			float gradient_0_ = _gradients[permutations_[i0] * _gradient_mask];
			float gradient_1_ = _gradients[permutations_[i1] * _gradient_mask];

			float val_0_ = gradient_0_ * t0_;
			float val_1_ = gradient_1_ * t1_;

			float a_ = val_0_;
			float b_ = val_1_ - val_0_;
			return a_ + b_ * t0_;
		}
	};

	template<>
	struct make_noise_1d<EmuMath::NoiseType::PERLIN_SMOOTH>
	{
		static constexpr std::size_t _num_gradients = 2;
		static constexpr float _gradients[_num_gradients] = { 1.0f, -1.0f };
		static constexpr std::int32_t _gradient_mask = 1;

		constexpr make_noise_1d()
		{
		}
		inline float operator()(float point_, float freq_, const EmuMath::ShuffledIntSequence<std::int32_t>& permutations_) const
		{
			std::int32_t mask_ = permutations_.MaxValue();
			point_ *= freq_;
			std::int32_t i0 = static_cast<std::int32_t>(floorf(point_));
			float t0_ = point_ - static_cast<float>(i0);
			float t1_ = t0_ - 1.0f;
			float t_ = EmuMath::Functors::_underlying_noise_gen::SmoothT(t0_);
			i0 &= mask_;
			std::int32_t i1 = i0 + 1;

			float gradient_0_ = _gradients[permutations_[i0] & _gradient_mask];
			float gradient_1_ = _gradients[permutations_[i1] & _gradient_mask];

			float val_0_ = gradient_0_ * t0_;
			float val_1_ = gradient_1_ * t1_;

			float a_ = val_0_;
			float b_ = val_1_ - val_0_;
			return a_ + b_ * t_;
		}
	};
}

#endif
