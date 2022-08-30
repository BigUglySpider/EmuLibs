#ifndef EMU_CORE_TMP_HELPERS_TYPE_COMPARATORS_H_INC_
#define EMU_CORE_TMP_HELPERS_TYPE_COMPARATORS_H_INC_ 1

#include <tuple>
#include <type_traits>
#include "TypeConvertors.h"
#include "OperatorChecks.h"
#include "Values.h"

namespace EmuCore::TMP
{
	template<typename Out_, typename In_>
	struct is_compatible
	{
		static constexpr bool is_constructible = std::is_constructible_v<Out_, In_>;
		static constexpr bool is_convertible = std::is_convertible_v<In_, Out_>;
		static constexpr bool is_assignable = std::is_assignable_v<Out_, In_>;
		static constexpr bool is_static_castable = EmuCore::TMP::is_static_castable_v<In_, Out_>;

		static constexpr bool value = is_constructible || is_convertible || is_assignable || is_static_castable;
	};
	template<typename Out_, typename In_>
	static constexpr bool is_compatible_v = is_compatible<Out_, In_>::value;

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
	template<class T_, template<class...> class ToFind_>
	struct is_instance_of_typeparams_only
	{
		static constexpr bool value = std::conditional_t
		<
			std::is_same_v<T_, EmuCore::TMP::remove_ref_cv_t<T_>>,
			std::false_type,
			is_instance_of_typeparams_only<EmuCore::TMP::remove_ref_cv_t<T_>, ToFind_>
		>::value;
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

	template<class T_>
	using is_tuple = is_instance_of_typeparams_only<T_, std::tuple>;
	template<class T_>
	static constexpr bool is_tuple_v = is_instance_of_typeparams_only_v<T_, std::tuple>;

	/// <summary> The number of bits contained within the passed type T. </summary>
	template<typename T>
	static constexpr std::size_t bits_in_type_v = sizeof(T) * CHAR_BIT;

	/// <summary> Finds the first floating point of all the passed types. If there are no floating point types, the type contained will be void. </summary>
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
		using type = std::conditional_t<std::is_floating_point_v<First_>, First_, void>;
	};
	template<typename...Types_>
	using first_floating_point_t = typename first_floating_point<Types_...>::type;

	template<typename Lhs_, typename Rhs_>
	struct larger_float
	{
	private:
		template<typename LhsFloat_, typename RhsFloat_>
		struct largest_of_guaranteed_floating_points
		{
			using type = std::conditional_t
			<
				(sizeof(LhsFloat_) == sizeof(RhsFloat_)),
				std::conditional_t
				<
					EmuCore::TMP::is_any_comparison_true<std::is_same, long double, LhsFloat_, RhsFloat_>::value,
					long double,
					Lhs_
				>,
				std::conditional_t
				<
					(sizeof(LhsFloat_) > sizeof(RhsFloat_)),
					LhsFloat_,
					RhsFloat_
				>
			>;
		};
	public:
		using type = std::conditional_t
		<
			EmuCore::TMP::is_any_floating_point_v<Lhs_, Rhs_>,
			std::conditional_t
			<
				EmuCore::TMP::are_all_check<std::is_floating_point, Lhs_, Rhs_>::value,
				typename largest_of_guaranteed_floating_points<Lhs_, Rhs_>::type,
				typename EmuCore::TMP::first_floating_point<Lhs_, Rhs_>::type
			>,
			void
		>;
	};
	/// <summary> Determines the largest floating point of the passed params. If no floating point type is passed, the determined type will be float. </summary>
	template<typename First_, typename...Others_>
	struct largest_floating_point
	{
	private:
		template<typename Highest_, typename First__, typename...Others__>
		struct find_largest_floating_point
		{
			using type = typename find_largest_floating_point
			<
				typename EmuCore::TMP::larger_float<Highest_, First__>::type,
				Others__...
			>::type;
		};
		template<typename Highest_, typename First__>
		struct find_largest_floating_point<Highest_, First__>
		{
			using type = std::conditional_t
			<
				std::is_floating_point_v<First__>,
				std::conditional_t
				<
					(sizeof(First__) > sizeof(Highest_)),
					First__,
					Highest_
				>,
				Highest_
			>;
		};
	public:
		using type = typename find_largest_floating_point<float, First_, Others_...>::type;
	};
	template<typename First_, typename...Others_>
	using largest_floating_point_t = typename largest_floating_point<First_, Others_...>::type;

	template<typename T_>
	struct is_reference_wrapper
	{
		static constexpr bool value = false;
	};
	template<typename T_>
	struct is_reference_wrapper<std::reference_wrapper<T_>>
	{
		static constexpr bool value = true;
	};

	template<class A_, class B_>
	struct is_two_way_static_castable
	{
		static constexpr bool value = EmuCore::TMP::is_static_castable_v<A_, B_> && EmuCore::TMP::is_static_castable_v<B_, A_>;
	};
	template<class A_, class B_>
	constexpr bool is_two_way_static_castable_v = is_two_way_static_castable<A_, B_>::value;

	/// <summary> Type used to encapsualate a void type. Not to be confused with std::void_t. </summary>
	struct void_type
	{
		using type = void;
	};

	/// <summary> Provides the constant type T_ if the provided Condition_ is true, otherwise provides T_ as it is passed. </summary>
	/// <typeparam name="T_"></typeparam>
	template<bool Condition_, typename T_>
	struct conditional_const
	{
		using type = std::conditional_t
		<
			Condition_,
			std::conditional_t
			<
				std::is_reference_v<T_>,
				std::add_const_t<std::remove_reference_t<T_>>&,
				std::add_const_t<T_>
			>,
			T_
		>;
	};
	template<bool Condition_, typename T_>
	using conditional_const_t = typename conditional_const<Condition_, T_>::type;

	template<typename ToConvertTo_, typename FirstToConvertFrom_, typename...OthersToConvertFrom_>
	struct are_all_static_castable
	{
		static constexpr bool value = EmuCore::TMP::is_static_castable_v<FirstToConvertFrom_, ToConvertTo_> ? are_all_static_castable<ToConvertTo_, OthersToConvertFrom_...>::value : false;
	};
	template<typename ToConvertTo_, typename FirstToConvertFrom_>
	struct are_all_static_castable<ToConvertTo_, FirstToConvertFrom_>
	{
		static constexpr bool value = EmuCore::TMP::is_static_castable_v<FirstToConvertFrom_, ToConvertTo_>;
	};
	template<typename ToConvertTo_, typename...ToConvertFrom_>
	static constexpr bool are_all_static_castable_v = are_all_static_castable<ToConvertTo_, ToConvertFrom_...>::value;

	template<class T_, typename = void>
	struct has_static_get : std::false_type
	{
	};
	template<class T_>
	struct has_static_get<T_, std::void_t<decltype(EmuCore::TMP::remove_ref_cv_t<T_>::get())>> : std::true_type
	{
	};

	template<class T_, typename = void>
	struct has_static_value : std::false_type
	{
	};
	template<class T_>
	struct has_static_value<T_, std::void_t<decltype(T_::value)>> : std::true_type
	{
	};

	template<template<class...> class Template_, class...TypeArgs_>
	struct valid_template_args
	{
	private:
		template<template<class...> class T_>
		static constexpr bool _get(T_<TypeArgs_...>* p_dummy_)
		{
			return true;
		};
		template<template<class...> class T_>
		static constexpr bool _get(...)
		{
			return false;
		}

	public:
		static constexpr bool value = _get<Template_>(nullptr);
	};
	template<template<class...> class Template_, class...TypeArgs_>
	static constexpr bool valid_template_args_v = valid_template_args<Template_, TypeArgs_...>::value;

	/// <summary>
	/// <para> Base component for performing a semi-recursive type check with an arbitrary number of type arguments. </para>
	/// <para> Checks will ignore reference and constant qualification, and any type T will be treated as `EmuCore::TMP::remove_ref_cv&lt;T_&gt;::type`. </para>
	/// <para> Pointers are still applied and will not be removed. </para>
	/// <para> Where all args are their unqualified state already, `value` will be `DefaultStaticValueType_::value`. </para>
	/// <para> Where any arg is ref/cv qualified, `value` will be `Template_&lt;EmuCore::TMP::remove_ref_cv&lt;Args_...&gt;::type...&gt;::value` </para>
	/// <para>
	///		This is intended as a base-class for type checks which recursively call back to themselves and have a trivial, non-conditional default value 
	///		(e.g. a default template whose default value is always `false`), but where ref/cv qualification is wanted to be ignored.
	/// </para>
	/// <para>For a recursive check on any arbitrary template without a default value, use `type_check_ignore_ref_cv`.</para>
	/// </summary>
	template<template<class...TemplateArgs_> class Template_, class DefaultStaticValueType_, class...Args_>
	struct type_check_ignore_ref_cv_base
	{
	private:
		static constexpr inline decltype(auto) _get()
		{
			if constexpr ((... && std::is_same_v<Args_, typename EmuCore::TMP::remove_ref_cv<Args_>::type>))
			{
				if constexpr (has_static_value<DefaultStaticValueType_>::value)
				{
					return DefaultStaticValueType_::value;
				}
				else
				{
					static_assert
					(
						EmuCore::TMP::get_false<DefaultStaticValueType_>(),
						"Attempted to create a semi-recursive, ref-cv-ignoring type check via `EmuCore::TMP::type_check_ignore_ref_cv_base`, but the provided `DefaultStaticValueType_` does not have a static `value` member."
					);
					return "ERROR: Bad DefaultStaticValueType_";
				}
			}
			else
			{
				if constexpr (valid_template_args_v<Template_, typename EmuCore::TMP::remove_ref_cv<Args_>::type...>)
				{
					using _finalised_template_for_value = Template_<typename EmuCore::TMP::remove_ref_cv<Args_>::type... >;
					if constexpr (has_static_value<_finalised_template_for_value>::value)
					{
						return _finalised_template_for_value::value;
					}
					else
					{
						static_assert
						(
							EmuCore::TMP::get_false<_finalised_template_for_value>(),
							"Attempted to create a semi-recursive, ref-cv-ignoring type check via `EmuCore::TMP::type_check_ignore_ref_cv_base`, but the instantiated template with ref/cv removed type arguments does not have a static `value`."
						);
						return "ERROR: Template instance from ref/cv-removed Args_ has no static `value`";
					} 
				}
				else
				{
					static_assert
					(
						EmuCore::TMP::get_false<Args_...>(),
						"Attempted to create a semi-recursive, ref-cv-ignoring type check via `EmuCore::TMP::type_check_ignore_ref_cv_base`, but the provided `Args_` with ref/cv qualification removed are not valid for instantiating the provided `Template_`."
					);
					return "ERROR: Bad Args_";
				}
			}

			if constexpr (valid_template_args_v<Template_, Args_...>)
			{
				if constexpr (has_static_value<DefaultStaticValueType_>::value)
				{
					return std::conditional_t
					<
						(... && std::is_same_v<Args_, typename EmuCore::TMP::remove_ref_cv<Args_>::type>),
						DefaultStaticValueType_,
						Template_<typename EmuCore::TMP::remove_ref_cv<Args_>::type...>
					>::value;
				}
			}
		}

	public:
		static constexpr auto value = _get();
	};

	/// <summary>
	/// <para> Template for performing a semi-recursive type check with an arbitrary number of type arguments. </para>
	/// <para> Checks will ignore reference and constant qualification, and any type T will be treated as `EmuCore::TMP::remove_ref_cv&lt;T_&gt;::type`. </para>
	/// <para> Pointers are still applied and will not be removed. </para>
	/// <para> Where all args are their unqualified state already, `value` will be `Template_&lt;Args_...&gt;::value`. </para>
	/// <para> Where any arg is ref/cv qualified, `value` will be `Template_&lt;EmuCore::TMP::remove_ref_cv&lt;Args_...&gt;::type...&gt;::value` </para>
	/// <para>For a recursive check with a default value if already unqualified, use `type_check_ignore_ref_cv_base`.</para>
	/// </summary>
	template<template<class...TemplateArgs_> class Template_, class...Args_>
	struct type_check_ignore_ref_cv
	{
	private:
		static constexpr inline decltype(auto) _get()
		{
			if constexpr (valid_template_args_v<Template_, typename EmuCore::TMP::remove_ref_cv<Args_>::type...>)
			{
				using _finalised_template_for_value = Template_<typename EmuCore::TMP::remove_ref_cv<Args_>::type...>;
				if constexpr (has_static_value<_finalised_template_for_value>::value)
				{
					return _finalised_template_for_value::value;
				}
				else
				{
					static_assert
					(
						EmuCore::TMP::get_false<_finalised_template_for_value>(),
						"Attempted to create a semi-recursive, ref-cv-ignoring type check via `EmuCore::TMP::type_check_ignore_ref_cv`, but the instantiated template with ref/cv removed type arguments does not have a static `value`."
					);
					return "ERROR: Template instance from ref/cv-removed Args_ has no static `value`";
				} 
			}
			else
			{
				static_assert
				(
					EmuCore::TMP::get_false<Args_...>(),
					"Attempted to create a semi-recursive, ref-cv-ignoring type check via `EmuCore::TMP::type_check_ignore_ref_cv`, but the provided `Args_` are not valid for instantiating the provided `Template_` when its ref/cv qualifiers are removed."
				);
				return "ERROR: Bad Args_";
			}
		}

	public:
		static constexpr auto value = _get();
	};

	template<class T_>
	struct is_integer_sequence
	{
		static constexpr bool value = false;
	};
	template<class T_, T_...Vals_>
	struct is_integer_sequence<std::integer_sequence<T_, Vals_...>>
	{
		static constexpr bool value = true;
	};
	template<class T_>
	static constexpr bool is_integer_sequence_v = is_integer_sequence<T_>::value;

	template<class T_>
	struct is_index_sequence
	{
		static constexpr bool value = false;
	};
	template<std::size_t...Vals_>
	struct is_index_sequence<std::index_sequence<Vals_...>>
	{
		static constexpr bool value = true;
	};
	template<class T_>
	static constexpr bool is_index_sequence_v = is_index_sequence<T_>::value;
	
	/// <summary>
	/// <para> Type to check if the passed type `T_` is a std::array instance. </para>
	/// <para>
	///		May optionally check for an array containing a specific type `Contains_`. 
	///		If `Contains_` is `void`, the result `value` will be `true` for any `std::array` instance regardless of contained type.
	/// </para>
	/// </summary>
	template<class T_, typename Contains_ = void>
	struct is_std_array : public EmuCore::TMP::type_check_ignore_ref_cv_base<is_std_array, std::false_type, T_, Contains_>
	{
	};

	template<std::size_t Size_, typename T_, typename Contains_>
	struct is_std_array<std::array<T_, Size_>, Contains_>
	{
		static constexpr bool value = std::conditional_t
		<
			std::is_void_v<Contains_>,
			std::true_type,
			std::is_same<T_, Contains_>
		>::value;
	};

	template<class T_, typename Contains_ = void>
	static constexpr bool is_std_array_v = is_std_array<T_, Contains_>::value;
}

#endif
