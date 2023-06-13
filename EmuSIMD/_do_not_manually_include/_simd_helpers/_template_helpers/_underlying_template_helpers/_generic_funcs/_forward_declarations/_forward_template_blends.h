#ifndef EMU_SIMD_HELPERS_FORWARD_TEMPLATE_BLEND_H_INC_
#define EMU_SIMD_HELPERS_FORWARD_TEMPLATE_BLEND_H_INC_ 1

#include "_forward_tmp.h"
#include "../../../../../../../EmuCore/CommonConcepts/CommonRequirements.h"

namespace EmuSIMD
{
	template<std::size_t PerElementWidthIfInt_ = 32, EmuConcepts::KnownSIMD RegisterA_, EmuConcepts::UnqualifiedMatch<RegisterA_> RegisterB_, EmuConcepts::UnqualifiedMatch<RegisterA_> MaskRegister_>
	[[nodiscard]] inline auto blendv(RegisterA_&& a_, RegisterB_&& b_, MaskRegister_&& mask_)
		-> typename std::remove_cvref<RegisterA_>::type;

	template<bool...IndexUsesB_, EmuConcepts::KnownSIMD RegisterA_, EmuConcepts::UnqualifiedMatch<RegisterA_> RegisterB_>
	[[nodiscard]] inline auto blend(RegisterA_&& a_, RegisterB_&& b_)
		-> typename std::remove_cvref<RegisterA_>::type;
}

#endif
