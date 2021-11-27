#ifndef EMU_MATH_FAST_NOISE_FUNCTORS_H_INC_
#define EMU_MATH_FAST_NOISE_FUNCTORS_H_INC_ 1

#include "_noise_gen_functors/FastNoiseGen1D.h"
#include "_noise_gen_functors/FastNoiseGen2D.h"
#include "_noise_gen_functors/FastNoiseGen3D.h"
#include "_noise_gen_functors/FastFractalNoiseWrapper.h"

namespace EmuMath::Functors
{
	template<std::size_t Dimensions_, EmuMath::NoiseType NoiseType_, typename Register_ = __m128>
	struct find_fast_noise_functor
	{
		static_assert(Dimensions_ >= 1 && Dimensions_ <= 3, "Attempted to use EmuMath::Functors::find_fast_noise_functor, but provided an invalid number of dimensions.");
		static_assert(EmuMath::Validity::AssertValidNoiseType<NoiseType_>(), "Provided an invalid EmuMath::NoiseType to EmuMath::Functors::find_noise_functor.");

		using type = std::conditional_t
		<
			Dimensions_ == 1,
			EmuMath::Functors::make_fast_noise_1d<NoiseType_, Register_>,
			std::conditional_t
			<
				Dimensions_ == 2,
				EmuMath::Functors::make_fast_noise_2d<NoiseType_, Register_>,
				std::conditional_t
				<
					Dimensions_ == 3,
					EmuMath::Functors::make_fast_noise_3d<NoiseType_, Register_>,
					void
				>
			>
		>;
	};
}

namespace EmuMath
{
	/// <summary> Alias to easily identify an EmuMath noise generation functor using purely template arguments. </summary>
	template<std::size_t Dimensions_, EmuMath::NoiseType NoiseType_, typename Register_ = __m128>
	using FastNoiseGenFunctor = typename EmuMath::Functors::find_fast_noise_functor<Dimensions_, NoiseType_, Register_>::type;
}

#endif
