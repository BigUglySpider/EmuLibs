#ifndef EMU_CORE_VARIADIC_HELPERS_H_INC_
#define EMU_CORE_VARIADIC_HELPERS_H_INC_ 1

#include "TypeComparators.h"
#include "../Functors/Comparators.h"
#include <utility>

namespace EmuCore::TMP
{
#pragma region TEMPLATE_HELPERS
	/// <summary>
	/// <para> Helper to safely instantiate a Template_ from variadic Args_, cancelling instantiation if it is a failure. </para>
	/// <para> If instantiation fails, type will be void. Otherwise, it will be an instance of Template_ instantiated with the provided Args_. </para>
	/// <para> Static member value may also be used to determine success (true if successful, otherwise false). </para>
	/// </summary>
	/// <typeparam name="Args_">All type arguments to attempt to instantiate Template_ with.</typeparam>
	template<template<class...> class Template_, class...Args_>
	struct safe_template_instantiate
	{
	private:
		template<template<class...> class ToInstantiate_, bool IsValid_ = EmuCore::TMP::valid_template_args_v<ToInstantiate_, Args_...>>
		struct _instantiator
		{
			static constexpr bool value = false;
			using type = void;
		};
		template<template<class...> class ToInstantiate_>
		struct _instantiator<ToInstantiate_, true>
		{
			static constexpr bool value = true;
			using type = ToInstantiate_<Args_...>;
		};

		using _make_instance = _instantiator<Template_>;

	public:
		static constexpr bool value = _make_instance::value;
		using type = typename _make_instance::type;
	};

	/// <summary>
	/// <para> Helper to safely use std::invoke_result on a Func_ that may or may not be invocable with the provided Args_. </para>
	/// <para> Type will be void upon failure, but does not directly indicate failure. For such checks, use value, which will be true on success and false on failure. </para>
	/// </summary>
	/// <typeparam name="Args_">All types to invoke Func_ with.</typeparam>
	template<class Func_, class...Args_>
	struct safe_invoke_result
	{
	private:
		template<class ToInvoke_, bool IsInvocable_ = std::is_invocable_v<ToInvoke_, Args_...>>
		struct _checker
		{
			static constexpr bool value = false;
			using type = void;
		};
		template<class ToInvoke_>
		struct _checker<ToInvoke_, true>
		{
			static constexpr bool value = true;
			using type = std::invoke_result_t<ToInvoke_, Args_...>;
		};

		using _check = _checker<Func_>;

	public:
		static constexpr bool value = _check::value;
		using type = typename _check::type;
	};
#pragma endregion

#pragma region TYPE_EXTRACTORS
	/// <summary>
	/// <para> Aliases a type T_, and ignores the provided Discarded_ type. </para>
	/// <para> Primarily exists for producing a variadic sequence of the same type, with a count based on variadic types that are unused. </para>
	/// <para> Useful for forming generic EmuCore functors with fixed outputs (such as do_clamp&lt;void, void, void, float&gt;) in allowing situations. </para>
	/// </summary>
	template<class T_, class Discarded_>
	struct type_and_discard
	{
		using type = T_;
	};
	template<class T_, class Discarded_>
	using type_and_discard_t = typename type_and_discard<T_, Discarded_>::type;

	/// <summary>
	/// <para> Variant of type_and_discard which instead takes a non-type Discarded_ argument. </para>
	/// </summary>
	template<class T_, auto Discarded_>
	struct type_and_discard_val
	{
		using type = T_;
	};
	template<class T_, auto Discarded_>
	using type_and_discard_val_t = typename type_and_discard_val<T_, Discarded_>::type;

	/// <summary>
	/// <para> Extracts the first argument type of a selection of variadic Args_, aliasing it as the internal type. </para>
	/// <para> If 1 or more arguments are provided: type will be the first provided type. </para>
	/// <para> If 0 arguments are provided: type will be void. </para>
	/// </summary>
	template<class...Args_>
	struct first_variadic_arg
	{
		using type = void;
	};
	template<class First_, class...Others_>
	struct first_variadic_arg<First_, Others_...>
	{
		using type = First_;
	};
	template<class First_>
	struct first_variadic_arg<First_>
	{
		using type = First_;
	};
	template<>
	struct first_variadic_arg<>
	{
		using type = void;
	};
	template<class...Args_>
	using first_variadic_arg_t = typename first_variadic_arg<Args_...>::type;
#pragma endregion

#pragma region VARIADIC_BOOLS
	/// <summary> Type to easily produce the result of a logical AND with variadic template argument results, with a consistent `false` value with no arguments. </summary>
	template<bool...Bools_>
	struct variadic_and
	{
		static constexpr bool value = (... && Bools_);
	};

	template<bool First_>
	struct variadic_and<First_>
	{
		static constexpr bool value = First_;
	};
	template<>
	struct variadic_and<>
	{
		static constexpr bool value = false;
	};
	template<bool...Bools_>
	static constexpr bool variadic_and_v = variadic_and<Bools_...>::value;

	/// <summary> Type to easily produce the result of a logical OR with variadic template argument results, with a consistent `false` value with no arguments. </summary>
	template<bool...Bools_>
	struct variadic_or
	{
		static constexpr bool value = (... || Bools_);
	};
	template<bool First_>
	struct variadic_or<First_>
	{
		static constexpr bool value = First_;
	};
	template<>
	struct variadic_or<>
	{
		static constexpr bool value = false;
	};
	template<bool...Bools_>
	static constexpr bool variadic_or_v = variadic_or<Bools_...>::value;

	/// <summary> Type to easily produce the result of a logical XOR with variadic template argument results, with a consistent 'false' value with no arguments. </summary>
	template<bool...Bools_>
	struct variadic_xor
	{
		static constexpr bool value = (... ^ Bools_);
	};
	template<bool First_>
	struct variadic_xor<First_>
	{
		static constexpr bool value = First_;
	};
	template<>
	struct variadic_xor<>
	{
		static constexpr bool value = false;
	};
	template<bool...Bools_>
	static constexpr bool variadic_xor_v = variadic_xor<Bools_...>::value;
#pragma endregion

#pragma region EXTRA_INDEX_SEQUENCES
	/// <summary> Type to create an Index_ sequence of the specified size similar to std::make_index_sequence, but starting at the provided Offset_ instead of 0. </summary>
	template<typename T_, T_ Offset_, T_ Size_>
	struct offset_integer_sequence_maker
	{
	private:
		template<std::size_t OffsetVal_, typename BaseSequence_, typename = void>
		struct _apply_offset
		{
			using type = BaseSequence_;
		};
		template<std::size_t OffsetVal_, T_...Vals_>
		struct _apply_offset<OffsetVal_, std::integer_sequence<T_, Vals_...>, std::enable_if_t<OffsetVal_ != 0>>
		{
			using type = std::integer_sequence<T_, (OffsetVal_ + Vals_)...>;
		};


	public:
		using type = typename _apply_offset<Offset_, std::make_integer_sequence<T_, Size_>>::type;
	};

	template<typename T_, T_ Offset_, T_ Size_>
	using make_offset_integer_sequence = typename offset_integer_sequence_maker<T_, Offset_, Size_>::type;

	template<std::size_t Offset_, std::size_t Size_>
	using make_offset_index_sequence = typename offset_integer_sequence_maker<std::size_t, Offset_, Size_>::type;

	/// <summary>
	///	<para> Type used to splice two integer sequences into a single one. Indices in the left-hand sequence will all appear first, then those in the right-hand sequence. </para>
	/// <para> If an argument is not a std::intger_sequence, it will be interpreted as an empty std::integer_sequence of the correct type. </para>
	/// <para> If both arguments are not a std::intger_sequence, type will be an empty std::integer_sequence of chars. </para>
	/// <para> If both arguments are std::integer_sequences (as they should be), the value_type of the left-hand integer sequence will be used. </para>
	/// </summary>
	template<class LhsIntegerSequence_, class RhsIntegerSequence_>
	struct splice_integer_sequences
	{
	private:
		template<class Lhs_, class Rhs_>
		struct _builder
		{
			using type = std::integer_sequence<char>;
		};

		template<class LhsT_, std::size_t...LhsIndices_, class Rhs_>
		struct _builder<std::integer_sequence<LhsT_, LhsIndices_...>, Rhs_>
		{
			using type = std::integer_sequence<LhsT_, LhsIndices_...>;
		};

		template<class Lhs_, class RhsT_, std::size_t...RhsIndices_>
		struct _builder<Lhs_, std::integer_sequence<RhsT_, RhsIndices_...>>
		{
			using type = std::integer_sequence<RhsT_, RhsIndices_...>;
		};

	public:
		using type = typename _builder<LhsIntegerSequence_, RhsIntegerSequence_>::type;
	};
	template<typename LhsT_, std::size_t...LhsIndices_, typename RhsT_, std::size_t...RhsIndices_>
	struct splice_integer_sequences<std::integer_sequence<LhsT_, LhsIndices_...>, std::integer_sequence<RhsT_, RhsIndices_...>>
	{
		using type = std::integer_sequence<LhsT_, LhsIndices_..., static_cast<LhsT_>(RhsIndices_)...>;
	};
	template<class Lhs_, class Rhs_>
	using splice_index_sequences_t = typename splice_integer_sequences<Lhs_, Rhs_>::type;

	/// <summary>
	/// <para> Type extension of splice_index_sequences which may be used to splice a variadic number of integer sequences. </para>
	/// <para> If an argument is not a std::integer_sequence, it will be interpreted as an empty std::integer_sequence of chars. </para>
	/// </summary>
	template<class...IntegerSequences_>
	struct variadic_splice_integer_sequences
	{
		using type = std::integer_sequence<char>;
	};
	template<typename T_, T_...Indices_>
	struct variadic_splice_integer_sequences<std::integer_sequence<T_, Indices_...>>
	{
		using type = std::index_sequence<Indices_...>;
	};
	template<class LhsIndexSequence_, class RhsIndexSequence_>
	struct variadic_splice_integer_sequences<LhsIndexSequence_, RhsIndexSequence_>
	{
		using type = typename splice_integer_sequences<LhsIndexSequence_, RhsIndexSequence_>::type;
	};
	template<class FirstIndexSequence_, class SecondIndexSequence_, class...RemainingIndexSequences_>
	struct variadic_splice_integer_sequences<FirstIndexSequence_, SecondIndexSequence_, RemainingIndexSequences_...>
	{
		using type = typename variadic_splice_integer_sequences
		<
			typename splice_integer_sequences<FirstIndexSequence_, SecondIndexSequence_>::type,
			RemainingIndexSequences_...
		>::type;
	};
	template<class...IntegerSequences_>
	using variadic_splice_integer_sequences_t = typename variadic_splice_integer_sequences<IntegerSequences_...>::type;

	/// <summary> Type used to form an index sequence containing only the specified Index_ the specified Count_ of times. </summary>
	template<typename T_, T_ Index_, std::size_t Count_>
	struct duplicated_integer_sequence
	{
		using type = typename splice_integer_sequences
		<
			std::index_sequence<Index_>,
			typename duplicated_integer_sequence<T_, Index_, Count_ - 1>::type
		>::type;
	};
	template<typename T_, T_ Index_>
	struct duplicated_integer_sequence<T_, Index_, 0>
	{
		using type = std::index_sequence<>;
	};
	template<typename T_, T_ Index_>
	struct duplicated_integer_sequence<T_, Index_, 1>
	{
		using type = std::integer_sequence<T_, Index_>;
	};
	template<std::size_t Index_, std::size_t Count_>
	using make_duplicated_index_sequence = typename duplicated_integer_sequence<std::size_t, Index_, Count_>::type;

	/// <summary> Type used to form an integer sequence which consists of the provided sequence looped the specified number of times. </summary>
	template<class IntegerSequence_, std::size_t LoopCount_>
	struct looped_integer_sequence
	{
		using type = std::integer_sequence<char>;
	};
	template<typename T_, T_...Indices_, std::size_t LoopCount_>
	struct looped_integer_sequence<std::integer_sequence<T_, Indices_...>, LoopCount_>
	{
	private:
		using _base_sequence = std::integer_sequence<T_, Indices_...>;

		template<class CurrentSequence_, std::size_t RemainingLoops_>
		struct _sequence_builder
		{
			using type = typename _sequence_builder
			<
				typename splice_integer_sequences<CurrentSequence_, _base_sequence>::type,
				RemainingLoops_ - 1
			>::type;
		};
		template<class CurrentSequence_>
		struct _sequence_builder<CurrentSequence_, 0>
		{
			using type = CurrentSequence_;
		};

	public:
		using type = typename _sequence_builder<_base_sequence, LoopCount_>::type;
	};
	template<class IntegerSequence_, std::size_t LoopCount_>
	using make_looped_integer_sequence = typename looped_integer_sequence<IntegerSequence_, LoopCount_>::type;

	/// <summary>
	/// <para> Helper type to perform a comparison of all constants to determine the last to compare true. </para>
	/// <para> The provided CmpTemplate_ will be instantiated with a single T_ argument, and used to perform each comparison. </para>
	/// <para> The instantiated template must be default-constructible, and constexpr invocable with two values of type T_ as arguments. </para>
	/// <para> Comparisons are performed purely with the provided values. </para>
	/// <para> If 0 Vals_ are provided: value will be a default-constructed T_. </para>
	/// <para> If 1 Val_ is provided: value will the single passed Val_. </para>
	/// <para>
	///		If multiple Vals_ are provided: current_value will start as the first passed Val_.
	///		When a comparison in the form cmp(Val_[x], current_value) returns true, current_val will be updated to Val_[x]. 
	///		This will repeat until the final Val_ has been compared, and value will be set to the final state of current_val.
	/// </para>
	/// </summary>
	template<template<class...> class CmpTemplate_, typename T_, T_...Vals_>
	struct last_constant_to_compare_true
	{
	private:
		using _cmp_maker = EmuCore::TMP::safe_template_instantiate<CmpTemplate_, T_>;
		using _cmp = typename _cmp_maker::type;
		static constexpr bool _cmp_invocable = std::is_invocable_v<_cmp, T_, T_>;
		static constexpr bool _cmp_default_constructible = std::is_default_constructible_v<_cmp>;
		static_assert
		(
			_cmp_maker::value,
			"Attempted to find the last constant to compare true to a comparison template's invocation via last_constant_to_compare_true, but the provided CmpTemplate_ cannot be instantiated as CmpTemplate_<T_>."
		);

		template<bool AnyTrue_, T_...All_>
		struct _find_last_true
		{
			// This is a dummy func and should never be called, but is here for consistent compilation
			static constexpr inline decltype(std::declval<T_>()) get()
			{
				return std::declval<T_>();
			}
		};

		template<bool AnyTrue_, T_ LastTrue_, T_ Current_, T_...Remaining_>
		struct _find_last_true<AnyTrue_, LastTrue_, Current_, Remaining_...>
		{
			[[nodiscard]] static constexpr inline T_ get()
			{
				if constexpr (_cmp_invocable)
				{
					if constexpr (_cmp_default_constructible)
					{
						if constexpr (_cmp()(Current_, LastTrue_))
						{
							return _find_last_true<true, Current_, Remaining_...>::get();
						}
						else
						{
							return _find_last_true<AnyTrue_, LastTrue_, Remaining_...>::get();
						}
					}
					else
					{
						static_assert
						(
							EmuCore::TMP::get_false<T_>(),
							"Attempted to find the last constant to comapre true to a comparison template's invocation via last_constant_to_compare_true, but the instantiated comparison type cannot be default-constructed."
						);
					}
				}
				else
				{
					static_assert
					(
						EmuCore::TMP::get_false<T_>(),
						"Attempted to find the last constant to compare true to a comparison template's invocation via last_constant_to_compare_true, but the instantiated comparison cannot be invoked with two values of type T_."
					);
				}
			}
		};

		template<bool AnyTrue_, T_ LastTrue_, T_ Current_>
		struct _find_last_true<AnyTrue_, LastTrue_, Current_>
		{
			[[nodiscard]] static constexpr inline T_ get()
			{
				if constexpr (_cmp_invocable)
				{
					if constexpr (_cmp_default_constructible)
					{
						if constexpr (_cmp()(Current_, LastTrue_))
						{
							return Current_;
						}
						else
						{
							return LastTrue_;
						}
					}
					else
					{
						static_assert
						(
							EmuCore::TMP::get_false<T_>(),
							"Attempted to find the last constant to comapre true to a comparison template's invocation via last_constant_to_compare_true, but the instantiated comparison type cannot be default-constructed."
						);
					}
				}
				else
				{
					static_assert
					(
						EmuCore::TMP::get_false<T_>(),
						"Attempted to find the last constant to compare true to a comparison template's invocation via last_constant_to_compare_true, but the instantiated comparison cannot be invoked with a value of type T_."
					);
				}
			}
		};

		template<bool AnyTrue_, T_ LastTrue_>
		struct _find_last_true<AnyTrue_, LastTrue_>
		{
			[[nodiscard]] static constexpr inline T_ get()
			{
				return LastTrue_;
			}
		};

		template<bool AnyTrue_>
		struct _find_last_true<AnyTrue_>
		{
			[[nodiscard]] static constexpr inline T_ get()
			{
				if constexpr (std::is_default_constructible_v<T_>)
				{
					return T_();
				}
				else
				{
					static_assert
					(
						EmuCore::TMP::get_false<T_>(),
						"Attempted to find the last constant to comapre true to a comparison template's invocation via last_constant_to_compare_true, but no arguments were provided and T_ cannot be default constructed."
					);
				}
			}
		};

	public:
		static constexpr T_ value = _find_last_true<false, Vals_...>::get();
	};

	/// <summary> Type to determine the smallest out of any number of passed constant Vals_. If no Vals_ are passed, the value will be default-constructed. </summary>
	template<typename T_, T_...Vals_>
	struct smallest_constant
	{
		static constexpr T_ value = EmuCore::TMP::last_constant_to_compare_true<EmuCore::do_cmp_less, T_, Vals_...>::value;
	};
	template<typename T_, T_...Vals_>
	static constexpr T_ smallest_constant_v = EmuCore::TMP::smallest_constant<T_, Vals_...>::value;

	/// <summary> Type to determine the greatest out of any number of passed constant Vals_. If no Vals_ are passed, the value will be default-constructed. </summary>
	template<typename T_, T_...Vals_>
	struct greatest_constant
	{
		static constexpr T_ value = EmuCore::TMP::last_constant_to_compare_true<EmuCore::do_cmp_greater, T_, Vals_...>::value;
	};
	template<typename T_, T_...Vals_>
	static constexpr T_ greatest_constant_v = EmuCore::TMP::greatest_constant<T_, Vals_...>::value;
#pragma endregion

	template<bool Condition_, template<class...> class TemplateIfTrue, template<class...> class TemplateIfFalse_, class...TypeArgs_>
	struct conditional_template_instance
	{
	private:
		template<bool Val_, template<class...> class IfTrue_, template<class...> class IfFalse_>
		struct _instantiation_template
		{
			using type = void;
			static constexpr bool success = false;
		};

		template<template<class...> class IfTrue_, template<class...> class IfFalse_>
		struct _instantiation_template<false, IfTrue_, IfFalse_>
		{
		private:
			using _safe_instantiate = EmuCore::TMP::safe_template_instantiate<IfFalse_, TypeArgs_...>;

		public:
			using type = typename _safe_instantiate::type;
			static constexpr bool success = _safe_instantiate::value;
		};

		template<template<class...> class IfTrue_, template<class...> class IfFalse_>
		struct _instantiation_template<true, IfTrue_, IfFalse_>
		{
		private:
			using _safe_instantiate = EmuCore::TMP::safe_template_instantiate<IfTrue_, TypeArgs_...>;

		public:
			using type = typename _safe_instantiate::type;
			static constexpr bool success = _safe_instantiate::value;
		};

		using _instantiation = _instantiation_template<Condition_, TemplateIfTrue, TemplateIfFalse_>;

	public:
		using type = typename _instantiation::type;
		static constexpr bool success = _instantiation::success;
	};
}

#endif
