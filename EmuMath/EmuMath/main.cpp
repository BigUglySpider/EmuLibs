#include "Tests.hpp"

#include "EmuMath/EmuVector.h"

using namespace EmuCore::TestingHelpers;
using namespace EmuMath;

int main()
{
	float balls[2] = { 2.0f, 177.31f };
	constexpr Vector2<float> CONSTEXPR_VF2 = { 0.0f, 2.0f };
	constexpr Vector2<float> CONSTEXPR_VF2_ADDED = CONSTEXPR_VF2 + Vector2<float>(5.0f, -22.6f);
	constexpr Vector2<std::int32_t> CONSTEXPR_32I2 = { 0, 5 };
	constexpr Vector2<std::int32_t> CONSTEXPR_32I2_ORED = CONSTEXPR_32I2 | std::size_t(2);

	constexpr long double MAG = CONSTEXPR_32I2_ORED.SquareMagnitude();

	constexpr Vector2<float> CLAMPED = Vector2<float>(1.0f, 25.0f).AsClamped(0.0f, 4.35f);

	Vector2<float> yo = CLAMPED;
	yo *= 5;
	Vector2<float&> yoRef = yo.ShuffledReference<0, 1>();
	yoRef /= 5;
	yoRef *= 2.3l;

	std::cout << "Normal: " << yoRef << " | Floored: "<< yoRef.AsFloored() << "\n";
	Vector2<const float&> boi = yoRef;

	Vector2<float&> anotherRef = yo;


	Vector2<float> a = Vector2<float>(15u, 1.0f);
	std::cout << a << "\n";

	Vector3<float> v3f(0.0f, 1.75f, 2.0f);
	Vector2si16 v2si16Fromv3f = v3f;
	std::cout << "v3f: " << v3f << " | v2si16: " << v2si16Fromv3f << "\n";

	Vector3<std::uint64_t> v3ui64 = v2si16Fromv3f;
	std::cout << v3ui64 << "\n";

#pragma region TEST_HARNESS_EXECUTION
	EmuCore::TestingHelpers::PerformTests();
#pragma endregion
	return 0;
}