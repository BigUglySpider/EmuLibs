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
			int ix = static_cast<int>(floorf(point_.x));
			int iy = static_cast<int>(floorf(point_.y));
			int iz = static_cast<int>(floorf(point_.z));
			ix &= mask_;
			iy &= mask_;
			iz &= mask_;
			return permutations_[(permutations_[(permutations_[ix] + iy) & mask_] + iz) & mask_] * (1.0f / mask_);
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
			return point_.x;
		}
		template<std::size_t Size_, typename T_, typename OnlyNonV3f = std::enable_if_t<Size_ != 3 || !std::is_same_v<float, T_>>>
		inline float operator()(const EmuMath::Vector<Size_, T_>& point_, float freq_, const EmuMath::NoisePermutations& permutations_) const
		{
			return operator()(EmuMath::Vector<3, float>(point_), freq_, permutations_);
		}
	};

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
			return point_.x;
		}
		template<std::size_t Size_, typename T_, typename OnlyNonV3f = std::enable_if_t<Size_ != 3 || !std::is_same_v<float, T_>>>
		inline float operator()(const EmuMath::Vector<Size_, T_>& point_, float freq_, const EmuMath::NoisePermutations& permutations_) const
		{
			return operator()(EmuMath::Vector<3, float>(point_), freq_, permutations_);
		}
	};
}

#endif
