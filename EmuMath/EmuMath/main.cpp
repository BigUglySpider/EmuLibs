#include "EmuCore/TestingHelpers/LoopingTestHarness.h"
#include "EmuCore/FileHelpers/PathValidation.h"
#include "EmuMath/EmuVector.h"
#include <iostream>

using namespace EmuMath;

struct NonConstexpr
{
	NonConstexpr()
	{
		floats.resize(2);
	}

	std::vector<float> floats;
};

int main()
{
	constexpr Vector2<float> CONSTEXPR_VF2 = { 0.0f, 2.0f };
	constexpr Vector2<float> CONSTEXPR_VF2_ADDED = CONSTEXPR_VF2 + Vector2<float>(5.0f, -22.6f);
	constexpr Vector2<std::int32_t> CONSTEXPR_32I2 = { 0, 5 };
	constexpr Vector2<std::int32_t> CONSTEXPR_32I2_ORED = CONSTEXPR_32I2 | std::size_t(2);

	constexpr long double MAG = CONSTEXPR_32I2_ORED.SquareMagnitude();

	return 0;
}