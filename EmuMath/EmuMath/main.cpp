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
	constexpr EmuMath::ColourRGBA<float> white4_(1.0f, 1.0f, 1.0f, 1.0f);
	constexpr EmuMath::ColourRGBA<float> overkill4_(1.5f, 1.6f, 1.7f, 1.5f);
	constexpr EmuMath::ColourRGB<std::uint8_t> white_byte_(255, 255, 255);
	constexpr EmuMath::ColourRGBA<std::uint8_t> white_byte_half_visible_(255, 255, 255, 255 / 2);
	constexpr EmuMath::ColourRGBA<float> overkill_inisible_(overkill4_, 0.0f);
	constexpr bool cmp_result_a_ = white_ == white4_;
	constexpr bool cmp_result_b_ = white_ == white_byte_;
	constexpr bool cmp_result_c_ = overkill4_ == white4_;
	constexpr bool cmp_result_d_ = overkill4_ == white_byte_;
	constexpr bool cmp_result_e_ = white_byte_ == overkill4_;
	constexpr bool cmp_result_f_ = white_ == white_byte_half_visible_;

	constexpr bool cmp_result_g_ = white_ != white4_;
	constexpr bool cmp_result_h_ = white_ != white_byte_;
	constexpr bool cmp_result_i_ = overkill4_ != white4_;
	constexpr bool cmp_result_j_ = overkill4_ != white_byte_;
	constexpr bool cmp_result_k_ = white_byte_ != overkill4_;
	constexpr bool cmp_result_l_ = white_ != white_byte_half_visible_;
	constexpr bool cmp_result_m_ = white_.operator!=<false>(white_byte_half_visible_);

	constexpr EmuMath::ColourRGB<float> some_inverted_colour_ = EmuMath::ColourRGB<float>(0.2f, 0.95f, 0.4f).Inverse();
	constexpr auto inverted_rgba_no_alpha_ = EmuMath::ColourRGBA<float>(1.0f, 0.5f, 0.2f).Inverse();
	constexpr EmuMath::ColourRGB<std::uint8_t> byte_from_float_rgba_inverted_(inverted_rgba_no_alpha_);
	constexpr EmuMath::ColourRGB<std::int8_t> seven_bits_from_byte_(byte_from_float_rgba_inverted_);
	constexpr EmuMath::ColourRGB<std::uint32_t> colour128_from_byte_(byte_from_float_rgba_inverted_);
	constexpr EmuMath::ColourRGBA<float> colour128f_from_colour128i_(colour128_from_byte_);

	constexpr EmuMath::ColourRGB<float> to_mult_f_rgb_ = EmuMath::ColourRGB<float>(0.2f, 1.0f, 0.5f);
	constexpr EmuMath::ColourRGBA<double> to_mult_d_rgba_ = EmuMath::ColourRGBA<double>(1.0, 0.5, 1.0, 0.2);
	constexpr EmuMath::ColourRGB<std::uint8_t> to_mult_byte_rgb_ = EmuMath::ColourRGB<std::uint8_t>(1, 255, 255/4);
	constexpr EmuMath::ColourRGBA<std::uint8_t> to_mult_byte_rgba_ = EmuMath::ColourRGBA<std::uint8_t>(255, 255, 127, 255);
	constexpr float to_mult_scalar_f_ = 2.5f;
	constexpr std::uint32_t to_mult_scalar_i_ = 2;
	constexpr auto to_mult_vector1f_ = EmuMath::Vector<1, float>(2.0f);
	constexpr auto to_mult_vector2d_ = EmuMath::Vector<2, double>(0.5, 0.5);
	constexpr auto to_mult_vector3ld_ = EmuMath::Vector<3, long double>(1.0L, 0.5L, 0.25L);
	constexpr auto to_mult_vector4i_ = EmuMath::Vector<4, std::int32_t>(-1, 1, -2, 2);

	//constexpr auto mult_result_0a_ = to_mult_f_rgb_ - to_mult_d_rgba_;
	//constexpr auto mult_result_0b_ = to_mult_f_rgb_ - to_mult_byte_rgb_;
	//constexpr auto mult_result_0c_ = to_mult_f_rgb_ - to_mult_byte_rgba_;
	//constexpr auto mult_result_0d_ = to_mult_f_rgb_ - to_mult_scalar_f_;
	//constexpr auto mult_result_0e_ = to_mult_f_rgb_ - to_mult_scalar_i_;
	//constexpr auto mult_result_0f_ = to_mult_f_rgb_ - to_mult_vector1f_;
	//constexpr auto mult_result_0g_ = to_mult_f_rgb_ - to_mult_vector2d_;
	//constexpr auto mult_result_0h_ = to_mult_f_rgb_ - to_mult_vector3ld_;
	//constexpr auto mult_result_0i_ = to_mult_f_rgb_ - to_mult_vector4i_;
	//
	//constexpr auto mult_result_1a_ = to_mult_d_rgba_ - to_mult_f_rgb_;
	//constexpr auto mult_result_1b_ = to_mult_d_rgba_ - to_mult_byte_rgb_;
	//constexpr auto mult_result_1c_ = to_mult_d_rgba_ - to_mult_byte_rgba_;
	//constexpr auto mult_result_1d_ = to_mult_d_rgba_ - to_mult_scalar_f_;
	//constexpr auto mult_result_1e_ = to_mult_d_rgba_ - to_mult_scalar_i_;
	//constexpr auto mult_result_1f_ = to_mult_d_rgba_ - to_mult_vector1f_;
	//constexpr auto mult_result_1g_ = to_mult_d_rgba_ - to_mult_vector2d_;
	//constexpr auto mult_result_1h_ = to_mult_d_rgba_ - to_mult_vector3ld_;
	//constexpr auto mult_result_1i_ = to_mult_d_rgba_ - to_mult_vector4i_;
	//
	//constexpr auto mult_result_2a_ = to_mult_byte_rgb_ - to_mult_f_rgb_;
	//constexpr auto mult_result_2b_ = to_mult_byte_rgb_ - to_mult_byte_rgb_;
	//constexpr auto mult_result_2c_ = to_mult_byte_rgb_ - to_mult_byte_rgba_;
	//constexpr auto mult_result_2d_ = to_mult_byte_rgb_ - to_mult_scalar_f_;
	//constexpr auto mult_result_2e_ = to_mult_byte_rgb_ - to_mult_scalar_i_;
	//constexpr auto mult_result_2f_ = to_mult_byte_rgb_ - to_mult_vector1f_;
	//constexpr auto mult_result_2g_ = to_mult_byte_rgb_ - to_mult_vector2d_;
	//constexpr auto mult_result_2h_ = to_mult_byte_rgb_ - to_mult_vector3ld_;
	//constexpr auto mult_result_2i_ = to_mult_byte_rgb_ - to_mult_vector4i_;
	//
	//constexpr auto mult_result_3a_ = to_mult_byte_rgba_ - to_mult_f_rgb_;
	//constexpr auto mult_result_3b_ = to_mult_byte_rgba_ - to_mult_byte_rgb_;
	//constexpr auto mult_result_3c_ = to_mult_byte_rgba_ - to_mult_byte_rgba_;
	//constexpr auto mult_result_3d_ = to_mult_byte_rgba_ - to_mult_scalar_f_;
	//constexpr auto mult_result_3e_ = to_mult_byte_rgba_ - to_mult_scalar_i_;
	//constexpr auto mult_result_3f_ = to_mult_byte_rgba_ - to_mult_vector1f_;
	//constexpr auto mult_result_3g_ = to_mult_byte_rgba_ - to_mult_vector2d_;
	//constexpr auto mult_result_3h_ = to_mult_byte_rgba_ - to_mult_vector3ld_;
	//constexpr auto mult_result_3i_ = to_mult_byte_rgba_ - to_mult_vector4i_;

	EmuMath::ColourRGBA<float> runtime_rgba_f_(0.1f, -0.1f, 1.0f, 1.5f);
	std::cout << runtime_rgba_f_ << "\n";
	runtime_rgba_f_.Wrap();
	std::cout << runtime_rgba_f_ << "\n";
	std::cout << (runtime_rgba_f_ == runtime_rgba_f_) << "\n";
	std::cout << (runtime_rgba_f_ != runtime_rgba_f_) << "\n";


#pragma region TEST_HARNESS_EXECUTION
	system("pause");
	EmuCore::TestingHelpers::PerformTests();
#pragma endregion
	return 0;
}
