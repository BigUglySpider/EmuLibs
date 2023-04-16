#ifndef EMU_SIMD_HELPERS_TEMPLATE_SETS_H_INC_
#define EMU_SIMD_HELPERS_TEMPLATE_SETS_H_INC_ 1

#include "_underlying_template_helpers/_generic_funcs/_forward_declarations/_forward_template_sets.h"
#include "_underlying_template_helpers/_all_underlying_templates.h"
#include "_simd_helpers_template_shuffles.h"
#include "../../../../EmuCore/TMPHelpers/Values.h"

namespace EmuSIMD
{
	template<EmuConcepts::KnownSIMD SIMDRegister_, std::size_t ElementWidthIfGenericInt_, typename...SetArgs_>
	[[nodiscard]] inline auto set(SetArgs_&&...set_args_) noexcept
		-> typename std::remove_cvref<SIMDRegister_>::type
	{
		using _register_type_uq = typename EmuCore::TMP::remove_ref_cv<SIMDRegister_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<_register_type_uq>)
		{
			if constexpr (EmuSIMD::TMP::is_floating_point_simd_register_v<_register_type_uq>)
			{
				return _underlying_simd_helpers::_set_fp<_register_type_uq, false>(std::forward<SetArgs_>(set_args_)...);
			}
			else
			{
				return _underlying_simd_helpers::_set_int<_register_type_uq, ElementWidthIfGenericInt_, false>(std::forward<SetArgs_>(set_args_)...);
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<SIMDRegister_>(), "Attempted to perform EmuSIMD::set with an unsupported type as the passed SIMDRegister_.");
		}
	}

	template<EmuConcepts::KnownSIMD SIMDRegister_, std::size_t ElementWidthIfGenericInt_, typename...SetArgs_>
	[[nodiscard]] inline auto setr(SetArgs_&&...setr_args_) noexcept
		-> typename std::remove_cvref<SIMDRegister_>::type
	{
		using _register_type_uq = typename EmuCore::TMP::remove_ref_cv<SIMDRegister_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<_register_type_uq>)
		{
			if constexpr (EmuSIMD::TMP::is_floating_point_simd_register_v<_register_type_uq>)
			{
				return _underlying_simd_helpers::_set_fp<SIMDRegister_, true>(std::forward<SetArgs_>(setr_args_)...);
			}
			else
			{
				return _underlying_simd_helpers::_set_int<SIMDRegister_, ElementWidthIfGenericInt_, true>(std::forward<SetArgs_>(setr_args_)...);
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<SIMDRegister_>(), "Attempted to perform EmuSIMD::setr with an unsupported type as the passed SIMDRegister_.");
		}
	}

	template<EmuConcepts::KnownSIMD SIMDRegister_, std::size_t ElementWidthIfInt_, typename Val_>
	[[nodiscard]] inline auto set1(const Val_& val_) noexcept
		-> typename std::remove_cvref<SIMDRegister_>::type
	{
		using _register_type_uq = typename EmuCore::TMP::remove_ref_cv<SIMDRegister_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<_register_type_uq>)
		{
			return _underlying_simd_helpers::_set1<SIMDRegister_, ElementWidthIfInt_>(val_);
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<SIMDRegister_>(), "Attempted to perform EmuSIMD::set1 with an unsupported type as the passed SIMDRegister_.");
		}
	}

	template<EmuConcepts::KnownSIMD SIMDRegister_>
	[[nodiscard]] inline auto setzero() noexcept
		-> typename std::remove_cvref<SIMDRegister_>::type
	{
		using _register_type_uq = typename EmuCore::TMP::remove_ref_cv<SIMDRegister_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<_register_type_uq>)
		{
			return _underlying_simd_helpers::_setzero<SIMDRegister_>();
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<SIMDRegister_>(), "Attempted to perform EmuSIMD::setzero with an unsupported type as the passed SIMDRegister_.");
		}
	}

	template<EmuConcepts::KnownSIMD SIMDRegister_>
	[[nodiscard]] inline auto setallone() noexcept
		-> typename std::remove_cvref<SIMDRegister_>::type
	{
		using _register_type_uq = typename EmuCore::TMP::remove_ref_cv<SIMDRegister_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<_register_type_uq>)
		{
			using mask_generator_instance = _underlying_simd_helpers::_per_index_mask<_register_type_uq, true>;
			if constexpr (EmuSIMD::_underlying_simd_helpers::_is_valid_per_index_mask_instance<mask_generator_instance>::value)
			{
				return mask_generator_instance::get();
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<SIMDRegister_>(), "Attempted to perform EmuSIMD::setallone, but a successful mask generation could not be performed.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<SIMDRegister_>(), "Attempted to perform EmuSIMD::setallone with an unsupported type as the passed SIMDRegister_.");
		}
	}

	template<EmuConcepts::KnownSIMD SIMDRegister_, std::int64_t StartingVal_, std::size_t ElementWidthIfGenericInt_>
	[[nodiscard]] inline auto set_decrementing() noexcept
		-> typename std::remove_cvref<SIMDRegister_>::type
	{
		using _register_type_uq = typename EmuCore::TMP::remove_ref_cv<SIMDRegister_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<_register_type_uq>)
		{
			return _underlying_simd_helpers::_set_from_starting_value<_register_type_uq, StartingVal_, EmuCore::do_subtract, false, ElementWidthIfGenericInt_>();
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<SIMDRegister_>(), "Attempted to perform EmuSIMD::set_decrementing with an unsupported type as the passed SIMDRegister_.");
		}
	}

	template<EmuConcepts::KnownSIMD SIMDRegister_, std::int64_t StartingVal_, std::size_t ElementWidthIfGenericInt_>
	[[nodiscard]] inline auto setr_decrementing() noexcept
		-> typename std::remove_cvref<SIMDRegister_>::type
	{
		using _register_type_uq = typename EmuCore::TMP::remove_ref_cv<SIMDRegister_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<_register_type_uq>)
		{
			return _underlying_simd_helpers::_set_from_starting_value<_register_type_uq, StartingVal_, EmuCore::do_subtract, true, ElementWidthIfGenericInt_>();
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<SIMDRegister_>(), "Attempted to perform EmuSIMD::setr_decrementing with an unsupported type as the passed SIMDRegister_.");
		}
	}

	template<EmuConcepts::KnownSIMD SIMDRegister_, std::int64_t StartingVal_, std::size_t ElementWidthIfGenericInt_>
	[[nodiscard]] inline auto set_incrementing() noexcept
		-> typename std::remove_cvref<SIMDRegister_>::type
	{
		using _register_type_uq = typename EmuCore::TMP::remove_ref_cv<SIMDRegister_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<_register_type_uq>)
		{
			return _underlying_simd_helpers::_set_from_starting_value<_register_type_uq, StartingVal_, EmuCore::do_add, false, ElementWidthIfGenericInt_>();
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<SIMDRegister_>(), "Attempted to perform EmuSIMD::set_incrementing with an unsupported type as the passed SIMDRegister_.");
		}
	}

	template<EmuConcepts::KnownSIMD SIMDRegister_, std::int64_t StartingVal_, std::size_t ElementWidthIfGenericInt_>
	[[nodiscard]] inline auto setr_incrementing() noexcept
		-> typename std::remove_cvref<SIMDRegister_>::type
	{
		using _register_type_uq = typename EmuCore::TMP::remove_ref_cv<SIMDRegister_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<_register_type_uq>)
		{
			return _underlying_simd_helpers::_set_from_starting_value<_register_type_uq, StartingVal_, EmuCore::do_add, true, ElementWidthIfGenericInt_>();
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<SIMDRegister_>(), "Attempted to perform EmuSIMD::setr_incrementing with an unsupported type as the passed SIMDRegister_.");
		}
	}

	template<EmuConcepts::KnownSIMD SIMDRegister_, typename In_>
	[[nodiscard]] inline auto load(const In_* p_to_load_)
		-> typename std::remove_cvref<SIMDRegister_>::type
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<SIMDRegister_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			return _underlying_simd_helpers::_load<SIMDRegister_>(p_to_load_);
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<SIMDRegister_>(), "Attempted to perform EmuSIMD::load with an unsupported type as the passed SIMDRegister_.");
		}
	}

	template<std::size_t Index_, std::size_t PerElementWidthIfGenericInt_, EmuConcepts::KnownSIMD SIMDRegister_>
	[[nodiscard]] inline auto set_all_to_index(SIMDRegister_&& in_) noexcept
		-> typename std::remove_cvref<SIMDRegister_>::type
	{
		using register_uq = typename EmuCore::TMP::remove_ref_cv<SIMDRegister_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_uq>)
		{
			constexpr std::size_t num_elements = EmuSIMD::TMP::register_element_count_v<SIMDRegister_, PerElementWidthIfGenericInt_>;
			if constexpr (Index_ < num_elements)
			{
				if constexpr (std::is_same_v<register_uq, EmuSIMD::f32x4>)
				{
					return EmuSIMD::shuffle<Index_, Index_, Index_, Index_>(std::forward<SIMDRegister_>(in_));
				}
				else if constexpr (std::is_same_v<register_uq, EmuSIMD::f32x8>)
				{
					constexpr std::size_t lane_index = Index_ >= 4 ? 1 : 0;
					constexpr std::size_t mask = (lane_index << 4) | lane_index;
					constexpr std::size_t index_in_lane = Index_ % 4;
					register_uq matching_lanes = _mm256_permute2f128_ps(in_, in_, mask);
					matching_lanes = _mm256_permute2f128_ps(matching_lanes, matching_lanes, mask);
					return EmuSIMD::shuffle<index_in_lane, index_in_lane, index_in_lane, index_in_lane>(matching_lanes);
				}
				else if constexpr (std::is_same_v<register_uq, EmuSIMD::f32x16>)
				{
					return EmuSIMD::set1<SIMDRegister_, PerElementWidthIfGenericInt_>(EmuSIMD::get_index<Index_, float, PerElementWidthIfGenericInt_>(std::forward<SIMDRegister_>(in_)));
				}
				else if constexpr (std::is_same_v<register_uq, EmuSIMD::f64x2>)
				{
					return EmuSIMD::shuffle<Index_, Index_>(in_);
				}
				else if constexpr (std::is_same_v<register_uq, EmuSIMD::f64x4>)
				{
					constexpr std::size_t lane_index = Index_ >= 2 ? 1 : 0;
					constexpr std::size_t mask = (lane_index << 4) | lane_index;
					constexpr std::size_t index_in_lane = Index_ % 2;
					register_uq matching_lanes = _mm256_permute2f128_pd(in_, in_, mask);
					return EmuSIMD::shuffle<index_in_lane, index_in_lane>(matching_lanes);
				}
				else if constexpr (std::is_same_v<register_uq, EmuSIMD::f64x8>)
				{
					return EmuSIMD::set1<SIMDRegister_, PerElementWidthIfGenericInt_>(EmuSIMD::get_index<Index_, double, PerElementWidthIfGenericInt_>(std::forward<SIMDRegister_>(in_)));
				}
				else if constexpr (std::is_same_v<register_uq, EmuSIMD::i128_generic>)
				{
					if constexpr (PerElementWidthIfGenericInt_ == 8)
					{
						return EmuSIMD::shuffle<Index_, Index_, Index_, Index_, Index_, Index_, Index_, Index_, Index_, Index_, Index_, Index_, Index_, Index_, Index_, Index_>(std::forward<SIMDRegister_>(in_));
					}
					else if constexpr (PerElementWidthIfGenericInt_ == 16)
					{
						return EmuSIMD::shuffle<Index_, Index_, Index_, Index_, Index_, Index_, Index_, Index_>(std::forward<SIMDRegister_>(in_));
					}
					else if constexpr (PerElementWidthIfGenericInt_ == 32)
					{
						return EmuSIMD::shuffle<Index_, Index_, Index_, Index_>(std::forward<SIMDRegister_>(in_));
					}
					else if constexpr (PerElementWidthIfGenericInt_ == 64)
					{
						return EmuSIMD::shuffle<Index_, Index_>(std::forward<SIMDRegister_>(in_));
					}
					else
					{
						static_assert
						(
							EmuCore::TMP::get_false<PerElementWidthIfGenericInt_>(),
							"Attempted to set all elements in a generic 128-bit integral SIMD register to match a specific index via EmuSIMD::set_all_to_index, but the provided PerElementWidthIfGenericInt_ is invalid. Valid values are: 8, 16, 32, 64."
						);
					}
				}
				else if constexpr (std::is_same_v<register_uq, EmuSIMD::i256_generic>)
				{
					constexpr std::size_t half_elements = num_elements / 2;
					constexpr std::size_t lane_index = Index_ >= half_elements ? 1 : 0;
					constexpr std::size_t mask = (lane_index << 4) | lane_index;
					constexpr std::size_t index_in_lane = Index_ % half_elements;
					register_uq matching_lanes;

					if constexpr (std::is_lvalue_reference_v<SIMDRegister_>)
					{
						matching_lanes = _mm256_permute2f128_si256(in_, in_, mask);
					}
					else
					{
						const register_uq& in_ref = EmuCore::TMP::const_lval_ref_cast<SIMDRegister_>(std::forward<SIMDRegister_>(in_));
						matching_lanes = _mm256_permute2f128_si256(in_ref, in_ref, mask);
					}

					if constexpr (PerElementWidthIfGenericInt_ == 8)
					{
						return EmuSIMD::shuffle<index_in_lane, index_in_lane, index_in_lane, index_in_lane, index_in_lane, index_in_lane, index_in_lane, index_in_lane, index_in_lane, index_in_lane, index_in_lane, index_in_lane, index_in_lane, index_in_lane, index_in_lane, index_in_lane>
						(
							matching_lanes
						);
					}
					else if constexpr (PerElementWidthIfGenericInt_ == 16)
					{
						return EmuSIMD::shuffle<index_in_lane, index_in_lane, index_in_lane, index_in_lane, index_in_lane, index_in_lane, index_in_lane, index_in_lane>(matching_lanes);
					}
					else if constexpr (PerElementWidthIfGenericInt_ == 32)
					{
						return EmuSIMD::shuffle<index_in_lane, index_in_lane, index_in_lane, index_in_lane>(matching_lanes);
					}
					else if constexpr (PerElementWidthIfGenericInt_ == 64)
					{
						return EmuSIMD::shuffle<index_in_lane, index_in_lane>(matching_lanes);
					}
					else
					{
						static_assert
						(
							EmuCore::TMP::get_false<PerElementWidthIfGenericInt_>(),
							"Attempted to set all elements in a generic 256-bit integral SIMD register to match a specific index via EmuSIMD::set_all_to_index, but the provided PerElementWidthIfGenericInt_ is invalid. Valid values are: 8, 16, 32, 64."
						);
					}
				}
				else if constexpr (std::is_same_v<register_uq, EmuSIMD::i512_generic>)
				{
					if constexpr (PerElementWidthIfGenericInt_ == 8 || PerElementWidthIfGenericInt_ == 16 || PerElementWidthIfGenericInt_ == 32 || PerElementWidthIfGenericInt_ == 64)
					{
						using sized_int = EmuCore::TMP::int_of_size_t<PerElementWidthIfGenericInt_ / 8>;
						return EmuSIMD::set1<SIMDRegister_, PerElementWidthIfGenericInt_>
						(
							EmuSIMD::get_index<Index_, sized_int, PerElementWidthIfGenericInt_>
							(
								std::forward<SIMDRegister_>(in_)
							)
						);
					}
					else
					{
						static_assert
						(
							EmuCore::TMP::get_false<PerElementWidthIfGenericInt_>(),
							"Attempted to set all elements in a generic 512-bit integral SIMD register to match a specific index via EmuSIMD::set_all_to_index, but the provided PerElementWidthIfGenericInt_ is invalid. Valid values are: 8, 16, 32, 64."
						);
					}
				}
				else if constexpr (std::is_same_v<register_uq, EmuSIMD::i8x16> || std::is_same_v<register_uq, EmuSIMD::u8x16>)
				{
					return EmuSIMD::shuffle<Index_, Index_, Index_, Index_, Index_, Index_, Index_, Index_, Index_, Index_, Index_, Index_, Index_, Index_, Index_, Index_>
					(
						std::forward<SIMDRegister_>(in_)
					);
				}
				else if constexpr (std::is_same_v<register_uq, EmuSIMD::i16x8> || std::is_same_v<register_uq, EmuSIMD::u16x8>)
				{
					return EmuSIMD::shuffle<Index_, Index_, Index_, Index_, Index_, Index_, Index_, Index_>
					(
						std::forward<SIMDRegister_>(in_)
					);
				}
				else if constexpr (std::is_same_v<register_uq, EmuSIMD::i32x4> || std::is_same_v<register_uq, EmuSIMD::u32x4>)
				{
					return EmuSIMD::shuffle<Index_, Index_, Index_, Index_>(std::forward<SIMDRegister_>(in_));
				}
				else if constexpr (std::is_same_v<register_uq, EmuSIMD::i64x2> || std::is_same_v<register_uq, EmuSIMD::u64x2>)
				{
					return EmuSIMD::shuffle<Index_, Index_>(std::forward<SIMDRegister_>(in_));
				}
				else if constexpr (EmuCore::TMP::is_any_same_v<register_uq, EmuSIMD::i8x32, EmuSIMD::i16x16, EmuSIMD::i32x8, EmuSIMD::i64x4, EmuSIMD::u8x32, EmuSIMD::u16x16, EmuSIMD::u32x8, EmuSIMD::u64x4>)
				{
					constexpr std::size_t half_elements = num_elements / 2;
					constexpr std::size_t lane_index = Index_ >= half_elements ? 1 : 0;
					constexpr std::size_t mask = (lane_index << 4) | lane_index;
					constexpr std::size_t index_in_lane = num_elements % half_elements;

					register_uq matching_lanes;
					if constexpr (std::is_lvalue_reference_v<SIMDRegister_>)
					{
						matching_lanes = _mm256_permute2f128_si256(in_, in_, mask);
					}
					else
					{
						const register_uq& in_ref = EmuCore::TMP::const_lval_ref_cast<SIMDRegister_>(std::forward<SIMDRegister_>(in_));
						matching_lanes = _mm256_permute2f128_si256(in_ref, in_ref, mask);
					}

					if constexpr (std::is_same_v<register_uq, EmuSIMD::i8x32> || std::is_same_v<register_uq, EmuSIMD::u8x32>)
					{
						return EmuSIMD::shuffle<index_in_lane, index_in_lane, index_in_lane, index_in_lane, index_in_lane, index_in_lane, index_in_lane, index_in_lane, index_in_lane, index_in_lane, index_in_lane, index_in_lane, index_in_lane, index_in_lane, index_in_lane, index_in_lane>
						(
							matching_lanes
						);

					}
					else if constexpr (std::is_same_v<register_uq, EmuSIMD::i16x16> || std::is_same_v<register_uq, EmuSIMD::u16x16>)
					{
						return EmuSIMD::shuffle<index_in_lane, index_in_lane, index_in_lane, index_in_lane, index_in_lane, index_in_lane, index_in_lane, index_in_lane>(matching_lanes);
					}
					else if constexpr (std::is_same_v<register_uq, EmuSIMD::i32x8> || std::is_same_v<register_uq, EmuSIMD::u32x8>)
					{
						return EmuSIMD::shuffle<index_in_lane, index_in_lane, index_in_lane, index_in_lane>(matching_lanes);
					}
					else if constexpr (std::is_same_v<register_uq, EmuSIMD::i64x4> || std::is_same_v<register_uq, EmuSIMD::u64x4>)
					{
						return EmuSIMD::shuffle<index_in_lane, index_in_lane>(matching_lanes);
					}
					else
					{
						static_assert
						(
							EmuCore::TMP::get_false<SIMDRegister_>(),
							"Internal EmuSIMD error @EmuSIMD::set_all_to_index, with register_uq recognised as one of: i8x32, i16x16, i32x8, i64x4, u8x32, u16x16, u32x8, or u64x4 in initial check, but not in further checks."
						);
					}
				}
				else if constexpr (std::is_same_v<register_uq, EmuSIMD::i8x64> || std::is_same_v<register_uq, EmuSIMD::u8x64>)
				{
					return EmuSIMD::set1<SIMDRegister_, 8>(EmuSIMD::get_index<Index_, std::int8_t, 8>(std::forward<SIMDRegister_>(in_)));
				}
				else if constexpr (std::is_same_v<register_uq, EmuSIMD::i16x32> || std::is_same_v<register_uq, EmuSIMD::u16x32>)
				{
					return EmuSIMD::set1<SIMDRegister_, 16>(EmuSIMD::get_index<Index_, std::int16_t, 16>(std::forward<SIMDRegister_>(in_)));
				}
				else if constexpr (std::is_same_v<register_uq, EmuSIMD::i32x16> || std::is_same_v<register_uq, EmuSIMD::u32x16>)
				{
					return EmuSIMD::set1<SIMDRegister_, 32>(EmuSIMD::get_index<Index_, std::int32_t, 32>(std::forward<SIMDRegister_>(in_)));
				}
				else if constexpr (std::is_same_v<register_uq, EmuSIMD::i8x64> || std::is_same_v<register_uq, EmuSIMD::u8x64>)
				{
					return EmuSIMD::set1<SIMDRegister_, 64>(EmuSIMD::get_index<Index_, std::int64_t, 64>(std::forward<SIMDRegister_>(in_)));
				}
				else
				{
					static_assert
					(
						EmuCore::TMP::get_false<SIMDRegister_>(),
						"Attempted to perform EmuSIMD::set_all_to_index, but the provided Register_ type is not supported for this operation."
					);
				}
			}
			else
			{
				static_assert
				(
					EmuCore::TMP::get_false<Index_>(),
					"Attempted to perform EmuSIMD::set_all_to_index with an index outside of the range of the passed SIMD register."
				);
			}

		}
		else
		{
			static_assert
			(
				EmuCore::TMP::get_false<SIMDRegister_>(),
				"Attempted to perform EmuSIMD::set_all_to_index with a passed Register_ type which is not recognised as a SIMD register."
			);
		}
	}

	template<EmuConcepts::KnownSIMD SIMDRegister_, std::size_t PerElementWidthIfGenericInt_, bool OddSign_>
	[[nodiscard]] inline auto alternating_sign_mask() noexcept
		-> typename std::remove_cvref<SIMDRegister_>::type
	{
		using index_seq = std::make_index_sequence<EmuSIMD::TMP::register_element_count_v<SIMDRegister_, PerElementWidthIfGenericInt_>>;
		return _underlying_simd_helpers::_make_alternating_sign_mask<SIMDRegister_, PerElementWidthIfGenericInt_, OddSign_, false>(index_seq());
	}

	template<EmuConcepts::KnownSIMD SIMDRegister_, std::size_t PerElementWidthIfGenericInt_, bool OddSign_>
	[[nodiscard]] constexpr inline auto alternating_sign_mask_reverse() noexcept
		-> typename std::remove_cvref<SIMDRegister_>::type
	{
		using index_seq = std::make_index_sequence<EmuSIMD::TMP::register_element_count_v<SIMDRegister_, PerElementWidthIfGenericInt_>>;
		return _underlying_simd_helpers::_make_alternating_sign_mask<SIMDRegister_, PerElementWidthIfGenericInt_, OddSign_, true>(index_seq());
	}

	template<std::size_t PerElementWidthIfGenericInt_, EmuConcepts::KnownSIMD SIMDRegister_, bool...SignAtIndex_>
	[[nodiscard]] constexpr inline auto sign_mask() noexcept
		-> typename std::remove_cvref<SIMDRegister_>::type
	{
		return _underlying_simd_helpers::_make_sign_mask<SIMDRegister_, PerElementWidthIfGenericInt_, false, SignAtIndex_...>();
	}

	template<std::size_t PerElementWidthIfGenericInt_, EmuConcepts::KnownSIMD SIMDRegister_, bool...SignAtIndex_>
	[[nodiscard]] constexpr inline auto sign_mask_reverse() noexcept
		-> typename std::remove_cvref<SIMDRegister_>::type
	{
		return _underlying_simd_helpers::_make_sign_mask<SIMDRegister_, PerElementWidthIfGenericInt_, false, SignAtIndex_...>();
	}
}

#endif
