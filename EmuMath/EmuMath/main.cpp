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
#include "EmuMath/Quaternion.h"
#include "EmuMath/Random.h"
#include "EmuMath/Rect.h"
#include "EmuMath/Vector.h"

// Test harness execution
#include "Tests.hpp"

#include "EmuCore/Functors/StdOps.h"

// Fast Vector
#include "EmuMath/FastMatrix.h"
#include "EmuMath/FastQuaternion.h"
#include "EmuMath/FastVector.h"

#include "EmuCore/ArithmeticHelpers/CommonAlgebra.h"

#include "EmuCore/CommonPreprocessor/All.h"

constexpr auto test_dot = EmuCore::dot<float>(1, 2, 6, 3, 7, 10);
constexpr auto test_dot_2 = EmuCore::dot(5, 7);

inline void universal_pause(const std::string& msg = "Press enter to continue...")
{
	std::string dummy;
	printf("%s", msg.c_str());
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

inline void universal_pause(const std::streamsize max_char_count, const std::string& msg = "Press enter to continue...")
{
	std::string dummy;
	printf("%s", msg.c_str());
	std::cin.ignore(max_char_count, '\n');
}

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

template<std::size_t Size_, typename T_>
inline void PrintIndexable(const T_& indexable)
{
	if constexpr (Size_ > 0)
	{
		std::cout << "{ " << indexable[0];
		for (std::size_t i = 1; i < Size_; ++i)
		{
			std::cout << ", ";
			std::cout << indexable[i];
		}
		std::cout << " }";
	}
	else
	{
		std::cout << "{ }";
	}
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

	{
		constexpr std::size_t len = 240;
		constexpr std::size_t inc = 8;
		using EmuCore::Pi;
		auto func = [](auto val) { return Pi::DegsToRads<float>(val * 0.333333333333333f); };
		for (std::size_t i = 0; i < len; i += inc)
		{
			auto acos_res = EmuSIMD::setr<EmuSIMD::f32x8, 32>(func(i), func(i + 1), func(i + 2), func(i + 3), func(i + 4), func(i + 5), func(i + 6), func(i + 7));
			acos_res = EmuSIMD::Funcs::tan_f32x8(acos_res);
			std::cout << "[" << i << "]: ";
			EmuSIMD::append_simd_vector_to_stream<32, true>(std::cout, acos_res) << "\n";
		}
		universal_pause();
	}

	//*
#pragma region PRE_TEST_BODY
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

	std::cout << "CLAMPS\n";
	std::cout << mat_a_.Clamp(-4, 4) << "\n\n";
	std::cout << mat_a_.Clamp(4, 40) << "\n\n";
	std::cout << mat_a_.Clamp(EmuMath::Matrix<4, 4, int, true>(7, 0, 2, 1, 4, 7, 5, 3, 2, 1, 12, 6, 144, 155, -275, 2), 6) << "\n\n";
	std::cout << mat_a_.Clamp(6, EmuMath::Matrix<4, 4, int, false>(7, 0, 2, 1, 4, 7, 5, 3, 2, 1, 12, 6, 144, 155, -275, 2)) << "\n\n";
	std::cout << mat_a_.Clamp(EmuMath::Matrix<2, 3, int, true>(7, 0, 2, 1, 4, 7), EmuMath::Matrix<4, 4, int, true>(12, 10, 6, 3, 15, 21, 13, -5, 19, 20, 21, -7, 1, 2, 3, 4)) << "\n\n";
	std::cout << mat_a_.Clamp(EmuMath::Matrix<4, 4, int, false>(-3, 4, -4, 5, 3, 4, 5, 6, 10, 11, 12, 13, -255, -511, 31, 1337), EmuMath::Matrix<2, 3, int, false>(3, 12, 6, 8, 9, 10)) << "\n\n";
	std::cout << "---\n";
	std::cout << mat_a_.ClampRange<1, 3, 1, 3>(-4, 4) << "\n\n";
	std::cout << mat_a_.ClampRange<1, 3, 1, 3>(4, 40) << "\n\n";
	std::cout << mat_a_.ClampRange<1, 3, 1, 3>(EmuMath::Matrix<4, 4, int, true>(7, 0, 2, 1, 4, 7, 5, 3, 2, 1, 12, 6, 144, 155, -275, 2), 6) << "\n\n";
	std::cout << mat_a_.ClampRange<1, 3, 1, 3>(6, EmuMath::Matrix<4, 4, int, false>(7, 0, 2, 1, 4, 7, 5, 3, 2, 1, 12, 6, 144, 155, -275, 2)) << "\n\n";
	std::cout << mat_a_.ClampRange<1, 3, 1, 3>(EmuMath::Matrix<2, 3, int, true>(7, 0, 2, 1, 4, 7), EmuMath::Matrix<4, 4, int, true>(12, 10, 6, 3, 15, 21, 13, -5, 19, 20, 21, -7, 1, 2, 3, 4)) << "\n\n";
	std::cout << mat_a_.ClampRange<1, 3, 1, 3>(EmuMath::Matrix<4, 4, int, false>(-3, 4, -4, 5, 3, 4, 5, 6, 10, 11, 12, 13, -255, -511, 31, 1337), EmuMath::Matrix<2, 3, int, false>(3, 12, 6, 8, 9, 10)) << "\n\n";
	std::cout << "---\n";
	std::cout << mat_a_.ClampRangeNoCopy<1, 3, 1, 3>(-4, 4) << "\n\n";
	std::cout << mat_a_.ClampRangeNoCopy<1, 3, 1, 3>(4, 40) << "\n\n";
	std::cout << mat_a_.ClampRangeNoCopy<1, 3, 1, 3>(EmuMath::Matrix<4, 4, int, true>(7, 0, 2, 1, 4, 7, 5, 3, 2, 1, 12, 6, 144, 155, -275, 2), 6) << "\n\n";
	std::cout << mat_a_.ClampRangeNoCopy<1, 3, 1, 3>(6, EmuMath::Matrix<4, 4, int, false>(7, 0, 2, 1, 4, 7, 5, 3, 2, 1, 12, 6, 144, 155, -275, 2)) << "\n\n";
	std::cout << mat_a_.ClampRangeNoCopy<1, 3, 1, 3>(EmuMath::Matrix<2, 3, int, true>(7, 0, 2, 1, 4, 7), EmuMath::Matrix<4, 4, int, true>(12, 10, 6, 3, 15, 21, 13, -5, 19, 20, 21, -7, 1, 2, 3, 4)) << "\n\n";
	std::cout << mat_a_.ClampRangeNoCopy<1, 3, 1, 3>(EmuMath::Matrix<4, 4, int, false>(-3, 4, -4, 5, 3, 4, 5, 6, 10, 11, 12, 13, -255, -511, 31, 1337), EmuMath::Matrix<2, 3, int, false>(3, 12, 6, 8, 9, 10)) << "\n\n";


	constexpr auto scale = EmuMath::Helpers::matrix_make_scale<float>(2, 5, 10);
	constexpr auto scale_from_tuple = EmuMath::Helpers::matrix_make_scale<double>(std::make_tuple(8, -2.0L, 0.5f));
	constexpr auto scale_from_vector = EmuMath::Helpers::matrix_make_scale<int>(EmuMath::Vector<3, float>(1.0f, 2.0f, 6.0f));
	constexpr auto scale_from_vector_no_t_arg = EmuMath::Helpers::matrix_make_scale(EmuMath::Vector<3, float>(1.0f, 0.5f, 6.0f));

	constexpr auto another_scale_0 = EmuMath::Helpers::matrix_make_scale<4, 4, float>(EmuMath::Vector<12, float>(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12));
	constexpr auto another_scale_1 = EmuMath::Helpers::matrix_make_scale<4, 4>(EmuMath::Vector<12, float>(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12));
	constexpr auto another_scale_2 = EmuMath::Helpers::matrix_make_scale<4, 4, float>(12, 5);

	constexpr auto scale_ree = EmuMath::Matrix<4, 4, float, true>::valid_make_scale_args<int, int, int>();
	constexpr auto scale_from_member = EmuMath::Matrix<4, 4, float, true>::make_scale(2, 1, 3);
	constexpr auto scale_ree_tuple = EmuMath::Matrix<4, 4, float, true>::valid_make_scale_args<decltype(std::make_tuple(2, 10, 6, 1))>();
	constexpr auto scale_tuple_from_member = EmuMath::Matrix<4, 4, float, true>::make_scale(std::make_tuple(2, 10));
	constexpr auto scale_vector_from_member = EmuMath::Matrix<4, 4, float, true>::make_scale(EmuMath::Vector<4, float>(7));

	std::cout << "\nASSIGN_SCALE TESTS\n";
	EmuMath::Matrix<4, 4, float, true> scale_assign_matrix(10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120, 130, 140, 150, 160);
	std::cout << scale_assign_matrix << "\n\n";
	scale_assign_matrix.AssignScale(5);
	std::cout << scale_assign_matrix << "\n\n";
	scale_assign_matrix.AssignScale(2, 4, 6);
	std::cout << scale_assign_matrix << "\n\n";
	scale_assign_matrix.AssignScale(std::make_tuple(0, 6));
	std::cout << scale_assign_matrix << "\n\n";
	scale_assign_matrix.AssignScale(EmuMath::Vector<4, unsigned long long int>(1, 2, 3, 4));
	std::cout << scale_assign_matrix << "\n\n";

	std::cout << "MAKE_TRANSLATION TESTS\n";
	constexpr auto translate = EmuMath::Helpers::matrix_make_translation<float>(2, 5, 10);
	constexpr auto translate_from_tuple = EmuMath::Helpers::matrix_make_translation<double>(std::make_tuple(8, -2.0L, 0.5f));
	constexpr auto translate_from_vector = EmuMath::Helpers::matrix_make_translation<int>(EmuMath::Vector<3, float>(1.0f, 2.0f, 6.0f));
	constexpr auto translate_from_vector_no_t_arg = EmuMath::Helpers::matrix_make_translation(EmuMath::Vector<3, float>(1.0f, 0.5f, 6.0f));
	constexpr auto translate_auto_2d = EmuMath::Helpers::matrix_make_translation<double>(-5, 5);
	std::cout << translate << "\n\n";
	std::cout << translate_from_tuple << "\n\n";
	std::cout << translate_from_vector << "\n\n";
	std::cout << translate_from_vector_no_t_arg << "\n\n";
	std::cout << translate_auto_2d << "\n\n";

	constexpr auto another_translate_0 = EmuMath::Helpers::matrix_make_translation<4, 4, float>(EmuMath::Vector<12, float>(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12));
	constexpr auto another_translate_1 = EmuMath::Helpers::matrix_make_translation<4, 4>(EmuMath::Vector<12, float>(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12));
	constexpr auto another_translate_2 = EmuMath::Helpers::matrix_make_translation<4, 4, float>(12, 5);
	std::cout << "---\n";
	std::cout << another_translate_0 << "\n\n";
	std::cout << another_translate_1 << "\n\n";
	std::cout << another_translate_2 << "\n\n";

	constexpr auto translate_ree = EmuMath::Matrix<4, 4, float, true>::valid_make_translation_args<int, int, int>();
	constexpr auto translate_from_member = EmuMath::Matrix<4, 4, float, true>::make_translation(2, 1, 3);
	constexpr auto translate_ree_tuple = EmuMath::Matrix<4, 4, float, true>::valid_make_translation_args<decltype(std::make_tuple(2, 10, 6, 1))>();
	constexpr auto translate_tuple_from_member = EmuMath::Matrix<4, 4, float, true>::make_translation(std::make_tuple(2, 10));
	constexpr auto translate_vector_from_member = EmuMath::Matrix<4, 4, float, true>::make_translation(EmuMath::Vector<4, float>(7));
	std::cout << "---\n";
	std::cout << translate_from_member << "\n\n";
	std::cout << translate_tuple_from_member << "\n\n";
	std::cout << translate_vector_from_member << "\n\n";


	std::cout << "ASSIGN_TRANSLATION TESTS\n";
	EmuMath::Matrix<4, 4, float, true> translate_assign_matrix(10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120, 130, 140, 150, 160);
	std::cout << translate_assign_matrix << "\n\n";
	translate_assign_matrix.AssignTranslation(5);
	std::cout << translate_assign_matrix << "\n\n";
	translate_assign_matrix.AssignTranslation(2, 4, 6);
	std::cout << translate_assign_matrix << "\n\n";
	translate_assign_matrix.AssignTranslation(std::make_tuple(0, 6));
	std::cout << translate_assign_matrix << "\n\n";
	translate_assign_matrix.AssignTranslation(EmuMath::Vector<4, unsigned long long int>(1, 2, 3, 4));
	std::cout << translate_assign_matrix << "\n\n";

	constexpr auto point_to_rotate = EmuMath::Vector<3, double>(1, 2, 3);
	constexpr auto rot_0 = EmuMath::Helpers::matrix_make_rotation_3d_z_constexpr<12, true, false, 4, 4, double, true>(-33);
	constexpr auto point_rot_0 = rot_0 * point_to_rotate;
	std::cout << "ROTATION TESTS\n";
	std::cout << "Constexpr:\n" << rot_0 << "\n\n:Runtime:\n" << EmuMath::Helpers::matrix_make_rotation_3d_z<true, float, false>(-33) << "\n\n";

	std::cout << "ROTATION MEMBER TESTS\n";
	auto member_rot_runtime = EmuMath::Matrix<4, 4, float, true>::make_rotation_3d_z<false>(33);
	constexpr auto member_rot = EmuMath::Matrix<4, 4, float, true>::make_rotation_3d_z_constexpr<4, true, false>(33);
	std::cout << "runtime: " << (member_rot_runtime * point_to_rotate) << "\n";
	std::cout << "constexpr: " << (member_rot * point_to_rotate) << "\n";

	std::cout << "ROTATION MEMBER ASSIGN TESTS\n";
	auto rot_mat_runtime = EmuMath::Matrix<4, 4, float, true>::identity();
	std::cout << rot_mat_runtime << "\nVec: " << (rot_mat_runtime * point_to_rotate) << "\n\n";
	rot_mat_runtime.AssignRotation3DZ<false>(33);
	std::cout << rot_mat_runtime << "\nVec: " << (rot_mat_runtime * point_to_rotate) << "\n\n";
	rot_mat_runtime.AssignRotation3DZConstexpr<12, true, false>(-33);
	std::cout << rot_mat_runtime << "\nVec: " << (rot_mat_runtime * point_to_rotate) << "\n\n";

	std::cout << "IRREGULAR MATRIX MAKE ROTATION TESTS\n";
	EmuMath::Matrix<2, 4, float, true> irregular_matrix(1, 2, 3, 4, 5, 6, 7, 8);
	std::cout << irregular_matrix.make_rotation_3d_x<false>(33) << "\n\n";
	std::cout << irregular_matrix.make_rotation_3d_y<false>(33) << "\n\n";
	std::cout << irregular_matrix.make_rotation_3d_z<false>(33) << "\n\n";

	std::cout << "IRREGULAR MATRIX MAKE ROTATION CONSTEXPR TESTS\n";
	std::cout << irregular_matrix.make_rotation_3d_x_constexpr<12, true, false>(-33) << "\n\n";
	std::cout << irregular_matrix.make_rotation_3d_y_constexpr<12, true, false>(-33) << "\n\n";
	std::cout << irregular_matrix.make_rotation_3d_z_constexpr<12, true, false>(-33) << "\n\n";

	std::cout << "IRREGULAR MATRIX ASSIGN ROTATION TESTS\n";
	irregular_matrix.AssignRotation3DX<false>(33);
	std::cout << irregular_matrix << "\n\n";
	irregular_matrix.AssignRotation3DY<false>(33);
	std::cout << irregular_matrix << "\n\n";
	irregular_matrix.AssignRotation3DZ<false>(33);
	std::cout << irregular_matrix << "\n\n";

	std::cout << "IRREGULAR MATRIX ASSIGN ROTATION CONSTEXPR TESTS\n";
	irregular_matrix.AssignRotation3DXConstexpr<12, true, false>(33);
	std::cout << irregular_matrix << "\n\n";
	irregular_matrix.AssignRotation3DYConstexpr<12, true, false>(33);
	std::cout << irregular_matrix << "\n\n";
	irregular_matrix.AssignRotation3DZConstexpr<12, true, false>(33);
	std::cout << irregular_matrix << "\n\n";

	universal_pause();;
	std::cout << "\n\n\n\nQUATERNIONS\n";
	constexpr auto rot_euler = EmuMath::Vector<3, float>
	(
		EmuCore::Pi::DegsToRads_v<float, int, 45>,
		EmuCore::Pi::DegsToRads_v<float, int, 33>,
		EmuCore::Pi::DegsToRads_v<float, int, 0>
	);

	constexpr auto quat_default = EmuMath::Quaternion<float>();
	auto quat_from_euler = EmuMath::Quaternion<float>(rot_euler.at<0>(), rot_euler.at<1>(), rot_euler.at<2>());
	std::cout << quat_from_euler << "\n";
	std::cout << quat_from_euler.data.Normalise() << "\n";
	constexpr auto quat_from_euler_constexpr = EmuMath::Quaternion<float>::from_euler_constexpr<false>(45, 33, 0);
	constexpr auto quat_from_euler_vector_constexpr = EmuMath::Quaternion<float>::from_euler_constexpr(rot_euler);

	//constexpr auto quat_from_euler_vector_constexpr = EmuMath::Quaternion<float>::from_euler_constexpr(rot_euler);

	constexpr auto a = -0.72301;
	auto asin_runtime = asin(a);

	constexpr std::size_t test_trig_its = 4;
	constexpr auto asin_constexpr = EmuCore::do_asin_constexpr<std::remove_const_t<decltype(a)>>()(a);
	std::cout << "asin: " << asin_runtime << " | asin_constexpr: " << asin_constexpr << "\n";

	auto acos_runtime = acos(a);
	constexpr auto acos_constexpr = EmuCore::do_acos_constexpr<std::remove_const_t<decltype(a)>>()(a);
	std::cout << "acos: " << acos_runtime << " | acos_constexpr: " << acos_constexpr << "\n";

	auto atan_runtime = atan(a);
	constexpr auto atan_constexpr = EmuCore::do_atan_constexpr<std::remove_const_t<decltype(a)>>()(a);
	std::cout << "atan: " << atan_runtime << " | atan_constexpr: " << atan_constexpr << "\n";

	constexpr auto atan2_y = 17.3f;
	auto atan2_runtime = atan2(-10, a);
	constexpr auto atan2_constexpr = EmuCore::do_atan2_constexpr<std::remove_const_t<decltype(a)>>()(-10, a);
	std::cout << "atan2: " << atan2_runtime << " | atan2_constexpr: " << atan2_constexpr << "\n";

	std::cout << "\n---\n";
	constexpr auto full_cvt_euler_test = EmuMath::Vector<3, float>(45.0f, -127.5f, 0.0f);
	std::cout << "Euler: " << full_cvt_euler_test << "\n";
	std::cout << "Quaternion: " << EmuMath::Quaternion<float>::from_euler<false>(full_cvt_euler_test) << "\n";
	std::cout << "Euler from Quaternion: " << EmuMath::Quaternion<float>::from_euler<false>(full_cvt_euler_test).ToEuler<false>() << "\n";
	std::cout << "Quaternion from Euler from Quaternion: " 
		<< EmuMath::Quaternion<float>::from_euler<false>(EmuMath::Quaternion<float>::from_euler<false>(full_cvt_euler_test).ToEuler<false>()) 
		<< "\n";

	constexpr auto constexpr_test_a = EmuMath::Quaternion<float>::from_euler_constexpr<false>(full_cvt_euler_test).ToEulerConstexpr<false>();
	constexpr auto frm_lr_cnstxpr = EmuMath::Quaternion<float>::from_euler_constexpr<false>(full_cvt_euler_test);
	constexpr auto frm_lr_cnstxpr_nrmlsd = frm_lr_cnstxpr.UnitConstexpr();
	constexpr auto nrm = frm_lr_cnstxpr.NormConstexpr();
	auto some_quat = EmuMath::Quaternion<double>::from_euler<false>(45.0, 0, 0);
	auto&& some_quat_scalar = some_quat.W();
	auto some_quat_vector = some_quat.ImaginaryVector<double&>();
	std::cout << some_quat << " | " << some_quat_scalar << " | " << some_quat_vector << "\n";
	some_quat = EmuMath::Quaternion<double>::from_euler<false>(45.0, -127.5f, 0.0L);
	std::cout << some_quat << " | " << some_quat_scalar << " | " << some_quat_vector << "\n";
	constexpr auto frm_lr_cnstxpr_cnjgt = frm_lr_cnstxpr.Conjugate();
	constexpr auto frm_lr_cnstxpr_nvrs = frm_lr_cnstxpr.InverseConstexpr();
	constexpr bool equal_boi = frm_lr_cnstxpr_cnjgt == frm_lr_cnstxpr_nvrs;

	constexpr auto not_normed = EmuMath::Quaternion<float>::from_euler_constexpr<false, false>(full_cvt_euler_test);
	constexpr bool lksdfnsd = not_normed.Conjugate() == frm_lr_cnstxpr_cnjgt;
	constexpr bool lksdfnsde = not_normed.InverseConstexpr() == frm_lr_cnstxpr_cnjgt;

	constexpr auto lerped = EmuMath::Quaternion<float>(1.0f, -1.0f, 12.0f, 0.0f).Lerp(EmuMath::Quaternion<float>(10.0f, 20.0f, 12.0f, 1337), 0.5f);
	constexpr auto lerped_with_vec = EmuMath::Quaternion<float>(1.0f, -1.0f, 12.0f, -6.0f).Lerp(EmuMath::Quaternion<float>(10.0f, 20.0f, 12.0f, 1337), EmuMath::Vector<3, float>(1, 2, 0.5));
	std::cout << "Lerped: " << lerped << " | FusedLerped: " << EmuMath::Quaternion<float>(1, -1, 12, 0).FusedLerp(EmuMath::Quaternion<double>(10, 20, 12, 1337), 0.5L) << "\n\n\n";

	constexpr auto slerp = EmuMath::Quaternion<float>::from_euler_constexpr<false>(45.0f, 0.0f, 0.0f).SlerpConstexpr(EmuMath::Quaternion<float>::from_euler_constexpr<false>(90.0f, 0.0f, 0.0f), 0.5f);
	constexpr auto slerp_euler = slerp.ToEulerConstexpr<false>();


	constexpr auto slerp2 = EmuMath::Quaternion<float>::from_euler_constexpr<false>(45.0f, 120.0f, 0).SlerpConstexpr(EmuMath::Quaternion<float>::from_euler_constexpr<false>(90.0f, 120.0f, 0.0f), 0.5f);
	constexpr auto slerp2_euler = slerp.ToEulerConstexpr<false>();

	auto slerp2_runtime = EmuMath::Quaternion<float>::from_euler<false>(45.0f, 120.0f, 0.0f).Slerp(EmuMath::Quaternion<float>::from_euler<false>(90.0f, 120.0f, 0.0f), 0.5f);
	auto slerp2_fused_runtime = EmuMath::Quaternion<float>::from_euler<false>(45.0f, 120.0f, 0.0f).FusedSlerp(EmuMath::Quaternion<float>::from_euler<false>(90.0f, 120.0f, 0.0f), 0.5f);
	auto slerp2_runtime_euler = slerp2_runtime.ToEuler<false>();
	auto slerp2_fused_runtime_euler = slerp2_fused_runtime.ToEuler<false>();
	std::cout << "Slerped: " << slerp2_runtime << " | Euler: " << slerp2_runtime_euler << "\n";
	std::cout << "Fused Slerped: " << slerp2_fused_runtime << " | Euler: " << slerp2_fused_runtime_euler << "\n";

	constexpr auto quat_a = EmuMath::Quaternion<float>::from_euler_constexpr<false>(20, 0, 0);
	constexpr auto quat_b = EmuMath::Quaternion<float>::from_euler_constexpr<false>(25, 30, 0);
	constexpr auto quat_ab = quat_a * quat_b;
	constexpr auto euler_ab = quat_ab.ToEulerConstexpr<false>();

	auto another_quat = EmuMath::Quaternion<float>(1, 2, 3, 4);
	std::cout << "\n\n\n---\n" << another_quat << " | " << another_quat.NormConstexpr() << " | ";
	another_quat.AssignFusedUnit();
	std::cout << another_quat << " | " << another_quat.FusedNorm() << "\n";

	constexpr auto another_unit = EmuMath::Quaternion<float>(1, 2, 3, 4).UnitConstexpr();

	auto old_euler = EmuMath::Quaternion<float>(EmuCore::Pi::DegsToRads(45.0), EmuCore::Pi::DegsToRads(45.0), EmuCore::Pi::DegsToRads(45.0));
	auto new_euler = EmuMath::Quaternion<float>::from_euler(EmuCore::Pi::DegsToRads(163.0), EmuCore::Pi::DegsToRads(233.151), EmuCore::Pi::DegsToRads(-23.157));
	auto fused_euler = EmuMath::Quaternion<float>::from_euler_fused<false>(45.0, 45.0, 45.0);
	std::cout << "Old Euler: " << old_euler << "\nNew Euler: " << new_euler << "\nFused Euler: " << fused_euler << "\n\n";

	std::cout << "\n\n\n---\nNew Euler: " << new_euler.ToEuler() << "\nFused Euler: " << new_euler.ToEulerFused() << "\nConstexpr Euler: " << new_euler.ToEulerConstexpr() << "\n";

	std::cout << "Mul:\t\t" << (old_euler * new_euler) << " | Fused Mul: " << old_euler.FusedMultiply(new_euler) << "\n";
	old_euler.FusedMultiplyAssign(new_euler);
	std::cout << "FusedMulAssign:\t" << old_euler << "\n\n\n";

	constexpr auto add_a = EmuMath::Helpers::quaternion_from_euler_constexpr<false, float>(30.0f, 25.0f, 10.0f);
	constexpr auto add_b = EmuMath::Quaternion<double>(1, 2, 3, 4);
	constexpr auto add_ab = add_a + add_b;
	constexpr auto unit_add_ab = add_ab.UnitConstexpr();
	constexpr auto add_ab_euler = unit_add_ab.ToEulerConstexpr<false>();
	auto runtime_add_ab = add_a;
	std::cout << runtime_add_ab << "\n";
	runtime_add_ab += add_b;
	std::cout << runtime_add_ab << "\n";

	constexpr auto sub_a = EmuMath::Helpers::quaternion_from_euler_constexpr<false, float>(30.0f, 25.0f, 10.0f);
	constexpr auto sub_b = EmuMath::Quaternion<double>(1, 2, 3, 4);
	constexpr auto sub_ab = sub_a - sub_b;
	constexpr auto unit_sub_ab = add_ab.UnitConstexpr();
	constexpr auto sub_ab_euler = unit_sub_ab.ToEulerConstexpr<false>();
	auto runtime_sub_ab = sub_a;
	std::cout << runtime_sub_ab << "\n";
	runtime_sub_ab -= sub_b;
	std::cout << runtime_sub_ab << "\n";

	constexpr auto neg_a = EmuMath::Helpers::quaternion_from_euler_constexpr<false, float>(30.0f, 25.0f, 10.0f);
	constexpr auto true_neg_a = -neg_a;
	auto runtime_neg_a = neg_a;
	std::cout << runtime_neg_a << "\n";
	runtime_neg_a.NegateAssign();
	std::cout << runtime_neg_a << "\n";

	constexpr auto div_a = EmuMath::Helpers::quaternion_from_euler_constexpr<false, float>(30.0f, 25.0f, 10.0f);
	constexpr auto div_ab = div_a / 10.0f;
	constexpr auto unit_div_ab = div_ab.UnitConstexpr();
	constexpr auto div_ab_euler = unit_div_ab.ToEulerConstexpr<false>();
	auto runtime_div_ab = div_a;
	std::cout << runtime_div_ab << "\n";
	runtime_div_ab /= 10.0f;
	std::cout << runtime_div_ab << "\n";

	constexpr auto mul_a = EmuMath::Helpers::quaternion_from_euler_constexpr<false, float>(30.0f, 25.0f, 10.0f);
	constexpr auto mul_ab = mul_a * 10.0;
	constexpr auto unit_mul_ab = mul_ab.UnitConstexpr();
	constexpr auto mul_ab_euler = unit_mul_ab.ToEulerConstexpr<false>();
	auto runtime_mul_ab = mul_a;
	std::cout << runtime_mul_ab << "\n";
	runtime_mul_ab *= 10.0L;
	std::cout << runtime_mul_ab << "\n\n\n";

	auto ass_quat_a = EmuMath::Quaternion<float>(1, 2, 3, 4);
	auto ass_quat_b = EmuMath::Quaternion<double>(-7, -16, 22, 42);
	const auto ass_quat_c = EmuMath::Quaternion<std::int64_t>(7, -21, 22, 33);
	auto ass_quat_d = EmuMath::Quaternion<long double>(-1337, -22, 1337, 47).FusedUnit();
	std::cout << ass_quat_a << "\n";
	ass_quat_a = ass_quat_b;
	std::cout << ass_quat_a << "\n";
	ass_quat_a = ass_quat_c;
	std::cout << ass_quat_a << "\n";
	ass_quat_a = std::move(ass_quat_d);
	std::cout << ass_quat_a << "\n";

	constexpr auto blo = EmuMath::Vector<3, float>(1, 2, 3);
	constexpr auto blo2 = blo;
	constexpr auto blo3 = EmuMath::Vector<3, float>::is_const_copy_constructible();

	using quat_to_mat_t = double;
	using quat_mat_type = EmuMath::Matrix<4, 4, quat_to_mat_t, true>;
	constexpr auto mat_quat = EmuMath::Quaternion<float>::from_euler_constexpr<false>(45, 0, 0) * EmuMath::Quaternion<double>::from_euler_constexpr<false>(0, 0, 33);

	constexpr auto mat_from_euler = quat_mat_type::make_rotation_3d_x_constexpr<5, false, false>(45.0f) *
		quat_mat_type::make_rotation_3d_z_constexpr<5, false, false>(33.0f);

	constexpr auto mat_from_quat = quat_mat_type::make_rotation_3d(mat_quat);

	constexpr auto mat_from_quats = quat_mat_type::make_rotation_3d
	(
		EmuMath::Quaternion<double>::from_euler_constexpr<false>(15.0f, 0.0f, 0.0f),
		EmuMath::Quaternion<double>::from_euler_constexpr<false>(15.0f, 0.0f, 0.0f),
		EmuMath::Quaternion<double>::from_euler_constexpr<false>(15.0f, 0.0f, 0.0f)
	);

	auto mat_from_fused_quats = quat_mat_type::make_rotation_3d_fused
	(
		EmuMath::Quaternion<double>::from_euler_constexpr<false>(15.0f, 0.0f, 0.0f),
		EmuMath::Quaternion<double>::from_euler_constexpr<false>(15.0f, 0.0f, 0.0f),
		EmuMath::Quaternion<double>::from_euler_constexpr<false>(15.0f, 0.0f, 0.0f)
	);

	std::cout << "\n\n" << mat_from_quats << "\n\n" << mat_from_fused_quats << "\n";

	constexpr auto rect = EmuMath::Rect<float>(5);
	constexpr auto rect_centre = rect.Centre();
	constexpr auto rect_b = EmuMath::Rect<double>(3, 4.2, 10, 10);
	constexpr auto rect_b_centre = rect_b.Centre();
	constexpr auto rect_well_formed = rect.WellFormed();
	constexpr auto rect_temp_well_formed = EmuMath::Rect<float>(0, 3, -1, 3).WellFormed();
	constexpr auto rect_made_central = EmuMath::Rect<float>(23, 10).MakeCentred(5, 5);
	constexpr auto central_contains_point_a_ = rect_made_central.ContainsPoint(4, 3);
	constexpr auto rect_to_scale = EmuMath::Rect<float>(1, -2, 2.5, 4.17);
	constexpr auto pre_scale_centre = rect_to_scale.Centre();
	constexpr auto pre_scale_width = rect_to_scale.Width();
	constexpr auto pre_scale_size = rect_to_scale.Size();
	constexpr auto scaled_rect = rect_to_scale * 2;
	constexpr auto scaled_centre = scaled_rect.Centre();
	constexpr auto scaled_width = scaled_rect.Width();
	constexpr auto scaled_size = scaled_rect.Size();
	constexpr auto reduce_scaled_rect = rect_to_scale * 0.5;
	constexpr auto reduce_scaled_centre = reduce_scaled_rect.Centre();
	constexpr auto reduce_scaled_width = reduce_scaled_rect.Width();
	constexpr auto reduce_scaled_size = reduce_scaled_rect.Size();

	constexpr auto to_reflect = EmuMath::Rect<float>(1.5, 3, 2, 4);
	constexpr auto reflect_a = to_reflect.Reflect<0, 0>();
	constexpr auto reflect_b = to_reflect.Reflect<-1, 0>();
	constexpr auto reflect_c = to_reflect.Reflect<1, 0>();
	constexpr auto reflect_d = to_reflect.Reflect<0, -1>();
	constexpr auto reflect_e = to_reflect.Reflect<0, 1>();
	constexpr auto reflect_f = to_reflect.Reflect<-1, -1>();
	constexpr auto reflect_g = to_reflect.Reflect<-1, 1>();
	constexpr auto reflect_h = to_reflect.Reflect<1, -1>();
	constexpr auto reflect_i = to_reflect.Reflect<1, 1>();
	constexpr auto reflect_j = to_reflect.Reflect<1, 1>().Reflect<-1, -1>();

	constexpr auto reflect_alt_a = to_reflect.Reflect(0, 0);
	constexpr auto reflect_alt_b = to_reflect.Reflect(-1, 0);
	constexpr auto reflect_alt_c = to_reflect.Reflect(1, 0);
	constexpr auto reflect_alt_d = to_reflect.Reflect(0, -1);
	constexpr auto reflect_alt_e = to_reflect.Reflect(0, 1);
	constexpr auto reflect_alt_f = to_reflect.Reflect(0, -1);
	constexpr auto reflect_alt_g = to_reflect.Reflect(0, 1);
	constexpr auto reflect_alt_h = to_reflect.Reflect(0, -1);
	constexpr auto reflect_alt_i = to_reflect.Reflect(0, 1);
	constexpr auto reflect_alt_j = to_reflect.Reflect(1, 1).Reflect(-1, -1);

	constexpr auto test_scale_rect_base = EmuMath::Rect<float>(1);
	constexpr auto scaled_a = test_scale_rect_base.Scale(2);
	constexpr auto scaled_b = test_scale_rect_base.ScaleAnchored<0, 0>(2, 2);
	constexpr auto scaled_c = test_scale_rect_base.ScaleAnchored<1, 0>(2, 2);
	constexpr auto scaled_d = test_scale_rect_base.ScaleAnchored<-1, 0>(2, 2);
	constexpr auto scaled_e = test_scale_rect_base.ScaleAnchored<0, 1>(2, 2);
	constexpr auto scaled_f = test_scale_rect_base.ScaleAnchored<1, -1>(2, 2);

	constexpr EmuMath::Rect<float> rect_from_init_list = { 1, 2, 3, 4 };
	constexpr auto vec_from_init_list = EmuMath::Vector<12, float>{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };
	auto yoiyoi = vec_from_init_list;

	constexpr auto blongo_dongo = EmuMath::Helpers::rect_get_left(rect_from_init_list);
	constexpr auto mbmfgkbmlk = EmuMath::Helpers::rect_get_left(EmuMath::Rect<int>(1, 2, 3, 4));

	constexpr auto collide_a = EmuMath::Rect<float>(0, 0, 5, 5);
	constexpr auto collide_b = EmuMath::Rect<double>(5, 5, 6, 6);
	constexpr auto colliding_a = collide_a.CollidingAxisAligned<true>(collide_b);
	constexpr auto colliding_b = collide_a.CollidingAxisAligned<false>(collide_b);
	constexpr auto colliding_c = collide_a.CollidingAxisAligned(collide_b);
	constexpr auto colliding_d = collide_a.CollidingAxisAligned(collide_b.Translate(-0.2, -0.5));
	constexpr auto colliding_e = collide_a.CollidingAxisAligned(collide_b.Scale(2, 2));
	constexpr auto colliding_f = collide_a.CollidingAxisAligned(collide_b.Translate(-5.9, -5.9));
	

	std::cout << "\n\nPERSPECTIVE (REVERSE DEPTH):\n";
	constexpr auto point_to_project = EmuMath::Vector<4, float>(1, 2, 3, 1);
	constexpr auto point_to_project_3d = EmuMath::Vector<3, float>(1, 2, 3);
	constexpr auto perspective_mat_reverse_z = EmuMath::Helpers::matrix_perspective_vk_reverse_depth_constexpr<double>
	(
		0.785398,
		1920.0 / 1080.0,
		0.1,
		100.0
	);
	std::cout << perspective_mat_reverse_z << "\n\nFlattened: " << perspective_mat_reverse_z.Flatten() << "\n";
	std::cout << "Transformed point: " << (perspective_mat_reverse_z * point_to_project) << "\n";

	std::cout << "---\n\nPERSPECTIVE:\n";
	constexpr auto perspective_mat = EmuMath::Helpers::matrix_perspective_vk_constexpr<double>
	(
		0.785398,
		1920.0 / 1080.0,
		0.1,
		100.0
	);
	std::cout << perspective_mat << "\n\nFlattened: " << perspective_mat.Flatten() << "\n";
	std::cout << "Transformed point: " << (perspective_mat * point_to_project) << "\n";

	std::cout << "---\n\nORTHO:\n";
	constexpr auto ortho_a = EmuMath::Helpers::matrix_ortho_vk<float>(EmuMath::Rect<double>(0, 0, 1280, 1280), 0.1, 100.0);
	std::cout << ortho_a << "\n\nFlattened: " << ortho_a.Flatten() << "\n\n";
	std::cout << "Transformed point: " << (ortho_a * point_to_project) << "\n";
	std::cout << "Transformed point as mat:\n" << 
		(EmuMath::Matrix<4, 4, float, false>(point_to_project, EmuMath::Vector<4, float>(), EmuMath::Vector<4, float>(), EmuMath::Vector<4, float>()) * ortho_a) 
		<< "\n";
	std::cout << "Transformed point as row vector: " << EmuMath::Helpers::matrix_multiply<float>(point_to_project_3d, ortho_a) << "\n";
	auto runtime_point_to_project = point_to_project_3d;
	EmuMath::Helpers::matrix_multiply_assign(runtime_point_to_project, ortho_a);
	std::cout << "Transformed point as row vector (assigned): " << runtime_point_to_project << "\n";
	std::cout << "Translated (lhs): " <<
		EmuMath::Helpers::matrix_multiply<float>(point_to_project_3d, EmuMath::Helpers::matrix_make_translation<float>(1, 2, 3)) << "\n";
	std::cout << "Translated (rhs): " <<
		EmuMath::Helpers::matrix_multiply<float>(EmuMath::Helpers::matrix_make_translation<float>(1, 2, 3), point_to_project_3d) << "\n";

	if constexpr (EmuCore::TMP::type_check_ignore_ref_cv<std::is_integral, const int&>::value)
	{
		std::cout << "HBTRGFHBKGFRNBOLGFNBKGFNBOGFNBFGB" << "\n";
	}

	constexpr auto translation = EmuMath::Helpers::matrix_make_translation<float>(1, 2, 3).Transpose();
	constexpr auto translated_test = EmuMath::Vector<3, float>(1, 1, 1) * translation;
	constexpr auto normal_mul_test = EmuMath::Vector<3, float>(1, 1, 1) * 29;
	constexpr auto hmm = EmuMath::Vector<3, float>(10, 10, 10) * (translation);
	constexpr auto bloog = -hmm;

	auto runtime_trans = EmuMath::Vector<3, float>(-5, 0, 5);
	std::cout << "Before trans: " << runtime_trans << "\n";
	runtime_trans *= translation;
	std::cout << "After trans: " << runtime_trans << "\n ";

	std::cout << "\n\n\nFast Matrix\n";
	EmuMath::FastMatrix<4, 4, float> fast_mat_4x4f;
	std::cout << fast_mat_4x4f << "\n\n";
	
	constexpr auto fast_mat_in_scalar_a = EmuMath::Helpers::matrix_ortho_vk<float, true>(0, 0, 1920, 1080, 0.001, 1000);
	constexpr auto fast_mat_in_scalar_b = EmuMath::Matrix<4, 4, float, true>(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);

	constexpr std::array<std::array<int, 3>, 3> matrix({ {1, 2, 3}, {4, 5, 6}, {7, 8, 9} });

	//constexpr auto fast8x8_in_a = EmuMath::Matrix<8, 7, float, false>
	//(
	//	1, 2, 3, 4, 5, 6, 7, 8,
	//	9, 10, 11, 12, 13, 14, 15, 16,
	//	17, 18, 19, 20, 21, 22, 23, 24,
	//	25, 26, 27, 28, 29, 30, 31, 32,
	//	33, 34, 35, 36, 37, 38, 39, 40,
	//	41, 42, 43, 44, 45, 46, 47, 48,
	//	49, 50, 51, 52, 53, 54, 55, 56
	//);
	//constexpr auto fast3x4_in_a = EmuMath::Matrix<3, 4, float, false>
	//(
	//	1, 2, 3,
	//	9, 10, 11,
	//	17, 18, 19,
	//	25, 26, 27
	//);
	//constexpr auto fast4x3_in_b = fast3x4_in_a.Transpose();
	//
	//auto fast3x4_a = EmuMath::FastMatrix<3, 4, float, false>
	//(
	//	EmuSIMD::load<EmuMath::FastMatrix<8, 8, float, false>::register_type>(fast3x4_in_a.data<0, 0>()),
	//	EmuSIMD::load<EmuMath::FastMatrix<8, 8, float, false>::register_type>(fast3x4_in_a.data<0, 1>()),
	//	EmuSIMD::load<EmuMath::FastMatrix<8, 8, float, false>::register_type>(fast3x4_in_a.data<0, 2>()),
	//	EmuSIMD::load<EmuMath::FastMatrix<8, 8, float, false>::register_type>(fast3x4_in_a.data<0, 3>())
	//);
	//auto fast4x3_b = EmuMath::FastMatrix<4, 3, float, false>
	//(
	//	EmuSIMD::load<EmuMath::FastMatrix<8, 8, float, false>::register_type>(fast4x3_in_b.data<0, 0>()),
	//	EmuSIMD::load<EmuMath::FastMatrix<8, 8, float, false>::register_type>(fast4x3_in_b.data<0, 1>()),
	//	EmuSIMD::load<EmuMath::FastMatrix<8, 8, float, false>::register_type>(fast4x3_in_b.data<0, 2>())
	//);
	//std::cout << fast3x4_a << "\nMUL\n" << fast4x3_b << "\n=\n" << fast3x4_a.Multiply(fast4x3_b) << "\n\n";
	//std::cout << "Scalar result:\n" << (fast3x4_in_a * fast4x3_in_b) << "\n\n";
	//std::cout << "REVERSED: " << fast3x4_a << "\nMUL\n" << fast4x3_b << "\n=\n" << fast4x3_b.Multiply(fast3x4_a) << "\n\n";
	//std::cout << "REVERSED: " << "Scalar result:\n" << (fast4x3_in_b * fast3x4_in_a) << "\n\n";










	constexpr bool tests_column_major = true;
	constexpr auto fast5x4_in_a = EmuMath::Matrix<5, 4, float, tests_column_major>
	(
		1, 2, 3, 4, 5,
		9, 10, 11, 12, 13,
		17, 18, 19, 20, 21,
		25, 26, 27, 28, 29
	);
	constexpr auto fast4x5_in_b = fast5x4_in_a.Transpose();

	auto fast5x4_a = EmuMath::FastMatrix<4, 5, float, tests_column_major>
	(
		EmuSIMD::load<EmuMath::FastMatrix<8, 8, float, tests_column_major>::register_type>(fast5x4_in_a.data<0, 0>()),
		EmuSIMD::load<EmuMath::FastMatrix<8, 8, float, tests_column_major>::register_type>(fast5x4_in_a.data<4, 0>()),
		EmuSIMD::load<EmuMath::FastMatrix<8, 8, float, tests_column_major>::register_type>(fast5x4_in_a.data<0, 1>()),
		EmuSIMD::load<EmuMath::FastMatrix<8, 8, float, tests_column_major>::register_type>(fast5x4_in_a.data<4, 1>()),
		EmuSIMD::load<EmuMath::FastMatrix<8, 8, float, tests_column_major>::register_type>(fast5x4_in_a.data<0, 2>()),
		EmuSIMD::load<EmuMath::FastMatrix<8, 8, float, tests_column_major>::register_type>(fast5x4_in_a.data<4, 2>()),
		EmuSIMD::load<EmuMath::FastMatrix<8, 8, float, tests_column_major>::register_type>(fast5x4_in_a.data<0, 3>()),
		EmuSIMD::load<EmuMath::FastMatrix<8, 8, float, tests_column_major>::register_type>(fast5x4_in_a.data<4, 3>())
	);
	auto fast4x5_b = EmuMath::FastMatrix<5, 4, float, tests_column_major>
	(
		EmuSIMD::load<EmuMath::FastMatrix<8, 8, float, tests_column_major>::register_type>(fast4x5_in_b.data<0, 0>()),
		EmuSIMD::load<EmuMath::FastMatrix<8, 8, float, tests_column_major>::register_type>(fast4x5_in_b.data<0, 1>()),
		EmuSIMD::load<EmuMath::FastMatrix<8, 8, float, tests_column_major>::register_type>(fast4x5_in_b.data<0, 2>()),
		EmuSIMD::load<EmuMath::FastMatrix<8, 8, float, tests_column_major>::register_type>(fast4x5_in_b.data<0, 3>()),
		EmuSIMD::load<EmuMath::FastMatrix<8, 8, float, tests_column_major>::register_type>(fast4x5_in_b.data<0, 4>())
	);
	std::cout << fast5x4_a << "\nMUL\n" << fast4x5_b << "\n=\n" << fast5x4_a.Multiply(fast4x5_b) << "\n\n";
	std::cout << "Scalar result:\n" << (fast5x4_in_a * fast4x5_in_b) << "\n\n";
	std::cout << "REVERSED: " << fast5x4_a << "\nMUL\n" << fast4x5_b << "\n=\n" << fast4x5_b.Multiply(fast5x4_a) << "\n\n";
	std::cout << "REVERSED: " << "Scalar result:\n" << (fast4x5_in_b * fast5x4_in_a) << "\n\n";






	constexpr auto fast8x8_in_a = EmuMath::Matrix<8, 7, float, tests_column_major>
	(
		1, 2, 3, 4, 5, 6, 7, 8,
		9, 10, 11, 12, 13, 14, 15, 16,
		17, 18, 19, 20, 21, 22, 23, 24,
		25, 26, 27, 28, 29, 30, 31, 32,
		33, 34, 35, 36, 37, 38, 39, 40,
		41, 42, 43, 44, 45, 46, 47, 48,
		49, 50, 51, 52, 53, 54, 55, 56
	);
	constexpr auto fast8x8_in_b = fast8x8_in_a.Transpose();
	
	//auto fast8x8_a = EmuMath::FastMatrix<8, 7, float, tests_column_major>
	//(
	//	EmuSIMD::load<EmuMath::FastMatrix<8, 8, float, tests_column_major>::register_type>(fast8x8_in_a.data<0, 0>()),
	//	EmuSIMD::load<EmuMath::FastMatrix<8, 8, float, tests_column_major>::register_type>(fast8x8_in_a.data<0, 4>()),
	//	EmuSIMD::load<EmuMath::FastMatrix<8, 8, float, tests_column_major>::register_type>(fast8x8_in_a.data<1, 0>()),
	//	EmuSIMD::load<EmuMath::FastMatrix<8, 8, float, tests_column_major>::register_type>(fast8x8_in_a.data<1, 4>()),
	//	EmuSIMD::load<EmuMath::FastMatrix<8, 8, float, tests_column_major>::register_type>(fast8x8_in_a.data<2, 0>()),
	//	EmuSIMD::load<EmuMath::FastMatrix<8, 8, float, tests_column_major>::register_type>(fast8x8_in_a.data<2, 4>()),
	//	EmuSIMD::load<EmuMath::FastMatrix<8, 8, float, tests_column_major>::register_type>(fast8x8_in_a.data<3, 0>()),
	//	EmuSIMD::load<EmuMath::FastMatrix<8, 8, float, tests_column_major>::register_type>(fast8x8_in_a.data<3, 4>()),
	//	EmuSIMD::load<EmuMath::FastMatrix<8, 8, float, tests_column_major>::register_type>(fast8x8_in_a.data<4, 0>()),
	//	EmuSIMD::load<EmuMath::FastMatrix<8, 8, float, tests_column_major>::register_type>(fast8x8_in_a.data<4, 4>()),
	//	EmuSIMD::load<EmuMath::FastMatrix<8, 8, float, tests_column_major>::register_type>(fast8x8_in_a.data<5, 0>()),
	//	EmuSIMD::load<EmuMath::FastMatrix<8, 8, float, tests_column_major>::register_type>(fast8x8_in_a.data<5, 4>()),
	//	EmuSIMD::load<EmuMath::FastMatrix<8, 8, float, tests_column_major>::register_type>(fast8x8_in_a.data<6, 0>()),
	//	EmuSIMD::load<EmuMath::FastMatrix<8, 8, float, tests_column_major>::register_type>(fast8x8_in_a.data<6, 4>()),
	//	EmuSIMD::load<EmuMath::FastMatrix<8, 8, float, tests_column_major>::register_type>(fast8x8_in_a.data<7, 0>()),
	//	EmuSIMD::load<EmuMath::FastMatrix<8, 8, float, tests_column_major>::register_type>(fast8x8_in_a.data<7, 4>())
	//);
	//auto fast8x8_b = EmuMath::FastMatrix<7, 8, float, tests_column_major>
	//(
	//	EmuSIMD::load<EmuMath::FastMatrix<8, 8, float, tests_column_major>::register_type>(fast8x8_in_b.data<0, 0>()),
	//	EmuSIMD::load<EmuMath::FastMatrix<8, 8, float, tests_column_major>::register_type>(fast8x8_in_b.data<0, 4>()),
	//	EmuSIMD::load<EmuMath::FastMatrix<8, 8, float, tests_column_major>::register_type>(fast8x8_in_b.data<1, 0>()),
	//	EmuSIMD::load<EmuMath::FastMatrix<8, 8, float, tests_column_major>::register_type>(fast8x8_in_b.data<1, 4>()),
	//	EmuSIMD::load<EmuMath::FastMatrix<8, 8, float, tests_column_major>::register_type>(fast8x8_in_b.data<2, 0>()),
	//	EmuSIMD::load<EmuMath::FastMatrix<8, 8, float, tests_column_major>::register_type>(fast8x8_in_b.data<2, 4>()),
	//	EmuSIMD::load<EmuMath::FastMatrix<8, 8, float, tests_column_major>::register_type>(fast8x8_in_b.data<3, 0>()),
	//	EmuSIMD::load<EmuMath::FastMatrix<8, 8, float, tests_column_major>::register_type>(fast8x8_in_b.data<3, 4>()),
	//	EmuSIMD::load<EmuMath::FastMatrix<8, 8, float, tests_column_major>::register_type>(fast8x8_in_b.data<4, 0>()),
	//	EmuSIMD::load<EmuMath::FastMatrix<8, 8, float, tests_column_major>::register_type>(fast8x8_in_b.data<4, 4>()),
	//	EmuSIMD::load<EmuMath::FastMatrix<8, 8, float, tests_column_major>::register_type>(fast8x8_in_b.data<5, 0>()),
	//	EmuSIMD::load<EmuMath::FastMatrix<8, 8, float, tests_column_major>::register_type>(fast8x8_in_b.data<5, 4>()),
	//	EmuSIMD::load<EmuMath::FastMatrix<8, 8, float, tests_column_major>::register_type>(fast8x8_in_b.data<6, 0>()),
	//	EmuSIMD::load<EmuMath::FastMatrix<8, 8, float, tests_column_major>::register_type>(fast8x8_in_b.data<6, 4>())
	//);
	//auto fast8x8_a = EmuMath::Helpers::fast_matrix_load<EmuMath::FastMatrix<8, 7, float, tests_column_major>>(fast8x8_in_a);
	//auto fast8x8_b = EmuMath::Helpers::fast_matrix_load<EmuMath::FastMatrix<7, 8, float, tests_column_major>>(fast8x8_in_b);
	auto fast8x8_a = EmuMath::FastMatrix<8, 7, float, tests_column_major>(fast8x8_in_a);
	auto fast8x8_b = EmuMath::FastMatrix<7, 8, float, tests_column_major>(fast8x8_in_b);

	std::cout << fast8x8_a << "\nMUL\n" << fast8x8_b << "\n=\n" << (fast8x8_a * fast8x8_b) << "\n\n";
	std::cout << "Scalar result:\n" << (fast8x8_in_a * fast8x8_in_b) << "\n\n";
	std::cout << "REVERSED: " << fast8x8_a << "\nMUL\n" << fast8x8_b << "\n=\n" << (fast8x8_b * fast8x8_a) << "\n\n";
	std::cout << "REVERSED: " << "Scalar result:\n" << (fast8x8_in_b * fast8x8_in_a) << "\n\n";












	constexpr auto fast4x4_in_a = EmuMath::Matrix<4, 4, float, tests_column_major>
	(
		1, 2, 3, 4,
		9, 10, 11, 12,
		17, 18, 19, 20,
		25, 26, 27, 28
	);
	constexpr auto fast4x4_in_b = fast4x4_in_a.Transpose();

	//auto fast4x4_a = EmuMath::FastMatrix<4, 4, float, tests_column_major>
	//(
	//	EmuSIMD::load<EmuMath::FastMatrix<8, 8, float, tests_column_major>::register_type>(fast4x4_in_a.data<0, 0>()),
	//	EmuSIMD::load<EmuMath::FastMatrix<8, 8, float, tests_column_major>::register_type>(fast4x4_in_a.data<1, 0>()),
	//	EmuSIMD::load<EmuMath::FastMatrix<8, 8, float, tests_column_major>::register_type>(fast4x4_in_a.data<2, 0>()),
	//	EmuSIMD::load<EmuMath::FastMatrix<8, 8, float, tests_column_major>::register_type>(fast4x4_in_a.data<3, 0>())
	//);
	//auto fast4x4_b = EmuMath::FastMatrix<4, 4, float, tests_column_major>
	//(
	//	EmuSIMD::load<EmuMath::FastMatrix<8, 8, float, tests_column_major>::register_type>(fast4x4_in_b.data<0, 0>()),
	//	EmuSIMD::load<EmuMath::FastMatrix<8, 8, float, tests_column_major>::register_type>(fast4x4_in_b.data<1, 0>()),
	//	EmuSIMD::load<EmuMath::FastMatrix<8, 8, float, tests_column_major>::register_type>(fast4x4_in_b.data<2, 0>()),
	//	EmuSIMD::load<EmuMath::FastMatrix<8, 8, float, tests_column_major>::register_type>(fast4x4_in_b.data<3, 0>())
	//);
	auto fast4x4_a = EmuMath::FastMatrix<4, 4, float, tests_column_major>(fast4x4_in_a);
	auto fast4x4_b = EmuMath::FastMatrix<4, 4, float, tests_column_major>(fast4x4_in_b);
	std::cout << fast4x4_a << "\nMUL\n" << fast4x4_b << "\n=\n" << fast4x4_a.Multiply(fast4x4_b) << "\n\n";
	std::cout << "Scalar result:\n" << (fast4x4_in_a * fast4x4_in_b) << "\n\n";
	std::cout << "REVERSED: " << fast4x4_a << "\nMUL\n" << fast4x4_b << "\n=\n" << fast4x4_b.Multiply(fast4x4_a) << "\n\n";
	std::cout << "REVERSED: " << "Scalar result:\n" << (fast4x4_in_b * fast4x4_in_a) << "\n\n";

	std::cout << EmuMath::FastMatrix<4, 4, float, true>(10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 101, 120, 130, 140, 150, 160) << "\n\n";
	std::cout << EmuMath::FastMatrix<4, 4, float, false>(10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 101, 120, 130, 140, 150, 160) << "\n\n";

	EmuMath::Matrix<5, 5, float, false> basic_store_test(1337);
	EmuMath::Helpers::fast_matrix_store(fast4x4_a, basic_store_test);
	std::cout << "STORED SCALAR:\n" << basic_store_test << "\n\nFAST VER:\n" << fast4x4_a << "\n\n";
	float test_out_floats[16] = { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 };
	std::cout << "Basic float array: ";
	PrintIndexable<16>(test_out_floats);
	std::cout << "\nAfter store: ";
	EmuMath::FastMatrix<3, 3, float, true>(1, 2, 3, 4, 5, 6, 7, 8, 9).Store<true>(test_out_floats);
	PrintIndexable<16>(test_out_floats);
	std::cout << "\n\n";

	std::cout << EmuMath::Helpers::fast_matrix_store
	(
		EmuMath::FastMatrix<4, 4, float, false>(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16)
	) << "\n\n";

	auto to_add_fast_a = EmuMath::FastMatrix<4, 4, float, true>(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
	auto to_add_fast_b = EmuMath::FastMatrix<2, 4, float, true>(10, 20, 30, 40, 50, 60, 70, 80);
	std::cout << to_add_fast_a << "\nPLUS\n" << to_add_fast_b << "\n=\n" << to_add_fast_a.Add(to_add_fast_b) << "\n\n";
	std::cout << to_add_fast_a << "\nSUB\n" << to_add_fast_b << "\n=\n" << to_add_fast_a.Subtract(to_add_fast_b) << "\n\n";
	std::cout << to_add_fast_a << "\nBASIC MUL\n" << to_add_fast_b << "\n=\n" << to_add_fast_a.BasicMultiply(to_add_fast_b) << "\n\n";
	std::cout << to_add_fast_a << "\nBASIC DIV\n" << to_add_fast_b << "\n=\n" << to_add_fast_a.BasicDivide(to_add_fast_b) << "\n\n";
	std::cout << to_add_fast_a << "\nBASIC MOD\n" << to_add_fast_b << "\n=\n" << to_add_fast_a.BasicMod(to_add_fast_b) << "\n\n";
	std::cout << "BASIC FMADD(\n" << to_add_fast_a << ",\n\n" << to_add_fast_b << ",\n\n" << 10 << "\n)=\n" << to_add_fast_a.BasicFmadd(to_add_fast_b, 10) << "\n\n";
	std::cout << "BASIC FMSUB(\n" << to_add_fast_a << ",\n\n" << to_add_fast_b << ",\n\n" << 10 << "\n)=\n" << to_add_fast_a.BasicFmsub(to_add_fast_b, 10) << "\n\n";

	std::cout << "\n\n---\n\n";
	float test_in_floats[20] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20 };
	std::cout << (to_add_fast_a *= EmuSIMD::setr<__m128>(10, 20, 30, 40)) << "\n\n";
	std::cout << (to_add_fast_a *= EmuMath::FastVector<4, float>(test_in_floats)) << "\n\n";
	std::cout << (to_add_fast_a *= EmuMath::FastVector<3, float>(test_in_floats)) << "\n\n";
	std::cout << (to_add_fast_a *= 5) << "\n\n";

	auto some_8x8_fast_mat = EmuMath::FastMatrix<8, 8, float, true, 256>
	(
		1, 2, 3, 4, 5, 6, 7, 8,
		9, 10, 11, 12, 13, 14, 15, 16,
		17, 18, 19, 20, 21, 22, 23, 24,
		25, 26, 27, 28, 29, 30, 31, 32,
		33, 34, 35, 36, 37, 38, 39, 40,
		41, 42, 43, 44, 45, 46, 47, 48,
		49, 50, 51, 52, 53, 54, 55, 56,
		57, 58, 59, 60, 61, 62, 63, 64
	);

	std::cout << "\n---\n";
	auto fast_mat_4x4_to_trans = EmuMath::FastMatrix<4, 4, float, true, 128>(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
	std::cout << fast_mat_4x4_to_trans << "\n\nTRANS:\n" << fast_mat_4x4_to_trans.Transpose() << "\n\n";

	EmuSIMD::append_simd_vector_to_stream<32, true>(std::cout, EmuSIMD::alternating_sign_mask<__m128, 32, false>()) << "\n";
	EmuSIMD::append_simd_vector_to_stream<32, true>(std::cout, EmuSIMD::alternating_sign_mask<__m128, 32, true>()) << "\n";
	EmuSIMD::append_simd_vector_to_stream<32, true>(std::cout, EmuSIMD::alternating_sign_mask_reverse<__m128, 32, false>()) << "\n";
	EmuSIMD::append_simd_vector_to_stream<32, true>(std::cout, EmuSIMD::alternating_sign_mask_reverse<__m128, 32, true>()) << "\n";
	EmuSIMD::append_simd_vector_to_stream<32, true>(std::cout, EmuSIMD::sign_mask<32, __m128, 0, 1, 1, 0>()) << "\n\n";

	float test_out_det = 0.0f;
	constexpr auto some_translation = (
		EmuMath::Helpers::matrix_make_rotation_3d<float, true>(EmuMath::Quaternion<float>::from_euler_constexpr(-30, 45, 90)) *
		EmuMath::Helpers::matrix_make_scale<4, 4, float, true>(25, 13, 9) *
		EmuMath::Helpers::matrix_make_translation<4, 4, float, true>(-17, 6, 28)
	);
	//auto some_fast_translation = EmuMath::FastMatrix<4, 4, float, true>(some_translation);
	auto some_fast_translation = EmuMath::FastMatrix<4, 4, float, true>
	(
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		1, 2, 3, 1
	);
	std::cout << some_fast_translation << "\n\n"
		<< EmuMath::Helpers::fast_matrix_inverse(some_fast_translation, test_out_det) << "\n";
	std::cout << "Det: " << test_out_det << "\n\n";

	std::cout << EmuMath::Helpers::fast_matrix_identity<4, 4, float, true>() << "\n\n";
	std::cout << EmuMath::Helpers::fast_matrix_identity<3, 4, float, true>() << "\n\n";
	std::cout << EmuMath::Helpers::fast_matrix_identity<4, 3, float, true>() << "\n\n";
	
	std::cout << some_8x8_fast_mat << "\n\n";
	EmuMath::Helpers::fast_matrix_assign_identity(some_8x8_fast_mat);
	std::cout << some_8x8_fast_mat << "\n\n";
	std::cout << EmuMath::Helpers::fast_matrix_identity<20, 20, std::int16_t, false, 256>() << "\n\n";

	std::cout << EmuMath::Helpers::fast_matrix_make_translation<float, true>(1, 2, 3) << "\n\n";
	std::cout << EmuMath::Helpers::fast_matrix_make_scale<float, true>(1, 2, 3, 4, 5, 6) << "\n\n";

	auto quat_for_fast_test = EmuMath::Quaternion<float>::from_euler(25, -60, 90);
	std::cout << EmuMath::Helpers::fast_matrix_make_rotation_3d<float>(quat_for_fast_test) << "\n\n";
	std::cout << EmuMath::Helpers::matrix_make_rotation_3d<float>(quat_for_fast_test) << "\n\n";



	std::cout << "\n\n---Fast Quaternion Tests---\n";
	std::cout << EmuMath::FastQuaternion<float>() << "\n";
	std::cout << EmuMath::FastQuaternion<float>(1, 2, 3, 4) << "\n";
	std::cout << EmuMath::FastQuaternion<float>(4, 3, 2, 1) << "\n";
	std::cout << EmuMath::FastQuaternion<float>(EmuMath::FastQuaternion<float>(4, 3, 2, 1)) << "\n";
	std::cout << EmuMath::FastQuaternion<float>(EmuMath::FastQuaternion<float>(4, 3, 2, 1).data) << "\n";
	//std::cout << EmuMath::FastQuaternion<double>(EmuSIMD::set1<__m128d, 64>(1337), EmuSIMD::set1<__m128d, 64>(-1337)) << "\n";
	std::cout << EmuMath::FastQuaternion<float>(EmuSIMD::set1<__m128, 64>(1337)) << "\n";

	EmuMath::Quaternion<float> just_a_test_quaternion_to_store_to(-1, -1, -1, -1);
	std::cout << just_a_test_quaternion_to_store_to << "\n";
	EmuMath::FastQuaternion<float, 256>(1, 2, 3, 4).Store(just_a_test_quaternion_to_store_to);
	std::cout << just_a_test_quaternion_to_store_to << "\n";

	constexpr bool r = false;
	constexpr bool n = false;
	constexpr float eulx = -45.0f;
	constexpr float euly = 93.0f;
	constexpr float eulz = 0;
	std::cout << EmuMath::FastQuaternion<float, 256>(EmuMath::Quaternion<float>::from_euler<r, n>(eulx, euly, eulz)) << " (Scalar f32)\n";
	std::cout << EmuMath::Helpers::fast_quaternion_from_euler<EmuMath::FastQuaternion<float>, r, n>(eulx, euly, eulz) << "(SIMD f32)\n";
	std::cout << EmuMath::FastQuaternion<double, 256>(EmuMath::Quaternion<double>::from_euler<r, n>(eulx, euly, eulz)) << " (Scalar f64)\n";
	std::cout << EmuMath::Helpers::fast_quaternion_from_euler<EmuMath::FastQuaternion<double, 256>, r, n>(eulx, euly, eulz) << "(SIMD f64)\n";
	std::cout << EmuMath::FastQuaternion<double, 128>(EmuMath::Quaternion<double>::from_euler<r, n>(eulx, euly, eulz)) << " (Scalar f64, 128)\n";
	std::cout << EmuMath::Helpers::fast_quaternion_from_euler<EmuMath::FastQuaternion<double, 128>, r, n>(eulx, euly, eulz) << "(SIMD f64, 128)\n";

	std::cout << "\n\n";
	auto some_m256d = EmuSIMD::setr<__m256d>(10, 20, 30, 40);
	auto some_other_m256d = EmuSIMD::setr<__m256d>(50, 60, 70, 80);
	EmuSIMD::append_simd_vector_to_stream(std::cout, some_m256d) << "\n";
	EmuSIMD::append_simd_vector_to_stream(std::cout, EmuSIMD::shuffle_full_width<0, 1, 2, 3>(some_m256d)) << "\n";
	EmuSIMD::append_simd_vector_to_stream(std::cout, EmuSIMD::shuffle_full_width<3, 2, 1, 0>(some_m256d)) << "\n";
	EmuSIMD::append_simd_vector_to_stream(std::cout, EmuSIMD::shuffle_full_width<2, 3, 1, 3>(some_m256d)) << "\n";

	EmuSIMD::append_simd_vector_to_stream(std::cout, EmuSIMD::shuffle_full_width<0, 1, 2, 3>(some_m256d, some_other_m256d)) << "\n";
	EmuSIMD::append_simd_vector_to_stream(std::cout, EmuSIMD::shuffle_full_width<3, 2, 1, 0>(some_m256d, some_other_m256d)) << "\n";
	EmuSIMD::append_simd_vector_to_stream(std::cout, EmuSIMD::shuffle_full_width<2, 3, 1, 3>(some_m256d, some_other_m256d)) << "\n";

	std::cout << "\nScalar result: " << EmuMath::Quaternion<float>::from_euler<false>(eulx, euly, eulz);
	std::cout << "\n\nSame conversion w/different args tests @FastQuaternion, f32\n";
	std::cout << "Scalars: " << EmuMath::FastQuaternion<float, 128>::from_euler<false>(eulx, euly, eulz) << "\n";
	std::cout << "Scalar Vector: " << EmuMath::FastQuaternion<float, 128>::from_euler<false>(EmuMath::Vector<3, float>(eulx, euly, eulz)) << "\n";
	std::cout << "Fast Vector: " << EmuMath::FastQuaternion<float, 128>::from_euler<false>(EmuMath::FastVector<3, float>(eulx, euly, eulz)) << "\n";
	std::cout << "SIMD: " << EmuMath::FastQuaternion<float, 128>::from_euler<false>(EmuSIMD::setr<__m128>(eulx, euly, eulz, 0)) << "\n";
	std::cout << "SIMD Arr: " 
		<< EmuMath::FastQuaternion<float, 128>::from_euler<false>(std::array<__m128, 2>({ EmuSIMD::setr<__m128>(eulx, euly, eulz, 0), __m128() }))
		<< "\n";

	std::cout << "\n\nSame conversion w/different args tests @FastQuaternion, f64\n";
	std::cout << "Scalars: " << EmuMath::FastQuaternion<double, 128>::from_euler<false>(eulx, euly, eulz) << "\n";
	std::cout << "Scalar Vector: " << EmuMath::FastQuaternion<double, 128>::from_euler<false>(EmuMath::Vector<3, double>(eulx, euly, eulz)) << "\n";
	std::cout << "Fast Vector: " << EmuMath::FastQuaternion<double, 128>::from_euler<false>(EmuMath::FastVector<3, double>(eulx, euly, eulz)) << "\n";
	std::cout << "SIMD: Not allowed with 128-bit f64\n";
	std::cout << "SIMD Arr: " 
		<< EmuMath::FastQuaternion<double, 128>::from_euler<false>(std::array<__m128d, 2>({ EmuSIMD::setr<__m128d>(eulx, euly), EmuSIMD::setr<__m128d>(eulz, 0) }))
		<< "\n";


	std::cout << "\n\nFastQuat -> Euler (Scalar)\n";
	std::cout << "Basic scalar (rads): " << EmuMath::Quaternion<float>::from_euler<false>(eulx, euly, eulz).ToEuler<true>() << "\n";
	std::cout << "Basic scalar (degs): " << EmuMath::Quaternion<float>::from_euler<false>(eulx, euly, eulz).ToEuler<false>() << "\n";
	std::cout << EmuMath::FastQuaternion<float>::from_euler<false>(eulx, euly, eulz).ToEulerScalar() << "\n";
	std::cout << EmuMath::FastQuaternion<float>::from_euler<false>(eulx, euly, eulz).ToEulerScalar<false>() << "\n";
	std::cout << EmuMath::FastQuaternion<float>::from_euler<false>(eulx, euly, eulz).ToEulerScalar<true, void, 20>() << "\n";
	std::cout << EmuMath::FastQuaternion<float>::from_euler<false>(eulx, euly, eulz).ToEulerScalar<true, float, 20>() << "\n";
	std::cout << EmuMath::FastQuaternion<float>::from_euler<false>(eulx, euly, eulz).ToEulerScalar<true, int>() << "\n";

	std::cout << "\n\nFastQuat -> Euler (Fast)\n";
	std::cout << EmuMath::FastQuaternion<float>::from_euler<false>(eulx, euly, eulz).ToEuler() << "\n";
	std::cout << EmuMath::FastQuaternion<float>::from_euler<false>(eulx, euly, eulz).ToEuler<false>() << "\n";
	std::cout << EmuMath::FastQuaternion<float>::from_euler<false>(eulx, euly, eulz).ToEuler<true, 20>() << "\n";
	std::cout << EmuMath::FastQuaternion<float>::from_euler<false>(eulx, euly, eulz).ToEuler<true, 20>() << "\n";
	std::cout << EmuMath::FastQuaternion<float>::from_euler<false>(eulx, euly, eulz).ToEuler<true>() << "\n";

	std::cout << "\n\nFastQuat * FastQuat\n";
	constexpr auto zero_rot_quat_from_euler = EmuMath::Quaternion<float>::from_euler_constexpr<false>(0, 0, 0);
	constexpr auto lhs_quat_test = EmuMath::Quaternion<float>::from_euler_constexpr<false>(eulx, euly, eulz);
	constexpr auto rhs_quat_test = EmuMath::Quaternion<float>::from_euler_constexpr<false>(eulz, euly, eulx);
	constexpr auto lhs_mul_rhs_quat_test = lhs_quat_test * rhs_quat_test;
	auto lhs_quat_runtime = lhs_quat_test;
	auto lhs_quat_fast_runtime_a = EmuMath::FastQuaternion<float>(lhs_quat_test);
	auto lhs_quat_fast_runtime_b = EmuMath::FastQuaternion<double, 128>(lhs_quat_test);
	auto lhs_quat_fast_runtime_c = EmuMath::FastQuaternion<double, 256>(lhs_quat_test);
	std::cout << "Expected: " << lhs_mul_rhs_quat_test << "\n";
	std::cout << "Fast Res: " << (EmuMath::FastQuaternion<float>(lhs_quat_test) * EmuMath::FastQuaternion<float>(rhs_quat_test)) << "\n";
	std::cout << "Fast Res: " << (EmuMath::FastQuaternion<double, 256>(lhs_quat_test) * EmuMath::FastQuaternion<double, 256>(rhs_quat_test)) << "\n";
	std::cout << "Fast Res: " << (EmuMath::FastQuaternion<double, 128>(lhs_quat_test) * EmuMath::FastQuaternion<double, 128>(rhs_quat_test)) << "\n";
	std::cout << "---\nExpected: " << (lhs_quat_test * 10.5f) << "\n";
	std::cout << "Fast Res: " << (EmuMath::FastQuaternion<float>(lhs_quat_test) * 10.5f) << "\n";
	std::cout << "Fast Res: " << (EmuMath::FastQuaternion<double, 256>(lhs_quat_test) * 10.5f) << "\n";
	std::cout << "Fast Res: " << (EmuMath::FastQuaternion<double, 128>(lhs_quat_test) * 10.5f) << "\n";
	std::cout << "---\nExpected: " << (lhs_quat_test / 10.5f) << "\n";
	std::cout << "Fast Res: " << (EmuMath::FastQuaternion<float>(lhs_quat_test) / 10.5f) << "\n";
	std::cout << "Fast Res: " << (EmuMath::FastQuaternion<double, 256>(lhs_quat_test) / 10.5f) << "\n";
	std::cout << "Fast Res: " << (EmuMath::FastQuaternion<double, 128>(lhs_quat_test) / 10.5f) << "\n";
	std::cout << "---\nExpected: " << (lhs_quat_test + rhs_quat_test) << "\n";
	std::cout << "Fast Res: " << (EmuMath::FastQuaternion<float>(lhs_quat_test) + EmuMath::FastQuaternion<float>(rhs_quat_test)) << "\n";
	std::cout << "Fast Res: " << (EmuMath::FastQuaternion<double, 256>(lhs_quat_test) + EmuMath::FastQuaternion<double, 256>(rhs_quat_test)) << "\n";
	std::cout << "Fast Res: " << (EmuMath::FastQuaternion<double, 128>(lhs_quat_test) + EmuMath::FastQuaternion<double, 128>(rhs_quat_test)) << "\n";
	std::cout << "---\nExpected: " << (lhs_quat_test - rhs_quat_test) << "\n";
	std::cout << "Fast Res: " << (EmuMath::FastQuaternion<float>(lhs_quat_test) - EmuMath::FastQuaternion<float>(rhs_quat_test)) << "\n";
	std::cout << "Fast Res: " << (EmuMath::FastQuaternion<double, 256>(lhs_quat_test) - EmuMath::FastQuaternion<double, 256>(rhs_quat_test)) << "\n";
	std::cout << "Fast Res: " << (EmuMath::FastQuaternion<double, 128>(lhs_quat_test) - EmuMath::FastQuaternion<double, 128>(rhs_quat_test)) << "\n";
	std::cout << "---\nExpected: [\n\t" << (lhs_quat_runtime *= rhs_quat_test) << "\n";
	std::cout << "\t" << (lhs_quat_runtime *= 10.5f) << "\n";
	std::cout << "\t" << (lhs_quat_runtime /= 5.0f) << "\n";
	std::cout << "\t" << (lhs_quat_runtime += lhs_quat_test) << "\n";
	std::cout << "\t" << (lhs_quat_runtime -= rhs_quat_test) << "\n]\n";
	std::cout << "---\nFast Res: [\n\t" << (lhs_quat_fast_runtime_a *= decltype(lhs_quat_fast_runtime_a)(rhs_quat_test)) << "\n";
	std::cout << "\t" << (lhs_quat_fast_runtime_a *= 10.5f) << "\n";
	std::cout << "\t" << (lhs_quat_fast_runtime_a /= 5.0f) << "\n";
	std::cout << "\t" << (lhs_quat_fast_runtime_a += decltype(lhs_quat_fast_runtime_a)(lhs_quat_test)) << "\n";
	std::cout << "\t" << (lhs_quat_fast_runtime_a -= decltype(lhs_quat_fast_runtime_a)(rhs_quat_test)) << "\n]\n";
	std::cout << "---\nFast Res: [\n\t" << (lhs_quat_fast_runtime_b *= decltype(lhs_quat_fast_runtime_b)(rhs_quat_test)) << "\n";
	std::cout << "\t" << (lhs_quat_fast_runtime_b *= 10.5f) << "\n";
	std::cout << "\t" << (lhs_quat_fast_runtime_b /= 5.0f) << "\n";
	std::cout << "\t" << (lhs_quat_fast_runtime_b += decltype(lhs_quat_fast_runtime_b)(lhs_quat_test)) << "\n";
	std::cout << "\t" << (lhs_quat_fast_runtime_b -= decltype(lhs_quat_fast_runtime_b)(rhs_quat_test)) << "\n]\n";
	std::cout << "---\nFast Res: [\n\t" << (lhs_quat_fast_runtime_c *= decltype(lhs_quat_fast_runtime_c)(rhs_quat_test)) << "\n";
	std::cout << "\t" << (lhs_quat_fast_runtime_c *= 10.5f) << "\n";
	std::cout << "\t" << (lhs_quat_fast_runtime_c /= 5.0f) << "\n";
	std::cout << "\t" << (lhs_quat_fast_runtime_c += decltype(lhs_quat_fast_runtime_c)(lhs_quat_test)) << "\n";
	std::cout << "\t" << (lhs_quat_fast_runtime_c -= decltype(lhs_quat_fast_runtime_c)(rhs_quat_test)) << "\n]\n";

	std::cout << "\n\n\n---CMP TESTS---\n";
	std::cout << (EmuMath::FastQuaternion<float>(1, 2, 3, 4) == EmuMath::FastQuaternion<float>(1, 2, 3, 4)) << "\n";
	std::cout << (EmuMath::FastQuaternion<float>(1, 2, 3, 4) != EmuMath::FastQuaternion<float>(1, 2, 3, 4)) << "\n";
	std::cout << EmuMath::FastQuaternion<float>(1, 2, 3, 4).CmpNear(EmuMath::FastQuaternion<float>(1, 2, 3, 4)) << "\n";
	std::cout << (EmuMath::FastQuaternion<double>(1, 2, 3, 4) == EmuMath::FastQuaternion<double>(1, 2, 3, 4)) << "\n";
	std::cout << (EmuMath::FastQuaternion<double>(1, 2, 3, 4) != EmuMath::FastQuaternion<double>(1, 2, 3, 4)) << "\n";
	std::cout << EmuMath::FastQuaternion<double>(1, 2, 3, 4).CmpNear(EmuMath::FastQuaternion<double>(1, 2, 3, 4)) << "\n";
	auto cmptesta = EmuMath::FastQuaternion<float, 256>(EmuSIMD::setr<__m256>(1, 2, 3, 4, 5, 6, 7, 8));
	auto cmptestb = EmuMath::FastQuaternion<float, 256>(EmuSIMD::setr<__m256>(1, 2, 3, 4, 9, 10, 11, 12));
	std::cout << (cmptesta == cmptestb) << "\n";
	std::cout << (cmptesta != cmptestb) << "\n";
	std::cout << cmptesta.CmpNear(cmptestb) << "\n";
	std::cout << "---\n";
	std::cout << (EmuMath::FastQuaternion<float>(1, 2, 3, 4) == EmuMath::FastQuaternion<float>(1, 2, 3, 217)) << "\n";
	std::cout << (EmuMath::FastQuaternion<float>(1, 2, 3, 4) != EmuMath::FastQuaternion<float>(1, 2, 3, 217)) << "\n";
	std::cout << EmuMath::FastQuaternion<float>(1, 2, 3, 4).CmpNear(EmuMath::FastQuaternion<float>(1, 2, 3, 217)) << "\n";
	std::cout << (EmuMath::FastQuaternion<double>(1, 2, 3, 4) == EmuMath::FastQuaternion<double>(1, 2, 3, 217)) << "\n";
	std::cout << (EmuMath::FastQuaternion<double>(1, 2, 3, 4) != EmuMath::FastQuaternion<double>(1, 2, 3, 217)) << "\n";
	std::cout << EmuMath::FastQuaternion<double>(1, 2, 3, 4).CmpNear(EmuMath::FastQuaternion<double>(1, 2, 3, 217)) << "\n";
	auto cmptestc = EmuMath::FastQuaternion<float, 256>(EmuSIMD::setr<__m256>(1, 2, 3, 4, 5, 6, 7, 8));
	auto cmptestd = EmuMath::FastQuaternion<float, 256>(EmuSIMD::setr<__m256>(1, 2, 3, 217, 9, 10, 11, 12));
	std::cout << (cmptestc == cmptestd) << "\n";
	std::cout << (cmptestc != cmptestd) << "\n";
	std::cout << cmptestc.CmpNear(cmptestd) << "\n";

	universal_pause();;
	// // ##### SCALAR vs SIMD NOISE #####
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
	//universal_pause();;
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
	//*/

	/*
	// Some tests to see disassembly
	EmuMath::FastVector<4, float> veca((rand() % 100) * 0.33f, (rand() % 100) * 0.33f, (rand() % 100) * 0.33f, (rand() % 100) * 0.33f);
	EmuMath::FastVector<4, float> vecb((rand() % 100) * 0.33f, (rand() % 100) * 0.33f, (rand() % 100) * 0.33f, (rand() % 100) * 0.33f);
	auto result = veca + vecb;
	std::cout << veca << " + " << vecb << " = " << result << "\n";
	// */

#pragma region TEST_HARNESS_EXECUTION
	universal_pause();;
	EmuCore::TestingHelpers::PerformTests();
#pragma endregion
	//std::cout << result.Add(rand()) << " :)";
	return 0;
}
