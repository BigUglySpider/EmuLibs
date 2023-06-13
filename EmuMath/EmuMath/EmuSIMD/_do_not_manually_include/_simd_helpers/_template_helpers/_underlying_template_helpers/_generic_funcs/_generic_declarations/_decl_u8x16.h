#ifndef EMU_SIMD_GENERIC_FUNCS_U8X16_DECL_H_INC_
#define EMU_SIMD_GENERIC_FUNCS_U8X16_DECL_H_INC_ 1

#include "../_common_generic_func_helpers.h"
#include "_decl_f32x4.h"

namespace EmuSIMD::Funcs
{
#pragma region SETTERS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 set_u8x16
	(
		std::uint8_t e0, std::uint8_t e1, std::uint8_t e2, std::uint8_t e3, std::uint8_t e4, std::uint8_t e5, std::uint8_t e6, std::uint8_t e7,
		std::uint8_t e8, std::uint8_t e9, std::uint8_t e10, std::uint8_t e11, std::uint8_t e12, std::uint8_t e13, std::uint8_t e14, std::uint8_t e15
	);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 setr_u8x16
	(
		std::uint8_t e0, std::uint8_t e1, std::uint8_t e2, std::uint8_t e3, std::uint8_t e4, std::uint8_t e5, std::uint8_t e6, std::uint8_t e7,
		std::uint8_t e8, std::uint8_t e9, std::uint8_t e10, std::uint8_t e11, std::uint8_t e12, std::uint8_t e13, std::uint8_t e14, std::uint8_t e15
	);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 set1_u8x16(std::uint8_t all_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 load_u8x16(const std::uint8_t* p_to_load_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 aligned_load_u8x16(const std::uint8_t* p_to_load_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 setzero_u8x16();
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 setmasked_u8x16(std::uint16_t bit_mask_);
#pragma endregion

#pragma region STORES
	EMU_SIMD_COMMON_FUNC_SPEC void store_u8x16(std::uint8_t* p_out_, u8x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC void aligned_store_u8x16(std::uint8_t* p_out_, u8x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC std::uint8_t get_first_u8x16(u8x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC std::uint16_t movemask_u8x16(u8x16_arg a_);
#pragma endregion

#pragma region CASTS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cast_f32x4_u8x16(f32x4_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cast_f32x8_u8x16(f32x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cast_f32x16_u8x16(f32x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cast_f64x2_u8x16(f64x2_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cast_f64x4_u8x16(f64x4_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cast_f64x8_u8x16(f64x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cast_i8x16_u8x16(i8x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cast_i16x8_u8x16(i16x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cast_i32x4_u8x16(i32x4_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cast_i64x2_u8x16(i64x2_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cast_i8x32_u8x16(i8x32_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cast_i16x16_u8x16(i16x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cast_i32x8_u8x16(i32x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cast_i64x4_u8x16(i64x4_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cast_i8x64_u8x16(i8x64_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cast_i16x32_u8x16(i16x32_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cast_i32x16_u8x16(i32x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cast_i64x8_u8x16(i64x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cast_u8x16_u8x16(u8x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cast_u16x8_u8x16(u16x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cast_u32x4_u8x16(u32x4_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cast_u64x2_u8x16(u64x2_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cast_u8x32_u8x16(u8x32_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cast_u16x16_u8x16(u16x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cast_u32x8_u8x16(u32x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cast_u64x4_u8x16(u64x4_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cast_u8x64_u8x16(u8x64_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cast_u16x32_u8x16(u16x32_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cast_u32x16_u8x16(u32x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cast_u64x8_u8x16(u64x8_arg a_);
#pragma endregion

#pragma region CONVERSIONS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cvt_f32x4_u8x16(f32x4_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cvt_f32x8_u8x16(f32x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cvt_f32x16_u8x16(f32x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cvt_f64x2_u8x16(f64x2_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cvt_f64x4_u8x16(f64x4_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cvt_f64x8_u8x16(f64x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cvt_i8x16_u8x16(i8x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cvt_i16x8_u8x16(i16x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cvt_i32x4_u8x16(i32x4_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cvt_i64x2_u8x16(i64x2_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cvt_i8x32_u8x16(i8x32_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cvt_i16x16_u8x16(i16x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cvt_i32x8_u8x16(i32x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cvt_i64x4_u8x16(i64x4_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cvt_i8x64_u8x16(i8x64_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cvt_i16x32_u8x16(i16x32_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cvt_i32x16_u8x16(i32x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cvt_i64x8_u8x16(i64x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cvt_u8x16_u8x16(u8x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cvt_u16x8_u8x16(u16x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cvt_u32x4_u8x16(u32x4_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cvt_u64x2_u8x16(u64x2_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cvt_u8x32_u8x16(u8x32_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x16 cvt_u16x16_u8x16(u16x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x16 cvt_u32x8_u8x16(u32x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x16 cvt_u64x4_u8x16(u64x4_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cvt_u8x64_u8x16(u8x64_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cvt_u16x32_u8x16(u16x32_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cvt_u32x16_u8x16(u32x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cvt_u64x8_u8x16(u64x8_arg a_);
#pragma endregion

#pragma region COMPARISONS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cmpeq_u8x16(EmuSIMD::u8x16_arg lhs_, EmuSIMD::u8x16_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cmpneq_u8x16(EmuSIMD::u8x16_arg lhs_, EmuSIMD::u8x16_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cmpgt_u8x16(EmuSIMD::u8x16_arg lhs_, EmuSIMD::u8x16_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cmplt_u8x16(EmuSIMD::u8x16_arg lhs_, EmuSIMD::u8x16_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cmpge_u8x16(EmuSIMD::u8x16_arg lhs_, EmuSIMD::u8x16_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cmple_u8x16(EmuSIMD::u8x16_arg lhs_, EmuSIMD::u8x16_arg rhs_);
#pragma endregion

#pragma region MOVES
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 movehl_u8x16(EmuSIMD::u8x16_arg lhs_, EmuSIMD::u8x16_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 movelh_u8x16(EmuSIMD::u8x16_arg lhs_, EmuSIMD::u8x16_arg rhs_);
#pragma endregion

#pragma region BITWISE_ARITHMETIC
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 and_u8x16(EmuSIMD::u8x16_arg lhs_, EmuSIMD::u8x16_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 or_u8x16(EmuSIMD::u8x16_arg lhs_, EmuSIMD::u8x16_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 xor_u8x16(EmuSIMD::u8x16_arg lhs_, EmuSIMD::u8x16_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 andnot_u8x16(EmuSIMD::u8x16_arg not_lhs_, EmuSIMD::u8x16_arg rhs_);
	template<std::int32_t NumShifts_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 shift_left_u8x16(EmuSIMD::u8x16_arg lhs_);
	template<std::int32_t NumShifts_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 shift_right_arithmetic_u8x16(EmuSIMD::u8x16_arg lhs_);
	template<std::int32_t NumShifts_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 shift_right_logical_u8x16(EmuSIMD::u8x16_arg lhs_);
#pragma endregion

#pragma region BLENDS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 blendv_u8x16(EmuSIMD::u8x16_arg a_, EmuSIMD::u8x16_arg b_, EmuSIMD::u8x16_arg shuffle_mask_vec_);
#pragma endregion

#pragma region MINMAX_FUNCS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 min_u8x16(EmuSIMD::u8x16_arg a_, EmuSIMD::u8x16_arg b_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 horizontal_min_u8x16(EmuSIMD::u8x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 horizontal_min_fill_u8x16(EmuSIMD::u8x16_arg a_);
	template<typename Out_ = std::uint8_t>
	EMU_SIMD_COMMON_FUNC_SPEC auto horizontal_min_scalar_u8x16(EmuSIMD::u8x16_arg a_)
		-> typename std::remove_cvref<Out_>::type;
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 max_u8x16(EmuSIMD::u8x16_arg a_, EmuSIMD::u8x16_arg b_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 horizontal_max_u8x16(EmuSIMD::u8x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 horizontal_max_fill_u8x16(EmuSIMD::u8x16_arg a_);
	template<typename Out_ = std::uint8_t>
	EMU_SIMD_COMMON_FUNC_SPEC auto horizontal_max_scalar_u8x16(EmuSIMD::u8x16_arg a_)
		-> typename std::remove_cvref<Out_>::type;
#pragma endregion

#pragma region BASIC_ARITHMETIC
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 mul_all_u8x16(EmuSIMD::u8x16_arg lhs_, EmuSIMD::u8x16_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 negate_u8x16(EmuSIMD::u8x16_arg to_negate_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 add_u8x16(EmuSIMD::u8x16_arg lhs_, EmuSIMD::u8x16_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 sub_u8x16(EmuSIMD::u8x16_arg lhs_, EmuSIMD::u8x16_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 div_u8x16(EmuSIMD::u8x16_arg lhs_, EmuSIMD::u8x16_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 addsub_u8x16(EmuSIMD::u8x16_arg lhs_, EmuSIMD::u8x16_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 subadd_u8x16(EmuSIMD::u8x16_arg lhs_, EmuSIMD::u8x16_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 fmadd_u8x16(EmuSIMD::u8x16_arg a_, EmuSIMD::u8x16_arg b_, EmuSIMD::u8x16_arg c_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 fmsub_u8x16(EmuSIMD::u8x16_arg a_, EmuSIMD::u8x16_arg b_, EmuSIMD::u8x16_arg c_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 fnmadd_u8x16(EmuSIMD::u8x16_arg a_, EmuSIMD::u8x16_arg b_, EmuSIMD::u8x16_arg c_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 fnmsub_u8x16(EmuSIMD::u8x16_arg a_, EmuSIMD::u8x16_arg b_, EmuSIMD::u8x16_arg c_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 fmaddsub_u8x16(EmuSIMD::u8x16_arg a_, EmuSIMD::u8x16_arg b_, EmuSIMD::u8x16_arg c_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 fmsubadd_u8x16(EmuSIMD::u8x16_arg a_, EmuSIMD::u8x16_arg b_, EmuSIMD::u8x16_arg c_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 floor_u8x16(EmuSIMD::u8x16_arg to_floor_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 ceil_u8x16(EmuSIMD::u8x16_arg to_ceil_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 trunc_u8x16(EmuSIMD::u8x16_arg to_trunc_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 mod_u8x16(EmuSIMD::u8x16_arg lhs_, EmuSIMD::u8x16_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 abs_u8x16(EmuSIMD::u8x16_arg in_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 sqrt_u8x16(EmuSIMD::u8x16_arg in_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 rsqrt_u8x16(EmuSIMD::u8x16_arg in_);
#pragma endregion

#pragma region NEAR_COMPARISONS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cmpnear_u8x16(EmuSIMD::u8x16_arg lhs_, EmuSIMD::u8x16_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cmpnear_u8x16(EmuSIMD::u8x16_arg lhs_, EmuSIMD::u8x16_arg rhs_, EmuSIMD::u8x16_arg epsilon);
#pragma endregion

#pragma region TRIG
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cos_u8x16(EmuSIMD::u8x16_arg in_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 sin_u8x16(EmuSIMD::u8x16_arg in_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 tan_u8x16(EmuSIMD::u8x16_arg in_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 acos_u8x16(EmuSIMD::u8x16_arg in_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 asin_u8x16(EmuSIMD::u8x16_arg in_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 atan_u8x16(EmuSIMD::u8x16_arg in_);
#pragma endregion

#pragma region ROUNDING_TEMPLATES
	template<int RoundingFlag_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 round_u8x16(EmuSIMD::u8x16_arg to_round_)
	{
		return to_round_;
	}
#pragma endregion

#pragma region SHUFFLE_TEMPLATES
	template<EmuSIMD::Funcs::shuffle_mask_type ShuffleMask_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 permute_u8x16(EmuSIMD::u8x16_arg a_)
	{
		constexpr bool is_reverse_set = false;
		using target_element_type = unsigned char;
		constexpr std::size_t argument_width = 4; // Max value of 15 (0b1111), per index
		constexpr std::size_t num_128_lanes = 1;

		return _mm_shuffle_epi8
		(
			a_,
			EmuSIMD::Funcs::shuffle_mask_to_vector<ShuffleMask_, is_reverse_set, argument_width, num_128_lanes, target_element_type>
			(
				std::make_index_sequence<16>(),
				[](auto&&...args_) { return set_u8x16(std::forward<decltype(args_)>(args_)...); }
			)
		);
	}

	template<EmuSIMD::Funcs::shuffle_mask_type ShuffleMask_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 shuffle_u8x16(EmuSIMD::u8x16_arg a_, EmuSIMD::u8x16_arg b_)
	{
		constexpr std::size_t a_permute_mask = duplicate_shuffle_mask_32bit_lane<ShuffleMask_, true>();
		constexpr std::size_t b_permute_mask = duplicate_shuffle_mask_32bit_lane<ShuffleMask_, false>();

		EmuSIMD::u8x16 a_permuted = permute_u8x16<a_permute_mask>(a_);
		EmuSIMD::u8x16 b_permuted = permute_u8x16<b_permute_mask>(b_);

		// Use f32x4 reinterpretation to take the lo bits of permuted a and the lo bits of permuted b and combine them into one register, 
		// where lo(result) = lo(a), hi(result) = lo(b)
		// --- We take this approach as each permutation has been duplicated across 64-bit lanes within the respective permuted register
		EmuSIMD::f32x4 tmp_cast = cast_u8x16_f32x4(a_permuted);
		tmp_cast = movelh_f32x4(tmp_cast, cast_u8x16_f32x4(b_permuted));

		return cast_f32x4_u8x16(tmp_cast);
	}
#pragma endregion

#pragma region BLEND_TEMPLATES
	template<EmuSIMD::Funcs::blend_mask_type BlendMask_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 blend_u8x16(EmuSIMD::u8x16_arg a_, EmuSIMD::u8x16_arg b_)
	{
		constexpr bool is_reverse_set = false;
		using target_element_type = std::uint8_t;
		constexpr std::size_t num_elements = 16;

		return _mm_blendv_epi8
		(
			a_,
			b_,
			EmuSIMD::Funcs::blend_mask_to_vector<BlendMask_, is_reverse_set, target_element_type>
			(
				std::make_index_sequence<num_elements>(),
				[](auto&&...args_) { return set_u8x16(std::forward<decltype(args_)>(args_)...); }
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
	EMU_SIMD_COMMON_FUNC_SPEC auto emulate_fp_u8x16(Func_ func_, EmuSIMD::u8x16_arg in_)
		-> std::enable_if_t<std::is_invocable_r_v<EmuSIMD::f32x4, decltype(func_), EmuSIMD::f32x4>, EmuSIMD::u8x16>
	{
		constexpr std::size_t num_elements = 16;
		constexpr std::size_t elements_per_register = 4;
		std::uint8_t data[num_elements];
		float results[num_elements];

		store_u8x16(data, in_);
		for (std::size_t i = 0; i < num_elements; i += elements_per_register)
		{
			store_f32x4(results + i, func_(set_f32x4(static_cast<float>(data[i + 3]), static_cast<float>(data[i + 2]), static_cast<float>(data[i + 1]), static_cast<float>(data[i]))));
		}

		return set_u8x16
		(
			static_cast<std::uint8_t>(results[15]),
			static_cast<std::uint8_t>(results[14]),
			static_cast<std::uint8_t>(results[13]),
			static_cast<std::uint8_t>(results[12]),
			static_cast<std::uint8_t>(results[11]),
			static_cast<std::uint8_t>(results[10]),
			static_cast<std::uint8_t>(results[9]),
			static_cast<std::uint8_t>(results[8]),
			static_cast<std::uint8_t>(results[7]),
			static_cast<std::uint8_t>(results[6]),
			static_cast<std::uint8_t>(results[5]),
			static_cast<std::uint8_t>(results[4]),
			static_cast<std::uint8_t>(results[3]),
			static_cast<std::uint8_t>(results[2]),
			static_cast<std::uint8_t>(results[1]),
			static_cast<std::uint8_t>(results[0])
		);
	}
#pragma endregion

#pragma region EXTRACTION_TEMPLATES
	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 extract_f32x4_lane_u8x16(f32x4_arg a_)
	{
		static_assert(Index_ == 0, "Invalid SIMD lane extraction index: Extracting u8x16 lane from a f32x4 instance; the maximum index is 0 but this index has been exceeded");
		return cast_f32x4_u8x16(a_);
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 extract_f32x8_lane_u8x16(f32x8_arg a_)
	{
		static_assert(Index_ <= 1, "Invalid SIMD lane extraction index: Extracting u8x16 lane from a f32x8 instance; the maximum index is 1 but this index has been exceeded.");
		if constexpr (Index_ == 0)
		{
			return cast_f32x8_u8x16(a_);
		}
		else
		{
			return cast_f32x4_u8x16(_mm256_extractf128_ps(a_, Index_));
		}
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 extract_f32x16_lane_u8x16(f32x16_arg a_)
	{
		static_assert(Index_ <= 3, "Invalid SIMD lane extraction index: Extracting u8x16 lane from a f32x16 instance; the maximum index is 3 but this index has been exceeded.");
		if constexpr (Index_ == 0)
		{
			return cast_f32x16_u8x16(a_);
		}
		else
		{
#if EMU_SIMD_USE_512_REGISTERS
			return cast_f32x4_u8x16(_mm512_extractf32x4_ps(a_, Index_));
#else
			return EmuSIMD::_underlying_impl::emulate_extraction<u8x16, 128, Index_>(a_);
#endif
		}
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 extract_f64x2_lane_u8x16(f64x2_arg a_)
	{
		static_assert(Index_ == 0, "Invalid SIMD lane extraction index: Extracting u8x16 lane from a f64x2 instance; the maximum index is 0 but this index has been exceeded.");
		return cast_f64x2_u8x16(a_);
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 extract_f64x4_lane_u8x16(f64x4_arg a_)
	{
		static_assert(Index_ <= 1, "Invalid SIMD lane extraction index: Extracting u8x16 lane from a f64x4 instance; the maximum index is 1 but this index has been exceeded.");
		if constexpr (Index_ == 0)
		{
			return cast_f64x4_u8x16(a_);
		}
		else
		{
			return cast_f64x2_u8x16(_mm256_extractf128_pd(a_, Index_));
		}
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 extract_f64x8_lane_u8x16(f64x8_arg a_)
	{
		static_assert(Index_ <= 3, "Invalid SIMD lane extraction index: Extracting u8x16 lane from a f64x8 instance; the maximum index is 3 but this index has been exceeded.");
		if constexpr (Index_ == 0)
		{
			return cast_f64x8_u8x16(a_);
		}
		else
		{
#if EMU_SIMD_USE_512_REGISTERS
			return cast_f64x2_u8x16(_mm512_extractf64x2_pd(a_, Index_));
#else
			return EmuSIMD::_underlying_impl::emulate_extraction<u8x16, 128, Index_>(a_);
#endif
		}
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 extract_i8x16_lane_u8x16(i8x16_arg a_)
	{
		static_assert(Index_ == 0, "Invalid SIMD lane extraction index: Extracting u8x16 lane from a i8x16 instance; the maximum index is 0 but this index has been exceeded.");
		return cast_i8x16_u8x16(a_);
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 extract_i8x32_lane_u8x16(i8x32_arg a_)
	{
		static_assert(Index_ <= 1, "Invalid SIMD lane extraction index: Extracting u8x16 lane from a i8x32 instance; the maximum index is 1 but this index has been exceeded.");
		if constexpr (Index_ == 0)
		{
			return cast_i8x32_u8x16(a_);
		}
		else
		{
			return _mm256_extracti128_si256(a_, Index_);
		}
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 extract_i8x64_lane_u8x16(i8x64_arg a_)
	{
		static_assert(Index_ <= 3, "Invalid SIMD lane extraction index: Extracting u8x16 lane from a i8x64 instance; the maximum index is 3 but this index has been exceeded.");
		if constexpr (Index_ == 0)
		{
			return cast_i8x64_u8x16(a_);
		}
		else
		{
#if EMU_SIMD_USE_512_REGISTERS
			return _mm512_extracti32x4_epi32(a_, Index_);
#else
			return EmuSIMD::_underlying_impl::emulate_extraction<u8x16, 128, Index_>(a_);
#endif
		}
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 extract_i16x8_lane_u8x16(i16x8_arg a_)
	{
		static_assert(Index_ == 0, "Invalid SIMD lane extraction index: Extracting u8x16 lane from a i16x8 instance; the maximum index is 0 but this index has been exceeded.");
		return cast_i16x8_u8x16(a_);
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 extract_i16x16_lane_u8x16(i16x16_arg a_)
	{
		static_assert(Index_ <= 1, "Invalid SIMD lane extraction index: Extracting u8x16 lane from a i16x16 instance; the maximum index is 1 but this index has been exceeded.");
		if constexpr (Index_ == 0)
		{
			return cast_i16x16_u8x16(a_);
		}
		else
		{
			return _mm256_extracti128_si256(a_, Index_);
		}
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 extract_i16x32_lane_u8x16(i16x32_arg a_)
	{
		static_assert(Index_ <= 3, "Invalid SIMD lane extraction index: Extracting u8x16 lane from a i16x32 instance; the maximum index is 3 but this index has been exceeded.");
		if constexpr (Index_ == 0)
		{
			return cast_i16x32_u8x16(a_);
		}
		else
		{
#if EMU_SIMD_USE_512_REGISTERS
			return _mm512_extracti32x4_epi32(a_, Index_);
#else
			return EmuSIMD::_underlying_impl::emulate_extraction<u8x16, 128, Index_>(a_);
#endif
		}
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 extract_i32x4_lane_u8x16(i32x4_arg a_)
	{
		static_assert(Index_ == 0, "Invalid SIMD lane extraction index: Extracting u8x16 lane from a i32x4 instance; the maximum index is 0 but this index has been exceeded.");
		return cast_i32x4_u8x16(a_);
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 extract_i32x8_lane_u8x16(i32x8_arg a_)
	{
		static_assert(Index_ <= 1, "Invalid SIMD lane extraction index: Extracting u8x16 lane from a i32x8 instance; the maximum index is 1 but this index has been exceeded.");
		if constexpr (Index_ == 0)
		{
			return cast_i32x8_u8x16(a_);
		}
		else
		{
			return _mm256_extracti128_si256(a_, Index_);
		}
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 extract_i32x16_lane_u8x16(i32x16_arg a_)
	{
		static_assert(Index_ <= 3, "Invalid SIMD lane extraction index: Extracting u8x16 lane from a i32x16 instance; the maximum index is 3 but this index has been exceeded.");
		if constexpr (Index_ == 0)
		{
			return cast_i32x16_u8x16(a_);
		}
		else
		{
#if EMU_SIMD_USE_512_REGISTERS
			return _mm512_extracti32x4_epi32(a_, Index_);
#else
			return EmuSIMD::_underlying_impl::emulate_extraction<u8x16, 128, Index_>(a_);
#endif
		}
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 extract_i64x2_lane_u8x16(i64x2_arg a_)
	{
		static_assert(Index_ == 0, "Invalid SIMD lane extraction index: Extracting u8x16 lane from a i64x2 instance; the maximum index is 0 but this index has been exceeded.");
		return cast_i64x2_u8x16(a_);
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 extract_i64x4_lane_u8x16(i64x4_arg a_)
	{
		static_assert(Index_ <= 1, "Invalid SIMD lane extraction index: Extracting u8x16 lane from a i64x4 instance; the maximum index is 1 but this index has been exceeded.");
		if constexpr (Index_ == 0)
		{
			return cast_i64x4_u8x16(a_);
		}
		else
		{
			return _mm256_extracti128_si256(a_, Index_);
		}
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 extract_i64x8_lane_u8x16(i64x8_arg a_)
	{
		static_assert(Index_ <= 3, "Invalid SIMD lane extraction index: Extracting u8x16 lane from a i64x8 instance; the maximum index is 3 but this index has been exceeded.");
		if constexpr (Index_ == 0)
		{
			return cast_i64x8_u8x16(a_);
		}
		else
		{
#if EMU_SIMD_USE_512_REGISTERS
			return _mm512_extracti32x4_epi32(a_, Index_);
#else
			return EmuSIMD::_underlying_impl::emulate_extraction<u8x16, 128, Index_>(a_);
#endif
		}
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 extract_u8x16_lane_u8x16(u8x16_arg a_)
	{
		static_assert(Index_ == 0, "Invalid SIMD lane extraction index: Extracting u8x16 lane from a u8x16 instance; the maximum index is 0 but this index has been exceeded.");
		return a_;
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 extract_u8x32_lane_u8x16(u8x32_arg a_)
	{
		static_assert(Index_ <= 1, "Invalid SIMD lane extraction index: Extracting u8x16 lane from a u8x32 instance; the maximum index is 1 but this index has been exceeded.");
		if constexpr (Index_ == 0)
		{
			return cast_u8x32_u8x16(a_);
		}
		else
		{
			return _mm256_extracti128_si256(a_, Index_);
		}
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 extract_u8x64_lane_u8x16(u8x64_arg a_)
	{
		static_assert(Index_ <= 3, "Invalid SIMD lane extraction index: Extracting u8x16 lane from a u8x64 instance; the maximum index is 3 but this index has been exceeded.");
		if constexpr (Index_ == 0)
		{
			return cast_u8x64_u8x16(a_);
		}
		else
		{
#if EMU_SIMD_USE_512_REGISTERS
			return _mm512_extracti32x4_epi32(a_, Index_);
#else
			return EmuSIMD::_underlying_impl::emulate_extraction<u8x16, 128, Index_>(a_);
#endif
		}
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 extract_u16x8_lane_u8x16(u16x8_arg a_)
	{
		static_assert(Index_ == 0, "Invalid SIMD lane extraction index: Extracting u8x16 lane from a u16x8 instance; the maximum index is 0 but this index has been exceeded.");
		return cast_u16x8_u8x16(a_);
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 extract_u16x16_lane_u8x16(u16x16_arg a_)
	{
		static_assert(Index_ <= 1, "Invalid SIMD lane extraction index: Extracting u8x16 lane from a u16x16 instance; the maximum index is 1 but this index has been exceeded.");
		if constexpr (Index_ == 0)
		{
			return cast_u16x16_u8x16(a_);
		}
		else
		{
			return _mm256_extracti128_si256(a_, Index_);
		}
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 extract_u16x32_lane_u8x16(u16x32_arg a_)
	{
		static_assert(Index_ <= 3, "Invalid SIMD lane extraction index: Extracting u8x16 lane from a u16x32 instance; the maximum index is 3 but this index has been exceeded.");
		if constexpr (Index_ == 0)
		{
			return cast_u16x32_u8x16(a_);
		}
		else
		{
#if EMU_SIMD_USE_512_REGISTERS
			return _mm512_extracti32x4_epi32(a_, Index_);
#else
			return EmuSIMD::_underlying_impl::emulate_extraction<u8x16, 128, Index_>(a_);
#endif
		}
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 extract_u32x4_lane_u8x16(u32x4_arg a_)
	{
		static_assert(Index_ == 0, "Invalid SIMD lane extraction index: Extracting u8x16 lane from a u32x4 instance; the maximum index is 0 but this index has been exceeded.");
		return cast_u32x4_u8x16(a_);
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 extract_u32x8_lane_u8x16(u32x8_arg a_)
	{
		static_assert(Index_ <= 1, "Invalid SIMD lane extraction index: Extracting u8x16 lane from a u32x8 instance; the maximum index is 1 but this index has been exceeded.");
		if constexpr (Index_ == 0)
		{
			return cast_u32x8_u8x16(a_);
		}
		else
		{
			return _mm256_extracti128_si256(a_, Index_);
		}
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 extract_u32x16_lane_u8x16(u32x16_arg a_)
	{
		static_assert(Index_ <= 3, "Invalid SIMD lane extraction index: Extracting u8x16 lane from a ui8x16 instance; the maximum index is 3 but this index has been exceeded.");
		if constexpr (Index_ == 0)
		{
			return cast_u32x16_u8x16(a_);
		}
		else
		{
#if EMU_SIMD_USE_512_REGISTERS
			return _mm512_extracti32x4_epi32(a_, Index_);
#else
			return EmuSIMD::_underlying_impl::emulate_extraction<u8x16, 128, Index_>(a_);
#endif
		}
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 extract_u64x2_lane_u8x16(u64x2_arg a_)
	{
		static_assert(Index_ == 0, "Invalid SIMD lane extraction index: Extracting u8x16 lane from a u64x2 instance; the maximum index is 0 but this index has been exceeded.");
		return cast_u64x2_u8x16(a_);
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 extract_u64x4_lane_u8x16(u64x4_arg a_)
	{
		static_assert(Index_ <= 1, "Invalid SIMD lane extraction index: Extracting u8x16 lane from a u64x4 instance; the maximum index is 1 but this index has been exceeded.");
		if constexpr (Index_ == 0)
		{
			return cast_u64x4_u8x16(a_);
		}
		else
		{
			return _mm256_extracti128_si256(a_, Index_);
		}
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 extract_u64x8_lane_u8x16(u64x8_arg a_)
	{
		static_assert(Index_ <= 3, "Invalid SIMD lane extraction index: Extracting u8x16 lane from a u64x8 instance; the maximum index is 3 but this index has been exceeded.");
		if constexpr (Index_ == 0)
		{
			return cast_u64x8_u8x16(a_);
		}
		else
		{
#if EMU_SIMD_USE_512_REGISTERS
			return _mm512_extracti32x4_epi32(a_, Index_);
#else
			return EmuSIMD::_underlying_impl::emulate_extraction<u8x16, 128, Index_>(a_);
#endif
		}
	}
#pragma endregion

#pragma region GET_TEMPLATES
	template<std::size_t Index_, typename OutT_ = std::uint8_t>
	EMU_SIMD_COMMON_FUNC_SPEC auto extract_element_u8x16(u8x16_arg in_)
		-> typename std::remove_cvref<OutT_>::type
	{
		if constexpr (Index_ == 0)
		{
			return static_cast<typename std::remove_cvref<OutT_>::type>(EmuSIMD::Funcs::get_first_u8x16(in_));
		}
		else
		{
			if constexpr (Index_ <= 15)
			{
#if EMU_SIMD_USE_128_REGISTERS
				return static_cast<typename std::remove_cvref<OutT_>::type>(_mm_extract_epi8(in_, Index_));
#else
				return EmuSIMD::_underlying_impl::retrieve_emulated_single_lane_simd_element<OutT_, Index_, false>(in_);
#endif
			}
			else
			{
				static_assert
				(
					EmuCore::TMP::get_false<std::size_t, Index_>(),
					"Invalid index provided when extracting an element from a u8x16 instance. Valid indices are 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15."
				);
			}
		}
	}
#pragma endregion
}

#endif
