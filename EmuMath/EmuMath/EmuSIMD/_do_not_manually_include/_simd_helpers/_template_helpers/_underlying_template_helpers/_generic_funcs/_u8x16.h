#ifndef EMU_SIMD_GENERIC_FUNCS_U8X16_H_INC_
#define EMU_SIMD_GENERIC_FUNCS_U8X16_H_INC_ 1

#include "_common_generic_func_helpers.h"
#include "_f32x4.h"
#include "_u16x8.h"

namespace EmuSIMD::Funcs
{
#pragma region SETTERS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 set_u8x16
	(
		std::uint8_t e0, std::uint8_t e1, std::uint8_t e2, std::uint8_t e3, std::uint8_t e4, std::uint8_t e5, std::uint8_t e6, std::uint8_t e7,
		std::uint8_t e8, std::uint8_t e9, std::uint8_t e10, std::uint8_t e11, std::uint8_t e12, std::uint8_t e13, std::uint8_t e14, std::uint8_t e15
	)
	{
		return _mm_set_epi8(e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 setr_u8x16
	(
		std::uint8_t e0, std::uint8_t e1, std::uint8_t e2, std::uint8_t e3, std::uint8_t e4, std::uint8_t e5, std::uint8_t e6, std::uint8_t e7,
		std::uint8_t e8, std::uint8_t e9, std::uint8_t e10, std::uint8_t e11, std::uint8_t e12, std::uint8_t e13, std::uint8_t e14, std::uint8_t e15
	)
	{
		//return _mm_setr_epi8(e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15);
		return _mm_set_epi8(e15, e14, e13, e12, e11, e10, e9, e8, e7, e6, e5, e4, e3, e2, e1, e0);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 set1_u8x16(std::uint8_t all_)
	{
		return _mm_set1_epi8(all_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 load_u8x16(const std::uint8_t* p_to_load_)
	{
		return _mm_load_si128(reinterpret_cast<const __m128i*>(p_to_load_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 setzero_u8x16()
	{
		return _mm_setzero_si128();
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 setmasked_u8x16(std::uint16_t bit_mask_)
	{
		constexpr std::uint8_t element_mask = static_cast<std::uint8_t>(0xFF);
		return _mm_set_epi8
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

#pragma region STORES
	EMU_SIMD_COMMON_FUNC_SPEC void store_u8x16(std::uint8_t* p_out_, u8x16_arg a_)
	{
		_mm_store_si128(reinterpret_cast<__m128i*>(p_out_), a_);
	}
#pragma endregion

#pragma region CASTS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cast_f32x4_u8x16(f32x4_arg a_)
	{
		return _mm_castps_si128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cast_f32x8_u8x16(f32x8_arg a_)
	{
		return _mm256_castsi256_si128(_mm256_castps_si256(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cast_f32x16_u8x16(f32x16_arg a_)
	{
		return _mm512_castsi512_si128(_mm512_castps_si512(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cast_f64x2_u8x16(f64x2_arg a_)
	{
		return _mm_castpd_si128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cast_f64x4_u8x16(f64x4_arg a_)
	{
		return _mm256_castsi256_si128(_mm256_castpd_si256(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cast_f64x8_u8x16(f64x8_arg a_)
	{
		return _mm512_castsi512_si128(_mm512_castpd_si512(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cast_i8x16_u8x16(i8x16_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cast_i16x8_u8x16(i16x8_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cast_i32x4_u8x16(i32x4_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cast_i64x2_u8x16(i64x2_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cast_i8x32_u8x16(i8x32_arg a_)
	{
		return _mm256_castsi256_si128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cast_i16x16_u8x16(i16x16_arg a_)
	{
		return _mm256_castsi256_si128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cast_i32x8_u8x16(i32x8_arg a_)
	{
		return _mm256_castsi256_si128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cast_i64x4_u8x16(i64x4_arg a_)
	{
		return _mm256_castsi256_si128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cast_i8x64_u8x16(i8x64_arg a_)
	{
		return _mm512_castsi512_si128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cast_i16x32_u8x16(i16x32_arg a_)
	{
		return _mm512_castsi512_si128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cast_i32x16_u8x16(i32x16_arg a_)
	{
		return _mm512_castsi512_si128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cast_i64x8_u8x16(i64x8_arg a_)
	{
		return _mm512_castsi512_si128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cast_u8x16_u8x16(u8x16_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cast_u16x8_u8x16(u16x8_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cast_u32x4_u8x16(u32x4_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cast_u64x2_u8x16(u64x2_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cast_u8x32_u8x16(u8x32_arg a_)
	{
		return _mm256_castsi256_si128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cast_u16x16_u8x16(u16x16_arg a_)
	{
		return _mm256_castsi256_si128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cast_u32x8_u8x16(u32x8_arg a_)
	{
		return _mm256_castsi256_si128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cast_u64x4_u8x16(u64x4_arg a_)
	{
		return _mm256_castsi256_si128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cast_u8x64_u8x16(u8x64_arg a_)
	{
		return _mm512_castsi512_si128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cast_u16x32_u8x16(u16x32_arg a_)
	{
		return _mm512_castsi512_si128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cast_u32x16_u8x16(u32x16_arg a_)
	{
		return _mm512_castsi512_si128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cast_u64x8_u8x16(u64x8_arg a_)
	{
		return _mm512_castsi512_si128(a_);
	}
#pragma endregion

#pragma region CONVERSIONS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cvt_f32x4_u8x16(f32x4_arg a_)
	{
		return _mm_cvtepi32_epi8(_mm_cvtps_epi32(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cvt_f32x8_u8x16(f32x8_arg a_)
	{
		return _mm256_cvtepi32_epi8(_mm256_cvtps_epi32(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cvt_f32x16_u8x16(f32x16_arg a_)
	{
		return _mm512_cvtepi32_epi8(_mm512_cvtps_epi32(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cvt_f64x2_u8x16(f64x2_arg a_)
	{
		return _mm_cvtepi64_epi8(_mm_cvtpd_epi64(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cvt_f64x4_u8x16(f64x4_arg a_)
	{
		return _mm256_cvtepi64_epi8(_mm256_cvtpd_epi64(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cvt_f64x8_u8x16(f64x8_arg a_)
	{
		return _mm512_cvtepi64_epi8(_mm512_cvtpd_epi64(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cvt_i8x16_u8x16(i8x16_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cvt_i16x8_u8x16(i16x8_arg a_)
	{
		return _mm_cvtepi16_epi8(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cvt_i32x4_u8x16(i32x4_arg a_)
	{
		return _mm_cvtepi32_epi8(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cvt_i64x2_u8x16(i64x2_arg a_)
	{
		return _mm_cvtepi64_epi8(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cvt_i8x32_u8x16(i8x32_arg a_)
	{
		return _mm256_castsi256_si128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cvt_i16x16_u8x16(i16x16_arg a_)
	{
		return _mm256_cvtepi16_epi8(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cvt_i32x8_u8x16(i32x8_arg a_)
	{
		return _mm256_cvtepi32_epi8(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cvt_i64x4_u8x16(i64x4_arg a_)
	{
		return _mm256_cvtepi64_epi8(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cvt_i8x64_u8x16(i8x64_arg a_)
	{
		return _mm512_castsi512_si128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cvt_i16x32_u8x16(i16x32_arg a_)
	{
		return _mm256_cvtepi16_epi8(_mm512_castsi512_si256(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cvt_i32x16_u8x16(i32x16_arg a_)
	{
		return _mm512_cvtepi32_epi8(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cvt_i64x8_u8x16(i64x8_arg a_)
	{
		return _mm512_cvtepi64_epi8(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cvt_u8x16_u8x16(u8x16_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cvt_u16x8_u8x16(u16x8_arg a_)
	{
		//return _mm_cvtepi16_epi8(a_);

		std::uint16_t data_dump[8];
		_mm_store_si128(reinterpret_cast<__m128i*>(data_dump), a_);
		return setr_u8x16
		(
			static_cast<std::uint8_t>(data_dump[0]),
			static_cast<std::uint8_t>(data_dump[1]),
			static_cast<std::uint8_t>(data_dump[2]),
			static_cast<std::uint8_t>(data_dump[3]),
			static_cast<std::uint8_t>(data_dump[4]),
			static_cast<std::uint8_t>(data_dump[5]),
			static_cast<std::uint8_t>(data_dump[6]),
			static_cast<std::uint8_t>(data_dump[7]),
			0,
			0,
			0,
			0,
			0,
			0,
			0,
			0
		);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cvt_u32x4_u8x16(u32x4_arg a_)
	{
		return _mm_cvtepi32_epi8(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cvt_u64x2_u8x16(u64x2_arg a_)
	{
		return _mm_cvtepi64_epi8(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cvt_u8x32_u8x16(u8x32_arg a_)
	{
		return _mm256_castsi256_si128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cvt_u16x16_u8x16(u16x16_arg a_)
	{
		return _mm256_cvtepi16_epi8(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cvt_u32x8_u8x16(u32x8_arg a_)
	{
		return _mm256_cvtepi32_epi8(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cvt_u64x4_u8x16(u64x4_arg a_)
	{
		return _mm256_cvtepi64_epi8(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cvt_u8x64_u8x16(u8x64_arg a_)
	{
		return _mm512_castsi512_si128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cvt_u16x32_u8x16(u16x32_arg a_)
	{
		return _mm256_cvtepi16_epi8(_mm512_castsi512_si256(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cvt_u32x16_u8x16(u32x16_arg a_)
	{
		return _mm512_cvtepi32_epi8(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cvt_u64x8_u8x16(u64x8_arg a_)
	{
		return _mm512_cvtepi64_epi8(a_);
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
	EMU_SIMD_COMMON_FUNC_SPEC auto emulate_fp_u8x16(Func_ func_, EmuSIMD::u8x16_arg in_)
		-> std::enable_if_t<std::is_invocable_r_v<EmuSIMD::f32x4, decltype(func_), EmuSIMD::f32x4>, EmuSIMD::u8x16>
	{
		constexpr std::size_t num_elements = 16;
		constexpr std::size_t elements_per_register = 4;
		std::uint8_t data[num_elements];
		float results[num_elements];

		store_u8x16(data, in_);
		for (std::size_t i = 0; i < num_elements; i += elements_per_register)
		{
			store_f32x4(results + i, func_(set_f32x4(static_cast<float>(data[i + 3]), static_cast<float>(data[i + 2]), static_cast<float>(data[i + 1]), static_cast<float>(data[i]))));
		}

		return set_u8x16
		(
			static_cast<std::uint8_t>(results[15]),
			static_cast<std::uint8_t>(results[14]),
			static_cast<std::uint8_t>(results[13]),
			static_cast<std::uint8_t>(results[12]),
			static_cast<std::uint8_t>(results[11]),
			static_cast<std::uint8_t>(results[10]),
			static_cast<std::uint8_t>(results[9]),
			static_cast<std::uint8_t>(results[8]),
			static_cast<std::uint8_t>(results[7]),
			static_cast<std::uint8_t>(results[6]),
			static_cast<std::uint8_t>(results[5]),
			static_cast<std::uint8_t>(results[4]),
			static_cast<std::uint8_t>(results[3]),
			static_cast<std::uint8_t>(results[2]),
			static_cast<std::uint8_t>(results[1]),
			static_cast<std::uint8_t>(results[0])
		);
	}
#pragma endregion

#pragma region COMPARISONS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cmpeq_u8x16(EmuSIMD::u8x16_arg lhs_, EmuSIMD::u8x16_arg rhs_)
	{
		return _mm_cmpeq_epi8(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cmpneq_u8x16(EmuSIMD::u8x16_arg lhs_, EmuSIMD::u8x16_arg rhs_)
	{
		constexpr std::uint8_t mask = static_cast<std::uint8_t>(0xFF);
		return _mm_xor_si128(set1_i8x16(mask), _mm_cmpeq_epi8(lhs_, rhs_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cmpgt_u8x16(EmuSIMD::u8x16_arg lhs_, EmuSIMD::u8x16_arg rhs_)
	{
		constexpr std::uint8_t mask = static_cast<std::uint8_t>(0xFF);
		return _mm_andnot_si128(_mm_cmpeq_epi8(_mm_min_epu8(lhs_, rhs_), lhs_), set1_u8x16(mask));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cmplt_u8x16(EmuSIMD::u8x16_arg lhs_, EmuSIMD::u8x16_arg rhs_)
	{
		constexpr std::uint8_t mask = static_cast<std::uint8_t>(0xFF);
		return _mm_andnot_si128(_mm_cmpeq_epi8(_mm_max_epu8(lhs_, rhs_), lhs_), set1_u8x16(mask));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cmpge_u8x16(EmuSIMD::u8x16_arg lhs_, EmuSIMD::u8x16_arg rhs_)
	{
		return _mm_cmpeq_epi8(_mm_max_epu8(lhs_, rhs_), lhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cmple_u8x16(EmuSIMD::u8x16_arg lhs_, EmuSIMD::u8x16_arg rhs_)
	{
		return _mm_cmpeq_epi8(_mm_min_epu8(lhs_, rhs_), lhs_);
	}
#pragma endregion

#pragma region MOVES
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 movehl_u8x16(EmuSIMD::u8x16_arg lhs_, EmuSIMD::u8x16_arg rhs_)
	{
		return cast_f32x4_u8x16(movehl_f32x4(cast_u8x16_f32x4(lhs_), cast_u8x16_f32x4(rhs_)));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 movelh_u8x16(EmuSIMD::u8x16_arg lhs_, EmuSIMD::u8x16_arg rhs_)
	{
		return cast_f32x4_u8x16(movelh_f32x4(cast_u8x16_f32x4(lhs_), cast_u8x16_f32x4(rhs_)));
	}
#pragma endregion

#pragma region BASIC_ARITHMETIC
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 mul_all_u8x16(EmuSIMD::u8x16_arg lhs_, EmuSIMD::u8x16_arg rhs_)
	{
		EmuSIMD::u8x16 even_bytes = _mm_mullo_epi16(lhs_, rhs_);
		EmuSIMD::u8x16 odd_bytes = _mm_mullo_epi16(_mm_srli_epi16(lhs_, 8), _mm_srli_epi16(rhs_, 8));
		return _mm_or_si128(_mm_slli_epi16(odd_bytes, 8), _mm_srli_epi16(_mm_slli_epi16(even_bytes, 8), 8));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 negate_u8x16(EmuSIMD::u8x16_arg to_negate_)
	{
		return _mm_sub_epi8(_mm_setzero_si128(), to_negate_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 add_u8x16(EmuSIMD::u8x16_arg lhs_, EmuSIMD::u8x16_arg rhs_)
	{
		return _mm_add_epi8(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 sub_u8x16(EmuSIMD::u8x16_arg lhs_, EmuSIMD::u8x16_arg rhs_)
	{
		return _mm_sub_epi8(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 mul_u8x16(EmuSIMD::u8x16_arg lhs_, EmuSIMD::u8x16_arg rhs_)
	{
		return _mm_mul_epu32(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 div_u8x16(EmuSIMD::u8x16_arg lhs_, EmuSIMD::u8x16_arg rhs_)
	{
#if EMU_CORE_X86_X64_SVML
		return _mm_div_epu8(lhs_, rhs_);
#else
		// lo
		EmuSIMD::u16x8 lane64_a = cvt_u8x16_u16x8(lhs_);
		EmuSIMD::u16x8 lane64_b = cvt_u8x16_u16x8(rhs_);
		EmuSIMD::u8x16 lo = cvt_u16x8_u8x16(div_u16x8(lane64_a, lane64_b));

		// hi - move hi bits to lo via f32 reinterpretation of this width register
		EmuSIMD::u8x16 tmp_lane = movehl_u8x16(lhs_, lhs_);
		lane64_a = cvt_u8x16_u16x8(tmp_lane);

		tmp_lane = movehl_u8x16(rhs_, rhs_);
		lane64_b = cvt_u8x16_u16x8(tmp_lane);

		// Move hi and lo into the same register, in their respective 64-bit lanes
		EmuSIMD::i8x16 hi = cvt_u16x8_u8x16(div_u16x8(lane64_a, lane64_b));
		return movelh_u8x16(lo, hi);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 addsub_u8x16(EmuSIMD::u8x16_arg lhs_, EmuSIMD::u8x16_arg rhs_)
	{
		constexpr std::uint8_t byte_mask = static_cast<std::uint8_t>(0xFF);
		const EmuSIMD::u8x16 mask = _mm_set_epi8(byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0);
		EmuSIMD::u8x16 out = _mm_add_epi8(lhs_, _mm_and_si128(mask, rhs_));
		return _mm_sub_epi8(lhs_, _mm_andnot_si128(mask, rhs_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 subadd_u8x16(EmuSIMD::u8x16_arg lhs_, EmuSIMD::u8x16_arg rhs_)
	{
		constexpr std::uint8_t byte_mask = static_cast<std::uint8_t>(0xFF);
		const EmuSIMD::u8x16 mask = _mm_set_epi8(byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0);
		EmuSIMD::u8x16 out = _mm_sub_epi8(lhs_, _mm_and_si128(mask, rhs_));
		return _mm_add_epi8(lhs_, _mm_andnot_si128(mask, rhs_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 fmadd_u8x16(EmuSIMD::u8x16_arg a_, EmuSIMD::u8x16_arg b_, EmuSIMD::u8x16_arg c_)
	{
		return _mm_add_epi8(mul_all_u8x16(a_, b_), c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 fmsub_u8x16(EmuSIMD::u8x16_arg a_, EmuSIMD::u8x16_arg b_, EmuSIMD::u8x16_arg c_)
	{
		return _mm_sub_epi8(mul_all_u8x16(a_, b_), c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 fnmadd_u8x16(EmuSIMD::u8x16_arg a_, EmuSIMD::u8x16_arg b_, EmuSIMD::u8x16_arg c_)
	{
		return _mm_add_epi8(mul_all_u8x16(negate_u8x16(a_), b_), c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 fnmsub_u8x16(EmuSIMD::u8x16_arg a_, EmuSIMD::u8x16_arg b_, EmuSIMD::u8x16_arg c_)
	{
		return _mm_sub_epi8(mul_all_u8x16(negate_u8x16(a_), b_), c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 fmaddsub_u8x16(EmuSIMD::u8x16_arg a_, EmuSIMD::u8x16_arg b_, EmuSIMD::u8x16_arg c_)
	{
		return addsub_u8x16(mul_all_u8x16(negate_u8x16(a_), b_), c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 fmsubadd_u8x16(EmuSIMD::u8x16_arg a_, EmuSIMD::u8x16_arg b_, EmuSIMD::u8x16_arg c_)
	{
		return subadd_u8x16(mul_all_u8x16(negate_u8x16(a_), b_), c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 floor_u8x16(EmuSIMD::u8x16_arg to_floor_)
	{
		return to_floor_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 ceil_u8x16(EmuSIMD::u8x16_arg to_ceil_)
	{
		return to_ceil_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 trunc_u8x16(EmuSIMD::u8x16_arg to_trunc_)
	{
		return to_trunc_;
	}

	template<int RoundingFlag_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 round_u8x16(EmuSIMD::u8x16_arg to_round_)
	{
		return to_round_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 mod_u8x16(EmuSIMD::u8x16_arg lhs_, EmuSIMD::u8x16_arg rhs_)
	{
#if EMU_CORE_X86_X64_SVML
		return _mm_rem_epu8(lhs_, rhs_);
#else
		EmuSIMD::u8x16 to_subtract = div_u8x16(lhs_, rhs_);
		to_subtract = mul_all_u8x16(to_subtract, rhs_);
		return sub_u8x16(lhs_, to_subtract);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 abs_u8x16(EmuSIMD::u8x16_arg in_)
	{
		return in_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 sqrt_u8x16(EmuSIMD::u8x16_arg in_)
	{
		return emulate_fp_u8x16([](EmuSIMD::f32x4_arg in_fp_) { return sqrt_f32x4(in_fp_); }, in_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 rsqrt_u8x16(EmuSIMD::u8x16_arg in_)
	{
		return emulate_fp_u8x16([](EmuSIMD::f32x4_arg in_fp_) { return rsqrt_f32x4(in_fp_); }, in_);
	}
#pragma endregion

#pragma region NEAR_COMPARISONS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cmpnear_u8x16(EmuSIMD::u8x16_arg lhs_, EmuSIMD::u8x16_arg rhs_)
	{
		return cmpeq_u8x16(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cmpnear_u8x16(EmuSIMD::u8x16_arg lhs_, EmuSIMD::u8x16_arg rhs_, EmuSIMD::u8x16_arg epsilon)
	{
		return cmple_u8x16(sub_u8x16(lhs_, rhs_), epsilon);
	}
#pragma endregion

#pragma region TRIG
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cos_u8x16(EmuSIMD::u8x16_arg in_)
	{
		return emulate_fp_u8x16([](EmuSIMD::f32x4_arg in_fp_) { return cos_f32x4(in_fp_); }, in_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 sin_u8x16(EmuSIMD::u8x16_arg in_)
	{
		return emulate_fp_u8x16([](EmuSIMD::f32x4_arg in_fp_) { return sin_f32x4(in_fp_); }, in_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 tan_u8x16(EmuSIMD::u8x16_arg in_)
	{
		return emulate_fp_u8x16([](EmuSIMD::f32x4_arg in_fp_) { return tan_f32x4(in_fp_); }, in_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 acos_u8x16(EmuSIMD::u8x16_arg in_)
	{
		return emulate_fp_u8x16([](EmuSIMD::f32x4_arg in_fp_) { return acos_f32x4(in_fp_); }, in_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 asin_u8x16(EmuSIMD::u8x16_arg in_)
	{
		return emulate_fp_u8x16([](EmuSIMD::f32x4_arg in_fp_) { return asin_f32x4(in_fp_); }, in_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 atan_u8x16(EmuSIMD::u8x16_arg in_)
	{
		return emulate_fp_u8x16([](EmuSIMD::f32x4_arg in_fp_) { return atan_f32x4(in_fp_); }, in_);
	}
#pragma endregion
}

#endif
