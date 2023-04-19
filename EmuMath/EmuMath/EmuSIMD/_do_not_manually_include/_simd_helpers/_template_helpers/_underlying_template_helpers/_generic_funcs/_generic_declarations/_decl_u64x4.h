#ifndef EMU_SIMD_GENERIC_FUNCS_U64X4_DECL_H_INC_
#define EMU_SIMD_GENERIC_FUNCS_U64X4_DECL_H_INC_ 1

#include "../_common_generic_func_helpers.h"
#include "_decl_f64x4.h"

namespace EmuSIMD::Funcs
{
#pragma region SETTERS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x4 set_u64x4(std::uint64_t e0, std::uint64_t e1, std::uint64_t e2, std::uint64_t e3);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x4 setr_u64x4(std::uint64_t e0, std::uint64_t e1, std::uint64_t e2, std::uint64_t e3);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x4 set1_u64x4(std::uint64_t all_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x4 load_u64x4(const std::uint64_t* p_to_load_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x4 setzero_u64x4();
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x4 setmasked_u64x4(std::uint8_t bit_mask_);
#pragma endregion

#pragma region STORES
	EMU_SIMD_COMMON_FUNC_SPEC void store_u64x4(std::uint64_t* p_out_, u64x4_arg a_);
#pragma endregion

#pragma region CASTS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x4 cast_f32x4_u64x4(f32x4_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x4 cast_f32x8_u64x4(f32x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x4 cast_f32x16_u64x4(f32x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x4 cast_f64x2_u64x4(f64x2_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x4 cast_f64x4_u64x4(f64x4_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x4 cast_f64x8_u64x4(f64x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x4 cast_i8x16_u64x4(i8x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x4 cast_i16x8_u64x4(i16x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x4 cast_i32x4_u64x4(i32x4_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x4 cast_i64x2_u64x4(i64x2_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x4 cast_i8x32_u64x4(i8x32_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x4 cast_i16x16_u64x4(i16x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x4 cast_i32x8_u64x4(i32x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x4 cast_i64x4_u64x4(i64x4_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x4 cast_i8x64_u64x4(i8x64_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x4 cast_i16x32_u64x4(i16x32_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x4 cast_i32x16_u64x4(i32x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x4 cast_i64x8_u64x4(i64x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x4 cast_u8x16_u64x4(u8x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x4 cast_u16x8_u64x4(u16x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x4 cast_u32x4_u64x4(u32x4_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x4 cast_u64x2_u64x4(u64x2_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x4 cast_u8x32_u64x4(u8x32_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x4 cast_u16x16_u64x4(u16x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x4 cast_u32x8_u64x4(u32x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x4 cast_u64x4_u64x4(u64x4_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x4 cast_u8x64_u64x4(u8x64_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x4 cast_u16x32_u64x4(u16x32_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x4 cast_u32x16_u64x4(u32x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x4 cast_u64x8_u64x4(u64x8_arg a_);
#pragma endregion

#pragma region CONVERSIONS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x4 cvt_f32x4_u64x4(f32x4_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x4 cvt_f32x8_u64x4(f32x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x4 cvt_f32x16_u64x4(f32x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x4 cvt_f64x2_u64x4(f64x2_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x4 cvt_f64x4_u64x4(f64x4_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x4 cvt_f64x8_u64x4(f64x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x4 cvt_i8x16_u64x4(i8x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x4 cvt_i16x8_u64x4(i16x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x4 cvt_i32x4_u64x4(i32x4_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x4 cvt_i64x2_u64x4(i64x2_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x4 cvt_i8x32_u64x4(i8x32_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x4 cvt_i16x16_u64x4(i16x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x4 cvt_i32x8_u64x4(i32x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x4 cvt_i64x4_u64x4(i64x4_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x4 cvt_i8x64_u64x4(i8x64_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x4 cvt_i16x32_u64x4(i16x32_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x4 cvt_i32x16_u64x4(i32x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x4 cvt_i64x8_u64x4(i64x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x4 cvt_u8x16_u64x4(u8x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x4 cvt_u16x8_u64x4(u16x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x4 cvt_u32x4_u64x4(u32x4_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x4 cvt_u64x2_u64x4(u64x2_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x4 cvt_u8x32_u64x4(u8x32_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x4 cvt_u16x16_u64x4(u16x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x4 cvt_u32x8_u64x4(u32x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x4 cvt_u64x4_u64x4(u64x4_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x4 cvt_u8x64_u64x4(u8x64_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x4 cvt_u16x32_u64x4(u16x32_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x4 cvt_u32x16_u64x4(u32x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x4 cvt_u64x8_u64x4(u64x8_arg a_);
#pragma endregion

#pragma region COMPARISONS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x4 cmpeq_u64x4(EmuSIMD::u64x4_arg lhs_, EmuSIMD::u64x4_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x4 cmpneq_u64x4(EmuSIMD::u64x4_arg lhs_, EmuSIMD::u64x4_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x4 cmpgt_u64x4(EmuSIMD::u64x4_arg lhs_, EmuSIMD::u64x4_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x4 cmplt_u64x4(EmuSIMD::u64x4_arg lhs_, EmuSIMD::u64x4_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x4 cmpge_u64x4(EmuSIMD::u64x4_arg lhs_, EmuSIMD::u64x4_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x4 cmple_u64x4(EmuSIMD::u64x4_arg lhs_, EmuSIMD::u64x4_arg rhs_);
#pragma endregion

#pragma region MOVES
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x4 movehl_u64x4(EmuSIMD::u64x4_arg lhs_, EmuSIMD::u64x4_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x4 movelh_u64x4(EmuSIMD::u64x4_arg lhs_, EmuSIMD::u64x4_arg rhs_);
#pragma endregion
	
#pragma region BLENDS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x4 bleudv_i64x4(EmuSIMD::u64x4_arg a_, EmuSIMD::u64x4_arg b_, EmuSIMD::u64x4_arg shuffle_mask_vec_);
#pragma endregion

#pragma region MINMAX_FUNCS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x4 min_u64x4(EmuSIMD::u64x4_arg a_, EmuSIMD::u64x4_arg b_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x4 max_u64x4(EmuSIMD::u64x4_arg a_, EmuSIMD::u64x4_arg b_);
#pragma endregion

#pragma region BASIC_ARITHMETIC
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x4 mul_all_u64x4(EmuSIMD::u64x4_arg lhs_, EmuSIMD::u64x4_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x4 negate_u64x4(EmuSIMD::u64x4_arg to_negate_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x4 add_u64x4(EmuSIMD::u64x4_arg lhs_, EmuSIMD::u64x4_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x4 sub_u64x4(EmuSIMD::u64x4_arg lhs_, EmuSIMD::u64x4_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x4 mul_u64x4(EmuSIMD::u64x4_arg lhs_, EmuSIMD::u64x4_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x4 div_u64x4(EmuSIMD::u64x4_arg lhs_, EmuSIMD::u64x4_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x4 addsub_u64x4(EmuSIMD::u64x4_arg lhs_, EmuSIMD::u64x4_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x4 subadd_u64x4(EmuSIMD::u64x4_arg lhs_, EmuSIMD::u64x4_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x4 fmadd_u64x4(EmuSIMD::u64x4_arg a_, EmuSIMD::u64x4_arg b_, EmuSIMD::u64x4_arg c_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x4 fmsub_u64x4(EmuSIMD::u64x4_arg a_, EmuSIMD::u64x4_arg b_, EmuSIMD::u64x4_arg c_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x4 fnmadd_u64x4(EmuSIMD::u64x4_arg a_, EmuSIMD::u64x4_arg b_, EmuSIMD::u64x4_arg c_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x4 fnmsub_u64x4(EmuSIMD::u64x4_arg a_, EmuSIMD::u64x4_arg b_, EmuSIMD::u64x4_arg c_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x4 fmaddsub_u64x4(EmuSIMD::u64x4_arg a_, EmuSIMD::u64x4_arg b_, EmuSIMD::u64x4_arg c_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x4 fmsubadd_u64x4(EmuSIMD::u64x4_arg a_, EmuSIMD::u64x4_arg b_, EmuSIMD::u64x4_arg c_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x4 floor_u64x4(EmuSIMD::u64x4_arg to_floor_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x4 ceil_u64x4(EmuSIMD::u64x4_arg to_ceil_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x4 trunc_u64x4(EmuSIMD::u64x4_arg to_trunc_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x4 mod_u64x4(EmuSIMD::u64x4_arg lhs_, EmuSIMD::u64x4_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x4 abs_u64x4(EmuSIMD::u64x4_arg in_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x4 sqrt_u64x4(EmuSIMD::u64x4_arg in_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x4 rsqrt_u64x4(EmuSIMD::u64x4_arg in_);
#pragma endregion

#pragma region NEAR_COMPARISONS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x4 cmpnear_u64x4(EmuSIMD::u64x4_arg lhs_, EmuSIMD::u64x4_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x4 cmpnear_u64x4(EmuSIMD::u64x4_arg lhs_, EmuSIMD::u64x4_arg rhs_, EmuSIMD::u64x4_arg epsilon);
#pragma endregion

#pragma region TRIG
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x4 cos_u64x4(EmuSIMD::u64x4_arg in_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x4 sin_u64x4(EmuSIMD::u64x4_arg in_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x4 tan_u64x4(EmuSIMD::u64x4_arg in_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x4 acos_u64x4(EmuSIMD::u64x4_arg in_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x4 asin_u64x4(EmuSIMD::u64x4_arg in_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x4 atan_u64x4(EmuSIMD::u64x4_arg in_);
#pragma endregion

#pragma region ROUNDING_TEMPLATES
	template<int RoundingFlag_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x4 round_u64x4(EmuSIMD::u64x4_arg to_round_)
	{
		return to_round_;
	}
#pragma endregion

#pragma region SHUFFLE_TEMPLATES
	template<EmuSIMD::Funcs::shuffle_mask_type ShuffleMask_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x4 permute_u64x4(EmuSIMD::u64x4_arg a_)
	{
		return cast_f64x4_u64x4
		(
			permute_f64x4<ShuffleMask_>(cast_u64x4_f64x4(a_))
		);
	}

	template<EmuSIMD::Funcs::shuffle_mask_type ShuffleMask_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x4 shuffle_u64x4(EmuSIMD::u64x4_arg a_, EmuSIMD::u64x4_arg b_)
	{
		return cast_f64x4_u64x4
		(
			shuffle_f64x4<ShuffleMask_>(cast_u64x4_f64x4(a_), cast_u64x4_f64x4(b_))
		);
	}
#pragma endregion

#pragma region BLEND_TEMPLATES
	template<blend_mask_type BlendMask_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x4 blend_u64x4(EmuSIMD::u64x4_arg a_, EmuSIMD::u64x4_arg b_)
	{
		return cast_f64x4_u64x4
		(
			blend_f64x4<BlendMask_>
			(
				cast_u64x4_f64x4(a_),
				cast_u64x4_f64x4(b_)
			)
		);
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
	EMU_SIMD_COMMON_FUNC_SPEC auto emulate_fp_u64x4(Func_ func_, EmuSIMD::u64x4_arg in_)
		-> std::enable_if_t<std::is_invocable_r_v<EmuSIMD::f64x4, decltype(func_), EmuSIMD::f64x4>, EmuSIMD::u64x4>
	{
		return cvt_f64x4_u64x4
		(
			func_(cvt_u64x4_f64x4(in_))
		);
	}
#pragma endregion

#pragma region EXTRACTION_TEMPLATES
	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x4 extract_f32x8_lane_u64x4(f32x8_arg a_)
	{
		static_assert(Index_ == 0, "Invalid SIMD lane extraction index: Extracting u64x4 lane from a f32x8 instance; the maximum index is 0 but this index has been exceeded.");
		return cast_f32x8_u64x4(a_);
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x4 extract_f32x16_lane_u64x4(f32x16_arg a_)
	{
		static_assert(Index_ <= 1, "Invalid SIMD lane extraction index: Extracting u64x4 lane from a f32x16 instance; the maximum index is 1 but this index has been exceeded.");
		if constexpr (Index_ == 0)
		{
			return cast_f32x16_u64x4(a_);
		}
		else
		{
			return cast_f32x8_u64x4(_mm512_extractf32x8_ps(a_, Index_));
		}
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x4 extract_f64x4_lane_u64x4(f64x4_arg a_)
	{
		static_assert(Index_ == 0, "Invalid SIMD lane extraction index: Extracting u64x4 lane from a f64x4 instance; the maximum index is 0 but this index has been exceeded.");
		return cast_f64x4_u64x4(a_);
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x4 extract_f64x8_lane_u64x4(f64x8_arg a_)
	{
		static_assert(Index_ <= 1, "Invalid SIMD lane extraction index: Extracting u64x4 lane from a f64x8 instance; the maximum index is 1 but this index has been exceeded.");
		if constexpr (Index_ == 0)
		{
			return cast_f64x8_u64x4(a_);
		}
		else
		{
			return cast_f64x4_u64x4(_mm512_extractf64x4_pd(a_, Index_));
		}
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x4 extract_i8x32_lane_u64x4(i8x32_arg a_)
	{
		static_assert(Index_ == 0, "Invalid SIMD lane extraction index: Extracting u64x4 lane from a i8x32 instance; the maximum index is 0 but this index has been exceeded.");
		return cast_i8x32_u64x4(a_);
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x4 extract_i8x64_lane_u64x4(i8x64_arg a_)
	{
		static_assert(Index_ <= 1, "Invalid SIMD lane extraction index: Extracting u64x4 lane from a i8x64 instance; the maximum index is 1 but this index has been exceeded.");
		if constexpr (Index_ == 0)
		{
			return cast_i8x64_u64x4(a_);
		}
		else
		{
			return _mm512_extracti32x8_epi32(a_, Index_);
		}
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x4 extract_i16x16_lane_u64x4(i16x16_arg a_)
	{
		static_assert(Index_ == 0, "Invalid SIMD lane extraction index: Extracting u64x4 lane from a i16x16 instance; the maximum index is 0 but this index has been exceeded.");
		return cast_i16x16_u64x4(a_);
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x4 extract_i16x32_lane_u64x4(i16x32_arg a_)
	{
		static_assert(Index_ <= 1, "Invalid SIMD lane extraction index: Extracting u64x4 lane from a i16x32 instance; the maximum index is 1 but this index has been exceeded.");
		if constexpr (Index_ == 0)
		{
			return cast_i16x32_u64x4(a_);
		}
		else
		{
			return _mm512_extracti32x8_epi32(a_, Index_);
		}
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x4 extract_i32x8_lane_u64x4(i32x8_arg a_)
	{
		static_assert(Index_ == 0, "Invalid SIMD lane extraction index: Extracting u64x4 lane from a i32x8 instance; the maximum index is 0 but this index has been exceeded.");
		return cast_i32x8_u64x4(a_);
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x4 extract_i32x16_lane_u64x4(i32x16_arg a_)
	{
		static_assert(Index_ <= 1, "Invalid SIMD lane extraction index: Extracting u64x4 lane from a i32x16 instance; the maximum index is 1 but this index has been exceeded.");
		if constexpr (Index_ == 0)
		{
			return cast_i32x16_u64x4(a_);
		}
		else
		{
			return _mm512_extracti32x8_epi32(a_, Index_);
		}
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x4 extract_i64x4_lane_u64x4(i64x4_arg a_)
	{
		static_assert(Index_ == 0, "Invalid SIMD lane extraction index: Extracting u64x4 lane from a i64x4 instance; the maximum index is 0 but this index has been exceeded.");
		return cast_i64x4_u64x4(a_);
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x4 extract_i64x8_lane_u64x4(i64x8_arg a_)
	{
		static_assert(Index_ <= 1, "Invalid SIMD lane extraction index: Extracting u64x4 lane from a i64x8 instance; the maximum index is 1 but this index has been exceeded.");
		if constexpr (Index_ == 0)
		{
			return cast_i64x8_u64x4(a_);
		}
		else
		{
			return _mm512_extracti32x8_epi32(a_, Index_);
		}
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x4 extract_u8x32_lane_u64x4(u8x32_arg a_)
	{
		static_assert(Index_ == 0, "Invalid SIMD lane extraction index: Extracting u64x4 lane from a u8x32 instance; the maximum index is 0 but this index has been exceeded.");
		return cast_u8x32_u64x4(a_);
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x4 extract_u8x64_lane_u64x4(u8x64_arg a_)
	{
		static_assert(Index_ <= 1, "Invalid SIMD lane extraction index: Extracting u64x4 lane from a u8x64 instance; the maximum index is 1 but this index has been exceeded.");
		if constexpr (Index_ == 0)
		{
			return cast_u8x64_u64x4(a_);
		}
		else
		{
			return _mm512_extracti32x8_epi32(a_, Index_);
		}
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x4 extract_u16x16_lane_u64x4(u16x16_arg a_)
	{
		static_assert(Index_ == 0, "Invalid SIMD lane extraction index: Extracting u64x4 lane from a u16x16 instance; the maximum index is 0 but this index has been exceeded.");
		return cast_u16x16_u64x4(a_);
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x4 extract_u16x32_lane_u64x4(u16x32_arg a_)
	{
		static_assert(Index_ <= 1, "Invalid SIMD lane extraction index: Extracting u64x4 lane from a u16x32 instance; the maximum index is 1 but this index has been exceeded.");
		if constexpr (Index_ == 0)
		{
			return cast_u16x32_u64x4(a_);
		}
		else
		{
			return _mm512_extracti32x8_epi32(a_, Index_);
		}
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x4 extract_u32x8_lane_u64x4(u32x8_arg a_)
	{
		static_assert(Index_ == 0, "Invalid SIMD lane extraction index: Extracting u64x4 lane from a u32x8 instance; the maximum index is 0 but this index has been exceeded.");
		return cast_u32x8_u64x4(a_);
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x4 extract_u32x16_lane_u64x4(u32x16_arg a_)
	{
		static_assert(Index_ <= 1, "Invalid SIMD lane extraction index: Extracting u64x4 lane from a u32x16 instance; the maximum index is 1 but this index has been exceeded.");
		if constexpr (Index_ == 0)
		{
			return cast_u32x16_u64x4(a_);
		}
		else
		{
			return _mm512_extracti32x8_epi32(a_, Index_);
		}
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x4 extract_u64x4_lane_u64x4(u64x4_arg a_)
	{
		static_assert(Index_ == 0, "Invalid SIMD lane extraction index: Extracting u64x4 lane from a u64x4 instance; the maximum index is 0 but this index has been exceeded.");
		return a_;
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x4 extract_u64x8_lane_u64x4(u64x8_arg a_)
	{
		static_assert(Index_ <= 1, "Invalid SIMD lane extraction index: Extracting u64x4 lane from a u64x8 instance; the maximum index is 1 but this index has been exceeded.");
		if constexpr (Index_ == 0)
		{
			return cast_u64x8_u64x4(a_);
		}
		else
		{
			return _mm512_extracti32x8_epi32(a_, Index_);
		}
	}
#pragma endregion
}

#endif
