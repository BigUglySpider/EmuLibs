#ifndef EMU_SIMD_GENERIC_FUNCS_U32X8_H_INC_
#define EMU_SIMD_GENERIC_FUNCS_U32X8_H_INC_ 1

#include "_generic_declarations/_all_generic_declarations.h"
#include "_common_generic_func_helpers.h"

namespace EmuSIMD::Funcs
{
#pragma region SETTERS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x8 set_u32x8
	(
		std::uint32_t e0, std::uint32_t e1, std::uint32_t e2, std::uint32_t e3, std::uint32_t e4, std::uint32_t e5, std::uint32_t e6, std::uint32_t e7
	)
	{
		return _mm256_set_epi32(e0, e1, e2, e3, e4, e5, e6, e7);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x8 setr_u32x8
	(
		std::uint32_t e0, std::uint32_t e1, std::uint32_t e2, std::uint32_t e3, std::uint32_t e4, std::uint32_t e5, std::uint32_t e6, std::uint32_t e7
	)
	{
		//return _mm256_setr_epi32(e0, e1, e2, e3, e4, e5, e6, e7);
		return _mm256_set_epi32(e7, e6, e5, e4, e3, e2, e1, e0);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x8 set1_u32x8(std::uint32_t all_)
	{
		return _mm256_set1_epi32(all_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x8 load_u32x8(const std::uint32_t* p_to_load_)
	{
		return _mm256_load_si256(reinterpret_cast<const __m256i*>(p_to_load_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x8 setzero_u32x8()
	{
		return _mm256_setzero_si256();
	}
#pragma endregion

#pragma region STORES
	EMU_SIMD_COMMON_FUNC_SPEC void store_u32x8(std::uint32_t* p_out_, u32x8_arg a_)
	{
		_mm256_store_si256(reinterpret_cast<__m256i*>(p_out_), a_);
	}
#pragma endregion

#pragma region CASTS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x8 cast_f32x4_u32x8(f32x4_arg a_)
	{
		return _mm256_castsi128_si256(_mm_castps_si128(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x8 cast_f32x8_u32x8(f32x8_arg a_)
	{
		return _mm256_castps_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x8 cast_f32x16_u32x8(f32x16_arg a_)
	{
		return _mm512_castsi512_si256(_mm512_castps_si512(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x8 cast_f64x2_u32x8(f64x2_arg a_)
	{
		return _mm256_castsi128_si256(_mm_castpd_si128(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x8 cast_f64x4_u32x8(f64x4_arg a_)
	{
		return _mm256_castpd_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x8 cast_f64x8_u32x8(f64x8_arg a_)
	{
		return _mm512_castsi512_si256(_mm512_castpd_si512(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x8 cast_i8x16_u32x8(i8x16_arg a_)
	{
		return _mm256_castsi128_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x8 cast_i16x8_u32x8(i16x8_arg a_)
	{
		return _mm256_castsi128_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x8 cast_i32x4_u32x8(i32x4_arg a_)
	{
		return _mm256_castsi128_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x8 cast_i64x2_u32x8(i64x2_arg a_)
	{
		return _mm256_castsi128_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x8 cast_i8x32_u32x8(i8x32_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x8 cast_i16x16_u32x8(i16x16_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x8 cast_i32x8_u32x8(i32x8_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x8 cast_i64x4_u32x8(i64x4_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x8 cast_i8x64_u32x8(i8x64_arg a_)
	{
		return _mm512_castsi512_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x8 cast_i16x32_u32x8(i16x32_arg a_)
	{
		return _mm512_castsi512_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x8 cast_i32x16_u32x8(i32x16_arg a_)
	{
		return _mm512_castsi512_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x8 cast_i64x8_u32x8(i64x8_arg a_)
	{
		return _mm512_castsi512_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x8 cast_u8x16_u32x8(u8x16_arg a_)
	{
		return _mm256_castsi128_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x8 cast_u16x8_u32x8(u16x8_arg a_)
	{
		return _mm256_castsi128_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x8 cast_u32x4_u32x8(u32x4_arg a_)
	{
		return _mm256_castsi128_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x8 cast_u64x2_u32x8(u64x2_arg a_)
	{
		return _mm256_castsi128_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x8 cast_u8x32_u32x8(u8x32_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x8 cast_u16x16_u32x8(u16x16_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x8 cast_u32x8_u32x8(u32x8_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x8 cast_u64x4_u32x8(u64x4_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x8 cast_u8x64_u32x8(u8x64_arg a_)
	{
		return _mm512_castsi512_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x8 cast_u16x32_u32x8(u16x32_arg a_)
	{
		return _mm512_castsi512_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x8 cast_u32x16_u32x8(u32x16_arg a_)
	{
		return _mm512_castsi512_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x8 cast_u64x8_u32x8(u64x8_arg a_)
	{
		return _mm512_castsi512_si256(a_);
	}
#pragma endregion

#pragma region EXTRACTION_TEMPLATES
	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x8 extract_f32x8_lane_u32x8(f32x8_arg a_)
	{
		static_assert(Index_ == 0, "Invalid SIMD lane extraction index: Extracting u32x8 lane from a f32x8 instance; the maximum index is 0 but this index has been exceeded.");
		return cast_f32x8_u32x8(a_);
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x8 extract_f32x16_lane_u32x8(f32x16_arg a_)
	{
		static_assert(Index_ <= 1, "Invalid SIMD lane extraction index: Extracting u32x8 lane from a f32x16 instance; the maximum index is 1 but this index has been exceeded.");
		if constexpr (Index_ == 0)
		{
			return cast_f32x16_u32x8(a_);
		}
		else
		{
			return cast_f32x8_u32x8(_mm512_extractf32x8_ps(a_, Index_));
		}
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x8 extract_f64x4_lane_u32x8(f64x4_arg a_)
	{
		static_assert(Index_ == 0, "Invalid SIMD lane extraction index: Extracting u32x8 lane from a f64x4 instance; the maximum index is 0 but this index has been exceeded.");
		return cast_f64x4_u32x8(a_);
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x8 extract_f64x8_lane_u32x8(f64x8_arg a_)
	{
		static_assert(Index_ <= 1, "Invalid SIMD lane extraction index: Extracting u32x8 lane from a f64x8 instance; the maximum index is 1 but this index has been exceeded.");
		if constexpr (Index_ == 0)
		{
			return cast_f64x8_u32x8(a_);
		}
		else
		{
			return cast_f64x4_u32x8(_mm512_extractf64x4_pd(a_, Index_));
		}
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x8 extract_i8x32_lane_u32x8(i8x32_arg a_)
	{
		static_assert(Index_ == 0, "Invalid SIMD lane extraction index: Extracting u32x8 lane from a i8x32 instance; the maximum index is 0 but this index has been exceeded.");
		return cast_i8x32_u32x8(a_);
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x8 extract_i8x64_lane_u32x8(i8x64_arg a_)
	{
		static_assert(Index_ <= 1, "Invalid SIMD lane extraction index: Extracting u32x8 lane from a i8x64 instance; the maximum index is 1 but this index has been exceeded.");
		if constexpr (Index_ == 0)
		{
			return cast_i8x64_u32x8(a_);
		}
		else
		{
			return _mm512_extracti32x8_epi32(a_, Index_);
		}
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x8 extract_i16x16_lane_u32x8(i16x16_arg a_)
	{
		static_assert(Index_ == 0, "Invalid SIMD lane extraction index: Extracting u32x8 lane from a i16x16 instance; the maximum index is 0 but this index has been exceeded.");
		return cast_i16x16_u32x8(a_);
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x8 extract_i16x32_lane_u32x8(i16x32_arg a_)
	{
		static_assert(Index_ <= 1, "Invalid SIMD lane extraction index: Extracting u32x8 lane from a i16x32 instance; the maximum index is 1 but this index has been exceeded.");
		if constexpr (Index_ == 0)
		{
			return cast_i16x32_u32x8(a_);
		}
		else
		{
			return _mm512_extracti32x8_epi32(a_, Index_);
		}
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x8 extract_i32x8_lane_u32x8(i32x8_arg a_)
	{
		static_assert(Index_ == 0, "Invalid SIMD lane extraction index: Extracting u32x8 lane from a i32x8 instance; the maximum index is 0 but this index has been exceeded.");
		return cast_i32x8_u32x8(a_);
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x8 extract_i32x16_lane_u32x8(i32x16_arg a_)
	{
		static_assert(Index_ <= 1, "Invalid SIMD lane extraction index: Extracting u32x8 lane from a i32x16 instance; the maximum index is 1 but this index has been exceeded.");
		if constexpr (Index_ == 0)
		{
			return cast_i32x16_u32x8(a_);
		}
		else
		{
			return _mm512_extracti32x8_epi32(a_, Index_);
		}
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x8 extract_i64x4_lane_u32x8(i64x4_arg a_)
	{
		static_assert(Index_ == 0, "Invalid SIMD lane extraction index: Extracting u32x8 lane from a i64x4 instance; the maximum index is 0 but this index has been exceeded.");
		return cast_i64x4_u32x8(a_);
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x8 extract_i64x8_lane_u32x8(i64x8_arg a_)
	{
		static_assert(Index_ <= 1, "Invalid SIMD lane extraction index: Extracting u32x8 lane from a i64x8 instance; the maximum index is 1 but this index has been exceeded.");
		if constexpr (Index_ == 0)
		{
			return cast_i64x8_u32x8(a_);
		}
		else
		{
			return _mm512_extracti32x8_epi32(a_, Index_);
		}
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x8 extract_u8x32_lane_u32x8(u8x32_arg a_)
	{
		static_assert(Index_ == 0, "Invalid SIMD lane extraction index: Extracting u32x8 lane from a u8x32 instance; the maximum index is 0 but this index has been exceeded.");
		return cast_u8x32_u32x8(a_);
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x8 extract_u8x64_lane_u32x8(u8x64_arg a_)
	{
		static_assert(Index_ <= 1, "Invalid SIMD lane extraction index: Extracting u32x8 lane from a u8x64 instance; the maximum index is 1 but this index has been exceeded.");
		if constexpr (Index_ == 0)
		{
			return cast_u8x64_u32x8(a_);
		}
		else
		{
			return _mm512_extracti32x8_epi32(a_, Index_);
		}
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x8 extract_u16x16_lane_u32x8(u16x16_arg a_)
	{
		static_assert(Index_ == 0, "Invalid SIMD lane extraction index: Extracting u32x8 lane from a u16x16 instance; the maximum index is 0 but this index has been exceeded.");
		return cast_u16x16_u32x8(a_);
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x8 extract_u16x32_lane_u32x8(u16x32_arg a_)
	{
		static_assert(Index_ <= 1, "Invalid SIMD lane extraction index: Extracting u32x8 lane from a u16x32 instance; the maximum index is 1 but this index has been exceeded.");
		if constexpr (Index_ == 0)
		{
			return cast_u16x32_u32x8(a_);
		}
		else
		{
			return _mm512_extracti32x8_epi32(a_, Index_);
		}
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x8 extract_u32x8_lane_u32x8(u32x8_arg a_)
	{
		static_assert(Index_ == 0, "Invalid SIMD lane extraction index: Extracting u32x8 lane from a u32x8 instance; the maximum index is 0 but this index has been exceeded.");
		return a_;
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x8 extract_u32x16_lane_u32x8(u32x16_arg a_)
	{
		static_assert(Index_ <= 1, "Invalid SIMD lane extraction index: Extracting u32x8 lane from a u32x16 instance; the maximum index is 1 but this index has been exceeded.");
		if constexpr (Index_ == 0)
		{
			return cast_u32x16_u32x8(a_);
		}
		else
		{
			return _mm512_extracti32x8_epi32(a_, Index_);
		}
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x8 extract_u64x4_lane_u32x8(u64x4_arg a_)
	{
		static_assert(Index_ == 0, "Invalid SIMD lane extraction index: Extracting u32x8 lane from a u64x4 instance; the maximum index is 0 but this index has been exceeded.");
		return cast_u64x4_u32x8(a_);
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x8 extract_u64x8_lane_u32x8(u64x8_arg a_)
	{
		static_assert(Index_ <= 1, "Invalid SIMD lane extraction index: Extracting u32x8 lane from a u64x8 instance; the maximum index is 1 but this index has been exceeded.");
		if constexpr (Index_ == 0)
		{
			return cast_u64x8_u32x8(a_);
		}
		else
		{
			return _mm512_extracti32x8_epi32(a_, Index_);
		}
	}
#pragma endregion

#pragma region CONVERSIONS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x8 cvt_f32x4_u32x8(f32x4_arg a_)
	{
		return _mm256_castsi128_si256(_mm_cvtps_epi32(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x8 cvt_f32x8_u32x8(f32x8_arg a_)
	{
		return _mm256_cvtps_epi32(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x8 cvt_f32x16_u32x8(f32x16_arg a_)
	{
		return _mm256_cvtps_epi32(_mm512_castps512_ps256(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x8 cvt_f64x2_u32x8(f64x2_arg a_)
	{
		return _mm256_castsi128_si256(_mm_cvtepi64_epi32(_mm_cvtpd_epi64(a_)));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x8 cvt_f64x4_u32x8(f64x4_arg a_)
	{
		return _mm256_castsi128_si256(_mm256_cvtpd_epi32(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x8 cvt_f64x8_u32x8(f64x8_arg a_)
	{
		return _mm512_cvtpd_epi32(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x8 cvt_i8x16_u32x8(i8x16_arg a_)
	{
		return _mm256_cvtepi8_epi32(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x8 cvt_i16x8_u32x8(i16x8_arg a_)
	{
		return _mm256_cvtepi16_epi32(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x8 cvt_i32x4_u32x8(i32x4_arg a_)
	{
		return _mm256_castsi128_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x8 cvt_i64x2_u32x8(i64x2_arg a_)
	{
		return _mm256_castsi128_si256(_mm_cvtepi64_epi32(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x8 cvt_i8x32_u32x8(i8x32_arg a_)
	{
		return _mm256_cvtepi8_epi32(_mm256_castsi256_si128(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x8 cvt_i16x16_u32x8(i16x16_arg a_)
	{
		return _mm256_cvtepi16_epi32(_mm256_castsi256_si128(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x8 cvt_i32x8_u32x8(i32x8_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x8 cvt_i64x4_u32x8(i64x4_arg a_)
	{
		return _mm256_castsi128_si256(_mm256_cvtepi64_epi32(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x8 cvt_i8x64_u32x8(i8x64_arg a_)
	{
		return _mm512_castsi512_si256(_mm512_cvtepi8_epi32(_mm512_castsi512_si128(a_)));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x8 cvt_i16x32_u32x8(i16x32_arg a_)
	{
		return _mm512_castsi512_si256(_mm512_cvtepi16_epi32(_mm512_castsi512_si256(a_)));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x8 cvt_i32x16_u32x8(i32x16_arg a_)
	{
		return _mm512_castsi512_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x8 cvt_i64x8_u32x8(i64x8_arg a_)
	{
		return _mm512_cvtepi64_epi32(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x8 cvt_u8x16_u32x8(u8x16_arg a_)
	{
		return _mm256_cvtepi8_epi32(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x8 cvt_u16x8_u32x8(u16x8_arg a_)
	{
		return _mm256_cvtepi16_epi32(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x8 cvt_u32x4_u32x8(u32x4_arg a_)
	{
		return _mm256_castsi128_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x8 cvt_u64x2_u32x8(u64x2_arg a_)
	{
		return _mm256_castsi128_si256(_mm_cvtepi64_epi32(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x8 cvt_u8x32_u32x8(u8x32_arg a_)
	{
		return _mm256_cvtepi8_epi32(_mm256_castsi256_si128(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x8 cvt_u16x16_u32x8(u16x16_arg a_)
	{
		return _mm256_cvtepi16_epi32(_mm256_castsi256_si128(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x8 cvt_u32x8_u32x8(u32x8_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x8 cvt_u64x4_u32x8(u64x4_arg a_)
	{
		return _mm256_castsi128_si256(_mm256_cvtepi64_epi32(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x8 cvt_u8x64_u32x8(u8x64_arg a_)
	{
		return _mm512_castsi512_si256(_mm512_cvtepi8_epi32(_mm512_castsi512_si128(a_)));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x8 cvt_u16x32_u32x8(u16x32_arg a_)
	{
		return _mm512_castsi512_si256(_mm512_cvtepi16_epi32(_mm512_castsi512_si256(a_)));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x8 cvt_u32x16_u32x8(u32x16_arg a_)
	{
		return _mm512_castsi512_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x8 cvt_u64x8_u32x8(u64x8_arg a_)
	{
		return _mm512_cvtepi64_epi32(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x8 setmasked_u32x8(std::uint8_t bit_mask_)
	{
		constexpr std::uint32_t element_mask = static_cast<std::uint32_t>(0xFFFFFFFF);
		return _mm256_set_epi32
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
	EMU_SIMD_COMMON_FUNC_SPEC auto emulate_fp_u32x8(Func_ func_, EmuSIMD::u32x8_arg in_)
		-> std::enable_if_t<std::is_invocable_r_v<EmuSIMD::f32x8, decltype(func_), EmuSIMD::f32x8>, EmuSIMD::u32x8>
	{
		return cvt_f32x8_u32x8
		(
			func_(cvt_u32x8_f32x8(in_))
		);
	}
#pragma endregion

#pragma region COMPARISONS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x8 cmpeq_u32x8(EmuSIMD::u32x8_arg lhs_, EmuSIMD::u32x8_arg rhs_)
	{
		return _mm256_cmpeq_epi32(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x8 cmpneq_u32x8(EmuSIMD::u32x8_arg lhs_, EmuSIMD::u32x8_arg rhs_)
	{
		constexpr std::uint32_t mask = static_cast<std::uint32_t>(0xFFFFFFFF);
		return _mm256_xor_si256(set1_u32x8(mask), _mm256_cmpeq_epi32(lhs_, rhs_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x8 cmpgt_u32x8(EmuSIMD::u32x8_arg lhs_, EmuSIMD::u32x8_arg rhs_)
	{
		constexpr std::uint32_t mask = static_cast<std::uint32_t>(0xFFFFFFFF);
		return _mm256_andnot_si256(_mm256_cmpeq_epi32(_mm256_min_epu32(lhs_, rhs_), lhs_), set1_u32x8(mask));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x8 cmplt_u32x8(EmuSIMD::u32x8_arg lhs_, EmuSIMD::u32x8_arg rhs_)
	{
		constexpr std::uint32_t mask = static_cast<std::uint32_t>(0xFFFFFFFF);
		return _mm256_andnot_si256(_mm256_cmpeq_epi32(_mm256_max_epu32(lhs_, rhs_), lhs_), set1_u32x8(mask));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x8 cmpge_u32x8(EmuSIMD::u32x8_arg lhs_, EmuSIMD::u32x8_arg rhs_)
	{
		return _mm256_cmpeq_epi32(_mm256_max_epu32(lhs_, rhs_), lhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x8 cmple_u32x8(EmuSIMD::u32x8_arg lhs_, EmuSIMD::u32x8_arg rhs_)
	{
		return _mm256_cmpeq_epi32(_mm256_min_epu32(lhs_, rhs_), lhs_);
	}
#pragma endregion

#pragma region MOVES
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x8 movehl_u32x8(EmuSIMD::u32x8_arg lhs_, EmuSIMD::u32x8_arg rhs_)
	{
		return cast_f32x8_u32x8(movehl_f32x8(cast_u32x8_f32x8(lhs_), cast_u32x8_f32x8(rhs_)));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x8 movelh_u32x8(EmuSIMD::u32x8_arg lhs_, EmuSIMD::u32x8_arg rhs_)
	{
		return cast_f32x8_u32x8(movelh_f32x8(cast_u32x8_f32x8(lhs_), cast_u32x8_f32x8(rhs_)));
	}
#pragma endregion

#pragma region BLENDS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x8 blendv_u32x8(EmuSIMD::u32x8_arg a_, EmuSIMD::u32x8_arg b_, EmuSIMD::u32x8_arg shuffle_mask_vec_)
	{
		return cast_f32x8_u32x8
		(
			blendv_f32x8
			(
				cast_u32x8_f32x8(a_),
				cast_u32x8_f32x8(b_),
				cast_u32x8_f32x8(shuffle_mask_vec_)
			)
		);
	}

	template<EmuSIMD::Funcs::blend_mask_type BlendMask_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x8 blend_u32x8(EmuSIMD::u32x8_arg a_, EmuSIMD::u32x8_arg b_)
	{
		return _mm256_blend_epi32(a_, b_, BlendMask_);
	}
#pragma endregion

#pragma region MINMAX_FUNCS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x8 min_u32x8(EmuSIMD::u32x8_arg a_, EmuSIMD::u32x8_arg b_)
	{
		return _mm256_min_epu32(a_, b_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x8 max_u32x8(EmuSIMD::u32x8_arg a_, EmuSIMD::u32x8_arg b_)
	{
		return _mm256_max_epu32(a_, b_);
	}
#pragma endregion

#pragma region SHUFFLES
	template<EmuSIMD::Funcs::shuffle_mask_type ShuffleMask_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x8 permute_u32x8(EmuSIMD::u32x8_arg a_)
	{
		return _mm256_shuffle_epi32(a_, ShuffleMask_);
	}

	template<EmuSIMD::Funcs::shuffle_mask_type ShuffleMask_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x8 shuffle_u32x8(EmuSIMD::u32x8_arg a_, EmuSIMD::u32x8_arg b_)
	{
		return cast_f32x8_u32x8
		(
			shuffle_f32x8<ShuffleMask_>
			(
				cast_u32x8_f32x8(a_),
				cast_u32x8_f32x8(b_)
			)
		);
	}
#pragma endregion

#pragma region BASIC_ARITHMETIC
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x8 mul_all_u32x8(EmuSIMD::u32x8_arg lhs_, EmuSIMD::u32x8_arg rhs_)
	{
		return _mm256_mullo_epi32(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x8 negate_u32x8(EmuSIMD::u32x8_arg to_negate_)
	{
		return _mm256_sub_epi32(_mm256_setzero_si256(), to_negate_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x8 add_u32x8(EmuSIMD::u32x8_arg lhs_, EmuSIMD::u32x8_arg rhs_)
	{
		return _mm256_add_epi32(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x8 sub_u32x8(EmuSIMD::u32x8_arg lhs_, EmuSIMD::u32x8_arg rhs_)
	{
		return _mm256_sub_epi32(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x8 mul_u32x8(EmuSIMD::u32x8_arg lhs_, EmuSIMD::u32x8_arg rhs_)
	{
		return _mm256_mul_epu32(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x8 div_u32x8(EmuSIMD::u32x8_arg lhs_, EmuSIMD::u32x8_arg rhs_)
	{
#if EMU_CORE_X86_X64_SVML
		return _mm256_div_epu32(lhs_, rhs_);
#else
		EmuSIMD::f32x8 result_f32 = cvt_u32x8_f32x8(lhs_);
		result_f32 = div_f32x8(result_f32, cvt_u32x8_f32x8(rhs_));
		return cvt_f32x8_u32x8(trunc_f32x8(result_f32));
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x8 addsub_u32x8(EmuSIMD::u32x8_arg lhs_, EmuSIMD::u32x8_arg rhs_)
	{
		constexpr std::uint32_t bytes_mask = static_cast<std::uint32_t>(0xFFFFFFFF);
		const EmuSIMD::u32x8 mask = _mm256_set_epi32(bytes_mask, 0, bytes_mask, 0, bytes_mask, 0, bytes_mask, 0);
		EmuSIMD::u32x8 out = _mm256_add_epi32(lhs_, _mm256_and_si256(mask, rhs_));
		return _mm256_sub_epi32(lhs_, _mm256_andnot_si256(mask, rhs_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x8 subadd_u32x8(EmuSIMD::u32x8_arg lhs_, EmuSIMD::u32x8_arg rhs_)
	{
		constexpr std::uint32_t bytes_mask = static_cast<std::uint32_t>(0xFFFFFFFF);
		const EmuSIMD::u32x8 mask = _mm256_set_epi32(bytes_mask, 0, bytes_mask, 0, bytes_mask, 0, bytes_mask, 0);
		EmuSIMD::u32x8 out = _mm256_sub_epi32(lhs_, _mm256_and_si256(mask, rhs_));
		return _mm256_add_epi32(lhs_, _mm256_andnot_si256(mask, rhs_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x8 fmadd_u32x8(EmuSIMD::u32x8_arg a_, EmuSIMD::u32x8_arg b_, EmuSIMD::u32x8_arg c_)
	{
		return _mm256_add_epi32(mul_all_u32x8(a_, b_), c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x8 fmsub_u32x8(EmuSIMD::u32x8_arg a_, EmuSIMD::u32x8_arg b_, EmuSIMD::u32x8_arg c_)
	{
		return _mm256_sub_epi32(mul_all_u32x8(a_, b_), c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x8 fnmadd_u32x8(EmuSIMD::u32x8_arg a_, EmuSIMD::u32x8_arg b_, EmuSIMD::u32x8_arg c_)
	{
		return _mm256_add_epi32(mul_all_u32x8(negate_u32x8(a_), b_), c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x8 fnmsub_u32x8(EmuSIMD::u32x8_arg a_, EmuSIMD::u32x8_arg b_, EmuSIMD::u32x8_arg c_)
	{
		return _mm256_sub_epi32(mul_all_u32x8(negate_u32x8(a_), b_), c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x8 fmaddsub_u32x8(EmuSIMD::u32x8_arg a_, EmuSIMD::u32x8_arg b_, EmuSIMD::u32x8_arg c_)
	{
		return addsub_u32x8(mul_all_u32x8(a_, b_), c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x8 fmsubadd_u32x8(EmuSIMD::u32x8_arg a_, EmuSIMD::u32x8_arg b_, EmuSIMD::u32x8_arg c_)
	{
		return subadd_u32x8(mul_all_u32x8(a_, b_), c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x8 floor_u32x8(EmuSIMD::u32x8_arg to_floor_)
	{
		return to_floor_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x8 ceil_u32x8(EmuSIMD::u32x8_arg to_ceil_)
	{
		return to_ceil_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x8 trunc_u32x8(EmuSIMD::u32x8_arg to_trunc_)
	{
		return to_trunc_;
	}

	template<int RoundingFlag_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x8 round_u32x8(EmuSIMD::u32x8_arg to_round_)
	{
		return to_round_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x8 mod_u32x8(EmuSIMD::u32x8_arg lhs_, EmuSIMD::u32x8_arg rhs_)
	{
#if EMU_CORE_X86_X64_SVML
		return _mm256_rem_epu32(lhs_, rhs_);
#else
		EmuSIMD::u32x8 to_subtract = div_u32x8(lhs_, rhs_);
		to_subtract = mul_all_u32x8(to_subtract, rhs_);
		return sub_u32x8(lhs_, to_subtract);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x8 abs_u32x8(EmuSIMD::u32x8_arg in_)
	{
		return in_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x8 sqrt_u32x8(EmuSIMD::u32x8_arg in_)
	{
		return emulate_fp_u32x8([](EmuSIMD::f32x8_arg in_fp_) { return sqrt_f32x8(in_fp_); }, in_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x8 rsqrt_u32x8(EmuSIMD::u32x8_arg in_)
	{
		return emulate_fp_u32x8([](EmuSIMD::f32x8_arg in_fp_) { return rsqrt_f32x8(in_fp_); }, in_);
	}
#pragma endregion

#pragma region NEAR_COMPARISONS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x8 cmpnear_u32x8(EmuSIMD::u32x8_arg lhs_, EmuSIMD::u32x8_arg rhs_)
	{
		return cmpeq_u32x8(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x8 cmpnear_u32x8(EmuSIMD::u32x8_arg lhs_, EmuSIMD::u32x8_arg rhs_, EmuSIMD::u32x8_arg epsilon)
	{
		return cmple_u32x8(sub_u32x8(lhs_, rhs_), epsilon);
	}
#pragma endregion

#pragma region TRIG
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x8 cos_u32x8(EmuSIMD::u32x8_arg in_)
	{
		return emulate_fp_u32x8([](EmuSIMD::f32x8_arg in_fp_) { return cos_f32x8(in_fp_); }, in_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x8 sin_u32x8(EmuSIMD::u32x8_arg in_)
	{
		return emulate_fp_u32x8([](EmuSIMD::f32x8_arg in_fp_) { return sin_f32x8(in_fp_); }, in_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x8 tan_u32x8(EmuSIMD::u32x8_arg in_)
	{
		return emulate_fp_u32x8([](EmuSIMD::f32x8_arg in_fp_) { return tan_f32x8(in_fp_); }, in_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x8 acos_u32x8(EmuSIMD::u32x8_arg in_)
	{
		return emulate_fp_u32x8([](EmuSIMD::f32x8_arg in_fp_) { return acos_f32x8(in_fp_); }, in_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x8 asin_u32x8(EmuSIMD::u32x8_arg in_)
	{
		return emulate_fp_u32x8([](EmuSIMD::f32x8_arg in_fp_) { return asin_f32x8(in_fp_); }, in_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x8 atan_u32x8(EmuSIMD::u32x8_arg in_)
	{
		return emulate_fp_u32x8([](EmuSIMD::f32x8_arg in_fp_) { return atan_f32x8(in_fp_); }, in_);
	}
#pragma endregion
}

#endif
