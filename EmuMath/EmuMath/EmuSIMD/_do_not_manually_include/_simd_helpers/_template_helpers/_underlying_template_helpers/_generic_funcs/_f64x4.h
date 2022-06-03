#ifndef EMU_SIMD_GENERIC_FUNCS_F64X4_H_INC_
#define EMU_SIMD_GENERIC_FUNCS_F64X4_H_INC_ 1

#include "_common_generic_func_helpers.h"

namespace EmuSIMD::Funcs
{
#pragma region SETTERS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x4 set_f64x4(double e0, double e1, double e2, double e3)
	{
		return _mm256_set_pd(e0, e1, e2, e3);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x4 setr_f64x4(double e0, double e1, double e2, double e3)
	{
		return _mm256_setr_pd(e0, e1, e2, e3);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x4 set1_f64x4(double all_)
	{
		return _mm256_set1_pd(all_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x4 load_f64x4(const double* p_to_load_)
	{
		return _mm256_load_pd(p_to_load_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x4 setzero_f64x4()
	{
		return _mm256_setzero_pd();
	}
#pragma endregion

#pragma region STORES
	EMU_SIMD_COMMON_FUNC_SPEC void store_f64x4(double* p_out_, f64x4_arg a_)
	{
		_mm256_store_pd(p_out_, a_);
	}
#pragma endregion

#pragma region CASTS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x4 cast_f32x4_f64x4(f32x4_arg a_)
	{
		return _mm256_castps_pd(_mm256_castps128_ps256(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x4 cast_f32x8_f64x4(f32x8_arg a_)
	{
		return _mm256_castps_pd(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x4 cast_f32x16_f64x4(f32x16_arg a_)
	{
		return _mm256_castps_pd(_mm512_castps512_ps256(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x4 cast_f64x2_f64x4(f64x2_arg a_)
	{
		return _mm256_castpd128_pd256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x4 cast_f64x4_f64x4(f64x4_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x4 cast_f64x8_f64x4(f64x8_arg a_)
	{
		return _mm512_castpd512_pd256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x4 cast_i8x16_f64x4(i8x16_arg a_)
	{
		return _mm256_castpd128_pd256(_mm_castsi128_pd(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x4 cast_i16x8_f64x4(i16x8_arg a_)
	{
		return _mm256_castpd128_pd256(_mm_castsi128_pd(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x4 cast_i32x4_f64x4(i32x4_arg a_)
	{
		return _mm256_castpd128_pd256(_mm_castsi128_pd(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x4 cast_i64x2_f64x4(i64x2_arg a_)
	{
		return _mm256_castpd128_pd256(_mm_castsi128_pd(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x4 cast_i8x32_f64x4(i8x32_arg a_)
	{
		return _mm256_castsi256_pd(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x4 cast_i16x16_f64x4(i16x16_arg a_)
	{
		return _mm256_castsi256_pd(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x4 cast_i32x8_f64x4(i32x8_arg a_)
	{
		return _mm256_castsi256_pd(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x4 cast_i64x4_f64x4(i64x4_arg a_)
	{
		return _mm256_castsi256_pd(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x4 cast_i8x64_f64x4(i8x64_arg a_)
	{
		return _mm512_castpd512_pd256(_mm512_castsi512_pd(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x4 cast_i16x32_f64x4(i16x32_arg a_)
	{
		return _mm512_castpd512_pd256(_mm512_castsi512_pd(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x4 cast_i32x16_f64x4(i32x16_arg a_)
	{
		return _mm512_castpd512_pd256(_mm512_castsi512_pd(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x4 cast_i64x8_f64x4(i64x8_arg a_)
	{
		return _mm512_castpd512_pd256(_mm512_castsi512_pd(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x4 cast_u8x16_f64x4(u8x16_arg a_)
	{
		return _mm256_castpd128_pd256(_mm_castsi128_pd(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x4 cast_u16x8_f64x4(u16x8_arg a_)
	{
		return _mm256_castpd128_pd256(_mm_castsi128_pd(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x4 cast_u32x4_f64x4(u32x4_arg a_)
	{
		return _mm256_castpd128_pd256(_mm_castsi128_pd(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x4 cast_u64x2_f64x4(u64x2_arg a_)
	{
		return _mm256_castpd128_pd256(_mm_castsi128_pd(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x4 cast_u8x32_f64x4(u8x32_arg a_)
	{
		return _mm256_castsi256_pd(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x4 cast_u16x16_f64x4(u16x16_arg a_)
	{
		return _mm256_castsi256_pd(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x4 cast_u32x8_f64x4(u32x8_arg a_)
	{
		return _mm256_castsi256_pd(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x4 cast_u64x4_f64x4(u64x4_arg a_)
	{
		return _mm256_castsi256_pd(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x4 cast_u8x64_f64x4(u8x64_arg a_)
	{
		return _mm512_castpd512_pd256(_mm512_castsi512_pd(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x4 cast_u16x32_f64x4(u16x32_arg a_)
	{
		return _mm512_castpd512_pd256(_mm512_castsi512_pd(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x4 cast_u32x16_f64x4(u32x16_arg a_)
	{
		return _mm512_castpd512_pd256(_mm512_castsi512_pd(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x4 cast_u64x8_f64x4(u64x8_arg a_)
	{
		return _mm512_castpd512_pd256(_mm512_castsi512_pd(a_));
	}
#pragma endregion

#pragma region CONVERSIONS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x4 cvt_f32x4_f64x4(f32x4_arg a_)
	{
		return _mm256_cvtps_pd(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x4 cvt_f32x8_f64x4(f32x8_arg a_)
	{
		return _mm256_cvtps_pd(_mm256_castps256_ps128(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x4 cvt_f32x16_f64x4(f32x16_arg a_)
	{
		return _mm256_cvtps_pd(_mm512_castps512_ps128(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x4 cvt_f64x2_f64x4(f64x2_arg a_)
	{
		return _mm256_castpd128_pd256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x4 cvt_f64x4_f64x4(f64x4_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x4 cvt_f64x8_f64x4(f64x8_arg a_)
	{
		return _mm512_castpd512_pd256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x4 cvt_i8x16_f64x4(i8x16_arg a_)
	{
		return _mm256_cvtepi64_pd(_mm256_cvtepi8_epi64(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x4 cvt_i16x8_f64x4(i16x8_arg a_)
	{
		return _mm256_cvtepi64_pd(_mm256_cvtepi16_epi64(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x4 cvt_i32x4_f64x4(i32x4_arg a_)
	{
		return _mm256_cvtepi32_pd(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x4 cvt_i64x2_f64x4(i64x2_arg a_)
	{
		return _mm256_castpd128_pd256(_mm_cvtepi64_pd(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x4 cvt_i8x32_f64x4(i8x32_arg a_)
	{
		return _mm256_cvtepi64_pd(_mm256_cvtepi8_epi64(_mm256_castsi256_si128(a_)));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x4 cvt_i16x16_f64x4(i16x16_arg a_)
	{
		return _mm256_cvtepi64_pd(_mm256_cvtepi16_epi64(_mm256_castsi256_si128(a_)));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x4 cvt_i32x8_f64x4(i32x8_arg a_)
	{
		return _mm256_cvtepi32_pd(_mm256_castsi256_si128(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x4 cvt_i64x4_f64x4(i64x4_arg a_)
	{
		return _mm256_cvtepi64_pd(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x4 cvt_i8x64_f64x4(i8x64_arg a_)
	{
		return _mm256_cvtepi64_pd(_mm256_cvtepi8_epi64(_mm512_castsi512_si128(a_)));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x4 cvt_i16x32_f64x4(i16x32_arg a_)
	{
		return _mm256_cvtepi64_pd(_mm256_cvtepi16_epi64(_mm512_castsi512_si128(a_)));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x4 cvt_i32x16_f64x4(i32x16_arg a_)
	{
		return _mm256_cvtepi32_pd(_mm512_castsi512_si128(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x4 cvt_i64x8_f64x4(i64x8_arg a_)
	{
		return _mm256_cvtepi64_pd(_mm512_castsi512_si256(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x4 cvt_u8x16_f64x4(u8x16_arg a_)
	{
		return _mm256_cvtepi64_pd(_mm256_cvtepu8_epi64(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x4 cvt_u16x8_f64x4(u16x8_arg a_)
	{
		return _mm256_cvtepi64_pd(_mm256_cvtepu16_epi64(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x4 cvt_u32x4_f64x4(u32x4_arg a_)
	{
		return _mm256_cvtepu32_pd(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x4 cvt_u64x2_f64x4(u64x2_arg a_)
	{
		return _mm256_castpd128_pd256(_mm_cvtepu64_pd(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x4 cvt_u8x32_f64x4(u8x32_arg a_)
	{
		return _mm256_cvtepi64_pd(_mm256_cvtepu8_epi64(_mm256_castsi256_si128(a_)));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x4 cvt_u16x16_f64x4(u16x16_arg a_)
	{
		return _mm256_cvtepi64_pd(_mm256_cvtepu16_epi64(_mm256_castsi256_si128(a_)));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x4 cvt_u32x8_f64x4(u32x8_arg a_)
	{
		return _mm256_cvtepu32_pd(_mm256_castsi256_si128(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x4 cvt_u64x4_f64x4(u64x4_arg a_)
	{
		return _mm256_cvtepu64_pd(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x4 cvt_u8x64_f64x4(u8x64_arg a_)
	{
		return _mm256_cvtepi64_pd(_mm256_cvtepu8_epi64(_mm512_castsi512_si128(a_)));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x4 cvt_u16x32_f64x4(u16x32_arg a_)
	{
		return _mm256_cvtepi64_pd(_mm256_cvtepu16_epi64(_mm512_castsi512_si128(a_)));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x4 cvt_u32x16_f64x4(u32x16_arg a_)
	{
		return _mm256_cvtepu32_pd(_mm512_castsi512_si128(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x4 cvt_u64x8_f64x4(u64x8_arg a_)
	{
		return _mm256_cvtepu64_pd(_mm512_castsi512_si256(a_));
	}
#pragma endregion

#pragma region BASIC_ARITHMETIC
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x4 mul_all_f64x4(EmuSIMD::f64x4_arg lhs_, EmuSIMD::f64x4_arg rhs_)
	{
		return _mm256_mul_pd(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x4 negate_f64x4(EmuSIMD::f64x4_arg to_negate_)
	{
		return _mm256_sub_pd(_mm256_setzero_pd(), to_negate_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x4 add_f64x4(EmuSIMD::f64x4_arg lhs_, EmuSIMD::f64x4_arg rhs_)
	{
		return _mm256_add_pd(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x4 sub_f64x4(EmuSIMD::f64x4_arg lhs_, EmuSIMD::f64x4_arg rhs_)
	{
		return _mm256_sub_pd(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x4 mul_f64x4(EmuSIMD::f64x4_arg lhs_, EmuSIMD::f64x4_arg rhs_)
	{
		return _mm256_mul_pd(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x4 div_f64x4(EmuSIMD::f64x4_arg lhs_, EmuSIMD::f64x4_arg rhs_)
	{
		return _mm256_div_pd(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x4 addsub_f64x4(EmuSIMD::f64x4_arg lhs_, EmuSIMD::f64x4_arg rhs_)
	{
		return _mm256_addsub_pd(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x4 fmadd_f64x4(EmuSIMD::f64x4_arg a_, EmuSIMD::f64x4_arg b_, EmuSIMD::f64x4_arg c_)
	{
		return _mm256_fmadd_pd(a_, b_, c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x4 fmsub_f64x4(EmuSIMD::f64x4_arg a_, EmuSIMD::f64x4_arg b_, EmuSIMD::f64x4_arg c_)
	{
		return _mm256_fmsub_pd(a_, b_, c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x4 fnmadd_f64x4(EmuSIMD::f64x4_arg a_, EmuSIMD::f64x4_arg b_, EmuSIMD::f64x4_arg c_)
	{
		return _mm256_fnmadd_pd(a_, b_, c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x4 fnmsub_f64x4(EmuSIMD::f64x4_arg a_, EmuSIMD::f64x4_arg b_, EmuSIMD::f64x4_arg c_)
	{
		return _mm256_fnmsub_pd(a_, b_, c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x4 fmaddsub_f64x4(EmuSIMD::f64x4_arg a_, EmuSIMD::f64x4_arg b_, EmuSIMD::f64x4_arg c_)
	{
		return _mm256_fmaddsub_pd(a_, b_, c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x4 fmsubadd_f64x4(EmuSIMD::f64x4_arg a_, EmuSIMD::f64x4_arg b_, EmuSIMD::f64x4_arg c_)
	{
		return _mm256_fmsubadd_pd(a_, b_, c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x4 floor_f64x4(EmuSIMD::f64x4_arg to_floor_)
	{
		return _mm256_floor_pd(to_floor_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x4 ceil_f64x4(EmuSIMD::f64x4_arg to_ceil_)
	{
		return _mm256_ceil_pd(to_ceil_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x4 trunc_f64x4(EmuSIMD::f64x4_arg to_trunc_)
	{
		return _mm256_trunc_pd(to_trunc_);
	}

	template<int RoundingFlag_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x4 round_f64x4(EmuSIMD::f64x4_arg to_round_)
	{
		return _mm256_round_pd(to_round_, RoundingFlag_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x4 mod_f64x4(EmuSIMD::f64x4_arg lhs_, EmuSIMD::f64x4_arg rhs_)
	{
		EmuSIMD::f64x4 res = _mm256_div_pd(lhs_, rhs_);
		res = _mm256_trunc_pd(res);
		return _mm256_fnmadd_pd(res, rhs_, lhs_);
	}
#pragma endregion
}

#endif
