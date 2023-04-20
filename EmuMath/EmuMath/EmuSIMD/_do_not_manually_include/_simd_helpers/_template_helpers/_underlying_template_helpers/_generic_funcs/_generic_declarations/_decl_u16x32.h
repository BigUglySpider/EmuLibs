#ifndef EMU_SIMD_GENERIC_FUNCS_U16X32_DECL_H_INC_
#define EMU_SIMD_GENERIC_FUNCS_U16X32_DECL_H_INC_ 1

#include "../_common_generic_func_helpers.h"
#include "_decl_f32x16.h"
#include "_decl_u16x32.h"

namespace EmuSIMD::Funcs
{
#pragma region SETTERS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 set_u16x32
	(
		std::uint16_t e0, std::uint16_t e1, std::uint16_t e2, std::uint16_t e3, std::uint16_t e4, std::uint16_t e5, std::uint16_t e6, std::uint16_t e7,
		std::uint16_t e8, std::uint16_t e9, std::uint16_t e10, std::uint16_t e11, std::uint16_t e12, std::uint16_t e13, std::uint16_t e14, std::uint16_t e15,
		std::uint16_t e16, std::uint16_t e17, std::uint16_t e18, std::uint16_t e19, std::uint16_t e20, std::uint16_t e21, std::uint16_t e22, std::uint16_t e23,
		std::uint16_t e24, std::uint16_t e25, std::uint16_t e26, std::uint16_t e27, std::uint16_t e28, std::uint16_t e29, std::uint16_t e30, std::uint16_t e31
	);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 setr_u16x32
	(
		std::uint16_t e0, std::uint16_t e1, std::uint16_t e2, std::uint16_t e3, std::uint16_t e4, std::uint16_t e5, std::uint16_t e6, std::uint16_t e7,
		std::uint16_t e8, std::uint16_t e9, std::uint16_t e10, std::uint16_t e11, std::uint16_t e12, std::uint16_t e13, std::uint16_t e14, std::uint16_t e15,
		std::uint16_t e16, std::uint16_t e17, std::uint16_t e18, std::uint16_t e19, std::uint16_t e20, std::uint16_t e21, std::uint16_t e22, std::uint16_t e23,
		std::uint16_t e24, std::uint16_t e25, std::uint16_t e26, std::uint16_t e27, std::uint16_t e28, std::uint16_t e29, std::uint16_t e30, std::uint16_t e31
	);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 set1_u16x32(std::uint16_t all_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 load_u16x32(const std::uint16_t* p_to_load_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 setzero_u16x32();
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 setmasked_u16x32(std::uint32_t bit_mask_);
#pragma endregion

#pragma region STORES
	EMU_SIMD_COMMON_FUNC_SPEC void store_u16x32(std::uint16_t* p_out_, u16x32_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC std::uint16_t get_first_u16x32(u16x32_arg a_);
#pragma endregion

#pragma region CASTS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 cast_f32x4_u16x32(f32x4_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 cast_f32x8_u16x32(f32x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 cast_f32x16_u16x32(f32x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 cast_f64x2_u16x32(f64x2_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 cast_f64x4_u16x32(f64x4_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 cast_f64x8_u16x32(f64x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 cast_i8x16_u16x32(i8x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 cast_i16x8_u16x32(i16x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 cast_i32x4_u16x32(i32x4_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 cast_i64x2_u16x32(i64x2_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 cast_i8x32_u16x32(i8x32_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 cast_i16x16_u16x32(i16x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 cast_i32x8_u16x32(i32x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 cast_i64x4_u16x32(i64x4_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 cast_i8x64_u16x32(i8x64_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 cast_i16x32_u16x32(i16x32_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 cast_i32x16_u16x32(i32x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 cast_i64x8_u16x32(i64x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 cast_u8x16_u16x32(u8x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 cast_u16x8_u16x32(u16x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 cast_u32x4_u16x32(u32x4_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 cast_u64x2_u16x32(u64x2_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 cast_u8x32_u16x32(u8x32_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 cast_u16x16_u16x32(u16x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 cast_u32x8_u16x32(u32x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 cast_u64x4_u16x32(u64x4_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 cast_u8x64_u16x32(u8x64_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 cast_u16x32_u16x32(u16x32_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 cast_u32x16_u16x32(u32x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 cast_u64x8_u16x32(u64x8_arg a_);
#pragma endregion

#pragma region CONVERSIONS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 cvt_f32x4_u16x32(f32x4_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 cvt_f32x8_u16x32(f32x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 cvt_f32x16_u16x32(f32x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 cvt_f64x2_u16x32(f64x2_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 cvt_f64x4_u16x32(f64x4_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 cvt_f64x8_u16x32(f64x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 cvt_i8x16_u16x32(i8x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 cvt_i16x8_u16x32(i16x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 cvt_i32x4_u16x32(i32x4_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 cvt_i64x2_u16x32(i64x2_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 cvt_i8x32_u16x32(i8x32_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 cvt_i16x16_u16x32(i16x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 cvt_i32x8_u16x32(i32x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 cvt_i64x4_u16x32(i64x4_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 cvt_i8x64_u16x32(i8x64_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 cvt_i16x32_u16x32(i16x32_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 cvt_i32x16_u16x32(i32x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 cvt_i64x8_u16x32(i64x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 cvt_u8x16_u16x32(u8x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 cvt_u16x8_u16x32(u16x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 cvt_u32x4_u16x32(u32x4_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 cvt_u64x2_u16x32(u64x2_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 cvt_u8x32_u16x32(u8x32_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 cvt_u16x16_u16x32(u16x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 cvt_u32x8_u16x32(u32x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 cvt_u64x4_u16x32(u64x4_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 cvt_u8x64_u16x32(u8x64_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 cvt_u16x32_u16x32(u16x32_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 cvt_u32x16_u16x32(u32x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 cvt_u64x8_u16x32(u64x8_arg a_);
#pragma endregion

#pragma region COMPARISONS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 cmpeq_u16x32(EmuSIMD::u16x32_arg lhs_, EmuSIMD::u16x32_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 cmpneq_u16x32(EmuSIMD::u16x32_arg lhs_, EmuSIMD::u16x32_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 cmpgt_u16x32(EmuSIMD::u16x32_arg lhs_, EmuSIMD::u16x32_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 cmplt_u16x32(EmuSIMD::u16x32_arg lhs_, EmuSIMD::u16x32_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 cmpge_u16x32(EmuSIMD::u16x32_arg lhs_, EmuSIMD::u16x32_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 cmple_u16x32(EmuSIMD::u16x32_arg lhs_, EmuSIMD::u16x32_arg rhs_);
#pragma endregion

#pragma region MOVES
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 movehl_u16x32(EmuSIMD::u16x32_arg lhs_, EmuSIMD::u16x32_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 movelh_u16x32(EmuSIMD::u16x32_arg lhs_, EmuSIMD::u16x32_arg rhs_);
#pragma endregion

#pragma region BITWISE_ARITHMETIC
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x32 and_i16x32(EmuSIMD::i16x32_arg lhs_, EmuSIMD::i16x32_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x32 or_i16x32(EmuSIMD::i16x32_arg lhs_, EmuSIMD::i16x32_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x32 xor_i16x32(EmuSIMD::i16x32_arg lhs_, EmuSIMD::i16x32_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x32 andnot_i16x32(EmuSIMD::i16x32_arg not_lhs_, EmuSIMD::i16x32_arg rhs_);
	template<std::int32_t NumShifts_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 shift_left_u16x32(EmuSIMD::u16x32_arg lhs_);
	template<std::int32_t NumShifts_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 shift_right_arithmetic_u16x32(EmuSIMD::u16x32_arg lhs_);
	template<std::int32_t NumShifts_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 shift_right_logical_u16x32(EmuSIMD::u16x32_arg lhs_);
#pragma endregion

#pragma region BLENDS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 blendv_u16x32(EmuSIMD::u16x32_arg a_, EmuSIMD::u16x32_arg b_, EmuSIMD::u16x32_arg shuffle_mask_vec_);
#pragma endregion

#pragma region MINMAX_FUNCS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 min_u16x32(EmuSIMD::u16x32_arg a_, EmuSIMD::u16x32_arg b_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 max_u16x32(EmuSIMD::u16x32_arg a_, EmuSIMD::u16x32_arg b_);
#pragma endregion

#pragma region BASIC_ARITHMETIC
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 mul_all_u16x32(EmuSIMD::u16x32_arg lhs_, EmuSIMD::u16x32_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 negate_u16x32(EmuSIMD::u16x32_arg to_negate_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 add_u16x32(EmuSIMD::u16x32_arg lhs_, EmuSIMD::u16x32_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 sub_u16x32(EmuSIMD::u16x32_arg lhs_, EmuSIMD::u16x32_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 mul_u16x32(EmuSIMD::u16x32_arg lhs_, EmuSIMD::u16x32_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 div_u16x32(EmuSIMD::u16x32_arg lhs_, EmuSIMD::u16x32_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 addsub_u16x32(EmuSIMD::u16x32_arg lhs_, EmuSIMD::u16x32_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 subadd_u16x32(EmuSIMD::u16x32_arg lhs_, EmuSIMD::u16x32_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 fmadd_u16x32(EmuSIMD::u16x32_arg a_, EmuSIMD::u16x32_arg b_, EmuSIMD::u16x32_arg c_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 fmsub_u16x32(EmuSIMD::u16x32_arg a_, EmuSIMD::u16x32_arg b_, EmuSIMD::u16x32_arg c_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 fnmadd_u16x32(EmuSIMD::u16x32_arg a_, EmuSIMD::u16x32_arg b_, EmuSIMD::u16x32_arg c_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 fnmsub_u16x32(EmuSIMD::u16x32_arg a_, EmuSIMD::u16x32_arg b_, EmuSIMD::u16x32_arg c_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 fmaddsub_u16x32(EmuSIMD::u16x32_arg a_, EmuSIMD::u16x32_arg b_, EmuSIMD::u16x32_arg c_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 fmsubadd_u16x32(EmuSIMD::u16x32_arg a_, EmuSIMD::u16x32_arg b_, EmuSIMD::u16x32_arg c_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 floor_u16x32(EmuSIMD::u16x32_arg to_floor_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 ceil_u16x32(EmuSIMD::u16x32_arg to_ceil_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 trunc_u16x32(EmuSIMD::u16x32_arg to_trunc_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 mod_u16x32(EmuSIMD::u16x32_arg lhs_, EmuSIMD::u16x32_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 abs_u16x32(EmuSIMD::u16x32_arg in_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 sqrt_u16x32(EmuSIMD::u16x32_arg in_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 rsqrt_u16x32(EmuSIMD::u16x32_arg in_);
#pragma endregion

#pragma region NEAR_COMPARISONS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 cmpnear_u16x32(EmuSIMD::u16x32_arg lhs_, EmuSIMD::u16x32_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 cmpnear_u16x32(EmuSIMD::u16x32_arg lhs_, EmuSIMD::u16x32_arg rhs_, EmuSIMD::u16x32_arg epsilon);
#pragma endregion

#pragma region TRIG
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 cos_u16x32(EmuSIMD::u16x32_arg in_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 sin_u16x32(EmuSIMD::u16x32_arg in_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 tan_u16x32(EmuSIMD::u16x32_arg in_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 acos_u16x32(EmuSIMD::u16x32_arg in_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 asin_u16x32(EmuSIMD::u16x32_arg in_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 atan_u16x32(EmuSIMD::u16x32_arg in_);
#pragma endregion

#pragma region ROUNDING_TEMPLATES
	template<int RoundingFlag_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 round_u16x32(EmuSIMD::u16x32_arg to_round_)
	{
		return to_round_;
	}
#pragma endregion

#pragma region SHUFFLE_TEMPLATES
	template<EmuSIMD::Funcs::shuffle_mask_type ShuffleMask_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 permute_u16x32(EmuSIMD::u16x32_arg a_)
	{
		static_assert(EmuCore::TMP::get_false<ShuffleMask_>(), "NO SUPPORT ERROR: EmuSIMD does not provide support for permuting u16x32 (512-bit registers containing 32 16-bit unsigned integer elements) [permute_u16x32].");
		return EmuSIMD::u16x32{};
	}

	template<EmuSIMD::Funcs::shuffle_mask_type ShuffleMask_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 shuffle_u16x32(EmuSIMD::u16x32_arg a_, EmuSIMD::u16x32_arg b_)
	{
		static_assert(EmuCore::TMP::get_false<ShuffleMask_>(), "NO SUPPORT ERROR: EmuSIMD does not provide support for shuffling u16x32 (512-bit registers containing 32 16-bit unsigned integer elements) [shuffle_u16x32].");
		return EmuSIMD::u16x32{};
	}
#pragma endregion

#pragma region BLEND_TEMPLATES
	template<EmuSIMD::Funcs::blend_mask_type BlendMask_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 blend_u16x32(EmuSIMD::u16x32_arg a_, EmuSIMD::u16x32_arg b_)
	{
		constexpr auto lo_blend_mask = BlendMask_;
		constexpr auto hi_blend_mask = BlendMask_ >> 16;

		EmuSIMD::u16x16 lo = _mm512_castsi512_si256(a_);
		EmuSIMD::u16x16 half_b = _mm512_castsi512_si256(b_);
		lo = _mm256_blend_epi16(lo, half_b, lo_blend_mask);

		EmuSIMD::u16x16 hi = _mm512_extracti32x8_epi32(a_, 1);
		half_b = _mm512_extracti32x8_epi32(b_, 1);
		hi = _mm256_blend_epi16(hi, half_b, hi_blend_mask);

		return _mm512_inserti32x8(cast_u8x32_u16x32(lo), hi, 1);
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
	EMU_SIMD_COMMON_FUNC_SPEC auto emulate_fp_u16x32(Func_ func_, EmuSIMD::u16x32_arg in_)
		-> std::enable_if_t<std::is_invocable_r_v<EmuSIMD::f32x16, decltype(func_), EmuSIMD::f32x16>, EmuSIMD::u16x32>
	{
		constexpr std::size_t num_elements = 32;
		constexpr std::size_t elements_per_register = 16;
		std::uint16_t data[num_elements];
		float results[num_elements];

		store_u16x32(data, in_);
		for (std::size_t i = 0; i < num_elements; i += elements_per_register)
		{
			store_f32x16
			(
				results + i,
				func_
				(
					set_f32x16
					(
						static_cast<float>(data[i + 15]), static_cast<float>(data[i + 14]), static_cast<float>(data[i + 13]), static_cast<float>(data[i + 12]),
						static_cast<float>(data[i + 11]), static_cast<float>(data[i + 10]), static_cast<float>(data[i + 9]), static_cast<float>(data[i + 8]),
						static_cast<float>(data[i + 7]), static_cast<float>(data[i + 6]), static_cast<float>(data[i + 5]), static_cast<float>(data[i + 4]),
						static_cast<float>(data[i + 3]), static_cast<float>(data[i + 2]), static_cast<float>(data[i + 1]), static_cast<float>(data[i])
					)
				)
			);
		}

		return set_u16x32
		(
			static_cast<std::uint16_t>(results[31]),
			static_cast<std::uint16_t>(results[30]),
			static_cast<std::uint16_t>(results[29]),
			static_cast<std::uint16_t>(results[28]),
			static_cast<std::uint16_t>(results[27]),
			static_cast<std::uint16_t>(results[26]),
			static_cast<std::uint16_t>(results[25]),
			static_cast<std::uint16_t>(results[24]),
			static_cast<std::uint16_t>(results[23]),
			static_cast<std::uint16_t>(results[22]),
			static_cast<std::uint16_t>(results[21]),
			static_cast<std::uint16_t>(results[20]),
			static_cast<std::uint16_t>(results[19]),
			static_cast<std::uint16_t>(results[18]),
			static_cast<std::uint16_t>(results[17]),
			static_cast<std::uint16_t>(results[16]),
			static_cast<std::uint16_t>(results[15]),
			static_cast<std::uint16_t>(results[14]),
			static_cast<std::uint16_t>(results[13]),
			static_cast<std::uint16_t>(results[12]),
			static_cast<std::uint16_t>(results[11]),
			static_cast<std::uint16_t>(results[10]),
			static_cast<std::uint16_t>(results[9]),
			static_cast<std::uint16_t>(results[8]),
			static_cast<std::uint16_t>(results[7]),
			static_cast<std::uint16_t>(results[6]),
			static_cast<std::uint16_t>(results[5]),
			static_cast<std::uint16_t>(results[4]),
			static_cast<std::uint16_t>(results[3]),
			static_cast<std::uint16_t>(results[2]),
			static_cast<std::uint16_t>(results[1]),
			static_cast<std::uint16_t>(results[0])
		);
	}
#pragma endregion

#pragma region EXTRACTION_TEMPLATES
	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 extract_f32x16_lane_u16x32(f32x16_arg a_)
	{
		static_assert(Index_ == 0, "Invalid SIMD lane extraction index: Extracting u16x32 lane from a f32x16 instance; the maximum index is 0 but this index has been exceeded.");
		return cast_f32x16_u16x32(a_);
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 extract_f64x8_lane_u16x32(f64x8_arg a_)
	{
		static_assert(Index_ == 0, "Invalid SIMD lane extraction index: Extracting u16x32 lane from a f64x8 instance; the maximum index is 0 but this index has been exceeded.");
		return cast_f64x8_u16x32(a_);
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 extract_i8x64_lane_u16x32(i8x64_arg a_)
	{
		static_assert(Index_ == 0, "Invalid SIMD lane extraction index: Extracting u16x32 lane from a i8x64 instance; the maximum index is 0 but this index has been exceeded.");
		return cast_i8x64_u16x32(a_);
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 extract_i16x32_lane_u16x32(i16x32_arg a_)
	{
		static_assert(Index_ == 0, "Invalid SIMD lane extraction index: Extracting u16x32 lane from a i16x32 instance; the maximum index is 0 but this index has been exceeded.");
		return cast_i16x32_u16x32(a_);
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 extract_i32x16_lane_u16x32(i32x16_arg a_)
	{
		static_assert(Index_ == 0, "Invalid SIMD lane extraction index: Extracting u16x32 lane from a i32x16 instance; the maximum index is 0 but this index has been exceeded.");
		return cast_i32x16_u16x32(a_);
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 extract_i64x8_lane_u16x32(i64x8_arg a_)
	{
		static_assert(Index_ == 0, "Invalid SIMD lane extraction index: Extracting u16x32 lane from a i64x8 instance; the maximum index is 0 but this index has been exceeded.");
		return cast_i64x8_u16x32(a_);
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 extract_u8x64_lane_u16x32(u8x64_arg a_)
	{
		static_assert(Index_ == 0, "Invalid SIMD lane extraction index: Extracting u16x32 lane from a u8x64 instance; the maximum index is 0 but this index has been exceeded.");
		return cast_u8x64_u16x32(a_);
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 extract_u16x32_lane_u16x32(u16x32_arg a_)
	{
		static_assert(Index_ == 0, "Invalid SIMD lane extraction index: Extracting u16x32 lane from a u16x32 instance; the maximum index is 0 but this index has been exceeded.");
		return a_;
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 extract_u32x16_lane_u16x32(u32x16_arg a_)
	{
		static_assert(Index_ == 0, "Invalid SIMD lane extraction index: Extracting u16x32 lane from a u32x16 instance; the maximum index is 0 but this index has been exceeded.");
		return cast_u32x16_u16x32(a_);
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 extract_u64x8_lane_u16x32(u64x8_arg a_)
	{
		static_assert(Index_ == 0, "Invalid SIMD lane extraction index: Extracting u16x32 lane from a u64x8 instance; the maximum index is 0 but this index has been exceeded.");
		return cast_u64x8_u16x32(a_);
	}
#pragma endregion

#pragma region GET_TEMPLATES
	template<std::size_t Index_, typename OutT_ = std::uint16_t>
	EMU_SIMD_COMMON_FUNC_SPEC auto extract_element_u16x32(u16x32_arg in_)
		-> typename std::remove_cvref<OutT_>::type
	{
		if constexpr (Index_ == 0)
		{
			return static_cast<typename std::remove_cvref<OutT_>::type>(EmuSIMD::Funcs::get_first_i16x32(in_));
		}
		else
		{
			if constexpr (Index_ <= 31)
			{
#if EMU_SIMD_USE_512_REGISTERS
				constexpr std::size_t elements_per_chunk = 8;
				constexpr std::size_t chunk_index = static_cast<std::size_t>(Index_ / elements_per_chunk);
				constexpr std::size_t index_in_chunk = Index_ - (chunk_index * elements_per_chunk);
				return EmuSIMD::Funcs::extract_element_u16x8<index_in_chunk, OutT_>(EmuSIMD::Funcs::extract_u16x32_lane_u16x8<chunk_index>(in_));
#else
				return EmuSIMD::_underlying_impl::retrieve_emulated_dual_lane_simd_element<OutT_, Index_, false, 16>(in_);
#endif
			}
			else
			{
				static_assert
				(
					EmuCore::TMP::get_false<std::size_t, Index_>(),
					"Invalid index provided when extracting an element from a u16x32 instance. Valid indices are 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31."
				);
			}
		}
	}
#pragma endregion
}

#endif
