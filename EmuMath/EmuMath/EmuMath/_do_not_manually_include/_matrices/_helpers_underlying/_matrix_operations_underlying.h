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
	template<std::size_t Index_, typename Out_, class RowEchelonMatrix_, class Multiplier_>
	constexpr inline void _calculate_determinant_from_row_echelon(Out_& out_, const RowEchelonMatrix_& row_echelon_, Multiplier_& mult_)
	{
		if constexpr (Index_ < RowEchelonMatrix_::num_rows)
		{
			out_ = mult_(out_, _get_matrix_data<Index_, Index_>(row_echelon_));
			_calculate_determinant_from_row_echelon<Index_ + 1, Out_, RowEchelonMatrix_, Multiplier_>(out_, row_echelon_, mult_);
		}
	}
	template<typename Out_, class RowEchelonMatrix_, class Multiplier_>
	constexpr inline Out_ _calculate_determinant_from_row_echelon(const RowEchelonMatrix_& row_echelon_, Multiplier_& mult_)
	{
		// The determinant of a matrix may be calculated from the product of its main diagonal when covnerted to row-echelon form
		Out_ out_ = Out_(1);
		_calculate_determinant_from_row_echelon<0, Out_, RowEchelonMatrix_, Multiplier_>(out_, row_echelon_, mult_);
		return out_;
	}

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
			out_ = adder_(out_, static_cast<Out_>(_get_matrix_data<Index_, Index_>(matrix_)));
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
				{
					using out_value = typename OutMatrix_::value_type;
					using sub_mat = typename EmuMath::TMP::emu_matrix_submatrix_excluding_element_region<typename Matrix_::value_type, Matrix_::is_column_major, Matrix_>::type;
					const out_value val_ = _calculate_matrix_determinant_laplace
					<
						out_value,
						sub_mat
					>(_get_submatrix_excluding_element_region<ColumnIndex_, RowIndex_, sub_mat, const Matrix_>(matrix_));
					_get_matrix_data<ColumnIndex_, RowIndex_>(out_) = val_;
				}
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
	constexpr inline void _transform_matrix_minors_to_cofactors(const InMatrix_& in_, OutMatrix_& out_, Negator_& negator_)
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
		reciprocal_type det_reciprocal_ = reciprocal_type(1) / static_cast<reciprocal_type>(outDeterminant_);
		return _matrix_multi_arg_operation<EmuCore::do_multiply, OutMatrix_, OutMatrix_, reciprocal_type>(adjugate_, det_reciprocal_);
	}

	template<std::size_t ColumnIndex_, std::size_t RowIndex_, std::size_t PivotIndex_, class OutMatrix_, class InMatrix_, class Adder_, class Multiplier_, typename RowMult_>
	constexpr inline void _calculate_matrix_inverse_gj_eliminate_row
	(
		OutMatrix_& out_,
		InMatrix_& in_calc_,
		Adder_& add_,
		Multiplier_& mult_,
		RowMult_ row_multiplier_
	)
	{
		if constexpr (ColumnIndex_ < OutMatrix_::num_columns)
		{
			auto& in_element_ = _get_matrix_data<ColumnIndex_, RowIndex_>(in_calc_);
			in_element_ = add_(in_element_, mult_(row_multiplier_, _get_matrix_data<ColumnIndex_, PivotIndex_>(in_calc_)));

			auto& out_element_ = _get_matrix_data<ColumnIndex_, RowIndex_>(out_);
			out_element_ = add_(out_element_, mult_(row_multiplier_, _get_matrix_data<ColumnIndex_, PivotIndex_>(out_)));

			_calculate_matrix_inverse_gj_eliminate_row
			<
				ColumnIndex_ + 1,
				RowIndex_,
				PivotIndex_,
				OutMatrix_,
				InMatrix_,
				Adder_,
				Multiplier_,
				RowMult_
			>(out_, in_calc_, add_, mult_, row_multiplier_);
		}
	}
	template<std::size_t RowIndex_, std::size_t PivotIndex_, class OutMatrix_, class InMatrix_, class Adder_, class Multiplier_, class Divider_, typename PivotNeg_>
	constexpr inline void _calculate_matrix_inverse_gj_with_pivot
	(
		OutMatrix_& out_,
		InMatrix_& in_calc_,
		Adder_& add_,
		Multiplier_& mult_,
		Divider_& div_,
		PivotNeg_ pivot_neg_
	)
	{
		if constexpr (RowIndex_ < OutMatrix_::num_rows)
		{
			if constexpr (RowIndex_ != PivotIndex_)
			{
				typename OutMatrix_::value_type multiplier_ = div_(_get_matrix_data<PivotIndex_, RowIndex_>(in_calc_), pivot_neg_);
				_calculate_matrix_inverse_gj_eliminate_row
				<
					0,
					RowIndex_,
					PivotIndex_,
					OutMatrix_,
					InMatrix_,
					Adder_,
					Multiplier_,
					decltype(multiplier_)
				>(out_, in_calc_, add_, mult_, multiplier_);
			}
			_calculate_matrix_inverse_gj_with_pivot
			<
				RowIndex_ + 1,
				PivotIndex_,
				OutMatrix_,
				InMatrix_,
				Adder_,
				Multiplier_,
				Divider_,
				PivotNeg_
			>(out_, in_calc_, add_, mult_, div_, pivot_neg_);
		}
	}
	template<std::size_t PivotIndex_, class OutMatrix_, class InMatrix_, class Adder_, class Multiplier_, class Divider_, class Negator_>
	constexpr inline void _calculate_matrix_inverse_gj(OutMatrix_& out_, InMatrix_& in_calc_, Adder_& add_, Multiplier_& mult_, Divider_& div_, Negator_& negate_)
	{
		if constexpr (PivotIndex_ < OutMatrix_::num_rows)
		{
			typename OutMatrix_::value_type pivot_neg_ = negate_(_get_matrix_data<PivotIndex_, PivotIndex_>(in_calc_));
			_calculate_matrix_inverse_gj_with_pivot
			<
				0,
				PivotIndex_,
				OutMatrix_,
				InMatrix_,
				Adder_,
				Multiplier_,
				Divider_,
				decltype(pivot_neg_)
			>(out_, in_calc_, add_, mult_, div_, pivot_neg_);
			_calculate_matrix_inverse_gj<PivotIndex_ + 1, OutMatrix_, InMatrix_, Adder_, Multiplier_, Divider_, Negator_>(out_, in_calc_, add_, mult_, div_, negate_);
		}
	}
	template<std::size_t ColumnIndex_, std::size_t RowIndex_, class OutMatrix_, class Multiplier_, typename PivotReciprocal_>
	constexpr inline void _calculate_matrix_inverse_gj_make_row_pivot_1(OutMatrix_& out_, Multiplier_& mult_, PivotReciprocal_ pivot_reciprocal_)
	{
		if constexpr (ColumnIndex_ < OutMatrix_::num_columns)
		{
			auto& out_element_ = _get_matrix_data<ColumnIndex_, RowIndex_>(out_);
			out_element_ = mult_(out_element_, pivot_reciprocal_);
			_calculate_matrix_inverse_gj_make_row_pivot_1<ColumnIndex_ + 1, RowIndex_, OutMatrix_, Multiplier_, PivotReciprocal_>(out_, mult_, pivot_reciprocal_);
		}
	}
	template<std::size_t PivotIndex_, class OutMatrix_, class InMatrix_, class Multiplier_, class Divider_>
	constexpr inline void _calculate_matrix_inverse_gj_make_pivots_1(OutMatrix_& out_, const InMatrix_& in_calc_, Multiplier_& mult_, Divider_& div_)
	{
		if constexpr (PivotIndex_ < OutMatrix_::num_rows)
		{
			typename OutMatrix_::value_type pivot_reciprocal_ = div_(typename OutMatrix_::value_type(1), _get_matrix_data<PivotIndex_, PivotIndex_>(in_calc_));
			_calculate_matrix_inverse_gj_make_row_pivot_1<0, PivotIndex_, OutMatrix_, Multiplier_, decltype(pivot_reciprocal_)>(out_, mult_, pivot_reciprocal_);
			_calculate_matrix_inverse_gj_make_pivots_1<PivotIndex_ + 1, OutMatrix_, InMatrix_, Multiplier_, Divider_>(out_, in_calc_, mult_, div_);
		}
	}
	template<class OutMatrix_, class InMatrix_, typename CalcType_>
	[[nodiscard]] constexpr inline OutMatrix_ _calculate_matrix_inverse_gj(const InMatrix_& in_)
	{
		using Adder_ = EmuCore::do_add<CalcType_, CalcType_>;
		using Multiplier_ = EmuCore::do_multiply<CalcType_, CalcType_>;
		using Divider_ = EmuCore::do_divide<CalcType_, CalcType_>;
		using Negator_ = EmuCore::do_negate<CalcType_>;

		EmuMath::Matrix<InMatrix_::num_columns, InMatrix_::num_rows, CalcType_, InMatrix_::is_column_major> in_calc_(in_);
		EmuMath::Matrix<OutMatrix_::num_columns, OutMatrix_::num_rows, CalcType_, OutMatrix_::is_column_major> out_ = _make_identity_matrix<decltype(out_)>();
		Adder_ add_ = Adder_();
		Multiplier_ mult_ = Multiplier_();
		Divider_ div_ = Divider_();
		Negator_ negate_ = Negator_();

		_calculate_matrix_inverse_gj<0, decltype(out_), decltype(in_calc_), Adder_, Multiplier_, Divider_, Negator_>(out_, in_calc_, add_, mult_, div_, negate_);
		_calculate_matrix_inverse_gj_make_pivots_1<0, decltype(out_), decltype(in_calc_), Multiplier_, Divider_>(out_, in_calc_, mult_, div_);

		return out_;
	}
	template<class OutMatrix_, class InMatrix_, typename CalcType_, typename OutDeterminant_>
	[[nodiscard]] constexpr inline OutMatrix_ _calculate_matrix_inverse_gj(const InMatrix_& in_, OutDeterminant_& out_determinant_)
	{
		using Adder_ = EmuCore::do_add<CalcType_, CalcType_>;
		using Multiplier_ = EmuCore::do_multiply<CalcType_, CalcType_>;
		using Divider_ = EmuCore::do_divide<CalcType_, CalcType_>;
		using Negator_ = EmuCore::do_negate<CalcType_>;

		EmuMath::Matrix<InMatrix_::num_columns, InMatrix_::num_rows, CalcType_, InMatrix_::is_column_major> in_calc_(in_);
		EmuMath::Matrix<OutMatrix_::num_columns, OutMatrix_::num_rows, CalcType_, OutMatrix_::is_column_major> out_ = _make_identity_matrix<decltype(out_)>();
		Adder_ add_ = Adder_();
		Multiplier_ mult_ = Multiplier_();
		Divider_ div_ = Divider_();
		Negator_ negate_ = Negator_();

		_calculate_matrix_inverse_gj<0, decltype(out_), decltype(in_calc_), Adder_, Multiplier_, Divider_, Negator_>(out_, in_calc_, add_, mult_, div_, negate_);
		_calculate_matrix_inverse_gj_make_pivots_1<0, decltype(out_), decltype(in_calc_), Multiplier_, Divider_>(out_, in_calc_, mult_, div_);
		out_determinant_ = static_cast<OutDeterminant_>(_calculate_determinant_from_row_echelon<CalcType_, decltype(in_calc_), Multiplier_>(in_calc_, mult_));

		return out_;
	}
}

#endif
