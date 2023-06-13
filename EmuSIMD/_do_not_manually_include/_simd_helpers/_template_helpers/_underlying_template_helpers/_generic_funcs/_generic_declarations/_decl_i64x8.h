#ifndef EMU_SIMD_GENERIC_FUNCS_I64X8_DECL_H_INC_
#define EMU_SIMD_GENERIC_FUNCS_I64X8_DECL_H_INC_ 1

#include "../_common_generic_func_helpers.h"
#include "_decl_f64x8.h"
#include "_decl_i64x2.h"

namespace EmuSIMD::Funcs
{
#pragma region SETTERS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 set_i64x8(std::int64_t e0, std::int64_t e1, std::int64_t e2, std::int64_t e3, std::int64_t e4, std::int64_t e5, std::int64_t e6, std::int64_t e7);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 setr_i64x8(std::int64_t e0, std::int64_t e1, std::int64_t e2, std::int64_t e3, std::int64_t e4, std::int64_t e5, std::int64_t e6, std::int64_t e7);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 set1_i64x8(std::int64_t all_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 load_i64x8(const std::int64_t* p_to_load_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 aligned_load_i64x8(const std::int64_t* p_to_load_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 setzero_i64x8();
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 setmasked_i64x8(std::uint8_t bit_mask_);
#pragma endregion

#pragma region STORES
	EMU_SIMD_COMMON_FUNC_SPEC void store_i64x8(std::int64_t* p_out_, i64x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC void aligned_store_i64x8(std::int64_t* p_out_, i64x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC std::int64_t get_first_i64x8(i64x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC std::uint8_t movemask_i64x8(i64x8_arg a_);
#pragma endregion

#pragma region CASTS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 cast_f32x4_i64x8(f32x4_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 cast_f32x8_i64x8(f32x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 cast_f32x16_i64x8(f32x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 cast_f64x2_i64x8(f64x2_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 cast_f64x4_i64x8(f64x4_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 cast_f64x8_i64x8(f64x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 cast_i8x16_i64x8(i8x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 cast_i16x8_i64x8(i16x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 cast_i32x4_i64x8(i32x4_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 cast_i64x2_i64x8(i64x2_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 cast_i8x32_i64x8(i8x32_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 cast_i16x16_i64x8(i16x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 cast_i32x8_i64x8(i32x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 cast_i64x4_i64x8(i64x4_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 cast_i8x64_i64x8(i8x64_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 cast_i16x32_i64x8(i16x32_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 cast_i32x16_i64x8(i32x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 cast_i64x8_i64x8(i64x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 cast_u8x16_i64x8(u8x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 cast_u16x8_i64x8(u16x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 cast_u32x4_i64x8(u32x4_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 cast_u64x2_i64x8(u64x2_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 cast_u8x32_i64x8(u8x32_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 cast_u16x16_i64x8(u16x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 cast_u32x8_i64x8(u32x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 cast_u64x4_i64x8(u64x4_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 cast_u8x64_i64x8(u8x64_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 cast_u16x32_i64x8(u16x32_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 cast_u32x16_i64x8(u32x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 cast_u64x8_i64x8(u64x8_arg a_);
#pragma endregion

#pragma region CONVERSIONS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 cvt_f32x4_i64x8(f32x4_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 cvt_f32x8_i64x8(f32x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 cvt_f32x16_i64x8(f32x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 cvt_f64x2_i64x8(f64x2_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 cvt_f64x4_i64x8(f64x4_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 cvt_f64x8_i64x8(f64x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 cvt_i8x16_i64x8(i8x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 cvt_i16x8_i64x8(i16x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 cvt_i32x4_i64x8(i32x4_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 cvt_i64x2_i64x8(i64x2_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 cvt_i8x32_i64x8(i8x32_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 cvt_i16x16_i64x8(i16x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 cvt_i32x8_i64x8(i32x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 cvt_i64x4_i64x8(i64x4_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 cvt_i8x64_i64x8(i8x64_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 cvt_i16x32_i64x8(i16x32_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 cvt_i32x16_i64x8(i32x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 cvt_i64x8_i64x8(i64x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 cvt_u8x16_i64x8(u8x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 cvt_u16x8_i64x8(u16x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 cvt_u32x4_i64x8(u32x4_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 cvt_u64x2_i64x8(u64x2_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 cvt_u8x32_i64x8(u8x32_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 cvt_u16x16_i64x8(u16x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 cvt_u32x8_i64x8(u32x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 cvt_u64x4_i64x8(u64x4_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 cvt_u8x64_i64x8(u8x64_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 cvt_u16x32_i64x8(u16x32_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 cvt_u32x16_i64x8(u32x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 cvt_u64x8_i64x8(u64x8_arg a_);
#pragma endregion

#pragma region COMPARISONS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 cmpeq_i64x8(EmuSIMD::i64x8_arg lhs_, EmuSIMD::i64x8_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 cmpneq_i64x8(EmuSIMD::i64x8_arg lhs_, EmuSIMD::i64x8_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 cmpgt_i64x8(EmuSIMD::i64x8_arg lhs_, EmuSIMD::i64x8_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 cmplt_i64x8(EmuSIMD::i64x8_arg lhs_, EmuSIMD::i64x8_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 cmpge_i64x8(EmuSIMD::i64x8_arg lhs_, EmuSIMD::i64x8_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 cmple_i64x8(EmuSIMD::i64x8_arg lhs_, EmuSIMD::i64x8_arg rhs_);

#pragma region MOVES
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 movehl_i64x8(EmuSIMD::i64x8_arg lhs_, EmuSIMD::i64x8_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 movelh_i64x8(EmuSIMD::i64x8_arg lhs_, EmuSIMD::i64x8_arg rhs_);
#pragma endregion

#pragma region BITWISE_ARITHMETIC
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 and_i64x8(EmuSIMD::i64x8_arg lhs_, EmuSIMD::i64x8_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 or_i64x8(EmuSIMD::i64x8_arg lhs_, EmuSIMD::i64x8_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 xor_i64x8(EmuSIMD::i64x8_arg lhs_, EmuSIMD::i64x8_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 andnot_i64x8(EmuSIMD::i64x8_arg not_lhs_, EmuSIMD::i64x8_arg rhs_);
	template<std::int32_t NumShifts_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 shift_left_i64x8(EmuSIMD::i64x8_arg lhs_);
	template<std::int32_t NumShifts_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 shift_right_arithmetic_i64x8(EmuSIMD::i64x8_arg lhs_);
	template<std::int32_t NumShifts_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 shift_right_logical_i64x8(EmuSIMD::i64x8_arg lhs_);
#pragma endregion
	
#pragma region BLENDS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 blendv_i64x8(EmuSIMD::i64x8_arg a_, EmuSIMD::i64x8_arg b_, EmuSIMD::i64x8_arg shuffle_mask_vec_);
#pragma endregion

#pragma region MINMAX_FUNCS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 min_i64x8(EmuSIMD::i64x8_arg a_, EmuSIMD::i64x8_arg b_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 horizontal_min_i64x8(EmuSIMD::i64x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 horizontal_min_fill_i64x8(EmuSIMD::i64x8_arg a_);
	template<typename Out_ = std::int64_t>
	EMU_SIMD_COMMON_FUNC_SPEC auto horizontal_min_scalar_i64x8(EmuSIMD::i64x8_arg a_)
		-> typename std::remove_cvref<Out_>::type;
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 max_i64x8(EmuSIMD::i64x8_arg a_, EmuSIMD::i64x8_arg b_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 horizontal_max_i64x8(EmuSIMD::i64x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 horizontal_max_fill_i64x8(EmuSIMD::i64x8_arg a_);
	template<typename Out_ = std::int64_t>
	EMU_SIMD_COMMON_FUNC_SPEC auto horizontal_max_scalar_i64x8(EmuSIMD::i64x8_arg a_)
		-> typename std::remove_cvref<Out_>::type;
#pragma endregion

#pragma region BASIC_ARITHMETIC
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 mul_all_i64x8(EmuSIMD::i64x8_arg lhs_, EmuSIMD::i64x8_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 negate_i64x8(EmuSIMD::i64x8_arg to_negate_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 add_i64x8(EmuSIMD::i64x8_arg lhs_, EmuSIMD::i64x8_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 sub_i64x8(EmuSIMD::i64x8_arg lhs_, EmuSIMD::i64x8_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 div_i64x8(EmuSIMD::i64x8_arg lhs_, EmuSIMD::i64x8_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 addsub_i64x8(EmuSIMD::i64x8_arg lhs_, EmuSIMD::i64x8_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 subadd_i64x8(EmuSIMD::i64x8_arg lhs_, EmuSIMD::i64x8_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 fmadd_i64x8(EmuSIMD::i64x8_arg a_, EmuSIMD::i64x8_arg b_, EmuSIMD::i64x8_arg c_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 fmsub_i64x8(EmuSIMD::i64x8_arg a_, EmuSIMD::i64x8_arg b_, EmuSIMD::i64x8_arg c_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 fnmadd_i64x8(EmuSIMD::i64x8_arg a_, EmuSIMD::i64x8_arg b_, EmuSIMD::i64x8_arg c_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 fnmsub_i64x8(EmuSIMD::i64x8_arg a_, EmuSIMD::i64x8_arg b_, EmuSIMD::i64x8_arg c_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 fmaddsub_i64x8(EmuSIMD::i64x8_arg a_, EmuSIMD::i64x8_arg b_, EmuSIMD::i64x8_arg c_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 fmsubadd_i64x8(EmuSIMD::i64x8_arg a_, EmuSIMD::i64x8_arg b_, EmuSIMD::i64x8_arg c_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 floor_i64x8(EmuSIMD::i64x8_arg to_floor_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 ceil_i64x8(EmuSIMD::i64x8_arg to_ceil_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 trunc_i64x8(EmuSIMD::i64x8_arg to_trunc_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 mod_i64x8(EmuSIMD::i64x8_arg lhs_, EmuSIMD::i64x8_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 abs_i64x8(EmuSIMD::i64x8_arg in_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 sqrt_i64x8(EmuSIMD::i64x8_arg in_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 rsqrt_i64x8(EmuSIMD::i64x8_arg in_);
#pragma endregion

#pragma region NEAR_COMPARISONS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 cmpnear_i64x8(EmuSIMD::i64x8_arg lhs_, EmuSIMD::i64x8_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 cmpnear_i64x8(EmuSIMD::i64x8_arg lhs_, EmuSIMD::i64x8_arg rhs_, EmuSIMD::i64x8_arg epsilon);
#pragma endregion

#pragma region TRIG
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 cos_i64x8(EmuSIMD::i64x8_arg in_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 sin_i64x8(EmuSIMD::i64x8_arg in_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 tan_i64x8(EmuSIMD::i64x8_arg in_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 acos_i64x8(EmuSIMD::i64x8_arg in_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 asin_i64x8(EmuSIMD::i64x8_arg in_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 atan_i64x8(EmuSIMD::i64x8_arg in_);
#pragma endregion

#pragma region ROUNDING_TEMPLATES
	template<int RoundingFlag_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 round_i64x8(EmuSIMD::i64x8_arg to_round_)
	{
		return to_round_;
	}
#pragma endregion

#pragma region SHUFFLE_TEMPLATES
	template<EmuSIMD::Funcs::shuffle_mask_type ShuffleMask_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 permute_i64x8(EmuSIMD::i64x8_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return cast_f64x8_i64x8
		(
			permute_f64x8<ShuffleMask_>(cast_i64x8_f64x8(a_))
		);
#else
		using EmuSIMD::_underlying_impl::emulate_simd_basic;
		return emulate_simd_basic([](i64x4_arg a) { return EmuSIMD::Funcs::permute_i64x4<ShuffleMask_>(a); }, a_);
#endif
	}

	template<EmuSIMD::Funcs::shuffle_mask_type ShuffleMask_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 shuffle_i64x8(EmuSIMD::i64x8_arg a_, EmuSIMD::i64x8_arg b_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return cast_f64x8_i64x8
		(
			shuffle_f64x8<ShuffleMask_>(cast_i64x8_f64x8(a_), cast_i64x8_f64x8(b_))
		);
#else
		using EmuSIMD::_underlying_impl::emulate_simd_basic;
		return emulate_simd_basic([](i64x4_arg a, i64x4_arg b) { return EmuSIMD::Funcs::shuffle_i64x4<ShuffleMask_>(a, b); }, a_, b_);
#endif
	}
#pragma endregion

#pragma region BLEND_TEMPLATES
	template<blend_mask_type BlendMask_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 blend_i64x8(EmuSIMD::i64x8_arg a_, EmuSIMD::i64x8_arg b_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return cast_f64x8_i64x8
		(
			blend_f64x8<BlendMask_>
			(
				cast_i64x8_f64x8(a_),
				cast_i64x8_f64x8(b_)
			)
		);
#else
		return EmuSIMD::_underlying_impl::emulate_dual_lane_blend_with_mask<BlendMask_>(a_, b_, std::make_index_sequence<4>());
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
	EMU_SIMD_COMMON_FUNC_SPEC auto emulate_fp_i64x8(Func_ func_, EmuSIMD::i64x8_arg in_)
		-> std::enable_if_t<std::is_invocable_r_v<EmuSIMD::f64x8, decltype(func_), EmuSIMD::f64x8>, EmuSIMD::i64x8>
	{
		return cvt_f64x8_i64x8
		(
			func_(cvt_i64x8_f64x8(in_))
		);
	}
#pragma endregion

#pragma region EXTRACTION_TEMPLATES
	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 extract_f32x16_lane_i64x8(f32x16_arg a_)
	{
		static_assert(Index_ == 0, "Invalid SIMD lane extraction index: Extracting i64x8 lane from a f32x16 instance; the maximum index is 0 but this index has been exceeded.");
		return cast_f32x16_i64x8(a_);
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 extract_f64x8_lane_i64x8(f64x8_arg a_)
	{
		static_assert(Index_ == 0, "Invalid SIMD lane extraction index: Extracting i64x8 lane from a f64x8 instance; the maximum index is 0 but this index has been exceeded.");
		return cast_f64x8_i64x8(a_);
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 extract_i8x64_lane_i64x8(i8x64_arg a_)
	{
		static_assert(Index_ == 0, "Invalid SIMD lane extraction index: Extracting i64x8 lane from a i8x64 instance; the maximum index is 0 but this index has been exceeded.");
		return cast_i8x64_i64x8(a_);
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 extract_i16x32_lane_i64x8(i16x32_arg a_)
	{
		static_assert(Index_ == 0, "Invalid SIMD lane extraction index: Extracting i64x8 lane from a i16x32 instance; the maximum index is 0 but this index has been exceeded.");
		return cast_i16x32_i64x8(a_);
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 extract_i32x16_lane_i64x8(i32x16_arg a_)
	{
		static_assert(Index_ == 0, "Invalid SIMD lane extraction index: Extracting i64x8 lane from a i32x16 instance; the maximum index is 0 but this index has been exceeded.");
		return cast_i32x16_i64x8(a_);
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 extract_i64x8_lane_i64x8(i64x8_arg a_)
	{
		static_assert(Index_ == 0, "Invalid SIMD lane extraction index: Extracting i64x8 lane from a i64x8 instance; the maximum index is 0 but this index has been exceeded.");
		return a_;
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 extract_u8x64_lane_i64x8(u8x64_arg a_)
	{
		static_assert(Index_ == 0, "Invalid SIMD lane extraction index: Extracting i64x8 lane from a u8x64 instance; the maximum index is 0 but this index has been exceeded.");
		return cast_u8x64_i64x8(a_);
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 extract_u16x32_lane_i64x8(u16x32_arg a_)
	{
		static_assert(Index_ == 0, "Invalid SIMD lane extraction index: Extracting i64x8 lane from a u16x32 instance; the maximum index is 0 but this index has been exceeded.");
		return cast_u16x32_i64x8(a_);
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 extract_u32x16_lane_i64x8(u32x16_arg a_)
	{
		static_assert(Index_ == 0, "Invalid SIMD lane extraction index: Extracting i64x8 lane from a u32x16 instance; the maximum index is 0 but this index has been exceeded.");
		return cast_u32x16_i64x8(a_);
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 extract_u64x8_lane_i64x8(u64x8_arg a_)
	{
		static_assert(Index_ == 0, "Invalid SIMD lane extraction index: Extracting i64x8 lane from a u64x8 instance; the maximum index is 0 but this index has been exceeded.");
		return cast_u64x8_i64x8(a_);
	}
#pragma endregion

#pragma region GET_TEMPLATES
	template<std::size_t Index_, typename OutT_ = std::int64_t>
	EMU_SIMD_COMMON_FUNC_SPEC auto extract_element_i64x8(i64x8_arg in_)
		-> typename std::remove_cvref<OutT_>::type
	{
		if constexpr (Index_ == 0)
		{
			return static_cast<typename std::remove_cvref<OutT_>::type>(EmuSIMD::Funcs::get_first_i64x8(in_));
		}
		else
		{
			if constexpr (Index_ <= 7)
			{
#if EMU_SIMD_USE_512_REGISTERS
				constexpr std::size_t elements_per_chunk = 2;
				constexpr std::size_t chunk_index = static_cast<std::size_t>(Index_ / elements_per_chunk);
				constexpr std::size_t index_in_chunk = Index_ - (chunk_index * elements_per_chunk);
				return EmuSIMD::Funcs::extract_element_i64x2<index_in_chunk, OutT_>(EmuSIMD::Funcs::extract_i64x8_lane_i64x2<chunk_index>(in_));
#else
				return EmuSIMD::_underlying_impl::retrieve_emulated_dual_lane_simd_element<OutT_, Index_, false, 4>(in_);
#endif
			}
			else
			{
				static_assert
				(
					EmuCore::TMP::get_false<std::size_t, Index_>(),
					"Invalid index provided when extracting an element from a i64x8 instance. Valid indices are 0, 1, 2, 3, 4, 5, 6, 7."
				);
			}
		}
	}
#pragma endregion
}

#endif
