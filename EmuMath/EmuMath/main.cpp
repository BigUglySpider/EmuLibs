#include "Tests.hpp"

#include "EmuMath/Vectors.h"

using namespace EmuCore::TestingHelpers;
using namespace EmuMath;

int main()
{
	Vector2<int> v2i(-7, 7);
	std::cout << v2i.AsLerped(Vector2<float>(4.0f, 4.0f), 0.5f) << "\n";

#pragma region TEST_HARNESS_EXECUTION
	EmuCore::TestingHelpers::PerformTests();
#pragma endregion
	return 0;
}