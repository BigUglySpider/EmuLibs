#ifndef EMU_SIMD_HELPERS_TEMPLATE_COMMON_ARITHMETIC
#define EMU_SIMD_HELPERS_TEMPLATE_COMMON_ARITHMETIC 1

#include "_underlying_template_helpers/_all_underlying_templates.h"
#include "_simd_helpers_template_cast.h"
#include "_simd_helpers_template_gets.h"
#include "_simd_helpers_template_shuffles.h"
#include "../../../../EmuCore/TMPHelpers/Values.h"

namespace EmuSIMD
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
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			if constexpr (EmuSIMD::TMP::is_floating_point_simd_register_v<register_type_uq>)
			{
				register_type_uq b_minus_a_ = _underlying_simd_helpers::_sub_fp(b_, a_);
				return _underlying_simd_helpers::_add_fp(a_, _underlying_simd_helpers::_mul_fp(b_minus_a_, t_));
			}
			else if constexpr (EmuSIMD::TMP::is_integral_simd_register_v<register_type_uq>)
			{
				register_type_uq b_minus_a_ = _underlying_simd_helpers::_sub_int<PerElementWidthIfInt_>(b_, a_);
				return _underlying_simd_helpers::_add_int(a_, _underlying_simd_helpers::_mul_all_int<PerElementWidthIfInt_>(b_minus_a_, t_));
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform EmuSIMD::lerp, but the provided SIMD register type is unsupported for this operation.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform EmuSIMD::lerp with an unsupported type as the passed Register_.");
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
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			if constexpr (EmuSIMD::TMP::is_floating_point_simd_register_v<register_type_uq>)
			{
				return _underlying_simd_helpers::_fmadd_fp
				(
					_underlying_simd_helpers::_sub_fp(b_, a_),
					t_,
					a_
				);
			}
			else if constexpr (EmuSIMD::TMP::is_integral_simd_register_v<register_type_uq>)
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
				static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform EmuSIMD::lerp, but the provided SIMD register type is unsupported for this operation.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform EmuSIMD::lerp with an unsupported type as the passed Register_.");
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
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			using namespace EmuSIMD::Funcs;
			if constexpr (EmuSIMD::TMP::is_floating_point_simd_register_v<register_type_uq>)
			{
				if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x4>)
				{
					EmuSIMD::f32x4 shuffled_ = _underlying_simd_helpers::_execute_shuffle<1, 0, 3, 2>(register_);
					EmuSIMD::f32x4 out_ = _underlying_simd_helpers::_add_fp(register_, shuffled_);
					shuffled_ = _mm_movehl_ps(shuffled_, out_);
					return _mm_add_ss(out_, shuffled_);
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x8>)
				{
					return _mm256_castps128_ps256
					(
						horizontal_sum<32>
						(
							_mm_add_ps
							(
								_mm256_extractf128_ps(register_, 0),
								_mm256_extractf128_ps(register_, 1)
							)
						)
					);
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x16>)
				{
					EmuSIMD::f32x4 chunks_[4] =
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
						horizontal_sum<32>(_mm_add_ps(chunks_[0], chunks_[3]))
					);
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x2>)
				{
					return _mm_add_pd(register_, _underlying_simd_helpers::_execute_shuffle<1, 0>(register_));
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x4>)
				{
					return _mm256_castpd128_pd256
					(
						horizontal_sum<64>
						(
							_mm_add_pd
							(
								_mm256_extractf128_pd(register_, 0),
								_mm256_extractf128_pd(register_, 1)
							)
						)
					);
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x8>)
				{
					EmuSIMD::f64x2 chunks_[4] =
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
						horizontal_sum<64>(_mm_add_pd(chunks_[0], chunks_[3]))
					);
				}
				else
				{
					static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform EmuSIMD::horizontal_sum, but the the provided floating-point SIMD register type is unsupported for this operation.");
				}
			}
			else if constexpr (EmuSIMD::TMP::is_integral_simd_register_v<register_type_uq>)
			{
				if constexpr (EmuSIMD::TMP::_assert_valid_simd_int_element_width<PerElementWidthIfInt_>())
				{
					if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i128_generic>)
					{
						if constexpr (PerElementWidthIfInt_ == 8)
						{
							EmuSIMD::i128_generic out_ = _mm_add_epi8(register_, _underlying_simd_helpers::_execute_shuffle<2, 3, 0, 1>(register_));
							out_ = add_i8x16(out_, _underlying_simd_helpers::_execute_shuffle<3, 2, 3, 2>(out_));

							constexpr auto shuffle_mask = make_shuffle_mask_32<2, 3, 0, 1>();
							out_ = add_i8x16(out_, _mm_shufflelo_epi16(out_, shuffle_mask));
							return add_i8x16
							(
								out_,
								//_mm_shuffle_epi8(out_, _underlying_simd_helpers::_shuffle_mask<EmuSIMD::i128_generic, 1, 0, 3, 2, 5, 4, 7, 6, 9, 8, 11, 10, 13, 12, 14, 15>::get()), // REMOVED, COMMENTED FOR ARCHIVAL PURPOSES
								EmuSIMD::Funcs::permute_i8x16<make_shuffle_mask_8<15, 14, 12, 13, 10, 11, 8, 9, 6, 7, 4, 5, 2, 3, 0, 1>()>(out_)
							);
						}
						else if constexpr (PerElementWidthIfInt_ == 16)
						{
							EmuSIMD::i128_generic out_ = _mm_add_epi16(register_, _underlying_simd_helpers::_execute_shuffle<2, 3, 0, 1>(register_));
							out_ = _mm_add_epi16(out_, _underlying_simd_helpers::_execute_shuffle<3, 2, 3, 2>(out_));
							// return _mm_add_epi16(out_, _mm_shufflelo_epi16(out_, _underlying_simd_helpers::_shuffle_mask<EmuSIMD::i128_generic, 1, 0, 3, 2>::get())); // REMOVED, COMMENTED FOR ARCHIVAL PURPOSES
							return add_i16x8(out_, _mm_shufflelo_epi16(out_, make_shuffle_mask_32<2, 3, 0, 1>()));
						}
						else if constexpr (PerElementWidthIfInt_ == 32)
						{
							EmuSIMD::i128_generic out_ = add_i32x4(register_, _underlying_simd_helpers::_execute_shuffle<2, 3, 0, 1>(register_));
							return add_i32x4(out_, _underlying_simd_helpers::_execute_shuffle<3, 0, 3, 2>(out_));
						}
						else
						{
							return add_i64x2(register_, _underlying_simd_helpers::_execute_shuffle<2, 3, 0, 1>(register_));
						}
					}
					else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i256_generic>)
					{
						EmuSIMD::i128_generic lo_ = _mm256_extracti128_si256(register_, 0);
						EmuSIMD::i128_generic hi_ = _mm256_extracti128_si256(register_, 1);
						return _mm256_castsi128_si256
						(
							horizontal_sum<PerElementWidthIfInt_>
							(
								_underlying_simd_helpers::_add_int<PerElementWidthIfInt_>(lo_, hi_)
							)
						);
					}
					else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i512_generic>)
					{
						EmuSIMD::i128_generic chunks_[4] =
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
						static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform EmuSIMD::horizontal_sum, but the provided integral SIMD register type is not supported for this operation.");
					}
				}
				else
				{
					static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform EmuSIMD::horizontal_sum, but the provided bit width for each element within the passed integral SIMD register is invalid.");
				}
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform EmuSIMD::horizontal_sum, but the provided SIMD register type is unsupported for this operation.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform EmuSIMD::horizontal_sum with an unsupported type as the passed Register_.");
		}
	}
	template<std::size_t PerElementWidthIfInt_ = 32, class Register_>
	[[nodiscard]] inline Register_ horizontal_sum_fill(Register_ register_)
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x4>)
			{
				EmuSIMD::f32x4 out_ = _mm_hadd_ps(register_, register_);
				return _mm_hadd_ps(out_, out_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x2>)
			{
				return _underlying_simd_helpers::_execute_shuffle<0>(horizontal_sum(register_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x8>)
			{
				EmuSIMD::f32x8 result_ = _underlying_simd_helpers::_cast<EmuSIMD::f32x8>
				(
					_underlying_simd_helpers::_execute_shuffle<0>
					(
						_underlying_simd_helpers::_cast<EmuSIMD::f32x4>(horizontal_sum(register_))
					)
				);
				return _mm256_permute2f128_ps(result_, result_, 0);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x4>)
			{
				EmuSIMD::f64x4 result_ = _underlying_simd_helpers::_cast<EmuSIMD::f64x4>
				(
					_underlying_simd_helpers::_execute_shuffle<0>
					(
						_underlying_simd_helpers::_cast<EmuSIMD::f64x2>(horizontal_sum(register_))
					)
				);
				return _mm256_permute2f128_pd(result_, result_, 0);
			}
			else if constexpr (EmuCore::TMP::is_any_comparison_true<std::is_same, register_type_uq, EmuSIMD::i128_generic, EmuSIMD::i256_generic>::value)
			{
				if constexpr (EmuSIMD::TMP::_assert_valid_simd_int_element_width<PerElementWidthIfInt_>())
				{
					return _underlying_simd_helpers::_set1<register_type_uq, PerElementWidthIfInt_>
					(
						_underlying_simd_helpers::_get_register_index<0, EmuCore::TMP::int_of_size_t<PerElementWidthIfInt_ / 8>>
						(
							horizontal_sum<PerElementWidthIfInt_>(register_)
						)
					);
				}
				else
				{
					static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform EmuSIMD::horizontal_sum_fill with an integral SIMD register, but the provided bit-width per element is invalid.");
				}
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform EmuSIMD::horizontal_sum_fill with a SIMD register type that is not supported for this operation.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform EmuSIMD::horizontal_sum_fill with an unsupported type as the passed Register_.");
		}
	}

	template<typename Out_, std::size_t PerElementWidthIfInt_ = 32, class Register_>
	[[nodiscard]] inline Out_ horizontal_sum_scalar(Register_ register_)
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			if constexpr (EmuSIMD::TMP::is_floating_point_simd_register_v<register_type_uq>)
			{
				return _underlying_simd_helpers::_get_register_index<0, Out_, PerElementWidthIfInt_>
				(
					horizontal_sum(register_)
				);
			}
			else if constexpr (EmuSIMD::TMP::is_integral_simd_register_v<register_type_uq>)
			{
				return _underlying_simd_helpers::_get_register_index<0, Out_, PerElementWidthIfInt_>
				(
					horizontal_sum<PerElementWidthIfInt_>(register_)
				);
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform EmuSIMD::horizontal_sum_scalar, but the provided SIMD register type is unsupported for this operation.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform EmuSIMD::horizontal_sum_scalar with an unsupported type as the passed Register_.");
		}
	}

	template<std::size_t PerElementWidthIfInt_ = 32, class Register_>
	[[nodiscard]] inline Register_ dot(Register_ a_, Register_ b_)
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			if constexpr (EmuSIMD::TMP::is_floating_point_simd_register_v<register_type_uq>)
			{
				return horizontal_sum(_underlying_simd_helpers::_mul_fp(a_, b_));
			}
			else if constexpr (EmuSIMD::TMP::is_integral_simd_register_v<register_type_uq>)
			{
				return horizontal_sum<PerElementWidthIfInt_>(_underlying_simd_helpers::_mul_all_int<PerElementWidthIfInt_>(a_, b_));
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform EmuSIMD::dot, but the provided SIMD register type is unsupported for this operation.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform EmuSIMD::dot with an unsupported type as the passed Register_.");
		}
	}

	template<typename Out_, std::size_t PerElementWidthIfInt_ = 32, class Register_>
	[[nodiscard]] inline Out_ dot_scalar(Register_ a_, Register_ b_)
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			if constexpr (EmuSIMD::TMP::is_floating_point_simd_register_v<register_type_uq>)
			{
				return _underlying_simd_helpers::_get_register_index<0, Out_, PerElementWidthIfInt_>
				(
					horizontal_sum(_underlying_simd_helpers::_mul_fp(a_, b_))
				);
			}
			else if constexpr (EmuSIMD::TMP::is_integral_simd_register_v<register_type_uq>)
			{
				return _underlying_simd_helpers::_get_register_index<0, Out_, PerElementWidthIfInt_>
				(
					horizontal_sum<PerElementWidthIfInt_>(_underlying_simd_helpers::_mul_all_int<PerElementWidthIfInt_>(a_, b_))
				);
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform EmuSIMD::dot_scalar, but the provided SIMD register type is unsupported for this operation.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform EmuSIMD::dot_scalar with an unsupported type as the passed Register_.");
		}
	}

	template<std::size_t PerElementWidthIfInt_ = 32, class Register_>
	[[nodiscard]] inline Register_ dot_fill(Register_ a_, Register_ b_)
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			if constexpr (EmuSIMD::TMP::is_floating_point_simd_register_v<register_type_uq>)
			{
				return horizontal_sum_fill(_underlying_simd_helpers::_mul_fp(a_, b_));
			}
			else if constexpr (EmuSIMD::TMP::is_integral_simd_register_v<register_type_uq>)
			{
				return horizontal_sum_fill<PerElementWidthIfInt_>(_underlying_simd_helpers::_mul_all_int<PerElementWidthIfInt_>(a_, b_));
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform EmuSIMD::dot_fill, but the provided SIMD register type is unsupported for this operation.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform EmuSIMD::dot_fill with an unsupported type as the passed Register_.");
		}
	}
}

#endif