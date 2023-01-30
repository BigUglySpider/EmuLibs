#ifndef EMU_SIMD_GENERIC_FUNCS_F32X4_H_INC_
#define EMU_SIMD_GENERIC_FUNCS_F32X4_H_INC_ 1

#include "_common_generic_func_helpers.h"

namespace EmuSIMD::Funcs
{
#pragma region SETTERS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 set_f32x4(float e0, float e1, float e2, float e3)
	{
		return _mm_set_ps(e0, e1, e2, e3);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 setr_f32x4(float e0, float e1, float e2, float e3)
	{
		return _mm_setr_ps(e0, e1, e2, e3);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 set1_f32x4(float all_)
	{
		return _mm_set1_ps(all_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 load_f32x4(const float* p_to_load_)
	{
		return _mm_load_ps(p_to_load_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 setzero_f32x4()
	{
		return _mm_setzero_ps();
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 setmasked_f32x4(std::uint8_t bit_mask_)
	{
		constexpr std::int32_t element_mask = static_cast<std::int32_t>(0xFFFFFFFF);
		return _mm_castsi128_ps
		(
			_mm_set_epi32
			(
				(bit_mask_ & 0x01) * element_mask,
				((bit_mask_ & 0x02) >> 1) * element_mask,
				((bit_mask_ & 0x04) >> 2) * element_mask,
				((bit_mask_ & 0x08) >> 3) * element_mask
			)
		);
	}
#pragma endregion

#pragma region STORES
	EMU_SIMD_COMMON_FUNC_SPEC void store_f32x4(float* p_out_, f32x4_arg a_)
	{
		_mm_store_ps(p_out_, a_);
	}
#pragma endregion

#pragma region CASTS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cast_f32x4_f32x4(f32x4_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cast_f32x8_f32x4(f32x8_arg a_)
	{
		return _mm256_castps256_ps128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cast_f32x16_f32x4(f32x16_arg a_)
	{
		return _mm512_castps512_ps128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cast_f64x2_f32x4(f64x2_arg a_)
	{
		return _mm_castpd_ps(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cast_f64x4_f32x4(f64x4_arg a_)
	{
		return _mm256_castps256_ps128(_mm256_castpd_ps(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cast_f64x8_f32x4(f64x8_arg a_)
	{
		return _mm512_castps512_ps128(_mm512_castpd_ps(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cast_i8x16_f32x4(i8x16_arg a_)
	{
		return _mm_castsi128_ps(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cast_i16x8_f32x4(i16x8_arg a_)
	{
		return _mm_castsi128_ps(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cast_i32x4_f32x4(i32x4_arg a_)
	{
		return _mm_castsi128_ps(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cast_i64x2_f32x4(i64x2_arg a_)
	{
		return _mm_castsi128_ps(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cast_i8x32_f32x4(i8x32_arg a_)
	{
		return _mm256_castps256_ps128(_mm256_castsi256_ps(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cast_i16x16_f32x4(i16x16_arg a_)
	{
		return _mm256_castps256_ps128(_mm256_castsi256_ps(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cast_i32x8_f32x4(i32x8_arg a_)
	{
		return _mm256_castps256_ps128(_mm256_castsi256_ps(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cast_i64x4_f32x4(i64x4_arg a_)
	{
		return _mm256_castps256_ps128(_mm256_castsi256_ps(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cast_i8x64_f32x4(i8x64_arg a_)
	{
		return _mm512_castps512_ps128(_mm512_castsi512_ps(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cast_i16x32_f32x4(i16x32_arg a_)
	{
		return _mm512_castps512_ps128(_mm512_castsi512_ps(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cast_i32x16_f32x4(i32x16_arg a_)
	{
		return _mm512_castps512_ps128(_mm512_castsi512_ps(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cast_i64x8_f32x4(i64x8_arg a_)
	{
		return _mm512_castps512_ps128(_mm512_castsi512_ps(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cast_u8x16_f32x4(u8x16_arg a_)
	{
		return _mm_castsi128_ps(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cast_u16x8_f32x4(u16x8_arg a_)
	{
		return _mm_castsi128_ps(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cast_u32x4_f32x4(u32x4_arg a_)
	{
		return _mm_castsi128_ps(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cast_u64x2_f32x4(u64x2_arg a_)
	{
		return _mm_castsi128_ps(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cast_u8x32_f32x4(u8x32_arg a_)
	{
		return _mm256_castps256_ps128(_mm256_castsi256_ps(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cast_u16x16_f32x4(u16x16_arg a_)
	{
		return _mm256_castps256_ps128(_mm256_castsi256_ps(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cast_u32x8_f32x4(u32x8_arg a_)
	{
		return _mm256_castps256_ps128(_mm256_castsi256_ps(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cast_u64x4_f32x4(u64x4_arg a_)
	{
		return _mm256_castps256_ps128(_mm256_castsi256_ps(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cast_u8x64_f32x4(u8x64_arg a_)
	{
		return _mm512_castps512_ps128(_mm512_castsi512_ps(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cast_u16x32_f32x4(u16x32_arg a_)
	{
		return _mm512_castps512_ps128(_mm512_castsi512_ps(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cast_u32x16_f32x4(u32x16_arg a_)
	{
		return _mm512_castps512_ps128(_mm512_castsi512_ps(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cast_u64x8_f32x4(u64x8_arg a_)
	{
		return _mm512_castps512_ps128(_mm512_castsi512_ps(a_));
	}
#pragma endregion

#pragma region CONVERSIONS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cvt_f32x4_f32x4(f32x4_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cvt_f32x8_f32x4(f32x8_arg a_)
	{
		return _mm256_castps256_ps128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cvt_f32x16_f32x4(f32x16_arg a_)
	{
		return _mm512_castps512_ps128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cvt_f64x2_f32x4(f64x2_arg a_)
	{
		return _mm_cvtpd_ps(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cvt_f64x4_f32x4(f64x4_arg a_)
	{
		return _mm256_cvtpd_ps(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cvt_f64x8_f32x4(f64x8_arg a_)
	{
		return _mm256_cvtpd_ps(_mm512_castpd512_pd256(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cvt_i8x16_f32x4(i8x16_arg a_)
	{
		return _mm_cvtepi32_ps(_mm_cvtepi8_epi32(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cvt_i16x8_f32x4(i16x8_arg a_)
	{
		return _mm_cvtepi32_ps(_mm_cvtepi16_epi32(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cvt_i32x4_f32x4(i32x4_arg a_)
	{
		return _mm_cvtepi32_ps(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cvt_i64x2_f32x4(i64x2_arg a_)
	{
		return _mm_cvtepi64_ps(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cvt_i8x32_f32x4(i8x32_arg a_)
	{
		return _mm_cvtepi32_ps(_mm_cvtepi8_epi32(_mm256_castsi256_si128(a_)));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cvt_i16x16_f32x4(i16x16_arg a_)
	{
		return _mm_cvtepi32_ps(_mm_cvtepi16_epi32(_mm256_castsi256_si128(a_)));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cvt_i32x8_f32x4(i32x8_arg a_)
	{
		return _mm_cvtepi32_ps(_mm256_castsi256_si128(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cvt_i64x4_f32x4(i64x4_arg a_)
	{
		return _mm256_cvtepi64_ps(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cvt_i8x64_f32x4(i8x64_arg a_)
	{
		return _mm_cvtepi32_ps(_mm_cvtepi8_epi32(_mm512_castsi512_si128(a_)));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cvt_i16x32_f32x4(i16x32_arg a_)
	{
		return _mm_cvtepi32_ps(_mm_cvtepi16_epi32(_mm512_castsi512_si128(a_)));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cvt_i32x16_f32x4(i32x16_arg a_)
	{
		return _mm_cvtepi32_ps(_mm512_castsi512_si128(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cvt_i64x8_f32x4(i64x8_arg a_)
	{
		return _mm256_cvtepi64_ps(_mm512_castsi512_si256(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cvt_u8x16_f32x4(u8x16_arg a_)
	{
		return _mm_cvtepi32_ps(_mm_cvtepu8_epi32(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cvt_u16x8_f32x4(u16x8_arg a_)
	{
		return _mm_cvtepi32_ps(_mm_cvtepu16_epi32(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cvt_u32x4_f32x4(u32x4_arg a_)
	{
		return _mm_cvtepu32_ps(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cvt_u64x2_f32x4(u64x2_arg a_)
	{
		return _mm_cvtepu64_ps(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cvt_u8x32_f32x4(u8x32_arg a_)
	{
		return _mm_cvtepi32_ps(_mm_cvtepu8_epi32(_mm256_castsi256_si128(a_)));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cvt_u16x16_f32x4(u16x16_arg a_)
	{
		return _mm_cvtepi32_ps(_mm_cvtepu16_epi32(_mm256_castsi256_si128(a_)));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cvt_u32x8_f32x4(u32x8_arg a_)
	{
		return _mm_cvtepu32_ps(_mm256_castsi256_si128(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cvt_u64x4_f32x4(u64x4_arg a_)
	{
		return _mm256_cvtepu64_ps(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cvt_u8x64_f32x4(u8x64_arg a_)
	{
		return _mm_cvtepi32_ps(_mm_cvtepu8_epi32(_mm512_castsi512_si128(a_)));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cvt_u16x32_f32x4(u16x32_arg a_)
	{
		return _mm_cvtepi32_ps(_mm_cvtepu16_epi32(_mm512_castsi512_si128(a_)));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cvt_u32x16_f32x4(u32x16_arg a_)
	{
		return _mm_cvtepu32_ps(_mm512_castsi512_si128(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cvt_u64x8_f32x4(u64x8_arg a_)
	{
		return _mm256_cvtepu64_ps(_mm512_castsi512_si256(a_));
	}
#pragma endregion

#pragma region COMPARISONS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cmpeq_f32x4(EmuSIMD::f32x4_arg lhs_, EmuSIMD::f32x4_arg rhs_)
	{
		return _mm_cmpeq_ps(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cmpneq_f32x4(EmuSIMD::f32x4_arg lhs_, EmuSIMD::f32x4_arg rhs_)
	{
		return _mm_cmpneq_ps(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cmpgt_f32x4(EmuSIMD::f32x4_arg lhs_, EmuSIMD::f32x4_arg rhs_)
	{
		return _mm_cmpgt_ps(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cmplt_f32x4(EmuSIMD::f32x4_arg lhs_, EmuSIMD::f32x4_arg rhs_)
	{
		return _mm_cmplt_ps(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cmpge_f32x4(EmuSIMD::f32x4_arg lhs_, EmuSIMD::f32x4_arg rhs_)
	{
		return _mm_cmpge_ps(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cmple_f32x4(EmuSIMD::f32x4_arg lhs_, EmuSIMD::f32x4_arg rhs_)
	{
		return _mm_cmple_ps(lhs_, rhs_);
	}
#pragma endregion

#pragma region BASIC_ARITHMETIC
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 mul_all_f32x4(EmuSIMD::f32x4_arg lhs_, EmuSIMD::f32x4_arg rhs_)
	{
		return _mm_mul_ps(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 negate_f32x4(EmuSIMD::f32x4_arg to_negate_)
	{
		return _mm_sub_ps(_mm_setzero_ps(), to_negate_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 add_f32x4(EmuSIMD::f32x4_arg lhs_, EmuSIMD::f32x4_arg rhs_)
	{
		return _mm_add_ps(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 sub_f32x4(EmuSIMD::f32x4_arg lhs_, EmuSIMD::f32x4_arg rhs_)
	{
		return _mm_sub_ps(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 mul_f32x4(EmuSIMD::f32x4_arg lhs_, EmuSIMD::f32x4_arg rhs_)
	{
		return _mm_mul_ps(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 div_f32x4(EmuSIMD::f32x4_arg lhs_, EmuSIMD::f32x4_arg rhs_)
	{
		return _mm_div_ps(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 addsub_f32x4(EmuSIMD::f32x4_arg lhs_, EmuSIMD::f32x4_arg rhs_)
	{
		return _mm_addsub_ps(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 fmadd_f32x4(EmuSIMD::f32x4_arg a_, EmuSIMD::f32x4_arg b_, EmuSIMD::f32x4_arg c_)
	{
		return _mm_fmadd_ps(a_, b_, c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 fmsub_f32x4(EmuSIMD::f32x4_arg a_, EmuSIMD::f32x4_arg b_, EmuSIMD::f32x4_arg c_)
	{
		return _mm_fmsub_ps(a_, b_, c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 fnmadd_f32x4(EmuSIMD::f32x4_arg a_, EmuSIMD::f32x4_arg b_, EmuSIMD::f32x4_arg c_)
	{
		return _mm_fnmadd_ps(a_, b_, c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 fnmsub_f32x4(EmuSIMD::f32x4_arg a_, EmuSIMD::f32x4_arg b_, EmuSIMD::f32x4_arg c_)
	{
		return _mm_fnmsub_ps(a_, b_, c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 fmaddsub_f32x4(EmuSIMD::f32x4_arg a_, EmuSIMD::f32x4_arg b_, EmuSIMD::f32x4_arg c_)
	{
		return _mm_fmaddsub_ps(a_, b_, c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 fmsubadd_f32x4(EmuSIMD::f32x4_arg a_, EmuSIMD::f32x4_arg b_, EmuSIMD::f32x4_arg c_)
	{
		return _mm_fmsubadd_ps(a_, b_, c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 floor_f32x4(EmuSIMD::f32x4_arg to_floor_)
	{
		return _mm_floor_ps(to_floor_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 ceil_f32x4(EmuSIMD::f32x4_arg to_ceil_)
	{
		return _mm_ceil_ps(to_ceil_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 trunc_f32x4(EmuSIMD::f32x4_arg to_trunc_)
	{
		return _mm_round_ps(to_trunc_, _MM_FROUND_TRUNC);
	}

	template<int RoundingFlag_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 round_f32x4(EmuSIMD::f32x4_arg to_round_)
	{
		return _mm_round_ps(to_round_, RoundingFlag_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 mod_f32x4(EmuSIMD::f32x4_arg lhs_, EmuSIMD::f32x4_arg rhs_)
	{
		EmuSIMD::f32x4 res = _mm_div_ps(lhs_, rhs_);
		res = trunc_f32x4(res);
		return _mm_fnmadd_ps(res, rhs_, lhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 abs_f32x4(EmuSIMD::f32x4_arg in_)
	{
		return _mm_andnot_ps(set1_f32x4(-0.0f), in_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 sqrt_f32x4(EmuSIMD::f32x4_arg in_)
	{
		return _mm_sqrt_ps(in_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 rsqrt_f32x4(EmuSIMD::f32x4_arg in_)
	{
		return _mm_rsqrt_ps(in_);
	}
#pragma endregion

#pragma region NEAR_COMPARISONS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cmpnear_f32x4(EmuSIMD::f32x4_arg lhs_, EmuSIMD::f32x4_arg rhs_, EmuSIMD::f32x4_arg epsilon = set1_f32x4(EmuCore::epsilon<float>::get()))
	{
		return cmple_f32x4(abs_f32x4(sub_f32x4(lhs_, rhs_)), epsilon);
	}
#pragma endregion

#pragma region TRIG
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cos_f32x4(EmuSIMD::f32x4_arg in_)
	{
		#ifdef _mm_cos_ps
		return _mm_cos_ps(in_);
		#else
		throw "NOT IMPLEMENTED: cos_f32x4";
		#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 sin_f32x4(EmuSIMD::f32x4_arg in_)
	{
		#ifdef _mm_sin_ps
		return _mm_sin_ps(in_);
		#else
		throw "NOT IMPLEMENTED: sin_f32x4";
		#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 tan_f32x4(EmuSIMD::f32x4_arg in_)
	{
		#ifdef _mm_tan_ps
		return _mm_tan_ps(in_);
		#else
		throw "NOT IMPLEMENTED: tan_f32x4";
		#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 acos_f32x4(EmuSIMD::f32x4_arg in_)
	{
		#ifdef _mm_acos_ps
		return _mm_acos_ps(in_);
		#else
		// Alternative manual approximation, based on https://developer.download.nvidia.com/cg/acos.html implementation
		EmuSIMD::f32x4 in_abs = abs_f32x4(in_);
		EmuSIMD::f32x4 one = set1_f32x4(1.0f);
		EmuSIMD::f32x4 negation_mult = _mm_cmplt_ps(in_, setzero_f32x4());
		negation_mult = _mm_and_ps(one, negation_mult);

		EmuSIMD::f32x4 result = mul_f32x4(set1_f32x4(-0.0187293f), in_abs);
		result = add_f32x4(result, set1_f32x4(0.074261f));
		result = mul_f32x4(result, in_abs);
		result = sub_f32x4(result, set1_f32x4(0.2121144f));
		result = mul_f32x4(result, in_abs);
		result = add_f32x4(result, set1_f32x4(1.5707288f));
		result = sqrt_f32x4(sub_f32x4(one, in_abs));
		
		EmuSIMD::f32x4 tmp = mul_f32x4(set1_f32x4(2.0f), negation_mult);
		tmp = mul_f32x4(tmp, result);
		result = sub_f32x4(result, tmp);

		return fmadd_f32x4(negation_mult, set1_f32x4(3.14159265358979f), result);
		#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 asin_f32x4(EmuSIMD::f32x4_arg in_)
	{
		#ifdef _mm_asin_ps
		return _mm_asin_ps(in_);
		#else
		// Alternative manual approximation, based on https://developer.download.nvidia.com/cg/asin.html implementation
		EmuSIMD::f32x4 in_abs = abs_f32x4(in_);
		EmuSIMD::f32x4 two = set1_f32x4(2.0f);
		EmuSIMD::f32x4 negation_mult = _mm_cmplt_ps(in_, setzero_f32x4());
		negation_mult = _mm_and_ps(two, negation_mult);

		EmuSIMD::f32x4 result = mul_f32x4(set1_f32x4(-0.0187293f), in_abs);
		result = add_f32x4(result, set1_f32x4(0.074261f));
		result = mul_f32x4(result, in_abs);
		result = sub_f32x4(result, set1_f32x4(0.2121144f));
		result = mul_f32x4(result, in_abs);
		result = add_f32x4(result, set1_f32x4(1.5707288f));

		EmuSIMD::f32x4 tmp = sub_f32x4(set1_f32x4(1.0f), in_abs);
		tmp = mul_f32x4(sqrt_f32x4(tmp), result);
		result = set1_f32x4(3.14159265358979f * 0.5f);
		result = sub_f32x4(result, tmp);

		tmp = mul_f32x4(negation_mult, result);
		return sub_f32x4(result, tmp);
		#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 atan2_f32x4(EmuSIMD::f32x4_arg y_, EmuSIMD::f32x4_arg x_)
	{
		#ifdef _mm_atan2_ps
		return atan2_f32x4(y_, x_);
		#else
		// Alternative manual approximation, based on https://developer.download.nvidia.com/cg/atan2.html implementation
		auto abs_x = abs_f32x4(x_);
		auto abs_y = abs_f32x4(y_);
		auto temp2 = abs_f32x4(abs_x);
		auto temp1 = abs_f32x4(abs_y);
		auto temp0 = _mm_max_ps(temp2, temp1);
		temp1 = _mm_min_ps(temp2, temp1);
		temp2 = div_f32x4(set1_f32x4(1.0f), temp0);
		temp2 = mul_f32x4(temp1, temp2);

		auto t4 = mul_f32x4(temp2, temp2);
		temp0 = set1_f32x4(0.013480470f);
		temp0 = fmadd_f32x4(temp0, t4, set1_f32x4(0.057477314f));
		temp0 = fmsub_f32x4(temp0, t4, set1_f32x4(0.121239071f));
		temp0 = fmadd_f32x4(temp0, t4, set1_f32x4(0.195635925f));
		temp0 = fmsub_f32x4(temp0, t4, set1_f32x4(0.332994597f));
		temp0 = fmadd_f32x4(temp0, t4, set1_f32x4(0.999995630f));
		temp2 = mul_f32x4(temp0, temp2);

		//t3 = (abs(y) > abs(x)) ? float(1.570796327) - t3 : t3;
		auto cmp_mask = _mm_cmpgt_ps(abs_y, abs_x);
		temp0 = _mm_and_ps(cmp_mask, set1_f32x4(1.570796327f));
		temp0 = sub_f32x4(temp0, temp2);
		temp2 = _mm_or_ps(_mm_andnot_ps(cmp_mask, temp2), _mm_and_ps(cmp_mask, temp0));

		// t3 = (x < 0) ?  float(3.141592654) - t3 : t3;
		auto zero = setzero_f32x4();
		cmp_mask = _mm_cmplt_ps(x_, zero);
		temp0 = _mm_and_ps(cmp_mask, set1_f32x4(3.141592654f));
		temp0 = sub_f32x4(temp0, temp2);
		temp2 = _mm_or_ps(_mm_andnot_ps(cmp_mask, temp2), _mm_and_ps(cmp_mask, temp0));

		//t3 = (y < 0) ? -t3 : t3;
		cmp_mask = _mm_cmplt_ps(y_, zero);
		temp0 = negate_f32x4(temp2);
		temp2 = _mm_or_ps(_mm_andnot_ps(cmp_mask, temp2), _mm_and_ps(cmp_mask, temp0));

		return temp2;
		#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 atan_f32x4(EmuSIMD::f32x4_arg in_)
	{
		#ifdef _mm_atan_ps
		return _mm_atan_ps(in_);
		#else
		// NOTE: Inefficient impl. as we check for some things that are known at compile time (such as the magnitude of 1.0f, making it absolute, etc)
		return atan2_f32x4(in_, set1_f32x4(1.0f));
		#endif
	}

	// TODO: Test efficiency, apply alternatives for all trig/trunc funcs
#pragma endregion
}

#endif
