#ifndef EMU_MATH_SIMD_HELPERS_BITS_H_INC_
#define EMU_MATH_SIMD_HELPERS_BITS_H_INC_ 1

#include "_common_simd_helpers_includes.h"
#include "_simd_helpers_masks.h"

namespace EmuMath::SIMD
{
	[[nodiscard]] inline __m128 not_128(__m128 val_)
	{
		return _mm_andnot_ps(val_, index_mask_m128<true, true, true, true>());
	}
	[[nodiscard]] inline __m128d not_128d(__m128d val_)
	{
		return _mm_andnot_pd(val_, index_mask_m128d<true, true>());
	}
	[[nodiscard]] inline __m128i not_128i(__m128i val_)
	{
		return _mm_andnot_si128(val_, index_mask_m128i_64<true, true>());
	}
}

#endif
