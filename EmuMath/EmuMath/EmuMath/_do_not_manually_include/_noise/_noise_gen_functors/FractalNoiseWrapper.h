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
			value_type freq_,
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
			value_type freq_,
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
		value_type freq;
	};

	template<class PerIterationGenerator_, typename Out_>
	struct fractal_noise_wrapper
	{
	public:
		using generator_type = PerIterationGenerator_;
		using value_type = Out_;
		using fractal_info_type = EmuMath::Info::FractalNoiseInfo<value_type>;

		template<typename...GeneratorConstructorArgs_, typename = std::enable_if_t<std::is_constructible_v<generator_type, GeneratorConstructorArgs_...>>>
		constexpr fractal_noise_wrapper
		(
			float freq_,
			const EmuMath::NoisePermutations& permutations_,
			const fractal_info_type& fractal_info_,
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
			value_type freq_,
			EmuMath::NoisePermutations&& permutations_,
			const fractal_info_type& fractal_info_,
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
			value_type freq_ = freq;
			value_type result_ = generator(point_, freq_, permutations);
			value_type range_ = value_type(1);
			value_type amplitude_ = value_type(1);
			value_type lacunarity_ = fractal_info.GetLacunarity();
			value_type gain_ = fractal_info.GetGain();
			for (std::size_t octave_ = 1, end_ = fractal_info.GetOctaves(); octave_ < end_; ++octave_)
			{
				freq_ *= lacunarity_;
				amplitude_ *= gain_;
				range_ += amplitude_;
				result_ += generator(point_, freq_, permutations) * amplitude_;
			}
			return result_ / range_;
		}

		fractal_info_type fractal_info;
		generator_type generator;
		EmuMath::NoisePermutations permutations;
		value_type freq;
	};
}

#endif
