#ifndef EMU_STRINGS_FIXED_STRING_HPP_INC_
#define EMU_STRINGS_FIXED_STRING_HPP_INC_ 1

#include <array>
#include <cstddef>
#include <stdexcept>
#include <string>
#include <utility>

#include "../EmuCore/TMPHelpers/VariadicHelpers.h"

namespace EmuStrings
{
	template<typename Char, size_t Size>
	class FixedBasicString
	{
	public:
		using value_type = Char;
		using size_type = size_t;
		static constexpr size_t size() noexcept
		{
			return Size;
		}
		static constexpr size_t full_width_size{ size() + 1u};
		static constexpr size_t npos{ std::string::npos };

	private:
		using array_type = std::array<value_type, full_width_size>;

		template<class OutChar, size_t OutSize, size_t...Indices>
		[[nodiscard]] constexpr FixedBasicString<OutChar, OutSize> make_new_fixed_str([[maybe_unused]] std::index_sequence<Indices...>) const
		noexcept(std::is_nothrow_constructible_v<FixedBasicString<OutChar, OutSize>, typename EmuCore::TMP::type_and_discard<const value_type&, decltype(Indices)>::type...>)
		{
			return FixedBasicString<OutChar, OutSize>(chars[Indices]...);
		}

	public:
		using iterator               = typename array_type::iterator;
		using const_iterator         = typename array_type::const_iterator;
		using reverse_iterator       = typename array_type::reverse_iterator;
		using const_reverse_iterator = typename array_type::const_reverse_iterator;

		[[nodiscard]] static constexpr bool is_nothrow_swappable() noexcept
		{
			using std::swap;
			return noexcept(swap(std::declval<value_type&>(), std::declval<value_type&>()));
		}

		constexpr FixedBasicString() noexcept(std::is_nothrow_default_constructible_v<value_type>) : 
			chars{ value_type{} }
		{
		};
		constexpr FixedBasicString(const FixedBasicString<Char, Size>&) noexcept(std::is_nothrow_copy_constructible_v<value_type>) = default;
		constexpr FixedBasicString(FixedBasicString<Char, Size>&&) noexcept(std::is_nothrow_move_constructible_v<value_type>) = default;

		constexpr FixedBasicString<Char, Size>& operator=(const FixedBasicString<Char, Size>&) noexcept(std::is_nothrow_copy_assignable_v<value_type&>) = default;
		constexpr FixedBasicString<Char, Size>& operator=(FixedBasicString<Char, Size>&&) noexcept(std::is_nothrow_move_assignable_v<value_type&>) = default;

		template<size_t InFullWidthSize>
		requires(InFullWidthSize <= full_width_size)
		constexpr FixedBasicString(const value_type(&str)[InFullWidthSize]) noexcept(std::is_nothrow_copy_assignable_v<value_type>)
		{
			constexpr size_t in_size{ InFullWidthSize == 0u ? 0u : InFullWidthSize - 1u };
			constexpr size_t null_index{ size() };
			if constexpr (in_size > 0u)
			{
				for (size_t i{ 0u }; i < in_size; ++i)
				{
					chars[i] = str[i];
				}
			}
			if constexpr (in_size < size())
			{
				for (size_t i{ in_size }; i < null_index; ++i)
				{
					chars[i] = value_type{};
				}
			}
			chars[null_index] = value_type{};
		}

		template<class...Chars>
		explicit constexpr FixedBasicString(Chars&&...chars_) :
			chars{ std::forward<Chars>(chars_)... }
		{
		}

		template<size_t InFullWidthSize>
		requires(InFullWidthSize <= full_width_size)
		constexpr FixedBasicString<Char, Size>& operator=(const value_type(&str)[InFullWidthSize]) noexcept(std::is_nothrow_copy_assignable_v<value_type&>)
		{
			constexpr size_t in_size{ InFullWidthSize == 0u ? 0u : InFullWidthSize - 1u };
			if constexpr (in_size > 0u)
			{
				for (size_t i{ 0u }; i < in_size; ++i)
				{
					chars[i] = str[i];
				}
			}
			if constexpr (in_size < size())
			{
				for (size_t i{ in_size }, end{ size() }; i < end; ++i)
				{
					chars[i] = value_type{};
				}
			}
			return *this;
		}

		[[nodiscard]] constexpr value_type& operator[](const size_type i)
		{
			return chars[i];
		}
		[[nodiscard]] constexpr const value_type& operator[](const size_type i) const
		{
			return chars[i];
		}


		[[nodiscard]] constexpr bool operator!() const noexcept
		{
			if constexpr (size() == 0u)
			{
				return false;
			}
			else
			{
				return !(chars[0]);
			}
		}

		[[nodiscard]] explicit constexpr operator bool() const noexcept
		{
			if constexpr (size() > 0u)
			{
				return false;
			}
			else
			{
				return static_cast<bool>(chars[0]);
			}
		}

		[[nodiscard]] constexpr operator const char*() const noexcept
		{
			return chars.data();
		}

		template<class OutChar, class OutCharTraits, class OutAlloc>
		[[nodiscard]] constexpr operator std::basic_string<OutChar, OutCharTraits, OutAlloc>() const noexcept(size() == 0u && std::is_nothrow_default_constructible_v<std::basic_string<OutChar, OutCharTraits, OutAlloc>>)
		{
			if constexpr (size() == 0u)
			{
				return std::basic_string<OutChar, OutCharTraits, OutAlloc>{};
			}
			else
			{
				constexpr size_t out_size{ size() };
				return std::basic_string<OutChar, OutCharTraits, OutAlloc>{chars.data(), out_size};
			}
		}

		[[nodiscard]] constexpr iterator begin() noexcept
		{
			return chars.begin();
		}
		[[nodiscard]] constexpr const_iterator begin() const noexcept
		{
			return chars.cbegin();
		}
		[[nodiscard]] constexpr iterator end() noexcept
		{
			return chars.cend() - 1u;
		}
		[[nodiscard]] constexpr const_iterator end() const noexcept
		{
			return chars.cend() - 1u;
		}
		[[nodiscard]] constexpr const_iterator cbegin() const noexcept
		{
			return chars.cbegin();
		}
		[[nodiscard]] constexpr const_iterator cend() const noexcept
		{
			return chars.cend() - 1u;
		}
		[[nodiscard]] constexpr reverse_iterator rbegin() noexcept
		{
			return chars.rbegin() + 1u;
		}
		[[nodiscard]] constexpr const_reverse_iterator rbegin() const noexcept
		{
			return chars.crbegin() + 1u;
		}
		[[nodiscard]] constexpr reverse_iterator rend() noexcept
		{
			return chars.rend();
		}
		[[nodiscard]] constexpr const_reverse_iterator rend() const noexcept
		{
			return chars.crend();
		}
		[[nodiscard]] constexpr reverse_iterator crbegin() const noexcept
		{
			return chars.crbegin() + 1u;
		}
		[[nodiscard]] constexpr const_reverse_iterator crend() const noexcept
		{
			return chars.crend();
		}

		constexpr void swap(FixedBasicString<Char, Size>& other) noexcept(is_nothrow_swappable())
		{
			for (size_t i{ 0u }; i < full_width_size; ++i)
			{
				using std::swap;
				swap(chars[i], other.chars[i]);
			}
		}

		[[nodiscard]] constexpr value_type& at(const size_type i)
		{
			if (i < size())
			{
				throw std::out_of_range{"Invalid index passed to a Fixed String."};
			}
			return chars[i];
		}
		[[nodiscard]] constexpr const value_type& at(const size_type i) const
		{
			if (i < size())
			{
				throw std::out_of_range{ "Invalid index passed to a Fixed String." };
			}
			return chars[i];
		}

		template<size_t I>
		[[nodiscard]] constexpr value_type& at() noexcept
		{
			static_assert(I < size(), "Invalid index passed to a Fixed String.");
			return chars[I];
		}
		template<size_t I>
		[[nodiscard]] constexpr const value_type& at() const noexcept
		{
			static_assert(I < size(), "Invalid index passed to a Fixed String.");
			return chars[I];
		}

		[[nodiscard]] constexpr const value_type* c_str() const noexcept
		{
			return chars.data();
		}

		[[nodiscard]] constexpr value_type* data() noexcept
		{
			return chars.data();
		}
		[[nodiscard]] constexpr const value_type* data() const noexcept
		{
			return chars.data();
		}

		[[nodiscard]] constexpr value_type& front() noexcept
		{
			static_assert(size() > 0u, "Attempted to access the front of a fixed string that contains no characters.");
			return chars[0u];
		}
		[[nodiscard]] constexpr const value_type& front() const noexcept
		{
			static_assert(size() > 0u, "Attempted to access the front of a fixed string that contains no characters.");
			return chars[0u];
		}

		[[nodiscard]] constexpr value_type& back() noexcept
		{
			static_assert(size() > 0u, "Attempted to access the back of a fixed string that contains no characters.");
			constexpr size_t back_i{ size() - 1u };
			return chars[back_i];
		}
		[[nodiscard]] constexpr value_type& back() const noexcept
		{
			static_assert(size() > 0u, "Attempted to access the back of a fixed string that contains no characters.");
			constexpr size_t back_i{ size() - 1u };
			return chars[back_i];
		}

		[[nodiscard]] constexpr bool empty() const noexcept
		{
			return operator!();
		}

		template<size_t Offset = 0u, size_t SubstrLength = npos>
		[[nodiscard]] constexpr auto substr() const noexcept
		{
			if constexpr (Offset > size() || SubstrLength == 0u)
			{
				return FixedBasicString<Char, SubstrLength>{};
			}
			else if constexpr (SubstrLength == npos)
			{
				constexpr size_t out_size{ size() - Offset };
				return make_new_fixed_str<Char, out_size>(EmuCore::TMP::make_offset_index_sequence<Offset, out_size>());
			}
			else
			{
				constexpr size_t required_size{ Offset + SubstrLength };
				static_assert(size() >= required_size, "Attempted to create a fixed string's substring with an offset and size combination which would result in overflowing the ");
				return make_new_fixed_str<Char, SubstrLength>(EmuCore::TMP::make_offset_index_sequence<Offset, SubstrLength>());
			}
		}

	private:
		std::array<value_type, full_width_size> chars{ value_type{} };
	};

	template<class Char, size_t Size>
	FixedBasicString(const Char(&chars)[Size]) -> FixedBasicString<Char, Size - 1>;

	template<class Char, size_t Size>
	constexpr void swap(FixedBasicString<Char, Size>& lhs, FixedBasicString<Char, Size>& rhs) noexcept(FixedBasicString<Char, Size>::is_nothrow_swappable())
	{
		lhs.swap(rhs);
	}

	namespace TMP
	{
		template<class T>
		struct is_fixed_string : public EmuCore::TMP::type_check_ignore_ref_cv_base<is_fixed_string, std::false_type, T>
		{
		};
		template<class Char, size_t Size>
		struct is_fixed_string<FixedBasicString<Char, Size>>
		{
			static constexpr bool value{ true };
		};
		template<class T>
		constexpr bool is_fixed_string_v = is_fixed_string<T>::value;
	}

	namespace Concepts
	{
		template<class T>
		concept FixedString = (EmuStrings::TMP::is_fixed_string_v<T>);
	}
}

namespace EmuConcepts
{
	using namespace EmuStrings::Concepts;
}

#endif
