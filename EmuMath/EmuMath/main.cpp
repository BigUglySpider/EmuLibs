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
	constexpr EmuMath::NoisePermutations::seed_64_type seed_64 = 1337;
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
			seed_32,
			seed_64
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
			seed_32,
			seed_64
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
	WriteNoiseTableToPPM(noise_table);

	EmuMath::NoiseTable<table_size> babby_table(std::move(noise_table));
	std::cout << "Main Size (Preswap): " << noise_table.size() << "\n";
	std::cout << "Babby Size (Preswap): " << babby_table.size() << "\n";
	babby_table.swap(noise_table);
	std::cout << "Main Size (Postswap): " << noise_table.size() << "\n";
	std::cout << "Babby Size (Postswap): " << babby_table.size() << "\n";
	std::cout << noise_table << "\n";
	std::cout << babby_table << "\n";

#pragma region TEST_HARNESS_EXECUTION
	system("pause");
	EmuCore::TestingHelpers::PerformTests();
#pragma endregion
	return 0;
}
