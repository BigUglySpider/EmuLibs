#ifndef EMU_MATH_FRACTAL_NOISE_WRAPPER_H_INC_
#define EMU_MATH_FRACTAL_NOISE_WRAPPER_H_INC_ 1

#include "_common_noise_gen_functor_includes.h"
#include "../_noise_info/FractalNoiseInfo.h"

namespace EmuMath::Functors
{
	template<class PerIterationGenerator_, typename OutT_>
	struct no_fractal_noise_wrapper
	{
		using generator_type = PerIterationGenerator_;
		using value_type = OutT_;

		template<typename...GeneratorConstructorArgs_, typename = std::enable_if_t<std::is_constructible_v<generator_type, GeneratorConstructorArgs_...>>>
		constexpr no_fractal_noise_wrapper
		(
			float freq_,
			const EmuMath::NoisePermutations& permutations_,
			GeneratorConstructorArgs_&&...generator_constructor_args_
		) :
			freq(freq_),
			permutations(permutations_),
			generator(generator_constructor_args_...)
		{
		}
		template<typename...GeneratorConstructorArgs_, typename = std::enable_if_t<std::is_constructible_v<generator_type, GeneratorConstructorArgs_...>>>
		constexpr no_fractal_noise_wrapper
		(
			float freq_,
			EmuMath::NoisePermutations&& permutations_,
			GeneratorConstructorArgs_&&...generator_constructor_args_
		) :
			freq(freq_),
			permutations(permutations_),
			generator(generator_constructor_args_...)
		{
		}

		template<typename Point_>
		constexpr inline value_type operator()(const Point_& point_)
		{
			return generator(point_, freq, permutations);
		}

		generator_type generator;
		EmuMath::NoisePermutations permutations;
		float freq;
	};

	template<class PerIterationGenerator_, typename Out_>
	struct fractal_noise_wrapper
	{
	public:
		using generator_type = PerIterationGenerator_;
		using value_type = Out_;

		template<typename...GeneratorConstructorArgs_, typename = std::enable_if_t<std::is_constructible_v<generator_type, GeneratorConstructorArgs_...>>>
		constexpr fractal_noise_wrapper
		(
			float freq_,
			const EmuMath::NoisePermutations& permutations_,
			const EmuMath::Info::FractalNoiseInfo& fractal_info_,
			GeneratorConstructorArgs_&&...generator_constructor_args_
		) :
			freq(freq_),
			fractal_info(fractal_info_),
			permutations(permutations_),
			generator(generator_constructor_args_...)
		{
		}
		template<typename...GeneratorConstructorArgs_, typename = std::enable_if_t<std::is_constructible_v<generator_type, GeneratorConstructorArgs_...>>>
		constexpr fractal_noise_wrapper
		(
			float freq_,
			EmuMath::NoisePermutations&& permutations_,
			const EmuMath::Info::FractalNoiseInfo& fractal_info_,
			GeneratorConstructorArgs_&&...generator_constructor_args_
		) :
			freq(freq_),
			fractal_info(fractal_info_),
			permutations(permutations_),
			generator(generator_constructor_args_...)
		{
		}

		template<typename Point_>
		constexpr inline value_type operator()(const Point_& point_)
		{
			float freq_ = freq;
			value_type result_ = generator(point_, freq_, permutations);
			float range_ = 1.0f;
			float amplitude_ = 1.0f;
			float lacunarity_ = fractal_info.GetLacunarity();
			float gain_ = fractal_info.GetGain();
			for (std::size_t octave_ = 1, end_ = fractal_info.GetOctaves(); octave_ < end_; ++octave_)
			{
				freq_ *= lacunarity_;
				amplitude_ *= gain_;
				range_ += amplitude_;
				result_ += generator(point_, freq_, permutations) * amplitude_;
			}
			return result_ / static_cast<value_type>(range_);
		}

		EmuMath::Info::FractalNoiseInfo fractal_info;
		generator_type generator;
		EmuMath::NoisePermutations permutations;
		float freq;
	};
}

#endif
