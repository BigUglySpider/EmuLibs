#ifndef EMU_SIMD_HELPERS_UNDERLYING_BITWISE_H_INC_
#define EMU_SIMD_HELPERS_UNDERLYING_BITWISE_H_INC_ 1

#include "_common_underlying_simd_template_helper_includes.h"
#include "_simd_helpers_underlying_index_masks.h"

namespace EmuSIMD::_underlying_simd_helpers
{
	template<class Register_>
	[[nodiscard]] inline Register_ _and(Register_ lhs_, Register_ rhs_)
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			if constexpr (std::is_same_v<register_type_uq, __m128>)
			{
				return _mm_and_ps(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, __m256>)
			{
				return _mm256_and_ps(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, __m512>)
			{
				return _mm512_and_ps(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, __m128d>)
			{
				return _mm_and_pd(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, __m256d>)
			{
				return _mm256_and_pd(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, __m512d>)
			{
				return _mm512_and_pd(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, __m128i>)
			{
				return _mm_and_si128(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, __m256i>)
			{
				return _mm256_and_si256(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, __m512i>)
			{
				return _mm512_and_si512(lhs_, rhs_);
			}
			else
			{
				static_assert(false, "Attempted to perform bitwise AND of a SIMD register using EmuSIMD helpers, but the provided SIMD register is not supported for this operation");
			}
		}
		else
		{
			static_assert(false, "Attempted to perform bitwise AND of a SIMD register using EmuSIMD helpers, but provided a type that is not a supported SIMD register.");
		}
	}

	template<class Register_>
	[[nodiscard]] inline Register_ _or(Register_ lhs_, Register_ rhs_)
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			if constexpr (std::is_same_v<register_type_uq, __m128>)
			{
				return _mm_or_ps(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, __m256>)
			{
				return _mm256_or_ps(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, __m512>)
			{
				return _mm512_or_ps(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, __m128d>)
			{
				return _mm_or_pd(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, __m256d>)
			{
				return _mm256_or_pd(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, __m512d>)
			{
				return _mm512_or_pd(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, __m128i>)
			{
				return _mm_or_si128(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, __m256i>)
			{
				return _mm256_or_si256(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, __m512i>)
			{
				return _mm512_or_si512(lhs_, rhs_);
			}
			else
			{
				static_assert(false, "Attempted to perform bitwise OR of a SIMD register using EmuSIMD helpers, but the provided SIMD register is not supported for this operation");
			}
		}
		else
		{
			static_assert(false, "Attempted to perform bitwise OR of a SIMD register using EmuSIMD helpers, but provided a type that is not a supported SIMD register.");
		}
	}

	template<class Register_>
	[[nodiscard]] inline Register_ _xor(Register_ lhs_, Register_ rhs_)
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			if constexpr (std::is_same_v<register_type_uq, __m128>)
			{
				return _mm_xor_ps(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, __m256>)
			{
				return _mm256_xor_ps(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, __m512>)
			{
				return _mm512_xor_ps(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, __m128d>)
			{
				return _mm_xor_pd(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, __m256d>)
			{
				return _mm256_xor_pd(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, __m512d>)
			{
				return _mm512_xor_pd(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, __m128i>)
			{
				return _mm_xor_si128(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, __m256i>)
			{
				return _mm256_xor_si256(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, __m512i>)
			{
				return _mm512_xor_si512(lhs_, rhs_);
			}
			else
			{
				static_assert(false, "Attempted to perform bitwise XOR of a SIMD register using EmuSIMD helpers, but the provided SIMD register is not supported for this operation");
			}
		}
		else
		{
			static_assert(false, "Attempted to perform bitwise XOR of a SIMD register using EmuSIMD helpers, but provided a type that is not a supported SIMD register.");
		}
	}

	template<class Register_>
	[[nodiscard]] inline Register_ _andnot(Register_ lhs_, Register_ rhs_)
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			if constexpr (std::is_same_v<register_type_uq, __m128>)
			{
				return _mm_andnot_ps(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, __m256>)
			{
				return _mm256_andnot_ps(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, __m512>)
			{
				return _mm512_andnot_ps(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, __m128d>)
			{
				return _mm_andnot_pd(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, __m256d>)
			{
				return _mm256_andnot_pd(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, __m512d>)
			{
				return _mm512_andnot_pd(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, __m128i>)
			{
				return _mm_andnot_si128(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, __m256i>)
			{
				return _mm256_andnot_si256(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, __m512i>)
			{
				return _mm512_andnot_si512(lhs_, rhs_);
			}
			else
			{
				static_assert(false, "Attempted to perform bitwise ANDNOT of a SIMD register using EmuSIMD helpers, but the provided SIMD register is not supported for this operation");
			}
		}
		else
		{
			static_assert(false, "Attempted to perform bitwise ANDNOT of a SIMD register using EmuSIMD helpers, but provided a type that is not a supported SIMD register.");
		}
	}

	template<class Register_>
	[[nodiscard]] inline Register_ _not(Register_ to_not_)
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			constexpr bool is_supported_register_ = EmuCore::TMP::is_any_comparison_true
			<
				std::is_same,
				register_type_uq,
				__m128, __m256, __m512,
				__m128d, __m256d, __m512d,
				__m128i, __m256i, __m512i
			>::value;
			if constexpr (is_supported_register_)
			{
				using all_indices_mask_generator = _underlying_simd_helpers::_per_index_mask<register_type_uq, true>;
				if constexpr (_is_valid_per_index_mask_instance<all_indices_mask_generator>::value)
				{
					// A XOR (11...11) == ~A
					return _xor(to_not_, all_indices_mask_generator::get());
				}
				else
				{
					static_assert(false, "Attempted to perform bitwise NOT of a SIMD register using EmuSIMD helpers, but a mask to perform the operation could not be successfully generated.");
				}
			}
			else
			{
				static_assert(false, "Attempted to perform bitwise NOT of a SIMD register using EmuSIMD helpers, but provided a SIMD register that is not supported for this operation.");
			}
		}
		else
		{
			static_assert(false, "Attempted to perform bitwise NOT of a SIMD register using EmuSIMD helpers, but provided a type that is not a supported SIMD register.");
		}
	}
}

#endif
