#ifndef EMU_SIMD_GENERIC_FUNCS_U16X8_H_INC_
#define EMU_SIMD_GENERIC_FUNCS_U16X8_H_INC_ 1

#include "_common_generic_func_helpers.h"

namespace EmuSIMD::Funcs
{
#pragma region SETTERS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 set_u16x8(std::uint16_t e0, std::uint16_t e1, std::uint16_t e2, std::uint16_t e3, std::uint16_t e4, std::uint16_t e5, std::uint16_t e6, std::uint16_t e7)
	{
		return _mm_set_epi16(e0, e1, e2, e3, e4, e5, e6, e7);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 setr_u16x8(std::uint16_t e0, std::uint16_t e1, std::uint16_t e2, std::uint16_t e3, std::uint16_t e4, std::uint16_t e5, std::uint16_t e6, std::uint16_t e7)
	{
		return _mm_setr_epi16(e0, e1, e2, e3, e4, e5, e6, e7);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 set1_u16x8(std::uint16_t all_)
	{
		return _mm_set1_epi16(all_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 load_u16x8(const std::uint16_t* p_to_load_)
	{
		return _mm_load_si128(reinterpret_cast<const __m128i*>(p_to_load_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 setzero_u16x8()
	{
		return _mm_setzero_si128();
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 setmasked_u16x8(std::uint8_t bit_mask_)
	{
		constexpr std::uint16_t element_mask = static_cast<std::uint16_t>(0xFFFF);
		return _mm_set_epi16
		(
			(bit_mask_ & 0x01) * element_mask,
			((bit_mask_ & 0x02) >> 1) * element_mask,
			((bit_mask_ & 0x04) >> 2) * element_mask,
			((bit_mask_ & 0x08) >> 3) * element_mask,
			((bit_mask_ & 0x10) >> 4) * element_mask,
			((bit_mask_ & 0x20) >> 5) * element_mask,
			((bit_mask_ & 0x40) >> 6) * element_mask,
			((bit_mask_ & 0x80) >> 7) * element_mask
		);
	}
#pragma endregion

#pragma region STORES
	EMU_SIMD_COMMON_FUNC_SPEC void store_u16x8(std::uint16_t* p_out_, u16x8_arg a_)
	{
		_mm_store_si128(reinterpret_cast<__m128i*>(p_out_), a_);
	}
#pragma endregion

#pragma region CASTS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 cast_f32x4_u16x8(f32x4_arg a_)
	{
		return _mm_castps_si128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 cast_f32x8_u16x8(f32x8_arg a_)
	{
		return _mm256_castsi256_si128(_mm256_castps_si256(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 cast_f32x16_u16x8(f32x16_arg a_)
	{
		return _mm512_castsi512_si128(_mm512_castps_si512(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 cast_f64x2_u16x8(f64x2_arg a_)
	{
		return _mm_castpd_si128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 cast_f64x4_u16x8(f64x4_arg a_)
	{
		return _mm256_castsi256_si128(_mm256_castpd_si256(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 cast_f64x8_u16x8(f64x8_arg a_)
	{
		return _mm512_castsi512_si128(_mm512_castpd_si512(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 cast_i8x16_u16x8(i8x16_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 cast_i16x8_u16x8(i16x8_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 cast_i32x4_u16x8(i32x4_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 cast_i64x2_u16x8(i64x2_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 cast_i8x32_u16x8(i8x32_arg a_)
	{
		return _mm256_castsi256_si128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 cast_i16x16_u16x8(i16x16_arg a_)
	{
		return _mm256_castsi256_si128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 cast_i32x8_u16x8(i32x8_arg a_)
	{
		return _mm256_castsi256_si128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 cast_i64x4_u16x8(i64x4_arg a_)
	{
		return _mm256_castsi256_si128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 cast_i8x64_u16x8(i8x64_arg a_)
	{
		return _mm512_castsi512_si128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 cast_i16x32_u16x8(i16x32_arg a_)
	{
		return _mm512_castsi512_si128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 cast_i32x16_u16x8(i32x16_arg a_)
	{
		return _mm512_castsi512_si128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 cast_i64x8_u16x8(i64x8_arg a_)
	{
		return _mm512_castsi512_si128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 cast_u8x16_u16x8(u8x16_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 cast_u16x8_u16x8(u16x8_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 cast_u32x4_u16x8(u32x4_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 cast_u64x2_u16x8(u64x2_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 cast_u8x32_u16x8(u8x32_arg a_)
	{
		return _mm256_castsi256_si128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 cast_u16x16_u16x8(u16x16_arg a_)
	{
		return _mm256_castsi256_si128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 cast_u32x8_u16x8(u32x8_arg a_)
	{
		return _mm256_castsi256_si128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 cast_u64x4_u16x8(u64x4_arg a_)
	{
		return _mm256_castsi256_si128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 cast_u8x64_u16x8(u8x64_arg a_)
	{
		return _mm512_castsi512_si128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 cast_u16x32_u16x8(u16x32_arg a_)
	{
		return _mm512_castsi512_si128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 cast_u32x16_u16x8(u32x16_arg a_)
	{
		return _mm512_castsi512_si128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 cast_u64x8_u16x8(u64x8_arg a_)
	{
		return _mm512_castsi512_si128(a_);
	}
#pragma endregion

#pragma region CONVERSIONS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 cvt_f32x4_u16x8(f32x4_arg a_)
	{
		return _mm_cvtepi32_epi16(_mm_cvtps_epi32(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 cvt_f32x8_u16x8(f32x8_arg a_)
	{
		return _mm256_cvtepi32_epi16(_mm256_cvtps_epi32(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 cvt_f32x16_u16x8(f32x16_arg a_)
	{
		return _mm256_castsi256_si128(_mm512_cvtepi32_epi16(_mm512_cvtps_epi32(a_)));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 cvt_f64x2_u16x8(f64x2_arg a_)
	{
		return _mm_cvtepi64_epi16(_mm_cvtpd_epi64(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 cvt_f64x4_u16x8(f64x4_arg a_)
	{
		return _mm256_cvtepi64_epi16(_mm256_cvtpd_epi64(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 cvt_f64x8_u16x8(f64x8_arg a_)
	{
		return _mm512_cvtepi64_epi16(_mm512_cvtpd_epi64(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 cvt_i8x16_u16x8(i8x16_arg a_)
	{
		return _mm_cvtepi8_epi16(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 cvt_i16x8_u16x8(i16x8_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 cvt_i32x4_u16x8(i32x4_arg a_)
	{
		return _mm_cvtepi32_epi16(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 cvt_i64x2_u16x8(i64x2_arg a_)
	{
		return _mm_cvtepi64_epi16(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 cvt_i8x32_u16x8(i8x32_arg a_)
	{
		return _mm256_castsi256_si128(_mm256_cvtepi8_epi16(_mm256_castsi256_si128(a_)));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 cvt_i16x16_u16x8(i16x16_arg a_)
	{
		return _mm256_castsi256_si128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 cvt_i32x8_u16x8(i32x8_arg a_)
	{
		return _mm256_cvtepi32_epi16(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 cvt_i64x4_u16x8(i64x4_arg a_)
	{
		return _mm256_cvtepi64_epi16(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 cvt_i8x64_u16x8(i8x64_arg a_)
	{
		return _mm512_castsi512_si128(_mm512_cvtepi8_epi16(_mm512_castsi512_si256(a_)));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 cvt_i16x32_u16x8(i16x32_arg a_)
	{
		return _mm512_castsi512_si128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 cvt_i32x16_u16x8(i32x16_arg a_)
	{
		return _mm512_castsi512_si128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 cvt_i64x8_u16x8(i64x8_arg a_)
	{
		return _mm512_cvtepi64_epi16(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 cvt_u8x16_u16x8(u8x16_arg a_)
	{
		return _mm_cvtepi8_epi16(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 cvt_u16x8_u16x8(u16x8_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 cvt_u32x4_u16x8(u32x4_arg a_)
	{
		return _mm_cvtepi32_epi16(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 cvt_u64x2_u16x8(u64x2_arg a_)
	{
		return _mm_cvtepi64_epi16(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 cvt_u8x32_u16x8(u8x32_arg a_)
	{
		return _mm256_castsi256_si128(_mm256_cvtepi8_epi16(_mm256_castsi256_si128(a_)));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 cvt_u16x16_u16x8(u16x16_arg a_)
	{
		return _mm256_castsi256_si128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 cvt_u32x8_u16x8(u32x8_arg a_)
	{
		return _mm256_cvtepi32_epi16(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 cvt_u64x4_u16x8(u64x4_arg a_)
	{
		return _mm256_cvtepi64_epi16(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 cvt_u8x64_u16x8(u8x64_arg a_)
	{
		return _mm512_castsi512_si128(_mm512_cvtepi8_epi16(_mm512_castsi512_si256(a_)));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 cvt_u16x32_u16x8(u16x32_arg a_)
	{
		return _mm512_castsi512_si128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 cvt_u32x16_u16x8(u32x16_arg a_)
	{
		return _mm512_castsi512_si128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 cvt_u64x8_u16x8(u64x8_arg a_)
	{
		return _mm512_cvtepi64_epi16(a_);
	}
#pragma endregion

#pragma region COMPARISONS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 cmpeq_u16x8(EmuSIMD::u16x8_arg lhs_, EmuSIMD::u16x8_arg rhs_)
	{
		return _mm_cmpeq_epi16(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 cmpneq_u16x8(EmuSIMD::u16x8_arg lhs_, EmuSIMD::u16x8_arg rhs_)
	{
		constexpr std::uint16_t mask = static_cast<std::uint16_t>(0xFFFF);
		return _mm_xor_si128(set1_i16x8(mask), _mm_cmpeq_epi16(lhs_, rhs_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 cmpgt_u16x8(EmuSIMD::u16x8_arg lhs_, EmuSIMD::u16x8_arg rhs_)
	{
		constexpr std::uint16_t mask = static_cast<std::uint16_t>(0xFFFF);
		return _mm_andnot_si128(_mm_cmpeq_epi16(_mm_min_epu16(lhs_, rhs_), lhs_), set1_u16x8(mask));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 cmplt_u16x8(EmuSIMD::u16x8_arg lhs_, EmuSIMD::u16x8_arg rhs_)
	{
		constexpr std::uint16_t mask = static_cast<std::uint16_t>(0xFFFF);
		return _mm_andnot_si128(_mm_cmpeq_epi16(_mm_max_epu16(lhs_, rhs_), lhs_), set1_u16x8(mask));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 cmpge_u16x8(EmuSIMD::u16x8_arg lhs_, EmuSIMD::u16x8_arg rhs_)
	{
		return _mm_cmpeq_epi16(_mm_max_epu16(lhs_, rhs_), lhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 cmple_u16x8(EmuSIMD::u16x8_arg lhs_, EmuSIMD::u16x8_arg rhs_)
	{
		return _mm_cmpeq_epi16(_mm_min_epu16(lhs_, rhs_), lhs_);
	}
#pragma endregion

#pragma region BASIC_ARITHMETIC
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 mul_all_u16x8(EmuSIMD::u16x8_arg lhs_, EmuSIMD::u16x8_arg rhs_)
	{
		return _mm_mullo_epi16(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 negate_u16x8(EmuSIMD::u16x8_arg to_negate_)
	{
		return _mm_sub_epi16(_mm_setzero_si128(), to_negate_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 add_u16x8(EmuSIMD::u16x8_arg lhs_, EmuSIMD::u16x8_arg rhs_)
	{
		return _mm_add_epi16(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 sub_u16x8(EmuSIMD::u16x8_arg lhs_, EmuSIMD::u16x8_arg rhs_)
	{
		return _mm_sub_epi16(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 mul_u16x8(EmuSIMD::u16x8_arg lhs_, EmuSIMD::u16x8_arg rhs_)
	{
		return _mm_mullo_epi16(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 div_u16x8(EmuSIMD::u16x8_arg lhs_, EmuSIMD::u16x8_arg rhs_)
	{
		return _mm_div_epu16(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 addsub_u16x8(EmuSIMD::u16x8_arg lhs_, EmuSIMD::u16x8_arg rhs_)
	{
		constexpr std::uint16_t bytes_mask = static_cast<std::uint16_t>(0xFFFF);
		const EmuSIMD::u16x8 mask = _mm_set_epi16(bytes_mask, 0, bytes_mask, 0, bytes_mask, 0, bytes_mask, 0);
		EmuSIMD::u16x8 out = _mm_add_epi16(lhs_, _mm_and_si128(mask, rhs_));
		return _mm_sub_epi16(lhs_, _mm_andnot_si128(mask, rhs_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 subadd_u16x8(EmuSIMD::u16x8_arg lhs_, EmuSIMD::u16x8_arg rhs_)
	{
		constexpr std::uint16_t bytes_mask = static_cast<std::uint16_t>(0xFFFF);
		const EmuSIMD::u16x8 mask = _mm_set_epi16(bytes_mask, 0, bytes_mask, 0, bytes_mask, 0, bytes_mask, 0);
		EmuSIMD::u16x8 out = _mm_sub_epi16(lhs_, _mm_and_si128(mask, rhs_));
		return _mm_add_epi16(lhs_, _mm_andnot_si128(mask, rhs_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 fmadd_u16x8(EmuSIMD::u16x8_arg a_, EmuSIMD::u16x8_arg b_, EmuSIMD::u16x8_arg c_)
	{
		return _mm_add_epi16(mul_all_u16x8(a_, b_), c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 fmsub_u16x8(EmuSIMD::u16x8_arg a_, EmuSIMD::u16x8_arg b_, EmuSIMD::u16x8_arg c_)
	{
		return _mm_sub_epi16(mul_all_u16x8(a_, b_), c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 fnmadd_u16x8(EmuSIMD::u16x8_arg a_, EmuSIMD::u16x8_arg b_, EmuSIMD::u16x8_arg c_)
	{
		return _mm_add_epi16(mul_all_u16x8(negate_u16x8(a_), b_), c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 fnmsub_u16x8(EmuSIMD::u16x8_arg a_, EmuSIMD::u16x8_arg b_, EmuSIMD::u16x8_arg c_)
	{
		return _mm_sub_epi16(mul_all_u16x8(negate_u16x8(a_), b_), c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 fmaddsub_u16x8(EmuSIMD::u16x8_arg a_, EmuSIMD::u16x8_arg b_, EmuSIMD::u16x8_arg c_)
	{
		return addsub_u16x8(mul_all_u16x8(a_, b_), c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 fmsubadd_u16x8(EmuSIMD::u16x8_arg a_, EmuSIMD::u16x8_arg b_, EmuSIMD::u16x8_arg c_)
	{
		return subadd_u16x8(mul_all_u16x8(a_, b_), c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 floor_u16x8(EmuSIMD::u16x8_arg to_floor_)
	{
		return to_floor_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 ceil_u16x8(EmuSIMD::u16x8_arg to_ceil_)
	{
		return to_ceil_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 trunc_u16x8(EmuSIMD::u16x8_arg to_trunc_)
	{
		return to_trunc_;
	}

	template<int RoundingFlag_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 round_u16x8(EmuSIMD::u16x8_arg to_round_)
	{
		return to_round_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 mod_u16x8(EmuSIMD::u16x8_arg lhs_, EmuSIMD::u16x8_arg rhs_)
	{
		return _mm_rem_epu16(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 abs_u16x8(EmuSIMD::u16x8_arg in_)
	{
		return in_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 sqrt_u16x8(EmuSIMD::u16x8_arg in_)
	{
		constexpr std::size_t num_elements = 8;
		constexpr std::size_t elements_per_register = 4;
		std::uint16_t data[num_elements];
		float results[num_elements];

		store_u16x8(data, in_);
		for (std::size_t i = 0; i < num_elements; i += elements_per_register)
		{
			_mm_store_ps(results + i, _mm_sqrt_ps(_mm_set_ps(data[i + 3], data[i + 2], data[i + 1], data[i])));
		}

		return set_u16x8
		(
			static_cast<std::uint16_t>(results[7]),
			static_cast<std::uint16_t>(results[6]),
			static_cast<std::uint16_t>(results[5]),
			static_cast<std::uint16_t>(results[4]),
			static_cast<std::uint16_t>(results[3]),
			static_cast<std::uint16_t>(results[2]),
			static_cast<std::uint16_t>(results[1]),
			static_cast<std::uint16_t>(results[0])
		);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 rsqrt_u16x8(EmuSIMD::u16x8_arg in_)
	{
		constexpr std::size_t num_elements = 8;
		constexpr std::size_t elements_per_register = 4;
		std::uint16_t data[num_elements];
		float results[num_elements];

		store_u16x8(data, in_);
		for (std::size_t i = 0; i < num_elements; i += elements_per_register)
		{
			_mm_store_ps(results + i, _mm_rsqrt_ps(_mm_set_ps(data[i + 3], data[i + 2], data[i + 1], data[i])));
		}

		return set_u16x8
		(
			static_cast<std::uint16_t>(results[7]),
			static_cast<std::uint16_t>(results[6]),
			static_cast<std::uint16_t>(results[5]),
			static_cast<std::uint16_t>(results[4]),
			static_cast<std::uint16_t>(results[3]),
			static_cast<std::uint16_t>(results[2]),
			static_cast<std::uint16_t>(results[1]),
			static_cast<std::uint16_t>(results[0])
		);
	}
#pragma endregion

#pragma region NEAR_COMPARISONS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 cmpnear_u16x8(EmuSIMD::u16x8_arg lhs_, EmuSIMD::u16x8_arg rhs_)
	{
		return cmpeq_u16x8(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 cmpnear_u16x8(EmuSIMD::u16x8_arg lhs_, EmuSIMD::u16x8_arg rhs_, EmuSIMD::u16x8_arg epsilon)
	{
		return cmple_u16x8(sub_u16x8(lhs_, rhs_), epsilon);
	}
#pragma endregion
}

#endif
