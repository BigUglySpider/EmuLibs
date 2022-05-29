#ifndef EMU_SIMD_HELPERS_UNDERLYING_ARITHMETIC_H_INC_
#define EMU_SIMD_HELPERS_UNDERLYING_ARITHMETIC_H_INC_ 1

#include "_common_underlying_simd_template_helper_includes.h"
#include "_simd_helpers_underlying_bitwise.h"
#include "_simd_helpers_underlying_cmp.h"
#include "_simd_helpers_underlying_set.h"
#include "../../../../../EmuCore/TMPHelpers/Values.h"

namespace EmuSIMD::_underlying_simd_helpers
{
#pragma region ADDITION_FUNCS
	template<class Register_>
	[[nodiscard]] inline Register_ _add_fp(Register_ lhs_, Register_ rhs_)
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
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
				static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform addition of floating-point SIMD registers via EmuSIMD helpers, but the provided Register_ type was not a supported floating-point SIMD register.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform addition of floating-point SIMD registers via EmuSIMD helpers, but the provided Register_ type is not a supported SIMD register.");
		}
	}

	template<std::size_t PerElementWidth_, class Register_>
	[[nodiscard]] inline Register_ _add_int(Register_ lhs_, Register_ rhs_)
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			if constexpr (EmuSIMD::TMP::_assert_valid_simd_int_element_width<PerElementWidth_>())
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
					static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform addition of integral SIMD registers via EmuSIMD helpers, but provided an unsupported integral SIMD register.");
				}
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform addition of integral SIMD registers via EmuSIMD helpers, but provided an invalid PerElementWidth_.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform addition of integral SIMD registers via EmuSIMD helpers, but the provided Register_ type was not a supported integral SIMD register.");
		}
	}
#pragma endregion

#pragma region SUBTRACTION_FUNCS
	template<class Register_>
	[[nodiscard]] inline Register_ _sub_fp(Register_ lhs_, Register_ rhs_)
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
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
				static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform subtraction of floating-point SIMD registers via EmuSIMD helpers, but the provided Register_ type was not a supported floating-point SIMD register.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform subtraction of floating-point SIMD registers via EmuSIMD helpers, but the provided Register_ type is not a supported SIMD register.");
		}
	}

	template<std::size_t PerElementWidth_, class Register_>
	[[nodiscard]] inline Register_ _sub_int(Register_ lhs_, Register_ rhs_)
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			if constexpr (EmuSIMD::TMP::_assert_valid_simd_int_element_width<PerElementWidth_>())
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
					static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform subtraction of integral SIMD registers via EmuSIMD helpers, but provided an unsupported integral SIMD register.");
				}
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform subtraction of integral SIMD registers via EmuSIMD helpers, but provided an invalid PerElementWidth_.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform subtraction of integral SIMD registers via EmuSIMD helpers, but the provided Register_ type was not a supported integral SIMD register.");
		}
	}
#pragma endregion

#pragma region MULTIPLICATION_FUNCS
	template<class Register_>
	[[nodiscard]] inline Register_ _mul_fp(Register_ lhs_, Register_ rhs_)
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
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
				static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform multiplication of floating-point SIMD registers via EmuSIMD helpers, but the provided Register_ type was not a supported floating-point SIMD register.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform multiplication of floating-point SIMD registers via EmuSIMD helpers, but the provided Register_ type is not a supported SIMD register.");
		}
	}

	// UNIQUE CASE: Integer _mul_ operations are not per-element returns.
	// --- _mul_all_int can be used for similar behaviour to FP mutliplication
	template<bool Signed_, class Register_>
	[[nodiscard]] inline Register_ _mul_int(Register_ lhs_, Register_ rhs_)
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
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
				static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform multiplication of integral SIMD registers via EmuSIMD helpers, but provided an unsupported integral SIMD register.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform multiplication of integral SIMD registers via EmuSIMD helpers, but the provided Register_ type was not a supported integral SIMD register.");
		}
	}

	/// <summary> Performs correct _mullo_ SIMD operations, and emulates the behaviour for 8-bits if width is 8. </summary>
	template<std::size_t PerElementWidth_, class Register_>
	[[nodiscard]] inline Register_ _mullo_int(Register_ lhs_, Register_ rhs_)
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			if constexpr (EmuSIMD::TMP::_assert_valid_simd_int_element_width<PerElementWidth_>())
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
					static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform lo multiplication of integral SIMD registers via EmuSIMD helpers, but provided an unsupported integral SIMD register.");
				}
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform lo multiplication of integral SIMD registers via EmuSIMD helpers, but provided an invalid PerElementWidth_.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform lo multiplication of integral SIMD registers via EmuSIMD helpers, but the provided Register_ type was not a supported integral SIMD register.");
		}
	}

	template<std::size_t PerElementWidth_, class Register_>
	[[nodiscard]] inline Register_ _mul_all_int(Register_ lhs_, Register_ rhs_)
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			if constexpr (EmuSIMD::TMP::_assert_valid_simd_int_element_width<PerElementWidth_>())
			{
				if constexpr (EmuSIMD::TMP::is_integral_simd_register_v<Register_>)
				{
					return _mullo_int<PerElementWidth_>(lhs_, rhs_);
				}
				else
				{
					static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform all-element multiplication of integral SIMD registers via EmuSIMD helpers, but provided a non-integral (or unsupported integral) SIMD register.");
				}
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform all-element multiplication of integral SIMD registers via EmuSIMD helpers, but provided an invalid PerElementWidth_.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform all-element multiplication of integral SIMD registers via EmuSIMD helpers, but the provided Register_ type was not a supported integral SIMD register.");
		}
	}
#pragma endregion

#pragma region DIVISION_FUNCS
	template<class Register_>
	[[nodiscard]] inline Register_ _div_fp(Register_ lhs_, Register_ rhs_)
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
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
				static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform division of floating-point SIMD registers via EmuSIMD helpers, but the provided Register_ type was not a supported floating-point SIMD register.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform division of floating-point SIMD registers via EmuSIMD helpers, but the provided Register_ type is not a supported SIMD register.");
		}
	}

	template<std::size_t PerElementWidth_, bool Signed_, class Register_>
	[[nodiscard]] inline Register_ _div_int(Register_ lhs_, Register_ rhs_)
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			if constexpr (EmuSIMD::TMP::_assert_valid_simd_int_element_width<PerElementWidth_>())
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
					static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform division of integral SIMD registers via EmuSIMD helpers, but provided an unsupported integral SIMD register.");
				}
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform division of integral SIMD registers via EmuSIMD helpers, but provided an invalid PerElementWidth_.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform division of integral SIMD registers via EmuSIMD helpers, but the provided Register_ type was not a supported integral SIMD register.");
		}
	}
#pragma endregion

#pragma region MOD_FUNCS
	template<class Register_>
	[[nodiscard]] inline Register_ _mod_fp(Register_ lhs_, Register_ rhs_)
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			if constexpr (std::is_same_v<register_type_uq, __m128>)
			{
				__m128 res = _mm_div_ps(lhs_, rhs_);
				res = _mm_trunc_ps(res);
				return _mm_fnmadd_ps(res, rhs_, lhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, __m256>)
			{
				__m256 res = _mm256_div_ps(lhs_, rhs_);
				res = _mm256_trunc_ps(res);
				return _mm256_fnmadd_ps(res, rhs_, lhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, __m512>)
			{
				__m512 res = _mm512_div_ps(lhs_, rhs_);
				res = _mm512_trunc_ps(res);
				return _mm512_fnmadd_ps(res, rhs_, lhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, __m128d>)
			{
				__m128d res = _mm_div_pd(lhs_, rhs_);
				res = _mm_trunc_pd(res);
				return _mm_fnmadd_pd(res, rhs_, lhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, __m256d>)
			{
				__m256d res = _mm256_div_pd(lhs_, rhs_);
				res = _mm256_trunc_pd(res);
				return _mm256_fnmadd_pd(res, rhs_, lhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, __m512d>)
			{
				__m512d res = _mm512_div_pd(lhs_, rhs_);
				res = _mm512_trunc_pd(res);
				return _mm512_fnmadd_pd(res, rhs_, lhs_);
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform modulo division of floating-point SIMD registers via EmuSIMD helpers, but the provided Register_ type was not a supported floating-point SIMD register.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform modulo division of floating-point SIMD registers via EmuSIMD helpers, but the provided Register_ type is not a supported SIMD register.");
		}
	}

	template<std::size_t PerElementWidth_, bool Signed_, class Register_>
	[[nodiscard]] inline Register_ _rem_int(Register_ lhs_, Register_ rhs_)
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			if constexpr (EmuSIMD::TMP::_assert_valid_simd_int_element_width<PerElementWidth_>())
			{
				if constexpr (std::is_same_v<register_type_uq, __m128i>)
				{
					if constexpr (PerElementWidth_ == 8)
					{
						if constexpr (Signed_)
						{
							return _mm_rem_epi8(lhs_, rhs_);
						}
						else
						{
							return _mm_rem_epu8(lhs_, rhs_);
						}
					}
					else if constexpr (PerElementWidth_ == 16)
					{
						if constexpr (Signed_)
						{
							return _mm_rem_epi16(lhs_, rhs_);
						}
						else
						{
							return _mm_rem_epu16(lhs_, rhs_);
						}
					}
					else if constexpr (PerElementWidth_ == 32)
					{
						if constexpr (Signed_)
						{
							return _mm_rem_epi32(lhs_, rhs_);
						}
						else
						{
							return _mm_rem_epu32(lhs_, rhs_);
						}
					}
					else
					{
						if constexpr (Signed_)
						{
							return _mm_rem_epi64(lhs_, rhs_);
						}
						else
						{
							return _mm_rem_epu64(lhs_, rhs_);
						}
					}
				}
				else if constexpr (std::is_same_v<register_type_uq, __m256i>)
				{
					if constexpr (PerElementWidth_ == 8)
					{
						if constexpr (Signed_)
						{
							return _mm256_rem_epi8(lhs_, rhs_);
						}
						else
						{
							return _mm256_rem_epu8(lhs_, rhs_);
						}
					}
					else if constexpr (PerElementWidth_ == 16)
					{
						if constexpr (Signed_)
						{
							return _mm256_rem_epi16(lhs_, rhs_);
						}
						else
						{
							return _mm256_rem_epu16(lhs_, rhs_);
						}
					}
					else if constexpr (PerElementWidth_ == 32)
					{
						if constexpr (Signed_)
						{
							return _mm256_rem_epi32(lhs_, rhs_);
						}
						else
						{
							return _mm256_rem_epu32(lhs_, rhs_);
						}
					}
					else
					{
						if constexpr (Signed_)
						{
							return _mm256_rem_epi64(lhs_, rhs_);
						}
						else
						{
							return _mm256_rem_epu64(lhs_, rhs_);
						}
					}
				}
				else if constexpr (std::is_same_v<register_type_uq, __m512i>)
				{
					if constexpr (PerElementWidth_ == 8)
					{
						if constexpr (Signed_)
						{
							return _mm512_rem_epi8(lhs_, rhs_);
						}
						else
						{
							return _mm512_rem_epu8(lhs_, rhs_);
						}
					}
					else if constexpr (PerElementWidth_ == 16)
					{
						if constexpr (Signed_)
						{
							return _mm512_rem_epi16(lhs_, rhs_);
						}
						else
						{
							return _mm512_rem_epu16(lhs_, rhs_);
						}
					}
					else if constexpr (PerElementWidth_ == 32)
					{
						if constexpr (Signed_)
						{
							return _mm512_rem_epi32(lhs_, rhs_);
						}
						else
						{
							return _mm512_rem_epu32(lhs_, rhs_);
						}
					}
					else
					{
						if constexpr (Signed_)
						{
							return _mm512_rem_epi64(lhs_, rhs_);
						}
						else
						{
							return _mm512_rem_epu64(lhs_, rhs_);
						}
					}
				}
				else
				{
					static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform remainder division of integral SIMD registers via EmuSIMD helpers, but provided an unsupported integral SIMD register.");
				}
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform remainder division of integral SIMD registers via EmuSIMD helpers, but provided an invalid PerElementWidth_.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform remainder division of integral SIMD registers via EmuSIMD helpers, but the provided Register_ type was not a supported integral SIMD register.");
		}
	}

	template<std::size_t PerElementWidth_, bool Signed_, class Register_>
	[[nodiscard]] inline Register_ _mod_int(Register_ lhs_, Register_ rhs_)
	{
		return _rem_int<PerElementWidth_, Signed_, Register_>(lhs_, rhs_);
	}
#pragma endregion

#pragma region NEGATION_OPERATIONS
	template<std::size_t PerElementWidthIfInt_, class Register_>
	[[nodiscard]] inline Register_ _negate(Register_ register_)
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			if constexpr (EmuSIMD::TMP::is_floating_point_simd_register_v<register_type_uq>)
			{
				return _sub_fp(_setzero<register_type_uq>(), register_);
			}
			else if constexpr (EmuSIMD::TMP::is_integral_simd_register_v<register_type_uq>)
			{
				return _sub_int<PerElementWidthIfInt_>(_setzero<register_type_uq>(), register_);
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to negate a SIMD register via EmuSIMD helpers, but the provided SIMD register is not supported for this operation.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to negate a SIMD register via EmuSIMD helpers, but the provided Register_ type is not recognised as a support SIMD register.");
		}
	}
#pragma endregion

#pragma region ALTERNATING_OPERATIONS
	template<class Register_>
	[[nodiscard]] inline Register_ _addsub_fp(Register_ lhs_, Register_ rhs_)
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			if constexpr (std::is_same_v<register_type_uq, __m128>)
			{
				return _mm_addsub_ps(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, __m256>)
			{
				return _mm256_addsub_ps(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, __m128d>)
			{
				return _mm_addsub_pd(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, __m256d>)
			{
				return _mm256_addsub_pd(lhs_, rhs_);
			}
			else if constexpr (EmuCore::TMP::is_any_comparison_true<std::is_same, register_type_uq, __m512, __m512d>::value)
			{
				// Covers both __m512 and __m512d without needing any register-specific functionality thanks to previously created functions
				using mask_generator = _underlying_simd_helpers::_alternating_index_mask<register_type_uq, true>;
				if constexpr (_underlying_simd_helpers::_is_valid_alternating_index_mask_instance<mask_generator>::value)
				{
					register_type_uq mask_ = mask_generator::get();
					register_type_uq out_ = _add_fp(lhs_, _and(mask_, rhs_));
					return _sub_fp(out_, _andnot(mask_, rhs_));
				}
				else
				{
					static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to emulate add/subtract operation of two floating-point SIMD registers which do not have a built-in addsub operation, but a mask could not be successfully generated to perform alternating operations.");
				}
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to add/subtract (addsub) two SIMD registers via EmuSIMD helpers, but the provided SIMD register is not a supported floating-point SIMD register.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to add/subtract (addsub) two SIMD registers via EmuSIMD helpers, but the provided Register_ type is not recognised as a supported SIMD register.");
		}
	}

	template<std::size_t PerElementWidth_, class Register_>
	[[nodiscard]] inline Register_ _addsub_int(Register_ lhs_, Register_ rhs_)
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			if constexpr (EmuSIMD::TMP::_assert_valid_simd_int_element_width<PerElementWidth_>())
			{
				using mask_generator = _underlying_simd_helpers::_alternating_index_mask<register_type_uq, true, PerElementWidth_>;
				if constexpr (_underlying_simd_helpers::_is_valid_alternating_index_mask_instance<mask_generator>::value)
				{
					register_type_uq mask_ = mask_generator::get();
					register_type_uq out_ = _add_int<PerElementWidth_>(lhs_, _and(mask_, rhs_));
					return _sub_int<PerElementWidth_>(out_, _andnot(mask_, rhs_));
				}
				else
				{
					static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to emulate a add/subtract (addsub) operation of two integral SIMD registers via EmuSIMD helpers, but a mask could not be successfully created to perform alternating operations.");
				}
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to emulate a add/subtract (addsub) operation of two integral SIMD registers via EmuSIMD helpers, but the provided SIMD register is not a supported integral SIMD register for this operation.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to emulate a add/subtract (addsub) operation of two integral SIMD registers via EmuSIMD helpers, but the provided Register_ type is not recognised as a supported SIMD register.");
		}
	}

	template<class Register_>
	[[nodiscard]] inline Register_ _subadd_fp(Register_ lhs_, Register_ rhs_)
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			using mask_generator = _underlying_simd_helpers::_alternating_index_mask<register_type_uq, true>;
			if constexpr (_underlying_simd_helpers::_is_valid_alternating_index_mask_instance<mask_generator>::value)
			{
				register_type_uq mask_ = mask_generator::get();
				register_type_uq out_ = _sub_fp(lhs_, _and(mask_, rhs_));
				return _add_fp(out_, _andnot(mask_, rhs_));
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to emulate a subtract/add (subadd) operation of two floating-point SIMD registers via EmuSIMD helpers, but a mask could not be successfully created to perform alternating operations.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to emulate a subtract/add (subadd) operation of two floating-point SIMD registers via EmuSIMD helpers, but the provided Register_ type is not recognised as a supported SIMD register.");
		}
	}

	template<std::size_t PerElementWidth_, class Register_>
	[[nodiscard]] inline Register_ _subadd_int(Register_ lhs_, Register_ rhs_)
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			if constexpr (EmuSIMD::TMP::_assert_valid_simd_int_element_width<PerElementWidth_>())
			{
				using mask_generator = _underlying_simd_helpers::_alternating_index_mask<register_type_uq, true, PerElementWidth_>;
				if constexpr (_underlying_simd_helpers::_is_valid_alternating_index_mask_instance<mask_generator>::value)
				{
					register_type_uq mask_ = mask_generator::get();
					register_type_uq out_ = _sub_int<PerElementWidth_>(lhs_, _and(mask_, rhs_));
					return _add_int<PerElementWidth_>(out_, _andnot(mask_, rhs_));
				}
				else
				{
					static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to emulate a subtract/add (subadd) operation of two integral SIMD registers via EmuSIMD helpers, but a mask could not be successfully created to perform alternating operations.");
				}
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to emulate a subtract/add (subadd) operation of two integral SIMD registers via EmuSIMD helpers, but the provided SIMD register is not a supported integral SIMD register for this operation.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to emulate a subtract/add (subadd) operation of two integral SIMD registers via EmuSIMD helpers, but the provided Register_ type is not recognised as a supported SIMD register.");
		}
	}
#pragma endregion

#pragma region FUSED_OPERATIONS
	template<class Register_>
	[[nodiscard]] inline Register_ _fmadd_fp(Register_ to_mult_lhs_, Register_ to_mult_rhs_, Register_ to_add_after_mult_)
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			if constexpr (std::is_same_v<register_type_uq, __m128>)
			{
				return _mm_fmadd_ps(to_mult_lhs_, to_mult_rhs_, to_add_after_mult_);
			}
			else if constexpr (std::is_same_v<register_type_uq, __m256>)
			{
				return _mm256_fmadd_ps(to_mult_lhs_, to_mult_rhs_, to_add_after_mult_);
			}
			else if constexpr (std::is_same_v<register_type_uq, __m512>)
			{
				return _mm512_fmadd_ps(to_mult_lhs_, to_mult_rhs_, to_add_after_mult_);
			}
			else if constexpr (std::is_same_v<register_type_uq, __m128d>)
			{
				return _mm_fmadd_pd(to_mult_lhs_, to_mult_rhs_, to_add_after_mult_);
			}
			else if constexpr (std::is_same_v<register_type_uq, __m256d>)
			{
				return _mm256_fmadd_pd(to_mult_lhs_, to_mult_rhs_, to_add_after_mult_);
			}
			else if constexpr (std::is_same_v<register_type_uq, __m512d>)
			{
				return _mm512_fmadd_pd(to_mult_lhs_, to_mult_rhs_, to_add_after_mult_);
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to fused multiply add (fmadd) three SIMD registers via EmuSIMD helpers, but the provided SIMD register is not a supported floating-point SIMD register.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to fused multiply add (fmadd) three SIMD registers via EmuSIMD helpers, but the provided Register_ type is not recognised as a support SIMD register.");
		}
	}
	template<std::size_t PerElementWidth_, class Register_>
	[[nodiscard]] inline Register_ _fmadd_int(Register_ to_mult_lhs_, Register_ to_mult_rhs_, Register_ to_add_after_mult_)
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			if constexpr (EmuSIMD::TMP::_assert_valid_simd_int_element_width<PerElementWidth_>())
			{
				return _add_int<PerElementWidth_>(_mul_all_int<PerElementWidth_>(to_mult_lhs_, to_mult_rhs_), to_add_after_mult_);
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to emulate a fused multiply add (fmadd) of three integral SIMD registers via EmuSIMD helpers, but the provided PerElementWidth_ is invalid.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to fused multiply add (fmadd) three SIMD registers via EmuSIMD helpers, but the provided Register_ type is not recognised as a support SIMD register.");
		}
	}

	template<class Register_>
	[[nodiscard]] inline Register_ _fmsub_fp(Register_ to_mult_lhs_, Register_ to_mult_rhs_, Register_ to_sub_after_mult_)
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			if constexpr (std::is_same_v<register_type_uq, __m128>)
			{
				return _mm_fmsub_ps(to_mult_lhs_, to_mult_rhs_, to_sub_after_mult_);
			}
			else if constexpr (std::is_same_v<register_type_uq, __m256>)
			{
				return _mm256_fmsub_ps(to_mult_lhs_, to_mult_rhs_, to_sub_after_mult_);
			}
			else if constexpr (std::is_same_v<register_type_uq, __m512>)
			{
				return _mm512_fmsub_ps(to_mult_lhs_, to_mult_rhs_, to_sub_after_mult_);
			}
			else if constexpr (std::is_same_v<register_type_uq, __m128d>)
			{
				return _mm_fmsub_pd(to_mult_lhs_, to_mult_rhs_, to_sub_after_mult_);
			}
			else if constexpr (std::is_same_v<register_type_uq, __m256d>)
			{
				return _mm256_fmsub_pd(to_mult_lhs_, to_mult_rhs_, to_sub_after_mult_);
			}
			else if constexpr (std::is_same_v<register_type_uq, __m512d>)
			{
				return _mm512_fmsub_pd(to_mult_lhs_, to_mult_rhs_, to_sub_after_mult_);
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to fused multiply subtract (fmsub) three SIMD registers via EmuSIMD helpers, but the provided SIMD register is not a supported floating-point SIMD register.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to fused multiply subtract (fmsub) three SIMD registers via EmuSIMD helpers, but the provided Register_ type is not recognised as a support SIMD register.");
		}
	}
	template<std::size_t PerElementWidth_, class Register_>
	[[nodiscard]] inline Register_ _fmsub_int(Register_ to_mult_lhs_, Register_ to_mult_rhs_, Register_ to_sub_after_mult_)
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			if constexpr (EmuSIMD::TMP::_assert_valid_simd_int_element_width<PerElementWidth_>())
			{
				return _sub_int<PerElementWidth_>(_mul_all_int<PerElementWidth_>(to_mult_lhs_, to_mult_rhs_), to_sub_after_mult_);
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to emulate a fused multiply subtract (fmsub) of three integral SIMD registers via EmuSIMD helpers, but the provided PerElementWidth_ is invalid.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to fused multiply subtract (fmsub) three SIMD registers via EmuSIMD helpers, but the provided Register_ type is not recognised as a support SIMD register.");
		}
	}

	template<class Register_>
	[[nodiscard]] inline Register_ _fmaddsub_fp(Register_ to_mult_lhs_, Register_ to_mult_rhs_, Register_ to_add_sub_after_mult_)
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			if constexpr (std::is_same_v<register_type_uq, __m128>)
			{
				return _mm_fmaddsub_ps(to_mult_lhs_, to_mult_rhs_, to_add_sub_after_mult_);
			}
			else if constexpr (std::is_same_v<register_type_uq, __m256>)
			{
				return _mm256_fmaddsub_ps(to_mult_lhs_, to_mult_rhs_, to_add_sub_after_mult_);
			}
			else if constexpr (std::is_same_v<register_type_uq, __m512>)
			{
				return _mm512_fmaddsub_ps(to_mult_lhs_, to_mult_rhs_, to_add_sub_after_mult_);
			}
			else if constexpr (std::is_same_v<register_type_uq, __m128d>)
			{
				return _mm_fmaddsub_pd(to_mult_lhs_, to_mult_rhs_, to_add_sub_after_mult_);
			}
			else if constexpr (std::is_same_v<register_type_uq, __m256d>)
			{
				return _mm256_fmaddsub_pd(to_mult_lhs_, to_mult_rhs_, to_add_sub_after_mult_);
			}
			else if constexpr (std::is_same_v<register_type_uq, __m512d>)
			{
				return _mm512_fmaddsub_pd(to_mult_lhs_, to_mult_rhs_, to_add_sub_after_mult_);
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to fused multiply add/subtract (fmaddsub) three SIMD registers via EmuSIMD helpers, but the provided SIMD register is not a supported floating-point SIMD register.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to fused multiply add/subtract (fmaddsub) three SIMD registers via EmuSIMD helpers, but the provided Register_ type is not recognised as a support SIMD register.");
		}
	}
	template<std::size_t PerElementWidth_, class Register_>
	[[nodiscard]] inline Register_ _fmaddsub_int(Register_ to_mult_lhs_, Register_ to_mult_rhs_, Register_ to_add_sub_after_mult_)
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			if constexpr (EmuSIMD::TMP::_assert_valid_simd_int_element_width<PerElementWidth_>())
			{
				using mask_generator = _underlying_simd_helpers::_alternating_index_mask<register_type_uq, true, PerElementWidth_>;
				if constexpr(_underlying_simd_helpers::_is_valid_alternating_index_mask_instance<mask_generator>::value)
				{
					register_type_uq out_ = _mul_all_int<PerElementWidth_>(to_mult_lhs_, to_mult_rhs_);
					register_type_uq mask_ = mask_generator::get();
					out_ = _add_int<PerElementWidth_>(out_, _and(mask_, to_add_sub_after_mult_));
					return _sub_int<PerElementWidth_>(out_, _andnot(mask_, to_add_sub_after_mult_));
				}
				else
				{
					static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to emulate a fused multiply add/subtract (fmaddsub) of three integral SIMD registers via EmuSIMD helpers, but an alternating mask could not be formed successfully.");
				}

			}
			else
			{
				static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to emulate a fused multiply add/subtract (fmaddsub) of three integral SIMD registers via EmuSIMD helpers, but the provided PerElementWidth_ is invalid.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to fused multiply subtract (fmsub) three SIMD registers via EmuSIMD helpers, but the provided Register_ type is not recognised as a support SIMD register.");
		}
	}

	template<class Register_>
	[[nodiscard]] inline Register_ _fmsubadd_fp(Register_ to_mult_lhs_, Register_ to_mult_rhs_, Register_ to_sub_add_after_mult_)
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			if constexpr (std::is_same_v<register_type_uq, __m128>)
			{
				return _mm_fmsubadd_ps(to_mult_lhs_, to_mult_rhs_, to_sub_add_after_mult_);
			}
			else if constexpr (std::is_same_v<register_type_uq, __m256>)
			{
				return _mm256_fmsubadd_ps(to_mult_lhs_, to_mult_rhs_, to_sub_add_after_mult_);
			}
			else if constexpr (std::is_same_v<register_type_uq, __m512>)
			{
				return _mm512_fmsubadd_ps(to_mult_lhs_, to_mult_rhs_, to_sub_add_after_mult_);
			}
			else if constexpr (std::is_same_v<register_type_uq, __m128d>)
			{
				return _mm_fmsubadd_pd(to_mult_lhs_, to_mult_rhs_, to_sub_add_after_mult_);
			}
			else if constexpr (std::is_same_v<register_type_uq, __m256d>)
			{
				return _mm256_fmsubadd_pd(to_mult_lhs_, to_mult_rhs_, to_sub_add_after_mult_);
			}
			else if constexpr (std::is_same_v<register_type_uq, __m512d>)
			{
				return _mm512_fmsubadd_pd(to_mult_lhs_, to_mult_rhs_, to_sub_add_after_mult_);
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to fused multiply subtract/add (fmsubadd) three SIMD registers via EmuSIMD helpers, but the provided SIMD register is not a supported floating-point SIMD register.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to fused multiply subtract/add (fmsubadd) three SIMD registers via EmuSIMD helpers, but the provided Register_ type is not recognised as a support SIMD register.");
		}
	}
	template<std::size_t PerElementWidth_, class Register_>
	[[nodiscard]] inline Register_ _fmsubadd_int(Register_ to_mult_lhs_, Register_ to_mult_rhs_, Register_ to_add_sub_after_mult_)
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			if constexpr (EmuSIMD::TMP::_assert_valid_simd_int_element_width<PerElementWidth_>())
			{
				using mask_generator = _underlying_simd_helpers::_alternating_index_mask<register_type_uq, true, PerElementWidth_>;
				if constexpr(_underlying_simd_helpers::_is_valid_alternating_index_mask_instance<mask_generator>::value)
				{
					register_type_uq out_ = _mul_all_int<PerElementWidth_>(to_mult_lhs_, to_mult_rhs_);
					register_type_uq mask_ = mask_generator::get();
					out_ = _sub_int<PerElementWidth_>(out_, _and(mask_, to_add_sub_after_mult_));
					return _add_int<PerElementWidth_>(out_, _andnot(mask_, to_add_sub_after_mult_));
				}
				else
				{
					static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to emulate a fused multiply subtract/add (fmsubadd) of three integral SIMD registers via EmuSIMD helpers, but an alternating mask could not be formed successfully.");
				}

			}
			else
			{
				static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to emulate a fused multiply subtract/add (fmsubadd) of three integral SIMD registers via EmuSIMD helpers, but the provided PerElementWidth_ is invalid.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to fused multiply subtract (fmsub) three SIMD registers via EmuSIMD helpers, but the provided Register_ type is not recognised as a support SIMD register.");
		}
	}
#pragma endregion

#pragma region ROUNDS
	template<int RoundingMode_, class Register_>
	[[nodiscard]] inline Register_ _round(Register_ register_)
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			if constexpr (std::is_same_v<register_type_uq, __m128>)
			{
				return _mm_round_ps(register_, RoundingMode_);
			}
			else if constexpr (std::is_same_v<register_type_uq, __m256>)
			{
				return _mm256_round_ps(register_, RoundingMode_);
			}
			else if constexpr (std::is_same_v<register_type_uq, __m512>)
			{
				static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to call a non-specific round function (round) on a __m512 SIMD register via EmuSIMD helpers. These registers are not supported for this operation. Consider the floor, trunc, or ceil operations instead.");
			}
			else if constexpr (std::is_same_v<register_type_uq, __m128d>)
			{
				return _mm_round_pd(register_, RoundingMode_);
			}
			else if constexpr (std::is_same_v<register_type_uq, __m256d>)
			{
				return _mm256_round_pd(register_, RoundingMode_);
			}
			else if constexpr (std::is_same_v<register_type_uq, __m512d>)
			{
				static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to call a non-specific round function (round) on a __m512d SIMD register via EmuSIMD helpers. These registers are not supported for this operation. Consider the floor, trunc, or ceil operations instead.");
			}
			else if constexpr (EmuSIMD::TMP::is_integral_simd_register_v<register_type_uq>)
			{
				// If integral, there is no round to be done
				return register_;
			}
			else
			{
				// Potentially requires a round but we don't know how to do it
				static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to floor a SIMD register via EmuSIMD helpers, but the provided non-integral SIMD register is not supported for this operation.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to floor a SIMD register via EmuSIMD helpers, but the provided Register_ type is not recognised as a supported SIMD register.");
		}
	}

	template<class Register_>
	[[nodiscard]] inline Register_ _floor(Register_ register_)
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			if constexpr (std::is_same_v<register_type_uq, __m128>)
			{
				return _mm_floor_ps(register_);
			}
			else if constexpr (std::is_same_v<register_type_uq, __m256>)
			{
				return _mm256_floor_ps(register_);
			}
			else if constexpr (std::is_same_v<register_type_uq, __m512>)
			{
				return _mm512_floor_ps(register_);
			}
			else if constexpr (std::is_same_v<register_type_uq, __m128d>)
			{
				return _mm_floor_pd(register_);
			}
			else if constexpr (std::is_same_v<register_type_uq, __m256d>)
			{
				return _mm256_floor_pd(register_);
			}
			else if constexpr (std::is_same_v<register_type_uq, __m512d>)
			{
				return _mm512_floor_pd(register_);
			}
			else if constexpr (EmuSIMD::TMP::is_integral_simd_register_v<register_type_uq>)
			{
				// If integral, there is no round to be done
				return register_;
			}
			else
			{
				// Potentially requires a round but we don't know how to do it
				static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to floor a SIMD register via EmuSIMD helpers, but the provided non-integral SIMD register is not supported for this operation.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to floor a SIMD register via EmuSIMD helpers, but the provided Register_ type is not recognised as a supported SIMD register.");
		}
	}

	template<class Register_>
	[[nodiscard]] inline Register_ _ceil(Register_ register_)
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			if constexpr (std::is_same_v<register_type_uq, __m128>)
			{
				return _mm_ceil_ps(register_);
			}
			else if constexpr (std::is_same_v<register_type_uq, __m256>)
			{
				return _mm256_ceil_ps(register_);
			}
			else if constexpr (std::is_same_v<register_type_uq, __m512>)
			{
				return _mm512_ceil_ps(register_);
			}
			else if constexpr (std::is_same_v<register_type_uq, __m128d>)
			{
				return _mm_ceil_pd(register_);
			}
			else if constexpr (std::is_same_v<register_type_uq, __m256d>)
			{
				return _mm256_ceil_pd(register_);
			}
			else if constexpr (std::is_same_v<register_type_uq, __m512d>)
			{
				return _mm512_ceil_pd(register_);
			}
			else if constexpr (EmuSIMD::TMP::is_integral_simd_register_v<register_type_uq>)
			{
				// If integral, there is no round to be done
				return register_;
			}
			else
			{
				// Potentially requires a round but we don't know how to do it
				static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to ceil a SIMD register via EmuSIMD helpers, but the provided non-integral SIMD register is not supported for this operation.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to ceil a SIMD register via EmuSIMD helpers, but the provided Register_ type is not recognised as a supported SIMD register.");
		}
	}

	template<class Register_>
	[[nodiscard]] inline Register_ _trunc(Register_ register_)
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			if constexpr (std::is_same_v<register_type_uq, __m128>)
			{
				return _mm_trunc_ps(register_);
			}
			else if constexpr (std::is_same_v<register_type_uq, __m256>)
			{
				return _mm256_trunc_ps(register_);
			}
			else if constexpr (std::is_same_v<register_type_uq, __m512>)
			{
				return _mm512_trunc_ps(register_);
			}
			else if constexpr (std::is_same_v<register_type_uq, __m128d>)
			{
				return _mm_trunc_pd(register_);
			}
			else if constexpr (std::is_same_v<register_type_uq, __m256d>)
			{
				return _mm256_trunc_pd(register_);
			}
			else if constexpr (std::is_same_v<register_type_uq, __m512d>)
			{
				return _mm512_trunc_pd(register_);
			}
			else if constexpr (EmuSIMD::TMP::is_integral_simd_register_v<register_type_uq>)
			{
				// If integral, there is no round to be done
				return register_;
			}
			else
			{
				// Potentially requires a round but we don't know how to do it
				static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to truncate a SIMD register via EmuSIMD helpers, but the provided non-integral SIMD register is not supported for this operation.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to truncate a SIMD register via EmuSIMD helpers, but the provided Register_ type is not recognised as a supported SIMD register.");
		}
	}
#pragma endregion

#pragma region MIN_MAX_OPS
	template<std::size_t PerElementWidthIfInt_, bool SignedIfInt_, class Register_>
	[[nodiscard]] inline Register_ _min(Register_ a_, Register_ b_)
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			if constexpr (std::is_same_v<register_type_uq, __m128>)
			{
				return _mm_min_ps(a_, b_);
			}
			else if constexpr (std::is_same_v<register_type_uq, __m256>)
			{
				return _mm256_min_ps(a_, b_);
			}
			else if constexpr (std::is_same_v<register_type_uq, __m512>)
			{
				return _mm512_min_ps(a_, b_);
			}
			else if constexpr (std::is_same_v<register_type_uq, __m128d>)
			{
				return _mm_min_pd(a_, b_);
			}
			else if constexpr (std::is_same_v<register_type_uq, __m256d>)
			{
				return _mm256_min_pd(a_, b_);
			}
			else if constexpr (std::is_same_v<register_type_uq, __m512d>)
			{
				return _mm512_min_pd(a_, b_);
			}
			else if constexpr (EmuCore::TMP::is_any_comparison_true<std::is_same, register_type_uq, __m128i, __m256i, __m512i>::value)
			{
				if constexpr (EmuSIMD::TMP::_assert_valid_simd_int_element_width<PerElementWidthIfInt_>())
				{
					if constexpr (std::is_same_v<register_type_uq, __m128i>)
					{
						if constexpr (PerElementWidthIfInt_ == 8)
						{
							if constexpr (SignedIfInt_)
							{
								return _mm_min_epi8(a_, b_);
							}
							else
							{
								return _mm_min_epu8(a_, b_);
							}
						}
						else if constexpr (PerElementWidthIfInt_ == 16)
						{
							if constexpr (SignedIfInt_)
							{
								return _mm_min_epi16(a_, b_);
							}
							else
							{
								return _mm_min_epu16(a_, b_);
							}
						}
						else if constexpr (PerElementWidthIfInt_ == 32)
						{
							if constexpr (SignedIfInt_)
							{
								return _mm_min_epi32(a_, b_);
							}
							else
							{
								return _mm_min_epu32(a_, b_);
							}
						}
						else
						{
							if constexpr (SignedIfInt_)
							{
								return _mm_min_epi64(a_, b_);
							}
							else
							{
								return _mm_min_epu64(a_, b_);
							}
						}
					}
					else if constexpr (std::is_same_v<register_type_uq, __m256i>)
					{
						if constexpr (PerElementWidthIfInt_ == 8)
						{
							if constexpr (SignedIfInt_)
							{
								return _mm256_min_epi8(a_, b_);
							}
							else
							{
								return _mm256_min_epu8(a_, b_);
							}
						}
						else if constexpr (PerElementWidthIfInt_ == 16)
						{
							if constexpr (SignedIfInt_)
							{
								return _mm256_min_epi16(a_, b_);
							}
							else
							{
								return _mm256_min_epu16(a_, b_);
							}
						}
						else if constexpr (PerElementWidthIfInt_ == 32)
						{
							if constexpr (SignedIfInt_)
							{
								return _mm256_min_epi32(a_, b_);
							}
							else
							{
								return _mm256_min_epu32(a_, b_);
							}
						}
						else
						{
							if constexpr (SignedIfInt_)
							{
								return _mm256_min_epi64(a_, b_);
							}
							else
							{
								return _mm256_min_epu64(a_, b_);
							}
						}
					}
					else
					{
						if constexpr (PerElementWidthIfInt_ == 8)
						{
							if constexpr (SignedIfInt_)
							{
								return _mm512_min_epi8(a_, b_);
							}
							else
							{
								return _mm512_min_epu8(a_, b_);
							}
						}
						else if constexpr (PerElementWidthIfInt_ == 16)
						{
							if constexpr (SignedIfInt_)
							{
								return _mm512_min_epi16(a_, b_);
							}
							else
							{
								return _mm512_min_epu16(a_, b_);
							}
						}
						else if constexpr (PerElementWidthIfInt_ == 32)
						{
							if constexpr (SignedIfInt_)
							{
								return _mm512_min_epi32(a_, b_);
							}
							else
							{
								return _mm512_min_epu32(a_, b_);
							}
						}
						else
						{
							if constexpr (SignedIfInt_)
							{
								return _mm512_min_epi64(a_, b_);
							}
							else
							{
								return _mm512_min_epu64(a_, b_);
							}
						}
					}
				}
				else
				{
					static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to find the minimum elements in two SIMD registers via EmuSIMD helpers, but the provided PerElementWidth_ is invalid.");
				}
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to find the minimum elements in two SIMD registers via EmuSIMD registers, but the passed Register_ type is not supported for this operation.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to find the minimum elements in two SIMD registers via EmuSIMD helpers, but the provided Register_ type is not recognised as a supported SIMD register.");
		}
	}

	template<std::size_t PerElementWidthIfInt_, bool SignedIfInt_, class Register_>
	[[nodiscard]] inline Register_ _max(Register_ a_, Register_ b_)
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			if constexpr (std::is_same_v<register_type_uq, __m128>)
			{
				return _mm_max_ps(a_, b_);
			}
			else if constexpr (std::is_same_v<register_type_uq, __m256>)
			{
				return _mm256_max_ps(a_, b_);
			}
			else if constexpr (std::is_same_v<register_type_uq, __m512>)
			{
				return _mm512_max_ps(a_, b_);
			}
			else if constexpr (std::is_same_v<register_type_uq, __m128d>)
			{
				return _mm_max_pd(a_, b_);
			}
			else if constexpr (std::is_same_v<register_type_uq, __m256d>)
			{
				return _mm256_max_pd(a_, b_);
			}
			else if constexpr (std::is_same_v<register_type_uq, __m512d>)
			{
				return _mm512_max_pd(a_, b_);
			}
			else if constexpr (EmuCore::TMP::is_any_comparison_true<std::is_same, register_type_uq, __m128i, __m256i, __m512i>::value)
			{
				if constexpr (EmuSIMD::TMP::_assert_valid_simd_int_element_width<PerElementWidthIfInt_>())
				{
					if constexpr (std::is_same_v<register_type_uq, __m128i>)
					{
						if constexpr (PerElementWidthIfInt_ == 8)
						{
							if constexpr (SignedIfInt_)
							{
								return _mm_max_epi8(a_, b_);
							}
							else
							{
								return _mm_max_epu8(a_, b_);
							}
						}
						else if constexpr (PerElementWidthIfInt_ == 16)
						{
							if constexpr (SignedIfInt_)
							{
								return _mm_max_epi16(a_, b_);
							}
							else
							{
								return _mm_max_epu16(a_, b_);
							}
						}
						else if constexpr (PerElementWidthIfInt_ == 32)
						{
							if constexpr (SignedIfInt_)
							{
								return _mm_max_epi32(a_, b_);
							}
							else
							{
								return _mm_max_epu32(a_, b_);
							}
						}
						else
						{
							if constexpr (SignedIfInt_)
							{
								return _mm_max_epi64(a_, b_);
							}
							else
							{
								return _mm_max_epu64(a_, b_);
							}
						}
					}
					else if constexpr (std::is_same_v<register_type_uq, __m256i>)
					{
						if constexpr (PerElementWidthIfInt_ == 8)
						{
							if constexpr (SignedIfInt_)
							{
								return _mm256_max_epi8(a_, b_);
							}
							else
							{
								return _mm256_max_epu8(a_, b_);
							}
						}
						else if constexpr (PerElementWidthIfInt_ == 16)
						{
							if constexpr (SignedIfInt_)
							{
								return _mm256_max_epi16(a_, b_);
							}
							else
							{
								return _mm256_max_epu16(a_, b_);
							}
						}
						else if constexpr (PerElementWidthIfInt_ == 32)
						{
							if constexpr (SignedIfInt_)
							{
								return _mm256_max_epi32(a_, b_);
							}
							else
							{
								return _mm256_max_epu32(a_, b_);
							}
						}
						else
						{
							if constexpr (SignedIfInt_)
							{
								return _mm256_max_epi64(a_, b_);
							}
							else
							{
								return _mm256_max_epu64(a_, b_);
							}
						}
					}
					else
					{
						if constexpr (PerElementWidthIfInt_ == 8)
						{
							if constexpr (SignedIfInt_)
							{
								return _mm512_max_epi8(a_, b_);
							}
							else
							{
								return _mm512_max_epu8(a_, b_);
							}
						}
						else if constexpr (PerElementWidthIfInt_ == 16)
						{
							if constexpr (SignedIfInt_)
							{
								return _mm512_max_epi16(a_, b_);
							}
							else
							{
								return _mm512_max_epu16(a_, b_);
							}
						}
						else if constexpr (PerElementWidthIfInt_ == 32)
						{
							if constexpr (SignedIfInt_)
							{
								return _mm512_max_epi32(a_, b_);
							}
							else
							{
								return _mm512_max_epu32(a_, b_);
							}
						}
						else
						{
							if constexpr (SignedIfInt_)
							{
								return _mm512_max_epi64(a_, b_);
							}
							else
							{
								return _mm512_max_epu64(a_, b_);
							}
						}
					}
				}
				else
				{
					static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to find the maximum elements in two SIMD registers via EmuSIMD helpers, but the provided PerElementWidth_ is invalid.");
				}
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to find the maximum elements in two SIMD registers via EmuSIMD registers, but the passed Register_ type is not supported for this operation.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to find the maximum elements in two SIMD registers via EmuSIMD helpers, but the provided Register_ type is not recognised as a supported SIMD register.");
		}
	}

	template<std::size_t PerElementWidthIfInt_, bool SignedIfInt_, class Register_>
	[[nodiscard]] inline Register_ _clamp_min(Register_ register_, Register_ min_)
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			return _max<PerElementWidthIfInt_, SignedIfInt_>(register_, min_);
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to clamp the values in a SIMD register to a minimum amount, but the provided Register_ type is not recognised as a supported SIMD register.");
		}
	}

	template<std::size_t PerElementWidthIfInt_, bool SignedIfInt_, class Register_>
	[[nodiscard]] inline Register_ _clamp_max(Register_ register_, Register_ max_)
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			return _min<PerElementWidthIfInt_, SignedIfInt_>(register_, max_);
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to clamp the values in a SIMD register to a maximum amount, but the provided Register_ type is not recognised as a supported SIMD register.");
		}
	}

	template<std::size_t PerElementWidthIfInt_, bool SignedIfInt_, class Register_>
	[[nodiscard]] inline Register_ _clamp(Register_ register_, Register_ min_, Register_ max_)
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			return _min<PerElementWidthIfInt_, SignedIfInt_>
			(
				_max<PerElementWidthIfInt_, SignedIfInt_>(register_, min_),
				max_
			);
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to clamp the values in a SIMD register to an inclusive min:max range, but the provided Register_ type is not recognised as a supported SIMD register.");
		}
	}
#pragma endregion
}

#endif
