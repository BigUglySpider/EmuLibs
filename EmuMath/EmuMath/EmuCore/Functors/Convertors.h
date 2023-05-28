#ifndef EMU_CORE_FUNCTORS_CONVERTORS_H_INC_
#define EMU_CORE_FUNCTORS_CONVERTORS_H_INC_ 1

#include "../CommonConcepts/Characters.h"
#include "../CommonConcepts/CommonRequirements.h"
#include "../TMPHelpers/TypeComparators.h"

#include <algorithm>
#include <iomanip>
#include <sstream>
#include <string>

namespace EmuCore
{
	/// <summary>
	/// <para> Functor for converting strings and characters to their lower case format. </para>
	/// </summary>
	template<class StringOrChar_>
	struct to_lower
	{
		constexpr inline to_lower() noexcept = default;
		constexpr inline to_lower(const to_lower&) noexcept = default;
		constexpr inline to_lower(to_lower&&) noexcept = default;

		constexpr inline StringOrChar_& operator()(const StringOrChar_& string_or_char_, StringOrChar_& out_string_or_char_) const
		{
			if constexpr (EmuConcepts::AnyBasicChar<StringOrChar_>)
			{
				if constexpr (EmuCore::TMP::is_any_same_v<typename std::remove_cvref<StringOrChar_>::type, char, signed char, unsigned char>)
				{
					out_string_or_char_ = tolower(string_or_char_);
				}
				else if constexpr (std::is_same_v<typename std::remove_cvref<StringOrChar_>::type>)
				{
					out_string_or_char_ = towlower(string_or_char_);
				}
				else
				{
					static_assert(EmuCore::TMP::get_false<StringOrChar_>(), "Invalid EmuCore::to_lower instance: Default instance cannot convert the input char type. A custom implementation is currently required.");
				}
			}
			else
			{
				using _string_uq = typename std::remove_cvref<StringOrChar_>::type;
				std::transform(string_or_char_.begin(), string_or_char_.end(), out_string_or_char_.begin(), to_lower<_string_uq::value_type>());
			}
			return out_string_or_char_;
		}

		[[nodiscard]] constexpr inline StringOrChar_ operator()(const StringOrChar_& string_or_char_) const
		{
			if constexpr (EmuConcepts::AnyBasicChar<StringOrChar_>)
			{
				StringOrChar_ out_char;
				return this->operator()(string_or_char_, out_char);
			}
			else
			{
				StringOrChar_ out_string = StringOrChar_();
				out_string.resize(string_or_char_.size());
				return this->operator()(string_or_char_, out_string);
			}
		}
	};

	/// <summary>
	/// <para> Specialisation of `to_lower` which may take any type as input, and will determine the correct (potentially specialised) instance to call when invoked. </para>
	/// </summary>
	template<>
	struct to_lower<void>
	{
		constexpr inline to_lower() noexcept = default;
		constexpr inline to_lower(const to_lower&) noexcept = default;
		constexpr inline to_lower(to_lower&&) noexcept = default;

		template<class T_>
		[[nodiscard]] constexpr inline decltype(auto) operator()(T_&& string_or_char_) const
		{
			return to_lower<typename std::remove_cvref<T_>::type>()(std::forward<T_>(string_or_char_));
		}

		template<class T_>
		[[nodiscard]] constexpr inline decltype(auto) operator()(T_&& string_or_char_, typename std::remove_cvref<T_>::type& out_string_or_char_) const
		{
			return to_lower<typename std::remove_cvref<T_>::type>()(std::forward<T_>(string_or_char_), out_string_or_char_);
		}
	};

	/// <summary>
	/// <para> Functor for converting strings and characters to booleans. </para>
	/// </summary>
	template<class T_>
	struct string_to_bool
	{
		constexpr inline string_to_bool() noexcept = default;
		constexpr inline string_to_bool(const string_to_bool&) noexcept = default;
		constexpr inline string_to_bool(string_to_bool&&) noexcept = default;

		template<EmuConcepts::UnqualifiedMatch<T_> StringArg_>
		[[nodiscard]] constexpr inline bool operator()(StringArg_&& string_) const
		{
			using _string_uq = typename std::remove_cvref<T_>::type;
			if constexpr (EmuCore::TMP::is_instance_of_typeparams_only_v<T_, std::basic_string>)
			{
				// We have a std::basic_string, so we can defer this to a stream
				using _value_type = typename _string_uq::value_type;
				using _trait_type = typename _string_uq::traits_type;
				using _alloc_type = typename _string_uq::allocator_type;
				std::basic_istringstream<_value_type, _trait_type, _alloc_type> str_stream(std::forward<StringArg_>(string_));
				bool out_bool;
				str_stream >> std::boolalpha >> out_bool;
				return out_bool;
			}
			else
			{
				auto lower_string = EmuCore::to_lower<_string_uq>()(std::forward<StringArg_>(string_));
				if constexpr (EmuConcepts::AnyBasicChar<T_>)
				{
					return (lower_string != '0') && (lower_string != 'f') && (lower_string != 0);
				}
				else
				{
					const std::size_t string_size = lower_string.size();
					return
					(
						(string_size <= 5)        && 
						(string_size != 0)        &&
						(lower_string != "f")     &&
						(lower_string != "false") &&
						(lower_string != "0")
					);
				}
			}
		}
	};

	/// <summary>
	/// <para> Specialisation of `string_to_bool` which may take any type as input, and will determine the correct (potentially specialised) instance to call when invoked. </para>
	/// </summary>
	template<>
	struct string_to_bool<void>
	{
		constexpr inline string_to_bool() noexcept = default;
		constexpr inline string_to_bool(const string_to_bool&) noexcept = default;
		constexpr inline string_to_bool(string_to_bool&&) noexcept = default;

		template<class T_>
		[[nodiscard]] constexpr inline bool operator()(T_&& string_or_char_) const
		{
			return string_to_bool<typename std::remove_cvref<T_>::type>()(std::forward<T_>(string_or_char_));
		}
	};
}

#endif