#ifndef EMU_SIMD_HELPERS_UNDERLYING_SHUFFLE_H_INC_
#define EMU_SIMD_HELPERS_UNDERLYING_SHUFFLE_H_INC_ 1

#include "_common_underlying_simd_template_helper_includes.h"
#include "_simd_helpers_underlying_shuffle_masks.h"
#include "../../../../../EmuCore/TMPHelpers/Values.h"

namespace EmuSIMD::_underlying_simd_helpers
{
	template<std::size_t...Indices_, class Register_>
	[[nodiscard]] inline Register_ _execute_shuffle(Register_ a_, Register_ b_)
	{
		if constexpr (EmuSIMD::TMP::is_simd_register_v<Register_>)
		{
			using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
			using shuffle_mask_inst = EmuSIMD::_underlying_simd_helpers::_shuffle_mask<register_type_uq, Indices_...>;
			if constexpr (EmuSIMD::_underlying_simd_helpers::is_valid_shuffle_mask_instance<shuffle_mask_inst>::value)
			{
				if constexpr (std::is_same_v<register_type_uq, __m128>)
				{
					return _mm_shuffle_ps(a_, b_, shuffle_mask_inst::get());
				}
				else if constexpr (std::is_same_v<register_type_uq, __m256>)
				{
					return _mm256_shuffle_ps(a_, b_, shuffle_mask_inst::get());
				}
				else if constexpr (std::is_same_v<register_type_uq, __m512>)
				{
					return _mm512_shuffle_ps(a_, b_, shuffle_mask_inst::get());
				}
				else if constexpr (std::is_same_v<register_type_uq, __m128d>)
				{
					return _mm_shuffle_pd(a_, b_, shuffle_mask_inst::get());
				}
				else if constexpr (std::is_same_v<register_type_uq, __m256d>)
				{
					return _mm256_shuffle_pd(a_, b_, shuffle_mask_inst::get());
				}
				else if constexpr (std::is_same_v<register_type_uq, __m512d>)
				{
					return _mm512_shuffle_pd(a_, b_, shuffle_mask_inst::get());
				}
				else if constexpr (EmuCore::TMP::is_any_comparison_true<std::is_same, register_type_uq, __m128i, __m256i, __m512i>::value)
				{
					static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to shuffle 2 integral SIMD registers using EmuSIMD helpers, but only one integral register may be shuffled.");
				}
				else
				{
					static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to shuffle SIMD registers using EmuSIMD helpers, but the provided Register_ types are unsupported.");
				}
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to shuffle SIMD registers using EmuSIMD helpers, but the provided indices did not form a valid shuffle mask template for the provided register type.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to shuffle SIMD registers using EmuSIMD helpers, but the provided Register_ type was not a supported SIMD register type.");
		}
	}
	template<std::size_t...Indices_, class Register_>
	[[nodiscard]] inline Register_ _execute_shuffle(Register_ ab_)
	{
		if constexpr (EmuSIMD::TMP::is_simd_register_v<Register_>)
		{
			using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
			if constexpr (EmuSIMD::TMP::is_floating_point_simd_register_v<register_type_uq>)
			{
				return _execute_shuffle<Indices_...>(ab_, ab_);
			}
			else
			{
				using shuffle_mask_inst = EmuSIMD::_underlying_simd_helpers::_shuffle_mask<register_type_uq, Indices_...>;
				if constexpr (EmuSIMD::_underlying_simd_helpers::is_valid_shuffle_mask_instance<shuffle_mask_inst>::value)
				{
					constexpr std::size_t num_indices_ = sizeof...(Indices_);
					constexpr bool is_8bit_shuffle_ = num_indices_ > 4;
					if constexpr (std::is_same_v<register_type_uq, __m128i>)
					{
						if constexpr (is_8bit_shuffle_)
						{
							return _mm_shuffle_epi8(ab_, shuffle_mask_inst::get());
						}
						else
						{
							return _mm_shuffle_epi32(ab_, shuffle_mask_inst::get());
						}
					}
					else if constexpr (std::is_same_v<register_type_uq, __m256i>)
					{
						if constexpr (is_8bit_shuffle_)
						{
							return _mm256_shuffle_epi8(ab_, shuffle_mask_inst::get());
						}
						else
						{
							return _mm256_shuffle_epi32(ab_, shuffle_mask_inst::get());
						}
					}
					else if constexpr (std::is_same_v<register_type_uq, __m512i>)
					{
						if constexpr (is_8bit_shuffle_)
						{
							return _mm512_shuffle_epi8(ab_, shuffle_mask_inst::get());
						}
						else
						{
							return _mm512_shuffle_epi32(ab_, shuffle_mask_inst::get());
						}
					}
					else
					{
						static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to shuffle a SIMD register using EmuSIMD helpers, but the provided Register_ type is unsupported.");
					}
				}
				else
				{
					static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to shuffle a SIMD register using EmuSIMD helpers, but the provided indices did not form a valid shuffle mask template for the provided register type.");
				}
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to shuffle a SIMD register using EmuSIMD helpers, but the provided Register_ type was not a supported SIMD register type.");
		}
	}

#pragma region M128_SPECIALISATIONS
	template<>
	[[nodiscard]] inline __m128 _execute_shuffle<0, 0, 2, 2>(__m128 ab_)
	{
		return _mm_moveldup_ps(ab_);
	}

	template<>
	[[nodiscard]] inline __m128 _execute_shuffle<1, 1, 3, 3>(__m128 ab_)
	{
		return _mm_movehdup_ps(ab_);
	}

	template<>
	[[nodiscard]] inline __m128 _execute_shuffle<0, 1, 0, 1>(__m128 ab_)
	{
		return _mm_movelh_ps(ab_, ab_);
	}
	template<>
	[[nodiscard]] inline __m128 _execute_shuffle<0, 1, 0, 1>(__m128 a_, __m128 b_)
	{
		return _mm_movelh_ps(a_, b_);
	}

	template<>
	[[nodiscard]] inline __m128 _execute_shuffle<2, 3, 2, 3>(__m128 ab_)
	{
		return _mm_movehl_ps(ab_, ab_);
	}
	template<>
	[[nodiscard]] inline __m128 _execute_shuffle<2, 3, 2, 3>(__m128 a_, __m128 b_)
	{
		return _mm_movehl_ps(b_, a_);
	}

	template<>
	[[nodiscard]] inline __m128 _execute_shuffle<0, 1, 2, 3>(__m128 ab_)
	{
		return ab_;
	}
#pragma endregion

#pragma region M128D_SPECIALISATIONS
	template<>
	[[nodiscard]] inline __m128d _execute_shuffle<0, 0>(__m128d ab_)
	{
		return _mm_movedup_pd(ab_);
	}

	template<>
	[[nodiscard]] inline __m128d _execute_shuffle<0, 1>(__m128d ab_)
	{
		return ab_;
	}

	template<>
	[[nodiscard]] inline __m128d _execute_shuffle<1, 0>(__m128d a_, __m128d b_)
	{
		return _mm_move_sd(a_, b_);
	}
#pragma endregion

#pragma region M128I_SPECIALISATIONS
	template<>
	[[nodiscard]] inline __m128i _execute_shuffle<0, 1, 2, 3>(__m128i ab_)
	{
		return ab_;
	}

	template<>
	[[nodiscard]] inline __m128i _execute_shuffle<0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15>(__m128i ab_)
	{
		return ab_;
	}
#pragma endregion
}

#endif
