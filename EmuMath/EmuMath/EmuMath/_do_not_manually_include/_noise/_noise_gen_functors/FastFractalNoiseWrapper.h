#ifndef EMU_MATH_FAST_FRACTAL_NOISE_WRAPPER_H_INC_
#define EMU_MATH_FAST_FRACTAL_NOISE_WRAPPER_H_INC_ 1

#include "FractalNoiseWrapper.h"
#include "../../../../EmuSIMD/SIMDHelpers.h"

namespace EmuMath::Functors
{
	namespace _underlying_implementations
	{
		template<class PerIterationGenerator_, class Register_>
		struct _fast_fractal_noise_wrapper
		{
		public:
			using generator_type = PerIterationGenerator_;
			using register_type = EmuCore::TMPHelpers::remove_ref_cv_t<Register_>;
			using integral_register_type = typename EmuSIMD::TMP::integer_register_type<EmuSIMD::TMP::simd_register_width_v<register_type>>::type;
			/// <summary> Float if __m128, __m256, or __m512 is the register type. Otherwise double, due to implied __m128d, __m256d, or __m512d. </summary>
			using value_type = std::conditional_t
			<
				EmuCore::TMPHelpers::is_any_comparison_true<std::is_same, register_type, __m128, __m256, __m512>::value,
				float,
				double
			>;
			using fractal_info_type = EmuMath::Info::FractalNoiseInfo<value_type>;

			static_assert
			(
				EmuCore::TMPHelpers::is_any_comparison_true<std::is_same, register_type, __m128, __m256, __m512, __m128d, __m256d, __m512d>::value,
				"Invalid register type provided for a fast_fractal_noise_wrapper. Valid register types: __m128, __m256, __m512, __m128d, __m256d, __m512d."
			);
			static_assert
			(
				std::is_invocable_r_v
				<
					register_type,
					generator_type,
					register_type, register_type, register_type, register_type, integral_register_type, EmuMath::NoisePermutations
				>,
				"Invalid generator type provided for a fast_fractal_noise_wrapper. The generator must return the provided register type, and take the following type arguments: register_type, register_type, register_type, register_type, integral_register_type, EmuMath::NoisePermutations"
			);

			template<typename...GeneratorConstructorArgs_, typename = std::enable_if_t<std::is_constructible_v<generator_type, GeneratorConstructorArgs_...>>>
			inline _fast_fractal_noise_wrapper
			(
				value_type freq_,
				const EmuMath::NoisePermutations& permutations_,
				const fractal_info_type& fractal_info_,
				GeneratorConstructorArgs_&&...generator_constructor_args_
			) :
				starting_freq_simd(EmuSIMD::set1<register_type>(freq_)),
				lacunarity_simd(EmuSIMD::set1<register_type>(fractal_info_.GetLacunarity())),
				gain_simd(EmuSIMD::set1<register_type>(fractal_info_.GetGain())),
				permutation_mask_simd(EmuSIMD::set1<integral_register_type>(permutations_.MaxValue())),
				fractal_info(fractal_info_),
				permutations(permutations_),
				generator(generator_constructor_args_...)
			{
			}
			template<typename...GeneratorConstructorArgs_, typename = std::enable_if_t<std::is_constructible_v<generator_type, GeneratorConstructorArgs_...>>>
			inline _fast_fractal_noise_wrapper
			(
				value_type freq_,
				EmuMath::NoisePermutations&& permutations_,
				const fractal_info_type& fractal_info_,
				GeneratorConstructorArgs_&&...generator_constructor_args_
			) :
				starting_freq_simd(EmuSIMD::set1<register_type>(freq_)),
				lacunarity_simd(EmuSIMD::set1<register_type>(fractal_info_.GetLacunarity())),
				gain_simd(EmuSIMD::set1<register_type>(fractal_info_.GetGain())),
				permutation_mask_simd(EmuSIMD::set1<integral_register_type>(permutations_.MaxValue())),
				fractal_info(fractal_info_),
				permutations(permutations_),
				generator(generator_constructor_args_...)
			{
			}

			[[nodiscard]] constexpr inline register_type operator()(register_type points_x_, register_type points_y_, register_type points_z_)
			{
				std::size_t end_ = fractal_info.GetOctaves();
				if (1 < end_)
				{
					std::size_t octave_ = 1;
					register_type range_ = EmuSIMD::set1<register_type>(1);
					register_type amplitude_ = range_;
					register_type active_freq_ = starting_freq_simd;
					register_type result_ = generator(points_x_, points_y_, points_z_, active_freq_, permutation_mask_simd, permutations);
					do
					{
						active_freq_ = EmuSIMD::mul_all(active_freq_, lacunarity_simd);
						amplitude_ = EmuSIMD::mul_all(amplitude_, gain_simd);
						range_ = EmuSIMD::add(range_, amplitude_);
						result_ = EmuSIMD::add
						(
							result_,
							EmuSIMD::mul(generator(points_x_, points_y_, points_z_, active_freq_, permutation_mask_simd, permutations), amplitude_)
						);
						++octave_;
					} while(octave_ < end_);
					return EmuSIMD::div(result_, range_);
				}
				else
				{
					return generator(points_x_, points_y_, points_z_, starting_freq_simd, permutation_mask_simd, permutations);
				}
			}

		private:
			register_type starting_freq_simd;
			register_type lacunarity_simd;
			register_type gain_simd;
			integral_register_type permutation_mask_simd;
			fractal_info_type fractal_info;
			EmuMath::NoisePermutations permutations;
			generator_type generator;
		};
	}


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
	struct no_fractal_noise_wrapper<PerIterationGenerator_, __m256>
	{
		using generator_type = PerIterationGenerator_;
		using value_type = __m256;

		template<typename...GeneratorConstructorArgs_, typename = std::enable_if_t<std::is_constructible_v<generator_type, GeneratorConstructorArgs_...>>>
		no_fractal_noise_wrapper
		(
			float freq_,
			const EmuMath::NoisePermutations& permutations_,
			GeneratorConstructorArgs_&&...generator_constructor_args_
		) :
			freq(EmuSIMD::set1<__m256>(freq_)),
			permutations(permutations_),
			generator(generator_constructor_args_...)
		{
			permutations_mask = EmuSIMD::set1<__m256i, 32>(permutations.MaxValue());
		}
		template<typename...GeneratorConstructorArgs_, typename = std::enable_if_t<std::is_constructible_v<generator_type, GeneratorConstructorArgs_...>>>
		no_fractal_noise_wrapper
		(
			float freq_,
			EmuMath::NoisePermutations&& permutations_,
			GeneratorConstructorArgs_&&...generator_constructor_args_
		) :
			freq(EmuSIMD::set1<__m256>(freq_)),
			permutations(permutations_),
			generator(generator_constructor_args_...)
		{
			permutations_mask = EmuSIMD::set1<__m256i, 32>(permutations.MaxValue());
		}

		[[nodiscard]] inline __m256 operator()(__m256 points_x_, __m256 points_y_, __m256 points_z_)
		{
			return generator(points_x_, points_y_, points_z_, freq, permutations_mask, permutations);
		}

		generator_type generator;
		EmuMath::NoisePermutations permutations;
		__m256i permutations_mask;
		__m256 freq;
	};

	template<class PerIterationGenerator_>
	struct fractal_noise_wrapper<PerIterationGenerator_, __m128> : public _underlying_implementations::_fast_fractal_noise_wrapper<PerIterationGenerator_, __m128>
	{
	private:
		using parent_type = _underlying_implementations::_fast_fractal_noise_wrapper<PerIterationGenerator_, __m128>;

	public:
		template<typename...GeneratorConstructorArgs_, typename = std::enable_if_t<std::is_constructible_v<typename parent_type::generator_type, GeneratorConstructorArgs_...>>>
		inline fractal_noise_wrapper
		(
			typename parent_type::value_type freq_,
			const EmuMath::NoisePermutations& permutations_,
			const typename parent_type::fractal_info_type& fractal_info_,
			GeneratorConstructorArgs_&&...generator_constructor_args_
		) : parent_type(freq_, permutations_, fractal_info_, generator_constructor_args_...)
		{
		}
		template<typename...GeneratorConstructorArgs_, typename = std::enable_if_t<std::is_constructible_v<typename parent_type::generator_type, GeneratorConstructorArgs_...>>>
		inline fractal_noise_wrapper
		(
			typename parent_type::value_type freq_,
			EmuMath::NoisePermutations&& permutations_,
			const typename parent_type::fractal_info_type& fractal_info_,
			GeneratorConstructorArgs_&&...generator_constructor_args_
		) : parent_type(freq_, permutations_, fractal_info_, generator_constructor_args_...)
		{
		}
	};

	template<class PerIterationGenerator_>
	struct fractal_noise_wrapper<PerIterationGenerator_, __m256> : public _underlying_implementations::_fast_fractal_noise_wrapper<PerIterationGenerator_, __m256>
	{
	private:
		using parent_type = _underlying_implementations::_fast_fractal_noise_wrapper<PerIterationGenerator_, __m256>;

	public:
		template<typename...GeneratorConstructorArgs_, typename = std::enable_if_t<std::is_constructible_v<typename parent_type::generator_type, GeneratorConstructorArgs_...>>>
		inline fractal_noise_wrapper
		(
			typename parent_type::value_type freq_,
			const EmuMath::NoisePermutations& permutations_,
			const typename parent_type::fractal_info_type& fractal_info_,
			GeneratorConstructorArgs_&&...generator_constructor_args_
		) : parent_type(freq_, permutations_, fractal_info_, generator_constructor_args_...)
		{
		}
		template<typename...GeneratorConstructorArgs_, typename = std::enable_if_t<std::is_constructible_v<typename parent_type::generator_type, GeneratorConstructorArgs_...>>>
		inline fractal_noise_wrapper
		(
			typename parent_type::value_type freq_,
			EmuMath::NoisePermutations&& permutations_,
			const typename parent_type::fractal_info_type& fractal_info_,
			GeneratorConstructorArgs_&&...generator_constructor_args_
		) : parent_type(freq_, permutations_, fractal_info_, generator_constructor_args_...)
		{
		}
	};
}

#endif
