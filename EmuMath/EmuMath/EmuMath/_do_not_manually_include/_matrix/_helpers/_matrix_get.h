#ifndef EMU_MATH_MATRIX_GET_H_INC_
#define EMU_MATH_MATRIX_GET_H_INC_ 1

#include "_common_matrix_helper_includes.h"

namespace EmuMath::Helpers
{
	/// <summary>
	/// <para> Outputs an implied-zero value that all non-contained elements of the provided Matrix_ type will be interpreted as. </para>
	/// </summary>
	/// <returns>
	///		A value of Matrix_'s value_type_uq type, default constructed, constructed with an argument of 0, 
	///		or constructed with an argument of 0.0f, whichever is possible and earliest in the listed order.
	/// </returns>
	template<class Matrix_, typename = std::enable_if_t<EmuMath::TMP::is_emu_matrix_v<Matrix_>>>
	[[nodiscard]] constexpr inline typename EmuCore::TMP::remove_ref_cv_t<Matrix_>::value_type_uq matrix_get_non_contained()
	{
		return _matrix_underlying::_matrix_get_non_contained<Matrix_>();
	}

	template<std::size_t NumColumns_, std::size_t NumRows_, typename T_, bool ColumnMajor_>
	[[nodiscard]] constexpr inline typename EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>::value_type_uq matrix_get_non_contained()
	{
		return _matrix_underlying::_matrix_get_non_contained<EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>>();
	}

	/// <summary>
	/// <para> Outputs an implied-zero Vector representing a non-contained column of the provided Matrix_ type. </para>
	/// </summary>
	/// <returns>
	///		By default, a Vector the same size as the passed Matrix_'s columns, containing value_type_uq elements that are default constructed, 
	///		constructed with an argument of 0, or constructed with an argument of 0.0f, whichever is possible and earliest in the listed order.
	/// </returns>
	template<class Matrix_, typename = std::enable_if_t<EmuMath::TMP::is_emu_matrix_v<Matrix_>>>
	[[nodiscard]] constexpr inline typename EmuMath::TMP::matrix_non_contained_column<Matrix_>::type matrix_get_column_non_contained()
	{
		return _matrix_underlying::_matrix_get_column_non_contained<Matrix_>();
	}

	template<std::size_t NumColumns_, std::size_t NumRows_, typename T_, bool ColumnMajor_>
	[[nodiscard]] constexpr inline typename EmuMath::TMP::matrix_non_contained_column<EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>>::type
	matrix_get_column_non_contained()
	{
		return _matrix_underlying::_matrix_get_column_non_contained<EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>>();
	}

	/// <summary>
	/// <para> Outputs an implied-zero Vector representing a non-contained row of the provided Matrix_ type. </para>
	/// </summary>
	/// <returns>
	///		By default, a Vector the same size as the passed Matrix_'s rows, containing value_type_uq elements that are default constructed, 
	///		constructed with an argument of 0, or constructed with an argument of 0.0f, whichever is possible and earliest in the listed order.
	/// </returns>
	template<class Matrix_, typename = std::enable_if_t<EmuMath::TMP::is_emu_matrix_v<Matrix_>>>
	[[nodiscard]] constexpr inline typename EmuMath::TMP::matrix_non_contained_row<Matrix_>::type matrix_get_row_non_contained()
	{
		return _matrix_underlying::_matrix_get_row_non_contained<Matrix_>();
	}

	template<std::size_t NumColumns_, std::size_t NumRows_, typename T_, bool ColumnMajor_>
	[[nodiscard]] constexpr inline typename EmuMath::TMP::matrix_non_contained_row<EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>>::type
	matrix_get_row_non_contained()
	{
		return _matrix_underlying::_matrix_get_row_non_contained<EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>>();
	}

	/// <summary>
	/// <para> Outputs an implied-zero Vector representing a non-contained major element of the provided Matrix_ type. </para>
	/// </summary>
	/// <returns> If Matrix_ is column-major, the same as matrix_get_column_non_contained. Otherwise, the same as matrix_get_row_non_contained. </returns>
	template<class Matrix_, typename = std::enable_if_t<EmuMath::TMP::is_emu_matrix_v<Matrix_>>>
	[[nodiscard]] constexpr inline decltype(_matrix_underlying::_matrix_get_major_non_contained<Matrix_>()) matrix_get_major_non_contained()
	{
		return _matrix_underlying::_matrix_get_major_non_contained<Matrix_>();
	}

	template<std::size_t NumColumns_, std::size_t NumRows_, typename T_, bool ColumnMajor_>
	[[nodiscard]] constexpr inline decltype(_matrix_underlying::_matrix_get_major_non_contained<EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>>())
	matrix_get_major_non_contained()
	{
		return _matrix_underlying::_matrix_get_major_non_contained<EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>>();
	}

	/// <summary>
	/// <para> Outputs an implied-zero Vector representing a non-contained non-major element of the provided Matrix_ type. </para>
	/// </summary>
	/// <returns> If Matrix_ is column-major, the same as matrix_get_row_non_contained. Otherwise, the same as matrix_get_column_non_contained. </returns>
	template<class Matrix_, typename = std::enable_if_t<EmuMath::TMP::is_emu_matrix_v<Matrix_>>>
	[[nodiscard]] constexpr inline decltype(_matrix_underlying::_matrix_get_non_major_non_contained<Matrix_>()) matrix_get_non_major_non_contained()
	{
		return _matrix_underlying::_matrix_get_non_major_non_contained<Matrix_>();
	}

	template<std::size_t NumColumns_, std::size_t NumRows_, typename T_, bool ColumnMajor_>
	[[nodiscard]] constexpr inline decltype(_matrix_underlying::_matrix_get_non_major_non_contained<EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>>())
	matrix_get_non_major_non_contained()
	{
		return _matrix_underlying::_matrix_get_non_major_non_contained<EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>>();
	}

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

	/// <summary>
	/// <para> Accesses the column at the provided ColumnIndex_ within the passed matrix_. </para>
	/// <para> If matrix_ is column-major: This will be a direct reference to the specified column. </para>
	/// <para> If matrix_ is not column-major: This will be an EmuMath Vector of references to elements at respective points within the specified column. </para>
	/// </summary>
	/// <param name="matrix_">: EmuMath Matrix to access the specified column of.</param>
	/// <returns>EmuMath Vector referencing the specified column within the passed matrix_.</returns>
	template<std::size_t ColumnIndex_, typename T_, std::size_t NumColumns_, std::size_t NumRows_, bool ColumnMajor_>
	[[nodiscard]] constexpr inline typename EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>::column_get_ref_type matrix_get_column
	(
		EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>& matrix_
	)
	{
		return _matrix_underlying::_matrix_get_column<ColumnIndex_>(matrix_);
	}

	template<std::size_t ColumnIndex_, typename T_, std::size_t NumColumns_, std::size_t NumRows_, bool ColumnMajor_>
	[[nodiscard]] constexpr inline typename EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>::column_get_const_ref_type matrix_get_column
	(
		const EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>& matrix_
	)
	{
		return _matrix_underlying::_matrix_get_column<ColumnIndex_>(matrix_);
	}

	/// <summary>
	/// <para> Accesses the theoretical column at the provided ColumnIndex_ within the passed matrix_. </para>
	/// <para> If matrix_ is column-major and the index is contained: This will be a direct reference to the specified column. </para>
	/// <para> 
	///		If matrix_ is not column-major and the index is contained: This will be an EmuMath Vector of references to elements at respective points within the specified column. 
	/// </para>
	/// <para> If the index is not contained: This will be an implied-zero column for the type of matrix_. </para>
	/// </summary>
	/// <param name="matrix_">: EmuMath Matrix to access the specified column of.</param>
	/// <returns>EmuMath Vector referencing the specified column within the passed matrix_, or an implied-zero column if the index is not contained.</returns>
	template<std::size_t ColumnIndex_, typename T_, std::size_t NumColumns_, std::size_t NumRows_, bool ColumnMajor_>
	[[nodiscard]] constexpr inline typename EmuMath::TMP::matrix_column_theoretical_get_result<ColumnIndex_, EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>&>::type
	matrix_get_column_theoretical
	(
		EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>& matrix_
	)
	{
		return _matrix_underlying::_matrix_get_column_theoretical<ColumnIndex_>(matrix_);
	}

	template<std::size_t ColumnIndex_, typename T_, std::size_t NumColumns_, std::size_t NumRows_, bool ColumnMajor_>
	[[nodiscard]] constexpr inline typename EmuMath::TMP::matrix_column_theoretical_get_result<ColumnIndex_, const EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>&>::type
	matrix_get_column_theoretical
	(
		const EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>& matrix_
	)
	{
		return _matrix_underlying::_matrix_get_column_theoretical<ColumnIndex_>(matrix_);
	}

	/// <summary>
	/// <para> Accesses the column at the provided RowIndex_ within the passed matrix_. </para>
	/// <para> If matrix_ is column-major: This will be a direct reference to the specified column. </para>
	/// <para> If matrix_ is not column-major: This will be an EmuMath Vector of references to elements at respective points within the specified column. </para>
	/// </summary>
	/// <param name="matrix_">: EmuMath Matrix to access the specified row of.</param>
	/// <returns>EmuMath Vector referencing the specified row within the passed matrix_.</returns>
	template<std::size_t RowIndex_, typename T_, std::size_t NumColumns_, std::size_t NumRows_, bool ColumnMajor_>
	[[nodiscard]] constexpr inline typename EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>::row_get_ref_type matrix_get_row
	(
		EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>& matrix_
	)
	{
		return _matrix_underlying::_matrix_get_row<RowIndex_>(matrix_);
	}

	template<std::size_t RowIndex_, typename T_, std::size_t NumColumns_, std::size_t NumRows_, bool ColumnMajor_>
	[[nodiscard]] constexpr inline typename EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>::row_get_const_ref_type matrix_get_row
	(
		const EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>& matrix_
	)
	{
		return _matrix_underlying::_matrix_get_row<RowIndex_>(matrix_);
	}

	/// <summary>
	/// <para> Accesses the theoretical row at the provided RowIndex_ within the passed matrix_. </para>
	/// <para> If matrix_ is column-major and the index is contained: This will be an EmuMath Vector of references to elements at respective points within the specified row. </para>
	/// <para> If matrix_ is not column-major and the index is contained: This will be a direct reference to the specified row. </para>
	/// <para> If the index is not contained: This will be an implied-zero row for the type of matrix_. </para>
	/// </summary>
	/// <param name="matrix_">: EmuMath Matrix to access the specified row of.</param>
	/// <returns>EmuMath Vector referencing the specified row within the passed matrix_, or an implied-zero row if the index is not contained.</returns>
	template<std::size_t RowIndex_, typename T_, std::size_t NumColumns_, std::size_t NumRows_, bool ColumnMajor_>
	[[nodiscard]] constexpr inline typename EmuMath::TMP::matrix_row_theoretical_get_result<RowIndex_, EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>&>::type
	matrix_get_row_theoretical
	(
		EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>& matrix_
	)
	{
		return _matrix_underlying::_matrix_get_row_theoretical<RowIndex_>(matrix_);
	}

	template<std::size_t RowIndex_, typename T_, std::size_t NumColumns_, std::size_t NumRows_, bool ColumnMajor_>
	[[nodiscard]] constexpr inline typename EmuMath::TMP::matrix_row_theoretical_get_result<RowIndex_, const EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>&>::type
	matrix_get_row_theoretical
	(
		const EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>& matrix_
	)
	{
		return _matrix_underlying::_matrix_get_row_theoretical<RowIndex_>(matrix_);
	}

	/// <summary>
	/// <para> Accesses the major element at the provided MajorIndex_ within the passed matrix_. </para>
	/// <para> If the passed matrix_ is column-major: This will be a reference to the column at the specified MajorIndex_. </para>
	/// <para> If the passed matrix_ is not column-major: This will be a reference to the row at the specified MajorIndex_. </para>
	/// </summary>
	/// <returns>EmuMath Vector referencing the specified major element within the passed matrix_.</returns>
	template<std::size_t MajorIndex_, typename T_, std::size_t NumColumns_, std::size_t NumRows_, bool ColumnMajor_>
	[[nodiscard]] constexpr inline typename EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>::major_get_ref_type matrix_get_major
	(
		EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>& matrix_
	)
	{
		return _matrix_underlying::_matrix_get_major<MajorIndex_>(matrix_);
	}

	template<std::size_t MajorIndex_, typename T_, std::size_t NumColumns_, std::size_t NumRows_, bool ColumnMajor_>
	[[nodiscard]] constexpr inline typename EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>::major_get_const_ref_type matrix_get_major
	(
		const EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>& matrix_
	)
	{
		return _matrix_underlying::_matrix_get_major<MajorIndex_>(matrix_);
	}

	/// <summary>
	/// <para> Accesses the theoretical major element at the provided MajorIndex_ within the passed matrix_. </para>
	/// <para> If the passed matrix_ is column-major and the index is contained: This will be a reference to the column at the specified MajorIndex_. </para>
	/// <para> If the passed matrix_ is not column-major and the index is contained: This will be a reference to the row at the specified MajorIndex_. </para>
	/// <para> If the passed matrix_ is column-major and the index is not contained: This will be an implied-zero column for the provided matrix_. </para>
	/// <para> If the passed matrix_ is not column-major and the index is not contained: This will be an implied-zero row for the provided matrix_. </para>
	/// </summary>
	/// <param name="matrix_">: EmuMath Matrix to access the specified major element of.</param>
	/// <returns>EmuMath Vector referencing the specified major element within the passed matrix_, or an implied-zero non-major element if it is not contained.</returns>
	template<std::size_t MajorIndex_, typename T_, std::size_t NumColumns_, std::size_t NumRows_, bool ColumnMajor_>
	[[nodiscard]] constexpr inline typename EmuMath::TMP::matrix_major_theoretical_get_result<MajorIndex_, EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>&>::type
	matrix_get_major_theoretical
	(
		EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>& matrix_
	)
	{
		return _matrix_underlying::_matrix_get_major_theoretical<MajorIndex_>(matrix_);
	}

	template<std::size_t MajorIndex_, typename T_, std::size_t NumColumns_, std::size_t NumRows_, bool ColumnMajor_>
	[[nodiscard]] constexpr inline typename EmuMath::TMP::matrix_major_theoretical_get_result<MajorIndex_, const EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>&>::type
	matrix_get_major_theoretical
	(
		const EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>& matrix_
	)
	{
		return _matrix_underlying::_matrix_get_major_theoretical<MajorIndex_>(matrix_);
	}

	/// <summary>
	/// <para> Accesses the non-major element at the provided NonMajorIndex_ within the passed matrix_. </para>
	/// <para> If the passed matrix_ is column-major: This will be a reference to the row at the specified MajorIndex_. </para>
	/// <para> If the passed matrix_ is not column-major: This will be a reference to the column at the specified MajorIndex_. </para>
	/// </summary>
	/// <returns>EmuMath Vector referencing the specified non-major element within the passed matrix_.</returns>
	template<std::size_t NonMajorIndex_, typename T_, std::size_t NumColumns_, std::size_t NumRows_, bool ColumnMajor_>
	[[nodiscard]] constexpr inline typename EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>::non_major_get_ref_type matrix_get_non_major
	(
		EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>& matrix_
	)
	{
		return _matrix_underlying::_matrix_get_non_major<NonMajorIndex_>(matrix_);
	}

	template<std::size_t NonMajorIndex_, typename T_, std::size_t NumColumns_, std::size_t NumRows_, bool ColumnMajor_>
	[[nodiscard]] constexpr inline typename EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>::non_major_get_const_ref_type matrix_get_non_major
	(
		const EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>& matrix_
	)
	{
		return _matrix_underlying::_matrix_get_non_major<NonMajorIndex_>(matrix_);
	}

	/// <summary>
	/// <para> Accesses the theoretical non-major element at the provided NonMajorIndex_ within the passed matrix_. </para>
	/// <para> If the passed matrix_ is column-major and the index is contained: This will be a reference to the row at the specified MajorIndex_. </para>
	/// <para> If the passed matrix_ is not column-major and the index is contained: This will be a reference to the column at the specified MajorIndex_. </para>
	/// <para> If the passed matrix_ is column-major and the index is not contained: This will be an implied-zero row for the provided matrix_. </para>
	/// <para> If the passed matrix_ is not column-major and the index is not contained: This will be an implied-zero column for the provided matrix_. </para>
	/// </summary>
	/// <param name="matrix_">: EmuMath Matrix to access the specified non-major element of.</param>
	/// <returns>EmuMath Vector referencing the specified non-major element within the passed matrix_, or an implied-zero non-major element if it is not contained.</returns>
	template<std::size_t NonMajorIndex_, typename T_, std::size_t NumColumns_, std::size_t NumRows_, bool ColumnMajor_>
	[[nodiscard]] constexpr inline typename EmuMath::TMP::matrix_non_major_theoretical_get_result<NonMajorIndex_, EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>&>::type
	matrix_get_non_major_theoretical
	(
		EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>& matrix_
	)
	{
		return _matrix_underlying::_matrix_get_non_major_theoretical<NonMajorIndex_>(matrix_);
	}

	template<std::size_t NonMajorIndex_, typename T_, std::size_t NumColumns_, std::size_t NumRows_, bool ColumnMajor_>
	[[nodiscard]] constexpr inline typename EmuMath::TMP::matrix_non_major_theoretical_get_result<NonMajorIndex_, const EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>&>::type
	matrix_get_non_major_theoretical
	(
		const EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>& matrix_
	)
	{
		return _matrix_underlying::_matrix_get_non_major_theoretical<NonMajorIndex_>(matrix_);
	}
}

#endif
