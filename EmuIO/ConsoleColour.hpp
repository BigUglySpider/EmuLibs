#ifndef EMU_IO_CONSOLE_COLOUR_HPP_INC_
#define EMU_IO_CONSOLE_COLOUR_HPP_INC_ 1

#include <cstdint>

#include "../EmuCore/CommonPreprocessor/Compiler.h"

#if EMU_CORE_IS_MSVC
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <Windows.h>
#else
#include <iostream>
#include <string>
#endif

namespace EmuIO
{
	/*
	* @brief Flags indicating a colour to communicate to the console.
	*        The values are guaranteed to translate to the colour code used to set text colour for the target operating system.
	*        You must not input or use underlying values directly unless absolutely certain about what the range of values will be.
	*/
	enum class ConsoleColour : std::uint32_t
	{
#if EMU_CORE_IS_MSVC
		Black       = 0,
		Blue        = 1,
		Green       = 2,
		Cyan        = 3,
		Red         = 4,
		Purple      = 5,
		Yellow      = 6,
		White       = 7,
		Grey        = 8,
		LightBlue   = 9,
		LightGreen  = 10,
		LightCyan   = 11,
		LightRed    = 12,
		LightPurple = 13,
		LightYellow = 14,
		LightWhite  = 15,
#else
		Black       = 30,
		Blue        = 34,
		Green       = 32,
		Cyan        = 36,
		Red         = 31,
		Purple      = 35,
		Yellow      = 33,
		White       = 37,
		Grey        = 90,
		LightBlue   = 94,
		LightGreen  = 92,
		LightCyan   = 96,
		LightRed    = 91,
		LightPurple = 95,
		LightYellow = 93,
		LightWhite  = 97,
#endif
		Gray      = Grey,
		Aqua      = Cyan,
		LightAqua = LightCyan
	};

	inline void SetConsoleColour(const ConsoleColour colour)
	{
#if EMU_CORE_IS_MSVC
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), static_cast<WORD>(colour));
#else
		std::cout << (std::string{ "\033[" } + std::to_string(static_cast<int>(colour)) + "m");
#endif
	}
}

#endif
