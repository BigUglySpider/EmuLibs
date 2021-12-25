#ifndef EMU_MATH_NOISE_GEN_FUNCTOR_3D_H_INC_
#define EMU_MATH_NOISE_GEN_FUNCTOR_3D_H_INC_ 1

#include "_common_noise_gen_functor_includes.h"
#include "../../../../EmuCore/TMPHelpers/Values.h"

namespace EmuMath::Functors
{
	template<EmuMath::NoiseType NoiseType_, typename FP_ = float>
	struct make_noise_3d
	{
		static_assert(EmuMath::Validity::assert_valid_noise_type<NoiseType_>(), "Invalid NoiseType_ argument provided to EmuMath::Functors::make_noise_3d.");
		static_assert(std::is_floating_point_v<FP_>, "Invalid FP_ type argument provided to EmuMath::Functors::make_noise_3d; the type must be a floating point.");
		constexpr make_noise_3d()
		{
			static_assert(EmuCore::TMP::get_false<FP_>(), "Attempted to construct a make_noise_3d instance for a NoiseType that has not been implemented.");
		}
	};

	template<typename FP_>
	struct make_noise_3d<EmuMath::NoiseType::VALUE, FP_>
	{
		static_assert(std::is_floating_point_v<FP_>, "Invalid FP_ type argument provided to EmuMath::Functors::make_noise_3d; the type must be a floating point.");
		using value_type = FP_;

		EmuCore::do_floor<value_type> floor_;
		constexpr make_noise_3d() : floor_()
		{
		}
		[[nodiscard]] inline value_type operator()(EmuMath::Vector<3, value_type> point_, value_type freq_, const EmuMath::NoisePermutations& permutations_) const
		{
			EmuMath::NoisePermutationValue mask_ = permutations_.HighestStoredValue();
			point_ *= freq_;
			EmuMath::NoisePermutationValue ix_ = static_cast<EmuMath::NoisePermutationValue>(floor_(point_.at<0>()));
			EmuMath::NoisePermutationValue iy_ = static_cast<EmuMath::NoisePermutationValue>(floor_(point_.at<1>()));
			EmuMath::NoisePermutationValue iz_ = static_cast<EmuMath::NoisePermutationValue>(floor_(point_.at<2>()));
			ix_ &= mask_;
			iy_ &= mask_;
			iz_ &= mask_;

			// Forced store as size_t so we can handle width changes if EmuMath::NoisePermutationValue is of different width
			std::size_t perm_x_ = static_cast<std::size_t>(permutations_[ix_]);
			std::size_t perm_xyz_ = (static_cast<std::size_t>(permutations_[(perm_x_ + iy_) & mask_]) + iz_) & mask_;
			return permutations_[perm_xyz_] * (value_type(1) / mask_);
		}
		template<std::size_t Size_, typename T_, typename OnlyNonV3f = std::enable_if_t<Size_ != 3 || !std::is_same_v<value_type, T_>>>
		[[nodiscard]] inline value_type operator()(const EmuMath::Vector<Size_, T_>& point_, value_type freq_, const EmuMath::NoisePermutations& permutations_) const
		{
			return operator()(EmuMath::Vector<3, value_type>(point_), freq_, permutations_);
		}
	};

	template<typename FP_>
	struct make_noise_3d<EmuMath::NoiseType::VALUE_SMOOTH, FP_>
	{
		static_assert(std::is_floating_point_v<FP_>, "Invalid FP_ type argument provided to EmuMath::Functors::make_noise_3d; the type must be a floating point.");
		using value_type = FP_;

		EmuCore::do_lerp<value_type, value_type, value_type> lerp_;
		EmuCore::do_floor<value_type> floor_;
		constexpr make_noise_3d() : lerp_(), floor_()
		{
		}
		[[nodiscard]] inline value_type operator()(EmuMath::Vector<3, value_type> point_, value_type freq_, const EmuMath::NoisePermutations& permutations_) const
		{
			EmuMath::NoisePermutationValue mask_ = permutations_.HighestStoredValue();
			point_ *= freq_;

			EmuMath::NoisePermutationValue ix_0_ = static_cast<EmuMath::NoisePermutationValue>(floor_(point_.at<0>()));
			EmuMath::NoisePermutationValue iy_0_ = static_cast<EmuMath::NoisePermutationValue>(floor_(point_.at<1>()));
			EmuMath::NoisePermutationValue iz_0_ = static_cast<EmuMath::NoisePermutationValue>(floor_(point_.at<2>()));

			value_type tx = EmuMath::Functors::_underlying_noise_gen::smooth_t(point_.x - static_cast<value_type>(ix_0_));
			value_type ty = EmuMath::Functors::_underlying_noise_gen::smooth_t(point_.y - static_cast<value_type>(iy_0_));
			value_type tz = EmuMath::Functors::_underlying_noise_gen::smooth_t(point_.z - static_cast<value_type>(iz_0_));

			ix_0_ &= mask_;
			iy_0_ &= mask_;
			iz_0_ &= mask_;
			EmuMath::NoisePermutationValue ix_1_ = (ix_0_ + 1) & mask_;
			EmuMath::NoisePermutationValue iy_1_ = (iy_0_ + 1) & mask_;
			EmuMath::NoisePermutationValue iz_1_ = (iz_0_ + 1) & mask_;


			// Forced store as size_t so we can handle width changes if EmuMath::NoisePermutationValue is not size_t width
			std::size_t perm_0_ = static_cast<std::size_t>(permutations_[ix_0_]);
			std::size_t perm_1_ = static_cast<std::size_t>(permutations_[ix_1_]);

			std::size_t perm_00_ = static_cast<std::size_t>(permutations_[(perm_0_ + iy_0_) & mask_]);
			std::size_t perm_01_ = static_cast<std::size_t>(permutations_[(perm_0_ + iy_1_) & mask_]);
			std::size_t perm_10_ = static_cast<std::size_t>(permutations_[(perm_1_ + iy_0_) & mask_]);
			std::size_t perm_11_ = static_cast<std::size_t>(permutations_[(perm_1_ + iy_1_) & mask_]);

			value_type perm_000_ = static_cast<value_type>(permutations_[(perm_00_ + iz_0_) & mask_]);
			value_type perm_001_ = static_cast<value_type>(permutations_[(perm_00_ + iz_1_) & mask_]);
			value_type perm_010_ = static_cast<value_type>(permutations_[(perm_01_ + iz_0_) & mask_]);
			value_type perm_011_ = static_cast<value_type>(permutations_[(perm_01_ + iz_1_) & mask_]);
			value_type perm_100_ = static_cast<value_type>(permutations_[(perm_10_ + iz_0_) & mask_]);
			value_type perm_101_ = static_cast<value_type>(permutations_[(perm_10_ + iz_1_) & mask_]);
			value_type perm_110_ = static_cast<value_type>(permutations_[(perm_11_ + iz_0_) & mask_]);
			value_type perm_111_ = static_cast<value_type>(permutations_[(perm_11_ + iz_1_) & mask_]);

			return lerp_
			(
				lerp_(lerp_(perm_000_, perm_100_, tx), lerp_(perm_010_, perm_110_, tx), ty),
				lerp_(lerp_(perm_001_, perm_101_, tx), lerp_(perm_011_, perm_111_, tx), ty),
				tz
			) * (value_type(1) / mask_);
		}
		template<std::size_t Size_, typename T_, typename OnlyNonV3f = std::enable_if_t<Size_ != 3 || !std::is_same_v<value_type, T_>>>
		[[nodiscard]] inline value_type operator()(const EmuMath::Vector<Size_, T_>& point_, value_type freq_, const EmuMath::NoisePermutations& permutations_) const
		{
			return operator()(EmuMath::Vector<3, value_type>(point_), freq_, permutations_);
		}
	};


	/// <summary> Functor to produce 3-dimensional smooth perlin noise. Produced noise targets the range -(sqrt(3)/2):(sqrt(3)/2). </summary>
	template<typename FP_>
	struct make_noise_3d<EmuMath::NoiseType::PERLIN, FP_>
	{

		static_assert(std::is_floating_point_v<FP_>, "Invalid FP_ type argument provided to EmuMath::Functors::make_noise_3d; the type must be a floating point.");
		using value_type = FP_;

		using gradients = EmuMath::Functors::_underlying_noise_gen::perlin_gradients<3, value_type>;

		EmuCore::do_lerp<value_type, value_type, value_type> lerp_;
		EmuCore::do_floor<value_type> floor_;
		constexpr make_noise_3d() : lerp_(), floor_()
		{
		}
		[[nodiscard]] inline value_type operator()(EmuMath::Vector<3, value_type> point_, value_type freq_, const EmuMath::NoisePermutations& permutations_) const
		{
			EmuMath::NoisePermutationValue mask_ = permutations_.HighestStoredValue();
			point_ *= freq_;

			EmuMath::NoisePermutationValue ix_0_ = static_cast<EmuMath::NoisePermutationValue>(floor_(point_.x));
			EmuMath::NoisePermutationValue iy_0_ = static_cast<EmuMath::NoisePermutationValue>(floor_(point_.y));
			EmuMath::NoisePermutationValue iz_0_ = static_cast<EmuMath::NoisePermutationValue>(floor_(point_.z));

			value_type tx_0_ = point_.x - ix_0_;
			value_type ty_0_ = point_.y - iy_0_;
			value_type tz_0_ = point_.z - iz_0_;
			value_type tx_1_ = tx_0_ - value_type(1);
			value_type ty_1_ = ty_0_ - value_type(1);
			value_type tz_1_ = tz_0_ - value_type(1);

			ix_0_ &= mask_;
			iy_0_ &= mask_;
			iz_0_ &= mask_;
			EmuMath::NoisePermutationValue ix_1_ = (ix_0_ + 1) & mask_;
			EmuMath::NoisePermutationValue iy_1_ = (iy_0_ + 1) & mask_;
			EmuMath::NoisePermutationValue iz_1_ = (iz_0_ + 1) & mask_;


			// Forced store as size_t so we can handle width changes if EmuMath::NoisePermutationValue is not size_t width
			std::size_t perm_0_ = static_cast<std::size_t>(permutations_[ix_0_]);
			std::size_t perm_1_ = static_cast<std::size_t>(permutations_[ix_1_]);

			std::size_t perm_00_ = static_cast<std::size_t>(permutations_[(perm_0_ + iy_0_) & mask_]);
			std::size_t perm_01_ = static_cast<std::size_t>(permutations_[(perm_0_ + iy_1_) & mask_]);
			std::size_t perm_10_ = static_cast<std::size_t>(permutations_[(perm_1_ + iy_0_) & mask_]);
			std::size_t perm_11_ = static_cast<std::size_t>(permutations_[(perm_1_ + iy_1_) & mask_]);

			std::size_t perm_000_ = static_cast<std::size_t>(permutations_[(perm_00_ + iz_0_) & mask_]);
			std::size_t perm_001_ = static_cast<std::size_t>(permutations_[(perm_00_ + iz_1_) & mask_]);
			std::size_t perm_010_ = static_cast<std::size_t>(permutations_[(perm_01_ + iz_0_) & mask_]);
			std::size_t perm_011_ = static_cast<std::size_t>(permutations_[(perm_01_ + iz_1_) & mask_]);
			std::size_t perm_100_ = static_cast<std::size_t>(permutations_[(perm_10_ + iz_0_) & mask_]);
			std::size_t perm_101_ = static_cast<std::size_t>(permutations_[(perm_10_ + iz_1_) & mask_]);
			std::size_t perm_110_ = static_cast<std::size_t>(permutations_[(perm_11_ + iz_0_) & mask_]);
			std::size_t perm_111_ = static_cast<std::size_t>(permutations_[(perm_11_ + iz_1_) & mask_]);

			value_type val_000_ = EmuMath::Functors::_underlying_noise_gen::dot_with_scalar(gradients::values[perm_000_ & gradients::mask], tx_0_, ty_0_, tz_0_);
			value_type val_001_ = EmuMath::Functors::_underlying_noise_gen::dot_with_scalar(gradients::values[perm_001_ & gradients::mask], tx_0_, ty_0_, tz_1_);
			value_type val_010_ = EmuMath::Functors::_underlying_noise_gen::dot_with_scalar(gradients::values[perm_010_ & gradients::mask], tx_0_, ty_1_, tz_0_);
			value_type val_011_ = EmuMath::Functors::_underlying_noise_gen::dot_with_scalar(gradients::values[perm_011_ & gradients::mask], tx_0_, ty_1_, tz_1_);
			value_type val_100_ = EmuMath::Functors::_underlying_noise_gen::dot_with_scalar(gradients::values[perm_100_ & gradients::mask], tx_1_, ty_0_, tz_0_);
			value_type val_101_ = EmuMath::Functors::_underlying_noise_gen::dot_with_scalar(gradients::values[perm_101_ & gradients::mask], tx_1_, ty_0_, tz_1_);
			value_type val_110_ = EmuMath::Functors::_underlying_noise_gen::dot_with_scalar(gradients::values[perm_110_ & gradients::mask], tx_1_, ty_1_, tz_0_);
			value_type val_111_ = EmuMath::Functors::_underlying_noise_gen::dot_with_scalar(gradients::values[perm_111_ & gradients::mask], tx_1_, ty_1_, tz_1_);

			value_type tx = EmuMath::Functors::_underlying_noise_gen::smooth_t(tx_0_);
			value_type ty = EmuMath::Functors::_underlying_noise_gen::smooth_t(ty_0_);
			value_type tz = EmuMath::Functors::_underlying_noise_gen::smooth_t(tz_0_);

			return lerp_
			(
				lerp_(lerp_(val_000_, val_100_, tx), lerp_(val_010_, val_110_, tx), ty),
				lerp_(lerp_(val_001_, val_101_, tx), lerp_(val_011_, val_111_, tx), ty),
				tz
			);
		}
		template<std::size_t Size_, typename T_, typename OnlyNonV3f = std::enable_if_t<Size_ != 3 || !std::is_same_v<value_type, T_>>>
		[[nodiscard]] inline value_type operator()(const EmuMath::Vector<Size_, T_>& point_, value_type freq_, const EmuMath::NoisePermutations& permutations_) const
		{
			return operator()(EmuMath::Vector<3, value_type>(point_), freq_, permutations_);
		}
	};
}

#endif
