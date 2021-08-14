#include "Tests.hpp"

#include "EmuMath/GeneralMath.h"
#include "EmuMath/NoOverflowT.h"
#include "EmuMath/Vector.h"
#include <array>
#include <iomanip>

using namespace EmuCore::TestingHelpers;
using namespace EmuMath;

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
	constexpr EmuMath::Vector<3, float> v3f(std::numeric_limits<std::uint64_t>::max(), 2.0f, double(-2255));
	std::cout << v3f << std::endl;

	constexpr auto shuffled = EmuMath::Helpers::VectorShuffle<double, 2, 1, 0, 0, 0, 1, 1, 2, 2, 1, 0, 1>(v3f);
	constexpr auto shuffled_without_type_arg = EmuMath::Helpers::VectorShuffle<1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 0, 0, 0, 0>(v3f);
	std::cout << shuffled << "\n";



	system("pause");

#pragma region TEST_HARNESS_EXECUTION
	EmuCore::TestingHelpers::PerformTests();
#pragma endregion
	return 0;
}