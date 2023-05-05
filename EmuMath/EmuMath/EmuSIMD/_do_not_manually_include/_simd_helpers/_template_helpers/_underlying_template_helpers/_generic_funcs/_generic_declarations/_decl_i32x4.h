#ifndef EMU_SIMD_GENERIC_FUNCS_I32X4_DECL_H_INC_
#define EMU_SIMD_GENERIC_FUNCS_I32X4_DECL_H_INC_ 1

#include "../_common_generic_func_helpers.h"
#include "_decl_f32x4.h"

namespace EmuSIMD::Funcs
{
#pragma region SETTERS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 set_i32x4(std::int32_t e0, std::int32_t e1, std::int32_t e2, std::int32_t e3);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 setr_i32x4(std::int32_t e0, std::int32_t e1, std::int32_t e2, std::int32_t e3);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 set1_i32x4(std::int32_t all_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 load_i32x4(const std::int32_t* p_to_load_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 setzero_i32x4();
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 setmasked_i32x4(std::uint8_t bit_mask_);
#pragma endregion

#pragma region STORES
	EMU_SIMD_COMMON_FUNC_SPEC void store_i32x4(std::int32_t* p_out_, i32x4_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC std::int32_t get_first_i32x4(i32x4_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC std::uint8_t movemask_i32x4(i32x4_arg a_);
#pragma endregion

#pragma region CASTS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cast_f32x4_i32x4(f32x4_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cast_f32x8_i32x4(f32x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cast_f32x16_i32x4(f32x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cast_f64x2_i32x4(f64x2_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cast_f64x4_i32x4(f64x4_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cast_f64x8_i32x4(f64x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cast_i8x16_i32x4(i8x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cast_i16x8_i32x4(i16x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cast_i32x4_i32x4(i32x4_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cast_i64x2_i32x4(i64x2_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cast_i8x32_i32x4(i8x32_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cast_i16x16_i32x4(i16x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cast_i32x8_i32x4(i32x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cast_i64x4_i32x4(i64x4_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cast_i8x64_i32x4(i8x64_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cast_i16x32_i32x4(i16x32_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cast_i32x16_i32x4(i32x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cast_i64x8_i32x4(i64x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cast_u8x16_i32x4(u8x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cast_u16x8_i32x4(u16x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cast_u32x4_i32x4(u32x4_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cast_u64x2_i32x4(u64x2_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cast_u8x32_i32x4(u8x32_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cast_u16x16_i32x4(u16x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cast_u32x8_i32x4(u32x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cast_u64x4_i32x4(u64x4_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cast_u8x64_i32x4(u8x64_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cast_u16x32_i32x4(u16x32_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cast_u32x16_i32x4(u32x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cast_u64x8_i32x4(u64x8_arg a_);
#pragma endregion

#pragma region CONVERSIONS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cvt_f32x4_i32x4(f32x4_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cvt_f32x8_i32x4(f32x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cvt_f32x16_i32x4(f32x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cvt_f64x2_i32x4(f64x2_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cvt_f64x4_i32x4(f64x4_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cvt_f64x8_i32x4(f64x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cvt_i8x16_i32x4(i8x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cvt_i16x8_i32x4(i16x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cvt_i32x4_i32x4(i32x4_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cvt_i64x2_i32x4(i64x2_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cvt_i8x32_i32x4(i8x32_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cvt_i16x16_i32x4(i16x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cvt_i32x8_i32x4(i32x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cvt_i64x4_i32x4(i64x4_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cvt_i8x64_i32x4(i8x64_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cvt_i16x32_i32x4(i16x32_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cvt_i32x16_i32x4(i32x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cvt_i64x8_i32x4(i64x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cvt_u8x16_i32x4(u8x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cvt_u16x8_i32x4(u16x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cvt_u32x4_i32x4(u32x4_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cvt_u64x2_i32x4(u64x2_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cvt_u8x32_i32x4(u8x32_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cvt_u16x16_i32x4(u16x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cvt_u32x8_i32x4(u32x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cvt_u64x4_i32x4(u64x4_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cvt_u8x64_i32x4(u8x64_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cvt_u16x32_i32x4(u16x32_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cvt_u32x16_i32x4(u32x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cvt_u64x8_i32x4(u64x8_arg a_);
#pragma endregion

#pragma region COMPARISONS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cmpeq_i32x4(EmuSIMD::i32x4_arg lhs_, EmuSIMD::i32x4_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cmpneq_i32x4(EmuSIMD::i32x4_arg lhs_, EmuSIMD::i32x4_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cmpgt_i32x4(EmuSIMD::i32x4_arg lhs_, EmuSIMD::i32x4_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cmplt_i32x4(EmuSIMD::i32x4_arg lhs_, EmuSIMD::i32x4_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cmpge_i32x4(EmuSIMD::i32x4_arg lhs_, EmuSIMD::i32x4_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cmple_i32x4(EmuSIMD::i32x4_arg lhs_, EmuSIMD::i32x4_arg rhs_);
#pragma endregion

#pragma region BITWISE_ARITHMETIC
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 and_i32x4(EmuSIMD::i32x4_arg lhs_, EmuSIMD::i32x4_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 or_i32x4(EmuSIMD::i32x4_arg lhs_, EmuSIMD::i32x4_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 xor_i32x4(EmuSIMD::i32x4_arg lhs_, EmuSIMD::i32x4_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 andnot_i32x4(EmuSIMD::i32x4_arg not_lhs_, EmuSIMD::i32x4_arg rhs_);
	template<std::int32_t NumShifts_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 shift_left_i32x4(EmuSIMD::i32x4_arg lhs_);
	template<std::int32_t NumShifts_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 shift_right_arithmetic_i32x4(EmuSIMD::i32x4_arg lhs_);
	template<std::int32_t NumShifts_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 shift_right_logical_i32x4(EmuSIMD::i32x4_arg lhs_);
#pragma endregion

#pragma region MOVES
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 movehl_i32x4(EmuSIMD::i32x4_arg lhs_, EmuSIMD::i32x4_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 movelh_i32x4(EmuSIMD::i32x4_arg lhs_, EmuSIMD::i32x4_arg rhs_);
#pragma endregion

#pragma region BLENDS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 blendv_i32x4(EmuSIMD::i32x4_arg a_, EmuSIMD::i32x4_arg b_, EmuSIMD::i32x4_arg shuffle_mask_vec_);
#pragma endregion

#pragma region MINMAX_FUNCS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 min_i32x4(EmuSIMD::i32x4_arg a_, EmuSIMD::i32x4_arg b_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 horizontal_min_i32x4(EmuSIMD::i32x4_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 max_i32x4(EmuSIMD::i32x4_arg a_, EmuSIMD::i32x4_arg b_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 horizontal_max_i32x4(EmuSIMD::i32x4_arg a_);
#pragma endregion

#pragma region BASIC_ARITHMETIC
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 mul_all_i32x4(EmuSIMD::i32x4_arg lhs_, EmuSIMD::i32x4_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 negate_i32x4(EmuSIMD::i32x4_arg to_negate_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 add_i32x4(EmuSIMD::i32x4_arg lhs_, EmuSIMD::i32x4_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 sub_i32x4(EmuSIMD::i32x4_arg lhs_, EmuSIMD::i32x4_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 mul_i32x4(EmuSIMD::i32x4_arg lhs_, EmuSIMD::i32x4_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 div_i32x4(EmuSIMD::i32x4_arg lhs_, EmuSIMD::i32x4_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 addsub_i32x4(EmuSIMD::i32x4_arg lhs_, EmuSIMD::i32x4_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 subadd_i32x4(EmuSIMD::i32x4_arg lhs_, EmuSIMD::i32x4_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 fmadd_i32x4(EmuSIMD::i32x4_arg a_, EmuSIMD::i32x4_arg b_, EmuSIMD::i32x4_arg c_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 fmsub_i32x4(EmuSIMD::i32x4_arg a_, EmuSIMD::i32x4_arg b_, EmuSIMD::i32x4_arg c_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 fnmadd_i32x4(EmuSIMD::i32x4_arg a_, EmuSIMD::i32x4_arg b_, EmuSIMD::i32x4_arg c_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 fnmsub_i32x4(EmuSIMD::i32x4_arg a_, EmuSIMD::i32x4_arg b_, EmuSIMD::i32x4_arg c_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 fmaddsub_i32x4(EmuSIMD::i32x4_arg a_, EmuSIMD::i32x4_arg b_, EmuSIMD::i32x4_arg c_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 fmsubadd_i32x4(EmuSIMD::i32x4_arg a_, EmuSIMD::i32x4_arg b_, EmuSIMD::i32x4_arg c_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 floor_i32x4(EmuSIMD::i32x4_arg to_floor_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 ceil_i32x4(EmuSIMD::i32x4_arg to_ceil_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 trunc_i32x4(EmuSIMD::i32x4_arg to_trunc_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 mod_i32x4(EmuSIMD::i32x4_arg lhs_, EmuSIMD::i32x4_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 abs_i32x4(EmuSIMD::i32x4_arg in_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 sqrt_i32x4(EmuSIMD::i32x4_arg in_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 rsqrt_i32x4(EmuSIMD::i32x4_arg in_);
#pragma endregion

#pragma region NEAR_COMPARISONS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cmpnear_i32x4(EmuSIMD::i32x4_arg lhs_, EmuSIMD::i32x4_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cmpnear_i32x4(EmuSIMD::i32x4_arg lhs_, EmuSIMD::i32x4_arg rhs_, EmuSIMD::i32x4_arg epsilon);
#pragma endregion

#pragma region TRIG
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cos_i32x4(EmuSIMD::i32x4_arg in_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 sin_i32x4(EmuSIMD::i32x4_arg in_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 tan_i32x4(EmuSIMD::i32x4_arg in_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 acos_i32x4(EmuSIMD::i32x4_arg in_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 asin_i32x4(EmuSIMD::i32x4_arg in_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 atan_i32x4(EmuSIMD::i32x4_arg in_);
#pragma endregion

#pragma region ROUNDING_TEMPLATES
	template<int RoundingFlag_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 round_i32x4(EmuSIMD::i32x4_arg to_round_)
	{
		return to_round_;
	}
#pragma endregion

#pragma region SHUFFLE_TEMPLATES
	template<EmuSIMD::Funcs::shuffle_mask_type ShuffleMask_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 permute_i32x4(EmuSIMD::i32x4_arg a_)
	{
		return _mm_shuffle_epi32(a_, ShuffleMask_);
	}

	template<EmuSIMD::Funcs::shuffle_mask_type ShuffleMask_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 shuffle_i32x4(EmuSIMD::i32x4_arg a_, EmuSIMD::i32x4_arg b_)
	{
		return cast_f32x4_i32x4
		(
			shuffle_f32x4<ShuffleMask_>
			(
				cast_i32x4_f32x4(a_),
				cast_i32x4_f32x4(b_)
			)
		);
	}
#pragma endregion

#pragma region BLEND_TEMPLATES
	template<EmuSIMD::Funcs::blend_mask_type BlendMask_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 blend_i32x4(EmuSIMD::i32x4_arg a_, EmuSIMD::i32x4_arg b_)
	{
		return _mm_blend_epi32(a_, b_, BlendMask_);
	}
#pragma endregion

#pragma region TEMPLATE_HELPERS
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
	EMU_SIMD_COMMON_FUNC_SPEC auto emulate_fp_i32x4(Func_ func_, EmuSIMD::i32x4_arg in_)
		-> std::enable_if_t<std::is_invocable_r_v<EmuSIMD::f32x4, decltype(func_), EmuSIMD::f32x4>, EmuSIMD::i32x4>
	{
		return cvt_f32x4_i32x4
		(
			func_(cvt_i32x4_f32x4(in_))
		);
	}
#pragma endregion

#pragma region EXTRACTION_TEMPLATES
	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 extract_f32x4_lane_i32x4(f32x4_arg a_)
	{
		static_assert(Index_ == 0, "Invalid SIMD lane extraction index: Extracting i32x4 lane from a f32x4 instance; the maximum index is 0 but this index has been exceeded");
		return cast_f32x4_i32x4(a_);
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 extract_f32x8_lane_i32x4(f32x8_arg a_)
	{
		static_assert(Index_ <= 1, "Invalid SIMD lane extraction index: Extracting i32x4 lane from a f32x8 instance; the maximum index is 1 but this index has been exceeded.");
		if constexpr (Index_ == 0)
		{
			return cast_f32x8_i32x4(a_);
		}
		else
		{
			return cast_f32x4_i32x4(_mm256_extractf128_ps(a_, Index_));
		}
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 extract_f32x16_lane_i32x4(f32x16_arg a_)
	{
		static_assert(Index_ <= 3, "Invalid SIMD lane extraction index: Extracting i32x4 lane from a f32x16 instance; the maximum index is 3 but this index has been exceeded.");
		if constexpr (Index_ == 0)
		{
			return cast_f32x16_i32x4(a_);
		}
		else
		{
			return cast_f32x4_i32x4(_mm512_extractf32x4_ps(a_, Index_));
		}
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 extract_f64x2_lane_i32x4(f64x2_arg a_)
	{
		static_assert(Index_ == 0, "Invalid SIMD lane extraction index: Extracting i32x4 lane from a f64x2 instance; the maximum index is 0 but this index has been exceeded.");
		return cast_f64x2_i32x4(a_);
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 extract_f64x4_lane_i32x4(f64x4_arg a_)
	{
		static_assert(Index_ <= 1, "Invalid SIMD lane extraction index: Extracting i32x4 lane from a f64x4 instance; the maximum index is 1 but this index has been exceeded.");
		if constexpr (Index_ == 0)
		{
			return cast_f64x4_i32x4(a_);
		}
		else
		{
			return cast_f64x2_i32x4(_mm256_extractf128_pd(a_, Index_));
		}
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 extract_f64x8_lane_i32x4(f64x8_arg a_)
	{
		static_assert(Index_ <= 3, "Invalid SIMD lane extraction index: Extracting i32x4 lane from a f64x8 instance; the maximum index is 3 but this index has been exceeded.");
		if constexpr (Index_ == 0)
		{
			return cast_f64x8_i32x4(a_);
		}
		else
		{
			return cast_f64x2_i32x4(_mm512_extractf64x2_pd(a_, Index_));
		}
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 extract_i8x16_lane_i32x4(i8x16_arg a_)
	{
		static_assert(Index_ == 0, "Invalid SIMD lane extraction index: Extracting i32x4 lane from a i8x16 instance; the maximum index is 0 but this index has been exceeded.");
		return cast_i8x16_i32x4(a_);
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 extract_i8x32_lane_i32x4(i8x32_arg a_)
	{
		static_assert(Index_ <= 1, "Invalid SIMD lane extraction index: Extracting i32x4 lane from a i8x32 instance; the maximum index is 1 but this index has been exceeded.");
		if constexpr (Index_ == 0)
		{
			return cast_i8x32_i32x4(a_);
		}
		else
		{
			return _mm256_extracti128_si256(a_, Index_);
		}
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 extract_i8x64_lane_i32x4(i8x64_arg a_)
	{
		static_assert(Index_ <= 3, "Invalid SIMD lane extraction index: Extracting i32x4 lane from a i8x64 instance; the maximum index is 3 but this index has been exceeded.");
		if constexpr (Index_ == 0)
		{
			return cast_i8x64_i32x4(a_);
		}
		else
		{
			return _mm512_extracti32x4_epi32(a_, Index_);
		}
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 extract_i16x8_lane_i32x4(i16x8_arg a_)
	{
		static_assert(Index_ == 0, "Invalid SIMD lane extraction index: Extracting i32x4 lane from a i16x8 instance; the maximum index is 0 but this index has been exceeded.");
		return cast_i16x8_i32x4(a_);
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 extract_i16x16_lane_i32x4(i16x16_arg a_)
	{
		static_assert(Index_ <= 1, "Invalid SIMD lane extraction index: Extracting i32x4 lane from a i16x16 instance; the maximum index is 1 but this index has been exceeded.");
		if constexpr (Index_ == 0)
		{
			return cast_i16x16_i32x4(a_);
		}
		else
		{
			return _mm256_extracti128_si256(a_, Index_);
		}
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 extract_i16x32_lane_i32x4(i16x32_arg a_)
	{
		static_assert(Index_ <= 3, "Invalid SIMD lane extraction index: Extracting i32x4 lane from a i16x32 instance; the maximum index is 3 but this index has been exceeded.");
		if constexpr (Index_ == 0)
		{
			return cast_i16x32_i32x4(a_);
		}
		else
		{
			return _mm512_extracti32x4_epi32(a_, Index_);
		}
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 extract_i32x4_lane_i32x4(i32x4_arg a_)
	{
		static_assert(Index_ == 0, "Invalid SIMD lane extraction index: Extracting i32x4 lane from a i32x4 instance; the maximum index is 0 but this index has been exceeded.");
		return a_;
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 extract_i32x8_lane_i32x4(i32x8_arg a_)
	{
		static_assert(Index_ <= 1, "Invalid SIMD lane extraction index: Extracting i32x4 lane from a i32x8 instance; the maximum index is 1 but this index has been exceeded.");
		if constexpr (Index_ == 0)
		{
			return cast_i32x8_i32x4(a_);
		}
		else
		{
			return _mm256_extracti128_si256(a_, Index_);
		}
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 extract_i32x16_lane_i32x4(i32x16_arg a_)
	{
		static_assert(Index_ <= 3, "Invalid SIMD lane extraction index: Extracting i32x4 lane from a i32x16 instance; the maximum index is 3 but this index has been exceeded.");
		if constexpr (Index_ == 0)
		{
			return cast_i32x16_i32x4(a_);
		}
		else
		{
			return _mm512_extracti32x4_epi32(a_, Index_);
		}
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 extract_i64x2_lane_i32x4(i64x2_arg a_)
	{
		static_assert(Index_ == 0, "Invalid SIMD lane extraction index: Extracting i32x4 lane from a i64x2 instance; the maximum index is 0 but this index has been exceeded.");
		return cast_i64x2_i32x4(a_);
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 extract_i64x4_lane_i32x4(i64x4_arg a_)
	{
		static_assert(Index_ <= 1, "Invalid SIMD lane extraction index: Extracting i32x4 lane from a i64x4 instance; the maximum index is 1 but this index has been exceeded.");
		if constexpr (Index_ == 0)
		{
			return cast_i64x4_i32x4(a_);
		}
		else
		{
			return _mm256_extracti128_si256(a_, Index_);
		}
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 extract_i64x8_lane_i32x4(i64x8_arg a_)
	{
		static_assert(Index_ <= 3, "Invalid SIMD lane extraction index: Extracting i32x4 lane from a i64x8 instance; the maximum index is 3 but this index has been exceeded.");
		if constexpr (Index_ == 0)
		{
			return cast_i64x8_i32x4(a_);
		}
		else
		{
			return _mm512_extracti32x4_epi32(a_, Index_);
		}
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 extract_u8x16_lane_i32x4(u8x16_arg a_)
	{
		static_assert(Index_ == 0, "Invalid SIMD lane extraction index: Extracting i32x4 lane from a u8x16 instance; the maximum index is 0 but this index has been exceeded.");
		return cast_u8x16_i32x4(a_);
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 extract_u8x32_lane_i32x4(u8x32_arg a_)
	{
		static_assert(Index_ <= 1, "Invalid SIMD lane extraction index: Extracting i32x4 lane from a u8x32 instance; the maximum index is 1 but this index has been exceeded.");
		if constexpr (Index_ == 0)
		{
			return cast_u8x32_i32x4(a_);
		}
		else
		{
			return _mm256_extracti128_si256(a_, Index_);
		}
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 extract_u8x64_lane_i32x4(u8x64_arg a_)
	{
		static_assert(Index_ <= 3, "Invalid SIMD lane extraction index: Extracting i32x4 lane from a u8x64 instance; the maximum index is 3 but this index has been exceeded.");
		if constexpr (Index_ == 0)
		{
			return cast_u8x64_i32x4(a_);
		}
		else
		{
			return _mm512_extracti32x4_epi32(a_, Index_);
		}
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 extract_u16x8_lane_i32x4(u16x8_arg a_)
	{
		static_assert(Index_ == 0, "Invalid SIMD lane extraction index: Extracting i32x4 lane from a u16x8 instance; the maximum index is 0 but this index has been exceeded.");
		return cast_u16x8_i32x4(a_);
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 extract_u16x16_lane_i32x4(u16x16_arg a_)
	{
		static_assert(Index_ <= 1, "Invalid SIMD lane extraction index: Extracting i32x4 lane from a u16x16 instance; the maximum index is 1 but this index has been exceeded.");
		if constexpr (Index_ == 0)
		{
			return cast_u16x16_i32x4(a_);
		}
		else
		{
			return _mm256_extracti128_si256(a_, Index_);
		}
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 extract_u16x32_lane_i32x4(u16x32_arg a_)
	{
		static_assert(Index_ <= 3, "Invalid SIMD lane extraction index: Extracting i32x4 lane from a u16x32 instance; the maximum index is 3 but this index has been exceeded.");
		if constexpr (Index_ == 0)
		{
			return cast_u16x32_i32x4(a_);
		}
		else
		{
			return _mm512_extracti32x4_epi32(a_, Index_);
		}
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 extract_u32x4_lane_i32x4(u32x4_arg a_)
	{
		static_assert(Index_ == 0, "Invalid SIMD lane extraction index: Extracting i32x4 lane from a i8x16 instance; the maximum index is 0 but this index has been exceeded.");
		return cast_u32x4_i32x4(a_);
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 extract_u32x8_lane_i32x4(u32x8_arg a_)
	{
		static_assert(Index_ <= 1, "Invalid SIMD lane extraction index: Extracting i32x4 lane from a u32x8 instance; the maximum index is 1 but this index has been exceeded.");
		if constexpr (Index_ == 0)
		{
			return cast_u32x8_i32x4(a_);
		}
		else
		{
			return _mm256_extracti128_si256(a_, Index_);
		}
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 extract_u32x16_lane_i32x4(u32x16_arg a_)
	{
		static_assert(Index_ <= 3, "Invalid SIMD lane extraction index: Extracting i32x4 lane from a ui8x16 instance; the maximum index is 3 but this index has been exceeded.");
		if constexpr (Index_ == 0)
		{
			return cast_u32x16_i32x4(a_);
		}
		else
		{
			return _mm512_extracti32x4_epi32(a_, Index_);
		}
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 extract_u64x2_lane_i32x4(u64x2_arg a_)
	{
		static_assert(Index_ == 0, "Invalid SIMD lane extraction index: Extracting i32x4 lane from a u64x2 instance; the maximum index is 0 but this index has been exceeded.");
		return cast_u64x2_i32x4(a_);
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 extract_u64x4_lane_i32x4(u64x4_arg a_)
	{
		static_assert(Index_ <= 1, "Invalid SIMD lane extraction index: Extracting i32x4 lane from a u64x4 instance; the maximum index is 1 but this index has been exceeded.");
		if constexpr (Index_ == 0)
		{
			return cast_u64x4_i32x4(a_);
		}
		else
		{
			return _mm256_extracti128_si256(a_, Index_);
		}
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 extract_u64x8_lane_i32x4(u64x8_arg a_)
	{
		static_assert(Index_ <= 3, "Invalid SIMD lane extraction index: Extracting i32x4 lane from a u64x8 instance; the maximum index is 3 but this index has been exceeded.");
		if constexpr (Index_ == 0)
		{
			return cast_u64x8_i32x4(a_);
		}
		else
		{
			return _mm512_extracti32x4_epi32(a_, Index_);
		}
	}
#pragma endregion

#pragma region GET_TEMPLATES
	template<std::size_t Index_, typename OutT_ = std::int32_t>
	EMU_SIMD_COMMON_FUNC_SPEC auto extract_element_i32x4(i32x4_arg in_)
		-> typename std::remove_cvref<OutT_>::type
	{
		if constexpr (Index_ == 0)
		{
			return static_cast<typename std::remove_cvref<OutT_>::type>(EmuSIMD::Funcs::get_first_i32x4(in_));
		}
		else
		{
			if constexpr (Index_ <= 3)
			{
#if EMU_SIMD_USE_128_REGISTERS
				return static_cast<typename std::remove_cvref<OutT_>::type>(_mm_extract_epi32(in_, Index_));
#else
				return EmuSIMD::_underlying_impl::retrieve_emulated_single_lane_simd_element<OutT_, Index_, false>(in_);
#endif
			}
			else
			{
				static_assert
				(
					EmuCore::TMP::get_false<std::size_t, Index_>(),
					"Invalid index provided when extracting an element from a i32x4 instance. Valid indices are 0, 1, 2, 3."
				);
			}
		}
	}
#pragma endregion
}

#endif
