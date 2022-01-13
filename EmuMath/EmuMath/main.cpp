// Helpeful Functors
#include "EmuCore/Functors/Analytics.h"

// Timing
#include "EmuCore/CommonTypes/Timer.h"
#include "EmuCore/CommonTypes/Stopwatch.h"

// Math components
#include "EmuMath/Colour.h"
#include "EmuMath/FastNoise.h"
#include "EmuMath/Matrix.h"
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
	EmuMath::Vector<3, FP_> white_(255.0f, 255.0f, 255.0f);

	if constexpr (num_dimensions == 3)
	{
		EmuMath::Vector<3, std::size_t> resolution_ = noise_table_.size();
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
					EmuMath::Vector<3, std::uint8_t> colour_byte_(white_.Multiply(noise_table_.at(x, y, z)).Clamp(0.0f, 255.0f));
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
				EmuMath::Vector<3, std::uint8_t> colour_byte_(white_.Multiply(noise_table_.at(x, y)).Clamp(0.0f, 255.0f));
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
			EmuMath::Vector<3, std::size_t> resolution_ = noise_table_.size();
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
			EmuMath::Vector<2, std::size_t> resolution_ = noise_table_.size();
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
			EmuMath::Vector<2, std::size_t> resolution_(noise_table_vector_[0].size<0>(), noise_table_vector_.size());
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

	EmuMath::Matrix<4, 2, float, false> some_mat_4x2f_cm_;
	some_mat_4x2f_cm_.at<0, 0>() = 0.0f;
	some_mat_4x2f_cm_.at<0, 1>() = 0.1f;
	some_mat_4x2f_cm_.at<1, 0>() = 1.0f;
	some_mat_4x2f_cm_.at<1, 1>() = 1.1f;
	some_mat_4x2f_cm_.at<2, 0>() = 2.0f;
	some_mat_4x2f_cm_.at<2, 1>() = 2.1f;
	some_mat_4x2f_cm_.at<3, 0>() = 3.0f;
	some_mat_4x2f_cm_.at<3, 1>() = 3.1f;
	some_mat_4x2f_cm_.AppendToStream<true>(std::cout) << "\n\n";
	some_mat_4x2f_cm_.AppendToStream<false>(std::cout) << "\n\n";
	for (std::size_t x = 0, end = some_mat_4x2f_cm_.num_columns * some_mat_4x2f_cm_.num_rows; x < end; ++x)
	{
		std::cout << *(some_mat_4x2f_cm_.data() + x) << ", ";
	}
	std::cout << "\n\n";

	try
	{
		std::cout << some_mat_4x2f_cm_.at(2, 4);
	}
	catch (std::out_of_range& e)
	{
		std::cout << e.what();
		std::cout << "\n";
	}

	std::cout << "\n---\n";
	constexpr auto unflattened_index_ = some_mat_4x2f_cm_.unflatten_index(5);
	for (std::size_t x = 0; x < 10; ++x)
	{
		try
		{
			std::cout << some_mat_4x2f_cm_.at(x) << "\n";
		}
		catch (std::out_of_range& e)
		{
			std::cout << "\n" << e.what() << "\n\n";
		}
	}

	std::cout << "\n---\n";
	std::cout << "Column 0: " << some_mat_4x2f_cm_.GetColumn<0>() << "\n";
	std::cout << "Column 3: " << some_mat_4x2f_cm_.GetColumn<3>() << "\n";
	std::cout << "Row 0: " << some_mat_4x2f_cm_.GetRow<0>() << "\n";
	std::cout << "Row 3: " << some_mat_4x2f_cm_.GetRow<1>() << "\n";

	some_mat_4x2f_cm_.GetRow<0>().at<2>() = 1337.0f;
	some_mat_4x2f_cm_.GetColumn<0>().at<1>() = -1337.0f;
	std::cout << some_mat_4x2f_cm_ << "\n";

	system("pause");
	
	// ##### SCALAR vs SIMD NOISE #####
	constexpr EmuMath::NoiseType test_noise_type_flag = EmuMath::NoiseType::PERLIN;
	constexpr std::size_t test_noise_dimensions = 3;
	constexpr auto sample_count = EmuMath::make_vector<std::size_t>(1024, 1024, 1);
	constexpr bool use_fractal = true;
	using scalar_test_noise_processor = EmuMath::Functors::noise_sample_processor_perlin_normalise<test_noise_dimensions>;
	using fast_test_noise_processor = EmuMath::Functors::fast_noise_sample_processor_perlin_normalise<test_noise_dimensions>;
	
	constexpr std::size_t num_iterations = 1;
	std::vector<EmuMath::NoiseTable<test_noise_dimensions, float>> noise_;
	std::vector<EmuMath::FastNoiseTable<test_noise_dimensions, 0>> fast_noise_;
	noise_.resize(num_iterations, decltype(noise_)::value_type());
	fast_noise_.resize(num_iterations, decltype(fast_noise_)::value_type());

	constexpr std::size_t noise_num_perms = 4096;
	constexpr EmuMath::Info::NoisePermutationShuffleMode noise_perm_shuffle_mode = EmuMath::Info::NoisePermutationShuffleMode::SEED_32;
	constexpr bool noise_perm_bool_input = true;
	constexpr EmuMath::Info::NoisePermutationInfo::seed_32_type noise_perm_seed_32 = 1337;
	constexpr EmuMath::Info::NoisePermutationInfo::seed_64_type noise_perm_seed_64 = 1337;
	
	system("pause");
	for (std::size_t i = 0; i < num_iterations; ++i)
	{
		std::cout << "\nNOISE BATCH " << i << "\n";
		timer_.Restart();
		noise_[i].GenerateNoise<test_noise_type_flag, scalar_test_noise_processor>
		(
			decltype(noise_)::value_type::MakeOptions
			(
				sample_count,
				EmuMath::Vector<test_noise_dimensions, float>(0.0f),
				EmuMath::Vector<test_noise_dimensions, float>(1.0f / 1024.0f),
				3.0f,
				true,
				use_fractal,
				EmuMath::Info::NoisePermutationInfo(noise_num_perms, noise_perm_shuffle_mode, noise_perm_bool_input, noise_perm_seed_32, noise_perm_seed_64),
				EmuMath::Info::FractalNoiseInfo<float>(6, 2.0f, 0.5f)
			)
		);
		timer_.Pause();
		std::cout << "FINISHED SCALAR NOISE IN: " << timer_.GetMilli() << "ms\n";
	
	
		timer_.Restart();
		fast_noise_[i].GenerateNoise<test_noise_type_flag, fast_test_noise_processor>
		(
			decltype(fast_noise_)::value_type::make_options
			(
				sample_count,
				EmuMath::Vector<test_noise_dimensions, float>(0.0f),
				EmuMath::Vector<test_noise_dimensions, float>(1.0f / 1024.0f),
				3.0f,
				true,
				use_fractal,
				EmuMath::Info::NoisePermutationInfo(noise_num_perms, noise_perm_shuffle_mode, noise_perm_bool_input, noise_perm_seed_32, noise_perm_seed_64),
				EmuMath::Info::FractalNoiseInfo<float>(6, 2.0f, 0.5f)
			)
		);
		timer_.Pause();
		std::cout << "FINISHED FAST NOISE IN: " << timer_.GetMilli() << "ms\n";
	}

	EmuMath::Gradient<float> gradient_colours_;
	gradient_colours_.AddClampedColourAnchor(0.0f, EmuMath::Colours::Blue());
	gradient_colours_.AddClampedColourAnchor(0.35f, EmuMath::Colours::Blue());
	gradient_colours_.AddClampedColourAnchor(0.45f, EmuMath::Colours::White());
	gradient_colours_.AddClampedColourAnchor(0.5f, EmuMath::Colours::Black());
	gradient_colours_.AddClampedColourAnchor(0.65f, EmuMath::Colours::Yellow());
	gradient_colours_.AddClampedColourAnchor(0.85f, EmuMath::Colours::Green());
	gradient_colours_.AddClampedColourAnchor(1.0f, EmuMath::Colours::Red());

	EmuMath::Gradient<std::uint8_t> gradient_grayscale_;
	gradient_colours_.AddClampedColourAnchor(0.0f, EmuMath::Colours::Black<std::uint8_t>());
	gradient_colours_.AddClampedColourAnchor(1.0f, EmuMath::Colours::White<std::uint8_t>());

	auto& noise_gradient_ = gradient_colours_;

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

#pragma region TEST_HARNESS_EXECUTION
	system("pause");
	EmuCore::TestingHelpers::PerformTests();
#pragma endregion
	return 0;
}
