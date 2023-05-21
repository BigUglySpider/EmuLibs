#ifndef EMU_SIMD_GENERIC_FUNCS_I32X4_H_INC_
#define EMU_SIMD_GENERIC_FUNCS_I32X4_H_INC_ 1

#include "_generic_declarations/_all_generic_declarations.h"
#include "_common_generic_func_helpers.h"

namespace EmuSIMD::Funcs
{
#pragma region SETTERS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 set_i32x4(std::int32_t e0, std::int32_t e1, std::int32_t e2, std::int32_t e3)
	{
		return _mm_set_epi32(e0, e1, e2, e3);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 setr_i32x4(std::int32_t e0, std::int32_t e1, std::int32_t e2, std::int32_t e3)
	{
		// return _mm_setr_epi32(e0, e1, e2, e3);
		return _mm_set_epi32(e3, e2, e1, e0);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 set1_i32x4(std::int32_t all_)
	{
		return _mm_set1_epi32(all_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 load_i32x4(const std::int32_t* p_to_load_)
	{
		return _mm_loadu_si128(reinterpret_cast<const __m128i*>(p_to_load_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 aligned_load_i32x4(const std::int32_t* p_to_load_)
	{
		return _mm_load_si128(reinterpret_cast<const __m128i*>(p_to_load_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 setzero_i32x4()
	{
		return _mm_setzero_si128();
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 setmasked_i32x4(std::uint8_t bit_mask_)
	{
		constexpr std::int32_t element_mask = static_cast<std::int32_t>(0xFFFFFFFF);
		return _mm_set_epi32
		(
			(bit_mask_  & 0x01)       * element_mask,
			((bit_mask_ & 0x02) >> 1) * element_mask,
			((bit_mask_ & 0x04) >> 2) * element_mask,
			((bit_mask_ & 0x08) >> 3) * element_mask
		);
	}

	template<std::uint8_t BitMask_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 setmasked_i32x4()
	{
		if constexpr(BitMask_ != 0)
		{
			return set_i32x4
			(
				std::integral_constant<std::int32_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<0, std::int32_t>(BitMask_)>::value,
				std::integral_constant<std::int32_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<1, std::int32_t>(BitMask_)>::value,
				std::integral_constant<std::int32_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<2, std::int32_t>(BitMask_)>::value,
				std::integral_constant<std::int32_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<3, std::int32_t>(BitMask_)>::value
			);
		}
		else
		{
			return setzero_i32x4();
		}
	}

	template<bool I0_, bool I1_, bool I2_, bool I3_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 set_index_mask_i32x4()
	{
		if constexpr(I0_ || I1_ || I2_ || I3_)
		{
			return setmasked_i32x4<EmuSIMD::Funcs::make_index_set_mask<I0_, I1_, I2_, I3_>()>();
		}
		else
		{
			return setzero_i32x4();
		}
	}

	template<bool Active_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 set_index_mask_i32x4()
	{
		if constexpr (Active_)
		{
			return setmasked_i32x4<EmuSIMD::Funcs::make_all_indices_set_mask<4, Active_>()>();
		}
		else
		{
			return setzero_i32x4();
		}
	}
#pragma endregion

#pragma region STORES
	EMU_SIMD_COMMON_FUNC_SPEC void store_i32x4(std::int32_t* p_out_, i32x4_arg a_)
	{
		_mm_storeu_si128(reinterpret_cast<__m128i*>(p_out_), a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC void aligned_store_i32x4(std::int32_t* p_out_, i32x4_arg a_)
	{
		_mm_store_si128(reinterpret_cast<__m128i*>(p_out_), a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC std::int32_t get_first_i32x4(i32x4_arg a_)
	{
		return _mm_cvtsi128_si32(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC std::uint8_t movemask_i32x4(i32x4_arg a_)
	{
		return movemask_f32x4(cast_i32x4_f32x4(a_));
	}
#pragma endregion

#pragma region CASTS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cast_f32x4_i32x4(f32x4_arg a_)
	{
		return _mm_castps_si128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cast_f32x8_i32x4(f32x8_arg a_)
	{
		return _mm256_castsi256_si128(_mm256_castps_si256(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cast_f32x16_i32x4(f32x16_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm_castps_si128(_mm512_castps512_ps128(a_));
#else
		return EmuSIMD::_underlying_impl::emulate_simd_cast_lesser_width<i32x4>(a_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cast_f64x2_i32x4(f64x2_arg a_)
	{
		return _mm_castpd_si128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cast_f64x4_i32x4(f64x4_arg a_)
	{
		return _mm256_castsi256_si128(_mm256_castpd_si256(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cast_f64x8_i32x4(f64x8_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm_castpd_si128(_mm512_castpd512_pd128(a_));
#else
		return EmuSIMD::_underlying_impl::emulate_simd_cast_lesser_width<i32x4>(a_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cast_i8x16_i32x4(i8x16_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cast_i16x8_i32x4(i16x8_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cast_i32x4_i32x4(i32x4_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cast_i64x2_i32x4(i64x2_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cast_i8x32_i32x4(i8x32_arg a_)
	{
		return _mm256_castsi256_si128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cast_i16x16_i32x4(i16x16_arg a_)
	{
		return _mm256_castsi256_si128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cast_i32x8_i32x4(i32x8_arg a_)
	{
		return _mm256_castsi256_si128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cast_i64x4_i32x4(i64x4_arg a_)
	{
		return _mm256_castsi256_si128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cast_i8x64_i32x4(i8x64_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_castsi512_si128(a_);
#else
		return EmuSIMD::_underlying_impl::emulate_simd_cast_lesser_width<i32x4>(a_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cast_i16x32_i32x4(i16x32_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_castsi512_si128(a_);
#else
		return EmuSIMD::_underlying_impl::emulate_simd_cast_lesser_width<i32x4>(a_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cast_i32x16_i32x4(i32x16_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_castsi512_si128(a_);
#else
		return EmuSIMD::_underlying_impl::emulate_simd_cast_lesser_width<i32x4>(a_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cast_i64x8_i32x4(i64x8_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_castsi512_si128(a_);
#else
		return EmuSIMD::_underlying_impl::emulate_simd_cast_lesser_width<i32x4>(a_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cast_u8x16_i32x4(u8x16_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cast_u16x8_i32x4(u16x8_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cast_u32x4_i32x4(u32x4_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cast_u64x2_i32x4(u64x2_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cast_u8x32_i32x4(u8x32_arg a_)
	{
		return _mm256_castsi256_si128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cast_u16x16_i32x4(u16x16_arg a_)
	{
		return _mm256_castsi256_si128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cast_u32x8_i32x4(u32x8_arg a_)
	{
		return _mm256_castsi256_si128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cast_u64x4_i32x4(u64x4_arg a_)
	{
		return _mm256_castsi256_si128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cast_u8x64_i32x4(u8x64_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_castsi512_si128(a_);
#else
		return EmuSIMD::_underlying_impl::emulate_simd_cast_lesser_width<i32x4>(a_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cast_u16x32_i32x4(u16x32_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_castsi512_si128(a_);
#else
		return EmuSIMD::_underlying_impl::emulate_simd_cast_lesser_width<i32x4>(a_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cast_u32x16_i32x4(u32x16_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_castsi512_si128(a_);
#else
		return EmuSIMD::_underlying_impl::emulate_simd_cast_lesser_width<i32x4>(a_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cast_u64x8_i32x4(u64x8_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_castsi512_si128(a_);
#else
		return EmuSIMD::_underlying_impl::emulate_simd_cast_lesser_width<i32x4>(a_);
#endif
	}
#pragma endregion

#pragma region CONVERSIONS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cvt_f32x4_i32x4(f32x4_arg a_)
	{
		return _mm_cvtps_epi32(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cvt_f32x8_i32x4(f32x8_arg a_)
	{
		return _mm_cvtps_epi32(_mm256_castps256_ps128(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cvt_f32x16_i32x4(f32x16_arg a_)
	{
		return cvt_f32x4_i32x4(cast_f32x16_f32x4(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cvt_f64x2_i32x4(f64x2_arg a_)
	{
		return _mm_cvtpd_epi32(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cvt_f64x4_i32x4(f64x4_arg a_)
	{
		return _mm256_cvtpd_epi32(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cvt_f64x8_i32x4(f64x8_arg a_)
	{
		return cvt_f64x4_i32x4(cast_f64x8_f64x4(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cvt_i8x16_i32x4(i8x16_arg a_)
	{
		return _mm_cvtepi8_epi32(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cvt_i16x8_i32x4(i16x8_arg a_)
	{
		return _mm_cvtepi16_epi32(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cvt_i32x4_i32x4(i32x4_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cvt_i64x2_i32x4(i64x2_arg a_)
	{
		return EmuSIMD::_underlying_impl::emulate_cvt<i32x4, std::int32_t, 32, true, 2, true, std::int64_t>(a_, std::make_index_sequence<4>());
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cvt_i8x32_i32x4(i8x32_arg a_)
	{
		return _mm_cvtepi8_epi32(_mm256_castsi256_si128(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cvt_i16x16_i32x4(i16x16_arg a_)
	{
		return _mm_cvtepi16_epi32(_mm256_castsi256_si128(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cvt_i32x8_i32x4(i32x8_arg a_)
	{
		return _mm256_castsi256_si128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cvt_i64x4_i32x4(i64x4_arg a_)
	{
		return EmuSIMD::_underlying_impl::emulate_cvt<i32x4, std::int32_t, 32, true, 4, true, std::int64_t>(a_, std::make_index_sequence<4>());
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cvt_i8x64_i32x4(i8x64_arg a_)
	{
		return cvt_i8x16_i32x4(cast_i8x64_i8x16(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cvt_i16x32_i32x4(i16x32_arg a_)
	{
		return cvt_i16x8_i32x4(cast_i16x32_i16x8(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cvt_i32x16_i32x4(i32x16_arg a_)
	{
		return cast_i32x16_i32x4(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cvt_i64x8_i32x4(i64x8_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm256_cvtepi64_epi32(_mm512_castsi512_si256(a_));
#else
		return EmuSIMD::_underlying_impl::emulate_cvt<i32x4, std::int32_t, 32, true, 8, true, std::int64_t>(a_, std::make_index_sequence<4>());
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cvt_u8x16_i32x4(u8x16_arg a_)
	{
		return _mm_cvtepu8_epi32(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cvt_u16x8_i32x4(u16x8_arg a_)
	{
		return _mm_cvtepu16_epi32(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cvt_u32x4_i32x4(u32x4_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cvt_u64x2_i32x4(u64x2_arg a_)
	{
		return EmuSIMD::_underlying_impl::emulate_cvt<i32x4, std::int32_t, 32, true, 2, false, std::uint64_t>(a_, std::make_index_sequence<4>());
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cvt_u8x32_i32x4(u8x32_arg a_)
	{
		return _mm_cvtepu8_epi32(_mm256_castsi256_si128(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cvt_u16x16_i32x4(u16x16_arg a_)
	{
		return _mm_cvtepu16_epi32(_mm256_castsi256_si128(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cvt_u32x8_i32x4(u32x8_arg a_)
	{
		return _mm256_castsi256_si128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cvt_u64x4_i32x4(u64x4_arg a_)
	{
		return EmuSIMD::_underlying_impl::emulate_cvt<i32x4, std::int32_t, 32, true, 4, false, std::uint64_t>(a_, std::make_index_sequence<4>());
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cvt_u8x64_i32x4(u8x64_arg a_)
	{
		return cvt_u8x16_i32x4(cast_u8x64_u8x16(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cvt_u16x32_i32x4(u16x32_arg a_)
	{
		return cvt_u16x8_i32x4(cast_u16x32_u16x8(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cvt_u32x16_i32x4(u32x16_arg a_)
	{
		return cast_u32x16_i32x4(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cvt_u64x8_i32x4(u64x8_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm256_cvtepi64_epi32(_mm512_castsi512_si256(a_));
#else
		return EmuSIMD::_underlying_impl::emulate_cvt<i32x4, std::int32_t, 32, true, 8, false, std::uint64_t>(a_, std::make_index_sequence<4>());
#endif
	}
#pragma endregion

#pragma region COMPARISONS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cmpeq_i32x4(EmuSIMD::i32x4_arg lhs_, EmuSIMD::i32x4_arg rhs_)
	{
		return _mm_cmpeq_epi32(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cmpneq_i32x4(EmuSIMD::i32x4_arg lhs_, EmuSIMD::i32x4_arg rhs_)
	{
		constexpr std::int32_t mask = static_cast<std::int32_t>(0xFFFFFFFF);
		return _mm_xor_si128(set1_i32x4(mask), _mm_cmpeq_epi32(lhs_, rhs_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cmpgt_i32x4(EmuSIMD::i32x4_arg lhs_, EmuSIMD::i32x4_arg rhs_)
	{
		return _mm_cmpgt_epi32(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cmplt_i32x4(EmuSIMD::i32x4_arg lhs_, EmuSIMD::i32x4_arg rhs_)
	{
		return _mm_cmplt_epi32(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cmpge_i32x4(EmuSIMD::i32x4_arg lhs_, EmuSIMD::i32x4_arg rhs_)
	{
		return _mm_or_si128(_mm_cmpgt_epi32(lhs_, rhs_), _mm_cmpeq_epi32(lhs_, rhs_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cmple_i32x4(EmuSIMD::i32x4_arg lhs_, EmuSIMD::i32x4_arg rhs_)
	{
		return _mm_or_si128(_mm_cmplt_epi32(lhs_, rhs_), _mm_cmpeq_epi32(lhs_, rhs_));
	}
#pragma endregion

#pragma region BITWISE_ARITHMETIC
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 and_i32x4(EmuSIMD::i32x4_arg lhs_, EmuSIMD::i32x4_arg rhs_)
	{
#if EMU_SIMD_USE_128_REGISTERS
		return _mm_and_si128(lhs_, rhs_);
#else
		using EmuSIMD::_underlying_impl::emulate_simd_basic;
		using index_sequence = std::make_index_sequence<4>;
		return emulate_simd_basic(EmuCore::do_bitwise_and<std::int32_t>(), lhs_, rhs_, index_sequence());
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 or_i32x4(EmuSIMD::i32x4_arg lhs_, EmuSIMD::i32x4_arg rhs_)
	{
#if EMU_SIMD_USE_128_REGISTERS
		return _mm_or_si128(lhs_, rhs_);
#else
		using EmuSIMD::_underlying_impl::emulate_simd_basic;
		using index_sequence = std::make_index_sequence<4>;
		return emulate_simd_basic(EmuCore::do_bitwise_or<std::int32_t>(), lhs_, rhs_, index_sequence());
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 xor_i32x4(EmuSIMD::i32x4_arg lhs_, EmuSIMD::i32x4_arg rhs_)
	{
#if EMU_SIMD_USE_128_REGISTERS
		return _mm_xor_si128(lhs_, rhs_);
#else
		using EmuSIMD::_underlying_impl::emulate_simd_basic;
		using index_sequence = std::make_index_sequence<4>;
		return emulate_simd_basic(EmuCore::do_bitwise_xor<std::int32_t>(), lhs_, rhs_, index_sequence());
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 andnot_i32x4(EmuSIMD::i32x4_arg not_lhs_, EmuSIMD::i32x4_arg rhs_)
	{
#if EMU_SIMD_USE_128_REGISTERS
		return _mm_andnot_si128(not_lhs_, rhs_);
#else
		using EmuSIMD::_underlying_impl::emulate_simd_basic;
		using index_sequence = std::make_index_sequence<4>;
		return emulate_simd_basic(EmuCore::do_bitwise_andnot<std::int32_t>(), not_lhs_, rhs_, index_sequence());
#endif
	}

	template<std::int32_t NumShifts_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 shift_left_i32x4(EmuSIMD::i32x4_arg lhs_)
	{
		if constexpr (NumShifts_ >= 32)
		{
			return setzero_i32x4();
		}
		else
		{
#if EMU_SIMD_USE_128_REGISTERS
			return _mm_slli_epi32(lhs_, NumShifts_);
#else
			using EmuSIMD::_underlying_impl::emulate_simd_basic;
			using index_sequence = std::make_index_sequence<4>;
			auto func = [](const std::int32_t& a_) { return (a_ << NumShifts_); };
			return emulate_simd_basic(func, lhs_, index_sequence());
#endif
		}

	}

	template<std::int32_t NumShifts_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 shift_right_arithmetic_i32x4(EmuSIMD::i32x4_arg lhs_)
	{
		if constexpr (NumShifts_ >= 32)
		{
			return setzero_i32x4();
		}
		else
		{
#if EMU_SIMD_USE_128_REGISTERS
			return _mm_srai_epi32(lhs_, NumShifts_);
#else
			constexpr std::int32_t sign_bit = std::int32_t(0b10000000000000000000000000000000);
			using EmuSIMD::_underlying_impl::emulate_simd_basic;
			using index_sequence = std::make_index_sequence<4>;
			auto func = [](const std::int32_t& a_) { return (a_ >> NumShifts_) | (sign_bit & a_); };
			return emulate_simd_basic(func, lhs_, index_sequence());
#endif
		}
	}

	template<std::int32_t NumShifts_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 shift_right_logical_i32x4(EmuSIMD::i32x4_arg lhs_)
	{
		if constexpr (NumShifts_ >= 32)
		{
			return setzero_i32x4();
		}
		else
		{
#if EMU_SIMD_USE_128_REGISTERS
			return _mm_srli_epi32(lhs_, NumShifts_);
#else
			using EmuSIMD::_underlying_impl::emulate_simd_basic;
			using index_sequence = std::make_index_sequence<4>;
			auto func = [](const std::int32_t& a_) { return (a_ >> NumShifts_); };
			return emulate_simd_basic(func, lhs_, index_sequence());
#endif
		}
	}
#pragma endregion

#pragma region MOVES
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 movehl_i32x4(EmuSIMD::i32x4_arg lhs_, EmuSIMD::i32x4_arg rhs_)
	{
		return cast_f32x4_i32x4(movehl_f32x4(cast_i32x4_f32x4(lhs_), cast_i32x4_f32x4(rhs_)));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 movelh_i32x4(EmuSIMD::i32x4_arg lhs_, EmuSIMD::i32x4_arg rhs_)
	{
		return cast_f32x4_i32x4(movelh_f32x4(cast_i32x4_f32x4(lhs_), cast_i32x4_f32x4(rhs_)));
	}
#pragma endregion

#pragma region BLENDS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 blendv_i32x4(EmuSIMD::i32x4_arg a_, EmuSIMD::i32x4_arg b_, EmuSIMD::i32x4_arg shuffle_mask_vec_)
	{
		return cast_f32x4_i32x4
		(
			blendv_f32x4
			(
				cast_i32x4_f32x4(a_),
				cast_i32x4_f32x4(b_),
				cast_i32x4_f32x4(shuffle_mask_vec_)
			)
		);
	}
#pragma endregion

#pragma region MINMAX_FUNCS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 min_i32x4(EmuSIMD::i32x4_arg a_, EmuSIMD::i32x4_arg b_)
	{
		return _mm_min_epi32(a_, b_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 horizontal_min_i32x4(EmuSIMD::i32x4_arg a_)
	{
		EmuSIMD::i32x4 min = movehl_i32x4(a_, a_);
		min = min_i32x4(min, a_);
		min = min_i32x4
		(
			permute_i32x4<make_shuffle_mask_32<0, 1, 0, 1>()>(min),
			min
		);
		return permute_i32x4<make_shuffle_mask_32<0, 0, 0, 0>()>(min);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 max_i32x4(EmuSIMD::i32x4_arg a_, EmuSIMD::i32x4_arg b_)
	{
		return _mm_max_epi32(a_, b_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 horizontal_max_i32x4(EmuSIMD::i32x4_arg a_)
	{
		EmuSIMD::i32x4 max = movehl_i32x4(a_, a_);
		max = max_i32x4(max, a_);
		max = max_i32x4
		(
			permute_i32x4<make_shuffle_mask_32<0, 1, 0, 1>()>(max),
			max
		);
		return permute_i32x4<make_shuffle_mask_32<0, 0, 0, 0>()>(max);
	}
#pragma endregion

#pragma region BASIC_ARITHMETIC
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 mul_all_i32x4(EmuSIMD::i32x4_arg lhs_, EmuSIMD::i32x4_arg rhs_)
	{
		return _mm_mullo_epi32(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 negate_i32x4(EmuSIMD::i32x4_arg to_negate_)
	{
		return _mm_sub_epi32(_mm_setzero_si128(), to_negate_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 add_i32x4(EmuSIMD::i32x4_arg lhs_, EmuSIMD::i32x4_arg rhs_)
	{
		return _mm_add_epi32(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 sub_i32x4(EmuSIMD::i32x4_arg lhs_, EmuSIMD::i32x4_arg rhs_)
	{
		return _mm_sub_epi32(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 div_i32x4(EmuSIMD::i32x4_arg lhs_, EmuSIMD::i32x4_arg rhs_)
	{
#if EMU_CORE_X86_X64_SVML
		return _mm_div_epi32(lhs_, rhs_);
#else
		EmuSIMD::f32x4 result_f32 = cvt_i32x4_f32x4(lhs_);
		result_f32 = div_f32x4(result_f32, cvt_i32x4_f32x4(rhs_));
		return cvt_f32x4_i32x4(trunc_f32x4(result_f32));
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 addsub_i32x4(EmuSIMD::i32x4_arg lhs_, EmuSIMD::i32x4_arg rhs_)
	{
		constexpr std::int32_t bytes_mask = static_cast<std::int32_t>(0xFFFFFFFF);
		const EmuSIMD::i32x4 mask = _mm_set_epi32(bytes_mask, 0, bytes_mask, 0);
		EmuSIMD::i32x4 out = _mm_add_epi32(lhs_, _mm_and_si128(mask, rhs_));
		return _mm_sub_epi32(lhs_, _mm_andnot_si128(mask, rhs_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 subadd_i32x4(EmuSIMD::i32x4_arg lhs_, EmuSIMD::i32x4_arg rhs_)
	{
		constexpr std::int32_t bytes_mask = static_cast<std::int32_t>(0xFFFFFFFF);
		const EmuSIMD::i32x4 mask = _mm_set_epi32(bytes_mask, 0, bytes_mask, 0);
		EmuSIMD::i32x4 out = _mm_sub_epi32(lhs_, _mm_and_si128(mask, rhs_));
		return _mm_add_epi32(lhs_, _mm_andnot_si128(mask, rhs_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 fmadd_i32x4(EmuSIMD::i32x4_arg a_, EmuSIMD::i32x4_arg b_, EmuSIMD::i32x4_arg c_)
	{
		return _mm_add_epi32(mul_all_i32x4(a_, b_), c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 fmsub_i32x4(EmuSIMD::i32x4_arg a_, EmuSIMD::i32x4_arg b_, EmuSIMD::i32x4_arg c_)
	{
		return _mm_sub_epi32(mul_all_i32x4(a_, b_), c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 fnmadd_i32x4(EmuSIMD::i32x4_arg a_, EmuSIMD::i32x4_arg b_, EmuSIMD::i32x4_arg c_)
	{
		return _mm_add_epi32(mul_all_i32x4(negate_i32x4(a_), b_), c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 fnmsub_i32x4(EmuSIMD::i32x4_arg a_, EmuSIMD::i32x4_arg b_, EmuSIMD::i32x4_arg c_)
	{
		return _mm_sub_epi32(mul_all_i32x4(negate_i32x4(a_), b_), c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 fmaddsub_i32x4(EmuSIMD::i32x4_arg a_, EmuSIMD::i32x4_arg b_, EmuSIMD::i32x4_arg c_)
	{
		return addsub_i32x4(mul_all_i32x4(a_, b_), c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 fmsubadd_i32x4(EmuSIMD::i32x4_arg a_, EmuSIMD::i32x4_arg b_, EmuSIMD::i32x4_arg c_)
	{
		return subadd_i32x4(mul_all_i32x4(a_, b_), c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 floor_i32x4(EmuSIMD::i32x4_arg to_floor_)
	{
		return to_floor_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 ceil_i32x4(EmuSIMD::i32x4_arg to_ceil_)
	{
		return to_ceil_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 trunc_i32x4(EmuSIMD::i32x4_arg to_trunc_)
	{
		return to_trunc_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 mod_i32x4(EmuSIMD::i32x4_arg lhs_, EmuSIMD::i32x4_arg rhs_)
	{
#if EMU_CORE_X86_X64_SVML
		return _mm_rem_epi32(lhs_, rhs_);
#else
		EmuSIMD::i32x4 to_subtract = div_i32x4(lhs_, rhs_);
		to_subtract = mul_all_i32x4(to_subtract, rhs_);
		return sub_i32x4(lhs_, to_subtract);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 abs_i32x4(EmuSIMD::i32x4_arg in_)
	{
		return _mm_abs_epi32(in_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 sqrt_i32x4(EmuSIMD::i32x4_arg in_)
	{
		return emulate_fp_i32x4([](EmuSIMD::f32x4_arg in_fp_) { return sqrt_f32x4(in_fp_); }, in_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 rsqrt_i32x4(EmuSIMD::i32x4_arg in_)
	{
		return emulate_fp_i32x4([](EmuSIMD::f32x4_arg in_fp_) { return rsqrt_f32x4(in_fp_); }, in_);
	}
#pragma endregion

#pragma region NEAR_COMPARISONS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cmpnear_i32x4(EmuSIMD::i32x4_arg lhs_, EmuSIMD::i32x4_arg rhs_)
	{
		return cmpeq_i32x4(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cmpnear_i32x4(EmuSIMD::i32x4_arg lhs_, EmuSIMD::i32x4_arg rhs_, EmuSIMD::i32x4_arg epsilon)
	{
		return cmple_i32x4(abs_i32x4(sub_i32x4(lhs_, rhs_)), epsilon);
	}
#pragma endregion

#pragma region TRIG
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 cos_i32x4(EmuSIMD::i32x4_arg in_)
	{
		return emulate_fp_i32x4([](EmuSIMD::f32x4_arg in_fp_) { return cos_f32x4(in_fp_); }, in_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 sin_i32x4(EmuSIMD::i32x4_arg in_)
	{
		return emulate_fp_i32x4([](EmuSIMD::f32x4_arg in_fp_) { return sin_f32x4(in_fp_); }, in_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 tan_i32x4(EmuSIMD::i32x4_arg in_)
	{
		return emulate_fp_i32x4([](EmuSIMD::f32x4_arg in_fp_) { return tan_f32x4(in_fp_); }, in_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 acos_i32x4(EmuSIMD::i32x4_arg in_)
	{
		return emulate_fp_i32x4([](EmuSIMD::f32x4_arg in_fp_) { return acos_f32x4(in_fp_); }, in_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 asin_i32x4(EmuSIMD::i32x4_arg in_)
	{
		return emulate_fp_i32x4([](EmuSIMD::f32x4_arg in_fp_) { return asin_f32x4(in_fp_); }, in_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i32x4 atan_i32x4(EmuSIMD::i32x4_arg in_)
	{
		return emulate_fp_i32x4([](EmuSIMD::f32x4_arg in_fp_) { return atan_f32x4(in_fp_); }, in_);
	}
#pragma endregion
}

#endif
