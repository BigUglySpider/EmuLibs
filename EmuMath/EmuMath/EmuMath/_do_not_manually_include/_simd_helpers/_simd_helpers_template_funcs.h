#ifndef EMU_MATH_SIMD_HELPERS_TEMPLATE_FUNCS_H_INC_
#define EMU_MATH_SIMD_HELPERS_TEMPLATE_FUNCS_H_INC_ 1

#include "_common_simd_helpers_includes.h"
#include "_simd_helpers_aliases.h"
#include "_simd_helpers_tmp.h"

namespace EmuMath::SIMD
{
	/// <summary>
	/// <para> Performs the correct _add_ operation for the provided SIMD Register_ type. </para>
	/// <para> 
	///		The provided PerElementWidthIfIntegral_ is used to determine how wide contained integer elements should be considered as for selecting the correct addition. 
	///		This is not used when a floating-point register is provided, and defaults to 32-bit elements.
	/// </para>
	/// </summary>
	/// <typeparam name="Register_">Register type to perform an addition operation via.</typeparam>
	/// <param name="lhs_">Register of values appearing on the left-hand side of addition.</param>
	/// <param name="rhs_">Register of values appearing on the right-hand side of addition.</param>
	/// <returns>Result of adding the two passed SIMD registers with their relevant _add_ operation (e.g. _mm_add_ps with __m128 registers).</returns>
	template<std::size_t PerElementWidthIfIntegral_ = 32, class Register_>
	[[nodiscard]] inline Register_ simd_add(Register_ lhs_, Register_ rhs_)
	{
		using register_type_uq = typename EmuCore::TMPHelpers::remove_ref_cv<Register_>::type;
		if constexpr (EmuMath::SIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			if constexpr (EmuMath::SIMD::TMP::is_floating_point_simd_register_v<register_type_uq>)
			{
				if constexpr (std::is_same_v<register_type_uq, __m128>)
				{
					return _mm_add_ps(lhs_, rhs_);
				}
				else if constexpr (std::is_same_v<register_type_uq, __m128d>)
				{
					return _mm_add_pd(lhs_, rhs_);
				}
				else if constexpr (std::is_same_v<register_type_uq, __m256>)
				{
					return _mm256_add_ps(lhs_, rhs_);
				}
				else if constexpr (std::is_same_v<register_type_uq, __m256d>)
				{
					return _mm256_add_pd(lhs_, rhs_);
				}
				else if constexpr (std::is_same_v<register_type_uq, __m512>)
				{
					return _mm512_add_ps(lhs_, rhs_);
				}
				else if constexpr (std::is_same_v<register_type_uq, __m512d>)
				{
					return _mm512_add_pd(lhs_, rhs_);
				}
				else
				{
					static_assert(false, "Unsupported SIMD register type provided to EmuMath::SIMD::simd_add. Register was considered a floating-point register type.");
				}
			}
			else
			{
				// Integral
				// --- No == 64 check for widths as that is the end of our valid range, and we won't reach that point if an invalid value is provided
				if constexpr (EmuMath::SIMD::TMP::_assert_valid_simd_int_element_width<PerElementWidthIfIntegral_>())
				{
					if constexpr (std::is_same_v<register_type_uq, __m128i>)
					{
						if constexpr (PerElementWidthIfIntegral_ == 8)
						{
							return _mm_add_epi8(lhs_, rhs_);
						}
						else if constexpr (PerElementWidthIfIntegral_ == 16)
						{
							return _mm_add_epi16(lhs_, rhs_);
						}
						else if constexpr (PerElementWidthIfIntegral_ == 32)
						{
							return _mm_add_epi32(lhs_, rhs_);
						}
						else
						{
							return _mm_add_epi64(lhs_, rhs_);
						}
					}
					else if constexpr (std::is_same_v<register_type_uq, __m256i>)
					{
						if constexpr (PerElementWidthIfIntegral_ == 8)
						{
							return _mm256_add_epi8(lhs_, rhs_);
						}
						else if constexpr (PerElementWidthIfIntegral_ == 16)
						{
							return _mm256_add_epi16(lhs_, rhs_);
						}
						else if constexpr (PerElementWidthIfIntegral_ == 32)
						{
							return _mm256_add_epi32(lhs_, rhs_);
						}
						else
						{
							return _mm256_add_epi64(lhs_, rhs_);
						}
					}
					else if constexpr (std::is_same_v<register_type_uq, __m512i>)
					{
						if constexpr (PerElementWidthIfIntegral_ == 8)
						{
							return _mm512_add_epi8(lhs_, rhs_);
						}
						else if constexpr (PerElementWidthIfIntegral_ == 16)
						{
							return _mm512_add_epi16(lhs_, rhs_);
						}
						else if constexpr (PerElementWidthIfIntegral_ == 32)
						{
							return _mm512_add_epi32(lhs_, rhs_);
						}
						else
						{
							return _mm512_add_epi64(lhs_, rhs_);
						}
					}
					else
					{
						static_assert(false, "Unsupported SIMD register type provided to EmuMath::SIMD::simd_add. Register was considered an integral register type.");
					}
				}
				else
				{
					static_assert(false, "Invalid PerElementWidthIfIntegral_ provided to EmuMath::SIMD::simd_add when used with an integral register type.");
				}
			}
		}
		else
		{
			static_assert(false, "Attempted to perform EmuMath::SIMD::simd_add with an unsupported type as the passed Register_.");
		}
	}
}

#endif
