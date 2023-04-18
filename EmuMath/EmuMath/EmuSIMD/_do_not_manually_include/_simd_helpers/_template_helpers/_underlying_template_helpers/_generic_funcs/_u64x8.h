#ifndef EMU_SIMD_GENERIC_FUNCS_U64X8_H_INC_
#define EMU_SIMD_GENERIC_FUNCS_U64X8_H_INC_ 1

#include "_generic_declarations/_all_generic_declarations.h"
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
		//return _mm512_setr_epi64(e0, e1, e2, e3, e4, e5, e6, e7);
		return _mm512_set_epi64(e7, e6, e5, e4, e3, e2, e1, e0);
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

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 setmasked_u64x8(std::uint8_t bit_mask_)
	{
		constexpr std::uint64_t element_mask = static_cast<std::uint64_t>(0xFFFFFFFFFFFFFFFF);
		return _mm512_set_epi64
		(
			(bit_mask_ & 0x01) * element_mask,
			((bit_mask_ & 0x02) >> 1) * element_mask,
			((bit_mask_ & 0x04) >> 2) * element_mask,
			((bit_mask_ & 0x08) >> 3) * element_mask,
			((bit_mask_ & 0x10) >> 4) * element_mask,
			((bit_mask_ & 0x20) >> 5) * element_mask,
			((bit_mask_ & 0x40) >> 6) * element_mask,
			((bit_mask_ & 0x80) >> 7) * element_mask
		);
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

#pragma region EXTRACTION_TEMPLATES
	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 extract_f32x16_lane_u64x8(f32x16_arg a_)
	{
		static_assert(Index_ == 0, "Invalid SIMD lane extraction index: Extracting u64x8 lane from a f32x16 instance; the maximum index is 0 but this index has been exceeded.");
		return cast_f32x16_u64x8(a_);
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 extract_f64x8_lane_u64x8(f64x8_arg a_)
	{
		static_assert(Index_ == 0, "Invalid SIMD lane extraction index: Extracting u64x8 lane from a f64x8 instance; the maximum index is 0 but this index has been exceeded.");
		return cast_f64x8_u64x8(a_);
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 extract_i8x64_lane_u64x8(i8x64_arg a_)
	{
		static_assert(Index_ == 0, "Invalid SIMD lane extraction index: Extracting u64x8 lane from a i8x64 instance; the maximum index is 0 but this index has been exceeded.");
		return cast_i8x64_u64x8(a_);
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 extract_i16x32_lane_u64x8(i16x32_arg a_)
	{
		static_assert(Index_ == 0, "Invalid SIMD lane extraction index: Extracting u64x8 lane from a i16x32 instance; the maximum index is 0 but this index has been exceeded.");
		return cast_i16x32_u64x8(a_);
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 extract_i32x16_lane_u64x8(i32x16_arg a_)
	{
		static_assert(Index_ == 0, "Invalid SIMD lane extraction index: Extracting u64x8 lane from a i32x16 instance; the maximum index is 0 but this index has been exceeded.");
		return cast_i32x16_u64x8(a_);
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 extract_i64x8_lane_u64x8(i64x8_arg a_)
	{
		static_assert(Index_ == 0, "Invalid SIMD lane extraction index: Extracting u64x8 lane from a i64x8 instance; the maximum index is 0 but this index has been exceeded.");
		return cast_i64x8_u64x8(a_);
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 extract_u8x64_lane_u64x8(u8x64_arg a_)
	{
		static_assert(Index_ == 0, "Invalid SIMD lane extraction index: Extracting u64x8 lane from a u8x64 instance; the maximum index is 0 but this index has been exceeded.");
		return cast_u8x64_u64x8(a_);
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 extract_u16x32_lane_u64x8(u16x32_arg a_)
	{
		static_assert(Index_ == 0, "Invalid SIMD lane extraction index: Extracting u64x8 lane from a u16x32 instance; the maximum index is 0 but this index has been exceeded.");
		return cast_u16x32_u64x8(a_);
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 extract_u32x16_lane_u64x8(u32x16_arg a_)
	{
		static_assert(Index_ == 0, "Invalid SIMD lane extraction index: Extracting u64x8 lane from a u32x16 instance; the maximum index is 0 but this index has been exceeded.");
		return cast_u32x16_u64x8(a_);
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 extract_u64x8_lane_u64x8(u64x8_arg a_)
	{
		static_assert(Index_ == 0, "Invalid SIMD lane extraction index: Extracting u64x8 lane from a u64x8 instance; the maximum index is 0 but this index has been exceeded.");
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
	EMU_SIMD_COMMON_FUNC_SPEC auto emulate_fp_u64x8(Func_ func_, EmuSIMD::u64x8_arg in_)
		-> std::enable_if_t<std::is_invocable_r_v<EmuSIMD::f64x8, decltype(func_), EmuSIMD::f64x8>, EmuSIMD::u64x8>
	{
		return cvt_f64x8_u64x8
		(
			func_(cvt_u64x8_f64x8(in_))
		);
	}
#pragma endregion

#pragma region COMPARISONS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 cmpeq_u64x8(EmuSIMD::u64x8_arg lhs_, EmuSIMD::u64x8_arg rhs_)
	{
		return setmasked_i8x64(_mm512_cmpeq_epu64_mask(lhs_, rhs_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 cmpneq_u64x8(EmuSIMD::u64x8_arg lhs_, EmuSIMD::u64x8_arg rhs_)
	{
		return setmasked_i8x64(_mm512_cmpneq_epu64_mask(lhs_, rhs_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 cmpgt_u64x8(EmuSIMD::u64x8_arg lhs_, EmuSIMD::u64x8_arg rhs_)
	{
		return setmasked_i8x64(_mm512_cmplt_epu64_mask(rhs_, lhs_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 cmplt_u64x8(EmuSIMD::u64x8_arg lhs_, EmuSIMD::u64x8_arg rhs_)
	{
		return setmasked_i8x64(_mm512_cmplt_epu64_mask(lhs_, rhs_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 cmpge_u64x8(EmuSIMD::u64x8_arg lhs_, EmuSIMD::u64x8_arg rhs_)
	{
		return setmasked_i8x64(_mm512_cmple_epu64_mask(rhs_, lhs_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 cmple_u64x8(EmuSIMD::u64x8_arg lhs_, EmuSIMD::u64x8_arg rhs_)
	{
		return setmasked_i8x64(_mm512_cmple_epu64_mask(lhs_, rhs_));
	}
#pragma endregion

#pragma region MOVES
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 movehl_u64x8(EmuSIMD::u64x8_arg lhs_, EmuSIMD::u64x8_arg rhs_)
	{
		return cast_f64x8_u64x8(movehl_f64x8(cast_u64x8_f64x8(lhs_), cast_u64x8_f64x8(rhs_)));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 movelh_u64x8(EmuSIMD::u64x8_arg lhs_, EmuSIMD::u64x8_arg rhs_)
	{
		return cast_f64x8_u64x8(movelh_f64x8(cast_u64x8_f64x8(lhs_), cast_u64x8_f64x8(rhs_)));
	}
#pragma endregion
	
#pragma region BLENDS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 blendv_u64x8(EmuSIMD::u64x8_arg a_, EmuSIMD::u64x8_arg b_, EmuSIMD::u64x8_arg shuffle_mask_vec_)
	{
		return cast_f64x8_u64x8
		(
			blendv_f64x8
			(
				cast_u64x8_f64x8(a_),
				cast_u64x8_f64x8(b_),
				cast_u64x8_f64x8(shuffle_mask_vec_)
			)
		);
	}

	template<blend_mask_type BlendMask_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 blend_u64x8(EmuSIMD::u64x8_arg a_, EmuSIMD::u64x8_arg b_)
	{
		return cast_f64x8_u64x8
		(
			blend_f64x8<BlendMask_>
			(
				cast_u64x8_f64x8(a_),
				cast_u64x8_f64x8(b_)
			)
		);
	}
#pragma endregion

#pragma region MINMAX_FUNCS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 min_u64x8(EmuSIMD::u64x8_arg a_, EmuSIMD::u64x8_arg b_)
	{
		return _mm512_min_epu64(a_, b_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 max_u64x8(EmuSIMD::u64x8_arg a_, EmuSIMD::u64x8_arg b_)
	{
		return _mm512_max_epu64(a_, b_);
	}
#pragma endregion

#pragma region SHUFFLES
	template<EmuSIMD::Funcs::shuffle_mask_type ShuffleMask_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 permute_u64x8(EmuSIMD::u64x8_arg a_)
	{
		return cast_f64x8_u64x8
		(
			permute_f64x8<ShuffleMask_>(cast_u64x8_f64x8(a_))
		);
	}

	template<EmuSIMD::Funcs::shuffle_mask_type ShuffleMask_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x4 shuffle_u64x8(EmuSIMD::u64x8_arg a_, EmuSIMD::u64x8_arg b_)
	{
		return cast_f64x8_u64x8
		(
			shuffle_f64x8<ShuffleMask_>(cast_u64x8_f64x8(a_), cast_u64x8_f64x8(b_))
		);
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
#if EMU_CORE_X86_X64_SVML
		return _mm512_div_epu64(lhs_, rhs_);
#else
		EmuSIMD::f64x8 result_f64 = cvt_u64x8_f64x8(lhs_);
		result_f64 = div_f64x8(result_f64, cvt_u64x8_f64x8(rhs_));
		return cvt_f64x8_u64x8(trunc_f64x8(result_f64));
#endif
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
#if EMU_CORE_X86_X64_SVML
		return _mm512_rem_epi64(lhs_, rhs_);
#else
		EmuSIMD::u64x8 to_subtract = div_u64x8(lhs_, rhs_);
		to_subtract = mul_all_u64x8(to_subtract, rhs_);
		return sub_u64x8(lhs_, to_subtract);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 abs_u64x8(EmuSIMD::u64x8_arg in_)
	{
		return in_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 sqrt_u64x8(EmuSIMD::u64x8_arg in_)
	{
		return emulate_fp_u64x8([](EmuSIMD::f64x8_arg in_fp_) { return sqrt_f64x8(in_fp_); }, in_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 rsqrt_u64x8(EmuSIMD::u64x8_arg in_)
	{
		return emulate_fp_u64x8([](EmuSIMD::f64x8_arg in_fp_) { return rsqrt_f64x8(in_fp_); }, in_);
	}
#pragma endregion

#pragma region NEAR_COMPARISONS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 cmpnear_u64x8(EmuSIMD::u64x8_arg lhs_, EmuSIMD::u64x8_arg rhs_)
	{
		return cmpeq_u64x8(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 cmpnear_u64x8(EmuSIMD::u64x8_arg lhs_, EmuSIMD::u64x8_arg rhs_, EmuSIMD::u64x8_arg epsilon)
	{
		return cmple_u64x8(sub_u64x8(lhs_, rhs_), epsilon);
	}
#pragma endregion

#pragma region TRIG
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 cos_u64x8(EmuSIMD::u64x8_arg in_)
	{
		return emulate_fp_u64x8([](EmuSIMD::f64x8_arg in_fp_) { return cos_f64x8(in_fp_); }, in_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 sin_u64x8(EmuSIMD::u64x8_arg in_)
	{
		return emulate_fp_u64x8([](EmuSIMD::f64x8_arg in_fp_) { return sin_f64x8(in_fp_); }, in_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 tan_u64x8(EmuSIMD::u64x8_arg in_)
	{
		return emulate_fp_u64x8([](EmuSIMD::f64x8_arg in_fp_) { return tan_f64x8(in_fp_); }, in_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 acos_u64x8(EmuSIMD::u64x8_arg in_)
	{
		return emulate_fp_u64x8([](EmuSIMD::f64x8_arg in_fp_) { return acos_f64x8(in_fp_); }, in_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 asin_u64x8(EmuSIMD::u64x8_arg in_)
	{
		return emulate_fp_u64x8([](EmuSIMD::f64x8_arg in_fp_) { return asin_f64x8(in_fp_); }, in_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 atan_u64x8(EmuSIMD::u64x8_arg in_)
	{
		return emulate_fp_u64x8([](EmuSIMD::f64x8_arg in_fp_) { return atan_f64x8(in_fp_); }, in_);
	}
#pragma endregion
}

#endif
