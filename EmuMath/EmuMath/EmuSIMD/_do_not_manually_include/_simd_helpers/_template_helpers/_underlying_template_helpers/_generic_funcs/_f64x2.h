#ifndef EMU_SIMD_GENERIC_FUNCS_F64X2_H_INC_
#define EMU_SIMD_GENERIC_FUNCS_F64X2_H_INC_ 1

#include "_common_generic_func_helpers.h"
#include "_f32x4.h"

namespace EmuSIMD::Funcs
{
#pragma region SETTERS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 set_f64x2(double e0, double e1)
	{
		return _mm_set_pd(e0, e1);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 setr_f64x2(double e0, double e1)
	{
		//return _mm_setr_pd(e0, e1);
		return _mm_set_pd(e1, e0);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 set1_f64x2(double all_)
	{
		return _mm_set1_pd(all_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 load_f64x2(const double* p_to_load_)
	{
		return _mm_load_pd(p_to_load_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 setzero_f64x2()
	{
		return _mm_setzero_pd();
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 setmasked_f64x2(std::uint8_t bit_mask_)
	{
		constexpr std::int64_t element_mask = static_cast<std::int64_t>(0xFFFFFFFFFFFFFFFF);
		return _mm_castsi128_pd
		(
			_mm_set_epi64x
			(
				(bit_mask_ & 0x01) * element_mask,
				((bit_mask_ & 0x02) >> 1) * element_mask
			)
		);
	}
#pragma endregion

#pragma region STORES
	EMU_SIMD_COMMON_FUNC_SPEC void store_f64x2(double* p_out_, f64x2_arg a_)
	{
		_mm_store_pd(p_out_, a_);
	}
#pragma endregion

#pragma region CASTS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cast_f32x4_f64x2(f32x4_arg a_)
	{
		return _mm_castps_pd(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cast_f32x8_f64x2(f32x8_arg a_)
	{
		return _mm256_castpd256_pd128(_mm256_castps_pd(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cast_f32x16_f64x2(f32x16_arg a_)
	{
		return _mm512_castpd512_pd128(_mm512_castps_pd(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cast_f64x2_f64x2(f64x2_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cast_f64x4_f64x2(f64x4_arg a_)
	{
		return _mm256_castpd256_pd128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cast_f64x8_f64x2(f64x8_arg a_)
	{
		return _mm512_castpd512_pd128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cast_i8x16_f64x2(i8x16_arg a_)
	{
		return _mm_castsi128_pd(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cast_i16x8_f64x2(i16x8_arg a_)
	{
		return _mm_castsi128_pd(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cast_i32x4_f64x2(i32x4_arg a_)
	{
		return _mm_castsi128_pd(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cast_i64x2_f64x2(i64x2_arg a_)
	{
		return _mm_castsi128_pd(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cast_i8x32_f64x2(i8x32_arg a_)
	{
		return _mm256_castpd256_pd128(_mm256_castsi256_pd(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cast_i16x16_f64x2(i16x16_arg a_)
	{
		return _mm256_castpd256_pd128(_mm256_castsi256_pd(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cast_i32x8_f64x2(i32x8_arg a_)
	{
		return _mm256_castpd256_pd128(_mm256_castsi256_pd(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cast_i64x4_f64x2(i64x4_arg a_)
	{
		return _mm256_castpd256_pd128(_mm256_castsi256_pd(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cast_i8x64_f64x2(i8x64_arg a_)
	{
		return _mm512_castpd512_pd128(_mm512_castsi512_pd(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cast_i16x32_f64x2(i16x32_arg a_)
	{
		return _mm512_castpd512_pd128(_mm512_castsi512_pd(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cast_i32x16_f64x2(i32x16_arg a_)
	{
		return _mm512_castpd512_pd128(_mm512_castsi512_pd(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cast_i64x8_f64x2(i64x8_arg a_)
	{
		return _mm512_castpd512_pd128(_mm512_castsi512_pd(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cast_u8x16_f64x2(u8x16_arg a_)
	{
		return _mm_castsi128_pd(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cast_u16x8_f64x2(u16x8_arg a_)
	{
		return _mm_castsi128_pd(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cast_u32x4_f64x2(u32x4_arg a_)
	{
		return _mm_castsi128_pd(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cast_u64x2_f64x2(u64x2_arg a_)
	{
		return _mm_castsi128_pd(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cast_u8x32_f64x2(u8x32_arg a_)
	{
		return _mm256_castpd256_pd128(_mm256_castsi256_pd(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cast_u16x16_f64x2(u16x16_arg a_)
	{
		return _mm256_castpd256_pd128(_mm256_castsi256_pd(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cast_u32x8_f64x2(u32x8_arg a_)
	{
		return _mm256_castpd256_pd128(_mm256_castsi256_pd(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cast_u64x4_f64x2(u64x4_arg a_)
	{
		return _mm256_castpd256_pd128(_mm256_castsi256_pd(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cast_u8x64_f64x2(u8x64_arg a_)
	{
		return _mm512_castpd512_pd128(_mm512_castsi512_pd(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cast_u16x32_f64x2(u16x32_arg a_)
	{
		return _mm512_castpd512_pd128(_mm512_castsi512_pd(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cast_u32x16_f64x2(u32x16_arg a_)
	{
		return _mm512_castpd512_pd128(_mm512_castsi512_pd(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cast_u64x8_f64x2(u64x8_arg a_)
	{
		return _mm512_castpd512_pd128(_mm512_castsi512_pd(a_));
	}
#pragma endregion

#pragma region CONVERSIONS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cvt_f32x4_f64x2(f32x4_arg a_)
	{
		return _mm_cvtps_pd(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cvt_f32x8_f64x2(f32x8_arg a_)
	{
		return _mm_cvtps_pd(_mm256_castps256_ps128(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cvt_f32x16_f64x2(f32x16_arg a_)
	{
		return _mm_cvtps_pd(_mm512_castps512_ps128(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cvt_f64x2_f64x2(f64x2_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cvt_f64x4_f64x2(f64x4_arg a_)
	{
		return _mm256_castpd256_pd128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cvt_f64x8_f64x2(f64x8_arg a_)
	{
		return _mm512_castpd512_pd128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cvt_i8x16_f64x2(i8x16_arg a_)
	{
		return _mm_cvtepi64_pd(_mm_cvtepi8_epi64(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cvt_i16x8_f64x2(i16x8_arg a_)
	{
		return _mm_cvtepi64_pd(_mm_cvtepi16_epi64(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cvt_i32x4_f64x2(i32x4_arg a_)
	{
		return _mm_cvtepi32_pd(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cvt_i64x2_f64x2(i64x2_arg a_)
	{
		return _mm_cvtepi64_pd(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cvt_i8x32_f64x2(i8x32_arg a_)
	{
		return _mm_cvtepi64_pd(_mm_cvtepi8_epi64(_mm256_castsi256_si128(a_)));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cvt_i16x16_f64x2(i16x16_arg a_)
	{
		return _mm_cvtepi64_pd(_mm_cvtepi16_epi64(_mm256_castsi256_si128(a_)));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cvt_i32x8_f64x2(i32x8_arg a_)
	{
		return _mm_cvtepi32_pd(_mm256_castsi256_si128(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cvt_i64x4_f64x2(i64x4_arg a_)
	{
		return _mm_cvtepi64_pd(_mm256_castsi256_si128(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cvt_i8x64_f64x2(i8x64_arg a_)
	{
		return _mm_cvtepi64_pd(_mm_cvtepi8_epi64(_mm512_castsi512_si128(a_)));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cvt_i16x32_f64x2(i16x32_arg a_)
	{
		return _mm_cvtepi64_pd(_mm_cvtepi16_epi64(_mm512_castsi512_si128(a_)));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cvt_i32x16_f64x2(i32x16_arg a_)
	{
		return _mm_cvtepi32_pd(_mm512_castsi512_si128(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cvt_i64x8_f64x2(i64x8_arg a_)
	{
		return _mm_cvtepi64_pd(_mm512_castsi512_si128(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cvt_u8x16_f64x2(u8x16_arg a_)
	{
		return _mm_cvtepi64_pd(_mm_cvtepu8_epi64(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cvt_u16x8_f64x2(u16x8_arg a_)
	{
		return _mm_cvtepi64_pd(_mm_cvtepu16_epi64(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cvt_u32x4_f64x2(u32x4_arg a_)
	{
		return _mm_cvtepu32_pd(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cvt_u64x2_f64x2(u64x2_arg a_)
	{
		return _mm_cvtepu64_pd(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cvt_u8x32_f64x2(u8x32_arg a_)
	{
		return _mm_cvtepi64_pd(_mm_cvtepu8_epi64(_mm256_castsi256_si128(a_)));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cvt_u16x16_f64x2(u16x16_arg a_)
	{
		return _mm_cvtepi64_pd(_mm_cvtepu16_epi64(_mm256_castsi256_si128(a_)));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cvt_u32x8_f64x2(u32x8_arg a_)
	{
		return _mm_cvtepu32_pd(_mm256_castsi256_si128(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cvt_u64x4_f64x2(u64x4_arg a_)
	{
		return _mm_cvtepu64_pd(_mm256_castsi256_si128(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cvt_u8x64_f64x2(u8x64_arg a_)
	{
		return _mm_cvtepi64_pd(_mm_cvtepu8_epi64(_mm512_castsi512_si128(a_)));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cvt_u16x32_f64x2(u16x32_arg a_)
	{
		return _mm_cvtepi64_pd(_mm_cvtepu16_epi64(_mm512_castsi512_si128(a_)));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cvt_u32x16_f64x2(u32x16_arg a_)
	{
		return _mm_cvtepu32_pd(_mm512_castsi512_si128(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cvt_u64x8_f64x2(u64x8_arg a_)
	{
		return _mm_cvtepu64_pd(_mm512_castsi512_si128(a_));
	}
#pragma endregion

#pragma region COMPARISONS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cmpeq_f64x2(EmuSIMD::f64x2_arg lhs_, EmuSIMD::f64x2_arg rhs_)
	{
		return _mm_cmpeq_pd(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cmpneq_f64x2(EmuSIMD::f64x2_arg lhs_, EmuSIMD::f64x2_arg rhs_)
	{
		return _mm_cmpneq_pd(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cmpgt_f64x2(EmuSIMD::f64x2_arg lhs_, EmuSIMD::f64x2_arg rhs_)
	{
		return _mm_cmpgt_pd(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cmplt_f64x2(EmuSIMD::f64x2_arg lhs_, EmuSIMD::f64x2_arg rhs_)
	{
		return _mm_cmplt_pd(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cmpge_f64x2(EmuSIMD::f64x2_arg lhs_, EmuSIMD::f64x2_arg rhs_)
	{
		return _mm_cmpge_pd(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cmple_f64x2(EmuSIMD::f64x2_arg lhs_, EmuSIMD::f64x2_arg rhs_)
	{
		return _mm_cmple_pd(lhs_, rhs_);
	}
#pragma endregion

#pragma region BLENDS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 blendv_f64x2(EmuSIMD::f64x2_arg a_, EmuSIMD::f64x2_arg b_, EmuSIMD::f64x2_arg shuffle_mask_vec_)
	{
		return _mm_blendv_pd(a_, b_, shuffle_mask_vec_);
	}

	template<EmuSIMD::Funcs::blend_mask_type BlendMask>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 blend_f64x2(EmuSIMD::f64x2_arg a_, EmuSIMD::f64x2_arg b_)
	{
		return _mm_blend_pd(a_, b_, BlendMask);
	}
#pragma endregion

#pragma region MOVES
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 movehl_f64x2(EmuSIMD::f64x2_arg lhs_, EmuSIMD::f64x2_arg rhs_)
	{
		return cast_f32x4_f64x2(movehl_f32x4(cast_f64x2_f32x4(lhs_), cast_f64x2_f32x4(rhs_)));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 movelh_f64x2(EmuSIMD::f64x2_arg lhs_, EmuSIMD::f64x2_arg rhs_)
	{
		return cast_f32x4_f64x2(movelh_f32x4(cast_f64x2_f32x4(lhs_), cast_f64x2_f32x4(rhs_)));
	}
#pragma endregion

#pragma region SHUFFLES
	template<EmuSIMD::Funcs::shuffle_mask_type ShuffleMask>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 shuffle_f64x2(EmuSIMD::f64x2_arg lhs_, EmuSIMD::f64x2_arg rhs_)
	{
		return _mm_shuffle_pd(lhs_, rhs_, ShuffleMask);
	}

	template<EmuSIMD::Funcs::shuffle_mask_type ShuffleMask>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 permute_f64x2(EmuSIMD::f64x2_arg in_)
	{
		return _mm_permute_pd(in_, ShuffleMask);
	}
#pragma endregion

#pragma region BITWISE_ARITHMETIC
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 and_f64x2(EmuSIMD::f64x2_arg lhs_, EmuSIMD::f64x2_arg rhs_)
	{
		return _mm_and_pd(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 or_f64x2(EmuSIMD::f64x2_arg lhs_, EmuSIMD::f64x2_arg rhs_)
	{
		return _mm_or_pd(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 xor_f64x2(EmuSIMD::f64x2_arg lhs_, EmuSIMD::f64x2_arg rhs_)
	{
		return _mm_xor_pd(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 andnot_f64x2(EmuSIMD::f64x2_arg not_lhs_, EmuSIMD::f64x2_arg rhs_)
	{
		return _mm_andnot_pd(not_lhs_, rhs_);
	}
#pragma endregion

#pragma region MINMAX_FUNCS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 min_f64x2(EmuSIMD::f64x2_arg a_, EmuSIMD::f64x2_arg b_)
	{
		return _mm_min_pd(a_, b_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 max_f64x2(EmuSIMD::f64x2_arg a_, EmuSIMD::f64x2_arg b_)
	{
		return _mm_max_pd(a_, b_);
	}
#pragma endregion

#pragma region BASIC_ARITHMETIC
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 mul_all_f64x2(EmuSIMD::f64x2_arg lhs_, EmuSIMD::f64x2_arg rhs_)
	{
		return _mm_mul_pd(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 negate_f64x2(EmuSIMD::f64x2_arg to_negate_)
	{
		return _mm_sub_pd(_mm_setzero_pd(), to_negate_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 add_f64x2(EmuSIMD::f64x2_arg lhs_, EmuSIMD::f64x2_arg rhs_)
	{
		return _mm_add_pd(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 sub_f64x2(EmuSIMD::f64x2_arg lhs_, EmuSIMD::f64x2_arg rhs_)
	{
		return _mm_sub_pd(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 mul_f64x2(EmuSIMD::f64x2_arg lhs_, EmuSIMD::f64x2_arg rhs_)
	{
		return _mm_mul_pd(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 div_f64x2(EmuSIMD::f64x2_arg lhs_, EmuSIMD::f64x2_arg rhs_)
	{
		return _mm_div_pd(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 addsub_f64x2(EmuSIMD::f64x2_arg lhs_, EmuSIMD::f64x2_arg rhs_)
	{
		return _mm_addsub_pd(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 fmadd_f64x2(EmuSIMD::f64x2_arg a_, EmuSIMD::f64x2_arg b_, EmuSIMD::f64x2_arg c_)
	{
		return _mm_fmadd_pd(a_, b_, c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 fmsub_f64x2(EmuSIMD::f64x2_arg a_, EmuSIMD::f64x2_arg b_, EmuSIMD::f64x2_arg c_)
	{
		return _mm_fmsub_pd(a_, b_, c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 fnmadd_f64x2(EmuSIMD::f64x2_arg a_, EmuSIMD::f64x2_arg b_, EmuSIMD::f64x2_arg c_)
	{
		return _mm_fnmadd_pd(a_, b_, c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 fnmsub_f64x2(EmuSIMD::f64x2_arg a_, EmuSIMD::f64x2_arg b_, EmuSIMD::f64x2_arg c_)
	{
		return _mm_fnmsub_pd(a_, b_, c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 fmaddsub_f64x2(EmuSIMD::f64x2_arg a_, EmuSIMD::f64x2_arg b_, EmuSIMD::f64x2_arg c_)
	{
		return _mm_fmaddsub_pd(a_, b_, c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 fmsubadd_f64x2(EmuSIMD::f64x2_arg a_, EmuSIMD::f64x2_arg b_, EmuSIMD::f64x2_arg c_)
	{
		return _mm_fmsubadd_pd(a_, b_, c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 floor_f64x2(EmuSIMD::f64x2_arg to_floor_)
	{
		return _mm_floor_pd(to_floor_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 ceil_f64x2(EmuSIMD::f64x2_arg to_ceil_)
	{
		return _mm_ceil_pd(to_ceil_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 trunc_f64x2(EmuSIMD::f64x2_arg to_trunc_)
	{
		return _mm_round_pd(to_trunc_, EMU_SIMD_FLAG_TRUNC);
	}

	template<int RoundingFlag_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 round_f64x2(EmuSIMD::f64x2_arg to_round_)
	{
		return _mm_round_pd(to_round_, RoundingFlag_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 mod_f64x2(EmuSIMD::f64x2_arg lhs_, EmuSIMD::f64x2_arg rhs_)
	{
		EmuSIMD::f64x2 res = div_f64x2(lhs_, rhs_);
		res = trunc_f64x2(res);
		return _mm_fnmadd_pd(res, rhs_, lhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 abs_f64x2(EmuSIMD::f64x2_arg in_)
	{
		EmuSIMD::f64x2 negative_mask = cmplt_f64x2(in_, setzero_f64x2());
		EmuSIMD::f64x2 out = _mm_and_pd(negative_mask, mul_all_f64x2(in_, set1_f64x2(-1)));
		return _mm_or_pd(out, _mm_andnot_pd(negative_mask, in_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2_arg sqrt_f64x2(EmuSIMD::f64x2_arg in_)
	{
		return _mm_sqrt_pd(in_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 rsqrt_f64x2(EmuSIMD::f64x2_arg in_)
	{
		return div_f64x2(set1_f64x2(1.0), sqrt_f64x2(in_));
	}
#pragma endregion

#pragma region NEAR_COMPARISONS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cmpnear_f64x2(EmuSIMD::f64x2_arg lhs_, EmuSIMD::f64x2_arg rhs_, EmuSIMD::f64x2_arg epsilon = set1_f64x2(EmuCore::epsilon<double>::get()))
	{
		return cmple_f64x2(abs_f64x2(sub_f64x2(lhs_, rhs_)), epsilon);
	}
#pragma endregion

#pragma region TRIG
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cos_f64x2(EmuSIMD::f64x2_arg in_)
	{
		#if EMU_CORE_IS_INTEL_COMPILER && EMU_CORE_X86_X64 // Only tends to score better on Intel platforms
		return _mm_cos_pd(in_);
		#else
		// Alternative manual approximation, based on https://developer.download.nvidia.com/cg/cos.html implementation
		
		// Store constants used > once in registers to allow shuffling them instead of multiple sets of the same
		EmuSIMD::f64x2 one_c4z = setr_f64x2(1.0, -1.0);

		// Prepare for power series
		EmuSIMD::f64x2 r1x = mul_f64x2(set1_f64x2(0.159154943091), in_); // r1.x = c1.w * in_;

		EmuSIMD::f64x2 r1y = trunc_f64x2(r1x); // r1.y = frac(r1.x)
		r1y = sub_f64x2(r1x, r1y);

		EmuSIMD::f64x2 const0 = set1_f64x2(0.25f);
		EmuSIMD::f64x2 r2x = cmplt_f64x2(r1x, const0); // r2.x = r1.x < c1.x

		const0 = permute_f64x2<make_shuffle_mask_64<0, 0>()>(one_c4z);
		r2x = and_f64x2(r2x, const0);

		EmuSIMD::f64x2 r2y = cmpge_f64x2(r1y, set1_f64x2(-9.0)); // r2.yz = r1.yy >= c1.yz
		EmuSIMD::f64x2 r2z = cmpge_f64x2(r1y, set1_f64x2(0.75));
		r2y = and_f64x2(r2y, const0);
		r2z = and_f64x2(r2z, const0);

		EmuSIMD::f64x2 const1 = permute_f64x2<make_shuffle_mask_64<1, 1>()>(one_c4z);
		r2y = fmadd_f64x2(r2x, const1, fmadd_f64x2(r2y, const0, mul_f64x2(r2z, const1))); // dot(r2, c4.zwz)

		EmuSIMD::f64x2 r0x = negate_f64x2(r1y);
		EmuSIMD::f64x2 r0y = sub_f64x2(set1_f64x2(0.5), r1y);
		EmuSIMD::f64x2 r0z = sub_f64x2(const0, r1y);
		r0x = mul_f64x2(r0x, r0x);
		r0y = mul_f64x2(r0y, r0y);
		r0z = mul_f64x2(r0z, r0z);

		// Begin power series
		// --- Power 1
		const0 = set1_f64x2(-60.1458091736);
		const1 = set1_f64x2(24.9808039603);
		r1x = fmadd_f64x2(const1, r0x, const0);
		r1y = fmadd_f64x2(set1_f64x2(-24.9808039603), r0y, set1_f64x2(60.1458091736));
		EmuSIMD::f64x2 r1z = fmadd_f64x2(const1, r0z, const0);

		// --- Power 2
		const0 = set1_f64x2(85.4537887573f);
		r1x = fmadd_f64x2(r1x, r0x, const0);
		r1y = fmadd_f64x2(r1y, r0y, set1_f64x2(-85.4537887573));
		r1z = fmadd_f64x2(r1z, r0z, const0);

		// --- Power 3
		const0 = set1_f64x2(-64.9393539429f);
		r1x = fmadd_f64x2(r1x, r0x, const0);
		r1y = fmadd_f64x2(r1y, r0y, set1_f64x2(64.9393539429));
		r1z = fmadd_f64x2(r1z, r0z, const0);

		// --- Power 4
		const0 = set1_f64x2(19.7392082214f);
		r1x = fmadd_f64x2(r1x, r0x, const0);
		r1y = fmadd_f64x2(r1y, r0y, set1_f64x2(-19.7392082214));
		r1z = fmadd_f64x2(r1z, r0z, const0);

		// --- Power 5
		const0 = permute_f64x2<make_shuffle_mask_64<0, 0>()>(one_c4z);
		const1 = permute_f64x2<make_shuffle_mask_64<1, 1>()>(one_c4z);
		r1x = fmadd_f64x2(r1x, r0x, const1);
		r1y = fmadd_f64x2(r1y, r0y, const0);
		r1z = fmadd_f64x2(r1z, r0z, const1);

		// Final dot
		r2x = negate_f64x2(r2x);
		r2y = negate_f64x2(r2y);
		r2z = negate_f64x2(r2z);

		return fmadd_f64x2(r1x, r2x, fmadd_f64x2(r1y, r2y, mul_f64x2(r1z, r2z)));
		#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 sin_f64x2(EmuSIMD::f64x2_arg in_)
	{
#if EMU_CORE_IS_INTEL_COMPILER && EMU_CORE_X86_X64 // Only tends to score better on Intel platforms
		return _mm_sin_pd(in_);
#else
		// Alternative manual approximation, based on https://developer.download.nvidia.com/cg/sin.html implementation

		// Store constants used > once in registers to allow shuffling to them
		EmuSIMD::f64x2 one_c4z = setr_f64x2(1.0, -1.0);

		// Prepare for power series
		EmuSIMD::f64x2 const0 = set1_f64x2(0.25);
		EmuSIMD::f64x2 r1x = fmsub_f64x2(set1_f64x2(0.159154943091), in_, const0); // r1.x = c1.w * in_ - c1.x

		EmuSIMD::f64x2 r1y = trunc_f64x2(r1x); // r1.y = frac(r1.x)
		r1y = sub_f64x2(r1x, r1y);

		EmuSIMD::f64x2 r2x = cmplt_f64x2(r1x, const0); // r2.x = r1.x < c1.x

		const0 = permute_f64x2<make_shuffle_mask_64<0, 0>()>(one_c4z);
		r2x = and_f64x2(r2x, const0);

		EmuSIMD::f64x2 r2y = cmpge_f64x2(r1y, set1_f64x2(-9.0)); // r2.yz = r1.yy >= c1.yz
		EmuSIMD::f64x2 r2z = cmpge_f64x2(r1y, set1_f64x2(0.75));
		r2y = and_f64x2(r2y, const0);
		r2z = and_f64x2(r2z, const0);

		EmuSIMD::f64x2 const1 = permute_f64x2<make_shuffle_mask_64<1, 1>()>(one_c4z);
		r2y = fmadd_f64x2(r2x, const1, fmadd_f64x2(r2y, const0, mul_f64x2(r2z, const1))); // dot(r2, c4.zwz)

		EmuSIMD::f64x2 r0x = negate_f64x2(r1y);
		EmuSIMD::f64x2 r0y = sub_f64x2(set1_f64x2(0.5), r1y);
		EmuSIMD::f64x2 r0z = sub_f64x2(const0, r1y);
		r0x = mul_f64x2(r0x, r0x);
		r0y = mul_f64x2(r0y, r0y);
		r0z = mul_f64x2(r0z, r0z);

		// Begin power series
		// --- Power 1
		const0 = set1_f64x2(-60.1458091736);
		const1 = set1_f64x2(24.9808039603);
		r1x = fmadd_f64x2(const1, r0x, const0);
		r1y = fmadd_f64x2(set1_f64x2(-24.9808039603), r0y, set1_f64x2(60.1458091736));
		EmuSIMD::f64x2 r1z = fmadd_f64x2(const1, r0z, const0);

		// --- Power 2
		const0 = set1_f64x2(85.4537887573);
		r1x = fmadd_f64x2(r1x, r0x, const0);
		r1y = fmadd_f64x2(r1y, r0y, set1_f64x2(-85.4537887573));
		r1z = fmadd_f64x2(r1z, r0z, const0);

		// --- Power 3
		const0 = set1_f64x2(-64.9393539429);
		r1x = fmadd_f64x2(r1x, r0x, const0);
		r1y = fmadd_f64x2(r1y, r0y, set1_f64x2(64.9393539429));
		r1z = fmadd_f64x2(r1z, r0z, const0);

		// --- Power 4
		const0 = set1_f64x2(19.7392082214);
		r1x = fmadd_f64x2(r1x, r0x, const0);
		r1y = fmadd_f64x2(r1y, r0y, set1_f64x2(-19.7392082214));
		r1z = fmadd_f64x2(r1z, r0z, const0);

		// --- Power 5
		const0 = permute_f64x2<make_shuffle_mask_64<0, 0>()>(one_c4z);
		const1 = permute_f64x2<make_shuffle_mask_64<1, 1>()>(one_c4z);
		r1x = fmadd_f64x2(r1x, r0x, const1);
		r1y = fmadd_f64x2(r1y, r0y, const0);
		r1z = fmadd_f64x2(r1z, r0z, const1);

		// Final dot
		r2x = negate_f64x2(r2x);
		r2y = negate_f64x2(r2y);
		r2z = negate_f64x2(r2z);

		return fmadd_f64x2(r1x, r2x, fmadd_f64x2(r1y, r2y, mul_f64x2(r1z, r2z)));
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 tan_f64x2(EmuSIMD::f64x2_arg in_)
	{
#if 0 && (EMU_CORE_IS_INTEL_COMPILER || EMU_CORE_IS_MSVC) && EMU_CORE_X86_X64 // Better on both Intel and AMD x86/x64 builds, so use where available
		return _mm_tan_pd(in_);
#else
		// Alternative manual approximation using sin/cos, based on https://developer.download.nvidia.com/cg/sin.html & https://developer.download.nvidia.com/cg/cos.html impl.
		// --- Made as a unique function instead of deferring to separate cos and sin to minimise required operations

		// Store constants used > once in registers to allow shuffling to them
		EmuSIMD::f64x2 one_c4z = setr_f64x2(1.0, -1.0);

		// Prepare for power series
		EmuSIMD::f64x2 const0 = set1_f64x2(0.25);
		EmuSIMD::f64x2 r1x_cos = mul_f64x2(set1_f64x2(0.159154943091), in_);
		EmuSIMD::f64x2 r1x_sin = sub_f64x2(r1x_cos, const0); // r1.x = c1.w * in_ - c1.x

		EmuSIMD::f64x2 r1y_sin = trunc_f64x2(r1x_sin); // r1.y = frac(r1.x)
		r1y_sin = sub_f64x2(r1x_sin, r1y_sin);
		EmuSIMD::f64x2 r1y_cos = trunc_f64x2(r1x_sin);
		r1y_cos = sub_f64x2(r1x_cos, r1y_cos);

		EmuSIMD::f64x2 r2x_sin = cmplt_f64x2(r1x_sin, const0); // r2.x = r1.x < c1.x
		EmuSIMD::f64x2 r2x_cos = cmplt_f64x2(r1x_cos, const0);

		const0 = permute_f64x2<make_shuffle_mask_64<0, 0>()>(one_c4z);
		r2x_sin = and_f64x2(r2x_sin, const0);
		r2x_cos = and_f64x2(r2x_cos, const0);

		EmuSIMD::f64x2 const1 = set1_f64x2(-9.0);
		EmuSIMD::f64x2 const2 = set1_f64x2(0.75);
		EmuSIMD::f64x2 r2y_sin = cmpge_f64x2(r1y_sin, const1); // r2.yz = r1.yy >= c1.yz
		EmuSIMD::f64x2 r2z_sin = cmpge_f64x2(r1y_sin, const2);
		r2y_sin = and_f64x2(r2y_sin, const0);
		r2z_sin = and_f64x2(r2z_sin, const0);
		EmuSIMD::f64x2 r2y_cos = cmpge_f64x2(r1y_cos, const1);
		EmuSIMD::f64x2 r2z_cos = cmpge_f64x2(r1y_cos, const2);
		r2y_cos = and_f64x2(r2y_cos, const0);
		r2z_cos = and_f64x2(r2z_cos, const0);

		const1 = permute_f64x2<make_shuffle_mask_64<1, 1>()>(one_c4z);
		r2y_sin = fmadd_f64x2(r2x_sin, const1, fmadd_f64x2(r2y_sin, const0, mul_f64x2(r2z_sin, const1))); // dot(r2, c4.zwz)
		r2y_cos = fmadd_f64x2(r2x_cos, const1, fmadd_f64x2(r2y_cos, const0, mul_f64x2(r2z_cos, const1)));

		const1 = set1_f64x2(0.5);
		EmuSIMD::f64x2 r0x_sin = negate_f64x2(r1y_sin);
		EmuSIMD::f64x2 r0y_sin = sub_f64x2(const1, r1y_sin);
		EmuSIMD::f64x2 r0z_sin = sub_f64x2(const0, r1y_sin);
		r0x_sin = mul_f64x2(r0x_sin, r0x_sin);
		r0y_sin = mul_f64x2(r0y_sin, r0y_sin);
		r0z_sin = mul_f64x2(r0z_sin, r0z_sin);
		EmuSIMD::f64x2 r0x_cos = negate_f64x2(r1y_cos);
		EmuSIMD::f64x2 r0y_cos = sub_f64x2(const1, r1y_cos);
		EmuSIMD::f64x2 r0z_cos = sub_f64x2(const0, r1y_cos);
		r0x_cos = mul_f64x2(r0x_cos, r0x_cos);
		r0y_cos = mul_f64x2(r0y_cos, r0y_cos);
		r0z_cos = mul_f64x2(r0z_cos, r0z_cos);

		// Begin power series
		// --- Power 1
		const0 = set1_f64x2(-60.1458091736);
		EmuSIMD::f64x2 const3 = negate_f64x2(const0);
		const1 = set1_f64x2(24.9808039603);
		const2 = negate_f64x2(const1);
		r1x_sin = fmadd_f64x2(const1, r0x_sin, const0);
		r1y_sin = fmadd_f64x2(const2, r0y_sin, const3);
		EmuSIMD::f64x2 r1z_sin = fmadd_f64x2(const1, r0z_sin, const0);
		r1x_cos = fmadd_f64x2(const1, r0x_cos, const0);
		r1y_cos = fmadd_f64x2(const2, r0y_cos, const3);
		EmuSIMD::f64x2 r1z_cos = fmadd_f64x2(const1, r0z_cos, const0);

		// --- Power 2
		const0 = set1_f64x2(85.4537887573);
		const1 = negate_f64x2(const0);
		r1x_sin = fmadd_f64x2(r1x_sin, r0x_sin, const0);
		r1y_sin = fmadd_f64x2(r1y_sin, r0y_sin, const1);
		r1z_sin = fmadd_f64x2(r1z_sin, r0z_sin, const0);
		r1x_cos = fmadd_f64x2(r1x_cos, r0x_cos, const0);
		r1y_cos = fmadd_f64x2(r1y_cos, r0y_cos, const1);
		r1z_cos = fmadd_f64x2(r1z_cos, r0z_cos, const0);

		// --- Power 3
		const0 = set1_f64x2(-64.9393539429);
		const1 = negate_f64x2(const0);
		r1x_sin = fmadd_f64x2(r1x_sin, r0x_sin, const0);
		r1y_sin = fmadd_f64x2(r1y_sin, r0y_sin, const1);
		r1z_sin = fmadd_f64x2(r1z_sin, r0z_sin, const0);
		r1x_cos = fmadd_f64x2(r1x_cos, r0x_cos, const0);
		r1y_cos = fmadd_f64x2(r1y_cos, r0y_cos, const1);
		r1z_cos = fmadd_f64x2(r1z_cos, r0z_cos, const0);

		// --- Power 4
		const0 = set1_f64x2(19.7392082214);
		const1 = negate_f64x2(const0);
		r1x_sin = fmadd_f64x2(r1x_sin, r0x_sin, const0);
		r1y_sin = fmadd_f64x2(r1y_sin, r0y_sin, const1);
		r1z_sin = fmadd_f64x2(r1z_sin, r0z_sin, const0);
		r1x_cos = fmadd_f64x2(r1x_cos, r0x_cos, const0);
		r1y_cos = fmadd_f64x2(r1y_cos, r0y_cos, const1);
		r1z_cos = fmadd_f64x2(r1z_cos, r0z_cos, const0);

		// --- Power 5
		const0 = permute_f64x2<make_shuffle_mask_64<0, 0>()>(one_c4z);
		const1 = permute_f64x2<make_shuffle_mask_64<1, 1>()>(one_c4z);
		r1x_sin = fmadd_f64x2(r1x_sin, r0x_sin, const1);
		r1y_sin = fmadd_f64x2(r1y_sin, r0y_sin, const0);
		r1z_sin = fmadd_f64x2(r1z_sin, r0z_sin, const1);
		r1x_cos = fmadd_f64x2(r1x_cos, r0x_cos, const1);
		r1y_cos = fmadd_f64x2(r1y_cos, r0y_cos, const0);
		r1z_cos = fmadd_f64x2(r1z_cos, r0z_cos, const1);

		// Final dot - store the sins in r2x
		r2x_sin = negate_f64x2(r2x_sin);
		r2y_sin = negate_f64x2(r2y_sin);
		r2z_sin = negate_f64x2(r2z_sin);
		r2x_sin = fmadd_f64x2(r1x_sin, r2x_sin, fmadd_f64x2(r1y_sin, r2y_sin, mul_f64x2(r1z_sin, r2z_sin)));
		r2x_cos = negate_f64x2(r2x_cos);
		r2y_cos = negate_f64x2(r2y_cos);
		r2z_cos = negate_f64x2(r2z_cos);
		r2x_cos = fmadd_f64x2(r1x_cos, r2x_cos, fmadd_f64x2(r1y_cos, r2y_cos, mul_f64x2(r1z_cos, r2z_cos)));

		return div_f64x2(r2x_sin, r2x_cos);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 acos_f64x2(EmuSIMD::f64x2_arg in_)
	{
#if EMU_CORE_IS_INTEL_COMPILER && EMU_CORE_X86_X64 // Only tends to score better on Intel platforms
		return _mm_acos_pd(in_);
#else
		// Alternative manual approximation, based on https://developer.download.nvidia.com/cg/acos.html implementation
		EmuSIMD::f64x2 in_abs = abs_f64x2(in_);
		EmuSIMD::f64x2 one = set1_f64x2(1.0);
		EmuSIMD::f64x2 negation_mult = cmple_f64x2(in_, setzero_f64x2());
		negation_mult = and_f64x2(one, negation_mult);

		EmuSIMD::f64x2 result = set1_f64x2(-0.0187293);
		result = fmadd_f64x2(result, in_abs, set1_f64x2(0.074261));
		result = fmsub_f64x2(result, in_abs, set1_f64x2(0.2121144));
		result = fmadd_f64x2(result, in_abs, set1_f64x2(1.5707288));
		result = mul_f64x2(result, sqrt_f64x2(sub_f64x2(one, in_abs)));

		EmuSIMD::f64x2 tmp = mul_f64x2(set1_f64x2(2.0), negation_mult);
		tmp = mul_f64x2(tmp, result);
		result = sub_f64x2(result, tmp);

		return fmadd_f64x2(negation_mult, set1_f64x2(3.14159265358979), result);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 asin_f64x2(EmuSIMD::f64x2_arg in_)
	{
#if EMU_CORE_IS_INTEL_COMPILER && EMU_CORE_X86_X64 // Only tends to score better on Intel platforms
		return _mm_asin_pd(in_);
#else
		// Alternative manual approximation, based on https://developer.download.nvidia.com/cg/asin.html implementation
		EmuSIMD::f64x2 in_abs = abs_f64x2(in_);
		EmuSIMD::f64x2 two = set1_f64x2(2.0);
		EmuSIMD::f64x2 negation_mult = cmplt_f64x2(in_, setzero_f64x2());
		negation_mult = and_f64x2(two, negation_mult);

		EmuSIMD::f64x2 result = set1_f64x2(-0.0187293);
		result = fmadd_f64x2(result, in_abs, set1_f64x2(0.074261));
		result = fmsub_f64x2(result, in_abs, set1_f64x2(0.2121144));
		result = fmadd_f64x2(result, in_abs, set1_f64x2(1.5707288));

		EmuSIMD::f64x2 tmp = sub_f64x2(set1_f64x2(1.0), in_abs);
		tmp = mul_f64x2(sqrt_f64x2(tmp), result);
		result = set1_f64x2(3.14159265358979 * 0.5);
		result = sub_f64x2(result, tmp);

		tmp = mul_f64x2(negation_mult, result);
		return sub_f64x2(result, tmp);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 atan2_f64x2(EmuSIMD::f64x2_arg y_, EmuSIMD::f64x2_arg x_)
	{
		#if EMU_CORE_IS_INTEL_COMPILER && EMU_CORE_X86_X64 // Only tends to score better on Intel platforms
		return _mm_atan2_pd(y_, x_);
		#else		
		// Alternative manual approximation, based on https://developer.download.nvidia.com/cg/atan2.html implementation

		auto abs_x = abs_f64x2(x_);
		auto abs_y = abs_f64x2(y_);
		
		EmuSIMD::f64x2 temp0 = max_f64x2(abs_x, abs_y);
		EmuSIMD::f64x2 temp1 = min_f64x2(abs_x, abs_y);
		EmuSIMD::f64x2 temp2 = div_f64x2(set1_f64x2(1.0), temp0);
		temp2 = mul_f64x2(temp1, temp2);

		EmuSIMD::f64x2 t4 = mul_f64x2(temp2, temp2);
		temp0 = set1_f64x2(-0.013480470);
		temp0 = fmadd_f64x2(temp0, t4, set1_f64x2(0.057477314));
		temp0 = fmsub_f64x2(temp0, t4, set1_f64x2(0.121239071));
		temp0 = fmadd_f64x2(temp0, t4, set1_f64x2(0.195635925));
		temp0 = fmsub_f64x2(temp0, t4, set1_f64x2(0.332994597));
		temp0 = fmadd_f64x2(temp0, t4, set1_f64x2(0.999995630));
		temp2 = mul_f64x2(temp0, temp2);

		//t3 = (abs(y) > abs(x)) ? float(1.570796327) - t3 : t3;
		EmuSIMD::f64x2 cmp_mask = cmpgt_f64x2(abs_y, abs_x);
		temp0 = and_f64x2(cmp_mask, set1_f64x2(1.570796327));
		temp0 = sub_f64x2(temp0, temp2);
		temp2 = or_f64x2(andnot_f64x2(cmp_mask, temp2), and_f64x2(cmp_mask, temp0));

		// t3 = (x < 0) ?  float(3.141592654) - t3 : t3;
		EmuSIMD::f64x2 zero = setzero_f64x2();
		cmp_mask = cmplt_f64x2(x_, zero);
		temp0 = and_f64x2(cmp_mask, set1_f64x2(3.141592654));
		temp0 = sub_f64x2(temp0, temp2);
		temp2 = or_f64x2(andnot_f64x2(cmp_mask, temp2), and_f64x2(cmp_mask, temp0));

		//t3 = (y < 0) ? -t3 : t3;
		cmp_mask = cmplt_f64x2(y_, zero);
		temp0 = negate_f64x2(temp2);
		temp2 = or_f64x2(andnot_f64x2(cmp_mask, temp2), and_f64x2(cmp_mask, temp0));

		return temp2;
		#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 atan_f64x2(EmuSIMD::f64x2_arg in_)
	{
#if EMU_CORE_IS_INTEL_COMPILER && EMU_CORE_X86_X64 // Only tends to score better on Intel platforms
		return _mm_atan_pd(in_);
#else
		// Alternative manual approximation, based on https://developer.download.nvidia.com/cg/atan2.html implementation with a constant x_ argument of 1
		EmuSIMD::f64x2 one = set1_f64x2(1.0);
		EmuSIMD::f64x2 abs_y = abs_f64x2(in_);

		//auto temp0 = _mm_max_ps(temp2, temp1);
		EmuSIMD::f64x2 cmp_mask = cmplt_f64x2(abs_y, one);
		EmuSIMD::f64x2 temp0 = or_f64x2(and_f64x2(cmp_mask, one), andnot_f64x2(cmp_mask, abs_y));
		EmuSIMD::f64x2 temp1 = or_f64x2(andnot_f64x2(cmp_mask, one), and_f64x2(cmp_mask, abs_y));
		EmuSIMD::f64x2 temp2 = div_f64x2(one, temp0);
		temp2 = mul_f64x2(temp1, temp2);

		EmuSIMD::f64x2 t4 = mul_f64x2(temp2, temp2);
		temp0 = set1_f64x2(-0.013480470);
		temp0 = fmadd_f64x2(temp0, t4, set1_f64x2(0.057477314));
		temp0 = fmsub_f64x2(temp0, t4, set1_f64x2(0.121239071));
		temp0 = fmadd_f64x2(temp0, t4, set1_f64x2(0.195635925));
		temp0 = fmsub_f64x2(temp0, t4, set1_f64x2(0.332994597));
		temp0 = fmadd_f64x2(temp0, t4, set1_f64x2(0.999995630));
		temp2 = mul_f64x2(temp0, temp2);

		//t3 = (abs(y) > abs(x)) ? float(1.570796327) - t3 : t3;
		cmp_mask = cmpgt_f64x2(abs_y, one);
		temp0 = and_f64x2(cmp_mask, set1_f64x2(1.570796327));
		temp0 = sub_f64x2(temp0, temp2);
		temp2 = or_f64x2(andnot_f64x2(cmp_mask, temp2), and_f64x2(cmp_mask, temp0));

		//t3 = (y < 0) ? -t3 : t3;
		cmp_mask = cmplt_f64x2(in_, setzero_f64x2());
		temp0 = negate_f64x2(temp2);
		temp2 = or_f64x2(andnot_f64x2(cmp_mask, temp2), and_f64x2(cmp_mask, temp0));

		return temp2;
#endif
	}
#pragma endregion
}

#endif
