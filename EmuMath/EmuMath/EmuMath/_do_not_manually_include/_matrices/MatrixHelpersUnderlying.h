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

	template<std::size_t Index_, class Matrix_, typename Arg_>
	constexpr inline Matrix_& _matrix_set_trace_region(Matrix_& matrix_,  Arg_& arg_)
	{
		if constexpr ((Index_ < Matrix_::num_columns) && (Index_ < Matrix_::num_rows))
		{
			matrix_.template GetMajor<Index_>().template Set<Index_>(arg_);
			_matrix_set_trace_region<Index_ + 1, Matrix_, Arg_>(matrix_, arg_);
		}
		return matrix_;
	}
	template<std::size_t Index_, class Matrix_, typename Arg_>
	constexpr inline Matrix_& _matrix_set_trace_region(Matrix_& matrix_, const Arg_& arg_)
	{
		if constexpr ((Index_ < Matrix_::num_columns) && (Index_ < Matrix_::num_rows))
		{
			matrix_.template GetMajor<Index_>().template Set<Index_>(arg_);
			_matrix_set_trace_region<Index_ + 1, Matrix_, Arg_>(matrix_, arg_);
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
	template<class Matrix_>
	[[nodiscard]] constexpr inline Matrix_ _make_identity_matrix()
	{
		Matrix_ out_ = Matrix_();
		_matrix_set_trace_region<0, Matrix_, typename Matrix_::contained_type>(out_, typename Matrix_::contained_type(1));
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

	template<std::size_t ColumnIndex_, std::size_t RowIndex_, class OutMatrix_, class Matrix_>
	constexpr inline void _calculate_matrix_of_minors_laplace(const Matrix_& matrix_, OutMatrix_& out_)
	{
		if constexpr (ColumnIndex_ < OutMatrix_::num_columns)
		{
			if constexpr (RowIndex_ < OutMatrix_::num_rows)
			{
				using out_value = typename OutMatrix_::value_type;
				using sub_mat = typename EmuMath::TMP::emu_matrix_submatrix_excluding_element_region<typename Matrix_::value_type, Matrix_::is_column_major, Matrix_>::type;
				const out_value val_ = _calculate_matrix_determinant_laplace
				<
					out_value,
					sub_mat
				>(_get_submatrix_excluding_element_region<ColumnIndex_, RowIndex_, sub_mat, const Matrix_>(matrix_));
				_get_matrix_data<ColumnIndex_, RowIndex_>(out_) = val_;
				_calculate_matrix_of_minors_laplace<ColumnIndex_, RowIndex_ + 1, OutMatrix_, Matrix_>(matrix_, out_);
			}
			else
			{
				_calculate_matrix_of_minors_laplace<ColumnIndex_ + 1, 0, OutMatrix_, Matrix_>(matrix_, out_);
			}
		}
	}
	template<typename OutMatrix_, class Matrix_>
	[[nodiscard]] constexpr inline OutMatrix_ _calculate_matrix_of_minors_laplace(const Matrix_& matrix_)
	{
		OutMatrix_ out_ = OutMatrix_();
		_calculate_matrix_of_minors_laplace<0, 0, OutMatrix_, Matrix_>(matrix_, out_);
		return out_;
	}

	template<std::size_t ColumnIndex_, std::size_t RowIndex_, class InMatrix_, class OutMatrix_, class Negator_>
	[[nodiscard]] constexpr inline void _transform_matrix_minors_to_cofactors(const InMatrix_& in_, OutMatrix_& out_, Negator_& negator_)
	{
		if constexpr (ColumnIndex_ < OutMatrix_::num_columns)
		{
			if constexpr (RowIndex_ < OutMatrix_::num_rows)
			{
				using out_value = typename OutMatrix_::value_type;
				
				// If both odd or even: copy of value
				// If one odd and the other even: negated copy of value
				if constexpr ((ColumnIndex_ & 1) == (RowIndex_ & 1))
				{
					_get_matrix_data<ColumnIndex_, RowIndex_>(out_) = static_cast<out_value>(_get_matrix_data<ColumnIndex_, RowIndex_>(in_));
				}
				else
				{
					_get_matrix_data<ColumnIndex_, RowIndex_>(out_) = negator_(static_cast<out_value>(_get_matrix_data<ColumnIndex_, RowIndex_>(in_)));
				}
				_transform_matrix_minors_to_cofactors<ColumnIndex_, RowIndex_ + 1, InMatrix_, OutMatrix_, Negator_>(in_, out_, negator_);
			}
			else
			{
				_transform_matrix_minors_to_cofactors<ColumnIndex_ + 1, 0, InMatrix_, OutMatrix_, Negator_>(in_, out_, negator_);
			}
		}
	}
	template<class OutMatrix_, class Matrix_>
	[[nodiscard]] constexpr inline OutMatrix_ _calculate_matrix_of_cofactors_laplace(const Matrix_& matrix_)
	{
		OutMatrix_ out_ = _calculate_matrix_of_minors_laplace<OutMatrix_, Matrix_>(matrix_);
		using Negator_ = EmuCore::do_negate<typename OutMatrix_::value_type>;
		Negator_ negator_ = Negator_();
		_transform_matrix_minors_to_cofactors<0, 0, OutMatrix_, OutMatrix_, Negator_>(out_, out_, negator_);
		return out_;
	}

	template<class OutMatrix_, class Matrix_>
	[[nodiscard]] constexpr inline OutMatrix_ _calculate_matrix_adjugate_laplace(const Matrix_& matrix_)
	{
		return _transpose_matrix<OutMatrix_, OutMatrix_>
		(
			_calculate_matrix_of_cofactors_laplace<OutMatrix_, Matrix_>(matrix_)
		);
	}

	template<std::size_t ColumnIndex_, class Out_, class Matrix_, class Minors_, class Adder_, class Subtractor_, class Multiplier_>
	constexpr inline void _calculate_determinant_from_matrix_of_minors
	(
		const Matrix_& matrix_,
		const Minors_& minors_,
		Out_& out_,
		Adder_& add_,
		Subtractor_& sub_,
		Multiplier_& mult_
	)
	{
		if constexpr (ColumnIndex_ < Minors_::num_columns)
		{
			using mat_value = typename Matrix_::value_type;
			mat_value val_ = static_cast<mat_value>
			(
				mult_
				(
					_get_matrix_data<ColumnIndex_, 0>(matrix_),
					_get_matrix_data<ColumnIndex_, 0>(minors_)
				)
			);

			if constexpr (ColumnIndex_ & 1)
			{
				// ODD: Subtract from existing out_.
				out_ = static_cast<Out_>(sub_(out_, val_));
			}
			else
			{
				// EVEN: Add to existing out_.
				out_ = static_cast<Out_>(add_(out_, val_));
			}
			_calculate_determinant_from_matrix_of_minors<ColumnIndex_ + 1, Out_, Matrix_, Minors_, Adder_, Subtractor_, Multiplier_>(matrix_, minors_, out_, add_, sub_, mult_);
		}
	}
	template<class Out_, class Matrix_, class Minors_>
	[[nodiscard]] constexpr inline Out_ _calculate_determinant_from_matrix_of_minors(const Matrix_& matrix_, const Minors_& minors_)
	{
		Out_ out_ = Out_();
		using mat_value = typename Matrix_::value_type;
		using Adder_ = EmuCore::do_add<Out_, mat_value>;
		using Subtractor_ = EmuCore::do_subtract<Out_, mat_value>;
		using Multiplier_ = EmuCore::do_multiply<mat_value, mat_value>;

		Adder_ add_ = Adder_();
		Subtractor_ sub_ = Subtractor_();
		Multiplier_ mult_ = Multiplier_();
		_calculate_determinant_from_matrix_of_minors<0, Out_, Matrix_, Minors_, Adder_, Subtractor_, Multiplier_>(matrix_, minors_, out_, add_, sub_, mult_);
		return out_;
	}

	template<class OutMatrix_, class Matrix_, class OutDeterminant_>
	[[nodiscard]] constexpr inline OutMatrix_ _calculate_matrix_inverse_laplace(const Matrix_& matrix_, OutDeterminant_& outDeterminant_)
	{
		using Negator_ = EmuCore::do_negate<typename OutMatrix_::value_type>;
		using mat_copy = EmuMath::Matrix<Matrix_::num_columns, Matrix_::num_rows, typename Matrix_::value_type, Matrix_::is_column_major>;
		Negator_ negator_ = Negator_();

		mat_copy cofactors_ = _calculate_matrix_of_minors_laplace<mat_copy, Matrix_>(matrix_);
		// Calculate overall determinant with existing minor values to avoid recalculating
		outDeterminant_ = _calculate_determinant_from_matrix_of_minors<OutDeterminant_, Matrix_, mat_copy>(matrix_, cofactors_);

		// Transform minors into final form as adjugate
		_transform_matrix_minors_to_cofactors<0, 0, mat_copy, mat_copy, Negator_>(cofactors_, cofactors_, negator_);
		OutMatrix_ adjugate_ = _transpose_matrix<OutMatrix_, mat_copy>(cofactors_);

		// Multiply the adjugate by the reciprocal to the original matrix's determinant
		using reciprocal_type = EmuCore::TMPHelpers::first_floating_point_t<OutDeterminant_, float>;
		using Multiplier_ = EmuCore::do_multiply<typename OutMatrix_::value_type, reciprocal_type>;
		reciprocal_type det_reciprocal_ = reciprocal_type(1) / static_cast<reciprocal_type>(outDeterminant_);
		return _matrix_lhs_rhs_operation<OutMatrix_, OutMatrix_, reciprocal_type, Multiplier_>(adjugate_, det_reciprocal_);
	}
#pragma endregion

#pragma region TRANSFORMATIONS


	template<class Matrix_, class FirstArg_, class...AdditionalArgs_>
	struct _translation_matrix_builder
	{
		constexpr _translation_matrix_builder()
		{
		}
		template<std::size_t RowIndex_ = 0>
		constexpr inline void operator()(Matrix_& out_, const FirstArg_& first_arg_, const AdditionalArgs_&...additional_args_) const
		{
			if constexpr (RowIndex_ < Matrix_::num_rows)
			{
				_translation_matrix_builder<Matrix_, FirstArg_>().operator() < RowIndex_ > (out_, first_arg_);
				_translation_matrix_builder<Matrix_, AdditionalArgs_...>().operator() < RowIndex_ + 1 > (out_, additional_args_...);
			}
		}
	};
	template<class Matrix_, class Arg_>
	struct _translation_matrix_builder<Matrix_, Arg_>
	{
		constexpr _translation_matrix_builder()
		{
		}
		// This is called independetnly from a recursive loop, and does not need to recursively call itself for further indices.
		template<std::size_t RowIndex_ = 0>
		constexpr inline void operator()(Matrix_& out_, const Arg_& arg_) const
		{
			if constexpr (RowIndex_ < Matrix_::num_rows)
			{
				using out_value = typename Matrix_::value_type;
				if constexpr (std::is_convertible_v<Arg_, out_value>)
				{
					_get_matrix_data<Matrix_::num_columns - 1, RowIndex_, Matrix_>(out_) = static_cast<out_value>(arg_);
				}
				else
				{
					static_assert(false, "Attempted to create an EmuMath translation matrix using a coordinate argument which cannot be converted to the output matrix's value type.");
				}
			}
		}
	};

	template<class OutMatrix_, class...Args_>
	constexpr inline OutMatrix_ _make_translation_matrix(const Args_&...args_)
	{
		OutMatrix_ out_ = OutMatrix_();
		_matrix_set_trace_region<0, OutMatrix_, typename OutMatrix_::contained_type>(out_, typename OutMatrix_::contained_type(1));
		_translation_matrix_builder<OutMatrix_, Args_...>()(out_, args_...);
		return out_;
	}

	template<class OutMatrix_, class Theta_, class CosCalculator_, class SinCalculator_>
	constexpr inline OutMatrix_ _make_rotation_matrix_x(const Theta_& theta_)
	{
		using out_value = typename OutMatrix_::value_type;

		OutMatrix_ out_ = OutMatrix_();
		out_value cos_ = static_cast<out_value>(CosCalculator_()(theta_));
		out_value sin_ = static_cast<out_value>(SinCalculator_()(theta_));
		_get_matrix_data<1, 1>(out_) = cos_;
		_get_matrix_data<2, 1>(out_) = sin_;
		_get_matrix_data<1, 2>(out_) = EmuCore::do_negate<out_value>()(sin_);
		_get_matrix_data<2, 2>(out_) = cos_;

		// Set unfilled trace elements to 1 before returning.
		const out_value one_ = out_value(1);
		_get_matrix_data<0, 0>(out_) = one_;
		if constexpr (OutMatrix_::num_columns >= 4 && OutMatrix_::num_rows >= 4)
		{
			_matrix_set_trace_region<3, OutMatrix_, out_value>(out_, one_);
		}
		return out_;
	}
	template<class OutMatrix_, class Theta_, class CosCalculator_, class SinCalculator_>
	constexpr inline OutMatrix_ _make_rotation_matrix_y(const Theta_& theta_)
	{
		using out_value = typename OutMatrix_::value_type;

		OutMatrix_ out_ = OutMatrix_();
		out_value cos_ = static_cast<out_value>(CosCalculator_()(theta_));
		out_value sin_ = static_cast<out_value>(SinCalculator_()(theta_));
		_get_matrix_data<0, 0>(out_) = cos_;
		_get_matrix_data<2, 0>(out_) = EmuCore::do_negate<out_value>()(sin_);
		_get_matrix_data<0, 2>(out_) = sin_;
		_get_matrix_data<2, 2>(out_) = cos_;

		// Set unfilled trace elements to 1 before returning.
		const out_value one_ = out_value(1);
		_get_matrix_data<1, 1>(out_) = one_;
		if constexpr (OutMatrix_::num_columns >= 4 && OutMatrix_::num_rows >= 4)
		{
			_matrix_set_trace_region<3, OutMatrix_, out_value>(out_, one_);
		}
		return out_;
	}
	template<class OutMatrix_, class Theta_, class CosCalculator_, class SinCalculator_>
	constexpr inline OutMatrix_ _make_rotation_matrix_z(const Theta_& theta_)
	{
		using out_value = typename OutMatrix_::value_type;

		OutMatrix_ out_ = OutMatrix_();
		out_value cos_ = static_cast<out_value>(CosCalculator_()(theta_));
		out_value sin_ = static_cast<out_value>(SinCalculator_()(theta_));
		_get_matrix_data<0, 0>(out_) = cos_;
		_get_matrix_data<1, 0>(out_) = EmuCore::do_negate<out_value>()(sin_);
		_get_matrix_data<0, 1>(out_) = sin_;
		_get_matrix_data<1, 1>(out_) = cos_;

		// Set unfilled trace elements to 1 before returning.
		if constexpr (OutMatrix_::num_columns >= 3 && OutMatrix_::num_rows >= 3)
		{
			_matrix_set_trace_region<2, OutMatrix_, out_value>(out_, out_value(1));
		}
		return out_;
	}
#pragma endregion
}

#endif
