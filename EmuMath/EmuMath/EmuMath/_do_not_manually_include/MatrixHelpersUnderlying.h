#ifndef EMU_MATH_MATRIX_HELPERS_UNDERLYING_H_INC_
#define EMU_MATH_MATRIX_HELPERS_UNDERLYING_H_INC_

#include "EmuMatrixTMPHelpers.h"
#include "../Vectors.h"

namespace EmuMath
{
	template<std::size_t NumColumns_, std::size_t NumRows_, typename T_>
	struct MatrixCM;
}

/// <summary> Underlying functions used by EmuMath::Helper functions for matrices. These should not be used directly. </summary>
namespace EmuMath::Helpers::_underlying_matrix_funcs
{
#pragma region CHECKS
	template<std::size_t Column_, std::size_t Row_, class Matrix_>
	constexpr inline bool _matrix_get_validity_check()
	{
		if constexpr (EmuMath::TMPHelpers::is_emu_matrix_v<Matrix_>)
		{
			if constexpr (Column_ < Matrix_::num_columns)
			{
				if constexpr (Row_ < Matrix_::num_rows)
				{
					return true;
				}
				else
				{
					static_assert(false, "Attempted to get a matrix element via MatrixGet via an invalid row index.");
					return false;
				}
			}
			else
			{
				static_assert(false, "Attempted to get a matrix element via MatrixGet via an invalid column index.");
				return false;
			}
		}
		else
		{
			static_assert(false, "Attempted to get a matrix element via MatrixGet, but passed a non-EmuMath-matrix type.");
			return false;
		}
	}
	template<std::size_t Index_, class Matrix_>
	constexpr inline bool _matrix_get_major_validity_check()
	{
		if constexpr (EmuMath::TMPHelpers::is_emu_matrix_v<Matrix_>)
		{
			if constexpr (Index_ < Matrix_::num_majors)
			{
				return true;
			}
			else
			{
				static_assert(false, "Attempted to get a major matrix element via MatrixGet, using an invalid major index.");
				return false;
			}
		}
		else
		{
			static_assert(false, "Attempted to get a major matrix element via MatrixGet, but passed a non-EmuMath-matrix type.");
			return false;
		}
	}
	template<class Matrix_>
	constexpr inline bool _matrix_get_basic_validity_check()
	{
		if constexpr (EmuMath::TMPHelpers::is_emu_matrix_v<Matrix_>)
		{
			return true;
		}
		else
		{
			static_assert(false, "Attempted to get a matrix element via MatrixGet, but passed a non-EmuMath-matrix type.");
			return false;
		}
	}
#pragma endregion

#pragma region BASIC_ARITHMETIC
	template<std::size_t Row_, class ArithmeticFunc_, std::size_t num_columns, std::size_t num_rows, typename value_type, typename Rhs_>
	constexpr inline void _execute_basic_matrix_arithmetic_on_contained_scalars_until_complete
	(
		typename EmuMath::MatrixCM<num_columns, num_rows, value_type>::column_type& outColumn_,
		const typename EmuMath::MatrixCM<num_columns, num_rows, value_type>::column_type& lhsColumn,
		const Rhs_& rhs,
		ArithmeticFunc_& func_
	)
	{
		if constexpr (Row_ < num_rows)
		{
			if constexpr (std::is_arithmetic_v<std::remove_reference_t<Rhs_>>)
			{
				outColumn_[Row_] = func_(lhsColumn[Row_], rhs);
				_execute_basic_matrix_arithmetic_on_contained_scalars_until_complete<Row_ + 1, ArithmeticFunc_, num_columns, num_rows, value_type>(outColumn_, lhsColumn, rhs, func_);
			}
			else
			{
				outColumn_[Row_] = func_(lhsColumn[Row_], rhs[Row_]);
				_execute_basic_matrix_arithmetic_on_contained_scalars_until_complete<Row_ + 1, ArithmeticFunc_, num_columns, num_rows, value_type>(outColumn_, lhsColumn, rhs, func_);
			}
		}
	}
	template<std::size_t Row_, class ArithmeticFunc_, std::size_t num_columns, std::size_t num_rows, typename value_type>
	constexpr inline void _execute_basic_matrix_arithmetic_on_contained_scalars_until_complete
	(
		typename EmuMath::MatrixCM<num_columns, num_rows, value_type>::column_type& outColumn_,
		const typename EmuMath::MatrixCM<num_columns, num_rows, value_type>::column_type& matrix_,
		ArithmeticFunc_& func_
	)
	{
		if constexpr (Row_ < num_rows)
		{
			outColumn_[Row_] = func_(matrix_[Row_]);
			_execute_basic_matrix_arithmetic_on_contained_scalars_until_complete<Row_ + 1, ArithmeticFunc_, num_columns, num_rows, value_type>(outColumn_, matrix_, func_);
		}
	}

	template<std::size_t Column_, class ArithmeticFunc_, std::size_t num_columns, std::size_t num_rows, typename value_type, typename Rhs_>
	constexpr inline void _execute_basic_matrix_arithmetic_until_complete
	(
		EmuMath::MatrixCM<num_columns, num_rows, value_type>& out_,
		const EmuMath::MatrixCM<num_columns, num_rows, value_type>& lhs,
		const Rhs_& rhs,
		ArithmeticFunc_& func_
	)
	{
		if constexpr (Column_ < num_columns)
		{
			if constexpr (EmuMath::MatrixCM<num_columns, num_rows, value_type>::uses_vector_storage)
			{
				if constexpr (std::is_same_v<EmuMath::MatrixCM<num_columns, num_rows, value_type>, Rhs_>)
				{
					out_.columns[Column_] = func_(lhs.columns[Column_], rhs.columns[Column_]);
				}
				else if constexpr (std::is_arithmetic_v<std::remove_reference_t<Rhs_>>)
				{
					out_.columns[Column_] = func_(lhs.columns[Column_], rhs);
				}
				else
				{
					static_assert(false, "Attempted to perform basic Matrix arithmetic with an invalid right-hand argument type.");
					return;
				}
			}
			else
			{
				if constexpr (std::is_same_v<EmuMath::MatrixCM<num_columns, num_rows, value_type>, Rhs_>)
				{
					_execute_basic_matrix_arithmetic_on_contained_scalars_until_complete<0, ArithmeticFunc_, num_columns, num_rows, value_type>
						(
							out_.columns[Column_],
							lhs.columns[Column_],
							rhs.columns[Column_],
							func_
							);
				}
				else if constexpr (std::is_arithmetic_v<std::remove_reference_t<Rhs_>>)
				{
					_execute_basic_matrix_arithmetic_on_contained_scalars_until_complete<0, ArithmeticFunc_, num_columns, num_rows, value_type>
						(
							out_.columns[Column_],
							lhs.columns[Column_],
							rhs,
							func_
							);
				}
				else
				{
					static_assert(false, "Attempted to perform basic Matrix arithmetic with an invalid right-hand argument type.");
					return;
				}
			}
			_execute_basic_matrix_arithmetic_until_complete<Column_ + 1, ArithmeticFunc_>(out_, lhs, rhs, func_);
		}
	}
	template<std::size_t Column_, class ArithmeticFunc_, std::size_t num_columns, std::size_t num_rows, typename value_type>
	constexpr inline void _execute_basic_matrix_arithmetic_until_complete
	(
		EmuMath::MatrixCM<num_columns, num_rows, value_type>& out_,
		const EmuMath::MatrixCM<num_columns, num_rows, value_type>& matrix_,
		ArithmeticFunc_& func_
	)
	{
		if constexpr (Column_ < num_columns)
		{
			if constexpr (EmuMath::MatrixCM<num_columns, num_rows, value_type>::uses_vector_storage)
			{
				out_.columns[Column_] = func_(matrix_.columns[Column_]);
			}
			else
			{
				_execute_basic_matrix_arithmetic_on_contained_scalars_until_complete<0, ArithmeticFunc_>
					(
						out_.columns[Column_],
						matrix_.columns[Column_],
						func_
						);
			}
			_execute_basic_matrix_arithmetic_until_complete<Column_ + 1, ArithmeticFunc_>(out_, matrix_, func_);
		}
	}

	/// <summary> Performs basic matrix arithmetic where adjacent elements have particular arithmetic performed on respective elements (e.g. c0r1a + c0r1b). </summary>
	/// <typeparam name="ArithmeticFunc_">Functor to perform arithmetic.</typeparam>
	/// <typeparam name="value_type">Type stored within the matrix.</typeparam>
	/// <returns>Matrix after the arithmetic has been performed.</returns>
	template<class ArithmeticFunc_, std::size_t num_columns, std::size_t num_rows, typename value_type, typename Rhs_>
	constexpr inline EmuMath::MatrixCM<num_columns, num_rows, value_type> _perform_basic_matrix_arithmetic
	(
		const EmuMath::MatrixCM<num_columns, num_rows, value_type>& lhs,
		const Rhs_& rhs
	)
	{
		ArithmeticFunc_ func_ = ArithmeticFunc_();
		EmuMath::MatrixCM<num_columns, num_rows, value_type> out_ = EmuMath::MatrixCM<num_columns, num_rows, value_type>();
		_execute_basic_matrix_arithmetic_until_complete<0, ArithmeticFunc_>(out_, lhs, rhs, func_);
		return out_;
	}
	template<class ArithmeticFunc_, std::size_t num_columns, std::size_t num_rows, typename value_type>
	constexpr inline EmuMath::MatrixCM<num_columns, num_rows, value_type> _perform_basic_matrix_arithmetic
	(
		const EmuMath::MatrixCM<num_columns, num_rows, value_type>& matrix_
	)
	{
		ArithmeticFunc_ func_ = ArithmeticFunc_();
		EmuMath::MatrixCM<num_columns, num_rows, value_type> out_ = EmuMath::MatrixCM<num_columns, num_rows, value_type>();
		_execute_basic_matrix_arithmetic_until_complete<0, ArithmeticFunc_>(out_, matrix_, func_);
		return out_;
	}
#pragma endregion

#pragma region GETS
	template<std::size_t Column_, std::size_t Row_, std::size_t num_columns, std::size_t num_rows, typename value_type>
	constexpr value_type& _get_matrix_data_value(EmuMath::MatrixCM<num_columns, num_rows, value_type>& matrix_)
	{
		if constexpr (Column_ < num_columns)
		{
			if constexpr (Row_ < num_rows)
			{
				if constexpr (EmuMath::MatrixCM<num_columns, num_rows, value_type>::uses_vector_storage)
				{
					return matrix_.columns[Column_].template at<Row_>();
				}
				else
				{
					return std::get<Row_>(matrix_.columns[Column_]);
				}
			}
			else
			{
				static_assert(false, "Provided an invalid row index when trying to get an element from an EmuMath Matrix.");
			}
		}
		else
		{
			static_assert(false, "Provided an invalid column index when trying to get an element from an EmuMath Matrix.");
		}
	}
	template<std::size_t Column_, std::size_t Row_, std::size_t num_columns, std::size_t num_rows, typename value_type>
	constexpr value_type _get_matrix_data_value(const EmuMath::MatrixCM<num_columns, num_rows, value_type>& matrix_)
	{
		if constexpr (Column_ < num_columns)
		{
			if constexpr (Row_ < num_rows)
			{
				if constexpr (EmuMath::MatrixCM<num_columns, num_rows, value_type>::uses_vector_storage)
				{
					return matrix_.columns[Column_].template at<Row_>();
				}
				else
				{
					return std::get<Row_>(matrix_.columns[Column_]);
				}
			}
			else
			{
				static_assert(false, "Provided an invalid row index when trying to get an element from an EmuMath Matrix.");
			}
		}
		else
		{
			static_assert(false, "Provided an invalid column index when trying to get an element from an EmuMath Matrix.");
		}
	}
	template<std::size_t num_columns, std::size_t num_rows, typename value_type>
	constexpr value_type& _get_matrix_data_value(EmuMath::MatrixCM<num_columns, num_rows, value_type>& matrix_, const std::size_t column_, const std::size_t row_)
	{
		return matrix_.columns[column_][row_];
	}
	template<std::size_t num_columns, std::size_t num_rows, typename value_type>
	constexpr value_type _get_matrix_data_value(const EmuMath::MatrixCM<num_columns, num_rows, value_type>& matrix_, const std::size_t column_, const std::size_t row_)
	{
		return matrix_.columns[column_][row_];
	}

	template<std::size_t Index_, std::size_t num_columns, std::size_t num_rows, typename value_type>
	constexpr inline typename EmuMath::MatrixCM<num_columns, num_rows, value_type>::major_type& _get_matrix_major_index
	(
		EmuMath::MatrixCM<num_columns, num_rows, value_type>& matrix_
	)
	{
		return matrix_.columns[Index_];
	}
	template<std::size_t Index_, std::size_t num_columns, std::size_t num_rows, typename value_type>
	constexpr inline typename EmuMath::MatrixCM<num_columns, num_rows, value_type>::major_type _get_matrix_major_index
	(
		const EmuMath::MatrixCM<num_columns, num_rows, value_type>& matrix_
	)
	{
		return matrix_.columns[Index_];
	}
	template<std::size_t num_columns, std::size_t num_rows, typename value_type>
	constexpr inline typename EmuMath::MatrixCM<num_columns, num_rows, value_type>::major_type& _get_matrix_major_index
	(
		EmuMath::MatrixCM<num_columns, num_rows, value_type>& matrix_,
		std::size_t index_
	)
	{
		return matrix_.columns[index_];
	}
	template<std::size_t num_columns, std::size_t num_rows, typename value_type>
	constexpr inline typename EmuMath::MatrixCM<num_columns, num_rows, value_type>::major_type _get_matrix_major_index
	(
		const EmuMath::MatrixCM<num_columns, num_rows, value_type>& matrix_,
		std::size_t index_
	)
	{
		return matrix_.columns[index_];
	}

	template<std::size_t Index_, typename MajorData_>
	constexpr typename MajorData_::value_type& _get_matrix_major_data_value(typename MajorData_& majorData_)
	{
		if constexpr (EmuMath::TMPHelpers::is_emu_vector_v<MajorData_>)
		{
			return majorData_.template at<Index_>();
		}
		else
		{
			return majorData_[Index_];
		}
	}
	template<std::size_t Index_, typename MajorData_>
	constexpr typename MajorData_::value_type _get_matrix_major_data_value(const MajorData_& majorData_)
	{
		if constexpr (EmuMath::TMPHelpers::is_emu_vector_v<MajorData_>)
		{
			return majorData_.template at<Index_>();
		}
		else
		{
			return majorData_[Index_];
		}
	}

	template<std::size_t CurrentColumn_, std::size_t TargetRowIndex_, std::size_t num_columns, std::size_t num_rows, typename value_type>
	void _fill_matrix_row

	(
		typename EmuMath::MatrixCM<num_columns, num_rows, value_type>::row_type& outRow_,
		const EmuMath::MatrixCM<num_columns, num_rows, value_type>& matrix_
	)
	{
		if constexpr (CurrentColumn_ < num_columns)
		{
			_get_matrix_major_data_value<CurrentColumn_>(outRow_) = _get_matrix_data_value<CurrentColumn_, TargetRowIndex_>(matrix_);
			_fill_matrix_row<CurrentColumn_ + 1, TargetRowIndex_>(outRow_, matrix_);
		}
	}

	template<std::size_t num_columns, std::size_t num_rows, typename value_type>
	std::array<typename EmuMath::MatrixCM<num_columns, num_rows, value_type>::row_type, num_columns> _copy_all_matrix_columns
	(
		const EmuMath::MatrixCM<num_columns, num_rows, value_type>& matrix_
	)
	{
		return matrix_.columns;
	}

	template<std::size_t RowIndex_, std::size_t num_columns, std::size_t num_rows, typename value_type>
	void _copy_all_matrix_rows
	(
		std::array<typename EmuMath::MatrixCM<num_columns, num_rows, value_type>::row_type, num_rows>& outRows_,
		const EmuMath::MatrixCM<num_columns, num_rows, value_type>& matrix_
	)
	{
		if constexpr (RowIndex_ < num_rows)
		{
			_fill_matrix_row<0, RowIndex_>(outRows_[RowIndex_], matrix_);
			_copy_all_matrix_rows<RowIndex_ + 1>(outRows_, matrix_);
		}
	}
	template<std::size_t num_columns, std::size_t num_rows, typename value_type>
	std::array<typename EmuMath::MatrixCM<num_columns, num_rows, value_type>::row_type, num_rows> _copy_all_matrix_rows
	(
		const EmuMath::MatrixCM<num_columns, num_rows, value_type>& matrix_
	)
	{
		std::array<typename EmuMath::MatrixCM<num_columns, num_rows, value_type>::row_type, num_rows> rows;
		_copy_all_matrix_rows<0>(rows, matrix_);
		return rows;
	}
#pragma endregion

#pragma region SETS
	template<std::size_t Column_, std::size_t Row_, class LhsMatrix_, class RhsMatrix_>
	constexpr inline void _matrix_set(LhsMatrix_& lhs_, const RhsMatrix_& rhs_)
	{
		if constexpr (Column_ < LhsMatrix_::num_columns)
		{
			if constexpr (Row_ < RhsMatrix_::num_rows)
			{
				_get_matrix_data_value<Column_, Row_>(lhs_) = static_cast<typename LhsMatrix_::value_type>(_get_matrix_data_value<Column_, Row_>(rhs_));
				_matrix_set<Column_, Row_ + 1, LhsMatrix_, RhsMatrix_>(lhs_, rhs_);
			}
			else
			{
				_matrix_set<Column_ + 1, 0, LhsMatrix_, RhsMatrix_>(lhs_, rhs_);
			}
		}
	}
#pragma endregion

#pragma region MATRIX_OPERATIONS
	template<std::size_t Row_, std::size_t num_columns, std::size_t num_rows, typename value_type>
	constexpr inline void _execute_matrix_transposition
	(
		EmuMath::MatrixCM<num_rows, num_columns, value_type>& out_,
		const EmuMath::MatrixCM<num_columns, num_rows, value_type>& matrix_
	)
	{
		if constexpr (Row_ < num_rows)
		{
			_fill_matrix_row<0, Row_>(out_.columns[Row_], matrix_);
			_execute_matrix_transposition<Row_ + 1>(out_, matrix_);
		}
	}

	template<std::size_t Index_, typename OutT_, class Matrix_>
	constexpr inline OutT_ _calculate_matrix_trace(const Matrix_& matrix_)
	{
		if constexpr (Index_ < Matrix_::num_rows)
		{
			return static_cast<OutT_>(_get_matrix_data_value<Index_, Index_>(matrix_)) + _calculate_matrix_trace<Index_ + 1, OutT_>(matrix_);
		}
		else
		{
			return OutT_(0);
		}
	}

	template<std::size_t Index_, class Matrix_>
	constexpr void _fill_identity_matrix(Matrix_& matrix_)
	{
		if constexpr (Index_ < Matrix_::num_rows)
		{
			using value_type = typename Matrix_::value_type;
			_get_matrix_data_value<Index_, Index_>(matrix_) = value_type(1);
			_fill_identity_matrix<Index_ + 1>(matrix_);
		}
	}

	template<std::size_t BeginColumn, std::size_t EndColumn, std::size_t BeginRow, std::size_t EndRow, std::size_t OutColumn, std::size_t OutRow, class Matrix_, class Out_>
	constexpr inline void _fill_matrix_submatrix(const Matrix_& matrix_, Out_& out_)
	{
		if constexpr (OutColumn < Out_::num_columns)
		{
			if constexpr (OutRow < Out_::num_rows)
			{
				_get_matrix_data_value<OutColumn, OutRow>(out_) = _get_matrix_data_value<BeginColumn + OutColumn, BeginRow + OutRow>(matrix_);
				_fill_matrix_submatrix<BeginColumn, EndColumn, BeginRow, EndRow, OutColumn, OutRow + 1, Matrix_, Out_>(matrix_, out_);
			}
			else
			{
				_fill_matrix_submatrix<BeginColumn, EndColumn, BeginRow, EndRow, OutColumn + 1, 0, Matrix_, Out_>(matrix_, out_);
			}
		}
	}

	template<std::size_t BeginColumn, std::size_t EndColumn, std::size_t BeginRow, std::size_t EndRow, class Matrix_, class Out_>
	constexpr inline Out_ _find_matrix_submatrix(const Matrix_& matrix_)
	{
		Out_ out_ = Out_();
		_fill_matrix_submatrix<BeginColumn, EndColumn, BeginRow, EndRow, 0, 0, Matrix_, Out_>(matrix_, out_);
		return out_;
	}

	template<std::size_t IgnoreColumn_, std::size_t IgnoreRow_, std::size_t InColumn_, std::size_t InRow_, std::size_t OutColumn_, std::size_t OutRow_, class Matrix_, class Out_>
	constexpr inline void _fill_matrix_submatrix_exclusive(const Matrix_& matrix_, Out_& out_)
	{
		if constexpr (InColumn_ < Matrix_::num_columns)
		{
			if constexpr (InColumn_ != IgnoreColumn_)
			{
				if constexpr (InRow_ < Matrix_::num_rows)
				{
					if constexpr (InRow_ != IgnoreRow_)
					{
						_get_matrix_data_value<OutColumn_, OutRow_>(out_) = _get_matrix_data_value<InColumn_, InRow_>(matrix_);
						_fill_matrix_submatrix_exclusive<IgnoreColumn_, IgnoreRow_, InColumn_, InRow_ + 1, OutColumn_, OutRow_ + 1, Matrix_, Out_>(matrix_, out_);
					}
					else
					{
						_fill_matrix_submatrix_exclusive<IgnoreColumn_, IgnoreRow_, InColumn_, InRow_ + 1, OutColumn_, OutRow_, Matrix_, Out_>(matrix_, out_);
					}
				}
				else
				{
					_fill_matrix_submatrix_exclusive<IgnoreColumn_, IgnoreRow_, InColumn_ + 1, 0, OutColumn_ + 1, 0, Matrix_, Out_>(matrix_, out_);
				}
			}
			else
			{
				_fill_matrix_submatrix_exclusive<IgnoreColumn_, IgnoreRow_, InColumn_ + 1, InRow_, OutColumn_, OutRow_, Matrix_, Out_>(matrix_, out_);
			}
		}
	}

	template<std::size_t IgnoreColumn_, std::size_t IgnoreRow_, class Matrix_, class Out_>
	constexpr inline Out_ _find_matrix_submatrix_exclusive(const Matrix_& matrix_)
	{
		Out_ out_ = Out_();
		_fill_matrix_submatrix_exclusive<IgnoreColumn_, IgnoreRow_, 0, 0, 0, 0, Matrix_, Out_>(matrix_, out_);
		return out_;
	}
#pragma endregion

#pragma region MATRIX_ARITHMETIC

	template<std::size_t Index_, typename OutT_, class LhsRow_, class RhsColumn_>
	inline constexpr OutT_ _matrix_row_column_dot_scalar(const LhsRow_& lhsRow_, const RhsColumn_& rhsColumn_)
	{
		if constexpr (Index_ < LhsRow_::size())
		{
			return (lhsRow_[Index_] * rhsColumn_[Index_]) + _matrix_row_column_dot_scalar<Index_ + 1, OutT_, LhsRow_, RhsColumn_>(lhsRow_, rhsColumn_);
		}
		else
		{
			return OutT_(0);
		}
	}
	template<typename OutT_, class LhsRow_, class RhsColumn_>
	inline constexpr OutT_ _matrix_row_column_dot(const LhsRow_& lhsRow_, const RhsColumn_& rhsColumn_)
	{
		if constexpr (EmuCore::TMPHelpers::are_all_check<EmuMath::TMPHelpers::is_emu_vector, LhsRow_, RhsColumn_>::value)
		{
			return EmuMath::Helpers::VectorDotProduct<OutT_>(lhsRow_, rhsColumn_);
		}
		else
		{
			return _matrix_row_column_dot_scalar<0, OutT_, LhsRow_, RhsColumn_>(lhsRow_, rhsColumn_);
		}
	}

	template<std::size_t Column_, std::size_t Row_, std::size_t num_columns, std::size_t num_rows, class LhsRows_, class RhsColumns_, typename value_type>
	constexpr void _multiply_matrices
	(
		EmuMath::MatrixCM<num_columns, num_rows, value_type>& out_,
		const LhsRows_& lhsRows_,
		const RhsColumns_& rhsColumns_
	)
	{
		if constexpr (Column_ < num_columns)
		{
			if constexpr (Row_ < num_rows)
			{
				using LhsValue = typename LhsRows_::value_type;
				using RhsValue = typename RhsColumns_::value_type;
				_get_matrix_data_value<Column_, Row_>(out_) = _matrix_row_column_dot<value_type, LhsValue, RhsValue>(lhsRows_[Row_], rhsColumns_[Column_]);
				_multiply_matrices<Column_, Row_ + 1>(out_, lhsRows_, rhsColumns_);
			}
			else
			{
				_multiply_matrices<Column_ + 1, 0>(out_, lhsRows_, rhsColumns_);
			}
		}
	}

	template<std::size_t num_columns, std::size_t num_rows, typename value_type>
	constexpr EmuMath::MatrixCM<num_columns, num_rows, value_type> _multiply_matrices
	(
		const EmuMath::MatrixCM<num_columns, num_rows, value_type>& lhs,
		const EmuMath::MatrixCM<num_columns, num_rows, value_type>& rhs
	)
	{
		using LhsRow = typename EmuMath::MatrixCM<num_columns, num_rows, value_type>::row_type;
		using RhsColumn = typename EmuMath::MatrixCM<num_columns, num_rows, value_type>::column_type;

		EmuMath::MatrixCM<num_columns, num_rows, value_type> out_ = EmuMath::MatrixCM<num_columns, num_rows, value_type>();
		std::array<LhsRow, num_rows> lhsRows = _copy_all_matrix_rows(lhs);
		std::array<RhsColumn, num_columns> rhsColumns = _copy_all_matrix_columns(rhs);
		_multiply_matrices<0, 0>(out_, lhsRows, rhsColumns);
		return out_;

	}
#pragma endregion
}

#endif
