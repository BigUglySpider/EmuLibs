#ifndef EMU_MATH_SIMD_HELPERS_ARITHMETIC_H_INC_
#define EMU_MATH_SIMD_HELPERS_ARITHMETIC_H_INC_ 1

#include "_common_simd_helpers_includes.h"

namespace EmuMath::SIMD
{
	/// <summary> Performs a horizontal add within the passed vector, storing the result in the output register's first component. </summary>
	/// <param name="a">SIMD vector to perform horizontal addition with.</param>
	/// <returns>SIMD vector containing the result of the horizontal add in its first component.</returns>
	[[nodiscard]] inline __m128 horizontal_vector_sum(__m128 a)
	{
		__m128 shuffled = _mm_shuffle_ps(a, a, _MM_SHUFFLE(2, 3, 0, 1));
		__m128 sums = _mm_add_ps(a, shuffled);
		shuffled = _mm_movehl_ps(shuffled, sums);
		return _mm_add_ss(sums, shuffled);
	}
	/// <summary> Performs a horizontal add within the passed vector, storing the result in every component of the output register. </summary>
	/// <param name="a">SIMD vector to perform horizontal addition with.</param>
	/// <returns>SIMD vector containing the result of the horizontal add in every component.</returns>
	[[nodiscard]] inline __m128 horizontal_vector_sum_fill(__m128 a)
	{
		__m128 result = _mm_hadd_ps(a, a);
		return _mm_hadd_ps(result, result);
	}
	/// <summary> Performs a horizontal add within the passed vector and returns the result as a scalar. </summary>
	/// <param name="a">SIMD vector to perform horizontal addition with.</param>
	/// <returns>Result of the horizontal addition as a scalar.</returns>
	[[nodiscard]] inline float horizontal_vector_sum_scalar(__m128 a)
	{
		return _mm_cvtss_f32(horizontal_vector_sum(a));
	}

	[[nodiscard]] __m128 dot_product(__m128 a_, __m128 b_)
	{
		a_ = _mm_mul_ps(a_, b_);
		return EmuMath::SIMD::horizontal_vector_sum(a_);
	}
	[[nodiscard]] __m128 dot_product_fill(__m128 a_, __m128 b_)
	{
		a_ = _mm_mul_ps(a_, b_);
		return EmuMath::SIMD::horizontal_vector_sum_fill(a_);
	}
	[[nodiscard]] float dot_product_scalar(__m128 a_, __m128 b_)
	{
		a_ = _mm_mul_ps(a_, b_);
		a_ = EmuMath::SIMD::horizontal_vector_sum(a_);
		return _mm_cvtss_f32(a_);
	}
}

#endif
