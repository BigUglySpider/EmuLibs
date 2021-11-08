#ifndef EMU_SIMD_HELPERS_TEMPLATE_CAST_H_INC_
#define EMU_SIMD_HELPERS_TEMPLATE_CAST_H_INC_ 1

#include "_underlying_template_helpers/_simd_helpers_underlying_cast.h"

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
	template<class ToRegister_, class FromRegister_>
	[[nodiscard]] inline ToRegister_ cast(FromRegister_ from_)
	{
		using from_uq = EmuCore::TMPHelpers::remove_ref_cv_t<FromRegister_>;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<from_uq>)
		{
			using to_uq = EmuCore::TMPHelpers::remove_ref_cv_t<ToRegister_>;
			if constexpr (EmuSIMD::TMP::is_simd_register_v<to_uq>)
			{
				return _underlying_simd_helpers::_cast<ToRegister_>(from_);
			}
			else
			{
				static_assert(false, "Attempted to perform EmuSIMD::cast, but the provided ToRegister_ (the output type) is not recognised as a supported SIMD register.");
			}
		}
		else
		{
			static_assert(false, "Attempted to perform EmuSIMD::cast, but the provided FromRegister_ (the input type) is not recognised as a supported SIMD register.");
		}
	}
}

#endif
