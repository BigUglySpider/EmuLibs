// Helpful Functors
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

template<class OutMatrix_, class InMatrix_, class ColumnIndices_, class RowIndices_>
struct _matrix_index_sequences_test
{
};

template<class OutMatrix_, class InMatrix_, std::size_t...ColumnIndices_, std::size_t...RowIndices_>
struct _matrix_index_sequences_test<OutMatrix_, InMatrix_, std::index_sequence<ColumnIndices_...>, std::index_sequence<RowIndices_...>>
{
	static constexpr std::size_t num_columns_ = sizeof...(ColumnIndices_);
	static constexpr std::size_t num_rows_ = sizeof...(RowIndices_);
	using column_index_sequence = typename EmuCore::TMP::variadic_splice_integer_sequences
	<
		EmuCore::TMP::make_duplicated_index_sequence<ColumnIndices_, num_rows_>...
	>::type;
	using row_index_sequence = typename EmuCore::TMP::looped_integer_sequence<std::index_sequence<RowIndices_...>, num_columns_ - 1>::type;
};

template<typename T_, T_...Indices_>
void PrintIntSequence(std::integer_sequence<T_, Indices_...>)
{
	std::cout << "{ ";
	((std::cout << Indices_ << ", "), ...);
	std::cout << " }";
}

template<typename...Args_>
constexpr inline bool variadic_and_test(Args_&&...args_)
{
	return (... && args_);
}

int main()
{
	srand(static_cast<unsigned int>(time(0)));
	EmuCore::Timer<std::milli> timer_;

	constexpr auto mat_to_transpose_ = EmuMath::Matrix<4, 5, float, true>(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20);
	constexpr auto transposed_from_rval_ = EmuMath::Matrix<4, 5, float, true>(mat_to_transpose_).Transpose();
	constexpr auto transposed_from_lval_ = mat_to_transpose_.Transpose();
	std::cout << mat_to_transpose_ << "\n\nTransposed Lval:\n" << transposed_from_lval_ << "\n\nTransposed Rval:\n" << transposed_from_rval_ << "\n\n";

	std::cout << "\n---\n";
	auto runtime_mat_to_transpose = EmuMath::Matrix<4, 5, float, true>(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20);
	auto runtime_ref_transpose_ = runtime_mat_to_transpose.Transpose<float&>();
	std::cout << runtime_mat_to_transpose << "\n\n" << runtime_ref_transpose_ << "\n\n";
	runtime_ref_transpose_.MainDiagonal<float&>() *= 2.5f;
	runtime_ref_transpose_.ColumnAt<3>() = EmuMath::make_vector<int>(-1, -2, -3, -4, -5);
	std::cout << runtime_mat_to_transpose << "\n\n" << runtime_ref_transpose_ << "\n\n";

	constexpr auto egrjoi = EmuMath::Matrix<4, 4, int, true>(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16) / 2.0f;
	constexpr auto egrjof = EmuMath::Matrix<4, 4, float, true>(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16) / 2;
	constexpr auto modi = EmuMath::Matrix<4, 4, int, true>(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16) % 3;
	constexpr auto modf = EmuMath::Matrix<4, 4, float, true>(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16) % 2.5;

	constexpr auto scalar_result_ = EmuMath::Matrix<4, 4, float, true>(1, 0, 0, 0, 0, 10, 0, 0, 0, 0, 1, 0, 1.5, 2, 3, 1) * 2;

	constexpr auto vec_result_ = EmuMath::Matrix<4, 4, float, true>(1, 0, 0, 0, 0, 10, 0, 0, 0, 0, 1, 0, 1.5, 2, 3, 1) * EmuMath::Vector<3, float>(1, 2, 3);

	constexpr auto mat_result_ =
	(
		EmuMath::Matrix<4, 4, float, true>(1, 0, 0, 0, 0, 10, 0, 0, 0, 0, 1, 0, 1.5, 2, 3, 1) *
		EmuMath::Matrix<4, 4, float, true>(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16)
	);

	constexpr auto unequal_mat_result = EmuMath::Matrix<4, 4, float, true>(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16) * EmuMath::Matrix<1, 4, float, true>(1, 2, 3, 4);

	runtime_mat_to_transpose = decltype(runtime_mat_to_transpose)(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20);
	std::cout << runtime_mat_to_transpose << "\n\n";
	decltype(runtime_mat_to_transpose) another_(std::move(runtime_mat_to_transpose));
	std::cout << another_ << "\n\n";

	std::cout << mat_result_ << "\n\n";

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
	//constexpr std::size_t noise_num_perms = 4096;
	//constexpr EmuMath::Info::NoisePermutationShuffleMode noise_perm_shuffle_mode = EmuMath::Info::NoisePermutationShuffleMode::SEED_32;
	//constexpr bool noise_perm_bool_input = true;
	//constexpr EmuMath::Info::NoisePermutationInfo::seed_32_type noise_perm_seed_32 = 1337;
	//constexpr EmuMath::Info::NoisePermutationInfo::seed_64_type noise_perm_seed_64 = 1337;
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
	//			EmuMath::Vector<test_noise_dimensions, float>(0.0f),
	//			EmuMath::Vector<test_noise_dimensions, float>(1.0f / 1024.0f),
	//			3.0f,
	//			true,
	//			use_fractal,
	//			EmuMath::Info::NoisePermutationInfo(noise_num_perms, noise_perm_shuffle_mode, noise_perm_bool_input, noise_perm_seed_32, noise_perm_seed_64),
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
	//			EmuMath::Vector<test_noise_dimensions, float>(0.0f),
	//			EmuMath::Vector<test_noise_dimensions, float>(1.0f / 1024.0f),
	//			3.0f,
	//			true,
	//			use_fractal,
	//			EmuMath::Info::NoisePermutationInfo(noise_num_perms, noise_perm_shuffle_mode, noise_perm_bool_input, noise_perm_seed_32, noise_perm_seed_64),
	//			EmuMath::Info::FractalNoiseInfo<float>(6, 2.0f, 0.5f)
	//		)
	//	);
	//	timer_.Pause();
	//	std::cout << "FINISHED FAST NOISE IN: " << timer_.GetMilli() << "ms\n";
	//}
	//
	//EmuMath::Gradient<float> gradient_colours_;
	//gradient_colours_.AddClampedColourAnchor(0.0f, EmuMath::Colours::Blue());
	//gradient_colours_.AddClampedColourAnchor(0.35f, EmuMath::Colours::Blue());
	//gradient_colours_.AddClampedColourAnchor(0.45f, EmuMath::Colours::White());
	//gradient_colours_.AddClampedColourAnchor(0.5f, EmuMath::Colours::Black());
	//gradient_colours_.AddClampedColourAnchor(0.65f, EmuMath::Colours::Yellow());
	//gradient_colours_.AddClampedColourAnchor(0.85f, EmuMath::Colours::Green());
	//gradient_colours_.AddClampedColourAnchor(1.0f, EmuMath::Colours::Red());
	//
	//EmuMath::Gradient<std::uint8_t> gradient_grayscale_;
	//gradient_colours_.AddClampedColourAnchor(0.0f, EmuMath::Colours::Black<std::uint8_t>());
	//gradient_colours_.AddClampedColourAnchor(1.0f, EmuMath::Colours::White<std::uint8_t>());
	//
	//auto& noise_gradient_ = gradient_colours_;
	//
	//WriteNoiseTableToPPM(noise_, noise_gradient_, "test_noise_scalar");
	//WriteNoiseTableToPPM(fast_noise_, noise_gradient_, "test_noise_simd");
	 
#pragma region TEST_HARNESS_EXECUTION
	system("pause");
	EmuCore::TestingHelpers::PerformTests();
#pragma endregion
	return 0;
}
