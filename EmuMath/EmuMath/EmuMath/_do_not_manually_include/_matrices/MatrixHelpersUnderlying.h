#ifndef EMU_MATH_MATRIX_HELPERS_UNDERLYING_H_INC_
#define EMU_MATH_MATRIX_HELPERS_UNDERLYING_H_INC_ 1

#include "MatrixTMP.h"

namespace EmuMath::Helpers::_underlying_matrix_funcs
{
#pragma region INDEX_CONVERSIONS
	template<std::size_t Index_, class Matrix_>
	constexpr inline std::size_t _matrix_major_order_index_to_column_index()
	{
		if constexpr (Matrix_::is_column_major)
		{
			return Index_ / Matrix_::num_columns;
		}
		else
		{
			return Index_ % Matrix_::num_columns;
		}
	}
	template<class Matrix_>
	constexpr inline std::size_t _matrix_major_order_index_to_column_index(const std::size_t index_)
	{
		if constexpr (Matrix_::is_column_major)
		{
			return index_ / Matrix_::num_columns;
		}
		else
		{
			return index_ % Matrix_::num_columns;
		}
	}

	template<std::size_t Index_, class Matrix_>
	constexpr inline std::size_t _matrix_major_order_index_to_row_index()
	{
		if constexpr (Matrix_::is_row_major)
		{
			return Index_ / Matrix_::num_rows;
		}
		else
		{
			return Index_ % Matrix_::num_rows;
		}
	}
	template<class Matrix_>
	constexpr inline std::size_t _matrix_major_order_index_to_row_index(const std::size_t index_)
	{
		if constexpr (Matrix_::is_row_major)
		{
			return index_ / Matrix_::num_rows;
		}
		else
		{
			return index_ % Matrix_::num_rows;
		}
	}
#pragma endregion

#pragma region GETS
	template<std::size_t ColumnIndex_, std::size_t RowIndex_, class Matrix_>
	constexpr inline typename Matrix_::raw_value_type& _get_matrix_data(Matrix_& matrix_)
	{
		return matrix_.template at<ColumnIndex_, RowIndex_>();
	}
	template<std::size_t ColumnIndex_, std::size_t RowIndex_, class Matrix_>
	constexpr inline const typename Matrix_::raw_value_type& _get_matrix_data(const Matrix_& matrix_)
	{
		return matrix_.template at<ColumnIndex_, RowIndex_>();
	}

	template<std::size_t Index_, class Matrix_>
	constexpr inline typename Matrix_::raw_value_type& _get_matrix_data(Matrix_& matrix_)
	{
		return _get_matrix_data
		<
			_matrix_major_order_index_to_column_index<Index_, Matrix_>(),
			_matrix_major_order_index_to_row_index<Index_, Matrix_>(),
			Matrix_
		>(matrix_);
	}
	template<std::size_t Index_, class Matrix_>
	constexpr inline const typename Matrix_::raw_value_type& _get_matrix_data(const Matrix_& matrix_)
	{
		return _get_matrix_data
		<
			_matrix_major_order_index_to_column_index<Index_, Matrix_>(),
			_matrix_major_order_index_to_row_index<Index_, Matrix_>(),
			Matrix_
		>(matrix_);
	}

	template<class Matrix_>
	constexpr inline typename Matrix_::raw_value_type& _get_matrix_data(Matrix_& matrix_, const std::size_t column_index_, const std::size_t row_index_)
	{
		return matrix_.at(column_index_, row_index_);
	}
	template<class Matrix_>
	constexpr inline const typename Matrix_::raw_value_type& _get_matrix_data(const Matrix_& matrix_, const std::size_t column_index_, const std::size_t row_index_)
	{
		return matrix_.at(column_index_, row_index_);
	}
	template<class Matrix_>
	constexpr inline typename Matrix_::raw_value_type& _get_matrix_data(Matrix_& matrix_, const std::size_t major_order_index_)
	{
		return _get_matrix_data
		(
			matrix_,
			_matrix_major_order_index_to_column_index<Matrix_>(major_order_index_),
			_matrix_major_order_index_to_row_index<Matrix_>(major_order_index_)
		);
	}
	template<class Matrix_>
	constexpr inline const typename Matrix_::raw_value_type& _get_matrix_data(const Matrix_& matrix_, const std::size_t major_order_index_)
	{
		return _get_matrix_data
		(
			matrix_,
			_matrix_major_order_index_to_column_index<Matrix_>(major_order_index_),
			_matrix_major_order_index_to_row_index<Matrix_>(major_order_index_)
		);
	}

	template<std::size_t MajorIndex_, std::size_t NonMajorIndex_, class Matrix_, class Out_>
	constexpr inline void _fill_matrix_non_major(Matrix_& matrix_, Out_& out_)
	{
		if constexpr (MajorIndex_ < Matrix_::num_major_elements)
		{
			if constexpr (Matrix_::is_column_major)
			{
				out_.template Set<MajorIndex_>(_get_matrix_data<MajorIndex_, NonMajorIndex_, Matrix_>(matrix_));
			}
			else
			{
				out_.template Set<MajorIndex_>(_get_matrix_data<NonMajorIndex_, MajorIndex_, Matrix_>(matrix_));
			}
			_fill_matrix_non_major<MajorIndex_ + 1, NonMajorIndex_, Matrix_, Out_>(matrix_, out_);
		}
	}
	template<std::size_t ColumnIndex_, class Matrix_>
	constexpr inline auto _get_matrix_column(Matrix_& matrix_)
	{
		using out_column = std::conditional_t<std::is_const_v<Matrix_>, typename Matrix_::const_random_access_column, typename Matrix_::random_access_column>;
		if constexpr (Matrix_::is_column_major)
		{
			return out_column(matrix_.template GetMajor<ColumnIndex_>());
		}
		else
		{
			out_column out_ = out_column();
			_fill_matrix_non_major<0, ColumnIndex_, Matrix_, out_column>(matrix_, out_);
			return out_column(out_);
		}
	}

	template<std::size_t RowIndex_, class Matrix_>
	constexpr inline auto _get_matrix_row(Matrix_& matrix_)
	{
		using out_row = std::conditional_t<std::is_const_v<Matrix_>, typename Matrix_::const_random_access_row, typename Matrix_::random_access_row>;
		if constexpr (Matrix_::is_row_major)
		{
			return out_row(matrix_.template GetMajor<RowIndex_>());
		}
		else
		{
			out_row out_ = out_row();
			_fill_matrix_non_major<0, RowIndex_, Matrix_, out_row>(matrix_, out_);
			return out_row(out_);
		}
	}
#pragma endregion

#pragma region REINTERPRETATIONS
	template<class Vector_, class OutMatrix_>
	constexpr inline OutMatrix_ _vector_to_matrix(const Vector_& vector_)
	{
		return OutMatrix_(static_cast<EmuMath::Vector<Vector_::size, typename OutMatrix_::contained_type>>(vector_));
	}
#pragma endregion
}

#endif
