#include "Tests.hpp"

#include "EmuMath/Vector.h"
#include <array>
#include <iomanip>

using namespace EmuCore::TestingHelpers;

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
	EmuMath::do_sqrt<void> do_sqrt_;

#pragma region TEST_HARNESS_EXECUTION
	EmuCore::TestingHelpers::PerformTests();
#pragma endregion
	return 0;
}