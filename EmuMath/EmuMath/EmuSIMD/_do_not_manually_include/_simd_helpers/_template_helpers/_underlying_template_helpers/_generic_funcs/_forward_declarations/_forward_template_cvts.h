#ifndef EMU_SIMD_UNDERLYING_FORWARD_TEMPLATE_CVTS_H_INC_
#define EMU_SIMD_UNDERLYING_FORWARD_TEMPLATE_CVTS_H_INC_ 1

#include "_forward_tmp.h"

namespace EmuSIMD
{
	/// <summary>
	/// <para> Returns the result of converting the passed SIMD register to the provided SIMD register type. </para>
	/// <para> This will convert values. To instead only perform a bitwise case, use `cast`. </para>
	/// <para>
	///		InWidthPerElementIfInt_ is the amount of bits each element consumes if the input register is integral. 
	///		It is not used if the input register is floating-point or is not a generic SIMD register. Defaults to 32.
	/// </para>
	/// <para>
	///		InSignedIfInt_ is true if the input register is signed, otherwise it is considered unsigned. 
	///		It is not used if the input register is floating-point or is not a generic SIMD register. Defaults to true.
	/// </para>
	/// <para>
	///		OutWidthPerElement is the amount of bits each element consumes if the output register is integral. 
	///		It is not used if the output register is floating-point or is not a generic SIMD register. Defaults to InWidthPerElementIfInt_.
	/// </para>
	/// <para>
	///		OutSignedIfInt_ is true if the input output is signed, otherwise it is considered unsigned. 
	///		It is not used if the output register is floating-point or is not a generic SIMD register. Defaults to InSignedIfInt_.
	/// </para>
	/// </summary>
	/// <typeparam name="ToRegister_">Type of SIMD register to convert the input register to.</typeparam>
	/// <typeparam name="FromRegister_">Type of SIMD register to perform the conversion on.</typeparam>
	/// <param name="from_">SIMD register to perform the conversion on.</param>
	/// <returns>Passed SIMD register converted to the provided type of SIMD register.</returns>
	template
	<
		EmuConcepts::KnownSIMD ToRegister_,
		std::size_t InWidthPerElementIfInt_ = 32,
		bool InSignedIfInt_ = true,
		std::size_t OutWidthPerElementIfInt_ = InWidthPerElementIfInt_,
		bool OutSignedIfInt_ = InSignedIfInt_,
		EmuConcepts::KnownSIMD FromRegister_
	>
	[[nodiscard]] inline auto convert(FromRegister_&& from_)
		-> typename std::remove_cvref<ToRegister_>::type;
}

#endif
