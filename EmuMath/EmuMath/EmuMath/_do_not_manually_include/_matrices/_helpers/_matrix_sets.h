#ifndef EMU_MATH_MATRIX_HELPERS_SETS_H_INC_
#define EMU_MATH_MATRIX_HELPERS_SETS_H_INC_ 1

#include "_common_matrix_helper_includes.h"

namespace EmuMath::Helpers
{
	/// <summary>
	/// <para> Creates a matrix of the specified dimensions, contained type and column-major memory order, whose components copy the provided src_. </para>
	/// <para> If src_ is an EmuMath matrix: elements of the output matrix will be copies of respective elements in the src_ matrix. </para>
	/// <para> If src_ is none of the above: All elements of the output matrix will be copies of src_ cast to the output matrix's value_type. </para>
	/// <para>
	///		Non-contained elements will be interpreted as default-constructed values within src_ if it is a matrix. 
	///		This will only be achieved if the output matrix has more columns or rows than a src_ matrix.
	/// </para>
	/// </summary>
	/// <typeparam name="out_contained_type">Type to be contained in the output matrix.</typeparam>
	/// <typeparam name="Src_">Type to use as the source for copying.</typeparam>
	/// <param name="src_">Source to copy to the output vector.</param>
	/// <returns>EmuMath matrix of the specified instantiation parameters which copies src_ based on the described conditions.</returns>
	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename out_contained_type, bool OutColumnMajor_ = true, class Src_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, out_contained_type, OutColumnMajor_> MatrixCopy(const Src_& src_)
	{
		return _underlying_matrix_funcs::_matrix_create_from_src<EmuMath::Matrix<OutNumColumns_, OutNumRows_, out_contained_type, OutColumnMajor_>, Src_>(src_);
	}

	/// <summary>
	/// <para> Copies the source rhs_ to the provided destination lhs_ matrix. </para>
	/// <para> If rhs_ is an EmuMath matrix: elements of lhs_ will be copies of respective elements in the rhs_ matrix. </para>
	/// <para> If rhs_ is none of the above: All elements of lhs_ will be copies of rhs_ cast to lhs_'s value_type. </para>
	/// </summary>
	/// <typeparam name="LhsMatrix_">Type of EmuMath matrix to copy to.</typeparam>
	/// <typeparam name="Rhs_">Type of the provided source.</typeparam>
	/// <param name="lhs_">Destination EmuMath matrix to copy to.</param>
	/// <param name="rhs_">Source to copy to the destination lhs_ matrix.</param>
	/// <returns>Reference to the provided lhs_ matrix after a copy.</returns>
	template<class LhsMatrix_, class Rhs_>
	constexpr inline LhsMatrix_& MatrixCopy(LhsMatrix_& lhs_, const Rhs_& rhs_)
	{
		if constexpr (EmuMath::TMP::is_emu_matrix_v<LhsMatrix_>)
		{
			return _underlying_matrix_funcs::_matrix_copy<LhsMatrix_, Rhs_>(lhs_, rhs_);
		}
		else
		{
			static_assert(false, "Attempted to copy to a matrix, but the provided lhs_ argument was not an EmuMath matrix.");
		}
	}

	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename out_contained_type, bool OutColumnMajor_ = true, class Src_>
	constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, out_contained_type, OutColumnMajor_> MatrixSet(Src_& src_)
	{
		return _underlying_matrix_funcs::_matrix_make_and_set_full<EmuMath::Matrix<OutNumColumns_, OutNumRows_, out_contained_type, OutColumnMajor_>, Src_>(src_);
	}
	template<class LhsMatrix_, class Rhs_>
	constexpr inline LhsMatrix_& MatrixSet(LhsMatrix_& lhs_, Rhs_& rhs_)
	{
		if constexpr (EmuMath::TMP::is_emu_matrix_v<LhsMatrix_>)
		{
			return _underlying_matrix_funcs::_matrix_set_full<LhsMatrix_, Rhs_>(lhs_, rhs_);
		}
		else
		{
			static_assert(false, "Attempted to set a matrix, but the provided lhs_ argument was not an EmuMath matrix.");
		}
	}
	template<class LhsMatrix_, class Rhs_>
	constexpr inline LhsMatrix_& MatrixSet(LhsMatrix_& lhs_, const Rhs_& rhs_)
	{
		if constexpr (EmuMath::TMP::is_emu_matrix_v<LhsMatrix_>)
		{
			return _underlying_matrix_funcs::_matrix_set_full<LhsMatrix_, const Rhs_>(lhs_, rhs_);
		}
		else
		{
			static_assert(false, "Attempted to set a matrix, but the provided lhs_ argument was not an EmuMath matrix.");
		}
	}

	/// <summary>
	/// <para> Creates an EmuMath matrix of const references with the specified template arguments, with its data set in contiguous order with the passed arguments. </para>
	/// <para> The passed number of arguments must be equal to the number of elements contained within the desired output matrix. </para>
	/// <para> If the matrix is column major: Arguments will be used in order to fill columns, moving on to the next column once one is complete. </para>
	/// <para> If the matrix is row major: Arguments will be used in order to fill rows, moving on to the next row once one is complete. </para>
	/// </summary>
	/// <typeparam name="T_">Type to be contained in the created matrix.</typeparam>
	/// <typeparam name="Args_">Types used as scalar arguments for constructing the matrix.</typeparam>
	/// <param name="contiguous_args_">Scalar arguments used to form the matrix in contiguous order. The number of arguments must match the matrix's number of elements.</param>
	/// <returns>Const reference matrix of the specified type with its elements contiguously set via the provided arguments as defined above.</returns>
	template<std::size_t NumColumns_, std::size_t NumRows_, typename T_, bool ColumnMajor_ = true, typename...Args_>
	[[nodiscard]] constexpr inline EmuMath::ConstRefMatrix<NumColumns_, NumRows_, T_, ColumnMajor_> MatrixMakeConstRef(Args_&&...contiguous_args_)
	{
		if constexpr (sizeof...(Args_) == EmuMath::ConstRefMatrix<NumColumns_, NumRows_, T_, ColumnMajor_>::size)
		{
			return _underlying_matrix_funcs::_make_matrix<EmuMath::ConstRefMatrix<NumColumns_, NumRows_, T_, ColumnMajor_>>(contiguous_args_...);
		}
		else
		{
			static_assert(false, "Attempted to make an EmuMath matrix of const references via MatrixMake with a number of arguments not equal to the number of elements within the matrix.");
		}
	}

	/// <summary>
	/// <para> Creates an EmuMath matrix of references with the specified template arguments, with its data set in contiguous order with the passed arguments. </para>
	/// <para> The passed number of arguments must be equal to the number of elements contained within the desired output matrix. </para>
	/// <para> If the matrix is column major: Arguments will be used in order to fill columns, moving on to the next column once one is complete. </para>
	/// <para> If the matrix is row major: Arguments will be used in order to fill rows, moving on to the next row once one is complete. </para>
	/// </summary>
	/// <typeparam name="T_">Type to be contained in the created matrix.</typeparam>
	/// <typeparam name="Args_">Types used as scalar arguments for constructing the matrix.</typeparam>
	/// <param name="contiguous_args_">Scalar arguments used to form the matrix in contiguous order. The number of arguments must match the matrix's number of elements.</param>
	/// <returns>Reference matrix of the specified type with its elements contiguously set via the provided arguments as defined above.</returns>
	template<std::size_t NumColumns_, std::size_t NumRows_, typename T_, bool ColumnMajor_ = true, typename...Args_>
	[[nodiscard]] constexpr inline EmuMath::RefMatrix<NumColumns_, NumRows_, T_, ColumnMajor_> MatrixMakeRef(Args_&&...contiguous_args_)
	{
		if constexpr (std::is_const_v<T_>)
		{
			return MatrixMakeConstRef<NumColumns_, NumRows_, T_, ColumnMajor_>(contiguous_args_...);
		}
		else
		{
			if constexpr (sizeof...(Args_) == EmuMath::RefMatrix<NumColumns_, NumRows_, T_, ColumnMajor_>::size)
			{
				return _underlying_matrix_funcs::_make_matrix<EmuMath::RefMatrix<NumColumns_, NumRows_, T_, ColumnMajor_>>(contiguous_args_...);
			}
			else
			{
				static_assert(false, "Attempted to make an EmuMath matrix of references via MatrixMake with a number of arguments not equal to the number of elements within the matrix.");
			}
		}
	}

	/// <summary>
	/// <para> Creates an EmuMath matrix with the specified template arguments, with its data set in contiguous order with the passed arguments. </para>
	/// <para> The passed number of arguments must be equal to the number of elements contained within the desired output matrix. </para>
	/// <para> If the matrix is column major: Arguments will be used in order to fill columns, moving on to the next column once one is complete. </para>
	/// <para> If the matrix is row major: Arguments will be used in order to fill rows, moving on to the next row once one is complete. </para>
	/// </summary>
	/// <typeparam name="T_">Type to be contained in the created matrix.</typeparam>
	/// <typeparam name="Args_">Types used as scalar arguments for constructing the matrix.</typeparam>
	/// <param name="contiguous_args_">Scalar arguments used to form the matrix in contiguous order. The number of arguments must match the matrix's number of elements.</param>
	/// <returns>Matrix of the specified type with its elements contiguously set via the provided arguments as defined above.</returns>
	template<std::size_t NumColumns_, std::size_t NumRows_, typename T_, bool ColumnMajor_ = true, typename...Args_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_> MatrixMake(Args_&&...contiguous_args_)
	{
		if constexpr (EmuMath::TMP::is_internal_emu_matrix_reference_v<T_>)
		{
			return MatrixMakeRef<NumColumns_, NumRows_, typename T_::value_type, ColumnMajor_>(contiguous_args_...);
		}
		else
		{
			if constexpr (sizeof...(Args_) == EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>::size)
			{
				return _underlying_matrix_funcs::_make_matrix<EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>>(contiguous_args_...);
			}
			else
			{
				static_assert(false, "Attempted to make an EmuMath matrix via MatrixMake with a number of arguments not equal to the number of elements within the matrix.");
			}
		}
	}
}

#endif
