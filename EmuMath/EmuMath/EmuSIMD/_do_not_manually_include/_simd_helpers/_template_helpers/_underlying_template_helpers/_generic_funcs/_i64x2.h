#ifndef EMU_SIMD_GENERIC_FUNCS_I64X2_H_INC_
#define EMU_SIMD_GENERIC_FUNCS_I64X2_H_INC_ 1

#include "_common_generic_func_helpers.h"

namespace EmuSIMD::Funcs
{
#pragma region SETTERS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 set_i64x2(std::int64_t e0, std::int64_t e1)
	{
		return _mm_set_epi64x(e0, e1);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 setr_i64x2(std::int64_t e0, std::int64_t e1)
	{
		return _mm_set_epi64x(e1, e0);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 set1_i64x2(std::int64_t all_)
	{
		return _mm_set1_epi64x(all_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 load_i64x2(const std::int64_t* p_to_load_)
	{
		return _mm_load_si128(reinterpret_cast<const __m128i*>(p_to_load_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 setzero_i64x2()
	{
		return _mm_setzero_si128();
	}
#pragma endregion

#pragma region STORES
	EMU_SIMD_COMMON_FUNC_SPEC void store_i64x2(std::int64_t* p_out_, i64x2_arg a_)
	{
		_mm_store_si128(reinterpret_cast<__m128i*>(p_out_), a_);
	}
#pragma endregion

#pragma region CASTS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 cast_f32x4_i64x2(f32x4_arg a_)
	{
		return _mm_castps_si128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 cast_f32x8_i64x2(f32x8_arg a_)
	{
		return _mm256_castsi256_si128(_mm256_castps_si256(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 cast_f32x16_i64x2(f32x16_arg a_)
	{
		return _mm512_castsi512_si128(_mm512_castps_si512(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 cast_f64x2_i64x2(f64x2_arg a_)
	{
		return _mm_castpd_si128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 cast_f64x4_i64x2(f64x4_arg a_)
	{
		return _mm256_castsi256_si128(_mm256_castpd_si256(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 cast_f64x8_i64x2(f64x8_arg a_)
	{
		return _mm512_castsi512_si128(_mm512_castpd_si512(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 cast_i8x16_i64x2(i8x16_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 cast_i16x8_i64x2(i16x8_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 cast_i32x4_i64x2(i32x4_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 cast_i64x2_i64x2(i64x2_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 cast_i8x32_i64x2(i8x32_arg a_)
	{
		return _mm256_castsi256_si128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 cast_i16x16_i64x2(i16x16_arg a_)
	{
		return _mm256_castsi256_si128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 cast_i32x8_i64x2(i32x8_arg a_)
	{
		return _mm256_castsi256_si128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 cast_i64x4_i64x2(i64x4_arg a_)
	{
		return _mm256_castsi256_si128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 cast_i8x64_i64x2(i8x64_arg a_)
	{
		return _mm512_castsi512_si128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 cast_i16x32_i64x2(i16x32_arg a_)
	{
		return _mm512_castsi512_si128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 cast_i32x16_i64x2(i32x16_arg a_)
	{
		return _mm512_castsi512_si128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 cast_i64x8_i64x2(i64x8_arg a_)
	{
		return _mm512_castsi512_si128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 cast_u8x16_i64x2(u8x16_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 cast_u16x8_i64x2(u16x8_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 cast_u32x4_i64x2(u32x4_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 cast_u64x2_i64x2(u64x2_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 cast_u8x32_i64x2(u8x32_arg a_)
	{
		return _mm256_castsi256_si128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 cast_u16x16_i64x2(u16x16_arg a_)
	{
		return _mm256_castsi256_si128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 cast_u32x8_i64x2(u32x8_arg a_)
	{
		return _mm256_castsi256_si128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 cast_u64x4_i64x2(u64x4_arg a_)
	{
		return _mm256_castsi256_si128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 cast_u8x64_i64x2(u8x64_arg a_)
	{
		return _mm512_castsi512_si128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 cast_u16x32_i64x2(u16x32_arg a_)
	{
		return _mm512_castsi512_si128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 cast_u32x16_i64x2(u32x16_arg a_)
	{
		return _mm512_castsi512_si128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 cast_u64x8_i64x2(u64x8_arg a_)
	{
		return _mm512_castsi512_si128(a_);
	}
#pragma endregion

#pragma region CONVERSIONS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 cvt_f32x4_i64x2(f32x4_arg a_)
	{
		return _mm_cvtps_epi64(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 cvt_f32x8_i64x2(f32x8_arg a_)
	{
		return _mm_cvtps_epi64(_mm256_castps256_ps128(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 cvt_f32x16_i64x2(f32x16_arg a_)
	{
		return _mm_cvtps_epi64(_mm512_castps512_ps128(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 cvt_f64x2_i64x2(f64x2_arg a_)
	{
		return _mm_cvtpd_epi64(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 cvt_f64x4_i64x2(f64x4_arg a_)
	{
		return _mm_cvtpd_epi64(_mm256_castpd256_pd128(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 cvt_f64x8_i64x2(f64x8_arg a_)
	{
		return _mm_cvtpd_epi64(_mm512_castpd512_pd128(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 cvt_i8x16_i64x2(i8x16_arg a_)
	{
		return _mm_cvtepi8_epi64(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 cvt_i16x8_i64x2(i16x8_arg a_)
	{
		return _mm_cvtepi16_epi64(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 cvt_i32x4_i64x2(i32x4_arg a_)
	{
		return _mm_cvtepi32_epi64(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 cvt_i64x2_i64x2(i64x2_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 cvt_i8x32_i64x2(i8x32_arg a_)
	{
		return _mm_cvtepi8_epi64(_mm256_castsi256_si128(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 cvt_i16x16_i64x2(i16x16_arg a_)
	{
		return _mm_cvtepi16_epi64(_mm256_castsi256_si128(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 cvt_i32x8_i64x2(i32x8_arg a_)
	{
		return _mm_cvtepi32_epi64(_mm256_castsi256_si128(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 cvt_i64x4_i64x2(i64x4_arg a_)
	{
		return _mm256_castsi256_si128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 cvt_i8x64_i64x2(i8x64_arg a_)
	{
		return _mm_cvtepi8_epi64(_mm512_castsi512_si128(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 cvt_i16x32_i64x2(i16x32_arg a_)
	{
		return _mm_cvtepi16_epi64(_mm512_castsi512_si128(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 cvt_i32x16_i64x2(i32x16_arg a_)
	{
		return _mm_cvtepi32_epi64(_mm512_castsi512_si128(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 cvt_i64x8_i64x2(i64x8_arg a_)
	{
		return _mm512_castsi512_si128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 cvt_u8x16_i64x2(i8x16_arg a_)
	{
		return _mm_cvtepu8_epi64(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 cvt_u16x8_i64x2(i16x8_arg a_)
	{
		return _mm_cvtepu16_epi64(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 cvt_u32x4_i64x2(i32x4_arg a_)
	{
		return _mm_cvtepu32_epi64(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 cvt_u64x2_i64x2(i64x2_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 cvt_u8x32_i64x2(i8x32_arg a_)
	{
		return _mm_cvtepu8_epi64(_mm256_castsi256_si128(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 cvt_u16x16_i64x2(i16x16_arg a_)
	{
		return _mm_cvtepu16_epi64(_mm256_castsi256_si128(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 cvt_u32x8_i64x2(i32x8_arg a_)
	{
		return _mm_cvtepu32_epi64(_mm256_castsi256_si128(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 cvt_u64x4_i64x2(i64x4_arg a_)
	{
		return _mm256_castsi256_si128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 cvt_u8x64_i64x2(i8x64_arg a_)
	{
		return _mm_cvtepu8_epi64(_mm512_castsi512_si128(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 cvt_u16x32_i64x2(i16x32_arg a_)
	{
		return _mm_cvtepu16_epi64(_mm512_castsi512_si128(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 cvt_u32x16_i64x2(i32x16_arg a_)
	{
		return _mm_cvtepu32_epi64(_mm512_castsi512_si128(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 cvt_u64x8_i64x2(i64x8_arg a_)
	{
		return _mm512_castsi512_si128(a_);
	}
#pragma endregion

#pragma region BASIC_ARITHMETIC
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 mul_all_i64x2(EmuSIMD::i64x2_arg lhs_, EmuSIMD::i64x2_arg rhs_)
	{
		return _mm_mullo_epi64(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 negate_i64x2(EmuSIMD::i64x2_arg to_negate_)
	{
		return _mm_sub_epi64(_mm_setzero_si128(), to_negate_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 add_i64x2(EmuSIMD::i64x2_arg lhs_, EmuSIMD::i64x2_arg rhs_)
	{
		return _mm_add_epi64(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 sub_i64x2(EmuSIMD::i64x2_arg lhs_, EmuSIMD::i64x2_arg rhs_)
	{
		return _mm_sub_epi64(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 mul_i64x2(EmuSIMD::i64x2_arg lhs_, EmuSIMD::i64x2_arg rhs_)
	{
		return _mm_mullo_epi64(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 div_i64x2(EmuSIMD::i64x2_arg lhs_, EmuSIMD::i64x2_arg rhs_)
	{
		return _mm_div_epi64(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 addsub_i64x2(EmuSIMD::i64x2_arg lhs_, EmuSIMD::i64x2_arg rhs_)
	{
		constexpr std::int64_t bytes_mask = static_cast<std::int64_t>(0xFFFFFFFFFFFFFFFF);
		const EmuSIMD::i64x2 mask = _mm_set_epi64x(bytes_mask, 0);
		EmuSIMD::i64x2 out = _mm_add_epi64(lhs_, _mm_and_si128(mask, rhs_));
		return _mm_sub_epi64(lhs_, _mm_andnot_si128(mask, rhs_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 subadd_i64x2(EmuSIMD::i64x2_arg lhs_, EmuSIMD::i64x2_arg rhs_)
	{
		constexpr std::int64_t bytes_mask = static_cast<std::int64_t>(0xFFFFFFFF);
		const EmuSIMD::i64x2 mask = _mm_set_epi64x(bytes_mask, 0);
		EmuSIMD::i64x2 out = _mm_sub_epi64(lhs_, _mm_and_si128(mask, rhs_));
		return _mm_add_epi64(lhs_, _mm_andnot_si128(mask, rhs_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 fmadd_i64x2(EmuSIMD::i64x2_arg a_, EmuSIMD::i64x2_arg b_, EmuSIMD::i64x2_arg c_)
	{
		return _mm_add_epi64(mul_all_i64x2(a_, b_), c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 fmsub_i64x2(EmuSIMD::i64x2_arg a_, EmuSIMD::i64x2_arg b_, EmuSIMD::i64x2_arg c_)
	{
		return _mm_sub_epi64(mul_all_i64x2(a_, b_), c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 fnmadd_i64x2(EmuSIMD::i64x2_arg a_, EmuSIMD::i64x2_arg b_, EmuSIMD::i64x2_arg c_)
	{
		return _mm_add_epi64(mul_all_i64x2(negate_i64x2(a_), b_), c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 fnmsub_i64x2(EmuSIMD::i64x2_arg a_, EmuSIMD::i64x2_arg b_, EmuSIMD::i64x2_arg c_)
	{
		return _mm_sub_epi64(mul_all_i64x2(negate_i64x2(a_), b_), c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 fmaddsub_i64x2(EmuSIMD::i64x2_arg a_, EmuSIMD::i64x2_arg b_, EmuSIMD::i64x2_arg c_)
	{
		return addsub_i64x2(mul_all_i64x2(a_, b_), c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 fmsubadd_i64x2(EmuSIMD::i64x2_arg a_, EmuSIMD::i64x2_arg b_, EmuSIMD::i64x2_arg c_)
	{
		return subadd_i64x2(mul_all_i64x2(a_, b_), c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 floor_i64x2(EmuSIMD::i64x2_arg to_floor_)
	{
		return to_floor_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 ceil_i64x2(EmuSIMD::i64x2_arg to_ceil_)
	{
		return to_ceil_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 trunc_i64x2(EmuSIMD::i64x2_arg to_trunc_)
	{
		return to_trunc_;
	}

	template<int RoundingFlag_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 round_i64x2(EmuSIMD::i64x2_arg to_round_)
	{
		return to_round_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 mod_i64x2(EmuSIMD::i64x2_arg lhs_, EmuSIMD::i64x2_arg rhs_)
	{
		return _mm_rem_epi64(lhs_, rhs_);
	}
#pragma endregion
}

#endif
