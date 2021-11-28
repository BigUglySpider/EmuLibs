#ifndef EMU_MATH_NOISE_GEN_FUNCTOR_2D_H_INC_
#define EMU_MATH_NOISE_GEN_FUNCTOR_2D_H_INC_ 1

#include "_common_noise_gen_functor_includes.h"

namespace EmuMath::Functors
{
	template<EmuMath::NoiseType NoiseType_, typename FP_ = float>
	struct make_noise_2d
	{
		static_assert(EmuMath::Validity::AssertValidNoiseType<NoiseType_>(), "Invalid NoiseType_ argument provided to EmuMath::Functors::make_noise_2d.");
		static_assert(std::is_floating_point_v<FP_>, "Invalid FP_ type argument provided to EmuMath::Functors::make_noise_2d; the type must be a floating point.");
		constexpr make_noise_2d()
		{
			static_assert(false, "Attempted to construct a make_noise_2d instance for a NoiseType that has not been implemented.");
		}
	};

	/// <summary> Functor to produce 2-dimensional value noise. Produced noise is in the range 0:1. </summary>
	template<typename FP_>
	struct make_noise_2d<EmuMath::NoiseType::VALUE, FP_>
	{
		static_assert(std::is_floating_point_v<FP_>, "Invalid FP_ type argument provided to EmuMath::Functors::make_noise_2d; the type must be a floating point.");
		using value_type = FP_;

		EmuCore::do_floor<value_type> floor_;
		constexpr make_noise_2d() : floor_()
		{
		}
		inline value_type operator()(EmuMath::Vector<2, value_type> point_, value_type freq_, const EmuMath::NoisePermutations& permutations_) const
		{
			EmuMath::NoisePermutationValue mask_ = permutations_.MaxValue();
			point_ *= freq_;

			EmuMath::NoisePermutationValue ix = static_cast<EmuMath::NoisePermutationValue>(floor_(point_.at<0>())) & mask_;
			EmuMath::NoisePermutationValue iy = static_cast<EmuMath::NoisePermutationValue>(floor_(point_.at<1>())) & mask_;

			return permutations_[(static_cast<std::size_t>(permutations_[ix]) + iy) & mask_] * (value_type(1) / mask_);
		}
		template<std::size_t Size_, typename T_, typename OnlyNonV2f = std::enable_if_t<Size_ != 2 || !std::is_same_v<value_type, T_>>>
		inline value_type operator()(const EmuMath::Vector<Size_, T_>& point_, value_type freq_, const EmuMath::NoisePermutations& permutations_) const
		{
			return operator()(EmuMath::Vector<2, value_type>(point_), freq_, permutations_);
		}
	};

	/// <summary> Functor to produce 2-dimensional smooth value noise. Produced noise is in the range 0:1. </summary>
	template<typename FP_>
	struct make_noise_2d<EmuMath::NoiseType::VALUE_SMOOTH, FP_>
	{
		static_assert(std::is_floating_point_v<FP_>, "Invalid FP_ type argument provided to EmuMath::Functors::make_noise_2d; the type must be a floating point.");
		using value_type = FP_;

		EmuCore::do_lerp<value_type, value_type, value_type> lerp_;
		EmuCore::do_floor<value_type> floor_;

		constexpr make_noise_2d() : lerp_(), floor_()
		{
		}
		[[nodiscard]] inline value_type operator()(EmuMath::Vector<2, value_type> point_, value_type freq_, const EmuMath::NoisePermutations& permutations_) const
		{
			EmuMath::NoisePermutationValue mask_ = permutations_.MaxValue();
			point_ *= freq_;

			EmuMath::NoisePermutationValue ix_0_ = static_cast<EmuMath::NoisePermutationValue>(floor_(point_.at<0>()));
			EmuMath::NoisePermutationValue iy_0_ = static_cast<EmuMath::NoisePermutationValue>(floor_(point_.at<1>()));

			value_type tx = point_.at<0>() - ix_0_;
			value_type ty = point_.at<1>() - iy_0_;
			ix_0_ &= mask_;
			iy_0_ &= mask_;
			EmuMath::NoisePermutationValue ix_1_ = (ix_0_ + 1) & mask_;
			EmuMath::NoisePermutationValue iy_1_ = (iy_0_ + 1) & mask_;

			// Prepare permutations for interpolation
			EmuMath::NoisePermutationValue perm_0_ = permutations_[ix_0_];
			EmuMath::NoisePermutationValue perm_1_ = permutations_[ix_1_];
			
			value_type perm_00_ = static_cast<value_type>(permutations_[(perm_0_ + iy_0_) & mask_]);
			value_type perm_01_ = static_cast<value_type>(permutations_[(perm_0_ + iy_1_) & mask_]);
			value_type perm_10_ = static_cast<value_type>(permutations_[(perm_1_ + iy_0_) & mask_]);
			value_type perm_11_ = static_cast<value_type>(permutations_[(perm_1_ + iy_1_) & mask_]);

			tx = EmuMath::Functors::_underlying_noise_gen::SmoothT(tx);
			ty = EmuMath::Functors::_underlying_noise_gen::SmoothT(ty);

			return lerp_
			(
				lerp_(perm_00_, perm_10_, tx),
				lerp_(perm_01_, perm_11_, tx),
				ty
			) * (value_type(1) / mask_);
		}
		template<std::size_t Size_, typename T_, typename OnlyNonV2f = std::enable_if_t<Size_ != 2 || !std::is_same_v<value_type, T_>>>
		[[nodiscard]] inline value_type operator()(const EmuMath::Vector<Size_, T_>& point_, value_type freq_, const EmuMath::NoisePermutations& permutations_) const
		{
			return operator()(EmuMath::Vector<2, value_type>(point_), freq_, permutations_);
		}
	};

	/// <summary> Functor to produce 2-dimensional smooth perlin noise. Produced noise targets the range -(sqrt(2)/2):(sqrt(2)/2). </summary>
	template<typename FP_>
	struct make_noise_2d<EmuMath::NoiseType::PERLIN, FP_>
	{
		static_assert(std::is_floating_point_v<FP_>, "Invalid FP_ type argument provided to EmuMath::Functors::make_noise_2d; the type must be a floating point.");
		using value_type = FP_;
		using gradients = EmuMath::Functors::_underlying_noise_gen::perlin_gradients<2, FP_>;
		using gradient_type = typename gradients::gradient_type;

		EmuCore::do_lerp<value_type, value_type, value_type> lerp_;
		EmuCore::do_floor<value_type> floor_;
		constexpr make_noise_2d() : lerp_(), floor_()
		{
		}
		[[nodiscard]] inline value_type operator()(EmuMath::Vector<2, value_type> point_, value_type freq_, const EmuMath::NoisePermutations& permutations_) const
		{
			EmuMath::NoisePermutationValue mask_ = permutations_.MaxValue();
			point_ *= freq_;
			EmuMath::NoisePermutationValue ix0 = static_cast<EmuMath::NoisePermutationValue>(floor_(point_.x));
			EmuMath::NoisePermutationValue iy0 = static_cast<EmuMath::NoisePermutationValue>(floor_(point_.y));
			value_type tx0 = point_.x - ix0;
			value_type ty0 = point_.y - iy0;
			value_type tx1 = tx0 - value_type(1);
			value_type ty1 = ty0 - value_type(1);
			ix0 &= mask_;
			iy0 &= mask_;
			EmuMath::NoisePermutationValue ix1 = (ix0 + 1) & mask_;
			EmuMath::NoisePermutationValue iy1 = (iy0 + 1) & mask_;
			
			// Forced store as size_t so we can handle width changes if EmuMath::NoisePermutationValue is not size_t width
			std::size_t h0 = static_cast<std::size_t>(permutations_[ix0]);
			std::size_t h1 = static_cast<std::size_t>(permutations_[ix1]);
			gradient_type g00 = gradients::values[permutations_[(h0 + iy0) & mask_] & gradients::mask];
			gradient_type g10 = gradients::values[permutations_[(h1 + iy0) & mask_] & gradients::mask];
			gradient_type g01 = gradients::values[permutations_[(h0 + iy1) & mask_] & gradients::mask];
			gradient_type g11 = gradients::values[permutations_[(h1 + iy1) & mask_] & gradients::mask];

			value_type v00 = EmuMath::Functors::_underlying_noise_gen::DotWithScalar(g00, tx0, ty0);
			value_type v10 = EmuMath::Functors::_underlying_noise_gen::DotWithScalar(g10, tx1, ty0);
			value_type v01 = EmuMath::Functors::_underlying_noise_gen::DotWithScalar(g01, tx0, ty1);
			value_type v11 = EmuMath::Functors::_underlying_noise_gen::DotWithScalar(g11, tx1, ty1);
			
			value_type tx = EmuMath::Functors::_underlying_noise_gen::SmoothT(tx0);
			value_type ty = EmuMath::Functors::_underlying_noise_gen::SmoothT(ty0);
			return lerp_(lerp_(v00, v10, tx), lerp_(v01, v11, tx), ty);
		}
		template<std::size_t Size_, typename T_, typename OnlyNonV2f = std::enable_if_t<Size_ != 2 || !std::is_same_v<value_type, T_>>>
		[[nodiscard]] inline value_type operator()(const EmuMath::Vector<Size_, T_>& point_, value_type freq_, const EmuMath::NoisePermutations& permutations_) const
		{
			return operator()(EmuMath::Vector<2, value_type>(point_), freq_, permutations_);
		}
	};
}

#endif
