#include "Tests.hpp"

#include "EmuMath/GeneralMath.h"
#include "EmuMath/Vectors.h"
#include <array>

using namespace EmuCore::TestingHelpers;
using namespace EmuMath;

template<typename T>
using bitset_t = std::bitset<sizeof(T) * CHAR_BIT>;

int main()
{
	constexpr Vector2<std::uint32_t> V2UI32 = { 0xFFFF0000, 0x0000FFFF };
	constexpr Vector2<std::uint32_t> NOT_V2UI32 = ~V2UI32;
	constexpr Vector4<std::uint64_t> V4UI64 = { 0xFFFFFFFFFFFFFFFF, 0x0000FFFF00000000, 0x00000000FFFF0000, 0x0000000000FFFF };

	constexpr float VAL = 2415126.37f;
	constexpr float MINUS_VAL = -VAL;

	constexpr float VAL_FLOOR = EmuCore::TMPHelpers::floor_diff_types<float, float>::ConstexprRound(VAL);
	constexpr float MINUS_VAL_FLOOR = EmuCore::TMPHelpers::floor_diff_types<float, float>::ConstexprRound(MINUS_VAL);

	constexpr float VAL_CEIL = EmuCore::TMPHelpers::ceil_diff_types<float, float>::ConstexprRound(VAL);
	constexpr float MINUS_VAL_CEIL = EmuCore::TMPHelpers::ceil_diff_types<float, float>::ConstexprRound(MINUS_VAL);

	constexpr float VAL_TRUNC = EmuCore::TMPHelpers::trunc_diff_types<float, float>::ConstexprRound(VAL);
	constexpr float MINUS_VAL_TRUNC = EmuCore::TMPHelpers::trunc_diff_types<float, float>::ConstexprRound(MINUS_VAL);

	constexpr Vector4<float> V4f = { 0.31f, -617.369f, 2.3f, 1.0f };
	constexpr Vector4<float> V4f_ceil = EmuMath::Helpers::VectorCeilConstexpr<4, float>(V4f);
	constexpr Vector4<float> V4f_floor = EmuMath::Helpers::VectorFloorConstexpr<4, float>(V4f);
	constexpr Vector4<float> V4f_trunc = EmuMath::Helpers::VectorTruncConstexpr<4, float>(V4f);

	constexpr Vector2<float> v2f = Vector2<float>(V4f);
	constexpr Vector2<float> v2f_ceil = v2f.CeilConstexpr();
	constexpr Vector2<float> v2f_floor = v2f.FloorConstexpr();
	constexpr Vector2<float> v2f_trunc = v2f.TruncConstexpr();

	EmuCore::TMPHelpers::bits_in_type_v<std::array<float, 400>>;

	constexpr Vector2<float> v4f_ywv2_ceil = V4f.AsShuffled<1, 3>().CeilConstexpr();

	constexpr float V4f_V4fyw2_dot = EmuMath::Helpers::VectorDotProduct<float>(V4f, v4f_ywv2_ceil);

	constexpr float min_v4f = EmuMath::Helpers::VectorMin<float>(V4f);
	constexpr float max_v4f = EmuMath::Helpers::VectorMax<float>(V4f);
	constexpr float min_v4fyw2 = v4f_ywv2_ceil.Min();
	constexpr float max_v4fyw2 = v4f_ywv2_ceil.Max();

	constexpr Vector4<float> v4f_clamped_min = EmuMath::Helpers::VectorClampMin<4, float>(V4f, -255);
	constexpr Vector4<float> v4f_clamped_max = EmuMath::Helpers::VectorClampMax<4, float>(V4f, -0.5f);
	constexpr Vector3<float> v4f_clamped = EmuMath::Helpers::VectorClamp<3, float>(V4f, -1000.0f, Vector4<float>(0.5f, 0.5f, 2.1f, 0.5f));

	v2f.Clamp(0.5f, 2.0f);
	v2f.ClampMin(0.5f);
	v2f.ClampMax(0.5f);

	constexpr Vector4<float> a_ = { 1.0f, 25.0f, -7.0f, 1.234f };
	constexpr Vector3<double> b_ = { 0.0, -25.0, 1.0 };
	constexpr Vector3<long double> t_ = { 0.5L, 0.25L, 0.75L };
	constexpr double lone_t_ = 0.5;
	constexpr Vector4<float> lerp_scalar_t_ = EmuMath::Helpers::VectorLerp<4, float>(a_, b_, lone_t_);
	constexpr Vector4<long double> lerp_vector_t_ = EmuMath::Helpers::VectorLerp<4, long double>(a_, b_, t_);

	constexpr Vector2<float> lerp_scalar_t_v2 = Vector2<float>(lerp_scalar_t_);
	constexpr Vector2<float> further_lerp_v2 = lerp_scalar_t_v2.Lerp(b_, lone_t_);

	constexpr Vector4<bool> check_equal_v4 = EmuMath::Helpers::VectorComparisonPerElement_Equal<4>(Vector2f(0.0f, 5.0f), Vector4<float>(5.0f, 5.0f, 1.0f, 0.0f));
	constexpr Vector4<bool> check_not_equal_v4 = EmuMath::Helpers::VectorComparisonPerElement_NotEqual<4>(Vector2f(0.0f, 5.0f), Vector4<float>(5.0f, 5.0f, 1.0f, 0.0f));
	constexpr Vector4<bool> check_less_v4 = EmuMath::Helpers::VectorComparisonPerElement_Less<4>(Vector2f(0.0f, 5.0f), Vector4<float>(5.0f, 5.0f, 1.0f, 0.0f));
	constexpr Vector4<bool> check_less_equal_v4 = EmuMath::Helpers::VectorComparisonPerElement_LessEqual<4>(Vector2f(0.0f, 5.0f), Vector4<float>(5.0f, 5.0f, 1.0f, 0.0f));
	constexpr Vector4<bool> check_greater_v4 = EmuMath::Helpers::VectorComparisonPerElement_Greater<4>(Vector2f(0.0f, 5.0f), Vector4<float>(5.0f, 5.0f, 1.0f, 0.0f));
	constexpr Vector4<bool> check_greater_equal_v4 = EmuMath::Helpers::VectorComparisonPerElement_GreaterEqual<4>(Vector2f(0.0f, 5.0f), Vector4<float>(5.0f, 5.0f, 1.0f, 0.0f));

	constexpr bool result_all_equal_ = EmuMath::Helpers::VectorComparisonAll_Equal<true>(Vector2<float>(2.5f, 2.5f), 2.5f);
	constexpr bool result_all_not_equal = EmuMath::Helpers::VectorComparisonAll_NotEqual<true>(Vector2<float>(2.5f, 2.5f), 2.1f);
	constexpr bool result_all_less = EmuMath::Helpers::VectorComparisonAll_Less<true>(Vector2<float>(2.5f, 2.5f), 2.6f);
	constexpr bool result_all_less_equal = EmuMath::Helpers::VectorComparisonAll_LessEqual<true>(Vector2<float>(2.5f, 2.5f), 2.5f);
	constexpr bool result_all_greater = EmuMath::Helpers::VectorComparisonAll_Greater<true>(Vector2<float>(2.5f, 2.6f), 2.4f);
	constexpr bool result_all_greater_equal = EmuMath::Helpers::VectorComparisonAll_GreaterEqual<true>(Vector2<float>(2.5f, 2.6f), 2.5f);


	constexpr bool result_any_equal_ = EmuMath::Helpers::VectorComparisonAny_Equal<true>(Vector2<float>(2.5f, 2.99f), 2.5f);
	constexpr bool result_any_not_equal = EmuMath::Helpers::VectorComparisonAny_NotEqual<true>(Vector2<float>(2.5f, 2.1f), 2.5f);
	constexpr bool result_any_less = EmuMath::Helpers::VectorComparisonAny_Less<true>(Vector2<float>(2.5f, 2.4f), 2.5f);
	constexpr bool result_any_less_equal = EmuMath::Helpers::VectorComparisonAny_LessEqual<true>(Vector2<float>(2.5f, 2.2f), 2.4f);
	constexpr bool result_any_greater = EmuMath::Helpers::VectorComparisonAny_Greater<true>(Vector2<float>(2.5f, 2.6f), 2.55f);
	constexpr bool result_any_greater_equal = EmuMath::Helpers::VectorComparisonAny_GreaterEqual<true>(Vector2<float>(2.5f, 2.6f), 2.6f);

	constexpr Vector4<float> shuffled_ = EmuMath::Helpers::VectorShuffle<1, 3, 2, 0, float>(Vector4<int>(1, 2, 3, 4));

	constexpr float some_val_ = 5.0f;
	auto made_vector_ = EmuMath::TMPHelpers::make_emu_vector<const float&>(some_val_, some_val_);
	std::cout << made_vector_ << "\n";
	constexpr auto hi = v2f.Reciprocal();

	constexpr float total_add_ = EmuMath::Helpers::VectorTotalSum<float>(Vector4<float>(5.0f, -27.0f, 3.1f, 27.0f));
	constexpr float total_mult_ = EmuMath::Helpers::VectorTotalProduct<float>(Vector4<float>(5.0f, -27.0f, 3.1f, 27.0f));

	constexpr Vector4<std::uint32_t> normal_vec_ = { 1, std::numeric_limits<std::uint32_t>::max(), 17, 198759823 };
	constexpr Vector4<std::int64_t> reverse_vec_ = EmuMath::Helpers::VectorReverse<4, std::int64_t>(normal_vec_);

#pragma region TEST_HARNESS_EXECUTION
	EmuCore::TestingHelpers::PerformTests();
#pragma endregion
	return 0;
}