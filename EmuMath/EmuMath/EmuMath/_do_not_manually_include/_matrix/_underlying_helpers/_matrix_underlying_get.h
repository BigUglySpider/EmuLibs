#ifndef EMU_MATH_MATRIX_UNDERLYING_GET_H_INC_
#define EMU_MATH_MATRIX_UNDERLYING_GET_H_INC_ 1

#include "_matrix_tmp.h"

namespace EmuMath::Helpers::_matrix_underlying
{
	// VALID COLUMN-ROW RANGE CHECK
	template<std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_>
	[[nodiscard]] constexpr inline bool _matrix_index_range_is_valid()
	{
		return (BeginColumn_ < EndColumn_) && (BeginRow_ < EndRow_);
	}

	// VALID+CONTAINED COLUMN RANGE CHECK
	template<std::size_t BeginColumn_, std::size_t EndColumn_, class Matrix_, typename = std::enable_if_t<EmuMath::TMP::is_emu_matrix_v<Matrix_>>>
	[[nodiscard]] constexpr inline bool _matrix_column_range_is_valid_and_contained()
	{
		using mat_uq = typename EmuCore::TMP::remove_ref_cv<Matrix_>::type;
		return
		(
			(BeginColumn_ >= 0 && BeginColumn_ < mat_uq::num_columns) &&
			(EndColumn_ > BeginColumn_ && EndColumn_ <= mat_uq::num_columns)
		);
	}

	// VALID+CONTAINED ROW RANGE CHECK
	template<std::size_t BeginRow_, std::size_t EndRow_, class Matrix_, typename = std::enable_if_t<EmuMath::TMP::is_emu_matrix_v<Matrix_>>>
	[[nodiscard]] constexpr inline bool _matrix_row_range_is_valid_and_contained()
	{
		using mat_uq = typename EmuCore::TMP::remove_ref_cv<Matrix_>::type;
		return
		(
			(BeginRow_ >= 0 && BeginRow_ < mat_uq::num_rows) &&
			(EndRow_ > BeginRow_ && EndRow_ <= mat_uq::num_rows)
		);
	}

	// VALID+CONTAINED COLUMN-ROW RANGE CHECK
	template
	<
		std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_, class Matrix_,
		typename = std::enable_if_t<EmuMath::TMP::is_emu_matrix_v<Matrix_>>
	>
	[[nodiscard]] constexpr inline bool _matrix_index_range_is_valid_and_contained()
	{
		using mat_uq = typename EmuCore::TMP::remove_ref_cv<Matrix_>::type;
		return 
		(
			_matrix_column_range_is_valid_and_contained<BeginColumn_, EndColumn_, mat_uq>() &&
			_matrix_row_range_is_valid_and_contained<BeginRow_, EndRow_, mat_uq>()
		);
	}

	// CONTAINED FLATTENED INDEX CHECK
	template<std::size_t FlattenedIndex_, class Matrix_, typename = std::enable_if_t<EmuMath::TMP::is_emu_matrix_v<Matrix_>>>
	[[nodiscard]] constexpr inline bool _matrix_index_is_contained()
	{
		return FlattenedIndex_ < EmuCore::TMP::remove_ref_cv_t<Matrix_>::size;
	}

	template<std::size_t FlattenedIndex_, std::size_t NumColumns_, std::size_t NumRows_, typename T_, bool ColumnMajor_>
	[[nodiscard]] constexpr inline bool _matrix_index_is_contained()
	{
		return _matrix_index_is_contained<FlattenedIndex_, EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>>();
	}

	// CONTAINED COLUMN-ROW INDEX CHECK
	template<std::size_t ColumnIndex_, std::size_t RowIndex_, class Matrix_, typename = std::enable_if_t<EmuMath::TMP::is_emu_matrix_v<Matrix_>>>
	[[nodiscard]] constexpr inline bool _matrix_index_is_contained()
	{
		return (ColumnIndex_ < EmuCore::TMP::remove_ref_cv_t<Matrix_>::num_columns) && (RowIndex_ < EmuCore::TMP::remove_ref_cv_t<Matrix_>::num_rows);
	}

	template<std::size_t ColumnIndex_, std::size_t RowIndex_, std::size_t NumColumns_, std::size_t NumRows_, typename T_, bool ColumnMajor_>
	[[nodiscard]] constexpr inline bool _matrix_index_is_contained()
	{
		return _matrix_index_is_contained<ColumnIndex_, RowIndex_, EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>>();
	}

	// CONTAINED COLUMN INDEX CHECK
	template<std::size_t ColumnIndex_, class Matrix_, typename = std::enable_if_t<EmuMath::TMP::is_emu_matrix_v<Matrix_>>>
	[[nodiscard]] constexpr inline bool _matrix_column_is_contained()
	{
		return ColumnIndex_ < EmuCore::TMP::remove_ref_cv_t<Matrix_>::num_columns;
	}

	template<std::size_t ColumnIndex_, std::size_t NumColumns_, std::size_t NumRows_, typename T_, bool ColumnMajor_>
	[[nodiscard]] constexpr inline bool _matrix_column_is_contained()
	{
		return _matrix_column_is_contained<ColumnIndex_, EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>>();
	}

	// CONTAINED ROW INDEX CHECK
	template<std::size_t RowIndex_, class Matrix_, typename = std::enable_if_t<EmuMath::TMP::is_emu_matrix_v<Matrix_>>>
	[[nodiscard]] constexpr inline bool _matrix_row_is_contained()
	{
		return RowIndex_ < EmuCore::TMP::remove_ref_cv_t<Matrix_>::num_rows;
	}

	template<std::size_t RowIndex_, std::size_t NumColumns_, std::size_t NumRows_, typename T_, bool ColumnMajor_>
	[[nodiscard]] constexpr inline bool _matrix_row_is_contained()
	{
		return _matrix_row_is_contained<RowIndex_, EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>>();
	}

	// CONTAINED MAJOR INDEX CHECK
	template<std::size_t MajorIndex_, class Matrix_, typename = std::enable_if_t<EmuMath::TMP::is_emu_matrix_v<Matrix_>>>
	[[nodiscard]] constexpr inline bool _matrix_major_is_contained()
	{
		return MajorIndex_ < EmuCore::TMP::remove_ref_cv_t<Matrix_>::num_major_elements;
	}

	template<std::size_t MajorIndex_, std::size_t NumColumns_, std::size_t NumRows_, typename T_, bool ColumnMajor_>
	[[nodiscard]] constexpr inline bool _matrix_major_is_contained()
	{
		return _matrix_major_is_contained<MajorIndex_, EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>>();
	}

	// CONTAINED NON-MAJOR INDEX CHECK
	template<std::size_t NonMajorIndex_, class Matrix_, typename = std::enable_if_t<EmuMath::TMP::is_emu_matrix_v<Matrix_>>>
	[[nodiscard]] constexpr inline bool _matrix_non_major_is_contained()
	{
		return NonMajorIndex_ < EmuCore::TMP::remove_ref_cv_t<Matrix_>::num_non_major_elements;
	}

	template<std::size_t NonMajorIndex_, std::size_t NumColumns_, std::size_t NumRows_, typename T_, bool ColumnMajor_>
	[[nodiscard]] constexpr inline bool _matrix_non_major_is_contained()
	{
		return _matrix_non_major_is_contained<NonMajorIndex_, EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>>();
	}

	// NON-CONTAINED GET
	template<class Matrix_, typename = std::enable_if_t<EmuMath::TMP::is_emu_matrix_v<Matrix_>>>
	[[nodiscard]] constexpr inline typename EmuCore::TMP::remove_ref_cv_t<Matrix_>::value_type_uq _matrix_get_non_contained()
	{
		if constexpr (std::is_default_constructible_v<typename Matrix_::value_type_uq>)
		{
			return typename Matrix_::value_type_uq();
		}
		else if constexpr (EmuCore::TMP::is_valid_make_constant_call<typename Matrix_::value_type_uq, 0, float>())
		{
			return EmuCore::TMP::make_constant<typename Matrix_::value_type_uq, 0, float>();
		}
		else
		{
			static_assert
			(
				EmuCore::TMP::get_false<Matrix_>(),
				"Attempted to create a non-contained element of an EmuMath Matrix, but the provided Matrix_ type cannot have its unqualified value type default-constructed or constructed with a constant of either 0 or 0.0f."
			);
		}
	}

	template<std::size_t NumColumns_, std::size_t NumRows_, typename T_, bool ColumnMajor_>
	[[nodiscard]] constexpr inline typename EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>::value_type_uq _matrix_get_non_contained()
	{
		return _matrix_get_non_contained<EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>>();
	}

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

	// FLATTENED THEORETICAL GETS
	template<std::size_t FlattenedIndex_, typename T_, std::size_t NumColumns_, std::size_t NumRows_, bool ColumnMajor_>
	[[nodiscard]] constexpr inline typename EmuMath::TMP::matrix_flattened_theoretical_get_result<FlattenedIndex_, EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>&>::type
	_matrix_get_theoretical(EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>& matrix_)
	{
		using matrix_type = EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>;
		if constexpr (EmuMath::TMP::is_theoretical_flattened_matrix_index<FlattenedIndex_, matrix_type>::value)
		{
			return _matrix_get_non_contained<matrix_type>();
		}
		else
		{
			return matrix_.template at<FlattenedIndex_>();
		}
	}

	template<std::size_t FlattenedIndex_, typename T_, std::size_t NumColumns_, std::size_t NumRows_, bool ColumnMajor_>
	[[nodiscard]] constexpr inline typename EmuMath::TMP::matrix_flattened_theoretical_get_result<FlattenedIndex_, const EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>&>::type
	_matrix_get_theoretical(const EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>& matrix_)
	{
		using matrix_type = EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>;
		if constexpr (EmuMath::TMP::is_theoretical_flattened_matrix_index<FlattenedIndex_, matrix_type>::value)
		{
			return _matrix_get_non_contained<matrix_type>();
		}
		else
		{
			return matrix_.template at<FlattenedIndex_>();
		}
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

	// COLUMN-ROW THEORETICAL GETS
	template<std::size_t ColumnIndex_, std::size_t RowIndex_, typename T_, std::size_t NumColumns_, std::size_t NumRows_, bool ColumnMajor_>
	[[nodiscard]] constexpr inline typename EmuMath::TMP::matrix_theoretical_get_result<ColumnIndex_, RowIndex_, EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>&>::type
	_matrix_get_theoretical(EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>& matrix_)
	{
		using matrix_type = EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>;
		if constexpr (EmuMath::TMP::is_theoretical_matrix_index<ColumnIndex_, RowIndex_, matrix_type>::value)
		{
			return _matrix_get_non_contained<matrix_type>();
		}
		else
		{
			return matrix_.template at<ColumnIndex_, RowIndex_>();
		}
	}

	template<std::size_t ColumnIndex_, std::size_t RowIndex_, typename T_, std::size_t NumColumns_, std::size_t NumRows_, bool ColumnMajor_>
	[[nodiscard]] constexpr inline typename EmuMath::TMP::matrix_theoretical_get_result<ColumnIndex_, RowIndex_, const EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>&>::type
	_matrix_get_theoretical(const EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>& matrix_)
	{
		using matrix_type = EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>;
		if constexpr (EmuMath::TMP::is_theoretical_matrix_index<ColumnIndex_, RowIndex_, matrix_type>::value)
		{
			return _matrix_get_non_contained<matrix_type>();
		}
		else
		{
			return matrix_.template at<ColumnIndex_, RowIndex_>();
		}
	}
	
	// COLUMN GETS
	template<std::size_t ColumnIndex_, std::size_t OutSize_, typename OutT_, std::size_t Offset_, std::size_t NumColumns_, std::size_t NumRows_, typename T_, bool ColumnMajor_>
	[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> _matrix_get_column(EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>& matrix_)
	{
		return matrix_.template Column<ColumnIndex_, OutSize_, OutT_, Offset_>();
	}

	template<std::size_t ColumnIndex_, std::size_t OutSize_, typename OutT_, std::size_t Offset_, std::size_t NumColumns_, std::size_t NumRows_, typename T_, bool ColumnMajor_>
	[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> _matrix_get_column(const EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>& matrix_)
	{
		return matrix_.template Column<ColumnIndex_, OutSize_, OutT_, Offset_>();
	}

	// ROW GETS
	template<std::size_t RowIndex_, std::size_t OutSize_, typename OutT_, std::size_t Offset_, std::size_t NumColumns_, std::size_t NumRows_, typename T_, bool ColumnMajor_>
	[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> _matrix_get_row(EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>& matrix_)
	{
		return matrix_.template Row<RowIndex_, OutSize_, OutT_, Offset_>();
	}

	template<std::size_t RowIndex_, std::size_t OutSize_, typename OutT_, std::size_t Offset_, std::size_t NumColumns_, std::size_t NumRows_, typename T_, bool ColumnMajor_>
	[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> _matrix_get_row(const EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>& matrix_)
	{
		return matrix_.template Row<RowIndex_, OutSize_, OutT_, Offset_>();
	}

	// MAJOR GETS
	template<std::size_t MajorIndex_, std::size_t OutSize_, typename OutT_, std::size_t Offset_, std::size_t NumColumns_, std::size_t NumRows_, typename T_, bool ColumnMajor_>
	[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> _matrix_get_major(EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>& matrix_)
	{
		return matrix_.template Major<MajorIndex_, OutSize_, OutT_, Offset_>();
	}

	template<std::size_t MajorIndex_, std::size_t OutSize_, typename OutT_, std::size_t Offset_, std::size_t NumColumns_, std::size_t NumRows_, typename T_, bool ColumnMajor_>
	[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> _matrix_get_major(const EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>& matrix_)
	{
		return matrix_.template Major<MajorIndex_, OutSize_, OutT_, Offset_>();
	}

	// NON-MAJOR GETS
	template<std::size_t NonMajorIndex_, std::size_t OutSize_, typename OutT_, std::size_t Offset_, std::size_t NumColumns_, std::size_t NumRows_, typename T_, bool ColumnMajor_>
	[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> _matrix_get_non_major(EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>& matrix_)
	{
		return matrix_.template NonMajor<NonMajorIndex_, OutSize_, OutT_, Offset_>();
	}

	template<std::size_t NonMajorIndex_, std::size_t OutSize_, typename OutT_, std::size_t Offset_, std::size_t NumColumns_, std::size_t NumRows_, typename T_, bool ColumnMajor_>
	[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> _matrix_get_non_major(const EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>& matrix_)
	{
		return matrix_.template NonMajor<NonMajorIndex_, OutSize_, OutT_, Offset_>();
	}

	// DIAGONAL GETS
	template<std::size_t OutSize_, typename OutT_, std::size_t ColumnOffset_, std::size_t RowOffset_, std::size_t NumColumns_, std::size_t NumRows_, typename T_, bool ColumnMajor_>
	[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> _matrix_get_diagonal(EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>& matrix_)
	{
		return matrix_.template Diagonal<OutSize_, OutT_, ColumnOffset_, RowOffset_>();
	}

	template<std::size_t OutSize_, typename OutT_, std::size_t ColumnOffset_, std::size_t RowOffset_, std::size_t NumColumns_, std::size_t NumRows_, typename T_, bool ColumnMajor_>
	[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, OutT_> _matrix_get_diagonal(const EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>& matrix_)
	{
		return matrix_.template Diagonal<OutSize_, OutT_, ColumnOffset_, RowOffset_>();
	}
}

#endif
