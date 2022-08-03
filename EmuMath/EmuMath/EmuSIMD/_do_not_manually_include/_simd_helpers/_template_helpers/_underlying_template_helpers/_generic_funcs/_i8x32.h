#ifndef EMU_SIMD_GENERIC_FUNCS_I8X32_H_INC_
#define EMU_SIMD_GENERIC_FUNCS_I8X32_H_INC_ 1

#include "_common_generic_func_helpers.h"

namespace EmuSIMD::Funcs
{
#pragma region SETTERS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 set_i8x32
	(
		std::int8_t e0, std::int8_t e1, std::int8_t e2, std::int8_t e3, std::int8_t e4, std::int8_t e5, std::int8_t e6, std::int8_t e7,
		std::int8_t e8, std::int8_t e9, std::int8_t e10, std::int8_t e11, std::int8_t e12, std::int8_t e13, std::int8_t e14, std::int8_t e15,
		std::int8_t e16, std::int8_t e17, std::int8_t e18, std::int8_t e19, std::int8_t e20, std::int8_t e21, std::int8_t e22, std::int8_t e23,
		std::int8_t e24, std::int8_t e25, std::int8_t e26, std::int8_t e27, std::int8_t e28, std::int8_t e29, std::int8_t e30, std::int8_t e31
	)
	{
		return _mm256_set_epi8(e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19, e20, e21, e22, e23, e24, e25, e26, e27, e28, e29, e30, e31);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 setr_i8x32
	(
		std::int8_t e0, std::int8_t e1, std::int8_t e2, std::int8_t e3, std::int8_t e4, std::int8_t e5, std::int8_t e6, std::int8_t e7,
		std::int8_t e8, std::int8_t e9, std::int8_t e10, std::int8_t e11, std::int8_t e12, std::int8_t e13, std::int8_t e14, std::int8_t e15,
		std::int8_t e16, std::int8_t e17, std::int8_t e18, std::int8_t e19, std::int8_t e20, std::int8_t e21, std::int8_t e22, std::int8_t e23,
		std::int8_t e24, std::int8_t e25, std::int8_t e26, std::int8_t e27, std::int8_t e28, std::int8_t e29, std::int8_t e30, std::int8_t e31
	)
	{
		return _mm256_setr_epi8(e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19, e20, e21, e22, e23, e24, e25, e26, e27, e28, e29, e30, e31);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 set1_i8x32(std::int8_t all_)
	{
		return _mm256_set1_epi8(all_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 load_i8x32(const std::int8_t* p_to_load_)
	{
		return _mm256_load_si256(reinterpret_cast<const __m256i*>(p_to_load_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 setzero_i8x32()
	{
		return _mm256_setzero_si256();
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 setmasked_i8x32(std::uint32_t bit_mask_)
	{
		constexpr std::int8_t element_mask = static_cast<std::int8_t>(0xFF);
		return _mm256_set_epi8
		(
			(bit_mask_ & 0x00000001) * element_mask,
			((bit_mask_ & 0x00000002) >> 1) * element_mask,
			((bit_mask_ & 0x00000004) >> 2) * element_mask,
			((bit_mask_ & 0x00000008) >> 3) * element_mask,
			((bit_mask_ & 0x00000010) >> 4) * element_mask,
			((bit_mask_ & 0x00000020) >> 5) * element_mask,
			((bit_mask_ & 0x00000040) >> 6) * element_mask,
			((bit_mask_ & 0x00000080) >> 7) * element_mask,
			((bit_mask_ & 0x00000100) >> 8) * element_mask,
			((bit_mask_ & 0x00000200) >> 9) * element_mask,
			((bit_mask_ & 0x00000400) >> 10) * element_mask,
			((bit_mask_ & 0x00000800) >> 11) * element_mask,
			((bit_mask_ & 0x00001000) >> 12) * element_mask,
			((bit_mask_ & 0x00002000) >> 13) * element_mask,
			((bit_mask_ & 0x00004000) >> 14) * element_mask,
			((bit_mask_ & 0x00008000) >> 15) * element_mask,
			((bit_mask_ & 0x00010000) >> 16) * element_mask,
			((bit_mask_ & 0x00020000) >> 17) * element_mask,
			((bit_mask_ & 0x00040000) >> 18) * element_mask,
			((bit_mask_ & 0x00080000) >> 19) * element_mask,
			((bit_mask_ & 0x00100000) >> 20) * element_mask,
			((bit_mask_ & 0x00200000) >> 21) * element_mask,
			((bit_mask_ & 0x00400000) >> 22) * element_mask,
			((bit_mask_ & 0x00800000) >> 23) * element_mask,
			((bit_mask_ & 0x01000000) >> 24) * element_mask,
			((bit_mask_ & 0x02000000) >> 25) * element_mask,
			((bit_mask_ & 0x04000000) >> 26) * element_mask,
			((bit_mask_ & 0x08000000) >> 27) * element_mask,
			((bit_mask_ & 0x10000000) >> 28) * element_mask,
			((bit_mask_ & 0x20000000) >> 29) * element_mask,
			((bit_mask_ & 0x40000000) >> 30) * element_mask,
			((bit_mask_ & 0x80000000) >> 31) * element_mask
		);
	}
#pragma endregion

#pragma region STORES
	EMU_SIMD_COMMON_FUNC_SPEC void store_i8x32(std::int8_t* p_out_, i8x32_arg a_)
	{
		_mm256_store_si256(reinterpret_cast<__m256i*>(p_out_), a_);
	}
#pragma endregion

#pragma region CASTS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 cast_f32x4_i8x32(f32x4_arg a_)
	{
		return _mm256_castsi128_si256(_mm_castps_si128(a_)); 
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 cast_f32x8_i8x32(f32x8_arg a_)
	{
		return _mm256_castps_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 cast_f32x16_i8x32(f32x16_arg a_)
	{
		return _mm512_castsi512_si256(_mm512_castps_si512(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 cast_f64x2_i8x32(f64x2_arg a_)
	{
		return _mm256_castsi128_si256(_mm_castpd_si128(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 cast_f64x4_i8x32(f64x4_arg a_)
	{
		return _mm256_castpd_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 cast_f64x8_i8x32(f64x8_arg a_)
	{
		return _mm512_castsi512_si256(_mm512_castpd_si512(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 cast_i8x16_i8x32(i8x16_arg a_)
	{
		return _mm256_castsi128_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 cast_i16x8_i8x32(i16x8_arg a_)
	{
		return _mm256_castsi128_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 cast_i32x4_i8x32(i32x4_arg a_)
	{
		return _mm256_castsi128_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 cast_i64x2_i8x32(i64x2_arg a_)
	{
		return _mm256_castsi128_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 cast_i8x32_i8x32(i8x32_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 cast_i16x16_i8x32(i16x16_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 cast_i32x8_i8x32(i32x8_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 cast_i64x4_i8x32(i64x4_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 cast_i8x64_i8x32(i8x64_arg a_)
	{
		return _mm512_castsi512_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 cast_i16x32_i8x32(i16x32_arg a_)
	{
		return _mm512_castsi512_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 cast_i32x16_i8x32(i32x16_arg a_)
	{
		return _mm512_castsi512_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 cast_i64x8_i8x32(i64x8_arg a_)
	{
		return _mm512_castsi512_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 cast_u8x16_i8x32(u8x16_arg a_)
	{
		return _mm256_castsi128_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 cast_u16x8_i8x32(u16x8_arg a_)
	{
		return _mm256_castsi128_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 cast_u32x4_i8x32(u32x4_arg a_)
	{
		return _mm256_castsi128_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 cast_u64x2_i8x32(u64x2_arg a_)
	{
		return _mm256_castsi128_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 cast_u8x32_i8x32(u8x32_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 cast_u16x16_i8x32(u16x16_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 cast_u32x8_i8x32(u32x8_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 cast_u64x4_i8x32(u64x4_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 cast_u8x64_i8x32(u8x64_arg a_)
	{
		return _mm512_castsi512_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 cast_u16x32_i8x32(u16x32_arg a_)
	{
		return _mm512_castsi512_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 cast_u32x16_i8x32(u32x16_arg a_)
	{
		return _mm512_castsi512_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 cast_u64x8_i8x32(u64x8_arg a_)
	{
		return _mm512_castsi512_si256(a_);
	}
#pragma endregion

#pragma region CONVERSIONS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 cvt_f32x4_i8x32(f32x4_arg a_)
	{
		return _mm256_castsi128_si256(_mm_cvtepi32_epi8(_mm_cvtps_epi32(a_)));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 cvt_f32x8_i8x32(f32x8_arg a_)
	{
		return _mm256_castsi128_si256(_mm256_cvtepi32_epi8(_mm256_cvtps_epi32(a_)));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 cvt_f32x16_i8x32(f32x16_arg a_)
	{
		return _mm256_castsi128_si256(_mm512_cvtepi32_epi8(_mm512_cvtps_epi32(a_)));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 cvt_f64x2_i8x32(f64x2_arg a_)
	{
		return _mm256_castsi128_si256(_mm_cvtepi64_epi8(_mm_cvtpd_epi64(a_)));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 cvt_f64x4_i8x32(f64x4_arg a_)
	{
		return _mm256_castsi128_si256(_mm256_cvtepi64_epi8(_mm256_cvtpd_epi64(a_)));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 cvt_f64x8_i8x32(f64x8_arg a_)
	{
		return _mm256_castsi128_si256(_mm512_cvtepi64_epi8(_mm512_cvtpd_epi64(a_)));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 cvt_i8x16_i8x32(i8x16_arg a_)
	{
		return _mm256_castsi128_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 cvt_i16x8_i8x32(i16x8_arg a_)
	{
		return _mm256_castsi128_si256(_mm_cvtepi16_epi8(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 cvt_i32x4_i8x32(i32x4_arg a_)
	{
		return _mm256_castsi128_si256(_mm_cvtepi32_epi8(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 cvt_i64x2_i8x32(i64x2_arg a_)
	{
		return _mm256_castsi128_si256(_mm_cvtepi64_epi8(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 cvt_i8x32_i8x32(i8x32_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 cvt_i16x16_i8x32(i16x16_arg a_)
	{
		return _mm256_castsi128_si256(_mm256_cvtepi16_epi8(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 cvt_i32x8_i8x32(i32x8_arg a_)
	{
		return _mm256_castsi128_si256(_mm256_cvtepi32_epi8(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 cvt_i64x4_i8x32(i64x4_arg a_)
	{
		return _mm256_castsi128_si256(_mm256_cvtepi64_epi8(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 cvt_i8x64_i8x32(i8x64_arg a_)
	{
		return _mm512_castsi512_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 cvt_i16x32_i8x32(i16x32_arg a_)
	{
		return _mm512_cvtepi16_epi8(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 cvt_i32x16_i8x32(i32x16_arg a_)
	{
		return _mm256_castsi128_si256(_mm512_cvtepi32_epi8(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 cvt_i64x8_i8x32(i64x8_arg a_)
	{
		return _mm256_castsi128_si256(_mm512_cvtepi64_epi8(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 cvt_u8x16_i8x32(u8x16_arg a_)
	{
		return _mm256_castsi128_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 cvt_u16x8_i8x32(u16x8_arg a_)
	{
		return _mm256_castsi128_si256(_mm_cvtepi16_epi8(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 cvt_u32x4_i8x32(u32x4_arg a_)
	{
		return _mm256_castsi128_si256(_mm_cvtepi32_epi8(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 cvt_u64x2_i8x32(u64x2_arg a_)
	{
		return _mm256_castsi128_si256(_mm_cvtepi64_epi8(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 cvt_u8x32_i8x32(u8x32_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 cvt_u16x16_i8x32(u16x16_arg a_)
	{
		return _mm256_castsi128_si256(_mm256_cvtepi16_epi8(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 cvt_u32x8_i8x32(u32x8_arg a_)
	{
		return _mm256_castsi128_si256(_mm256_cvtepi32_epi8(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 cvt_u64x4_i8x32(u64x4_arg a_)
	{
		return _mm256_castsi128_si256(_mm256_cvtepi64_epi8(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 cvt_u8x64_i8x32(u8x64_arg a_)
	{
		return _mm512_castsi512_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 cvt_u16x32_i8x32(u16x32_arg a_)
	{
		return _mm512_cvtepi16_epi8(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 cvt_u32x16_i8x32(u32x16_arg a_)
	{
		return _mm256_castsi128_si256(_mm512_cvtepi32_epi8(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 cvt_u64x8_i8x32(u64x8_arg a_)
	{
		return _mm256_castsi128_si256(_mm512_cvtepi64_epi8(a_));
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
	EMU_SIMD_COMMON_FUNC_SPEC auto emulate_fp_i8x32(Func_ func_, EmuSIMD::i8x32_arg in_)
		-> std::enable_if_t<std::is_invocable_r_v<EmuSIMD::f32x8, decltype(func_), EmuSIMD::f32x8>, EmuSIMD::i8x32>
	{
		constexpr std::size_t num_elements = 32;
		constexpr std::size_t elements_per_register = 8;
		std::int8_t data[num_elements];
		float results[num_elements];

		store_i8x32(data, in_);
		for (std::size_t i = 0; i < num_elements; i += elements_per_register)
		{
			_mm256_store_ps(results + i, func_(_mm256_set_ps(data[i + 7], data[i + 6], data[i + 5], data[i + 4], data[i + 3], data[i + 2], data[i + 1], data[i])));
		}

		return set_i8x32
		(

			static_cast<std::int8_t>(results[31]),
			static_cast<std::int8_t>(results[30]),
			static_cast<std::int8_t>(results[29]),
			static_cast<std::int8_t>(results[28]),
			static_cast<std::int8_t>(results[27]),
			static_cast<std::int8_t>(results[26]),
			static_cast<std::int8_t>(results[25]),
			static_cast<std::int8_t>(results[24]),
			static_cast<std::int8_t>(results[23]),
			static_cast<std::int8_t>(results[22]),
			static_cast<std::int8_t>(results[21]),
			static_cast<std::int8_t>(results[20]),
			static_cast<std::int8_t>(results[19]),
			static_cast<std::int8_t>(results[18]),
			static_cast<std::int8_t>(results[17]),
			static_cast<std::int8_t>(results[16]),
			static_cast<std::int8_t>(results[15]),
			static_cast<std::int8_t>(results[14]),
			static_cast<std::int8_t>(results[13]),
			static_cast<std::int8_t>(results[12]),
			static_cast<std::int8_t>(results[11]),
			static_cast<std::int8_t>(results[10]),
			static_cast<std::int8_t>(results[9]),
			static_cast<std::int8_t>(results[8]),
			static_cast<std::int8_t>(results[7]),
			static_cast<std::int8_t>(results[6]),
			static_cast<std::int8_t>(results[5]),
			static_cast<std::int8_t>(results[4]),
			static_cast<std::int8_t>(results[3]),
			static_cast<std::int8_t>(results[2]),
			static_cast<std::int8_t>(results[1]),
			static_cast<std::int8_t>(results[0])
		);
	}
#pragma endregion

#pragma region COMPARISONS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 cmpeq_i8x32(EmuSIMD::i8x32_arg lhs_, EmuSIMD::i8x32_arg rhs_)
	{
		return _mm256_cmpeq_epi8(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 cmpneq_i8x32(EmuSIMD::i8x32_arg lhs_, EmuSIMD::i8x32_arg rhs_)
	{
		constexpr std::int8_t mask = static_cast<std::int8_t>(0xFF);
		return _mm256_xor_si256(set1_i8x32(mask), _mm256_cmpeq_epi8(lhs_, rhs_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 cmpgt_i8x32(EmuSIMD::i8x32_arg lhs_, EmuSIMD::i8x32_arg rhs_)
	{
		return _mm256_cmpgt_epi8(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 cmplt_i8x32(EmuSIMD::i8x32_arg lhs_, EmuSIMD::i8x32_arg rhs_)
	{
		return _mm256_cmpgt_epi8(rhs_, lhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 cmpge_i8x32(EmuSIMD::i8x32_arg lhs_, EmuSIMD::i8x32_arg rhs_)
	{
		return _mm256_or_si256(_mm256_cmpgt_epi8(lhs_, rhs_), _mm256_cmpeq_epi8(lhs_, rhs_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 cmple_i8x32(EmuSIMD::i8x32_arg lhs_, EmuSIMD::i8x32_arg rhs_)
	{
		return _mm256_or_si256(_mm256_cmpgt_epi8(rhs_, lhs_), _mm256_cmpeq_epi8(lhs_, rhs_));
	}
#pragma endregion

#pragma region BASIC_ARITHMETIC
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 mul_all_i8x32(EmuSIMD::i8x32_arg lhs_, EmuSIMD::i8x32_arg rhs_)
	{
		EmuSIMD::i8x32 even_bytes = _mm256_mullo_epi16(lhs_, rhs_);
		EmuSIMD::i8x32 odd_bytes = _mm256_mullo_epi16(_mm256_srli_epi16(lhs_, 8), _mm256_srli_epi16(rhs_, 8));
		return _mm256_or_si256(_mm256_slli_epi16(odd_bytes, 8), _mm256_srli_epi16(_mm256_slli_epi16(even_bytes, 8), 8));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 negate_i8x32(EmuSIMD::i8x32_arg to_negate_)
	{
		return _mm256_sub_epi8(_mm256_setzero_si256(), to_negate_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 add_i8x32(EmuSIMD::i8x32_arg lhs_, EmuSIMD::i8x32_arg rhs_)
	{
		return _mm256_add_epi8(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 sub_i8x32(EmuSIMD::i8x32_arg lhs_, EmuSIMD::i8x32_arg rhs_)
	{
		return _mm256_sub_epi8(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 mul_i8x32(EmuSIMD::i8x32_arg lhs_, EmuSIMD::i8x32_arg rhs_)
	{
		return _mm256_mul_epi32(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 div_i8x32(EmuSIMD::i8x32_arg lhs_, EmuSIMD::i8x32_arg rhs_)
	{
		return _mm256_div_epi8(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 addsub_i8x32(EmuSIMD::i8x32_arg lhs_, EmuSIMD::i8x32_arg rhs_)
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

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 subadd_i8x32(EmuSIMD::i8x32_arg lhs_, EmuSIMD::i8x32_arg rhs_)
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

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 fmadd_i8x32(EmuSIMD::i8x32_arg a_, EmuSIMD::i8x32_arg b_, EmuSIMD::i8x32_arg c_)
	{
		return _mm256_add_epi8(mul_all_i8x32(a_, b_), c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 fmsub_i8x32(EmuSIMD::i8x32_arg a_, EmuSIMD::i8x32_arg b_, EmuSIMD::i8x32_arg c_)
	{
		return _mm256_sub_epi8(mul_all_i8x32(a_, b_), c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 fnmadd_i8x32(EmuSIMD::i8x32_arg a_, EmuSIMD::i8x32_arg b_, EmuSIMD::i8x32_arg c_)
	{
		return _mm256_add_epi8(mul_all_i8x32(negate_i8x32(a_), b_), c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 fnmsub_i8x32(EmuSIMD::i8x32_arg a_, EmuSIMD::i8x32_arg b_, EmuSIMD::i8x32_arg c_)
	{
		return _mm256_sub_epi8(mul_all_i8x32(negate_i8x32(a_), b_), c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 fmaddsub_i8x32(EmuSIMD::i8x32_arg a_, EmuSIMD::i8x32_arg b_, EmuSIMD::i8x32_arg c_)
	{
		return addsub_i8x32(mul_all_i8x32(negate_i8x32(a_), b_), c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 fmsubadd_i8x32(EmuSIMD::i8x32_arg a_, EmuSIMD::i8x32_arg b_, EmuSIMD::i8x32_arg c_)
	{
		return subadd_i8x32(mul_all_i8x32(negate_i8x32(a_), b_), c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 floor_i8x32(EmuSIMD::i8x32_arg to_floor_)
	{
		return to_floor_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 ceil_i8x32(EmuSIMD::i8x32_arg to_ceil_)
	{
		return to_ceil_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 trunc_i8x32(EmuSIMD::i8x32_arg to_trunc_)
	{
		return to_trunc_;
	}

	template<int RoundingFlag_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 round_i8x32(EmuSIMD::i8x32_arg to_round_)
	{
		return to_round_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 mod_i8x32(EmuSIMD::i8x32_arg lhs_, EmuSIMD::i8x32_arg rhs_)
	{
		return _mm256_rem_epi8(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 abs_i8x32(EmuSIMD::i8x32_arg in_)
	{
		return _mm256_abs_epi8(in_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 sqrt_i8x32(EmuSIMD::i8x32_arg in_)
	{
		return emulate_fp_i8x32([](EmuSIMD::f32x8_arg in_fp_) { return _mm256_sqrt_ps(in_fp_); }, in_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 rsqrt_i8x32(EmuSIMD::i8x32_arg in_)
	{
		return emulate_fp_i8x32([](EmuSIMD::f32x8_arg in_fp_) { return _mm256_rsqrt_ps(in_fp_); }, in_);
	}
#pragma endregion

#pragma region NEAR_COMPARISONS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 cmpnear_i8x32(EmuSIMD::i8x32_arg lhs_, EmuSIMD::i8x32_arg rhs_)
	{
		return cmpeq_i8x32(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 cmpnear_i8x32(EmuSIMD::i8x32_arg lhs_, EmuSIMD::i8x32_arg rhs_, EmuSIMD::i8x32_arg epsilon)
	{
		return cmple_i8x32(abs_i8x32(sub_i8x32(lhs_, rhs_)), epsilon);
	}
#pragma endregion

#pragma region TRIG
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 cos_i8x32(EmuSIMD::i8x32_arg in_)
	{
		return emulate_fp_i8x32([](EmuSIMD::f32x8_arg in_fp_) { return _mm256_cos_ps(in_fp_); }, in_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 sin_i8x32(EmuSIMD::i8x32_arg in_)
	{
		return emulate_fp_i8x32([](EmuSIMD::f32x8_arg in_fp_) { return _mm256_sin_ps(in_fp_); }, in_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 tan_i8x32(EmuSIMD::i8x32_arg in_)
	{
		return emulate_fp_i8x32([](EmuSIMD::f32x8_arg in_fp_) { return _mm256_tan_ps(in_fp_); }, in_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 acos_i8x32(EmuSIMD::i8x32_arg in_)
	{
		return emulate_fp_i8x32([](EmuSIMD::f32x8_arg in_fp_) { return _mm256_acos_ps(in_fp_); }, in_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 asin_i8x32(EmuSIMD::i8x32_arg in_)
	{
		return emulate_fp_i8x32([](EmuSIMD::f32x8_arg in_fp_) { return _mm256_asin_ps(in_fp_); }, in_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 atan_i8x32(EmuSIMD::i8x32_arg in_)
	{
		return emulate_fp_i8x32([](EmuSIMD::f32x8_arg in_fp_) { return _mm256_atan_ps(in_fp_); }, in_);
	}
#pragma endregion
}

#endif