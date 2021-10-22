#include "EmuCore/Functors/Analytics.h"
#include "EmuMath/Noise.h"
#include "EmuMath/Random.h"

#include "EmuMath/Colour.h"

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

template<std::size_t num_dimensions, typename FP_>
inline void WriteNoiseTableToPPM(const EmuMath::NoiseTable<num_dimensions, FP_>& noise_table_)
{
	EmuMath::Vector3<FP_> white_(255.0f, 255.0f, 255.0f);

	if constexpr (num_dimensions == 3)
	{
		EmuMath::Vector3<std::size_t> resolution_ = noise_table_.size();
		for (std::size_t z = 0; z < resolution_.z; ++z)
		{
			std::cout << "\nOutputting image layer #" << z << "...\n";

			std::ostringstream name_;
			name_ << "./test_noise_" << z << ".ppm";
			std::ofstream out_ppm_(name_.str(), std::ios_base::out | std::ios_base::binary);
			out_ppm_ << "P6" << std::endl << resolution_.x << ' ' << resolution_.y << std::endl << "255" << std::endl;

			for (std::size_t y = 0; y < resolution_.y; ++y)
			{
				for (std::size_t x = 0; x < resolution_.x; ++x)
				{
					// Clamp is merely to cancel out fp-rounding errors
					EmuMath::Vector<3, std::uint8_t> colour_byte_(white_.Multiply(noise_table_.at(x, y, z)).Clamp(0.0f, 255.0f));
					out_ppm_ << (char)colour_byte_.x << (char)colour_byte_.y << (char)colour_byte_.z;
				}
			}
			out_ppm_.close();
		}
		std::cout << "Finished outputting all 3D noise layers.\n";
	}
	else if constexpr (num_dimensions == 2)
	{
		std::cout << "\nOutputting image...\n";

		std::ostringstream name_;
		name_ << "./2d_test_noise_.ppm";
		std::ofstream out_ppm_(name_.str(), std::ios_base::out | std::ios_base::binary);
		out_ppm_ << "P6" << std::endl << noise_table_.size<0>() << ' ' << noise_table_.size<1>() << std::endl << "255" << std::endl;

		for (std::size_t y = 0, end_y = noise_table_.size<1>(); y < end_y; ++y)
		{
			for (std::size_t x = 0, end_x = noise_table_.size<0>(); x < end_x; ++x)
			{
				// Clamp is merely to cancel out fp-rounding errors
				EmuMath::Vector<3, std::uint8_t> colour_byte_(white_.Multiply(noise_table_.at(x, y)).Clamp(0.0f, 255.0f));
				out_ppm_ << (char)colour_byte_.x << (char)colour_byte_.y << (char)colour_byte_.z;
			}
		}
		out_ppm_.close();
		std::cout << "Finished outputting 2D noise layer.\n";
	}
}

int main()
{
	srand(static_cast<unsigned int>(time(0)));

	constexpr EmuMath::ColourRGB<float> colour_(-0.2f, 2.5, 2.0f);
	constexpr auto wrapped_ = colour_.Wrapped<std::uint8_t, true>();
	constexpr auto clamped_ = colour_.Clamped<std::uint8_t, true>();

	constexpr EmuMath::ColourRGB<float> white_(1.0f, 1.0f, 1.0f);
	constexpr EmuMath::ColourRGB<float> black_(0.0f, 0.0f, 0.0f);
	constexpr auto white_lerp_black_ = white_.Lerp(black_, 0.5f);

	constexpr auto colour_a_ = EmuMath::ColourRGBA<double>(0.8, 1.0, 0.5, 1.0);
	constexpr auto colour_b_ = EmuMath::ColourRGBA<std::uint8_t>(0, 255 / 2, 255 / 4, 255);
	constexpr auto colour_c_ = EmuMath::ColourRGBA<std::uint8_t>(255, 0, 255 / 2, 255 / 4);
	constexpr auto vector_a_ = EmuMath::Vector<2, double>(0.5, 0.25);
	constexpr auto lerp_a_ = colour_a_.Lerp(colour_b_, 0.5f);
	constexpr auto lerp_b_ = colour_a_.Lerp(colour_b_, colour_c_);
	constexpr auto lerp_c_ = colour_a_.Lerp(colour_b_, vector_a_);

	EmuMath::ColourRGBA<float> runtime_rgba_f_(0.1f, -0.1f, 1.0f, 1.5f);
	std::cout << runtime_rgba_f_ << "\n";
	runtime_rgba_f_.Wrap();
	std::cout << runtime_rgba_f_ << "\n";
	runtime_rgba_f_ *= 0.5f;
	std::cout << runtime_rgba_f_ << "\n";
	runtime_rgba_f_ += 0.1;
	std::cout << runtime_rgba_f_ << "\n";
	runtime_rgba_f_ -= 0.1;
	std::cout << runtime_rgba_f_ << "\n";
	runtime_rgba_f_ /= 2;
	std::cout << runtime_rgba_f_ << "\n";
	std::cout << (runtime_rgba_f_ == runtime_rgba_f_) << "\n";
	std::cout << (runtime_rgba_f_ != runtime_rgba_f_) << "\n";

	constexpr EmuMath::ColourRGB<float> from_rgba_ = EmuMath::ColourRGBA<float>(1, 2, 3, 4);



#pragma region TEST_HARNESS_EXECUTION
	system("pause");
	EmuCore::TestingHelpers::PerformTests();
#pragma endregion
	return 0;
}
