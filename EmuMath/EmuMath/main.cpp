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
	FastVector<4, float> no(5.0f, 1.0f, 6.0f, 2.0f);
	yo.vectorData = _mm_load_ps(bobs);
	const float* pData = yo.vectorData.m128_f32;
	std::cout << "Data: { " << pData[0] << ", " << pData[1] << ", " << pData[2] << ", " << pData[3] << " }\n";
	yo = yo.Shuffle<2, 1, 0, 3>();
	std::cout << "Data: { " << pData[0] << ", " << pData[1] << ", " << pData[2] << ", " << pData[3] << " }\n";
	float dot = yo.DotProduct(no);
	std::cout << yo << " DOT " << no << " = " << dot << "\n\n";

	FastVector<4, float> max0(123.4f, 123.3f, 3.0f, -123.5f);
	FastVector<4, float> max1(4.6f, 22.5f, 3.5f, -22.5f);
	FastVector<4, float> max2(2.3f, -77.1f, 666.666f, 2.2f);
	FastVector<4, float> max3(12.0f, 34.0f, 56.0f, 78.0f);
	std::cout << max0 << " | Min: " << max0.Min() << " |  Max: " << max0.Max() << " | Average: " << max0.Mean() << "\n";
	std::cout << max1 << " | Min: " << max1.Min() << " |  Max: " << max1.Max() << " | Average: " << max1.Mean() << "\n";
	std::cout << max2 << " | Min: " << max2.Min() << " |  Max: " << max2.Max() << " | Average: " << max2.Mean() << "\n";
	std::cout << max3 << " | Min: " << max3.Min() << " |  Max: " << max3.Max() << " | Average: " << max3.Mean() << "\n";

	__m128 test128 = _mm_setr_ps(1.0f, 2.0f, 3.0f, 4.0f);
	test128 = EmuMath::SIMD::horizontal_vector_sum(test128);
	std::cout << "[0] = " << EmuMath::SIMD::get_m128_index(test128, 0) << "\n";
	std::cout << "[1] = " << EmuMath::SIMD::get_m128_index(test128, 1) << "\n";
	std::cout << "[2] = " << EmuMath::SIMD::get_m128_index(test128, 2) << "\n";
	std::cout << "[3] = " << EmuMath::SIMD::get_m128_index(test128, 3) << "\n";
	system("pause");

#pragma region TEST_HARNESS_EXECUTION
	EmuCore::TestingHelpers::PerformTests();
#pragma endregion
	return 0;
}