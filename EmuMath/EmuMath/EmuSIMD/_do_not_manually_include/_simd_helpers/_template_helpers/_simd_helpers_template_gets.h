#ifndef EMU_SIMD_HELPERS_TEMPLATE_GETS_H_INC_
#define EMU_SIMD_HELPERS_TEMPLATE_GETS_H_INC_ 1

#include "_underlying_template_helpers/_all_underlying_templates.h"
#include "../../../../EmuCore/TMPHelpers/Values.h"

namespace EmuSIMD
{
	/// <summary>
	/// <para> Retrieves a specified index from a the passed SIMD register, cast as the provided Out_ type. </para>
	/// <para> If the requested register is integral, PerElementWidthIfInt_ will be used to determine how many bits each element should be interpreted as. </para>
	///	<para> PerElementWidthIfInt_ will not be used if the output register is a floating-point register. </para>
	/// <para> This is a relatively slow operation; if multiple indices are required as scalars, it is recommended to use `store` instead. </para>
	/// </summary>
	/// <typeparam name="Out_">Type to output as. Must be convertible to from the interpreted type contained within the passed register.</typeparam>
	/// <param name="register_">Register to extract the specified index from.</param>
	/// <returns>Requested index of the provided SIMD register cast to the provided Out_ type.</returns>
	template<std::size_t Index_, class Out_, std::size_t PerElementWidthIfInt_ = 32, class Register_>
	[[nodiscard]] inline Out_ get_index(Register_ register_)
	{
		if constexpr (EmuSIMD::TMP::is_simd_register_v<Register_>)
		{
			return _underlying_simd_helpers::_get_register_index<Index_, Out_, PerElementWidthIfInt_>(register_);
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Out_>(), "Attempted to extract a SIMD register index via EmuSIMD::get_index, but the provided register_ is not recognised as a SIMD register.");
		}
	}

	/// <summary>
	/// <para> Outputs the entirety of the passed SIMD register to the contiguous memory location pointed to by p_out_. </para>
	/// <para> 
	///		It is the caller's responsibility to ensure that the output location contains enough contiguously safe memory 
	///		(e.g. 256 bits for EmuSIMD::f32x8 registers) to store the passed register. 
	/// </para>
	/// <para> EmuSIMD::TMP::simd_register_width_v may be useful for forming a generic output location for this function. </para>
	/// </summary>
	/// <typeparam name="Out_">Type pointed to by the passed output pointer. May not be constant.</typeparam>
	/// <param name="register_">Register to store the contained data of.</param>
	/// <param name="p_out_">Non-const pointer to a memory location to output to.</param>
	template<typename Out_, class Register_, typename NoConstReq_ = std::enable_if_t<!std::is_const_v<Out_>>>
	inline void store(Register_ register_, Out_* p_out_)
	{
		if constexpr (EmuSIMD::TMP::is_simd_register_v<Register_>)
		{
			return _underlying_simd_helpers::_store_register(register_, p_out_);
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Out_>(), "Attempted to extract a SIMD register index via EmuSIMD::get_index, but the provided register_ is not recognised as a SIMD register.");
		}
	}

	template<std::size_t LaneIndex_, class OutLaneRegister_, class InRegister_>
	[[nodiscard]] constexpr inline OutLaneRegister_ extract_lane(InRegister_&& in_)
	{
		using in_uq = typename EmuCore::TMP::remove_ref_cv<InRegister_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<in_uq>)
		{
			using out_uq = typename EmuCore::TMP::remove_ref_cv<OutLaneRegister_>::type;
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
							return EmuSIMD::_underlying_simd_helpers::_extract_lane_f32x4_prevalidated<LaneIndex_>(std::forward<InRegister_>(in_));
						}
						else if constexpr (std::is_same_v<EmuSIMD::f32x8, out_uq>)
						{
							return EmuSIMD::_underlying_simd_helpers::_extract_lane_f32x8_prevalidated<LaneIndex_>(std::forward<InRegister_>(in_));
						}
						else if constexpr (std::is_same_v<EmuSIMD::f32x16, out_uq>)
						{
							return EmuSIMD::_underlying_simd_helpers::_extract_lane_f32x16_prevalidated<LaneIndex_>(std::forward<InRegister_>(in_));
						}
						else if constexpr (std::is_same_v<EmuSIMD::f64x2, out_uq>)
						{
							return EmuSIMD::_underlying_simd_helpers::_extract_lane_f64x2_prevalidated<LaneIndex_>(std::forward<InRegister_>(in_));
						}
						else if constexpr (std::is_same_v<EmuSIMD::f64x4, out_uq>)
						{
							return EmuSIMD::_underlying_simd_helpers::_extract_lane_f64x4_prevalidated<LaneIndex_>(std::forward<InRegister_>(in_));
						}
						else if constexpr (std::is_same_v<EmuSIMD::f64x8, out_uq>)
						{
							return EmuSIMD::_underlying_simd_helpers::_extract_lane_f64x8_prevalidated<LaneIndex_>(std::forward<InRegister_>(in_));
						}
						else if constexpr (std::is_same_v<EmuSIMD::i128_generic, out_uq>)
						{
							return EmuSIMD::_underlying_simd_helpers::_extract_lane_i32x4_prevalidated<LaneIndex_>(std::forward<InRegister_>(in_));
						}
						else if constexpr (std::is_same_v<EmuSIMD::i256_generic, out_uq>)
						{
							return EmuSIMD::_underlying_simd_helpers::_extract_lane_i32x8_prevalidated<LaneIndex_>(std::forward<InRegister_>(in_));
						}
						else if constexpr (std::is_same_v<EmuSIMD::i512_generic, out_uq>)
						{
							return EmuSIMD::_underlying_simd_helpers::_extract_lane_i32x16_prevalidated<LaneIndex_>(std::forward<InRegister_>(in_));
						}
						else if constexpr (std::is_same_v<EmuSIMD::i8x16, out_uq>)
						{
							return EmuSIMD::_underlying_simd_helpers::_extract_lane_i8x16_prevalidated<LaneIndex_>(std::forward<InRegister_>(in_));
						}
						else if constexpr (std::is_same_v<EmuSIMD::i8x32, out_uq>)
						{
							return EmuSIMD::_underlying_simd_helpers::_extract_lane_i8x32_prevalidated<LaneIndex_>(std::forward<InRegister_>(in_));
						}
						else if constexpr (std::is_same_v<EmuSIMD::i8x64, out_uq>)
						{
							return EmuSIMD::_underlying_simd_helpers::_extract_lane_i8x64_prevalidated<LaneIndex_>(std::forward<InRegister_>(in_));
						}
						else if constexpr (std::is_same_v<EmuSIMD::i16x8, out_uq>)
						{
							return EmuSIMD::_underlying_simd_helpers::_extract_lane_i16x8_prevalidated<LaneIndex_>(std::forward<InRegister_>(in_));
						}
						else if constexpr (std::is_same_v<EmuSIMD::i16x16, out_uq>)
						{
							return EmuSIMD::_underlying_simd_helpers::_extract_lane_i16x16_prevalidated<LaneIndex_>(std::forward<InRegister_>(in_));
						}
						else if constexpr (std::is_same_v<EmuSIMD::i16x32, out_uq>)
						{
							return EmuSIMD::_underlying_simd_helpers::_extract_lane_i16x32_prevalidated<LaneIndex_>(std::forward<InRegister_>(in_));
						}
						else if constexpr (std::is_same_v<EmuSIMD::i32x4, out_uq>)
						{
							return EmuSIMD::_underlying_simd_helpers::_extract_lane_i32x4_prevalidated<LaneIndex_>(std::forward<InRegister_>(in_));
						}
						else if constexpr (std::is_same_v<EmuSIMD::i32x8, out_uq>)
						{
							return EmuSIMD::_underlying_simd_helpers::_extract_lane_i32x8_prevalidated<LaneIndex_>(std::forward<InRegister_>(in_));
						}
						else if constexpr (std::is_same_v<EmuSIMD::i32x16, out_uq>)
						{
							return EmuSIMD::_underlying_simd_helpers::_extract_lane_i32x16_prevalidated<LaneIndex_>(std::forward<InRegister_>(in_));
						}
						else if constexpr (std::is_same_v<EmuSIMD::i64x2, out_uq>)
						{
							return EmuSIMD::_underlying_simd_helpers::_extract_lane_i64x2_prevalidated<LaneIndex_>(std::forward<InRegister_>(in_));
						}
						else if constexpr (std::is_same_v<EmuSIMD::i64x4, out_uq>)
						{
							return EmuSIMD::_underlying_simd_helpers::_extract_lane_i64x4_prevalidated<LaneIndex_>(std::forward<InRegister_>(in_));
						}
						else if constexpr (std::is_same_v<EmuSIMD::i64x8, out_uq>)
						{
							return EmuSIMD::_underlying_simd_helpers::_extract_lane_i64x8_prevalidated<LaneIndex_>(std::forward<InRegister_>(in_));
						}
						else
						{
							static_assert
							(
								EmuCore::TMP::get_false<OutLaneRegister_>(),
								"Attempted to extract a SIMD register lane via EmuSIMD::extract_lane, but the provided OutLaneRegister_ type is not a supported output type."
							);
						}
					}
					else
					{
						static_assert
						(
							EmuCore::TMP::get_false<LaneIndex_>(),
							"Attempted to extract a SIMD register lane via EmuSIMD::extract_lane, but the provided LaneIndex_ requires a width that exceeds that of the InRegister_ type. You may only extract fully contained lanes."
						);
					}
				}
				else
				{
					static_assert
					(
						EmuCore::TMP::get_false<OutLaneRegister_>(),
						"Attempted to extract a SIMD register lane via EmuSIMD::extract_lane, but the OutLaneRegister_ type is a greater width than the entire InRegister_ type. You may only extract lanes of widths less than or equal to the width of the input register."
					);
				}
			}
			else
			{
				static_assert
				(
					EmuCore::TMP::get_false<OutLaneRegister_>(),
					"Attempted to extract a SIMD register lane via EmuSIMD::extract_lane, but the OutLaneRegister_ type is not recognised as a SIMD register."
				);
			}
		}
		else
		{
			static_assert
			(
				EmuCore::TMP::get_false<InRegister_>(),
				"Attempted to extract a SIMD register lane via EmuSIMD::extract_lane, but the InRegister_ type is not recognised as a SIMD register."
			);
		}
	}
}

#endif