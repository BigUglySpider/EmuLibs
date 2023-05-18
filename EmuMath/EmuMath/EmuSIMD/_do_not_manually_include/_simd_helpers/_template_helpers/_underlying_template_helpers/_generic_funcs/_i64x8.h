#ifndef EMU_SIMD_GENERIC_FUNCS_I64X8_H_INC_
#define EMU_SIMD_GENERIC_FUNCS_I64X8_H_INC_ 1

#include "_generic_declarations/_all_generic_declarations.h"
#include "_common_generic_func_helpers.h"

namespace EmuSIMD::Funcs
{
#pragma region SETTERS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 set_i64x8
	(
		std::int64_t e0, std::int64_t e1, std::int64_t e2, std::int64_t e3, std::int64_t e4, std::int64_t e5, std::int64_t e6, std::int64_t e7
	)
	{
		return _mm512_set_epi64(e0, e1, e2, e3, e4, e5, e6, e7);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 setr_i64x8
	(
		std::int64_t e0, std::int64_t e1, std::int64_t e2, std::int64_t e3, std::int64_t e4, std::int64_t e5, std::int64_t e6, std::int64_t e7
	)
	{
		// return _mm512_setr_epi64(e0, e1, e2, e3, e4, e5, e6, e7);
		return _mm512_set_epi64(e7, e6, e5, e4, e3, e2, e1, e0);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 set1_i64x8(std::int64_t all_)
	{
		return _mm512_set1_epi64(all_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 load_i64x8(const std::int64_t* p_to_load_)
	{
		return _mm512_loadu_si512(p_to_load_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 aligned_load_i64x8(const std::int64_t* p_to_load_)
	{
		return _mm512_load_si512(p_to_load_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 setzero_i64x8()
	{
		return _mm512_setzero_si512();
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 setmasked_i64x8(std::uint8_t bit_mask_)
	{
		constexpr std::int64_t element_mask = static_cast<std::int64_t>(0xFFFFFFFFFFFFFFFF);
		return _mm512_set_epi64
		(
			(bit_mask_  & 0x01)       * element_mask,
			((bit_mask_ & 0x02) >> 1) * element_mask,
			((bit_mask_ & 0x04) >> 2) * element_mask,
			((bit_mask_ & 0x08) >> 3) * element_mask,
			((bit_mask_ & 0x10) >> 4) * element_mask,
			((bit_mask_ & 0x20) >> 5) * element_mask,
			((bit_mask_ & 0x40) >> 6) * element_mask,
			((bit_mask_ & 0x80) >> 7) * element_mask
		);
	}

	template<std::uint8_t BitMask_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 setmasked_i64x8()
	{
		if constexpr(BitMask_ != 0)
		{
			return set_i64x8
			(
				std::integral_constant<std::int64_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<0,  std::int64_t>(BitMask_)>::value,
				std::integral_constant<std::int64_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<1,  std::int64_t>(BitMask_)>::value,
				std::integral_constant<std::int64_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<2,  std::int64_t>(BitMask_)>::value,
				std::integral_constant<std::int64_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<3,  std::int64_t>(BitMask_)>::value,
				std::integral_constant<std::int64_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<4,  std::int64_t>(BitMask_)>::value,
				std::integral_constant<std::int64_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<5,  std::int64_t>(BitMask_)>::value,
				std::integral_constant<std::int64_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<6,  std::int64_t>(BitMask_)>::value,
				std::integral_constant<std::int64_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<7,  std::int64_t>(BitMask_)>::value
			);
		}
		else
		{
			return setzero_i64x8();
		}
	}

	template<bool I0_, bool I1_, bool I2_, bool I3_, bool I4_, bool I5_, bool I6_, bool I7_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 set_index_mask_i64x8()
	{
		if constexpr(I0_ || I1_ || I2_ || I3_ || I4_ || I5_ || I6_ || I7_)
		{
			return setmasked_i64x8<EmuSIMD::Funcs::make_index_set_mask<I0_, I1_, I2_, I3_, I4_, I5_, I6_, I7_>()>();
		}
		else
		{
			return setzero_i64x8();
		}
	}

	template<bool Active_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 set_index_mask_i64x8()
	{
		if constexpr (Active_)
		{
			return setmasked_i64x8<EmuSIMD::Funcs::make_all_indices_set_mask<8, Active_>()>();
		}
		else
		{
			return setzero_i64x8();
		}
	}
#pragma endregion

#pragma region STORES
	EMU_SIMD_COMMON_FUNC_SPEC void store_i64x8(std::int64_t* p_out_, i64x8_arg a_)
	{
		_mm512_storeu_si512(reinterpret_cast<__m256i*>(p_out_), a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC void aligned_store_i64x8(std::int64_t* p_out_, i64x8_arg a_)
	{
		_mm512_store_si512(reinterpret_cast<__m256i*>(p_out_), a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC std::int64_t get_first_i64x8(i64x8_arg a_)
	{
		return get_first_i64x2(cast_i64x8_i64x2(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC std::uint8_t movemask_i64x8(i64x8_arg a_)
	{
		return static_cast<std::uint8_t>(_mm512_movepi64_mask(a_));
	}
#pragma endregion

#pragma region CASTS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 cast_f32x4_i64x8(f32x4_arg a_)
	{
		return _mm512_castsi128_si512(_mm_castps_si128(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 cast_f32x8_i64x8(f32x8_arg a_)
	{
		return _mm512_castsi256_si512(_mm256_castps_si256(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 cast_f32x16_i64x8(f32x16_arg a_)
	{
		return _mm512_castps_si512(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 cast_f64x2_i64x8(f64x2_arg a_)
	{
		return _mm512_castsi128_si512(_mm_castpd_si128(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 cast_f64x4_i64x8(f64x4_arg a_)
	{
		return _mm512_castsi256_si512(_mm256_castpd_si256(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 cast_f64x8_i64x8(f64x8_arg a_)
	{
		return _mm512_castpd_si512(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 cast_i8x16_i64x8(i8x16_arg a_)
	{
		return _mm512_castsi128_si512(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 cast_i16x8_i64x8(i16x8_arg a_)
	{
		return _mm512_castsi128_si512(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 cast_i32x4_i64x8(i32x4_arg a_)
	{
		return _mm512_castsi128_si512(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 cast_i64x2_i64x8(i64x2_arg a_)
	{
		return _mm512_castsi128_si512(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 cast_i8x32_i64x8(i8x32_arg a_)
	{
		return _mm512_castsi256_si512(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 cast_i16x16_i64x8(i16x16_arg a_)
	{
		return _mm512_castsi256_si512(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 cast_i32x8_i64x8(i32x8_arg a_)
	{
		return _mm512_castsi256_si512(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 cast_i64x4_i64x8(i64x4_arg a_)
	{
		return _mm512_castsi256_si512(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 cast_i8x64_i64x8(i8x64_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 cast_i16x32_i64x8(i16x32_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 cast_i32x16_i64x8(i32x16_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 cast_i64x8_i64x8(i64x8_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 cast_u8x16_i64x8(u8x16_arg a_)
	{
		return _mm512_castsi128_si512(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 cast_u16x8_i64x8(u16x8_arg a_)
	{
		return _mm512_castsi128_si512(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 cast_u32x4_i64x8(u32x4_arg a_)
	{
		return _mm512_castsi128_si512(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 cast_u64x2_i64x8(u64x2_arg a_)
	{
		return _mm512_castsi128_si512(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 cast_u8x32_i64x8(u8x32_arg a_)
	{
		return _mm512_castsi256_si512(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 cast_u16x16_i64x8(u16x16_arg a_)
	{
		return _mm512_castsi256_si512(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 cast_u32x8_i64x8(u32x8_arg a_)
	{
		return _mm512_castsi256_si512(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 cast_u64x4_i64x8(u64x4_arg a_)
	{
		return _mm512_castsi256_si512(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 cast_u8x64_i64x8(u8x64_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 cast_u16x32_i64x8(u16x32_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 cast_u32x16_i64x8(u32x16_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 cast_u64x8_i64x8(u64x8_arg a_)
	{
		return a_;
	}
#pragma endregion

#pragma region CONVERSIONS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 cvt_f32x4_i64x8(f32x4_arg a_)
	{
		return _mm512_castsi128_si512(_mm_cvtps_epi64(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 cvt_f32x8_i64x8(f32x8_arg a_)
	{
		return _mm512_cvtps_epi64(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 cvt_f32x16_i64x8(f32x16_arg a_)
	{
		return _mm512_cvtps_epi64(_mm512_castps512_ps256(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 cvt_f64x2_i64x8(f64x2_arg a_)
	{
		return _mm512_castsi128_si512(_mm_cvtpd_epi64(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 cvt_f64x4_i64x8(f64x4_arg a_)
	{
		return _mm512_castsi256_si512(_mm256_cvtpd_epi64(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 cvt_f64x8_i64x8(f64x8_arg a_)
	{
		return _mm512_cvtpd_epi64(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 cvt_i8x16_i64x8(i8x16_arg a_)
	{
		return _mm512_cvtepi8_epi64(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 cvt_i16x8_i64x8(i16x8_arg a_)
	{
		return _mm512_cvtepi16_epi64(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 cvt_i32x4_i64x8(i32x4_arg a_)
	{
		return _mm512_castsi256_si512(_mm256_cvtepi32_epi64(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 cvt_i64x2_i64x8(i64x2_arg a_)
	{
		return _mm512_castsi128_si512(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 cvt_i8x32_i64x8(i8x32_arg a_)
	{
		return _mm512_cvtepi8_epi64(_mm256_castsi256_si128(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 cvt_i16x16_i64x8(i16x16_arg a_)
	{
		return _mm512_cvtepi16_epi64(_mm256_castsi256_si128(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 cvt_i32x8_i64x8(i32x8_arg a_)
	{
		return _mm512_castsi256_si512(_mm256_cvtepi32_epi64(_mm256_castsi256_si128(a_)));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 cvt_i64x4_i64x8(i64x4_arg a_)
	{
		return _mm512_castsi256_si512(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 cvt_i8x64_i64x8(i8x64_arg a_)
	{
		return _mm512_cvtepi8_epi64(_mm512_castsi512_si128(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 cvt_i16x32_i64x8(i16x32_arg a_)
	{
		return _mm512_cvtepi16_epi64(_mm512_castsi512_si128(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 cvt_i32x16_i64x8(i32x16_arg a_)
	{
		return _mm512_cvtepi32_epi64(_mm512_castsi512_si256(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 cvt_i64x8_i64x8(i64x8_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 cvt_u8x16_i64x8(u8x16_arg a_)
	{
		return _mm512_cvtepu8_epi64(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 cvt_u16x8_i64x8(u16x8_arg a_)
	{
		return _mm512_cvtepu16_epi64(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 cvt_u32x4_i64x8(u32x4_arg a_)
	{
		return _mm512_castsi256_si512(_mm256_cvtepu32_epi64(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 cvt_u64x2_i64x8(u64x2_arg a_)
	{
		return _mm512_castsi128_si512(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 cvt_u8x32_i64x8(u8x32_arg a_)
	{
		return _mm512_cvtepu8_epi64(_mm256_castsi256_si128(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 cvt_u16x16_i64x8(u16x16_arg a_)
	{
		return _mm512_cvtepu16_epi64(_mm256_castsi256_si128(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 cvt_u32x8_i64x8(u32x8_arg a_)
	{
		return _mm512_castsi256_si512(_mm256_cvtepu32_epi64(_mm256_castsi256_si128(a_)));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 cvt_u64x4_i64x8(u64x4_arg a_)
	{
		return _mm512_castsi256_si512(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 cvt_u8x64_i64x8(u8x64_arg a_)
	{
		return _mm512_cvtepu8_epi64(_mm512_castsi512_si128(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 cvt_u16x32_i64x8(u16x32_arg a_)
	{
		return _mm512_cvtepu16_epi64(_mm512_castsi512_si128(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 cvt_u32x16_i64x8(u32x16_arg a_)
	{
		return _mm512_cvtepu32_epi64(_mm512_castsi512_si256(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 cvt_u64x8_i64x8(u64x8_arg a_)
	{
		return a_;
	}
#pragma endregion

#pragma region COMPARISONS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 cmpeq_i64x8(EmuSIMD::i64x8_arg lhs_, EmuSIMD::i64x8_arg rhs_)
	{
		return setmasked_i64x8(_mm512_cmpeq_epi64_mask(lhs_, rhs_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 cmpneq_i64x8(EmuSIMD::i64x8_arg lhs_, EmuSIMD::i64x8_arg rhs_)
	{
		return setmasked_i64x8(_mm512_cmpneq_epi64_mask(lhs_, rhs_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 cmpgt_i64x8(EmuSIMD::i64x8_arg lhs_, EmuSIMD::i64x8_arg rhs_)
	{
		return setmasked_i64x8(_mm512_cmplt_epi64_mask(rhs_, lhs_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 cmplt_i64x8(EmuSIMD::i64x8_arg lhs_, EmuSIMD::i64x8_arg rhs_)
	{
		return setmasked_i64x8(_mm512_cmplt_epi64_mask(lhs_, rhs_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 cmpge_i64x8(EmuSIMD::i64x8_arg lhs_, EmuSIMD::i64x8_arg rhs_)
	{
		return setmasked_i64x8(_mm512_cmple_epi64_mask(rhs_, lhs_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 cmple_i64x8(EmuSIMD::i64x8_arg lhs_, EmuSIMD::i64x8_arg rhs_)
	{
		return setmasked_i64x8(_mm512_cmple_epi64_mask(lhs_, rhs_));
	}
#pragma endregion

#pragma region MOVES
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 movehl_i64x8(EmuSIMD::i64x8_arg lhs_, EmuSIMD::i64x8_arg rhs_)
	{
		return cast_f64x8_i64x8(movehl_f64x8(cast_i64x8_f64x8(lhs_), cast_i64x8_f64x8(rhs_)));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 movelh_i64x8(EmuSIMD::i64x8_arg lhs_, EmuSIMD::i64x8_arg rhs_)
	{
		return cast_f64x8_i64x8(movelh_f64x8(cast_i64x8_f64x8(lhs_), cast_i64x8_f64x8(rhs_)));
	}
#pragma endregion

#pragma region BITWISE_ARITHMETIC
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 and_i64x8(EmuSIMD::i64x8_arg lhs_, EmuSIMD::i64x8_arg rhs_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_and_si512(lhs_, rhs_);
#else
		using EmuSIMD::_underlying_impl::emulate_simd_basic;
		return emulate_simd_basic([](i64x4_arg a_, i64x4_arg b_) { return EmuSIMD::Funcs::and_i64x4(a_, b_); }, lhs_, rhs_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 or_i64x8(EmuSIMD::i64x8_arg lhs_, EmuSIMD::i64x8_arg rhs_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_or_si512(lhs_, rhs_);
#else
		using EmuSIMD::_underlying_impl::emulate_simd_basic;
		return emulate_simd_basic([](i64x4_arg a_, i64x4_arg b_) { return EmuSIMD::Funcs::or_i64x4(a_, b_); }, lhs_, rhs_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 xor_i64x8(EmuSIMD::i64x8_arg lhs_, EmuSIMD::i64x8_arg rhs_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_xor_si512(lhs_, rhs_);
#else
		using EmuSIMD::_underlying_impl::emulate_simd_basic;
		return emulate_simd_basic([](i64x4_arg a_, i64x4_arg b_) { return EmuSIMD::Funcs::xor_i64x4(a_, b_); }, lhs_, rhs_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 andnot_i64x8(EmuSIMD::i64x8_arg not_lhs_, EmuSIMD::i64x8_arg rhs_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_andnot_si512(not_lhs_, rhs_);
#else
		using EmuSIMD::_underlying_impl::emulate_simd_basic;
		return emulate_simd_basic([](i64x4_arg a_, i64x4_arg b_) { return EmuSIMD::Funcs::andnot_i64x4(a_, b_); }, not_lhs_, rhs_);
#endif
	}

	template<std::int32_t NumShifts_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 shift_left_i64x8(EmuSIMD::i64x8_arg lhs_)
	{
		if constexpr (NumShifts_ >= 64)
		{
			return setzero_i64x8();
		}
		else
		{
#if EMU_SIMD_USE_512_REGISTERS
			return _mm512_slli_epi64(lhs_, NumShifts_);
#else
			using EmuSIMD::_underlying_impl::emulate_simd_basic;
			return emulate_simd_basic([](i64x4_arg a_) { return shift_left_i64x4<NumShifts_>(a_); }, lhs_);
#endif
		}
	}

	template<std::int32_t NumShifts_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 shift_right_arithmetic_i64x8(EmuSIMD::i64x8_arg lhs_)
	{
		if constexpr (NumShifts_ >= 64)
		{
			return setzero_i64x8();
		}
		else
		{
#if EMU_SIMD_USE_512_REGISTERS
			return _mm512_srai_epi64(lhs_, NumShifts_);
#else
			using EmuSIMD::_underlying_impl::emulate_simd_basic;
			return emulate_simd_basic([](i64x4_arg a_) { return shift_right_arithmetic_i64x4<NumShifts_>(a_); }, lhs_);
#endif
		}
	}

	template<std::int32_t NumShifts_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 shift_right_logical_i64x8(EmuSIMD::i64x8_arg lhs_)
	{
		if constexpr (NumShifts_ >= 64)
		{
			return setzero_i64x8();
		}
		else
		{
#if EMU_SIMD_USE_512_REGISTERS
			return _mm512_srli_epi64(lhs_, NumShifts_);
#else
			using EmuSIMD::_underlying_impl::emulate_simd_basic;
			return emulate_simd_basic([](i64x4_arg a_) { return shift_right_logical_i64x4<NumShifts_>(a_); }, lhs_);
#endif
		}
	}
#pragma endregion

#pragma region BLENDS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 blendv_i64x8(EmuSIMD::i64x8_arg a_, EmuSIMD::i64x8_arg b_, EmuSIMD::i64x8_arg shuffle_mask_vec_)
	{
		return cast_f32x16_i64x8
		(
			blendv_f32x16
			(
				cast_i64x8_f32x16(a_),
				cast_i64x8_f32x16(b_),
				cast_i64x8_f32x16(shuffle_mask_vec_)
			)
		);
	}
#pragma endregion

#pragma region MINMAX_FUNCS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 min_i64x8(EmuSIMD::i64x8_arg a_, EmuSIMD::i64x8_arg b_)
	{
		return _mm512_min_epi64(a_, b_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 horizontal_min_i64x8(EmuSIMD::i64x8_arg a_)
	{
		i64x4 min_lane = min_i64x4(cast_i64x8_i64x4(a_), extract_i64x8_lane_i64x4<1>(a_));
		min_lane = horizontal_min_i64x4(min_lane);
		return _mm512_inserti64x4(cast_i64x4_i64x8(min_lane), min_lane, 1);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 max_i64x8(EmuSIMD::i64x8_arg a_, EmuSIMD::i64x8_arg b_)
	{
		return _mm512_max_epi64(a_, b_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 horizontal_max_i64x8(EmuSIMD::i64x8_arg a_)
	{
		i64x4 max_lane = max_i64x4(cast_i64x8_i64x4(a_), extract_i64x8_lane_i64x4<1>(a_));
		max_lane = horizontal_max_i64x4(max_lane);
		return _mm512_inserti64x4(cast_i64x4_i64x8(max_lane), max_lane, 1);
	}
#pragma endregion

#pragma region BASIC_ARITHMETIC
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 mul_all_i64x8(EmuSIMD::i64x8_arg lhs_, EmuSIMD::i64x8_arg rhs_)
	{
		return _mm512_mullo_epi64(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 negate_i64x8(EmuSIMD::i64x8_arg to_negate_)
	{
		return _mm512_sub_epi64(_mm512_setzero_si512(), to_negate_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 add_i64x8(EmuSIMD::i64x8_arg lhs_, EmuSIMD::i64x8_arg rhs_)
	{
		return _mm512_add_epi64(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 sub_i64x8(EmuSIMD::i64x8_arg lhs_, EmuSIMD::i64x8_arg rhs_)
	{
		return _mm512_sub_epi64(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 div_i64x8(EmuSIMD::i64x8_arg lhs_, EmuSIMD::i64x8_arg rhs_)
	{
#if EMU_CORE_X86_X64_SVML
		return _mm512_div_epi64(lhs_, rhs_);
#else
		EmuSIMD::f64x8 result_f64 = cvt_i64x8_f64x8(lhs_);
		result_f64 = div_f64x8(result_f64, cvt_i64x8_f64x8(rhs_));
		return cvt_f64x8_i64x8(trunc_f64x8(result_f64));
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 addsub_i64x8(EmuSIMD::i64x8_arg lhs_, EmuSIMD::i64x8_arg rhs_)
	{
		constexpr std::int64_t bytes_mask = static_cast<std::int64_t>(0xFFFFFFFFFFFFFFFF);
		const EmuSIMD::i64x8 mask = _mm512_set_epi64(bytes_mask, 0, bytes_mask, 0, bytes_mask, 0, bytes_mask, 0);
		EmuSIMD::i64x8 out = _mm512_add_epi64(lhs_, _mm512_and_si512(mask, rhs_));
		return _mm512_sub_epi64(lhs_, _mm512_andnot_si512(mask, rhs_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 subadd_i64x8(EmuSIMD::i64x8_arg lhs_, EmuSIMD::i64x8_arg rhs_)
	{
		constexpr std::int64_t bytes_mask = static_cast<std::int64_t>(0xFFFFFFFFFFFFFFFF);
		const EmuSIMD::i64x8 mask = _mm512_set_epi64(bytes_mask, 0, bytes_mask, 0, bytes_mask, 0, bytes_mask, 0);
		EmuSIMD::i64x8 out = _mm512_sub_epi64(lhs_, _mm512_and_si512(mask, rhs_));
		return _mm512_add_epi64(lhs_, _mm512_andnot_si512(mask, rhs_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 fmadd_i64x8(EmuSIMD::i64x8_arg a_, EmuSIMD::i64x8_arg b_, EmuSIMD::i64x8_arg c_)
	{
		return _mm512_add_epi64(mul_all_i64x8(a_, b_), c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 fmsub_i64x8(EmuSIMD::i64x8_arg a_, EmuSIMD::i64x8_arg b_, EmuSIMD::i64x8_arg c_)
	{
		return _mm512_sub_epi64(mul_all_i64x8(a_, b_), c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 fnmadd_i64x8(EmuSIMD::i64x8_arg a_, EmuSIMD::i64x8_arg b_, EmuSIMD::i64x8_arg c_)
	{
		return _mm512_add_epi64(mul_all_i64x8(negate_i64x8(a_), b_), c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 fnmsub_i64x8(EmuSIMD::i64x8_arg a_, EmuSIMD::i64x8_arg b_, EmuSIMD::i64x8_arg c_)
	{
		return _mm512_sub_epi64(mul_all_i64x8(negate_i64x8(a_), b_), c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 fmaddsub_i64x8(EmuSIMD::i64x8_arg a_, EmuSIMD::i64x8_arg b_, EmuSIMD::i64x8_arg c_)
	{
		return addsub_i64x8(mul_all_i64x8(a_, b_), c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 fmsubadd_i64x8(EmuSIMD::i64x8_arg a_, EmuSIMD::i64x8_arg b_, EmuSIMD::i64x8_arg c_)
	{
		return subadd_i64x8(mul_all_i64x8(a_, b_), c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 floor_i64x8(EmuSIMD::i64x8_arg to_floor_)
	{
		return to_floor_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 ceil_i64x8(EmuSIMD::i64x8_arg to_ceil_)
	{
		return to_ceil_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 trunc_i64x8(EmuSIMD::i64x8_arg to_trunc_)
	{
		return to_trunc_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 mod_i64x8(EmuSIMD::i64x8_arg lhs_, EmuSIMD::i64x8_arg rhs_)
	{
#if EMU_CORE_X86_X64_SVML
		return _mm512_rem_epi64(lhs_, rhs_);
#else
		EmuSIMD::i64x8 to_subtract = div_i64x8(lhs_, rhs_);
		to_subtract = mul_all_i64x8(to_subtract, rhs_);
		return sub_i64x8(lhs_, to_subtract);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 abs_i64x8(EmuSIMD::i64x8_arg in_)
	{
		return _mm512_abs_epi64(in_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 sqrt_i64x8(EmuSIMD::i64x8_arg in_)
	{
		return emulate_fp_i64x8([](EmuSIMD::f64x8_arg in_fp_) { return sqrt_f64x8(in_fp_); }, in_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 rsqrt_i64x8(EmuSIMD::i64x8_arg in_)
	{
		return emulate_fp_i64x8([](EmuSIMD::f64x8_arg in_fp_) { return rsqrt_f64x8(in_fp_); }, in_);
	}
#pragma endregion

#pragma region NEAR_COMPARISONS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 cmpnear_i64x8(EmuSIMD::i64x8_arg lhs_, EmuSIMD::i64x8_arg rhs_)
	{
		return cmpeq_i64x8(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 cmpnear_i64x8(EmuSIMD::i64x8_arg lhs_, EmuSIMD::i64x8_arg rhs_, EmuSIMD::i64x8_arg epsilon)
	{
		return cmple_i64x8(abs_i64x8(sub_i64x8(lhs_, rhs_)), epsilon);
	}
#pragma endregion

#pragma region TRIG
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 cos_i64x8(EmuSIMD::i64x8_arg in_)
	{
		return emulate_fp_i64x8([](EmuSIMD::f64x8_arg in_fp_) { return cos_f64x8(in_fp_); }, in_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 sin_i64x8(EmuSIMD::i64x8_arg in_)
	{
		return emulate_fp_i64x8([](EmuSIMD::f64x8_arg in_fp_) { return sin_f64x8(in_fp_); }, in_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 tan_i64x8(EmuSIMD::i64x8_arg in_)
	{
		return emulate_fp_i64x8([](EmuSIMD::f64x8_arg in_fp_) { return tan_f64x8(in_fp_); }, in_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 acos_i64x8(EmuSIMD::i64x8_arg in_)
	{
		return emulate_fp_i64x8([](EmuSIMD::f64x8_arg in_fp_) { return acos_f64x8(in_fp_); }, in_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 asin_i64x8(EmuSIMD::i64x8_arg in_)
	{
		return emulate_fp_i64x8([](EmuSIMD::f64x8_arg in_fp_) { return asin_f64x8(in_fp_); }, in_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x8 atan_i64x8(EmuSIMD::i64x8_arg in_)
	{
		return emulate_fp_i64x8([](EmuSIMD::f64x8_arg in_fp_) { return atan_f64x8(in_fp_); }, in_);
	}
#pragma endregion
}

#endif
