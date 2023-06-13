#ifndef EMU_MATH_NOISE_GEN_FUNCTOR_2D_H_INC_
#define EMU_MATH_NOISE_GEN_FUNCTOR_2D_H_INC_ 1

#include "_common_noise_gen_functor_includes.h"
#include "../../../../EmuCore/TMPHelpers/Values.h"

namespace EmuMath::Functors
{
	template<EmuMath::NoiseType NoiseType_, typename FP_ = float>
	struct make_noise_2d
	{
		static_assert(EmuMath::Validity::assert_valid_noise_type<NoiseType_>(), "Invalid NoiseType_ argument provided to EmuMath::Functors::make_noise_2d.");
		static_assert(std::is_floating_point_v<FP_>, "Invalid FP_ type argument provided to EmuMath::Functors::make_noise_2d; the type must be a floating point.");
		constexpr make_noise_2d()
		{
			static_assert(EmuCore::TMP::get_false<FP_>(), "Attempted to construct a make_noise_2d instance for a NoiseType that has not been implemented.");
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
			EmuMath::NoisePermutationValue mask_ = permutations_.HighestStoredValue();
			point_ *= freq_;

			EmuMath::NoisePermutationValue ix_ = static_cast<EmuMath::NoisePermutationValue>(floor_(point_.template at<0>())) & mask_;
			EmuMath::NoisePermutationValue iy_ = static_cast<EmuMath::NoisePermutationValue>(floor_(point_.template at<1>())) & mask_;

			return permutations_[(static_cast<std::size_t>(permutations_[ix_]) + iy_) & mask_] * (value_type(1) / mask_);
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
			EmuMath::NoisePermutationValue mask_ = permutations_.HighestStoredValue();
			point_ *= freq_;

			EmuMath::NoisePermutationValue ix_0_ = static_cast<EmuMath::NoisePermutationValue>(floor_(point_.template at<0>()));
			EmuMath::NoisePermutationValue iy_0_ = static_cast<EmuMath::NoisePermutationValue>(floor_(point_.template at<1>()));

			value_type tx = point_.template at<0>() - ix_0_;
			value_type ty = point_.template at<1>() - iy_0_;
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

			tx = EmuMath::Functors::_underlying_noise_gen::smooth_t(tx);
			ty = EmuMath::Functors::_underlying_noise_gen::smooth_t(ty);

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
			EmuMath::NoisePermutationValue mask_ = permutations_.HighestStoredValue();
			point_ *= freq_;
			EmuMath::NoisePermutationValue ix_0_ = static_cast<EmuMath::NoisePermutationValue>(floor_(point_.template at<0>()));
			EmuMath::NoisePermutationValue iy_0_ = static_cast<EmuMath::NoisePermutationValue>(floor_(point_.template at<1>()));
			value_type tx_0_ = point_.template at<0>() - ix_0_;
			value_type ty_0_ = point_.template at<1>() - iy_0_;
			value_type tx_1_ = tx_0_ - value_type(1);
			value_type ty_1_ = ty_0_ - value_type(1);
			ix_0_ &= mask_;
			iy_0_ &= mask_;
			EmuMath::NoisePermutationValue ix_1_ = (ix_0_ + 1) & mask_;
			EmuMath::NoisePermutationValue iy_1_ = (iy_0_ + 1) & mask_;
			
			// Forced store as size_t so we can handle width changes if EmuMath::NoisePermutationValue is not size_t width
			std::size_t perm_0_ = static_cast<std::size_t>(permutations_[ix_0_]);
			std::size_t perm_1_ = static_cast<std::size_t>(permutations_[ix_1_]);
			gradient_type gradient_00_ = gradients::values[permutations_[(perm_0_ + iy_0_) & mask_] & gradients::mask];
			gradient_type gradient_01_ = gradients::values[permutations_[(perm_0_ + iy_1_) & mask_] & gradients::mask];
			gradient_type gradient_10_ = gradients::values[permutations_[(perm_1_ + iy_0_) & mask_] & gradients::mask];
			gradient_type gradient_11_ = gradients::values[permutations_[(perm_1_ + iy_1_) & mask_] & gradients::mask];

			value_type val_00_ = EmuMath::Functors::_underlying_noise_gen::dot_with_scalar(gradient_00_, tx_0_, ty_0_);
			value_type val_01_ = EmuMath::Functors::_underlying_noise_gen::dot_with_scalar(gradient_01_, tx_0_, ty_1_);
			value_type val_10_ = EmuMath::Functors::_underlying_noise_gen::dot_with_scalar(gradient_10_, tx_1_, ty_0_);
			value_type val_11_ = EmuMath::Functors::_underlying_noise_gen::dot_with_scalar(gradient_11_, tx_1_, ty_1_);
			
			value_type tx_ = EmuMath::Functors::_underlying_noise_gen::smooth_t(tx_0_);
			value_type ty_ = EmuMath::Functors::_underlying_noise_gen::smooth_t(ty_0_);
			return lerp_(lerp_(val_00_, val_10_, tx_), lerp_(val_01_, val_11_, tx_), ty_);
		}
		template<std::size_t Size_, typename T_, typename OnlyNonV2f = std::enable_if_t<Size_ != 2 || !std::is_same_v<value_type, T_>>>
		[[nodiscard]] inline value_type operator()(const EmuMath::Vector<Size_, T_>& point_, value_type freq_, const EmuMath::NoisePermutations& permutations_) const
		{
			return operator()(EmuMath::Vector<2, value_type>(point_), freq_, permutations_);
		}
	};
}

#endif
