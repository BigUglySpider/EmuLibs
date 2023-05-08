#ifndef EMU_SIMD_GENERIC_FUNCS_F64X2_DECL_H_INC_
#define EMU_SIMD_GENERIC_FUNCS_F64X2_DECL_H_INC_ 1

#include "../_common_generic_func_helpers.h"

namespace EmuSIMD::Funcs
{
#pragma region SETTERS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 set_f64x2(double e0, double e1);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 setr_f64x2(double e0, double e1);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 set1_f64x2(double all_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 load_f64x2(const double* p_to_load_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 aligned_load_f64x2(const double* p_to_load_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 setzero_f64x2();
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 setmasked_f64x2(std::uint8_t bit_mask_);
#pragma endregion

#pragma region STORES
	EMU_SIMD_COMMON_FUNC_SPEC void store_f64x2(double* p_out_, f64x2_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC void aligned_store_f64x2(double* p_out_, f64x2_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC double get_first_f64x2(f64x2_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC std::uint8_t movemask_f64x2(f64x2_arg a_);
#pragma endregion

#pragma region CASTS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cast_f32x4_f64x2(f32x4_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cast_f32x8_f64x2(f32x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cast_f32x16_f64x2(f32x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cast_f64x2_f64x2(f64x2_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cast_f64x4_f64x2(f64x4_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cast_f64x8_f64x2(f64x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cast_i8x16_f64x2(i8x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cast_i16x8_f64x2(i16x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cast_i32x4_f64x2(i32x4_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cast_i64x2_f64x2(i64x2_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cast_i8x32_f64x2(i8x32_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cast_i16x16_f64x2(i16x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cast_i32x8_f64x2(i32x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cast_i64x4_f64x2(i64x4_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cast_i8x64_f64x2(i8x64_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cast_i16x32_f64x2(i16x32_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cast_i32x16_f64x2(i32x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cast_i64x8_f64x2(i64x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cast_u8x16_f64x2(u8x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cast_u16x8_f64x2(u16x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cast_u32x4_f64x2(u32x4_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cast_u64x2_f64x2(u64x2_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cast_u8x32_f64x2(u8x32_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cast_u16x16_f64x2(u16x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cast_u32x8_f64x2(u32x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cast_u64x4_f64x2(u64x4_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cast_u8x64_f64x2(u8x64_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cast_u16x32_f64x2(u16x32_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cast_u32x16_f64x2(u32x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cast_u64x8_f64x2(u64x8_arg a_);
#pragma endregion

#pragma region EXTRACTION_TEMPLATES
	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 extract_f32x4_lane_f64x2(f32x4_arg a_)
	{
		static_assert(Index_ == 0, "Invalid SIMD lane extraction index: Extracting f64x2 lane from a f32x4 instance; the maximum index is 0 but this index has been exceeded.");
		return cast_f32x4_f64x2(a_);
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 extract_f32x8_lane_f64x2(f32x8_arg a_)
	{
		static_assert(Index_ <= 1, "Invalid SIMD lane extraction index: Extracting f64x2 lane from a f32x8 instance; the maximum index is 1 but this index has been exceeded.");
		if constexpr (Index_ == 0)
		{
			return cast_f32x8_f64x2(a_);
		}
		else
		{
			return cast_f32x4_f64x2(_mm256_extractf128_ps(a_, Index_));
		}
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 extract_f32x16_lane_f64x2(f32x16_arg a_)
	{
		static_assert(Index_ <= 3, "Invalid SIMD lane extraction index: Extracting f64x2 lane from a f32x16 instance; the maximum index is 3 but this index has been exceeded.");
		if constexpr (Index_ == 0)
		{
			return cast_f32x16_f64x2(a_);
		}
		else
		{
			return cast_f32x4_f64x2(_mm512_extractf32x4_ps(a_, Index_));
		}
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 extract_f64x2_lane_f64x2(f64x2_arg a_)
	{
		static_assert(Index_ == 0, "Invalid SIMD lane extraction index: Extracting f64x2 lane from a f64x2 instance; the maximum index is 0 but this index has been exceeded.");
		return a_;
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 extract_f64x4_lane_f64x2(f64x4_arg a_)
	{
		static_assert(Index_ <= 1, "Invalid SIMD lane extraction index: Extracting f64x2 lane from a f64x4 instance; the maximum index is 1 but this index has been exceeded.");
		if constexpr (Index_ == 0)
		{
			return cast_f64x4_f64x2(a_);
		}
		else
		{
			return _mm256_extractf128_pd(a_, Index_);
		}
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 extract_f64x8_lane_f64x2(f64x8_arg a_)
	{
		static_assert(Index_ <= 3, "Invalid SIMD lane extraction index: Extracting f64x2 lane from a f64x8 instance; the maximum index is 3 but this index has been exceeded.");
		if constexpr (Index_ == 0)
		{
			return cast_f64x8_f64x2(a_);
		}
		else
		{
			return _mm512_extractf64x2_pd(a_, Index_);
		}
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 extract_i8x16_lane_f64x2(i8x16_arg a_)
	{
		static_assert(Index_ == 0, "Invalid SIMD lane extraction index: Extracting f64x2 lane from a i8x16 instance; the maximum index is 0 but this index has been exceeded.");
		return cast_i8x16_f64x2(a_);
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 extract_i8x32_lane_f64x2(i8x32_arg a_)
	{
		static_assert(Index_ <= 1, "Invalid SIMD lane extraction index: Extracting f64x2 lane from a i8x32 instance; the maximum index is 1 but this index has been exceeded.");
		if constexpr (Index_ == 0)
		{
			return cast_i8x32_f64x2(a_);
		}
		else
		{
			return cast_i8x16_f64x2(_mm256_extracti128_si256(a_, Index_));
		}
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 extract_i8x64_lane_f64x2(i8x64_arg a_)
	{
		static_assert(Index_ <= 3, "Invalid SIMD lane extraction index: Extracting f64x2 lane from a i8x64 instance; the maximum index is 3 but this index has been exceeded.");
		if constexpr (Index_ == 0)
		{
			return cast_i8x64_f64x2(a_);
		}
		else
		{
			return cast_i8x16_f64x2(_mm512_extracti32x4_epi32(a_, Index_));
		}
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 extract_i16x8_lane_f64x2(i16x8_arg a_)
	{
		static_assert(Index_ == 0, "Invalid SIMD lane extraction index: Extracting f64x2 lane from a i16x8 instance; the maximum index is 0 but this index has been exceeded.");
		return cast_i16x8_f64x2(a_);
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 extract_i16x16_lane_f64x2(i16x16_arg a_)
	{
		static_assert(Index_ <= 1, "Invalid SIMD lane extraction index: Extracting f64x2 lane from a i16x16 instance; the maximum index is 1 but this index has been exceeded.");
		if constexpr (Index_ == 0)
		{
			return cast_i16x16_f64x2(a_);
		}
		else
		{
			return cast_i16x8_f64x2(_mm256_extracti128_si256(a_, Index_));
		}
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 extract_i16x32_lane_f64x2(i16x32_arg a_)
	{
		static_assert(Index_ <= 3, "Invalid SIMD lane extraction index: Extracting f64x2 lane from a i16x32 instance; the maximum index is 3 but this index has been exceeded.");
		if constexpr (Index_ == 0)
		{
			return cast_i16x32_f64x2(a_);
		}
		else
		{
			return cast_i16x8_f64x2(_mm512_extracti32x4_epi32(a_, Index_));
		}
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 extract_i32x4_lane_f64x2(i32x4_arg a_)
	{
		static_assert(Index_ == 0, "Invalid SIMD lane extraction index: Extracting f64x2 lane from a i32x4 instance; the maximum index is 0 but this index has been exceeded.");
		return cast_i32x4_f64x2(a_);
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 extract_i32x8_lane_f64x2(i32x8_arg a_)
	{
		static_assert(Index_ <= 1, "Invalid SIMD lane extraction index: Extracting f64x2 lane from a i32x8 instance; the maximum index is 1 but this index has been exceeded.");
		if constexpr (Index_ == 0)
		{
			return cast_i32x8_f64x2(a_);
		}
		else
		{
			return cast_i32x4_f64x2(_mm256_extracti128_si256(a_, Index_));
		}
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 extract_i32x16_lane_f64x2(i32x16_arg a_)
	{
		static_assert(Index_ <= 3, "Invalid SIMD lane extraction index: Extracting f64x2 lane from a i32x16 instance; the maximum index is 3 but this index has been exceeded.");
		if constexpr (Index_ == 0)
		{
			return cast_i32x16_f64x2(a_);
		}
		else
		{
			return cast_i32x4_f64x2(_mm512_extracti32x4_epi32(a_, Index_));
		}
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 extract_i64x2_lane_f64x2(i64x2_arg a_)
	{
		static_assert(Index_ == 0, "Invalid SIMD lane extraction index: Extracting f64x2 lane from a i64x2 instance; the maximum index is 0 but this index has been exceeded.");
		return cast_i64x2_f64x2(a_);
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 extract_i64x4_lane_f64x2(i64x4_arg a_)
	{
		static_assert(Index_ <= 1, "Invalid SIMD lane extraction index: Extracting f64x2 lane from a i64x4 instance; the maximum index is 1 but this index has been exceeded.");
		if constexpr (Index_ == 0)
		{
			return cast_i64x4_f64x2(a_);
		}
		else
		{
			return cast_i64x2_f64x2(_mm256_extracti128_si256(a_, Index_));
		}
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 extract_i64x8_lane_f64x2(i64x8_arg a_)
	{
		static_assert(Index_ <= 3, "Invalid SIMD lane extraction index: Extracting f64x2 lane from a i64x8 instance; the maximum index is 3 but this index has been exceeded.");
		if constexpr (Index_ == 0)
		{
			return cast_i64x8_f64x2(a_);
		}
		else
		{
			return cast_i64x2_f64x2(_mm512_extracti32x4_epi32(a_, Index_));
		}
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 extract_u8x16_lane_f64x2(u8x16_arg a_)
	{
		static_assert(Index_ == 0, "Invalid SIMD lane extraction index: Extracting f64x2 lane from a u8x16 instance; the maximum index is 0 but this index has been exceeded.");
		return cast_u8x16_f64x2(a_);
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 extract_u8x32_lane_f64x2(u8x32_arg a_)
	{
		static_assert(Index_ <= 1, "Invalid SIMD lane extraction index: Extracting f64x2 lane from a u8x32 instance; the maximum index is 1 but this index has been exceeded.");
		if constexpr (Index_ == 0)
		{
			return cast_u8x32_f64x2(a_);
		}
		else
		{
			return cast_u8x16_f64x2(_mm256_extracti128_si256(a_, Index_));
		}
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 extract_u8x64_lane_f64x2(u8x64_arg a_)
	{
		static_assert(Index_ <= 3, "Invalid SIMD lane extraction index: Extracting f64x2 lane from a u8x64 instance; the maximum index is 3 but this index has been exceeded.");
		if constexpr (Index_ == 0)
		{
			return cast_u8x64_f64x2(a_);
		}
		else
		{
			return cast_u8x16_f64x2(_mm512_extracti32x4_epi32(a_, Index_));
		}
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 extract_u16x8_lane_f64x2(u16x8_arg a_)
	{
		static_assert(Index_ == 0, "Invalid SIMD lane extraction index: Extracting f64x2 lane from a u16x8 instance; the maximum index is 0 but this index has been exceeded.");
		return cast_u16x8_f64x2(a_);
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 extract_u16x16_lane_f64x2(u16x16_arg a_)
	{
		static_assert(Index_ <= 1, "Invalid SIMD lane extraction index: Extracting f64x2 lane from a u16x16 instance; the maximum index is 1 but this index has been exceeded.");
		if constexpr (Index_ == 0)
		{
			return cast_u16x16_f64x2(a_);
		}
		else
		{
			return cast_u16x8_f64x2(_mm256_extracti128_si256(a_, Index_));
		}
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 extract_u16x32_lane_f64x2(u16x32_arg a_)
	{
		static_assert(Index_ <= 3, "Invalid SIMD lane extraction index: Extracting f64x2 lane from a u16x32 instance; the maximum index is 3 but this index has been exceeded.");
		if constexpr (Index_ == 0)
		{
			return cast_u16x32_f64x2(a_);
		}
		else
		{
			return cast_u16x8_f64x2(_mm512_extracti32x4_epi32(a_, Index_));
		}
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 extract_u32x4_lane_f64x2(u32x4_arg a_)
	{
		static_assert(Index_ == 0, "Invalid SIMD lane extraction index: Extracting f64x2 lane from a u32x4 instance; the maximum index is 0 but this index has been exceeded.");
		return cast_u32x4_f64x2(a_);
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 extract_u32x8_lane_f64x2(u32x8_arg a_)
	{
		static_assert(Index_ <= 1, "Invalid SIMD lane extraction index: Extracting f64x2 lane from a u32x8 instance; the maximum index is 1 but this index has been exceeded.");
		if constexpr (Index_ == 0)
		{
			return cast_u32x8_f64x2(a_);
		}
		else
		{
			return cast_u32x4_f64x2(_mm256_extracti128_si256(a_, Index_));
		}
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 extract_u32x16_lane_f64x2(u32x16_arg a_)
	{
		static_assert(Index_ <= 3, "Invalid SIMD lane extraction index: Extracting f64x2 lane from a u32x16 instance; the maximum index is 3 but this index has been exceeded.");
		if constexpr (Index_ == 0)
		{
			return cast_u32x16_f64x2(a_);
		}
		else
		{
			return cast_u32x4_f64x2(_mm512_extracti32x4_epi32(a_, Index_));
		}
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 extract_u64x2_lane_f64x2(u64x2_arg a_)
	{
		static_assert(Index_ == 0, "Invalid SIMD lane extraction index: Extracting f64x2 lane from a u64x2 instance; the maximum index is 0 but this index has been exceeded.");
		return cast_u64x2_f64x2(a_);
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 extract_u64x4_lane_f64x2(u64x4_arg a_)
	{
		static_assert(Index_ <= 1, "Invalid SIMD lane extraction index: Extracting f64x2 lane from a u64x4 instance; the maximum index is 1 but this index has been exceeded.");
		if constexpr (Index_ == 0)
		{
			return cast_u64x4_f64x2(a_);
		}
		else
		{
			return cast_u64x2_f64x2(_mm256_extracti128_si256(a_, Index_));
		}
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 extract_u64x8_lane_f64x2(u64x8_arg a_)
	{
		static_assert(Index_ <= 3, "Invalid SIMD lane extraction index: Extracting f64x2 lane from a u64x8 instance; the maximum index is 3 but this index has been exceeded.");
		if constexpr (Index_ == 0)
		{
			return cast_u64x8_f64x2(a_);
		}
		else
		{
			return cast_u64x2_f64x2(_mm512_extracti32x4_epi32(a_, Index_));
		}
	}
#pragma endregion

#pragma region CONVERSIONS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cvt_f32x4_f64x2(f32x4_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cvt_f32x8_f64x2(f32x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cvt_f32x16_f64x2(f32x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cvt_f64x2_f64x2(f64x2_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cvt_f64x4_f64x2(f64x4_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cvt_f64x8_f64x2(f64x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cvt_i8x16_f64x2(i8x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cvt_i16x8_f64x2(i16x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cvt_i32x4_f64x2(i32x4_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cvt_i64x2_f64x2(i64x2_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cvt_i8x32_f64x2(i8x32_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cvt_i16x16_f64x2(i16x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cvt_i32x8_f64x2(i32x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cvt_i64x4_f64x2(i64x4_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cvt_i8x64_f64x2(i8x64_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cvt_i16x32_f64x2(i16x32_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cvt_i32x16_f64x2(i32x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cvt_i64x8_f64x2(i64x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cvt_u8x16_f64x2(u8x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cvt_u16x8_f64x2(u16x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cvt_u32x4_f64x2(u32x4_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cvt_u64x2_f64x2(u64x2_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cvt_u8x32_f64x2(u8x32_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cvt_u16x16_f64x2(u16x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cvt_u32x8_f64x2(u32x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cvt_u64x4_f64x2(u64x4_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cvt_u8x64_f64x2(u8x64_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cvt_u16x32_f64x2(u16x32_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cvt_u32x16_f64x2(u32x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cvt_u64x8_f64x2(u64x8_arg a_);
#pragma endregion

#pragma region COMPARISONS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cmpeq_f64x2(EmuSIMD::f64x2_arg lhs_, EmuSIMD::f64x2_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cmpneq_f64x2(EmuSIMD::f64x2_arg lhs_, EmuSIMD::f64x2_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cmpgt_f64x2(EmuSIMD::f64x2_arg lhs_, EmuSIMD::f64x2_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cmplt_f64x2(EmuSIMD::f64x2_arg lhs_, EmuSIMD::f64x2_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cmpge_f64x2(EmuSIMD::f64x2_arg lhs_, EmuSIMD::f64x2_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cmple_f64x2(EmuSIMD::f64x2_arg lhs_, EmuSIMD::f64x2_arg rhs_);
#pragma endregion

#pragma region BLENDS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 blendv_f64x2(EmuSIMD::f64x2_arg a_, EmuSIMD::f64x2_arg b_, EmuSIMD::f64x2_arg shuffle_mask_vec_);
#pragma endregion

#pragma region MOVES
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 movehl_f64x2(EmuSIMD::f64x2_arg lhs_, EmuSIMD::f64x2_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 movelh_f64x2(EmuSIMD::f64x2_arg lhs_, EmuSIMD::f64x2_arg rhs_);
#pragma endregion

#pragma region BITWISE_ARITHMETIC
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 and_f64x2(EmuSIMD::f64x2_arg lhs_, EmuSIMD::f64x2_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 or_f64x2(EmuSIMD::f64x2_arg lhs_, EmuSIMD::f64x2_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 xor_f64x2(EmuSIMD::f64x2_arg lhs_, EmuSIMD::f64x2_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 andnot_f64x2(EmuSIMD::f64x2_arg not_lhs_, EmuSIMD::f64x2_arg rhs_);
	template<std::int32_t NumShifts_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 shift_left_f64x2(EmuSIMD::f64x2_arg lhs_);
	template<std::int32_t NumShifts_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 shift_right_arithmetic_f64x2(EmuSIMD::f64x2_arg lhs_);
	template<std::int32_t NumShifts_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 shift_right_logical_f64x2(EmuSIMD::f64x2_arg lhs_);
#pragma endregion

#pragma region MINMAX_FUNCS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 min_f64x2(EmuSIMD::f64x2_arg a_, EmuSIMD::f64x2_arg b_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 horizontal_min_f64x2(EmuSIMD::f64x2_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 max_f64x2(EmuSIMD::f64x2_arg a_, EmuSIMD::f64x2_arg b_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 horizontal_max_f64x2(EmuSIMD::f64x2_arg a_);
#pragma endregion

#pragma region BASIC_ARITHMETIC
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 mul_all_f64x2(EmuSIMD::f64x2_arg lhs_, EmuSIMD::f64x2_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 negate_f64x2(EmuSIMD::f64x2_arg to_negate_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 add_f64x2(EmuSIMD::f64x2_arg lhs_, EmuSIMD::f64x2_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 sub_f64x2(EmuSIMD::f64x2_arg lhs_, EmuSIMD::f64x2_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 mul_f64x2(EmuSIMD::f64x2_arg lhs_, EmuSIMD::f64x2_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 div_f64x2(EmuSIMD::f64x2_arg lhs_, EmuSIMD::f64x2_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 addsub_f64x2(EmuSIMD::f64x2_arg lhs_, EmuSIMD::f64x2_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 fmadd_f64x2(EmuSIMD::f64x2_arg a_, EmuSIMD::f64x2_arg b_, EmuSIMD::f64x2_arg c_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 fmsub_f64x2(EmuSIMD::f64x2_arg a_, EmuSIMD::f64x2_arg b_, EmuSIMD::f64x2_arg c_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 fnmadd_f64x2(EmuSIMD::f64x2_arg a_, EmuSIMD::f64x2_arg b_, EmuSIMD::f64x2_arg c_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 fnmsub_f64x2(EmuSIMD::f64x2_arg a_, EmuSIMD::f64x2_arg b_, EmuSIMD::f64x2_arg c_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 fmaddsub_f64x2(EmuSIMD::f64x2_arg a_, EmuSIMD::f64x2_arg b_, EmuSIMD::f64x2_arg c_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 fmsubadd_f64x2(EmuSIMD::f64x2_arg a_, EmuSIMD::f64x2_arg b_, EmuSIMD::f64x2_arg c_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 subadd_f64x2(EmuSIMD::f64x2_arg lhs_, EmuSIMD::f64x2_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 floor_f64x2(EmuSIMD::f64x2_arg to_floor_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 ceil_f64x2(EmuSIMD::f64x2_arg to_ceil_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 trunc_f64x2(EmuSIMD::f64x2_arg to_trunc_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 mod_f64x2(EmuSIMD::f64x2_arg lhs_, EmuSIMD::f64x2_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 abs_f64x2(EmuSIMD::f64x2_arg in_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2_arg sqrt_f64x2(EmuSIMD::f64x2_arg in_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 rsqrt_f64x2(EmuSIMD::f64x2_arg in_);
#pragma endregion

#pragma region NEAR_COMPARISONS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cmpnear_f64x2(EmuSIMD::f64x2_arg lhs_, EmuSIMD::f64x2_arg rhs_, EmuSIMD::f64x2_arg epsilon = set1_f64x2(EmuCore::epsilon<double>::get()));
#pragma endregion

#pragma region TRIG
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 cos_f64x2(EmuSIMD::f64x2_arg in_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 sin_f64x2(EmuSIMD::f64x2_arg in_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 tan_f64x2(EmuSIMD::f64x2_arg in_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 acos_f64x2(EmuSIMD::f64x2_arg in_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 asin_f64x2(EmuSIMD::f64x2_arg in_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 atan2_f64x2(EmuSIMD::f64x2_arg y_, EmuSIMD::f64x2_arg x_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 atan_f64x2(EmuSIMD::f64x2_arg in_);
#pragma endregion

#pragma region ROUNDING_TEMPLATES
	template<int RoundingFlag_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 round_f64x2(EmuSIMD::f64x2_arg to_round_)
	{
		return _mm_round_pd(to_round_, RoundingFlag_);
	}
#pragma endregion

#pragma region SHUFFLE_TEMPLATES
	template<EmuSIMD::Funcs::shuffle_mask_type ShuffleMask>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 shuffle_f64x2(EmuSIMD::f64x2_arg lhs_, EmuSIMD::f64x2_arg rhs_)
	{
		return _mm_shuffle_pd(lhs_, rhs_, ShuffleMask);
	}

	template<EmuSIMD::Funcs::shuffle_mask_type ShuffleMask>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 permute_f64x2(EmuSIMD::f64x2_arg in_)
	{
		return _mm_permute_pd(in_, ShuffleMask);
	}
#pragma endregion

#pragma region BLEND_TEMPLATES
	template<EmuSIMD::Funcs::blend_mask_type BlendMask>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x2 blend_f64x2(EmuSIMD::f64x2_arg a_, EmuSIMD::f64x2_arg b_)
	{
		return _mm_blend_pd(a_, b_, BlendMask);
	}
#pragma endregion

#pragma region GET_TEMPLATES
	template<std::size_t Index_, typename OutT_ = double>
	EMU_SIMD_COMMON_FUNC_SPEC auto extract_element_f64x2(f64x2_arg in_)
		-> typename std::remove_cvref<OutT_>::type
	{
		if constexpr (Index_ == 0)
		{
			return static_cast<typename std::remove_cvref<OutT_>::type>(EmuSIMD::Funcs::get_first_f64x2(in_));
		}
		else
		{
			if constexpr (Index_ <= 1)
			{
#if EMU_SIMD_USE_128_REGISTERS
				return static_cast<typename std::remove_cvref<OutT_>::type>(EmuSIMD::Funcs::get_first_f64x2(EmuSIMD::Funcs::movehl_f64x2(in_, in_)));
#else
				return EmuSIMD::_underlying_impl::retrieve_emulated_single_lane_simd_element<OutT_, Index_, false>(in_);
#endif
			}
			else
			{
				static_assert
				(
					EmuCore::TMP::get_false<std::size_t, Index_>(),
					"Invalid index provided when extracting an element from a f64x2 instance. Valid indices are 0, 1."
				);
			}
		}
	}
#pragma endregion
}

#endif
