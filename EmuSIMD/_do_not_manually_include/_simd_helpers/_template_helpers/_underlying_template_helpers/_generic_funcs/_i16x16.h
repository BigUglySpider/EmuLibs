#ifndef EMU_SIMD_GENERIC_FUNCS_I16X16_H_INC_
#define EMU_SIMD_GENERIC_FUNCS_I16X16_H_INC_ 1

#include "_generic_declarations/_all_generic_declarations.h"
#include "_common_generic_func_helpers.h"

namespace EmuSIMD::Funcs
{
#pragma region SETTERS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 set_i16x16
	(
		std::int16_t e0, std::int16_t e1, std::int16_t e2, std::int16_t e3, std::int16_t e4, std::int16_t e5, std::int16_t e6, std::int16_t e7,
		std::int16_t e8, std::int16_t e9, std::int16_t e10, std::int16_t e11, std::int16_t e12, std::int16_t e13, std::int16_t e14, std::int16_t e15
	)
	{
		return _mm256_set_epi16(e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 setr_i16x16
	(
		std::int16_t e0, std::int16_t e1, std::int16_t e2, std::int16_t e3, std::int16_t e4, std::int16_t e5, std::int16_t e6, std::int16_t e7,
		std::int16_t e8, std::int16_t e9, std::int16_t e10, std::int16_t e11, std::int16_t e12, std::int16_t e13, std::int16_t e14, std::int16_t e15
	)
	{
		//return _mm256_setr_epi16(e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15);
		return _mm256_set_epi16(e15, e14, e13, e12, e11, e10, e9, e8, e7, e6, e5, e4, e3, e2, e1, e0);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 set1_i16x16(std::int16_t all_)
	{
		return _mm256_set1_epi16(all_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 load_i16x16(const std::int16_t* p_to_load_)
	{
		return _mm256_loadu_si256(reinterpret_cast<const __m256i*>(p_to_load_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 aligned_load_i16x16(const std::int16_t* p_to_load_)
	{
		return _mm256_load_si256(reinterpret_cast<const __m256i*>(p_to_load_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 setzero_i16x16()
	{
		return _mm256_setzero_si256();
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 setmasked_i16x16(std::uint16_t bit_mask_)
	{
		constexpr std::int16_t element_mask = static_cast<std::int16_t>(0xFFFF);
		return _mm256_set_epi16
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
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 setmasked_i16x16()
	{
		if constexpr(BitMask_ != 0)
		{
			return set_i16x16
			(
				std::integral_constant<std::int16_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<0,  std::int16_t>(BitMask_)>::value,
				std::integral_constant<std::int16_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<1,  std::int16_t>(BitMask_)>::value,
				std::integral_constant<std::int16_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<2,  std::int16_t>(BitMask_)>::value,
				std::integral_constant<std::int16_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<3,  std::int16_t>(BitMask_)>::value,
				std::integral_constant<std::int16_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<4,  std::int16_t>(BitMask_)>::value,
				std::integral_constant<std::int16_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<5,  std::int16_t>(BitMask_)>::value,
				std::integral_constant<std::int16_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<6,  std::int16_t>(BitMask_)>::value,
				std::integral_constant<std::int16_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<7,  std::int16_t>(BitMask_)>::value,
				std::integral_constant<std::int16_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<8,  std::int16_t>(BitMask_)>::value,
				std::integral_constant<std::int16_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<9,  std::int16_t>(BitMask_)>::value,
				std::integral_constant<std::int16_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<10, std::int16_t>(BitMask_)>::value,
				std::integral_constant<std::int16_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<11, std::int16_t>(BitMask_)>::value,
				std::integral_constant<std::int16_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<12, std::int16_t>(BitMask_)>::value,
				std::integral_constant<std::int16_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<13, std::int16_t>(BitMask_)>::value,
				std::integral_constant<std::int16_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<14, std::int16_t>(BitMask_)>::value,
				std::integral_constant<std::int16_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<15, std::int16_t>(BitMask_)>::value
			);
		}
		else
		{
			return setzero_i16x16();
		}
	}

	template<bool I0_, bool I1_, bool I2_, bool I3_, bool I4_, bool I5_, bool I6_, bool I7_, bool I8_, bool I9_, bool I10_, bool I11_, bool I12_, bool I13_, bool I14_, bool I15_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 set_index_mask_i16x16()
	{
		if constexpr(I0_ || I1_ || I2_ || I3_ || I4_ || I5_ || I6_ || I7_ || I8_ || I9_ || I10_ || I11_ || I12_ || I13_ || I14_ || I15_)
		{
			return setmasked_i16x16<EmuSIMD::Funcs::make_index_set_mask<I0_, I1_, I2_, I3_, I4_, I5_, I6_, I7_, I8_, I9_, I10_, I11_, I12_, I13_, I14_, I15_>()>();
		}
		else
		{
			return setzero_i16x16();
		}
	}

	template<bool Active_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 set_index_mask_i16x16()
	{
		if constexpr (Active_)
		{
			return setmasked_i16x16<EmuSIMD::Funcs::make_all_indices_set_mask<16, Active_>()>();
		}
		else
		{
			return setzero_i16x16();
		}
	}
#pragma endregion

#pragma region STORES
	EMU_SIMD_COMMON_FUNC_SPEC void store_i16x16(std::int16_t* p_out_, i16x16_arg a_)
	{
		_mm256_storeu_si256(reinterpret_cast<__m256i*>(p_out_), a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC void aligned_store_i16x16(std::int16_t* p_out_, i16x16_arg a_)
	{
		_mm256_store_si256(reinterpret_cast<__m256i*>(p_out_), a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC std::int16_t get_first_i16x16(i16x16_arg a_)
	{
		return get_first_i16x8(cast_i16x16_i16x8(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC std::uint16_t movemask_i16x16(i16x16_arg a_)
	{
		return EmuSIMD::Funcs::convert_movemask_width<32, 16, std::uint16_t>(_mm256_movemask_epi8(a_));
	}
#pragma endregion

#pragma region CASTS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cast_f32x4_i16x16(f32x4_arg a_)
	{
		return _mm256_castsi128_si256(_mm_castps_si128(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cast_f32x8_i16x16(f32x8_arg a_)
	{
		return _mm256_castps_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cast_f32x16_i16x16(f32x16_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_castsi512_si256(_mm512_castps_si512(a_));
#else
		return _underlying_impl::emulate_simd_cast_lesser_width<i16x16>(a_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cast_f64x2_i16x16(f64x2_arg a_)
	{
		return _mm256_castsi128_si256(_mm_castpd_si128(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cast_f64x4_i16x16(f64x4_arg a_)
	{
		return _mm256_castpd_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cast_f64x8_i16x16(f64x8_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_castsi512_si256(_mm512_castpd_si512(a_));
#else
		return _underlying_impl::emulate_simd_cast_lesser_width<i16x16>(a_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cast_i8x16_i16x16(i8x16_arg a_)
	{
		return _mm256_castsi128_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cast_i16x8_i16x16(i16x8_arg a_)
	{
		return _mm256_castsi128_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cast_i32x4_i16x16(i32x4_arg a_)
	{
		return _mm256_castsi128_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cast_i64x2_i16x16(i64x2_arg a_)
	{
		return _mm256_castsi128_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cast_i8x32_i16x16(i8x32_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cast_i16x16_i16x16(i16x16_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cast_i32x8_i16x16(i32x8_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cast_i64x4_i16x16(i64x4_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cast_i8x64_i16x16(i8x64_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_castsi512_si256(a_);
#else
		return _underlying_impl::emulate_simd_cast_lesser_width<i16x16>(a_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cast_i16x32_i16x16(i16x32_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_castsi512_si256(a_);
#else
		return _underlying_impl::emulate_simd_cast_lesser_width<i16x16>(a_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cast_i32x16_i16x16(i32x16_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_castsi512_si256(a_);
#else
		return _underlying_impl::emulate_simd_cast_lesser_width<i16x16>(a_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cast_i64x8_i16x16(i64x8_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_castsi512_si256(a_);
#else
		return _underlying_impl::emulate_simd_cast_lesser_width<i16x16>(a_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cast_u8x16_i16x16(u8x16_arg a_)
	{
		return _mm256_castsi128_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cast_u16x8_i16x16(u16x8_arg a_)
	{
		return _mm256_castsi128_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cast_u32x4_i16x16(u32x4_arg a_)
	{
		return _mm256_castsi128_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cast_u64x2_i16x16(u64x2_arg a_)
	{
		return _mm256_castsi128_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cast_u8x32_i16x16(u8x32_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cast_u16x16_i16x16(u16x16_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cast_u32x8_i16x16(u32x8_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cast_u64x4_i16x16(u64x4_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cast_u8x64_i16x16(u8x64_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_castsi512_si256(a_);
#else
		return _underlying_impl::emulate_simd_cast_lesser_width<i16x16>(a_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cast_u16x32_i16x16(u16x32_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_castsi512_si256(a_);
#else
		return _underlying_impl::emulate_simd_cast_lesser_width<i16x16>(a_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cast_u32x16_i16x16(u32x16_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_castsi512_si256(a_);
#else
		return _underlying_impl::emulate_simd_cast_lesser_width<i16x16>(a_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cast_u64x8_i16x16(u64x8_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_castsi512_si256(a_);
#else
		return _underlying_impl::emulate_simd_cast_lesser_width<i16x16>(a_);
#endif
	}
#pragma endregion

#pragma region CONVERSIONS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cvt_f32x4_i16x16(f32x4_arg a_)
	{
		return cvt_i32x4_i16x16(_mm_cvtps_epi32(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cvt_f32x8_i16x16(f32x8_arg a_)
	{
		return cvt_i32x8_i16x16(_mm256_cvtps_epi32(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cvt_f32x16_i16x16(f32x16_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_cvtepi32_epi16(_mm512_cvtps_epi32(a_));
#else
		return EmuSIMD::_underlying_impl::emulate_cvt<i16x16, std::int16_t, 16, true, 16, true, float>(a_, std::make_index_sequence<16>());
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cvt_f64x2_i16x16(f64x2_arg a_)
	{
		return cvt_i32x4_i16x16(_mm_cvtpd_epi32(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cvt_f64x4_i16x16(f64x4_arg a_)
	{
		return cvt_i32x4_i16x16(_mm256_cvtpd_epi32(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cvt_f64x8_i16x16(f64x8_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm256_castsi128_si256(_mm512_cvtepi64_epi16(_mm512_cvtpd_epi64(a_)));
#else
		return EmuSIMD::_underlying_impl::emulate_cvt<i16x16, std::int16_t, 16, true, 8, true, double>(a_, std::make_index_sequence<16>());
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cvt_i8x16_i16x16(i8x16_arg a_)
	{
		return _mm256_cvtepi8_epi16(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cvt_i16x8_i16x16(i16x8_arg a_)
	{
		return _mm256_castsi128_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cvt_i32x4_i16x16(i32x4_arg a_)
	{
		return EmuSIMD::_underlying_impl::emulate_cvt<i16x16, std::int16_t, 16, true, 4, true, std::int32_t>(a_, std::make_index_sequence<16>());
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cvt_i64x2_i16x16(i64x2_arg a_)
	{
		return EmuSIMD::_underlying_impl::emulate_cvt<i16x16, std::int16_t, 16, true, 2, true, std::int64_t>(a_, std::make_index_sequence<16>());
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cvt_i8x32_i16x16(i8x32_arg a_)
	{
		return _mm256_cvtepi8_epi16(_mm256_castsi256_si128(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cvt_i16x16_i16x16(i16x16_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cvt_i32x8_i16x16(i32x8_arg a_)
	{
		return EmuSIMD::_underlying_impl::emulate_cvt<i16x16, std::int32_t, 16, true, 8, true, std::int32_t>(a_, std::make_index_sequence<16>());
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cvt_i64x4_i16x16(i64x4_arg a_)
	{
		return EmuSIMD::_underlying_impl::emulate_cvt<i16x16, std::int16_t, 16, true, 4, true, std::int64_t>(a_, std::make_index_sequence<16>());
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cvt_i8x64_i16x16(i8x64_arg a_)
	{
		return cvt_i8x16_i16x16(cast_i8x64_i8x16(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cvt_i16x32_i16x16(i16x32_arg a_)
	{
		return cast_i16x32_i16x16(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cvt_i32x16_i16x16(i32x16_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_cvtepi32_epi16(a_);
#else
		return EmuSIMD::_underlying_impl::emulate_cvt<i16x16, std::int16_t, 16, true, 16, true, std::int32_t>(a_, std::make_index_sequence<16>());
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cvt_i64x8_i16x16(i64x8_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm256_castsi128_si256(_mm512_cvtepi64_epi16(a_));
#else
		return EmuSIMD::_underlying_impl::emulate_cvt<i16x16, std::int16_t, 16, true, 8, true, std::int64_t>(a_, std::make_index_sequence<16>());
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cvt_u8x16_i16x16(u8x16_arg a_)
	{
		return _mm256_castsi128_si256(_mm_cvtepu8_epi16(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cvt_u16x8_i16x16(u16x8_arg a_)
	{
		return _mm256_castsi128_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cvt_u32x4_i16x16(u32x4_arg a_)
	{
		return EmuSIMD::_underlying_impl::emulate_cvt<i16x16, std::int16_t, 16, true, 4, false, std::uint32_t>(a_, std::make_index_sequence<16>());
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cvt_u64x2_i16x16(u64x2_arg a_)
	{
		return EmuSIMD::_underlying_impl::emulate_cvt<i16x16, std::int16_t, 16, true, 2, false, std::uint64_t>(a_, std::make_index_sequence<16>());
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cvt_u8x32_i16x16(u8x32_arg a_)
	{
		return _mm256_cvtepu8_epi16(_mm256_castsi256_si128(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cvt_u16x16_i16x16(u16x16_arg a_)
	{
		return cast_u16x16_i16x16(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cvt_u32x8_i16x16(u32x8_arg a_)
	{
		return EmuSIMD::_underlying_impl::emulate_cvt<i16x16, std::int16_t, 16, true, 8, false, std::uint32_t>(a_, std::make_index_sequence<16>());
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cvt_u64x4_i16x16(u64x4_arg a_)
	{
		return EmuSIMD::_underlying_impl::emulate_cvt<i16x16, std::int16_t, 16, true, 4, false, std::uint64_t>(a_, std::make_index_sequence<16>());
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cvt_u8x64_i16x16(u8x64_arg a_)
	{
		return cvt_u8x16_i16x16(cast_u8x64_u8x16(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cvt_u16x32_i16x16(u16x32_arg a_)
	{
		return cast_u16x32_i16x16(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cvt_u32x16_i16x16(u32x16_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_cvtepi32_epi16(a_);
#else
		return EmuSIMD::_underlying_impl::emulate_cvt<i16x16, std::int16_t, 16, true, 16, false, std::uint32_t>(a_, std::make_index_sequence<16>());
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cvt_u64x8_i16x16(u64x8_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm256_castsi128_si256(_mm512_cvtepi64_epi16(a_));
#else
		return EmuSIMD::_underlying_impl::emulate_cvt<i16x16, std::int16_t, 16, true, 8, false, std::uint64_t>(a_, std::make_index_sequence<16>());
#endif
	}
#pragma endregion

#pragma region COMPARISONS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cmpeq_i16x16(EmuSIMD::i16x16_arg lhs_, EmuSIMD::i16x16_arg rhs_)
	{
		return _mm256_cmpeq_epi16(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cmpneq_i16x16(EmuSIMD::i16x16_arg lhs_, EmuSIMD::i16x16_arg rhs_)
	{
		constexpr std::int16_t mask = static_cast<std::int16_t>(0xFFFF);
		return _mm256_xor_si256(set1_i16x16(mask), _mm256_cmpeq_epi16(lhs_, rhs_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cmpgt_i16x16(EmuSIMD::i16x16_arg lhs_, EmuSIMD::i16x16_arg rhs_)
	{
		return _mm256_cmpgt_epi16(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cmplt_i16x16(EmuSIMD::i16x16_arg lhs_, EmuSIMD::i16x16_arg rhs_)
	{
		return _mm256_cmpgt_epi16(rhs_, lhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cmpge_i16x16(EmuSIMD::i16x16_arg lhs_, EmuSIMD::i16x16_arg rhs_)
	{
		return _mm256_or_si256(_mm256_cmpgt_epi16(lhs_, rhs_), _mm256_cmpeq_epi16(lhs_, rhs_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cmple_i16x16(EmuSIMD::i16x16_arg lhs_, EmuSIMD::i16x16_arg rhs_)
	{
		return _mm256_or_si256(_mm256_cmpgt_epi16(rhs_, lhs_), _mm256_cmpeq_epi16(lhs_, rhs_));
	}
#pragma endregion

#pragma region MOVES
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 movehl_i16x16(EmuSIMD::i16x16_arg lhs_, EmuSIMD::i16x16_arg rhs_)
	{
		return cast_f32x8_i16x16(movehl_f32x8(cast_i16x16_f32x8(lhs_), cast_i16x16_f32x8(rhs_)));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 movelh_i16x16(EmuSIMD::i16x16_arg lhs_, EmuSIMD::i16x16_arg rhs_)
	{
		return cast_f32x8_i16x16(movelh_f32x8(cast_i16x16_f32x8(lhs_), cast_i16x16_f32x8(rhs_)));
	}
#pragma endregion

#pragma region BITWISE_ARITHMETIC
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 and_i16x16(EmuSIMD::i16x16_arg lhs_, EmuSIMD::i16x16_arg rhs_)
	{
#if EMU_SIMD_USE_256_REGISTERS
		return _mm256_and_si256(lhs_, rhs_);
#else
		using EmuSIMD::_underlying_impl::emulate_simd_basic;
		return emulate_simd_basic([](i16x8_arg a_, i16x8_arg b_) { return EmuSIMD::Funcs::and_i16x8(a_, b_); }, lhs_, rhs_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 or_i16x16(EmuSIMD::i16x16_arg lhs_, EmuSIMD::i16x16_arg rhs_)
	{
#if EMU_SIMD_USE_256_REGISTERS
		return _mm256_or_si256(lhs_, rhs_);
#else
		using EmuSIMD::_underlying_impl::emulate_simd_basic;
		return emulate_simd_basic([](i16x8_arg a_, i16x8_arg b_) { return EmuSIMD::Funcs::or_i16x8(a_, b_); }, lhs_, rhs_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 xor_i16x16(EmuSIMD::i16x16_arg lhs_, EmuSIMD::i16x16_arg rhs_)
	{
#if EMU_SIMD_USE_256_REGISTERS
		return _mm256_xor_si256(lhs_, rhs_);
#else
		using EmuSIMD::_underlying_impl::emulate_simd_basic;
		return emulate_simd_basic([](i16x8_arg a_, i16x8_arg b_) { return EmuSIMD::Funcs::xor_i16x8(a_, b_); }, lhs_, rhs_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 andnot_i16x16(EmuSIMD::i16x16_arg not_lhs_, EmuSIMD::i16x16_arg rhs_)
	{
#if EMU_SIMD_USE_256_REGISTERS
		return _mm256_andnot_si256(not_lhs_, rhs_);
#else
		using EmuSIMD::_underlying_impl::emulate_simd_basic;
		return emulate_simd_basic([](i16x8_arg a_, i16x8_arg b_) { return EmuSIMD::Funcs::andnot_i16x8(a_, b_); }, not_lhs_, rhs_);
#endif
	}

	template<std::int32_t NumShifts_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 shift_left_i16x16(EmuSIMD::i16x16_arg lhs_)
	{
		if constexpr (NumShifts_ >= 16)
		{
			return setzero_i16x16();
		}
		else
		{
#if EMU_SIMD_USE_256_REGISTERS
			return _mm256_slli_epi16(lhs_, NumShifts_);
#else
			using EmuSIMD::_underlying_impl::emulate_simd_basic;
			return emulate_simd_basic([](i16x8_arg a_) { return shift_left_i16x8<NumShifts_>(a_); }, lhs_);
#endif
		}
	}

	template<std::int32_t NumShifts_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 shift_right_arithmetic_i16x16(EmuSIMD::i16x16_arg lhs_)
	{
		if constexpr (NumShifts_ >= 16)
		{
			return setzero_i16x16();
		}
		else
		{
#if EMU_SIMD_USE_256_REGISTERS
			return _mm256_srai_epi16(lhs_, NumShifts_);
#else
			using EmuSIMD::_underlying_impl::emulate_simd_basic;
			return emulate_simd_basic([](i16x8_arg a_) { return shift_right_arithmetic_i16x8<NumShifts_>(a_); }, lhs_);
#endif
		}
	}

	template<std::int32_t NumShifts_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 shift_right_logical_i16x16(EmuSIMD::i16x16_arg lhs_)
	{
		if constexpr (NumShifts_ >= 16)
		{
			return setzero_i16x16();
		}
		else
		{
#if EMU_SIMD_USE_256_REGISTERS
			return _mm256_srli_epi16(lhs_, NumShifts_);
#else
			using EmuSIMD::_underlying_impl::emulate_simd_basic;
			return emulate_simd_basic([](i16x8_arg a_) { return shift_right_logical_i16x8<NumShifts_>(a_); }, lhs_);
#endif
		}
	}
#pragma endregion

#pragma region BLENDS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 blendv_i16x16(EmuSIMD::i16x16_arg a_, EmuSIMD::i16x16_arg b_, EmuSIMD::i16x16_arg shuffle_mask_vec_)
	{
		return _mm256_blendv_epi8
		(
			a_,
			b_,
			blend_mask_vector_16_to_8(shuffle_mask_vec_)
		);
	}
#pragma endregion

#pragma region MINMAX_FUNCS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 min_i16x16(EmuSIMD::i16x16_arg a_, EmuSIMD::i16x16_arg b_)
	{
		return _mm256_min_epi16(a_, b_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 horizontal_min_i16x16(EmuSIMD::i16x16_arg a_)
	{
		i16x8 lane = min_i16x8(cast_i16x16_i16x8(a_), extract_i16x16_lane_i16x8<1>(a_));
		return cast_i16x8_i16x16(horizontal_min_i16x8(lane));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 horizontal_min_fill_i16x16(EmuSIMD::i16x16_arg a_)
	{
		i16x8 lane = min_i16x8(cast_i16x16_i16x8(a_), extract_i16x16_lane_i16x8<1>(a_));
		lane = horizontal_min_fill_i16x8(lane);
		return _mm256_inserti128_si256(cast_i16x8_i16x16(lane), lane, 1);
	}

	template<typename Out_>
	EMU_SIMD_COMMON_FUNC_SPEC auto horizontal_min_scalar_i16x16(EmuSIMD::i16x16_arg a_)
		-> typename std::remove_cvref<Out_>::type
	{
		i16x8 lane = min_i16x8(cast_i16x16_i16x8(a_), extract_i16x16_lane_i16x8<1>(a_));
		return horizontal_min_scalar_i16x8<Out_>(lane);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 max_i16x16(EmuSIMD::i16x16_arg a_, EmuSIMD::i16x16_arg b_)
	{
		return _mm256_max_epi16(a_, b_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 horizontal_max_i16x16(EmuSIMD::i16x16_arg a_)
	{
		i16x8 lane = max_i16x8(cast_i16x16_i16x8(a_), extract_i16x16_lane_i16x8<1>(a_));
		return cast_i16x8_i16x16(horizontal_max_i16x8(lane));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 horizontal_max_fill_i16x16(EmuSIMD::i16x16_arg a_)
	{
		i16x8 lane = max_i16x8(cast_i16x16_i16x8(a_), extract_i16x16_lane_i16x8<1>(a_));
		lane = horizontal_max_fill_i16x8(lane);
		return _mm256_inserti128_si256(cast_i16x8_i16x16(lane), lane, 1);
	}

	template<typename Out_>
	EMU_SIMD_COMMON_FUNC_SPEC auto horizontal_max_scalar_i16x16(EmuSIMD::i16x16_arg a_)
		-> typename std::remove_cvref<Out_>::type
	{
		i16x8 lane = max_i16x8(cast_i16x16_i16x8(a_), extract_i16x16_lane_i16x8<1>(a_));
		return horizontal_max_scalar_i16x8<Out_>(lane);
	}
#pragma endregion

#pragma region BASIC_ARITHMETIC
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 mul_all_i16x16(EmuSIMD::i16x16_arg lhs_, EmuSIMD::i16x16_arg rhs_)
	{
		return _mm256_mullo_epi16(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 negate_i16x16(EmuSIMD::i16x16_arg to_negate_)
	{
		return _mm256_sub_epi16(_mm256_setzero_si256(), to_negate_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 add_i16x16(EmuSIMD::i16x16_arg lhs_, EmuSIMD::i16x16_arg rhs_)
	{
		return _mm256_add_epi16(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 sub_i16x16(EmuSIMD::i16x16_arg lhs_, EmuSIMD::i16x16_arg rhs_)
	{
		return _mm256_sub_epi16(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 div_i16x16(EmuSIMD::i16x16_arg lhs_, EmuSIMD::i16x16_arg rhs_)
	{
#if EMU_CORE_X86_X64_SVML
		return _mm256_div_epi16(lhs_, rhs_);
#else
		// lo
		EmuSIMD::i32x8 lane64_a = cvt_i16x16_i32x8(lhs_);
		EmuSIMD::i32x8 lane64_b = cvt_i16x16_i32x8(rhs_);
		EmuSIMD::i16x16 lo = cvt_i32x8_i16x16(div_i32x8(lane64_a, lane64_b));

		// hi - move hi bits to lo
		EmuSIMD::i16x16 tmp_lane = movehl_i16x16(lhs_, lhs_);
		lane64_a = cvt_i16x16_i32x8(tmp_lane);

		tmp_lane = movehl_i16x16(rhs_, rhs_);
		lane64_b = cvt_i16x16_i32x8(tmp_lane);

		// Move hi and lo into the same register, in their respective 64-bit lanes
		EmuSIMD::i16x16 hi = cvt_i32x8_i16x16(div_i32x8(lane64_a, lane64_b));
		return movelh_i16x16(lo, hi);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 addsub_i16x16(EmuSIMD::i16x16_arg lhs_, EmuSIMD::i16x16_arg rhs_)
	{
		constexpr std::int16_t bytes_mask = static_cast<std::int16_t>(0xFFFF);
		const EmuSIMD::i16x16 mask = _mm256_set_epi16(bytes_mask, 0, bytes_mask, 0, bytes_mask, 0, bytes_mask, 0, bytes_mask, 0, bytes_mask, 0, bytes_mask, 0, bytes_mask, 0);
		EmuSIMD::i16x16 out = _mm256_add_epi16(lhs_, _mm256_and_si256(mask, rhs_));
		return _mm256_sub_epi16(lhs_, _mm256_andnot_si256(mask, rhs_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 subadd_i16x16(EmuSIMD::i16x16_arg lhs_, EmuSIMD::i16x16_arg rhs_)
	{
		constexpr std::int16_t bytes_mask = static_cast<std::int16_t>(0xFFFF);
		const EmuSIMD::i16x16 mask = _mm256_set_epi16(bytes_mask, 0, bytes_mask, 0, bytes_mask, 0, bytes_mask, 0, bytes_mask, 0, bytes_mask, 0, bytes_mask, 0, bytes_mask, 0);
		EmuSIMD::i16x16 out = _mm256_sub_epi16(lhs_, _mm256_and_si256(mask, rhs_));
		return _mm256_add_epi16(lhs_, _mm256_andnot_si256(mask, rhs_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 fmadd_i16x16(EmuSIMD::i16x16_arg a_, EmuSIMD::i16x16_arg b_, EmuSIMD::i16x16_arg c_)
	{
		return _mm256_add_epi16(mul_all_i16x16(a_, b_), c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 fmsub_i16x16(EmuSIMD::i16x16_arg a_, EmuSIMD::i16x16_arg b_, EmuSIMD::i16x16_arg c_)
	{
		return _mm256_sub_epi16(mul_all_i16x16(a_, b_), c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 fnmadd_i16x16(EmuSIMD::i16x16_arg a_, EmuSIMD::i16x16_arg b_, EmuSIMD::i16x16_arg c_)
	{
		return _mm256_add_epi16(mul_all_i16x16(negate_i16x16(a_), b_), c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 fnmsub_i16x16(EmuSIMD::i16x16_arg a_, EmuSIMD::i16x16_arg b_, EmuSIMD::i16x16_arg c_)
	{
		return _mm256_sub_epi16(mul_all_i16x16(negate_i16x16(a_), b_), c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 fmaddsub_i16x16(EmuSIMD::i16x16_arg a_, EmuSIMD::i16x16_arg b_, EmuSIMD::i16x16_arg c_)
	{
		return addsub_i16x16(mul_all_i16x16(a_, b_), c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 fmsubadd_i16x16(EmuSIMD::i16x16_arg a_, EmuSIMD::i16x16_arg b_, EmuSIMD::i16x16_arg c_)
	{
		return subadd_i16x16(mul_all_i16x16(a_, b_), c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 floor_i16x16(EmuSIMD::i16x16_arg to_floor_)
	{
		return to_floor_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 ceil_i16x16(EmuSIMD::i16x16_arg to_ceil_)
	{
		return to_ceil_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 trunc_i16x16(EmuSIMD::i16x16_arg to_trunc_)
	{
		return to_trunc_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 mod_i16x16(EmuSIMD::i16x16_arg lhs_, EmuSIMD::i16x16_arg rhs_)
	{
#if EMU_CORE_X86_X64_SVML
		return _mm256_rem_epi16(lhs_, rhs_);
#else
		EmuSIMD::i16x16 to_subtract = div_i16x16(lhs_, rhs_);
		to_subtract = mul_all_i16x16(to_subtract, rhs_);
		return sub_i16x16(lhs_, to_subtract);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 abs_i16x16(EmuSIMD::i16x16_arg in_)
	{
		return _mm256_abs_epi16(in_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 sqrt_i16x16(EmuSIMD::i16x16_arg in_)
	{
		return emulate_fp_i16x16([](EmuSIMD::f32x8_arg in_fp_) { return sqrt_f32x8(in_fp_); }, in_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 rsqrt_i16x16(EmuSIMD::i16x16_arg in_)
	{
		return emulate_fp_i16x16([](EmuSIMD::f32x8_arg in_fp_) { return rsqrt_f32x8(in_fp_); }, in_);
	}
#pragma endregion

#pragma region NEAR_COMPARISONS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cmpnear_i16x16(EmuSIMD::i16x16_arg lhs_, EmuSIMD::i16x16_arg rhs_)
	{
		return cmpeq_i16x16(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cmpnear_i16x16(EmuSIMD::i16x16_arg lhs_, EmuSIMD::i16x16_arg rhs_, EmuSIMD::i16x16_arg epsilon)
	{
		return cmple_i16x16(abs_i16x16(sub_i16x16(lhs_, rhs_)), epsilon);
	}
#pragma endregion

#pragma region TRIG
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 cos_i16x16(EmuSIMD::i16x16_arg in_)
	{
		return emulate_fp_i16x16([](EmuSIMD::f32x8_arg in_fp_) { return cos_f32x8(in_fp_); }, in_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 sin_i16x16(EmuSIMD::i16x16_arg in_)
	{
		return emulate_fp_i16x16([](EmuSIMD::f32x8_arg in_fp_) { return sin_f32x8(in_fp_); }, in_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 tan_i16x16(EmuSIMD::i16x16_arg in_)
	{
		return emulate_fp_i16x16([](EmuSIMD::f32x8_arg in_fp_) { return tan_f32x8(in_fp_); }, in_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 acos_i16x16(EmuSIMD::i16x16_arg in_)
	{
		return emulate_fp_i16x16([](EmuSIMD::f32x8_arg in_fp_) { return acos_f32x8(in_fp_); }, in_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 asin_i16x16(EmuSIMD::i16x16_arg in_)
	{
		return emulate_fp_i16x16([](EmuSIMD::f32x8_arg in_fp_) { return asin_f32x8(in_fp_); }, in_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i16x16 atan_i16x16(EmuSIMD::i16x16_arg in_)
	{
		return emulate_fp_i16x16([](EmuSIMD::f32x8_arg in_fp_) { return atan_f32x8(in_fp_); }, in_);
	}
#pragma endregion
}

#endif
