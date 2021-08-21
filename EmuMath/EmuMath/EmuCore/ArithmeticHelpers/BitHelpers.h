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
}

#endif
