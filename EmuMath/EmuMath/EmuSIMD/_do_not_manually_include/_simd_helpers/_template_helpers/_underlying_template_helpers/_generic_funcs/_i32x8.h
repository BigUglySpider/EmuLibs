#ifndef EMU_SIMD_GENERIC_FUNCS_I32X8_H_INC_
#define EMU_SIMD_GENERIC_FUNCS_I32X8_H_INC_ 1

#include "_generic_declarations/_all_generic_declarations.h"
#include "_common_generic_func_helpers.h"

namespace EmuSIMD::Funcs
{
#pragma region SETTERS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 set_i32x8
	(
		std::int32_t e0, std::int32_t e1, std::int32_t e2, std::int32_t e3, std::int32_t e4, std::int32_t e5, std::int32_t e6, std::int32_t e7
	)
	{
		return _mm256_set_epi32(e0, e1, e2, e3, e4, e5, e6, e7);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 setr_i32x8
	(
		std::int32_t e0, std::int32_t e1, std::int32_t e2, std::int32_t e3, std::int32_t e4, std::int32_t e5, std::int32_t e6, std::int32_t e7
	)
	{
		//return _mm256_setr_epi32(e0, e1, e2, e3, e4, e5, e6, e7);
		return _mm256_set_epi32(e7, e6, e5, e4, e3, e2, e1, e0);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 set1_i32x8(std::int32_t all_)
	{
		return _mm256_set1_epi32(all_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 load_i32x8(const std::int32_t* p_to_load_)
	{
		return _mm256_load_si256(reinterpret_cast<const __m256i*>(p_to_load_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 setzero_i32x8()
	{
		return _mm256_setzero_si256();
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 setmasked_i32x8(std::uint8_t bit_mask_)
	{
		constexpr std::int32_t element_mask = static_cast<std::int32_t>(0xFFFFFFFF);
		return _mm256_set_epi32
		(
			(bit_mask_ & 0x01) * element_mask,
			((bit_mask_ & 0x02) >> 1) * element_mask,
			((bit_mask_ & 0x04) >> 2) * element_mask,
			((bit_mask_ & 0x08) >> 3) * element_mask,
			((bit_mask_ & 0x10) >> 4) * element_mask,
			((bit_mask_ & 0x20) >> 5) * element_mask,
			((bit_mask_ & 0x40) >> 6) * element_mask,
			((bit_mask_ & 0x80) >> 7) * element_mask
		);
	}
#pragma endregion

#pragma region STORES
	EMU_SIMD_COMMON_FUNC_SPEC void store_i32x8(std::int32_t* p_out_, i32x8_arg a_)
	{
		_mm256_store_si256(reinterpret_cast<__m256i*>(p_out_), a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC std::int32_t get_first_i32x8(i32x8_arg a_)
	{
		return get_first_i32x4(cast_i32x8_i32x4(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC std::uint8_t movemask_i32x8(i32x8_arg a_)
	{
		return movemask_f32x8(cast_i32x8_f32x8(a_));
	}
#pragma endregion

#pragma region CASTS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 cast_f32x4_i32x8(f32x4_arg a_)
	{
		return _mm256_castsi128_si256(_mm_castps_si128(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 cast_f32x8_i32x8(f32x8_arg a_)
	{
		return _mm256_castps_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 cast_f32x16_i32x8(f32x16_arg a_)
	{
		return _mm512_castsi512_si256(_mm512_castps_si512(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 cast_f64x2_i32x8(f64x2_arg a_)
	{
		return _mm256_castsi128_si256(_mm_castpd_si128(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 cast_f64x4_i32x8(f64x4_arg a_)
	{
		return _mm256_castpd_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 cast_f64x8_i32x8(f64x8_arg a_)
	{
		return _mm512_castsi512_si256(_mm512_castpd_si512(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 cast_i8x16_i32x8(i8x16_arg a_)
	{
		return _mm256_castsi128_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 cast_i16x8_i32x8(i16x8_arg a_)
	{
		return _mm256_castsi128_si256(a_);
	}
	
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 cast_i32x4_i32x8(i32x4_arg a_)
	{
		return _mm256_castsi128_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 cast_i32x8_i32x8(i32x4_arg a_)
	{
		return _mm256_castsi128_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 cast_i64x2_i32x8(i64x2_arg a_)
	{
		return _mm256_castsi128_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 cast_i8x32_i32x8(i8x32_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 cast_i16x16_i32x8(i16x16_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 cast_i32x8_i32x8(i32x8_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 cast_i64x4_i32x8(i64x4_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 cast_i8x64_i32x8(i8x64_arg a_)
	{
		return _mm512_castsi512_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 cast_i16x32_i32x8(i16x32_arg a_)
	{
		return _mm512_castsi512_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 cast_i32x16_i32x8(i32x16_arg a_)
	{
		return _mm512_castsi512_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 cast_i64x8_i32x8(i64x8_arg a_)
	{
		return _mm512_castsi512_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 cast_u8x16_i32x8(u8x16_arg a_)
	{
		return _mm256_castsi128_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 cast_u16x8_i32x8(u16x8_arg a_)
	{
		return _mm256_castsi128_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 cast_u32x4_i32x8(u32x4_arg a_)
	{
		return _mm256_castsi128_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 cast_u64x2_i32x8(u64x2_arg a_)
	{
		return _mm256_castsi128_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 cast_u8x32_i32x8(u8x32_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 cast_u16x16_i32x8(u16x16_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 cast_u32x8_i32x8(u32x8_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 cast_u64x4_i32x8(u64x4_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 cast_u8x64_i32x8(u8x64_arg a_)
	{
		return _mm512_castsi512_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 cast_u16x32_i32x8(u16x32_arg a_)
	{
		return _mm512_castsi512_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 cast_u32x16_i32x8(u32x16_arg a_)
	{
		return _mm512_castsi512_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 cast_u64x8_i32x8(u64x8_arg a_)
	{
		return _mm512_castsi512_si256(a_);
	}
#pragma endregion

#pragma region CONVERSIONS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 cvt_f32x4_i32x8(f32x4_arg a_)
	{
		return _mm256_castsi128_si256(_mm_cvtps_epi32(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 cvt_f32x8_i32x8(f32x8_arg a_)
	{
		return _mm256_cvtps_epi32(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 cvt_f32x16_i32x8(f32x16_arg a_)
	{
		return _mm256_cvtps_epi32(_mm512_castps512_ps256(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 cvt_f64x2_i32x8(f64x2_arg a_)
	{
		return _mm256_castsi128_si256(_mm_cvtepi64_epi32(_mm_cvtpd_epi64(a_)));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 cvt_f64x4_i32x8(f64x4_arg a_)
	{
		return _mm256_castsi128_si256(_mm256_cvtpd_epi32(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 cvt_f64x8_i32x8(f64x8_arg a_)
	{
		return _mm512_cvtpd_epi32(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 cvt_i8x16_i32x8(i8x16_arg a_)
	{
		return _mm256_cvtepi8_epi32(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 cvt_i16x8_i32x8(i16x8_arg a_)
	{
		return _mm256_cvtepi16_epi32(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 cvt_i32x4_i32x8(i32x4_arg a_)
	{
		return _mm256_castsi128_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 cvt_i64x2_i32x8(i64x2_arg a_)
	{
		return _mm256_castsi128_si256(_mm_cvtepi64_epi32(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 cvt_i8x32_i32x8(i8x32_arg a_)
	{
		return _mm256_cvtepi8_epi32(_mm256_castsi256_si128(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 cvt_i16x16_i32x8(i16x16_arg a_)
	{
		return _mm256_cvtepi16_epi32(_mm256_castsi256_si128(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 cvt_i32x8_i32x8(i32x8_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 cvt_i64x4_i32x8(i64x4_arg a_)
	{
		return _mm256_castsi128_si256(_mm256_cvtepi64_epi32(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 cvt_i8x64_i32x8(i8x64_arg a_)
	{
		return _mm512_castsi512_si256(_mm512_cvtepi8_epi32(_mm512_castsi512_si128(a_)));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 cvt_i16x32_i32x8(i16x32_arg a_)
	{
		return _mm512_castsi512_si256(_mm512_cvtepi16_epi32(_mm512_castsi512_si256(a_)));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 cvt_i32x16_i32x8(i32x16_arg a_)
	{
		return _mm512_castsi512_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 cvt_i64x8_i32x8(i64x8_arg a_)
	{
		return _mm512_cvtepi64_epi32(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 cvt_u8x16_i32x8(u8x16_arg a_)
	{
		return _mm256_cvtepu8_epi32(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 cvt_u16x8_i32x8(u16x8_arg a_)
	{
		return _mm256_cvtepu16_epi32(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 cvt_u32x4_i32x8(u32x4_arg a_)
	{
		return _mm256_castsi128_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 cvt_u64x2_i32x8(u64x2_arg a_)
	{
		return _mm256_castsi128_si256(_mm_cvtepi64_epi32(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 cvt_u8x32_i32x8(u8x32_arg a_)
	{
		return _mm256_cvtepu8_epi32(_mm256_castsi256_si128(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 cvt_u16x16_i32x8(u16x16_arg a_)
	{
		return _mm256_cvtepu16_epi32(_mm256_castsi256_si128(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 cvt_u32x8_i32x8(u32x8_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 cvt_u64x4_i32x8(u64x4_arg a_)
	{
		return _mm256_castsi128_si256(_mm256_cvtepi64_epi32(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 cvt_u8x64_i32x8(u8x64_arg a_)
	{
		return _mm512_castsi512_si256(_mm512_cvtepu8_epi32(_mm512_castsi512_si128(a_)));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 cvt_u16x32_i32x8(u16x32_arg a_)
	{
		return _mm512_castsi512_si256(_mm512_cvtepu16_epi32(_mm512_castsi512_si256(a_)));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 cvt_u32x16_i32x8(u32x16_arg a_)
	{
		return _mm512_castsi512_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 cvt_u64x8_i32x8(u64x8_arg a_)
	{
		return _mm512_cvtepi64_epi32(a_);
	}
#pragma endregion

#pragma region COMPARISONS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 cmpeq_i32x8(EmuSIMD::i32x8_arg lhs_, EmuSIMD::i32x8_arg rhs_)
	{
		return _mm256_cmpeq_epi32(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 cmpneq_i32x8(EmuSIMD::i32x8_arg lhs_, EmuSIMD::i32x8_arg rhs_)
	{
		constexpr std::int32_t mask = static_cast<std::int32_t>(0xFFFFFFFF);
		return _mm256_xor_si256(set1_i32x8(mask), _mm256_cmpeq_epi32(lhs_, rhs_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 cmpgt_i32x8(EmuSIMD::i32x8_arg lhs_, EmuSIMD::i32x8_arg rhs_)
	{
		return _mm256_cmpgt_epi32(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 cmplt_i32x8(EmuSIMD::i32x8_arg lhs_, EmuSIMD::i32x8_arg rhs_)
	{
		return _mm256_cmpgt_epi32(rhs_, lhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 cmpge_i32x8(EmuSIMD::i32x8_arg lhs_, EmuSIMD::i32x8_arg rhs_)
	{
		return _mm256_or_si256(_mm256_cmpgt_epi32(lhs_, rhs_), _mm256_cmpeq_epi32(lhs_, rhs_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 cmple_i32x8(EmuSIMD::i32x8_arg lhs_, EmuSIMD::i32x8_arg rhs_)
	{
		return _mm256_or_si256(_mm256_cmpgt_epi32(rhs_, lhs_), _mm256_cmpeq_epi32(lhs_, rhs_));
	}
#pragma endregion

#pragma region MOVES
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 movehl_i32x8(EmuSIMD::i32x8_arg lhs_, EmuSIMD::i32x8_arg rhs_)
	{
		return cast_f32x8_i32x8(movehl_f32x8(cast_i32x8_f32x8(lhs_), cast_i32x8_f32x8(rhs_)));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 movelh_i32x8(EmuSIMD::i32x8_arg lhs_, EmuSIMD::i32x8_arg rhs_)
	{
		return cast_f32x8_i32x8(movelh_f32x8(cast_i32x8_f32x8(lhs_), cast_i32x8_f32x8(rhs_)));
	}
#pragma endregion

#pragma region BITWISE_ARITHMETIC
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 and_i32x8(EmuSIMD::i32x8_arg lhs_, EmuSIMD::i32x8_arg rhs_)
	{
#if EMU_SIMD_USE_256_REGISTERS
		return _mm256_and_si256(lhs_, rhs_);
#else
		using EmuSIMD::_underlying_impl::emulate_simd_basic;
		return emulate_simd_basic([](i32x4_arg a_, i32x4_arg b_) { return EmuSIMD::Funcs::and_i32x4(a_, b_); }, lhs_, rhs_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 or_i32x8(EmuSIMD::i32x8_arg lhs_, EmuSIMD::i32x8_arg rhs_)
	{
#if EMU_SIMD_USE_256_REGISTERS
		return _mm256_or_si256(lhs_, rhs_);
#else
		using EmuSIMD::_underlying_impl::emulate_simd_basic;
		return emulate_simd_basic([](i32x4_arg a_, i32x4_arg b_) { return EmuSIMD::Funcs::or_i32x4(a_, b_); }, lhs_, rhs_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 xor_i32x8(EmuSIMD::i32x8_arg lhs_, EmuSIMD::i32x8_arg rhs_)
	{
#if EMU_SIMD_USE_256_REGISTERS
		return _mm256_xor_si256(lhs_, rhs_);
#else
		using EmuSIMD::_underlying_impl::emulate_simd_basic;
		return emulate_simd_basic([](i32x4_arg a_, i32x4_arg b_) { return EmuSIMD::Funcs::xor_i32x4(a_, b_); }, lhs_, rhs_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 andnot_i32x8(EmuSIMD::i32x8_arg not_lhs_, EmuSIMD::i32x8_arg rhs_)
	{
#if EMU_SIMD_USE_256_REGISTERS
		return _mm256_andnot_si256(not_lhs_, rhs_);
#else
		using EmuSIMD::_underlying_impl::emulate_simd_basic;
		return emulate_simd_basic([](i32x4_arg a_, i32x4_arg b_) { return EmuSIMD::Funcs::andnot_i32x4(a_, b_); }, not_lhs_, rhs_);
#endif
	}

	template<std::int32_t NumShifts_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 shift_left_i32x8(EmuSIMD::i32x8_arg lhs_)
	{
		if constexpr (NumShifts_ >= 32)
		{
			return setzero_i32x8();
		}
		else
		{
#if EMU_SIMD_USE_256_REGISTERS
			return _mm256_slli_epi32(lhs_, NumShifts_);
#else
			using EmuSIMD::_underlying_impl::emulate_simd_basic;
			return emulate_simd_basic([](i32x4_arg a_) { return shift_left_i32x4<NumShifts_>(a_); }, lhs_);
#endif
		}
	}

	template<std::int32_t NumShifts_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 shift_right_arithmetic_i32x8(EmuSIMD::i32x8_arg lhs_)
	{
		if constexpr (NumShifts_ >= 32)
		{
			return setzero_i32x8();
		}
		else
		{
#if EMU_SIMD_USE_256_REGISTERS
			return _mm256_srai_epi32(lhs_, NumShifts_);
#else
			using EmuSIMD::_underlying_impl::emulate_simd_basic;
			return emulate_simd_basic([](i32x4_arg a_) { return shift_right_arithmetic_i32x4<NumShifts_>(a_); }, lhs_);
#endif
		}
	}

	template<std::int32_t NumShifts_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 shift_right_logical_i32x8(EmuSIMD::i32x8_arg lhs_)
	{
		if constexpr (NumShifts_ >= 32)
		{
			return setzero_i32x8();
		}
		else
		{
#if EMU_SIMD_USE_256_REGISTERS
			return _mm256_srli_epi32(lhs_, NumShifts_);
#else
			using EmuSIMD::_underlying_impl::emulate_simd_basic;
			return emulate_simd_basic([](i32x4_arg a_) { return shift_right_logical_i32x4<NumShifts_>(a_); }, lhs_);
#endif
		}
	}
#pragma endregion

#pragma region BLENDS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 blendv_i32x8(EmuSIMD::i32x8_arg a_, EmuSIMD::i32x8_arg b_, EmuSIMD::i32x8_arg shuffle_mask_vec_)
	{
		return cast_f32x8_i32x8
		(
			blendv_f32x8
			(
				cast_i32x8_f32x8(a_),
				cast_i32x8_f32x8(b_),
				cast_i32x8_f32x8(shuffle_mask_vec_)
			)
		);
	}
#pragma endregion

#pragma region MINMAX_FUNCS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 min_i32x8(EmuSIMD::i32x8_arg a_, EmuSIMD::i32x8_arg b_)
	{
		return _mm256_min_epi32(a_, b_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 max_i32x8(EmuSIMD::i32x8_arg a_, EmuSIMD::i32x8_arg b_)
	{
		return _mm256_max_epi32(a_, b_);
	}
#pragma endregion

#pragma region BASIC_ARITHMETIC
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 mul_all_i32x8(EmuSIMD::i32x8_arg lhs_, EmuSIMD::i32x8_arg rhs_)
	{
		return _mm256_mullo_epi32(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 negate_i32x8(EmuSIMD::i32x8_arg to_negate_)
	{
		return _mm256_sub_epi32(_mm256_setzero_si256(), to_negate_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 add_i32x8(EmuSIMD::i32x8_arg lhs_, EmuSIMD::i32x8_arg rhs_)
	{
		return _mm256_add_epi32(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 sub_i32x8(EmuSIMD::i32x8_arg lhs_, EmuSIMD::i32x8_arg rhs_)
	{
		return _mm256_sub_epi32(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 mul_i32x8(EmuSIMD::i32x8_arg lhs_, EmuSIMD::i32x8_arg rhs_)
	{
		return _mm256_mul_epi32(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 div_i32x8(EmuSIMD::i32x8_arg lhs_, EmuSIMD::i32x8_arg rhs_)
	{
#if EMU_CORE_X86_X64_SVML
		return _mm256_div_epi32(lhs_, rhs_);
#else
		EmuSIMD::f32x8 result_f32 = cvt_i32x8_f32x8(lhs_);
		result_f32 = div_f32x8(result_f32, cvt_i32x8_f32x8(rhs_));
		return cvt_f32x8_i32x8(trunc_f32x8(result_f32));
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 addsub_i32x8(EmuSIMD::i32x8_arg lhs_, EmuSIMD::i32x8_arg rhs_)
	{
		constexpr std::int32_t bytes_mask = static_cast<std::int32_t>(0xFFFFFFFF);
		const EmuSIMD::i32x8 mask = _mm256_set_epi32(bytes_mask, 0, bytes_mask, 0, bytes_mask, 0, bytes_mask, 0);
		EmuSIMD::i32x8 out = _mm256_add_epi32(lhs_, _mm256_and_si256(mask, rhs_));
		return _mm256_sub_epi32(lhs_, _mm256_andnot_si256(mask, rhs_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 subadd_i32x8(EmuSIMD::i32x8_arg lhs_, EmuSIMD::i32x8_arg rhs_)
	{
		constexpr std::int32_t bytes_mask = static_cast<std::int32_t>(0xFFFFFFFF);
		const EmuSIMD::i32x8 mask = _mm256_set_epi32(bytes_mask, 0, bytes_mask, 0, bytes_mask, 0, bytes_mask, 0);
		EmuSIMD::i32x8 out = _mm256_sub_epi32(lhs_, _mm256_and_si256(mask, rhs_));
		return _mm256_add_epi32(lhs_, _mm256_andnot_si256(mask, rhs_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 fmadd_i32x8(EmuSIMD::i32x8_arg a_, EmuSIMD::i32x8_arg b_, EmuSIMD::i32x8_arg c_)
	{
		return _mm256_add_epi32(mul_all_i32x8(a_, b_), c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 fmsub_i32x8(EmuSIMD::i32x8_arg a_, EmuSIMD::i32x8_arg b_, EmuSIMD::i32x8_arg c_)
	{
		return _mm256_sub_epi32(mul_all_i32x8(a_, b_), c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 fnmadd_i32x8(EmuSIMD::i32x8_arg a_, EmuSIMD::i32x8_arg b_, EmuSIMD::i32x8_arg c_)
	{
		return _mm256_add_epi32(mul_all_i32x8(negate_i32x8(a_), b_), c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 fnmsub_i32x8(EmuSIMD::i32x8_arg a_, EmuSIMD::i32x8_arg b_, EmuSIMD::i32x8_arg c_)
	{
		return _mm256_sub_epi32(mul_all_i32x8(negate_i32x8(a_), b_), c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 fmaddsub_i32x8(EmuSIMD::i32x8_arg a_, EmuSIMD::i32x8_arg b_, EmuSIMD::i32x8_arg c_)
	{
		return addsub_i32x8(mul_all_i32x8(a_, b_), c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 fmsubadd_i32x8(EmuSIMD::i32x8_arg a_, EmuSIMD::i32x8_arg b_, EmuSIMD::i32x8_arg c_)
	{
		return subadd_i32x8(mul_all_i32x8(a_, b_), c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 floor_i32x8(EmuSIMD::i32x8_arg to_floor_)
	{
		return to_floor_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 ceil_i32x8(EmuSIMD::i32x8_arg to_ceil_)
	{
		return to_ceil_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 trunc_i32x8(EmuSIMD::i32x8_arg to_trunc_)
	{
		return to_trunc_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 mod_i32x8(EmuSIMD::i32x8_arg lhs_, EmuSIMD::i32x8_arg rhs_)
	{
#if EMU_CORE_X86_X64_SVML
		return _mm256_rem_epi32(lhs_, rhs_);
#else
		EmuSIMD::i32x8 to_subtract = div_i32x8(lhs_, rhs_);
		to_subtract = mul_all_i32x8(to_subtract, rhs_);
		return sub_i32x8(lhs_, to_subtract);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 abs_i32x8(EmuSIMD::i32x8_arg in_)
	{
		return _mm256_abs_epi32(in_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 sqrt_i32x8(EmuSIMD::i32x8_arg in_)
	{
		return emulate_fp_i32x8([](EmuSIMD::f32x8_arg in_fp_) { return sqrt_f32x8(in_fp_); }, in_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 rsqrt_i32x8(EmuSIMD::i32x8_arg in_)
	{
		return emulate_fp_i32x8([](EmuSIMD::f32x8_arg in_fp_) { return rsqrt_f32x8(in_fp_); }, in_);
	}
#pragma endregion

#pragma region NEAR_COMPARISONS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 cmpnear_i32x8(EmuSIMD::i32x8_arg lhs_, EmuSIMD::i32x8_arg rhs_)
	{
		return cmpeq_i32x8(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 cmpnear_i32x8(EmuSIMD::i32x8_arg lhs_, EmuSIMD::i32x8_arg rhs_, EmuSIMD::i32x8_arg epsilon)
	{
		return cmple_i32x8(abs_i32x8(sub_i32x8(lhs_, rhs_)), epsilon);
	}
#pragma endregion

#pragma region TRIG
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 cos_i32x8(EmuSIMD::i32x8_arg in_)
	{
		return emulate_fp_i32x8([](EmuSIMD::f32x8_arg in_fp_) { return cos_f32x8(in_fp_); }, in_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 sin_i32x8(EmuSIMD::i32x8_arg in_)
	{
		return emulate_fp_i32x8([](EmuSIMD::f32x8_arg in_fp_) { return sin_f32x8(in_fp_); }, in_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 tan_i32x8(EmuSIMD::i32x8_arg in_)
	{
		return emulate_fp_i32x8([](EmuSIMD::f32x8_arg in_fp_) { return tan_f32x8(in_fp_); }, in_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 acos_i32x8(EmuSIMD::i32x8_arg in_)
	{
		return emulate_fp_i32x8([](EmuSIMD::f32x8_arg in_fp_) { return acos_f32x8(in_fp_); }, in_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 asin_i32x8(EmuSIMD::i32x8_arg in_)
	{
		return emulate_fp_i32x8([](EmuSIMD::f32x8_arg in_fp_) { return asin_f32x8(in_fp_); }, in_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x8 atan_i32x8(EmuSIMD::i32x8_arg in_)
	{
		return emulate_fp_i32x8([](EmuSIMD::f32x8_arg in_fp_) { return atan_f32x8(in_fp_); }, in_);
	}
#pragma endregion
}

#endif
