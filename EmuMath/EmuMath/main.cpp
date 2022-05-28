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

#include "EmuCore/Functors/StdOps.h"

// Fast Vector
#include "EmuMath/FastVector.h"

template<typename T_, std::size_t Size_>
inline std::ostream& operator<<(std::ostream& str_, const std::array<T_, Size_>& arr_)
{
	str_ << "{";
	if constexpr (Size_ > 0)
	{
		str_ << " " << arr_[0];
		for (std::size_t i = 1; i < Size_; ++i)
		{
			str_ << ", " << arr_[i];
		}
	}
	str_ << " }";
	return str_;
}

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

	/*
#pragma region PRE_TEST_BODY
	EmuMath::FastVector<4, float> fast_v4f_a;
	EmuMath::FastVector<4, float> fast_v4f_b(12);
	std::cout << fast_v4f_a << std::endl;
	std::cout << fast_v4f_b << std::endl;
	std::cout << fast_v4f_b.Store<5>() << std::endl;
	std::cout << fast_v4f_a.Store<3>() << std::endl;

	EmuMath::FastVector<8, float> fast_v8f_a(7);
	std::cout << fast_v8f_a << std::endl;
	std::cout << EmuMath::FastVector<7, float>(6);
	std::cout << std::endl << EmuMath::FastVector<9, float>(8) << std::endl;
	std::cout << EmuMath::FastVector<8, float, 256>() << std::endl;
	std::cout << EmuMath::FastVector<8, float, 256>(3) << std::endl;
	std::cout << EmuMath::FastVector<9, float, 256>(3) << std::endl;
	std::cout << EmuMath::FastVector<7, float, 256>(3) << std::endl;
	std::cout << EmuMath::FastVector<3, float, 256>(3).Store<4>() << std::endl;
	std::cout << EmuMath::FastVector<12, float, 128>(6).Store<4>() << std::endl;

	std::cout << "\n\n";
	EmuMath::Vector<6, long long> normal_v(42);
	std::cout << normal_v << std::endl;
	fast_v4f_a.Store<1>(normal_v);
	std::cout << normal_v << std::endl;
	std::array<float, 9> some_floats{};
	std::cout << some_floats << std::endl;
	fast_v8f_a.Store(some_floats.data());
	std::cout << some_floats << std::endl;
	fast_v4f_b.Store(some_floats.data() + 4);
	std::cout << some_floats << std::endl;
	EmuMath::FastVector<6, float, 128>(42).Store<true>(some_floats.data());
	std::cout << some_floats << std::endl;
	
	std::cout << "\n\n";
	const float a_float_array[16] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };
	std::cout << EmuMath::FastVector<4, float>(a_float_array) << "\n";
	std::cout << EmuMath::FastVector<12, float>(a_float_array + 4) << "\n";
	std::cout << EmuMath::FastVector<4, float>(1, 2, 3, 4) << "\n";
	std::cout << EmuMath::FastVector<3, int>(1, 2.0f, 3) << "\n";
	std::cout << EmuMath::FastVector<27, float>(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27) << "\n";
	std::cout << EmuMath::FastVector<35, std::uint16_t>(_mm_setr_epi16(1, 2, 3, 4, 5, 6, 7, 8)) << "\n";
	std::cout << EmuMath::FastVector<3, float>(EmuMath::Vector<8, const float>(1, 2, 3, 4, 42, 69, 420, 42)) << "\n";
	std::cout << EmuMath::FastVector<12, float>(_mm_set_ps(1, 2, 3, 4), _mm_set_ps(4, 3, 2, 1), _mm_set_ps(42, 42, 42, 42)) << "\n";

	std::cout << "\n\n";
	std::cout << fast_v8f_a << "\n";
	fast_v8f_a.GetRegisterTheoretical<1>() = _mm_set_ps(42, 4242, 424242, 42424242);
	std::cout << fast_v8f_a << "\n";
	std::cout << fast_v4f_b << "\n";
	EmuSIMD::append_simd_vector_to_stream(std::cout, fast_v4f_b.GetRegisterTheoretical<0>()) << "\n";
	EmuSIMD::append_simd_vector_to_stream(std::cout, fast_v4f_b.GetRegisterTheoretical<1>()) << "\n";

	std::cout << "\n\n";
	EmuMath::FastVector<4, float> fast_v4f_d(1, 2, 3, 4);
	EmuMath::FastVector<4, float> fast_v4f_e(10, 20, 30, 42);
	std::cout << fast_v4f_d << " + " << fast_v4f_e << " = " << fast_v4f_d.Add(fast_v4f_e) << "\n";

	EmuMath::FastVector<8, std::int32_t> fast_v8i32_a(1, 2, 3, 4, 5, 6, 7, 8);
	EmuMath::FastVector<8, std::int32_t> fast_v8i32_b(10, 20, 30, 42, 50, 60, 70, 80);
	std::cout << fast_v8i32_a << " + " << fast_v8i32_b << " = " << fast_v8i32_a.Add(fast_v8i32_b) << "\n";

	std::cout << "\n\n";
	EmuMath::FastVector<16, std::uint16_t, 128> fast_v16u16_a(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
	EmuMath::FastVector<16, std::uint16_t, 128> fast_v16u16_b(10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120, 130, 140, 150, 160);
	std::cout << fast_v16u16_a << " +\n" << fast_v16u16_b << " =\n" << fast_v16u16_a.Add(fast_v16u16_b) << "\n";
	std::cout << fast_v16u16_a << " + 16 = " << fast_v16u16_a.Add(16) << "\n";
	std::cout << EmuMath::FastVector<4, std::int32_t>(1, 2, 3, 4).Add(5) << "\n";


	system("pause");
	constexpr auto mat_a_ = EmuMath::Matrix<4, 4, int, true>(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
	constexpr auto mat_b_ = EmuMath::Matrix<4, 4, int, true>(1, 1, 1, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13);
	constexpr auto mat_c_ = EmuMath::Matrix<4, 4, float, true>(0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.25, 0.25, 0.25, 0.25);
	constexpr auto mat_lerped_mmm_ = mat_a_.Lerp<float>(mat_b_, mat_c_);
	constexpr auto mat_lerped_msm_ = mat_a_.Lerp<float>(100, mat_c_);
	constexpr auto mat_lerped_mms_ = mat_a_.Lerp<float>(mat_b_, 0.5L);
	constexpr auto mat_lerped_mss_ = mat_a_.Lerp(100, 2);
	constexpr auto mat_lerped_mmm_1313_ = mat_a_.LerpRange<1, 3, 1, 3, float>(mat_b_, mat_c_);
	constexpr auto mat_lerped_mmm_1313_no_copy_ = mat_a_.LerpRangeNoCopy<1, 3, 1, 3>(mat_b_, mat_c_);

	constexpr auto max_ = mat_a_.Max();
	constexpr auto max_1324 = mat_a_.MaxRange<1, 3, 2, 4>();
	constexpr auto max_vecs_ = mat_a_.Max(mat_c_);
	constexpr auto max_vecs_1324_ = mat_c_.MaxRange<1, 3, 2, 4>(mat_a_);
	constexpr auto max_vecs_1324_no_copy_ = mat_a_.MaxRangeNoCopy<1, 3, 2, 4>(mat_c_);

	auto rt_ = EmuMath::Matrix<4, 4, float, true>(1, 2, 3, 4, -5, -6, -7, -8, 9, 10, 11, 12, -13, -14, -15, -16);
	std::cout << rt_ << "\n\n" << mat_a_.Min(rt_) << "\n\n" << mat_a_.MinRange<1, 3, 1, 3>(rt_) << "\n\n" << mat_a_.MinRangeNoCopy<1, 3, 1, 3>(rt_) << "\n\n";
	mat_a_.MinRange<1, 3, 1, 3>(rt_, mat_a_);
	std::cout << rt_ << "\n\n";
	rt_.identity(rt_);
	std::cout << rt_ << "\n\n";


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
#pragma endregion
	 */

	/*// Some tests to see disassembly
	EmuMath::FastVector<4, float> veca((rand() % 100) * 0.33f, (rand() % 100) * 0.33f, (rand() % 100) * 0.33f, (rand() % 100) * 0.33f);
	EmuMath::FastVector<4, float> vecb((rand() % 100) * 0.33f, (rand() % 100) * 0.33f, (rand() % 100) * 0.33f, (rand() % 100) * 0.33f);
	auto result = veca.Add(vecb);
	std::cout << result << "\n";
	*/

#pragma region TEST_HARNESS_EXECUTION
	system("pause");
	EmuCore::TestingHelpers::PerformTests();
#pragma endregion
	//std::cout << result.Add(rand()) << " :)";
	return 0;
}
