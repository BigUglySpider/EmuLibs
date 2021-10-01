#ifndef EMU_MATH_FAST_MATRIX_4X4_H_INC_
#define EMU_MATH_FAST_MATRIX_4X4_H_INC_ 1

#include "../../Matrix.h"
#include "../../SIMDHelpers.h"
#include "../../FastVector.h"

namespace EmuMath
{
	/// <summary> 4x4 matrix of floating points which makes use of SIMD intrinsics. Uses column-major storage. </summary>
	struct FastMatrix4x4f_CM
	{
		FastMatrix4x4f_CM() : column_0(), column_1(), column_2(), column_3()
		{
		}
		FastMatrix4x4f_CM(__m128 column_0_, __m128 column_1_, __m128 column_2_, __m128 column_3_) :
			column_0(column_0_),
			column_1(column_1_),
			column_2(column_2_),
			column_3(column_3_)
		{
		}
		FastMatrix4x4f_CM(const FastMatrix4x4f_CM& to_copy_) :
			column_0(to_copy_.column_0),
			column_1(to_copy_.column_1),
			column_2(to_copy_.column_2),
			column_3(to_copy_.column_3)
		{
		}
		template<typename std::size_t InColumns_, std::size_t InRows_, typename in_contained_type, bool InColumnMajor_>
		explicit FastMatrix4x4f_CM(const EmuMath::Matrix<InColumns_, InRows_, in_contained_type, InColumnMajor_>& to_copy_) :
			column_0
			(
				_mm_set_ps
				(
					EmuMath::Helpers::MatrixGetTheoretical<0, 3>(to_copy_),
					EmuMath::Helpers::MatrixGetTheoretical<0, 2>(to_copy_),
					EmuMath::Helpers::MatrixGetTheoretical<0, 1>(to_copy_),
					EmuMath::Helpers::MatrixGetTheoretical<0, 0>(to_copy_)
				)
			),
			column_1
			(
				_mm_set_ps
				(
					EmuMath::Helpers::MatrixGetTheoretical<1, 3>(to_copy_),
					EmuMath::Helpers::MatrixGetTheoretical<1, 2>(to_copy_),
					EmuMath::Helpers::MatrixGetTheoretical<1, 1>(to_copy_),
					EmuMath::Helpers::MatrixGetTheoretical<1, 0>(to_copy_)
				)
			),
			column_2
			(
				_mm_set_ps
				(
					EmuMath::Helpers::MatrixGetTheoretical<2, 3>(to_copy_),
					EmuMath::Helpers::MatrixGetTheoretical<2, 2>(to_copy_),
					EmuMath::Helpers::MatrixGetTheoretical<2, 1>(to_copy_),
					EmuMath::Helpers::MatrixGetTheoretical<2, 0>(to_copy_)
				)
			),
			column_3
			(
				_mm_set_ps
				(
					EmuMath::Helpers::MatrixGetTheoretical<3, 3>(to_copy_),
					EmuMath::Helpers::MatrixGetTheoretical<3, 2>(to_copy_),
					EmuMath::Helpers::MatrixGetTheoretical<3, 1>(to_copy_),
					EmuMath::Helpers::MatrixGetTheoretical<3, 0>(to_copy_)
				)
			)
		{
		}
		template
		<
			std::size_t Size0_, typename contained_type_0,
			std::size_t Size1_, typename contained_type_1,
			std::size_t Size2_, typename contained_type_2,
			std::size_t Size3_, typename contained_type_3
		>
		FastMatrix4x4f_CM
		(
			const EmuMath::Vector<Size0_, contained_type_0>& column_0_,
			const EmuMath::Vector<Size1_, contained_type_1>& column_1_,
			const EmuMath::Vector<Size2_, contained_type_2>& column_2_,
			const EmuMath::Vector<Size3_, contained_type_3>& column_3_
		) : 
			column_0(EmuMath::SIMD::m128_from_emu_math_vector(column_0_)),
			column_1(EmuMath::SIMD::m128_from_emu_math_vector(column_1_)),
			column_2(EmuMath::SIMD::m128_from_emu_math_vector(column_2_)),
			column_3(EmuMath::SIMD::m128_from_emu_math_vector(column_3_))
		{
		}
		template
		<
			typename C0R0_, typename C0R1_, typename C0R2_, typename C0R3_,
			typename C1R0_, typename C1R1_, typename C1R2_, typename C1R3_,
			typename C2R0_, typename C2R1_, typename C2R2_, typename C2R3_,
			typename C3R0_, typename C3R1_, typename C3R2_, typename C3R3_
		>
		FastMatrix4x4f_CM
		(
			const C0R0_& c0r0_, const C0R1_& c0r1_, const C0R2_& c0r2_, const C0R3_& c0r3_,
			const C1R0_& c1r0_, const C1R1_& c1r1_, const C1R2_& c1r2_, const C1R3_& c1r3_,
			const C2R0_& c2r0_, const C2R1_& c2r1_, const C2R2_& c2r2_, const C2R3_& c2r3_,
			const C3R0_& c3r0_, const C3R1_& c3r1_, const C3R2_& c3r2_, const C3R3_& c3r3_
		) :
			column_0(_mm_set_ps(static_cast<float>(c0r3_), static_cast<float>(c0r2_), static_cast<float>(c0r1_), static_cast<float>(c0r0_))),
			column_1(_mm_set_ps(static_cast<float>(c1r3_), static_cast<float>(c1r2_), static_cast<float>(c1r1_), static_cast<float>(c1r0_))),
			column_2(_mm_set_ps(static_cast<float>(c2r3_), static_cast<float>(c2r2_), static_cast<float>(c2r1_), static_cast<float>(c2r0_))),
			column_3(_mm_set_ps(static_cast<float>(c3r3_), static_cast<float>(c3r2_), static_cast<float>(c3r1_), static_cast<float>(c3r0_)))
		{
		}

		template<typename out_contained_type = float, bool OutColumnMajor_ = true>
		[[nodiscard]] EmuMath::Matrix<4, 4, out_contained_type, OutColumnMajor_> Store() const
		{
			if constexpr (std::is_same_v<out_contained_type, float> && OutColumnMajor_)
			{
				EmuMath::Matrix<4, 4, out_contained_type, OutColumnMajor_> out_;
				auto& out_data_ = *out_.data();
				_mm_store_ps(out_data_.template at<0>().data(), column_0);
				_mm_store_ps(out_data_.template at<1>().data(), column_1);
				_mm_store_ps(out_data_.template at<2>().data(), column_2);
				_mm_store_ps(out_data_.template at<3>().data(), column_3);
				return out_;
			}
			else
			{
				static_assert(false, "Additional storage of FastMatrix4x4f not implemented.");
			}
		}

		template<std::size_t Column_>
		[[nodiscard]] __m128 GetColumn() const
		{
			if constexpr (Column_ == 0)
			{
				return column_0;
			}
			else if constexpr (Column_ == 1)
			{
				return column_1;
			}
			else if constexpr (Column_ == 2)
			{
				return column_2;
			}
			else if constexpr (Column_ == 3)
			{
				return column_3;
			}
			else
			{
				static_assert(false, "Attempted to get a column with an invalid index from an EmuMath::FastMatrix4x4f_CM.");
			}
		}
		template<std::size_t Column_>
		[[nodiscard]] EmuMath::Vector<4, float> GetColumnReadable() const
		{
			EmuMath::Vector4<float> out_;
			_mm_store_ps(out_.data(), GetColumn<Column_>());
			return out_;
		}

		template<std::size_t Row_>
		[[nodiscard]] __m128 GetRow() const
		{
			if constexpr (Row_ <= 3)
			{
				__m128 out_0_1 = EmuMath::SIMD::shuffle<Row_, 0, Row_, 0>(column_0, column_1);
				__m128 out_2_3 = EmuMath::SIMD::shuffle<Row_, 0, Row_, 0>(column_2, column_3);
				return EmuMath::SIMD::shuffle<0, 2, 0, 2>(out_0_1, out_2_3);
			}
			else
			{
				static_assert(false, "Attempted to get a column with an invalid index from an EmuMath::FastMatrix4x4f_CM.");
			}
		}
		template<std::size_t Row_>
		[[nodiscard]] EmuMath::Vector<4, float> GetRowReadable() const
		{
			EmuMath::Vector4<float> out_;
			_mm_store_ps(out_.data(), GetRow<Row_>());
			return out_;
		}

		FastMatrix4x4f_CM Transpose() const
		{
			return FastMatrix4x4f_CM(GetRow<0>(), GetRow<1>(), GetRow<2>(), GetRow<3>());
		}

		__m128 column_0;
		__m128 column_1;
		__m128 column_2;
		__m128 column_3;
	};
}

std::ostream& operator<<(std::ostream& stream_, const EmuMath::FastMatrix4x4f_CM& matrix_)
{
	stream_ << matrix_.Store<float, true>();
	return stream_;
}

#endif
