#ifndef EMU_SIMD_COMMON_UNDERLYING_SIMD_CAST_INCLUDES_H_INC_
#define EMU_SIMD_COMMON_UNDERLYING_SIMD_CAST_INCLUDES_H_INC_ 1

#include "_common_underlying_simd_template_helper_includes.h"
#include "../../../../../EmuCore/TMPHelpers/Values.h"

namespace EmuSIMD::_underlying_simd_helpers
{
	template<class ToRegister_>
	[[nodiscard]] inline ToRegister_ _cast_m128(EmuSIMD::f32x4 from_)
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
				return _mm_castpd_ps(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x4>)
			{
				return _mm256_castpd128_pd256(_mm_castps_pd(from_));
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x8>)
			{
				return _mm512_castpd128_pd512(_mm_castps_pd(from_));
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i128_generic>)
			{
				return _mm_castps_si128(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i256_generic>)
			{
				return _mm256_castsi128_si256(_mm_castps_si128(from_));
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i512_generic>)
			{
				return _mm512_castsi128_si512(_mm_castps_si128(from_));
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<ToRegister_>(), "Attempted to cast a EmuSIMD::f32x4 register via EmuSIMD helpers, but the provided SIMD register to cast to is not supported for this operation.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<ToRegister_>(), "Attempted to cast a EmuSIMD::f32x4 register via EmuSIMD helpers, but the provided register to cast to is not recognisd as a supported SIMD register.");
		}
	}

	template<class ToRegister_>
	[[nodiscard]] inline ToRegister_ _cast_m256(EmuSIMD::f32x8 from_)
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
				return _mm_castps_pd(_mm256_castps256_ps128(from_));
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x4>)
			{
				return _mm256_castps_pd(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x8>)
			{
				return _mm512_castps_pd(_mm512_castps256_ps512(from_));
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i128_generic>)
			{
				return _mm_castps_si128(_mm256_castps256_ps128(from_));
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i256_generic>)
			{
				return _mm256_castps_si256(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i512_generic>)
			{
				return _mm512_castps_si512(_mm512_castps256_ps512(from_));
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<ToRegister_>(), "Attempted to cast a EmuSIMD::f32x8 register via EmuSIMD helpers, but the provided SIMD register to cast to is not supported for this operation.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<ToRegister_>(), "Attempted to cast a EmuSIMD::f32x8 register via EmuSIMD helpers, but the provided register to cast to is not recognisd as a supported SIMD register.");
		}
	}

	template<class ToRegister_>
	[[nodiscard]] inline ToRegister_ _cast_m512(EmuSIMD::f32x16 from_)
	{
		using to_uq = EmuCore::TMP::remove_ref_cv_t<ToRegister_>;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<to_uq>)
		{
			if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x4>)
			{
				return _mm512_castps512_ps128(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x8>)
			{
				return _mm512_castps512_ps256(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x16>)
			{
				return from_;
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x2>)
			{
				return _mm_castps_pd(_mm512_castps512_ps128(from_));
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x4>)
			{
				return _mm256_castps_pd(_mm512_castps512_ps256(from_));
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x8>)
			{
				return _mm512_castps_pd(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i128_generic>)
			{
				return _mm_castps_si128(_mm512_castps512_ps128(from_));
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i256_generic>)
			{
				return _mm256_castps_si256(_mm512_castps512_ps256(from_));
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i512_generic>)
			{
				return _mm512_castps_si512(from_);
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<ToRegister_>(), "Attempted to cast a EmuSIMD::f32x16 register via EmuSIMD helpers, but the provided SIMD register to cast to is not supported for this operation.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<ToRegister_>(), "Attempted to cast a EmuSIMD::f32x16 register via EmuSIMD helpers, but the provided register to cast to is not recognisd as a supported SIMD register.");
		}
	}

	template<class ToRegister_>
	[[nodiscard]] inline ToRegister_ _cast_m128d(EmuSIMD::f64x2 from_)
	{
		using to_uq = EmuCore::TMP::remove_ref_cv_t<ToRegister_>;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<to_uq>)
		{
			if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x4>)
			{
				return _mm_castpd_ps(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x8>)
			{
				return _mm256_castpd_ps(_mm256_castpd128_pd256(from_));
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x16>)
			{
				return _mm512_castpd_ps(_mm512_castpd128_pd512(from_));
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x2>)
			{
				return from_;
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x4>)
			{
				return _mm256_castpd128_pd256(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x8>)
			{
				return _mm512_castpd128_pd512(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i128_generic>)
			{
				return _mm_castpd_si128(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i256_generic>)
			{
				return _mm256_castpd_si256(_mm256_castpd128_pd256(from_));
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i512_generic>)
			{
				return _mm512_castpd_si512(_mm512_castpd128_pd512(from_));
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<ToRegister_>(), "Attempted to cast a EmuSIMD::f64x2 register via EmuSIMD helpers, but the provided SIMD register to cast to is not supported for this operation.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<ToRegister_>(), "Attempted to cast a EmuSIMD::f64x2 register via EmuSIMD helpers, but the provided register to cast to is not recognisd as a supported SIMD register.");
		}
	}

	template<class ToRegister_>
	[[nodiscard]] inline ToRegister_ _cast_m256d(EmuSIMD::f64x4 from_)
	{
		using to_uq = EmuCore::TMP::remove_ref_cv_t<ToRegister_>;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<to_uq>)
		{
			if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x4>)
			{
				return _mm_castpd_ps(_mm256_castpd256_pd128(from_));
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x8>)
			{
				return _mm256_castpd_ps(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x16>)
			{
				return _mm512_castpd_ps(_mm512_castpd256_pd512(from_));
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x2>)
			{
				return _mm256_castpd256_pd128(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x4>)
			{
				return from_;
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x8>)
			{
				return _mm512_castpd256_pd512(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i128_generic>)
			{
				return _mm_castpd_si128(_mm256_castpd256_pd128(from_));
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i256_generic>)
			{
				return _mm256_castpd_si256(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i512_generic>)
			{
				return _mm512_castpd_si512(_mm512_castpd256_pd512(from_));
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<ToRegister_>(), "Attempted to cast a EmuSIMD::f64x4 register via EmuSIMD helpers, but the provided SIMD register to cast to is not supported for this operation.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<ToRegister_>(), "Attempted to cast a EmuSIMD::f64x4 register via EmuSIMD helpers, but the provided register to cast to is not recognisd as a supported SIMD register.");
		}
	}

	template<class ToRegister_>
	[[nodiscard]] inline ToRegister_ _cast_m512d(EmuSIMD::f64x8 from_)
	{
		using to_uq = EmuCore::TMP::remove_ref_cv_t<ToRegister_>;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<to_uq>)
		{
			if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x4>)
			{
				return _mm_castpd_ps(_mm512_castpd512_pd128(from_));
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x8>)
			{
				return _mm256_castpd_ps(_mm512_castpd512_pd256(from_));
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x16>)
			{
				return _mm512_castpd_ps(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x2>)
			{
				return _mm512_castpd512_pd128(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x4>)
			{
				return _mm512_castpd512_pd256(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x8>)
			{
				return from_;
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i128_generic>)
			{
				return _mm_castpd_si128(_mm512_castpd512_pd128(from_));
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i256_generic>)
			{
				return _mm256_castpd_si256(_mm512_castpd512_pd256(from_));
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i512_generic>)
			{
				return _mm512_castpd_si512(from_);
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<ToRegister_>(), "Attempted to cast a EmuSIMD::f64x8 register via EmuSIMD helpers, but the provided SIMD register to cast to is not supported for this operation.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<ToRegister_>(), "Attempted to cast a EmuSIMD::f64x8 register via EmuSIMD helpers, but the provided register to cast to is not recognisd as a supported SIMD register.");
		}
	}

	template<class ToRegister_>
	[[nodiscard]] inline ToRegister_ _cast_m128i(EmuSIMD::i128_generic from_)
	{
		using to_uq = EmuCore::TMP::remove_ref_cv_t<ToRegister_>;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<to_uq>)
		{
			if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x4>)
			{
				return _mm_castsi128_ps(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x8>)
			{
				return _mm256_castsi256_ps(_mm256_castsi128_si256(from_));
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x16>)
			{
				return _mm512_castsi512_ps(_mm512_castsi128_si512(from_));
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x2>)
			{
				return _mm_castsi128_pd(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x4>)
			{
				return _mm256_castsi256_pd(_mm256_castsi128_si256(from_));
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x8>)
			{
				return _mm512_castsi512_pd(_mm512_castsi128_si512(from_));
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i128_generic>)
			{
				return from_;
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i256_generic>)
			{
				return _mm256_castsi128_si256(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i512_generic>)
			{
				return _mm512_castsi128_si512(from_);
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<ToRegister_>(), "Attempted to cast a EmuSIMD::i128_generic register via EmuSIMD helpers, but the provided SIMD register to cast to is not supported for this operation.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<ToRegister_>(), "Attempted to cast a EmuSIMD::i128_generic register via EmuSIMD helpers, but the provided register to cast to is not recognisd as a supported SIMD register.");
		}
	}

	template<class ToRegister_>
	[[nodiscard]] inline ToRegister_ _cast_m256i(EmuSIMD::i256_generic from_)
	{
		using to_uq = EmuCore::TMP::remove_ref_cv_t<ToRegister_>;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<to_uq>)
		{
			if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x4>)
			{
				return _mm_castsi128_ps(_mm256_castsi256_si128(from_));
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x8>)
			{
				return _mm256_castsi256_ps(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x16>)
			{
				return _mm512_castsi512_ps(_mm512_castsi256_si512(from_));
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x2>)
			{
				return _mm_castsi128_pd(_mm256_castsi256_si128(from_));
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x4>)
			{
				return _mm256_castsi256_pd(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x8>)
			{
				return _mm512_castsi512_pd(_mm512_castsi256_si512(from_));
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i128_generic>)
			{
				return _mm256_castsi256_si128(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i256_generic>)
			{
				return from_;
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i512_generic>)
			{
				return _mm512_castsi256_si512(from_);
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<ToRegister_>(), "Attempted to cast a EmuSIMD::i256_generic register via EmuSIMD helpers, but the provided SIMD register to cast to is not supported for this operation.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<ToRegister_>(), "Attempted to cast a EmuSIMD::i256_generic register via EmuSIMD helpers, but the provided register to cast to is not recognisd as a supported SIMD register.");
		}
	}

	template<class ToRegister_>
	[[nodiscard]] inline ToRegister_ _cast_m512i(EmuSIMD::i512_generic from_)
	{
		using to_uq = EmuCore::TMP::remove_ref_cv_t<ToRegister_>;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<to_uq>)
		{
			if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x4>)
			{
				return _mm_castsi128_ps(_mm512_castsi512_si128(from_));
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x8>)
			{
				return _mm256_castsi256_ps(_mm512_castsi512_si256(from_));
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x16>)
			{
				return _mm512_castsi512_ps(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x2>)
			{
				return _mm_castsi128_pd(_mm512_castsi512_si128(from_));
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x4>)
			{
				return _mm256_castsi256_pd(_mm512_castsi512_si256(from_));
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x8>)
			{
				return _mm512_castsi512_pd(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i128_generic>)
			{
				return _mm512_castsi512_si128(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i256_generic>)
			{
				return _mm512_castsi512_si256(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i512_generic>)
			{
				return from_;
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<ToRegister_>(), "Attempted to cast a EmuSIMD::i512_generic register via EmuSIMD helpers, but the provided SIMD register to cast to is not supported for this operation.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<ToRegister_>(), "Attempted to cast a EmuSIMD::i512_generic register via EmuSIMD helpers, but the provided register to cast to is not recognisd as a supported SIMD register.");
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
				if constexpr (std::is_same_v<from_uq, EmuSIMD::f32x4>)
				{
					return _cast_m128<ToRegister_>(from_);
				}
				else if constexpr (std::is_same_v<from_uq, EmuSIMD::f32x8>)
				{
					return _cast_m256<ToRegister_>(from_);
				}
				else if constexpr (std::is_same_v<from_uq, EmuSIMD::f32x16>)
				{
					return _cast_m512<ToRegister_>(from_);
				}
				else if constexpr (std::is_same_v<from_uq, EmuSIMD::f64x2>)
				{
					return _cast_m128d<ToRegister_>(from_);
				}
				else if constexpr (std::is_same_v<from_uq, EmuSIMD::f64x4>)
				{
					return _cast_m256d<ToRegister_>(from_);
				}
				else if constexpr (std::is_same_v<from_uq, EmuSIMD::f64x8>)
				{
					return _cast_m512d<ToRegister_>(from_);
				}
				else if constexpr (std::is_same_v<from_uq, EmuSIMD::i128_generic>)
				{
					return _cast_m128i<ToRegister_>(from_);
				}
				else if constexpr (std::is_same_v<from_uq, EmuSIMD::i256_generic>)
				{
					return _cast_m256i<ToRegister_>(from_);
				}
				else if constexpr (std::is_same_v<from_uq, EmuSIMD::i512_generic>)
				{
					return _cast_m512i<ToRegister_>(from_);
				}
				else
				{
					static_assert(EmuCore::TMP::get_false<ToRegister_>(), "Attempted to cast a SIMD register via EmuSIMD helpers, but the provided SIMD register to cast from is not supported for this operation.");
				}
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<ToRegister_>(), "Attempted to cast a SIMD register via EmuSIMD helpers, but the provided register to cast to is not recognisd as a supported SIMD register.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<ToRegister_>(), "Attempted to cast a SIMD register via EmuSIMD helpers, but the provided register to cast from is not recognisd as a supported SIMD register.");
		}
	}
}

#endif
