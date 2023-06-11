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

#pragma region GAUSS_JORDAN	
	template<std::size_t Index_, typename Out_, class RowEchelonMatrix_, class Multiplier_>
	constexpr inline void _calculate_determinant_from_row_echelon(Out_& out_, const RowEchelonMatrix_& row_echelon_, Multiplier_& mult_)
	{
		out_ = mult_(out_, _matrix_get<Index_, Index_>(row_echelon_));
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
		auto& in_element_ = _matrix_get<ColumnIndex_, RowIndex_>(in_calc_);
		in_element_ = add_(in_element_, mult_(row_multiplier_, _matrix_get<ColumnIndex_, PivotIndex_>(in_calc_)));

		auto& out_element_ = _matrix_get<ColumnIndex_, RowIndex_>(out_);
		out_element_ = add_(out_element_, mult_(row_multiplier_, _matrix_get<ColumnIndex_, PivotIndex_>(out_)));
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

	template<std::size_t PivotIndex_, class OutMatrix_, class InMatrix_, class Adder_, class Multiplier_, class DivisionApplier_, typename PivotNeg_, std::size_t...OutRowIndicesExceptPivot_>
	constexpr inline void _calculate_matrix_inverse_gauss_jordan_with_pivot
	(
		OutMatrix_& out_,
		InMatrix_& in_calc_,
		Adder_& add_,
		Multiplier_& mult_,
		DivisionApplier_& division_applier_,
		PivotNeg_ pivot_neg_divisor_,
		std::index_sequence<OutRowIndicesExceptPivot_...> out_row_indices_except_pivot_
	)
	{
		// division_applier_ and pivot_neg_divisor_ may be multiplication-function and reciprocal pair or division-function and divisor pair, depending on if reciprocal division was allowed
		// --- As such, we always want to have the pivot_neg_divisor_ on the right-hand side of operation, as we could either be multiplying or dividing to perform the division
		(
			_calculate_matrix_inverse_gauss_jordan_eliminate_row<OutRowIndicesExceptPivot_, PivotIndex_>
			(
				out_,
				in_calc_,
				add_,
				mult_,
				division_applier_(_matrix_get<PivotIndex_, OutRowIndicesExceptPivot_>(in_calc_), pivot_neg_divisor_),
				std::make_index_sequence<OutMatrix_::num_columns>()
			), ...
		);
	}

	template<std::size_t RowIndex_, class OutMatrix_, class DivisionApplier_, typename PivotReciprocal_, std::size_t...OutColumnIndices_>
	constexpr inline void _calculate_matrix_inverse_gauss_jordan_make_row_pivot_equal_to_1(OutMatrix_& out_, DivisionApplier_& division_applier_, PivotReciprocal_ pivot_divisor_, std::index_sequence<OutColumnIndices_...> out_column_indices_)
	{
		// division_applier_ and pivot_divisor_ may be multiplication-function and reciprocal pair or division-function and divisor pair, depending on if reciprocal division was allowed
		// --- As such, we always want to have the pivot_divisor_ on the right-hand side of operation, as we could either be multiplying or dividing to perform the division
		(
			(
				_matrix_get<OutColumnIndices_, RowIndex_>(out_) = division_applier_(_matrix_get<OutColumnIndices_, RowIndex_>(out_), pivot_divisor_)
			), ...
		);
	}

	template<bool UseReciprocalDivision_, class OutMatrix_, class InMatrix_, class Multiplier_, class Divider_, std::size_t...OutRowIndices_>
	constexpr inline void _calculate_matrix_inverse_gauss_jordan_make_pivots_equal_to_1(OutMatrix_& out_, const InMatrix_& in_calc_, Multiplier_& mult_, Divider_& div_, std::index_sequence<OutRowIndices_...> out_row_indices_)
	{
		using out_column_indices = std::make_index_sequence<std::remove_cvref_t<OutMatrix_>::num_columns>;

		if constexpr(UseReciprocalDivision_)
		{
			// Can optimise to divide once and use reciprocal multiplication for calculating the row
			// --- Pass mult_ as the divsion applier, and pivot divisor will be the reciprocal of the pivot
			(
				_calculate_matrix_inverse_gauss_jordan_make_row_pivot_equal_to_1<OutRowIndices_, OutMatrix_>
				(
					out_,
					mult_,
					div_(typename OutMatrix_::preferred_floating_point(1), _matrix_get<OutRowIndices_, OutRowIndices_>(in_calc_)),
					out_column_indices()
				), ...
			);
		}
		else
		{
			// May not optimise for reciprocal division (e.g. loss of accuracy may be unwanted)
			// --- Pass div_ as division applier, and pivot divisor is the pivot without modification
			(
				_calculate_matrix_inverse_gauss_jordan_make_row_pivot_equal_to_1<OutRowIndices_, OutMatrix_>
				(
					out_,
					div_,
					_matrix_get<OutRowIndices_, OutRowIndices_>(in_calc_),
					out_column_indices()
				), ...
			);
		}
	}

	template<bool UseReciprocalDivision_, class OutMatrix_, class InMatrix_, class Adder_, class Multiplier_, class Divider_, class Negator_, std::size_t...OutRowIndices_>
	constexpr inline void _calculate_matrix_inverse_gauss_jordan(OutMatrix_& out_, InMatrix_& in_calc_, Adder_& add_, Multiplier_& mult_, Divider_& div_, Negator_& negate_, std::index_sequence<OutRowIndices_...> out_row_indices_)
	{
		if constexpr (UseReciprocalDivision_)
		{
			// Can optimise to divide once and use reciprocal multiplication for calculating the row
			// --- Pass mult_ as the divsion applier, and negated pivot divisor will be the negated reciprocal of the pivot
			(
				_calculate_matrix_inverse_gauss_jordan_with_pivot<OutRowIndices_>
				(
					out_,
					in_calc_,
					add_,
					mult_,
					mult_,
					negate_(div_(typename OutMatrix_::preferred_floating_point(1), _matrix_get<OutRowIndices_, OutRowIndices_>(in_calc_))),
					typename EmuCore::TMP::make_int_sequence_excluding_values<std::index_sequence<OutRowIndices_...>, OutRowIndices_>::type()
				), ...
			);
		}
		else
		{
			// May not optimise for reciprocal division (e.g. loss of accuracy may be unwanted)
			// --- Pass div_ as division applier, and pivot divisor is the pivot without modification
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
	}

	template<bool AllowReciprocalDivision_, EmuConcepts::EmuMatrix InOutMatrix_>
	constexpr inline void _matrix_inverse_assign_gauss_jordan(InOutMatrix_& in_out_)
	{
		if constexpr (!std::is_const_v<InOutMatrix_>)
		{
			// Common types and constants
			using _inout_mat_uq = typename std::remove_cvref<InOutMatrix_>::type;
			constexpr std::size_t num_columns = _inout_mat_uq::num_columns;
			constexpr std::size_t num_rows = _inout_mat_uq::num_rows;
			constexpr bool is_column_major = _inout_mat_uq::is_column_major;

			using calc_type = typename EmuCore::TMP::largest_floating_point<typename _inout_mat_uq::preferred_floating_point, float>::type;
			using _calc_mat = EmuMath::Matrix<num_columns, num_rows, void, is_column_major>;
			using Adder_ = EmuCore::do_add<void, void>;
			using Multiplier_ = EmuCore::do_multiply<void, void>;
			using Divider_ = EmuCore::do_divide<void, void>;
			using Negator_ = EmuCore::do_negate<void>;

			// Prepare common data shared between funcs
			// --- We output to the provided reference when everything is done, and allow the input to be mutated as the usual `in_calc_` type
			Adder_ add_ = Adder_();
			Multiplier_ mult_ = Multiplier_();
			Divider_ div_ = Divider_();
			Negator_ negate_ = Negator_();
			auto result = EmuMath::Matrix<num_columns, num_rows, calc_type, is_column_major>::identity();

			// Eliminate rows and modify to set eliminated pivots to 1
			using out_row_indices = std::make_index_sequence<num_rows>;
			_calculate_matrix_inverse_gauss_jordan<AllowReciprocalDivision_>(result, in_out_, add_, mult_, div_, negate_, out_row_indices());
			_calculate_matrix_inverse_gauss_jordan_make_pivots_equal_to_1<AllowReciprocalDivision_>(result, in_out_, mult_, div_, out_row_indices());

			// Assign inverse result to output reference w/move semantics
			if constexpr (EmuCore::TMP::valid_assign_direct_or_cast<typename std::remove_cvref<InOutMatrix_>::type, decltype(std::move(result)), InOutMatrix_>())
			{
				EmuCore::TMP::assign_direct_or_cast<typename std::remove_cvref<InOutMatrix_>::type>(in_out_, std::move(result));
			}
			else
			{
				static_assert
				(
					EmuCore::TMP::get_false<InOutMatrix_>(),
					"Unable to finalise direct inverse assignment to an EmuMath Matrix determinant as the output type cannot be constructed or converted to from the used calculation type."
				);
			}
		}
		else
		{
			static_assert
			(
				EmuCore::TMP::get_false<InOutMatrix_>(),
				"Error attempting to perform direct inverse assignment to an EmuMath Matrix: The input Matrix is const-qualified, and cannot be assigned to."
			);
		}
	}

	template<bool AllowReciprocalDivision_, EmuConcepts::EmuMatrix InOutMatrix_, typename OutDeterminant_>
	constexpr inline void _matrix_inverse_assign_gauss_jordan(InOutMatrix_& in_out_, OutDeterminant_& out_determinant_)
	{
		if constexpr (!std::is_const_v<InOutMatrix_>)
		{
			// Common types and constants
			using _inout_mat_uq = typename std::remove_cvref<InOutMatrix_>::type;
			constexpr std::size_t num_columns = _inout_mat_uq::num_columns;
			constexpr std::size_t num_rows = _inout_mat_uq::num_rows;
			constexpr bool is_column_major = _inout_mat_uq::is_column_major;

			using calc_type = typename EmuCore::TMP::largest_floating_point<typename _inout_mat_uq::preferred_floating_point, float>::type;
			using _calc_mat = EmuMath::Matrix<num_columns, num_rows, void, is_column_major>;
			using Adder_ = EmuCore::do_add<void, void>;
			using Multiplier_ = EmuCore::do_multiply<void, void>;
			using Divider_ = EmuCore::do_divide<void, void>;
			using Negator_ = EmuCore::do_negate<void>;

			// Prepare common data shared between funcs
			// --- We output to the provided reference when everything is done, and allow the input to be mutated as the usual `in_calc_` type
			Adder_ add_ = Adder_();
			Multiplier_ mult_ = Multiplier_();
			Divider_ div_ = Divider_();
			Negator_ negate_ = Negator_();
			auto result = EmuMath::Matrix<num_columns, num_rows, calc_type, is_column_major>::identity();

			// Eliminate rows and modify to set eliminated pivots to 1
			using out_row_indices = std::make_index_sequence<num_rows>;
			_calculate_matrix_inverse_gauss_jordan<AllowReciprocalDivision_>(result, in_out_, add_, mult_, div_, negate_, out_row_indices());
			_calculate_matrix_inverse_gauss_jordan_make_pivots_equal_to_1<AllowReciprocalDivision_>(result, in_out_, mult_, div_, out_row_indices());
			
			
			// Calculate and output determinant to reference
			if constexpr (EmuCore::TMP::valid_assign_direct_or_cast<typename std::remove_cvref<OutDeterminant_>::type, calc_type&&, OutDeterminant_>())
			{
				using out_row_indices_except_0 = EmuCore::TMP::make_index_sequence_excluding_0<num_rows>;
				EmuCore::TMP::assign_direct_or_cast<typename std::remove_cvref<OutDeterminant_>::type>
				(
					out_determinant_,
					_calculate_determinant_from_row_echelon<calc_type>(in_out_, mult_, out_row_indices_except_0())
				);
			}
			else
			{
				static_assert
				(
					EmuCore::TMP::get_false<OutDeterminant_>(),
					"Unable to output determinant calculated during inversion of an EmuMath Matrix as the output determinant type cannot be assigned to directly or via conversion from the used calculation type."
				);
			}

			// Assign inverse result to output reference w/move semantics
			if constexpr (EmuCore::TMP::valid_assign_direct_or_cast<typename std::remove_cvref<InOutMatrix_>::type, decltype(std::move(result)), InOutMatrix_>())
			{
				EmuCore::TMP::assign_direct_or_cast<typename std::remove_cvref<InOutMatrix_>::type>(in_out_, std::move(result));
			}
			else
			{
				static_assert
				(
					EmuCore::TMP::get_false<InOutMatrix_>(),
					"Unable to finalise direct inverse assignment to an EmuMath Matrix determinant as the output type cannot be constructed or converted to from the used calculation type."
				);
			}
		}
		else
		{
			static_assert
			(
				EmuCore::TMP::get_false<InOutMatrix_>(),
				"Error attempting to perform direct inverse assignment to an EmuMath Matrix: The input Matrix is const-qualified, and cannot be assigned to."
			);
		}
	}

	template<class OutMatrix_, bool AllowReciprocalDivision_, EmuConcepts::EmuMatrix InMatrix_>
	[[nodiscard]] constexpr inline auto _matrix_inverse_gauss_jordan(InMatrix_&& in_)
		-> typename std::remove_cvref<OutMatrix_>::type
	{
		// Common types and constants
		using _in_mat_uq = typename std::remove_cvref<InMatrix_>::type;
		using _out_mat_uq = typename std::remove_cvref<OutMatrix_>::type;
		using _in_fp = typename _in_mat_uq::preferred_floating_point;
		using _out_fp = typename _out_mat_uq::preferred_floating_point;
		using calc_type = typename EmuCore::TMP::largest_floating_point<_in_fp, _out_fp, float>::type;
		constexpr std::size_t in_num_columns = _in_mat_uq::num_columns;
		constexpr std::size_t in_num_rows = _in_mat_uq::num_rows;
		constexpr bool in_column_major = _in_mat_uq::is_column_major;
		constexpr std::size_t out_num_columns = _out_mat_uq::num_columns;
		constexpr std::size_t out_num_rows = _out_mat_uq::num_rows;
		constexpr bool out_column_major = _out_mat_uq::is_column_major;

		using Adder_ = EmuCore::do_add<calc_type, calc_type>;
		using Multiplier_ = EmuCore::do_multiply<calc_type, calc_type>;
		using Divider_ = EmuCore::do_divide<calc_type, calc_type>;
		using Negator_ = EmuCore::do_negate<calc_type>;
		using out_row_indices = std::make_index_sequence<OutMatrix_::num_rows>;

		// Prepare common data shared between funcs
		auto in_calc_ = EmuMath::Matrix<in_num_columns, in_num_rows, calc_type, in_column_major>(std::forward<InMatrix_>(in_));
		auto out_ = EmuMath::Matrix<out_num_columns, out_num_rows, calc_type, out_column_major>::identity();
		Adder_ add_ = Adder_();
		Multiplier_ mult_ = Multiplier_();
		Divider_ div_ = Divider_();
		Negator_ negate_ = Negator_();

		// Eliminate rows and modify to set eliminated pivots to 1
		_calculate_matrix_inverse_gauss_jordan<AllowReciprocalDivision_>(out_, in_calc_, add_, mult_, div_, negate_, out_row_indices());
		_calculate_matrix_inverse_gauss_jordan_make_pivots_equal_to_1<AllowReciprocalDivision_>(out_, in_calc_, mult_, div_, out_row_indices());

		// Output inverse
		if constexpr (std::is_same_v<typename std::remove_cvref<decltype(out_)>::type, typename std::remove_cvref<OutMatrix_>::type>)
		{
			return out_;
		}
		else
		{
			if constexpr (EmuCore::TMP::valid_construct_or_cast<typename std::remove_cvref<OutMatrix_>::type, decltype(std::move(out_))>())
			{
				return EmuCore::TMP::construct_or_cast<typename std::remove_cvref<OutMatrix_>::type>(std::move(out_));
			}
			else
			{
				static_assert
				(
					EmuCore::TMP::get_false<OutMatrix_>(),
					"Unable to finalise calculation of an EmuMath Matrix inversion operation as the output Matrix cannot be constructed or converted to from the Matrix used for calculation."
				);
			}
		}
	}

	template<EmuConcepts::EmuMatrix OutMatrix_, bool AllowReciprocalDivision_, EmuConcepts::EmuMatrix InMatrix_, typename OutDeterminant_>
	[[nodiscard]] constexpr inline auto _matrix_inverse_gauss_jordan(InMatrix_&& in_, OutDeterminant_& out_determinant_)
		-> typename std::remove_cvref<OutMatrix_>::type
	{
		// Common types and constants
		using _in_mat_uq = typename std::remove_cvref<InMatrix_>::type;
		using _out_mat_uq = typename std::remove_cvref<OutMatrix_>::type;
		using _in_fp = typename _in_mat_uq::preferred_floating_point;
		using _out_fp = typename _out_mat_uq::preferred_floating_point;
		using calc_type = typename EmuCore::TMP::largest_floating_point<_in_fp, _out_fp, float>::type;
		constexpr std::size_t in_num_columns = _in_mat_uq::num_columns;
		constexpr std::size_t in_num_rows = _in_mat_uq::num_rows;
		constexpr bool in_column_major = _in_mat_uq::is_column_major;
		constexpr std::size_t out_num_columns = _out_mat_uq::num_columns;
		constexpr std::size_t out_num_rows = _out_mat_uq::num_rows;
		constexpr bool out_column_major = _out_mat_uq::is_column_major;

		using Adder_ = EmuCore::do_add<calc_type, calc_type>;
		using Multiplier_ = EmuCore::do_multiply<calc_type, calc_type>;
		using Divider_ = EmuCore::do_divide<calc_type, calc_type>;
		using Negator_ = EmuCore::do_negate<calc_type>;
		using out_row_indices = std::make_index_sequence<out_num_rows>;

		// Prepare common data shared between funcs
		auto in_calc_ = EmuMath::Matrix<in_num_columns, in_num_rows, calc_type, in_column_major>(std::forward<InMatrix_>(in_));
		auto out_ = EmuMath::Matrix<out_num_columns, out_num_rows, calc_type, out_column_major>::identity();
		Adder_ add_ = Adder_();
		Multiplier_ mult_ = Multiplier_();
		Divider_ div_ = Divider_();
		Negator_ negate_ = Negator_();

		// Eliminate rows and modify to set eliminated pivots to 1
		_calculate_matrix_inverse_gauss_jordan<AllowReciprocalDivision_>(out_, in_calc_, add_, mult_, div_, negate_, out_row_indices());
		_calculate_matrix_inverse_gauss_jordan_make_pivots_equal_to_1<AllowReciprocalDivision_>(out_, in_calc_, mult_, div_, out_row_indices());

		// Calculate and output determinant to reference
		if constexpr (EmuCore::TMP::valid_assign_direct_or_cast<typename std::remove_cvref<OutDeterminant_>::type, calc_type&&, OutDeterminant_>())
		{
			using out_row_indices_except_0 = EmuCore::TMP::make_index_sequence_excluding_0<out_num_rows>;
			EmuCore::TMP::assign_direct_or_cast<typename std::remove_cvref<OutDeterminant_>::type>
			(
				out_determinant_,
				_calculate_determinant_from_row_echelon<calc_type>(in_calc_, mult_, out_row_indices_except_0())
			);
		}
		else
		{
			static_assert
			(
				EmuCore::TMP::get_false<OutDeterminant_>(),
				"Unable to output determinant calculated during inversion of an EmuMath Matrix as the output determinant type cannot be assigned to directly or via conversion from the used calculation type."
			);
		}

		// Output inverse
		if constexpr (std::is_same_v<typename std::remove_cvref<decltype(out_)>::type, typename std::remove_cvref<OutMatrix_>::type>)
		{
			return out_;
		}
		else
		{
			if constexpr (EmuCore::TMP::valid_construct_or_cast<typename std::remove_cvref<OutMatrix_>::type, decltype(std::move(out_))>())
			{
				return EmuCore::TMP::construct_or_cast<typename std::remove_cvref<OutMatrix_>::type>(std::move(out_));
			}
			else
			{
				static_assert
				(
					EmuCore::TMP::get_false<OutMatrix_>(),
					"Unable to finalise calculation of an EmuMath Matrix inversion operation as the output Matrix cannot be constructed or converted to from the Matrix used for calculation."
				);
			}
		}
	}

	template<class OutScalar_, bool AllowReciprocalDivision_, EmuConcepts::EmuMatrix InMatrix_>
	[[nodiscard]] constexpr inline auto _matrix_determinant_gauss_jordan(InMatrix_&& in_)
		-> typename std::remove_cvref<OutScalar_>::type
	{
		// Common types and constants
		using _in_mat_uq = typename std::remove_cvref<InMatrix_>::type;
		constexpr std::size_t num_columns = _in_mat_uq::num_columns;
		constexpr std::size_t num_rows = _in_mat_uq::num_rows;
		constexpr bool is_column_major = _in_mat_uq::is_column_major;

		using calc_type = typename EmuCore::TMP::largest_floating_point<typename std::remove_cvref<OutScalar_>::type, typename _in_mat_uq::preferred_floating_point, float>::type;
		using Adder_ = EmuCore::do_add<calc_type, calc_type>;
		using Multiplier_ = EmuCore::do_multiply<calc_type, calc_type>;
		using Divider_ = EmuCore::do_divide<calc_type, calc_type>;
		using Negator_ = EmuCore::do_negate<calc_type>;

		// Prepare common data shared between funcs
		auto in_calc_ = EmuMath::Matrix<num_columns, num_rows, calc_type, is_column_major>(std::forward<InMatrix_>(in_));
		auto out_ = EmuMath::Matrix<num_columns, num_rows, calc_type, is_column_major>::identity();
		Adder_ add_ = Adder_();
		Multiplier_ mult_ = Multiplier_();
		Divider_ div_ = Divider_();
		Negator_ negate_ = Negator_();

		// Eliminate rows and modify to set eliminated pivots to 1
		using out_row_indices = std::make_index_sequence<num_rows>;
		_calculate_matrix_inverse_gauss_jordan(out_, in_calc_, add_, mult_, div_, negate_, out_row_indices());
		_calculate_matrix_inverse_gauss_jordan_make_pivots_equal_to_1<AllowReciprocalDivision_>(out_, in_calc_, mult_, div_, out_row_indices());

		// Calculate determinant from result and output
		if constexpr (EmuCore::TMP::valid_construct_or_cast<typename std::remove_cvref<OutScalar_>::type, calc_type&&>())
		{
			using out_row_indices_except_0 = EmuCore::TMP::make_index_sequence_excluding_0<num_rows>;
			return EmuCore::TMP::construct_or_cast<typename std::remove_cvref<OutScalar_>::type>
			(
				_calculate_determinant_from_row_echelon<calc_type>(in_calc_, mult_, out_row_indices_except_0())
			);
		}
		else
		{
			static_assert
			(
				EmuCore::TMP::get_false<OutScalar_>(),
				"Unable to finalise calculation of an EmuMath Matrix determinant as the output type cannot be constructed or converted to from the used calculation type."
			);
		}
	}
#pragma endregion
}

#endif
