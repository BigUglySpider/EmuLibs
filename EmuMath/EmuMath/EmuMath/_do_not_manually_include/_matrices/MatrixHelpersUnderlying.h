#ifndef EMU_MATH_MATRIX_HELPERS_UNDERLYING_H_INC_
#define EMU_MATH_MATRIX_HELPERS_UNDERLYING_H_INC_ 1

#include "MatrixTMP.h"

namespace EmuMath::Helpers::_underlying_matrix_funcs
{
#pragma region VALIDITY_CHECKS
	template<std::size_t ColumnIndex_, std::size_t RowIndex_, class Matrix_>
	constexpr inline bool _valid_matrix_indices()
	{
		return ColumnIndex_ < Matrix_::num_columns && RowIndex_ < Matrix_::num_rows;
	}
	template<std::size_t MajorOrderIndex_, class Matrix_>
	constexpr inline bool _valid_matrix_major_order_index()
	{
		return MajorOrderIndex_ < Matrix_::size;
	}
#pragma endregion

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

	template<std::size_t ColumnIndex_, std::size_t RowIndex_, class Matrix_>
	constexpr inline typename EmuMath::TMP::emu_matrix_theoretical_data<ColumnIndex_, RowIndex_, Matrix_>::type _get_matrix_theoretical_data(const Matrix_& matrix_)
	{
		if constexpr (_valid_matrix_indices<ColumnIndex_, RowIndex_, Matrix_>())
		{
			return _get_matrix_data<ColumnIndex_, RowIndex_, Matrix_>(matrix_);
		}
		else
		{
			return typename Matrix_::value_type();
		}
	}
	template<std::size_t MajorOrderIndex_, class Matrix_>
	constexpr inline typename EmuMath::TMP::emu_matrix_theoretical_major_order_index_data<MajorOrderIndex_, Matrix_>::type _get_matrix_theoretical_data(const Matrix_& matrix_)
	{
		if constexpr (_valid_matrix_major_order_index<MajorOrderIndex_, Matrix_>())
		{
			return _get_matrix_data<MajorOrderIndex_, Matrix_>(matrix_);
		}
		else
		{
			return typename Matrix_::value_type();
		}
	}
#pragma endregion

#pragma region SETS
	template<std::size_t ColumnIndex_, std::size_t RowIndex_, class Matrix_, typename Arg_>
	constexpr inline Matrix_& _matrix_set(Matrix_& matrix_, Arg_& arg_)
	{
		if constexpr (Matrix_::is_column_major)
		{
			auto& column_ = matrix_.template GetMajor<ColumnIndex_>();
			column_.template Set<RowIndex_>(arg_);
		}
		else
		{
			auto& row_ = matrix_.template GetMajor<RowIndex_>();
			row_.template Set<ColumnIndex_>(arg_);
		}
		return matrix_;
	}
	template<std::size_t ColumnIndex_, std::size_t RowIndex_, class Matrix_, typename Arg_>
	constexpr inline Matrix_& _matrix_set(Matrix_& matrix_, const Arg_& arg_)
	{
		if constexpr (Matrix_::is_column_major)
		{
			auto& column_ = matrix_.template GetMajor<ColumnIndex_>();
			column_.template Set<RowIndex_>(arg_);
		}
		else
		{
			auto& row_ = matrix_.template GetMajor<RowIndex_>();
			row_.template Set<ColumnIndex_>(arg_);
		}
		return matrix_;
	}
#pragma endregion

#pragma region REINTERPRETATIONS
	template<class Vector_, class OutMatrix_>
	constexpr inline OutMatrix_ _vector_to_matrix(const Vector_& vector_)
	{
		return OutMatrix_(static_cast<EmuMath::Vector<Vector_::size, typename OutMatrix_::contained_type>>(vector_));
	}
#pragma endregion

#pragma region ARITHMETIC
	template<std::size_t ColumnIndex_, std::size_t RowIndex_, class OutMatrix_, class LhsMatrix_, class Rhs_, class Func_>
	constexpr inline void _matrix_lhs_rhs_operation_rhs_scalar(const LhsMatrix_& lhs_, const Rhs_& rhs_, Func_& func_, OutMatrix_& out_)
	{
		if constexpr (ColumnIndex_ < OutMatrix_::num_columns)
		{
			if constexpr (RowIndex_ < OutMatrix_::num_rows)
			{
				using out_value = typename OutMatrix_::value_type;
				_get_matrix_data<ColumnIndex_, RowIndex_>(out_) = static_cast<out_value>(func_(_get_matrix_theoretical_data<ColumnIndex_, RowIndex_>(lhs_), rhs_));
				_matrix_lhs_rhs_operation_rhs_scalar<ColumnIndex_, RowIndex_ + 1, OutMatrix_, LhsMatrix_, Rhs_, Func_>(lhs_, rhs_, func_, out_);
			}
			else
			{
				_matrix_lhs_rhs_operation_rhs_scalar<ColumnIndex_ + 1, 0, OutMatrix_, LhsMatrix_, Rhs_, Func_>(lhs_, rhs_, func_, out_);
			}
		}
	}
	template<std::size_t ColumnIndex_, std::size_t RowIndex_, class OutMatrix_, class LhsMatrix_, class Rhs_, class Func_>
	constexpr inline void _matrix_lhs_rhs_operation_rhs_matrix(const LhsMatrix_& lhs_, const Rhs_& rhs_, Func_& func_, OutMatrix_& out_)
	{
		if constexpr (ColumnIndex_ < OutMatrix_::num_columns)
		{
			if constexpr (RowIndex_ < OutMatrix_::num_rows)
			{
				using out_value = typename OutMatrix_::value_type;
				_get_matrix_data<ColumnIndex_, RowIndex_>(out_) = static_cast<out_value>
				(
					func_
					(
						_get_matrix_theoretical_data<ColumnIndex_, RowIndex_>(lhs_),
						_get_matrix_theoretical_data<ColumnIndex_, RowIndex_>(rhs_)
					)
				);
				_matrix_lhs_rhs_operation_rhs_matrix<ColumnIndex_, RowIndex_ + 1, OutMatrix_, LhsMatrix_, Rhs_, Func_>(lhs_, rhs_, func_, out_);
			}
			else
			{
				_matrix_lhs_rhs_operation_rhs_matrix<ColumnIndex_ + 1, 0, OutMatrix_, LhsMatrix_, Rhs_, Func_>(lhs_, rhs_, func_, out_);
			}
		}
	}
	template<class OutMatrix_, class LhsMatrix_, class Rhs_, class Func_>
	constexpr inline OutMatrix_ _matrix_lhs_rhs_operation(const LhsMatrix_& lhs_, const Rhs_& rhs_, Func_& func_)
	{
		OutMatrix_ out_ = OutMatrix_();
		if constexpr (EmuMath::TMP::is_emu_matrix_v<Rhs_>)
		{
			_matrix_lhs_rhs_operation_rhs_matrix<0, 0, OutMatrix_, LhsMatrix_, Rhs_, Func_>(lhs_, rhs_, func_, out_);
		}
		else
		{
			_matrix_lhs_rhs_operation_rhs_scalar<0, 0, OutMatrix_, LhsMatrix_, Rhs_, Func_>(lhs_, rhs_, func_, out_);
		}
		return out_;
	}
	template<class OutMatrix_, class LhsMatrix_, class Rhs_, class Func_>
	constexpr inline OutMatrix_ _matrix_lhs_rhs_operation(const LhsMatrix_& lhs_, const Rhs_& rhs_)
	{
		Func_ func_ = Func_();
		return _matrix_lhs_rhs_operation<OutMatrix_, LhsMatrix_, Rhs_, Func_&>(lhs_, rhs_, func_);
	}

	template<class Matrix_, std::size_t...Indices_>
	constexpr inline std::array<EmuMath::Vector<Matrix_::num_rows, typename Matrix_::value_type>, sizeof...(Indices_)> _get_matrix_columns
	(
		const Matrix_& matrix_,
		std::index_sequence<Indices_...>
	)
	{
		return std::array<EmuMath::Vector<Matrix_::num_rows, typename Matrix_::value_type>, sizeof...(Indices_)>
		({
			_get_matrix_column<Indices_>(matrix_)...
		});
	}
	template<class Matrix_, std::size_t...Indices_>
	constexpr inline std::array<EmuMath::Vector<Matrix_::num_columns, typename Matrix_::value_type>, sizeof...(Indices_)> _get_matrix_rows
	(
		const Matrix_& matrix_,
		std::index_sequence<Indices_...>
	)
	{
		return std::array<EmuMath::Vector<Matrix_::num_columns, typename Matrix_::value_type>, sizeof...(Indices_)>
		({
			_get_matrix_row<Indices_>(matrix_)...
		});
	}
	template<std::size_t ColumnIndex_, std::size_t RowIndex_, class OutMatrix_, class LhsRows_, class RhsColumns_>
	constexpr inline void _matrix_std_multiply(OutMatrix_& out_, const LhsRows_& lhs_rows_, const RhsColumns_& rhs_columns_)
	{
		if constexpr (ColumnIndex_ < OutMatrix_::num_columns)
		{
			if constexpr (RowIndex_ < OutMatrix_::num_rows)
			{
				_get_matrix_data<ColumnIndex_, RowIndex_>(out_) = EmuMath::Helpers::VectorDotProduct<typename OutMatrix_::value_type>
				(
					std::get<RowIndex_>(lhs_rows_),
					std::get<ColumnIndex_>(rhs_columns_)
				);
				_matrix_std_multiply<ColumnIndex_, RowIndex_ + 1, OutMatrix_, LhsRows_, RhsColumns_>(out_, lhs_rows_, rhs_columns_);
			}
			else
			{
				_matrix_std_multiply<ColumnIndex_ + 1, 0, OutMatrix_, LhsRows_, RhsColumns_>(out_, lhs_rows_, rhs_columns_);
			}
		}
	}
	template<class OutMatrix_, class LhsMatrix_, class Rhs_>
	constexpr inline OutMatrix_ _matrix_std_multiply(const LhsMatrix_& lhs_, const Rhs_& rhs_)
	{
		if constexpr (EmuMath::TMP::is_emu_matrix_v<Rhs_>)
		{
			auto lhs_rows_ = _get_matrix_rows<LhsMatrix_>(lhs_, std::make_index_sequence<LhsMatrix_::num_rows>());
			auto rhs_columns_ = _get_matrix_columns<Rhs_>(rhs_, std::make_index_sequence<Rhs_::num_columns>());
			OutMatrix_ out_ = OutMatrix_();
			_matrix_std_multiply<0, 0, OutMatrix_>(out_, lhs_rows_, rhs_columns_);
			return out_;
		}
		else
		{
			// Defer to basic lhs_rhs functor executor since A * scalar_x is effectively A[00]-A[XX] * scalar_x.
			return _matrix_lhs_rhs_operation<OutMatrix_, LhsMatrix_, Rhs_, EmuCore::do_multiply<typename LhsMatrix_::value_type, Rhs_>>(lhs_, rhs_);
		}
	}
#pragma endregion

#pragma region MATRIX_OPERATIONS
	template<std::size_t Index_, class Matrix_>
	constexpr inline void _make_identity_matrix(Matrix_& out_)
	{
		if constexpr (Index_ < Matrix_::num_columns)
		{
			_get_matrix_data<Index_, Index_>(out_) = typename Matrix_::value_type(1);
			_make_identity_matrix<Index_ + 1, Matrix_>(out_);
		}
	}
	template<class Matrix_>
	[[nodiscard]] constexpr inline Matrix_ _make_identity_matrix()
	{
		Matrix_ out_ = Matrix_();
		_make_identity_matrix<0, Matrix_>(out_);
		return out_;
	}

	template<std::size_t ColumnIndex_, std::size_t RowIndex_, class OutMatrix_, class Matrix_>
	constexpr inline void _transpose_matrix(const Matrix_& matrix_, OutMatrix_& out_)
	{
		if constexpr (ColumnIndex_ < OutMatrix_::num_columns)
		{
			if constexpr (RowIndex_ < OutMatrix_::num_rows)
			{
				_get_matrix_data<ColumnIndex_, RowIndex_>(out_) = _get_matrix_data<RowIndex_, ColumnIndex_>(matrix_);
				_transpose_matrix<ColumnIndex_, RowIndex_ + 1, OutMatrix_, Matrix_>(matrix_, out_);
			}
			else
			{
				_transpose_matrix<ColumnIndex_ + 1, 0, OutMatrix_, Matrix_>(matrix_, out_);
			}
		}
	}
	template<class OutMatrix_, class Matrix_>
	[[nodiscard]] constexpr inline OutMatrix_ _transpose_matrix(const Matrix_& matrix_)
	{
		OutMatrix_ out_ = OutMatrix_();
		_transpose_matrix<0, 0, OutMatrix_, Matrix_>(matrix_, out_);
		return out_;
	}

	template<std::size_t Index_, typename Out_, class Matrix_, class Adder_>
	constexpr inline void _calculate_matrix_trace(const Matrix_& matrix_, Out_& out_, Adder_& adder_)
	{
		if constexpr (Index_ < Matrix_::num_columns)
		{
			out_ = adder_(out_, _get_matrix_data<Index_, Index_>(matrix_));
			_calculate_matrix_trace<Index_ + 1, Out_, Matrix_, Adder_>(matrix_, out_, adder_);
		}
	}
	template<typename Out_, class Matrix_>
	[[nodiscard]] constexpr inline Out_ _calculate_matrix_trace(const Matrix_& matrix_)
	{
		using Adder_ = EmuCore::do_add<Out_, Out_>;
		Out_ out_ = Out_();
		Adder_ adder_ = Adder_();
		_calculate_matrix_trace<0, Out_, Matrix_, Adder_>(matrix_, out_, adder_);
		return out_;
	}

	template<std::size_t InColumn_, std::size_t InRow_, std::size_t OutColumn_, std::size_t OutRow_, std::size_t ExcludeColumn_, std::size_t ExcludeRow_, class Out_, class In_>
	constexpr inline void _get_submatrix_excluding_element_region(In_& in_, Out_& out_)
	{
		if constexpr (OutColumn_ < Out_::num_columns)
		{
			if constexpr (OutRow_ < Out_::num_rows)
			{
				if constexpr (InColumn_ != ExcludeColumn_)
				{
					if constexpr (InRow_ != ExcludeRow_)
					{
						_matrix_set<OutColumn_, OutRow_>
						(
							out_,
							(_get_matrix_data<InColumn_, InRow_>(in_))
						);
						_get_submatrix_excluding_element_region<InColumn_, InRow_ + 1, OutColumn_, OutRow_ + 1, ExcludeColumn_, ExcludeRow_, Out_, In_>(in_, out_);
					}
					else
					{
						_get_submatrix_excluding_element_region<InColumn_, InRow_ + 1, OutColumn_, OutRow_, ExcludeColumn_, ExcludeRow_, Out_, In_>(in_, out_);
					}
				}
				else
				{
					_get_submatrix_excluding_element_region<InColumn_ + 1, InRow_, OutColumn_, OutRow_, ExcludeColumn_, ExcludeRow_, Out_, In_>(in_, out_);
				}
			}
			else
			{
				_get_submatrix_excluding_element_region<InColumn_ + 1, 0, OutColumn_ + 1, 0, ExcludeColumn_, ExcludeRow_, Out_, In_>(in_, out_);
			}
		}
	}
	template<std::size_t ExcludeColumn_, std::size_t ExcludeRow_, class OutMatrix_, class InMatrix_>
	[[nodiscard]] constexpr inline OutMatrix_ _get_submatrix_excluding_element_region(InMatrix_& in_)
	{
		OutMatrix_ out_ = OutMatrix_();
		_get_submatrix_excluding_element_region<0, 0, 0, 0, ExcludeColumn_, ExcludeRow_, OutMatrix_, InMatrix_>(in_, out_);
		return out_;
	}

	template<typename Out_, class Matrix_>
	constexpr inline void _calculate_matrix_determinant_laplace_1x1(const Matrix_& matrix_, Out_& out_)
	{
		out_ = static_cast<Out_>(_get_matrix_data<0, 0>(matrix_));
	}
	template<typename Out_, class Matrix_, class Subtractor_, class Multiplier_>
	constexpr inline void _calculate_matrix_determinant_laplace_2x2(const Matrix_& matrix_, Out_& out_, Subtractor_& sub_, Multiplier_& mult_)
	{
		// Returns (a*d)-(b*c) where a 2x2 matrix is:
		// a b
		// c d
		out_ = static_cast<Out_>
		(
			sub_
			(
				mult_(static_cast<Out_>(_get_matrix_data<0, 0>(matrix_)), static_cast<Out_>(_get_matrix_data<1, 1>(matrix_))),
				mult_(static_cast<Out_>(_get_matrix_data<1, 0>(matrix_)), static_cast<Out_>(_get_matrix_data<0, 1>(matrix_)))
			)
		);
	}
	template<std::size_t ColumnIndex_, typename Out_, class Matrix_, class Adder_, class Subtractor_, class Multiplier_>
	constexpr inline void _calculate_matrix_determinant_laplace(const Matrix_& matrix_, Out_& out_, Adder_& add_, Subtractor_& sub_, Multiplier_& mult_)
	{
		if constexpr (Matrix_::num_columns == 1)
		{
			_calculate_matrix_determinant_laplace_1x1<Out_, Matrix_>(matrix_, out_);
		}
		else if constexpr (Matrix_::num_columns == 2)
		{
			_calculate_matrix_determinant_laplace_2x2<Out_, Matrix_, Subtractor_, Multiplier_>(matrix_, out_, sub_, mult_);
		}
		else if constexpr (ColumnIndex_ < Matrix_::num_columns)
		{
			using mat_val = typename Matrix_::value_type;
			using sub_mat_type = EmuMath::TMP::emu_matrix_submatrix_excluding_element_region_t<typename Matrix_::value_type, Matrix_::is_column_major, Matrix_>;
			mat_val sub_det_ = mat_val();
			sub_mat_type sub_mat_ = _get_submatrix_excluding_element_region<ColumnIndex_, 0, sub_mat_type, const Matrix_>(matrix_);
			_calculate_matrix_determinant_laplace<0, mat_val, sub_mat_type, Adder_, Subtractor_, Multiplier_>(sub_mat_, sub_det_, add_, sub_, mult_);
			sub_det_ = mult_(sub_det_, _get_matrix_data<ColumnIndex_, 0>(matrix_));

			if constexpr ((ColumnIndex_ % 2) == 0)
			{
				// EVEN: Add to existing out_.
				out_ = static_cast<Out_>(add_(out_, sub_det_));
			}
			else
			{
				// ODD: Subtract from existing out_.
				out_ = static_cast<Out_>(sub_(out_, sub_det_));
			}
			_calculate_matrix_determinant_laplace<ColumnIndex_ + 1, Out_, Matrix_, Adder_, Subtractor_, Multiplier_>(matrix_, out_, add_, sub_, mult_);
		}
	}
	template<typename Out_, class Matrix_>
	[[nodiscard]] constexpr inline Out_ _calculate_matrix_determinant_laplace(const Matrix_& matrix_)
	{
		using mat_value = typename Matrix_::value_type;
		using Adder_ = EmuCore::do_add<Out_, mat_value>;
		using Subtractor_ = EmuCore::do_subtract<Out_, mat_value>;
		using Multiplier_ = EmuCore::do_multiply<mat_value, mat_value>;

		Multiplier_ mult_ = Multiplier_();
		Subtractor_ sub_ = Subtractor_();
		Adder_ add_ = Adder_();
		Out_ out_ = Out_();
		_calculate_matrix_determinant_laplace<0, Out_, Matrix_, Adder_, Subtractor_, Multiplier_>(matrix_, out_, add_, sub_, mult_);
		return out_;
	}
#pragma endregion
}

#endif
