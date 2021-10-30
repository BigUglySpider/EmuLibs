#ifndef EMU_MATH_SIMD_HELPERS_TEMPLATE_FUNCS_H_INC_
#define EMU_MATH_SIMD_HELPERS_TEMPLATE_FUNCS_H_INC_ 1

#include "_underlying_template_helpers/_common_underlying_simd_template_helper_includes.h"
#include "_underlying_template_helpers/_simd_helpers_underlying_set.h"
#include "_underlying_template_helpers/_simd_helpers_underlying_stream.h"
#include <ostream>

namespace EmuMath::SIMD
{
	template<std::size_t OutputWidthIfInt_ = 32, bool OutputSignedIfInt_ = true, class Register_>
	inline std::ostream& append_simd_vector_to_stream(std::ostream& str_, Register_ vec_)
	{
		return _underlying_simd_helpers::_append_to_stream<false, OutputWidthIfInt_, OutputSignedIfInt_>(str_, vec_);
	}

	template<std::size_t OutputWidthIfInt_ = 32, bool OutputSignedIfInt_ = true, class Register_>
	inline std::wostream& append_simd_vector_to_stream(std::wostream& str_, Register_ vec_)
	{
		return _underlying_simd_helpers::_append_to_stream<true, OutputWidthIfInt_, OutputSignedIfInt_>(str_, vec_);
	}

	template<class Register_, std::size_t ElementWidthIfInt_ = 32, typename...Args_>
	[[nodiscard]] inline Register_ simd_set(Args_&&...args_)
	{
		using register_type_uq = typename EmuCore::TMPHelpers::remove_ref_cv<Register_>::type;
		if constexpr (EmuMath::SIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			constexpr std::size_t num_args_ = sizeof...(Args_);
			if constexpr (EmuMath::SIMD::TMP::is_floating_point_simd_register_v<register_type_uq>)
			{
				return _underlying_simd_helpers::_set_fp<Register_>(args_...);
			}
			else
			{
				// Integral
				return _underlying_simd_helpers::_set_int<Register_, ElementWidthIfInt_>(args_...);
			}
		}
		else
		{
			static_assert(false, "Attempted to perform EmuMath::SIMD::simd_set with an unsupported type as the passed Register_.");
		}
	}

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
