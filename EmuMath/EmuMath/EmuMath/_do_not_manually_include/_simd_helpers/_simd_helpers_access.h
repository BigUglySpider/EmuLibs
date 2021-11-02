#ifndef EMU_MATH_SIMD_HELPERS_ACCESS_H_INC_
#define EMU_MATH_SIMD_HELPERS_ACCESS_H_INC_ 1

#include "_common_simd_helpers_includes.h"

namespace EmuMath::SIMD
{
	/// <summary>
	/// <para> Returns a copy of the element at the provided Index_ of the provided m128_ SIMD vector. </para>
	/// </summary>
	/// <param name="m128_">SIMD vector to access an index of.</param>
	/// <returns>Copy of the value at the provided index of the provided SIMD vector.</returns>
	template<std::size_t Index_>
	[[nodiscard]] float get_m128_index(__m128 m128_)
	{
		if constexpr (Index_ == 0)
		{
			return _mm_cvtss_f32(m128_);
		}
		else if constexpr (Index_ <= 3)
		{
			return _mm_cvtss_f32(shuffle<Index_, 1, 2, 3>(m128_));
		}
		else
		{
			static_assert(false, "Invalid index provided to get_m128_index template function. Only 0-3 (inclusive) are valid indices.");
			return 0.0f;
		}
	}
	/// <summary>
	/// <para> Returns a copy of the element at the provided index_ of the provided m128_ SIMD vector. </para>
	/// <para>
	///		This uses a conditional check due to requirements for constant expressions with some intrinsic functions. 
	///		If the provided index_ may be evaluated at compile time, it is highly recommended to provide it as a template argument instead to avoid the condition.
	/// </para>
	/// <para> If the provided index_ is invalid, a standard logic_error will be thrown. </para>
	/// </summary>
	/// <param name="m128_">SIMD vector to access an index of.</param>
	/// <param name="index_">Index of the provided SIMD vector to access.</param>
	/// <returns>Copy of the value at the provided index of the provided SIMD vector.</returns>
	[[nodiscard]] inline float get_m128_index(__m128 m128_, std::size_t index_)
	{
		switch (index_)
		{
			case 0:
				return get_m128_index<0>(m128_);
				break;
			case 1:
				return get_m128_index<1>(m128_);
				break;
			case 2:
				return get_m128_index<2>(m128_);
				break;
			case 3:
				return get_m128_index<3>(m128_);
				break;
			default:
				throw std::logic_error("Invalid index provided to get_m128_index template function. Only 0-3 (inclusive) are valid indices.");
				break;
		}
	}
}

#endif