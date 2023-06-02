#ifndef EMU_SIMD_GENERIC_FUNCS_I8X32_H_INC_
#define EMU_SIMD_GENERIC_FUNCS_I8X32_H_INC_ 1

#include "_generic_declarations/_all_generic_declarations.h"
#include "_common_generic_func_helpers.h"

namespace EmuSIMD::Funcs
{
#pragma region SETTERS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 set_i8x32
	(
		std::int8_t e0, std::int8_t e1, std::int8_t e2, std::int8_t e3, std::int8_t e4, std::int8_t e5, std::int8_t e6, std::int8_t e7,
		std::int8_t e8, std::int8_t e9, std::int8_t e10, std::int8_t e11, std::int8_t e12, std::int8_t e13, std::int8_t e14, std::int8_t e15,
		std::int8_t e16, std::int8_t e17, std::int8_t e18, std::int8_t e19, std::int8_t e20, std::int8_t e21, std::int8_t e22, std::int8_t e23,
		std::int8_t e24, std::int8_t e25, std::int8_t e26, std::int8_t e27, std::int8_t e28, std::int8_t e29, std::int8_t e30, std::int8_t e31
	)
	{
		return _mm256_set_epi8(e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19, e20, e21, e22, e23, e24, e25, e26, e27, e28, e29, e30, e31);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 setr_i8x32
	(
		std::int8_t e0, std::int8_t e1, std::int8_t e2, std::int8_t e3, std::int8_t e4, std::int8_t e5, std::int8_t e6, std::int8_t e7,
		std::int8_t e8, std::int8_t e9, std::int8_t e10, std::int8_t e11, std::int8_t e12, std::int8_t e13, std::int8_t e14, std::int8_t e15,
		std::int8_t e16, std::int8_t e17, std::int8_t e18, std::int8_t e19, std::int8_t e20, std::int8_t e21, std::int8_t e22, std::int8_t e23,
		std::int8_t e24, std::int8_t e25, std::int8_t e26, std::int8_t e27, std::int8_t e28, std::int8_t e29, std::int8_t e30, std::int8_t e31
	)
	{
		//return _mm256_setr_epi8(e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19, e20, e21, e22, e23, e24, e25, e26, e27, e28, e29, e30, e31);
		return _mm256_set_epi8(e31, e30, e29, e28, e27, e26, e25, e24, e23, e22, e21, e20, e19, e18, e17, e16, e15, e14, e13, e12, e11, e10, e9, e8, e7, e6, e5, e4, e3, e2, e1, e0);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 set1_i8x32(std::int8_t all_)
	{
		return _mm256_set1_epi8(all_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 load_i8x32(const std::int8_t* p_to_load_)
	{
		return _mm256_loadu_si256(reinterpret_cast<const __m256i*>(p_to_load_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 aligned_load_i8x32(const std::int8_t* p_to_load_)
	{
		return _mm256_load_si256(reinterpret_cast<const __m256i*>(p_to_load_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 setzero_i8x32()
	{
		return _mm256_setzero_si256();
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 setmasked_i8x32(std::uint32_t bit_mask_)
	{
		constexpr std::int8_t element_mask = static_cast<std::int8_t>(0xFF);
		return _mm256_set_epi8
		(
			(bit_mask_  & 0x00000001)        * element_mask,
			((bit_mask_ & 0x00000002) >> 1)  * element_mask,
			((bit_mask_ & 0x00000004) >> 2)  * element_mask,
			((bit_mask_ & 0x00000008) >> 3)  * element_mask,
			((bit_mask_ & 0x00000010) >> 4)  * element_mask,
			((bit_mask_ & 0x00000020) >> 5)  * element_mask,
			((bit_mask_ & 0x00000040) >> 6)  * element_mask,
			((bit_mask_ & 0x00000080) >> 7)  * element_mask,
			((bit_mask_ & 0x00000100) >> 8)  * element_mask,
			((bit_mask_ & 0x00000200) >> 9)  * element_mask,
			((bit_mask_ & 0x00000400) >> 10) * element_mask,
			((bit_mask_ & 0x00000800) >> 11) * element_mask,
			((bit_mask_ & 0x00001000) >> 12) * element_mask,
			((bit_mask_ & 0x00002000) >> 13) * element_mask,
			((bit_mask_ & 0x00004000) >> 14) * element_mask,
			((bit_mask_ & 0x00008000) >> 15) * element_mask,
			((bit_mask_ & 0x00010000) >> 16) * element_mask,
			((bit_mask_ & 0x00020000) >> 17) * element_mask,
			((bit_mask_ & 0x00040000) >> 18) * element_mask,
			((bit_mask_ & 0x00080000) >> 19) * element_mask,
			((bit_mask_ & 0x00100000) >> 20) * element_mask,
			((bit_mask_ & 0x00200000) >> 21) * element_mask,
			((bit_mask_ & 0x00400000) >> 22) * element_mask,
			((bit_mask_ & 0x00800000) >> 23) * element_mask,
			((bit_mask_ & 0x01000000) >> 24) * element_mask,
			((bit_mask_ & 0x02000000) >> 25) * element_mask,
			((bit_mask_ & 0x04000000) >> 26) * element_mask,
			((bit_mask_ & 0x08000000) >> 27) * element_mask,
			((bit_mask_ & 0x10000000) >> 28) * element_mask,
			((bit_mask_ & 0x20000000) >> 29) * element_mask,
			((bit_mask_ & 0x40000000) >> 30) * element_mask,
			((bit_mask_ & 0x80000000) >> 31) * element_mask
		);
	}

	template<std::uint32_t BitMask_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 setmasked_i8x32()
	{
		if constexpr(BitMask_)
		{
			return set_i8x32
			(
				std::integral_constant<std::int8_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<0,  std::int8_t>(BitMask_)>::value,
				std::integral_constant<std::int8_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<1,  std::int8_t>(BitMask_)>::value,
				std::integral_constant<std::int8_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<2,  std::int8_t>(BitMask_)>::value,
				std::integral_constant<std::int8_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<3,  std::int8_t>(BitMask_)>::value,
				std::integral_constant<std::int8_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<4,  std::int8_t>(BitMask_)>::value,
				std::integral_constant<std::int8_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<5,  std::int8_t>(BitMask_)>::value,
				std::integral_constant<std::int8_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<6,  std::int8_t>(BitMask_)>::value,
				std::integral_constant<std::int8_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<7,  std::int8_t>(BitMask_)>::value,
				std::integral_constant<std::int8_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<8,  std::int8_t>(BitMask_)>::value,
				std::integral_constant<std::int8_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<9,  std::int8_t>(BitMask_)>::value,
				std::integral_constant<std::int8_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<10, std::int8_t>(BitMask_)>::value,
				std::integral_constant<std::int8_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<11, std::int8_t>(BitMask_)>::value,
				std::integral_constant<std::int8_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<12, std::int8_t>(BitMask_)>::value,
				std::integral_constant<std::int8_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<13, std::int8_t>(BitMask_)>::value,
				std::integral_constant<std::int8_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<14, std::int8_t>(BitMask_)>::value,
				std::integral_constant<std::int8_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<15, std::int8_t>(BitMask_)>::value,
				std::integral_constant<std::int8_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<16, std::int8_t>(BitMask_)>::value,
				std::integral_constant<std::int8_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<17, std::int8_t>(BitMask_)>::value,
				std::integral_constant<std::int8_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<18, std::int8_t>(BitMask_)>::value,
				std::integral_constant<std::int8_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<19, std::int8_t>(BitMask_)>::value,
				std::integral_constant<std::int8_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<20, std::int8_t>(BitMask_)>::value,
				std::integral_constant<std::int8_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<21, std::int8_t>(BitMask_)>::value,
				std::integral_constant<std::int8_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<22, std::int8_t>(BitMask_)>::value,
				std::integral_constant<std::int8_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<23, std::int8_t>(BitMask_)>::value,
				std::integral_constant<std::int8_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<24, std::int8_t>(BitMask_)>::value,
				std::integral_constant<std::int8_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<25, std::int8_t>(BitMask_)>::value,
				std::integral_constant<std::int8_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<26, std::int8_t>(BitMask_)>::value,
				std::integral_constant<std::int8_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<27, std::int8_t>(BitMask_)>::value,
				std::integral_constant<std::int8_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<28, std::int8_t>(BitMask_)>::value,
				std::integral_constant<std::int8_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<29, std::int8_t>(BitMask_)>::value,
				std::integral_constant<std::int8_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<30, std::int8_t>(BitMask_)>::value,
				std::integral_constant<std::int8_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<31, std::int8_t>(BitMask_)>::value
			);
		}
		else
		{
			return setzero_i8x32();
		}
	}

	template
	<
		bool I0_,  bool I1_,  bool I2_,  bool I3_,  bool I4_,  bool I5_,  bool I6_,  bool I7_,  bool I8_,  bool I9_,  bool I10_, bool I11_, bool I12_, bool I13_, bool I14_, bool I15_,
		bool I16_, bool I17_, bool I18_, bool I19_, bool I20_, bool I21_, bool I22_, bool I23_, bool I24_, bool I25_, bool I26_, bool I27_, bool I28_, bool I29_, bool I30_, bool I31_
	>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 set_index_mask_i8x32()
	{
		if constexpr
		(
			I0_  || I1_  || I2_  || I3_  || I4_  || I5_  || I6_  || I7_  || I8_  || I9_  || I10_ || I11_ || I12_ || I13_ || I14_ || I15_ ||
			I16_ || I17_ || I18_ || I19_ || I20_ || I21_ || I22_ || I23_ || I24_ || I25_ || I26_ || I27_ || I28_ || I29_ || I30_ || I31_
		)
		{
			return setmasked_i8x32
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
			return setzero_i8x32();
		}
	}

	template<bool Active_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 set_index_mask_i8x32()
	{
		if constexpr (Active_)
		{
			return setmasked_i8x32<EmuSIMD::Funcs::make_all_indices_set_mask<32, Active_>()>();
		}
		else
		{
			return setzero_i8x32();
		}
	}
#pragma endregion

#pragma region STORES
	EMU_SIMD_COMMON_FUNC_SPEC void store_i8x32(std::int8_t* p_out_, i8x32_arg a_)
	{
		_mm256_storeu_si256(reinterpret_cast<__m256i*>(p_out_), a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC void aligned_store_i8x32(std::int8_t* p_out_, i8x32_arg a_)
	{
		_mm256_store_si256(reinterpret_cast<__m256i*>(p_out_), a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC std::int8_t get_first_i8x32(i8x32_arg a_)
	{
		return get_first_i8x16(cast_i8x32_i8x16(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC std::uint32_t movemask_i8x32(i8x32_arg a_)
	{
		return static_cast<std::uint32_t>(_mm256_movemask_epi8(a_));
	}
#pragma endregion

#pragma region CASTS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 cast_f32x4_i8x32(f32x4_arg a_)
	{
		return _mm256_castsi128_si256(_mm_castps_si128(a_)); 
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 cast_f32x8_i8x32(f32x8_arg a_)
	{
		return _mm256_castps_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 cast_f32x16_i8x32(f32x16_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_castsi512_si256(_mm512_castps_si512(a_));
#else
		return _underlying_impl::emulate_simd_cast_lesser_width<i8x32>(a_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 cast_f64x2_i8x32(f64x2_arg a_)
	{
		return _mm256_castsi128_si256(_mm_castpd_si128(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 cast_f64x4_i8x32(f64x4_arg a_)
	{
		return _mm256_castpd_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 cast_f64x8_i8x32(f64x8_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_castsi512_si256(_mm512_castpd_si512(a_));
#else
		return _underlying_impl::emulate_simd_cast_lesser_width<i8x32>(a_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 cast_i8x16_i8x32(i8x16_arg a_)
	{
		return _mm256_castsi128_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 cast_i16x8_i8x32(i16x8_arg a_)
	{
		return _mm256_castsi128_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 cast_i32x4_i8x32(i32x4_arg a_)
	{
		return _mm256_castsi128_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 cast_i64x2_i8x32(i64x2_arg a_)
	{
		return _mm256_castsi128_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 cast_i8x32_i8x32(i8x32_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 cast_i16x16_i8x32(i16x16_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 cast_i32x8_i8x32(i32x8_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 cast_i64x4_i8x32(i64x4_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 cast_i8x64_i8x32(i8x64_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_castsi512_si256(a_);
#else
		return _underlying_impl::emulate_simd_cast_lesser_width<i8x32>(a_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 cast_i16x32_i8x32(i16x32_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_castsi512_si256(a_);
#else
		return _underlying_impl::emulate_simd_cast_lesser_width<i8x32>(a_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 cast_i32x16_i8x32(i32x16_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_castsi512_si256(a_);
#else
		return _underlying_impl::emulate_simd_cast_lesser_width<i8x32>(a_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 cast_i64x8_i8x32(i64x8_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_castsi512_si256(a_);
#else
		return _underlying_impl::emulate_simd_cast_lesser_width<i8x32>(a_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 cast_u8x16_i8x32(u8x16_arg a_)
	{
		return _mm256_castsi128_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 cast_u16x8_i8x32(u16x8_arg a_)
	{
		return _mm256_castsi128_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 cast_u32x4_i8x32(u32x4_arg a_)
	{
		return _mm256_castsi128_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 cast_u64x2_i8x32(u64x2_arg a_)
	{
		return _mm256_castsi128_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 cast_u8x32_i8x32(u8x32_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 cast_u16x16_i8x32(u16x16_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 cast_u32x8_i8x32(u32x8_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 cast_u64x4_i8x32(u64x4_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 cast_u8x64_i8x32(u8x64_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_castsi512_si256(a_);
#else
		return _underlying_impl::emulate_simd_cast_lesser_width<i8x32>(a_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 cast_u16x32_i8x32(u16x32_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_castsi512_si256(a_);
#else
		return _underlying_impl::emulate_simd_cast_lesser_width<i8x32>(a_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 cast_u32x16_i8x32(u32x16_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_castsi512_si256(a_);
#else
		return _underlying_impl::emulate_simd_cast_lesser_width<i8x32>(a_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 cast_u64x8_i8x32(u64x8_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_castsi512_si256(a_);
#else
		return _underlying_impl::emulate_simd_cast_lesser_width<i8x32>(a_);
#endif
	}
#pragma endregion

#pragma region CONVERSIONS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 cvt_f32x4_i8x32(f32x4_arg a_)
	{
		return cvt_i32x4_i8x32(_mm_cvtps_epi32(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 cvt_f32x8_i8x32(f32x8_arg a_)
	{
		return cvt_i32x8_i8x32(_mm256_cvtps_epi32(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 cvt_f32x16_i8x32(f32x16_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm256_castsi128_si256(_mm512_cvtepi32_epi8(_mm512_cvtps_epi32(a_)));
#else
		return EmuSIMD::_underlying_impl::emulate_cvt<i8x32, std::int8_t, 8, true, 16, true, float>(a_, std::make_index_sequence<32>());
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 cvt_f64x2_i8x32(f64x2_arg a_)
	{
		return cvt_i32x4_i8x32(_mm_cvtpd_epi32(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 cvt_f64x4_i8x32(f64x4_arg a_)
	{
		return cvt_i32x4_i8x32(_mm256_cvtpd_epi32(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 cvt_f64x8_i8x32(f64x8_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm256_castsi128_si256(_mm512_cvtepi64_epi8(_mm512_cvtpd_epi64(a_)));
#else
		return EmuSIMD::_underlying_impl::emulate_cvt<i8x32, std::int8_t, 8, true, 8, true, double>(a_, std::make_index_sequence<32>());
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 cvt_i8x16_i8x32(i8x16_arg a_)
	{
		return _mm256_castsi128_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 cvt_i16x8_i8x32(i16x8_arg a_)
	{
		return EmuSIMD::_underlying_impl::emulate_cvt<i8x32, std::int8_t, 8, true, 8, true, std::int16_t>(a_, std::make_index_sequence<32>());
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 cvt_i32x4_i8x32(i32x4_arg a_)
	{
		return EmuSIMD::_underlying_impl::emulate_cvt<i8x32, std::int8_t, 8, true, 4, true, std::int32_t>(a_, std::make_index_sequence<32>());
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 cvt_i64x2_i8x32(i64x2_arg a_)
	{
		return EmuSIMD::_underlying_impl::emulate_cvt<i8x32, std::int8_t, 8, true, 2, true, std::int64_t>(a_, std::make_index_sequence<32>());
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 cvt_i8x32_i8x32(i8x32_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 cvt_i16x16_i8x32(i16x16_arg a_)
	{
		return EmuSIMD::_underlying_impl::emulate_cvt<i8x32, std::int8_t, 8, true, 16, true, std::int16_t>(a_, std::make_index_sequence<32>());
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 cvt_i32x8_i8x32(i32x8_arg a_)
	{
		return EmuSIMD::_underlying_impl::emulate_cvt<i8x32, std::int8_t, 8, true, 8, true, std::int32_t>(a_, std::make_index_sequence<32>());
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 cvt_i64x4_i8x32(i64x4_arg a_)
	{
		return EmuSIMD::_underlying_impl::emulate_cvt<i8x32, std::int8_t, 8, true, 4, true, std::int64_t>(a_, std::make_index_sequence<32>());
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 cvt_i8x64_i8x32(i8x64_arg a_)
	{
		return cast_i8x64_i8x32(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 cvt_i16x32_i8x32(i16x32_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_cvtepi16_epi8(a_);
#else
		return EmuSIMD::_underlying_impl::emulate_cvt<i8x32, std::int8_t, 8, true, 8, true, double>(a_, std::make_index_sequence<32>());
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 cvt_i32x16_i8x32(i32x16_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm256_castsi128_si256(_mm512_cvtepi32_epi8(a_));
#else
		return EmuSIMD::_underlying_impl::emulate_cvt<i8x32, std::int8_t, 8, true, 16, true, std::int32_t>(a_, std::make_index_sequence<32>());
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 cvt_i64x8_i8x32(i64x8_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm256_castsi128_si256(_mm512_cvtepi64_epi8(a_));
#else
		return EmuSIMD::_underlying_impl::emulate_cvt<i8x32, std::int8_t, 8, true, 8, true, std::int64_t>(a_, std::make_index_sequence<32>());
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 cvt_u8x16_i8x32(u8x16_arg a_)
	{
		return _mm256_castsi128_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 cvt_u16x8_i8x32(u16x8_arg a_)
	{
		return EmuSIMD::_underlying_impl::emulate_cvt<i8x32, std::int8_t, 8, true, 8, false, std::uint16_t>(a_, std::make_index_sequence<32>());
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 cvt_u32x4_i8x32(u32x4_arg a_)
	{
		return EmuSIMD::_underlying_impl::emulate_cvt<i8x32, std::int8_t, 8, true, 4, false, std::uint32_t>(a_, std::make_index_sequence<32>());
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 cvt_u64x2_i8x32(u64x2_arg a_)
	{
		return EmuSIMD::_underlying_impl::emulate_cvt<i8x32, std::int8_t, 8, true, 2, false, std::uint64_t>(a_, std::make_index_sequence<32>());
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 cvt_u8x32_i8x32(u8x32_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 cvt_u16x16_i8x32(u16x16_arg a_)
	{
		return EmuSIMD::_underlying_impl::emulate_cvt<i8x32, std::int8_t, 8, true, 16, false, std::uint16_t>(a_, std::make_index_sequence<32>());
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 cvt_u32x8_i8x32(u32x8_arg a_)
	{
		return EmuSIMD::_underlying_impl::emulate_cvt<i8x32, std::int8_t, 8, true, 8, false, std::uint32_t>(a_, std::make_index_sequence<32>());
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 cvt_u64x4_i8x32(u64x4_arg a_)
	{
		return EmuSIMD::_underlying_impl::emulate_cvt<i8x32, std::int8_t, 8, true, 4, false, std::uint64_t>(a_, std::make_index_sequence<32>());
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 cvt_u8x64_i8x32(u8x64_arg a_)
	{
		return cast_u8x64_i8x32(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 cvt_u16x32_i8x32(u16x32_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_cvtepi16_epi8(a_);
#else
		return EmuSIMD::_underlying_impl::emulate_cvt<i8x32, std::int8_t, 8, true, 32, false, std::uint16_t>(a_, std::make_index_sequence<32>());
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 cvt_u32x16_i8x32(u32x16_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm256_castsi128_si256(_mm512_cvtepi32_epi8(a_));
#else
		return EmuSIMD::_underlying_impl::emulate_cvt<i8x32, std::int8_t, 8, true, 16, false, std::uint32_t>(a_, std::make_index_sequence<32>());
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 cvt_u64x8_i8x32(u64x8_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm256_castsi128_si256(_mm512_cvtepi64_epi8(a_));
#else
		return EmuSIMD::_underlying_impl::emulate_cvt<i8x32, std::int8_t, 8, true, 8, false, std::uint64_t>(a_, std::make_index_sequence<32>());
#endif
	}
#pragma endregion

#pragma region COMPARISONS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 cmpeq_i8x32(EmuSIMD::i8x32_arg lhs_, EmuSIMD::i8x32_arg rhs_)
	{
		return _mm256_cmpeq_epi8(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 cmpneq_i8x32(EmuSIMD::i8x32_arg lhs_, EmuSIMD::i8x32_arg rhs_)
	{
		constexpr std::int8_t mask = static_cast<std::int8_t>(0xFF);
		return _mm256_xor_si256(set1_i8x32(mask), _mm256_cmpeq_epi8(lhs_, rhs_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 cmpgt_i8x32(EmuSIMD::i8x32_arg lhs_, EmuSIMD::i8x32_arg rhs_)
	{
		return _mm256_cmpgt_epi8(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 cmplt_i8x32(EmuSIMD::i8x32_arg lhs_, EmuSIMD::i8x32_arg rhs_)
	{
		return _mm256_cmpgt_epi8(rhs_, lhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 cmpge_i8x32(EmuSIMD::i8x32_arg lhs_, EmuSIMD::i8x32_arg rhs_)
	{
		return _mm256_or_si256(_mm256_cmpgt_epi8(lhs_, rhs_), _mm256_cmpeq_epi8(lhs_, rhs_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 cmple_i8x32(EmuSIMD::i8x32_arg lhs_, EmuSIMD::i8x32_arg rhs_)
	{
		return _mm256_or_si256(_mm256_cmpgt_epi8(rhs_, lhs_), _mm256_cmpeq_epi8(lhs_, rhs_));
	}
#pragma endregion

#pragma region BLENDS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 blendv_i8x32(EmuSIMD::i8x32_arg a_, EmuSIMD::i8x32_arg b_, EmuSIMD::i8x32_arg shuffle_mask_vec_)
	{
		return _mm256_blendv_epi8(a_, b_, shuffle_mask_vec_);
	}
#pragma endregion

#pragma region MOVES
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 movehl_i8x32(EmuSIMD::i8x32_arg lhs_, EmuSIMD::i8x32_arg rhs_)
	{
		return cast_f32x8_i8x32(movehl_f32x8(cast_i8x32_f32x8(lhs_), cast_i8x32_f32x8(rhs_)));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 movelh_i8x32(EmuSIMD::i8x32_arg lhs_, EmuSIMD::i8x32_arg rhs_)
	{
		return cast_f32x8_i8x32(movelh_f32x8(cast_i8x32_f32x8(lhs_), cast_i8x32_f32x8(rhs_)));
	}
#pragma endregion

#pragma region BITWISE_ARITHMETIC
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 and_i8x32(EmuSIMD::i8x32_arg lhs_, EmuSIMD::i8x32_arg rhs_)
	{
#if EMU_SIMD_USE_256_REGISTERS
		return _mm256_and_si256(lhs_, rhs_);
#else
		using EmuSIMD::_underlying_impl::emulate_simd_basic;
		return emulate_simd_basic([](i8x16_arg a_, i8x16_arg b_) { return EmuSIMD::Funcs::and_i8x16(a_, b_); }, lhs_, rhs_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 or_i8x32(EmuSIMD::i8x32_arg lhs_, EmuSIMD::i8x32_arg rhs_)
	{
#if EMU_SIMD_USE_256_REGISTERS
		return _mm256_or_si256(lhs_, rhs_);
#else
		using EmuSIMD::_underlying_impl::emulate_simd_basic;
		return emulate_simd_basic([](i8x16_arg a_, i8x16_arg b_) { return EmuSIMD::Funcs::or_i8x16(a_, b_); }, lhs_, rhs_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 xor_i8x32(EmuSIMD::i8x32_arg lhs_, EmuSIMD::i8x32_arg rhs_)
	{
#if EMU_SIMD_USE_256_REGISTERS
		return _mm256_xor_si256(lhs_, rhs_);
#else
		using EmuSIMD::_underlying_impl::emulate_simd_basic;
		return emulate_simd_basic([](i8x16_arg a_, i8x16_arg b_) { return EmuSIMD::Funcs::xor_i8x16(a_, b_); }, lhs_, rhs_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 andnot_i8x32(EmuSIMD::i8x32_arg not_lhs_, EmuSIMD::i8x32_arg rhs_)
	{
#if EMU_SIMD_USE_256_REGISTERS
		return _mm256_andnot_si256(not_lhs_, rhs_);
#else
		using EmuSIMD::_underlying_impl::emulate_simd_basic;
		return emulate_simd_basic([](i8x16_arg a_, i8x16_arg b_) { return EmuSIMD::Funcs::andnot_i8x16(a_, b_); }, not_lhs_, rhs_);
#endif
	}

	template<std::int32_t NumShifts_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 shift_left_i8x32(EmuSIMD::i8x32_arg lhs_)
	{
		if constexpr (NumShifts_ >= 8)
		{
			return setzero_i8x32();
		}
		else
		{
#if EMU_SIMD_USE_256_REGISTERS
			constexpr std::int8_t remaining_bits = std::int8_t(0xFF << NumShifts_);
			EmuSIMD::i8x32 remaining_bits_mask = set1_i8x32(remaining_bits);
			return and_i8x32(remaining_bits_mask, _mm256_slli_epi32(lhs_, NumShifts_));
#else
			using EmuSIMD::_underlying_impl::emulate_simd_basic;
			return emulate_simd_basic([](i8x16_arg a_) { return shift_left_i8x16<NumShifts_>(a_); }, lhs_);
#endif
		}
	}

	template<std::int32_t NumShifts_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 shift_right_arithmetic_i8x32(EmuSIMD::i8x32_arg lhs_)
	{
		if constexpr (NumShifts_ >= 8)
		{
			return setzero_i8x32();
		}
		else
		{
#if EMU_SIMD_USE_256_REGISTERS
			constexpr std::int8_t sign_bit = std::int8_t(0b10000000);
			EmuSIMD::i8x32 signs_mask = and_i8x32(set1_i8x32(sign_bit), lhs_);
			return or_i8x32(signs_mask, shift_right_logical_i8x32<NumShifts_>(lhs_));
#else
			using EmuSIMD::_underlying_impl::emulate_simd_basic;
			return emulate_simd_basic([](i8x16_arg a_) { return shift_right_arithmetic_i8x16<NumShifts_>(a_); }, lhs_);
#endif
		}
	}

	template<std::int32_t NumShifts_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 shift_right_logical_i8x32(EmuSIMD::i8x32_arg lhs_)
	{
		if constexpr (NumShifts_ >= 8)
		{
			return setzero_i8x32();
		}
		else
		{
#if EMU_SIMD_USE_256_REGISTERS
			constexpr std::int8_t remaining_bits = std::int8_t(0xFF >> NumShifts_);
			EmuSIMD::i8x32 remaining_bits_mask = set1_i8x32(remaining_bits);
			return and_i8x32(remaining_bits_mask, _mm256_slli_epi32(lhs_, NumShifts_));
#else
			using EmuSIMD::_underlying_impl::emulate_simd_basic;
			return emulate_simd_basic([](i8x16_arg a_) { return shift_right_logical_i8x16<NumShifts_>(a_); }, lhs_);
#endif
		}
	}
#pragma endregion

#pragma region MINMAX_FUNCS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 min_i8x32(EmuSIMD::i8x32_arg a_, EmuSIMD::i8x32_arg b_)
	{
		return _mm256_min_epi8(a_, b_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 horizontal_min_i8x32(EmuSIMD::i8x32_arg a_)
	{
		i8x16 lane = min_i8x16(cast_i8x32_i8x16(a_), extract_i8x32_lane_i8x16<1>(a_));
		lane = horizontal_min_i8x16(lane);
		return _mm256_inserti128_si256(cast_i8x16_i8x32(lane), lane, 1);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 max_i8x32(EmuSIMD::i8x32_arg a_, EmuSIMD::i8x32_arg b_)
	{
		return _mm256_max_epi8(a_, b_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 horizontal_max_i8x32(EmuSIMD::i8x32_arg a_)
	{
		i8x16 lane = max_i8x16(cast_i8x32_i8x16(a_), extract_i8x32_lane_i8x16<1>(a_));
		lane = horizontal_max_i8x16(lane);
		return _mm256_inserti128_si256(cast_i8x16_i8x32(lane), lane, 1);
	}
#pragma endregion

#pragma region BASIC_ARITHMETIC
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 mul_all_i8x32(EmuSIMD::i8x32_arg lhs_, EmuSIMD::i8x32_arg rhs_)
	{
		EmuSIMD::i8x32 even_bytes = _mm256_mullo_epi16(lhs_, rhs_);
		EmuSIMD::i8x32 odd_bytes = _mm256_mullo_epi16(_mm256_srli_epi16(lhs_, 8), _mm256_srli_epi16(rhs_, 8));
		return _mm256_or_si256(_mm256_slli_epi16(odd_bytes, 8), _mm256_srli_epi16(_mm256_slli_epi16(even_bytes, 8), 8));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 negate_i8x32(EmuSIMD::i8x32_arg to_negate_)
	{
		return _mm256_sub_epi8(_mm256_setzero_si256(), to_negate_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 add_i8x32(EmuSIMD::i8x32_arg lhs_, EmuSIMD::i8x32_arg rhs_)
	{
		return _mm256_add_epi8(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 sub_i8x32(EmuSIMD::i8x32_arg lhs_, EmuSIMD::i8x32_arg rhs_)
	{
		return _mm256_sub_epi8(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 div_i8x32(EmuSIMD::i8x32_arg lhs_, EmuSIMD::i8x32_arg rhs_)
	{
#if EMU_CORE_X86_X64_SVML
		return _mm256_div_epi8(lhs_, rhs_);
#else
		// lo
		EmuSIMD::i16x16 lane64_a = cvt_i8x32_i16x16(lhs_);
		EmuSIMD::i16x16 lane64_b = cvt_i8x32_i16x16(rhs_);
		EmuSIMD::i8x32 lo = cvt_i16x16_i8x32(div_i16x16(lane64_a, lane64_b));

		// hi - move hi bits to lo
		EmuSIMD::i8x32 tmp_lane = movehl_i8x32(lhs_, lhs_);
		lane64_a = cvt_i8x32_i16x16(tmp_lane);

		tmp_lane = movehl_i8x32(rhs_, rhs_);
		lane64_b = cvt_i8x32_i16x16(tmp_lane);

		// Move hi and lo into the same register, in their respective 64-bit lanes
		EmuSIMD::i8x32 hi = cvt_i16x16_i8x32(div_i16x16(lane64_a, lane64_b));
		return movelh_i8x32(lo, hi);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 addsub_i8x32(EmuSIMD::i8x32_arg lhs_, EmuSIMD::i8x32_arg rhs_)
	{
		constexpr std::int8_t byte_mask = static_cast<std::int8_t>(0xFF);
		const EmuSIMD::i8x32 mask = _mm256_set_epi8
		(
			byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0,
			byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0
		);
		EmuSIMD::i8x32 out = _mm256_add_epi8(lhs_, _mm256_and_si256(mask, rhs_));
		return _mm256_sub_epi8(lhs_, _mm256_andnot_si256(mask, rhs_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 subadd_i8x32(EmuSIMD::i8x32_arg lhs_, EmuSIMD::i8x32_arg rhs_)
	{
		constexpr std::int8_t byte_mask = static_cast<std::int8_t>(0xFF);
		const EmuSIMD::i8x32 mask = _mm256_set_epi8
		(
			byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0,
			byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0, byte_mask, 0
		);
		EmuSIMD::i8x32 out = _mm256_sub_epi8(lhs_, _mm256_and_si256(mask, rhs_));
		return _mm256_add_epi8(lhs_, _mm256_andnot_si256(mask, rhs_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 fmadd_i8x32(EmuSIMD::i8x32_arg a_, EmuSIMD::i8x32_arg b_, EmuSIMD::i8x32_arg c_)
	{
		return _mm256_add_epi8(mul_all_i8x32(a_, b_), c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 fmsub_i8x32(EmuSIMD::i8x32_arg a_, EmuSIMD::i8x32_arg b_, EmuSIMD::i8x32_arg c_)
	{
		return _mm256_sub_epi8(mul_all_i8x32(a_, b_), c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 fnmadd_i8x32(EmuSIMD::i8x32_arg a_, EmuSIMD::i8x32_arg b_, EmuSIMD::i8x32_arg c_)
	{
		return _mm256_add_epi8(mul_all_i8x32(negate_i8x32(a_), b_), c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 fnmsub_i8x32(EmuSIMD::i8x32_arg a_, EmuSIMD::i8x32_arg b_, EmuSIMD::i8x32_arg c_)
	{
		return _mm256_sub_epi8(mul_all_i8x32(negate_i8x32(a_), b_), c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 fmaddsub_i8x32(EmuSIMD::i8x32_arg a_, EmuSIMD::i8x32_arg b_, EmuSIMD::i8x32_arg c_)
	{
		return addsub_i8x32(mul_all_i8x32(negate_i8x32(a_), b_), c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 fmsubadd_i8x32(EmuSIMD::i8x32_arg a_, EmuSIMD::i8x32_arg b_, EmuSIMD::i8x32_arg c_)
	{
		return subadd_i8x32(mul_all_i8x32(negate_i8x32(a_), b_), c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 floor_i8x32(EmuSIMD::i8x32_arg to_floor_)
	{
		return to_floor_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 ceil_i8x32(EmuSIMD::i8x32_arg to_ceil_)
	{
		return to_ceil_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 trunc_i8x32(EmuSIMD::i8x32_arg to_trunc_)
	{
		return to_trunc_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 mod_i8x32(EmuSIMD::i8x32_arg lhs_, EmuSIMD::i8x32_arg rhs_)
	{
#if EMU_CORE_X86_X64_SVML
		return _mm256_rem_epi8(lhs_, rhs_);
#else
		EmuSIMD::i8x32 to_subtract = div_i8x32(lhs_, rhs_);
		to_subtract = mul_all_i8x32(to_subtract, rhs_);
		return sub_i8x32(lhs_, to_subtract);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 abs_i8x32(EmuSIMD::i8x32_arg in_)
	{
		return _mm256_abs_epi8(in_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 sqrt_i8x32(EmuSIMD::i8x32_arg in_)
	{
		return emulate_fp_i8x32([](EmuSIMD::f32x8_arg in_fp_) { return sqrt_f32x8(in_fp_); }, in_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 rsqrt_i8x32(EmuSIMD::i8x32_arg in_)
	{
		return emulate_fp_i8x32([](EmuSIMD::f32x8_arg in_fp_) { return rsqrt_f32x8(in_fp_); }, in_);
	}
#pragma endregion

#pragma region NEAR_COMPARISONS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 cmpnear_i8x32(EmuSIMD::i8x32_arg lhs_, EmuSIMD::i8x32_arg rhs_)
	{
		return cmpeq_i8x32(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 cmpnear_i8x32(EmuSIMD::i8x32_arg lhs_, EmuSIMD::i8x32_arg rhs_, EmuSIMD::i8x32_arg epsilon)
	{
		return cmple_i8x32(abs_i8x32(sub_i8x32(lhs_, rhs_)), epsilon);
	}
#pragma endregion

#pragma region TRIG
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 cos_i8x32(EmuSIMD::i8x32_arg in_)
	{
		return emulate_fp_i8x32([](EmuSIMD::f32x8_arg in_fp_) { return cos_f32x8(in_fp_); }, in_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 sin_i8x32(EmuSIMD::i8x32_arg in_)
	{
		return emulate_fp_i8x32([](EmuSIMD::f32x8_arg in_fp_) { return sin_f32x8(in_fp_); }, in_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 tan_i8x32(EmuSIMD::i8x32_arg in_)
	{
		return emulate_fp_i8x32([](EmuSIMD::f32x8_arg in_fp_) { return tan_f32x8(in_fp_); }, in_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 acos_i8x32(EmuSIMD::i8x32_arg in_)
	{
		return emulate_fp_i8x32([](EmuSIMD::f32x8_arg in_fp_) { return acos_f32x8(in_fp_); }, in_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 asin_i8x32(EmuSIMD::i8x32_arg in_)
	{
		return emulate_fp_i8x32([](EmuSIMD::f32x8_arg in_fp_) { return asin_f32x8(in_fp_); }, in_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i8x32 atan_i8x32(EmuSIMD::i8x32_arg in_)
	{
		return emulate_fp_i8x32([](EmuSIMD::f32x8_arg in_fp_) { return atan_f32x8(in_fp_); }, in_);
	}
#pragma endregion
}

#endif
