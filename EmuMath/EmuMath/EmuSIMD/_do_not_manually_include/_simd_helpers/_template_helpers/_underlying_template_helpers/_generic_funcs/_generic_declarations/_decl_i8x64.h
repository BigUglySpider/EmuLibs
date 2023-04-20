#ifndef EMU_SIMD_GENERIC_FUNCS_I8X64_DECL_H_INC_
#define EMU_SIMD_GENERIC_FUNCS_I8X64_DECL_H_INC_ 1

#include "../_common_generic_func_helpers.h"
#include "_decl_f32x16.h"
#include "_decl_i8x16.h"

namespace EmuSIMD::Funcs
{
#pragma region SETTERS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x64 set_i8x64
	(
		std::int8_t e0, std::int8_t e1, std::int8_t e2, std::int8_t e3, std::int8_t e4, std::int8_t e5, std::int8_t e6, std::int8_t e7,
		std::int8_t e8, std::int8_t e9, std::int8_t e10, std::int8_t e11, std::int8_t e12, std::int8_t e13, std::int8_t e14, std::int8_t e15,
		std::int8_t e16, std::int8_t e17, std::int8_t e18, std::int8_t e19, std::int8_t e20, std::int8_t e21, std::int8_t e22, std::int8_t e23,
		std::int8_t e24, std::int8_t e25, std::int8_t e26, std::int8_t e27, std::int8_t e28, std::int8_t e29, std::int8_t e30, std::int8_t e31,
		std::int8_t e32, std::int8_t e33, std::int8_t e34, std::int8_t e35, std::int8_t e36, std::int8_t e37, std::int8_t e38, std::int8_t e39,
		std::int8_t e40, std::int8_t e41, std::int8_t e42, std::int8_t e43, std::int8_t e44, std::int8_t e45, std::int8_t e46, std::int8_t e47,
		std::int8_t e48, std::int8_t e49, std::int8_t e50, std::int8_t e51, std::int8_t e52, std::int8_t e53, std::int8_t e54, std::int8_t e55,
		std::int8_t e56, std::int8_t e57, std::int8_t e58, std::int8_t e59, std::int8_t e60, std::int8_t e61, std::int8_t e62, std::int8_t e63
	);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x64 setr_i8x64
	(
		std::int8_t e0, std::int8_t e1, std::int8_t e2, std::int8_t e3, std::int8_t e4, std::int8_t e5, std::int8_t e6, std::int8_t e7,
		std::int8_t e8, std::int8_t e9, std::int8_t e10, std::int8_t e11, std::int8_t e12, std::int8_t e13, std::int8_t e14, std::int8_t e15,
		std::int8_t e16, std::int8_t e17, std::int8_t e18, std::int8_t e19, std::int8_t e20, std::int8_t e21, std::int8_t e22, std::int8_t e23,
		std::int8_t e24, std::int8_t e25, std::int8_t e26, std::int8_t e27, std::int8_t e28, std::int8_t e29, std::int8_t e30, std::int8_t e31,
		std::int8_t e32, std::int8_t e33, std::int8_t e34, std::int8_t e35, std::int8_t e36, std::int8_t e37, std::int8_t e38, std::int8_t e39,
		std::int8_t e40, std::int8_t e41, std::int8_t e42, std::int8_t e43, std::int8_t e44, std::int8_t e45, std::int8_t e46, std::int8_t e47,
		std::int8_t e48, std::int8_t e49, std::int8_t e50, std::int8_t e51, std::int8_t e52, std::int8_t e53, std::int8_t e54, std::int8_t e55,
		std::int8_t e56, std::int8_t e57, std::int8_t e58, std::int8_t e59, std::int8_t e60, std::int8_t e61, std::int8_t e62, std::int8_t e63
	);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x64 set1_i8x64(std::int8_t all_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x64 load_i8x64(const std::int8_t* p_to_load_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x64 setzero_i8x64();
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x64 setmasked_i8x64(std::uint64_t bit_mask_);
#pragma endregion

#pragma region STORES
	EMU_SIMD_COMMON_FUNC_SPEC void store_i8x64(std::int8_t* p_out_, i8x64_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC std::int8_t get_first_i8x64(i8x64_arg a_);
#pragma endregion

#pragma region CASTS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x64 cast_f32x4_i8x64(f32x4_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x64 cast_f32x8_i8x64(f32x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x64 cast_f32x16_i8x64(f32x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x64 cast_f64x2_i8x64(f64x2_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x64 cast_f64x4_i8x64(f64x4_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x64 cast_f64x8_i8x64(f64x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x64 cast_i8x16_i8x64(i8x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x64 cast_i16x8_i8x64(i16x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x64 cast_i32x4_i8x64(i32x4_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x64 cast_i64x2_i8x64(i64x2_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x64 cast_i8x32_i8x64(i8x32_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x64 cast_i16x16_i8x64(i16x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x64 cast_i32x8_i8x64(i32x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x64 cast_i64x4_i8x64(i64x4_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x64 cast_i8x64_i8x64(i8x64_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x64 cast_i16x32_i8x64(i16x32_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x64 cast_i32x16_i8x64(i32x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x64 cast_i64x8_i8x64(i64x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x64 cast_u8x16_i8x64(u8x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x64 cast_u16x8_i8x64(u16x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x64 cast_u32x4_i8x64(u32x4_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x64 cast_u64x2_i8x64(u64x2_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x64 cast_u8x32_i8x64(u8x32_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x64 cast_u16x16_i8x64(u16x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x64 cast_u32x8_i8x64(u32x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x64 cast_u64x4_i8x64(u64x4_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x64 cast_u8x64_i8x64(u8x64_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x64 cast_u16x32_i8x64(u16x32_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x64 cast_u32x16_i8x64(u32x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x64 cast_u64x8_i8x64(u64x8_arg a_);
#pragma endregion

#pragma region CONVERSIONS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x64 cvt_f32x4_i8x64(f32x4_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x64 cvt_f32x8_i8x64(f32x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x64 cvt_f32x16_i8x64(f32x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x64 cvt_f64x2_i8x64(f64x2_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x64 cvt_f64x4_i8x64(f64x4_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x64 cvt_f64x8_i8x64(f64x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x64 cvt_i8x16_i8x64(i8x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x64 cvt_i16x8_i8x64(i16x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x64 cvt_i32x4_i8x64(i32x4_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x64 cvt_i64x2_i8x64(i64x2_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x64 cvt_i8x32_i8x64(i8x32_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x64 cvt_i16x16_i8x64(i16x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x64 cvt_i32x8_i8x64(i32x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x64 cvt_i64x4_i8x64(i64x4_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x64 cvt_i8x64_i8x64(i8x64_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x64 cvt_i16x32_i8x64(i16x32_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x64 cvt_i32x16_i8x64(i32x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x64 cvt_i64x8_i8x64(i64x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x64 cvt_u8x16_i8x64(u8x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x64 cvt_u16x8_i8x64(u16x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x64 cvt_u32x4_i8x64(u32x4_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x64 cvt_u64x2_i8x64(u64x2_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x64 cvt_u8x32_i8x64(u8x32_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x64 cvt_u16x16_i8x64(u16x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x64 cvt_u32x8_i8x64(u32x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x64 cvt_u64x4_i8x64(u64x4_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x64 cvt_u8x64_i8x64(u8x64_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x64 cvt_u16x32_i8x64(u16x32_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x64 cvt_u32x16_i8x64(u32x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x64 cvt_u64x8_i8x64(u64x8_arg a_);
#pragma endregion

#pragma region COMPARISONS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x64 cmpeq_i8x64(EmuSIMD::i8x64_arg lhs_, EmuSIMD::i8x64_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x64 cmpneq_i8x64(EmuSIMD::i8x64_arg lhs_, EmuSIMD::i8x64_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x64 cmpgt_i8x64(EmuSIMD::i8x64_arg lhs_, EmuSIMD::i8x64_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x64 cmplt_i8x64(EmuSIMD::i8x64_arg lhs_, EmuSIMD::i8x64_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x64 cmpge_i8x64(EmuSIMD::i8x64_arg lhs_, EmuSIMD::i8x64_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x64 cmple_i8x64(EmuSIMD::i8x64_arg lhs_, EmuSIMD::i8x64_arg rhs_);
#pragma endregion

#pragma region MOVES
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x64 movehl_i8x64(EmuSIMD::i8x64_arg lhs_, EmuSIMD::i8x64_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x64 movelh_i8x64(EmuSIMD::i8x64_arg lhs_, EmuSIMD::i8x64_arg rhs_);
#pragma endregion

#pragma region BITWISE_ARITHMETIC
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x64 and_i8x64(EmuSIMD::i8x64_arg lhs_, EmuSIMD::i8x64_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x64 or_i8x64(EmuSIMD::i8x64_arg lhs_, EmuSIMD::i8x64_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x64 xor_i8x64(EmuSIMD::i8x64_arg lhs_, EmuSIMD::i8x64_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x64 andnot_i8x64(EmuSIMD::i8x64_arg not_lhs_, EmuSIMD::i8x64_arg rhs_);
	template<std::int32_t NumShifts_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x64 shift_left_i8x64(EmuSIMD::i8x64_arg lhs_);
	template<std::int32_t NumShifts_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x64 shift_right_arithmetic_i8x64(EmuSIMD::i8x64_arg lhs_);
	template<std::int32_t NumShifts_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x64 shift_right_logical_i8x64(EmuSIMD::i8x64_arg lhs_);
#pragma endregion

#pragma region BLENDS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x64 blendv_i8x64(EmuSIMD::i8x64_arg a_, EmuSIMD::i8x64_arg b_, EmuSIMD::i8x64_arg shuffle_mask_vec_);
#pragma endregion

#pragma region MINMAX_FUNCS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x64 min_i8x64(EmuSIMD::i8x64_arg a_, EmuSIMD::i8x64_arg b_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x64 max_i8x64(EmuSIMD::i8x64_arg a_, EmuSIMD::i8x64_arg b_);
#pragma endregion

#pragma region BASIC_ARITHMETIC
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x64 mul_all_i8x64(EmuSIMD::i8x64_arg lhs_, EmuSIMD::i8x64_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x64 negate_i8x64(EmuSIMD::i8x64_arg to_negate_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x64 add_i8x64(EmuSIMD::i8x64_arg lhs_, EmuSIMD::i8x64_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x64 sub_i8x64(EmuSIMD::i8x64_arg lhs_, EmuSIMD::i8x64_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x64 mul_i8x64(EmuSIMD::i8x64_arg lhs_, EmuSIMD::i8x64_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x64 div_i8x64(EmuSIMD::i8x64_arg lhs_, EmuSIMD::i8x64_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x64 addsub_i8x64(EmuSIMD::i8x64_arg lhs_, EmuSIMD::i8x64_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x64 subadd_i8x64(EmuSIMD::i8x64_arg lhs_, EmuSIMD::i8x64_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x64 fmadd_i8x64(EmuSIMD::i8x64_arg a_, EmuSIMD::i8x64_arg b_, EmuSIMD::i8x64_arg c_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x64 fmsub_i8x64(EmuSIMD::i8x64_arg a_, EmuSIMD::i8x64_arg b_, EmuSIMD::i8x64_arg c_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x64 fnmadd_i8x64(EmuSIMD::i8x64_arg a_, EmuSIMD::i8x64_arg b_, EmuSIMD::i8x64_arg c_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x64 fnmsub_i8x64(EmuSIMD::i8x64_arg a_, EmuSIMD::i8x64_arg b_, EmuSIMD::i8x64_arg c_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x64 fmaddsub_i8x64(EmuSIMD::i8x64_arg a_, EmuSIMD::i8x64_arg b_, EmuSIMD::i8x64_arg c_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x64 fmsubadd_i8x64(EmuSIMD::i8x64_arg a_, EmuSIMD::i8x64_arg b_, EmuSIMD::i8x64_arg c_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x64 floor_i8x64(EmuSIMD::i8x64_arg to_floor_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x64 ceil_i8x64(EmuSIMD::i8x64_arg to_ceil_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x64 trunc_i8x64(EmuSIMD::i8x64_arg to_trunc_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x64 mod_i8x64(EmuSIMD::i8x64_arg lhs_, EmuSIMD::i8x64_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x64 abs_i8x64(EmuSIMD::i8x64_arg in_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x64 sqrt_i8x64(EmuSIMD::i8x64_arg in_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x64 rsqrt_i8x64(EmuSIMD::i8x64_arg in_);
#pragma endregion

#pragma region NEAR_COMPARISONS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x64 cmpnear_i8x64(EmuSIMD::i8x64_arg lhs_, EmuSIMD::i8x64_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x64 cmpnear_i8x64(EmuSIMD::i8x64_arg lhs_, EmuSIMD::i8x64_arg rhs_, EmuSIMD::i8x64_arg epsilon);
#pragma endregion

#pragma region TRIG
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x64 cos_i8x64(EmuSIMD::i8x64_arg in_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x64 sin_i8x64(EmuSIMD::i8x64_arg in_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x64 tan_i8x64(EmuSIMD::i8x64_arg in_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x64 acos_i8x64(EmuSIMD::i8x64_arg in_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x64 asin_i8x64(EmuSIMD::i8x64_arg in_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x64 atan_i8x64(EmuSIMD::i8x64_arg in_);
#pragma endregion

#pragma region ROUNDING_TEMPLATES
	template<int RoundingFlag_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x64 round_i8x64(EmuSIMD::i8x64_arg to_round_)
	{
		return to_round_;
	}
#pragma endregion

#pragma region SHUFFLE_TEMPLATES
	template<EmuSIMD::Funcs::shuffle_mask_type ShuffleMask_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x64 permute_i8x64(EmuSIMD::i8x64_arg a_)
	{
		constexpr bool is_reverse_set = false;
		using target_element_type = signed char;
		constexpr std::size_t argument_width = 4; // Max value of 15 (0b1111), per index
		constexpr std::size_t num_128_lanes = 4;

		return _mm512_shuffle_epi8
		(
			a_,
			EmuSIMD::Funcs::shuffle_mask_to_vector<ShuffleMask_, is_reverse_set, argument_width, num_128_lanes, target_element_type>
			(
				std::make_index_sequence<64>(),
				[](auto&&...args_) { return set_i8x64(std::forward<decltype(args_)>(args_)...); }
			)
		);
	}

	template<EmuSIMD::Funcs::shuffle_mask_type ShuffleMask_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x64 shuffle_i8x64(EmuSIMD::i8x64_arg a_, EmuSIMD::i8x64_arg b_)
	{
		constexpr std::size_t a_permute_mask = duplicate_shuffle_mask_32bit_lane<ShuffleMask_, true>();
		constexpr std::size_t b_permute_mask = duplicate_shuffle_mask_32bit_lane<ShuffleMask_, false>();

		EmuSIMD::i8x64 a_permuted = permute_i8x64<a_permute_mask>(a_);
		EmuSIMD::i8x64 b_permuted = permute_i8x64<b_permute_mask>(b_);

		// Use f32x16 reinterpretation to take the lo bits of permuted a and the lo bits of permuted b and combine them into one register, 
		// where lo(result) = lo(a), hi(result) = lo(b)
		// --- We take this approach as each permutation has been duplicated across 64-bit lanes within the respective permuted register
		EmuSIMD::f32x16 tmp_cast = cast_i8x64_f32x16(a_permuted);
		tmp_cast = movelh_f32x16(tmp_cast, cast_i8x64_f32x16(b_permuted));

		return cast_f32x16_i8x64(tmp_cast);
	}
#pragma endregion

#pragma region BLEND_TEMPLATES
	template<EmuSIMD::Funcs::blend_mask_type BlendMask>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x64 blend_i8x64(EmuSIMD::i8x64_arg a_, EmuSIMD::i8x64_arg b_)
	{
		constexpr bool is_reverse_set = false;
		using target_element_type = std::int8_t;
		constexpr std::size_t num_elements = 64;

		return blendv_i8x64
		(
			a_,
			b_,
			EmuSIMD::Funcs::blend_mask_to_vector<BlendMask, is_reverse_set, target_element_type>
			(
				std::make_index_sequence<num_elements>(),
				[](auto&&...args_) { return set_i8x64(std::forward<decltype(args_)>(args_)...); }
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
	EMU_SIMD_COMMON_FUNC_SPEC auto emulate_fp_i8x64(Func_ func_, EmuSIMD::i8x64_arg in_)
		-> std::enable_if_t<std::is_invocable_r_v<EmuSIMD::f32x16, decltype(func_), EmuSIMD::f32x16>, EmuSIMD::i8x64>
	{
		constexpr std::size_t num_elements = 64;
		constexpr std::size_t elements_per_register = 16;
		std::int8_t data[num_elements];
		float results[num_elements];

		store_i8x64(data, in_);
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

		return set_i8x64
		(
			static_cast<std::int8_t>(results[63]),
			static_cast<std::int8_t>(results[62]),
			static_cast<std::int8_t>(results[61]),
			static_cast<std::int8_t>(results[60]),
			static_cast<std::int8_t>(results[59]),
			static_cast<std::int8_t>(results[58]),
			static_cast<std::int8_t>(results[57]),
			static_cast<std::int8_t>(results[56]),
			static_cast<std::int8_t>(results[55]),
			static_cast<std::int8_t>(results[54]),
			static_cast<std::int8_t>(results[53]),
			static_cast<std::int8_t>(results[52]),
			static_cast<std::int8_t>(results[51]),
			static_cast<std::int8_t>(results[50]),
			static_cast<std::int8_t>(results[49]),
			static_cast<std::int8_t>(results[48]),
			static_cast<std::int8_t>(results[47]),
			static_cast<std::int8_t>(results[46]),
			static_cast<std::int8_t>(results[45]),
			static_cast<std::int8_t>(results[44]),
			static_cast<std::int8_t>(results[43]),
			static_cast<std::int8_t>(results[42]),
			static_cast<std::int8_t>(results[41]),
			static_cast<std::int8_t>(results[40]),
			static_cast<std::int8_t>(results[39]),
			static_cast<std::int8_t>(results[38]),
			static_cast<std::int8_t>(results[37]),
			static_cast<std::int8_t>(results[36]),
			static_cast<std::int8_t>(results[35]),
			static_cast<std::int8_t>(results[34]),
			static_cast<std::int8_t>(results[33]),
			static_cast<std::int8_t>(results[32]),
			static_cast<std::int8_t>(results[31]),
			static_cast<std::int8_t>(results[30]),
			static_cast<std::int8_t>(results[29]),
			static_cast<std::int8_t>(results[28]),
			static_cast<std::int8_t>(results[27]),
			static_cast<std::int8_t>(results[26]),
			static_cast<std::int8_t>(results[25]),
			static_cast<std::int8_t>(results[24]),
			static_cast<std::int8_t>(results[23]),
			static_cast<std::int8_t>(results[22]),
			static_cast<std::int8_t>(results[21]),
			static_cast<std::int8_t>(results[20]),
			static_cast<std::int8_t>(results[19]),
			static_cast<std::int8_t>(results[18]),
			static_cast<std::int8_t>(results[17]),
			static_cast<std::int8_t>(results[16]),
			static_cast<std::int8_t>(results[15]),
			static_cast<std::int8_t>(results[14]),
			static_cast<std::int8_t>(results[13]),
			static_cast<std::int8_t>(results[12]),
			static_cast<std::int8_t>(results[11]),
			static_cast<std::int8_t>(results[10]),
			static_cast<std::int8_t>(results[9]),
			static_cast<std::int8_t>(results[8]),
			static_cast<std::int8_t>(results[7]),
			static_cast<std::int8_t>(results[6]),
			static_cast<std::int8_t>(results[5]),
			static_cast<std::int8_t>(results[4]),
			static_cast<std::int8_t>(results[3]),
			static_cast<std::int8_t>(results[2]),
			static_cast<std::int8_t>(results[1]),
			static_cast<std::int8_t>(results[0])
		);
	}
#pragma endregion

#pragma region EXTRACTION_TEMPLATES
	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x64 extract_f32x16_lane_i8x64(f32x16_arg a_)
	{
		static_assert(Index_ == 0, "Invalid SIMD lane extraction index: Extracting i8x64 lane from a f32x16 instance; the maximum index is 0 but this index has been exceeded.");
		return cast_f32x16_i8x64(a_);
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x64 extract_f64x8_lane_i8x64(f64x8_arg a_)
	{
		static_assert(Index_ == 0, "Invalid SIMD lane extraction index: Extracting i8x64 lane from a f64x8 instance; the maximum index is 0 but this index has been exceeded.");
		return cast_f64x8_i8x64(a_);
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x64 extract_i8x64_lane_i8x64(i8x64_arg a_)
	{
		static_assert(Index_ == 0, "Invalid SIMD lane extraction index: Extracting i8x64 lane from a i8x64 instance; the maximum index is 0 but this index has been exceeded.");
		return a_;
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x64 extract_i16x32_lane_i8x64(i16x32_arg a_)
	{
		static_assert(Index_ == 0, "Invalid SIMD lane extraction index: Extracting i8x64 lane from a i16x32 instance; the maximum index is 0 but this index has been exceeded.");
		return cast_i16x32_i8x64(a_);
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x64 extract_i32x16_lane_i8x64(i32x16_arg a_)
	{
		static_assert(Index_ == 0, "Invalid SIMD lane extraction index: Extracting i8x64 lane from a i32x16 instance; the maximum index is 0 but this index has been exceeded.");
		return cast_i32x16_i8x64(a_);
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x64 extract_i64x8_lane_i8x64(i64x8_arg a_)
	{
		static_assert(Index_ == 0, "Invalid SIMD lane extraction index: Extracting i8x64 lane from a i64x8 instance; the maximum index is 0 but this index has been exceeded.");
		return cast_i64x8_i8x64(a_);
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x64 extract_u8x64_lane_i8x64(u8x64_arg a_)
	{
		static_assert(Index_ == 0, "Invalid SIMD lane extraction index: Extracting i8x64 lane from a u8x64 instance; the maximum index is 0 but this index has been exceeded.");
		return cast_u8x64_i8x64(a_);
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x64 extract_u16x32_lane_i8x64(u16x32_arg a_)
	{
		static_assert(Index_ == 0, "Invalid SIMD lane extraction index: Extracting i8x64 lane from a u16x32 instance; the maximum index is 0 but this index has been exceeded.");
		return cast_u16x32_i8x64(a_);
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x64 extract_u32x16_lane_i8x64(u32x16_arg a_)
	{
		static_assert(Index_ == 0, "Invalid SIMD lane extraction index: Extracting i8x64 lane from a u32x16 instance; the maximum index is 0 but this index has been exceeded.");
		return cast_u32x16_i8x64(a_);
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x64 extract_u64x8_lane_i8x64(u64x8_arg a_)
	{
		static_assert(Index_ == 0, "Invalid SIMD lane extraction index: Extracting i8x64 lane from a u64x8 instance; the maximum index is 0 but this index has been exceeded.");
		return cast_u64x8_i8x64(a_);
	}
#pragma endregion

#pragma region GET_TEMPLATES
	template<std::size_t Index_, typename OutT_ = std::int8_t>
	EMU_SIMD_COMMON_FUNC_SPEC auto extract_element_i8x64(i8x64_arg in_)
		-> typename std::remove_cvref<OutT_>::type
	{
		if constexpr (Index_ == 0)
		{
			return static_cast<typename std::remove_cvref<OutT_>::type>(EmuSIMD::Funcs::get_first_i8x64(in_));
		}
		else
		{
			if constexpr (Index_ <= 63)
			{
#if EMU_SIMD_USE_512_REGISTERS
				constexpr std::size_t elements_per_chunk = 16;
				constexpr std::size_t chunk_index = static_cast<std::size_t>(Index_ / elements_per_chunk);
				constexpr std::size_t index_in_chunk = Index_ - (chunk_index * elements_per_chunk);
				return EmuSIMD::Funcs::extract_element_i8x16<index_in_chunk, OutT_>(EmuSIMD::Funcs::extract_i8x64_lane_i8x16<chunk_index>(in_));
#else
				return EmuSIMD::_underlying_impl::retrieve_emulated_dual_lane_simd_element<OutT_, Index_, false, 32>(in_);
#endif
			}
			else
			{
				static_assert
				(
					EmuCore::TMP::get_false<std::size_t, Index_>(),
					"Invalid index provided when extracting an element from a i8x64 instance. Valid indices are 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63."
				);
			}
		}
	}
#pragma endregion
}

#endif
