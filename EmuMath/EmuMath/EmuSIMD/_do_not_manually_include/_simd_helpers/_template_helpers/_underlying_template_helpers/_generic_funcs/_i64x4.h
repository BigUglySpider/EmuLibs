#ifndef EMU_SIMD_GENERIC_FUNCS_I64X4_H_INC_
#define EMU_SIMD_GENERIC_FUNCS_I64X4_H_INC_ 1

#include "_common_generic_func_helpers.h"

namespace EmuSIMD::Funcs
{
#pragma region SETTERS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 set_i64x4(std::int64_t e0, std::int64_t e1, std::int64_t e2, std::int64_t e3)
	{
		return _mm256_set_epi64x(e3, e2, e1, e0);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 setr_i64x4(std::int64_t e0, std::int64_t e1, std::int64_t e2, std::int64_t e3)
	{
		return _mm256_set_epi64x(e3, e2, e1, e0);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 set1_i64x4(std::int64_t all_)
	{
		return _mm256_set1_epi64x(all_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 load_i64x4(const std::int64_t* p_to_load_)
	{
		return _mm256_load_si256(reinterpret_cast<const __m256i*>(p_to_load_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 setzero_i64x4()
	{
		return _mm256_setzero_si256();
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 setmasked_i64x4(std::uint8_t bit_mask_)
	{
		constexpr std::int64_t element_mask = static_cast<std::int64_t>(0xFFFFFFFFFFFFFFFF);
		return _mm256_set_epi64x
		(
			(bit_mask_ & 0x01) * element_mask,
			((bit_mask_ & 0x02) >> 1) * element_mask,
			((bit_mask_ & 0x04) >> 2) * element_mask,
			((bit_mask_ & 0x08) >> 3) * element_mask
		);
	}
#pragma endregion

#pragma region STORES
	EMU_SIMD_COMMON_FUNC_SPEC void store_i64x4(std::int64_t* p_out_, i64x4_arg a_)
	{
		_mm256_store_si256(reinterpret_cast<__m256i*>(p_out_), a_);
	}
#pragma endregion

#pragma region CASTS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 cast_f32x4_i64x4(f32x4_arg a_)
	{
		return _mm256_castsi128_si256(_mm_castps_si128(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 cast_f32x8_i64x4(f32x8_arg a_)
	{
		return _mm256_castps_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 cast_f32x16_i64x4(f32x16_arg a_)
	{
		return _mm512_castsi512_si256(_mm512_castps_si512(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 cast_f64x2_i64x4(f64x2_arg a_)
	{
		return _mm256_castsi128_si256(_mm_castpd_si128(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 cast_f64x4_i64x4(f64x4_arg a_)
	{
		return _mm256_castpd_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 cast_f64x8_i64x4(f64x8_arg a_)
	{
		return _mm512_castsi512_si256(_mm512_castpd_si512(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 cast_i8x16_i64x4(i8x16_arg a_)
	{
		return _mm256_castsi128_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 cast_i16x8_i64x4(i16x8_arg a_)
	{
		return _mm256_castsi128_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 cast_i32x4_i64x4(i32x4_arg a_)
	{
		return _mm256_castsi128_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 cast_i64x2_i64x4(i64x2_arg a_)
	{
		return _mm256_castsi128_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 cast_i8x32_i64x4(i8x32_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 cast_i16x16_i64x4(i16x16_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 cast_i32x8_i64x4(i32x8_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 cast_i64x4_i64x4(i64x4_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 cast_i8x64_i64x4(i8x64_arg a_)
	{
		return _mm512_castsi512_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 cast_i16x32_i64x4(i16x32_arg a_)
	{
		return _mm512_castsi512_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 cast_i32x16_i64x4(i32x16_arg a_)
	{
		return _mm512_castsi512_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 cast_i64x8_i64x4(i64x8_arg a_)
	{
		return _mm512_castsi512_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 cast_u8x16_i64x4(u8x16_arg a_)
	{
		return _mm256_castsi128_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 cast_u16x8_i64x4(u16x8_arg a_)
	{
		return _mm256_castsi128_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 cast_u32x4_i64x4(u32x4_arg a_)
	{
		return _mm256_castsi128_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 cast_u64x2_i64x4(u64x2_arg a_)
	{
		return _mm256_castsi128_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 cast_u8x32_i64x4(u8x32_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 cast_u16x16_i64x4(u16x16_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 cast_u32x8_i64x4(u32x8_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 cast_u64x4_i64x4(u64x4_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 cast_u8x64_i64x4(u8x64_arg a_)
	{
		return _mm512_castsi512_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 cast_u16x32_i64x4(u16x32_arg a_)
	{
		return _mm512_castsi512_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 cast_u32x16_i64x4(u32x16_arg a_)
	{
		return _mm512_castsi512_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 cast_u64x8_i64x4(u64x8_arg a_)
	{
		return _mm512_castsi512_si256(a_);
	}
#pragma endregion

#pragma region CONVERSIONS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 cvt_f32x4_i64x4(f32x4_arg a_)
	{
		return _mm256_cvtps_epi64(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 cvt_f32x8_i64x4(f32x8_arg a_)
	{
		return _mm256_cvtps_epi64(_mm256_castps256_ps128(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 cvt_f32x16_i64x4(f32x16_arg a_)
	{
		return _mm256_cvtps_epi64(_mm512_castps512_ps128(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 cvt_f64x2_i64x4(f64x2_arg a_)
	{
		return _mm256_castsi128_si256(_mm_cvtpd_epi64(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 cvt_f64x4_i64x4(f64x4_arg a_)
	{
		return _mm256_cvtpd_epi64(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 cvt_f64x8_i64x4(f64x8_arg a_)
	{
		return _mm256_cvtpd_epi64(_mm512_castpd512_pd256(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 cvt_i8x16_i64x4(i8x16_arg a_)
	{
		return _mm256_cvtepi8_epi64(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 cvt_i16x8_i64x4(i16x8_arg a_)
	{
		return _mm256_cvtepi16_epi64(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 cvt_i32x4_i64x4(i32x4_arg a_)
	{
		return _mm256_cvtepi32_epi64(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 cvt_i64x2_i64x4(i64x2_arg a_)
	{
		return _mm256_castsi128_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 cvt_i8x32_i64x4(i8x32_arg a_)
	{
		return _mm256_cvtepi8_epi64(_mm256_castsi256_si128(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 cvt_i16x16_i64x4(i16x16_arg a_)
	{
		return _mm256_cvtepi16_epi64(_mm256_castsi256_si128(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 cvt_i32x8_i64x4(i32x8_arg a_)
	{
		return _mm256_cvtepi32_epi64(_mm256_castsi256_si128(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 cvt_i64x4_i64x4(i64x4_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 cvt_i8x64_i64x4(i8x64_arg a_)
	{
		return _mm256_cvtepi8_epi64(_mm512_castsi512_si128(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 cvt_i16x32_i64x4(i16x32_arg a_)
	{
		return _mm256_cvtepi16_epi32(_mm512_castsi512_si128(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 cvt_i32x16_i64x4(i32x16_arg a_)
	{
		return _mm256_cvtepi32_epi64(_mm512_castsi512_si128(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 cvt_i64x8_i64x4(i64x8_arg a_)
	{
		return _mm512_castsi512_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 cvt_u8x16_i64x4(u8x16_arg a_)
	{
		return _mm256_cvtepu8_epi64(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 cvt_u16x8_i64x4(u16x8_arg a_)
	{
		return _mm256_cvtepu16_epi64(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 cvt_u32x4_i64x4(u32x4_arg a_)
	{
		return _mm256_cvtepu32_epi64(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 cvt_u64x2_i64x4(u64x2_arg a_)
	{
		return _mm256_castsi128_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 cvt_u8x32_i64x4(u8x32_arg a_)
	{
		return _mm256_cvtepu8_epi64(_mm256_castsi256_si128(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 cvt_u16x16_i64x4(u16x16_arg a_)
	{
		return _mm256_cvtepu16_epi64(_mm256_castsi256_si128(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 cvt_u32x8_i64x4(u32x8_arg a_)
	{
		return _mm256_cvtepu32_epi64(_mm256_castsi256_si128(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 cvt_u64x4_i64x4(u64x4_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 cvt_u8x64_i64x4(u8x64_arg a_)
	{
		return _mm256_cvtepu8_epi64(_mm512_castsi512_si128(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 cvt_u16x32_i64x4(u16x32_arg a_)
	{
		return _mm256_cvtepu16_epi32(_mm512_castsi512_si128(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 cvt_u32x16_i64x4(u32x16_arg a_)
	{
		return _mm256_cvtepu32_epi64(_mm512_castsi512_si128(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 cvt_u64x8_i64x4(u64x8_arg a_)
	{
		return _mm512_castsi512_si256(a_);
	}
#pragma endregion

#pragma region COMPARISONS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 cmpeq_i64x4(EmuSIMD::i64x4_arg lhs_, EmuSIMD::i64x4_arg rhs_)
	{
		return _mm256_cmpeq_epi64(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 cmpneq_i64x4(EmuSIMD::i64x4_arg lhs_, EmuSIMD::i64x4_arg rhs_)
	{
		constexpr std::int64_t mask = static_cast<std::int64_t>(0xFFFFFFFFFFFFFFFF);
		return _mm256_xor_si256(set1_i64x4(mask), _mm256_cmpeq_epi64(lhs_, rhs_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 cmpgt_i64x4(EmuSIMD::i64x4_arg lhs_, EmuSIMD::i64x4_arg rhs_)
	{
		return _mm256_cmpgt_epi64(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 cmplt_i64x4(EmuSIMD::i64x4_arg lhs_, EmuSIMD::i64x4_arg rhs_)
	{
		return _mm256_cmpgt_epi64(rhs_, lhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 cmpge_i64x4(EmuSIMD::i64x4_arg lhs_, EmuSIMD::i64x4_arg rhs_)
	{
		return _mm256_or_si256(_mm256_cmpgt_epi64(lhs_, rhs_), _mm256_cmpeq_epi64(lhs_, rhs_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 cmple_i64x4(EmuSIMD::i64x4_arg lhs_, EmuSIMD::i64x4_arg rhs_)
	{
		return _mm256_or_si256(_mm256_cmpgt_epi64(rhs_, lhs_), _mm256_cmpeq_epi64(lhs_, rhs_));
	}
#pragma endregion

#pragma region BASIC_ARITHMETIC
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 mul_all_i64x4(EmuSIMD::i64x4_arg lhs_, EmuSIMD::i64x4_arg rhs_)
	{
		return _mm256_mullo_epi64(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 negate_i64x4(EmuSIMD::i64x4_arg to_negate_)
	{
		return _mm256_sub_epi64(_mm256_setzero_si256(), to_negate_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 add_i64x4(EmuSIMD::i64x4_arg lhs_, EmuSIMD::i64x4_arg rhs_)
	{
		return _mm256_add_epi64(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 sub_i64x4(EmuSIMD::i64x4_arg lhs_, EmuSIMD::i64x4_arg rhs_)
	{
		return _mm256_sub_epi64(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 mul_i64x4(EmuSIMD::i64x4_arg lhs_, EmuSIMD::i64x4_arg rhs_)
	{
		return _mm256_mullo_epi64(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 div_i64x4(EmuSIMD::i64x4_arg lhs_, EmuSIMD::i64x4_arg rhs_)
	{
		return _mm256_div_epi64(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 addsub_i64x4(EmuSIMD::i64x4_arg lhs_, EmuSIMD::i64x4_arg rhs_)
	{
		constexpr std::int64_t bytes_mask = static_cast<std::int64_t>(0xFFFFFFFFFFFFFFFF);
		const EmuSIMD::i64x4 mask = _mm256_set_epi64x(bytes_mask, 0, bytes_mask, 0);
		EmuSIMD::i64x4 out = _mm256_add_epi64(lhs_, _mm256_and_si256(mask, rhs_));
		return _mm256_sub_epi64(lhs_, _mm256_andnot_si256(mask, rhs_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 subadd_i64x4(EmuSIMD::i64x4_arg lhs_, EmuSIMD::i64x4_arg rhs_)
	{
		constexpr std::int64_t bytes_mask = static_cast<std::int64_t>(0xFFFFFFFFFFFFFFFF);
		const EmuSIMD::i64x4 mask = _mm256_set_epi64x(bytes_mask, 0, bytes_mask, 0);
		EmuSIMD::i64x4 out = _mm256_sub_epi64(lhs_, _mm256_and_si256(mask, rhs_));
		return _mm256_add_epi64(lhs_, _mm256_andnot_si256(mask, rhs_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 fmadd_i64x4(EmuSIMD::i64x4_arg a_, EmuSIMD::i64x4_arg b_, EmuSIMD::i64x4_arg c_)
	{
		return _mm256_add_epi64(mul_all_i64x4(a_, b_), c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 fmsub_i64x4(EmuSIMD::i64x4_arg a_, EmuSIMD::i64x4_arg b_, EmuSIMD::i64x4_arg c_)
	{
		return _mm256_sub_epi64(mul_all_i64x4(a_, b_), c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 fnmadd_i64x4(EmuSIMD::i64x4_arg a_, EmuSIMD::i64x4_arg b_, EmuSIMD::i64x4_arg c_)
	{
		return _mm256_add_epi64(mul_all_i64x4(negate_i64x4(a_), b_), c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 fnmsub_i64x4(EmuSIMD::i64x4_arg a_, EmuSIMD::i64x4_arg b_, EmuSIMD::i64x4_arg c_)
	{
		return _mm256_sub_epi64(mul_all_i64x4(negate_i64x4(a_), b_), c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 fmaddsub_i64x4(EmuSIMD::i64x4_arg a_, EmuSIMD::i64x4_arg b_, EmuSIMD::i64x4_arg c_)
	{
		return addsub_i64x4(mul_all_i64x4(a_, b_), c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 fmsubadd_i64x4(EmuSIMD::i64x4_arg a_, EmuSIMD::i64x4_arg b_, EmuSIMD::i64x4_arg c_)
	{
		return subadd_i64x4(mul_all_i64x4(a_, b_), c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 floor_i64x4(EmuSIMD::i64x4_arg to_floor_)
	{
		return to_floor_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 ceil_i64x4(EmuSIMD::i64x4_arg to_ceil_)
	{
		return to_ceil_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 trunc_i64x4(EmuSIMD::i64x4_arg to_trunc_)
	{
		return to_trunc_;
	}

	template<int RoundingFlag_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 round_i64x4(EmuSIMD::i64x4_arg to_round_)
	{
		return to_round_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 mod_i64x4(EmuSIMD::i64x4_arg lhs_, EmuSIMD::i64x4_arg rhs_)
	{
		return _mm256_rem_epi64(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 abs_i64x4(EmuSIMD::i64x4_arg in_)
	{
		return _mm256_abs_epi64(in_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 sqrt_i64x4(EmuSIMD::i64x4_arg in_)
	{
		return _mm256_cvtpd_epi64(_mm256_sqrt_pd(_mm256_cvtepi64_pd(in_)));
	}
#pragma endregion
}

#endif
