#ifndef EMU_CORE_COMMON_CONCEPTS_CHARACTERS_H_INC_
#define EMU_CORE_COMMON_CONCEPTS_CHARACTERS_H_INC_ 1

#include <type_traits>

namespace EmuCore::Concepts
{
	template<typename T_>
	concept BasicByteChar =
	(
		std::is_same_v<char, typename std::remove_cvref<T_>::type> ||
		std::is_same_v<unsigned char, typename std::remove_cvref<T_>::type> ||
		std::is_same_v<signed char, typename std::remove_cvref<T_>::type>
	);

	template<typename T_>
	concept BasicChar8 = (std::is_same_v<char8_t, typename std::remove_cvref<T_>::type>);

	template<typename T_>
	concept BasicChar16 = (std::is_same_v<char16_t, typename std::remove_cvref<T_>::type>);

	template<typename T_>
	concept BasicChar32 = (std::is_same_v<char32_t, typename std::remove_cvref<T_>::type>);

	template<typename T_>
	concept BasicWideChar = (std::is_same_v<wchar_t, typename std::remove_cvref<T_>::type>);

	template<typename T_>
	concept AnyBasicChar =
	(
		(BasicByteChar<T_>) ||
		(BasicChar8<T_>) ||
		(BasicChar16<T_>) ||
		(BasicChar32<T_>) ||
		(BasicWideChar<T_>)
	);
}

namespace EmuConcepts
{
	using namespace EmuCore::Concepts;
}

#endif
