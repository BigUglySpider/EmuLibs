#ifndef EMU_SIMD_GENERIC_FUNCS_F32X4_DECL_H_INC_
#define EMU_SIMD_GENERIC_FUNCS_F32X4_DECL_H_INC_ 1

#include "../_common_generic_func_helpers.h"

namespace EmuSIMD::Funcs
{
#pragma region SETTERS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 set_f32x4(float e0, float e1, float e2, float e3);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 setr_f32x4(float e0, float e1, float e2, float e3);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 set1_f32x4(float all_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 load_f32x4(const float* p_to_load_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 aligned_load_f32x4(const float* p_to_load_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 setzero_f32x4();
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 setmasked_f32x4(std::uint8_t bit_mask_);
#pragma endregion

#pragma region STORES
	EMU_SIMD_COMMON_FUNC_SPEC void store_f32x4(float* p_out_, f32x4_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC void aligned_store_f32x4(float* p_out_, f32x4_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC float get_first_f32x4(f32x4_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC std::uint8_t movemask_f32x4(f32x4_arg a_);
#pragma endregion

#pragma region CASTS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cast_f32x4_f32x4(f32x4_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cast_f32x8_f32x4(f32x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cast_f32x16_f32x4(f32x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cast_f64x2_f32x4(f64x2_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cast_f64x4_f32x4(f64x4_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cast_f64x8_f32x4(f64x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cast_i8x16_f32x4(i8x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cast_i16x8_f32x4(i16x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cast_i32x4_f32x4(i32x4_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cast_i64x2_f32x4(i64x2_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cast_i8x32_f32x4(i8x32_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cast_i16x16_f32x4(i16x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cast_i32x8_f32x4(i32x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cast_i64x4_f32x4(i64x4_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cast_i8x64_f32x4(i8x64_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cast_i16x32_f32x4(i16x32_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cast_i32x16_f32x4(i32x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cast_i64x8_f32x4(i64x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cast_u8x16_f32x4(u8x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cast_u16x8_f32x4(u16x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cast_u32x4_f32x4(u32x4_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cast_u64x2_f32x4(u64x2_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cast_u8x32_f32x4(u8x32_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cast_u16x16_f32x4(u16x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cast_u32x8_f32x4(u32x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cast_u64x4_f32x4(u64x4_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cast_u8x64_f32x4(u8x64_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cast_u16x32_f32x4(u16x32_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cast_u32x16_f32x4(u32x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cast_u64x8_f32x4(u64x8_arg a_);
#pragma endregion

#pragma region CONVERSIONS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cvt_f32x4_f32x4(f32x4_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cvt_f32x8_f32x4(f32x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cvt_f32x16_f32x4(f32x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cvt_f64x2_f32x4(f64x2_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cvt_f64x4_f32x4(f64x4_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cvt_f64x8_f32x4(f64x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cvt_i8x16_f32x4(i8x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cvt_i16x8_f32x4(i16x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cvt_i32x4_f32x4(i32x4_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cvt_i64x2_f32x4(i64x2_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cvt_i8x32_f32x4(i8x32_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cvt_i16x16_f32x4(i16x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cvt_i32x8_f32x4(i32x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cvt_i64x4_f32x4(i64x4_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cvt_i8x64_f32x4(i8x64_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cvt_i16x32_f32x4(i16x32_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cvt_i32x16_f32x4(i32x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cvt_i64x8_f32x4(i64x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cvt_u8x16_f32x4(u8x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cvt_u16x8_f32x4(u16x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cvt_u32x4_f32x4(u32x4_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cvt_u64x2_f32x4(u64x2_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cvt_u8x32_f32x4(u8x32_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cvt_u16x16_f32x4(u16x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cvt_u32x8_f32x4(u32x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cvt_u64x4_f32x4(u64x4_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cvt_u8x64_f32x4(u8x64_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cvt_u16x32_f32x4(u16x32_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cvt_u32x16_f32x4(u32x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cvt_u64x8_f32x4(u64x8_arg a_);
#pragma endregion

#pragma region COMPARISONS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cmpeq_f32x4(EmuSIMD::f32x4_arg lhs_, EmuSIMD::f32x4_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cmpneq_f32x4(EmuSIMD::f32x4_arg lhs_, EmuSIMD::f32x4_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cmpgt_f32x4(EmuSIMD::f32x4_arg lhs_, EmuSIMD::f32x4_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cmplt_f32x4(EmuSIMD::f32x4_arg lhs_, EmuSIMD::f32x4_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cmpge_f32x4(EmuSIMD::f32x4_arg lhs_, EmuSIMD::f32x4_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cmple_f32x4(EmuSIMD::f32x4_arg lhs_, EmuSIMD::f32x4_arg rhs_);
#pragma endregion

#pragma region BLENDS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 blendv_f32x4(EmuSIMD::f32x4_arg a_, EmuSIMD::f32x4_arg b_, EmuSIMD::f32x4_arg shuffle_mask_vec_);
#pragma endregion

#pragma region MOVES
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 movehl_f32x4(EmuSIMD::f32x4_arg lhs_, EmuSIMD::f32x4_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 movelh_f32x4(EmuSIMD::f32x4_arg lhs_, EmuSIMD::f32x4_arg rhs_);
#pragma endregion

#pragma region BITWISE_ARITHMETIC
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 and_f32x4(EmuSIMD::f32x4_arg lhs_, EmuSIMD::f32x4_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 or_f32x4(EmuSIMD::f32x4_arg lhs_, EmuSIMD::f32x4_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 xor_f32x4(EmuSIMD::f32x4_arg lhs_, EmuSIMD::f32x4_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 andnot_f32x4(EmuSIMD::f32x4_arg not_lhs_, EmuSIMD::f32x4_arg rhs_);
	template<std::int32_t NumShifts_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 shift_left_f32x4(EmuSIMD::f32x4_arg lhs_);
	template<std::int32_t NumShifts_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 shift_right_arithmetic_f32x4(EmuSIMD::f32x4_arg lhs_);
	template<std::int32_t NumShifts_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 shift_right_logical_f32x4(EmuSIMD::f32x4_arg lhs_);
#pragma endregion

#pragma region MINMAX_FUNCS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 min_f32x4(EmuSIMD::f32x4_arg a_, EmuSIMD::f32x4_arg b_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 horizontal_min_f32x4(EmuSIMD::f32x4_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 max_f32x4(EmuSIMD::f32x4_arg a_, EmuSIMD::f32x4_arg b_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 horizontal_max_f32x4(EmuSIMD::f32x4_arg a_);
#pragma endregion

#pragma region BASIC_ARITHMETIC
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 mul_all_f32x4(EmuSIMD::f32x4_arg lhs_, EmuSIMD::f32x4_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 add_f32x4(EmuSIMD::f32x4_arg lhs_, EmuSIMD::f32x4_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 sub_f32x4(EmuSIMD::f32x4_arg lhs_, EmuSIMD::f32x4_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 negate_f32x4(EmuSIMD::f32x4_arg to_negate_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 div_f32x4(EmuSIMD::f32x4_arg lhs_, EmuSIMD::f32x4_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 addsub_f32x4(EmuSIMD::f32x4_arg lhs_, EmuSIMD::f32x4_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 fmadd_f32x4(EmuSIMD::f32x4_arg a_, EmuSIMD::f32x4_arg b_, EmuSIMD::f32x4_arg c_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 fmsub_f32x4(EmuSIMD::f32x4_arg a_, EmuSIMD::f32x4_arg b_, EmuSIMD::f32x4_arg c_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 fnmadd_f32x4(EmuSIMD::f32x4_arg a_, EmuSIMD::f32x4_arg b_, EmuSIMD::f32x4_arg c_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 fnmsub_f32x4(EmuSIMD::f32x4_arg a_, EmuSIMD::f32x4_arg b_, EmuSIMD::f32x4_arg c_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 fmaddsub_f32x4(EmuSIMD::f32x4_arg a_, EmuSIMD::f32x4_arg b_, EmuSIMD::f32x4_arg c_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 fmsubadd_f32x4(EmuSIMD::f32x4_arg a_, EmuSIMD::f32x4_arg b_, EmuSIMD::f32x4_arg c_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 subadd_f32x4(EmuSIMD::f32x4_arg lhs_, EmuSIMD::f32x4_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 floor_f32x4(EmuSIMD::f32x4_arg to_floor_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 ceil_f32x4(EmuSIMD::f32x4_arg to_ceil_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 trunc_f32x4(EmuSIMD::f32x4_arg to_trunc_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 mod_f32x4(EmuSIMD::f32x4_arg lhs_, EmuSIMD::f32x4_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 abs_f32x4(EmuSIMD::f32x4_arg in_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 sqrt_f32x4(EmuSIMD::f32x4_arg in_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 rsqrt_f32x4(EmuSIMD::f32x4_arg in_);
#pragma endregion

#pragma region NEAR_COMPARISONS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cmpnear_f32x4(EmuSIMD::f32x4_arg lhs_, EmuSIMD::f32x4_arg rhs_, EmuSIMD::f32x4_arg epsilon = set1_f32x4(EmuCore::epsilon<float>::get()));
#pragma endregion

#pragma region TRIG
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cos_f32x4(EmuSIMD::f32x4_arg in_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 sin_f32x4(EmuSIMD::f32x4_arg in_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 tan_f32x4(EmuSIMD::f32x4_arg in_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 acos_f32x4(EmuSIMD::f32x4_arg in_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 asin_f32x4(EmuSIMD::f32x4_arg in_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 atan2_f32x4(EmuSIMD::f32x4_arg y_, EmuSIMD::f32x4_arg x_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 atan_f32x4(EmuSIMD::f32x4_arg in_);
#pragma endregion

	// ^^^ ENDING DECLARATIONS ^^^
	// ---------------------------
	// vvv STARTING  TEMPLATES vvv
#pragma region ROUND_TEMPLATES
	template<int RoundingFlag_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 round_f32x4(EmuSIMD::f32x4_arg to_round_)
	{
#if EMU_SIMD_USE_128_REGISTERS
		return _mm_round_ps(to_round_, RoundingFlag_);
#else
		using EmuSIMD::_underlying_impl::emulate_simd_basic;
		using index_sequence = std::make_index_sequence<4>;
		return emulate_simd_basic(EmuSIMD::_underlying_impl::round_with_flag_emulator_func<RoundingFlag_, float>(), to_round_, index_sequence());
#endif
	}
#pragma endregion

#pragma region SHUFFLE_TEMPLATES
	template<EmuSIMD::Funcs::shuffle_mask_type ShuffleMask_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 shuffle_f32x4(EmuSIMD::f32x4_arg lhs_, EmuSIMD::f32x4_arg rhs_)
	{
#if EMU_SIMD_USE_128_REGISTERS
		return _mm_shuffle_ps(lhs_, rhs_, ShuffleMask_);
#else
		return EmuSIMD::_underlying_impl::_emulate_single_lane_shuffle<ShuffleMask_, 2>(lhs_, rhs_, std::make_index_sequence<4>());
#endif
	}

	template<EmuSIMD::Funcs::shuffle_mask_type ShuffleMask_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 permute_f32x4(EmuSIMD::f32x4_arg in_)
	{
#if EMU_SIMD_USE_128_REGISTERS
		return _mm_permute_ps(in_, ShuffleMask_);
#else
		return EmuSIMD::_underlying_impl::_emulate_single_lane_permute<ShuffleMask_, 2>(in_, std::make_index_sequence<4>());
#endif
	}
#pragma endregion

#pragma region BLEND_TEMPLATES
	template<EmuSIMD::Funcs::blend_mask_type BlendMask_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 blend_f32x4(EmuSIMD::f32x4_arg a_, EmuSIMD::f32x4_arg b_)
	{
#if EMU_SIMD_USE_128_REGISTERS
		return _mm_blend_ps(a_, b_, BlendMask_);
#else
		return EmuSIMD::_underlying_impl::emulate_single_lane_blend_with_mask<BlendMask_>(a_, b_, std::make_index_sequence<4>());
#endif
	}
#pragma endregion

#pragma region EXTRACTION_TEMPLATES
	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 extract_f32x4_lane_f32x4(f32x4_arg a_)
	{
		static_assert(Index_ == 0, "Invalid SIMD lane extraction index: Extracting f32x4 lane from a f32x4 instance; the maximum index is 0 but this index has been exceeded.");
		return a_;
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 extract_f32x8_lane_f32x4(f32x8_arg a_)
	{
		static_assert(Index_ <= 1, "Invalid SIMD lane extraction index: Extracting f32x4 lane from a f32x8 instance; the maximum index is 1 but this index has been exceeded.");
		if constexpr (Index_ == 0)
		{
			return cast_f32x8_f32x4(a_);
		}
		else
		{
#if EMU_SIMD_USE_256_REGISTERS
			return _mm256_extractf128_ps(a_, Index_);
#else
			return EmuSIMD::_underlying_impl::emulate_extraction<f32x4, 128, Index_>(a_);
#endif
		}
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 extract_f32x16_lane_f32x4(f32x16_arg a_)
	{
		static_assert(Index_ <= 3, "Invalid SIMD lane extraction index: Extracting f32x4 lane from a f32x16 instance; the maximum index is 3 but this index has been exceeded.");
		if constexpr (Index_ == 0)
		{
			return cast_f32x16_f32x4(a_);
		}
		else
		{
#if EMU_SIMD_USE_512_REGISTERS
			return _mm512_extractf32x4_ps(a_, Index_);
#else
			return EmuSIMD::_underlying_impl::emulate_extraction<f32x4, 128, Index_>(a_);
#endif
		}
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 extract_f64x2_lane_f32x4(f64x2_arg a_)
	{
		static_assert(Index_ == 0, "Invalid SIMD lane extraction index: Extracting f32x4 lane from a f64x2 instance; the maximum index is 0 but this index has been exceeded.");
		return cast_f64x2_f32x4(a_);
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 extract_f64x4_lane_f32x4(f64x4_arg a_)
	{
		static_assert(Index_ <= 1, "Invalid SIMD lane extraction index: Extracting f32x4 lane from a f64x4 instance; the maximum index is 1 but this index has been exceeded.");
		if constexpr (Index_ == 0)
		{
			return cast_f64x4_f32x4(a_);
		}
		else
		{
#if EMU_SIMD_USE_256_REGISTERS
			return cast_f64x2_f32x4(_mm256_extractf128_pd(a_, Index_));
#else
			return EmuSIMD::_underlying_impl::emulate_extraction<f32x4, 128, Index_>(a_);
#endif
		}
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 extract_f64x8_lane_f32x4(f64x8_arg a_)
	{
		static_assert(Index_ <= 3, "Invalid SIMD lane extraction index: Extracting f32x4 lane from a f64x8 instance; the maximum index is 3 but this index has been exceeded.");
		if constexpr (Index_ == 0)
		{
			return cast_f64x8_f32x4(a_);
		}
		else
		{
#if EMU_SIMD_USE_512_REGISTERS
			return cast_f64x2_f32x4(_mm512_extractf64x2_pd(a_, Index_));
#else
			return EmuSIMD::_underlying_impl::emulate_extraction<f32x4, 128, Index_>(a_);
#endif
		}
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 extract_i8x16_lane_f32x4(i8x16_arg a_)
	{
		static_assert(Index_ == 0, "Invalid SIMD lane extraction index: Extracting f32x4 lane from a i8x16 instance; the maximum index is 0 but this index has been exceeded.");
		return cast_i8x16_f32x4(a_);
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 extract_i8x32_lane_f32x4(i8x32_arg a_)
	{
		static_assert(Index_ <= 1, "Invalid SIMD lane extraction index: Extracting f32x4 lane from a i8x32 instance; the maximum index is 1 but this index has been exceeded.");
		if constexpr (Index_ == 0)
		{
			return cast_i8x32_f32x4(a_);
		}
		else
		{
#if EMU_SIMD_USE_256_REGISTERS
			return cast_i8x16_f32x4(_mm256_extracti128_si256(a_, Index_));
#else
			return EmuSIMD::_underlying_impl::emulate_extraction<f32x4, 128, Index_>(a_);
#endif
		}
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 extract_i8x64_lane_f32x4(i8x64_arg a_)
	{
		static_assert(Index_ <= 3, "Invalid SIMD lane extraction index: Extracting f32x4 lane from a i8x64 instance; the maximum index is 3 but this index has been exceeded.");
		if constexpr (Index_ == 0)
		{
			return cast_i8x64_f32x4(a_);
		}
		else
		{
#if EMU_SIMD_USE_512_REGISTERS
			return cast_i8x16_f32x4(_mm512_extracti32x4_epi32(a_, Index_));
#else
			return EmuSIMD::_underlying_impl::emulate_extraction<f32x4, 128, Index_>(a_);
#endif
		}
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 extract_i16x8_lane_f32x4(i16x8_arg a_)
	{
		static_assert(Index_ == 0, "Invalid SIMD lane extraction index: Extracting f32x4 lane from a i16x8 instance; the maximum index is 0 but this index has been exceeded.");
		return cast_i16x8_f32x4(a_);
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 extract_i16x16_lane_f32x4(i16x16_arg a_)
	{
		static_assert(Index_ <= 1, "Invalid SIMD lane extraction index: Extracting f32x4 lane from a i16x16 instance; the maximum index is 1 but this index has been exceeded.");
		if constexpr (Index_ == 0)
		{
			return cast_i16x16_f32x4(a_);
		}
		else
		{
#if EMU_SIMD_USE_256_REGISTERS
			return cast_i16x8_f32x4(_mm256_extracti128_si256(a_, Index_));
#else
			return EmuSIMD::_underlying_impl::emulate_extraction<f32x4, 128, Index_>(a_);
#endif
		}
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 extract_i16x32_lane_f32x4(i16x32_arg a_)
	{
		static_assert(Index_ <= 3, "Invalid SIMD lane extraction index: Extracting f32x4 lane from a i16x32 instance; the maximum index is 3 but this index has been exceeded.");
		if constexpr (Index_ == 0)
		{
			return cast_i16x32_f32x4(a_);
		}
		else
		{
#if EMU_SIMD_USE_512_REGISTERS
			return cast_i16x8_f32x4(_mm512_extracti32x4_epi32(a_, Index_));
#else
			return EmuSIMD::_underlying_impl::emulate_extraction<f32x4, 128, Index_>(a_);
#endif
		}
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 extract_i32x4_lane_f32x4(i32x4_arg a_)
	{
		static_assert(Index_ == 0, "Invalid SIMD lane extraction index: Extracting f32x4 lane from a i32x4 instance; the maximum index is 0 but this index has been exceeded.");
		return cast_i32x4_f32x4(a_);
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 extract_i32x8_lane_f32x4(i32x8_arg a_)
	{
		static_assert(Index_ <= 1, "Invalid SIMD lane extraction index: Extracting f32x4 lane from a i32x8 instance; the maximum index is 1 but this index has been exceeded.");
		if constexpr (Index_ == 0)
		{
			return cast_i32x8_f32x4(a_);
		}
		else
		{
#if EMU_SIMD_USE_256_REGISTERS
			return cast_i32x4_f32x4(_mm256_extracti128_si256(a_, Index_));
#else
			return EmuSIMD::_underlying_impl::emulate_extraction<f32x4, 128, Index_>(a_);
#endif
		}
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 extract_i32x16_lane_f32x4(i32x16_arg a_)
	{
		static_assert(Index_ <= 3, "Invalid SIMD lane extraction index: Extracting f32x4 lane from a i32x16 instance; the maximum index is 3 but this index has been exceeded.");
		if constexpr (Index_ == 0)
		{
			return cast_i32x16_f32x4(a_);
		}
		else
		{
#if EMU_SIMD_USE_512_REGISTERS
			return cast_i32x4_f32x4(_mm512_extracti32x4_epi32(a_, Index_));
#else
			return EmuSIMD::_underlying_impl::emulate_extraction<f32x4, 128, Index_>(a_);
#endif
		}
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 extract_i64x2_lane_f32x4(i64x2_arg a_)
	{
		static_assert(Index_ == 0, "Invalid SIMD lane extraction index: Extracting f32x4 lane from a i64x2 instance; the maximum index is 0 but this index has been exceeded.");
		return cast_i64x2_f32x4(a_);
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 extract_i64x4_lane_f32x4(i64x4_arg a_)
	{
		static_assert(Index_ <= 1, "Invalid SIMD lane extraction index: Extracting f32x4 lane from a i64x4 instance; the maximum index is 1 but this index has been exceeded.");
		if constexpr (Index_ == 0)
		{
			return cast_i64x4_f32x4(a_);
		}
		else
		{
#if EMU_SIMD_USE_256_REGISTERS
			return cast_i64x2_f32x4(_mm256_extracti128_si256(a_, Index_));
#else
			return EmuSIMD::_underlying_impl::emulate_extraction<f32x4, 128, Index_>(a_);
#endif
		}
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 extract_i64x8_lane_f32x4(i64x8_arg a_)
	{
		static_assert(Index_ <= 3, "Invalid SIMD lane extraction index: Extracting f32x4 lane from a i64x8 instance; the maximum index is 3 but this index has been exceeded.");
		if constexpr (Index_ == 0)
		{
			return cast_i64x8_f32x4(a_);
		}
		else
		{
#if EMU_SIMD_USE_512_REGISTERS
			return cast_i64x2_f32x4(_mm512_extracti32x4_epi32(a_, Index_));
#else
			return EmuSIMD::_underlying_impl::emulate_extraction<f32x4, 128, Index_>(a_);
#endif
		}
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 extract_u8x16_lane_f32x4(u8x16_arg a_)
	{
		static_assert(Index_ == 0, "Invalid SIMD lane extraction index: Extracting f32x4 lane from a u8x16 instance; the maximum index is 0 but this index has been exceeded.");
		return cast_u8x16_f32x4(a_);
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 extract_u8x32_lane_f32x4(u8x32_arg a_)
	{
		static_assert(Index_ <= 1, "Invalid SIMD lane extraction index: Extracting f32x4 lane from a u8x32 instance; the maximum index is 1 but this index has been exceeded.");
		if constexpr (Index_ == 0)
		{
			return cast_u8x32_f32x4(a_);
		}
		else
		{
#if EMU_SIMD_USE_256_REGISTERS
			return cast_u8x16_f32x4(_mm256_extracti128_si256(a_, Index_));
#else
			return EmuSIMD::_underlying_impl::emulate_extraction<f32x4, 128, Index_>(a_);
#endif
		}
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 extract_u8x64_lane_f32x4(u8x64_arg a_)
	{
		static_assert(Index_ <= 3, "Invalid SIMD lane extraction index: Extracting f32x4 lane from a u8x64 instance; the maximum index is 3 but this index has been exceeded.");
		if constexpr (Index_ == 0)
		{
			return cast_u8x64_f32x4(a_);
		}
		else
		{
#if EMU_SIMD_USE_512_REGISTERS
			return cast_u8x16_f32x4(_mm512_extracti32x4_epi32(a_, Index_));
#else
			return EmuSIMD::_underlying_impl::emulate_extraction<f32x4, 128, Index_>(a_);
#endif
		}
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 extract_u16x8_lane_f32x4(u16x8_arg a_)
	{
		static_assert(Index_ == 0, "Invalid SIMD lane extraction index: Extracting f32x4 lane from a u16x8 instance; the maximum index is 0 but this index has been exceeded.");
		return cast_u16x8_f32x4(a_);
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 extract_u16x16_lane_f32x4(u16x16_arg a_)
	{
		static_assert(Index_ <= 1, "Invalid SIMD lane extraction index: Extracting f32x4 lane from a u16x16 instance; the maximum index is 1 but this index has been exceeded.");
		if constexpr (Index_ == 0)
		{
			return cast_u16x16_f32x4(a_);
		}
		else
		{
#if EMU_SIMD_USE_256_REGISTERS
			return cast_u16x8_f32x4(_mm256_extracti128_si256(a_, Index_));
#else
			return EmuSIMD::_underlying_impl::emulate_extraction<f32x4, 128, Index_>(a_);
#endif
		}
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 extract_u16x32_lane_f32x4(u16x32_arg a_)
	{
		static_assert(Index_ <= 3, "Invalid SIMD lane extraction index: Extracting f32x4 lane from a u16x32 instance; the maximum index is 3 but this index has been exceeded.");
		if constexpr (Index_ == 0)
		{
			return cast_u16x32_f32x4(a_);
		}
		else
		{
#if EMU_SIMD_USE_512_REGISTERS
			return cast_u16x8_f32x4(_mm512_extracti32x4_epi32(a_, Index_));
#else
			return EmuSIMD::_underlying_impl::emulate_extraction<f32x4, 128, Index_>(a_);
#endif
		}
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 extract_u32x4_lane_f32x4(u32x4_arg a_)
	{
		static_assert(Index_ == 0, "Invalid SIMD lane extraction index: Extracting f32x4 lane from a u32x4 instance; the maximum index is 0 but this index has been exceeded.");
		return cast_u32x4_f32x4(a_);
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 extract_u32x8_lane_f32x4(u32x8_arg a_)
	{
		static_assert(Index_ <= 1, "Invalid SIMD lane extraction index: Extracting f32x4 lane from a u32x8 instance; the maximum index is 1 but this index has been exceeded.");
		if constexpr (Index_ == 0)
		{
			return cast_u32x8_f32x4(a_);
		}
		else
		{
#if EMU_SIMD_USE_256_REGISTERS
			return cast_u32x4_f32x4(_mm256_extracti128_si256(a_, Index_));
#else
			return EmuSIMD::_underlying_impl::emulate_extraction<f32x4, 128, Index_>(a_);
#endif
		}
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 extract_u32x16_lane_f32x4(u32x16_arg a_)
	{
		static_assert(Index_ <= 3, "Invalid SIMD lane extraction index: Extracting f32x4 lane from a u32x16 instance; the maximum index is 3 but this index has been exceeded.");
		if constexpr (Index_ == 0)
		{
			return cast_u32x16_f32x4(a_);
		}
		else
		{
#if EMU_SIMD_USE_512_REGISTERS
			return cast_u32x4_f32x4(_mm512_extracti32x4_epi32(a_, Index_));
#else
			return EmuSIMD::_underlying_impl::emulate_extraction<f32x4, 128, Index_>(a_);
#endif
		}
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 extract_u64x2_lane_f32x4(u64x2_arg a_)
	{
		static_assert(Index_ == 0, "Invalid SIMD lane extraction index: Extracting f32x4 lane from a u64x2 instance; the maximum index is 0 but this index has been exceeded.");
		return cast_u64x2_f32x4(a_);
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 extract_u64x4_lane_f32x4(u64x4_arg a_)
	{
		static_assert(Index_ <= 1, "Invalid SIMD lane extraction index: Extracting f32x4 lane from a u64x4 instance; the maximum index is 1 but this index has been exceeded.");
		if constexpr (Index_ == 0)
		{
			return cast_u64x4_f32x4(a_);
		}
		else
		{
#if EMU_SIMD_USE_256_REGISTERS
			return cast_u64x2_f32x4(_mm256_extracti128_si256(a_, Index_));
#else
			return EmuSIMD::_underlying_impl::emulate_extraction<f32x4, 128, Index_>(a_);
#endif
		}
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 extract_u64x8_lane_f32x4(u64x8_arg a_)
	{
		static_assert(Index_ <= 3, "Invalid SIMD lane extraction index: Extracting f32x4 lane from a u64x8 instance; the maximum index is 3 but this index has been exceeded.");
		if constexpr (Index_ == 0)
		{
			return cast_u64x8_f32x4(a_);
		}
		else
		{
#if EMU_SIMD_USE_512_REGISTERS
			return cast_u64x2_f32x4(_mm512_extracti32x4_epi32(a_, Index_));
#else
			return EmuSIMD::_underlying_impl::emulate_extraction<f32x4, 128, Index_>(a_);
#endif
		}
	}
#pragma endregion

#pragma region GET_TEMPLATES
	template<std::size_t Index_, typename OutT_ = float>
	EMU_SIMD_COMMON_FUNC_SPEC auto extract_element_f32x4(f32x4_arg in_)
		-> typename std::remove_cvref<OutT_>::type
	{
		if constexpr (Index_ == 0)
		{
			return static_cast<typename std::remove_cvref<OutT_>::type>(EmuSIMD::Funcs::get_first_f32x4(in_));
		}
		else
		{
			if constexpr (Index_ <= 3)
			{
#if EMU_SIMD_USE_128_REGISTERS
				constexpr auto shuffle_mask = make_shuffle_mask_32<Index_, Index_, Index_, Index_>();
				return static_cast<typename std::remove_cvref<OutT_>::type>(EmuSIMD::Funcs::get_first_f32x4(permute_f32x4<shuffle_mask>(in_)));
#else
				return EmuSIMD::_underlying_impl::retrieve_emulated_single_lane_simd_element<OutT_, Index_, false>(in_);
#endif
			}
			else
			{
				static_assert
				(
					EmuCore::TMP::get_false<std::size_t, Index_>(),
					"Invalid index provided when extracting an element from a f32x4 instance. Valid indices are 0, 1, 2, 3."
				);
			}
		}
	}
#pragma endregion
}

#endif
