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

#pragma region MATRIX_MUL_MATRIX_ASSIGN
	template
	<
		std::size_t OutColumn_, std::size_t OutRow_,
		std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, bool OutColumnMajor_,
		std::size_t RhsNumColumns_, std::size_t RhsNumRows_, typename RhsT_, bool RhsColumnMajor_,
		std::size_t LhsNumColumns_, std::size_t LhsNumRows_, typename LhsT_, bool LhsColumnMajor_,
		std::size_t...DpIndices_
	>
	constexpr inline void _matrix_std_multiply_assign_index_mat_mat
	(
		EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>& out_matrix_,
		const EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>& lhs_matrix_,
		const EmuMath::Matrix<RhsNumColumns_, RhsNumRows_, RhsT_, RhsColumnMajor_>& rhs_matrix_
	)
	{
		if constexpr (OutColumn_ < OutNumColumns_ && OutRow_ < OutNumRows_)
		{
			using out_get_result = decltype(_matrix_get<OutColumn_, OutRow_>(out_matrix_));
			using out_value_uq = typename EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>::value_type_uq;

			if constexpr(OutColumn_ < RhsNumColumns_ && OutRow_ < LhsNumRows_)
			{
				using dp_result = decltype((_matrix_std_multiply_mat_mat_dp_mult<OutColumn_, OutRow_, DpIndices_>(lhs_matrix_, rhs_matrix_) + ...));
				if constexpr (EmuCore::TMP::valid_assign_direct_or_cast<out_value_uq, dp_result, out_get_result>())
				{
					EmuCore::TMP::assign_direct_or_cast<out_value_uq>
					(
						_matrix_get<OutColumn_, OutRow_>(out_matrix_),
						(_matrix_std_multiply_mat_mat_dp_mult<OutColumn_, OutRow_, DpIndices_>(lhs_matrix_, rhs_matrix_) + ...)
					);
				}
				else
				{
					static_assert
					(
						EmuCore::TMP::get_false<OutT_>(),
						"Attempted to standard multiply-assign two EmuMath Matrices, but the output Matrix could not have an element assigned via at least one of the resulting dot products."
					);
				}
			}
			else
			{
				// DP will be 0 because at least one of the vectors (either lhs row or rhs column) is implied 0
				using implied_zero_type = decltype(out_matrix_.get_implied_zero());
				if constexpr (EmuCore::TMP::valid_assign_direct_or_cast<out_value_uq, implied_zero_type, out_get_result>())
				{
					EmuCore::TMP::assign_direct_or_cast<out_value_uq>
					(
						_matrix_get<OutColumn_, OutRow_>(out_matrix_),
						out_matrix_.get_implied_zero()
					);
				}
				else
				{
					static_assert
					(
						EmuCore::TMP::get_false<OutT_>(),
						"Attempted to standard multiply-assign two EmuMath Matrices, but the output Matrix could not have an element assigned via its implied-zero in an index that would result in an implied-zero left-hand row or implied-zero right-hand column."
					);
				}
			}
		}
	}

	template
	<
		std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, bool OutColumnMajor_,
		std::size_t RhsNumColumns_, std::size_t RhsNumRows_, typename RhsT_, bool RhsColumnMajor_,
		std::size_t LhsNumColumns_, std::size_t LhsNumRows_, typename LhsT_, bool LhsColumnMajor_,
		std::size_t...OutColumnIndices_, std::size_t...OutRowIndices_, std::size_t...DpIndices_
	>
	constexpr inline void _matrix_std_multiply_assign_mat_mat
	(
		std::index_sequence<OutColumnIndices_...> out_column_indices_,
		std::index_sequence<OutRowIndices_...> out_row_indices_,
		std::index_sequence<DpIndices_...> dp_indices_,
		EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>& out_matrix_,
		const EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>& lhs_matrix_,
		const EmuMath::Matrix<RhsNumColumns_, RhsNumRows_, RhsT_, RhsColumnMajor_>& rhs_matrix_
	)
	{
		if constexpr (LhsNumColumns_ == RhsNumRows_)
		{
			(
				_matrix_std_multiply_assign_index_mat_mat
				<
					OutColumnIndices_, OutRowIndices_,
					OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_,
					RhsNumColumns_, RhsNumRows_, RhsT_, RhsColumnMajor_,
					LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_,
					DpIndices_...
				>(out_matrix_, lhs_matrix_, rhs_matrix_), ...
			);
		}
		else
		{
			static_assert
			(
				EmuCore::TMP::get_false<std::size_t, RhsNumRows_>(),
				"Attempted to standard multiply-assign two EmuMath Matrices, but the right-hand Matrix's number of rows is not equal to the left-hand Matrix's number of columns."
			);
		}
	}

	template
	<
		bool ColumnMajorOrder_, std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, bool OutColumnMajor_,
		std::size_t RhsNumColumns_, std::size_t RhsNumRows_, typename RhsT_, bool RhsColumnMajor_,
		std::size_t LhsNumColumns_, std::size_t LhsNumRows_, typename LhsT_, bool LhsColumnMajor_
	>
	constexpr inline void _matrix_std_multiply_assign_mat_mat
	(
		EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>& out_matrix_,
		const EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>& lhs_matrix_,
		const EmuMath::Matrix<RhsNumColumns_, RhsNumRows_, RhsT_, RhsColumnMajor_>& rhs_matrix_
	)
	{
		using out_matrix = EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>;
		using out_indices = EmuMath::TMP::make_full_matrix_index_sequences<out_matrix>;
		using out_column_indices = typename out_indices::column_index_sequence;
		using out_row_indices = typename out_indices::row_index_sequence;
		using dp_indices = std::make_index_sequence<LhsNumRows_>;
		_matrix_std_multiply_assign_mat_mat(out_column_indices(), out_row_indices(), dp_indices(), out_matrix_, lhs_matrix_, rhs_matrix_);
	}

	template
	<
		bool ColumnMajorOrder_, std::size_t RhsNumColumns_, std::size_t RhsNumRows_, typename RhsT_, bool RhsColumnMajor_,
		std::size_t LhsNumColumns_, std::size_t LhsNumRows_, typename LhsT_, bool LhsColumnMajor_
	>
	constexpr inline void _matrix_std_multiply_assign_mat_mat
	(
		EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>& lhs_matrix_,
		const EmuMath::Matrix<RhsNumColumns_, RhsNumRows_, RhsT_, RhsColumnMajor_>& rhs_matrix_
	)
	{
		using lhs_mat_type = EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>;
		using lhs_copy_type_out_major = EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, typename lhs_mat_type::value_type_uq, ColumnMajorOrder_>;

		// A copy of lhs Matrix is needed to produce correct results whilst outputting said results to it
		// --- Prioritise accessed major-order to improve chances of cache locality
		if constexpr (std::is_constructible_v<lhs_copy_type_out_major, lhs_mat_type&>)
		{
			_matrix_std_multiply_assign_mat_mat<ColumnMajorOrder_>(lhs_matrix_, lhs_copy_type_out_major(lhs_matrix_), rhs_matrix_);
		}
		else
		{
			using lhs_copy_type_matching_major = EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, typename lhs_mat_type::value_type_uq, LhsColumnMajor_>;
			if constexpr (std::is_constructible_v<lhs_copy_type_matching_major, lhs_mat_type&>)
			{
				_matrix_std_multiply_assign_mat_mat<ColumnMajorOrder_>(lhs_matrix_, lhs_copy_type_matching_major(lhs_matrix_), rhs_matrix_);
			}
			else
			{
				static_assert
				(
					EmuCore::TMP::get_false<lhs_mat_type>(),
					"Attempted to standard multiply-assign two EmuMath Matrices, but the left-hand Matrix requires a copy to be output to while maintaining correct results, and the copy cannot be successfully constructed."
				);
			}
		}
	}
#pragma endregion

#pragma region MATRIX_MUL_VECTOR
	template<std::size_t DpIndex_, std::size_t OtherIndex_, bool VectorLhs_, class LhsMatrix_, class RhsVector_>
	[[nodiscard]] constexpr inline auto _matrix_std_multiply_vector_calculate_dp_mult(const LhsMatrix_& matrix_, const RhsVector_& vector_)
	{
		constexpr std::size_t column_index = VectorLhs_ ? OtherIndex_ : DpIndex_;
		constexpr std::size_t row_index = VectorLhs_ ? DpIndex_ : OtherIndex_;

		if constexpr (DpIndex_ < EmuCore::TMP::remove_ref_cv_t<RhsVector_>::size)
		{
			using lhs_get_uq = EmuCore::TMP::remove_ref_cv_t<decltype(matrix_.template at<column_index, row_index>())>;
			using rhs_get_uq = EmuCore::TMP::remove_ref_cv_t<decltype(vector_.template at<DpIndex_>())>;
			return EmuCore::do_multiply<lhs_get_uq, rhs_get_uq>()
			(
				matrix_.template at<column_index, row_index>(),
				vector_.template at<DpIndex_>()
			);
		}
		else
		{
			return matrix_.template at<column_index, row_index>();
		}
	}

	template<std::size_t Index_, class OutVector_, class LhsMatrix_, class RhsVector_, std::size_t...DpIndices_>
	[[nodiscard]] constexpr inline typename decltype(auto) _matrix_std_multiply_mat_vector_dp_for_index
	(
		const LhsMatrix_& lhs_matrix_,
		const RhsVector_& rhs_vector_
	)
	{
		return EmuCore::TMP::construct_or_cast<typename OutVector_::stored_type>
		(
			(_matrix_std_multiply_vector_calculate_dp_mult<DpIndices_, Index_, false>(lhs_matrix_, rhs_vector_) + ...)
		);
	}

	template<std::size_t Index_, class LhsMatrix_, class RhsVector_, std::size_t...DpIndices_>
	[[nodiscard]] constexpr inline decltype(auto) _matrix_std_multiply_mat_vector_dp_for_assigned_index
	(
		const LhsMatrix_& lhs_matrix_,
		const RhsVector_& rhs_vector_
	)
	{
		return
		(
			(_matrix_std_multiply_vector_calculate_dp_mult<DpIndices_, Index_, false>(lhs_matrix_, rhs_vector_) + ...)
		);
	}

	template<std::size_t Index_, EmuMath::TMP::EmuVector OutVector_, EmuMath::TMP::EmuVector LhsVector_, EmuMath::TMP::EmuMatrix RhsMatrix_, std::size_t...DpIndices_>
	[[nodiscard]] constexpr inline typename decltype(auto) _matrix_std_multiply_vector_mat_dp_for_index
	(
		const LhsVector_& lhs_vector_,
		const RhsMatrix_& rhs_matrix_
	)
	{
		return EmuCore::TMP::construct_or_cast<typename OutVector_::stored_type>
		(
			(_matrix_std_multiply_vector_calculate_dp_mult<DpIndices_, Index_, true>(rhs_matrix_, lhs_vector_) + ...)
		);
	}

	template<std::size_t Index_, EmuMath::TMP::EmuVector LhsVector_, EmuMath::TMP::EmuMatrix RhsMatrix_, std::size_t...DpIndices_>
	[[nodiscard]] constexpr inline decltype(auto) _matrix_std_multiply_vector_mat_dp_for_assigned_index
	(
		const LhsVector_& lhs_vector_,
		const RhsMatrix_& rhs_matrix_
	)
	{
		return
		(
			(_matrix_std_multiply_vector_calculate_dp_mult<DpIndices_, Index_, true>(rhs_matrix_, lhs_vector_) + ...)
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
					"Attempted to standard-multiply an EmuMath Matrix and EmuMath Vector (MAT * VEC), but the provided output Vector cannot be constructed from one stored_type per contained element."
				);
			}
		}
		else
		{
			static_assert
			(
				EmuCore::TMP::get_false<std::size_t, RhsSize_>(),
				"Attempted to standard-multiply an EmuMath Matrix and EmuMath Vector (MAT * VEC), but the provided Vector has a number of elements not equal to the Matrix's number of rows, or its number of rows - 1."
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
		return _matrix_std_multiply_mat_vector<EmuMath::Vector<RhsSize_, OutT_>>(out_indices(), dp_indices(), lhs_matrix_, rhs_vector_);
	}

	template<typename OutT_, EmuMath::TMP::EmuMatrix Matrix_, std::size_t LhsSize_, typename LhsT_, std::size_t...OutIndices_, std::size_t...DpIndices_>
	[[nodiscard]] constexpr inline auto _matrix_std_multiply_vector_mat
	(
		const EmuMath::Vector<LhsSize_, LhsT_>& lhs_vector_,
		const Matrix_& rhs_matrix_,
		std::index_sequence<OutIndices_...> out_indices_,
		std::index_sequence<DpIndices_...> dp_indices_
	)
	{
		using rhs_uq = typename EmuCore::TMP::remove_ref_cv<Matrix_>::type;
		constexpr std::size_t rhs_num_columns = rhs_uq::num_columns;

		if constexpr (LhsSize_ == rhs_num_columns || (LhsSize_ + 1) == rhs_num_columns)
		{
			using lhs_vector_type = EmuMath::Vector<LhsSize_, LhsT_>;
			constexpr bool is_constructible_ = std::is_constructible_v
			<
				EmuMath::Vector<LhsSize_, LhsT_>,
				decltype
				(
					_matrix_std_multiply_vector_mat_dp_for_index<OutIndices_, EmuMath::Vector<LhsSize_, OutT_>, lhs_vector_type, rhs_uq, DpIndices_...>
					(
						lhs_vector_,
						rhs_matrix_
					)
				)...
			>;
			if constexpr (is_constructible_)
			{
				return EmuMath::Vector<LhsSize_, OutT_>
				(
					_matrix_std_multiply_vector_mat_dp_for_index<OutIndices_, EmuMath::Vector<LhsSize_, OutT_>, lhs_vector_type, rhs_uq, DpIndices_...>
					(
						lhs_vector_,
						rhs_matrix_
					)...
				);
			}
			else
			{
				static_assert
				(
					EmuCore::TMP::get_false<EmuMath::Vector<LhsSize_, OutT_>>(),
					"Attempted to standard-multiply an EmuMath Vector and EmuMath Matrix¬ (VEC * MAT), but the provided output Vector cannot be constructed from one stored_type per contained element."
				);
			}
		}
		else
		{
			static_assert
			(
				EmuCore::TMP::get_false<std::size_t, LhsSize_>(),
				"Attempted to standard-multiply an EmuMath Vector and EmuMath Matrix (VEC * MAT), but the provided Vector has a number of elements not equal to the Matrix's number of columns, or its number of columns - 1."
			);
		}
	}

	template<typename OutT_, EmuMath::TMP::EmuMatrix Matrix_, std::size_t LhsSize_, typename LhsT_>
	[[nodiscard]] constexpr inline auto _matrix_std_multiply_vector_mat(const EmuMath::Vector<LhsSize_, LhsT_>& lhs_vector_, Matrix_&& rhs_matrix_)
	{
		using mat_uq = typename EmuCore::TMP::remove_ref_cv<Matrix_>::type;
		using out_indices = std::make_index_sequence<LhsSize_>;
		using dp_indices = std::make_index_sequence<mat_uq::num_columns>;
		return _matrix_std_multiply_vector_mat<OutT_>
		(
			lhs_vector_,
			EmuCore::TMP::const_lval_ref_cast<Matrix_>(std::forward<Matrix_>(rhs_matrix_)),
			out_indices(),
			dp_indices()
		);
	}
#pragma endregion

#pragma region MATRIX_MUL_VECTOR_ASSIGN
	template<std::size_t RhsSize_, typename RhsT_, std::size_t LhsNumColumns_, std::size_t LhsNumRows_, typename LhsT_, bool LhsColumnMajor_, bool DoAssertions_>
	[[nodiscard]] constexpr inline bool _matrix_std_multiply_assign_mat_vector_is_valid()
	{
		if constexpr (RhsSize_ == LhsNumRows_ || (RhsSize_ + 1) == LhsNumRows_)
		{
			return true;
		}
		else
		{
			static_assert(!DoAssertions_, "Attempted to standard multiply-assign an EmuMath Matrix and EmuMath Vector, but the provided Vector has a number of elements not equal to the Matrix's number of rows, or its number of rows - 1.");
			return false;
		}
	}

	template
	<
		std::size_t OutIndex_,
		std::size_t OutSize_,
		typename OutT_,
		std::size_t RhsSize_,
		typename RhsT_,
		std::size_t LhsNumColumns_,
		std::size_t LhsNumRows_,
		typename LhsT_,
		bool LhsColumnMajor_,
		std::size_t...DpIndices_
	>
	constexpr inline void _matrix_std_multiply_assign_index_mat_vector
	(
		EmuMath::Vector<OutSize_, OutT_>& out_vector_,
		const EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>& lhs_matrix_,
		const EmuMath::Vector<RhsSize_, RhsT_>& rhs_vector_
	)
	{
		if constexpr (OutIndex_ < OutSize_)
		{
			using lhs_matrix_type = EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>;
			using rhs_vector_type = EmuMath::Vector<RhsSize_, RhsT_>;
			using out_get_result = decltype(out_vector_.template at<OutIndex_>());
			using dp_result = decltype
			(
				_matrix_std_multiply_mat_vector_dp_for_assigned_index<OutIndex_, lhs_matrix_type, rhs_vector_type, DpIndices_...>(lhs_matrix_, rhs_vector_)
			);
			using out_value_uq = typename EmuMath::Vector<OutSize_, OutT_>::value_type_uq;

			if constexpr (EmuCore::TMP::valid_assign_direct_or_cast<out_value_uq, dp_result, out_get_result>())
			{
				EmuCore::TMP::assign_direct_or_cast<out_value_uq>
				(
					out_vector_.template at<OutIndex_>(),
					_matrix_std_multiply_mat_vector_dp_for_assigned_index<OutIndex_, lhs_matrix_type, rhs_vector_type, DpIndices_...>(lhs_matrix_, rhs_vector_)
				);
			}
			else
			{
				static_assert
				(
					EmuCore::TMP::get_false<OutT_>(),
					"Attempted to standard multiply-assign an EmuMath Matrix and EmuMath Vector, but the provided output Vector could not have one of its indices assigned from the result from at least one iteration's dot product."
				);
			}
		}
	}

	template
	<
		std::size_t OutSize_,
		typename OutT_,
		std::size_t RhsSize_,
		typename RhsT_,
		std::size_t LhsNumColumns_,
		std::size_t LhsNumRows_,
		typename LhsT_,
		bool LhsColumnMajor_,
		std::size_t...OutIndices_,
		std::size_t...DpIndices_
	>
	constexpr inline void _matrix_std_multiply_assign_mat_vector
	(
		std::index_sequence<OutIndices_...> out_indices_,
		std::index_sequence<DpIndices_...> dp_indices_,
		EmuMath::Vector<OutSize_, OutT_>& out_vector_,
		const EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>& lhs_matrix_,
		const EmuMath::Vector<RhsSize_, RhsT_>& rhs_vector_
	)
	{
		if constexpr (RhsSize_ == LhsNumRows_ || (RhsSize_ + 1) == LhsNumRows_)
		{
			(
				_matrix_std_multiply_assign_index_mat_vector<OutIndices_, OutSize_, OutT_, RhsSize_, RhsT_, LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_, DpIndices_...>
				(
					out_vector_,
					lhs_matrix_,
					rhs_vector_
				), ...
			);
		}
		else
		{
			static_assert
			(
				!EmuCore::TMP::get_false<std::size_t, RhsSize_>(),
				"Attempted to standard multiply-assign an EmuMath Matrix and EmuMath Vector, but the provided Vector has a number of elements not equal to the Matrix's number of rows, or its number of rows - 1."
			);
		}
	}

	template<std::size_t OutSize_, typename OutT_, std::size_t RhsSize_, typename RhsT_, std::size_t LhsNumColumns_, std::size_t LhsNumRows_, typename LhsT_, bool LhsColumnMajor_>
	constexpr inline void _matrix_std_multiply_assign_mat_vector
	(
		EmuMath::Vector<OutSize_, OutT_>& out_vector_,
		const EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>& lhs_matrix_,
		const EmuMath::Vector<RhsSize_, RhsT_>& rhs_vector_
	)
	{
		using out_indices = std::make_index_sequence<(OutSize_ < RhsSize_) ? OutSize_ : RhsSize_>;
		using dp_indices = std::make_index_sequence<LhsNumRows_>;
		_matrix_std_multiply_assign_mat_vector(out_indices(), dp_indices(), out_vector_, lhs_matrix_, rhs_vector_);
	}

	template<std::size_t RhsSize_, typename RhsT_, std::size_t LhsNumColumns_, std::size_t LhsNumRows_, typename LhsT_, bool LhsColumnMajor_>
	constexpr inline void _matrix_std_multiply_assign_mat_vector
	(
		const EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>& lhs_matrix_,
		EmuMath::Vector<RhsSize_, RhsT_>& rhs_vector_
	)
	{
		if constexpr (RhsSize_ == 1)
		{
			// No need for a temp copy
			_matrix_std_multiply_assign_mat_vector(rhs_vector_, lhs_matrix_, rhs_vector_);
		}
		else
		{
			// Need a copy as referenced data which will be modified will need to be used multiple times
			using rhs_copy_type = EmuMath::Vector<RhsSize_, typename EmuMath::Vector<RhsSize_, RhsT_>::value_type_uq>;
			if constexpr (std::is_constructible_v<rhs_copy_type, EmuMath::Vector<RhsSize_, RhsT_>&>)
			{
				_matrix_std_multiply_assign_mat_vector(rhs_vector_, lhs_matrix_, rhs_copy_type(rhs_vector_));
			}
			else
			{
				static_assert
				(
					EmuCore::TMP::get_false<rhs_copy_type>(),
					"Attempted to perform a standard Matrix multiply-assign with an EmuMath Matrix and EmuMath Vector, with assignment going to the Vector. However, the provided Vector type could not successfully be copied to retain data for each assignment."
				);
			}
		}
	}





	

	template
	<
		std::size_t OutIndex_, std::size_t OutSize_, typename OutT_, std::size_t LhsSize_, typename LhsT_,
		EmuMath::TMP::EmuMatrix Matrix_, std::size_t...DpIndices_
	>
	constexpr inline void _matrix_std_multiply_assign_index_vector_mat
	(
		EmuMath::Vector<OutSize_, OutT_>& out_vector_,
		const EmuMath::Vector<LhsSize_, LhsT_>& lhs_vector_,
		const Matrix_& rhs_matrix_
	)
	{
		if constexpr (OutIndex_ < OutSize_)
		{
			using lhs_uq = EmuMath::Vector<LhsSize_, LhsT_>;
			using rhs_uq = typename EmuCore::TMP::remove_ref_cv<Matrix_>::type;
			using out_get_result = decltype(out_vector_.template at<OutIndex_>());
			using dp_result = decltype
			(
				_matrix_std_multiply_vector_mat_dp_for_assigned_index<OutIndex_, lhs_uq, rhs_uq, DpIndices_...>(lhs_vector_, rhs_matrix_)
			);
			using out_value_uq = typename EmuMath::Vector<OutSize_, OutT_>::value_type_uq;

			if constexpr (EmuCore::TMP::valid_assign_direct_or_cast<out_value_uq, dp_result, out_get_result>())
			{
				EmuCore::TMP::assign_direct_or_cast<out_value_uq>
				(
					out_vector_.template at<OutIndex_>(),
					_matrix_std_multiply_vector_mat_dp_for_assigned_index<OutIndex_, lhs_uq, rhs_uq, DpIndices_...>(lhs_vector_, rhs_matrix_)
				);
			}
			else
			{
				static_assert
				(
					EmuCore::TMP::get_false<OutT_>(),
					"Attempted to standard multiply-assign an EmuMath Vector and EmuMath Matrix (VEC * MAT), but the provided output Vector could not have one of its indices assigned from the result from at least one iteration's dot product."
				);
			}
		}
	}

	template
	<
		std::size_t OutSize_, typename OutT_, std::size_t LhsSize_, typename LhsT_, EmuMath::TMP::EmuMatrix Matrix_,
		std::size_t...OutIndices_, std::size_t...DpIndices_
	>
	constexpr inline void _matrix_std_multiply_assign_vector_mat
	(
		std::index_sequence<OutIndices_...> out_indices_,
		std::index_sequence<DpIndices_...> dp_indices_,
		EmuMath::Vector<OutSize_, OutT_>& out_vector_,
		const EmuMath::Vector<LhsSize_, LhsT_>& lhs_vector_,
		const Matrix_& rhs_matrix_
	)
	{
		using mat_uq = typename EmuCore::TMP::remove_ref_cv<Matrix_>::type;
		if constexpr (LhsSize_ == mat_uq::num_columns || (LhsSize_ + 1) == mat_uq::num_columns)
		{
			(
				_matrix_std_multiply_assign_index_vector_mat<OutIndices_, OutSize_, OutT_, LhsSize_, LhsT_, Matrix_, DpIndices_...>
				(
					out_vector_,
					lhs_vector_,
					rhs_matrix_
				), ...
			);
		}
		else
		{
			static_assert
			(
				!EmuCore::TMP::get_false<std::size_t, LhsSize_>(),
				"Attempted to standard multiply-assign an EmuMath Vector and EmuMath Matrix (VEC * MAT), but the provided Vector has a number of elements not equal to the Matrix's number of columns, or its number of columns - 1."
			);
		}
	}

	template<std::size_t OutSize_, typename OutT_, std::size_t LhsSize_, typename LhsT_, EmuMath::TMP::EmuMatrix Matrix_>
	constexpr inline void _matrix_std_multiply_assign_vector_mat
	(
		EmuMath::Vector<OutSize_, OutT_>& out_vector_,
		const EmuMath::Vector<LhsSize_, LhsT_>& lhs_vector_,
		Matrix_&& rhs_matrix_
	)
	{
		using rhs_uq = typename EmuCore::TMP::remove_ref_cv<Matrix_>::type;
		using out_indices = std::make_index_sequence<OutSize_ < LhsSize_ ? OutSize_ : LhsSize_>;
		using dp_indices = std::make_index_sequence<rhs_uq::num_columns>;
		_matrix_std_multiply_assign_vector_mat(out_indices(), dp_indices(), out_vector_, lhs_vector_, rhs_matrix_);
	}

	template<std::size_t LhsSize_, typename LhsT_, EmuMath::TMP::EmuMatrix Matrix_>
	constexpr inline void _matrix_std_multiply_assign_vector_mat
	(
		EmuMath::Vector<LhsSize_, LhsT_>& lhs_vector_,
		Matrix_&& rhs_matrix_
	)
	{
		if constexpr (LhsSize_ == 1)
		{
			// No need for a temp copy
			_matrix_std_multiply_assign_vector_mat(lhs_vector_, std::forward<Matrix_>(rhs_matrix_), lhs_vector_);
		}
		else
		{
			// Need a copy as referenced data which will be modified will need to be used multiple times
			using lhs_copy_type = EmuMath::Vector<LhsSize_, typename EmuMath::Vector<LhsSize_, LhsT_>::value_type_uq>;
			if constexpr (std::is_constructible_v<lhs_copy_type, EmuMath::Vector<LhsSize_, LhsT_>&>)
			{
				_matrix_std_multiply_assign_vector_mat(lhs_vector_, lhs_copy_type(lhs_vector_), std::forward<Matrix_>(rhs_matrix_));
			}
			else
			{
				static_assert
				(
					EmuCore::TMP::get_false<lhs_copy_type>(),
					"Attempted to perform a standard Matrix multiply-assign with an EmuMath Vector and EmuMath Matrix (VEC * MAT), with assignment going to the Vector. However, the provided Vector type could not successfully be copied to retain data after each assignment."
				);
			}
		}
	}
#pragma endregion
}

#endif
