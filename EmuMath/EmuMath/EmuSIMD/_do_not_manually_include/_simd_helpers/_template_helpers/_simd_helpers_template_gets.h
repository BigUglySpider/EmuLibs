#ifndef EMU_SIMD_HELPERS_TEMPLATE_GETS_H_INC_
#define EMU_SIMD_HELPERS_TEMPLATE_GETS_H_INC_ 1

#include "_underlying_template_helpers/_all_underlying_templates.h"
#include "_underlying_template_helpers/_generic_funcs/_forward_declarations/_forward_template_gets.h"
#include "../../../../EmuCore/TMPHelpers/Values.h"

namespace EmuSIMD
{
	template<std::size_t Index_, class Out_, std::size_t PerElementWidthIfGenericInt_, EmuConcepts::KnownSIMD SIMDRegister_>
	[[nodiscard]] inline auto get_index(SIMDRegister_&& simd_register_) noexcept
		-> Out_
	{
		if constexpr (EmuSIMD::TMP::is_simd_register_v<SIMDRegister_>)
		{
			return _underlying_simd_helpers::_get_register_index<Index_, Out_, PerElementWidthIfGenericInt_>(std::forward<SIMDRegister_>(simd_register_));
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<SIMDRegister_>(), "Attempted to extract a SIMD register index via EmuSIMD::get_index, but the provided register_ is not recognised as a SIMD register.");
		}
	}

	template<EmuConcepts::Writable Out_, EmuConcepts::KnownSIMD SIMDRegister_>
	inline void store(SIMDRegister_&& simd_register_, Out_* p_out_)
	{
		if constexpr (EmuSIMD::TMP::is_simd_register_v<SIMDRegister_>)
		{
			return _underlying_simd_helpers::_store_register(std::forward<SIMDRegister_>(simd_register_), p_out_);
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<SIMDRegister_>(), "Attempted to extract a SIMD register index via EmuSIMD::get_index, but the provided register_ is not recognised as a SIMD register.");
		}
	}

	template<std::size_t LaneIndex_, EmuConcepts::KnownSIMD OutLaneSIMDRegister_, EmuConcepts::KnownSIMD InSIMDRegister_>
	[[nodiscard]] inline auto extract_lane(InSIMDRegister_&& in_multi_lane_simd_register_) noexcept
		-> typename std::remove_cvref<OutLaneSIMDRegister_>::type
	{
		using in_uq = typename EmuCore::TMP::remove_ref_cv<InSIMDRegister_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<in_uq>)
		{
			using out_uq = typename EmuCore::TMP::remove_ref_cv<OutLaneSIMDRegister_>::type;
			if constexpr (EmuSIMD::TMP::is_simd_register_v<out_uq>)
			{
				constexpr std::size_t in_width = EmuSIMD::TMP::simd_register_width_v<in_uq>;
				constexpr std::size_t out_width = EmuSIMD::TMP::simd_register_width_v<out_uq>;
				if constexpr (out_width <= in_width)
				{
					constexpr std::size_t required_width = out_width * (LaneIndex_ + 1);
					if constexpr (required_width <= in_width)
					{
						if constexpr (std::is_same_v<EmuSIMD::f32x4, out_uq>)
						{
							return EmuSIMD::_underlying_simd_helpers::_extract_lane_f32x4_prevalidated<LaneIndex_>(std::forward<InSIMDRegister_>(in_multi_lane_simd_register_));
						}
						else if constexpr (std::is_same_v<EmuSIMD::f32x8, out_uq>)
						{
							return EmuSIMD::_underlying_simd_helpers::_extract_lane_f32x8_prevalidated<LaneIndex_>(std::forward<InSIMDRegister_>(in_multi_lane_simd_register_));
						}
						else if constexpr (std::is_same_v<EmuSIMD::f32x16, out_uq>)
						{
							return EmuSIMD::_underlying_simd_helpers::_extract_lane_f32x16_prevalidated<LaneIndex_>(std::forward<InSIMDRegister_>(in_multi_lane_simd_register_));
						}
						else if constexpr (std::is_same_v<EmuSIMD::f64x2, out_uq>)
						{
							return EmuSIMD::_underlying_simd_helpers::_extract_lane_f64x2_prevalidated<LaneIndex_>(std::forward<InSIMDRegister_>(in_multi_lane_simd_register_));
						}
						else if constexpr (std::is_same_v<EmuSIMD::f64x4, out_uq>)
						{
							return EmuSIMD::_underlying_simd_helpers::_extract_lane_f64x4_prevalidated<LaneIndex_>(std::forward<InSIMDRegister_>(in_multi_lane_simd_register_));
						}
						else if constexpr (std::is_same_v<EmuSIMD::f64x8, out_uq>)
						{
							return EmuSIMD::_underlying_simd_helpers::_extract_lane_f64x8_prevalidated<LaneIndex_>(std::forward<InSIMDRegister_>(in_multi_lane_simd_register_));
						}
						else if constexpr (std::is_same_v<EmuSIMD::i128_generic, out_uq>)
						{
							return EmuSIMD::_underlying_simd_helpers::_extract_lane_i32x4_prevalidated<LaneIndex_>(std::forward<InSIMDRegister_>(in_multi_lane_simd_register_));
						}
						else if constexpr (std::is_same_v<EmuSIMD::i256_generic, out_uq>)
						{
							return EmuSIMD::_underlying_simd_helpers::_extract_lane_i32x8_prevalidated<LaneIndex_>(std::forward<InSIMDRegister_>(in_multi_lane_simd_register_));
						}
						else if constexpr (std::is_same_v<EmuSIMD::i512_generic, out_uq>)
						{
							return EmuSIMD::_underlying_simd_helpers::_extract_lane_i32x16_prevalidated<LaneIndex_>(std::forward<InSIMDRegister_>(in_multi_lane_simd_register_));
						}
						else if constexpr (std::is_same_v<EmuSIMD::i8x16, out_uq>)
						{
							return EmuSIMD::_underlying_simd_helpers::_extract_lane_i8x16_prevalidated<LaneIndex_>(std::forward<InSIMDRegister_>(in_multi_lane_simd_register_));
						}
						else if constexpr (std::is_same_v<EmuSIMD::i8x32, out_uq>)
						{
							return EmuSIMD::_underlying_simd_helpers::_extract_lane_i8x32_prevalidated<LaneIndex_>(std::forward<InSIMDRegister_>(in_multi_lane_simd_register_));
						}
						else if constexpr (std::is_same_v<EmuSIMD::i8x64, out_uq>)
						{
							return EmuSIMD::_underlying_simd_helpers::_extract_lane_i8x64_prevalidated<LaneIndex_>(std::forward<InSIMDRegister_>(in_multi_lane_simd_register_));
						}
						else if constexpr (std::is_same_v<EmuSIMD::i16x8, out_uq>)
						{
							return EmuSIMD::_underlying_simd_helpers::_extract_lane_i16x8_prevalidated<LaneIndex_>(std::forward<InSIMDRegister_>(in_multi_lane_simd_register_));
						}
						else if constexpr (std::is_same_v<EmuSIMD::i16x16, out_uq>)
						{
							return EmuSIMD::_underlying_simd_helpers::_extract_lane_i16x16_prevalidated<LaneIndex_>(std::forward<InSIMDRegister_>(in_multi_lane_simd_register_));
						}
						else if constexpr (std::is_same_v<EmuSIMD::i16x32, out_uq>)
						{
							return EmuSIMD::_underlying_simd_helpers::_extract_lane_i16x32_prevalidated<LaneIndex_>(std::forward<InSIMDRegister_>(in_multi_lane_simd_register_));
						}
						else if constexpr (std::is_same_v<EmuSIMD::i32x4, out_uq>)
						{
							return EmuSIMD::_underlying_simd_helpers::_extract_lane_i32x4_prevalidated<LaneIndex_>(std::forward<InSIMDRegister_>(in_multi_lane_simd_register_));
						}
						else if constexpr (std::is_same_v<EmuSIMD::i32x8, out_uq>)
						{
							return EmuSIMD::_underlying_simd_helpers::_extract_lane_i32x8_prevalidated<LaneIndex_>(std::forward<InSIMDRegister_>(in_multi_lane_simd_register_));
						}
						else if constexpr (std::is_same_v<EmuSIMD::i32x16, out_uq>)
						{
							return EmuSIMD::_underlying_simd_helpers::_extract_lane_i32x16_prevalidated<LaneIndex_>(std::forward<InSIMDRegister_>(in_multi_lane_simd_register_));
						}
						else if constexpr (std::is_same_v<EmuSIMD::i64x2, out_uq>)
						{
							return EmuSIMD::_underlying_simd_helpers::_extract_lane_i64x2_prevalidated<LaneIndex_>(std::forward<InSIMDRegister_>(in_multi_lane_simd_register_));
						}
						else if constexpr (std::is_same_v<EmuSIMD::i64x4, out_uq>)
						{
							return EmuSIMD::_underlying_simd_helpers::_extract_lane_i64x4_prevalidated<LaneIndex_>(std::forward<InSIMDRegister_>(in_multi_lane_simd_register_));
						}
						else if constexpr (std::is_same_v<EmuSIMD::i64x8, out_uq>)
						{
							return EmuSIMD::_underlying_simd_helpers::_extract_lane_i64x8_prevalidated<LaneIndex_>(std::forward<InSIMDRegister_>(in_multi_lane_simd_register_));
						}
						else
						{
							static_assert
							(
								EmuCore::TMP::get_false<OutLaneSIMDRegister_>(),
								"Attempted to extract a SIMD register lane via EmuSIMD::extract_lane, but the provided OutLaneSIMDRegister_ type is not a supported output type."
							);
						}
					}
					else
					{
						static_assert
						(
							EmuCore::TMP::get_false<LaneIndex_>(),
							"Attempted to extract a SIMD register lane via EmuSIMD::extract_lane, but the provided LaneIndex_ requires a width that exceeds that of the InSIMDRegister_ type. You may only extract fully contained lanes."
						);
					}
				}
				else
				{
					static_assert
					(
						EmuCore::TMP::get_false<OutLaneSIMDRegister_>(),
						"Attempted to extract a SIMD register lane via EmuSIMD::extract_lane, but the OutLaneSIMDRegister_ type is a greater width than the entire InRegister_ type. You may only extract lanes of widths less than or equal to the width of the input register."
					);
				}
			}
			else
			{
				static_assert
				(
					EmuCore::TMP::get_false<OutLaneSIMDRegister_>(),
					"Attempted to extract a SIMD register lane via EmuSIMD::extract_lane, but the OutLaneSIMDRegister_ type is not recognised as a SIMD register."
				);
			}
		}
		else
		{
			static_assert
			(
				EmuCore::TMP::get_false<InSIMDRegister_>(),
				"Attempted to extract a SIMD register lane via EmuSIMD::extract_lane, but the InSIMDRegister_ type is not recognised as a SIMD register."
			);
		}
	}
}

#endif