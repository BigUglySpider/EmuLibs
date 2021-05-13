#include "EmuCore/TestingHelpers/LoopingTestHarness.h"
#include "EmuCore/FileHelpers/PathValidation.h"
#include "EmuMath/EmuVector.h"
#include <iostream>

using namespace EmuCore::TestingHelpers;
using namespace EmuMath;

template<typename T>
struct NonSIMDTest
{
	NonSIMDTest(std::size_t numLoops)
	{
		allClamped.resize(numLoops);
		for (auto& vec : allClamped)
		{
			vec = { static_cast<T>(rand() % 30 - 15), static_cast<T>(rand() % 30 - 15) };
		}
	}
	void operator()(std::size_t i)
	{
		allClamped[i] = allClamped[i].AsClamped(T(0), T(1));
	}
	std::vector<Vector2<T>> allClamped;
};

template<typename T>
struct SIMDTest
{
	SIMDTest(std::size_t numLoops)
	{
		allClamped.resize(numLoops);
		for (auto& vec : allClamped)
		{
			vec = { static_cast<T>(rand() % 30 - 15), static_cast<T>(rand() % 30 - 15) };
		}
	}
	void operator()(std::size_t i)
	{
		allClamped[i].Clamp(T(0), T(1));
	}
	std::vector<Vector2<T>> allClamped;
};

int main()
{
	constexpr Vector2<float> CONSTEXPR_VF2 = { 0.0f, 2.0f };
	constexpr Vector2<float> CONSTEXPR_VF2_ADDED = CONSTEXPR_VF2 + Vector2<float>(5.0f, -22.6f);
	constexpr Vector2<std::int32_t> CONSTEXPR_32I2 = { 0, 5 };
	constexpr Vector2<std::int32_t> CONSTEXPR_32I2_ORED = CONSTEXPR_32I2 | std::size_t(2);

	constexpr long double MAG = CONSTEXPR_32I2_ORED.SquareMagnitude();

	constexpr Vector2<float> CLAMPED = Vector2<float>(1.0f, 25.0f).AsClamped(0.0f, 4.0f);

	Vector2<float> yo;

	constexpr std::size_t NUM_LOOPS = 5000000;
	using NO_SIMD = NonSIMDTest<float>;
	using SIMD = SIMDTest<float>;
	LoopingTestHarness<NO_SIMD> nonSimdHarness;
	LoopingTestHarness<SIMD> simdHarness;
	NO_SIMD noSimd(NUM_LOOPS);
	SIMD simd(NUM_LOOPS);

	auto noSimdOutput = nonSimdHarness.ExecuteAndOutputAsString<true>(NUM_LOOPS, noSimd, false);
	auto simdOutput = simdHarness.ExecuteAndOutputAsString<true>(NUM_LOOPS, simd, false);

	std::cout << "NO SIMD:\n" << noSimdOutput << "\n\nWITH SIMD:\n" << simdOutput << "\n";

	for (std::size_t i = 0; i < NUM_LOOPS; ++i)
	{
		std::cout << simd.allClamped[i] << " | " << noSimd.allClamped[i] << "\n";
	}

	return 0;
}