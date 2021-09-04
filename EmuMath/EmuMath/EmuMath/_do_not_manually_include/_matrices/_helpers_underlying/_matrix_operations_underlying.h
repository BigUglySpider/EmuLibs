#ifndef EMU_MATH__UNDERLYING_MATRIX_OPERATIONS_H_INC_
#define EMU_MATH__UNDERLYING_MATRIX_OPERATIONS_H_INC_ 1

#include "_common_underlying_matrix_helper_includes.h"
#include "_matrix_arithmetic_underlying.h"
#include "_matrix_gets_underlying.h"
#include "_matrix_reinterpretations_underlying.h"
#include "_matrix_sets_underlying.h"
#include "_matrix_validity_checks_underlying.h"

namespace EmuMath::Helpers::_underlying_matrix_funcs
{
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
}

#endif
