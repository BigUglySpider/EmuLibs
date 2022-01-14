#ifndef EMU_MATH_MATRIX_GET_H_INC_
#define EMU_MATH_MATRIX_GET_H_INC_ 1

#include "_common_matrix_helper_includes.h"

namespace EmuMath::Helpers
{
	/// <summary>
	/// <para> Accesses a reference to the element at the provided column+row index of the passed matrix_. </para>
	/// <para> If a non-contained index may attempt to be accessed (and this is intended behaviour), one should use `matrix_get_theoretical` instead. </para>
	/// </summary>
	/// <param name="matrix_">: EmuMath Matrix to access the specified element of.</param>
	/// <returns>Reference to the element at the provided column and row index within the passed Matrix.</returns>
	template<std::size_t ColumnIndex_, std::size_t RowIndex_, typename T_, std::size_t NumColumns_, std::size_t NumRows_, bool ColumnMajor_>
	[[nodiscard]] constexpr inline typename EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>::value_type& matrix_get
	(
		EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>& matrix_
	)
	{
		return _matrix_underlying::_matrix_get<ColumnIndex_, RowIndex_>(matrix_);
	}

	template<std::size_t ColumnIndex_, std::size_t RowIndex_, typename T_, std::size_t NumColumns_, std::size_t NumRows_, bool ColumnMajor_>
	[[nodiscard]] constexpr inline const typename EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>::value_type& matrix_get
	(
		const EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>& matrix_
	)
	{
		return _matrix_underlying::_matrix_get<ColumnIndex_, RowIndex_>(matrix_);
	}

	/// <summary>
	/// <para> Accesses a reference to the element at the provided flattened index of the passed matrix_. </para>
	/// <para>
	///		The flattened index is always interpreted as column-major, where index (x + 1) is the next item in a column after x,
	///		or the start of the next column if x is the final index of a column.
	/// </para>
	/// <para> If a non-contained index may attempt to be accessed (and this is intended behaviour), one should use `matrix_get_theoretical` instead. </para>
	/// </summary>
	/// <param name="matrix_">: EmuMath Matrix to access the specified element of.</param>
	/// <returns>Reference to the element at the provided flattened index within the passed Matrix.</returns>
	template<std::size_t FlattenedIndex_, typename T_, std::size_t NumColumns_, std::size_t NumRows_, bool ColumnMajor_>
	[[nodiscard]] constexpr inline typename EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>::value_type& matrix_get
	(
		EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>& matrix_
	)
	{
		return _matrix_underlying::_matrix_get<FlattenedIndex_>(matrix_);
	}

	template<std::size_t FlattenedIndex_, typename T_, std::size_t NumColumns_, std::size_t NumRows_, bool ColumnMajor_>
	[[nodiscard]] constexpr inline const typename EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>::value_type& matrix_get
	(
		const EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>& matrix_
	)
	{
		return _matrix_underlying::_matrix_get<FlattenedIndex_>(matrix_);
	}

	/// <summary>
	/// <para> Accesses either a reference to the element at the provided column+row index of the passed matrix_, or an implied-zero value_type_uq of the Matrix type. </para>
	/// </summary>
	/// <param name="matrix_">: EmuMath Matrix to access the specified theoretical element of.</param>
	/// <returns>Reference to the element at the provided column+row index within the passed Matrix_ if the index is contained, otherwise an implied-zero value_type_uq.</returns>
	template<std::size_t ColumnIndex_, std::size_t RowIndex_, typename T_, std::size_t NumColumns_, std::size_t NumRows_, bool ColumnMajor_>
	[[nodiscard]] constexpr inline typename EmuMath::TMP::matrix_theoretical_get_result<ColumnIndex_, RowIndex_, EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>&>::type
	matrix_get_theoretical(EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>& matrix_)
	{
		return _matrix_underlying::_matrix_get_theoretical<ColumnIndex_, RowIndex_>(matrix_);
	}

	template<std::size_t ColumnIndex_, std::size_t RowIndex_, typename T_, std::size_t NumColumns_, std::size_t NumRows_, bool ColumnMajor_>
	[[nodiscard]] constexpr inline typename EmuMath::TMP::matrix_theoretical_get_result<ColumnIndex_, RowIndex_, const EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>&>::type
	matrix_get_theoretical(const EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>& matrix_)
	{
		return _matrix_underlying::_matrix_get_theoretical<ColumnIndex_, RowIndex_>(matrix_);
	}

	/// <summary>
	/// <para> Accesses either a reference to the element at the provided flattened index of the passed matrix_, or an implied-zero value_type_uq of the Matrix type. </para>
	/// <para>
	///		The flattened index is always interpreted as column-major, where index (x + 1) is the next item in a column after x,
	///		or the start of the next column if x is the final index of a column.
	/// </para>
	/// </summary>
	/// <param name="matrix_">: EmuMath Matrix to access the specified theoretical element of.</param>
	/// <returns>Reference to the element at the provided flattened index within the passed Matrix_ if the index is contained, otherwise an implied-zero value_type_uq.</returns>
	template<std::size_t FlattenedIndex_, typename T_, std::size_t NumColumns_, std::size_t NumRows_, bool ColumnMajor_>
	[[nodiscard]] constexpr inline typename EmuMath::TMP::matrix_flattened_theoretical_get_result<FlattenedIndex_, EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>&>::type
	matrix_get_theoretical(EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>& matrix_)
	{
		return _matrix_underlying::_matrix_get_theoretical<FlattenedIndex_>(matrix_);
	}

	template<std::size_t FlattenedIndex_, typename T_, std::size_t NumColumns_, std::size_t NumRows_, bool ColumnMajor_>
	[[nodiscard]] constexpr inline typename EmuMath::TMP::matrix_flattened_theoretical_get_result<FlattenedIndex_, const EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>&>::type
	matrix_get_theoretical(const EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>& matrix_)
	{
		return _matrix_underlying::_matrix_get_theoretical<FlattenedIndex_>(matrix_);
	}
}

#endif
