#ifndef EMU_SIMD_GENERIC_FUNCS_I8X16_H_INC_
#define EMU_SIMD_GENERIC_FUNCS_I8X16_H_INC_ 1

#include "_common_generic_func_helpers.h"
#include "_f32x4.h"
#include "_i16x8.h"
#include "_i16x16.h"
#include "_i32x4.h"
#include "_i32x8.h"
#include "_i64x2.h"
#include "_i64x4.h"
#include "_u16x8.h"
#include "_u16x16.h"
#include "_u32x4.h"
#include "_u32x8.h"
#include "_u64x2.h"
#include "_u64x4.h"

namespace EmuSIMD::Funcs
{
#pragma region SETTERS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x16 set_i8x16
	(
		std::int8_t e0, std::int8_t e1, std::int8_t e2, std::int8_t e3, std::int8_t e4, std::int8_t e5, std::int8_t e6, std::int8_t e7,
		std::int8_t e8, std::int8_t e9, std::int8_t e10, std::int8_t e11, std::int8_t e12, std::int8_t e13, std::int8_t e14, std::int8_t e15
	)
	{
		return _mm_set_epi8(e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x16 setr_i8x16
	(
		std::int8_t e0, std::int8_t e1, std::int8_t e2, std::int8_t e3, std::int8_t e4, std::int8_t e5, std::int8_t e6, std::int8_t e7,
		std::int8_t e8, std::int8_t e9, std::int8_t e10, std::int8_t e11, std::int8_t e12, std::int8_t e13, std::int8_t e14, std::int8_t e15
	)
	{
		//return _mm_setr_epi8(e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15);
		return _mm_set_epi8(e15, e14, e13, e12, e11, e10, e9, e8, e7, e6, e5, e4, e3, e2, e1, e0);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x16 set1_i8x16(std::int8_t all_)
	{
		return _mm_set1_epi8(all_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x16 load_i8x16(const std::int8_t* p_to_load_)
	{
		return _mm_load_si128(reinterpret_cast<const __m128i*>(p_to_load_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x16 setzero_i8x16()
	{
		return _mm_setzero_si128();
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x16 setmasked_i8x16(std::uint16_t bit_mask_)
	{
		constexpr std::int8_t element_mask = static_cast<std::int8_t>(0xFF);
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
	EMU_SIMD_COMMON_FUNC_SPEC void store_i8x16(std::int8_t* p_out_, i8x16_arg a_)
	{
		_mm_store_si128(reinterpret_cast<__m128i*>(p_out_), a_);
	}
#pragma endregion

#pragma region CASTS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x16 cast_f32x4_i8x16(f32x4_arg a_)
	{
		return _mm_castps_si128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x16 cast_f32x8_i8x16(f32x8_arg a_)
	{
		return _mm256_castsi256_si128(_mm256_castps_si256(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x16 cast_f32x16_i8x16(f32x16_arg a_)
	{
		return _mm512_castsi512_si128(_mm512_castps_si512(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x16 cast_f64x2_i8x16(f64x2_arg a_)
	{
		return _mm_castpd_si128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x16 cast_f64x4_i8x16(f64x4_arg a_)
	{
		return _mm256_castsi256_si128(_mm256_castpd_si256(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x16 cast_f64x8_i8x16(f64x8_arg a_)
	{
		return _mm512_castsi512_si128(_mm512_castpd_si512(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x16 cast_i8x16_i8x16(i8x16_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x16 cast_i16x8_i8x16(i16x8_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x16 cast_i32x4_i8x16(i32x4_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x16 cast_i64x2_i8x16(i64x2_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x16 cast_i8x32_i8x16(i8x32_arg a_)
	{
		return _mm256_castsi256_si128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x16 cast_i16x16_i8x16(i16x16_arg a_)
	{
		return _mm256_castsi256_si128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x16 cast_i32x8_i8x16(i32x8_arg a_)
	{
		return _mm256_castsi256_si128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x16 cast_i64x4_i8x16(i64x4_arg a_)
	{
		return _mm256_castsi256_si128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x16 cast_i8x64_i8x16(i8x64_arg a_)
	{
		return _mm512_castsi512_si128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x16 cast_i16x32_i8x16(i16x32_arg a_)
	{
		return _mm512_castsi512_si128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x16 cast_i32x16_i8x16(i32x16_arg a_)
	{
		return _mm512_castsi512_si128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x16 cast_i64x8_i8x16(i64x8_arg a_)
	{
		return _mm512_castsi512_si128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x16 cast_u8x16_i8x16(u8x16_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x16 cast_u16x8_i8x16(u16x8_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x16 cast_u32x4_i8x16(u32x4_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x16 cast_u64x2_i8x16(u64x2_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x16 cast_u8x32_i8x16(u8x32_arg a_)
	{
		return _mm256_castsi256_si128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x16 cast_u16x16_i8x16(u16x16_arg a_)
	{
		return _mm256_castsi256_si128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x16 cast_u32x8_i8x16(u32x8_arg a_)
	{
		return _mm256_castsi256_si128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x16 cast_u64x4_i8x16(u64x4_arg a_)
	{
		return _mm256_castsi256_si128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x16 cast_u8x64_i8x16(u8x64_arg a_)
	{
		return _mm512_castsi512_si128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x16 cast_u16x32_i8x16(u16x32_arg a_)
	{
		return _mm512_castsi512_si128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x16 cast_u32x16_i8x16(u32x16_arg a_)
	{
		return _mm512_castsi512_si128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x16 cast_u64x8_i8x16(u64x8_arg a_)
	{
		return _mm512_castsi512_si128(a_);
	}
#pragma endregion

#pragma region EXTRACTION_TEMPLATES
	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x16 extract_f32x4_lane_i8x16(f32x4_arg a_)
	{
		static_assert(Index_ == 0, "Invalid SIMD lane extraction index: Extracting i8x16 lane from a f32x4 instance; the maximum index is 0 but this index has been exceeded");
		return cast_f32x4_i8x16(a_);
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x16 extract_f32x8_lane_i8x16(f32x8_arg a_)
	{
		static_assert(Index_ <= 1, "Invalid SIMD lane extraction index: Extracting i8x16 lane from a f32x8 instance; the maximum index is 1 but this index has been exceeded.");
		if constexpr (Index_ == 0)
		{
			return cast_f32x8_i8x16(a_);
		}
		else
		{
			return cast_f32x4_i8x16(_mm256_extractf128_ps(a_, Index_));
		}
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x16 extract_f32x16_lane_i8x16(f32x16_arg a_)
	{
		static_assert(Index_ <= 3, "Invalid SIMD lane extraction index: Extracting i8x16 lane from a f32x16 instance; the maximum index is 3 but this index has been exceeded.");
		if constexpr (Index_ == 0)
		{
			return cast_f32x16_i8x16(a_);
		}
		else
		{
			return cast_f32x4_i8x16(_mm512_extractf32x4_ps(a_, Index_));
		}
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x16 extract_f64x2_lane_i8x16(f64x2_arg a_)
	{
		static_assert(Index_ == 0, "Invalid SIMD lane extraction index: Extracting i8x16 lane from a f64x2 instance; the maximum index is 0 but this index has been exceeded.");
		return cast_f64x2_i8x16(a_);
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x16 extract_f64x4_lane_i8x16(f64x4_arg a_)
	{
		static_assert(Index_ <= 1, "Invalid SIMD lane extraction index: Extracting i8x16 lane from a f64x4 instance; the maximum index is 1 but this index has been exceeded.");
		if constexpr (Index_ == 0)
		{
			return cast_f64x4_i8x16(a_);
		}
		else
		{
			return cast_f64x2_i8x16(_mm256_extractf128_pd(a_, Index_));
		}
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x16 extract_f64x8_lane_i8x16(f64x8_arg a_)
	{
		static_assert(Index_ <= 3, "Invalid SIMD lane extraction index: Extracting i8x16 lane from a f64x8 instance; the maximum index is 3 but this index has been exceeded.");
		if constexpr (Index_ == 0)
		{
			return cast_f64x8_i8x16(a_);
		}
		else
		{
			return cast_f64x2_i8x16(_mm512_extractf64x2_pd(a_, Index_));
		}
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x16 extract_i8x16_lane_i8x16(i8x16_arg a_)
	{
		static_assert(Index_ == 0, "Invalid SIMD lane extraction index: Extracting i8x16 lane from a i8x16 instance; the maximum index is 0 but this index has been exceeded.");
		return a_;
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x16 extract_i8x32_lane_i8x16(i8x32_arg a_)
	{
		static_assert(Index_ <= 1, "Invalid SIMD lane extraction index: Extracting i8x16 lane from a i8x32 instance; the maximum index is 1 but this index has been exceeded.");
		if constexpr (Index_ == 0)
		{
			return cast_i8x32_i8x16(a_);
		}
		else
		{
			return _mm256_extracti128_si256(a_, Index_);
		}
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x16 extract_i8x64_lane_i8x16(i8x64_arg a_)
	{
		static_assert(Index_ <= 3, "Invalid SIMD lane extraction index: Extracting i8x16 lane from a i8x64 instance; the maximum index is 3 but this index has been exceeded.");
		if constexpr (Index_ == 0)
		{
			return cast_i8x64_i8x16(a_);
		}
		else
		{
			return _mm512_extracti32x4_epi32(a_, Index_);
		}
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x16 extract_i16x8_lane_i8x16(i16x8_arg a_)
	{
		static_assert(Index_ == 0, "Invalid SIMD lane extraction index: Extracting i8x16 lane from a i16x8 instance; the maximum index is 0 but this index has been exceeded.");
		return cast_i16x8_i8x16(a_);
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x16 extract_i16x16_lane_i8x16(i16x16_arg a_)
	{
		static_assert(Index_ <= 1, "Invalid SIMD lane extraction index: Extracting i8x16 lane from a i16x16 instance; the maximum index is 1 but this index has been exceeded.");
		if constexpr (Index_ == 0)
		{
			return cast_i16x16_i8x16(a_);
		}
		else
		{
			return _mm256_extracti128_si256(a_, Index_);
		}
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x16 extract_i16x32_lane_i8x16(i16x32_arg a_)
	{
		static_assert(Index_ <= 3, "Invalid SIMD lane extraction index: Extracting i8x16 lane from a i16x32 instance; the maximum index is 3 but this index has been exceeded.");
		if constexpr (Index_ == 0)
		{
			return cast_i16x32_i8x16(a_);
		}
		else
		{
			return _mm512_extracti32x4_epi32(a_, Index_);
		}
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x16 extract_i32x4_lane_i8x16(i32x4_arg a_)
	{
		static_assert(Index_ == 0, "Invalid SIMD lane extraction index: Extracting i8x16 lane from a i32x4 instance; the maximum index is 0 but this index has been exceeded.");
		return cast_i32x4_i8x16(a_);
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x16 extract_i32x8_lane_i8x16(i32x8_arg a_)
	{
		static_assert(Index_ <= 1, "Invalid SIMD lane extraction index: Extracting i8x16 lane from a i32x8 instance; the maximum index is 1 but this index has been exceeded.");
		if constexpr (Index_ == 0)
		{
			return cast_i32x8_i8x16(a_);
		}
		else
		{
			return _mm256_extracti128_si256(a_, Index_);
		}
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x16 extract_i32x16_lane_i8x16(i32x16_arg a_)
	{
		static_assert(Index_ <= 3, "Invalid SIMD lane extraction index: Extracting i8x16 lane from a i32x16 instance; the maximum index is 3 but this index has been exceeded.");
		if constexpr (Index_ == 0)
		{
			return cast_i32x16_i8x16(a_);
		}
		else
		{
			return _mm512_extracti32x4_epi32(a_, Index_);
		}
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x16 extract_i64x2_lane_i8x16(i64x2_arg a_)
	{
		static_assert(Index_ == 0, "Invalid SIMD lane extraction index: Extracting i8x16 lane from a i64x2 instance; the maximum index is 0 but this index has been exceeded.");
		return cast_i64x2_i8x16(a_);
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x16 extract_i64x4_lane_i8x16(i64x4_arg a_)
	{
		static_assert(Index_ <= 1, "Invalid SIMD lane extraction index: Extracting i8x16 lane from a i64x4 instance; the maximum index is 1 but this index has been exceeded.");
		if constexpr (Index_ == 0)
		{
			return cast_i64x4_i8x16(a_);
		}
		else
		{
			return _mm256_extracti128_si256(a_, Index_);
		}
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x16 extract_i64x8_lane_i8x16(i64x8_arg a_)
	{
		static_assert(Index_ <= 3, "Invalid SIMD lane extraction index: Extracting i8x16 lane from a i64x8 instance; the maximum index is 3 but this index has been exceeded.");
		if constexpr (Index_ == 0)
		{
			return cast_i64x8_i8x16(a_);
		}
		else
		{
			return _mm512_extracti32x4_epi32(a_, Index_);
		}
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x16 extract_u8x16_lane_i8x16(u8x16_arg a_)
	{
		static_assert(Index_ == 0, "Invalid SIMD lane extraction index: Extracting i8x16 lane from a u8x16 instance; the maximum index is 0 but this index has been exceeded.");
		return cast_u8x16_i8x16(a_);
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x16 extract_u8x32_lane_i8x16(u8x32_arg a_)
	{
		static_assert(Index_ <= 1, "Invalid SIMD lane extraction index: Extracting i8x16 lane from a u8x32 instance; the maximum index is 1 but this index has been exceeded.");
		if constexpr (Index_ == 0)
		{
			return cast_u8x32_i8x16(a_);
		}
		else
		{
			return _mm256_extracti128_si256(a_, Index_);
		}
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x16 extract_u8x64_lane_i8x16(u8x64_arg a_)
	{
		static_assert(Index_ <= 3, "Invalid SIMD lane extraction index: Extracting i8x16 lane from a u8x64 instance; the maximum index is 3 but this index has been exceeded.");
		if constexpr (Index_ == 0)
		{
			return cast_u8x64_i8x16(a_);
		}
		else
		{
			return _mm512_extracti32x4_epi32(a_, Index_);
		}
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x16 extract_u16x8_lane_i8x16(u16x8_arg a_)
	{
		static_assert(Index_ == 0, "Invalid SIMD lane extraction index: Extracting i8x16 lane from a u16x8 instance; the maximum index is 0 but this index has been exceeded.");
		return cast_u16x8_i8x16(a_);
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x16 extract_u16x16_lane_i8x16(u16x16_arg a_)
	{
		static_assert(Index_ <= 1, "Invalid SIMD lane extraction index: Extracting i8x16 lane from a u16x16 instance; the maximum index is 1 but this index has been exceeded.");
		if constexpr (Index_ == 0)
		{
			return cast_u16x16_i8x16(a_);
		}
		else
		{
			return _mm256_extracti128_si256(a_, Index_);
		}
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x16 extract_u16x32_lane_i8x16(u16x32_arg a_)
	{
		static_assert(Index_ <= 3, "Invalid SIMD lane extraction index: Extracting i8x16 lane from a u16x32 instance; the maximum index is 3 but this index has been exceeded.");
		if constexpr (Index_ == 0)
		{
			return cast_u16x32_i8x16(a_);
		}
		else
		{
			return _mm512_extracti32x4_epi32(a_, Index_);
		}
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x16 extract_u32x4_lane_i8x16(u32x4_arg a_)
	{
		static_assert(Index_ == 0, "Invalid SIMD lane extraction index: Extracting i8x16 lane from a u32x4 instance; the maximum index is 0 but this index has been exceeded.");
		return cast_u32x4_i8x16(a_);
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x16 extract_u32x8_lane_i8x16(u32x8_arg a_)
	{
		static_assert(Index_ <= 1, "Invalid SIMD lane extraction index: Extracting i8x16 lane from a u32x8 instance; the maximum index is 1 but this index has been exceeded.");
		if constexpr (Index_ == 0)
		{
			return cast_u32x8_i8x16(a_);
		}
		else
		{
			return _mm256_extracti128_si256(a_, Index_);
		}
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x16 extract_u32x16_lane_i8x16(u32x16_arg a_)
	{
		static_assert(Index_ <= 3, "Invalid SIMD lane extraction index: Extracting f32x4 lane from a ui8x16 instance; the maximum index is 3 but this index has been exceeded.");
		if constexpr (Index_ == 0)
		{
			return cast_u32x16_i8x16(a_);
		}
		else
		{
			return _mm512_extracti32x4_epi32(a_, Index_);
		}
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x16 extract_u64x2_lane_i8x16(u64x2_arg a_)
	{
		static_assert(Index_ == 0, "Invalid SIMD lane extraction index: Extracting i8x16 lane from a u64x2 instance; the maximum index is 0 but this index has been exceeded.");
		return cast_u64x2_i8x16(a_);
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x16 extract_u64x4_lane_i8x16(u64x4_arg a_)
	{
		static_assert(Index_ <= 1, "Invalid SIMD lane extraction index: Extracting i8x16 lane from a u64x4 instance; the maximum index is 1 but this index has been exceeded.");
		if constexpr (Index_ == 0)
		{
			return cast_u64x4_i8x16(a_);
		}
		else
		{
			return _mm256_extracti128_si256(a_, Index_);
		}
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x16 extract_u64x8_lane_i8x16(u64x8_arg a_)
	{
		static_assert(Index_ <= 3, "Invalid SIMD lane extraction index: Extracting i8x16 lane from a u64x8 instance; the maximum index is 3 but this index has been exceeded.");
		if constexpr (Index_ == 0)
		{
			return cast_u64x8_i8x16(a_);
		}
		else
		{
			return _mm512_extracti32x4_epi32(a_, Index_);
		}
	}
#pragma endregion

#pragma region CONVERSIONS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x16 cvt_f32x4_i8x16(f32x4_arg a_)
	{
		return _mm_cvtepi32_epi8(_mm_cvtps_epi32(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x16 cvt_f32x8_i8x16(f32x8_arg a_)
	{
		return _mm256_cvtepi32_epi8(_mm256_cvtps_epi32(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x16 cvt_f32x16_i8x16(f32x16_arg a_)
	{
		return _mm512_cvtepi32_epi8(_mm512_cvtps_epi32(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x16 cvt_f64x2_i8x16(f64x2_arg a_)
	{
		return _mm_cvtepi64_epi8(_mm_cvtpd_epi64(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x16 cvt_f64x4_i8x16(f64x4_arg a_)
	{
		return _mm256_cvtepi64_epi8(_mm256_cvtpd_epi64(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x16 cvt_f64x8_i8x16(f64x8_arg a_)
	{
		return _mm512_cvtepi64_epi8(_mm512_cvtpd_epi64(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x16 cvt_i8x16_i8x16(i8x16_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x16 cvt_i16x8_i8x16(i16x8_arg a_)
	{
#if 0 // Need a test for if this is legal
		return _mm_cvtepi16_epi8(a_);
#else
		std::int16_t dump[8];
		store_i16x8(dump, a_);
		return setr_i8x16
		(
			static_cast<std::int8_t>(dump[0]),
			static_cast<std::int8_t>(dump[1]),
			static_cast<std::int8_t>(dump[2]),
			static_cast<std::int8_t>(dump[3]),
			static_cast<std::int8_t>(dump[4]),
			static_cast<std::int8_t>(dump[5]),
			static_cast<std::int8_t>(dump[6]),
			static_cast<std::int8_t>(dump[7]),
			0,
			0,
			0,
			0,
			0,
			0,
			0,
			0
		);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x16 cvt_i32x4_i8x16(i32x4_arg a_)
	{
#if 0 // Need a test for if this is legal
		return _mm_cvtepi32_epi8(a_);
#else
		std::int32_t dump[4];
		store_i32x4(dump, a_);
		return setr_i8x16
		(
			static_cast<std::int8_t>(dump[0]),
			static_cast<std::int8_t>(dump[1]),
			static_cast<std::int8_t>(dump[2]),
			static_cast<std::int8_t>(dump[3]),
			0,
			0,
			0,
			0,
			0,
			0,
			0,
			0,
			0,
			0,
			0,
			0
		);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x16 cvt_i64x2_i8x16(i64x2_arg a_)
	{
#if 0 // Need a test for if this is legal
		return _mm_cvtepi64_epi8(a_);
#else
		std::int64_t dump[2];
		store_i64x2(dump, a_);
		return setr_i8x16
		(
			static_cast<std::int8_t>(dump[0]),
			static_cast<std::int8_t>(dump[1]),
			0,
			0,
			0,
			0,
			0,
			0,
			0,
			0,
			0,
			0,
			0,
			0,
			0,
			0
		);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x16 cvt_i8x32_i8x16(i8x32_arg a_)
	{
		return _mm256_castsi256_si128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x16 cvt_i16x16_i8x16(i16x16_arg a_)
	{
#if 0 // Need a test for if this is legal
		return _mm256_cvtepi16_epi8(a_);
#else
		std::int16_t dump[16];
		store_i16x16(dump, a_);
		return setr_i8x16
		(
			static_cast<std::int8_t>(dump[0]),
			static_cast<std::int8_t>(dump[1]),
			static_cast<std::int8_t>(dump[2]),
			static_cast<std::int8_t>(dump[3]),
			static_cast<std::int8_t>(dump[4]),
			static_cast<std::int8_t>(dump[5]),
			static_cast<std::int8_t>(dump[6]),
			static_cast<std::int8_t>(dump[7]),
			static_cast<std::int8_t>(dump[8]),
			static_cast<std::int8_t>(dump[9]),
			static_cast<std::int8_t>(dump[10]),
			static_cast<std::int8_t>(dump[11]),
			static_cast<std::int8_t>(dump[12]),
			static_cast<std::int8_t>(dump[13]),
			static_cast<std::int8_t>(dump[14]),
			static_cast<std::int8_t>(dump[15])
		);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x16 cvt_i32x8_i8x16(i32x8_arg a_)
	{
#if 0 // Need a test for if this is legal
		return _mm256_cvtepi32_epi8(a_);
#else
		std::int32_t dump[8];
		store_i32x8(dump, a_);
		return setr_i8x16
		(
			static_cast<std::int8_t>(dump[0]),
			static_cast<std::int8_t>(dump[1]),
			static_cast<std::int8_t>(dump[2]),
			static_cast<std::int8_t>(dump[3]),
			static_cast<std::int8_t>(dump[4]),
			static_cast<std::int8_t>(dump[5]),
			static_cast<std::int8_t>(dump[6]),
			static_cast<std::int8_t>(dump[7]),
			0,
			0,
			0,
			0,
			0,
			0,
			0,
			0
		);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x16 cvt_i64x4_i8x16(i64x4_arg a_)
	{
#if 0 // Need a test for if this is legal
		return _mm256_cvtepi64_epi8(a_);
#else
		std::int32_t dump[4];
		store_i32x8(dump, a_);
		return setr_i8x16
		(
			static_cast<std::int8_t>(dump[0]),
			static_cast<std::int8_t>(dump[1]),
			static_cast<std::int8_t>(dump[2]),
			static_cast<std::int8_t>(dump[3]),
			0,
			0,
			0,
			0,
			0,
			0,
			0,
			0,
			0,
			0,
			0,
			0
		);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x16 cvt_i8x64_i8x16(i8x64_arg a_)
	{
		return _mm512_castsi512_si128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x16 cvt_i16x32_i8x16(i16x32_arg a_)
	{
		return cvt_i16x16_i8x16(_mm512_castsi512_si256(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x16 cvt_i32x16_i8x16(i32x16_arg a_)
	{
		return _mm512_cvtepi32_epi8(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x16 cvt_i64x8_i8x16(i64x8_arg a_)
	{
		return _mm512_cvtepi64_epi8(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x16 cvt_u8x16_i8x16(u8x16_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x16 cvt_u16x8_i8x16(u16x8_arg a_)
	{
#if 0 // Need a test for if this is legal
		return _mm_cvtepi16_epi8(a_);
#else
		std::uint16_t dump[8];
		store_u16x8(dump, a_);
		return setr_i8x16
		(
			static_cast<std::int8_t>(dump[0]),
			static_cast<std::int8_t>(dump[1]),
			static_cast<std::int8_t>(dump[2]),
			static_cast<std::int8_t>(dump[3]),
			static_cast<std::int8_t>(dump[4]),
			static_cast<std::int8_t>(dump[5]),
			static_cast<std::int8_t>(dump[6]),
			static_cast<std::int8_t>(dump[7]),
			0,
			0,
			0,
			0,
			0,
			0,
			0,
			0
		);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x16 cvt_u32x4_i8x16(u32x4_arg a_)
	{
#if 0 // Need a test for if this is legal
		return _mm_cvtepi32_epi8(a_);
#else
		std::uint32_t dump[4];
		store_u32x4(dump, a_);
		return setr_i8x16
		(
			static_cast<std::int8_t>(dump[0]),
			static_cast<std::int8_t>(dump[1]),
			static_cast<std::int8_t>(dump[2]),
			static_cast<std::int8_t>(dump[3]),
			0,
			0,
			0,
			0,
			0,
			0,
			0,
			0,
			0,
			0,
			0,
			0
		);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x16 cvt_u64x2_i8x16(u64x2_arg a_)
	{
#if 0 // Need a test for if this is legal
		return _mm_cvtepi64_epi8(a_);
#else
		std::uint64_t dump[4];
		store_u64x2(dump, a_);
		return setr_i8x16
		(
			static_cast<std::int8_t>(dump[0]),
			static_cast<std::int8_t>(dump[1]),
			0,
			0,
			0,
			0,
			0,
			0,
			0,
			0,
			0,
			0,
			0,
			0,
			0,
			0
		);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x16 cvt_u8x32_i8x16(u8x32_arg a_)
	{
		return _mm256_castsi256_si128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x16 cvt_u16x16_i8x16(u16x16_arg a_)
	{
#if 0 // Need a test for if this is legal
		return _mm256_cvtepi16_epi8(a_);
#else
		std::uint16_t dump[16];
		store_u16x16(dump, a_);
		return setr_i8x16
		(
			static_cast<std::int8_t>(dump[0]),
			static_cast<std::int8_t>(dump[1]),
			static_cast<std::int8_t>(dump[2]),
			static_cast<std::int8_t>(dump[3]),
			static_cast<std::int8_t>(dump[4]),
			static_cast<std::int8_t>(dump[5]),
			static_cast<std::int8_t>(dump[6]),
			static_cast<std::int8_t>(dump[7]),
			static_cast<std::int8_t>(dump[8]),
			static_cast<std::int8_t>(dump[9]),
			static_cast<std::int8_t>(dump[10]),
			static_cast<std::int8_t>(dump[11]),
			static_cast<std::int8_t>(dump[12]),
			static_cast<std::int8_t>(dump[13]),
			static_cast<std::int8_t>(dump[14]),
			static_cast<std::int8_t>(dump[15])
		);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x16 cvt_u32x8_i8x16(u32x8_arg a_)
	{
#if 0 // Need a test for if this is legal
		return _mm256_cvtepi32_epi8(a_);
#else
		std::uint32_t dump[8];
		store_u32x8(dump, a_);
		return setr_i8x16
		(
			static_cast<std::int8_t>(dump[0]),
			static_cast<std::int8_t>(dump[1]),
			static_cast<std::int8_t>(dump[2]),
			static_cast<std::int8_t>(dump[3]),
			static_cast<std::int8_t>(dump[4]),
			static_cast<std::int8_t>(dump[5]),
			static_cast<std::int8_t>(dump[6]),
			static_cast<std::int8_t>(dump[7]),
			0,
			0,
			0,
			0,
			0,
			0,
			0,
			0
		);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x16 cvt_u64x4_i8x16(u64x4_arg a_)
	{
#if 0 // Need a test for if this is legal
		return _mm256_cvtepi64_epi8(a_);
#else
		std::uint64_t dump[4];
		store_u64x4(dump, a_);
		return setr_i8x16
		(
			static_cast<std::int8_t>(dump[0]),
			static_cast<std::int8_t>(dump[1]),
			static_cast<std::int8_t>(dump[2]),
			static_cast<std::int8_t>(dump[3]),
			0,
			0,
			0,
			0,
			0,
			0,
			0,
			0,
			0,
			0,
			0,
			0
		);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x16 cvt_u8x64_i8x16(u8x64_arg a_)
	{
		return _mm512_castsi512_si128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x16 cvt_u16x32_i8x16(u16x32_arg a_)
	{
		return cvt_u16x16_i8x16(_mm512_castsi512_si256(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x16 cvt_u32x16_i8x16(u32x16_arg a_)
	{
		return _mm512_cvtepi32_epi8(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x16 cvt_u64x8_i8x16(u64x8_arg a_)
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
	EMU_SIMD_COMMON_FUNC_SPEC auto emulate_fp_i8x16(Func_ func_, EmuSIMD::i8x16_arg in_)
		-> std::enable_if_t<std::is_invocable_r_v<EmuSIMD::f32x4, decltype(func_), EmuSIMD::f32x4>, EmuSIMD::i8x16>
	{
		constexpr std::size_t num_elements = 16;
		constexpr std::size_t elements_per_register = 4;
		std::int8_t data[num_elements];
		float results[num_elements];

		store_i8x16(data, in_);
		for (std::size_t i = 0; i < num_elements; i += elements_per_register)
		{
			_mm_store_ps(results + i, func_(_mm_set_ps(data[i + 3], data[i + 2], data[i + 1], data[i])));
		}

		return set_i8x16
		(
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
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x16 cmpeq_i8x16(EmuSIMD::i8x16_arg lhs_, EmuSIMD::i8x16_arg rhs_)
	{
		return _mm_cmpeq_epi8(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x16 cmpneq_i8x16(EmuSIMD::i8x16_arg lhs_, EmuSIMD::i8x16_arg rhs_)
	{
		constexpr std::int8_t mask = static_cast<std::int8_t>(0xFF);
		return _mm_xor_si128(set1_i8x16(mask), _mm_cmpeq_epi8(lhs_, rhs_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x16 cmpgt_i8x16(EmuSIMD::i8x16_arg lhs_, EmuSIMD::i8x16_arg rhs_)
	{
		return _mm_cmpgt_epi8(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x16 cmplt_i8x16(EmuSIMD::i8x16_arg lhs_, EmuSIMD::i8x16_arg rhs_)
	{
		return _mm_cmplt_epi8(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x16 cmpge_i8x16(EmuSIMD::i8x16_arg lhs_, EmuSIMD::i8x16_arg rhs_)
	{
		return _mm_or_si128(_mm_cmpgt_epi8(lhs_, rhs_), _mm_cmpeq_epi8(lhs_, rhs_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x16 cmple_i8x16(EmuSIMD::i8x16_arg lhs_, EmuSIMD::i8x16_arg rhs_)
	{
		return _mm_or_si128(_mm_cmplt_epi8(lhs_, rhs_), _mm_cmpeq_epi8(lhs_, rhs_));
	}
#pragma endregion

#pragma region BLENDS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x16 blendv_i8x16(EmuSIMD::i8x16_arg a_, EmuSIMD::i8x16_arg b_, EmuSIMD::i8x16_arg shuffle_mask_vec_)
	{
		return _mm_blendv_epi8(a_, b_, shuffle_mask_vec_);
	}

	template<EmuSIMD::Funcs::blend_mask_type BlendMask>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x16 blend_i8x16(EmuSIMD::i8x16_arg a_, EmuSIMD::i8x16_arg b_)
	{
		constexpr bool is_reverse_set = false;
		using target_element_type = std::int8_t;
		constexpr std::size_t num_elements = 16;

		return _mm_blendv_epi8
		(
			a_,
			b_,
			EmuSIMD::Funcs::blend_mask_to_vector<BlendMask, is_reverse_set, target_element_type>
			(
				std::make_index_sequence<num_elements>(),
				[](auto&&...args_) { return set_i8x16(std::forward<decltype(args_)>(args_)...); }
			)
		);
	}
#pragma endregion

#pragma region MOVES
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x16 movehl_i8x16(EmuSIMD::i8x16_arg lhs_, EmuSIMD::i8x16_arg rhs_)
	{
		return cast_f32x4_i8x16(movehl_f32x4(cast_i8x16_f32x4(lhs_), cast_i8x16_f32x4(rhs_)));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x16 movelh_i8x16(EmuSIMD::i8x16_arg lhs_, EmuSIMD::i8x16_arg rhs_)
	{
		return cast_f32x4_i8x16(movelh_f32x4(cast_i8x16_f32x4(lhs_), cast_i8x16_f32x4(rhs_)));
	}
#pragma endregion

#pragma region SHUFFLES
	template<EmuSIMD::Funcs::shuffle_mask_type ShuffleMask_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x16 permute_i8x16(EmuSIMD::i8x16_arg a_)
	{
		constexpr bool is_reverse_set = false;
		using target_element_type = signed char;
		constexpr std::size_t argument_width = 4; // Max value of 15 (0b1111), per index
		constexpr std::size_t num_128_lanes = 1;

		return _mm_shuffle_epi8
		(
			a_,
			EmuSIMD::Funcs::shuffle_mask_to_vector<ShuffleMask_, is_reverse_set, argument_width, num_128_lanes, target_element_type>
			(
				std::make_index_sequence<16>(),
				[](auto&&...args_) { return set_i8x16(std::forward<decltype(args_)>(args_)...); }
			)
		);
	}

	template<EmuSIMD::Funcs::shuffle_mask_type ShuffleMask_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x16 shuffle_i8x16(EmuSIMD::i8x16_arg a_, EmuSIMD::i8x16_arg b_)
	{
		constexpr std::size_t a_permute_mask = duplicate_shuffle_mask_32bit_lane<ShuffleMask_, true>();
		constexpr std::size_t b_permute_mask = duplicate_shuffle_mask_32bit_lane<ShuffleMask_, false>();

		EmuSIMD::i8x16 a_permuted = permute_i8x16<a_permute_mask>(a_);
		EmuSIMD::i8x16 b_permuted = permute_i8x16<b_permute_mask>(b_);

		// Use f32x4 reinterpretation to take the lo bits of permuted a and the lo bits of permuted b and combine them into one register, 
		// where lo(result) = lo(a), hi(result) = lo(b)
		// --- We take this approach as each permutation has been duplicated across 64-bit lanes within the respective permuted register
		EmuSIMD::f32x4 tmp_cast = cast_i8x16_f32x4(a_permuted);
		tmp_cast = movelh_f32x4(tmp_cast, cast_i8x16_f32x4(b_permuted));

		return cast_f32x4_i8x16(tmp_cast);
	}
#pragma endregion

#pragma region BITWISE_ARITHMETIC
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x16 and_i8x16(EmuSIMD::i8x16_arg lhs_, EmuSIMD::i8x16_arg rhs_)
	{
		return _mm_and_si128(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x16 or_i8x16(EmuSIMD::i8x16_arg lhs_, EmuSIMD::i8x16_arg rhs_)
	{
		return _mm_or_si128(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x16 xor_i8x16(EmuSIMD::i8x16_arg lhs_, EmuSIMD::i8x16_arg rhs_)
	{
		return _mm_xor_si128(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x16 andnot_i8x16(EmuSIMD::i8x16_arg not_lhs_, EmuSIMD::i8x16_arg rhs_)
	{
		return _mm_andnot_si128(not_lhs_, rhs_);
	}
#pragma endregion

#pragma region MINMAX_FUNCS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x16 min_i8x16(EmuSIMD::i8x16_arg a_, EmuSIMD::i8x16_arg b_)
	{
		return _mm_min_epi8(a_, b_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x16 horizontal_min_i8x16(EmuSIMD::i8x16_arg a_)
	{
		EmuSIMD::i8x16 min = movelh_i8x16(a_, a_);
		min = min_i8x16(min, a_);
		min = min_i8x16(min, permute_i8x16<make_shuffle_mask_8<0, 1, 2, 3, 4, 5, 6, 7, 0, 1, 2, 3, 4, 5, 6, 7>()>(min));

		// 4 elements left to determine min, so defer to 32-bit calculation
		EmuSIMD::i32x4 last_4_min = cvt_i8x16_i32x4(min);
		last_4_min = horizontal_min_i32x4(last_4_min);

		return min;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x16 max_i8x16(EmuSIMD::i8x16_arg a_, EmuSIMD::i8x16_arg b_)
	{
		return _mm_max_epi8(a_, b_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x16 horizontal_max_i8x16(EmuSIMD::i8x16_arg a_)
	{
		EmuSIMD::i8x16 max = movelh_i8x16(a_, a_);
		max = max_i8x16(max, a_);
		max = max_i8x16(max, permute_i8x16<make_shuffle_mask_8<0, 1, 2, 3, 4, 5, 6, 7, 0, 1, 2, 3, 4, 5, 6, 7>()>(max));

		// 4 elements left to determine max, so defer to 32-bit calculation
		EmuSIMD::i32x4 last_4_max = cvt_i8x16_i32x4(max);
		last_4_max = horizontal_max_i32x4(last_4_max);

		max = cvt_i32x4_i8x16(last_4_max);
		max = permute_i8x16<make_reverse_shuffle_mask_8<0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0>()>(max);

		return max;
	}
#pragma endregion

#pragma region BASIC_ARITHMETIC
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x16 mul_all_i8x16(EmuSIMD::i8x16_arg lhs_, EmuSIMD::i8x16_arg rhs_)
	{
		EmuSIMD::i8x16 even_bytes = _mm_mullo_epi16(lhs_, rhs_);
		EmuSIMD::i8x16 odd_bytes = _mm_mullo_epi16(_mm_srli_epi16(lhs_, 8), _mm_srli_epi16(rhs_, 8));
		return _mm_or_si128(_mm_slli_epi16(odd_bytes, 8), _mm_srli_epi16(_mm_slli_epi16(even_bytes, 8), 8));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x16 negate_i8x16(EmuSIMD::i8x16_arg to_negate_)
	{
		return _mm_sub_epi8(_mm_setzero_si128(), to_negate_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x16 add_i8x16(EmuSIMD::i8x16_arg lhs_, EmuSIMD::i8x16_arg rhs_)
	{
		return _mm_add_epi8(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x16 sub_i8x16(EmuSIMD::i8x16_arg lhs_, EmuSIMD::i8x16_arg rhs_)
	{
		return _mm_sub_epi8(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x16 mul_i8x16(EmuSIMD::i8x16_arg lhs_, EmuSIMD::i8x16_arg rhs_)
	{
		// lo
		EmuSIMD::i16x8 lane64_a = cvt_i8x16_i16x8(lhs_);
		EmuSIMD::i16x8 lane64_b = cvt_i8x16_i16x8(rhs_);
		EmuSIMD::i8x16 lo = cvt_i16x8_i8x16(mul_i16x8(lane64_a, lane64_b));

		// hi - move hi bits to lo via f32 reinterpretation of this width register
		EmuSIMD::f32x4 tmp_cast = cast_i8x16_f32x4(lhs_);
		tmp_cast = _mm_movehl_ps(tmp_cast, tmp_cast);
		lane64_a = cvt_i8x16_i16x8(cast_f32x4_i8x16(tmp_cast));

		tmp_cast = cast_i8x16_f32x4(rhs_);
		tmp_cast = _mm_movehl_ps(tmp_cast, tmp_cast);
		lane64_b = cvt_i8x16_i16x8(cast_f32x4_i8x16(tmp_cast));

		// Move hi and lo into the same register, using the same f32 reinterpretation for moving hi and lo bits
		EmuSIMD::i8x16 hi = cvt_i16x8_i8x16(mul_i16x8(lane64_a, lane64_b));
		tmp_cast = cast_i8x16_f32x4(lo);
		tmp_cast = _mm_movelh_ps(tmp_cast, cast_i8x16_f32x4(hi));

		return cast_f32x4_i8x16(tmp_cast);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x16 div_i8x16(EmuSIMD::i8x16_arg lhs_, EmuSIMD::i8x16_arg rhs_)
	{
	#if EMU_CORE_X86_X64_SVML
		return _mm_div_epi8(lhs_, rhs_);
	#else
		// lo
		EmuSIMD::i16x8 lane64_a = cvt_i8x16_i16x8(lhs_);
		EmuSIMD::i16x8 lane64_b = cvt_i8x16_i16x8(rhs_);
		EmuSIMD::i8x16 lo = cvt_i16x8_i8x16(div_i16x8(lane64_a, lane64_b));
		
		// hi - move hi bits to lo via f32 reinterpretation of this width register
		EmuSIMD::i8x16 tmp_lane = movehl_i8x16(lhs_, lhs_);
		lane64_a = cvt_i8x16_i16x8(tmp_lane);
		
		tmp_lane = movehl_i8x16(rhs_, rhs_);
		lane64_b = cvt_i8x16_i16x8(tmp_lane);
		
		// Move hi and lo into the same register, in their respective 64-bit lanes
		EmuSIMD::i8x16 hi = cvt_i16x8_i8x16(div_i16x8(lane64_a, lane64_b));
		return movelh_i8x16(lo, hi);
	#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x16 addsub_i8x16(EmuSIMD::i8x16_arg lhs_, EmuSIMD::i8x16_arg rhs_)
	{
		constexpr std::int8_t byte_mask = static_cast<std::int8_t>(0xFF);
		const EmuSIMD::i8x16 mask = set_i8x16(byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0);
		EmuSIMD::i8x16 out = add_i8x16(lhs_, and_i8x16(mask, rhs_));
		return sub_i8x16(lhs_, andnot_i8x16(mask, rhs_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x16 subadd_i8x16(EmuSIMD::i8x16_arg lhs_, EmuSIMD::i8x16_arg rhs_)
	{
		constexpr std::int8_t byte_mask = static_cast<std::int8_t>(0xFF);
		const EmuSIMD::i8x16 mask = set_i8x16(byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0);
		EmuSIMD::i8x16 out = sub_i8x16(lhs_, and_i8x16(mask, rhs_));
		return add_i8x16(lhs_, andnot_i8x16(mask, rhs_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x16 fmadd_i8x16(EmuSIMD::i8x16_arg a_, EmuSIMD::i8x16_arg b_, EmuSIMD::i8x16_arg c_)
	{
		return add_i8x16(mul_all_i8x16(a_, b_), c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x16 fmsub_i8x16(EmuSIMD::i8x16_arg a_, EmuSIMD::i8x16_arg b_, EmuSIMD::i8x16_arg c_)
	{
		return sub_i8x16(mul_all_i8x16(a_, b_), c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x16 fnmadd_i8x16(EmuSIMD::i8x16_arg a_, EmuSIMD::i8x16_arg b_, EmuSIMD::i8x16_arg c_)
	{
		return add_i8x16(mul_all_i8x16(negate_i8x16(a_), b_), c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x16 fnmsub_i8x16(EmuSIMD::i8x16_arg a_, EmuSIMD::i8x16_arg b_, EmuSIMD::i8x16_arg c_)
	{
		return sub_i8x16(mul_all_i8x16(negate_i8x16(a_), b_), c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x16 fmaddsub_i8x16(EmuSIMD::i8x16_arg a_, EmuSIMD::i8x16_arg b_, EmuSIMD::i8x16_arg c_)
	{
		return addsub_i8x16(mul_all_i8x16(negate_i8x16(a_), b_), c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x16 fmsubadd_i8x16(EmuSIMD::i8x16_arg a_, EmuSIMD::i8x16_arg b_, EmuSIMD::i8x16_arg c_)
	{
		return subadd_i8x16(mul_all_i8x16(negate_i8x16(a_), b_), c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x16 floor_i8x16(EmuSIMD::i8x16_arg to_floor_)
	{
		return to_floor_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x16 ceil_i8x16(EmuSIMD::i8x16_arg to_ceil_)
	{
		return to_ceil_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x16 trunc_i8x16(EmuSIMD::i8x16_arg to_trunc_)
	{
		return to_trunc_;
	}

	template<int RoundingFlag_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x16 round_i8x16(EmuSIMD::i8x16_arg to_round_)
	{
		return to_round_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x16 mod_i8x16(EmuSIMD::i8x16_arg lhs_, EmuSIMD::i8x16_arg rhs_)
	{
	#if EMU_CORE_X86_X64_SVML
		return _mm_rem_epi8(lhs_, rhs_);
	#else
		EmuSIMD::i8x16 to_subtract = div_i8x16(lhs_, rhs_);
		to_subtract = mul_all_i8x16(to_subtract, rhs_);
		return sub_i8x16(lhs_, to_subtract);
	#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x16 abs_i8x16(EmuSIMD::i8x16_arg in_)
	{
		return _mm_abs_epi8(in_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x16 sqrt_i8x16(EmuSIMD::i8x16_arg in_)
	{
		return emulate_fp_i8x16([](EmuSIMD::f32x4_arg in_fp_) { return sqrt_f32x4(in_fp_); }, in_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x16 rsqrt_i8x16(EmuSIMD::i8x16_arg in_)
	{
		return emulate_fp_i8x16([](EmuSIMD::f32x4_arg in_fp_) { return rsqrt_f32x4(in_fp_); }, in_);
	}
#pragma endregion

#pragma region NEAR_COMPARISONS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x16 cmpnear_i8x16(EmuSIMD::i8x16_arg lhs_, EmuSIMD::i8x16_arg rhs_)
	{
		return cmpeq_i8x16(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x16 cmpnear_i8x16(EmuSIMD::i8x16_arg lhs_, EmuSIMD::i8x16_arg rhs_, EmuSIMD::i8x16_arg epsilon)
	{
		return cmple_i8x16(abs_i8x16(sub_i8x16(lhs_, rhs_)), epsilon);
	}
#pragma endregion

#pragma region TRIG
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x16 cos_i8x16(EmuSIMD::i8x16_arg in_)
	{
		constexpr std::size_t num_elements = 16;
		constexpr std::size_t elements_per_register = 4;
		std::int8_t data[num_elements];
		float results[num_elements];

		store_i8x16(data, in_);
		for (std::size_t i = 0; i < num_elements; i += elements_per_register)
		{
			store_f32x4(results + i, cos_f32x4(set_f32x4(static_cast<float>(data[i + 3]), static_cast<float>(data[i + 2]), static_cast<float>(data[i + 1]), static_cast<float>(data[i]))));
		}

		return set_i8x16
		(
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

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x16 sin_i8x16(EmuSIMD::i8x16_arg in_)
	{
		constexpr std::size_t num_elements = 16;
		constexpr std::size_t elements_per_register = 4;
		std::int8_t data[num_elements];
		float results[num_elements];

		store_i8x16(data, in_);
		for (std::size_t i = 0; i < num_elements; i += elements_per_register)
		{
			store_f32x4(results + i, sin_f32x4(set_f32x4(static_cast<float>(data[i + 3]), static_cast<float>(data[i + 2]), static_cast<float>(data[i + 1]), static_cast<float>(data[i]))));
		}

		return set_i8x16
		(
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

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x16 tan_i8x16(EmuSIMD::i8x16_arg in_)
	{
		constexpr std::size_t num_elements = 16;
		constexpr std::size_t elements_per_register = 4;
		std::int8_t data[num_elements];
		float results[num_elements];

		store_i8x16(data, in_);
		for (std::size_t i = 0; i < num_elements; i += elements_per_register)
		{
			store_f32x4(results + i, tan_f32x4(set_f32x4(static_cast<float>(data[i + 3]), static_cast<float>(data[i + 2]), static_cast<float>(data[i + 1]), static_cast<float>(data[i]))));
		}

		return set_i8x16
		(
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

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x16 acos_i8x16(EmuSIMD::i8x16_arg in_)
	{
		constexpr std::size_t num_elements = 16;
		constexpr std::size_t elements_per_register = 4;
		std::int8_t data[num_elements];
		float results[num_elements];

		store_i8x16(data, in_);
		for (std::size_t i = 0; i < num_elements; i += elements_per_register)
		{
			store_f32x4(results + i, acos_f32x4(set_f32x4(static_cast<float>(data[i + 3]), static_cast<float>(data[i + 2]), static_cast<float>(data[i + 1]), static_cast<float>(data[i]))));
		}

		return set_i8x16
		(
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

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x16 asin_i8x16(EmuSIMD::i8x16_arg in_)
	{
		constexpr std::size_t num_elements = 16;
		constexpr std::size_t elements_per_register = 4;
		std::int8_t data[num_elements];
		float results[num_elements];

		store_i8x16(data, in_);
		for (std::size_t i = 0; i < num_elements; i += elements_per_register)
		{
			store_f32x4(results + i, asin_f32x4(set_f32x4(static_cast<float>(data[i + 3]), static_cast<float>(data[i + 2]), static_cast<float>(data[i + 1]), static_cast<float>(data[i]))));
		}

		return set_i8x16
		(
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

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x16 atan_i8x16(EmuSIMD::i8x16_arg in_)
	{
		constexpr std::size_t num_elements = 16;
		constexpr std::size_t elements_per_register = 4;
		std::int8_t data[num_elements];
		float results[num_elements];

		store_i8x16(data, in_);
		for (std::size_t i = 0; i < num_elements; i += elements_per_register)
		{
			store_f32x4(results + i, atan_f32x4(set_f32x4(static_cast<float>(data[i + 3]), static_cast<float>(data[i + 2]), static_cast<float>(data[i + 1]), static_cast<float>(data[i]))));
		}

		return set_i8x16
		(
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
}

#endif
