#ifndef EMU_CORE_TMP_HELPERS_TYPE_COMPARATORS_H_INC_
#define EMU_CORE_TMP_HELPERS_TYPE_COMPARATORS_H_INC_

#include <type_traits>

namespace EmuCore::TMPHelpers
{
	/// <summary> Finds the largest byte-sized type of the passed options. For matching type sizes, the leftmost type receives priority. </summary>
	/// <typeparam name="X_">First type to compare. Required.</typeparam>
	/// <typeparam name="Y_">Second type to compare. Required.</typeparam>
	/// <typeparam name="Others_">All additional types to compare. Optional.</typeparam>
	template<typename X_, typename Y_, typename...Others_>
	struct highest_byte_size
	{
		using type = typename highest_byte_size<X_, typename highest_byte_size<Y_, Others_...>::type>::type;
	};
	/// <summary> Finds the largest byte-sized type of the passed options. For matching type sizes, X_ receives priority. </summary>
	/// <typeparam name="X_">First type to compare.</typeparam>
	/// <typeparam name="Y_">Second type to compare.</typeparam>
	template<typename X_, typename Y_>
	struct highest_byte_size<X_, Y_>
	{
		using type = std::conditional_t<(sizeof(X_) >= sizeof(Y_)), X_, Y_>;
	};
	/// <summary> The largest byte-sized type of the passed options. For matching type sizes, the leftmost type receives priority. </summary>
	/// <typeparam name="X_">First type to compare. Required.</typeparam>
	/// <typeparam name="Y_">Second type to compare. Required.</typeparam>
	/// <typeparam name="Others_">All additional types to compare. Optional.</typeparam>
	template<typename X_, typename Y_, typename...Others_>
	using highest_byte_size_t = typename highest_byte_size<X_, Y_, Others_...>::type;

	/// <summary> Finds the smallest byte-sized type of the passed options. For matching type sizes, the leftmost type receives priority. </summary>
	/// <typeparam name="X_">First type to compare. Required.</typeparam>
	/// <typeparam name="Y_">Second type to compare. Required.</typeparam>
	/// <typeparam name="Others_">All additional types to compare. Optional.</typeparam>
	template<typename X_, typename Y_, typename...Others_>
	struct lowest_byte_size
	{
		using type = typename lowest_byte_size<X_, typename lowest_byte_size<Y_, Others_...>::type>::type;
	};
	/// <summary> Finds the smallest byte-sized type of the passed options. For matching type sizes, X_ receives priority. </summary>
	/// <typeparam name="X_">First type to compare.</typeparam>
	/// <typeparam name="Y_">Second type to compare.</typeparam>
	template<typename X_, typename Y_>
	struct lowest_byte_size<X_, Y_>
	{
		using type = std::conditional_t<(sizeof(X_) <= sizeof(Y_)), X_, Y_>;
	};
	/// <summary> The smallest byte-sized type of the passed options. For matching type sizes, the leftmost type receives priority. </summary>
	/// <typeparam name="X_">First type to compare. Required.</typeparam>
	/// <typeparam name="Y_">Second type to compare. Required.</typeparam>
	/// <typeparam name="Others_">All additional types to compare. Optional.</typeparam>
	template<typename X_, typename Y_, typename...Others_>
	using lowest_byte_size_t = typename lowest_byte_size<X_, Y_, Others_...>::type;

	/// <summary> Underlying check used for all is_any_ values. Performs the passed check_ with each provided parameter until one is true or they are exhausted. </summary>
	/// <typeparam name="First">The first type to perform the check on. Required.</typeparam>
	/// <typeparam name="Others">All additional types to perform the check on. Optional.</typeparam>
	template<template<typename T_> typename check_, typename First, typename...Others>
	struct is_any_check
	{
		static constexpr bool value = check_<First>::value ? true : is_any_check<check_, Others...>::value;
	};
	/// <summary> Underlying check used for all is_any_ values. Contained value is set to the value of the passed check_ with the provided First parameter. </summary>
	/// <typeparam name="First">Type to perform the check on.</typeparam>
	template<template<typename T_> typename check_, typename First>
	struct is_any_check<check_, First>
	{
		static constexpr bool value = check_<First>::value;
	};
	/// <summary> Inverted variant of is_any_check, which in turn is the underlying check for all is_any_not_ values. </summary>
	/// <typeparam name="First">The first type to perform the check on. Required.</typeparam>
	/// <typeparam name="Others">All additional types to perform the check on. Optional.</typeparam>
	template<template<typename T_> typename check_, typename First, typename...Others>
	struct is_any_not_check
	{
		static constexpr bool value = !check_<First>::value ? true : is_any_not_check<check_, Others...>::value;
	};
	/// <summary> Inverted variant of is_any_check, which in turn is the underlying check for all is_any_not_ values. </summary>
	/// <typeparam name="First">Type to perform the check on.</typeparam>
	template<template<typename T_> typename check_, typename First>
	struct is_any_not_check<check_, First>
	{
		static constexpr bool value = !check_<First>::value;
	};

	/// <summary> Underlying check used for all are_all_ values. Performs the passed check_ with each provided parameter until one is false or they are exhausted. </summary>
	/// <typeparam name="First">The first type to perform the check on. Required.</typeparam>
	/// <typeparam name="Others">All additional types to perform the check on. Optional.</typeparam>
	template<template<typename T_> typename check_, typename First, typename...Others>
	struct are_all_check
	{
		static constexpr bool value = check_<First>::value ? are_all_check<check_, Others...>::value : false;
	};
	/// <summary> Underlying check used for all are_all_ values. Contained value is set to the value of the passed check_ with the provided First parameter. </summary>
	/// <typeparam name="First">Type to perform the check on.</typeparam>
	template<template<typename T_> typename check_, typename First>
	struct are_all_check<check_, First>
	{
		static constexpr bool value = check_<First>::value;
	};
	/// <summary> Inverted variant of are_all_check, which in turn is the underlying check for all are_all_not_ values. </summary>
	/// <typeparam name="First">The first type to perform the check on. Required.</typeparam>
	/// <typeparam name="Others">All additional types to perform the check on. Optional.</typeparam>
	template<template<typename T_> typename check_, typename First, typename...Others>
	struct are_all_not_check
	{
		static constexpr bool value = !check_<First>::value ? is_any_not_check<check_, Others...>::value : false;
	};
	/// <summary> Inverted variant of are_all_check, which in turn is the underlying check for all are_all_not_ values. </summary>
	/// <typeparam name="First">Type to perform the check on.</typeparam>
	template<template<typename T_> typename check_, typename First>
	struct are_all_not_check<check_, First>
	{
		static constexpr bool value = !check_<First>::value;
	};

	/// <summary> Boolean indicating if any of the provided types are signed. </summary>
	/// <typeparam name="T">First type to check. Required.</typeparam>
	/// <typeparam name="Others">All types to check after the first. Optional.</typeparam>
	template<typename T, typename...Others>
	static constexpr bool is_any_signed_v = is_any_check<std::is_signed, T, Others...>::value;
	/// <summary> Boolean indicating if all provided types are signed. </summary>
	/// <typeparam name="T">First type to check. Required.</typeparam>
	/// <typeparam name="Others">All types to check after the first. Optional.</typeparam>
	template<typename T, typename...Others>
	static constexpr bool are_all_signed_v = are_all_check<std::is_signed, T, Others...>::value;
	/// <summary> Boolean indicating if any of the provided types are not signed (not to be confused with is_any_unsigned_v). </summary>
	/// <typeparam name="T">First type to check. Required.</typeparam>
	/// <typeparam name="Others">All types to check after the first. Optional.</typeparam>
	template<typename T, typename...Others>
	static constexpr bool is_any_not_signed_v = is_any_not_check<std::is_signed, T, Others...>::value;
	/// <summary> Boolean indicating if all provided types are not signed (not to be confused with are_all_unsigned_v). </summary>
	/// <typeparam name="T">First type to check. Required.</typeparam>
	/// <typeparam name="Others">All types to check after the first. Optional.</typeparam>
	template<typename T, typename...Others>
	static constexpr bool are_all_not_signed_v = are_all_not_check<std::is_signed, T, Others...>::value;

	/// <summary> Boolean indicating if any of the provided types are unsigned. </summary>
	/// <typeparam name="T">First type to check. Required.</typeparam>
	/// <typeparam name="Others">All types to check after the first. Optional.</typeparam>
	template<typename T, typename...Others>
	static constexpr bool is_any_unsigned_v = is_any_check<std::is_unsigned, T, Others...>::value;
	/// <summary> Boolean indicating if all provided types are unsigned. </summary>
	/// <typeparam name="T">First type to check. Required.</typeparam>
	/// <typeparam name="Others">All types to check after the first. Optional.</typeparam>
	template<typename T, typename...Others>
	static constexpr bool are_all_unsigned_v = are_all_check<std::is_unsigned, T, Others...>::value;
	/// <summary> Boolean indicating if any of the provided types are not unsigned (not to be confused with is_any_signed_v). </summary>
	/// <typeparam name="T">First type to check. Required.</typeparam>
	/// <typeparam name="Others">All types to check after the first. Optional.</typeparam>
	template<typename T, typename...Others>
	static constexpr bool is_any_not_unsigned_v = is_any_not_check<std::is_unsigned, T, Others...>::value;
	/// <summary> Boolean indicating if all provided types are not unsigned (not to be confused with are_all_signed_v). </summary>
	/// <typeparam name="T">First type to check. Required.</typeparam>
	/// <typeparam name="Others">All types to check after the first. Optional.</typeparam>
	template<typename T, typename...Others>
	static constexpr bool are_all_not_unsigned_v = are_all_not_check<std::is_unsigned, T, Others...>::value;

	template<typename T, typename...Others>
	static constexpr bool is_any_floating_point_v = is_any_check<std::is_floating_point, T, Others...>::value;

	/// <summary> Underlying check used for all is_any_[comparison] values. </summary>
	/// <typeparam name="First_">First item to compare.</typeparam>
	/// <typeparam name="ToCompareAgainst_">Item to compare all additional passed items against within comparison_.</typeparam>
	/// <typeparam name="Others">All additional items to compare against after First_ until true or exhausted.</typeparam>
	template<template<typename X__, typename Y__> typename comparison_, typename ToCompareAgainst_, typename First_, typename...Others>
	struct is_any_comparison_true
	{
		static constexpr bool value = comparison_<ToCompareAgainst_, First_>::value ? true : is_any_comparison_true<comparison_, ToCompareAgainst_, Others...>::value;
	};
	/// <summary> Underlying check used for all is_any_[comparison] values. </summary>
	/// <typeparam name="First_">First item to compare.</typeparam>
	/// <typeparam name="ToCompareAgainst_">Item to compare all additional passed items against within comparison_.</typeparam>
	template<template<typename X__, typename Y__> typename comparison_, typename ToCompareAgainst_, typename First_>
	struct is_any_comparison_true<comparison_, ToCompareAgainst_, First_>
	{
		static constexpr bool value = comparison_<ToCompareAgainst_, First_>::value;
	};

	/// <summary> Boolean indicating if any of the types passed types after ToFind_ are the same type as it. </summary>
	/// <typeparam name="ToFind_">Type to try to find.</typeparam>
	/// <typeparam name="First_">First type to compare to ToFind_.</typeparam>
	/// <typeparam name="Others">All types to compare after First_ until true or exhausted.</typeparam>
	template<typename ToFind_, typename First_, typename...Others>
	static constexpr bool is_any_same_v = is_any_comparison_true<std::is_same, ToFind_, First_, Others...>::value;
}

#endif
