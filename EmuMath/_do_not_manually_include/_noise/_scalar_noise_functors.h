#ifndef EMU_MATH_NOISE_FUNCTORS_H_INC_
#define EMU_MATH_NOISE_FUNCTORS_H_INC_ 1

#include "_noise_gen_functors/_common_noise_gen_functor_includes.h"
#include "_noise_gen_functors/_scalar_noise_gen_1d.h"
#include "_noise_gen_functors/_scalar_noise_gen_2d.h"
#include "_noise_gen_functors/_scalar_noise_gen_3d.h"
#include "_noise_gen_functors/_fractal_noise_wrapper.h"

namespace EmuMath::Functors
{
	template<std::size_t Dimensions_, EmuMath::NoiseType NoiseType_, typename FP_ = float>
	struct find_noise_functor
	{
		static_assert(Dimensions_ >= 1 && Dimensions_ <= 3, "Attempted to use EmuMath::Functors::find_noise_functor, but provided an invalid number of dimensions.");
		static_assert(EmuMath::Validity::assert_valid_noise_type<NoiseType_>(), "Provided an invalid EmuMath::NoiseType to EmuMath::Functors::find_noise_functor.");

		using type = std::conditional_t
		<
			Dimensions_ == 1,
			EmuMath::Functors::make_noise_1d<NoiseType_, FP_>,
			std::conditional_t
			<
				Dimensions_ == 2,
				EmuMath::Functors::make_noise_2d<NoiseType_, FP_>,
				std::conditional_t
				<
					Dimensions_ == 3,
					EmuMath::Functors::make_noise_3d<NoiseType_, FP_>,
					void
				>
			>
		>;
	};
}

namespace EmuMath
{
	/// <summary> Alias to easily identify an EmuMath noise generation functor using purely template arguments. </summary>
	template<std::size_t Dimensions_, EmuMath::NoiseType NoiseType_, typename FP_ = float>
	using noise_gen_functor = typename EmuMath::Functors::find_noise_functor<Dimensions_, NoiseType_, FP_>::type;
}

#endif
