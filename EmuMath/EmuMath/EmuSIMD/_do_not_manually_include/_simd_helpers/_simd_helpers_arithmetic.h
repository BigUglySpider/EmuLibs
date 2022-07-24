#ifndef EMU_SIMD_HELPERS_ARITHMETIC_H_INC_
#define EMU_SIMD_HELPERS_ARITHMETIC_H_INC_ 1

#include "_common_simd_helpers_includes.h"

namespace EmuSIMD
{
	/// <summary> Finds the lowest value in the passed SIMD register and returns a register containing the lowest value in its x-component.. </summary>
	/// <param name="val_">SIMD vector to find the minimum value of.</param>
	/// <returns>EmuSIMD::f32x4 register with the lowest value of the passed val_ register located in its x-component.</returns>
	[[nodiscard]]inline  EmuSIMD::f32x4 vector_min_128(EmuSIMD::f32x4 val_)
	{
		val_ = _mm_min_ps(val_, EmuSIMD::shuffle<3, 2, 1, 0>(val_));
		return _mm_min_ps(val_, EmuSIMD::shuffle<1, 0, 2, 3>(val_));
	}
	/// <summary> Finds the lowest value in the passed SIMD register and returns a register filled with just that value. </summary>
	/// <param name="val_">SIMD vector to find the minimum value of.</param>
	/// <returns>EmuSIMD::f32x4 register with each component set to the lowest value of the passed val_.</returns>
	[[nodiscard]] inline EmuSIMD::f32x4 vector_min_128_fill(EmuSIMD::f32x4 val_)
	{
		return EmuSIMD::shuffle<0, 0, 0, 0>(vector_min_128(val_));
	}
	/// <summary> Finds the lowest value in the passed SIMD register and returns it as a scalar. </summary>
	/// <param name="val_">SIMD vector to find the minimum value of.</param>
	/// <returns>Scalar copy of the lowest value in the passed SIMD vector.</returns>
	[[nodiscard]] inline float vector_min_scalar(EmuSIMD::f32x4 val_)
	{
		return _mm_cvtss_f32(vector_min_128(val_));
	}

	/// <summary> Finds the highest value in the passed SIMD register and returns a register containing the highest value in its x-component.. </summary>
	/// <param name="val_">SIMD vector to find the maximum value of.</param>
	/// <returns>EmuSIMD::f32x4 register with the highest value of the passed val_ register located in its x-component.</returns>
	[[nodiscard]] inline EmuSIMD::f32x4 vector_max_128(EmuSIMD::f32x4 val_)
	{
		val_ = _mm_max_ps(val_, EmuSIMD::shuffle<3, 2, 1, 0>(val_));
		return _mm_max_ps(val_, EmuSIMD::shuffle<1, 0, 2, 3>(val_));
	}
	/// <summary> Finds the highest value in the passed SIMD register and returns a register filled with just that value. </summary>
	/// <param name="val_">SIMD vector to find the maximum value of.</param>
	/// <returns>EmuSIMD::f32x4 register with each component set to the highest value of the passed val_.</returns>
	[[nodiscard]] inline EmuSIMD::f32x4 vector_max_128_fill(EmuSIMD::f32x4 val_)
	{
		return EmuSIMD::shuffle<0, 0, 0, 0>(vector_max_128(val_));
	}
	/// <summary> Finds the highest value in the passed SIMD register and returns it as a scalar. </summary>
	/// <param name="val_">SIMD vector to find the maximum value of.</param>
	/// <returns>Scalar copy of the highest value in the passed SIMD vector.</returns>
	[[nodiscard]] inline float vector_max_scalar(EmuSIMD::f32x4 val_)
	{
		return _mm_cvtss_f32(vector_max_128(val_));
	}

	/// <summary> Multiplies lhs_mat_cm_ by rhs_mat_cm_ as though they are both contiguously column-major 2x2 matrices. </summary>
	/// <param name="lhs_mat_cm_">SIMD vector representing a contiguously column-major 2x2 matrix which appears on the left of a matrix multiplication.</param>
	/// <param name="rhs_mat_cm_">SIMD vector representing a contiguously column-major 2x2 matrix which appears on the right of a matrix multiplication.</param>
	/// <returns>SIMD vector representing the result of multiplying the passed matrices, represented as a contiguously column-major 2x2 matrix.</returns>
	[[nodiscard]] inline EmuSIMD::f32x4 matrix_2x2_multiply_cm(EmuSIMD::f32x4 lhs_mat_cm_, EmuSIMD::f32x4 rhs_mat_cm_)
	{
		return _mm_add_ps
		(
			_mm_mul_ps(lhs_mat_cm_, EmuSIMD::shuffle<0, 0, 3, 3>(rhs_mat_cm_)),
			_mm_mul_ps(EmuSIMD::shuffle<2, 3, 0, 1>(lhs_mat_cm_), EmuSIMD::shuffle<1, 1, 2, 2>(rhs_mat_cm_))
		);
	}
	/// <summary> Multiplies the adjugate of lhs_mat_cm_ by rhs_mat_cm_ as though they are both contiguously column-major 2x2 matrices. </summary>
	/// <param name="lhs_mat_cm_">SIMD vector representing a contiguously column-major 2x2 matrix whose adjugate appears on the left of a matrix multiplication.</param>
	/// <param name="rhs_mat_cm_">SIMD vector representing a contiguously column-major 2x2 matrix which appears on the right of a matrix multiplication.</param>
	/// <returns>
	///		SIMD vector representing the result of multiplying the adjugate of the passed lhs matrix by the passed rhs matrix, 
	///		represented as a contiguously column-major 2x2 matrix.
	/// </returns>
	[[nodiscard]] inline EmuSIMD::f32x4 matrix_2x2_multiply_adj_norm_cm(EmuSIMD::f32x4 lhs_mat_cm_, EmuSIMD::f32x4 rhs_mat_cm_)
	{
		return _mm_sub_ps
		(
			_mm_mul_ps(EmuSIMD::shuffle<3, 0, 3, 0>(lhs_mat_cm_), rhs_mat_cm_),
			_mm_mul_ps(EmuSIMD::shuffle<2, 1, 2, 1>(lhs_mat_cm_), EmuSIMD::shuffle<1, 0, 3, 2>(rhs_mat_cm_))
		);
	}
	/// <summary> Multiplies lhs_mat_cm_ by the adjugate of rhs_mat_cm_ as though they are both contiguously column-major 2x2 matrices. </summary>
	/// <param name="lhs_mat_cm_">SIMD vector representing a contiguously column-major 2x2 matrix which appears on the left of a matrix multiplication.</param>
	/// <param name="rhs_mat_cm_">SIMD vector representing a contiguously column-major 2x2 matrix whose adjugate appears on the right of a matrix multiplication.</param>
	/// <returns>
	///		SIMD vector representing the result of multiplying the passed lhs matrix by the adjugate of the passed rhs matrix, 
	///		represented as a contiguously column-major 2x2 matrix.
	/// </returns>
	[[nodiscard]] inline EmuSIMD::f32x4 matrix_2x2_multiply_norm_adj_cm(EmuSIMD::f32x4 lhs_mat_cm_, EmuSIMD::f32x4 rhs_mat_cm_)
	{
		return _mm_sub_ps
		(
			_mm_mul_ps(lhs_mat_cm_, EmuSIMD::shuffle<3, 3, 0, 0>(rhs_mat_cm_)),
			_mm_mul_ps(EmuSIMD::shuffle<2, 3, 0, 1>(lhs_mat_cm_), EmuSIMD::shuffle<1, 1, 2, 2>(rhs_mat_cm_))
		);
	}
}

#endif
