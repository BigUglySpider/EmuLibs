#ifndef EMU_MATH_COLOUR_HELPERS_UNDERLYING_H_INC_
#define EMU_MATH_COLOUR_HELPERS_UNDERLYING_H_INC_ 1

#include "_colour_helpers_underlying_common_includes.h"

namespace EmuMath::Helpers::_underlying_colour_funcs
{
	template<bool IncludeAlpha_, template<typename Lhs__, typename Rhs__> class CmpTemplate_, class AndOr_, class LhsColour_, class RhsColour_>
	[[nodiscard]] constexpr inline bool colour_cmp(const LhsColour_& lhs_, const RhsColour_& rhs_, AndOr_ and_or_)
	{
		if constexpr (EmuMath::TMP::is_emu_colour_v<LhsColour_>)
		{
			if constexpr (EmuMath::TMP::is_emu_colour_v<RhsColour_>)
			{
				using lhs_channel_type = typename LhsColour_::value_type;
				using rhs_channel_type = typename RhsColour_::value_type;
				if constexpr
				(
					std::is_same_v<lhs_channel_type, rhs_channel_type> ||
					(std::is_floating_point_v<lhs_channel_type> && std::is_floating_point_v<rhs_channel_type>)
				)
				{
					// Passed colours contain either the same type, or floating points that lie in the same 0:1 range.
					// --- This allows us to compare without any conversions
					using Cmp_ = CmpTemplate_<lhs_channel_type, rhs_channel_type>;
					Cmp_ cmp_ = Cmp_();
					if constexpr (IncludeAlpha_ && (LhsColour_::contains_alpha || RhsColour_::contains_alpha))
					{
						return and_or_
						(
							cmp_(lhs_.R(), rhs_.R()),
							and_or_
							(
								cmp_(lhs_.G(), rhs_.G()),
								and_or_
								(
									cmp_(lhs_.B(), rhs_.B()),
									cmp_(lhs_.A(), rhs_.A())
								)
							)
						);
					}
					else
					{
						return and_or_
						(
							cmp_(lhs_.R(), rhs_.R()),
							and_or_
							(
								cmp_(lhs_.G(), rhs_.G()),
								cmp_(lhs_.B(), rhs_.B())
							)
						);
					}
				}
				else
				{
					// Passed colours contain incompatible intensity values, so a conversion is required
					// --- Prioritise floating-point comparison as float->int conversion is lossy which can lead to situations of (A == B) && (B != A)
					// --- These are recursive calls of this function which guarantee that the above constexpr branch is true
					// --- Conversions are automatically performed upon construction
					if constexpr (std::is_floating_point_v<rhs_channel_type>)
					{
						using lhs_conversion_type = EmuMath::Colour<rhs_channel_type, LhsColour_::contains_alpha>;
						return colour_cmp<IncludeAlpha_, CmpTemplate_, AndOr_&>(lhs_conversion_type(lhs_), rhs_, and_or_);
					}
					else
					{
						using rhs_conversion_type = EmuMath::Colour<lhs_channel_type, RhsColour_::contains_alpha>;
						return colour_cmp<IncludeAlpha_, CmpTemplate_, AndOr_&>(lhs_, rhs_conversion_type(rhs_), and_or_);
					}
				}
			}
			else
			{
				static_assert(false, "Attempted to compare two EmuMath Colours, but the provided rhs_ was not an EmuMath colour.");
			}
		}
		else
		{
			static_assert(false, "Attempted to compare two EmuMath Colours, but the provided lhs_ was not an EmuMath colour.");
		}
	}
}

#endif
