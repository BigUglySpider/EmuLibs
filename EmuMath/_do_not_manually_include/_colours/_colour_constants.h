#ifndef EMU_MATH_COLOUR_CONSTANTS_H_INC_
#define EMU_MATH_COLOUR_CONSTANTS_H_INC_ 1

#include "_colour_t.h"
#include "_colour_validation_layer.h"
#include "../../../EmuCore/TMPHelpers/Values.h"

/// <summary> Namespace for constant colour definitions. </summary>
namespace EmuMath::Colours
{
	/// <summary>
	/// <para> Function used for making colours from provided channels. Primarily exists for the colour constants in the EmuMath::Colours namespace. </para>
	/// <para> Provided r_, g_, and b_ arguments are interpreted as channels; as such, it is important to provide their type so they are interpreted as expected. </para>
	/// </summary>
	/// <typeparam name="OutColour_">Type of EmuMath Colour to output as. A static assertion will fail if this is not an EmuMath Colour.</typeparam>
	/// <typeparam name="R_">Type used to provide the Red channel.</typeparam>
	/// <typeparam name="G_">Type used to provide the Green channel.</typeparam>
	/// <typeparam name="B_">Type used to provide the Blue channel.</typeparam>
	/// <param name="r_">Red channel to convert and set as the output colour's Red channel.</param>
	/// <param name="g_">Green channel to convert and set as the output colour's Green channel.</param>
	/// <param name="b_">Blue channel to convert and set as the output colour's Blue channel.</param>
	/// <returns>Specified output OutColour_ constructed with the provided Red, Green, and Blue channels, converting to matching intensities where necessary.</returns>
	template<class OutColour_, typename R_, typename G_, typename B_>
	[[nodiscard]] constexpr inline OutColour_ _make_colour(const R_& r_, const G_& g_, const B_& b_)
	{
		if constexpr (EmuMath::TMP::is_emu_colour_v<OutColour_>)
		{
			using out_channel_type = typename OutColour_::value_type;
			return OutColour_
			(
				EmuMath::Helpers::colour_convert_channel<out_channel_type, R_>(r_),
				EmuMath::Helpers::colour_convert_channel<out_channel_type, G_>(g_),
				EmuMath::Helpers::colour_convert_channel<out_channel_type, B_>(b_)
			);
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<R_>(), "Attempted to use EmuMath::Colours::_make_colour with a non-EmuMath-Colour output type.");
		}
	}
	template<class OutColour_, typename R_, typename G_, typename B_, typename A_>
	[[nodiscard]] constexpr inline OutColour_ _make_colour(const R_& r_, const G_& g_, const B_& b_, const A_& a_)
	{
		if constexpr (EmuMath::TMP::is_emu_colour_v<OutColour_>)
		{
			using out_channel_type = typename OutColour_::value_type;
			if constexpr (OutColour_::contains_alpha)
			{
				return OutColour_
				(
					EmuMath::Helpers::colour_convert_channel<out_channel_type, R_>(r_),
					EmuMath::Helpers::colour_convert_channel<out_channel_type, G_>(g_),
					EmuMath::Helpers::colour_convert_channel<out_channel_type, B_>(b_),
					EmuMath::Helpers::colour_convert_channel<out_channel_type, A_>(a_)
				);
			}
			else
			{
				return OutColour_
				(
					EmuMath::Helpers::colour_convert_channel<out_channel_type, R_>(r_),
					EmuMath::Helpers::colour_convert_channel<out_channel_type, G_>(g_),
					EmuMath::Helpers::colour_convert_channel<out_channel_type, B_>(b_)
				);
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<R_>(), "Attempted to use EmuMath::Colours::_make_colour with a non-EmuMath-Colour output type.");
		}
	}

	/// <summary> { R: 0.0, G: 0.0, B: 0.0 } </summary>
	template<typename Channel_ = float, bool OutContainsAlpha_ = false>
	[[nodiscard]] constexpr inline EmuMath::Colour<Channel_, OutContainsAlpha_> Black()
	{
		return _make_colour<EmuMath::Colour<Channel_, OutContainsAlpha_>, float, float, float>(0.0f, 0.0f, 0.0f);
	}

	/// <summary> { R: 0.0, G: 0.0, B: 1.0 } </summary>
	template<typename Channel_ = float, bool OutContainsAlpha_ = false>
	[[nodiscard]] constexpr inline EmuMath::Colour<Channel_, OutContainsAlpha_> Blue()
	{
		return _make_colour<EmuMath::Colour<Channel_, OutContainsAlpha_>, float, float, float>(0.0f, 0.0f, 1.0f);
	}

	/// <summary> { R: 0.545, G: 0.271, B: 0.075 } </summary>
	template<typename Channel_ = float, bool OutContainsAlpha_ = false>
	[[nodiscard]] constexpr inline EmuMath::Colour<Channel_, OutContainsAlpha_> Brown()
	{
		return _make_colour<EmuMath::Colour<Channel_, OutContainsAlpha_>, float, float, float>(0.545f, 0.271f, 0.075f);
	}

	/// <summary> { R: 0.392, G: 0.584, B: 0.929 } </summary>
	template<typename Channel_ = float, bool OutContainsAlpha_ = false>
	[[nodiscard]] constexpr inline EmuMath::Colour<Channel_, OutContainsAlpha_> Cornflower()
	{
		return _make_colour<EmuMath::Colour<Channel_, OutContainsAlpha_>, float, float, float>(0.392f, 0.584f, 0.929f);
	}

	/// <summary> { R: 0.0, G: 1.0, B: 1.0 } </summary>
	template<typename Channel_ = float, bool OutContainsAlpha_ = false>
	[[nodiscard]] constexpr inline EmuMath::Colour<Channel_, OutContainsAlpha_> Cyan()
	{
		return _make_colour<EmuMath::Colour<Channel_, OutContainsAlpha_>, float, float, float>(0.0f, 1.0f, 1.0f);
	}

	/// <summary> { R: 0.0, G: 0.5, B: 0.0 } </summary>
	template<typename Channel_ = float, bool OutContainsAlpha_ = false>
	[[nodiscard]] constexpr inline EmuMath::Colour<Channel_, OutContainsAlpha_> Green()
	{
		return _make_colour<EmuMath::Colour<Channel_, OutContainsAlpha_>, float, float, float>(0.0f, 0.5f, 0.0f);
	}

	/// <summary> { R: 0.5, G: 0.5, B: 0.5 } </summary>
	template<typename Channel_ = float, bool OutContainsAlpha_ = false>
	[[nodiscard]] constexpr inline EmuMath::Colour<Channel_, OutContainsAlpha_> Grey()
	{
		return _make_colour<EmuMath::Colour<Channel_, OutContainsAlpha_>, float, float, float>(0.5f, 0.5f, 0.5f);
	}

	/// <summary> { R: 0.294, G: 0.0, B: 0.51 } </summary>
	template<typename Channel_ = float, bool OutContainsAlpha_ = false>
	[[nodiscard]] constexpr inline EmuMath::Colour<Channel_, OutContainsAlpha_> Indigo()
	{
		return _make_colour<EmuMath::Colour<Channel_, OutContainsAlpha_>, float, float, float>(0.294f, 0.0f, 0.51f);
	}

	/// <summary> { R: 0.0, G: 1.0, B: 0.0 } </summary>
	template<typename Channel_ = float, bool OutContainsAlpha_ = false>
	[[nodiscard]] constexpr inline EmuMath::Colour<Channel_, OutContainsAlpha_> Lime()
	{
		return _make_colour<EmuMath::Colour<Channel_, OutContainsAlpha_>, float, float, float>(0.0f, 1.0f, 0.0f);
	}

	/// <summary> { R: 1.0, G: 0.0, B: 1.0 } </summary>
	template<typename Channel_ = float, bool OutContainsAlpha_ = false>
	[[nodiscard]] constexpr inline EmuMath::Colour<Channel_, OutContainsAlpha_> Magenta()
	{
		return _make_colour<EmuMath::Colour<Channel_, OutContainsAlpha_>, float, float, float>(1.0f, 0.0f, 1.0f);
	}

	/// <summary> { R: 0.5, G: 0.0, B: 0.0 } </summary>
	template<typename Channel_ = float, bool OutContainsAlpha_ = false>
	[[nodiscard]] constexpr inline EmuMath::Colour<Channel_, OutContainsAlpha_> Maroon()
	{
		return _make_colour<EmuMath::Colour<Channel_, OutContainsAlpha_>, float, float, float>(0.5f, 0.0f, 0.0f);
	}

	/// <summary> { R: 0.0, G: 0.0, B: 0.5 } </summary>
	template<typename Channel_ = float, bool OutContainsAlpha_ = false>
	[[nodiscard]] constexpr inline EmuMath::Colour<Channel_, OutContainsAlpha_> Navy()
	{
		return _make_colour<EmuMath::Colour<Channel_, OutContainsAlpha_>, float, float, float>(0.0f, 0.0f, 0.5f);
	}

	/// <summary> { R: 0.5, G: 0.5, B: 0.0 } </summary>
	template<typename Channel_ = float, bool OutContainsAlpha_ = false>
	[[nodiscard]] constexpr inline EmuMath::Colour<Channel_, OutContainsAlpha_> Olive()
	{
		return _make_colour<EmuMath::Colour<Channel_, OutContainsAlpha_>, float, float, float>(0.5f, 0.5f, 0.0f);
	}

	/// <summary> { R: 1.0, G: 0.647, B: 0.0 } </summary>
	template<typename Channel_ = float, bool OutContainsAlpha_ = false>
	[[nodiscard]] constexpr inline EmuMath::Colour<Channel_, OutContainsAlpha_> Orange()
	{
		return _make_colour<EmuMath::Colour<Channel_, OutContainsAlpha_>, float, float, float>(1.0f, 0.647f, 0.0f);
	}

	/// <summary> { R: 0.5, G: 0.0, B: 0.5 } </summary>
	template<typename Channel_ = float, bool OutContainsAlpha_ = false>
	[[nodiscard]] constexpr inline EmuMath::Colour<Channel_, OutContainsAlpha_> Purple()
	{
		return _make_colour<EmuMath::Colour<Channel_, OutContainsAlpha_>, float, float, float>(0.5f, 0.0f, 0.5f);
	}

	/// <summary> { R: 1.0, G: 0.0, B: 0.0 } </summary>
	template<typename Channel_ = float, bool OutContainsAlpha_ = false>
	[[nodiscard]] constexpr inline EmuMath::Colour<Channel_, OutContainsAlpha_> Red()
	{
		return _make_colour<EmuMath::Colour<Channel_, OutContainsAlpha_>, float, float, float>(1.0f, 0.0f, 0.0f);
	}

	/// <summary> { R: 0.75, G: 0.75, B: 0.75 } </summary>
	template<typename Channel_ = float, bool OutContainsAlpha_ = false>
	[[nodiscard]] constexpr inline EmuMath::Colour<Channel_, OutContainsAlpha_> Silver()
	{
		return _make_colour<EmuMath::Colour<Channel_, OutContainsAlpha_>, float, float, float>(0.75f, 0.75f, 0.75f);
	}

	/// <summary> { R: 0.0, G: 0.5, B: 0.5 } </summary>
	template<typename Channel_ = float, bool OutContainsAlpha_ = false>
	[[nodiscard]] constexpr inline EmuMath::Colour<Channel_, OutContainsAlpha_> Teal()
	{
		return _make_colour<EmuMath::Colour<Channel_, OutContainsAlpha_>, float, float, float>(0.0f, 0.5f, 0.5f);
	}

	/// <summary> { R: 1.0, G: 1.0, B: 1.0 } </summary>
	template<typename Channel_ = float, bool OutContainsAlpha_ = false>
	[[nodiscard]] constexpr inline EmuMath::Colour<Channel_, OutContainsAlpha_> White()
	{
		return _make_colour<EmuMath::Colour<Channel_, OutContainsAlpha_>, float, float, float>(1.0f, 1.0f, 1.0f);
	}

	/// <summary> { R: 1.0, G: 1.0, B: 0.0 } </summary>
	template<typename Channel_ = float, bool OutContainsAlpha_ = false>
	[[nodiscard]] constexpr inline EmuMath::Colour<Channel_, OutContainsAlpha_> Yellow()
	{
		return _make_colour<EmuMath::Colour<Channel_, OutContainsAlpha_>, float, float, float>(1.0f, 1.0f, 0.0f);
	}
}


#endif
