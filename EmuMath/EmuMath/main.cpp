#include "Tests.hpp"

#include "EmuMath/GeneralMath.h"
#include "EmuMath/NoOverflowT.h"
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
	constexpr EmuMath::Vector<3, float> v3f(std::numeric_limits<std::uint64_t>::max(), 2.0f, double(-2255));
	std::cout << v3f << std::endl;

	constexpr auto shuffled = EmuMath::Helpers::VectorShuffle<double, 2, 1, 0, 0, 0, 1, 1, 2, 2, 1, 0, 1>(v3f);
	constexpr auto shuffled_without_type_arg = EmuMath::Helpers::VectorShuffle<1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 0, 0, 0, 0, 1>(v3f);
	std::cout << shuffled << "\n";

	EmuMath::Vector<4, double> a(1.0, 2.0, 3.0, 4.0);
	EmuMath::Vector<3, int> b(5, -6, 7);

	std::cout << "Before:\nA: " << a << "\nB: " << b << "\n";
	EmuMath::Vector<4, int> temp_v4si = a;
	a.Copy(b);
	b.Copy(temp_v4si);
	std::cout << "After:\nA: " << a << "\nB: " << b << "\n";
	std::cout << "a[2]: " << EmuMath::Helpers::VectorGet<2>(a) << " | " << EmuMath::Helpers::VectorGet(a, 2) << "\n";
	a.at<3>() = 4.0;


	std::cout << "Total product of " << a << ": " << EmuMath::Helpers::VectorElementProduct(a) << "\n";
	std::cout << "Total sum of " << a << ": " << EmuMath::Helpers::VectorElementSum(a) << "\n";


	std::cout << a << " + " << b << ": " << EmuMath::Helpers::VectorAdd<2, long double>(a, b) << "\n";
	std::cout << a << " + " << b << ": " << EmuMath::Helpers::VectorAdd(a, b) << "\n";
	std::cout << a << " + " << b << ": " << EmuMath::Helpers::VectorAdd<12>(a, b) << "\n";
	std::cout << b << " + " << a << ": " << EmuMath::Helpers::VectorAdd<12>(b, a) << "\n";
	std::cout << b << " + " << a << ": " << EmuMath::Helpers::VectorAdd(b, a) << "\n";

	const float c = 3.0f;
	std::cout << a << " x " << b << ": " << EmuMath::Helpers::VectorMultiply(a, b) << "\n";
	std::cout << a << " x " << c << ": " << EmuMath::Helpers::VectorMultiply(a, c) << "\n";


	std::cout << a << " / " << b << ": " << EmuMath::Helpers::VectorDivide(a, b) << "\n";
	std::cout << a << " / " << c << ": " << EmuMath::Helpers::VectorDivide(a, c) << "\n";

	constexpr EmuMath::Vector<3, int> d(0, -7, 23);
	constexpr EmuMath::Vector<4, float> e(1.0f, 0.0f, 3.0f, 2.0f);
	auto result_ = EmuMath::Helpers::VectorDivide<5, float>(d, e);
	std::cout << d << " / " << e << ": " << EmuMath::Helpers::VectorDivide<5, float>(d, e) << "\n";
	std::cout << d << " DOT " << e << ": " << EmuMath::Helpers::VectorDotProduct(d, e) << "\n";

	constexpr double dMag = EmuMath::Helpers::VectorMagnitudeConstexpr<double>(d);
	std::cout << EmuMath::Helpers::VectorMagnitude(d) << "\n";

	system("pause");

#pragma region TEST_HARNESS_EXECUTION
	EmuCore::TestingHelpers::PerformTests();
#pragma endregion
	return 0;
}