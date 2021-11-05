#ifndef EMU_MATH_SIMD_HELPERS_TEMPLATE_COMMON_ARITHMETIC
#define EMU_MATH_SIMD_HELPERS_TEMPLATE_COMMON_ARITHMETIC 1

#include "_underlying_template_helpers/_simd_helpers_underlying_basic_arithmetic.h"
#include "_simd_helpers_template_cast.h"
#include "_simd_helpers_template_gets.h"
#include "_simd_helpers_template_shuffles.h"

namespace EmuMath::SIMD
{
	/// <summary>
	/// <para> Performs a linear interpolation using a_ as initial values, b_ as target values, and t_ as interpolation weightings. </para>
	/// <para> 
	///		The provided PerElementWidthIfInt_ is used to determine how wide contained integer elements should be considered as 
	///		for selecting the correct operations if an integral register is provided.
	/// </para>
	/// <para> The provided PerElementWidthIfInt_ argument is not used if the provided register contains floating-point elements. </para>
	/// </summary>
	/// <param name="a_">SIMD vector to use as starting values.</param>
	/// <param name="b_">SIMD vector to use as target values.</param>
	/// <param name="t_">SIMD vector to use as weightings for each interpolation.</param>
	/// <returns>Result of linear interpolation, summarised as a + ((b - a) * t)</returns>
	template<std::size_t PerElementWidthIfInt_ = 32, class Register_>
	[[nodiscard]] inline Register_ lerp(Register_ a_, Register_ b_, Register_ t_)
	{
		using register_type_uq = typename EmuCore::TMPHelpers::remove_ref_cv<Register_>::type;
		if constexpr (EmuMath::SIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			if constexpr (EmuMath::SIMD::TMP::is_floating_point_simd_register_v<register_type_uq>)
			{
				register_type_uq b_minus_a_ = _underlying_simd_helpers::_sub_fp(b_, a_);
				return _underlying_simd_helpers::_add_fp(a_, _underlying_simd_helpers::_mul_fp(b_minus_a_, t_));
			}
			else if constexpr (EmuMath::SIMD::TMP::is_integral_simd_register_v<register_type_uq>)
			{
				register_type_uq b_minus_a_ = _underlying_simd_helpers::_sub_int<PerElementWidthIfInt_>(b_, a_);
				return _underlying_simd_helpers::_add_int(a_, _underlying_simd_helpers::_mul_all_int<PerElementWidthIfInt_>(b_minus_a_, t_));
			}
			else
			{
				static_assert(false, "Attempted to perform EmuMath::SIMD::lerp, but the provided SIMD register type is unsupported for this operation.");
			}
		}
		else
		{
			static_assert(false, "Attempted to perform EmuMath::SIMD::lerp with an unsupported type as the passed Register_.");
		}
	}

	/// <summary>
	/// <para> Performs a linear interpolation using a_ as initial values, b_ as target values, and t_ as interpolation weightings. </para>
	/// <para> Fused operations will be performed where possible if the passed registers are capable, avoiding an additional rounding operation. </para>
	/// <para> 
	///		The provided PerElementWidthIfInt_ is used to determine how wide contained integer elements should be considered as 
	///		for selecting the correct operations if an integral register is provided.
	/// </para>
	/// <para> The provided PerElementWidthIfInt_ argument is not used if the provided register contains floating-point elements. </para>
	/// </summary>
	/// <param name="a_">SIMD vector to use as starting values.</param>
	/// <param name="b_">SIMD vector to use as target values.</param>
	/// <param name="t_">SIMD vector to use as weightings for each interpolation.</param>
	/// <returns>Result of linear interpolation, summarised as a + ((b - a) * t)</returns>
	template<std::size_t PerElementWidthIfInt_ = 32, class Register_>
	[[nodiscard]] inline Register_ fused_lerp(Register_ a_, Register_ b_, Register_ t_)
	{
		using register_type_uq = typename EmuCore::TMPHelpers::remove_ref_cv<Register_>::type;
		if constexpr (EmuMath::SIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			if constexpr (EmuMath::SIMD::TMP::is_floating_point_simd_register_v<register_type_uq>)
			{
				return _underlying_simd_helpers::_fmadd_fp
				(
					_underlying_simd_helpers::_sub_fp(b_, a_),
					t_,
					a_
				);
			}
			else if constexpr (EmuMath::SIMD::TMP::is_integral_simd_register_v<register_type_uq>)
			{
				return _underlying_simd_helpers::_fmadd_int<PerElementWidthIfInt_>
				(
					_underlying_simd_helpers::_sub_int<PerElementWidthIfInt_>(b_, a_),
					t_,
					a_
				);
			}
			else
			{
				static_assert(false, "Attempted to perform EmuMath::SIMD::lerp, but the provided SIMD register type is unsupported for this operation.");
			}
		}
		else
		{
			static_assert(false, "Attempted to perform EmuMath::SIMD::lerp with an unsupported type as the passed Register_.");
		}
	}

	/// <summary>
	/// <para> Calculates the horizontal sum of the passed register, guaranteeing the result to be stored in the first element. </para>
	/// <para> Result elements that are not the first have no guarantees, and are likely to vary between different register types. </para>
	/// <para> 
	///		The provided PerElementWidthIfInt_ is used to determine how wide contained integer elements should be considered as 
	///		for selecting the correct operations if an integral register is provided.
	/// </para>
	/// <para> The provided PerElementWidthIfInt_ argument is not used if the provided register contains floating-point elements. </para>
	/// </summary>
	/// <typeparam name="Register_">Type of register to calculate the horizontal sum of.</typeparam>
	/// <param name="register_">Register to calculate the horizontal sum of.</param>
	/// <returns>SIMD register of the provided type containing the horizontal sum of the passed register_ within its first element.</returns>
	template<std::size_t PerElementWidthIfInt_ = 32, class Register_>
	[[nodiscard]] inline Register_ horizontal_sum(Register_ register_)
	{
		using register_type_uq = typename EmuCore::TMPHelpers::remove_ref_cv<Register_>::type;
		if constexpr (EmuMath::SIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			if constexpr (EmuMath::SIMD::TMP::is_floating_point_simd_register_v<register_type_uq>)
			{
				if constexpr (std::is_same_v<register_type_uq, __m128>)
				{
					__m128 shuffled_ = _underlying_simd_helpers::_execute_shuffle<1, 0, 3, 2>(register_);
					__m128 out_ = _underlying_simd_helpers::_add_fp(register_, shuffled_);
					shuffled_ = _mm_movehl_ps(shuffled_, out_);
					return _mm_add_ss(out_, shuffled_);
				}
				else if constexpr (std::is_same_v<register_type_uq, __m256>)
				{
					return _mm256_castps128_ps256
					(
						horizontal_sum
						(
							_mm_add_ps
							(
								_mm256_extractf128_ps(register_, 0),
								_mm256_extractf128_ps(register_, 1)
							)
						)
					);
				}
				else if constexpr (std::is_same_v<register_type_uq, __m512>)
				{
					__m128 chunks_[4] =
					{
						_mm512_extractf32x4_ps(register_, 0),
						_mm512_extractf32x4_ps(register_, 1),
						_mm512_extractf32x4_ps(register_, 2),
						_mm512_extractf32x4_ps(register_, 3)
					};
					chunks_[0] = _mm_add_ps(chunks_[0], chunks_[1]);
					chunks_[0] = _mm_add_ps(chunks_[0], chunks_[2]);
					return _mm512_castps128_ps512
					(
						horizontal_sum(_mm_add_ps(chunks_[0], chunks_[3]))
					);
				}
				else if constexpr (std::is_same_v<register_type_uq, __m128d>)
				{
					return _mm_add_ps(register_, _underlying_simd_helpers::_execute_shuffle<0, 1>(register_));
				}
				else if constexpr (std::is_same_v<register_type_uq, __m256d>)
				{
					return _mm256_castpd128_pd256
					(
						horizontal_sum
						(
							_mm_add_pd
							(
								_mm256_extractf128_pd(register_, 0),
								_mm256_extractf128_pd(register_, 1)
							)
						)
					);
				}
				else if constexpr (std::is_same_v<register_type_uq, __m512d>)
				{
					__m128d chunks_[4] =
					{
						_mm512_extractf64x2_pd(register_, 0),
						_mm512_extractf64x2_pd(register_, 1),
						_mm512_extractf64x2_pd(register_, 2),
						_mm512_extractf64x2_pd(register_, 3)
					};
					chunks_[0] = _mm_add_pd(chunks_[0], chunks_[1]);
					chunks_[0] = _mm_add_pd(chunks_[0], chunks_[2]);
					return _mm512_castpd128_pd512
					(
						horizontal_sum(_mm_add_pd(chunks_[0], chunks_[3]))
					);
				}
				else
				{
					static_assert(false, "Attempted to perform EmuMath::SIMD::horizontal_sum, but the the provided floating-point SIMD register type is unsupported for this operation.");
				}
			}
			else if constexpr (EmuMath::SIMD::TMP::is_integral_simd_register_v<register_type_uq>)
			{
				if constexpr (EmuMath::SIMD::TMP::_assert_valid_simd_int_element_width<PerElementWidthIfInt_>())
				{
					if constexpr (std::is_same_v<register_type_uq, __m128i>)
					{
						if constexpr (PerElementWidthIfInt_ == 8)
						{
							__m128i out_ = _mm_add_epi8(register_, _underlying_simd_helpers::_execute_shuffle<2, 3, 0, 1>(register_));
							out_ = _mm_add_epi8(out_, _underlying_simd_helpers::_execute_shuffle<3, 2, 3, 2>(out_));
							out_ = _mm_add_epi8(out_, _mm_shufflelo_epi16(out_, _underlying_simd_helpers::_shuffle_mask<__m128i, 1, 0, 3, 2>::get()));
							return _mm_add_epi8
							(
								out_,
								_mm_shuffle_epi8(out_, _underlying_simd_helpers::_shuffle_mask<__m128i, 1, 0, 3, 2, 5, 4, 7, 6, 9, 8, 11, 10, 13, 12, 14, 15>::get())
							);
						}
						else if constexpr (PerElementWidthIfInt_ == 16)
						{
							__m128i out_ = _mm_add_epi16(register_, _underlying_simd_helpers::_execute_shuffle<2, 3, 0, 1>(register_));
							out_ = _mm_add_epi16(out_, _underlying_simd_helpers::_execute_shuffle<3, 2, 3, 2>(out_));
							return _mm_add_epi16(out_, _mm_shufflelo_epi16(out_, _underlying_simd_helpers::_shuffle_mask<__m128i, 1, 0, 3, 2>::get()));
						}
						else if constexpr (PerElementWidthIfInt_ == 32)
						{
							__m128i out_ = _mm_add_epi32(register_, _underlying_simd_helpers::_execute_shuffle<2, 3, 0, 1>(register_));
							return _mm_add_epi32(out_, _underlying_simd_helpers::_execute_shuffle<3, 0, 3, 2>(out_));
						}
						else
						{
							return _mm_add_epi64(register_, _underlying_simd_helpers::_execute_shuffle<2, 3, 0, 1>(register_));
						}
					}
					else if constexpr (std::is_same_v<register_type_uq, __m256i>)
					{
						__m128i lo_ = _mm256_extracti128_si256(register_, 0);
						__m128i hi_ = _mm256_extracti128_si256(register_, 1);
						return _mm256_castsi128_si256
						(
							horizontal_sum<PerElementWidthIfInt_>
							(
								_underlying_simd_helpers::_add_int<PerElementWidthIfInt_>(lo_, hi_)
							)
						);
					}
					else if constexpr (std::is_same_v<register_type_uq, __m512i>)
					{
						__m128i chunks_[4] =
						{
							_mm256_extracti128_si256(register_, 0),
							_mm256_extracti128_si256(register_, 1),
							_mm256_extracti128_si256(register_, 2),
							_mm256_extracti128_si256(register_, 3)
						};
						chunks_[0] = _underlying_simd_helpers::_add_int<PerElementWidthIfInt_>(chunks_[0], chunks_[1]);
						chunks_[0] = _underlying_simd_helpers::_add_int<PerElementWidthIfInt_>(chunks_[0], chunks_[2]);
						chunks_[0] = _underlying_simd_helpers::_add_int<PerElementWidthIfInt_>(chunks_[0], chunks_[3]);
						return _mm512_castsi128_si512(horizontal_sum<PerElementWidthIfInt_>(chunks_[0]));
					}
					else
					{
						static_assert(false, "Attempted to perform EmuMath::SIMD::horizontal_sum, but the provided integral SIMD register type is not supported for this operation.");
					}
				}
				else
				{
					static_assert(false, "Attempted to perform EmuMath::SIMD::horizontal_sum, but the provided bit width for each element within the passed integral SIMD register is invalid.");
				}
			}
			else
			{
				static_assert(false, "Attempted to perform EmuMath::SIMD::horizontal_sum, but the provided SIMD register type is unsupported for this operation.");
			}
		}
		else
		{
			static_assert(false, "Attempted to perform EmuMath::SIMD::horizontal_sum with an unsupported type as the passed Register_.");
		}
	}
	template<std::size_t PerElementWidthIfInt_ = 32, class Register_>
	[[nodiscard]] inline Register_ horizontal_sum_fill(Register_ register_)
	{
		using register_type_uq = typename EmuCore::TMPHelpers::remove_ref_cv<Register_>::type;
		if constexpr (EmuMath::SIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			if constexpr (std::is_same_v<register_type_uq, __m128>)
			{
				__m128 out_ = _mm_hadd_ps(register_, register_);
				return _mm_hadd_ps(out_, out_);
			}
			else if constexpr (std::is_same_v<register_type_uq, __m128d>)
			{
				return _underlying_simd_helpers::_execute_shuffle<0>(horizontal_sum(register_));
			}
			else if constexpr (std::is_same_v<register_type_uq, __m256>)
			{
				__m256 result_ = _underlying_simd_helpers::_cast<__m256>
				(
					_underlying_simd_helpers::_execute_shuffle<0>
					(
						_underlying_simd_helpers::_cast<__m128>(horizontal_sum(register_))
					)
				);
				return _mm256_permute2f128_ps(result_, result_, 0);
			}
			else if constexpr (std::is_same_v<register_type_uq, __m256d>)
			{
				__m256d result_ = _underlying_simd_helpers::_cast<__m256d>
				(
					_underlying_simd_helpers::_execute_shuffle<0>
					(
						_underlying_simd_helpers::_cast<__m128d>(horizontal_sum(register_))
					)
				);
				return _mm256_permute2f128_pd(result_, result_, 0);
			}
			else if constexpr (EmuCore::TMPHelpers::is_any_comparison_true<std::is_same, register_type_uq, __m128i, __m256i>::value)
			{
				if constexpr (EmuMath::SIMD::TMP::_assert_valid_simd_int_element_width<PerElementWidthIfInt_>())
				{
					return _underlying_simd_helpers::_set1<register_type_uq, PerElementWidthIfInt_>
					(
						_underlying_simd_helpers::_get_register_index<0, EmuCore::TMPHelpers::int_of_size_t<PerElementWidthIfInt_ / 8>>
						(
							horizontal_sum<PerElementWidthIfInt_>(register_)
						)
					);
				}
				else
				{
					static_assert(false, "Attempted to perform EmuMath::SIMD::horizontal_sum_fill with an integral SIMD register, but the provided bit-width per element is invalid.");
				}
			}
			else
			{
				static_assert(false, "Attempted to perform EmuMath::SIMD::horizontal_sum_fill with a SIMD register type that is not supported for this operation.");
			}
		}
		else
		{
			static_assert(false, "Attempted to perform EmuMath::SIMD::horizontal_sum_fill with an unsupported type as the passed Register_.");
		}
	}

	template<typename Out_, std::size_t PerElementWidthIfInt_ = 32, class Register_>
	[[nodiscard]] inline Out_ horizontal_sum_scalar(Register_ register_)
	{
		using register_type_uq = typename EmuCore::TMPHelpers::remove_ref_cv<Register_>::type;
		if constexpr (EmuMath::SIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			if constexpr (EmuMath::SIMD::TMP::is_floating_point_simd_register_v<register_type_uq>)
			{
				return _underlying_simd_helpers::_get_register_index<0, Out_, PerElementWidthIfInt_>
				(
					horizontal_sum(register_)
				);
			}
			else if constexpr (EmuMath::SIMD::TMP::is_integral_simd_register_v<register_type_uq>)
			{
				return _underlying_simd_helpers::_get_register_index<0, Out_, PerElementWidthIfInt_>
				(
					horizontal_sum<PerElementWidthIfInt_>(register_)
				);
			}
			else
			{
				static_assert(false, "Attempted to perform EmuMath::SIMD::horizontal_sum_scalar, but the provided SIMD register type is unsupported for this operation.");
			}
		}
		else
		{
			static_assert(false, "Attempted to perform EmuMath::SIMD::horizontal_sum_scalar with an unsupported type as the passed Register_.");
		}
	}

	template<std::size_t PerElementWidthIfInt_ = 32, class Register_>
	[[nodiscard]] inline Register_ dot(Register_ a_, Register_ b_)
	{
		using register_type_uq = typename EmuCore::TMPHelpers::remove_ref_cv<Register_>::type;
		if constexpr (EmuMath::SIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			if constexpr (EmuMath::SIMD::TMP::is_floating_point_simd_register_v<register_type_uq>)
			{
				return horizontal_sum(_underlying_simd_helpers::_mul_fp(a_, b_));
			}
			else if constexpr (EmuMath::SIMD::TMP::is_integral_simd_register_v<register_type_uq>)
			{
				return horizontal_sum<PerElementWidthIfInt_>(_underlying_simd_helpers::_mul_all_int<PerElementWidthIfInt_>(a_, b_));
			}
			else
			{
				static_assert(false, "Attempted to perform EmuMath::SIMD::dot, but the provided SIMD register type is unsupported for this operation.");
			}
		}
		else
		{
			static_assert(false, "Attempted to perform EmuMath::SIMD::dot with an unsupported type as the passed Register_.");
		}
	}

	template<typename Out_, std::size_t PerElementWidthIfInt_ = 32, class Register_>
	[[nodiscard]] inline Out_ dot_scalar(Register_ a_, Register_ b_)
	{
		using register_type_uq = typename EmuCore::TMPHelpers::remove_ref_cv<Register_>::type;
		if constexpr (EmuMath::SIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			if constexpr (EmuMath::SIMD::TMP::is_floating_point_simd_register_v<register_type_uq>)
			{
				return _underlying_simd_helpers::_get_register_index<0, Out_, PerElementWidthIfInt_>
				(
					horizontal_sum(_underlying_simd_helpers::_mul_fp(a_, b_))
				);
			}
			else if constexpr (EmuMath::SIMD::TMP::is_integral_simd_register_v<register_type_uq>)
			{
				return _underlying_simd_helpers::_get_register_index<0, Out_, PerElementWidthIfInt_>
				(
					horizontal_sum<PerElementWidthIfInt_>(_underlying_simd_helpers::_mul_all_int<PerElementWidthIfInt_>(a_, b_))
				);
			}
			else
			{
				static_assert(false, "Attempted to perform EmuMath::SIMD::dot_scalar, but the provided SIMD register type is unsupported for this operation.");
			}
		}
		else
		{
			static_assert(false, "Attempted to perform EmuMath::SIMD::dot_scalar with an unsupported type as the passed Register_.");
		}
	}

	template<std::size_t PerElementWidthIfInt_ = 32, class Register_>
	[[nodiscard]] inline Register_ dot_fill(Register_ a_, Register_ b_)
	{
		using register_type_uq = typename EmuCore::TMPHelpers::remove_ref_cv<Register_>::type;
		if constexpr (EmuMath::SIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			if constexpr (EmuMath::SIMD::TMP::is_floating_point_simd_register_v<register_type_uq>)
			{
				return horizontal_sum_fill(_underlying_simd_helpers::_mul_fp(a_, b_));
			}
			else if constexpr (EmuMath::SIMD::TMP::is_integral_simd_register_v<register_type_uq>)
			{
				return horizontal_sum_fill<PerElementWidthIfInt_>(_underlying_simd_helpers::_mul_all_int<PerElementWidthIfInt_>(a_, b_));
			}
			else
			{
				static_assert(false, "Attempted to perform EmuMath::SIMD::dot_fill, but the provided SIMD register type is unsupported for this operation.");
			}
		}
		else
		{
			static_assert(false, "Attempted to perform EmuMath::SIMD::dot_fill with an unsupported type as the passed Register_.");
		}
	}
}

#endif