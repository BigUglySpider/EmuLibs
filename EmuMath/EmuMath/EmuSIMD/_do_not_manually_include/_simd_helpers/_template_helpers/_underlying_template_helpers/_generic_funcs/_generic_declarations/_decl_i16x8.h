#ifndef EMU_SIMD_GENERIC_FUNCS_I16X8_DECL_H_INC_
#define EMU_SIMD_GENERIC_FUNCS_I16X8_DECL_H_INC_ 1

#include "../_common_generic_func_helpers.h"
#include "_decl_f32x4.h"

namespace EmuSIMD::Funcs
{
#pragma region SETTERS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x8 set_i16x8(std::int16_t e0, std::int16_t e1, std::int16_t e2, std::int16_t e3, std::int16_t e4, std::int16_t e5, std::int16_t e6, std::int16_t e7);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x8 setr_i16x8(std::int16_t e0, std::int16_t e1, std::int16_t e2, std::int16_t e3, std::int16_t e4, std::int16_t e5, std::int16_t e6, std::int16_t e7);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x8 set1_i16x8(std::int16_t all_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x8 load_i16x8(const std::int16_t* p_to_load_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x8 setzero_i16x8();
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x8 setmasked_i16x8(std::uint8_t bit_mask_);
#pragma endregion

#pragma region STORES
	EMU_SIMD_COMMON_FUNC_SPEC void store_i16x8(std::int16_t* p_out_, i16x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC std::int16_t get_first_i16x8(i16x8_arg a_);
#pragma endregion

#pragma region CASTS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x8 cast_f32x4_i16x8(f32x4_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x8 cast_f32x8_i16x8(f32x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x8 cast_f32x16_i16x8(f32x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x8 cast_f64x2_i16x8(f64x2_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x8 cast_f64x4_i16x8(f64x4_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x8 cast_f64x8_i16x8(f64x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x8 cast_i8x16_i16x8(i8x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x8 cast_i16x8_i16x8(i16x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x8 cast_i32x4_i16x8(i32x4_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x8 cast_i64x2_i16x8(i64x2_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x8 cast_i8x32_i16x8(i8x32_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x8 cast_i16x16_i16x8(i16x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x8 cast_i32x8_i16x8(i32x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x8 cast_i64x4_i16x8(i64x4_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x8 cast_i8x64_i16x8(i8x64_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x8 cast_i16x32_i16x8(i16x32_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x8 cast_i32x16_i16x8(i32x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x8 cast_i64x8_i16x8(i64x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x8 cast_u8x16_i16x8(u8x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x8 cast_u16x8_i16x8(u16x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x8 cast_u32x4_i16x8(u32x4_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x8 cast_u64x2_i16x8(u64x2_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x8 cast_u8x32_i16x8(u8x32_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x8 cast_u16x16_i16x8(u16x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x8 cast_u32x8_i16x8(u32x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x8 cast_u64x4_i16x8(u64x4_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x8 cast_u8x64_i16x8(u8x64_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x8 cast_u16x32_i16x8(u16x32_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x8 cast_u32x16_i16x8(u32x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x8 cast_u64x8_i16x8(u64x8_arg a_);
#pragma endregion

#pragma region CONVERSIONS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x8 cvt_f32x4_i16x8(f32x4_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x8 cvt_f32x8_i16x8(f32x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x8 cvt_f32x16_i16x8(f32x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x8 cvt_f64x2_i16x8(f64x2_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x8 cvt_f64x4_i16x8(f64x4_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x8 cvt_f64x8_i16x8(f64x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x8 cvt_i8x16_i16x8(i8x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x8 cvt_i16x8_i16x8(i16x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x8 cvt_i32x4_i16x8(i32x4_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x8 cvt_i64x2_i16x8(i64x2_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x8 cvt_i8x32_i16x8(i8x32_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x8 cvt_i16x16_i16x8(i16x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x8 cvt_i32x8_i16x8(i32x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x8 cvt_i64x4_i16x8(i64x4_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x8 cvt_i8x64_i16x8(i8x64_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x8 cvt_i16x32_i16x8(i16x32_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x8 cvt_i32x16_i16x8(i32x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x8 cvt_i64x8_i16x8(i64x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x8 cvt_u8x16_i16x8(u8x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x8 cvt_u16x8_i16x8(u16x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x8 cvt_u32x4_i16x8(u32x4_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x8 cvt_u64x2_i16x8(u64x2_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x8 cvt_u8x32_i16x8(u8x32_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x8 cvt_u16x16_i16x8(u16x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x8 cvt_u32x8_i16x8(u32x8_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x8 cvt_u64x4_i16x8(u64x4_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x8 cvt_u8x64_i16x8(u8x64_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x8 cvt_u16x32_i16x8(u16x32_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x8 cvt_u32x16_i16x8(u32x16_arg a_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x8 cvt_u64x8_i16x8(u64x8_arg a_);
#pragma endregion

#pragma region COMPARISONS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x8 cmpeq_i16x8(EmuSIMD::i16x8_arg lhs_, EmuSIMD::i16x8_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x8 cmpneq_i16x8(EmuSIMD::i16x8_arg lhs_, EmuSIMD::i16x8_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x8 cmpgt_i16x8(EmuSIMD::i16x8_arg lhs_, EmuSIMD::i16x8_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x8 cmplt_i16x8(EmuSIMD::i16x8_arg lhs_, EmuSIMD::i16x8_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x8 cmpge_i16x8(EmuSIMD::i16x8_arg lhs_, EmuSIMD::i16x8_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x8 cmple_i16x8(EmuSIMD::i16x8_arg lhs_, EmuSIMD::i16x8_arg rhs_);
#pragma endregion

#pragma region MOVES
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x8 movehl_i16x8(EmuSIMD::i16x8_arg lhs_, EmuSIMD::i16x8_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x8 movelh_i16x8(EmuSIMD::i16x8_arg lhs_, EmuSIMD::i16x8_arg rhs_);
#pragma endregion

#pragma region BLENDS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x8 blendv_i16x8(EmuSIMD::i16x8_arg a_, EmuSIMD::i16x8_arg b_, EmuSIMD::i16x8_arg shuffle_mask_vec_);
#pragma endregion

#pragma region MINMAX_FUNCS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x8 min_i16x8(EmuSIMD::i16x8_arg a_, EmuSIMD::i16x8_arg b_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x8 max_i16x8(EmuSIMD::i16x8_arg a_, EmuSIMD::i16x8_arg b_);
#pragma endregion

#pragma region BASIC_ARITHMETIC
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x8 mul_all_i16x8(EmuSIMD::i16x8_arg lhs_, EmuSIMD::i16x8_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x8 negate_i16x8(EmuSIMD::i16x8_arg to_negate_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x8 add_i16x8(EmuSIMD::i16x8_arg lhs_, EmuSIMD::i16x8_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x8 sub_i16x8(EmuSIMD::i16x8_arg lhs_, EmuSIMD::i16x8_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x8 mul_i16x8(EmuSIMD::i16x8_arg lhs_, EmuSIMD::i16x8_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x8 div_i16x8(EmuSIMD::i16x8_arg lhs_, EmuSIMD::i16x8_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x8 addsub_i16x8(EmuSIMD::i16x8_arg lhs_, EmuSIMD::i16x8_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x8 subadd_i16x8(EmuSIMD::i16x8_arg lhs_, EmuSIMD::i16x8_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x8 fmadd_i16x8(EmuSIMD::i16x8_arg a_, EmuSIMD::i16x8_arg b_, EmuSIMD::i16x8_arg c_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x8 fmsub_i16x8(EmuSIMD::i16x8_arg a_, EmuSIMD::i16x8_arg b_, EmuSIMD::i16x8_arg c_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x8 fnmadd_i16x8(EmuSIMD::i16x8_arg a_, EmuSIMD::i16x8_arg b_, EmuSIMD::i16x8_arg c_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x8 fnmsub_i16x8(EmuSIMD::i16x8_arg a_, EmuSIMD::i16x8_arg b_, EmuSIMD::i16x8_arg c_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x8 fmaddsub_i16x8(EmuSIMD::i16x8_arg a_, EmuSIMD::i16x8_arg b_, EmuSIMD::i16x8_arg c_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x8 fmsubadd_i16x8(EmuSIMD::i16x8_arg a_, EmuSIMD::i16x8_arg b_, EmuSIMD::i16x8_arg c_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x8 floor_i16x8(EmuSIMD::i16x8_arg to_floor_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x8 ceil_i16x8(EmuSIMD::i16x8_arg to_ceil_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x8 trunc_i16x8(EmuSIMD::i16x8_arg to_trunc_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x8 mod_i16x8(EmuSIMD::i16x8_arg lhs_, EmuSIMD::i16x8_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x8 abs_i16x8(EmuSIMD::i16x8_arg in_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x8 sqrt_i16x8(EmuSIMD::i16x8_arg in_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x8 rsqrt_i16x8(EmuSIMD::i16x8_arg in_);
#pragma endregion

#pragma region NEAR_COMPARISONS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x8 cmpnear_i16x8(EmuSIMD::i16x8_arg lhs_, EmuSIMD::i16x8_arg rhs_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x8 cmpnear_i16x8(EmuSIMD::i16x8_arg lhs_, EmuSIMD::i16x8_arg rhs_, EmuSIMD::i16x8_arg epsilon);
#pragma endregion

#pragma region TRIG
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x8 cos_i16x8(EmuSIMD::i16x8_arg in_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x8 sin_i16x8(EmuSIMD::i16x8_arg in_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x8 tan_i16x8(EmuSIMD::i16x8_arg in_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x8 acos_i16x8(EmuSIMD::i16x8_arg in_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x8 asin_i16x8(EmuSIMD::i16x8_arg in_);
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x8 atan_i16x8(EmuSIMD::i16x8_arg in_);
#pragma endregion

#pragma region ROUNDING_TEMPLATES
	template<int RoundingFlag_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x8 round_i16x8(EmuSIMD::i16x8_arg to_round_)
	{
		return to_round_;
	}
#pragma endregion

#pragma region SHUFFLE_TEMPLATES
	template<EmuSIMD::Funcs::shuffle_mask_type ShuffleMask_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x8 permute_i16x8(EmuSIMD::i16x8_arg a_)
	{
		static_assert(EmuCore::TMP::get_false<ShuffleMask_>(), "NO SUPPORT ERROR: EmuSIMD does not provide support for permuting i16x8 (128-bit registers containing 8 16-bit signed integer elements) [permute_i16x8].");
		return EmuSIMD::i16x8{};
	}

	template<EmuSIMD::Funcs::shuffle_mask_type ShuffleMask_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x8 shuffle_i16x8(EmuSIMD::i16x8_arg a_, EmuSIMD::i16x8_arg b_)
	{
		static_assert(EmuCore::TMP::get_false<ShuffleMask_>(), "NO SUPPORT ERROR: EmuSIMD does not provide support for shuffling i16x8 (128-bit registers containing 8 16-bit signed integer elements) [shuffle_i16x8].");
		return EmuSIMD::i16x8{};
	}
#pragma endregion

#pragma region BLEND_TEMPLATES
	template<EmuSIMD::Funcs::blend_mask_type BlendMask_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x8 blend_i16x8(EmuSIMD::i16x8_arg a_, EmuSIMD::i16x8_arg b_)
	{
		return _mm_blend_epi16(a_, b_, BlendMask_);
	}
#pragma endregion

#pragma region TEMPLATES
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
	EMU_SIMD_COMMON_FUNC_SPEC auto emulate_fp_i16x8(Func_ func_, EmuSIMD::i16x8_arg in_)
		-> std::enable_if_t<std::is_invocable_r_v<EmuSIMD::f32x4, decltype(func_), EmuSIMD::f32x4>, EmuSIMD::i16x8>
	{
		constexpr std::size_t num_elements = 8;
		constexpr std::size_t elements_per_register = 4;
		std::int16_t data[num_elements];
		float results[num_elements];

		store_i16x8(data, in_);
		for (std::size_t i = 0; i < num_elements; i += elements_per_register)
		{
			store_f32x4(results + i, func_(set_f32x4(static_cast<float>(data[i + 3]), static_cast<float>(data[i + 2]), static_cast<float>(data[i + 1]), static_cast<float>(data[i]))));
		}

		return set_i16x8
		(
			static_cast<std::int16_t>(results[7]),
			static_cast<std::int16_t>(results[6]),
			static_cast<std::int16_t>(results[5]),
			static_cast<std::int16_t>(results[4]),
			static_cast<std::int16_t>(results[3]),
			static_cast<std::int16_t>(results[2]),
			static_cast<std::int16_t>(results[1]),
			static_cast<std::int16_t>(results[0])
		);
	}
#pragma endregion

#pragma region EXTRACTION_TEMPLATES
	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x8 extract_f32x4_lane_i16x8(f32x4_arg a_)
	{
		static_assert(Index_ == 0, "Invalid SIMD lane extraction index: Extracting i16x8 lane from a f32x4 instance; the maximum index is 0 but this index has been exceeded");
		return cast_f32x4_i16x8(a_);
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x8 extract_f32x8_lane_i16x8(f32x8_arg a_)
	{
		static_assert(Index_ <= 1, "Invalid SIMD lane extraction index: Extracting i16x8 lane from a f32x8 instance; the maximum index is 1 but this index has been exceeded.");
		if constexpr (Index_ == 0)
		{
			return cast_f32x8_i16x8(a_);
		}
		else
		{
			return cast_f32x4_i16x8(_mm256_extractf128_ps(a_, Index_));
		}
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x8 extract_f32x16_lane_i16x8(f32x16_arg a_)
	{
		static_assert(Index_ <= 3, "Invalid SIMD lane extraction index: Extracting i16x8 lane from a f32x16 instance; the maximum index is 3 but this index has been exceeded.");
		if constexpr (Index_ == 0)
		{
			return cast_f32x16_i16x8(a_);
		}
		else
		{
			return cast_f32x4_i16x8(_mm512_extractf32x4_ps(a_, Index_));
		}
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x8 extract_f64x2_lane_i16x8(f64x2_arg a_)
	{
		static_assert(Index_ == 0, "Invalid SIMD lane extraction index: Extracting i16x8 lane from a f64x2 instance; the maximum index is 0 but this index has been exceeded.");
		return cast_f64x2_i16x8(a_);
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x8 extract_f64x4_lane_i16x8(f64x4_arg a_)
	{
		static_assert(Index_ <= 1, "Invalid SIMD lane extraction index: Extracting i16x8 lane from a f64x4 instance; the maximum index is 1 but this index has been exceeded.");
		if constexpr (Index_ == 0)
		{
			return cast_f64x4_i16x8(a_);
		}
		else
		{
			return cast_f64x2_i16x8(_mm256_extractf128_pd(a_, Index_));
		}
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x8 extract_f64x8_lane_i16x8(f64x8_arg a_)
	{
		static_assert(Index_ <= 3, "Invalid SIMD lane extraction index: Extracting i16x8 lane from a f64x8 instance; the maximum index is 3 but this index has been exceeded.");
		if constexpr (Index_ == 0)
		{
			return cast_f64x8_i16x8(a_);
		}
		else
		{
			return cast_f64x2_i16x8(_mm512_extractf64x2_pd(a_, Index_));
		}
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x8 extract_i8x16_lane_i16x8(i8x16_arg a_)
	{
		static_assert(Index_ == 0, "Invalid SIMD lane extraction index: Extracting i16x8 lane from a i8x16 instance; the maximum index is 0 but this index has been exceeded.");
		return cast_i8x16_i16x8(a_);
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x8 extract_i8x32_lane_i16x8(i8x32_arg a_)
	{
		static_assert(Index_ <= 1, "Invalid SIMD lane extraction index: Extracting i16x8 lane from a i8x32 instance; the maximum index is 1 but this index has been exceeded.");
		if constexpr (Index_ == 0)
		{
			return cast_i8x32_i16x8(a_);
		}
		else
		{
			return _mm256_extracti128_si256(a_, Index_);
		}
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x8 extract_i8x64_lane_i16x8(i8x64_arg a_)
	{
		static_assert(Index_ <= 3, "Invalid SIMD lane extraction index: Extracting i16x8 lane from a i8x64 instance; the maximum index is 3 but this index has been exceeded.");
		if constexpr (Index_ == 0)
		{
			return cast_i8x64_i16x8(a_);
		}
		else
		{
			return _mm512_extracti32x4_epi32(a_, Index_);
		}
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x8 extract_i16x8_lane_i16x8(i16x8_arg a_)
	{
		static_assert(Index_ == 0, "Invalid SIMD lane extraction index: Extracting i16x8 lane from a i16x8 instance; the maximum index is 0 but this index has been exceeded.");
		return a_;
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x8 extract_i16x16_lane_i16x8(i16x16_arg a_)
	{
		static_assert(Index_ <= 1, "Invalid SIMD lane extraction index: Extracting i16x8 lane from a i16x16 instance; the maximum index is 1 but this index has been exceeded.");
		if constexpr (Index_ == 0)
		{
			return cast_i16x16_i16x8(a_);
		}
		else
		{
			return _mm256_extracti128_si256(a_, Index_);
		}
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x8 extract_i16x32_lane_i16x8(i16x32_arg a_)
	{
		static_assert(Index_ <= 3, "Invalid SIMD lane extraction index: Extracting i16x8 lane from a i16x32 instance; the maximum index is 3 but this index has been exceeded.");
		if constexpr (Index_ == 0)
		{
			return cast_i16x32_i16x8(a_);
		}
		else
		{
			return _mm512_extracti32x4_epi32(a_, Index_);
		}
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x8 extract_i32x4_lane_i16x8(i32x4_arg a_)
	{
		static_assert(Index_ == 0, "Invalid SIMD lane extraction index: Extracting i16x8 lane from a i32x4 instance; the maximum index is 0 but this index has been exceeded.");
		return cast_i32x4_i16x8(a_);
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x8 extract_i32x8_lane_i16x8(i32x8_arg a_)
	{
		static_assert(Index_ <= 1, "Invalid SIMD lane extraction index: Extracting i16x8 lane from a i32x8 instance; the maximum index is 1 but this index has been exceeded.");
		if constexpr (Index_ == 0)
		{
			return cast_i32x8_i16x8(a_);
		}
		else
		{
			return _mm256_extracti128_si256(a_, Index_);
		}
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x8 extract_i32x16_lane_i16x8(i32x16_arg a_)
	{
		static_assert(Index_ <= 3, "Invalid SIMD lane extraction index: Extracting i16x8 lane from a i32x16 instance; the maximum index is 3 but this index has been exceeded.");
		if constexpr (Index_ == 0)
		{
			return cast_i32x16_i16x8(a_);
		}
		else
		{
			return _mm512_extracti32x4_epi32(a_, Index_);
		}
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x8 extract_i64x2_lane_i16x8(i64x2_arg a_)
	{
		static_assert(Index_ == 0, "Invalid SIMD lane extraction index: Extracting i16x8 lane from a i64x2 instance; the maximum index is 0 but this index has been exceeded.");
		return cast_i64x2_i16x8(a_);
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x8 extract_i64x4_lane_i16x8(i64x4_arg a_)
	{
		static_assert(Index_ <= 1, "Invalid SIMD lane extraction index: Extracting i16x8 lane from a i64x4 instance; the maximum index is 1 but this index has been exceeded.");
		if constexpr (Index_ == 0)
		{
			return cast_i64x4_i16x8(a_);
		}
		else
		{
			return _mm256_extracti128_si256(a_, Index_);
		}
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x8 extract_i64x8_lane_i16x8(i64x8_arg a_)
	{
		static_assert(Index_ <= 3, "Invalid SIMD lane extraction index: Extracting i16x8 lane from a i64x8 instance; the maximum index is 3 but this index has been exceeded.");
		if constexpr (Index_ == 0)
		{
			return cast_i64x8_i16x8(a_);
		}
		else
		{
			return _mm512_extracti32x4_epi32(a_, Index_);
		}
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x8 extract_u8x16_lane_i16x8(u8x16_arg a_)
	{
		static_assert(Index_ == 0, "Invalid SIMD lane extraction index: Extracting i16x8 lane from a u8x16 instance; the maximum index is 0 but this index has been exceeded.");
		return cast_u8x16_i16x8(a_);
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x8 extract_u8x32_lane_i16x8(u8x32_arg a_)
	{
		static_assert(Index_ <= 1, "Invalid SIMD lane extraction index: Extracting i16x8 lane from a u8x32 instance; the maximum index is 1 but this index has been exceeded.");
		if constexpr (Index_ == 0)
		{
			return cast_u8x32_i16x8(a_);
		}
		else
		{
			return _mm256_extracti128_si256(a_, Index_);
		}
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x8 extract_u8x64_lane_i16x8(u8x64_arg a_)
	{
		static_assert(Index_ <= 3, "Invalid SIMD lane extraction index: Extracting i16x8 lane from a u8x64 instance; the maximum index is 3 but this index has been exceeded.");
		if constexpr (Index_ == 0)
		{
			return cast_u8x64_i16x8(a_);
		}
		else
		{
			return _mm512_extracti32x4_epi32(a_, Index_);
		}
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x8 extract_u16x8_lane_i16x8(u16x8_arg a_)
	{
		static_assert(Index_ == 0, "Invalid SIMD lane extraction index: Extracting i16x8 lane from a u16x8 instance; the maximum index is 0 but this index has been exceeded.");
		return cast_u16x8_i16x8(a_);
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x8 extract_u16x16_lane_i16x8(u16x16_arg a_)
	{
		static_assert(Index_ <= 1, "Invalid SIMD lane extraction index: Extracting i16x8 lane from a u16x16 instance; the maximum index is 1 but this index has been exceeded.");
		if constexpr (Index_ == 0)
		{
			return cast_u16x16_i16x8(a_);
		}
		else
		{
			return _mm256_extracti128_si256(a_, Index_);
		}
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x8 extract_u16x32_lane_i16x8(u16x32_arg a_)
	{
		static_assert(Index_ <= 3, "Invalid SIMD lane extraction index: Extracting i16x8 lane from a u16x32 instance; the maximum index is 3 but this index has been exceeded.");
		if constexpr (Index_ == 0)
		{
			return cast_u16x32_i16x8(a_);
		}
		else
		{
			return _mm512_extracti32x4_epi32(a_, Index_);
		}
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x8 extract_u32x4_lane_i16x8(u32x4_arg a_)
	{
		static_assert(Index_ == 0, "Invalid SIMD lane extraction index: Extracting i16x8 lane from a i8x16 instance; the maximum index is 0 but this index has been exceeded.");
		return cast_u32x4_i16x8(a_);
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x8 extract_u32x8_lane_i16x8(u32x8_arg a_)
	{
		static_assert(Index_ <= 1, "Invalid SIMD lane extraction index: Extracting i16x8 lane from a u32x8 instance; the maximum index is 1 but this index has been exceeded.");
		if constexpr (Index_ == 0)
		{
			return cast_u32x8_i16x8(a_);
		}
		else
		{
			return _mm256_extracti128_si256(a_, Index_);
		}
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x8 extract_u32x16_lane_i16x8(u32x16_arg a_)
	{
		static_assert(Index_ <= 3, "Invalid SIMD lane extraction index: Extracting i16x8 lane from a ui8x16 instance; the maximum index is 3 but this index has been exceeded.");
		if constexpr (Index_ == 0)
		{
			return cast_u32x16_i16x8(a_);
		}
		else
		{
			return _mm512_extracti32x4_epi32(a_, Index_);
		}
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x8 extract_u64x2_lane_i16x8(u64x2_arg a_)
	{
		static_assert(Index_ == 0, "Invalid SIMD lane extraction index: Extracting i16x8 lane from a u64x2 instance; the maximum index is 0 but this index has been exceeded.");
		return cast_u64x2_i16x8(a_);
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x8 extract_u64x4_lane_i16x8(u64x4_arg a_)
	{
		static_assert(Index_ <= 1, "Invalid SIMD lane extraction index: Extracting i16x8 lane from a u64x4 instance; the maximum index is 1 but this index has been exceeded.");
		if constexpr (Index_ == 0)
		{
			return cast_u64x4_i16x8(a_);
		}
		else
		{
			return _mm256_extracti128_si256(a_, Index_);
		}
	}

	template<std::size_t Index_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x8 extract_u64x8_lane_i16x8(u64x8_arg a_)
	{
		static_assert(Index_ <= 3, "Invalid SIMD lane extraction index: Extracting i16x8 lane from a u64x8 instance; the maximum index is 3 but this index has been exceeded.");
		if constexpr (Index_ == 0)
		{
			return cast_u64x8_i16x8(a_);
		}
		else
		{
			return _mm512_extracti32x4_epi32(a_, Index_);
		}
	}
#pragma endregion
}

#endif
