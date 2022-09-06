#ifndef EMU_CORE_COMMON_CONCEPTS_ARITHMETIC_H_INC_
#define EMU_CORE_COMMON_CONCEPTS_ARITHMETIC_H_INC_ 1

#include "../TMPHelpers/TypeConvertors.h"
#include <concepts>

namespace EmuCore::Concepts
{
	template<class T_>
	concept Arithmetic =
	(
		(std::integral<typename EmuCore::TMP::remove_ref_cv<T_>::type>) ||
		(std::floating_point<typename EmuCore::TMP::remove_ref_cv<T_>::type>)
	);

	template<class T_>
	concept SignedArithmetic =
	(
		(std::signed_integral<typename EmuCore::TMP::remove_ref_cv<T_>::type>) ||
		(std::floating_point<typename EmuCore::TMP::remove_ref_cv<T_>::type>)
	);

	template<class T_>
	concept UnsignedArithmetic =
	(
		(std::unsigned_integral<typename EmuCore::TMP::remove_ref_cv<T_>::type>)
	);
}

namespace EmuConcepts
{
	using namespace EmuCore::Concepts;
}

#endif
