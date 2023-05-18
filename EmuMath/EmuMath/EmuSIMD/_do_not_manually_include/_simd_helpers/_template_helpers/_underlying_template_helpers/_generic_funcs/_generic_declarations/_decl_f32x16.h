#ifndef EMU_SIMD_GENERIC_FUNCS_F32X16_DECL_H_INC_
#define EMU_SIMD_GENERIC_FUNCS_F32X16_DECL_H_INC_ 1

#include "../_common_generic_func_helpers.h"
#include "_decl_f32x4.h"

namespace EmuSIMD::Funcs
{
#pragma region SETTERS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 set_f32x16
	(
		float e0, float e1, float e2, float e3, float e4, float e5, float e6, float e7,
		float e8, float e9, float e10, float e11, float e12, float e13, float e14, float e15
	);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 setr_f32x16
	(
		float e0, float e1, float e2, float e3, float e4, float e5, float e6, float e7,
		float e8, float e9, float e10, float e11, float e12, float e13, float e14, float e15
	);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 set1_f32x16(float all_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 load_f32x16(const float* p_to_load_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 aligned_load_f32x16(const float* p_to_load_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 setzero_f32x16();
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 setmasked_f32x16(std::uint16_t bit_mask_);
#pragma endregion

#pragma region STORES
	EMU_SIMD_COMMON_FUNC_SPEC void store_f32x16(float* p_out_, f32x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC void aligned_store_f32x16(float* p_out_, f32x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC float get_first_f32x16(f32x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC std::uint16_t movemask_f32x16(f32x16_arg a_);
#pragma endregion

#pragma region CASTS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 cast_f32x4_f32x16(f32x4_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 cast_f32x8_f32x16(f32x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 cast_f32x16_f32x16(f32x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 cast_f64x2_f32x16(f64x2_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 cast_f64x4_f32x16(f64x4_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 cast_f64x8_f32x16(f64x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 cast_i8x16_f32x16(i8x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 cast_i16x8_f32x16(i16x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 cast_i32x4_f32x16(i32x4_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 cast_i64x2_f32x16(i64x2_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 cast_i8x32_f32x16(i8x32_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 cast_i16x16_f32x16(i16x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 cast_i32x8_f32x16(i32x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 cast_i64x4_f32x16(i64x4_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 cast_i8x64_f32x16(i8x64_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 cast_i16x32_f32x16(i16x32_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 cast_i32x16_f32x16(i32x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 cast_i64x8_f32x16(i64x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 cast_u8x16_f32x16(u8x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 cast_u16x8_f32x16(u16x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 cast_u32x4_f32x16(u32x4_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 cast_u64x2_f32x16(u64x2_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 cast_u8x32_f32x16(u8x32_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 cast_u16x16_f32x16(u16x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 cast_u32x8_f32x16(u32x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 cast_u64x4_f32x16(u64x4_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 cast_u8x64_f32x16(u8x64_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 cast_u16x32_f32x16(u16x32_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 cast_u32x16_f32x16(u32x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 cast_u64x8_f32x16(u64x8_arg a_);
#pragma endregion

#pragma region CONVERSIONS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 cvt_f32x4_f32x16(f32x4_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 cvt_f32x8_f32x16(f32x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 cvt_f32x16_f32x16(f32x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 cvt_f64x2_f32x16(f64x2_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 cvt_f64x4_f32x16(f64x4_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 cvt_f64x8_f32x16(f64x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 cvt_i8x16_f32x16(i8x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 cvt_i16x8_f32x16(i16x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 cvt_i32x4_f32x16(i32x4_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 cvt_i64x2_f32x16(i64x2_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 cvt_i8x32_f32x16(i8x32_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 cvt_i16x16_f32x16(i16x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 cvt_i32x8_f32x16(i32x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 cvt_i64x4_f32x16(i64x4_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 cvt_i8x64_f32x16(i8x64_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 cvt_i16x32_f32x16(i16x32_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 cvt_i32x16_f32x16(i32x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 cvt_i64x8_f32x16(i64x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 cvt_u8x16_f32x16(u8x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 cvt_u16x8_f32x16(u16x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 cvt_u32x4_f32x16(u32x4_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 cvt_u64x2_f32x16(u64x2_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 cvt_u8x32_f32x16(u8x32_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 cvt_u16x16_f32x16(u16x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 cvt_u32x8_f32x16(u32x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 cvt_u64x4_f32x16(u64x4_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 cvt_u8x64_f32x16(u8x64_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 cvt_u16x32_f32x16(u16x32_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 cvt_u32x16_f32x16(u32x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 cvt_u64x8_f32x16(u64x8_arg a_);
#pragma endregion

#pragma region COMPARISONS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 cmpeq_f32x16(EmuSIMD::f32x16_arg lhs_, EmuSIMD::f32x16_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 cmpneq_f32x16(EmuSIMD::f32x16_arg lhs_, EmuSIMD::f32x16_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 cmpgt_f32x16(EmuSIMD::f32x16_arg lhs_, EmuSIMD::f32x16_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 cmplt_f32x16(EmuSIMD::f32x16_arg lhs_, EmuSIMD::f32x16_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 cmpge_f32x16(EmuSIMD::f32x16_arg lhs_, EmuSIMD::f32x16_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 cmple_f32x16(EmuSIMD::f32x16_arg lhs_, EmuSIMD::f32x16_arg rhs_);
#pragma endregion

#pragma region BLENDS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 blendv_f32x16(EmuSIMD::f32x16_arg a_, EmuSIMD::f32x16_arg b_, EmuSIMD::f32x16_arg shuffle_mask_vec_);
#pragma endregion

#pragma region MOVES
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 movehl_f32x16(EmuSIMD::f32x16_arg lhs_, EmuSIMD::f32x16_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 movelh_f32x16(EmuSIMD::f32x16_arg lhs_, EmuSIMD::f32x16_arg rhs_);
#pragma endregion

#pragma region BITWISE_ARITHMETIC
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 and_f32x16(EmuSIMD::f32x16_arg lhs_, EmuSIMD::f32x16_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 or_f32x16(EmuSIMD::f32x16_arg lhs_, EmuSIMD::f32x16_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 xor_f32x16(EmuSIMD::f32x16_arg lhs_, EmuSIMD::f32x16_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 andnot_f32x16(EmuSIMD::f32x16_arg not_lhs_, EmuSIMD::f32x16_arg rhs_);
	template<std::int32_t NumShifts_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 shift_left_f32x16(EmuSIMD::f32x16_arg lhs_);
	template<std::int32_t NumShifts_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 shift_right_arithmetic_f32x16(EmuSIMD::f32x16_arg lhs_);
	template<std::int32_t NumShifts_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 shift_right_logical_f32x16(EmuSIMD::f32x16_arg lhs_);
#pragma endregion

#pragma region MINMAX_FUNCS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 min_f32x16(EmuSIMD::f32x16_arg a_, EmuSIMD::f32x16_arg b_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 horizontal_min_f32x16(EmuSIMD::f32x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 max_f32x16(EmuSIMD::f32x16_arg a_, EmuSIMD::f32x16_arg b_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 horizontal_max_f32x16(EmuSIMD::f32x16_arg a_);
#pragma endregion

#pragma region BASIC_ARITHMETIC
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 mul_all_f32x16(EmuSIMD::f32x16_arg lhs_, EmuSIMD::f32x16_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 add_f32x16(EmuSIMD::f32x16_arg lhs_, EmuSIMD::f32x16_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 sub_f32x16(EmuSIMD::f32x16_arg lhs_, EmuSIMD::f32x16_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 negate_f32x16(EmuSIMD::f32x16_arg to_negate_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 div_f32x16(EmuSIMD::f32x16_arg lhs_, EmuSIMD::f32x16_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 fmadd_f32x16(EmuSIMD::f32x16_arg a_, EmuSIMD::f32x16_arg b_, EmuSIMD::f32x16_arg c_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 fmsub_f32x16(EmuSIMD::f32x16_arg a_, EmuSIMD::f32x16_arg b_, EmuSIMD::f32x16_arg c_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 fnmadd_f32x16(EmuSIMD::f32x16_arg a_, EmuSIMD::f32x16_arg b_, EmuSIMD::f32x16_arg c_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 fnmsub_f32x16(EmuSIMD::f32x16_arg a_, EmuSIMD::f32x16_arg b_, EmuSIMD::f32x16_arg c_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 fmaddsub_f32x16(EmuSIMD::f32x16_arg a_, EmuSIMD::f32x16_arg b_, EmuSIMD::f32x16_arg c_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 addsub_f32x16(EmuSIMD::f32x16_arg lhs_, EmuSIMD::f32x16_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 fmsubadd_f32x16(EmuSIMD::f32x16_arg a_, EmuSIMD::f32x16_arg b_, EmuSIMD::f32x16_arg c_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 subadd_f32x16(EmuSIMD::f32x16_arg lhs_, EmuSIMD::f32x16_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 floor_f32x16(EmuSIMD::f32x16_arg to_floor_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 ceil_f32x16(EmuSIMD::f32x16_arg to_ceil_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 trunc_f32x16(EmuSIMD::f32x16_arg to_trunc_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 mod_f32x16(EmuSIMD::f32x16_arg lhs_, EmuSIMD::f32x16_arg rhs_);;
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 abs_f32x16(EmuSIMD::f32x16_arg in_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 sqrt_f32x16(EmuSIMD::f32x16_arg in_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 rsqrt_f32x16(EmuSIMD::f32x16_arg in_);
#pragma endregion

#pragma region NEAR_COMPARISONS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 cmpnear_f32x16(EmuSIMD::f32x16_arg lhs_, EmuSIMD::f32x16_arg rhs_, EmuSIMD::f32x16_arg epsilon = set1_f32x16(EmuCore::epsilon<float>::get()));
#pragma endregion

#pragma region TRIG
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 cos_f32x16(EmuSIMD::f32x16_arg in_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 sin_f32x16(EmuSIMD::f32x16_arg in_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 tan_f32x16(EmuSIMD::f32x16_arg in_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 acos_f32x16(EmuSIMD::f32x16_arg in_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 asin_f32x16(EmuSIMD::f32x16_arg in_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 atan2_f32x16(EmuSIMD::f32x16_arg y_, EmuSIMD::f32x16_arg x_);
#pragma endregion

	// ^^^ ENDING DECLARATIONS ^^^
	// ---------------------------
	// vvv STARTING  TEMPLATES vvv

#pragma region ROUNDING_TEMPLATES
	template<int RoundingFlag_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 round_f32x16(EmuSIMD::f32x16_arg to_round_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_roundscale_ps(to_round_, RoundingFlag_);
#else
		using EmuSIMD::_underlying_impl::emulate_simd_basic;
		return emulate_simd_basic([](EmuSIMD::f32x8_arg to_round) { return round_f32x8<RoundingFlag_>(to_round); }, to_round_);
#endif
	}
#pragma endregion

#pragma region SHUFFLE_TEMPLATES
	template<shuffle_mask_type ShuffleMask>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 shuffle_f32x16(EmuSIMD::f32x16_arg lhs_, EmuSIMD::f32x16_arg rhs_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_shuffle_ps(lhs_, rhs_, ShuffleMask);
#else
		using EmuSIMD::_underlying_impl::emulate_simd_basic;
		return emulate_simd_basic([](EmuSIMD::f32x8_arg lhs, EmuSIMD::f32x8_arg rhs) { return shuffle_f32x8<ShuffleMask>(lhs, rhs); }, lhs_, rhs_);
#endif
	}

	template<shuffle_mask_type ShuffleMask>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 permute_f32x16(EmuSIMD::f32x16_arg in_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_permute_ps(in_, ShuffleMask);
#else
		using EmuSIMD::_underlying_impl::emulate_simd_basic;
		return emulate_simd_basic([](EmuSIMD::f32x8_arg ab) { return permute_f32x8<ShuffleMask>(ab); }, in_);
#endif
	}
#pragma endregion

#pragma region BLEND_TEMPLATES
	template<EmuSIMD::Funcs::blend_mask_type BlendMask>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 blend_f32x16(EmuSIMD::f32x16_arg a_, EmuSIMD::f32x16_arg b_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_mask_blend_ps(BlendMask, a_, b_);
#else
		return EmuSIMD::_underlying_impl::emulate_dual_lane_blend_with_mask<BlendMask>(a_, b_, std::make_index_sequence<8>());
#endif
	}
#pragma endregion

#pragma region EXTRACTION_TEMPLATES
	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 extract_f32x16_lane_f32x16(f32x16_arg a_)
	{
		static_assert(Index_ == 0, "Invalid SIMD lane extraction index: Extracting f32x16 lane from a f32x16 instance; the maximum index is 0 but this index has been exceeded.");
		return a_;
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 extract_f64x8_lane_f32x16(f64x8_arg a_)
	{
		static_assert(Index_ == 0, "Invalid SIMD lane extraction index: Extracting f32x16 lane from a f64x8 instance; the maximum index is 0 but this index has been exceeded.");
		return cast_f64x8_f32x16(a_);
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 extract_i8x64_lane_f32x16(i8x64_arg a_)
	{
		static_assert(Index_ == 0, "Invalid SIMD lane extraction index: Extracting f32x16 lane from a i8x64 instance; the maximum index is 0 but this index has been exceeded.");
		return cast_i8x64_f32x16(a_);
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 extract_i16x32_lane_f32x16(i16x32_arg a_)
	{
		static_assert(Index_ == 0, "Invalid SIMD lane extraction index: Extracting f32x16 lane from a i16x32 instance; the maximum index is 0 but this index has been exceeded.");
		return cast_i16x32_f32x16(a_);
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 extract_i32x16_lane_f32x16(i32x16_arg a_)
	{
		static_assert(Index_ == 0, "Invalid SIMD lane extraction index: Extracting f32x16 lane from a i32x16 instance; the maximum index is 0 but this index has been exceeded.");
		return cast_i32x16_f32x16(a_);
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 extract_i64x8_lane_f32x16(i64x8_arg a_)
	{
		static_assert(Index_ == 0, "Invalid SIMD lane extraction index: Extracting f32x16 lane from a i64x8 instance; the maximum index is 0 but this index has been exceeded.");
		return cast_i64x8_f32x16(a_);
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 extract_u8x64_lane_f32x16(u8x64_arg a_)
	{
		static_assert(Index_ == 0, "Invalid SIMD lane extraction index: Extracting f32x16 lane from a u8x64 instance; the maximum index is 0 but this index has been exceeded.");
		return cast_u8x64_f32x16(a_);
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 extract_u16x32_lane_f32x16(u16x32_arg a_)
	{
		static_assert(Index_ == 0, "Invalid SIMD lane extraction index: Extracting f32x16 lane from a u16x32 instance; the maximum index is 0 but this index has been exceeded.");
		return cast_u16x32_f32x16(a_);
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 extract_u32x16_lane_f32x16(u32x16_arg a_)
	{
		static_assert(Index_ == 0, "Invalid SIMD lane extraction index: Extracting f32x16 lane from a u32x16 instance; the maximum index is 0 but this index has been exceeded.");
		return cast_u32x16_f32x16(a_);
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x16 extract_u64x8_lane_f32x16(u64x8_arg a_)
	{
		static_assert(Index_ == 0, "Invalid SIMD lane extraction index: Extracting f32x16 lane from a u64x8 instance; the maximum index is 0 but this index has been exceeded.");
		return cast_u64x8_f32x16(a_);
	}
#pragma endregion

#pragma region GET_TEMPLATES
	template<std::size_t Index_, typename OutT_ = float>
	EMU_SIMD_COMMON_FUNC_SPEC auto extract_element_f32x16(f32x16_arg in_)
		-> typename std::remove_cvref<OutT_>::type
	{
		if constexpr (Index_ == 0)
		{
			return static_cast<typename std::remove_cvref<OutT_>::type>(get_first_f32x16(in_));
		}
		else
		{
			if constexpr (Index_ <= 7)
			{
#if EMU_SIMD_USE_512_REGISTERS
				constexpr std::size_t chunk_index = static_cast<std::size_t>(Index_ / 4);
				constexpr std::size_t index_128 = Index_ - (4 * chunk_index);
				return EmuSIMD::Funcs::extract_element_f32x4<index_128, OutT_>(EmuSIMD::Funcs::extract_f32x16_lane_f32x4<chunk_index>(in_));
#else
				return EmuSIMD::_underlying_impl::retrieve_emulated_dual_lane_simd_element<OutT_, Index_, false, 8>(in_);
#endif
			}
			else
			{
				static_assert
				(
					EmuCore::TMP::get_false<std::size_t, Index_>(),
					"Invalid index provided when extracting an element from a f32x16 instance. Valid indices are 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15."
				);
			}
		}
	}
#pragma endregion
}

#endif
