#ifndef EMU_MATH_SIMD_TEMPLATE_HELPERS_UNDERLYING_GET_H_INC_
#define EMU_MATH_SIMD_TEMPLATE_HELPERS_UNDERLYING_GET_H_INC_ 1

#include "_common_underlying_simd_template_helper_includes.h"

namespace EmuMath::SIMD::_underlying_simd_helpers
{
	template
	<
		typename POutNoVoidOrConst_,
		class Register_,
		typename = std::enable_if_t<!std::is_same_v<POutNoVoidOrConst_, void> && !std::is_const_v<POutNoVoidOrConst_>>
	>
	[[nodiscard]] inline void _store_register(Register_ register_, POutNoVoidOrConst_* p_out_no_void_or_const_)
	{
		if constexpr (EmuMath::SIMD::TMP::is_simd_register_v<Register_>)
		{
			using register_type_uq = typename EmuCore::TMPHelpers::remove_ref_cv<Register_>::type;
			if constexpr (std::is_same_v<register_type_uq, __m128>)
			{
				_mm_store_ps(reinterpret_cast<float*>(p_out_no_void_or_const_), register_);
			}
			else if constexpr (std::is_same_v<register_type_uq, __m128d>)
			{
				_mm_store_pd(reinterpret_cast<double*>(p_out_no_void_or_const_), register_);
			}
			else if constexpr (std::is_same_v<register_type_uq, __m256>)
			{
				_mm256_store_ps(reinterpret_cast<float*>(p_out_no_void_or_const_), register_);
			}
			else if constexpr (std::is_same_v<register_type_uq, __m256d>)
			{
				_mm256_store_pd(reinterpret_cast<double*>(p_out_no_void_or_const_), register_);
			}
			else if constexpr (std::is_same_v<register_type_uq, __m512>)
			{
				_mm512_store_ps(reinterpret_cast<void*>(p_out_no_void_or_const_), register_);
			}
			else if constexpr (std::is_same_v<register_type_uq, __m512d>)
			{
				_mm512_store_pd(reinterpret_cast<void*>(p_out_no_void_or_const_), register_);
			}
			else if constexpr (std::is_same_v<register_type_uq, __m128i>)
			{
				_mm_store_si128(reinterpret_cast<__m128i*>(p_out_no_void_or_const_), register_);
			}
			else if constexpr (std::is_same_v<register_type_uq, __m256i>)
			{
				_mm256_store_si256(reinterpret_cast<__m256i*>(p_out_no_void_or_const_), register_);
			}
			else if constexpr (std::is_same_v<register_type_uq, __m512i>)
			{
				_mm512_store_si512(reinterpret_cast<void*>(p_out_no_void_or_const_), register_);
			}
			else
			{
				static_assert(false, "Attempted to store a SIMD register to a pointer via an EmuMath SIMD helper, but the provided register_ could not be recognised.");
			}
		}
		else
		{
			static_assert(false, "Attempted to store a SIMD register to a pointer via an EmuMath SIMD helper, but the provided register_ was not a supported SIMD register.");
		}
	}
}

#endif
