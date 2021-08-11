#ifndef EMU_MATH_MATRIX_HELPERS_H_INC_
#define EMU_MATH_MATRIX_HELPERS_H_INC_

#include "EmuMatrixTMPHelpers.h"
#include "../Vectors.h"

namespace EmuMath
{
	template<std::size_t NumColumns_, std::size_t NumRows_, typename T_>
	struct MatrixCM;
}

namespace EmuMath::Helpers
{
	/// <summary> TMP helper to determine what a major type should be stored as within a matrix (e.g. what columns are stored as in column-major matrices). </summary>
	/// <typeparam name="T_">Type used to represent an individual value within the matrix.</typeparam>
	template<std::size_t NumComponents_, typename T_>
	struct matrix_major_element
	{
		using type = std::array<T_, NumComponents_>;
	};
	template<typename T_>
	struct matrix_major_element<2, T_>
	{
		using type = EmuMath::Vector2<T_>;
	};
	template<typename T_>
	struct matrix_major_element<3, T_>
	{
		using type = EmuMath::Vector3<T_>;
	};
	template<typename T_>
	struct matrix_major_element<4, T_>
	{
		using type = EmuMath::Vector4<T_>;
	};

	namespace _underlying_matrix_funcs
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

#pragma region ARITHMETIC
	template<std::size_t num_columns, std::size_t num_rows, typename value_type>
	constexpr EmuMath::MatrixCM<num_columns, num_rows, value_type> MatrixAddition
	(
		const EmuMath::MatrixCM<num_columns, num_rows, value_type>& lhs,
		const EmuMath::MatrixCM<num_columns, num_rows, value_type>& rhs
	)
	{
		return _underlying_matrix_funcs::_perform_basic_matrix_arithmetic<std::plus<void>>(lhs, rhs);
	}
	template<std::size_t num_columns, std::size_t num_rows, typename value_type>
	constexpr EmuMath::MatrixCM<num_columns, num_rows, value_type> MatrixSubtraction
	(
		const EmuMath::MatrixCM<num_columns, num_rows, value_type>& lhs,
		const EmuMath::MatrixCM<num_columns, num_rows, value_type>& rhs
	)
	{
		return _underlying_matrix_funcs::_perform_basic_matrix_arithmetic<std::minus<void>>(lhs, rhs);
	}
	template<std::size_t num_columns, std::size_t num_rows, typename value_type>
	constexpr EmuMath::MatrixCM<num_columns, num_rows, value_type> MatrixNegation(const EmuMath::MatrixCM<num_columns, num_rows, value_type>& matrix_)
	{
		return _underlying_matrix_funcs::_perform_basic_matrix_arithmetic<std::negate<void>>(matrix_);
	}

	template<typename ScalarMultiplier, std::size_t num_columns, std::size_t num_rows, typename value_type>
	constexpr EmuMath::MatrixCM<num_columns, num_rows, value_type> MatrixMultiplication
	(
		const EmuMath::MatrixCM<num_columns, num_rows, value_type>& matrix_,
		ScalarMultiplier mult
	)
	{
		static_assert
		(
			std::is_arithmetic_v<std::remove_reference_t<ScalarMultiplier>>,
			"Attempted to multiply an EmuMath Matrix by a non-matrix right-hand type which is also not an arithmetic type."
		);
		return _underlying_matrix_funcs::_perform_basic_matrix_arithmetic<std::multiplies<void>>(matrix_, mult);
	}
	template<std::size_t num_columns, std::size_t num_rows, typename value_type>
	constexpr EmuMath::MatrixCM<num_columns, num_rows, value_type> MatrixMultiplication
	(
		const EmuMath::MatrixCM<num_columns, num_rows, value_type>& lhs,
		const EmuMath::MatrixCM<num_columns, num_rows, value_type>& rhs
	)
	{
		return _underlying_matrix_funcs::_multiply_matrices(lhs, rhs);
	}
	/// <summary>
	/// <para> Multiplies respective elements of two matrices, instead of performing a normal matrix multiplication (e.g. c0r2` = c0r2a * c0r2b). </para>
	/// <para> To perform a standard matrix multiplication, use MatrixMultiplication with the same arguments. </para>
	/// </summary>
	/// <typeparam name="value_type">Type stored within the passed matrices.</typeparam>
	/// <param name="lhs">Left-hand argument for the multiplications. This is a commutative multiplication, so handedness does not affect the result.</param>
	/// <param name="lhs">Right-hand argument for the multiplications. This is a commutative multiplication, so handedness does not affect the result.</param>
	/// <returns>Resulting matrix from mutliplying respective elements of the two passed matrices. This is not the result of a standard matrix multiplication.</returns>
	template<std::size_t num_columns, std::size_t num_rows, typename value_type>
	constexpr EmuMath::MatrixCM<num_columns, num_rows, value_type> MatrixRespectiveMultiplication
	(
		const EmuMath::MatrixCM<num_columns, num_rows, value_type>& lhs,
		const EmuMath::MatrixCM<num_columns, num_rows, value_type>& rhs
	)
	{
		return _underlying_matrix_funcs::_perform_basic_matrix_arithmetic<std::multiplies<void>>(lhs, rhs);

	}

#pragma endregion

#pragma region GETS
	/// <summary> Accesses the element at the provided indices of the passed matrix. </summary>
	/// <typeparam name="Matrix_">Type of matrix to access.</typeparam>
	/// <param name="matrix_">EmuMath matrix to access.</param>
	/// <returns>Reference to the element at the provided indices within the passed matrix.</returns>
	template<std::size_t Column_, std::size_t Row_, class Matrix_>
	constexpr inline typename Matrix_::value_type& MatrixGet(Matrix_& matrix_)
	{
		if constexpr (_underlying_matrix_funcs::_matrix_get_validity_check<Column_, Row_, Matrix_>())
		{
			return _underlying_matrix_funcs::_get_matrix_data_value<Column_, Row_>(matrix_);
		}
		else
		{
			static_assert(false, "Invalid call to EmuMath::Helpers::MatrixGet.");
		}
	}
	/// <summary> Accesses a copy of the element at the provided indices of the passed matrix. </summary>
	/// <typeparam name="Matrix_">Type of matrix to access.</typeparam>
	/// <param name="matrix_">EmuMath matrix to access.</param>
	/// <returns>Copy of the element at the provided indices within the passed matrix.</returns>
	template<std::size_t Column_, std::size_t Row_, class Matrix_>
	constexpr inline typename Matrix_::value_type MatrixGet(const Matrix_& matrix_)
	{
		if constexpr (_underlying_matrix_funcs::_matrix_get_validity_check<Column_, Row_, Matrix_>())
		{
			return _underlying_matrix_funcs::_get_matrix_data_value<Column_, Row_>(matrix_);
		}
		else
		{
			static_assert(false, "Invalid call to EmuMath::Helpers::MatrixGet.");
		}
	}
	/// <summary>
	/// <para> Accesses the major element at the provided index of the passed matrix. </para>
	/// <para>
	///		The returned data will depend on the storage of the matrix; if it is column major, this will return the row at the passed index; 
	///		if row major, it will return the row at the passed index.
	/// </para>
	/// </summary>
	/// <typeparam name="Matrix_">Type of matrix to access.</typeparam>
	/// <param name="matrix_">EmuMath matrix to access.</param>
	/// <returns>Reference to the major element at the provided indices within the passed matrix; a column if the matrix is column major, or a row if the matrix is row major.</returns>
	template<std::size_t MajorIndex_, class Matrix_>
	constexpr inline typename Matrix_::major_type& MatrixGet(Matrix_& matrix_)
	{
		if constexpr (_underlying_matrix_funcs::_matrix_get_major_validity_check<MajorIndex_, Matrix_>())
		{
			return _underlying_matrix_funcs::_get_matrix_major_index<MajorIndex_>(matrix_);
		}
		else
		{
			static_assert(false, "Invalid call to EmuMath::Helpers::MatrixGet.");
		}
	}
	/// <summary>
	/// <para> Accesses a copy of the major element at the provided index of the passed matrix. </para>
	/// <para>
	///		The returned data will depend on the storage of the matrix; if it is column major, this will return the row at the passed index; 
	///		if row major, it will return the row at the passed index.
	/// </para>
	/// </summary>
	/// <typeparam name="Matrix_">Type of matrix to access.</typeparam>
	/// <param name="matrix_">EmuMath matrix to access.</param>
	/// <returns>Copy of the major element at the provided indices within the passed matrix; a column if the matrix is column major, or a row if the matrix is row major.</returns>
	template<std::size_t MajorIndex_, class Matrix_>
	constexpr inline typename Matrix_::major_type MatrixGet(const Matrix_& matrix_)
	{
		if constexpr (_underlying_matrix_funcs::_matrix_get_major_validity_check<MajorIndex_, Matrix_>())
		{
			return _underlying_matrix_funcs::_get_matrix_major_index<MajorIndex_>(matrix_);
		}
		else
		{
			static_assert(false, "Invalid call to EmuMath::Helpers::MatrixGet.");
		}
	}
	/// <summary>
	/// <para> Accesses the element at the provided column_ and row_ indices of the passed matrix. </para>
	/// <para> If column_ and row_ are compile-time evaluable, it is recommended to pass them as template arguments instead. </para>
	/// </summary>
	/// <typeparam name="Matrix_">Type of matrix to access.</typeparam>
	/// <param name="matrix_">EmuMath matrix to access.</param>
	/// <param name="column_">Index of the column to access.</param>
	/// <param name="row_">Index of the row to access.</param>
	/// <returns>Reference to the element at the provided indices within the passed matrix.</returns>
	template<class Matrix_>
	constexpr inline typename Matrix_::value_type& MatrixGet(Matrix_& matrix_, const std::size_t column_, const std::size_t row_)
	{
		if constexpr (_underlying_matrix_funcs::_matrix_get_basic_validity_check<Matrix_>())
		{
			return _underlying_matrix_funcs::_get_matrix_data_value(matrix_, column_, row_);
		}
		else
		{
			static_assert(false, "Invalid call to EmuMath::Helpers::MatrixGet.");
		}
	}
	/// <summary>
	/// <para> Accesses a copy of the element at the provided column_ and row_ indices of the passed matrix. </para>
	/// <para> If column_ and row_ are compile-time evaluable, it is recommended to pass them as template arguments instead. </para>
	/// </summary>
	/// <typeparam name="Matrix_">Type of matrix to access.</typeparam>
	/// <param name="matrix_">EmuMath matrix to access.</param>
	/// <param name="column_">Index of the column to access.</param>
	/// <param name="row_">Index of the row to access.</param>
	/// <returns>Copy of the element at the provided indices within the passed matrix.</returns>
	template<class Matrix_>
	constexpr inline typename Matrix_::value_type MatrixGet(const Matrix_& matrix_, const std::size_t column_, const std::size_t row_)
	{
		if constexpr (_underlying_matrix_funcs::_matrix_get_basic_validity_check<Matrix_>())
		{
			return _underlying_matrix_funcs::_get_matrix_data_value(matrix_, column_, row_);
		}
		else
		{
			static_assert(false, "Invalid call to EmuMath::Helpers::MatrixGet.");
		}
	}
	/// <summary>
	/// <para> Accesses the major element at the provided index of the passed matrix. </para>
	/// <para>
	///		The returned data will depend on the storage of the matrix; if it is column major, this will return the row at the passed index; 
	///		if row major, it will return the row at the passed index.
	/// </para>
	/// <para> If majorIndex_ is compile-time evaluable, it is recommended to pass it as a template argument instead. </para>
	/// </summary>
	/// <typeparam name="Matrix_">Type of matrix to access.</typeparam>
	/// <param name="matrix_">EmuMath matrix to access.</param>
	/// <param name="majorIndex_">Index of the major-stored element to access.</param>
	/// <returns>Reference to the major element at the provided indices within the passed matrix; a column if the matrix is column major, or a row if the matrix is row major.</returns>
	template<class Matrix_>
	constexpr inline typename Matrix_::major_type& MatrixGet(Matrix_& matrix_, const std::size_t majorIndex_)
	{
		if constexpr (_underlying_matrix_funcs::_matrix_get_basic_validity_check<Matrix_>())
		{
			return _underlying_matrix_funcs::_get_matrix_major_index(matrix_, majorIndex_);
		}
		else
		{
			static_assert(false, "Invalid call to EmuMath::Helpers::MatrixGet.");
		}
	}
	/// <summary>
	/// <para> Accesses a copy of the major element at the provided index of the passed matrix. </para>
	/// <para>
	///		The returned data will depend on the storage of the matrix; if it is column major, this will return the row at the passed index; 
	///		if row major, it will return the row at the passed index.
	/// </para>
	/// <para> If majorIndex_ is compile-time evaluable, it is recommended to pass it as a template argument instead. </para>
	/// </summary>
	/// <typeparam name="Matrix_">Type of matrix to access.</typeparam>
	/// <param name="matrix_">EmuMath matrix to access.</param>
	/// <param name="majorIndex_">Index of the major-stored element to access.</param>
	/// <returns>Copy of the major element at the provided indices within the passed matrix; a column if the matrix is column major, or a row if the matrix is row major.</returns>
	template<class Matrix_>
	constexpr inline typename Matrix_::major_type MatrixGet(const Matrix_& matrix_, const std::size_t majorIndex_)
	{
		if constexpr (_underlying_matrix_funcs::_matrix_get_basic_validity_check<Matrix_>())
		{
			return _underlying_matrix_funcs::_get_matrix_major_index(matrix_, majorIndex_);
		}
		else
		{
			static_assert(false, "Invalid call to EmuMath::Helpers::MatrixGet.");
		}
	}

	/// <summary> Copies the specified row index from the passed matrix, regardless of its major-storage configuration. </summary>
	/// <param name="matrix_">EmuMath matrix to access.</param>
	/// <returns>Copy of the specified row within the passed matrix.</returns>
	template<std::size_t TargetRowIndex_, std::size_t num_columns, std::size_t num_rows, typename value_type>
	constexpr inline typename EmuMath::MatrixCM<num_columns, num_rows, value_type>::row_type MatrixGetRow(const EmuMath::MatrixCM<num_columns, num_rows, value_type>& matrix_)
	{
		using OutT_ = typename EmuMath::MatrixCM<num_columns, num_rows, value_type>::row_type;
		if constexpr (TargetRowIndex_ < num_rows)
		{
			OutT_ out_ = OutT_();
			_underlying_matrix_funcs::_fill_matrix_row<0, TargetRowIndex_, num_columns, num_rows, value_type>(out_, matrix_);
			return out_;
		}
		else
		{
			static_assert(false, "Passed an invalid row index when attempting to get the row of an EmuMath Matrix.");
			return OutT_();
		}
	}
	/// <summary> Copies the specified column index from the passed matrix, regardless of its major-storage configuration. </summary>
	/// <param name="matrix_">EmuMath matrix to access.</param>
	/// <returns>Copy of the specified column within the passed matrix.</returns>
	template<std::size_t TargetColumnIndex_, std::size_t num_columns, std::size_t num_rows, typename value_type>
	constexpr inline typename EmuMath::MatrixCM<num_columns, num_rows, value_type>::column_type MatrixGetColumn(const EmuMath::MatrixCM<num_columns, num_rows, value_type>& matrix_)
	{
		if constexpr (TargetColumnIndex_ < num_columns)
		{
			return matrix_.columns[TargetColumnIndex_];
		}
		else
		{
			static_assert(false, "Passed an invalid column index when attempting to get the column of an EmuMath Matrix.");
			return typename EmuMath::MatrixCM<num_columns, num_rows, value_type>::column_type();
		}
	}

	/// <summary> Returns a standard array copy of the passed matrix, stored in rows as the matrix's row_type. </summary>
	/// <typeparam name="Matrix_">Type of matrix to access.</typeparam>
	/// <param name="matrix_">EmuMath matrix to access.</param>
	/// <returns>Standard array of passed matrix's row_type, representing a copy of the passed matrix.</returns>
	template<class Matrix_>
	constexpr inline std::array<typename Matrix_::row_type, Matrix_::num_rows> MatrixCopyAsRows(const Matrix_& matrix_)
	{
		return _underlying_matrix_funcs::_copy_all_matrix_rows(matrix_);
	}
	/// <summary> Returns a standard array copy of the passed matrix, stored in columns as the matrix's column_type. </summary>
	/// <typeparam name="Matrix_">Type of matrix to access.</typeparam>
	/// <param name="matrix_">EmuMath matrix to access.</param>
	/// <returns>Standard array of passed matrix's column_type, representing a copy of the passed matrix.</returns>
	template<class Matrix_>
	constexpr inline std::array<typename Matrix_::column_type, Matrix_::num_columns> MatrixCopyAsColumns(const Matrix_& matrix_)
	{
		return _underlying_matrix_funcs::_copy_all_matrix_columns(matrix_);
	}
#pragma endregion

#pragma region SETS
	template<class LhsMatrix_, class RhsMatrix_>
	constexpr inline LhsMatrix_& MatrixSet(LhsMatrix_& lhs_, const RhsMatrix_& rhs_)
	{
		if constexpr (EmuMath::TMPHelpers::is_emu_matrix_v<LhsMatrix_>)
		{
			if constexpr (EmuMath::TMPHelpers::is_emu_matrix_v<RhsMatrix_>)
			{
				if constexpr (LhsMatrix_::num_columns == RhsMatrix_::num_columns)
				{
					if constexpr (LhsMatrix_::num_rows == RhsMatrix_::num_rows)
					{
						_underlying_matrix_funcs::_matrix_set<0, 0, LhsMatrix_, RhsMatrix_>(lhs_, rhs_);
					}
					else
					{
						static_assert(false, "Attempted to set an EmuMath matrix via MatrixSet, but the matrices did not have matching numbers of rows.");
					}
				}
				else
				{
					static_assert(false, "Attempted to set an EmuMath matrix via MatrixSet, but the matrices did not have matching numbers of columns.");
				}
			}
			else
			{
				static_assert(false, "Attempted to set an EmuMath Matrix via MatrixSet, but provided a non-EmuMath-matrix right-hand operand.");
			}
		}
		else
		{
			static_assert(false, "Attempted to set an EmuMath Matrix via MatrixSet, but provided a non-EmuMath-matrix left-hand operand.");
		}
		return lhs_;
	}
#pragma endregion

#pragma region MATRIX_OPERATIONS
	/// <summary> Returns the transpose of the passed matrix. Columns will be converted to rows and vice versa. </summary>
	/// <param name="matrix_">EmuMath matrix to determine the transpose of.</param>
	/// <returns>
	///		Tranposed variant of the passed matrix. If the dimensions differ, the returned matrix's dimensions will be flipped 
	///		(i.e. num_columns will be the passed matrix's num_rows, and num_rows will be the passed matrix's num_columns).
	/// </returns>
	template<std::size_t num_columns, std::size_t num_rows, typename value_type>
	constexpr EmuMath::MatrixCM<num_rows, num_columns, value_type> MatrixTranspose(const EmuMath::MatrixCM<num_columns, num_rows, value_type>& matrix_)
	{
		EmuMath::MatrixCM<num_rows, num_columns, value_type> out_ = EmuMath::MatrixCM<num_rows, num_columns, value_type>();
		_underlying_matrix_funcs::_execute_matrix_transposition<0>(out_, matrix_);
		return out_;
	}

	/// <summary>
	/// <para> Calculates the trace of the passed matrix (the sum of diagonals from the top-left corner to the bottom-right corner). </para>
	/// <para> As the trace is only defined for a square matrix, this function requires that the passed matrix be a square matrix (i.e. equal number of columns and rows). </para>
	/// </summary>
	/// <typeparam name="OutT_">Type to output the trace as.</typeparam>
	/// <typeparam name="Matrix_">Type of matrix to calculate the trace of.</typeparam>
	/// <param name="matrix_">EmuMath matrix to calculate the trace of.</param>
	/// <returns>Trace of the passed matrix, assuming it is a square matrix.</returns>
	template<typename OutT_ = float, class Matrix_ = void>
	constexpr inline OutT_ MatrixTrace(const Matrix_& matrix_)
	{
		if constexpr (EmuMath::TMPHelpers::is_emu_matrix_v<Matrix_>)
		{
			if constexpr (Matrix_::is_square)
			{
				return _underlying_matrix_funcs::_calculate_matrix_trace<0, OutT_>(matrix_);
			}
			else
			{
				static_assert(false, "Attempted to get the trace of a non-square matrix. Only square matrices have a defined trace.");
			}
		}
		else
		{
			static_assert(false, "Passed a non-EmuMath Matrix argument when attempting to get the trace of a matrix.");
		}
	}

	/// <summary>
	/// <para> Returns the identity matrix of the provided matrix type. </para>
	/// <para> As the identity matrix is only defined for square matrices, this requires that the provided matrix type has an equal number of columns and rows. </para>
	/// </summary>
	/// <typeparam name="Matrix_">Type of matrix to return the identity matrix of.</typeparam>
	/// <typeparam name="RequiresSquareMatrix">Dummy parameter to make use of std::enable_if.</typeparam>
	/// <returns>Identity matrix of the provided EmuMath Matrix_ type.</returns>
	template<class Matrix_, typename RequiresSquareMatrix = std::enable_if_t<Matrix_::is_square>>
	constexpr inline Matrix_ MatrixIdentity()
	{
		if constexpr (EmuMath::TMPHelpers::is_emu_matrix_v<Matrix_>)
		{
			if constexpr (Matrix_::is_square)
			{
				Matrix_ out_ = Matrix_();
				_underlying_matrix_funcs::_fill_identity_matrix<0>(out_);
				return out_;
			}
			else
			{
				static_assert(false, "Attempted to get the identity matrix of an EmuMath matrix that does not have square dimensions (i.e. num_columns != num_rows).")
				return Matrix_();
			}
		}
		else
		{
			static_assert(false, "Attempted to get the identity matrix of a type that is not an EmuMath matrix.");
			return Matrix_();
		}
	}
	/// <summary> Shorthand for MatrixIdentity(), determining the argument for Matrix_ itself based on the passed matrix. </summary>
	/// <typeparam name="Matrix_">Type of matrix to return the identity matrix of.</typeparam>
	/// <typeparam name="RequiresSquareMatrix">Dummy parameter to make use of std::enable_if.</typeparam>
	/// <param name="matrix_">Matrix to determine the identity matrix of. This is the same for all matrices of the provided type, and the matrix is never used directly.</param>
	/// <returns>Identity matrix of the provided EmuMath Matrix_ type.</returns>
	template<class Matrix_, typename RequiresSquareMatrix = std::enable_if_t<Matrix_::is_square>>
	constexpr inline Matrix_ MatrixIdentity(const Matrix_& matrix_)
	{
		return MatrixIdentity<Matrix_>();
	}

	/// <summary>
	/// <para> Returns a smaller matrix contained within the passed matrix at the given ranges. </para>
	/// </summary>
	/// <typeparam name="Matrix_">Type of the full matrix to return a submatrix of.</typeparam>
	/// <param name="matrix_">The full matrix to return a submatrix of.</param>
	/// <returns>Submatrix of the correct dimensions located at the specified inclusive indices within the passed matrix.</returns>
	template<std::size_t BeginColumn, std::size_t EndColumn, std::size_t BeginRow, std::size_t EndRow, class Matrix_>
	constexpr inline typename TMPHelpers::emu_matrix_matching_template<EndColumn - BeginColumn + 1, EndRow - BeginRow + 1, typename Matrix_::value_type, Matrix_>::type
		MatrixSubMatrix
	(
		const Matrix_& matrix_
	)
	{
		// NOTE: Output type is handled the way it is to allow nice intellisense
		// --- Sometimes using a cleaner alias results in intellisense saying the alias rather than a clear output type when calling the function

		constexpr std::size_t OutColumns = EndColumn - BeginColumn + 1;
		constexpr std::size_t OutRows = EndRow - BeginRow + 1;
		if constexpr (EmuMath::TMPHelpers::is_emu_matrix_v<Matrix_>)
		{
			if constexpr (EndColumn > BeginColumn)
			{
				if constexpr (EndRow > BeginRow)
				{
					if constexpr (OutColumns <= Matrix_::num_columns)
					{
						if constexpr (OutRows <= Matrix_::num_rows)
						{
							if constexpr (EndColumn < Matrix_::num_columns)
							{
								if constexpr (EndRow < Matrix_::num_rows)
								{
									if constexpr (OutColumns == Matrix_::num_columns && OutRows == Matrix_::num_rows)
									{
										// Only reach this point if we're covering the full matrix, so quickly return a copy of the matrix instead.
										return matrix_;
									}
									else
									{
										return _underlying_matrix_funcs::_find_matrix_submatrix
										<
											BeginColumn,
											EndColumn,
											BeginRow,
											EndRow,
											Matrix_,
											typename EmuMath::TMPHelpers::emu_matrix_matching_template<OutColumns, OutRows, typename Matrix_::value_type, Matrix_>::type
										>(matrix_);
									}
								}
								else
								{
									static_assert(false, "Attempting to output a submatrix within a matrix, but the indices of the submatrix rows exceed those of the full matrix.");
									return typename EmuMath::TMPHelpers::emu_matrix_matching_template<OutColumns, OutRows, typename Matrix_::value_type, Matrix_>::type();
								}
							}
							else
							{
								static_assert(false, "Attempting to output a submatrix within a matrix, but the indices of the submatrix columns exceed those of the full matrix.");
								return typename EmuMath::TMPHelpers::emu_matrix_matching_template<OutColumns, OutRows, typename Matrix_::value_type, Matrix_>::type();
							}
						}
						else
						{
							static_assert(false, "Attempting to output a submatrix within a matrix, but the output submatrix has more rows than the full matrix.");
							return typename EmuMath::TMPHelpers::emu_matrix_matching_template<OutColumns, OutRows, typename Matrix_::value_type, Matrix_>::type();
						}
					}
					else
					{
						static_assert(false, "Attempting to output a submatrix within a matrix, but the output submatrix has more columns than the full matrix.");
						return typename EmuMath::TMPHelpers::emu_matrix_matching_template<OutColumns, OutRows, typename Matrix_::value_type, Matrix_>::type();
					}
				}
				else
				{
					static_assert(false, "Attempting to output a submatrix within a matrix, but the end row indices are not greater than the begin row indices.");
					return typename EmuMath::TMPHelpers::emu_matrix_matching_template<OutColumns, OutRows, typename Matrix_::value_type, Matrix_>::type();
				}
			}
			else
			{
				static_assert(false, "Attempting to output a submatrix within a matrix, but the end column indices are not greater than the begin column indices.");
				return typename EmuMath::TMPHelpers::emu_matrix_matching_template<OutColumns, OutRows, typename Matrix_::value_type, Matrix_>::type();
			}
		}
		else
		{
			static_assert(false, "Attempting to output a submatrix within a matrix, but passed a non-EmuMath-matrix type.");
			return typename EmuMath::TMPHelpers::emu_matrix_matching_template<OutColumns, OutRows, typename Matrix_::value_type, Matrix_>::type();
		}
	}
	/// <summary>
	/// <para> Returns a smaller matrix contained within the passed matrix once the provided column and row indices are excluded. </para>
	/// </summary>
	/// <typeparam name="Matrix_">Type of the matrix to find a submatrix within.</typeparam>
	/// <param name="matrix_">EmuMath matrix to find the specified submatrix of.</param>
	/// <returns>Submatrix contained within the passed matrix when the column at index Column_ is removed, and the row and index Row_ is removed.</returns>
	template<std::size_t Column_, std::size_t Row_, class Matrix_>
	constexpr inline typename TMPHelpers::emu_matrix_matching_template<Matrix_::num_columns - 1, Matrix_::num_rows - 1, typename Matrix_::value_type, Matrix_>::type 
		MatrixSubMatrixExcluding(const Matrix_& matrix_)
	{
		if constexpr (EmuMath::TMPHelpers::is_emu_matrix_v<Matrix_>)
		{
			if constexpr (Matrix_::num_columns != 1 && Matrix_::num_rows != 1)
			{
				if constexpr (Column_ < Matrix_::num_columns)
				{
					if constexpr (Row_ < Matrix_::num_rows)
					{
						return _underlying_matrix_funcs::_find_matrix_submatrix_exclusive
						<
							Column_,
							Row_,
							Matrix_,
							typename TMPHelpers::emu_matrix_matching_template<Matrix_::num_columns - 1, Matrix_::num_rows - 1, typename Matrix_::value_type, Matrix_>::type
						>(matrix_);
					}
					else
					{
						static_assert(false, "Attempted to get a matrix's submatrix excluding a certain column+row via MatrixSubMatrixExcluding, but provided a row index that exceeds the matrix's indices.");
						return typename TMPHelpers::emu_matrix_matching_template<Matrix_::num_columns - 1, Matrix_::num_rows - 1, typename Matrix_::value_type, Matrix_>::type();
					}
				}
				else
				{
					static_assert(false, "Attempted to get a matrix's submatrix excluding a certain column+row via MatrixSubMatrixExcluding, but provided a column index that exceeds the matrix's indices.");
					return typename TMPHelpers::emu_matrix_matching_template<Matrix_::num_columns - 1, Matrix_::num_rows - 1, typename Matrix_::value_type, Matrix_>::type();
				}
			}
			else
			{
				static_assert(false, "Attempted to get a matrix's submatrix excluding a certain column+row via MatrixSubMatrixExcluding, but provided a matrix which cannot contain any smaller matrix after exclusion.");
				return typename TMPHelpers::emu_matrix_matching_template<Matrix_::num_columns - 1, Matrix_::num_rows - 1, typename Matrix_::value_type, Matrix_>::type();
			}
		}
		else
		{
			static_assert(false, "Attempted to get a matrix's submatrix excluding a certain column+row via MatrixSubMatrixExcluding, but the provided argument was not an EmuMath matrix.");
			return typename TMPHelpers::emu_matrix_matching_template<Matrix_::num_columns - 1, Matrix_::num_rows - 1, typename Matrix_::value_type, Matrix_>::type();
		}
	}
#pragma endregion
}

#endif
