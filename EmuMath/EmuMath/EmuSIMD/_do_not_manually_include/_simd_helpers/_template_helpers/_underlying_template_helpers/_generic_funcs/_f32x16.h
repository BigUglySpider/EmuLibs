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

#pragma region SHUFFLES
	template<shuffle_mask_type ShuffleMask>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 shuffle_f32x16(EmuSIMD::f32x16_arg lhs_, EmuSIMD::f32x16_arg rhs_)
	{
		return _mm512_shuffle_ps(lhs_, rhs_, ShuffleMask);
	}

	template<shuffle_mask_type ShuffleMask>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 permute_f32x16(EmuSIMD::f32x16_arg in_)
	{
		return _mm512_permute_ps(in_, ShuffleMask);
	}
#pragma endregion

#pragma region BITWISE_ARITHMETIC
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 and_f32x16(EmuSIMD::f32x16_arg lhs_, EmuSIMD::f32x16_arg rhs_)
	{
		return _mm512_and_ps(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 or_f32x16(EmuSIMD::f32x16_arg lhs_, EmuSIMD::f32x16_arg rhs_)
	{
		return _mm512_or_ps(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 xor_f32x16(EmuSIMD::f32x16_arg lhs_, EmuSIMD::f32x16_arg rhs_)
	{
		return _mm512_xor_ps(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 andnot_f32x16(EmuSIMD::f32x16_arg not_lhs_, EmuSIMD::f32x16_arg rhs_)
	{
		return _mm512_andnot_ps(not_lhs_, rhs_);
	}
#pragma endregion

#pragma region MINMAX_FUNCS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 min_f32x16(EmuSIMD::f32x16_arg a_, EmuSIMD::f32x16_arg b_)
	{
		return _mm512_min_ps(a_, b_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 max_f32x16(EmuSIMD::f32x16_arg a_, EmuSIMD::f32x16_arg b_)
	{
		return _mm512_max_ps(a_, b_);
	}
#pragma endregion

#pragma region BASIC_ARITHMETIC
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 mul_all_f32x16(EmuSIMD::f32x16_arg lhs_, EmuSIMD::f32x16_arg rhs_)
	{
		return _mm512_mul_ps(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 add_f32x16(EmuSIMD::f32x16_arg lhs_, EmuSIMD::f32x16_arg rhs_)
	{
		return _mm512_add_ps(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 sub_f32x16(EmuSIMD::f32x16_arg lhs_, EmuSIMD::f32x16_arg rhs_)
	{
		return _mm512_sub_ps(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 negate_f32x16(EmuSIMD::f32x16_arg to_negate_)
	{
		return sub_f32x16(setzero_f32x16(), to_negate_);
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
		EmuSIMD::f32x16 res = div_f32x16(lhs_, rhs_);
		res = trunc_f32x16(res);
		return fmadd_f32x16(res, rhs_, lhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 abs_f32x16(EmuSIMD::f32x16_arg in_)
	{
		EmuSIMD::f32x16 negative_mask = cmplt_f32x16(in_, setzero_f32x16());
		EmuSIMD::f32x16 out = and_f32x16(negative_mask, mul_all_f32x16(in_, set1_f32x16(-1)));
		return or_f32x16(out, andnot_f32x16(negative_mask, in_));
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

#pragma region TRIG
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 cos_f32x16(EmuSIMD::f32x16_arg in_)
	{
		#if EMU_CORE_IS_INTEL_COMPILER && EMU_CORE_X86_X64 // Only tends to score better on Intel platforms
		return _mm256_cos_ps(in_);
		#else
		// Alternative manual approximation, based on https://developer.download.nvidia.com/cg/cos.html implementation

		// Store constants used > once in registers to allow shuffling to them
		EmuSIMD::f32x16 c1x_c2x_c3x_c4x = setr_f32x16
		(
			0.25f, 24.9808039603f, 85.4537887573f, 19.7392082214f,
			0.25f, 24.9808039603f, 85.4537887573f, 19.7392082214f,
			0.25f, 24.9808039603f, 85.4537887573f, 19.7392082214f,
			0.25f, 24.9808039603f, 85.4537887573f, 19.7392082214f
		);
		EmuSIMD::f32x16 one_c2z_c3z_c4z = setr_f32x16
		(
			1.0f, -60.1458091736f, -64.9393539429f, -1.0f,
			1.0f, -60.1458091736f, -64.9393539429f, -1.0f,
			1.0f, -60.1458091736f, -64.9393539429f, -1.0f,
			1.0f, -60.1458091736f, -64.9393539429f, -1.0f
		);

		// Prepare for power series
		EmuSIMD::f32x16 r1x = mul_f32x16(set1_f32x16(0.159154943091f), in_); // r1.x = c1.w * in_;

		EmuSIMD::f32x16 r1y = trunc_f32x16(r1x); // r1.y = frac(r1.x)
		r1y = sub_f32x16(r1x, r1y);

		EmuSIMD::f32x16 const0 = permute_f32x16<make_shuffle_mask<0, 0, 0, 0>()>(c1x_c2x_c3x_c4x);
		EmuSIMD::f32x16 r2x = cmplt_f32x16(r1x, const0); // r2.x = r1.x < c1.x

		const0 = permute_f32x16<make_shuffle_mask<0, 0, 0, 0>()>(one_c2z_c3z_c4z);
		r2x = and_f32x16(r2x, const0);

		EmuSIMD::f32x16 r2y = cmpge_f32x16(r1y, set1_f32x16(-9.0f)); // r2.yz = r1.yy >= c1.yz
		EmuSIMD::f32x16 r2z = cmpge_f32x16(r1y, set1_f32x16(0.75f));
		r2y = and_f32x16(r2y, const0);
		r2z = and_f32x16(r2z, const0);

		EmuSIMD::f32x16 const1 = permute_f32x16<make_shuffle_mask<3, 3, 3, 3>()>(one_c2z_c3z_c4z);
		r2y = fmadd_f32x16(r2x, const1, fmadd_f32x16(r2y, const0, mul_f32x16(r2z, const1))); // dot(r2, c4.zwz)

		EmuSIMD::f32x16 r0x = negate_f32x16(r1y);
		EmuSIMD::f32x16 r0y = sub_f32x16(set1_f32x16(0.5f), r1y);
		EmuSIMD::f32x16 r0z = sub_f32x16(const0, r1y);
		r0x = mul_f32x16(r0x, r0x);
		r0y = mul_f32x16(r0y, r0y);
		r0z = mul_f32x16(r0z, r0z);

		// Begin power series
		// --- Power 1
		const0 = permute_f32x16<make_shuffle_mask<1, 1, 1, 1>()>(one_c2z_c3z_c4z);
		const1 = permute_f32x16<make_shuffle_mask<1, 1, 1, 1>()>(c1x_c2x_c3x_c4x);
		r1x = fmadd_f32x16(const1, r0x, const0);
		r1y = fmadd_f32x16(set1_f32x16(-24.9808039603f), r0y, set1_f32x16(60.1458091736f));
		EmuSIMD::f32x16 r1z = fmadd_f32x16(const1, r0z, const0);

		// --- Power 2
		const0 = permute_f32x16<make_shuffle_mask<2, 2, 2, 2>()>(c1x_c2x_c3x_c4x);
		r1x = fmadd_f32x16(r1x, r0x, const0);
		r1y = fmadd_f32x16(r1y, r0y, set1_f32x16(-85.4537887573f));
		r1z = fmadd_f32x16(r1z, r0z, const0);

		// --- Power 3
		const0 = permute_f32x16<make_shuffle_mask<2, 2, 2, 2>()>(one_c2z_c3z_c4z);
		r1x = fmadd_f32x16(r1x, r0x, const0);
		r1y = fmadd_f32x16(r1y, r0y, set1_f32x16(64.9393539429f));
		r1z = fmadd_f32x16(r1z, r0z, const0);

		// --- Power 4
		const0 = permute_f32x16<make_shuffle_mask<3, 3, 3, 3>()>(c1x_c2x_c3x_c4x);
		r1x = fmadd_f32x16(r1x, r0x, const0);
		r1y = fmadd_f32x16(r1y, r0y, set1_f32x16(-19.7392082214f));
		r1z = fmadd_f32x16(r1z, r0z, const0);

		// --- Power 5
		const0 = permute_f32x16<make_shuffle_mask<0, 0, 0, 0>()>(one_c2z_c3z_c4z);
		const1 = permute_f32x16<make_shuffle_mask<3, 3, 3, 3>()>(one_c2z_c3z_c4z);
		r1x = fmadd_f32x16(r1x, r0x, const1);
		r1y = fmadd_f32x16(r1y, r0y, const0);
		r1z = fmadd_f32x16(r1z, r0z, const1);

		// Final dot
		r2x = negate_f32x16(r2x);
		r2y = negate_f32x16(r2y);
		r2z = negate_f32x16(r2z);

		return fmadd_f32x16(r1x, r2x, fmadd_f32x16(r1y, r2y, mul_f32x16(r1z, r2z)));
		#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 sin_f32x16(EmuSIMD::f32x16_arg in_)
	{
		#if EMU_CORE_IS_INTEL_COMPILER && EMU_CORE_X86_X64 // Only tends to score better on Intel platforms
		return _mm256_sin_ps(in_);
		#else
		// Alternative manual approximation, based on https://developer.download.nvidia.com/cg/sin.html implementation
		
		// Store constants used > once in registers to allow shuffling to them
		EmuSIMD::f32x16 c1x_c2x_c3x_c4x = setr_f32x16
		(
			0.25f, 24.9808039603f, 85.4537887573f, 19.7392082214f,
			0.25f, 24.9808039603f, 85.4537887573f, 19.7392082214f,
			0.25f, 24.9808039603f, 85.4537887573f, 19.7392082214f,
			0.25f, 24.9808039603f, 85.4537887573f, 19.7392082214f
		);
		EmuSIMD::f32x16 one_c2z_c3z_c4z = setr_f32x16
		(
			1.0f, -60.1458091736f, -64.9393539429f, -1.0f,
			1.0f, -60.1458091736f, -64.9393539429f, -1.0f,
			1.0f, -60.1458091736f, -64.9393539429f, -1.0f,
			1.0f, -60.1458091736f, -64.9393539429f, -1.0f
		);

		// Prepare for power series
		EmuSIMD::f32x16 const0 = permute_f32x16<make_shuffle_mask<0, 0, 0, 0>()>(c1x_c2x_c3x_c4x);
		EmuSIMD::f32x16 r1x = fmsub_f32x16(set1_f32x16(0.159154943091f), in_, const0); // r1.x = c1.w * in_ - c1.x

		EmuSIMD::f32x16 r1y = trunc_f32x16(r1x); // r1.y = frac(r1.x)
		r1y = sub_f32x16(r1x, r1y);

		EmuSIMD::f32x16 r2x = cmplt_f32x16(r1x, const0); // r2.x = r1.x < c1.x

		const0 = permute_f32x16<make_shuffle_mask<0, 0, 0, 0>()>(one_c2z_c3z_c4z);
		r2x = and_f32x16(r2x, const0);

		EmuSIMD::f32x16 r2y = cmpge_f32x16(r1y, set1_f32x16(-9.0f)); // r2.yz = r1.yy >= c1.yz
		EmuSIMD::f32x16 r2z = cmpge_f32x16(r1y, set1_f32x16(0.75f));
		r2y = and_f32x16(r2y, const0);
		r2z = and_f32x16(r2z, const0);

		EmuSIMD::f32x16 const1 = permute_f32x16<make_shuffle_mask<3, 3, 3, 3>()>(one_c2z_c3z_c4z);
		r2y = fmadd_f32x16(r2x, const1, fmadd_f32x16(r2y, const0, mul_f32x16(r2z, const1))); // dot(r2, c4.zwz)

		EmuSIMD::f32x16 r0x = negate_f32x16(r1y);
		EmuSIMD::f32x16 r0y = sub_f32x16(set1_f32x16(0.5f), r1y);
		EmuSIMD::f32x16 r0z = sub_f32x16(const0, r1y);
		r0x = mul_f32x16(r0x, r0x);
		r0y = mul_f32x16(r0y, r0y);
		r0z = mul_f32x16(r0z, r0z);

		// Begin power series
		// --- Power 1
		const0 = permute_f32x16<make_shuffle_mask<1, 1, 1, 1>()>(one_c2z_c3z_c4z);
		const1 = permute_f32x16<make_shuffle_mask<1, 1, 1, 1>()>(c1x_c2x_c3x_c4x);
		r1x = fmadd_f32x16(const1, r0x, const0);
		r1y = fmadd_f32x16(set1_f32x16(-24.9808039603f), r0y, set1_f32x16(60.1458091736f));
		EmuSIMD::f32x16 r1z = fmadd_f32x16(const1, r0z, const0);

		// --- Power 2
		const0 = permute_f32x16<make_shuffle_mask<2, 2, 2, 2>()>(c1x_c2x_c3x_c4x);
		r1x = fmadd_f32x16(r1x, r0x, const0);
		r1y = fmadd_f32x16(r1y, r0y, set1_f32x16(-85.4537887573f));
		r1z = fmadd_f32x16(r1z, r0z, const0);

		// --- Power 3
		const0 = permute_f32x16<make_shuffle_mask<2, 2, 2, 2>()>(one_c2z_c3z_c4z);
		r1x = fmadd_f32x16(r1x, r0x, const0);
		r1y = fmadd_f32x16(r1y, r0y, set1_f32x16(64.9393539429f));
		r1z = fmadd_f32x16(r1z, r0z, const0);

		// --- Power 4
		const0 = permute_f32x16<make_shuffle_mask<3, 3, 3, 3>()>(c1x_c2x_c3x_c4x);
		r1x = fmadd_f32x16(r1x, r0x, const0);
		r1y = fmadd_f32x16(r1y, r0y, set1_f32x16(-19.7392082214f));
		r1z = fmadd_f32x16(r1z, r0z, const0);

		// --- Power 5
		const0 = permute_f32x16<make_shuffle_mask<0, 0, 0, 0>()>(one_c2z_c3z_c4z);
		const1 = permute_f32x16<make_shuffle_mask<3, 3, 3, 3>()>(one_c2z_c3z_c4z);
		r1x = fmadd_f32x16(r1x, r0x, const1);
		r1y = fmadd_f32x16(r1y, r0y, const0);
		r1z = fmadd_f32x16(r1z, r0z, const1);

		// Final dot
		r2x = negate_f32x16(r2x);
		r2y = negate_f32x16(r2y);
		r2z = negate_f32x16(r2z);

		return fmadd_f32x16(r1x, r2x, fmadd_f32x16(r1y, r2y, mul_f32x16(r1z, r2z)));
		#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 tan_f32x16(EmuSIMD::f32x16_arg in_)
	{
		#if 0 && (EMU_CORE_IS_INTEL_COMPILER || EMU_CORE_IS_MSVC) && EMU_CORE_X86_X64 // Better on both Intel and AMD x86/x64 builds, so use where available
		return _mm512_tan_ps(in_);
		#else
		// Alternative manual approximation using sin/cos, based on https://developer.download.nvidia.com/cg/sin.html & https://developer.download.nvidia.com/cg/cos.html impl.
		// --- Made as a unique function instead of deferring to separate cos and sin to minimise required operations
		
		// Store constants used > once in registers to allow shuffling to them
		EmuSIMD::f32x16 c1x_c2x_c3x_c4x = setr_f32x16
		(
			0.25f, 24.9808039603f, 85.4537887573f, 19.7392082214f,
			0.25f, 24.9808039603f, 85.4537887573f, 19.7392082214f,
			0.25f, 24.9808039603f, 85.4537887573f, 19.7392082214f,
			0.25f, 24.9808039603f, 85.4537887573f, 19.7392082214f
		);
		EmuSIMD::f32x16 one_c2z_c3z_c4z = setr_f32x16
		(
			1.0f, -60.1458091736f, -64.9393539429f, -1.0f,
			1.0f, -60.1458091736f, -64.9393539429f, -1.0f,
			1.0f, -60.1458091736f, -64.9393539429f, -1.0f,
			1.0f, -60.1458091736f, -64.9393539429f, -1.0f
		);

		// Prepare for power series
		EmuSIMD::f32x16 const0 = permute_f32x16<make_shuffle_mask<0, 0, 0, 0>()>(c1x_c2x_c3x_c4x);
		EmuSIMD::f32x16 r1x_cos = mul_f32x16(set1_f32x16(0.159154943091f), in_);
		EmuSIMD::f32x16 r1x_sin = sub_f32x16(r1x_cos, const0); // r1.x = c1.w * in_ - c1.x

		EmuSIMD::f32x16 r1y_sin = trunc_f32x16(r1x_sin); // r1.y = frac(r1.x)
		r1y_sin = sub_f32x16(r1x_sin, r1y_sin);
		EmuSIMD::f32x16 r1y_cos = trunc_f32x16(r1x_sin);
		r1y_cos = sub_f32x16(r1x_cos, r1y_cos);

		EmuSIMD::f32x16 r2x_sin = cmplt_f32x16(r1x_sin, const0); // r2.x = r1.x < c1.x
		EmuSIMD::f32x16 r2x_cos = cmplt_f32x16(r1x_cos, const0);

		const0 = permute_f32x16<make_shuffle_mask<0, 0, 0, 0>()>(one_c2z_c3z_c4z);
		r2x_sin = and_f32x16(r2x_sin, const0);
		r2x_cos = and_f32x16(r2x_cos, const0);

		EmuSIMD::f32x16 r2y_sin = cmpge_f32x16(r1y_sin, set1_f32x16(-9.0f)); // r2.yz = r1.yy >= c1.yz
		EmuSIMD::f32x16 r2z_sin = cmpge_f32x16(r1y_sin, set1_f32x16(0.75f));
		r2y_sin = and_f32x16(r2y_sin, const0);
		r2z_sin = and_f32x16(r2z_sin, const0);
		EmuSIMD::f32x16 r2y_cos = cmpge_f32x16(r1y_cos, set1_f32x16(-9.0f));
		EmuSIMD::f32x16 r2z_cos = cmpge_f32x16(r1y_cos, set1_f32x16(0.75f));
		r2y_cos = and_f32x16(r2y_cos, const0);
		r2z_cos = and_f32x16(r2z_cos, const0);

		EmuSIMD::f32x16 const1 = permute_f32x16<make_shuffle_mask<3, 3, 3, 3>()>(one_c2z_c3z_c4z);
		r2y_sin = fmadd_f32x16(r2x_sin, const1, fmadd_f32x16(r2y_sin, const0, mul_f32x16(r2z_sin, const1))); // dot(r2, c4.zwz)
		r2y_cos = fmadd_f32x16(r2x_cos, const1, fmadd_f32x16(r2y_cos, const0, mul_f32x16(r2z_cos, const1)));

		EmuSIMD::f32x16 r0x_sin = negate_f32x16(r1y_sin);
		EmuSIMD::f32x16 r0y_sin = sub_f32x16(set1_f32x16(0.5f), r1y_sin);
		EmuSIMD::f32x16 r0z_sin = sub_f32x16(const0, r1y_sin);
		r0x_sin = mul_f32x16(r0x_sin, r0x_sin);
		r0y_sin = mul_f32x16(r0y_sin, r0y_sin);
		r0z_sin = mul_f32x16(r0z_sin, r0z_sin);
		EmuSIMD::f32x16 r0x_cos = negate_f32x16(r1y_cos);
		EmuSIMD::f32x16 r0y_cos = sub_f32x16(set1_f32x16(0.5f), r1y_cos);
		EmuSIMD::f32x16 r0z_cos = sub_f32x16(const0, r1y_cos);
		r0x_cos = mul_f32x16(r0x_cos, r0x_cos);
		r0y_cos = mul_f32x16(r0y_cos, r0y_cos);
		r0z_cos = mul_f32x16(r0z_cos, r0z_cos);

		// Begin power series
		// --- Power 1
		const0 = permute_f32x16<make_shuffle_mask<1, 1, 1, 1>()>(one_c2z_c3z_c4z);
		const1 = permute_f32x16<make_shuffle_mask<1, 1, 1, 1>()>(c1x_c2x_c3x_c4x);
		r1x_sin = fmadd_f32x16(const1, r0x_sin, const0);
		r1y_sin = fmadd_f32x16(set1_f32x16(-24.9808039603f), r0y_sin, set1_f32x16(60.1458091736f));
		EmuSIMD::f32x16 r1z_sin = fmadd_f32x16(const1, r0z_sin, const0);
		r1x_cos = fmadd_f32x16(const1, r0x_cos, const0);
		r1y_cos = fmadd_f32x16(set1_f32x16(-24.9808039603f), r0y_cos, set1_f32x16(60.1458091736f));
		EmuSIMD::f32x16 r1z_cos = fmadd_f32x16(const1, r0z_cos, const0);

		// --- Power 2
		const0 = permute_f32x16<make_shuffle_mask<2, 2, 2, 2>()>(c1x_c2x_c3x_c4x);
		const1 = set1_f32x16(-85.4537887573f);
		r1x_sin = fmadd_f32x16(r1x_sin, r0x_sin, const0);
		r1y_sin = fmadd_f32x16(r1y_sin, r0y_sin, const1);
		r1z_sin = fmadd_f32x16(r1z_sin, r0z_sin, const0);
		r1x_cos = fmadd_f32x16(r1x_cos, r0x_cos, const0);
		r1y_cos = fmadd_f32x16(r1y_cos, r0y_cos, const1);
		r1z_cos = fmadd_f32x16(r1z_cos, r0z_cos, const0);

		// --- Power 3
		const0 = permute_f32x16<make_shuffle_mask<2, 2, 2, 2>()>(one_c2z_c3z_c4z);
		const1 = set1_f32x16(64.9393539429f);
		r1x_sin = fmadd_f32x16(r1x_sin, r0x_sin, const0);
		r1y_sin = fmadd_f32x16(r1y_sin, r0y_sin, const1);
		r1z_sin = fmadd_f32x16(r1z_sin, r0z_sin, const0);
		r1x_cos = fmadd_f32x16(r1x_cos, r0x_cos, const0);
		r1y_cos = fmadd_f32x16(r1y_cos, r0y_cos, const1);
		r1z_cos = fmadd_f32x16(r1z_cos, r0z_cos, const0);

		// --- Power 4
		const0 = permute_f32x16<make_shuffle_mask<3, 3, 3, 3>()>(c1x_c2x_c3x_c4x);
		const1 = set1_f32x16(-19.7392082214f);
		r1x_sin = fmadd_f32x16(r1x_sin, r0x_sin, const0);
		r1y_sin = fmadd_f32x16(r1y_sin, r0y_sin, const1);
		r1z_sin = fmadd_f32x16(r1z_sin, r0z_sin, const0);
		r1x_cos = fmadd_f32x16(r1x_cos, r0x_cos, const0);
		r1y_cos = fmadd_f32x16(r1y_cos, r0y_cos, const1);
		r1z_cos = fmadd_f32x16(r1z_cos, r0z_cos, const0);

		// --- Power 5
		const0 = permute_f32x16<make_shuffle_mask<0, 0, 0, 0>()>(one_c2z_c3z_c4z);
		const1 = permute_f32x16<make_shuffle_mask<3, 3, 3, 3>()>(one_c2z_c3z_c4z);
		r1x_sin = fmadd_f32x16(r1x_sin, r0x_sin, const1);
		r1y_sin = fmadd_f32x16(r1y_sin, r0y_sin, const0);
		r1z_sin = fmadd_f32x16(r1z_sin, r0z_sin, const1);
		r1x_cos = fmadd_f32x16(r1x_cos, r0x_cos, const1);
		r1y_cos = fmadd_f32x16(r1y_cos, r0y_cos, const0);
		r1z_cos = fmadd_f32x16(r1z_cos, r0z_cos, const1);

		// Final dot - store the sins in r2x
		r2x_sin = negate_f32x16(r2x_sin);
		r2y_sin = negate_f32x16(r2y_sin);
		r2z_sin = negate_f32x16(r2z_sin);
		r2x_sin = fmadd_f32x16(r1x_sin, r2x_sin, fmadd_f32x16(r1y_sin, r2y_sin, mul_f32x16(r1z_sin, r2z_sin)));
		r2x_cos = negate_f32x16(r2x_cos);
		r2y_cos = negate_f32x16(r2y_cos);
		r2z_cos = negate_f32x16(r2z_cos);
		r2x_cos = fmadd_f32x16(r1x_cos, r2x_cos, fmadd_f32x16(r1y_cos, r2y_cos, mul_f32x16(r1z_cos, r2z_cos)));

		return div_f32x16(r2x_sin, r2x_cos);
		#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 acos_f32x16(EmuSIMD::f32x16_arg in_)
	{
		#if EMU_CORE_IS_INTEL_COMPILER && EMU_CORE_X86_X64 // Only tends to score better on Intel platforms
		return _mm256_acos_ps(in_);
		#else
		// Alternative manual approximation, based on https://developer.download.nvidia.com/cg/acos.html implementation
		EmuSIMD::f32x16 in_abs = abs_f32x16(in_);
		EmuSIMD::f32x16 one = set1_f32x16(1.0f);
		EmuSIMD::f32x16 negation_mult = cmple_f32x16(in_, setzero_f32x16());
		negation_mult = and_f32x16(one, negation_mult);

		EmuSIMD::f32x16 result = set1_f32x16(-0.0187293f);
		result = fmadd_f32x16(result, in_abs, set1_f32x16(0.074261f));
		result = fmsub_f32x16(result, in_abs, set1_f32x16(0.2121144f));
		result = fmadd_f32x16(result, in_abs, set1_f32x16(1.5707288f));
		result = mul_f32x16(result, sqrt_f32x16(sub_f32x16(one, in_abs)));

		EmuSIMD::f32x16 tmp = mul_f32x16(set1_f32x16(2.0f), negation_mult);
		tmp = mul_f32x16(tmp, result);
		result = sub_f32x16(result, tmp);

		return fmadd_f32x16(negation_mult, set1_f32x16(3.14159265358979f), result);
		#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 asin_f32x16(EmuSIMD::f32x16_arg in_)
	{
		#if EMU_CORE_IS_INTEL_COMPILER && EMU_CORE_X86_X64 // Only tends to score better on Intel platforms
		return _mm256_asin_ps(in_);
		#else
		// Alternative manual approximation, based on https://developer.download.nvidia.com/cg/asin.html implementation
		EmuSIMD::f32x16 in_abs = abs_f32x16(in_);
		EmuSIMD::f32x16 two = set1_f32x16(2.0f);
		EmuSIMD::f32x16 negation_mult = cmplt_f32x16(in_, setzero_f32x16());
		negation_mult = and_f32x16(two, negation_mult);

		EmuSIMD::f32x16 result = set1_f32x16(-0.0187293f);
		result = fmadd_f32x16(result, in_abs, set1_f32x16(0.074261f));
		result = fmsub_f32x16(result, in_abs, set1_f32x16(0.2121144f));
		result = fmadd_f32x16(result, in_abs, set1_f32x16(1.5707288f));

		EmuSIMD::f32x16 tmp = sub_f32x16(set1_f32x16(1.0f), in_abs);
		tmp = mul_f32x16(sqrt_f32x16(tmp), result);
		result = set1_f32x16(3.14159265358979f * 0.5f);
		result = sub_f32x16(result, tmp);

		tmp = mul_f32x16(negation_mult, result);
		return sub_f32x16(result, tmp);
		#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 atan2_f32x16(EmuSIMD::f32x16_arg y_, EmuSIMD::f32x16_arg x_)
	{
		#if EMU_CORE_IS_INTEL_COMPILER && EMU_CORE_X86_X64 // Only tends to score better on Intel platforms
		return _mm256_atan2_ps(y_, x_);
		#else		
		// Alternative manual approximation, based on https://developer.download.nvidia.com/cg/atan2.html implementation

		EmuSIMD::f32x16 abs_x = abs_f32x16(x_);
		EmuSIMD::f32x16 abs_y = abs_f32x16(y_);
		
		EmuSIMD::f32x16 temp0 = max_f32x16(abs_x, abs_y);
		EmuSIMD::f32x16 temp1 = min_f32x16(abs_x, abs_y);
		EmuSIMD::f32x16 temp2 = div_f32x16(set1_f32x16(1.0f), temp0);
		temp2 = mul_f32x16(temp1, temp2);

		EmuSIMD::f32x16 t4 = mul_f32x16(temp2, temp2);
		temp0 = set1_f32x16(-0.013480470f);
		temp0 = fmadd_f32x16(temp0, t4, set1_f32x16(0.057477314f));
		temp0 = fmsub_f32x16(temp0, t4, set1_f32x16(0.121239071f));
		temp0 = fmadd_f32x16(temp0, t4, set1_f32x16(0.195635925f));
		temp0 = fmsub_f32x16(temp0, t4, set1_f32x16(0.332994597f));
		temp0 = fmadd_f32x16(temp0, t4, set1_f32x16(0.999995630f));
		temp2 = mul_f32x16(temp0, temp2);

		//t3 = (abs(y) > abs(x)) ? float(1.570796327) - t3 : t3;
		EmuSIMD::f32x16 cmp_mask = cmpgt_f32x16(abs_y, abs_x);
		temp0 = and_f32x16(cmp_mask, set1_f32x16(1.570796327f));
		temp0 = sub_f32x16(temp0, temp2);
		temp2 = or_f32x16(andnot_f32x16(cmp_mask, temp2), and_f32x16(cmp_mask, temp0));

		// t3 = (x < 0) ?  float(3.141592654) - t3 : t3;
		EmuSIMD::f32x16 zero = setzero_f32x16();
		cmp_mask = cmplt_f32x16(x_, zero);
		temp0 = and_f32x16(cmp_mask, set1_f32x16(3.141592654f));
		temp0 = sub_f32x16(temp0, temp2);
		temp2 = or_f32x16(andnot_f32x16(cmp_mask, temp2), and_f32x16(cmp_mask, temp0));

		//t3 = (y < 0) ? -t3 : t3;
		cmp_mask = cmplt_f32x16(y_, zero);
		temp0 = negate_f32x16(temp2);
		temp2 = or_f32x16(andnot_f32x16(cmp_mask, temp2), and_f32x16(cmp_mask, temp0));

		return temp2;
		#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 atan_f32x16(EmuSIMD::f32x16_arg in_)
	{
		#if EMU_CORE_IS_INTEL_COMPILER && EMU_CORE_X86_X64 // Only tends to score better on Intel platforms
		return _mm256_atan_ps(in_);
		#else
		// Alternative manual approximation, based on https://developer.download.nvidia.com/cg/atan2.html implementation with a constant x_ argument of 1
		EmuSIMD::f32x16 one = set1_f32x16(1.0f);
		EmuSIMD::f32x16 abs_y = abs_f32x16(in_);

		//auto temp0 = _mm_max_ps(temp2, temp1);
		EmuSIMD::f32x16 cmp_mask = cmplt_f32x16(abs_y, one);
		EmuSIMD::f32x16 temp0 = or_f32x16(and_f32x16(cmp_mask, one), andnot_f32x16(cmp_mask, abs_y));
		EmuSIMD::f32x16 temp1 = or_f32x16(andnot_f32x16(cmp_mask, one), and_f32x16(cmp_mask, abs_y));
		EmuSIMD::f32x16 temp2 = div_f32x16(one, temp0);
		temp2 = mul_f32x16(temp1, temp2);

		EmuSIMD::f32x16 t4 = mul_f32x16(temp2, temp2);
		temp0 = set1_f32x16(-0.013480470f);
		temp0 = fmadd_f32x16(temp0, t4, set1_f32x16(0.057477314f));
		temp0 = fmsub_f32x16(temp0, t4, set1_f32x16(0.121239071f));
		temp0 = fmadd_f32x16(temp0, t4, set1_f32x16(0.195635925f));
		temp0 = fmsub_f32x16(temp0, t4, set1_f32x16(0.332994597f));
		temp0 = fmadd_f32x16(temp0, t4, set1_f32x16(0.999995630f));
		temp2 = mul_f32x16(temp0, temp2);

		//t3 = (abs(y) > abs(x)) ? float(1.570796327) - t3 : t3;
		cmp_mask = cmpgt_f32x16(abs_y, one);
		temp0 = and_f32x16(cmp_mask, set1_f32x16(1.570796327f));
		temp0 = sub_f32x16(temp0, temp2);
		temp2 = or_f32x16(andnot_f32x16(cmp_mask, temp2), and_f32x16(cmp_mask, temp0));

		//t3 = (y < 0) ? -t3 : t3;
		cmp_mask = cmplt_f32x16(in_, setzero_f32x16());
		temp0 = negate_f32x16(temp2);
		temp2 = or_f32x16(andnot_f32x16(cmp_mask, temp2), and_f32x16(cmp_mask, temp0));

		return temp2;
		#endif
	}
#pragma endregion
}

#endif
