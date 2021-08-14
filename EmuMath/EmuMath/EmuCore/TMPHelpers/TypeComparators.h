#ifndef EMU_CORE_TMP_HELPERS_TYPE_COMPARATORS_H_INC_
#define EMU_CORE_TMP_HELPERS_TYPE_COMPARATORS_H_INC_

#include <type_traits>

namespace EmuCore::TMPHelpers
{
	/// <summary> Finds the largest byte-sized type of the passed options. For matching type sizes, the leftmost type receives priority. </summary>
	/// <typeparam name="X_">First type to compare. Required.</typeparam>
	/// <typeparam name="Y_">Second type to compare. Required.</typeparam>
	/// <typeparam name="Others_">All additional types to compare. Optional.</typeparam>
	template<class X_, class Y_, class...Others_>
	struct highest_byte_size
	{
		using type = typename highest_byte_size<X_, typename highest_byte_size<Y_, Others_...>::type>::type;
	};
	/// <summary> Finds the largest byte-sized type of the passed options. For matching type sizes, X_ receives priority. </summary>
	/// <typeparam name="X_">First type to compare.</typeparam>
	/// <typeparam name="Y_">Second type to compare.</typeparam>
	template<class X_, class Y_>
	struct highest_byte_size<X_, Y_>
	{
		using type = std::conditional_t<(sizeof(X_) >= sizeof(Y_)), X_, Y_>;
	};
	/// <summary> The largest byte-sized type of the passed options. For matching type sizes, the leftmost type receives priority. </summary>
	/// <typeparam name="X_">First type to compare. Required.</typeparam>
	/// <typeparam name="Y_">Second type to compare. Required.</typeparam>
	/// <typeparam name="Others_">All additional types to compare. Optional.</typeparam>
	template<class X_, class Y_, class...Others_>
	using highest_byte_size_t = typename highest_byte_size<X_, Y_, Others_...>::type;

	/// <summary> Finds the smallest byte-sized type of the passed options. For matching type sizes, the leftmost type receives priority. </summary>
	/// <typeparam name="X_">First type to compare. Required.</typeparam>
	/// <typeparam name="Y_">Second type to compare. Required.</typeparam>
	/// <typeparam name="Others_">All additional types to compare. Optional.</typeparam>
	template<class X_, class Y_, class...Others_>
	struct lowest_byte_size
	{
		using type = typename lowest_byte_size<X_, typename lowest_byte_size<Y_, Others_...>::type>::type;
	};
	/// <summary> Finds the smallest byte-sized type of the passed options. For matching type sizes, X_ receives priority. </summary>
	/// <typeparam name="X_">First type to compare.</typeparam>
	/// <typeparam name="Y_">Second type to compare.</typeparam>
	template<class X_, class Y_>
	struct lowest_byte_size<X_, Y_>
	{
		using type = std::conditional_t<(sizeof(X_) <= sizeof(Y_)), X_, Y_>;
	};
	/// <summary> The smallest byte-sized type of the passed options. For matching type sizes, the leftmost type receives priority. </summary>
	/// <typeparam name="X_">First type to compare. Required.</typeparam>
	/// <typeparam name="Y_">Second type to compare. Required.</typeparam>
	/// <typeparam name="Others_">All additional types to compare. Optional.</typeparam>
	template<class X_, class Y_, class...Others_>
	using lowest_byte_size_t = typename lowest_byte_size<X_, Y_, Others_...>::type;
	/// <summary> The number of bytes within the lowest type of passed options. </summary>
	/// <typeparam name="X_">First type to compare. Required.</typeparam>
	/// <typeparam name="Y_">Second type to compare. Required.</typeparam>
	/// <typeparam name="Others_">All additional types to compare. Optional.</typeparam>
	template<class X_, class Y_, class...Others_>
	static constexpr std::size_t lowest_byte_size_v = sizeof(lowest_byte_size_t<X_, Y_, Others_...>);

	/// <summary> Underlying check used for all is_any_ values. Performs the passed check_ with each provided parameter until one is true or they are exhausted. </summary>
	/// <typeparam name="First">The first type to perform the check on. Required.</typeparam>
	/// <typeparam name="Others">All additional types to perform the check on. Optional.</typeparam>
	template<template<class OutT_> class check_, class First, class...Others>
	struct is_any_check
	{
		static constexpr bool value = check_<First>::value ? true : is_any_check<check_, Others...>::value;
	};
	/// <summary> Underlying check used for all is_any_ values. Contained value is set to the value of the passed check_ with the provided First parameter. </summary>
	/// <typeparam name="First">Type to perform the check on.</typeparam>
	template<template<class OutT_> class check_, class First>
	struct is_any_check<check_, First>
	{
		static constexpr bool value = check_<First>::value;
	};
	/// <summary> Inverted variant of is_any_check, which in turn is the underlying check for all is_any_not_ values. </summary>
	/// <typeparam name="First">The first type to perform the check on. Required.</typeparam>
	/// <typeparam name="Others">All additional types to perform the check on. Optional.</typeparam>
	template<template<class OutT_> class check_, class First, class...Others>
	struct is_any_not_check
	{
		static constexpr bool value = !check_<First>::value ? true : is_any_not_check<check_, Others...>::value;
	};
	/// <summary> Inverted variant of is_any_check, which in turn is the underlying check for all is_any_not_ values. </summary>
	/// <typeparam name="First">Type to perform the check on.</typeparam>
	template<template<class OutT_> class check_, class First>
	struct is_any_not_check<check_, First>
	{
		static constexpr bool value = !check_<First>::value;
	};

	/// <summary> Underlying check used for all are_all_ values. Performs the passed check_ with each provided parameter until one is false or they are exhausted. </summary>
	/// <typeparam name="First">The first type to perform the check on. Required.</typeparam>
	/// <typeparam name="Others">All additional types to perform the check on. Optional.</typeparam>
	template<template<class OutT_> class check_, class First, class...Others>
	struct are_all_check
	{
		static constexpr bool value = check_<First>::value ? are_all_check<check_, Others...>::value : false;
	};
	/// <summary> Underlying check used for all are_all_ values. Contained value is set to the value of the passed check_ with the provided First parameter. </summary>
	/// <typeparam name="First">Type to perform the check on.</typeparam>
	template<template<class OutT_> class check_, class First>
	struct are_all_check<check_, First>
	{
		static constexpr bool value = check_<First>::value;
	};
	/// <summary> Inverted variant of are_all_check, which in turn is the underlying check for all are_all_not_ values. </summary>
	/// <typeparam name="First">The first type to perform the check on. Required.</typeparam>
	/// <typeparam name="Others">All additional types to perform the check on. Optional.</typeparam>
	template<template<class OutT_> class check_, class First, class...Others>
	struct are_all_not_check
	{
		static constexpr bool value = !check_<First>::value ? is_any_not_check<check_, Others...>::value : false;
	};
	/// <summary> Inverted variant of are_all_check, which in turn is the underlying check for all are_all_not_ values. </summary>
	/// <typeparam name="First">Type to perform the check on.</typeparam>
	template<template<class OutT_> class check_, class First>
	struct are_all_not_check<check_, First>
	{
		static constexpr bool value = !check_<First>::value;
	};

	/// <summary> Boolean indicating if any of the provided types are signed. </summary>
	/// <typeparam name="T">First type to check. Required.</typeparam>
	/// <typeparam name="Others">All types to check after the first. Optional.</typeparam>
	template<class T, class...Others>
	static constexpr bool is_any_signed_v = is_any_check<std::is_signed, T, Others...>::value;
	/// <summary> Boolean indicating if all provided types are signed. </summary>
	/// <typeparam name="T">First type to check. Required.</typeparam>
	/// <typeparam name="Others">All types to check after the first. Optional.</typeparam>
	template<class T, class...Others>
	static constexpr bool are_all_signed_v = are_all_check<std::is_signed, T, Others...>::value;
	/// <summary> Boolean indicating if any of the provided types are not signed (not to be confused with is_any_unsigned_v). </summary>
	/// <typeparam name="T">First type to check. Required.</typeparam>
	/// <typeparam name="Others">All types to check after the first. Optional.</typeparam>
	template<class T, class...Others>
	static constexpr bool is_any_not_signed_v = is_any_not_check<std::is_signed, T, Others...>::value;
	/// <summary> Boolean indicating if all provided types are not signed (not to be confused with are_all_unsigned_v). </summary>
	/// <typeparam name="T">First type to check. Required.</typeparam>
	/// <typeparam name="Others">All types to check after the first. Optional.</typeparam>
	template<class T, class...Others>
	static constexpr bool are_all_not_signed_v = are_all_not_check<std::is_signed, T, Others...>::value;

	/// <summary> Boolean indicating if any of the provided types are unsigned. </summary>
	/// <typeparam name="T">First type to check. Required.</typeparam>
	/// <typeparam name="Others">All types to check after the first. Optional.</typeparam>
	template<class T, class...Others>
	static constexpr bool is_any_unsigned_v = is_any_check<std::is_unsigned, T, Others...>::value;
	/// <summary> Boolean indicating if all provided types are unsigned. </summary>
	/// <typeparam name="T">First type to check. Required.</typeparam>
	/// <typeparam name="Others">All types to check after the first. Optional.</typeparam>
	template<class T, class...Others>
	static constexpr bool are_all_unsigned_v = are_all_check<std::is_unsigned, T, Others...>::value;
	/// <summary> Boolean indicating if any of the provided types are not unsigned (not to be confused with is_any_signed_v). </summary>
	/// <typeparam name="T">First type to check. Required.</typeparam>
	/// <typeparam name="Others">All types to check after the first. Optional.</typeparam>
	template<class T, class...Others>
	static constexpr bool is_any_not_unsigned_v = is_any_not_check<std::is_unsigned, T, Others...>::value;
	/// <summary> Boolean indicating if all provided types are not unsigned (not to be confused with are_all_signed_v). </summary>
	/// <typeparam name="T">First type to check. Required.</typeparam>
	/// <typeparam name="Others">All types to check after the first. Optional.</typeparam>
	template<class T, class...Others>
	static constexpr bool are_all_not_unsigned_v = are_all_not_check<std::is_unsigned, T, Others...>::value;

	template<class T, class...Others>
	static constexpr bool is_any_floating_point_v = is_any_check<std::is_floating_point, T, Others...>::value;

	/// <summary> Underlying check used for all is_any_[comparison] values. </summary>
	/// <typeparam name="First_">First item to compare.</typeparam>
	/// <typeparam name="ToCompareAgainst_">Item to compare all additional passed items against within comparison_.</typeparam>
	/// <typeparam name="Others">All additional items to compare against after First_ until true or exhausted.</typeparam>
	template<template<class X__, class Y__> class comparison_, class ToCompareAgainst_, class First_, class...Others>
	struct is_any_comparison_true
	{
		static constexpr bool value = comparison_<ToCompareAgainst_, First_>::value ? true : is_any_comparison_true<comparison_, ToCompareAgainst_, Others...>::value;
	};
	/// <summary> Underlying check used for all is_any_[comparison] values. </summary>
	/// <typeparam name="First_">First item to compare.</typeparam>
	/// <typeparam name="ToCompareAgainst_">Item to compare all additional passed items against within comparison_.</typeparam>
	template<template<class X__, class Y__> class comparison_, class ToCompareAgainst_, class First_>
	struct is_any_comparison_true<comparison_, ToCompareAgainst_, First_>
	{
		static constexpr bool value = comparison_<ToCompareAgainst_, First_>::value;
	};

	template<template<class X__, class Y__> class comparison_, class ToCompareAgainst_, class First_, class...Others>
	struct are_all_comparisons_true
	{
		static constexpr bool value = comparison_<ToCompareAgainst_, First_>::value ? are_all_comparisons_true<comparison_, ToCompareAgainst_, Others...>::value : false;
	};

	template<template<class X__, class Y__> class comparison_, class ToCompareAgainst_, class First_>
	struct are_all_comparisons_true<comparison_, ToCompareAgainst_, First_>
	{
		static constexpr bool value = comparison_<ToCompareAgainst_, First_>::value;
	};

	/// <summary> Boolean indicating if any of the types passed types after ToFind_ are the same type as it. </summary>
	/// <typeparam name="ToFind_">Type to try to find.</typeparam>
	/// <typeparam name="First_">First type to compare to ToFind_.</typeparam>
	/// <typeparam name="Others">All types to compare after First_ until true or exhausted.</typeparam>
	template<class ToFind_, class First_, class...Others>
	static constexpr bool is_any_same_v = is_any_comparison_true<std::is_same, ToFind_, First_, Others...>::value;

	/// <summary> Determines if the passed type T is an instance of the template class ToFind_. Only works for templates which only take typeparams. </summary>
	template<class T, template<class...> class ToFind_>
	struct is_instance_of_typeparams_only
	{
		static constexpr bool value = false;
	};
	/// <summary> Determines if the passed type T is an instance of the template class ToFind_. Only works for templates which only take typeparams. </summary>
	template<class...T, template<class...> class ToFind_>
	struct is_instance_of_typeparams_only<ToFind_<T...>, ToFind_>
	{
		static constexpr bool value = true;
	};
	/// <summary> Boolean indicating if the passed type T is an instance of the template class ToFind_. </summary>
	template<class T, template<class...> class ToFind_>
	static constexpr bool is_instance_of_typeparams_only_v = is_instance_of_typeparams_only<T, ToFind_>::value;

	/// <summary> The number of bits contained within the passed type T. </summary>
	template<typename T>
	static constexpr std::size_t bits_in_type_v = sizeof(T) * CHAR_BIT;

	/// <summary> Finds the first floating point of all the passed types. If there are no floating point types, the type contained will be std::false_type. </summary>
	/// <typeparam name="First_">First type to check.</typeparam>
	/// <typeparam name="Others_">All other types to check if First_ is not a floating point.</typeparam>
	template<typename First_, typename...Others_>
	struct first_floating_point
	{
		using type = std::conditional_t<std::is_floating_point_v<First_>, First_, typename first_floating_point<Others_...>::type>;
	};
	template<typename First_>
	struct first_floating_point<First_>
	{
		using type = std::conditional_t<std::is_floating_point_v<First_>, First_, std::false_type>;
	};
	template<typename...Types_>
	using first_floating_point_t = typename first_floating_point<Types_...>::type;
}

#endif
