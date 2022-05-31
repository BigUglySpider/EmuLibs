#ifndef EMU_SIMD_GENERIC_FUNCS_F32X16_H_INC_
#define EMU_SIMD_GENERIC_FUNCS_F32X16_H_INC_ 1

#include "../_common_underlying_simd_template_helper_includes.h"
#include <immintrin.h>

namespace EmuSIMD::Funcs
{
#pragma region SETTERS
	inline EmuSIMD::f32x16 set_f32x16
	(
		float e0, float e1, float e2, float e3, float e4, float e5, float e6, float e7,
		float e8, float e9, float e10, float e11, float e12, float e13, float e14, float e15
	)
	{
		return _mm512_set_ps(e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15);
	}

	inline EmuSIMD::f32x16 setr_f32x16
	(
		float e0, float e1, float e2, float e3, float e4, float e5, float e6, float e7,
		float e8, float e9, float e10, float e11, float e12, float e13, float e14, float e15
	)
	{
		return _mm512_set_ps(e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15);
	}

	inline EmuSIMD::f32x16 set1_f32x16(float all_)
	{
		return _mm512_set1_ps(all_);
	}

	inline EmuSIMD::f32x16 load_f32x16(const float* p_to_load_)
	{
		return _mm512_load_ps(p_to_load_);
	}

	inline EmuSIMD::f32x16 setzero_f32x16()
	{
		return _mm512_setzero_ps();
	}
#pragma endregion

#pragma region STORES
	inline EmuSIMD::f32x16 store_f32x16(float* p_out_, f32x16_arg a_)
	{
		_mm512_store_ps(p_out_, a_);
	}
#pragma endregion

#pragma region SHUFFLES
	template<int ShuffleMask_>
	inline EmuSIMD::f32x16 shuffle_f32x16(f32x16_arg a_, f32x16_arg b_)
	{
		return _mm512_shuffle_ps(a_, b_, ShuffleMask_);
	}

	template<int ShuffleMask_>
	inline EmuSIMD::f32x16 permute_f32x16(f32x16_arg a_)
	{
		return _mm512_permute_ps(a_, ShuffleMask_);
	}
#pragma endregion

#pragma region CASTS
	inline EmuSIMD::f32x16 cast_f32x4_f32x16(f32x4_arg a_)
	{
		return _mm512_castps128_ps512(a_);
	}

	inline EmuSIMD::f32x16 cast_f32x8_f32x16(f32x8_arg a_)
	{
		return _mm512_castps256_ps512(a_);
	}

	inline EmuSIMD::f32x16 cast_f32x16_f32x16(f32x16_arg a_)
	{
		return a_;
	}

	inline EmuSIMD::f32x16 cast_f64x2_f32x16(f64x2_arg a_)
	{
		return _mm512_castpd_ps(_mm512_castpd128_pd512(a_));
	}

	inline EmuSIMD::f32x16 cast_f64x4_f32x16(f64x4_arg a_)
	{
		return _mm512_castpd_ps(_mm512_castpd256_pd512(a_));
	}

	inline EmuSIMD::f32x16 cast_f64x8_f32x16(f64x8_arg a_)
	{
		return _mm512_castpd_ps(a_);
	}

	inline EmuSIMD::f32x16 cast_i8x16_f32x16(i8x16_arg a_)
	{
		return _mm512_castsi512_ps(_mm512_castsi128_si512(a_));
	}

	inline EmuSIMD::f32x16 cast_i16x8_f32x16(i16x8_arg a_)
	{
		return _mm512_castsi512_ps(_mm512_castsi128_si512(a_));
	}

	inline EmuSIMD::f32x16 cast_i32x4_f32x16(i32x4_arg a_)
	{
		return _mm512_castsi512_ps(_mm512_castsi128_si512(a_));
	}

	inline EmuSIMD::f32x16 cast_i64x2_f32x16(i64x2_arg a_)
	{
		return _mm512_castsi512_ps(_mm512_castsi128_si512(a_));
	}

	inline EmuSIMD::f32x16 cast_i8x32_f32x16(i8x32_arg a_)
	{
		return _mm512_castsi512_ps(_mm512_castsi256_si512(a_));
	}

	inline EmuSIMD::f32x16 cast_i16x16_f32x16(i16x16_arg a_)
	{
		return _mm512_castsi512_ps(_mm512_castsi256_si512(a_));
	}

	inline EmuSIMD::f32x16 cast_i32x8_f32x16(i32x8_arg a_)
	{
		return _mm512_castsi512_ps(_mm512_castsi256_si512(a_));
	}

	inline EmuSIMD::f32x16 cast_i64x4_f32x16(i64x4_arg a_)
	{
		return _mm512_castsi512_ps(_mm512_castsi256_si512(a_));
	}

	inline EmuSIMD::f32x16 cast_i8x64_f32x16(i8x64_arg a_)
	{
		return _mm512_castsi512_ps(a_);
	}

	inline EmuSIMD::f32x16 cast_i16x32_f32x16(i16x32_arg a_)
	{
		return _mm512_castsi512_ps(a_);
	}

	inline EmuSIMD::f32x16 cast_i32x16_f32x16(i32x16_arg a_)
	{
		return _mm512_castsi512_ps(a_);
	}

	inline EmuSIMD::f32x16 cast_i64x8_f32x16(i64x8_arg a_)
	{
		return _mm512_castsi512_ps(a_);
	}

	inline EmuSIMD::f32x16 cast_u8x16_f32x16(u8x16_arg a_)
	{
		return _mm512_castsi512_ps(_mm512_castsi128_si512(a_));
	}

	inline EmuSIMD::f32x16 cast_u16x8_f32x16(u16x8_arg a_)
	{
		return _mm512_castsi512_ps(_mm512_castsi128_si512(a_));
	}

	inline EmuSIMD::f32x16 cast_u32x4_f32x16(u32x4_arg a_)
	{
		return _mm512_castsi512_ps(_mm512_castsi128_si512(a_));
	}

	inline EmuSIMD::f32x16 cast_u64x2_f32x16(u64x2_arg a_)
	{
		return _mm512_castsi512_ps(_mm512_castsi128_si512(a_));
	}

	inline EmuSIMD::f32x16 cast_u8x32_f32x16(u8x32_arg a_)
	{
		return _mm512_castsi512_ps(_mm512_castsi256_si512(a_));
	}

	inline EmuSIMD::f32x16 cast_u16x16_f32x16(u16x16_arg a_)
	{
		return _mm512_castsi512_ps(_mm512_castsi256_si512(a_));
	}

	inline EmuSIMD::f32x16 cast_u32x8_f32x16(u32x8_arg a_)
	{
		return _mm512_castsi512_ps(_mm512_castsi256_si512(a_));
	}

	inline EmuSIMD::f32x16 cast_u64x4_f32x16(u64x4_arg a_)
	{
		return _mm512_castsi512_ps(_mm512_castsi256_si512(a_));
	}

	inline EmuSIMD::f32x16 cast_u8x64_f32x16(u8x64_arg a_)
	{
		return _mm512_castsi512_ps(a_);
	}

	inline EmuSIMD::f32x16 cast_u16x32_f32x16(u16x32_arg a_)
	{
		return _mm512_castsi512_ps(a_);
	}

	inline EmuSIMD::f32x16 cast_u32x16_f32x16(u32x16_arg a_)
	{
		return _mm512_castsi512_ps(a_);
	}

	inline EmuSIMD::f32x16 cast_u64x8_f32x16(u64x8_arg a_)
	{
		return _mm512_castsi512_ps(a_);
	}
#pragma endregion

#pragma region CONVERSIONS
	inline EmuSIMD::f32x16 cvt_f32x4_f32x16(f32x4_arg a_)
	{
		return _mm512_castps128_ps512(a_);
	}

	inline EmuSIMD::f32x16 cvt_f32x8_f32x16(f32x8_arg a_)
	{
		return _mm512_castps256_ps512(a_);
	}

	inline EmuSIMD::f32x16 cvt_f32x16_f32x16(f32x16_arg a_)
	{
		return a_;
	}

	inline EmuSIMD::f32x16 cvt_f64x2_f32x16(f64x2_arg a_)
	{
		return _mm512_castps128_ps512(_mm_cvtpd_ps(a_));
	}

	inline EmuSIMD::f32x16 cvt_f64x4_f32x16(f64x4_arg a_)
	{
		return _mm512_castps128_ps512(_mm256_cvtpd_ps(a_));
	}

	inline EmuSIMD::f32x16 cvt_f64x8_f32x16(f64x8_arg a_)
	{
		return _mm512_castps256_ps512(_mm512_cvtpd_ps(a_));
	}

	inline EmuSIMD::f32x16 cvt_i8x16_f32x16(i8x16_arg a_)
	{
		return _mm512_cvtepi32_ps(_mm512_cvtepi8_epi32(a_));
	}

	inline EmuSIMD::f32x16 cvt_i16x8_f32x16(i16x8_arg a_)
	{
		return _mm512_castps256_ps512(_mm256_cvtepi32_ps(_mm256_cvtepi16_epi32(a_)));
	}

	inline EmuSIMD::f32x16 cvt_i32x4_f32x16(i32x4_arg a_)
	{
		return _mm512_castps128_ps512(_mm_cvtepi32_ps(a_));
	}

	inline EmuSIMD::f32x16 cvt_i64x2_f32x16(i64x2_arg a_)
	{
		return _mm512_castps128_ps512(_mm_cvtepi64_ps(a_));
	}

	inline EmuSIMD::f32x16 cvt_i8x32_f32x16(i8x32_arg a_)
	{
		return _mm512_cvtepi32_ps(_mm512_cvtepi8_epi32(_mm256_castsi256_si128(a_)));
	}

	inline EmuSIMD::f32x16 cvt_i16x16_f32x16(i16x16_arg a_)
	{
		return _mm512_cvtepi32_ps(_mm512_cvtepi16_epi32(a_));
	}

	inline EmuSIMD::f32x16 cvt_i32x8_f32x16(i32x8_arg a_)
	{
		return _mm512_castps256_ps512(_mm256_cvtepi32_ps(a_));
	}

	inline EmuSIMD::f32x16 cvt_i64x4_f32x16(i64x4_arg a_)
	{
		return _mm512_castps128_ps512(_mm256_cvtepi64_ps(a_));
	}

	inline EmuSIMD::f32x16 cvt_i8x32_f32x16(i8x64_arg a_)
	{
		return _mm512_cvtepi32_ps(_mm512_cvtepi8_epi32(_mm512_castsi512_si128(a_)));
	}

	inline EmuSIMD::f32x16 cvt_i16x16_f32x16(i16x32_arg a_)
	{
		return _mm512_cvtepi32_ps(_mm512_cvtepi16_epi32(_mm512_castsi512_si256(a_)));
	}

	inline EmuSIMD::f32x16 cvt_i32x8_f32x16(i32x16_arg a_)
	{
		return _mm512_cvtepi32_ps(a_);
	}

	inline EmuSIMD::f32x16 cvt_i64x4_f32x16(i64x8_arg a_)
	{
		return _mm512_castps256_ps512(_mm512_cvtepi64_ps(a_));
	}







	inline EmuSIMD::f32x16 cvt_u8x16_f32x16(u8x16_arg a_)
	{
		return _mm512_cvtepi32_ps(_mm512_cvtepu8_epi32(a_));
	}

	inline EmuSIMD::f32x16 cvt_u16x8_f32x16(u16x8_arg a_)
	{
		return _mm512_castps256_ps512(_mm256_cvtepu32_ps(_mm256_cvtepi16_epi32(a_)));
	}

	inline EmuSIMD::f32x16 cvt_u32x4_f32x16(u32x4_arg a_)
	{
		return _mm512_castps128_ps512(_mm_cvtepu32_ps(a_));
	}

	inline EmuSIMD::f32x16 cvt_u64x2_f32x16(u64x2_arg a_)
	{
		return _mm512_castps128_ps512(_mm_cvtepu64_ps(a_));
	}

	inline EmuSIMD::f32x16 cvt_u8x32_f32x16(u8x32_arg a_)
	{
		return _mm512_cvtepi32_ps(_mm512_cvtepu8_epi32(_mm256_castsi256_si128(a_)));
	}

	inline EmuSIMD::f32x16 cvt_u16x16_f32x16(u16x16_arg a_)
	{
		return _mm512_cvtepi32_ps(_mm512_cvtepu16_epi32(a_));
	}

	inline EmuSIMD::f32x16 cvt_u32x8_f32x16(u32x8_arg a_)
	{
		return _mm512_castps256_ps512(_mm256_cvtepu32_ps(a_));
	}

	inline EmuSIMD::f32x16 cvt_u64x4_f32x16(u64x4_arg a_)
	{
		return _mm512_castps128_ps512(_mm256_cvtepu64_ps(a_));
	}

	inline EmuSIMD::f32x16 cvt_u8x32_f32x16(u8x64_arg a_)
	{
		return _mm512_cvtepi32_ps(_mm512_cvtepu8_epi32(_mm512_castsi512_si128(a_)));
	}

	inline EmuSIMD::f32x16 cvt_u16x16_f32x16(u16x32_arg a_)
	{
		return _mm512_cvtepi32_ps(_mm512_cvtepu16_epi32(_mm512_castsi512_si256(a_)));
	}

	inline EmuSIMD::f32x16 cvt_u32x8_f32x16(u32x16_arg a_)
	{
		return _mm512_cvtepu32_ps(a_);
	}

	inline EmuSIMD::f32x16 cvt_u64x4_f32x16(u64x8_arg a_)
	{
		return _mm512_castps256_ps512(_mm512_cvtepu64_ps(a_));
	}
#pragma endregion

#pragma region BASIC_ARITHMETIC
	inline EmuSIMD::f32x16 mul_all_f32x16(EmuSIMD::f32x16_arg lhs_, EmuSIMD::f32x16_arg rhs_)
	{
		return _mm512_mul_ps(lhs_, rhs_);
	}

	inline EmuSIMD::f32x16 negate_f32x16(EmuSIMD::f32x16_arg to_negate_)
	{
		return _mm512_sub_ps(_mm512_setzero_ps(), to_negate_);
	}

	inline EmuSIMD::f32x16 add_f32x16(EmuSIMD::f32x16_arg lhs_, EmuSIMD::f32x16_arg rhs_)
	{
		return _mm512_add_ps(lhs_, rhs_);
	}

	inline EmuSIMD::f32x16 sub_f32x16(EmuSIMD::f32x16_arg lhs_, EmuSIMD::f32x16_arg rhs_)
	{
		return _mm512_sub_ps(lhs_, rhs_);
	}

	inline EmuSIMD::f32x16 mul_f32x16(EmuSIMD::f32x16_arg lhs_, EmuSIMD::f32x16_arg rhs_)
	{
		return _mm512_mul_ps(lhs_, rhs_);
	}

	inline EmuSIMD::f32x16 div_f32x16(EmuSIMD::f32x16_arg lhs_, EmuSIMD::f32x16_arg rhs_)
	{
		return _mm512_div_ps(lhs_, rhs_);
	}

	inline EmuSIMD::f32x16 addsub_f32x16(EmuSIMD::f32x16_arg lhs_, EmuSIMD::f32x16_arg rhs_)
	{
		return _mm512_fmaddsub_ps(_mm512_set1_ps(1.0f), lhs_, rhs_);
	}

	inline EmuSIMD::f32x16 fmadd_f32x16(EmuSIMD::f32x16_arg a_, EmuSIMD::f32x16_arg b_, EmuSIMD::f32x16_arg c_)
	{
		return _mm512_fmadd_ps(a_, b_, c_);
	}

	inline EmuSIMD::f32x16 fmsub_f32x16(EmuSIMD::f32x16_arg a_, EmuSIMD::f32x16_arg b_, EmuSIMD::f32x16_arg c_)
	{
		return _mm512_fmsub_ps(a_, b_, c_);
	}

	inline EmuSIMD::f32x16 fnmadd_f32x16(EmuSIMD::f32x16_arg a_, EmuSIMD::f32x16_arg b_, EmuSIMD::f32x16_arg c_)
	{
		return _mm512_fnmadd_ps(a_, b_, c_);
	}

	inline EmuSIMD::f32x16 fnmsub_f32x16(EmuSIMD::f32x16_arg a_, EmuSIMD::f32x16_arg b_, EmuSIMD::f32x16_arg c_)
	{
		return _mm512_fnmsub_ps(a_, b_, c_);
	}

	inline EmuSIMD::f32x16 fmaddsub_f32x16(EmuSIMD::f32x16_arg a_, EmuSIMD::f32x16_arg b_, EmuSIMD::f32x16_arg c_)
	{
		return _mm512_fmaddsub_ps(a_, b_, c_);
	}

	inline EmuSIMD::f32x16 fmsubadd_f32x16(EmuSIMD::f32x16_arg a_, EmuSIMD::f32x16_arg b_, EmuSIMD::f32x16_arg c_)
	{
		return _mm512_fmsubadd_ps(a_, b_, c_);
	}

	inline EmuSIMD::f32x16 floor_f32x16(EmuSIMD::f32x16_arg to_floor_)
	{
		return _mm512_floor_ps(to_floor_);
	}

	inline EmuSIMD::f32x16 ceil_f32x16(EmuSIMD::f32x16_arg to_ceil_)
	{
		return _mm512_ceil_ps(to_ceil_);
	}

	inline EmuSIMD::f32x16 trunc_f32x16(EmuSIMD::f32x16_arg to_trunc_)
	{
		return _mm512_trunc_ps(to_trunc_);
	}

	template<int RoundingFlag_>
	inline EmuSIMD::f32x16 round_f32x16(EmuSIMD::f32x16_arg to_round_)
	{
		return _mm512_roundscale_ps(to_round_, RoundingFlag_);
	}

	inline EmuSIMD::f32x16 mod_f32x16(EmuSIMD::f32x16_arg lhs_, EmuSIMD::f32x16_arg rhs_)
	{
		EmuSIMD::f32x16 res = _mm512_div_ps(lhs_, rhs_);
		res = _mm512_trunc_ps(res);
		return _mm512_fnmadd_ps(res, rhs_, lhs_);
	}
#pragma endregion
}

#endif
