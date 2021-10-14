#ifndef EMU_MATH_NOISE_TYPE_H_INC_
#define EMU_MATH_NOISE_TYPE_H_INC_ 1

#include <cstdint>

namespace EmuMath
{
	enum class NoiseType : std::uint8_t
	{
		PERLIN = 1u,
		VALUE = 2u
	};

	namespace Validity
	{
		constexpr inline bool IsValidNoiseType(const NoiseType noise_type_)
		{
			return noise_type_ == NoiseType::PERLIN || noise_type_ == NoiseType::VALUE;
		}

		template<NoiseType NoiseType_>
		constexpr inline bool AssertValidNoiseType()
		{
			if constexpr (IsValidNoiseType(NoiseType_))
			{
				return true;
			}
			else
			{
				static_assert(false, "Valid EmuMath::NoiseType assertion failed. A NoiseType may only be one of the defined EmuMath::NoiseType enum values.");
				return false;
			}
		}
	}
}

#endif
