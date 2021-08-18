#include "Tests.hpp"

#include "EmuMath/Vector.h"
#include <array>
#include <bitset>
#include <iomanip>

using namespace EmuCore::TestingHelpers;

template<typename T_>
using simple_bitset = std::bitset<sizeof(T_) * CHAR_BIT>;

template<typename T_, std::size_t Size_>
inline std::ostream& operator<<(std::ostream& stream_, const std::array<T_, Size_>& arr_)
{
	std::ostringstream str;
	str << "{ ";
	str << arr_[0];
	for (std::size_t i = 1; i < Size_; ++i)
	{
		str << ", " << arr_[i];
	}
	str << " }";
	stream_ << str.str();
	return stream_;
}

template<typename T_, int Max_ = std::numeric_limits<int>::max()>
struct SettyBoi
{
	SettyBoi() : SettyBoi(static_cast<unsigned int>(time(0)))
	{
	}
	SettyBoi(unsigned int seed_)
	{
		srand(seed_);
	}

	T_ operator()() const
	{
		return T_(rand() % Max_);
	}
	T_ operator()(const std::size_t x_, const std::size_t y_) const
	{
		return T_(rand() % (x_ + y_ + 1));
	}
};

int main()
{
	srand(static_cast<unsigned int>(time(0)));

	auto vectorf = EmuMath::TMP::make_emu_vector<float>(1.0f);
	auto vectord = EmuMath::TMP::make_emu_vector<double>(1.0, 3.0, 5.0, 6.5, 21.345);

	auto ref_d_ = EmuMath::Helpers::VectorShuffledReference<4, 3, 2, 1, 0>(vectord);
	std::cout << "D: " << vectord << "\nRef: " << ref_d_ << "\n";
	ref_d_.at<2>() = 255.0;
	ref_d_.at<0>() = std::numeric_limits<double>::infinity();
	std::cout << "D: " << vectord << "\nRef: " << ref_d_ << "\n";


	EmuMath::Helpers::VectorSet(ref_d_, EmuMath::Helpers::VectorFloor(EmuMath::Helpers::VectorNegate(ref_d_)));
	std::cout << "D: " << vectord << "\nRef: " << ref_d_ << "\n";

	auto some_vector = EmuMath::TMP::make_emu_vector<float>(102, 13.0f, 27.6, 100, 10000, 1000000);
	std::cout << "Sqrt(" << some_vector << "): " << EmuMath::Helpers::VectorSqrt(some_vector) << "\n";
	constexpr auto some_other_vector = EmuMath::TMP::make_emu_vector<double>(100.0, 0.25, 1.0f, 2.0f, EmuCore::Pi::PI<long double>);
	constexpr auto some_other_vector_sqrt = EmuMath::Helpers::VectorSqrtConstexpr(some_other_vector);
	std::cout << "SqrtConstexpr(" << some_other_vector << "): " << some_other_vector_sqrt << "\n";

	constexpr auto some_uint_vector = EmuMath::TMP::make_emu_vector<std::uint32_t>(1, 2, 4, 8, 16, 32, 64, 128);
	constexpr auto shifted_left_uint_vector = EmuMath::Helpers::VectorShiftLeft(some_uint_vector, 1);
	constexpr auto shifted_right_uint_vector = EmuMath::Helpers::VectorShiftRight(some_uint_vector, float(2));
	constexpr auto shifted_left_vector_shifts = EmuMath::Helpers::VectorShiftLeft(some_uint_vector, EmuMath::TMP::make_emu_vector<float>(1, 2, 3, 4, 5, 6, 7, 8));
	constexpr auto shifted_right_vector_shifts = EmuMath::Helpers::VectorShiftRight(some_uint_vector, EmuMath::TMP::make_emu_vector<float>(1, 1, 1, 1, 5));

	constexpr auto vec_a = EmuMath::TMP::make_emu_vector<float>(1.0f, 2.0f, 3.0f);
	constexpr auto vec_b = EmuMath::TMP::make_emu_vector<std::uint64_t>(1, 2, 3);
	constexpr auto vec_c = EmuMath::TMP::make_emu_vector<float>(1.1f, 2.2f, 3.0f);
	auto vec_d = EmuMath::Helpers::VectorShuffledReference<0, 1, 2, 0>(vec_a);
	auto vec_e = EmuMath::Vector<10, double>(vec_d);
	std::cout << vec_e << "\n";


	// NOTE: TESTING EmuMath::VectorCmpEqualTo
	std::cout << vec_a << " == " << vec_b << ": " << EmuMath::Helpers::VectorCmpEqualTo(vec_a, vec_b) << "\n";
	std::cout << vec_b << " == " << vec_c << ": " << EmuMath::Helpers::VectorCmpEqualTo(vec_b, vec_c) << "\n";
	std::cout << vec_a << " == " << vec_d << ": " << EmuMath::Helpers::VectorCmpEqualTo(vec_a, vec_d) << "\n";
	std::cout << vec_a << " == " << vec_d << " (Don't include non-contained): " << EmuMath::Helpers::VectorCmpEqualTo<false>(vec_a, vec_d) << "\n";
	std::cout << "----------\n";


	std::cout << vec_a << " != " << vec_b << ": " << EmuMath::Helpers::VectorCmpNotEqualTo(vec_a, vec_b) << "\n";
	std::cout << vec_b << " != " << vec_c << ": " << EmuMath::Helpers::VectorCmpNotEqualTo(vec_b, vec_c) << "\n";
	std::cout << vec_a << " != " << vec_d << ": " << EmuMath::Helpers::VectorCmpNotEqualTo(vec_a, vec_d) << "\n";
	std::cout << vec_a << " != " << vec_d << " (Don't include non-contained): " << EmuMath::Helpers::VectorCmpNotEqualTo<false>(vec_a, vec_d) << "\n";
	std::cout << "----------\n";


	constexpr auto vec_a_sqr_mag_ = EmuMath::Helpers::VectorSquareMagnitude<float>(vec_a);
	constexpr auto vec_a_mag_ = EmuMath::Helpers::VectorMagnitudeConstexpr<float>(vec_a);
	constexpr auto vec_a_mag_mult_vec_a_mag_ = vec_a_mag_ * vec_a_mag_;
	std::cout << vec_a << " == " << EmuMath::Helpers::VectorMagnitude(vec_a) << ": " << EmuMath::Helpers::VectorCmpEqualTo(vec_a, vec_a_mag_) << "\n";
	std::cout << vec_b << " == " << 2 << ": " << EmuMath::Helpers::VectorCmpEqualTo(vec_b, 2) << "\n";
	std::cout << vec_a << " == " << 5 << ": " << EmuMath::Helpers::VectorCmpEqualTo(vec_a, 5) << "\n";
	std::cout << vec_a << " == " << 4 << " (Don't include non-contained): " << EmuMath::Helpers::VectorCmpEqualTo<false>(vec_a, 4) << "\n";
	std::cout << "----------\n";


	std::cout << vec_a << " ALL == " << vec_b << ": " << EmuMath::Helpers::VectorCmpAllEqualTo(vec_a, vec_b) << "\n";
	std::cout << vec_b << " ALL != " << vec_c << ": " << EmuMath::Helpers::VectorCmpAllNotEqualTo(vec_b, std::uint64_t(2)) << "\n";
	std::cout << vec_a << " ALL <= " << vec_d << ": " << EmuMath::Helpers::VectorCmpAllLessEqual(vec_a, vec_d) << "\n";
	std::cout << vec_a << " ALL > " << vec_a << " (Don't include non-contained): " << EmuMath::Helpers::VectorCmpAllGreater<false>(vec_a, vec_a) << "\n";
	std::cout << vec_a << " ALL == " << EmuMath::Helpers::VectorShuffle<0, 1, 2, 2, 1, 0>(vec_a) << " (Don't include non-contained): " << EmuMath::Helpers::VectorCmpAllEqualTo<false>(vec_a, EmuMath::Helpers::VectorShuffle<0, 1, 2, 2, 1, 0>(vec_a)) << "\n";
	std::cout << vec_a << " ALL == " << EmuMath::Helpers::VectorShuffle<0, 1>(vec_a) << " (Don't include non-contained): " << EmuMath::Helpers::VectorCmpAllEqualTo<false>(vec_a, EmuMath::Helpers::VectorShuffle<0, 1>(vec_a)) << "\n";
	std::cout << "----------\n";


	std::cout << vec_a << " ANY == " << vec_b << ": " << EmuMath::Helpers::VectorCmpAnyEqualTo(vec_a, vec_b) << "\n";
	std::cout << vec_b << " ANY != " << std::uint64_t(2) << ": " << EmuMath::Helpers::VectorCmpAnyNotEqualTo(vec_b, std::uint64_t(2)) << "\n";
	std::cout << vec_a << " ANY <= " << vec_a << ": " << EmuMath::Helpers::VectorCmpAnyLessEqual(vec_a, vec_a) << "\n";
	std::cout << vec_a << " ANY > " << vec_a << " (Don't include non-contained): " << EmuMath::Helpers::VectorCmpAnyGreater<false>(vec_a, vec_a) << "\n";
	std::cout << vec_a << " ANY < " << EmuMath::Helpers::VectorShuffle<2, 1, 0>(vec_a) << " (Don't include non-contained): " << EmuMath::Helpers::VectorCmpAnyLess<false>(vec_a, EmuMath::Helpers::VectorShuffle<2, 1, 0>(vec_a)) << "\n";
	std::cout << "----------\n";

	constexpr auto vec_a_mag_recip_constexpr = EmuMath::Helpers::VectorMagnitudeReciprocalConstexpr(vec_a);
	std::cout << "MagRecipConstexpr(" << vec_a << "): " << vec_a_mag_recip_constexpr << "\n";
	std::cout << "MagRecipQrsqrt(" << vec_a << "): " << EmuMath::Helpers::VectorMagnitudeReciprocalQrsqrt<float, 1>(vec_a) << "\n";

	using x_val_type = std::uint16_t;
	using y_val_type = std::uint16_t;
	EmuMath::Vector<4, x_val_type> x_(128, 7, 255, 16);
	EmuMath::Vector<3, y_val_type> y_(128, 6, 231);
	EmuMath::Vector<4, simple_bitset<x_val_type>> x_bits_(x_);
	EmuMath::Vector<3, simple_bitset<y_val_type>> y_bits_(y_);
	std::cout << x_bits_ << " &\n" << y_bits_ << ":\n" << EmuMath::Vector<4, simple_bitset<x_val_type>>(EmuMath::Helpers::VectorAnd(x_, y_)) << "\n\n";
	std::cout << x_bits_ << " |\n" << y_bits_ << ":\n" << EmuMath::Vector<4, simple_bitset<x_val_type>>(EmuMath::Helpers::VectorOr(x_, y_)) << "\n\n";
	std::cout << x_bits_ << " ^\n" << y_bits_ << ":\n" << EmuMath::Vector<4, simple_bitset<x_val_type>>(EmuMath::Helpers::VectorXor(x_, y_)) << "\n\n";
	std::cout << x_bits_ << ".NOT():\n" << EmuMath::Vector<4, simple_bitset<x_val_type>>(EmuMath::Helpers::VectorNot(x_)) << "\n\n";

	x_val_type some_constant_ = 0xE28F;
	std::cout << x_bits_ << " &\n  " << simple_bitset<x_val_type>(some_constant_) << ":\n" << EmuMath::Vector<4, simple_bitset<x_val_type>>(EmuMath::Helpers::VectorAnd(x_, some_constant_)) << "\n\n";
	std::cout << x_bits_ << " |\n  " << simple_bitset<x_val_type>(some_constant_) << ":\n" << EmuMath::Vector<4, simple_bitset<x_val_type>>(EmuMath::Helpers::VectorOr(x_, some_constant_)) << "\n\n";
	std::cout << x_bits_ << " ^\n  " << simple_bitset<x_val_type>(some_constant_) << ":\n" << EmuMath::Vector<4, simple_bitset<x_val_type>>(EmuMath::Helpers::VectorXor(x_, some_constant_)) << "\n\n";

#pragma region TEST_HARNESS_EXECUTION
	system("pause");
	EmuCore::TestingHelpers::PerformTests();
#pragma endregion
	return 0;
}