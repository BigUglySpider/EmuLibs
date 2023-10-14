#ifndef EMU_CORE_COMMON_CONCEPTS_COMMON_REQUIREMENTS_H_INC_
#define EMU_CORE_COMMON_CONCEPTS_COMMON_REQUIREMENTS_H_INC_ 1

#include <type_traits>

namespace EmuCore::Concepts
{
	/// <summary>
	/// <para> Simple concept to constrain a type to be the exact same as the Target_ type. </para>
	/// </summary>
	template<class T_, class Target_>
	concept Same = (std::is_same_v<T_, Target_>);

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

	/// <summary>
	/// <para> Simple concept to constrain a type to be invocable with the provided arguments, regardless of return type. </para>
	/// <para> To require a return type, use `InvocableWithReturn` or `InvocableWithExactReturn`. </para>
	/// </summary>
	template<class T_, class...Args_>
	concept Invocable = requires(T_ item_)
	{
		{ item_(std::declval<Args_>()...) };
	};

	/// <summary>
	/// <para> Simple concept to constrain a type to be invocable with the provided arguments, and return a type compatible with Returns_ (e.g. the same type or a convertible type). </para>
	/// <para> To require an exact return type (instead of one which may be converted), use `InvocableWithExactReturn`. </para>
	/// <para> If return type is irrelevant, use `Invocable`. </para>
	/// </summary>
	template<class T_, class Returns_, class...Args_>
	concept InvocableWithReturn = requires(T_ item_)
	{
		{ item_(std::declval<Args_>()...) } -> std::convertible_to<Returns_>;
	};

	/// <summary>
	/// <para> Simple concept to constrain a type to be invocable with the provided arguments, and return the exact same type as Returns_. </para>
	/// <para> To relax the return requirement to a type that is convertible to the target Returns_ type, use `InvocableWithReturn`. </para>
	/// <para> If return type is irrelevant, use `Invocable`. </para>
	template<class T_, class Returns_, class...Args_>
	concept InvocableWithExactReturn = requires(T_ item_)
	{
		{ item_(std::declval<Args_>()...) } -> Same<Returns_>;
	};
}

namespace EmuConcepts
{
	using namespace EmuCore::Concepts;
}

#endif
