#include "EmuCore/Functors/Analytics.h"
#include "EmuMath/Noise.h"
#include "EmuMath/Random.h"

#include "EmuMath/Colour.h"

#include "Tests.hpp"

#include <chrono>
#include <thread>

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
	constexpr auto lerp_c_min_false_ = lerp_c_.Min<false>();
	constexpr auto lerp_c_min_true_ = lerp_c_.Min<true>();
	constexpr auto lerp_c_max_false_ = lerp_c_.Max<false>();
	constexpr auto lerp_c_max_true_ = lerp_c_.Max<true>();

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
	runtime_rgba_f_.Set(0.1, 0.2f, 0.53L, 1);
	std::cout << runtime_rgba_f_ << "\n";
	std::cout << "---Grey---\n";
	std::cout << "Basic Average: " << runtime_rgba_f_.GreyscaleBasic() << "\n";
	std::cout << "Luminance Average: " << runtime_rgba_f_.GreyscaleLuminance() << "\n";
	std::cout << "Desaturated: " << runtime_rgba_f_.GreyscaleDesaturate() << "\n";
	std::cout << "Decomposed (Min): " << runtime_rgba_f_.GreyscaleMin() << "\n";
	std::cout << "Decomposed (Max): " << runtime_rgba_f_.GreyscaleMax() << "\n";

	constexpr EmuMath::ColourRGB<float> from_rgba_ = EmuMath::ColourRGBA<float>(1, 2, 3, 4);

	constexpr auto some_vec_ = EmuMath::Vector<1, long double>(colour_a_.AsVector());

	auto bloob = EmuMath::ColourRGB<float>().AsVectorRGB();
	auto bloob_ = EmuMath::ColourRGBA<float>().AsVectorRGB();
	auto bloob__ = EmuMath::ColourRGB<float>().AsVectorRGBA();
	auto bloob___ = EmuMath::ColourRGBA<float>().AsVectorRGBA();


	constexpr EmuMath::WrappedColour<float, true> wrapped_colour_(-0.2, 0.2, 0.5, 1.1);

	std::cout << "\n\n";
	auto wrapped_runtime_ = wrapped_colour_;
	std::cout << wrapped_runtime_ << "\n";
	wrapped_runtime_.G(25);
	std::cout << wrapped_runtime_ << "\n";
	std::cout << (wrapped_runtime_ * 2) << "\n";
	std::cout << (wrapped_runtime_ * EmuMath::WrappedColour<std::uint8_t, true>(255, 0, 255)) << "\n";

	EmuMath::WrappedColourRGBA<float> some_wrapped_colour_(2, 3.2, -4.6, 1.0);
	EmuMath::ColourRGB<float> some_colour_again_( some_wrapped_colour_ );

	std::cout << "\n\n";
	std::cout << some_wrapped_colour_ << "\n";
	EmuMath::WrappedColourRGBA<float> wee = some_wrapped_colour_.Add(2.1);
	std::cout << wee << "\n";
	std::cout << wee.Lerp<false>(EmuMath::ColourRGBA<double>(1, 2, 3, 1), 0.5f) << "\n";
	std::cout << wee.Lerp<true>(EmuMath::ColourRGBA<double>(1, 2, 3, 1), 0.5f) << "\n";

	decltype(wee)::underlying_colour wee_unwrapped_(wee);

	constexpr auto wrapped_colour_greyscale_basic_ = wrapped_colour_.GreyscaleBasic();
	constexpr auto wrapped_colour_greyscale_luminance_ = wrapped_colour_.GreyscaleLuminance();
	constexpr auto wrapped_colour_greyscale_desaturate_ = wrapped_colour_.GreyscaleDesaturate();
	constexpr auto wrapped_colour_greyscale_decompose_min_ = wrapped_colour_.GreyscaleMin();
	constexpr auto wrapped_colour_greyscale_decompose_max_ = wrapped_colour_.GreyscaleMax();

	constexpr EmuMath::ClampedColourRGBA<float> some_clamped_colour_(-0.1, 0.0, 0.8, 1.5);

	std::cout << "\n\n\n";
	using grad_type = EmuMath::Gradient<float>;
	grad_type gradient_;
	gradient_.AddColourAnchor(1.0f, EmuMath::ColourRGB<float>(0.75f, 0.1f, 0.0f));
	gradient_.AddColourAnchor(0.5f, EmuMath::ColourRGB<float>(0.5f, 0.5f, 0.5f));
	gradient_.AddColourAnchor(123.5f, EmuMath::ColourRGB<float>(0.2f, 1.0f, 1.0f));
	gradient_.AddAlphaAnchor(1.0f, 0.0f);
	std::cout << gradient_ << "\n";
	std::cout << "---\n";
	std::cout << "at(0.0): " << gradient_.GetColour(0.0f) << "\n";
	std::cout << "at(1.0): " << gradient_.GetColour(1.0f) << "\n";
	std::cout << "at(0.5): " << gradient_.GetColour(0.5f) << "\n";
	std::cout << "at(0.75): " << gradient_.GetColour(0.75f) << "\n";
	std::cout << "at(0.25): " << gradient_.GetColour(0.25f) << "\n";
	std::cout << "---\n";
	std::cout << "at(0.0): " << gradient_.GetAlpha(0.0f) << "\n";
	std::cout << "at(1.0): " << gradient_.GetAlpha(1.0f) << "\n";
	std::cout << "at(0.5): " << gradient_.GetAlpha(0.5f) << "\n";
	std::cout << "at(0.75): " << gradient_.GetAlpha(0.75f) << "\n";
	std::cout << "at(0.25): " << gradient_.GetAlpha(0.25f) << "\n";
	std::cout << "---\n";
	std::cout << "at(0.0): " << gradient_.Get(0.0f) << "\n";
	std::cout << "at(1.0): " << gradient_.Get(1.0f) << "\n";
	std::cout << "at(0.5): " << gradient_.Get(0.5f) << "\n";
	std::cout << "at(0.75): " << gradient_.Get(0.75f) << "\n";
	std::cout << "at(0.25): " << gradient_.Get(0.25f) << "\n";

	constexpr auto wrap_test_ = grad_type::wrap_anchor(-0.3f);

	grad_type::anchor_type anchor_ = 0.0f;
	while (true)
	{
		using namespace std::chrono_literals;
		std::cout << "at(" << anchor_ << "): " << gradient_.GetColourWrapped(anchor_) << "\n";
		anchor_ -= 0.001f;
		std::this_thread::sleep_for(100ms);
	}

#pragma region TEST_HARNESS_EXECUTION
	system("pause");
	EmuCore::TestingHelpers::PerformTests();
#pragma endregion
	return 0;
}
