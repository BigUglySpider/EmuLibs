#ifndef EMU_MATH_NOISE_FUNCTORS_H_INC_
#define EMU_MATH_NOISE_FUNCTORS_H_INC_ 1

#include "_noise_gen_functors/_common_noise_gen_functor_includes.h"
#include "_noise_gen_functors/NoiseGen1D.h"
#include "_noise_gen_functors/NoiseGen2D.h"
#include "_noise_gen_functors/NoiseGen3D.h"

namespace EmuMath::Functors
{
	template<std::size_t Dimensions_, EmuMath::NoiseType NoiseType_>
	struct find_noise_functor
	{
		static_assert(Dimensions_ >= 1 && Dimensions_ <= 3, "Attempted to use EmuMath::Functors::find_noise_functor, but provided an invalid number of dimensions.");
		static_assert(EmuMath::Validity::AssertValidNoiseType<NoiseType_>(), "Provided an invalid EmuMath::NoiseType to EmuMath::Functors::find_noise_functor.");

		using type = std::conditional_t
		<
			Dimensions_ == 1,
			EmuMath::Functors::make_noise_1d<NoiseType_>,
			std::conditional_t
			<
				Dimensions_ == 2,
				EmuMath::Functors::make_noise_2d<NoiseType_>,
				std::conditional_t
				<
					Dimensions_ == 3,
					EmuMath::Functors::make_noise_3d<NoiseType_>,
					void
				>
			>
		>;
	};
}

namespace EmuMath
{
	/// <summary> Alias to easily identify an EmuMath noise generation functor using purely template arguments. </summary>
	template<std::size_t Dimensions_, EmuMath::NoiseType NoiseType_>
	using noise_gen_functor = typename EmuMath::Functors::find_noise_functor<Dimensions_, NoiseType_>::type;
}

#endif
