#ifndef EMU_SIMD_GENERIC_FUNCS_U8X32_H_INC_
#define EMU_SIMD_GENERIC_FUNCS_U8X32_H_INC_ 1

#include "_common_generic_func_helpers.h"

namespace EmuSIMD::Funcs
{
#pragma region SETTERS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x32 set_u8x32
	(
		std::uint8_t e0, std::uint8_t e1, std::uint8_t e2, std::uint8_t e3, std::uint8_t e4, std::uint8_t e5, std::uint8_t e6, std::uint8_t e7,
		std::uint8_t e8, std::uint8_t e9, std::uint8_t e10, std::uint8_t e11, std::uint8_t e12, std::uint8_t e13, std::uint8_t e14, std::uint8_t e15,
		std::uint8_t e16, std::uint8_t e17, std::uint8_t e18, std::uint8_t e19, std::uint8_t e20, std::uint8_t e21, std::uint8_t e22, std::uint8_t e23,
		std::uint8_t e24, std::uint8_t e25, std::uint8_t e26, std::uint8_t e27, std::uint8_t e28, std::uint8_t e29, std::uint8_t e30, std::uint8_t e31
	)
	{
		return _mm256_set_epi8(e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19, e20, e21, e22, e23, e24, e25, e26, e27, e28, e29, e30, e31);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x32 setr_u8x32
	(
		std::uint8_t e0, std::uint8_t e1, std::uint8_t e2, std::uint8_t e3, std::uint8_t e4, std::uint8_t e5, std::uint8_t e6, std::uint8_t e7,
		std::uint8_t e8, std::uint8_t e9, std::uint8_t e10, std::uint8_t e11, std::uint8_t e12, std::uint8_t e13, std::uint8_t e14, std::uint8_t e15,
		std::uint8_t e16, std::uint8_t e17, std::uint8_t e18, std::uint8_t e19, std::uint8_t e20, std::uint8_t e21, std::uint8_t e22, std::uint8_t e23,
		std::uint8_t e24, std::uint8_t e25, std::uint8_t e26, std::uint8_t e27, std::uint8_t e28, std::uint8_t e29, std::uint8_t e30, std::uint8_t e31
	)
	{
		return _mm256_setr_epi8(e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19, e20, e21, e22, e23, e24, e25, e26, e27, e28, e29, e30, e31);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x32 set1_u8x32(std::uint8_t all_)
	{
		return _mm256_set1_epi8(all_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x32 load_u8x32(const std::uint8_t* p_to_load_)
	{
		return _mm256_load_si256(reinterpret_cast<const __m256i*>(p_to_load_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x32 setzero_u8x32()
	{
		return _mm256_setzero_si256();
	}
#pragma endregion

#pragma region STORES
	EMU_SIMD_COMMON_FUNC_SPEC void store_u8x32(std::uint8_t* p_out_, u8x32_arg a_)
	{
		_mm256_store_si256(reinterpret_cast<__m256i*>(p_out_), a_);
	}
#pragma endregion

#pragma region CASTS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x32 cast_f32x4_u8x32(f32x4_arg a_)
	{
		return _mm256_castsi128_si256(_mm_castps_si128(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x32 cast_f32x8_u8x32(f32x8_arg a_)
	{
		return _mm256_castps_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x32 cast_f32x16_u8x32(f32x16_arg a_)
	{
		return _mm512_castsi512_si256(_mm512_castps_si512(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x32 cast_f64x2_u8x32(f64x2_arg a_)
	{
		return _mm256_castsi128_si256(_mm_castpd_si128(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x32 cast_f64x4_u8x32(f64x4_arg a_)
	{
		return _mm256_castpd_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x32 cast_f64x8_u8x32(f64x8_arg a_)
	{
		return _mm512_castsi512_si256(_mm512_castpd_si512(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x32 cast_i8x16_u8x32(i8x16_arg a_)
	{
		return _mm256_castsi128_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x32 cast_i16x8_u8x32(i16x8_arg a_)
	{
		return _mm256_castsi128_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x32 cast_i32x4_u8x32(i32x4_arg a_)
	{
		return _mm256_castsi128_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x32 cast_i64x2_u8x32(i64x2_arg a_)
	{
		return _mm256_castsi128_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x32 cast_i8x32_u8x32(i8x32_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x32 cast_i16x16_u8x32(i16x16_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x32 cast_i32x8_u8x32(i32x8_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x32 cast_i64x4_u8x32(i64x4_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x32 cast_i8x64_u8x32(i8x64_arg a_)
	{
		return _mm512_castsi512_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x32 cast_i16x32_u8x32(i16x32_arg a_)
	{
		return _mm512_castsi512_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x32 cast_i32x16_u8x32(i32x16_arg a_)
	{
		return _mm512_castsi512_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x32 cast_i64x8_u8x32(i64x8_arg a_)
	{
		return _mm512_castsi512_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x32 cast_u8x16_u8x32(u8x16_arg a_)
	{
		return _mm256_castsi128_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x32 cast_u16x8_u8x32(u16x8_arg a_)
	{
		return _mm256_castsi128_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x32 cast_u32x4_u8x32(u32x4_arg a_)
	{
		return _mm256_castsi128_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x32 cast_u64x2_u8x32(u64x2_arg a_)
	{
		return _mm256_castsi128_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x32 cast_u8x32_u8x32(u8x32_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x32 cast_u16x16_u8x32(u16x16_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x32 cast_u32x8_u8x32(u32x8_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x32 cast_u64x4_u8x32(u64x4_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x32 cast_u8x64_u8x32(u8x64_arg a_)
	{
		return _mm512_castsi512_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x32 cast_u16x32_u8x32(u16x32_arg a_)
	{
		return _mm512_castsi512_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x32 cast_u32x16_u8x32(u32x16_arg a_)
	{
		return _mm512_castsi512_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x32 cast_u64x8_u8x32(u64x8_arg a_)
	{
		return _mm512_castsi512_si256(a_);
	}
#pragma endregion

#pragma region CONVERSIONS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x32 cvt_f32x4_u8x32(f32x4_arg a_)
	{
		return _mm256_castsi128_si256(_mm_cvtepi32_epi8(_mm_cvtps_epi32(a_)));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x32 cvt_f32x8_u8x32(f32x8_arg a_)
	{
		return _mm256_castsi128_si256(_mm256_cvtepi32_epi8(_mm256_cvtps_epi32(a_)));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x32 cvt_f32x16_u8x32(f32x16_arg a_)
	{
		return _mm256_castsi128_si256(_mm512_cvtepi32_epi8(_mm512_cvtps_epi32(a_)));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x32 cvt_f64x2_u8x32(f64x2_arg a_)
	{
		return _mm256_castsi128_si256(_mm_cvtepi64_epi8(_mm_cvtpd_epi64(a_)));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x32 cvt_f64x4_u8x32(f64x4_arg a_)
	{
		return _mm256_castsi128_si256(_mm256_cvtepi64_epi8(_mm256_cvtpd_epi64(a_)));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x32 cvt_f64x8_u8x32(f64x8_arg a_)
	{
		return _mm256_castsi128_si256(_mm512_cvtepi64_epi8(_mm512_cvtpd_epi64(a_)));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x32 cvt_i8x16_u8x32(i8x16_arg a_)
	{
		return _mm256_castsi128_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x32 cvt_i16x8_u8x32(i16x8_arg a_)
	{
		return _mm256_castsi128_si256(_mm_cvtepi16_epi8(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x32 cvt_i32x4_u8x32(i32x4_arg a_)
	{
		return _mm256_castsi128_si256(_mm_cvtepi32_epi8(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x32 cvt_i64x2_u8x32(i64x2_arg a_)
	{
		return _mm256_castsi128_si256(_mm_cvtepi64_epi8(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x32 cvt_i8x32_u8x32(i8x32_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x32 cvt_i16x16_u8x32(i16x16_arg a_)
	{
		return _mm256_castsi128_si256(_mm256_cvtepi16_epi8(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x32 cvt_i32x8_u8x32(i32x8_arg a_)
	{
		return _mm256_castsi128_si256(_mm256_cvtepi32_epi8(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x32 cvt_i64x4_u8x32(i64x4_arg a_)
	{
		return _mm256_castsi128_si256(_mm256_cvtepi64_epi8(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x32 cvt_i8x64_u8x32(i8x64_arg a_)
	{
		return _mm512_castsi512_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x32 cvt_i16x32_u8x32(i16x32_arg a_)
	{
		return _mm512_cvtepi16_epi8(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x32 cvt_i32x16_u8x32(i32x16_arg a_)
	{
		return _mm256_castsi128_si256(_mm512_cvtepi32_epi8(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x32 cvt_i64x8_u8x32(i64x8_arg a_)
	{
		return _mm256_castsi128_si256(_mm512_cvtepi64_epi8(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x32 cvt_u8x16_u8x32(u8x16_arg a_)
	{
		return _mm256_castsi128_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x32 cvt_u16x8_u8x32(u16x8_arg a_)
	{
		return _mm256_castsi128_si256(_mm_cvtepi16_epi8(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x32 cvt_u32x4_u8x32(u32x4_arg a_)
	{
		return _mm256_castsi128_si256(_mm_cvtepi32_epi8(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x32 cvt_u64x2_u8x32(u64x2_arg a_)
	{
		return _mm256_castsi128_si256(_mm_cvtepi64_epi8(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x32 cvt_u8x32_u8x32(u8x32_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x32 cvt_u16x16_u8x32(u16x16_arg a_)
	{
		return _mm256_castsi128_si256(_mm256_cvtepi16_epi8(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x32 cvt_u32x8_u8x32(u32x8_arg a_)
	{
		return _mm256_castsi128_si256(_mm256_cvtepi32_epi8(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x32 cvt_u64x4_u8x32(u64x4_arg a_)
	{
		return _mm256_castsi128_si256(_mm256_cvtepi64_epi8(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x32 cvt_u8x64_u8x32(u8x64_arg a_)
	{
		return _mm512_castsi512_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x32 cvt_u16x32_u8x32(u16x32_arg a_)
	{
		return _mm512_cvtepi16_epi8(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x32 cvt_u32x16_u8x32(u32x16_arg a_)
	{
		return _mm256_castsi128_si256(_mm512_cvtepi32_epi8(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x32 cvt_u64x8_u8x32(u64x8_arg a_)
	{
		return _mm256_castsi128_si256(_mm512_cvtepi64_epi8(a_));
	}
#pragma endregion

#pragma region BASIC_ARITHMETIC
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x32 mul_all_u8x32(EmuSIMD::u8x32_arg lhs_, EmuSIMD::u8x32_arg rhs_)
	{
		EmuSIMD::u8x32 even_bytes = _mm256_mullo_epi16(lhs_, rhs_);
		EmuSIMD::u8x32 odd_bytes = _mm256_mullo_epi16(_mm256_srli_epi16(lhs_, 8), _mm256_srli_epi16(rhs_, 8));
		return _mm256_or_si256(_mm256_slli_epi16(odd_bytes, 8), _mm256_srli_epi16(_mm256_slli_epi16(even_bytes, 8), 8));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x32 negate_u8x32(EmuSIMD::u8x32_arg to_negate_)
	{
		return _mm256_sub_epi8(_mm256_setzero_si256(), to_negate_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x32 add_u8x32(EmuSIMD::u8x32_arg lhs_, EmuSIMD::u8x32_arg rhs_)
	{
		return _mm256_add_epi8(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x32 sub_u8x32(EmuSIMD::u8x32_arg lhs_, EmuSIMD::u8x32_arg rhs_)
	{
		return _mm256_sub_epi8(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x32 mul_u8x32(EmuSIMD::u8x32_arg lhs_, EmuSIMD::u8x32_arg rhs_)
	{
		return _mm256_mul_epu32(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x32 div_u8x32(EmuSIMD::u8x32_arg lhs_, EmuSIMD::u8x32_arg rhs_)
	{
		return _mm256_div_epu8(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x32 addsub_u8x32(EmuSIMD::u8x32_arg lhs_, EmuSIMD::u8x32_arg rhs_)
	{
		constexpr std::uint8_t byte_mask = static_cast<std::uint8_t>(0xFF);
		const EmuSIMD::u8x32 mask = _mm256_set_epi8
		(
			byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0,
			byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0
		);
		EmuSIMD::u8x32 out = _mm256_add_epi8(lhs_, _mm256_and_si256(mask, rhs_));
		return _mm256_sub_epi8(lhs_, _mm256_andnot_si256(mask, rhs_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x32 subadd_u8x32(EmuSIMD::u8x32_arg lhs_, EmuSIMD::u8x32_arg rhs_)
	{
		constexpr std::uint8_t byte_mask = static_cast<std::uint8_t>(0xFF);
		const EmuSIMD::u8x32 mask = _mm256_set_epi8
		(
			byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0,
			byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0
		);
		EmuSIMD::u8x32 out = _mm256_sub_epi8(lhs_, _mm256_and_si256(mask, rhs_));
		return _mm256_add_epi8(lhs_, _mm256_andnot_si256(mask, rhs_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x32 fmadd_u8x32(EmuSIMD::u8x32_arg a_, EmuSIMD::u8x32_arg b_, EmuSIMD::u8x32_arg c_)
	{
		return _mm256_add_epi8(mul_all_u8x32(a_, b_), c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x32 fmsub_u8x32(EmuSIMD::u8x32_arg a_, EmuSIMD::u8x32_arg b_, EmuSIMD::u8x32_arg c_)
	{
		return _mm256_sub_epi8(mul_all_u8x32(a_, b_), c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x32 fnmadd_u8x32(EmuSIMD::u8x32_arg a_, EmuSIMD::u8x32_arg b_, EmuSIMD::u8x32_arg c_)
	{
		return _mm256_add_epi8(mul_all_u8x32(negate_u8x32(a_), b_), c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x32 fnmsub_u8x32(EmuSIMD::u8x32_arg a_, EmuSIMD::u8x32_arg b_, EmuSIMD::u8x32_arg c_)
	{
		return _mm256_sub_epi8(mul_all_u8x32(negate_u8x32(a_), b_), c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x32 fmaddsub_u8x32(EmuSIMD::u8x32_arg a_, EmuSIMD::u8x32_arg b_, EmuSIMD::u8x32_arg c_)
	{
		return addsub_u8x32(mul_all_u8x32(negate_u8x32(a_), b_), c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x32 fmsubadd_u8x32(EmuSIMD::u8x32_arg a_, EmuSIMD::u8x32_arg b_, EmuSIMD::u8x32_arg c_)
	{
		return subadd_u8x32(mul_all_u8x32(negate_u8x32(a_), b_), c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x32 floor_u8x32(EmuSIMD::u8x32_arg to_floor_)
	{
		return to_floor_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x32 ceil_u8x32(EmuSIMD::u8x32_arg to_ceil_)
	{
		return to_ceil_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x32 trunc_u8x32(EmuSIMD::u8x32_arg to_trunc_)
	{
		return to_trunc_;
	}

	template<int RoundingFlag_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x32 round_u8x32(EmuSIMD::u8x32_arg to_round_)
	{
		return to_round_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x32 mod_u8x32(EmuSIMD::u8x32_arg lhs_, EmuSIMD::u8x32_arg rhs_)
	{
		return _mm256_rem_epu8(lhs_, rhs_);
	}
#pragma endregion
}

#endif