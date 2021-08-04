#ifndef EMU_MATH_SIMD_HELPERS_H_INC_
#define EMU_MATH_SIMD_HELPERS_H_INC_

#include <cstdlib>
#include <exception>
#include <immintrin.h>

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
	__m128 shuffle(const __m128 a, const __m128 b)
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
	__m128 shuffle(const __m128 ab)
	{
		return _mm_shuffle_ps(ab, ab, shuffle_arg_v<X_, Y_, Z_, W_>);
	}

	/// <summary>
	/// <para> Returns a copy of the element at the provided Index_ of the provided m128_ SIMD vector. </para>
	/// </summary>
	/// <param name="m128_">SIMD vector to access an index of.</param>
	/// <returns>Copy of the value at the provided index of the provided SIMD vector.</returns>
	template<std::size_t Index_>
	float get_m128_index(__m128 m128_)
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
	inline float get_m128_index(__m128 m128_, std::size_t index_)
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

	/// <summary> Performs a horizontal add within the passed vector, storing the result in the output register's first component. </summary>
	/// <param name="a">SIMD vector to perform horizontal addition with.</param>
	/// <returns>SIMD vector containing the result of the horizontal add in its first component.</returns>
	inline __m128 horizontal_vector_sum(__m128 a)
	{
		__m128 shuffled = _mm_shuffle_ps(a, a, _MM_SHUFFLE(2, 3, 0, 1));
		__m128 sums = _mm_add_ps(a, shuffled);
		shuffled = _mm_movehl_ps(shuffled, sums);
		return _mm_add_ss(sums, shuffled);
	}
	/// <summary> Performs a horizontal add within the passed vector, storing the result in every component of the output register. </summary>
	/// <param name="a">SIMD vector to perform horizontal addition with.</param>
	/// <returns>SIMD vector containing the result of the horizontal add in every component.</returns>
	inline __m128 horizontal_vector_sum_fill(__m128 a)
	{
		__m128 result = _mm_hadd_ps(a, a);
		return _mm_hadd_ps(a, a);
	}
	/// <summary> Performs a horizontal add within the passed vector and returns the result as a scalar. </summary>
	/// <param name="a">SIMD vector to perform horizontal addition with.</param>
	/// <returns>Result of the horizontal addition as a scalar.</returns>
	inline float horizontal_vector_sum_scalar(__m128 a)
	{
		return _mm_cvtss_f32(horizontal_vector_sum(a));
	}
}

#endif
