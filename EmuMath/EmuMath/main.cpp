#include "EmuMath/Vector.h"
#include "EmuMath/FastVector.h"
#include "EmuMath/Matrix.h"
#include "EmuMath/NoOverflowT.h"
#include "EmuCore/TMPHelpers/Tuples.h"
#include <array>
#include <bitset>
#include <iomanip>

#include "Tests.hpp"

#include "EmuCore/Events/Event.h"
#include "EmuCore/Events/ThreadSafeEvent.h"

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

	EmuMath::Vector<4, double> _1(4.0f, 5.0f, 6.0f, 37.0f);

	EmuMath::Matrix<4, 4, float, true> matrix_
	(
		EmuMath::Vector4<float>(0.0f, 1.0f, 2.0f, 3.0f),
		std::move(_1),
		EmuMath::Vector4<std::uint8_t>(8.0f, 9.0f, 10.0f, 11.0f),
		EmuMath::Vector4<std::uint64_t>(12.0f, 13.0f, 14.0f, 15.0f)
	);


	std::cout << matrix_ << "\n";
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
	auto out_c_ = EmuMath::Helpers::MatrixGetTheoretical<13, 13>(matrix_);
	auto out_d_ = EmuMath::Helpers::MatrixGetTheoretical<16, 16>(matrix_);

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

	constexpr auto scale_123_mat_ = EmuMath::Helpers::MatrixScale(1.0f, 2.0f, 3.0f);
	std::cout << "Scale(1, 2, 3) Mat:\n" << scale_123_mat_ << "\n";
	constexpr auto scaled_point_ = EmuMath::Helpers::MatrixMultiply(scale_123_mat_, point_as_column_vector_).GetMajor<0>().As<3, float>();

	constexpr auto scale_123_mat_double_ = EmuMath::Helpers::MatrixScale<double>(1.0, 2.0, 3.0);
	constexpr auto scaled_point_v2_ = EmuMath::Helpers::MatrixMultiply<float, true, EmuMath::Matrix<4, 4, double, true>, EmuMath::Vector<3, float>>(scale_123_mat_double_, point_);
	constexpr auto scaled_point_v3_ = EmuMath::Helpers::MatrixMultiply(scale_123_mat_double_, point_);

	//constexpr EmuMath::TMP::emu_matrix_multiplication_result<int, false, EmuMath::Matrix<4, 4, double, true>, EmuMath::Vector<3, float>>::type ree = scaled_point_v2_;

	std::cout << "\n\n\n" << EmuMath::Helpers::MatrixMultiply(scale_123_mat_double_, point_) << "\n\n\n";

	constexpr auto cof_a_ = EmuMath::Helpers::MatrixBasicPerspectiveNearFarCofactorA<long double>(0.1f, 1.0f);
	constexpr auto cof_b_ = EmuMath::Helpers::MatrixBasicPerspectiveNearFarCofactorB<long double>(0.1f, 1.0f);

	float cof_a_runtime_;
	double cof_b_runtime_;
	EmuMath::Helpers::MatrixBasicPerspectiveNearFarCofactors(0.1f, 1.0f, cof_a_runtime_, cof_b_runtime_);
	std::cout << "\n\n";
	std::cout << "Cofactor A: " << cof_a_runtime_ << "\n";
	std::cout << "Cofactor B: " << cof_b_runtime_ << "\n";

	constexpr auto tan_constexpr_ = EmuCore::do_tan_constexpr<float, 3>()(EmuCore::Pi::DegsToRads(30.0f));
	std::cout << "\ntan_constexpr(30): " << tan_constexpr_ << "\ntanf(30): " << tanf(EmuCore::Pi::DegsToRads(30.0f)) << "\n";

	constexpr auto sin_constexpr_ = EmuCore::do_sin_constexpr<float, 3>()(30.0f);
	std::cout << "\nsin_constexpr(30): " << sin_constexpr_ << "\nsinf(30): " << sinf(30.0f) << "\n";

	constexpr auto cos_constexpr_ = EmuCore::do_cos_constexpr<float, 5>()(30.0f);
	std::cout << "\ncos_constexpr(30): " << cos_constexpr_ << "\ncosf(30): " << cosf(30.0f) << "\n";

	constexpr float help_ = 30.0f;
	constexpr float const_sin_ = EmuCore::do_sin_constexpr<float, 10>()(help_);
	float sin___ = sinf(help_);
	std::cout << "\nhelp_: " << const_sin_ << "\nstd__: " << sin___ << "\n\n";

	constexpr auto ndjkisgndefi = 179 % 180;

	constexpr float bloobjgboirejhoie = 361.0f;
	constexpr float djfgokd = EmuCore::do_cos_constexpr<float, 10, true>()(bloobjgboirejhoie);
	float cos___ = cosf(bloobjgboirejhoie);
	std::cout << "\nhelp_: " << djfgokd << "\nstd__: " << cos___ << "\n\n";

	constexpr auto basic_perspective_mat_ = EmuMath::Helpers::MatrixBasicPerspective<5, false>(0.01f, 1.0f, 45.0f);
	std::cout << basic_perspective_mat_ << "\n";

	constexpr float fov_angle_y_ = 75.0f;
	constexpr float near_ = 0.1f;
	constexpr float far_ = 1000.0f;
	constexpr float width_ = 1920.0f;
	constexpr float height_ = 1080.0f;
	constexpr float half_width_ = width_ * decltype(width_)(0.5);
	constexpr float half_height_ = height_ * decltype(height_)(0.5);
	constexpr float aspect_ratio_ = width_ / height_;

	constexpr auto scale_ = EmuMath::Helpers::MatrixPerspectiveFrustumScale<false, float, 5>(fov_angle_y_, near_);
	constexpr auto edge_top_ = EmuMath::Helpers::MatrixPerspectiveFrustumEdgeTop<false>(fov_angle_y_, near_);
	constexpr auto edge_bottom_ = EmuMath::Helpers::MatrixPerspectiveFrustumEdgeBottom<false>(fov_angle_y_, near_);
	constexpr auto edge_right_ = EmuMath::Helpers::MatrixPerspectiveFrustumEdgeRight<false>(fov_angle_y_, near_, aspect_ratio_);
	constexpr auto edge_left_ = EmuMath::Helpers::MatrixPerspectiveFrustumEdgeLeft<false>(fov_angle_y_, near_, aspect_ratio_);

	constexpr SomeStructForTestingEdges test_struct_(fov_angle_y_, near_, aspect_ratio_);
	constexpr auto struct_top_ = test_struct_.top_;
	constexpr auto struct_bottom_ = test_struct_.bottom_;
	constexpr auto struct_left_ = test_struct_.left_;
	constexpr auto struct_right_ = test_struct_.right_;

	constexpr auto full_perspective_mat_ = EmuMath::Helpers::MatrixPerspectiveGL<false>(fov_angle_y_, near_, far_, aspect_ratio_);
	std::cout << "Perspective(FovY (degs): " << fov_angle_y_ << ", Near: " << near_ << ", Far: " << far_ << ", Aspect Ratio: " << aspect_ratio_ << "):\n";
	std::cout << full_perspective_mat_ << "\n";
	
	constexpr auto size_ortho_mat_ = EmuMath::Helpers::MatrixOrthographicGL(width_, height_, near_, far_);
	constexpr auto bounds_ortho_mat_ = EmuMath::Helpers::MatrixOrthographicGL(-half_width_, half_width_, -half_height_, half_height_, near_, far_);
	std::cout << "Ortho(Dims):\n" << size_ortho_mat_ << "\nOrtho(bounds):\n" << bounds_ortho_mat_ << "\n";

	std::cout << "Copy3x3:\n" << EmuMath::Helpers::MatrixCopy<3, 3, float, true>(bounds_ortho_mat_) << "\n";
	std::cout << "Copy2x4:\n" << EmuMath::Helpers::MatrixCopy<2, 4, float, true>(bounds_ortho_mat_) << "\n";
	std::cout << "Copy1x1:\n" << EmuMath::Helpers::MatrixCopy<1, 1, float, true>(bounds_ortho_mat_) << "\n";
	std::cout << "Copy16x16:\n" << EmuMath::Helpers::MatrixCopy<16, 16, float, true>(bounds_ortho_mat_) << "\n";
	std::cout << "Copy16x16(13.37L):\n" << EmuMath::Helpers::MatrixCopy<16, 16, float, true>(13.37L) << "\n";

	EmuMath::Matrix<7, 2, double, false> direct_copy_;
	EmuMath::Helpers::MatrixCopy(direct_copy_, 5.5f);
	std::cout << "Direct Copy(5.5f):\n" << direct_copy_ << "\n";
	EmuMath::Helpers::MatrixCopy(direct_copy_, size_ortho_mat_);
	std::cout << "Direct Copy(Ortho(Dims)):\n" << direct_copy_ << "\n";

	EmuMath::Helpers::MatrixSet(direct_copy_, bounds_ortho_mat_);
	std::cout << "After set:\n" << direct_copy_ << "\n";
	EmuMath::Helpers::MatrixSet(direct_copy_, 2);
	std::cout << "After set(2):\n" << direct_copy_ << "\n";

	EmuMath::ConstRefMatrix<4, 4, float, true> const_ref_mat_;
	EmuMath::Helpers::MatrixSet(const_ref_mat_, bounds_ortho_mat_);
	std::cout << "Const Ref set:\n" << const_ref_mat_ << "\n";

	EmuMath::RefMatrix<4, 4, float, true> ref_mat_;
	float some_random_val_ = rand() * 0.5f;
	EmuMath::Helpers::MatrixSet(ref_mat_, some_random_val_);
	std::cout << "Ref set:\n" << ref_mat_ << "\n";
	some_random_val_ = 0.5f;
	std::cout << "Ref set after changing referenced scalar:\n" << ref_mat_ << "\n";
	
	auto auto_mat_ = EmuMath::Helpers::MatrixMake<4, 4, float, true>(1.0f, 2.0f, 3, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f);
	std::cout << "Matrix via MatrixMake:\n" << auto_mat_ << "\n";
	auto auto_mat_rm_ = EmuMath::Helpers::MatrixMake<4, 4, float, false>(1.0f, 2.0f, 3, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f);
	std::cout << "Same args but row major:\n" << auto_mat_rm_ << "\n";

	std::cout << "2x6:\n" << EmuMath::Helpers::MatrixMake<2, 6, float, true>(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7, 8.L, 9., 10U, 11u, 12L) << "\n";
	std::cout << "6x2:\n" << EmuMath::Helpers::MatrixMake<6, 2, float, true>(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7, 8.L, 9., 10U, 11u, 12L) << "\n";

	constexpr auto scalar_made_matrix_cm_ = EmuMath::Matrix<4, 4, float, true>(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
	constexpr auto scalar_made_matrix_rm_ = EmuMath::Matrix<4, 4, float, false>(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
	std::cout << "Constructed CM:\n" << scalar_made_matrix_cm_ << "\n";
	std::cout << "Constructed RM:\n" << scalar_made_matrix_rm_ << "\n";
	constexpr auto scalar_made_matrix_1x1_cm = EmuMath::Matrix<1, 1, float, true>(1);
	constexpr auto scalar_made_matrix_1x1_rm = EmuMath::Matrix<1, 1, long double, false>(1);
	std::cout << "Constructed 1x1 CM:\n" << scalar_made_matrix_1x1_cm << "\n";
	std::cout << "Constructed 1x1 RM:\n" << scalar_made_matrix_1x1_rm << "\n";


	constexpr auto mat_2x2_cm_auto_ = EmuMath::Helpers::MatrixMake<2, 2, float, true>(1, 2, 3, 4);
	constexpr auto mat_2x2_rm_auto_ = EmuMath::Helpers::MatrixMake<2, 2, float, false>(1, 2, 3, 4);

	std::cout << "MatrixMake<2, 2, float, true>(1, 2, 3, 4):\n" << mat_2x2_cm_auto_ << "\n";
	std::cout << "MatrixMake<2, 2, float, false>(1, 2, 3, 4):\n" << mat_2x2_rm_auto_ << "\n";

	std::cout << "CM Negated:\n" << EmuMath::Helpers::MatrixNegate(mat_2x2_cm_auto_) << "\n";
	std::cout << "NegNeg:\n" << EmuMath::Helpers::MatrixNegate<4, 4>(EmuMath::Helpers::MatrixNegate<4, 4>(mat_2x2_cm_auto_)) << "\n";

	auto mat_to_negate_ = EmuMath::Helpers::MatrixMake<4, 4, double, true>(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f);
	std::cout << "Before negate:\n" << mat_to_negate_ << "\n";
	EmuMath::Helpers::MatrixMutate(mat_to_negate_, mat_to_negate_, EmuCore::do_negate<double>());
	std::cout << "After negate:\n" << mat_to_negate_ << "\n";


	constexpr auto cm_2x2_auto_cast_ = EmuMath::Helpers::MatrixAs<2, 4, std::int32_t, false>(mat_2x2_cm_auto_);
	std::cout << EmuMath::Helpers::MatrixAnd(cm_2x2_auto_cast_, 0x01) << "\n";
	std::cout << EmuMath::Helpers::MatrixNot<3, 2>(cm_2x2_auto_cast_) << "\n";
	std::cout << EmuMath::Helpers::MatrixOr<3, 2>(cm_2x2_auto_cast_, 0x01) << "\n";
	std::cout << EmuMath::Helpers::MatrixXor<3, 2>(cm_2x2_auto_cast_, 0x01) << "\n";

	constexpr auto to_shift_ = EmuMath::Helpers::MatrixMake<3, 3, std::uint32_t, true>(8, 4, 8, 4, 8, 4, 8, 4, 8);
	constexpr auto shifted_left_scalar = EmuMath::Helpers::MatrixShiftLeft(to_shift_, 2);
	constexpr auto shifted_left_mat = EmuMath::Helpers::MatrixShiftLeft(to_shift_, EmuMath::Helpers::MatrixMake<3, 3, std::size_t>(2, 1, 2, 0, 1, 2, 1, 2, 3));
	constexpr auto shifted_right_scalar = EmuMath::Helpers::MatrixShiftRight(to_shift_, 2);
	constexpr auto shifted_right_mat = EmuMath::Helpers::MatrixShiftRight<std::int64_t>(to_shift_, EmuMath::Helpers::MatrixMake<3, 3, std::size_t>(2, 1, 2, 0, 1, 2, 1, 2, 3));
	constexpr auto neg_srm_ = -shifted_right_mat;
	constexpr auto pos_srm_ = +shifted_right_mat;
	constexpr auto inv_srm_ = ~shifted_right_mat;


	constexpr auto cmp_per_element_result_equal_ = EmuMath::Helpers::MatrixCmpPerElementEqual(inv_srm_, -3);
	constexpr auto cmp_per_element_result_not_equal_ = EmuMath::Helpers::MatrixCmpPerElementNotEqual(inv_srm_, -3);
	constexpr auto cmp_per_element_result_greater_ = EmuMath::Helpers::MatrixCmpPerElementGreater(inv_srm_, -3);
	constexpr auto cmp_per_element_result_less_ = EmuMath::Helpers::MatrixCmpPerElementLess(inv_srm_, -3);
	constexpr auto cmp_per_element_result_greater_equal_ = EmuMath::Helpers::MatrixCmpPerElementGreaterEqual(inv_srm_, -3);
	constexpr auto cmp_per_element_result_less_equal_ = EmuMath::Helpers::MatrixCmpPerElementLessEqual(inv_srm_, -3);

	constexpr auto cmp_all_result_equal_scalar_ = EmuMath::Helpers::MatrixCmpAllEqual(inv_srm_, -2);
	constexpr auto cmp_all_result_not_equal_scalar_ = EmuMath::Helpers::MatrixCmpAllNotEqual(inv_srm_, 42);
	constexpr auto cmp_all_result_greater_scalar_ = EmuMath::Helpers::MatrixCmpAllGreater(inv_srm_, -5);
	constexpr auto cmp_all_result_greater_equal_scalar_ = EmuMath::Helpers::MatrixCmpAllGreaterEqual(inv_srm_, -5);
	constexpr auto cmp_all_result_less_scalar_ = EmuMath::Helpers::MatrixCmpAllLess(inv_srm_, -2);
	constexpr auto cmp_all_result_less_equal_scalar_ = EmuMath::Helpers::MatrixCmpAllLessEqual(inv_srm_, -2);

	constexpr auto cmp_any_result_equal_scalar_ = EmuMath::Helpers::MatrixCmpAnyEqual(inv_srm_, -2);
	constexpr auto cmp_any_result_not_equal_scalar_ = EmuMath::Helpers::MatrixCmpAnyNotEqual(inv_srm_, 42);
	constexpr auto cmp_any_result_greater_scalar_ = EmuMath::Helpers::MatrixCmpAnyGreater(inv_srm_, -5);
	constexpr auto cmp_any_result_greater_equal_scalar_ = EmuMath::Helpers::MatrixCmpAnyGreaterEqual(inv_srm_, -5);
	constexpr auto cmp_any_result_less_scalar_ = EmuMath::Helpers::MatrixCmpAnyLess(inv_srm_, -2);
	constexpr auto cmp_any_result_less_equal_scalar_ = EmuMath::Helpers::MatrixCmpAnyLessEqual(inv_srm_, -2);
	constexpr auto cmp_any_result_less_equal_scalar_ex0_ = EmuMath::Helpers::MatrixCmpAnyLessEqual(inv_srm_, 0);
	constexpr auto cmp_any_result_less_equal_scalar_ex1_ = EmuMath::Helpers::MatrixCmpAnyGreaterEqual(inv_srm_, 0);


	constexpr auto copied_ = EmuMath::Helpers::MatrixAs<4, 4>(inv_srm_);
	
	constexpr auto copied_with_noise_ = EmuMath::Helpers::MatrixMake<4, 4, float, true>
	(
		copied_.at<0, 0>(), copied_.at<0, 1>(), copied_.at<0, 2>(), 1.0f,
		copied_.at<1, 0>(), copied_.at<1, 1>(), copied_.at<1, 2>(), 2.0f,
		copied_.at<2, 0>(), copied_.at<2, 1>(), copied_.at<2, 2>(), 3.0f,
		4.0f, 5.0f, 6.0f, 7.0f
	);

	int x__ = 1; int y__ = 2; int z__ = 3; int w__ = 4;
	auto yo_ = EmuMath::Helpers::MatrixMake<3, 3, double>(0.0f, x__, 0.0f, y__, 0.0f, z__, 0.0f, w__, 0.0f);

	constexpr auto cmp_all_result_equal_mat_all_ = EmuMath::Helpers::MatrixCmpAllEqual<true>(inv_srm_, copied_with_noise_);
	constexpr auto cmp_all_result_equal_mat_largest_ = EmuMath::Helpers::MatrixCmpAllEqual<false>(inv_srm_, copied_with_noise_);
	constexpr auto cmp_all_result_equal_mat_all_no_noise_ = EmuMath::Helpers::MatrixCmpAllEqual<true>(inv_srm_, copied_);
	constexpr auto cmp_all_result_equal_mat_largest_no_noise_ = EmuMath::Helpers::MatrixCmpAllEqual<false>(inv_srm_, copied_);

	constexpr auto _some2x2cm = EmuMath::Helpers::MatrixMake<2, 2, float, true>(1.0f, 2.0f, 3.0f, 4.0f);
	constexpr auto _some2x2rm = EmuMath::Helpers::MatrixMake<2, 2, float, false>(1.0f, 2.0f, 3.0f, 4.0f);
	std::cout << "---\n";
	std::cout << _some2x2cm << "\n";
	std::cout << _some2x2rm << "\n";

	constexpr auto _some1x1cm = EmuMath::Helpers::MatrixMake<1, 1, float, true>(5);
	constexpr auto _some1x1rm = EmuMath::Helpers::MatrixMake<1, 1, float, false>(5);
	std::cout << "---\n";
	std::cout << _some1x1cm << "\n\n";
	std::cout << _some1x1rm << "\n\n";


	constexpr auto _some1x16cm = EmuMath::Helpers::MatrixMake<1, 16, float, true>(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
	constexpr auto _some1x16rm = EmuMath::Helpers::MatrixMake<1, 16, float, false>(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
	std::cout << "---\n";
	std::cout << _some1x16cm << "\n\n";
	std::cout << _some1x16rm << "\n\n";


	constexpr auto _some16x1cm = EmuMath::Helpers::MatrixMake<16, 1, float, true>(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
	constexpr auto _some16x1rm = EmuMath::Helpers::MatrixMake<16, 1, float, false>(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
	std::cout << "---\n";
	std::cout << _some16x1cm << "\n\n";
	std::cout << _some16x1rm << "\n\n";

	constexpr auto _some16x2cm = EmuMath::Helpers::MatrixMake<16, 2, float, true>(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32);
	constexpr auto _some16x2rm = EmuMath::Helpers::MatrixMake<16, 2, float, false>(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32);
	std::cout << "---\n";
	std::cout << _some16x2cm << "\n\n";
	std::cout << _some16x2rm << "\n\n";

	constexpr bool cmp_0_ = _some16x2cm == _some16x2rm;
	constexpr bool cmp_1_ = _some16x2cm == _some16x2cm;
	constexpr bool cmp_2_ = _some16x2cm != _some16x2rm;
	constexpr bool cmp_3_ = _some16x2cm != _some16x2cm;


	constexpr auto some_translation_mat_ = EmuMath::Helpers::MatrixTranslation(1.0f, 2.0f, 3.0f);
	constexpr auto trans_mul_vec = some_translation_mat_ * EmuMath::Vector3<float>(10.0f, 20.0f, 10.0f);
	constexpr auto trans_mul_scalar = some_translation_mat_ * 5;
	constexpr auto trans_mul_trans_ = some_translation_mat_ * some_translation_mat_;
	constexpr auto trans_det_ = EmuMath::Helpers::MatrixDeterminantLaplace(some_translation_mat_);
	constexpr auto trans_inv_ = EmuMath::Helpers::MatrixInverseLaplace(some_translation_mat_);

	auto muleq_mat_ = EmuMath::Matrix<4, 4, float, true>(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f);
	std::cout << "\n\n";
	std::cout << "Before mult:\n" << muleq_mat_ << "\n";
	muleq_mat_ *= 2.0f;
	std::cout << "After scalar mult:\n" << muleq_mat_ << "\n";
	muleq_mat_ *= EmuMath::Matrix<4, 4, float, true>(2.0f, 0.0f, 0.0f, 0.0f, 0.0f, 2.0f, 0.0f, 0.0f, 0.0f, 0.0f, 2.0f, 0.0f, 0.0f, 0.0f, 0.0f, 2.0f);
	std::cout << "After matrix mult:\n" << muleq_mat_ << "\n";

	constexpr auto lhs___ = EmuMath::Matrix<3, 3, float, true>(		 0.0f, -3.0f, 27.0f, 16.6f, 2.0f,  15.0f, 0.0f, 0.0f, 1.0f);
	constexpr auto rhs___ = EmuMath::Matrix<3, 3, long double, true>(1.0f, -4.0f, 14.0f, 16.7f, 12.0f, 13.0f, 0.0f, 1.0f, 0.0f);
	constexpr auto min_mat_ = EmuMath::Helpers::MatrixMin<std::int64_t>(lhs___, rhs___);
	constexpr auto max_mat_ = EmuMath::Helpers::MatrixMax<long double>(lhs___, rhs___);

	constexpr auto clamped_min_scalar = EmuMath::Helpers::MatrixClampMin(lhs___, 1.0f);
	constexpr auto clamped_min_mat = EmuMath::Helpers::MatrixClampMin(lhs___, rhs___);
	constexpr auto clamped_max_scalar = EmuMath::Helpers::MatrixClampMax(lhs___, 1.0f);
	constexpr auto clamped_max_mat = EmuMath::Helpers::MatrixClampMax(lhs___, rhs___);

	constexpr auto clamped_min_max_ss = EmuMath::Helpers::MatrixClamp<3, 3, int, true>(lhs___, 1.0f, 3.0f);

	constexpr auto id_ = lhs___.Identity();

	constexpr auto _3x3_transpose_ = lhs___.Transpose();
	constexpr auto _2x4_tranpose_ = EmuMath::Matrix<2, 4, double, true>(1, 2, 3, 4, 5, 6, 7, 8).Transpose();
	constexpr auto _4x5_sub = EmuMath::Matrix<4, 5, int>(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20).ExclusiveSubmatrix<0, 0>();
	constexpr auto _3x3_trans_cast_ = _3x3_transpose_.AsMatrix<EmuMath::Matrix<5, 27, float, true>>();



#pragma region TEST_HARNESS_EXECUTION
	system("pause");
	EmuCore::TestingHelpers::PerformTests();
#pragma endregion
	return 0;
}
