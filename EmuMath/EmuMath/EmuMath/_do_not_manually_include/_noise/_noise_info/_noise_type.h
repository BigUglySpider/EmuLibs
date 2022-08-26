#ifndef EMU_MATH_NOISE_TYPE_H_INC_
#define EMU_MATH_NOISE_TYPE_H_INC_ 1

#include <cstdint>
#include "../../../../EmuCore/TMPHelpers/Values.h"

namespace EmuMath
{
	/// <summary> Enum flags to specify specific noise types defined within EmuMath. </summary>
	enum class NoiseType : std::uint8_t
	{
		// Smooth Perlin noise
		PERLIN = 0x01,
		// Value noise with no smoothing
		VALUE = 0x02,
		// Value noise with smoothing applied
		VALUE_SMOOTH = 0x04
	};

	namespace Validity
	{
		[[nodiscard]] constexpr inline bool is_valid_noise_type(const NoiseType noise_type_)
		{
			// Disable this warning as we want exact matches, not specific bits
#pragma warning(push)
#pragma warning(disable: 26813)
			return
			(
				noise_type_ == NoiseType::PERLIN ||
				noise_type_ == NoiseType::VALUE ||
				noise_type_ == NoiseType::VALUE_SMOOTH
			);
#pragma warning(pop)
		}

		template<NoiseType NoiseType_>
		constexpr inline bool assert_valid_noise_type()
		{
			if constexpr (is_valid_noise_type(NoiseType_))
			{
				return true;
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<NoiseType, NoiseType_>(), "Valid EmuMath::NoiseType assertion failed. A NoiseType may only be one of the defined EmuMath::NoiseType enum values.");
				return false;
			}
		}
	}
}

#endif
