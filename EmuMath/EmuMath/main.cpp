#include "Tests.hpp"

#include "EmuMath/GeneralMath.h"
#include "EmuMath/NoOverflowT.h"
#include "EmuMath/Vectors.h"
#include "EmuMath/FastVector.h"
#include "EmuMath/Matrices.h"
#include <array>
#include <iomanip>

using namespace EmuCore::TestingHelpers;
using namespace EmuMath;

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

int main()
{
	const float bobs[4] = { 1.0f, 2.0f, 3.0f, 4.0f };
	FastVector<4, float> yo(2.0f, 1.0f, 5.0f, -777.69f);
	FastVector<4, float> no(5.0f, 1.0f, 6.0f, 2.0f);
	yo.vectorData = _mm_load_ps(bobs);
	const float* pData = yo.vectorData.m128_f32;
	std::cout << "Data: { " << pData[0] << ", " << pData[1] << ", " << pData[2] << ", " << pData[3] << " }\n";
	yo = yo.Shuffle<2, 1, 0, 3>();
	std::cout << "Data: { " << pData[0] << ", " << pData[1] << ", " << pData[2] << ", " << pData[3] << " }\n";
	float dot = yo.DotProduct(no);
	std::cout << yo << " DOT " << no << " = " << dot << "\n\n";

	FastVector<4, float> max0(123.4f, 123.3f, 3.0f, -123.5f);
	FastVector<4, float> max1(4.6f, 22.5f, 3.5f, -22.5f);
	FastVector<4, float> max2(2.3f, -77.1f, 666.666f, 2.2f);
	FastVector<4, float> max3(12.0f, 34.0f, 56.0f, 78.0f);
	std::cout << max0 << " | Min: " << max0.Min() << " |  Max: " << max0.Max() << " | Average: " << max0.Mean() << "\n";
	std::cout << max1 << " | Min: " << max1.Min() << " |  Max: " << max1.Max() << " | Average: " << max1.Mean() << "\n";
	std::cout << max2 << " | Min: " << max2.Min() << " |  Max: " << max2.Max() << " | Average: " << max2.Mean() << "\n";
	std::cout << max3 << " | Min: " << max3.Min() << " |  Max: " << max3.Max() << " | Average: " << max3.Mean() << "\n";

	__m128 test128 = _mm_setr_ps(1.0f, 2.0f, 3.0f, 4.0f);
	test128 = EmuMath::SIMD::horizontal_vector_sum(test128);
	std::cout << "[0] = " << EmuMath::SIMD::get_m128_index(test128, 0) << "\n";
	std::cout << "[1] = " << EmuMath::SIMD::get_m128_index(test128, 1) << "\n";
	std::cout << "[2] = " << EmuMath::SIMD::get_m128_index(test128, 2) << "\n";
	std::cout << "[3] = " << EmuMath::SIMD::get_m128_index(test128, 3) << "\n";

	EmuMath::FastVector<4, float> a(1.0f, 1.0f, 1.0f, 1.0f);
	EmuMath::FastVector<4, float> b(1.0f, 2.0f, 1.0f, 1.0f);
	std::cout << a << " == " << b << ": " << (EmuMath::SIMD::all_not_equal<false, true, false, false>(a.vectorData, b.vectorData) ? "true" : "false") << "\n";

	constexpr std::uint32_t c = 0b0011;
	constexpr std::uint32_t d = 0b11111111111111110111111111111111;
	constexpr std::uint32_t e = 0;
	std::cout
		<< "c bits: " << EmuCore::ArithmeticHelpers::num_active_bits(c) << "\t(" << std::bitset<32>(c) << ")\n"
		<< "d bits: " << EmuCore::ArithmeticHelpers::num_active_bits(d) << "\t(" << std::bitset<32>(d) << ")\n"
		<< "e bits: " << EmuCore::ArithmeticHelpers::num_active_bits(e) << "\t(" << std::bitset<32>(e) << ")\n";
	
	
	EmuMath::MatrixCM<4, 4, float> blooble(1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f);

	constexpr EmuMath::MatrixCM<25, 25, float> mat_25x25_identity = EmuMath::MatrixCM<25, 25, float>::Identity();
	std::cout << mat_25x25_identity << "\n";

	constexpr auto SomeSubMatrix = EmuMath::MatrixCM<4, 4, std::uint32_t>(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16).SubMatrix<0, 2, 0, 2>();


	//blooble.columns[1] *= 10.0f;
	std::cout << "Base:\n" << blooble << std::endl;
	std::cout << "Tranpose:\n" << blooble.Transpose() << std::endl;
	std::cout << "Added to self:\n" << (blooble + blooble) << std::endl;
	std::cout << "Subtracted from self 3 times:\n" << (blooble - blooble - blooble - blooble) << std::endl;
	std::cout << "Negated:\n" << -blooble << std::endl;
	//std::cout << "Negated row 1:\n" << (-blooble).GetRow<1>() << std::endl;
	//std::cout << "Column 3:\n" << blooble.GetColumn<3>() << std::endl;
	std::cout << "Multiplied by 0.5f:\n" << (blooble * 0.5f) << std::endl;
	std::cout << "Trace: " << blooble.Trace() << std::endl;
	std::cout << "\n\n" << blooble << "\nMULT\n" << (blooble * 2.5f) << "\nEQUALS:\n" << (blooble * (blooble * 2.5f)) << std::endl;

	std::cout << "BLOOBLE ROWS EXTRACTED INDIVIDUALLY:\n" << EmuMath::Helpers::MatrixCopyAsRows(blooble) << "\n";
	std::cout << "BLOOBLE COLUMNS EXTRACTED INDIVIDUALLY:\n" << EmuMath::Helpers::MatrixCopyAsColumns(blooble) << "\n";

	std::cout << "Identity:\n" << blooble.Identity() << std::endl;


	std::cout << "Submatrix(0:1, 0:1):\n" << EmuMath::Helpers::MatrixSubMatrix<0, 1, 0, 1>(blooble) << std::endl;
	std::cout << "Submatrix(0:1, 1:3):\n" << EmuMath::Helpers::MatrixSubMatrix<0, 1, 1, 3>(blooble) << std::endl;
	std::cout << "Submatrix(2:3, 0:3):\n" << blooble.SubMatrix<2, 3, 0, 3>() << std::endl;

	std::cout << "\n\nMatrix:\n" << blooble << "\nSubmatrix[3, 2] (" << blooble.at<3, 2>() << "):\n" << blooble.SubMatrixExcluding<3, 2>() << std::endl;

	constexpr EmuMath::MatrixCM<4, 4, float> McDooble(17.0, 18.0, 19.0, 20.0, 21.0, 22.0, 23.0, 24.0, 25.0, 26.0, 27.0, 28.0, 29.0, 30.0, 31.0, 32.0);
	blooble = McDooble;
	std::cout << "After set:\n" << blooble << std::endl;

	std::cout << "Element (1, 3): " << EmuMath::Helpers::MatrixGet(blooble, 1, 3) << "\n";
	std::cout << "Column 2: " << EmuMath::Helpers::MatrixGet(blooble, 2) << "\n";
	std::cout << "Column 3: " << blooble[3] << "\n";

	EmuMath::MatrixCM<2, 2, std::uint64_t> a_(257, 1, 233, 42);
	EmuMath::MatrixCM<2, 2, std::uint64_t> b_(29, 333, 1, 2);
	EmuMath::MatrixCM<2, 2, std::uint64_t> result_ = EmuMath::Helpers::MatrixRespectiveMultiplication(a_, b_);
	std::cout << "Determinant of:\n" << result_ << "\n: " << EmuMath::Helpers::MatrixDeterminantLaplace<float>(result_) << "\n";

	auto resooble = EmuMath::MatrixCM<4, 4, double>(2.73, -6.66, 2.0, 3.5, 2.3, 16.6, 0.0, 12.345, 19.9, -1.337, 22.0, 1.0, 3.0, 5.0, 2.37, 6.6);
	std::cout << "Determinant of:\n" << resooble << "\n: " << std::setprecision(10) << std::fixed << EmuMath::Helpers::MatrixDeterminantLaplace<double>(resooble) << std::endl;

	auto bigooble = EmuMath::MatrixCM<6, 6, double>
	(
		EmuMath::MatrixCM<6, 6, double>::column_type({ 0.1f, 0.005f, 0.6f, 2.0f, 3.0f, 2.0f }),
		EmuMath::MatrixCM<6, 6, double>::column_type({ 26.0f }),
		EmuMath::MatrixCM<6, 6, double>::column_type({ 1.0f, 1.0f, 1.0f, 3.0f, 1.0f, 2.0f }),
		EmuMath::MatrixCM<6, 6, double>::column_type({ 31.5f, 0.0f, 2.0f, 3.0f, 7.0f, 13.0f }),
		EmuMath::MatrixCM<6, 6, double>::column_type({ 12.0f, 1.0f, 0.0f, 3.0f, 4.0f, 6.0f }),
		EmuMath::MatrixCM<6, 6, double>::column_type({ -22.0f, 3.0f, 4.0f, 5.0f, 1.0f, 23.0215f })
	);
	std::cout << "Determinant of:\n" << bigooble << "\n: " << std::setprecision(10) << std::fixed << EmuMath::Helpers::MatrixDeterminantLaplace<double>(bigooble) << std::endl;

	auto resoobleInverse = EmuMath::Helpers::MatrixInverseLaplace<double>(resooble);
	std::cout << "Base:\n" << resooble << "\nInverse:\n" << resoobleInverse << "\nBase x Inverse:\n" << (resooble * resoobleInverse) << "\n";

	std::cout << "Minors:\n" << EmuMath::Helpers::MatrixMinorsLaplace(resooble) << "\n";

	system("pause");

#pragma region TEST_HARNESS_EXECUTION
	EmuCore::TestingHelpers::PerformTests();
#pragma endregion
	return 0;
}