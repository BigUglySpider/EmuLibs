#ifndef EMU_CORE_COMMON_CONCEPTS_COMMON_REQUIREMENTS_H_INC_
#define EMU_CORE_COMMON_CONCEPTS_COMMON_REQUIREMENTS_H_INC_ 1

#include <type_traits>

namespace EmuCore::Concepts
{
	/// <summary>
	/// <para> Simple concept to constrain a type to be const-qualified. </para>
	/// </summary>
	template<typename T_>
	concept Constant = (std::is_const_v<T_>);

	/// <summary>
	/// <para> Simple concept to constrain a type to *not* be const-qualified. </para>
	/// </summary>
	template<typename T_>
	concept Writable = !(Constant<T_>);

	/// <summary>
	/// <para> Simple concept to constrain a type to be a pointer to a type that is not const-qualified. </para>
	/// <para> The pointer itself can be const qualified (e.g. int* const is valid, but const int* is not valid). </para>
	/// </summary>
	template<typename T_>
	concept WritablePointer = 
	(
		std::is_pointer_v<T_> &&
		!std::is_const_v<typename std::remove_pointer<T_>::type>
	);

	/// <summary>
	/// <para> Simple concept to constrain a pair of types to be of a mutual type but not necessarily of the same cvref qualification. </para>
	/// </summary>
	template<class T_, class Target_>
	concept UnqualifiedMatch =
	(
		std::is_same_v<typename std::remove_cvref<T_>::type, typename std::remove_cvref<Target_>::type>
	);
}

namespace EmuConcepts
{
	using namespace EmuCore::Concepts;
}

#endif
