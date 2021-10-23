#ifndef EMU_MATH_COLOUR_ARITHMETIC_FUNCTORS_H_INC_
#define EMU_MATH_COLOUR_ARITHMETIC_FUNCTORS_H_INC_ 1

#include "ColourT.h"
#include "ColourValidationLayer.h"

namespace EmuCore
{
	template<class ChannelA_, bool ContainsAlphaA_, class B_, class T_>
	struct do_lerp<EmuMath::Colour<ChannelA_, ContainsAlphaA_>, B_, T_>
	{
		constexpr do_lerp()
		{
		}
		[[nodiscard]] constexpr inline auto operator()
		(
			const EmuMath::Colour<ChannelA_, ContainsAlphaA_>& a_,
			const B_& b_,
			const T_& t_
		) const
		{
			return a_.Lerp(b_, t_);
		}
	};

	template<class ChannelA_, bool ContainsAlphaA_, class ValidationFuncA_, class B_, class T_>
	struct do_lerp<EmuMath::Helpers::_colour_validation_layer<ChannelA_, ContainsAlphaA_, ValidationFuncA_>, B_, T_>
	{
		constexpr do_lerp()
		{
		}
		[[nodiscard]] constexpr inline auto operator()
		(
			const EmuMath::Colour<ChannelA_, ContainsAlphaA_>& a_,
			const B_& b_,
			const T_& t_
		) const
		{
			return a_.Lerp(b_, t_);
		}
		[[nodiscard]] constexpr inline auto operator()
		(
			const EmuMath::Helpers::_colour_validation_layer<ChannelA_, ContainsAlphaA_, ValidationFuncA_>& a_,
			const B_& b_,
			const T_& t_
		) const
		{
			return a_.Lerp(b_, t_);
		}
	};
}

#endif
