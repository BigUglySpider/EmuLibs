#include "EmuMath/Vector.h"
#include "EmuMath/FastVector.h"
#include "EmuMath/Matrix.h"
#include "EmuMath/NoOverflowT.h"
#include "EmuCore/TMPHelpers/Tuples.h"
#include <array>
#include <bitset>
#include <iomanip>

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

int main()
{
	srand(static_cast<unsigned int>(time(0)));

	EmuMath::Vector<4, double> _1(4.0f, 5.0f, 6.0f, 37.0f);

	EmuMath::Matrix<4, 4, float, true> matrix_
	(
		EmuMath::Vector4<float>(0.0f, 1.0f, 2.0f, 3.0f),
		std::move(_1),
		EmuMath::Vector4<std::uint8_t>(8.0f, 9.0f, 10.0f, 11.0f),
		EmuMath::Vector4<std::uint64_t>(12.0f, 13.0f, 14.0f, 15.0f)
	);


	std::cout << matrix_ << "\n";
	std::cout << "[2]: " << matrix_[2] << "\n";
	std::cout << "[7]: " << matrix_[7] << "\n";
	std::cout << "[13]: " << matrix_[13] << "\n";
	std::cout << "[15]: " << matrix_[15] << "\n";
	std::cout << "Column 3: " << matrix_.GetColumn<3>() << "\n";
	std::cout << "Row 2: " << matrix_.GetRow<2>() << "\n";
	
	std::cout << matrix_ << "\n";

	using test_type = EmuCore::TMPHelpers::tuple_n<10, float>::type;

	constexpr auto vec_ = (EmuMath::Vector<10, float>(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f));;
	constexpr test_type tuple_ = EmuMath::Helpers::VectorAsTuple(vec_);
	std::cout << std::get<0>(tuple_) << "\n";

	constexpr auto column_ = EmuMath::Helpers::VectorToColumnMatrix<true>(vec_);
	constexpr auto row_ = EmuMath::Helpers::VectorToRowMatrix<true>(vec_);
	std::cout << column_ << "\n";
	std::cout << row_ << "\n";

	auto out_a_ = EmuMath::Helpers::MatrixGetTheoretical<2, 2>(matrix_);
	auto out_b_ = EmuMath::Helpers::MatrixGetTheoretical<2, 5>(matrix_);
	auto out_c_ = EmuMath::Helpers::MatrixGetTheoretical<13>(matrix_);
	auto out_d_ = EmuMath::Helpers::MatrixGetTheoretical<16>(matrix_);

	constexpr EmuMath::Matrix<4, 4, float, true> mat_a_
	(
		EmuMath::Vector4<float>(1.0f, 2.0f, 3.0f, 4.0f),
		EmuMath::Vector4<float>(5.0f, 6.0f, 7.0f, 8.0f),
		EmuMath::Vector4<float>(9.0f, 10.0f, 11.0f, 12.0f),
		EmuMath::Vector4<float>(13.0f, 14.0f, 15.0f, 16.0f)
	);
	constexpr EmuMath::Matrix<4, 4, float, true> mat_b_
	(
		EmuMath::Vector4<float>(1.0f + 16.0f, 2.0f + 16.0f, 3.0f + 16.0f, 4.0f + 16.0f),
		EmuMath::Vector4<float>(5.0f + 16.0f, 6.0f + 16.0f, 7.0f + 16.0f, 8.0f + 16.0f),
		EmuMath::Vector4<float>(9.0f + 16.0f, 10.0f + 16.0f, 11.0f + 16.0f, 12.0f + 16.0f),
		EmuMath::Vector4<float>(13.0f + 16.0f, 14.0f + 16.0f, 15.0f + 16.0f, 16.0f + 16.0f)
	);
	constexpr auto mat_res_ = EmuMath::Helpers::MatrixDivideBasic<long double>(mat_a_, mat_b_);
	constexpr auto mat_res_scalar_ = EmuMath::Helpers::MatrixDivideBasic(mat_a_, 25.0f);

	std::cout << mat_res_scalar_ << "\n";

	constexpr auto mat_mult = EmuMath::Helpers::MatrixMultiply<float, true>(mat_a_, mat_b_);

	std::cout << "\n\n";
	std::cout << mat_a_ << "\nMULT\n" << mat_b_ << "\n:\n" << mat_mult << "\n";

	constexpr auto mat_c_ = EmuMath::Matrix<5, 2, float, true>
	(
		EmuMath::Vector<2, float>(2.0f, 4.0f),
		EmuMath::Vector<2, float>(6.0f, 8.0f),
		EmuMath::Vector<2, float>(10.0f, 12.0f),
		EmuMath::Vector<2, float>(14.0f, 16.0f),
		EmuMath::Vector<2, float>(18.0f, 20.0f)
	);
	constexpr auto mat_d_ = EmuMath::Matrix<3, 5, double, false>
	(
		EmuMath::Vector<2, double>(13.0, 16.0),
		EmuMath::Vector<2, double>(2.5, 0.5),
		EmuMath::Vector<2, double>(1.0, 0.25),
		EmuMath::Vector<2, double>(1.0, 0.1),
		EmuMath::Vector<2, double>(2.0, 6)
	);
	constexpr auto mat_mult_cd_ = EmuMath::Helpers::MatrixMultiply<double, true>(mat_c_, mat_d_);

	EmuMath::TMP::emu_matrix_multiplication_result_t<float, true, EmuMath::Matrix<5, 2, float, true>, EmuMath::Matrix<2, 5, double, false>> dummy_;

	std::cout << "\n\n";
	std::cout << mat_c_ << "\nMULT\n" << mat_d_ << "\n:\n" << mat_mult_cd_ << "\n";

	//constexpr auto mat_mult_dc_ = EmuMath::Helpers::MatrixMultiply<double, true>(mat_d_, mat_c_);
	//std::cout << "\n\n";
	//std::cout << mat_d_ << "\nMULT\n" << mat_c_ << "\n:\n" << mat_mult_dc_ << "\n";

	constexpr auto mat_mult_c05_ = EmuMath::Helpers::MatrixMultiply<double, false>(mat_c_, 0.5);
	std::cout << "\n\n";
	std::cout << mat_c_ << "\nMULT\n" << 0.5 << "\n:\n" << mat_mult_c05_ << "\n";

	constexpr auto mat_e_ = EmuMath::Matrix<4, 3, float>
	(
		EmuMath::Vector<3, float>(1.0f, 5.0f, 9.0f),
		EmuMath::Vector<3, float>(2.0f, 6.0f, 10.0f),
		EmuMath::Vector<3, float>(3.0f, 7.0f, 11.0f),
		EmuMath::Vector<3, float>(4.0f, 8.0f, 12.0f)
	);
	constexpr auto mat_f_ = EmuMath::Helpers::VectorToColumnMatrix(EmuMath::Vector<4, double>(10.0, 20.0, 30.0, 40.0));
	
	constexpr auto mat_mult_ef_ = EmuMath::Helpers::MatrixMultiply<double, true>(mat_e_, mat_f_);
	std::cout << "\n\n";
	std::cout << mat_e_ << "\nMULT\n" << mat_f_ << "\n:\n" << mat_mult_ef_ << "\n";

	EmuMath::Matrix<4, 4, float> wee
	(
		EmuMath::Vector<3, float>(1.0f, 5.0f, 9.0f),
		EmuMath::Vector<3, float>(2.0f, 6.0f, 10.0f),
		EmuMath::Vector<3, float>(3.0f, 7.0f, 11.0f),
		EmuMath::Vector<3, float>(4.0f, 8.0f, 12.0f)
	);
	wee = EmuMath::Helpers::MatrixMultiply(wee, 1.0f / (rand() + 1.0f));
	std::cout << wee << "\n";
	constexpr auto wee_identity = EmuMath::Helpers::MatrixIdentity(wee);
	std::cout << "Identity:\n" << wee_identity << "\n";

	constexpr std::size_t Size_ = 1;
	std::cout << Size_ << "x" << Size_ << " Identity:\n" << EmuMath::Helpers::MatrixIdentity<Size_, Size_, float, true>();

	constexpr auto size_identity_ = EmuMath::Helpers::MatrixIdentity<Size_, Size_, float, true>();

	constexpr auto bloobo = EmuMath::Matrix<4, 2, double>
	(
		EmuMath::Vector<2, double>(25.0, 50.0),
		EmuMath::Vector<2, double>(13, -27),
		EmuMath::Vector<2, double>(-0.0052, 13.37),
		EmuMath::Vector<2, double>(-13, 6.66)
	);
	constexpr auto bloobo_trans_ = EmuMath::Helpers::MatrixTranspose(bloobo);

	std::cout << "\n\n";

	std::cout << bloobo << "\nTRANSPOSED:\n" << bloobo_trans_  << "\nRETURNED:\n" << EmuMath::Helpers::MatrixTranspose(bloobo_trans_) << "\n\n";

	constexpr auto mat_hehe_ = EmuMath::Matrix<4, 4, float, true>
	(
		EmuMath::Vector4<float>(1.0f, 2.0f, 3.0f, 4.0f),
		EmuMath::Vector4<float>(5.0f, 6.0f, 7.0f, 8.0f),
		EmuMath::Vector4<float>(9.0f, 10.0f, 11.2f, 12.0f),
		EmuMath::Vector4<float>(13.0f, 14.0f, 15.0f, 16.0f)
	);
	constexpr auto mat_hehe_trace_ = EmuMath::Helpers::MatrixTrace(mat_hehe_);

	constexpr auto mat_2x2_ = EmuMath::Matrix<2, 2, float>(EmuMath::Vector2<float>(2.0f, -13.3f), EmuMath::Vector2<float>(17.0f, 7.0f));
	constexpr auto det_ = EmuMath::Helpers::MatrixDeterminantLaplace(mat_2x2_);

	auto mat_2x2_rt_ = mat_2x2_;
	std::cout << "\n\nBEFORE:\n" << mat_2x2_rt_ << "\n";
	EmuMath::Helpers::_underlying_matrix_funcs::_matrix_set<1, 1>(mat_2x2_rt_, 13.37f);
	std::cout << "AFTER:\n" << mat_2x2_rt_ << "\n\n";

	EmuMath::RefMatrix<2, 2, float> ref_;
	ref_.GetMajor<0>().Set<0>(mat_2x2_rt_.GetMajor<0>().at<0>());
	ref_.GetMajor<0>().Set<1>(mat_2x2_rt_.GetMajor<0>().at<1>());
	ref_.GetMajor<1>().Set<0>(mat_2x2_rt_.GetMajor<1>().at<0>());
	ref_.GetMajor<1>().Set<1>(mat_2x2_rt_.GetMajor<1>().at<1>());
	std::cout << ref_ << "\n\n";
	ref_.at<0, 1>() = 0.0f;
	std::cout << ref_ << "\n|\n" << mat_2x2_rt_ << "\n\n";

	float some_fp_ = 1337.0f;
	EmuMath::Helpers::_underlying_matrix_funcs::_matrix_set<0, 0>(ref_, some_fp_);
	std::cout << ref_ << "\n";
	some_fp_ = 25.0f;
	std::cout << "|\n" << ref_ << "\n";


	std::cout << "\n\n\n\n";

	wee.at<2, 3>() = 5.0f;
	auto wee_submat_ = EmuMath::Helpers::MatrixExclusiveSubmatrix<1, 1, EmuMath::InternalMatrixReference<const float>, true>(wee);
	wee.at<0, 0>() = 25.0f;
	std::cout << "WEE:\n" << wee << "\nWEE SUBMAT<1, 1>:\n" << wee_submat_ << "\n";
	std::cout << "SUBMAT SUBMAT<0, 0>:\n" << EmuMath::Helpers::MatrixExclusiveSubmatrix<0, 0>(wee_submat_) << "\n";
	std::cout << "SUBMAT SUBMAT SUBMAT<1, 1>:\n" << EmuMath::Helpers::MatrixExclusiveSubmatrix<1, 1>(EmuMath::Helpers::MatrixExclusiveSubmatrix<0, 0, double>(wee_submat_)) << "\n";

	std::cout << "\n" << wee << "\nDET: " << EmuMath::Helpers::MatrixDeterminantLaplace(wee) << "\n";

	constexpr auto some_mat_ = EmuMath::Matrix<4, 4, float, true>
	(
		EmuMath::Vector4<float>(2.0f, 3.0f, 1.0f, 1.75f),
		EmuMath::Vector4<float>(-2.0f, 3.5f, 0.05f, 1.3f),
		EmuMath::Vector4<float>(1.0f, 2.4f, 2.6f, 0.75f),
		EmuMath::Vector4<float>(2.0f, 1.2f, 0.37f, 0.75f)
	);
	constexpr auto some_mat_det_ = EmuMath::Helpers::MatrixDeterminantLaplace(some_mat_);
	constexpr auto some_mat_mul_det_ = EmuMath::Helpers::MatrixMultiply(some_mat_, some_mat_det_);
	std::cout << "\n\n" << some_mat_ << "\nDET: " << some_mat_det_ << "\n";

	constexpr auto some_2x2_ = EmuMath::Matrix<2, 2, float, true>(EmuMath::Vector2<float>(2.0f, 6.0f), EmuMath::Vector2<float>(-17.0f, 0.51f));
	constexpr auto some_2x2_det_ = EmuMath::Helpers::MatrixDeterminantLaplace(some_2x2_);

	std::cout << "\n\n" << some_2x2_ << "\nMINOR MATRIX:\n" << EmuMath::Helpers::MatrixOfMinorsLaplace(some_2x2_) << "\n\n";
	std::cout << "\n\n" << some_2x2_ << "\nCOFACTOR MATRIX:\n" << EmuMath::Helpers::MatrixOfCofactorsLaplace(some_2x2_) << "\n\n";
	std::cout << "\n\n" << some_2x2_ << "\nADJUGATE MATRIX:\n" << EmuMath::Helpers::MatrixAdjugateLaplace(some_2x2_) << "\n\n";
	float test_det_output_ = 0.0f;
	std::cout << "\n\n" << some_2x2_ << "\nINVERSE MATRIX:\n" << EmuMath::Helpers::MatrixInverseLaplace(some_2x2_, test_det_output_) << "\n\n";
	std::cout << "\n\n" << some_2x2_ << "\nDETERMINANT: " << test_det_output_ << "\n\n";
	std::cout << "\n\n" << some_2x2_ << "\nMULT INVERSE:\n" << EmuMath::Helpers::MatrixMultiply(some_2x2_, EmuMath::Helpers::MatrixInverseLaplace(some_2x2_, test_det_output_)) << "\n\n";
	std::cout << "\n\n" << some_2x2_ << "\nMULT INVERSE:\n" << EmuMath::Helpers::MatrixMultiply(some_2x2_, EmuMath::Helpers::MatrixInverseLaplace(some_2x2_)) << "\n\n";


	constexpr auto translate_mat_ = EmuMath::Helpers::MatrixTranslation(1.0f, 2.0f, 3.0f);
	std::cout << translate_mat_ << "\n\n";
	constexpr auto translate_mat_rm_ = EmuMath::Helpers::MatrixTranslation<double, false>(1.0f, 2.0f, 3.0f);
	std::cout << translate_mat_rm_ << "\n\n";

	constexpr auto identity_mat_10x10_ = EmuMath::Helpers::MatrixIdentity<EmuMath::Matrix<10, 10, float>>();
	std::cout << identity_mat_10x10_ << "\n\n";

	constexpr auto point_ = EmuMath::Vector3<float>(1.0f, 2.0f, 3.0f);
	constexpr auto point_as_column_vector_ = EmuMath::Helpers::VectorToColumnMatrix(EmuMath::Helpers::VectorPrepareToTransform(point_));
	constexpr auto point_translation_ = EmuMath::Helpers::MatrixTranslation(10.0f, 20.0f, 30.0f);
	constexpr auto point_translated_ = EmuMath::Helpers::MatrixMultiply(point_translation_, point_as_column_vector_).GetMajor<0>().As<3, float>();

	std::cout << "Point: " << point_ << "\nTransformation Matrix:\n" << point_translation_ << "\nTransformed point: " << point_translated_ << "\n\n";

	constexpr auto sin_ = EmuCore::do_sin_constexpr<void, 5>()(10.0f);
	constexpr auto cos_ = EmuCore::do_cos_constexpr<double>()(10.0f);

	constexpr auto rot_x_mat_ = EmuMath::Helpers::MatrixRotationXDegsConstexpr<10>(10.0f);
	constexpr auto point_rotated_x = EmuMath::Helpers::MatrixMultiply(rot_x_mat_, point_as_column_vector_).GetMajor<0>().As<3, float>();
	constexpr auto rot_x_det_ = EmuMath::Helpers::MatrixDeterminantLaplace(rot_x_mat_);

	constexpr auto rot_y_mat_ = EmuMath::Helpers::MatrixRotationYDegsConstexpr<10>(10.0f);
	constexpr auto point_rotated_y = EmuMath::Helpers::MatrixMultiply(rot_y_mat_, point_as_column_vector_).GetMajor<0>().As<3, float>();
	constexpr auto rot_y_det_ = EmuMath::Helpers::MatrixDeterminantLaplace(rot_y_mat_);

	constexpr auto rot_z_mat_ = EmuMath::Helpers::MatrixRotationZDegsConstexpr<10>(10.0f);
	constexpr auto point_rotated_z = EmuMath::Helpers::MatrixMultiply(rot_z_mat_, point_as_column_vector_).GetMajor<0>().As<3, float>();
	constexpr auto rot_z_det_ = EmuMath::Helpers::MatrixDeterminantLaplace(rot_z_mat_);

	auto runtime_point = point_;
	auto rot_x_runtime_ = EmuMath::Helpers::MatrixRotationXDegs(25.0f);
	auto runtime_point_cm_ = EmuMath::Helpers::VectorToColumnMatrix(EmuMath::Helpers::VectorPrepareToTransform(point_));
	std::cout
		<< "Point: " << runtime_point
		<< "\nMatrix:\n" << rot_x_runtime_
		<< "\nRotated Point: " << EmuMath::Helpers::MatrixMultiply(rot_x_runtime_, runtime_point_cm_).GetMajor<0>().As<3, float>() << "\n";



#pragma region TEST_HARNESS_EXECUTION
	system("pause");
	EmuCore::TestingHelpers::PerformTests();
#pragma endregion
	return 0;
}
