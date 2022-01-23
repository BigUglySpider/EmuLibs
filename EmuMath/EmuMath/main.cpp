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
	std::cout << "Column 0: " << some_mat_4x2f_cm_.ColumnAt<0>() << "\n";
	std::cout << "Column 3: " << some_mat_4x2f_cm_.ColumnAt<3>() << "\n";
	std::cout << "Row 0: " << some_mat_4x2f_cm_.RowAt<0>() << "\n";
	std::cout << "Row 3: " << some_mat_4x2f_cm_.RowAt<1>() << "\n";

	some_mat_4x2f_cm_.RowAt<0>().at<2>() = 1337.0f;
	some_mat_4x2f_cm_.ColumnAt<0>().at<1>() = -1337.0f;
	std::cout << some_mat_4x2f_cm_ << "\n";

	std::cout << "\n---\n";
	constexpr auto some_mat_4x4f_cm_ = EmuMath::Matrix<4, 4, float, true>
	(
		0, 1, 2, 3,
		4, 5, 6, 7,
		8, 9, 10, 11,
		12, 13, 14, 15
	);

	constexpr auto some_mat_4x3f_cm_ = EmuMath::Matrix<4, 3, float, true>
	(
		0, 1, 2,
		4, 5, 6,
		8, 9, 10,
		12, 13, 14
	);

	constexpr auto some_mat_3x4f_cm_ = EmuMath::Matrix<3, 4, float, true>
	(
		0, 1, 2, 4,
		5, 6, 8, 9,
		10, 12, 13, 14
	);
	
	constexpr auto some_mat_3x4f_rm_ = EmuMath::Matrix<3, 4, float, false>
	(
		0, 1, 2,
		4, 5, 6,
		8, 9, 10,
		12, 13, 14
	);

	std::cout << some_mat_3x4f_cm_ << "\n\n";
	std::cout << some_mat_3x4f_rm_ << "\n\n";

	constexpr auto some_mat_3x4f_cm_copy_ = EmuMath::Matrix<3, 4, float, true>(some_mat_3x4f_cm_);
	constexpr auto column_1_ = some_mat_3x4f_cm_copy_.ColumnAt<1>();
	constexpr auto row_2_ = some_mat_3x4f_cm_copy_.RowAt<2>().Cast<float>();

	constexpr auto theoretical_test_0_ = some_mat_3x4f_cm_.AtTheoretical<25>();
	constexpr auto theoretical_test_1_ = some_mat_3x4f_cm_.AtTheoretical<3>();
	constexpr auto theoretical_test_2_ = some_mat_3x4f_cm_.AtTheoretical<1, 2>();
	constexpr auto theoretical_test_3_ = some_mat_3x4f_cm_.AtTheoretical<0, 25>();
	constexpr auto theoretical_test_4_ = some_mat_3x4f_cm_.AtTheoretical<25, 0>();
	constexpr auto theoretical_test_5_ = some_mat_3x4f_cm_.AtTheoretical<25, 25>();

	EmuMath::Matrix<3, 4, float, false> tester_;
	constexpr auto zero_ = tester_.get_implied_zero();
	constexpr auto zero_column_ = tester_.get_implied_zero_column();
	constexpr auto zero_row_ = tester_.get_implied_zero_row();
	constexpr auto zero_major_ = tester_.get_implied_zero_major();
	constexpr auto zero_non_major_ = tester_.get_implied_zero_non_major();

	auto column_theoretical_0_ = tester_.ColumnAtTheoretical<0>();
	auto column_theoretical_1_ = tester_.ColumnAtTheoretical<25>();
	auto& row_theoretical_0_ = tester_.RowAtTheoretical<0>();
	auto row_theoretical_1_ = tester_.RowAtTheoretical<25>();
	auto& major_theoretical_0_ = tester_.MajorAtTheoretical<0>();
	auto major_theoretical_1_ = tester_.MajorAtTheoretical<25>();
	auto non_major_theoretical_0_ = tester_.NonMajorAtTheoretical<0>();
	auto non_major_theoretical_1_ = tester_.NonMajorAtTheoretical<25>();

	std::cout << "\n---\n";
	constexpr auto read_mat_cm_ = EmuMath::Matrix<4, 4, float, true>(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
	constexpr auto read_mat_rm_ = EmuMath::Matrix<4, 4, float, false>(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
	std::cout << "Column Major:\n" << read_mat_cm_ << "\n\nRow Major:\n" << read_mat_rm_ << "\n\n";

	std::cout << "\n---\n";
	constexpr auto mat_from_vecs_cm_ = EmuMath::Matrix<4, 3, float, true>
	(
		EmuMath::Vector<3, float>(1, 2, 3),
		EmuMath::Vector<3, float>(4, 5, 6),
		EmuMath::Vector<3, float>(7, 8, 9),
		EmuMath::Vector<3, float>(10, 11, 12)
	);
	constexpr auto mat_from_vecs_rm_ = EmuMath::Matrix<4, 3, float, false>
	(
		EmuMath::Vector<4, float>(1, 2, 3, 4),
		EmuMath::Vector<4, float>(5, 6, 7, 8),
		EmuMath::Vector<4, float>(9, 10, 11, 12)
	);

	std::cout << "\n---\n";
	constexpr auto mat_from_vec_move_cm_ = EmuMath::Matrix<4, 3, float, true>
	(
		EmuMath::Matrix<4, 3, float, true>::matrix_vector_type
		(
			EmuMath::Vector<3, float>(1, 2, 3),
			EmuMath::Vector<3, float>(4, 5, 6),
			EmuMath::Vector<3, float>(7, 8, 9),
			EmuMath::Vector<3, float>(10, 11, 12)
		)
	);
	constexpr auto mat_from_vec_move_rm_ = EmuMath::Matrix<4, 3, float, false>
	(
		EmuMath::Matrix<4, 3, float, false>::matrix_vector_type
		(
			EmuMath::Vector<4, float>(1, 2, 3, 4),
			EmuMath::Vector<4, float>(5, 6, 7, 8),
			EmuMath::Vector<4, float>(9, 10, 11, 12)
		)
	);

	std::cout << "\n---\n";
	constexpr auto main_diagonal_cm_normal_ = mat_from_vec_move_cm_.MainDiagonal();
	constexpr auto main_diagonal_rm_normal_ = mat_from_vec_move_rm_.MainDiagonal();
	constexpr auto main_diagonal_cm_smaller_no_offset_ = mat_from_vec_move_cm_.MainDiagonal<2>();
	constexpr auto main_diagonal_rm_smaller_no_offset_ = mat_from_vec_move_rm_.MainDiagonal<2>();
	constexpr auto main_diagonal_cm_smaller_offset_ = mat_from_vec_move_cm_.MainDiagonal<2, 1>();
	constexpr auto main_diagonal_rm_smaller_offset_ = mat_from_vec_move_rm_.MainDiagonal<2, 1>();
	constexpr auto main_diagonal_cm_larger_no_offset_ = mat_from_vec_move_cm_.MainDiagonal<5>();
	constexpr auto main_diagonal_rm_larger_no_offset_ = mat_from_vec_move_rm_.MainDiagonal<5>();
	constexpr auto main_diagonal_cm_larger_offset_ = mat_from_vec_move_cm_.MainDiagonal<5, 25>();
	constexpr auto main_diagonal_rm_larger_offset_ = mat_from_vec_move_rm_.MainDiagonal<5, 25>();

	EmuMath::Matrix<4, 4, float, true> runtime_mat_4x4f_cm_(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
	std::cout << runtime_mat_4x4f_cm_ << "\n\n";
	runtime_mat_4x4f_cm_.MainDiagonal<float&>() *= 10.0f;
	std::cout << runtime_mat_4x4f_cm_ << "\n\n";

	std::cout << "\n---\n";
	constexpr auto mat_to_copy_cm_ = EmuMath::Matrix<4, 4, float, true>(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
	constexpr auto mat_to_copy_rm_ = EmuMath::Matrix<4, 4, float, false>(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);

	std::cout << "Full CM:\n" << mat_to_copy_cm_ << "\n\nFull RM:\n" << mat_to_copy_rm_ << "\n\n";

	constexpr auto copy_mat_2x4i32_cm_from_cm_ = EmuMath::Helpers::matrix_copy<2, 4, std::int32_t, true>(mat_to_copy_cm_);
	constexpr auto copy_mat_2x4i32_cm_from_rm_ = EmuMath::Helpers::matrix_copy<2, 4, std::int32_t, true>(mat_to_copy_rm_);
	std::cout << "CM FROM CM:\n" << copy_mat_2x4i32_cm_from_cm_ << "\n\nCM FROM RM:\n" << copy_mat_2x4i32_cm_from_rm_ << "\n\n";

	constexpr auto copy_mat_2x4i32_rm_from_cm_ = EmuMath::Helpers::matrix_copy<2, 4, std::int32_t, false>(mat_to_copy_cm_);
	constexpr auto copy_mat_2x4i32_rm_from_rm_ = EmuMath::Helpers::matrix_copy<2, 4, std::int32_t, false>(mat_to_copy_rm_);
	std::cout << "RM FROM CM:\n" << copy_mat_2x4i32_rm_from_cm_ << "\n\nRM FROM RM:\n" << copy_mat_2x4i32_rm_from_rm_ << "\n\n";

	std::cout << "\n---\n";
	constexpr auto constructed_copy_ = EmuMath::Matrix<12, 7, long double, true>(copy_mat_2x4i32_cm_from_rm_);
	std::cout << constructed_copy_ << "\n\n";

	constexpr auto moved_copy_ = EmuMath::Matrix<4, 4, float, true>
	(
		EmuMath::Matrix<5, 3, float, false>
		(
			0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14
		)
	);

	std::cout << "\n---\n";
	auto mat_to_ref_ = EmuMath::Matrix<4, 4, float, true>(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
	auto ref_copy_ = EmuMath::Matrix<3, 3, float&, true>(mat_to_ref_);
	std::cout << "Mat:\n" << mat_to_ref_ << "\n\nRef Mat:\n" << ref_copy_ << "\n\n";
	ref_copy_ = EmuMath::Matrix<2, 6, float, true>(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12);
	std::cout << "Mat:\n" << mat_to_ref_ << "\n\nRef Mat:\n" << ref_copy_ << "\n\n";

	std::cout << "\n---\n";

	constexpr auto mut_result_scalars_ = EmuMath::Helpers::matrix_mutate<EmuCore::do_add<void>, 4, 3, float, true>(1, 2);
	constexpr auto mut_result_matrices_ = EmuMath::Helpers::matrix_mutate<EmuCore::do_add<void>, 3, 4, float, true>
	(
		EmuMath::Matrix<3, 3, float, true>(10, 20, 30, 40, 50, 60, 70, 80, 90),
		27
	);
	constexpr auto mut_result_passed_ = EmuMath::Helpers::matrix_mutate<4, 4, float, false>
	(
		EmuCore::do_bitwise_or<std::uint16_t, std::uint16_t>(),
		std::uint16_t(1),
		EmuMath::Matrix<3, 3, std::uint16_t, false>(1, 2, 4, 5, 8, 0, 2, 4, 12)
	);

	auto runtime_to_mutate_ = EmuMath::Matrix<4, 4, float, true>(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
	std::cout << runtime_to_mutate_ << "\n\n";
	EmuMath::Helpers::matrix_mutate_to<1, 2, 0, 3, 0, 0>(runtime_to_mutate_, EmuCore::do_multiply<void>(), 2, 25);
	std::cout << runtime_to_mutate_ << "\n\n";
	EmuMath::Helpers::matrix_mutate_to<2, 3, 1, 4, 1, 1>
	(
		runtime_to_mutate_,
		EmuCore::do_add<void>(),
		EmuMath::Matrix<4, 4, float, true>(10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120, 130, 140, 150, 160),
		1
	);
	std::cout << runtime_to_mutate_ << "\n\n";
	EmuMath::Helpers::matrix_mutate_to<EmuCore::do_multiply<void>>
	(
		runtime_to_mutate_,
		0.5f,
		EmuMath::Matrix<3, 3, double, false>(1, 2, 3, 4, 5, 6, 7, 8, 9)
	);
	std::cout << runtime_to_mutate_ << "\n\n";

	std::cout << "\n---\n";
	constexpr auto one_mat_ = EmuMath::Matrix<4, 4, float, true>(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
	constexpr auto inner_multiplied_mat_ = EmuMath::Helpers::matrix_mutate_copy<EmuCore::do_multiply, 4, 4, float, true, 1, 3, 1, 3>(one_mat_, one_mat_, 5.0f);
	std::cout << inner_multiplied_mat_ << "\n\n";
	constexpr auto inner_subtracted_mat_ = EmuMath::Helpers::matrix_mutate_copy<4, 4, float, true, 1, 3, 1, 3>(one_mat_, EmuCore::do_subtract<void>(), one_mat_, one_mat_);
	std::cout << inner_subtracted_mat_ << "\n\n";

	std::cout << "\n---\n";
	auto another_runtime_mat_ = EmuMath::Matrix<5, 5, float, true>(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25);
	auto mat_to_copy = EmuMath::Matrix<6, 6, float, true>(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36);
	auto another_mat_to_copy_ = EmuMath::Matrix<5, 5, int, true>(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25);
	std::cout << another_runtime_mat_ << "\n\n";
	EmuMath::Helpers::matrix_mutate_copy_to<1, 4, 1, 4>(another_runtime_mat_, mat_to_copy, EmuCore::do_multiply<void>(), another_runtime_mat_, 0);
	std::cout << another_runtime_mat_ << "\n\n";
	EmuMath::Helpers::matrix_mutate_copy_to<EmuCore::do_add, 1, 4, 1, 4>(another_runtime_mat_, another_mat_to_copy_, another_runtime_mat_, 50);
	std::cout << another_runtime_mat_ << "\n\n";

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

#pragma region TEST_HARNESS_EXECUTION
	system("pause");
	EmuCore::TestingHelpers::PerformTests();
#pragma endregion
	return 0;
}
