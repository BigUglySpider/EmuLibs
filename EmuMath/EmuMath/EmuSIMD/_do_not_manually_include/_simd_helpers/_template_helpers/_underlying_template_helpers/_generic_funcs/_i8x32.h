#ifndef EMU_SIMD_GENERIC_FUNCS_I8X32_H_INC_
#define EMU_SIMD_GENERIC_FUNCS_I8X32_H_INC_ 1

#include "../_common_underlying_simd_template_helper_includes.h"
#include <immintrin.h>

namespace EmuSIMD::Funcs
{
#pragma region SETTERS
	inline EmuSIMD::i8x32 set_i8x16
	(
		std::int8_t e0, std::int8_t e1, std::int8_t e2, std::int8_t e3, std::int8_t e4, std::int8_t e5, std::int8_t e6, std::int8_t e7,
		std::int8_t e8, std::int8_t e9, std::int8_t e10, std::int8_t e11, std::int8_t e12, std::int8_t e13, std::int8_t e14, std::int8_t e15,
		std::int8_t e16, std::int8_t e17, std::int8_t e18, std::int8_t e19, std::int8_t e20, std::int8_t e21, std::int8_t e22, std::int8_t e23,
		std::int8_t e24, std::int8_t e25, std::int8_t e26, std::int8_t e27, std::int8_t e28, std::int8_t e29, std::int8_t e30, std::int8_t e31
	)
	{
		return _mm256_set_epi8(e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19, e20, e21, e22, e23, e24, e25, e26, e27, e28, e29, e30, e31);
	}

	inline EmuSIMD::i8x32 setr_i8x16
	(
		std::int8_t e0, std::int8_t e1, std::int8_t e2, std::int8_t e3, std::int8_t e4, std::int8_t e5, std::int8_t e6, std::int8_t e7,
		std::int8_t e8, std::int8_t e9, std::int8_t e10, std::int8_t e11, std::int8_t e12, std::int8_t e13, std::int8_t e14, std::int8_t e15,
		std::int8_t e16, std::int8_t e17, std::int8_t e18, std::int8_t e19, std::int8_t e20, std::int8_t e21, std::int8_t e22, std::int8_t e23,
		std::int8_t e24, std::int8_t e25, std::int8_t e26, std::int8_t e27, std::int8_t e28, std::int8_t e29, std::int8_t e30, std::int8_t e31
	)
	{
		return _mm256_setr_epi8(e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19, e20, e21, e22, e23, e24, e25, e26, e27, e28, e29, e30, e31);
	}

	inline EmuSIMD::i8x32 set1_i8x32(std::int8_t all_)
	{
		return _mm256_set1_epi8(all_);
	}

	inline EmuSIMD::i8x32 load_i8x32(const std::int8_t* p_to_load_)
	{
		return _mm256_load_si256(reinterpret_cast<const __m256i*>(p_to_load_));
	}

	inline EmuSIMD::i8x32 setzero_i8x32()
	{
		return _mm256_setzero_si256();
	}
#pragma endregion

#pragma region STORES
	inline void store_i8x32(std::int8_t* p_out_, i8x32_arg a_)
	{
		_mm256_store_si256(reinterpret_cast<__m256i*>(p_out_), a_);
	}
#pragma endregion

#pragma region SHUFFLES
	inline EmuSIMD::i8x32 shuffle_i8x32(i8x32_arg a_, i8x32_arg mask_)
	{
		return _mm256_shuffle_epi8(a_, mask_);
	}
#pragma endregion

#pragma region CASTS
	inline EmuSIMD::i8x32 cast_f32x4_i8x32(f32x4_arg a_)
	{
		return _mm256_castsi128_si256(_mm_castps_si128(a_)); 
	}

	inline EmuSIMD::i8x32 cast_f32x8_i8x32(f32x8_arg a_)
	{
		return _mm256_castps_si256(a_);
	}

	inline EmuSIMD::i8x32 cast_f32x16_i8x32(f32x16_arg a_)
	{
		return _mm512_castsi512_si256(_mm512_castps_si512(a_));
	}

	inline EmuSIMD::i8x32 cast_f64x2_i8x32(f64x2_arg a_)
	{
		return _mm256_castsi128_si256(_mm_castpd_si128(a_));
	}

	inline EmuSIMD::i8x32 cast_f64x4_i8x32(f64x4_arg a_)
	{
		return _mm256_castpd_si256(a_);
	}

	inline EmuSIMD::i8x32 cast_f64x8_i8x32(f64x8_arg a_)
	{
		return _mm512_castsi512_si256(_mm512_castpd_si512(a_));
	}

	inline EmuSIMD::i8x32 cast_i8x16_i8x32(i8x16_arg a_)
	{
		return _mm256_castsi128_si256(a_);
	}

	inline EmuSIMD::i8x32 cast_i16x8_i8x32(i16x8_arg a_)
	{
		return _mm256_castsi128_si256(a_);
	}

	inline EmuSIMD::i8x32 cast_i32x4_i8x32(i32x4_arg a_)
	{
		return _mm256_castsi128_si256(a_);
	}

	inline EmuSIMD::i8x32 cast_i64x2_i8x32(i64x2_arg a_)
	{
		return _mm256_castsi128_si256(a_);
	}

	inline EmuSIMD::i8x32 cast_i8x32_i8x32(i8x32_arg a_)
	{
		return a_;
	}

	inline EmuSIMD::i8x32 cast_i16x16_i8x32(i16x16_arg a_)
	{
		return a_;
	}

	inline EmuSIMD::i8x32 cast_i32x8_i8x32(i32x8_arg a_)
	{
		return a_;
	}

	inline EmuSIMD::i8x32 cast_i64x4_i8x32(i64x4_arg a_)
	{
		return a_;
	}

	inline EmuSIMD::i8x32 cast_i8x64_i8x32(i8x64_arg a_)
	{
		return _mm512_castsi512_si256(a_);
	}

	inline EmuSIMD::i8x32 cast_i16x32_i8x32(i16x32_arg a_)
	{
		return _mm512_castsi512_si256(a_);
	}

	inline EmuSIMD::i8x32 cast_i32x16_i8x32(i32x16_arg a_)
	{
		return _mm512_castsi512_si256(a_);
	}

	inline EmuSIMD::i8x32 cast_i64x8_i8x32(i64x8_arg a_)
	{
		return _mm512_castsi512_si256(a_);
	}

	inline EmuSIMD::i8x32 cast_u8x16_i8x32(u8x16_arg a_)
	{
		return _mm256_castsi128_si256(a_);
	}

	inline EmuSIMD::i8x32 cast_u16x8_i8x32(u16x8_arg a_)
	{
		return _mm256_castsi128_si256(a_);
	}

	inline EmuSIMD::i8x32 cast_u32x4_i8x32(u32x4_arg a_)
	{
		return _mm256_castsi128_si256(a_);
	}

	inline EmuSIMD::i8x32 cast_u64x2_i8x32(u64x2_arg a_)
	{
		return _mm256_castsi128_si256(a_);
	}

	inline EmuSIMD::i8x32 cast_u8x32_i8x32(u8x32_arg a_)
	{
		return a_;
	}

	inline EmuSIMD::i8x32 cast_u16x16_i8x32(u16x16_arg a_)
	{
		return a_;
	}

	inline EmuSIMD::i8x32 cast_u32x8_i8x32(u32x8_arg a_)
	{
		return a_;
	}

	inline EmuSIMD::i8x32 cast_u64x4_i8x32(u64x4_arg a_)
	{
		return a_;
	}

	inline EmuSIMD::i8x32 cast_u8x64_i8x32(u8x64_arg a_)
	{
		return _mm512_castsi512_si256(a_);
	}

	inline EmuSIMD::i8x32 cast_u16x32_i8x32(u16x32_arg a_)
	{
		return _mm512_castsi512_si256(a_);
	}

	inline EmuSIMD::i8x32 cast_u32x16_i8x32(u32x16_arg a_)
	{
		return _mm512_castsi512_si256(a_);
	}

	inline EmuSIMD::i8x32 cast_u64x8_i8x32(u64x8_arg a_)
	{
		return _mm512_castsi512_si256(a_);
	}
#pragma endregion

#pragma region CONVERSIONS
	inline EmuSIMD::i8x32 cvt_f32x4_i8x32(f32x4_arg a_)
	{
		return _mm256_castsi128_si256(_mm_cvtepi32_epi8(_mm_cvtps_epi32(a_)));
	}

	inline EmuSIMD::i8x32 cvt_f32x8_i8x32(f32x8_arg a_)
	{
		return _mm256_castsi128_si256(_mm256_cvtepi32_epi8(_mm256_cvtps_epi32(a_)));
	}

	inline EmuSIMD::i8x32 cvt_f32x16_i8x32(f32x16_arg a_)
	{
		return _mm256_castsi128_si256(_mm512_cvtepi32_epi8(_mm512_cvtps_epi32(a_)));
	}

	inline EmuSIMD::i8x32 cvt_f64x2_i8x32(f64x2_arg a_)
	{
		return _mm256_castsi128_si256(_mm_cvtepi64_epi8(_mm_cvtpd_epi64(a_)));
	}

	inline EmuSIMD::i8x32 cvt_f64x4_i8x32(f64x4_arg a_)
	{
		return _mm256_castsi128_si256(_mm256_cvtepi64_epi8(_mm256_cvtpd_epi64(a_)));
	}

	inline EmuSIMD::i8x32 cvt_f64x8_i8x32(f64x8_arg a_)
	{
		return _mm256_castsi128_si256(_mm512_cvtepi64_epi8(_mm512_cvtpd_epi64(a_)));
	}

	inline EmuSIMD::i8x32 cvt_i8x16_i8x32(i8x16_arg a_)
	{
		return _mm256_castsi128_si256(a_);
	}

	inline EmuSIMD::i8x32 cvt_i16x8_i8x32(i16x8_arg a_)
	{
		return _mm256_castsi128_si256(_mm_cvtepi16_epi8(a_));
	}

	inline EmuSIMD::i8x32 cvt_i32x4_i8x32(i32x4_arg a_)
	{
		return _mm256_castsi128_si256(_mm_cvtepi32_epi8(a_));
	}

	inline EmuSIMD::i8x32 cvt_i64x2_i8x32(i64x2_arg a_)
	{
		return _mm256_castsi128_si256(_mm_cvtepi64_epi8(a_));
	}

	inline EmuSIMD::i8x32 cvt_i8x32_i8x32(i8x32_arg a_)
	{
		return a_;
	}

	inline EmuSIMD::i8x32 cvt_i16x16_i8x32(i16x16_arg a_)
	{
		return _mm256_castsi128_si256(_mm256_cvtepi16_epi8(a_));
	}

	inline EmuSIMD::i8x32 cvt_i32x8_i8x32(i32x8_arg a_)
	{
		return _mm256_castsi128_si256(_mm256_cvtepi32_epi8(a_));
	}

	inline EmuSIMD::i8x32 cvt_i64x4_i8x32(i64x4_arg a_)
	{
		return _mm256_castsi128_si256(_mm256_cvtepi64_epi8(a_));
	}

	inline EmuSIMD::i8x32 cvt_i8x64_i8x32(i8x64_arg a_)
	{
		return _mm512_castsi512_si256(a_);
	}

	inline EmuSIMD::i8x32 cvt_i16x32_i8x32(i16x32_arg a_)
	{
		return _mm512_cvtepi16_epi8(a_);
	}

	inline EmuSIMD::i8x32 cvt_i32x16_i8x32(i32x16_arg a_)
	{
		return _mm256_castsi128_si256(_mm512_cvtepi32_epi8(a_));
	}

	inline EmuSIMD::i8x32 cvt_i64x8_i8x32(i64x8_arg a_)
	{
		return _mm256_castsi128_si256(_mm512_cvtepi64_epi8(a_));
	}

	inline EmuSIMD::i8x32 cvt_u8x16_i8x32(u8x16_arg a_)
	{
		return _mm256_castsi128_si256(a_);
	}

	inline EmuSIMD::i8x32 cvt_u16x8_i8x32(u16x8_arg a_)
	{
		return _mm256_castsi128_si256(_mm_cvtepi16_epi8(a_));
	}

	inline EmuSIMD::i8x32 cvt_u32x4_i8x32(u32x4_arg a_)
	{
		return _mm256_castsi128_si256(_mm_cvtepi32_epi8(a_));
	}

	inline EmuSIMD::i8x32 cvt_u64x2_i8x32(u64x2_arg a_)
	{
		return _mm256_castsi128_si256(_mm_cvtepi64_epi8(a_));
	}

	inline EmuSIMD::i8x32 cvt_u8x32_i8x32(u8x32_arg a_)
	{
		return a_;
	}

	inline EmuSIMD::i8x32 cvt_u16x16_i8x32(u16x16_arg a_)
	{
		return _mm256_castsi128_si256(_mm256_cvtepi16_epi8(a_));
	}

	inline EmuSIMD::i8x32 cvt_u32x8_i8x32(u32x8_arg a_)
	{
		return _mm256_castsi128_si256(_mm256_cvtepi32_epi8(a_));
	}

	inline EmuSIMD::i8x32 cvt_u64x4_i8x32(u64x4_arg a_)
	{
		return _mm256_castsi128_si256(_mm256_cvtepi64_epi8(a_));
	}

	inline EmuSIMD::i8x32 cvt_u8x64_i8x32(u8x64_arg a_)
	{
		return _mm512_castsi512_si256(a_);
	}

	inline EmuSIMD::i8x32 cvt_u16x32_i8x32(u16x32_arg a_)
	{
		return _mm512_cvtepi16_epi8(a_);
	}

	inline EmuSIMD::i8x32 cvt_u32x16_i8x32(u32x16_arg a_)
	{
		return _mm256_castsi128_si256(_mm512_cvtepi32_epi8(a_));
	}

	inline EmuSIMD::i8x32 cvt_u64x8_i8x32(u64x8_arg a_)
	{
		return _mm256_castsi128_si256(_mm512_cvtepi64_epi8(a_));
	}
#pragma endregion

#pragma region BASIC_ARITHMETIC
	inline EmuSIMD::i8x32 mul_all_i8x32(EmuSIMD::i8x32_arg lhs_, EmuSIMD::i8x32_arg rhs_)
	{
		EmuSIMD::i8x32 even_bytes = _mm256_mullo_epi16(lhs_, rhs_);
		EmuSIMD::i8x32 odd_bytes = _mm256_mullo_epi16(_mm256_srli_epi16(lhs_, 8), _mm256_srli_epi16(rhs_, 8));
		return _mm256_or_si256(_mm256_slli_epi16(odd_bytes, 8), _mm256_srli_epi16(_mm256_slli_epi16(even_bytes, 8), 8));
	}

	inline EmuSIMD::i8x32 negate_i8x32(EmuSIMD::i8x32_arg to_negate_)
	{
		return _mm256_sub_epi8(_mm256_setzero_si256(), to_negate_);
	}

	inline EmuSIMD::i8x32 add_i8x32(EmuSIMD::i8x32_arg lhs_, EmuSIMD::i8x32_arg rhs_)
	{
		return _mm256_add_epi8(lhs_, rhs_);
	}

	inline EmuSIMD::i8x32 sub_i8x32(EmuSIMD::i8x32_arg lhs_, EmuSIMD::i8x32_arg rhs_)
	{
		return _mm256_sub_epi8(lhs_, rhs_);
	}

	inline EmuSIMD::i8x32 mul_i8x32(EmuSIMD::i8x32_arg lhs_, EmuSIMD::i8x32_arg rhs_)
	{
		return _mm256_mul_epi32(lhs_, rhs_);
	}

	inline EmuSIMD::i8x32 div_i8x32(EmuSIMD::i8x32_arg lhs_, EmuSIMD::i8x32_arg rhs_)
	{
		return _mm256_div_epi8(lhs_, rhs_);
	}

	inline EmuSIMD::i8x32 addsub_i8x32(EmuSIMD::i8x32_arg lhs_, EmuSIMD::i8x32_arg rhs_)
	{
		constexpr std::int8_t byte_mask = static_cast<std::int8_t>(0xFF);
		const EmuSIMD::i8x32 mask = _mm256_set_epi8
		(
			byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0,
			byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0
		);
		EmuSIMD::i8x32 out = _mm256_add_epi8(lhs_, _mm256_and_si256(mask, rhs_));
		return _mm256_sub_epi8(lhs_, _mm256_andnot_si256(mask, rhs_));
	}

	inline EmuSIMD::i8x32 subadd_i8x32(EmuSIMD::i8x32_arg lhs_, EmuSIMD::i8x32_arg rhs_)
	{
		constexpr std::int8_t byte_mask = static_cast<std::int8_t>(0xFF);
		const EmuSIMD::i8x32 mask = _mm256_set_epi8
		(
			byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0,
			byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0
		);
		EmuSIMD::i8x32 out = _mm256_sub_epi8(lhs_, _mm256_and_si256(mask, rhs_));
		return _mm256_add_epi8(lhs_, _mm256_andnot_si256(mask, rhs_));
	}

	inline EmuSIMD::i8x32 fmadd_i8x32(EmuSIMD::i8x32_arg a_, EmuSIMD::i8x32_arg b_, EmuSIMD::i8x32_arg c_)
	{
		return _mm256_add_epi8(mul_all_i8x32(a_, b_), c_);
	}

	inline EmuSIMD::i8x32 fmsub_i8x32(EmuSIMD::i8x32_arg a_, EmuSIMD::i8x32_arg b_, EmuSIMD::i8x32_arg c_)
	{
		return _mm256_sub_epi8(mul_all_i8x32(a_, b_), c_);
	}

	inline EmuSIMD::i8x32 fnmadd_i8x32(EmuSIMD::i8x32_arg a_, EmuSIMD::i8x32_arg b_, EmuSIMD::i8x32_arg c_)
	{
		return _mm256_add_epi8(mul_all_i8x32(negate_i8x32(a_), b_), c_);
	}

	inline EmuSIMD::i8x32 fnmsub_i8x32(EmuSIMD::i8x32_arg a_, EmuSIMD::i8x32_arg b_, EmuSIMD::i8x32_arg c_)
	{
		return _mm256_sub_epi8(mul_all_i8x32(negate_i8x32(a_), b_), c_);
	}

	inline EmuSIMD::i8x32 fmaddsub_i8x32(EmuSIMD::i8x32_arg a_, EmuSIMD::i8x32_arg b_, EmuSIMD::i8x32_arg c_)
	{
		return addsub_i8x32(mul_all_i8x32(negate_i8x32(a_), b_), c_);
	}

	inline EmuSIMD::i8x32 fmsubadd_i8x32(EmuSIMD::i8x32_arg a_, EmuSIMD::i8x32_arg b_, EmuSIMD::i8x32_arg c_)
	{
		return subadd_i8x32(mul_all_i8x32(negate_i8x32(a_), b_), c_);
	}

	inline EmuSIMD::i8x32 floor_i8x32(EmuSIMD::i8x32_arg to_floor_)
	{
		return to_floor_;
	}

	inline EmuSIMD::i8x32 ceil_i8x32(EmuSIMD::i8x32_arg to_ceil_)
	{
		return to_ceil_;
	}

	inline EmuSIMD::i8x32 trunc_i8x32(EmuSIMD::i8x32_arg to_trunc_)
	{
		return to_trunc_;
	}

	template<int RoundingFlag_>
	inline EmuSIMD::i8x32 round_i8x32(EmuSIMD::i8x32_arg to_round_)
	{
		return to_round_;
	}

	inline EmuSIMD::i8x32 mod_i8x32(EmuSIMD::i8x32_arg lhs_, EmuSIMD::i8x32_arg rhs_)
	{
		return _mm256_rem_epi8(lhs_, rhs_);
	}
#pragma endregion
}

#endif
