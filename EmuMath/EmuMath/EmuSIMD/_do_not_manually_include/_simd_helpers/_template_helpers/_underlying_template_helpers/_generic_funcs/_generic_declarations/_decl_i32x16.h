#ifndef EMU_SIMD_GENERIC_FUNCS_I32X16_DECL_H_INC_
#define EMU_SIMD_GENERIC_FUNCS_I32X16_DECL_H_INC_ 1

#include "../_common_generic_func_helpers.h"
#include "_decl_f32x16.h"
#include "_decl_i32x4.h"

namespace EmuSIMD::Funcs
{
#pragma region SETTERS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 set_i32x16
	(
		std::int32_t e0, std::int32_t e1, std::int32_t e2, std::int32_t e3, std::int32_t e4, std::int32_t e5, std::int32_t e6, std::int32_t e7,
		std::int32_t e8, std::int32_t e9, std::int32_t e10, std::int32_t e11, std::int32_t e12, std::int32_t e13, std::int32_t e14, std::int32_t e15
	);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 setr_i32x16
	(
		std::int32_t e0, std::int32_t e1, std::int32_t e2, std::int32_t e3, std::int32_t e4, std::int32_t e5, std::int32_t e6, std::int32_t e7,
		std::int32_t e8, std::int32_t e9, std::int32_t e10, std::int32_t e11, std::int32_t e12, std::int32_t e13, std::int32_t e14, std::int32_t e15
	);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 set1_i32x16(std::int32_t all_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 load_i32x16(const std::int32_t* p_to_load_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 aligned_load_i32x16(const std::int32_t* p_to_load_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 setzero_i32x16();
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 setmasked_i32x16(std::uint16_t bit_mask_);
#pragma endregion

#pragma region STORES
	EMU_SIMD_COMMON_FUNC_SPEC void store_i32x16(std::int32_t* p_out_, i32x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC void aligned_store_i32x16(std::int32_t* p_out_, i32x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC std::int32_t get_first_i32x16(i32x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC std::uint16_t movemask_i32x16(i32x16_arg a_);
#pragma endregion

#pragma region CASTS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cast_f32x4_i32x16(f32x4_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cast_f32x8_i32x16(f32x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cast_f32x16_i32x16(f32x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cast_f64x2_i32x16(f64x2_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cast_f64x4_i32x16(f64x4_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cast_f64x8_i32x16(f64x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cast_i8x16_i32x16(i8x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cast_i16x8_i32x16(i16x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cast_i32x4_i32x16(i32x4_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cast_i64x2_i32x16(i64x2_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cast_i8x32_i32x16(i8x32_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cast_i16x16_i32x16(i16x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cast_i32x8_i32x16(i32x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cast_i64x4_i32x16(i64x4_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cast_i8x64_i32x16(i8x64_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cast_i16x32_i32x16(i16x32_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cast_i32x16_i32x16(i32x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cast_i64x8_i32x16(i64x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cast_u8x16_i32x16(u8x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cast_u16x8_i32x16(u16x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cast_u32x4_i32x16(u32x4_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cast_u64x2_i32x16(u64x2_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cast_u8x32_i32x16(u8x32_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cast_u16x16_i32x16(u16x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cast_u32x8_i32x16(u32x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cast_u64x4_i32x16(u64x4_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cast_u8x64_i32x16(u8x64_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cast_u16x32_i32x16(u16x32_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cast_u32x16_i32x16(u32x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cast_u64x8_i32x16(u64x8_arg a_);
#pragma endregion

#pragma region CONVERSIONS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cvt_f32x4_i32x16(f32x4_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cvt_f32x8_i32x16(f32x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cvt_f32x16_i32x16(f32x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cvt_f64x2_i32x16(f64x2_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cvt_f64x4_i32x16(f64x4_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cvt_f64x8_i32x16(f64x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cvt_i8x16_i32x16(i8x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cvt_i16x8_i32x16(i16x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cvt_i32x4_i32x16(i32x4_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cvt_i64x2_i32x16(i64x2_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cvt_i8x32_i32x16(i8x32_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cvt_i16x16_i32x16(i16x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cvt_i32x8_i32x16(i32x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cvt_i64x4_i32x16(i64x4_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cvt_i8x64_i32x16(i8x64_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cvt_i16x32_i32x16(i16x32_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cvt_i32x16_i32x16(i32x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cvt_i64x8_i32x16(i64x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cvt_u8x16_i32x16(i8x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cvt_u16x8_i32x16(i16x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cvt_u32x4_i32x16(i32x4_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cvt_u64x2_i32x16(i64x2_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cvt_u8x32_i32x16(i8x32_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cvt_u16x16_i32x16(i16x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cvt_u32x8_i32x16(i32x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cvt_u64x4_i32x16(i64x4_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cvt_u8x64_i32x16(i8x64_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cvt_u16x32_i32x16(i16x32_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cvt_u32x16_i32x16(i32x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cvt_u64x8_i32x16(i64x8_arg a_);
#pragma endregion

#pragma region COMPARISONS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cmpeq_i32x16(EmuSIMD::i32x16_arg lhs_, EmuSIMD::i32x16_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cmpneq_i32x16(EmuSIMD::i32x16_arg lhs_, EmuSIMD::i32x16_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cmpgt_i32x16(EmuSIMD::i32x16_arg lhs_, EmuSIMD::i32x16_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cmplt_i32x16(EmuSIMD::i32x16_arg lhs_, EmuSIMD::i32x16_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cmpge_i32x16(EmuSIMD::i32x16_arg lhs_, EmuSIMD::i32x16_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cmple_i32x16(EmuSIMD::i32x16_arg lhs_, EmuSIMD::i32x16_arg rhs_);
#pragma endregion

#pragma region MOVES
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 movehl_i32x16(EmuSIMD::i32x16_arg lhs_, EmuSIMD::i32x16_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 movelh_i32x16(EmuSIMD::i32x16_arg lhs_, EmuSIMD::i32x16_arg rhs_);
#pragma endregion

#pragma region BITWISE_ARITHMETIC
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 and_i32x16(EmuSIMD::i32x16_arg lhs_, EmuSIMD::i32x16_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 or_i32x16(EmuSIMD::i32x16_arg lhs_, EmuSIMD::i32x16_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 xor_i32x16(EmuSIMD::i32x16_arg lhs_, EmuSIMD::i32x16_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 andnot_i32x16(EmuSIMD::i32x16_arg not_lhs_, EmuSIMD::i32x16_arg rhs_);
	template<std::int32_t NumShifts_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 shift_left_i32x16(EmuSIMD::i32x16_arg lhs_);
	template<std::int32_t NumShifts_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 shift_right_arithmetic_i32x16(EmuSIMD::i32x16_arg lhs_);
	template<std::int32_t NumShifts_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 shift_right_logical_i32x16(EmuSIMD::i32x16_arg lhs_);
#pragma endregion

#pragma region BLENDS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 blendv_i32x16(EmuSIMD::i32x16_arg a_, EmuSIMD::i32x16_arg b_, EmuSIMD::i32x16_arg shuffle_mask_vec_);
#pragma endregion

#pragma region MINMAX_FUNCS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 min_i32x16(EmuSIMD::i32x16_arg a_, EmuSIMD::i32x16_arg b_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 horizontal_min_i32x16(EmuSIMD::i32x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 max_i32x16(EmuSIMD::i32x16_arg a_, EmuSIMD::i32x16_arg b_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 horizontal_max_i32x16(EmuSIMD::i32x16_arg a_);
#pragma endregion

#pragma region BASIC_ARITHMETIC
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 mul_all_i32x16(EmuSIMD::i32x16_arg lhs_, EmuSIMD::i32x16_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 negate_i32x16(EmuSIMD::i32x16_arg to_negate_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 add_i32x16(EmuSIMD::i32x16_arg lhs_, EmuSIMD::i32x16_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 sub_i32x16(EmuSIMD::i32x16_arg lhs_, EmuSIMD::i32x16_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 div_i32x16(EmuSIMD::i32x16_arg lhs_, EmuSIMD::i32x16_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 addsub_i32x16(EmuSIMD::i32x16_arg lhs_, EmuSIMD::i32x16_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 subadd_i32x16(EmuSIMD::i32x16_arg lhs_, EmuSIMD::i32x16_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 fmadd_i32x16(EmuSIMD::i32x16_arg a_, EmuSIMD::i32x16_arg b_, EmuSIMD::i32x16_arg c_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 fmsub_i32x16(EmuSIMD::i32x16_arg a_, EmuSIMD::i32x16_arg b_, EmuSIMD::i32x16_arg c_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 fnmadd_i32x16(EmuSIMD::i32x16_arg a_, EmuSIMD::i32x16_arg b_, EmuSIMD::i32x16_arg c_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 fnmsub_i32x16(EmuSIMD::i32x16_arg a_, EmuSIMD::i32x16_arg b_, EmuSIMD::i32x16_arg c_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 fmaddsub_i32x16(EmuSIMD::i32x16_arg a_, EmuSIMD::i32x16_arg b_, EmuSIMD::i32x16_arg c_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 fmsubadd_i32x16(EmuSIMD::i32x16_arg a_, EmuSIMD::i32x16_arg b_, EmuSIMD::i32x16_arg c_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 floor_i32x16(EmuSIMD::i32x16_arg to_floor_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 ceil_i32x16(EmuSIMD::i32x16_arg to_ceil_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 trunc_i32x16(EmuSIMD::i32x16_arg to_trunc_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 mod_i32x16(EmuSIMD::i32x16_arg lhs_, EmuSIMD::i32x16_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 abs_i32x16(EmuSIMD::i32x16_arg in_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 sqrt_i32x16(EmuSIMD::i32x16_arg in_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 rsqrt_i32x16(EmuSIMD::i32x16_arg in_);
#pragma endregion

#pragma region NEAR_COMPARISONS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cmpnear_i32x16(EmuSIMD::i32x16_arg lhs_, EmuSIMD::i32x16_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cmpnear_i32x16(EmuSIMD::i32x16_arg lhs_, EmuSIMD::i32x16_arg rhs_, EmuSIMD::i32x16_arg epsilon);
#pragma endregion

#pragma region TRIG
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cos_i32x16(EmuSIMD::i32x16_arg in_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 sin_i32x16(EmuSIMD::i32x16_arg in_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 tan_i32x16(EmuSIMD::i32x16_arg in_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 acos_i32x16(EmuSIMD::i32x16_arg in_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 asin_i32x16(EmuSIMD::i32x16_arg in_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 atan_i32x16(EmuSIMD::i32x16_arg in_);
#pragma endregion

#pragma region ROUNDING_TEMPLATES
	template<int RoundingFlag_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 round_i32x16(EmuSIMD::i32x16_arg to_round_)
	{
		return to_round_;
	}
#pragma endregion

#pragma region SHUFFLE_TEMPLATES
	template<EmuSIMD::Funcs::shuffle_mask_type ShuffleMask_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 permute_i32x16(EmuSIMD::i32x16_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_shuffle_epi32(a_, ShuffleMask_);
#else
		using EmuSIMD::_underlying_impl::emulate_simd_basic;
		return emulate_simd_basic([](i32x8_arg a) { return EmuSIMD::Funcs::permute_i32x8<ShuffleMask>(a); }, a_);
#endif
	}

	template<EmuSIMD::Funcs::shuffle_mask_type ShuffleMask_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 shuffle_i32x16(EmuSIMD::i32x16_arg a_, EmuSIMD::i32x16_arg b_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return cast_f32x16_i32x16
		(
			shuffle_f32x16<ShuffleMask_>
			(
				cast_i32x16_f32x16(a_),
				cast_i32x16_f32x16(b_)
			)
		);
#else
		using EmuSIMD::_underlying_impl::emulate_simd_basic;
		return emulate_simd_basic([](i32x8_arg a, i32x8_arg b) { return EmuSIMD::Funcs::shuffle_i32x8<ShuffleMask>(a, b); }, a_, b_);
#endif
	}
#pragma endregion

#pragma region BLEND_TEMPLATES
	template<EmuSIMD::Funcs::blend_mask_type BlendMask_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 blend_i32x16(EmuSIMD::i32x16_arg a_, EmuSIMD::i32x16_arg b_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return cast_f32x16_i32x16
		(
			blend_f32x16<BlendMask_>
			(
				cast_i32x16_f32x16(a_),
				cast_i32x16_f32x16(b_)
			)
		);
#else
		return EmuSIMD::_underlying_impl::emulate_dual_lane_blend_with_mask<BlendMask>(a_, b_, std::make_index_sequence<8>());
#endif
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
	EMU_SIMD_COMMON_FUNC_SPEC auto emulate_fp_i32x16(Func_ func_, EmuSIMD::i32x16_arg in_)
		-> std::enable_if_t<std::is_invocable_r_v<EmuSIMD::f32x16, decltype(func_), EmuSIMD::f32x16>, EmuSIMD::i32x16>
	{
		return cvt_f32x16_i32x16
		(
			func_(cvt_i32x16_f32x16(in_))
		);
	}
#pragma endregion

#pragma region EXTRACTION_TEMPLATES
	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 extract_f32x16_lane_i32x16(f32x16_arg a_)
	{
		static_assert(Index_ == 0, "Invalid SIMD lane extraction index: Extracting i32x16 lane from a f32x16 instance; the maximum index is 0 but this index has been exceeded.");
		return cast_f32x16_i32x16(a_);
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 extract_f64x8_lane_i32x16(f64x8_arg a_)
	{
		static_assert(Index_ == 0, "Invalid SIMD lane extraction index: Extracting i32x16 lane from a f64x8 instance; the maximum index is 0 but this index has been exceeded.");
		return cast_f64x8_i32x16(a_);
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 extract_i8x64_lane_i32x16(i8x64_arg a_)
	{
		static_assert(Index_ == 0, "Invalid SIMD lane extraction index: Extracting i32x16 lane from a i8x64 instance; the maximum index is 0 but this index has been exceeded.");
		return cast_i8x64_i32x16(a_);
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 extract_i16x32_lane_i32x16(i16x32_arg a_)
	{
		static_assert(Index_ == 0, "Invalid SIMD lane extraction index: Extracting i32x16 lane from a i16x32 instance; the maximum index is 0 but this index has been exceeded.");
		return cast_i16x32_i32x16(a_);
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 extract_i32x16_lane_i32x16(i32x16_arg a_)
	{
		static_assert(Index_ == 0, "Invalid SIMD lane extraction index: Extracting i32x16 lane from a i32x16 instance; the maximum index is 0 but this index has been exceeded.");
		return a_;
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 extract_i64x8_lane_i32x16(i64x8_arg a_)
	{
		static_assert(Index_ == 0, "Invalid SIMD lane extraction index: Extracting i32x16 lane from a i64x8 instance; the maximum index is 0 but this index has been exceeded.");
		return cast_i64x8_i32x16(a_);
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 extract_u8x64_lane_i32x16(u8x64_arg a_)
	{
		static_assert(Index_ == 0, "Invalid SIMD lane extraction index: Extracting i32x16 lane from a u8x64 instance; the maximum index is 0 but this index has been exceeded.");
		return cast_u8x64_i32x16(a_);
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 extract_u16x32_lane_i32x16(u16x32_arg a_)
	{
		static_assert(Index_ == 0, "Invalid SIMD lane extraction index: Extracting i32x16 lane from a u16x32 instance; the maximum index is 0 but this index has been exceeded.");
		return cast_u16x32_i32x16(a_);
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 extract_u32x16_lane_i32x16(u32x16_arg a_)
	{
		static_assert(Index_ == 0, "Invalid SIMD lane extraction index: Extracting i32x16 lane from a u32x16 instance; the maximum index is 0 but this index has been exceeded.");
		return cast_u32x16_i32x16(a_);
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 extract_u64x8_lane_i32x16(u64x8_arg a_)
	{
		static_assert(Index_ == 0, "Invalid SIMD lane extraction index: Extracting i32x16 lane from a u64x8 instance; the maximum index is 0 but this index has been exceeded.");
		return cast_u64x8_i32x16(a_);
	}
#pragma endregion

#pragma region GET_TEMPLATES
	template<std::size_t Index_, typename OutT_ = std::int32_t>
	EMU_SIMD_COMMON_FUNC_SPEC auto extract_element_i32x16(i32x16_arg in_)
		-> typename std::remove_cvref<OutT_>::type
	{
		if constexpr (Index_ == 0)
		{
			return static_cast<typename std::remove_cvref<OutT_>::type>(EmuSIMD::Funcs::get_first_i32x16(in_));
		}
		else
		{
			if constexpr (Index_ <= 15)
			{
#if EMU_SIMD_USE_512_REGISTERS
				constexpr std::size_t elements_per_chunk = 4;
				constexpr std::size_t chunk_index = static_cast<std::size_t>(Index_ / elements_per_chunk);
				constexpr std::size_t index_in_chunk = Index_ - (chunk_index * elements_per_chunk);
				return EmuSIMD::Funcs::extract_element_i32x4<index_in_chunk, OutT_>(EmuSIMD::Funcs::extract_i32x16_lane_i32x4<chunk_index>(in_));
#else
				return EmuSIMD::_underlying_impl::retrieve_emulated_dual_lane_simd_element<OutT_, Index_, false, 8>(in_);
#endif
			}
			else
			{
				static_assert
				(
					EmuCore::TMP::get_false<std::size_t, Index_>(),
					"Invalid index provided when extracting an element from a i32x16 instance. Valid indices are 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15."
				);
			}
		}
	}
#pragma endregion
}

#endif
