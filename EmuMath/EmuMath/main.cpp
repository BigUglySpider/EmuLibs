#include "EmuCore/Functors/Analytics.h"
#include "EmuMath/Noise.h"
#include "EmuMath/Random.h"

#include "EmuMath/Colour.h"

#include "Tests.hpp"

#include "EmuMath/FastNoise.h"

#include "EmuThreads/ThreadPool.h"
#include "EmuThreads/Functors/prioritised_work_allocator.h"
#include "EmuThreads/ThreadSafeHelpers.h"
#include "EmuThreads/ParallelFor.h"

#include <chrono>
#include <thread>

#include "EmuCore/CommonTypes/Timer.h"
#include "EmuCore/CommonTypes/Stopwatch.h"

#include "EmuMath/NewVector.h"

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

void some_test(int& yo_)
{
	std::this_thread::sleep_for(std::chrono::duration<double, std::milli>(rand() % 1000));
	EmuThreads::stream_append_all_in_one(std::cout, ++yo_, " : ", &yo_, "\n");
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

struct FunctorThisTime
{
	inline void operator()() const
	{
		using namespace std::chrono_literals;
		std::this_thread::sleep_for(3000ms);
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

struct SafeOutputter
{
	SafeOutputter() : mutex_(), count_(0), total(0.0)
	{
	}
	SafeOutputter(SafeOutputter&&) noexcept : SafeOutputter()
	{
	}
	SafeOutputter(const SafeOutputter&) : SafeOutputter()
	{
	}

	inline void _action(std::size_t x_, std::size_t y_)
	{
		for (std::size_t i = 0; i < 255; ++i)
		{
			srand(static_cast<unsigned int>(i));
			std::size_t val_ = (x_ << ((rand() % 32) + (rand() % 33)));
			val_ <<= (y_ % 4);
			x_ *= 3;
			x_ |= std::size_t(-1);
			y_ &= ~x_;
			x_ -= y_ * y_;
			total += x_ % 64;
		}
	}

	inline void operator()(std::size_t index_)
	{
		using namespace std::chrono_literals;
		std::lock_guard lock_(mutex_);
		_action(index_, 0);
		++count_;
	}
	inline void operator()(std::size_t x_, std::size_t y_)
	{
		using namespace std::chrono_literals;
		std::lock_guard lock_(mutex_);
		_action(x_, y_);
		++count_;
	}
	inline void operator()(std::tuple<std::size_t, std::size_t> xy_)
	{
		operator()(std::get<0>(xy_), std::get<1>(xy_));
	}

	std::mutex mutex_;
	std::size_t count_;
	double total;
};

struct SomeStructForTestingEdges
{
	template<typename Fov_, typename Near_, typename AspectRatio_>
	constexpr SomeStructForTestingEdges(const Fov_& in_fov_angle_y_, const Near_& in_near_, const AspectRatio_& in_aspect_ratio_) :
		left_(0.0f), right_(0.0f), bottom_(0.0f), top_(0.0f)
	{
		EmuMath::Helpers::matrix_perspective_frustum_edges<false>(in_fov_angle_y_, in_near_, in_aspect_ratio_, left_, right_, bottom_, top_);
	}

	float left_;
	float right_;
	float bottom_;
	float top_;
};

template<class NoiseTable_>
inline void WriteNoiseTableToPPM(const NoiseTable_& noise_table_, const std::string& out_name_ = "test_noise")
{
	using FP_ = typename NoiseTable_::value_type;
	constexpr std::size_t num_dimensions = NoiseTable_::num_dimensions;
	EmuMath::Vector3<FP_> white_(255.0f, 255.0f, 255.0f);

	if constexpr (num_dimensions == 3)
	{
		EmuMath::Vector3<std::size_t> resolution_ = noise_table_.size();
		for (std::size_t z = 0; z < resolution_.z; ++z)
		{
			std::cout << "\nOutputting image layer #" << z << "...\n";

			std::ostringstream name_;
			name_ << "./" << out_name_ << "_" << z << ".ppm";
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

template<class NoiseTable_, class GradientChannel_>
inline void WriteNoiseTableToPPM
(
	const std::vector<NoiseTable_>& noise_table_vector_,
	const EmuMath::Gradient<GradientChannel_>& gradient_,
	const std::string& out_name_ = "test_noise"
)
{
	constexpr std::size_t num_dimensions = NoiseTable_::num_dimensions;
	if (noise_table_vector_.size() != 0)
	{
		if constexpr (num_dimensions == 3)
		{
			const auto& noise_table_ = noise_table_vector_[0];
			EmuMath::Vector3<std::size_t> resolution_ = noise_table_.size();
			for (std::size_t z = 0; z < resolution_.z; ++z)
			{
				std::cout << "\nOutputting image layer #" << z << "...\n";

				std::ostringstream name_;
				name_ << "./" << out_name_ << "_" << z << ".ppm";
				std::ofstream out_ppm_(name_.str(), std::ios_base::out | std::ios_base::binary);
				out_ppm_ << "P6" << std::endl << resolution_.x << ' ' << resolution_.y << std::endl << "255" << std::endl;

				for (std::size_t y = 0; y < resolution_.y; ++y)
				{
					for (std::size_t x = 0; x < resolution_.x; ++x)
					{
						EmuMath::ColourRGB<std::uint8_t> colour_byte_ = gradient_.GetColour<std::uint8_t>(noise_table_.at(x, y, z));
						out_ppm_ << (char)colour_byte_.R() << (char)colour_byte_.G() << (char)colour_byte_.B();
					}
				}
				out_ppm_.close();
			}
			std::cout << "Finished outputting all 3D noise layers.\n";
		}
		else if constexpr (num_dimensions == 2)
		{
			const auto& noise_table_ = noise_table_vector_[0];
			EmuMath::Vector2<std::size_t> resolution_ = noise_table_.size();
			std::cout << "\nOutputting 2D noise image layer...\n";

			std::ostringstream name_;
			name_ << "./" << out_name_ << ".ppm";
			std::ofstream out_ppm_(name_.str(), std::ios_base::out | std::ios_base::binary);
			out_ppm_ << "P6" << std::endl << resolution_.x << ' ' << resolution_.y << std::endl << "255" << std::endl;

			for (std::size_t y = 0; y < resolution_.y; ++y)
			{
				for (std::size_t x = 0; x < resolution_.x; ++x)
				{
					EmuMath::ColourRGB<std::uint8_t> colour_byte_ = gradient_.GetColour<std::uint8_t>(noise_table_.at(x, y));
					out_ppm_ << (char)colour_byte_.R() << (char)colour_byte_.G() << (char)colour_byte_.B();
				}
			}
			out_ppm_.close();
			std::cout << "Finished outputting all 2D noise.\n";
		}
		else
		{
			EmuMath::Vector2<std::size_t> resolution_ = { noise_table_vector_[0].size<0>(), noise_table_vector_.size() };
			std::cout << "\nOutputting 1D noise image layer from full vector...\n";

			std::ostringstream name_;
			name_ << "./" << out_name_ << ".ppm";
			std::ofstream out_ppm_(name_.str(), std::ios_base::out | std::ios_base::binary);
			out_ppm_ << "P6" << std::endl << resolution_.x << ' ' << resolution_.y << std::endl << "255" << std::endl;

			for (std::size_t y = 0; y < resolution_.y; ++y)
			{
				auto& noise_table_ = noise_table_vector_[y];
				for (std::size_t x = 0; x < resolution_.x; ++x)
				{
					EmuMath::ColourRGB<std::uint8_t> colour_byte_ = gradient_.GetColour<std::uint8_t>(noise_table_.at(x));
					out_ppm_ << (char)colour_byte_.R() << (char)colour_byte_.G() << (char)colour_byte_.B();
				}
			}
			out_ppm_.close();
			std::cout << "Finished outputting all 1D noise.\n";
		}
	}
}

int main()
{
	srand(static_cast<unsigned int>(time(0)));
	EmuCore::Timer<std::milli> timer_;

	EmuMath::Vector<5, float> aaaaa;
	EmuMath::Matrix<1, 27, int> bbbbb;

	constexpr EmuMath::NewVector<4, float> newvector_a_(1, 2, 3, 4);
	constexpr bool hoigjheor = EmuMath::NewVector<4, float>().valid_template_construction_args<int, int, int, int>();
	constexpr auto val_0_ = newvector_a_.at<0>();
	constexpr auto val_1_ = newvector_a_.at<1>();
	constexpr auto val_2_ = newvector_a_.at<2>();
	constexpr auto val_3_ = newvector_a_.at<3>();
	EmuMath::NewVector<4, const float&> newvector_b_(val_0_, val_1_, val_2_, val_3_);
	EmuMath::NewVector<4, EmuMath::vector_internal_ref<const float>> newvector_c_(newvector_b_);

	constexpr auto ct_theoretical_0_ = EmuMath::Helpers::new_vector_get_theoretical<0>(newvector_a_);
	constexpr auto ct_theoretical_1_ = EmuMath::Helpers::new_vector_get_theoretical<1>(newvector_a_);
	constexpr auto ct_theoretical_2_ = EmuMath::Helpers::new_vector_get_theoretical<2>(newvector_a_);
	constexpr auto ct_theoretical_3_ = EmuMath::Helpers::new_vector_get_theoretical<3>(newvector_a_);
	constexpr auto ct_theoretical_4_ = EmuMath::Helpers::new_vector_get_theoretical<4>(newvector_a_);

	auto& rt_theoretical_0_ = EmuMath::Helpers::new_vector_get_theoretical<0>(newvector_b_);
	auto& rt_theoretical_1_ = EmuMath::Helpers::new_vector_get_theoretical<1>(newvector_b_);
	auto& rt_theoretical_2_ = EmuMath::Helpers::new_vector_get_theoretical<2>(newvector_b_);
	auto& rt_theoretical_3_ = EmuMath::Helpers::new_vector_get_theoretical<3>(newvector_b_);
	auto rt_theoretical_4_ = EmuMath::Helpers::new_vector_get_theoretical<4>(newvector_b_);
	
	std::cout << newvector_b_ << "\n";
	std::cout << newvector_c_ << "\n";
	std::cout << EmuMath::NewVector<4, const float&>(  std::move(newvector_c_)) << "\n";
	std::cout << EmuMath::NewVector<4, const float&>(  newvector_c_) << "\n";
	std::cout << EmuMath::NewVector<4, const float&>(  const_cast<const decltype(newvector_c_)&>(newvector_c_)) << "\n";

	float new_num_ = 45;
	int blombo = 2;
	newvector_b_.Set<0>(new_num_);
	std::cout << newvector_b_ << "\n";
	newvector_b_.Set<2>(new_num_);
	newvector_b_.Set<3>(newvector_a_.at<2>());
	new_num_ = 12;
	std::cout << newvector_b_ << "\n";


	system("pause");
	std::cout << "\n---\n\n\n";
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
	gradient_.AddClampedColourAnchor(1.0f, EmuMath::ColourRGB<float>(0.75f, 0.1f, 0.0f));
	gradient_.AddClampedColourAnchor(0.5f, EmuMath::ColourRGB<float>(0.5f, 0.5f, 0.5f));
	gradient_.AddClampedColourAnchor(123.5f, EmuMath::ColourRGB<float>(0.2f, 1.0f, 1.0f));
	gradient_.AddClampedAlphaAnchor(1.0f, 0.0f);
	gradient_.AddClampedColourAnchor(0.9f, EmuMath::ColourRGB<std::uint8_t>(255 / 4, 255 / 2, 255));
	std::size_t dummy_index_ = gradient_.AddWrappedColourAnchor_GetIndex(0.3f, EmuMath::ColourRGBA<std::int8_t>(-1, -2, -3));
	std::cout << gradient_ << "\n";
	gradient_.EraseColourIndex(dummy_index_);
	gradient_.EraseColourAnchor(0.9f);
	std::cout << "---\n" << gradient_ << "\n";
	std::cout << "---\n" << EmuMath::Gradient<std::uint8_t>(gradient_) << "\n";
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
	std::cout << "---\n";
	std::cout << (gradient_ == gradient_) << "\n";
	std::cout << (EmuMath::Gradient<std::int8_t>(gradient_) == EmuMath::Gradient<std::uint8_t>(gradient_)) << "\n";
	std::cout << (gradient_ == grad_type()) << "\n";
	std::cout << "---\n";
	std::cout << (gradient_ != gradient_) << "\n";
	std::cout << (EmuMath::Gradient<std::int8_t>(gradient_) != EmuMath::Gradient<std::uint8_t>(gradient_)) << "\n";
	std::cout << (gradient_ != grad_type()) << "\n";
	std::cout << "---\n";
	std::cout << gradient_.HasMatchingAlphaAnchors(gradient_) << "\n";
	std::cout << EmuMath::Gradient<std::int8_t>(gradient_).HasMatchingAlphaAnchors(EmuMath::Gradient<std::uint8_t>(gradient_)) << "\n";
	std::cout << gradient_.HasMatchingAlphaAnchors(grad_type()) << "\n";
	std::cout << "---\n";
	std::cout << gradient_.HasMatchingColourAnchors(gradient_) << "\n";
	std::cout << EmuMath::Gradient<std::int8_t>(gradient_).HasMatchingColourAnchors(EmuMath::Gradient<std::uint8_t>(gradient_)) << "\n";
	std::cout << gradient_.HasMatchingColourAnchors(grad_type()) << "\n";
	std::cout << "---\n";
	grad_type ______;
	______.AddClampedColourAnchor<float, true>(0.5f, {});
	std::cout << (______ == grad_type()) << "\n";
	std::cout << (______ != grad_type()) << "\n";
	std::cout << ______.HasMatchingAlphaAnchors(grad_type()) << "\n";
	std::cout << ______.HasMatchingColourAnchors(grad_type()) << "\n";
	std::cout << "---\n";

	constexpr auto wrap_test_ = grad_type::wrap_anchor(-0.3f);

	constexpr auto red_ = EmuMath::Colours::Lime();

	grad_type::anchor_type anchor_ = 0.0f;


	grad_type gradient_colours_;
	gradient_colours_.AddClampedColourAnchor(0.0f, EmuMath::Colours::Blue());
	gradient_colours_.AddClampedColourAnchor(0.35f, EmuMath::Colours::Blue());
	gradient_colours_.AddClampedColourAnchor(0.45f, EmuMath::Colours::White());
	gradient_colours_.AddClampedColourAnchor(0.5f, EmuMath::Colours::Black());
	gradient_colours_.AddClampedColourAnchor(0.65f, EmuMath::Colours::Yellow());
	gradient_colours_.AddClampedColourAnchor(0.85f, EmuMath::Colours::Green());
	gradient_colours_.AddClampedColourAnchor(1.0f, EmuMath::Colours::Red());

	grad_type gradient_greyscale_;
	gradient_greyscale_.AddClampedColourAnchor(0.0f, EmuMath::Colours::White());
	gradient_greyscale_.AddClampedColourAnchor(1.0f, EmuMath::Colours::Black());

	grad_type& noise_gradient_ = gradient_colours_;
	std::cout << "\nNoise Gradient:\n";
	std::cout << noise_gradient_ << "\n";
	std::cout << "\nNoise Gradient Reversed:\n";
	noise_gradient_.ReverseColours();
	std::cout << noise_gradient_ << "\n";

	__m128 some_a_128_ = _mm_set_ps(3.0f, 2.0f, 1.0f, 0.0f);
	__m128 some_b_128_ = _mm_set_ps(7.0f, 6.0f, 5.0f, 4.0f);
	std::cout << EmuMath::FastVector4f(EmuSIMD::_underlying_simd_helpers::_execute_shuffle<1, 1, 3, 3>(some_a_128_, some_b_128_)) << "\n";

	EmuSIMD::append_simd_vector_to_stream<8>
	(
		std::cout,
		_mm256_set_epi8(0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31)
	) << "\n";


	__m256i _8_bit_256_ = _mm256_setr_epi8    (1,  2,  3,  4,  5,  6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32);
	__m256i _8_bit_mul_256_ = _mm256_setr_epi8(32, 31, 30, 29, 28, 1, 2, 3, 4, 10, 5,  2,  1,  3,  4,  4,  5,  2,  6,  5,  4,  3,  2,  1,  1,  0,  3,  4,  5,  1,  2,  3);
	EmuSIMD::append_simd_vector_to_stream<8, false>
	(
		std::cout,
		EmuSIMD::_underlying_simd_helpers::_mul_all_int<8>(_8_bit_256_, _8_bit_mul_256_)
	) << "\n";

	__m256 cmp_a_ = _mm256_set_ps(2.0f, 1.0f, 3.0f, 4.0f, 0.0f, 2.0f, 3.0f, 3.0f);
	__m256 cmp_b_ = _mm256_set_ps(2.0f, 5.0f, 6.6f, 4.0f, 3.0f, 1.0f, 2.0f, 3.0f);
	EmuSIMD::append_simd_vector_to_stream
	(
		std::cout,
		EmuSIMD::_underlying_simd_helpers::_make_register_from_movemask_fp<__m256>(_mm256_movemask_ps(_mm256_cmp_ps(cmp_a_, cmp_b_, _CMP_EQ_OS)))
	) << "\n";

	__m128i mod_a_256_ = _mm_setr_epi32(10, 3, -4, 4);
	__m128i mod_b_256_ = _mm_setr_epi32(1,  2,  3, 4);
	EmuSIMD::append_simd_vector_to_stream
	(
		std::cout,
		EmuSIMD::_underlying_simd_helpers::_mod_int<32, true>(mod_a_256_, mod_b_256_)
	) << "\n";
	EmuSIMD::append_simd_vector_to_stream
	(
		std::cout,
		EmuSIMD::_underlying_simd_helpers::_rem_int<32, true>(mod_a_256_, mod_b_256_)
	) << "\n";
	EmuSIMD::append_simd_vector_to_stream(std::cout, EmuSIMD::setallone<__m256>()) << "\n";


	std::cout << "---\n\n";


	using testing_register = __m256i;
	constexpr std::size_t testing_element_width = 8;
	testing_register a_simd_ = EmuSIMD::set_incrementing<testing_register, 1, testing_element_width>();
	testing_register b_simd_ = EmuSIMD::set_incrementing<testing_register, 33, testing_element_width>();
	testing_register mask_simd_ = EmuSIMD::index_mask<testing_register, true, false, false, false, false, true, false, false>::get();
	EmuSIMD::append_simd_vector_to_stream<testing_element_width, false>(std::cout, a_simd_) << " BLEND\n";
	EmuSIMD::append_simd_vector_to_stream<testing_element_width, false>(std::cout, b_simd_) << " WITH MASK\n";
	EmuSIMD::append_simd_vector_to_stream<testing_element_width, false>(std::cout, mask_simd_) << ":\n";
	EmuSIMD::append_simd_vector_to_stream<testing_element_width, false>(std::cout, EmuSIMD::blendv(a_simd_, b_simd_, mask_simd_)) << "\n";
	EmuSIMD::append_simd_vector_to_stream<testing_element_width, false>
	(
		std::cout,
		EmuSIMD::blend
		<
			false, false, true, true, true, false, true, false, false, false, false, true, true, true, true, false,
			true, true, true, true, true, false, true, false, false, false, false, true, true, true, true, true
		>(a_simd_, b_simd_)
	) << "\n";

	__m256 lhs_ = EmuSIMD::set<__m256>(1, 2, 3, 4, 5, 6, 7, 8);
	__m256 rhs_ = EmuSIMD::set<__m256>(9, 10, 11, 12, 13, 14, 15, 16);
	EmuSIMD::append_simd_vector_to_stream(std::cout, lhs_) << "\n";
	EmuSIMD::append_simd_vector_to_stream(std::cout, rhs_) << "\n";
	EmuSIMD::append_simd_vector_to_stream(std::cout, _mm256_permute2f128_ps(lhs_, rhs_, 0b00110001)) << "\n";

	__m256i lhs_int_ = _mm256_set_epi32(1, 2, 3, 4, 5, 6, 7, 8);
	__m256i rhs_int_ = _mm256_set_epi32(1, 4, 3, 2, 5, 6, 7, 8);
	std::cout << std::bitset<32>(_mm256_movemask_epi8(_mm256_cmpeq_epi32(lhs_int_, rhs_int_))) << "\n";
	std::cout << EmuSIMD::cmp_all_eq<true, true, true, true, true, false, true, false, true>(lhs_int_, rhs_int_) << "\n";
	EmuSIMD::append_simd_vector_to_stream(std::cout, EmuSIMD::horizontal_sum_fill(lhs_)) << "\n";


	constexpr EmuMath::NoiseType test_noise_type_flag = EmuMath::NoiseType::PERLIN;
	constexpr std::size_t test_noise_dimensions = 3;
	constexpr auto sample_count = EmuMath::Vector<3, std::size_t>(1024, 1024, 1);
	constexpr bool use_fractal = true;
	using scalar_test_noise_processor = EmuMath::Functors::noise_sample_processor_perlin_normalise<test_noise_dimensions>;
	using fast_test_noise_processor = EmuMath::Functors::fast_noise_sample_processor_perlin_normalise<test_noise_dimensions>;

	constexpr std::size_t num_iterations = 1;
	std::vector<EmuMath::NoiseTable<test_noise_dimensions, float>> noise_;
	std::vector<EmuMath::FastNoiseTable<test_noise_dimensions, 0>> fast_noise_;
	noise_.resize(num_iterations, decltype(noise_)::value_type());
	fast_noise_.resize(num_iterations, decltype(fast_noise_)::value_type());

	system("pause");
	for (std::size_t i = 0; i < num_iterations; ++i)
	{
		std::cout << "\nNOISE BATCH " << i << "\n";
		timer_.Restart();
		noise_[i].GenerateNoise<test_noise_type_flag, scalar_test_noise_processor>
		(
			noise_[i].MakeOptions
			(
				sample_count,
				EmuMath::Vector<3, float>(0.0f, 0.0f, 0.0f),
				EmuMath::Vector<3, float>(1.0f / 1024.0f, 1.0f / 1024.0f, 1.0f / 1024.0f),
				3.0f,
				true,
				use_fractal,
				EmuMath::Info::NoisePermutationInfo(4096, EmuMath::Info::NoisePermutationShuffleMode::SEED_32, true, 1337, 1337),
				EmuMath::Info::FractalNoiseInfo<float>(6, 2.0f, 0.5f)
			)
		);
		timer_.Pause();
		std::cout << "FINISHED SCALAR NOISE IN: " << timer_.GetMilli() << "ms\n";


		timer_.Restart();
		fast_noise_[i].GenerateNoise<test_noise_type_flag, fast_test_noise_processor>
		(
			fast_noise_[i].make_options
			(
				sample_count,
				EmuMath::Vector<3, float>(0.0f, 0.0f, 0.0f),
				EmuMath::Vector<3, float>(1.0f / 1024.0f, 1.0f / 1024.0f, 1.0f / 1024.0f),
				3.0f,
				true,
				use_fractal,
				EmuMath::Info::NoisePermutationInfo(4096, EmuMath::Info::NoisePermutationShuffleMode::SEED_32, true, 1337, 1337),
				EmuMath::Info::FractalNoiseInfo<float>(6, 2.0f, 0.5f)
			)
		);
		timer_.Pause();
		std::cout << "FINISHED FAST NOISE IN: " << timer_.GetMilli() << "ms\n";
	}
	WriteNoiseTableToPPM(noise_, noise_gradient_, "test_noise_scalar");
	WriteNoiseTableToPPM(fast_noise_, noise_gradient_, "test_noise_simd");

	// #### THREADED_NOISE_EXAMPLE ####
	//std::cout << "GENERATING FAST NOISE VIA THREAD POOL...\n";
	//timer_.Restart();
	//EmuThreads::DefaultThreadPool thread_pool_(6);
	//using fast_noise_array_type = std::vector<std::vector<EmuMath::FastNoiseTable<3, 1>>>;
	//fast_noise_array_type fast_noise_array_(8, fast_noise_array_type::value_type(8, EmuMath::FastNoiseTable<3, 1>()));
	//for (std::size_t x = 0, end_x_ = fast_noise_array_.size(); x < end_x_; ++x)
	//{
	//	auto& array_ = fast_noise_array_[x];
	//	for (std::size_t y = 0, end_y_ = fast_noise_array_.size(); y < end_y_; ++y)
	//	{
	//		auto* p_table_ = &(array_[y]);
	//		auto options_ = EmuMath::FastNoiseTable<3, 1>::make_options
	//		(
	//			EmuMath::Vector<3, std::size_t>(128, 128, 1),
	//			EmuMath::Vector<3, float>((1.0f / 1024.0f) * (x * 128), (1.0f / 1024.0f) * (y * 128), 0.0f),
	//			EmuMath::Vector<3, float>(1.0f / 1024.0f, 1.0f / 1024.0f, 1.0f / 1024.0f),
	//			3.0f,
	//			true,
	//			true,
	//			EmuMath::Info::NoisePermutationInfo(4096, EmuMath::Info::NoisePermutationShuffleMode::SEED_32, true, 1337, 1337),
	//			EmuMath::Info::FractalNoiseInfo<float>(6, 2.0f, 0.5f)
	//		);
	//
	//		using func_type = bool(EmuMath::FastNoiseTable<3, 1>::*)(const EmuMath::FastNoiseTable<3, 1>::options_type&);
	//
	//		thread_pool_.AllocateTask
	//		(
	//			std::bind<func_type>
	//			(
	//				&EmuMath::FastNoiseTable<3, 1>::GenerateNoise<test_noise_type_flag, test_noise_processor>,
	//				p_table_,
	//				options_
	//			)
	//		);
	//	}
	//}
	//thread_pool_.ViewWorkAllocator().WaitForAllTasksToComplete();
	//timer_.Pause();
	//std::cout << "FINISHED FAST NOISE VIA THREAD POOL IN: " << timer_.GetMilli() << "ms\n";
	//EmuMath::Vector3<std::size_t> resolution_ = fast_noise_.size();
	//for (std::size_t z = 0; z < resolution_.z; ++z)
	//{
	//	std::cout << "\nOutputting threaded image layer #" << z << "...\n";
	//
	//	std::ostringstream name_;
	//	name_ << "./test_noise_threaded_" << z << ".ppm";
	//	std::ofstream out_ppm_(name_.str(), std::ios_base::out | std::ios_base::binary);
	//	out_ppm_ << "P6" << std::endl << resolution_.x << ' ' << resolution_.y << std::endl << "255" << std::endl;
	//
	//	for (std::size_t y = 0; y < resolution_.y; ++y)
	//	{
	//		for (std::size_t x = 0; x < resolution_.x; ++x)
	//		{
	//			auto& array_ = fast_noise_array_[x / 128];
	//			auto& noise_table_ = array_[y / 128];
	//			EmuMath::ColourRGB<std::uint8_t> colour_byte_ = noise_gradient_.GetColour<std::uint8_t>(noise_table_.at(x % 128, y % 128, z % 1));
	//			out_ppm_ << (char)colour_byte_.R() << (char)colour_byte_.G() << (char)colour_byte_.B();
	//		}
	//	}
	//	out_ppm_.close();
	//}
	//std::cout << "Finished outputting all 3D noise layers from array.\n";



	EmuSIMD::append_simd_vector_to_stream(std::cout, EmuSIMD::cast<__m256>(_mm_set_ps(1.0f, 2.0f, 3.0f, 4.0f))) << "\n";
	EmuMath::Functors::make_fast_noise_3d<EmuMath::NoiseType::PERLIN, __m128> fast_generator_;
	__m128 test_128_ = fast_generator_(_mm_set1_ps(0.4f), _mm_set1_ps(0.0f), _mm_set1_ps(1.0f), _mm_set1_ps(16.0f), _mm_set1_epi32(1023), EmuMath::NoisePermutations(1024, 0U));
	std::cout << "\n\n";
	std::cout << EmuMath::FastVector4f(test_128_) << "\n";
	std::cout << EmuMath::Functors::make_noise_3d<EmuMath::NoiseType::PERLIN, float>()({ 0.4f, 0.0f, 1.0f }, 16.0f, EmuMath::NoisePermutations(1024, 0U)) << "\n";

	__m128 some_float_ = _mm_set_ps(1.0f, 2.0f, 3.0f, 4.0f);
	std::cout << EmuMath::FastVector4f(some_float_) << "\n";
	__m128i some_ints_ = _mm_cvtps_epi32(some_float_);
	std::cout << EmuMath::FastVector4f(_mm_cvtepi32_ps(some_ints_)) << "\n";

#pragma region TEST_HARNESS_EXECUTION
	system("pause");
	EmuCore::TestingHelpers::PerformTests();
#pragma endregion
	return 0;
}
