#ifndef EMU_MATH_MATRIX_UNDERLYING_SPECIAL_OPERATIONS_H_INC_
#define EMU_MATH_MATRIX_UNDERLYING_SPECIAL_OPERATIONS_H_INC_ 1

#include "_matrix_underlying_copy.h"
#include "_matrix_tmp.h"

namespace EmuMath::Helpers::_matrix_underlying
{
	template<class OutMatrix_, class InMatrix_, bool DoAssertions_, std::size_t...OutColumnIndices_, std::size_t...OutRowIndices_>
	[[nodiscard]] constexpr inline bool _matrix_transpose_is_valid
	(
		std::index_sequence<OutColumnIndices_...> out_column_indices_,
		std::index_sequence<OutRowIndices_...> out_row_indices_
	)
	{
		using out_matrix_uq = EmuCore::TMP::remove_ref_cv_t<OutMatrix_>;
		constexpr bool copy_success_ = (... && _matrix_create_from_matrix_index_is_valid<out_matrix_uq, InMatrix_, DoAssertions_, OutRowIndices_, OutColumnIndices_>());
		if constexpr (copy_success_)
		{
			constexpr bool is_constructible_ = std::is_constructible_v
			<
				out_matrix_uq,
				decltype(_matrix_create_out_from_index<out_matrix_uq, InMatrix_, OutRowIndices_, OutColumnIndices_>(std::declval<InMatrix_>()))...
			>;
			if constexpr (is_constructible_)
			{
				return true;
			}
			else
			{
				static_assert(!DoAssertions_, "Invalid EmuMath Matrix Transpose output: The output Matrix cannot be constructed from one stored_type argument per contained element.");
				return false;
			}
		}
		else
		{
			static_assert(!DoAssertions_, "Invalid EmuMath Matrix Transpose Parameters: The output Matrix's stored_type cannot be created from the input Matrix for all indices.");
			return false;
		}
	}

	template<class OutMatrix_, class InMatrix_, bool DoAssertions_>
	[[nodiscard]] constexpr inline bool _matrix_transpose_is_valid()
	{
		using out_matrix_uq = EmuCore::TMP::remove_ref_cv_t<OutMatrix_>;
		using out_indices = EmuMath::TMP::make_full_matrix_index_sequences<out_matrix_uq>;
		using column_index_sequence = typename out_indices::column_index_sequence;
		using row_index_sequence = typename out_indices::row_index_sequence;
		return _matrix_transpose_is_valid<out_matrix_uq, InMatrix_, true>(column_index_sequence(), row_index_sequence());
	}

	template<class OutMatrix_, class InMatrix_, std::size_t...OutColumnIndices_, std::size_t...OutRowIndices_>
	[[nodiscard]] constexpr inline OutMatrix_ _matrix_transpose_execution
	(
		std::index_sequence<OutColumnIndices_...> out_column_indices_,
		std::index_sequence<OutRowIndices_...> out_row_indices_,
		InMatrix_&& in_matrix_
	)
	{
		if constexpr (_matrix_transpose_is_valid<OutMatrix_, InMatrix_, true>(std::index_sequence<OutColumnIndices_...>(), std::index_sequence<OutRowIndices_...>()))
		{
			// Disable warning as intended use will never duplicate an index access, so we are never actually moving from the same object
EMU_CORE_MSVC_PUSH_WARNING_STACK
EMU_CORE_MSVC_DISABLE_WARNING(EMU_CORE_WARNING_BAD_MOVE)
			return OutMatrix_
			(
				_matrix_create_out_from_index<OutMatrix_, InMatrix_, OutRowIndices_, OutColumnIndices_>(std::forward<InMatrix_>(in_matrix_))...
			);
EMU_CORE_MSVC_POP_WARNING_STACK
		}
		else
		{
			static_assert
			(
				EmuCore::TMP::get_false<OutMatrix_>(),
				"Could not successfully determine the transpose of an EmuMath Matrix."
			);
		}
	}

	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, bool OutColumnMajor_, class InMatrix_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_> _matrix_transpose(InMatrix_&& in_matrix_)
	{
		using out_matrix = EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>;
		using out_indices = EmuMath::TMP::make_full_matrix_index_sequences<out_matrix>;
		using column_index_sequence = typename out_indices::column_index_sequence;
		using row_index_sequence = typename out_indices::row_index_sequence;
		return _matrix_transpose_execution<out_matrix, InMatrix_>(column_index_sequence(), row_index_sequence(), std::forward<InMatrix_>(in_matrix_));
	}

	template<std::size_t ColumnIndex_, std::size_t RowIndex_, class Matrix_>
	[[nodiscard]] constexpr inline typename EmuCore::TMP::remove_ref_cv_t<Matrix_>::stored_type _matrix_identity_element()
	{
		if constexpr (ColumnIndex_ == RowIndex_)
		{
			using stored_type = typename EmuCore::TMP::remove_ref_cv_t<Matrix_>::stored_type;
			if constexpr (EmuCore::TMP::valid_construct_or_cast<stored_type, decltype(1)>())
			{
				return EmuCore::TMP::construct_or_cast<stored_type>(1);
			}
			else
			{
				static_assert
				(
					EmuCore::TMP::get_false<Matrix_>(),
					"Attempted to make an Identity Matrix for a specified EmuMath Matrix type, but the provided Matrix's stored_type cannot be constructed or static_cast to with an argument of 1."
				);
			}
		}
		else
		{
			return _matrix_get_non_contained<Matrix_>();
		}
	}

	template<std::size_t ColumnIndex_, std::size_t RowIndex_, class Matrix_>
	constexpr inline void _matrix_assign_identity_element(Matrix_& matrix_)
	{
		using get_result = decltype(_matrix_get<ColumnIndex_, RowIndex_>(matrix_));
		if constexpr (ColumnIndex_ == RowIndex_)
		{
			using value_uq = typename EmuCore::TMP::remove_ref_cv_t<Matrix_>::value_type_uq;
			if constexpr (EmuCore::TMP::valid_assign_direct_or_cast<value_uq, decltype(1), get_result>())
			{
				EmuCore::TMP::assign_direct_or_cast<value_uq>(_matrix_get<ColumnIndex_, RowIndex_>(matrix_), 1);
			}
			else
			{
				static_assert
				(
					EmuCore::TMP::get_false<Matrix_>(),
					"Attempted to assign the Identity Matrix to a provided EmuMath Matrix, but the Matrix cannot have one of its main diagonal elements assigned by a value of 1, or the value of 1 static_cast to its value_type_uq."
				);
			}
		}
		else
		{
			if constexpr (std::is_assignable_v<get_result, decltype(0)>)
			{
				_matrix_get<ColumnIndex_, RowIndex_>(matrix_) = 0;
			}
			else if constexpr (std::is_assignable_v<get_result, decltype(_matrix_get_non_contained<Matrix_>())>)
			{
				_matrix_get<ColumnIndex_, RowIndex_>(matrix_) = _matrix_get_non_contained<Matrix_>();
			}
			else
			{
				static_assert
				(
					EmuCore::TMP::get_false<Matrix_>(),
					"Attempted to assign the Identity Matrix to a provided EmuMath Matrix, but the Matrix cannot have one of its non-main-diagonal elements assigned by a value of 0, or its implied-zero non-contained value."
				);
			}
		}
	}

	template<class Matrix_, std::size_t...ColumnIndices_, std::size_t...RowIndices_>
	[[nodiscard]] constexpr inline Matrix_ _matrix_make_identity(std::index_sequence<ColumnIndices_...> column_indices_, std::index_sequence<RowIndices_...> row_indices_)
	{
		if constexpr (std::is_constructible_v<Matrix_, decltype(_matrix_identity_element<ColumnIndices_, RowIndices_, Matrix_>())...>)
		{
			return Matrix_(_matrix_identity_element<ColumnIndices_, RowIndices_, Matrix_>()...);
		}
		else
		{
			static_assert
			(
				EmuCore::TMP::get_false<Matrix_>(),
				"Attempted to make an Identy Matrix for a specified EmuMath Matrix type, but the provided Matrix_ cannot be constructed with a value argument of its stored_type per element."
			);
		}
	}

	template<class Matrix_, std::size_t...ColumnIndices_, std::size_t...RowIndices_>
	constexpr inline void _matrix_assign_identity(Matrix_& matrix_, std::index_sequence<ColumnIndices_...> column_indices_, std::index_sequence<RowIndices_...> row_indices_)
	{
		(_matrix_assign_identity_element<ColumnIndices_, RowIndices_>(matrix_), ...);
	}

	template<std::size_t NumColumns_, std::size_t NumRows_, typename T_, bool ColumnMajor_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_> _matrix_identity()
	{
		using matrix_type = EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>;
		using indices = EmuMath::TMP::make_full_matrix_index_sequences<matrix_type>;
		return _matrix_make_identity<matrix_type>(typename indices::column_index_sequence(), typename indices::row_index_sequence());
	}

	template<std::size_t NumColumns_, std::size_t NumRows_, typename T_, bool ColumnMajor_>
	constexpr inline void _matrix_identity(EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>& matrix_)
	{
		using matrix_type = EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>;
		using indices = EmuMath::TMP::make_full_matrix_index_sequences<matrix_type>;
		return _matrix_assign_identity(matrix_, typename indices::column_index_sequence(), typename indices::row_index_sequence());
	}

#pragma region NAYUSTY
	
	template<std::size_t Index_, typename Out_, class RowEchelonMatrix_, class Multiplier_>
	constexpr inline void _calculate_determinant_from_row_echelon(Out_& out_, const RowEchelonMatrix_& row_echelon_, Multiplier_& mult_)
	{
		if constexpr (Index_ < RowEchelonMatrix_::num_rows)
		{
			out_ = mult_(out_, _matrix_get<Index_, Index_>(row_echelon_));
			_calculate_determinant_from_row_echelon<Index_ + 1, Out_, RowEchelonMatrix_, Multiplier_>(out_, row_echelon_, mult_);
		}
	}
	template<typename Out_, class RowEchelonMatrix_, class Multiplier_, std::size_t...RowEchelonRowIndicesExcept0_>
	constexpr inline Out_ _calculate_determinant_from_row_echelon(const RowEchelonMatrix_& row_echelon_, Multiplier_& mult_, std::index_sequence<RowEchelonRowIndicesExcept0_...> row_echelon_row_indices_except_0_)
	{
		if constexpr (RowEchelonMatrix_::num_rows == 0)
		{
			return Out_(0);
		}
		else if constexpr (RowEchelonMatrix_::num_rows == 1)
		{
			return static_cast<Out_>(_matrix_get<0, 0>(row_echelon_));
		}
		else
		{
			// The determinant of a matrix may be calculated from the product of its main diagonal when converted to row-echelon form
			Out_ out_ = static_cast<Out_>(_matrix_get<0, 0>(row_echelon_));
			(
				_calculate_determinant_from_row_echelon<RowEchelonRowIndicesExcept0_>
				(
					out_,
					row_echelon_,
					mult_
				), ...
			);
			return out_;
		}
	}

	template<std::size_t ColumnIndex_, std::size_t RowIndex_, std::size_t PivotIndex_, class OutMatrix_, class InMatrix_, class Adder_, class Multiplier_, typename RowMult_>
	constexpr inline void _calculate_matrix_inverse_gauss_jordan_eliminate_row
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
			auto& in_element_ = _matrix_get<ColumnIndex_, RowIndex_>(in_calc_);
			in_element_ = add_(in_element_, mult_(row_multiplier_, _matrix_get<ColumnIndex_, PivotIndex_>(in_calc_)));

			auto& out_element_ = _matrix_get<ColumnIndex_, RowIndex_>(out_);
			out_element_ = add_(out_element_, mult_(row_multiplier_, _matrix_get<ColumnIndex_, PivotIndex_>(out_)));
		}
	}

	template<std::size_t RowIndex_, std::size_t PivotIndex_, class OutMatrix_, class InMatrix_, class Adder_, class Multiplier_, typename RowMult_, std::size_t...OutColumnIndices_>
	constexpr inline void _calculate_matrix_inverse_gauss_jordan_eliminate_row
	(
		OutMatrix_& out_,
		InMatrix_& in_calc_,
		Adder_& add_,
		Multiplier_& mult_,
		RowMult_ row_multiplier_,
		std::index_sequence<OutColumnIndices_...> column_indices_
	)
	{
		(
			_calculate_matrix_inverse_gauss_jordan_eliminate_row<OutColumnIndices_, RowIndex_, PivotIndex_>
			(
				out_,
				in_calc_,
				add_,
				mult_,
				row_multiplier_
			), ...
		);
	}

	template<std::size_t PivotIndex_, class OutMatrix_, class InMatrix_, class Adder_, class Multiplier_, class Divider_, typename PivotNeg_, std::size_t...OutRowIndicesExceptPivot_>
	constexpr inline void _calculate_matrix_inverse_gauss_jordan_with_pivot
	(
		OutMatrix_& out_,
		InMatrix_& in_calc_,
		Adder_& add_,
		Multiplier_& mult_,
		Divider_& div_,
		PivotNeg_ pivot_neg_,
		std::index_sequence<OutRowIndicesExceptPivot_...> out_row_indices_except_pivot_
	)
	{
		(
			_calculate_matrix_inverse_gauss_jordan_eliminate_row<OutRowIndicesExceptPivot_, PivotIndex_>
			(
				out_,
				in_calc_,
				add_,
				mult_,
				div_(_matrix_get<PivotIndex_, OutRowIndicesExceptPivot_>(in_calc_), pivot_neg_),
				std::make_index_sequence<OutMatrix_::num_columns>()
			), ...
		);
	}

	template<std::size_t RowIndex_, class OutMatrix_, class Multiplier_, typename PivotReciprocal_, std::size_t...OutColumnIndices_>
	constexpr inline void _calculate_matrix_inverse_gauss_jordan_make_row_pivot_equal_to_1(OutMatrix_& out_, Multiplier_& mult_, PivotReciprocal_ pivot_reciprocal_, std::index_sequence<OutColumnIndices_...> out_column_indices_)
	{
		(
			(
				_matrix_get<OutColumnIndices_, RowIndex_>(out_) = mult_(_matrix_get<OutColumnIndices_, RowIndex_>(out_), pivot_reciprocal_)
			), ...
		);
	}

	template<class OutMatrix_, class InMatrix_, class Multiplier_, class Divider_, std::size_t...OutRowIndices_>
	constexpr inline void _calculate_matrix_inverse_gauss_jordan_make_pivots_equal_to_1(OutMatrix_& out_, const InMatrix_& in_calc_, Multiplier_& mult_, Divider_& div_, std::index_sequence<OutRowIndices_...> out_row_indices_)
	{
		(
			_calculate_matrix_inverse_gauss_jordan_make_row_pivot_equal_to_1<OutRowIndices_, OutMatrix_>
			(
				out_,
				mult_,
				div_(typename OutMatrix_::value_type(1), _matrix_get<OutRowIndices_, OutRowIndices_>(in_calc_)),
				std::make_index_sequence<OutMatrix_::num_columns>()
			), ...
		);
	}

	template<class OutMatrix_, class InMatrix_, class Adder_, class Multiplier_, class Divider_, class Negator_, std::size_t...OutRowIndices_>
	constexpr inline void _calculate_matrix_inverse_gauss_jordan(OutMatrix_& out_, InMatrix_& in_calc_, Adder_& add_, Multiplier_& mult_, Divider_& div_, Negator_& negate_, std::index_sequence<OutRowIndices_...> out_row_indices_)
	{
		(
			_calculate_matrix_inverse_gauss_jordan_with_pivot<OutRowIndices_>
			(
				out_,
				in_calc_,
				add_,
				mult_,
				div_,
				negate_(_matrix_get<OutRowIndices_, OutRowIndices_>(in_calc_)),
				typename EmuCore::TMP::make_int_sequence_excluding_values<std::index_sequence<OutRowIndices_...>, OutRowIndices_>::type()
			), ...
		);
	}

	template<class OutMatrix_, class InMatrix_, typename CalcType_>
	[[nodiscard]] constexpr inline OutMatrix_ _calculate_matrix_inverse_gauss_jordan(const InMatrix_& in_)
	{
		using Adder_ = EmuCore::do_add<CalcType_, CalcType_>;
		using Multiplier_ = EmuCore::do_multiply<CalcType_, CalcType_>;
		using Divider_ = EmuCore::do_divide<CalcType_, CalcType_>;
		using Negator_ = EmuCore::do_negate<CalcType_>;

		EmuMath::Matrix<InMatrix_::num_columns, InMatrix_::num_rows, CalcType_, InMatrix_::is_column_major> in_calc_(in_);
		auto out_ = EmuMath::Matrix<OutMatrix_::num_columns, OutMatrix_::num_rows, CalcType_, OutMatrix_::is_column_major>::identity();
		Adder_ add_ = Adder_();
		Multiplier_ mult_ = Multiplier_();
		Divider_ div_ = Divider_();
		Negator_ negate_ = Negator_();

		using out_row_indices = std::make_index_sequence<OutMatrix_::num_rows>;
		_calculate_matrix_inverse_gauss_jordan(out_, in_calc_, add_, mult_, div_, negate_, out_row_indices());
		_calculate_matrix_inverse_gauss_jordan_make_pivots_equal_to_1(out_, in_calc_, mult_, div_, out_row_indices());

		return out_;
	}
	template<class OutMatrix_, class InMatrix_, typename CalcType_, typename OutDeterminant_>
	[[nodiscard]] constexpr inline OutMatrix_ _calculate_matrix_inverse_gauss_jordan(const InMatrix_& in_, OutDeterminant_& out_determinant_)
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

		using out_row_indices = std::make_index_sequence<OutMatrix_::num_rows>;
		_calculate_matrix_inverse_gauss_jordan(out_, in_calc_, add_, mult_, div_, negate_, out_row_indices());
		_calculate_matrix_inverse_gauss_jordan_make_pivots_equal_to_1(out_, in_calc_, mult_, div_, out_row_indices());
		out_determinant_ = static_cast<OutDeterminant_>(_calculate_determinant_from_row_echelon<CalcType_>(in_calc_, mult_, EmuCore::TMP::make_index_sequence_excluding_0<OutMatrix_::num_rows>()));

		return out_;
	}

	template<class OutScalar_, class InMatrix_, typename OutDeterminant_>
	[[nodiscard]] constexpr inline auto _calculate_matrix_inverse_gauss_jordan(const InMatrix_& in_, OutDeterminant_& out_determinant_)
	{
		using _in_mat_uq = typename std::remove_cvref<InMatrix_>::type;
		constexpr std::size_t num_columns = _in_mat_uq::num_columns;
		constexpr std::size_t num_rows = _in_mat_uq::num_rows;
		constexpr bool is_column_major = _in_mat_uq::is_column_major;

		using calc_type = typename EmuCore::TMP::largest_floating_point<typename std::remove_cvref<OutScalar_>::type, typename _in_mat_uq::preferred_floating_point>::type;
		using Adder_ = EmuCore::do_add<calc_type, calc_type>;
		using Multiplier_ = EmuCore::do_multiply<calc_type, calc_type>;
		using Divider_ = EmuCore::do_divide<calc_type, calc_type>;
		using Negator_ = EmuCore::do_negate<calc_type>;

		auto in_calc_ = EmuMath::Matrix<num_columns, num_rows, calc_type, is_column_major>(in_);
		auto out_ = EmuMath::Matrix<num_columns, num_rows, calc_type, is_column_major>::identity();
		Adder_ add_ = Adder_();
		Multiplier_ mult_ = Multiplier_();
		Divider_ div_ = Divider_();
		Negator_ negate_ = Negator_();

		using out_row_indices = std::make_index_sequence<num_rows>;
		_calculate_matrix_inverse_gauss_jordan(out_, in_calc_, add_, mult_, div_, negate_, out_row_indices());
		_calculate_matrix_inverse_gauss_jordan_make_pivots_equal_to_1(out_, in_calc_, mult_, div_, out_row_indices());
		return static_cast<typename std::remove_cvref<OutScalar_>::type>
		(
			_calculate_determinant_from_row_echelon<calc_type>(in_calc_, mult_, EmuCore::TMP::make_index_sequence_excluding_0<num_rows>())
		);
	}
#pragma endregion
}

#endif
