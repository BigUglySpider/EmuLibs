#ifndef EMU_SIMD_HELPERS_TEMPLATE_CVT_H_INC_
#define EMU_SIMD_HELPERS_TEMPLATE_CVT_H_INC_ 1

#include "_underlying_template_helpers/_simd_helpers_underlying_cvt.h"
#include "../../../../EmuCore/TMPHelpers/Values.h"

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
		class ToRegister_,
		std::size_t InWidthPerElementIfInt_ = 32,
		bool InSignedIfInt_ = true,
		std::size_t OutWidthPerElementIfInt_ = InWidthPerElementIfInt_,
		bool OutSignedIfInt_ = InSignedIfInt_,
		class FromRegister_
	>
	[[nodiscard]] inline ToRegister_ convert(FromRegister_&& from_)
	{
		using from_uq = EmuCore::TMP::remove_ref_cv_t<FromRegister_>;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<from_uq>)
		{
			using to_uq = EmuCore::TMP::remove_ref_cv_t<ToRegister_>;
			if constexpr (EmuSIMD::TMP::is_simd_register_v<to_uq>)
			{
				return _underlying_simd_helpers::_cvt_register<OutWidthPerElementIfInt_, OutSignedIfInt_, InWidthPerElementIfInt_, InSignedIfInt_, ToRegister_>
				(
					std::forward<FromRegister_>(from_)
				);
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<ToRegister_>(), "Attempted to perform EmuSIMD::convert, but the provided ToRegister_ (the output type) is not recognised as a supported SIMD register.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<ToRegister_>(), "Attempted to perform EmuSIMD::convert, but the provided FromRegister_ (the input type) is not recognised as a supported SIMD register.");
		}
	}
}

#endif
