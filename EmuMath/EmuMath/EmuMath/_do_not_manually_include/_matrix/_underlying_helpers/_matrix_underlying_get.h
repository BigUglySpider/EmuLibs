#ifndef EMU_MATH_MATRIX_UNDERLYING_GET_H_INC_
#define EMU_MATH_MATRIX_UNDERLYING_GET_H_INC_ 1

#include "_matrix_tmp.h"

namespace EmuMath::Helpers::_matrix_underlying
{
	// FLATTENED GETS
	template<std::size_t FlattenedIndex_, typename T_, std::size_t NumColumns_, std::size_t NumRows_, bool ColumnMajor_>
	[[nodiscard]] constexpr inline typename EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>::value_type& _matrix_get
	(
		EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>& matrix_
	)
	{
		return matrix_.template at<FlattenedIndex_>();
	}

	template<std::size_t FlattenedIndex_, typename T_, std::size_t NumColumns_, std::size_t NumRows_, bool ColumnMajor_>
	[[nodiscard]] constexpr inline const typename EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>::value_type& _matrix_get
	(
		const EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>& matrix_
	)
	{
		return matrix_.template at<FlattenedIndex_>();
	}

	// COLUMN-ROW GETS
	template<std::size_t ColumnIndex_, std::size_t RowIndex_, typename T_, std::size_t NumColumns_, std::size_t NumRows_, bool ColumnMajor_>
	[[nodiscard]] constexpr inline typename EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>::value_type& _matrix_get
	(
		EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>& matrix_
	)
	{
		return matrix_.template at<ColumnIndex_, RowIndex_>();
	}

	template<std::size_t ColumnIndex_, std::size_t RowIndex_, typename T_, std::size_t NumColumns_, std::size_t NumRows_, bool ColumnMajor_>
	[[nodiscard]] constexpr inline const typename EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>::value_type& _matrix_get
	(
		const EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>& matrix_
	)
	{
		return matrix_.template at<ColumnIndex_, RowIndex_>();
	}

	// COLUMN GETS
	template<std::size_t ColumnIndex_, typename T_, std::size_t NumColumns_, std::size_t NumRows_, bool ColumnMajor_>
	[[nodiscard]] constexpr inline typename EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>::column_get_ref_type _matrix_get_column
	(
		EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>& matrix_
	)
	{
		return matrix_.template GetColumn<ColumnIndex_>();
	}

	template<std::size_t ColumnIndex_, typename T_, std::size_t NumColumns_, std::size_t NumRows_, bool ColumnMajor_>
	[[nodiscard]] constexpr inline typename EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>::column_get_const_ref_type _matrix_get_column
	(
		const EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>& matrix_
	)
	{
		return matrix_.template GetColumn<ColumnIndex_>();
	}

	// ROW GETS
	template<std::size_t RowIndex_, typename T_, std::size_t NumColumns_, std::size_t NumRows_, bool ColumnMajor_>
	[[nodiscard]] constexpr inline typename EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>::row_get_ref_type _matrix_get_row
	(
		EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>& matrix_
	)
	{
		return matrix_.template GetRow<RowIndex_>();
	}

	template<std::size_t RowIndex_, typename T_, std::size_t NumColumns_, std::size_t NumRows_, bool ColumnMajor_>
	[[nodiscard]] constexpr inline typename EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>::row_get_const_ref_type _matrix_get_row
	(
		const EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>& matrix_
	)
	{
		return matrix_.template GetRow<RowIndex_>();
	}

	// MAJOR GETS
	template<std::size_t MajorIndex_, typename T_, std::size_t NumColumns_, std::size_t NumRows_, bool ColumnMajor_>
	[[nodiscard]] constexpr inline typename EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>::major_get_ref_type _matrix_get_major
	(
		EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>& matrix_
	)
	{
		return matrix_.template GetMajor<MajorIndex_>();
	}

	template<std::size_t MajorIndex_, typename T_, std::size_t NumColumns_, std::size_t NumRows_, bool ColumnMajor_>
	[[nodiscard]] constexpr inline typename EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>::major_get_const_ref_type _matrix_get_major
	(
		const EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>& matrix_
	)
	{
		return matrix_.template GetMajor<MajorIndex_>();
	}

	// NON-MAJOR GETS
	template<std::size_t NonMajorIndex_, typename T_, std::size_t NumColumns_, std::size_t NumRows_, bool ColumnMajor_>
	[[nodiscard]] constexpr inline typename EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>::non_major_get_ref_type _matrix_get_non_major
	(
		EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>& matrix_
	)
	{
		return matrix_.template GetNonMajor<NonMajorIndex_>();
	}

	template<std::size_t NonMajorIndex_, typename T_, std::size_t NumColumns_, std::size_t NumRows_, bool ColumnMajor_>
	[[nodiscard]] constexpr inline typename EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>::non_major_get_const_ref_type _matrix_get_non_major
	(
		const EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>& matrix_
	)
	{
		return matrix_.template GetNonMajor<NonMajorIndex_>();
	}
}

#endif
