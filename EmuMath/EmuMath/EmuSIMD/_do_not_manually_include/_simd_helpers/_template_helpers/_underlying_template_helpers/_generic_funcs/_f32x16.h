#ifndef EMU_SIMD_GENERIC_FUNCS_F32X16_H_INC_
#define EMU_SIMD_GENERIC_FUNCS_F32X16_H_INC_ 1

#include "_common_generic_func_helpers.h"

namespace EmuSIMD::Funcs
{
#pragma region SETTERS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 set_f32x16
	(
		float e0, float e1, float e2, float e3, float e4, float e5, float e6, float e7,
		float e8, float e9, float e10, float e11, float e12, float e13, float e14, float e15
	)
	{
		return _mm512_set_ps(e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 setr_f32x16
	(
		float e0, float e1, float e2, float e3, float e4, float e5, float e6, float e7,
		float e8, float e9, float e10, float e11, float e12, float e13, float e14, float e15
	)
	{
		return _mm512_set_ps(e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 set1_f32x16(float all_)
	{
		return _mm512_set1_ps(all_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 load_f32x16(const float* p_to_load_)
	{
		return _mm512_load_ps(p_to_load_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 setzero_f32x16()
	{
		return _mm512_setzero_ps();
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 setmasked_f32x16(std::uint16_t bit_mask_)
	{
		constexpr std::int32_t element_mask = static_cast<std::int32_t>(0xFFFFFFFF);
		return _mm512_castsi512_ps
		(
			_mm512_set_epi32
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
			)
		);
	}
#pragma endregion

#pragma region STORES
	EMU_SIMD_COMMON_FUNC_SPEC void store_f32x16(float* p_out_, f32x16_arg a_)
	{
		_mm512_store_ps(p_out_, a_);
	}
#pragma endregion

#pragma region CASTS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 cast_f32x4_f32x16(f32x4_arg a_)
	{
		return _mm512_castps128_ps512(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 cast_f32x8_f32x16(f32x8_arg a_)
	{
		return _mm512_castps256_ps512(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 cast_f32x16_f32x16(f32x16_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 cast_f64x2_f32x16(f64x2_arg a_)
	{
		return _mm512_castpd_ps(_mm512_castpd128_pd512(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 cast_f64x4_f32x16(f64x4_arg a_)
	{
		return _mm512_castpd_ps(_mm512_castpd256_pd512(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 cast_f64x8_f32x16(f64x8_arg a_)
	{
		return _mm512_castpd_ps(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 cast_i8x16_f32x16(i8x16_arg a_)
	{
		return _mm512_castsi512_ps(_mm512_castsi128_si512(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 cast_i16x8_f32x16(i16x8_arg a_)
	{
		return _mm512_castsi512_ps(_mm512_castsi128_si512(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 cast_i32x4_f32x16(i32x4_arg a_)
	{
		return _mm512_castsi512_ps(_mm512_castsi128_si512(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 cast_i64x2_f32x16(i64x2_arg a_)
	{
		return _mm512_castsi512_ps(_mm512_castsi128_si512(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 cast_i8x32_f32x16(i8x32_arg a_)
	{
		return _mm512_castsi512_ps(_mm512_castsi256_si512(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 cast_i16x16_f32x16(i16x16_arg a_)
	{
		return _mm512_castsi512_ps(_mm512_castsi256_si512(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 cast_i32x8_f32x16(i32x8_arg a_)
	{
		return _mm512_castsi512_ps(_mm512_castsi256_si512(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 cast_i64x4_f32x16(i64x4_arg a_)
	{
		return _mm512_castsi512_ps(_mm512_castsi256_si512(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 cast_i8x64_f32x16(i8x64_arg a_)
	{
		return _mm512_castsi512_ps(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 cast_i16x32_f32x16(i16x32_arg a_)
	{
		return _mm512_castsi512_ps(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 cast_i32x16_f32x16(i32x16_arg a_)
	{
		return _mm512_castsi512_ps(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 cast_i64x8_f32x16(i64x8_arg a_)
	{
		return _mm512_castsi512_ps(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 cast_u8x16_f32x16(u8x16_arg a_)
	{
		return _mm512_castsi512_ps(_mm512_castsi128_si512(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 cast_u16x8_f32x16(u16x8_arg a_)
	{
		return _mm512_castsi512_ps(_mm512_castsi128_si512(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 cast_u32x4_f32x16(u32x4_arg a_)
	{
		return _mm512_castsi512_ps(_mm512_castsi128_si512(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 cast_u64x2_f32x16(u64x2_arg a_)
	{
		return _mm512_castsi512_ps(_mm512_castsi128_si512(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 cast_u8x32_f32x16(u8x32_arg a_)
	{
		return _mm512_castsi512_ps(_mm512_castsi256_si512(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 cast_u16x16_f32x16(u16x16_arg a_)
	{
		return _mm512_castsi512_ps(_mm512_castsi256_si512(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 cast_u32x8_f32x16(u32x8_arg a_)
	{
		return _mm512_castsi512_ps(_mm512_castsi256_si512(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 cast_u64x4_f32x16(u64x4_arg a_)
	{
		return _mm512_castsi512_ps(_mm512_castsi256_si512(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 cast_u8x64_f32x16(u8x64_arg a_)
	{
		return _mm512_castsi512_ps(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 cast_u16x32_f32x16(u16x32_arg a_)
	{
		return _mm512_castsi512_ps(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 cast_u32x16_f32x16(u32x16_arg a_)
	{
		return _mm512_castsi512_ps(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 cast_u64x8_f32x16(u64x8_arg a_)
	{
		return _mm512_castsi512_ps(a_);
	}
#pragma endregion

#pragma region CONVERSIONS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 cvt_f32x4_f32x16(f32x4_arg a_)
	{
		return _mm512_castps128_ps512(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 cvt_f32x8_f32x16(f32x8_arg a_)
	{
		return _mm512_castps256_ps512(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 cvt_f32x16_f32x16(f32x16_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 cvt_f64x2_f32x16(f64x2_arg a_)
	{
		return _mm512_castps128_ps512(_mm_cvtpd_ps(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 cvt_f64x4_f32x16(f64x4_arg a_)
	{
		return _mm512_castps128_ps512(_mm256_cvtpd_ps(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 cvt_f64x8_f32x16(f64x8_arg a_)
	{
		return _mm512_castps256_ps512(_mm512_cvtpd_ps(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 cvt_i8x16_f32x16(i8x16_arg a_)
	{
		return _mm512_cvtepi32_ps(_mm512_cvtepi8_epi32(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 cvt_i16x8_f32x16(i16x8_arg a_)
	{
		return _mm512_castps256_ps512(_mm256_cvtepi32_ps(_mm256_cvtepi16_epi32(a_)));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 cvt_i32x4_f32x16(i32x4_arg a_)
	{
		return _mm512_castps128_ps512(_mm_cvtepi32_ps(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 cvt_i64x2_f32x16(i64x2_arg a_)
	{
		return _mm512_castps128_ps512(_mm_cvtepi64_ps(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 cvt_i8x32_f32x16(i8x32_arg a_)
	{
		return _mm512_cvtepi32_ps(_mm512_cvtepi8_epi32(_mm256_castsi256_si128(a_)));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 cvt_i16x16_f32x16(i16x16_arg a_)
	{
		return _mm512_cvtepi32_ps(_mm512_cvtepi16_epi32(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 cvt_i32x8_f32x16(i32x8_arg a_)
	{
		return _mm512_castps256_ps512(_mm256_cvtepi32_ps(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 cvt_i64x4_f32x16(i64x4_arg a_)
	{
		return _mm512_castps128_ps512(_mm256_cvtepi64_ps(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 cvt_i8x64_f32x16(i8x64_arg a_)
	{
		return _mm512_cvtepi32_ps(_mm512_cvtepi8_epi32(_mm512_castsi512_si128(a_)));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 cvt_i16x32_f32x16(i16x32_arg a_)
	{
		return _mm512_cvtepi32_ps(_mm512_cvtepi16_epi32(_mm512_castsi512_si256(a_)));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 cvt_i32x16_f32x16(i32x16_arg a_)
	{
		return _mm512_cvtepi32_ps(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 cvt_i64x8_f32x16(i64x8_arg a_)
	{
		return _mm512_castps256_ps512(_mm512_cvtepi64_ps(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 cvt_u8x16_f32x16(u8x16_arg a_)
	{
		return _mm512_cvtepi32_ps(_mm512_cvtepu8_epi32(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 cvt_u16x8_f32x16(u16x8_arg a_)
	{
		return _mm512_castps256_ps512(_mm256_cvtepu32_ps(_mm256_cvtepi16_epi32(a_)));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 cvt_u32x4_f32x16(u32x4_arg a_)
	{
		return _mm512_castps128_ps512(_mm_cvtepu32_ps(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 cvt_u64x2_f32x16(u64x2_arg a_)
	{
		return _mm512_castps128_ps512(_mm_cvtepu64_ps(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 cvt_u8x32_f32x16(u8x32_arg a_)
	{
		return _mm512_cvtepi32_ps(_mm512_cvtepu8_epi32(_mm256_castsi256_si128(a_)));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 cvt_u16x16_f32x16(u16x16_arg a_)
	{
		return _mm512_cvtepi32_ps(_mm512_cvtepu16_epi32(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 cvt_u32x8_f32x16(u32x8_arg a_)
	{
		return _mm512_castps256_ps512(_mm256_cvtepu32_ps(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 cvt_u64x4_f32x16(u64x4_arg a_)
	{
		return _mm512_castps128_ps512(_mm256_cvtepu64_ps(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 cvt_u8x64_f32x16(u8x64_arg a_)
	{
		return _mm512_cvtepi32_ps(_mm512_cvtepu8_epi32(_mm512_castsi512_si128(a_)));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 cvt_u16x32_f32x16(u16x32_arg a_)
	{
		return _mm512_cvtepi32_ps(_mm512_cvtepu16_epi32(_mm512_castsi512_si256(a_)));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 cvt_u32x16_f32x16(u32x16_arg a_)
	{
		return _mm512_cvtepu32_ps(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 cvt_u64x8_f32x16(u64x8_arg a_)
	{
		return _mm512_castps256_ps512(_mm512_cvtepu64_ps(a_));
	}
#pragma endregion

#pragma region COMPARISONS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 cmpeq_f32x16(EmuSIMD::f32x16_arg lhs_, EmuSIMD::f32x16_arg rhs_)
	{
		return setmasked_f32x16(_mm512_cmpeq_ps_mask(lhs_, rhs_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 cmpneq_f32x16(EmuSIMD::f32x16_arg lhs_, EmuSIMD::f32x16_arg rhs_)
	{
		return setmasked_f32x16(_mm512_cmpneq_ps_mask(lhs_, rhs_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 cmpgt_f32x16(EmuSIMD::f32x16_arg lhs_, EmuSIMD::f32x16_arg rhs_)
	{
		return setmasked_f32x16(_mm512_cmplt_ps_mask(rhs_, lhs_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 cmplt_f32x16(EmuSIMD::f32x16_arg lhs_, EmuSIMD::f32x16_arg rhs_)
	{
		return setmasked_f32x16(_mm512_cmplt_ps_mask(lhs_, rhs_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 cmpge_f32x16(EmuSIMD::f32x16_arg lhs_, EmuSIMD::f32x16_arg rhs_)
	{
		return setmasked_f32x16(_mm512_cmple_ps_mask(rhs_, lhs_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 cmple_f32x16(EmuSIMD::f32x16_arg lhs_, EmuSIMD::f32x16_arg rhs_)
	{
		return setmasked_f32x16(_mm512_cmple_ps_mask(lhs_, rhs_));
	}
#pragma endregion

#pragma region BASIC_ARITHMETIC
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 mul_all_f32x16(EmuSIMD::f32x16_arg lhs_, EmuSIMD::f32x16_arg rhs_)
	{
		return _mm512_mul_ps(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 negate_f32x16(EmuSIMD::f32x16_arg to_negate_)
	{
		return _mm512_sub_ps(_mm512_setzero_ps(), to_negate_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 add_f32x16(EmuSIMD::f32x16_arg lhs_, EmuSIMD::f32x16_arg rhs_)
	{
		return _mm512_add_ps(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 sub_f32x16(EmuSIMD::f32x16_arg lhs_, EmuSIMD::f32x16_arg rhs_)
	{
		return _mm512_sub_ps(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 mul_f32x16(EmuSIMD::f32x16_arg lhs_, EmuSIMD::f32x16_arg rhs_)
	{
		return _mm512_mul_ps(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 div_f32x16(EmuSIMD::f32x16_arg lhs_, EmuSIMD::f32x16_arg rhs_)
	{
		return _mm512_div_ps(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 addsub_f32x16(EmuSIMD::f32x16_arg lhs_, EmuSIMD::f32x16_arg rhs_)
	{
		return _mm512_fmaddsub_ps(_mm512_set1_ps(1.0f), lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 fmadd_f32x16(EmuSIMD::f32x16_arg a_, EmuSIMD::f32x16_arg b_, EmuSIMD::f32x16_arg c_)
	{
		return _mm512_fmadd_ps(a_, b_, c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 fmsub_f32x16(EmuSIMD::f32x16_arg a_, EmuSIMD::f32x16_arg b_, EmuSIMD::f32x16_arg c_)
	{
		return _mm512_fmsub_ps(a_, b_, c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 fnmadd_f32x16(EmuSIMD::f32x16_arg a_, EmuSIMD::f32x16_arg b_, EmuSIMD::f32x16_arg c_)
	{
		return _mm512_fnmadd_ps(a_, b_, c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 fnmsub_f32x16(EmuSIMD::f32x16_arg a_, EmuSIMD::f32x16_arg b_, EmuSIMD::f32x16_arg c_)
	{
		return _mm512_fnmsub_ps(a_, b_, c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 fmaddsub_f32x16(EmuSIMD::f32x16_arg a_, EmuSIMD::f32x16_arg b_, EmuSIMD::f32x16_arg c_)
	{
		return _mm512_fmaddsub_ps(a_, b_, c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 fmsubadd_f32x16(EmuSIMD::f32x16_arg a_, EmuSIMD::f32x16_arg b_, EmuSIMD::f32x16_arg c_)
	{
		return _mm512_fmsubadd_ps(a_, b_, c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 floor_f32x16(EmuSIMD::f32x16_arg to_floor_)
	{
		return _mm512_floor_ps(to_floor_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 ceil_f32x16(EmuSIMD::f32x16_arg to_ceil_)
	{
		return _mm512_ceil_ps(to_ceil_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 trunc_f32x16(EmuSIMD::f32x16_arg to_trunc_)
	{
		return _mm512_trunc_ps(to_trunc_);
	}

	template<int RoundingFlag_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 round_f32x16(EmuSIMD::f32x16_arg to_round_)
	{
		return _mm512_roundscale_ps(to_round_, RoundingFlag_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 mod_f32x16(EmuSIMD::f32x16_arg lhs_, EmuSIMD::f32x16_arg rhs_)
	{
		EmuSIMD::f32x16 res = _mm512_div_ps(lhs_, rhs_);
		res = _mm512_trunc_ps(res);
		return _mm512_fnmadd_ps(res, rhs_, lhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 abs_f32x16(EmuSIMD::f32x16_arg in_)
	{
		EmuSIMD::f32x16 negative_mask = cmplt_f32x16(in_, setzero_f32x16());
		EmuSIMD::f32x16 out = _mm512_and_ps(negative_mask, mul_all_f32x16(in_, set1_f32x16(-1)));
		return _mm512_or_ps(out, _mm512_andnot_ps(negative_mask, in_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 sqrt_f32x16(EmuSIMD::f32x16_arg in_)
	{
		return _mm512_sqrt_ps(in_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 rsqrt_f32x16(EmuSIMD::f32x16_arg in_)
	{
		return _mm512_rsqrt28_ps(in_);
	}
#pragma endregion

#pragma region NEAR_COMPARISONS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 cmpnear_f32x16(EmuSIMD::f32x16_arg lhs_, EmuSIMD::f32x16_arg rhs_, EmuSIMD::f32x16_arg epsilon = set1_f32x16(EmuCore::epsilon<float>::get()))
	{
		return cmple_f32x16(abs_f32x16(sub_f32x16(lhs_, rhs_)), epsilon);
	}
#pragma endregion
}

#endif
