#ifndef EMU_CORE_BIT_HELPERS_H_INC_
#define EMU_CORE_BIT_HELPERS_H_INC_ 1

#include <array>
#include <bit>
#include <cstddef>
#include <cstdint>
#include <utility>

namespace EmuCore::ArithmeticHelpers
{
	/// <summary>
	/// <para> Compile-time check if the byte order of the target system is little-endian (or there is no endianness due to all scalar types being 1-byte). </para>
	/// </summary>
	/// <returns>True if target system is little-endian or has no endianness; otherwise false.</returns>
	[[nodiscard]] constexpr inline bool is_little_endian() noexcept
	{
		return std::endian::native == std::endian::little;
	}

	/// <summary>
	/// <para> Compile-time check if the byte order of the target system is big-endian (or there is no endianness due to all scalar types being 1-byte). </para>
	/// </summary>
	/// <returns>True if target system is big-endian or has no endianness; otherwise false.</returns>
	[[nodiscard]] constexpr inline bool is_big_endian() noexcept
	{
		return std::endian::native == std::endian::big;
	}

	/// <summary>
	/// <para> Compile-time check if the byte order of the target system is mixed-endian. </para>
	/// </summary>
	/// <returns>True if target system is mixed-endian; otherwise false.</returns>
	[[nodiscard]] constexpr inline bool is_mixed_endian() noexcept
	{
		return std::endian::native != std::endian::little && std::endian::native != std::endian::big;
	}

	/// <summary>
	/// <para> Compile-time check if the target system is byte-order-agnostic due to all scalar types having a byte size of 1. </para>
	/// </summary>
	/// <returns>True if target system has no endianness; otherwise false.</returns>
	[[nodiscard]] constexpr inline bool is_no_endian() noexcept
	{
		return std::endian::little == std::endian::big && std::endian::little == std::endian::native;
	}

	constexpr inline std::size_t num_active_bits(std::uint32_t val) noexcept
	{
		val -= ((val >> 1) & 0x55555555);
		val = (val & 0x33333333) + ((val >> 2) & 0x33333333);
		val = (val + (val >> 4)) & 0x0F0F0F0F;
		return static_cast<std::size_t>((val * 0x01010101) >> 24);
	}
	template<std::uint32_t Val_>
	static constexpr std::size_t num_active_bits_v = num_active_bits(Val_);

	template<typename IntT_>
	constexpr inline bool is_integral_power_of_2(IntT_ val_) noexcept
	{
		static_assert(std::is_integral_v<IntT_>, "Provided a non-integral type to EmuCore::ArithmeticHelpers::is_integral_power_of_2.");
		return val_ && ((val_ & (val_ - 1)) == 0);
	}

	template<typename UintT_>
	constexpr inline UintT_ highest_set_uint_bit(UintT_ val_) noexcept
	{
		if (val_ == 0)
		{
			return 0;
		}
		else
		{
			std::size_t bit_offset_ = 0;
			val_ >>= 1;
			while (val_ != 0)
			{
				++bit_offset_;
				val_ >>= 1;
			}
			return UintT_(1) << bit_offset_;
		}
	}

	template<typename UintT_>
	constexpr inline UintT_ next_unsigned_power_of_2(UintT_ val_) noexcept
	{
		UintT_ highest_bit_ = highest_set_uint_bit<UintT_>(val_);
		return highest_bit_ == 0 ? UintT_(1) : (highest_bit_ << 1);
	}

	template<typename UintT_>
	constexpr inline UintT_ previous_unsigned_power_of_2(UintT_ val_) noexcept
	{
		UintT_ highest_bit_ = highest_set_uint_bit<UintT_>(val_);
		return (highest_bit_ <= 1) ? UintT_(1) : (highest_bit_ >> 1);
	}

	namespace _underlying_funcs
	{
		template<typename UnqualifiedT_, std::size_t...ByteIndices_>
		[[nodiscard]] constexpr inline decltype(auto) _set_generic_bits_to_max(std::index_sequence<ByteIndices_...> byte_indices_) noexcept
		{
			using byte_type = unsigned char;
			constexpr byte_type all_one = std::numeric_limits<byte_type>::max();
			constexpr byte_type bytes[sizeof...(ByteIndices_)] = { static_cast<byte_type>(all_one + (ByteIndices_ * 0))... };
			return std::bit_cast<UnqualifiedT_>(bytes);
		}
	}

	template<typename T_>
	[[nodiscard]] constexpr inline decltype(auto) set_all_bits_one() noexcept
	{
		using _unqualified_type = typename std::remove_cvref<T_>::type;
		if constexpr (std::is_integral_v<_unqualified_type>)
		{
			if constexpr (std::is_signed_v<_unqualified_type>)
			{
				return _unqualified_type(-1);
			}
			else
			{
				return std::numeric_limits<_unqualified_type>::max();
			}
		}
		else
		{
			constexpr std::size_t num_bytes = sizeof(_unqualified_type);
			return _underlying_funcs::_set_generic_bits_to_max<_unqualified_type>(std::make_index_sequence<num_bytes>());
		}
	}

	/// <summary>
	/// <para> Determines the value of the most-significant byte within the passed item type. </para>
	/// <para> This function is compatible with any type, including non-arithmetic values. </para>
	/// <para> Output as any type that can be constructed from a `std::byte`; defaults to a `std::byte` if no output type is provided. </para>
	/// <para> May optionally output a reference to the byte by passing `std::byte&amp;` as the Out_ type. Normal const-safety rules apply. </para>
	/// </summary>
	/// <returns>Value of or reference to the most-significant byte, which may lie anywhere within the range of 0x00:0xFF (or signed equivalent).</returns>
	template<typename Out_ = std::byte, typename T_>
	[[nodiscard]] constexpr inline auto get_most_significant_byte(T_& in_) noexcept
		-> Out_
	{
		constexpr std::size_t num_bytes = sizeof(T_);
		constexpr std::size_t msb_index = is_little_endian() ? (num_bytes - 1) : 0;
		std::byte* p_bytes = reinterpret_cast<std::byte*>(&in_);
		return static_cast<Out_>(*(p_bytes + msb_index));
	}

	template<typename Out_ = std::byte, typename T_>
	[[nodiscard]] constexpr inline auto get_most_significant_byte(const T_& in_) noexcept
		-> Out_
	{
		constexpr std::size_t num_bytes = sizeof(T_);
		constexpr std::size_t msb_index = is_little_endian() ? (num_bytes - 1) : 0;
		const std::byte* p_bytes = reinterpret_cast<const std::byte*>(&in_);
		return static_cast<Out_>(*(p_bytes + msb_index));
	}

	/// <summary>
	/// <para> Determines the value of the least-significant byte within the passed item type. </para>
	/// <para> This function is compatible with any type, including non-arithmetic values. </para>
	/// <para> Output as any type that can be constructed from a `std::byte`; defaults to a `std::byte` if no output type is provided. </para>
	/// <para> May optionally output a reference to the byte by passing `std::byte&amp;` as the Out_ type. Normal const-safety rules apply. </para>
	/// </summary>
	/// <returns>Value of or reference to the least-significant byte, which may lie anywhere within the range of 0x00:0xFF (or signed equivalent).</returns>
	template<typename Out_ = std::byte, typename T_>
	[[nodiscard]] constexpr inline auto get_least_significant_byte(T_& in_) noexcept
		-> Out_
	{
		if constexpr (std::integral<T_> && !std::is_reference_v<Out_>)
		{
			return static_cast<Out_>(in_ & typename std::remove_cvref<T_>::type(0xFF));
		}
		else
		{
			constexpr std::size_t num_bytes = sizeof(T_);
			constexpr std::size_t lsb_index = is_little_endian() ? 0 : (num_bytes - 1);
			std::byte* p_bytes = reinterpret_cast<std::byte*>(&in_);
			return static_cast<Out_>(*(p_bytes + lsb_index));
		}
	}

	template<typename Out_ = std::byte, typename T_>
	[[nodiscard]] constexpr inline auto get_least_significant_byte(const T_& in_) noexcept
		-> Out_
	{
		if constexpr (std::integral<T_> && !std::is_reference_v<Out_>)
		{
			return static_cast<Out_>(in_ & typename std::remove_cvref<T_>::type(0xFF));
		}
		else
		{
			constexpr std::size_t num_bytes = sizeof(T_);
			constexpr std::size_t lsb_index = is_little_endian() ? 0 : (num_bytes - 1);
			const std::byte* p_bytes = reinterpret_cast<const std::byte*>(&in_);
			return static_cast<Out_>(*(p_bytes + lsb_index));
		}
	}

	/// <summary>
	/// <para> Determines the value of the most-significant byte within the passed item type. </para>
	/// <para> This function is compatible with any type, including non-arithmetic values. </para>
	/// <para> Output as any type that can be constructed from a `std::byte`; defaults to a `std::byte` if no output type is provided. </para>
	/// <para> Executed in a way that can be evaluated at compile-time; if executing at runtime, use `get_most_significant_byte` instead for performance reasons. </para>
	/// </summary>
	/// <returns>Value of the most-significant byte, which may lie anywhere within the range of 0x00:0xFF (or signed equivalent).</returns>
	template<typename Out_ = std::byte, typename T_>
	[[nodiscard]] constexpr inline auto get_most_significant_byte_constexpr(const T_& in_) noexcept
		-> typename std::remove_cvref<Out_>::type
	{
		constexpr std::size_t num_bytes = sizeof(T_);
		constexpr std::size_t msb_index = is_little_endian() ? (num_bytes - 1) : 0;
		using _bytes_array_type = std::array<std::byte, num_bytes>;
		const _bytes_array_type bytes = std::bit_cast<_bytes_array_type>(in_);
		return static_cast<typename std::remove_cvref<Out_>::type>(bytes[msb_index]);
	}

	/// <summary>
	/// <para> Determines the value of the least-significant byte within the passed item type. </para>
	/// <para> This function is compatible with any type, including non-arithmetic values. </para>
	/// <para> Output as any type that can be constructed from a `std::byte`; defaults to a `std::byte` if no output type is provided. </para>
	/// <para> Executed in a way that can be evaluated at compile-time; if executing at runtime, use `get_least_significant_byte` instead for performance reasons. </para>
	/// </summary>
	/// <returns>Value of the least-significant byte, which may lie anywhere within the range of 0x00:0xFF (or signed equivalent).</returns>
	template<typename Out_ = std::byte, typename T_>
	[[nodiscard]] constexpr inline auto get_least_significant_byte_constexpr(const T_& in_) noexcept
		-> typename std::remove_cvref<Out_>::type
	{
		if constexpr (std::integral<T_>)
		{
			return static_cast<typename std::remove_cvref<Out_>::type>(in_ & typename std::remove_cvref<T_>::type(0xFF));
		}
		else
		{
			constexpr std::size_t num_bytes = sizeof(T_);
			constexpr std::size_t lsb_index = is_little_endian() ? 0 : (num_bytes - 1);
			using _bytes_array_type = std::array<std::byte, num_bytes>;
			const _bytes_array_type bytes = std::bit_cast<_bytes_array_type>(in_);
			return static_cast<typename std::remove_cvref<Out_>::type>(bytes[lsb_index]);
		}
	}

	/// <summary>
	/// <para> Determines the value of the most-significant bit within the passed item type. </para>
	/// <para> This function is compatible with any type, including non-arithmetic values. </para>
	/// <para> Output as any type that can be constructed from a `std::byte`; defaults to a `std::byte` if no output type is provided. </para>
	/// </summary>
	/// <returns>1 if the most-significant bit is set; otherwise 0.</returns>
	template<typename Out_ = std::byte, typename T_>
	[[nodiscard]] constexpr inline auto get_most_significant_bit(const T_& in_) noexcept
		-> typename std::remove_cvref<Out_>::type
	{
		return static_cast<typename std::remove_cvref<Out_>::type>
		(
			get_most_significant_byte<std::byte>(in_) >> 7
		);
	}

	/// <summary>
	/// <para> Determines the value of the least-significant bit within the passed item type. </para>
	/// <para> This function is compatible with any type, including non-arithmetic values. </para>
	/// <para> Output as any type that can be constructed from a `std::byte`; defaults to a `std::byte` if no output type is provided. </para>
	/// </summary>
	/// <returns>1 if the least-significant bit is set; otherwise 0.</returns>
	template<typename Out_ = std::byte, typename T_>
	[[nodiscard]] constexpr inline auto get_least_significant_bit(const T_& in_) noexcept
		-> typename std::remove_cvref<Out_>::type
	{
		if constexpr (std::integral<T_>)
		{
			return static_cast<Out_>(in_ & typename std::remove_cvref<T_>::type(1));
		}
		else
		{
			return static_cast<typename std::remove_cvref<Out_>::type>
			(
				get_least_significant_byte<std::byte>(in_) & std::byte(1)
			);
		}
	}

	/// <summary>
	/// <para> Determines the value of the most-significant bit within the passed item type. </para>
	/// <para> This function is compatible with any type, including non-arithmetic values. </para>
	/// <para> Output as any type that can be constructed from a `std::byte`; defaults to a `std::byte` if no output type is provided. </para>
	/// <para> Executed in a way that can be evaluated at compile-time; if executing at runtime, use `get_most_significant_bit` instead for performance reasons. </para>
	/// </summary>
	/// <returns>1 if the most-significant bit is set; otherwise 0.</returns>
	template<typename Out_ = std::byte, typename T_>
	[[nodiscard]] constexpr inline auto get_most_significant_bit_constexpr(const T_& in_) noexcept
		-> typename std::remove_cvref<Out_>::type
	{
		return static_cast<typename std::remove_cvref<Out_>::type>
		(
			get_most_significant_byte_constexpr<std::byte>(in_) >> 7
		);
	}

	/// <summary>
	/// <para> Determines the value of the least-significant bit within the passed item type. </para>
	/// <para> This function is compatible with any type, including non-arithmetic values. </para>
	/// <para> Output as any type that can be constructed from a `std::byte`; defaults to a `std::byte` if no output type is provided. </para>
	/// <para> Executed in a way that can be evaluated at compile-time; if executing at runtime, use `get_least_significant_bit` instead for performance reasons. </para>
	/// </summary>
	/// <returns>1 if the least-significant bit is set; otherwise 0.</returns>
	template<typename Out_ = std::byte, typename T_>
	[[nodiscard]] constexpr inline auto get_least_significant_bit_constexpr(const T_& in_) noexcept
		-> typename std::remove_cvref<Out_>::type
	{
		if constexpr (std::integral<T_>)
		{
			return static_cast<Out_>(in_ & typename std::remove_cvref<T_>::type(1));
		}
		else
		{
			return static_cast<typename std::remove_cvref<Out_>::type>
			(
				get_least_significant_byte_constexpr<std::byte>(in_) & std::byte(1)
			);
		}
	}
}

#endif
