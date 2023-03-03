#ifndef EMU_SIMD_GENERIC_FUNCS_U32X4_H_INC_
#define EMU_SIMD_GENERIC_FUNCS_U32X4_H_INC_ 1

#include "_common_generic_func_helpers.h"
#include "_f32x4.h"

namespace EmuSIMD::Funcs
{
#pragma region SETTERS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x4 set_u32x4(std::uint32_t e0, std::uint32_t e1, std::uint32_t e2, std::uint32_t e3)
	{
		return _mm_set_epi32(e0, e1, e2, e3);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x4 setr_u32x4(std::uint32_t e0, std::uint32_t e1, std::uint32_t e2, std::uint32_t e3)
	{
		return _mm_setr_epi32(e0, e1, e2, e3);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x4 set1_u32x4(std::uint32_t all_)
	{
		return _mm_set1_epi32(all_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x4 load_u32x4(const std::uint32_t* p_to_load_)
	{
		return _mm_load_si128(reinterpret_cast<const __m128i*>(p_to_load_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x4 setzero_u32x4()
	{
		return _mm_setzero_si128();
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x4 setmasked_u32x4(std::uint8_t bit_mask_)
	{
		constexpr std::uint32_t element_mask = static_cast<std::uint32_t>(0xFFFFFFFF);
		return _mm_set_epi32
		(
			(bit_mask_ & 0x01) * element_mask,
			((bit_mask_ & 0x02) >> 1) * element_mask,
			((bit_mask_ & 0x04) >> 2) * element_mask,
			((bit_mask_ & 0x08) >> 3) * element_mask
		);
	}
#pragma endregion

#pragma region STORES
	EMU_SIMD_COMMON_FUNC_SPEC void store_u32x4(std::uint32_t* p_out_, u32x4_arg a_)
	{
		_mm_store_si128(reinterpret_cast<__m128i*>(p_out_), a_);
	}
#pragma endregion

#pragma region CASTS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x4 cast_f32x4_u32x4(f32x4_arg a_)
	{
		return _mm_castps_si128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x4 cast_f32x8_u32x4(f32x8_arg a_)
	{
		return _mm256_castsi256_si128(_mm256_castps_si256(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x4 cast_f32x16_u32x4(f32x16_arg a_)
	{
		return _mm512_castsi512_si128(_mm512_castps_si512(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x4 cast_f64x2_u32x4(f64x2_arg a_)
	{
		return _mm_castpd_si128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x4 cast_f64x4_u32x4(f64x4_arg a_)
	{
		return _mm256_castsi256_si128(_mm256_castpd_si256(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x4 cast_f64x8_u32x4(f64x8_arg a_)
	{
		return _mm512_castsi512_si128(_mm512_castpd_si512(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x4 cast_i8x16_u32x4(i8x16_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x4 cast_i16x8_u32x4(i16x8_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x4 cast_i32x4_u32x4(i32x4_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x4 cast_i64x2_u32x4(i64x2_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x4 cast_i8x32_u32x4(i8x32_arg a_)
	{
		return _mm256_castsi256_si128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x4 cast_i16x16_u32x4(i16x16_arg a_)
	{
		return _mm256_castsi256_si128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x4 cast_i32x8_u32x4(i32x8_arg a_)
	{
		return _mm256_castsi256_si128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x4 cast_i64x4_u32x4(i64x4_arg a_)
	{
		return _mm256_castsi256_si128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x4 cast_i8x64_u32x4(i8x64_arg a_)
	{
		return _mm512_castsi512_si128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x4 cast_i16x32_u32x4(i16x32_arg a_)
	{
		return _mm512_castsi512_si128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x4 cast_i32x16_u32x4(i32x16_arg a_)
	{
		return _mm512_castsi512_si128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x4 cast_i64x8_u32x4(i64x8_arg a_)
	{
		return _mm512_castsi512_si128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x4 cast_u8x16_u32x4(u8x16_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x4 cast_u16x8_u32x4(u16x8_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x4 cast_u32x4_u32x4(u32x4_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x4 cast_u64x2_u32x4(u64x2_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x4 cast_u8x32_u32x4(u8x32_arg a_)
	{
		return _mm256_castsi256_si128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x4 cast_u16x16_u32x4(u16x16_arg a_)
	{
		return _mm256_castsi256_si128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x4 cast_u32x8_u32x4(u32x8_arg a_)
	{
		return _mm256_castsi256_si128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x4 cast_u64x4_u32x4(u64x4_arg a_)
	{
		return _mm256_castsi256_si128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x4 cast_u8x64_u32x4(u8x64_arg a_)
	{
		return _mm512_castsi512_si128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x4 cast_u16x32_u32x4(u16x32_arg a_)
	{
		return _mm512_castsi512_si128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x4 cast_u32x16_u32x4(u32x16_arg a_)
	{
		return _mm512_castsi512_si128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x4 cast_u64x8_u32x4(u64x8_arg a_)
	{
		return _mm512_castsi512_si128(a_);
	}
#pragma endregion

#pragma region CONVERSIONS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x4 cvt_f32x4_u32x4(f32x4_arg a_)
	{
		return _mm_cvtps_epi32(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x4 cvt_f32x8_u32x4(f32x8_arg a_)
	{
		return _mm_cvtps_epi32(_mm256_castps256_ps128(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x4 cvt_f32x16_u32x4(f32x16_arg a_)
	{
		return _mm_cvtps_epi32(_mm512_castps512_ps128(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x4 cvt_f64x2_u32x4(f64x2_arg a_)
	{
		return _mm_cvtpd_epi32(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x4 cvt_f64x4_u32x4(f64x4_arg a_)
	{
		return _mm256_cvtpd_epi32(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x4 cvt_f64x8_u32x4(f64x8_arg a_)
	{
		return _mm256_cvtpd_epi32(_mm512_castpd512_pd256(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x4 cvt_i8x16_u32x4(i8x16_arg a_)
	{
		return _mm_cvtepi8_epi32(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x4 cvt_i16x8_u32x4(i16x8_arg a_)
	{
		return _mm_cvtepi16_epi32(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x4 cvt_i32x4_u32x4(i32x4_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x4 cvt_i64x2_u32x4(i64x2_arg a_)
	{
		return _mm_cvtepi64_epi32(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x4 cvt_i8x32_u32x4(i8x32_arg a_)
	{
		return _mm_cvtepi8_epi32(_mm256_castsi256_si128(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x4 cvt_i16x16_u32x4(i16x16_arg a_)
	{
		return _mm_cvtepi16_epi32(_mm256_castsi256_si128(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x4 cvt_i32x8_u32x4(i32x8_arg a_)
	{
		return _mm256_castsi256_si128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x4 cvt_i64x4_u32x4(i64x4_arg a_)
	{
		return _mm256_cvtepi64_epi32(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x4 cvt_i8x64_u32x4(i8x64_arg a_)
	{
		return _mm_cvtepi8_epi32(_mm512_castsi512_si128(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x4 cvt_i16x32_u32x4(i16x32_arg a_)
	{
		return _mm_cvtepi16_epi32(_mm512_castsi512_si128(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x4 cvt_i32x16_u32x4(i32x16_arg a_)
	{
		return _mm512_castsi512_si128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x4 cvt_i64x8_u32x4(i64x8_arg a_)
	{
		return _mm256_cvtepi64_epi32(_mm512_castsi512_si256(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x4 cvt_u8x16_u32x4(u8x16_arg a_)
	{
		return _mm_cvtepi8_epi32(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x4 cvt_u16x8_u32x4(u16x8_arg a_)
	{
		return _mm_cvtepi16_epi32(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x4 cvt_u32x4_u32x4(u32x4_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x4 cvt_u64x2_u32x4(u64x2_arg a_)
	{
		return _mm_cvtepi64_epi32(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x4 cvt_u8x32_u32x4(u8x32_arg a_)
	{
		return _mm_cvtepi8_epi32(_mm256_castsi256_si128(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x4 cvt_u16x16_u32x4(u16x16_arg a_)
	{
		return _mm_cvtepi16_epi32(_mm256_castsi256_si128(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x4 cvt_u32x8_u32x4(u32x8_arg a_)
	{
		return _mm256_castsi256_si128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x4 cvt_u64x4_u32x4(u64x4_arg a_)
	{
		return _mm256_cvtepi64_epi32(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x4 cvt_u8x64_u32x4(u8x64_arg a_)
	{
		return _mm_cvtepi8_epi32(_mm512_castsi512_si128(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x4 cvt_u16x32_u32x4(u16x32_arg a_)
	{
		return _mm_cvtepi16_epi32(_mm512_castsi512_si128(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x4 cvt_u32x16_u32x4(u32x16_arg a_)
	{
		return _mm512_castsi512_si128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x4 cvt_u64x8_u32x4(u64x8_arg a_)
	{
		return _mm256_cvtepi64_epi32(_mm512_castsi512_si256(a_));
	}
#pragma endregion

#pragma region TEMPLATES
	/// <summary>
	/// <para> Template helper for performing a floating-point operation on an integral register. The floating-point operation is provided by Func_. </para>
	/// <para>
	///		The used floating-point register is the first with element width greater than or equal to the width of elements in the integer register. 
	///		The full width of the registers will match fully. 
	/// </para>
	/// </summary>
	/// <param name="func_">Floating-point function to execute.</param>
	/// <param name="in_">Integral register to emulate the fp operation with.</param>
	/// <returns>The results of the floating-point operation with the provided register elements.</returns>
	template<class Func_>
	EMU_SIMD_COMMON_FUNC_SPEC auto emulate_fp_u32x4(Func_ func_, EmuSIMD::u32x4_arg in_)
		-> std::enable_if_t<std::is_invocable_r_v<EmuSIMD::f32x4, decltype(func_), EmuSIMD::f32x4>, EmuSIMD::u32x4>
	{
		return cvt_f32x4_u32x4
		(
			func_(cvt_u32x4_f32x4(in_))
		);
	}
#pragma endregion

#pragma region COMPARISONS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x4 cmpeq_u32x4(EmuSIMD::u32x4_arg lhs_, EmuSIMD::u32x4_arg rhs_)
	{
		return _mm_cmpeq_epi32(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x4 cmpneq_u32x4(EmuSIMD::u32x4_arg lhs_, EmuSIMD::u32x4_arg rhs_)
	{
		constexpr std::uint32_t mask = static_cast<std::uint32_t>(0xFFFFFFFF);
		return _mm_xor_si128(set1_u32x4(mask), _mm_cmpeq_epi32(lhs_, rhs_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x4 cmpgt_u32x4(EmuSIMD::u32x4_arg lhs_, EmuSIMD::u32x4_arg rhs_)
	{
		constexpr std::uint32_t mask = static_cast<std::uint32_t>(0xFFFFFFFF);
		return _mm_andnot_si128(_mm_cmpeq_epi32(_mm_min_epu32(lhs_, rhs_), lhs_), set1_u32x4(mask));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x4 cmplt_u32x4(EmuSIMD::u32x4_arg lhs_, EmuSIMD::u32x4_arg rhs_)
	{
		constexpr std::uint32_t mask = static_cast<std::uint32_t>(0xFFFFFFFF);
		return _mm_andnot_si128(_mm_cmpeq_epi32(_mm_max_epu32(lhs_, rhs_), lhs_), set1_u32x4(mask));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x4 cmpge_u32x4(EmuSIMD::u32x4_arg lhs_, EmuSIMD::u32x4_arg rhs_)
	{
		return _mm_cmpeq_epi32(_mm_max_epu32(lhs_, rhs_), lhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x4 cmple_u32x4(EmuSIMD::u32x4_arg lhs_, EmuSIMD::u32x4_arg rhs_)
	{
		return _mm_cmpeq_epi32(_mm_min_epu32(lhs_, rhs_), lhs_);
	}
#pragma endregion

#pragma region BASIC_ARITHMETIC
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x4 mul_all_u32x4(EmuSIMD::u32x4_arg lhs_, EmuSIMD::u32x4_arg rhs_)
	{
		return _mm_mullo_epi32(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x4 negate_u32x4(EmuSIMD::u32x4_arg to_negate_)
	{
		return _mm_sub_epi32(_mm_setzero_si128(), to_negate_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x4 add_u32x4(EmuSIMD::u32x4_arg lhs_, EmuSIMD::u32x4_arg rhs_)
	{
		return _mm_add_epi32(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x4 sub_u32x4(EmuSIMD::u32x4_arg lhs_, EmuSIMD::u32x4_arg rhs_)
	{
		return _mm_sub_epi32(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x4 mul_u32x4(EmuSIMD::u32x4_arg lhs_, EmuSIMD::u32x4_arg rhs_)
	{
		return _mm_mul_epu32(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x4 div_u32x4(EmuSIMD::u32x4_arg lhs_, EmuSIMD::u32x4_arg rhs_)
	{
		return _mm_div_epu32(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x4 addsub_u32x4(EmuSIMD::u32x4_arg lhs_, EmuSIMD::u32x4_arg rhs_)
	{
		constexpr std::uint32_t bytes_mask = static_cast<std::uint32_t>(0xFFFFFFFF);
		const EmuSIMD::u32x4 mask = _mm_set_epi32(bytes_mask, 0, bytes_mask, 0);
		EmuSIMD::u32x4 out = _mm_add_epi32(lhs_, _mm_and_si128(mask, rhs_));
		return _mm_sub_epi32(lhs_, _mm_andnot_si128(mask, rhs_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x4 subadd_u32x4(EmuSIMD::u32x4_arg lhs_, EmuSIMD::u32x4_arg rhs_)
	{
		constexpr std::uint32_t bytes_mask = static_cast<std::uint32_t>(0xFFFFFFFF);
		const EmuSIMD::u32x4 mask = _mm_set_epi32(bytes_mask, 0, bytes_mask, 0);
		EmuSIMD::u32x4 out = _mm_sub_epi32(lhs_, _mm_and_si128(mask, rhs_));
		return _mm_add_epi32(lhs_, _mm_andnot_si128(mask, rhs_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x4 fmadd_u32x4(EmuSIMD::u32x4_arg a_, EmuSIMD::u32x4_arg b_, EmuSIMD::u32x4_arg c_)
	{
		return _mm_add_epi32(mul_all_u32x4(a_, b_), c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x4 fmsub_u32x4(EmuSIMD::u32x4_arg a_, EmuSIMD::u32x4_arg b_, EmuSIMD::u32x4_arg c_)
	{
		return _mm_sub_epi32(mul_all_u32x4(a_, b_), c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x4 fnmadd_u32x4(EmuSIMD::u32x4_arg a_, EmuSIMD::u32x4_arg b_, EmuSIMD::u32x4_arg c_)
	{
		return _mm_add_epi32(mul_all_u32x4(negate_u32x4(a_), b_), c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x4 fnmsub_u32x4(EmuSIMD::u32x4_arg a_, EmuSIMD::u32x4_arg b_, EmuSIMD::u32x4_arg c_)
	{
		return _mm_sub_epi32(mul_all_u32x4(negate_u32x4(a_), b_), c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x4 fmaddsub_u32x4(EmuSIMD::u32x4_arg a_, EmuSIMD::u32x4_arg b_, EmuSIMD::u32x4_arg c_)
	{
		return addsub_u32x4(mul_all_u32x4(a_, b_), c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x4 fmsubadd_u32x4(EmuSIMD::u32x4_arg a_, EmuSIMD::u32x4_arg b_, EmuSIMD::u32x4_arg c_)
	{
		return subadd_u32x4(mul_all_u32x4(a_, b_), c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x4 floor_u32x4(EmuSIMD::u32x4_arg to_floor_)
	{
		return to_floor_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x4 ceil_u32x4(EmuSIMD::u32x4_arg to_ceil_)
	{
		return to_ceil_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x4 trunc_u32x4(EmuSIMD::u32x4_arg to_trunc_)
	{
		return to_trunc_;
	}

	template<int RoundingFlag_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x4 round_u32x4(EmuSIMD::u32x4_arg to_round_)
	{
		return to_round_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x4 mod_u32x4(EmuSIMD::u32x4_arg lhs_, EmuSIMD::u32x4_arg rhs_)
	{
		return _mm_rem_epu32(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x4 abs_u32x4(EmuSIMD::u32x4_arg in_)
	{
		return in_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x4 sqrt_u32x4(EmuSIMD::u32x4_arg in_)
	{
		return emulate_fp_u32x4([](EmuSIMD::f32x4_arg in_fp_) { return sqrt_f32x4(in_fp_); }, in_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x4 rsqrt_u32x4(EmuSIMD::u32x4_arg in_)
	{
		return emulate_fp_u32x4([](EmuSIMD::f32x4_arg in_fp_) { return rsqrt_f32x4(in_fp_); }, in_);
	}
#pragma endregion

#pragma region NEAR_COMPARISONS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x4 cmpnear_u32x4(EmuSIMD::u32x4_arg lhs_, EmuSIMD::u32x4_arg rhs_)
	{
		return cmpeq_u32x4(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x4 cmpnear_u32x4(EmuSIMD::u32x4_arg lhs_, EmuSIMD::u32x4_arg rhs_, EmuSIMD::u32x4_arg epsilon)
	{
		return cmple_u32x4(sub_u32x4(lhs_, rhs_), epsilon);
	}
#pragma endregion

#pragma region TRIG
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x4 cos_u32x4(EmuSIMD::u32x4_arg in_)
	{
		return emulate_fp_u32x4([](EmuSIMD::f32x4_arg in_fp_) { return cos_f32x4(in_fp_); }, in_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x4 sin_u32x4(EmuSIMD::u32x4_arg in_)
	{
		return emulate_fp_u32x4([](EmuSIMD::f32x4_arg in_fp_) { return sin_f32x4(in_fp_); }, in_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x4 tan_u32x4(EmuSIMD::u32x4_arg in_)
	{
		return emulate_fp_u32x4([](EmuSIMD::f32x4_arg in_fp_) { return tan_f32x4(in_fp_); }, in_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x4 acos_u32x4(EmuSIMD::u32x4_arg in_)
	{
		return emulate_fp_u32x4([](EmuSIMD::f32x4_arg in_fp_) { return acos_f32x4(in_fp_); }, in_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x4 asin_u32x4(EmuSIMD::u32x4_arg in_)
	{
		return emulate_fp_u32x4([](EmuSIMD::f32x4_arg in_fp_) { return asin_f32x4(in_fp_); }, in_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x4 atan_u32x4(EmuSIMD::u32x4_arg in_)
	{
		return emulate_fp_u32x4([](EmuSIMD::f32x4_arg in_fp_) { return atan_f32x4(in_fp_); }, in_);
	}
#pragma endregion
}

#endif
