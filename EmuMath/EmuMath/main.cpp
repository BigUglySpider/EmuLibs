#include "EmuMath/Vector.h"
#include "EmuMath/FastVector.h"
#include "EmuMath/Matrix.h"
#include "EmuMath/FastMatrix.h"
#include "EmuMath/NoOverflowT.h"
#include "EmuCore/TMPHelpers/Tuples.h"
#include <array>
#include <bitset>
#include <iomanip>

#include "Tests.hpp"

#include "EmuCore/Events/Event.h"
#include "EmuCore/Events/ThreadSafeEvent.h"

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

template<std::size_t X_, std::size_t Y_, typename Type_, bool ColumnMajor_>
void TestFunc(const EmuMath::Matrix<X_, Y_, Type_, ColumnMajor_>& matrix_)
{
	std::cout << matrix_ << "\n";
}
template<std::size_t X_, std::size_t Y_, typename Type_, bool ColumnMajor_>
void TestFunc(EmuMath::Matrix<X_, Y_, Type_, ColumnMajor_>&& matrix_)
{
	TestFunc(std::forward<EmuMath::Matrix<X_, Y_, Type_, ColumnMajor_>>(matrix_));
}
template<std::size_t FirstX_, std::size_t FirstY_, typename FirstType_, bool FirstColumnMajor_, std::size_t...X_, std::size_t...Y_, typename...Types_, bool...ColumnMajors_>
void TestFunc(const EmuMath::Matrix<FirstX_, FirstY_, FirstType_, FirstColumnMajor_>& first_, const EmuMath::Matrix<X_, Y_, Types_, ColumnMajors_>&...matrices_)
{
	TestFunc(first_);
	TestFunc(matrices_...);
}

void _up(int val_)
{
	std::cout << val_ << "\n";
}
void _down(int val_)
{
	std::cout << -val_ << "\n";
}
float _upf(int val_)
{
	_up(val_);
	return static_cast<float>(val_);
}

struct SomeStructForTestingEdges
{
	template<typename Fov_, typename Near_, typename AspectRatio_>
	constexpr SomeStructForTestingEdges(const Fov_& in_fov_angle_y_, const Near_& in_near_, const AspectRatio_& in_aspect_ratio_) :
		left_(0.0f), right_(0.0f), bottom_(0.0f), top_(0.0f)
	{
		EmuMath::Helpers::MatrixPerspectiveFrustumEdges<false>(in_fov_angle_y_, in_near_, in_aspect_ratio_, left_, right_, bottom_, top_);
	}

	float left_;
	float right_;
	float bottom_;
	float top_;
};

int main()
{
	srand(static_cast<unsigned int>(time(0)));

	EmuMath::FastMatrix4x4f_CM fast_4x4_from_scalars(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
	std::cout << "\n\n";
	std::cout << fast_4x4_from_scalars << "\n";
	std::cout << "Row[0]: " << fast_4x4_from_scalars.GetRowReadable<0>() << "\n";
	std::cout << "Row[1]: " << fast_4x4_from_scalars.GetRowReadable<1>() << "\n";
	std::cout << "Row[2]: " << fast_4x4_from_scalars.GetRowReadable<2>() << "\n";
	std::cout << "Row[3]: " << fast_4x4_from_scalars.GetRowReadable<3>() << "\n";
	std::cout << "Column[0]: " << fast_4x4_from_scalars.GetColumnReadable<0>() << "\n";
	std::cout << "Column[1]: " << fast_4x4_from_scalars.GetColumnReadable<1>() << "\n";
	std::cout << "Column[2]: " << fast_4x4_from_scalars.GetColumnReadable<2>() << "\n";
	std::cout << "Column[3]: " << fast_4x4_from_scalars.GetColumnReadable<3>() << "\n";
	std::cout << "Stored as column-major matrix:\n" << fast_4x4_from_scalars.Store<float, true>() << "\n";
	std::cout << "Stored as row-major matrix:\n" << fast_4x4_from_scalars.Store<float, false>() << "\n";
	std::cout << (fast_4x4_from_scalars != fast_4x4_from_scalars) << " | " << (fast_4x4_from_scalars == fast_4x4_from_scalars) << "\n";
	std::cout << fast_4x4_from_scalars * 2.5L << "\n\n";
	std::cout << fast_4x4_from_scalars.Multiply(fast_4x4_from_scalars) << "\n\n";

#pragma region TEST_HARNESS_EXECUTION
	system("pause");
	EmuCore::TestingHelpers::PerformTests();
#pragma endregion
	return 0;
}
