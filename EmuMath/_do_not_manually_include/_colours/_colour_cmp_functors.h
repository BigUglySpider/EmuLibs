#ifndef EMU_MATH_COLOUR_COMPARISON_FUNCTORS_H_INC_
#define EMU_MATH_COLOUR_COMPARISON_FUNCTORS_H_INC_ 1

#include "_colour_t.h"
#include "_colour_validation_layer.h"
#include "../../../EmuCore/Functors/Comparators.h"

namespace EmuCore
{
	template<class LhsChannel_, bool LhsContainsAlpha_, class Rhs_>
	struct do_cmp_equal_to<EmuMath::Colour<LhsChannel_, LhsContainsAlpha_>, Rhs_>
	{
		constexpr do_cmp_equal_to()
		{
		}
		[[nodiscard]] constexpr inline bool operator()(const EmuMath::Colour<LhsChannel_, LhsContainsAlpha_>& lhs_, const Rhs_& rhs_) const
		{
			return lhs_ == rhs_;
		}
	};
	template<class LhsChannel_, bool LhsContainsAlpha_, class LhsValidationFunc_, class Rhs_>
	struct do_cmp_equal_to<EmuMath::Helpers::_colour_validation_layer<LhsChannel_, LhsContainsAlpha_, LhsValidationFunc_>, Rhs_>
	{
		constexpr do_cmp_equal_to()
		{
		}
		[[nodiscard]] constexpr inline bool operator()
		(
			const EmuMath::Helpers::_colour_validation_layer<LhsChannel_, LhsContainsAlpha_, LhsValidationFunc_>& lhs_,
			const Rhs_& rhs_
		) const
		{
			return lhs_ == rhs_;
		}
	};
}

#endif
