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

	constexpr EmuMath::Vector<4, int> d(0, -7, 23, 2);
	constexpr EmuMath::Vector<4, float> e(1.0f, 0.0f, 3.0f, 2.0f);
	auto result_ = EmuMath::Helpers::VectorDivide<5, float>(d, e);
	std::cout << d << " / " << e << ": " << EmuMath::Helpers::VectorDivide<5, float>(d, e) << "\n";
	std::cout << d << " DOT " << e << ": " << EmuMath::Helpers::VectorDotProduct(d, e) << "\n";

	constexpr double dSqrMag = EmuMath::Helpers::VectorSquareMagnitude<double>(d);
	constexpr double dMag = EmuMath::Helpers::VectorMagnitudeConstexpr<double>(d);

	std::cout << d << " == " << e << ": " << EmuMath::Helpers::VectorPerElementCmpEqualTo(d, e) << "\n";
	std::cout << d << " != " << e << ": " << EmuMath::Helpers::VectorPerElementCmpNotEqualTo(d, e) << "\n";
	std::cout << d << " < " << e << ": " << EmuMath::Helpers::VectorPerElementCmpLess(d, e) << "\n";
	std::cout << d << " > " << e << ": " << EmuMath::Helpers::VectorPerElementCmpGreater(d, e) << "\n";
	std::cout << d << " <= " << e << ": " << EmuMath::Helpers::VectorPerElementCmpLessEqual(d, e) << "\n";
	std::cout << d << " >= " << e << ": " << EmuMath::Helpers::VectorPerElementCmpGreaterEqual(d, e) << "\n";

	std::cout << "MIN(" << d << "): " << EmuMath::Helpers::VectorMin(d) << "\n";
	std::cout << "MAX(" << d << "): " << EmuMath::Helpers::VectorMax(d) << "\n";
	std::cout << "MINMAX(" << d << "): " << EmuMath::Helpers::VectorMinMax(d) << "\n";
	std::cout << "MINMAX(" << d << ", min&, max&): ";
	int min_ = 0, max_ = 0;
	EmuMath::Helpers::VectorMinMax(d, min_, max_);
	std::cout << "(" << min_ << ", " << max_ << ")\n";

	std::cout << "MinIndex(" << d << "): " << EmuMath::Helpers::VectorMinIndex(d) << "\n";
	std::cout << "MaxIndex(" << d << "): " << EmuMath::Helpers::VectorMaxIndex(d) << "\n";
	std::cout << "MinMaxIndices(" << d << "): " << EmuMath::Helpers::VectorMinMaxIndices(d) << "\n";
	std::cout << "MinMaxIndices(" << d << ", min&, max&): ";
	std::size_t minIndex_ = 0, maxIndex_ = 0;
	EmuMath::Helpers::VectorMinMaxIndices(d, minIndex_, maxIndex_);
	std::cout << "(" << minIndex_ << ", " << maxIndex_ << ")\n";

	std::cout << EmuMath::Helpers::VectorMagnitude(d) << "\n";

	constexpr EmuMath::Vector<7, double> a_(1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0);
	constexpr float b_ = 25.0f;
	constexpr std::uint32_t c_ = 100;
	constexpr EmuMath::Vector<5, double> d_(5.0, 4.0, 3.0, 2.0, 1.0);
	constexpr float u_ = 0.5f;
	constexpr EmuMath::Vector<10, float> v_(0.1f, 0.2f, 0.3f, 0.4f, 0.5f, 0.6f, 0.7f, 0.8f, 0.9f, 1.0f);

	std::cout << "\nBLERP(" << a_ << ", " << b_ << ", " << c_ << ", " << d_ << ", " << u_ << ", " << v_ << "): " << EmuMath::Helpers::VectorBlerp(a_, b_, c_, d_, u_, v_) << "\n";

	constexpr auto blerped = EmuMath::Helpers::VectorBlerp(a_, b_, c_, d_, u_, v_);
	constexpr auto half_doubled_blerp = EmuMath::Helpers::VectorLerp<3, float>(blerped, EmuMath::Helpers::VectorMultiply(blerped, 2.0f), 0.5f);

	std::cout << "do_lerp(0, 10, 0.5): " << EmuMath::do_lerp<void>()(0, 10, 0.5) << "\n";
	using V2f = EmuMath::Vector<2, float>;
	using V2si32 = EmuMath::Vector<2, std::int32_t>;
	std::cout << "do_lerp({0, 100}, {100, 0}, {0.5, 0.25}): " << EmuMath::do_lerp<void>()(V2si32(0, 100), V2si32(100, 0), V2f(0.5f, 0.25f)) << "\n";
	std::cout << "Reciprocal(" << d << "): " << EmuMath::Helpers::VectorReciprocal(d) << "\n";

	system("pause");

#pragma region TEST_HARNESS_EXECUTION
	EmuCore::TestingHelpers::PerformTests();
#pragma endregion
	return 0;
}