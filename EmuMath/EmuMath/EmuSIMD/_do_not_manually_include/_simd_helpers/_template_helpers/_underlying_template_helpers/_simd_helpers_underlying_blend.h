#ifndef EMU_SIMD_HELPERS_UNDERLYING_BLEND_H_INC_
#define EMU_SIMD_HELPERS_UNDERLYING_BLEND_H_INC_ 1

#include "_common_underlying_simd_template_helper_includes.h"
#include "_simd_helpers_underlying_blend_mask.h"
#include "_simd_helpers_underlying_shuffle.h"

namespace EmuSIMD::_underlying_simd_helpers
{
	template<std::size_t PerElementWidthIfInt_ = 32, class Register_>
	[[nodiscard]] inline Register_ _blendv(Register_ a_, Register_ b_, Register_ mask_)
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			if constexpr (std::is_same_v<register_type_uq, __m128>)
			{
				return _mm_blendv_ps(a_, b_, mask_);
			}
			else if constexpr (std::is_same_v<register_type_uq, __m256>)
			{
				return _mm256_blendv_ps(a_, b_, mask_);
			}
			else if constexpr (std::is_same_v<register_type_uq, __m512>)
			{
				// No blendv for 512-bits, so split into two 256-bit registers to execute on those
				__m256 lo_ = _blendv(_mm512_castps512_ps256(a_), _mm512_castps512_ps256(b_), _mm512_castps512_ps256(mask_));
				__m256 hi_ = _blendv(_mm512_extractf32x8_ps(a_, 1), _mm512_extractf32x8_ps(b_, 1), _mm512_extractf32x8_ps(mask_, 1));
				return _mm512_insertf32x8(_mm512_castps256_ps512(lo_), hi_, 1);
			}
			else if constexpr (std::is_same_v<register_type_uq, __m128d>)
			{
				return _mm_blendv_pd(a_, b_, mask_);
			}
			else if constexpr (std::is_same_v<register_type_uq, __m256d>)
			{
				return _mm256_blendv_pd(a_, b_, mask_);
			}
			else if constexpr (std::is_same_v<register_type_uq, __m512d>)
			{
				__m256d lo_ = _blendv(_mm512_castpd512_pd256(a_), _mm512_castpd512_pd256(b_), _mm512_castpd512_pd256(mask_));
				__m256d hi_ = _blendv(_mm512_extractf64x4_pd(a_, 1), _mm512_extractf64x4_pd(b_, 1), _mm512_extractf64x4_pd(mask_, 1));
				return _mm512_insertf64x4(_mm512_castpd256_pd512(lo_), hi_, 1);
			}
			else if constexpr (EmuCore::TMP::is_any_comparison_true<std::is_same, register_type_uq, __m128i, __m256i, __m512i>::value)
			{
				// COVERS ALL SUPPORTED INTS
				if constexpr (EmuSIMD::TMP::_assert_valid_simd_int_element_width<PerElementWidthIfInt_>())
				{
					if constexpr (std::is_same_v<register_type_uq, __m128i>)
					{
						if constexpr (PerElementWidthIfInt_ == 8)
						{
							return _mm_blendv_epi8(a_, b_, mask_);
						}
						else if constexpr (PerElementWidthIfInt_ == 16)
						{
							return _mm_blendv_epi8
							(
								a_,
								b_,
								_execute_shuffle<0, 0, 2, 2, 4, 4, 6, 6, 8, 8, 10, 10, 12, 12, 14, 14>(mask_)
							);
						}
						else if constexpr (PerElementWidthIfInt_ == 32)
						{
							return _mm_blendv_epi8
							(
								a_,
								b_,
								_execute_shuffle<0, 0, 0, 0, 4, 4, 4, 4, 8, 8, 8, 8, 12, 12, 12, 12>(mask_)
							);
						}
						else
						{
							return _mm_blendv_epi8
							(
								a_,
								b_,
								_execute_shuffle<0, 0, 0, 0, 0, 0, 0, 0, 8, 8, 8, 8, 8, 8, 8, 8>(mask_)
							);
						}
					}
					else if constexpr(std::is_same_v<register_type_uq, __m256i>)
					{
						if constexpr (PerElementWidthIfInt_ == 8)
						{
							return _mm256_blendv_epi8(a_, b_, mask_);
						}
						else if constexpr (PerElementWidthIfInt_ == 16)
						{
							return _mm256_blendv_epi8
							(
								a_,
								b_,
								_execute_shuffle<0, 0, 2, 2, 4, 4, 6, 6, 8, 8, 10, 10, 12, 12, 14, 14, 0, 0, 2, 2, 4, 4, 6, 6, 8, 8, 10, 10, 12, 12, 14, 14>(mask_)
							);
						}
						else if constexpr (PerElementWidthIfInt_ == 32)
						{
							return _mm256_blendv_epi8
							(
								a_,
								b_,
								_execute_shuffle<0, 0, 0, 0, 4, 4, 4, 4, 8, 8, 8, 8, 12, 12, 12, 12, 0, 0, 0, 0, 4, 4, 4, 4, 8, 8, 8, 8, 12, 12, 12, 12>(mask_)
							);
						}
						else
						{
							return _mm256_blendv_epi8
							(
								a_,
								b_,
								_execute_shuffle<0, 0, 0, 0, 0, 0, 0, 0, 8, 8, 8, 8, 8, 8, 8, 8, 0, 0, 0, 0, 0, 0, 0, 0, 8, 8, 8, 8, 8, 8, 8, 8>(mask_)
							);
						}
					}
					else
					{
						__m256 lo_ = _blendv<PerElementWidthIfInt_>
						(
							_mm512_castsi512_si256(a_),
							_mm512_castsi512_si256(b_),
							_mm512_castsi512_si256(mask_)
						);
						__m256 hi_ = _blendv<PerElementWidthIfInt_>
						(
							_mm512_extracti64x4_epi64(a_, 1),
							_mm512_extracti64x4_epi64(b_, 1),
							_mm512_extracti64x4_epi64(mask_, 1)
						);
						return _mm512_inserti64x4(_mm512_castsi256_si512(lo_), hi_, 1);
					}
				}
				else
				{
					static_assert(false, "Attempted to execute a SIMD vectorwise blend (blendv) on an integral register, but the bit-width per element is invalid.");
				}
			}
			else
			{
				static_assert(false, "Attempted to execute a SIMD vectorwise blend (blendv), but the provided SIMD register is not supported for this operation.");
			}
		}
		else
		{
			static_assert(false, "Attempted to execute a SIMD vectorwise blend (blendv), but the provided Register_ type is not recognised as a supported SIMD register.");
		}
	}

	template<bool...IndexUsesB_, class Register_>
	[[nodiscard]] inline Register_ _blend(Register_ a_, Register_ b_)
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			using mask_generator = _underlying_simd_helpers::_blend_mask<register_type_uq, IndexUsesB_...>;
			if constexpr (_underlying_simd_helpers::_is_valid_blend_mask<mask_generator>::value)
			{
				if constexpr (_underlying_simd_helpers::_blend_mask_is_simd_register<mask_generator>::value)
				{
					// Defer to blendv for executing a register mask
					if constexpr (EmuCore::TMP::is_any_comparison_true<std::is_same, register_type_uq, __m128, __m256, __m512, __m128d, __m256d, __m512d>::value)
					{
						// Nothing extra needed
						return _blendv(a_, b_, mask_generator::get());
					}
					else if constexpr (EmuCore::TMP::is_any_comparison_true<std::is_same, register_type_uq, __m128i, __m256i, __m512i>::value)
					{
						constexpr std::size_t register_width_ = EmuSIMD::TMP::simd_register_width_v<register_type_uq>;
						constexpr std::size_t num_index_args_ = sizeof...(IndexUsesB_);
						constexpr std::size_t per_element_width_ = register_width_ / num_index_args_;
						if constexpr (EmuSIMD::TMP::_valid_simd_int_element_width(per_element_width_))
						{
							return _blendv<per_element_width_>(a_, b_, mask_generator::get());
						}
						else
						{
							static_assert(false, "Attempted to execute SIMD blend with index arguments which result in a vectorwise blend mask for a blendv operation, however the index argument count cannot be successfully used to determine a per-element width (in bits) for the register.");
						}
					}
					else
					{
						static_assert(false, "Attempted to execute SIMD blend with index arguments which result in a vectorwise blend mask for a blendv operation, however the passed SIMD register is not supported for EmuMath's blendv functionality.");
					}
				}
				else
				{
					// We have a non-register mask to use
					if constexpr (std::is_same_v<register_type_uq, __m128>)
					{
						return _mm_blend_ps(a_, b_, mask_generator::get());
					}
					else if constexpr (std::is_same_v<register_type_uq, __m256>)
					{
						return _mm256_blend_ps(a_, b_, mask_generator::get());
					}
					else if constexpr (std::is_same_v<register_type_uq, __m512>)
					{
						return _mm512_mask_blend_ps(mask_generator::get(), a_, b_);
					}
					else if constexpr (std::is_same_v<register_type_uq, __m128d>)
					{
						return _mm_blend_pd(a_, b_, mask_generator::get());
					}
					else if constexpr (std::is_same_v<register_type_uq, __m256d>)
					{
						return _mm256_blend_pd(a_, b_, mask_generator::get());
					}
					else if constexpr (std::is_same_v<register_type_uq, __m512d>)
					{
						return _mm512_mask_blend_pd(mask_generator::get(), a_, b_);
					}
					else if constexpr (EmuCore::TMP::is_any_comparison_true<std::is_same, register_type_uq, __m128i, __m256i, __m512i>::value)
					{
						constexpr std::size_t register_width_ = EmuSIMD::TMP::simd_register_width_v<register_type_uq>;
						constexpr std::size_t num_index_args_ = sizeof...(IndexUsesB_);
						constexpr std::size_t per_element_width_ = register_width_ / num_index_args_;

						if constexpr (EmuSIMD::TMP::_assert_valid_simd_int_element_width<per_element_width_>() && (per_element_width_ != 8))
						{
							// 8-bit is handled as vectorwise blend, so these cover the entire valid range in just an if...else
							if constexpr (per_element_width_ == 16)
							{
								// We know we have one of the 3 integral registers, so simple else...elif...else covers all scenarios
								if constexpr (std::is_same_v<register_type_uq, __m128i>)
								{
									return _mm_blend_epi16(a_, b_, mask_generator::get());
								}
								else if constexpr (std::is_same_v<register_type_uq, __m256i>)
								{
									return _mm256_blend_epi16(a_, b_, mask_generator::get());
								}
								else
								{
									return _mm512_mask_blend_epi16(mask_generator::get(), a_, b_);
								}
							}
							else
							{
								// Blending 64-bit boundaries is emulated through a 32-bit blend; arguments are duplicated before moving to the next
								// --- e.g. 64-bit blend<false, true> translates to 32-bit blend<false, false, true, true>
								if constexpr (std::is_same_v<register_type_uq, __m128i>)
								{
									return _mm_blend_epi32(a_, b_, mask_generator::get());
								}
								else if constexpr (std::is_same_v<register_type_uq, __m256i>)
								{
									return _mm256_blend_epi32(a_, b_, mask_generator::get());
								}
								else
								{
									return _mm512_mask_blend_epi32(mask_generator::get(), a_, b_);
								}
							}
						}
						else
						{
							if constexpr (per_element_width_ == 8)
							{
								static_assert(false, "Attempted to execute a SIMD blend, but the provided arguments and register resulted in an attempt at blending an integral register in 8-bit fields without deferring to blendv. This behaviour is prohibited.");
							}
							else
							{
								static_assert(false, "Attempted to execute SIMD blend with integral registers, however the index argument count cannot be successfully used to determine a per-element width (in bits) for the register.");
							}
						}
					}
					else
					{
						static_assert(false, "Attempted to execute a SIMD blend via EmuSIMD helpers using a SIMD register that is not supported for this operation.");
					}
				}
			}
			else
			{
				static_assert(false, "Attempted to execute a SIMD blend, but the provided IndexUsesB_ arguments were not valid for creating a mask for the provided SIMD register type.");
			}
		}
		else
		{
			static_assert(false, "Attempted to execute a SIMD blend, but the provided Register_ type is not recognised as a supported SIMD register.");
		}
	}
}

#endif
