#ifndef EMU_SIMD_HELPERS_TEMPLATE_CVT_H_INC_
#define EMU_SIMD_HELPERS_TEMPLATE_CVT_H_INC_ 1

#include "_underlying_template_helpers/_all_underlying_templates.h"
#include "_underlying_template_helpers/_generic_funcs/_forward_declarations/_forward_template_cvts.h"
#include "../../../../EmuCore/TMPHelpers/Values.h"

namespace EmuSIMD
{
	template<EmuConcepts::KnownSIMD ToRegister_, std::size_t InWidthPerElementIfInt_, bool InSignedIfInt_, std::size_t OutWidthPerElementIfInt_, bool OutSignedIfInt_, EmuConcepts::KnownSIMD FromRegister_>
	[[nodiscard]] inline auto convert(FromRegister_&& from_)
		-> typename std::remove_cvref<ToRegister_>::type
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
