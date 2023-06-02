#ifndef EMU_SIMD_GENERIC_FUNCS_I64X2_H_INC_
#define EMU_SIMD_GENERIC_FUNCS_I64X2_H_INC_ 1

#include "_generic_declarations/_all_generic_declarations.h"
#include "_common_generic_func_helpers.h"

namespace EmuSIMD::Funcs
{
#pragma region SETTERS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 set_i64x2(std::int64_t e0, std::int64_t e1)
	{
		return _mm_set_epi64x(e0, e1);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 setr_i64x2(std::int64_t e0, std::int64_t e1)
	{
		return _mm_set_epi64x(e1, e0);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 set1_i64x2(std::int64_t all_)
	{
		return _mm_set1_epi64x(all_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 load_i64x2(const std::int64_t* p_to_load_)
	{
		return _mm_loadu_si128(reinterpret_cast<const __m128i*>(p_to_load_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 aligned_load_i64x2(const std::int64_t* p_to_load_)
	{
		return _mm_load_si128(reinterpret_cast<const __m128i*>(p_to_load_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 setzero_i64x2()
	{
		return _mm_setzero_si128();
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 setmasked_i64x2(std::uint8_t bit_mask_)
	{
		constexpr std::int64_t element_mask = static_cast<std::int64_t>(0xFFFFFFFFFFFFFFFF);
		return _mm_set_epi64x
		(
			(bit_mask_  & 0x01)       * element_mask,
			((bit_mask_ & 0x02) >> 1) * element_mask
		);
	}

	template<std::uint8_t BitMask_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 setmasked_i64x2()
	{
		if constexpr(BitMask_ != 0)
		{
			return set_i64x2
			(
				std::integral_constant<std::int64_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<0, std::int64_t>(BitMask_)>::value,
				std::integral_constant<std::int64_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<1, std::int64_t>(BitMask_)>::value
			);
		}
		else
		{
			return setzero_i64x2();
		}
	}

	template<bool I0_, bool I1_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 set_index_mask_i64x2()
	{
		if constexpr(I0_ || I1_)
		{
			return setmasked_i64x2<EmuSIMD::Funcs::make_index_set_mask<I0_, I1_>()>();
		}
		else
		{
			return setzero_i64x2();
		}
	}

	template<bool Active_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 set_index_mask_i64x2()
	{
		if constexpr (Active_)
		{
			return setmasked_i64x2<EmuSIMD::Funcs::make_all_indices_set_mask<2, Active_>()>();
		}
		else
		{
			return setzero_i64x2();
		}
	}
#pragma endregion

#pragma region STORES
	EMU_SIMD_COMMON_FUNC_SPEC void store_i64x2(std::int64_t* p_out_, i64x2_arg a_)
	{
		_mm_storeu_si128(reinterpret_cast<__m128i*>(p_out_), a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC void aligned_store_i64x2(std::int64_t* p_out_, i64x2_arg a_)
	{
		_mm_store_si128(reinterpret_cast<__m128i*>(p_out_), a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC std::int64_t get_first_i64x2(i64x2_arg a_)
	{
		return _mm_cvtsi128_si64(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC std::uint8_t movemask_i64x2(i64x2_arg a_)
	{
		return movemask_f64x2(cast_i64x2_f64x2(a_));
	}
#pragma endregion

#pragma region CASTS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 cast_f32x4_i64x2(f32x4_arg a_)
	{
		return _mm_castps_si128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 cast_f32x8_i64x2(f32x8_arg a_)
	{
		return _mm256_castsi256_si128(_mm256_castps_si256(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 cast_f32x16_i64x2(f32x16_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_castsi512_si128(_mm512_castps_si512(a_));
#else
		return EmuSIMD::_underlying_impl::emulate_simd_cast_lesser_width<i64x2>(a_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 cast_f64x2_i64x2(f64x2_arg a_)
	{
		return _mm_castpd_si128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 cast_f64x4_i64x2(f64x4_arg a_)
	{
		return _mm256_castsi256_si128(_mm256_castpd_si256(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 cast_f64x8_i64x2(f64x8_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_castsi512_si128(_mm512_castpd_si512(a_));
#else
		return EmuSIMD::_underlying_impl::emulate_simd_cast_lesser_width<i64x2>(a_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 cast_i8x16_i64x2(i8x16_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 cast_i16x8_i64x2(i16x8_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 cast_i32x4_i64x2(i32x4_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 cast_i64x2_i64x2(i64x2_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 cast_i8x32_i64x2(i8x32_arg a_)
	{
		return _mm256_castsi256_si128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 cast_i16x16_i64x2(i16x16_arg a_)
	{
		return _mm256_castsi256_si128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 cast_i32x8_i64x2(i32x8_arg a_)
	{
		return _mm256_castsi256_si128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 cast_i64x4_i64x2(i64x4_arg a_)
	{
		return _mm256_castsi256_si128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 cast_i8x64_i64x2(i8x64_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_castsi512_si128(a_);
#else
		return EmuSIMD::_underlying_impl::emulate_simd_cast_lesser_width<i64x2>(a_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 cast_i16x32_i64x2(i16x32_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_castsi512_si128(a_);
#else
		return EmuSIMD::_underlying_impl::emulate_simd_cast_lesser_width<i64x2>(a_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 cast_i32x16_i64x2(i32x16_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_castsi512_si128(a_);
#else
		return EmuSIMD::_underlying_impl::emulate_simd_cast_lesser_width<i64x2>(a_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 cast_i64x8_i64x2(i64x8_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_castsi512_si128(a_);
#else
		return EmuSIMD::_underlying_impl::emulate_simd_cast_lesser_width<i64x2>(a_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 cast_u8x16_i64x2(u8x16_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 cast_u16x8_i64x2(u16x8_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 cast_u32x4_i64x2(u32x4_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 cast_u64x2_i64x2(u64x2_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 cast_u8x32_i64x2(u8x32_arg a_)
	{
		return _mm256_castsi256_si128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 cast_u16x16_i64x2(u16x16_arg a_)
	{
		return _mm256_castsi256_si128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 cast_u32x8_i64x2(u32x8_arg a_)
	{
		return _mm256_castsi256_si128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 cast_u64x4_i64x2(u64x4_arg a_)
	{
		return _mm256_castsi256_si128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 cast_u8x64_i64x2(u8x64_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_castsi512_si128(a_);
#else
		return EmuSIMD::_underlying_impl::emulate_simd_cast_lesser_width<i64x2>(a_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 cast_u16x32_i64x2(u16x32_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_castsi512_si128(a_);
#else
		return EmuSIMD::_underlying_impl::emulate_simd_cast_lesser_width<i64x2>(a_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 cast_u32x16_i64x2(u32x16_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_castsi512_si128(a_);
#else
		return EmuSIMD::_underlying_impl::emulate_simd_cast_lesser_width<i64x2>(a_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 cast_u64x8_i64x2(u64x8_arg a_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_castsi512_si128(a_);
#else
		return EmuSIMD::_underlying_impl::emulate_simd_cast_lesser_width<i64x2>(a_);
#endif
	}
#pragma endregion

#pragma region CONVERSIONS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 cvt_f32x4_i64x2(f32x4_arg a_)
	{
		return _mm_cvtps_epi64(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 cvt_f32x8_i64x2(f32x8_arg a_)
	{
		return _mm_cvtps_epi64(_mm256_castps256_ps128(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 cvt_f32x16_i64x2(f32x16_arg a_)
	{
		return cvt_f32x4_i64x2(cast_f32x16_f32x4(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 cvt_f64x2_i64x2(f64x2_arg a_)
	{
		return _mm_cvtpd_epi64(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 cvt_f64x4_i64x2(f64x4_arg a_)
	{
		return cvt_i32x4_i64x2(_mm_cvtpd_epi32(_mm256_castpd256_pd128(a_)));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 cvt_f64x8_i64x2(f64x8_arg a_)
	{
		return cvt_f64x2_i64x2(cast_f64x8_f64x2(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 cvt_i8x16_i64x2(i8x16_arg a_)
	{
		return _mm_cvtepi8_epi64(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 cvt_i16x8_i64x2(i16x8_arg a_)
	{
		return _mm_cvtepi16_epi64(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 cvt_i32x4_i64x2(i32x4_arg a_)
	{
		return _mm_cvtepi32_epi64(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 cvt_i64x2_i64x2(i64x2_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 cvt_i8x32_i64x2(i8x32_arg a_)
	{
		return _mm_cvtepi8_epi64(_mm256_castsi256_si128(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 cvt_i16x16_i64x2(i16x16_arg a_)
	{
		return _mm_cvtepi16_epi64(_mm256_castsi256_si128(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 cvt_i32x8_i64x2(i32x8_arg a_)
	{
		return _mm_cvtepi32_epi64(_mm256_castsi256_si128(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 cvt_i64x4_i64x2(i64x4_arg a_)
	{
		return _mm256_castsi256_si128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 cvt_i8x64_i64x2(i8x64_arg a_)
	{
		return cvt_i8x16_i64x2(cast_i8x64_i8x16(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 cvt_i16x32_i64x2(i16x32_arg a_)
	{
		return cvt_i16x8_i64x2(cast_i16x32_i16x8(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 cvt_i32x16_i64x2(i32x16_arg a_)
	{
		return cvt_i32x4_i64x2(cast_i32x16_i32x4(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 cvt_i64x8_i64x2(i64x8_arg a_)
	{
		return cast_i64x8_i64x2(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 cvt_u8x16_i64x2(i8x16_arg a_)
	{
		return _mm_cvtepu8_epi64(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 cvt_u16x8_i64x2(i16x8_arg a_)
	{
		return _mm_cvtepu16_epi64(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 cvt_u32x4_i64x2(i32x4_arg a_)
	{
		return _mm_cvtepu32_epi64(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 cvt_u64x2_i64x2(i64x2_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 cvt_u8x32_i64x2(i8x32_arg a_)
	{
		return _mm_cvtepu8_epi64(_mm256_castsi256_si128(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 cvt_u16x16_i64x2(i16x16_arg a_)
	{
		return _mm_cvtepu16_epi64(_mm256_castsi256_si128(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 cvt_u32x8_i64x2(i32x8_arg a_)
	{
		return _mm_cvtepu32_epi64(_mm256_castsi256_si128(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 cvt_u64x4_i64x2(i64x4_arg a_)
	{
		return _mm256_castsi256_si128(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 cvt_u8x64_i64x2(i8x64_arg a_)
	{
		return cvt_u8x16_i64x2(cast_u8x64_u8x16(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 cvt_u16x32_i64x2(i16x32_arg a_)
	{
		return cvt_u16x8_i64x2(cast_u16x32_u16x8(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 cvt_u32x16_i64x2(i32x16_arg a_)
	{
		return cvt_u32x4_i64x2(cast_u32x16_u32x4(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 cvt_u64x8_i64x2(i64x8_arg a_)
	{
		return cast_u64x8_i64x2(a_);
	}
#pragma endregion

#pragma region COMPARISONS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 cmpeq_i64x2(EmuSIMD::i64x2_arg lhs_, EmuSIMD::i64x2_arg rhs_)
	{
		return _mm_cmpeq_epi64(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 cmpneq_i64x2(EmuSIMD::i64x2_arg lhs_, EmuSIMD::i64x2_arg rhs_)
	{
		constexpr std::int64_t mask = static_cast<std::int64_t>(0xFFFFFFFFFFFFFFFF);
		return _mm_xor_si128(set1_i64x2(mask), _mm_cmpeq_epi64(lhs_, rhs_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 cmpgt_i64x2(EmuSIMD::i64x2_arg lhs_, EmuSIMD::i64x2_arg rhs_)
	{
		return _mm_cmpgt_epi64(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 cmplt_i64x2(EmuSIMD::i64x2_arg lhs_, EmuSIMD::i64x2_arg rhs_)
	{
		return _mm_cmpgt_epi64(rhs_, lhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 cmpge_i64x2(EmuSIMD::i64x2_arg lhs_, EmuSIMD::i64x2_arg rhs_)
	{
		return _mm_or_si128(_mm_cmpgt_epi64(lhs_, rhs_), _mm_cmpeq_epi64(lhs_, rhs_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 cmple_i64x2(EmuSIMD::i64x2_arg lhs_, EmuSIMD::i64x2_arg rhs_)
	{
		return _mm_or_si128(_mm_cmpgt_epi64(rhs_, lhs_), _mm_cmpeq_epi64(lhs_, rhs_));
	}
#pragma endregion

#pragma region MOVES
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 movehl_i64x2(EmuSIMD::i64x2_arg lhs_, EmuSIMD::i64x2_arg rhs_)
	{
		return cast_f64x2_i64x2(movehl_f64x2(cast_i64x2_f64x2(lhs_), cast_i64x2_f64x2(rhs_)));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 movelh_i64x2(EmuSIMD::i64x2_arg lhs_, EmuSIMD::i64x2_arg rhs_)
	{
		return cast_f64x2_i64x2(movelh_f64x2(cast_i64x2_f64x2(lhs_), cast_i64x2_f64x2(rhs_)));
	}
#pragma endregion

#pragma region BITWISE_ARITHMETIC
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 and_i64x2(EmuSIMD::i64x2_arg lhs_, EmuSIMD::i64x2_arg rhs_)
	{
#if EMU_SIMD_USE_128_REGISTERS
		return _mm_and_si128(lhs_, rhs_);
#else
		using EmuSIMD::_underlying_impl::emulate_simd_basic;
		using index_sequence = std::make_index_sequence<2>;
		return emulate_simd_basic(EmuCore::do_bitwise_and<std::int64_t>(), lhs_, rhs_, index_sequence());
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 or_i64x2(EmuSIMD::i64x2_arg lhs_, EmuSIMD::i64x2_arg rhs_)
	{
#if EMU_SIMD_USE_128_REGISTERS
		return _mm_or_si128(lhs_, rhs_);
#else
		using EmuSIMD::_underlying_impl::emulate_simd_basic;
		using index_sequence = std::make_index_sequence<2>;
		return emulate_simd_basic(EmuCore::do_bitwise_or<std::int64_t>(), lhs_, rhs_, index_sequence());
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 xor_i64x2(EmuSIMD::i64x2_arg lhs_, EmuSIMD::i64x2_arg rhs_)
	{
#if EMU_SIMD_USE_128_REGISTERS
		return _mm_xor_si128(lhs_, rhs_);
#else
		using EmuSIMD::_underlying_impl::emulate_simd_basic;
		using index_sequence = std::make_index_sequence<2>;
		return emulate_simd_basic(EmuCore::do_bitwise_xor<std::int64_t>(), lhs_, rhs_, index_sequence());
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 andnot_i64x2(EmuSIMD::i64x2_arg not_lhs_, EmuSIMD::i64x2_arg rhs_)
	{
#if EMU_SIMD_USE_128_REGISTERS
		return _mm_andnot_si128(not_lhs_, rhs_);
#else
		using EmuSIMD::_underlying_impl::emulate_simd_basic;
		using index_sequence = std::make_index_sequence<2>;
		return emulate_simd_basic(EmuCore::do_bitwise_andnot<std::int64_t>(), not_lhs_, rhs_, index_sequence());
#endif
	}

	template<std::int32_t NumShifts_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 shift_left_i64x2(EmuSIMD::i64x2_arg lhs_)
	{
		if constexpr (NumShifts_ >= 64)
		{
			return setzero_i64x2();
		}
		else
		{
#if EMU_SIMD_USE_128_REGISTERS
			return _mm_slli_epi64(lhs_, NumShifts_);
#else
			using EmuSIMD::_underlying_impl::emulate_simd_basic;
			using index_sequence = std::make_index_sequence<2>;
			auto func = [](const std::int64_t& a_) { return (a_ << NumShifts_); };
			return emulate_simd_basic(func, lhs_, index_sequence());
#endif
		}

	}

	template<std::int32_t NumShifts_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 shift_right_arithmetic_i64x2(EmuSIMD::i64x2_arg lhs_)
	{
		if constexpr (NumShifts_ >= 64)
		{
			return setzero_i32x4();
		}
		else
		{
#if EMU_SIMD_USE_128_REGISTERS
	#if EMU_SIMD_USE_512_REGISTERS // 64-bit srai only available with AVX-512
			return _mm_srai_epi64(lhs_, NumShifts_);
	#else
			constexpr std::int64_t sign_bit = std::int64_t(0b1000000000000000000000000000000000000000000000000000000000000000);
			i64x2 signs_mask = set1_i64x2(sign_bit);
			signs_mask = and_i64x2(signs_mask, lhs_);
			return or_i64x2(signs_mask, shift_right_logical_i64x2<NumShifts_>(lhs_));
	#endif
#else
			constexpr std::int64_t sign_bit = std::int64_t(0b1000000000000000000000000000000000000000000000000000000000000000);
			using EmuSIMD::_underlying_impl::emulate_simd_basic;
			using index_sequence = std::make_index_sequence<2>;
			auto func = [](const std::int64_t& a_) { return (a_ >> NumShifts_) | (sign_bit & a_); };
			return emulate_simd_basic(func, lhs_, index_sequence());
#endif
		}
	}

	template<std::int32_t NumShifts_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 shift_right_logical_i64x2(EmuSIMD::i64x2_arg lhs_)
	{
		if constexpr (NumShifts_ >= 64)
		{
			return setzero_i64x2();
		}
		else
		{
#if EMU_SIMD_USE_128_REGISTERS
			return _mm_srli_epi64(lhs_, NumShifts_);
#else
			using EmuSIMD::_underlying_impl::emulate_simd_basic;
			using index_sequence = std::make_index_sequence<2>;
			auto func = [](const std::int64_t& a_) { return (a_ >> NumShifts_); };
			return emulate_simd_basic(func, lhs_, index_sequence());
#endif
		}
	}
#pragma endregion

#pragma region BLENDS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 blendv_i64x2(EmuSIMD::i64x2_arg a_, EmuSIMD::i64x2_arg b_, EmuSIMD::i64x2_arg shuffle_mask_vec_)
	{
		return cast_f64x2_i64x2
		(
			blendv_f64x2
			(
				cast_i64x2_f64x2(a_),
				cast_i64x2_f64x2(b_),
				cast_i64x2_f64x2(shuffle_mask_vec_)
			)
		);
	}
#pragma endregion

#pragma region MINMAX_FUNCS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 min_i64x2(EmuSIMD::i64x2_arg a_, EmuSIMD::i64x2_arg b_)
	{
		return _mm_min_epi64(a_, b_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 horizontal_min_i64x2(EmuSIMD::i64x2_arg a_)
	{
		return min_i64x2(a_, permute_i64x2<make_shuffle_mask_64x2<0, 1>()>(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 horizontal_min_fill_i64x2(EmuSIMD::i64x2_arg a_)
	{
		return horizontal_min_i64x2(a_);
	}

	template<typename Out_>
	EMU_SIMD_COMMON_FUNC_SPEC auto horizontal_min_fill_i64x2(EmuSIMD::i64x2_arg a_)
		-> typename std::remove_cvref<Out_>::type
	{
		return static_cast<typename std::remove_cvref<Out_>::type>(get_first_i64x2(horizontal_min_i64x2(a_)));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 max_i64x2(EmuSIMD::i64x2_arg a_, EmuSIMD::i64x2_arg b_)
	{
		return _mm_max_epi64(a_, b_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 horizontal_max_i64x2(EmuSIMD::i64x2_arg a_)
	{
		return max_i64x2(a_, permute_i64x2<make_shuffle_mask_64x2<0, 1>()>(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 horizontal_max_fill_i64x2(EmuSIMD::i64x2_arg a_)
	{
		return horizontal_max_i64x2(a_);
	}

	template<typename Out_>
	EMU_SIMD_COMMON_FUNC_SPEC auto horizontal_max_fill_i64x2(EmuSIMD::i64x2_arg a_)
		-> typename std::remove_cvref<Out_>::type
	{
		return static_cast<typename std::remove_cvref<Out_>::type>(get_first_i64x2(horizontal_max_i64x2(a_)));
	}
#pragma endregion

#pragma region BASIC_ARITHMETIC
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 mul_all_i64x2(EmuSIMD::i64x2_arg lhs_, EmuSIMD::i64x2_arg rhs_)
	{
		return _mm_mullo_epi64(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 negate_i64x2(EmuSIMD::i64x2_arg to_negate_)
	{
		return _mm_sub_epi64(_mm_setzero_si128(), to_negate_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 add_i64x2(EmuSIMD::i64x2_arg lhs_, EmuSIMD::i64x2_arg rhs_)
	{
		return _mm_add_epi64(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 sub_i64x2(EmuSIMD::i64x2_arg lhs_, EmuSIMD::i64x2_arg rhs_)
	{
		return _mm_sub_epi64(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 div_i64x2(EmuSIMD::i64x2_arg lhs_, EmuSIMD::i64x2_arg rhs_)
	{
#if EMU_CORE_X86_X64_SVML
		return _mm_div_epi64(lhs_, rhs_);
#else
		EmuSIMD::f64x2 result_f64 = cvt_i64x2_f64x2(lhs_);
		result_f64 = div_f64x2(result_f64, cvt_i64x2_f64x2(rhs_));
		return cvt_f64x2_i64x2(trunc_f64x2(result_f64));
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 addsub_i64x2(EmuSIMD::i64x2_arg lhs_, EmuSIMD::i64x2_arg rhs_)
	{
		constexpr std::int64_t bytes_mask = static_cast<std::int64_t>(0xFFFFFFFFFFFFFFFF);
		const EmuSIMD::i64x2 mask = _mm_set_epi64x(bytes_mask, 0);
		EmuSIMD::i64x2 out = _mm_add_epi64(lhs_, _mm_and_si128(mask, rhs_));
		return _mm_sub_epi64(lhs_, _mm_andnot_si128(mask, rhs_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 subadd_i64x2(EmuSIMD::i64x2_arg lhs_, EmuSIMD::i64x2_arg rhs_)
	{
		constexpr std::int64_t bytes_mask = static_cast<std::int64_t>(0xFFFFFFFF);
		const EmuSIMD::i64x2 mask = _mm_set_epi64x(bytes_mask, 0);
		EmuSIMD::i64x2 out = _mm_sub_epi64(lhs_, _mm_and_si128(mask, rhs_));
		return _mm_add_epi64(lhs_, _mm_andnot_si128(mask, rhs_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 fmadd_i64x2(EmuSIMD::i64x2_arg a_, EmuSIMD::i64x2_arg b_, EmuSIMD::i64x2_arg c_)
	{
		return _mm_add_epi64(mul_all_i64x2(a_, b_), c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 fmsub_i64x2(EmuSIMD::i64x2_arg a_, EmuSIMD::i64x2_arg b_, EmuSIMD::i64x2_arg c_)
	{
		return _mm_sub_epi64(mul_all_i64x2(a_, b_), c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 fnmadd_i64x2(EmuSIMD::i64x2_arg a_, EmuSIMD::i64x2_arg b_, EmuSIMD::i64x2_arg c_)
	{
		return _mm_add_epi64(mul_all_i64x2(negate_i64x2(a_), b_), c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 fnmsub_i64x2(EmuSIMD::i64x2_arg a_, EmuSIMD::i64x2_arg b_, EmuSIMD::i64x2_arg c_)
	{
		return _mm_sub_epi64(mul_all_i64x2(negate_i64x2(a_), b_), c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 fmaddsub_i64x2(EmuSIMD::i64x2_arg a_, EmuSIMD::i64x2_arg b_, EmuSIMD::i64x2_arg c_)
	{
		return addsub_i64x2(mul_all_i64x2(a_, b_), c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 fmsubadd_i64x2(EmuSIMD::i64x2_arg a_, EmuSIMD::i64x2_arg b_, EmuSIMD::i64x2_arg c_)
	{
		return subadd_i64x2(mul_all_i64x2(a_, b_), c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 floor_i64x2(EmuSIMD::i64x2_arg to_floor_)
	{
		return to_floor_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 ceil_i64x2(EmuSIMD::i64x2_arg to_ceil_)
	{
		return to_ceil_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 trunc_i64x2(EmuSIMD::i64x2_arg to_trunc_)
	{
		return to_trunc_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 mod_i64x2(EmuSIMD::i64x2_arg lhs_, EmuSIMD::i64x2_arg rhs_)
	{
#if EMU_CORE_X86_X64_SVML
		return _mm_rem_epi64(lhs_, rhs_);
#else
		EmuSIMD::i64x2 to_subtract = div_i64x2(lhs_, rhs_);
		to_subtract = mul_all_i64x2(to_subtract, rhs_);
		return sub_i64x2(lhs_, to_subtract);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 abs_i64x2(EmuSIMD::i64x2_arg in_)
	{
		return _mm_abs_epi64(in_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 sqrt_i64x2(EmuSIMD::i64x2_arg in_)
	{
		return emulate_fp_i64x2([](EmuSIMD::f64x2_arg in_fp_) { return sqrt_f64x2(in_fp_); }, in_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 rsqrt_i64x2(EmuSIMD::i64x2_arg in_)
	{
		return emulate_fp_i64x2([](EmuSIMD::f64x2_arg in_fp_) { return rsqrt_f64x2(in_fp_); }, in_);
	}
#pragma endregion

#pragma region NEAR_COMPARISONS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 cmpnear_i64x2(EmuSIMD::i64x2_arg lhs_, EmuSIMD::i64x2_arg rhs_)
	{
		return cmpeq_i64x2(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 cmpnear_i64x2(EmuSIMD::i64x2_arg lhs_, EmuSIMD::i64x2_arg rhs_, EmuSIMD::i64x2_arg epsilon)
	{
		return cmple_i64x2(abs_i64x2(sub_i64x2(lhs_, rhs_)), epsilon);
	}
#pragma endregion

#pragma region TRIG
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 cos_i64x2(EmuSIMD::i64x2_arg in_)
	{
		return emulate_fp_i64x2([](EmuSIMD::f64x2_arg in_fp_) { return cos_f64x2(in_fp_); }, in_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 sin_i64x2(EmuSIMD::i64x2_arg in_)
	{
		return emulate_fp_i64x2([](EmuSIMD::f64x2_arg in_fp_) { return sin_f64x2(in_fp_); }, in_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 tan_i64x2(EmuSIMD::i64x2_arg in_)
	{
		return emulate_fp_i64x2([](EmuSIMD::f64x2_arg in_fp_) { return tan_f64x2(in_fp_); }, in_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 acos_i64x2(EmuSIMD::i64x2_arg in_)
	{
		return emulate_fp_i64x2([](EmuSIMD::f64x2_arg in_fp_) { return acos_f64x2(in_fp_); }, in_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 asin_i64x2(EmuSIMD::i64x2_arg in_)
	{
		return emulate_fp_i64x2([](EmuSIMD::f64x2_arg in_fp_) { return asin_f64x2(in_fp_); }, in_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::i64x2 atan_i64x2(EmuSIMD::i64x2_arg in_)
	{
		return emulate_fp_i64x2([](EmuSIMD::f64x2_arg in_fp_) { return atan_f64x2(in_fp_); }, in_);
	}
#pragma endregion
}

#endif
