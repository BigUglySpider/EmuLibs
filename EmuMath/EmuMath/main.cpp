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

	std::cout << EmuMath::Functors::make_noise_1d<EmuMath::NoiseType::PERLIN>()(23.175f, 0.675f, EmuMath::ShuffledIntSequence<std::int32_t>(128, 2u)) << "\n";
	std::cout << EmuMath::Functors::make_noise_1d<EmuMath::NoiseType::PERLIN>()(23.575f, 0.675f, EmuMath::ShuffledIntSequence<std::int32_t>(128, 2u)) << "\n";

	constexpr EmuMath::Vector<3, float> white_(1.0f, 1.0f, 1.0f);
	constexpr EmuMath::Vector<2, float> start_(0.0f, 0.0f);
	constexpr EmuMath::Vector<2, float> end_(1.0f, 1.0f);
	constexpr EmuMath::Vector<3, std::size_t> resolution_(1920, 1080, 0);
	constexpr EmuMath::Vector<2, float> step_ = (end_ - start_) / resolution_;
	constexpr float freq_ = 32.0f;
	constexpr std::size_t num_permutations_ = 1024;
	constexpr EmuMath::NoiseType noise_type_ = EmuMath::NoiseType::PERLIN;
	constexpr bool seed_arg_bool_ = true;
	constexpr std::uint32_t seed_arg_32_ = 25;
	constexpr std::uint64_t seed_arg_64_ = 14154;
	constexpr auto seed_arg_ = seed_arg_64_;
	using noise_generator = EmuMath::Functors::make_noise_2d<noise_type_>;
	using sample_processor = EmuMath::Functors::noise_sample_processor_perlin2d_normalise;

	std::vector<EmuMath::Vector<3, float>> colour_grid_(resolution_.x * resolution_.y);
	EmuMath::Vector<2, float> point_ = start_;
	noise_generator noise_generator_ = noise_generator();
	EmuMath::NoisePermutations permutations(num_permutations_, seed_arg_);
	sample_processor sample_processor_ = sample_processor();

	for (std::size_t y = 0, i = 0; y < resolution_.y; ++y)
	{
		point_.x = start_.x;
		for (std::size_t x = 0; x < resolution_.x; ++x)
		{
			float sample_= noise_generator_(point_, freq_, permutations);
			sample_ = sample_processor_(sample_);
			std::cout << sample_ << "\n";
			colour_grid_[i] = ((white_ * sample_) * 255.0f).Clamp(0.0f, 255.0f); // Clamp instead of fmod since we know we're producing 0:1 range; this is to correct fp errors
			point_.x += step_.x;
			++i;
		}
		point_.y += step_.y;
	}

	std::ofstream out_ppm_("./test_noise.ppm", std::ios_base::out | std::ios_base::binary);
	out_ppm_ << "P6" << std::endl << resolution_.x << ' ' << resolution_.y << std::endl << "255" << std::endl;
	for (std::size_t i = 0, end = colour_grid_.size(); i < end; ++i)
	{
		EmuMath::Vector<3, std::uint8_t> colour_byte_(colour_grid_[i]);
		out_ppm_ << (char) colour_byte_.x << (char) colour_byte_.y << (char) colour_byte_.z;
	}
	out_ppm_.close();

#pragma region TEST_HARNESS_EXECUTION
	system("pause");
	EmuCore::TestingHelpers::PerformTests();
#pragma endregion
	return 0;
}
