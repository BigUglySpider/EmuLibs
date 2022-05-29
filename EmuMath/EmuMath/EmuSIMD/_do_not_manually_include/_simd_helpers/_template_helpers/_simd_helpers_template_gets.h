#ifndef EMU_SIMD_HELPERS_TEMPLATE_GETS_H_INC_
#define EMU_SIMD_HELPERS_TEMPLATE_GETS_H_INC_ 1

#include "_underlying_template_helpers/_common_underlying_simd_template_helper_includes.h"
#include "_underlying_template_helpers/_simd_helpers_underlying_get.h"
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
	[[nodiscard]] inline void store(Register_ register_, Out_* p_out_)
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
}

#endif