#ifndef EMU_SIMD_GENERIC_FUNCS_F32X8_H_INC_
#define EMU_SIMD_GENERIC_FUNCS_F32X8_H_INC_ 1

#include "_common_generic_func_helpers.h"

namespace EmuSIMD::Funcs
{
#pragma region SETTERS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 set_f32x8(float e0, float e1, float e2, float e3, float e4, float e5, float e6, float e7)
	{
		return _mm256_set_ps(e0, e1, e2, e3, e4, e5, e6, e7);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 setr_f32x8(float e0, float e1, float e2, float e3, float e4, float e5, float e6, float e7)
	{
		return _mm256_setr_ps(e0, e1, e2, e3, e4, e5, e6, e7);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 set1_f32x8(float all_)
	{
		return _mm256_set1_ps(all_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 load_f32x8(const float* p_to_load_)
	{
		return _mm256_load_ps(p_to_load_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 setzero_f32x8()
	{
		return _mm256_setzero_ps();
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 setmasked_f32x8(std::uint8_t bit_mask_)
	{
		constexpr std::int32_t element_mask = static_cast<std::int32_t>(0xFFFFFFFF);
		return _mm256_castsi256_ps
		(
			_mm256_set_epi32
			(
				(bit_mask_ & 0x01) * element_mask,
				((bit_mask_ & 0x02) >> 1) * element_mask,
				((bit_mask_ & 0x04) >> 2) * element_mask,
				((bit_mask_ & 0x08) >> 3) * element_mask,
				((bit_mask_ & 0x10) >> 4) * element_mask,
				((bit_mask_ & 0x20) >> 5) * element_mask,
				((bit_mask_ & 0x40) >> 6) * element_mask,
				((bit_mask_ & 0x80) >> 7) * element_mask
			)
		);
	}
#pragma endregion

#pragma region STORES
	EMU_SIMD_COMMON_FUNC_SPEC void store_f32x8(float* p_out_, f32x8_arg a_)
	{
		_mm256_store_ps(p_out_, a_);
	}
#pragma endregion

#pragma region CASTS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 cast_f32x4_f32x8(f32x4_arg a_)
	{
		return _mm256_castps128_ps256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 cast_f32x8_f32x8(f32x8_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 cast_f32x16_f32x8(f32x16_arg a_)
	{
		return _mm512_castps512_ps256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 cast_f64x2_f32x8(f64x2_arg a_)
	{
		return _mm256_castpd_ps(_mm256_castpd128_pd256(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 cast_f64x4_f32x8(f64x4_arg a_)
	{
		return _mm256_castpd_ps(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 cast_f64x8_f32x8(f64x8_arg a_)
	{
		return _mm512_castps512_ps256(_mm512_castpd_ps(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 cast_i8x16_f32x8(i8x16_arg a_)
	{
		return _mm256_castsi256_ps(_mm256_castsi128_si256(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 cast_i16x8_f32x8(i16x8_arg a_)
	{
		return _mm256_castsi256_ps(_mm256_castsi128_si256(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 cast_i32x4_f32x8(i32x4_arg a_)
	{
		return _mm256_castsi256_ps(_mm256_castsi128_si256(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 cast_i64x2_f32x8(i64x2_arg a_)
	{
		return _mm256_castsi256_ps(_mm256_castsi128_si256(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 cast_i8x32_f32x8(i8x32_arg a_)
	{
		return _mm256_castsi256_ps(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 cast_i16x16_f32x8(i16x16_arg a_)
	{
		return _mm256_castsi256_ps(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 cast_i32x8_f32x8(i32x8_arg a_)
	{
		return _mm256_castsi256_ps(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 cast_i64x4_f32x8(i64x4_arg a_)
	{
		return _mm256_castsi256_ps(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 cast_i8x64_f32x8(i8x64_arg a_)
	{
		return _mm256_castsi256_ps(_mm512_castsi512_si256(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 cast_i16x32_f32x8(i16x32_arg a_)
	{
		return _mm256_castsi256_ps(_mm512_castsi512_si256(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 cast_i32x16_f32x8(i32x16_arg a_)
	{
		return _mm256_castsi256_ps(_mm512_castsi512_si256(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 cast_i64x8_f32x8(i64x8_arg a_)
	{
		return _mm256_castsi256_ps(_mm512_castsi512_si256(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 cast_u8x16_f32x8(u8x16_arg a_)
	{
		return _mm256_castsi256_ps(_mm256_castsi128_si256(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 cast_u16x8_f32x8(u16x8_arg a_)
	{
		return _mm256_castsi256_ps(_mm256_castsi128_si256(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 cast_u32x4_f32x8(u32x4_arg a_)
	{
		return _mm256_castsi256_ps(_mm256_castsi128_si256(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 cast_u64x2_f32x8(u64x2_arg a_)
	{
		return _mm256_castsi256_ps(_mm256_castsi128_si256(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 cast_u8x32_f32x8(u8x32_arg a_)
	{
		return _mm256_castsi256_ps(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 cast_u16x16_f32x8(u16x16_arg a_)
	{
		return _mm256_castsi256_ps(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 cast_u32x8_f32x8(u32x8_arg a_)
	{
		return _mm256_castsi256_ps(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 cast_u64x4_f32x8(u64x4_arg a_)
	{
		return _mm256_castsi256_ps(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 cast_u8x64_f32x8(u8x64_arg a_)
	{
		return _mm256_castsi256_ps(_mm512_castsi512_si256(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 cast_u16x32_f32x8(u16x32_arg a_)
	{
		return _mm256_castsi256_ps(_mm512_castsi512_si256(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 cast_u32x16_f32x8(u32x16_arg a_)
	{
		return _mm256_castsi256_ps(_mm512_castsi512_si256(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 cast_u64x8_f32x8(u64x8_arg a_)
	{
		return _mm256_castsi256_ps(_mm512_castsi512_si256(a_));
	}
#pragma endregion

#pragma region CONVERSIONS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 cvt_f32x4_f32x8(f32x4_arg a_)
	{
		return _mm256_castps128_ps256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 cvt_f32x8_f32x8(f32x8_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 cvt_f32x16_f32x8(f32x16_arg a_)
	{
		return _mm512_castps512_ps256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 cvt_f64x2_f32x8(f64x2_arg a_)
	{
		return _mm256_castps128_ps256(_mm_cvtpd_ps(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 cvt_f64x4_f32x8(f64x4_arg a_)
	{
		return _mm256_castps128_ps256(_mm256_cvtpd_ps(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 cvt_f64x8_f32x8(f64x8_arg a_)
	{
		return _mm512_cvtpd_ps(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 cvt_i8x16_f32x8(i8x16_arg a_)
	{
		return _mm256_cvtepi32_ps(_mm256_cvtepi8_epi32(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 cvt_i16x8_f32x8(i16x8_arg a_)
	{
		return _mm256_cvtepi32_ps(_mm256_cvtepi16_epi32(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 cvt_i32x4_f32x8(i32x4_arg a_)
	{
		return _mm256_castps128_ps256(_mm_cvtepi32_ps(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 cvt_i64x2_f32x8(i64x2_arg a_)
	{
		return _mm256_castps128_ps256(_mm_cvtepi64_ps(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 cvt_i8x32_f32x8(i8x32_arg a_)
	{
		return _mm256_cvtepi32_ps(_mm256_cvtepi8_epi32(_mm256_castsi256_si128(a_)));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 cvt_i16x16_f32x8(i16x16_arg a_)
	{
		return _mm256_cvtepi32_ps(_mm256_cvtepi16_epi32(_mm256_castsi256_si128(a_)));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 cvt_i32x8_f32x8(i32x8_arg a_)
	{
		return _mm256_cvtepi32_ps(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 cvt_i64x4_f32x8(i64x4_arg a_)
	{
		return _mm256_castps128_ps256(_mm256_cvtepi64_ps(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 cvt_i8x64_f32x8(i8x64_arg a_)
	{
		return _mm256_cvtepi32_ps(_mm256_cvtepi8_epi32(_mm512_castsi512_si128(a_)));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 cvt_i16x32_f32x8(i16x32_arg a_)
	{
		return _mm256_cvtepi32_ps(_mm256_cvtepi16_epi32(_mm512_castsi512_si128(a_)));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 cvt_i32x16_f32x8(i32x16_arg a_)
	{
		return _mm256_cvtepi32_ps(_mm512_castsi512_si256(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 cvt_i64x8_f32x8(i64x8_arg a_)
	{
		return _mm512_cvtepi64_ps(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 cvt_u8x16_f32x8(u8x16_arg a_)
	{
		return _mm256_cvtepi32_ps(_mm256_cvtepu8_epi32(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 cvt_u16x8_f32x8(u16x8_arg a_)
	{
		return _mm256_cvtepi32_ps(_mm256_cvtepu16_epi32(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 cvt_u32x4_f32x8(u32x4_arg a_)
	{
		return _mm256_castps128_ps256(_mm_cvtepu32_ps(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 cvt_u64x2_f32x8(u64x2_arg a_)
	{
		return _mm256_castps128_ps256(_mm_cvtepu64_ps(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 cvt_u8x32_f32x8(u8x32_arg a_)
	{
		return _mm256_cvtepi32_ps(_mm256_cvtepu8_epi32(_mm256_castsi256_si128(a_)));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 cvt_u16x16_f32x8(u16x16_arg a_)
	{
		return _mm256_cvtepi32_ps(_mm256_cvtepu16_epi32(_mm256_castsi256_si128(a_)));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 cvt_u32x8_f32x8(u32x8_arg a_)
	{
		return _mm256_cvtepu32_ps(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 cvt_u64x4_f32x8(u64x4_arg a_)
	{
		return _mm256_castps128_ps256(_mm256_cvtepu64_ps(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 cvt_u8x64_f32x8(u8x64_arg a_)
	{
		return _mm256_cvtepi32_ps(_mm256_cvtepu8_epi32(_mm512_castsi512_si128(a_)));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 cvt_u16x32_f32x8(u16x32_arg a_)
	{
		return _mm256_cvtepi32_ps(_mm256_cvtepu16_epi32(_mm512_castsi512_si128(a_)));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 cvt_u32x16_f32x8(u32x16_arg a_)
	{
		return _mm256_cvtepu32_ps(_mm512_castsi512_si256(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 cvt_u64x8_f32x8(u64x8_arg a_)
	{
		return _mm512_cvtepu64_ps(a_);
	}
#pragma endregion

#pragma region COMPARISONS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 cmpeq_f32x8(EmuSIMD::f32x8_arg lhs_, EmuSIMD::f32x8_arg rhs_)
	{
		return _mm256_cmp_ps(lhs_, rhs_, EMU_SIMD_CMP_EQ_FLAG);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 cmpneq_f32x8(EmuSIMD::f32x8_arg lhs_, EmuSIMD::f32x8_arg rhs_)
	{
		return _mm256_cmp_ps(lhs_, rhs_, EMU_SIMD_CMP_NEQ_FLAG);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 cmpgt_f32x8(EmuSIMD::f32x8_arg lhs_, EmuSIMD::f32x8_arg rhs_)
	{
		return _mm256_cmp_ps(lhs_, rhs_, EMU_SIMD_CMP_GT_FLAG);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 cmplt_f32x8(EmuSIMD::f32x8_arg lhs_, EmuSIMD::f32x8_arg rhs_)
	{
		return _mm256_cmp_ps(lhs_, rhs_, EMU_SIMD_CMP_LT_FLAG);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 cmpge_f32x8(EmuSIMD::f32x8_arg lhs_, EmuSIMD::f32x8_arg rhs_)
	{
		return _mm256_cmp_ps(lhs_, rhs_, EMU_SIMD_CMP_GE_FLAG);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 cmple_f32x8(EmuSIMD::f32x8_arg lhs_, EmuSIMD::f32x8_arg rhs_)
	{
		return _mm256_cmp_ps(lhs_, rhs_, EMU_SIMD_CMP_LE_FLAG);
	}
#pragma endregion

#pragma region BASIC_ARITHMETIC
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 mul_all_f32x8(EmuSIMD::f32x8_arg lhs_, EmuSIMD::f32x8_arg rhs_)
	{
		return _mm256_mul_ps(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 negate_f32x8(EmuSIMD::f32x8_arg to_negate_)
	{
		return _mm256_sub_ps(_mm256_setzero_ps(), to_negate_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 add_f32x8(EmuSIMD::f32x8_arg lhs_, EmuSIMD::f32x8_arg rhs_)
	{
		return _mm256_add_ps(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 sub_f32x8(EmuSIMD::f32x8_arg lhs_, EmuSIMD::f32x8_arg rhs_)
	{
		return _mm256_sub_ps(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 mul_f32x8(EmuSIMD::f32x8_arg lhs_, EmuSIMD::f32x8_arg rhs_)
	{
		return _mm256_mul_ps(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 div_f32x8(EmuSIMD::f32x8_arg lhs_, EmuSIMD::f32x8_arg rhs_)
	{
		return _mm256_div_ps(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 addsub_f32x8(EmuSIMD::f32x8_arg lhs_, EmuSIMD::f32x8_arg rhs_)
	{
		return _mm256_addsub_ps(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 fmadd_f32x8(EmuSIMD::f32x8_arg a_, EmuSIMD::f32x8_arg b_, EmuSIMD::f32x8_arg c_)
	{
		return _mm256_fmadd_ps(a_, b_, c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 fmsub_f32x8(EmuSIMD::f32x8_arg a_, EmuSIMD::f32x8_arg b_, EmuSIMD::f32x8_arg c_)
	{
		return _mm256_fmsub_ps(a_, b_, c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 fnmadd_f32x8(EmuSIMD::f32x8_arg a_, EmuSIMD::f32x8_arg b_, EmuSIMD::f32x8_arg c_)
	{
		return _mm256_fnmadd_ps(a_, b_, c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 fnmsub_f32x8(EmuSIMD::f32x8_arg a_, EmuSIMD::f32x8_arg b_, EmuSIMD::f32x8_arg c_)
	{
		return _mm256_fnmsub_ps(a_, b_, c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 fmaddsub_f32x8(EmuSIMD::f32x8_arg a_, EmuSIMD::f32x8_arg b_, EmuSIMD::f32x8_arg c_)
	{
		return _mm256_fmaddsub_ps(a_, b_, c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 fmsubadd_f32x8(EmuSIMD::f32x8_arg a_, EmuSIMD::f32x8_arg b_, EmuSIMD::f32x8_arg c_)
	{
		return _mm256_fmsubadd_ps(a_, b_, c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 floor_f32x8(EmuSIMD::f32x8_arg to_floor_)
	{
		return _mm256_floor_ps(to_floor_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 ceil_f32x8(EmuSIMD::f32x8_arg to_ceil_)
	{
		return _mm256_ceil_ps(to_ceil_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 trunc_f32x8(EmuSIMD::f32x8_arg to_trunc_)
	{
		return _mm256_trunc_ps(to_trunc_);
	}

	template<int RoundingFlag_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 round_f32x8(EmuSIMD::f32x8_arg to_round_)
	{
		return _mm256_round_ps(to_round_, RoundingFlag_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 mod_f32x8(EmuSIMD::f32x8_arg lhs_, EmuSIMD::f32x8_arg rhs_)
	{
		EmuSIMD::f32x8 res = _mm256_div_ps(lhs_, rhs_);
		res = _mm256_trunc_ps(res);
		return _mm256_fnmadd_ps(res, rhs_, lhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 abs_f32x8(EmuSIMD::f32x8_arg in_)
	{
		EmuSIMD::f32x8 negative_mask = cmplt_f32x8(in_, setzero_f32x8());
		EmuSIMD::f32x8 out = _mm256_and_ps(negative_mask, mul_all_f32x8(in_, set1_f32x8(-1)));
		return _mm256_or_ps(out, _mm256_andnot_ps(negative_mask, in_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 sqrt_f32x8(EmuSIMD::f32x8_arg in_)
	{
		return _mm256_sqrt_ps(in_);
	}
#pragma endregion
}

#endif
