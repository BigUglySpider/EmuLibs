#ifndef EMU_SIMD_GENERIC_FUNCS_U8X64_H_INC_
#define EMU_SIMD_GENERIC_FUNCS_U8X64_H_INC_ 1

#include "_common_generic_func_helpers.h"
#include "_f32x16.h"
#include "_u16x32.h"

namespace EmuSIMD::Funcs
{
#pragma region SETTERS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 set_u8x64
	(
		std::uint8_t e0, std::uint8_t e1, std::uint8_t e2, std::uint8_t e3, std::uint8_t e4, std::uint8_t e5, std::uint8_t e6, std::uint8_t e7,
		std::uint8_t e8, std::uint8_t e9, std::uint8_t e10, std::uint8_t e11, std::uint8_t e12, std::uint8_t e13, std::uint8_t e14, std::uint8_t e15,
		std::uint8_t e16, std::uint8_t e17, std::uint8_t e18, std::uint8_t e19, std::uint8_t e20, std::uint8_t e21, std::uint8_t e22, std::uint8_t e23,
		std::uint8_t e24, std::uint8_t e25, std::uint8_t e26, std::uint8_t e27, std::uint8_t e28, std::uint8_t e29, std::uint8_t e30, std::uint8_t e31,
		std::uint8_t e32, std::uint8_t e33, std::uint8_t e34, std::uint8_t e35, std::uint8_t e36, std::uint8_t e37, std::uint8_t e38, std::uint8_t e39,
		std::uint8_t e40, std::uint8_t e41, std::uint8_t e42, std::uint8_t e43, std::uint8_t e44, std::uint8_t e45, std::uint8_t e46, std::uint8_t e47,
		std::uint8_t e48, std::uint8_t e49, std::uint8_t e50, std::uint8_t e51, std::uint8_t e52, std::uint8_t e53, std::uint8_t e54, std::uint8_t e55,
		std::uint8_t e56, std::uint8_t e57, std::uint8_t e58, std::uint8_t e59, std::uint8_t e60, std::uint8_t e61, std::uint8_t e62, std::uint8_t e63
	)
	{
		return _mm512_set_epi8
		(
			e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19, e20, e21, e22, e23, e24, e25, e26, e27, e28, e29, e30, e31,
			e32, e33, e34, e35, e36, e37, e38, e39, e40, e41, e42, e43, e44, e45, e46, e47, e48, e49, e50, e51, e52, e53, e54, e55, e56, e57, e58, e59, e60, e61, e62, e63
		);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 setr_u8x64
	(
		std::uint8_t e0, std::uint8_t e1, std::uint8_t e2, std::uint8_t e3, std::uint8_t e4, std::uint8_t e5, std::uint8_t e6, std::uint8_t e7,
		std::uint8_t e8, std::uint8_t e9, std::uint8_t e10, std::uint8_t e11, std::uint8_t e12, std::uint8_t e13, std::uint8_t e14, std::uint8_t e15,
		std::uint8_t e16, std::uint8_t e17, std::uint8_t e18, std::uint8_t e19, std::uint8_t e20, std::uint8_t e21, std::uint8_t e22, std::uint8_t e23,
		std::uint8_t e24, std::uint8_t e25, std::uint8_t e26, std::uint8_t e27, std::uint8_t e28, std::uint8_t e29, std::uint8_t e30, std::uint8_t e31,
		std::uint8_t e32, std::uint8_t e33, std::uint8_t e34, std::uint8_t e35, std::uint8_t e36, std::uint8_t e37, std::uint8_t e38, std::uint8_t e39,
		std::uint8_t e40, std::uint8_t e41, std::uint8_t e42, std::uint8_t e43, std::uint8_t e44, std::uint8_t e45, std::uint8_t e46, std::uint8_t e47,
		std::uint8_t e48, std::uint8_t e49, std::uint8_t e50, std::uint8_t e51, std::uint8_t e52, std::uint8_t e53, std::uint8_t e54, std::uint8_t e55,
		std::uint8_t e56, std::uint8_t e57, std::uint8_t e58, std::uint8_t e59, std::uint8_t e60, std::uint8_t e61, std::uint8_t e62, std::uint8_t e63
	)
	{
		return _mm512_setr_epi8
		(
			e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19, e20, e21, e22, e23, e24, e25, e26, e27, e28, e29, e30, e31,
			e32, e33, e34, e35, e36, e37, e38, e39, e40, e41, e42, e43, e44, e45, e46, e47, e48, e49, e50, e51, e52, e53, e54, e55, e56, e57, e58, e59, e60, e61, e62, e63
		);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 set1_u8x64(std::uint8_t all_)
	{
		return _mm512_set1_epi8(all_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 load_u8x64(const std::uint8_t* p_to_load_)
	{
		return _mm512_load_si512(p_to_load_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 setzero_u8x64()
	{
		return _mm512_setzero_si512();
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 setmasked_u8x64(std::uint64_t bit_mask_)
	{
		constexpr std::uint8_t element_mask = static_cast<std::uint8_t>(0xFF);
		return _mm512_set_epi8
		(
			static_cast<std::int8_t>(bit_mask_  & 0x0000000000000001) * element_mask,
			static_cast<std::int8_t>((bit_mask_ & 0x0000000000000002) >> 1) * element_mask,
			static_cast<std::int8_t>((bit_mask_ & 0x0000000000000004) >> 2) * element_mask,
			static_cast<std::int8_t>((bit_mask_ & 0x0000000000000008) >> 3) * element_mask,
			static_cast<std::int8_t>((bit_mask_ & 0x0000000000000010) >> 4) * element_mask,
			static_cast<std::int8_t>((bit_mask_ & 0x0000000000000020) >> 5) * element_mask,
			static_cast<std::int8_t>((bit_mask_ & 0x0000000000000040) >> 6) * element_mask,
			static_cast<std::int8_t>((bit_mask_ & 0x0000000000000080) >> 7) * element_mask,
			static_cast<std::int8_t>((bit_mask_ & 0x0000000000000100) >> 8) * element_mask,
			static_cast<std::int8_t>((bit_mask_ & 0x0000000000000200) >> 9) * element_mask,
			static_cast<std::int8_t>((bit_mask_ & 0x0000000000000400) >> 10) * element_mask,
			static_cast<std::int8_t>((bit_mask_ & 0x0000000000000800) >> 11) * element_mask,
			static_cast<std::int8_t>((bit_mask_ & 0x0000000000001000) >> 12) * element_mask,
			static_cast<std::int8_t>((bit_mask_ & 0x0000000000002000) >> 13) * element_mask,
			static_cast<std::int8_t>((bit_mask_ & 0x0000000000004000) >> 14) * element_mask,
			static_cast<std::int8_t>((bit_mask_ & 0x0000000000008000) >> 15) * element_mask,
			static_cast<std::int8_t>((bit_mask_ & 0x0000000000010000) >> 16) * element_mask,
			static_cast<std::int8_t>((bit_mask_ & 0x0000000000020000) >> 17) * element_mask,
			static_cast<std::int8_t>((bit_mask_ & 0x0000000000040000) >> 18) * element_mask,
			static_cast<std::int8_t>((bit_mask_ & 0x0000000000080000) >> 19) * element_mask,
			static_cast<std::int8_t>((bit_mask_ & 0x0000000000100000) >> 20) * element_mask,
			static_cast<std::int8_t>((bit_mask_ & 0x0000000000200000) >> 21) * element_mask,
			static_cast<std::int8_t>((bit_mask_ & 0x0000000000400000) >> 22) * element_mask,
			static_cast<std::int8_t>((bit_mask_ & 0x0000000000800000) >> 23) * element_mask,
			static_cast<std::int8_t>((bit_mask_ & 0x0000000001000000) >> 24) * element_mask,
			static_cast<std::int8_t>((bit_mask_ & 0x0000000002000000) >> 25) * element_mask,
			static_cast<std::int8_t>((bit_mask_ & 0x0000000004000000) >> 26) * element_mask,
			static_cast<std::int8_t>((bit_mask_ & 0x0000000008000000) >> 27) * element_mask,
			static_cast<std::int8_t>((bit_mask_ & 0x0000000010000000) >> 28) * element_mask,
			static_cast<std::int8_t>((bit_mask_ & 0x0000000020000000) >> 29) * element_mask,
			static_cast<std::int8_t>((bit_mask_ & 0x0000000040000000) >> 30) * element_mask,
			static_cast<std::int8_t>((bit_mask_ & 0x0000000080000000) >> 31) * element_mask,
			static_cast<std::int8_t>((bit_mask_ & 0x0000000100000000) >> 32) * element_mask,
			static_cast<std::int8_t>((bit_mask_ & 0x0000000200000000) >> 33) * element_mask,
			static_cast<std::int8_t>((bit_mask_ & 0x0000000400000000) >> 34) * element_mask,
			static_cast<std::int8_t>((bit_mask_ & 0x0000000800000000) >> 35) * element_mask,
			static_cast<std::int8_t>((bit_mask_ & 0x0000001000000000) >> 36) * element_mask,
			static_cast<std::int8_t>((bit_mask_ & 0x0000002000000000) >> 37) * element_mask,
			static_cast<std::int8_t>((bit_mask_ & 0x0000004000000000) >> 38) * element_mask,
			static_cast<std::int8_t>((bit_mask_ & 0x0000008000000000) >> 39) * element_mask,
			static_cast<std::int8_t>((bit_mask_ & 0x0000010000000000) >> 40) * element_mask,
			static_cast<std::int8_t>((bit_mask_ & 0x0000020000000000) >> 41) * element_mask,
			static_cast<std::int8_t>((bit_mask_ & 0x0000040000000000) >> 42) * element_mask,
			static_cast<std::int8_t>((bit_mask_ & 0x0000080000000000) >> 43) * element_mask,
			static_cast<std::int8_t>((bit_mask_ & 0x0000100000000000) >> 44) * element_mask,
			static_cast<std::int8_t>((bit_mask_ & 0x0000200000000000) >> 45) * element_mask,
			static_cast<std::int8_t>((bit_mask_ & 0x0000400000000000) >> 46) * element_mask,
			static_cast<std::int8_t>((bit_mask_ & 0x0000800000000000) >> 47) * element_mask,
			static_cast<std::int8_t>((bit_mask_ & 0x0001000000000000) >> 48) * element_mask,
			static_cast<std::int8_t>((bit_mask_ & 0x0002000000000000) >> 49) * element_mask,
			static_cast<std::int8_t>((bit_mask_ & 0x0004000000000000) >> 50) * element_mask,
			static_cast<std::int8_t>((bit_mask_ & 0x0008000000000000) >> 51) * element_mask,
			static_cast<std::int8_t>((bit_mask_ & 0x0010000000000000) >> 52) * element_mask,
			static_cast<std::int8_t>((bit_mask_ & 0x0020000000000000) >> 53) * element_mask,
			static_cast<std::int8_t>((bit_mask_ & 0x0040000000000000) >> 54) * element_mask,
			static_cast<std::int8_t>((bit_mask_ & 0x0080000000000000) >> 55) * element_mask,
			static_cast<std::int8_t>((bit_mask_ & 0x0100000000000000) >> 56) * element_mask,
			static_cast<std::int8_t>((bit_mask_ & 0x0200000000000000) >> 57) * element_mask,
			static_cast<std::int8_t>((bit_mask_ & 0x0400000000000000) >> 58) * element_mask,
			static_cast<std::int8_t>((bit_mask_ & 0x0800000000000000) >> 59) * element_mask,
			static_cast<std::int8_t>((bit_mask_ & 0x1000000000000000) >> 60) * element_mask,
			static_cast<std::int8_t>((bit_mask_ & 0x2000000000000000) >> 61) * element_mask,
			static_cast<std::int8_t>((bit_mask_ & 0x4000000000000000) >> 62) * element_mask,
			static_cast<std::int8_t>((bit_mask_ & 0x8000000000000000) >> 63)* element_mask
		);
	}
#pragma endregion

#pragma region STORES
	EMU_SIMD_COMMON_FUNC_SPEC void store_u8x64(std::uint8_t* p_out_, u8x64_arg a_)
	{
		_mm512_store_si512(reinterpret_cast<__m256i*>(p_out_), a_);
	}
#pragma endregion

#pragma region CASTS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cast_f32x4_u8x64(f32x4_arg a_)
	{
		return _mm512_castsi128_si512(_mm_castps_si128(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cast_f32x8_u8x64(f32x8_arg a_)
	{
		return _mm512_castsi256_si512(_mm256_castps_si256(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cast_f32x16_u8x64(f32x16_arg a_)
	{
		return _mm512_castps_si512(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cast_f64x2_u8x64(f64x2_arg a_)
	{
		return _mm512_castsi128_si512(_mm_castpd_si128(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cast_f64x4_u8x64(f64x4_arg a_)
	{
		return _mm512_castsi256_si512(_mm256_castpd_si256(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cast_f64x8_u8x64(f64x8_arg a_)
	{
		return _mm512_castpd_si512(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cast_i8x16_u8x64(i8x16_arg a_)
	{
		return _mm512_castsi128_si512(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cast_i16x8_u8x64(i16x8_arg a_)
	{
		return _mm512_castsi128_si512(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cast_i32x4_u8x64(i32x4_arg a_)
	{
		return _mm512_castsi128_si512(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cast_i64x2_u8x64(i64x2_arg a_)
	{
		return _mm512_castsi128_si512(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cast_i8x32_u8x64(i8x32_arg a_)
	{
		return _mm512_castsi256_si512(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cast_i16x16_u8x64(i16x16_arg a_)
	{
		return _mm512_castsi256_si512(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cast_i32x8_u8x64(i32x8_arg a_)
	{
		return _mm512_castsi256_si512(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cast_i64x4_u8x64(i64x4_arg a_)
	{
		return _mm512_castsi256_si512(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cast_i8x64_u8x64(i8x64_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cast_i16x32_u8x64(i16x32_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cast_i32x16_u8x64(i32x16_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cast_i64x8_u8x64(i64x8_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cast_u8x16_u8x64(u8x16_arg a_)
	{
		return _mm512_castsi128_si512(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cast_u16x8_u8x64(u16x8_arg a_)
	{
		return _mm512_castsi128_si512(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cast_u32x4_u8x64(u32x4_arg a_)
	{
		return _mm512_castsi128_si512(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cast_u64x2_u8x64(u64x2_arg a_)
	{
		return _mm512_castsi128_si512(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cast_u8x32_u8x64(u8x32_arg a_)
	{
		return _mm512_castsi256_si512(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cast_u16x16_u8x64(u16x16_arg a_)
	{
		return _mm512_castsi256_si512(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cast_u32x8_u8x64(u32x8_arg a_)
	{
		return _mm512_castsi256_si512(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cast_u64x4_u8x64(u64x4_arg a_)
	{
		return _mm512_castsi256_si512(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cast_u8x64_u8x64(u8x64_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cast_u16x32_u8x64(u16x32_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cast_u32x16_u8x64(u32x16_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cast_u64x8_u8x64(u64x8_arg a_)
	{
		return a_;
	}
#pragma endregion

#pragma region CONVERSIONS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cvt_f32x4_u8x64(f32x4_arg a_)
	{
		return _mm512_castsi128_si512(_mm_cvtepi32_epi8(_mm_cvtps_epi32(a_)));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cvt_f32x8_u8x64(f32x8_arg a_)
	{
		return _mm512_castsi128_si512(_mm256_cvtepi32_epi8(_mm256_cvtps_epi32(a_)));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cvt_f32x16_u8x64(f32x16_arg a_)
	{
		return _mm512_castsi128_si512(_mm512_cvtepi32_epi8(_mm512_cvtps_epi32(a_)));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cvt_f64x2_u8x64(f64x2_arg a_)
	{
		return _mm512_castsi128_si512(_mm_cvtepi64_epi8(_mm_cvtpd_epi64(a_)));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cvt_f64x4_u8x64(f64x4_arg a_)
	{
		return _mm512_castsi128_si512(_mm256_cvtepi64_epi8(_mm256_cvtpd_epi64(a_)));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cvt_f64x8_u8x64(f64x8_arg a_)
	{
		return _mm512_castsi128_si512(_mm512_cvtepi64_epi8(_mm512_cvtpd_epi64(a_)));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cvt_i8x16_u8x64(i8x16_arg a_)
	{
		return _mm512_castsi128_si512(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cvt_i16x8_u8x64(i16x8_arg a_)
	{
		return _mm512_castsi128_si512(_mm_cvtepi16_epi8(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cvt_i32x4_u8x64(i32x4_arg a_)
	{
		return _mm512_castsi128_si512(_mm_cvtepi32_epi8(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cvt_i64x2_u8x64(i64x2_arg a_)
	{
		return _mm512_castsi128_si512(_mm_cvtepi64_epi8(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cvt_i8x32_u8x64(i8x32_arg a_)
	{
		return _mm512_castsi256_si512(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cvt_i16x16_u8x64(i16x16_arg a_)
	{
		return _mm512_castsi128_si512(_mm256_cvtepi16_epi8(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cvt_i32x8_u8x64(i32x8_arg a_)
	{
		return _mm512_castsi128_si512(_mm256_cvtepi32_epi8(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cvt_i64x4_u8x64(i64x4_arg a_)
	{
		return _mm512_castsi128_si512(_mm256_cvtepi64_epi8(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cvt_i8x64_u8x64(i8x64_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cvt_i16x32_u8x64(i16x32_arg a_)
	{
		return _mm512_castsi256_si512(_mm512_cvtepi16_epi8(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cvt_i32x16_u8x64(i32x16_arg a_)
	{
		return _mm512_castsi128_si512(_mm512_cvtepi32_epi8(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cvt_i64x8_u8x64(i64x8_arg a_)
	{
		return _mm512_castsi128_si512(_mm512_cvtepi64_epi8(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cvt_u8x16_u8x64(u8x16_arg a_)
	{
		return _mm512_castsi128_si512(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cvt_u16x8_u8x64(u16x8_arg a_)
	{
		return _mm512_castsi128_si512(_mm_cvtepi16_epi8(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cvt_u32x4_u8x64(u32x4_arg a_)
	{
		return _mm512_castsi128_si512(_mm_cvtepi32_epi8(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cvt_u64x2_u8x64(u64x2_arg a_)
	{
		return _mm512_castsi128_si512(_mm_cvtepi64_epi8(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cvt_u8x32_u8x64(u8x32_arg a_)
	{
		return _mm512_castsi256_si512(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cvt_u16x16_u8x64(u16x16_arg a_)
	{
		return _mm512_castsi128_si512(_mm256_cvtepi16_epi8(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cvt_u32x8_u8x64(u32x8_arg a_)
	{
		return _mm512_castsi128_si512(_mm256_cvtepi32_epi8(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cvt_u64x4_u8x64(u64x4_arg a_)
	{
		return _mm512_castsi128_si512(_mm256_cvtepi64_epi8(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cvt_u8x64_u8x64(u8x64_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cvt_u16x32_u8x64(u16x32_arg a_)
	{
		return _mm512_castsi256_si512(_mm512_cvtepi16_epi8(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cvt_u32x16_u8x64(u32x16_arg a_)
	{
		return _mm512_castsi128_si512(_mm512_cvtepi32_epi8(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cvt_u64x8_u8x64(u64x8_arg a_)
	{
		return _mm512_castsi128_si512(_mm512_cvtepi64_epi8(a_));
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
	EMU_SIMD_COMMON_FUNC_SPEC auto emulate_fp_u8x64(Func_ func_, EmuSIMD::u8x64_arg in_)
		-> std::enable_if_t<std::is_invocable_r_v<EmuSIMD::f32x16, decltype(func_), EmuSIMD::f32x16>, EmuSIMD::u8x64>
	{
		constexpr std::size_t num_elements = 64;
		constexpr std::size_t elements_per_register = 16;
		std::uint8_t data[num_elements];
		float results[num_elements];

		store_u8x64(data, in_);
		for (std::size_t i = 0; i < num_elements; i += elements_per_register)
		{
			store_f32x16
			(
				results + i,
				func_
				(
					set_f32x16
					(
						static_cast<float>(data[i + 15]), static_cast<float>(data[i + 14]), static_cast<float>(data[i + 13]), static_cast<float>(data[i + 12]),
						static_cast<float>(data[i + 11]), static_cast<float>(data[i + 10]), static_cast<float>(data[i + 9]), static_cast<float>(data[i + 8]),
						static_cast<float>(data[i + 7]), static_cast<float>(data[i + 6]), static_cast<float>(data[i + 5]), static_cast<float>(data[i + 4]),
						static_cast<float>(data[i + 3]), static_cast<float>(data[i + 2]), static_cast<float>(data[i + 1]), static_cast<float>(data[i])
					)
				)
			);
		}

		return set_u8x64
		(
			static_cast<std::uint8_t>(results[63]),
			static_cast<std::uint8_t>(results[62]),
			static_cast<std::uint8_t>(results[61]),
			static_cast<std::uint8_t>(results[60]),
			static_cast<std::uint8_t>(results[59]),
			static_cast<std::uint8_t>(results[58]),
			static_cast<std::uint8_t>(results[57]),
			static_cast<std::uint8_t>(results[56]),
			static_cast<std::uint8_t>(results[55]),
			static_cast<std::uint8_t>(results[54]),
			static_cast<std::uint8_t>(results[53]),
			static_cast<std::uint8_t>(results[52]),
			static_cast<std::uint8_t>(results[51]),
			static_cast<std::uint8_t>(results[50]),
			static_cast<std::uint8_t>(results[49]),
			static_cast<std::uint8_t>(results[48]),
			static_cast<std::uint8_t>(results[47]),
			static_cast<std::uint8_t>(results[46]),
			static_cast<std::uint8_t>(results[45]),
			static_cast<std::uint8_t>(results[44]),
			static_cast<std::uint8_t>(results[43]),
			static_cast<std::uint8_t>(results[42]),
			static_cast<std::uint8_t>(results[41]),
			static_cast<std::uint8_t>(results[40]),
			static_cast<std::uint8_t>(results[39]),
			static_cast<std::uint8_t>(results[38]),
			static_cast<std::uint8_t>(results[37]),
			static_cast<std::uint8_t>(results[36]),
			static_cast<std::uint8_t>(results[35]),
			static_cast<std::uint8_t>(results[34]),
			static_cast<std::uint8_t>(results[33]),
			static_cast<std::uint8_t>(results[32]),
			static_cast<std::uint8_t>(results[31]),
			static_cast<std::uint8_t>(results[30]),
			static_cast<std::uint8_t>(results[29]),
			static_cast<std::uint8_t>(results[28]),
			static_cast<std::uint8_t>(results[27]),
			static_cast<std::uint8_t>(results[26]),
			static_cast<std::uint8_t>(results[25]),
			static_cast<std::uint8_t>(results[24]),
			static_cast<std::uint8_t>(results[23]),
			static_cast<std::uint8_t>(results[22]),
			static_cast<std::uint8_t>(results[21]),
			static_cast<std::uint8_t>(results[20]),
			static_cast<std::uint8_t>(results[19]),
			static_cast<std::uint8_t>(results[18]),
			static_cast<std::uint8_t>(results[17]),
			static_cast<std::uint8_t>(results[16]),
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
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cmpeq_u8x64(EmuSIMD::u8x64_arg lhs_, EmuSIMD::u8x64_arg rhs_)
	{
		return setmasked_i8x64(_mm512_cmpeq_epu8_mask(lhs_, rhs_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cmpneq_u8x64(EmuSIMD::u8x64_arg lhs_, EmuSIMD::u8x64_arg rhs_)
	{
		return setmasked_i8x64(_mm512_cmpneq_epu8_mask(lhs_, rhs_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cmpgt_u8x64(EmuSIMD::u8x64_arg lhs_, EmuSIMD::u8x64_arg rhs_)
	{
		return setmasked_i8x64(_mm512_cmplt_epu8_mask(rhs_, lhs_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cmplt_u8x64(EmuSIMD::u8x64_arg lhs_, EmuSIMD::u8x64_arg rhs_)
	{
		return setmasked_i8x64(_mm512_cmplt_epu8_mask(lhs_, rhs_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cmpge_u8x64(EmuSIMD::u8x64_arg lhs_, EmuSIMD::u8x64_arg rhs_)
	{
		return setmasked_i8x64(_mm512_cmple_epu8_mask(rhs_, lhs_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cmple_u8x64(EmuSIMD::u8x64_arg lhs_, EmuSIMD::u8x64_arg rhs_)
	{
		return setmasked_i8x64(_mm512_cmple_epu8_mask(lhs_, rhs_));
	}
#pragma endregion

#pragma region MOVES
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 movehl_u8x64(EmuSIMD::u8x64_arg lhs_, EmuSIMD::u8x64_arg rhs_)
	{
		return cast_f32x16_u8x64(movehl_f32x16(cast_u8x64_f32x16(lhs_), cast_u8x64_f32x16(rhs_)));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 movelh_u8x64(EmuSIMD::u8x64_arg lhs_, EmuSIMD::u8x64_arg rhs_)
	{
		return cast_f32x16_u8x64(movelh_f32x16(cast_u8x64_f32x16(lhs_), cast_u8x64_f32x16(rhs_)));
	}
#pragma endregion

#pragma region BASIC_ARITHMETIC
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 mul_all_u8x64(EmuSIMD::u8x64_arg lhs_, EmuSIMD::u8x64_arg rhs_)
	{
		EmuSIMD::u8x64 even_bytes = _mm512_mullo_epi16(lhs_, rhs_);
		EmuSIMD::u8x64 odd_bytes = _mm512_mullo_epi16(_mm512_srli_epi16(lhs_, 8), _mm512_srli_epi16(rhs_, 8));
		return _mm512_or_si512(_mm512_slli_epi16(odd_bytes, 8), _mm512_srli_epi16(_mm512_slli_epi16(even_bytes, 8), 8));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 negate_u8x64(EmuSIMD::u8x64_arg to_negate_)
	{
		return _mm512_sub_epi8(_mm512_setzero_si512(), to_negate_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 add_u8x64(EmuSIMD::u8x64_arg lhs_, EmuSIMD::u8x64_arg rhs_)
	{
		return _mm512_add_epi8(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 sub_u8x64(EmuSIMD::u8x64_arg lhs_, EmuSIMD::u8x64_arg rhs_)
	{
		return _mm512_sub_epi8(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 mul_u8x64(EmuSIMD::u8x64_arg lhs_, EmuSIMD::u8x64_arg rhs_)
	{
		return _mm512_mul_epu32(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 div_u8x64(EmuSIMD::u8x64_arg lhs_, EmuSIMD::u8x64_arg rhs_)
	{
#if EMU_CORE_X86_X64_SVML
		return _mm512_div_epu8(lhs_, rhs_);
#else
		// lo
		EmuSIMD::i16x32 lane64_a = cvt_i8x64_i16x32(lhs_);
		EmuSIMD::i16x32 lane64_b = cvt_i8x64_i16x32(rhs_);
		EmuSIMD::i8x64 lo = cvt_i16x32_i8x64(div_i16x32(lane64_a, lane64_b));

		// hi - move hi bits to lo
		EmuSIMD::i8x64 tmp_lane = movehl_i8x64(lhs_, lhs_);
		lane64_a = cvt_i8x64_i16x32(tmp_lane);

		tmp_lane = movehl_i8x64(rhs_, rhs_);
		lane64_b = cvt_i8x64_i16x32(tmp_lane);

		// Move hi and lo into the same register, in their respective 64-bit lanes
		EmuSIMD::i8x64 hi = cvt_i16x32_i8x64(div_i16x32(lane64_a, lane64_b));
		return movelh_i8x64(lo, hi);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 addsub_u8x64(EmuSIMD::u8x64_arg lhs_, EmuSIMD::u8x64_arg rhs_)
	{
		constexpr std::uint8_t byte_mask = static_cast<std::uint8_t>(0xFF);
		const EmuSIMD::u8x64 mask = _mm512_set_epi8
		(
			byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0,
			byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0,
			byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0,
			byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0
		);
		EmuSIMD::u8x64 out = _mm512_add_epi8(lhs_, _mm512_and_si512(mask, rhs_));
		return _mm512_sub_epi8(lhs_, _mm512_andnot_si512(mask, rhs_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 subadd_u8x64(EmuSIMD::u8x64_arg lhs_, EmuSIMD::u8x64_arg rhs_)
	{
		constexpr std::uint8_t byte_mask = static_cast<std::uint8_t>(0xFF);
		const EmuSIMD::u8x64 mask = _mm512_set_epi8
		(
			byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0,
			byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0,
			byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0,
			byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0
		);
		EmuSIMD::u8x64 out = _mm512_sub_epi8(lhs_, _mm512_and_si512(mask, rhs_));
		return _mm512_add_epi8(lhs_, _mm512_andnot_si512(mask, rhs_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 fmadd_u8x64(EmuSIMD::u8x64_arg a_, EmuSIMD::u8x64_arg b_, EmuSIMD::u8x64_arg c_)
	{
		return _mm512_add_epi8(mul_all_u8x64(a_, b_), c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 fmsub_u8x64(EmuSIMD::u8x64_arg a_, EmuSIMD::u8x64_arg b_, EmuSIMD::u8x64_arg c_)
	{
		return _mm512_sub_epi8(mul_all_u8x64(a_, b_), c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 fnmadd_u8x64(EmuSIMD::u8x64_arg a_, EmuSIMD::u8x64_arg b_, EmuSIMD::u8x64_arg c_)
	{
		return _mm512_add_epi8(mul_all_u8x64(negate_u8x64(a_), b_), c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 fnmsub_u8x64(EmuSIMD::u8x64_arg a_, EmuSIMD::u8x64_arg b_, EmuSIMD::u8x64_arg c_)
	{
		return _mm512_sub_epi8(mul_all_u8x64(negate_u8x64(a_), b_), c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 fmaddsub_u8x64(EmuSIMD::u8x64_arg a_, EmuSIMD::u8x64_arg b_, EmuSIMD::u8x64_arg c_)
	{
		return addsub_u8x64(mul_all_u8x64(negate_u8x64(a_), b_), c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 fmsubadd_u8x64(EmuSIMD::u8x64_arg a_, EmuSIMD::u8x64_arg b_, EmuSIMD::u8x64_arg c_)
	{
		return subadd_u8x64(mul_all_u8x64(negate_u8x64(a_), b_), c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 floor_u8x64(EmuSIMD::u8x64_arg to_floor_)
	{
		return to_floor_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 ceil_u8x64(EmuSIMD::u8x64_arg to_ceil_)
	{
		return to_ceil_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 trunc_u8x64(EmuSIMD::u8x64_arg to_trunc_)
	{
		return to_trunc_;
	}

	template<int RoundingFlag_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 round_u8x64(EmuSIMD::u8x64_arg to_round_)
	{
		return to_round_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 mod_u8x64(EmuSIMD::u8x64_arg lhs_, EmuSIMD::u8x64_arg rhs_)
	{
#if EMU_CORE_X86_X64_SVML
		return _mm512_rem_epu8(lhs_, rhs_);
#else
		EmuSIMD::u8x64 to_subtract = div_u8x64(lhs_, rhs_);
		to_subtract = mul_all_u8x64(to_subtract, rhs_);
		return sub_u8x64(lhs_, to_subtract);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 abs_u8x64(EmuSIMD::u8x64_arg in_)
	{
		return in_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 sqrt_u8x64(EmuSIMD::u8x64_arg in_)
	{
		return emulate_fp_u8x64([](EmuSIMD::f32x16_arg in_fp_) { return sqrt_f32x16(in_fp_); }, in_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 rsqrt_u8x64(EmuSIMD::u8x64_arg in_)
	{
		return emulate_fp_u8x64([](EmuSIMD::f32x16_arg in_fp_) { return rsqrt_f32x16(in_fp_); }, in_);
	}
#pragma endregion

#pragma region NEAR_COMPARISONS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cmpnear_u8x64(EmuSIMD::u8x64_arg lhs_, EmuSIMD::u8x64_arg rhs_)
	{
		return cmpeq_u8x64(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cmpnear_u8x64(EmuSIMD::u8x64_arg lhs_, EmuSIMD::u8x64_arg rhs_, EmuSIMD::u8x64_arg epsilon)
	{
		return cmple_u8x64(sub_u8x64(lhs_, rhs_), epsilon);
	}
#pragma endregion

#pragma region TRIG
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cos_u8x64(EmuSIMD::u8x64_arg in_)
	{
		return emulate_fp_u8x64([](EmuSIMD::f32x16_arg in_fp_) { return cos_f32x16(in_fp_); }, in_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 sin_u8x64(EmuSIMD::u8x64_arg in_)
	{
		return emulate_fp_u8x64([](EmuSIMD::f32x16_arg in_fp_) { return sin_f32x16(in_fp_); }, in_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 tan_u8x64(EmuSIMD::u8x64_arg in_)
	{
		return emulate_fp_u8x64([](EmuSIMD::f32x16_arg in_fp_) { return tan_f32x16(in_fp_); }, in_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 acos_u8x64(EmuSIMD::u8x64_arg in_)
	{
		return emulate_fp_u8x64([](EmuSIMD::f32x16_arg in_fp_) { return acos_f32x16(in_fp_); }, in_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 asin_u8x64(EmuSIMD::u8x64_arg in_)
	{
		return emulate_fp_u8x64([](EmuSIMD::f32x16_arg in_fp_) { return asin_f32x16(in_fp_); }, in_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 atan_u8x64(EmuSIMD::u8x64_arg in_)
	{
		return emulate_fp_u8x64([](EmuSIMD::f32x16_arg in_fp_) { return atan_f32x16(in_fp_); }, in_);
	}
#pragma endregion
}

#endif
