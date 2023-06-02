#ifndef EMU_SIMD_GENERIC_FUNCS_U64X8_H_INC_
#define EMU_SIMD_GENERIC_FUNCS_U64X8_H_INC_ 1

#include "_generic_declarations/_all_generic_declarations.h"
#include "_common_generic_func_helpers.h"

namespace EmuSIMD::Funcs
{
#pragma region SETTERS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 set_u64x8
	(
		std::uint64_t e0, std::uint64_t e1, std::uint64_t e2, std::uint64_t e3, std::uint64_t e4, std::uint64_t e5, std::uint64_t e6, std::uint64_t e7
	)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_set_epi64(e0, e1, e2, e3, e4, e5, e6, e7);
#else
		return EmuSIMD::_underlying_impl::set_dual_lane_simd_emulator<false, 512, u64x4>(e0, e1, e2, e3, e4, e5, e6, e7);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 setr_u64x8
	(
		std::uint64_t e0, std::uint64_t e1, std::uint64_t e2, std::uint64_t e3, std::uint64_t e4, std::uint64_t e5, std::uint64_t e6, std::uint64_t e7
	)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_set_epi64(e7, e6, e5, e4, e3, e2, e1, e0);
#else
		return EmuSIMD::_underlying_impl::set_dual_lane_simd_emulator<true, 512, u64x4>(e0, e1, e2, e3, e4, e5, e6, e7);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 set1_u64x8(std::uint64_t all_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_set1_epi64(all_);
#else
		return EmuSIMD::_underlying_impl::set1_dual_lane_simd_emulator<512, u64x4, 64>(all_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 load_u64x8(const std::uint64_t* p_to_load_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_loadu_si512(p_to_load_);
#else
		return EmuSIMD::_underlying_impl::load_dual_lane_simd_emulator<512, u64x4>(p_to_load_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 aligned_load_u64x8(const std::uint64_t* p_to_load_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_load_si512(p_to_load_);
#else
		return EmuSIMD::_underlying_impl::load_dual_lane_simd_emulator<512, u64x4>(p_to_load_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 setzero_u64x8()
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_setzero_si512();
#else
		return EmuSIMD::_underlying_impl::set_dual_lane_simd_emulator<512, u64x4>();
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 setmasked_u64x8(std::uint8_t bit_mask_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		constexpr std::uint64_t element_mask = static_cast<std::uint64_t>(0xFFFFFFFFFFFFFFFF);
		return _mm512_set_epi64
		(
			static_cast<std::uint64_t>(bit_mask_ & 0x01) * element_mask,
			static_cast<std::uint64_t>((bit_mask_ & 0x02) >> 1) * element_mask,
			static_cast<std::uint64_t>((bit_mask_ & 0x04) >> 2) * element_mask,
			static_cast<std::uint64_t>((bit_mask_ & 0x08) >> 3) * element_mask,
			static_cast<std::uint64_t>((bit_mask_ & 0x10) >> 4) * element_mask,
			static_cast<std::uint64_t>((bit_mask_ & 0x20) >> 5) * element_mask,
			static_cast<std::uint64_t>((bit_mask_ & 0x40) >> 6) * element_mask,
			static_cast<std::uint64_t>((bit_mask_ & 0x80) >> 7) * element_mask
		);
#else
		return EmuSIMD::_underlying_impl::setmasked_dual_lane_simd_emulator<512, u64x4, 8, std::uint8_t>(bit_mask_, [](std::uint8_t lane_mask) { return setmasked_u64x4(lane_mask); });
#endif
	}

	template<std::uint8_t BitMask_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 setmasked_u64x8()
	{
		if constexpr(BitMask_ != 0)
		{
#if EMU_SIMD_USE_512_REGISTERS
			return set_u64x8
			(
				std::integral_constant<std::uint64_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<0,  std::uint64_t>(BitMask_)>::value,
				std::integral_constant<std::uint64_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<1,  std::uint64_t>(BitMask_)>::value,
				std::integral_constant<std::uint64_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<2,  std::uint64_t>(BitMask_)>::value,
				std::integral_constant<std::uint64_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<3,  std::uint64_t>(BitMask_)>::value,
				std::integral_constant<std::uint64_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<4,  std::uint64_t>(BitMask_)>::value,
				std::integral_constant<std::uint64_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<5,  std::uint64_t>(BitMask_)>::value,
				std::integral_constant<std::uint64_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<6,  std::uint64_t>(BitMask_)>::value,
				std::integral_constant<std::uint64_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<7,  std::uint64_t>(BitMask_)>::value
			);
#else
			auto lane_setmasked = []<std::uint8_t lane_mask>() { return setmasked_u64x4<lane_mask>(); };
			return EmuSIMD::_underlying_impl::setmasked_dual_lane_simd_emulator<BitMask_, 512, u64x4, 8, std::uint8_t>(lane_setmasked);
#endif
		}
		else
		{
			return setzero_u64x8();
		}
	}

	template<bool I0_, bool I1_, bool I2_, bool I3_, bool I4_, bool I5_, bool I6_, bool I7_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 set_index_mask_u64x8()
	{
		if constexpr(I0_ || I1_ || I2_ || I3_ || I4_ || I5_ || I6_ || I7_)
		{
			return setmasked_u64x8<EmuSIMD::Funcs::make_index_set_mask<I0_, I1_, I2_, I3_, I4_, I5_, I6_, I7_>()>();
		}
		else
		{
			return setzero_u64x8();
		}
	}

	template<bool Active_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 set_index_mask_u64x8()
	{
		if constexpr (Active_)
		{
			return setmasked_u64x8<EmuSIMD::Funcs::make_all_indices_set_mask<8, Active_>()>();
		}
		else
		{
			return setzero_u64x8();
		}
	}
#pragma endregion

#pragma region STORES
	EMU_SIMD_COMMON_FUNC_SPEC void store_u64x8(std::uint64_t* p_out_, u64x8_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		_mm512_storeu_si512(reinterpret_cast<__m256i*>(p_out_), a_);
#else
		EmuSIMD::_underlying_impl::emulate_simd_store(a_, p_out_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC void aligned_store_u64x8(std::uint64_t* p_out_, u64x8_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		_mm512_store_si512(reinterpret_cast<__m256i*>(p_out_), a_);
#else
		EmuSIMD::_underlying_impl::emulate_simd_store(a_, p_out_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC std::uint64_t get_first_u64x8(u64x8_arg a_)
	{
		return get_first_u64x2(cast_u64x8_u64x2(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC std::uint8_t movemask_u64x8(u64x8_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return static_cast<std::uint8_t>(_mm512_movepi64_mask(a_));
#else
		return EmuSIMD::_underlying_impl::emulate_simd_movemask<std::uint8_t, 8>(a_);
#endif
	}
#pragma endregion

#pragma region CASTS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 cast_f32x4_u64x8(f32x4_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_castsi128_si512(_mm_castps_si128(a_));
#else
		return EmuSIMD::_underlying_impl::emulate_simd_cast_greater_width<u64x8>(a_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 cast_f32x8_u64x8(f32x8_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_castsi256_si512(_mm256_castps_si256(a_));
#else
		return EmuSIMD::_underlying_impl::emulate_simd_cast_greater_width<u64x8>(a_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 cast_f32x16_u64x8(f32x16_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_castps_si512(a_);
#else
		return EmuSIMD::_underlying_impl::emulate_simd_cast_same_width<u64x4>(a_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 cast_f64x2_u64x8(f64x2_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_castsi128_si512(_mm_castpd_si128(a_));
#else
		return EmuSIMD::_underlying_impl::emulate_simd_cast_greater_width<u64x8>(a_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 cast_f64x4_u64x8(f64x4_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_castsi256_si512(_mm256_castpd_si256(a_));
#else
		return EmuSIMD::_underlying_impl::emulate_simd_cast_greater_width<u64x8>(a_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 cast_f64x8_u64x8(f64x8_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_castpd_si512(a_);
#else
		return EmuSIMD::_underlying_impl::emulate_simd_cast_same_width<u64x4>(a_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 cast_i8x16_u64x8(i8x16_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_castsi128_si512(a_);
#else
		return EmuSIMD::_underlying_impl::emulate_simd_cast_greater_width<u64x8>(a_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 cast_i16x8_u64x8(i16x8_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_castsi128_si512(a_);
#else
		return EmuSIMD::_underlying_impl::emulate_simd_cast_greater_width<u64x8>(a_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 cast_i32x4_u64x8(i32x4_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_castsi128_si512(a_);
#else
		return EmuSIMD::_underlying_impl::emulate_simd_cast_greater_width<u64x8>(a_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 cast_i64x2_u64x8(i64x2_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_castsi128_si512(a_);
#else
		return EmuSIMD::_underlying_impl::emulate_simd_cast_greater_width<u64x8>(a_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 cast_i8x32_u64x8(i8x32_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_castsi256_si512(a_);
#else
		return EmuSIMD::_underlying_impl::emulate_simd_cast_greater_width<u64x8>(a_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 cast_i16x16_u64x8(i16x16_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_castsi256_si512(a_);
#else
		return EmuSIMD::_underlying_impl::emulate_simd_cast_greater_width<u64x8>(a_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 cast_i32x8_u64x8(i32x8_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_castsi256_si512(a_);
#else
		return EmuSIMD::_underlying_impl::emulate_simd_cast_greater_width<u64x8>(a_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 cast_i64x4_u64x8(i64x4_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_castsi256_si512(a_);
#else
		return EmuSIMD::_underlying_impl::emulate_simd_cast_greater_width<u64x8>(a_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 cast_i8x64_u64x8(i8x64_arg a_)
	{
#if EMU_SIMD_USE_128_REGISTERS && EMU_SIMD_USE_GENERIC_INT_REGISTERS
		return a_;
#else
		return EmuSIMD::_underlying_impl::emulate_simd_cast_same_width<u64x4>(a_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 cast_i16x32_u64x8(i16x32_arg a_)
	{
#if EMU_SIMD_USE_128_REGISTERS && EMU_SIMD_USE_GENERIC_INT_REGISTERS
		return a_;
#else
		return EmuSIMD::_underlying_impl::emulate_simd_cast_same_width<u64x4>(a_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 cast_i32x16_u64x8(i32x16_arg a_)
	{
#if EMU_SIMD_USE_128_REGISTERS && EMU_SIMD_USE_GENERIC_INT_REGISTERS
		return a_;
#else
		return EmuSIMD::_underlying_impl::emulate_simd_cast_same_width<u64x4>(a_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 cast_i64x8_u64x8(i64x8_arg a_)
	{
#if EMU_SIMD_USE_128_REGISTERS && EMU_SIMD_USE_GENERIC_INT_REGISTERS
		return a_;
#else
		return EmuSIMD::_underlying_impl::emulate_simd_cast_same_width<u64x4>(a_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 cast_u8x16_u64x8(u8x16_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_castsi128_si512(a_);
#else
		return EmuSIMD::_underlying_impl::emulate_simd_cast_greater_width<u64x8>(a_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 cast_u16x8_u64x8(u16x8_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_castsi128_si512(a_);
#else
		return EmuSIMD::_underlying_impl::emulate_simd_cast_greater_width<u64x8>(a_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 cast_u32x4_u64x8(u32x4_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_castsi128_si512(a_);
#else
		return EmuSIMD::_underlying_impl::emulate_simd_cast_greater_width<u64x8>(a_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 cast_u64x2_u64x8(u64x2_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_castsi128_si512(a_);
#else
		return EmuSIMD::_underlying_impl::emulate_simd_cast_greater_width<u64x8>(a_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 cast_u8x32_u64x8(u8x32_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_castsi256_si512(a_);
#else
		return EmuSIMD::_underlying_impl::emulate_simd_cast_greater_width<u64x8>(a_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 cast_u16x16_u64x8(u16x16_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_castsi256_si512(a_);
#else
		return EmuSIMD::_underlying_impl::emulate_simd_cast_greater_width<u64x8>(a_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 cast_u32x8_u64x8(u32x8_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_castsi256_si512(a_);
#else
		return EmuSIMD::_underlying_impl::emulate_simd_cast_greater_width<u64x8>(a_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 cast_u64x4_u64x8(u64x4_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_castsi256_si512(a_);
#else
		return EmuSIMD::_underlying_impl::emulate_simd_cast_greater_width<u64x8>(a_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 cast_u8x64_u64x8(u8x64_arg a_)
	{
#if EMU_SIMD_USE_128_REGISTERS && EMU_SIMD_USE_GENERIC_INT_REGISTERS
		return a_;
#else
		return EmuSIMD::_underlying_impl::emulate_simd_cast_same_width<u64x4>(a_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 cast_u16x32_u64x8(u16x32_arg a_)
	{
#if EMU_SIMD_USE_128_REGISTERS && EMU_SIMD_USE_GENERIC_INT_REGISTERS
		return a_;
#else
		return EmuSIMD::_underlying_impl::emulate_simd_cast_same_width<u64x4>(a_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 cast_u32x16_u64x8(u32x16_arg a_)
	{
#if EMU_SIMD_USE_128_REGISTERS && EMU_SIMD_USE_GENERIC_INT_REGISTERS
		return a_;
#else
		return EmuSIMD::_underlying_impl::emulate_simd_cast_same_width<u64x4>(a_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 cast_u64x8_u64x8(u64x8_arg a_)
	{
		return a_;
	}
#pragma endregion

#pragma region CONVERSIONS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 cvt_f32x4_u64x8(f32x4_arg a_)
	{
		return cast_u64x4_u64x8(cvt_f32x4_u64x4(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 cvt_f32x8_u64x8(f32x8_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_cvtps_epu64(a_);
#elif EMU_SIMD_USE_256_REGISTERS
		u64x4 lo = cvt_f32x4_u64x4(cast_f32x8_f32x4(a_));
		u64x4 hi = cvt_f32x4_u64x4(cast_f32x8_f32x4(movehl_f32x8(a_, a_)));
		return u64x8(lo, hi);
#else
		return EmuSIMD::_underlying_impl::emulate_cvt<u64x8, std::uint64_t, 64, false, 8, true, float>(a_, std::make_index_sequence<8>());
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 cvt_f32x16_u64x8(f32x16_arg a_)
	{
#if EMU_SIMD_USES_ANY_SIMD_REGISTERS
		return cvt_f32x8_u64x8(cast_f32x16_f32x8(a_));
#else
		return EmuSIMD::_underlying_impl::emulate_cvt<u64x8, std::uint64_t, 64, false, 16, true, float>(a_, std::make_index_sequence<8>());
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 cvt_f64x2_u64x8(f64x2_arg a_)
	{
#if EMU_SIMD_USE_128_REGISTERS
		return cast_u64x2_u64x8(cvt_f64x2_u64x2(a_));
#else
		return EmuSIMD::_underlying_impl::emulate_cvt<u64x8, std::uint64_t, 64, false, 2, true, double>(a_, std::make_index_sequence<8>());
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 cvt_f64x4_u64x8(f64x4_arg a_)
	{
#if EMU_SIMD_USE_256_REGISTERS
		return cast_u64x4_u64x8(cvt_f64x4_u64x4(a_));
#else
		return EmuSIMD::_underlying_impl::emulate_cvt<u64x8, std::uint64_t, 64, false, 4, true, double>(a_, std::make_index_sequence<8>());
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 cvt_f64x8_u64x8(f64x8_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_cvtpd_epu64(a_);
#else
		return EmuSIMD::_underlying_impl::emulate_cvt<u64x8, std::uint64_t, 64, false, 8, true, double>(a_, std::make_index_sequence<8>());
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 cvt_i8x16_u64x8(i8x16_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_cvtepi8_epi64(a_);
#else
		return EmuSIMD::_underlying_impl::emulate_cvt<u64x8, std::uint64_t, 64, false, 16, true, std::int8_t>(a_, std::make_index_sequence<8>());
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 cvt_i16x8_u64x8(i16x8_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_cvtepi16_epi64(a_);
#elif EMU_SIMD_USE_256_REGISTERS
		u64x4 lo = _mm256_cvtepi16_epi64(a_);
		u64x4 hi = _mm256_cvtepi16_epi64(movehl_i16x8(a_, a_));
		return u64x8(lo, hi);
#else
		return EmuSIMD::_underlying_impl::emulate_cvt<u64x8, std::uint64_t, 64, false, 8, true, std::int16_t>(a_, std::make_index_sequence<8>());
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 cvt_i32x4_u64x8(i32x4_arg a_)
	{
#if EMU_SIMD_USE_256_REGISTERS
		return cast_u64x4_u64x8(_mm256_cvtepi32_epi64(a_));
#elif EMU_SIMD_USE_128_REGISTERS
		u64x2 lo_lo = _mm_cvtepi32_epi64(a_);
		u64x2 lo_hi = _mm_cvtepi32_epi64(movehl_i32x4(a_, a_));
		return u64x8(u64x4(lo_lo, lo_hi)); // { a_, zero }
#else
		return EmuSIMD::_underlying_impl::emulate_cvt<u64x8, std::uint64_t, 64, false, 4, true, std::int32_t>(a_, std::make_index_sequence<8>());
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 cvt_i64x2_u64x8(i64x2_arg a_)
	{
		return cast_i64x2_u64x8(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 cvt_i8x32_u64x8(i8x32_arg a_)
	{
#if EMU_SIMD_USES_ANY_SIMD_REGISTERS
		return cvt_i8x16_u64x8(cast_i8x32_i8x16(a_));
#else
		return EmuSIMD::_underlying_impl::emulate_cvt<u64x8, std::uint64_t, 64, false, 32, true, std::int8_t>(a_, std::make_index_sequence<8>());
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 cvt_i16x16_u64x8(i16x16_arg a_)
	{
#if EMU_SIMD_USES_ANY_SIMD_REGISTERS
		return cvt_i16x8_u64x8(cast_i16x16_i16x8(a_));
#else
		return EmuSIMD::_underlying_impl::emulate_cvt<u64x8, std::uint64_t, 64, false, 16, true, std::int16_t>(a_, std::make_index_sequence<8>());
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 cvt_i32x8_u64x8(i32x8_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_cvtepi32_epi64(a_);
#elif EMU_SIMD_USE_256_REGISTERS
		u64x4 lo = _mm256_cvtepi32_epi64(cast_i32x8_i32x4(a_));
		u64x4 hi = _mm256_cvtepi32_epi64(cast_i32x8_i32x4(movehl_i32x8(a_, a_)));
		return u64x8(lo, hi);
#elif EMU_SIMD_USE_128_REGISTERS
		u32x4 a_lane = a_._lane_0;
		u64x2 lo_lo = _mm_cvtepi32_epi64(a_lane);
		u64x2 lo_hi = _mm_cvtepi32_epi64(movehl_i32x4(a_lane, a_lane));
		a_lane = a_._lane_1;
		u64x2 hi_lo = _mm_cvtepi32_epi64(a_lane);
		u64x2 hi_hi = _mm_cvtepi32_epi64(movehl_i32x4(a_lane, a_lane));
		return i64x8(i64x4(lo_lo, lo_hi), i64x4(hi_lo, hi_hi));
#else
		return EmuSIMD::_underlying_impl::emulate_cvt<u64x8, std::uint64_t, 64, false, 8, true, std::int32_t>(a_, std::make_index_sequence<8>());
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 cvt_i64x4_u64x8(i64x4_arg a_)
	{
		return cast_i64x4_u64x8(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 cvt_i8x64_u64x8(i8x64_arg a_)
	{
#if EMU_SIMD_USES_ANY_SIMD_REGISTERS
		return cvt_i8x16_u64x8(cast_i8x64_i8x16(a_));
#else
		return EmuSIMD::_underlying_impl::emulate_cvt<u64x8, std::uint64_t, 64, false, 64, true, std::int8_t>(a_, std::make_index_sequence<8>());
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 cvt_i16x32_u64x8(i16x32_arg a_)
	{
#if EMU_SIMD_USES_ANY_SIMD_REGISTERS
		return cvt_i16x8_u64x8(cast_i16x32_i16x8(a_));
#else
		return EmuSIMD::_underlying_impl::emulate_cvt<u64x8, std::uint64_t, 64, false, 32, true, std::int16_t>(a_, std::make_index_sequence<8>());
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 cvt_i32x16_u64x8(i32x16_arg a_)
	{
#if EMU_SIMD_USES_ANY_SIMD_REGISTERS
		return cvt_i32x8_u64x8(cast_i32x16_i32x8(a_));
#else
		return EmuSIMD::_underlying_impl::emulate_cvt<u64x8, std::uint64_t, 64, false, 16, true, std::int32_t>(a_, std::make_index_sequence<8>());
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 cvt_i64x8_u64x8(i64x8_arg a_)
	{
		return cast_i64x8_u64x8(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 cvt_u8x16_u64x8(u8x16_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_cvtepu8_epi64(a_);
#else
		return EmuSIMD::_underlying_impl::emulate_cvt<u64x8, std::uint64_t, 64, false, 16, false, std::uint8_t>(a_, std::make_index_sequence<8>());
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 cvt_u16x8_u64x8(u16x8_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_cvtepu16_epi64(a_);
#elif EMU_SIMD_USE_256_REGISTERS
		u64x4 lo = _mm256_cvtepu16_epi64(a_);
		u64x4 hi = _mm256_cvtepu16_epi64(movehl_i16x8(a_, a_));
		return u64x8(lo, hi);
#else
		return EmuSIMD::_underlying_impl::emulate_cvt<u64x8, std::uint64_t, 64, false, 8, false, std::uint16_t>(a_, std::make_index_sequence<8>());
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 cvt_u32x4_u64x8(u32x4_arg a_)
	{
#if EMU_SIMD_USE_256_REGISTERS
		return cast_u64x4_u64x8(_mm256_cvtepu32_epi64(a_));
#elif EMU_SIMD_USE_128_REGISTERS
		u64x2 lo_lo = _mm_cvtepu32_epi64(a_);
		u64x2 lo_hi = _mm_cvtepu32_epi64(movehl_u32x4(a_, a_));
		return u64x8(u64x4(lo_lo, lo_hi)); // { a_, zero }
#else
		return EmuSIMD::_underlying_impl::emulate_cvt<u64x8, std::uint64_t, 64, false, 4, false, std::uint32_t>(a_, std::make_index_sequence<8>());
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 cvt_u64x2_u64x8(u64x2_arg a_)
	{
		return cast_u64x2_u64x8(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 cvt_u8x32_u64x8(u8x32_arg a_)
	{
#if EMU_SIMD_USES_ANY_SIMD_REGISTERS
		return cvt_u8x16_u64x8(cast_u8x32_u8x16(a_));
#else
		return EmuSIMD::_underlying_impl::emulate_cvt<u64x8, std::uint64_t, 64, false, 32, false, std::uint8_t>(a_, std::make_index_sequence<8>());
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 cvt_u16x16_u64x8(u16x16_arg a_)
	{
#if EMU_SIMD_USES_ANY_SIMD_REGISTERS
		return cvt_u16x8_u64x8(cast_u16x16_u16x8(a_));
#else
		return EmuSIMD::_underlying_impl::emulate_cvt<u64x8, std::uint64_t, 64, false, 16, false, std::uint16_t>(a_, std::make_index_sequence<8>());
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 cvt_u32x8_u64x8(u32x8_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_cvtepu32_epi64(a_);
#elif EMU_SIMD_USE_256_REGISTERS
		u64x4 lo = _mm256_cvtepu32_epi64(cast_u32x8_u32x4(a_));
		u64x4 hi = _mm256_cvtepu32_epi64(cast_u32x8_u32x4(movehl_u32x8(a_, a_)));
		return u64x8(lo, hi);
#elif EMU_SIMD_USE_128_REGISTERS
		u32x4 a_lane = a_._lane_0;
		u64x2 lo_lo = _mm_cvtepu32_epi64(a_lane);
		u64x2 lo_hi = _mm_cvtepu32_epi64(movehl_u32x4(a_lane, a_lane));
		a_lane = a_._lane_1;
		u64x2 hi_lo = _mm_cvtepu32_epi64(a_lane);
		u64x2 hi_hi = _mm_cvtepu32_epi64(movehl_u32x4(a_lane, a_lane));
		return u64x8(i64x4(lo_lo, lo_hi), i64x4(hi_lo, hi_hi));
#else
		return EmuSIMD::_underlying_impl::emulate_cvt<u64x8, std::uint64_t, 64, false, 8, false, std::uint32_t>(a_, std::make_index_sequence<8>());
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 cvt_u64x4_u64x8(u64x4_arg a_)
	{
		return cast_u64x4_u64x8(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 cvt_u8x64_u64x8(u8x64_arg a_)
	{
#if EMU_SIMD_USES_ANY_SIMD_REGISTERS
		return cvt_u8x16_u64x8(cast_u8x64_u8x16(a_));
#else
		return EmuSIMD::_underlying_impl::emulate_cvt<u64x8, std::uint64_t, 64, false, 64, false, std::uint8_t>(a_, std::make_index_sequence<8>());
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 cvt_u16x32_u64x8(u16x32_arg a_)
	{
#if EMU_SIMD_USES_ANY_SIMD_REGISTERS
		return cvt_u16x8_u64x8(cast_u16x32_u16x8(a_));
#else
		return EmuSIMD::_underlying_impl::emulate_cvt<u64x8, std::uint64_t, 64, false, 32, false, std::uint16_t>(a_, std::make_index_sequence<8>());
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 cvt_u32x16_u64x8(u32x16_arg a_)
	{
#if EMU_SIMD_USES_ANY_SIMD_REGISTERS
		return cvt_u32x8_u64x8(cast_u32x16_u32x8(a_));
#else
		return EmuSIMD::_underlying_impl::emulate_cvt<u64x8, std::uint64_t, 64, false, 16, false, std::uint32_t>(a_, std::make_index_sequence<8>());
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 cvt_u64x8_u64x8(u64x8_arg a_)
	{
		return a_;
	}
#pragma endregion

#pragma region COMPARISONS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 cmpeq_u64x8(EmuSIMD::u64x8_arg lhs_, EmuSIMD::u64x8_arg rhs_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return setmasked_u64x8(_mm512_cmpeq_epu64_mask(lhs_, rhs_));
#else
		return u64x8(cmpeq_u64x4(lhs_._lane_0, rhs_._lane_0), cmpeq_u64x4(lhs_._lane_1, rhs_._lane_1));
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 cmpneq_u64x8(EmuSIMD::u64x8_arg lhs_, EmuSIMD::u64x8_arg rhs_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return setmasked_i8x64(_mm512_cmpneq_epu64_mask(lhs_, rhs_));
#else
		return u64x8(cmpneq_u64x4(lhs_._lane_0, rhs_._lane_0), cmpneq_u64x4(lhs_._lane_1, rhs_._lane_1));
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 cmpgt_u64x8(EmuSIMD::u64x8_arg lhs_, EmuSIMD::u64x8_arg rhs_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return setmasked_i8x64(_mm512_cmplt_epu64_mask(rhs_, lhs_));
#else
		return u64x8(cmpgt_u64x4(lhs_._lane_0, rhs_._lane_0), cmpgt_u64x4(lhs_._lane_1, rhs_._lane_1));
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 cmplt_u64x8(EmuSIMD::u64x8_arg lhs_, EmuSIMD::u64x8_arg rhs_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return setmasked_i8x64(_mm512_cmplt_epu64_mask(lhs_, rhs_));
#else
		return u64x8(cmplt_u64x4(lhs_._lane_0, rhs_._lane_0), cmplt_u64x4(lhs_._lane_1, rhs_._lane_1));
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 cmpge_u64x8(EmuSIMD::u64x8_arg lhs_, EmuSIMD::u64x8_arg rhs_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return setmasked_i8x64(_mm512_cmple_epu64_mask(rhs_, lhs_));
#else
		return u64x8(cmpge_u64x4(lhs_._lane_0, rhs_._lane_0), cmpge_u64x4(lhs_._lane_1, rhs_._lane_1));
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 cmple_u64x8(EmuSIMD::u64x8_arg lhs_, EmuSIMD::u64x8_arg rhs_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return setmasked_i8x64(_mm512_cmple_epu64_mask(lhs_, rhs_));
#else
		return u64x8(cmple_u64x4(lhs_._lane_0, rhs_._lane_0), cmple_u64x4(lhs_._lane_1, rhs_._lane_1));
#endif
	}
#pragma endregion

#pragma region MOVES
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 movehl_u64x8(EmuSIMD::u64x8_arg lhs_, EmuSIMD::u64x8_arg rhs_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return cast_f64x8_u64x8(movehl_f64x8(cast_u64x8_f64x8(lhs_), cast_u64x8_f64x8(rhs_)));
#else
		return EmuSIMD::_underlying_impl::emulated_movehl(lhs_, rhs_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 movelh_u64x8(EmuSIMD::u64x8_arg lhs_, EmuSIMD::u64x8_arg rhs_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return cast_f64x8_u64x8(movelh_f64x8(cast_u64x8_f64x8(lhs_), cast_u64x8_f64x8(rhs_)));
#else
		return EmuSIMD::_underlying_impl::emulated_movelh(lhs_, rhs_);
#endif
	}
#pragma endregion

#pragma region BITWISE_ARITHMETIC
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 and_u64x8(EmuSIMD::i64x8_arg lhs_, EmuSIMD::i64x8_arg rhs_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_and_si512(lhs_, rhs_);
#else
		using EmuSIMD::_underlying_impl::emulate_simd_basic;
		return emulate_simd_basic([](u64x4_arg a_, u64x4_arg b_) { return EmuSIMD::Funcs::and_u64x4(a_, b_); }, lhs_, rhs_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 or_u64x8(EmuSIMD::i64x8_arg lhs_, EmuSIMD::i64x8_arg rhs_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_or_si512(lhs_, rhs_);
#else
		using EmuSIMD::_underlying_impl::emulate_simd_basic;
		return emulate_simd_basic([](u64x4_arg a_, u64x4_arg b_) { return EmuSIMD::Funcs::or_u64x4(a_, b_); }, lhs_, rhs_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 xor_u64x8(EmuSIMD::i64x8_arg lhs_, EmuSIMD::i64x8_arg rhs_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_xor_si512(lhs_, rhs_);
#else
		using EmuSIMD::_underlying_impl::emulate_simd_basic;
		return emulate_simd_basic([](u64x4_arg a_, u64x4_arg b_) { return EmuSIMD::Funcs::xor_u64x4(a_, b_); }, lhs_, rhs_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 andnot_u64x8(EmuSIMD::i64x8_arg not_lhs_, EmuSIMD::i64x8_arg rhs_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_andnot_si512(not_lhs_, rhs_);
#else
		using EmuSIMD::_underlying_impl::emulate_simd_basic;
		return emulate_simd_basic([](u64x4_arg a_, u64x4_arg b_) { return EmuSIMD::Funcs::andnot_u64x4(a_, b_); }, not_lhs_, rhs_);
#endif
	}

	template<std::int32_t NumShifts_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 shift_left_u64x8(EmuSIMD::u64x8_arg lhs_)
	{
		if constexpr (NumShifts_ >= 64)
		{
			return setzero_u64x8();
		}
		else
		{
#if EMU_SIMD_USE_512_REGISTERS
			return _mm512_slli_epi64(lhs_, NumShifts_);
#else
			using EmuSIMD::_underlying_impl::emulate_simd_basic;
			return emulate_simd_basic([](u64x4_arg a_) { return shift_left_u64x4<NumShifts_>(a_); }, lhs_);
#endif
		}
	}

	template<std::int32_t NumShifts_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 shift_right_arithmetic_u64x8(EmuSIMD::u64x8_arg lhs_)
	{
		// No sign bit, so same as logical shift
		return shift_right_logical_u64x4<NumShifts_>(lhs_);
	}

	template<std::int32_t NumShifts_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 shift_right_logical_u64x8(EmuSIMD::u64x8_arg lhs_)
	{
		if constexpr (NumShifts_ >= 64)
		{
			return setzero_u64x8();
		}
		else
		{
#if EMU_SIMD_USE_512_REGISTERS
			return _mm512_srli_epi64(lhs_, NumShifts_);
#else
			using EmuSIMD::_underlying_impl::emulate_simd_basic;
			return emulate_simd_basic([](u64x4_arg a_) { return shift_right_logical_u64x4<NumShifts_>(a_); }, lhs_);
#endif
		}
	}
#pragma endregion
	
#pragma region BLENDS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 blendv_u64x8(EmuSIMD::u64x8_arg a_, EmuSIMD::u64x8_arg b_, EmuSIMD::u64x8_arg blend_mask_vec_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return cast_f64x8_u64x8
		(
			blendv_f64x8
			(
				cast_u64x8_f64x8(a_),
				cast_u64x8_f64x8(b_),
				cast_u64x8_f64x8(blend_mask_vec_)
			)
		);
#else
		return u64x8(blendv_u64x4(a_._lane_0, b_._lane_0, blend_mask_vec_._lane_0), blendv_u64x4(a_._lane_1, b_._lane_1, blend_mask_vec_._lane_1));
#endif
	}
#pragma endregion

#pragma region MINMAX_FUNCS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 min_u64x8(EmuSIMD::u64x8_arg a_, EmuSIMD::u64x8_arg b_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_min_epu64(a_, b_);
#else
		return u64x8(min_u64x4(a_._lane_0, b_._lane_0), min_u64x4(a_._lane_1, b_._lane_1));
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 horizontal_min_u64x8(EmuSIMD::u64x8_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		u64x4 lane = min_u64x4(cast_u64x8_u64x4(a_), extract_u64x8_lane_u64x4<1>(a_));
		return cast_u64x4_u64x8(horizontal_min_u64x4(lane));
#else
		return EmuSIMD::_underlying_impl::emulate_horizontal_min_or_max<false, 64, false>(a_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 horizontal_min_fill_u64x8(EmuSIMD::u64x8_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		u64x4 lane = min_u64x4(cast_u64x8_u64x4(a_), extract_u64x8_lane_u64x4<1>(a_));
		lane = horizontal_min_fill_u64x4(lane);
		return _mm512_inserti64x4(cast_u64x4_u64x8(lane), lane, 1);
#else
		return EmuSIMD::_underlying_impl::emulate_horizontal_min_or_max<false, 64, false>(a_);
#endif
	}

	template<typename Out_>
	EMU_SIMD_COMMON_FUNC_SPEC auto horizontal_min_scalar_u64x8(EmuSIMD::u64x8_arg a_)
		-> typename std::remove_cvref<Out_>::type
	{
#if EMU_SIMD_USE_512_REGISTERS
		u64x4 lane = min_u64x4(cast_u64x8_u64x4(a_), extract_u64x8_lane_u64x4<1>(a_));
		return horizontal_min_scalar_u64x4<Out_>(lane);
#else
		return EmuSIMD::_underlying_impl::emulate_horizontal_min_or_max_scalar<Out_, false, 64, false>(a_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 max_u64x8(EmuSIMD::u64x8_arg a_, EmuSIMD::u64x8_arg b_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_max_epu64(a_, b_);
#else
		return u64x8(max_u64x4(a_._lane_0, b_._lane_0), max_u64x4(a_._lane_1, b_._lane_1));
#endif
	}

	// TODO: TEMPLATE FUNCS FOR NEW HORIZONTAL MIN/MAX

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 horizontal_max_u64x8(EmuSIMD::u64x8_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		u64x4 lane = max_u64x4(cast_u64x8_u64x4(a_), extract_u64x8_lane_u64x4<1>(a_));
		return cast_u64x4_u64x8(horizontal_max_u64x4(lane));
#else
		return EmuSIMD::_underlying_impl::emulate_horizontal_min_or_max<false, 64, false>(a_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 horizontal_max_fill_u64x8(EmuSIMD::u64x8_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		u64x4 lane = max_u64x4(cast_u64x8_u64x4(a_), extract_u64x8_lane_u64x4<1>(a_));
		lane = horizontal_max_fill_u64x4(lane);
		return _mm512_inserti64x4(cast_u64x4_u64x8(lane), lane, 1);
#else
		return EmuSIMD::_underlying_impl::emulate_horizontal_min_or_max<false, 64, false>(a_);
#endif
	}

	template<typename Out_>
	EMU_SIMD_COMMON_FUNC_SPEC auto horizontal_max_scalar_u64x8(EmuSIMD::u64x8_arg a_)
		-> typename std::remove_cvref<Out_>::type
	{
#if EMU_SIMD_USE_512_REGISTERS
		u64x4 lane = max_u64x4(cast_u64x8_u64x4(a_), extract_u64x8_lane_u64x4<1>(a_));
		return horizontal_max_scalar_u64x4<Out_>(lane);
#else
		return EmuSIMD::_underlying_impl::emulate_horizontal_min_or_max_scalar<Out_, false, 64, false>(a_);
#endif
	}
#pragma endregion

#pragma region BASIC_ARITHMETIC
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 mul_all_u64x8(EmuSIMD::u64x8_arg lhs_, EmuSIMD::u64x8_arg rhs_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_mullo_epi64(lhs_, rhs_);
#else
		return EmuSIMD::_underlying_impl::emulate_simd_basic([](u64x4_arg lhs, u64x4_arg rhs) { return mul_all_u64x4(lhs, rhs); }, lhs_, rhs_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 negate_u64x8(EmuSIMD::u64x8_arg to_negate_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_sub_epi64(_mm512_setzero_si512(), to_negate_);
#else
		return EmuSIMD::_underlying_impl::emulate_simd_basic([](u64x4_arg to_negate) { return negate_u64x4(to_negate); }, to_negate_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 add_u64x8(EmuSIMD::u64x8_arg lhs_, EmuSIMD::u64x8_arg rhs_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_add_epi64(lhs_, rhs_);
#else
		return EmuSIMD::_underlying_impl::emulate_simd_basic([](u64x4_arg lhs, u64x4_arg rhs) { return add_u64x4(lhs, rhs); }, lhs_, rhs_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 sub_u64x8(EmuSIMD::u64x8_arg lhs_, EmuSIMD::u64x8_arg rhs_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_sub_epi64(lhs_, rhs_);
#else
		return EmuSIMD::_underlying_impl::emulate_simd_basic([](u64x4_arg lhs, u64x4_arg rhs) { return sub_u64x4(lhs, rhs); }, lhs_, rhs_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 div_u64x8(EmuSIMD::u64x8_arg lhs_, EmuSIMD::u64x8_arg rhs_)
	{
#if EMU_SIMD_USE_512_REGISTERS
#if EMU_CORE_X86_X64_SVML
		return _mm512_div_epu64(lhs_, rhs_);
#else
		EmuSIMD::f64x8 result_f64 = cvt_u64x8_f64x8(lhs_);
		result_f64 = div_f64x8(result_f64, cvt_u64x8_f64x8(rhs_));
		return cvt_f64x8_u64x8(trunc_f64x8(result_f64));
#endif
#else
		return EmuSIMD::_underlying_impl::emulate_simd_basic([](u64x4_arg lhs, u64x4_arg rhs) { return div_u64x4(lhs, rhs); }, lhs_, rhs_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 addsub_u64x8(EmuSIMD::u64x8_arg lhs_, EmuSIMD::u64x8_arg rhs_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		constexpr std::uint64_t bytes_mask = static_cast<std::uint64_t>(0xFFFFFFFFFFFFFFFF);
		const EmuSIMD::u64x8 mask = _mm512_set_epi64(bytes_mask, 0, bytes_mask, 0, bytes_mask, 0, bytes_mask, 0);
		EmuSIMD::u64x8 out = _mm512_add_epi64(lhs_, _mm512_and_si512(mask, rhs_));
		return _mm512_sub_epi64(lhs_, _mm512_andnot_si512(mask, rhs_));
#else
		return EmuSIMD::_underlying_impl::emulate_simd_basic([](u64x4_arg lhs, u64x4_arg rhs) { return addsub_u64x4(lhs, rhs); }, lhs_, rhs_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 subadd_u64x8(EmuSIMD::u64x8_arg lhs_, EmuSIMD::u64x8_arg rhs_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		constexpr std::uint64_t bytes_mask = static_cast<std::uint64_t>(0xFFFFFFFFFFFFFFFF);
		const EmuSIMD::u64x8 mask = _mm512_set_epi64(bytes_mask, 0, bytes_mask, 0, bytes_mask, 0, bytes_mask, 0);
		EmuSIMD::u64x8 out = _mm512_sub_epi64(lhs_, _mm512_and_si512(mask, rhs_));
		return _mm512_add_epi64(lhs_, _mm512_andnot_si512(mask, rhs_));
#else
		return EmuSIMD::_underlying_impl::emulate_simd_basic([](u64x4_arg lhs, u64x4_arg rhs) { return subadd_u64x4(lhs, rhs); }, lhs_, rhs_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 fmadd_u64x8(EmuSIMD::u64x8_arg a_, EmuSIMD::u64x8_arg b_, EmuSIMD::u64x8_arg c_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_add_epi64(mul_all_u64x8(a_, b_), c_);
#else
		return EmuSIMD::_underlying_impl::emulate_simd_basic([](u64x4_arg a, u64x4_arg b, u64x4_arg c) { return fmadd_u64x4(a, b, c); }, a_, b_, c_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 fmsub_u64x8(EmuSIMD::u64x8_arg a_, EmuSIMD::u64x8_arg b_, EmuSIMD::u64x8_arg c_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_sub_epi64(mul_all_u64x8(a_, b_), c_);
#else
		return EmuSIMD::_underlying_impl::emulate_simd_basic([](u64x4_arg a, u64x4_arg b, u64x4_arg c) { return fmsub_u64x4(a, b, c); }, a_, b_, c_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 fnmadd_u64x8(EmuSIMD::u64x8_arg a_, EmuSIMD::u64x8_arg b_, EmuSIMD::u64x8_arg c_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_add_epi64(mul_all_u64x8(negate_u64x8(a_), b_), c_);
#else
		return EmuSIMD::_underlying_impl::emulate_simd_basic([](u64x4_arg a, u64x4_arg b, u64x4_arg c) { return fnmadd_u64x4(a, b, c); }, a_, b_, c_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 fnmsub_u64x8(EmuSIMD::u64x8_arg a_, EmuSIMD::u64x8_arg b_, EmuSIMD::u64x8_arg c_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_sub_epi64(mul_all_u64x8(negate_u64x8(a_), b_), c_);
#else
		return EmuSIMD::_underlying_impl::emulate_simd_basic([](u64x4_arg a, u64x4_arg b, u64x4_arg c) { return fnmsub_u64x4(a, b, c); }, a_, b_, c_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 fmaddsub_u64x8(EmuSIMD::u64x8_arg a_, EmuSIMD::u64x8_arg b_, EmuSIMD::u64x8_arg c_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return addsub_u64x8(mul_all_u64x8(a_, b_), c_);
#else
		return EmuSIMD::_underlying_impl::emulate_simd_basic([](u64x4_arg a, u64x4_arg b, u64x4_arg c) { return fmaddsub_u64x4(a, b, c); }, a_, b_, c_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 fmsubadd_u64x8(EmuSIMD::u64x8_arg a_, EmuSIMD::u64x8_arg b_, EmuSIMD::u64x8_arg c_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return subadd_u64x8(mul_all_u64x8(a_, b_), c_);
#else
		return EmuSIMD::_underlying_impl::emulate_simd_basic([](u64x4_arg a, u64x4_arg b, u64x4_arg c) { return fmsubadd_u64x4(a, b, c); }, a_, b_, c_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 floor_u64x8(EmuSIMD::u64x8_arg to_floor_)
	{
		return to_floor_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 ceil_u64x8(EmuSIMD::u64x8_arg to_ceil_)
	{
		return to_ceil_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 trunc_u64x8(EmuSIMD::u64x8_arg to_trunc_)
	{
		return to_trunc_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 mod_u64x8(EmuSIMD::u64x8_arg lhs_, EmuSIMD::u64x8_arg rhs_)
	{
#if EMU_SIMD_USE_512_REGISTERS
#if EMU_CORE_X86_X64_SVML
		return _mm512_rem_epi64(lhs_, rhs_);
#else
		EmuSIMD::u64x8 to_subtract = div_u64x8(lhs_, rhs_);
		to_subtract = mul_all_u64x8(to_subtract, rhs_);
		return sub_u64x8(lhs_, to_subtract);
#endif
#else
		return EmuSIMD::_underlying_impl::emulate_simd_basic([](u64x4_arg lhs, u64x4_arg rhs) { return mod_u64x4(lhs, rhs); }, lhs_, rhs_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 abs_u64x8(EmuSIMD::u64x8_arg in_)
	{
		return in_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 sqrt_u64x8(EmuSIMD::u64x8_arg in_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return emulate_fp_u64x8([](EmuSIMD::f64x8_arg in_fp_) { return sqrt_f64x8(in_fp_); }, in_);
#else
		return EmuSIMD::_underlying_impl::emulate_simd_basic([](u64x4_arg a) { return sqrt_u64x4(a); }, in_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 rsqrt_u64x8(EmuSIMD::u64x8_arg in_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return emulate_fp_u64x8([](EmuSIMD::f64x8_arg in_fp_) { return rsqrt_f64x8(in_fp_); }, in_);
#else
		return EmuSIMD::_underlying_impl::emulate_simd_basic([](u64x4_arg a) { return rsqrt_u64x4(a); }, in_);
#endif
	}
#pragma endregion

#pragma region NEAR_COMPARISONS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 cmpnear_u64x8(EmuSIMD::u64x8_arg lhs_, EmuSIMD::u64x8_arg rhs_)
	{
		return cmpeq_u64x8(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 cmpnear_u64x8(EmuSIMD::u64x8_arg lhs_, EmuSIMD::u64x8_arg rhs_, EmuSIMD::u64x8_arg epsilon)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return cmple_u64x8(sub_u64x8(lhs_, rhs_), epsilon);
#else
		return u64x8(cmpnear_u64x4(lhs_._lane_1, rhs_._lane_1, epsilon._lane_0), cmpnear_u64x4(lhs_._lane_1, rhs_._lane_1, epsilon._lane_1));
#endif
	}
#pragma endregion

#pragma region TRIG
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 cos_u64x8(EmuSIMD::u64x8_arg in_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return emulate_fp_u64x8([](EmuSIMD::f64x8_arg in_fp_) { return cos_f64x8(in_fp_); }, in_);
#else
		return EmuSIMD::_underlying_impl::emulate_simd_basic([](u64x4_arg a) { return cos_u64x4(a); }, in_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 sin_u64x8(EmuSIMD::u64x8_arg in_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return emulate_fp_u64x8([](EmuSIMD::f64x8_arg in_fp_) { return sin_f64x8(in_fp_); }, in_);
#else
		return EmuSIMD::_underlying_impl::emulate_simd_basic([](u64x4_arg a) { return sin_u64x4(a); }, in_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 tan_u64x8(EmuSIMD::u64x8_arg in_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return emulate_fp_u64x8([](EmuSIMD::f64x8_arg in_fp_) { return tan_f64x8(in_fp_); }, in_);
#else
		return EmuSIMD::_underlying_impl::emulate_simd_basic([](u64x4_arg a) { return tan_u64x4(a); }, in_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 acos_u64x8(EmuSIMD::u64x8_arg in_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return emulate_fp_u64x8([](EmuSIMD::f64x8_arg in_fp_) { return acos_f64x8(in_fp_); }, in_);
#else
		return EmuSIMD::_underlying_impl::emulate_simd_basic([](u64x4_arg a) { return acos_u64x4(a); }, in_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 asin_u64x8(EmuSIMD::u64x8_arg in_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return emulate_fp_u64x8([](EmuSIMD::f64x8_arg in_fp_) { return asin_f64x8(in_fp_); }, in_);
#else
		return EmuSIMD::_underlying_impl::emulate_simd_basic([](u64x4_arg a) { return asin_u64x4(a); }, in_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u64x8 atan_u64x8(EmuSIMD::u64x8_arg in_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return emulate_fp_u64x8([](EmuSIMD::f64x8_arg in_fp_) { return atan_f64x8(in_fp_); }, in_);
#else
		return EmuSIMD::_underlying_impl::emulate_simd_basic([](u64x4_arg a) { return atan_u64x4(a); }, in_);
#endif
	}
#pragma endregion
}

#endif
