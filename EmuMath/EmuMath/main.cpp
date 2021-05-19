#include "Tests.hpp"

#include "EmuMath/GeneralMath.h"
#include "EmuMath/Vectors.h"

using namespace EmuCore::TestingHelpers;
using namespace EmuMath;



int main()
{
	constexpr double SQRT_0 = EmuMath::SqrtConstexpr<long double>(42141124214126477412.512512);

	constexpr Vector3<std::uint32_t> BLOOB = { 1, 2, 3 };
	constexpr std::uint32_t BLOOB_X = EmuMath::TMPHelpers::emu_vector_x(BLOOB);
	constexpr std::uint32_t BLOOB_Y = EmuMath::TMPHelpers::emu_vector_y(BLOOB);
	constexpr std::uint32_t BLOOB_Z = EmuMath::TMPHelpers::emu_vector_z(BLOOB);
	constexpr std::uint32_t BLOOB_W = EmuMath::TMPHelpers::emu_vector_w(BLOOB);
	constexpr auto BLOOB_SQR_MAGXY = Vector2<std::uint32_t>(BLOOB.x, BLOOB.y).SquareMagnitude();
	constexpr auto BLOOB_SQR_MAG = EmuMath::Helpers::VectorSquareMagnitude<std::uint64_t>(BLOOB);
	constexpr auto BLOOB_MAG = EmuMath::Helpers::VectorMagnitudeConstexpr<long double>(BLOOB);
	constexpr auto BLOOB_NORM = Vector2<std::uint32_t>(BLOOB).NormalisedConstexpr();

	Vector2<int> v2i(-7, 7);
	Vector3<float> v3f(-7.0f, 7.0f, -777.0f);
	std::cout << v2i.AsLerped(Vector2<float>(4.0f, 4.0f), 0.5f) << "\n";

	std::cout << "Base: " << v2i << "\n";
	std::cout << "After add (default): " << v2i.AsAdded(v3f) << "\n";
	std::cout << "After add (v2): " << v2i.AsAdded<2>(v3f) << "\n";
	std::cout << "After add (v3): " << v2i.AsAdded<3, float>(v3f) << "\n";
	//std::cout << "After add (v3): " << (v2i + v3f) << "\n";
	std::cout << "After mult (v3): " << v2i.AsMultiplied<3, double>(v3f) << "\n";
	std::cout << "After scalar mult (v3): " << v2i.AsMultiplied<3, long double>(5.5f) << "\n";

	std::cout << "5 & 4 (same out): " << EmuCore::TMPHelpers::logical_and_diff_types<int, int, int>()(5, 4) << "\n";
	std::cout << "3 & 1 (diff out): " << EmuCore::TMPHelpers::logical_and_diff_types<int, int, std::size_t>()(3, 1) << "\n";

	constexpr std::uint32_t all_32 = 0xFFFFFFFF;
	constexpr float lhsf = 2.0f;
	float rhsf = *reinterpret_cast<const float*>(&all_32);
	std::cout << lhsf << " & " << rhsf << " (same out): " << EmuCore::TMPHelpers::logical_and_diff_types<float, float, float>()(lhsf, rhsf) << "\n";

	constexpr Vector2<std::int16_t> lhsv2si16 = { -2, 2 };
	constexpr Vector2<std::uint32_t> rhsv3ui32 = { 0, 7 };
	constexpr Vector2<float> lhsvf2 = { 2.0f, 4.0f };
	constexpr Vector3<float> rhsvf3 = { 4.0f, 1.0f, 255.0f };
	std::cout << lhsv2si16 << " & " << rhsv3ui32 << ": " << lhsv2si16.AsBitwiseAnded(rhsv3ui32) << "\n";
	std::cout << lhsv2si16 << " ^ 3: " << lhsv2si16.AsBitwiseXored(3) << "\n";

	using T__ =  EmuMath::Vector3<int>;

	Vector2<float> invertv2 = { 1.0f, 2.0f };
	unsigned short yo = 8;
	std::cout << "Before invert: " << yo << " | After invert: " << (EmuCore::TMPHelpers::bit_inversion_diff_types<unsigned short, float>()(yo)) << "\n";
	std::cout << "Before invert (f): " << invertv2 << " | After invert: " << invertv2.AsNot<2, std::uint32_t>() << "\n";
	Vector2<std::uint16_t> inverui16 = { 1, 2 };
	std::cout << "Before invert (ui16): " << inverui16 << " | After invert: " << inverui16.AsNot<3>() << " | " << ~inverui16 << "\n";

	Vector2<float> yooooooo;

	Vector2<float> A(2.5f, 5.0f);
	Vector2<float> B(5.0f, 2.5f);
	Vector2<float> C(2.5f, 2.5f);
	Vector2<float> D(2.5f, 5.0f);


	std::cout << EmuMath::TMPHelpers::emu_vector_z(T__(2, 3, 4)) << "\n";

	EmuMath::Vector4<float> v4f = Vector4<float>(EmuMath::Vector2<int>(2, 1), 1.0f, 66.66666666666666f);

	A.SquareMagnitude<long double>();

	Vector4<float> v4fOut = EmuMath::Helpers::VectorSubtraction<Vector4<float>>(Vector2<std::uint16_t>(5, 2), Vector3<std::uint32_t>(2.5f, 4.0f, 255.0f));
	std::cout << v4fOut << "\n";

	std::uint16_t boi(0b0110001000010000);
	std::cout << "Before reverse: " << boi << " | After reverse: " << EmuCore::TMPHelpers::reverse_bits<std::uint16_t>()(boi) << "\n\n\n";

	Vector4<std::uint16_t> initial = { 0b0000000000000011, 0b1110100000000000, 0b0000000000000001, 0b0100000000000000 };
	Vector4<float> u16vwshift = Vector4<float>();
	Vector4<std::uint32_t> as32 = initial;
	for (std::size_t i = 0, end = Vector2<std::size_t>(initial.size(), u16vwshift.size()).Min(); i < end; ++i)
	{
		u16vwshift.at(i) = *reinterpret_cast<const float*>(&initial.at(i));
	}
	for (std::size_t i = 0, end = Vector2<std::size_t>(initial.size(), u16vwshift.size()).Min(); i < end; ++i)
	{
		as32.at(i) = initial.at(i) << 16;
	}

	Vector4<std::uint16_t> ree = { 0b0000000000000011, 0b1110100000000000, 0b0000000000000011, 0b1000000000000001 };
	Vector2<std::uint16_t> ree2 = { ree.x, ree.y };
	using BitVec2 = Vector2<std::bitset<sizeof(std::uint16_t) * 8>>;
	std::cout << "Before vectorwise shift (Left): " << ree << " | After vectorwise shift (Left): " << EmuMath::Helpers::VectorLeftShiftVectorwise(ree, 16) << "\n";
	std::cout << "Before vectorwise shift (Right): " << ree << " | After vectorwise shift (Right): " << EmuMath::Helpers::VectorRightShiftVectorwise(ree, 48) << "\n";
	std::cout << "Before vectorwise shift (Left): " << BitVec2(ree2) << " | After vectorwise shift (Left): " << BitVec2(ree2.AsLeftShiftedVectorwise(8)) << "\n";
	std::cout << "Before vectorwise shift (Right): " << BitVec2(ree2) << " | After vectorwise shift (Right): " << BitVec2(ree2.AsRightShiftedVectorwise(8)) << "\n";

#pragma region TEST_HARNESS_EXECUTION
	EmuCore::TestingHelpers::PerformTests();
#pragma endregion
	return 0;
}