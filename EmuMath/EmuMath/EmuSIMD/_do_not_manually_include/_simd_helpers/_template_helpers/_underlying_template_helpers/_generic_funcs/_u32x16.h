#ifndef EMU_SIMD_GENERIC_FUNCS_U32X16_H_INC_
#define EMU_SIMD_GENERIC_FUNCS_U32X16_H_INC_ 1

#include "_common_generic_func_helpers.h"
#include "_f32x16.h"

namespace EmuSIMD::Funcs
{
#pragma region SETTERS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 set_u32x16
	(
		std::uint32_t e0, std::uint32_t e1, std::uint32_t e2, std::uint32_t e3, std::uint32_t e4, std::uint32_t e5, std::uint32_t e6, std::uint32_t e7,
		std::uint32_t e8, std::uint32_t e9, std::uint32_t e10, std::uint32_t e11, std::uint32_t e12, std::uint32_t e13, std::uint32_t e14, std::uint32_t e15
	)
	{
		return _mm512_set_epi32(e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 setr_u32x16
	(
		std::uint32_t e0, std::uint32_t e1, std::uint32_t e2, std::uint32_t e3, std::uint32_t e4, std::uint32_t e5, std::uint32_t e6, std::uint32_t e7,
		std::uint32_t e8, std::uint32_t e9, std::uint32_t e10, std::uint32_t e11, std::uint32_t e12, std::uint32_t e13, std::uint32_t e14, std::uint32_t e15
	)
	{
		//return _mm512_setr_epi32(e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15);
		return _mm512_set_epi32(e15, e14, e13, e12, e11, e10, e9, e8, e7, e6, e5, e4, e3, e2, e1, e0);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 set1_u32x16(std::uint32_t all_)
	{
		return _mm512_set1_epi32(all_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 load_u32x16(const std::uint32_t* p_to_load_)
	{
		return _mm512_load_si512(p_to_load_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 setzero_u32x16()
	{
		return _mm512_setzero_si512();
	}
#pragma endregion

#pragma region STORES
	EMU_SIMD_COMMON_FUNC_SPEC void store_u32x16(std::uint32_t* p_out_, u32x16_arg a_)
	{
		_mm512_store_si512(reinterpret_cast<__m256i*>(p_out_), a_);
	}
#pragma endregion

#pragma region CASTS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cast_f32x4_u32x16(f32x4_arg a_)
	{
		return _mm512_castsi128_si512(_mm_castps_si128(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cast_f32x8_u32x16(f32x8_arg a_)
	{
		return _mm512_castsi256_si512(_mm256_castps_si256(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cast_f32x16_u32x16(f32x16_arg a_)
	{
		return _mm512_castps_si512(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cast_f64x2_u32x16(f64x2_arg a_)
	{
		return _mm512_castsi128_si512(_mm_castpd_si128(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cast_f64x4_u32x16(f64x4_arg a_)
	{
		return _mm512_castsi256_si512(_mm256_castpd_si256(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cast_f64x8_u32x16(f64x8_arg a_)
	{
		return _mm512_castpd_si512(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cast_i8x16_u32x16(i8x16_arg a_)
	{
		return _mm512_castsi128_si512(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cast_i16x8_u32x16(i16x8_arg a_)
	{
		return _mm512_castsi128_si512(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cast_i32x4_u32x16(i32x4_arg a_)
	{
		return _mm512_castsi128_si512(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cast_i64x2_u32x16(i64x2_arg a_)
	{
		return _mm512_castsi128_si512(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cast_i8x32_u32x16(i8x32_arg a_)
	{
		return _mm512_castsi256_si512(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cast_i16x16_u32x16(i16x16_arg a_)
	{
		return _mm512_castsi256_si512(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cast_i32x8_u32x16(i32x8_arg a_)
	{
		return _mm512_castsi256_si512(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cast_i64x4_u32x16(i64x4_arg a_)
	{
		return _mm512_castsi256_si512(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cast_i8x64_u32x16(i8x64_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cast_i16x32_u32x16(i16x32_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cast_i32x16_u32x16(i32x16_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cast_i64x8_u32x16(i64x8_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cast_u8x16_u32x16(u8x16_arg a_)
	{
		return _mm512_castsi128_si512(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cast_u16x8_u32x16(u16x8_arg a_)
	{
		return _mm512_castsi128_si512(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cast_u32x4_u32x16(u32x4_arg a_)
	{
		return _mm512_castsi128_si512(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cast_u64x2_u32x16(u64x2_arg a_)
	{
		return _mm512_castsi128_si512(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cast_u8x32_u32x16(u8x32_arg a_)
	{
		return _mm512_castsi256_si512(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cast_u16x16_u32x16(u16x16_arg a_)
	{
		return _mm512_castsi256_si512(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cast_u32x8_u32x16(u32x8_arg a_)
	{
		return _mm512_castsi256_si512(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cast_u64x4_u32x16(u64x4_arg a_)
	{
		return _mm512_castsi256_si512(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cast_u8x64_u32x16(u8x64_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cast_u16x32_u32x16(u16x32_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cast_u32x16_u32x16(u32x16_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cast_u64x8_u32x16(u64x8_arg a_)
	{
		return a_;
	}
#pragma endregion

#pragma region CONVERSIONS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cvt_f32x4_u32x16(f32x4_arg a_)
	{
		return _mm512_castsi128_si512(_mm_cvtps_epi32(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cvt_f32x8_u32x16(f32x8_arg a_)
	{
		return _mm512_castsi256_si512(_mm256_cvtps_epi32(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cvt_f32x16_u32x16(f32x16_arg a_)
	{
		return _mm512_cvtps_epi32(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cvt_f64x2_u32x16(f64x2_arg a_)
	{
		return _mm512_castsi128_si512(_mm_cvtpd_epi32(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cvt_f64x4_u32x16(f64x4_arg a_)
	{
		return _mm512_castsi128_si512(_mm256_cvtpd_epi32(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cvt_f64x8_u32x16(f64x8_arg a_)
	{
		return _mm512_castsi256_si512(_mm512_cvtpd_epi32(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cvt_i8x16_u32x16(i8x16_arg a_)
	{
		return _mm512_cvtepi8_epi32(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cvt_i16x8_u32x16(i16x8_arg a_)
	{
		return _mm512_castsi256_si512(_mm256_cvtepi16_epi32(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cvt_i32x4_u32x16(i32x4_arg a_)
	{
		return _mm512_castsi128_si512(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cvt_i64x2_u32x16(i64x2_arg a_)
	{
		return _mm512_castsi128_si512(_mm_cvtepi64_epi32(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cvt_i8x32_u32x16(i8x32_arg a_)
	{
		return _mm512_cvtepi8_epi32(_mm256_castsi256_si128(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cvt_i16x16_u32x16(i16x16_arg a_)
	{
		return _mm512_cvtepi16_epi32(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cvt_i32x8_u32x16(i32x8_arg a_)
	{
		return _mm512_castsi256_si512(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cvt_i64x4_u32x16(i64x4_arg a_)
	{
		return _mm512_castsi128_si512(_mm256_cvtepi64_epi32(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cvt_i8x64_u32x16(i8x64_arg a_)
	{
		return _mm512_cvtepi8_epi32(_mm512_castsi512_si128(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cvt_i16x32_u32x16(i16x32_arg a_)
	{
		return _mm512_cvtepi16_epi32(_mm512_castsi512_si256(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cvt_i32x16_u32x16(i32x16_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cvt_i64x8_u32x16(i64x8_arg a_)
	{
		return _mm512_castsi256_si512(_mm512_cvtepi64_epi32(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cvt_u8x16_u32x16(i8x16_arg a_)
	{
		return _mm512_cvtepi8_epi32(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cvt_u16x8_u32x16(i16x8_arg a_)
	{
		return _mm512_castsi256_si512(_mm256_cvtepi16_epi32(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cvt_u32x4_u32x16(i32x4_arg a_)
	{
		return _mm512_castsi128_si512(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cvt_u64x2_u32x16(i64x2_arg a_)
	{
		return _mm512_castsi128_si512(_mm_cvtepi64_epi32(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cvt_u8x32_u32x16(i8x32_arg a_)
	{
		return _mm512_cvtepi8_epi32(_mm256_castsi256_si128(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cvt_u16x16_u32x16(i16x16_arg a_)
	{
		return _mm512_cvtepi16_epi32(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cvt_u32x8_u32x16(i32x8_arg a_)
	{
		return _mm512_castsi256_si512(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cvt_u64x4_u32x16(i64x4_arg a_)
	{
		return _mm512_castsi128_si512(_mm256_cvtepi64_epi32(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cvt_u8x64_u32x16(i8x64_arg a_)
	{
		return _mm512_cvtepi8_epi32(_mm512_castsi512_si128(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cvt_u16x32_u32x16(i16x32_arg a_)
	{
		return _mm512_cvtepi16_epi32(_mm512_castsi512_si256(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cvt_u32x16_u32x16(i32x16_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cvt_u64x8_u32x16(i64x8_arg a_)
	{
		return _mm512_castsi256_si512(_mm512_cvtepi64_epi32(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 setmasked_u32x16(std::uint16_t bit_mask_)
	{
		constexpr std::uint32_t element_mask = static_cast<std::uint32_t>(0xFFFFFFFF);
		return _mm512_set_epi32
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
		);
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
	EMU_SIMD_COMMON_FUNC_SPEC auto emulate_fp_u32x16(Func_ func_, EmuSIMD::u32x16_arg in_)
		-> std::enable_if_t<std::is_invocable_r_v<EmuSIMD::f32x16, decltype(func_), EmuSIMD::f32x16>, EmuSIMD::u32x16>
	{
		return cvt_f32x16_u32x16
		(
			func_(cvt_u32x16_f32x16(in_))
		);
	}
#pragma endregion

#pragma region COMPARISONS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cmpeq_u32x16(EmuSIMD::u32x16_arg lhs_, EmuSIMD::u32x16_arg rhs_)
	{
		return setmasked_i8x64(_mm512_cmpeq_epu32_mask(lhs_, rhs_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cmpneq_u32x16(EmuSIMD::u32x16_arg lhs_, EmuSIMD::u32x16_arg rhs_)
	{
		return setmasked_i8x64(_mm512_cmpneq_epu32_mask(lhs_, rhs_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cmpgt_u32x16(EmuSIMD::u32x16_arg lhs_, EmuSIMD::u32x16_arg rhs_)
	{
		return setmasked_i8x64(_mm512_cmplt_epu32_mask(rhs_, lhs_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cmplt_u32x16(EmuSIMD::u32x16_arg lhs_, EmuSIMD::u32x16_arg rhs_)
	{
		return setmasked_i8x64(_mm512_cmplt_epu32_mask(lhs_, rhs_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cmpge_u32x16(EmuSIMD::u32x16_arg lhs_, EmuSIMD::u32x16_arg rhs_)
	{
		return setmasked_i8x64(_mm512_cmple_epu32_mask(rhs_, lhs_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cmple_u32x16(EmuSIMD::u32x16_arg lhs_, EmuSIMD::u32x16_arg rhs_)
	{
		return setmasked_i8x64(_mm512_cmple_epu32_mask(lhs_, rhs_));
	}
#pragma endregion

#pragma region MOVES
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 movehl_u32x16(EmuSIMD::u32x16_arg lhs_, EmuSIMD::u32x16_arg rhs_)
	{
		return cast_f32x16_u32x16(movehl_f32x16(cast_u32x16_f32x16(lhs_), cast_u32x16_f32x16(rhs_)));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 movelh_u32x16(EmuSIMD::u32x16_arg lhs_, EmuSIMD::u32x16_arg rhs_)
	{
		return cast_f32x16_u32x16(movelh_f32x16(cast_u32x16_f32x16(lhs_), cast_u32x16_f32x16(rhs_)));
	}
#pragma endregion

#pragma region MINMAX_FUNCS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 min_u32x16(EmuSIMD::u32x16_arg a_, EmuSIMD::u32x16_arg b_)
	{
		return _mm512_min_epu32(a_, b_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 max_u32x16(EmuSIMD::u32x16_arg a_, EmuSIMD::u32x16_arg b_)
	{
		return _mm512_max_epu32(a_, b_);
	}
#pragma endregion

#pragma region SHUFFLES
	template<EmuSIMD::Funcs::shuffle_mask_type ShuffleMask_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 permute_u32x16(EmuSIMD::u32x16_arg a_)
	{
		return _mm512_shuffle_epi32(a_, ShuffleMask_);
	}

	template<EmuSIMD::Funcs::shuffle_mask_type ShuffleMask_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 shuffle_u32x16(EmuSIMD::u32x16_arg a_, EmuSIMD::u32x16_arg b_)
	{
		return cast_f32x16_u32x16
		(
			shuffle_f32x16<ShuffleMask_>
			(
				cast_u32x16_f32x16(a_),
				cast_u32x16_f32x16(b_)
			)
		);
	}
#pragma endregion

#pragma region BASIC_ARITHMETIC
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 mul_all_u32x16(EmuSIMD::u32x16_arg lhs_, EmuSIMD::u32x16_arg rhs_)
	{
		return _mm512_mullo_epi32(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 negate_u32x16(EmuSIMD::u32x16_arg to_negate_)
	{
		return _mm512_sub_epi32(_mm512_setzero_si512(), to_negate_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 add_u32x16(EmuSIMD::u32x16_arg lhs_, EmuSIMD::u32x16_arg rhs_)
	{
		return _mm512_add_epi32(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 sub_u32x16(EmuSIMD::u32x16_arg lhs_, EmuSIMD::u32x16_arg rhs_)
	{
		return _mm512_sub_epi32(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 mul_u32x16(EmuSIMD::u32x16_arg lhs_, EmuSIMD::u32x16_arg rhs_)
	{
		return _mm512_mul_epu32(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 div_u32x16(EmuSIMD::u32x16_arg lhs_, EmuSIMD::u32x16_arg rhs_)
	{
#if EMU_CORE_X86_X64_SVML
		return _mm512_div_epi32(lhs_, rhs_);
#else
		EmuSIMD::f32x16 result_f32 = cvt_u32x16_f32x16(lhs_);
		result_f32 = div_f32x16(result_f32, cvt_u32x16_f32x16(rhs_));
		return cvt_f32x16_u32x16(trunc_f32x16(result_f32));
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 addsub_u32x16(EmuSIMD::u32x16_arg lhs_, EmuSIMD::u32x16_arg rhs_)
	{
		constexpr std::uint32_t bytes_mask = static_cast<std::uint32_t>(0xFFFFFFFF);
		const EmuSIMD::u32x16 mask = _mm512_set_epi32(bytes_mask, 0, bytes_mask, 0, bytes_mask, 0, bytes_mask, 0, bytes_mask, 0, bytes_mask, 0, bytes_mask, 0, bytes_mask, 0);
		EmuSIMD::u32x16 out = _mm512_add_epi32(lhs_, _mm512_and_si512(mask, rhs_));
		return _mm512_sub_epi32(lhs_, _mm512_andnot_si512(mask, rhs_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 subadd_u32x16(EmuSIMD::u32x16_arg lhs_, EmuSIMD::u32x16_arg rhs_)
	{
		constexpr std::uint32_t bytes_mask = static_cast<std::uint32_t>(0xFFFFFFFF);
		const EmuSIMD::u32x16 mask = _mm512_set_epi32(bytes_mask, 0, bytes_mask, 0, bytes_mask, 0, bytes_mask, 0, bytes_mask, 0, bytes_mask, 0, bytes_mask, 0, bytes_mask, 0);
		EmuSIMD::u32x16 out = _mm512_sub_epi32(lhs_, _mm512_and_si512(mask, rhs_));
		return _mm512_add_epi32(lhs_, _mm512_andnot_si512(mask, rhs_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 fmadd_u32x16(EmuSIMD::u32x16_arg a_, EmuSIMD::u32x16_arg b_, EmuSIMD::u32x16_arg c_)
	{
		return _mm512_add_epi32(mul_all_u32x16(a_, b_), c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 fmsub_u32x16(EmuSIMD::u32x16_arg a_, EmuSIMD::u32x16_arg b_, EmuSIMD::u32x16_arg c_)
	{
		return _mm512_sub_epi32(mul_all_u32x16(a_, b_), c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 fnmadd_u32x16(EmuSIMD::u32x16_arg a_, EmuSIMD::u32x16_arg b_, EmuSIMD::u32x16_arg c_)
	{
		return _mm512_add_epi32(mul_all_u32x16(negate_u32x16(a_), b_), c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 fnmsub_u32x16(EmuSIMD::u32x16_arg a_, EmuSIMD::u32x16_arg b_, EmuSIMD::u32x16_arg c_)
	{
		return _mm512_sub_epi32(mul_all_u32x16(negate_u32x16(a_), b_), c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 fmaddsub_u32x16(EmuSIMD::u32x16_arg a_, EmuSIMD::u32x16_arg b_, EmuSIMD::u32x16_arg c_)
	{
		return addsub_u32x16(mul_all_u32x16(a_, b_), c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 fmsubadd_u32x16(EmuSIMD::u32x16_arg a_, EmuSIMD::u32x16_arg b_, EmuSIMD::u32x16_arg c_)
	{
		return subadd_u32x16(mul_all_u32x16(a_, b_), c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 floor_u32x16(EmuSIMD::u32x16_arg to_floor_)
	{
		return to_floor_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 ceil_u32x16(EmuSIMD::u32x16_arg to_ceil_)
	{
		return to_ceil_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 trunc_u32x16(EmuSIMD::u32x16_arg to_trunc_)
	{
		return to_trunc_;
	}

	template<int RoundingFlag_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 round_u32x16(EmuSIMD::u32x16_arg to_round_)
	{
		return to_round_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 mod_u32x16(EmuSIMD::u32x16_arg lhs_, EmuSIMD::u32x16_arg rhs_)
	{
#if EMU_CORE_X86_X64_SVML
		return _mm512_rem_epu32(lhs_, rhs_);
#else
		EmuSIMD::u32x16 to_subtract = div_u32x16(lhs_, rhs_);
		to_subtract = mul_all_u32x16(to_subtract, rhs_);
		return sub_u32x16(lhs_, to_subtract);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 abs_u32x16(EmuSIMD::u32x16_arg in_)
	{
		return in_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 sqrt_u32x16(EmuSIMD::u32x16_arg in_)
	{
		return emulate_fp_u32x16([](EmuSIMD::f32x16_arg in_fp_) { return sqrt_f32x16(in_fp_); }, in_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 rsqrt_u32x16(EmuSIMD::u32x16_arg in_)
	{
		return emulate_fp_u32x16([](EmuSIMD::f32x16_arg in_fp_) { return rsqrt_f32x16(in_fp_); }, in_);
	}
#pragma endregion

#pragma region NEAR_COMPARISONS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cmpnear_u32x16(EmuSIMD::u32x16_arg lhs_, EmuSIMD::u32x16_arg rhs_)
	{
		return cmpeq_u32x16(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cmpnear_u32x16(EmuSIMD::u32x16_arg lhs_, EmuSIMD::u32x16_arg rhs_, EmuSIMD::u32x16_arg epsilon)
	{
		return cmple_u32x16(sub_u32x16(lhs_, rhs_), epsilon);
	}
#pragma endregion

#pragma region TRIG
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cos_u32x16(EmuSIMD::u32x16_arg in_)
	{
		return emulate_fp_u32x16([](EmuSIMD::f32x16_arg in_fp_) { return cos_f32x16(in_fp_); }, in_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 sin_u32x16(EmuSIMD::u32x16_arg in_)
	{
		return emulate_fp_u32x16([](EmuSIMD::f32x16_arg in_fp_) { return sin_f32x16(in_fp_); }, in_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 tan_u32x16(EmuSIMD::u32x16_arg in_)
	{
		return emulate_fp_u32x16([](EmuSIMD::f32x16_arg in_fp_) { return tan_f32x16(in_fp_); }, in_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 acos_u32x16(EmuSIMD::u32x16_arg in_)
	{
		return emulate_fp_u32x16([](EmuSIMD::f32x16_arg in_fp_) { return acos_f32x16(in_fp_); }, in_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 asin_u32x16(EmuSIMD::u32x16_arg in_)
	{
		return emulate_fp_u32x16([](EmuSIMD::f32x16_arg in_fp_) { return asin_f32x16(in_fp_); }, in_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 atan_u32x16(EmuSIMD::u32x16_arg in_)
	{
		return emulate_fp_u32x16([](EmuSIMD::f32x16_arg in_fp_) { return atan_f32x16(in_fp_); }, in_);
	}
#pragma endregion
}

#endif
