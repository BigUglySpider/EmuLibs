#ifndef EMU_SIMD_GENERIC_FUNCS_I64X4_H_INC_
#define EMU_SIMD_GENERIC_FUNCS_I64X4_H_INC_ 1

#include "_generic_declarations/_all_generic_declarations.h"
#include "_common_generic_func_helpers.h"

namespace EmuSIMD::Funcs
{
#pragma region SETTERS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 set_i64x4(std::int64_t e0, std::int64_t e1, std::int64_t e2, std::int64_t e3)
	{
		return _mm256_set_epi64x(e3, e2, e1, e0);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 setr_i64x4(std::int64_t e0, std::int64_t e1, std::int64_t e2, std::int64_t e3)
	{
		return _mm256_set_epi64x(e3, e2, e1, e0);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 set1_i64x4(std::int64_t all_)
	{
		return _mm256_set1_epi64x(all_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 load_i64x4(const std::int64_t* p_to_load_)
	{
		return _mm256_loadu_si256(reinterpret_cast<const __m256i*>(p_to_load_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 aligned_load_i64x4(const std::int64_t* p_to_load_)
	{
		return _mm256_load_si256(reinterpret_cast<const __m256i*>(p_to_load_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 setzero_i64x4()
	{
		return _mm256_setzero_si256();
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 setmasked_i64x4(std::uint8_t bit_mask_)
	{
		constexpr std::int64_t element_mask = static_cast<std::int64_t>(0xFFFFFFFFFFFFFFFF);
		return _mm256_set_epi64x
		(
			(bit_mask_  & 0x01)       * element_mask,
			((bit_mask_ & 0x02) >> 1) * element_mask,
			((bit_mask_ & 0x04) >> 2) * element_mask,
			((bit_mask_ & 0x08) >> 3) * element_mask
		);
	}

	template<std::uint8_t BitMask_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 setmasked_i64x4()
	{
		if constexpr(BitMask_ != 0)
		{
			return set_i64x4
			(
				std::integral_constant<std::int64_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<0,  std::int64_t>(BitMask_)>::value,
				std::integral_constant<std::int64_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<1,  std::int64_t>(BitMask_)>::value,
				std::integral_constant<std::int64_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<2,  std::int64_t>(BitMask_)>::value,
				std::integral_constant<std::int64_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<3,  std::int64_t>(BitMask_)>::value
			);
		}
		else
		{
			return setzero_i64x4();
		}
	}

	template<bool I0_, bool I1_, bool I2_, bool I3_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 set_index_mask_i64x4()
	{
		if constexpr(I0_ || I1_ || I2_ || I3_)
		{
			return setmasked_i64x4<EmuSIMD::Funcs::make_index_set_mask<I0_, I1_, I2_, I3_>()>();
		}
		else
		{
			return setzero_i64x4();
		}
	}

	template<bool Active_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 set_index_mask_i64x4()
	{
		if constexpr (Active_)
		{
			return setmasked_i64x4<EmuSIMD::Funcs::make_all_indices_set_mask<4, Active_>()>();
		}
		else
		{
			return setzero_i64x4();
		}
	}
#pragma endregion

#pragma region STORES
	EMU_SIMD_COMMON_FUNC_SPEC void store_i64x4(std::int64_t* p_out_, i64x4_arg a_)
	{
		_mm256_storeu_si256(reinterpret_cast<__m256i*>(p_out_), a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC void aligned_store_i64x4(std::int64_t* p_out_, i64x4_arg a_)
	{
		_mm256_store_si256(reinterpret_cast<__m256i*>(p_out_), a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC std::int64_t get_first_i64x4(i64x4_arg a_)
	{
		return get_first_i64x2(cast_i64x4_i64x2(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC std::uint8_t movemask_i64x4(i64x4_arg a_)
	{
		return movemask_f64x4(cast_i64x4_f64x4(a_));
	}
#pragma endregion

#pragma region CASTS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 cast_f32x4_i64x4(f32x4_arg a_)
	{
		return _mm256_castsi128_si256(_mm_castps_si128(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 cast_f32x8_i64x4(f32x8_arg a_)
	{
		return _mm256_castps_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 cast_f32x16_i64x4(f32x16_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_castsi512_si256(_mm512_castps_si512(a_));
#else
		return EmuSIMD::_underlying_impl::emulate_simd_cast_lesser_width<i64x4>(a_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 cast_f64x2_i64x4(f64x2_arg a_)
	{
		return _mm256_castsi128_si256(_mm_castpd_si128(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 cast_f64x4_i64x4(f64x4_arg a_)
	{
		return _mm256_castpd_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 cast_f64x8_i64x4(f64x8_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_castsi512_si256(_mm512_castpd_si512(a_));
#else
		return EmuSIMD::_underlying_impl::emulate_simd_cast_lesser_width<i64x4>(a_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 cast_i8x16_i64x4(i8x16_arg a_)
	{
		return _mm256_castsi128_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 cast_i16x8_i64x4(i16x8_arg a_)
	{
		return _mm256_castsi128_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 cast_i32x4_i64x4(i32x4_arg a_)
	{
		return _mm256_castsi128_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 cast_i64x2_i64x4(i64x2_arg a_)
	{
		return _mm256_castsi128_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 cast_i8x32_i64x4(i8x32_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 cast_i16x16_i64x4(i16x16_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 cast_i32x8_i64x4(i32x8_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 cast_i64x4_i64x4(i64x4_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 cast_i8x64_i64x4(i8x64_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_castsi512_si256(a_);
#else
		return EmuSIMD::_underlying_impl::emulate_simd_cast_lesser_width<i64x4>(a_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 cast_i16x32_i64x4(i16x32_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_castsi512_si256(a_);
#else
		return EmuSIMD::_underlying_impl::emulate_simd_cast_lesser_width<i64x4>(a_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 cast_i32x16_i64x4(i32x16_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_castsi512_si256(a_);
#else
		return EmuSIMD::_underlying_impl::emulate_simd_cast_lesser_width<i64x4>(a_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 cast_i64x8_i64x4(i64x8_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_castsi512_si256(a_);
#else
		return EmuSIMD::_underlying_impl::emulate_simd_cast_lesser_width<i64x4>(a_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 cast_u8x16_i64x4(u8x16_arg a_)
	{
		return _mm256_castsi128_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 cast_u16x8_i64x4(u16x8_arg a_)
	{
		return _mm256_castsi128_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 cast_u32x4_i64x4(u32x4_arg a_)
	{
		return _mm256_castsi128_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 cast_u64x2_i64x4(u64x2_arg a_)
	{
		return _mm256_castsi128_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 cast_u8x32_i64x4(u8x32_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 cast_u16x16_i64x4(u16x16_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 cast_u32x8_i64x4(u32x8_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 cast_u64x4_i64x4(u64x4_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 cast_u8x64_i64x4(u8x64_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_castsi512_si256(a_);
#else
		return EmuSIMD::_underlying_impl::emulate_simd_cast_lesser_width<i64x4>(a_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 cast_u16x32_i64x4(u16x32_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_castsi512_si256(a_);
#else
		return EmuSIMD::_underlying_impl::emulate_simd_cast_lesser_width<i64x4>(a_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 cast_u32x16_i64x4(u32x16_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_castsi512_si256(a_);
#else
		return EmuSIMD::_underlying_impl::emulate_simd_cast_lesser_width<i64x4>(a_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 cast_u64x8_i64x4(u64x8_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_castsi512_si256(a_);
#else
		return EmuSIMD::_underlying_impl::emulate_simd_cast_lesser_width<i64x4>(a_);
#endif
	}
#pragma endregion

#pragma region CONVERSIONS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 cvt_f32x4_i64x4(f32x4_arg a_)
	{
		return _mm256_cvtps_epi64(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 cvt_f32x8_i64x4(f32x8_arg a_)
	{
		return _mm256_cvtps_epi64(_mm256_castps256_ps128(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 cvt_f32x16_i64x4(f32x16_arg a_)
	{
		return cvt_f32x4_i64x4(cast_f32x16_f32x4(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 cvt_f64x2_i64x4(f64x2_arg a_)
	{
		return _mm256_castsi128_si256(_mm_cvtpd_epi64(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 cvt_f64x4_i64x4(f64x4_arg a_)
	{
		return _mm256_cvtpd_epi64(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 cvt_f64x8_i64x4(f64x8_arg a_)
	{
		return cvt_f64x4_i64x4(cast_f64x8_f64x4(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 cvt_i8x16_i64x4(i8x16_arg a_)
	{
		return _mm256_cvtepi8_epi64(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 cvt_i16x8_i64x4(i16x8_arg a_)
	{
		return _mm256_cvtepi16_epi64(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 cvt_i32x4_i64x4(i32x4_arg a_)
	{
		return _mm256_cvtepi32_epi64(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 cvt_i64x2_i64x4(i64x2_arg a_)
	{
		return _mm256_castsi128_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 cvt_i8x32_i64x4(i8x32_arg a_)
	{
		return _mm256_cvtepi8_epi64(_mm256_castsi256_si128(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 cvt_i16x16_i64x4(i16x16_arg a_)
	{
		return _mm256_cvtepi16_epi64(_mm256_castsi256_si128(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 cvt_i32x8_i64x4(i32x8_arg a_)
	{
		return _mm256_cvtepi32_epi64(_mm256_castsi256_si128(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 cvt_i64x4_i64x4(i64x4_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 cvt_i8x64_i64x4(i8x64_arg a_)
	{
		return cvt_i8x16_i64x4(cast_i8x64_i8x16(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 cvt_i16x32_i64x4(i16x32_arg a_)
	{
		return cvt_i16x8_i64x4(cast_i16x32_i16x8(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 cvt_i32x16_i64x4(i32x16_arg a_)
	{
		return cvt_i32x4_i64x4(cast_i32x16_i32x4(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 cvt_i64x8_i64x4(i64x8_arg a_)
	{
		return cast_i64x8_i64x4(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 cvt_u8x16_i64x4(u8x16_arg a_)
	{
		return _mm256_cvtepu8_epi64(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 cvt_u16x8_i64x4(u16x8_arg a_)
	{
		return _mm256_cvtepu16_epi64(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 cvt_u32x4_i64x4(u32x4_arg a_)
	{
		return _mm256_cvtepu32_epi64(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 cvt_u64x2_i64x4(u64x2_arg a_)
	{
		return _mm256_castsi128_si256(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 cvt_u8x32_i64x4(u8x32_arg a_)
	{
		return _mm256_cvtepu8_epi64(_mm256_castsi256_si128(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 cvt_u16x16_i64x4(u16x16_arg a_)
	{
		return _mm256_cvtepu16_epi64(_mm256_castsi256_si128(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 cvt_u32x8_i64x4(u32x8_arg a_)
	{
		return _mm256_cvtepu32_epi64(_mm256_castsi256_si128(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 cvt_u64x4_i64x4(u64x4_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 cvt_u8x64_i64x4(u8x64_arg a_)
	{
		return cvt_u8x16_i64x4(cast_u8x64_u8x16(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 cvt_u16x32_i64x4(u16x32_arg a_)
	{
		return cvt_u16x8_i64x4(cast_u16x32_u16x8(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 cvt_u32x16_i64x4(u32x16_arg a_)
	{
		return cvt_u32x4_i64x4(cast_u32x16_u32x4(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 cvt_u64x8_i64x4(u64x8_arg a_)
	{
		return cast_u64x8_i64x4(a_);
	}
#pragma endregion

#pragma region COMPARISONS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 cmpeq_i64x4(EmuSIMD::i64x4_arg lhs_, EmuSIMD::i64x4_arg rhs_)
	{
		return _mm256_cmpeq_epi64(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 cmpneq_i64x4(EmuSIMD::i64x4_arg lhs_, EmuSIMD::i64x4_arg rhs_)
	{
		constexpr std::int64_t mask = static_cast<std::int64_t>(0xFFFFFFFFFFFFFFFF);
		return _mm256_xor_si256(set1_i64x4(mask), _mm256_cmpeq_epi64(lhs_, rhs_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 cmpgt_i64x4(EmuSIMD::i64x4_arg lhs_, EmuSIMD::i64x4_arg rhs_)
	{
		return _mm256_cmpgt_epi64(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 cmplt_i64x4(EmuSIMD::i64x4_arg lhs_, EmuSIMD::i64x4_arg rhs_)
	{
		return _mm256_cmpgt_epi64(rhs_, lhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 cmpge_i64x4(EmuSIMD::i64x4_arg lhs_, EmuSIMD::i64x4_arg rhs_)
	{
		return _mm256_or_si256(_mm256_cmpgt_epi64(lhs_, rhs_), _mm256_cmpeq_epi64(lhs_, rhs_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 cmple_i64x4(EmuSIMD::i64x4_arg lhs_, EmuSIMD::i64x4_arg rhs_)
	{
		return _mm256_or_si256(_mm256_cmpgt_epi64(rhs_, lhs_), _mm256_cmpeq_epi64(lhs_, rhs_));
	}
#pragma endregion

#pragma region MOVES
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 movehl_i64x4(EmuSIMD::i64x4_arg lhs_, EmuSIMD::i64x4_arg rhs_)
	{
		return cast_f64x4_i64x4(movehl_f64x4(cast_i64x4_f64x4(lhs_), cast_i64x4_f64x4(rhs_)));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 movelh_i64x4(EmuSIMD::i64x4_arg lhs_, EmuSIMD::i64x4_arg rhs_)
	{
		return cast_f64x4_i64x4(movelh_f64x4(cast_i64x4_f64x4(lhs_), cast_i64x4_f64x4(rhs_)));
	}
#pragma endregion

#pragma region BITWISE_ARITHMETIC
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 and_i64x4(EmuSIMD::i64x4_arg lhs_, EmuSIMD::i64x4_arg rhs_)
	{
#if EMU_SIMD_USE_256_REGISTERS
		return _mm256_and_si256(lhs_, rhs_);
#else
		using EmuSIMD::_underlying_impl::emulate_simd_basic;
		return emulate_simd_basic([](i64x2_arg a_, i64x2_arg b_) { return EmuSIMD::Funcs::and_i64x2(a_, b_); }, lhs_, rhs_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 or_i64x4(EmuSIMD::i64x4_arg lhs_, EmuSIMD::i64x4_arg rhs_)
	{
#if EMU_SIMD_USE_256_REGISTERS
		return _mm256_or_si256(lhs_, rhs_);
#else
		using EmuSIMD::_underlying_impl::emulate_simd_basic;
		return emulate_simd_basic([](i64x2_arg a_, i64x2_arg b_) { return EmuSIMD::Funcs::or_i64x2(a_, b_); }, lhs_, rhs_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 xor_i64x4(EmuSIMD::i64x4_arg lhs_, EmuSIMD::i64x4_arg rhs_)
	{
#if EMU_SIMD_USE_256_REGISTERS
		return _mm256_xor_si256(lhs_, rhs_);
#else
		using EmuSIMD::_underlying_impl::emulate_simd_basic;
		return emulate_simd_basic([](i64x2_arg a_, i64x2_arg b_) { return EmuSIMD::Funcs::xor_i64x2(a_, b_); }, lhs_, rhs_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 andnot_i64x4(EmuSIMD::i64x4_arg not_lhs_, EmuSIMD::i64x4_arg rhs_)
	{
#if EMU_SIMD_USE_256_REGISTERS
		return _mm256_andnot_si256(not_lhs_, rhs_);
#else
		using EmuSIMD::_underlying_impl::emulate_simd_basic;
		return emulate_simd_basic([](i64x2_arg a_, i64x2_arg b_) { return EmuSIMD::Funcs::andnot_i64x2(a_, b_); }, not_lhs_, rhs_);
#endif
	}

	template<std::int32_t NumShifts_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 shift_left_i64x4(EmuSIMD::i64x4_arg lhs_)
	{
		if constexpr (NumShifts_ >= 64)
		{
			return setzero_i64x4();
		}
		else
		{
#if EMU_SIMD_USE_256_REGISTERS
			return _mm256_slli_epi64(lhs_, NumShifts_);
#else
			using EmuSIMD::_underlying_impl::emulate_simd_basic;
			return emulate_simd_basic([](i64x2_arg a_) { return shift_left_i64x2<NumShifts_>(a_); }, lhs_);
#endif
		}
	}

	template<std::int32_t NumShifts_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 shift_right_arithmetic_i64x4(EmuSIMD::i64x4_arg lhs_)
	{
		if constexpr (NumShifts_ >= 64)
		{
			return setzero_i64x4();
		}
		else
		{
#if EMU_SIMD_USE_256_REGISTERS
	#if EMU_SIMD_USE_512_REGISTERS // 64-bit srai only available with AVX-512
			return _mm256_srai_epi64(lhs_, NumShifts_);
	#else
			constexpr std::int64_t sign_bit = std::int64_t(0b1000000000000000000000000000000000000000000000000000000000000000);
			i64x4 signs_mask = set1_i64x4(sign_bit);
			signs_mask = and_i64x4(signs_mask, lhs_);
			return or_i64x4(signs_mask, shift_right_logical_i64x4<NumShifts_>(lhs_));
	#endif
#else
			using EmuSIMD::_underlying_impl::emulate_simd_basic;
			return emulate_simd_basic([](i64x2_arg a_) { return shift_right_arithmetic_i64x2<NumShifts_>(a_); }, lhs_);
#endif
		}
	}

	template<std::int32_t NumShifts_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 shift_right_logical_i64x4(EmuSIMD::i64x4_arg lhs_)
	{
		if constexpr (NumShifts_ >= 64)
		{
			return setzero_i64x4();
		}
		else
		{
#if EMU_SIMD_USE_256_REGISTERS
			return _mm256_srli_epi64(lhs_, NumShifts_);
#else
			using EmuSIMD::_underlying_impl::emulate_simd_basic;
			return emulate_simd_basic([](i64x2_arg a_) { return shift_right_logical_i64x2<NumShifts_>(a_); }, lhs_);
#endif
		}
	}
#pragma endregion
	
#pragma region BLENDS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 blendv_i64x4(EmuSIMD::i64x4_arg a_, EmuSIMD::i64x4_arg b_, EmuSIMD::i64x4_arg shuffle_mask_vec_)
	{
		return cast_f64x4_i64x4
		(
			blendv_f64x4
			(
				cast_i64x4_f64x4(a_),
				cast_i64x4_f64x4(b_),
				cast_i64x4_f64x4(shuffle_mask_vec_)
			)
		);
	}
#pragma endregion

#pragma region MINMAX_FUNCS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 min_i64x4(EmuSIMD::i64x4_arg a_, EmuSIMD::i64x4_arg b_)
	{
		return _mm256_min_epi64(a_, b_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 horizontal_min_i64x4(EmuSIMD::i64x4_arg a_)
	{
		i64x2 min_lane = min_i64x2(cast_i64x4_i64x2(a_), extract_i64x4_lane_i64x2<1>(a_));
		min_lane = horizontal_min_i64x2(min_lane);
		return _mm256_inserti128_si256(cast_i64x2_i64x4(min_lane), min_lane, 1);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 max_i64x4(EmuSIMD::i64x4_arg a_, EmuSIMD::i64x4_arg b_)
	{
		return _mm256_max_epi64(a_, b_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 horizontal_max_i64x4(EmuSIMD::i64x4_arg a_)
	{
		i64x2 max_lane = max_i64x2(cast_i64x4_i64x2(a_), extract_i64x4_lane_i64x2<1>(a_));
		max_lane = horizontal_max_i64x2(max_lane);
		return _mm256_inserti128_si256(cast_i64x2_i64x4(max_lane), max_lane, 1);
	}
#pragma endregion

#pragma region BASIC_ARITHMETIC
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 mul_all_i64x4(EmuSIMD::i64x4_arg lhs_, EmuSIMD::i64x4_arg rhs_)
	{
		return _mm256_mullo_epi64(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 negate_i64x4(EmuSIMD::i64x4_arg to_negate_)
	{
		return _mm256_sub_epi64(_mm256_setzero_si256(), to_negate_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 add_i64x4(EmuSIMD::i64x4_arg lhs_, EmuSIMD::i64x4_arg rhs_)
	{
		return _mm256_add_epi64(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 sub_i64x4(EmuSIMD::i64x4_arg lhs_, EmuSIMD::i64x4_arg rhs_)
	{
		return _mm256_sub_epi64(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 div_i64x4(EmuSIMD::i64x4_arg lhs_, EmuSIMD::i64x4_arg rhs_)
	{
#if EMU_CORE_X86_X64_SVML
		return _mm256_div_epi64(lhs_, rhs_);
#else
		EmuSIMD::f64x4 result_f64 = cvt_i64x4_f64x4(lhs_);
		result_f64 = div_f64x4(result_f64, cvt_i64x4_f64x4(rhs_));
		return cvt_f64x4_i64x4(trunc_f64x4(result_f64));
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 addsub_i64x4(EmuSIMD::i64x4_arg lhs_, EmuSIMD::i64x4_arg rhs_)
	{
		constexpr std::int64_t bytes_mask = static_cast<std::int64_t>(0xFFFFFFFFFFFFFFFF);
		const EmuSIMD::i64x4 mask = _mm256_set_epi64x(bytes_mask, 0, bytes_mask, 0);
		EmuSIMD::i64x4 out = _mm256_add_epi64(lhs_, _mm256_and_si256(mask, rhs_));
		return _mm256_sub_epi64(lhs_, _mm256_andnot_si256(mask, rhs_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 subadd_i64x4(EmuSIMD::i64x4_arg lhs_, EmuSIMD::i64x4_arg rhs_)
	{
		constexpr std::int64_t bytes_mask = static_cast<std::int64_t>(0xFFFFFFFFFFFFFFFF);
		const EmuSIMD::i64x4 mask = _mm256_set_epi64x(bytes_mask, 0, bytes_mask, 0);
		EmuSIMD::i64x4 out = _mm256_sub_epi64(lhs_, _mm256_and_si256(mask, rhs_));
		return _mm256_add_epi64(lhs_, _mm256_andnot_si256(mask, rhs_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 fmadd_i64x4(EmuSIMD::i64x4_arg a_, EmuSIMD::i64x4_arg b_, EmuSIMD::i64x4_arg c_)
	{
		return _mm256_add_epi64(mul_all_i64x4(a_, b_), c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 fmsub_i64x4(EmuSIMD::i64x4_arg a_, EmuSIMD::i64x4_arg b_, EmuSIMD::i64x4_arg c_)
	{
		return _mm256_sub_epi64(mul_all_i64x4(a_, b_), c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 fnmadd_i64x4(EmuSIMD::i64x4_arg a_, EmuSIMD::i64x4_arg b_, EmuSIMD::i64x4_arg c_)
	{
		return _mm256_add_epi64(mul_all_i64x4(negate_i64x4(a_), b_), c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 fnmsub_i64x4(EmuSIMD::i64x4_arg a_, EmuSIMD::i64x4_arg b_, EmuSIMD::i64x4_arg c_)
	{
		return _mm256_sub_epi64(mul_all_i64x4(negate_i64x4(a_), b_), c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 fmaddsub_i64x4(EmuSIMD::i64x4_arg a_, EmuSIMD::i64x4_arg b_, EmuSIMD::i64x4_arg c_)
	{
		return addsub_i64x4(mul_all_i64x4(a_, b_), c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 fmsubadd_i64x4(EmuSIMD::i64x4_arg a_, EmuSIMD::i64x4_arg b_, EmuSIMD::i64x4_arg c_)
	{
		return subadd_i64x4(mul_all_i64x4(a_, b_), c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 floor_i64x4(EmuSIMD::i64x4_arg to_floor_)
	{
		return to_floor_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 ceil_i64x4(EmuSIMD::i64x4_arg to_ceil_)
	{
		return to_ceil_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 trunc_i64x4(EmuSIMD::i64x4_arg to_trunc_)
	{
		return to_trunc_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 mod_i64x4(EmuSIMD::i64x4_arg lhs_, EmuSIMD::i64x4_arg rhs_)
	{
#if EMU_CORE_X86_X64_SVML
		return _mm256_rem_epi64(lhs_, rhs_);
#else
		EmuSIMD::i64x4 to_subtract = div_i64x4(lhs_, rhs_);
		to_subtract = mul_all_i64x4(to_subtract, rhs_);
		return sub_i64x4(lhs_, to_subtract);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 abs_i64x4(EmuSIMD::i64x4_arg in_)
	{
		return _mm256_abs_epi64(in_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 sqrt_i64x4(EmuSIMD::i64x4_arg in_)
	{
		return emulate_fp_i64x4([](EmuSIMD::f64x4_arg in_fp_) { return sqrt_f64x4(in_fp_); }, in_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 rsqrt_i64x4(EmuSIMD::i64x4_arg in_)
	{
		return emulate_fp_i64x4([](EmuSIMD::f64x4_arg in_fp_) { return rsqrt_f64x4(in_fp_); }, in_);
	}
#pragma endregion

#pragma region NEAR_COMPARISONS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 cmpnear_i64x4(EmuSIMD::i64x4_arg lhs_, EmuSIMD::i64x4_arg rhs_)
	{
		return cmpeq_i64x4(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 cmpnear_i64x4(EmuSIMD::i64x4_arg lhs_, EmuSIMD::i64x4_arg rhs_, EmuSIMD::i64x4_arg epsilon)
	{
		return cmple_i64x4(abs_i64x4(sub_i64x4(lhs_, rhs_)), epsilon);
	}
#pragma endregion

#pragma region TRIG
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 cos_i64x4(EmuSIMD::i64x4_arg in_)
	{
		return emulate_fp_i64x4([](EmuSIMD::f64x4_arg in_fp_) { return cos_f64x4(in_fp_); }, in_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 sin_i64x4(EmuSIMD::i64x4_arg in_)
	{
		return emulate_fp_i64x4([](EmuSIMD::f64x4_arg in_fp_) { return sin_f64x4(in_fp_); }, in_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 tan_i64x4(EmuSIMD::i64x4_arg in_)
	{
		return emulate_fp_i64x4([](EmuSIMD::f64x4_arg in_fp_) { return tan_f64x4(in_fp_); }, in_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 acos_i64x4(EmuSIMD::i64x4_arg in_)
	{
		return emulate_fp_i64x4([](EmuSIMD::f64x4_arg in_fp_) { return acos_f64x4(in_fp_); }, in_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 asin_i64x4(EmuSIMD::i64x4_arg in_)
	{
		return emulate_fp_i64x4([](EmuSIMD::f64x4_arg in_fp_) { return asin_f64x4(in_fp_); }, in_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x4 atan_i64x4(EmuSIMD::i64x4_arg in_)
	{
		return emulate_fp_i64x4([](EmuSIMD::f64x4_arg in_fp_) { return atan_f64x4(in_fp_); }, in_);
	}
#pragma endregion
}

#endif
