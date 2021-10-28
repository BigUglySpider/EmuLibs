#ifndef EMU_MATH_FAST_FRACTAL_NOISE_WRAPPER_H_INC_
#define EMU_MATH_FAST_FRACTAL_NOISE_WRAPPER_H_INC_ 1

#include "FractalNoiseWrapper.h"
#include "../../../SIMDHelpers.h"

namespace EmuMath::Functors
{
	template<class PerIterationGenerator_>
	struct no_fractal_noise_wrapper<PerIterationGenerator_, __m128>
	{
		using generator_type = PerIterationGenerator_;
		using value_type = __m128;

		template<typename...GeneratorConstructorArgs_, typename = std::enable_if_t<std::is_constructible_v<generator_type, GeneratorConstructorArgs_...>>>
		no_fractal_noise_wrapper
		(
			float freq_,
			const EmuMath::NoisePermutations& permutations_,
			GeneratorConstructorArgs_&&...generator_constructor_args_
		) :
			freq(_mm_set1_ps(freq_)),
			permutations(permutations_),
			generator(generator_constructor_args_...)
		{
			permutations_mask_128 = _mm_set1_epi32(static_cast<std::int32_t>(permutations.MaxValue()));
		}
		template<typename...GeneratorConstructorArgs_, typename = std::enable_if_t<std::is_constructible_v<generator_type, GeneratorConstructorArgs_...>>>
		no_fractal_noise_wrapper
		(
			float freq_,
			EmuMath::NoisePermutations&& permutations_,
			GeneratorConstructorArgs_&&...generator_constructor_args_
		) :
			freq(_mm_set1_ps(freq_)),
			permutations(permutations_),
			generator(generator_constructor_args_...)
		{
			permutations_mask_128 = _mm_set1_epi32(static_cast<std::int32_t>(permutations.MaxValue()));
		}

		[[nodiscard]] inline __m128 operator()(__m128 points_x_, __m128 points_y_, __m128 points_z_)
		{
			return generator(points_x_, points_y_, points_z_, freq, permutations_mask_128, permutations);
		}

		generator_type generator;
		EmuMath::NoisePermutations permutations;
		__m128i permutations_mask_128;
		__m128 freq;
	};

	template<class PerIterationGenerator_>
	struct fractal_noise_wrapper<PerIterationGenerator_, __m128>
	{
	public:
		using generator_type = PerIterationGenerator_;
		using value_type = __m128;
		using fractal_info_type = EmuMath::Info::FractalNoiseInfo<float>;

		template<typename...GeneratorConstructorArgs_, typename = std::enable_if_t<std::is_constructible_v<generator_type, GeneratorConstructorArgs_...>>>
		fractal_noise_wrapper
		(
			float freq_,
			const EmuMath::NoisePermutations& permutations_,
			const fractal_info_type& fractal_info_,
			GeneratorConstructorArgs_&&...generator_constructor_args_
		) :
			starting_freq_128(_mm_broadcast_ss(&freq_)),
			lacunarity_128(_mm_set1_ps(fractal_info.GetLacunarity())),
			gain_128(_mm_set1_ps(fractal_info.GetGain())),
			fractal_info(fractal_info_),
			permutations(permutations_),
			generator(generator_constructor_args_...)
		{
			permutations_mask_128 = _mm_set1_epi32(static_cast<std::int32_t>(permutations.MaxValue()));
		}
		template<typename...GeneratorConstructorArgs_, typename = std::enable_if_t<std::is_constructible_v<generator_type, GeneratorConstructorArgs_...>>>
		fractal_noise_wrapper
		(
			float freq_,
			EmuMath::NoisePermutations&& permutations_,
			const fractal_info_type& fractal_info_,
			GeneratorConstructorArgs_&&...generator_constructor_args_
		) :
			starting_freq_128(_mm_broadcast_ss(&freq_)),
			lacunarity_128(_mm_set1_ps(fractal_info.GetLacunarity())),
			gain_128(_mm_set1_ps(fractal_info.GetGain())),
			fractal_info(fractal_info_),
			permutations(permutations_),
			generator(generator_constructor_args_...)
		{
			permutations_mask_128 = _mm_set1_epi32(static_cast<std::int32_t>(permutations.MaxValue()));
		}

		constexpr inline __m128 operator()(__m128 points_x_, __m128 points_y_, __m128 points_z_)
		{
			__m128 result_ = generator(points_x_, points_y_, points_z_, starting_freq_128, permutations_mask_128, permutations);
			std::size_t end_ = fractal_info.GetOctaves();
			if (1 < end_)
			{
				std::size_t octave_ = 1;
				__m128 modified_freq_ = starting_freq_128;
				__m128 range_ = _mm_set1_ps(1.0f);
				__m128 amplitude_ = range_;

				do
				{
					modified_freq_ = _mm_mul_ps(modified_freq_, lacunarity_128);
					amplitude_ = _mm_mul_ps(amplitude_, gain_128);
					range_ = _mm_add_ps(range_, amplitude_);
					result_ = _mm_add_ps
					(
						result_, 
						_mm_mul_ps(generator(points_x_, points_y_, points_z_, modified_freq_, permutations_mask_128, permutations), amplitude_)
					);
					++octave_;
				} while(octave_ < end_);
				return _mm_div_ps(result_, range_);
			}
			else
			{
				return result_;
			}
		}

		fractal_info_type fractal_info;
		generator_type generator;
		EmuMath::NoisePermutations permutations;
		__m128i permutations_mask_128;
		__m128 starting_freq_128;
		__m128 lacunarity_128;
		__m128 gain_128;
	};
}

#endif
