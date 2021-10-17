#include "EmuCore/Functors/Analytics.h"
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

template<std::size_t num_dimensions>
inline void WriteNoiseTableToPPM(const EmuMath::NoiseTable<num_dimensions>& noise_table_)
{
	EmuMath::Vector3<float> white_(255.0f, 255.0f, 255.0f);

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
	}
}

int main()
{
	srand(static_cast<unsigned int>(time(0)));

	constexpr EmuMath::NoisePermutations::seed_32_type seed_32 = 1337;
	constexpr EmuMath::NoisePermutations::seed_64_type seed_64 = 13337;
	constexpr std::size_t num_permutations_ = 1024;
	constexpr EmuMath::NoiseType noise_type_ = EmuMath::NoiseType::PERLIN;
	constexpr float freq_ = 128.0f;
	constexpr EmuMath::Vector<3, float> start_(0.0f, 0.0f, 0.0f);
	constexpr EmuMath::Vector<3, float> end_(1.0f, 1.0f, 1.0f);
	constexpr EmuMath::Vector<3, float> custom_step(0.001f, 0.001f, 0.001f);
	constexpr EmuMath::Vector<3, std::size_t> resolution_(1920, 1920, 5);
	constexpr std::size_t total_samples_ = resolution_.TotalProduct<std::size_t>();
	constexpr bool use_fractal_noise_ = false;
	constexpr std::size_t fractal_octaves_ = 3;
	constexpr float fractal_lacunarity_ = 2.0f;
	constexpr float fractal_gain_ = 0.5;
	constexpr EmuMath::Info::FractalNoiseInfo fractal_noise_info_ = EmuMath::Info::FractalNoiseInfo
	(
		fractal_octaves_,
		fractal_lacunarity_,
		fractal_gain_
	);
	constexpr EmuMath::Info::NoisePermutationInfo::ShuffleMode shuffle_mode_ = EmuMath::Info::NoisePermutationInfo::ShuffleMode::SEED_64;

	constexpr std::size_t table_size = 3;
	EmuMath::NoiseTable<table_size> noise_table;

	using underlying_sample_processor = EmuMath::Functors::noise_sample_processor_perlin3d_normalise;
	using sample_processor_with_analytics = EmuMath::Functors::noise_sample_processor_with_analytics
	<
		underlying_sample_processor,
		EmuCore::analytic_track_min<float>,
		EmuCore::analytic_track_max<float>,
		EmuCore::analytic_sum<float>,
		EmuCore::analytic_count<std::size_t>
	>;

	constexpr bool use_analytics = true;
	using sample_processor = std::conditional_t<!use_analytics, underlying_sample_processor, sample_processor_with_analytics>;

	constexpr EmuMath::NoiseTableOptions<table_size> options_no_step = EmuMath::NoiseTableOptions<table_size>
	(
		resolution_,
		start_,
		end_,
		freq_,
		false,
		use_fractal_noise_,
		EmuMath::Info::NoisePermutationInfo
		(
			num_permutations_,
			shuffle_mode_,
			EmuMath::Info::NoisePermutationInfo::_default_bool_input,
			seed_32,
			seed_64
		),
		fractal_noise_info_
	);
	constexpr EmuMath::NoiseTableOptions<table_size> options_with_step = EmuMath::NoiseTableOptions<table_size>
	(
		resolution_,
		start_,
		custom_step,
		freq_,
		true,
		use_fractal_noise_,
		EmuMath::Info::NoisePermutationInfo
		(
			num_permutations_,
			shuffle_mode_,
			EmuMath::Info::NoisePermutationInfo::_default_bool_input,
			seed_32,
			seed_64
		),
		fractal_noise_info_
	);

	constexpr auto auto_step = options_no_step.MakeStep();
	constexpr auto custom_step_from_options = options_with_step.MakeStep();

	sample_processor sample_processor_;
	
	std::cout << "Generating table...\n";
	if (noise_table.GenerateNoise<noise_type_, sample_processor&>(options_no_step, sample_processor_))
	{
		std::cout << "Success! (" << noise_table.size() << ")\n";
	}
	else
	{
		std::cout << "Failure!\n";
	}
	WriteNoiseTableToPPM(noise_table);

	std::cout << "Min: " << sample_processor_.at<0>().min_value << "\n";
	std::cout << "Max: " << sample_processor_.at<1>().max_value << "\n";
	std::cout << "Sum: " << sample_processor_.at<2>().total_sum << "\n";
	std::cout << "Count: " << sample_processor_.at<3>().total_calls << "\n";
	std::cout << "Mean: " << sample_processor_.at<2>().total_sum / sample_processor_.at<3>().total_calls << "\n";

	system("pause");
	for (std::size_t z = 0, end_z_ = noise_table.size<2>(); z < end_z_; ++z)
	{
		for (std::size_t y = 0, end_y_ = noise_table.size<1>(); y < end_y_; ++y)
		{
			for (std::size_t x = 0, end_x_ = noise_table.size<0>(); x < end_x_; ++x)
			{
				float sample_ = noise_table(x, y, z);
				if (sample_ <= 0.0f || sample_ >= 1.0f)
				{
					std::cout << sample_ << "\n";
				}
			}
		}
	}

	//std::cout << noise_table << "\n";

	//EmuMath::NoiseTable<table_size> babby_table = EmuMath::NoiseTable<table_size>(noise_table);
	//std::cout << "Main Size (Copy-construct):\n" << noise_table << "\n";
	//std::cout << "Babby Size (Copy-construct):\n" << babby_table << "\n\n###\n\n";
	//noise_table = EmuMath::NoiseTable<table_size>(std::move(babby_table));
	//std::cout << "Main Size (Reversed std::move construct):\n" << noise_table << "\n";
	//std::cout << "Babby Size (Reversed std::move construct):\n" << babby_table << "\n\n###\n\n";
	//babby_table = noise_table;
	//std::cout << "Main Size (Copy assign):\n" << noise_table << "\n";
	//std::cout << "Babby Size (Copy assign):\n" << babby_table << "\n\n###\n\n";
	//babby_table = std::move(noise_table);
	//std::cout << "Main Size (std::move assign):\n" << noise_table << "\n";
	//std::cout << "Babby Size (std::move assign):\n" << babby_table << "\n\n###\n\n";

	noise_table.Deallocate();

#pragma region TEST_HARNESS_EXECUTION
	system("pause");
	EmuCore::TestingHelpers::PerformTests();
#pragma endregion
	return 0;
}
