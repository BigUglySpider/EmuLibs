#ifndef EMU_MATH_MATRIX_HELPERS_H_INC_
#define EMU_MATH_MATRIX_HELPERS_H_INC_

#include "MatrixHelpersUnderlying.h"

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

	

#pragma region ARITHMETIC
	/// <summary> Adds respective elements of the passed matrices together and outputs them in a new matrix. </summary>
	/// <typeparam name="value_type">Type contained within the passed matrices.</typeparam>
	/// <param name="lhs">Left-hand EmuMath matrix in the addition.</param>
	/// <param name="rhs">Right-hand EmuMath matrix in the addition.</param>
	/// <returns>Matrix containing the results of the addition.</returns>
	template<std::size_t num_columns, std::size_t num_rows, typename value_type>
	constexpr EmuMath::MatrixCM<num_columns, num_rows, value_type> MatrixAddition
	(
		const EmuMath::MatrixCM<num_columns, num_rows, value_type>& lhs,
		const EmuMath::MatrixCM<num_columns, num_rows, value_type>& rhs
	)
	{
		return _underlying_matrix_funcs::_perform_basic_matrix_arithmetic<std::plus<void>>(lhs, rhs);
	}

	/// <summary> Subtracts respective elements of the passed matrices together and outputs them in a new matrix. </summary>
	/// <typeparam name="value_type">Type contained within the passed matrices.</typeparam>
	/// <param name="lhs">Left-hand EmuMath matrix in the subtraction.</param>
	/// <param name="rhs">Right-hand EmuMath matrix in the subtraction.</param>
	/// <returns>Matrix containing the results of the subtraction.</returns>
	template<std::size_t num_columns, std::size_t num_rows, typename value_type>
	constexpr EmuMath::MatrixCM<num_columns, num_rows, value_type> MatrixSubtraction
	(
		const EmuMath::MatrixCM<num_columns, num_rows, value_type>& lhs,
		const EmuMath::MatrixCM<num_columns, num_rows, value_type>& rhs
	)
	{
		return _underlying_matrix_funcs::_perform_basic_matrix_arithmetic<std::minus<void>>(lhs, rhs);
	}

	/// <summary> Negates all elements within the passed matrix (i.e. element[x][y] is set to -element[x][y]). </summary>
	/// <typeparam name="value_type">Type contained within the passed matrix.</typeparam>
	/// <param name="matrix_">EmuMath matrix to negate.</param>
	/// <returns>Negated variant of the passed matrix.</returns>
	template<std::size_t num_columns, std::size_t num_rows, typename value_type>
	constexpr EmuMath::MatrixCM<num_columns, num_rows, value_type> MatrixNegation(const EmuMath::MatrixCM<num_columns, num_rows, value_type>& matrix_)
	{
		return _underlying_matrix_funcs::_perform_basic_matrix_arithmetic<std::negate<void>>(matrix_);
	}

	/// <summary> Multiplies all elements within the passed matrix by the passed scalar mult. </summary>
	/// <typeparam name="ScalarMultiplier">Type of scalar provided. Must be an arithmetic type.</typeparam>
	/// <typeparam name="value_type">Type contained within the passed matrix.</typeparam>
	/// <param name="matrix_">EmuMath matrix to multiply.</param>
	/// <param name="mult">Value to multiply all of the passed matrix's elements by.</param>
	/// <returns>Matrix containing the results of the multiplication.</returns>
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
	/// <para> Multiplies the two passed matrices and returns the result as another matrix. </para>
	/// <para> Note that matrix multiplication is non-commutative, and (lhs * rhs) != (rhs * lhs) in most cases. </para>
	/// </summary>
	/// <typeparam name="value_type">Type contained within the passed matrices.</typeparam>
	/// <param name="lhs">Left-hand matrix in this multiplication.</param>
	/// <param name="rhs">Right-hand matrix in this multiplication.</param>
	/// <returns>Matrix containing the results of the multiplication lhs * rhs.</returns>
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
	/// <summary> Sets respective elements in the left-hand matrix to match those of the right-hand matrix. </summary>
	/// <typeparam name="LhsMatrix_">Type of the left-hand matrix in this set.</typeparam>
	/// <typeparam name="RhsMatrix_">Type of the right-hand matrix in this set.</typeparam>
	/// <param name="lhs_">EmuMath matrix to set the values of.</param>
	/// <param name="rhs_">EmuMath matrix to copy the values of.</param>
	/// <returns>Reference to lhs_ after it has been fully set.</returns>
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
				static_assert(false, "Attempted to get the identity matrix of an EmuMath matrix that does not have square dimensions (i.e. num_columns != num_rows).");
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

	template<class Matrix_>
	constexpr inline Matrix_ MatrixMinorsLaplace(const Matrix_& matrix_)
	{
		if constexpr (EmuMath::TMPHelpers::is_emu_matrix_v<Matrix_>)
		{
			if constexpr (Matrix_::is_square)
			{
				Matrix_ out_ = Matrix_();
				_underlying_matrix_funcs::_calculate_matrix_of_minors_laplace<0, 0, Matrix_>(matrix_, out_);
				return out_;
			}
			else
			{
				static_assert(false, "Attempted to calculate a matrix of minors for a non-square matrix.");
				return Matrix_();
			}
		}
		else
		{
			static_assert(false, "Attempted to calculate a matrix of minors for a non-EmuMath-matrix type.");
			return Matrix_();
		}
	}

	template<class Matrix_>
	constexpr inline Matrix_ MatrixCofactorsLaplace(const Matrix_& matrix_)
	{
		if constexpr (EmuMath::TMPHelpers::is_emu_matrix_v<Matrix_>)
		{
			Matrix_ out_ = Matrix_();
			_underlying_matrix_funcs::_create_cofactor_matrix<0, 0, Matrix_>(MatrixMinorsLaplace(matrix_), out_);
			return out_;
		}
		else
		{
			static_assert(false, "Attempted to retrieve a matrix of cofactors via a non-EmuMath-matrix type.");
			return Matrix_();
		}
	}

	template<class Matrix_>
	constexpr inline Matrix_ MatrixAdjugateLaplace(const Matrix_& matrix_)
	{
		return MatrixTranspose(MatrixCofactorsLaplace(matrix_));
	}

	/// <summary>
	/// <para> Calculates the determinant of the passed matrix, outputting it as the provided Out_ type (a floating-point type is recommended). </para>
	/// <para> The determinant is only defined for square matrices. As such, this function may only be validly used with a square matrix. </para>
	/// <para> This function uses the Laplace Expansion method to calculate the determinant. This method takes exponentially longer the larger a matrix is. </para>
	/// </summary>
	/// <typeparam name="Out_">Type to output as. Preference should be given to float or double.</typeparam>
	/// <typeparam name="Matrix_">Type of matrix to find the determinant of.</typeparam>
	/// <param name="matrix_">Square EmuMath matrix to calculate the determinant of.</param>
	/// <returns>Determinant of the passed matrix, represented as the provided Out_ type.</returns>
	template<typename Out_ = float, class Matrix_>
	constexpr inline Out_ MatrixDeterminantLaplace(const Matrix_& matrix_)
	{
		if constexpr (_underlying_matrix_funcs::_matrix_valid_for_determinant<Matrix_>())
		{
			Out_ out_ = Out_();
			_underlying_matrix_funcs::_calculate_matrix_determinant_laplace<0, Out_, Matrix_>(matrix_, out_);
			return out_;
		}
		else
		{
			return Out_();
		}
	}

	template<typename Determinant_ = double, class Matrix_>
	constexpr inline Matrix_ MatrixInverseLaplace(const Matrix_& matrix_, Determinant_& outDeterminant)
	{
		if constexpr (_underlying_matrix_funcs::_matrix_valid_for_inversion<Matrix_>())
		{
			outDeterminant = MatrixDeterminantLaplace<Determinant_, Matrix_>(matrix_);
			if (outDeterminant != Determinant_(0))
			{
				return MatrixMultiplication(MatrixAdjugateLaplace(matrix_), Determinant_(1) / outDeterminant);
			}
			else
			{
				return matrix_;
			}
		}
		else
		{
			return Matrix_();
		}
	}
	template<typename Determinant_ = float, class Matrix_ = void>
	constexpr inline Matrix_ MatrixInverseLaplace(const Matrix_& matrix_)
	{
		Determinant_ dummy_ = Determinant_();
		return MatrixInverseLaplace<Determinant_, Matrix_>(matrix_, dummy_);
	}
#pragma endregion
}

#endif
