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
	const float bobs[4] = { 1.0f, 2.0f, 3.0f, 4.0f };
	FastVector<4, float> yo(2.0f, 1.0f, 5.0f, -777.69f);
	yo.vectorData = _mm_load_ps(bobs);
	const float* pData = yo.vectorData.m128_f32;
	std::cout << "Data: { " << pData[0] << ", " << pData[1] << ", " << pData[2] << ", " << pData[3] << " }\n";
	yo = yo.Shuffle<2, 1, 0, 3>();
	std::cout << "Data: { " << pData[0] << ", " << pData[1] << ", " << pData[2] << ", " << pData[3] << " }\n";
	system("pause");

#pragma region TEST_HARNESS_EXECUTION
	EmuCore::TestingHelpers::PerformTests();
#pragma endregion
	return 0;
}