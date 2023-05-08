#ifndef EMU_SIMD_GENERIC_FUNCS_I32X16_H_INC_
#define EMU_SIMD_GENERIC_FUNCS_I32X16_H_INC_ 1

#include "_generic_declarations/_all_generic_declarations.h"
#include "_common_generic_func_helpers.h"

namespace EmuSIMD::Funcs
{
#pragma region SETTERS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 set_i32x16
	(
		std::int32_t e0, std::int32_t e1, std::int32_t e2, std::int32_t e3, std::int32_t e4, std::int32_t e5, std::int32_t e6, std::int32_t e7,
		std::int32_t e8, std::int32_t e9, std::int32_t e10, std::int32_t e11, std::int32_t e12, std::int32_t e13, std::int32_t e14, std::int32_t e15
	)
	{
		return _mm512_set_epi32(e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 setr_i32x16
	(
		std::int32_t e0, std::int32_t e1, std::int32_t e2, std::int32_t e3, std::int32_t e4, std::int32_t e5, std::int32_t e6, std::int32_t e7,
		std::int32_t e8, std::int32_t e9, std::int32_t e10, std::int32_t e11, std::int32_t e12, std::int32_t e13, std::int32_t e14, std::int32_t e15
	)
	{
		return _mm512_set_epi32(e15, e14, e13, e12, e11, e10, e9, e8, e7, e6, e5, e4, e3, e2, e1, e0);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 set1_i32x16(std::int32_t all_)
	{
		return _mm512_set1_epi32(all_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 load_i32x16(const std::int32_t* p_to_load_)
	{
		return _mm512_loadu_si512(p_to_load_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 aligned_load_i32x16(const std::int32_t* p_to_load_)
	{
		return _mm512_load_si512(p_to_load_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 setzero_i32x16()
	{
		return _mm512_setzero_si512();
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 setmasked_i32x16(std::uint16_t bit_mask_)
	{
		constexpr std::int32_t element_mask = static_cast<std::int32_t>(0xFFFFFFFF);
		return _mm512_set_epi32
		(
			(bit_mask_  & 0x0001)        * element_mask,
			((bit_mask_ & 0x0002) >> 1)  * element_mask,
			((bit_mask_ & 0x0004) >> 2)  * element_mask,
			((bit_mask_ & 0x0008) >> 3)  * element_mask,
			((bit_mask_ & 0x0010) >> 4)  * element_mask,
			((bit_mask_ & 0x0020) >> 5)  * element_mask,
			((bit_mask_ & 0x0040) >> 6)  * element_mask,
			((bit_mask_ & 0x0080) >> 7)  * element_mask,
			((bit_mask_ & 0x0100) >> 8)  * element_mask,
			((bit_mask_ & 0x0200) >> 9)  * element_mask,
			((bit_mask_ & 0x0400) >> 10) * element_mask,
			((bit_mask_ & 0x0800) >> 11) * element_mask,
			((bit_mask_ & 0x1000) >> 12) * element_mask,
			((bit_mask_ & 0x2000) >> 13) * element_mask,
			((bit_mask_ & 0x4000) >> 14) * element_mask,
			((bit_mask_ & 0x8000) >> 15) * element_mask
		);
	}

	template<std::uint16_t BitMask_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 setmasked_i32x16()
	{
		if constexpr(BitMask_ != 0)
		{
			return set_i32x16
			(
				std::integral_constant<std::int32_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<0,  std::int32_t>(BitMask_)>::value,
				std::integral_constant<std::int32_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<1,  std::int32_t>(BitMask_)>::value,
				std::integral_constant<std::int32_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<2,  std::int32_t>(BitMask_)>::value,
				std::integral_constant<std::int32_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<3,  std::int32_t>(BitMask_)>::value,
				std::integral_constant<std::int32_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<4,  std::int32_t>(BitMask_)>::value,
				std::integral_constant<std::int32_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<5,  std::int32_t>(BitMask_)>::value,
				std::integral_constant<std::int32_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<6,  std::int32_t>(BitMask_)>::value,
				std::integral_constant<std::int32_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<7,  std::int32_t>(BitMask_)>::value,
				std::integral_constant<std::int32_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<8,  std::int32_t>(BitMask_)>::value,
				std::integral_constant<std::int32_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<9,  std::int32_t>(BitMask_)>::value,
				std::integral_constant<std::int32_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<10, std::int32_t>(BitMask_)>::value,
				std::integral_constant<std::int32_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<11, std::int32_t>(BitMask_)>::value,
				std::integral_constant<std::int32_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<12, std::int32_t>(BitMask_)>::value,
				std::integral_constant<std::int32_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<13, std::int32_t>(BitMask_)>::value,
				std::integral_constant<std::int32_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<14, std::int32_t>(BitMask_)>::value,
				std::integral_constant<std::int32_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<15, std::int32_t>(BitMask_)>::value
			);
		}
		else
		{
			return setzero_i32x16();
		}
	}

	template<bool I0_, bool I1_, bool I2_, bool I3_, bool I4_, bool I5_, bool I6_, bool I7_, bool I8_, bool I9_, bool I10_, bool I11_, bool I12_, bool I13_, bool I14_, bool I15_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 set_index_mask_i32x16()
	{
		if constexpr(I0_ || I1_ || I2_ || I3_ || I4_ || I5_ || I6_ || I7_ || I8_ || I9_ || I10_ || I11_ || I12_ || I13_ || I14_ || I15_)
		{
			return setmasked_i32x16<EmuSIMD::Funcs::make_index_set_mask<I0_, I1_, I2_, I3_, I4_, I5_, I6_, I7_, I8_, I9_, I10_, I11_, I12_, I13_, I14_, I15_>()>();
		}
		else
		{
			return setzero_i32x16();
		}
	}

	template<bool Active_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 set_index_mask_i32x16()
	{
		if constexpr (Active_)
		{
			return setmasked_i32x16<EmuSIMD::Funcs::make_all_indices_set_mask<16, Active_>()>();
		}
		else
		{
			return setzero_i32x16();
		}
	}
#pragma endregion

#pragma region STORES
	EMU_SIMD_COMMON_FUNC_SPEC void store_i32x16(std::int32_t* p_out_, i32x16_arg a_)
	{
		_mm512_storeu_si512(reinterpret_cast<__m256i*>(p_out_), a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC void aligned_store_i32x16(std::int32_t* p_out_, i32x16_arg a_)
	{
		_mm512_store_si512(reinterpret_cast<__m256i*>(p_out_), a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC std::int32_t get_first_i32x16(i32x16_arg a_)
	{
		return get_first_i32x4(cast_i32x16_i32x4(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC std::uint16_t movemask_i32x16(i32x16_arg a_)
	{
		return static_cast<std::uint16_t>(_mm512_movepi32_mask(a_));
	}
#pragma endregion

#pragma region CASTS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cast_f32x4_i32x16(f32x4_arg a_)
	{
		return _mm512_castsi128_si512(_mm_castps_si128(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cast_f32x8_i32x16(f32x8_arg a_)
	{
		return _mm512_castsi256_si512(_mm256_castps_si256(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cast_f32x16_i32x16(f32x16_arg a_)
	{
		return _mm512_castps_si512(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cast_f64x2_i32x16(f64x2_arg a_)
	{
		return _mm512_castsi128_si512(_mm_castpd_si128(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cast_f64x4_i32x16(f64x4_arg a_)
	{
		return _mm512_castsi256_si512(_mm256_castpd_si256(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cast_f64x8_i32x16(f64x8_arg a_)
	{
		return _mm512_castpd_si512(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cast_i8x16_i32x16(i8x16_arg a_)
	{
		return _mm512_castsi128_si512(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cast_i16x8_i32x16(i16x8_arg a_)
	{
		return _mm512_castsi128_si512(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cast_i32x4_i32x16(i32x4_arg a_)
	{
		return _mm512_castsi128_si512(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cast_i64x2_i32x16(i64x2_arg a_)
	{
		return _mm512_castsi128_si512(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cast_i8x32_i32x16(i8x32_arg a_)
	{
		return _mm512_castsi256_si512(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cast_i16x16_i32x16(i16x16_arg a_)
	{
		return _mm512_castsi256_si512(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cast_i32x8_i32x16(i32x8_arg a_)
	{
		return _mm512_castsi256_si512(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cast_i64x4_i32x16(i64x4_arg a_)
	{
		return _mm512_castsi256_si512(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cast_i8x64_i32x16(i8x64_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cast_i16x32_i32x16(i16x32_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cast_i32x16_i32x16(i32x16_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cast_i64x8_i32x16(i64x8_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cast_u8x16_i32x16(u8x16_arg a_)
	{
		return _mm512_castsi128_si512(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cast_u16x8_i32x16(u16x8_arg a_)
	{
		return _mm512_castsi128_si512(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cast_u32x4_i32x16(u32x4_arg a_)
	{
		return _mm512_castsi128_si512(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cast_u64x2_i32x16(u64x2_arg a_)
	{
		return _mm512_castsi128_si512(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cast_u8x32_i32x16(u8x32_arg a_)
	{
		return _mm512_castsi256_si512(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cast_u16x16_i32x16(u16x16_arg a_)
	{
		return _mm512_castsi256_si512(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cast_u32x8_i32x16(u32x8_arg a_)
	{
		return _mm512_castsi256_si512(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cast_u64x4_i32x16(u64x4_arg a_)
	{
		return _mm512_castsi256_si512(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cast_u8x64_i32x16(u8x64_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cast_u16x32_i32x16(u16x32_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cast_u32x16_i32x16(u32x16_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cast_u64x8_i32x16(u64x8_arg a_)
	{
		return a_;
	}
#pragma endregion

#pragma region CONVERSIONS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cvt_f32x4_i32x16(f32x4_arg a_)
	{
		return _mm512_castsi128_si512(_mm_cvtps_epi32(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cvt_f32x8_i32x16(f32x8_arg a_)
	{
		return _mm512_castsi256_si512(_mm256_cvtps_epi32(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cvt_f32x16_i32x16(f32x16_arg a_)
	{
		return _mm512_cvtps_epi32(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cvt_f64x2_i32x16(f64x2_arg a_)
	{
		return _mm512_castsi128_si512(_mm_cvtpd_epi32(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cvt_f64x4_i32x16(f64x4_arg a_)
	{
		return _mm512_castsi128_si512(_mm256_cvtpd_epi32(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cvt_f64x8_i32x16(f64x8_arg a_)
	{
		return _mm512_castsi256_si512(_mm512_cvtpd_epi32(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cvt_i8x16_i32x16(i8x16_arg a_)
	{
		return _mm512_cvtepi8_epi32(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cvt_i16x8_i32x16(i16x8_arg a_)
	{
		return _mm512_castsi256_si512(_mm256_cvtepi16_epi32(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cvt_i32x4_i32x16(i32x4_arg a_)
	{
		return _mm512_castsi128_si512(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cvt_i64x2_i32x16(i64x2_arg a_)
	{
		return _mm512_castsi128_si512(_mm_cvtepi64_epi32(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cvt_i8x32_i32x16(i8x32_arg a_)
	{
		return _mm512_cvtepi8_epi32(_mm256_castsi256_si128(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cvt_i16x16_i32x16(i16x16_arg a_)
	{
		return _mm512_cvtepi16_epi32(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cvt_i32x8_i32x16(i32x8_arg a_)
	{
		return _mm512_castsi256_si512(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cvt_i64x4_i32x16(i64x4_arg a_)
	{
		return _mm512_castsi128_si512(_mm256_cvtepi64_epi32(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cvt_i8x64_i32x16(i8x64_arg a_)
	{
		return _mm512_cvtepi8_epi32(_mm512_castsi512_si128(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cvt_i16x32_i32x16(i16x32_arg a_)
	{
		return _mm512_cvtepi16_epi32(_mm512_castsi512_si256(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cvt_i32x16_i32x16(i32x16_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cvt_i64x8_i32x16(i64x8_arg a_)
	{
		return _mm512_castsi256_si512(_mm512_cvtepi64_epi32(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cvt_u8x16_i32x16(i8x16_arg a_)
	{
		return _mm512_cvtepu8_epi32(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cvt_u16x8_i32x16(i16x8_arg a_)
	{
		return _mm512_castsi256_si512(_mm256_cvtepu16_epi32(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cvt_u32x4_i32x16(i32x4_arg a_)
	{
		return _mm512_castsi128_si512(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cvt_u64x2_i32x16(i64x2_arg a_)
	{
		return _mm512_castsi128_si512(_mm_cvtepi64_epi32(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cvt_u8x32_i32x16(i8x32_arg a_)
	{
		return _mm512_cvtepu8_epi32(_mm256_castsi256_si128(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cvt_u16x16_i32x16(i16x16_arg a_)
	{
		return _mm512_cvtepu16_epi32(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cvt_u32x8_i32x16(i32x8_arg a_)
	{
		return _mm512_castsi256_si512(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cvt_u64x4_i32x16(i64x4_arg a_)
	{
		return _mm512_castsi128_si512(_mm256_cvtepi64_epi32(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cvt_u8x64_i32x16(i8x64_arg a_)
	{
		return _mm512_cvtepu8_epi32(_mm512_castsi512_si128(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cvt_u16x32_i32x16(i16x32_arg a_)
	{
		return _mm512_cvtepu16_epi32(_mm512_castsi512_si256(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cvt_u32x16_i32x16(i32x16_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cvt_u64x8_i32x16(i64x8_arg a_)
	{
		return _mm512_castsi256_si512(_mm512_cvtepi64_epi32(a_));
	}
#pragma endregion

#pragma region COMPARISONS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cmpeq_i32x16(EmuSIMD::i32x16_arg lhs_, EmuSIMD::i32x16_arg rhs_)
	{
		return setmasked_i32x16(_mm512_cmpeq_epi32_mask(lhs_, rhs_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cmpneq_i32x16(EmuSIMD::i32x16_arg lhs_, EmuSIMD::i32x16_arg rhs_)
	{
		return setmasked_i32x16(_mm512_cmpneq_epi32_mask(lhs_, rhs_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cmpgt_i32x16(EmuSIMD::i32x16_arg lhs_, EmuSIMD::i32x16_arg rhs_)
	{
		return setmasked_i32x16(_mm512_cmplt_epi32_mask(rhs_, lhs_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cmplt_i32x16(EmuSIMD::i32x16_arg lhs_, EmuSIMD::i32x16_arg rhs_)
	{
		return setmasked_i32x16(_mm512_cmplt_epi32_mask(lhs_, rhs_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cmpge_i32x16(EmuSIMD::i32x16_arg lhs_, EmuSIMD::i32x16_arg rhs_)
	{
		return setmasked_i32x16(_mm512_cmple_epi32_mask(rhs_, lhs_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cmple_i32x16(EmuSIMD::i32x16_arg lhs_, EmuSIMD::i32x16_arg rhs_)
	{
		return setmasked_i32x16(_mm512_cmple_epi32_mask(lhs_, rhs_));
	}
#pragma endregion

#pragma region MOVES
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 movehl_i32x16(EmuSIMD::i32x16_arg lhs_, EmuSIMD::i32x16_arg rhs_)
	{
		return cast_f32x16_i32x16(movehl_f32x16(cast_i32x16_f32x16(lhs_), cast_i32x16_f32x16(rhs_)));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 movelh_i32x16(EmuSIMD::i32x16_arg lhs_, EmuSIMD::i32x16_arg rhs_)
	{
		return cast_f32x16_i32x16(movelh_f32x16(cast_i32x16_f32x16(lhs_), cast_i32x16_f32x16(rhs_)));
	}
#pragma endregion

#pragma region BITWISE_ARITHMETIC
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 and_i32x16(EmuSIMD::i32x16_arg lhs_, EmuSIMD::i32x16_arg rhs_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_and_si512(lhs_, rhs_);
#else
		using EmuSIMD::_underlying_impl::emulate_simd_basic;
		return emulate_simd_basic([](i32x8_arg a_, i32x8_arg b_) { return EmuSIMD::Funcs::and_i32x8(a_, b_); }, lhs_, rhs_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 or_i32x16(EmuSIMD::i32x16_arg lhs_, EmuSIMD::i32x16_arg rhs_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_or_si512(lhs_, rhs_);
#else
		using EmuSIMD::_underlying_impl::emulate_simd_basic;
		return emulate_simd_basic([](i32x8_arg a_, i32x8_arg b_) { return EmuSIMD::Funcs::or_i32x8(a_, b_); }, lhs_, rhs_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 xor_i32x16(EmuSIMD::i32x16_arg lhs_, EmuSIMD::i32x16_arg rhs_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_xor_si512(lhs_, rhs_);
#else
		using EmuSIMD::_underlying_impl::emulate_simd_basic;
		return emulate_simd_basic([](i32x8_arg a_, i32x8_arg b_) { return EmuSIMD::Funcs::xor_i32x8(a_, b_); }, lhs_, rhs_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 andnot_i32x16(EmuSIMD::i32x16_arg not_lhs_, EmuSIMD::i32x16_arg rhs_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_andnot_si512(not_lhs_, rhs_);
#else
		using EmuSIMD::_underlying_impl::emulate_simd_basic;
		return emulate_simd_basic([](i32x8_arg a_, i32x8_arg b_) { return EmuSIMD::Funcs::andnot_i32x8(a_, b_); }, not_lhs_, rhs_);
#endif
	}

	template<std::int32_t NumShifts_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 shift_left_i32x16(EmuSIMD::i32x16_arg lhs_)
	{
		if constexpr (NumShifts_ >= 32)
		{
			return setzero_i32x16();
		}
		else
		{
#if EMU_SIMD_USE_512_REGISTERS
			return _mm512_slli_epi32(lhs_, NumShifts_);
#else
			using EmuSIMD::_underlying_impl::emulate_simd_basic;
			return emulate_simd_basic([](i32x8_arg a_) { return shift_left_i32x8<NumShifts_>(a_); }, lhs_);
#endif
		}
	}

	template<std::int32_t NumShifts_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 shift_right_arithmetic_i32x16(EmuSIMD::i32x16_arg lhs_)
	{
		if constexpr (NumShifts_ >= 32)
		{
			return setzero_i32x16();
		}
		else
		{
#if EMU_SIMD_USE_512_REGISTERS
			return _mm512_srai_epi32(lhs_, NumShifts_);
#else
			using EmuSIMD::_underlying_impl::emulate_simd_basic;
			return emulate_simd_basic([](i32x8_arg a_) { return shift_right_arithmetic_i32x8<NumShifts_>(a_); }, lhs_);
#endif
		}
	}

	template<std::int32_t NumShifts_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 shift_right_logical_i32x16(EmuSIMD::i32x16_arg lhs_)
	{
		if constexpr (NumShifts_ >= 32)
		{
			return setzero_i32x16();
		}
		else
		{
#if EMU_SIMD_USE_512_REGISTERS
			return _mm512_srli_epi32(lhs_, NumShifts_);
#else
			using EmuSIMD::_underlying_impl::emulate_simd_basic;
			return emulate_simd_basic([](i32x8_arg a_) { return shift_right_logical_i32x8<NumShifts_>(a_); }, lhs_);
#endif
		}
	}
#pragma endregion

#pragma region BLENDS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 blendv_i32x16(EmuSIMD::i32x16_arg a_, EmuSIMD::i32x16_arg b_, EmuSIMD::i32x16_arg shuffle_mask_vec_)
	{
		return cast_f32x16_i32x16
		(
			blendv_f32x16
			(
				cast_i32x16_f32x16(a_),
				cast_i32x16_f32x16(b_),
				cast_i32x16_f32x16(shuffle_mask_vec_)
			)
		);
	}
#pragma endregion

#pragma region MINMAX_FUNCS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 min_i32x16(EmuSIMD::i32x16_arg a_, EmuSIMD::i32x16_arg b_)
	{
		return _mm512_min_epi32(a_, b_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 max_i32x16(EmuSIMD::i32x16_arg a_, EmuSIMD::i32x16_arg b_)
	{
		return _mm512_max_epi32(a_, b_);
	}
#pragma endregion

#pragma region BASIC_ARITHMETIC
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 mul_all_i32x16(EmuSIMD::i32x16_arg lhs_, EmuSIMD::i32x16_arg rhs_)
	{
		return _mm512_mullo_epi32(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 negate_i32x16(EmuSIMD::i32x16_arg to_negate_)
	{
		return _mm512_sub_epi32(_mm512_setzero_si512(), to_negate_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 add_i32x16(EmuSIMD::i32x16_arg lhs_, EmuSIMD::i32x16_arg rhs_)
	{
		return _mm512_add_epi32(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 sub_i32x16(EmuSIMD::i32x16_arg lhs_, EmuSIMD::i32x16_arg rhs_)
	{
		return _mm512_sub_epi32(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 mul_i32x16(EmuSIMD::i32x16_arg lhs_, EmuSIMD::i32x16_arg rhs_)
	{
		return _mm512_mul_epi32(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 div_i32x16(EmuSIMD::i32x16_arg lhs_, EmuSIMD::i32x16_arg rhs_)
	{
#if EMU_CORE_X86_X64_SVML
		return _mm512_div_epi32(lhs_, rhs_);
#else
		EmuSIMD::f32x16 result_f32 = cvt_i32x16_f32x16(lhs_);
		result_f32 = div_f32x16(result_f32, cvt_i32x16_f32x16(rhs_));
		return cvt_f32x16_i32x16(trunc_f32x16(result_f32));
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 addsub_i32x16(EmuSIMD::i32x16_arg lhs_, EmuSIMD::i32x16_arg rhs_)
	{
		constexpr std::int32_t bytes_mask = static_cast<std::int32_t>(0xFFFFFFFF);
		const EmuSIMD::i32x16 mask = _mm512_set_epi32(bytes_mask, 0, bytes_mask, 0, bytes_mask, 0, bytes_mask, 0, bytes_mask, 0, bytes_mask, 0, bytes_mask, 0, bytes_mask, 0);
		EmuSIMD::i32x16 out = _mm512_add_epi32(lhs_, _mm512_and_si512(mask, rhs_));
		return _mm512_sub_epi32(lhs_, _mm512_andnot_si512(mask, rhs_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 subadd_i32x16(EmuSIMD::i32x16_arg lhs_, EmuSIMD::i32x16_arg rhs_)
	{
		constexpr std::int32_t bytes_mask = static_cast<std::int32_t>(0xFFFFFFFF);
		const EmuSIMD::i32x16 mask = _mm512_set_epi32(bytes_mask, 0, bytes_mask, 0, bytes_mask, 0, bytes_mask, 0, bytes_mask, 0, bytes_mask, 0, bytes_mask, 0, bytes_mask, 0);
		EmuSIMD::i32x16 out = _mm512_sub_epi32(lhs_, _mm512_and_si512(mask, rhs_));
		return _mm512_add_epi32(lhs_, _mm512_andnot_si512(mask, rhs_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 fmadd_i32x16(EmuSIMD::i32x16_arg a_, EmuSIMD::i32x16_arg b_, EmuSIMD::i32x16_arg c_)
	{
		return _mm512_add_epi32(mul_all_i32x16(a_, b_), c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 fmsub_i32x16(EmuSIMD::i32x16_arg a_, EmuSIMD::i32x16_arg b_, EmuSIMD::i32x16_arg c_)
	{
		return _mm512_sub_epi32(mul_all_i32x16(a_, b_), c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 fnmadd_i32x16(EmuSIMD::i32x16_arg a_, EmuSIMD::i32x16_arg b_, EmuSIMD::i32x16_arg c_)
	{
		return _mm512_add_epi32(mul_all_i32x16(negate_i32x16(a_), b_), c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 fnmsub_i32x16(EmuSIMD::i32x16_arg a_, EmuSIMD::i32x16_arg b_, EmuSIMD::i32x16_arg c_)
	{
		return _mm512_sub_epi32(mul_all_i32x16(negate_i32x16(a_), b_), c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 fmaddsub_i32x16(EmuSIMD::i32x16_arg a_, EmuSIMD::i32x16_arg b_, EmuSIMD::i32x16_arg c_)
	{
		return addsub_i32x16(mul_all_i32x16(a_, b_), c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 fmsubadd_i32x16(EmuSIMD::i32x16_arg a_, EmuSIMD::i32x16_arg b_, EmuSIMD::i32x16_arg c_)
	{
		return subadd_i32x16(mul_all_i32x16(a_, b_), c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 floor_i32x16(EmuSIMD::i32x16_arg to_floor_)
	{
		return to_floor_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 ceil_i32x16(EmuSIMD::i32x16_arg to_ceil_)
	{
		return to_ceil_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 trunc_i32x16(EmuSIMD::i32x16_arg to_trunc_)
	{
		return to_trunc_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 mod_i32x16(EmuSIMD::i32x16_arg lhs_, EmuSIMD::i32x16_arg rhs_)
	{
#if EMU_CORE_X86_X64_SVML
		return _mm512_rem_epi32(lhs_, rhs_);
#else
		EmuSIMD::i32x16 to_subtract = div_i32x16(lhs_, rhs_);
		to_subtract = mul_all_i32x16(to_subtract, rhs_);
		return sub_i32x16(lhs_, to_subtract);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 abs_i32x16(EmuSIMD::i32x16_arg in_)
	{
		return _mm512_abs_epi32(in_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 sqrt_i32x16(EmuSIMD::i32x16_arg in_)
	{
		return emulate_fp_i32x16([](EmuSIMD::f32x16_arg in_fp_) { return sqrt_f32x16(in_fp_); }, in_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 rsqrt_i32x16(EmuSIMD::i32x16_arg in_)
	{
		return emulate_fp_i32x16([](EmuSIMD::f32x16_arg in_fp_) { return rsqrt_f32x16(in_fp_); }, in_);
	}
#pragma endregion

#pragma region NEAR_COMPARISONS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cmpnear_i32x16(EmuSIMD::i32x16_arg lhs_, EmuSIMD::i32x16_arg rhs_)
	{
		return cmpeq_i32x16(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cmpnear_i32x16(EmuSIMD::i32x16_arg lhs_, EmuSIMD::i32x16_arg rhs_, EmuSIMD::i32x16_arg epsilon)
	{
		return cmple_i32x16(abs_i32x16(sub_i32x16(lhs_, rhs_)), epsilon);
	}
#pragma endregion

#pragma region TRIG
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 cos_i32x16(EmuSIMD::i32x16_arg in_)
	{
		return emulate_fp_i32x16([](EmuSIMD::f32x16_arg in_fp_) { return cos_f32x16(in_fp_); }, in_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 sin_i32x16(EmuSIMD::i32x16_arg in_)
	{
		return emulate_fp_i32x16([](EmuSIMD::f32x16_arg in_fp_) { return sin_f32x16(in_fp_); }, in_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 tan_i32x16(EmuSIMD::i32x16_arg in_)
	{
		return emulate_fp_i32x16([](EmuSIMD::f32x16_arg in_fp_) { return tan_f32x16(in_fp_); }, in_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 acos_i32x16(EmuSIMD::i32x16_arg in_)
	{
		return emulate_fp_i32x16([](EmuSIMD::f32x16_arg in_fp_) { return acos_f32x16(in_fp_); }, in_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 asin_i32x16(EmuSIMD::i32x16_arg in_)
	{
		return emulate_fp_i32x16([](EmuSIMD::f32x16_arg in_fp_) { return asin_f32x16(in_fp_); }, in_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x16 atan_i32x16(EmuSIMD::i32x16_arg in_)
	{
		return emulate_fp_i32x16([](EmuSIMD::f32x16_arg in_fp_) { return atan_f32x16(in_fp_); }, in_);
	}
#pragma endregion
}

#endif
