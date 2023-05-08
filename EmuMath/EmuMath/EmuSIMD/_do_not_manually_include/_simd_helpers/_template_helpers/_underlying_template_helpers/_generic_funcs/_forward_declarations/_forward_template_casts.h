#ifndef EMU_SIMD_UNDERLYING_FORWARD_TEMPLATE_CASTS_H_INC_
#define EMU_SIMD_UNDERLYING_FORWARD_TEMPLATE_CASTS_H_INC_ 1

#include "_forward_tmp.h"

namespace EmuSIMD
{
	/// <summary>
	/// <para> Returns the result of casting the passed SIMD register to the provided SIMD register type. </para>
	/// <para> This is purely a register reinterpretation; no conversions are performed. </para>
	/// </summary>
	/// <typeparam name="ToRegister_">Type of SIMD register to cast the input register to.</typeparam>
	/// <typeparam name="FromRegister_">Type of SIMD register to perform the cast on.</typeparam>
	/// <param name="from_">SIMD register to perform the cast on.</param>
	/// <returns>Passed SIMD register reinterpreted as the provided type of SIMD register.</returns>
	template<EmuConcepts::KnownSIMD ToRegister_, EmuConcepts::KnownSIMD FromRegister_>
	[[nodiscard]] inline auto cast(FromRegister_&& from_)
		-> typename std::remove_cvref<ToRegister_>::type;
}

#endif
