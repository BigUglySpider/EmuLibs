#ifndef EMU_SIMD_GENERIC_FUNCS_F64X8_DECL_H_INC_
#define EMU_SIMD_GENERIC_FUNCS_F64X8_DECL_H_INC_ 1

#include "../_common_generic_func_helpers.h"
#include "_decl_f64x2.h"

namespace EmuSIMD::Funcs
{
#pragma region SETTERS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 set_f64x8(double e0, double e1, double e2, double e3, double e4, double e5, double e6, double e7);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 setr_f64x8(double e0, double e1, double e2, double e3, double e4, double e5, double e6, double e7);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 set1_f64x8(double all_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 load_f64x8(const double* p_to_load_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 aligned_load_f64x8(const double* p_to_load_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 setzero_f64x8();
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 setmasked_f64x8(std::uint8_t bit_mask_);
#pragma endregion

#pragma region STORES
	EMU_SIMD_COMMON_FUNC_SPEC void store_f64x8(double* p_out_, f64x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC void aligned_store_f64x8(double* p_out_, f64x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC double get_first_f64x8(f64x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC std::uint8_t movemask_f64x8(f64x8_arg a_);
#pragma endregion

#pragma region CASTS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cast_f32x4_f64x8(f32x4_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cast_f32x8_f64x8(f32x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cast_f32x16_f64x8(f32x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cast_f64x2_f64x8(f64x2_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cast_f64x4_f64x8(f64x4_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cast_f64x8_f64x8(f64x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cast_i8x16_f64x8(i8x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cast_i16x8_f64x8(i16x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cast_i32x4_f64x8(i32x4_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cast_i64x2_f64x8(i64x2_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cast_i8x32_f64x8(i8x32_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cast_i16x16_f64x8(i16x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cast_i32x8_f64x8(i32x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cast_i64x4_f64x8(i64x4_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cast_i8x64_f64x8(i8x64_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cast_i16x32_f64x8(i16x32_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cast_i32x16_f64x8(i32x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cast_i64x8_f64x8(i64x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cast_u8x16_f64x8(u8x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cast_u16x8_f64x8(u16x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cast_u32x4_f64x8(u32x4_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cast_u64x2_f64x8(u64x2_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cast_u8x32_f64x8(u8x32_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cast_u16x16_f64x8(u16x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cast_u32x8_f64x8(u32x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cast_u64x4_f64x8(u64x4_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cast_u8x64_f64x8(u8x64_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cast_u16x32_f64x8(u16x32_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cast_u32x16_f64x8(u32x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cast_u64x8_f64x8(u64x8_arg a_);
#pragma endregion

#pragma region CONVERSIONS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cvt_f32x4_f64x8(f32x4_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cvt_f32x8_f64x8(f32x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cvt_f32x16_f64x8(f32x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cvt_f64x2_f64x8(f64x2_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cvt_f64x4_f64x8(f64x4_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cvt_f64x8_f64x8(f64x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cvt_i8x16_f64x8(i8x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cvt_i16x8_f64x8(i16x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cvt_i32x4_f64x8(i32x4_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cvt_i64x2_f64x8(i64x2_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cvt_i8x32_f64x8(i8x32_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cvt_i16x16_f64x8(i16x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cvt_i32x8_f64x8(i32x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cvt_i64x4_f64x8(i64x4_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cvt_i8x64_f64x8(i8x64_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cvt_i16x32_f64x8(i16x32_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cvt_i32x16_f64x8(i32x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cvt_i64x8_f64x8(i64x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cvt_u8x16_f64x8(u8x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cvt_u16x8_f64x8(u16x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cvt_u32x4_f64x8(u32x4_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cvt_u64x2_f64x8(u64x2_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cvt_u8x32_f64x8(u8x32_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cvt_u16x16_f64x8(u16x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cvt_u32x8_f64x8(u32x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cvt_u64x4_f64x8(u64x4_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cvt_u8x64_f64x8(u8x64_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cvt_u16x32_f64x8(u16x32_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cvt_u32x16_f64x8(u32x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cvt_u64x8_f64x8(u64x8_arg a_);
#pragma endregion

#pragma region COMPARISONS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cmpeq_f64x8(EmuSIMD::f64x8_arg lhs_, EmuSIMD::f64x8_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cmpneq_f64x8(EmuSIMD::f64x8_arg lhs_, EmuSIMD::f64x8_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cmpgt_f64x8(EmuSIMD::f64x8_arg lhs_, EmuSIMD::f64x8_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cmplt_f64x8(EmuSIMD::f64x8_arg lhs_, EmuSIMD::f64x8_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cmpge_f64x8(EmuSIMD::f64x8_arg lhs_, EmuSIMD::f64x8_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cmple_f64x8(EmuSIMD::f64x8_arg lhs_, EmuSIMD::f64x8_arg rhs_);
#pragma endregion

#pragma region BLENDS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 blendv_f64x8(EmuSIMD::f64x8_arg a_, EmuSIMD::f64x8_arg b_, EmuSIMD::f64x8_arg shuffle_mask_vec_);
#pragma endregion

#pragma region MOVES
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 movehl_f64x8(EmuSIMD::f64x8_arg lhs_, EmuSIMD::f64x8_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 movelh_f64x8(EmuSIMD::f64x8_arg lhs_, EmuSIMD::f64x8_arg rhs_);
#pragma endregion

#pragma region BITWISE_ARITHMETIC
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 and_f64x8(EmuSIMD::f64x8_arg lhs_, EmuSIMD::f64x8_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 or_f64x8(EmuSIMD::f64x8_arg lhs_, EmuSIMD::f64x8_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 xor_f64x8(EmuSIMD::f64x8_arg lhs_, EmuSIMD::f64x8_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 andnot_f64x8(EmuSIMD::f64x8_arg not_lhs_, EmuSIMD::f64x8_arg rhs_);
	template<std::int32_t NumShifts_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 shift_left_f64x8(EmuSIMD::f64x8_arg lhs_);
	template<std::int32_t NumShifts_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 shift_right_arithmetic_f64x8(EmuSIMD::f64x8_arg lhs_);
	template<std::int32_t NumShifts_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 shift_right_logical_f64x8(EmuSIMD::f64x8_arg lhs_);
#pragma endregion

#pragma region MINMAX_FUNCS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 min_f64x8(EmuSIMD::f64x8_arg a_, EmuSIMD::f64x8_arg b_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 horizontal_min_f64x8(EmuSIMD::f64x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 max_f64x8(EmuSIMD::f64x8_arg a_, EmuSIMD::f64x8_arg b_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 horizontal_max_f64x8(EmuSIMD::f64x8_arg a_);
#pragma endregion

#pragma region BASIC_ARITHMETIC
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 mul_all_f64x8(EmuSIMD::f64x8_arg lhs_, EmuSIMD::f64x8_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 negate_f64x8(EmuSIMD::f64x8_arg to_negate_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 add_f64x8(EmuSIMD::f64x8_arg lhs_, EmuSIMD::f64x8_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 sub_f64x8(EmuSIMD::f64x8_arg lhs_, EmuSIMD::f64x8_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 div_f64x8(EmuSIMD::f64x8_arg lhs_, EmuSIMD::f64x8_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 fmadd_f64x8(EmuSIMD::f64x8_arg a_, EmuSIMD::f64x8_arg b_, EmuSIMD::f64x8_arg c_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 fmsub_f64x8(EmuSIMD::f64x8_arg a_, EmuSIMD::f64x8_arg b_, EmuSIMD::f64x8_arg c_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 fnmadd_f64x8(EmuSIMD::f64x8_arg a_, EmuSIMD::f64x8_arg b_, EmuSIMD::f64x8_arg c_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 fnmsub_f64x8(EmuSIMD::f64x8_arg a_, EmuSIMD::f64x8_arg b_, EmuSIMD::f64x8_arg c_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 fmaddsub_f64x8(EmuSIMD::f64x8_arg a_, EmuSIMD::f64x8_arg b_, EmuSIMD::f64x8_arg c_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 fmsubadd_f64x8(EmuSIMD::f64x8_arg a_, EmuSIMD::f64x8_arg b_, EmuSIMD::f64x8_arg c_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 addsub_f64x8(EmuSIMD::f64x8_arg lhs_, EmuSIMD::f64x8_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 subadd_f64x8(EmuSIMD::f64x8_arg lhs_, EmuSIMD::f64x8_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 floor_f64x8(EmuSIMD::f64x8_arg to_floor_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 ceil_f64x8(EmuSIMD::f64x8_arg to_ceil_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 trunc_f64x8(EmuSIMD::f64x8_arg to_trunc_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 mod_f64x8(EmuSIMD::f64x8_arg lhs_, EmuSIMD::f64x8_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 abs_f64x8(EmuSIMD::f64x8_arg in_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 sqrt_f64x8(EmuSIMD::f64x8_arg in_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 rsqrt_f64x8(EmuSIMD::f64x8_arg in_);
#pragma endregion

#pragma region NEAR_COMPARISONS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cmpnear_f64x8(EmuSIMD::f64x8_arg lhs_, EmuSIMD::f64x8_arg rhs_, EmuSIMD::f64x8_arg epsilon = set1_f64x8(EmuCore::epsilon<double>::get()));
#pragma endregion

#pragma region TRIG
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cos_f64x8(EmuSIMD::f64x8_arg in_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 sin_f64x8(EmuSIMD::f64x8_arg in_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 tan_f64x8(EmuSIMD::f64x8_arg in_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 acos_f64x8(EmuSIMD::f64x8_arg in_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 asin_f64x8(EmuSIMD::f64x8_arg in_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 atan2_f64x8(EmuSIMD::f64x8_arg y_, EmuSIMD::f64x8_arg x_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 atan_f64x8(EmuSIMD::f64x8_arg in_);
#pragma endregion

#pragma region ROUNDING_TEMPLATES
	template<int RoundingFlag_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 round_f64x8(EmuSIMD::f64x8_arg to_round_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_roundscale_pd(to_round_, RoundingFlag_);
#else
		using EmuSIMD::_underlying_impl::emulate_simd_basic;
		return emulate_simd_basic([](f64x4_arg to_round) { return EmuSIMD::Funcs::round_f64x4<RoundingFlag_>(to_round); }, to_round_);
#endif
	}
#pragma endregion

#pragma region SHUFFLE_TEMPLATES
	template<EmuSIMD::Funcs::shuffle_mask_type ShuffleMask_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 shuffle_f64x8(EmuSIMD::f64x8_arg lhs_, EmuSIMD::f64x8_arg rhs_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_shuffle_pd(lhs_, rhs_, ShuffleMask_);
#else
		using EmuSIMD::_underlying_impl::emulate_simd_basic;
		return emulate_simd_basic([](f64x4_arg lhs, f64x4_arg rhs) { return EmuSIMD::Funcs::shuffle_f64x4<ShuffleMask_>(lhs, rhs); }, lhs_, rhs_);
#endif
	}

	template<EmuSIMD::Funcs::shuffle_mask_type ShuffleMask_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 permute_f64x8(EmuSIMD::f64x8_arg in_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_permute_pd(in_, ShuffleMask_);
#else
		using EmuSIMD::_underlying_impl::emulate_simd_basic;
		return emulate_simd_basic([](f64x4_arg a) { return EmuSIMD::Funcs::permute_f64x4<ShuffleMask_>(a); }, in_);
#endif
	}
#pragma endregion

#pragma region BLEND_TEMPLATES
	template<EmuSIMD::Funcs::blend_mask_type BlendMask_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 blend_f64x8(EmuSIMD::f64x8_arg a_, EmuSIMD::f64x8_arg b_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_mask_blend_pd(BlendMask_, a_, b_);
#else
		return EmuSIMD::_underlying_impl::emulate_dual_lane_blend_with_mask<BlendMask_>(a_, b_, std::make_index_sequence<4>());
#endif
	}
#pragma endregion

#pragma region EXTRACTION_TEMPLATES
	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 extract_f32x16_lane_f64x8(f32x16_arg a_)
	{
		static_assert(Index_ == 0, "Invalid SIMD lane extraction index: Extracting f64x8 lane from a f32x16 instance; the maximum index is 0 but this index has been exceeded.");
		return cast_f32x16_f64x8(a_);
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 extract_f64x8_lane_f64x8(f64x8_arg a_)
	{
		static_assert(Index_ == 0, "Invalid SIMD lane extraction index: Extracting f64x8 lane from a f64x8 instance; the maximum index is 0 but this index has been exceeded.");
		return a_;
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 extract_i8x64_lane_f64x8(i8x64_arg a_)
	{
		static_assert(Index_ == 0, "Invalid SIMD lane extraction index: Extracting f64x8 lane from a i8x64 instance; the maximum index is 0 but this index has been exceeded.");
		return cast_i8x64_f64x8(a_);
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 extract_i16x32_lane_f64x8(i16x32_arg a_)
	{
		static_assert(Index_ == 0, "Invalid SIMD lane extraction index: Extracting f64x8 lane from a i16x32 instance; the maximum index is 0 but this index has been exceeded.");
		return cast_i16x32_f64x8(a_);
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 extract_i32x16_lane_f64x8(i32x16_arg a_)
	{
		static_assert(Index_ == 0, "Invalid SIMD lane extraction index: Extracting f64x8 lane from a i32x16 instance; the maximum index is 0 but this index has been exceeded.");
		return cast_i32x16_f64x8(a_);
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 extract_i64x8_lane_f64x8(i64x8_arg a_)
	{
		static_assert(Index_ == 0, "Invalid SIMD lane extraction index: Extracting f64x8 lane from a i64x8 instance; the maximum index is 0 but this index has been exceeded.");
		return cast_i64x8_f64x8(a_);
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 extract_u8x64_lane_f64x8(u8x64_arg a_)
	{
		static_assert(Index_ == 0, "Invalid SIMD lane extraction index: Extracting f64x8 lane from a u8x64 instance; the maximum index is 0 but this index has been exceeded.");
		return cast_u8x64_f64x8(a_);
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 extract_u16x32_lane_f64x8(u16x32_arg a_)
	{
		static_assert(Index_ == 0, "Invalid SIMD lane extraction index: Extracting f64x8 lane from a u16x32 instance; the maximum index is 0 but this index has been exceeded.");
		return cast_u16x32_f64x8(a_);
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 extract_u32x16_lane_f64x8(u32x16_arg a_)
	{
		static_assert(Index_ == 0, "Invalid SIMD lane extraction index: Extracting f64x8 lane from a u32x16 instance; the maximum index is 0 but this index has been exceeded.");
		return cast_u32x16_f64x8(a_);
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 extract_u64x8_lane_f64x8(u64x8_arg a_)
	{
		static_assert(Index_ == 0, "Invalid SIMD lane extraction index: Extracting f64x8 lane from a u64x8 instance; the maximum index is 0 but this index has been exceeded.");
		return cast_u64x8_f64x8(a_);
	}
#pragma endregion

#pragma region GET_TEMPLATES
	template<std::size_t Index_, typename OutT_ = double>
	EMU_SIMD_COMMON_FUNC_SPEC auto extract_element_f64x8(f64x8_arg in_)
		-> typename std::remove_cvref<OutT_>::type
	{
		if constexpr (Index_ == 0)
		{
			return static_cast<typename std::remove_cvref<OutT_>::type>(get_first_f64x8(in_));
		}
		else
		{
			if constexpr (Index_ <= 7)
			{
#if EMU_SIMD_USE_512_REGISTERS
				constexpr std::size_t chunk_index = static_cast<std::size_t>(Index_ / 2);
				constexpr std::size_t index_128 = Index_ - (2 * chunk_index);
				return EmuSIMD::Funcs::extract_element_f64x2<index_128, OutT_>(EmuSIMD::Funcs::extract_f64x8_lane_f64x2<chunk_index>(in_));
#else
				return EmuSIMD::_underlying_impl::retrieve_emulated_dual_lane_simd_element<OutT_, Index_, false, 4>(in_);
#endif
			}
			else
			{
				static_assert
				(
					EmuCore::TMP::get_false<std::size_t, Index_>(),
					"Invalid index provided when extracting an element from a f64x8 instance. Valid indices are 0, 1, 2, 3, 4, 5, 6, 7."
				);
			}
		}
	}
#pragma endregion
}

#endif
