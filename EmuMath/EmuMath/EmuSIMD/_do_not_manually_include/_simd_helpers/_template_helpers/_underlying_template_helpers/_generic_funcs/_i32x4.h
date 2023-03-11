#ifndef EMU_SIMD_GENERIC_FUNCS_I32X4_H_INC_
#define EMU_SIMD_GENERIC_FUNCS_I32X4_H_INC_ 1

#include "_common_generic_func_helpers.h"
#include "_f32x4.h"

namespace EmuSIMD::Funcs
{
#pragma region SETTERS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 set_i32x4(std::int32_t e0, std::int32_t e1, std::int32_t e2, std::int32_t e3)
	{
		return _mm_set_epi32(e0, e1, e2, e3);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 setr_i32x4(std::int32_t e0, std::int32_t e1, std::int32_t e2, std::int32_t e3)
	{
		return _mm_setr_epi32(e0, e1, e2, e3);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 set1_i32x4(std::int32_t all_)
	{
		return _mm_set1_epi32(all_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 load_i32x4(const std::int32_t* p_to_load_)
	{
		return _mm_load_si128(reinterpret_cast<const __m128i*>(p_to_load_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 setzero_i32x4()
	{
		return _mm_setzero_si128();
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 setmasked_i32x4(std::uint8_t bit_mask_)
	{
		constexpr std::int32_t element_mask = static_cast<std::int32_t>(0xFFFFFFFF);
		return _mm_set_epi32
		(
			(bit_mask_ &  0x01) * element_mask,
			((bit_mask_ & 0x02) >> 1) * element_mask,
			((bit_mask_ & 0x04) >> 2) * element_mask,
			((bit_mask_ & 0x08) >> 3) * element_mask
		);
	}
#pragma endregion

#pragma region STORES
	EMU_SIMD_COMMON_FUNC_SPEC void store_i32x4(std::int32_t* p_out_, i32x4_arg a_)
	{
		_mm_store_si128(reinterpret_cast<__m128i*>(p_out_), a_);
	}
#pragma endregion

#pragma region CASTS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cast_f32x4_i32x4(f32x4_arg a_)
	{
		return _mm_castps_si128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cast_f32x8_i32x4(f32x8_arg a_)
	{
		return _mm256_castsi256_si128(_mm256_castps_si256(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cast_f32x16_i32x4(f32x16_arg a_)
	{
		return _mm512_castsi512_si128(_mm512_castps_si512(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cast_f64x2_i32x4(f64x2_arg a_)
	{
		return _mm_castpd_si128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cast_f64x4_i32x4(f64x4_arg a_)
	{
		return _mm256_castsi256_si128(_mm256_castpd_si256(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cast_f64x8_i32x4(f64x8_arg a_)
	{
		return _mm512_castsi512_si128(_mm512_castpd_si512(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cast_i8x16_i32x4(i8x16_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cast_i16x8_i32x4(i16x8_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cast_i32x4_i32x4(i32x4_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cast_i64x2_i32x4(i64x2_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cast_i8x32_i32x4(i8x32_arg a_)
	{
		return _mm256_castsi256_si128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cast_i16x16_i32x4(i16x16_arg a_)
	{
		return _mm256_castsi256_si128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cast_i32x8_i32x4(i32x8_arg a_)
	{
		return _mm256_castsi256_si128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cast_i64x4_i32x4(i64x4_arg a_)
	{
		return _mm256_castsi256_si128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cast_i8x64_i32x4(i8x64_arg a_)
	{
		return _mm512_castsi512_si128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cast_i16x32_i32x4(i16x32_arg a_)
	{
		return _mm512_castsi512_si128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cast_i32x16_i32x4(i32x16_arg a_)
	{
		return _mm512_castsi512_si128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cast_i64x8_i32x4(i64x8_arg a_)
	{
		return _mm512_castsi512_si128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cast_u8x16_i32x4(u8x16_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cast_u16x8_i32x4(u16x8_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cast_u32x4_i32x4(u32x4_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cast_u64x2_i32x4(u64x2_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cast_u8x32_i32x4(u8x32_arg a_)
	{
		return _mm256_castsi256_si128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cast_u16x16_i32x4(u16x16_arg a_)
	{
		return _mm256_castsi256_si128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cast_u32x8_i32x4(u32x8_arg a_)
	{
		return _mm256_castsi256_si128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cast_u64x4_i32x4(u64x4_arg a_)
	{
		return _mm256_castsi256_si128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cast_u8x64_i32x4(u8x64_arg a_)
	{
		return _mm512_castsi512_si128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cast_u16x32_i32x4(u16x32_arg a_)
	{
		return _mm512_castsi512_si128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cast_u32x16_i32x4(u32x16_arg a_)
	{
		return _mm512_castsi512_si128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cast_u64x8_i32x4(u64x8_arg a_)
	{
		return _mm512_castsi512_si128(a_);
	}
#pragma endregion

#pragma region CONVERSIONS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cvt_f32x4_i32x4(f32x4_arg a_)
	{
		return _mm_cvtps_epi32(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cvt_f32x8_i32x4(f32x8_arg a_)
	{
		return _mm_cvtps_epi32(_mm256_castps256_ps128(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cvt_f32x16_i32x4(f32x16_arg a_)
	{
		return _mm_cvtps_epi32(_mm512_castps512_ps128(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cvt_f64x2_i32x4(f64x2_arg a_)
	{
		return _mm_cvtpd_epi32(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cvt_f64x4_i32x4(f64x4_arg a_)
	{
		return _mm256_cvtpd_epi32(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cvt_f64x8_i32x4(f64x8_arg a_)
	{
		return _mm256_cvtpd_epi32(_mm512_castpd512_pd256(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cvt_i8x16_i32x4(i8x16_arg a_)
	{
		return _mm_cvtepi8_epi32(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cvt_i16x8_i32x4(i16x8_arg a_)
	{
		return _mm_cvtepi16_epi32(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cvt_i32x4_i32x4(i32x4_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cvt_i64x2_i32x4(i64x2_arg a_)
	{
		return _mm_cvtepi64_epi32(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cvt_i8x32_i32x4(i8x32_arg a_)
	{
		return _mm_cvtepi8_epi32(_mm256_castsi256_si128(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cvt_i16x16_i32x4(i16x16_arg a_)
	{
		return _mm_cvtepi16_epi32(_mm256_castsi256_si128(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cvt_i32x8_i32x4(i32x8_arg a_)
	{
		return _mm256_castsi256_si128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cvt_i64x4_i32x4(i64x4_arg a_)
	{
		return _mm256_cvtepi64_epi32(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cvt_i8x64_i32x4(i8x64_arg a_)
	{
		return _mm_cvtepi8_epi32(_mm512_castsi512_si128(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cvt_i16x32_i32x4(i16x32_arg a_)
	{
		return _mm_cvtepi16_epi32(_mm512_castsi512_si128(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cvt_i32x16_i32x4(i32x16_arg a_)
	{
		return _mm512_castsi512_si128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cvt_i64x8_i32x4(i64x8_arg a_)
	{
		return _mm256_cvtepi64_epi32(_mm512_castsi512_si256(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cvt_u8x16_i32x4(u8x16_arg a_)
	{
		return _mm_cvtepu8_epi32(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cvt_u16x8_i32x4(u16x8_arg a_)
	{
		return _mm_cvtepu16_epi32(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cvt_u32x4_i32x4(u32x4_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cvt_u64x2_i32x4(u64x2_arg a_)
	{
		return _mm_cvtepi64_epi32(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cvt_u8x32_i32x4(u8x32_arg a_)
	{
		return _mm_cvtepu8_epi32(_mm256_castsi256_si128(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cvt_u16x16_i32x4(u16x16_arg a_)
	{
		return _mm_cvtepu16_epi32(_mm256_castsi256_si128(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cvt_u32x8_i32x4(u32x8_arg a_)
	{
		return _mm256_castsi256_si128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cvt_u64x4_i32x4(u64x4_arg a_)
	{
		return _mm256_cvtepi64_epi32(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cvt_u8x64_i32x4(u8x64_arg a_)
	{
		return _mm_cvtepu8_epi32(_mm512_castsi512_si128(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cvt_u16x32_i32x4(u16x32_arg a_)
	{
		return _mm_cvtepu16_epi32(_mm512_castsi512_si128(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cvt_u32x16_i32x4(u32x16_arg a_)
	{
		return _mm512_castsi512_si128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cvt_u64x8_i32x4(u64x8_arg a_)
	{
		return _mm256_cvtepi64_epi32(_mm512_castsi512_si256(a_));
	}
#pragma endregion

#pragma region COMPARISONS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cmpeq_i32x4(EmuSIMD::i32x4_arg lhs_, EmuSIMD::i32x4_arg rhs_)
	{
		return _mm_cmpeq_epi32(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cmpneq_i32x4(EmuSIMD::i32x4_arg lhs_, EmuSIMD::i32x4_arg rhs_)
	{
		constexpr std::int32_t mask = static_cast<std::int32_t>(0xFFFFFFFF);
		return _mm_xor_si128(set1_i32x4(mask), _mm_cmpeq_epi32(lhs_, rhs_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cmpgt_i32x4(EmuSIMD::i32x4_arg lhs_, EmuSIMD::i32x4_arg rhs_)
	{
		return _mm_cmpgt_epi32(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cmplt_i32x4(EmuSIMD::i32x4_arg lhs_, EmuSIMD::i32x4_arg rhs_)
	{
		return _mm_cmplt_epi32(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cmpge_i32x4(EmuSIMD::i32x4_arg lhs_, EmuSIMD::i32x4_arg rhs_)
	{
		return _mm_or_si128(_mm_cmpgt_epi32(lhs_, rhs_), _mm_cmpeq_epi32(lhs_, rhs_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cmple_i32x4(EmuSIMD::i32x4_arg lhs_, EmuSIMD::i32x4_arg rhs_)
	{
		return _mm_or_si128(_mm_cmplt_epi32(lhs_, rhs_), _mm_cmpeq_epi32(lhs_, rhs_));
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
	EMU_SIMD_COMMON_FUNC_SPEC auto emulate_fp_i32x4(Func_ func_, EmuSIMD::i32x4_arg in_)
		-> std::enable_if_t<std::is_invocable_r_v<EmuSIMD::f32x4, decltype(func_), EmuSIMD::f32x4>, EmuSIMD::i32x4>
	{
		return cvt_f32x4_i32x4
		(
			func_(cvt_i32x4_f32x4(in_))
		);
	}
#pragma endregion

#pragma region SHUFFLES
	template<EmuSIMD::Funcs::shuffle_mask_type ShuffleMask>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 shuffle_i32x4(EmuSIMD::i32x4_arg lhs_, EmuSIMD::i32x4_arg rhs_)
	{
		return cast_f32x4_i32x4(shuffle_f32x4<ShuffleMask>(cast_i32x4_f32x4(lhs_), cast_i32x4_f32x4(rhs_)));
	}

	template<EmuSIMD::Funcs::shuffle_mask_type ShuffleMask>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 permute_i32x4(EmuSIMD::i32x4_arg in_)
	{
		return _mm_shuffle_epi32(in_, ShuffleMask);
	}
#pragma endregion

#pragma region BITWISE_ARITHMETIC
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 and_i32x4(EmuSIMD::i32x4_arg lhs_, EmuSIMD::i32x4_arg rhs_)
	{
		return _mm_and_si128(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 or_i32x4(EmuSIMD::i32x4_arg lhs_, EmuSIMD::i32x4_arg rhs_)
	{
		return _mm_or_si128(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 xor_i32x4(EmuSIMD::i32x4_arg lhs_, EmuSIMD::i32x4_arg rhs_)
	{
		return _mm_xor_si128(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 andnot_i32x4(EmuSIMD::i32x4_arg not_lhs_, EmuSIMD::i32x4_arg rhs_)
	{
		return _mm_andnot_si128(not_lhs_, rhs_);
	}
#pragma endregion

#pragma region MINMAX_FUNCS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 min_i32x4(EmuSIMD::i32x4_arg a_, EmuSIMD::i32x4_arg b_)
	{
		return _mm_min_epi32(a_, b_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 max_i32x4(EmuSIMD::i32x4_arg a_, EmuSIMD::i32x4_arg b_)
	{
		return _mm_max_epi32(a_, b_);
	}
#pragma endregion

#pragma region MOVES
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 movehl_i32x4(EmuSIMD::i32x4_arg lhs_, EmuSIMD::i32x4_arg rhs_)
	{
		return cast_f32x4_i32x4(movehl_f32x4(cast_i32x4_f32x4(lhs_), cast_i32x4_f32x4(rhs_)));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 movelh_i32x4(EmuSIMD::i32x4_arg lhs_, EmuSIMD::i32x4_arg rhs_)
	{
		return cast_f32x4_i32x4(movelh_f32x4(cast_i32x4_f32x4(lhs_), cast_i32x4_f32x4(rhs_)));
	}
#pragma endregion

#pragma region BASIC_ARITHMETIC
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 mul_all_i32x4(EmuSIMD::i32x4_arg lhs_, EmuSIMD::i32x4_arg rhs_)
	{
		return _mm_mullo_epi32(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 negate_i32x4(EmuSIMD::i32x4_arg to_negate_)
	{
		return _mm_sub_epi32(_mm_setzero_si128(), to_negate_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 add_i32x4(EmuSIMD::i32x4_arg lhs_, EmuSIMD::i32x4_arg rhs_)
	{
		return _mm_add_epi32(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 sub_i32x4(EmuSIMD::i32x4_arg lhs_, EmuSIMD::i32x4_arg rhs_)
	{
		return _mm_sub_epi32(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 mul_i32x4(EmuSIMD::i32x4_arg lhs_, EmuSIMD::i32x4_arg rhs_)
	{
		return _mm_mul_epi32(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 div_i32x4(EmuSIMD::i32x4_arg lhs_, EmuSIMD::i32x4_arg rhs_)
	{
#if EMU_CORE_X86_X64_SVML
		return _mm_div_epi32(lhs_, rhs_);
#else
		EmuSIMD::f32x4 result_f32 = cvt_i32x4_f32x4(lhs_);
		result_f32 = div_f32x4(result_f32, cvt_i32x4_f32x4(rhs_));
		return cvt_f32x4_i32x4(trunc_f32x4(result_f32));
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 addsub_i32x4(EmuSIMD::i32x4_arg lhs_, EmuSIMD::i32x4_arg rhs_)
	{
		constexpr std::int32_t bytes_mask = static_cast<std::int32_t>(0xFFFFFFFF);
		const EmuSIMD::i32x4 mask = _mm_set_epi32(bytes_mask, 0, bytes_mask, 0);
		EmuSIMD::i32x4 out = _mm_add_epi32(lhs_, _mm_and_si128(mask, rhs_));
		return _mm_sub_epi32(lhs_, _mm_andnot_si128(mask, rhs_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 subadd_i32x4(EmuSIMD::i32x4_arg lhs_, EmuSIMD::i32x4_arg rhs_)
	{
		constexpr std::int32_t bytes_mask = static_cast<std::int32_t>(0xFFFFFFFF);
		const EmuSIMD::i32x4 mask = _mm_set_epi32(bytes_mask, 0, bytes_mask, 0);
		EmuSIMD::i32x4 out = _mm_sub_epi32(lhs_, _mm_and_si128(mask, rhs_));
		return _mm_add_epi32(lhs_, _mm_andnot_si128(mask, rhs_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 fmadd_i32x4(EmuSIMD::i32x4_arg a_, EmuSIMD::i32x4_arg b_, EmuSIMD::i32x4_arg c_)
	{
		return _mm_add_epi32(mul_all_i32x4(a_, b_), c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 fmsub_i32x4(EmuSIMD::i32x4_arg a_, EmuSIMD::i32x4_arg b_, EmuSIMD::i32x4_arg c_)
	{
		return _mm_sub_epi32(mul_all_i32x4(a_, b_), c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 fnmadd_i32x4(EmuSIMD::i32x4_arg a_, EmuSIMD::i32x4_arg b_, EmuSIMD::i32x4_arg c_)
	{
		return _mm_add_epi32(mul_all_i32x4(negate_i32x4(a_), b_), c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 fnmsub_i32x4(EmuSIMD::i32x4_arg a_, EmuSIMD::i32x4_arg b_, EmuSIMD::i32x4_arg c_)
	{
		return _mm_sub_epi32(mul_all_i32x4(negate_i32x4(a_), b_), c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 fmaddsub_i32x4(EmuSIMD::i32x4_arg a_, EmuSIMD::i32x4_arg b_, EmuSIMD::i32x4_arg c_)
	{
		return addsub_i32x4(mul_all_i32x4(a_, b_), c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 fmsubadd_i32x4(EmuSIMD::i32x4_arg a_, EmuSIMD::i32x4_arg b_, EmuSIMD::i32x4_arg c_)
	{
		return subadd_i32x4(mul_all_i32x4(a_, b_), c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 floor_i32x4(EmuSIMD::i32x4_arg to_floor_)
	{
		return to_floor_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 ceil_i32x4(EmuSIMD::i32x4_arg to_ceil_)
	{
		return to_ceil_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 trunc_i32x4(EmuSIMD::i32x4_arg to_trunc_)
	{
		return to_trunc_;
	}

	template<int RoundingFlag_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 round_i32x4(EmuSIMD::i32x4_arg to_round_)
	{
		return to_round_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 mod_i32x4(EmuSIMD::i32x4_arg lhs_, EmuSIMD::i32x4_arg rhs_)
	{
#if EMU_CORE_X86_X64_SVML
		return _mm_rem_epi32(lhs_, rhs_);
#else
		EmuSIMD::i32x4 to_subtract = div_i32x4(lhs_, rhs_);
		to_subtract = mul_all_i32x4(to_subtract, rhs_);
		return sub_i32x4(lhs_, to_subtract);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 abs_i32x4(EmuSIMD::i32x4_arg in_)
	{
		return _mm_abs_epi32(in_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 sqrt_i32x4(EmuSIMD::i32x4_arg in_)
	{
		return emulate_fp_i32x4([](EmuSIMD::f32x4_arg in_fp_) { return sqrt_f32x4(in_fp_); }, in_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 rsqrt_i32x4(EmuSIMD::i32x4_arg in_)
	{
		return emulate_fp_i32x4([](EmuSIMD::f32x4_arg in_fp_) { return rsqrt_f32x4(in_fp_); }, in_);
	}
#pragma endregion

#pragma region NEAR_COMPARISONS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cmpnear_i32x4(EmuSIMD::i32x4_arg lhs_, EmuSIMD::i32x4_arg rhs_)
	{
		return cmpeq_i32x4(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cmpnear_i32x4(EmuSIMD::i32x4_arg lhs_, EmuSIMD::i32x4_arg rhs_, EmuSIMD::i32x4_arg epsilon)
	{
		return cmple_i32x4(abs_i32x4(sub_i32x4(lhs_, rhs_)), epsilon);
	}
#pragma endregion

#pragma region TRIG
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cos_i32x4(EmuSIMD::i32x4_arg in_)
	{
		return emulate_fp_i32x4([](EmuSIMD::f32x4_arg in_fp_) { return cos_f32x4(in_fp_); }, in_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 sin_i32x4(EmuSIMD::i32x4_arg in_)
	{
		return emulate_fp_i32x4([](EmuSIMD::f32x4_arg in_fp_) { return sin_f32x4(in_fp_); }, in_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 tan_i32x4(EmuSIMD::i32x4_arg in_)
	{
		return emulate_fp_i32x4([](EmuSIMD::f32x4_arg in_fp_) { return tan_f32x4(in_fp_); }, in_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 acos_i32x4(EmuSIMD::i32x4_arg in_)
	{
		return emulate_fp_i32x4([](EmuSIMD::f32x4_arg in_fp_) { return acos_f32x4(in_fp_); }, in_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 asin_i32x4(EmuSIMD::i32x4_arg in_)
	{
		return emulate_fp_i32x4([](EmuSIMD::f32x4_arg in_fp_) { return asin_f32x4(in_fp_); }, in_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 atan_i32x4(EmuSIMD::i32x4_arg in_)
	{
		return emulate_fp_i32x4([](EmuSIMD::f32x4_arg in_fp_) { return atan_f32x4(in_fp_); }, in_);
	}
#pragma endregion
}

#endif
