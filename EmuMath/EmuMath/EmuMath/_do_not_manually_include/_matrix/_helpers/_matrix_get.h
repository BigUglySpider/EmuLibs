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
	/// <para> Accesses a reference to the element at the provided contiguous flattened index of the passed matrix_. </para>
	/// <para> If a non-contained index may attempt to be accessed (and this is intended behaviour), one should use `matrix_get_theoretical` instead. </para>
	/// </summary>
	/// <param name="matrix_">: EmuMath Matrix to access the specified element of.</param>
	/// <returns>Reference to the element at the provided contiguous flattened index within the passed Matrix.</returns>
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
	/// <para>
	///		Accesses either a reference to the element at the provided contiguous flattened index of the passed matrix_, 
	///		or an implied-zero value_type_uq of the Matrix type.
	/// </para>
	/// </summary>
	/// <param name="matrix_">: EmuMath Matrix to access the specified theoretical element of.</param>
	/// <returns>Reference to the element at the provided contiguous flattened index within the passed Matrix_ if the index is contained, otherwise an implied-zero value.</returns>
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
	/// <para> Outputs an EmuMath Vector of elements in the specified Column within the passed EmuMath Matrix. </para>
	/// <para> May output a Vector of references to the elements of the Column, as long as all required indices are contained within the Matrix. </para>
	/// <para> Offset_: Index of the Row at which to start reading the Column at the provided ColumnIndex_. Defaults to 0. </para>
	/// </summary>
	/// <param name="matrix_">: EmuMath Matrix to retrieve a Column from.</param>
	/// <returns>EmuMath Vector of the specified Column within the passed matrix_.</returns>
	template<std::size_t ColumnIndex_, std::size_t OutSize_, typename OutT_, std::size_t Offset_ = 0, typename T_, std::size_t NumColumns_, std::size_t NumRows_, bool ColumnMajor_>
	[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> matrix_get_column(EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>& matrix_)
	{
		return _matrix_underlying::_matrix_get_column<ColumnIndex_, OutSize_, OutT_, Offset_>(matrix_);
	}

	template<std::size_t ColumnIndex_, typename OutT_, std::size_t Offset_ = 0, typename T_, std::size_t NumColumns_, std::size_t NumRows_, bool ColumnMajor_>
	[[nodiscard]] constexpr inline EmuMath::Vector<NumRows_, OutT_> matrix_get_column(EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>& matrix_)
	{
		return _matrix_underlying::_matrix_get_column<ColumnIndex_, NumRows_, OutT_, Offset_>(matrix_);
	}

	template<std::size_t ColumnIndex_, std::size_t OutSize_, std::size_t Offset_ = 0, typename T_, std::size_t NumColumns_, std::size_t NumRows_, bool ColumnMajor_>
	[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, typename EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>::value_type_uq> matrix_get_column
	(
		EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>& matrix_
	)
	{
		using matrix_value_uq = typename EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>::value_type_uq;
		return _matrix_underlying::_matrix_get_column<ColumnIndex_, OutSize_, matrix_value_uq, Offset_>(matrix_);
	}

	template<std::size_t ColumnIndex_, typename T_, std::size_t NumColumns_, std::size_t NumRows_, bool ColumnMajor_>
	[[nodiscard]] constexpr inline EmuMath::Vector<NumRows_, typename EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>::value_type_uq> matrix_get_column
	(
		EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>& matrix_
	)
	{
		using matrix_value_uq = typename EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>::value_type_uq;
		return _matrix_underlying::_matrix_get_column<ColumnIndex_, NumRows_, matrix_value_uq, 0>(matrix_);
	}

	template<std::size_t ColumnIndex_, std::size_t OutSize_, typename OutT_, std::size_t Offset_ = 0, typename T_, std::size_t NumColumns_, std::size_t NumRows_, bool ColumnMajor_>
	[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> matrix_get_column(const EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>& matrix_)
	{
		return _matrix_underlying::_matrix_get_column<ColumnIndex_, OutSize_, OutT_, Offset_>(matrix_);
	}

	template<std::size_t ColumnIndex_, typename OutT_, std::size_t Offset_ = 0, typename T_, std::size_t NumColumns_, std::size_t NumRows_, bool ColumnMajor_>
	[[nodiscard]] constexpr inline EmuMath::Vector<NumRows_, OutT_> matrix_get_column(const EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>& matrix_)
	{
		return _matrix_underlying::_matrix_get_column<ColumnIndex_, NumRows_, OutT_, Offset_>(matrix_);
	}

	template<std::size_t ColumnIndex_, std::size_t OutSize_, std::size_t Offset_ = 0, typename T_, std::size_t NumColumns_, std::size_t NumRows_, bool ColumnMajor_>
	[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, typename EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>::value_type_uq> matrix_get_column
	(
		const EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>& matrix_
	)
	{
		using matrix_value_uq = typename EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>::value_type_uq;
		return _matrix_underlying::_matrix_get_column<ColumnIndex_, OutSize_, matrix_value_uq, Offset_>(matrix_);
	}

	template<std::size_t ColumnIndex_, typename T_, std::size_t NumColumns_, std::size_t NumRows_, bool ColumnMajor_>
	[[nodiscard]] constexpr inline EmuMath::Vector<NumRows_, typename EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>::value_type_uq> matrix_get_column
	(
		const EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>& matrix_
	)
	{
		using matrix_value_uq = typename EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>::value_type_uq;
		return _matrix_underlying::_matrix_get_column<ColumnIndex_, NumRows_, matrix_value_uq, 0>(matrix_);
	}

	/// <summary>
	/// <para> Outputs an EmuMath Vector of elements in the specified Row within the passed EmuMath Matrix. </para>
	/// <para> May output a Vector of references to the elements of the Row, as long as all required indices are contained within the Matrix. </para>
	/// <para> Offset_: Index of the Column at which to start reading the Row at the provided RowIndex_. Defaults to 0. </para>
	/// </summary>
	/// <param name="matrix_">: EmuMath Matrix to retrieve a Row from.</param>
	/// <returns>EmuMath Vector of the specified Row within the passed matrix_.</returns>
	template<std::size_t RowIndex_, std::size_t OutSize_, typename OutT_, std::size_t Offset_ = 0, typename T_, std::size_t NumColumns_, std::size_t NumRows_, bool ColumnMajor_>
	[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> matrix_get_row(EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>& matrix_)
	{
		return _matrix_underlying::_matrix_get_row<RowIndex_, OutSize_, OutT_, Offset_>(matrix_);
	}

	template<std::size_t RowIndex_, typename OutT_, std::size_t Offset_ = 0, typename T_, std::size_t NumColumns_, std::size_t NumRows_, bool ColumnMajor_>
	[[nodiscard]] constexpr inline EmuMath::Vector<NumColumns_, OutT_> matrix_get_row(EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>& matrix_)
	{
		return _matrix_underlying::_matrix_get_row<RowIndex_, NumColumns_, OutT_, Offset_>(matrix_);
	}

	template<std::size_t RowIndex_, std::size_t OutSize_, std::size_t Offset_ = 0, typename T_, std::size_t NumColumns_, std::size_t NumRows_, bool ColumnMajor_>
	[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, typename EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>::value_type_uq> matrix_get_row
	(
		EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>& matrix_
	)
	{
		using matrix_value_uq = typename EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>::value_type_uq;
		return _matrix_underlying::_matrix_get_row<RowIndex_, OutSize_, matrix_value_uq, Offset_>(matrix_);
	}

	template<std::size_t RowIndex_, typename T_, std::size_t NumColumns_, std::size_t NumRows_, bool ColumnMajor_>
	[[nodiscard]] constexpr inline EmuMath::Vector<NumColumns_, typename EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>::value_type_uq> matrix_get_row
	(
		EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>& matrix_
	)
	{
		using matrix_value_uq = typename EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>::value_type_uq;
		return _matrix_underlying::_matrix_get_row<RowIndex_, NumColumns_, matrix_value_uq, 0>(matrix_);
	}

	template<std::size_t RowIndex_, std::size_t OutSize_, typename OutT_, std::size_t Offset_ = 0, typename T_, std::size_t NumColumns_, std::size_t NumRows_, bool ColumnMajor_>
	[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> matrix_get_row(const EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>& matrix_)
	{
		return _matrix_underlying::_matrix_get_row<RowIndex_, OutSize_, OutT_, Offset_>(matrix_);
	}

	template<std::size_t RowIndex_, typename OutT_, std::size_t Offset_ = 0, typename T_, std::size_t NumColumns_, std::size_t NumRows_, bool ColumnMajor_>
	[[nodiscard]] constexpr inline EmuMath::Vector<NumColumns_, OutT_> matrix_get_row(const EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>& matrix_)
	{
		return _matrix_underlying::_matrix_get_row<RowIndex_, NumColumns_, OutT_, Offset_>(matrix_);
	}

	template<std::size_t RowIndex_, std::size_t OutSize_, std::size_t Offset_ = 0, typename T_, std::size_t NumColumns_, std::size_t NumRows_, bool ColumnMajor_>
	[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, typename EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>::value_type_uq> matrix_get_row
	(
		const EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>& matrix_
	)
	{
		using matrix_value_uq = typename EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>::value_type_uq;
		return _matrix_underlying::_matrix_get_row<RowIndex_, OutSize_, matrix_value_uq, Offset_>(matrix_);
	}

	template<std::size_t RowIndex_, typename T_, std::size_t NumColumns_, std::size_t NumRows_, bool ColumnMajor_>
	[[nodiscard]] constexpr inline EmuMath::Vector<NumColumns_, typename EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>::value_type_uq> matrix_get_row
	(
		const EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>& matrix_
	)
	{
		using matrix_value_uq = typename EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>::value_type_uq;
		return _matrix_underlying::_matrix_get_row<RowIndex_, NumColumns_, matrix_value_uq, 0>(matrix_);
	}

	/// <summary>
	/// <para> Outputs an EmuMath Vector of elements in the specified Major Segment within the passed Matrix. </para>
	/// <para> May output a Vector of references to the elements of the Major Segment, as long as all required indices are contained within the Matrix. </para>
	/// <para> If matrix_ is Column Major, this is equivalent to `matrix_get_column`. Otherwise, it is equivalent to `matrix_get_row`. </para>
	/// <para> Offset_: Non-Major index at which to start reading the Major Segment at the provided MajorIndex_. Defaults to 0. </para>
	/// </summary>
	/// <param name="matrix_">: EmuMath Matrix to retrieve a Major Segment from.</param>
	/// <returns>EmuMath Vector of the specified Major Segment within the passed matrix_.</returns>
	template<std::size_t MajorIndex_, std::size_t OutSize_, typename OutT_, std::size_t Offset_ = 0, typename T_, std::size_t NumColumns_, std::size_t NumRows_, bool ColumnMajor_>
	[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> matrix_get_major(EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>& matrix_)
	{
		return _matrix_underlying::_matrix_get_major<MajorIndex_, OutSize_, OutT_, Offset_>(matrix_);
	}

	template<std::size_t MajorIndex_, typename OutT_, std::size_t Offset_ = 0, typename T_, std::size_t NumColumns_, std::size_t NumRows_, bool ColumnMajor_>
	[[nodiscard]] constexpr inline EmuMath::Vector<(ColumnMajor_ ? NumRows_ : NumColumns_), OutT_> matrix_get_major
	(
		EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>& matrix_
	)
	{
		constexpr std::size_t out_size_ = (ColumnMajor_ ? NumRows_ : NumColumns_);
		return _matrix_underlying::_matrix_get_major<MajorIndex_, out_size_, OutT_, Offset_>(matrix_);
	}

	template<std::size_t MajorIndex_, std::size_t OutSize_, std::size_t Offset_ = 0, typename T_, std::size_t NumColumns_, std::size_t NumRows_, bool ColumnMajor_>
	[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, typename EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>::value_type_uq> matrix_get_major
	(
		EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>& matrix_
	)
	{
		using matrix_value_uq = typename EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>::value_type_uq;
		return _matrix_underlying::_matrix_get_major<MajorIndex_, OutSize_, matrix_value_uq, Offset_>(matrix_);
	}

	template<std::size_t MajorIndex_, typename T_, std::size_t NumColumns_, std::size_t NumRows_, bool ColumnMajor_>
	[[nodiscard]] constexpr inline EmuMath::Vector<(ColumnMajor_ ? NumRows_ : NumColumns_), typename EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>::value_type_uq>
	matrix_get_major
	(
		EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>& matrix_
	)
	{
		using matrix_value_uq = typename EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>::value_type_uq;
		constexpr std::size_t out_size_ = (ColumnMajor_ ? NumRows_ : NumColumns_);
		return _matrix_underlying::_matrix_get_major<MajorIndex_, out_size_, matrix_value_uq, 0>(matrix_);
	}

	template<std::size_t MajorIndex_, std::size_t OutSize_, typename OutT_, std::size_t Offset_ = 0, typename T_, std::size_t NumColumns_, std::size_t NumRows_, bool ColumnMajor_>
	[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> matrix_get_major(const EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>& matrix_)
	{
		return _matrix_underlying::_matrix_get_major<MajorIndex_, OutSize_, OutT_, Offset_>(matrix_);
	}

	template<std::size_t MajorIndex_, typename OutT_, std::size_t Offset_ = 0, typename T_, std::size_t NumColumns_, std::size_t NumRows_, bool ColumnMajor_>
	[[nodiscard]] constexpr inline EmuMath::Vector<(ColumnMajor_ ? NumRows_ : NumColumns_), OutT_> matrix_get_major
	(
		const EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>& matrix_
	)
	{
		constexpr std::size_t out_size_ = (ColumnMajor_ ? NumRows_ : NumColumns_);
		return _matrix_underlying::_matrix_get_major<MajorIndex_, out_size_, OutT_, Offset_>(matrix_);
	}

	template<std::size_t MajorIndex_, std::size_t OutSize_, std::size_t Offset_ = 0, typename T_, std::size_t NumColumns_, std::size_t NumRows_, bool ColumnMajor_>
	[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, typename EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>::value_type_uq> matrix_get_major
	(
		const EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>& matrix_
	)
	{
		using matrix_value_uq = typename EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>::value_type_uq;
		return _matrix_underlying::_matrix_get_major<MajorIndex_, OutSize_, matrix_value_uq, Offset_>(matrix_);
	}

	template<std::size_t MajorIndex_, typename T_, std::size_t NumColumns_, std::size_t NumRows_, bool ColumnMajor_>
	[[nodiscard]] constexpr inline EmuMath::Vector<(ColumnMajor_ ? NumRows_ : NumColumns_), typename EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>::value_type_uq>
	matrix_get_major
	(
		const EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>& matrix_
	)
	{
		using matrix_value_uq = typename EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>::value_type_uq;
		constexpr std::size_t out_size_ = (ColumnMajor_ ? NumRows_ : NumColumns_);
		return _matrix_underlying::_matrix_get_major<MajorIndex_, out_size_, matrix_value_uq, 0>(matrix_);
	}

	/// <summary>
	/// <para> Outputs an EmuMath Vector of elements in the specified Non-Major Segment within the passed Matrix. </para>
	/// <para> May output a Vector of references to the elements of the Non-Major Segment, as long as all required indices are contained within the Matrix. </para>
	/// <para> If Matrix is Column Major, this is equivalent to `matrix_get_row`. Otherwise, it is equivalent to `matrix_get_column`. </para>
	/// <para> Offset_: Major index at which to start reading the Non-Major Segment at the provided NonMajorIndex_. Defaults to 0. </para>
	/// </summary>
	/// <param name="matrix_">: EmuMath Matrix to retrieve a Non-Major Segment from.</param>
	/// <returns>EmuMath Vector of the specified Non-Major Segment within the passed matrix_.</returns>
	template<std::size_t MajorIndex_, std::size_t OutSize_, typename OutT_, std::size_t Offset_ = 0, typename T_, std::size_t NumColumns_, std::size_t NumRows_, bool ColumnMajor_>
	[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> matrix_get_non_major(EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>& matrix_)
	{
		return _matrix_underlying::_matrix_get_non_major<MajorIndex_, OutSize_, OutT_, Offset_>(matrix_);
	}

	template<std::size_t MajorIndex_, typename OutT_, std::size_t Offset_ = 0, typename T_, std::size_t NumColumns_, std::size_t NumRows_, bool ColumnMajor_>
	[[nodiscard]] constexpr inline EmuMath::Vector<(ColumnMajor_ ? NumColumns_ : NumRows_), OutT_> matrix_get_non_major
	(
		EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>& matrix_
	)
	{
		constexpr std::size_t out_size_ = (ColumnMajor_ ? NumColumns_ : NumRows_);
		return _matrix_underlying::_matrix_get_non_major<MajorIndex_, out_size_, OutT_, Offset_>(matrix_);
	}

	template<std::size_t MajorIndex_, std::size_t OutSize_, std::size_t Offset_ = 0, typename T_, std::size_t NumColumns_, std::size_t NumRows_, bool ColumnMajor_>
	[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, typename EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>::value_type_uq> matrix_get_non_major
	(
		EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>& matrix_
	)
	{
		using matrix_value_uq = typename EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>::value_type_uq;
		return _matrix_underlying::_matrix_get_non_major<MajorIndex_, OutSize_, matrix_value_uq, Offset_>(matrix_);
	}

	template<std::size_t MajorIndex_, typename T_, std::size_t NumColumns_, std::size_t NumRows_, bool ColumnMajor_>
	[[nodiscard]] constexpr inline EmuMath::Vector<(ColumnMajor_ ? NumColumns_ : NumRows_), typename EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>::value_type_uq>
	matrix_get_non_major
	(
		EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>& matrix_
	)
	{
		using matrix_value_uq = typename EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>::value_type_uq;
		constexpr std::size_t out_size_ = (ColumnMajor_ ? NumColumns_ : NumRows_);
		return _matrix_underlying::_matrix_get_non_major<MajorIndex_, out_size_, matrix_value_uq, 0>(matrix_);
	}

	template<std::size_t MajorIndex_, std::size_t OutSize_, typename OutT_, std::size_t Offset_ = 0, typename T_, std::size_t NumColumns_, std::size_t NumRows_, bool ColumnMajor_>
	[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> matrix_get_non_major(const EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>& matrix_)
	{
		return _matrix_underlying::_matrix_get_non_major<MajorIndex_, OutSize_, OutT_, Offset_>(matrix_);
	}

	template<std::size_t MajorIndex_, typename OutT_, std::size_t Offset_ = 0, typename T_, std::size_t NumColumns_, std::size_t NumRows_, bool ColumnMajor_>
	[[nodiscard]] constexpr inline EmuMath::Vector<(ColumnMajor_ ? NumColumns_ : NumRows_), OutT_> matrix_get_non_major
	(
		const EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>& matrix_
	)
	{
		constexpr std::size_t out_size_ = (ColumnMajor_ ? NumColumns_ : NumRows_);
		return _matrix_underlying::_matrix_get_non_major<MajorIndex_, out_size_, OutT_, Offset_>(matrix_);
	}

	template<std::size_t MajorIndex_, std::size_t OutSize_, std::size_t Offset_ = 0, typename T_, std::size_t NumColumns_, std::size_t NumRows_, bool ColumnMajor_>
	[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, typename EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>::value_type_uq> matrix_get_non_major
	(
		const EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>& matrix_
	)
	{
		using matrix_value_uq = typename EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>::value_type_uq;
		return _matrix_underlying::_matrix_get_non_major<MajorIndex_, OutSize_, matrix_value_uq, Offset_>(matrix_);
	}

	template<std::size_t MajorIndex_, typename T_, std::size_t NumColumns_, std::size_t NumRows_, bool ColumnMajor_>
	[[nodiscard]] constexpr inline EmuMath::Vector<(ColumnMajor_ ? NumColumns_ : NumRows_), typename EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>::value_type_uq>
	matrix_get_non_major
	(
		const EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>& matrix_
	)
	{
		using matrix_value_uq = typename EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>::value_type_uq;
		constexpr std::size_t out_size_ = (ColumnMajor_ ? NumColumns_ : NumRows_);
		return _matrix_underlying::_matrix_get_non_major<MajorIndex_, out_size_, matrix_value_uq, 0>(matrix_);
	}

	/// <summary>
	/// <para> Outputs an EmuMath Vector of elements within the specified Diagonal Segment within the passed Matrix, defaulting to its main diagonal. </para>
	/// <para> ColumnOffset_: Index of the first Column to access. This will increment by 1 for each progressive element in the output Vector. Defaults to 0. </para>
	/// <para> RowOffset_: Index of the first Row to access. This will increment by 1 for each progressive element in the output Vector. Defaults to ColumnOffset_. </para>
	/// <para> May output a Vector of references to the elements of the Diagonal Segment, as long as all required indices are contained within the Matrix. </para>
	/// </summary>
	/// <param name="matrix_">: EmuMath Matrix to retrieve a Diagonal Segment from.</param>
	/// <returns>EmuMath Vector of the specified Diagonal Segment within the passed matrix_.</returns>
	template
	<
		std::size_t OutSize_, typename OutT_, std::size_t ColumnOffset_ = 0, std::size_t RowOffset_ = ColumnOffset_,
		typename T_, std::size_t NumColumns_, std::size_t NumRows_, bool ColumnMajor_
	>
	[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> matrix_get_diagonal(EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>& matrix_)
	{
		return _matrix_underlying::_matrix_get_diagonal<OutSize_, OutT_, ColumnOffset_, RowOffset_>(matrix_);
	}

	template<typename OutT_, std::size_t ColumnOffset_ = 0, std::size_t RowOffset_ = ColumnOffset_, typename T_, std::size_t NumColumns_, std::size_t NumRows_, bool ColumnMajor_>
	[[nodiscard]] constexpr inline EmuMath::Vector<EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>::smallest_direction_size, OutT_>
	matrix_get_diagonal(EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>& matrix_)
	{
		constexpr std::size_t out_size_ = EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>::smallest_direction_size;
		return _matrix_underlying::_matrix_get_diagonal<out_size_, OutT_, ColumnOffset_, RowOffset_>(matrix_);
	}

	template<std::size_t OutSize_, std::size_t ColumnOffset_ = 0, std::size_t RowOffset_ = ColumnOffset_, typename T_, std::size_t NumColumns_, std::size_t NumRows_, bool ColumnMajor_>
	constexpr inline EmuMath::Vector<OutSize_, typename EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>::value_type_uq> matrix_get_diagonal
	(
		EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>& matrix_
	)
	{
		using matrix_value_uq = typename EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>::value_type_uq;
		return _matrix_underlying::_matrix_get_diagonal<OutSize_, matrix_value_uq, ColumnOffset_, RowOffset_>(matrix_);
	}

	template<std::size_t OutSize_, std::size_t ColumnOffset_ = 0, std::size_t RowOffset_ = ColumnOffset_, typename T_, std::size_t NumColumns_, std::size_t NumRows_, bool ColumnMajor_>
	constexpr inline EmuMath::Vector
	<
		EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>::smallest_direction_size,
		typename EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>::value_type_uq
	>
	matrix_get_diagonal
	(
		EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>& matrix_
	)
	{
		using matrix_value_uq = typename EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>::value_type_uq;
		constexpr std::size_t out_size_ = EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>::smallest_direction_size;
		return _matrix_underlying::_matrix_get_diagonal<out_size_, matrix_value_uq, ColumnOffset_, RowOffset_>(matrix_);
	}

	template
	<
		std::size_t OutSize_, typename OutT_, std::size_t ColumnOffset_ = 0, std::size_t RowOffset_ = ColumnOffset_,
		typename T_, std::size_t NumColumns_, std::size_t NumRows_, bool ColumnMajor_
	>
	[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> matrix_get_diagonal(const EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>& matrix_)
	{
		return _matrix_underlying::_matrix_get_diagonal<OutSize_, OutT_, ColumnOffset_, RowOffset_>(matrix_);
	}

	template<typename OutT_, std::size_t ColumnOffset_ = 0, std::size_t RowOffset_ = ColumnOffset_, typename T_, std::size_t NumColumns_, std::size_t NumRows_, bool ColumnMajor_>
	[[nodiscard]] constexpr inline EmuMath::Vector<EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>::smallest_direction_size, OutT_>
	matrix_get_diagonal(const EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>& matrix_)
	{
		constexpr std::size_t out_size_ = EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>::smallest_direction_size;
		return _matrix_underlying::_matrix_get_diagonal<out_size_, OutT_, ColumnOffset_, RowOffset_>(matrix_);
	}

	template<std::size_t OutSize_, std::size_t ColumnOffset_ = 0, std::size_t RowOffset_ = ColumnOffset_, typename T_, std::size_t NumColumns_, std::size_t NumRows_, bool ColumnMajor_>
	constexpr inline EmuMath::Vector<OutSize_, typename EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>::value_type_uq> matrix_get_diagonal
	(
		const EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>& matrix_
	)
	{
		using matrix_value_uq = typename EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>::value_type_uq;
		return _matrix_underlying::_matrix_get_diagonal<OutSize_, matrix_value_uq, ColumnOffset_, RowOffset_>(matrix_);
	}

	template<std::size_t OutSize_, std::size_t ColumnOffset_ = 0, std::size_t RowOffset_ = ColumnOffset_, typename T_, std::size_t NumColumns_, std::size_t NumRows_, bool ColumnMajor_>
	constexpr inline EmuMath::Vector
	<
		EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>::smallest_direction_size,
		typename EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>::value_type_uq
	>
	matrix_get_diagonal
	(
		const EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>& matrix_
	)
	{
		using matrix_value_uq = typename EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>::value_type_uq;
		constexpr std::size_t out_size_ = EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>::smallest_direction_size;
		return _matrix_underlying::_matrix_get_diagonal<out_size_, matrix_value_uq, ColumnOffset_, RowOffset_>(matrix_);
	}
}

#endif
