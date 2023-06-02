#ifndef EMU_SIMD_GENERIC_FUNCS_U16X32_H_INC_
#define EMU_SIMD_GENERIC_FUNCS_U16X32_H_INC_ 1

#include "_generic_declarations/_all_generic_declarations.h"
#include "_common_generic_func_helpers.h"

namespace EmuSIMD::Funcs
{
#pragma region SETTERS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 set_u16x32
	(
		std::uint16_t e0, std::uint16_t e1, std::uint16_t e2, std::uint16_t e3, std::uint16_t e4, std::uint16_t e5, std::uint16_t e6, std::uint16_t e7,
		std::uint16_t e8, std::uint16_t e9, std::uint16_t e10, std::uint16_t e11, std::uint16_t e12, std::uint16_t e13, std::uint16_t e14, std::uint16_t e15,
		std::uint16_t e16, std::uint16_t e17, std::uint16_t e18, std::uint16_t e19, std::uint16_t e20, std::uint16_t e21, std::uint16_t e22, std::uint16_t e23,
		std::uint16_t e24, std::uint16_t e25, std::uint16_t e26, std::uint16_t e27, std::uint16_t e28, std::uint16_t e29, std::uint16_t e30, std::uint16_t e31
	)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_set_epi16(e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19, e20, e21, e22, e23, e24, e25, e26, e27, e28, e29, e30, e31);
#else
	return EmuSIMD::_underlying_impl::set_dual_lane_simd_emulator<false, 512, u16x16>
	(
		e0,  e1,  e2,  e3,  e4,  e5,  e6,  e7,  e8,  e9,  e10, e11, e12, e13, e14, e15, e16, e17, e18, e19, e20, e21, e22, e23, e24, e25, e26, e27, e28, e29, e30, e31
	);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 setr_u16x32
	(
		std::uint16_t e0, std::uint16_t e1, std::uint16_t e2, std::uint16_t e3, std::uint16_t e4, std::uint16_t e5, std::uint16_t e6, std::uint16_t e7,
		std::uint16_t e8, std::uint16_t e9, std::uint16_t e10, std::uint16_t e11, std::uint16_t e12, std::uint16_t e13, std::uint16_t e14, std::uint16_t e15,
		std::uint16_t e16, std::uint16_t e17, std::uint16_t e18, std::uint16_t e19, std::uint16_t e20, std::uint16_t e21, std::uint16_t e22, std::uint16_t e23,
		std::uint16_t e24, std::uint16_t e25, std::uint16_t e26, std::uint16_t e27, std::uint16_t e28, std::uint16_t e29, std::uint16_t e30, std::uint16_t e31
	)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_set_epi16(e31, e30, e29, e28, e27, e26, e25, e24, e23, e22, e21, e20, e19, e18, e17, e16, e15, e14, e13, e12, e11, e10, e9, e8, e7, e6, e5, e4, e3, e2, e1, e0);
#else
		return EmuSIMD::_underlying_impl::set_dual_lane_simd_emulator<true, 512, u16x16>
		(
			e0,  e1,  e2,  e3,  e4,  e5,  e6,  e7,  e8,  e9,  e10, e11, e12, e13, e14, e15, e16, e17, e18, e19, e20, e21, e22, e23, e24, e25, e26, e27, e28, e29, e30, e31
		);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 set1_u16x32(std::uint16_t all_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_set1_epi16(all_);
#else
		return EmuSIMD::_underlying_impl::set1_dual_lane_simd_emulator<512, u16x16, 16>(all_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 load_u16x32(const std::uint16_t* p_to_load_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_loadu_si512(p_to_load_);
#else
		return EmuSIMD::_underlying_impl::load_dual_lane_simd_emulator<512, u16x16>(p_to_load_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 aligned_load_u16x32(const std::uint16_t* p_to_load_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_load_si512(p_to_load_);
#else
		return EmuSIMD::_underlying_impl::load_dual_lane_simd_emulator<512, u16x16>(p_to_load_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 setzero_u16x32()
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_setzero_si512();
#else
		return EmuSIMD::_underlying_impl::set_dual_lane_simd_emulator<512, u16x16>();
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 setmasked_u16x32(std::uint32_t bit_mask_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		constexpr std::uint16_t element_mask = static_cast<std::uint16_t>(0xFFFF);
		return _mm512_set_epi16
		(
			static_cast<std::uint16_t>(bit_mask_  & 0x00000001)        * element_mask,
			static_cast<std::uint16_t>((bit_mask_ & 0x00000002) >> 1)  * element_mask,
			static_cast<std::uint16_t>((bit_mask_ & 0x00000004) >> 2)  * element_mask,
			static_cast<std::uint16_t>((bit_mask_ & 0x00000008) >> 3)  * element_mask,
			static_cast<std::uint16_t>((bit_mask_ & 0x00000010) >> 4)  * element_mask,
			static_cast<std::uint16_t>((bit_mask_ & 0x00000020) >> 5)  * element_mask,
			static_cast<std::uint16_t>((bit_mask_ & 0x00000040) >> 6)  * element_mask,
			static_cast<std::uint16_t>((bit_mask_ & 0x00000080) >> 7)  * element_mask,
			static_cast<std::uint16_t>((bit_mask_ & 0x00000100) >> 8)  * element_mask,
			static_cast<std::uint16_t>((bit_mask_ & 0x00000200) >> 9)  * element_mask,
			static_cast<std::uint16_t>((bit_mask_ & 0x00000400) >> 10) * element_mask,
			static_cast<std::uint16_t>((bit_mask_ & 0x00000800) >> 11) * element_mask,
			static_cast<std::uint16_t>((bit_mask_ & 0x00001000) >> 12) * element_mask,
			static_cast<std::uint16_t>((bit_mask_ & 0x00002000) >> 13) * element_mask,
			static_cast<std::uint16_t>((bit_mask_ & 0x00004000) >> 14) * element_mask,
			static_cast<std::uint16_t>((bit_mask_ & 0x00008000) >> 15) * element_mask,
			static_cast<std::uint16_t>((bit_mask_ & 0x00010000) >> 16) * element_mask,
			static_cast<std::uint16_t>((bit_mask_ & 0x00020000) >> 17) * element_mask,
			static_cast<std::uint16_t>((bit_mask_ & 0x00040000) >> 18) * element_mask,
			static_cast<std::uint16_t>((bit_mask_ & 0x00080000) >> 19) * element_mask,
			static_cast<std::uint16_t>((bit_mask_ & 0x00100000) >> 20) * element_mask,
			static_cast<std::uint16_t>((bit_mask_ & 0x00200000) >> 21) * element_mask,
			static_cast<std::uint16_t>((bit_mask_ & 0x00400000) >> 22) * element_mask,
			static_cast<std::uint16_t>((bit_mask_ & 0x00800000) >> 23) * element_mask,
			static_cast<std::uint16_t>((bit_mask_ & 0x01000000) >> 24) * element_mask,
			static_cast<std::uint16_t>((bit_mask_ & 0x02000000) >> 25) * element_mask,
			static_cast<std::uint16_t>((bit_mask_ & 0x04000000) >> 26) * element_mask,
			static_cast<std::uint16_t>((bit_mask_ & 0x08000000) >> 27) * element_mask,
			static_cast<std::uint16_t>((bit_mask_ & 0x10000000) >> 28) * element_mask,
			static_cast<std::uint16_t>((bit_mask_ & 0x20000000) >> 29) * element_mask,
			static_cast<std::uint16_t>((bit_mask_ & 0x40000000) >> 30) * element_mask,
			static_cast<std::uint16_t>((bit_mask_ & 0x80000000) >> 31) * element_mask
		);
#else
		return EmuSIMD::_underlying_impl::setmasked_dual_lane_simd_emulator<512, u16x16, 32, std::uint16_t>(bit_mask_, [](std::uint16_t lane_mask) { return setmasked_u16x16(lane_mask); });
#endif
	}

	template<std::uint32_t BitMask_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 setmasked_u16x32()
	{
		if constexpr(BitMask_ != 0)
		{
#if EMU_SIMD_USE_512_REGISTERS
			return set_u16x32
			(
				std::integral_constant<std::uint16_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<0,  std::uint16_t>(BitMask_)>::value,
				std::integral_constant<std::uint16_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<1,  std::uint16_t>(BitMask_)>::value,
				std::integral_constant<std::uint16_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<2,  std::uint16_t>(BitMask_)>::value,
				std::integral_constant<std::uint16_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<3,  std::uint16_t>(BitMask_)>::value,
				std::integral_constant<std::uint16_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<4,  std::uint16_t>(BitMask_)>::value,
				std::integral_constant<std::uint16_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<5,  std::uint16_t>(BitMask_)>::value,
				std::integral_constant<std::uint16_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<6,  std::uint16_t>(BitMask_)>::value,
				std::integral_constant<std::uint16_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<7,  std::uint16_t>(BitMask_)>::value,
				std::integral_constant<std::uint16_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<8,  std::uint16_t>(BitMask_)>::value,
				std::integral_constant<std::uint16_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<9,  std::uint16_t>(BitMask_)>::value,
				std::integral_constant<std::uint16_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<10, std::uint16_t>(BitMask_)>::value,
				std::integral_constant<std::uint16_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<11, std::uint16_t>(BitMask_)>::value,
				std::integral_constant<std::uint16_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<12, std::uint16_t>(BitMask_)>::value,
				std::integral_constant<std::uint16_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<13, std::uint16_t>(BitMask_)>::value,
				std::integral_constant<std::uint16_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<14, std::uint16_t>(BitMask_)>::value,
				std::integral_constant<std::uint16_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<15, std::uint16_t>(BitMask_)>::value,
				std::integral_constant<std::uint16_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<16, std::uint16_t>(BitMask_)>::value,
				std::integral_constant<std::uint16_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<17, std::uint16_t>(BitMask_)>::value,
				std::integral_constant<std::uint16_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<18, std::uint16_t>(BitMask_)>::value,
				std::integral_constant<std::uint16_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<19, std::uint16_t>(BitMask_)>::value,
				std::integral_constant<std::uint16_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<20, std::uint16_t>(BitMask_)>::value,
				std::integral_constant<std::uint16_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<21, std::uint16_t>(BitMask_)>::value,
				std::integral_constant<std::uint16_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<22, std::uint16_t>(BitMask_)>::value,
				std::integral_constant<std::uint16_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<23, std::uint16_t>(BitMask_)>::value,
				std::integral_constant<std::uint16_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<24, std::uint16_t>(BitMask_)>::value,
				std::integral_constant<std::uint16_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<25, std::uint16_t>(BitMask_)>::value,
				std::integral_constant<std::uint16_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<26, std::uint16_t>(BitMask_)>::value,
				std::integral_constant<std::uint16_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<27, std::uint16_t>(BitMask_)>::value,
				std::integral_constant<std::uint16_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<28, std::uint16_t>(BitMask_)>::value,
				std::integral_constant<std::uint16_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<29, std::uint16_t>(BitMask_)>::value,
				std::integral_constant<std::uint16_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<30, std::uint16_t>(BitMask_)>::value,
				std::integral_constant<std::uint16_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<31, std::uint16_t>(BitMask_)>::value
			);
#else
			auto lane_setmasked = []<std::uint16_t lane_mask>() { return setmasked_u16x16<lane_mask>(); };
			return EmuSIMD::_underlying_impl::setmasked_dual_lane_simd_emulator<BitMask_, 512, u16x16, 32, std::uint16_t>(lane_setmasked);
#endif
		}
		else
		{
			return setzero_u16x32();
		}
	}

	template
	<
		bool I0_,  bool I1_,  bool I2_,  bool I3_,  bool I4_,  bool I5_,  bool I6_,  bool I7_,  bool I8_,  bool I9_,  bool I10_, bool I11_, bool I12_, bool I13_, bool I14_, bool I15_,
		bool I16_, bool I17_, bool I18_, bool I19_, bool I20_, bool I21_, bool I22_, bool I23_, bool I24_, bool I25_, bool I26_, bool I27_, bool I28_, bool I29_, bool I30_, bool I31_
	>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 set_index_mask_u16x32()
	{
		if constexpr
		(
			I0_  || I1_  || I2_  || I3_  || I4_  || I5_  || I6_  || I7_  || I8_  || I9_  || I10_ || I11_ || I12_ || I13_ || I14_ || I15_ ||
			I16_ || I17_ || I18_ || I19_ || I20_ || I21_ || I22_ || I23_ || I24_ || I25_ || I26_ || I27_ || I28_ || I29_ || I30_ || I31_
		)
		{
			return setmasked_u16x32
			<
				EmuSIMD::Funcs::make_index_set_mask
				<
					I0_,  I1_,  I2_,  I3_,  I4_,  I5_,  I6_,  I7_,  I8_,  I9_,  I10_, I11_, I12_, I13_, I14_, I15_,
					I16_, I17_, I18_, I19_, I20_, I21_, I22_, I23_, I24_, I25_, I26_, I27_, I28_, I29_, I30_, I31_
				>()
			>();
		}
		else
		{
			return setzero_u16x32();
		}
	}

	template<bool Active_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 set_index_mask_u16x32()
	{
		if constexpr (Active_)
		{
			return setmasked_u16x32<EmuSIMD::Funcs::make_all_indices_set_mask<32, Active_>()>();
		}
		else
		{
			return setzero_u16x32();
		}
	}
#pragma endregion

#pragma region STORES
	EMU_SIMD_COMMON_FUNC_SPEC void store_u16x32(std::uint16_t* p_out_, u16x32_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		_mm512_storeu_si512(p_out_, a_);
#else
		EmuSIMD::_underlying_impl::emulate_simd_store(a_, p_out_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC void aligned_store_u16x32(std::uint16_t* p_out_, u16x32_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		_mm512_store_si512(p_out_, a_);
#else
		EmuSIMD::_underlying_impl::emulate_simd_store(a_, p_out_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC std::uint16_t get_first_u16x32(u16x32_arg a_)
	{
		return get_first_u16x8(cast_u16x32_u16x8(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC std::uint32_t movemask_u16x32(u16x32_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return static_cast<std::uint32_t>(_mm512_movepi16_mask(a_));
#else
		return EmuSIMD::_underlying_impl::emulate_simd_movemask<std::uint32_t, 32>(a_);
#endif
	}
#pragma endregion

#pragma region CASTS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 cast_f32x4_u16x32(f32x4_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_castsi128_si512(_mm_castps_si128(a_));
#else
		return EmuSIMD::_underlying_impl::emulate_simd_cast_greater_width<u16x32>(a_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 cast_f32x8_u16x32(f32x8_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_castsi256_si512(_mm256_castps_si256(a_));
#else
		return EmuSIMD::_underlying_impl::emulate_simd_cast_greater_width<u16x32>(a_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 cast_f32x16_u16x32(f32x16_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_castps_si512(a_);
#else
		return EmuSIMD::_underlying_impl::emulate_simd_cast_same_width<u16x16>(a_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 cast_f64x2_u16x32(f64x2_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_castsi128_si512(_mm_castpd_si128(a_));
#else
		return EmuSIMD::_underlying_impl::emulate_simd_cast_greater_width<u16x32>(a_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 cast_f64x4_u16x32(f64x4_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_castsi256_si512(_mm256_castpd_si256(a_));
#else
		return EmuSIMD::_underlying_impl::emulate_simd_cast_greater_width<u16x32>(a_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 cast_f64x8_u16x32(f64x8_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_castpd_si512(a_);
#else
		return EmuSIMD::_underlying_impl::emulate_simd_cast_same_width<u16x16>(a_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 cast_i8x16_u16x32(i8x16_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_castsi128_si512(a_);
#else
		return EmuSIMD::_underlying_impl::emulate_simd_cast_greater_width<u16x32>(a_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 cast_i16x8_u16x32(i16x8_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_castsi128_si512(a_);
#else
		return EmuSIMD::_underlying_impl::emulate_simd_cast_greater_width<u16x32>(a_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 cast_i32x4_u16x32(i32x4_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_castsi128_si512(a_);
#else
		return EmuSIMD::_underlying_impl::emulate_simd_cast_greater_width<u16x32>(a_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 cast_i64x2_u16x32(i64x2_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_castsi128_si512(a_);
#else
		return EmuSIMD::_underlying_impl::emulate_simd_cast_greater_width<u16x32>(a_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 cast_i8x32_u16x32(i8x32_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_castsi256_si512(a_);
#else
		return EmuSIMD::_underlying_impl::emulate_simd_cast_greater_width<u16x32>(a_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 cast_i16x16_u16x32(i16x16_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_castsi256_si512(a_);
#else
		return EmuSIMD::_underlying_impl::emulate_simd_cast_greater_width<u16x32>(a_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 cast_i32x8_u16x32(i32x8_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_castsi256_si512(a_);
#else
		return EmuSIMD::_underlying_impl::emulate_simd_cast_greater_width<u16x32>(a_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 cast_i64x4_u16x32(i64x4_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_castsi256_si512(a_);
#else
		return EmuSIMD::_underlying_impl::emulate_simd_cast_greater_width<u16x32>(a_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 cast_i8x64_u16x32(i8x64_arg a_)
	{
#if EMU_SIMD_USES_ANY_SIMD_REGISTERS && EMU_SIMD_USE_GENERIC_INT_REGISTERS
		return a_;
#else
		return EmuSIMD::_underlying_impl::emulate_simd_cast_same_width<u16x16>(a_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 cast_i16x32_u16x32(i16x32_arg a_)
	{
#if EMU_SIMD_USES_ANY_SIMD_REGISTERS && EMU_SIMD_USE_GENERIC_INT_REGISTERS
		return a_;
#else
		return EmuSIMD::_underlying_impl::emulate_simd_cast_same_width<u16x16>(a_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 cast_i32x16_u16x32(i32x16_arg a_)
	{
#if EMU_SIMD_USES_ANY_SIMD_REGISTERS && EMU_SIMD_USE_GENERIC_INT_REGISTERS
		return a_;
#else
		return EmuSIMD::_underlying_impl::emulate_simd_cast_same_width<u16x16>(a_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 cast_i64x8_u16x32(i64x8_arg a_)
	{
#if EMU_SIMD_USES_ANY_SIMD_REGISTERS && EMU_SIMD_USE_GENERIC_INT_REGISTERS
		return a_;
#else
		return EmuSIMD::_underlying_impl::emulate_simd_cast_same_width<u16x16>(a_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 cast_u8x16_u16x32(u8x16_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_castsi128_si512(a_);
#else
		return EmuSIMD::_underlying_impl::emulate_simd_cast_greater_width<u16x32>(a_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 cast_u16x8_u16x32(u16x8_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_castsi128_si512(a_);
#else
		return EmuSIMD::_underlying_impl::emulate_simd_cast_greater_width<u16x32>(a_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 cast_u32x4_u16x32(u32x4_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_castsi128_si512(a_);
#else
		return EmuSIMD::_underlying_impl::emulate_simd_cast_greater_width<u16x32>(a_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 cast_u64x2_u16x32(u64x2_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_castsi128_si512(a_);
#else
		return EmuSIMD::_underlying_impl::emulate_simd_cast_greater_width<u16x32>(a_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 cast_u8x32_u16x32(u8x32_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_castsi256_si512(a_);
#else
		return EmuSIMD::_underlying_impl::emulate_simd_cast_greater_width<u16x32>(a_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 cast_u16x16_u16x32(u16x16_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_castsi256_si512(a_);
#else
		return EmuSIMD::_underlying_impl::emulate_simd_cast_greater_width<u16x32>(a_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 cast_u32x8_u16x32(u32x8_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_castsi256_si512(a_);
#else
		return EmuSIMD::_underlying_impl::emulate_simd_cast_greater_width<u16x32>(a_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 cast_u64x4_u16x32(u64x4_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_castsi256_si512(a_);
#else
		return EmuSIMD::_underlying_impl::emulate_simd_cast_greater_width<u16x32>(a_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 cast_u8x64_u16x32(u8x64_arg a_)
	{
#if EMU_SIMD_USES_ANY_SIMD_REGISTERS && EMU_SIMD_USE_GENERIC_INT_REGISTERS
		return a_;
#else
		return EmuSIMD::_underlying_impl::emulate_simd_cast_same_width<u16x16>(a_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 cast_u16x32_u16x32(u16x32_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 cast_u32x16_u16x32(u32x16_arg a_)
	{
#if EMU_SIMD_USES_ANY_SIMD_REGISTERS && EMU_SIMD_USE_GENERIC_INT_REGISTERS
		return a_;
#else
		return EmuSIMD::_underlying_impl::emulate_simd_cast_same_width<u16x16>(a_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 cast_u64x8_u16x32(u64x8_arg a_)
	{
#if EMU_SIMD_USES_ANY_SIMD_REGISTERS && EMU_SIMD_USE_GENERIC_INT_REGISTERS
		return a_;
#else
		return EmuSIMD::_underlying_impl::emulate_simd_cast_same_width<u16x16>(a_);
#endif
	}
#pragma endregion

#pragma region CONVERSIONS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 cvt_f32x4_u16x32(f32x4_arg a_)
	{
#if EMU_SIMD_USE_128_REGISTERS
		return cvt_i32x4_u16x32(cvt_f32x4_u32x4(a_));
#else
		return EmuSIMD::_underlying_impl::emulate_cvt<u16x32, std::uint16_t, 16, false, 4, true, float>(a_, std::make_index_sequence<32>());
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 cvt_f32x8_u16x32(f32x8_arg a_)
	{
#if EMU_SIMD_USE_256_REGISTERS
		return cvt_i32x8_u16x32(cvt_f32x8_u32x8(a_));
#else
		return EmuSIMD::_underlying_impl::emulate_cvt<u16x32, std::uint16_t, 16, false, 8, true, float>(a_, std::make_index_sequence<32>());
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 cvt_f32x16_u16x32(f32x16_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_castsi256_si512(_mm512_cvtepi32_epi16(_mm512_cvtps_epu32(a_)));
#else
		return EmuSIMD::_underlying_impl::emulate_cvt<u16x32, std::uint16_t, 16, false, 16, true, float>(a_, std::make_index_sequence<32>());
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 cvt_f64x2_u16x32(f64x2_arg a_)
	{
#if EMU_SIMD_USE_128_REGISTERS
		return cvt_i32x4_u16x32(cvt_f64x2_u32x4(a_));
#else
		return EmuSIMD::_underlying_impl::emulate_cvt<u16x32, std::uint16_t, 16, false, 2, true, double>(a_, std::make_index_sequence<32>());
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 cvt_f64x4_u16x32(f64x4_arg a_)
	{
#if EMU_SIMD_USE_256_REGISTERS
		return cvt_i32x4_u16x32(cvt_f64x4_u32x4(a_));
#else
		return EmuSIMD::_underlying_impl::emulate_cvt<u16x32, std::uint16_t, 16, false, 4, true, double>(a_, std::make_index_sequence<32>());
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 cvt_f64x8_u16x32(f64x8_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_castsi128_si512(_mm512_cvtepi64_epi16(_mm512_cvtpd_epu64(a_)));
#else
		return EmuSIMD::_underlying_impl::emulate_cvt<u16x32, std::uint16_t, 16, false, 8, true, double>(a_, std::make_index_sequence<32>());
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 cvt_i8x16_u16x32(i8x16_arg a_)
	{
#if EMU_SIMD_USE_256_REGISTERS
		return cast_u16x16_u16x32(_mm256_cvtepi8_epi16(a_));
#elif EMU_SIMD_USE_128_REGISTERS
		u16x8 lo_lo = _mm_cvtepi8_epi16(a_);
		u16x8 lo_hi = _mm_cvtepi8_epi16(movehl_i8x16(a_, a_));
		return u16x32(u16x16(lo_lo, lo_hi)); // { a_, zero }
#else
		return EmuSIMD::_underlying_impl::emulate_cvt<u16x32, std::uint16_t, 16, false, 16, true, std::int8_t>(a_, std::make_index_sequence<32>());
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 cvt_i16x8_u16x32(i16x8_arg a_)
	{
		return cast_i16x8_u16x32(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 cvt_i32x4_u16x32(i32x4_arg a_)
	{
#if EMU_SIMD_USE_128_REGISTERS
		return cast_u16x8_u16x32(cvt_i32x4_u16x8(a_));
#else
		return EmuSIMD::_underlying_impl::emulate_cvt<u16x32, std::uint16_t, 16, false, 4, true, std::int32_t>(a_, std::make_index_sequence<32>());
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 cvt_i64x2_u16x32(i64x2_arg a_)
	{
#if EMU_SIMD_USE_128_REGISTERS
		return cast_u16x8_u16x32(cvt_i64x2_u16x8(a_));
#else
		return EmuSIMD::_underlying_impl::emulate_cvt<u16x32, std::uint16_t, 16, false, 4, true, std::int64_t>(a_, std::make_index_sequence<32>());
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 cvt_i8x32_u16x32(i8x32_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_cvtepi8_epi16(a_);
#elif EMU_SIMD_USE_256_REGISTERS
		i16x16 lo = _mm256_cvtepi8_epi16(cast_i8x32_i8x16(a_));
		i16x16 hi = _mm256_cvtepi8_epi16(cast_i8x32_i8x16(movehl_i8x32(a_, a_)));
		return i16x32(lo, hi);
#elif EMU_SIMD_USE_128_REGISTERS
		i8x16 a_lane = cast_i8x32_i8x16(a_);
		i16x8 lo_lo = _mm_cvtepi8_epi16(a_lane);
		i16x8 lo_hi = _mm_cvtepi8_epi16(movehl_i8x16(a_lane, a_lane));
		a_lane = cast_i8x32_i8x16(movehl_i8x32(a_, a_));
		i16x8 hi_lo = _mm_cvtepi8_epi16(a_lane);
		i16x8 hi_hi = _mm_cvtepi8_epi16(movehl_i8x16(a_lane, a_lane));
		return i16x32(i16x16(lo_lo, lo_hi), i16x16(hi_lo, hi_hi));
#else
		return EmuSIMD::_underlying_impl::emulate_cvt<u16x32, std::uint16_t, 16, false, 32, true, std::int8_t>(a_, std::make_index_sequence<32>());
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 cvt_i16x16_u16x32(i16x16_arg a_)
	{
		return cast_i16x16_u16x32(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 cvt_i32x8_u16x32(i32x8_arg a_)
	{
#if EMU_SIMD_USE_256_REGISTERS
		return cast_u16x8_u16x32(cvt_i32x8_u16x8(a_));
#else
		return EmuSIMD::_underlying_impl::emulate_cvt<u16x32, std::uint16_t, 8, false, 8, true, std::int32_t>(a_, std::make_index_sequence<32>());
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 cvt_i64x4_u16x32(i64x4_arg a_)
	{
#if EMU_SIMD_USE_256_REGISTERS
		return cast_u16x8_u16x32(cvt_i64x4_u16x8(a_));
#else
		return EmuSIMD::_underlying_impl::emulate_cvt<u16x32, std::uint16_t, 16, false, 4, true, std::int64_t>(a_, std::make_index_sequence<32>());
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 cvt_i8x64_u16x32(i8x64_arg a_)
	{
#if EMU_SIMD_USES_ANY_SIMD_REGISTERS
		return cvt_i8x32_u16x32(cast_i8x64_i8x32(a_));
#else
		return EmuSIMD::_underlying_impl::emulate_cvt<u16x32, std::uint16_t, 16, false, 64, true, std::int8_t>(a_, std::make_index_sequence<32>());
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 cvt_i16x32_u16x32(i16x32_arg a_)
	{
		return cast_i16x32_u16x32(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 cvt_i32x16_u16x32(i32x16_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_castsi256_si512(_mm512_cvtepi32_epi16(a_));
#else
		return EmuSIMD::_underlying_impl::emulate_cvt<u16x32, std::uint16_t, 16, false, 16, true, std::int32_t>(a_, std::make_index_sequence<32>());
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 cvt_i64x8_u16x32(i64x8_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_castsi128_si512(_mm512_cvtepi64_epi16(a_));
#else
		return EmuSIMD::_underlying_impl::emulate_cvt<u16x32, std::uint16_t, 16, false, 8, true, std::int64_t>(a_, std::make_index_sequence<32>());
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 cvt_u8x16_u16x32(u8x16_arg a_)
	{
#if EMU_SIMD_USE_256_REGISTERS
		return cast_u16x16_u16x32(_mm256_cvtepu8_epi16(a_));
#elif EMU_SIMD_USE_128_REGISTERS
		i16x8 lo_lo = _mm_cvtepu8_epi16(a_);
		i16x8 lo_hi = _mm_cvtepu8_epi16(movehl_i8x16(a_, a_));
		return i16x32(i16x16(lo_lo, lo_hi)); // { a_, zero }
#else
		return EmuSIMD::_underlying_impl::emulate_cvt<u16x32, std::uint16_t, 16, false, 16, false, std::uint8_t>(a_, std::make_index_sequence<32>());
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 cvt_u16x8_u16x32(u16x8_arg a_)
	{
		return cast_u16x8_u16x32(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 cvt_u32x4_u16x32(u32x4_arg a_)
	{
#if EMU_SIMD_USE_128_REGISTERS
		return cast_u16x8_u16x32(cvt_u32x4_u16x8(a_));
#else
		return EmuSIMD::_underlying_impl::emulate_cvt<u16x32, std::uint16_t, 16, false, 4, false, std::uint32_t>(a_, std::make_index_sequence<32>());
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 cvt_u64x2_u16x32(u64x2_arg a_)
	{
#if EMU_SIMD_USE_128_REGISTERS
		return cast_u16x8_u16x32(cvt_u64x2_u16x8(a_));
#else
		return EmuSIMD::_underlying_impl::emulate_cvt<u16x32, std::uint16_t, 16, false, 4, false, std::uint64_t>(a_, std::make_index_sequence<32>());
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 cvt_u8x32_u16x32(u8x32_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_cvtepu8_epi16(a_);
#elif EMU_SIMD_USE_256_REGISTERS
		i16x16 lo = _mm256_cvtepu8_epi16(cast_i8x32_i8x16(a_));
		i16x16 hi = _mm256_cvtepu8_epi16(cast_i8x32_i8x16(movehl_i8x32(a_, a_)));
		return i16x32(lo, hi);
#elif EMU_SIMD_USE_128_REGISTERS
		u8x16 a_lane = cast_u8x32_u8x16(a_);
		i16x8 lo_lo = _mm_cvtepu8_epi16(a_lane);
		i16x8 lo_hi = _mm_cvtepu8_epi16(movehl_u8x16(a_lane, a_lane));
		a_lane = cast_u8x32_u8x16(movehl_u8x32(a_, a_));
		i16x8 hi_lo = _mm_cvtepu8_epi16(a_lane);
		i16x8 hi_hi = _mm_cvtepu8_epi16(movehl_i8x16(a_lane, a_lane));
		return i16x32(i16x16(lo_lo, lo_hi), i16x16(hi_lo, hi_hi));
#else
		return EmuSIMD::_underlying_impl::emulate_cvt<u16x32, std::uint16_t, 16, false, 32, false, std::uint8_t>(a_, std::make_index_sequence<32>());
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 cvt_u16x16_u16x32(u16x16_arg a_)
	{
		return cast_u16x16_u16x32(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 cvt_u32x8_u16x32(u32x8_arg a_)
	{
#if EMU_SIMD_USE_256_REGISTERS
		return cast_u16x8_u16x32(cvt_u32x8_u16x8(a_));
#else
		return EmuSIMD::_underlying_impl::emulate_cvt<u16x32, std::uint16_t, 8, false, 8, false, std::uint32_t>(a_, std::make_index_sequence<32>());
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 cvt_u64x4_u16x32(u64x4_arg a_)
	{
#if EMU_SIMD_USE_256_REGISTERS
		return cast_u16x8_u16x32(cvt_u64x4_u16x8(a_));
#else
		return EmuSIMD::_underlying_impl::emulate_cvt<u16x32, std::uint16_t, 16, false, 4, false, std::uint64_t>(a_, std::make_index_sequence<32>());
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 cvt_u8x64_u16x32(u8x64_arg a_)
	{
#if EMU_SIMD_USES_ANY_SIMD_REGISTERS
		return cvt_u8x32_u16x32(cast_u8x64_u8x32(a_));
#else
		return EmuSIMD::_underlying_impl::emulate_cvt<u16x32, std::uint16_t, 16, false, 64, false, std::uint8_t>(a_, std::make_index_sequence<32>());
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 cvt_u16x32_u16x32(u16x32_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 cvt_u32x16_u16x32(u32x16_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_castsi256_si512(_mm512_cvtepi32_epi16(a_));
#else
		return EmuSIMD::_underlying_impl::emulate_cvt<u16x32, std::uint16_t, 16, false, 16, false, std::uint32_t>(a_, std::make_index_sequence<32>());
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 cvt_u64x8_u16x32(u64x8_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_castsi128_si512(_mm512_cvtepi64_epi16(a_));
#else
		return EmuSIMD::_underlying_impl::emulate_cvt<u16x32, std::uint16_t, 16, false, 8, false, std::uint64_t>(a_, std::make_index_sequence<32>());
#endif
	}
#pragma endregion

#pragma region COMPARISONS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 cmpeq_u16x32(EmuSIMD::u16x32_arg lhs_, EmuSIMD::u16x32_arg rhs_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return setmasked_u16x32(_mm512_cmpeq_epu16_mask(lhs_, rhs_));
#else
		return u16x32(cmpeq_u16x16(lhs_._lane_0, rhs_._lane_0), cmpeq_u16x16(lhs_._lane_1, rhs_._lane_1));
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 cmpneq_u16x32(EmuSIMD::u16x32_arg lhs_, EmuSIMD::u16x32_arg rhs_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return setmasked_i8x64(_mm512_cmpneq_epu16_mask(lhs_, rhs_));
#else
		return u16x32(cmpneq_u16x16(lhs_._lane_0, rhs_._lane_0), cmpneq_u16x16(lhs_._lane_1, rhs_._lane_1));
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 cmpgt_u16x32(EmuSIMD::u16x32_arg lhs_, EmuSIMD::u16x32_arg rhs_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return setmasked_i8x64(_mm512_cmpgt_epu16_mask(rhs_, lhs_));
#else
		return u16x32(cmpgt_u16x16(lhs_._lane_0, rhs_._lane_0), cmpgt_u16x16(lhs_._lane_1, rhs_._lane_1));
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 cmplt_u16x32(EmuSIMD::u16x32_arg lhs_, EmuSIMD::u16x32_arg rhs_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return setmasked_i8x64(_mm512_cmplt_epu16_mask(lhs_, rhs_));
#else
		return u16x32(cmplt_u16x16(lhs_._lane_0, rhs_._lane_0), cmplt_u16x16(lhs_._lane_1, rhs_._lane_1));
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 cmpge_u16x32(EmuSIMD::u16x32_arg lhs_, EmuSIMD::u16x32_arg rhs_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return setmasked_i8x64(_mm512_cmpge_epu16_mask(rhs_, lhs_));
#else
		return u16x32(cmpge_u16x16(lhs_._lane_0, rhs_._lane_0), cmpge_u16x16(lhs_._lane_1, rhs_._lane_1));
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 cmple_u16x32(EmuSIMD::u16x32_arg lhs_, EmuSIMD::u16x32_arg rhs_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return setmasked_i8x64(_mm512_cmple_epu16_mask(lhs_, rhs_));
#else
		return u16x32(cmple_u16x16(lhs_._lane_0, rhs_._lane_0), cmple_u16x16(lhs_._lane_1, rhs_._lane_1));
#endif
	}
#pragma endregion

#pragma region MOVES
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 movehl_u16x32(EmuSIMD::u16x32_arg lhs_, EmuSIMD::u16x32_arg rhs_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return cast_f32x16_u16x32(movehl_f32x16(cast_u16x32_f32x16(lhs_), cast_u16x32_f32x16(rhs_)));
#else
		return EmuSIMD::_underlying_impl::emulated_movehl(lhs_, rhs_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 movelh_u16x32(EmuSIMD::u16x32_arg lhs_, EmuSIMD::u16x32_arg rhs_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return cast_f32x16_u16x32(movelh_f32x16(cast_u16x32_f32x16(lhs_), cast_u16x32_f32x16(rhs_)));
#else
		return EmuSIMD::_underlying_impl::emulated_movelh(lhs_, rhs_);
#endif
	}
#pragma endregion

#pragma region BITWISE_ARITHMETIC
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 and_u16x32(EmuSIMD::u16x32_arg lhs_, EmuSIMD::u16x32_arg rhs_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_and_si512(lhs_, rhs_);
#else
		using EmuSIMD::_underlying_impl::emulate_simd_basic;
		return emulate_simd_basic([](u16x16_arg a_, u16x16_arg b_) { return EmuSIMD::Funcs::and_u16x16(a_, b_); }, lhs_, rhs_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 or_u16x32(EmuSIMD::u16x32_arg lhs_, EmuSIMD::u16x32_arg rhs_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_or_si512(lhs_, rhs_);
#else
		using EmuSIMD::_underlying_impl::emulate_simd_basic;
		return emulate_simd_basic([](u16x16_arg a_, u16x16_arg b_) { return EmuSIMD::Funcs::or_u16x16(a_, b_); }, lhs_, rhs_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 xor_u16x32(EmuSIMD::u16x32_arg lhs_, EmuSIMD::u16x32_arg rhs_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_xor_si512(lhs_, rhs_);
#else
		using EmuSIMD::_underlying_impl::emulate_simd_basic;
		return emulate_simd_basic([](u16x16_arg a_, u16x16_arg b_) { return EmuSIMD::Funcs::xor_u16x16(a_, b_); }, lhs_, rhs_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 andnot_u16x32(EmuSIMD::u16x32_arg not_lhs_, EmuSIMD::u16x32_arg rhs_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_andnot_si512(not_lhs_, rhs_);
#else
		using EmuSIMD::_underlying_impl::emulate_simd_basic;
		return emulate_simd_basic([](u16x16_arg a_, u16x16_arg b_) { return EmuSIMD::Funcs::andnot_u16x16(a_, b_); }, not_lhs_, rhs_);
#endif
	}

	template<std::int32_t NumShifts_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 shift_left_u16x32(EmuSIMD::u16x32_arg lhs_)
	{
		if constexpr (NumShifts_ >= 16)
		{
			return setzero_u16x32();
		}
		else
		{
#if EMU_SIMD_USE_512_REGISTERS
			return _mm512_slli_epi16(lhs_, NumShifts_);
#else
			using EmuSIMD::_underlying_impl::emulate_simd_basic;
			return emulate_simd_basic([](u16x16_arg a_) { return shift_left_u16x16<NumShifts_>(a_); }, lhs_);
#endif
		}
	}

	template<std::int32_t NumShifts_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 shift_right_arithmetic_u16x32(EmuSIMD::u16x32_arg lhs_)
	{
		// No sign bit, so same as logical shift
		return shift_right_logical_u16x32<NumShifts_>(lhs_);
	}

	template<std::int32_t NumShifts_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 shift_right_logical_u16x32(EmuSIMD::u16x32_arg lhs_)
	{
		if constexpr (NumShifts_ >= 16)
		{
			return setzero_u16x32();
		}
		else
		{
#if EMU_SIMD_USE_512_REGISTERS
			return _mm512_srli_epi16(lhs_, NumShifts_);
#else
			using EmuSIMD::_underlying_impl::emulate_simd_basic;
			return emulate_simd_basic([](u16x16_arg a_) { return shift_right_logical_u16x16<NumShifts_>(a_); }, lhs_);
#endif
		}
	}
#pragma endregion

#pragma region BLENDS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 blendv_u16x32(EmuSIMD::u16x32_arg a_, EmuSIMD::u16x32_arg b_, EmuSIMD::u16x32_arg blend_mask_vec_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		auto blend_mask_for_8bit = blend_mask_vector_16_to_8(blend_mask_vec_);

		EmuSIMD::u8x32 half_a = _mm512_castsi512_si256(a_);
		EmuSIMD::u8x32 half_b = _mm512_castsi512_si256(b_);
		EmuSIMD::u8x32 half_mask = _mm512_castsi512_si256(blend_mask_for_8bit);
		EmuSIMD::u8x32 lo = _mm256_blendv_epi8(half_a, half_b, half_mask);

		half_a = _mm512_extracti32x8_epi32(a_, 1);
		half_b = _mm512_extracti32x8_epi32(b_, 1);
		half_mask = _mm512_extracti32x8_epi32(blend_mask_for_8bit, 1);
		half_b = _mm256_blendv_epi8(half_a, half_b, half_mask);

		return _mm512_inserti32x8(cast_u8x32_u16x32(lo), half_b, 1);
#else
		return u16x32(blendv_u16x16(a_._lane_0, b_._lane_0, blend_mask_vec_._lane_0), blendv_u16x16(a_._lane_1, b_._lane_1, blend_mask_vec_._lane_1));
#endif
	}
#pragma endregion

#pragma region MINMAX_FUNCS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 min_u16x32(EmuSIMD::u16x32_arg a_, EmuSIMD::u16x32_arg b_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_min_epu16(a_, b_);
#else
		return u16x32(min_u16x16(a_._lane_0, b_._lane_0), min_u16x16(a_._lane_1, b_._lane_1));
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 horizontal_min_u16x32(EmuSIMD::u16x32_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		u16x16 lane = min_u16x16(cast_u16x32_u16x16(a_), extract_u16x32_lane_u16x16<1>(a_));
		return cast_u16x16_u16x32(horizontal_min_u16x16(lane));
#else
		return EmuSIMD::_underlying_impl::emulate_horizontal_min_or_max<false, 16, true>(a_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 horizontal_min_fill_u16x32(EmuSIMD::u16x32_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		u16x16 lane = min_u16x16(cast_u16x32_u16x16(a_), extract_u16x32_lane_u16x16<1>(a_));
		lane = horizontal_min_fill_u16x16(lane);
		return _mm512_inserti32x8(cast_u16x16_u16x32(lane), lane, 1);
#else
		return EmuSIMD::_underlying_impl::emulate_horizontal_min_or_max<false, 16, true>(a_);
#endif
	}

	template<typename Out_>
	EMU_SIMD_COMMON_FUNC_SPEC auto horizontal_min_scalar_u16x32(EmuSIMD::u16x32_arg a_)
		-> typename std::remove_cvref<Out_>::type
	{
#if EMU_SIMD_USE_512_REGISTERS
		u16x16 lane = min_u16x16(cast_u16x32_u16x16(a_), extract_u16x32_lane_u16x16<1>(a_));
		return horizontal_min_scalar_u16x16<Out_>(lane);
#else
		return EmuSIMD::_underlying_impl::emulate_horizontal_min_or_max_scalar<Out_, false, 16, true>(a_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 max_u16x32(EmuSIMD::u16x32_arg a_, EmuSIMD::u16x32_arg b_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_max_epu16(a_, b_);
#else
		return u16x32(max_u16x16(a_._lane_0, b_._lane_0), max_u16x16(a_._lane_1, b_._lane_1));
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 horizontal_max_u16x32(EmuSIMD::u16x32_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		u16x16 lane = max_u16x16(cast_u16x32_u16x16(a_), extract_u16x32_lane_u16x16<1>(a_));
		return cast_u16x16_u16x32(horizontal_max_u16x16(lane));
#else
		return EmuSIMD::_underlying_impl::emulate_horizontal_min_or_max<false, 16, true>(a_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 horizontal_max_fill_u16x32(EmuSIMD::u16x32_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		u16x16 lane = max_u16x16(cast_u16x32_u16x16(a_), extract_u16x32_lane_u16x16<1>(a_));
		lane = horizontal_max_fill_u16x16(lane);
		return _mm512_inserti32x8(cast_u16x16_u16x32(lane), lane, 1);
#else
		return EmuSIMD::_underlying_impl::emulate_horizontal_min_or_max<false, 16, true>(a_);
#endif
	}

	template<typename Out_>
	EMU_SIMD_COMMON_FUNC_SPEC auto horizontal_max_scalar_u16x32(EmuSIMD::u16x32_arg a_)
		-> typename std::remove_cvref<Out_>::type
	{
#if EMU_SIMD_USE_512_REGISTERS
		u16x16 lane = max_u16x16(cast_u16x32_u16x16(a_), extract_u16x32_lane_u16x16<1>(a_));
		return horizontal_max_scalar_u16x16<Out_>(lane);
#else
		return EmuSIMD::_underlying_impl::emulate_horizontal_min_or_max_scalar<Out_, false, 16, true>(a_);
#endif
	}
#pragma endregion

#pragma region BASIC_ARITHMETIC
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 mul_all_u16x32(EmuSIMD::u16x32_arg lhs_, EmuSIMD::u16x32_arg rhs_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_mullo_epi16(lhs_, rhs_);
#else
		return EmuSIMD::_underlying_impl::emulate_simd_basic([](u16x16_arg lhs, u16x16_arg rhs) { return mul_all_u16x16(lhs, rhs); }, lhs_, rhs_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 negate_u16x32(EmuSIMD::u16x32_arg to_negate_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_sub_epi16(_mm512_setzero_si512(), to_negate_);
#else
		return EmuSIMD::_underlying_impl::emulate_simd_basic([](u16x16_arg to_negate) { return negate_u16x16(to_negate); }, to_negate_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 add_u16x32(EmuSIMD::u16x32_arg lhs_, EmuSIMD::u16x32_arg rhs_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_add_epi16(lhs_, rhs_);
#else
		return EmuSIMD::_underlying_impl::emulate_simd_basic([](u16x16_arg lhs, u16x16_arg rhs) { return add_u16x16(lhs, rhs); }, lhs_, rhs_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 sub_u16x32(EmuSIMD::u16x32_arg lhs_, EmuSIMD::u16x32_arg rhs_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_sub_epi16(lhs_, rhs_);
#else
		return EmuSIMD::_underlying_impl::emulate_simd_basic([](u16x16_arg lhs, u16x16_arg rhs) { return sub_u16x16(lhs, rhs); }, lhs_, rhs_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 div_u16x32(EmuSIMD::u16x32_arg lhs_, EmuSIMD::u16x32_arg rhs_)
	{
#if EMU_SIMD_USE_512_REGISTERS
#if EMU_CORE_X86_X64_SVML
		return _mm512_div_epu16(lhs_, rhs_);
#else
		// lo
		EmuSIMD::i32x16 lane64_a = cvt_u16x32_u32x16(lhs_);
		EmuSIMD::i32x16 lane64_b = cvt_u16x32_u32x16(rhs_);
		EmuSIMD::i16x32 lo = cvt_u32x16_u16x32(div_u32x16(lane64_a, lane64_b));

		// hi - move hi bits to lo
		EmuSIMD::i16x32 tmp_lane = movehl_u16x32(lhs_, lhs_);
		lane64_a = cvt_u16x32_u32x16(tmp_lane);

		tmp_lane = movehl_u16x32(rhs_, rhs_);
		lane64_b = cvt_u16x32_u32x16(tmp_lane);

		// Move hi and lo into the same register, in their respective 64-bit lanes
		EmuSIMD::i16x32 hi = cvt_u32x16_u16x32(div_u32x16(lane64_a, lane64_b));
		return movelh_u16x32(lo, hi);
#endif
#else
		return EmuSIMD::_underlying_impl::emulate_simd_basic([](u16x16_arg lhs, u16x16_arg rhs) { return div_u16x16(lhs, rhs); }, lhs_, rhs_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 addsub_u16x32(EmuSIMD::u16x32_arg lhs_, EmuSIMD::u16x32_arg rhs_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		constexpr std::uint16_t bytes_mask = static_cast<std::uint16_t>(0xFFFF);
		const EmuSIMD::u16x32 mask = _mm512_set_epi16
		(
			bytes_mask, 0, bytes_mask, 0, bytes_mask, 0, bytes_mask, 0, bytes_mask, 0, bytes_mask, 0, bytes_mask, 0, bytes_mask, 0,
			bytes_mask, 0, bytes_mask, 0, bytes_mask, 0, bytes_mask, 0, bytes_mask, 0, bytes_mask, 0, bytes_mask, 0, bytes_mask, 0
		);
		EmuSIMD::u16x32 out = _mm512_add_epi16(lhs_, _mm512_and_si512(mask, rhs_));
		return _mm512_sub_epi16(lhs_, _mm512_andnot_si512(mask, rhs_));
#else
		return EmuSIMD::_underlying_impl::emulate_simd_basic([](u16x16_arg lhs, u16x16_arg rhs) { return addsub_u16x16(lhs, rhs); }, lhs_, rhs_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 subadd_u16x32(EmuSIMD::u16x32_arg lhs_, EmuSIMD::u16x32_arg rhs_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		constexpr std::uint16_t bytes_mask = static_cast<std::uint16_t>(0xFFFF);
		const EmuSIMD::u16x32 mask = _mm512_set_epi16
		(
			bytes_mask, 0, bytes_mask, 0, bytes_mask, 0, bytes_mask, 0, bytes_mask, 0, bytes_mask, 0, bytes_mask, 0, bytes_mask, 0,
			bytes_mask, 0, bytes_mask, 0, bytes_mask, 0, bytes_mask, 0, bytes_mask, 0, bytes_mask, 0, bytes_mask, 0, bytes_mask, 0
		);
		EmuSIMD::u16x32 out = _mm512_sub_epi16(lhs_, _mm512_and_si512(mask, rhs_));
		return _mm512_add_epi16(lhs_, _mm512_andnot_si512(mask, rhs_));
#else
		return EmuSIMD::_underlying_impl::emulate_simd_basic([](u16x16_arg lhs, u16x16_arg rhs) { return subadd_u16x16(lhs, rhs); }, lhs_, rhs_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 fmadd_u16x32(EmuSIMD::u16x32_arg a_, EmuSIMD::u16x32_arg b_, EmuSIMD::u16x32_arg c_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_add_epi16(mul_all_u16x32(a_, b_), c_);
#else
		return EmuSIMD::_underlying_impl::emulate_simd_basic([](u16x16_arg a, u16x16_arg b, u16x16_arg c) { return fmadd_u16x16(a, b, c); }, a_, b_, c_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 fmsub_u16x32(EmuSIMD::u16x32_arg a_, EmuSIMD::u16x32_arg b_, EmuSIMD::u16x32_arg c_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_sub_epi16(mul_all_u16x32(a_, b_), c_);
#else
		return EmuSIMD::_underlying_impl::emulate_simd_basic([](u16x16_arg a, u16x16_arg b, u16x16_arg c) { return fmsub_u16x16(a, b, c); }, a_, b_, c_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 fnmadd_u16x32(EmuSIMD::u16x32_arg a_, EmuSIMD::u16x32_arg b_, EmuSIMD::u16x32_arg c_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_add_epi16(mul_all_u16x32(negate_u16x32(a_), b_), c_);
#else
		return EmuSIMD::_underlying_impl::emulate_simd_basic([](u16x16_arg a, u16x16_arg b, u16x16_arg c) { return fnmadd_u16x16(a, b, c); }, a_, b_, c_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 fnmsub_u16x32(EmuSIMD::u16x32_arg a_, EmuSIMD::u16x32_arg b_, EmuSIMD::u16x32_arg c_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_sub_epi16(mul_all_u16x32(negate_u16x32(a_), b_), c_);
#else
		return EmuSIMD::_underlying_impl::emulate_simd_basic([](u16x16_arg a, u16x16_arg b, u16x16_arg c) { return fnmsub_u16x16(a, b, c); }, a_, b_, c_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 fmaddsub_u16x32(EmuSIMD::u16x32_arg a_, EmuSIMD::u16x32_arg b_, EmuSIMD::u16x32_arg c_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return addsub_u16x32(mul_all_u16x32(a_, b_), c_);
#else
		return EmuSIMD::_underlying_impl::emulate_simd_basic([](u16x16_arg a, u16x16_arg b, u16x16_arg c) { return fmaddsub_u16x16(a, b, c); }, a_, b_, c_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 fmsubadd_u16x32(EmuSIMD::u16x32_arg a_, EmuSIMD::u16x32_arg b_, EmuSIMD::u16x32_arg c_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return subadd_u16x32(mul_all_u16x32(a_, b_), c_);
#else
		return EmuSIMD::_underlying_impl::emulate_simd_basic([](u16x16_arg a, u16x16_arg b, u16x16_arg c) { return fmsubadd_u16x16(a, b, c); }, a_, b_, c_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 floor_u16x32(EmuSIMD::u16x32_arg to_floor_)
	{
		return to_floor_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 ceil_u16x32(EmuSIMD::u16x32_arg to_ceil_)
	{
		return to_ceil_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 trunc_u16x32(EmuSIMD::u16x32_arg to_trunc_)
	{
		return to_trunc_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 mod_u16x32(EmuSIMD::u16x32_arg lhs_, EmuSIMD::u16x32_arg rhs_)
	{
#if EMU_SIMD_USE_512_REGISTERS
#if EMU_CORE_X86_X64_SVML
		return _mm512_rem_epu16(lhs_, rhs_);
#else
		EmuSIMD::u16x32 to_subtract = div_u16x32(lhs_, rhs_);
		to_subtract = mul_all_u16x32(to_subtract, rhs_);
		return sub_u16x32(lhs_, to_subtract);
#endif
#else
		return EmuSIMD::_underlying_impl::emulate_simd_basic([](u16x16_arg lhs, u16x16_arg rhs) { return mod_u16x16(lhs, rhs); }, lhs_, rhs_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 abs_u16x32(EmuSIMD::u16x32_arg in_)
	{
		return in_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 sqrt_u16x32(EmuSIMD::u16x32_arg in_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return emulate_fp_u16x32([](EmuSIMD::f32x16_arg in_fp_) { return sqrt_f32x16(in_fp_); }, in_);
#else
		return EmuSIMD::_underlying_impl::emulate_simd_basic([](u16x16_arg a) { return sqrt_u16x16(a); }, in_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 rsqrt_u16x32(EmuSIMD::u16x32_arg in_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return emulate_fp_u16x32([](EmuSIMD::f32x16_arg in_fp_) { return rsqrt_f32x16(in_fp_); }, in_);
#else
		return EmuSIMD::_underlying_impl::emulate_simd_basic([](u16x16_arg a) { return rsqrt_u16x16(a); }, in_);
#endif
	}
#pragma endregion

#pragma region NEAR_COMPARISONS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 cmpnear_u16x32(EmuSIMD::u16x32_arg lhs_, EmuSIMD::u16x32_arg rhs_)
	{
		return cmpeq_u16x32(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 cmpnear_u16x32(EmuSIMD::u16x32_arg lhs_, EmuSIMD::u16x32_arg rhs_, EmuSIMD::u16x32_arg epsilon)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return cmple_u16x32(sub_u16x32(lhs_, rhs_), epsilon);
#else
		return u16x32(cmpnear_u16x16(lhs_._lane_0, rhs_._lane_0, epsilon._lane_0), cmpnear_u16x16(lhs_._lane_1, rhs_._lane_1, epsilon._lane_1));
#endif
	}
#pragma endregion

#pragma region TRIG
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 cos_u16x32(EmuSIMD::u16x32_arg in_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return emulate_fp_u16x32([](EmuSIMD::f32x16_arg in_fp_) { return cos_f32x16(in_fp_); }, in_);
#else
		return EmuSIMD::_underlying_impl::emulate_simd_basic([](u16x16_arg a) { return cos_u16x16(a); }, in_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 sin_u16x32(EmuSIMD::u16x32_arg in_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return emulate_fp_u16x32([](EmuSIMD::f32x16_arg in_fp_) { return sin_f32x16(in_fp_); }, in_);
#else
		return EmuSIMD::_underlying_impl::emulate_simd_basic([](u16x16_arg a) { return sin_u16x16(a); }, in_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 tan_u16x32(EmuSIMD::u16x32_arg in_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return emulate_fp_u16x32([](EmuSIMD::f32x16_arg in_fp_) { return tan_f32x16(in_fp_); }, in_);
#else
		return EmuSIMD::_underlying_impl::emulate_simd_basic([](u16x16_arg a) { return tan_u16x16(a); }, in_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 acos_u16x32(EmuSIMD::u16x32_arg in_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return emulate_fp_u16x32([](EmuSIMD::f32x16_arg in_fp_) { return acos_f32x16(in_fp_); }, in_);
#else
		return EmuSIMD::_underlying_impl::emulate_simd_basic([](u16x16_arg a) { return acos_u16x16(a); }, in_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 asin_u16x32(EmuSIMD::u16x32_arg in_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return emulate_fp_u16x32([](EmuSIMD::f32x16_arg in_fp_) { return asin_f32x16(in_fp_); }, in_);
#else
		return EmuSIMD::_underlying_impl::emulate_simd_basic([](u16x16_arg a) { return asin_u16x16(a); }, in_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u16x32 atan_u16x32(EmuSIMD::u16x32_arg in_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return emulate_fp_u16x32([](EmuSIMD::f32x16_arg in_fp_) { return atan_f32x16(in_fp_); }, in_);
#else
		return EmuSIMD::_underlying_impl::emulate_simd_basic([](u16x16_arg a) { return atan_u16x16(a); }, in_);
#endif
	}
#pragma endregion
}

#endif
