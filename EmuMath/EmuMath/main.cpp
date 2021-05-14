#include "EmuCore/TestingHelpers/LoopingTestHarness.h"
#include "EmuCore/FileHelpers/PathValidation.h"
#include "EmuMath/EmuVector.h"
#include <iostream>

using namespace EmuCore::TestingHelpers;
using namespace EmuMath;

template<typename T>
struct TestA
{
	TestA(std::size_t numLoops)
	{
		allClamped.resize(numLoops);
		for (auto& vec : allClamped)
		{
			vec = { static_cast<T>((rand() % 30 - 15) * 0.75f), static_cast<T>((rand() % 30 - 15) * 0.75f) };
		}
	}
	void operator()(std::size_t i)
	{
		allClamped[i] = allClamped[i].AsTrunced();
	}
	std::vector<Vector2<T>> allClamped;
};

int main()
{
	float balls[2] = { 2.0f, 177.31f };
	constexpr Vector2<float> CONSTEXPR_VF2 = { 0.0f, 2.0f };
	constexpr Vector2<float> CONSTEXPR_VF2_ADDED = CONSTEXPR_VF2 + Vector2<float>(5.0f, -22.6f);
	constexpr Vector2<std::int32_t> CONSTEXPR_32I2 = { 0, 5 };
	constexpr Vector2<std::int32_t> CONSTEXPR_32I2_ORED = CONSTEXPR_32I2 | std::size_t(2);

	constexpr long double MAG = CONSTEXPR_32I2_ORED.SquareMagnitude();

	constexpr Vector2<float> CLAMPED = Vector2<float>(1.0f, 25.0f).AsClamped(0.0f, 4.0f);

	Vector2<float> yo;

	constexpr std::size_t NUM_LOOPS = 5000000;
	using TEST_A = TestA<float>;
	LoopingTestHarness<TEST_A> testHarnessA;
	TEST_A testA(NUM_LOOPS);

	Vector2<float> a = Vector2<float>(1u, 1.0f);

	auto outputA = testHarnessA.ExecuteAndOutputAsString<true>(NUM_LOOPS, testA, false);

	std::cout << "TEST A:\n" << outputA << "\n";

	for (std::size_t i = 0; i < NUM_LOOPS; ++i)
	{
		std::cout << testA.allClamped[i] << "\n";
	}

	return 0;
}