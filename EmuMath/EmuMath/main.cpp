// Helpeful Functors
#include "EmuCore/Functors/Analytics.h"

// Timing
#include "EmuCore/CommonTypes/Timer.h"
#include "EmuCore/CommonTypes/Stopwatch.h"

// Math components
#include "EmuMath/Colour.h"
#include "EmuMath/FastNoise.h"
#include "EmuMath/Noise.h"
#include "EmuMath/Random.h"
#include "EmuMath/Vector.h"

// Test harness execution
#include "Tests.hpp"

template<class NoiseTable_>
inline void WriteNoiseTableToPPM(const NoiseTable_& noise_table_, const std::string& out_name_ = "test_noise")
{
	using FP_ = typename NoiseTable_::value_type;
	constexpr std::size_t num_dimensions = NoiseTable_::num_dimensions;
	EmuMath::NewVector<3, FP_> white_(255.0f, 255.0f, 255.0f);

	if constexpr (num_dimensions == 3)
	{
		EmuMath::NewVector<3, std::size_t> resolution_ = noise_table_.size();
		for (std::size_t z = 0; z < resolution_.at<2>(); ++z)
		{
			std::cout << "\nOutputting image layer #" << z << "...\n";

			std::ostringstream name_;
			name_ << "./" << out_name_ << "_" << z << ".ppm";
			std::ofstream out_ppm_(name_.str(), std::ios_base::out | std::ios_base::binary);
			out_ppm_ << "P6" << std::endl << resolution_.at<0>() << ' ' << resolution_.at<1>() << std::endl << "255" << std::endl;

			for (std::size_t y = 0; y < resolution_.at<1>(); ++y)
			{
				for (std::size_t x = 0; x < resolution_.at<0>(); ++x)
				{
					// Clamp is merely to cancel out fp-rounding errors
					EmuMath::NewVector<3, std::uint8_t> colour_byte_(white_.Multiply(noise_table_.at(x, y, z)).Clamp(0.0f, 255.0f));
					out_ppm_ << (char)colour_byte_.at<0>() << (char)colour_byte_.at<1>() << (char)colour_byte_.at<2>();
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
				EmuMath::NewVector<3, std::uint8_t> colour_byte_(white_.Multiply(noise_table_.at(x, y)).Clamp(0.0f, 255.0f));
				out_ppm_ << (char)colour_byte_.at<0>() << (char)colour_byte_.at<1>() << (char)colour_byte_.at<2>();
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
			EmuMath::NewVector<3, std::size_t> resolution_ = noise_table_.size();
			for (std::size_t z = 0; z < resolution_.at<2>(); ++z)
			{
				std::cout << "\nOutputting image layer #" << z << "...\n";

				std::ostringstream name_;
				name_ << "./" << out_name_ << "_" << z << ".ppm";
				std::ofstream out_ppm_(name_.str(), std::ios_base::out | std::ios_base::binary);
				out_ppm_ << "P6" << std::endl << resolution_.at<0>() << ' ' << resolution_.at<1>() << std::endl << "255" << std::endl;

				for (std::size_t y = 0; y < resolution_.at<1>(); ++y)
				{
					for (std::size_t x = 0; x < resolution_.at<0>(); ++x)
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
			EmuMath::NewVector<2, std::size_t> resolution_ = noise_table_.size();
			std::cout << "\nOutputting 2D noise image layer...\n";

			std::ostringstream name_;
			name_ << "./" << out_name_ << ".ppm";
			std::ofstream out_ppm_(name_.str(), std::ios_base::out | std::ios_base::binary);
			out_ppm_ << "P6" << std::endl << resolution_.at<0>() << ' ' << resolution_.at<1>() << std::endl << "255" << std::endl;

			for (std::size_t y = 0; y < resolution_.at<1>(); ++y)
			{
				for (std::size_t x = 0; x < resolution_.at<0>(); ++x)
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
			EmuMath::NewVector<2, std::size_t> resolution_(noise_table_vector_[0].size<0>(), noise_table_vector_.size());
			std::cout << "\nOutputting 1D noise image layer from full vector...\n";

			std::ostringstream name_;
			name_ << "./" << out_name_ << ".ppm";
			std::ofstream out_ppm_(name_.str(), std::ios_base::out | std::ios_base::binary);
			out_ppm_ << "P6" << std::endl << resolution_.at<0>() << ' ' << resolution_.at<1>() << std::endl << "255" << std::endl;

			for (std::size_t y = 0; y < resolution_.at<1>(); ++y)
			{
				auto& noise_table_ = noise_table_vector_[y];
				for (std::size_t x = 0; x < resolution_.at<0>(); ++x)
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


	
	// ##### SCALAR vs SIMD NOISE #####
	//constexpr EmuMath::NoiseType test_noise_type_flag = EmuMath::NoiseType::PERLIN;
	//constexpr std::size_t test_noise_dimensions = 3;
	//constexpr auto sample_count = EmuMath::make_vector<std::size_t>(1024, 1024, 1);
	//constexpr bool use_fractal = true;
	//using scalar_test_noise_processor = EmuMath::Functors::noise_sample_processor_perlin_normalise<test_noise_dimensions>;
	//using fast_test_noise_processor = EmuMath::Functors::fast_noise_sample_processor_perlin_normalise<test_noise_dimensions>;
	//
	//constexpr std::size_t num_iterations = 1;
	//std::vector<EmuMath::NoiseTable<test_noise_dimensions, float>> noise_;
	//std::vector<EmuMath::FastNoiseTable<test_noise_dimensions, 0>> fast_noise_;
	//noise_.resize(num_iterations, decltype(noise_)::value_type());
	//fast_noise_.resize(num_iterations, decltype(fast_noise_)::value_type());
	//
	//system("pause");
	//for (std::size_t i = 0; i < num_iterations; ++i)
	//{
	//	std::cout << "\nNOISE BATCH " << i << "\n";
	//	timer_.Restart();
	//	noise_[i].GenerateNoise<test_noise_type_flag, scalar_test_noise_processor>
	//	(
	//		decltype(noise_)::value_type::MakeOptions
	//		(
	//			sample_count,
	//			EmuMath::NewVector<test_noise_dimensions, float>(0.0f),
	//			EmuMath::NewVector<test_noise_dimensions, float>(1.0f / 1024.0f),
	//			3.0f,
	//			true,
	//			use_fractal,
	//			EmuMath::Info::NoisePermutationInfo(4096, EmuMath::Info::NoisePermutationShuffleMode::SEED_32, true, 1337, 1337),
	//			EmuMath::Info::FractalNoiseInfo<float>(6, 2.0f, 0.5f)
	//		)
	//	);
	//	timer_.Pause();
	//	std::cout << "FINISHED SCALAR NOISE IN: " << timer_.GetMilli() << "ms\n";
	//
	//
	//	timer_.Restart();
	//	fast_noise_[i].GenerateNoise<test_noise_type_flag, fast_test_noise_processor>
	//	(
	//		decltype(fast_noise_)::value_type::make_options
	//		(
	//			sample_count,
	//			EmuMath::NewVector<test_noise_dimensions, float>(0.0f),
	//			EmuMath::NewVector<test_noise_dimensions, float>(1.0f / 1024.0f),
	//			3.0f,
	//			true,
	//			use_fractal,
	//			EmuMath::Info::NoisePermutationInfo(4096, EmuMath::Info::NoisePermutationShuffleMode::SEED_32, true, 1337, 1337),
	//			EmuMath::Info::FractalNoiseInfo<float>(6, 2.0f, 0.5f)
	//		)
	//	);
	//	timer_.Pause();
	//	std::cout << "FINISHED FAST NOISE IN: " << timer_.GetMilli() << "ms\n";
	//}
	//WriteNoiseTableToPPM(noise_, noise_gradient_, "test_noise_scalar");
	//WriteNoiseTableToPPM(fast_noise_, noise_gradient_, "test_noise_simd");

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
	//			EmuMath::NewVector<3, std::size_t>(128, 128, 1),
	//			EmuMath::NewVector<3, float>((1.0f / 1024.0f) * (x * 128), (1.0f / 1024.0f) * (y * 128), 0.0f),
	//			EmuMath::NewVector<3, float>(1.0f / 1024.0f, 1.0f / 1024.0f, 1.0f / 1024.0f),
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
	//EmuMath::NewVector3<std::size_t> resolution_ = fast_noise_.size();
	//for (std::size_t z = 0; z < resolution_.at<2>(); ++z)
	//{
	//	std::cout << "\nOutputting threaded image layer #" << z << "...\n";
	//
	//	std::ostringstream name_;
	//	name_ << "./test_noise_threaded_" << z << ".ppm";
	//	std::ofstream out_ppm_(name_.str(), std::ios_base::out | std::ios_base::binary);
	//	out_ppm_ << "P6" << std::endl << resolution_.at<0>() << ' ' << resolution_.at<1>() << std::endl << "255" << std::endl;
	//
	//	for (std::size_t y = 0; y < resolution_.at<1>(); ++y)
	//	{
	//		for (std::size_t x = 0; x < resolution_.at<0>(); ++x)
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



	//EmuSIMD::append_simd_vector_to_stream(std::cout, EmuSIMD::cast<__m256>(_mm_set_ps(1.0f, 2.0f, 3.0f, 4.0f))) << "\n";
	//EmuMath::Functors::make_fast_noise_3d<EmuMath::NoiseType::PERLIN, __m128> fast_generator_;
	//__m128 test_128_ = fast_generator_(_mm_set1_ps(0.4f), _mm_set1_ps(0.0f), _mm_set1_ps(1.0f), _mm_set1_ps(16.0f), _mm_set1_epi32(1023), EmuMath::NoisePermutations(1024, 0U));
	//std::cout << "\n\n";
	//std::cout << EmuMath::FastVector4f(test_128_) << "\n";
	//std::cout << EmuMath::Functors::make_noise_3d<EmuMath::NoiseType::PERLIN, float>()({ 0.4f, 0.0f, 1.0f }, 16.0f, EmuMath::NoisePermutations(1024, 0U)) << "\n";
	//
	//__m128 some_float_ = _mm_set_ps(1.0f, 2.0f, 3.0f, 4.0f);
	//std::cout << EmuMath::FastVector4f(some_float_) << "\n";
	//__m128i some_ints_ = _mm_cvtps_epi32(some_float_);
	//std::cout << EmuMath::FastVector4f(_mm_cvtepi32_ps(some_ints_)) << "\n";

#pragma region TEST_HARNESS_EXECUTION
	system("pause");
	EmuCore::TestingHelpers::PerformTests();
#pragma endregion
	return 0;
}
