#ifndef EMU_SIMD_GENERIC_FUNCS_U8X16_H_INC_
#define EMU_SIMD_GENERIC_FUNCS_U8X16_H_INC_ 1

#include "_generic_declarations/_all_generic_declarations.h"
#include "_common_generic_func_helpers.h"

namespace EmuSIMD::Funcs
{
#pragma region SETTERS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 set_u8x16
	(
		std::uint8_t e0, std::uint8_t e1, std::uint8_t e2, std::uint8_t e3, std::uint8_t e4, std::uint8_t e5, std::uint8_t e6, std::uint8_t e7,
		std::uint8_t e8, std::uint8_t e9, std::uint8_t e10, std::uint8_t e11, std::uint8_t e12, std::uint8_t e13, std::uint8_t e14, std::uint8_t e15
	)
	{
		return _mm_set_epi8(e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 setr_u8x16
	(
		std::uint8_t e0, std::uint8_t e1, std::uint8_t e2, std::uint8_t e3, std::uint8_t e4, std::uint8_t e5, std::uint8_t e6, std::uint8_t e7,
		std::uint8_t e8, std::uint8_t e9, std::uint8_t e10, std::uint8_t e11, std::uint8_t e12, std::uint8_t e13, std::uint8_t e14, std::uint8_t e15
	)
	{
		//return _mm_setr_epi8(e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15);
		return _mm_set_epi8(e15, e14, e13, e12, e11, e10, e9, e8, e7, e6, e5, e4, e3, e2, e1, e0);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 set1_u8x16(std::uint8_t all_)
	{
		return _mm_set1_epi8(all_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 load_u8x16(const std::uint8_t* p_to_load_)
	{
		return _mm_loadu_si128(reinterpret_cast<const __m128i*>(p_to_load_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 aligned_load_u8x16(const std::uint8_t* p_to_load_)
	{
		return _mm_load_si128(reinterpret_cast<const __m128i*>(p_to_load_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 setzero_u8x16()
	{
		return _mm_setzero_si128();
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 setmasked_u8x16(std::uint16_t bit_mask_)
	{
		constexpr std::uint8_t element_mask = static_cast<std::uint8_t>(0xFF);
		return _mm_set_epi8
		(
			static_cast<std::uint8_t>(bit_mask_  & 0x0001)        * element_mask,
			static_cast<std::uint8_t>((bit_mask_ & 0x0002) >> 1)  * element_mask,
			static_cast<std::uint8_t>((bit_mask_ & 0x0004) >> 2)  * element_mask,
			static_cast<std::uint8_t>((bit_mask_ & 0x0008) >> 3)  * element_mask,
			static_cast<std::uint8_t>((bit_mask_ & 0x0010) >> 4)  * element_mask,
			static_cast<std::uint8_t>((bit_mask_ & 0x0020) >> 5)  * element_mask,
			static_cast<std::uint8_t>((bit_mask_ & 0x0040) >> 6)  * element_mask,
			static_cast<std::uint8_t>((bit_mask_ & 0x0080) >> 7)  * element_mask,
			static_cast<std::uint8_t>((bit_mask_ & 0x0100) >> 8)  * element_mask,
			static_cast<std::uint8_t>((bit_mask_ & 0x0200) >> 9)  * element_mask,
			static_cast<std::uint8_t>((bit_mask_ & 0x0400) >> 10) * element_mask,
			static_cast<std::uint8_t>((bit_mask_ & 0x0800) >> 11) * element_mask,
			static_cast<std::uint8_t>((bit_mask_ & 0x1000) >> 12) * element_mask,
			static_cast<std::uint8_t>((bit_mask_ & 0x2000) >> 13) * element_mask,
			static_cast<std::uint8_t>((bit_mask_ & 0x4000) >> 14) * element_mask,
			static_cast<std::uint8_t>((bit_mask_ & 0x8000) >> 15) * element_mask
		);
	}

	template<std::uint16_t BitMask_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 setmasked_u8x16()
	{
		if constexpr (BitMask_ != 0)
		{
			return set_u8x16
			(
				std::integral_constant<std::uint8_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<0,  std::uint8_t>(BitMask_)>::value,
				std::integral_constant<std::uint8_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<1,  std::uint8_t>(BitMask_)>::value,
				std::integral_constant<std::uint8_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<2,  std::uint8_t>(BitMask_)>::value,
				std::integral_constant<std::uint8_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<3,  std::uint8_t>(BitMask_)>::value,
				std::integral_constant<std::uint8_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<4,  std::uint8_t>(BitMask_)>::value,
				std::integral_constant<std::uint8_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<5,  std::uint8_t>(BitMask_)>::value,
				std::integral_constant<std::uint8_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<6,  std::uint8_t>(BitMask_)>::value,
				std::integral_constant<std::uint8_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<7,  std::uint8_t>(BitMask_)>::value,
				std::integral_constant<std::uint8_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<8,  std::uint8_t>(BitMask_)>::value,
				std::integral_constant<std::uint8_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<9,  std::uint8_t>(BitMask_)>::value,
				std::integral_constant<std::uint8_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<10, std::uint8_t>(BitMask_)>::value,
				std::integral_constant<std::uint8_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<11, std::uint8_t>(BitMask_)>::value,
				std::integral_constant<std::uint8_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<12, std::uint8_t>(BitMask_)>::value,
				std::integral_constant<std::uint8_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<13, std::uint8_t>(BitMask_)>::value,
				std::integral_constant<std::uint8_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<14, std::uint8_t>(BitMask_)>::value,
				std::integral_constant<std::uint8_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<15, std::uint8_t>(BitMask_)>::value
			);
		}
		else
		{
			return setzero_u8x16();
		}
	}

	template<bool I0_, bool I1_, bool I2_, bool I3_, bool I4_, bool I5_, bool I6_, bool I7_, bool I8_, bool I9_, bool I10_, bool I11_, bool I12_, bool I13_, bool I14_, bool I15_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 set_index_mask_u8x16()
	{
		if constexpr (I0_ || I1_ || I2_ || I3_ || I4_ || I5_ || I6_ || I7_ || I8_ || I9_ || I10_ || I11_ || I12_ || I13_ || I14_ || I15_)
		{
			return setmasked_u8x16<EmuSIMD::Funcs::make_index_set_mask<I0_, I1_, I2_, I3_, I4_, I5_, I6_, I7_, I8_, I9_, I10_, I11_, I12_, I13_, I14_, I15_>()>();
		}
		else
		{
			return setzero_u8x16();
		}
	}

	template<bool Active_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 set_index_mask_u8x16()
	{
		if constexpr (Active_)
		{
			return setmasked_u8x16<EmuSIMD::Funcs::make_all_indices_set_mask<16, Active_>()>();
		}
		else
		{
			return setzero_u8x16();
		}
	}
#pragma endregion

#pragma region STORES
	EMU_SIMD_COMMON_FUNC_SPEC void store_u8x16(std::uint8_t* p_out_, u8x16_arg a_)
	{
		_mm_storeu_si128(reinterpret_cast<__m128i*>(p_out_), a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC void aligned_store_u8x16(std::uint8_t* p_out_, u8x16_arg a_)
	{
		_mm_store_si128(reinterpret_cast<__m128i*>(p_out_), a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC std::uint8_t get_first_u8x16(u8x16_arg a_)
	{
		std::int32_t first_32_bits = _mm_cvtsi128_si32(a_);
		return *reinterpret_cast<std::uint8_t*>(&first_32_bits);
	}

	EMU_SIMD_COMMON_FUNC_SPEC std::uint16_t movemask_u8x16(u8x16_arg a_)
	{
		return static_cast<std::uint16_t>(_mm_movemask_epi8(a_));
	}
#pragma endregion

#pragma region CASTS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cast_f32x4_u8x16(f32x4_arg a_)
	{
		return _mm_castps_si128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cast_f32x8_u8x16(f32x8_arg a_)
	{
		return _mm256_castsi256_si128(_mm256_castps_si256(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cast_f32x16_u8x16(f32x16_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_castsi512_si128(_mm512_castps_si512(a_));
#else
		return _underlying_impl::emulate_simd_cast_lesser_width<i8x16>(a_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cast_f64x2_u8x16(f64x2_arg a_)
	{
		return _mm_castpd_si128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cast_f64x4_u8x16(f64x4_arg a_)
	{
		return _mm256_castsi256_si128(_mm256_castpd_si256(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cast_f64x8_u8x16(f64x8_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_castsi512_si128(_mm512_castpd_si512(a_));
#else
		return _underlying_impl::emulate_simd_cast_lesser_width<i8x16>(a_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cast_i8x16_u8x16(i8x16_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cast_i16x8_u8x16(i16x8_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cast_i32x4_u8x16(i32x4_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cast_i64x2_u8x16(i64x2_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cast_i8x32_u8x16(i8x32_arg a_)
	{
		return _mm256_castsi256_si128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cast_i16x16_u8x16(i16x16_arg a_)
	{
		return _mm256_castsi256_si128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cast_i32x8_u8x16(i32x8_arg a_)
	{
		return _mm256_castsi256_si128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cast_i64x4_u8x16(i64x4_arg a_)
	{
		return _mm256_castsi256_si128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cast_i8x64_u8x16(i8x64_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_castsi512_si128(a_);
#else
		return _underlying_impl::emulate_simd_cast_lesser_width<u8x16>(a_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cast_i16x32_u8x16(i16x32_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_castsi512_si128(a_);
#else
		return _underlying_impl::emulate_simd_cast_lesser_width<u8x16>(a_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cast_i32x16_u8x16(i32x16_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_castsi512_si128(a_);
#else
		return _underlying_impl::emulate_simd_cast_lesser_width<u8x16>(a_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cast_i64x8_u8x16(i64x8_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_castsi512_si128(a_);
#else
		return _underlying_impl::emulate_simd_cast_lesser_width<u8x16>(a_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cast_u8x16_u8x16(u8x16_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cast_u16x8_u8x16(u16x8_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cast_u32x4_u8x16(u32x4_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cast_u64x2_u8x16(u64x2_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cast_u8x32_u8x16(u8x32_arg a_)
	{
		return _mm256_castsi256_si128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cast_u16x16_u8x16(u16x16_arg a_)
	{
		return _mm256_castsi256_si128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cast_u32x8_u8x16(u32x8_arg a_)
	{
		return _mm256_castsi256_si128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cast_u64x4_u8x16(u64x4_arg a_)
	{
		return _mm256_castsi256_si128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cast_u8x64_u8x16(u8x64_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_castsi512_si128(a_);
#else
		return _underlying_impl::emulate_simd_cast_lesser_width<u8x16>(a_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cast_u16x32_u8x16(u16x32_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_castsi512_si128(a_);
#else
		return _underlying_impl::emulate_simd_cast_lesser_width<u8x16>(a_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cast_u32x16_u8x16(u32x16_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_castsi512_si128(a_);
#else
		return _underlying_impl::emulate_simd_cast_lesser_width<u8x16>(a_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cast_u64x8_u8x16(u64x8_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_castsi512_si128(a_);
#else
		return _underlying_impl::emulate_simd_cast_lesser_width<u8x16>(a_);
#endif
	}
#pragma endregion

#pragma region CONVERSIONS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cvt_f32x4_u8x16(f32x4_arg a_)
	{
		return _mm_cvtepi32_epi8(_mm_cvtps_epi32(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cvt_f32x8_u8x16(f32x8_arg a_)
	{
		return _mm256_cvtepi32_epi8(_mm256_cvtps_epi32(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cvt_f32x16_u8x16(f32x16_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_cvtepi32_epi8(_mm512_cvtps_epi32(a_));
#else
		return EmuSIMD::_underlying_impl::emulate_cvt<u8x16, std::uint8_t, 8, false, 16, true, float>(a_, std::make_index_sequence<16>());
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cvt_f64x2_u8x16(f64x2_arg a_)
	{
		return cvt_i64x2_u8x16(_mm_cvtpd_epi64(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cvt_f64x4_u8x16(f64x4_arg a_)
	{
		return cvt_i64x4_u8x16(_mm256_cvtpd_epi64(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cvt_f64x8_u8x16(f64x8_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_cvtepi64_epi8(_mm512_cvtpd_epi64(a_));
#else
		return EmuSIMD::_underlying_impl::emulate_cvt<u8x16, std::uint8_t, 8, false, 16, true, float>(a_, std::make_index_sequence<16>());
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cvt_i8x16_u8x16(i8x16_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cvt_i16x8_u8x16(i16x8_arg a_)
	{
		return EmuSIMD::_underlying_impl::emulate_cvt<u8x16, std::uint8_t, 8, false, 8, true, std::int16_t>(a_, std::make_index_sequence<16>());
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cvt_i32x4_u8x16(i32x4_arg a_)
	{
		return EmuSIMD::_underlying_impl::emulate_cvt<u8x16, std::uint8_t, 8, false, 4, true, std::int32_t>(a_, std::make_index_sequence<16>());
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cvt_i64x2_u8x16(i64x2_arg a_)
	{
		return EmuSIMD::_underlying_impl::emulate_cvt<u8x16, std::uint8_t, 8, false, 2, true, std::int64_t>(a_, std::make_index_sequence<16>());
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cvt_i8x32_u8x16(i8x32_arg a_)
	{
		return _mm256_castsi256_si128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cvt_i16x16_u8x16(i16x16_arg a_)
	{
		return EmuSIMD::_underlying_impl::emulate_cvt<u8x16, std::uint8_t, 8, false, 16, true, std::int16_t>(a_, std::make_index_sequence<16>());
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cvt_i32x8_u8x16(i32x8_arg a_)
	{
		return EmuSIMD::_underlying_impl::emulate_cvt<u8x16, std::uint8_t, 8, false, 8, true, std::int32_t>(a_, std::make_index_sequence<16>());
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cvt_i64x4_u8x16(i64x4_arg a_)
	{
		return EmuSIMD::_underlying_impl::emulate_cvt<u8x16, std::uint8_t, 8, false, 8, true, std::int64_t>(a_, std::make_index_sequence<16>());
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cvt_i8x64_u8x16(i8x64_arg a_)
	{
		return cast_i8x64_u8x16(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cvt_i16x32_u8x16(i16x32_arg a_)
	{
		return cvt_i16x16_u8x16(cast_i16x32_i16x16(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cvt_i32x16_u8x16(i32x16_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_cvtepi32_epi8(a_);
#else
		return EmuSIMD::_underlying_impl::emulate_cvt<u8x16, std::uint8_t, 8, false, 16, true, std::int32_t>(a_, std::make_index_sequence<16>());
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cvt_i64x8_u8x16(i64x8_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_cvtepi64_epi8(a_);
#else
		return EmuSIMD::_underlying_impl::emulate_cvt<u8x16, std::uint8_t, 8, false, 8, true, std::int64_t>(a_, std::make_index_sequence<16>());
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cvt_u8x16_u8x16(u8x16_arg a_)
	{
		return a_;
	}

		EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cvt_u16x8_u8x16(u16x8_arg a_)
	{
#if 0 // Need a test for if this is legal
		return _mm_cvtepi16_epi8(a_);
#else
		return EmuSIMD::_underlying_impl::emulate_cvt<u8x16, std::uint8_t, 8, false, 8, false, std::uint16_t>(a_, std::make_index_sequence<16>());
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cvt_u32x4_u8x16(u32x4_arg a_)
	{
#if 0 // Need a test for if this is legal
		return _mm_cvtepi32_epi8(a_);
#else
		return EmuSIMD::_underlying_impl::emulate_cvt<u8x16, std::uint8_t, 8, false, 4, false, std::uint32_t>(a_, std::make_index_sequence<16>());
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cvt_u64x2_u8x16(u64x2_arg a_)
	{
#if 0 // Need a test for if this is legal
		return _mm_cvtepi64_epi8(a_);
#else
		return EmuSIMD::_underlying_impl::emulate_cvt<u8x16, std::uint8_t, 8, false, 2, false, std::uint64_t>(a_, std::make_index_sequence<16>());
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cvt_u8x32_u8x16(u8x32_arg a_)
	{
		return _mm256_castsi256_si128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x16 cvt_u16x16_u8x16(u16x16_arg a_)
	{
#if 0 // Need a test for if this is legal
		return _mm256_cvtepi16_epi8(a_);
#else
		return EmuSIMD::_underlying_impl::emulate_cvt<u8x16, std::uint8_t, 8, false, 16, false, std::uint16_t>(a_, std::make_index_sequence<16>());
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x16 cvt_u32x8_u8x16(u32x8_arg a_)
	{
#if 0 // Need a test for if this is legal
		return _mm256_cvtepi32_epi8(a_);
#else
		return EmuSIMD::_underlying_impl::emulate_cvt<u8x16, std::uint8_t, 8, false, 8, false, std::uint32_t>(a_, std::make_index_sequence<16>());
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x16 cvt_u64x4_u8x16(u64x4_arg a_)
	{
#if 0 // Need a test for if this is legal
		return _mm256_cvtepi64_epi8(a_);
#else
		return EmuSIMD::_underlying_impl::emulate_cvt<u8x16, std::uint8_t, 8, false, 4, false, std::uint64_t>(a_, std::make_index_sequence<16>());
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cvt_u8x64_u8x16(u8x64_arg a_)
	{
		return cast_u8x64_u8x16(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cvt_u16x32_u8x16(u16x32_arg a_)
	{
		return cvt_u16x16_u8x16(cast_u16x32_u16x16(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cvt_u32x16_u8x16(u32x16_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_cvtepi32_epi8(a_);
#else
		return EmuSIMD::_underlying_impl::emulate_cvt<u8x16, std::uint8_t, 8, false, 16, false, std::uint32_t>(a_, std::make_index_sequence<16>());
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cvt_u64x8_u8x16(u64x8_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_cvtepi64_epi8(a_);
#else
		return EmuSIMD::_underlying_impl::emulate_cvt<u8x16, std::uint8_t, 8, false, 8, false, std::uint64_t>(a_, std::make_index_sequence<16>());
#endif
	}
#pragma endregion

#pragma region COMPARISONS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cmpeq_u8x16(EmuSIMD::u8x16_arg lhs_, EmuSIMD::u8x16_arg rhs_)
	{
		return _mm_cmpeq_epi8(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cmpneq_u8x16(EmuSIMD::u8x16_arg lhs_, EmuSIMD::u8x16_arg rhs_)
	{
		constexpr std::uint8_t mask = static_cast<std::uint8_t>(0xFF);
		return _mm_xor_si128(set1_i8x16(mask), _mm_cmpeq_epi8(lhs_, rhs_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cmpgt_u8x16(EmuSIMD::u8x16_arg lhs_, EmuSIMD::u8x16_arg rhs_)
	{
		constexpr std::uint8_t mask = static_cast<std::uint8_t>(0xFF);
		return _mm_andnot_si128(_mm_cmpeq_epi8(_mm_min_epu8(lhs_, rhs_), lhs_), set1_u8x16(mask));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cmplt_u8x16(EmuSIMD::u8x16_arg lhs_, EmuSIMD::u8x16_arg rhs_)
	{
		constexpr std::uint8_t mask = static_cast<std::uint8_t>(0xFF);
		return _mm_andnot_si128(_mm_cmpeq_epi8(_mm_max_epu8(lhs_, rhs_), lhs_), set1_u8x16(mask));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cmpge_u8x16(EmuSIMD::u8x16_arg lhs_, EmuSIMD::u8x16_arg rhs_)
	{
		return _mm_cmpeq_epi8(_mm_max_epu8(lhs_, rhs_), lhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cmple_u8x16(EmuSIMD::u8x16_arg lhs_, EmuSIMD::u8x16_arg rhs_)
	{
		return _mm_cmpeq_epi8(_mm_min_epu8(lhs_, rhs_), lhs_);
	}
#pragma endregion

#pragma region MOVES
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 movehl_u8x16(EmuSIMD::u8x16_arg lhs_, EmuSIMD::u8x16_arg rhs_)
	{
		return cast_f32x4_u8x16(movehl_f32x4(cast_u8x16_f32x4(lhs_), cast_u8x16_f32x4(rhs_)));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 movelh_u8x16(EmuSIMD::u8x16_arg lhs_, EmuSIMD::u8x16_arg rhs_)
	{
		return cast_f32x4_u8x16(movelh_f32x4(cast_u8x16_f32x4(lhs_), cast_u8x16_f32x4(rhs_)));
	}
#pragma endregion

#pragma region BITWISE_ARITHMETIC
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 and_u8x16(EmuSIMD::u8x16_arg lhs_, EmuSIMD::u8x16_arg rhs_)
	{
#if EMU_SIMD_USE_128_REGISTERS
		return _mm_and_si128(lhs_, rhs_);
#else
		using EmuSIMD::_underlying_impl::emulate_simd_basic;
		using index_sequence = std::make_index_sequence<16>;
		return emulate_simd_basic(EmuCore::do_bitwise_and<std::uint8_t>(), lhs_, rhs_, index_sequence());
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 or_u8x16(EmuSIMD::u8x16_arg lhs_, EmuSIMD::u8x16_arg rhs_)
	{
#if EMU_SIMD_USE_128_REGISTERS
		return _mm_or_si128(lhs_, rhs_);
#else
		using EmuSIMD::_underlying_impl::emulate_simd_basic;
		using index_sequence = std::make_index_sequence<16>;
		return emulate_simd_basic(EmuCore::do_bitwise_or<std::uint8_t>(), lhs_, rhs_, index_sequence());
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 xor_u8x16(EmuSIMD::u8x16_arg lhs_, EmuSIMD::u8x16_arg rhs_)
	{
#if EMU_SIMD_USE_128_REGISTERS
		return _mm_xor_si128(lhs_, rhs_);
#else
		using EmuSIMD::_underlying_impl::emulate_simd_basic;
		using index_sequence = std::make_index_sequence<16>;
		return emulate_simd_basic(EmuCore::do_bitwise_xor<std::uint8_t>(), lhs_, rhs_, index_sequence());
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 andnot_u8x16(EmuSIMD::u8x16_arg not_lhs_, EmuSIMD::u8x16_arg rhs_)
	{
#if EMU_SIMD_USE_128_REGISTERS
		return _mm_andnot_si128(not_lhs_, rhs_);
#else
		using EmuSIMD::_underlying_impl::emulate_simd_basic;
		using index_sequence = std::make_index_sequence<16>;
		return emulate_simd_basic(EmuCore::do_bitwise_andnot<std::uint8_t>(), not_lhs_, rhs_, index_sequence());
#endif
	}

	template<std::int32_t NumShifts_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 shift_left_u8x16(EmuSIMD::u8x16_arg lhs_)
	{
		if constexpr (NumShifts_ >= 8)
		{
			return setzero_u8x16();
		}
		else
		{
#if EMU_SIMD_USE_128_REGISTERS
			constexpr std::uint8_t remaining_bits = std::uint8_t(0xFF << NumShifts_);
			EmuSIMD::u8x16 remaining_bits_mask = set1_u8x16(remaining_bits);
			return and_u8x16(remaining_bits_mask, _mm_slli_epi32(lhs_, NumShifts_));
#else
			using EmuSIMD::_underlying_impl::emulate_simd_basic;
			using index_sequence = std::make_index_sequence<16>;
			auto func = [](const std::uint8_t& a_) { return (a_ << NumShifts_); };
			return emulate_simd_basic(func, lhs_, index_sequence());
#endif
		}

	}

	template<std::int32_t NumShifts_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 shift_right_arithmetic_u8x16(EmuSIMD::u8x16_arg lhs_)
	{
		// No sign bit, so same as logical shift
		return shift_right_logical_u8x16<NumShifts_>(lhs_);
	}

	template<std::int32_t NumShifts_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 shift_right_logical_u8x16(EmuSIMD::u8x16_arg lhs_)
	{
		if constexpr (NumShifts_ >= 8)
		{
			return setzero_u8x16();
		}
		else
		{
#if EMU_SIMD_USE_128_REGISTERS
			constexpr std::uint8_t remaining_bits = std::uint8_t(0xFF >> NumShifts_);
			EmuSIMD::u8x16 remaining_bits_mask = set1_u8x16(remaining_bits);
			return and_u8x16(remaining_bits_mask, _mm_srli_epi32(lhs_, NumShifts_));
#else
			using EmuSIMD::_underlying_impl::emulate_simd_basic;
			using index_sequence = std::make_index_sequence<16>;
			auto func = [](const std::uint8_t& a_) { return (a_ >> NumShifts_); };
			return emulate_simd_basic(func, lhs_, index_sequence());
#endif
		}
	}
#pragma endregion

#pragma region BLENDS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 blendv_u8x16(EmuSIMD::u8x16_arg a_, EmuSIMD::u8x16_arg b_, EmuSIMD::u8x16_arg shuffle_mask_vec_)
	{
		return _mm_blendv_epi8(a_, b_, shuffle_mask_vec_);
	}
#pragma endregion

#pragma region MINMAX_FUNCS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 min_u8x16(EmuSIMD::u8x16_arg a_, EmuSIMD::u8x16_arg b_)
	{
		return _mm_min_epu8(a_, b_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 horizontal_min_u8x16(EmuSIMD::u8x16_arg a_)
	{
		constexpr auto reverse_lo_mask = make_shuffle_mask_8<0, 1, 2, 3, 4, 5, 6, 7, 0, 1, 2, 3, 4, 5, 6, 7>();
		EmuSIMD::u8x16 result = movelh_u8x16(a_, a_);
		result = min_u8x16(result, a_);
		result = min_u8x16(result, permute_u8x16<reverse_lo_mask>(result));

		// 4 elements left to determine result, so defer to 32-bit calculation
		EmuSIMD::u32x4 last_4_result = cvt_u8x16_u32x4(result);
		last_4_result = horizontal_min_u32x4(last_4_result);
		return cvt_u32x4_u8x16(last_4_result);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 horizontal_min_fill_u8x16(EmuSIMD::u8x16_arg a_)
	{
		constexpr auto all_el0_mask = make_shuffle_mask_8<0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0>();
		return permute_u8x16<all_el0_mask>(horizontal_min_u8x16(a_));
	}

	template<typename Out_>
	EMU_SIMD_COMMON_FUNC_SPEC auto horizontal_min_scalar_u8x16(EmuSIMD::u8x16_arg a_)
		-> typename std::remove_cvref<Out_>::type
	{
		return static_cast<typename std::remove_cvref<Out_>::type>(get_first_u8x16(horizontal_min_u8x16(a_)));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 max_u8x16(EmuSIMD::u8x16_arg a_, EmuSIMD::u8x16_arg b_)
	{
		return _mm_max_epu8(a_, b_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 horizontal_max_u8x16(EmuSIMD::u8x16_arg a_)
	{
		constexpr auto reverse_lo_mask = make_shuffle_mask_8<0, 1, 2, 3, 4, 5, 6, 7, 0, 1, 2, 3, 4, 5, 6, 7>();
		EmuSIMD::u8x16 result = movelh_u8x16(a_, a_);
		result = max_u8x16(result, a_);
		result = max_u8x16(result, permute_u8x16<reverse_lo_mask>(result));

		// 4 elements left to determine result, so defer to 32-bit calculation
		EmuSIMD::u32x4 last_4_result = cvt_u8x16_u32x4(result);
		last_4_result = horizontal_max_u32x4(last_4_result);
		return cvt_u32x4_u8x16(last_4_result);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 horizontal_max_fill_u8x16(EmuSIMD::u8x16_arg a_)
	{
		constexpr auto all_el0_mask = make_shuffle_mask_8<0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0>();
		return permute_u8x16<all_el0_mask>(horizontal_max_u8x16(a_));
	}

	template<typename Out_>
	EMU_SIMD_COMMON_FUNC_SPEC auto horizontal_max_scalar_u8x16(EmuSIMD::u8x16_arg a_)
		-> typename std::remove_cvref<Out_>::type
	{
		return static_cast<typename std::remove_cvref<Out_>::type>(get_first_u8x16(horizontal_max_u8x16(a_)));
	}
#pragma endregion

#pragma region BASIC_ARITHMETIC
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 mul_all_u8x16(EmuSIMD::u8x16_arg lhs_, EmuSIMD::u8x16_arg rhs_)
	{
		EmuSIMD::u8x16 even_bytes = _mm_mullo_epi16(lhs_, rhs_);
		EmuSIMD::u8x16 odd_bytes = _mm_mullo_epi16(_mm_srli_epi16(lhs_, 8), _mm_srli_epi16(rhs_, 8));
		return _mm_or_si128(_mm_slli_epi16(odd_bytes, 8), _mm_srli_epi16(_mm_slli_epi16(even_bytes, 8), 8));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 negate_u8x16(EmuSIMD::u8x16_arg to_negate_)
	{
		return _mm_sub_epi8(_mm_setzero_si128(), to_negate_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 add_u8x16(EmuSIMD::u8x16_arg lhs_, EmuSIMD::u8x16_arg rhs_)
	{
		return _mm_add_epi8(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 sub_u8x16(EmuSIMD::u8x16_arg lhs_, EmuSIMD::u8x16_arg rhs_)
	{
		return _mm_sub_epi8(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 div_u8x16(EmuSIMD::u8x16_arg lhs_, EmuSIMD::u8x16_arg rhs_)
	{
#if EMU_CORE_X86_X64_SVML
		return _mm_div_epu8(lhs_, rhs_);
#else
		// lo
		EmuSIMD::u16x8 lane64_a = cvt_u8x16_u16x8(lhs_);
		EmuSIMD::u16x8 lane64_b = cvt_u8x16_u16x8(rhs_);
		EmuSIMD::u8x16 lo = cvt_u16x8_u8x16(div_u16x8(lane64_a, lane64_b));

		// hi - move hi bits to lo via f32 reinterpretation of this width register
		EmuSIMD::u8x16 tmp_lane = movehl_u8x16(lhs_, lhs_);
		lane64_a = cvt_u8x16_u16x8(tmp_lane);

		tmp_lane = movehl_u8x16(rhs_, rhs_);
		lane64_b = cvt_u8x16_u16x8(tmp_lane);

		// Move hi and lo into the same register, in their respective 64-bit lanes
		EmuSIMD::i8x16 hi = cvt_u16x8_u8x16(div_u16x8(lane64_a, lane64_b));
		return movelh_u8x16(lo, hi);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 addsub_u8x16(EmuSIMD::u8x16_arg lhs_, EmuSIMD::u8x16_arg rhs_)
	{
		constexpr std::uint8_t byte_mask = static_cast<std::uint8_t>(0xFF);
		const EmuSIMD::u8x16 mask = _mm_set_epi8(byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0);
		EmuSIMD::u8x16 out = _mm_add_epi8(lhs_, _mm_and_si128(mask, rhs_));
		return _mm_sub_epi8(lhs_, _mm_andnot_si128(mask, rhs_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 subadd_u8x16(EmuSIMD::u8x16_arg lhs_, EmuSIMD::u8x16_arg rhs_)
	{
		constexpr std::uint8_t byte_mask = static_cast<std::uint8_t>(0xFF);
		const EmuSIMD::u8x16 mask = _mm_set_epi8(byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0);
		EmuSIMD::u8x16 out = _mm_sub_epi8(lhs_, _mm_and_si128(mask, rhs_));
		return _mm_add_epi8(lhs_, _mm_andnot_si128(mask, rhs_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 fmadd_u8x16(EmuSIMD::u8x16_arg a_, EmuSIMD::u8x16_arg b_, EmuSIMD::u8x16_arg c_)
	{
		return _mm_add_epi8(mul_all_u8x16(a_, b_), c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 fmsub_u8x16(EmuSIMD::u8x16_arg a_, EmuSIMD::u8x16_arg b_, EmuSIMD::u8x16_arg c_)
	{
		return _mm_sub_epi8(mul_all_u8x16(a_, b_), c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 fnmadd_u8x16(EmuSIMD::u8x16_arg a_, EmuSIMD::u8x16_arg b_, EmuSIMD::u8x16_arg c_)
	{
		return _mm_add_epi8(mul_all_u8x16(negate_u8x16(a_), b_), c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 fnmsub_u8x16(EmuSIMD::u8x16_arg a_, EmuSIMD::u8x16_arg b_, EmuSIMD::u8x16_arg c_)
	{
		return _mm_sub_epi8(mul_all_u8x16(negate_u8x16(a_), b_), c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 fmaddsub_u8x16(EmuSIMD::u8x16_arg a_, EmuSIMD::u8x16_arg b_, EmuSIMD::u8x16_arg c_)
	{
		return addsub_u8x16(mul_all_u8x16(negate_u8x16(a_), b_), c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 fmsubadd_u8x16(EmuSIMD::u8x16_arg a_, EmuSIMD::u8x16_arg b_, EmuSIMD::u8x16_arg c_)
	{
		return subadd_u8x16(mul_all_u8x16(negate_u8x16(a_), b_), c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 floor_u8x16(EmuSIMD::u8x16_arg to_floor_)
	{
		return to_floor_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 ceil_u8x16(EmuSIMD::u8x16_arg to_ceil_)
	{
		return to_ceil_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 trunc_u8x16(EmuSIMD::u8x16_arg to_trunc_)
	{
		return to_trunc_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 mod_u8x16(EmuSIMD::u8x16_arg lhs_, EmuSIMD::u8x16_arg rhs_)
	{
#if EMU_CORE_X86_X64_SVML
		return _mm_rem_epu8(lhs_, rhs_);
#else
		EmuSIMD::u8x16 to_subtract = div_u8x16(lhs_, rhs_);
		to_subtract = mul_all_u8x16(to_subtract, rhs_);
		return sub_u8x16(lhs_, to_subtract);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 abs_u8x16(EmuSIMD::u8x16_arg in_)
	{
		return in_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 sqrt_u8x16(EmuSIMD::u8x16_arg in_)
	{
		return emulate_fp_u8x16([](EmuSIMD::f32x4_arg in_fp_) { return sqrt_f32x4(in_fp_); }, in_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 rsqrt_u8x16(EmuSIMD::u8x16_arg in_)
	{
		return emulate_fp_u8x16([](EmuSIMD::f32x4_arg in_fp_) { return rsqrt_f32x4(in_fp_); }, in_);
	}
#pragma endregion

#pragma region NEAR_COMPARISONS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cmpnear_u8x16(EmuSIMD::u8x16_arg lhs_, EmuSIMD::u8x16_arg rhs_)
	{
		return cmpeq_u8x16(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cmpnear_u8x16(EmuSIMD::u8x16_arg lhs_, EmuSIMD::u8x16_arg rhs_, EmuSIMD::u8x16_arg epsilon)
	{
		return cmple_u8x16(sub_u8x16(lhs_, rhs_), epsilon);
	}
#pragma endregion

#pragma region TRIG
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 cos_u8x16(EmuSIMD::u8x16_arg in_)
	{
		return emulate_fp_u8x16([](EmuSIMD::f32x4_arg in_fp_) { return cos_f32x4(in_fp_); }, in_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 sin_u8x16(EmuSIMD::u8x16_arg in_)
	{
		return emulate_fp_u8x16([](EmuSIMD::f32x4_arg in_fp_) { return sin_f32x4(in_fp_); }, in_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 tan_u8x16(EmuSIMD::u8x16_arg in_)
	{
		return emulate_fp_u8x16([](EmuSIMD::f32x4_arg in_fp_) { return tan_f32x4(in_fp_); }, in_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 acos_u8x16(EmuSIMD::u8x16_arg in_)
	{
		return emulate_fp_u8x16([](EmuSIMD::f32x4_arg in_fp_) { return acos_f32x4(in_fp_); }, in_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 asin_u8x16(EmuSIMD::u8x16_arg in_)
	{
		return emulate_fp_u8x16([](EmuSIMD::f32x4_arg in_fp_) { return asin_f32x4(in_fp_); }, in_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x16 atan_u8x16(EmuSIMD::u8x16_arg in_)
	{
		return emulate_fp_u8x16([](EmuSIMD::f32x4_arg in_fp_) { return atan_f32x4(in_fp_); }, in_);
	}
#pragma endregion
}

#endif
