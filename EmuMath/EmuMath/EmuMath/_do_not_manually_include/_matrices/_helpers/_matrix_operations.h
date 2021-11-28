#ifndef EMU_MATH_MATRIX_HELPERS_MATRIX_OPERATIONS_H_INC_
#define EMU_MATH_MATRIX_HELPERS_MATRIX_OPERATIONS_H_INC_ 1

#include "_common_matrix_helper_includes.h"

namespace EmuMath::Helpers
{
	/// <summary>
	/// <para> Determines the identity matrix of an EmuMath matrix with the provided dimensions. </para>
	/// <para> Instead of passing dimensions and other matrix focused data, a matrix type may be provided as a template argument to determine defaults. </para>
	/// <para> If a specific matrix's identity is desired, but the type is unknown, the matrix itself may be passed to this function to determine default arguments. </para>
	/// </summary>
	/// <typeparam name="out_contained_type">Type to be contained in the output identity matrix.</typeparam>
	/// <returns>Identity matrix of the provided size, where all elements are 0 excluding the main diagonal, along which all elements are 1.</returns>
	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename out_contained_type, bool OutColumnMajor_ = true>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, out_contained_type, OutColumnMajor_> matrix_identity()
	{
		if constexpr (OutNumColumns_ == OutNumRows_)
		{
			return _underlying_matrix_funcs::_make_identity_matrix<EmuMath::Matrix<OutNumColumns_, OutNumRows_, out_contained_type, OutColumnMajor_>>();
		}
		else
		{
			static_assert(false, "Attempted to acquire an EmuMath identity matrix, but the provided matrix dimensions were non-square. An identity matrix must be square.");
		}
	}
	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename out_contained_type, bool OutColumnMajor_, class Matrix_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, out_contained_type, OutColumnMajor_> matrix_identity()
	{
		if constexpr (EmuMath::TMP::is_emu_matrix_v<Matrix_>)
		{
			return matrix_identity<OutNumColumns_, OutNumRows_, out_contained_type, OutColumnMajor_>();
		}
		else
		{
			static_assert(false, "Attempted to acquire an EmuMath identity matrix, but provided a non-EmuMath-matrix type to determine the identity of.");
		}
	}
	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename out_contained_type, bool OutColumnMajor_, class Matrix_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, out_contained_type, OutColumnMajor_> matrix_identity
	(
		const Matrix_& matrix_
	)
	{
		if constexpr (EmuMath::TMP::is_emu_matrix_v<Matrix_>)
		{
			return matrix_identity<OutNumColumns_, OutNumRows_, out_contained_type, OutColumnMajor_>();
		}
		else
		{
			static_assert(false, "Attempted to acquire an EmuMath identity matrix, but provided a non-EmuMath-matrix type to determine the identity of.");
		}
	}
	template<typename out_contained_type, bool OutColumnMajor_, class Matrix_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<Matrix_::num_columns, Matrix_::num_rows, out_contained_type, OutColumnMajor_> matrix_identity()
	{
		if constexpr (EmuMath::TMP::is_emu_matrix_v<Matrix_>)
		{
			return matrix_identity<Matrix_::num_columns, Matrix_::num_rows, out_contained_type, OutColumnMajor_>();
		}
		else
		{
			static_assert(false, "Attempted to acquire an EmuMath identity matrix, but provided a non-EmuMath-matrix type to determine the identity of.");
		}
	}
	template<typename out_contained_type, bool OutColumnMajor_, class Matrix_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<Matrix_::num_columns, Matrix_::num_rows, out_contained_type, OutColumnMajor_> matrix_identity
	(
		const Matrix_& matrix_
	)
	{
		if constexpr (EmuMath::TMP::is_emu_matrix_v<Matrix_>)
		{
			return matrix_identity<Matrix_::num_columns, Matrix_::num_rows, out_contained_type, OutColumnMajor_>();
		}
		else
		{
			static_assert(false, "Attempted to acquire an EmuMath identity matrix, but provided a non-EmuMath-matrix type to determine the identity of.");
		}
	}
	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, bool OutColumnMajor_, class Matrix_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, typename Matrix_::value_type, OutColumnMajor_> matrix_identity()
	{
		if constexpr (EmuMath::TMP::is_emu_matrix_v<Matrix_>)
		{
			return matrix_identity<OutNumColumns_, OutNumRows_, typename Matrix_::value_type, OutColumnMajor_>();
		}
		else
		{
			static_assert(false, "Attempted to acquire an EmuMath identity matrix, but provided a non-EmuMath-matrix type to determine the identity of.");
		}
	}
	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, bool OutColumnMajor_, class Matrix_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, typename Matrix_::value_type, OutColumnMajor_> matrix_identity
	(
		const Matrix_& matrix_
	)
	{
		if constexpr (EmuMath::TMP::is_emu_matrix_v<Matrix_>)
		{
			return matrix_identity<OutNumColumns_, OutNumRows_, typename Matrix_::value_type, OutColumnMajor_>();
		}
		else
		{
			static_assert(false, "Attempted to acquire an EmuMath identity matrix, but provided a non-EmuMath-matrix type to determine the identity of.");
		}
	}
	template<bool OutColumnMajor_, class Matrix_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<Matrix_::num_columns, Matrix_::num_rows, typename Matrix_::value_type, OutColumnMajor_> matrix_identity()
	{
		if constexpr (EmuMath::TMP::is_emu_matrix_v<Matrix_>)
		{
			return matrix_identity<Matrix_::num_columns, Matrix_::num_rows, typename Matrix_::value_type, OutColumnMajor_>();
		}
		else
		{
			static_assert(false, "Attempted to acquire an EmuMath identity matrix, but provided a non-EmuMath-matrix type to determine the identity of.");
		}
	}
	template<bool OutColumnMajor_, class Matrix_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<Matrix_::num_columns, Matrix_::num_rows, typename Matrix_::value_type, OutColumnMajor_> matrix_identity
	(
		const Matrix_& matrix_
	)
	{
		if constexpr (EmuMath::TMP::is_emu_matrix_v<Matrix_>)
		{
			return matrix_identity<Matrix_::num_columns, Matrix_::num_rows, typename Matrix_::value_type, OutColumnMajor_>();
		}
		else
		{
			static_assert(false, "Attempted to acquire an EmuMath identity matrix, but provided a non-EmuMath-matrix type to determine the identity of.");
		}
	}
	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename out_contained_type, class Matrix_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, out_contained_type, Matrix_::is_column_major> matrix_identity()
	{
		if constexpr (EmuMath::TMP::is_emu_matrix_v<Matrix_>)
		{
			return matrix_identity<OutNumColumns_, OutNumRows_, out_contained_type, Matrix_::is_column_major>();
		}
		else
		{
			static_assert(false, "Attempted to acquire an EmuMath identity matrix, but provided a non-EmuMath-matrix type to determine the identity of.");
		}
	}
	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename out_contained_type, class Matrix_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, out_contained_type, Matrix_::is_column_major> matrix_identity
	(
		const Matrix_& matrix_
	)
	{
		if constexpr (EmuMath::TMP::is_emu_matrix_v<Matrix_>)
		{
			return matrix_identity<OutNumColumns_, OutNumRows_, out_contained_type, Matrix_::is_column_major>();
		}
		else
		{
			static_assert(false, "Attempted to acquire an EmuMath identity matrix, but provided a non-EmuMath-matrix type to determine the identity of.");
		}
	}
	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, class Matrix_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, typename Matrix_::value_type, Matrix_::is_column_major> matrix_identity()
	{
		if constexpr (EmuMath::TMP::is_emu_matrix_v<Matrix_>)
		{
			return matrix_identity<OutNumColumns_, OutNumRows_, typename Matrix_::value_type, Matrix_::is_column_major>();
		}
		else
		{
			static_assert(false, "Attempted to acquire an EmuMath identity matrix, but provided a non-EmuMath-matrix type to determine the identity of.");
		}
	}
	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, class Matrix_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, typename Matrix_::value_type, Matrix_::is_column_major> matrix_identity
	(
		const Matrix_& matrix_
	)
	{
		if constexpr (EmuMath::TMP::is_emu_matrix_v<Matrix_>)
		{
			return matrix_identity<OutNumColumns_, OutNumRows_, typename Matrix_::value_type, Matrix_::is_column_major>();
		}
		else
		{
			static_assert(false, "Attempted to acquire an EmuMath identity matrix, but provided a non-EmuMath-matrix type to determine the identity of.");
		}
	}
	template<typename out_contained_type, class Matrix_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<Matrix_::num_columns, Matrix_::num_rows, out_contained_type, Matrix_::is_column_major> matrix_identity()
	{
		if constexpr (EmuMath::TMP::is_emu_matrix_v<Matrix_>)
		{
			return matrix_identity<Matrix_::num_columns, Matrix_::num_rows, out_contained_type, Matrix_::is_column_major>();
		}
		else
		{
			static_assert(false, "Attempted to acquire an EmuMath identity matrix, but provided a non-EmuMath-matrix type to determine the identity of.");
		}
	}
	template<typename out_contained_type, class Matrix_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<Matrix_::num_columns, Matrix_::num_rows, out_contained_type, Matrix_::is_column_major> matrix_identity
	(
		const Matrix_& matrix_
	)
	{
		if constexpr (EmuMath::TMP::is_emu_matrix_v<Matrix_>)
		{
			return matrix_identity<Matrix_::num_columns, Matrix_::num_rows, out_contained_type, Matrix_::is_column_major>();
		}
		else
		{
			static_assert(false, "Attempted to acquire an EmuMath identity matrix, but provided a non-EmuMath-matrix type to determine the identity of.");
		}
	}
	template<class Matrix_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<Matrix_::num_columns, Matrix_::num_rows, typename Matrix_::value_type, Matrix_::is_column_major> matrix_identity()
	{
		if constexpr (EmuMath::TMP::is_emu_matrix_v<Matrix_>)
		{
			return matrix_identity<Matrix_::num_columns, Matrix_::num_rows, typename Matrix_::value_type, Matrix_::is_column_major>();
		}
		else
		{
			static_assert(false, "Attempted to acquire an EmuMath identity matrix, but provided a non-EmuMath-matrix type to determine the identity of.");
		}
	}
	template<class Matrix_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<Matrix_::num_columns, Matrix_::num_rows, typename Matrix_::value_type, Matrix_::is_column_major> matrix_identity
	(
		const Matrix_& matrix_
	)
	{
		if constexpr (EmuMath::TMP::is_emu_matrix_v<Matrix_>)
		{
			return matrix_identity<Matrix_::num_columns, Matrix_::num_rows, typename Matrix_::value_type, Matrix_::is_column_major>();
		}
		else
		{
			static_assert(false, "Attempted to acquire an EmuMath identity matrix, but provided a non-EmuMath-matrix type to determine the identity of.");
		}
	}

	/// <summary>
	/// <para> Transposes the passed matrix, effectively turning columns into rows and vice versa. </para>
	/// <para> The output matrix will always be of dimensions [Y, X] when provided an input matrix of dimensions [X, Y]. </para>
	/// </summary>
	/// <typeparam name="out_contained_type">Type to be contained in the output transpose matrix.</typeparam>
	/// <typeparam name="Matrix_">Type of matrix to tranpose.</typeparam>
	/// <param name="matrix_">EmuMath matrix to transpose.</param>
	/// <returns>Tranposed form of the passed EmuMath matrix.</returns>
	template<typename out_contained_type, bool OutColumnMajor_, class Matrix_>
	[[nodiscard]] constexpr inline typename EmuMath::TMP::emu_matrix_transpose<out_contained_type, OutColumnMajor_, Matrix_>::type 
	matrix_transpose
	(
		const Matrix_& matrix_
	)
	{
		if constexpr (EmuMath::TMP::is_emu_matrix_v<Matrix_>)
		{
			return _underlying_matrix_funcs::_transpose_matrix
			<
				typename EmuMath::TMP::emu_matrix_transpose<out_contained_type, OutColumnMajor_, Matrix_>::type,
				Matrix_
			>(matrix_);
		}
		else
		{
			static_assert(false, "Attempted to form the transpose of a matrix, but the passed argument was not an EmuMath matrix.");
		}
	}
	template<typename out_contained_type, class Matrix_>
	[[nodiscard]] constexpr inline typename EmuMath::TMP::emu_matrix_transpose<out_contained_type, Matrix_::is_column_major, Matrix_>::type
	matrix_transpose
	(
		const Matrix_& matrix_
	)
	{
		return matrix_transpose<out_contained_type, Matrix_::is_column_major, Matrix_>(matrix_);
	}
	template<bool OutColumnMajor_, class Matrix_>
	[[nodiscard]] constexpr inline typename EmuMath::TMP::emu_matrix_transpose<typename Matrix_::value_type, OutColumnMajor_, Matrix_>::type
	matrix_transpose
	(
		const Matrix_& matrix_
	)
	{
		return matrix_transpose<typename Matrix_::value_type, OutColumnMajor_, Matrix_>(matrix_);
	}
	template<class Matrix_>
	[[nodiscard]] constexpr inline typename EmuMath::TMP::emu_matrix_transpose<typename Matrix_::value_type, Matrix_::is_column_major, Matrix_>::type
	matrix_transpose
	(
		const Matrix_& matrix_
	)
	{
		return matrix_transpose<typename Matrix_::value_type, Matrix_::is_column_major, Matrix_>(matrix_);
	}

	/// <summary>
	/// <para> Calculates the trace of the passed matrix (i.e. the sum of all diagonal elements from the top-left to the bottom right). </para>
	/// <para> The trace is only defined for a square matrix, and as such this function may only be validly executed on square matrices. </para>
	/// </summary>
	/// <typeparam name="OutT_">Type to output the trace as.</typeparam>
	/// <typeparam name="Matrix_">Type of matrix to calculate the trace of.</typeparam>
	/// <param name="matrix_">EmuMath matrix to calculate the trace of.</param>
	/// <returns>Trace of the passed matrix, represented as the provided OutT_.</returns>
	template<typename OutT_, class Matrix_>
	[[nodiscard]] constexpr inline OutT_ matrix_trace(const Matrix_& matrix_)
	{
		if constexpr (EmuMath::TMP::is_emu_matrix_v<Matrix_>)
		{
			if constexpr (Matrix_::is_square)
			{
				return _underlying_matrix_funcs::_calculate_matrix_trace<OutT_, Matrix_>(matrix_);
			}
			else
			{
				static_assert(false, "Attempted to calculate the trace of an EmuMath matrix that is not square. Only square matrices have a mathematically defined trace.");
			}
		}
		else
		{
			static_assert(false, "Attempted to calculate the trace of a matrix, but a non-EmuMath-matrix argument was passed.");
		}
	}
	template<class Matrix_>
	[[nodiscard]] constexpr inline typename Matrix_::value_type matrix_trace(const Matrix_& matrix_)
	{
		return matrix_trace<typename Matrix_::value_type, Matrix_>(matrix_);
	}

	/// <summary>
	/// <para> Retrieves a smaller matrix from within the passed matrix, which is formed of all elements excluding those in the provided row and column. </para>
	/// <para> This will always yield a matrix of size [X-1, Y-1] when performed on a matrix of size [X, Y]. </para>
	/// </summary>
	/// <typeparam name="out_contained_type">Type to be contained in the output submatrix.</typeparam>
	/// <typeparam name="Matrix_">Type of matrix to retrieve a submatrix from.</typeparam>
	/// <param name="matrix_">EmuMath matrix to retrieve the specified submatrix from.</param>
	/// <returns>Copy of the submatrix within the passed EmuMath matrix, formed of all elements excluding those in the provided column or row indices.</returns>
	template<std::size_t ExcludeColumn_, std::size_t ExcludeRow_, typename out_contained_type, bool OutColumnMajor_, class Matrix_>
	[[nodiscard]] constexpr inline typename EmuMath::TMP::emu_matrix_submatrix_excluding_element_region<out_contained_type, OutColumnMajor_, Matrix_>::type
	matrix_submatrix_exclusive
	(
		Matrix_& matrix_
	)
	{
		if constexpr (EmuMath::TMP::is_emu_matrix_v<Matrix_>)
		{
			if constexpr (!std::is_same_v<typename EmuMath::TMP::emu_matrix_submatrix_excluding_element_region<out_contained_type, OutColumnMajor_, Matrix_>::type, void>)
			{
				if constexpr (ExcludeColumn_ < Matrix_::num_columns)
				{
					if constexpr (ExcludeRow_ < Matrix_::num_rows)
					{
						return _underlying_matrix_funcs::_get_submatrix_excluding_element_region
						<
							ExcludeColumn_,
							ExcludeRow_,
							typename EmuMath::TMP::emu_matrix_submatrix_excluding_element_region<out_contained_type, OutColumnMajor_, Matrix_>::type,
							Matrix_
						>(matrix_);
					}
					else
					{
						static_assert(false, "Attempted to retrieve a submatrix excluding an element's regions within an EmuMath matrix, but the provided row index to ignore exceeded the range of the passed matrix's rows.");
					}
				}
				else
				{
					static_assert(false, "Attempted to retrieve a submatrix excluding an element's regions within an EmuMath matrix, but the provided column index to ignore exceeded the range of the passed matrix's columns.");
				}
			}
			else
			{
				static_assert(false, "Attempted to retrieve a submatrix excluding an element's regions with an EmuMath matrix, but the provided matrix cannot supply a submatrix.");
			}
		}
		else
		{
			static_assert(false, "Attempted to retrieve a submatrix excluding an element's regions within a matrix, but the provided argument was not an EmuMath matrix.");
		}
	}
	template<std::size_t ExcludeColumn_, std::size_t ExcludeRow_, typename out_contained_type, class Matrix_>
	[[nodiscard]] constexpr inline typename EmuMath::TMP::emu_matrix_submatrix_excluding_element_region<out_contained_type, Matrix_::is_column_major, Matrix_>::type
	matrix_submatrix_exclusive
	(
		Matrix_& matrix_
	)
	{
		return matrix_submatrix_exclusive<ExcludeColumn_, ExcludeRow_, out_contained_type, Matrix_::is_column_major, Matrix_>(matrix_);
	}
	template<std::size_t ExcludeColumn_, std::size_t ExcludeRow_, typename out_contained_type, class Matrix_>
	[[nodiscard]] constexpr inline typename EmuMath::TMP::emu_matrix_submatrix_excluding_element_region<out_contained_type, Matrix_::is_column_major, Matrix_>::type
	matrix_submatrix_exclusive
	(
		const Matrix_& matrix_
	)
	{
		return matrix_submatrix_exclusive<ExcludeColumn_, ExcludeRow_, out_contained_type, Matrix_::is_column_major, const Matrix_>(matrix_);
	}
	template<std::size_t ExcludeColumn_, std::size_t ExcludeRow_, bool OutColumnMajor_, class Matrix_>
	[[nodiscard]] constexpr inline typename EmuMath::TMP::emu_matrix_submatrix_excluding_element_region<typename Matrix_::value_type, OutColumnMajor_, Matrix_>::type
	matrix_submatrix_exclusive
	(
		Matrix_& matrix_
	)
	{
		return matrix_submatrix_exclusive<ExcludeColumn_, ExcludeRow_, typename Matrix_::value_type, OutColumnMajor_, Matrix_>(matrix_);
	}
	template<std::size_t ExcludeColumn_, std::size_t ExcludeRow_, bool OutColumnMajor_, class Matrix_>
	[[nodiscard]] constexpr inline typename EmuMath::TMP::emu_matrix_submatrix_excluding_element_region<typename Matrix_::value_type, OutColumnMajor_, Matrix_>::type
	matrix_submatrix_exclusive
	(
		const Matrix_& matrix_
	)
	{
		return matrix_submatrix_exclusive<ExcludeColumn_, ExcludeRow_, typename Matrix_::value_type, OutColumnMajor_, const Matrix_>(matrix_);
	}
	template<std::size_t ExcludeColumn_, std::size_t ExcludeRow_, class Matrix_>
	[[nodiscard]] constexpr inline typename EmuMath::TMP::emu_matrix_submatrix_excluding_element_region<typename Matrix_::value_type, Matrix_::is_column_major, Matrix_>::type
	matrix_submatrix_exclusive
	(
		Matrix_& matrix_
	)
	{
		return matrix_submatrix_exclusive<ExcludeColumn_, ExcludeRow_, typename Matrix_::value_type, Matrix_::is_column_major, Matrix_>(matrix_);
	}
	template<std::size_t ExcludeColumn_, std::size_t ExcludeRow_, class Matrix_>
	[[nodiscard]] constexpr inline typename EmuMath::TMP::emu_matrix_submatrix_excluding_element_region<typename Matrix_::value_type, Matrix_::is_column_major, Matrix_>::type
	matrix_submatrix_exclusive
	(
		const Matrix_& matrix_
	)
	{
		return matrix_submatrix_exclusive<ExcludeColumn_, ExcludeRow_, typename Matrix_::value_type, Matrix_::is_column_major, const Matrix_>(matrix_);
	}

	/// <summary>
	/// <para> Calculates the determinant of the passed matrix using Laplace Expansion. </para>
	/// <para> NOTE: Laplace Expansion grows exponentially more expensive as the size of a matrix increases. </para>
	/// </summary>
	/// <typeparam name="OutDet_">Type to output the passed matrix's determinant as.</typeparam>
	/// <typeparam name="Matrix_">Type of matrix to calculate the determinant of.</typeparam>
	/// <param name="matrix_">EmuMath matrix to calculate the determinant of.</param>
	/// <returns>Determinant of the passed EmuMath matrix, represented as the provided OutDet_ type.</returns>
	template<typename OutDet_, class Matrix_>
	[[nodiscard]] constexpr inline OutDet_ matrix_determinant_laplace(const Matrix_& matrix_)
	{
		if constexpr (EmuMath::TMP::is_emu_matrix_v<Matrix_>)
		{
			if constexpr (Matrix_::is_square)
			{
				return _underlying_matrix_funcs::_calculate_matrix_determinant_laplace<OutDet_, Matrix_>(matrix_);
			}
			else
			{
				static_assert(false, "Attempted to calculate the determinant of an EmuMath matrix that is not square. Only square matrices have a mathematically defined determinant.");
			}
		}
		else
		{
			static_assert(false, "Attempted to calculate a matrix's determinant, but a non-EmuMath-matrix argument was passed.");
		}
	}
	template<class Matrix_>
	[[nodiscard]] constexpr inline typename Matrix_::preferred_floating_point matrix_determinant_laplace(const Matrix_& matrix_)
	{
		return matrix_determinant_laplace<typename Matrix_::preferred_floating_point, Matrix_>(matrix_);
	}

	/// <summary>
	/// <para> Calculates the matrix of minors to the passed matrix using Laplace Expansion. </para>
	/// <para> Each element in the output matrix may be summarised as the determinant of the submatrix which excludes said element's column and row. </para>
	/// <para> NOTE: Laplace Expansion grows exponentially more expensive as the size of a matrix increases. </para>
	/// </summary>
	/// <typeparam name="out_contained_type">Type to be contained in the output minor matrix.</typeparam>
	/// <typeparam name="Matrix_">Matrix to calculate the matrix of minors to.</typeparam>
	/// <param name="matrix_">EmuMath matrix to find the matrix of minors to.</param>
	/// <returns>Matrix of minors to the passed EmuMath matrix.</returns>
	template<typename out_contained_type, bool OutColumnMajor_, class Matrix_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<Matrix_::num_columns, Matrix_::num_rows, out_contained_type, OutColumnMajor_> matrix_minors_laplace
	(
		const Matrix_& matrix_
	)
	{
		if constexpr (EmuMath::TMP::is_emu_matrix_v<Matrix_>)
		{
			if constexpr (Matrix_::is_square)
			{
				return _underlying_matrix_funcs::_calculate_matrix_of_minors_laplace
				<
					EmuMath::Matrix<Matrix_::num_columns, Matrix_::num_rows, out_contained_type, OutColumnMajor_>,
					Matrix_
				>(matrix_);
			}
			else
			{
				static_assert(false, "Attempted to calculate a matrix of minors, but provided a non-square EmuMath matrix. Only square matrices are valid for this operation.");
			}
		}
		else
		{
			static_assert(false, "Attempted to calculate a matrix of minors, but provided a non-EmuMath-matrix argument.");
		}
	}
	template<bool OutColumnMajor_, class Matrix_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<Matrix_::num_columns, Matrix_::num_rows, typename Matrix_::preferred_floating_point, OutColumnMajor_> matrix_minors_laplace
	(
		const Matrix_& matrix_
	)
	{
		return matrix_minors_laplace<typename Matrix_::preferred_floating_point, OutColumnMajor_, Matrix_>(matrix_);
	}
	template<typename out_contained_type, class Matrix_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<Matrix_::num_columns, Matrix_::num_rows, out_contained_type, Matrix_::is_column_major> matrix_minors_laplace
	(
		const Matrix_& matrix_
	)
	{
		return matrix_minors_laplace<out_contained_type, Matrix_::is_column_major, Matrix_>(matrix_);
	}
	template<class Matrix_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<Matrix_::num_columns, Matrix_::num_rows, typename Matrix_::preferred_floating_point, Matrix_::is_column_major>
	matrix_minors_laplace
	(
		const Matrix_& matrix_
	)
	{
		return matrix_minors_laplace<typename Matrix_::preferred_floating_point, Matrix_::is_column_major, Matrix_>(matrix_);
	}

	/// <summary>
	/// <para> Calculates the matrix of cofactors to the passed matrix using Laplace Expansion. </para>
	/// <para> NOTE: Laplace Expansion grows exponentially more expensive as the size of a matrix increases. </para>
	/// </summary>
	/// <typeparam name="out_contained_type">Type to be contained in the output cofactor matrix.</typeparam>
	/// <typeparam name="Matrix_">Matrix to calculate the matrix of cofactors to.</typeparam>
	/// <param name="matrix_">EmuMath matrix to find the matrix of cofactors to.</param>
	/// <returns>Matrix of cofactors to the passed EmuMath matrix.</returns>
	template<typename out_contained_type, bool OutColumnMajor_, class Matrix_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<Matrix_::num_columns, Matrix_::num_rows, out_contained_type, OutColumnMajor_> matrix_cofactors_laplace
	(
		const Matrix_& matrix_
	)
	{
		if constexpr (EmuMath::TMP::is_emu_matrix_v<Matrix_>)
		{
			if constexpr (Matrix_::is_square)
			{
				return _underlying_matrix_funcs::_calculate_matrix_of_cofactors_laplace
				<
					EmuMath::Matrix<Matrix_::num_columns, Matrix_::num_rows, out_contained_type, OutColumnMajor_>,
					Matrix_
				>(matrix_);
			}
			else
			{
				static_assert(false, "Attempted to calculate a matrix of cofactors, but provided a non-square EmuMath matrix. Only square matrices are valid for this operation.");
			}
		}
		else
		{
			static_assert(false, "Attempted to calculate a matrix of cofactors, but provided a non-EmuMath-matrix argument.");
		}
	}
	template<bool OutColumnMajor_, class Matrix_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<Matrix_::num_columns, Matrix_::num_rows, typename Matrix_::preferred_floating_point, OutColumnMajor_>
	matrix_cofactors_laplace
	(
		const Matrix_& matrix_
	)
	{
		return matrix_cofactors_laplace<typename Matrix_::preferred_floating_point, OutColumnMajor_, Matrix_>(matrix_);
	}
	template<typename out_contained_type, class Matrix_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<Matrix_::num_columns, Matrix_::num_rows, out_contained_type, Matrix_::is_column_major> matrix_cofactors_laplace
	(
		const Matrix_& matrix_
	)
	{
		return matrix_cofactors_laplace<out_contained_type, Matrix_::is_column_major, Matrix_>(matrix_);
	}
	template<class Matrix_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<Matrix_::num_columns, Matrix_::num_rows, typename Matrix_::preferred_floating_point, Matrix_::is_column_major>
	matrix_cofactors_laplace
	(
		const Matrix_& matrix_
	)
	{
		return matrix_cofactors_laplace<typename Matrix_::preferred_floating_point, Matrix_::is_column_major, Matrix_>(matrix_);
	}

	/// <summary>
	/// <para> Calculates the adjugate matrix to the passed matrix using Laplace Expansion. </para>
	/// <para> This matrix can be summarised as the transpose to the passed matrix's matrix of cofactors. </para>
	/// <para> NOTE: Laplace Expansion grows exponentially more expensive as the size of a matrix increases. </para>
	/// </summary>
	/// <typeparam name="out_contained_type">Type to be contained in the output adjugate matrix.</typeparam>
	/// <typeparam name="Matrix_">Matrix to calculate the adjugate to.</typeparam>
	/// <param name="matrix_">EmuMath matrix to find the adjugate to.</param>
	/// <returns>Adjugate matrix to the passed EmuMath matrix.</returns>
	template<typename out_contained_type, bool OutColumnMajor_, class Matrix_>
	[[nodiscard]] constexpr inline typename EmuMath::TMP::emu_matrix_transpose<out_contained_type, OutColumnMajor_, Matrix_>::type matrix_adjugate_laplace
	(
		const Matrix_& matrix_
	)
	{
		if constexpr (EmuMath::TMP::is_emu_matrix_v<Matrix_>)
		{
			if constexpr (Matrix_::is_square)
			{
				return _underlying_matrix_funcs::_calculate_matrix_adjugate_laplace
				<
					typename EmuMath::TMP::emu_matrix_transpose<out_contained_type, OutColumnMajor_, Matrix_>::type,
					Matrix_
				>(matrix_);
			}
			else
			{
				static_assert(false, "Attempted to calculate an adjugate matrix, but provided a non-square EmuMath matrix. Only square matrices are valid for this operation.");
			}
		}
		else
		{
			static_assert(false, "Attempted to calculate an adjugate matrix, but provided a non-EmuMath-matrix argument.");
		}
	}
	template<bool OutColumnMajor_, class Matrix_>
	[[nodiscard]] constexpr inline typename EmuMath::TMP::emu_matrix_transpose<typename Matrix_::preferred_floating_point, OutColumnMajor_, Matrix_>::type
	matrix_adjugate_laplace
	(
		const Matrix_& matrix_
	)
	{
		return matrix_adjugate_laplace<typename Matrix_::preferred_floating_point, OutColumnMajor_, Matrix_>(matrix_);
	}
	template<typename out_contained_type, class Matrix_>
	[[nodiscard]] constexpr inline typename EmuMath::TMP::emu_matrix_transpose<out_contained_type, Matrix_::is_column_major, Matrix_>::type matrix_adjugate_laplace
	(
		const Matrix_& matrix_
	)
	{
		return matrix_adjugate_laplace<out_contained_type, Matrix_::is_column_major, Matrix_>(matrix_);
	}
	template<class Matrix_>
	[[nodiscard]] constexpr inline typename EmuMath::TMP::emu_matrix_transpose<typename Matrix_::preferred_floating_point, Matrix_::is_column_major, Matrix_>::type
	matrix_adjugate_laplace
	(
		const Matrix_& matrix_
	)
	{
		return matrix_adjugate_laplace<typename Matrix_::preferred_floating_point, Matrix_::is_column_major, Matrix_>(matrix_);
	}

	/// <summary>
	/// <para> Calculates the inverse to the passed matrix using Laplace Expansion. May optionally output the matrix's determinant as a customisable type. </para>
	/// <para>
	///		Note that this operation does not check that the matrix's determinant is not 0. As matrices with a determinant of 0 have no inverse,
	///		it is recommended to use the outDeterminant argument to test if the output matrix is valid if there is a chance that the passed matrix's determinant will be 0.
	/// </para>
	/// <para> NOTE: Laplace Expansion grows exponentially more expensive as the size of a matrix increases. </para>
	/// </summary>
	/// <typeparam name="out_contained_type">Type to be contained in the output inverse matrix.</typeparam>
	/// <typeparam name="Matrix_">Type of matrix to find the inverse of.</typeparam>
	/// <typeparam name="OutDeterminant_">Type to optionally output the matrix's determinant as.</typeparam>
	/// <param name="matrix_">EmuMath matrix to find the inverse of.</param>
	/// <param name="outDeterminant_">
	///		Optional reference to output the passed matrix's determinant to. 
	///		Useful to test if the determinant is 0 in cases where a non-invertible matrix may potentially be passed.
	/// </param>
	/// <returns>Inverted version of the passed matrix if it is invertible. Otherwise, a matrix containing the results of multiplying its adjugate by (1/0).</returns>
	template<typename out_contained_type, bool OutColumnMajor_, class Matrix_, typename OutDeterminant_>
	[[nodiscard]] constexpr inline typename EmuMath::TMP::emu_matrix_transpose<out_contained_type, OutColumnMajor_, Matrix_>::type matrix_inverse_laplace
	(
		const Matrix_& matrix_,
		OutDeterminant_& outDeterminant_
	)
	{
		if constexpr (EmuMath::TMP::is_emu_matrix_v<Matrix_>)
		{
			if constexpr (Matrix_::is_square)
			{
				return _underlying_matrix_funcs::_calculate_matrix_inverse_laplace
				<
					typename EmuMath::TMP::emu_matrix_transpose<out_contained_type, OutColumnMajor_, Matrix_>::type,
					Matrix_,
					OutDeterminant_
				>(matrix_, outDeterminant_);
			}
			else
			{
				static_assert(false, "Attempted to calculate an inverse matrix, but provided a non-square EmuMath matrix. Only square matrices are valid for this operation.");
			}
		}
		else
		{
			static_assert(false, "Attempted to calculate an inverse matrix, but provided a non-EmuMath-matrix argument.");
		}
	}
	template<bool OutColumnMajor_, class Matrix_, typename OutDeterminant_>
	[[nodiscard]] constexpr inline typename EmuMath::TMP::emu_matrix_transpose<typename Matrix_::preferred_floating_point, OutColumnMajor_, Matrix_>::type
	matrix_inverse_laplace
	(
		const Matrix_& matrix_,
		OutDeterminant_& outDeterminant_
	)
	{
		return matrix_inverse_laplace<typename Matrix_::preferred_floating_point, OutColumnMajor_, Matrix_, OutDeterminant_>(matrix_, outDeterminant_);
	}
	template<typename out_contained_type, class Matrix_, typename OutDeterminant_>
	[[nodiscard]] constexpr inline typename EmuMath::TMP::emu_matrix_transpose<out_contained_type, Matrix_::is_column_major, Matrix_>::type matrix_inverse_laplace
	(
		const Matrix_& matrix_,
		OutDeterminant_& outDeterminant_
	)
	{
		return matrix_inverse_laplace<out_contained_type, Matrix_::is_column_major, Matrix_, OutDeterminant_>(matrix_, outDeterminant_);
	}
	template<class Matrix_, typename OutDeterminant_>
	[[nodiscard]] constexpr inline typename EmuMath::TMP::emu_matrix_transpose<typename Matrix_::preferred_floating_point, Matrix_::is_column_major, Matrix_>::type
	matrix_inverse_laplace
	(
		const Matrix_& matrix_,
		OutDeterminant_& outDeterminant_
	)
	{
		return matrix_inverse_laplace<typename Matrix_::preferred_floating_point, Matrix_::is_column_major, Matrix_, OutDeterminant_>(matrix_, outDeterminant_);
	}
	template<typename out_contained_type, bool OutColumnMajor_, class Matrix_>
	[[nodiscard]] constexpr inline typename EmuMath::TMP::emu_matrix_transpose<out_contained_type, OutColumnMajor_, Matrix_>::type matrix_inverse_laplace
	(
		const Matrix_& matrix_
	)
	{
		using dummy_output_type = float;
		dummy_output_type reciprocal_dummy_output_ = 0.0f;
		return matrix_inverse_laplace<out_contained_type, OutColumnMajor_, Matrix_, dummy_output_type>(matrix_, reciprocal_dummy_output_);
	}
	template<bool OutColumnMajor_, class Matrix_>
	[[nodiscard]] constexpr inline typename EmuMath::TMP::emu_matrix_transpose<typename Matrix_::preferred_floating_point, OutColumnMajor_, Matrix_>::type
	matrix_inverse_laplace
	(
		const Matrix_& matrix_
	)
	{
		return matrix_inverse_laplace<typename Matrix_::preferred_floating_point, OutColumnMajor_, Matrix_>(matrix_);
	}
	template<typename out_contained_type, class Matrix_>
	[[nodiscard]] constexpr inline typename EmuMath::TMP::emu_matrix_transpose<out_contained_type, Matrix_::is_column_major, Matrix_>::type matrix_inverse_laplace
	(
		const Matrix_& matrix_
	)
	{
		return matrix_inverse_laplace<out_contained_type, Matrix_::is_column_major, Matrix_>(matrix_);
	}
	template<class Matrix_>
	[[nodiscard]] constexpr inline typename EmuMath::TMP::emu_matrix_transpose<typename Matrix_::preferred_floating_point, Matrix_::is_column_major, Matrix_>::type
	matrix_inverse_laplace
	(
		const Matrix_& matrix_
	)
	{
		return matrix_inverse_laplace<typename Matrix_::preferred_floating_point, Matrix_::is_column_major, Matrix_>(matrix_);
	}

	/// <summary>
	/// <para> Calculates the inverse to the passed matrix using Gauss-Jordan elimination. May optionally output the determinant as a customisable type. </para>
	/// <para> Note that this operation does not check that the determinant is not 0. </para>
	/// <para> NOTE: Gauss-Jordan's time complexity may be considered O(n*n*n), where n is the size of the passed matrix in any one dimension. </para>
	/// <para> Especially recommended over laplace expansion when working with large matrices. </para>
	/// </summary>
	/// <typeparam name="out_contained_type">Type to be contained in the output inverse matrix.</typeparam>
	/// <typeparam name="OutDeterminant_">Type to optionally output the matrix's determinant as.</typeparam>
	/// <param name="matrix_">EmuMath matrix to find the inverse of.</param>
	/// <param name="out_determinant_">Optional reference to output the passed matrix's determinant to.</param>
	/// <returns>Inverted version of the passed matrix if it is invertible. Otherwise, a matrix resulting from simultaneous Gauss-Jordan elimination with its values.</returns>
	template<typename out_contained_type, bool OutColumnMajor_, class Matrix_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<Matrix_::num_columns, Matrix_::num_rows, out_contained_type, OutColumnMajor_> matrix_inverse_gauss_jordan
	(
		const Matrix_& matrix_
	)
	{
		if constexpr (EmuMath::TMP::is_emu_matrix_v<Matrix_>)
		{
			if constexpr (Matrix_::is_square)
			{
				return _underlying_matrix_funcs::_calculate_matrix_inverse_gj
				<
					EmuMath::Matrix<Matrix_::num_columns, Matrix_::num_rows, out_contained_type, OutColumnMajor_>,
					Matrix_,
					typename EmuCore::TMPHelpers::first_floating_point
					<
						out_contained_type,
						typename Matrix_::value_type,
						typename EmuMath::Matrix<Matrix_::num_columns, Matrix_::num_rows, out_contained_type, OutColumnMajor_>::preferred_floating_point
					>::type
				>(matrix_);
			}
			else
			{
				static_assert(false, "Attempted to calculate an inverse matrix, but provided a non-square EmuMath matrix. Only square matrices are valid for this operation.");
			}
		}
		else
		{
			static_assert(false, "Attempted to calculate an inverse matrix, but provided a non-EmuMath-matrix argument.");
		}
	}
	template<bool OutColumnMajor_, class Matrix_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<Matrix_::num_columns, Matrix_::num_rows, typename Matrix_::preferred_floating_point, OutColumnMajor_>
	matrix_inverse_gauss_jordan
	(
		const Matrix_& matrix_
	)
	{
		return matrix_inverse_gauss_jordan<typename Matrix_::preferred_floating_point, OutColumnMajor_, Matrix_>(matrix_);
	}
	template<typename out_contained_type, class Matrix_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<Matrix_::num_columns, Matrix_::num_rows, out_contained_type, Matrix_::is_column_major>
	matrix_inverse_gauss_jordan
	(
		const Matrix_& matrix_
	)
	{
		return matrix_inverse_gauss_jordan<out_contained_type, Matrix_::is_column_major, Matrix_>(matrix_);
	}
	template<class Matrix_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<Matrix_::num_columns, Matrix_::num_rows, typename Matrix_::preferred_floating_point, Matrix_::is_column_major>
	matrix_inverse_gauss_jordan
	(
		const Matrix_& matrix_
	)
	{
		return matrix_inverse_gauss_jordan<typename Matrix_::preferred_floating_point, Matrix_::is_column_major, Matrix_>(matrix_);
	}
	template<typename out_contained_type, bool OutColumnMajor_, class Matrix_, typename OutDeterminant_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<Matrix_::num_columns, Matrix_::num_rows, out_contained_type, OutColumnMajor_> matrix_inverse_gauss_jordan
	(
		const Matrix_& matrix_,
		OutDeterminant_& out_determinant_
	)
	{
		if constexpr (EmuMath::TMP::is_emu_matrix_v<Matrix_>)
		{
			if constexpr (Matrix_::is_square)
			{
				return _underlying_matrix_funcs::_calculate_matrix_inverse_gj
				<
					EmuMath::Matrix<Matrix_::num_columns, Matrix_::num_rows, out_contained_type, OutColumnMajor_>,
					Matrix_,
					typename EmuCore::TMPHelpers::first_floating_point
					<
						out_contained_type,
						OutDeterminant_,
						typename Matrix_::value_type,
						typename EmuMath::Matrix<Matrix_::num_columns, Matrix_::num_rows, out_contained_type, OutColumnMajor_>::preferred_floating_point
					>::type,
					OutDeterminant_
				>(matrix_, out_determinant_);
			}
			else
			{
				static_assert(false, "Attempted to calculate an inverse matrix, but provided a non-square EmuMath matrix. Only square matrices are valid for this operation.");
			}
		}
		else
		{
			static_assert(false, "Attempted to calculate an inverse matrix, but provided a non-EmuMath-matrix argument.");
		}
	}
	template<bool OutColumnMajor_, class Matrix_, typename OutDeterminant_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<Matrix_::num_columns, Matrix_::num_rows, typename Matrix_::preferred_floating_point, OutColumnMajor_>
	matrix_inverse_gauss_jordan
	(
		const Matrix_& matrix_,
		OutDeterminant_& out_determinant_
	)
	{
		return matrix_inverse_gauss_jordan<typename Matrix_::preferred_floating_point, OutColumnMajor_, Matrix_, OutDeterminant_>(matrix_, out_determinant_);
	}
	template<typename out_contained_type, class Matrix_, typename OutDeterminant_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<Matrix_::num_columns, Matrix_::num_rows, out_contained_type, Matrix_::is_column_major>
	matrix_inverse_gauss_jordan
	(
		const Matrix_& matrix_,
		OutDeterminant_& out_determinant_
	)
	{
		return matrix_inverse_gauss_jordan<out_contained_type, Matrix_::is_column_major, Matrix_, OutDeterminant_>(matrix_, out_determinant_);
	}
	template<class Matrix_, typename OutDeterminant_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<Matrix_::num_columns, Matrix_::num_rows, typename Matrix_::preferred_floating_point, Matrix_::is_column_major>
	matrix_inverse_gauss_jordan
	(
		const Matrix_& matrix_,
		OutDeterminant_& out_determinant_
	)
	{
		return matrix_inverse_gauss_jordan<typename Matrix_::preferred_floating_point, Matrix_::is_column_major, Matrix_, OutDeterminant_>(matrix_, out_determinant_);
	}
}

#endif
