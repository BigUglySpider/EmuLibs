#ifndef EMU_SIMD_GENERIC_FUNCS_F64X8_H_INC_
#define EMU_SIMD_GENERIC_FUNCS_F64X8_H_INC_ 1

#include "_generic_declarations/_all_generic_declarations.h"
#include "_common_generic_func_helpers.h"

namespace EmuSIMD::Funcs
{
#pragma region SETTERS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 set_f64x8(double e0, double e1, double e2, double e3, double e4, double e5, double e6, double e7)
	{
		return _mm512_set_pd(e0, e1, e2, e3, e4, e5, e6, e7);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 setr_f64x8(double e0, double e1, double e2, double e3, double e4, double e5, double e6, double e7)
	{
		//return _mm512_setr_pd(e0, e1, e2, e3, e4, e5, e6, e7);
		return _mm512_set_pd(e7, e6, e5, e4, e3, e2, e1, e0);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 set1_f64x8(double all_)
	{
		return _mm512_set1_pd(all_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 load_f64x8(const double* p_to_load_)
	{
		return _mm512_loadu_pd(p_to_load_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 aligned_load_f64x8(const double* p_to_load_)
	{
		return _mm512_load_pd(p_to_load_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 setzero_f64x8()
	{
		return _mm512_setzero_pd();
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 setmasked_f64x8(std::uint8_t bit_mask_)
	{
		constexpr std::int64_t element_mask = static_cast<std::int64_t>(0xFFFFFFFFFFFFFFFF);
		return _mm512_castsi512_pd
		(
			_mm512_set_epi64
			(
				(bit_mask_  & 0x01)       * element_mask,
				((bit_mask_ & 0x02) >> 1) * element_mask,
				((bit_mask_ & 0x04) >> 2) * element_mask,
				((bit_mask_ & 0x08) >> 3) * element_mask,
				((bit_mask_ & 0x10) >> 4) * element_mask,
				((bit_mask_ & 0x20) >> 5) * element_mask,
				((bit_mask_ & 0x40) >> 6) * element_mask,
				((bit_mask_ & 0x80) >> 7) * element_mask
			)
		);
	}
	

	template<std::uint8_t BitMask_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 setmasked_f64x8()
	{
		if constexpr(BitMask_ != 0)
		{
			return cast_u64x8_f64x8
			(
				set_u64x8
				(
					std::integral_constant<std::uint64_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<0, std::uint64_t>(BitMask_)>::value,
					std::integral_constant<std::uint64_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<1, std::uint64_t>(BitMask_)>::value,
					std::integral_constant<std::uint64_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<2, std::uint64_t>(BitMask_)>::value,
					std::integral_constant<std::uint64_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<3, std::uint64_t>(BitMask_)>::value,
					std::integral_constant<std::uint64_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<4, std::uint64_t>(BitMask_)>::value,
					std::integral_constant<std::uint64_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<5, std::uint64_t>(BitMask_)>::value,
					std::integral_constant<std::uint64_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<6, std::uint64_t>(BitMask_)>::value,
					std::integral_constant<std::uint64_t, EmuCore::ArithmeticHelpers::make_from_masked_bit<7, std::uint64_t>(BitMask_)>::value
				)
			);
		}
		else
		{
			return setzero_f64x8();
		}
	}

	template<bool I0_, bool I1_, bool I2_, bool I3_, bool I4_, bool I5_, bool I6_, bool I7_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 set_index_mask_f64x8()
	{
		if constexpr (I0_ || I1_ || I2_ || I3_ || I4_ || I5_ || I6_ || I7_)
		{
			return setmasked_f64x8<EmuSIMD::Funcs::make_index_set_mask<I0_, I1_, I2_, I3_, I4_, I5_, I6_, I7_>()>();
		}
		else
		{
			return setzero_f64x8();
		}
	}

	template<bool Active_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 set_index_mask_f64x8()
	{
		if constexpr (Active_)
		{
			return setmasked_f64x4<EmuSIMD::Funcs::make_all_indices_set_mask<8, Active_>()>();
		}
		else
		{
			return setzero_f64x8();
		}
	}
#pragma endregion

#pragma region STORES
	EMU_SIMD_COMMON_FUNC_SPEC void store_f64x8(double* p_out_, f64x8_arg a_)
	{
		_mm512_storeu_pd(p_out_, a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC void aligned_store_f64x8(double* p_out_, f64x8_arg a_)
	{
		_mm512_store_pd(p_out_, a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC double get_first_f64x8(f64x8_arg a_)
	{
		return get_first_f64x2(cast_f64x8_f64x2(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC std::uint8_t movemask_f64x8(f64x8_arg a_)
	{
		return movemask_i64x8(cast_f64x8_i64x8(a_));
	}
#pragma endregion

#pragma region CASTS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cast_f32x4_f64x8(f32x4_arg a_)
	{
		return _mm512_castps_pd(_mm512_castps128_ps512(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cast_f32x8_f64x8(f32x8_arg a_)
	{
		return _mm512_castps_pd(_mm512_castps256_ps512(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cast_f32x16_f64x8(f32x16_arg a_)
	{
		return _mm512_castps_pd(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cast_f64x2_f64x8(f64x2_arg a_)
	{
		return _mm512_castpd128_pd512(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cast_f64x4_f64x8(f64x4_arg a_)
	{
		return _mm512_castpd256_pd512(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cast_f64x8_f64x8(f64x8_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cast_i8x16_f64x8(i8x16_arg a_)
	{
		return _mm512_castpd128_pd512(_mm_castsi128_pd(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cast_i16x8_f64x8(i16x8_arg a_)
	{
		return _mm512_castpd128_pd512(_mm_castsi128_pd(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cast_i32x4_f64x8(i32x4_arg a_)
	{
		return _mm512_castpd128_pd512(_mm_castsi128_pd(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cast_i64x2_f64x8(i64x2_arg a_)
	{
		return _mm512_castpd128_pd512(_mm_castsi128_pd(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cast_i8x32_f64x8(i8x32_arg a_)
	{
		return _mm512_castpd256_pd512(_mm256_castsi256_pd(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cast_i16x16_f64x8(i16x16_arg a_)
	{
		return _mm512_castpd256_pd512(_mm256_castsi256_pd(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cast_i32x8_f64x8(i32x8_arg a_)
	{
		return _mm512_castpd256_pd512(_mm256_castsi256_pd(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cast_i64x4_f64x8(i64x4_arg a_)
	{
		return _mm512_castpd256_pd512(_mm256_castsi256_pd(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cast_i8x64_f64x8(i8x64_arg a_)
	{
		return _mm512_castsi512_pd(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cast_i16x32_f64x8(i16x32_arg a_)
	{
		return _mm512_castsi512_pd(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cast_i32x16_f64x8(i32x16_arg a_)
	{
		return _mm512_castsi512_pd(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cast_i64x8_f64x8(i64x8_arg a_)
	{
		return _mm512_castsi512_pd(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cast_u8x16_f64x8(u8x16_arg a_)
	{
		return _mm512_castpd128_pd512(_mm_castsi128_pd(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cast_u16x8_f64x8(u16x8_arg a_)
	{
		return _mm512_castpd128_pd512(_mm_castsi128_pd(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cast_u32x4_f64x8(u32x4_arg a_)
	{
		return _mm512_castpd128_pd512(_mm_castsi128_pd(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cast_u64x2_f64x8(u64x2_arg a_)
	{
		return _mm512_castpd128_pd512(_mm_castsi128_pd(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cast_u8x32_f64x8(u8x32_arg a_)
	{
		return _mm512_castpd256_pd512(_mm256_castsi256_pd(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cast_u16x16_f64x8(u16x16_arg a_)
	{
		return _mm512_castpd256_pd512(_mm256_castsi256_pd(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cast_u32x8_f64x8(u32x8_arg a_)
	{
		return _mm512_castpd256_pd512(_mm256_castsi256_pd(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cast_u64x4_f64x8(u64x4_arg a_)
	{
		return _mm512_castpd256_pd512(_mm256_castsi256_pd(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cast_u8x64_f64x8(u8x64_arg a_)
	{
		return _mm512_castsi512_pd(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cast_u16x32_f64x8(u16x32_arg a_)
	{
		return _mm512_castsi512_pd(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cast_u32x16_f64x8(u32x16_arg a_)
	{
		return _mm512_castsi512_pd(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cast_u64x8_f64x8(u64x8_arg a_)
	{
		return _mm512_castsi512_pd(a_);
	}
#pragma endregion

#pragma region CONVERSIONS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cvt_f32x4_f64x8(f32x4_arg a_)
	{
		return _mm512_castpd256_pd512(_mm256_cvtps_pd(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cvt_f32x8_f64x8(f32x8_arg a_)
	{
		return _mm512_cvtps_pd(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cvt_f32x16_f64x8(f32x16_arg a_)
	{
		return _mm512_cvtps_pd(_mm512_castps512_ps256(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cvt_f64x2_f64x8(f64x2_arg a_)
	{
		return _mm512_castpd128_pd512(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cvt_f64x4_f64x8(f64x4_arg a_)
	{
		return _mm512_castpd256_pd512(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cvt_f64x8_f64x8(f64x8_arg a_)
	{
		return a_;
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cvt_i8x16_f64x8(i8x16_arg a_)
	{
		return _mm512_cvtepi64_pd(_mm512_cvtepi8_epi64(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cvt_i16x8_f64x8(i16x8_arg a_)
	{
		return _mm512_cvtepi64_pd(_mm512_cvtepi16_epi64(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cvt_i32x4_f64x8(i32x4_arg a_)
	{
		return _mm512_castpd256_pd512(_mm256_cvtepi32_pd(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cvt_i64x2_f64x8(i64x2_arg a_)
	{
		return _mm512_castpd128_pd512(_mm_cvtepi64_pd(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cvt_i8x32_f64x8(i8x32_arg a_)
	{
		return _mm512_cvtepi64_pd(_mm512_cvtepi8_epi64(_mm256_castsi256_si128(a_)));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cvt_i16x16_f64x8(i16x16_arg a_)
	{
		return _mm512_cvtepi64_pd(_mm512_cvtepi16_epi64(_mm256_castsi256_si128(a_)));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cvt_i32x8_f64x8(i32x8_arg a_)
	{
		return _mm512_cvtepi32_pd(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cvt_i64x4_f64x8(i64x4_arg a_)
	{
		return _mm512_castpd256_pd512(_mm256_cvtepi64_pd(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cvt_i8x64_f64x8(i8x64_arg a_)
	{
		return _mm512_cvtepi64_pd(_mm512_cvtepi8_epi64(_mm512_castsi512_si128(a_)));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cvt_i16x32_f64x8(i16x32_arg a_)
	{
		return _mm512_cvtepi64_pd(_mm512_cvtepi16_epi64(_mm512_castsi512_si128(a_)));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cvt_i32x16_f64x8(i32x16_arg a_)
	{
		return _mm512_cvtepi32_pd(_mm512_castsi512_si256(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cvt_i64x8_f64x8(i64x8_arg a_)
	{
		return _mm512_cvtepi64_pd(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cvt_u8x16_f64x8(u8x16_arg a_)
	{
		return _mm512_cvtepi64_pd(_mm512_cvtepu8_epi64(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cvt_u16x8_f64x8(u16x8_arg a_)
	{
		return _mm512_cvtepi64_pd(_mm512_cvtepu16_epi64(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cvt_u32x4_f64x8(u32x4_arg a_)
	{
		return _mm512_castpd256_pd512(_mm256_cvtepu32_pd(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cvt_u64x2_f64x8(u64x2_arg a_)
	{
		return _mm512_castpd128_pd512(_mm_cvtepu64_pd(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cvt_u8x32_f64x8(u8x32_arg a_)
	{
		return _mm512_cvtepi64_pd(_mm512_cvtepu8_epi64(_mm256_castsi256_si128(a_)));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cvt_u16x16_f64x8(u16x16_arg a_)
	{
		return _mm512_cvtepi64_pd(_mm512_cvtepu16_epi64(_mm256_castsi256_si128(a_)));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cvt_u32x8_f64x8(u32x8_arg a_)
	{
		return _mm512_cvtepu32_pd(a_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cvt_u64x4_f64x8(u64x4_arg a_)
	{
		return _mm512_castpd256_pd512(_mm256_cvtepu64_pd(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cvt_u8x64_f64x8(u8x64_arg a_)
	{
		return _mm512_cvtepi64_pd(_mm512_cvtepu8_epi64(_mm512_castsi512_si128(a_)));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cvt_u16x32_f64x8(u16x32_arg a_)
	{
		return _mm512_cvtepi64_pd(_mm512_cvtepu16_epi64(_mm512_castsi512_si128(a_)));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cvt_u32x16_f64x8(u32x16_arg a_)
	{
		return _mm512_cvtepu32_pd(_mm512_castsi512_si256(a_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cvt_u64x8_f64x8(u64x8_arg a_)
	{
		return _mm512_cvtepu64_pd(a_);
	}
#pragma endregion

#pragma region COMPARISONS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cmpeq_f64x8(EmuSIMD::f64x8_arg lhs_, EmuSIMD::f64x8_arg rhs_)
	{
		return setmasked_f64x8(_mm512_cmpeq_pd_mask(lhs_, rhs_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cmpneq_f64x8(EmuSIMD::f64x8_arg lhs_, EmuSIMD::f64x8_arg rhs_)
	{
		return setmasked_f64x8(_mm512_cmpneq_pd_mask(lhs_, rhs_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cmpgt_f64x8(EmuSIMD::f64x8_arg lhs_, EmuSIMD::f64x8_arg rhs_)
	{
		return setmasked_f64x8(_mm512_cmplt_pd_mask(rhs_, lhs_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cmplt_f64x8(EmuSIMD::f64x8_arg lhs_, EmuSIMD::f64x8_arg rhs_)
	{
		return setmasked_f64x8(_mm512_cmplt_pd_mask(lhs_, rhs_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cmpge_f64x8(EmuSIMD::f64x8_arg lhs_, EmuSIMD::f64x8_arg rhs_)
	{
		return setmasked_f64x8(_mm512_cmple_pd_mask(rhs_, lhs_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cmple_f64x8(EmuSIMD::f64x8_arg lhs_, EmuSIMD::f64x8_arg rhs_)
	{
		return setmasked_f64x8(_mm512_cmple_pd_mask(lhs_, rhs_));
	}
#pragma endregion

#pragma region BLENDS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 blendv_f64x8(EmuSIMD::f64x8_arg a_, EmuSIMD::f64x8_arg b_, EmuSIMD::f64x8_arg shuffle_mask_vec_)
	{
		EmuSIMD::f64x4 lo = blendv_f64x4(cast_f64x8_f64x4(a_), cast_f64x8_f64x4(b_), cast_f64x8_f64x4(shuffle_mask_vec_));
		EmuSIMD::f64x4 hi = blendv_f64x4(_mm512_extractf64x4_pd(a_, 1), _mm512_extractf64x4_pd(b_, 1), _mm512_extractf64x4_pd(shuffle_mask_vec_, 1));
		return _mm512_insertf64x4(cast_f64x4_f64x8(lo), hi, 1);
	}
#pragma endregion

#pragma region MOVES
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 movehl_f64x8(EmuSIMD::f64x8_arg lhs_, EmuSIMD::f64x8_arg rhs_)
	{
		constexpr auto permute_mask = EmuSIMD::Funcs::make_shuffle_mask_32<3, 2, 3, 2>(); // Mask for { b[hi] a[hi] } - Uses 32-bit mask maker as the format used is the same
		return _mm512_shuffle_f64x2(rhs_, lhs_, permute_mask);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 movelh_f64x8(EmuSIMD::f64x8_arg lhs_, EmuSIMD::f64x8_arg rhs_)
	{
		constexpr auto permute_mask = EmuSIMD::Funcs::make_shuffle_mask_32<1, 0, 1, 0>(); // Mask for { a[lo] b[lo] } - Uses 32-bit mask maker as the format used is the same
		return _mm512_shuffle_f64x2(lhs_, rhs_, permute_mask);
	}
#pragma endregion

#pragma region BITWISE_ARITHMETIC
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 and_f64x8(EmuSIMD::f64x8_arg lhs_, EmuSIMD::f64x8_arg rhs_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_and_pd(lhs_, rhs_);
#else
		using EmuSIMD::_underlying_impl::emulate_simd_basic;
		return emulate_simd_basic([](f64x4_arg a_, f64x4_arg b_) { return EmuSIMD::Funcs::and_f64x4(a_, b_); }, lhs_, rhs_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 or_f64x8(EmuSIMD::f64x8_arg lhs_, EmuSIMD::f64x8_arg rhs_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_or_pd(lhs_, rhs_);
#else
		using EmuSIMD::_underlying_impl::emulate_simd_basic;
		return emulate_simd_basic([](f64x4_arg a_, f64x4_arg b_) { return EmuSIMD::Funcs::or_f64x4(a_, b_); }, lhs_, rhs_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 xor_f64x8(EmuSIMD::f64x8_arg lhs_, EmuSIMD::f64x8_arg rhs_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_xor_pd(lhs_, rhs_);
#else
		using EmuSIMD::_underlying_impl::emulate_simd_basic;
		return emulate_simd_basic([](f64x4_arg a_, f64x4_arg b_) { return EmuSIMD::Funcs::xor_f64x4(a_, b_); }, lhs_, rhs_);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 andnot_f64x8(EmuSIMD::f64x8_arg not_lhs_, EmuSIMD::f64x8_arg rhs_)
	{
#if EMU_SIMD_USE_512_REGISTERS
		return _mm512_andnot_pd(not_lhs_, rhs_);
#else
		using EmuSIMD::_underlying_impl::emulate_simd_basic;
		return emulate_simd_basic([](f64x4_arg a_, f64x4_arg b_) { return EmuSIMD::Funcs::andnot_f64x4(a_, b_); }, not_lhs_, rhs_);
#endif
	}

	template<std::int32_t NumShifts_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 shift_left_f64x8(EmuSIMD::f64x8_arg lhs_)
	{
		return cast_i64x2_f64x8
		(
			shift_left_i64x8<NumShifts_>(cast_f64x8_i64x8(lhs_))
		);
	}

	template<std::int32_t NumShifts_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 shift_right_arithmetic_f64x8(EmuSIMD::f64x8_arg lhs_)
	{
		if constexpr (NumShifts_ >= 64)
		{
			return setzero_f64x8();
		}
		else
		{
			constexpr double sign_bit = -0.0;
			f64x8 sign_mask = set1_f64x8(sign_bit);
			sign_mask = and_f64x8(sign_mask, lhs_);
			return or_f64x8(sign_mask, shift_right_logical_f64x8<NumShifts_>(lhs_));
		}
	}

	template<std::int32_t NumShifts_>
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 shift_right_logical_f64x8(EmuSIMD::f64x8_arg lhs_)
	{
		return cast_i64x2_f64x8
		(
			shift_right_logical_i64x8<NumShifts_>(cast_f64x8_i64x8(lhs_))
		);
	}
#pragma endregion

#pragma region MINMAX_FUNCS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 min_f64x8(EmuSIMD::f64x8_arg a_, EmuSIMD::f64x8_arg b_)
	{
		return _mm512_min_pd(a_, b_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 horizontal_min_f64x8(EmuSIMD::f64x8_arg a_)
	{
		EmuSIMD::f64x4 min256 = cast_f64x8_f64x4(a_);
		min256 = min_f64x4(min256, _mm512_extractf64x4_pd(a_, 1));
		min256 = horizontal_min_f64x4(min256);
		return _mm512_insertf64x4(cast_f64x4_f64x8(min256), min256, 1);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 max_f64x8(EmuSIMD::f64x8_arg a_, EmuSIMD::f64x8_arg b_)
	{
		return _mm512_max_pd(a_, b_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 horizontal_max_f64x8(EmuSIMD::f64x8_arg a_)
	{
		EmuSIMD::f64x4 max256 = cast_f64x8_f64x4(a_);
		max256 = max_f64x4(max256, _mm512_extractf64x4_pd(a_, 1));
		max256 = horizontal_max_f64x4(max256);
		return _mm512_insertf64x4(cast_f64x4_f64x8(max256), max256, 1);
	}
#pragma endregion

#pragma region BASIC_ARITHMETIC
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 mul_all_f64x8(EmuSIMD::f64x8_arg lhs_, EmuSIMD::f64x8_arg rhs_)
	{
		return _mm512_mul_pd(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 negate_f64x8(EmuSIMD::f64x8_arg to_negate_)
	{
		return _mm512_sub_pd(_mm512_setzero_pd(), to_negate_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 add_f64x8(EmuSIMD::f64x8_arg lhs_, EmuSIMD::f64x8_arg rhs_)
	{
		return _mm512_add_pd(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 sub_f64x8(EmuSIMD::f64x8_arg lhs_, EmuSIMD::f64x8_arg rhs_)
	{
		return _mm512_sub_pd(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 mul_f64x8(EmuSIMD::f64x8_arg lhs_, EmuSIMD::f64x8_arg rhs_)
	{
		return _mm512_mul_pd(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 div_f64x8(EmuSIMD::f64x8_arg lhs_, EmuSIMD::f64x8_arg rhs_)
	{
		return _mm512_div_pd(lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 fmadd_f64x8(EmuSIMD::f64x8_arg a_, EmuSIMD::f64x8_arg b_, EmuSIMD::f64x8_arg c_)
	{
		return _mm512_fmadd_pd(a_, b_, c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 fmsub_f64x8(EmuSIMD::f64x8_arg a_, EmuSIMD::f64x8_arg b_, EmuSIMD::f64x8_arg c_)
	{
		return _mm512_fmsub_pd(a_, b_, c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 fnmadd_f64x8(EmuSIMD::f64x8_arg a_, EmuSIMD::f64x8_arg b_, EmuSIMD::f64x8_arg c_)
	{
		return _mm512_fnmadd_pd(a_, b_, c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 fnmsub_f64x8(EmuSIMD::f64x8_arg a_, EmuSIMD::f64x8_arg b_, EmuSIMD::f64x8_arg c_)
	{
		return _mm512_fnmsub_pd(a_, b_, c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 fmaddsub_f64x8(EmuSIMD::f64x8_arg a_, EmuSIMD::f64x8_arg b_, EmuSIMD::f64x8_arg c_)
	{
		return _mm512_fmaddsub_pd(a_, b_, c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 fmsubadd_f64x8(EmuSIMD::f64x8_arg a_, EmuSIMD::f64x8_arg b_, EmuSIMD::f64x8_arg c_)
	{
		return _mm512_fmsubadd_pd(a_, b_, c_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 addsub_f64x8(EmuSIMD::f64x8_arg lhs_, EmuSIMD::f64x8_arg rhs_)
	{
		return fmaddsub_f64x8(set1_f64x8(1.0), lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 subadd_f64x8(EmuSIMD::f64x8_arg lhs_, EmuSIMD::f64x8_arg rhs_)
	{
		return fmsubadd_f64x8(set1_f64x8(1.0), lhs_, rhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 floor_f64x8(EmuSIMD::f64x8_arg to_floor_)
	{
		return _mm512_floor_pd(to_floor_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 ceil_f64x8(EmuSIMD::f64x8_arg to_ceil_)
	{
		return _mm512_ceil_pd(to_ceil_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 trunc_f64x8(EmuSIMD::f64x8_arg to_trunc_)
	{
		return _mm512_roundscale_pd(to_trunc_, EMU_SIMD_FLAG_TRUNC);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 mod_f64x8(EmuSIMD::f64x8_arg lhs_, EmuSIMD::f64x8_arg rhs_)
	{
		EmuSIMD::f64x8 res = div_f64x8(lhs_, rhs_);
		res = trunc_f64x8(res);
		return _mm512_fnmadd_pd(res, rhs_, lhs_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 abs_f64x8(EmuSIMD::f64x8_arg in_)
	{
		EmuSIMD::f64x8 negative_mask = cmplt_f64x8(in_, setzero_f64x8());
		EmuSIMD::f64x8 out = _mm512_and_pd(negative_mask, mul_all_f64x8(in_, set1_f64x8(-1)));
		return _mm512_or_pd(out, _mm512_andnot_pd(negative_mask, in_));
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 sqrt_f64x8(EmuSIMD::f64x8_arg in_)
	{
		return _mm512_sqrt_pd(in_);
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 rsqrt_f64x8(EmuSIMD::f64x8_arg in_)
	{
		return div_f64x8(set1_f64x8(1.0), sqrt_f64x8(in_));
	}
#pragma endregion

#pragma region NEAR_COMPARISONS
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cmpnear_f64x8(EmuSIMD::f64x8_arg lhs_, EmuSIMD::f64x8_arg rhs_, EmuSIMD::f64x8_arg epsilon)
	{
		return cmple_f64x8(abs_f64x8(sub_f64x8(lhs_, rhs_)), epsilon);
	}
#pragma endregion

#pragma region TRIG
	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 cos_f64x8(EmuSIMD::f64x8_arg in_)
	{
#if EMU_CORE_IS_INTEL_COMPILER && EMU_CORE_X86_X64 // Only tends to score better on Intel platforms
		return _mm512_cos_pd(in_);
#else
		// Alternative manual approximation, based on https://developer.download.nvidia.com/cg/cos.html implementation

		// Store constants used > once in registers to allow shuffling them instead of multiple sets of the same
		EmuSIMD::f64x8 one_c4z = setr_f64x8(1.0, -1.0, 1.0, -1.0, 1.0, -1.0, 1.0, -1.0);

		// Prepare for power series
		EmuSIMD::f64x8 r1x = mul_f64x8(set1_f64x8(0.159154943091), in_); // r1.x = c1.w * in_;

		EmuSIMD::f64x8 r1y = trunc_f64x8(r1x); // r1.y = frac(r1.x)
		r1y = sub_f64x8(r1x, r1y);

		EmuSIMD::f64x8 const0 = set1_f64x8(0.25f);
		EmuSIMD::f64x8 r2x = cmplt_f64x8(r1x, const0); // r2.x = r1.x < c1.x

		const0 = permute_f64x8<make_shuffle_mask_64<0, 0, 0, 0, 0, 0, 0, 0>()>(one_c4z);
		r2x = and_f64x8(r2x, const0);

		EmuSIMD::f64x8 r2y = cmpge_f64x8(r1y, set1_f64x8(-9.0)); // r2.yz = r1.yy >= c1.yz
		EmuSIMD::f64x8 r2z = cmpge_f64x8(r1y, set1_f64x8(0.75));
		r2y = and_f64x8(r2y, const0);
		r2z = and_f64x8(r2z, const0);

		EmuSIMD::f64x8 const1 = permute_f64x8<make_shuffle_mask_64<1, 1, 1, 1, 1, 1, 1, 1>()>(one_c4z);
		r2y = fmadd_f64x8(r2x, const1, fmadd_f64x8(r2y, const0, mul_f64x8(r2z, const1))); // dot(r2, c4.zwz)

		EmuSIMD::f64x8 r0x = negate_f64x8(r1y);
		EmuSIMD::f64x8 r0y = sub_f64x8(set1_f64x8(0.5), r1y);
		EmuSIMD::f64x8 r0z = sub_f64x8(const0, r1y);
		r0x = mul_f64x8(r0x, r0x);
		r0y = mul_f64x8(r0y, r0y);
		r0z = mul_f64x8(r0z, r0z);

		// Begin power series
		// --- Power 1
		const0 = set1_f64x8(-60.1458091736);
		const1 = set1_f64x8(24.9808039603);
		r1x = fmadd_f64x8(const1, r0x, const0);
		r1y = fmadd_f64x8(set1_f64x8(-24.9808039603), r0y, set1_f64x8(60.1458091736));
		EmuSIMD::f64x8 r1z = fmadd_f64x8(const1, r0z, const0);

		// --- Power 2
		const0 = set1_f64x8(85.4537887573f);
		r1x = fmadd_f64x8(r1x, r0x, const0);
		r1y = fmadd_f64x8(r1y, r0y, set1_f64x8(-85.4537887573));
		r1z = fmadd_f64x8(r1z, r0z, const0);

		// --- Power 3
		const0 = set1_f64x8(-64.9393539429f);
		r1x = fmadd_f64x8(r1x, r0x, const0);
		r1y = fmadd_f64x8(r1y, r0y, set1_f64x8(64.9393539429));
		r1z = fmadd_f64x8(r1z, r0z, const0);

		// --- Power 4
		const0 = set1_f64x8(19.7392082214f);
		r1x = fmadd_f64x8(r1x, r0x, const0);
		r1y = fmadd_f64x8(r1y, r0y, set1_f64x8(-19.7392082214));
		r1z = fmadd_f64x8(r1z, r0z, const0);

		// --- Power 5
		const0 = permute_f64x8<make_shuffle_mask_64<0, 0, 0, 0, 0, 0, 0, 0>()>(one_c4z);
		const1 = permute_f64x8<make_shuffle_mask_64<1, 1, 1, 1, 1, 1, 1, 1>()>(one_c4z);
		r1x = fmadd_f64x8(r1x, r0x, const1);
		r1y = fmadd_f64x8(r1y, r0y, const0);
		r1z = fmadd_f64x8(r1z, r0z, const1);

		// Final dot
		r2x = negate_f64x8(r2x);
		r2y = negate_f64x8(r2y);
		r2z = negate_f64x8(r2z);

		return fmadd_f64x8(r1x, r2x, fmadd_f64x8(r1y, r2y, mul_f64x8(r1z, r2z)));
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 sin_f64x8(EmuSIMD::f64x8_arg in_)
	{
#if EMU_CORE_IS_INTEL_COMPILER && EMU_CORE_X86_X64 // Only tends to score better on Intel platforms
		return _mm512_sin_pd(in_);
#else
		// Alternative manual approximation, based on https://developer.download.nvidia.com/cg/sin.html implementation

		// Store constants used > once in registers to allow shuffling to them
		EmuSIMD::f64x8 one_c4z = setr_f64x8(1.0, -1.0, 1.0, -1.0, 1.0, -1.0, 1.0, -1.0);

		// Prepare for power series
		EmuSIMD::f64x8 const0 = set1_f64x8(0.25);
		EmuSIMD::f64x8 r1x = fmsub_f64x8(set1_f64x8(0.159154943091), in_, const0); // r1.x = c1.w * in_ - c1.x

		EmuSIMD::f64x8 r1y = trunc_f64x8(r1x); // r1.y = frac(r1.x)
		r1y = sub_f64x8(r1x, r1y);

		EmuSIMD::f64x8 r2x = cmplt_f64x8(r1x, const0); // r2.x = r1.x < c1.x

		const0 = permute_f64x8<make_shuffle_mask_64<0, 0, 0, 0, 0, 0, 0, 0>()>(one_c4z);
		r2x = and_f64x8(r2x, const0);

		EmuSIMD::f64x8 r2y = cmpge_f64x8(r1y, set1_f64x8(-9.0)); // r2.yz = r1.yy >= c1.yz
		EmuSIMD::f64x8 r2z = cmpge_f64x8(r1y, set1_f64x8(0.75));
		r2y = and_f64x8(r2y, const0);
		r2z = and_f64x8(r2z, const0);

		EmuSIMD::f64x8 const1 = permute_f64x8<make_shuffle_mask_64<1, 1, 1, 1, 1, 1, 1, 1>()>(one_c4z);
		r2y = fmadd_f64x8(r2x, const1, fmadd_f64x8(r2y, const0, mul_f64x8(r2z, const1))); // dot(r2, c4.zwz)

		EmuSIMD::f64x8 r0x = negate_f64x8(r1y);
		EmuSIMD::f64x8 r0y = sub_f64x8(set1_f64x8(0.5), r1y);
		EmuSIMD::f64x8 r0z = sub_f64x8(const0, r1y);
		r0x = mul_f64x8(r0x, r0x);
		r0y = mul_f64x8(r0y, r0y);
		r0z = mul_f64x8(r0z, r0z);

		// Begin power series
		// --- Power 1
		const0 = set1_f64x8(-60.1458091736);
		const1 = set1_f64x8(24.9808039603);
		r1x = fmadd_f64x8(const1, r0x, const0);
		r1y = fmadd_f64x8(set1_f64x8(-24.9808039603), r0y, set1_f64x8(60.1458091736));
		EmuSIMD::f64x8 r1z = fmadd_f64x8(const1, r0z, const0);

		// --- Power 2
		const0 = set1_f64x8(85.4537887573);
		r1x = fmadd_f64x8(r1x, r0x, const0);
		r1y = fmadd_f64x8(r1y, r0y, set1_f64x8(-85.4537887573));
		r1z = fmadd_f64x8(r1z, r0z, const0);

		// --- Power 3
		const0 = set1_f64x8(-64.9393539429);
		r1x = fmadd_f64x8(r1x, r0x, const0);
		r1y = fmadd_f64x8(r1y, r0y, set1_f64x8(64.9393539429));
		r1z = fmadd_f64x8(r1z, r0z, const0);

		// --- Power 4
		const0 = set1_f64x8(19.7392082214);
		r1x = fmadd_f64x8(r1x, r0x, const0);
		r1y = fmadd_f64x8(r1y, r0y, set1_f64x8(-19.7392082214));
		r1z = fmadd_f64x8(r1z, r0z, const0);

		// --- Power 5
		const0 = permute_f64x8<make_shuffle_mask_64<0, 0, 0, 0, 0, 0, 0, 0>()>(one_c4z);
		const1 = permute_f64x8<make_shuffle_mask_64<1, 1, 1, 1, 1, 1, 1, 1>()>(one_c4z);
		r1x = fmadd_f64x8(r1x, r0x, const1);
		r1y = fmadd_f64x8(r1y, r0y, const0);
		r1z = fmadd_f64x8(r1z, r0z, const1);

		// Final dot
		r2x = negate_f64x8(r2x);
		r2y = negate_f64x8(r2y);
		r2z = negate_f64x8(r2z);

		return fmadd_f64x8(r1x, r2x, fmadd_f64x8(r1y, r2y, mul_f64x8(r1z, r2z)));
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 tan_f64x8(EmuSIMD::f64x8_arg in_)
	{
#if (EMU_CORE_IS_INTEL_COMPILER || EMU_CORE_IS_MSVC) && EMU_CORE_X86_X64 // Better on both Intel and AMD x86/x64 builds, so use where available
		return _mm512_tan_pd(in_);
#else
		// Alternative manual approximation using sin/cos, based on https://developer.download.nvidia.com/cg/sin.html & https://developer.download.nvidia.com/cg/cos.html impl.
		// --- Made as a unique function instead of deferring to separate cos and sin to minimise required operations

		// Store constants used > once in registers to allow shuffling to them
		EmuSIMD::f64x8 one_c4z = setr_f64x8(1.0, -1.0, 1.0, -1.0, 1.0, -1.0, 1.0, -1.0);

		// Prepare for power series
		EmuSIMD::f64x8 const0 = set1_f64x8(0.25);
		EmuSIMD::f64x8 r1x_cos = mul_f64x8(set1_f64x8(0.159154943091), in_);
		EmuSIMD::f64x8 r1x_sin = sub_f64x8(r1x_cos, const0); // r1.x = c1.w * in_ - c1.x

		EmuSIMD::f64x8 r1y_sin = trunc_f64x8(r1x_sin); // r1.y = frac(r1.x)
		r1y_sin = sub_f64x8(r1x_sin, r1y_sin);
		EmuSIMD::f64x8 r1y_cos = trunc_f64x8(r1x_sin);
		r1y_cos = sub_f64x8(r1x_cos, r1y_cos);

		EmuSIMD::f64x8 r2x_sin = cmplt_f64x8(r1x_sin, const0); // r2.x = r1.x < c1.x
		EmuSIMD::f64x8 r2x_cos = cmplt_f64x8(r1x_cos, const0);

		const0 = permute_f64x8<make_shuffle_mask_64<0, 0, 0, 0, 0, 0, 0, 0>()>(one_c4z);
		r2x_sin = and_f64x8(r2x_sin, const0);
		r2x_cos = and_f64x8(r2x_cos, const0);

		EmuSIMD::f64x8 const1 = set1_f64x8(-9.0);
		EmuSIMD::f64x8 const2 = set1_f64x8(0.75);
		EmuSIMD::f64x8 r2y_sin = cmpge_f64x8(r1y_sin, const1); // r2.yz = r1.yy >= c1.yz
		EmuSIMD::f64x8 r2z_sin = cmpge_f64x8(r1y_sin, const2);
		r2y_sin = and_f64x8(r2y_sin, const0);
		r2z_sin = and_f64x8(r2z_sin, const0);
		EmuSIMD::f64x8 r2y_cos = cmpge_f64x8(r1y_cos, const1);
		EmuSIMD::f64x8 r2z_cos = cmpge_f64x8(r1y_cos, const2);
		r2y_cos = and_f64x8(r2y_cos, const0);
		r2z_cos = and_f64x8(r2z_cos, const0);

		const1 = permute_f64x8<make_shuffle_mask_64<1, 1, 1, 1, 1, 1, 1, 1>()>(one_c4z);
		r2y_sin = fmadd_f64x8(r2x_sin, const1, fmadd_f64x8(r2y_sin, const0, mul_f64x8(r2z_sin, const1))); // dot(r2, c4.zwz)
		r2y_cos = fmadd_f64x8(r2x_cos, const1, fmadd_f64x8(r2y_cos, const0, mul_f64x8(r2z_cos, const1)));

		const1 = set1_f64x8(0.5);
		EmuSIMD::f64x8 r0x_sin = negate_f64x8(r1y_sin);
		EmuSIMD::f64x8 r0y_sin = sub_f64x8(const1, r1y_sin);
		EmuSIMD::f64x8 r0z_sin = sub_f64x8(const0, r1y_sin);
		r0x_sin = mul_f64x8(r0x_sin, r0x_sin);
		r0y_sin = mul_f64x8(r0y_sin, r0y_sin);
		r0z_sin = mul_f64x8(r0z_sin, r0z_sin);
		EmuSIMD::f64x8 r0x_cos = negate_f64x8(r1y_cos);
		EmuSIMD::f64x8 r0y_cos = sub_f64x8(const1, r1y_cos);
		EmuSIMD::f64x8 r0z_cos = sub_f64x8(const0, r1y_cos);
		r0x_cos = mul_f64x8(r0x_cos, r0x_cos);
		r0y_cos = mul_f64x8(r0y_cos, r0y_cos);
		r0z_cos = mul_f64x8(r0z_cos, r0z_cos);

		// Begin power series
		// --- Power 1
		const0 = set1_f64x8(-60.1458091736);
		EmuSIMD::f64x8 const3 = negate_f64x8(const0);
		const1 = set1_f64x8(24.9808039603);
		const2 = negate_f64x8(const1);
		r1x_sin = fmadd_f64x8(const1, r0x_sin, const0);
		r1y_sin = fmadd_f64x8(const2, r0y_sin, const3);
		EmuSIMD::f64x8 r1z_sin = fmadd_f64x8(const1, r0z_sin, const0);
		r1x_cos = fmadd_f64x8(const1, r0x_cos, const0);
		r1y_cos = fmadd_f64x8(const2, r0y_cos, const3);
		EmuSIMD::f64x8 r1z_cos = fmadd_f64x8(const1, r0z_cos, const0);

		// --- Power 2
		const0 = set1_f64x8(85.4537887573);
		const1 = negate_f64x8(const0);
		r1x_sin = fmadd_f64x8(r1x_sin, r0x_sin, const0);
		r1y_sin = fmadd_f64x8(r1y_sin, r0y_sin, const1);
		r1z_sin = fmadd_f64x8(r1z_sin, r0z_sin, const0);
		r1x_cos = fmadd_f64x8(r1x_cos, r0x_cos, const0);
		r1y_cos = fmadd_f64x8(r1y_cos, r0y_cos, const1);
		r1z_cos = fmadd_f64x8(r1z_cos, r0z_cos, const0);

		// --- Power 3
		const0 = set1_f64x8(-64.9393539429);
		const1 = negate_f64x8(const0);
		r1x_sin = fmadd_f64x8(r1x_sin, r0x_sin, const0);
		r1y_sin = fmadd_f64x8(r1y_sin, r0y_sin, const1);
		r1z_sin = fmadd_f64x8(r1z_sin, r0z_sin, const0);
		r1x_cos = fmadd_f64x8(r1x_cos, r0x_cos, const0);
		r1y_cos = fmadd_f64x8(r1y_cos, r0y_cos, const1);
		r1z_cos = fmadd_f64x8(r1z_cos, r0z_cos, const0);

		// --- Power 4
		const0 = set1_f64x8(19.7392082214);
		const1 = negate_f64x8(const0);
		r1x_sin = fmadd_f64x8(r1x_sin, r0x_sin, const0);
		r1y_sin = fmadd_f64x8(r1y_sin, r0y_sin, const1);
		r1z_sin = fmadd_f64x8(r1z_sin, r0z_sin, const0);
		r1x_cos = fmadd_f64x8(r1x_cos, r0x_cos, const0);
		r1y_cos = fmadd_f64x8(r1y_cos, r0y_cos, const1);
		r1z_cos = fmadd_f64x8(r1z_cos, r0z_cos, const0);

		// --- Power 5
		const0 = permute_f64x8<make_shuffle_mask_64<0, 0, 0, 0, 0, 0, 0, 0>()>(one_c4z);
		const1 = permute_f64x8<make_shuffle_mask_64<1, 1, 1, 1, 1, 1, 1, 1>()>(one_c4z);
		r1x_sin = fmadd_f64x8(r1x_sin, r0x_sin, const1);
		r1y_sin = fmadd_f64x8(r1y_sin, r0y_sin, const0);
		r1z_sin = fmadd_f64x8(r1z_sin, r0z_sin, const1);
		r1x_cos = fmadd_f64x8(r1x_cos, r0x_cos, const1);
		r1y_cos = fmadd_f64x8(r1y_cos, r0y_cos, const0);
		r1z_cos = fmadd_f64x8(r1z_cos, r0z_cos, const1);

		// Final dot - store the sins in r2x
		r2x_sin = negate_f64x8(r2x_sin);
		r2y_sin = negate_f64x8(r2y_sin);
		r2z_sin = negate_f64x8(r2z_sin);
		r2x_sin = fmadd_f64x8(r1x_sin, r2x_sin, fmadd_f64x8(r1y_sin, r2y_sin, mul_f64x8(r1z_sin, r2z_sin)));
		r2x_cos = negate_f64x8(r2x_cos);
		r2y_cos = negate_f64x8(r2y_cos);
		r2z_cos = negate_f64x8(r2z_cos);
		r2x_cos = fmadd_f64x8(r1x_cos, r2x_cos, fmadd_f64x8(r1y_cos, r2y_cos, mul_f64x8(r1z_cos, r2z_cos)));

		return div_f64x8(r2x_sin, r2x_cos);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 acos_f64x8(EmuSIMD::f64x8_arg in_)
	{
#if EMU_CORE_IS_INTEL_COMPILER && EMU_CORE_X86_X64 // Only tends to score better on Intel platforms
		return _mm512_acos_pd(in_);
#else
		// Alternative manual approximation, based on https://developer.download.nvidia.com/cg/acos.html implementation
		EmuSIMD::f64x8 in_abs = abs_f64x8(in_);
		EmuSIMD::f64x8 one = set1_f64x8(1.0);
		EmuSIMD::f64x8 negation_mult = cmple_f64x8(in_, setzero_f64x8());
		negation_mult = and_f64x8(one, negation_mult);

		EmuSIMD::f64x8 result = set1_f64x8(-0.0187293);
		result = fmadd_f64x8(result, in_abs, set1_f64x8(0.074261));
		result = fmsub_f64x8(result, in_abs, set1_f64x8(0.2121144));
		result = fmadd_f64x8(result, in_abs, set1_f64x8(1.5707288));
		result = mul_f64x8(result, sqrt_f64x8(sub_f64x8(one, in_abs)));

		EmuSIMD::f64x8 tmp = mul_f64x8(set1_f64x8(2.0), negation_mult);
		tmp = mul_f64x8(tmp, result);
		result = sub_f64x8(result, tmp);

		return fmadd_f64x8(negation_mult, set1_f64x8(3.14159265358979), result);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 asin_f64x8(EmuSIMD::f64x8_arg in_)
	{
#if EMU_CORE_IS_INTEL_COMPILER && EMU_CORE_X86_X64 // Only tends to score better on Intel platforms
		return _mm512_asin_pd(in_);
#else
		// Alternative manual approximation, based on https://developer.download.nvidia.com/cg/asin.html implementation
		EmuSIMD::f64x8 in_abs = abs_f64x8(in_);
		EmuSIMD::f64x8 two = set1_f64x8(2.0);
		EmuSIMD::f64x8 negation_mult = cmplt_f64x8(in_, setzero_f64x8());
		negation_mult = and_f64x8(two, negation_mult);

		EmuSIMD::f64x8 result = set1_f64x8(-0.0187293);
		result = fmadd_f64x8(result, in_abs, set1_f64x8(0.074261));
		result = fmsub_f64x8(result, in_abs, set1_f64x8(0.2121144));
		result = fmadd_f64x8(result, in_abs, set1_f64x8(1.5707288));

		EmuSIMD::f64x8 tmp = sub_f64x8(set1_f64x8(1.0), in_abs);
		tmp = mul_f64x8(sqrt_f64x8(tmp), result);
		result = set1_f64x8(3.14159265358979 * 0.5);
		result = sub_f64x8(result, tmp);

		tmp = mul_f64x8(negation_mult, result);
		return sub_f64x8(result, tmp);
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 atan2_f64x8(EmuSIMD::f64x8_arg y_, EmuSIMD::f64x8_arg x_)
	{
#if EMU_CORE_IS_INTEL_COMPILER && EMU_CORE_X86_X64 // Only tends to score better on Intel platforms
		return _mm512_atan2_pd(y_, x_);
#else		
		// Alternative manual approximation, based on https://developer.download.nvidia.com/cg/atan2.html implementation

		auto abs_x = abs_f64x8(x_);
		auto abs_y = abs_f64x8(y_);

		EmuSIMD::f64x8 temp0 = max_f64x8(abs_x, abs_y);
		EmuSIMD::f64x8 temp1 = min_f64x8(abs_x, abs_y);
		EmuSIMD::f64x8 temp2 = div_f64x8(set1_f64x8(1.0), temp0);
		temp2 = mul_f64x8(temp1, temp2);

		EmuSIMD::f64x8 t4 = mul_f64x8(temp2, temp2);
		temp0 = set1_f64x8(-0.013480470);
		temp0 = fmadd_f64x8(temp0, t4, set1_f64x8(0.057477314));
		temp0 = fmsub_f64x8(temp0, t4, set1_f64x8(0.121239071));
		temp0 = fmadd_f64x8(temp0, t4, set1_f64x8(0.195635925));
		temp0 = fmsub_f64x8(temp0, t4, set1_f64x8(0.332994597));
		temp0 = fmadd_f64x8(temp0, t4, set1_f64x8(0.999995630));
		temp2 = mul_f64x8(temp0, temp2);

		//t3 = (abs(y) > abs(x)) ? float(1.570796327) - t3 : t3;
		EmuSIMD::f64x8 cmp_mask = cmpgt_f64x8(abs_y, abs_x);
		temp0 = and_f64x8(cmp_mask, set1_f64x8(1.570796327));
		temp0 = sub_f64x8(temp0, temp2);
		temp2 = or_f64x8(andnot_f64x8(cmp_mask, temp2), and_f64x8(cmp_mask, temp0));

		// t3 = (x < 0) ?  float(3.141592654) - t3 : t3;
		EmuSIMD::f64x8 zero = setzero_f64x8();
		cmp_mask = cmplt_f64x8(x_, zero);
		temp0 = and_f64x8(cmp_mask, set1_f64x8(3.141592654));
		temp0 = sub_f64x8(temp0, temp2);
		temp2 = or_f64x8(andnot_f64x8(cmp_mask, temp2), and_f64x8(cmp_mask, temp0));

		//t3 = (y < 0) ? -t3 : t3;
		cmp_mask = cmplt_f64x8(y_, zero);
		temp0 = negate_f64x8(temp2);
		temp2 = or_f64x8(andnot_f64x8(cmp_mask, temp2), and_f64x8(cmp_mask, temp0));

		return temp2;
#endif
	}

	EMU_SIMD_COMMON_FUNC_SPEC EmuSIMD::f64x8 atan_f64x8(EmuSIMD::f64x8_arg in_)
	{
#if EMU_CORE_IS_INTEL_COMPILER && EMU_CORE_X86_X64 // Only tends to score better on Intel platforms
		return _mm512_atan_pd(in_);
#else
		// Alternative manual approximation, based on https://developer.download.nvidia.com/cg/atan2.html implementation with a constant x_ argument of 1
		EmuSIMD::f64x8 one = set1_f64x8(1.0);
		EmuSIMD::f64x8 abs_y = abs_f64x8(in_);

		//auto temp0 = _mm_max_ps(temp2, temp1);
		EmuSIMD::f64x8 cmp_mask = cmplt_f64x8(abs_y, one);
		EmuSIMD::f64x8 temp0 = or_f64x8(and_f64x8(cmp_mask, one), andnot_f64x8(cmp_mask, abs_y));
		EmuSIMD::f64x8 temp1 = or_f64x8(andnot_f64x8(cmp_mask, one), and_f64x8(cmp_mask, abs_y));
		EmuSIMD::f64x8 temp2 = div_f64x8(one, temp0);
		temp2 = mul_f64x8(temp1, temp2);

		EmuSIMD::f64x8 t4 = mul_f64x8(temp2, temp2);
		temp0 = set1_f64x8(-0.013480470);
		temp0 = fmadd_f64x8(temp0, t4, set1_f64x8(0.057477314));
		temp0 = fmsub_f64x8(temp0, t4, set1_f64x8(0.121239071));
		temp0 = fmadd_f64x8(temp0, t4, set1_f64x8(0.195635925));
		temp0 = fmsub_f64x8(temp0, t4, set1_f64x8(0.332994597));
		temp0 = fmadd_f64x8(temp0, t4, set1_f64x8(0.999995630));
		temp2 = mul_f64x8(temp0, temp2);

		//t3 = (abs(y) > abs(x)) ? float(1.570796327) - t3 : t3;
		cmp_mask = cmpgt_f64x8(abs_y, one);
		temp0 = and_f64x8(cmp_mask, set1_f64x8(1.570796327));
		temp0 = sub_f64x8(temp0, temp2);
		temp2 = or_f64x8(andnot_f64x8(cmp_mask, temp2), and_f64x8(cmp_mask, temp0));

		//t3 = (y < 0) ? -t3 : t3;
		cmp_mask = cmplt_f64x8(in_, setzero_f64x8());
		temp0 = negate_f64x8(temp2);
		temp2 = or_f64x8(andnot_f64x8(cmp_mask, temp2), and_f64x8(cmp_mask, temp0));

		return temp2;
#endif
	}
#pragma endregion
}

#endif
