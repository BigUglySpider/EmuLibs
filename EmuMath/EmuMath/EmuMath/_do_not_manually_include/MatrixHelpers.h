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
					_execute_basic_matrix_arithmetic_on_contained_scalars_until_complete<Row_ + 1, ArithmeticFunc_>(outColumn_, lhsColumn, rhs, func_);
				}
				else
				{
					outColumn_[Row_] = func_(lhsColumn[Row_], rhs[Row_]);
					_execute_basic_matrix_arithmetic_on_contained_scalars_until_complete<Row_ + 1, ArithmeticFunc_>(outColumn_, lhsColumn, rhs, func_);
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
				_execute_basic_matrix_arithmetic_on_contained_scalars_until_complete<Row_ + 1, ArithmeticFunc_>(outColumn_, matrix_, func_);
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
						_execute_basic_matrix_arithmetic_on_contained_scalars_until_complete<0, ArithmeticFunc_>
						(
							out_.columns[Column_],
							lhs.columns[Column_],
							rhs.columns[Column_],
							func_
						);
					}
					else if constexpr (std::is_arithmetic_v<std::remove_reference_t<Rhs_>>)
					{
						_execute_basic_matrix_arithmetic_on_contained_scalars_until_complete<0, ArithmeticFunc_>
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
#pragma endregion

#pragma region MATRIX_OPERATIONS
	template<std::size_t num_columns, std::size_t num_rows, typename value_type>
	constexpr EmuMath::MatrixCM<num_rows, num_columns, value_type> MatrixTranspose(const EmuMath::MatrixCM<num_columns, num_rows, value_type>& matrix_)
	{
		EmuMath::MatrixCM<num_rows, num_columns, value_type> out_ = EmuMath::MatrixCM<num_rows, num_columns, value_type>();
		_underlying_matrix_funcs::_execute_matrix_transposition<0>(out_, matrix_);
		return out_;
	}

	template<typename OutT_ = float, typename Matrix_ = void>
	constexpr inline OutT_ MatrixTrace(const Matrix_& matrix_)
	{
		if constexpr (EmuMath::TMPHelpers::is_emu_matrix_v<Matrix_>)
		{
			if constexpr (Matrix_::num_rows == Matrix_::num_columns)
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
#pragma endregion
}

#endif
