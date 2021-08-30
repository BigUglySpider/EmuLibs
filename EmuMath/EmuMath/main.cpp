#include "EmuMath/Vector.h"
#include "EmuMath/FastVector.h"
#include "EmuMath/Matrix.h"
#include "EmuMath/NoOverflowT.h"
#include "EmuCore/TMPHelpers/Tuples.h"
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

int main()
{
	srand(static_cast<unsigned int>(time(0)));

	EmuMath::Vector<4, double> _1(4.0f, 5.0f, 6.0f, 37.0f);

	EmuMath::Matrix<4, 4, float, true> matrix_
	(
		EmuMath::Vector4<float>(0.0f, 1.0f, 2.0f, 3.0f),
		std::move(_1),
		EmuMath::Vector4<std::uint8_t>(8.0f, 9.0f, 10.0f, 11.0f),
		EmuMath::Vector4<std::uint64_t>(12.0f, 13.0f, 14.0f, 15.0f)
	);


	std::cout << matrix_ << "\n";
	std::cout << "[2]: " << matrix_[2] << "\n";
	std::cout << "[7]: " << matrix_[7] << "\n";
	std::cout << "[13]: " << matrix_[13] << "\n";
	std::cout << "[15]: " << matrix_[15] << "\n";
	std::cout << "Column 3: " << matrix_.GetColumn<3>() << "\n";
	std::cout << "Row 2: " << matrix_.GetRow<2>() << "\n";
	
	std::cout << matrix_ << "\n";

	using test_type = EmuCore::TMPHelpers::tuple_n<10, float>::type;

	constexpr auto vec_ = (EmuMath::Vector<10, float>(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f));;
	constexpr test_type tuple_ = EmuMath::Helpers::VectorAsTuple(vec_);
	std::cout << std::get<0>(tuple_) << "\n";

	constexpr auto column_ = EmuMath::Helpers::VectorToColumnMatrix<true>(vec_);
	constexpr auto row_ = EmuMath::Helpers::VectorToRowMatrix<true>(vec_);
	std::cout << column_ << "\n";
	std::cout << row_ << "\n";

	//constexpr auto ColumnVector_ = EmuMath::Helpers::VectorToColumnMatrix<float, false>(EmuMath::Vector<12, float>(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12));

#pragma region TEST_HARNESS_EXECUTION
	system("pause");
	EmuCore::TestingHelpers::PerformTests();
#pragma endregion
	return 0;
}
