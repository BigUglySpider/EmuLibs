#ifndef EMU_MATH_SIMD_TEMPLATE_HELPERS_UNDERLYING_SET_H_INC_
#define EMU_MATH_SIMD_TEMPLATE_HELPERS_UNDERLYING_SET_H_INC_ 1

#include "_common_underlying_simd_template_helper_includes.h"

namespace EmuMath::SIMD::_underlying_simd_helpers
{
	template<class Register_, std::size_t ElementWidth_, typename...Args_>
	[[nodiscard]] inline Register_ _set_int(Args_&&...args_)
	{
		static_assert
		(
			EmuMath::SIMD::TMP::_assert_valid_simd_int_element_width<ElementWidth_>(),
			"Invalid ElementWidth_ provided when setting an integral SIMD register via EmuMath SIMD helpers."
		);
		using register_type_uq = typename EmuCore::TMPHelpers::remove_ref_cv<Register_>::type;
		constexpr std::size_t num_args_ = sizeof...(Args_);
		constexpr std::size_t register_width_ = EmuMath::SIMD::TMP::simd_register_width_v<register_type_uq>;
		constexpr std::size_t expected_num_args_ = register_width_ / ElementWidth_;
		using width_int = EmuCore::TMPHelpers::int_of_size_t<ElementWidth_ / 8>;

		if constexpr (!std::is_same_v<width_int, std::false_type>)
		{
			if constexpr (num_args_ == expected_num_args_)
			{
				if constexpr (EmuCore::TMPHelpers::are_all_convertible_v<width_int, Args_...>)
				{
					if constexpr (std::is_same_v<register_type_uq, __m128i>)
					{
						// 128-bit
						if constexpr (ElementWidth_ == 8)
						{
							return _mm_set_epi8(static_cast<width_int>(args_)...);
						}
						else if constexpr (ElementWidth_ == 16)
						{
							return _mm_set_epi16(static_cast<width_int>(args_)...);
						}
						else if constexpr (ElementWidth_ == 32)
						{
							return _mm_set_epi32(static_cast<width_int>(args_)...);
						}
						else
						{
							return _mm_set_epi64x(static_cast<width_int>(args_)...);
						}
					}
					else if constexpr (std::is_same_v<register_type_uq, __m256i>)
					{
						// 256-bit
						if constexpr (ElementWidth_ == 8)
						{
							return _mm256_set_epi8(static_cast<width_int>(args_)...);
						}
						else if constexpr (ElementWidth_ == 16)
						{
							return _mm256_set_epi16(static_cast<width_int>(args_)...);
						}
						else if constexpr (ElementWidth_ == 32)
						{
							return _mm256_set_epi32(static_cast<width_int>(args_)...);
						}
						else
						{
							return _mm256_set_epi64x(static_cast<width_int>(args_)...);
						}
					}
					else if constexpr (std::is_same_v<register_type_uq, __m512i>)
					{
						// 512-bit
						if constexpr (ElementWidth_ == 8)
						{
							return _mm512_set_epi8(static_cast<width_int>(args_)...);
						}
						else if constexpr (ElementWidth_ == 16)
						{
							return _mm512_set_epi16(static_cast<width_int>(args_)...);
						}
						else if constexpr (ElementWidth_ == 32)
						{
							return _mm512_set_epi32(static_cast<width_int>(args_)...);
						}
						else
						{
							return _mm512_set_epi64(static_cast<width_int>(args_)...);
						}
					}
					else
					{
						// UNSUPPORTED
						static_assert
						(
							false,
							"Attempted to set an integral SIMD register via EmuMath SIMD helpers, but the provided Register_ type was not a supported integral SIMD register."
						);
					}
				}
				else
				{
					static_assert(false, "Attempted to set an integral SIMD register via EmuMath SIMD helpers, but at least one provided argument could not be converted to the type being used to set the register.");
				}
			}
			else
			{
				static_assert(false, "Attempted to set an integral SIMD register via EmuMath SIMD helpers, but an invalid number of arguments was provided. The following argument counts are required, with element bit-widths contained in square parantheses []: (__m128i[8]: 16), (__m128i[16]: 8), (__m128i[32]: 4), (__m128i[64]: 2), (__m256i[8]: 32), (__m256i[16]: 16), (__m256i[32]: 8), (__m256i[64]: 4), (__m512i[8]: 64), (__m512i[16]: 32), (__m512i[32] : 16), (__m512i[64]: 8).");
			}
		}
		else
		{
			static_assert(false, "Attempted to set an integral SIMD register via EmuMath SIMD helpers, but a valid integral scalar type for set casts could not be determined.");
		}
	}

	template<class Register_, typename...Args_>
	[[nodiscard]] inline Register_ _set_fp(Args_&&...args_)
	{
		using register_type_uq = typename EmuCore::TMPHelpers::remove_ref_cv<Register_>::type;

		if constexpr (EmuCore::TMPHelpers::is_any_comparison_true<std::is_same, register_type_uq, __m128, __m256, __m512>::value)
		{
			// FLOAT
			constexpr std::size_t register_width_ = EmuMath::SIMD::TMP::simd_register_width_v<register_type_uq>;
			constexpr std::size_t num_args_ = sizeof...(Args_);
			constexpr std::size_t expected_num_args_ = register_width_ / 32;

			if constexpr (num_args_ == expected_num_args_)
			{
				if constexpr (EmuCore::TMPHelpers::are_all_convertible_v<float, Args_...>)
				{
					if constexpr (std::is_same_v<register_type_uq, __m128>)
					{
						return _mm_set_ps(static_cast<float>(args_)...);
					}
					else if constexpr (std::is_same_v<register_type_uq, __m256>)
					{
						return _mm256_set_ps(static_cast<float>(args_)...);
					}
					else
					{
						return _mm512_set_ps(static_cast<float>(args_)...);
					}
				}
				else
				{
					static_assert(false, "Attempted to set a SIMD float register via EmuMath SIMD helpers, but at least one provided argument was not convertible to `float`.");
				}
			}
			else
			{
				static_assert(false, "Attempted to set a SIMD float register via EmuMath SIMD helpers, but an invalid number of arguments was provided. The following argument counts are required: (__m128: 4), (__m256: 8), (__m512: 16).");
			}
		}
		else if constexpr (EmuCore::TMPHelpers::is_any_comparison_true<std::is_same, register_type_uq, __m128d, __m256d, __m512d>::value)
		{
			// DOUBLE
			constexpr std::size_t register_width_ = EmuMath::SIMD::TMP::simd_register_width_v<register_type_uq>;
			constexpr std::size_t num_args_ = sizeof...(Args_);
			constexpr std::size_t expected_num_args_ = register_width_ / 64;

			if constexpr (num_args_ == expected_num_args_)
			{
				if constexpr (EmuCore::TMPHelpers::are_all_convertible_v<double, Args_...>)
				{
					if constexpr (std::is_same_v<register_type_uq, __m128d>)
					{
						return _mm_set_pd(static_cast<double>(args_)...);
					}
					else if constexpr (std::is_same_v<register_type_uq, __m256d>)
					{
						return _mm256_set_pd(static_cast<double>(args_)...);
					}
					else
					{
						return _mm512_set_pd(static_cast<double>(args_)...);
					}
				}
				else
				{
					static_assert(false, "Attempted to set a SIMD double register via EmuMath SIMD helpers, but at least one provided argument was not convertible to `double`.");
				}
			}
			else
			{
				static_assert(false, "Attempted to set a SIMD double register via EmuMath SIMD helpers, but an invalid number of arguments was provided. The following argument counts are required: (__m128d: 2), (__m256d: 4), (__m512d: 8).");
			}
		}
		else
		{
			// UNSUPPORTED
			static_assert
			(
				false,
				"Attempted to set a floating-point SIMD register via EmuMath SIMD helpers, but the provided Register_ type was not a supported floating-point SIMD register."
			);
		}
	}

	template<class Register_>
	[[nodiscard]] inline Register_ _setzero()
	{
		using register_type_uq = typename EmuCore::TMPHelpers::remove_ref_cv<Register_>::type;
		if constexpr (EmuMath::SIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			if constexpr (std::is_same_v<register_type_uq, __m128>)
			{
				return _mm_setzero_ps();
			}
			else if constexpr (std::is_same_v<register_type_uq, __m256>)
			{
				return _mm256_setzero_ps();
			}
			else if constexpr (std::is_same_v<register_type_uq, __m512>)
			{
				return _mm512_setzero_ps();
			}
			else if constexpr (std::is_same_v<register_type_uq, __m128d>)
			{
				return _mm_setzero_pd();
			}
			else if constexpr (std::is_same_v<register_type_uq, __m256d>)
			{
				return _mm256_setzero_pd();
			}
			else if constexpr (std::is_same_v<register_type_uq, __m512d>)
			{
				return _mm512_setzero_pd();
			}
			else if constexpr (std::is_same_v<register_type_uq, __m128i>)
			{
				return _mm_setzero_si128();
			}
			else if constexpr (std::is_same_v<register_type_uq, __m256i>)
			{
				return _mm256_setzero_si256();
			}
			else if constexpr (std::is_same_v<register_type_uq, __m512i>)
			{
				return _mm512_setzero_si512();
			}
			else
			{
				static_assert(false, "Attempted to set a SIMD register to zero via EmuMath SIMD helpers, but the provided SIMD register is not supported for this feature.");
			}
		}
		else
		{
			static_assert(false, "Attempted to set a SIMD register to zero via EmuMath SIMD helpers, but the provided type was not a SIMD register type, or was not a supported SIMD type.");
		}
	}

	template<class Register_, std::size_t PerElementWidthIfInt_ = 32, typename Val_>
	[[nodiscard]] inline Register_ _set1(const Val_& val_)
	{
		using register_type_uq = typename EmuCore::TMPHelpers::remove_ref_cv<Register_>::type;
		if constexpr (EmuMath::SIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			if constexpr (EmuCore::TMPHelpers::is_any_comparison_true<std::is_same, register_type_uq, __m128, __m256, __m512>::value)
			{
				if constexpr (std::is_convertible_v<Val_, float>)
				{
					if constexpr (std::is_same_v<register_type_uq, __m128>)
					{
						return _mm_set1_ps(static_cast<float>(val_));
					}
					else if constexpr (std::is_same_v<register_type_uq, __m256>)
					{
						return _mm256_set1_ps(static_cast<float>(val_));
					}
					else
					{
						return _mm512_set1_ps(static_cast<float>(val_));
					}
				}
				else
				{
					static_assert(false, "Attempted to set a SIMD register of floats to the same value, but the provided Val_ was a type that cannot be converted to float.");
				}
			}
			else if constexpr (EmuCore::TMPHelpers::is_any_comparison_true<std::is_same, register_type_uq, __m128d, __m256d, __m512d>::value)
			{
				if constexpr (std::is_constructible_v<Val_, double>)
				{
					if constexpr (std::is_same_v<register_type_uq, __m128d>)
					{
						return _mm_set1_pd(static_cast<double>(val_));
					}
					else if constexpr (std::is_same_v<register_type_uq, __m256d>)
					{
						return _mm256_set1_pd(static_cast<double>(val_));
					}
					else
					{
						return _mm512_set1_pd(static_cast<double>(val_));
					}
				}
				else
				{
					static_assert(false, "Attempted to set a SIMD register of doubles to the same value, but the provided Val_ was a type that cannot be converted to double.");
				}
			}
			else if constexpr (EmuCore::TMPHelpers::is_any_comparison_true<std::is_same, register_type_uq, __m128i, __m256i, __m512i>::value)
			{
				if constexpr (EmuMath::SIMD::TMP::_assert_valid_simd_int_element_width<PerElementWidthIfInt_>())
				{
					using int_type = EmuCore::TMPHelpers::int_of_size_t<PerElementWidthIfInt_ / 8>;
					if constexpr (std::is_convertible_v<Val_, int_type>)
					{
						if constexpr (std::is_same_v<register_type_uq, __m128i>)
						{
							if constexpr (PerElementWidthIfInt_ == 8)
							{
								return _mm_set1_epi8(static_cast<int_type>(val_));
							}
							else if constexpr (PerElementWidthIfInt_ == 16)
							{
								return _mm_set1_epi16(static_cast<int_type>(val_));
							}
							else if constexpr (PerElementWidthIfInt_ == 32)
							{
								return _mm_set1_epi32(static_cast<int_type>(val_));
							}
							else
							{
								return _mm_set1_epi64x(static_cast<int_type>(val_));
							}
						}
						else if constexpr (std::is_same_v<register_type_uq, __m256i>)
						{
							if constexpr (PerElementWidthIfInt_ == 8)
							{
								return _mm256_set1_epi8(static_cast<int_type>(val_));
							}
							else if constexpr (PerElementWidthIfInt_ == 16)
							{
								return _mm256_set1_epi16(static_cast<int_type>(val_));
							}
							else if constexpr (PerElementWidthIfInt_ == 32)
							{
								return _mm256_set1_epi32(static_cast<int_type>(val_));
							}
							else
							{
								return _mm256_set1_epi64x(static_cast<int_type>(val_));
							}
						}
						else
						{
							if constexpr (PerElementWidthIfInt_ == 8)
							{
								return _mm512_set1_epi8(static_cast<int_type>(val_));
							}
							else if constexpr (PerElementWidthIfInt_ == 16)
							{
								return _mm512_set1_epi16(static_cast<int_type>(val_));
							}
							else if constexpr (PerElementWidthIfInt_ == 32)
							{
								return _mm512_set1_epi32(static_cast<int_type>(val_));
							}
							else
							{
								return _mm512_set1_epi64(static_cast<int_type>(val_));
							}
						}
					}
					else
					{
						static_assert(false, "Attempted to set an integral SIMD register with all elements at the same value via EmuMath SIMD helpers, but the provided value cannot be converted to an integer of the specified bit width.");
					}
				}
				else
				{
					static_assert(false, "Attempted to set an integral SIMD register with all elements at the same value via EmuMath SIMD helpers, but the provided per-element width is invalid.");
				}
			}
			else
			{
				static_assert(false, "Attempted to set a SIMD register with all elements at the same value via EmuMath SIMD helpers, but the provided SIMD register is not supported for this feature.");
			}
		}
		else
		{
			static_assert(false, "Attempted to set a SIMD register with all elements at the same value via EmuMath SIMD helpers, but the provided type was not a SIMD register type, or was not a supported SIMD type.");
		}
	}
}

#endif
