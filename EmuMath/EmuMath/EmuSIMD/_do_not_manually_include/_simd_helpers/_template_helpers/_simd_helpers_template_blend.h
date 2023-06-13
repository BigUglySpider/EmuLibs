#ifndef EMU_SIMD_HELPERS_TEMPLATE_BLEND_H_INC_
#define EMU_SIMD_HELPERS_TEMPLATE_BLEND_H_INC_ 1

#include "_underlying_template_helpers/_all_underlying_templates.h"
#include "_underlying_template_helpers/_generic_funcs/_forward_declarations/_forward_template_blends.h"
#include "../../../../EmuCore/TMPHelpers/Values.h"

namespace EmuSIMD
{
	template<std::size_t PerElementWidthIfInt_, EmuConcepts::KnownSIMD RegisterA_, EmuConcepts::UnqualifiedMatch<RegisterA_> RegisterB_, EmuConcepts::UnqualifiedMatch<RegisterA_> MaskRegister_>
	[[nodiscard]] inline auto blendv(RegisterA_&& a_, RegisterB_&& b_, MaskRegister_&& mask_)
		-> typename std::remove_cvref<RegisterA_>::type
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<RegisterA_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			return _underlying_simd_helpers::_blendv<PerElementWidthIfInt_>
			(
				std::forward<RegisterA_>(a_),
				std::forward<RegisterB_>(b_),
				std::forward<MaskRegister_>(mask_)
			);
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<RegisterA_>(), "Attempted to perform EmuSIMD::blendv with an unsupported or unrecognised type as the passed Register_.");
		}
	}

	template<bool...IndexUsesB_, EmuConcepts::KnownSIMD RegisterA_, EmuConcepts::UnqualifiedMatch<RegisterA_> RegisterB_>
	[[nodiscard]] inline auto blend(RegisterA_&& a_, RegisterB_&& b_)
		-> typename std::remove_cvref<RegisterA_>::type
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<RegisterA_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			return _underlying_simd_helpers::_blend<IndexUsesB_...>
			(
				std::forward<RegisterA_>(a_),
				std::forward<RegisterB_>(b_)
			);
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<RegisterA_>(), "Attempted to perform EmuSIMD::blend with an unsupported or unrecognised type as the passed Register_.");
		}
	}
}

#endif
