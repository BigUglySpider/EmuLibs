#ifndef EMU_MATH_SIMD_HELPERS_TEMPLATE_BLEND_H_INC_
#define EMU_MATH_SIMD_HELPERS_TEMPLATE_BLEND_H_INC_ 1

#include "_underlying_template_helpers/_simd_helpers_underlying_blend.h"

namespace EmuMath::SIMD
{
	template<std::size_t PerElementWidthIfInt_ = 32, class Register_>
	[[nodiscard]] inline Register_ blendv(Register_ a_, Register_ b_, Register_ mask_)
	{
		using register_type_uq = typename EmuCore::TMPHelpers::remove_ref_cv<Register_>::type;
		if constexpr (EmuMath::SIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			return _underlying_simd_helpers::_blendv<PerElementWidthIfInt_>(a_, b_, mask_);
		}
		else
		{
			static_assert(false, "Attempted to perform EmuMath::SIMD::blendv with an unsupported or unrecognised type as the passed Register_.");
		}
	}

	template<bool...IndexUsesB_, class Register_>
	[[nodiscard]] inline Register_ blend(Register_ a_, Register_ b_)
	{
		using register_type_uq = typename EmuCore::TMPHelpers::remove_ref_cv<Register_>::type;
		if constexpr (EmuMath::SIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			return _underlying_simd_helpers::_blend<IndexUsesB_...>(a_, b_);
		}
		else
		{
			static_assert(false, "Attempted to perform EmuMath::SIMD::blend with an unsupported or unrecognised type as the passed Register_.");
		}
	}
}

#endif
