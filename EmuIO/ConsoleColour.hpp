#ifndef EMU_IO_CONSOLE_COLOUR_HPP_INC_
#define EMU_IO_CONSOLE_COLOUR_HPP_INC_ 1

#include <cstdint>
#include <iostream>

#include "../EmuCore/CommonPreprocessor/Compiler.h"

#if EMU_CORE_IS_MSVC
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <Windows.h>
#else
#include <string>
#endif

// Define to use virtual terminal for handling colours in Windows
// --- Be aware that, although most modern users will be able to use this, it is not entirely cross-generation compatible
//#define EMU_IO_USE_VIRTUAL_TERMINAL_IN_WINDOWS

namespace EmuIO
{
	/*
	* @brief Flags indicating a colour to communicate to the console.
	*        The values are guaranteed to translate to the colour code used to set text colour for the target operating system.
	*        You must not input or use underlying values directly unless absolutely certain about what the range of values will be.
	*/
	enum class ConsoleColour : std::uint32_t
	{
#if EMU_CORE_IS_MSVC && !defined(EMU_IO_USE_VIRTUAL_TERMINAL_IN_WINDOWS)
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

		Gray      = Grey,     // Alias of `Grey`
		Aqua      = Cyan,     // Alias of `Cyan`
		LightAqua = LightCyan // Alias of `LightCyan
	};

	inline void SetConsoleColour(const ConsoleColour colour)
	{
#if EMU_CORE_IS_MSVC
	#ifdef EMU_IO_USE_VIRTUAL_TERMINAL_IN_WINDOWS
		static bool _enabled_virtual{ false };
		if (!_enabled_virtual)
		{
			HANDLE _stdout_handle{ GetStdHandle(STD_OUTPUT_HANDLE) };
			DWORD _mode{};
			GetConsoleMode(_stdout_handle, &_mode);
			_mode |= ENABLE_PROCESSED_OUTPUT | ENABLE_VIRTUAL_TERMINAL_PROCESSING;
			SetConsoleMode(_stdout_handle, _mode);
			_enabled_virtual = true;
		}
		std::cout << (std::string{ "\033[" } + std::to_string(static_cast<int>(colour)) + "m");
	#else
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), static_cast<WORD>(colour));
	#endif
#else
		std::cout << (std::string{ "\033[" } + std::to_string(static_cast<int>(colour)) + "m");
#endif
	}

	template<bool Err>
	class PrintColoured
	{
	public:
		static constexpr EmuIO::ConsoleColour default_colour = EmuIO::ConsoleColour::LightWhite;

		PrintColoured(EmuIO::ConsoleColour colour_) :
			_colour{ colour_ }
		{
		}

		template<class T>
		PrintColoured<Err>& operator<<(T&& to_append)
		{
			SetConsoleColour(_colour);
			if constexpr (Err)
			{
				std::cerr << std::forward<T>(to_append);
			}
			else
			{
				std::cout << std::forward<T>(to_append);
			}
			SetConsoleColour(default_colour);
			return *this;
		}

		PrintColoured<Err>& operator<<(std::ostream& (*pManip)(std::ostream&))
		{
			(*pManip)(std::cout);
			return *this;
		}

		template<class...Ts>
		requires(sizeof...(Ts) != 0)
		PrintColoured& Append(Ts&&...to_append)
		{
			SetConsoleColour(_colour);
			if constexpr (Err)
			{
				((std::cerr << std::forward<Ts>(to_append)), ...);
			}
			else
			{
				((std::cout << std::forward<Ts>(to_append)), ...);
			}
			SetConsoleColour(default_colour);
		}

	private:
		EmuIO::ConsoleColour _colour;
	};
}

#endif
