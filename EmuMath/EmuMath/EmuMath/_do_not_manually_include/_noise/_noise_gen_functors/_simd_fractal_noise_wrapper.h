#ifndef EMU_MATH_FAST_FRACTAL_NOISE_WRAPPER_H_INC_
#define EMU_MATH_FAST_FRACTAL_NOISE_WRAPPER_H_INC_ 1

#include "_fractal_noise_wrapper.h"
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
			using register_type = EmuCore::TMP::remove_ref_cv_t<Register_>;
			using integral_register_type = typename EmuSIMD::TMP::register_as_integral<register_type>::type;
			/// <summary> Float if __m128, __m256, or __m512 is the register type. Otherwise double, due to implied __m128d, __m256d, or __m512d. </summary>
			using value_type = std::conditional_t
			<
				EmuCore::TMP::is_any_comparison_true<std::is_same, register_type, EmuSIMD::f32x4, EmuSIMD::f32x8, EmuSIMD::f32x16>::value,
				float,
				double
			>;
			using fractal_info_type = EmuMath::Info::FractalNoiseInfo<value_type>;

			static_assert
			(
				EmuCore::TMP::is_any_comparison_true<std::is_same, register_type, EmuSIMD::f32x4, EmuSIMD::f32x8, EmuSIMD::f32x16, EmuSIMD::f64x2, EmuSIMD::f64x4, EmuSIMD::f64x8>::value,
				"Invalid register type provided for a fast_fractal_noise_wrapper. Valid register types: __m128, __m256, __m512, __m128d, __m256d, __m512d."
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
				permutation_mask_simd(EmuSIMD::set1<integral_register_type>(permutations_.HighestStoredValue())),
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
				permutation_mask_simd(EmuSIMD::set1<integral_register_type>(permutations_.HighestStoredValue())),
				fractal_info(fractal_info_),
				permutations(permutations_),
				generator(generator_constructor_args_...)
			{
			}

			[[nodiscard]] constexpr inline register_type operator()(register_type points_x_, register_type points_y_, register_type points_z_)
			{
				constexpr bool is_valid_for_3d = std::is_invocable_r_v
				<
					register_type,
					generator_type,
					register_type, register_type, register_type, register_type, integral_register_type, EmuMath::NoisePermutations
				>;
				if constexpr (is_valid_for_3d)
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
								EmuSIMD::mul_all(generator(points_x_, points_y_, points_z_, active_freq_, permutation_mask_simd, permutations), amplitude_)
							);
							++octave_;
						} while (octave_ < end_);
						return EmuSIMD::div(result_, range_);
					}
					else
					{
						return generator(points_x_, points_y_, points_z_, starting_freq_simd, permutation_mask_simd, permutations);
					}
				}
				else
				{
					static_assert
					(
						EmuCore::TMP::get_false<generator_type>(),
						"Invalid generator type provided for a fast_fractal_noise_wrapper when invoked with 3 coordinate registers. The generator must return the provided register type, and take the following type arguments: register_type, register_type, register_type, register_type, integral_register_type, EmuMath::NoisePermutations, interpreted as: `points_x`, `points_y`, `points_z`, `freq`, `permutation_mask`, `permutations`"
					);
				}
			}
			[[nodiscard]] constexpr inline register_type operator()(register_type points_x_, register_type points_y_)
			{
				constexpr bool is_valid_for_2d = std::is_invocable_r_v
				<
					register_type,
					generator_type,
					register_type, register_type, register_type, integral_register_type, EmuMath::NoisePermutations
				>;
				if constexpr (is_valid_for_2d)
				{
					std::size_t end_ = fractal_info.GetOctaves();
					if (1 < end_)
					{
						std::size_t octave_ = 1;
						register_type range_ = EmuSIMD::set1<register_type>(1);
						register_type amplitude_ = range_;
						register_type active_freq_ = starting_freq_simd;
						register_type result_ = generator(points_x_, points_y_, active_freq_, permutation_mask_simd, permutations);
						do
						{
							active_freq_ = EmuSIMD::mul_all(active_freq_, lacunarity_simd);
							amplitude_ = EmuSIMD::mul_all(amplitude_, gain_simd);
							range_ = EmuSIMD::add(range_, amplitude_);
							result_ = EmuSIMD::add
							(
								result_,
								EmuSIMD::mul_all(generator(points_x_, points_y_, active_freq_, permutation_mask_simd, permutations), amplitude_)
							);
							++octave_;
						} while (octave_ < end_);
						return EmuSIMD::div(result_, range_);
					}
					else
					{
						return generator(points_x_, points_y_, starting_freq_simd, permutation_mask_simd, permutations);
					}
				}
				else
				{
					static_assert
					(
						EmuCore::TMP::get_false<generator_type>(),
						"Invalid generator type provided for a fast_fractal_noise_wrapper when invoked with 2 coordinate registers. The generator must return the provided register type, and take the following type arguments: register_type, register_type, register_type, integral_register_type, EmuMath::NoisePermutations, interpreted as: `points_x`, `points_y`, `freq`, `permutation_mask`, `permutations`"
					);
				}
			}
			[[nodiscard]] constexpr inline register_type operator()(register_type points_x_)
			{
				constexpr bool is_valid_for_1d = std::is_invocable_r_v
				<
					register_type,
					generator_type,
					register_type, register_type, integral_register_type, EmuMath::NoisePermutations
				>;
				if constexpr (is_valid_for_1d)
				{
					std::size_t end_ = fractal_info.GetOctaves();
					if (1 < end_)
					{
						std::size_t octave_ = 1;
						register_type range_ = EmuSIMD::set1<register_type>(1);
						register_type amplitude_ = range_;
						register_type active_freq_ = starting_freq_simd;
						register_type result_ = generator(points_x_, active_freq_, permutation_mask_simd, permutations);
						do
						{
							active_freq_ = EmuSIMD::mul_all(active_freq_, lacunarity_simd);
							amplitude_ = EmuSIMD::mul_all(amplitude_, gain_simd);
							range_ = EmuSIMD::add(range_, amplitude_);
							result_ = EmuSIMD::add
							(
								result_,
								EmuSIMD::mul_all(generator(points_x_, active_freq_, permutation_mask_simd, permutations), amplitude_)
							);
							++octave_;
						} while (octave_ < end_);
						return EmuSIMD::div(result_, range_);
					}
					else
					{
						return generator(points_x_, starting_freq_simd, permutation_mask_simd, permutations);
					}
				}
				else
				{
					static_assert
					(
						EmuCore::TMP::get_false<generator_type>(),
						"Invalid generator type provided for a fast_fractal_noise_wrapper when invoked with 1 coordinate register. The generator must return the provided register type, and take the following type arguments: register_type, register_type, integral_register_type, EmuMath::NoisePermutations, interpreted as: `points_x`, `freq`, `permutation_mask`, `permutations`"
					);
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


	template<class PerIterationGenerator_, EmuConcepts::KnownSIMD SIMD32>
		requires((EmuSIMD::TMP::is_floating_point_simd_register_v<SIMD32>) && (EmuSIMD::TMP::floating_point_register_element_width_v<SIMD32> == 32))
	struct no_fractal_noise_wrapper<PerIterationGenerator_, SIMD32>
	{
		using generator_type = PerIterationGenerator_;
		using value_type = typename std::remove_cvref<SIMD32>::type;
		using integer_type = typename EmuSIMD::TMP::register_as_integral<value_type>::type;
		using register_arg_type = typename EmuSIMD::TMP::register_as_arg_type<value_type>::type;
		static constexpr std::size_t per_element_width = 32;

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
			permutations_mask_128 = _mm_set1_epi32(static_cast<std::int32_t>(permutations.HighestStoredValue()));
		}
		template<typename...GeneratorConstructorArgs_, typename = std::enable_if_t<std::is_constructible_v<generator_type, GeneratorConstructorArgs_...>>>
		no_fractal_noise_wrapper
		(
			float freq_,
			EmuMath::NoisePermutations&& permutations_,
			GeneratorConstructorArgs_&&...generator_constructor_args_
		) :
			freq(EmuSIMD::set1<value_type, per_element_width>(freq_)),
			permutations(permutations_),
			generator(generator_constructor_args_...)
		{
			permutations_mask_128 = EmuSIMD::set1<integer_type, per_element_width>(static_cast<std::int32_t>(permutations.HighestStoredValue()));
		}

		[[nodiscard]] inline value_type operator()(register_arg_type points_x_, register_arg_type points_y_, register_arg_type points_z_)
		{
			constexpr bool is_valid_for_3d = std::is_invocable_r_v
			<
				value_type,
				generator_type,
				value_type, value_type, value_type, value_type, integer_type, EmuMath::NoisePermutations
			>;
			if constexpr (is_valid_for_3d)
			{
				return generator(points_x_, points_y_, points_z_, freq, permutations_mask_128, permutations);
			}
			else
			{
				static_assert
				(
					EmuCore::TMP::get_false<generator_type>(),
					"Invalid generator type provided for a no_fractal_noise_wrapper taking __m128 values when invoked with 3 coordinate registers. The generator must return the __m128 type, and take the following type arguments: __m128, __m128, __m128, __m128, __m128i, EmuMath::NoisePermutations, interpreted as: `points_x`, `points_y`, `points_z`, `freq`, `permutation_mask`, `permutations`"
				);
			}
		}
		[[nodiscard]] inline value_type operator()(register_arg_type points_x_, register_arg_type points_y_)
		{
			constexpr bool is_valid_for_2d = std::is_invocable_r_v
			<
				value_type,
				generator_type,
				value_type, value_type, value_type, integer_type, EmuMath::NoisePermutations
			>;
			if constexpr (is_valid_for_2d)
			{
				return generator(points_x_, points_y_, freq, permutations_mask_128, permutations);
			}
			else
			{
				static_assert
				(
					EmuCore::TMP::get_false<generator_type>(),
					"Invalid generator type provided for a no_fractal_noise_wrapper taking __m128 values when invoked with 2 coordinate registers. The generator must return the __m128 type, and take the following type arguments: __m128, __m128, __m128, __m128i, EmuMath::NoisePermutations, interpreted as: `points_x`, `points_y`, `freq`, `permutation_mask`, `permutations`"
				);
			}
		}
		[[nodiscard]] inline value_type operator()(register_arg_type points_x_)
		{
			constexpr bool is_valid_for_1d = std::is_invocable_r_v
			<
				value_type,
				generator_type,
				value_type, value_type, integer_type, EmuMath::NoisePermutations
			>;
			if constexpr (is_valid_for_1d)
			{
				return generator(points_x_, freq, permutations_mask_128, permutations);
			}
			else
			{
				static_assert
				(
					EmuCore::TMP::get_false<generator_type>(),
					"Invalid generator type provided for a no_fractal_noise_wrapper taking __m128 values when invoked with 1 coordinate register. The generator must return the __m128 type, and take the following type arguments: __m128, __m128, __m128i, EmuMath::NoisePermutations, interpreted as: `points_x`, `freq`, `permutation_mask`, `permutations`"
				);
			}
		}

		generator_type generator;
		EmuMath::NoisePermutations permutations;
		integer_type permutations_mask_128;
		value_type freq;
	};

	template<class PerIterationGenerator_, EmuConcepts::KnownSIMD SIMDRegister_>
	requires((EmuSIMD::TMP::is_floating_point_simd_register_v<SIMDRegister_>))
	struct fractal_noise_wrapper<PerIterationGenerator_, SIMDRegister_> : 
		public _underlying_implementations::_fast_fractal_noise_wrapper<PerIterationGenerator_, typename std::remove_cvref<SIMDRegister_>::type>
	{
	private:
		using parent_type = _underlying_implementations::_fast_fractal_noise_wrapper<PerIterationGenerator_, typename std::remove_cvref<SIMDRegister_>::type>;

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
