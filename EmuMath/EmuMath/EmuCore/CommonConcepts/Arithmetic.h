#ifndef EMU_CORE_COMMON_CONCEPTS_ARITHMETIC_H_INC_
#define EMU_CORE_COMMON_CONCEPTS_ARITHMETIC_H_INC_ 1

#include <concepts>
#include <type_traits>

namespace EmuCore::Concepts
{
	template<class T_>
	concept FloatingPoint = (std::floating_point<typename std::remove_cvref<T_>::type>);

	template<class T_>
	concept Integer = (std::integral<typename std::remove_cvref<T_>::type>);

	template<class T_>
	concept SignedInteger = (std::signed_integral<typename std::remove_cvref<T_>::type>);

	template<class T_>
	concept UnsignedInteger = (std::unsigned_integral<typename std::remove_cvref<T_>::type>);

	template<class T_>
	concept Arithmetic = ((FloatingPoint<T_>) || (Integer<T_>));

	template<class T_>
	concept SignedArithmetic = ((FloatingPoint<T_>) || (SignedInteger<T_>));

	template<class T_>
	concept UnsignedArithmetic = ((UnsignedInteger<T_>));
}

namespace EmuConcepts
{
	using namespace EmuCore::Concepts;
}

#endif
