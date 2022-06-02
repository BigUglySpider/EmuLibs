#ifndef EMU_SIMD_GENERIC_FUNCS_F64X8_H_INC_
#define EMU_SIMD_GENERIC_FUNCS_F64X8_H_INC_ 1

#include "_common_generic_func_helpers.h"

namespace EmuSIMD::Funcs
{
#pragma region SETTERS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 set_f64x8(double e0, double e1, double e2, double e3, double e4, double e5, double e6, double e7)
	{
		return _mm512_set_pd(e0, e1, e2, e3, e4, e5, e6, e7);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 setr_f64x8(double e0, double e1, double e2, double e3, double e4, double e5, double e6, double e7)
	{
		return _mm512_setr_pd(e0, e1, e2, e3, e4, e5, e6, e7);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 set1_f64x8(double all_)
	{
		return _mm512_set1_pd(all_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 load_f64x8(const double* p_to_load_)
	{
		return _mm512_load_pd(p_to_load_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 setzero_f64x8()
	{
		return _mm512_setzero_pd();
	}
#pragma endregion

#pragma region STORES
	EMU_SIMD_COMMON_FUNC_SPEC void store_f64x8(double* p_out_, f64x8_arg a_)
	{
		_mm512_store_pd(p_out_, a_);
	}
#pragma endregion

#pragma region SHUFFLES
	template<int ShuffleMask_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 shuffle_f64x8(f64x8_arg a_, f64x8_arg b_)
	{
		return _mm512_shuffle_pd(a_, b_, ShuffleMask_);
	}

	template<int ShuffleMask_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 permute_f64x8(f64x8_arg a_)
	{
		return _mm512_permute_pd(a_, ShuffleMask_);
	}
#pragma endregion

#pragma region CASTS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cast_f32x4_f64x8(f32x4_arg a_)
	{
		return _mm512_castps_pd(_mm512_castps128_ps512(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cast_f32x8_f64x8(f32x8_arg a_)
	{
		return _mm512_castps_pd(_mm512_castps256_ps512(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cast_f32x16_f64x8(f32x16_arg a_)
	{
		return _mm512_castps_pd(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cast_f64x2_f64x8(f64x2_arg a_)
	{
		return _mm512_castpd128_pd512(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cast_f64x4_f64x8(f64x4_arg a_)
	{
		return _mm512_castpd256_pd512(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cast_f64x8_f64x8(f64x8_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cast_i8x16_f64x8(i8x16_arg a_)
	{
		return _mm512_castpd128_pd512(_mm_castsi128_pd(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cast_i16x8_f64x8(i16x8_arg a_)
	{
		return _mm512_castpd128_pd512(_mm_castsi128_pd(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cast_i32x4_f64x8(i32x4_arg a_)
	{
		return _mm512_castpd128_pd512(_mm_castsi128_pd(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cast_i64x2_f64x8(i64x2_arg a_)
	{
		return _mm512_castpd128_pd512(_mm_castsi128_pd(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cast_i8x32_f64x8(i8x32_arg a_)
	{
		return _mm512_castpd256_pd512(_mm256_castsi256_pd(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cast_i16x16_f64x8(i16x16_arg a_)
	{
		return _mm512_castpd256_pd512(_mm256_castsi256_pd(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cast_i32x8_f64x8(i32x8_arg a_)
	{
		return _mm512_castpd256_pd512(_mm256_castsi256_pd(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cast_i64x4_f64x8(i64x4_arg a_)
	{
		return _mm512_castpd256_pd512(_mm256_castsi256_pd(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cast_i8x64_f64x8(i8x64_arg a_)
	{
		return _mm512_castsi512_pd(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cast_i16x32_f64x8(i16x32_arg a_)
	{
		return _mm512_castsi512_pd(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cast_i32x16_f64x8(i32x16_arg a_)
	{
		return _mm512_castsi512_pd(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cast_i64x8_f64x8(i64x8_arg a_)
	{
		return _mm512_castsi512_pd(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cast_u8x16_f64x8(u8x16_arg a_)
	{
		return _mm512_castpd128_pd512(_mm_castsi128_pd(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cast_u16x8_f64x8(u16x8_arg a_)
	{
		return _mm512_castpd128_pd512(_mm_castsi128_pd(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cast_u32x4_f64x8(u32x4_arg a_)
	{
		return _mm512_castpd128_pd512(_mm_castsi128_pd(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cast_u64x2_f64x8(u64x2_arg a_)
	{
		return _mm512_castpd128_pd512(_mm_castsi128_pd(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cast_u8x32_f64x8(u8x32_arg a_)
	{
		return _mm512_castpd256_pd512(_mm256_castsi256_pd(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cast_u16x16_f64x8(u16x16_arg a_)
	{
		return _mm512_castpd256_pd512(_mm256_castsi256_pd(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cast_u32x8_f64x8(u32x8_arg a_)
	{
		return _mm512_castpd256_pd512(_mm256_castsi256_pd(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cast_u64x4_f64x8(u64x4_arg a_)
	{
		return _mm512_castpd256_pd512(_mm256_castsi256_pd(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cast_u8x64_f64x8(u8x64_arg a_)
	{
		return _mm512_castsi512_pd(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cast_u16x32_f64x8(u16x32_arg a_)
	{
		return _mm512_castsi512_pd(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cast_u32x16_f64x8(u32x16_arg a_)
	{
		return _mm512_castsi512_pd(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cast_u64x8_f64x8(u64x8_arg a_)
	{
		return _mm512_castsi512_pd(a_);
	}
#pragma endregion

#pragma region CONVERSIONS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cvt_f32x4_f64x8(f32x4_arg a_)
	{
		return _mm512_castpd256_pd512(_mm256_cvtps_pd(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cvt_f32x8_f64x8(f32x8_arg a_)
	{
		return _mm512_cvtps_pd(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cvt_f32x16_f64x8(f32x16_arg a_)
	{
		return _mm512_cvtps_pd(_mm512_castps512_ps256(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cvt_f64x2_f64x8(f64x2_arg a_)
	{
		return _mm512_castpd128_pd512(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cvt_f64x4_f64x8(f64x4_arg a_)
	{
		return _mm512_castpd256_pd512(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cvt_f64x8_f64x8(f64x8_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cvt_i8x16_f64x8(i8x16_arg a_)
	{
		return _mm512_cvtepi64_pd(_mm512_cvtepi8_epi64(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cvt_i16x8_f64x8(i16x8_arg a_)
	{
		return _mm512_cvtepi64_pd(_mm512_cvtepi16_epi64(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cvt_i32x4_f64x8(i32x4_arg a_)
	{
		return _mm512_castpd256_pd512(_mm256_cvtepi32_pd(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cvt_i64x2_f64x8(i64x2_arg a_)
	{
		return _mm512_castpd128_pd512(_mm_cvtepi64_pd(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cvt_i8x32_f64x8(i8x32_arg a_)
	{
		return _mm512_cvtepi64_pd(_mm512_cvtepi8_epi64(_mm256_castsi256_si128(a_)));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cvt_i16x16_f64x8(i16x16_arg a_)
	{
		return _mm512_cvtepi64_pd(_mm512_cvtepi16_epi64(_mm256_castsi256_si128(a_)));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cvt_i32x8_f64x8(i32x8_arg a_)
	{
		return _mm512_cvtepi32_pd(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cvt_i64x4_f64x8(i64x4_arg a_)
	{
		return _mm512_castpd256_pd512(_mm256_cvtepi64_pd(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cvt_i8x32_f64x8(i8x64_arg a_)
	{
		return _mm512_cvtepi64_pd(_mm512_cvtepi8_epi64(_mm512_castsi512_si128(a_)));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cvt_i16x16_f64x8(i16x32_arg a_)
	{
		return _mm512_cvtepi64_pd(_mm512_cvtepi16_epi64(_mm512_castsi512_si128(a_)));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cvt_i32x8_f64x8(i32x16_arg a_)
	{
		return _mm512_cvtepi32_pd(_mm512_castsi512_si256(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cvt_i64x4_f64x8(i64x8_arg a_)
	{
		return _mm512_cvtepi64_pd(a_);
	}







	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cvt_u8x16_f64x8(u8x16_arg a_)
	{
		return _mm512_cvtepi64_pd(_mm512_cvtepu8_epi64(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cvt_u16x8_f64x8(u16x8_arg a_)
	{
		return _mm512_cvtepi64_pd(_mm512_cvtepu16_epi64(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cvt_u32x4_f64x8(u32x4_arg a_)
	{
		return _mm512_castpd256_pd512(_mm256_cvtepu32_pd(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cvt_u64x2_f64x8(u64x2_arg a_)
	{
		return _mm512_castpd128_pd512(_mm_cvtepu64_pd(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cvt_u8x32_f64x8(u8x32_arg a_)
	{
		return _mm512_cvtepi64_pd(_mm512_cvtepu8_epi64(_mm256_castsi256_si128(a_)));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cvt_u16x16_f64x8(u16x16_arg a_)
	{
		return _mm512_cvtepi64_pd(_mm512_cvtepu16_epi64(_mm256_castsi256_si128(a_)));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cvt_u32x8_f64x8(u32x8_arg a_)
	{
		return _mm512_cvtepu32_pd(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cvt_u64x4_f64x8(u64x4_arg a_)
	{
		return _mm512_castpd256_pd512(_mm256_cvtepu64_pd(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cvt_u8x32_f64x8(u8x64_arg a_)
	{
		return _mm512_cvtepi64_pd(_mm512_cvtepu8_epi64(_mm512_castsi512_si128(a_)));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cvt_u16x16_f64x8(u16x32_arg a_)
	{
		return _mm512_cvtepi64_pd(_mm512_cvtepu16_epi64(_mm512_castsi512_si128(a_)));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cvt_u32x8_f64x8(u32x16_arg a_)
	{
		return _mm512_cvtepu32_pd(_mm512_castsi512_si256(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cvt_u64x4_f64x8(u64x8_arg a_)
	{
		return _mm512_cvtepu64_pd(a_);
	}
#pragma endregion

#pragma region BASIC_ARITHMETIC
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 mul_all_f64x8(EmuSIMD::f64x8_arg lhs_, EmuSIMD::f64x8_arg rhs_)
	{
		return _mm512_mul_pd(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 negate_f64x8(EmuSIMD::f64x8_arg to_negate_)
	{
		return _mm512_sub_pd(_mm512_setzero_pd(), to_negate_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 add_f64x8(EmuSIMD::f64x8_arg lhs_, EmuSIMD::f64x8_arg rhs_)
	{
		return _mm512_add_pd(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 sub_f64x8(EmuSIMD::f64x8_arg lhs_, EmuSIMD::f64x8_arg rhs_)
	{
		return _mm512_sub_pd(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 mul_f64x8(EmuSIMD::f64x8_arg lhs_, EmuSIMD::f64x8_arg rhs_)
	{
		return _mm512_mul_pd(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 div_f64x8(EmuSIMD::f64x8_arg lhs_, EmuSIMD::f64x8_arg rhs_)
	{
		return _mm512_div_pd(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 addsub_f64x8(EmuSIMD::f64x8_arg lhs_, EmuSIMD::f64x8_arg rhs_)
	{
		return _mm512_fmaddsub_pd(_mm512_set1_pd(1.0), lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 fmadd_f64x8(EmuSIMD::f64x8_arg a_, EmuSIMD::f64x8_arg b_, EmuSIMD::f64x8_arg c_)
	{
		return _mm512_fmadd_pd(a_, b_, c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 fmsub_f64x8(EmuSIMD::f64x8_arg a_, EmuSIMD::f64x8_arg b_, EmuSIMD::f64x8_arg c_)
	{
		return _mm512_fmsub_pd(a_, b_, c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 fnmadd_f64x8(EmuSIMD::f64x8_arg a_, EmuSIMD::f64x8_arg b_, EmuSIMD::f64x8_arg c_)
	{
		return _mm512_fnmadd_pd(a_, b_, c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 fnmsub_f64x8(EmuSIMD::f64x8_arg a_, EmuSIMD::f64x8_arg b_, EmuSIMD::f64x8_arg c_)
	{
		return _mm512_fnmsub_pd(a_, b_, c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 fmaddsub_f64x8(EmuSIMD::f64x8_arg a_, EmuSIMD::f64x8_arg b_, EmuSIMD::f64x8_arg c_)
	{
		return _mm512_fmaddsub_pd(a_, b_, c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 fmsubadd_f64x8(EmuSIMD::f64x8_arg a_, EmuSIMD::f64x8_arg b_, EmuSIMD::f64x8_arg c_)
	{
		return _mm512_fmsubadd_pd(a_, b_, c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 floor_f64x8(EmuSIMD::f64x8_arg to_floor_)
	{
		return _mm512_floor_pd(to_floor_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 ceil_f64x8(EmuSIMD::f64x8_arg to_ceil_)
	{
		return _mm512_ceil_pd(to_ceil_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 trunc_f64x8(EmuSIMD::f64x8_arg to_trunc_)
	{
		return _mm512_trunc_pd(to_trunc_);
	}

	template<int RoundingFlag_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 round_f64x8(EmuSIMD::f64x8_arg to_round_)
	{
		return _mm512_roundscale_pd(to_round_, RoundingFlag_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 mod_f64x8(EmuSIMD::f64x8_arg lhs_, EmuSIMD::f64x8_arg rhs_)
	{
		EmuSIMD::f64x8 res = _mm512_div_pd(lhs_, rhs_);
		res = _mm512_trunc_pd(res);
		return _mm512_fnmadd_pd(res, rhs_, lhs_);
	}
#pragma endregion
}

#endif
