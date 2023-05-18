#ifndef EMU_SIMD_GENERIC_FUNCS_U32X16_H_INC_
#define EMU_SIMD_GENERIC_FUNCS_U32X16_H_INC_ 1

#include "_generic_declarations/_all_generic_declarations.h"
#include "_common_generic_func_helpers.h"

namespace EmuSIMD::Funcs
{
#pragma region SETTERS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 set_u32x16
	(
		std::uint32_t e0, std::uint32_t e1, std::uint32_t e2, std::uint32_t e3, std::uint32_t e4, std::uint32_t e5, std::uint32_t e6, std::uint32_t e7,
		std::uint32_t e8, std::uint32_t e9, std::uint32_t e10, std::uint32_t e11, std::uint32_t e12, std::uint32_t e13, std::uint32_t e14, std::uint32_t e15
	)
	{
		return _mm512_set_epi32(e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 setr_u32x16
	(
		std::uint32_t e0, std::uint32_t e1, std::uint32_t e2, std::uint32_t e3, std::uint32_t e4, std::uint32_t e5, std::uint32_t e6, std::uint32_t e7,
		std::uint32_t e8, std::uint32_t e9, std::uint32_t e10, std::uint32_t e11, std::uint32_t e12, std::uint32_t e13, std::uint32_t e14, std::uint32_t e15
	)
	{
		//return _mm512_setr_epi32(e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15);
		return _mm512_set_epi32(e15, e14, e13, e12, e11, e10, e9, e8, e7, e6, e5, e4, e3, e2, e1, e0);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 set1_u32x16(std::uint32_t all_)
	{
		return _mm512_set1_epi32(all_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 load_u32x16(const std::uint32_t* p_to_load_)
	{
		return _mm512_loadu_si512(p_to_load_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 aligned_load_u32x16(const std::uint32_t* p_to_load_)
	{
		return _mm512_load_si512(p_to_load_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 setzero_u32x16()
	{
		return _mm512_setzero_si512();
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 setmasked_u32x16(std::uint16_t bit_mask_)
	{
		constexpr std::uint32_t element_mask = static_cast<std::uint32_t>(0xFFFFFFFF);
		return _mm512_set_epi32
		(
			static_cast<std::uint32_t>(bit_mask_  & 0x0001)        * element_mask,
			static_cast<std::uint32_t>((bit_mask_ & 0x0002) >> 1)  * element_mask,
			static_cast<std::uint32_t>((bit_mask_ & 0x0004) >> 2)  * element_mask,
			static_cast<std::uint32_t>((bit_mask_ & 0x0008) >> 3)  * element_mask,
			static_cast<std::uint32_t>((bit_mask_ & 0x0010) >> 4)  * element_mask,
			static_cast<std::uint32_t>((bit_mask_ & 0x0020) >> 5)  * element_mask,
			static_cast<std::uint32_t>((bit_mask_ & 0x0040) >> 6)  * element_mask,
			static_cast<std::uint32_t>((bit_mask_ & 0x0080) >> 7)  * element_mask,
			static_cast<std::uint32_t>((bit_mask_ & 0x0100) >> 8)  * element_mask,
			static_cast<std::uint32_t>((bit_mask_ & 0x0200) >> 9)  * element_mask,
			static_cast<std::uint32_t>((bit_mask_ & 0x0400) >> 10) * element_mask,
			static_cast<std::uint32_t>((bit_mask_ & 0x0800) >> 11) * element_mask,
			static_cast<std::uint32_t>((bit_mask_ & 0x1000) >> 12) * element_mask,
			static_cast<std::uint32_t>((bit_mask_ & 0x2000) >> 13) * element_mask,
			static_cast<std::uint32_t>((bit_mask_ & 0x4000) >> 14) * element_mask,
			static_cast<std::uint32_t>((bit_mask_ & 0x8000) >> 15) * element_mask
		);
	}

	template<std::uint16_t BitMask_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 setmasked_u32x16()
	{
		if constexpr(BitMask_ != 0)
		{
			return set_u32x16
			(
				std::integral_constant<std::uint32_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<0,  std::uint32_t>(BitMask_)>::value,
				std::integral_constant<std::uint32_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<1,  std::uint32_t>(BitMask_)>::value,
				std::integral_constant<std::uint32_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<2,  std::uint32_t>(BitMask_)>::value,
				std::integral_constant<std::uint32_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<3,  std::uint32_t>(BitMask_)>::value,
				std::integral_constant<std::uint32_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<4,  std::uint32_t>(BitMask_)>::value,
				std::integral_constant<std::uint32_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<5,  std::uint32_t>(BitMask_)>::value,
				std::integral_constant<std::uint32_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<6,  std::uint32_t>(BitMask_)>::value,
				std::integral_constant<std::uint32_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<7,  std::uint32_t>(BitMask_)>::value,
				std::integral_constant<std::uint32_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<8,  std::uint32_t>(BitMask_)>::value,
				std::integral_constant<std::uint32_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<9,  std::uint32_t>(BitMask_)>::value,
				std::integral_constant<std::uint32_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<10, std::uint32_t>(BitMask_)>::value,
				std::integral_constant<std::uint32_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<11, std::uint32_t>(BitMask_)>::value,
				std::integral_constant<std::uint32_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<12, std::uint32_t>(BitMask_)>::value,
				std::integral_constant<std::uint32_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<13, std::uint32_t>(BitMask_)>::value,
				std::integral_constant<std::uint32_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<14, std::uint32_t>(BitMask_)>::value,
				std::integral_constant<std::uint32_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<15, std::uint32_t>(BitMask_)>::value
			);
		}
		else
		{
			return setzero_u32x16();
		}
	}

	template<bool I0_, bool I1_, bool I2_, bool I3_, bool I4_, bool I5_, bool I6_, bool I7_, bool I8_, bool I9_, bool I10_, bool I11_, bool I12_, bool I13_, bool I14_, bool I15_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 set_index_mask_u32x16()
	{
		if constexpr(I0_ || I1_ || I2_ || I3_ || I4_ || I5_ || I6_ || I7_ || I8_ || I9_ || I10_ || I11_ || I12_ || I13_ || I14_ || I15_)
		{
			return setmasked_u32x16<EmuSIMD::Funcs::make_index_set_mask<I0_, I1_, I2_, I3_, I4_, I5_, I6_, I7_, I8_, I9_, I10_, I11_, I12_, I13_, I14_, I15_>()>();
		}
		else
		{
			return setzero_u32x16();
		}
	}

	template<bool Active_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 set_index_mask_u32x16()
	{
		if constexpr (Active_)
		{
			return setmasked_u32x16<EmuSIMD::Funcs::make_all_indices_set_mask<16, Active_>()>();
		}
		else
		{
			return setzero_u32x16();
		}
	}
#pragma endregion

#pragma region STORES
	EMU_SIMD_COMMON_FUNC_SPEC void store_u32x16(std::uint32_t* p_out_, u32x16_arg a_)
	{
		_mm512_storeu_si512(reinterpret_cast<__m256i*>(p_out_), a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC void aligned_store_u32x16(std::uint32_t* p_out_, u32x16_arg a_)
	{
		_mm512_store_si512(reinterpret_cast<__m256i*>(p_out_), a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC std::uint32_t get_first_u32x16(u32x16_arg a_)
	{
		return get_first_u32x4(cast_u32x16_u32x4(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC std::uint16_t movemask_u32x16(u32x16_arg a_)
	{
		return static_cast<std::uint16_t>(_mm512_movepi32_mask(a_));
	}
#pragma endregion

#pragma region CASTS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cast_f32x4_u32x16(f32x4_arg a_)
	{
		return _mm512_castsi128_si512(_mm_castps_si128(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cast_f32x8_u32x16(f32x8_arg a_)
	{
		return _mm512_castsi256_si512(_mm256_castps_si256(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cast_f32x16_u32x16(f32x16_arg a_)
	{
		return _mm512_castps_si512(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cast_f64x2_u32x16(f64x2_arg a_)
	{
		return _mm512_castsi128_si512(_mm_castpd_si128(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cast_f64x4_u32x16(f64x4_arg a_)
	{
		return _mm512_castsi256_si512(_mm256_castpd_si256(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cast_f64x8_u32x16(f64x8_arg a_)
	{
		return _mm512_castpd_si512(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cast_i8x16_u32x16(i8x16_arg a_)
	{
		return _mm512_castsi128_si512(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cast_i16x8_u32x16(i16x8_arg a_)
	{
		return _mm512_castsi128_si512(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cast_i32x4_u32x16(i32x4_arg a_)
	{
		return _mm512_castsi128_si512(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cast_i64x2_u32x16(i64x2_arg a_)
	{
		return _mm512_castsi128_si512(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cast_i8x32_u32x16(i8x32_arg a_)
	{
		return _mm512_castsi256_si512(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cast_i16x16_u32x16(i16x16_arg a_)
	{
		return _mm512_castsi256_si512(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cast_i32x8_u32x16(i32x8_arg a_)
	{
		return _mm512_castsi256_si512(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cast_i64x4_u32x16(i64x4_arg a_)
	{
		return _mm512_castsi256_si512(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cast_i8x64_u32x16(i8x64_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cast_i16x32_u32x16(i16x32_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cast_i32x16_u32x16(i32x16_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cast_i64x8_u32x16(i64x8_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cast_u8x16_u32x16(u8x16_arg a_)
	{
		return _mm512_castsi128_si512(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cast_u16x8_u32x16(u16x8_arg a_)
	{
		return _mm512_castsi128_si512(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cast_u32x4_u32x16(u32x4_arg a_)
	{
		return _mm512_castsi128_si512(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cast_u64x2_u32x16(u64x2_arg a_)
	{
		return _mm512_castsi128_si512(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cast_u8x32_u32x16(u8x32_arg a_)
	{
		return _mm512_castsi256_si512(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cast_u16x16_u32x16(u16x16_arg a_)
	{
		return _mm512_castsi256_si512(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cast_u32x8_u32x16(u32x8_arg a_)
	{
		return _mm512_castsi256_si512(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cast_u64x4_u32x16(u64x4_arg a_)
	{
		return _mm512_castsi256_si512(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cast_u8x64_u32x16(u8x64_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cast_u16x32_u32x16(u16x32_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cast_u32x16_u32x16(u32x16_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cast_u64x8_u32x16(u64x8_arg a_)
	{
		return a_;
	}
#pragma endregion

#pragma region CONVERSIONS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cvt_f32x4_u32x16(f32x4_arg a_)
	{
		return _mm512_castsi128_si512(_mm_cvtps_epi32(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cvt_f32x8_u32x16(f32x8_arg a_)
	{
		return _mm512_castsi256_si512(_mm256_cvtps_epi32(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cvt_f32x16_u32x16(f32x16_arg a_)
	{
		return _mm512_cvtps_epi32(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cvt_f64x2_u32x16(f64x2_arg a_)
	{
		return _mm512_castsi128_si512(_mm_cvtpd_epi32(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cvt_f64x4_u32x16(f64x4_arg a_)
	{
		return _mm512_castsi128_si512(_mm256_cvtpd_epi32(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cvt_f64x8_u32x16(f64x8_arg a_)
	{
		return _mm512_castsi256_si512(_mm512_cvtpd_epi32(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cvt_i8x16_u32x16(i8x16_arg a_)
	{
		return _mm512_cvtepi8_epi32(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cvt_i16x8_u32x16(i16x8_arg a_)
	{
		return _mm512_castsi256_si512(_mm256_cvtepi16_epi32(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cvt_i32x4_u32x16(i32x4_arg a_)
	{
		return _mm512_castsi128_si512(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cvt_i64x2_u32x16(i64x2_arg a_)
	{
		return _mm512_castsi128_si512(_mm_cvtepi64_epi32(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cvt_i8x32_u32x16(i8x32_arg a_)
	{
		return _mm512_cvtepi8_epi32(_mm256_castsi256_si128(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cvt_i16x16_u32x16(i16x16_arg a_)
	{
		return _mm512_cvtepi16_epi32(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cvt_i32x8_u32x16(i32x8_arg a_)
	{
		return _mm512_castsi256_si512(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cvt_i64x4_u32x16(i64x4_arg a_)
	{
		return _mm512_castsi128_si512(_mm256_cvtepi64_epi32(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cvt_i8x64_u32x16(i8x64_arg a_)
	{
		return _mm512_cvtepi8_epi32(_mm512_castsi512_si128(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cvt_i16x32_u32x16(i16x32_arg a_)
	{
		return _mm512_cvtepi16_epi32(_mm512_castsi512_si256(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cvt_i32x16_u32x16(i32x16_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cvt_i64x8_u32x16(i64x8_arg a_)
	{
		return _mm512_castsi256_si512(_mm512_cvtepi64_epi32(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cvt_u8x16_u32x16(i8x16_arg a_)
	{
		return _mm512_cvtepi8_epi32(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cvt_u16x8_u32x16(i16x8_arg a_)
	{
		return _mm512_castsi256_si512(_mm256_cvtepi16_epi32(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cvt_u32x4_u32x16(i32x4_arg a_)
	{
		return _mm512_castsi128_si512(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cvt_u64x2_u32x16(i64x2_arg a_)
	{
		return _mm512_castsi128_si512(_mm_cvtepi64_epi32(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cvt_u8x32_u32x16(i8x32_arg a_)
	{
		return _mm512_cvtepi8_epi32(_mm256_castsi256_si128(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cvt_u16x16_u32x16(i16x16_arg a_)
	{
		return _mm512_cvtepi16_epi32(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cvt_u32x8_u32x16(i32x8_arg a_)
	{
		return _mm512_castsi256_si512(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cvt_u64x4_u32x16(i64x4_arg a_)
	{
		return _mm512_castsi128_si512(_mm256_cvtepi64_epi32(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cvt_u8x64_u32x16(i8x64_arg a_)
	{
		return _mm512_cvtepi8_epi32(_mm512_castsi512_si128(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cvt_u16x32_u32x16(i16x32_arg a_)
	{
		return _mm512_cvtepi16_epi32(_mm512_castsi512_si256(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cvt_u32x16_u32x16(i32x16_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cvt_u64x8_u32x16(i64x8_arg a_)
	{
		return _mm512_castsi256_si512(_mm512_cvtepi64_epi32(a_));
	}
#pragma endregion

#pragma region COMPARISONS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cmpeq_u32x16(EmuSIMD::u32x16_arg lhs_, EmuSIMD::u32x16_arg rhs_)
	{
		return setmasked_i8x64(_mm512_cmpeq_epu32_mask(lhs_, rhs_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cmpneq_u32x16(EmuSIMD::u32x16_arg lhs_, EmuSIMD::u32x16_arg rhs_)
	{
		return setmasked_i8x64(_mm512_cmpneq_epu32_mask(lhs_, rhs_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cmpgt_u32x16(EmuSIMD::u32x16_arg lhs_, EmuSIMD::u32x16_arg rhs_)
	{
		return setmasked_i8x64(_mm512_cmplt_epu32_mask(rhs_, lhs_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cmplt_u32x16(EmuSIMD::u32x16_arg lhs_, EmuSIMD::u32x16_arg rhs_)
	{
		return setmasked_i8x64(_mm512_cmplt_epu32_mask(lhs_, rhs_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cmpge_u32x16(EmuSIMD::u32x16_arg lhs_, EmuSIMD::u32x16_arg rhs_)
	{
		return setmasked_i8x64(_mm512_cmple_epu32_mask(rhs_, lhs_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cmple_u32x16(EmuSIMD::u32x16_arg lhs_, EmuSIMD::u32x16_arg rhs_)
	{
		return setmasked_i8x64(_mm512_cmple_epu32_mask(lhs_, rhs_));
	}
#pragma endregion

#pragma region MOVES
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 movehl_u32x16(EmuSIMD::u32x16_arg lhs_, EmuSIMD::u32x16_arg rhs_)
	{
		return cast_f32x16_u32x16(movehl_f32x16(cast_u32x16_f32x16(lhs_), cast_u32x16_f32x16(rhs_)));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 movelh_u32x16(EmuSIMD::u32x16_arg lhs_, EmuSIMD::u32x16_arg rhs_)
	{
		return cast_f32x16_u32x16(movelh_f32x16(cast_u32x16_f32x16(lhs_), cast_u32x16_f32x16(rhs_)));
	}
#pragma endregion

#pragma region BITWISE_ARITHMETIC
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 and_u32x16(EmuSIMD::u32x16_arg lhs_, EmuSIMD::u32x16_arg rhs_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_and_si512(lhs_, rhs_);
#else
		using EmuSIMD::_underlying_impl::emulate_simd_basic;
		return emulate_simd_basic([](u32x8_arg a_, u32x8_arg b_) { return EmuSIMD::Funcs::and_u32x8(a_, b_); }, lhs_, rhs_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 or_u32x16(EmuSIMD::u32x16_arg lhs_, EmuSIMD::u32x16_arg rhs_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_or_si512(lhs_, rhs_);
#else
		using EmuSIMD::_underlying_impl::emulate_simd_basic;
		return emulate_simd_basic([](u32x8_arg a_, u32x8_arg b_) { return EmuSIMD::Funcs::or_u32x8(a_, b_); }, lhs_, rhs_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 xor_u32x16(EmuSIMD::u32x16_arg lhs_, EmuSIMD::u32x16_arg rhs_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_xor_si512(lhs_, rhs_);
#else
		using EmuSIMD::_underlying_impl::emulate_simd_basic;
		return emulate_simd_basic([](u32x8_arg a_, u32x8_arg b_) { return EmuSIMD::Funcs::xor_u32x8(a_, b_); }, lhs_, rhs_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 andnot_u32x16(EmuSIMD::u32x16_arg not_lhs_, EmuSIMD::u32x16_arg rhs_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_andnot_si512(not_lhs_, rhs_);
#else
		using EmuSIMD::_underlying_impl::emulate_simd_basic;
		return emulate_simd_basic([](u32x8_arg a_, u32x8_arg b_) { return EmuSIMD::Funcs::andnot_u32x8(a_, b_); }, not_lhs_, rhs_);
#endif
	}

	template<std::int32_t NumShifts_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 shift_left_u32x16(EmuSIMD::u32x16_arg lhs_)
	{
		if constexpr (NumShifts_ >= 32)
		{
			return setzero_u32x16();
		}
		else
		{
#if EMU_SIMD_USE_512_REGISTERS
			return _mm512_slli_epi32(lhs_, NumShifts_);
#else
			using EmuSIMD::_underlying_impl::emulate_simd_basic;
			return emulate_simd_basic([](u32x8_arg a_) { return shift_left_u32x8<NumShifts_>(a_); }, lhs_);
#endif
		}
	}

	template<std::int32_t NumShifts_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 shift_right_arithmetic_u32x16(EmuSIMD::u32x16_arg lhs_)
	{
		// No sign bit, so same as logical shift
		return shift_right_logical_u32x16<NumShifts_>(lhs_);
	}

	template<std::int32_t NumShifts_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 shift_right_logical_u32x16(EmuSIMD::u32x16_arg lhs_)
	{
		if constexpr (NumShifts_ >= 32)
		{
			return setzero_u32x16();
		}
		else
		{
#if EMU_SIMD_USE_512_REGISTERS
			return _mm512_srli_epi32(lhs_, NumShifts_);
#else
			using EmuSIMD::_underlying_impl::emulate_simd_basic;
			return emulate_simd_basic([](u32x8_arg a_) { return shift_right_logical_u32x8<NumShifts_>(a_); }, lhs_);
#endif
		}
	}
#pragma endregion

#pragma region BLENDS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 blendv_u32x16(EmuSIMD::u32x16_arg a_, EmuSIMD::u32x16_arg b_, EmuSIMD::u32x16_arg shuffle_mask_vec_)
	{
		return cast_f32x16_u32x16
		(
			blendv_f32x16
			(
				cast_u32x16_f32x16(a_),
				cast_u32x16_f32x16(b_),
				cast_u32x16_f32x16(shuffle_mask_vec_)
			)
		);
	}
#pragma endregion

#pragma region MINMAX_FUNCS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 min_u32x16(EmuSIMD::u32x16_arg a_, EmuSIMD::u32x16_arg b_)
	{
		return _mm512_min_epu32(a_, b_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 horizontal_min_u32x16(EmuSIMD::u32x16_arg a_)
	{
		u32x8 min_lane = min_u32x8(cast_u32x16_u32x8(a_), extract_u32x16_lane_u32x8<1>(a_));
		min_lane = horizontal_min_u32x8(min_lane);
		return _mm512_inserti32x8(cast_u32x8_u32x16(min_lane), min_lane, 1);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 max_u32x16(EmuSIMD::u32x16_arg a_, EmuSIMD::u32x16_arg b_)
	{
		return _mm512_max_epu32(a_, b_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 horizontal_max_u32x16(EmuSIMD::u32x16_arg a_)
	{
		u32x8 max_lane = max_u32x8(cast_u32x16_u32x8(a_), extract_u32x16_lane_u32x8<1>(a_));
		max_lane = horizontal_max_u32x8(max_lane);
		return _mm512_inserti32x8(cast_u32x8_u32x16(max_lane), max_lane, 1);
	}
#pragma endregion

#pragma region BASIC_ARITHMETIC
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 mul_all_u32x16(EmuSIMD::u32x16_arg lhs_, EmuSIMD::u32x16_arg rhs_)
	{
		return _mm512_mullo_epi32(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 negate_u32x16(EmuSIMD::u32x16_arg to_negate_)
	{
		return _mm512_sub_epi32(_mm512_setzero_si512(), to_negate_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 add_u32x16(EmuSIMD::u32x16_arg lhs_, EmuSIMD::u32x16_arg rhs_)
	{
		return _mm512_add_epi32(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 sub_u32x16(EmuSIMD::u32x16_arg lhs_, EmuSIMD::u32x16_arg rhs_)
	{
		return _mm512_sub_epi32(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 div_u32x16(EmuSIMD::u32x16_arg lhs_, EmuSIMD::u32x16_arg rhs_)
	{
#if EMU_CORE_X86_X64_SVML
		return _mm512_div_epi32(lhs_, rhs_);
#else
		EmuSIMD::f32x16 result_f32 = cvt_u32x16_f32x16(lhs_);
		result_f32 = div_f32x16(result_f32, cvt_u32x16_f32x16(rhs_));
		return cvt_f32x16_u32x16(trunc_f32x16(result_f32));
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 addsub_u32x16(EmuSIMD::u32x16_arg lhs_, EmuSIMD::u32x16_arg rhs_)
	{
		constexpr std::uint32_t bytes_mask = static_cast<std::uint32_t>(0xFFFFFFFF);
		const EmuSIMD::u32x16 mask = _mm512_set_epi32(bytes_mask, 0, bytes_mask, 0, bytes_mask, 0, bytes_mask, 0, bytes_mask, 0, bytes_mask, 0, bytes_mask, 0, bytes_mask, 0);
		EmuSIMD::u32x16 out = _mm512_add_epi32(lhs_, _mm512_and_si512(mask, rhs_));
		return _mm512_sub_epi32(lhs_, _mm512_andnot_si512(mask, rhs_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 subadd_u32x16(EmuSIMD::u32x16_arg lhs_, EmuSIMD::u32x16_arg rhs_)
	{
		constexpr std::uint32_t bytes_mask = static_cast<std::uint32_t>(0xFFFFFFFF);
		const EmuSIMD::u32x16 mask = _mm512_set_epi32(bytes_mask, 0, bytes_mask, 0, bytes_mask, 0, bytes_mask, 0, bytes_mask, 0, bytes_mask, 0, bytes_mask, 0, bytes_mask, 0);
		EmuSIMD::u32x16 out = _mm512_sub_epi32(lhs_, _mm512_and_si512(mask, rhs_));
		return _mm512_add_epi32(lhs_, _mm512_andnot_si512(mask, rhs_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 fmadd_u32x16(EmuSIMD::u32x16_arg a_, EmuSIMD::u32x16_arg b_, EmuSIMD::u32x16_arg c_)
	{
		return _mm512_add_epi32(mul_all_u32x16(a_, b_), c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 fmsub_u32x16(EmuSIMD::u32x16_arg a_, EmuSIMD::u32x16_arg b_, EmuSIMD::u32x16_arg c_)
	{
		return _mm512_sub_epi32(mul_all_u32x16(a_, b_), c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 fnmadd_u32x16(EmuSIMD::u32x16_arg a_, EmuSIMD::u32x16_arg b_, EmuSIMD::u32x16_arg c_)
	{
		return _mm512_add_epi32(mul_all_u32x16(negate_u32x16(a_), b_), c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 fnmsub_u32x16(EmuSIMD::u32x16_arg a_, EmuSIMD::u32x16_arg b_, EmuSIMD::u32x16_arg c_)
	{
		return _mm512_sub_epi32(mul_all_u32x16(negate_u32x16(a_), b_), c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 fmaddsub_u32x16(EmuSIMD::u32x16_arg a_, EmuSIMD::u32x16_arg b_, EmuSIMD::u32x16_arg c_)
	{
		return addsub_u32x16(mul_all_u32x16(a_, b_), c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 fmsubadd_u32x16(EmuSIMD::u32x16_arg a_, EmuSIMD::u32x16_arg b_, EmuSIMD::u32x16_arg c_)
	{
		return subadd_u32x16(mul_all_u32x16(a_, b_), c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 floor_u32x16(EmuSIMD::u32x16_arg to_floor_)
	{
		return to_floor_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 ceil_u32x16(EmuSIMD::u32x16_arg to_ceil_)
	{
		return to_ceil_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 trunc_u32x16(EmuSIMD::u32x16_arg to_trunc_)
	{
		return to_trunc_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 mod_u32x16(EmuSIMD::u32x16_arg lhs_, EmuSIMD::u32x16_arg rhs_)
	{
#if EMU_CORE_X86_X64_SVML
		return _mm512_rem_epu32(lhs_, rhs_);
#else
		EmuSIMD::u32x16 to_subtract = div_u32x16(lhs_, rhs_);
		to_subtract = mul_all_u32x16(to_subtract, rhs_);
		return sub_u32x16(lhs_, to_subtract);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 abs_u32x16(EmuSIMD::u32x16_arg in_)
	{
		return in_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 sqrt_u32x16(EmuSIMD::u32x16_arg in_)
	{
		return emulate_fp_u32x16([](EmuSIMD::f32x16_arg in_fp_) { return sqrt_f32x16(in_fp_); }, in_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 rsqrt_u32x16(EmuSIMD::u32x16_arg in_)
	{
		return emulate_fp_u32x16([](EmuSIMD::f32x16_arg in_fp_) { return rsqrt_f32x16(in_fp_); }, in_);
	}
#pragma endregion

#pragma region NEAR_COMPARISONS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cmpnear_u32x16(EmuSIMD::u32x16_arg lhs_, EmuSIMD::u32x16_arg rhs_)
	{
		return cmpeq_u32x16(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cmpnear_u32x16(EmuSIMD::u32x16_arg lhs_, EmuSIMD::u32x16_arg rhs_, EmuSIMD::u32x16_arg epsilon)
	{
		return cmple_u32x16(sub_u32x16(lhs_, rhs_), epsilon);
	}
#pragma endregion

#pragma region TRIG
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 cos_u32x16(EmuSIMD::u32x16_arg in_)
	{
		return emulate_fp_u32x16([](EmuSIMD::f32x16_arg in_fp_) { return cos_f32x16(in_fp_); }, in_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 sin_u32x16(EmuSIMD::u32x16_arg in_)
	{
		return emulate_fp_u32x16([](EmuSIMD::f32x16_arg in_fp_) { return sin_f32x16(in_fp_); }, in_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 tan_u32x16(EmuSIMD::u32x16_arg in_)
	{
		return emulate_fp_u32x16([](EmuSIMD::f32x16_arg in_fp_) { return tan_f32x16(in_fp_); }, in_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 acos_u32x16(EmuSIMD::u32x16_arg in_)
	{
		return emulate_fp_u32x16([](EmuSIMD::f32x16_arg in_fp_) { return acos_f32x16(in_fp_); }, in_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 asin_u32x16(EmuSIMD::u32x16_arg in_)
	{
		return emulate_fp_u32x16([](EmuSIMD::f32x16_arg in_fp_) { return asin_f32x16(in_fp_); }, in_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u32x16 atan_u32x16(EmuSIMD::u32x16_arg in_)
	{
		return emulate_fp_u32x16([](EmuSIMD::f32x16_arg in_fp_) { return atan_f32x16(in_fp_); }, in_);
	}
#pragma endregion
}

#endif
