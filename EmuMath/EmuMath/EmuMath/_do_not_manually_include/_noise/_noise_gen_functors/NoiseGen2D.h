#ifndef EMU_MATH_NOISE_GEN_FUNCTOR_2D_H_INC_
#define EMU_MATH_NOISE_GEN_FUNCTOR_2D_H_INC_ 1

#include "_common_noise_gen_functor_includes.h"

namespace EmuMath::Functors
{
	template<EmuMath::NoiseType NoiseType_>
	struct make_noise_2d
	{
		static_assert(EmuMath::Validity::AssertValidNoiseType<NoiseType_>(), "Invalid NoiseType_ argument provided to EmuMath::Functors::make_noise_2d.");
		constexpr make_noise_2d()
		{
			static_assert(false, "Attempted to construct a make_noise_2d instance for a NoiseType that has not been implemented.");
		}
	};

	/// <summary> Functor to produce 2-dimensional value noise. Produced noise is in the range 0:1. </summary>
	template<>
	struct make_noise_2d<EmuMath::NoiseType::VALUE>
	{
		constexpr make_noise_2d()
		{
		}
		inline float operator()(EmuMath::Vector<2, float> point_, float freq_, const EmuMath::NoisePermutations& permutations_) const
		{
			std::int32_t mask_ = permutations_.MaxValue();
			point_ *= freq_;

			std::int32_t ix = static_cast<std::int32_t>(floorf(point_.at<0>())) & mask_;
			std::int32_t iy = static_cast<std::int32_t>(floorf(point_.at<1>())) & mask_;

			return permutations_[static_cast<std::size_t>(permutations_[ix] + iy) & mask_] * (1.0f / mask_);
		}
		template<std::size_t Size_, typename T_, typename OnlyNonV2f = std::enable_if_t<Size_ != 2 || !std::is_same_v<float, T_>>>
		inline float operator()(const EmuMath::Vector<Size_, T_>& point_, float freq_, const EmuMath::NoisePermutations& permutations_) const
		{
			return operator()(EmuMath::Vector<2, float>(point_), freq_, permutations_);
		}
	};

	/// <summary> Functor to produce 2-dimensional smooth value noise. Produced noise is in the range 0:1. </summary>
	template<>
	struct make_noise_2d<EmuMath::NoiseType::VALUE_SMOOTH>
	{
		EmuCore::do_lerp<float, float, float> lerp_;

		constexpr make_noise_2d() : lerp_()
		{
		}
		inline float operator()(EmuMath::Vector<2, float> point_, float freq_, const EmuMath::NoisePermutations& permutations_) const
		{
			std::int32_t mask_ = permutations_.MaxValue();
			point_ *= freq_;

			std::int32_t ix_0_ = static_cast<std::int32_t>(floorf(point_.at<0>()));
			std::int32_t iy_0_ = static_cast<std::int32_t>(floorf(point_.at<1>()));

			float tx = point_.at<0>() - ix_0_;
			float ty = point_.at<1>() - iy_0_;
			ix_0_ &= mask_;
			iy_0_ &= mask_;
			std::int32_t ix_1_ = (ix_0_ + 1) & mask_;
			std::int32_t iy_1_ = (iy_0_ + 1) & mask_;

			// Prepare permutations for interpolation
			std::size_t perm_0_ = static_cast<std::size_t>(permutations_[ix_0_]);
			std::size_t perm_1_ = static_cast<std::size_t>(permutations_[ix_1_]);
			
			float perm_00_ = static_cast<float>(permutations_[(perm_0_ + iy_0_) & mask_]);
			float perm_01_ = static_cast<float>(permutations_[(perm_0_ + iy_1_) & mask_]);
			float perm_10_ = static_cast<float>(permutations_[(perm_1_ + iy_0_) & mask_]);
			float perm_11_ = static_cast<float>(permutations_[(perm_1_ + iy_1_) & mask_]);

			tx = EmuMath::Functors::_underlying_noise_gen::SmoothT(tx);
			ty = EmuMath::Functors::_underlying_noise_gen::SmoothT(ty);

			return lerp_
			(
				lerp_(perm_00_, perm_10_, tx),
				lerp_(perm_01_, perm_11_, tx),
				ty
			) * (1.0f / mask_);
		}
		template<std::size_t Size_, typename T_, typename OnlyNonV2f = std::enable_if_t<Size_ != 2 || !std::is_same_v<float, T_>>>
		inline float operator()(const EmuMath::Vector<Size_, T_>& point_, float freq_, const EmuMath::NoisePermutations& permutations_) const
		{
			return operator()(EmuMath::Vector<2, float>(point_), freq_, permutations_);
		}
	};

	/// <summary> Functor to produce 2-dimensional smooth perlin noise. Produced noise targets the range -(sqrt(2)/2):(sqrt(2)/2). </summary>
	template<>
	struct make_noise_2d<EmuMath::NoiseType::PERLIN>
	{
		static constexpr std::size_t _num_gradients = 8;
		static constexpr EmuMath::Vector<2, float> _gradients[_num_gradients] =
		{
			EmuMath::Vector<2, float>(1.0f, 0.0f),
			EmuMath::Vector<2, float>(-1.0f, 0.0f),
			EmuMath::Vector<2, float>(0.0f, 1.0f),
			EmuMath::Vector<2, float>(0.0f,-1.0f),
			EmuMath::Vector<2, float>(1.0f, 1.0f).NormaliseConstexpr(),
			EmuMath::Vector<2, float>(-1.0f, 1.0f).NormaliseConstexpr(),
			EmuMath::Vector<2, float>(1.0f,-1.0f).NormaliseConstexpr(),
			EmuMath::Vector<2, float>(-1.0f,-1.0f).NormaliseConstexpr()
		};
		static constexpr std::size_t _gradient_mask = 7;

		EmuCore::do_lerp<float, float, float> lerp_;
		constexpr make_noise_2d() : lerp_()
		{
		}
		inline float operator()(EmuMath::Vector<2, float> point_, float freq_, const EmuMath::NoisePermutations& permutations_) const
		{
			std::int32_t mask_ = permutations_.MaxValue();
			point_ *= freq_;
			std::int32_t ix0 = static_cast<int>(floorf(point_.x));
			std::int32_t iy0 = static_cast<int>(floorf(point_.y));
			float tx0 = point_.x - ix0;
			float ty0 = point_.y - iy0;
			float tx1 = tx0 - 1.0f;
			float ty1 = ty0 - 1.0f;
			ix0 &= mask_;
			iy0 &= mask_;
			std::int32_t ix1 = (ix0 + 1) & mask_;
			std::int32_t iy1 = (iy0 + 1) & mask_;
			
			std::size_t h0 = static_cast<std::size_t>(permutations_[static_cast<std::size_t>(ix0)]);
			std::size_t h1 = static_cast<std::size_t>(permutations_[static_cast<std::size_t>(ix1)]);
			EmuMath::Vector<2, float> g00 = _gradients[permutations_[(h0 + iy0) & mask_] & _gradient_mask];
			EmuMath::Vector<2, float> g10 = _gradients[permutations_[(h1 + iy0) & mask_] & _gradient_mask];
			EmuMath::Vector<2, float> g01 = _gradients[permutations_[(h0 + iy1) & mask_] & _gradient_mask];
			EmuMath::Vector<2, float> g11 = _gradients[permutations_[(h1 + iy1) & mask_] & _gradient_mask];

			float v00 = EmuMath::Functors::_underlying_noise_gen::DotWithScalar(g00, tx0, ty0);
			float v10 = EmuMath::Functors::_underlying_noise_gen::DotWithScalar(g10, tx1, ty0);
			float v01 = EmuMath::Functors::_underlying_noise_gen::DotWithScalar(g01, tx0, ty1);
			float v11 = EmuMath::Functors::_underlying_noise_gen::DotWithScalar(g11, tx1, ty1);
			
			float tx = EmuMath::Functors::_underlying_noise_gen::SmoothT(tx0);
			float ty = EmuMath::Functors::_underlying_noise_gen::SmoothT(ty0);
			return lerp_(lerp_(v00, v10, tx), lerp_(v01, v11, tx), ty);
		}
		template<std::size_t Size_, typename T_, typename OnlyNonV2f = std::enable_if_t<Size_ != 2 || !std::is_same_v<float, T_>>>
		inline float operator()(const EmuMath::Vector<Size_, T_>& point_, float freq_, const EmuMath::NoisePermutations& permutations_) const
		{
			return operator()(EmuMath::Vector<2, float>(point_), freq_, permutations_);
		}
	};
}

#endif
