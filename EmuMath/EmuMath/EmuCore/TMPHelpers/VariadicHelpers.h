#ifndef EMU_CORE_VARIADIC_HELPERS_H_INC_
#define EMU_CORE_VARIADIC_HELPERS_H_INC_ 1

#include <utility>

namespace EmuCore::TMP
{
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
	template<std::size_t Offset_, std::size_t Size_>
	struct offset_index_sequence_maker
	{
	private:
		template<std::size_t Remaining_, std::size_t Current_, typename Previous_>
		struct _maker
		{
			using type = void;
		};
		template<std::size_t Remaining_, std::size_t Current_, std::size_t...PreviousIndices_>
		struct _maker<Remaining_, Current_, std::index_sequence<PreviousIndices_...>>
		{
			using type = typename _maker<Remaining_ - 1, Current_ + 1, std::index_sequence<PreviousIndices_..., Current_>>::type;
		};
		template<std::size_t Current_, std::size_t...PreviousIndices_>
		struct _maker<0, Current_, std::index_sequence<PreviousIndices_...>>
		{
			using type = std::index_sequence<PreviousIndices_...>;
		};

	public:
		using type = typename _maker<Size_, Offset_, std::index_sequence<>>::type;
	};

	template<std::size_t Offset_, std::size_t Size_>
	using make_offset_index_sequence = typename offset_index_sequence_maker<Offset_, Size_>::type;

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
#pragma endregion
}

#endif
