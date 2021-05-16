#include "Tests.hpp"

#include "EmuMath/Vectors.h"

using namespace EmuCore::TestingHelpers;
using namespace EmuMath;

int main()
{
	Vector2<int> v2i(-7, 7);
	Vector3<float> v3f(-7.0f, 7.0f, -777.0f);
	std::cout << v2i.AsLerped(Vector2<float>(4.0f, 4.0f), 0.5f) << "\n";

	std::cout << "Base: " << v2i << "\n";
	std::cout << "After add (default): " << v2i.AsAdded(v3f) << "\n";
	std::cout << "After add (v2): " << v2i.AsAdded<2>(v3f) << "\n";
	std::cout << "After add (v3): " << v2i.AsAdded<3, float>(v3f) << "\n";
	std::cout << "After mult (v3): " << v2i.AsMultiplied<3, double>(v3f) << "\n";
	std::cout << "After scalar mult (v3): " << v2i.AsMultiplied<3, long double>(5.5f) << "\n";


	using T__ =  EmuMath::Vector3<int>;

	std::cout << EmuMath::TMPHelpers::emu_vector_z(T__(2, 3, 4)) << "\n";

#pragma region TEST_HARNESS_EXECUTION
	EmuCore::TestingHelpers::PerformTests();
#pragma endregion
	return 0;
}