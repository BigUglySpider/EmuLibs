#ifndef EMU_SIMD_GENERIC_FUNCS_U64X8_H_INC_
#define EMU_SIMD_GENERIC_FUNCS_U64X8_H_INC_ 1

#include "_common_generic_func_helpers.h"

namespace EmuSIMD::Funcs
{
#pragma region SETTERS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 set_u64x8
	(
		std::uint64_t e0, std::uint64_t e1, std::uint64_t e2, std::uint64_t e3, std::uint64_t e4, std::uint64_t e5, std::uint64_t e6, std::uint64_t e7
	)
	{
		return _mm512_set_epi64(e0, e1, e2, e3, e4, e5, e6, e7);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 setr_u64x8
	(
		std::uint64_t e0, std::uint64_t e1, std::uint64_t e2, std::uint64_t e3, std::uint64_t e4, std::uint64_t e5, std::uint64_t e6, std::uint64_t e7
	)
	{
		return _mm512_setr_epi64(e0, e1, e2, e3, e4, e5, e6, e7);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 set1_u64x8(std::uint64_t all_)
	{
		return _mm512_set1_epi64(all_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 load_u64x8(const std::uint64_t* p_to_load_)
	{
		return _mm512_load_si512(p_to_load_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 setzero_u64x8()
	{
		return _mm512_setzero_si512();
	}
#pragma endregion

#pragma region STORES
	EMU_SIMD_COMMON_FUNC_SPEC void store_u64x8(std::uint64_t* p_out_, u64x8_arg a_)
	{
		_mm512_store_si512(reinterpret_cast<__m256i*>(p_out_), a_);
	}
#pragma endregion

#pragma region CASTS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 cast_f32x4_u64x8(f32x4_arg a_)
	{
		return _mm512_castsi128_si512(_mm_castps_si128(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 cast_f32x8_u64x8(f32x8_arg a_)
	{
		return _mm512_castsi256_si512(_mm256_castps_si256(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 cast_f32x16_u64x8(f32x16_arg a_)
	{
		return _mm512_castps_si512(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 cast_f64x2_u64x8(f64x2_arg a_)
	{
		return _mm512_castsi128_si512(_mm_castpd_si128(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 cast_f64x4_u64x8(f64x4_arg a_)
	{
		return _mm512_castsi256_si512(_mm256_castpd_si256(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 cast_f64x8_u64x8(f64x8_arg a_)
	{
		return _mm512_castpd_si512(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 cast_i8x16_u64x8(i8x16_arg a_)
	{
		return _mm512_castsi128_si512(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 cast_i16x8_u64x8(i16x8_arg a_)
	{
		return _mm512_castsi128_si512(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 cast_i32x4_u64x8(i32x4_arg a_)
	{
		return _mm512_castsi128_si512(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 cast_i64x2_u64x8(i64x2_arg a_)
	{
		return _mm512_castsi128_si512(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 cast_i8x32_u64x8(i8x32_arg a_)
	{
		return _mm512_castsi256_si512(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 cast_i16x16_u64x8(i16x16_arg a_)
	{
		return _mm512_castsi256_si512(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 cast_i32x8_u64x8(i32x8_arg a_)
	{
		return _mm512_castsi256_si512(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 cast_i64x4_u64x8(i64x4_arg a_)
	{
		return _mm512_castsi256_si512(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 cast_i8x64_u64x8(i8x64_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 cast_i16x32_u64x8(i16x32_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 cast_i32x16_u64x8(i32x16_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 cast_i64x8_u64x8(i64x8_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 cast_u8x16_u64x8(u8x16_arg a_)
	{
		return _mm512_castsi128_si512(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 cast_u16x8_u64x8(u16x8_arg a_)
	{
		return _mm512_castsi128_si512(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 cast_u32x4_u64x8(u32x4_arg a_)
	{
		return _mm512_castsi128_si512(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 cast_u64x2_u64x8(u64x2_arg a_)
	{
		return _mm512_castsi128_si512(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 cast_u8x32_u64x8(u8x32_arg a_)
	{
		return _mm512_castsi256_si512(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 cast_u16x16_u64x8(u16x16_arg a_)
	{
		return _mm512_castsi256_si512(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 cast_u32x8_u64x8(u32x8_arg a_)
	{
		return _mm512_castsi256_si512(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 cast_u64x4_u64x8(u64x4_arg a_)
	{
		return _mm512_castsi256_si512(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 cast_u8x64_u64x8(u8x64_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 cast_u16x32_u64x8(u16x32_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 cast_u32x16_u64x8(u32x16_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 cast_u64x8_u64x8(u64x8_arg a_)
	{
		return a_;
	}
#pragma endregion

#pragma region CONVERSIONS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 cvt_f32x4_u64x8(f32x4_arg a_)
	{
		return _mm512_castsi128_si512(_mm_cvtps_epi64(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 cvt_f32x8_u64x8(f32x8_arg a_)
	{
		return _mm512_cvtps_epi64(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 cvt_f32x16_u64x8(f32x16_arg a_)
	{
		return _mm512_cvtps_epi64(_mm512_castps512_ps256(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 cvt_f64x2_u64x8(f64x2_arg a_)
	{
		return _mm512_castsi128_si512(_mm_cvtpd_epi64(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 cvt_f64x4_u64x8(f64x4_arg a_)
	{
		return _mm512_castsi256_si512(_mm256_cvtpd_epi64(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 cvt_f64x8_u64x8(f64x8_arg a_)
	{
		return _mm512_cvtpd_epi64(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 cvt_i8x16_u64x8(i8x16_arg a_)
	{
		return _mm512_cvtepi8_epi64(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 cvt_i16x8_u64x8(i16x8_arg a_)
	{
		return _mm512_cvtepi16_epi64(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 cvt_i32x4_u64x8(i32x4_arg a_)
	{
		return _mm512_castsi256_si512(_mm256_cvtepi32_epi64(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 cvt_i64x2_u64x8(i64x2_arg a_)
	{
		return _mm512_castsi128_si512(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 cvt_i8x32_u64x8(i8x32_arg a_)
	{
		return _mm512_cvtepi8_epi64(_mm256_castsi256_si128(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 cvt_i16x16_u64x8(i16x16_arg a_)
	{
		return _mm512_cvtepi16_epi64(_mm256_castsi256_si128(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 cvt_i32x8_u64x8(i32x8_arg a_)
	{
		return _mm512_castsi256_si512(_mm256_cvtepi32_epi64(_mm256_castsi256_si128(a_)));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 cvt_i64x4_u64x8(i64x4_arg a_)
	{
		return _mm512_castsi256_si512(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 cvt_i8x64_u64x8(i8x64_arg a_)
	{
		return _mm512_cvtepi8_epi64(_mm512_castsi512_si128(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 cvt_i16x32_u64x8(i16x32_arg a_)
	{
		return _mm512_cvtepi16_epi64(_mm512_castsi512_si128(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 cvt_i32x16_u64x8(i32x16_arg a_)
	{
		return _mm512_cvtepi32_epi64(_mm512_castsi512_si256(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 cvt_i64x8_u64x8(i64x8_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 cvt_u8x16_u64x8(u8x16_arg a_)
	{
		return _mm512_cvtepi8_epi64(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 cvt_u16x8_u64x8(u16x8_arg a_)
	{
		return _mm512_cvtepi16_epi64(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 cvt_u32x4_u64x8(u32x4_arg a_)
	{
		return _mm512_castsi256_si512(_mm256_cvtepi32_epi64(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 cvt_u64x2_u64x8(u64x2_arg a_)
	{
		return _mm512_castsi128_si512(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 cvt_u8x32_u64x8(u8x32_arg a_)
	{
		return _mm512_cvtepi8_epi64(_mm256_castsi256_si128(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 cvt_u16x16_u64x8(u16x16_arg a_)
	{
		return _mm512_cvtepi16_epi64(_mm256_castsi256_si128(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 cvt_u32x8_u64x8(u32x8_arg a_)
	{
		return _mm512_castsi256_si512(_mm256_cvtepi32_epi64(_mm256_castsi256_si128(a_)));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 cvt_u64x4_u64x8(u64x4_arg a_)
	{
		return _mm512_castsi256_si512(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 cvt_u8x64_u64x8(u8x64_arg a_)
	{
		return _mm512_cvtepi8_epi64(_mm512_castsi512_si128(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 cvt_u16x32_u64x8(u16x32_arg a_)
	{
		return _mm512_cvtepi16_epi64(_mm512_castsi512_si128(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 cvt_u32x16_u64x8(u32x16_arg a_)
	{
		return _mm512_cvtepi32_epi64(_mm512_castsi512_si256(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 cvt_u64x8_u64x8(u64x8_arg a_)
	{
		return a_;
	}
#pragma endregion

#pragma region BASIC_ARITHMETIC
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 mul_all_u64x8(EmuSIMD::u64x8_arg lhs_, EmuSIMD::u64x8_arg rhs_)
	{
		return _mm512_mullo_epi64(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 negate_u64x8(EmuSIMD::u64x8_arg to_negate_)
	{
		return _mm512_sub_epi64(_mm512_setzero_si512(), to_negate_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 add_u64x8(EmuSIMD::u64x8_arg lhs_, EmuSIMD::u64x8_arg rhs_)
	{
		return _mm512_add_epi64(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 sub_u64x8(EmuSIMD::u64x8_arg lhs_, EmuSIMD::u64x8_arg rhs_)
	{
		return _mm512_sub_epi64(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 mul_u64x8(EmuSIMD::u64x8_arg lhs_, EmuSIMD::u64x8_arg rhs_)
	{
		return _mm512_mullo_epi64(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 div_u64x8(EmuSIMD::u64x8_arg lhs_, EmuSIMD::u64x8_arg rhs_)
	{
		return _mm512_div_epu64(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 addsub_u64x8(EmuSIMD::u64x8_arg lhs_, EmuSIMD::u64x8_arg rhs_)
	{
		constexpr std::uint64_t bytes_mask = static_cast<std::uint64_t>(0xFFFFFFFFFFFFFFFF);
		const EmuSIMD::u64x8 mask = _mm512_set_epi64(bytes_mask, 0, bytes_mask, 0, bytes_mask, 0, bytes_mask, 0);
		EmuSIMD::u64x8 out = _mm512_add_epi64(lhs_, _mm512_and_si512(mask, rhs_));
		return _mm512_sub_epi64(lhs_, _mm512_andnot_si512(mask, rhs_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 subadd_u64x8(EmuSIMD::u64x8_arg lhs_, EmuSIMD::u64x8_arg rhs_)
	{
		constexpr std::uint64_t bytes_mask = static_cast<std::uint64_t>(0xFFFFFFFFFFFFFFFF);
		const EmuSIMD::u64x8 mask = _mm512_set_epi64(bytes_mask, 0, bytes_mask, 0, bytes_mask, 0, bytes_mask, 0);
		EmuSIMD::u64x8 out = _mm512_sub_epi64(lhs_, _mm512_and_si512(mask, rhs_));
		return _mm512_add_epi64(lhs_, _mm512_andnot_si512(mask, rhs_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 fmadd_u64x8(EmuSIMD::u64x8_arg a_, EmuSIMD::u64x8_arg b_, EmuSIMD::u64x8_arg c_)
	{
		return _mm512_add_epi64(mul_all_u64x8(a_, b_), c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 fmsub_u64x8(EmuSIMD::u64x8_arg a_, EmuSIMD::u64x8_arg b_, EmuSIMD::u64x8_arg c_)
	{
		return _mm512_sub_epi64(mul_all_u64x8(a_, b_), c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 fnmadd_u64x8(EmuSIMD::u64x8_arg a_, EmuSIMD::u64x8_arg b_, EmuSIMD::u64x8_arg c_)
	{
		return _mm512_add_epi64(mul_all_u64x8(negate_u64x8(a_), b_), c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 fnmsub_u64x8(EmuSIMD::u64x8_arg a_, EmuSIMD::u64x8_arg b_, EmuSIMD::u64x8_arg c_)
	{
		return _mm512_sub_epi64(mul_all_u64x8(negate_u64x8(a_), b_), c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 fmaddsub_u64x8(EmuSIMD::u64x8_arg a_, EmuSIMD::u64x8_arg b_, EmuSIMD::u64x8_arg c_)
	{
		return addsub_u64x8(mul_all_u64x8(a_, b_), c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 fmsubadd_u64x8(EmuSIMD::u64x8_arg a_, EmuSIMD::u64x8_arg b_, EmuSIMD::u64x8_arg c_)
	{
		return subadd_u64x8(mul_all_u64x8(a_, b_), c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 floor_u64x8(EmuSIMD::u64x8_arg to_floor_)
	{
		return to_floor_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 ceil_u64x8(EmuSIMD::u64x8_arg to_ceil_)
	{
		return to_ceil_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 trunc_u64x8(EmuSIMD::u64x8_arg to_trunc_)
	{
		return to_trunc_;
	}

	template<int RoundingFlag_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 round_u64x8(EmuSIMD::u64x8_arg to_round_)
	{
		return to_round_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 mod_u64x8(EmuSIMD::u64x8_arg lhs_, EmuSIMD::u64x8_arg rhs_)
	{
		return _mm512_rem_epu64(lhs_, rhs_);
	}
#pragma endregion
}

#endif
