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
		// TODO
		if constexpr (EmuSIMD::TMP::is_simd_register_v<Register_>)
		{
			using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
			using shuffle_mask_inst = EmuSIMD::_underlying_simd_helpers::_shuffle_mask<register_type_uq, Indices_...>;
			if constexpr (true)
			{
				if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x4>)
				{
					return _mm_shuffle_ps(a_, b_, shuffle_mask_inst::get());
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x8>)
				{
					return _mm256_shuffle_ps(a_, b_, shuffle_mask_inst::get());
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x16>)
				{
					return _mm512_shuffle_ps(a_, b_, shuffle_mask_inst::get());
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x2>)
				{
					return _mm_shuffle_pd(a_, b_, shuffle_mask_inst::get());
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x4>)
				{
					return _mm256_shuffle_pd(a_, b_, shuffle_mask_inst::get());
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x8>)
				{
					return _mm512_shuffle_pd(a_, b_, shuffle_mask_inst::get());
				}
				else if constexpr (EmuCore::TMP::is_any_comparison_true<std::is_same, register_type_uq, EmuSIMD::i128_generic, EmuSIMD::i256_generic, EmuSIMD::i512_generic>::value)
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
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			if constexpr (EmuSIMD::TMP::is_floating_point_simd_register_v<register_type_uq>)
			{
				using namespace EmuSIMD::Funcs;
				constexpr std::size_t num_register_indices = EmuSIMD::TMP::register_element_count_v<register_type_uq>;
				constexpr std::size_t per_element_width = EmuSIMD::TMP::floating_point_register_element_width_v<register_type_uq>;
				static_assert(per_element_width != 0, "Error executing templatised floating-point SIMD shuffle: per_element_width is 0, meaning that the passed register type is unsupported.");

				constexpr std::size_t num_index_args = sizeof...(Indices_);
				constexpr std::size_t expected_num_index_args = per_element_width == 32 ? 4 : num_register_indices;

				if constexpr (num_index_args == expected_num_index_args)
				{
					if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x4>)
					{
						constexpr auto determined_mask = make_reverse_shuffle_mask_32<Indices_...>();
						return permute_f32x4<determined_mask>(ab_);
					}
					else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x8>)
					{
						constexpr auto determined_mask = make_reverse_shuffle_mask_32<Indices_...>();
						return permute_f32x8<determined_mask>(ab_);
					}
					else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x16>)
					{
						constexpr auto determined_mask = make_reverse_shuffle_mask_32<Indices_...>();
						return permute_f32x16<determined_mask>(ab_);
					}
					else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x2>)
					{
						constexpr auto determined_mask = make_reverse_shuffle_mask_64<Indices_...>();
						return permute_f64x2<determined_mask>(ab_);
					}
					else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x4>)
					{
						constexpr auto determined_mask = make_reverse_shuffle_mask_64<0>();
						return permute_f64x4<determined_mask>(ab_);
					}
					else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x8>)
					{
						constexpr auto determined_mask = make_reverse_shuffle_mask_64<Indices_...>();
						return permute_f64x8<determined_mask>(ab_);
					}
					else
					{
						static_assert(EmuCore::TMP::get_false<Register_>(), "Error executing templatised floating-point SIMD shuffle: The passed floating-point register type is not supported for this operation.");
					}
				}
				else if constexpr(num_index_args == 1)
				{
					// Support for shuffling all to a single index
					if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x4>)
					{
						constexpr auto determined_mask = make_looping_shuffle_mask_32x4<Indices_...>();
						return permute_f32x4<determined_mask>(ab_);
					}
					else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x8>)
					{
						constexpr auto determined_mask = make_looping_shuffle_mask_32x4<Indices_...>();
						return permute_f32x8<determined_mask>(ab_);
					}
					else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x16>)
					{
						constexpr auto determined_mask = make_looping_shuffle_mask_32x4<Indices_...>();
						return permute_f32x16<determined_mask>(ab_);
					}
					else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x2>)
					{
						constexpr auto determined_mask = make_looping_shuffle_mask_64x2<Indices_...>();
						return permute_f64x2<determined_mask>(ab_);
					}
					else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x4>)
					{
						constexpr auto determined_mask = make_looping_shuffle_mask_64x4<0>();
						return permute_f64x4<determined_mask>(ab_);
					}
					else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x8>)
					{
						constexpr auto determined_mask = make_looping_shuffle_mask_64x8<Indices_...>();
						return permute_f64x8<determined_mask>(ab_);
					}
					else
					{
						static_assert(EmuCore::TMP::get_false<Register_>(), "Error executing templatised floating-point SIMD shuffle with a single index argument: The passed floating-point register type is not supported for this operation.");
					}
				}
				else if constexpr (num_index_args == 2 && per_element_width == 64)
				{
					// Support for formatting 64-bit shuffle masks in the same way as a 32-bit shuffle mask (i.e. same number of index args for any register width)
					if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x2>)
					{
						constexpr auto determined_mask = make_reverse_shuffle_mask_64x2<Indices_...>();
						return permute_f64x2<determined_mask>(ab_);
					}
					else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x4>)
					{
						constexpr auto determined_mask = make_reverse_shuffle_mask_64x4<Indices_...>();
						return permute_f64x4<determined_mask>(ab_);
					}
					else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x8>)
					{
						constexpr auto determined_mask = make_reverse_shuffle_mask_64x8<Indices_...>();
						return permute_f64x8<determined_mask>(ab_);
					}
					else
					{
						static_assert(EmuCore::TMP::get_false<Register_>(), "Error executing templatised 64-bit-floating-point SIMD shuffle with two index arguments: The passed 64-bit-floating-point register type is not supported for this operation.");
					}
				}
				else
				{
					static_assert(EmuCore::TMP::get_false<std::size_t, num_index_args>(), "Error executing templatised EmuSIMD shuffle: attempted to shuffle a floating-point register with a number of elements not equal to either the number of elements in the register, or 1.");
				}
			} // END OF FLOATING-POINT SHUFFLE HANDLING
			else
			{
				// START OF INTEGRAL SHUFFLE HANDLING
				// --- TODO
				using shuffle_mask_inst = EmuSIMD::_underlying_simd_helpers::_shuffle_mask<register_type_uq, Indices_...>;
				if constexpr (EmuSIMD::_underlying_simd_helpers::is_valid_shuffle_mask_instance<shuffle_mask_inst>::value)
				{
					constexpr std::size_t num_indices_ = sizeof...(Indices_);
					constexpr bool is_8bit_shuffle_ = num_indices_ > 4;
					if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i128_generic>)
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
					else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i256_generic>)
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
					else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i512_generic>)
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
	[[nodiscard]] inline EmuSIMD::f32x4 _execute_shuffle<0, 0, 2, 2>(EmuSIMD::f32x4 ab_)
	{
		return _mm_moveldup_ps(ab_);
	}

	template<>
	[[nodiscard]] inline EmuSIMD::f32x4 _execute_shuffle<1, 1, 3, 3>(EmuSIMD::f32x4 ab_)
	{
		return _mm_movehdup_ps(ab_);
	}

	template<>
	[[nodiscard]] inline EmuSIMD::f32x4 _execute_shuffle<0, 1, 0, 1>(EmuSIMD::f32x4 ab_)
	{
		return _mm_movelh_ps(ab_, ab_);
	}
	template<>
	[[nodiscard]] inline EmuSIMD::f32x4 _execute_shuffle<0, 1, 0, 1>(EmuSIMD::f32x4 a_, EmuSIMD::f32x4 b_)
	{
		return _mm_movelh_ps(a_, b_);
	}

	template<>
	[[nodiscard]] inline EmuSIMD::f32x4 _execute_shuffle<2, 3, 2, 3>(EmuSIMD::f32x4 ab_)
	{
		return _mm_movehl_ps(ab_, ab_);
	}
	template<>
	[[nodiscard]] inline EmuSIMD::f32x4 _execute_shuffle<2, 3, 2, 3>(EmuSIMD::f32x4 a_, EmuSIMD::f32x4 b_)
	{
		return _mm_movehl_ps(b_, a_);
	}

	template<>
	[[nodiscard]] inline EmuSIMD::f32x4 _execute_shuffle<0, 1, 2, 3>(EmuSIMD::f32x4 ab_)
	{
		return ab_;
	}
#pragma endregion

#pragma region M128D_SPECIALISATIONS
	template<>
	[[nodiscard]] inline EmuSIMD::f64x2 _execute_shuffle<0, 0>(EmuSIMD::f64x2 ab_)
	{
		return _mm_movedup_pd(ab_);
	}

	template<>
	[[nodiscard]] inline EmuSIMD::f64x2 _execute_shuffle<0, 1>(EmuSIMD::f64x2 ab_)
	{
		return ab_;
	}
#pragma endregion

#pragma region M128I_SPECIALISATIONS
	template<>
	[[nodiscard]] inline EmuSIMD::i128_generic _execute_shuffle<0, 1, 2, 3>(EmuSIMD::i128_generic ab_)
	{
		return ab_;
	}

	template<>
	[[nodiscard]] inline EmuSIMD::i128_generic _execute_shuffle<0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15>(EmuSIMD::i128_generic ab_)
	{
		return ab_;
	}
#pragma endregion
}

#endif
