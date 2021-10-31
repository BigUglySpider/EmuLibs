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

	template<class Register_, std::int64_t StartingVal_, template<class Lhs__, class Rhs__> class PerItemFuncTemplate_, bool Reverse_, std::size_t PerElementWidthIfInt_ = 32>
	[[nodiscard]] inline Register_ _set_from_starting_value()
	{
		using register_type_uq = typename EmuCore::TMPHelpers::remove_ref_cv<Register_>::type;
		if constexpr (EmuMath::SIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			using PerItemFunc_ = PerItemFuncTemplate_<std::int64_t, std::int64_t>;
			constexpr PerItemFunc_ func_ = PerItemFunc_();

			if constexpr (EmuCore::TMPHelpers::is_any_comparison_true<std::is_same, register_type_uq, __m128, __m256, __m512>::value)
			{
				constexpr float val_0_ = static_cast<float>(StartingVal_);
				constexpr float val_1_ = static_cast<float>(func_(StartingVal_, 1));
				constexpr float val_2_ = static_cast<float>(func_(StartingVal_, 2));
				constexpr float val_3_ = static_cast<float>(func_(StartingVal_, 3));

				if constexpr (std::is_same_v<register_type_uq, __m128>)
				{
					if constexpr (Reverse_)
					{
						return _mm_setr_ps(val_0_, val_1_, val_2_, val_3_);
					}
					else
					{
						return _mm_set_ps(val_0_, val_1_, val_2_, val_3_);
					}

				}
				else
				{
					constexpr float val_4_ = static_cast<float>(func_(StartingVal_, 4));
					constexpr float val_5_ = static_cast<float>(func_(StartingVal_, 5));
					constexpr float val_6_ = static_cast<float>(func_(StartingVal_, 6));
					constexpr float val_7_ = static_cast<float>(func_(StartingVal_, 7));

					if constexpr (std::is_same_v<register_type_uq, __m256>)
					{
						if constexpr (Reverse_)
						{
							return _mm256_setr_ps(val_0_, val_1_, val_2_, val_3_, val_4_, val_5_, val_6_, val_7_);
						}
						else
						{
							return _mm256_set_ps(val_0_, val_1_, val_2_, val_3_, val_4_, val_5_, val_6_, val_7_);
						}
					}
					else
					{
						constexpr float val_8_ = static_cast<float>(func_(StartingVal_, 8));
						constexpr float val_9_ = static_cast<float>(func_(StartingVal_, 9));
						constexpr float val_10_ = static_cast<float>(func_(StartingVal_, 10));
						constexpr float val_11_ = static_cast<float>(func_(StartingVal_, 11));
						constexpr float val_12_ = static_cast<float>(func_(StartingVal_, 12));
						constexpr float val_13_ = static_cast<float>(func_(StartingVal_, 13));
						constexpr float val_14_ = static_cast<float>(func_(StartingVal_, 14));
						constexpr float val_15_ = static_cast<float>(func_(StartingVal_, 15));

						if constexpr (Reverse_)
						{
							return _mm512_setr_ps
							(
								val_0_, val_1_, val_2_, val_3_, val_4_, val_5_, val_6_, val_7_,
								val_8_, val_9_, val_10_, val_11_, val_12_, val_13_, val_14_, val_15_
							);
						}
						else
						{
							return _mm512_set_ps
							(
								val_0_, val_1_, val_2_, val_3_, val_4_, val_5_, val_6_, val_7_,
								val_8_, val_9_, val_10_, val_11_, val_12_, val_13_, val_14_, val_15_
							);
						}
					}
				}
			}
			else if constexpr (EmuCore::TMPHelpers::is_any_comparison_true<std::is_same, register_type_uq, __m128d, __m256d, __m512d>::value)
			{
				constexpr double val_0_ = static_cast<double>(StartingVal_);
				constexpr double val_1_ = static_cast<double>(func_(StartingVal_, 1));

				if constexpr (std::is_same_v<register_type_uq, __m128d>)
				{
					if constexpr (Reverse_)
					{
						return _mm_setr_pd(val_0_, val_1_);
					}
					else
					{
						return _mm_set_pd(val_0_, val_1_);
					}
				}
				else
				{
					constexpr double val_2_ = static_cast<double>(func_(StartingVal_, 2));
					constexpr double val_3_ = static_cast<double>(func_(StartingVal_, 3));

					if constexpr (std::is_same_v<register_type_uq, __m256d>)
					{
						if constexpr (Reverse_)
						{
							return _mm256_setr_pd(val_0_, val_1_, val_2_, val_3_);
						}
						else
						{
							return _mm256_set_pd(val_0_, val_1_, val_2_, val_3_);
						}
					}
					else
					{
						constexpr double val_4_ = static_cast<double>(func_(StartingVal_, 4));
						constexpr double val_5_ = static_cast<double>(func_(StartingVal_, 5));
						constexpr double val_6_ = static_cast<double>(func_(StartingVal_, 6));
						constexpr double val_7_ = static_cast<double>(func_(StartingVal_, 7));

						if constexpr (Reverse_)
						{
							return _mm512_setr_pd(val_0_, val_1_, val_2_, val_3_, val_4_, val_5_, val_6_, val_7_);
						}
						else
						{
							return _mm512_set_pd(val_0_, val_1_, val_2_, val_3_, val_4_, val_5_, val_6_, val_7_);
						}
					}
				}
			}
			else if constexpr (EmuCore::TMPHelpers::is_any_comparison_true<std::is_same, register_type_uq, __m128i, __m256i, __m512i>::value)
			{
				if constexpr (EmuMath::SIMD::TMP::_assert_valid_simd_int_element_width<PerElementWidthIfInt_>())
				{
					if constexpr (PerElementWidthIfInt_ == 8)
					{
						constexpr std::int8_t val_0_ = static_cast<std::int8_t>(StartingVal_);
						constexpr std::int8_t val_1_ = static_cast<std::int8_t>(func_(StartingVal_, 1));
						constexpr std::int8_t val_2_ = static_cast<std::int8_t>(func_(StartingVal_, 2));
						constexpr std::int8_t val_3_ = static_cast<std::int8_t>(func_(StartingVal_, 3));
						constexpr std::int8_t val_4_ = static_cast<std::int8_t>(func_(StartingVal_, 4));
						constexpr std::int8_t val_5_ = static_cast<std::int8_t>(func_(StartingVal_, 5));
						constexpr std::int8_t val_6_ = static_cast<std::int8_t>(func_(StartingVal_, 6));
						constexpr std::int8_t val_7_ = static_cast<std::int8_t>(func_(StartingVal_, 7));
						constexpr std::int8_t val_8_ = static_cast<std::int8_t>(func_(StartingVal_, 8));
						constexpr std::int8_t val_9_ = static_cast<std::int8_t>(func_(StartingVal_, 9));
						constexpr std::int8_t val_10_ = static_cast<std::int8_t>(func_(StartingVal_, 10));
						constexpr std::int8_t val_11_ = static_cast<std::int8_t>(func_(StartingVal_, 11));
						constexpr std::int8_t val_12_ = static_cast<std::int8_t>(func_(StartingVal_, 12));
						constexpr std::int8_t val_13_ = static_cast<std::int8_t>(func_(StartingVal_, 13));
						constexpr std::int8_t val_14_ = static_cast<std::int8_t>(func_(StartingVal_, 14));
						constexpr std::int8_t val_15_ = static_cast<std::int8_t>(func_(StartingVal_, 15));

						if constexpr (std::is_same_v<register_type_uq, __m128i>)
						{
							if constexpr (Reverse_)
							{
								return _mm_setr_epi8
								(
									val_0_, val_1_, val_2_, val_3_, val_4_, val_5_, val_6_, val_7_,
									val_8_, val_9_, val_10_, val_11_, val_12_, val_13_, val_14_, val_15_
								);
							}
							else
							{
								return _mm_set_epi8
								(
									val_0_, val_1_, val_2_, val_3_, val_4_, val_5_, val_6_, val_7_,
									val_8_, val_9_, val_10_, val_11_, val_12_, val_13_, val_14_, val_15_
								);
							}
						}
						else
						{
							constexpr std::int8_t val_16_ = static_cast<std::int8_t>(func_(StartingVal_, 16));
							constexpr std::int8_t val_17_ = static_cast<std::int8_t>(func_(StartingVal_, 17));
							constexpr std::int8_t val_18_ = static_cast<std::int8_t>(func_(StartingVal_, 18));
							constexpr std::int8_t val_19_ = static_cast<std::int8_t>(func_(StartingVal_, 19));
							constexpr std::int8_t val_20_ = static_cast<std::int8_t>(func_(StartingVal_, 20));
							constexpr std::int8_t val_21_ = static_cast<std::int8_t>(func_(StartingVal_, 21));
							constexpr std::int8_t val_22_ = static_cast<std::int8_t>(func_(StartingVal_, 22));
							constexpr std::int8_t val_23_ = static_cast<std::int8_t>(func_(StartingVal_, 23));
							constexpr std::int8_t val_24_ = static_cast<std::int8_t>(func_(StartingVal_, 24));
							constexpr std::int8_t val_25_ = static_cast<std::int8_t>(func_(StartingVal_, 25));
							constexpr std::int8_t val_26_ = static_cast<std::int8_t>(func_(StartingVal_, 26));
							constexpr std::int8_t val_27_ = static_cast<std::int8_t>(func_(StartingVal_, 27));
							constexpr std::int8_t val_28_ = static_cast<std::int8_t>(func_(StartingVal_, 28));
							constexpr std::int8_t val_29_ = static_cast<std::int8_t>(func_(StartingVal_, 29));
							constexpr std::int8_t val_30_ = static_cast<std::int8_t>(func_(StartingVal_, 30));
							constexpr std::int8_t val_31_ = static_cast<std::int8_t>(func_(StartingVal_, 31));

							if constexpr (std::is_same_v<register_type_uq, __m256i>)
							{
								if constexpr (Reverse_)
								{
									return _mm256_setr_epi8
									(
										val_0_, val_1_, val_2_, val_3_, val_4_, val_5_, val_6_, val_7_,
										val_8_, val_9_, val_10_, val_11_, val_12_, val_13_, val_14_, val_15_,
										val_16_, val_17_, val_18_, val_19_, val_20_, val_21_, val_22_, val_23_,
										val_24_, val_25_, val_26_, val_27_, val_28_, val_29_, val_30_, val_31_
									);
								}
								else
								{
									return _mm256_set_epi8
									(
										val_0_, val_1_, val_2_, val_3_, val_4_, val_5_, val_6_, val_7_,
										val_8_, val_9_, val_10_, val_11_, val_12_, val_13_, val_14_, val_15_,
										val_16_, val_17_, val_18_, val_19_, val_20_, val_21_, val_22_, val_23_,
										val_24_, val_25_, val_26_, val_27_, val_28_, val_29_, val_30_, val_31_
									);
								}
							}
							else
							{
								constexpr std::int8_t val_32_ = static_cast<std::int8_t>(func_(StartingVal_, 32));
								constexpr std::int8_t val_33_ = static_cast<std::int8_t>(func_(StartingVal_, 33));
								constexpr std::int8_t val_34_ = static_cast<std::int8_t>(func_(StartingVal_, 34));
								constexpr std::int8_t val_35_ = static_cast<std::int8_t>(func_(StartingVal_, 35));
								constexpr std::int8_t val_36_ = static_cast<std::int8_t>(func_(StartingVal_, 36));
								constexpr std::int8_t val_37_ = static_cast<std::int8_t>(func_(StartingVal_, 37));
								constexpr std::int8_t val_38_ = static_cast<std::int8_t>(func_(StartingVal_, 38));
								constexpr std::int8_t val_39_ = static_cast<std::int8_t>(func_(StartingVal_, 39));
								constexpr std::int8_t val_40_ = static_cast<std::int8_t>(func_(StartingVal_, 40));
								constexpr std::int8_t val_41_ = static_cast<std::int8_t>(func_(StartingVal_, 41));
								constexpr std::int8_t val_42_ = static_cast<std::int8_t>(func_(StartingVal_, 42));
								constexpr std::int8_t val_43_ = static_cast<std::int8_t>(func_(StartingVal_, 43));
								constexpr std::int8_t val_44_ = static_cast<std::int8_t>(func_(StartingVal_, 44));
								constexpr std::int8_t val_45_ = static_cast<std::int8_t>(func_(StartingVal_, 45));
								constexpr std::int8_t val_46_ = static_cast<std::int8_t>(func_(StartingVal_, 46));
								constexpr std::int8_t val_47_ = static_cast<std::int8_t>(func_(StartingVal_, 47));
								constexpr std::int8_t val_48_ = static_cast<std::int8_t>(func_(StartingVal_, 48));
								constexpr std::int8_t val_49_ = static_cast<std::int8_t>(func_(StartingVal_, 49));
								constexpr std::int8_t val_50_ = static_cast<std::int8_t>(func_(StartingVal_, 50));
								constexpr std::int8_t val_51_ = static_cast<std::int8_t>(func_(StartingVal_, 51));
								constexpr std::int8_t val_52_ = static_cast<std::int8_t>(func_(StartingVal_, 52));
								constexpr std::int8_t val_53_ = static_cast<std::int8_t>(func_(StartingVal_, 53));
								constexpr std::int8_t val_54_ = static_cast<std::int8_t>(func_(StartingVal_, 54));
								constexpr std::int8_t val_55_ = static_cast<std::int8_t>(func_(StartingVal_, 55));
								constexpr std::int8_t val_56_ = static_cast<std::int8_t>(func_(StartingVal_, 56));
								constexpr std::int8_t val_57_ = static_cast<std::int8_t>(func_(StartingVal_, 57));
								constexpr std::int8_t val_58_ = static_cast<std::int8_t>(func_(StartingVal_, 58));
								constexpr std::int8_t val_59_ = static_cast<std::int8_t>(func_(StartingVal_, 59));
								constexpr std::int8_t val_60_ = static_cast<std::int8_t>(func_(StartingVal_, 60));
								constexpr std::int8_t val_61_ = static_cast<std::int8_t>(func_(StartingVal_, 61));
								constexpr std::int8_t val_62_ = static_cast<std::int8_t>(func_(StartingVal_, 62));
								constexpr std::int8_t val_63_ = static_cast<std::int8_t>(func_(StartingVal_, 63));

								if constexpr (Reverse_)
								{
									return _mm512_setr_epi8
									(
										val_0_, val_1_, val_2_, val_3_, val_4_, val_5_, val_6_, val_7_,
										val_8_, val_9_, val_10_, val_11_, val_12_, val_13_, val_14_, val_15_,
										val_16_, val_17_, val_18_, val_19_, val_20_, val_21_, val_22_, val_23_,
										val_24_, val_25_, val_26_, val_27_, val_28_, val_29_, val_30_, val_31_,
										val_32_, val_33_, val_34_, val_35_, val_36_, val_37_, val_38_, val_39_,
										val_40_, val_41_, val_42_, val_43_, val_44_, val_45_, val_46_, val_47_,
										val_48_, val_49_, val_50_, val_51_, val_52_, val_53_, val_54_, val_55_,
										val_56_, val_57_, val_58_, val_59_, val_60_, val_61_, val_62_, val_63_
									);
								}
								else
								{
									return _mm512_set_epi8
									(
										val_0_, val_1_, val_2_, val_3_, val_4_, val_5_, val_6_, val_7_,
										val_8_, val_9_, val_10_, val_11_, val_12_, val_13_, val_14_, val_15_,
										val_16_, val_17_, val_18_, val_19_, val_20_, val_21_, val_22_, val_23_,
										val_24_, val_25_, val_26_, val_27_, val_28_, val_29_, val_30_, val_31_,
										val_32_, val_33_, val_34_, val_35_, val_36_, val_37_, val_38_, val_39_,
										val_40_, val_41_, val_42_, val_43_, val_44_, val_45_, val_46_, val_47_,
										val_48_, val_49_, val_50_, val_51_, val_52_, val_53_, val_54_, val_55_,
										val_56_, val_57_, val_58_, val_59_, val_60_, val_61_, val_62_, val_63_
									);
								}
							}
						}
					}
					else if constexpr (PerElementWidthIfInt_ == 16)
					{
						constexpr std::int16_t val_0_ = static_cast<std::int16_t>(StartingVal_);
						constexpr std::int16_t val_1_ = static_cast<std::int16_t>(func_(StartingVal_, 1));
						constexpr std::int16_t val_2_ = static_cast<std::int16_t>(func_(StartingVal_, 2));
						constexpr std::int16_t val_3_ = static_cast<std::int16_t>(func_(StartingVal_, 3));
						constexpr std::int16_t val_4_ = static_cast<std::int16_t>(func_(StartingVal_, 4));
						constexpr std::int16_t val_5_ = static_cast<std::int16_t>(func_(StartingVal_, 5));
						constexpr std::int16_t val_6_ = static_cast<std::int16_t>(func_(StartingVal_, 6));
						constexpr std::int16_t val_7_ = static_cast<std::int16_t>(func_(StartingVal_, 7));

						if constexpr (std::is_same_v<register_type_uq, __m128i>)
						{
							if constexpr (Reverse_)
							{
								return _mm_setr_epi16(val_0_, val_1_, val_2_, val_3_, val_4_, val_5_, val_6_, val_7_);
							}
							else
							{
								return _mm_set_epi16(val_0_, val_1_, val_2_, val_3_, val_4_, val_5_, val_6_, val_7_);
							}
						}
						else
						{
							constexpr std::int16_t val_8_ = static_cast<std::int16_t>(func_(StartingVal_, 8));
							constexpr std::int16_t val_9_ = static_cast<std::int16_t>(func_(StartingVal_, 9));
							constexpr std::int16_t val_10_ = static_cast<std::int16_t>(func_(StartingVal_, 10));
							constexpr std::int16_t val_11_ = static_cast<std::int16_t>(func_(StartingVal_, 11));
							constexpr std::int16_t val_12_ = static_cast<std::int16_t>(func_(StartingVal_, 12));
							constexpr std::int16_t val_13_ = static_cast<std::int16_t>(func_(StartingVal_, 13));
							constexpr std::int16_t val_14_ = static_cast<std::int16_t>(func_(StartingVal_, 14));
							constexpr std::int16_t val_15_ = static_cast<std::int16_t>(func_(StartingVal_, 15));

							if constexpr (std::is_same_v<register_type_uq, __m256i>)
							{
								if constexpr (Reverse_)
								{
									return _mm256_setr_epi16
									(
										val_0_, val_1_, val_2_, val_3_, val_4_, val_5_, val_6_, val_7_,
										val_8_, val_9_, val_10_, val_11_, val_12_, val_13_, val_14_, val_15_
									);
								}
								else
								{
									return _mm256_set_epi16
									(
										val_0_, val_1_, val_2_, val_3_, val_4_, val_5_, val_6_, val_7_,
										val_8_, val_9_, val_10_, val_11_, val_12_, val_13_, val_14_, val_15_
									);
								}
							}
							else
							{
								constexpr std::int16_t val_16_ = static_cast<std::int16_t>(func_(StartingVal_, 16));
								constexpr std::int16_t val_17_ = static_cast<std::int16_t>(func_(StartingVal_, 17));
								constexpr std::int16_t val_18_ = static_cast<std::int16_t>(func_(StartingVal_, 18));
								constexpr std::int16_t val_19_ = static_cast<std::int16_t>(func_(StartingVal_, 19));
								constexpr std::int16_t val_20_ = static_cast<std::int16_t>(func_(StartingVal_, 20));
								constexpr std::int16_t val_21_ = static_cast<std::int16_t>(func_(StartingVal_, 21));
								constexpr std::int16_t val_22_ = static_cast<std::int16_t>(func_(StartingVal_, 22));
								constexpr std::int16_t val_23_ = static_cast<std::int16_t>(func_(StartingVal_, 23));
								constexpr std::int16_t val_24_ = static_cast<std::int16_t>(func_(StartingVal_, 24));
								constexpr std::int16_t val_25_ = static_cast<std::int16_t>(func_(StartingVal_, 25));
								constexpr std::int16_t val_26_ = static_cast<std::int16_t>(func_(StartingVal_, 26));
								constexpr std::int16_t val_27_ = static_cast<std::int16_t>(func_(StartingVal_, 27));
								constexpr std::int16_t val_28_ = static_cast<std::int16_t>(func_(StartingVal_, 28));
								constexpr std::int16_t val_29_ = static_cast<std::int16_t>(func_(StartingVal_, 29));
								constexpr std::int16_t val_30_ = static_cast<std::int16_t>(func_(StartingVal_, 30));
								constexpr std::int16_t val_31_ = static_cast<std::int16_t>(func_(StartingVal_, 31));

								if constexpr (Reverse_)
								{
									return _mm512_setr_epi16
									(
										val_0_, val_1_, val_2_, val_3_, val_4_, val_5_, val_6_, val_7_,
										val_8_, val_9_, val_10_, val_11_, val_12_, val_13_, val_14_, val_15_,
										val_16_, val_17_, val_18_, val_19_, val_20_, val_21_, val_22_, val_23_,
										val_24_, val_25_, val_26_, val_27_, val_28_, val_29_, val_30_, val_31_
									);
								}
								else
								{
									return _mm512_set_epi16
									(
										val_0_, val_1_, val_2_, val_3_, val_4_, val_5_, val_6_, val_7_,
										val_8_, val_9_, val_10_, val_11_, val_12_, val_13_, val_14_, val_15_,
										val_16_, val_17_, val_18_, val_19_, val_20_, val_21_, val_22_, val_23_,
										val_24_, val_25_, val_26_, val_27_, val_28_, val_29_, val_30_, val_31_
									);
								}
							}
						}
					}
					else if constexpr (PerElementWidthIfInt_ == 32)
					{
						constexpr std::int32_t val_0_ = static_cast<std::int32_t>(StartingVal_);
						constexpr std::int32_t val_1_ = static_cast<std::int32_t>(func_(StartingVal_, 1));
						constexpr std::int32_t val_2_ = static_cast<std::int32_t>(func_(StartingVal_, 2));
						constexpr std::int32_t val_3_ = static_cast<std::int32_t>(func_(StartingVal_, 3));

						if constexpr (std::is_same_v<register_type_uq, __m128i>)
						{
							if constexpr (Reverse_)
							{
								return _mm_setr_epi32(val_0_, val_1_, val_2_, val_3_);
							}
							else
							{
								return _mm_set_epi32(val_0_, val_1_, val_2_, val_3_);
							}
						}
						else
						{
							constexpr std::int32_t val_4_ = static_cast<std::int32_t>(func_(StartingVal_, 4));
							constexpr std::int32_t val_5_ = static_cast<std::int32_t>(func_(StartingVal_, 5));
							constexpr std::int32_t val_6_ = static_cast<std::int32_t>(func_(StartingVal_, 6));
							constexpr std::int32_t val_7_ = static_cast<std::int32_t>(func_(StartingVal_, 7));

							if constexpr (std::is_same_v<register_type_uq, __m256i>)
							{
								if constexpr (Reverse_)
								{
									return _mm256_setr_epi32(val_0_, val_1_, val_2_, val_3_, val_4_, val_5_, val_6_, val_7_);
								}
								else
								{
									return _mm256_set_epi32(val_0_, val_1_, val_2_, val_3_, val_4_, val_5_, val_6_, val_7_);
								}
							}
							else
							{
								constexpr std::int32_t val_8_ = static_cast<std::int32_t>(func_(StartingVal_, 8));
								constexpr std::int32_t val_9_ = static_cast<std::int32_t>(func_(StartingVal_, 9));
								constexpr std::int32_t val_10_ = static_cast<std::int32_t>(func_(StartingVal_, 10));
								constexpr std::int32_t val_11_ = static_cast<std::int32_t>(func_(StartingVal_, 11));
								constexpr std::int32_t val_12_ = static_cast<std::int32_t>(func_(StartingVal_, 12));
								constexpr std::int32_t val_13_ = static_cast<std::int32_t>(func_(StartingVal_, 13));
								constexpr std::int32_t val_14_ = static_cast<std::int32_t>(func_(StartingVal_, 14));
								constexpr std::int32_t val_15_ = static_cast<std::int32_t>(func_(StartingVal_, 15));

								if constexpr (Reverse_)
								{
									return _mm512_setr_epi32
									(
										val_0_, val_1_, val_2_, val_3_, val_4_, val_5_, val_6_, val_7_,
										val_8_, val_9_, val_10_, val_11_, val_12_, val_13_, val_14_, val_15_
									);
								}
								else
								{
									return _mm512_set_epi32
									(
										val_0_, val_1_, val_2_, val_3_, val_4_, val_5_, val_6_, val_7_,
										val_8_, val_9_, val_10_, val_11_, val_12_, val_13_, val_14_, val_15_
									);
								}
							}
						}
					}
					else
					{
						constexpr std::int64_t val_0_ = static_cast<std::int64_t>(StartingVal_);
						constexpr std::int64_t val_1_ = static_cast<std::int64_t>(func_(StartingVal_, 1));

						if constexpr (std::is_same_v<register_type_uq, __m128i>)
						{
							if constexpr (Reverse_)
							{
								return _mm_setr_epi64x(val_0_, val_1_);
							}
							else
							{
								return _mm_set_epi64x(val_0_, val_1_);
							}
						}
						else
						{
							constexpr std::int64_t val_2_ = static_cast<std::int64_t>(func_(StartingVal_, 2));
							constexpr std::int64_t val_3_ = static_cast<std::int64_t>(func_(StartingVal_, 3));

							if constexpr (std::is_same_v<register_type_uq, __m256i>)
							{
								if constexpr (Reverse_)
								{
									return _mm256_setr_epi64x(val_0_, val_1_, val_2_, val_3_);
								}
								else
								{
									return _mm256_set_epi64x(val_0_, val_1_, val_2_, val_3_);
								}
							}
							else
							{
								constexpr std::int64_t val_4_ = static_cast<std::int64_t>(func_(StartingVal_, 4));
								constexpr std::int64_t val_5_ = static_cast<std::int64_t>(func_(StartingVal_, 5));
								constexpr std::int64_t val_6_ = static_cast<std::int64_t>(func_(StartingVal_, 6));
								constexpr std::int64_t val_7_ = static_cast<std::int64_t>(func_(StartingVal_, 7));

								if constexpr (Reverse_)
								{
									return _mm512_setr_epi64x(val_0_, val_1_, val_2_, val_3_, val_4_, val_5_, val_6_, val_7_);
								}
								else
								{
									return _mm512_set_epi64x(val_0_, val_1_, val_2_, val_3_, val_4_, val_5_, val_6_, val_7_);
								}
							}
						}
					}
				}
				else
				{
					static_assert(false, "Attempted to set an integral SIMD register with a progressively modified value via EmuMath SIMD helpers, but the provided bit-width per element is invalid.");
				}
			}
			else
			{
				static_assert(false, "Attempted to set a SIMD register with a progressively modified value via EmuMath SIMD helpers, but the provided SIMD register is not supported for this feature.");
			}
		}
		else
		{
			static_assert(false, "Attempted to set a SIMD register with a progressively modified value via EmuMath SIMD helpers, but the provided type was not a SIMD register type, or was not a supported SIMD type.");
		}
	}
}

#endif
