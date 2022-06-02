#ifndef EMU_SIMD_GENERIC_FUNCS_I16X16_H_INC_
#define EMU_SIMD_GENERIC_FUNCS_I16X16_H_INC_ 1

#include "_common_generic_func_helpers.h"

namespace EmuSIMD::Funcs
{
#pragma region SETTERS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 set_i16x16
	(
		std::int16_t e0, std::int16_t e1, std::int16_t e2, std::int16_t e3, std::int16_t e4, std::int16_t e5, std::int16_t e6, std::int16_t e7,
		std::int16_t e8, std::int16_t e9, std::int16_t e10, std::int16_t e11, std::int16_t e12, std::int16_t e13, std::int16_t e14, std::int16_t e15
	)
	{
		return _mm256_set_epi16(e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 setr_i16x16
	(
		std::int16_t e0, std::int16_t e1, std::int16_t e2, std::int16_t e3, std::int16_t e4, std::int16_t e5, std::int16_t e6, std::int16_t e7,
		std::int16_t e8, std::int16_t e9, std::int16_t e10, std::int16_t e11, std::int16_t e12, std::int16_t e13, std::int16_t e14, std::int16_t e15
	)
	{
		return _mm256_setr_epi16(e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 set1_i16x16(std::int16_t all_)
	{
		return _mm256_set1_epi16(all_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 load_i16x16(const std::int16_t* p_to_load_)
	{
		return _mm256_load_si256(reinterpret_cast<const __m256i*>(p_to_load_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 setzero_i16x16()
	{
		return _mm256_setzero_si256();
	}
#pragma endregion

#pragma region STORES
	EMU_SIMD_COMMON_FUNC_SPEC void store_i16x16(std::int16_t* p_out_, i16x16_arg a_)
	{
		_mm256_store_si256(reinterpret_cast<__m256i*>(p_out_), a_);
	}
#pragma endregion

#pragma region CASTS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cast_f32x4_i16x16(f32x4_arg a_)
	{
		return _mm256_castsi128_si256(_mm_castps_si128(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cast_f32x8_i16x16(f32x8_arg a_)
	{
		return _mm256_castps_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cast_f32x16_i16x16(f32x16_arg a_)
	{
		return _mm512_castsi512_si256(_mm512_castps_si512(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cast_f64x2_i16x16(f64x2_arg a_)
	{
		return _mm256_castsi128_si256(_mm_castpd_si128(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cast_f64x4_i16x16(f64x4_arg a_)
	{
		return _mm256_castpd_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cast_f64x8_i16x16(f64x8_arg a_)
	{
		return _mm512_castsi512_si256(_mm512_castpd_si512(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cast_i8x16_i16x16(i8x16_arg a_)
	{
		return _mm256_castsi128_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cast_i16x8_i16x16(i16x8_arg a_)
	{
		return _mm256_castsi128_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cast_i32x4_i16x16(i32x4_arg a_)
	{
		return _mm256_castsi128_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cast_i64x2_i16x16(i64x2_arg a_)
	{
		return _mm256_castsi128_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cast_i8x32_i16x16(i8x32_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cast_i16x16_i16x16(i16x16_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cast_i32x8_i16x16(i32x8_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cast_i64x4_i16x16(i64x4_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cast_i8x64_i16x16(i8x64_arg a_)
	{
		return _mm512_castsi512_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cast_i16x32_i16x16(i16x32_arg a_)
	{
		return _mm512_castsi512_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cast_i32x16_i16x16(i32x16_arg a_)
	{
		return _mm512_castsi512_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cast_i64x8_i16x16(i64x8_arg a_)
	{
		return _mm512_castsi512_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cast_u8x16_i16x16(u8x16_arg a_)
	{
		return _mm256_castsi128_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cast_u16x8_i16x16(u16x8_arg a_)
	{
		return _mm256_castsi128_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cast_u32x4_i16x16(u32x4_arg a_)
	{
		return _mm256_castsi128_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cast_u64x2_i16x16(u64x2_arg a_)
	{
		return _mm256_castsi128_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cast_u8x32_i16x16(u8x32_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cast_u16x16_i16x16(u16x16_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cast_u32x8_i16x16(u32x8_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cast_u64x4_i16x16(u64x4_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cast_u8x64_i16x16(u8x64_arg a_)
	{
		return _mm512_castsi512_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cast_u16x32_i16x16(u16x32_arg a_)
	{
		return _mm512_castsi512_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cast_u32x16_i16x16(u32x16_arg a_)
	{
		return _mm512_castsi512_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cast_u64x8_i16x16(u64x8_arg a_)
	{
		return _mm512_castsi512_si256(a_);
	}
#pragma endregion

#pragma region CONVERSIONS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cvt_f32x4_i16x16(f32x4_arg a_)
	{
		return _mm256_castsi128_si256(_mm_cvtepi32_epi16(_mm_cvtps_epi32(a_)));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cvt_f32x8_i16x16(f32x8_arg a_)
	{
		return _mm256_castsi128_si256(_mm256_cvtepi32_epi16(_mm256_cvtps_epi32(a_)));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cvt_f32x16_i16x16(f32x16_arg a_)
	{
		return _mm512_cvtepi32_epi16(_mm512_cvtps_epi32(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cvt_f64x2_i16x16(f64x2_arg a_)
	{
		return _mm256_castsi128_si256(_mm_cvtepi64_epi16(_mm_cvtpd_epi64(a_)));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cvt_f64x4_i16x16(f64x4_arg a_)
	{
		return _mm256_castsi128_si256(_mm256_cvtepi64_epi16(_mm256_cvtpd_epi64(a_)));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cvt_f64x8_i16x16(f64x8_arg a_)
	{
		return _mm256_castsi128_si256(_mm512_cvtepi64_epi16(_mm512_cvtpd_epi64(a_)));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cvt_i8x16_i16x16(i8x16_arg a_)
	{
		return _mm256_cvtepi8_epi16(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cvt_i16x8_i16x16(i16x8_arg a_)
	{
		return _mm256_castsi128_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cvt_i32x4_i16x16(i32x4_arg a_)
	{
		return _mm256_castsi128_si256(_mm_cvtepi32_epi16(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cvt_i64x2_i16x16(i64x2_arg a_)
	{
		return _mm256_castsi128_si256(_mm_cvtepi64_epi16(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cvt_i8x32_i16x16(i8x32_arg a_)
	{
		return _mm256_cvtepi8_epi16(_mm256_castsi256_si128(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cvt_i16x16_i16x16(i16x16_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cvt_i32x8_i16x16(i32x8_arg a_)
	{
		return _mm256_castsi128_si256(_mm256_cvtepi32_epi16(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cvt_i64x4_i16x16(i64x4_arg a_)
	{
		return _mm256_castsi128_si256(_mm256_cvtepi64_epi16(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cvt_i8x64_i16x16(i8x64_arg a_)
	{
		return _mm512_castsi512_si256(_mm512_cvtepi8_epi16(_mm512_castsi512_si256(a_)));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cvt_i16x32_i16x16(i16x32_arg a_)
	{
		return _mm512_castsi512_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cvt_i32x16_i16x16(i32x16_arg a_)
	{
		return _mm512_cvtepi32_epi16(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cvt_i64x8_i16x16(i64x8_arg a_)
	{
		return _mm256_castsi128_si256(_mm512_cvtepi64_epi16(a_));
	}






	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cvt_u8x16_i16x16(u8x16_arg a_)
	{
		return _mm256_castsi128_si256(_mm_cvtepu8_epi16(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cvt_u16x8_i16x16(u16x8_arg a_)
	{
		return _mm256_castsi128_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cvt_u32x4_i16x16(u32x4_arg a_)
	{
		return _mm256_castsi128_si256(_mm_cvtepi32_epi16(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cvt_u64x2_i16x16(u64x2_arg a_)
	{
		return _mm256_castsi128_si256(_mm_cvtepi64_epi16(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cvt_u8x32_i16x16(u8x32_arg a_)
	{
		return _mm256_cvtepu8_epi16(_mm256_castsi256_si128(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cvt_u16x16_i16x16(u16x16_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cvt_u32x8_i16x16(u32x8_arg a_)
	{
		return _mm256_castsi128_si256(_mm256_cvtepi32_epi16(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cvt_u64x4_i16x16(u64x4_arg a_)
	{
		return _mm256_castsi128_si256(_mm256_cvtepi64_epi16(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cvt_u8x64_i16x16(u8x64_arg a_)
	{
		return _mm512_castsi512_si256(_mm512_cvtepu8_epi16(_mm512_castsi512_si256(a_)));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cvt_u16x32_i16x16(u16x32_arg a_)
	{
		return _mm512_castsi512_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cvt_u32x16_i16x16(u32x16_arg a_)
	{
		return _mm512_cvtepi32_epi16(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cvt_u64x8_i16x16(u64x8_arg a_)
	{
		return _mm256_castsi128_si256(_mm512_cvtepi64_epi16(a_));
	}
#pragma endregion

#pragma region BASIC_ARITHMETIC
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 mul_all_i16x16(EmuSIMD::i16x16_arg lhs_, EmuSIMD::i16x16_arg rhs_)
	{
		return _mm256_mullo_epi16(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 negate_i16x16(EmuSIMD::i16x16_arg to_negate_)
	{
		return _mm256_sub_epi16(_mm256_setzero_si256(), to_negate_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 add_i16x16(EmuSIMD::i16x16_arg lhs_, EmuSIMD::i16x16_arg rhs_)
	{
		return _mm256_add_epi16(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 sub_i16x16(EmuSIMD::i16x16_arg lhs_, EmuSIMD::i16x16_arg rhs_)
	{
		return _mm256_sub_epi16(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 mul_i16x16(EmuSIMD::i16x16_arg lhs_, EmuSIMD::i16x16_arg rhs_)
	{
		return _mm256_mul_epi32(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 div_i16x16(EmuSIMD::i16x16_arg lhs_, EmuSIMD::i16x16_arg rhs_)
	{
		return _mm256_div_epi16(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 addsub_i16x16(EmuSIMD::i16x16_arg lhs_, EmuSIMD::i16x16_arg rhs_)
	{
		constexpr std::int16_t bytes_mask = static_cast<std::int16_t>(0xFFFF);
		const EmuSIMD::i16x16 mask = _mm256_set_epi16(bytes_mask, 0, bytes_mask, 0, bytes_mask, 0, bytes_mask, 0, bytes_mask, 0, bytes_mask, 0, bytes_mask, 0, bytes_mask, 0);
		EmuSIMD::i16x16 out = _mm256_add_epi16(lhs_, _mm256_and_si256(mask, rhs_));
		return _mm256_sub_epi16(lhs_, _mm256_andnot_si256(mask, rhs_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 subadd_i16x16(EmuSIMD::i16x16_arg lhs_, EmuSIMD::i16x16_arg rhs_)
	{
		constexpr std::int16_t bytes_mask = static_cast<std::int16_t>(0xFFFF);
		const EmuSIMD::i16x16 mask = _mm256_set_epi16(bytes_mask, 0, bytes_mask, 0, bytes_mask, 0, bytes_mask, 0, bytes_mask, 0, bytes_mask, 0, bytes_mask, 0, bytes_mask, 0);
		EmuSIMD::i16x16 out = _mm256_sub_epi16(lhs_, _mm256_and_si256(mask, rhs_));
		return _mm256_add_epi16(lhs_, _mm256_andnot_si256(mask, rhs_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 fmadd_i16x16(EmuSIMD::i16x16_arg a_, EmuSIMD::i16x16_arg b_, EmuSIMD::i16x16_arg c_)
	{
		return _mm256_add_epi16(mul_all_i16x16(a_, b_), c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 fmsub_i16x16(EmuSIMD::i16x16_arg a_, EmuSIMD::i16x16_arg b_, EmuSIMD::i16x16_arg c_)
	{
		return _mm256_sub_epi16(mul_all_i16x16(a_, b_), c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 fnmadd_i16x16(EmuSIMD::i16x16_arg a_, EmuSIMD::i16x16_arg b_, EmuSIMD::i16x16_arg c_)
	{
		return _mm256_add_epi16(mul_all_i16x16(negate_i16x16(a_), b_), c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 fnmsub_i16x16(EmuSIMD::i16x16_arg a_, EmuSIMD::i16x16_arg b_, EmuSIMD::i16x16_arg c_)
	{
		return _mm256_sub_epi16(mul_all_i16x16(negate_i16x16(a_), b_), c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 fmaddsub_i16x16(EmuSIMD::i16x16_arg a_, EmuSIMD::i16x16_arg b_, EmuSIMD::i16x16_arg c_)
	{
		return addsub_i16x16(mul_all_i16x16(a_, b_), c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 fmsubadd_i16x16(EmuSIMD::i16x16_arg a_, EmuSIMD::i16x16_arg b_, EmuSIMD::i16x16_arg c_)
	{
		return subadd_i16x16(mul_all_i16x16(a_, b_), c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 floor_i16x16(EmuSIMD::i16x16_arg to_floor_)
	{
		return to_floor_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 ceil_i16x16(EmuSIMD::i16x16_arg to_ceil_)
	{
		return to_ceil_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 trunc_i16x16(EmuSIMD::i16x16_arg to_trunc_)
	{
		return to_trunc_;
	}

	template<int RoundingFlag_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 round_i16x16(EmuSIMD::i16x16_arg to_round_)
	{
		return to_round_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 mod_i16x16(EmuSIMD::i16x16_arg lhs_, EmuSIMD::i16x16_arg rhs_)
	{
		return _mm256_rem_epi16(lhs_, rhs_);
	}
#pragma endregion
}

#endif
