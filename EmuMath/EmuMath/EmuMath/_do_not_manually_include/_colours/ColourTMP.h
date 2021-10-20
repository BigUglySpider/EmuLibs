#ifndef EMU_MATH_COLOUR_TMP_H_INC_
#define EMU_MATH_COLOUR_TMP_H_INC_ 1

#include <type_traits>

namespace EmuMath
{
	template<typename Channel_>
	struct ColourRGB;

	template<typename Channel_>
	struct ColourRGBA;
}

namespace EmuMath::TMP
{
	template<class T_>
	struct is_emu_colour
	{
		static constexpr bool value = std::conditional_t
		<
			// This is a recursive check to make sure that T_ does not have modifiers that may lead to false negatives
			std::is_same_v<T_, std::remove_reference_t<std::remove_cv_t<T_>>>,
			std::false_type,
			is_emu_colour<std::remove_reference_t<std::remove_cv_t<T_>>>
		>::value;
	};
	template<typename T_>
	struct is_emu_colour<EmuMath::ColourRGB<T_>>
	{
		static constexpr bool value = true;
	};
	template<typename T_>
	struct is_emu_colour<EmuMath::ColourRGBA<T_>>
	{
		static constexpr bool value = true;
	};
	template<class T_>
	static constexpr bool is_emu_colour_v = is_emu_colour<T_>::value;
}

#endif
