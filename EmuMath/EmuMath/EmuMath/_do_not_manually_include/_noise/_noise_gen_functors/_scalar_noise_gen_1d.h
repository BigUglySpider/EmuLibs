#ifndef EMU_MATH_NOISE_GEN_FUNCTOR_1D_H_INC_
#define EMU_MATH_NOISE_GEN_FUNCTOR_1D_H_INC_ 1

#include "_common_noise_gen_functor_includes.h"
#include "../../../../EmuCore/TMPHelpers/Values.h"

namespace EmuMath::Functors
{
	/// <summary>
	/// <para> Noise generation functor for 1-dimensional noise. </para>
	/// <para> Valid EmuMath::NoiseType arguments have been specialised for this functor. Invalid arguments will result in an empty struct. </para>
	/// </summary>
	template<EmuMath::NoiseType NoiseType_, typename FP_ = float>
	struct make_noise_1d
	{
		static_assert(EmuMath::Validity::assert_valid_noise_type<NoiseType_>(), "Invalid NoiseType_ argument provided to EmuMath::Functors::make_noise_1d.");
		static_assert(std::is_floating_point_v<FP_>, "Invalid FP_ type argument provided to EmuMath::Functors::make_noise_1d; the type must be a floating point.");
		constexpr make_noise_1d()
		{
			static_assert(EmuCore::TMP::get_false<FP_>(), "Attempted to construct a make_noise_1d instance for a NoiseType that has not been implemented.");
		}
	};

	/// <summary> Functor to produce 1-dimensional value noise. Produced noise is in the range 0:1. </summary>
	template<typename FP_>
	struct make_noise_1d<EmuMath::NoiseType::VALUE, FP_>
	{
		static_assert(std::is_floating_point_v<FP_>, "Invalid FP_ type argument provided to EmuMath::Functors::make_noise_1d; the type must be a floating point.");
		using value_type = FP_;

		EmuCore::do_floor<value_type> floor_;
		constexpr make_noise_1d() : floor_()
		{
		}
		[[nodiscard]] inline FP_ operator()(value_type point_, value_type freq_, const EmuMath::NoisePermutations& permutations_) const
		{
			EmuMath::NoisePermutationValue mask_ = permutations_.HighestStoredValue();
			point_ *= freq_;

			EmuMath::NoisePermutationValue i_ = static_cast<EmuMath::NoisePermutationValue>(floor_(point_)) & mask_;
			return permutations_[i_] * (value_type(1) / mask_);
		}
		template<std::size_t Size_, typename T_>
		inline value_type operator()(const EmuMath::Vector<Size_, T_>& point_, value_type freq_, const EmuMath::NoisePermutations& permutations_) const
		{
			return operator()(static_cast<value_type>(point_.template at<0>()), freq_, permutations_);
		}
	};

	/// <summary> Functor to produce 1-dimensional smooth value noise. Produced noise is in the range 0:1. </summary>
	template<typename FP_>
	struct make_noise_1d<EmuMath::NoiseType::VALUE_SMOOTH, FP_>
	{
		static_assert(std::is_floating_point_v<FP_>, "Invalid FP_ type argument provided to EmuMath::Functors::make_noise_1d; the type must be a floating point.");
		using value_type = FP_;

		EmuCore::do_lerp<value_type, value_type, value_type> lerp_;
		EmuCore::do_floor<value_type> floor_;
		constexpr make_noise_1d() : lerp_(), floor_()
		{
		}
		inline value_type operator()(value_type point_, value_type freq_, const EmuMath::NoisePermutations& permutations_) const
		{
			EmuMath::NoisePermutationValue mask_ = permutations_.HighestStoredValue();
			point_ *= freq_;

			EmuMath::NoisePermutationValue i_0_ = static_cast<EmuMath::NoisePermutationValue>(floor_(point_));
			value_type t_ = EmuMath::Functors::_underlying_noise_gen::smooth_t(point_ - i_0_);
			i_0_ &= mask_;
			EmuMath::NoisePermutationValue i_1_ = (i_0_ + 1) & mask_;

			value_type perm_0_ = static_cast<value_type>(permutations_[i_0_]);
			value_type perm_1_ = static_cast<value_type>(permutations_[i_1_]);

			return lerp_(perm_0_, perm_1_, t_) * (value_type(1) / mask_);
		}
		template<std::size_t Size_, typename T_>
		inline value_type operator()(const EmuMath::Vector<Size_, T_>& point_, value_type freq_, const EmuMath::NoisePermutations& permutations_) const
		{
			return operator()(static_cast<value_type>(point_.template at<0>()), freq_, permutations_);
		}
	};

	/// <summary> Functor to produce 1-dimensional smooth perlin noise. Produced noise is in the range -0.5:0.5. </summary>
	template<typename FP_>
	struct make_noise_1d<EmuMath::NoiseType::PERLIN, FP_>
	{
		static_assert(std::is_floating_point_v<FP_>, "Invalid FP_ type argument provided to EmuMath::Functors::make_noise_1d; the type must be a floating point.");
		using value_type = FP_;
		using gradient_type = value_type;

		static constexpr std::size_t _num_gradients = 2;
		static constexpr gradient_type _gradients[_num_gradients] = { gradient_type(1), gradient_type(-1) };
		static constexpr EmuMath::NoisePermutationValue _gradient_mask = 1;

		EmuCore::do_lerp<value_type, value_type, value_type> lerp_;
		EmuCore::do_floor<value_type> floor_;
		constexpr make_noise_1d() : lerp_(), floor_()
		{
		}
		inline value_type operator()(value_type point_, value_type freq_, const EmuMath::NoisePermutations& permutations_) const
		{
			EmuMath::NoisePermutationValue mask_ = permutations_.HighestStoredValue();
			point_ *= freq_;
			EmuMath::NoisePermutationValue i_0_ = static_cast<EmuMath::NoisePermutationValue>(floor_(point_));
			value_type t_0_ = point_ - static_cast<value_type>(i_0_);
			value_type t_1_ = t_0_ - value_type(1);
			i_0_ &= mask_;
			EmuMath::NoisePermutationValue i_1_ = (i_0_ + 1) & mask_;

			gradient_type gradient_0_ = _gradients[permutations_[i_0_] & _gradient_mask];
			gradient_type gradient_1_ = _gradients[permutations_[i_1_] & _gradient_mask];

			value_type val_0_ = gradient_0_ * t_0_;
			value_type val_1_ = gradient_1_ * t_1_;

			return lerp_(val_0_, val_1_, EmuMath::Functors::_underlying_noise_gen::smooth_t(t_0_));
		}
		template<std::size_t Size_, typename T_>
		inline value_type operator()(const EmuMath::Vector<Size_, T_>& point_, value_type freq_, const EmuMath::NoisePermutations& permutations_) const
		{
			return operator()(static_cast<value_type>(point_.template at<0>()), freq_, permutations_);
		}
	};
}

#endif
