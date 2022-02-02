#ifndef EMU_MATH_MATRIX_SPECIAL_ARITHMETIC_H_INC_
#define EMU_MATH_MATRIX_SPECIAL_ARITHMETIC_H_INC_ 1

#include "_matrix_tmp.h"
#include "_matrix_underlying_get.h"
#include "_matrix_underlying_mutate.h"

namespace EmuMath::Helpers::_matrix_underlying
{
#pragma region MATRIX_MUL_MATRIX
	template
	<
		std::size_t ColumnIndex_, std::size_t RowIndex_, std::size_t DpIndex_,
		std::size_t LhsNumColumns_, std::size_t LhsNumRows_, typename LhsT_, bool LhsColumnMajor_,
		std::size_t RhsNumColumns_, std::size_t RhsNumRows_, typename RhsT_, bool RhsColumnMajor_
	>
	[[nodiscard]] constexpr inline typename auto _matrix_std_multiply_mat_mat_dp_mult
	(
		const EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>& lhs_matrix_,
		const EmuMath::Matrix<RhsNumColumns_, RhsNumRows_, RhsT_, RhsColumnMajor_>& rhs_matrix_
	)
	{
		using lhs_get_result_uq = EmuCore::TMP::remove_ref_cv_t<decltype(lhs_matrix_.template at<DpIndex_, RowIndex_>())>;
		using rhs_get_result_uq = EmuCore::TMP::remove_ref_cv_t<decltype(rhs_matrix_.template at<ColumnIndex_, DpIndex_>())>;
		return EmuCore::do_multiply<lhs_get_result_uq, rhs_get_result_uq>()
		(
			lhs_matrix_.template at<DpIndex_, RowIndex_>(),
			rhs_matrix_.template at<ColumnIndex_, DpIndex_>()
		);
	}

	template
	<
		std::size_t ColumnIndex_, std::size_t RowIndex_, class OutMatrix_,
		std::size_t LhsNumColumns_, std::size_t LhsNumRows_, typename LhsT_, bool LhsColumnMajor_,
		std::size_t RhsNumColumns_, std::size_t RhsNumRows_, typename RhsT_, bool RhsColumnMajor_,
		std::size_t...DpIndices_
	>
	[[nodiscard]] constexpr inline typename OutMatrix_::stored_type _matrix_std_multiply_mat_mat_for_index
	(
		std::index_sequence<DpIndices_...> dp_indices_,
		const EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>& lhs_matrix_,
		const EmuMath::Matrix<RhsNumColumns_, RhsNumRows_, RhsT_, RhsColumnMajor_>& rhs_matrix_
	)
	{
		return EmuCore::TMP::construct_or_cast<typename OutMatrix_::stored_type>
		(
			(_matrix_std_multiply_mat_mat_dp_mult<ColumnIndex_, RowIndex_, DpIndices_>(lhs_matrix_, rhs_matrix_) + ...)
		);
	}

	template
	<
		class OutMatrix_,
		std::size_t LhsNumColumns_, std::size_t LhsNumRows_, typename LhsT_, bool LhsColumnMajor_,
		std::size_t RhsNumColumns_, std::size_t RhsNumRows_, typename RhsT_, bool RhsColumnMajor_,
		std::size_t...OutColumnIndices_,
		std::size_t...OutRowIndices_,
		std::size_t...DpIndices_
	>
	[[nodiscard]] constexpr inline OutMatrix_ _matrix_std_multiply_mat_mat
	(
		std::index_sequence<OutColumnIndices_...> out_column_indices_,
		std::index_sequence<OutRowIndices_...> out_row_indices_,
		std::index_sequence<DpIndices_...> dp_indices_,
		const EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>& lhs_matrix_,
		const EmuMath::Matrix<RhsNumColumns_, RhsNumRows_, RhsT_, RhsColumnMajor_>& rhs_matrix_
	)
	{
		if constexpr (LhsNumColumns_ == RhsNumRows_)
		{
			using dp_index_sequence = decltype(dp_indices_);
			constexpr bool is_constructible_ = std::is_constructible_v
			<
				OutMatrix_,
				decltype(_matrix_std_multiply_mat_mat_for_index<OutColumnIndices_, OutRowIndices_, OutMatrix_>(dp_index_sequence(), lhs_matrix_, rhs_matrix_))...
			>;

			if constexpr (is_constructible_)
			{
				return OutMatrix_
				(
					_matrix_std_multiply_mat_mat_for_index<OutColumnIndices_, OutRowIndices_, OutMatrix_>(dp_index_sequence(), lhs_matrix_, rhs_matrix_)...
				);
			}
			else
			{
				static_assert
				(
					EmuCore::TMP::get_false<OutMatrix_>(),
					"Attempted to standard-multiply two EmuMath Matrices, but the provided output Matrix cannot be constructed from one of its stored_type per element."
				);
			}
		}
		else
		{
			static_assert
			(
				EmuCore::TMP::get_false<std::size_t, RhsNumRows_>(),
				"Attempted to standard-multiply two EmuMath Matrices, but the right-hand Matrix's number of rows is not equal to the left-hand Matrix's number of columns."
			);
		}
	}

	template
	<
		typename OutT_, bool OutColumnMajor_,
		std::size_t LhsNumColumns_, std::size_t LhsNumRows_, typename LhsT_, bool LhsColumnMajor_,
		std::size_t RhsNumColumns_, std::size_t RhsNumRows_, typename RhsT_, bool RhsColumnMajor_
	>
	[[nodiscard]] constexpr inline EmuMath::Matrix<RhsNumColumns_, LhsNumRows_, OutT_, OutColumnMajor_> _matrix_std_multiply_mat_mat
	(
		const EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>& lhs_matrix_,
		const EmuMath::Matrix<RhsNumColumns_, RhsNumRows_, RhsT_, RhsColumnMajor_>& rhs_matrix_
	)
	{
		using out_matrix = EmuMath::Matrix<RhsNumColumns_, LhsNumRows_, OutT_, OutColumnMajor_>;
		using out_indices = EmuMath::TMP::make_full_matrix_index_sequences<out_matrix>;
		using out_column_indices = typename out_indices::column_index_sequence;
		using out_row_indices = typename out_indices::row_index_sequence;
		using dp_indices = std::make_index_sequence<LhsNumRows_>;
		return _matrix_std_multiply_mat_mat<out_matrix>(out_column_indices(), out_row_indices(), dp_indices(), lhs_matrix_, rhs_matrix_);
	}
#pragma endregion

#pragma region MATRIX_MUL_VECTOR
	template<std::size_t DpIndex_, class LhsRow_, class RhsVector_>
	[[nodiscard]] constexpr inline auto _matrix_std_multiply_vector_calculate_dp_mult(const LhsRow_& lhs_row_, const RhsVector_& rhs_vector_)
	{
		if constexpr (DpIndex_ < EmuCore::TMP::remove_ref_cv_t<RhsVector_>::size)
		{
			using lhs_get_uq = EmuCore::TMP::remove_ref_cv_t<decltype(lhs_row_.template at<DpIndex_>())>;
			using rhs_get_uq = EmuCore::TMP::remove_ref_cv_t<decltype(rhs_vector_.template at<DpIndex_>())>;
			return EmuCore::do_multiply<lhs_get_uq, rhs_get_uq>()
			(
				lhs_row_.template at<DpIndex_>(),
				rhs_vector_.template at<DpIndex_>()
			);
		}
		else
		{
			return lhs_row_.template at<DpIndex_>();
		}
	}

	template<std::size_t Index_, class OutVector_, class LhsMatrix_, class RhsVector_, std::size_t...DpIndices_>
	[[nodiscard]] constexpr inline typename OutVector_::stored_type _matrix_std_multiply_mat_vector_dp_for_index
	(
		const LhsMatrix_& lhs_matrix_,
		const RhsVector_& rhs_vector_
	)
	{
		using lhs_row_ref_type = typename LhsMatrix_::row_get_const_ref_type;
		lhs_row_ref_type lhs_row_ref_ = lhs_matrix_.template RowAt<Index_>();
		return EmuCore::TMP::construct_or_cast<typename OutVector_::stored_type>
		(
			(_matrix_std_multiply_vector_calculate_dp_mult<DpIndices_, lhs_row_ref_type, RhsVector_>(lhs_row_ref_, rhs_vector_) + ...)
		);
	}

	template
	<
		class OutVector_,
		std::size_t LhsNumColumns_,
		std::size_t LhsNumRows_,
		typename LhsT_,
		bool LhsColumnMajor_,
		std::size_t RhsSize_,
		typename RhsT_,
		std::size_t...OutIndices_,
		std::size_t...DpIndices_
	>
	[[nodiscard]] constexpr inline OutVector_ _matrix_std_multiply_mat_vector
	(
		std::index_sequence<OutIndices_...> out_indices_,
		std::index_sequence<DpIndices_...> dp_indices_,
		const EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>& lhs_matrix_,
		const EmuMath::Vector<RhsSize_, RhsT_> rhs_vector_
	)
	{
		if constexpr (RhsSize_ == LhsNumRows_ || (RhsSize_ + 1) == LhsNumRows_)
		{
			using lhs_matrix_type = EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>;
			using rhs_vector_type = EmuMath::Vector<RhsSize_, RhsT_>;
			constexpr bool is_constructible_ = std::is_constructible_v
			<
				OutVector_,
				decltype(_matrix_std_multiply_mat_vector_dp_for_index<OutIndices_, OutVector_, lhs_matrix_type, rhs_vector_type, DpIndices_...>(lhs_matrix_, rhs_vector_))...
			>;
			if constexpr (is_constructible_)
			{
				return OutVector_
				(
					_matrix_std_multiply_mat_vector_dp_for_index<OutIndices_, OutVector_, lhs_matrix_type, rhs_vector_type, DpIndices_...>(lhs_matrix_, rhs_vector_)...
				);
			}
			else
			{
				static_assert
				(
					EmuCore::TMP::get_false<OutVector_>(),
					"Attempted to standard-multiply an EmuMath Matrix and EmuMath Vector, but the provided output Vector cannot be constructed from one stored_type per contained element."
				);
			}
		}
		else
		{
			static_assert
			(
				EmuCore::TMP::get_false<std::size_t, RhsSize_>(),
				"Attempted to standard-multiply an EmuMath Matrix and EmuMath Vector, but the provided Vector has a number of elements not equal to the Matrix's number of rows, or its number of rows - 1."
			);
		}
	}

	template<typename OutT_, std::size_t LhsNumColumns_, std::size_t LhsNumRows_, typename LhsT_, bool LhsColumnMajor_, std::size_t RhsSize_, typename RhsT_>
	[[nodiscard]] constexpr inline EmuMath::Vector<RhsSize_, OutT_> _matrix_std_multiply_mat_vector
	(
		const EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>& lhs_matrix_,
		const EmuMath::Vector<RhsSize_, RhsT_>& rhs_vector_
	)
	{
		using out_indices = std::make_index_sequence<RhsSize_>;
		using dp_indices = std::make_index_sequence<LhsNumRows_>;
		using out_vector = EmuMath::Vector<RhsSize_, OutT_>;
		return _matrix_std_multiply_mat_vector<out_vector>(out_indices(), dp_indices(), lhs_matrix_, rhs_vector_);
	}
#pragma endregion
}

#endif
