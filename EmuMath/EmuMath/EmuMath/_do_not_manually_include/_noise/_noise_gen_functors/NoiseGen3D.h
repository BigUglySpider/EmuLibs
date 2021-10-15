#ifndef EMU_MATH_NOISE_GEN_FUNCTOR_3D_H_INC_
#define EMU_MATH_NOISE_GEN_FUNCTOR_3D_H_INC_ 1

#include "_common_noise_gen_functor_includes.h"

namespace EmuMath::Functors
{
	template<EmuMath::NoiseType NoiseType_>
	struct make_noise_3d
	{
		static_assert(EmuMath::Validity::AssertValidNoiseType<NoiseType_>(), "Invalid NoiseType_ argument provided to EmuMath::Functors::make_noise_3d.");
		constexpr make_noise_3d()
		{
			static_assert(false, "Attempted to construct a make_noise_3d instance for a NoiseType that has not been implemented.");
		}
	};

	template<>
	struct make_noise_3d<EmuMath::NoiseType::VALUE>
	{
		constexpr make_noise_3d()
		{
		}
		inline float operator()(EmuMath::Vector<3, float> point_, float freq_, const EmuMath::NoisePermutations& permutations_) const
		{
			std::int32_t mask_ = permutations_.MaxValue();
			point_ *= freq_;
			int ix = static_cast<int>(floorf(point_.at<0>()));
			int iy = static_cast<int>(floorf(point_.at<1>()));
			int iz = static_cast<int>(floorf(point_.at<2>()));
			ix &= mask_;
			iy &= mask_;
			iz &= mask_;

			std::size_t perm_x_ = static_cast<std::size_t>(permutations_[ix]);
			std::size_t perm_xyz_ = (static_cast<std::size_t>(permutations_[(perm_x_ + iy) & mask_]) + iz) & mask_;
			return permutations_[perm_xyz_] * (1.0f / mask_);
		}
		template<std::size_t Size_, typename T_, typename OnlyNonV3f = std::enable_if_t<Size_ != 3 || !std::is_same_v<float, T_>>>
		inline float operator()(const EmuMath::Vector<Size_, T_>& point_, float freq_, const EmuMath::NoisePermutations& permutations_) const
		{
			return operator()(EmuMath::Vector<3, float>(point_), freq_, permutations_);
		}
	};

	template<>
	struct make_noise_3d<EmuMath::NoiseType::VALUE_SMOOTH>
	{
		EmuCore::do_lerp<float, float, float> lerp_;
		constexpr make_noise_3d() : lerp_()
		{
		}
		inline float operator()(EmuMath::Vector<3, float> point_, float freq_, const EmuMath::NoisePermutations& permutations_) const
		{
			std::int32_t mask_ = permutations_.MaxValue();
			point_ *= freq_;

			std::int32_t ix_0_ = static_cast<std::int32_t>(floorf(point_.at<0>()));
			std::int32_t iy_0_ = static_cast<std::int32_t>(floorf(point_.at<1>()));
			std::int32_t iz_0_ = static_cast<std::int32_t>(floorf(point_.at<2>()));

			float tx = EmuMath::Functors::_underlying_noise_gen::SmoothT(point_.x - ix_0_);
			float ty = EmuMath::Functors::_underlying_noise_gen::SmoothT(point_.y - iy_0_);
			float tz = EmuMath::Functors::_underlying_noise_gen::SmoothT(point_.z - iz_0_);

			ix_0_ &= mask_;
			iy_0_ &= mask_;
			iz_0_ &= mask_;
			std::int32_t ix_1_ = (ix_0_ + 1) & mask_;
			std::int32_t iy_1_ = (iy_0_ + 1) & mask_;
			std::int32_t iz_1_ = (iz_0_ + 1) & mask_;

			std::int32_t perm_0_ = permutations_[ix_0_];
			std::int32_t perm_1_ = permutations_[ix_1_];

			std::int32_t perm_00_ = permutations_[static_cast<std::size_t>(perm_0_ + iy_0_) & mask_];
			std::int32_t perm_01_ = permutations_[static_cast<std::size_t>(perm_0_ + iy_1_) & mask_];
			std::int32_t perm_10_ = permutations_[static_cast<std::size_t>(perm_1_ + iy_0_) & mask_];
			std::int32_t perm_11_ = permutations_[static_cast<std::size_t>(perm_1_ + iy_1_) & mask_];

			float perm_000_ = static_cast<float>(permutations_[static_cast<std::size_t>(perm_00_ + iz_0_) & mask_]);
			float perm_001_ = static_cast<float>(permutations_[static_cast<std::size_t>(perm_00_ + iz_1_) & mask_]);
			float perm_010_ = static_cast<float>(permutations_[static_cast<std::size_t>(perm_01_ + iz_0_) & mask_]);
			float perm_011_ = static_cast<float>(permutations_[static_cast<std::size_t>(perm_01_ + iz_1_) & mask_]);
			float perm_100_ = static_cast<float>(permutations_[static_cast<std::size_t>(perm_10_ + iz_0_) & mask_]);
			float perm_101_ = static_cast<float>(permutations_[static_cast<std::size_t>(perm_10_ + iz_1_) & mask_]);
			float perm_110_ = static_cast<float>(permutations_[static_cast<std::size_t>(perm_11_ + iz_0_) & mask_]);
			float perm_111_ = static_cast<float>(permutations_[static_cast<std::size_t>(perm_11_ + iz_1_) & mask_]);

			return lerp_
			(
				lerp_(lerp_(perm_000_, perm_100_, tx), lerp_(perm_010_, perm_110_, tx), ty),
				lerp_(lerp_(perm_001_, perm_101_, tx), lerp_(perm_011_, perm_111_, tx), ty),
				tz
			) * (1.0f / mask_);
		}
		template<std::size_t Size_, typename T_, typename OnlyNonV3f = std::enable_if_t<Size_ != 3 || !std::is_same_v<float, T_>>>
		inline float operator()(const EmuMath::Vector<Size_, T_>& point_, float freq_, const EmuMath::NoisePermutations& permutations_) const
		{
			return operator()(EmuMath::Vector<3, float>(point_), freq_, permutations_);
		}
	};


	/// <summary> Functor to produce 3-dimensional smooth perlin noise. Produced noise targets the range -(sqrt(3)/2):(sqrt(3)/2). </summary>
	template<>
	struct make_noise_3d<EmuMath::NoiseType::PERLIN>
	{
		static constexpr std::size_t _num_gradients = 16;
		static constexpr EmuMath::Vector<3, float> _gradients[_num_gradients] =
		{
			EmuMath::Vector<3, float>( 1.0f, 1.0f, 0.0f),
			EmuMath::Vector<3, float>(-1.0f, 1.0f, 0.0f),
			EmuMath::Vector<3, float>( 1.0f, -1.0f, 0.0f),
			EmuMath::Vector<3, float>(-1.0f, -1.0f, 0.0f),
			EmuMath::Vector<3, float>( 1.0f, 0.0f, 1.0f),
			EmuMath::Vector<3, float>(-1.0f, 0.0f, 1.0f),
			EmuMath::Vector<3, float>( 1.0f, 0.0f, -1.0f),
			EmuMath::Vector<3, float>(-1.0f, 0.0f, -1.0f),
			EmuMath::Vector<3, float>( 0.0f, 1.0f,  1.0f),
			EmuMath::Vector<3, float>( 0.0f,-1.0f,  1.0f),
			EmuMath::Vector<3, float>( 0.0f, 1.0f, -1.0f),
			EmuMath::Vector<3, float>( 0.0f,-1.0f, -1.0f),
			// Filler values for successful bit masking; specific values are used to introduce no directional bias as per Ken Perlin
			EmuMath::Vector<3, float>(1.0f, 1.0f, 0.0f),
			EmuMath::Vector<3, float>(-1.0f, 1.0f, 0.0f),
			EmuMath::Vector<3, float>(0.0f, -1.0f, 1.0f),
			EmuMath::Vector<3, float>(0.0f, -1.0f, -1.0f)
		};
		static constexpr std::size_t _gradient_mask = 15;

		EmuCore::do_lerp<float, float, float> lerp_;
		constexpr make_noise_3d() : lerp_()
		{
		}
		inline float operator()(EmuMath::Vector<3, float> point_, float freq_, const EmuMath::NoisePermutations& permutations_) const
		{
			std::int32_t mask_ = permutations_.MaxValue();
			point_ *= freq_;

			std::int32_t ix_0_ = static_cast<std::int32_t>(floorf(point_.x));
			std::int32_t iy_0_ = static_cast<std::int32_t>(floorf(point_.y));
			std::int32_t iz_0_ = static_cast<std::int32_t>(floorf(point_.z));

			float tx_0_ = point_.x - ix_0_;
			float ty_0_ = point_.y - iy_0_;
			float tz_0_ = point_.z - iz_0_;
			float tx_1_ = tx_0_ - 1.0f;
			float ty_1_ = ty_0_ - 1.0f;
			float tz_1_ = tz_0_ - 1.0f;

			ix_0_ &= mask_;
			iy_0_ &= mask_;
			iz_0_ &= mask_;
			std::int32_t ix_1_ = (ix_0_ + 1) & mask_;
			std::int32_t iy_1_ = (iy_0_ + 1) & mask_;
			std::int32_t iz_1_ = (iz_0_ + 1) & mask_;

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

			float val_000_ = EmuMath::Functors::_underlying_noise_gen::DotWithScalar(_gradients[perm_000_ & _gradient_mask], tx_0_, ty_0_, tz_0_);
			float val_001_ = EmuMath::Functors::_underlying_noise_gen::DotWithScalar(_gradients[perm_001_ & _gradient_mask], tx_0_, ty_0_, tz_1_);
			float val_010_ = EmuMath::Functors::_underlying_noise_gen::DotWithScalar(_gradients[perm_010_ & _gradient_mask], tx_0_, ty_1_, tz_0_);
			float val_011_ = EmuMath::Functors::_underlying_noise_gen::DotWithScalar(_gradients[perm_011_ & _gradient_mask], tx_0_, ty_1_, tz_1_);
			float val_100_ = EmuMath::Functors::_underlying_noise_gen::DotWithScalar(_gradients[perm_100_ & _gradient_mask], tx_1_, ty_0_, tz_0_);
			float val_101_ = EmuMath::Functors::_underlying_noise_gen::DotWithScalar(_gradients[perm_101_ & _gradient_mask], tx_1_, ty_0_, tz_1_);
			float val_110_ = EmuMath::Functors::_underlying_noise_gen::DotWithScalar(_gradients[perm_110_ & _gradient_mask], tx_1_, ty_1_, tz_0_);
			float val_111_ = EmuMath::Functors::_underlying_noise_gen::DotWithScalar(_gradients[perm_111_ & _gradient_mask], tx_1_, ty_1_, tz_1_);

			float tx = EmuMath::Functors::_underlying_noise_gen::SmoothT(tx_0_);
			float ty = EmuMath::Functors::_underlying_noise_gen::SmoothT(ty_0_);
			float tz = EmuMath::Functors::_underlying_noise_gen::SmoothT(tz_0_);
			return lerp_
			(
				lerp_(lerp_(val_000_, val_100_, tx), lerp_(val_010_, val_110_, tx), ty),
				lerp_(lerp_(val_001_, val_101_, tx), lerp_(val_011_, val_111_, tx), ty),
				tz
			);
		}
		template<std::size_t Size_, typename T_, typename OnlyNonV3f = std::enable_if_t<Size_ != 3 || !std::is_same_v<float, T_>>>
		inline float operator()(const EmuMath::Vector<Size_, T_>& point_, float freq_, const EmuMath::NoisePermutations& permutations_) const
		{
			return operator()(EmuMath::Vector<3, float>(point_), freq_, permutations_);
		}
	};
}

#endif
