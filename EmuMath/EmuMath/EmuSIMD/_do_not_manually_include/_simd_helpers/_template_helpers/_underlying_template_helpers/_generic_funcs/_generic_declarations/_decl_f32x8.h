#ifndef EMU_SIMD_GENERIC_FUNCS_F32X8_DECL_H_INC_
#define EMU_SIMD_GENERIC_FUNCS_F32X8_DECL_H_INC_ 1

#include "../_common_generic_func_helpers.h"
#include "_decl_f32x4.h"

namespace EmuSIMD::Funcs
{
#pragma region SETTERS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 set_f32x8(float e0, float e1, float e2, float e3, float e4, float e5, float e6, float e7);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 setr_f32x8(float e0, float e1, float e2, float e3, float e4, float e5, float e6, float e7);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 set1_f32x8(float all_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 load_f32x8(const float* p_to_load_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 setzero_f32x8();
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 setmasked_f32x8(std::uint8_t bit_mask_);
#pragma endregion

#pragma region STORES
	EMU_SIMD_COMMON_FUNC_SPEC void store_f32x8(float* p_out_, f32x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC float get_first_f32x8(f32x8_arg a_);
#pragma endregion

#pragma region CASTS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 cast_f32x4_f32x8(f32x4_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 cast_f32x8_f32x8(f32x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 cast_f32x16_f32x8(f32x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 cast_f64x2_f32x8(f64x2_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 cast_f64x4_f32x8(f64x4_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 cast_f64x8_f32x8(f64x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 cast_i8x16_f32x8(i8x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 cast_i16x8_f32x8(i16x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 cast_i32x4_f32x8(i32x4_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 cast_i64x2_f32x8(i64x2_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 cast_i8x32_f32x8(i8x32_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 cast_i16x16_f32x8(i16x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 cast_i32x8_f32x8(i32x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 cast_i64x4_f32x8(i64x4_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 cast_i8x64_f32x8(i8x64_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 cast_i16x32_f32x8(i16x32_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 cast_i32x16_f32x8(i32x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 cast_i64x8_f32x8(i64x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 cast_u8x16_f32x8(u8x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 cast_u16x8_f32x8(u16x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 cast_u32x4_f32x8(u32x4_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 cast_u64x2_f32x8(u64x2_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 cast_u8x32_f32x8(u8x32_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 cast_u16x16_f32x8(u16x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 cast_u32x8_f32x8(u32x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 cast_u64x4_f32x8(u64x4_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 cast_u8x64_f32x8(u8x64_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 cast_u16x32_f32x8(u16x32_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 cast_u32x16_f32x8(u32x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 cast_u64x8_f32x8(u64x8_arg a_);
#pragma endregion

#pragma region CONVERSIONS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 cvt_f32x4_f32x8(f32x4_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 cvt_f32x8_f32x8(f32x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 cvt_f32x16_f32x8(f32x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 cvt_f64x2_f32x8(f64x2_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 cvt_f64x4_f32x8(f64x4_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 cvt_f64x8_f32x8(f64x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 cvt_i8x16_f32x8(i8x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 cvt_i16x8_f32x8(i16x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 cvt_i32x4_f32x8(i32x4_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 cvt_i64x2_f32x8(i64x2_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 cvt_i8x32_f32x8(i8x32_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 cvt_i16x16_f32x8(i16x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 cvt_i32x8_f32x8(i32x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 cvt_i64x4_f32x8(i64x4_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 cvt_i8x64_f32x8(i8x64_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 cvt_i16x32_f32x8(i16x32_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 cvt_i32x16_f32x8(i32x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 cvt_i64x8_f32x8(i64x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 cvt_u8x16_f32x8(u8x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 cvt_u16x8_f32x8(u16x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 cvt_u32x4_f32x8(u32x4_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 cvt_u64x2_f32x8(u64x2_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 cvt_u8x32_f32x8(u8x32_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 cvt_u16x16_f32x8(u16x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 cvt_u32x8_f32x8(u32x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 cvt_u64x4_f32x8(u64x4_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 cvt_u8x64_f32x8(u8x64_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 cvt_u16x32_f32x8(u16x32_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 cvt_u32x16_f32x8(u32x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 cvt_u64x8_f32x8(u64x8_arg a_);
#pragma endregion

#pragma region COMPARISONS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 cmpeq_f32x8(EmuSIMD::f32x8_arg lhs_, EmuSIMD::f32x8_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 cmpneq_f32x8(EmuSIMD::f32x8_arg lhs_, EmuSIMD::f32x8_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 cmpgt_f32x8(EmuSIMD::f32x8_arg lhs_, EmuSIMD::f32x8_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 cmplt_f32x8(EmuSIMD::f32x8_arg lhs_, EmuSIMD::f32x8_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 cmpge_f32x8(EmuSIMD::f32x8_arg lhs_, EmuSIMD::f32x8_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 cmple_f32x8(EmuSIMD::f32x8_arg lhs_, EmuSIMD::f32x8_arg rhs_);
#pragma endregion

#pragma region BLENDS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 blendv_f32x8(EmuSIMD::f32x8_arg a_, EmuSIMD::f32x8_arg b_, EmuSIMD::f32x8_arg shuffle_mask_vec_);
#pragma endregion

#pragma region MOVES
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 movehl_f32x8(EmuSIMD::f32x8_arg lhs_, EmuSIMD::f32x8_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 movelh_f32x8(EmuSIMD::f32x8_arg lhs_, EmuSIMD::f32x8_arg rhs_);
#pragma endregion

#pragma region BITWISE_ARITHMETIC
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 and_f32x8(EmuSIMD::f32x8_arg lhs_, EmuSIMD::f32x8_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 or_f32x8(EmuSIMD::f32x8_arg lhs_, EmuSIMD::f32x8_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 xor_f32x8(EmuSIMD::f32x8_arg lhs_, EmuSIMD::f32x8_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 andnot_f32x8(EmuSIMD::f32x8_arg not_lhs_, EmuSIMD::f32x8_arg rhs_);
#pragma endregion

#pragma region MINMAX_FUNCS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 min_f32x8(EmuSIMD::f32x8_arg a_, EmuSIMD::f32x8_arg b_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 horizontal_min_f32x8(EmuSIMD::f32x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 max_f32x8(EmuSIMD::f32x8_arg a_, EmuSIMD::f32x8_arg b_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 horizontal_max_f32x8(EmuSIMD::f32x8_arg a_);
#pragma endregion

#pragma region BASIC_ARITHMETIC
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 mul_all_f32x8(EmuSIMD::f32x8_arg lhs_, EmuSIMD::f32x8_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 add_f32x8(EmuSIMD::f32x8_arg lhs_, EmuSIMD::f32x8_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 sub_f32x8(EmuSIMD::f32x8_arg lhs_, EmuSIMD::f32x8_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 negate_f32x8(EmuSIMD::f32x8_arg to_negate_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 mul_f32x8(EmuSIMD::f32x8_arg lhs_, EmuSIMD::f32x8_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 div_f32x8(EmuSIMD::f32x8_arg lhs_, EmuSIMD::f32x8_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 addsub_f32x8(EmuSIMD::f32x8_arg lhs_, EmuSIMD::f32x8_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 fmadd_f32x8(EmuSIMD::f32x8_arg a_, EmuSIMD::f32x8_arg b_, EmuSIMD::f32x8_arg c_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 fmsub_f32x8(EmuSIMD::f32x8_arg a_, EmuSIMD::f32x8_arg b_, EmuSIMD::f32x8_arg c_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 fnmadd_f32x8(EmuSIMD::f32x8_arg a_, EmuSIMD::f32x8_arg b_, EmuSIMD::f32x8_arg c_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 fnmsub_f32x8(EmuSIMD::f32x8_arg a_, EmuSIMD::f32x8_arg b_, EmuSIMD::f32x8_arg c_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 fmaddsub_f32x8(EmuSIMD::f32x8_arg a_, EmuSIMD::f32x8_arg b_, EmuSIMD::f32x8_arg c_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 fmsubadd_f32x8(EmuSIMD::f32x8_arg a_, EmuSIMD::f32x8_arg b_, EmuSIMD::f32x8_arg c_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 subadd_f32x8(EmuSIMD::f32x8_arg lhs_, EmuSIMD::f32x8_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 floor_f32x8(EmuSIMD::f32x8_arg to_floor_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 ceil_f32x8(EmuSIMD::f32x8_arg to_ceil_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 trunc_f32x8(EmuSIMD::f32x8_arg to_trunc_);

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 mod_f32x8(EmuSIMD::f32x8_arg lhs_, EmuSIMD::f32x8_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 abs_f32x8(EmuSIMD::f32x8_arg in_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 sqrt_f32x8(EmuSIMD::f32x8_arg in_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 rsqrt_f32x8(EmuSIMD::f32x8_arg in_);
#pragma endregion

#pragma region NEAR_COMPARISONS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 cmpnear_f32x8(EmuSIMD::f32x8_arg lhs_, EmuSIMD::f32x8_arg rhs_, EmuSIMD::f32x8_arg epsilon = set1_f32x8(EmuCore::epsilon<float>::get()));
#pragma endregion

#pragma region TRIG
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 cos_f32x8(EmuSIMD::f32x8_arg in_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 sin_f32x8(EmuSIMD::f32x8_arg in_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 tan_f32x8(EmuSIMD::f32x8_arg in_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 acos_f32x8(EmuSIMD::f32x8_arg in_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 asin_f32x8(EmuSIMD::f32x8_arg in_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 atan2_f32x8(EmuSIMD::f32x8_arg y_, EmuSIMD::f32x8_arg x_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 atan_f32x8(EmuSIMD::f32x8_arg in_);
#pragma endregion

	// ^^^ ENDING DECLARATIONS ^^^
	// ---------------------------
	// vvv STARTING  TEMPLATES vvv
#pragma region ROUND_TEMPLATES
	template<int RoundingFlag_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 round_f32x8(EmuSIMD::f32x8_arg to_round_)
	{
		return _mm256_round_ps(to_round_, RoundingFlag_);
	}
#pragma endregion

#pragma region SHUFFLE_TEMPLATES
	template<shuffle_mask_type ShuffleMask>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 shuffle_f32x8(EmuSIMD::f32x8_arg lhs_, EmuSIMD::f32x8_arg rhs_)
	{
		return _mm256_shuffle_ps(lhs_, rhs_, ShuffleMask);
	}

	template<shuffle_mask_type ShuffleMask>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 permute_f32x8(EmuSIMD::f32x8_arg in_)
	{
		return _mm256_permute_ps(in_, ShuffleMask);
	}
#pragma endregion

#pragma region BLEND_TEMPLATES
	template<EmuSIMD::Funcs::blend_mask_type BlendMask>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 blend_f32x8(EmuSIMD::f32x8_arg a_, EmuSIMD::f32x8_arg b_)
	{
		return _mm256_blend_ps(a_, b_, BlendMask);
	}
#pragma endregion

#pragma region EXTRACTION_TEMPLATES
	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 extract_f32x8_lane_f32x8(f32x8_arg a_)
	{
		static_assert(Index_ == 0, "Invalid SIMD lane extraction index: Extracting f32x8 lane from a f32x8 instance; the maximum index is 0 but this index has been exceeded.");
		return a_;
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 extract_f32x16_lane_f32x8(f32x16_arg a_)
	{
		static_assert(Index_ <= 1, "Invalid SIMD lane extraction index: Extracting f32x8 lane from a f32x16 instance; the maximum index is 1 but this index has been exceeded.");
		if constexpr (Index_ == 0)
		{
			return cast_f32x16_f32x8(a_);
		}
		else
		{
			return _mm512_extractf32x8_ps(a_, Index_);
		}
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 extract_f64x4_lane_f32x8(f64x4_arg a_)
	{
		static_assert(Index_ == 0, "Invalid SIMD lane extraction index: Extracting f32x8 lane from a f64x4 instance; the maximum index is 0 but this index has been exceeded.");
		return cast_f64x4_f32x8(a_);
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 extract_f64x8_lane_f32x8(f64x8_arg a_)
	{
		static_assert(Index_ <= 1, "Invalid SIMD lane extraction index: Extracting f32x8 lane from a f64x8 instance; the maximum index is 1 but this index has been exceeded.");
		if constexpr (Index_ == 0)
		{
			return cast_f64x8_f32x8(a_);
		}
		else
		{
			return cast_f64x4_f32x8(_mm512_extractf64x4_pd(a_, Index_));
		}
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 extract_i8x32_lane_f32x8(i8x32_arg a_)
	{
		static_assert(Index_ == 0, "Invalid SIMD lane extraction index: Extracting f32x8 lane from a i8x32 instance; the maximum index is 0 but this index has been exceeded.");
		return cast_i8x32_f32x8(a_);
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 extract_i8x64_lane_f32x8(i8x64_arg a_)
	{
		static_assert(Index_ <= 1, "Invalid SIMD lane extraction index: Extracting f32x8 lane from a i8x64 instance; the maximum index is 1 but this index has been exceeded.");
		if constexpr (Index_ == 0)
		{
			return cast_i8x64_f32x8(a_);
		}
		else
		{
			return cast_i8x32_f32x8(_mm512_extracti32x8_epi32(a_, Index_));
		}
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 extract_i16x16_lane_f32x8(i16x16_arg a_)
	{
		static_assert(Index_ == 0, "Invalid SIMD lane extraction index: Extracting f32x8 lane from a i16x16 instance; the maximum index is 0 but this index has been exceeded.");
		return cast_i16x16_f32x8(a_);
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 extract_i16x32_lane_f32x8(i16x32_arg a_)
	{
		static_assert(Index_ <= 1, "Invalid SIMD lane extraction index: Extracting f32x8 lane from a i16x32 instance; the maximum index is 1 but this index has been exceeded.");
		if constexpr (Index_ == 0)
		{
			return cast_i16x32_f32x8(a_);
		}
		else
		{
			return cast_i16x16_f32x8(_mm512_extracti32x8_epi32(a_, Index_));
		}
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 extract_i32x8_lane_f32x8(i32x8_arg a_)
	{
		static_assert(Index_ == 0, "Invalid SIMD lane extraction index: Extracting f32x8 lane from a i32x8 instance; the maximum index is 0 but this index has been exceeded.");
		return cast_i32x8_f32x8(a_);
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 extract_i32x16_lane_f32x8(i32x16_arg a_)
	{
		static_assert(Index_ <= 1, "Invalid SIMD lane extraction index: Extracting f32x8 lane from a i32x16 instance; the maximum index is 1 but this index has been exceeded.");
		if constexpr (Index_ == 0)
		{
			return cast_i32x16_f32x8(a_);
		}
		else
		{
			return cast_i32x8_f32x8(_mm512_extracti32x8_epi32(a_, Index_));
		}
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 extract_i64x4_lane_f32x8(i64x4_arg a_)
	{
		static_assert(Index_ == 0, "Invalid SIMD lane extraction index: Extracting f32x8 lane from a i64x4 instance; the maximum index is 0 but this index has been exceeded.");
		return cast_i64x4_f32x8(a_);
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 extract_i64x8_lane_f32x8(i64x8_arg a_)
	{
		static_assert(Index_ <= 1, "Invalid SIMD lane extraction index: Extracting f32x8 lane from a i64x8 instance; the maximum index is 1 but this index has been exceeded.");
		if constexpr (Index_ == 0)
		{
			return cast_i64x8_f32x8(a_);
		}
		else
		{
			return cast_i64x4_f32x8(_mm512_extracti32x8_epi32(a_, Index_));
		}
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 extract_u8x32_lane_f32x8(u8x32_arg a_)
	{
		static_assert(Index_ == 0, "Invalid SIMD lane extraction index: Extracting f32x8 lane from a u8x32 instance; the maximum index is 0 but this index has been exceeded.");
		return cast_u8x32_f32x8(a_);
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 extract_u8x64_lane_f32x8(u8x64_arg a_)
	{
		static_assert(Index_ <= 1, "Invalid SIMD lane extraction index: Extracting f32x8 lane from a u8x64 instance; the maximum index is 1 but this index has been exceeded.");
		if constexpr (Index_ == 0)
		{
			return cast_u8x64_f32x8(a_);
		}
		else
		{
			return cast_u8x32_f32x8(_mm512_extracti32x8_epi32(a_, Index_));
		}
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 extract_u16x16_lane_f32x8(u16x16_arg a_)
	{
		static_assert(Index_ == 0, "Invalid SIMD lane extraction index: Extracting f32x8 lane from a u16x16 instance; the maximum index is 0 but this index has been exceeded.");
		return cast_u16x16_f32x8(a_);
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 extract_u16x32_lane_f32x8(u16x32_arg a_)
	{
		static_assert(Index_ <= 1, "Invalid SIMD lane extraction index: Extracting f32x8 lane from a u16x32 instance; the maximum index is 1 but this index has been exceeded.");
		if constexpr (Index_ == 0)
		{
			return cast_u16x32_f32x8(a_);
		}
		else
		{
			return cast_u16x16_f32x8(_mm512_extracti32x8_epi32(a_, Index_));
		}
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 extract_u32x8_lane_f32x8(u32x8_arg a_)
	{
		static_assert(Index_ == 0, "Invalid SIMD lane extraction index: Extracting f32x8 lane from a u32x8 instance; the maximum index is 0 but this index has been exceeded.");
		return cast_u32x8_f32x8(a_);
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 extract_u32x16_lane_f32x8(u32x16_arg a_)
	{
		static_assert(Index_ <= 1, "Invalid SIMD lane extraction index: Extracting f32x8 lane from a u32x16 instance; the maximum index is 1 but this index has been exceeded.");
		if constexpr (Index_ == 0)
		{
			return cast_u32x16_f32x8(a_);
		}
		else
		{
			return cast_u32x8_f32x8(_mm512_extracti32x8_epi32(a_, Index_));
		}
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 extract_u64x4_lane_f32x8(u64x4_arg a_)
	{
		static_assert(Index_ == 0, "Invalid SIMD lane extraction index: Extracting f32x8 lane from a u64x4 instance; the maximum index is 0 but this index has been exceeded.");
		return cast_u64x4_f32x8(a_);
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x8 extract_u64x8_lane_f32x8(u64x8_arg a_)
	{
		static_assert(Index_ <= 1, "Invalid SIMD lane extraction index: Extracting f32x8 lane from a u64x8 instance; the maximum index is 1 but this index has been exceeded.");
		if constexpr (Index_ == 0)
		{
			return cast_u64x8_f32x8(a_);
		}
		else
		{
			return cast_u64x4_f32x8(_mm512_extracti32x8_epi32(a_, Index_));
		}
	}
#pragma endregion

#pragma region GET_TEMPLATES
	template<std::size_t Index_, typename OutT_ = float>
	EMU_SIMD_COMMON_FUNC_SPEC auto extract_element_f32x8(f32x8_arg in_)
		-> typename std::remove_cvref<OutT_>::type
	{
		if constexpr (Index_ == 0)
		{
			return get_first_f32x8(in_);
		}
		else
		{
			if constexpr (Index_ <= 7)
			{
				constexpr int is_hi = static_cast<int>(Index_ >= 4);
				constexpr std::size_t index_in_half = Index_ - (4 * is_hi);
				return EmuSIMD::Funcs::extract_element_f32x4<index_in_half>(EmuSIMD::Funcs::extract_f32x8_lane_f32x4<is_hi>(in_));
			}
			else
			{
				static_assert
				(
					EmuCore::TMP::get_false<std::size_t, Index_>(),
					"Invalid index provided when extracting an element from a f32x8 instance. Valid indices are 0, 1, 2, 3, 4, 5, 6, 7."
				);
			}
		}
	}
#pragma endregion
}

#endif
