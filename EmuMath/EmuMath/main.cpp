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
	using Mat4x4f32CM = EmuMath::Matrix<4, 4, float, true>;
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
	auto member_rot_runtime = Mat4x4f32CM::make_rotation_3d_z<false>(33);
	constexpr auto member_rot = Mat4x4f32CM::make_rotation_3d_z_constexpr<4, true, false>(33);
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

	system("pause");
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

	system("pause");
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
	//*/

	/*
	// Some tests to see disassembly
	EmuMath::FastVector<4, float> veca((rand() % 100) * 0.33f, (rand() % 100) * 0.33f, (rand() % 100) * 0.33f, (rand() % 100) * 0.33f);
	EmuMath::FastVector<4, float> vecb((rand() % 100) * 0.33f, (rand() % 100) * 0.33f, (rand() % 100) * 0.33f, (rand() % 100) * 0.33f);
	auto result = veca + vecb;
	std::cout << veca << " + " << vecb << " = " << result << "\n";
	// */

#pragma region TEST_HARNESS_EXECUTION
	system("pause");
	EmuCore::TestingHelpers::PerformTests();
#pragma endregion
	//std::cout << result.Add(rand()) << " :)";
	return 0;
}
