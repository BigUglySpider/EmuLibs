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

	/// <summary>
	/// <para> Provides the mask for the provided index within an __m128i 8-bit register. </para>
	/// </summary>
	/// <returns>__m128i register which acts as a mask for the provided index within said register types.</returns>
	template<std::size_t Index_>
	[[nodiscard]] inline __m128i index_mask_m128i_8()
	{
		if constexpr (Index_ <= 15)
		{
			return _mm_set_epi8
			(
				EmuCore::TMPHelpers::conditional_value_v<Index_ == 15, std::int8_t, 0xFF, 0x00>,
				EmuCore::TMPHelpers::conditional_value_v<Index_ == 14, std::int8_t, 0xFF, 0x00>,
				EmuCore::TMPHelpers::conditional_value_v<Index_ == 13, std::int8_t, 0xFF, 0x00>,
				EmuCore::TMPHelpers::conditional_value_v<Index_ == 12, std::int8_t, 0xFF, 0x00>,
				EmuCore::TMPHelpers::conditional_value_v<Index_ == 11, std::int8_t, 0xFF, 0x00>,
				EmuCore::TMPHelpers::conditional_value_v<Index_ == 10, std::int8_t, 0xFF, 0x00>,
				EmuCore::TMPHelpers::conditional_value_v<Index_ == 9,  std::int8_t, 0xFF, 0x00>,
				EmuCore::TMPHelpers::conditional_value_v<Index_ == 8,  std::int8_t, 0xFF, 0x00>,
				EmuCore::TMPHelpers::conditional_value_v<Index_ == 7,  std::int8_t, 0xFF, 0x00>,
				EmuCore::TMPHelpers::conditional_value_v<Index_ == 6,  std::int8_t, 0xFF, 0x00>,
				EmuCore::TMPHelpers::conditional_value_v<Index_ == 5,  std::int8_t, 0xFF, 0x00>,
				EmuCore::TMPHelpers::conditional_value_v<Index_ == 4,  std::int8_t, 0xFF, 0x00>,
				EmuCore::TMPHelpers::conditional_value_v<Index_ == 3,  std::int8_t, 0xFF, 0x00>,
				EmuCore::TMPHelpers::conditional_value_v<Index_ == 2,  std::int8_t, 0xFF, 0x00>,
				EmuCore::TMPHelpers::conditional_value_v<Index_ == 1,  std::int8_t, 0xFF, 0x00>,
				EmuCore::TMPHelpers::conditional_value_v<Index_ == 0,  std::int8_t, 0xFF, 0x00>
			);
		}
		else
		{
			static_assert(false, "Attempted to retrieve a mask for an invalid index within an __m128i 8-bit register.");
		}
	}
	template<bool i0_, bool i1_, bool i2_, bool i3_, bool i4_, bool i5_, bool i6_, bool i7_, bool i8_, bool i9_, bool i10_, bool i11_, bool i12_, bool i13_, bool i14_, bool i15_>
	[[nodiscard]] inline __m128i index_mask_m128i_8()
	{
		return _mm_set_epi8
		(
			EmuCore::TMPHelpers::conditional_value_v<i15_, std::int8_t, 0xFF, 0x00>,
			EmuCore::TMPHelpers::conditional_value_v<i14_, std::int8_t, 0xFF, 0x00>,
			EmuCore::TMPHelpers::conditional_value_v<i13_, std::int8_t, 0xFF, 0x00>,
			EmuCore::TMPHelpers::conditional_value_v<i12_, std::int8_t, 0xFF, 0x00>,
			EmuCore::TMPHelpers::conditional_value_v<i11_, std::int8_t, 0xFF, 0x00>,
			EmuCore::TMPHelpers::conditional_value_v<i10_, std::int8_t, 0xFF, 0x00>,
			EmuCore::TMPHelpers::conditional_value_v<i9_,  std::int8_t, 0xFF, 0x00>,
			EmuCore::TMPHelpers::conditional_value_v<i8_,  std::int8_t, 0xFF, 0x00>,
			EmuCore::TMPHelpers::conditional_value_v<i7_,  std::int8_t, 0xFF, 0x00>,
			EmuCore::TMPHelpers::conditional_value_v<i6_,  std::int8_t, 0xFF, 0x00>,
			EmuCore::TMPHelpers::conditional_value_v<i5_,  std::int8_t, 0xFF, 0x00>,
			EmuCore::TMPHelpers::conditional_value_v<i4_,  std::int8_t, 0xFF, 0x00>,
			EmuCore::TMPHelpers::conditional_value_v<i3_,  std::int8_t, 0xFF, 0x00>,
			EmuCore::TMPHelpers::conditional_value_v<i2_,  std::int8_t, 0xFF, 0x00>,
			EmuCore::TMPHelpers::conditional_value_v<i1_,  std::int8_t, 0xFF, 0x00>,
			EmuCore::TMPHelpers::conditional_value_v<i0_,  std::int8_t, 0xFF, 0x00>
		);
	}
	/// <summary>
	/// <para> Provides the mask for the provided index within an __m128i 16-bit register. </para>
	/// </summary>
	/// <returns>__m128i register which acts as a mask for the provided index within said register types.</returns>
	template<std::size_t Index_>
	[[nodiscard]] inline __m128i index_mask_m128i_16()
	{
		if constexpr (Index_ <= 7)
		{
			return _mm_set_epi16
			(
				EmuCore::TMPHelpers::conditional_value_v<Index_ == 7, std::int16_t, 0xFFFF, 0x0000>,
				EmuCore::TMPHelpers::conditional_value_v<Index_ == 6, std::int16_t, 0xFFFF, 0x0000>,
				EmuCore::TMPHelpers::conditional_value_v<Index_ == 5, std::int16_t, 0xFFFF, 0x0000>,
				EmuCore::TMPHelpers::conditional_value_v<Index_ == 4, std::int16_t, 0xFFFF, 0x0000>,
				EmuCore::TMPHelpers::conditional_value_v<Index_ == 3, std::int16_t, 0xFFFF, 0x0000>,
				EmuCore::TMPHelpers::conditional_value_v<Index_ == 2, std::int16_t, 0xFFFF, 0x0000>,
				EmuCore::TMPHelpers::conditional_value_v<Index_ == 1, std::int16_t, 0xFFFF, 0x0000>,
				EmuCore::TMPHelpers::conditional_value_v<Index_ == 0, std::int16_t, 0xFFFF, 0x0000>
			);
		}
		else
		{
			static_assert(false, "Attempted to retrieve a mask for an invalid index within an __m128i 16-bit register.");
		}
	}
	template<bool i0_, bool i1_, bool i2_, bool i3_, bool i4_, bool i5_, bool i6_, bool i7_>
	[[nodiscard]] inline __m128 index_mask_m128i_16()
	{
		return _mm_set_epi16
		(
			EmuCore::TMPHelpers::conditional_value_v<i7_, std::int16_t, 0xFFFF, 0x0000>,
			EmuCore::TMPHelpers::conditional_value_v<i6_, std::int16_t, 0xFFFF, 0x0000>,
			EmuCore::TMPHelpers::conditional_value_v<i5_, std::int16_t, 0xFFFF, 0x0000>,
			EmuCore::TMPHelpers::conditional_value_v<i4_, std::int16_t, 0xFFFF, 0x0000>,
			EmuCore::TMPHelpers::conditional_value_v<i3_, std::int16_t, 0xFFFF, 0x0000>,
			EmuCore::TMPHelpers::conditional_value_v<i2_, std::int16_t, 0xFFFF, 0x0000>,
			EmuCore::TMPHelpers::conditional_value_v<i1_, std::int16_t, 0xFFFF, 0x0000>,
			EmuCore::TMPHelpers::conditional_value_v<i0_, std::int16_t, 0xFFFF, 0x0000>
		);
	}

	/// <summary>
	/// <para> Provides the mask for the provided index within an __m128i 32-bit register. </para>
	/// </summary>
	/// <returns>__m128i register which acts as a mask for the provided index within said register types.</returns>
	template<std::size_t Index_>
	[[nodiscard]] inline __m128i index_mask_m128i_32()
	{
		if constexpr (Index_ <= 3)
		{
			return _mm_set_epi32
			(
				EmuCore::TMPHelpers::conditional_value_v<Index_ == 3, std::int32_t, 0xFFFFFFFF, 0x00000000>,
				EmuCore::TMPHelpers::conditional_value_v<Index_ == 2, std::int32_t, 0xFFFFFFFF, 0x00000000>,
				EmuCore::TMPHelpers::conditional_value_v<Index_ == 1, std::int32_t, 0xFFFFFFFF, 0x00000000>,
				EmuCore::TMPHelpers::conditional_value_v<Index_ == 0, std::int32_t, 0xFFFFFFFF, 0x00000000>
			);
		}
		else
		{
			static_assert(false, "Attempted to retrieve a mask for an invalid index within an __m128i 32-bit register.");
		}
	}
	template<bool i0_, bool i1_, bool i2_, bool i3_>
	[[nodiscard]] inline __m128i index_mask_m128i_32()
	{
		return _mm_set_epi32
		(
			EmuCore::TMPHelpers::conditional_value_v<i3_, std::int32_t, 0xFFFFFFFF, 0x00000000>,
			EmuCore::TMPHelpers::conditional_value_v<i2_, std::int32_t, 0xFFFFFFFF, 0x00000000>,
			EmuCore::TMPHelpers::conditional_value_v<i1_, std::int32_t, 0xFFFFFFFF, 0x00000000>,
			EmuCore::TMPHelpers::conditional_value_v<i0_, std::int32_t, 0xFFFFFFFF, 0x00000000>
		);
	}

	/// <summary>
	/// <para> Provides the mask for the provided index within an __m128i 64-bit register. </para>
	/// </summary>
	/// <returns>__m128i register which acts as a mask for the provided index within said register types.</returns>
	template<std::size_t Index_>
	[[nodiscard]] inline __m128i index_mask_m128i_64()
	{
		if constexpr (Index_ <= 1)
		{
			return _mm_set_epi64x
			(
				EmuCore::TMPHelpers::conditional_value_v<Index_ == 1, std::int64_t, 0xFFFFFFFFFFFFFFFF, 0x0000000000000000>,
				EmuCore::TMPHelpers::conditional_value_v<Index_ == 0, std::int64_t, 0xFFFFFFFFFFFFFFFF, 0x0000000000000000>
			);
		}
		else
		{
			static_assert(false, "Attempted to retrieve a mask for an invalid index within an __m128i 64-bit register.");
		}
	}
	template<bool i0_, bool i1_>
	[[nodiscard]] inline __m128i index_mask_m128i_64()
	{
		return _mm_set_epi64x
		(
			EmuCore::TMPHelpers::conditional_value_v<i1_, std::int64_t, 0xFFFFFFFFFFFFFFFF, 0x0000000000000000>,
			EmuCore::TMPHelpers::conditional_value_v<i0_, std::int64_t, 0xFFFFFFFFFFFFFFFF, 0x0000000000000000>
		);
	}

	/// <summary>
	/// <para> Provides the mask for the provided index within an __m128i register, where each element is considered to contain NumBits_ bits. </para>
	/// <para> Valid values for NumBits_ are: 8, 16, 32, 64. Anything else will result in a static assertion being triggered. </para>
	/// </summary>
	/// <returns></returns>
	template<std::size_t Index_, std::size_t NumBits_>
	[[nodiscard]] inline __m128i index_mask_m128i()
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
	[[nodiscard]] inline __m128 index_mask_m128()
	{
		if constexpr (Index_ <= 3)
		{
			return _mm_castsi128_ps(index_mask_m128i_32<Index_>());
		}
		else
		{
			static_assert(false, "Attempted to retrieve a mask for an invalid index within an __m128 register.");
		}
	}
	template<bool i0_, bool i1_, bool i2_, bool i3_>
	[[nodiscard]] inline __m128 index_mask_m128()
	{
		return _mm_castsi128_ps(index_mask_m128i_32<i0_, i1_, i2_, i3_>());
	}

	template<std::size_t Index_>
	[[nodiscard]] inline __m128d index_mask_m128d()
	{
		if constexpr (Index_ <= 1)
		{
			return _mm_castsi128_pd(index_mask_m128i_32<Index_>());
		}
		else
		{
			static_assert(false, "Attempted to retrieve a mask for an invalid index within an __m128d reigster.");
		}
	}
	template<bool i0_, bool i1_>
	[[nodiscard]] inline __m128d index_mask_m128d()
	{
		return _mm_castsi128_pd(index_mask_m128i_64<i0_, i1_>());
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
	[[nodiscard]] inline RegisterType_ index_mask()
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
}

#endif
