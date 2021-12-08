#ifndef EMU_SIMD_COMMON_UNDERLYING_SIMD_CAST_INCLUDES_H_INC_
#define EMU_SIMD_COMMON_UNDERLYING_SIMD_CAST_INCLUDES_H_INC_ 1

#include "_common_underlying_simd_template_helper_includes.h"

namespace EmuSIMD::_underlying_simd_helpers
{
	template<class ToRegister_>
	[[nodiscard]] inline ToRegister_ _cast_m128(__m128 from_)
	{
		using to_uq = EmuCore::TMP::remove_ref_cv_t<ToRegister_>;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<to_uq>)
		{
			if constexpr (std::is_same_v<to_uq, __m128>)
			{
				return from_;
			}
			else if constexpr (std::is_same_v<to_uq, __m256>)
			{
				return _mm256_castps128_ps256(from_);
			}
			else if constexpr (std::is_same_v<to_uq, __m512>)
			{
				return _mm512_castps128_ps512(from_);
			}
			else if constexpr (std::is_same_v<to_uq, __m128d>)
			{
				return _mm_castpd_ps(from_);
			}
			else if constexpr (std::is_same_v<to_uq, __m256d>)
			{
				return _mm256_castpd128_pd256(_mm_castps_pd(from_));
			}
			else if constexpr (std::is_same_v<to_uq, __m512d>)
			{
				return _mm512_castpd128_pd512(_mm_castps_pd(from_));
			}
			else if constexpr (std::is_same_v<to_uq, __m128i>)
			{
				return _mm_castps_si128(from_);
			}
			else if constexpr (std::is_same_v<to_uq, __m256i>)
			{
				return _mm256_castsi128_si256(_mm_castps_si128(from_));
			}
			else if constexpr (std::is_same_v<to_uq, __m512i>)
			{
				return _mm512_castsi128_si512(_mm_castps_si128(from_));
			}
			else
			{
				static_assert(false, "Attempted to cast a __m128 register via EmuSIMD helpers, but the provided SIMD register to cast to is not supported for this operation.");
			}
		}
		else
		{
			static_assert(false, "Attempted to cast a __m128 register via EmuSIMD helpers, but the provided register to cast to is not recognisd as a supported SIMD register.");
		}
	}

	template<class ToRegister_>
	[[nodiscard]] inline ToRegister_ _cast_m256(__m256 from_)
	{
		using to_uq = EmuCore::TMP::remove_ref_cv_t<ToRegister_>;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<to_uq>)
		{
			if constexpr (std::is_same_v<to_uq, __m128>)
			{
				return _mm256_castps256_ps128(from_);
			}
			else if constexpr (std::is_same_v<to_uq, __m256>)
			{
				return from_;
			}
			else if constexpr (std::is_same_v<to_uq, __m512>)
			{
				return _mm512_castps256_ps512(from_);
			}
			else if constexpr (std::is_same_v<to_uq, __m128d>)
			{
				return _mm_castps_pd(_mm256_castps256_ps128(from_));
			}
			else if constexpr (std::is_same_v<to_uq, __m256d>)
			{
				return _mm256_castps_pd(from_);
			}
			else if constexpr (std::is_same_v<to_uq, __m512d>)
			{
				return _mm512_castps_pd(_mm512_castps256_ps512(from_));
			}
			else if constexpr (std::is_same_v<to_uq, __m128i>)
			{
				return _mm_castps_si128(_mm256_castps256_ps128(from_));
			}
			else if constexpr (std::is_same_v<to_uq, __m256i>)
			{
				return _mm256_castps_si256(from_);
			}
			else if constexpr (std::is_same_v<to_uq, __m512i>)
			{
				return _mm512_castps_si512(_mm512_castps256_ps512(from_));
			}
			else
			{
				static_assert(false, "Attempted to cast a __m256 register via EmuSIMD helpers, but the provided SIMD register to cast to is not supported for this operation.");
			}
		}
		else
		{
			static_assert(false, "Attempted to cast a __m256 register via EmuSIMD helpers, but the provided register to cast to is not recognisd as a supported SIMD register.");
		}
	}

	template<class ToRegister_>
	[[nodiscard]] inline ToRegister_ _cast_m512(__m512 from_)
	{
		using to_uq = EmuCore::TMP::remove_ref_cv_t<ToRegister_>;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<to_uq>)
		{
			if constexpr (std::is_same_v<to_uq, __m128>)
			{
				return _mm512_castps512_ps128(from_);
			}
			else if constexpr (std::is_same_v<to_uq, __m256>)
			{
				return _mm512_castps512_ps256(from_);
			}
			else if constexpr (std::is_same_v<to_uq, __m512>)
			{
				return from_;
			}
			else if constexpr (std::is_same_v<to_uq, __m128d>)
			{
				return _mm_castps_pd(_mm512_castps512_ps128(from_));
			}
			else if constexpr (std::is_same_v<to_uq, __m256d>)
			{
				return _mm256_castps_pd(_mm512_castps512_ps256(from_));
			}
			else if constexpr (std::is_same_v<to_uq, __m512d>)
			{
				return _mm512_castps_pd(from_);
			}
			else if constexpr (std::is_same_v<to_uq, __m128i>)
			{
				return _mm_castps_si128(_mm512_castps512_ps128(from_));
			}
			else if constexpr (std::is_same_v<to_uq, __m256i>)
			{
				return _mm256_castps_si256(_mm512_castps512_ps256(from_));
			}
			else if constexpr (std::is_same_v<to_uq, __m512i>)
			{
				return _mm512_castps_si512(from_);
			}
			else
			{
				static_assert(false, "Attempted to cast a __m512 register via EmuSIMD helpers, but the provided SIMD register to cast to is not supported for this operation.");
			}
		}
		else
		{
			static_assert(false, "Attempted to cast a __m512 register via EmuSIMD helpers, but the provided register to cast to is not recognisd as a supported SIMD register.");
		}
	}

	template<class ToRegister_>
	[[nodiscard]] inline ToRegister_ _cast_m128d(__m128d from_)
	{
		using to_uq = EmuCore::TMP::remove_ref_cv_t<ToRegister_>;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<to_uq>)
		{
			if constexpr (std::is_same_v<to_uq, __m128>)
			{
				return _mm_castpd_ps(from_);
			}
			else if constexpr (std::is_same_v<to_uq, __m256>)
			{
				return _mm256_castpd_ps(_mm256_castpd128_pd256(from_));
			}
			else if constexpr (std::is_same_v<to_uq, __m512>)
			{
				return _mm512_castpd_ps(_mm512_castpd128_pd512(from_));
			}
			else if constexpr (std::is_same_v<to_uq, __m128d>)
			{
				return from_;
			}
			else if constexpr (std::is_same_v<to_uq, __m256d>)
			{
				return _mm256_castpd128_pd256(from_);
			}
			else if constexpr (std::is_same_v<to_uq, __m512d>)
			{
				return _mm512_castpd128_pd512(from_);
			}
			else if constexpr (std::is_same_v<to_uq, __m128i>)
			{
				return _mm_castpd_si128(from_);
			}
			else if constexpr (std::is_same_v<to_uq, __m256i>)
			{
				return _mm256_castpd_si256(_mm256_castpd128_pd256(from_));
			}
			else if constexpr (std::is_same_v<to_uq, __m512i>)
			{
				return _mm512_castpd_si512(_mm512_castpd128_pd512(from_));
			}
			else
			{
				static_assert(false, "Attempted to cast a __m128d register via EmuSIMD helpers, but the provided SIMD register to cast to is not supported for this operation.");
			}
		}
		else
		{
			static_assert(false, "Attempted to cast a __m128d register via EmuSIMD helpers, but the provided register to cast to is not recognisd as a supported SIMD register.");
		}
	}

	template<class ToRegister_>
	[[nodiscard]] inline ToRegister_ _cast_m256d(__m256d from_)
	{
		using to_uq = EmuCore::TMP::remove_ref_cv_t<ToRegister_>;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<to_uq>)
		{
			if constexpr (std::is_same_v<to_uq, __m128>)
			{
				return _mm_castpd_ps(_mm256_castpd256_pd128(from_));
			}
			else if constexpr (std::is_same_v<to_uq, __m256>)
			{
				return _mm256_castpd_ps(from_);
			}
			else if constexpr (std::is_same_v<to_uq, __m512>)
			{
				return _mm512_castpd_ps(_mm512_castpd256_pd512(from_));
			}
			else if constexpr (std::is_same_v<to_uq, __m128d>)
			{
				return _mm256_castpd256_pd128(from_);
			}
			else if constexpr (std::is_same_v<to_uq, __m256d>)
			{
				return from_;
			}
			else if constexpr (std::is_same_v<to_uq, __m512d>)
			{
				return _mm512_castpd256_pd512(from_);
			}
			else if constexpr (std::is_same_v<to_uq, __m128i>)
			{
				return _mm_castpd_si128(_mm256_castpd256_pd128(from_));
			}
			else if constexpr (std::is_same_v<to_uq, __m256i>)
			{
				return _mm256_castpd_si256(from_);
			}
			else if constexpr (std::is_same_v<to_uq, __m512i>)
			{
				return _mm512_castpd_si512(_mm512_castpd256_pd512(from_));
			}
			else
			{
				static_assert(false, "Attempted to cast a __m256d register via EmuSIMD helpers, but the provided SIMD register to cast to is not supported for this operation.");
			}
		}
		else
		{
			static_assert(false, "Attempted to cast a __m256d register via EmuSIMD helpers, but the provided register to cast to is not recognisd as a supported SIMD register.");
		}
	}

	template<class ToRegister_>
	[[nodiscard]] inline ToRegister_ _cast_m512d(__m512d from_)
	{
		using to_uq = EmuCore::TMP::remove_ref_cv_t<ToRegister_>;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<to_uq>)
		{
			if constexpr (std::is_same_v<to_uq, __m128>)
			{
				return _mm_castpd_ps(_mm512_castpd512_pd128(from_));
			}
			else if constexpr (std::is_same_v<to_uq, __m256>)
			{
				return _mm256_castpd_ps(_mm512_castpd512_pd256(from_));
			}
			else if constexpr (std::is_same_v<to_uq, __m512>)
			{
				return _mm512_castpd_ps(from_);
			}
			else if constexpr (std::is_same_v<to_uq, __m128d>)
			{
				return _mm512_castpd512_pd128(from_);
			}
			else if constexpr (std::is_same_v<to_uq, __m256d>)
			{
				return _mm512_castpd512_pd256(from_);
			}
			else if constexpr (std::is_same_v<to_uq, __m512d>)
			{
				return from_;
			}
			else if constexpr (std::is_same_v<to_uq, __m128i>)
			{
				return _mm_castpd_si128(_mm512_castpd512_pd128(from_));
			}
			else if constexpr (std::is_same_v<to_uq, __m256i>)
			{
				return _mm256_castpd_si256(_mm512_castpd512_pd256(from_));
			}
			else if constexpr (std::is_same_v<to_uq, __m512i>)
			{
				return _mm512_castpd_si512(from_);
			}
			else
			{
				static_assert(false, "Attempted to cast a __m512d register via EmuSIMD helpers, but the provided SIMD register to cast to is not supported for this operation.");
			}
		}
		else
		{
			static_assert(false, "Attempted to cast a __m512d register via EmuSIMD helpers, but the provided register to cast to is not recognisd as a supported SIMD register.");
		}
	}

	template<class ToRegister_>
	[[nodiscard]] inline ToRegister_ _cast_m128i(__m128i from_)
	{
		using to_uq = EmuCore::TMP::remove_ref_cv_t<ToRegister_>;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<to_uq>)
		{
			if constexpr (std::is_same_v<to_uq, __m128>)
			{
				return _mm_castsi128_ps(from_);
			}
			else if constexpr (std::is_same_v<to_uq, __m256>)
			{
				return _mm256_castsi256_ps(_mm256_castsi128_si256(from_));
			}
			else if constexpr (std::is_same_v<to_uq, __m512>)
			{
				return _mm512_castsi512_ps(_mm512_castsi128_si512(from_));
			}
			else if constexpr (std::is_same_v<to_uq, __m128d>)
			{
				return _mm_castsi128_pd(from_);
			}
			else if constexpr (std::is_same_v<to_uq, __m256d>)
			{
				return _mm256_castsi256_pd(_mm256_castsi128_si256(from_));
			}
			else if constexpr (std::is_same_v<to_uq, __m512d>)
			{
				return _mm512_castsi512_pd(_mm512_castsi128_si512(from_));
			}
			else if constexpr (std::is_same_v<to_uq, __m128i>)
			{
				return from_;
			}
			else if constexpr (std::is_same_v<to_uq, __m256i>)
			{
				return _mm256_castsi128_si256(from_);
			}
			else if constexpr (std::is_same_v<to_uq, __m512i>)
			{
				return _mm512_castsi128_si512(from_);
			}
			else
			{
				static_assert(false, "Attempted to cast a __m128i register via EmuSIMD helpers, but the provided SIMD register to cast to is not supported for this operation.");
			}
		}
		else
		{
			static_assert(false, "Attempted to cast a __m128i register via EmuSIMD helpers, but the provided register to cast to is not recognisd as a supported SIMD register.");
		}
	}

	template<class ToRegister_>
	[[nodiscard]] inline ToRegister_ _cast_m256i(__m256i from_)
	{
		using to_uq = EmuCore::TMP::remove_ref_cv_t<ToRegister_>;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<to_uq>)
		{
			if constexpr (std::is_same_v<to_uq, __m128>)
			{
				return _mm_castsi128_ps(_mm256_castsi256_si128(from_));
			}
			else if constexpr (std::is_same_v<to_uq, __m256>)
			{
				return _mm256_castsi256_ps(from_);
			}
			else if constexpr (std::is_same_v<to_uq, __m512>)
			{
				return _mm512_castsi512_ps(_mm512_castsi256_si512(from_));
			}
			else if constexpr (std::is_same_v<to_uq, __m128d>)
			{
				return _mm_castsi128_pd(_mm256_castsi256_si128(from_));
			}
			else if constexpr (std::is_same_v<to_uq, __m256d>)
			{
				return _mm256_castsi256_pd(from_);
			}
			else if constexpr (std::is_same_v<to_uq, __m512d>)
			{
				return _mm512_castsi512_pd(_mm512_castsi256_si512(from_));
			}
			else if constexpr (std::is_same_v<to_uq, __m128i>)
			{
				return _mm256_castsi256_si128(from_);
			}
			else if constexpr (std::is_same_v<to_uq, __m256i>)
			{
				return from_;
			}
			else if constexpr (std::is_same_v<to_uq, __m512i>)
			{
				return _mm512_castsi256_si512(from_);
			}
			else
			{
				static_assert(false, "Attempted to cast a __m256i register via EmuSIMD helpers, but the provided SIMD register to cast to is not supported for this operation.");
			}
		}
		else
		{
			static_assert(false, "Attempted to cast a __m256i register via EmuSIMD helpers, but the provided register to cast to is not recognisd as a supported SIMD register.");
		}
	}

	template<class ToRegister_>
	[[nodiscard]] inline ToRegister_ _cast_m512i(__m512i from_)
	{
		using to_uq = EmuCore::TMP::remove_ref_cv_t<ToRegister_>;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<to_uq>)
		{
			if constexpr (std::is_same_v<to_uq, __m128>)
			{
				return _mm_castsi128_ps(_mm512_castsi512_si128(from_));
			}
			else if constexpr (std::is_same_v<to_uq, __m256>)
			{
				return _mm256_castsi256_ps(_mm512_castsi512_si256(from_));
			}
			else if constexpr (std::is_same_v<to_uq, __m512>)
			{
				return _mm512_castsi512_ps(from_);
			}
			else if constexpr (std::is_same_v<to_uq, __m128d>)
			{
				return _mm_castsi128_pd(_mm512_castsi512_si128(from_));
			}
			else if constexpr (std::is_same_v<to_uq, __m256d>)
			{
				return _mm256_castsi256_pd(_mm512_castsi512_si256(from_));
			}
			else if constexpr (std::is_same_v<to_uq, __m512d>)
			{
				return _mm512_castsi512_pd(from_);
			}
			else if constexpr (std::is_same_v<to_uq, __m128i>)
			{
				return _mm512_castsi512_si128(from_);
			}
			else if constexpr (std::is_same_v<to_uq, __m256i>)
			{
				return _mm512_castsi512_si256(from_);
			}
			else if constexpr (std::is_same_v<to_uq, __m512i>)
			{
				return from_;
			}
			else
			{
				static_assert(false, "Attempted to cast a __m512i register via EmuSIMD helpers, but the provided SIMD register to cast to is not supported for this operation.");
			}
		}
		else
		{
			static_assert(false, "Attempted to cast a __m512i register via EmuSIMD helpers, but the provided register to cast to is not recognisd as a supported SIMD register.");
		}
	}

	template<class ToRegister_, class FromRegister_>
	[[nodiscard]] ToRegister_ _cast(FromRegister_ from_)
	{
		using from_uq = EmuCore::TMP::remove_ref_cv_t<FromRegister_>;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<from_uq>)
		{
			using to_uq = EmuCore::TMP::remove_ref_cv_t<ToRegister_>;
			if constexpr (EmuSIMD::TMP::is_simd_register_v<to_uq>)
			{
				if constexpr (std::is_same_v<from_uq, __m128>)
				{
					return _cast_m128<ToRegister_>(from_);
				}
				else if constexpr (std::is_same_v<from_uq, __m256>)
				{
					return _cast_m256<ToRegister_>(from_);
				}
				else if constexpr (std::is_same_v<from_uq, __m512>)
				{
					return _cast_m512<ToRegister_>(from_);
				}
				else if constexpr (std::is_same_v<from_uq, __m128d>)
				{
					return _cast_m128d<ToRegister_>(from_);
				}
				else if constexpr (std::is_same_v<from_uq, __m256d>)
				{
					return _cast_m256d<ToRegister_>(from_);
				}
				else if constexpr (std::is_same_v<from_uq, __m512d>)
				{
					return _cast_m512d<ToRegister_>(from_);
				}
				else if constexpr (std::is_same_v<from_uq, __m128i>)
				{
					return _cast_m128i<ToRegister_>(from_);
				}
				else if constexpr (std::is_same_v<from_uq, __m256i>)
				{
					return _cast_m256i<ToRegister_>(from_);
				}
				else if constexpr (std::is_same_v<from_uq, __m512i>)
				{
					return _cast_m512i<ToRegister_>(from_);
				}
				else
				{
					static_assert(false, "Attempted to cast a SIMD register via EmuSIMD helpers, but the provided SIMD register to cast from is not supported for this operation.");
				}
			}
			else
			{
				static_assert(false, "Attempted to cast a SIMD register via EmuSIMD helpers, but the provided register to cast to is not recognisd as a supported SIMD register.");
			}
		}
		else
		{
			static_assert(false, "Attempted to cast a SIMD register via EmuSIMD helpers, but the provided register to cast from is not recognisd as a supported SIMD register.");
		}
	}
}

#endif
