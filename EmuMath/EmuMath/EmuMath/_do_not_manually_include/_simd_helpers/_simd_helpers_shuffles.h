#ifndef EMU_MATH_SIMD_HELPERS_SHUFFLES_H_INC_
#define EMU_MATH_SIMD_HELPERS_SHUFFLES_H_INC_ 1

#include "_common_simd_helpers_includes.h"

namespace EmuMath::SIMD
{
	/// <summary>
	/// <para> Creates a compile-time shuffle argument for a call to _mm_shuffle_ps, where X_ is the first item in memory and W_ is the last contiguous item in memory. </para>
	/// <para> X_ and Y_ correlate to indices in argument a of a shuffle, Z_ and W_ correlate to indices in argument b of a shuffle. </para>
	/// <para> As such, the result of a shuffle with this argument would be { a[X_}, a[Y_], b[Z_], b[W_] }. </para>
	/// </summary>
	template<std::size_t X_, std::size_t Y_, std::size_t Z_, std::size_t W_>
	struct shuffle_arg
	{
		static_assert(X_ <= 3 && Y_ <= 3 && Z_ <= 3 && W_ <= 3, "Provided a shuffle argument parameter which does not match any index for a 4-dimensional SIMD vector.");
		constexpr static unsigned int value = ((W_ << 6) | (Z_ << 4) | (Y_ << 2) | X_);
	};
	/// <summary> Compile-time shuffle argument for a call to _mm_shuffle_ps, where X_ is the first item in memory and W_ is the last contiguous item in memory. </summary>
	template<std::size_t X_, std::size_t Y_, std::size_t Z_, std::size_t W_>
	constexpr unsigned int shuffle_arg_v = shuffle_arg<X_, Y_, Z_, W_>::value;

	/// <summary>
	///	<para> Returns the result of a SIMD shuffle with the provided 2 operands, using the value of shuffle_arg with the passed template params as the third argument. </para>
	/// <para> The resulting SIMD vector will be { a[X_}, a[Y_], b[Z_], b[W_] }. </para>
	/// </summary>
	/// <param name="a">Left-hand SIMD vector, accessed with the X_ and Y_ template arguments. </param>
	/// <param name="b">Right-hand SIMD vector, accessed with the Z_ and W_ template arguments.</param>
	/// <returns>Result of shuffling the passed two SIMD vectors based on the provided template arguments.</returns>
	template<std::size_t X_, std::size_t Y_, std::size_t Z_, std::size_t W_>
	[[nodiscard]] inline __m128 shuffle(const __m128 a, const __m128 b)
	{
		return _mm_shuffle_ps(a, b, shuffle_arg_v<X_, Y_, Z_, W_>);
	}
	/// <summary>
	/// <para> Returns a SIMD vector shuffled with indices correlating to the provided arguments. </para>
	/// <para> X_ through W_ refer to indices in order in the resultant vector, and take values from the indices of the passed vector ab. </para>
	/// <para> The resulting SIMD vector will be { ab[X_], ab[Y_], ab[Z_], ab[W_] }. </para>
	/// </summary>
	/// <param name="ab">SIMD vector to return a shuffled variant of. Used as both vector arguments in a call to _mm_shuffle_ps.</param>
	/// <returns>Shuffled variant of the passed SIMD vector, using the passed template arguments to identify indices for the output vector.	</returns>
	template<std::size_t X_, std::size_t Y_, std::size_t Z_, std::size_t W_>
	[[nodiscard]] inline __m128 shuffle(const __m128 ab)
	{
		return _mm_shuffle_ps(ab, ab, shuffle_arg_v<X_, Y_, Z_, W_>);
	}
	/// <summary>
	/// <para> Returns a SIMD vector shuffled so that all indices correlate to the provided index within the passed vector. </para>
	/// <para> The resulting SIMD vector will be { ab[Index_], ab[Index_], ab[Index_], ab[Index_] }. </para>
	/// </summary>
	/// <param name="ab">SIMD vector to perform the shuffle on.</param>
	/// <returns>Passed SIMD vector shuffled so that all elements match the provided index.</returns>
	template<std::size_t Index_>
	[[nodiscard]] inline __m128 shuffle(__m128 ab)
	{
		return _mm_shuffle_ps(ab, ab, shuffle_arg_v<Index_, Index_, Index_, Index_>);
	}

	template<>
	[[nodiscard]] inline __m128 shuffle<0, 0, 2, 2>(__m128 ab)
	{
		return _mm_moveldup_ps(ab);
	}
	
	template<>
	[[nodiscard]] inline __m128 shuffle<1, 1, 3, 3>(__m128 ab)
	{
		return _mm_movehdup_ps(ab);
	}

	template<>
	[[nodiscard]] inline __m128 shuffle<0, 1, 0, 1>(__m128 a, __m128 b)
	{
		return _mm_movelh_ps(a, b);
	}
	template<>
	[[nodiscard]] inline __m128 shuffle<0, 1, 0, 1>(__m128 ab)
	{
		return _mm_movelh_ps(ab, ab);
	}

	template<>
	[[nodiscard]] inline __m128 shuffle<2, 3, 2, 3>(__m128 a, __m128 b)
	{
		return _mm_movehl_ps(b, a);
	}
	template<>
	[[nodiscard]] inline __m128 shuffle<2, 3, 2, 3>(__m128 ab)
	{
		return _mm_movehl_ps(ab, ab);
	}
}

#endif
