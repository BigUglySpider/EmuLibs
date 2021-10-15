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

	constexpr std::size_t num_permutations_ = 1024;
	constexpr EmuMath::NoiseType noise_type_ = EmuMath::NoiseType::PERLIN;
	using sample_processor = EmuMath::Functors::noise_sample_processor_perlin3d_normalise;
	constexpr float freq_ = 32.0f;
	constexpr EmuMath::Vector<3, float> start_(0.0f, 0.0f, 0.0f);
	constexpr EmuMath::Vector<3, float> end_(1.0f, 1.0f, 1.0f);
	constexpr EmuMath::Vector<3, float> custom_step(0.001f, 0.001f, 0.001f);
	constexpr EmuMath::Vector<3, std::size_t> resolution_(32, 32, 32);

	constexpr std::size_t table_size = 3;
	EmuMath::NoiseTable<table_size> noise_table;

	constexpr EmuMath::NoiseTableOptions<table_size> options_no_step = EmuMath::NoiseTableOptions<3>
	(
		resolution_,
		start_,
		end_,
		freq_,
		false,
		EmuMath::Info::NoisePermutationInfo
		(
			num_permutations_,
			EmuMath::Info::NoisePermutationInfo::ShuffleMode::SEED_64,
			EmuMath::Info::NoisePermutationInfo::_default_bool_input,
			1337,
			1337
		)
	);
	constexpr EmuMath::NoiseTableOptions<table_size> options_with_step = EmuMath::NoiseTableOptions<3>
	(
		resolution_,
		start_,
		custom_step,
		freq_,
		true,
		EmuMath::Info::NoisePermutationInfo
		(
			num_permutations_,
			EmuMath::Info::NoisePermutationInfo::ShuffleMode::SEED_64,
			EmuMath::Info::NoisePermutationInfo::_default_bool_input,
			1337,
			1337
		)
	);

	constexpr auto auto_step = options_no_step.MakeStep();
	constexpr auto custom_step_from_options = options_with_step.MakeStep();
	
	std::cout << "Generating table...\n";
	if (noise_table.GenerateNoise<noise_type_, sample_processor>(options_with_step))
	{
		std::cout << "Success! (" << noise_table.size() << ")\n";
	}
	else
	{
		std::cout << "Failure!\n";
	}
	std::cout << noise_table << "\n";

#pragma region OLD_NOISE_TESTS
	constexpr EmuMath::Vector<3, float> white_(1.0f, 1.0f, 1.0f);
	constexpr EmuMath::Vector<3, float> step_ = (end_ - start_) / resolution_;
	constexpr bool seed_arg_bool_ = true;
	constexpr std::uint32_t seed_arg_32_ = 25;
	constexpr std::uint64_t seed_arg_64_ = 14154;
	constexpr auto seed_arg_ = seed_arg_bool_;

	constexpr bool DO_2D_ = false;
	using noise_generator = EmuMath::NoiseGenFunctor<DO_2D_ ? 2 : 3, noise_type_>;

	std::vector<EmuMath::Vector<3, float>> colour_grid_(resolution_.x * resolution_.y * (DO_2D_ ? 1 : resolution_.z));
	EmuMath::Vector<3, float> point_ = start_;
	noise_generator noise_generator_ = noise_generator();
	EmuMath::NoisePermutations permutations(num_permutations_, seed_arg_);
	sample_processor sample_processor_ = sample_processor();

	std::size_t sample_i = 0;
	for (std::size_t z = 0, end_z = (DO_2D_ ? 1 : resolution_.z); z < end_z; ++z)
	{
		std::cout << "Processing layer #" << z << "...\n";
		point_.y = start_.y;
		for (std::size_t y = 0; y < resolution_.y; ++y)
		{
			point_.x = start_.x;
			for (std::size_t x = 0; x < resolution_.x; ++x)
			{
				float sample_ = noise_generator_(point_, freq_, permutations);
				sample_ = sample_processor_(sample_);
				if (true) std::cout << sample_ << "\n";
				colour_grid_[sample_i] = ((white_ * sample_) * 255.0f).Clamp(0.0f, 255.0f); // Clamp instead of fmod since we know we're producing 0:1 range; this is to correct fp errors
				point_.x += step_.x;
				++sample_i;
			}
			point_.y += step_.y;
		}
		point_.z += step_.z;
	}

	if constexpr (DO_2D_)
	{
		std::ofstream out_ppm_("./test_noise.ppm", std::ios_base::out | std::ios_base::binary);
		out_ppm_ << "P6" << std::endl << resolution_.x << ' ' << resolution_.y << std::endl << "255" << std::endl;
		std::cout << "\nOutputting image...\n";
		for (std::size_t i = 0, end = colour_grid_.size() / (DO_2D_ ? 1 : resolution_.z); i < end; ++i)
		{
			EmuMath::Vector<3, std::uint8_t> colour_byte_(colour_grid_[i]);
			out_ppm_ << (char)colour_byte_.x << (char)colour_byte_.y << (char)colour_byte_.z;
		}
		out_ppm_.close();
	}
	else
	{
		for (std::size_t z = 0; z < resolution_.z; ++z)
		{
			std::cout << "\nOutputting image layer #" << z << "...\n";

			std::ostringstream name_;
			name_ << "./test_noise_" << z << ".ppm";
			std::ofstream out_ppm_(name_.str(), std::ios_base::out | std::ios_base::binary);
			out_ppm_ << "P6" << std::endl << resolution_.x << ' ' << resolution_.y << std::endl << "255" << std::endl;

			for (std::size_t i = resolution_.x * resolution_.y * z, end_i = resolution_.x * resolution_.y * (z + 1); i < end_i; ++i)
			{
				EmuMath::Vector<3, std::uint8_t> colour_byte_(colour_grid_[i]);
				out_ppm_ << (char)colour_byte_.x << (char)colour_byte_.y << (char)colour_byte_.z;
			}
			out_ppm_.close();
		}
	}
#pragma endregion

#pragma region TEST_HARNESS_EXECUTION
	system("pause");
	EmuCore::TestingHelpers::PerformTests();
#pragma endregion
	return 0;
}
