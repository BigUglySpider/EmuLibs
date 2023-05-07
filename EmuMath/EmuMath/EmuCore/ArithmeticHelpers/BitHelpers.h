#ifndef EMU_CORE_BIT_HELPERS_H_INC_
#define EMU_CORE_BIT_HELPERS_H_INC_ 1

#include "../CommonConcepts/Arithmetic.h"
#include "../TMPHelpers/TypeConvertors.h"
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

	namespace _underlying_funcs
	{
		template<class T_, std::size_t...Indices_>
		[[nodiscard]] constexpr inline std::size_t _pop_count_per_byte(T_&& val_, std::index_sequence<Indices_...> byte_indices_) noexcept
		{
			if constexpr (true) // TODO: Update to `if consteval` to allow optimised branch in C++23
			{
				constexpr std::size_t num_bytes = sizeof(typename std::remove_cvref<T_>::type);
				using _bytes_arr_type = std::array<unsigned char, num_bytes>;
				auto bytes_array = std::bit_cast<_bytes_arr_type>(std::forward<T_>(val_));
				return (std::popcount(bytes_array[Indices_]) + ...);
			}
			else
			{
				const unsigned char* p_bytes = reinterpret_cast<const unsigned char*>(&(std::forward<T_>(val_)));
				return (std::popcount(*(p_bytes + Indices_)) + ...);
			}
		}
	}

	/// <summary>
	/// <para> Returns the number of bits currently set to 1 within the passed value. </para>
	/// <para> Where necessary, casts will be made to abide by strict aliasing. </para>
	/// <para> By default, items that are neither integral nor floating-point will be popcounted on a per-byte basis in order to abide by strict aliasing. </para>
	/// </summary>
	/// <returns>Total number of bits set to 1 within the memory used to store the passed item.</returns>
	template<class T_>
	constexpr inline std::size_t pop_count(T_&& val_) noexcept
	{
		if constexpr (EmuConcepts::UnsignedInteger<T_>)
		{
			return std::popcount(std::forward<T_>(val_));
		}
		else if constexpr (EmuConcepts::SignedInteger<T_>)
		{
			return std::popcount
			(
				static_cast<typename std::make_unsigned<typename std::remove_cvref<T_>::type>::type>(std::forward<T_>(val_))
			);
		}
		else if constexpr (EmuConcepts::FloatingPoint<T_>)
		{
			constexpr std::size_t num_bytes = sizeof(typename std::remove_cvref<T_>::type);
			return std::popcount
			(
				std::bit_cast<EmuCore::TMP::uint_of_size_t<num_bytes>>(std::forward<T_>(val_))
			);
		}
		else
		{
			constexpr std::size_t num_bytes = sizeof(typename std::remove_cvref<T_>::type);
			return _underlying_funcs::_pop_count_per_byte(std::forward<T_>(val_), std::make_index_sequence<num_bytes>());
		}
	}

	/// <summary>
	/// <para> Determines if the passed value is a power of 2. </para>
	/// </summary>
	/// <param name="val_">Value to check.</param>
	/// <returns>True if `val_` is a power of 2; otherwise false.</returns>
	template<EmuConcepts::UnsignedInteger Uint_>
	constexpr inline bool is_integral_power_of_2(Uint_ val_) noexcept
	{
		const auto& val_ref = std::forward<Uint_>(val_);
		return (val_ref) && ((val_ref & (val_ref - 1)) == 0);
	}

	template<EmuConcepts::SignedInteger SignedInt_>
	constexpr inline bool is_integral_power_of_2(SignedInt_ val_) noexcept
	{
		using _unsigned_type = typename std::make_unsigned<typename std::remove_cvref<SignedInt_>::type>::type;
		const auto& val_ref = std::forward<SignedInt_>(val_);
		const auto is_negative = static_cast<typename std::remove_cvref<SignedInt_>::type>(val_ref < 0);
		return is_integral_power_of_2
		(
			static_cast<_unsigned_type>(val_ref * ((is_negative * -2) + 1))
		);
	}

	/// <summary>
	/// <para> Returns the bit set within the passed value. </para>
	/// <para> The output value is the power of 2 represented by the discovered bit (e.g. for `0b1110`, the output will be `8`.) </para>
	/// </summary>
	/// <param name="val_">Value to search.</param>
	/// <returns>Power of 2 represented by the highest bit within the passed `val_`. If no bits are active, this is 0.</returns>
	template<EmuConcepts::UnsignedInteger Uint_>
	constexpr inline auto highest_set_bit(Uint_ val_) noexcept
		-> typename std::remove_cvref<Uint_>::type
	{
		std::size_t bit_offset = 0;
		auto popped_val = val_ >> 1;
		while (popped_val)
		{
			++bit_offset;
			popped_val >>= 1;
		}
		return typename std::remove_cvref<Uint_>::type(val_ != 0) << bit_offset;
	}

	template<EmuConcepts::SignedInteger Int_>
	[[nodiscard]] constexpr inline auto highest_set_bit(Int_&& val_) noexcept
		-> typename std::remove_cvref<Int_>::type
	{
		constexpr std::size_t num_bytes = sizeof(typename std::remove_cvref<Int_>::type);
		auto highest_unsigned_bit = highest_set_bit
		(
			static_cast<typename std::make_unsigned<typename std::remove_cvref<Int_>::type>::type>(std::forward<Int_>(val_))
		);
		return static_cast<typename std::remove_cvref<Int_>::type>
		(
			std::move(highest_unsigned_bit)
		);
	}

	/// <summary>
	/// <para> Determines the next power of 2 for the passed value. </para>
	/// <para> 
	///		If `ExcludeCurrentPowerIfReducingMagnitude_` is true, 
	///		this will ignore the current power even if the passed value is greater than it (absolutely) if the previous power results in a smaller absolute value.
	/// </para>
	/// <para> `ExcludeCurrentPowerIfReducingMagnitude_` is only useful if the input value is negative; otherwise it is functionally useless. </para>
	/// <para> If `SustainDirection_` is `true`, the direction of power increases will continue to move in the direction of the passed value (e.g. 5 -> 8, -5 -> -8). </para>
	/// <para> If `SustainDirection_` is `false`, the direction of power increases will always move toward positive infinity (e.g. 5 -> 8, -5 -> [-4|-2]), stopping at -1 if negative. </para>
	/// <para> By default, `SustainDirection_` is `false`. </para>
	/// <para> By default, `ExcludeCurrentPowerIfReducingMagnitude_` is `false`. </para>
	/// </summary>
	/// <param name="val_">Value to find the next power of 2 for.</param>
	/// <returns>Next greatest power of 2 from the current value in `val_`.</returns>
	template<bool ExcludeCurrentPowerIfReducingMagnitude_ = true, bool SustainDirection_ = false, EmuConcepts::UnsignedInteger Uint_>
	constexpr inline auto next_power_of_2(Uint_&& val_) noexcept
		-> typename std::remove_cvref<Uint_>::type
	{
		const auto highest_bit = highest_set_bit<typename std::remove_cvref<Uint_>::type>(std::forward<Uint_>(val_));
		return typename std::remove_cvref<Uint_>::type(highest_bit == 0) | (highest_bit << 1);
	}

	template<bool ExcludeCurrentPowerIfReducingMagnitude_ = true, bool SustainDirection_ = false, EmuConcepts::SignedInteger SignedInt_>
	constexpr inline auto next_power_of_2(SignedInt_&& val_) noexcept
		-> typename std::remove_cvref<SignedInt_>::type
	{
		using _unsigned_type = typename std::make_unsigned<typename std::remove_cvref<SignedInt_>::type>::type;
		constexpr _unsigned_type all_bits = std::numeric_limits<_unsigned_type>::max();
		const auto& val_ref = std::forward<SignedInt_>(val_);

		const bool is_negative = val_ref < 0;
		const _unsigned_type not_mask = all_bits * static_cast<_unsigned_type>(is_negative);
		_unsigned_type unsigned_next = static_cast<_unsigned_type>(val_ref ^ not_mask);
		unsigned_next = next_power_of_2(unsigned_next);

		if constexpr (SustainDirection_)
		{
			int extra_negative_offset = 0 * is_negative * (ExcludeCurrentPowerIfReducingMagnitude_);
			unsigned_next <<= ((is_integral_power_of_2(val_ref) * is_negative) + extra_negative_offset);
		}
		else
		{
			int extra_negative_offset = int(ExcludeCurrentPowerIfReducingMagnitude_ && is_negative && !is_integral_power_of_2(val_ref));
			unsigned_next >>= (int(is_negative) + extra_negative_offset);
		}
		return static_cast<typename std::remove_cvref<SignedInt_>::type>(unsigned_next ^ not_mask) + is_negative;
	}

	/// <summary>
	/// <para> Determines the previous power of 2 for the passed value. </para>
	/// <para> Stops at 1 (or -1 if negative and moving in the positive direction), and transforms 0 into 1. </para>
	/// <para> 
	///		If `ExcludeCurrentPowerIfReducingMagnitude_` is true, 
	///		this will ignore the current power even if the passed value is greater than it (absolutely) if the previous power results in a smaller absolute value.
	/// </para>
	/// <para> If `SustainDirection_` is `true`, the direction of power reductions will continue to move toward 0 (e.g. 5 -> [4|2], -5 -> [-4|-2]), stopping at 1 or -1 depending on direction. </para>
	/// <para> If `SustainDirection_` is `false`, the direction of power reductions will always move toward negative infinity (e.g. 5 -> [4|2], -5 -> -8), stopping at 1 if positive. </para>
	/// <para> By default, `ExcludeCurrentPower_` is `true`. </para>
	/// <para> By default, `ExcludeCurrentPowerIfReducingMagnitude_` is `false`. </para>
	/// </summary>
	/// <param name="val_">Value to find the next power of 2 for.</param>
	/// <returns>Next greatest power of 2 from the current value in `val_`.</returns>
	template<bool ExcludeCurrentPowerIfReducingMagnitude_ = true, bool SustainDirection_ = false, EmuConcepts::UnsignedInteger Uint_>
	constexpr inline auto previous_power_of_2(Uint_&& val_) noexcept
		-> typename std::remove_cvref<Uint_>::type
	{
		if constexpr (ExcludeCurrentPowerIfReducingMagnitude_)
		{
			const auto highest_bit = highest_set_bit(std::forward<Uint_>(val_));
			return typename std::remove_cvref<Uint_>::type(highest_bit <= 1) | (highest_bit >> 1);
		}
		else
		{
			const auto& val_ref = std::forward<Uint_>(val_);
			const auto highest_bit = highest_set_bit(val_ref);
			const auto shift_count = static_cast<int>(is_integral_power_of_2(val_ref));
			return typename std::remove_cvref<Uint_>::type(highest_bit <= 1) | (highest_bit >> shift_count);
		}
	}

	template<bool ExcludeCurrentPowerIfReducingMagnitude_ = true, bool SustainDirection_ = false, EmuConcepts::SignedInteger SignedInt_>
	constexpr inline auto previous_power_of_2(SignedInt_&& val_) noexcept
		-> typename std::remove_cvref<SignedInt_>::type
	{
		using _unsigned_type = typename std::make_unsigned<typename std::remove_cvref<SignedInt_>::type>::type;
		constexpr _unsigned_type all_bits = std::numeric_limits<_unsigned_type>::max();
		const auto& val_ref = std::forward<SignedInt_>(val_);
		const auto is_negative = static_cast<typename std::remove_cvref<SignedInt_>::type>(val_ref < 0);
		const _unsigned_type not_mask = all_bits * static_cast<_unsigned_type>(is_negative);
		_unsigned_type unsigned_prev = static_cast<_unsigned_type>(val_ref ^ not_mask);
		unsigned_prev = previous_power_of_2<ExcludeCurrentPowerIfReducingMagnitude_>(unsigned_prev);
		if constexpr (!SustainDirection_)
		{
			unsigned_prev <<= (is_negative << ExcludeCurrentPowerIfReducingMagnitude_) + (is_negative && int(is_integral_power_of_2(val_ref)));
		}
		else
		{
			unsigned_prev <<= int(ExcludeCurrentPowerIfReducingMagnitude_ && is_negative && is_integral_power_of_2(val_ref));
		}
		return static_cast<typename std::remove_cvref<SignedInt_>::type>(unsigned_prev ^ not_mask) + is_negative;
	}

	namespace _underlying_funcs
	{
		template<auto ValToDiscard_>
		[[nodiscard]] constexpr inline decltype(auto) _discard_template_arg_retrieve_func_arg(auto&& func_arg_) noexcept
		{
			return std::forward<decltype(func_arg_)>(func_arg_);
		}

		template<typename UnqualifiedT_, std::size_t...ByteIndices_>
		[[nodiscard]] constexpr inline decltype(auto) _set_generic_bits_to_zero(std::index_sequence<ByteIndices_...> byte_indices_) noexcept
		{
			using byte_type = unsigned char;
			constexpr byte_type all_zero = byte_type(0x00);
			constexpr byte_type bytes[sizeof...(ByteIndices_)] = { _discard_template_arg_retrieve_func_arg<ByteIndices_>(all_zero)... };
			return std::bit_cast<UnqualifiedT_>(bytes);
		}

		template<typename UnqualifiedT_, std::size_t...ByteIndices_>
		[[nodiscard]] constexpr inline decltype(auto) _set_generic_bits_to_max(std::index_sequence<ByteIndices_...> byte_indices_) noexcept
		{
			using byte_type = unsigned char;
			constexpr byte_type all_one = byte_type(0xFF);
			constexpr byte_type bytes[sizeof...(ByteIndices_)] = { _discard_template_arg_retrieve_func_arg<ByteIndices_>(all_one)... };
			return std::bit_cast<UnqualifiedT_>(bytes);
		}
	}

	/// <summary>
	/// <para> "Safely" creates the specified type with all bits set to 0. </para>
	/// <para> Naturally, this is unsafe to use with more complex types that should not be all-0 in memory. </para>
	/// </summary>
	/// <returns>Input type created in memory as all 0s.</returns>
	template<typename T_>
	[[nodiscard]] constexpr inline decltype(auto) set_all_bits_zero() noexcept
	{
		if constexpr (EmuConcepts::Arithmetic<T_>)
		{
			return typename std::remove_cvref<T_>::type();
		}
		else
		{
			constexpr std::size_t num_bytes = sizeof(typename std::remove_cvref<T_>::type);
			return _underlying_funcs::_set_generic_bits_to_zero<typename std::remove_cvref<T_>::type>(std::make_index_sequence<num_bytes>());
		}
	}

	/// <summary>
	/// <para> "Safely" creates the specified type with all bits set to 1. </para>
	/// <para> Naturally, this is unsafe to use with more complex types that should not be all-1 in memory. </para>
	/// </summary>
	/// <returns>Input type created in memory as all 1s.</returns>
	template<typename T_>
	[[nodiscard]] constexpr inline decltype(auto) set_all_bits_one() noexcept
	{
		if constexpr (std::is_integral_v<typename std::remove_cvref<T_>::type>)
		{
			if constexpr (std::is_signed_v<typename std::remove_cvref<T_>::type>)
			{
				return typename std::remove_cvref<T_>::type(-1);
			}
			else
			{
				return std::numeric_limits<typename std::remove_cvref<T_>::type>::max();
			}
		}
		else
		{
			using _uint_equivalent = EmuCore::TMP::uint_of_size_t<sizeof(typename std::remove_cvref<T_>::type)>;
			if constexpr (!std::is_same_v<_uint_equivalent, EmuCore::TMP::emu_tmp_err>)
			{
				constexpr _uint_equivalent all_one_uint = std::numeric_limits<_uint_equivalent>::max();
				return std::bit_cast<typename std::remove_cvref<T_>::type>(all_one_uint);
			}
			else
			{
				constexpr std::size_t num_bytes = sizeof(typename std::remove_cvref<T_>::type);
				return _underlying_funcs::_set_generic_bits_to_max<typename std::remove_cvref<T_>::type>
				(
					std::make_index_sequence<num_bytes>()
				);
			}
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

	/// <summary>
	/// <para> Creates the passed `Out_` type (without qualification) as either all 0s or all 1s, depending on the value of the bit at the given index within the passed `bit_mask_`. </para>
	/// <para> If the bit at the specified index is `0`, the output is all-zero; if the bit at the specified index is `1`, the output is all-one. </para>
	/// <para> `BitIndex_` must be a valid zero-based index of bits that are contained within the width of the passed mask. </para>
	/// <para> Naturally, this is unsafe to use with more complex types that should not be all-1 or all-0 in memory. </para>
	/// <para> May optionally pass another item of the same width as `Out_` to use instead of all-1 in the case where the bit at the specified index is `1`. </para>
	/// </summary>
	/// <param name="bit_mask_">Unsigned integer to use inspect as the bit mask.</param>
	/// <returns>Item of the specified type as all-zero in memory if the bit at the specified index within the mask is 0; otherwise the specified type as all-one in memory.</returns>
	template<std::size_t BitIndex_, typename Out_, EmuConcepts::UnsignedInteger UnsignedBitMask_>
	[[nodiscard]] constexpr inline auto make_from_masked_bit(UnsignedBitMask_&& bit_mask_) noexcept
		-> typename std::remove_cvref<Out_>::type
	{
		constexpr std::size_t total_bits_in_mask = sizeof(typename std::remove_cvref<UnsignedBitMask_>::type) * CHAR_BIT;
		static_assert(BitIndex_ < total_bits_in_mask, "Invalid mask bit index provided to `make_from_masked_bit`: exceeds the highest bit index for that passed mask. You may need to cast to a higher width integer if expecting the stated bit to be present.");

		constexpr auto mask_for_bit_index = typename std::remove_cvref<UnsignedBitMask_>::type(1) << BitIndex_;
		if constexpr (EmuConcepts::Arithmetic<Out_>)
		{
			if constexpr (EmuConcepts::FloatingPoint<Out_>)
			{
				using _uint_of_out_width = EmuCore::TMP::uint_of_size_t<sizeof(typename std::remove_cvref<Out_>::type)>;
				constexpr auto int_ones_mask = set_all_bits_one<_uint_of_out_width>();
				return std::bit_cast<typename std::remove_cvref<Out_>::type>
				(
					static_cast<_uint_of_out_width>((bit_mask_ & mask_for_bit_index) >> BitIndex_) * int_ones_mask
				);
			}
			else
			{
				constexpr auto ones_mask = set_all_bits_one<typename std::remove_cvref<Out_>::type>();
				return static_cast<typename std::remove_cvref<Out_>::type>((bit_mask_ & mask_for_bit_index) >> BitIndex_) * ones_mask;
			}
		}
		else
		{
			if (((bit_mask_ & mask_for_bit_index) >> BitIndex_))
			{
				return set_all_bits_one<typename std::remove_cvref<Out_>::type>();
			}
			else
			{
				constexpr std::size_t num_bytes = sizeof(typename std::remove_cvref<Out_>::type);
				constexpr auto bytes = std::array<unsigned char, num_bytes>();
				return std::bit_cast<typename std::remove_cvref<Out_>::type>(bytes);
			}
		}
	}

	/// <summary>
	/// <para> Creates the passed `Out_` type (without qualification) as either all 0s or all 1s, depending on the value of the bit at the given index within the passed `bit_mask_`. </para>
	/// <para> If the bit at the specified index is `0`, the output is all-zero; if the bit at the specified index is `1`, the output is all-one. </para>
	/// <para> `BitIndex_` must be a valid zero-based index of bits that are contained within the width of the passed mask. </para>
	/// <para> Naturally, this is unsafe to use with more complex types that should not be all-1 or all-0 in memory. </para>
	/// </summary>
	/// <param name="bit_mask_">Unsigned integer to use inspect as the bit mask.</param>
	/// <param name="mask_for_out_if_bit_active_">Mask to use instead of all-ones if the specified bit in `bit_mask_` is active.</param>
	/// <returns>Item of the specified type as all-zero in memory if the bit at the specified index within the mask is 0; otherwise the specified type as the given `mask_for_out_if_bit_active_` in memory.</returns>
	template<std::size_t BitIndex_, typename Out_, EmuConcepts::UnsignedInteger UnsignedBitMask_, typename OutMaskIfActiveBit_>
	requires(sizeof(typename std::remove_cvref<Out_>::type) == sizeof(typename std::remove_cvref<OutMaskIfActiveBit_>::type))
	[[nodiscard]] constexpr inline auto make_from_masked_bit(UnsignedBitMask_&& bit_mask_, OutMaskIfActiveBit_&& mask_for_out_if_bit_active_) noexcept
		-> typename std::remove_cvref<Out_>::type
	{
		constexpr std::size_t total_bits_in_mask = sizeof(typename std::remove_cvref<UnsignedBitMask_>::type) * CHAR_BIT;
		static_assert(BitIndex_ < total_bits_in_mask, "Invalid mask bit index provided to `make_from_masked_bit`: exceeds the highest bit index for that passed mask. You may need to cast to a higher width integer if expecting the stated bit to be present.");

		constexpr auto mask_for_bit_index = typename std::remove_cvref<UnsignedBitMask_>::type(1) << BitIndex_;
		if constexpr (EmuConcepts::Arithmetic<Out_>)
		{
			if constexpr (EmuConcepts::FloatingPoint<Out_>)
			{
				using _uint_of_out_width = EmuCore::TMP::uint_of_size_t<sizeof(typename std::remove_cvref<Out_>::type)>;
				_uint_of_out_width correct_int_mask;
				if constexpr (EmuConcepts::Integer<OutMaskIfActiveBit_>)
				{
					correct_int_mask = static_cast<_uint_of_out_width>(std::forward<OutMaskIfActiveBit_>(mask_for_out_if_bit_active_));
				}
				else
				{
					correct_int_mask = std::bit_cast<_uint_of_out_width>(std::forward<OutMaskIfActiveBit_>(mask_for_out_if_bit_active_));
				}

				return std::bit_cast<typename std::remove_cvref<Out_>::type>
				(
					static_cast<_uint_of_out_width>((bit_mask_ & mask_for_bit_index) >> BitIndex_) * correct_int_mask
				);
			}
			else
			{
				return static_cast<typename std::remove_cvref<Out_>::type>
				(
					static_cast<typename std::remove_cvref<Out_>::type>((bit_mask_ & mask_for_bit_index) >> BitIndex_) *
					std::forward<OutMaskIfActiveBit_>(mask_for_out_if_bit_active_)
				);
			}
		}
		else
		{
			if (((bit_mask_ & mask_for_bit_index) >> BitIndex_))
			{
				return std::bit_cast<typename std::remove_cvref<Out_>::type>(std::forward<OutMaskIfActiveBit_>(mask_for_out_if_bit_active_));
			}
			else
			{
				constexpr std::size_t num_bytes = sizeof(typename std::remove_cvref<Out_>::type);
				constexpr auto bytes = std::array<unsigned char, num_bytes>();
				return std::bit_cast<typename std::remove_cvref<Out_>::type>(bytes);
			}
		}
	}
}

#endif
