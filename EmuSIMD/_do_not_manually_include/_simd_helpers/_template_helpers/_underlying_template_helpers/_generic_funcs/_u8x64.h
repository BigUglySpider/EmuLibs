#ifndef EMU_SIMD_GENERIC_FUNCS_U8X64_H_INC_
#define EMU_SIMD_GENERIC_FUNCS_U8X64_H_INC_ 1

#include "_generic_declarations/_all_generic_declarations.h"
#include "_common_generic_func_helpers.h"

namespace EmuSIMD::Funcs
{
#pragma region SETTERS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 set_u8x64
	(
		std::uint8_t e0, std::uint8_t e1, std::uint8_t e2, std::uint8_t e3, std::uint8_t e4, std::uint8_t e5, std::uint8_t e6, std::uint8_t e7,
		std::uint8_t e8, std::uint8_t e9, std::uint8_t e10, std::uint8_t e11, std::uint8_t e12, std::uint8_t e13, std::uint8_t e14, std::uint8_t e15,
		std::uint8_t e16, std::uint8_t e17, std::uint8_t e18, std::uint8_t e19, std::uint8_t e20, std::uint8_t e21, std::uint8_t e22, std::uint8_t e23,
		std::uint8_t e24, std::uint8_t e25, std::uint8_t e26, std::uint8_t e27, std::uint8_t e28, std::uint8_t e29, std::uint8_t e30, std::uint8_t e31,
		std::uint8_t e32, std::uint8_t e33, std::uint8_t e34, std::uint8_t e35, std::uint8_t e36, std::uint8_t e37, std::uint8_t e38, std::uint8_t e39,
		std::uint8_t e40, std::uint8_t e41, std::uint8_t e42, std::uint8_t e43, std::uint8_t e44, std::uint8_t e45, std::uint8_t e46, std::uint8_t e47,
		std::uint8_t e48, std::uint8_t e49, std::uint8_t e50, std::uint8_t e51, std::uint8_t e52, std::uint8_t e53, std::uint8_t e54, std::uint8_t e55,
		std::uint8_t e56, std::uint8_t e57, std::uint8_t e58, std::uint8_t e59, std::uint8_t e60, std::uint8_t e61, std::uint8_t e62, std::uint8_t e63
	)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_set_epi8
		(
			e0,  e1,  e2,  e3,  e4,  e5,  e6,  e7,  e8,  e9,  e10, e11, e12, e13, e14, e15, e16, e17, e18, e19, e20, e21, e22, e23, e24, e25, e26, e27, e28, e29, e30, e31,
			e32, e33, e34, e35, e36, e37, e38, e39, e40, e41, e42, e43, e44, e45, e46, e47, e48, e49, e50, e51, e52, e53, e54, e55, e56, e57, e58, e59, e60, e61, e62, e63
		);
#else
		return EmuSIMD::_underlying_impl::set_dual_lane_simd_emulator<false, 512, u8x32>
		(
			e0,  e1,  e2,  e3,  e4,  e5,  e6,  e7,  e8,  e9,  e10, e11, e12, e13, e14, e15, e16, e17, e18, e19, e20, e21, e22, e23, e24, e25, e26, e27, e28, e29, e30, e31,
			e32, e33, e34, e35, e36, e37, e38, e39, e40, e41, e42, e43, e44, e45, e46, e47, e48, e49, e50, e51, e52, e53, e54, e55, e56, e57, e58, e59, e60, e61, e62, e63
		);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 setr_u8x64
	(
		std::uint8_t e0, std::uint8_t e1, std::uint8_t e2, std::uint8_t e3, std::uint8_t e4, std::uint8_t e5, std::uint8_t e6, std::uint8_t e7,
		std::uint8_t e8, std::uint8_t e9, std::uint8_t e10, std::uint8_t e11, std::uint8_t e12, std::uint8_t e13, std::uint8_t e14, std::uint8_t e15,
		std::uint8_t e16, std::uint8_t e17, std::uint8_t e18, std::uint8_t e19, std::uint8_t e20, std::uint8_t e21, std::uint8_t e22, std::uint8_t e23,
		std::uint8_t e24, std::uint8_t e25, std::uint8_t e26, std::uint8_t e27, std::uint8_t e28, std::uint8_t e29, std::uint8_t e30, std::uint8_t e31,
		std::uint8_t e32, std::uint8_t e33, std::uint8_t e34, std::uint8_t e35, std::uint8_t e36, std::uint8_t e37, std::uint8_t e38, std::uint8_t e39,
		std::uint8_t e40, std::uint8_t e41, std::uint8_t e42, std::uint8_t e43, std::uint8_t e44, std::uint8_t e45, std::uint8_t e46, std::uint8_t e47,
		std::uint8_t e48, std::uint8_t e49, std::uint8_t e50, std::uint8_t e51, std::uint8_t e52, std::uint8_t e53, std::uint8_t e54, std::uint8_t e55,
		std::uint8_t e56, std::uint8_t e57, std::uint8_t e58, std::uint8_t e59, std::uint8_t e60, std::uint8_t e61, std::uint8_t e62, std::uint8_t e63
	)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_set_epi8
		(
			e63, e62, e61, e60, e59, e58, e57, e56, e55, e54, e53, e52, e51, e50, e49, e48, e47, e46, e45, e44, e43, e42, e41, e40, e39, e38, e37, e36, e35, e34, e33, e32,
			e31, e30, e29, e28, e27, e26, e25, e24, e23, e22, e21, e20, e19, e18, e17, e16, e15, e14, e13, e12, e11, e10, e9, e8, e7, e6, e5, e4, e3, e2, e1, e0
		);
#else
		return EmuSIMD::_underlying_impl::set_dual_lane_simd_emulator<true, 512, u8x32>
		(
			e0,  e1,  e2,  e3,  e4,  e5,  e6,  e7,  e8,  e9,  e10, e11, e12, e13, e14, e15, e16, e17, e18, e19, e20, e21, e22, e23, e24, e25, e26, e27, e28, e29, e30, e31,
			e32, e33, e34, e35, e36, e37, e38, e39, e40, e41, e42, e43, e44, e45, e46, e47, e48, e49, e50, e51, e52, e53, e54, e55, e56, e57, e58, e59, e60, e61, e62, e63
		);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 set1_u8x64(std::uint8_t all_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_set1_epi8(all_);
#else
		return EmuSIMD::_underlying_impl::set1_dual_lane_simd_emulator<512, u8x32, 8>(all_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 load_u8x64(const std::uint8_t* p_to_load_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_loadu_si512(p_to_load_);
#else
		return EmuSIMD::_underlying_impl::load_dual_lane_simd_emulator<512, u8x32>(p_to_load_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 aligned_load_u8x64(const std::uint8_t* p_to_load_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_load_si512(p_to_load_);
#else
		return EmuSIMD::_underlying_impl::load_dual_lane_simd_emulator<512, u8x32>(p_to_load_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 setzero_u8x64()
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_setzero_si512();
#else
		return EmuSIMD::_underlying_impl::set_dual_lane_simd_emulator<512, u8x32>();
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 setmasked_u8x64(std::uint64_t bit_mask_)
	{
		#if EMU_SIMD_USE_512_REGISTERS
		constexpr std::int8_t element_mask = static_cast<std::int8_t>(0xFF);
		return _mm512_set_epi8
		(
			static_cast<std::uint8_t>(bit_mask_  & 0x0000000000000001)        * element_mask,
			static_cast<std::uint8_t>((bit_mask_ & 0x0000000000000002) >> 1)  * element_mask,
			static_cast<std::uint8_t>((bit_mask_ & 0x0000000000000004) >> 2)  * element_mask,
			static_cast<std::uint8_t>((bit_mask_ & 0x0000000000000008) >> 3)  * element_mask,
			static_cast<std::uint8_t>((bit_mask_ & 0x0000000000000010) >> 4)  * element_mask,
			static_cast<std::uint8_t>((bit_mask_ & 0x0000000000000020) >> 5)  * element_mask,
			static_cast<std::uint8_t>((bit_mask_ & 0x0000000000000040) >> 6)  * element_mask,
			static_cast<std::uint8_t>((bit_mask_ & 0x0000000000000080) >> 7)  * element_mask,
			static_cast<std::uint8_t>((bit_mask_ & 0x0000000000000100) >> 8)  * element_mask,
			static_cast<std::uint8_t>((bit_mask_ & 0x0000000000000200) >> 9)  * element_mask,
			static_cast<std::uint8_t>((bit_mask_ & 0x0000000000000400) >> 10) * element_mask,
			static_cast<std::uint8_t>((bit_mask_ & 0x0000000000000800) >> 11) * element_mask,
			static_cast<std::uint8_t>((bit_mask_ & 0x0000000000001000) >> 12) * element_mask,
			static_cast<std::uint8_t>((bit_mask_ & 0x0000000000002000) >> 13) * element_mask,
			static_cast<std::uint8_t>((bit_mask_ & 0x0000000000004000) >> 14) * element_mask,
			static_cast<std::uint8_t>((bit_mask_ & 0x0000000000008000) >> 15) * element_mask,
			static_cast<std::uint8_t>((bit_mask_ & 0x0000000000010000) >> 16) * element_mask,
			static_cast<std::uint8_t>((bit_mask_ & 0x0000000000020000) >> 17) * element_mask,
			static_cast<std::uint8_t>((bit_mask_ & 0x0000000000040000) >> 18) * element_mask,
			static_cast<std::uint8_t>((bit_mask_ & 0x0000000000080000) >> 19) * element_mask,
			static_cast<std::uint8_t>((bit_mask_ & 0x0000000000100000) >> 20) * element_mask,
			static_cast<std::uint8_t>((bit_mask_ & 0x0000000000200000) >> 21) * element_mask,
			static_cast<std::uint8_t>((bit_mask_ & 0x0000000000400000) >> 22) * element_mask,
			static_cast<std::uint8_t>((bit_mask_ & 0x0000000000800000) >> 23) * element_mask,
			static_cast<std::uint8_t>((bit_mask_ & 0x0000000001000000) >> 24) * element_mask,
			static_cast<std::uint8_t>((bit_mask_ & 0x0000000002000000) >> 25) * element_mask,
			static_cast<std::uint8_t>((bit_mask_ & 0x0000000004000000) >> 26) * element_mask,
			static_cast<std::uint8_t>((bit_mask_ & 0x0000000008000000) >> 27) * element_mask,
			static_cast<std::uint8_t>((bit_mask_ & 0x0000000010000000) >> 28) * element_mask,
			static_cast<std::uint8_t>((bit_mask_ & 0x0000000020000000) >> 29) * element_mask,
			static_cast<std::uint8_t>((bit_mask_ & 0x0000000040000000) >> 30) * element_mask,
			static_cast<std::uint8_t>((bit_mask_ & 0x0000000080000000) >> 31) * element_mask,
			static_cast<std::uint8_t>((bit_mask_ & 0x0000000100000000) >> 32) * element_mask,
			static_cast<std::uint8_t>((bit_mask_ & 0x0000000200000000) >> 33) * element_mask,
			static_cast<std::uint8_t>((bit_mask_ & 0x0000000400000000) >> 34) * element_mask,
			static_cast<std::uint8_t>((bit_mask_ & 0x0000000800000000) >> 35) * element_mask,
			static_cast<std::uint8_t>((bit_mask_ & 0x0000001000000000) >> 36) * element_mask,
			static_cast<std::uint8_t>((bit_mask_ & 0x0000002000000000) >> 37) * element_mask,
			static_cast<std::uint8_t>((bit_mask_ & 0x0000004000000000) >> 38) * element_mask,
			static_cast<std::uint8_t>((bit_mask_ & 0x0000008000000000) >> 39) * element_mask,
			static_cast<std::uint8_t>((bit_mask_ & 0x0000010000000000) >> 40) * element_mask,
			static_cast<std::uint8_t>((bit_mask_ & 0x0000020000000000) >> 41) * element_mask,
			static_cast<std::uint8_t>((bit_mask_ & 0x0000040000000000) >> 42) * element_mask,
			static_cast<std::uint8_t>((bit_mask_ & 0x0000080000000000) >> 43) * element_mask,
			static_cast<std::uint8_t>((bit_mask_ & 0x0000100000000000) >> 44) * element_mask,
			static_cast<std::uint8_t>((bit_mask_ & 0x0000200000000000) >> 45) * element_mask,
			static_cast<std::uint8_t>((bit_mask_ & 0x0000400000000000) >> 46) * element_mask,
			static_cast<std::uint8_t>((bit_mask_ & 0x0000800000000000) >> 47) * element_mask,
			static_cast<std::uint8_t>((bit_mask_ & 0x0001000000000000) >> 48) * element_mask,
			static_cast<std::uint8_t>((bit_mask_ & 0x0002000000000000) >> 49) * element_mask,
			static_cast<std::uint8_t>((bit_mask_ & 0x0004000000000000) >> 50) * element_mask,
			static_cast<std::uint8_t>((bit_mask_ & 0x0008000000000000) >> 51) * element_mask,
			static_cast<std::uint8_t>((bit_mask_ & 0x0010000000000000) >> 52) * element_mask,
			static_cast<std::uint8_t>((bit_mask_ & 0x0020000000000000) >> 53) * element_mask,
			static_cast<std::uint8_t>((bit_mask_ & 0x0040000000000000) >> 54) * element_mask,
			static_cast<std::uint8_t>((bit_mask_ & 0x0080000000000000) >> 55) * element_mask,
			static_cast<std::uint8_t>((bit_mask_ & 0x0100000000000000) >> 56) * element_mask,
			static_cast<std::uint8_t>((bit_mask_ & 0x0200000000000000) >> 57) * element_mask,
			static_cast<std::uint8_t>((bit_mask_ & 0x0400000000000000) >> 58) * element_mask,
			static_cast<std::uint8_t>((bit_mask_ & 0x0800000000000000) >> 59) * element_mask,
			static_cast<std::uint8_t>((bit_mask_ & 0x1000000000000000) >> 60) * element_mask,
			static_cast<std::uint8_t>((bit_mask_ & 0x2000000000000000) >> 61) * element_mask,
			static_cast<std::uint8_t>((bit_mask_ & 0x4000000000000000) >> 62) * element_mask,
			static_cast<std::uint8_t>((bit_mask_ & 0x8000000000000000) >> 63) * element_mask
		);
#else
		return EmuSIMD::_underlying_impl::setmasked_dual_lane_simd_emulator<512, u8x32, 64, std::uint32_t>(bit_mask_, [](std::uint32_t lane_mask) { return setmasked_u8x32(lane_mask); });
#endif
	}

	template<std::uint64_t BitMask_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 setmasked_u8x64()
	{
		if constexpr(BitMask_ != 0)
		{
#if EMU_SIMD_USE_512_REGISTERS
			return set_i8x64
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
				std::integral_constant<std::uint8_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<15, std::uint8_t>(BitMask_)>::value,
				std::integral_constant<std::uint8_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<16, std::uint8_t>(BitMask_)>::value,
				std::integral_constant<std::uint8_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<17, std::uint8_t>(BitMask_)>::value,
				std::integral_constant<std::uint8_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<18, std::uint8_t>(BitMask_)>::value,
				std::integral_constant<std::uint8_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<19, std::uint8_t>(BitMask_)>::value,
				std::integral_constant<std::uint8_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<20, std::uint8_t>(BitMask_)>::value,
				std::integral_constant<std::uint8_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<21, std::uint8_t>(BitMask_)>::value,
				std::integral_constant<std::uint8_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<22, std::uint8_t>(BitMask_)>::value,
				std::integral_constant<std::uint8_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<23, std::uint8_t>(BitMask_)>::value,
				std::integral_constant<std::uint8_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<24, std::uint8_t>(BitMask_)>::value,
				std::integral_constant<std::uint8_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<25, std::uint8_t>(BitMask_)>::value,
				std::integral_constant<std::uint8_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<26, std::uint8_t>(BitMask_)>::value,
				std::integral_constant<std::uint8_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<27, std::uint8_t>(BitMask_)>::value,
				std::integral_constant<std::uint8_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<28, std::uint8_t>(BitMask_)>::value,
				std::integral_constant<std::uint8_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<29, std::uint8_t>(BitMask_)>::value,
				std::integral_constant<std::uint8_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<30, std::uint8_t>(BitMask_)>::value,
				std::integral_constant<std::uint8_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<31, std::uint8_t>(BitMask_)>::value,
				std::integral_constant<std::uint8_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<32, std::uint8_t>(BitMask_)>::value,
				std::integral_constant<std::uint8_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<33, std::uint8_t>(BitMask_)>::value,
				std::integral_constant<std::uint8_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<34, std::uint8_t>(BitMask_)>::value,
				std::integral_constant<std::uint8_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<35, std::uint8_t>(BitMask_)>::value,
				std::integral_constant<std::uint8_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<36, std::uint8_t>(BitMask_)>::value,
				std::integral_constant<std::uint8_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<37, std::uint8_t>(BitMask_)>::value,
				std::integral_constant<std::uint8_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<38, std::uint8_t>(BitMask_)>::value,
				std::integral_constant<std::uint8_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<39, std::uint8_t>(BitMask_)>::value,
				std::integral_constant<std::uint8_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<40, std::uint8_t>(BitMask_)>::value,
				std::integral_constant<std::uint8_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<41, std::uint8_t>(BitMask_)>::value,
				std::integral_constant<std::uint8_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<42, std::uint8_t>(BitMask_)>::value,
				std::integral_constant<std::uint8_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<43, std::uint8_t>(BitMask_)>::value,
				std::integral_constant<std::uint8_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<44, std::uint8_t>(BitMask_)>::value,
				std::integral_constant<std::uint8_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<45, std::uint8_t>(BitMask_)>::value,
				std::integral_constant<std::uint8_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<46, std::uint8_t>(BitMask_)>::value,
				std::integral_constant<std::uint8_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<47, std::uint8_t>(BitMask_)>::value,
				std::integral_constant<std::uint8_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<48, std::uint8_t>(BitMask_)>::value,
				std::integral_constant<std::uint8_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<49, std::uint8_t>(BitMask_)>::value,
				std::integral_constant<std::uint8_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<50, std::uint8_t>(BitMask_)>::value,
				std::integral_constant<std::uint8_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<51, std::uint8_t>(BitMask_)>::value,
				std::integral_constant<std::uint8_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<52, std::uint8_t>(BitMask_)>::value,
				std::integral_constant<std::uint8_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<53, std::uint8_t>(BitMask_)>::value,
				std::integral_constant<std::uint8_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<54, std::uint8_t>(BitMask_)>::value,
				std::integral_constant<std::uint8_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<55, std::uint8_t>(BitMask_)>::value,
				std::integral_constant<std::uint8_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<56, std::uint8_t>(BitMask_)>::value,
				std::integral_constant<std::uint8_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<57, std::uint8_t>(BitMask_)>::value,
				std::integral_constant<std::uint8_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<58, std::uint8_t>(BitMask_)>::value,
				std::integral_constant<std::uint8_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<59, std::uint8_t>(BitMask_)>::value,
				std::integral_constant<std::uint8_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<60, std::uint8_t>(BitMask_)>::value,
				std::integral_constant<std::uint8_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<61, std::uint8_t>(BitMask_)>::value,
				std::integral_constant<std::uint8_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<62, std::uint8_t>(BitMask_)>::value,
				std::integral_constant<std::uint8_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<63, std::uint8_t>(BitMask_)>::value
			);
#else
			auto lane_setmasked = []<std::uint32_t lane_mask>() { return setmasked_u8x32<lane_mask>(); };
			return EmuSIMD::_underlying_impl::setmasked_dual_lane_simd_emulator<BitMask_, 512, u8x32, 64, std::uint32_t>(lane_setmasked);
#endif
		}
		else
		{
			return setzero_u8x64();
		}
	}

	template
	<
		bool I0_,  bool I1_,  bool I2_,  bool I3_,  bool I4_,  bool I5_,  bool I6_,  bool I7_,  bool I8_,  bool I9_,  bool I10_, bool I11_, bool I12_, bool I13_, bool I14_, bool I15_,
		bool I16_, bool I17_, bool I18_, bool I19_, bool I20_, bool I21_, bool I22_, bool I23_, bool I24_, bool I25_, bool I26_, bool I27_, bool I28_, bool I29_, bool I30_, bool I31_,
		bool I32_, bool I33_, bool I34_, bool I35_, bool I36_, bool I37_, bool I38_, bool I39_, bool I40_, bool I41_, bool I42_, bool I43_, bool I44_, bool I45_, bool I46_, bool I47_,
		bool I48_, bool I49_, bool I50_, bool I51_, bool I52_, bool I53_, bool I54_, bool I55_, bool I56_, bool I57_, bool I58_, bool I59_, bool I60_, bool I61_, bool I62_, bool I63_
	>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 set_index_mask_u8x64()
	{
		if constexpr
		(
			I0_  || I1_  || I2_  || I3_  || I4_  || I5_  || I6_  || I7_  || I8_  || I9_  || I10_ || I11_ || I12_ || I13_ || I14_ || I15_ ||
			I16_ || I17_ || I18_ || I19_ || I20_ || I21_ || I22_ || I23_ || I24_ || I25_ || I26_ || I27_ || I28_ || I29_ || I30_ || I31_ ||
			I32_ || I33_ || I34_ || I35_ || I36_ || I37_ || I38_ || I39_ || I40_ || I41_ || I42_ || I43_ || I44_ || I45_ || I46_ || I47_ ||
			I48_ || I49_ || I50_ || I51_ || I52_ || I53_ || I54_ || I55_ || I56_ || I57_ || I58_ || I59_ || I60_ || I61_ || I62_ || I63_
		)
		{
			return setmasked_u8x64
			<
				EmuSIMD::Funcs::make_index_set_mask
				<
					I0_,  I1_,  I2_,  I3_,  I4_,  I5_,  I6_,  I7_,  I8_,  I9_,  I10_, I11_, I12_, I13_, I14_, I15_,
					I16_, I17_, I18_, I19_, I20_, I21_, I22_, I23_, I24_, I25_, I26_, I27_, I28_, I29_, I30_, I31_,
					I32_, I33_, I34_, I35_, I36_, I37_, I38_, I39_, I40_, I41_, I42_, I43_, I44_, I45_, I46_, I47_,
					I48_, I49_, I50_, I51_, I52_, I53_, I54_, I55_, I56_, I57_, I58_, I59_, I60_, I61_, I62_, I63_
				>()
			>();
		}
		else
		{
			return setzero_u8x64();
		}
	}

	template<bool Active_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 set_index_mask_u8x64()
	{
		if constexpr (Active_)
		{
			return setmasked_u8x64<EmuSIMD::Funcs::make_all_indices_set_mask<64, Active_>()>();
		}
		else
		{
			return setzero_u8x64();
		}
	}
#pragma endregion

#pragma region STORES
	EMU_SIMD_COMMON_FUNC_SPEC void store_u8x64(std::uint8_t* p_out_, u8x64_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		_mm512_storeu_si512(p_out_, a_);
#else
		EmuSIMD::_underlying_impl::emulate_simd_store(a_, p_out_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC void aligned_store_u8x64(std::uint8_t* p_out_, u8x64_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		_mm512_store_si512(p_out_, a_);
#else
		EmuSIMD::_underlying_impl::emulate_simd_store(a_, p_out_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC std::uint8_t get_first_u8x64(u8x64_arg a_)
	{
		return get_first_u8x16(cast_u8x64_u8x16(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC std::uint64_t movemask_u8x64(u8x64_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return static_cast<std::uint64_t>(_mm512_movepi8_mask(a_));
#else
		return EmuSIMD::_underlying_impl::emulate_simd_movemask<std::uint64_t, 64>(a_);
#endif
	}
#pragma endregion

#pragma region CASTS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cast_f32x4_u8x64(f32x4_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_castsi128_si512(_mm_castps_si128(a_));
#else
		return EmuSIMD::_underlying_impl::emulate_simd_cast_greater_width<u8x64>(a_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cast_f32x8_u8x64(f32x8_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_castsi256_si512(_mm256_castps_si256(a_));
#else
		return EmuSIMD::_underlying_impl::emulate_simd_cast_greater_width<u8x64>(a_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cast_f32x16_u8x64(f32x16_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_castps_si512(a_);
#else
		return EmuSIMD::_underlying_impl::emulate_simd_cast_same_width<u8x32>(a_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cast_f64x2_u8x64(f64x2_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_castsi128_si512(_mm_castpd_si128(a_));
#else
		return EmuSIMD::_underlying_impl::emulate_simd_cast_greater_width<u8x64>(a_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cast_f64x4_u8x64(f64x4_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_castsi256_si512(_mm256_castpd_si256(a_));
#else
		return EmuSIMD::_underlying_impl::emulate_simd_cast_greater_width<u8x64>(a_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cast_f64x8_u8x64(f64x8_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_castpd_si512(a_);
#else
		return EmuSIMD::_underlying_impl::emulate_simd_cast_same_width<u8x32>(a_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cast_i8x16_u8x64(i8x16_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_castsi128_si512(a_);
#else
		return EmuSIMD::_underlying_impl::emulate_simd_cast_greater_width<u8x64>(a_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cast_i16x8_u8x64(i16x8_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_castsi128_si512(a_);
#else
		return EmuSIMD::_underlying_impl::emulate_simd_cast_greater_width<u8x64>(a_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cast_i32x4_u8x64(i32x4_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_castsi128_si512(a_);
#else
		return EmuSIMD::_underlying_impl::emulate_simd_cast_greater_width<u8x64>(a_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cast_i64x2_u8x64(i64x2_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_castsi128_si512(a_);
#else
		return EmuSIMD::_underlying_impl::emulate_simd_cast_greater_width<u8x64>(a_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cast_i8x32_u8x64(i8x32_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_castsi256_si512(a_);
#else
		return EmuSIMD::_underlying_impl::emulate_simd_cast_greater_width<u8x64>(a_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cast_i16x16_u8x64(i16x16_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_castsi256_si512(a_);
#else
		return EmuSIMD::_underlying_impl::emulate_simd_cast_greater_width<u8x64>(a_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cast_i32x8_u8x64(i32x8_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_castsi256_si512(a_);
#else
		return EmuSIMD::_underlying_impl::emulate_simd_cast_greater_width<u8x64>(a_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cast_i64x4_u8x64(i64x4_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_castsi256_si512(a_);
#else
		return EmuSIMD::_underlying_impl::emulate_simd_cast_greater_width<u8x64>(a_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cast_i8x64_u8x64(i8x64_arg a_)
	{
#if EMU_SIMD_USES_ANY_SIMD_REGISTERS && EMU_SIMD_USE_GENERIC_INT_REGISTERS
		return a_;
#else
		return EmuSIMD::_underlying_impl::emulate_simd_cast_same_width<u8x32>(a_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cast_i16x32_u8x64(i16x32_arg a_)
	{
#if EMU_SIMD_USES_ANY_SIMD_REGISTERS && EMU_SIMD_USE_GENERIC_INT_REGISTERS
		return a_;
#else
		return EmuSIMD::_underlying_impl::emulate_simd_cast_same_width<u8x32>(a_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cast_i32x16_u8x64(i32x16_arg a_)
	{
#if EMU_SIMD_USES_ANY_SIMD_REGISTERS && EMU_SIMD_USE_GENERIC_INT_REGISTERS
		return a_;
#else
		return EmuSIMD::_underlying_impl::emulate_simd_cast_same_width<u8x32>(a_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cast_i64x8_u8x64(i64x8_arg a_)
	{
#if EMU_SIMD_USES_ANY_SIMD_REGISTERS && EMU_SIMD_USE_GENERIC_INT_REGISTERS
		return a_;
#else
		return EmuSIMD::_underlying_impl::emulate_simd_cast_same_width<u8x32>(a_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cast_u8x16_u8x64(u8x16_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_castsi128_si512(a_);
#else
		return EmuSIMD::_underlying_impl::emulate_simd_cast_greater_width<u8x64>(a_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cast_u16x8_u8x64(u16x8_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_castsi128_si512(a_);
#else
		return EmuSIMD::_underlying_impl::emulate_simd_cast_greater_width<u8x64>(a_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cast_u32x4_u8x64(u32x4_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_castsi128_si512(a_);
#else
		return EmuSIMD::_underlying_impl::emulate_simd_cast_greater_width<u8x64>(a_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cast_u64x2_u8x64(u64x2_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_castsi128_si512(a_);
#else
		return EmuSIMD::_underlying_impl::emulate_simd_cast_greater_width<u8x64>(a_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cast_u8x32_u8x64(u8x32_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_castsi256_si512(a_);
#else
		return EmuSIMD::_underlying_impl::emulate_simd_cast_greater_width<u8x64>(a_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cast_u16x16_u8x64(u16x16_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_castsi256_si512(a_);
#else
		return EmuSIMD::_underlying_impl::emulate_simd_cast_greater_width<u8x64>(a_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cast_u32x8_u8x64(u32x8_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_castsi256_si512(a_);
#else
		return EmuSIMD::_underlying_impl::emulate_simd_cast_greater_width<u8x64>(a_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cast_u64x4_u8x64(u64x4_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_castsi256_si512(a_);
#else
		return EmuSIMD::_underlying_impl::emulate_simd_cast_greater_width<u8x64>(a_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cast_u8x64_u8x64(u8x64_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cast_u16x32_u8x64(u16x32_arg a_)
	{
#if EMU_SIMD_USES_ANY_SIMD_REGISTERS && EMU_SIMD_USE_GENERIC_INT_REGISTERS
		return a_;
#else
		return EmuSIMD::_underlying_impl::emulate_simd_cast_same_width<u8x32>(a_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cast_u32x16_u8x64(u32x16_arg a_)
	{
#if EMU_SIMD_USES_ANY_SIMD_REGISTERS && EMU_SIMD_USE_GENERIC_INT_REGISTERS
		return a_;
#else
		return EmuSIMD::_underlying_impl::emulate_simd_cast_same_width<u8x32>(a_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cast_u64x8_u8x64(u64x8_arg a_)
	{
#if EMU_SIMD_USES_ANY_SIMD_REGISTERS && EMU_SIMD_USE_GENERIC_INT_REGISTERS
		return a_;
#else
		return EmuSIMD::_underlying_impl::emulate_simd_cast_same_width<u8x32>(a_);
#endif
	}
#pragma endregion

#pragma region CONVERSIONS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cvt_f32x4_u8x64(f32x4_arg a_)
	{
#if EMU_SIMD_USE_128_REGISTERS
		return cvt_u32x4_u8x64(cvt_f32x4_u32x4(a_));
#else
		return EmuSIMD::_underlying_impl::emulate_cvt<u8x64, std::uint8_t, 8, false, 4, true, float>(a_, std::make_index_sequence<64>());
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cvt_f32x8_u8x64(f32x8_arg a_)
	{
#if EMU_SIMD_USE_256_REGISTERS
		return cvt_u32x8_u8x64(cvt_f32x8_u32x8(a_));
#else
		return EmuSIMD::_underlying_impl::emulate_cvt<u8x64, std::uint8_t, 8, false, 8, true, float>(a_, std::make_index_sequence<64>());
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cvt_f32x16_u8x64(f32x16_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return cvt_u32x16_u8x64(_mm512_cvtps_epu32(a_));
#else
		return EmuSIMD::_underlying_impl::emulate_cvt<u8x64, std::uint8_t, 8, false, 16, true, float>(a_, std::make_index_sequence<64>());
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cvt_f64x2_u8x64(f64x2_arg a_)
	{
#if EMU_SIMD_USE_128_REGISTERS
		return cvt_u32x4_u8x64(cvt_f64x2_u32x4(a_));
#else
		return EmuSIMD::_underlying_impl::emulate_cvt<i8x64, std::uint8_t, 8, false, 2, true, double>(a_, std::make_index_sequence<64>());
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cvt_f64x4_u8x64(f64x4_arg a_)
	{
#if EMU_SIMD_USE_128_REGISTERS
		return cvt_u32x4_u8x64(cvt_f64x4_u32x4(a_));
#else
		return EmuSIMD::_underlying_impl::emulate_cvt<i8x64, std::uint8_t, 8, false, 4, true, double>(a_, std::make_index_sequence<64>());
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cvt_f64x8_u8x64(f64x8_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_castsi128_si512(_mm512_cvtepi64_epi8(_mm512_cvtpd_epu64(a_)));
#else
		return EmuSIMD::_underlying_impl::emulate_cvt<i8x64, std::uint8_t, 8, false, 8, true, double>(a_, std::make_index_sequence<64>());
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cvt_i8x16_u8x64(i8x16_arg a_)
	{
		return cast_i8x16_u8x64(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cvt_i16x8_u8x64(i16x8_arg a_)
	{
#if EMU_SIMD_USE_128_REGISTERS
		return cast_u8x16_u8x64(cvt_i16x8_u8x16(a_));
#else
		return EmuSIMD::_underlying_impl::emulate_cvt<u8x64, std::uint8_t, 8, false, 8, true, std::int16_t>(a_, std::make_index_sequence<64>());
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cvt_i32x4_u8x64(i32x4_arg a_)
	{
#if EMU_SIMD_USE_128_REGISTERS
		return cast_u8x16_u8x64(cvt_i32x4_u8x16(a_));
#else
		return EmuSIMD::_underlying_impl::emulate_cvt<u8x64, std::uint8_t, 8, false, 4, true, std::int32_t>(a_, std::make_index_sequence<64>());
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cvt_i64x2_u8x64(i64x2_arg a_)
	{
#if EMU_SIMD_USE_128_REGISTERS
		return cast_u8x16_u8x64(cvt_i64x2_u8x16(a_));
#else
		return EmuSIMD::_underlying_impl::emulate_cvt<u8x64, std::uint8_t, 8, false, 2, true, std::int64_t>(a_, std::make_index_sequence<64>());
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cvt_i8x32_u8x64(i8x32_arg a_)
	{
		return cast_i8x32_u8x64(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cvt_i16x16_u8x64(i16x16_arg a_)
	{
#if EMU_SIMD_USE_256_REGISTERS
		return cast_u8x16_u8x64(cvt_i16x16_u8x16(a_));
#else
		return EmuSIMD::_underlying_impl::emulate_cvt<u8x64, std::uint8_t, 8, false, 16, true, std::int16_t>(a_, std::make_index_sequence<64>());
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cvt_i32x8_u8x64(i32x8_arg a_)
	{
#if EMU_SIMD_USE_256_REGISTERS
		return cast_u8x16_u8x64(cvt_i32x8_u8x16(a_));
#else
		return EmuSIMD::_underlying_impl::emulate_cvt<u8x64, std::uint8_t, 8, false, 8, true, std::int32_t>(a_, std::make_index_sequence<64>());
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cvt_i64x4_u8x64(i64x4_arg a_)
	{
#if EMU_SIMD_USE_256_REGISTERS
		return cast_u8x16_u8x64(cvt_i64x4_u8x16(a_));
#else
		return EmuSIMD::_underlying_impl::emulate_cvt<u8x64, std::uint8_t, 8, false, 4, true, std::int64_t>(a_, std::make_index_sequence<64>());
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cvt_i8x64_u8x64(i8x64_arg a_)
	{
		return cast_i8x64_u8x64(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cvt_i16x32_u8x64(i16x32_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_castsi256_si512(cvt_i16x32_i8x32(a_));
#else
		return EmuSIMD::_underlying_impl::emulate_cvt<u8x64, std::uint8_t, 8, false, 32, true, std::int16_t>(a_, std::make_index_sequence<64>());
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cvt_i32x16_u8x64(i32x16_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_castsi128_si512(_mm512_cvtepi32_epi8(a_));
#else
		return EmuSIMD::_underlying_impl::emulate_cvt<u8x64, std::uint8_t, 8, false, 16, true, std::int32_t>(a_, std::make_index_sequence<64>());
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cvt_i64x8_u8x64(i64x8_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_castsi128_si512(_mm512_cvtepi64_epi8(a_));
#else
		return EmuSIMD::_underlying_impl::emulate_cvt<u8x64, std::uint8_t, 8, false, 8, true, std::int64_t>(a_, std::make_index_sequence<64>());
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cvt_u8x16_u8x64(u8x16_arg a_)
	{
		return cast_u8x16_u8x64(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cvt_u16x8_u8x64(u16x8_arg a_)
	{
#if EMU_SIMD_USE_128_REGISTERS
		return cast_u8x16_u8x64(cvt_u16x8_u8x16(a_));
#else
		return EmuSIMD::_underlying_impl::emulate_cvt<u8x64, std::uint8_t, 8, false, 8, false, std::uint16_t>(a_, std::make_index_sequence<64>());
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cvt_u32x4_u8x64(u32x4_arg a_)
	{
#if EMU_SIMD_USE_128_REGISTERS
		return cast_u8x16_u8x64(cvt_u32x4_u8x16(a_));
#else
		return EmuSIMD::_underlying_impl::emulate_cvt<u8x64, std::uint8_t, 8, false, 4, false, std::uint32_t>(a_, std::make_index_sequence<64>());
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cvt_u64x2_u8x64(u64x2_arg a_)
	{
#if EMU_SIMD_USE_128_REGISTERS
		return cast_u8x16_u8x64(cvt_u64x2_u8x16(a_));
#else
		return EmuSIMD::_underlying_impl::emulate_cvt<u8x64, std::uint8_t, 8, false, 2, false, std::uint64_t>(a_, std::make_index_sequence<64>());
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cvt_u8x32_u8x64(u8x32_arg a_)
	{
		return cast_u8x32_u8x64(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cvt_u16x16_u8x64(u16x16_arg a_)
	{
#if EMU_SIMD_USE_256_REGISTERS
		return cast_u8x16_u8x64(cvt_u16x16_u8x16(a_));
#else
		return EmuSIMD::_underlying_impl::emulate_cvt<u8x64, std::uint8_t, 8, false, 16, false, std::uint16_t>(a_, std::make_index_sequence<64>());
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cvt_u32x8_u8x64(u32x8_arg a_)
	{
#if EMU_SIMD_USE_256_REGISTERS
		return cast_u8x16_u8x64(cvt_u32x8_u8x16(a_));
#else
		return EmuSIMD::_underlying_impl::emulate_cvt<u8x64, std::uint8_t, 8, false, 8, false, std::uint32_t>(a_, std::make_index_sequence<64>());
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cvt_u64x4_u8x64(u64x4_arg a_)
	{
#if EMU_SIMD_USE_256_REGISTERS
		return cast_u8x16_u8x64(cvt_u64x4_u8x16(a_));
#else
		return EmuSIMD::_underlying_impl::emulate_cvt<u8x64, std::uint8_t, 8, false, 4, false, std::uint64_t>(a_, std::make_index_sequence<64>());
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cvt_u8x64_u8x64(u8x64_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cvt_u16x32_u8x64(u16x32_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_castsi256_si512(_mm512_cvtepi16_epi8(a_));
#else
		return EmuSIMD::_underlying_impl::emulate_cvt<u8x64, std::uint8_t, 8, false, 32, false, std::uint16_t>(a_, std::make_index_sequence<64>());
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cvt_u32x16_u8x64(u32x16_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_castsi128_si512(_mm512_cvtepi32_epi8(a_));
#else
		return EmuSIMD::_underlying_impl::emulate_cvt<u8x64, std::uint8_t, 8, false, 16, false, std::uint32_t>(a_, std::make_index_sequence<64>());
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cvt_u64x8_u8x64(u64x8_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_castsi128_si512(_mm512_cvtepi64_epi8(a_));
#else
		return EmuSIMD::_underlying_impl::emulate_cvt<u8x64, std::uint8_t, 8, false, 8, false, std::uint64_t>(a_, std::make_index_sequence<64>());
#endif
	}
#pragma endregion

#pragma region COMPARISONS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cmpeq_u8x64(EmuSIMD::u8x64_arg lhs_, EmuSIMD::u8x64_arg rhs_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return setmasked_u8x64(_mm512_cmpeq_epu8_mask(lhs_, rhs_));
#else
		return u8x64(cmpeq_u8x32(lhs_._lane_0, rhs_._lane_0), cmpeq_u8x32(lhs_._lane_1, rhs_._lane_1));
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cmpneq_u8x64(EmuSIMD::u8x64_arg lhs_, EmuSIMD::u8x64_arg rhs_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return setmasked_u8x64(_mm512_cmpneq_epu8_mask(lhs_, rhs_));
#else
		return u8x64(cmpneq_u8x32(lhs_._lane_0, rhs_._lane_0), cmpneq_u8x32(lhs_._lane_1, rhs_._lane_1));
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cmpgt_u8x64(EmuSIMD::u8x64_arg lhs_, EmuSIMD::u8x64_arg rhs_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return setmasked_u8x64(_mm512_cmpgt_epu8_mask(lhs_, rhs_));
#else
		return u8x64(cmpgt_u8x32(lhs_._lane_0, rhs_._lane_0), cmpgt_u8x32(lhs_._lane_1, rhs_._lane_1));
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cmplt_u8x64(EmuSIMD::u8x64_arg lhs_, EmuSIMD::u8x64_arg rhs_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return setmasked_u8x64(_mm512_cmplt_epu8_mask(lhs_, rhs_));
#else
		return u8x64(cmplt_u8x32(lhs_._lane_0, rhs_._lane_0), cmplt_u8x32(lhs_._lane_1, rhs_._lane_1));
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cmpge_u8x64(EmuSIMD::u8x64_arg lhs_, EmuSIMD::u8x64_arg rhs_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return setmasked_u8x64(_mm512_cmpge_epu8_mask(lhs_, rhs_));
#else
		return u8x64(cmpge_u8x32(lhs_._lane_0, rhs_._lane_0), cmpge_u8x32(lhs_._lane_1, rhs_._lane_1));
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cmple_u8x64(EmuSIMD::u8x64_arg lhs_, EmuSIMD::u8x64_arg rhs_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return setmasked_u8x64(_mm512_cmple_epu8_mask(lhs_, rhs_));
#else
		return u8x64(cmple_u8x32(lhs_._lane_0, rhs_._lane_0), cmple_u8x32(lhs_._lane_1, rhs_._lane_1));
#endif
	}
#pragma endregion

#pragma region MOVES
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 movehl_u8x64(EmuSIMD::u8x64_arg lhs_, EmuSIMD::u8x64_arg rhs_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return cast_f32x16_u8x64(movehl_f32x16(cast_u8x64_f32x16(lhs_), cast_u8x64_f32x16(rhs_)));
#else
		return EmuSIMD::_underlying_impl::emulated_movehl(lhs_, rhs_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 movelh_u8x64(EmuSIMD::u8x64_arg lhs_, EmuSIMD::u8x64_arg rhs_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return cast_f32x16_u8x64(movelh_f32x16(cast_u8x64_f32x16(lhs_), cast_u8x64_f32x16(rhs_)));
#else
		return EmuSIMD::_underlying_impl::emulated_movelh(lhs_, rhs_);
#endif
	}
#pragma endregion

#pragma region BITWISE_ARITHMETIC
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 and_u8x64(EmuSIMD::u8x64_arg lhs_, EmuSIMD::u8x64_arg rhs_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_and_si512(lhs_, rhs_);
#else
		using EmuSIMD::_underlying_impl::emulate_simd_basic;
		return emulate_simd_basic([](u8x32_arg a_, u8x32_arg b_) { return EmuSIMD::Funcs::and_u8x32(a_, b_); }, lhs_, rhs_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 or_u8x64(EmuSIMD::u8x64_arg lhs_, EmuSIMD::u8x64_arg rhs_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_or_si512(lhs_, rhs_);
#else
		using EmuSIMD::_underlying_impl::emulate_simd_basic;
		return emulate_simd_basic([](u8x32_arg a_, u8x32_arg b_) { return EmuSIMD::Funcs::or_u8x32(a_, b_); }, lhs_, rhs_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 xor_u8x64(EmuSIMD::u8x64_arg lhs_, EmuSIMD::u8x64_arg rhs_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_xor_si512(lhs_, rhs_);
#else
		using EmuSIMD::_underlying_impl::emulate_simd_basic;
		return emulate_simd_basic([](u8x32_arg a_, u8x32_arg b_) { return EmuSIMD::Funcs::xor_u8x32(a_, b_); }, lhs_, rhs_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 andnot_u8x64(EmuSIMD::u8x64_arg not_lhs_, EmuSIMD::u8x64_arg rhs_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_andnot_si512(not_lhs_, rhs_);
#else
		using EmuSIMD::_underlying_impl::emulate_simd_basic;
		return emulate_simd_basic([](u8x32_arg a_, u8x32_arg b_) { return EmuSIMD::Funcs::andnot_u8x32(a_, b_); }, not_lhs_, rhs_);
#endif
	}

	template<std::int32_t NumShifts_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 shift_left_u8x64(EmuSIMD::u8x64_arg lhs_)
	{
		if constexpr (NumShifts_ >= 8)
		{
			return setzero_u8x64();
		}
		else
		{
#if EMU_SIMD_USE_512_REGISTERS
			constexpr std::uint8_t remaining_bits = std::uint8_t(0xFF << NumShifts_);
			EmuSIMD::u8x64 remaining_bits_mask = set1_u8x64(remaining_bits);
			return and_u8x64(remaining_bits_mask, _mm512_slli_epi32(lhs_, NumShifts_));
#else
			using EmuSIMD::_underlying_impl::emulate_simd_basic;
			return emulate_simd_basic([](u8x32_arg a_) { return shift_left_u8x32<NumShifts_>(a_); }, lhs_);
#endif
		}
	}

	template<std::int32_t NumShifts_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 shift_right_arithmetic_u8x64(EmuSIMD::u8x64_arg lhs_)
	{
		// No sign bit, so same as logical shift
		return shift_right_logical_u8x64<NumShifts_>(lhs_);
	}

	template<std::int32_t NumShifts_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 shift_right_logical_u8x64(EmuSIMD::u8x64_arg lhs_)
	{
		if constexpr (NumShifts_ >= 8)
		{
			return setzero_u8x64();
		}
		else
		{
#if EMU_SIMD_USE_512_REGISTERS
			constexpr std::uint8_t remaining_bits = std::uint8_t(0xFF >> NumShifts_);
			EmuSIMD::u8x64 remaining_bits_mask = set1_u8x64(remaining_bits);
			return and_u8x64(remaining_bits_mask, _mm512_slli_epi32(lhs_, NumShifts_));
#else
			using EmuSIMD::_underlying_impl::emulate_simd_basic;
			return emulate_simd_basic([](u8x32_arg a_) { return shift_right_logical_u8x32<NumShifts_>(a_); }, lhs_);
#endif
		}
	}
#pragma endregion

#pragma region BLENDS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 blendv_u8x64(EmuSIMD::u8x64_arg a_, EmuSIMD::u8x64_arg b_, EmuSIMD::u8x64_arg blend_mask_vec_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		EmuSIMD::u8x32 half_a = _mm512_castsi512_si256(a_);
		EmuSIMD::u8x32 half_b = _mm512_castsi512_si256(b_);
		EmuSIMD::u8x32 half_mask = _mm512_castsi512_si256(blend_mask_vec_);
		EmuSIMD::u8x32 lo = _mm256_blendv_epi8(half_a, half_b, half_mask);

		half_a = _mm512_extracti32x8_epi32(a_, 1);
		half_b = _mm512_extracti32x8_epi32(b_, 1);
		half_mask = _mm512_extracti32x8_epi32(blend_mask_vec_, 1);
		half_b = _mm256_blendv_epi8(half_a, half_b, half_mask);

		return _mm512_inserti32x8(cast_u8x32_u8x64(lo), half_b, 1);
#else
		return i8x64(blendv_u8x32(a_._lane_0, b_._lane_0, blend_mask_vec_._lane_0), blendv_u8x32(a_._lane_1, b_._lane_1, blend_mask_vec_._lane_1));
#endif
	}
#pragma endregion

#pragma region MINMAX_FUNCS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 min_u8x64(EmuSIMD::u8x64_arg a_, EmuSIMD::u8x64_arg b_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_min_epu8(a_, b_);
#else
		return EmuSIMD::_underlying_impl::emulate_simd_basic([](u8x32_arg a, u8x32_arg b) { return min_u8x32(a, b); }, a_, b_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 horizontal_min_u8x64(EmuSIMD::u8x64_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		u8x32 lane = min_u8x32(cast_u8x64_u8x32(a_), extract_u8x64_lane_u8x32<1>(a_));
		return cast_u8x32_u8x64(horizontal_min_u8x32(lane));
#else
		return EmuSIMD::_underlying_impl::emulate_horizontal_min_or_max<false, 8, false>(a_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 horizontal_min_fill_u8x64(EmuSIMD::u8x64_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		u8x32 lane = min_u8x32(cast_u8x64_u8x32(a_), extract_u8x64_lane_u8x32<1>(a_));
		lane = horizontal_min_fill_u8x32(lane);
		return _mm512_inserti32x8(cast_i8x32_i8x64(lane), lane, 1);
#else
		return EmuSIMD::_underlying_impl::emulate_horizontal_min_or_max<false, 8, false>(a_);
#endif
	}

	template<typename Out_>
	EMU_SIMD_COMMON_FUNC_SPEC auto horizontal_min_scalar_u8x64(EmuSIMD::u8x64_arg a_)
		-> typename std::remove_cvref<Out_>::type
	{
#if EMU_SIMD_USE_512_REGISTERS
		u8x32 lane = min_u8x32(cast_u8x64_u8x32(a_), extract_u8x64_lane_u8x32<1>(a_));
		return horizontal_min_scalar_u8x32<Out_>(lane);
#else
		return EmuSIMD::_underlying_impl::emulate_horizontal_min_or_max_scalar<Out_, false, 8, false>(a_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 max_u8x64(EmuSIMD::u8x64_arg a_, EmuSIMD::u8x64_arg b_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_max_epu8(a_, b_);
#else
		return EmuSIMD::_underlying_impl::emulate_simd_basic([](u8x32_arg a, u8x32_arg b) { return max_u8x32(a, b); }, a_, b_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 horizontal_max_u8x64(EmuSIMD::u8x64_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		u8x32 lane = max_u8x32(cast_u8x64_u8x32(a_), extract_u8x64_lane_u8x32<1>(a_));
		return cast_u8x32_u8x64(horizontal_max_u8x32(lane));
#else
		return EmuSIMD::_underlying_impl::emulate_horizontal_min_or_max<true, 8, false>(a_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 horizontal_max_fill_u8x64(EmuSIMD::u8x64_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		u8x32 lane = max_u8x32(cast_u8x64_u8x32(a_), extract_u8x64_lane_u8x32<1>(a_));
		lane = horizontal_max_fill_u8x32(lane);
		return _mm512_inserti32x8(cast_i8x32_i8x64(lane), lane, 1);
#else
		return EmuSIMD::_underlying_impl::emulate_horizontal_min_or_max<true, 8, false>(a_);
#endif
	}

	template<typename Out_>
	EMU_SIMD_COMMON_FUNC_SPEC auto horizontal_max_scalar_u8x64(EmuSIMD::u8x64_arg a_)
		-> typename std::remove_cvref<Out_>::type
	{
#if EMU_SIMD_USE_512_REGISTERS
		u8x32 lane = max_u8x32(cast_u8x64_u8x32(a_), extract_u8x64_lane_u8x32<1>(a_));
		return horizontal_max_scalar_u8x32<Out_>(lane);
#else
		return EmuSIMD::_underlying_impl::emulate_horizontal_min_or_max_scalar<Out_, true, 8, false>(a_);
#endif
	}
#pragma endregion

#pragma region BASIC_ARITHMETIC
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 mul_all_u8x64(EmuSIMD::u8x64_arg lhs_, EmuSIMD::u8x64_arg rhs_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		EmuSIMD::u8x64 even_bytes = _mm512_mullo_epi16(lhs_, rhs_);
		EmuSIMD::u8x64 odd_bytes = _mm512_mullo_epi16(_mm512_srli_epi16(lhs_, 8), _mm512_srli_epi16(rhs_, 8));
		return _mm512_or_si512(_mm512_slli_epi16(odd_bytes, 8), _mm512_srli_epi16(_mm512_slli_epi16(even_bytes, 8), 8));
#else
		return EmuSIMD::_underlying_impl::emulate_simd_basic([](u8x32_arg lhs, u8x32_arg rhs) { return mul_all_u8x32(lhs, rhs); }, lhs_, rhs_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 negate_u8x64(EmuSIMD::u8x64_arg to_negate_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_sub_epi8(_mm512_setzero_si512(), to_negate_);
#else
		return EmuSIMD::_underlying_impl::emulate_simd_basic([](u8x32_arg to_negate) { return negate_u8x32(to_negate); }, to_negate_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 add_u8x64(EmuSIMD::u8x64_arg lhs_, EmuSIMD::u8x64_arg rhs_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_add_epi8(lhs_, rhs_);
#else
		return EmuSIMD::_underlying_impl::emulate_simd_basic([](u8x32_arg lhs, u8x32_arg rhs) { return add_u8x32(lhs, rhs); }, lhs_, rhs_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 sub_u8x64(EmuSIMD::u8x64_arg lhs_, EmuSIMD::u8x64_arg rhs_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_sub_epi8(lhs_, rhs_);
#else
		return EmuSIMD::_underlying_impl::emulate_simd_basic([](u8x32_arg lhs, u8x32_arg rhs) { return sub_u8x32(lhs, rhs); }, lhs_, rhs_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 div_u8x64(EmuSIMD::u8x64_arg lhs_, EmuSIMD::u8x64_arg rhs_)
	{
#if EMU_SIMD_USE_512_REGISTERS
#if EMU_CORE_X86_X64_SVML
		return _mm512_div_epu8(lhs_, rhs_);
#else
		// lo
		EmuSIMD::u16x32 lane64_a = cvt_u8x64_u16x32(lhs_);
		EmuSIMD::u16x32 lane64_b = cvt_u8x64_u16x32(rhs_);
		EmuSIMD::u8x64 lo = cvt_u16x32_u8x64(div_i16x32(lane64_a, lane64_b));

		// hi - move hi bits to lo
		EmuSIMD::i8x64 tmp_lane = movehl_i8x64(lhs_, lhs_);
		lane64_a = cvt_i8x64_i16x32(tmp_lane);

		tmp_lane = movehl_i8x64(rhs_, rhs_);
		lane64_b = cvt_i8x64_i16x32(tmp_lane);

		// Move hi and lo into the same register, in their respective 64-bit lanes
		EmuSIMD::i8x64 hi = cvt_i16x32_i8x64(div_i16x32(lane64_a, lane64_b));
		return movelh_i8x64(lo, hi);
#endif
#else
		return EmuSIMD::_underlying_impl::emulate_simd_basic([](u8x32_arg lhs, u8x32_arg rhs) { return div_u8x32(lhs, rhs); }, lhs_, rhs_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 addsub_u8x64(EmuSIMD::u8x64_arg lhs_, EmuSIMD::u8x64_arg rhs_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		constexpr std::uint8_t byte_mask = static_cast<std::uint8_t>(0xFF);
		const EmuSIMD::u8x64 mask = _mm512_set_epi8
		(
			byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0,
			byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0,
			byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0,
			byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0
		);
		EmuSIMD::u8x64 out = _mm512_add_epi8(lhs_, _mm512_and_si512(mask, rhs_));
		return _mm512_sub_epi8(out, _mm512_andnot_si512(mask, rhs_));
#else
		return EmuSIMD::_underlying_impl::emulate_simd_basic([](u8x32_arg lhs, u8x32_arg rhs) { return addsub_u8x32(lhs, rhs); }, lhs_, rhs_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 subadd_u8x64(EmuSIMD::u8x64_arg lhs_, EmuSIMD::u8x64_arg rhs_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		constexpr std::uint8_t byte_mask = static_cast<std::uint8_t>(0xFF);
		const EmuSIMD::u8x64 mask = _mm512_set_epi8
		(
			byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0,
			byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0,
			byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0,
			byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0
		);
		EmuSIMD::u8x64 out = _mm512_sub_epi8(lhs_, _mm512_and_si512(mask, rhs_));
		return _mm512_add_epi8(out, _mm512_andnot_si512(mask, rhs_));
#else
		return EmuSIMD::_underlying_impl::emulate_simd_basic([](u8x32_arg lhs, u8x32_arg rhs) { return sub_u8x32(lhs, rhs); }, lhs_, rhs_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 fmadd_u8x64(EmuSIMD::u8x64_arg a_, EmuSIMD::u8x64_arg b_, EmuSIMD::u8x64_arg c_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_add_epi8(mul_all_u8x64(a_, b_), c_);
#else
		return EmuSIMD::_underlying_impl::emulate_simd_basic([](u8x32_arg a, u8x32_arg b, u8x32_arg c) { return fmadd_u8x32(a, b, c); }, a_, b_, c_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 fmsub_u8x64(EmuSIMD::u8x64_arg a_, EmuSIMD::u8x64_arg b_, EmuSIMD::u8x64_arg c_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_sub_epi8(mul_all_u8x64(a_, b_), c_);
#else
		return EmuSIMD::_underlying_impl::emulate_simd_basic([](u8x32_arg a, u8x32_arg b, u8x32_arg c) { return fmsub_u8x32(a, b, c); }, a_, b_, c_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 fnmadd_u8x64(EmuSIMD::u8x64_arg a_, EmuSIMD::u8x64_arg b_, EmuSIMD::u8x64_arg c_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_add_epi8(mul_all_u8x64(negate_u8x64(a_), b_), c_);
#else
		return EmuSIMD::_underlying_impl::emulate_simd_basic([](u8x32_arg a, u8x32_arg b, u8x32_arg c) { return fnmadd_u8x32(a, b, c); }, a_, b_, c_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 fnmsub_u8x64(EmuSIMD::u8x64_arg a_, EmuSIMD::u8x64_arg b_, EmuSIMD::u8x64_arg c_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_sub_epi8(mul_all_u8x64(negate_u8x64(a_), b_), c_);
#else
		return EmuSIMD::_underlying_impl::emulate_simd_basic([](u8x32_arg a, u8x32_arg b, u8x32_arg c) { return fnmsub_u8x32(a, b, c); }, a_, b_, c_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 fmaddsub_u8x64(EmuSIMD::u8x64_arg a_, EmuSIMD::u8x64_arg b_, EmuSIMD::u8x64_arg c_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return addsub_u8x64(mul_all_u8x64(negate_u8x64(a_), b_), c_);
#else
		return EmuSIMD::_underlying_impl::emulate_simd_basic([](u8x32_arg a, u8x32_arg b, u8x32_arg c) { return fmaddsub_u8x32(a, b, c); }, a_, b_, c_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 fmsubadd_u8x64(EmuSIMD::u8x64_arg a_, EmuSIMD::u8x64_arg b_, EmuSIMD::u8x64_arg c_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return subadd_u8x64(mul_all_u8x64(negate_u8x64(a_), b_), c_);
#else
		return EmuSIMD::_underlying_impl::emulate_simd_basic([](u8x32_arg a, u8x32_arg b, u8x32_arg c) { return fmsubadd_u8x32(a, b, c); }, a_, b_, c_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 floor_u8x64(EmuSIMD::u8x64_arg to_floor_)
	{
		return to_floor_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 ceil_u8x64(EmuSIMD::u8x64_arg to_ceil_)
	{
		return to_ceil_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 trunc_u8x64(EmuSIMD::u8x64_arg to_trunc_)
	{
		return to_trunc_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 mod_u8x64(EmuSIMD::u8x64_arg lhs_, EmuSIMD::u8x64_arg rhs_)
	{
#if EMU_SIMD_USE_512_REGISTERS
#if EMU_CORE_X86_X64_SVML
		return _mm512_rem_epu8(lhs_, rhs_);
#else
		EmuSIMD::u8x64 to_subtract = div_u8x64(lhs_, rhs_);
		to_subtract = mul_all_u8x64(to_subtract, rhs_);
		return sub_u8x64(lhs_, to_subtract);
#endif
#else
		return EmuSIMD::_underlying_impl::emulate_simd_basic([](u8x32_arg lhs, u8x32_arg rhs) { return sub_u8x32(lhs, rhs); }, lhs_, rhs_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 abs_u8x64(EmuSIMD::u8x64_arg in_)
	{
		return in_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 sqrt_u8x64(EmuSIMD::u8x64_arg in_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return emulate_fp_u8x64([](EmuSIMD::f32x16_arg in_fp_) { return sqrt_f32x16(in_fp_); }, in_);
#else
		return EmuSIMD::_underlying_impl::emulate_simd_basic([](u8x32_arg a) { return sqrt_u8x32(a); }, in_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 rsqrt_u8x64(EmuSIMD::u8x64_arg in_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return emulate_fp_u8x64([](EmuSIMD::f32x16_arg in_fp_) { return rsqrt_f32x16(in_fp_); }, in_);
#else
		return EmuSIMD::_underlying_impl::emulate_simd_basic([](u8x32_arg a) { return rsqrt_u8x32(a); }, in_);
#endif
	}
#pragma endregion

#pragma region NEAR_COMPARISONS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cmpnear_u8x64(EmuSIMD::u8x64_arg lhs_, EmuSIMD::u8x64_arg rhs_)
	{
		return cmpeq_u8x64(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cmpnear_u8x64(EmuSIMD::u8x64_arg lhs_, EmuSIMD::u8x64_arg rhs_, EmuSIMD::u8x64_arg epsilon)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return cmple_u8x64(sub_u8x64(lhs_, rhs_), epsilon);
#else
		return u8x64(cmpnear_u8x32(lhs_._lane_0, rhs_._lane_0, epsilon._lane_0), cmpnear_u8x32(lhs_._lane_1, rhs_._lane_1, epsilon._lane_1));
#endif
	}
#pragma endregion

#pragma region TRIG
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 cos_u8x64(EmuSIMD::u8x64_arg in_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return emulate_fp_u8x64([](EmuSIMD::f32x16_arg in_fp_) { return cos_f32x16(in_fp_); }, in_);
#else
		return EmuSIMD::_underlying_impl::emulate_simd_basic([](u8x32_arg a) { return cos_u8x32(a); }, in_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 sin_u8x64(EmuSIMD::u8x64_arg in_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return emulate_fp_u8x64([](EmuSIMD::f32x16_arg in_fp_) { return sin_f32x16(in_fp_); }, in_);
#else
		return EmuSIMD::_underlying_impl::emulate_simd_basic([](u8x32_arg a) { return sin_u8x32(a); }, in_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 tan_u8x64(EmuSIMD::u8x64_arg in_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return emulate_fp_u8x64([](EmuSIMD::f32x16_arg in_fp_) { return tan_f32x16(in_fp_); }, in_);
#else
		return EmuSIMD::_underlying_impl::emulate_simd_basic([](u8x32_arg a) { return tan_u8x32(a); }, in_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 acos_u8x64(EmuSIMD::u8x64_arg in_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return emulate_fp_u8x64([](EmuSIMD::f32x16_arg in_fp_) { return acos_f32x16(in_fp_); }, in_);
#else
		return EmuSIMD::_underlying_impl::emulate_simd_basic([](u8x32_arg a) { return acos_u8x32(a); }, in_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 asin_u8x64(EmuSIMD::u8x64_arg in_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return emulate_fp_u8x64([](EmuSIMD::f32x16_arg in_fp_) { return asin_f32x16(in_fp_); }, in_);
#else
		return EmuSIMD::_underlying_impl::emulate_simd_basic([](u8x32_arg a) { return asin_u8x32(a); }, in_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::u8x64 atan_u8x64(EmuSIMD::u8x64_arg in_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return emulate_fp_u8x64([](EmuSIMD::f32x16_arg in_fp_) { return atan_f32x16(in_fp_); }, in_);
#else
		return EmuSIMD::_underlying_impl::emulate_simd_basic([](u8x32_arg a) { return atan_u8x32(a); }, in_);
#endif
	}
#pragma endregion
}

#endif
