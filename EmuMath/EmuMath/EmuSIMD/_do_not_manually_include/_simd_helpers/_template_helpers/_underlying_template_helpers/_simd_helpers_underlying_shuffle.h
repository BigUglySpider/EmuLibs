#ifndef EMU_SIMD_HELPERS_UNDERLYING_SHUFFLE_H_INC_
#define EMU_SIMD_HELPERS_UNDERLYING_SHUFFLE_H_INC_ 1

#include "_common_underlying_simd_template_helper_includes.h"
#include "../../../../../EmuCore/TMPHelpers/Values.h"

namespace EmuSIMD::_underlying_simd_helpers
{
	template<EmuConcepts::KnownSIMD A_, EmuConcepts::UnqualifiedMatch<A_> B_, std::size_t...Indices_>
	struct _shuffler
	{
		template<EmuConcepts::UnqualifiedMatch<A_> RegisterA_, EmuConcepts::UnqualifiedMatch<B_> RegisterB_>
		[[nodiscard]] static constexpr inline auto execute(RegisterA_&& a_, RegisterB_&& b_)
			-> typename std::remove_cvref<RegisterA_>::type
		{
			constexpr bool struct_input_a_is_unqualified = std::is_same_v<A_, typename std::remove_cvref<A_>::type>;
			constexpr bool struct_input_b_is_unqualified = std::is_same_v<B_, typename std::remove_cvref<B_>::type>;
			if constexpr (!(struct_input_a_is_unqualified && struct_input_b_is_unqualified))
			{
				// Specialisation may exist, defer to ver. with unqualified arguments
				return _shuffler<typename std::remove_cvref<A_>::type, typename std::remove_cvref<B_>::type, Indices_...>::execute
				(
					std::forward<RegisterA_>(a_),
					std::forward<RegisterB_>(b_)
				);
			}
			else
			{
				// No deferrence needed, continue to execute default
				using register_type_uq = typename EmuCore::TMP::remove_ref_cv<RegisterA_>::type;
				if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
				{
					using namespace EmuSIMD::Funcs;
					constexpr std::size_t num_index_args = sizeof...(Indices_);
					if constexpr (EmuSIMD::TMP::is_floating_point_simd_register_v<register_type_uq>)
					{
						#pragma region FLOATING_POINT_2ARG_SHUFFLE
						constexpr std::size_t num_register_indices = EmuSIMD::TMP::register_element_count_v<register_type_uq>;
						constexpr std::size_t per_element_width = EmuSIMD::TMP::floating_point_register_element_width_v<register_type_uq>;
						static_assert(per_element_width != 0, "Error executing templatised floating-point SIMD shuffle: per_element_width is 0, meaning that the passed register type is unsupported.");

						constexpr std::size_t expected_num_index_args = per_element_width == 32 ? 4 : num_register_indices;

						if constexpr (num_index_args == expected_num_index_args)
						{
							if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x4>)
							{
								constexpr auto determined_mask = make_reverse_shuffle_mask_32<Indices_...>();
								return shuffle_f32x4<determined_mask>(a_, b_);
							}
							else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x8>)
							{
								constexpr auto determined_mask = make_reverse_shuffle_mask_32<Indices_...>();
								return shuffle_f32x8<determined_mask>(a_, b_);
							}
							else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x16>)
							{
								constexpr auto determined_mask = make_reverse_shuffle_mask_32<Indices_...>();
								return shuffle_f32x16<determined_mask>(a_, b_);
							}
							else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x2>)
							{
								constexpr auto determined_mask = make_reverse_shuffle_mask_64<Indices_...>();
								return shuffle_f64x2<determined_mask>(a_, b_);
							}
							else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x4>)
							{
								constexpr auto determined_mask = make_reverse_shuffle_mask_64<Indices_...>();
								return shuffle_f64x4<determined_mask>(a_, b_);
							}
							else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x8>)
							{
								constexpr auto determined_mask = make_reverse_shuffle_mask_64<Indices_...>();
								return shuffle_f64x8<determined_mask>(a_, b_);
							}
							else
							{
								static_assert(EmuCore::TMP::get_false<RegisterA_>(), "Error executing templatised floating-point SIMD shuffle: The passed floating-point register type is not supported for this operation.");
							}
						}
						else if constexpr(num_index_args == 1)
						{
							// Support for shuffling all to a single index
							if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x4>)
							{
								constexpr auto determined_mask = make_looping_shuffle_mask_32x4<Indices_...>();
								return shuffle_f32x4<determined_mask>(a_, b_);
							}
							else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x8>)
							{
								constexpr auto determined_mask = make_looping_shuffle_mask_32x4<Indices_...>();
								return shuffle_f32x8<determined_mask>(a_, b_);
							}
							else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x16>)
							{
								constexpr auto determined_mask = make_looping_shuffle_mask_32x4<Indices_...>();
								return shuffle_f32x16<determined_mask>(a_, b_);
							}
							else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x2>)
							{
								constexpr auto determined_mask = make_looping_shuffle_mask_64x2<Indices_...>();
								return shuffle_f64x2<determined_mask>(a_, b_);
							}
							else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x4>)
							{
								constexpr auto determined_mask = make_looping_shuffle_mask_64x4<Indices_...>();
								return shuffle_f64x4<determined_mask>(a_, b_);
							}
							else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x8>)
							{
								constexpr auto determined_mask = make_looping_shuffle_mask_64x8<Indices_...>();
								return shuffle_f64x8<determined_mask>(a_, b_);
							}
							else
							{
								static_assert(EmuCore::TMP::get_false<RegisterA_>(), "Error executing templatised floating-point SIMD shuffle with a single index argument: The passed floating-point register type is not supported for this operation.");
							}
						}
						else if constexpr (num_index_args == 2 && per_element_width == 64)
						{
							// Support for formatting 64-bit shuffle masks in the same way as a 32-bit shuffle mask (i.e. same number of index args for any register width)
							if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x2>)
							{
								constexpr auto determined_mask = make_reverse_shuffle_mask_64x2<Indices_...>();
								return shuffle_f64x2<determined_mask>(a_, b_);
							}
							else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x4>)
							{
								constexpr auto determined_mask = make_reverse_shuffle_mask_64x4<Indices_...>();
								return shuffle_f64x4<determined_mask>(a_, b_);
							}
							else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x8>)
							{
								constexpr auto determined_mask = make_reverse_shuffle_mask_64x8<Indices_...>();
								return shuffle_f64x8<determined_mask>(a_, b_);
							}
							else
							{
								static_assert(EmuCore::TMP::get_false<RegisterA_>(), "Error executing templatised 64-bit-floating-point SIMD shuffle with two index arguments: The passed 64-bit-floating-point register type is not supported for this operation.");
							}
						}
						else
						{
							static_assert(EmuCore::TMP::get_false<std::size_t, num_index_args>(), "Error executing templatised EmuSIMD shuffle: attempted to shuffle a floating-point register with a number of elements not equal to either the number of elements in the register, or 1.");
						}
						#pragma endregion
					} // END OF FLOATING-POINT SHUFFLE HANDLING
					else
					{
						#pragma region INTEGRAL_2ARG_SHUFFLE
						// START OF INTEGRAL SHUFFLE HANDLING
						// --- NOTE: Shuffles through this only take 128-bit lane masks; thus there is currently no support for e.g. 4-argument 64-bit shuffles in 256-bit registers, only 2-argument
						// --- This is the case even for when we know the register width, to provide a consistent interface that won't suddenly create uncompilable code when switching to an architecture which uses generic registers instead of named ones per-width.
						// ------ Additionally, no support for single-argument shuffle indices for similar reasons (i.e. cannot determine width from a single index arg with generic registers).
						if constexpr (EmuCore::TMP::is_any_same_v<register_type_uq, EmuSIMD::i128_generic, EmuSIMD::i256_generic, EmuSIMD::i512_generic>)
						{
							if constexpr (num_index_args == 2) // 64-bit
							{
								constexpr auto determined_mask = make_reverse_shuffle_mask_64<Indices_...>();
								return shuffle_i64x2<determined_mask>(a_, b_);
							}
							else if constexpr (num_index_args == 4) // 32-bit
							{
								constexpr auto determined_mask = make_reverse_shuffle_mask_32<Indices_...>();
								return shuffle_i32x4<determined_mask>(a_, b_);
							}
							else if constexpr (num_index_args == 8) // 16-bit
							{
								static_assert(EmuCore::TMP::get_false<RegisterA_>(), "NO SUPPORT ERROR: EmuSIMD does not provide support for shuffling 16-bit-element SIMD registers. As 8 index arguments have been provided with a generic 128-bit integral register, elements have been assumed as 16-bit.");
							}
							else if constexpr (num_index_args == 16) // 8-bit
							{
								constexpr auto determined_mask = make_reverse_shuffle_mask_8<Indices_...>();
								return shuffle_i8x16<determined_mask>(a_, b_);
							}
							else
							{
								static_assert(EmuCore::TMP::get_false<num_index_args>(), "Error executing templatised generic integral SIMD register shuffle: Invalid number of index arguments. The number of arguments for this register type must be equal to the number of elements within a 128-bit lane for the register. Valid values: 2 [64-bit], 4 [32-bit], 8 [16-bit, currently unsupported], 16 [8-bit].");
							}
						}
						else if constexpr (EmuCore::TMP::is_any_same_v<register_type_uq, EmuSIMD::i8x16, EmuSIMD::u8x16, EmuSIMD::i8x32, EmuSIMD::u8x32, EmuSIMD::i8x64, EmuSIMD::u8x64>)
						{
							if constexpr (num_index_args == 16)
							{
								constexpr auto determined_mask = make_reverse_shuffle_mask_8<Indices_...>();
								if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i8x16>)
								{
									return shuffle_i8x16<determined_mask>(a_, b_);
								}
								else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u8x16>)
								{
									return shuffle_u8x16<determined_mask>(a_, b_);
								}
								else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i8x32>)
								{
									return shuffle_i8x32<determined_mask>(a_, b_);
								}
								else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u8x32>)
								{
									return shuffle_u8x32<determined_mask>(a_, b_);
								}
								else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i8x64>)
								{
									return shuffle_i8x64<determined_mask>(a_, b_);
								}
								else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u8x64>)
								{
									return shuffle_u8x64<determined_mask>(a_, b_);
								}
								else
								{
									static_assert(EmuCore::TMP::get_false<RegisterA_>(), "INTERNAL EMUSIMD ERROR: Reached impossible point whilst instantiating template shuffle for an integral register of 8-bit elements.");
								}
							}
							else
							{
								static_assert(EmuCore::TMP::get_false<num_index_args>(), "Error executing templatised shuffle of an integral SIMD register with 8-bit elements: Invalid number of index arguments. The number of arguments must be equal to the number of elements within a 128-bit lane (16).");
							}
						}
						else if constexpr (EmuCore::TMP::is_any_same_v<register_type_uq, EmuSIMD::i16x8, EmuSIMD::u16x8, EmuSIMD::i16x16, EmuSIMD::u16x16, EmuSIMD::i16x32, EmuSIMD::u16x32>)
						{
							static_assert(EmuCore::TMP::get_false<RegisterA_>(), "NO SUPPORT ERROR: EmuSIMD does not provide support for permuting 16-bit-element SIMD registers. If you intend to use the passed register differently, cast it to the intended shuffle width before executing the shuffle.");
						}
						else if constexpr (EmuCore::TMP::is_any_same_v<register_type_uq, EmuSIMD::i32x4, EmuSIMD::u32x4, EmuSIMD::i32x8, EmuSIMD::u32x8, EmuSIMD::i32x16, EmuSIMD::u32x16>)
						{
							if constexpr (num_index_args == 4)
							{
								constexpr auto determined_mask = make_reverse_shuffle_mask_32<Indices_...>();
								if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i32x4>)
								{
									return shuffle_i32x4<determined_mask>(a_, b_);
								}
								else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u32x4>)
								{
									return shuffle_u32x4<determined_mask>(a_, b_);
								}
								else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i32x8>)
								{
									return shuffle_i32x8<determined_mask>(a_, b_);
								}
								else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u32x8>)
								{
									return shuffle_u32x8<determined_mask>(a_, b_);
								}
								else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i32x16>)
								{
									return shuffle_i32x16<determined_mask>(a_, b_);
								}
								else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u32x16>)
								{
									return shuffle_u32x16<determined_mask>(a_, b_);
								}
								else
								{
									static_assert(EmuCore::TMP::get_false<RegisterA_>(), "INTERNAL EMUSIMD ERROR: Reached impossible point whilst instantiating template shuffle for an integral register of 32-bit elements.");
								}
							}
							else
							{
								static_assert(EmuCore::TMP::get_false<num_index_args>(), "Error executing templatised shuffle of an integral SIMD register with 32-bit elements: Invalid number of index arguments. The number of arguments must be equal to the number of elements within a 128-bit lane (4).");
							}
						}
						else if constexpr (EmuCore::TMP::is_any_same_v<register_type_uq, EmuSIMD::i64x2, EmuSIMD::u64x2, EmuSIMD::i64x4, EmuSIMD::u64x4, EmuSIMD::i64x8, EmuSIMD::u64x8>)
						{
							if constexpr (num_index_args == 2)
							{
								if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i64x2>)
								{
									constexpr auto determined_mask = make_reverse_shuffle_mask_64x2<Indices_...>();
									return shuffle_i64x2<determined_mask>(a_, b_);
								}
								else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u64x2>)
								{
									constexpr auto determined_mask = make_reverse_shuffle_mask_64x2<Indices_...>();
									return shuffle_u64x2<determined_mask>(a_, b_);
								}
								else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i64x4>)
								{
									constexpr auto determined_mask = make_reverse_shuffle_mask_64x4<Indices_...>();
									return shuffle_i64x4<determined_mask>(a_, b_);
								}
								else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u64x4>)
								{
									constexpr auto determined_mask = make_reverse_shuffle_mask_64x4<Indices_...>();
									return shuffle_u64x4<determined_mask>(a_, b_);
								}
								else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i64x8>)
								{
									constexpr auto determined_mask = make_reverse_shuffle_mask_64x8<Indices_...>();
									return shuffle_i64x8<determined_mask>(a_, b_);
								}
								else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u64x8>)
								{
									constexpr auto determined_mask = make_reverse_shuffle_mask_64x8<Indices_...>();
									return shuffle_u64x8<determined_mask>(a_, b_);
								}
								else
								{
									static_assert(EmuCore::TMP::get_false<RegisterA_>(), "INTERNAL EMUSIMD ERROR: Reached impossible point whilst instantiating template shuffle for an integral register of 64-bit elements.");
								}
							}
							else
							{
								static_assert(EmuCore::TMP::get_false<num_index_args>(), "Error executing templatised shuffle of an integral SIMD register with 64-bit elements: Invalid number of index arguments. The number of arguments must be equal to the number of elements within a 128-bit lane (2).");
							}
						}
						else
						{
							static_assert(EmuCore::TMP::get_false<RegisterA_>(), "Error executing templatised integral SIMD register shuffle: The passed register type is not supported for this operation.");
						}
						#pragma endregion
					}
				}
				else
				{
					static_assert(EmuCore::TMP::get_false<RegisterA_>(), "Attempted to shuffle a SIMD register using EmuSIMD helpers, but the provided Register_ type was not a supported SIMD register type.");
				}
			}
		}
	};

	template<EmuConcepts::KnownSIMD AB_, std::size_t...Indices_>
	struct _permuter
	{
		template<EmuConcepts::UnqualifiedMatch<AB_> Register_>
		[[nodiscard]] static constexpr inline auto execute(Register_&& ab_)
			-> typename std::remove_cvref<Register_>::type
		{
			constexpr bool struct_input_is_unqualified = std::is_same_v<AB_, typename std::remove_cvref<AB_>::type>;
			if constexpr (!struct_input_is_unqualified)
			{
				// Specialisation may exist, defer to ver. with unqualified arguments
				return _permuter<typename std::remove_cvref<AB_>::type, Indices_...>::execute
				(
					std::forward<Register_>(ab_)
				);
			}
			else
			{
				// No deferrence needed, continue to execute default
				using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
				if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
				{
					using namespace EmuSIMD::Funcs;
					constexpr std::size_t num_index_args = sizeof...(Indices_);
					if constexpr (EmuSIMD::TMP::is_floating_point_simd_register_v<register_type_uq>)
					{
						#pragma region FLOATING_POINT_1ARG_SHUFFLE
						constexpr std::size_t num_register_indices = EmuSIMD::TMP::register_element_count_v<register_type_uq>;
						constexpr std::size_t per_element_width = EmuSIMD::TMP::floating_point_register_element_width_v<register_type_uq>;
						static_assert(per_element_width != 0, "Error executing templatised floating-point SIMD shuffle: per_element_width is 0, meaning that the passed register type is unsupported.");

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
								constexpr auto determined_mask = make_reverse_shuffle_mask_64<Indices_...>();
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
								constexpr auto determined_mask = make_looping_shuffle_mask_64x4<Indices_...>();
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
						#pragma endregion
					} // END OF FLOATING-POINT SHUFFLE HANDLING
					else
					{
						#pragma region INTEGRAL_1ARG_SHUFFLE
						// START OF INTEGRAL SHUFFLE HANDLING
						// --- NOTE: Shuffles through this only take 128-bit lane masks; thus there is currently no support for e.g. 4-argument 64-bit shuffles in 256-bit registers, only 2-argument
						// --- This is the case even for when we know the register width, to provide a consistent interface that won't suddenly create uncompilable code when switching to an architecture which uses generic registers instead of named ones per-width.
						// ------ Additionally, no support for single-argument shuffle indices for similar reasons (i.e. cannot determine width from a single index arg with generic registers).
						if constexpr (EmuCore::TMP::is_any_same_v<register_type_uq, EmuSIMD::i128_generic, EmuSIMD::i256_generic, EmuSIMD::i512_generic>)
						{
							if constexpr (num_index_args == 2) // 64-bit
							{
								constexpr auto determined_mask = make_reverse_shuffle_mask_64<Indices_...>();
								return permute_i64x2<determined_mask>(ab_);
							}
							else if constexpr (num_index_args == 4) // 32-bit
							{
								constexpr auto determined_mask = make_reverse_shuffle_mask_32<Indices_...>();
								return permute_i32x4<determined_mask>(ab_);
							}
							else if constexpr (num_index_args == 8) // 16-bit
							{
								static_assert(EmuCore::TMP::get_false<Register_>(), "NO SUPPORT ERROR: EmuSIMD does not provide support for permuting 16-bit-element SIMD registers. As 8 index arguments have been provided with a generic 128-bit integral register, elements have been assumed as 16-bit.");
							}
							else if constexpr (num_index_args == 16) // 8-bit
							{
								constexpr auto determined_mask = make_reverse_shuffle_mask_8<Indices_...>();
								return permute_i8x16<determined_mask>(ab_);
							}
							else
							{
								static_assert(EmuCore::TMP::get_false<num_index_args>(), "Error executing templatised generic integral SIMD register shuffle: Invalid number of index arguments. The number of arguments for this register type must be equal to the number of elements within a 128-bit lane for the register. Valid values: 2 [64-bit], 4 [32-bit], 8 [16-bit, currently unsupported], 16 [8-bit].");
							}
						}
						else if constexpr (EmuCore::TMP::is_any_same_v<register_type_uq, EmuSIMD::i8x16, EmuSIMD::u8x16, EmuSIMD::i8x32, EmuSIMD::u8x32, EmuSIMD::i8x64, EmuSIMD::u8x64>)
						{
							if constexpr (num_index_args == 16)
							{
								constexpr auto determined_mask = make_reverse_shuffle_mask_8<Indices_...>();
								if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i8x16>)
								{
									return permute_i8x16<determined_mask>(ab_);
								}
								else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u8x16>)
								{
									return permute_u8x16<determined_mask>(ab_);
								}
								else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i8x32>)
								{
									return permute_i8x32<determined_mask>(ab_);
								}
								else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u8x32>)
								{
									return permute_u8x32<determined_mask>(ab_);
								}
								else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i8x64>)
								{
									return permute_i8x64<determined_mask>(ab_);
								}
								else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u8x64>)
								{
									return permute_u8x64<determined_mask>(ab_);
								}
								else
								{
									static_assert(EmuCore::TMP::get_false<Register_>(), "INTERNAL EMUSIMD ERROR: Reached impossible point whilst instantiating template shuffle for an integral register of 8-bit elements.");
								}
							}
							else
							{
								static_assert(EmuCore::TMP::get_false<num_index_args>(), "Error executing templatised shuffle of an integral SIMD register with 8-bit elements: Invalid number of index arguments. The number of arguments must be equal to the number of elements within a 128-bit lane (16).");
							}
						}
						else if constexpr (EmuCore::TMP::is_any_same_v<register_type_uq, EmuSIMD::i16x8, EmuSIMD::u16x8, EmuSIMD::i16x16, EmuSIMD::u16x16, EmuSIMD::i16x32, EmuSIMD::u16x32>)
						{
							static_assert(EmuCore::TMP::get_false<Register_>(), "NO SUPPORT ERROR: EmuSIMD does not provide support for permuting 16-bit-element SIMD registers. If you intend to use the passed register differently, cast it to the intended shuffle width before executing the shuffle.");
						}
						else if constexpr (EmuCore::TMP::is_any_same_v<register_type_uq, EmuSIMD::i32x4, EmuSIMD::u32x4, EmuSIMD::i32x8, EmuSIMD::u32x8, EmuSIMD::i32x16, EmuSIMD::u32x16>)
						{
							if constexpr (num_index_args == 4)
							{
								constexpr auto determined_mask = make_reverse_shuffle_mask_32<Indices_...>();
								if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i32x4>)
								{
									return permute_i32x4<determined_mask>(ab_);
								}
								else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u32x4>)
								{
									return permute_u32x4<determined_mask>(ab_);
								}
								else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i32x8>)
								{
									return permute_i32x8<determined_mask>(ab_);
								}
								else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u32x8>)
								{
									return permute_u32x8<determined_mask>(ab_);
								}
								else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i32x16>)
								{
									return permute_i32x16<determined_mask>(ab_);
								}
								else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u32x16>)
								{
									return permute_u32x16<determined_mask>(ab_);
								}
								else
								{
									static_assert(EmuCore::TMP::get_false<Register_>(), "INTERNAL EMUSIMD ERROR: Reached impossible point whilst instantiating template shuffle for an integral register of 32-bit elements.");
								}
							}
							else
							{
								static_assert(EmuCore::TMP::get_false<num_index_args>(), "Error executing templatised shuffle of an integral SIMD register with 32-bit elements: Invalid number of index arguments. The number of arguments must be equal to the number of elements within a 128-bit lane (4).");
							}
						}
						else if constexpr (EmuCore::TMP::is_any_same_v<register_type_uq, EmuSIMD::i64x2, EmuSIMD::u64x2, EmuSIMD::i64x4, EmuSIMD::u64x4, EmuSIMD::i64x8, EmuSIMD::u64x8>)
						{
							if constexpr (num_index_args == 2)
							{
								if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i64x2>)
								{
									constexpr auto determined_mask = make_reverse_shuffle_mask_64x2<Indices_...>();
									return permute_i64x2<determined_mask>(ab_);
								}
								else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u64x2>)
								{
									constexpr auto determined_mask = make_reverse_shuffle_mask_64x2<Indices_...>();
									return permute_u64x2<determined_mask>(ab_);
								}
								else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i64x4>)
								{
									constexpr auto determined_mask = make_reverse_shuffle_mask_64x4<Indices_...>();
									return permute_i64x4<determined_mask>(ab_);
								}
								else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u64x4>)
								{
									constexpr auto determined_mask = make_reverse_shuffle_mask_64x4<Indices_...>();
									return permute_u64x4<determined_mask>(ab_);
								}
								else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i64x8>)
								{
									constexpr auto determined_mask = make_reverse_shuffle_mask_64x8<Indices_...>();
									return permute_i64x8<determined_mask>(ab_);
								}
								else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u64x8>)
								{
									constexpr auto determined_mask = make_reverse_shuffle_mask_64x8<Indices_...>();
									return permute_u64x8<determined_mask>(ab_);
								}
								else
								{
									static_assert(EmuCore::TMP::get_false<Register_>(), "INTERNAL EMUSIMD ERROR: Reached impossible point whilst instantiating template shuffle for an integral register of 64-bit elements.");
								}
							}
							else
							{
								static_assert(EmuCore::TMP::get_false<num_index_args>(), "Error executing templatised shuffle of an integral SIMD register with 64-bit elements: Invalid number of index arguments. The number of arguments must be equal to the number of elements within a 128-bit lane (2).");
							}
						}
						else
						{
							static_assert(EmuCore::TMP::get_false<Register_>(), "Error executing templatised integral SIMD register shuffle: The passed register type is not supported for this operation.");
						}
						#pragma endregion
					}
				}
				else
				{
					static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to shuffle a SIMD register using EmuSIMD helpers, but the provided Register_ type was not a supported SIMD register type.");
				}
			}
		}
	};
}

#endif
