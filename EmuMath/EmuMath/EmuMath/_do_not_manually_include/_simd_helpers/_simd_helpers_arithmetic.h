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

	[[nodiscard]] inline __m128 dot_product(__m128 a_, __m128 b_)
	{
		a_ = _mm_mul_ps(a_, b_);
		return EmuMath::SIMD::horizontal_vector_sum(a_);
	}
	[[nodiscard]] inline __m128 dot_product_fill(__m128 a_, __m128 b_)
	{
		a_ = _mm_mul_ps(a_, b_);
		return EmuMath::SIMD::horizontal_vector_sum_fill(a_);
	}
	[[nodiscard]] inline float dot_product_scalar(__m128 a_, __m128 b_)
	{
		a_ = _mm_mul_ps(a_, b_);
		a_ = EmuMath::SIMD::horizontal_vector_sum(a_);
		return _mm_cvtss_f32(a_);
	}

	[[nodiscard]]inline  __m128 vector_clamp(__m128 val_, __m128 min_, __m128 max_)
	{
		val_ = _mm_max_ps(val_, min_);
		return _mm_min_ps(val_, max_);
	}

	[[nodiscard]] inline __m128 vector_clamp_min(__m128 val_, __m128 min_)
	{
		return _mm_max_ps(val_, min_);
	}

	[[nodiscard]] inline __m128 vector_clamp_max(__m128 val_, __m128 max_)
	{
		return _mm_min_ps(val_, max_);
	}

	/// <summary> Finds the lowest value in the passed SIMD register and returns a register containing the lowest value in its x-component.. </summary>
	/// <param name="val_">SIMD vector to find the minimum value of.</param>
	/// <returns>__m128 register with the lowest value of the passed val_ register located in its x-component.</returns>
	[[nodiscard]]inline  __m128 vector_min_128(__m128 val_)
	{
		val_ = _mm_min_ps(val_, EmuMath::SIMD::shuffle<3, 2, 1, 0>(val_));
		return _mm_min_ps(val_, EmuMath::SIMD::shuffle<1, 0, 2, 3>(val_));
	}
	/// <summary> Finds the lowest value in the passed SIMD register and returns a register filled with just that value. </summary>
	/// <param name="val_">SIMD vector to find the minimum value of.</param>
	/// <returns>__m128 register with each component set to the lowest value of the passed val_.</returns>
	[[nodiscard]] inline __m128 vector_min_128_fill(__m128 val_)
	{
		return EmuMath::SIMD::shuffle<0, 0, 0, 0>(vector_min_128(val_));
	}
	/// <summary> Finds the lowest value in the passed SIMD register and returns it as a scalar. </summary>
	/// <param name="val_">SIMD vector to find the minimum value of.</param>
	/// <returns>Scalar copy of the lowest value in the passed SIMD vector.</returns>
	[[nodiscard]] inline float vector_min_scalar(__m128 val_)
	{
		return _mm_cvtss_f32(vector_min_128(val_));
	}

	/// <summary> Finds the highest value in the passed SIMD register and returns a register containing the highest value in its x-component.. </summary>
	/// <param name="val_">SIMD vector to find the maximum value of.</param>
	/// <returns>__m128 register with the highest value of the passed val_ register located in its x-component.</returns>
	[[nodiscard]] inline __m128 vector_max_128(__m128 val_)
	{
		val_ = _mm_max_ps(val_, EmuMath::SIMD::shuffle<3, 2, 1, 0>(val_));
		return _mm_max_ps(val_, EmuMath::SIMD::shuffle<1, 0, 2, 3>(val_));
	}
	/// <summary> Finds the highest value in the passed SIMD register and returns a register filled with just that value. </summary>
	/// <param name="val_">SIMD vector to find the maximum value of.</param>
	/// <returns>__m128 register with each component set to the highest value of the passed val_.</returns>
	[[nodiscard]] inline __m128 vector_max_128_fill(__m128 val_)
	{
		return EmuMath::SIMD::shuffle<0, 0, 0, 0>(vector_max_128(val_));
	}
	/// <summary> Finds the highest value in the passed SIMD register and returns it as a scalar. </summary>
	/// <param name="val_">SIMD vector to find the maximum value of.</param>
	/// <returns>Scalar copy of the highest value in the passed SIMD vector.</returns>
	[[nodiscard]] inline float vector_max_scalar(__m128 val_)
	{
		return _mm_cvtss_f32(vector_max_128(val_));
	}

	/// <summary> Negates the passed SIMD vector. </summary>
	/// <param name="val_">SIMD vector to negate.</param>
	/// <returns>Negated form of the passed SIMD vector, such that the output matrix can be summarised as { -val_[0], -val_[1], -val_[2], -val_[3] }.</returns>
	[[nodiscard]] inline __m128 vector_negate(__m128 val_)
	{
		return _mm_sub_ps(_mm_setzero_ps(), val_);
	}

	/// <summary> Multiplies lhs_mat_cm_ by rhs_mat_cm_ as though they are both contiguously column-major 2x2 matrices. </summary>
	/// <param name="lhs_mat_cm_">SIMD vector representing a contiguously column-major 2x2 matrix which appears on the left of a matrix multiplication.</param>
	/// <param name="rhs_mat_cm_">SIMD vector representing a contiguously column-major 2x2 matrix which appears on the right of a matrix multiplication.</param>
	/// <returns>SIMD vector representing the result of multiplying the passed matrices, represented as a contiguously column-major 2x2 matrix.</returns>
	[[nodiscard]] inline __m128 matrix_2x2_multiply_cm(__m128 lhs_mat_cm_, __m128 rhs_mat_cm_)
	{
		return _mm_add_ps
		(
			_mm_mul_ps(lhs_mat_cm_, EmuMath::SIMD::shuffle<0, 0, 3, 3>(rhs_mat_cm_)),
			_mm_mul_ps(EmuMath::SIMD::shuffle<2, 3, 0, 1>(lhs_mat_cm_), EmuMath::SIMD::shuffle<1, 1, 2, 2>(rhs_mat_cm_))
		);
	}
	/// <summary> Multiplies the adjugate of lhs_mat_cm_ by rhs_mat_cm_ as though they are both contiguously column-major 2x2 matrices. </summary>
	/// <param name="lhs_mat_cm_">SIMD vector representing a contiguously column-major 2x2 matrix whose adjugate appears on the left of a matrix multiplication.</param>
	/// <param name="rhs_mat_cm_">SIMD vector representing a contiguously column-major 2x2 matrix which appears on the right of a matrix multiplication.</param>
	/// <returns>
	///		SIMD vector representing the result of multiplying the adjugate of the passed lhs matrix by the passed rhs matrix, 
	///		represented as a contiguously column-major 2x2 matrix.
	/// </returns>
	[[nodiscard]] inline __m128 matrix_2x2_multiply_adj_norm_cm(__m128 lhs_mat_cm_, __m128 rhs_mat_cm_)
	{
		return _mm_sub_ps
		(
			_mm_mul_ps(EmuMath::SIMD::shuffle<3, 0, 3, 0>(lhs_mat_cm_), rhs_mat_cm_),
			_mm_mul_ps(EmuMath::SIMD::shuffle<2, 1, 2, 1>(lhs_mat_cm_), EmuMath::SIMD::shuffle<1, 0, 3, 2>(rhs_mat_cm_))
		);
	}
	/// <summary> Multiplies lhs_mat_cm_ by the adjugate of rhs_mat_cm_ as though they are both contiguously column-major 2x2 matrices. </summary>
	/// <param name="lhs_mat_cm_">SIMD vector representing a contiguously column-major 2x2 matrix which appears on the left of a matrix multiplication.</param>
	/// <param name="rhs_mat_cm_">SIMD vector representing a contiguously column-major 2x2 matrix whose adjugate appears on the right of a matrix multiplication.</param>
	/// <returns>
	///		SIMD vector representing the result of multiplying the passed lhs matrix by the adjugate of the passed rhs matrix, 
	///		represented as a contiguously column-major 2x2 matrix.
	/// </returns>
	[[nodiscard]] inline __m128 matrix_2x2_multiply_norm_adj_cm(__m128 lhs_mat_cm_, __m128 rhs_mat_cm_)
	{
		return _mm_sub_ps
		(
			_mm_mul_ps(lhs_mat_cm_, EmuMath::SIMD::shuffle<3, 3, 0, 0>(rhs_mat_cm_)),
			_mm_mul_ps(EmuMath::SIMD::shuffle<2, 3, 0, 1>(lhs_mat_cm_), EmuMath::SIMD::shuffle<1, 1, 2, 2>(rhs_mat_cm_))
		);
	}
}

#endif
