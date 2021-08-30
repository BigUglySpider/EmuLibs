#include "EmuMath/Vector.h"
#include "EmuMath/FastVector.h"
#include "EmuMath/Matrix.h"
#include "EmuMath/NoOverflowT.h"
#include <array>
#include <bitset>
#include <iomanip>

#include "Tests.hpp"
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

bool boolfunc(bool bool_)
{
	return bool(bool_);
}

int main()
{
	srand(static_cast<unsigned int>(time(0)));

	EmuMath::Matrix<4, 4, float, true> matrix_
	(
		EmuMath::Vector4<float>(0.0f, 1.0f, 2.0f, 3.0f),
		EmuMath::Vector4<double>(4.0f, 5.0f, 6.0f, 7.0f),
		EmuMath::Vector4<std::uint8_t>(8.0f, 9.0f, 10.0f, 11.0f),
		EmuMath::Vector4<std::uint64_t>(12.0f, 13.0f, 14.0f, 15.0f)
	);

	std::cout << matrix_ << "\n";

#pragma region TEST_HARNESS_EXECUTION
	system("pause");
	EmuCore::TestingHelpers::PerformTests();
#pragma endregion
	return 0;
}
