#ifndef EMU_MATH_SIMD_HELPERS_MASKS_H_INC_
#define EMU_MATH_SIMD_HELPERS_MASKS_H_INC_

#include "_common_simd_helpers_includes.h"

namespace EmuMath::SIMD
{
	/// <summary> Compile-time executable function to generate an expected move mask for the provided comparison results for respective elements. </summary>
	/// <param name="x_">Whether the resultant x-bit should be true or false.</param>
	/// <param name="y_">Whether the resultant y-bit should be true or false.</param>
	/// <param name="z_">Whether the resultant z-bit should be true or false.</param>
	/// <param name="w_">Whether the resultant w-bit should be true or false.</param>
	/// <returns>4-bit move mask expected to result from _mm_movemask_ps after a comparison if it has the provided results.</returns>
	[[nodiscard]] constexpr int generate_move_mask(bool x_, bool y_, bool z_, bool w_)
	{
		return (static_cast<int>(w_) << 3) | (static_cast<int>(z_) << 2) | (static_cast<int>(y_) << 1) | static_cast<int>(x_);
	}
	/// <summary> Variant of generate_move_mask which takes template boolean arguments to guarantee compile-time execution. </summary>
	/// <returns>4-bit move mask expected to result from _mm_movemask_ps after a comparison if it has the provided results.</returns>
	template<bool X_, bool Y_, bool Z_, bool W_>
	[[nodiscard]] constexpr int generate_move_mask()
	{
		return generate_move_mask(X_, Y_, Z_, W_);
	}
	/// <summary> Shorthand for calling generate_move_mask with the same template arguments. </summary>
	template<bool X_, bool Y_, bool Z_, bool W_>
	constexpr int move_mask_v = generate_move_mask<X_, Y_, Z_, W_>();
}

#endif
