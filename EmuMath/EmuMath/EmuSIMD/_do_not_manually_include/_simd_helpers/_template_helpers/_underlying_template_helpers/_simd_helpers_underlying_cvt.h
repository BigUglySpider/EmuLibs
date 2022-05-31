#ifndef EMU_SIMD_COMMON_UNDERLYING_SIMD_CVT_INCLUDES_H_INC_
#define EMU_SIMD_COMMON_UNDERLYING_SIMD_CVT_INCLUDES_H_INC_ 1

#include "_common_underlying_simd_template_helper_includes.h"
#include "_simd_helpers_underlying_cast.h"
#include "../../../../../EmuCore/TMPHelpers/Values.h"

namespace EmuSIMD::_underlying_simd_helpers
{
	template<class ToRegister_, std::size_t OutPerElementWidthIfInt_>
	[[nodiscard]] inline ToRegister_ _cvt_f32x4(EmuSIMD::f32x4 from_)
	{
		using to_uq = EmuCore::TMP::remove_ref_cv_t<ToRegister_>;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<to_uq>)
		{
			if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x4>)
			{
				return from_;
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x8>)
			{
				return _mm256_castps128_ps256(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x16>)
			{
				return _mm512_castps128_ps512(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x2>)
			{
				EmuSIMD::f64x2 = _mm_cvtps_pd(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x4>)
			{
				return _mm256_cvtps_pd(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x8>)
			{
				return _mm512_castpd256_pd512(_mm256_cvtps_pd(from_));
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i128_generic>)
			{
				if constexpr (OutPerElementWidthIfInt_ == 8)
				{
					return _mm_cvtepi32_epi8(_mm_cvtps_epi32(from_));
				}
				else if constexpr (OutPerElementWidthIfInt_ == 16)
				{
					return _mm_cvtepi32_epi16(_mm_cvtps_epi32(from_));
				}
				else if constexpr (OutPerElementWidthIfInt_ == 32)
				{
					return _mm_cvtps_epi32(from_);
				}
				else if constexpr (OutPerElementWidthIfInt_ == 64)
				{
					return _mm_cvtps_epi64(from_);
				}
				else
				{
					static_assert
					(
						EmuCore::TMP::get_false<OutPerElementWidthIfInt_>(),
						"Attempted to convert a EmuSIMD::f32x4 register to an integral register via EmuSIMD helpers, but the provided width per element is invalid. Only 8, 16, 32, and 64 are valid values."
					);
				}
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i256_generic>)
			{
				if constexpr (OutPerElementWidthIfInt_ == 8)
				{
					return _mm256_cvtepi32_epi8(_mm256_castsi128_si256(_mm_cvtps_epi32(from_)));
				}
				else if constexpr (OutPerElementWidthIfInt_ == 16)
				{
					return _mm256_castsi128_si256(_mm_cvtepi32_epi16(_mm_cvtps_epi32(from_)));
				}
				else if constexpr (OutPerElementWidthIfInt_ == 32)
				{
					return _mm256_castsi128_si256(_mm_cvtps_epi32(from_));
				}
				else if constexpr (OutPerElementWidthIfInt_ == 64)
				{
					return _mm256_cvtps_epi64(from_);
				}
				else
				{
					static_assert
					(
						EmuCore::TMP::get_false<OutPerElementWidthIfInt_>(),
						"Attempted to convert a EmuSIMD::f32x4 register to an integral register via EmuSIMD helpers, but the provided width per element is invalid. Only 8, 16, 32, and 64 are valid values."
					);
				}
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i512_generic>)
			{
				if constexpr (OutPerElementWidthIfInt_ == 8)
				{
					return _mm512_cvtepi32_epi8(_mm512_castsi128_si512(_mm_cvtps_epi32(from_)));
				}
				else if constexpr (OutPerElementWidthIfInt_ == 16)
				{
					_mm512_cvtepi32_epi16(_mm512_castsi128_si512(_mm_cvtps_epi32(from_)));
				}
				else if constexpr (OutPerElementWidthIfInt_ == 32)
				{
					return _mm512_castsi128_si512(_mm_cvtps_epi32(from_)));
				}
				else if constexpr (OutPerElementWidthIfInt_ == 64)
				{
					return _mm512_castsi256_si512(_mm256_cvtps_epi64(from_));
				}
				else
				{
					static_assert
					(
						EmuCore::TMP::get_false<OutPerElementWidthIfInt_>(),
						"Attempted to convert a EmuSIMD::f32x4 register to an integral register via EmuSIMD helpers, but the provided width per element is invalid. Only 8, 16, 32, and 64 are valid values."
					);
				}
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<ToRegister_>(), "Attempted to convert a EmuSIMD::f32x4 register via EmuSIMD helpers, but the provided SIMD register to convert to is not supported for this operation.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<ToRegister_>(), "Attempted to convert a EmuSIMD::f32x4 register via EmuSIMD helpers, but the provided register to convert to is not recognisd as a supported SIMD register.");
		}
	}








	template<class ToRegister_, std::size_t OutPerElementWidthIfInt_>
	[[nodiscard]] inline ToRegister_ _cvt_f32x4(EmuSIMD::f32x8 from_)
	{
		using to_uq = EmuCore::TMP::remove_ref_cv_t<ToRegister_>;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<to_uq>)
		{
			if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x4>)
			{
				return _mm256_castps256_ps128(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x8>)
			{
				return from_;
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x16>)
			{
				return _mm512_castps256_ps512(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x2>)
			{
				return _mm_cvtps_pd(_mm256_castps256_ps128(from_));
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x4>)
			{
				return _mm256_cvtps_pd(_mm256_castps256_ps128(from_));
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x8>)
			{
				return _mm512_cvtps_pd(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i128_generic>)
			{
				if constexpr (OutPerElementWidthIfInt_ == 8)
				{
					return _mm_cvtepi32_epi8(_mm_cvtps_epi32((_mm256_castps256_ps128(from_)));
				}
				else if constexpr (OutPerElementWidthIfInt_ == 16)
				{
					return _mm_cvtepi32_epi16(_mm_cvtps_epi32((_mm256_castps256_ps128(from_)));
				}
				else if constexpr (OutPerElementWidthIfInt_ == 32)
				{
					return _mm_cvtps_epi32((_mm256_castps256_ps128(from_));
				}
				else if constexpr (OutPerElementWidthIfInt_ == 64)
				{
					return _mm512_castsi512_si128(_mm512_cvtps_epi64(from_));
				}
				else
				{
					static_assert
					(
						EmuCore::TMP::get_false<OutPerElementWidthIfInt_>(),
						"Attempted to convert a EmuSIMD::f32x8 register to an integral register via EmuSIMD helpers, but the provided width per element is invalid. Only 8, 16, 32, and 64 are valid values."
					);
				}
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i256_generic>)
			{
				if constexpr (OutPerElementWidthIfInt_ == 8)
				{
					return _mm256_cvtepi32_epi8(_mm256_castsi128_si256(_mm_cvtps_epi32(from_)));
				}
				else if constexpr (OutPerElementWidthIfInt_ == 16)
				{
					return _mm256_castsi128_si256(_mm_cvtepi32_epi16(_mm_cvtps_epi32(from_)));
				}
				else if constexpr (OutPerElementWidthIfInt_ == 32)
				{
					return _mm256_castsi128_si256(_mm_cvtps_epi32(from_));
				}
				else if constexpr (OutPerElementWidthIfInt_ == 64)
				{
					return _mm256_cvtps_epi64(from_);
				}
				else
				{
					static_assert
					(
						EmuCore::TMP::get_false<OutPerElementWidthIfInt_>(),
						"Attempted to convert a EmuSIMD::f32x8 register to an integral register via EmuSIMD helpers, but the provided width per element is invalid. Only 8, 16, 32, and 64 are valid values."
					);
				}
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i512_generic>)
			{
				if constexpr (OutPerElementWidthIfInt_ == 8)
				{
					return _mm512_cvtepi32_epi8(_mm512_castsi128_si512(_mm_cvtps_epi32(from_)));
				}
				else if constexpr (OutPerElementWidthIfInt_ == 16)
				{
					_mm512_cvtepi32_epi16(_mm512_castsi128_si512(_mm_cvtps_epi32(from_)));
				}
				else if constexpr (OutPerElementWidthIfInt_ == 32)
				{
					return _mm512_castsi128_si512(_mm_cvtps_epi32(from_)));
				}
				else if constexpr (OutPerElementWidthIfInt_ == 64)
				{
					return _mm512_castsi256_si512(_mm256_cvtps_epi64(from_));
				}
				else
				{
					static_assert
					(
						EmuCore::TMP::get_false<OutPerElementWidthIfInt_>(),
						"Attempted to convert a EmuSIMD::f32x8 register to an integral register via EmuSIMD helpers, but the provided width per element is invalid. Only 8, 16, 32, and 64 are valid values."
					);
				}
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<ToRegister_>(), "Attempted to convert a EmuSIMD::f32x8 register via EmuSIMD helpers, but the provided SIMD register to convert to is not supported for this operation.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<ToRegister_>(), "Attempted to convert a EmuSIMD::f32x8 register via EmuSIMD helpers, but the provided register to convert to is not recognisd as a supported SIMD register.");
		}
	}
}

#endif

