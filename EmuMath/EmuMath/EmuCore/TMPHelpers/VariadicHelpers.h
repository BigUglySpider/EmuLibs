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
#pragma endregion

#pragma region VARIADIC_BOOLS
	/// <summary> Type to easily produce the result of a logical AND with variadic template argument results. </summary>
	template<bool...Bools_>
	struct variadic_and
	{
		static constexpr bool value = false;
	};
	template<bool First_, bool...Remaining_>
	struct variadic_and<First_, Remaining_...>
	{
		static constexpr bool value = First_ ? variadic_and<Remaining_...>::value : false;
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

	/// <summary> Type to easily produce the result of a logical OR with variadic template argument results. </summary>
	template<bool...Bools_>
	struct variadic_or
	{
		static constexpr bool value = false;
	};
	template<bool First_, bool...Remaining_>
	struct variadic_or<First_, Remaining_...>
	{
		static constexpr bool value = First_ ? true : variadic_or<Remaining_...>::value;
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

	/// <summary> Type to easily produce the result of a logical XOR with variadic template argument results. </summary>
	template<bool...Bools_>
	struct variadic_xor
	{
	private:
		template<bool Current, bool...Bools_>
		struct _variadic_xor_executor
		{
			static constexpr bool value = Current;
		};
		template<bool Current_, bool First_, bool...Remaining_>
		struct _variadic_xor_executor<Current_, First_, Remaining_...>
		{
			[[nodiscard]] static constexpr inline bool _get()
			{
				if constexpr (Current_)
				{
					return First_ ? false : _variadic_xor_executor<Current_, Remaining_...>::value;
				}
				else
				{
					return _variadic_xor_executor<First_, Remaining_...>::value;
				}
			}

			static constexpr bool value = _get();
		};
		template<bool Current_, bool First_>
		struct _variadic_xor_executor<Current_, First_>
		{
			static constexpr bool value = Current_ ^ First_;
		};
		template<bool Current_>
		struct _variadic_xor_executor<Current_>
		{
			static constexpr bool value = Current_;
		};

	public:
		static constexpr bool value = _variadic_xor_executor<false, Bools_...>::value;
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
	///	<para> Type used to splice to index sequences into a single one. Indices in the left-hand sequence will all appear first, then those in the right-hand sequence. </para>
	/// <para> If an argument is not a std::index_sequence, it will be interpreted as an empty std::index_sequence. </para>
	/// </summary>
	template<class LhsIndexSequence_, class RhsIndexSequence_>
	struct splice_index_sequences
	{
		using type = std::index_sequence<>;
	};
	template<std::size_t...LhsIndices_, class Rhs_>
	struct splice_index_sequences<std::index_sequence<LhsIndices_...>, Rhs_>
	{
		using type = std::index_sequence<LhsIndices_...>;
	};
	template<class Lhs_, std::size_t...RhsIndices_>
	struct splice_index_sequences<Lhs_, std::index_sequence<RhsIndices_...>>
	{
		using type = std::index_sequence<RhsIndices_...>;
	};
	template<std::size_t...LhsIndices_, std::size_t...RhsIndices_>
	struct splice_index_sequences<std::index_sequence<LhsIndices_...>, std::index_sequence<RhsIndices_...>>
	{
		using type = std::index_sequence<LhsIndices_..., RhsIndices_...>;
	};
	template<class Lhs_, class Rhs_>
	using splice_index_sequences_t = typename splice_index_sequences<Lhs_, Rhs_>::type;

	/// <summary> Type used to form an index sequence containing only the specified Index_ the specified Count_ of times. </summary>
	template<std::size_t Index_, std::size_t Count_>
	struct duplicated_index_sequence
	{
		using type = typename splice_index_sequences
		<
			std::index_sequence<Index_>,
			typename duplicated_index_sequence<Index_, Count_ - 1>::type
		>::type;
	};
	template<std::size_t Index_>
	struct duplicated_index_sequence<Index_, 0>
	{
		using type = std::index_sequence<>;
	};
	template<std::size_t Index_>
	struct duplicated_index_sequence<Index_, 1>
	{
		using type = std::index_sequence<Index_>;
	};
	template<std::size_t Index_, std::size_t Count_>
	using make_duplicated_index_sequence = typename duplicated_index_sequence<Index_, Count_>::type;

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
}

#endif
