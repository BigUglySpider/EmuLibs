#ifndef EMU_MATH_SIMD_HELPERS_UNDERLYING_ARITHMETIC_H_INC_
#define EMU_MATH_SIMD_HELPERS_UNDERLYING_ARITHMETIC_H_INC_ 1

#include "_common_underlying_simd_template_helper_includes.h"

namespace EmuMath::SIMD::_underlying_simd_helpers
{
#pragma region ADDITION_FUNCS
	template<class Register_>
	[[nodiscard]] inline Register_ _add_fp(Register_ lhs_, Register_ rhs_)
	{
		using register_type_uq = typename EmuCore::TMPHelpers::remove_ref_cv<Register_>::type;
		if constexpr (EmuMath::SIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			if constexpr (std::is_same_v<register_type_uq, __m128>)
			{
				return _mm_add_ps(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, __m256>)
			{
				return _mm256_add_ps(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, __m512>)
			{
				return _mm512_add_ps(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, __m128d>)
			{
				return _mm_add_pd(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, __m256d>)
			{
				return _mm256_add_pd(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, __m512d>)
			{
				return _mm512_add_pd(lhs_, rhs_);
			}
			else
			{
				static_assert(false, "Attempted to perform addition of floating-point SIMD registers via EmuMath SIMD helpers, but the provided Register_ type was not a supported floating-point SIMD register.");
			}
		}
		else
		{
			static_assert(false, "Attempted to perform addition of floating-point SIMD registers via EmuMath SIMD helpers, but the provided Register_ type is not a supported SIMD register.");
		}
	}

	template<std::size_t PerElementWidth_, class Register_>
	[[nodiscard]] inline Register_ _add_int(Register_ lhs_, Register_ rhs_)
	{
		using register_type_uq = typename EmuCore::TMPHelpers::remove_ref_cv<Register_>::type;
		if constexpr (EmuMath::SIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			if constexpr (EmuMath::SIMD::TMP::_assert_valid_simd_int_element_width<PerElementWidth_>())
			{
				if constexpr (std::is_same_v<register_type_uq, __m128i>)
				{
					if constexpr (PerElementWidth_ == 8)
					{
						return _mm_add_epi8(lhs_, rhs_);
					}
					else if constexpr (PerElementWidth_ == 16)
					{
						return _mm_add_epi16(lhs_, rhs_);
					}
					else if constexpr (PerElementWidth_ == 32)
					{
						return _mm_add_epi32(lhs_, rhs_);
					}
					else
					{
						return _mm_add_epi64(lhs_, rhs_);
					}
				}
				else if constexpr (std::is_same_v<register_type_uq, __m256i>)
				{
					if constexpr (PerElementWidth_ == 8)
					{
						return _mm256_add_epi8(lhs_, rhs_);
					}
					else if constexpr (PerElementWidth_ == 16)
					{
						return _mm256_add_epi16(lhs_, rhs_);
					}
					else if constexpr (PerElementWidth_ == 32)
					{
						return _mm256_add_epi32(lhs_, rhs_);
					}
					else
					{
						return _mm256_add_epi64(lhs_, rhs_);
					}
				}
				else if constexpr (std::is_same_v<register_type_uq, __m512i>)
				{
					if constexpr (PerElementWidth_ == 8)
					{
						return _mm512_add_epi8(lhs_, rhs_);
					}
					else if constexpr (PerElementWidth_ == 16)
					{
						return _mm512_add_epi16(lhs_, rhs_);
					}
					else if constexpr (PerElementWidth_ == 32)
					{
						return _mm512_add_epi32(lhs_, rhs_);
					}
					else
					{
						return _mm512_add_epi64(lhs_, rhs_);
					}
				}
				else
				{
					static_assert(false, "Attempted to perform addition of integral SIMD registers via EmuMath SIMD helpers, but provided an unsupported integral SIMD register.");
				}
			}
			else
			{
				static_assert(false, "Attempted to perform addition of integral SIMD registers via EmuMath SIMD helpers, but provided an invalid PerElementWidth_.");
			}
		}
		else
		{
			static_assert(false, "Attempted to perform addition of integral SIMD registers via EmuMath SIMD helpers, but the provided Register_ type was not a supported integral SIMD register.");
		}
	}
#pragma endregion

#pragma region SUBTRACTION_FUNCS
	template<class Register_>
	[[nodiscard]] inline Register_ _sub_fp(Register_ lhs_, Register_ rhs_)
	{
		using register_type_uq = typename EmuCore::TMPHelpers::remove_ref_cv<Register_>::type;
		if constexpr (EmuMath::SIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			if constexpr (std::is_same_v<register_type_uq, __m128>)
			{
				return _mm_sub_ps(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, __m256>)
			{
				return _mm256_sub_ps(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, __m512>)
			{
				return _mm512_sub_ps(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, __m128d>)
			{
				return _mm_sub_pd(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, __m256d>)
			{
				return _mm256_sub_pd(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, __m512d>)
			{
				return _mm512_sub_pd(lhs_, rhs_);
			}
			else
			{
				static_assert(false, "Attempted to perform subtraction of floating-point SIMD registers via EmuMath SIMD helpers, but the provided Register_ type was not a supported floating-point SIMD register.");
			}
		}
		else
		{
			static_assert(false, "Attempted to perform subtraction of floating-point SIMD registers via EmuMath SIMD helpers, but the provided Register_ type is not a supported SIMD register.");
		}
	}

	template<std::size_t PerElementWidth_, class Register_>
	[[nodiscard]] inline Register_ _sub_int(Register_ lhs_, Register_ rhs_)
	{
		using register_type_uq = typename EmuCore::TMPHelpers::remove_ref_cv<Register_>::type;
		if constexpr (EmuMath::SIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			if constexpr (EmuMath::SIMD::TMP::_assert_valid_simd_int_element_width<PerElementWidth_>())
			{
				if constexpr (std::is_same_v<register_type_uq, __m128i>)
				{
					if constexpr (PerElementWidth_ == 8)
					{
						return _mm_sub_epi8(lhs_, rhs_);
					}
					else if constexpr (PerElementWidth_ == 16)
					{
						return _mm_sub_epi16(lhs_, rhs_);
					}
					else if constexpr (PerElementWidth_ == 32)
					{
						return _mm_sub_epi32(lhs_, rhs_);
					}
					else
					{
						return _mm_sub_epi64(lhs_, rhs_);
					}
				}
				else if constexpr (std::is_same_v<register_type_uq, __m256i>)
				{
					if constexpr (PerElementWidth_ == 8)
					{
						return _mm256_sub_epi8(lhs_, rhs_);
					}
					else if constexpr (PerElementWidth_ == 16)
					{
						return _mm256_sub_epi16(lhs_, rhs_);
					}
					else if constexpr (PerElementWidth_ == 32)
					{
						return _mm256_sub_epi32(lhs_, rhs_);
					}
					else
					{
						return _mm256_sub_epi64(lhs_, rhs_);
					}
				}
				else if constexpr (std::is_same_v<register_type_uq, __m512i>)
				{
					if constexpr (PerElementWidth_ == 8)
					{
						return _mm512_sub_epi8(lhs_, rhs_);
					}
					else if constexpr (PerElementWidth_ == 16)
					{
						return _mm512_sub_epi16(lhs_, rhs_);
					}
					else if constexpr (PerElementWidth_ == 32)
					{
						return _mm512_sub_epi32(lhs_, rhs_);
					}
					else
					{
						return _mm512_sub_epi64(lhs_, rhs_);
					}
				}
				else
				{
					static_assert(false, "Attempted to perform subtraction of integral SIMD registers via EmuMath SIMD helpers, but provided an unsupported integral SIMD register.");
				}
			}
			else
			{
				static_assert(false, "Attempted to perform subtraction of integral SIMD registers via EmuMath SIMD helpers, but provided an invalid PerElementWidth_.");
			}
		}
		else
		{
			static_assert(false, "Attempted to perform subtraction of integral SIMD registers via EmuMath SIMD helpers, but the provided Register_ type was not a supported integral SIMD register.");
		}
	}
#pragma endregion

#pragma region MULTIPLICATION_FUNCS
	template<class Register_>
	[[nodiscard]] inline Register_ _mul_fp(Register_ lhs_, Register_ rhs_)
	{
		using register_type_uq = typename EmuCore::TMPHelpers::remove_ref_cv<Register_>::type;
		if constexpr (EmuMath::SIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			if constexpr (std::is_same_v<register_type_uq, __m128>)
			{
				return _mm_mul_ps(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, __m256>)
			{
				return _mm256_mul_ps(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, __m512>)
			{
				return _mm512_mul_ps(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, __m128d>)
			{
				return _mm_mul_pd(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, __m256d>)
			{
				return _mm256_mul_pd(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, __m512d>)
			{
				return _mm512_mul_pd(lhs_, rhs_);
			}
			else
			{
				static_assert(false, "Attempted to perform multiplication of floating-point SIMD registers via EmuMath SIMD helpers, but the provided Register_ type was not a supported floating-point SIMD register.");
			}
		}
		else
		{
			static_assert(false, "Attempted to perform multiplication of floating-point SIMD registers via EmuMath SIMD helpers, but the provided Register_ type is not a supported SIMD register.");
		}
	}

	// UNIQUE CASE: Integer _mul_ operations are not per-element returns.
	// --- _mul_all_int can be used for similar behaviour to FP mutliplication
	template<bool Signed_, class Register_>
	[[nodiscard]] inline Register_ _mul_int(Register_ lhs_, Register_ rhs_)
	{
		using register_type_uq = typename EmuCore::TMPHelpers::remove_ref_cv<Register_>::type;
		if constexpr (EmuMath::SIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			if constexpr (std::is_same_v<register_type_uq, __m128i>)
			{
				if constexpr (Signed_)
				{
					return _mm_mul_epi32(lhs_, rhs_);
				}
				else
				{
					return _mm_mul_epu32(lhs_, rhs_);
				}
			}
			else if constexpr (std::is_same_v<register_type_uq, __m256i>)
			{
				if constexpr (Signed_)
				{
					return _mm256_mul_epi32(lhs_, rhs_);
				}
				else
				{
					return _mm256_mul_epu32(lhs_, rhs_);
				}
			}
			else if constexpr (std::is_same_v<register_type_uq, __m512i>)
			{
				if constexpr (Signed_)
				{
					return _mm512_mul_epi32(lhs_, rhs_);
				}
				else
				{
					return _mm512_mul_epu32(lhs_, rhs_);
				}
			}
			else
			{
				static_assert(false, "Attempted to perform multiplication of integral SIMD registers via EmuMath SIMD helpers, but provided an unsupported integral SIMD register.");
			}
		}
		else
		{
			static_assert(false, "Attempted to perform multiplication of integral SIMD registers via EmuMath SIMD helpers, but the provided Register_ type was not a supported integral SIMD register.");
		}
	}

	/// <summary> Performs correct _mullo_ SIMD operations, and emulates the behaviour for 8-bits if width is 8. </summary>
	template<std::size_t PerElementWidth_, class Register_>
	[[nodiscard]] inline Register_ _mullo_int(Register_ lhs_, Register_ rhs_)
	{
		using register_type_uq = typename EmuCore::TMPHelpers::remove_ref_cv<Register_>::type;
		if constexpr (EmuMath::SIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			if constexpr (EmuMath::SIMD::TMP::_assert_valid_simd_int_element_width<PerElementWidth_>())
			{
				if constexpr (std::is_same_v<register_type_uq, __m128i>)
				{
					if constexpr (PerElementWidth_ == 8)
					{
						__m128i out_even_ = _mm_mullo_epi16(lhs_, rhs_);
						__m128 out_odd_ = _mm_mullo_epi16(_mm_srli_epi16(lhs_, 8), _mm_srli_epi16(rhs_, 8));

						// Mask the least-significant 8 bits for even elements
						// --- Bits of odd elements are shifted so we only have the least significant bits available, which also places them in their output slot
						// --- This applies for other 8-bit _mullo_ implementations
						__m128 mask_ = _mm_set1_epi16(0xFF);
						return _mm_or_si128(_mm_slli_epi16(out_odd_, 8), _mm_and_si128(out_even_, mask_));
					}
					else if constexpr (PerElementWidth_ == 16)
					{
						return _mm_mullo_epi16(lhs_, rhs_);
					}
					else if constexpr (PerElementWidth_ == 32)
					{
						return _mm_mullo_epi32(lhs_, rhs_);
					}
					else
					{
						return _mm_mullo_epi64(lhs_, rhs_);
					}
				}
				else if constexpr (std::is_same_v<register_type_uq, __m256i>)
				{
					if constexpr (PerElementWidth_ == 8)
					{
						__m256i out_even_ = _mm256_mullo_epi16(lhs_, rhs_);
						__m256i out_odd_ = _mm256_mullo_epi16(_mm256_srli_epi16(lhs_, 8), _mm256_srli_epi16(rhs_, 8));
						__m256i mask_ = _mm256_set1_epi16(0xFF);
						return _mm256_or_si256(_mm256_slli_epi16(out_odd_, 8), _mm256_and_si256(out_even_, mask_));
					}
					else if constexpr (PerElementWidth_ == 16)
					{
						return _mm256_mullo_epi32(lhs_, rhs_);
					}
					else if constexpr (PerElementWidth_ == 32)
					{
						return _mm256_mullo_epi32(lhs_, rhs_);
					}
					else
					{
						return _mm256_mullo_epi64(lhs_, rhs_);
					}
				}
				else if constexpr (std::is_same_v<register_type_uq, __m512i>)
				{
					if constexpr (PerElementWidth_ == 8)
					{

					}
					else if constexpr (PerElementWidth_ == 16)
					{
						return _mm512_mullo_epi16(lhs_, rhs_);
					}
					else if constexpr (PerElementWidth_ == 32)
					{
						return _mm512_mullo_epi32(lhs_, rhs_);
					}
					else
					{
						return _mm512_mullo_epi64(lhs_, rhs_);
					}
				}
				else
				{
					static_assert(false, "Attempted to perform lo multiplication of integral SIMD registers via EmuMath SIMD helpers, but provided an unsupported integral SIMD register.");
				}
			}
			else
			{
				static_assert(false, "Attempted to perform lo multiplication of integral SIMD registers via EmuMath SIMD helpers, but provided an invalid PerElementWidth_.");
			}
		}
		else
		{
			static_assert(false, "Attempted to perform lo multiplication of integral SIMD registers via EmuMath SIMD helpers, but the provided Register_ type was not a supported integral SIMD register.");
		}
	}

	template<std::size_t PerElementWidth_, class Register_>
	[[nodiscard]] inline Register_ _mul_all_int(Register_ lhs_, Register_ rhs_)
	{
		using register_type_uq = typename EmuCore::TMPHelpers::remove_ref_cv<Register_>::type;
		if constexpr (EmuMath::SIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			if constexpr (EmuMath::SIMD::TMP::_assert_valid_simd_int_element_width<PerElementWidth_>())
			{
				if constexpr (EmuMath::SIMD::TMP::is_integral_simd_register_v<Register_>)
				{
					return _mullo_int<PerElementWidth_>(lhs_, rhs_);
				}
				else
				{
					static_assert(false, "Attempted to perform all-element multiplication of integral SIMD registers via EmuMath SIMD helpers, but provided a non-integral (or unsupported integral) SIMD register.");
				}
			}
			else
			{
				static_assert(false, "Attempted to perform all-element multiplication of integral SIMD registers via EmuMath SIMD helpers, but provided an invalid PerElementWidth_.");
			}
		}
		else
		{
			static_assert(false, "Attempted to perform all-element multiplication of integral SIMD registers via EmuMath SIMD helpers, but the provided Register_ type was not a supported integral SIMD register.");
		}
	}
#pragma endregion

#pragma region DIVISION_FUNCS
	template<class Register_>
	[[nodiscard]] inline Register_ _div_fp(Register_ lhs_, Register_ rhs_)
	{
		using register_type_uq = typename EmuCore::TMPHelpers::remove_ref_cv<Register_>::type;
		if constexpr (EmuMath::SIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			if constexpr (std::is_same_v<register_type_uq, __m128>)
			{
				return _mm_div_ps(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, __m256>)
			{
				return _mm256_div_ps(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, __m512>)
			{
				return _mm512_div_ps(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, __m128d>)
			{
				return _mm_div_pd(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, __m256d>)
			{
				return _mm256_div_pd(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, __m512d>)
			{
				return _mm512_div_pd(lhs_, rhs_);
			}
			else
			{
				static_assert(false, "Attempted to perform division of floating-point SIMD registers via EmuMath SIMD helpers, but the provided Register_ type was not a supported floating-point SIMD register.");
			}
		}
		else
		{
			static_assert(false, "Attempted to perform division of floating-point SIMD registers via EmuMath SIMD helpers, but the provided Register_ type is not a supported SIMD register.");
		}
	}

	template<std::size_t PerElementWidth_, bool Signed_, class Register_>
	[[nodiscard]] inline Register_ _div_int(Register_ lhs_, Register_ rhs_)
	{
		using register_type_uq = typename EmuCore::TMPHelpers::remove_ref_cv<Register_>::type;
		if constexpr (EmuMath::SIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			if constexpr (EmuMath::SIMD::TMP::_assert_valid_simd_int_element_width<PerElementWidth_>())
			{
				if constexpr (std::is_same_v<register_type_uq, __m128i>)
				{
					if constexpr (PerElementWidth_ == 8)
					{
						if constexpr (Signed_)
						{
							return _mm_div_epi8(lhs_, rhs_);
						}
						else
						{
							return _mm_div_epu8(lhs_, rhs_);
						}
					}
					else if constexpr (PerElementWidth_ == 16)
					{
						if constexpr (Signed_)
						{
							return _mm_div_epi16(lhs_, rhs_);
						}
						else
						{
							return _mm_div_epu16(lhs_, rhs_);
						}
					}
					else if constexpr (PerElementWidth_ == 32)
					{
						if constexpr (Signed_)
						{
							return _mm_div_epi32(lhs_, rhs_);
						}
						else
						{
							return _mm_div_epu32(lhs_, rhs_);
						}
					}
					else
					{
						if constexpr (Signed_)
						{
							return _mm_div_epi64(lhs_, rhs_);
						}
						else
						{
							return _mm_div_epu64(lhs_, rhs_);
						}
					}
				}
				else if constexpr (std::is_same_v<register_type_uq, __m256i>)
				{
					if constexpr (PerElementWidth_ == 8)
					{
						if constexpr (Signed_)
						{
							return _mm256_div_epi8(lhs_, rhs_);
						}
						else
						{
							return _mm256_div_epu8(lhs_, rhs_);
						}
					}
					else if constexpr (PerElementWidth_ == 16)
					{
						if constexpr (Signed_)
						{
							return _mm256_div_epi16(lhs_, rhs_);
						}
						else
						{
							return _mm256_div_epu16(lhs_, rhs_);
						}
					}
					else if constexpr (PerElementWidth_ == 32)
					{
						if constexpr (Signed_)
						{
							return _mm256_div_epi32(lhs_, rhs_);
						}
						else
						{
							return _mm256_div_epu32(lhs_, rhs_);
						}
					}
					else
					{
						if constexpr (Signed_)
						{
							return _mm256_div_epi64(lhs_, rhs_);
						}
						else
						{
							return _mm256_div_epu64(lhs_, rhs_);
						}
					}
				}
				else if constexpr (std::is_same_v<register_type_uq, __m512i>)
				{
					if constexpr (PerElementWidth_ == 8)
					{
						if constexpr (Signed_)
						{
							return _mm512_div_epi8(lhs_, rhs_);
						}
						else
						{
							return _mm512_div_epu8(lhs_, rhs_);
						}
					}
					else if constexpr (PerElementWidth_ == 16)
					{
						if constexpr (Signed_)
						{
							return _mm512_div_epi16(lhs_, rhs_);
						}
						else
						{
							return _mm512_div_epu16(lhs_, rhs_);
						}
					}
					else if constexpr (PerElementWidth_ == 32)
					{
						if constexpr (Signed_)
						{
							return _mm512_div_epi32(lhs_, rhs_);
						}
						else
						{
							return _mm512_div_epu32(lhs_, rhs_);
						}
					}
					else
					{
						if constexpr (Signed_)
						{
							return _mm512_div_epi64(lhs_, rhs_);
						}
						else
						{
							return _mm512_div_epu64(lhs_, rhs_);
						}
					}
				}
				else
				{
					static_assert(false, "Attempted to perform division of integral SIMD registers via EmuMath SIMD helpers, but provided an unsupported integral SIMD register.");
				}
			}
			else
			{
				static_assert(false, "Attempted to perform division of integral SIMD registers via EmuMath SIMD helpers, but provided an invalid PerElementWidth_.");
			}
		}
		else
		{
			static_assert(false, "Attempted to perform division of integral SIMD registers via EmuMath SIMD helpers, but the provided Register_ type was not a supported integral SIMD register.");
		}
	}
#pragma endregion
}

#endif
