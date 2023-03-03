#ifndef EMU_SIMD_GENERIC_FUNCS_I16X16_H_INC_
#define EMU_SIMD_GENERIC_FUNCS_I16X16_H_INC_ 1

#include "_common_generic_func_helpers.h"
#include "_f32x8.h"

namespace EmuSIMD::Funcs
{
#pragma region SETTERS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 set_i16x16
	(
		std::int16_t e0, std::int16_t e1, std::int16_t e2, std::int16_t e3, std::int16_t e4, std::int16_t e5, std::int16_t e6, std::int16_t e7,
		std::int16_t e8, std::int16_t e9, std::int16_t e10, std::int16_t e11, std::int16_t e12, std::int16_t e13, std::int16_t e14, std::int16_t e15
	)
	{
		return _mm256_set_epi16(e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 setr_i16x16
	(
		std::int16_t e0, std::int16_t e1, std::int16_t e2, std::int16_t e3, std::int16_t e4, std::int16_t e5, std::int16_t e6, std::int16_t e7,
		std::int16_t e8, std::int16_t e9, std::int16_t e10, std::int16_t e11, std::int16_t e12, std::int16_t e13, std::int16_t e14, std::int16_t e15
	)
	{
		return _mm256_setr_epi16(e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 set1_i16x16(std::int16_t all_)
	{
		return _mm256_set1_epi16(all_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 load_i16x16(const std::int16_t* p_to_load_)
	{
		return _mm256_load_si256(reinterpret_cast<const __m256i*>(p_to_load_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 setzero_i16x16()
	{
		return _mm256_setzero_si256();
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 setmasked_i16x16(std::uint16_t bit_mask_)
	{
		constexpr std::int16_t element_mask = static_cast<std::int16_t>(0xFFFF);
		return _mm256_set_epi16
		(
			(bit_mask_  & 0x0001) * element_mask,
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
	EMU_SIMD_COMMON_FUNC_SPEC void store_i16x16(std::int16_t* p_out_, i16x16_arg a_)
	{
		_mm256_store_si256(reinterpret_cast<__m256i*>(p_out_), a_);
	}
#pragma endregion

#pragma region CASTS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cast_f32x4_i16x16(f32x4_arg a_)
	{
		return _mm256_castsi128_si256(_mm_castps_si128(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cast_f32x8_i16x16(f32x8_arg a_)
	{
		return _mm256_castps_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cast_f32x16_i16x16(f32x16_arg a_)
	{
		return _mm512_castsi512_si256(_mm512_castps_si512(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cast_f64x2_i16x16(f64x2_arg a_)
	{
		return _mm256_castsi128_si256(_mm_castpd_si128(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cast_f64x4_i16x16(f64x4_arg a_)
	{
		return _mm256_castpd_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cast_f64x8_i16x16(f64x8_arg a_)
	{
		return _mm512_castsi512_si256(_mm512_castpd_si512(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cast_i8x16_i16x16(i8x16_arg a_)
	{
		return _mm256_castsi128_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cast_i16x8_i16x16(i16x8_arg a_)
	{
		return _mm256_castsi128_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cast_i32x4_i16x16(i32x4_arg a_)
	{
		return _mm256_castsi128_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cast_i64x2_i16x16(i64x2_arg a_)
	{
		return _mm256_castsi128_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cast_i8x32_i16x16(i8x32_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cast_i16x16_i16x16(i16x16_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cast_i32x8_i16x16(i32x8_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cast_i64x4_i16x16(i64x4_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cast_i8x64_i16x16(i8x64_arg a_)
	{
		return _mm512_castsi512_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cast_i16x32_i16x16(i16x32_arg a_)
	{
		return _mm512_castsi512_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cast_i32x16_i16x16(i32x16_arg a_)
	{
		return _mm512_castsi512_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cast_i64x8_i16x16(i64x8_arg a_)
	{
		return _mm512_castsi512_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cast_u8x16_i16x16(u8x16_arg a_)
	{
		return _mm256_castsi128_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cast_u16x8_i16x16(u16x8_arg a_)
	{
		return _mm256_castsi128_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cast_u32x4_i16x16(u32x4_arg a_)
	{
		return _mm256_castsi128_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cast_u64x2_i16x16(u64x2_arg a_)
	{
		return _mm256_castsi128_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cast_u8x32_i16x16(u8x32_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cast_u16x16_i16x16(u16x16_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cast_u32x8_i16x16(u32x8_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cast_u64x4_i16x16(u64x4_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cast_u8x64_i16x16(u8x64_arg a_)
	{
		return _mm512_castsi512_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cast_u16x32_i16x16(u16x32_arg a_)
	{
		return _mm512_castsi512_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cast_u32x16_i16x16(u32x16_arg a_)
	{
		return _mm512_castsi512_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cast_u64x8_i16x16(u64x8_arg a_)
	{
		return _mm512_castsi512_si256(a_);
	}
#pragma endregion

#pragma region CONVERSIONS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cvt_f32x4_i16x16(f32x4_arg a_)
	{
		return _mm256_castsi128_si256(_mm_cvtepi32_epi16(_mm_cvtps_epi32(a_)));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cvt_f32x8_i16x16(f32x8_arg a_)
	{
		return _mm256_castsi128_si256(_mm256_cvtepi32_epi16(_mm256_cvtps_epi32(a_)));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cvt_f32x16_i16x16(f32x16_arg a_)
	{
		return _mm512_cvtepi32_epi16(_mm512_cvtps_epi32(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cvt_f64x2_i16x16(f64x2_arg a_)
	{
		return _mm256_castsi128_si256(_mm_cvtepi64_epi16(_mm_cvtpd_epi64(a_)));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cvt_f64x4_i16x16(f64x4_arg a_)
	{
		return _mm256_castsi128_si256(_mm256_cvtepi64_epi16(_mm256_cvtpd_epi64(a_)));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cvt_f64x8_i16x16(f64x8_arg a_)
	{
		return _mm256_castsi128_si256(_mm512_cvtepi64_epi16(_mm512_cvtpd_epi64(a_)));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cvt_i8x16_i16x16(i8x16_arg a_)
	{
		return _mm256_cvtepi8_epi16(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cvt_i16x8_i16x16(i16x8_arg a_)
	{
		return _mm256_castsi128_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cvt_i32x4_i16x16(i32x4_arg a_)
	{
		return _mm256_castsi128_si256(_mm_cvtepi32_epi16(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cvt_i64x2_i16x16(i64x2_arg a_)
	{
		return _mm256_castsi128_si256(_mm_cvtepi64_epi16(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cvt_i8x32_i16x16(i8x32_arg a_)
	{
		return _mm256_cvtepi8_epi16(_mm256_castsi256_si128(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cvt_i16x16_i16x16(i16x16_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cvt_i32x8_i16x16(i32x8_arg a_)
	{
		return _mm256_castsi128_si256(_mm256_cvtepi32_epi16(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cvt_i64x4_i16x16(i64x4_arg a_)
	{
		return _mm256_castsi128_si256(_mm256_cvtepi64_epi16(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cvt_i8x64_i16x16(i8x64_arg a_)
	{
		return _mm512_castsi512_si256(_mm512_cvtepi8_epi16(_mm512_castsi512_si256(a_)));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cvt_i16x32_i16x16(i16x32_arg a_)
	{
		return _mm512_castsi512_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cvt_i32x16_i16x16(i32x16_arg a_)
	{
		return _mm512_cvtepi32_epi16(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cvt_i64x8_i16x16(i64x8_arg a_)
	{
		return _mm256_castsi128_si256(_mm512_cvtepi64_epi16(a_));
	}






	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cvt_u8x16_i16x16(u8x16_arg a_)
	{
		return _mm256_castsi128_si256(_mm_cvtepu8_epi16(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cvt_u16x8_i16x16(u16x8_arg a_)
	{
		return _mm256_castsi128_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cvt_u32x4_i16x16(u32x4_arg a_)
	{
		return _mm256_castsi128_si256(_mm_cvtepi32_epi16(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cvt_u64x2_i16x16(u64x2_arg a_)
	{
		return _mm256_castsi128_si256(_mm_cvtepi64_epi16(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cvt_u8x32_i16x16(u8x32_arg a_)
	{
		return _mm256_cvtepu8_epi16(_mm256_castsi256_si128(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cvt_u16x16_i16x16(u16x16_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cvt_u32x8_i16x16(u32x8_arg a_)
	{
		return _mm256_castsi128_si256(_mm256_cvtepi32_epi16(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cvt_u64x4_i16x16(u64x4_arg a_)
	{
		return _mm256_castsi128_si256(_mm256_cvtepi64_epi16(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cvt_u8x64_i16x16(u8x64_arg a_)
	{
		return _mm512_castsi512_si256(_mm512_cvtepu8_epi16(_mm512_castsi512_si256(a_)));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cvt_u16x32_i16x16(u16x32_arg a_)
	{
		return _mm512_castsi512_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cvt_u32x16_i16x16(u32x16_arg a_)
	{
		return _mm512_cvtepi32_epi16(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cvt_u64x8_i16x16(u64x8_arg a_)
	{
		return _mm256_castsi128_si256(_mm512_cvtepi64_epi16(a_));
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
	EMU_SIMD_COMMON_FUNC_SPEC auto emulate_fp_i16x16(Func_ func_, EmuSIMD::i16x16_arg in_)
		-> std::enable_if_t<std::is_invocable_r_v<EmuSIMD::f32x8, decltype(func_), EmuSIMD::f32x8>, EmuSIMD::i16x16>
	{
		constexpr std::size_t num_elements = 16;
		constexpr std::size_t elements_per_register = 8;
		std::int16_t data[num_elements];
		float results[num_elements];

		store_i16x16(data, in_);
		for (std::size_t i = 0; i < num_elements; i += elements_per_register)
		{
			store_f32x8
			(
				results + i, 
				func_
				(
					set_f32x8
					(
						static_cast<float>(data[i + 7]), static_cast<float>(data[i + 6]), static_cast<float>(data[i + 5]), static_cast<float>(data[i + 4]),
						static_cast<float>(data[i + 3]), static_cast<float>(data[i + 2]), static_cast<float>(data[i + 1]), static_cast<float>(data[i])
					)
				)
			);
		}

		return set_i16x16
		(
			static_cast<std::int16_t>(results[15]),
			static_cast<std::int16_t>(results[14]),
			static_cast<std::int16_t>(results[13]),
			static_cast<std::int16_t>(results[12]),
			static_cast<std::int16_t>(results[11]),
			static_cast<std::int16_t>(results[10]),
			static_cast<std::int16_t>(results[9]),
			static_cast<std::int16_t>(results[8]),
			static_cast<std::int16_t>(results[7]),
			static_cast<std::int16_t>(results[6]),
			static_cast<std::int16_t>(results[5]),
			static_cast<std::int16_t>(results[4]),
			static_cast<std::int16_t>(results[3]),
			static_cast<std::int16_t>(results[2]),
			static_cast<std::int16_t>(results[1]),
			static_cast<std::int16_t>(results[0])
		);
	}
#pragma endregion

#pragma region COMPARISONS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cmpeq_i16x16(EmuSIMD::i16x16_arg lhs_, EmuSIMD::i16x16_arg rhs_)
	{
		return _mm256_cmpeq_epi16(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cmpneq_i16x16(EmuSIMD::i16x16_arg lhs_, EmuSIMD::i16x16_arg rhs_)
	{
		constexpr std::int16_t mask = static_cast<std::int16_t>(0xFFFF);
		return _mm256_xor_si256(set1_i16x16(mask), _mm256_cmpeq_epi16(lhs_, rhs_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cmpgt_i16x16(EmuSIMD::i16x16_arg lhs_, EmuSIMD::i16x16_arg rhs_)
	{
		return _mm256_cmpgt_epi16(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cmplt_i16x16(EmuSIMD::i16x16_arg lhs_, EmuSIMD::i16x16_arg rhs_)
	{
		return _mm256_cmpgt_epi16(rhs_, lhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cmpge_i16x16(EmuSIMD::i16x16_arg lhs_, EmuSIMD::i16x16_arg rhs_)
	{
		return _mm256_or_si256(_mm256_cmpgt_epi16(lhs_, rhs_), _mm256_cmpeq_epi16(lhs_, rhs_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cmple_i16x16(EmuSIMD::i16x16_arg lhs_, EmuSIMD::i16x16_arg rhs_)
	{
		return _mm256_or_si256(_mm256_cmpgt_epi16(rhs_, lhs_), _mm256_cmpeq_epi16(lhs_, rhs_));
	}
#pragma endregion

#pragma region BASIC_ARITHMETIC
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 mul_all_i16x16(EmuSIMD::i16x16_arg lhs_, EmuSIMD::i16x16_arg rhs_)
	{
		return _mm256_mullo_epi16(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 negate_i16x16(EmuSIMD::i16x16_arg to_negate_)
	{
		return _mm256_sub_epi16(_mm256_setzero_si256(), to_negate_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 add_i16x16(EmuSIMD::i16x16_arg lhs_, EmuSIMD::i16x16_arg rhs_)
	{
		return _mm256_add_epi16(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 sub_i16x16(EmuSIMD::i16x16_arg lhs_, EmuSIMD::i16x16_arg rhs_)
	{
		return _mm256_sub_epi16(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 mul_i16x16(EmuSIMD::i16x16_arg lhs_, EmuSIMD::i16x16_arg rhs_)
	{
		return _mm256_mul_epi32(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 div_i16x16(EmuSIMD::i16x16_arg lhs_, EmuSIMD::i16x16_arg rhs_)
	{
		return _mm256_div_epi16(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 addsub_i16x16(EmuSIMD::i16x16_arg lhs_, EmuSIMD::i16x16_arg rhs_)
	{
		constexpr std::int16_t bytes_mask = static_cast<std::int16_t>(0xFFFF);
		const EmuSIMD::i16x16 mask = _mm256_set_epi16(bytes_mask, 0, bytes_mask, 0, bytes_mask, 0, bytes_mask, 0, bytes_mask, 0, bytes_mask, 0, bytes_mask, 0, bytes_mask, 0);
		EmuSIMD::i16x16 out = _mm256_add_epi16(lhs_, _mm256_and_si256(mask, rhs_));
		return _mm256_sub_epi16(lhs_, _mm256_andnot_si256(mask, rhs_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 subadd_i16x16(EmuSIMD::i16x16_arg lhs_, EmuSIMD::i16x16_arg rhs_)
	{
		constexpr std::int16_t bytes_mask = static_cast<std::int16_t>(0xFFFF);
		const EmuSIMD::i16x16 mask = _mm256_set_epi16(bytes_mask, 0, bytes_mask, 0, bytes_mask, 0, bytes_mask, 0, bytes_mask, 0, bytes_mask, 0, bytes_mask, 0, bytes_mask, 0);
		EmuSIMD::i16x16 out = _mm256_sub_epi16(lhs_, _mm256_and_si256(mask, rhs_));
		return _mm256_add_epi16(lhs_, _mm256_andnot_si256(mask, rhs_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 fmadd_i16x16(EmuSIMD::i16x16_arg a_, EmuSIMD::i16x16_arg b_, EmuSIMD::i16x16_arg c_)
	{
		return _mm256_add_epi16(mul_all_i16x16(a_, b_), c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 fmsub_i16x16(EmuSIMD::i16x16_arg a_, EmuSIMD::i16x16_arg b_, EmuSIMD::i16x16_arg c_)
	{
		return _mm256_sub_epi16(mul_all_i16x16(a_, b_), c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 fnmadd_i16x16(EmuSIMD::i16x16_arg a_, EmuSIMD::i16x16_arg b_, EmuSIMD::i16x16_arg c_)
	{
		return _mm256_add_epi16(mul_all_i16x16(negate_i16x16(a_), b_), c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 fnmsub_i16x16(EmuSIMD::i16x16_arg a_, EmuSIMD::i16x16_arg b_, EmuSIMD::i16x16_arg c_)
	{
		return _mm256_sub_epi16(mul_all_i16x16(negate_i16x16(a_), b_), c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 fmaddsub_i16x16(EmuSIMD::i16x16_arg a_, EmuSIMD::i16x16_arg b_, EmuSIMD::i16x16_arg c_)
	{
		return addsub_i16x16(mul_all_i16x16(a_, b_), c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 fmsubadd_i16x16(EmuSIMD::i16x16_arg a_, EmuSIMD::i16x16_arg b_, EmuSIMD::i16x16_arg c_)
	{
		return subadd_i16x16(mul_all_i16x16(a_, b_), c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 floor_i16x16(EmuSIMD::i16x16_arg to_floor_)
	{
		return to_floor_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 ceil_i16x16(EmuSIMD::i16x16_arg to_ceil_)
	{
		return to_ceil_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 trunc_i16x16(EmuSIMD::i16x16_arg to_trunc_)
	{
		return to_trunc_;
	}

	template<int RoundingFlag_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 round_i16x16(EmuSIMD::i16x16_arg to_round_)
	{
		return to_round_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 mod_i16x16(EmuSIMD::i16x16_arg lhs_, EmuSIMD::i16x16_arg rhs_)
	{
		return _mm256_rem_epi16(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 abs_i16x16(EmuSIMD::i16x16_arg in_)
	{
		return _mm256_abs_epi16(in_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 sqrt_i16x16(EmuSIMD::i16x16_arg in_)
	{
		return emulate_fp_i16x16([](EmuSIMD::f32x8_arg in_fp_) { return sqrt_f32x8(in_fp_); }, in_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 rsqrt_i16x16(EmuSIMD::i16x16_arg in_)
	{
		return emulate_fp_i16x16([](EmuSIMD::f32x8_arg in_fp_) { return rsqrt_f32x8(in_fp_); }, in_);
	}
#pragma endregion

#pragma region NEAR_COMPARISONS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cmpnear_i16x16(EmuSIMD::i16x16_arg lhs_, EmuSIMD::i16x16_arg rhs_)
	{
		return cmpeq_i16x16(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cmpnear_i16x16(EmuSIMD::i16x16_arg lhs_, EmuSIMD::i16x16_arg rhs_, EmuSIMD::i16x16_arg epsilon)
	{
		return cmple_i16x16(abs_i16x16(sub_i16x16(lhs_, rhs_)), epsilon);
	}
#pragma endregion

#pragma region TRIG
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cos_i16x16(EmuSIMD::i16x16_arg in_)
	{
		return emulate_fp_i16x16([](EmuSIMD::f32x8_arg in_fp_) { return cos_f32x8(in_fp_); }, in_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 sin_i16x16(EmuSIMD::i16x16_arg in_)
	{
		return emulate_fp_i16x16([](EmuSIMD::f32x8_arg in_fp_) { return sin_f32x8(in_fp_); }, in_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 tan_i16x16(EmuSIMD::i16x16_arg in_)
	{
		return emulate_fp_i16x16([](EmuSIMD::f32x8_arg in_fp_) { return tan_f32x8(in_fp_); }, in_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 acos_i16x16(EmuSIMD::i16x16_arg in_)
	{
		return emulate_fp_i16x16([](EmuSIMD::f32x8_arg in_fp_) { return acos_f32x8(in_fp_); }, in_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 asin_i16x16(EmuSIMD::i16x16_arg in_)
	{
		return emulate_fp_i16x16([](EmuSIMD::f32x8_arg in_fp_) { return asin_f32x8(in_fp_); }, in_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 atan_i16x16(EmuSIMD::i16x16_arg in_)
	{
		return emulate_fp_i16x16([](EmuSIMD::f32x8_arg in_fp_) { return atan_f32x8(in_fp_); }, in_);
	}
#pragma endregion
}

#endif
