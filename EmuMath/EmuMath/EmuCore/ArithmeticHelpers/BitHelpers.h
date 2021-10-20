#ifndef EMU_CORE_BIT_HELPERS_H_INC_
#define EMU_CORE_BIT_HELPERS_H_INC_ 1

#include <cstddef>
#include <cstdint>

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
}

#endif
