#include "EmuMath/Vector.h"
#include "EmuMath/FastVector.h"
#include "EmuMath/Matrix.h"
#include "EmuMath/FastMatrix.h"
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

	EmuMath::FastMatrix4x4f_CM fast_4x4_from_scalars(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
	std::cout << "\n\n";
	std::cout << fast_4x4_from_scalars << "\n";
	std::cout << "Row[0]: " << fast_4x4_from_scalars.GetRowReadable<0>() << "\n";
	std::cout << "Row[1]: " << fast_4x4_from_scalars.GetRowReadable<1>() << "\n";
	std::cout << "Row[2]: " << fast_4x4_from_scalars.GetRowReadable<2>() << "\n";
	std::cout << "Row[3]: " << fast_4x4_from_scalars.GetRowReadable<3>() << "\n";
	std::cout << "Column[0]: " << fast_4x4_from_scalars.GetColumnReadable<0>() << "\n";
	std::cout << "Column[1]: " << fast_4x4_from_scalars.GetColumnReadable<1>() << "\n";
	std::cout << "Column[2]: " << fast_4x4_from_scalars.GetColumnReadable<2>() << "\n";
	std::cout << "Column[3]: " << fast_4x4_from_scalars.GetColumnReadable<3>() << "\n";
	std::cout << "Trace: " << fast_4x4_from_scalars.Trace() << "\n";
	std::cout << "Stored as column-major matrix:\n" << fast_4x4_from_scalars.Store<float, true>() << "\n";
	std::cout << "Stored as row-major matrix:\n" << fast_4x4_from_scalars.Store<float, false>() << "\n";
	std::cout << (fast_4x4_from_scalars != fast_4x4_from_scalars) << " | " << (fast_4x4_from_scalars == fast_4x4_from_scalars) << "\n";
	std::cout << fast_4x4_from_scalars * 2.5L << "\n\n";
	std::cout << fast_4x4_from_scalars.Multiply(fast_4x4_from_scalars) << "\n\n";
	std::cout << "(Above as SISD):\n" << fast_4x4_from_scalars.Store().Multiply(fast_4x4_from_scalars.Store()) << "\n\n";

	std::cout << "TRANSFORMATIONS\n";
	std::cout << "Translation(1, 2, 3) SIMD:\n" << EmuMath::FastMatrix4x4f_CM::Translation(1, 2, 3) << "\n";
	std::cout << "Translation(1, 2, 3) SISD:\n" << EmuMath::Matrix4x4<float, true>::Translation(1, 2, 3) << "\n\n";
	std::cout << "Scale(1.5, -2, 3.3) SIMD:\n" << EmuMath::FastMatrix4x4f_CM::Scale(1.5, -2, 3.3) << "\n";
	std::cout << "Scale(1.5, -2, 3.3) SISD:\n" << EmuMath::Matrix4x4<float, true>::Scale(1.5, -2, 3.3) << "\n\n";
	std::cout << "RotationX<false>(33) SIMD:\n" << EmuMath::FastMatrix4x4f_CM::RotationX<false>(33.0f) << "\n";
	std::cout << "RotationX<false>(33) SISD:\n" << EmuMath::Matrix4x4<float, true>::RotationX<false>(33.0f) << "\n\n";
	std::cout << "RotationY<false>(33) SIMD:\n" << EmuMath::FastMatrix4x4f_CM::RotationY<false>(33) << "\n";
	std::cout << "RotationY<false>(33) SISD:\n" << EmuMath::Matrix4x4<float, true>::RotationY<false>(33) << "\n\n";
	std::cout << "RotationZ<false>(33) SIMD:\n" << EmuMath::FastMatrix4x4f_CM::RotationZ<false>(33) << "\n";
	std::cout << "RotationZ<false>(33) SISD:\n" << EmuMath::Matrix4x4<float, true>::RotationZ<false>(33) << "\n\n";

	std::cout << "Ortho(0.01f, 25.0f, 1920.0f, 1080.0f) (SIMD):\n" << EmuMath::FastMatrix4x4f_CM::OrthographicRhVK(1920.0f, 1080.0f, 0.01f, 25.0f) << "\n\n";
	std::cout << "Ortho(0.01f, 25.0f, 1920.0f, 1080.0f) (SISD):\n" << EmuMath::Matrix4x4<float>::OrthographicVK(1920.0f, 1080.0f, 0.01f, 25.0f) << "\n\n";
	std::cout << "Ortho(0.01f, 25.0f, 1920.0f, 1080.0f) (DXM):\n";
	auto dxm_proj_ = DirectX::XMMatrixOrthographicRH(1920.0f, 1080.0f, 0.01f, 25.0f);
	DirectX::XMFLOAT4X4 readable_dxm_mat_;
	DirectX::XMStoreFloat4x4(&readable_dxm_mat_, dxm_proj_);
	for (std::size_t x = 0; x < 4; ++x)
	{
		std::cout << "{ ";
		for (std::size_t y = 0; y < 4; ++y)
		{
			std::cout << readable_dxm_mat_(x, y);
			if (y != 3)
			{
				std::cout << ", ";
			}
		}
		std::cout << " }\n";
	}
	std::cout << "\n\n";

	std::cout << "Projection(75.0f, 0.01f, 25.0f, 1920.0f / 1080.0f) (SIMD):\n" << EmuMath::FastMatrix4x4f_CM::PerspectiveRhVK<false>(75.0f, 0.01f, 25.0f, 1920.0f / 1080.0f) << "\n\n";
	std::cout << "Projection(75.0f, 0.01f, 25.0f, 1920.0f / 1080.0f) (SISD):\n" << EmuMath::Matrix4x4<float>::PerspectiveVK<false>(75.0f, 0.01f, 25.0f, 1920.0f / 1080.0f) << "\n\n";
	std::cout << "Projection(75.0f, 0.01f, 25.0f, 1920.0f / 1080.0f) (DXM):\n";
	dxm_proj_ = DirectX::XMMatrixPerspectiveFovRH(EmuCore::Pi::DegsToRads(75.0f), 1920.0f / 1080.0f, 0.01f, 25.0f);
	DirectX::XMStoreFloat4x4(&readable_dxm_mat_, dxm_proj_);
	for (std::size_t x = 0; x < 4; ++x)
	{
		std::cout << "{ ";
		for (std::size_t y = 0; y < 4; ++y)
		{
			std::cout << readable_dxm_mat_(x, y);
			if (y != 3)
			{
				std::cout << ", ";
			}
		}
		std::cout << " }\n";
	}
	std::cout << "\n\n";

	std::cout << fast_4x4_from_scalars << "\n\n";
	std::cout << ~fast_4x4_from_scalars << "\n\n";
	std::cout << ~~fast_4x4_from_scalars << "\n\n";
	std::cout << ~~~fast_4x4_from_scalars << "\n\n";

	EmuMath::FastMatrix4x4f_CM a_mat_
	(
		0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f
	);
	EmuMath::FastMatrix4x4f_CM b_mat_
	(
		10.0f, 10.0f, 10.0f, 10.0f,
		10.0f, 10.0f, 10.0f, 10.0f,
		10.0f, 10.0f, 10.0f, 10.0f,
		10.0f, 10.0f, 10.0f, 10.0f
	);
	EmuMath::FastMatrix4x4f_CM t_mat_
	(
		0.1f, 0.2f, 0.3f, 0.4f,
		0.5f, 0.6f, 0.7f, 0.8f,
		0.9f, 1.0f, 1.1f, 1.2f,
		1.3f, 1.4f, 1.5f, 1.6f
	);
	std::cout << "A:\n" << a_mat_ << "\nB:\n" << b_mat_ << "\nT:\n" << t_mat_ << "\nLERPED:\n" << a_mat_.Lerp(b_mat_, t_mat_) << "\n\n";
	std::cout << "A:\n" << a_mat_ << "\nB:\n" << b_mat_ << "\nT:\n" << t_mat_ << "\nLERPED:\n" << a_mat_.Lerp(10.0L, 0.5f) << "\n\n";


	EmuMath::FastMatrix4x4f_CM original_mat_
	(
		-5.0f, 0.0f, 1.0f, 12.0f,
		66.0f, -555.0f, 12.0f, 1,
		1.0f, 2.0f, 3.0f, 1337.1f,
		1.0f, 3.0f, 3.0f, 7.331f
	);
	EmuMath::FastMatrix4x4f_CM min_mat_
	(
		0.0f, 0.0f, -5.0f, 0.0f,
		1.0f, -500.0f, 2.0f, 0.0f,
		6.0f, 1.0f, 3.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f
	);
	EmuMath::FastMatrix4x4f_CM max_mat_
	(
		1.0f, 2.0f, 3.0f, 4.0f,
		5.0f, 6.0f, 7.0f, 8.0f,
		9.0f, 10.0f, 11.0f, 12.0f,
		13.0f, 14.0f, 15.0f, 16.0f
	);
	std::cout << "Original:\n" << original_mat_ << "\nMin:\n" << min_mat_ << "\nMax:\n" << max_mat_ << "\nClamped:\n" << original_mat_.Clamp(min_mat_, max_mat_) << "\n\n";
	std::cout << "Original min: " << original_mat_.Min() << " | Original max: " << original_mat_.Max() << "\n\n";

	std::cout << original_mat_ << "\nTRANSPOSE:\n" << original_mat_.Transpose() << "\n\n";
	

	EmuMath::FastMatrix4x4f_CM inv_test_
	(
		-3, 6, 3, 1,
		2, -6, -4, 2,
		-1, 7, 4, 3,
		1, 1, 1, 1
	);
	std::cout << "Mat:\n" << inv_test_ << "\nInverse:\n" << inv_test_.InverseGaussJordan() << "\n\n";
	std::cout << "\n\nSCALAR INVERSE:\n" << inv_test_.Store().InverseLaplace() << "\n\n";


	std::cout << "Mat:\n" << inv_test_ << "\nDeterminant: " << inv_test_.Determinant() << "\n\n";
	std::cout << "\n\nSCALAR DETERMINANT: " << inv_test_.Store().DeterminantLaplace() << "\n\n";

	EmuMath::FastMatrix4x4f_CM det_test_
	(
		1, 2, 4, 3,
		1, 36, -7, 8,
		10, 22, 44, 12,
		333, -666, 12, 1
	);
	EmuMath::Matrix<4, 4, float, true> det_test_scalar_
	(
		1, 2, 4, 3,
		1, 36, -7, 8,
		10, 22, 44, 12,
		333, -666, 12, 1
	);
	std::cout << "Matrix:\n" << det_test_ << "\n";
	std::cout << "Det (SISD) 2x2: " << det_test_scalar_.As<2, 2>().DeterminantLaplace() << "\n\n";
	std::cout << "Det (SISD) 3x3: " << det_test_scalar_.As<3, 3>().DeterminantLaplace() << "\n\n";

	std::cout << "Minors (SIMD):\n" << det_test_.MatrixOfMinorsLaplace<false>() << "\n";
	std::cout << "Minors (SIMD Transposed):\n" << det_test_.MatrixOfMinorsLaplace<true>() << "\n";
	std::cout << "Minors (SISD):\n" << det_test_scalar_.MatrixOfMinorsLaplace() << "\n";
	std::cout << "Determinant [Sub[0, 0]]: " << det_test_scalar_.ExclusiveSubmatrix<3, 3>().ExclusiveSubmatrix<0, 0>().DeterminantLaplace() << "\n";
	std::cout << "Inverse:\n" << det_test_.InverseLaplace() << "\nSISD Inverse:\n" << det_test_scalar_.InverseLaplace() << "\n\n";

#pragma region TEST_HARNESS_EXECUTION
	system("pause");
	EmuCore::TestingHelpers::PerformTests();
#pragma endregion
	return 0;
}
