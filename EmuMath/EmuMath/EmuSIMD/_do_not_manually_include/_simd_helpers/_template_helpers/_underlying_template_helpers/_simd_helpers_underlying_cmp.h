#ifndef EMU_SIMD_HELPERS_UNDERLYING_CMP_H_INC_
#define EMU_SIMD_HELPERS_UNDERLYING_CMP_H_INC_ 1

#include "_common_underlying_simd_template_helper_includes.h"
#include "_simd_helpers_underlying_cast.h"
#include "../../../../../EmuCore/CommonConcepts/Arithmetic.h"
#include "../../../../../EmuCore/TMPHelpers/Values.h"

namespace EmuSIMD::_underlying_simd_helpers
{
#pragma region MAKE_FROM_MOVEMASK_FUNCS
	template<class Register_, std::size_t PerElementWidth_, std::uint64_t Bits_ = 0xFFFFFFFFFFFFFFFF>
	[[nodiscard]] inline Register_ _make_register_from_movemask_int(const unsigned long long mask_)
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			if constexpr (EmuSIMD::TMP::_assert_valid_simd_int_element_width<PerElementWidth_>())
			{
				using bits_type = EmuCore::TMP::int_of_size_t<PerElementWidth_ / 8>;
				constexpr bits_type bit_mask_ =
				(
					PerElementWidth_ == 8 ? 0xFF : 
						PerElementWidth_ == 16 ? 0xFFFF : 
							PerElementWidth_ == 32 ? 0xFFFFFFFF : 0xFFFFFFFFFFFFFFFF
				);
				constexpr bits_type masked_bits_ = static_cast<bits_type>(Bits_ & bit_mask_);

				if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i128_generic>)
				{
					if constexpr (PerElementWidth_ == 8)
					{
						return _mm_set_epi8
						(
							(mask_ & 1) *         masked_bits_,
							((mask_ >> 1) & 1) *  masked_bits_,
							((mask_ >> 2) & 1) *  masked_bits_,
							((mask_ >> 3) & 1) *  masked_bits_,
							((mask_ >> 4) & 1) *  masked_bits_,
							((mask_ >> 5) & 1) *  masked_bits_,
							((mask_ >> 6) & 1) *  masked_bits_,
							((mask_ >> 7) & 1) *  masked_bits_,
							((mask_ >> 8) & 1) *  masked_bits_,
							((mask_ >> 9) & 1) *  masked_bits_,
							((mask_ >> 10) & 1) * masked_bits_,
							((mask_ >> 11) & 1) * masked_bits_,
							((mask_ >> 12) & 1) * masked_bits_,
							((mask_ >> 13) & 1) * masked_bits_,
							((mask_ >> 14) & 1) * masked_bits_,
							((mask_ >> 15) & 1) * masked_bits_
						);
					}
					else if constexpr (PerElementWidth_ == 16)
					{
						return _mm_set_epi16
						(
							(mask_ & 1) *         masked_bits_,
							((mask_ >> 1) & 1) *  masked_bits_,
							((mask_ >> 2) & 1) *  masked_bits_,
							((mask_ >> 3) & 1) *  masked_bits_,
							((mask_ >> 4) & 1) *  masked_bits_,
							((mask_ >> 5) & 1) *  masked_bits_,
							((mask_ >> 6) & 1) *  masked_bits_,
							((mask_ >> 7) & 1) *  masked_bits_
						);
					}
					else if constexpr (PerElementWidth_ == 32)
					{
						return _mm_set_epi32
						(
							(mask_ & 1) *         masked_bits_,
							((mask_ >> 1) & 1) *  masked_bits_,
							((mask_ >> 2) & 1) *  masked_bits_,
							((mask_ >> 3) & 1) *  masked_bits_
						);
					}
					else
					{
						return _mm_set_epi64x
						(
							(mask_ & 1) *         masked_bits_,
							((mask_ >> 1) & 1) *  masked_bits_
						);
					}
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i256_generic>)
				{
					if constexpr (PerElementWidth_ == 8)
					{
						return _mm256_set_epi8
						(
							(mask_ & 1) *         masked_bits_,
							((mask_ >> 1) & 1) *  masked_bits_,
							((mask_ >> 2) & 1) *  masked_bits_,
							((mask_ >> 3) & 1) *  masked_bits_,
							((mask_ >> 4) & 1) *  masked_bits_,
							((mask_ >> 5) & 1) *  masked_bits_,
							((mask_ >> 6) & 1) *  masked_bits_,
							((mask_ >> 7) & 1) *  masked_bits_,
							((mask_ >> 8) & 1) *  masked_bits_,
							((mask_ >> 9) & 1) *  masked_bits_,
							((mask_ >> 10) & 1) * masked_bits_,
							((mask_ >> 11) & 1) * masked_bits_,
							((mask_ >> 12) & 1) * masked_bits_,
							((mask_ >> 13) & 1) * masked_bits_,
							((mask_ >> 14) & 1) * masked_bits_,
							((mask_ >> 15) & 1) * masked_bits_,
							((mask_ >> 16) & 1) * masked_bits_,
							((mask_ >> 17) & 1) * masked_bits_,
							((mask_ >> 18) & 1) * masked_bits_,
							((mask_ >> 19) & 1) * masked_bits_,
							((mask_ >> 20) & 1) * masked_bits_,
							((mask_ >> 21) & 1) * masked_bits_,
							((mask_ >> 22) & 1) * masked_bits_,
							((mask_ >> 23) & 1) * masked_bits_,
							((mask_ >> 24) & 1) * masked_bits_,
							((mask_ >> 25) & 1) * masked_bits_,
							((mask_ >> 26) & 1) * masked_bits_,
							((mask_ >> 27) & 1) * masked_bits_,
							((mask_ >> 28) & 1) * masked_bits_,
							((mask_ >> 29) & 1) * masked_bits_,
							((mask_ >> 30) & 1) * masked_bits_,
							((mask_ >> 31) & 1) * masked_bits_
						);
					}
					else if constexpr (PerElementWidth_ == 16)
					{
						return _mm256_set_epi16
						(
							(mask_ & 1) *         masked_bits_,
							((mask_ >> 1) & 1) *  masked_bits_,
							((mask_ >> 2) & 1) *  masked_bits_,
							((mask_ >> 3) & 1) *  masked_bits_,
							((mask_ >> 4) & 1) *  masked_bits_,
							((mask_ >> 5) & 1) *  masked_bits_,
							((mask_ >> 6) & 1) *  masked_bits_,
							((mask_ >> 7) & 1) *  masked_bits_,
							((mask_ >> 8) & 1) *  masked_bits_,
							((mask_ >> 9) & 1) *  masked_bits_,
							((mask_ >> 10) & 1) * masked_bits_,
							((mask_ >> 11) & 1) * masked_bits_,
							((mask_ >> 12) & 1) * masked_bits_,
							((mask_ >> 13) & 1) * masked_bits_,
							((mask_ >> 14) & 1) * masked_bits_,
							((mask_ >> 15) & 1) * masked_bits_
						);
					}
					else if constexpr (PerElementWidth_ == 32)
					{
						return _mm256_set_epi32
						(
							(mask_ & 1) *         masked_bits_,
							((mask_ >> 1) & 1) *  masked_bits_,
							((mask_ >> 2) & 1) *  masked_bits_,
							((mask_ >> 3) & 1) *  masked_bits_,
							((mask_ >> 4) & 1) *  masked_bits_,
							((mask_ >> 5) & 1) *  masked_bits_,
							((mask_ >> 6) & 1) *  masked_bits_,
							((mask_ >> 7) & 1) *  masked_bits_
						);
					}
					else
					{
						return _mm256_set_epi64x
						(
							(mask_ & 1) *         masked_bits_,
							((mask_ >> 1) & 1) *  masked_bits_,
							((mask_ >> 2) & 1) *  masked_bits_,
							((mask_ >> 3) & 1) *  masked_bits_
						);
					}
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i512_generic>)
				{
					if constexpr (PerElementWidth_ == 8)
					{
						return _mm512_set_epi8
						(
							(mask_ & 1) *         masked_bits_,
							((mask_ >> 1) & 1) *  masked_bits_,
							((mask_ >> 2) & 1) *  masked_bits_,
							((mask_ >> 3) & 1) *  masked_bits_,
							((mask_ >> 4) & 1) *  masked_bits_,
							((mask_ >> 5) & 1) *  masked_bits_,
							((mask_ >> 6) & 1) *  masked_bits_,
							((mask_ >> 7) & 1) *  masked_bits_,
							((mask_ >> 8) & 1) *  masked_bits_,
							((mask_ >> 9) & 1) *  masked_bits_,
							((mask_ >> 10) & 1) * masked_bits_,
							((mask_ >> 11) & 1) * masked_bits_,
							((mask_ >> 12) & 1) * masked_bits_,
							((mask_ >> 13) & 1) * masked_bits_,
							((mask_ >> 14) & 1) * masked_bits_,
							((mask_ >> 15) & 1) * masked_bits_,
							((mask_ >> 16) & 1) * masked_bits_,
							((mask_ >> 17) & 1) * masked_bits_,
							((mask_ >> 18) & 1) * masked_bits_,
							((mask_ >> 19) & 1) * masked_bits_,
							((mask_ >> 20) & 1) * masked_bits_,
							((mask_ >> 21) & 1) * masked_bits_,
							((mask_ >> 22) & 1) * masked_bits_,
							((mask_ >> 23) & 1) * masked_bits_,
							((mask_ >> 24) & 1) * masked_bits_,
							((mask_ >> 25) & 1) * masked_bits_,
							((mask_ >> 26) & 1) * masked_bits_,
							((mask_ >> 27) & 1) * masked_bits_,
							((mask_ >> 28) & 1) * masked_bits_,
							((mask_ >> 29) & 1) * masked_bits_,
							((mask_ >> 30) & 1) * masked_bits_,
							((mask_ >> 31) & 1) * masked_bits_,
							((mask_ >> 32) & 1) * masked_bits_,
							((mask_ >> 33) & 1) * masked_bits_,
							((mask_ >> 34) & 1) * masked_bits_,
							((mask_ >> 35) & 1) * masked_bits_,
							((mask_ >> 36) & 1) * masked_bits_,
							((mask_ >> 37) & 1) * masked_bits_,
							((mask_ >> 38) & 1) * masked_bits_,
							((mask_ >> 39) & 1) * masked_bits_,
							((mask_ >> 40) & 1) * masked_bits_,
							((mask_ >> 41) & 1) * masked_bits_,
							((mask_ >> 42) & 1) * masked_bits_,
							((mask_ >> 43) & 1) * masked_bits_,
							((mask_ >> 44) & 1) * masked_bits_,
							((mask_ >> 45) & 1) * masked_bits_,
							((mask_ >> 46) & 1) * masked_bits_,
							((mask_ >> 47) & 1) * masked_bits_,
							((mask_ >> 48) & 1) * masked_bits_,
							((mask_ >> 49) & 1) * masked_bits_,
							((mask_ >> 50) & 1) * masked_bits_,
							((mask_ >> 51) & 1) * masked_bits_,
							((mask_ >> 52) & 1) * masked_bits_,
							((mask_ >> 53) & 1) * masked_bits_,
							((mask_ >> 54) & 1) * masked_bits_,
							((mask_ >> 55) & 1) * masked_bits_,
							((mask_ >> 56) & 1) * masked_bits_,
							((mask_ >> 57) & 1) * masked_bits_,
							((mask_ >> 58) & 1) * masked_bits_,
							((mask_ >> 59) & 1) * masked_bits_,
							((mask_ >> 60) & 1) * masked_bits_,
							((mask_ >> 61) & 1) * masked_bits_,
							((mask_ >> 62) & 1) * masked_bits_,
							((mask_ >> 63) & 1) * masked_bits_
						);
					}
					else if constexpr (PerElementWidth_ == 16)
					{
						return _mm512_set_epi16
						(
							(mask_ & 1) *         masked_bits_,
							((mask_ >> 1) & 1) *  masked_bits_,
							((mask_ >> 2) & 1) *  masked_bits_,
							((mask_ >> 3) & 1) *  masked_bits_,
							((mask_ >> 4) & 1) *  masked_bits_,
							((mask_ >> 5) & 1) *  masked_bits_,
							((mask_ >> 6) & 1) *  masked_bits_,
							((mask_ >> 7) & 1) *  masked_bits_,
							((mask_ >> 8) & 1) *  masked_bits_,
							((mask_ >> 9) & 1) *  masked_bits_,
							((mask_ >> 10) & 1) * masked_bits_,
							((mask_ >> 11) & 1) * masked_bits_,
							((mask_ >> 12) & 1) * masked_bits_,
							((mask_ >> 13) & 1) * masked_bits_,
							((mask_ >> 14) & 1) * masked_bits_,
							((mask_ >> 15) & 1) * masked_bits_,
							((mask_ >> 16) & 1) * masked_bits_,
							((mask_ >> 17) & 1) * masked_bits_,
							((mask_ >> 18) & 1) * masked_bits_,
							((mask_ >> 19) & 1) * masked_bits_,
							((mask_ >> 20) & 1) * masked_bits_,
							((mask_ >> 21) & 1) * masked_bits_,
							((mask_ >> 22) & 1) * masked_bits_,
							((mask_ >> 23) & 1) * masked_bits_,
							((mask_ >> 24) & 1) * masked_bits_,
							((mask_ >> 25) & 1) * masked_bits_,
							((mask_ >> 26) & 1) * masked_bits_,
							((mask_ >> 27) & 1) * masked_bits_,
							((mask_ >> 28) & 1) * masked_bits_,
							((mask_ >> 29) & 1) * masked_bits_,
							((mask_ >> 30) & 1) * masked_bits_,
							((mask_ >> 31) & 1) * masked_bits_
						);
					}
					else if constexpr (PerElementWidth_ == 32)
					{
						return _mm512_set_epi32
						(
							(mask_ & 1) *         masked_bits_,
							((mask_ >> 1) & 1) *  masked_bits_,
							((mask_ >> 2) & 1) *  masked_bits_,
							((mask_ >> 3) & 1) *  masked_bits_,
							((mask_ >> 4) & 1) *  masked_bits_,
							((mask_ >> 5) & 1) *  masked_bits_,
							((mask_ >> 6) & 1) *  masked_bits_,
							((mask_ >> 7) & 1) *  masked_bits_,
							((mask_ >> 8) & 1) *  masked_bits_,
							((mask_ >> 9) & 1) *  masked_bits_,
							((mask_ >> 10) & 1) * masked_bits_,
							((mask_ >> 11) & 1) * masked_bits_,
							((mask_ >> 12) & 1) * masked_bits_,
							((mask_ >> 13) & 1) * masked_bits_,
							((mask_ >> 14) & 1) * masked_bits_,
							((mask_ >> 15) & 1) * masked_bits_
						);
					}
					else
					{
						return _mm512_set_epi64
						(
							(mask_ & 1) *         masked_bits_,
							((mask_ >> 1) & 1) *  masked_bits_,
							((mask_ >> 2) & 1) *  masked_bits_,
							((mask_ >> 3) & 1) *  masked_bits_,
							((mask_ >> 4) & 1) *  masked_bits_,
							((mask_ >> 5) & 1) *  masked_bits_,
							((mask_ >> 6) & 1) *  masked_bits_,
							((mask_ >> 7) & 1) *  masked_bits_
						);
					}
				}
				else
				{
					static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to make an integral SIMD register from a move mask using EmuSIMD helpers, but the requested output register is not a supported integral SIMD register.");
				}
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to make an integral SIMD register from a move mask using EmuSIMD helpers, but the provided PerElementWidth_ is invalid.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to make an integral SIMD register from a move mask using EmuSIMD helpers, but the requested output register is not recognised as a SIMD register.");
		}
	}

	
	template<class Register_, std::int64_t Bits_ = 0xFFFFFFFFFFFFFFFF>
	[[nodiscard]] inline Register_ _make_register_from_movemask_fp(const unsigned long long mask_)
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x4>)
			{
				return _mm_castsi128_ps(_make_register_from_movemask_int<EmuSIMD::i128_generic, 32, Bits_>(mask_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x8>)
			{
				return _mm256_castsi256_ps(_make_register_from_movemask_int<EmuSIMD::i256_generic, 32, Bits_>(mask_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x16>)
			{
				return _mm512_castsi512_ps(_make_register_from_movemask_int<EmuSIMD::i512_generic, 32, Bits_>(mask_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x2>)
			{
				return _mm_castsi128_pd(_make_register_from_movemask_int<EmuSIMD::i128_generic, 64, Bits_>(mask_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x4>)
			{
				return _mm256_castsi256_pd(_make_register_from_movemask_int<EmuSIMD::i256_generic, 64, Bits_>(mask_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x8>)
			{
				return _mm512_castsi512_pd(_make_register_from_movemask_int<EmuSIMD::i512_generic, 64, Bits_>(mask_));
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to make a floating-point SIMD register from a move mask using EmuSIMD helpers, but the requested output register is not a supported floating-point SIMD register.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to make a floating-point SIMD register from a move mask using EmuSIMD helpers, but the requested output register is not recognised as a SIMD register.");
		}
	}

	template<class Register_, std::size_t PerElementWidthIfIntegral_ = 32, std::int64_t Bits_ = 0xFFFFFFFFFFFFFFFF>
	[[nodiscard]] inline Register_ _make_register_from_movemask(const unsigned long long mask_)
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			if constexpr (EmuSIMD::TMP::is_floating_point_simd_register_v<register_type_uq>)
			{
				return _make_register_from_movemask_fp<register_type_uq, Bits_>(mask_);
			}
			else if constexpr (EmuSIMD::TMP::is_integral_simd_register_v<register_type_uq>)
			{
				return _make_register_from_movemask_int<register_type_uq, PerElementWidthIfIntegral_, Bits_>(mask_);
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to make a SIMD register from a move mask using EmuSIMD helpers, but the requested output register is not a supported SIMD register.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to make a SIMD register from a move mask using EmuSIMD helpers, but the requested output register is not recognised as a SIMD register.");
		}
	}

	template<class Register_, std::size_t PerElementWidthIfIntegral_ = 32, std::int64_t Bits_ = 0xFFFFFFFFFFFFFFFF>
	[[nodiscard]] inline Register_ _make_register_from_movemask(const signed long long mask_)
	{
		return _make_register_from_movemask<Register_, PerElementWidthIfIntegral_, Bits_>(static_cast<unsigned long long>(mask_));
	}
#pragma endregion

#pragma region MOVEMASK_EXTRACTION
	template<class Register_>
	[[nodiscard]] inline auto _movemask(Register_ register_)
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x4>)
			{
				return _mm_movemask_ps(register_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x8>)
			{
				return _mm256_movemask_ps(register_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x16>)
			{
				int mask_ = _mm256_movemask_ps(_cast<EmuSIMD::f32x8>(register_)) << 8;
				return mask_ | _mm256_movemask_ps(_mm512_extractf32x8_ps(register_, 1));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x2>)
			{
				return _mm_movemask_pd(register_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x4>)
			{
				return _mm256_movemask_pd(register_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x8>)
			{
				int mask_ = _mm256_movemask_pd(_cast<EmuSIMD::f64x4>(register_)) << 4;
				return mask_ | _mm256_movemask_pd(_mm512_extractf64x4_pd(register_, 1));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i128_generic>)
			{
				return _mm_movemask_epi8(register_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i256_generic>)
			{
				return _mm256_movemask_epi8(register_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i256_generic>)
			{
				std::int64_t mask_ = _mm256_movemask_epi8(_cast<EmuSIMD::i256_generic>(register_));
				mask_ <<= 32;
				return mask_ | _mm256_movemask_epi8(_mm512_extracti32x8_epi32(register_, 1));
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to acquire a movemask via EmuSIMD helpers, but the provided SIMD register is not supported for this operation.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to acquire a movemask via EmuSIMD helpers, but the passed Register_ type is not recognised as a supported SIMD register.");
		}
	}
#pragma endregion

#pragma region GENERIC_CMP_FUNCS
	template<int CmpFlags_, class Register_>
	[[nodiscard]] inline unsigned long long _cmp_fp_mask(Register_ lhs_, Register_ rhs_)
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x4>)
			{
				return static_cast<unsigned long long>(_mm_cmp_ps_mask(lhs_, rhs_, CmpFlags_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x8>)
			{
				return static_cast<unsigned long long>(_mm256_cmp_ps_mask(lhs_, rhs_, CmpFlags_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x16>)
			{
				return static_cast<unsigned long long>(_mm512_cmp_ps_mask(lhs_, rhs_, CmpFlags_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x2>)
			{
				return static_cast<unsigned long long>(_mm_cmp_pd_mask(lhs_, rhs_, CmpFlags_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x4>)
			{
				return static_cast<unsigned long long>(_mm256_cmp_pd_mask(lhs_, rhs_, CmpFlags_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x8>)
			{
				return static_cast<unsigned long long>(_mm512_cmp_pd_mask(lhs_, rhs_, CmpFlags_));
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform a comparison of floating-point SIMD registers using EmuSIMD helpers, but the provided floating-point SIMD register type is not supported for this operation.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform a comparison of floating-point SIMD registers using EmuSIMD helpers, but the provided Register_ type was not recognised as a SIMD register.");
		}
	}
	template<int CmpFlags_, std::size_t PerElementWidth_, bool Signed_, class Register_>
	[[nodiscard]] inline unsigned long long _cmp_int_mask(Register_ lhs_, Register_ rhs_)
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			if constexpr (EmuSIMD::TMP::_assert_valid_simd_int_element_width<PerElementWidth_>())
			{
				if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i128_generic>)
				{
					if constexpr (PerElementWidth_ == 8)
					{
						if constexpr (Signed_)
						{
							return _mm_cmp_epi8_mask(lhs_, rhs_, CmpFlags_);
						}
						else
						{
							return _mm_cmp_epu8_mask(lhs_, rhs_, CmpFlags_);
						}
					}
					else if constexpr (PerElementWidth_ == 16)
					{
						if constexpr (Signed_)
						{
							return _mm_cmp_epi16_mask(lhs_, rhs_, CmpFlags_);
						}
						else
						{
							return _mm_cmp_epu16_mask(lhs_, rhs_, CmpFlags_);
						}
					}
					else if constexpr (PerElementWidth_ == 32)
					{
						if constexpr (Signed_)
						{
							return _mm_cmp_epi32_mask(lhs_, rhs_, CmpFlags_);
						}
						else
						{
							return _mm_cmp_epu32_mask(lhs_, rhs_, CmpFlags_);
						}
					}
					else
					{
						if constexpr (Signed_)
						{
							return _mm_cmp_epi64_mask(lhs_, rhs_, CmpFlags_);
						}
						else
						{
							return _mm_cmp_epu64_mask(lhs_, rhs_, CmpFlags_);
						}
					}
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i256_generic>)
				{
					if constexpr (PerElementWidth_ == 8)
					{
						if constexpr (Signed_)
						{
							return _mm256_cmp_epi8_mask(lhs_, rhs_, CmpFlags_);
						}
						else
						{
							return _mm256_cmp_epu8_mask(lhs_, rhs_, CmpFlags_);
						}
					}
					else if constexpr (PerElementWidth_ == 16)
					{
						if constexpr (Signed_)
						{
							return _mm256_cmp_epi16_mask(lhs_, rhs_, CmpFlags_);
						}
						else
						{
							return _mm256_cmp_epu16_mask(lhs_, rhs_, CmpFlags_);
						}
					}
					else if constexpr (PerElementWidth_ == 32)
					{
						if constexpr (Signed_)
						{
							return _mm256_cmp_epi32_mask(lhs_, rhs_, CmpFlags_);
						}
						else
						{
							return _mm256_cmp_epu32_mask(lhs_, rhs_, CmpFlags_);
						}
					}
					else
					{
						if constexpr (Signed_)
						{
							return _mm256_cmp_epi64_mask(lhs_, rhs_, CmpFlags_);
						}
						else
						{
							return _mm256_cmp_epu64_mask(lhs_, rhs_, CmpFlags_);
						}
					}
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i512_generic>)
				{
					if constexpr (PerElementWidth_ == 8)
					{
						if constexpr (Signed_)
						{
							return _mm512_cmp_epi8_mask(lhs_, rhs_, CmpFlags_);
						}
						else
						{
							return _mm512_cmp_epu8_mask(lhs_, rhs_, CmpFlags_);
						}
					}
					else if constexpr (PerElementWidth_ == 16)
					{
						if constexpr (Signed_)
						{
							return _mm512_cmp_epi16_mask(lhs_, rhs_, CmpFlags_);
						}
						else
						{
							return _mm512_cmp_epu16_mask(lhs_, rhs_, CmpFlags_);
						}
					}
					else if constexpr (PerElementWidth_ == 32)
					{
						if constexpr (Signed_)
						{
							return _mm512_cmp_epi32_mask(lhs_, rhs_, CmpFlags_);
						}
						else
						{
							return _mm512_cmp_epu32_mask(lhs_, rhs_, CmpFlags_);
						}
					}
					else
					{
						if constexpr (Signed_)
						{
							return _mm512_cmp_epi64_mask(lhs_, rhs_, CmpFlags_);
						}
						else
						{
							return _mm512_cmp_epu64_mask(lhs_, rhs_, CmpFlags_);
						}
					}
				}
				else
				{
					static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform a comparison of integral SIMD registers using EmuSIMD helpers, but the provided integral SIMD register type is not supported for this operation.");
				}
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform a comparison of integral SIMD registers using EmuSIMD helpers, but the provided PerElementWidth_ is invalid.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform a comparison of integral SIMD registers using EmuSIMD helpers, but the provided Register_ type was not recognised as a SIMD register.");
		}
	}
	template<int CmpFlags_, std::size_t PerElementWidthIfInt_ = 32, bool SignedIfInt_ = true, class Register_>
	[[nodiscard]] inline unsigned long long _cmp_mask(Register_ lhs_, Register_ rhs_)
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			if constexpr (EmuSIMD::TMP::is_floating_point_simd_register_v<register_type_uq>)
			{
				return _cmp_fp_mask(lhs_, rhs_, CmpFlags_);
			}
			else if constexpr (EmuSIMD::TMP::is_integral_simd_register_v<register_type_uq>)
			{
				return _cmp_int_mask<PerElementWidthIfInt_, SignedIfInt_>(lhs_, rhs_, CmpFlags_);
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform a comparison of SIMD registers using EmuSIMD helpers, but the provided SIMD Register_ type is not supported for this operation.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform a comparison of SIMD registers using EmuSIMD helpers, but the provided Register_ type was not recognised as a SIMD register.");
		}
	}

	template<int CmpFlags_, std::size_t PerElementWidth_, bool Signed_, class Register_>
	[[nodiscard]] inline Register_ _cmp_int(Register_ lhs_, Register_ rhs_)
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			if constexpr (EmuSIMD::TMP::_assert_valid_simd_int_element_width<PerElementWidth_>())
			{
				if constexpr (EmuCore::TMP::is_any_comparison_true<std::is_same, register_type_uq, EmuSIMD::i128_generic, EmuSIMD::i256_generic, EmuSIMD::i512_generic>::value)
				{
					return _make_register_from_movemask<register_type_uq, PerElementWidth_>
					(
						_cmp_int_mask<CmpFlags_, PerElementWidth_, Signed_>(lhs_, rhs_)
					);
				}
				else
				{
					static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform a comparison of integral SIMD register using EmuSIMD helpers, but the provided Register_ type was not recognised as a supported integral SIMD register.");
				}
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform a comparison of integral SIMD registers using EmuSIMD helpers, but the provided PerElementWidth_ is invalid.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform a comparison of integral SIMD registers using EmuSIMD helpers, but the provided Register_ type was not recognised as a SIMD register.");
		}
	}
	template<int CmpFlags_, class Register_>
	[[nodiscard]] inline Register_ _cmp_fp(Register_ lhs_, Register_ rhs_)
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x4>)
			{
				return _mm_cmp_ps(lhs_, rhs_, CmpFlags_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x8>)
			{
				return _mm256_cmp_ps(lhs_, rhs_, CmpFlags_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x16>)
			{
				return _make_register_from_movemask<EmuSIMD::f32x16, 32, 0xFFFFFFFF>(static_cast<unsigned long long>(_mm512_cmp_ps_mask(lhs_, rhs_, CmpFlags_)));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x2>)
			{
				return _mm_cmp_pd(lhs_, rhs_, CmpFlags_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x4>)
			{
				return _mm256_cmp_pd(lhs_, rhs_, CmpFlags_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x8>)
			{
				return _make_register_from_movemask<EmuSIMD::f64x8, 64, 0xFFFFFFFFFFFFFFFF>(static_cast<unsigned long long>(_mm512_cmp_pd_mask(lhs_, rhs_, CmpFlags_)));
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform a comparison of floating-point SIMD registers using EmuSIMD helpers, but the provided Register_ type was not recognised as a SIMD register.");
		}
	}
	template<int CmpFlags_, std::size_t PerElementWidthIfInt_ = 32, bool SignedIfInt_ = true, class Register_>
	[[nodiscard]] inline Register_ _cmp(Register_ lhs_, Register_ rhs_)
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			if constexpr (EmuSIMD::TMP::is_floating_point_simd_register_v<register_type_uq>)
			{
				return _cmp_fp<CmpFlags_>(lhs_, rhs_);
			}
			else if constexpr (EmuSIMD::TMP::is_integral_simd_register_v<register_type_uq>)
			{
				return _cmp_int<CmpFlags_, PerElementWidthIfInt_, SignedIfInt_>(lhs_, rhs_);
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform a comparison of SIMD registers using EmuSIMD helpers, but the provided SIMD Register_ type is not supported for this operation.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform a comparison of SIMD registers using EmuSIMD helpers, but the provided Register_ type was not recognised as a SIMD register.");
		}
	}
#pragma endregion

#pragma region CMP_EQ_FUNCS
	template<class Register_>
	[[nodiscard]] inline Register_ _cmp_eq_fp(Register_ lhs_, Register_ rhs_)
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x4>)
			{
				return _mm_cmpeq_ps(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x2>)
			{
				return _mm_cmpeq_pd(lhs_, rhs_);
			}
			else
			{
				return _cmp_fp<_CMP_EQ_OQ>(lhs_, rhs_);
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform an equal comparison of floating-point SIMD registers using EmuSIMD helpers, but the provided Register_ type was not recognised as a SIMD register.");
		}
	}
	template<std::size_t PerElementWidth_, bool Signed_, class Register_>
	[[nodiscard]] inline Register_ _cmp_eq_int(Register_ lhs_, Register_ rhs_)
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			if constexpr (EmuSIMD::TMP::_assert_valid_simd_int_element_width<PerElementWidth_>())
			{
				if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i128_generic>)
				{
					if constexpr (PerElementWidth_ == 8)
					{
						return _mm_cmpeq_epi8(lhs_, rhs_);
					}
					else if constexpr (PerElementWidth_ == 16)
					{
						return _mm_cmpeq_epi16(lhs_, rhs_);
					}
					else if constexpr (PerElementWidth_ == 32)
					{
						return _mm_cmpeq_epi32(lhs_, rhs_);
					}
					else
					{
						return _mm_cmpeq_epi64(lhs_, rhs_);
					}
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i256_generic>)
				{
					if constexpr (PerElementWidth_ == 8)
					{
						return _mm256_cmpeq_epi8(lhs_, rhs_);
					}
					else if constexpr (PerElementWidth_ == 16)
					{
						return _mm256_cmpeq_epi16(lhs_, rhs_);
					}
					else if constexpr (PerElementWidth_ == 32)
					{
						return _mm256_cmpeq_epi32(lhs_, rhs_);
					}
					else
					{
						return _mm256_cmpeq_epi64(lhs_, rhs_);
					}
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i512_generic>)
				{
					if constexpr (PerElementWidth_ == 8)
					{
						if constexpr (Signed_)
						{
							return _make_register_from_movemask<register_type_uq, 8>(_mm512_cmpeq_epi8_mask(lhs_, rhs_));
						}
						else
						{
							return _make_register_from_movemask<register_type_uq, 8>(_mm512_cmpeq_epu8_mask(lhs_, rhs_));
						}
					}
					else if constexpr (PerElementWidth_ == 16)
					{
						if constexpr (Signed_)
						{
							return _make_register_from_movemask<register_type_uq, 16>(_mm512_cmpeq_epi16_mask(lhs_, rhs_));
						}
						else
						{
							return _make_register_from_movemask<register_type_uq, 16>(_mm512_cmpeq_epu16_mask(lhs_, rhs_));
						}
					}
					else if constexpr (PerElementWidth_ == 32)
					{
						if constexpr (Signed_)
						{
							return _make_register_from_movemask<register_type_uq, 32>(_mm512_cmpeq_epi32_mask(lhs_, rhs_));
						}
						else
						{
							return _make_register_from_movemask<register_type_uq, 32>(_mm512_cmpeq_epu32_mask(lhs_, rhs_));
						}
					}
					else
					{
						if constexpr (Signed_)
						{
							return _make_register_from_movemask<register_type_uq, 64>(_mm512_cmpeq_epi64_mask(lhs_, rhs_));
						}
						else
						{
							return _make_register_from_movemask<register_type_uq, 64>(_mm512_cmpeq_epu64_mask(lhs_, rhs_));
						}
					}
				}
				else
				{
					static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform an equal comparison of integral SIMD register using EmuSIMD helpers, but the provided Register_ type was not recognised as a supported integral SIMD register.");
				}
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform an equal comparison of integral SIMD registers using EmuSIMD helpers, but the provided PerElementWidth_ is invalid.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform an equal comparison of integral SIMD registers using EmuSIMD helpers, but the provided Register_ type was not recognised as a SIMD register.");
		}
	}
	template<std::size_t PerElementWidthIfInt_ = 32, bool SignedIfInt_ = true, class Register_>
	[[nodiscard]] inline Register_ _cmp_eq(Register_ lhs_, Register_ rhs_)
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			if constexpr (EmuSIMD::TMP::is_floating_point_simd_register_v<register_type_uq>)
			{
				return _cmp_eq_fp(lhs_, rhs_);
			}
			else if constexpr (EmuSIMD::TMP::is_integral_simd_register_v<register_type_uq>)
			{
				return _cmp_eq_int<PerElementWidthIfInt_, SignedIfInt_>(lhs_, rhs_);
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform an equal comparison of SIMD registers using EmuSIMD helpers, but the provided Register_ type is not a supported SIMD register for this operation.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform an equal comparison of SIMD registers using EmuSIMD helpers, but the provided Register_ type was not recognised as a SIMD register.");
		}
	}
#pragma endregion

#pragma region CMP_NEQ_FUNCS
	template<std::size_t PerElementWidth_, bool Signed_, class Register_>
	[[nodiscard]] inline Register_ _cmp_neq_int(Register_ lhs_, Register_ rhs_)
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			if constexpr (EmuSIMD::TMP::_assert_valid_simd_int_element_width<PerElementWidth_>())
			{
				if constexpr (EmuCore::TMP::is_any_comparison_true<std::is_same, register_type_uq, EmuSIMD::i128_generic, EmuSIMD::i256_generic, EmuSIMD::i512_generic>::value)
				{
					return _cmp_int<_CMP_NEQ_UQ, PerElementWidth_, Signed_>(lhs_, rhs_);
				}
				else
				{
					static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform a not-equal comparison of integral SIMD registers using EmuSIMD helpers, but the provided Register_ type is not a supported integral SIMD register.");
				}
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform a not-equal comparison of integral SIMD registers using EmuSIMD helpers, but provided an invalid PerElementWidth_.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform a not-equal comparison of integral SIMD registers using EmuSIMD helpers, but the provided Register_ type was not recognised as a SIMD register.");
		}
	}
	template<class Register_>
	[[nodiscard]] inline Register_ _cmp_neq_fp(Register_ lhs_, Register_ rhs_)
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x4>)
			{
				return _mm_cmpneq_ps(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x2>)
			{
				return _mm_cmpneq_pd(lhs_, rhs_);
			}
			else if constexpr (EmuCore::TMP::is_any_comparison_true<std::is_same, register_type_uq, EmuSIMD::f32x8, EmuSIMD::f32x16, EmuSIMD::f64x4, EmuSIMD::f64x8>::value)
			{
				return _cmp_fp<_CMP_NEQ_UQ>(lhs_, rhs_);
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform a not-equal comparison of floating-point SIMD registers using EmuSIMD helpers, but the provided Register_ type is not a supported floating-point SIMD register.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform a not-equal comparison of floating-point SIMD registers using EmuSIMD helpers, but the provided Register_ type was not recognised as a SIMD register.");
		}
	}
	template<std::size_t PerElementWidthIfInt_ = 32, bool SignedIfInt_ = true, class Register_>
	[[nodiscard]] inline Register_ _cmp_neq(Register_ lhs_, Register_ rhs_)
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			if constexpr (EmuSIMD::TMP::is_floating_point_simd_register_v<register_type_uq>)
			{
				return _cmp_neq_fp(lhs_, rhs_);
			}
			else if constexpr (EmuSIMD::TMP::is_integral_simd_register_v<register_type_uq>)
			{
				return _cmp_neq_int<PerElementWidthIfInt_, SignedIfInt_>(lhs_, rhs_);
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform a not-equal comparison of SIMD registers using EmuSIMD helpers, but the provided Register_ type is not a supported SIMD register for this operation.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform a not-equal comparison of SIMD registers using EmuSIMD helpers, but the provided Register_ type was not recognised as a SIMD register.");
		}
	}
#pragma endregion

#pragma region CMP_LT_FUNCS
	template<std::size_t PerElementWidth_, bool Signed_, class Register_>
	[[nodiscard]] inline Register_ _cmp_lt_int(Register_ lhs_, Register_ rhs_)
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			if constexpr (EmuSIMD::TMP::_assert_valid_simd_int_element_width<PerElementWidth_>())
			{
				if constexpr (!Signed_ || (PerElementWidth_ == 64))
				{
					if constexpr (EmuCore::TMP::is_any_comparison_true<std::is_same, register_type_uq, EmuSIMD::i128_generic, EmuSIMD::i256_generic, EmuSIMD::i512_generic>::value)
					{
						return _cmp_int<_CMP_LT_OS, PerElementWidth_, false>(lhs_, rhs_);
					}
					else
					{
						static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform a less-than comparison of unsigned integral SIMD registers using EmuSIMD helpers, but the provided Register_ type is not a supported integral SIMD register.");
					}
				}
				else
				{
					// Only valid widths allowed, and 64-bit width is excluded before this point, so only need to differentiate 8-, 16-, and 32-bit widths.
					if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i128_generic>)
					{
						if constexpr (PerElementWidth_ == 8)
						{
							return _mm_cmplt_epi8(lhs_, rhs_);
						}
						else if constexpr (PerElementWidth_ == 16)
						{
							return _mm_cmplt_epi16(lhs_, rhs_);
						}
						else
						{
							return _mm_cmplt_epi32(lhs_, rhs_);
						}
					}
					else if constexpr (EmuCore::TMP::is_any_comparison_true<std::is_same, register_type_uq, EmuSIMD::i256_generic, EmuSIMD::i512_generic>::value)
					{
						// Remaining registers don't have built in _cmplt_ non-mask funcs, so defer to that
						return _cmp_int<_CMP_LT_OS, PerElementWidth_, true>(lhs_, rhs_);
					}
					else
					{
						static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform a less-than comparison of signed integral SIMD registers using EmuSIMD helpers, but the provided Register_ type is not a supported integral SIMD register.");
					}
				}
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform a less-than comparison of integral SIMD registers using EmuSIMD helpers, but provided an invalid PerElementWidth_.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform a less-than comparison of integral SIMD registers using EmuSIMD helpers, but the provided Register_ type was not recognised as a SIMD register.");
		}
	}
	template<class Register_>
	[[nodiscard]] inline Register_ _cmp_lt_fp(Register_ lhs_, Register_ rhs_)
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x4>)
			{
				return _mm_cmplt_ps(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x2>)
			{
				return _mm_cmplt_pd(lhs_, rhs_);
			}
			else if constexpr (EmuCore::TMP::is_any_comparison_true<std::is_same, register_type_uq, EmuSIMD::f32x8, EmuSIMD::f64x4, EmuSIMD::f32x16, EmuSIMD::f64x8>::value)
			{
				return _cmp_fp<_CMP_LT_OS>(lhs_, rhs_);
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform a less-than comparison of floating-point SIMD registers using EmuSIMD helpers, but the provided Register_ type is not a supported floating-point SIMD register for this operation.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform a less-than comparison of floating-point SIMD registers using EmuSIMD helpers, but the provided Register_ type was not recognised as a SIMD register.");
		}
	}
	template<std::size_t PerElementWidthIfInt_ = 32, bool SignedIfInt_ = true, class Register_>
	[[nodiscard]] inline Register_ _cmp_lt(Register_ lhs_, Register_ rhs_)
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			if constexpr (EmuSIMD::TMP::is_floating_point_simd_register_v<register_type_uq>)
			{
				return _cmp_lt_fp(lhs_, rhs_);
			}
			else if constexpr (EmuSIMD::TMP::is_integral_simd_register_v<register_type_uq>)
			{
				return _cmp_lt_int<PerElementWidthIfInt_, SignedIfInt_>(lhs_, rhs_);
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform a less-than comparison of SIMD registers using EmuSIMD helpers, but the provided Register_ type is not a supported SIMD register for this operation.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform a less-than comparison of SIMD registers using EmuSIMD helpers, but the provided Register_ type was not recognised as a SIMD register.");
		}
	}
#pragma endregion

#pragma region CMP_GT_FUNCS
	template<std::size_t PerElementWidth_, bool Signed_, class Register_>
	[[nodiscard]] inline Register_ _cmp_gt_int(Register_ lhs_, Register_ rhs_)
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			if constexpr (EmuSIMD::TMP::_assert_valid_simd_int_element_width<PerElementWidth_>())
			{
				if constexpr (!Signed_)
				{
					if constexpr (EmuCore::TMP::is_any_comparison_true<std::is_same, register_type_uq, EmuSIMD::i128_generic, EmuSIMD::i256_generic, EmuSIMD::i512_generic>::value)
					{
						return _cmp_int<_CMP_NLE_US, PerElementWidth_, false>(lhs_, rhs_);
					}
					else
					{
						static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform a greater-than comparison of unsigned integral SIMD registers using EmuSIMD helpers, but the provided Register_ type is not a supported integral SIMD register.");
					}
				}
				else
				{
					// Signed comparisons
					if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i128_generic>)
					{
						if constexpr (PerElementWidth_ == 8)
						{
							return _mm_cmpgt_epi8(lhs_, rhs_);
						}
						else if constexpr (PerElementWidth_ == 16)
						{
							return _mm_cmpgt_epi16(lhs_, rhs_);
						}
						else if constexpr(PerElementWidth_ == 32)
						{
							return _mm_cmpgt_epi32(lhs_, rhs_);
						}
						else
						{
							return _mm_cmpgt_epi64(lhs_, rhs_);
						}
					}
					else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i256_generic>)
					{
						if constexpr (PerElementWidth_ == 8)
						{
							return _mm256_cmpgt_epi8(lhs_, rhs_);
						}
						else if constexpr (PerElementWidth_ == 16)
						{
							return _mm256_cmpgt_epi16(lhs_, rhs_);
						}
						else if constexpr (PerElementWidth_ == 32)
						{
							return _mm256_cmpgt_epi32(lhs_, rhs_);
						}
						else
						{
							return _mm256_cmpgt_epi64(lhs_, rhs_);
						}
					}
					else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i512_generic>)
					{
						return _cmp_int<_CMP_NLE_US, PerElementWidth_, true>(lhs_, rhs_);
					}
					else
					{
						static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform a greater-than comparison of signed integral SIMD registers using EmuSIMD helpers, but the provided Register_ type is not a supported integral SIMD register.");
					}
				}
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform a greater-than comparison of integral SIMD registers using EmuSIMD helpers, but provided an invalid PerElementWidth_.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform a greater-than comparison of integral SIMD registers using EmuSIMD helpers, but the provided Register_ type was not recognised as a SIMD register.");
		}
	}
	template<class Register_>
	[[nodiscard]] inline Register_ _cmp_gt_fp(Register_ lhs_, Register_ rhs_)
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x4>)
			{
				return _mm_cmpgt_ps(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x2>)
			{
				return _mm_cmpgt_pd(lhs_, rhs_);
			}
			else if constexpr (EmuCore::TMP::is_any_comparison_true<std::is_same, register_type_uq, EmuSIMD::f32x8, EmuSIMD::f64x4, EmuSIMD::f32x16, EmuSIMD::f64x8>::value)
			{
				return _cmp_fp<_CMP_NLE_US>(lhs_, rhs_);
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform a greater-than comparison of floating-point SIMD registers using EmuSIMD helpers, but the provided Register_ type is not a supported floating-point SIMD register for this operation.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform a greater-than comparison of floating-point SIMD registers using EmuSIMD helpers, but the provided Register_ type was not recognised as a SIMD register.");
		}
	}
	template<std::size_t PerElementWidthIfInt_ = 32, bool SignedIfInt_ = true, class Register_>
	[[nodiscard]] inline Register_ _cmp_gt(Register_ lhs_, Register_ rhs_)
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			if constexpr (EmuSIMD::TMP::is_floating_point_simd_register_v<register_type_uq>)
			{
				return _cmp_gt_fp(lhs_, rhs_);
			}
			else if constexpr (EmuSIMD::TMP::is_integral_simd_register_v<register_type_uq>)
			{
				return _cmp_gt_int<PerElementWidthIfInt_, SignedIfInt_>(lhs_, rhs_);
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform a greater-than comparison of SIMD registers using EmuSIMD helpers, but the provided Register_ type is not a supported SIMD register for this operation.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform a greater-than comparison of SIMD registers using EmuSIMD helpers, but the provided Register_ type was not recognised as a SIMD register.");
		}
	}
#pragma endregion

#pragma region CMP_LE_FUNCS
	template<std::size_t PerElementWidth_, bool Signed_, class Register_>
	[[nodiscard]] inline Register_ _cmp_le_int(Register_ lhs_, Register_ rhs_)
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			if constexpr (EmuSIMD::TMP::_assert_valid_simd_int_element_width<PerElementWidth_>)
			{
				if constexpr (EmuCore::TMP::is_any_comparison_true<std::is_same, register_type_uq, EmuSIMD::i128_generic, EmuSIMD::i256_generic, EmuSIMD::i512_generic>::value)
				{
					return _cmp_int<_CMP_LE_OS, PerElementWidth_, Signed_>(lhs_, rhs_);
				}
				else
				{
					static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform a less-equal comparison of signed integral SIMD registers using EmuSIMD helpers, but the provided Register_ type is not a supported integral SIMD register.");
				}
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform a less-equal comparison of integral SIMD registers using EmuSIMD helpers, but provided an invalid PerElementWidth_.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform a less-equal comparison of integral SIMD registers using EmuSIMD helpers, but the provided Register_ type was not recognised as a SIMD register.");
		}
	}
	template<class Register_>
	[[nodiscard]] inline Register_ _cmp_le_fp(Register_ lhs_, Register_ rhs_)
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x4>)
			{
				return _mm_cmple_ps(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x2>)
			{
				return _mm_cmple_pd(lhs_, rhs_);
			}
			else if constexpr (EmuCore::TMP::is_any_comparison_true<std::is_same, register_type_uq, EmuSIMD::f32x8, EmuSIMD::f64x4, EmuSIMD::f32x16, EmuSIMD::f64x8>::value)
			{
				return _cmp_fp<_CMP_LE_OS>(lhs_, rhs_);
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform a less-equal comparison of floating-point SIMD registers using EmuSIMD helpers, but the provided Register_ type is not a supported floating-point SIMD register for this operation.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform a less-equal comparison of floating-point SIMD registers using EmuSIMD helpers, but the provided Register_ type was not recognised as a SIMD register.");
		}
	}
	template<std::size_t PerElementWidthIfInt_ = 32, bool SignedIfInt_ = true, class Register_>
	[[nodiscard]] inline Register_ _cmp_le(Register_ lhs_, Register_ rhs_)
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			if constexpr (EmuSIMD::TMP::is_floating_point_simd_register_v<register_type_uq>)
			{
				return _cmp_le_fp(lhs_, rhs_);
			}
			else if constexpr (EmuSIMD::TMP::is_integral_simd_register_v<register_type_uq>)
			{
				return _cmp_le_int<PerElementWidthIfInt_, SignedIfInt_>(lhs_, rhs_);
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform a less-equal comparison of SIMD registers using EmuSIMD helpers, but the provided Register_ type is not a supported SIMD register for this operation.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform a less-equal comparison of SIMD registers using EmuSIMD helpers, but the provided Register_ type was not recognised as a SIMD register.");
		}
	}
#pragma endregion

#pragma region CMP_GE_FUNCS
	template<std::size_t PerElementWidth_, bool Signed_, class Register_>
	[[nodiscard]] inline Register_ _cmp_ge_int(Register_ lhs_, Register_ rhs_)
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			if constexpr (EmuSIMD::TMP::_assert_valid_simd_int_element_width<PerElementWidth_>())
			{
				if constexpr (EmuCore::TMP::is_any_comparison_true<std::is_same, register_type_uq, EmuSIMD::i128_generic, EmuSIMD::i256_generic, EmuSIMD::i512_generic>::value)
				{
					return _cmp_int<_CMP_NLT_US, PerElementWidth_, Signed_>(lhs_, rhs_);
				}
				else
				{
					static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform a greater-equal comparison of signed integral SIMD registers using EmuSIMD helpers, but the provided Register_ type is not a supported integral SIMD register.");
				}
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform a greater-equal comparison of integral SIMD registers using EmuSIMD helpers, but provided an invalid PerElementWidth_.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform a greater-equal comparison of integral SIMD registers using EmuSIMD helpers, but the provided Register_ type was not recognised as a SIMD register.");
		}
	}
	template<class Register_>
	[[nodiscard]] inline Register_ _cmp_ge_fp(Register_ lhs_, Register_ rhs_)
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x4>)
			{
				return _mm_cmpge_ps(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x2>)
			{
				return _mm_cmpge_pd(lhs_, rhs_);
			}
			else if constexpr (EmuCore::TMP::is_any_comparison_true<std::is_same, register_type_uq, EmuSIMD::f32x8, EmuSIMD::f64x4, EmuSIMD::f32x16, EmuSIMD::f64x8>::value)
			{
				return _cmp_fp<_CMP_NLT_US>(lhs_, rhs_);
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform a greater-equal comparison of floating-point SIMD registers using EmuSIMD helpers, but the provided Register_ type is not a supported floating-point SIMD register for this operation.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform a greater-equal comparison of floating-point SIMD registers using EmuSIMD helpers, but the provided Register_ type was not recognised as a SIMD register.");
		}
	}
	template<std::size_t PerElementWidthIfInt_ = 32, bool SignedIfInt_ = true, class Register_>
	[[nodiscard]] inline Register_ _cmp_ge(Register_ lhs_, Register_ rhs_)
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			if constexpr (EmuSIMD::TMP::is_floating_point_simd_register_v<register_type_uq>)
			{
				return _cmp_ge_fp(lhs_, rhs_);
			}
			else if constexpr (EmuSIMD::TMP::is_integral_simd_register_v<register_type_uq>)
			{
				return _cmp_ge_int<PerElementWidthIfInt_, SignedIfInt_>(lhs_, rhs_);
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform a greater-equal comparison of SIMD registers using EmuSIMD helpers, but the provided Register_ type is not a supported SIMD register for this operation.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform a greater-equal comparison of SIMD registers using EmuSIMD helpers, but the provided Register_ type was not recognised as a SIMD register.");
		}
	}
#pragma endregion

#pragma region CMP_NEAR_HELPERS
	template<std::size_t PerElementWidthIfInt_, bool SignedIfInt_, class Register_>
	[[nodiscard]] inline Register_ _cmp_near_equal(Register_ a_, Register_ b_)
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x4>)
			{
				return EmuSIMD::Funcs::cmpnear_f32x4(a_, b_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x8>)
			{
				return EmuSIMD::Funcs::cmpnear_f32x8(a_, b_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x16>)
			{
				return EmuSIMD::Funcs::cmpnear_f32x16(a_, b_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x2>)
			{
				return EmuSIMD::Funcs::cmpnear_f64x2(a_, b_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x4>)
			{
				return EmuSIMD::Funcs::cmpnear_f64x4(a_, b_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x8>)
			{
				return EmuSIMD::Funcs::cmpnear_f64x8(a_, b_);
			}
			else if constexpr (EmuCore::TMP::is_any_comparison_true<std::is_same, register_type_uq, EmuSIMD::i128_generic, EmuSIMD::i256_generic, EmuSIMD::i512_generic>::value)
			{
				if constexpr (EmuSIMD::TMP::_assert_valid_simd_int_element_width<PerElementWidthIfInt_>())
				{
					if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i128_generic>)
					{
						if constexpr (PerElementWidthIfInt_ == 8)
						{
							if constexpr (SignedIfInt_)
							{
								return EmuSIMD::Funcs::cmpnear_i8x16(a_, b_);
							}
							else
							{
								return EmuSIMD::Funcs::cmpnear_u8x16(a_, b_);
							}
						}
						else if constexpr (PerElementWidthIfInt_ == 16)
						{
							if constexpr (SignedIfInt_)
							{
								return EmuSIMD::Funcs::cmpnear_i16x8(a_, b_);
							}
							else
							{
								return EmuSIMD::Funcs::cmpnear_u16x8(a_, b_);
							}
						}
						else if constexpr (PerElementWidthIfInt_ == 32)
						{
							if constexpr (SignedIfInt_)
							{
								return EmuSIMD::Funcs::cmpnear_i32x4(a_, b_);
							}
							else
							{
								return EmuSIMD::Funcs::cmpnear_u32x4(a_, b_);
							}
						}
						else
						{
							if constexpr (SignedIfInt_)
							{
								return EmuSIMD::Funcs::cmpnear_i64x2(a_, b_);
							}
							else
							{
								return EmuSIMD::Funcs::cmpnear_u64x2(a_, b_);
							}
						}
					}
					else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i256_generic>)
					{
						if constexpr (PerElementWidthIfInt_ == 8)
						{
							if constexpr (SignedIfInt_)
							{
								return EmuSIMD::Funcs::cmpnear_i8x32(a_, b_);
							}
							else
							{
								return EmuSIMD::Funcs::cmpnear_u8x32(a_, b_);
							}
						}
						else if constexpr (PerElementWidthIfInt_ == 16)
						{
							if constexpr (SignedIfInt_)
							{
								return EmuSIMD::Funcs::cmpnear_i16x16(a_, b_);
							}
							else
							{
								return EmuSIMD::Funcs::cmpnear_u16x16(a_, b_);
							}
						}
						else if constexpr (PerElementWidthIfInt_ == 32)
						{
							if constexpr (SignedIfInt_)
							{
								return EmuSIMD::Funcs::cmpnear_i32x8(a_, b_);
							}
							else
							{
								return EmuSIMD::Funcs::cmpnear_u32x8(a_, b_);
							}
						}
						else
						{
							if constexpr (SignedIfInt_)
							{
								return EmuSIMD::Funcs::cmpnear_i64x4(a_, b_);
							}
							else
							{
								return EmuSIMD::Funcs::cmpnear_u64x4(a_, b_);
							}
						}
					}
					else
					{
						if constexpr (PerElementWidthIfInt_ == 8)
						{
							if constexpr (SignedIfInt_)
							{
								return EmuSIMD::Funcs::cmpnear_i8x64(a_, b_);
							}
							else
							{
								return EmuSIMD::Funcs::cmpnear_u8x64(a_, b_);
							}
						}
						else if constexpr (PerElementWidthIfInt_ == 16)
						{
							if constexpr (SignedIfInt_)
							{
								return EmuSIMD::Funcs::cmpnear_i16x32(a_, b_);
							}
							else
							{
								return EmuSIMD::Funcs::cmpnear_u16x32(a_, b_);
							}
						}
						else if constexpr (PerElementWidthIfInt_ == 32)
						{
							if constexpr (SignedIfInt_)
							{
								return EmuSIMD::Funcs::cmpnear_i32x16(a_, b_);
							}
							else
							{
								return EmuSIMD::Funcs::cmpnear_u32x16(a_, b_);
							}
						}
						else
						{
							if constexpr (SignedIfInt_)
							{
								return EmuSIMD::Funcs::cmpnear_i64x8(a_, b_);
							}
							else
							{
								return EmuSIMD::Funcs::cmpnear_u64x8(a_, b_);
							}
						}
					}
				}
				else
				{
					static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to determine if the elements of two SIMD registers are near-equal via EmuSIMD helpers, but the provided PerElementWidth_ is invalid.");
				}
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i8x16>)
			{
				return EmuSIMD::Funcs::cmpnear_i8x16(a_, b_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i8x32>)
			{
				return EmuSIMD::Funcs::cmpnear_i8x32(a_, b_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i8x64>)
			{
				return EmuSIMD::Funcs::cmpnear_i8x64(a_, b_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u8x16>)
			{
				return EmuSIMD::Funcs::cmpnear_u8x16(a_, b_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u8x32>)
			{
				return EmuSIMD::Funcs::cmpnear_u8x32(a_, b_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u8x64>)
			{
				return EmuSIMD::Funcs::cmpnear_u8x64(a_, b_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i16x8>)
			{
				return EmuSIMD::Funcs::cmpnear_i16x8(a_, b_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i16x16>)
			{
				return EmuSIMD::Funcs::cmpnear_i16x16(a_, b_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i16x32>)
			{
				return EmuSIMD::Funcs::cmpnear_i16x32(a_, b_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u16x8>)
			{
				return EmuSIMD::Funcs::cmpnear_u16x8(a_, b_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u16x16>)
			{
				return EmuSIMD::Funcs::cmpnear_u16x16(a_, b_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u16x32>)
			{
				return EmuSIMD::Funcs::cmpnear_u16x32(a_, b_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i32x4>)
			{
				return EmuSIMD::Funcs::cmpnear_i32x4(a_, b_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i32x8>)
			{
				return EmuSIMD::Funcs::cmpnear_i32x8(a_, b_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i32x16>)
			{
				return EmuSIMD::Funcs::cmpnear_i32x16(a_, b_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u32x4>)
			{
				return EmuSIMD::Funcs::cmpnear_u32x4(a_, b_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u32x8>)
			{
				return EmuSIMD::Funcs::cmpnear_u32x8(a_, b_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u32x16>)
			{
				return EmuSIMD::Funcs::cmpnear_u32x16(a_, b_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i64x2>)
			{
				return EmuSIMD::Funcs::cmpnear_i64x2(a_, b_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i64x4>)
			{
				return EmuSIMD::Funcs::cmpnear_i64x4(a_, b_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i64x8>)
			{
				return EmuSIMD::Funcs::cmpnear_i64x8(a_, b_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u64x2>)
			{
				return EmuSIMD::Funcs::cmpnear_u64x2(a_, b_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u64x4>)
			{
				return EmuSIMD::Funcs::cmpnear_u64x4(a_, b_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u64x8>)
			{
				return EmuSIMD::Funcs::cmpnear_u64x8(a_, b_);
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to determine if the elements of two SIMD registers are near-equal via EmuSIMD registers, but the passed Register_ type is not supported for this operation.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to determine if the elements of two SIMD registers are near-equal via EmuSIMD helpers, but the provided Register_ type is not recognised as a supported SIMD register.");
		}
	}

	template<std::size_t PerElementWidthIfInt_, bool SignedIfInt_, class Register_>
	[[nodiscard]] inline Register_ _cmp_near_equal(Register_ a_, Register_ b_, Register_ epsilon_)
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x4>)
			{
				return EmuSIMD::Funcs::cmpnear_f32x4(a_, b_, epsilon_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x8>)
			{
				return EmuSIMD::Funcs::cmpnear_f32x8(a_, b_, epsilon_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x16>)
			{
				return EmuSIMD::Funcs::cmpnear_f32x16(a_, b_, epsilon_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x2>)
			{
				return EmuSIMD::Funcs::cmpnear_f64x2(a_, b_, epsilon_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x4>)
			{
				return EmuSIMD::Funcs::cmpnear_f64x4(a_, b_, epsilon_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x8>)
			{
				return EmuSIMD::Funcs::cmpnear_f64x8(a_, b_, epsilon_);
			}
			else if constexpr (EmuCore::TMP::is_any_comparison_true<std::is_same, register_type_uq, EmuSIMD::i128_generic, EmuSIMD::i256_generic, EmuSIMD::i512_generic>::value)
			{
				if constexpr (EmuSIMD::TMP::_assert_valid_simd_int_element_width<PerElementWidthIfInt_>())
				{
					if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i128_generic>)
					{
						if constexpr (PerElementWidthIfInt_ == 8)
						{
							if constexpr (SignedIfInt_)
							{
								return EmuSIMD::Funcs::cmpnear_i8x16(a_, b_, epsilon_);
							}
							else
							{
								return EmuSIMD::Funcs::cmpnear_u8x16(a_, b_, epsilon_);
							}
						}
						else if constexpr (PerElementWidthIfInt_ == 16)
						{
							if constexpr (SignedIfInt_)
							{
								return EmuSIMD::Funcs::cmpnear_i16x8(a_, b_, epsilon_);
							}
							else
							{
								return EmuSIMD::Funcs::cmpnear_u16x8(a_, b_, epsilon_);
							}
						}
						else if constexpr (PerElementWidthIfInt_ == 32)
						{
							if constexpr (SignedIfInt_)
							{
								return EmuSIMD::Funcs::cmpnear_i32x4(a_, b_, epsilon_);
							}
							else
							{
								return EmuSIMD::Funcs::cmpnear_u32x4(a_, b_, epsilon_);
							}
						}
						else
						{
							if constexpr (SignedIfInt_)
							{
								return EmuSIMD::Funcs::cmpnear_i64x2(a_, b_, epsilon_);
							}
							else
							{
								return EmuSIMD::Funcs::cmpnear_u64x2(a_, b_, epsilon_);
							}
						}
					}
					else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i256_generic>)
					{
						if constexpr (PerElementWidthIfInt_ == 8)
						{
							if constexpr (SignedIfInt_)
							{
								return EmuSIMD::Funcs::cmpnear_i8x32(a_, b_, epsilon_);
							}
							else
							{
								return EmuSIMD::Funcs::cmpnear_u8x32(a_, b_, epsilon_);
							}
						}
						else if constexpr (PerElementWidthIfInt_ == 16)
						{
							if constexpr (SignedIfInt_)
							{
								return EmuSIMD::Funcs::cmpnear_i16x16(a_, b_, epsilon_);
							}
							else
							{
								return EmuSIMD::Funcs::cmpnear_u16x16(a_, b_, epsilon_);
							}
						}
						else if constexpr (PerElementWidthIfInt_ == 32)
						{
							if constexpr (SignedIfInt_)
							{
								return EmuSIMD::Funcs::cmpnear_i32x8(a_, b_, epsilon_);
							}
							else
							{
								return EmuSIMD::Funcs::cmpnear_u32x8(a_, b_, epsilon_);
							}
						}
						else
						{
							if constexpr (SignedIfInt_)
							{
								return EmuSIMD::Funcs::cmpnear_i64x4(a_, b_, epsilon_);
							}
							else
							{
								return EmuSIMD::Funcs::cmpnear_u64x4(a_, b_, epsilon_);
							}
						}
					}
					else
					{
						if constexpr (PerElementWidthIfInt_ == 8)
						{
							if constexpr (SignedIfInt_)
							{
								return EmuSIMD::Funcs::cmpnear_i8x64(a_, b_, epsilon_);
							}
							else
							{
								return EmuSIMD::Funcs::cmpnear_u8x64(a_, b_, epsilon_);
							}
						}
						else if constexpr (PerElementWidthIfInt_ == 16)
						{
							if constexpr (SignedIfInt_)
							{
								return EmuSIMD::Funcs::cmpnear_i16x32(a_, b_, epsilon_);
							}
							else
							{
								return EmuSIMD::Funcs::cmpnear_u16x32(a_, b_, epsilon_);
							}
						}
						else if constexpr (PerElementWidthIfInt_ == 32)
						{
							if constexpr (SignedIfInt_)
							{
								return EmuSIMD::Funcs::cmpnear_i32x16(a_, b_, epsilon_);
							}
							else
							{
								return EmuSIMD::Funcs::cmpnear_u32x16(a_, b_, epsilon_);
							}
						}
						else
						{
							if constexpr (SignedIfInt_)
							{
								return EmuSIMD::Funcs::cmpnear_i64x8(a_, b_, epsilon_);
							}
							else
							{
								return EmuSIMD::Funcs::cmpnear_u64x8(a_, b_, epsilon_);
							}
						}
					}
				}
				else
				{
					static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to determine if the elements of two SIMD registers are near-equal via EmuSIMD helpers, but the provided PerElementWidth_ is invalid.");
				}
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i8x16>)
			{
				return EmuSIMD::Funcs::cmpnear_i8x16(a_, b_, epsilon_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i8x32>)
			{
				return EmuSIMD::Funcs::cmpnear_i8x32(a_, b_, epsilon_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i8x64>)
			{
				return EmuSIMD::Funcs::cmpnear_i8x64(a_, b_, epsilon_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u8x16>)
			{
				return EmuSIMD::Funcs::cmpnear_u8x16(a_, b_, epsilon_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u8x32>)
			{
				return EmuSIMD::Funcs::cmpnear_u8x32(a_, b_, epsilon_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u8x64>)
			{
				return EmuSIMD::Funcs::cmpnear_u8x64(a_, b_, epsilon_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i16x8>)
			{
				return EmuSIMD::Funcs::cmpnear_i16x8(a_, b_, epsilon_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i16x16>)
			{
				return EmuSIMD::Funcs::cmpnear_i16x16(a_, b_, epsilon_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i16x32>)
			{
				return EmuSIMD::Funcs::cmpnear_i16x32(a_, b_, epsilon_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u16x8>)
			{
				return EmuSIMD::Funcs::cmpnear_u16x8(a_, b_, epsilon_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u16x16>)
			{
				return EmuSIMD::Funcs::cmpnear_u16x16(a_, b_, epsilon_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u16x32>)
			{
				return EmuSIMD::Funcs::cmpnear_u16x32(a_, b_, epsilon_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i32x4>)
			{
				return EmuSIMD::Funcs::cmpnear_i32x4(a_, b_, epsilon_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i32x8>)
			{
				return EmuSIMD::Funcs::cmpnear_i32x8(a_, b_, epsilon_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i32x16>)
			{
				return EmuSIMD::Funcs::cmpnear_i32x16(a_, b_, epsilon_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u32x4>)
			{
				return EmuSIMD::Funcs::cmpnear_u32x4(a_, b_, epsilon_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u32x8>)
			{
				return EmuSIMD::Funcs::cmpnear_u32x8(a_, b_, epsilon_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u32x16>)
			{
				return EmuSIMD::Funcs::cmpnear_u32x16(a_, b_, epsilon_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i64x2>)
			{
				return EmuSIMD::Funcs::cmpnear_i64x2(a_, b_, epsilon_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i64x4>)
			{
				return EmuSIMD::Funcs::cmpnear_i64x4(a_, b_, epsilon_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i64x8>)
			{
				return EmuSIMD::Funcs::cmpnear_i64x8(a_, b_, epsilon_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u64x2>)
			{
				return EmuSIMD::Funcs::cmpnear_u64x2(a_, b_, epsilon_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u64x4>)
			{
				return EmuSIMD::Funcs::cmpnear_u64x4(a_, b_, epsilon_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u64x8>)
			{
				return EmuSIMD::Funcs::cmpnear_u64x8(a_, b_, epsilon_);
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to determine if the elements of two SIMD registers are near-equal via EmuSIMD helpers, but the passed Register_ type is not supported for this operation.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to determine if the elements of two SIMD registers are near-equal via EmuSIMD helpers, but the provided Register_ type is not recognised as a supported SIMD register.");
		}
	}
#pragma endregion
}

#endif
