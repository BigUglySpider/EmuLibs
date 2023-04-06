#ifndef EMU_CORE_BIT_HELPERS_H_INC_
#define EMU_CORE_BIT_HELPERS_H_INC_ 1

#include <bit>
#include <cstddef>
#include <cstdint>
#include <utility>

namespace EmuCore::ArithmeticHelpers
{
	constexpr inline std::size_t num_active_bits(std::uint32_t val)
	{
		val -= ((val >> 1) & 0x55555555);
		val = (val & 0x33333333) + ((val >> 2) & 0x33333333);
		val = (val + (val >> 4)) & 0x0F0F0F0F;
		return static_cast<std::size_t>((val * 0x01010101) >> 24);
	}
	template<std::uint32_t Val_>
	static constexpr std::size_t num_active_bits_v = num_active_bits(Val_);

	template<typename IntT_>
	constexpr inline bool is_integral_power_of_2(IntT_ val_)
	{
		static_assert(std::is_integral_v<IntT_>, "Provided a non-integral type to EmuCore::ArithmeticHelpers::is_integral_power_of_2.");
		return val_ && ((val_ & (val_ - 1)) == 0);
	}

	template<typename UintT_>
	constexpr inline UintT_ highest_set_uint_bit(UintT_ val_)
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
	constexpr inline UintT_ next_unsigned_power_of_2(UintT_ val_)
	{
		UintT_ highest_bit_ = highest_set_uint_bit<UintT_>(val_);
		return highest_bit_ == 0 ? UintT_(1) : (highest_bit_ << 1);
	}

	template<typename UintT_>
	constexpr inline UintT_ previous_unsigned_power_of_2(UintT_ val_)
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
}

#endif
