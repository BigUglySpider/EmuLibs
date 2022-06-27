#ifndef EMU_SIMD_GENERIC_FUNCS_U16X16_H_INC_
#define EMU_SIMD_GENERIC_FUNCS_U16X16_H_INC_ 1

#include "_common_generic_func_helpers.h"

namespace EmuSIMD::Funcs
{
#pragma region SETTERS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x16 set_u16x16
	(
		std::uint16_t e0, std::uint16_t e1, std::uint16_t e2, std::uint16_t e3, std::uint16_t e4, std::uint16_t e5, std::uint16_t e6, std::uint16_t e7,
		std::uint16_t e8, std::uint16_t e9, std::uint16_t e10, std::uint16_t e11, std::uint16_t e12, std::uint16_t e13, std::uint16_t e14, std::uint16_t e15
	)
	{
		return _mm256_set_epi16(e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x16 setr_u16x16
	(
		std::uint16_t e0, std::uint16_t e1, std::uint16_t e2, std::uint16_t e3, std::uint16_t e4, std::uint16_t e5, std::uint16_t e6, std::uint16_t e7,
		std::uint16_t e8, std::uint16_t e9, std::uint16_t e10, std::uint16_t e11, std::uint16_t e12, std::uint16_t e13, std::uint16_t e14, std::uint16_t e15
	)
	{
		return _mm256_setr_epi16(e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x16 set1_u16x16(std::uint16_t all_)
	{
		return _mm256_set1_epi16(all_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x16 load_u16x16(const std::uint16_t* p_to_load_)
	{
		return _mm256_load_si256(reinterpret_cast<const __m256i*>(p_to_load_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x16 setzero_u16x16()
	{
		return _mm256_setzero_si256();
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x16 setmasked_u16x16(std::uint16_t bit_mask_)
	{
		constexpr std::uint16_t element_mask = static_cast<std::uint16_t>(0xFFFF);
		return _mm256_set_epi16
		(
			(bit_mask_ & 0x0001) * element_mask,
			((bit_mask_ & 0x0002) >> 1) * element_mask,
			((bit_mask_ & 0x0004) >> 2) * element_mask,
			((bit_mask_ & 0x0008) >> 3) * element_mask,
			((bit_mask_ & 0x0010) >> 4) * element_mask,
			((bit_mask_ & 0x0020) >> 5) * element_mask,
			((bit_mask_ & 0x0040) >> 6) * element_mask,
			((bit_mask_ & 0x0080) >> 7) * element_mask,
			((bit_mask_ & 0x0100) >> 8) * element_mask,
			((bit_mask_ & 0x0200) >> 9) * element_mask,
			((bit_mask_ & 0x0400) >> 10) * element_mask,
			((bit_mask_ & 0x0800) >> 11) * element_mask,
			((bit_mask_ & 0x1000) >> 12) * element_mask,
			((bit_mask_ & 0x2000) >> 13) * element_mask,
			((bit_mask_ & 0x4000) >> 14) * element_mask,
			((bit_mask_ & 0x8000) >> 15) * element_mask
		);
	}
#pragma endregion

#pragma region STORES
	EMU_SIMD_COMMON_FUNC_SPEC void store_u16x16(std::uint16_t* p_out_, u16x16_arg a_)
	{
		_mm256_store_si256(reinterpret_cast<__m256i*>(p_out_), a_);
	}
#pragma endregion

#pragma region CASTS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x16 cast_f32x4_u16x16(f32x4_arg a_)
	{
		return _mm256_castsi128_si256(_mm_castps_si128(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x16 cast_f32x8_u16x16(f32x8_arg a_)
	{
		return _mm256_castps_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x16 cast_f32x16_u16x16(f32x16_arg a_)
	{
		return _mm512_castsi512_si256(_mm512_castps_si512(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x16 cast_f64x2_u16x16(f64x2_arg a_)
	{
		return _mm256_castsi128_si256(_mm_castpd_si128(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x16 cast_f64x4_u16x16(f64x4_arg a_)
	{
		return _mm256_castpd_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x16 cast_f64x8_u16x16(f64x8_arg a_)
	{
		return _mm512_castsi512_si256(_mm512_castpd_si512(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x16 cast_i8x16_u16x16(i8x16_arg a_)
	{
		return _mm256_castsi128_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x16 cast_i16x8_u16x16(i16x8_arg a_)
	{
		return _mm256_castsi128_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x16 cast_i32x4_u16x16(i32x4_arg a_)
	{
		return _mm256_castsi128_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x16 cast_i64x2_u16x16(i64x2_arg a_)
	{
		return _mm256_castsi128_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x16 cast_i8x32_u16x16(i8x32_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x16 cast_i16x16_u16x16(i16x16_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x16 cast_i32x8_u16x16(i32x8_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x16 cast_i64x4_u16x16(i64x4_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x16 cast_i8x64_u16x16(i8x64_arg a_)
	{
		return _mm512_castsi512_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x16 cast_i16x32_u16x16(i16x32_arg a_)
	{
		return _mm512_castsi512_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x16 cast_i32x16_u16x16(i32x16_arg a_)
	{
		return _mm512_castsi512_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x16 cast_i64x8_u16x16(i64x8_arg a_)
	{
		return _mm512_castsi512_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x16 cast_u8x16_u16x16(u8x16_arg a_)
	{
		return _mm256_castsi128_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x16 cast_u16x8_u16x16(u16x8_arg a_)
	{
		return _mm256_castsi128_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x16 cast_u32x4_u16x16(u32x4_arg a_)
	{
		return _mm256_castsi128_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x16 cast_u64x2_u16x16(u64x2_arg a_)
	{
		return _mm256_castsi128_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x16 cast_u8x32_u16x16(u8x32_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x16 cast_u16x16_u16x16(u16x16_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x16 cast_u32x8_u16x16(u32x8_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x16 cast_u64x4_u16x16(u64x4_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x16 cast_u8x64_u16x16(u8x64_arg a_)
	{
		return _mm512_castsi512_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x16 cast_u16x32_u16x16(u16x32_arg a_)
	{
		return _mm512_castsi512_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x16 cast_u32x16_u16x16(u32x16_arg a_)
	{
		return _mm512_castsi512_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x16 cast_u64x8_u16x16(u64x8_arg a_)
	{
		return _mm512_castsi512_si256(a_);
	}
#pragma endregion

#pragma region CONVERSIONS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x16 cvt_f32x4_u16x16(f32x4_arg a_)
	{
		return _mm256_castsi128_si256(_mm_cvtepi32_epi16(_mm_cvtps_epi32(a_)));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x16 cvt_f32x8_u16x16(f32x8_arg a_)
	{
		return _mm256_castsi128_si256(_mm256_cvtepi32_epi16(_mm256_cvtps_epi32(a_)));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x16 cvt_f32x16_u16x16(f32x16_arg a_)
	{
		return _mm512_cvtepi32_epi16(_mm512_cvtps_epi32(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x16 cvt_f64x2_u16x16(f64x2_arg a_)
	{
		return _mm256_castsi128_si256(_mm_cvtepi64_epi16(_mm_cvtpd_epi64(a_)));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x16 cvt_f64x4_u16x16(f64x4_arg a_)
	{
		return _mm256_castsi128_si256(_mm256_cvtepi64_epi16(_mm256_cvtpd_epi64(a_)));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x16 cvt_f64x8_u16x16(f64x8_arg a_)
	{
		return _mm256_castsi128_si256(_mm512_cvtepi64_epi16(_mm512_cvtpd_epi64(a_)));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x16 cvt_i8x16_u16x16(i8x16_arg a_)
	{
		return _mm256_cvtepi8_epi16(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x16 cvt_i16x8_u16x16(i16x8_arg a_)
	{
		return _mm256_castsi128_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x16 cvt_i32x4_u16x16(i32x4_arg a_)
	{
		return _mm256_castsi128_si256(_mm_cvtepi32_epi16(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x16 cvt_i64x2_u16x16(i64x2_arg a_)
	{
		return _mm256_castsi128_si256(_mm_cvtepi64_epi16(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x16 cvt_i8x32_u16x16(i8x32_arg a_)
	{
		return _mm256_cvtepi8_epi16(_mm256_castsi256_si128(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x16 cvt_i16x16_u16x16(i16x16_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x16 cvt_i32x8_u16x16(i32x8_arg a_)
	{
		return _mm256_castsi128_si256(_mm256_cvtepi32_epi16(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x16 cvt_i64x4_u16x16(i64x4_arg a_)
	{
		return _mm256_castsi128_si256(_mm256_cvtepi64_epi16(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x16 cvt_i8x64_u16x16(i8x64_arg a_)
	{
		return _mm512_castsi512_si256(_mm512_cvtepi8_epi16(_mm512_castsi512_si256(a_)));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x16 cvt_i16x32_u16x16(i16x32_arg a_)
	{
		return _mm512_castsi512_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x16 cvt_i32x16_u16x16(i32x16_arg a_)
	{
		return _mm512_cvtepi32_epi16(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x16 cvt_i64x8_u16x16(i64x8_arg a_)
	{
		return _mm256_castsi128_si256(_mm512_cvtepi64_epi16(a_));
	}






	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x16 cvt_u8x16_u16x16(u8x16_arg a_)
	{
		return _mm256_castsi128_si256(_mm_cvtepi8_epi16(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x16 cvt_u16x8_u16x16(u16x8_arg a_)
	{
		return _mm256_castsi128_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x16 cvt_u32x4_u16x16(u32x4_arg a_)
	{
		return _mm256_castsi128_si256(_mm_cvtepi32_epi16(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x16 cvt_u64x2_u16x16(u64x2_arg a_)
	{
		return _mm256_castsi128_si256(_mm_cvtepi64_epi16(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x16 cvt_u8x32_u16x16(u8x32_arg a_)
	{
		return _mm256_cvtepi8_epi16(_mm256_castsi256_si128(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x16 cvt_u16x16_u16x16(u16x16_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x16 cvt_u32x8_u16x16(u32x8_arg a_)
	{
		return _mm256_castsi128_si256(_mm256_cvtepi32_epi16(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x16 cvt_u64x4_u16x16(u64x4_arg a_)
	{
		return _mm256_castsi128_si256(_mm256_cvtepi64_epi16(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x16 cvt_u8x64_u16x16(u8x64_arg a_)
	{
		return _mm512_castsi512_si256(_mm512_cvtepi8_epi16(_mm512_castsi512_si256(a_)));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x16 cvt_u16x32_u16x16(u16x32_arg a_)
	{
		return _mm512_castsi512_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x16 cvt_u32x16_u16x16(u32x16_arg a_)
	{
		return _mm512_cvtepi32_epi16(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x16 cvt_u64x8_u16x16(u64x8_arg a_)
	{
		return _mm256_castsi128_si256(_mm512_cvtepi64_epi16(a_));
	}
#pragma endregion

#pragma region COMPARISONS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x16 cmpeq_u16x16(EmuSIMD::u16x16_arg lhs_, EmuSIMD::u16x16_arg rhs_)
	{
		return _mm256_cmpeq_epi16(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x16 cmpneq_u16x16(EmuSIMD::u16x16_arg lhs_, EmuSIMD::u16x16_arg rhs_)
	{
		constexpr std::uint16_t mask = static_cast<std::uint16_t>(0xFFFF);
		return _mm256_xor_si256(set1_i16x16(mask), _mm256_cmpeq_epi16(lhs_, rhs_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x16 cmpgt_u16x16(EmuSIMD::u16x16_arg lhs_, EmuSIMD::u16x16_arg rhs_)
	{
		constexpr std::uint16_t mask = static_cast<std::uint16_t>(0xFFFF);
		return _mm256_andnot_si256(_mm256_cmpeq_epi16(_mm256_min_epu16(lhs_, rhs_), lhs_), set1_u16x16(mask));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x16 cmplt_u16x16(EmuSIMD::u16x16_arg lhs_, EmuSIMD::u16x16_arg rhs_)
	{
		constexpr std::uint16_t mask = static_cast<std::uint16_t>(0xFFFF);
		return _mm256_andnot_si256(_mm256_cmpeq_epi16(_mm256_max_epu16(lhs_, rhs_), lhs_), set1_u16x16(mask));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x16 cmpge_u16x16(EmuSIMD::u16x16_arg lhs_, EmuSIMD::u16x16_arg rhs_)
	{
		return _mm256_cmpeq_epi16(_mm256_max_epu16(lhs_, rhs_), lhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x16 cmple_u16x16(EmuSIMD::u16x16_arg lhs_, EmuSIMD::u16x16_arg rhs_)
	{
		return _mm256_cmpeq_epi16(_mm256_min_epu16(lhs_, rhs_), lhs_);
	}
#pragma endregion

#pragma region BASIC_ARITHMETIC
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x16 mul_all_u16x16(EmuSIMD::u16x16_arg lhs_, EmuSIMD::u16x16_arg rhs_)
	{
		return _mm256_mullo_epi16(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x16 negate_u16x16(EmuSIMD::u16x16_arg to_negate_)
	{
		return _mm256_sub_epi16(_mm256_setzero_si256(), to_negate_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x16 add_u16x16(EmuSIMD::u16x16_arg lhs_, EmuSIMD::u16x16_arg rhs_)
	{
		return _mm256_add_epi16(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x16 sub_u16x16(EmuSIMD::u16x16_arg lhs_, EmuSIMD::u16x16_arg rhs_)
	{
		return _mm256_sub_epi16(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x16 mul_u16x16(EmuSIMD::u16x16_arg lhs_, EmuSIMD::u16x16_arg rhs_)
	{
		return _mm256_mul_epu32(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x16 div_u16x16(EmuSIMD::u16x16_arg lhs_, EmuSIMD::u16x16_arg rhs_)
	{
		return _mm256_div_epu16(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x16 addsub_u16x16(EmuSIMD::u16x16_arg lhs_, EmuSIMD::u16x16_arg rhs_)
	{
		constexpr std::uint16_t bytes_mask = static_cast<std::uint16_t>(0xFFFF);
		const EmuSIMD::u16x16 mask = _mm256_set_epi16(bytes_mask, 0, bytes_mask, 0, bytes_mask, 0, bytes_mask, 0, bytes_mask, 0, bytes_mask, 0, bytes_mask, 0, bytes_mask, 0);
		EmuSIMD::u16x16 out = _mm256_add_epi16(lhs_, _mm256_and_si256(mask, rhs_));
		return _mm256_sub_epi16(lhs_, _mm256_andnot_si256(mask, rhs_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x16 subadd_u16x16(EmuSIMD::u16x16_arg lhs_, EmuSIMD::u16x16_arg rhs_)
	{
		constexpr std::uint16_t bytes_mask = static_cast<std::uint16_t>(0xFFFF);
		const EmuSIMD::u16x16 mask = _mm256_set_epi16(bytes_mask, 0, bytes_mask, 0, bytes_mask, 0, bytes_mask, 0, bytes_mask, 0, bytes_mask, 0, bytes_mask, 0, bytes_mask, 0);
		EmuSIMD::u16x16 out = _mm256_sub_epi16(lhs_, _mm256_and_si256(mask, rhs_));
		return _mm256_add_epi16(lhs_, _mm256_andnot_si256(mask, rhs_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x16 fmadd_u16x16(EmuSIMD::u16x16_arg a_, EmuSIMD::u16x16_arg b_, EmuSIMD::u16x16_arg c_)
	{
		return _mm256_add_epi16(mul_all_u16x16(a_, b_), c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x16 fmsub_u16x16(EmuSIMD::u16x16_arg a_, EmuSIMD::u16x16_arg b_, EmuSIMD::u16x16_arg c_)
	{
		return _mm256_sub_epi16(mul_all_u16x16(a_, b_), c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x16 fnmadd_u16x16(EmuSIMD::u16x16_arg a_, EmuSIMD::u16x16_arg b_, EmuSIMD::u16x16_arg c_)
	{
		return _mm256_add_epi16(mul_all_u16x16(negate_u16x16(a_), b_), c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x16 fnmsub_u16x16(EmuSIMD::u16x16_arg a_, EmuSIMD::u16x16_arg b_, EmuSIMD::u16x16_arg c_)
	{
		return _mm256_sub_epi16(mul_all_u16x16(negate_u16x16(a_), b_), c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x16 fmaddsub_u16x16(EmuSIMD::u16x16_arg a_, EmuSIMD::u16x16_arg b_, EmuSIMD::u16x16_arg c_)
	{
		return addsub_u16x16(mul_all_u16x16(a_, b_), c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x16 fmsubadd_u16x16(EmuSIMD::u16x16_arg a_, EmuSIMD::u16x16_arg b_, EmuSIMD::u16x16_arg c_)
	{
		return subadd_u16x16(mul_all_u16x16(a_, b_), c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x16 floor_u16x16(EmuSIMD::u16x16_arg to_floor_)
	{
		return to_floor_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x16 ceil_u16x16(EmuSIMD::u16x16_arg to_ceil_)
	{
		return to_ceil_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x16 trunc_u16x16(EmuSIMD::u16x16_arg to_trunc_)
	{
		return to_trunc_;
	}

	template<int RoundingFlag_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x16 round_u16x16(EmuSIMD::u16x16_arg to_round_)
	{
		return to_round_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x16 mod_u16x16(EmuSIMD::u16x16_arg lhs_, EmuSIMD::u16x16_arg rhs_)
	{
		return _mm256_rem_epu16(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x16 abs_u16x16(EmuSIMD::u16x16_arg in_)
	{
		return in_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x16 sqrt_u16x16(EmuSIMD::u16x16_arg in_)
	{
		constexpr std::size_t num_elements = 16;
		constexpr std::size_t elements_per_register = 8;
		std::uint16_t data[num_elements];
		float results[num_elements];

		store_u16x16(data, in_);
		for (std::size_t i = 0; i < num_elements; i += elements_per_register)
		{
			_mm256_store_ps(results + i, _mm256_sqrt_ps(_mm256_set_ps(data[i + 7], data[i + 6], data[i + 5], data[i + 4], data[i + 3], data[i + 2], data[i + 1], data[i])));
		}

		return set_u16x16
		(
			static_cast<std::uint16_t>(results[15]),
			static_cast<std::uint16_t>(results[14]),
			static_cast<std::uint16_t>(results[13]),
			static_cast<std::uint16_t>(results[12]),
			static_cast<std::uint16_t>(results[11]),
			static_cast<std::uint16_t>(results[10]),
			static_cast<std::uint16_t>(results[9]),
			static_cast<std::uint16_t>(results[8]),
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

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x16 rsqrt_u16x16(EmuSIMD::u16x16_arg in_)
	{
		constexpr std::size_t num_elements = 16;
		constexpr std::size_t elements_per_register = 8;
		std::uint16_t data[num_elements];
		float results[num_elements];

		store_u16x16(data, in_);
		for (std::size_t i = 0; i < num_elements; i += elements_per_register)
		{
			_mm256_store_ps(results + i, _mm256_rsqrt_ps(_mm256_set_ps(data[i + 7], data[i + 6], data[i + 5], data[i + 4], data[i + 3], data[i + 2], data[i + 1], data[i])));
		}

		return set_u16x16
		(
			static_cast<std::uint16_t>(results[15]),
			static_cast<std::uint16_t>(results[14]),
			static_cast<std::uint16_t>(results[13]),
			static_cast<std::uint16_t>(results[12]),
			static_cast<std::uint16_t>(results[11]),
			static_cast<std::uint16_t>(results[10]),
			static_cast<std::uint16_t>(results[9]),
			static_cast<std::uint16_t>(results[8]),
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
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x16 cmpnear_u16x16(EmuSIMD::u16x16_arg lhs_, EmuSIMD::u16x16_arg rhs_)
	{
		return cmpeq_u16x16(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x16 cmpnear_u16x16(EmuSIMD::u16x16_arg lhs_, EmuSIMD::u16x16_arg rhs_, EmuSIMD::u16x16_arg epsilon)
	{
		return cmple_u16x16(sub_u16x16(lhs_, rhs_), epsilon);
	}
#pragma endregion
}

#endif
