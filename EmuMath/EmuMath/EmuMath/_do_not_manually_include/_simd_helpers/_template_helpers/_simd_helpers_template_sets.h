#ifndef EMU_MATH_SIMD_HELPERS_TEMPLATE_SETS_H_INC_
#define EMU_MATH_SIMD_HELPERS_TEMPLATE_SETS_H_INC_ 1

#include "_underlying_template_helpers/_common_underlying_simd_template_helper_includes.h"
#include "_underlying_template_helpers/_simd_helpers_underlying_set.h"

namespace EmuMath::SIMD
{
	template<class Register_, std::size_t ElementWidthIfInt_ = 32, typename...Args_>
	[[nodiscard]] inline Register_ simd_set(Args_&&...args_)
	{
		using register_type_uq = typename EmuCore::TMPHelpers::remove_ref_cv<Register_>::type;
		if constexpr (EmuMath::SIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			constexpr std::size_t num_args_ = sizeof...(Args_);
			if constexpr (EmuMath::SIMD::TMP::is_floating_point_simd_register_v<register_type_uq>)
			{
				return _underlying_simd_helpers::_set_fp<Register_>(args_...);
			}
			else
			{
				// Integral
				return _underlying_simd_helpers::_set_int<Register_, ElementWidthIfInt_>(args_...);
			}
		}
		else
		{
			static_assert(false, "Attempted to perform EmuMath::SIMD::simd_set with an unsupported type as the passed Register_.");
		}
	}
}

#endif
