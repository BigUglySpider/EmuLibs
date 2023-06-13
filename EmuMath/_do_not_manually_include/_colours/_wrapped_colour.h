#ifndef EMU_MATH_COLOUR_WRAPPED_H_INC_
#define EMU_MATH_COLOUR_WRAPPED_H_INC_ 1

#include "_colour_validation_layer.h"

namespace EmuMath
{
	namespace Helpers
	{
		template<typename TargetChannelType_>
		struct do_colour_wrap
		{
			constexpr do_colour_wrap()
			{
			}

			template<typename Channel_, bool ContainsAlpha_>
			constexpr inline void operator()(EmuMath::Colour<Channel_, ContainsAlpha_>& colour_) const
			{
				colour_.Wrap();
			}
			template<typename Val_, typename = std::enable_if_t<!EmuMath::TMP::is_emu_colour_v<Val_>>>
			[[nodiscard]] constexpr inline TargetChannelType_ operator()(Val_ set_val_) const
			{
				// We can do a direct conversion if compatible, but otherwise we'll need a cast
				// --- This is due to sets viewing all passed values as a form of the stored channel_type
				// ------ This in itself is to remove ambiguity when providing integral literals for sets,
				// ------ since converting them to an intensity would mean knowing exactly what byte-width a user desires,
				// ------ which would make sets highly prone to bugs.
				if constexpr (EmuMath::Helpers::_underlying_colour_funcs::compatible_channel_types<TargetChannelType_, Val_>())
				{
					return EmuMath::Helpers::colour_wrap_channel<TargetChannelType_, Val_>(set_val_);
				}
				else
				{
					return EmuMath::Helpers::colour_wrap_channel<TargetChannelType_, TargetChannelType_>(static_cast<TargetChannelType_>(set_val_));
				}
			}
		};
	}

	template<typename Channel_, bool ContainsAlpha_>
	using WrappedColour = EmuMath::Helpers::_colour_validation_layer<Channel_, ContainsAlpha_, EmuMath::Helpers::do_colour_wrap<Channel_>>;

	template<typename Channel_>
	using WrappedColourRGB = WrappedColour<Channel_, false>;

	template<typename Channel_>
	using WrappedColourRGBA = WrappedColour<Channel_, true>;
}

#endif
