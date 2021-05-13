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
	constexpr Vector2<std::int32_t> CONSTEXPR_32I2_ANDED = CONSTEXPR_32I2 | std::size_t(2);

	Vector2<float> vf2;
	vf2.x = 0;
	vf2.y = 1;

	constexpr Vector2<float> vf2Divd = CONSTEXPR_VF2 / 5.0f;
	Vector2<float> yo = vf2Divd / int(0);
	std::cout << yo;
	auto shuffledRef = yo.ShuffledReference<1, 0>();
	shuffledRef.y = 555.5f;
	std::cout << yo;
	std::cout << "\n" << shuffledRef;
	shuffledRef = shuffledRef * 5;
	std::cout << yo;
	return 0;
}