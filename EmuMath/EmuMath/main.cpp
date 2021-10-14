#include "EmuMath/Noise.h"

#include "EmuMath/Random.h"

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

	EmuMath::NoiseTable<float> noise;
	EmuMath::RngWrapper<true> rng_64(2, 5);
	EmuMath::RngWrapper<false> rng_32(2, 5);

	std::cout << rng_32.NextInt() << " | " << rng_32.NextInt<unsigned short>() << " | " << rng_32.NextInt<std::int64_t>(0, 100) << " | " << rng_32.NextReal() << " | " << rng_32.NextReal<long double>() << "\n";
	std::cout << rng_64.NextInt() << " | " << rng_64.NextInt<unsigned short>() << " | " << rng_64.NextInt<std::int64_t>(0, 100) << " | " << rng_64.NextReal() << " | " << rng_64.NextReal<long double>() << "\n";

	EmuMath::ShuffledIntSequence perms_(33, true);
	std::cout << perms_ << "\n";
	for (std::size_t i = 0; i < perms_.size() + 1; ++i)
	{
		std::cout << (perms_ << i) << "\n";
	}
	std::cout << "\n\n";
	for (std::size_t i = 0; i < perms_.size() + 1; ++i)
	{
		std::cout << (perms_ >> i) << "\n";
	}
	perms_.TryShortenToPowerOf2(true);
	std::cout << perms_ << " | " << perms_.size() << " | " << perms_.MaxValue() << "\n";
	perms_.resize(33);
	perms_.TryIncreaseToPowerOf2(true);
	std::cout << perms_ << " | " << perms_.size() << " | " << perms_.MaxValue() << "\n";

	std::cout << EmuMath::Functors::make_noise_1d<EmuMath::NoiseType::PERLIN_SMOOTH>()(23.175f, 0.675f, EmuMath::ShuffledIntSequence<std::int32_t>(128, 2u)) << "\n";
	std::cout << EmuMath::Functors::make_noise_1d<EmuMath::NoiseType::PERLIN_SMOOTH>()(23.575f, 0.675f, EmuMath::ShuffledIntSequence<std::int32_t>(128, 2u)) << "\n";

#pragma region TEST_HARNESS_EXECUTION
	system("pause");
	EmuCore::TestingHelpers::PerformTests();
#pragma endregion
	return 0;
}
