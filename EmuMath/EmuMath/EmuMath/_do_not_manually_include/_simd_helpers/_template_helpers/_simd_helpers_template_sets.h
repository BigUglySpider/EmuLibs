#ifndef EMU_MATH_SIMD_HELPERS_TEMPLATE_SETS_H_INC_
#define EMU_MATH_SIMD_HELPERS_TEMPLATE_SETS_H_INC_ 1

#include "_underlying_template_helpers/_common_underlying_simd_template_helper_includes.h"
#include "_underlying_template_helpers/_simd_helpers_underlying_set.h"

namespace EmuMath::SIMD
{
	template<class Register_, std::size_t ElementWidthIfInt_ = 32, typename...Args_>
	[[nodiscard]] inline Register_ set(Args_&&...args_)
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
				return _underlying_simd_helpers::_set_int<Register_, ElementWidthIfInt_>(args_...);
			}
		}
		else
		{
			static_assert(false, "Attempted to perform EmuMath::SIMD::set with an unsupported type as the passed Register_.");
		}
	}

	template<class Register_, std::size_t ElementWidthIfInt_ = 32, typename Val_>
	[[nodiscard]] inline Register_ set1(const Val_& val_)
	{
		using register_type_uq = typename EmuCore::TMPHelpers::remove_ref_cv<Register_>::type;
		if constexpr (EmuMath::SIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			return _underlying_simd_helpers::_set1<Register_, ElementWidthIfInt_>(val_);
		}
		else
		{
			static_assert(false, "Attempted to perform EmuMath::SIMD::set1 with an unsupported type as the passed Register_.");
		}
	}
}

#endif
