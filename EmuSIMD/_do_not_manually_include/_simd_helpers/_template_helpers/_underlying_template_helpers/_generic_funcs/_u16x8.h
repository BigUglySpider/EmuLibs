#ifndef EMU_SIMD_GENERIC_FUNCS_U16X8_H_INC_
#define EMU_SIMD_GENERIC_FUNCS_U16X8_H_INC_ 1

#include "_generic_declarations/_all_generic_declarations.h"
#include "_common_generic_func_helpers.h"

namespace EmuSIMD::Funcs
{
#pragma region SETTERS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 set_u16x8(std::uint16_t e0, std::uint16_t e1, std::uint16_t e2, std::uint16_t e3, std::uint16_t e4, std::uint16_t e5, std::uint16_t e6, std::uint16_t e7)
	{
		return _mm_set_epi16(e0, e1, e2, e3, e4, e5, e6, e7);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 setr_u16x8(std::uint16_t e0, std::uint16_t e1, std::uint16_t e2, std::uint16_t e3, std::uint16_t e4, std::uint16_t e5, std::uint16_t e6, std::uint16_t e7)
	{
		//return _mm_setr_epi16(e0, e1, e2, e3, e4, e5, e6, e7);
		return _mm_set_epi16(e7, e6, e5, e4, e3, e2, e1, e0);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 set1_u16x8(std::uint16_t all_)
	{
		return _mm_set1_epi16(all_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 load_u16x8(const std::uint16_t* p_to_load_)
	{
		return _mm_loadu_si128(reinterpret_cast<const __m128i*>(p_to_load_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 aligned_load_u16x8(const std::uint16_t* p_to_load_)
	{
		return _mm_load_si128(reinterpret_cast<const __m128i*>(p_to_load_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 setzero_u16x8()
	{
		return _mm_setzero_si128();
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 setmasked_u16x8(std::uint8_t bit_mask_)
	{
		constexpr std::uint16_t element_mask = static_cast<std::uint16_t>(0xFFFF);
		return _mm_set_epi16
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
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 setmasked_u16x8()
	{
		if constexpr(BitMask_ != 0)
		{
			return set_u16x8
			(
				std::integral_constant<std::uint16_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<0, std::uint16_t>(BitMask_)>::value,
				std::integral_constant<std::uint16_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<1, std::uint16_t>(BitMask_)>::value,
				std::integral_constant<std::uint16_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<2, std::uint16_t>(BitMask_)>::value,
				std::integral_constant<std::uint16_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<3, std::uint16_t>(BitMask_)>::value,
				std::integral_constant<std::uint16_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<4, std::uint16_t>(BitMask_)>::value,
				std::integral_constant<std::uint16_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<5, std::uint16_t>(BitMask_)>::value,
				std::integral_constant<std::uint16_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<6, std::uint16_t>(BitMask_)>::value,
				std::integral_constant<std::uint16_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<7, std::uint16_t>(BitMask_)>::value
			);
		}
		else
		{
			return setzero_u16x8();
		}
	}

	template<bool I0_, bool I1_, bool I2_, bool I3_, bool I4_, bool I5_, bool I6_, bool I7_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 set_index_mask_u16x8()
	{
		if constexpr(I0_ || I1_ || I2_ || I3_ || I4_ || I5_ || I6_ || I7_)
		{
			return setmasked_u16x8<EmuSIMD::Funcs::make_index_set_mask<I0_,  I1_,  I2_,  I3_,  I4_,  I5_,  I6_,  I7_>()>();
		}
		else
		{
			return setzero_u16x8();
		}
	}

	template<bool Active_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 set_index_mask_u16x8()
	{
		if constexpr (Active_)
		{
			return setmasked_u16x8<EmuSIMD::Funcs::make_all_indices_set_mask<8, Active_>()>();
		}
		else
		{
			return setzero_u16x8();
		}
	}
#pragma endregion

#pragma region STORES
	EMU_SIMD_COMMON_FUNC_SPEC void store_u16x8(std::uint16_t* p_out_, u16x8_arg a_)
	{
		_mm_storeu_si128(reinterpret_cast<__m128i*>(p_out_), a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC void aligned_store_u16x8(std::uint16_t* p_out_, u16x8_arg a_)
	{
		_mm_store_si128(reinterpret_cast<__m128i*>(p_out_), a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC std::uint16_t get_first_u16x8(u16x8_arg a_)
	{
		std::int32_t first_32_bits = _mm_cvtsi128_si32(a_);
		return *reinterpret_cast<std::uint16_t*>(&first_32_bits);
	}

	EMU_SIMD_COMMON_FUNC_SPEC std::uint8_t movemask_u16x8(u16x8_arg a_)
	{
		return EmuSIMD::Funcs::convert_movemask_width<16, 8, std::uint8_t>(_mm_movemask_epi8(a_));
	}
#pragma endregion

#pragma region CASTS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 cast_f32x4_u16x8(f32x4_arg a_)
	{
		return _mm_castps_si128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 cast_f32x8_u16x8(f32x8_arg a_)
	{
		return _mm256_castsi256_si128(_mm256_castps_si256(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 cast_f32x16_u16x8(f32x16_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_castsi512_si128(_mm512_castps_si512(a_));
#else
		return _underlying_impl::emulate_simd_cast_lesser_width<u16x8>(a_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 cast_f64x2_u16x8(f64x2_arg a_)
	{
		return _mm_castpd_si128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 cast_f64x4_u16x8(f64x4_arg a_)
	{
		return _mm256_castsi256_si128(_mm256_castpd_si256(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 cast_f64x8_u16x8(f64x8_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_castsi512_si128(_mm512_castpd_si512(a_));
#else
		return _underlying_impl::emulate_simd_cast_lesser_width<u16x8>(a_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 cast_i8x16_u16x8(i8x16_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 cast_i16x8_u16x8(i16x8_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 cast_i32x4_u16x8(i32x4_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 cast_i64x2_u16x8(i64x2_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 cast_i8x32_u16x8(i8x32_arg a_)
	{
		return _mm256_castsi256_si128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 cast_i16x16_u16x8(i16x16_arg a_)
	{
		return _mm256_castsi256_si128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 cast_i32x8_u16x8(i32x8_arg a_)
	{
		return _mm256_castsi256_si128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 cast_i64x4_u16x8(i64x4_arg a_)
	{
		return _mm256_castsi256_si128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 cast_i8x64_u16x8(i8x64_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_castsi512_si128(a_);
#else
		return _underlying_impl::emulate_simd_cast_lesser_width<u16x8>(a_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 cast_i16x32_u16x8(i16x32_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_castsi512_si128(a_);
#else
		return _underlying_impl::emulate_simd_cast_lesser_width<u16x8>(a_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 cast_i32x16_u16x8(i32x16_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_castsi512_si128(a_);
#else
		return _underlying_impl::emulate_simd_cast_lesser_width<u16x8>(a_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 cast_i64x8_u16x8(i64x8_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_castsi512_si128(a_);
#else
		return _underlying_impl::emulate_simd_cast_lesser_width<u16x8>(a_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 cast_u8x16_u16x8(u8x16_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 cast_u16x8_u16x8(u16x8_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 cast_u32x4_u16x8(u32x4_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 cast_u64x2_u16x8(u64x2_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 cast_u8x32_u16x8(u8x32_arg a_)
	{
		return _mm256_castsi256_si128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 cast_u16x16_u16x8(u16x16_arg a_)
	{
		return _mm256_castsi256_si128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 cast_u32x8_u16x8(u32x8_arg a_)
	{
		return _mm256_castsi256_si128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 cast_u64x4_u16x8(u64x4_arg a_)
	{
		return _mm256_castsi256_si128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 cast_u8x64_u16x8(u8x64_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_castsi512_si128(a_);
#else
		return _underlying_impl::emulate_simd_cast_lesser_width<u16x8>(a_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 cast_u16x32_u16x8(u16x32_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_castsi512_si128(a_);
#else
		return _underlying_impl::emulate_simd_cast_lesser_width<u16x8>(a_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 cast_u32x16_u16x8(u32x16_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_castsi512_si128(a_);
#else
		return _underlying_impl::emulate_simd_cast_lesser_width<u16x8>(a_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 cast_u64x8_u16x8(u64x8_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_castsi512_si128(a_);
#else
		return _underlying_impl::emulate_simd_cast_lesser_width<u16x8>(a_);
#endif
	}
#pragma endregion

#pragma region CONVERSIONS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 cvt_f32x4_u16x8(f32x4_arg a_)
	{
		return _mm_cvtepi32_epi16(_mm_cvtps_epi32(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 cvt_f32x8_u16x8(f32x8_arg a_)
	{
		return _mm256_cvtepi32_epi16(_mm256_cvtps_epi32(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 cvt_f32x16_u16x8(f32x16_arg a_)
	{
		return cvt_f32x8_u16x8(cast_f32x16_f32x8(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 cvt_f64x2_u16x8(f64x2_arg a_)
	{
		return _mm_cvtepi64_epi16(_mm_cvtpd_epi64(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 cvt_f64x4_u16x8(f64x4_arg a_)
	{
		return _mm256_cvtepi64_epi16(_mm256_cvtpd_epi64(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 cvt_f64x8_u16x8(f64x8_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_cvtepi64_epi16(_mm512_cvtpd_epi64(a_));
#else
		return EmuSIMD::_underlying_impl::emulate_cvt<u16x8, std::uint16_t, 16, false, 8, true, double>(a_, std::make_index_sequence<8>());
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 cvt_i8x16_u16x8(i8x16_arg a_)
	{
		return _mm_cvtepi8_epi16(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 cvt_i16x8_u16x8(i16x8_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 cvt_i32x4_u16x8(i32x4_arg a_)
	{
		return EmuSIMD::_underlying_impl::emulate_cvt<u16x8, std::uint16_t, 16, false, 4, true, std::int32_t>(a_, std::make_index_sequence<8>());
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 cvt_i64x2_u16x8(i64x2_arg a_)
	{
		return EmuSIMD::_underlying_impl::emulate_cvt<u16x8, std::uint16_t, 16, false, 2, true, std::int64_t>(a_, std::make_index_sequence<8>());
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 cvt_i8x32_u16x8(i8x32_arg a_)
	{
		return _mm256_castsi256_si128(_mm256_cvtepi8_epi16(_mm256_castsi256_si128(a_)));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 cvt_i16x16_u16x8(i16x16_arg a_)
	{
		return _mm256_castsi256_si128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 cvt_i32x8_u16x8(i32x8_arg a_)
	{
		return EmuSIMD::_underlying_impl::emulate_cvt<u16x8, std::uint16_t, 16, false, 8, true, std::int32_t>(a_, std::make_index_sequence<8>());
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 cvt_i64x4_u16x8(i64x4_arg a_)
	{
		return EmuSIMD::_underlying_impl::emulate_cvt<u16x8, std::uint16_t, 16, false, 4, true, std::int64_t>(a_, std::make_index_sequence<8>());
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 cvt_i8x64_u16x8(i8x64_arg a_)
	{
		return cvt_i8x16_u16x8(cast_i8x64_i8x16(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 cvt_i16x32_u16x8(i16x32_arg a_)
	{
		return cast_i16x32_u16x8(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 cvt_i32x16_u16x8(i32x16_arg a_)
	{
		return cvt_i32x8_u16x8(cast_i32x16_i32x8(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 cvt_i64x8_u16x8(i64x8_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_cvtepi64_epi16(a_);
#else
		return EmuSIMD::_underlying_impl::emulate_cvt<u16x8, std::uint16_t, 16, false, 8, true, std::int64_t>(a_, std::make_index_sequence<8>());
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 cvt_u8x16_u16x8(u8x16_arg a_)
	{
		return _mm_cvtepi8_epi16(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 cvt_u16x8_u16x8(u16x8_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 cvt_u32x4_u16x8(u32x4_arg a_)
	{
		return EmuSIMD::_underlying_impl::emulate_cvt<u16x8, std::uint16_t, 16, false, 4, false, std::uint32_t>(a_, std::make_index_sequence<8>());
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 cvt_u64x2_u16x8(u64x2_arg a_)
	{
		return EmuSIMD::_underlying_impl::emulate_cvt<u16x8, std::uint16_t, 16, false, 2, false, std::uint64_t>(a_, std::make_index_sequence<8>());
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 cvt_u8x32_u16x8(u8x32_arg a_)
	{
		return _mm256_castsi256_si128(_mm256_cvtepi8_epi16(_mm256_castsi256_si128(a_)));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 cvt_u16x16_u16x8(u16x16_arg a_)
	{
		return _mm256_castsi256_si128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 cvt_u32x8_u16x8(u32x8_arg a_)
	{
		return _mm256_cvtepi32_epi16(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 cvt_u64x4_u16x8(u64x4_arg a_)
	{
		return EmuSIMD::_underlying_impl::emulate_cvt<u16x8, std::uint16_t, 16, false, 4, false, std::uint64_t>(a_, std::make_index_sequence<8>());
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 cvt_u8x64_u16x8(u8x64_arg a_)
	{
		return cvt_u8x16_u16x8(cast_u8x64_u8x16(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 cvt_u16x32_u16x8(u16x32_arg a_)
	{
		return cast_u16x32_u16x8(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 cvt_u32x16_u16x8(u32x16_arg a_)
	{
		return cvt_u32x8_u16x8(cast_u32x16_u32x8(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 cvt_u64x8_u16x8(u64x8_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_cvtepi64_epi16(a_);
#else
		return EmuSIMD::_underlying_impl::emulate_cvt<u16x8, std::uint16_t, 16, false, 8, false, std::uint64_t>(a_, std::make_index_sequence<8>());
#endif
	}
#pragma endregion

#pragma region COMPARISONS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 cmpeq_u16x8(EmuSIMD::u16x8_arg lhs_, EmuSIMD::u16x8_arg rhs_)
	{
		return _mm_cmpeq_epi16(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 cmpneq_u16x8(EmuSIMD::u16x8_arg lhs_, EmuSIMD::u16x8_arg rhs_)
	{
		constexpr std::uint16_t mask = static_cast<std::uint16_t>(0xFFFF);
		return _mm_xor_si128(set1_i16x8(mask), _mm_cmpeq_epi16(lhs_, rhs_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 cmpgt_u16x8(EmuSIMD::u16x8_arg lhs_, EmuSIMD::u16x8_arg rhs_)
	{
		constexpr std::uint16_t mask = static_cast<std::uint16_t>(0xFFFF);
		return _mm_andnot_si128(_mm_cmpeq_epi16(_mm_min_epu16(lhs_, rhs_), lhs_), set1_u16x8(mask));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 cmplt_u16x8(EmuSIMD::u16x8_arg lhs_, EmuSIMD::u16x8_arg rhs_)
	{
		constexpr std::uint16_t mask = static_cast<std::uint16_t>(0xFFFF);
		return _mm_andnot_si128(_mm_cmpeq_epi16(_mm_max_epu16(lhs_, rhs_), lhs_), set1_u16x8(mask));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 cmpge_u16x8(EmuSIMD::u16x8_arg lhs_, EmuSIMD::u16x8_arg rhs_)
	{
		return _mm_cmpeq_epi16(_mm_max_epu16(lhs_, rhs_), lhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 cmple_u16x8(EmuSIMD::u16x8_arg lhs_, EmuSIMD::u16x8_arg rhs_)
	{
		return _mm_cmpeq_epi16(_mm_min_epu16(lhs_, rhs_), lhs_);
	}
#pragma endregion

#pragma region MOVES
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 movehl_u16x8(EmuSIMD::u16x8_arg lhs_, EmuSIMD::u16x8_arg rhs_)
	{
		return cast_f32x4_u16x8(movehl_f32x4(cast_u16x8_f32x4(lhs_), cast_u16x8_f32x4(rhs_)));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 movelh_u16x8(EmuSIMD::u16x8_arg lhs_, EmuSIMD::u16x8_arg rhs_)
	{
		return cast_f32x4_u16x8(movelh_f32x4(cast_u16x8_f32x4(lhs_), cast_u16x8_f32x4(rhs_)));
	}
#pragma endregion

#pragma region BITWISE_ARITHMETIC
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 and_u16x8(EmuSIMD::u16x8_arg lhs_, EmuSIMD::u16x8_arg rhs_)
	{
#if EMU_SIMD_USE_128_REGISTERS
		return _mm_and_si128(lhs_, rhs_);
#else
		using EmuSIMD::_underlying_impl::emulate_simd_basic;
		using index_sequence = std::make_index_sequence<8>;
		return emulate_simd_basic(EmuCore::do_bitwise_and<std::uint16_t>(), lhs_, rhs_, index_sequence());
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 or_u16x8(EmuSIMD::u16x8_arg lhs_, EmuSIMD::u16x8_arg rhs_)
	{
#if EMU_SIMD_USE_128_REGISTERS
		return _mm_or_si128(lhs_, rhs_);
#else
		using EmuSIMD::_underlying_impl::emulate_simd_basic;
		using index_sequence = std::make_index_sequence<8>;
		return emulate_simd_basic(EmuCore::do_bitwise_or<std::uint16_t>(), lhs_, rhs_, index_sequence());
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 xor_u16x8(EmuSIMD::u16x8_arg lhs_, EmuSIMD::u16x8_arg rhs_)
	{
#if EMU_SIMD_USE_128_REGISTERS
		return _mm_xor_si128(lhs_, rhs_);
#else
		using EmuSIMD::_underlying_impl::emulate_simd_basic;
		using index_sequence = std::make_index_sequence<8>;
		return emulate_simd_basic(EmuCore::do_bitwise_xor<std::uint16_t>(), lhs_, rhs_, index_sequence());
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 andnot_u16x8(EmuSIMD::u16x8_arg not_lhs_, EmuSIMD::u16x8_arg rhs_)
	{
#if EMU_SIMD_USE_128_REGISTERS
		return _mm_andnot_si128(not_lhs_, rhs_);
#else
		using EmuSIMD::_underlying_impl::emulate_simd_basic;
		using index_sequence = std::make_index_sequence<8>;
		return emulate_simd_basic(EmuCore::do_bitwise_andnot<std::uint16_t>(), not_lhs_, rhs_, index_sequence());
#endif
	}

	template<std::int32_t NumShifts_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 shift_left_u16x8(EmuSIMD::u16x8_arg lhs_)
	{
		if constexpr (NumShifts_ >= 16)
		{
			return setzero_u16x8();
		}
		else
		{
#if EMU_SIMD_USE_128_REGISTERS
			return _mm_slli_epi16(lhs_, NumShifts_);
#else
			using EmuSIMD::_underlying_impl::emulate_simd_basic;
			using index_sequence = std::make_index_sequence<8>;
			auto func = [](const std::uint16_t& a_) { return (a_ << NumShifts_); };
			return emulate_simd_basic(func, lhs_, index_sequence());
#endif
		}

	}

	template<std::int32_t NumShifts_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 shift_right_arithmetic_u16x8(EmuSIMD::u16x8_arg lhs_)
	{
		// No sign bit, so same as logical shift
		return shift_right_logical_u16x8<NumShifts_>(lhs_);
	}

	template<std::int32_t NumShifts_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 shift_right_logical_u16x8(EmuSIMD::u16x8_arg lhs_)
	{
		if constexpr (NumShifts_ >= 16)
		{
			return setzero_u16x8();
		}
		else
		{
#if EMU_SIMD_USE_128_REGISTERS
			return _mm_srli_epi16(lhs_, NumShifts_);
#else
			using EmuSIMD::_underlying_impl::emulate_simd_basic;
			using index_sequence = std::make_index_sequence<8>;
			auto func = [](const std::uint16_t& a_) { return (a_ >> NumShifts_); };
			return emulate_simd_basic(func, lhs_, index_sequence());
#endif
		}
	}
#pragma endregion

#pragma region BLENDS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 blendv_u16x8(EmuSIMD::u16x8_arg a_, EmuSIMD::u16x8_arg b_, EmuSIMD::u16x8_arg shuffle_mask_vec_)
	{
		return _mm_blendv_epi8
		(
			a_,
			b_,
			blend_mask_vector_16_to_8(shuffle_mask_vec_)
		);
	}
#pragma endregion

#pragma region MINMAX_FUNCS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 min_u16x8(EmuSIMD::u16x8_arg a_, EmuSIMD::u16x8_arg b_)
	{
		return _mm_min_epu16(a_, b_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 horizontal_min_u16x8(EmuSIMD::u16x8_arg a_)
	{
		EmuSIMD::u16x8 result = movelh_u16x8(a_, a_);
		result = min_u16x8(result, a_);
		EmuSIMD::u32x4 last_4_result = cvt_u16x8_u32x4(result);
		last_4_result = horizontal_min_u32x4(last_4_result);
		return cvt_u32x4_u16x8(last_4_result);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 horizontal_min_fill_u16x8(EmuSIMD::u16x8_arg a_)
	{
		constexpr auto all_el0_mask = make_shuffle_mask_16<0, 0, 0, 0, 0, 0, 0, 0>();
		return permute_u16x8<all_el0_mask>(horizontal_min_u16x8(a_));
	}

	template<typename Out_>
	EMU_SIMD_COMMON_FUNC_SPEC auto horizontal_min_scalar_u16x8(EmuSIMD::u16x8_arg a_)
		-> typename std::remove_cvref<Out_>::type
	{
		return static_cast<typename std::remove_cvref<Out_>::type>(get_first_u16x8(horizontal_min_u16x8(a_)));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 max_u16x8(EmuSIMD::u16x8_arg a_, EmuSIMD::u16x8_arg b_)
	{
		return _mm_max_epu16(a_, b_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 horizontal_max_u16x8(EmuSIMD::u16x8_arg a_)
	{
		EmuSIMD::u16x8 result = movelh_u16x8(a_, a_);
		result = max_u16x8(result, a_);
		EmuSIMD::u32x4 last_4_result = cvt_u16x8_u32x4(result);
		last_4_result = horizontal_max_u32x4(last_4_result);
		return cvt_u32x4_u16x8(last_4_result);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 horizontal_max_fill_u16x8(EmuSIMD::u16x8_arg a_)
	{
		constexpr auto all_el0_mask = make_shuffle_mask_16<0, 0, 0, 0, 0, 0, 0, 0>();
		return permute_u16x8<all_el0_mask>(horizontal_max_u16x8(a_));
	}

	template<typename Out_>
	EMU_SIMD_COMMON_FUNC_SPEC auto horizontal_max_scalar_u16x8(EmuSIMD::u16x8_arg a_)
		-> typename std::remove_cvref<Out_>::type
	{
		return static_cast<typename std::remove_cvref<Out_>::type>(get_first_u16x8(horizontal_max_u16x8(a_)));
	}
#pragma endregion

#pragma region BASIC_ARITHMETIC
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 mul_all_u16x8(EmuSIMD::u16x8_arg lhs_, EmuSIMD::u16x8_arg rhs_)
	{
		return _mm_mullo_epi16(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 negate_u16x8(EmuSIMD::u16x8_arg to_negate_)
	{
		return _mm_sub_epi16(_mm_setzero_si128(), to_negate_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 add_u16x8(EmuSIMD::u16x8_arg lhs_, EmuSIMD::u16x8_arg rhs_)
	{
		return _mm_add_epi16(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 sub_u16x8(EmuSIMD::u16x8_arg lhs_, EmuSIMD::u16x8_arg rhs_)
	{
		return _mm_sub_epi16(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 div_u16x8(EmuSIMD::u16x8_arg lhs_, EmuSIMD::u16x8_arg rhs_)
	{
#if EMU_CORE_X86_X64_SVML
		return _mm_div_epu16(lhs_, rhs_);
#else
		// lo
		EmuSIMD::i32x4 lane64_a = cvt_u16x8_u32x4(lhs_);
		EmuSIMD::i32x4 lane64_b = cvt_u16x8_u32x4(rhs_);
		EmuSIMD::i16x8 lo = cvt_u32x4_u16x8(div_u32x4(lane64_a, lane64_b));

		// hi - move hi bits to lo
		EmuSIMD::i16x8 tmp_lane = movehl_u16x8(lhs_, lhs_);
		lane64_a = cvt_u16x8_u32x4(tmp_lane);

		tmp_lane = movehl_u16x8(rhs_, rhs_);
		lane64_b = cvt_u16x8_u32x4(tmp_lane);

		// Move hi and lo into the same register, in their respective 64-bit lanes
		EmuSIMD::i16x8 hi = cvt_u32x4_u16x8(div_u32x4(lane64_a, lane64_b));
		return movelh_u16x8(lo, hi);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 addsub_u16x8(EmuSIMD::u16x8_arg lhs_, EmuSIMD::u16x8_arg rhs_)
	{
		constexpr std::uint16_t bytes_mask = static_cast<std::uint16_t>(0xFFFF);
		const EmuSIMD::u16x8 mask = _mm_set_epi16(bytes_mask, 0, bytes_mask, 0, bytes_mask, 0, bytes_mask, 0);
		EmuSIMD::u16x8 out = _mm_add_epi16(lhs_, _mm_and_si128(mask, rhs_));
		return _mm_sub_epi16(lhs_, _mm_andnot_si128(mask, rhs_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 subadd_u16x8(EmuSIMD::u16x8_arg lhs_, EmuSIMD::u16x8_arg rhs_)
	{
		constexpr std::uint16_t bytes_mask = static_cast<std::uint16_t>(0xFFFF);
		const EmuSIMD::u16x8 mask = _mm_set_epi16(bytes_mask, 0, bytes_mask, 0, bytes_mask, 0, bytes_mask, 0);
		EmuSIMD::u16x8 out = _mm_sub_epi16(lhs_, _mm_and_si128(mask, rhs_));
		return _mm_add_epi16(lhs_, _mm_andnot_si128(mask, rhs_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 fmadd_u16x8(EmuSIMD::u16x8_arg a_, EmuSIMD::u16x8_arg b_, EmuSIMD::u16x8_arg c_)
	{
		return _mm_add_epi16(mul_all_u16x8(a_, b_), c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 fmsub_u16x8(EmuSIMD::u16x8_arg a_, EmuSIMD::u16x8_arg b_, EmuSIMD::u16x8_arg c_)
	{
		return _mm_sub_epi16(mul_all_u16x8(a_, b_), c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 fnmadd_u16x8(EmuSIMD::u16x8_arg a_, EmuSIMD::u16x8_arg b_, EmuSIMD::u16x8_arg c_)
	{
		return _mm_add_epi16(mul_all_u16x8(negate_u16x8(a_), b_), c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 fnmsub_u16x8(EmuSIMD::u16x8_arg a_, EmuSIMD::u16x8_arg b_, EmuSIMD::u16x8_arg c_)
	{
		return _mm_sub_epi16(mul_all_u16x8(negate_u16x8(a_), b_), c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 fmaddsub_u16x8(EmuSIMD::u16x8_arg a_, EmuSIMD::u16x8_arg b_, EmuSIMD::u16x8_arg c_)
	{
		return addsub_u16x8(mul_all_u16x8(a_, b_), c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 fmsubadd_u16x8(EmuSIMD::u16x8_arg a_, EmuSIMD::u16x8_arg b_, EmuSIMD::u16x8_arg c_)
	{
		return subadd_u16x8(mul_all_u16x8(a_, b_), c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 floor_u16x8(EmuSIMD::u16x8_arg to_floor_)
	{
		return to_floor_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 ceil_u16x8(EmuSIMD::u16x8_arg to_ceil_)
	{
		return to_ceil_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 trunc_u16x8(EmuSIMD::u16x8_arg to_trunc_)
	{
		return to_trunc_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 mod_u16x8(EmuSIMD::u16x8_arg lhs_, EmuSIMD::u16x8_arg rhs_)
	{
#if EMU_CORE_X86_X64_SVML
		return _mm256_rem_epu16(lhs_, rhs_);
#else
		EmuSIMD::u16x8 to_subtract = div_u16x8(lhs_, rhs_);
		to_subtract = mul_all_u16x8(to_subtract, rhs_);
		return sub_u16x8(lhs_, to_subtract);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 abs_u16x8(EmuSIMD::u16x8_arg in_)
	{
		return in_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 sqrt_u16x8(EmuSIMD::u16x8_arg in_)
	{
		return emulate_fp_u16x8([](EmuSIMD::f32x4_arg in_fp_) { return sqrt_f32x4(in_fp_); }, in_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 rsqrt_u16x8(EmuSIMD::u16x8_arg in_)
	{
		return emulate_fp_u16x8([](EmuSIMD::f32x4_arg in_fp_) { return rsqrt_f32x4(in_fp_); }, in_);
	}
#pragma endregion

#pragma region NEAR_COMPARISONS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 cmpnear_u16x8(EmuSIMD::u16x8_arg lhs_, EmuSIMD::u16x8_arg rhs_)
	{
		return cmpeq_u16x8(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 cmpnear_u16x8(EmuSIMD::u16x8_arg lhs_, EmuSIMD::u16x8_arg rhs_, EmuSIMD::u16x8_arg epsilon)
	{
		return cmple_u16x8(sub_u16x8(lhs_, rhs_), epsilon);
	}
#pragma endregion

#pragma region TRIG
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 cos_u16x8(EmuSIMD::u16x8_arg in_)
	{
		return emulate_fp_u16x8([](EmuSIMD::f32x4_arg in_fp_) { return cos_f32x4(in_fp_); }, in_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 sin_u16x8(EmuSIMD::u16x8_arg in_)
	{
		return emulate_fp_u16x8([](EmuSIMD::f32x4_arg in_fp_) { return sin_f32x4(in_fp_); }, in_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 tan_u16x8(EmuSIMD::u16x8_arg in_)
	{
		return emulate_fp_u16x8([](EmuSIMD::f32x4_arg in_fp_) { return tan_f32x4(in_fp_); }, in_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 acos_u16x8(EmuSIMD::u16x8_arg in_)
	{
		return emulate_fp_u16x8([](EmuSIMD::f32x4_arg in_fp_) { return acos_f32x4(in_fp_); }, in_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 asin_u16x8(EmuSIMD::u16x8_arg in_)
	{
		return emulate_fp_u16x8([](EmuSIMD::f32x4_arg in_fp_) { return asin_f32x4(in_fp_); }, in_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x8 atan_u16x8(EmuSIMD::u16x8_arg in_)
	{
		return emulate_fp_u16x8([](EmuSIMD::f32x4_arg in_fp_) { return atan_f32x4(in_fp_); }, in_);
	}
#pragma endregion
}

#endif
