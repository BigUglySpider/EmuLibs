#ifndef EMU_SIMD_GENERIC_FUNCS_U32X16_DECL_H_INC_
#define EMU_SIMD_GENERIC_FUNCS_U32X16_DECL_H_INC_ 1

#include "../_common_generic_func_helpers.h"
#include "_decl_f32x16.h"

namespace EmuSIMD::Funcs
{
#pragma region SETTERS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 set_u32x16
	(
		std::uint32_t e0, std::uint32_t e1, std::uint32_t e2, std::uint32_t e3, std::uint32_t e4, std::uint32_t e5, std::uint32_t e6, std::uint32_t e7,
		std::uint32_t e8, std::uint32_t e9, std::uint32_t e10, std::uint32_t e11, std::uint32_t e12, std::uint32_t e13, std::uint32_t e14, std::uint32_t e15
	);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 setr_u32x16
	(
		std::uint32_t e0, std::uint32_t e1, std::uint32_t e2, std::uint32_t e3, std::uint32_t e4, std::uint32_t e5, std::uint32_t e6, std::uint32_t e7,
		std::uint32_t e8, std::uint32_t e9, std::uint32_t e10, std::uint32_t e11, std::uint32_t e12, std::uint32_t e13, std::uint32_t e14, std::uint32_t e15
	);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 set1_u32x16(std::uint32_t all_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 load_u32x16(const std::uint32_t* p_to_load_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 setzero_u32x16();
#pragma endregion

#pragma region STORES
	EMU_SIMD_COMMON_FUNC_SPEC void store_u32x16(std::uint32_t* p_out_, u32x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC std::uint32_t get_first_u32x16(u32x16_arg a_);
#pragma endregion

#pragma region CASTS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cast_f32x4_u32x16(f32x4_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cast_f32x8_u32x16(f32x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cast_f32x16_u32x16(f32x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cast_f64x2_u32x16(f64x2_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cast_f64x4_u32x16(f64x4_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cast_f64x8_u32x16(f64x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cast_i8x16_u32x16(i8x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cast_i16x8_u32x16(i16x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cast_i32x4_u32x16(i32x4_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cast_i64x2_u32x16(i64x2_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cast_i8x32_u32x16(i8x32_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cast_i16x16_u32x16(i16x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cast_i32x8_u32x16(i32x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cast_i64x4_u32x16(i64x4_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cast_i8x64_u32x16(i8x64_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cast_i16x32_u32x16(i16x32_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cast_i32x16_u32x16(i32x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cast_i64x8_u32x16(i64x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cast_u8x16_u32x16(u8x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cast_u16x8_u32x16(u16x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cast_u32x4_u32x16(u32x4_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cast_u64x2_u32x16(u64x2_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cast_u8x32_u32x16(u8x32_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cast_u16x16_u32x16(u16x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cast_u32x8_u32x16(u32x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cast_u64x4_u32x16(u64x4_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cast_u8x64_u32x16(u8x64_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cast_u16x32_u32x16(u16x32_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cast_u32x16_u32x16(u32x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cast_u64x8_u32x16(u64x8_arg a_);
#pragma endregion

#pragma region CONVERSIONS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cvt_f32x4_u32x16(f32x4_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cvt_f32x8_u32x16(f32x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cvt_f32x16_u32x16(f32x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cvt_f64x2_u32x16(f64x2_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cvt_f64x4_u32x16(f64x4_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cvt_f64x8_u32x16(f64x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cvt_i8x16_u32x16(i8x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cvt_i16x8_u32x16(i16x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cvt_i32x4_u32x16(i32x4_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cvt_i64x2_u32x16(i64x2_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cvt_i8x32_u32x16(i8x32_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cvt_i16x16_u32x16(i16x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cvt_i32x8_u32x16(i32x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cvt_i64x4_u32x16(i64x4_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cvt_i8x64_u32x16(i8x64_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cvt_i16x32_u32x16(i16x32_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cvt_i32x16_u32x16(i32x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cvt_i64x8_u32x16(i64x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cvt_u8x16_u32x16(i8x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cvt_u16x8_u32x16(i16x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cvt_u32x4_u32x16(i32x4_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cvt_u64x2_u32x16(i64x2_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cvt_u8x32_u32x16(i8x32_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cvt_u16x16_u32x16(i16x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cvt_u32x8_u32x16(i32x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cvt_u64x4_u32x16(i64x4_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cvt_u8x64_u32x16(i8x64_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cvt_u16x32_u32x16(i16x32_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cvt_u32x16_u32x16(i32x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cvt_u64x8_u32x16(i64x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 setmasked_u32x16(std::uint16_t bit_mask_);
#pragma endregion

#pragma region COMPARISONS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cmpeq_u32x16(EmuSIMD::u32x16_arg lhs_, EmuSIMD::u32x16_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cmpneq_u32x16(EmuSIMD::u32x16_arg lhs_, EmuSIMD::u32x16_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cmpgt_u32x16(EmuSIMD::u32x16_arg lhs_, EmuSIMD::u32x16_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cmplt_u32x16(EmuSIMD::u32x16_arg lhs_, EmuSIMD::u32x16_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cmpge_u32x16(EmuSIMD::u32x16_arg lhs_, EmuSIMD::u32x16_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cmple_u32x16(EmuSIMD::u32x16_arg lhs_, EmuSIMD::u32x16_arg rhs_);
#pragma endregion

#pragma region MOVES
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 movehl_u32x16(EmuSIMD::u32x16_arg lhs_, EmuSIMD::u32x16_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 movelh_u32x16(EmuSIMD::u32x16_arg lhs_, EmuSIMD::u32x16_arg rhs_);
#pragma endregion

#pragma region BLENDS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 blendv_u32x16(EmuSIMD::u32x16_arg a_, EmuSIMD::u32x16_arg b_, EmuSIMD::u32x16_arg shuffle_mask_vec_);
#pragma endregion

#pragma region MINMAX_FUNCS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 min_u32x16(EmuSIMD::u32x16_arg a_, EmuSIMD::u32x16_arg b_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 max_u32x16(EmuSIMD::u32x16_arg a_, EmuSIMD::u32x16_arg b_);
#pragma endregion

#pragma region BASIC_ARITHMETIC
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 mul_all_u32x16(EmuSIMD::u32x16_arg lhs_, EmuSIMD::u32x16_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 negate_u32x16(EmuSIMD::u32x16_arg to_negate_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 add_u32x16(EmuSIMD::u32x16_arg lhs_, EmuSIMD::u32x16_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 sub_u32x16(EmuSIMD::u32x16_arg lhs_, EmuSIMD::u32x16_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 mul_u32x16(EmuSIMD::u32x16_arg lhs_, EmuSIMD::u32x16_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 div_u32x16(EmuSIMD::u32x16_arg lhs_, EmuSIMD::u32x16_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 addsub_u32x16(EmuSIMD::u32x16_arg lhs_, EmuSIMD::u32x16_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 subadd_u32x16(EmuSIMD::u32x16_arg lhs_, EmuSIMD::u32x16_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 fmadd_u32x16(EmuSIMD::u32x16_arg a_, EmuSIMD::u32x16_arg b_, EmuSIMD::u32x16_arg c_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 fmsub_u32x16(EmuSIMD::u32x16_arg a_, EmuSIMD::u32x16_arg b_, EmuSIMD::u32x16_arg c_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 fnmadd_u32x16(EmuSIMD::u32x16_arg a_, EmuSIMD::u32x16_arg b_, EmuSIMD::u32x16_arg c_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 fnmsub_u32x16(EmuSIMD::u32x16_arg a_, EmuSIMD::u32x16_arg b_, EmuSIMD::u32x16_arg c_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 fmaddsub_u32x16(EmuSIMD::u32x16_arg a_, EmuSIMD::u32x16_arg b_, EmuSIMD::u32x16_arg c_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 fmsubadd_u32x16(EmuSIMD::u32x16_arg a_, EmuSIMD::u32x16_arg b_, EmuSIMD::u32x16_arg c_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 floor_u32x16(EmuSIMD::u32x16_arg to_floor_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 ceil_u32x16(EmuSIMD::u32x16_arg to_ceil_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 trunc_u32x16(EmuSIMD::u32x16_arg to_trunc_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 mod_u32x16(EmuSIMD::u32x16_arg lhs_, EmuSIMD::u32x16_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 abs_u32x16(EmuSIMD::u32x16_arg in_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 sqrt_u32x16(EmuSIMD::u32x16_arg in_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 rsqrt_u32x16(EmuSIMD::u32x16_arg in_);
#pragma endregion

#pragma region NEAR_COMPARISONS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cmpnear_u32x16(EmuSIMD::u32x16_arg lhs_, EmuSIMD::u32x16_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cmpnear_u32x16(EmuSIMD::u32x16_arg lhs_, EmuSIMD::u32x16_arg rhs_, EmuSIMD::u32x16_arg epsilon);
#pragma endregion

#pragma region TRIG
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cos_u32x16(EmuSIMD::u32x16_arg in_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 sin_u32x16(EmuSIMD::u32x16_arg in_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 tan_u32x16(EmuSIMD::u32x16_arg in_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 acos_u32x16(EmuSIMD::u32x16_arg in_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 asin_u32x16(EmuSIMD::u32x16_arg in_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 atan_u32x16(EmuSIMD::u32x16_arg in_);
#pragma endregion

#pragma region ROUNDING_TEMPLATES
	template<int RoundingFlag_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 round_u32x16(EmuSIMD::u32x16_arg to_round_)
	{
		return to_round_;
	}
#pragma endregion

#pragma region SHUFFLE_TEMPLATES
	template<EmuSIMD::Funcs::shuffle_mask_type ShuffleMask_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 permute_u32x16(EmuSIMD::u32x16_arg a_)
	{
		return _mm512_shuffle_epi32(a_, ShuffleMask_);
	}

	template<EmuSIMD::Funcs::shuffle_mask_type ShuffleMask_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 shuffle_u32x16(EmuSIMD::u32x16_arg a_, EmuSIMD::u32x16_arg b_)
	{
		return cast_f32x16_u32x16
		(
			shuffle_f32x16<ShuffleMask_>
			(
				cast_u32x16_f32x16(a_),
				cast_u32x16_f32x16(b_)
			)
		);
	}
#pragma endregion

#pragma region BLEND_TEMPLATES
	template<EmuSIMD::Funcs::blend_mask_type BlendMask_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 blend_u32x16(EmuSIMD::u32x16_arg a_, EmuSIMD::u32x16_arg b_)
	{
		return cast_f32x16_u32x16
		(
			blend_f32x16<BlendMask_>
			(
				cast_u32x16_f32x16(a_),
				cast_u32x16_f32x16(b_)
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
	EMU_SIMD_COMMON_FUNC_SPEC auto emulate_fp_u32x16(Func_ func_, EmuSIMD::u32x16_arg in_)
		-> std::enable_if_t<std::is_invocable_r_v<EmuSIMD::f32x16, decltype(func_), EmuSIMD::f32x16>, EmuSIMD::u32x16>
	{
		return cvt_f32x16_u32x16
		(
			func_(cvt_u32x16_f32x16(in_))
		);
	}
#pragma endregion

#pragma region EXTRACTION_TEMPLATES
	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 extract_f32x16_lane_u32x16(f32x16_arg a_)
	{
		static_assert(Index_ == 0, "Invalid SIMD lane extraction index: Extracting u32x16 lane from a f32x16 instance; the maximum index is 0 but this index has been exceeded.");
		return cast_f32x16_u32x16(a_);
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 extract_f64x8_lane_u32x16(f64x8_arg a_)
	{
		static_assert(Index_ == 0, "Invalid SIMD lane extraction index: Extracting u32x16 lane from a f64x8 instance; the maximum index is 0 but this index has been exceeded.");
		return cast_f64x8_u32x16(a_);
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 extract_i8x64_lane_u32x16(i8x64_arg a_)
	{
		static_assert(Index_ == 0, "Invalid SIMD lane extraction index: Extracting u32x16 lane from a i8x64 instance; the maximum index is 0 but this index has been exceeded.");
		return cast_i8x64_u32x16(a_);
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 extract_i16x32_lane_u32x16(i16x32_arg a_)
	{
		static_assert(Index_ == 0, "Invalid SIMD lane extraction index: Extracting u32x16 lane from a i16x32 instance; the maximum index is 0 but this index has been exceeded.");
		return cast_i16x32_u32x16(a_);
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 extract_i32x16_lane_u32x16(i32x16_arg a_)
	{
		static_assert(Index_ == 0, "Invalid SIMD lane extraction index: Extracting u32x16 lane from a i32x16 instance; the maximum index is 0 but this index has been exceeded.");
		return cast_i32x16_u32x16(a_);
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 extract_i64x8_lane_u32x16(i64x8_arg a_)
	{
		static_assert(Index_ == 0, "Invalid SIMD lane extraction index: Extracting u32x16 lane from a i64x8 instance; the maximum index is 0 but this index has been exceeded.");
		return cast_i64x8_u32x16(a_);
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 extract_u8x64_lane_u32x16(u8x64_arg a_)
	{
		static_assert(Index_ == 0, "Invalid SIMD lane extraction index: Extracting u32x16 lane from a u8x64 instance; the maximum index is 0 but this index has been exceeded.");
		return cast_u8x64_u32x16(a_);
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 extract_u16x32_lane_u32x16(u16x32_arg a_)
	{
		static_assert(Index_ == 0, "Invalid SIMD lane extraction index: Extracting u32x16 lane from a u16x32 instance; the maximum index is 0 but this index has been exceeded.");
		return cast_u16x32_u32x16(a_);
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 extract_u32x16_lane_u32x16(u32x16_arg a_)
	{
		static_assert(Index_ == 0, "Invalid SIMD lane extraction index: Extracting u32x16 lane from a u32x16 instance; the maximum index is 0 but this index has been exceeded.");
		return a_;
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 extract_u64x8_lane_u32x16(u64x8_arg a_)
	{
		static_assert(Index_ == 0, "Invalid SIMD lane extraction index: Extracting u32x16 lane from a u64x8 instance; the maximum index is 0 but this index has been exceeded.");
		return cast_u64x8_u32x16(a_);
	}
#pragma endregion
}

#endif
