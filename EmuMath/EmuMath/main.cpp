#include "Tests.hpp"

#include "EmuMath/GeneralMath.h"
#include "EmuMath/NoOverflowT.h"
#include "EmuMath/Vectors.h"
#include "EmuMath/FastVector.h"
#include <array>

using namespace EmuCore::TestingHelpers;
using namespace EmuMath;

int main()
{
	FastVector<4, float> yo(2.0f, 1.0f, 5.0f, -777.69f);

#pragma region TEST_HARNESS_EXECUTION
	EmuCore::TestingHelpers::PerformTests();
#pragma endregion
	return 0;
}