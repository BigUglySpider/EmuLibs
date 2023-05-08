#ifndef EMU_SIMD_GENERIC_FUNCS_I32X8_DECL_H_INC_
#define EMU_SIMD_GENERIC_FUNCS_I32X8_DECL_H_INC_ 1

#include "../_common_generic_func_helpers.h"
#include "_decl_f32x8.h"

namespace EmuSIMD::Funcs
{
#pragma region SETTERS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 set_i32x8
	(
		std::int32_t e0, std::int32_t e1, std::int32_t e2, std::int32_t e3, std::int32_t e4, std::int32_t e5, std::int32_t e6, std::int32_t e7
	);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 setr_i32x8
	(
		std::int32_t e0, std::int32_t e1, std::int32_t e2, std::int32_t e3, std::int32_t e4, std::int32_t e5, std::int32_t e6, std::int32_t e7
	);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 set1_i32x8(std::int32_t all_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 load_i32x8(const std::int32_t* p_to_load_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 aligned_load_i32x8(const std::int32_t* p_to_load_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 setzero_i32x8();
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 setmasked_i32x8(std::uint8_t bit_mask_);
#pragma endregion

#pragma region STORES
	EMU_SIMD_COMMON_FUNC_SPEC void store_i32x8(std::int32_t* p_out_, i32x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC void aligned_store_i32x8(std::int32_t* p_out_, i32x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC std::int32_t get_first_i32x8(i32x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC std::uint8_t movemask_i32x8(i32x8_arg a_);
#pragma endregion

#pragma region CASTS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 cast_f32x4_i32x8(f32x4_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 cast_f32x8_i32x8(f32x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 cast_f32x16_i32x8(f32x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 cast_f64x2_i32x8(f64x2_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 cast_f64x4_i32x8(f64x4_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 cast_f64x8_i32x8(f64x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 cast_i8x16_i32x8(i8x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 cast_i16x8_i32x8(i16x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 cast_i32x4_i32x8(i32x4_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 cast_i64x2_i32x8(i64x2_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 cast_i8x32_i32x8(i8x32_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 cast_i16x16_i32x8(i16x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 cast_i32x8_i32x8(i32x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 cast_i64x4_i32x8(i64x4_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 cast_i8x64_i32x8(i8x64_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 cast_i16x32_i32x8(i16x32_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 cast_i32x16_i32x8(i32x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 cast_i64x8_i32x8(i64x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 cast_u8x16_i32x8(u8x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 cast_u16x8_i32x8(u16x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 cast_u32x4_i32x8(u32x4_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 cast_u64x2_i32x8(u64x2_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 cast_u8x32_i32x8(u8x32_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 cast_u16x16_i32x8(u16x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 cast_u32x8_i32x8(u32x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 cast_u64x4_i32x8(u64x4_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 cast_u8x64_i32x8(u8x64_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 cast_u16x32_i32x8(u16x32_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 cast_u32x16_i32x8(u32x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 cast_u64x8_i32x8(u64x8_arg a_);
#pragma endregion

#pragma region CONVERSIONS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 cvt_f32x4_i32x8(f32x4_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 cvt_f32x8_i32x8(f32x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 cvt_f32x16_i32x8(f32x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 cvt_f64x2_i32x8(f64x2_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 cvt_f64x4_i32x8(f64x4_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 cvt_f64x8_i32x8(f64x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 cvt_i8x16_i32x8(i8x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 cvt_i16x8_i32x8(i16x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 cvt_i32x4_i32x8(i32x4_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 cvt_i64x2_i32x8(i64x2_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 cvt_i8x32_i32x8(i8x32_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 cvt_i16x16_i32x8(i16x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 cvt_i32x8_i32x8(i32x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 cvt_i64x4_i32x8(i64x4_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 cvt_i8x64_i32x8(i8x64_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 cvt_i16x32_i32x8(i16x32_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 cvt_i32x16_i32x8(i32x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 cvt_i64x8_i32x8(i64x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 cvt_u8x16_i32x8(u8x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 cvt_u16x8_i32x8(u16x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 cvt_u32x4_i32x8(u32x4_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 cvt_u64x2_i32x8(u64x2_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 cvt_u8x32_i32x8(u8x32_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 cvt_u16x16_i32x8(u16x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 cvt_u32x8_i32x8(u32x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 cvt_u64x4_i32x8(u64x4_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 cvt_u8x64_i32x8(u8x64_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 cvt_u16x32_i32x8(u16x32_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 cvt_u32x16_i32x8(u32x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 cvt_u64x8_i32x8(u64x8_arg a_);
#pragma endregion

#pragma region COMPARISONS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 cmpeq_i32x8(EmuSIMD::i32x8_arg lhs_, EmuSIMD::i32x8_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 cmpneq_i32x8(EmuSIMD::i32x8_arg lhs_, EmuSIMD::i32x8_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 cmpgt_i32x8(EmuSIMD::i32x8_arg lhs_, EmuSIMD::i32x8_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 cmplt_i32x8(EmuSIMD::i32x8_arg lhs_, EmuSIMD::i32x8_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 cmpge_i32x8(EmuSIMD::i32x8_arg lhs_, EmuSIMD::i32x8_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 cmple_i32x8(EmuSIMD::i32x8_arg lhs_, EmuSIMD::i32x8_arg rhs_);
#pragma endregion

#pragma region MOVES
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 movehl_i32x8(EmuSIMD::i32x8_arg lhs_, EmuSIMD::i32x8_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 movelh_i32x8(EmuSIMD::i32x8_arg lhs_, EmuSIMD::i32x8_arg rhs_);
#pragma endregion

#pragma region BITWISE_ARITHMETIC
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 and_i32x8(EmuSIMD::i32x8_arg lhs_, EmuSIMD::i32x8_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 or_i32x8(EmuSIMD::i32x8_arg lhs_, EmuSIMD::i32x8_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 xor_i32x8(EmuSIMD::i32x8_arg lhs_, EmuSIMD::i32x8_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 andnot_i32x8(EmuSIMD::i32x8_arg not_lhs_, EmuSIMD::i32x8_arg rhs_);
	template<std::int32_t NumShifts_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 shift_left_i32x8(EmuSIMD::i32x8_arg lhs_);
	template<std::int32_t NumShifts_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 shift_right_arithmetic_i32x8(EmuSIMD::i32x8_arg lhs_);
	template<std::int32_t NumShifts_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 shift_right_logical_i32x8(EmuSIMD::i32x8_arg lhs_);
#pragma endregion

#pragma region BLENDS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 blendv_i32x8(EmuSIMD::i32x8_arg a_, EmuSIMD::i32x8_arg b_, EmuSIMD::i32x8_arg shuffle_mask_vec_);
#pragma endregion

#pragma region MINMAX_FUNCS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 min_i32x8(EmuSIMD::i32x8_arg a_, EmuSIMD::i32x8_arg b_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 max_i32x8(EmuSIMD::i32x8_arg a_, EmuSIMD::i32x8_arg b_);
#pragma endregion

#pragma region BASIC_ARITHMETIC
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 mul_all_i32x8(EmuSIMD::i32x8_arg lhs_, EmuSIMD::i32x8_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 negate_i32x8(EmuSIMD::i32x8_arg to_negate_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 add_i32x8(EmuSIMD::i32x8_arg lhs_, EmuSIMD::i32x8_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 sub_i32x8(EmuSIMD::i32x8_arg lhs_, EmuSIMD::i32x8_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 mul_i32x8(EmuSIMD::i32x8_arg lhs_, EmuSIMD::i32x8_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 div_i32x8(EmuSIMD::i32x8_arg lhs_, EmuSIMD::i32x8_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 addsub_i32x8(EmuSIMD::i32x8_arg lhs_, EmuSIMD::i32x8_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 subadd_i32x8(EmuSIMD::i32x8_arg lhs_, EmuSIMD::i32x8_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 fmadd_i32x8(EmuSIMD::i32x8_arg a_, EmuSIMD::i32x8_arg b_, EmuSIMD::i32x8_arg c_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 fmsub_i32x8(EmuSIMD::i32x8_arg a_, EmuSIMD::i32x8_arg b_, EmuSIMD::i32x8_arg c_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 fnmadd_i32x8(EmuSIMD::i32x8_arg a_, EmuSIMD::i32x8_arg b_, EmuSIMD::i32x8_arg c_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 fnmsub_i32x8(EmuSIMD::i32x8_arg a_, EmuSIMD::i32x8_arg b_, EmuSIMD::i32x8_arg c_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 fmaddsub_i32x8(EmuSIMD::i32x8_arg a_, EmuSIMD::i32x8_arg b_, EmuSIMD::i32x8_arg c_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 fmsubadd_i32x8(EmuSIMD::i32x8_arg a_, EmuSIMD::i32x8_arg b_, EmuSIMD::i32x8_arg c_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 floor_i32x8(EmuSIMD::i32x8_arg to_floor_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 ceil_i32x8(EmuSIMD::i32x8_arg to_ceil_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 trunc_i32x8(EmuSIMD::i32x8_arg to_trunc_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 mod_i32x8(EmuSIMD::i32x8_arg lhs_, EmuSIMD::i32x8_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 abs_i32x8(EmuSIMD::i32x8_arg in_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 sqrt_i32x8(EmuSIMD::i32x8_arg in_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 rsqrt_i32x8(EmuSIMD::i32x8_arg in_);
#pragma endregion

#pragma region NEAR_COMPARISONS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 cmpnear_i32x8(EmuSIMD::i32x8_arg lhs_, EmuSIMD::i32x8_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 cmpnear_i32x8(EmuSIMD::i32x8_arg lhs_, EmuSIMD::i32x8_arg rhs_, EmuSIMD::i32x8_arg epsilon);
#pragma endregion

#pragma region TRIG
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 cos_i32x8(EmuSIMD::i32x8_arg in_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 sin_i32x8(EmuSIMD::i32x8_arg in_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 tan_i32x8(EmuSIMD::i32x8_arg in_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 acos_i32x8(EmuSIMD::i32x8_arg in_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 asin_i32x8(EmuSIMD::i32x8_arg in_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 atan_i32x8(EmuSIMD::i32x8_arg in_);
#pragma endregion

#pragma region ROUNDING_TEMPLATES
	template<int RoundingFlag_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 round_i32x8(EmuSIMD::i32x8_arg to_round_)
	{
		return to_round_;
	}
#pragma endregion

#pragma region SHUFFLE_TEMPLATES
	template<EmuSIMD::Funcs::shuffle_mask_type ShuffleMask_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 permute_i32x8(EmuSIMD::i32x8_arg a_)
	{
		return _mm256_shuffle_epi32(a_, ShuffleMask_);
	}

	template<EmuSIMD::Funcs::shuffle_mask_type ShuffleMask_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 shuffle_i32x8(EmuSIMD::i32x8_arg a_, EmuSIMD::i32x8_arg b_)
	{
		return cast_f32x8_i32x8
		(
			shuffle_f32x8<ShuffleMask_>
			(
				cast_i32x8_f32x8(a_),
				cast_i32x8_f32x8(b_)
			)
		);
	}
#pragma endregion

#pragma region BLEND_FUNCS
	template<EmuSIMD::Funcs::blend_mask_type BlendMask_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 blend_i32x8(EmuSIMD::i32x8_arg a_, EmuSIMD::i32x8_arg b_)
	{
		return _mm256_blend_epi32(a_, b_, BlendMask_);
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
	EMU_SIMD_COMMON_FUNC_SPEC auto emulate_fp_i32x8(Func_ func_, EmuSIMD::i32x8_arg in_)
		-> std::enable_if_t<std::is_invocable_r_v<EmuSIMD::f32x8, decltype(func_), EmuSIMD::f32x8>, EmuSIMD::i32x8>
	{
		return cvt_f32x8_i32x8
		(
			func_(cvt_i32x8_f32x8(in_))
		);
	}
#pragma endregion

#pragma region EXTRACTION_TEMPLATES
	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 extract_f32x8_lane_i32x8(f32x8_arg a_)
	{
		static_assert(Index_ == 0, "Invalid SIMD lane extraction index: Extracting i32x8 lane from a f32x8 instance; the maximum index is 0 but this index has been exceeded.");
		return cast_f32x8_i32x8(a_);
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 extract_f32x16_lane_i32x8(f32x16_arg a_)
	{
		static_assert(Index_ <= 1, "Invalid SIMD lane extraction index: Extracting i32x8 lane from a f32x16 instance; the maximum index is 1 but this index has been exceeded.");
		if constexpr (Index_ == 0)
		{
			return cast_f32x16_i32x8(a_);
		}
		else
		{
			return cast_f32x8_i32x8(_mm512_extractf32x8_ps(a_, Index_));
		}
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 extract_f64x4_lane_i32x8(f64x4_arg a_)
	{
		static_assert(Index_ == 0, "Invalid SIMD lane extraction index: Extracting i32x8 lane from a f64x4 instance; the maximum index is 0 but this index has been exceeded.");
		return cast_f64x4_i32x8(a_);
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 extract_f64x8_lane_i32x8(f64x8_arg a_)
	{
		static_assert(Index_ <= 1, "Invalid SIMD lane extraction index: Extracting i32x8 lane from a f64x8 instance; the maximum index is 1 but this index has been exceeded.");
		if constexpr (Index_ == 0)
		{
			return cast_f64x8_i32x8(a_);
		}
		else
		{
			return cast_f64x4_i32x8(_mm512_extractf64x4_pd(a_, Index_));
		}
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 extract_i8x32_lane_i32x8(i8x32_arg a_)
	{
		static_assert(Index_ == 0, "Invalid SIMD lane extraction index: Extracting i32x8 lane from a i8x32 instance; the maximum index is 0 but this index has been exceeded.");
		return cast_i8x32_i32x8(a_);
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 extract_i8x64_lane_i32x8(i8x64_arg a_)
	{
		static_assert(Index_ <= 1, "Invalid SIMD lane extraction index: Extracting i32x8 lane from a i8x64 instance; the maximum index is 1 but this index has been exceeded.");
		if constexpr (Index_ == 0)
		{
			return cast_i8x64_i32x8(a_);
		}
		else
		{
			return _mm512_extracti32x8_epi32(a_, Index_);
		}
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 extract_i16x16_lane_i32x8(i16x16_arg a_)
	{
		static_assert(Index_ == 0, "Invalid SIMD lane extraction index: Extracting i32x8 lane from a i16x16 instance; the maximum index is 0 but this index has been exceeded.");
		return cast_i16x16_i32x8(a_);
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 extract_i16x32_lane_i32x8(i16x32_arg a_)
	{
		static_assert(Index_ <= 1, "Invalid SIMD lane extraction index: Extracting i32x8 lane from a i16x32 instance; the maximum index is 1 but this index has been exceeded.");
		if constexpr (Index_ == 0)
		{
			return cast_i16x32_i32x8(a_);
		}
		else
		{
			return _mm512_extracti32x8_epi32(a_, Index_);
		}
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 extract_i32x8_lane_i32x8(i32x8_arg a_)
	{
		static_assert(Index_ == 0, "Invalid SIMD lane extraction index: Extracting i32x8 lane from a i32x8 instance; the maximum index is 0 but this index has been exceeded.");
		return a_;
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 extract_i32x16_lane_i32x8(i32x16_arg a_)
	{
		static_assert(Index_ <= 1, "Invalid SIMD lane extraction index: Extracting i32x8 lane from a i32x16 instance; the maximum index is 1 but this index has been exceeded.");
		if constexpr (Index_ == 0)
		{
			return cast_i32x16_i32x8(a_);
		}
		else
		{
			return _mm512_extracti32x8_epi32(a_, Index_);
		}
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 extract_i64x4_lane_i32x8(i64x4_arg a_)
	{
		static_assert(Index_ == 0, "Invalid SIMD lane extraction index: Extracting i32x8 lane from a i64x4 instance; the maximum index is 0 but this index has been exceeded.");
		return cast_i64x4_i32x8(a_);
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 extract_i64x8_lane_i32x8(i64x8_arg a_)
	{
		static_assert(Index_ <= 1, "Invalid SIMD lane extraction index: Extracting i32x8 lane from a i64x8 instance; the maximum index is 1 but this index has been exceeded.");
		if constexpr (Index_ == 0)
		{
			return cast_i64x8_i32x8(a_);
		}
		else
		{
			return _mm512_extracti32x8_epi32(a_, Index_);
		}
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 extract_u8x32_lane_i32x8(u8x32_arg a_)
	{
		static_assert(Index_ == 0, "Invalid SIMD lane extraction index: Extracting i32x8 lane from a u8x32 instance; the maximum index is 0 but this index has been exceeded.");
		return cast_u8x32_i32x8(a_);
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 extract_u8x64_lane_i32x8(u8x64_arg a_)
	{
		static_assert(Index_ <= 1, "Invalid SIMD lane extraction index: Extracting i32x8 lane from a u8x64 instance; the maximum index is 1 but this index has been exceeded.");
		if constexpr (Index_ == 0)
		{
			return cast_u8x64_i32x8(a_);
		}
		else
		{
			return _mm512_extracti32x8_epi32(a_, Index_);
		}
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 extract_u16x16_lane_i32x8(u16x16_arg a_)
	{
		static_assert(Index_ == 0, "Invalid SIMD lane extraction index: Extracting i32x8 lane from a u16x16 instance; the maximum index is 0 but this index has been exceeded.");
		return cast_u16x16_i32x8(a_);
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 extract_u16x32_lane_i32x8(u16x32_arg a_)
	{
		static_assert(Index_ <= 1, "Invalid SIMD lane extraction index: Extracting i32x8 lane from a u16x32 instance; the maximum index is 1 but this index has been exceeded.");
		if constexpr (Index_ == 0)
		{
			return cast_u16x32_i32x8(a_);
		}
		else
		{
			return _mm512_extracti32x8_epi32(a_, Index_);
		}
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 extract_u32x8_lane_i32x8(u32x8_arg a_)
	{
		static_assert(Index_ == 0, "Invalid SIMD lane extraction index: Extracting i32x8 lane from a u32x8 instance; the maximum index is 0 but this index has been exceeded.");
		return cast_u32x8_i32x8(a_);
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 extract_u32x16_lane_i32x8(u32x16_arg a_)
	{
		static_assert(Index_ <= 1, "Invalid SIMD lane extraction index: Extracting i32x8 lane from a u32x16 instance; the maximum index is 1 but this index has been exceeded.");
		if constexpr (Index_ == 0)
		{
			return cast_u32x16_i32x8(a_);
		}
		else
		{
			return _mm512_extracti32x8_epi32(a_, Index_);
		}
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 extract_u64x4_lane_i32x8(u64x4_arg a_)
	{
		static_assert(Index_ == 0, "Invalid SIMD lane extraction index: Extracting i32x8 lane from a u64x4 instance; the maximum index is 0 but this index has been exceeded.");
		return cast_u64x4_i32x8(a_);
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 extract_u64x8_lane_i32x8(u64x8_arg a_)
	{
		static_assert(Index_ <= 1, "Invalid SIMD lane extraction index: Extracting i32x8 lane from a u64x8 instance; the maximum index is 1 but this index has been exceeded.");
		if constexpr (Index_ == 0)
		{
			return cast_u64x8_i32x8(a_);
		}
		else
		{
			return _mm512_extracti32x8_epi32(a_, Index_);
		}
	}
#pragma endregion

#pragma region GET_TEMPLATES
	template<std::size_t Index_, typename OutT_ = std::int32_t>
	EMU_SIMD_COMMON_FUNC_SPEC auto extract_element_i32x8(i32x8_arg in_)
		-> typename std::remove_cvref<OutT_>::type
	{
		if constexpr (Index_ == 0)
		{
			return static_cast<typename std::remove_cvref<OutT_>::type>(EmuSIMD::Funcs::get_first_i32x8(in_));
		}
		else
		{
			if constexpr (Index_ <= 7)
			{
#if EMU_SIMD_USE_256_REGISTERS
				return static_cast<typename std::remove_cvref<OutT_>::type>(_mm256_extract_epi32(in_, Index_));
#else
				return EmuSIMD::_underlying_impl::retrieve_emulated_dual_lane_simd_element<OutT_, Index_, false, 4>(in_);
#endif
			}
			else
			{
				static_assert
				(
					EmuCore::TMP::get_false<std::size_t, Index_>(),
					"Invalid index provided when extracting an element from a i32x8 instance. Valid indices are 0, 1, 2, 3, 4, 5, 6, 7."
				);
			}
		}
	}
#pragma endregion
}

#endif
