#ifndef EMU_MATH_SIMD_HELPERS_H_INC_
#define EMU_MATH_SIMD_HELPERS_H_INC_ 1

#include "../EmuCore/ArithmeticHelpers/BitHelpers.h"
#include <cstdlib>
#include <immintrin.h>
#include <stdexcept>

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
	/// <para> Provides the mask for the provided index within an __m128i 8-bit register. </para>
	/// </summary>
	/// <returns>__m128i register which acts as a mask for the provided index within said register types.</returns>
	template<std::size_t Index_>
	inline __m128i index_mask_m128i_8()
	{
		// Switch constexpr would sure be nice...
		if constexpr (Index_ == 0)
		{
			return _mm_set_epi8(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0xFF);
		}
		else if constexpr (Index_ == 1)
		{
			return _mm_set_epi8(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0xFF, 0);
		}
		else if constexpr (Index_ == 2)
		{
			return _mm_set_epi8(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0xFF, 0, 0);
		}
		else if constexpr (Index_ == 3)
		{
			return _mm_set_epi8(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0xFF, 0, 0, 0);
		}
		else if constexpr (Index_ == 4)
		{
			return _mm_set_epi8(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0xFF, 0, 0, 0, 0);
		}
		else if constexpr (Index_ == 5)
		{
			return _mm_set_epi8(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0xFF, 0, 0, 0, 0, 0);
		}
		else if constexpr (Index_ == 6)
		{
			return _mm_set_epi8(0, 0, 0, 0, 0, 0, 0, 0, 0, 0xFF, 0, 0, 0, 0, 0, 0);
		}
		else if constexpr (Index_ == 7)
		{
			return _mm_set_epi8(0, 0, 0, 0, 0, 0, 0, 0, 0xFF, 0, 0, 0, 0, 0, 0, 0);
		}
		else if constexpr (Index_ == 8)
		{
			return _mm_set_epi8(0, 0, 0, 0, 0, 0, 0, 0xFF, 0, 0, 0, 0, 0, 0, 0, 0);
		}
		else if constexpr (Index_ == 9)
		{
			return _mm_set_epi8(0, 0, 0, 0, 0, 0, 0xFF, 0, 0, 0, 0, 0, 0, 0, 0, 0);
		}
		else if constexpr (Index_ == 10)
		{
			return _mm_set_epi8(0, 0, 0, 0, 0, 0xFF, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
		}
		else if constexpr (Index_ == 11)
		{
			return _mm_set_epi8(0, 0, 0, 0, 0xFF, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
		}
		else if constexpr (Index_ == 12)
		{
			return _mm_set_epi8(0, 0, 0, 0xFF, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
		}
		else if constexpr (Index_ == 13)
		{
			return _mm_set_epi8(0, 0, 0xFF, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
		}
		else if constexpr (Index_ == 14)
		{
			return _mm_set_epi8(0, 0xFF, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
		}
		else if constexpr (Index_ == 15)
		{
			return _mm_set_epi8(0xFF, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
		}
		else
		{
			static_assert(false, "Attempted to retrieve a mask for an invalid index within an __m128i 8-bit register.");
		}
	}
	template<bool i0_, bool i1_, bool i2_, bool i3_, bool i4_, bool i5_, bool i6_, bool i7_, bool i8_, bool i9_, bool i10_, bool i11_, bool i12_, bool i13_, bool i14_, bool i15_>
	inline __m128i index_mask_m128i_8()
	{
		return _mm_set_epi8
		(
			0xFF * i15_,
			0xFF * i14_,
			0xFF * i13_,
			0xFF * i12_,
			0xFF * i11_,
			0xFF * i10_,
			0xFF * i9_,
			0xFF * i8_,
			0xFF * i7_,
			0xFF * i6_,
			0xFF * i5_,
			0xFF * i4_,
			0xFF * i3_,
			0xFF * i2_,
			0xFF * i1_,
			0xFF * i0_
		);
	}
	/// <summary>
	/// <para> Provides the mask for the provided index within an __m128i 16-bit register. </para>
	/// </summary>
	/// <returns>__m128i register which acts as a mask for the provided index within said register types.</returns>
	template<std::size_t Index_>
	inline __m128i index_mask_m128i_16()
	{
		if constexpr (Index_ == 0)
		{
			return _mm_set_epi16(0, 0, 0, 0, 0, 0, 0, 0xFFFF);
		}
		else if constexpr (Index_ == 1)
		{
			return _mm_set_epi16(0, 0, 0, 0, 0, 0, 0xFFFF, 0);
		}
		else if constexpr (Index_ == 2)
		{
			return _mm_set_epi16(0, 0, 0, 0, 0, 0xFFFF, 0, 0);
		}
		else if constexpr (Index_ == 3)
		{
			return _mm_set_epi16(0, 0, 0, 0, 0xFFFF, 0, 0, 0);
		}
		else if constexpr (Index_ == 4)
		{
			return _mm_set_epi16(0, 0, 0, 0xFFFF0, 0, 0, 0, 0);
		}
		else if constexpr (Index_ == 5)
		{
			return _mm_set_epi16(0, 0, 0xFFFF, 0, 0, 0, 0, 0);
		}
		else if constexpr (Index_ == 6)
		{
			return _mm_set_epi16(0, 0xFFFF, 0, 0, 0, 0, 0, 0);
		}
		else if constexpr (Index_ == 7)
		{
			return _mm_set_epi16(0xFFFF, 0, 0, 0, 0, 0, 0, 0);
		}
		else
		{
			static_assert(false, "Attempted to retrieve a mask for an invalid index within an __m128i 16-bit register.");
		}
	}
	template<bool i0_, bool i1_, bool i2_, bool i3_, bool i4_, bool i5_, bool i6_, bool i7_>
	inline __m128 index_mask_m128i_16()
	{
		return _mm_set_epi16(0xFFFF * i7_, 0xFFFF * i6_, 0xFFFF * i5_, 0xFFFF * i4_, 0xFFFF * i3_, 0xFFFF * i2_, 0xFFFF * i1_, 0xFFFF * i0_);
	}

	/// <summary>
	/// <para> Provides the mask for the provided index within an __m128i 32-bit register. </para>
	/// </summary>
	/// <returns>__m128i register which acts as a mask for the provided index within said register types.</returns>
	template<std::size_t Index_>
	inline __m128i index_mask_m128i_32()
	{
		if constexpr (Index_ == 0)
		{
			return _mm_set_epi32(0, 0, 0, 0xFFFFFFFF);
		}
		else if constexpr (Index_ == 1)
		{
			return _mm_set_epi32(0, 0, 0xFFFFFFFF, 0);
		}
		else if constexpr (Index_ == 2)
		{
			return _mm_set_epi32(0, 0xFFFFFFFF, 0, 0);
		}
		else if constexpr (Index_ == 3)
		{
			return _mm_set_epi32(0xFFFFFFFF, 0, 0, 0);
		}
		else
		{
			static_assert(false, "Attempted to retrieve a mask for an invalid index within an __m128i 32-bit register.");
		}
	}
	template<bool i0_, bool i1_, bool i2_, bool i3_>
	inline __m128i index_mask_m128i_32()
	{
		return _mm_set_epi32(0xFFFFFFFF * i3_, 0xFFFFFFFF * i2_, 0xFFFFFFFF * i1_, 0xFFFFFFFF * i0_);
	}

	/// <summary>
	/// <para> Provides the mask for the provided index within an __m128i 64-bit register. </para>
	/// </summary>
	/// <returns>__m128i register which acts as a mask for the provided index within said register types.</returns>
	template<std::size_t Index_>
	inline __m128i index_mask_m128i_64()
	{
		if constexpr (Index_ == 0)
		{
			return _mm_set_epi64x(0, 0xFFFFFFFFFFFFFFFF);
		}
		else if constexpr (Index_ == 1)
		{
			return _mm_set_epi64x(0xFFFFFFFFFFFFFFFF, 0);
		}
		else
		{
			static_assert(false, "Attempted to retrieve a mask for an invalid index within an __m128i 64-bit register.");
		}
	}
	template<bool i0_, bool i1_>
	inline __m128i index_mask_m128i_64()
	{
		return _mm_set_epi64x(0xFFFFFFFFFFFFFFFF * i1_, 0xFFFFFFFFFFFFFFFF * i0_);
	}

	/// <summary>
	/// <para> Provides the mask for the provided index within an __m128i register, where each element is considered to contain NumBits_ bits. </para>
	/// <para> Valid values for NumBits_ are: 8, 16, 32, 64. Anything else will result in a static assertion being triggered. </para>
	/// </summary>
	/// <returns></returns>
	template<std::size_t Index_, std::size_t NumBits_>
	inline __m128i index_mask_m128i()
	{
		if constexpr (NumBits_ == 8)
		{
			return index_mask_m128i_8<Index_>();
		}
		else if constexpr (NumBits_ == 16)
		{
			return index_mask_m128i_16<Index_>();
		}
		else if constexpr (NumBits_ == 32)
		{
			return index_mask_m128i_32<Index_>();
		}
		else if constexpr (NumBits_ == 64)
		{
			return index_mask_m128i_64<Index_>();
		}
		else
		{
			static_assert(false, "Attempted to retreieve a mask for an __m128i register with an invalid number of bits per element. The only valid numbers of bits are 8, 16, 32, and 64.");
		}
	}

	/// <summary>
	/// <para> Provides the mask for the provided index within an __m128 register. </para>
	/// </summary>
	/// <returns>__m128 register which acts as a mask for the provided index within said register types.</returns>
	template<std::size_t Index_>
	inline __m128 index_mask_m128()
	{
		if constexpr (Index_ <= 3)
		{
			__m128i mask_ = index_mask_m128i_32<Index_>();
			return *reinterpret_cast<__m128*>(&mask_);
		}
		else
		{
			static_assert(false, "Attempted to retrieve a mask for an invalid index within an __m128 register.");
		}
	}
	template<bool i0_, bool i1_, bool i2_, bool i3_>
	inline __m128 index_mask_m128()
	{
		__m128i mask_ = index_mask_m128i_32<i0_, i1_, i2_, i3_>();
		return *reinterpret_cast<__m128*>(&mask_);
	}

	template<std::size_t Index_>
	inline __m128d index_mask_m128d()
	{
		if constexpr (Index_ <= 1)
		{
			__m128i mask_ = index_mask_m128i_64<Index_>();
			return *reinterpret_cast<__m128d*>(&mask_);
		}
		else
		{
			static_assert(false, "Attempted to retrieve a mask for an invalid index within an __m128d reigster.");
		}
	}
	template<bool i0_, bool i1_>
	inline __m128d index_mask_m128d()
	{
		__m128i mask_ = index_mask_m128i_64<i0_, i1_>();
		return *reinterpret_cast<__m128d*>(&mask_);
	}

	/// <summary>
	/// <para> Provides the mask for a provided index for a provided SIMD RegisterType_. Useful for when a type of register may not be known. </para>
	/// <para>
	///		NOTE: The NumBits_ argument is only used if an integer register is being passed, and is used to determine the number of bits that each element consumes. 
	///		It defaults to 32-bit integers, but may be 8-, 16-, 32-, or 64-bit integers. If a non-integer register type is provided, this value may be anything.
	/// </para>
	/// </summary>
	/// <typeparam name="RegisterType_">Type of SIMD register intrinsic type to return an index mask for.</typeparam>
	/// <returns>Mask for the provided index when used with the provided register type.</returns>
	template<typename RegisterType_, std::size_t Index_, std::size_t NumBits_>
	inline RegisterType_ index_mask()
	{
		using unqualified_ = std::remove_cv_t<std::remove_reference_t<RegisterType_>>;
		if constexpr (std::is_same_v<unqualified_, __m128>)
		{
			return index_mask_m128<Index_>();
		}
		else if constexpr (std::is_same_v<unqualified_, __m128i>)
		{
			return index_mask_m128i<Index_, NumBits_>();
		}
		else
		{
			static_assert(false, "Provided an unsupported register type when attempting to get a register index mask via index_mask_t.");
		}
	}

	/// <summary> Compile-time executable function to generate an expected move mask for the provided comparison results for respective elements. </summary>
	/// <param name="x_">Whether the resultant x-bit should be true or false.</param>
	/// <param name="y_">Whether the resultant y-bit should be true or false.</param>
	/// <param name="z_">Whether the resultant z-bit should be true or false.</param>
	/// <param name="w_">Whether the resultant w-bit should be true or false.</param>
	/// <returns>4-bit move mask expected to result from _mm_movemask_ps after a comparison if it has the provided results.</returns>
	constexpr int generate_move_mask(bool x_, bool y_, bool z_, bool w_)
	{
		return (static_cast<int>(w_) << 3) | (static_cast<int>(z_) << 2) | (static_cast<int>(y_) << 1) | static_cast<int>(x_);
	}
	/// <summary> Variant of generate_move_mask which takes template boolean arguments to guarantee compile-time execution. </summary>
	/// <returns>4-bit move mask expected to result from _mm_movemask_ps after a comparison if it has the provided results.</returns>
	template<bool X_, bool Y_, bool Z_, bool W_>
	constexpr int generate_move_mask()
	{
		return generate_move_mask(X_, Y_, Z_, W_);
	}
	/// <summary> Shorthand for calling generate_move_mask with the same template arguments. </summary>
	template<bool X_, bool Y_, bool Z_, bool W_>
	constexpr int move_mask_v = generate_move_mask<X_, Y_, Z_, W_>();

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
		return _mm_hadd_ps(result, result);
	}
	/// <summary> Performs a horizontal add within the passed vector and returns the result as a scalar. </summary>
	/// <param name="a">SIMD vector to perform horizontal addition with.</param>
	/// <returns>Result of the horizontal addition as a scalar.</returns>
	inline float horizontal_vector_sum_scalar(__m128 a)
	{
		return _mm_cvtss_f32(horizontal_vector_sum(a));
	}

#pragma region MASK_COMPARISONS
	/// <summary> Performs an equality comparison of respective elements of the two passed SIMD vectors and returns the resultant 4-bit move mask. </summary>
	/// <param name="lhs">Left-hand argument of the comparison.</param>
	/// <param name="rhs">Right-hand argument of the comparison.</param>
	/// <returns>4-bit move mask resulting from the comparison. Each individual bit starting from the least-significant represents an element's comparison result.</returns>
	inline int mask_equal(__m128 lhs, __m128 rhs)
	{
		__m128 result = _mm_cmpeq_ps(lhs, rhs);
		return _mm_movemask_ps(result);
	}
	/// <summary> Performs an inequality comparison of respective elements of the two passed SIMD vectors and returns the resultant 4-bit move mask. </summary>
	/// <param name="lhs">Left-hand argument of the comparison.</param>
	/// <param name="rhs">Right-hand argument of the comparison.</param>
	/// <returns>4-bit move mask resulting from the comparison. Each individual bit starting from the least-significant represents an element's comparison result.</returns>
	inline int mask_not_equal(__m128 lhs, __m128 rhs)
	{
		__m128 result = _mm_cmpneq_ps(lhs, rhs);
		return _mm_movemask_ps(result);
	}
	/// <summary> Performs a less-than comparison of respective elements of the two passed SIMD vectors and returns the resultant 4-bit move mask. </summary>
	/// <param name="lhs">Left-hand argument of the comparison.</param>
	/// <param name="rhs">Right-hand argument of the comparison.</param>
	/// <returns>4-bit move mask resulting from the comparison. Each individual bit starting from the least-significant represents an element's comparison result.</returns>
	inline int mask_less_than(__m128 lhs, __m128 rhs)
	{
		__m128 result = _mm_cmplt_ps(lhs, rhs);
		return _mm_movemask_ps(result);
	}
	/// <summary> Performs a greater-than comparison of respective elements of the two passed SIMD vectors and returns the resultant 4-bit move mask. </summary>
	/// <param name="lhs">Left-hand argument of the comparison.</param>
	/// <param name="rhs">Right-hand argument of the comparison.</param>
	/// <returns>4-bit move mask resulting from the comparison. Each individual bit starting from the least-significant represents an element's comparison result.</returns>
	inline int mask_greater_than(__m128 lhs, __m128 rhs)
	{
		__m128 result = _mm_cmpgt_ps(lhs, rhs);
		return _mm_movemask_ps(result);
	}
	/// <summary> Performs a less-or-equal comparison of respective elements of the two passed SIMD vectors and returns the resultant 4-bit move mask. </summary>
	/// <param name="lhs">Left-hand argument of the comparison.</param>
	/// <param name="rhs">Right-hand argument of the comparison.</param>
	/// <returns>4-bit move mask resulting from the comparison. Each individual bit starting from the least-significant represents an element's comparison result.</returns>
	inline int mask_less_equal(__m128 lhs, __m128 rhs)
	{
		__m128 result = _mm_cmple_ps(lhs, rhs);
		return _mm_movemask_ps(result);
	}
	/// <summary> Performs a greater-or-equal comparison of respective elements of the two passed SIMD vectors and returns the resultant 4-bit move mask. </summary>
	/// <param name="lhs">Left-hand argument of the comparison.</param>
	/// <param name="rhs">Right-hand argument of the comparison.</param>
	/// <returns>4-bit move mask resulting from the comparison. Each individual bit starting from the least-significant represents an element's comparison result.</returns>
	inline int mask_greater_equal(__m128 lhs, __m128 rhs)
	{
		__m128 result = _mm_cmpge_ps(lhs, rhs);
		return _mm_movemask_ps(result);
	}
#pragma endregion

#pragma region ALL_COMPARISONS
	/// <summary>
	/// <para> Compares the equality of respective elements of the two passed SIMD vectors. </para>
	/// <para> The output of this function will be true if the respective template arguments match the results of the comparison. Otherwise, it will be false. </para>
	/// </summary>
	/// <param name="lhs">Left-hand argument of the comparison.</param>
	/// <param name="rhs">Right-hand argument of the comparison.</param>
	/// <returns>Boolean indicating if the result of an equality comparison with the provided vectors matches all provided template arguments for respective elements.</returns>
	template<bool X_ = true, bool Y_ = true, bool Z_ = true, bool W_ = true>
	inline bool all_equal(__m128 lhs, __m128 rhs)
	{
		return mask_equal(lhs, rhs) == move_mask_v<X_, Y_, Z_, W_>;
	}
	inline bool all_equal(__m128 lhs, __m128 rhs, int mask_)
	{
		return mask_equal(lhs, rhs) == mask_;
	}
	inline bool all_equal(__m128 lhs, __m128 rhs, bool x_, bool y_, bool z_, bool w_)
	{
		return all_equal(lhs, rhs, generate_move_mask(x_, y_, z_, w_));
	}
	/// <summary>
	/// <para> Compares the inequality of respective elements of the two passed SIMD vectors. </para>
	/// <para> The output of this function will be true if the respective template arguments match the results of the comparison. Otherwise, it will be false. </para>
	/// </summary>
	/// <param name="lhs">Left-hand argument of the comparison.</param>
	/// <param name="rhs">Right-hand argument of the comparison.</param>
	/// <returns>Boolean indicating if the result of an inequality comparison with the provided vectors matches all provided template arguments for respective elements.</returns>
	template<bool X_ = true, bool Y_ = true, bool Z_ = true, bool W_ = true>
	inline bool all_not_equal(__m128 lhs, __m128 rhs)
	{
		return mask_not_equal(lhs, rhs) == move_mask_v<X_, Y_, Z_, W_>;
	}
	inline bool all_not_equal(__m128 lhs, __m128 rhs, int mask_)
	{
		return mask_not_equal(lhs, rhs) == mask_;
	}
	inline bool all_not_equal(__m128 lhs, __m128 rhs, bool x_, bool y_, bool z_, bool w_)
	{
		return all_not_equal(lhs, rhs, generate_move_mask(x_, y_, z_, w_));
	}
	/// <summary>
	/// <para> Performs a less-than (&lt;) comparison of respective elements of the two passed SIMD vectors. </para>
	/// <para> The output of this function will be true if the respective template arguments match the results of the comparison. Otherwise, it will be false. </para>
	/// </summary>
	/// <param name="lhs">Left-hand argument of the comparison.</param>
	/// <param name="rhs">Right-hand argument of the comparison.</param>
	/// <returns>Boolean indicating if the result of a less-than (&lt;) comparison with the provided vectors matches all provided template arguments for respective elements.</returns>
	template<bool X_ = true, bool Y_ = true, bool Z_ = true, bool W_ = true>
	inline bool all_less_than(__m128 lhs, __m128 rhs)
	{
		return mask_less_than(lhs, rhs) == move_mask_v<X_, Y_, Z_, W_>;
	}
	inline bool all_less_than(__m128 lhs, __m128 rhs, int mask_)
	{
		return mask_less_than(lhs, rhs) == mask_;
	}
	inline bool all_less_than(__m128 lhs, __m128 rhs, bool x_, bool y_, bool z_, bool w_)
	{
		return all_less_than(lhs, rhs, generate_move_mask(x_, y_, z_, w_));
	}
	/// <summary>
	/// <para> Performs a greater-than (&gt;) comparison of respective elements of the two passed SIMD vectors. </para>
	/// <para> The output of this function will be true if the respective template arguments match the results of the comparison. Otherwise, it will be false. </para>
	/// </summary>
	/// <param name="lhs">Left-hand argument of the comparison.</param>
	/// <param name="rhs">Right-hand argument of the comparison.</param>
	/// <returns>Boolean indicating if the result of a greater-than (&gt;) comparison with the provided vectors matches all provided template arguments for respective elements.</returns>
	template<bool X_ = true, bool Y_ = true, bool Z_ = true, bool W_ = true>
	inline bool all_greater_than(__m128 lhs, __m128 rhs)
	{
		return mask_greater_than(lhs, rhs) == move_mask_v<X_, Y_, Z_, W_>;
	}
	inline bool all_greater_than(__m128 lhs, __m128 rhs, int mask_)
	{
		return mask_greater_than(lhs, rhs) == mask_;
	}
	inline bool all_greater_than(__m128 lhs, __m128 rhs, bool x_, bool y_, bool z_, bool w_)
	{
		return all_greater_than(lhs, rhs, generate_move_mask(x_, y_, z_, w_));
	}
	/// <summary>
	/// <para> Performs a less-or-equal (&lt;=) comparison of respective elements of the two passed SIMD vectors. </para>
	/// <para> The output of this function will be true if the respective template arguments match the results of the comparison. Otherwise, it will be false. </para>
	/// </summary>
	/// <param name="lhs">Left-hand argument of the comparison.</param>
	/// <param name="rhs">Right-hand argument of the comparison.</param>
	/// <returns>Boolean indicating if the result of a less-or-equal (&lt;=) comparison with the provided vectors matches all provided template arguments for respective elements.</returns>
	template<bool X_ = true, bool Y_ = true, bool Z_ = true, bool W_ = true>
	inline bool all_less_equal(__m128 lhs, __m128 rhs)
	{
		return mask_less_equal(lhs, rhs) == move_mask_v<X_, Y_, Z_, W_>;
	}
	inline bool all_less_equal(__m128 lhs, __m128 rhs, int mask_)
	{
		return mask_less_equal(lhs, rhs) == mask_;
	}
	inline bool all_less_equal(__m128 lhs, __m128 rhs, bool x_, bool y_, bool z_, bool w_)
	{
		return all_less_equal(lhs, rhs, generate_move_mask(x_, y_, z_, w_));
	}
	/// <summary>
	/// <para> Performs a greater-or-equal (&gt;=) comparison of respective elements of the two passed SIMD vectors. </para>
	/// <para> The output of this function will be true if the respective template arguments match the results of the comparison. Otherwise, it will be false. </para>
	/// </summary>
	/// <param name="lhs">Left-hand argument of the comparison.</param>
	/// <param name="rhs">Right-hand argument of the comparison.</param>
	/// <returns>Boolean indicating if the result of a greater-or-equal (&gt;=) comparison with the provided vectors matches all provided template arguments for respective elements.</returns>
	template<bool X_ = true, bool Y_ = true, bool Z_ = true, bool W_ = true>
	inline bool all_greater_equal(__m128 lhs, __m128 rhs)
	{
		return mask_greater_equal(lhs, rhs) == move_mask_v<X_, Y_, Z_, W_>;
	}
	inline bool all_greater_equal(__m128 lhs, __m128 rhs, int mask_)
	{
		return mask_greater_equal(lhs, rhs) == mask_;
	}
	inline bool all_greater_equal(__m128 lhs, __m128 rhs, bool x_, bool y_, bool z_, bool w_)
	{
		return all_greater_equal(lhs, rhs, generate_move_mask(x_, y_, z_, w_));
	}
#pragma endregion

#pragma region ANY_COMPARISONS
	/// <summary> Performs an equality comparison of respective elements of the two passed SIMD vectors. Returns true if at least one element comparison was true. </summary>
	/// <param name="lhs">Left-hand argument of the comparison.</param>
	/// <param name="rhs">Right-hand argument of the comparison.</param>
	/// <returns>True if any respective-element comparison is true, otherwise false.</returns>
	inline bool any_equal(__m128 lhs, __m128 rhs)
	{
		return mask_equal(lhs, rhs) != 0;
	}
	/// <summary> Performs an inequality comparison of respective elements of the two passed SIMD vectors. Returns true if at least one element comparison was true. </summary>
	/// <param name="lhs">Left-hand argument of the comparison.</param>
	/// <param name="rhs">Right-hand argument of the comparison.</param>
	/// <returns>True if any respective-element comparison is true, otherwise false.</returns>
	inline bool any_not_equal(__m128 lhs, __m128 rhs)
	{
		return mask_not_equal(lhs, rhs) != 0;
	}
	/// <summary> Performs a less-than comparison of respective elements of the two passed SIMD vectors. Returns true if at least one element comparison was true. </summary>
	/// <param name="lhs">Left-hand argument of the comparison.</param>
	/// <param name="rhs">Right-hand argument of the comparison.</param>
	/// <returns>True if any respective-element comparison is true, otherwise false.</returns>
	inline bool any_less_than(__m128 lhs, __m128 rhs)
	{
		return mask_less_than(lhs, rhs) != 0;
	}
	/// <summary> Performs a greater-than comparison of respective elements of the two passed SIMD vectors. Returns true if at least one element comparison was true. </summary>
	/// <param name="lhs">Left-hand argument of the comparison.</param>
	/// <param name="rhs">Right-hand argument of the comparison.</param>
	/// <returns>True if any respective-element comparison is true, otherwise false.</returns>
	inline bool any_greater_than(__m128 lhs, __m128 rhs)
	{
		return mask_greater_than(lhs, rhs) != 0;
	}
	/// <summary> Performs a less-or-equal comparison of respective elements of the two passed SIMD vectors. Returns true if at least one element comparison was true. </summary>
	/// <param name="lhs">Left-hand argument of the comparison.</param>
	/// <param name="rhs">Right-hand argument of the comparison.</param>
	/// <returns>True if any respective-element comparison is true, otherwise false.</returns>
	inline bool any_less_equal(__m128 lhs, __m128 rhs)
	{
		return mask_less_equal(lhs, rhs) != 0;
	}
	/// <summary> Performs a greater-or-equal comparison of respective elements of the two passed SIMD vectors. Returns true if at least one element comparison was true. </summary>
	/// <param name="lhs">Left-hand argument of the comparison.</param>
	/// <param name="rhs">Right-hand argument of the comparison.</param>
	/// <returns>True if any respective-element comparison is true, otherwise false.</returns>
	inline bool any_greater_equal(__m128 lhs, __m128 rhs)
	{
		return mask_greater_equal(lhs, rhs) != 0;
	}
#pragma endregion

#pragma region COUNT_COMPARISONS
	/// <summary> Performs an equality comparison of respective elements of the two passed SIMD vectors and returns the number of true results. </summary>
	/// <param name="lhs">Left-hand argument of the comparison.</param>
	/// <param name="rhs">Right-hand argument of the comparison.</param>
	/// <returns>Number of comparisons within the vectors which returned true. Any integer in the inclusve range 0-4.</returns>
	inline std::size_t count_equal(__m128 lhs, __m128 rhs)
	{
		return EmuCore::ArithmeticHelpers::num_active_bits(mask_equal(lhs, rhs));
	}
	/// <summary> Performs an inequality comparison of respective elements of the two passed SIMD vectors and returns the number of true results. </summary>
	/// <param name="lhs">Left-hand argument of the comparison.</param>
	/// <param name="rhs">Right-hand argument of the comparison.</param>
	/// <returns>Number of comparisons within the vectors which returned true. Any integer in the inclusve range 0-4.</returns>
	inline std::size_t count_not_equal(__m128 lhs, __m128 rhs)
	{
		return EmuCore::ArithmeticHelpers::num_active_bits(mask_not_equal(lhs, rhs));
	}
	/// <summary> Performs a less-than comparison of respective elements of the two passed SIMD vectors and returns the number of true results. </summary>
	/// <param name="lhs">Left-hand argument of the comparison.</param>
	/// <param name="rhs">Right-hand argument of the comparison.</param>
	/// <returns>Number of comparisons within the vectors which returned true. Any integer in the inclusve range 0-4.</returns>
	inline std::size_t count_less_than(__m128 lhs, __m128 rhs)
	{
		return EmuCore::ArithmeticHelpers::num_active_bits(mask_less_than(lhs, rhs));
	}
	/// <summary> Performs a greater-than comparison of respective elements of the two passed SIMD vectors and returns the number of true results. </summary>
	/// <param name="lhs">Left-hand argument of the comparison.</param>
	/// <param name="rhs">Right-hand argument of the comparison.</param>
	/// <returns>Number of comparisons within the vectors which returned true. Any integer in the inclusve range 0-4.</returns>
	inline std::size_t count_greater_than(__m128 lhs, __m128 rhs)
	{
		return EmuCore::ArithmeticHelpers::num_active_bits(mask_greater_than(lhs, rhs));
	}
	/// <summary> Performs a less-or-equal comparison of respective elements of the two passed SIMD vectors and returns the number of true results. </summary>
	/// <param name="lhs">Left-hand argument of the comparison.</param>
	/// <param name="rhs">Right-hand argument of the comparison.</param>
	/// <returns>Number of comparisons within the vectors which returned true. Any integer in the inclusve range 0-4.</returns>
	inline std::size_t count_less_equal(__m128 lhs, __m128 rhs)
	{
		return EmuCore::ArithmeticHelpers::num_active_bits(mask_less_equal(lhs, rhs));
	}
	/// <summary> Performs a greater-or-equal comparison of respective elements of the two passed SIMD vectors and returns the number of true results. </summary>
	/// <param name="lhs">Left-hand argument of the comparison.</param>
	/// <param name="rhs">Right-hand argument of the comparison.</param>
	/// <returns>Number of comparisons within the vectors which returned true. Any integer in the inclusve range 0-4.</returns>
	inline std::size_t count_greater_equal(__m128 lhs, __m128 rhs)
	{
		return EmuCore::ArithmeticHelpers::num_active_bits(mask_greater_equal(lhs, rhs));
	}
#pragma endregion

#pragma region GENERAL_ARITHMETIC
	__m128 dot_product(__m128 a_, __m128 b_)
	{
		a_ = _mm_mul_ps(a_, b_);
		return EmuMath::SIMD::horizontal_vector_sum(a_);
	}
	__m128 dot_product_fill(__m128 a_, __m128 b_)
	{
		a_ = _mm_mul_ps(a_, b_);
		return EmuMath::SIMD::horizontal_vector_sum_fill(a_);
	}
	float dot_product_scalar(__m128 a_, __m128 b_)
	{
		a_ = _mm_mul_ps(a_, b_);
		a_ = EmuMath::SIMD::horizontal_vector_sum(a_);
		return _mm_cvtss_f32(a_);
	}
#pragma endregion
}

#endif
