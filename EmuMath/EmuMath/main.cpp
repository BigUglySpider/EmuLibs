#include "Tests.hpp"

#include "EmuMath/GeneralMath.h"
#include "EmuMath/NoOverflowT.h"
#include "EmuMath/Vectors.h"
#include <array>

using namespace EmuCore::TestingHelpers;
using namespace EmuMath;

int main()
{
	constexpr NoOverflowT<std::int32_t> no_overflow_si32_pos = 25;
	constexpr NoOverflowT<std::int32_t> no_overflow_si32_neg = -no_overflow_si32_pos;
	constexpr float to_add = static_cast<float>(std::numeric_limits<std::int16_t>::max());
	constexpr double to_sub = static_cast<double>(to_add);
	constexpr float flt_max = std::numeric_limits<float>::max();

	constexpr NoOverflowT<std::int32_t> add_pos_pos = no_overflow_si32_pos + to_add;
	constexpr NoOverflowT<std::int32_t> add_pos_neg = no_overflow_si32_pos + -to_add;
	constexpr NoOverflowT<std::int32_t> add_neg_pos = no_overflow_si32_neg + to_add;
	constexpr NoOverflowT<std::int32_t> add_neg_neg = no_overflow_si32_neg + -to_add;

	constexpr NoOverflowT<std::int16_t> add_signed_pos_pos_overflow = no_overflow_si32_pos + flt_max;
	constexpr NoOverflowT<std::int16_t> add_signed_pos_neg_overflow = no_overflow_si32_pos + -flt_max;
	constexpr NoOverflowT<std::int16_t> add_signed_neg_pos_overflow = no_overflow_si32_neg + flt_max;
	constexpr NoOverflowT<std::int16_t> add_signed_neg_neg_overflow = no_overflow_si32_neg + -flt_max;

	constexpr std::uint16_t to_add_ui16 = std::numeric_limits<std::uint16_t>::max();

	constexpr NoOverflowT<std::int32_t> add_signed_pos_unsigned= no_overflow_si32_pos + to_add_ui16;
	constexpr NoOverflowT<std::int32_t> add_signed_neg_unsigned = no_overflow_si32_neg + to_add_ui16;

	constexpr std::uint32_t to_add_ui32 = std::numeric_limits<std::uint32_t>::max();

	constexpr NoOverflowT<std::int32_t> add_signed_pos_unsigned_overflow = no_overflow_si32_pos + to_add_ui32;
	constexpr NoOverflowT<std::int32_t> add_signed_neg_unsigned_overflow = no_overflow_si32_neg + to_add_ui32;

	constexpr NoOverflowT<std::int32_t> overflown_positive_negated = -add_signed_pos_unsigned_overflow;
	constexpr std::int64_t overflown_unsigned_negated = -NoOverflowT<std::uint32_t>(NoOverflowT<std::uint32_t>::max_val);

	constexpr NoOverflowT<std::int32_t> sub_pos_pos = no_overflow_si32_pos - to_sub;
	constexpr NoOverflowT<std::int32_t> sub_pos_neg = no_overflow_si32_pos - -to_sub;
	constexpr NoOverflowT<std::int32_t> sub_neg_pos = no_overflow_si32_neg - to_sub;
	constexpr NoOverflowT<std::int32_t> sub_neg_neg = no_overflow_si32_neg - -to_sub;

	constexpr NoOverflowT<std::int16_t> sub_signed_pos_pos_overflow = no_overflow_si32_pos - flt_max;
	constexpr NoOverflowT<std::int16_t> sub_signed_pos_neg_overflow = no_overflow_si32_pos - -flt_max;
	constexpr NoOverflowT<std::int16_t> sub_signed_neg_pos_overflow = no_overflow_si32_neg - flt_max;
	constexpr NoOverflowT<std::int16_t> sub_signed_neg_neg_overflow = no_overflow_si32_neg - -flt_max;

	constexpr std::uint16_t to_sub_ui16 = std::numeric_limits<std::uint16_t>::max();

	constexpr NoOverflowT<std::int32_t> sub_signed_pos_unsigned = no_overflow_si32_pos - to_sub_ui16;
	constexpr NoOverflowT<std::int32_t> sub_signed_neg_unsigned = no_overflow_si32_neg - to_sub_ui16;

	constexpr std::uint32_t to_sub_ui32 = std::numeric_limits<std::uint32_t>::max();

	constexpr NoOverflowT<std::int32_t> sub_signed_pos_unsigned_overflow = no_overflow_si32_pos - to_sub_ui32;
	constexpr NoOverflowT<std::int32_t> sub_signed_neg_unsigned_overflow = no_overflow_si32_neg - to_sub_ui32;

#pragma region TEST_HARNESS_EXECUTION
	EmuCore::TestingHelpers::PerformTests();
#pragma endregion
	return 0;
}