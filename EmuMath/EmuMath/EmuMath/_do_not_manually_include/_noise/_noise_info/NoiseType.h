#ifndef EMU_MATH_NOISE_TYPE_H_INC_
#define EMU_MATH_NOISE_TYPE_H_INC_ 1

#include <cstdint>

namespace EmuMath
{
	/// <summary> Enum flags to specify specific noise types defined within EmuMath. </summary>
	enum class NoiseType : std::uint8_t
	{
		// Perlin noise with no smoothing
		PERLIN = 0x01,
		// Value noise with no smoothing
		VALUE = 0x02,
		// Perlin noise with smoothing applied
		PERLIN_SMOOTH = 0x04,
		// Value noise with smoothing applied
		VALUE_SMOOTH = 0x08
	};

	namespace Validity
	{
		constexpr inline bool IsValidNoiseType(const NoiseType noise_type_)
		{
			return
			(
				noise_type_ == NoiseType::PERLIN ||
				noise_type_ == NoiseType::VALUE ||
				noise_type_ == NoiseType::PERLIN_SMOOTH ||
				noise_type_ == NoiseType::VALUE_SMOOTH
			);
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
