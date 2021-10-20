#include "EmuCore/Functors/Analytics.h"
#include "EmuMath/Noise.h"
#include "EmuMath/Random.h"

#include "EmuMath/Colours.h"

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

	constexpr EmuMath::ColourRGB<float> colour_ = EmuMath::ColourRGB<float>(-0.2f, 2.5, 0.0f).MakeWrapped();
	constexpr EmuMath::ColourRGB<std::uint8_t> byte_colour_(colour_);
	constexpr EmuMath::ColourRGB<std::int8_t> byte_colour_from_overflow_(EmuMath::ColourRGB<float>(2.5f, -20.1f, 0.5f));
	constexpr EmuMath::ColourRGB<std::uint8_t> byte_colour_from_wrapped_byte_overflow_ = byte_colour_from_overflow_.MakeWrapped<std::uint8_t>();
	constexpr EmuMath::ColourRGB<std::uint8_t> byte_colour_from_byte_overflow_ = EmuMath::ColourRGB<std::uint8_t>(byte_colour_from_overflow_);

	constexpr EmuMath::ColourRGB<float> test_float_(0.0f, 1.0f, 0.0f);
	constexpr EmuMath::ColourRGB<std::uint16_t> test_int_(0, std::numeric_limits<std::uint16_t>::max(), 0);
	constexpr EmuMath::ColourRGB<std::uint32_t> test_int32_(0, std::numeric_limits<std::uint32_t>::max(), 0);
	constexpr bool test_bool_a_lhsint_rhsfloat_ = test_int_ == test_float_;
	constexpr bool test_bool_b_lhsfloat_rhsint_ = test_float_ == test_int_;
	constexpr bool test_lhsint32_rhsint16_ = test_int32_ == test_int_;
	constexpr bool test_lhsint16_rhsint32_ = test_int_ == test_int32_;

	constexpr EmuMath::ColourRGB<float> white_float_(1.0f, 1.0f, 1.0f);
	constexpr EmuMath::ColourRGB<float> modifier_float_(1.0f, 0.5f, 0.25f);
	constexpr EmuMath::ColourRGB<std::uint8_t> modifier_uint8_(255, 255 / 2, 255 / 4);
	constexpr EmuMath::ColourRGB<float> result_ff_ = white_float_ * modifier_float_;
	constexpr EmuMath::ColourRGB<float> result_fb_ = white_float_ * modifier_uint8_;
	constexpr EmuMath::ColourRGB<std::uint8_t> result_bf_ = modifier_uint8_ * white_float_;

	constexpr EmuMath::ColourRGB<std::uint8_t> two_float(255, 127, 64);
	constexpr EmuMath::ColourRGB<float> white_div_two_ = white_float_ / two_float;

	constexpr auto white_cast_ = white_float_.As<std::uint16_t>();
	constexpr auto white_div_two_cast_ = white_div_two_.As<std::uint16_t>();
	constexpr auto result_fb_cast_ = result_fb_.As<std::uint16_t>();
	constexpr auto rest_fb_cast_cast_again_ = result_fb_cast_.As<std::uint8_t>();

	constexpr auto white_mult_5_ = white_float_ * 5;
	constexpr auto white_mult_10_100_1000_ = white_float_ * EmuMath::Vector<3, std::uint64_t>(10, 100, 1000);

#pragma region TEST_HARNESS_EXECUTION
	system("pause");
	EmuCore::TestingHelpers::PerformTests();
#pragma endregion
	return 0;
}
