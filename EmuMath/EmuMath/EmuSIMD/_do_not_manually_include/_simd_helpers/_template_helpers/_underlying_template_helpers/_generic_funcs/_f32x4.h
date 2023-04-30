#ifndef EMU_SIMD_GENERIC_FUNCS_F32X4_H_INC_
#define EMU_SIMD_GENERIC_FUNCS_F32X4_H_INC_ 1

#include "_generic_declarations/_all_generic_declarations.h"
#include "_common_generic_func_helpers.h"

namespace EmuSIMD::Funcs
{
#pragma region SETTERS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 set_f32x4(float e0, float e1, float e2, float e3)
	{
#if EMU_SIMD_USE_128_REGISTERS
		return _mm_set_ps(e0, e1, e2, e3);
#else
		// Emulated, we use reverse-ordering in this case
		return _underlying_impl::set_single_lane_simd_emulator<4, float>(e3, e2, e1, e0);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 setr_f32x4(float e0, float e1, float e2, float e3)
	{
#if EMU_SIMD_USE_128_REGISTERS
		return _mm_set_ps(e3, e2, e1, e0);
#else
		// Emulated, we use reverse-ordering in this case
		return _underlying_impl::set_single_lane_simd_emulator<4, float>(e0, e1, e2, e3);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 set1_f32x4(float all_)
	{
#if EMU_SIMD_USE_128_REGISTERS
		return _mm_set1_ps(all_);
#else
		return _underlying_impl::set1_single_lane_simd_emulator<4, float>(all_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 load_f32x4(const float* p_to_load_)
	{
#if EMU_SIMD_USE_128_REGISTERS
		return _mm_load_ps(p_to_load_);
#else
		return _underlying_impl::load_single_lane_simd_emulator<4, float>(p_to_load_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 setzero_f32x4()
	{
#if EMU_SIMD_USE_128_REGISTERS
		return _mm_setzero_ps();
#else
		return _underlying_impl::set_single_lane_simd_emulator<4, float>();
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 setmasked_f32x4(std::uint8_t bit_mask_)
	{
#if EMU_SIMD_USE_128_REGISTERS
		constexpr std::int32_t element_mask = static_cast<std::int32_t>(0xFFFFFFFF);
		return _mm_castsi128_ps
		(
			_mm_set_epi32
			(
				(bit_mask_ & 0x01) * element_mask,
				((bit_mask_ & 0x02) >> 1) * element_mask,
				((bit_mask_ & 0x04) >> 2) * element_mask,
				((bit_mask_ & 0x08) >> 3) * element_mask
			)
		);
#else
		return _underlying_impl::setmasked_single_lane_simd_emulator<4, float>(bit_mask_);
#endif
	}
#pragma endregion

#pragma region STORES
	EMU_SIMD_COMMON_FUNC_SPEC void store_f32x4(float* p_out_, f32x4_arg a_)
	{
#if EMU_SIMD_USE_128_REGISTERS
		_mm_store_ps(p_out_, a_);
#else
		_underlying_impl::emulate_simd_store(a_, p_out_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC float get_first_f32x4(f32x4_arg a_)
	{
		return _mm_cvtss_f32(a_);
	}
#pragma endregion

#pragma region CASTS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cast_f32x4_f32x4(f32x4_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cast_f32x8_f32x4(f32x8_arg a_)
	{
#if EMU_SIMD_USE_256_REGISTERS
		return _mm256_castps256_ps128(a_);
#else
		return _underlying_impl::emulate_simd_cast_lesser_width<f32x4>(a_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cast_f32x16_f32x4(f32x16_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_castps512_ps128(a_);
#else
		return _underlying_impl::emulate_simd_cast_lesser_width<f32x4>(a_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cast_f64x2_f32x4(f64x2_arg a_)
	{
#if EMU_SIMD_USE_128_REGISTERS
		return _mm_castpd_ps(a_);
#else
		return _underlying_impl::emulate_simd_cast_same_width<4, float>(a_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cast_f64x4_f32x4(f64x4_arg a_)
	{
#if EMU_SIMD_USE_256_REGISTERS
		return _mm256_castps256_ps128(_mm256_castpd_ps(a_));
#else
		return _underlying_impl::emulate_simd_cast_lesser_width<f32x4>(a_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cast_f64x8_f32x4(f64x8_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_castps512_ps128(_mm512_castpd_ps(a_));
#else
		return _underlying_impl::emulate_simd_cast_lesser_width<f32x4>(a_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cast_i8x16_f32x4(i8x16_arg a_)
	{
#if EMU_SIMD_USE_128_REGISTERS
		return _mm_castsi128_ps(a_);
#else
		return _underlying_impl::emulate_simd_cast_same_width<4, float>(a_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cast_i16x8_f32x4(i16x8_arg a_)
	{
#if EMU_SIMD_USE_128_REGISTERS
		return _mm_castsi128_ps(a_);
#else
		return _underlying_impl::emulate_simd_cast_same_width<4, float>(a_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cast_i32x4_f32x4(i32x4_arg a_)
	{
#if EMU_SIMD_USE_128_REGISTERS
		return _mm_castsi128_ps(a_);
#else
		return _underlying_impl::emulate_simd_cast_same_width<4, float>(a_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cast_i64x2_f32x4(i64x2_arg a_)
	{
#if EMU_SIMD_USE_128_REGISTERS
		return _mm_castsi128_ps(a_);
#else
		return _underlying_impl::emulate_simd_cast_same_width<4, float>(a_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cast_i8x32_f32x4(i8x32_arg a_)
	{
#if EMU_SIMD_USE_256_REGISTERS
		return _mm256_castps256_ps128(_mm256_castsi256_ps(a_));
#else
		return _underlying_impl::emulate_simd_cast_same_width<4, float>(a_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cast_i16x16_f32x4(i16x16_arg a_)
	{
#if EMU_SIMD_USE_256_REGISTERS
		return _mm256_castps256_ps128(_mm256_castsi256_ps(a_));
#else
		return _underlying_impl::emulate_simd_cast_same_width<4, float>(a_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cast_i32x8_f32x4(i32x8_arg a_)
	{
#if EMU_SIMD_USE_256_REGISTERS
		return _mm256_castps256_ps128(_mm256_castsi256_ps(a_));
#else
		return _underlying_impl::emulate_simd_cast_same_width<4, float>(a_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cast_i64x4_f32x4(i64x4_arg a_)
	{
#if EMU_SIMD_USE_256_REGISTERS
		return _mm256_castps256_ps128(_mm256_castsi256_ps(a_));
#else
		return _underlying_impl::emulate_simd_cast_same_width<4, float>(a_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cast_i8x64_f32x4(i8x64_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_castps512_ps128(_mm512_castsi512_ps(a_));
#else
		return _underlying_impl::emulate_simd_cast_same_width<4, float>(a_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cast_i16x32_f32x4(i16x32_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_castps512_ps128(_mm512_castsi512_ps(a_));
#else
		return _underlying_impl::emulate_simd_cast_same_width<4, float>(a_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cast_i32x16_f32x4(i32x16_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_castps512_ps128(_mm512_castsi512_ps(a_));
#else
		return _underlying_impl::emulate_simd_cast_same_width<4, float>(a_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cast_i64x8_f32x4(i64x8_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_castps512_ps128(_mm512_castsi512_ps(a_));
#else
		return _underlying_impl::emulate_simd_cast_same_width<4, float>(a_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cast_u8x16_f32x4(u8x16_arg a_)
	{
#if EMU_SIMD_USE_128_REGISTERS
		return _mm_castsi128_ps(a_);
#else
		return _underlying_impl::emulate_simd_cast_same_width<4, float>(a_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cast_u16x8_f32x4(u16x8_arg a_)
	{
#if EMU_SIMD_USE_128_REGISTERS
		return _mm_castsi128_ps(a_);
#else
		return _underlying_impl::emulate_simd_cast_same_width<4, float>(a_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cast_u32x4_f32x4(u32x4_arg a_)
	{
#if EMU_SIMD_USE_128_REGISTERS
		return _mm_castsi128_ps(a_);
#else
		return _underlying_impl::emulate_simd_cast_same_width<4, float>(a_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cast_u64x2_f32x4(u64x2_arg a_)
	{
#if EMU_SIMD_USE_128_REGISTERS
		return _mm_castsi128_ps(a_);
#else
		return _underlying_impl::emulate_simd_cast_same_width<4, float>(a_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cast_u8x32_f32x4(u8x32_arg a_)
	{
#if EMU_SIMD_USE_256_REGISTERS
		return _mm256_castps256_ps128(_mm256_castsi256_ps(a_));
#else
		return _underlying_impl::emulate_simd_cast_same_width<4, float>(a_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cast_u16x16_f32x4(u16x16_arg a_)
	{
#if EMU_SIMD_USE_256_REGISTERS
		return _mm256_castps256_ps128(_mm256_castsi256_ps(a_));
#else
		return _underlying_impl::emulate_simd_cast_same_width<4, float>(a_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cast_u32x8_f32x4(u32x8_arg a_)
	{
#if EMU_SIMD_USE_256_REGISTERS
		return _mm256_castps256_ps128(_mm256_castsi256_ps(a_));
#else
		return _underlying_impl::emulate_simd_cast_same_width<4, float>(a_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cast_u64x4_f32x4(u64x4_arg a_)
	{
#if EMU_SIMD_USE_256_REGISTERS
		return _mm256_castps256_ps128(_mm256_castsi256_ps(a_));
#else
		return _underlying_impl::emulate_simd_cast_same_width<4, float>(a_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cast_u8x64_f32x4(u8x64_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_castps512_ps128(_mm512_castsi512_ps(a_));
#else
		return _underlying_impl::emulate_simd_cast_same_width<4, float>(a_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cast_u16x32_f32x4(u16x32_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_castps512_ps128(_mm512_castsi512_ps(a_));
#else
		return _underlying_impl::emulate_simd_cast_same_width<4, float>(a_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cast_u32x16_f32x4(u32x16_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_castps512_ps128(_mm512_castsi512_ps(a_));
#else
		return _underlying_impl::emulate_simd_cast_same_width<4, float>(a_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cast_u64x8_f32x4(u64x8_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_castps512_ps128(_mm512_castsi512_ps(a_));
#else
		return _underlying_impl::emulate_simd_cast_same_width<4, float>(a_);
#endif
	}
#pragma endregion

#pragma region CONVERSIONS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cvt_f32x4_f32x4(f32x4_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cvt_f32x8_f32x4(f32x8_arg a_)
	{
		return _mm256_castps256_ps128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cvt_f32x16_f32x4(f32x16_arg a_)
	{
		return _mm512_castps512_ps128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cvt_f64x2_f32x4(f64x2_arg a_)
	{
		return _mm_cvtpd_ps(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cvt_f64x4_f32x4(f64x4_arg a_)
	{
		return _mm256_cvtpd_ps(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cvt_f64x8_f32x4(f64x8_arg a_)
	{
		return _mm256_cvtpd_ps(_mm512_castpd512_pd256(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cvt_i8x16_f32x4(i8x16_arg a_)
	{
		return _mm_cvtepi32_ps(_mm_cvtepi8_epi32(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cvt_i16x8_f32x4(i16x8_arg a_)
	{
		return _mm_cvtepi32_ps(_mm_cvtepi16_epi32(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cvt_i32x4_f32x4(i32x4_arg a_)
	{
		return _mm_cvtepi32_ps(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cvt_i64x2_f32x4(i64x2_arg a_)
	{
		return _mm_cvtepi64_ps(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cvt_i8x32_f32x4(i8x32_arg a_)
	{
		return _mm_cvtepi32_ps(_mm_cvtepi8_epi32(_mm256_castsi256_si128(a_)));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cvt_i16x16_f32x4(i16x16_arg a_)
	{
		return _mm_cvtepi32_ps(_mm_cvtepi16_epi32(_mm256_castsi256_si128(a_)));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cvt_i32x8_f32x4(i32x8_arg a_)
	{
		return _mm_cvtepi32_ps(_mm256_castsi256_si128(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cvt_i64x4_f32x4(i64x4_arg a_)
	{
		return _mm256_cvtepi64_ps(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cvt_i8x64_f32x4(i8x64_arg a_)
	{
		return _mm_cvtepi32_ps(_mm_cvtepi8_epi32(_mm512_castsi512_si128(a_)));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cvt_i16x32_f32x4(i16x32_arg a_)
	{
		return _mm_cvtepi32_ps(_mm_cvtepi16_epi32(_mm512_castsi512_si128(a_)));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cvt_i32x16_f32x4(i32x16_arg a_)
	{
		return _mm_cvtepi32_ps(_mm512_castsi512_si128(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cvt_i64x8_f32x4(i64x8_arg a_)
	{
		return _mm256_cvtepi64_ps(_mm512_castsi512_si256(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cvt_u8x16_f32x4(u8x16_arg a_)
	{
		return _mm_cvtepi32_ps(_mm_cvtepu8_epi32(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cvt_u16x8_f32x4(u16x8_arg a_)
	{
		return _mm_cvtepi32_ps(_mm_cvtepu16_epi32(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cvt_u32x4_f32x4(u32x4_arg a_)
	{
		return _mm_cvtepu32_ps(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cvt_u64x2_f32x4(u64x2_arg a_)
	{
		return _mm_cvtepu64_ps(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cvt_u8x32_f32x4(u8x32_arg a_)
	{
		return _mm_cvtepi32_ps(_mm_cvtepu8_epi32(_mm256_castsi256_si128(a_)));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cvt_u16x16_f32x4(u16x16_arg a_)
	{
		return _mm_cvtepi32_ps(_mm_cvtepu16_epi32(_mm256_castsi256_si128(a_)));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cvt_u32x8_f32x4(u32x8_arg a_)
	{
		return _mm_cvtepu32_ps(_mm256_castsi256_si128(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cvt_u64x4_f32x4(u64x4_arg a_)
	{
		return _mm256_cvtepu64_ps(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cvt_u8x64_f32x4(u8x64_arg a_)
	{
		return _mm_cvtepi32_ps(_mm_cvtepu8_epi32(_mm512_castsi512_si128(a_)));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cvt_u16x32_f32x4(u16x32_arg a_)
	{
		return _mm_cvtepi32_ps(_mm_cvtepu16_epi32(_mm512_castsi512_si128(a_)));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cvt_u32x16_f32x4(u32x16_arg a_)
	{
		return _mm_cvtepu32_ps(_mm512_castsi512_si128(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cvt_u64x8_f32x4(u64x8_arg a_)
	{
		return _mm256_cvtepu64_ps(_mm512_castsi512_si256(a_));
	}
#pragma endregion

#pragma region COMPARISONS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cmpeq_f32x4(EmuSIMD::f32x4_arg lhs_, EmuSIMD::f32x4_arg rhs_)
	{
		return _mm_cmpeq_ps(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cmpneq_f32x4(EmuSIMD::f32x4_arg lhs_, EmuSIMD::f32x4_arg rhs_)
	{
		return _mm_cmpneq_ps(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cmpgt_f32x4(EmuSIMD::f32x4_arg lhs_, EmuSIMD::f32x4_arg rhs_)
	{
		return _mm_cmpgt_ps(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cmplt_f32x4(EmuSIMD::f32x4_arg lhs_, EmuSIMD::f32x4_arg rhs_)
	{
		return _mm_cmplt_ps(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cmpge_f32x4(EmuSIMD::f32x4_arg lhs_, EmuSIMD::f32x4_arg rhs_)
	{
		return _mm_cmpge_ps(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cmple_f32x4(EmuSIMD::f32x4_arg lhs_, EmuSIMD::f32x4_arg rhs_)
	{
		return _mm_cmple_ps(lhs_, rhs_);
	}
#pragma endregion

#pragma region BLENDS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 blendv_f32x4(EmuSIMD::f32x4_arg a_, EmuSIMD::f32x4_arg b_, EmuSIMD::f32x4_arg shuffle_mask_vec_)
	{
		return _mm_blendv_ps(a_, b_, shuffle_mask_vec_);
	}
#pragma endregion

#pragma region MOVES
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 movehl_f32x4(EmuSIMD::f32x4_arg lhs_, EmuSIMD::f32x4_arg rhs_)
	{
		return _mm_movehl_ps(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 movelh_f32x4(EmuSIMD::f32x4_arg lhs_, EmuSIMD::f32x4_arg rhs_)
	{
		return _mm_movelh_ps(lhs_, rhs_);
	}
#pragma endregion

#pragma region BITWISE_ARITHMETIC
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 and_f32x4(EmuSIMD::f32x4_arg lhs_, EmuSIMD::f32x4_arg rhs_)
	{
#if EMU_SIMD_USE_128_REGISTERS
		return _mm_and_ps(lhs_, rhs_);
#else
		using EmuSIMD::_underlying_impl::emulate_simd_basic;
		using index_sequence = std::make_index_sequence<4>;
		return emulate_simd_basic(EmuCore::do_bitwise_and<float>(), lhs_, rhs_, index_sequence());
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 or_f32x4(EmuSIMD::f32x4_arg lhs_, EmuSIMD::f32x4_arg rhs_)
	{
#if EMU_SIMD_USE_128_REGISTERS
		return _mm_or_ps(lhs_, rhs_);
#else
		using EmuSIMD::_underlying_impl::emulate_simd_basic;
		using index_sequence = std::make_index_sequence<4>;
		return emulate_simd_basic(EmuCore::do_bitwise_or<float>(), lhs_, rhs_, index_sequence());
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 xor_f32x4(EmuSIMD::f32x4_arg lhs_, EmuSIMD::f32x4_arg rhs_)
	{
#if EMU_SIMD_USE_128_REGISTERS
		return _mm_xor_ps(lhs_, rhs_);
#else
		using EmuSIMD::_underlying_impl::emulate_simd_basic;
		using index_sequence = std::make_index_sequence<4>;
		return emulate_simd_basic(EmuCore::do_bitwise_xor<float>(), lhs_, rhs_, index_sequence());
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 andnot_f32x4(EmuSIMD::f32x4_arg not_lhs_, EmuSIMD::f32x4_arg rhs_)
	{
#if EMU_SIMD_USE_128_REGISTERS
		return _mm_andnot_ps(not_lhs_, rhs_);
#else
		using EmuSIMD::_underlying_impl::emulate_simd_basic;
		using index_sequence = std::make_index_sequence<4>;
		return emulate_simd_basic(EmuCore::do_bitwise_andnot<float>(), not_lhs_, rhs_, index_sequence());
#endif
	}

	template<std::int32_t NumShifts_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 shift_left_f32x4(EmuSIMD::f32x4_arg lhs_)
	{
		return cast_i32x4_f32x4
		(
			shift_left_i32x4<NumShifts_>(cast_f32x4_i32x4(lhs_))
		);
	}

	template<std::int32_t NumShifts_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 shift_right_arithmetic_f32x4(EmuSIMD::f32x4_arg lhs_)
	{
		if constexpr (NumShifts_ >= 32)
		{
			return setzero_f32x4();
		}
		else
		{
			constexpr float sign_bit = -0.0f;
			f32x4 sign_mask = set1_f32x4(sign_bit);
			sign_mask = and_f32x4(sign_mask, lhs_);
			return or_f32x4(sign_mask, shift_right_logical_f32x4<NumShifts_>(lhs_));
		}
	}

	template<std::int32_t NumShifts_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 shift_right_logical_f32x4(EmuSIMD::f32x4_arg lhs_)
	{
		return cast_i32x4_f32x4
		(
			shift_right_logical_i32x4<NumShifts_>(cast_f32x4_i32x4(lhs_))
		);
	}
#pragma endregion

#pragma region MINMAX_FUNCS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 min_f32x4(EmuSIMD::f32x4_arg a_, EmuSIMD::f32x4_arg b_)
	{
		return _mm_min_ps(a_, b_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 horizontal_min_f32x4(EmuSIMD::f32x4_arg a_)
	{
		EmuSIMD::f32x4 min = movehl_f32x4(a_, a_);
		min = min_f32x4(min, a_);
		min = min_f32x4
		(
			permute_f32x4<make_shuffle_mask_32<0, 1, 0, 1>()>(min),
			min
		);
		return permute_f32x4<make_shuffle_mask_32<0, 0, 0, 0>()>(min);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 max_f32x4(EmuSIMD::f32x4_arg a_, EmuSIMD::f32x4_arg b_)
	{
		return _mm_max_ps(a_, b_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 horizontal_max_f32x4(EmuSIMD::f32x4_arg a_)
	{
		EmuSIMD::f32x4 max = movehl_f32x4(a_, a_);
		max = max_f32x4(max, a_);
		max = max_f32x4
		(
			permute_f32x4<make_shuffle_mask_32<0, 1, 0, 1>()>(max),
			max
		);
		return permute_f32x4<make_shuffle_mask_32<0, 0, 0, 0>()>(max);
	}
#pragma endregion

#pragma region BASIC_ARITHMETIC
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 mul_all_f32x4(EmuSIMD::f32x4_arg lhs_, EmuSIMD::f32x4_arg rhs_)
	{
		return _mm_mul_ps(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 add_f32x4(EmuSIMD::f32x4_arg lhs_, EmuSIMD::f32x4_arg rhs_)
	{
		return _mm_add_ps(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 sub_f32x4(EmuSIMD::f32x4_arg lhs_, EmuSIMD::f32x4_arg rhs_)
	{
		return _mm_sub_ps(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 negate_f32x4(EmuSIMD::f32x4_arg to_negate_)
	{
		if constexpr (std::numeric_limits<float>::is_iec559)
		{
			// IEEE-754 std, value is identical when negative except left-most bit, so just flip msb
			return xor_f32x4(to_negate_, set1_f32x4(-0.0f));
		}
		else
		{
			return sub_f32x4(setzero_f32x4(), to_negate_);
		}
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 mul_f32x4(EmuSIMD::f32x4_arg lhs_, EmuSIMD::f32x4_arg rhs_)
	{
		return _mm_mul_ps(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 div_f32x4(EmuSIMD::f32x4_arg lhs_, EmuSIMD::f32x4_arg rhs_)
	{
		return _mm_div_ps(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 addsub_f32x4(EmuSIMD::f32x4_arg lhs_, EmuSIMD::f32x4_arg rhs_)
	{
		return _mm_addsub_ps(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 fmadd_f32x4(EmuSIMD::f32x4_arg a_, EmuSIMD::f32x4_arg b_, EmuSIMD::f32x4_arg c_)
	{
		return _mm_fmadd_ps(a_, b_, c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 fmsub_f32x4(EmuSIMD::f32x4_arg a_, EmuSIMD::f32x4_arg b_, EmuSIMD::f32x4_arg c_)
	{
		return _mm_fmsub_ps(a_, b_, c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 fnmadd_f32x4(EmuSIMD::f32x4_arg a_, EmuSIMD::f32x4_arg b_, EmuSIMD::f32x4_arg c_)
	{
		return _mm_fnmadd_ps(a_, b_, c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 fnmsub_f32x4(EmuSIMD::f32x4_arg a_, EmuSIMD::f32x4_arg b_, EmuSIMD::f32x4_arg c_)
	{
		return _mm_fnmsub_ps(a_, b_, c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 fmaddsub_f32x4(EmuSIMD::f32x4_arg a_, EmuSIMD::f32x4_arg b_, EmuSIMD::f32x4_arg c_)
	{
		return _mm_fmaddsub_ps(a_, b_, c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 fmsubadd_f32x4(EmuSIMD::f32x4_arg a_, EmuSIMD::f32x4_arg b_, EmuSIMD::f32x4_arg c_)
	{
		return _mm_fmsubadd_ps(a_, b_, c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 subadd_f32x4(EmuSIMD::f32x4_arg lhs_, EmuSIMD::f32x4_arg rhs_)
	{
		return fmsubadd_f32x4(set1_f32x4(1.0f), lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 floor_f32x4(EmuSIMD::f32x4_arg to_floor_)
	{
		return _mm_floor_ps(to_floor_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 ceil_f32x4(EmuSIMD::f32x4_arg to_ceil_)
	{
		return _mm_ceil_ps(to_ceil_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 trunc_f32x4(EmuSIMD::f32x4_arg to_trunc_)
	{
		return _mm_round_ps(to_trunc_, EMU_SIMD_FLAG_TRUNC);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 mod_f32x4(EmuSIMD::f32x4_arg lhs_, EmuSIMD::f32x4_arg rhs_)
	{
		EmuSIMD::f32x4 res = div_f32x4(lhs_, rhs_);
		res = trunc_f32x4(res);
		return fmadd_f32x4(res, rhs_, lhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 abs_f32x4(EmuSIMD::f32x4_arg in_)
	{
		return andnot_f32x4(set1_f32x4(-0.0f), in_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 sqrt_f32x4(EmuSIMD::f32x4_arg in_)
	{
		return _mm_sqrt_ps(in_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 rsqrt_f32x4(EmuSIMD::f32x4_arg in_)
	{
		return _mm_rsqrt_ps(in_);
	}
#pragma endregion

#pragma region NEAR_COMPARISONS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cmpnear_f32x4(EmuSIMD::f32x4_arg lhs_, EmuSIMD::f32x4_arg rhs_, EmuSIMD::f32x4_arg epsilon)
	{
		return cmple_f32x4(abs_f32x4(sub_f32x4(lhs_, rhs_)), epsilon);
	}
#pragma endregion

#pragma region TRIG
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 cos_f32x4(EmuSIMD::f32x4_arg in_)
	{
		#if EMU_CORE_IS_INTEL_COMPILER && EMU_CORE_X86_X64 // Only tends to score better on Intel platforms
		return _mm_cos_ps(in_);
		#else
		// Alternative manual approximation, based on https://developer.download.nvidia.com/cg/cos.html implementation

		// Store constants used > once in registers to allow shuffling to them
		EmuSIMD::f32x4 c1x_c2x_c3x_c4x = setr_f32x4(0.25f, 24.9808039603f, 85.4537887573f, 19.7392082214f);
		EmuSIMD::f32x4 one_c2z_c3z_c4z = setr_f32x4(1.0f, -60.1458091736f, -64.9393539429f, -1.0f);

		// Prepare for power series
		EmuSIMD::f32x4 r1x = mul_f32x4(set1_f32x4(0.159154943091f), in_); // r1.x = c1.w * in_;

		EmuSIMD::f32x4 r1y = trunc_f32x4(r1x); // r1.y = frac(r1.x)
		r1y = sub_f32x4(r1x, r1y);

		EmuSIMD::f32x4 const0 = permute_f32x4<make_shuffle_mask_32<0, 0, 0, 0>()>(c1x_c2x_c3x_c4x);
		EmuSIMD::f32x4 r2x = cmplt_f32x4(r1x, const0); // r2.x = r1.x < c1.x

		const0 = permute_f32x4<make_shuffle_mask_32<0, 0, 0, 0>()>(one_c2z_c3z_c4z);
		r2x = and_f32x4(r2x, const0);

		EmuSIMD::f32x4 r2y = cmpge_f32x4(r1y, set1_f32x4(-9.0f)); // r2.yz = r1.yy >= c1.yz
		EmuSIMD::f32x4 r2z = cmpge_f32x4(r1y, set1_f32x4(0.75f));
		r2y = and_f32x4(r2y, const0);
		r2z = and_f32x4(r2z, const0);

		EmuSIMD::f32x4 const1 = permute_f32x4<make_shuffle_mask_32<3, 3, 3, 3>()>(one_c2z_c3z_c4z);
		r2y = fmadd_f32x4(r2x, const1, fmadd_f32x4(r2y, const0, mul_f32x4(r2z, const1))); // dot(r2, c4.zwz)

		EmuSIMD::f32x4 r0x = negate_f32x4(r1y);
		EmuSIMD::f32x4 r0y = sub_f32x4(set1_f32x4(0.5f), r1y);
		EmuSIMD::f32x4 r0z = sub_f32x4(const0, r1y);
		r0x = mul_f32x4(r0x, r0x);
		r0y = mul_f32x4(r0y, r0y);
		r0z = mul_f32x4(r0z, r0z);

		// Begin power series
		// --- Power 1
		const0 = permute_f32x4<make_shuffle_mask_32<1, 1, 1, 1>()>(one_c2z_c3z_c4z);
		const1 = permute_f32x4<make_shuffle_mask_32<1, 1, 1, 1>()>(c1x_c2x_c3x_c4x);
		r1x = fmadd_f32x4(const1, r0x, const0);
		r1y = fmadd_f32x4(set1_f32x4(-24.9808039603f), r0y, set1_f32x4(60.1458091736f));
		EmuSIMD::f32x4 r1z = fmadd_f32x4(const1, r0z, const0);

		// --- Power 2
		const0 = permute_f32x4<make_shuffle_mask_32<2, 2, 2, 2>()>(c1x_c2x_c3x_c4x);
		r1x = fmadd_f32x4(r1x, r0x, const0);
		r1y = fmadd_f32x4(r1y, r0y, set1_f32x4(-85.4537887573f));
		r1z = fmadd_f32x4(r1z, r0z, const0);

		// --- Power 3
		const0 = permute_f32x4<make_shuffle_mask_32<2, 2, 2, 2>()>(one_c2z_c3z_c4z);
		r1x = fmadd_f32x4(r1x, r0x, const0);
		r1y = fmadd_f32x4(r1y, r0y, set1_f32x4(64.9393539429f));
		r1z = fmadd_f32x4(r1z, r0z, const0);

		// --- Power 4
		const0 = permute_f32x4<make_shuffle_mask_32<3, 3, 3, 3>()>(c1x_c2x_c3x_c4x);
		r1x = fmadd_f32x4(r1x, r0x, const0);
		r1y = fmadd_f32x4(r1y, r0y, set1_f32x4(-19.7392082214f));
		r1z = fmadd_f32x4(r1z, r0z, const0);

		// --- Power 5
		const0 = permute_f32x4<make_shuffle_mask_32<0, 0, 0, 0>()>(one_c2z_c3z_c4z);
		const1 = permute_f32x4<make_shuffle_mask_32<3, 3, 3, 3>()>(one_c2z_c3z_c4z);
		r1x = fmadd_f32x4(r1x, r0x, const1);
		r1y = fmadd_f32x4(r1y, r0y, const0);
		r1z = fmadd_f32x4(r1z, r0z, const1);

		// Final dot
		r2x = negate_f32x4(r2x);
		r2y = negate_f32x4(r2y);
		r2z = negate_f32x4(r2z);

		return fmadd_f32x4(r1x, r2x, fmadd_f32x4(r1y, r2y, mul_f32x4(r1z, r2z)));
		#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 sin_f32x4(EmuSIMD::f32x4_arg in_)
	{
		#if EMU_CORE_IS_INTEL_COMPILER && EMU_CORE_X86_X64 // Only tends to score better on Intel platforms
		return _mm_sin_ps(in_);
		#else
		// Alternative manual approximation, based on https://developer.download.nvidia.com/cg/sin.html implementation
		
		// Store constants used > once in registers to allow shuffling to them
		EmuSIMD::f32x4 c1x_c2x_c3x_c4x = setr_f32x4(0.25f, 24.9808039603f, 85.4537887573f, 19.7392082214f);
		EmuSIMD::f32x4 one_c2z_c3z_c4z = setr_f32x4(1.0f, -60.1458091736f, -64.9393539429f, -1.0f);

		// Prepare for power series
		EmuSIMD::f32x4 const0 = permute_f32x4<make_shuffle_mask_32<0, 0, 0, 0>()>(c1x_c2x_c3x_c4x);
		EmuSIMD::f32x4 r1x = fmsub_f32x4(set1_f32x4(0.159154943091f), in_, const0); // r1.x = c1.w * in_ - c1.x

		EmuSIMD::f32x4 r1y = trunc_f32x4(r1x); // r1.y = frac(r1.x)
		r1y = sub_f32x4(r1x, r1y);

		EmuSIMD::f32x4 r2x = cmplt_f32x4(r1x, const0); // r2.x = r1.x < c1.x

		const0 = permute_f32x4<make_shuffle_mask_32<0, 0, 0, 0>()>(one_c2z_c3z_c4z);
		r2x = and_f32x4(r2x, const0);

		EmuSIMD::f32x4 r2y = cmpge_f32x4(r1y, set1_f32x4(-9.0f)); // r2.yz = r1.yy >= c1.yz
		EmuSIMD::f32x4 r2z = cmpge_f32x4(r1y, set1_f32x4(0.75f));
		r2y = and_f32x4(r2y, const0);
		r2z = and_f32x4(r2z, const0);

		EmuSIMD::f32x4 const1 = permute_f32x4<make_shuffle_mask_32<3, 3, 3, 3>()>(one_c2z_c3z_c4z);
		r2y = fmadd_f32x4(r2x, const1, fmadd_f32x4(r2y, const0, mul_f32x4(r2z, const1))); // dot(r2, c4.zwz)

		EmuSIMD::f32x4 r0x = negate_f32x4(r1y);
		EmuSIMD::f32x4 r0y = sub_f32x4(set1_f32x4(0.5f), r1y);
		EmuSIMD::f32x4 r0z = sub_f32x4(const0, r1y);
		r0x = mul_f32x4(r0x, r0x);
		r0y = mul_f32x4(r0y, r0y);
		r0z = mul_f32x4(r0z, r0z);

		// Begin power series
		// --- Power 1
		const0 = permute_f32x4<make_shuffle_mask_32<1, 1, 1, 1>()>(one_c2z_c3z_c4z);
		const1 = permute_f32x4<make_shuffle_mask_32<1, 1, 1, 1>()>(c1x_c2x_c3x_c4x);
		r1x = fmadd_f32x4(const1, r0x, const0);
		r1y = fmadd_f32x4(set1_f32x4(-24.9808039603f), r0y, set1_f32x4(60.1458091736f));
		EmuSIMD::f32x4 r1z = fmadd_f32x4(const1, r0z, const0);

		// --- Power 2
		const0 = permute_f32x4<make_shuffle_mask_32<2, 2, 2, 2>()>(c1x_c2x_c3x_c4x);
		r1x = fmadd_f32x4(r1x, r0x, const0);
		r1y = fmadd_f32x4(r1y, r0y, set1_f32x4(-85.4537887573f));
		r1z = fmadd_f32x4(r1z, r0z, const0);

		// --- Power 3
		const0 = permute_f32x4<make_shuffle_mask_32<2, 2, 2, 2>()>(one_c2z_c3z_c4z);
		r1x = fmadd_f32x4(r1x, r0x, const0);
		r1y = fmadd_f32x4(r1y, r0y, set1_f32x4(64.9393539429f));
		r1z = fmadd_f32x4(r1z, r0z, const0);

		// --- Power 4
		const0 = permute_f32x4<make_shuffle_mask_32<3, 3, 3, 3>()>(c1x_c2x_c3x_c4x);
		r1x = fmadd_f32x4(r1x, r0x, const0);
		r1y = fmadd_f32x4(r1y, r0y, set1_f32x4(-19.7392082214f));
		r1z = fmadd_f32x4(r1z, r0z, const0);

		// --- Power 5
		const0 = permute_f32x4<make_shuffle_mask_32<0, 0, 0, 0>()>(one_c2z_c3z_c4z);
		const1 = permute_f32x4<make_shuffle_mask_32<3, 3, 3, 3>()>(one_c2z_c3z_c4z);
		r1x = fmadd_f32x4(r1x, r0x, const1);
		r1y = fmadd_f32x4(r1y, r0y, const0);
		r1z = fmadd_f32x4(r1z, r0z, const1);

		// Final dot
		r2x = negate_f32x4(r2x);
		r2y = negate_f32x4(r2y);
		r2z = negate_f32x4(r2z);

		return fmadd_f32x4(r1x, r2x, fmadd_f32x4(r1y, r2y, mul_f32x4(r1z, r2z)));
		#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 tan_f32x4(EmuSIMD::f32x4_arg in_)
	{
		#if 0 && (EMU_CORE_IS_INTEL_COMPILER || EMU_CORE_IS_MSVC) && EMU_CORE_X86_X64 // Better on both Intel and AMD x86/x64 builds, so use where available
		return _mm_tan_ps(in_);
		#else
		// Alternative manual approximation using sin/cos, based on https://developer.download.nvidia.com/cg/sin.html & https://developer.download.nvidia.com/cg/cos.html impl.
		// --- Made as a unique function instead of deferring to separate cos and sin to minimise required operations
		
		// Store constants used > once in registers to allow shuffling to them
		EmuSIMD::f32x4 c1x_c2x_c3x_c4x = setr_f32x4(0.25f, 24.9808039603f, 85.4537887573f, 19.7392082214f);
		EmuSIMD::f32x4 one_c2z_c3z_c4z = setr_f32x4(1.0f, -60.1458091736f, -64.9393539429f, -1.0f);

		// Prepare for power series
		EmuSIMD::f32x4 const0 = permute_f32x4<make_shuffle_mask_32<0, 0, 0, 0>()>(c1x_c2x_c3x_c4x);
		EmuSIMD::f32x4 r1x_cos = mul_f32x4(set1_f32x4(0.159154943091f), in_);
		EmuSIMD::f32x4 r1x_sin = sub_f32x4(r1x_cos, const0); // r1.x = c1.w * in_ - c1.x

		EmuSIMD::f32x4 r1y_sin = trunc_f32x4(r1x_sin); // r1.y = frac(r1.x)
		r1y_sin = sub_f32x4(r1x_sin, r1y_sin);
		EmuSIMD::f32x4 r1y_cos = trunc_f32x4(r1x_sin);
		r1y_cos = sub_f32x4(r1x_cos, r1y_cos);

		EmuSIMD::f32x4 r2x_sin = cmplt_f32x4(r1x_sin, const0); // r2.x = r1.x < c1.x
		EmuSIMD::f32x4 r2x_cos = cmplt_f32x4(r1x_cos, const0);

		const0 = permute_f32x4<make_shuffle_mask_32<0, 0, 0, 0>()>(one_c2z_c3z_c4z);
		r2x_sin = and_f32x4(r2x_sin, const0);
		r2x_cos = and_f32x4(r2x_cos, const0);

		EmuSIMD::f32x4 r2y_sin = cmpge_f32x4(r1y_sin, set1_f32x4(-9.0f)); // r2.yz = r1.yy >= c1.yz
		EmuSIMD::f32x4 r2z_sin = cmpge_f32x4(r1y_sin, set1_f32x4(0.75f));
		r2y_sin = and_f32x4(r2y_sin, const0);
		r2z_sin = and_f32x4(r2z_sin, const0);
		EmuSIMD::f32x4 r2y_cos = cmpge_f32x4(r1y_cos, set1_f32x4(-9.0f));
		EmuSIMD::f32x4 r2z_cos = cmpge_f32x4(r1y_cos, set1_f32x4(0.75f));
		r2y_cos = and_f32x4(r2y_cos, const0);
		r2z_cos = and_f32x4(r2z_cos, const0);

		EmuSIMD::f32x4 const1 = permute_f32x4<make_shuffle_mask_32<3, 3, 3, 3>()>(one_c2z_c3z_c4z);
		r2y_sin = fmadd_f32x4(r2x_sin, const1, fmadd_f32x4(r2y_sin, const0, mul_f32x4(r2z_sin, const1))); // dot(r2, c4.zwz)
		r2y_cos = fmadd_f32x4(r2x_cos, const1, fmadd_f32x4(r2y_cos, const0, mul_f32x4(r2z_cos, const1)));

		EmuSIMD::f32x4 r0x_sin = negate_f32x4(r1y_sin);
		EmuSIMD::f32x4 r0y_sin = sub_f32x4(set1_f32x4(0.5f), r1y_sin);
		EmuSIMD::f32x4 r0z_sin = sub_f32x4(const0, r1y_sin);
		r0x_sin = mul_f32x4(r0x_sin, r0x_sin);
		r0y_sin = mul_f32x4(r0y_sin, r0y_sin);
		r0z_sin = mul_f32x4(r0z_sin, r0z_sin);
		EmuSIMD::f32x4 r0x_cos = negate_f32x4(r1y_cos);
		EmuSIMD::f32x4 r0y_cos = sub_f32x4(set1_f32x4(0.5f), r1y_cos);
		EmuSIMD::f32x4 r0z_cos = sub_f32x4(const0, r1y_cos);
		r0x_cos = mul_f32x4(r0x_cos, r0x_cos);
		r0y_cos = mul_f32x4(r0y_cos, r0y_cos);
		r0z_cos = mul_f32x4(r0z_cos, r0z_cos);

		// Begin power series
		// --- Power 1
		const0 = permute_f32x4<make_shuffle_mask_32<1, 1, 1, 1>()>(one_c2z_c3z_c4z);
		const1 = permute_f32x4<make_shuffle_mask_32<1, 1, 1, 1>()>(c1x_c2x_c3x_c4x);
		r1x_sin = fmadd_f32x4(const1, r0x_sin, const0);
		r1y_sin = fmadd_f32x4(set1_f32x4(-24.9808039603f), r0y_sin, set1_f32x4(60.1458091736f));
		EmuSIMD::f32x4 r1z_sin = fmadd_f32x4(const1, r0z_sin, const0);
		r1x_cos = fmadd_f32x4(const1, r0x_cos, const0);
		r1y_cos = fmadd_f32x4(set1_f32x4(-24.9808039603f), r0y_cos, set1_f32x4(60.1458091736f));
		EmuSIMD::f32x4 r1z_cos = fmadd_f32x4(const1, r0z_cos, const0);

		// --- Power 2
		const0 = permute_f32x4<make_shuffle_mask_32<2, 2, 2, 2>()>(c1x_c2x_c3x_c4x);
		const1 = set1_f32x4(-85.4537887573f);
		r1x_sin = fmadd_f32x4(r1x_sin, r0x_sin, const0);
		r1y_sin = fmadd_f32x4(r1y_sin, r0y_sin, const1);
		r1z_sin = fmadd_f32x4(r1z_sin, r0z_sin, const0);
		r1x_cos = fmadd_f32x4(r1x_cos, r0x_cos, const0);
		r1y_cos = fmadd_f32x4(r1y_cos, r0y_cos, const1);
		r1z_cos = fmadd_f32x4(r1z_cos, r0z_cos, const0);

		// --- Power 3
		const0 = permute_f32x4<make_shuffle_mask_32<2, 2, 2, 2>()>(one_c2z_c3z_c4z);
		const1 = set1_f32x4(64.9393539429f);
		r1x_sin = fmadd_f32x4(r1x_sin, r0x_sin, const0);
		r1y_sin = fmadd_f32x4(r1y_sin, r0y_sin, const1);
		r1z_sin = fmadd_f32x4(r1z_sin, r0z_sin, const0);
		r1x_cos = fmadd_f32x4(r1x_cos, r0x_cos, const0);
		r1y_cos = fmadd_f32x4(r1y_cos, r0y_cos, const1);
		r1z_cos = fmadd_f32x4(r1z_cos, r0z_cos, const0);

		// --- Power 4
		const0 = permute_f32x4<make_shuffle_mask_32<3, 3, 3, 3>()>(c1x_c2x_c3x_c4x);
		const1 = set1_f32x4(-19.7392082214f);
		r1x_sin = fmadd_f32x4(r1x_sin, r0x_sin, const0);
		r1y_sin = fmadd_f32x4(r1y_sin, r0y_sin, const1);
		r1z_sin = fmadd_f32x4(r1z_sin, r0z_sin, const0);
		r1x_cos = fmadd_f32x4(r1x_cos, r0x_cos, const0);
		r1y_cos = fmadd_f32x4(r1y_cos, r0y_cos, const1);
		r1z_cos = fmadd_f32x4(r1z_cos, r0z_cos, const0);

		// --- Power 5
		const0 = permute_f32x4<make_shuffle_mask_32<0, 0, 0, 0>()>(one_c2z_c3z_c4z);
		const1 = permute_f32x4<make_shuffle_mask_32<3, 3, 3, 3>()>(one_c2z_c3z_c4z);
		r1x_sin = fmadd_f32x4(r1x_sin, r0x_sin, const1);
		r1y_sin = fmadd_f32x4(r1y_sin, r0y_sin, const0);
		r1z_sin = fmadd_f32x4(r1z_sin, r0z_sin, const1);
		r1x_cos = fmadd_f32x4(r1x_cos, r0x_cos, const1);
		r1y_cos = fmadd_f32x4(r1y_cos, r0y_cos, const0);
		r1z_cos = fmadd_f32x4(r1z_cos, r0z_cos, const1);

		// Final dot - store the sins in r2x
		r2x_sin = negate_f32x4(r2x_sin);
		r2y_sin = negate_f32x4(r2y_sin);
		r2z_sin = negate_f32x4(r2z_sin);
		r2x_sin = fmadd_f32x4(r1x_sin, r2x_sin, fmadd_f32x4(r1y_sin, r2y_sin, mul_f32x4(r1z_sin, r2z_sin)));
		r2x_cos = negate_f32x4(r2x_cos);
		r2y_cos = negate_f32x4(r2y_cos);
		r2z_cos = negate_f32x4(r2z_cos);
		r2x_cos = fmadd_f32x4(r1x_cos, r2x_cos, fmadd_f32x4(r1y_cos, r2y_cos, mul_f32x4(r1z_cos, r2z_cos)));

		return div_f32x4(r2x_sin, r2x_cos);
		#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 acos_f32x4(EmuSIMD::f32x4_arg in_)
	{
		#if EMU_CORE_IS_INTEL_COMPILER && EMU_CORE_X86_X64 // Only tends to score better on Intel platforms
		return _mm_acos_ps(in_);
		#else
		// Alternative manual approximation, based on https://developer.download.nvidia.com/cg/acos.html implementation
		EmuSIMD::f32x4 in_abs = abs_f32x4(in_);
		EmuSIMD::f32x4 one = set1_f32x4(1.0f);
		EmuSIMD::f32x4 negation_mult = cmple_f32x4(in_, setzero_f32x4());
		negation_mult = and_f32x4(one, negation_mult);
		
		EmuSIMD::f32x4 result = set1_f32x4(-0.0187293f);
		result = fmadd_f32x4(result, in_abs, set1_f32x4(0.074261f));
		result = fmsub_f32x4(result, in_abs, set1_f32x4(0.2121144f));
		result = fmadd_f32x4(result, in_abs, set1_f32x4(1.5707288f));
		result = mul_f32x4(result, sqrt_f32x4(sub_f32x4(one, in_abs)));
		
		EmuSIMD::f32x4 tmp = mul_f32x4(set1_f32x4(2.0f), negation_mult);
		tmp = mul_f32x4(tmp, result);
		result = sub_f32x4(result, tmp);

		return fmadd_f32x4(negation_mult, set1_f32x4(3.14159265358979f), result);
		#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 asin_f32x4(EmuSIMD::f32x4_arg in_)
	{
		#if EMU_CORE_IS_INTEL_COMPILER && EMU_CORE_X86_X64 // Only tends to score better on Intel platforms
		return _mm_asin_ps(in_);
		#else
		// Alternative manual approximation, based on https://developer.download.nvidia.com/cg/asin.html implementation
		EmuSIMD::f32x4 in_abs = abs_f32x4(in_);
		EmuSIMD::f32x4 two = set1_f32x4(2.0f);
		EmuSIMD::f32x4 negation_mult = cmplt_f32x4(in_, setzero_f32x4());
		negation_mult = and_f32x4(two, negation_mult);

		EmuSIMD::f32x4 result = set1_f32x4(-0.0187293f);
		result = fmadd_f32x4(result, in_abs, set1_f32x4(0.074261f));
		result = fmsub_f32x4(result, in_abs, set1_f32x4(0.2121144f));
		result = fmadd_f32x4(result, in_abs, set1_f32x4(1.5707288f));

		EmuSIMD::f32x4 tmp = sub_f32x4(set1_f32x4(1.0f), in_abs);
		tmp = mul_f32x4(sqrt_f32x4(tmp), result);
		result = set1_f32x4(3.14159265358979f * 0.5f);
		result = sub_f32x4(result, tmp);

		tmp = mul_f32x4(negation_mult, result);
		return sub_f32x4(result, tmp);
		#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 atan2_f32x4(EmuSIMD::f32x4_arg y_, EmuSIMD::f32x4_arg x_)
	{
		#if EMU_CORE_IS_INTEL_COMPILER && EMU_CORE_X86_X64 // Only tends to score better on Intel platforms
		return _mm_atan2_ps(y_, x_);
		#else		
		// Alternative manual approximation, based on https://developer.download.nvidia.com/cg/atan2.html implementation

		auto abs_x = abs_f32x4(x_);
		auto abs_y = abs_f32x4(y_);
		
		EmuSIMD::f32x4 temp0 = max_f32x4(abs_x, abs_y);
		EmuSIMD::f32x4 temp1 = min_f32x4(abs_x, abs_y);
		EmuSIMD::f32x4 temp2 = div_f32x4(set1_f32x4(1.0f), temp0);
		temp2 = mul_f32x4(temp1, temp2);

		EmuSIMD::f32x4 t4 = mul_f32x4(temp2, temp2);
		temp0 = set1_f32x4(-0.013480470f);
		temp0 = fmadd_f32x4(temp0, t4, set1_f32x4(0.057477314f));
		temp0 = fmsub_f32x4(temp0, t4, set1_f32x4(0.121239071f));
		temp0 = fmadd_f32x4(temp0, t4, set1_f32x4(0.195635925f));
		temp0 = fmsub_f32x4(temp0, t4, set1_f32x4(0.332994597f));
		temp0 = fmadd_f32x4(temp0, t4, set1_f32x4(0.999995630f));
		temp2 = mul_f32x4(temp0, temp2);

		//t3 = (abs(y) > abs(x)) ? float(1.570796327) - t3 : t3;
		EmuSIMD::f32x4 cmp_mask = cmpgt_f32x4(abs_y, abs_x);
		temp0 = and_f32x4(cmp_mask, set1_f32x4(1.570796327f));
		temp0 = sub_f32x4(temp0, temp2);
		temp2 = or_f32x4(andnot_f32x4(cmp_mask, temp2), and_f32x4(cmp_mask, temp0));

		// t3 = (x < 0) ?  float(3.141592654) - t3 : t3;
		EmuSIMD::f32x4 zero = setzero_f32x4();
		cmp_mask = cmplt_f32x4(x_, zero);
		temp0 = and_f32x4(cmp_mask, set1_f32x4(3.141592654f));
		temp0 = sub_f32x4(temp0, temp2);
		temp2 = or_f32x4(andnot_f32x4(cmp_mask, temp2), and_f32x4(cmp_mask, temp0));

		//t3 = (y < 0) ? -t3 : t3;
		cmp_mask = cmplt_f32x4(y_, zero);
		temp0 = negate_f32x4(temp2);
		temp2 = or_f32x4(andnot_f32x4(cmp_mask, temp2), and_f32x4(cmp_mask, temp0));

		return temp2;
		#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f32x4 atan_f32x4(EmuSIMD::f32x4_arg in_)
	{
		#if EMU_CORE_IS_INTEL_COMPILER && EMU_CORE_X86_X64 // Only tends to score better on Intel platforms
		return _mm_atan_ps(in_);
		#else
		// Alternative manual approximation, based on https://developer.download.nvidia.com/cg/atan2.html implementation with a constant x_ argument of 1
		EmuSIMD::f32x4 one = set1_f32x4(1.0f);
		EmuSIMD::f32x4 abs_y = abs_f32x4(in_);

		//auto temp0 = _mm_max_ps(temp2, temp1);
		EmuSIMD::f32x4 cmp_mask = cmplt_f32x4(abs_y, one);
		EmuSIMD::f32x4 temp0 = or_f32x4(and_f32x4(cmp_mask, one), andnot_f32x4(cmp_mask, abs_y));
		EmuSIMD::f32x4 temp1 = or_f32x4(andnot_f32x4(cmp_mask, one), and_f32x4(cmp_mask, abs_y));
		EmuSIMD::f32x4 temp2 = div_f32x4(one, temp0);
		temp2 = mul_f32x4(temp1, temp2);

		EmuSIMD::f32x4 t4 = mul_f32x4(temp2, temp2);
		temp0 = set1_f32x4(-0.013480470f);
		temp0 = fmadd_f32x4(temp0, t4, set1_f32x4(0.057477314f));
		temp0 = fmsub_f32x4(temp0, t4, set1_f32x4(0.121239071f));
		temp0 = fmadd_f32x4(temp0, t4, set1_f32x4(0.195635925f));
		temp0 = fmsub_f32x4(temp0, t4, set1_f32x4(0.332994597f));
		temp0 = fmadd_f32x4(temp0, t4, set1_f32x4(0.999995630f));
		temp2 = mul_f32x4(temp0, temp2);

		//t3 = (abs(y) > abs(x)) ? float(1.570796327) - t3 : t3;
		cmp_mask = cmpgt_f32x4(abs_y, one);
		temp0 = and_f32x4(cmp_mask, set1_f32x4(1.570796327f));
		temp0 = sub_f32x4(temp0, temp2);
		temp2 = or_f32x4(andnot_f32x4(cmp_mask, temp2), and_f32x4(cmp_mask, temp0));

		//t3 = (y < 0) ? -t3 : t3;
		cmp_mask = cmplt_f32x4(in_, setzero_f32x4());
		temp0 = negate_f32x4(temp2);
		temp2 = or_f32x4(andnot_f32x4(cmp_mask, temp2), and_f32x4(cmp_mask, temp0));

		return temp2;
		#endif
	}
#pragma endregion
}

#endif
