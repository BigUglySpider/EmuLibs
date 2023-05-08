#ifndef EMU_SIMD_UNDERLYING_FORWARD_TEMPLATE_GETS_H_INC_
#define EMU_SIMD_UNDERLYING_FORWARD_TEMPLATE_GETS_H_INC_ 1

#include "_forward_tmp.h"
#include "../../../../../../../EmuCore/CommonConcepts/CommonRequirements.h"

// DECLARES:
// EmuSIMD::
// --- get_index
// --- store
// --- extract_lane

namespace EmuSIMD
{
	template<std::size_t PerElementWidthIfGenericInt_ = 32, EmuConcepts::KnownSIMD Register_>
	[[nodiscard]] inline decltype(auto) movemask(Register_&& simd_register_);

	/// <summary>
	/// <para> Retrieves a specified index from a the passed SIMD register, cast as the provided Out_ type. </para>
	/// <para> If the requested register is integral, PerElementWidthIfGenericInt_ will be used to determine how many bits each element should be interpreted as. </para>
	///	<para> PerElementWidthIfGenericInt_ will not be used if the output register is a floating-point register. </para>
	/// <para> This is a relatively slow operation; if multiple indices are required as scalars, it is recommended to use `store` instead. </para>
	/// </summary>
	/// <typeparam name="Out_">Type to output as. Must be convertible to from the interpreted type contained within the passed register.</typeparam>
	/// <param name="register_">Register to extract the specified index from.</param>
	/// <returns>Requested index of the provided SIMD register cast to the provided Out_ type.</returns>
	template<std::size_t Index_, class Out_, std::size_t PerElementWidthIfGenericInt_ = 32, EmuConcepts::KnownSIMD SIMDRegister_>
	[[nodiscard]] inline auto get_index(SIMDRegister_&& simd_register_) noexcept
		-> Out_;

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
	template<EmuConcepts::Writable Out_, EmuConcepts::KnownSIMD SIMDRegister_>
	inline void store(SIMDRegister_&& simd_register_, Out_* p_out_);

	/// <summary>
	/// <para> Extracts a lane from the input SIMD register and outputs it as a SIMD register of the specified type. </para>
	/// <para> Valid lane indices are determined by the width of both the input and output SIMD register types. For example: </para>
	/// <para> --- Outputting a 128-bit lane from a 256-bit lane register will have valid lane indices 0, 1. </para>
	/// <para> --- Outputting a 256-bit lane from a 512-bit lane register will have valid lane indices 0, 1. </para>
	/// <para> --- Outputting a 128-bit lane from a 512-bit lane register will have valid lane indices 0, 1, 2, 3. </para>
	/// <para> Invalid extractions will trigger a static assertion. </para>
	/// <para> This is a bitwise extraction; outputting as different types (e.g. f32 in, i32 out) will not perform conversions. </para>
	/// </summary>
	/// <param name="in_multi_lane_simd_register_">SIMD register to extract a lane from.</param>
	/// <returns>Requested lane of the specified width from within the input SIMD register.</returns>
	template<std::size_t LaneIndex_, EmuConcepts::KnownSIMD OutLaneSIMDRegister_, EmuConcepts::KnownSIMD InSIMDRegister_>
	[[nodiscard]] inline auto extract_lane(InSIMDRegister_&& in_multi_lane_simd_register_) noexcept
		-> typename std::remove_cvref<OutLaneSIMDRegister_>::type;
}

#endif
