#ifndef EMU_MATH_MATRIX_HELPERS_ARITHMETIC_H_INC_
#define EMU_MATH_MATRIX_HELPERS_ARITHMETIC_H_INC_ 1

#include "_common_matrix_helper_includes.h"
#include "_matrix_reinterpretations.h"

namespace EmuMath::Helpers
{
	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename out_contained_type, bool OutColumnMajor_, class LhsMatrix_, class Rhs_, class Func_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, out_contained_type, OutColumnMajor_> MatrixLhsRhsOperation
	(
		const LhsMatrix_& lhs_,
		const Rhs_& rhs_,
		Func_ func_
	)
	{
		if constexpr (EmuMath::TMP::is_emu_matrix_v<LhsMatrix_>)
		{
			return _underlying_matrix_funcs::_matrix_multi_arg_operation
			<
				Func_&,
				EmuMath::Matrix<OutNumColumns_, OutNumRows_, out_contained_type, OutColumnMajor_>,
				LhsMatrix_,
				Rhs_
			>(func_, lhs_, rhs_);
		}
		else
		{
			static_assert(false, "Attempting to perform an operation on an EmuMath matrix which takes a rhs_ argument, but the lhs_ argument was not an EmuMath matrix.");
		}
	}
	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename out_contained_type, bool OutColumnMajor_, class LhsMatrix_, class Rhs_, class Func_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, out_contained_type, OutColumnMajor_> MatrixLhsRhsOperation
	(
		const LhsMatrix_& lhs_,
		const Rhs_& rhs_
	)
	{
		Func_ func_ = Func_();
		return MatrixLhsRhsOperation<OutNumColumns_, OutNumRows_, out_contained_type, OutColumnMajor_, LhsMatrix_, Rhs_, Func_&>(lhs_, rhs_, func_);
	}
	template<typename out_contained_type, bool OutColumnMajor_ , class LhsMatrix_, class Rhs_, class Func_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<LhsMatrix_::num_columns, LhsMatrix_::num_rows, out_contained_type, OutColumnMajor_> MatrixLhsRhsOperation
	(
		const LhsMatrix_& lhs_,
		const Rhs_& rhs_,
		Func_ func_
	)
	{
		return MatrixLhsRhsOperation<LhsMatrix_::num_columns, LhsMatrix_::num_rows, out_contained_type, OutColumnMajor_, LhsMatrix_, Rhs_, Func_&>(lhs_, rhs_, func_);
	}
	template<typename out_contained_type, bool OutColumnMajor_, class LhsMatrix_, class Rhs_, class Func_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<LhsMatrix_::num_columns, LhsMatrix_::num_rows, out_contained_type, OutColumnMajor_> MatrixLhsRhsOperation
	(
		const LhsMatrix_& lhs_,
		const Rhs_& rhs_
	)
	{
		return MatrixLhsRhsOperation<LhsMatrix_::num_columns, LhsMatrix_::num_rows, out_contained_type, OutColumnMajor_, LhsMatrix_, Rhs_, Func_>(lhs_, rhs_);
	}
	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, bool OutColumnMajor_, class LhsMatrix_, class Rhs_, class Func_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, typename LhsMatrix_::value_type, OutColumnMajor_> MatrixLhsRhsOperation
	(
		const LhsMatrix_& lhs_,
		const Rhs_& rhs_,
		Func_ func_
	)
	{
		return MatrixLhsRhsOperation<OutNumColumns_, OutNumRows_, typename LhsMatrix_::value_type, OutColumnMajor_, LhsMatrix_, rhs_, Func_&>(lhs_, rhs_, func_);
	}
	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, bool OutColumnMajor_, class LhsMatrix_, class Rhs_, class Func_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, typename LhsMatrix_::value_type, OutColumnMajor_> MatrixLhsRhsOperation
	(
		const LhsMatrix_& lhs_,
		const Rhs_& rhs_
	)
	{
		return MatrixLhsRhsOperation<OutNumColumns_, OutNumRows_, typename LhsMatrix_::value_type, OutColumnMajor_, LhsMatrix_, rhs_, Func_>(lhs_, rhs_);
	}
	template<bool OutColumnMajor_, class LhsMatrix_, class Rhs_, class Func_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<LhsMatrix_::num_columns, LhsMatrix_::num_rows, typename LhsMatrix_::value_type, OutColumnMajor_> MatrixLhsRhsOperation
	(
		const LhsMatrix_& lhs_,
		const Rhs_& rhs_,
		Func_ func_
	)
	{
		return MatrixLhsRhsOperation<LhsMatrix_::num_columns, LhsMatrix_::num_rows, typename LhsMatrix_::value_type, OutColumnMajor_, LhsMatrix_, Rhs_, Func_&>
		(
			lhs_,
			rhs_,
			func_
		);
	}
	template<bool OutColumnMajor_, class LhsMatrix_, class Rhs_, class Func_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<LhsMatrix_::num_columns, LhsMatrix_::num_rows, typename LhsMatrix_::value_type, OutColumnMajor_> MatrixLhsRhsOperation
	(
		const LhsMatrix_& lhs_,
		const Rhs_& rhs_
	)
	{
		return MatrixLhsRhsOperation<LhsMatrix_::num_columns, LhsMatrix_::num_rows, typename LhsMatrix_::value_type, OutColumnMajor_, LhsMatrix_, Rhs_, Func_>
		(
			lhs_,
			rhs_
		);
	}
	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename out_contained_type, class LhsMatrix_, class Rhs_, class Func_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, out_contained_type, LhsMatrix_::is_column_major> MatrixLhsRhsOperation
	(
		const LhsMatrix_& lhs_,
		const Rhs_& rhs_,
		Func_ func_
	)
	{
		return MatrixLhsRhsOperation<OutNumColumns_, OutNumColumns_, out_contained_type, LhsMatrix_::is_column_major, LhsMatrix_, Rhs_, Func_&>(lhs_, rhs_, func_);
	}
	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename out_contained_type, class LhsMatrix_, class Rhs_, class Func_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, out_contained_type, LhsMatrix_::is_column_major> MatrixLhsRhsOperation
	(
		const LhsMatrix_& lhs_,
		const Rhs_& rhs_
	)
	{
		return MatrixLhsRhsOperation<OutNumColumns_, OutNumRows_, out_contained_type, LhsMatrix_::is_column_major, LhsMatrix_, Rhs_, Func_>(lhs_, rhs_);
	}
	template<typename out_contained_type, class LhsMatrix_, class Rhs_, class Func_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<LhsMatrix_::num_columns, LhsMatrix_::num_rows, out_contained_type, LhsMatrix_::is_column_major> MatrixLhsRhsOperation
	(
		const LhsMatrix_& lhs_,
		const Rhs_& rhs_,
		Func_ func_
	)
	{
		return MatrixLhsRhsOperation<LhsMatrix_::num_columns, LhsMatrix_::num_rows, out_contained_type, LhsMatrix_::is_column_major, LhsMatrix_, Rhs_, Func_&>
		(
			lhs_,
			rhs_,
			func_
		);
	}
	template<typename out_contained_type, class LhsMatrix_, class Rhs_, class Func_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<LhsMatrix_::num_columns, LhsMatrix_::num_rows, out_contained_type, LhsMatrix_::is_column_major> MatrixLhsRhsOperation
	(
		const LhsMatrix_& lhs_,
		const Rhs_& rhs_
	)
	{
		return MatrixLhsRhsOperation<LhsMatrix_::num_columns, LhsMatrix_::num_rows, out_contained_type, LhsMatrix_::is_column_major, LhsMatrix_, Rhs_, Func_>
		(
			lhs_,
			rhs_
		);
	}
	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, class LhsMatrix_, class Rhs_, class Func_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, typename LhsMatrix_::value_type, LhsMatrix_::is_column_major> MatrixLhsRhsOperation
	(
		const LhsMatrix_& lhs_,
		const Rhs_& rhs_,
		Func_ func_
	)
	{
		return MatrixLhsRhsOperation<OutNumColumns_, OutNumRows_, typename LhsMatrix_::value_type, LhsMatrix_::is_column_major, LhsMatrix_, Rhs_, Func_&>
		(
			lhs_,
			rhs_,
			func_
		);
	}
	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, class LhsMatrix_, class Rhs_, class Func_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, typename LhsMatrix_::value_type, LhsMatrix_::is_column_major> MatrixLhsRhsOperation
	(
		const LhsMatrix_& lhs_,
		const Rhs_& rhs_
	)
	{
		return MatrixLhsRhsOperation<OutNumColumns_, OutNumRows_, typename LhsMatrix_::value_type, LhsMatrix_::is_column_major, LhsMatrix_, Rhs_, Func_>
		(
			lhs_,
			rhs_
		);
	}
	template<class LhsMatrix_, class Rhs_, class Func_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<LhsMatrix_::num_columns, LhsMatrix_::num_rows, typename LhsMatrix_::value_type, LhsMatrix_::is_column_major>
	MatrixLhsRhsOperation
	(
		const LhsMatrix_& lhs_,
		const Rhs_& rhs_,
		Func_ func_
	)
	{
		return MatrixLhsRhsOperation<LhsMatrix_::num_columns, LhsMatrix_::num_rows, typename LhsMatrix_::value_type, LhsMatrix_::is_column_major, LhsMatrix_, Rhs_, Func_&>
		(
			lhs_,
			rhs_,
			func_
		);
	}
	template<class LhsMatrix_, class Rhs_, class Func_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<LhsMatrix_::num_columns, LhsMatrix_::num_rows, typename LhsMatrix_::value_type, LhsMatrix_::is_column_major> 
	MatrixLhsRhsOperation
	(
		const LhsMatrix_& lhs_,
		const Rhs_& rhs_
	)
	{
		return MatrixLhsRhsOperation<LhsMatrix_::num_columns, LhsMatrix_::num_rows, typename LhsMatrix_::value_type, LhsMatrix_::is_column_major, LhsMatrix_, Rhs_, Func_>
		(
			lhs_,
			rhs_
		);
	}

	/// <summary>
	/// <para> Performs an addition operation on the passed lhs_ matrix using the passed rhs_. </para>
	/// <para> If the passed rhs_ is a matrix, respective indices in each matrix will be added. Otherwise, each index in the lhs_ matrix will have Rhs_ added to it. </para>
	/// <para> Additions are performed using EmuCore::do_add&lt;LhsMatrix_::value_type, Rhs_ (or Rhs_::value_type if it is a matrix)&gt;. </para>
	/// </summary>
	/// <typeparam name="out_contained_type">Type to be contained within the result matrix.</typeparam>
	/// <typeparam name="LhsMatrix_">Type of matrix appearing on the left-hand side of addition.</typeparam>
	/// <typeparam name="Rhs_">Type of matrix or scalar appearing on the right-hand side of addition.</typeparam>
	/// <param name="lhs_">EmuMath matrix appearing on the left-hand side of addition.</param>
	/// <param name="rhs_">EmuMath matrix or scalar appearing on the right-hand side of addition.</param>
	/// <returns>Matrix containing the results of adding rhs_ to the lhs_ matrix.</returns>
	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename out_contained_type, bool OutColumnMajor_, class LhsMatrix_, class Rhs_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, out_contained_type, OutColumnMajor_> MatrixAdd
	(
		const LhsMatrix_& lhs_,
		const Rhs_& rhs_
	)
	{
		if constexpr (EmuMath::TMP::is_emu_matrix_v<LhsMatrix_>)
		{
			return _underlying_matrix_funcs::_matrix_multi_arg_operation
			<
				EmuCore::do_add,
				EmuMath::Matrix<OutNumColumns_, OutNumRows_, out_contained_type, OutColumnMajor_>,
				LhsMatrix_,
				Rhs_
			>(lhs_, rhs_);
		}
		else
		{
			static_assert(false, "Attempted to perform matrix addition, but provided a non-EmuMath-matrix lhs_ argument.");
		}
	}
	template<typename out_contained_type, bool OutColumnMajor_, class LhsMatrix_, class Rhs_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<LhsMatrix_::num_columns, LhsMatrix_::num_rows, out_contained_type, OutColumnMajor_> MatrixAdd
	(
		const LhsMatrix_& lhs_,
		const Rhs_& rhs_
	)
	{
		return MatrixAdd<LhsMatrix_::num_columns, LhsMatrix_::num_rows, out_contained_type, OutColumnMajor_, LhsMatrix_, Rhs_>(lhs_, rhs_);
	}
	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, bool OutColumnMajor_, class LhsMatrix_, class Rhs_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, typename LhsMatrix_::value_type, OutColumnMajor_> MatrixAdd
	(
		const LhsMatrix_& lhs_,
		const Rhs_& rhs_
	)
	{
		return MatrixAdd<OutNumColumns_, OutNumRows_, typename LhsMatrix_::value_type, OutColumnMajor_, LhsMatrix_, Rhs_>(lhs_, rhs_);
	}
	template<bool OutColumnMajor_, class LhsMatrix_, class Rhs_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<LhsMatrix_::num_columns, LhsMatrix_::num_rows, typename LhsMatrix_::value_type, OutColumnMajor_> MatrixAdd
	(
		const LhsMatrix_& lhs_,
		const Rhs_& rhs_
	)
	{
		return MatrixAdd<LhsMatrix_::num_columns, LhsMatrix_::num_rows, typename LhsMatrix_::value_type, OutColumnMajor_, LhsMatrix_, Rhs_>(lhs_, rhs_);
	}

	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename out_contained_type, class LhsMatrix_, class Rhs_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, out_contained_type, LhsMatrix_::is_column_major> MatrixAdd
	(
		const LhsMatrix_& lhs_,
		const Rhs_& rhs_
	)
	{
		return MatrixAdd<OutNumColumns_, OutNumRows_, out_contained_type, LhsMatrix_::is_column_major, LhsMatrix_, Rhs_>(lhs_, rhs_);
	}
	template<typename out_contained_type, class LhsMatrix_, class Rhs_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<LhsMatrix_::num_columns, LhsMatrix_::num_rows, out_contained_type, LhsMatrix_::is_column_major> MatrixAdd
	(
		const LhsMatrix_& lhs_,
		const Rhs_& rhs_
	)
	{
		return MatrixAdd<LhsMatrix_::num_columns, LhsMatrix_::num_rows, out_contained_type, LhsMatrix_::is_column_major, LhsMatrix_, Rhs_>(lhs_, rhs_);
	}
	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, class LhsMatrix_, class Rhs_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, typename LhsMatrix_::value_type, LhsMatrix_::is_column_major> MatrixAdd
	(
		const LhsMatrix_& lhs_,
		const Rhs_& rhs_
	)
	{
		return MatrixAdd<OutNumColumns_, OutNumRows_, typename LhsMatrix_::value_type, LhsMatrix_::is_column_major, LhsMatrix_, Rhs_>(lhs_, rhs_);
	}
	template<class LhsMatrix_, class Rhs_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<LhsMatrix_::num_columns, LhsMatrix_::num_rows, typename LhsMatrix_::value_type, LhsMatrix_::is_column_major> MatrixAdd
	(
		const LhsMatrix_& lhs_,
		const Rhs_& rhs_
	)
	{
		return MatrixAdd<LhsMatrix_::num_columns, LhsMatrix_::num_rows, typename LhsMatrix_::value_type, LhsMatrix_::is_column_major, LhsMatrix_, Rhs_>(lhs_, rhs_);
	}

	/// <summary>
	/// <para> Performs an subtraction operation on the passed lhs_ matrix using the passed rhs_. </para>
	/// <para>
	///		If the passed rhs_ is a matrix, respective indices in each matrix will be subtracted. 
	/// Otherwise, each index in the lhs_ matrix will have Rhs_ subtracted from it.
	/// </para>
	/// <para> Subtractions are performed using EmuCore::do_subtract&lt;LhsMatrix_::value_type, Rhs_ (or Rhs_::value_type if it is a matrix)&gt;. </para>
	/// </summary>
	/// <typeparam name="out_contained_type">Type to be contained within the result matrix.</typeparam>
	/// <typeparam name="LhsMatrix_">Type of matrix appearing on the left-hand side of subtraction.</typeparam>
	/// <typeparam name="Rhs_">Type of matrix or scalar appearing on the right-hand side of subtraction.</typeparam>
	/// <param name="lhs_">EmuMath matrix appearing on the left-hand side of subtraction.</param>
	/// <param name="rhs_">EmuMath matrix or scalar appearing on the right-hand side of subtraction.</param>
	/// <returns>Matrix containing the results of subtracting rhs_ from the lhs_ matrix.</returns>
	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename out_contained_type, bool OutColumnMajor_, class LhsMatrix_, class Rhs_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, out_contained_type, OutColumnMajor_> MatrixSubtract
	(
		const LhsMatrix_& lhs_,
		const Rhs_& rhs_
	)
	{
		if constexpr (EmuMath::TMP::is_emu_matrix_v<LhsMatrix_>)
		{
			return _underlying_matrix_funcs::_matrix_multi_arg_operation
			<
				EmuCore::do_subtract,
				EmuMath::Matrix<OutNumColumns_, OutNumRows_, out_contained_type, OutColumnMajor_>,
				LhsMatrix_,
				Rhs_
			>(lhs_, rhs_);
		}
		else
		{
			static_assert(false, "Attempted to perform matrix subtraction, but provided a non-EmuMath-matrix lhs_ argument.");
		}
	}
	template<typename out_contained_type, bool OutColumnMajor_, class LhsMatrix_, class Rhs_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<LhsMatrix_::num_columns, LhsMatrix_::num_rows, out_contained_type, OutColumnMajor_> MatrixSubtract
	(
		const LhsMatrix_& lhs_,
		const Rhs_& rhs_
	)
	{
		return MatrixSubtract<LhsMatrix_::num_columns, LhsMatrix_::num_rows, out_contained_type, OutColumnMajor_, LhsMatrix_, Rhs_>(lhs_, rhs_);
	}
	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, bool OutColumnMajor_, class LhsMatrix_, class Rhs_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, typename LhsMatrix_::value_type, OutColumnMajor_> MatrixSubtract
	(
		const LhsMatrix_& lhs_,
		const Rhs_& rhs_
	)
	{
		return MatrixSubtract<OutNumColumns_, OutNumRows_, typename LhsMatrix_::value_type, OutColumnMajor_, LhsMatrix_, Rhs_>(lhs_, rhs_);
	}
	template<bool OutColumnMajor_, class LhsMatrix_, class Rhs_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<LhsMatrix_::num_columns, LhsMatrix_::num_rows, typename LhsMatrix_::value_type, OutColumnMajor_> MatrixSubtract
	(
		const LhsMatrix_& lhs_,
		const Rhs_& rhs_
	)
	{
		return MatrixSubtract<LhsMatrix_::num_columns, LhsMatrix_::num_rows, typename LhsMatrix_::value_type, OutColumnMajor_, LhsMatrix_, Rhs_>(lhs_, rhs_);
	}

	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename out_contained_type, class LhsMatrix_, class Rhs_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, out_contained_type, LhsMatrix_::is_column_major> MatrixSubtract
	(
		const LhsMatrix_& lhs_,
		const Rhs_& rhs_
	)
	{
		return MatrixSubtract<OutNumColumns_, OutNumRows_, out_contained_type, LhsMatrix_::is_column_major, LhsMatrix_, Rhs_>(lhs_, rhs_);
	}
	template<typename out_contained_type, class LhsMatrix_, class Rhs_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<LhsMatrix_::num_columns, LhsMatrix_::num_rows, out_contained_type, LhsMatrix_::is_column_major> MatrixSubtract
	(
		const LhsMatrix_& lhs_,
		const Rhs_& rhs_
	)
	{
		return MatrixSubtract<LhsMatrix_::num_columns, LhsMatrix_::num_rows, out_contained_type, LhsMatrix_::is_column_major, LhsMatrix_, Rhs_>(lhs_, rhs_);
	}
	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, class LhsMatrix_, class Rhs_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, typename LhsMatrix_::value_type, LhsMatrix_::is_column_major> MatrixSubtract
	(
		const LhsMatrix_& lhs_,
		const Rhs_& rhs_
	)
	{
		return MatrixSubtract<OutNumColumns_, OutNumRows_, typename LhsMatrix_::value_type, LhsMatrix_::is_column_major, LhsMatrix_, Rhs_>(lhs_, rhs_);
	}
	template<class LhsMatrix_, class Rhs_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<LhsMatrix_::num_columns, LhsMatrix_::num_rows, typename LhsMatrix_::value_type, LhsMatrix_::is_column_major> MatrixSubtract
	(
		const LhsMatrix_& lhs_,
		const Rhs_& rhs_
	)
	{
		return MatrixSubtract<LhsMatrix_::num_columns, LhsMatrix_::num_rows, typename LhsMatrix_::value_type, LhsMatrix_::is_column_major, LhsMatrix_, Rhs_>(lhs_, rhs_);
	}

	/// <summary>
	/// <para> Performs a basic multiplication operation on lhs_ using the passed rhs_. </para>
	/// <para>
	///		If the passed rhs_ is a matrix, respective indices in each matrix will be multiplied. 
	///		Otherwise, each index in the lhs_ matrix will be multiplied by rhs_.
	/// </para>
	/// <para> Multiplications are performed using EmuCore::do_multiply&lt;LhsMatrix_::value_type, Rhs_ (or Rhs_::value_type if it is a matrix)&gt;. </para>
	/// <para> NOTE: This is NOT a standard matrix multiplication operation. For such behaviour, use MatrixMultiply instead. </para>
	/// </summary>
	/// <typeparam name="out_contained_type">Type to be contained within the result matrix.</typeparam>
	/// <typeparam name="LhsMatrix_">Type of matrix appearing on the left-hand side of multiplication.</typeparam>
	/// <typeparam name="Rhs_">Type of matrix or scalar appearing on the right-hand side of multiplication.</typeparam>
	/// <param name="lhs_">EmuMath matrix appearing on the left-hand side of multiplication.</param>
	/// <param name="rhs_">EmuMath matrix or scalar appearing on the right-hand side of multiplication.</param>
	/// <returns>Matrix containing the results of performing a basic multiplication on the lhs_ matrix by the provided rhs_.</returns>
	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename out_contained_type, bool OutColumnMajor_, class LhsMatrix_, class Rhs_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, out_contained_type, OutColumnMajor_> MatrixMultiplyBasic
	(
		const LhsMatrix_& lhs_,
		const Rhs_& rhs_
	)
	{
		if constexpr (EmuMath::TMP::is_emu_matrix_v<LhsMatrix_>)
		{
			return _underlying_matrix_funcs::_matrix_multi_arg_operation
			<
				EmuCore::do_multiply,
				EmuMath::Matrix<OutNumColumns_, OutNumRows_, out_contained_type, OutColumnMajor_>,
				LhsMatrix_,
				Rhs_
			>(lhs_, rhs_);
		}
		else
		{
			static_assert(false, "Attempted to perform basic matrix multiplication, but provided a non-EmuMath-matrix lhs_ argument.");
		}
	}
	template<typename out_contained_type, bool OutColumnMajor_, class LhsMatrix_, class Rhs_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<LhsMatrix_::num_columns, LhsMatrix_::num_rows, out_contained_type, OutColumnMajor_> MatrixMultiplyBasic
	(
		const LhsMatrix_& lhs_,
		const Rhs_& rhs_
	)
	{
		return MatrixMultiplyBasic<LhsMatrix_::num_columns, LhsMatrix_::num_rows, out_contained_type, OutColumnMajor_, LhsMatrix_, Rhs_>(lhs_, rhs_);
	}
	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, bool OutColumnMajor_, class LhsMatrix_, class Rhs_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, typename LhsMatrix_::value_type, OutColumnMajor_> MatrixMultiplyBasic
	(
		const LhsMatrix_& lhs_,
		const Rhs_& rhs_
	)
	{
		return MatrixMultiplyBasic<OutNumColumns_, OutNumRows_, typename LhsMatrix_::value_type, OutColumnMajor_, LhsMatrix_, Rhs_>(lhs_, rhs_);
	}
	template<bool OutColumnMajor_, class LhsMatrix_, class Rhs_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<LhsMatrix_::num_columns, LhsMatrix_::num_rows, typename LhsMatrix_::value_type, OutColumnMajor_> MatrixMultiplyBasic
	(
		const LhsMatrix_& lhs_,
		const Rhs_& rhs_
	)
	{
		return MatrixMultiplyBasic<LhsMatrix_::num_columns, LhsMatrix_::num_rows, typename LhsMatrix_::value_type, OutColumnMajor_, LhsMatrix_, Rhs_>(lhs_, rhs_);
	}

	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename out_contained_type, class LhsMatrix_, class Rhs_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, out_contained_type, LhsMatrix_::is_column_major> MatrixMultiplyBasic
	(
		const LhsMatrix_& lhs_,
		const Rhs_& rhs_
	)
	{
		return MatrixMultiplyBasic<OutNumColumns_, OutNumRows_, out_contained_type, LhsMatrix_::is_column_major, LhsMatrix_, Rhs_>(lhs_, rhs_);
	}
	template<typename out_contained_type, class LhsMatrix_, class Rhs_>
	constexpr inline EmuMath::Matrix<LhsMatrix_::num_columns, LhsMatrix_::num_rows, out_contained_type, LhsMatrix_::is_column_major> MatrixMultiplyBasic
	(
		const LhsMatrix_& lhs_,
		const Rhs_& rhs_
	)
	{
		return MatrixMultiplyBasic<LhsMatrix_::num_columns, LhsMatrix_::num_rows, out_contained_type, LhsMatrix_::is_column_major, LhsMatrix_, Rhs_>(lhs_, rhs_);
	}
	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, class LhsMatrix_, class Rhs_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, typename LhsMatrix_::value_type, LhsMatrix_::is_column_major> MatrixMultiplyBasic
	(
		const LhsMatrix_& lhs_,
		const Rhs_& rhs_
	)
	{
		return MatrixMultiplyBasic<OutNumColumns_, OutNumRows_, typename LhsMatrix_::value_type, LhsMatrix_::is_column_major, LhsMatrix_, Rhs_>(lhs_, rhs_);
	}
	template<class LhsMatrix_, class Rhs_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<LhsMatrix_::num_columns, LhsMatrix_::num_rows, typename LhsMatrix_::value_type, LhsMatrix_::is_column_major> 
	MatrixMultiplyBasic
	(
		const LhsMatrix_& lhs_,
		const Rhs_& rhs_
	)
	{
		return MatrixMultiplyBasic<LhsMatrix_::num_columns, LhsMatrix_::num_rows, typename LhsMatrix_::value_type, LhsMatrix_::is_column_major, LhsMatrix_, Rhs_>(lhs_, rhs_);
	}

	/// <summary>
	/// <para> Performs a basic division operation on lhs_ using the passed rhs_. </para>
	/// <para>
	///		If the passed rhs_ is a matrix, respective indices in each matrix will be divided. 
	///		Otherwise, each index in the lhs_ matrix will be divided by rhs_.
	/// </para>
	/// <para> Divisions are performed using EmuCore::do_divide&lt;LhsMatrix_::value_type, Rhs_ (or Rhs_::value_type if it is a matrix)&gt;. </para>
	/// <para> NOTE: This is NOT a standard matrix division operation. Such behaviour is mathematically undefined. </para>
	/// </summary>
	/// <typeparam name="out_contained_type">Type to be contained within the result matrix.</typeparam>
	/// <typeparam name="LhsMatrix_">Type of matrix appearing on the left-hand side of division.</typeparam>
	/// <typeparam name="Rhs_">Type of matrix or scalar appearing on the right-hand side of division.</typeparam>
	/// <param name="lhs_">EmuMath matrix appearing on the left-hand side of division.</param>
	/// <param name="rhs_">EmuMath matrix or scalar appearing on the right-hand side of division.</param>
	/// <returns>Matrix containing the results of performing a basic division on the lhs_ matrix by the provided rhs_.</returns>
	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename out_contained_type, bool OutColumnMajor_, class LhsMatrix_, class Rhs_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, out_contained_type, OutColumnMajor_> MatrixDivideBasic
	(
		const LhsMatrix_& lhs_,
		const Rhs_& rhs_
	)
	{
		if constexpr (EmuMath::TMP::is_emu_matrix_v<LhsMatrix_>)
		{
			return _underlying_matrix_funcs::_matrix_multi_arg_operation
			<
				EmuCore::do_divide,
				EmuMath::Matrix<OutNumColumns_, OutNumRows_, out_contained_type, OutColumnMajor_>,
				LhsMatrix_,
				Rhs_
			>(lhs_, rhs_);
		}
		else
		{
			static_assert(false, "Attempted to perform basic matrix division, but provided a non-EmuMath-matrix lhs_ argument.");
		}
	}
	template<typename out_contained_type, bool OutColumnMajor_, class LhsMatrix_, class Rhs_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<LhsMatrix_::num_columns, LhsMatrix_::num_rows, out_contained_type, OutColumnMajor_> MatrixDivideBasic
	(
		const LhsMatrix_& lhs_,
		const Rhs_& rhs_
	)
	{
		return MatrixDivideBasic<LhsMatrix_::num_columns, LhsMatrix_::num_rows, out_contained_type, OutColumnMajor_, LhsMatrix_, Rhs_>(lhs_, rhs_);
	}
	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, bool OutColumnMajor_, class LhsMatrix_, class Rhs_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, typename LhsMatrix_::value_type, OutColumnMajor_> MatrixDivideBasic
	(
		const LhsMatrix_& lhs_,
		const Rhs_& rhs_
	)
	{
		return MatrixDivideBasic<OutNumColumns_, OutNumRows_, typename LhsMatrix_::value_type, OutColumnMajor_, LhsMatrix_, Rhs_>(lhs_, rhs_);
	}
	template<bool OutColumnMajor_, class LhsMatrix_, class Rhs_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<LhsMatrix_::num_columns, LhsMatrix_::num_rows, typename LhsMatrix_::value_type, OutColumnMajor_> MatrixDivideBasic
	(
		const LhsMatrix_& lhs_,
		const Rhs_& rhs_
	)
	{
		return MatrixDivideBasic<LhsMatrix_::num_columns, LhsMatrix_::num_rows, typename LhsMatrix_::value_type, OutColumnMajor_, LhsMatrix_, Rhs_>(lhs_, rhs_);
	}

	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename out_contained_type, class LhsMatrix_, class Rhs_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, out_contained_type, LhsMatrix_::is_column_major> MatrixDivideBasic
	(
		const LhsMatrix_& lhs_,
		const Rhs_& rhs_
	)
	{
		return MatrixDivideBasic<OutNumColumns_, OutNumRows_, out_contained_type, LhsMatrix_::is_column_major, LhsMatrix_, Rhs_>(lhs_, rhs_);
	}
	template<typename out_contained_type, class LhsMatrix_, class Rhs_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<LhsMatrix_::num_columns, LhsMatrix_::num_rows, out_contained_type, LhsMatrix_::is_column_major> MatrixDivideBasic
	(
		const LhsMatrix_& lhs_,
		const Rhs_& rhs_
	)
	{
		return MatrixDivideBasic<LhsMatrix_::num_columns, LhsMatrix_::num_rows, out_contained_type, LhsMatrix_::is_column_major, LhsMatrix_, Rhs_>(lhs_, rhs_);
	}
	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, class LhsMatrix_, class Rhs_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, typename LhsMatrix_::value_type, LhsMatrix_::is_column_major> MatrixDivideBasic
	(
		const LhsMatrix_& lhs_,
		const Rhs_& rhs_
	)
	{
		return MatrixDivideBasic<OutNumColumns_, OutNumRows_, typename LhsMatrix_::value_type, LhsMatrix_::is_column_major, LhsMatrix_, Rhs_>(lhs_, rhs_);
	}
	template<class LhsMatrix_, class Rhs_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<LhsMatrix_::num_columns, LhsMatrix_::num_rows, typename LhsMatrix_::value_type, LhsMatrix_::is_column_major>
	MatrixDivideBasic
	(
		const LhsMatrix_& lhs_,
		const Rhs_& rhs_
	)
	{
		return MatrixDivideBasic<LhsMatrix_::num_columns, LhsMatrix_::num_rows, typename LhsMatrix_::value_type, LhsMatrix_::is_column_major, LhsMatrix_, Rhs_>(lhs_, rhs_);
	}

	/// <summary>
	/// <para>
	///		Returns a resulting EmuMath vector from a multiplication between the passed lhs_matrix_ and rhs_vector_, 
	///		where rhs_vector_ is interpreted as a single-column matrix.
	/// </para>
	/// <para> The provided vector requires one of two specific sizes in order to be valid: </para>
	/// <para> 1. Equal to the number of rows within the matrix. </para>
	/// <para> 2. Equal to the number of rows within the matrix - 1. The non-contained element will be implicitly considered to be 1. </para>
	/// <para> Condition 2. allows spatial transformation multiplications to be performed, such as transforming 3D vectors with a 4x4 transformation matrix. </para>
	/// </summary>
	/// <typeparam name="out_contained_type">Type to be contained within the output vector.</typeparam>
	/// <typeparam name="LhsMatrix_">Type of matrix appearing on the left of multiplication.</typeparam>
	/// <typeparam name="RhsVector_">Type of vector appearing on the right of multiplication.</typeparam>
	/// <param name="lhs_matrix_">EmuMath matrix appearing on the left of multiplication.</param>
	/// <param name="rhs_vector_">EmuMath vector appearing on the right of multiplication.</param>
	/// <returns>
	///		EmuMath vector of the passed vector's size containing the results of matrix multiplication, where rhs_vector_ is interpreted as a single-column matrix.
	/// </returns>
	template<typename out_contained_type, class LhsMatrix_, class RhsVector_>
	[[nodiscard]] constexpr inline EmuMath::Vector<RhsVector_::size, out_contained_type> MatrixMultiplyVector
	(
		const LhsMatrix_& lhs_matrix_,
		const RhsVector_& rhs_vector_
	)
	{
		if constexpr (EmuMath::TMP::is_emu_matrix_v<LhsMatrix_>)
		{
			if constexpr (EmuMath::TMP::is_emu_vector_v<RhsVector_>)
			{
				using RhsMatrix_ = EmuMath::Matrix<1, LhsMatrix_::num_rows, typename RhsVector_::value_type, true>;
				if constexpr (RhsVector_::size == LhsMatrix_::num_rows)
				{
					RhsMatrix_ rhs_matrix_ = VectorToColumnMatrix<typename RhsVector_::value_type, true, RhsVector_>(rhs_vector_);
					RhsMatrix_ result_ = _underlying_matrix_funcs::_matrix_std_multiply<RhsMatrix_, LhsMatrix_, RhsMatrix_>(lhs_matrix_, rhs_matrix_);
					return _underlying_matrix_funcs::_get_matrix_major<0>(result_).template As<RhsVector_::size, out_contained_type>();
				}
				else if constexpr ((RhsVector_::size + 1) == LhsMatrix_::num_rows)
				{
					using rhs_value = typename RhsVector_::value_type;
					using prepared_vector = EmuMath::Vector<RhsVector_::size + 1, rhs_value>;
					RhsMatrix_ rhs_matrix_ = VectorToColumnMatrix<rhs_value, true, prepared_vector>(VectorPrepareToTransform<rhs_value, RhsVector_>(rhs_vector_));
					RhsMatrix_ result_ = _underlying_matrix_funcs::_matrix_std_multiply<RhsMatrix_, LhsMatrix_, RhsMatrix_>(lhs_matrix_, rhs_matrix_);
					return _underlying_matrix_funcs::_get_matrix_major<0>(result_).template As<RhsVector_::size, out_contained_type>();
				}
				else
				{
					static_assert(false, "Attempted to multiply a left-hand EmuMath matrix and right-hand EmuMath vector, but the provided vector is not a valid size. The vector must have a size equal to the matrix's number of rows, or the matrix's number of rows - 1, to be correctly reinterpreted as a single-column matrix.");
				}
			}
			else
			{
				static_assert(false, "Attempted to multiply a matrix and vector, but the provided rhs_vector_ argument was not an EmuMath vector.");
			}
		}
		else
		{
			static_assert(false, "Attempted to multiply a matrix and vector, but the provided lhs_matrix_ argument was not an EmuMath matrix.");
		}
	}
	template<class LhsMatrix_, class RhsVector_>
	[[nodiscard]] constexpr inline EmuMath::Vector<RhsVector_::size, typename RhsVector_::value_type> MatrixMultiplyVector
	(
		const LhsMatrix_& lhs_matrix_,
		const RhsVector_& rhs_vector_
	)
	{
		if constexpr (EmuMath::TMP::is_emu_vector_v<RhsVector_>)
		{
			return MatrixMultiplyVector<typename RhsVector_::value_type, LhsMatrix_, RhsVector_>(lhs_matrix_, rhs_vector_);
		}
		else
		{
			static_assert(false, "Attempted to multiply a matrix and vector, but the provided rhs_vector_ argument was not an EmuMath vector.");
		}
	}

	/// <summary>
	/// <para> Performs a multiplication operation on lhs_ using the passed rhs_. </para>
	/// <para>
	///		If the passed rhs_ is a matrix, the resulting matrix will be that of a standard matrix multiplication.
	///		Otherwise, each index in the lhs_ matrix will be multiplied by rhs_.
	/// </para>
	/// <para> If rhs_ is an EmuMath vector, it will be interpreted as a single-column matrix. Refer to MatrixMultiplyVector for more information. </para>
	/// <para> If rhs_ is a scalar, multiplications are performed using EmuCore::do_multiply&lt;LhsMatrix_::value_type, Rhs_ (or Rhs_::value_type if it is a matrix)&gt;. </para>
	/// <para> NOTE: This is a standard matrix multiplication operation. To instead multiply respective matrix indices, use MatrixMultiplyBasic. </para>
	/// </summary>
	/// <typeparam name="out_contained_type">Type to be contained within the result matrix.</typeparam>
	/// <typeparam name="LhsMatrix_">Type of matrix appearing on the left-hand side of multiplication.</typeparam>
	/// <typeparam name="Rhs_">Type of matrix or scalar appearing on the right-hand side of multiplication.</typeparam>
	/// <param name="lhs_">EmuMath matrix appearing on the left-hand side of multiplication.</param>
	/// <param name="rhs_">EmuMath matrix or scalar appearing on the right-hand side of multiplication.</param>
	/// <returns>Matrix containing the results of performing multiplication on the lhs_ matrix by the provided rhs_.</returns>
	template<typename out_contained_type, bool OutColumnMajor_, class LhsMatrix_, class Rhs_>
	[[nodiscard]] constexpr inline auto MatrixMultiply
	(
		const LhsMatrix_& lhs_,
		const Rhs_& rhs_
	)
	{
		if constexpr (EmuMath::TMP::is_emu_matrix_v<LhsMatrix_>)
		{
			if constexpr(!std::is_same_v<typename EmuMath::TMP::emu_matrix_multiplication_result<out_contained_type, OutColumnMajor_, LhsMatrix_, Rhs_>::type, void>)
			{
				if constexpr (EmuMath::TMP::is_emu_vector_v<Rhs_>)
				{
					return MatrixMultiplyVector<out_contained_type, LhsMatrix_, Rhs_>(lhs_, rhs_);
				}
				else
				{
					return _underlying_matrix_funcs::_matrix_std_multiply
					<
						typename EmuMath::TMP::emu_matrix_multiplication_result<out_contained_type, OutColumnMajor_, LhsMatrix_, Rhs_>::type,
						LhsMatrix_,
						Rhs_
					>(lhs_, rhs_);
				}
			}
			else
			{
				static_assert(false, "Attempted to multiply two EmuMath matrices which can not be multiplied together. When multiplying matrices, the left-hand matrix must have the same number of columns as the right-hand matrix's number of rows.");
			}
		}
		else
		{
			static_assert(false, "Attempted to perform matrix multiplication with a lhs_ argument that is not an EmuMath matrix.");
		}
	}
	template<typename out_contained_type, class LhsMatrix_, class Rhs_>
	[[nodiscard]] constexpr inline auto MatrixMultiply
	(
		const LhsMatrix_& lhs_,
		const Rhs_& rhs_
	)
	{
		return MatrixMultiply<out_contained_type, LhsMatrix_::is_column_major, LhsMatrix_, Rhs_>(lhs_, rhs_);
	}
	template<bool OutColumnMajor_, class LhsMatrix_, class Rhs_>
	[[nodiscard]] constexpr inline auto MatrixMultiply
	(
		const LhsMatrix_& lhs_,
		const Rhs_& rhs_
	)
	{
		return MatrixMultiply<typename LhsMatrix_::value_type, OutColumnMajor_, LhsMatrix_, Rhs_>(lhs_, rhs_);
	}
	template<class LhsMatrix_, class Rhs_>
	[[nodiscard]] constexpr inline auto MatrixMultiply
	(
		const LhsMatrix_& lhs_,
		const Rhs_& rhs_
	)
	{
		return MatrixMultiply<typename LhsMatrix_::value_type, LhsMatrix_::is_column_major, LhsMatrix_, Rhs_>(lhs_, rhs_);
	}

	/// <summary>
	/// <para> Function which may be used to create a new EmuMath matrix containing copies of mutated respective elements within another EmuMath matrix. </para>
	/// <para>
	///		The passed Func_ is expected to be invocable with one argument, of the type InMatrix_::raw_value_type, or a type it may be implictly cast to. 
	///		Additionally, it is expected to return a type castable to OutMatrix_::value_type.
	/// </para>
	/// <para> Invocations of func_ will always be in column-major order; all elements in a column will be passed before the next column, until all columns are complete. </para>
	/// </summary>
	/// <typeparam name="Func_">Type to invoke for every element.</typeparam>
	/// <typeparam name="InMatrix_">Type of matrix to mutate.</typeparam>
	/// <param name="in_matrix_">EmuMath matrix to mutate each element of.</param>
	/// <param name="func_">Invocable item that meets the defined constraints above, which will be invoked for every element to mutate said element.</param>
	/// <returns>Copy of the provided matrix with its elements mutated via the provided func_.</returns>
	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename out_contained_type, bool OutColumnMajor_, class Func_, class InMatrix_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, out_contained_type, OutColumnMajor_> MatrixMutate
	(
		const InMatrix_& in_matrix_,
		Func_ func_
	)
	{
		if constexpr (EmuMath::TMP::is_emu_matrix_v<InMatrix_>)
		{
			return _underlying_matrix_funcs::_make_mutated_matrix
			<
				Func_&,
				EmuMath::Matrix<OutNumColumns_, OutNumRows_, out_contained_type, OutColumnMajor_>,
				InMatrix_
			>(in_matrix_, func_);
		}
		else
		{
			static_assert(false, "Attempted to mutate a matrix, but the passed in_matrix_ was not an EmuMath matrix.");
		}
	}
	template<typename out_contained_type, bool OutColumnMajor_, class Func_, class InMatrix_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<InMatrix_::num_columns, InMatrix_::num_rows, out_contained_type, OutColumnMajor_> MatrixMutate
	(
		const InMatrix_& in_matrix_,
		Func_ func_
	)
	{
		return MatrixMutate<InMatrix_::num_columns, InMatrix_::num_rows, out_contained_type, OutColumnMajor_, Func_&, InMatrix_>(in_matrix_, func_);
	}
	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, bool OutColumnMajor_, class Func_, class InMatrix_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, typename InMatrix_::value_type, OutColumnMajor_> MatrixMutate
	(
		const InMatrix_& in_matrix_,
		Func_ func_
	)
	{
		return MatrixMutate<OutNumColumns_, OutNumRows_, typename InMatrix_::value_type, OutColumnMajor_, Func_&, InMatrix_>(in_matrix_, func_);
	}
	template<bool OutColumnMajor_, class Func_, class InMatrix_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<InMatrix_::num_columns, InMatrix_::num_rows, typename InMatrix_::value_type, OutColumnMajor_> MatrixMutate
	(
		const InMatrix_& in_matrix_,
		Func_ func_
	)
	{
		return MatrixMutate<InMatrix_::num_columns, InMatrix_::num_rows, typename InMatrix_::value_type, OutColumnMajor_, Func_&, InMatrix_>(in_matrix_, func_);
	}
	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename out_contained_type, class Func_, class InMatrix_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, out_contained_type, InMatrix_::is_column_major> MatrixMutate
	(
		const InMatrix_& in_matrix_,
		Func_ func_
	)
	{
		return MatrixMutate<OutNumColumns_, OutNumColumns_, out_contained_type, InMatrix_::is_column_major, Func_&, InMatrix_>(in_matrix_, func_);
	}
	template<typename out_contained_type, class Func_, class InMatrix_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<InMatrix_::num_columns, InMatrix_::num_rows, out_contained_type, InMatrix_::is_column_major> MatrixMutate
	(
		const InMatrix_& in_matrix_,
		Func_ func_
	)
	{
		return MatrixMutate<InMatrix_::num_columns, InMatrix_::num_rows, out_contained_type, InMatrix_::is_column_major, Func_&, InMatrix_>(in_matrix_, func_);
	}
	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, class Func_, class InMatrix_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, typename InMatrix_::value_type, InMatrix_::is_column_major> MatrixMutate
	(
		const InMatrix_& in_matrix_,
		Func_ func_
	)
	{
		return MatrixMutate<OutNumColumns_, OutNumRows_, typename InMatrix_::value_type, InMatrix_::is_column_major, Func_&, InMatrix_>(in_matrix_, func_);
	}
	template<class Func_, class InMatrix_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<InMatrix_::num_columns, InMatrix_::num_rows, typename InMatrix_::value_type, InMatrix_::is_column_major> MatrixMutate
	(
		const InMatrix_& in_matrix_,
		Func_ func_
	)
	{
		return MatrixMutate<InMatrix_::num_columns, InMatrix_::num_rows, typename InMatrix_::value_type, InMatrix_::is_column_major, Func_&, InMatrix_>(in_matrix_, func_);
	}

	/// <summary>
	/// <para> Function which may be used to output mutated elements of an EmuMath matrix to a referenced output EmuMath matrix. </para>
	/// <para>
	///		The passed Func_ is expected to be invocable with one argument, of the type InMatrix_::raw_value_type, or a type it may be implictly cast to. 
	///		Additionally, it is expected to return a type castable to OutMatrix_::value_type.
	/// </para>
	/// <para> Invocations of func_ will always be in column-major order; all elements in a column will be passed before the next column, until all columns are complete. </para>
	/// </summary>
	/// <typeparam name="Func_">Type to invoke for every element.</typeparam>
	/// <typeparam name="InMatrix_">Type of matrix to mutate.</typeparam>
	/// <typeparam name="OutMatrix_">Type of matrix to output mutation results to.</typeparam>
	/// <param name="in_matrix_">EmuMath matrix to mutate each element of.</param>
	/// <param name="out_matrix_">Reference to the EmuMath matrix to store the results of respective element mutations within.</param>
	/// <param name="func_">Invocable item that meets the defined constraints above, which will be invoked for every element to mutate said element.</param>
	/// <returns>Reference to out_matrix_ after mutation has been called for all elements.</returns>
	template<class Func_, class InMatrix_, class OutMatrix_>
	constexpr inline OutMatrix_& MatrixMutate(const InMatrix_& in_matrix_, OutMatrix_& out_matrix_, Func_ func_)
	{
		if constexpr (EmuMath::TMP::is_emu_matrix_v<InMatrix_>)
		{
			if constexpr (EmuMath::TMP::is_emu_matrix_v<OutMatrix_>)
			{
				return _underlying_matrix_funcs::_matrix_mutate
				<
					Func_&,
					OutMatrix_,
					InMatrix_
				>(in_matrix_, out_matrix_, func_);
			}
			else
			{
				static_assert(false, "Attempted to mutate a matrix, but the passed out_matrix_ was not an EmuMath matrix.");
			}
		}
		else
		{
			static_assert(false, "Attempted to mutate a matrix, but the passed in_matrix_ was not an EmuMath matrix.");
		}
	}

	/// <summary> Returns a negated version of the passed EmuMath matrix, where all elements [x][y] can be summarised as -[x][y]. </summary>
	/// <typeparam name="out_contained_type">Type to be contained in the output matrix.</typeparam>
	/// <typeparam name="Matrix_">Type of matrix to negate.</typeparam>
	/// <param name="matrix_">EmuMath matrix to negate.</param>
	/// <returns>Negated form of the provided matrix.</returns>
	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename out_contained_type, bool OutColumnMajor_, class Matrix_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, out_contained_type, OutColumnMajor_> MatrixNegate(const Matrix_& matrix_)
	{
		if constexpr (EmuMath::TMP::is_emu_matrix_v<Matrix_>)
		{
			return _underlying_matrix_funcs::_make_mutated_matrix
			<
				EmuCore::do_negate<typename Matrix_::value_type>,
				EmuMath::Matrix<OutNumColumns_, OutNumRows_, out_contained_type, OutColumnMajor_>,
				Matrix_
			>(matrix_);
		}
		else
		{
			static_assert(false, "Attempted to negate a matrix, but the passed matrix_ was not an EmuMath matrix.");
		}
	}
	template<typename out_contained_type, bool OutColumnMajor_, class Matrix_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<Matrix_::num_columns, Matrix_::num_rows, out_contained_type, OutColumnMajor_> MatrixNegate(const Matrix_& matrix_)
	{
		return MatrixNegate<Matrix_::num_columns, Matrix_::num_rows, out_contained_type, OutColumnMajor_, Matrix_>(matrix_);
	}
	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, bool OutColumnMajor_, class Matrix_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, typename Matrix_::value_type, OutColumnMajor_> MatrixNegate(const Matrix_& matrix_)
	{
		return MatrixNegate<OutNumColumns_, OutNumRows_, typename Matrix_::value_type, OutColumnMajor_, Matrix_>(matrix_);
	}
	template<bool OutColumnMajor_, class Matrix_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<Matrix_::num_columns, Matrix_::num_rows, typename Matrix_::value_type, OutColumnMajor_> MatrixNegate
	(
		const Matrix_& matrix_
	)
	{
		return MatrixNegate<Matrix_::num_columns, Matrix_::num_rows, typename Matrix_::value_type, OutColumnMajor_, Matrix_>(matrix_);
	}
	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename out_contained_type, class Matrix_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, out_contained_type, Matrix_::is_column_major> MatrixNegate(const Matrix_& matrix_)
	{
		return MatrixNegate<OutNumColumns_, OutNumRows_, out_contained_type, Matrix_::is_column_major, Matrix_>(matrix_);
	}
	template<typename out_contained_type, class Matrix_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<Matrix_::num_columns, Matrix_::num_rows, out_contained_type, Matrix_::is_column_major> MatrixNegate(const Matrix_& matrix_)
	{
		return MatrixNegate<Matrix_::num_columns, Matrix_::num_rows, out_contained_type, Matrix_::is_column_major, Matrix_>(matrix_);
	}
	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, class Matrix_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, typename Matrix_::value_type, Matrix_::is_column_major> MatrixNegate(const Matrix_& matrix_)
	{
		return MatrixNegate<OutNumColumns_, OutNumRows_, typename Matrix_::value_type, Matrix_::is_column_major, Matrix_>(matrix_);
	}
	template<class Matrix_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<Matrix_::num_columns, Matrix_::num_rows, typename Matrix_::value_type, Matrix_::is_column_major> MatrixNegate
	(
		const Matrix_& matrix_
	)
	{
		return MatrixNegate<Matrix_::num_columns, Matrix_::num_rows, typename Matrix_::value_type, Matrix_::is_column_major, Matrix_>(matrix_);
	}

	/// <summary> Floors all elements of the provided matrix, rounding them toward negative infinity. </summary>
	/// <typeparam name="out_contained_type">Type to be contained in the output matrix.</typeparam>
	/// <typeparam name="Matrix_">Type of matrix to round the elements of.</typeparam>
	/// <param name="matrix_">EmuMath matrix to round the elements of.</param>
	/// <returns>Rounded form of the provided matrix.</returns>
	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename out_contained_type, bool OutColumnMajor_, class Matrix_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, out_contained_type, OutColumnMajor_> MatrixFloor(const Matrix_& matrix_)
	{
		if constexpr (EmuMath::TMP::is_emu_matrix_v<Matrix_>)
		{
			return _underlying_matrix_funcs::_make_mutated_matrix
			<
				EmuCore::do_floor<typename Matrix_::value_type>,
				EmuMath::Matrix<OutNumColumns_, OutNumRows_, out_contained_type, OutColumnMajor_>,
				Matrix_
			>(matrix_);
		}
		else
		{
			static_assert(false, "Attempted to floor a matrix, but the passed matrix_ was not an EmuMath matrix.");
		}
	}
	template<typename out_contained_type, bool OutColumnMajor_, class Matrix_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<Matrix_::num_columns, Matrix_::num_rows, out_contained_type, OutColumnMajor_> MatrixFloor(const Matrix_& matrix_)
	{
		return MatrixFloor<Matrix_::num_columns, Matrix_::num_rows, out_contained_type, OutColumnMajor_, Matrix_>(matrix_);
	}
	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, bool OutColumnMajor_, class Matrix_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, typename Matrix_::value_type, OutColumnMajor_> MatrixFloor(const Matrix_& matrix_)
	{
		return MatrixFloor<OutNumColumns_, OutNumRows_, typename Matrix_::value_type, OutColumnMajor_, Matrix_>(matrix_);
	}
	template<bool OutColumnMajor_, class Matrix_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<Matrix_::num_columns, Matrix_::num_rows, typename Matrix_::value_type, OutColumnMajor_> MatrixFloor
	(
		const Matrix_& matrix_
	)
	{
		return MatrixFloor<Matrix_::num_columns, Matrix_::num_rows, typename Matrix_::value_type, OutColumnMajor_, Matrix_>(matrix_);
	}
	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename out_contained_type, class Matrix_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, out_contained_type, Matrix_::is_column_major> MatrixFloor(const Matrix_& matrix_)
	{
		return MatrixFloor<OutNumColumns_, OutNumRows_, out_contained_type, Matrix_::is_column_major, Matrix_>(matrix_);
	}
	template<typename out_contained_type, class Matrix_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<Matrix_::num_columns, Matrix_::num_rows, out_contained_type, Matrix_::is_column_major> MatrixFloor(const Matrix_& matrix_)
	{
		return MatrixFloor<Matrix_::num_columns, Matrix_::num_rows, out_contained_type, Matrix_::is_column_major, Matrix_>(matrix_);
	}
	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, class Matrix_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, typename Matrix_::value_type, Matrix_::is_column_major> MatrixFloor(const Matrix_& matrix_)
	{
		return MatrixFloor<OutNumColumns_, OutNumRows_, typename Matrix_::value_type, Matrix_::is_column_major, Matrix_>(matrix_);
	}
	template<class Matrix_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<Matrix_::num_columns, Matrix_::num_rows, typename Matrix_::value_type, Matrix_::is_column_major> MatrixFloor
	(
		const Matrix_& matrix_
	)
	{
		return MatrixFloor<Matrix_::num_columns, Matrix_::num_rows, typename Matrix_::value_type, Matrix_::is_column_major, Matrix_>(matrix_);
	}

	/// <summary> Ceils all elements of the provided matrix, rounding them toward positive infinity. </summary>
	/// <typeparam name="out_contained_type">Type to be contained in the output matrix.</typeparam>
	/// <typeparam name="Matrix_">Type of matrix to round the elements of.</typeparam>
	/// <param name="matrix_">EmuMath matrix to round the elements of.</param>
	/// <returns>Rounded form of the provided matrix.</returns>
	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename out_contained_type, bool OutColumnMajor_, class Matrix_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, out_contained_type, OutColumnMajor_> MatrixCeil(const Matrix_& matrix_)
	{
		if constexpr (EmuMath::TMP::is_emu_matrix_v<Matrix_>)
		{
			return _underlying_matrix_funcs::_make_mutated_matrix
			<
				EmuCore::do_ceil<typename Matrix_::value_type>,
				EmuMath::Matrix<OutNumColumns_, OutNumRows_, out_contained_type, OutColumnMajor_>,
				Matrix_
			>(matrix_);
		}
		else
		{
			static_assert(false, "Attempted to ceil a matrix, but the passed matrix_ was not an EmuMath matrix.");
		}
	}
	template<typename out_contained_type, bool OutColumnMajor_, class Matrix_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<Matrix_::num_columns, Matrix_::num_rows, out_contained_type, OutColumnMajor_> MatrixCeil(const Matrix_& matrix_)
	{
		return MatrixCeil<Matrix_::num_columns, Matrix_::num_rows, out_contained_type, OutColumnMajor_, Matrix_>(matrix_);
	}
	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, bool OutColumnMajor_, class Matrix_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, typename Matrix_::value_type, OutColumnMajor_> MatrixCeil(const Matrix_& matrix_)
	{
		return MatrixCeil<OutNumColumns_, OutNumRows_, typename Matrix_::value_type, OutColumnMajor_, Matrix_>(matrix_);
	}
	template<bool OutColumnMajor_, class Matrix_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<Matrix_::num_columns, Matrix_::num_rows, typename Matrix_::value_type, OutColumnMajor_> MatrixCeil
	(
		const Matrix_& matrix_
	)
	{
		return MatrixCeil<Matrix_::num_columns, Matrix_::num_rows, typename Matrix_::value_type, OutColumnMajor_, Matrix_>(matrix_);
	}
	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename out_contained_type, class Matrix_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, out_contained_type, Matrix_::is_column_major> MatrixCeil(const Matrix_& matrix_)
	{
		return MatrixCeil<OutNumColumns_, OutNumRows_, out_contained_type, Matrix_::is_column_major, Matrix_>(matrix_);
	}
	template<typename out_contained_type, class Matrix_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<Matrix_::num_columns, Matrix_::num_rows, out_contained_type, Matrix_::is_column_major> MatrixCeil(const Matrix_& matrix_)
	{
		return MatrixCeil<Matrix_::num_columns, Matrix_::num_rows, out_contained_type, Matrix_::is_column_major, Matrix_>(matrix_);
	}
	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, class Matrix_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, typename Matrix_::value_type, Matrix_::is_column_major> MatrixCeil(const Matrix_& matrix_)
	{
		return MatrixCeil<OutNumColumns_, OutNumRows_, typename Matrix_::value_type, Matrix_::is_column_major, Matrix_>(matrix_);
	}
	template<class Matrix_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<Matrix_::num_columns, Matrix_::num_rows, typename Matrix_::value_type, Matrix_::is_column_major> MatrixCeil
	(
		const Matrix_& matrix_
	)
	{
		return MatrixCeil<Matrix_::num_columns, Matrix_::num_rows, typename Matrix_::value_type, Matrix_::is_column_major, Matrix_>(matrix_);
	}

	/// <summary> Truncates all elements of the provided matrix, rounding them toward 0. </summary>
	/// <typeparam name="out_contained_type">Type to be contained in the output matrix.</typeparam>
	/// <typeparam name="Matrix_">Type of matrix to round the elements of.</typeparam>
	/// <param name="matrix_">EmuMath matrix to round the elements of.</param>
	/// <returns>Rounded form of the provided matrix.</returns>
	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename out_contained_type, bool OutColumnMajor_, class Matrix_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, out_contained_type, OutColumnMajor_> MatrixTrunc(const Matrix_& matrix_)
	{
		if constexpr (EmuMath::TMP::is_emu_matrix_v<Matrix_>)
		{
			return _underlying_matrix_funcs::_make_mutated_matrix
			<
				EmuCore::do_trunc<typename Matrix_::value_type>,
				EmuMath::Matrix<OutNumColumns_, OutNumRows_, out_contained_type, OutColumnMajor_>,
				Matrix_
			>(matrix_);
		}
		else
		{
			static_assert(false, "Attempted to trunc a matrix, but the passed matrix_ was not an EmuMath matrix.");
		}
	}
	template<typename out_contained_type, bool OutColumnMajor_, class Matrix_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<Matrix_::num_columns, Matrix_::num_rows, out_contained_type, OutColumnMajor_> MatrixTrunc(const Matrix_& matrix_)
	{
		return MatrixTrunc<Matrix_::num_columns, Matrix_::num_rows, out_contained_type, OutColumnMajor_, Matrix_>(matrix_);
	}
	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, bool OutColumnMajor_, class Matrix_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, typename Matrix_::value_type, OutColumnMajor_> MatrixTrunc(const Matrix_& matrix_)
	{
		return MatrixTrunc<OutNumColumns_, OutNumRows_, typename Matrix_::value_type, OutColumnMajor_, Matrix_>(matrix_);
	}
	template<bool OutColumnMajor_, class Matrix_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<Matrix_::num_columns, Matrix_::num_rows, typename Matrix_::value_type, OutColumnMajor_> MatrixTrunc
	(
		const Matrix_& matrix_
	)
	{
		return MatrixTrunc<Matrix_::num_columns, Matrix_::num_rows, typename Matrix_::value_type, OutColumnMajor_, Matrix_>(matrix_);
	}
	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename out_contained_type, class Matrix_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, out_contained_type, Matrix_::is_column_major> MatrixTrunc(const Matrix_& matrix_)
	{
		return MatrixTrunc<OutNumColumns_, OutNumRows_, out_contained_type, Matrix_::is_column_major, Matrix_>(matrix_);
	}
	template<typename out_contained_type, class Matrix_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<Matrix_::num_columns, Matrix_::num_rows, out_contained_type, Matrix_::is_column_major> MatrixTrunc(const Matrix_& matrix_)
	{
		return MatrixTrunc<Matrix_::num_columns, Matrix_::num_rows, out_contained_type, Matrix_::is_column_major, Matrix_>(matrix_);
	}
	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, class Matrix_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, typename Matrix_::value_type, Matrix_::is_column_major> MatrixTrunc(const Matrix_& matrix_)
	{
		return MatrixTrunc<OutNumColumns_, OutNumRows_, typename Matrix_::value_type, Matrix_::is_column_major, Matrix_>(matrix_);
	}
	template<class Matrix_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<Matrix_::num_columns, Matrix_::num_rows, typename Matrix_::value_type, Matrix_::is_column_major> MatrixTrunc
	(
		const Matrix_& matrix_
	)
	{
		return MatrixTrunc<Matrix_::num_columns, Matrix_::num_rows, typename Matrix_::value_type, Matrix_::is_column_major, Matrix_>(matrix_);
	}

	/// <summary>
	/// <para> Finds the smallest respective value for each element of lhs_matrix_ and rhs_. </para>
	/// <para> If rhs_ is an EmuMath matrix: Determined min elements will be for respective elements in lhs_matrix_ and rhs_. </para>
	/// <para> If rhs_ is none of the above: Determined min elements will be for respective elements in lhs_matrix_ and the value of rhs_. </para>
	/// </summary>
	/// <typeparam name="out_contained_type">Type to be contained in the output matrix.</typeparam>
	/// <typeparam name="LhsMatrix_">Type of matrix appearing as the left-hand argument.</typeparam>
	/// <typeparam name="Rhs_">Type of item appearing as the right-hand argument.</typeparam>
	/// <param name="lhs_matrix_">EmuMath matrix appearing as the left-hand argument.</param>
	/// <param name="lhs_matrix_">Item appearing as the right-hand argument.</param>
	/// <returns>Matrix containing the minimum values for respective elements betweeen lhs_matrix_ and rhs_.</returns>
	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename out_contained_type, bool OutColumnMajor_, class LhsMatrix_, class Rhs_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, out_contained_type, OutColumnMajor_> MatrixMin
	(
		const LhsMatrix_& lhs_matrix_,
		const Rhs_& rhs_
	)
	{
		if constexpr (EmuMath::TMP::is_emu_matrix_v<LhsMatrix_>)
		{
			return _underlying_matrix_funcs::_matrix_multi_arg_operation
			<
				EmuCore::do_min,
				EmuMath::Matrix<OutNumColumns_, OutNumRows_, out_contained_type, OutColumnMajor_>,
				LhsMatrix_,
				Rhs_
			>(lhs_matrix_, rhs_);
		}
		else
		{
			static_assert(false, "Attempted to find the minimum of elements between a lhs_matrix_ and a rhs_ arg, but the passed lhs_matrix_ was not an EmuMath matrix.");
		}
	}
	template<typename out_contained_type, bool OutColumnMajor_, class LhsMatrix_, class Rhs_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<LhsMatrix_::num_columns, LhsMatrix_::num_rows, out_contained_type, OutColumnMajor_> MatrixMin
	(
		const LhsMatrix_& lhs_matrix_,
		const Rhs_& rhs_
	)
	{
		return MatrixMin<LhsMatrix_::num_columns, LhsMatrix_::num_rows, out_contained_type, OutColumnMajor_, LhsMatrix_, Rhs_>(lhs_matrix_, rhs_);
	}
	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, bool OutColumnMajor_, class LhsMatrix_, class Rhs_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, typename LhsMatrix_::value_type, OutColumnMajor_> MatrixMin
	(
		const LhsMatrix_& lhs_matrix_,
		const Rhs_& rhs_
	)
	{
		return MatrixMin<OutNumColumns_, OutNumRows_, typename LhsMatrix_::value_type, OutColumnMajor_, LhsMatrix_, Rhs_>(lhs_matrix_, rhs_);
	}
	template<bool OutColumnMajor_, class LhsMatrix_, class Rhs_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<LhsMatrix_::num_columns, LhsMatrix_::num_rows, typename LhsMatrix_::value_type, OutColumnMajor_> MatrixMin
	(
		const LhsMatrix_& lhs_matrix_,
		const Rhs_& rhs_
	)
	{
		return MatrixMin<LhsMatrix_::num_columns, LhsMatrix_::num_rows, typename LhsMatrix_::value_type, OutColumnMajor_, LhsMatrix_, Rhs_>(lhs_matrix_, rhs_);
	}
	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename out_contained_type, class LhsMatrix_, class Rhs_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, out_contained_type, LhsMatrix_::is_column_major> MatrixMin
	(
		const LhsMatrix_& lhs_matrix_,
		const Rhs_& rhs_
	)
	{
		return MatrixMin<OutNumColumns_, OutNumRows_, out_contained_type, LhsMatrix_::is_column_major, LhsMatrix_, Rhs_>(lhs_matrix_, rhs_);
	}
	template<typename out_contained_type, class LhsMatrix_, class Rhs_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<LhsMatrix_::num_columns, LhsMatrix_::num_rows, out_contained_type, LhsMatrix_::is_column_major> MatrixMin
	(
		const LhsMatrix_& lhs_matrix_,
		const Rhs_& rhs_
	)
	{
		return MatrixMin<LhsMatrix_::num_columns, LhsMatrix_::num_rows, out_contained_type, LhsMatrix_::is_column_major, LhsMatrix_, Rhs_>(lhs_matrix_, rhs_);
	}
	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, class LhsMatrix_, class Rhs_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, typename LhsMatrix_::value_type, LhsMatrix_::is_column_major> MatrixMin
	(
		const LhsMatrix_& lhs_matrix_,
		const Rhs_& rhs_
	)
	{
		return MatrixMin<OutNumColumns_, OutNumRows_, typename LhsMatrix_::value_type, LhsMatrix_::is_column_major, LhsMatrix_, Rhs_>(lhs_matrix_, rhs_);
	}
	template<class LhsMatrix_, class Rhs_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<LhsMatrix_::num_columns, LhsMatrix_::num_rows, typename LhsMatrix_::value_type, LhsMatrix_::is_column_major> MatrixMin
	(
		const LhsMatrix_& lhs_matrix_,
		const Rhs_& rhs_
	)
	{
		return MatrixMin<LhsMatrix_::num_columns, LhsMatrix_::num_rows, typename LhsMatrix_::value_type, LhsMatrix_::is_column_major, LhsMatrix_, Rhs_>(lhs_matrix_, rhs_);
	}

	/// <summary>
	/// <para> Finds the greatest respective value for each element of lhs_matrix_ and rhs_. </para>
	/// <para> If rhs_ is an EmuMath matrix: Determined min elements will be for respective elements in lhs_matrix_ and rhs_. </para>
	/// <para> If rhs_ is none of the above: Determined min elements will be for respective elements in lhs_matrix_ and the value of rhs_. </para>
	/// </summary>
	/// <typeparam name="out_contained_type">Type to be contained in the output matrix.</typeparam>
	/// <typeparam name="LhsMatrix_">Type of matrix appearing as the left-hand argument.</typeparam>
	/// <typeparam name="Rhs_">Type of item appearing as the right-hand argument.</typeparam>
	/// <param name="lhs_matrix_">EmuMath matrix appearing as the left-hand argument.</param>
	/// <param name="lhs_matrix_">Item appearing as the right-hand argument.</param>
	/// <returns>Matrix containing the maximum values for respective elements betweeen lhs_matrix_ and rhs_.</returns>
	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename out_contained_type, bool OutColumnMajor_, class LhsMatrix_, class Rhs_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, out_contained_type, OutColumnMajor_> MatrixMax
	(
		const LhsMatrix_& lhs_matrix_,
		const Rhs_& rhs_
	)
	{
		if constexpr (EmuMath::TMP::is_emu_matrix_v<LhsMatrix_>)
		{
			return _underlying_matrix_funcs::_matrix_multi_arg_operation
			<
				EmuCore::do_max,
				EmuMath::Matrix<OutNumColumns_, OutNumRows_, out_contained_type, OutColumnMajor_>,
				LhsMatrix_,
				Rhs_
			>(lhs_matrix_, rhs_);
		}
		else
		{
			static_assert(false, "Attempted to find the maximum of elements between a lhs_matrix_ and a rhs_ arg, but the passed lhs_matrix_ was not an EmuMath matrix.");
		}
	}
	template<typename out_contained_type, bool OutColumnMajor_, class LhsMatrix_, class Rhs_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<LhsMatrix_::num_columns, LhsMatrix_::num_rows, out_contained_type, OutColumnMajor_> MatrixMax
	(
		const LhsMatrix_& lhs_matrix_,
		const Rhs_& rhs_
	)
	{
		return MatrixMax<LhsMatrix_::num_columns, LhsMatrix_::num_rows, out_contained_type, OutColumnMajor_, LhsMatrix_, Rhs_>(lhs_matrix_, rhs_);
	}
	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, bool OutColumnMajor_, class LhsMatrix_, class Rhs_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, typename LhsMatrix_::value_type, OutColumnMajor_> MatrixMax
	(
		const LhsMatrix_& lhs_matrix_,
		const Rhs_& rhs_
	)
	{
		return MatrixMax<OutNumColumns_, OutNumRows_, typename LhsMatrix_::value_type, OutColumnMajor_, LhsMatrix_, Rhs_>(lhs_matrix_, rhs_);
	}
	template<bool OutColumnMajor_, class LhsMatrix_, class Rhs_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<LhsMatrix_::num_columns, LhsMatrix_::num_rows, typename LhsMatrix_::value_type, OutColumnMajor_> MatrixMax
	(
		const LhsMatrix_& lhs_matrix_,
		const Rhs_& rhs_
	)
	{
		return MatrixMax<LhsMatrix_::num_columns, LhsMatrix_::num_rows, typename LhsMatrix_::value_type, OutColumnMajor_, LhsMatrix_, Rhs_>(lhs_matrix_, rhs_);
	}
	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename out_contained_type, class LhsMatrix_, class Rhs_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, out_contained_type, LhsMatrix_::is_column_major> MatrixMax
	(
		const LhsMatrix_& lhs_matrix_,
		const Rhs_& rhs_
	)
	{
		return MatrixMax<OutNumColumns_, OutNumRows_, out_contained_type, LhsMatrix_::is_column_major, LhsMatrix_, Rhs_>(lhs_matrix_, rhs_);
	}
	template<typename out_contained_type, class LhsMatrix_, class Rhs_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<LhsMatrix_::num_columns, LhsMatrix_::num_rows, out_contained_type, LhsMatrix_::is_column_major> MatrixMax
	(
		const LhsMatrix_& lhs_matrix_,
		const Rhs_& rhs_
	)
	{
		return MatrixMax<LhsMatrix_::num_columns, LhsMatrix_::num_rows, out_contained_type, LhsMatrix_::is_column_major, LhsMatrix_, Rhs_>(lhs_matrix_, rhs_);
	}
	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, class LhsMatrix_, class Rhs_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, typename LhsMatrix_::value_type, LhsMatrix_::is_column_major> MatrixMax
	(
		const LhsMatrix_& lhs_matrix_,
		const Rhs_& rhs_
	)
	{
		return MatrixMax<OutNumColumns_, OutNumRows_, typename LhsMatrix_::value_type, LhsMatrix_::is_column_major, LhsMatrix_, Rhs_>(lhs_matrix_, rhs_);
	}
	template<class LhsMatrix_, class Rhs_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<LhsMatrix_::num_columns, LhsMatrix_::num_rows, typename LhsMatrix_::value_type, LhsMatrix_::is_column_major> MatrixMax
	(
		const LhsMatrix_& lhs_matrix_,
		const Rhs_& rhs_
	)
	{
		return MatrixMax<LhsMatrix_::num_columns, LhsMatrix_::num_rows, typename LhsMatrix_::value_type, LhsMatrix_::is_column_major, LhsMatrix_, Rhs_>(lhs_matrix_, rhs_);
	}

	/// <summary>
	/// <para> Clamps the passed matrix_ so that none of its elements compares less than min_. </para>
	/// <para> If min_ is an EmuMath matrix: Elements in the passed matrix_ are clamped to a minimum of the respective element in min_. </para>
	/// <para> If min_ is none of the above: All elements in the passed matrix_ are clamped to a minimum of the value of min_. </para>
	/// </summary>
	/// <typeparam name="out_contained_type">Type to be contained in the output matrix.</typeparam>
	/// <typeparam name="Matrix_">Type of matrix to clamp.</typeparam>
	/// <typeparam name="Rhs_">Type used as the minimum value to clamp to.</typeparam>
	/// <param name="matrix_">EmuMath matrix to clamp.</param>
	/// <param name="min_">Item to clamp the matrix's minimum values to.</param>
	/// <returns>EmuMath matrix copy of the passed matrix_ with its elements clamped to a minimum via the passed min_ as defined above.</returns>
	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename out_contained_type, bool OutColumnMajor_, class Matrix_, class Min_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, out_contained_type, OutColumnMajor_> MatrixClampMin
	(
		const Matrix_& matrix_,
		const Min_& min_
	)
	{
		if constexpr (EmuMath::TMP::is_emu_matrix_v<Matrix_>)
		{
			return _underlying_matrix_funcs::_matrix_multi_arg_operation
			<
				EmuCore::do_clamp_min,
				EmuMath::Matrix<OutNumColumns_, OutNumRows_, out_contained_type, OutColumnMajor_>,
				Matrix_,
				Min_
			>(matrix_, min_);
		}
		else
		{
			static_assert(false, "Attempted to clamp the elements of an EmuMath matrix to minimum values, but the passed matrix_ was not an EmuMath matrix.");
		}
	}
	template<typename out_contained_type, bool OutColumnMajor_, class Matrix_, class Min_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<Matrix_::num_columns, Matrix_::num_rows, out_contained_type, OutColumnMajor_> MatrixClampMin
	(
		const Matrix_& matrix_,
		const Min_& min_
	)
	{
		return MatrixClampMin<Matrix_::num_columns, Matrix_::num_rows, out_contained_type, OutColumnMajor_, Matrix_, Min_>(matrix_, min_);
	}
	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, bool OutColumnMajor_, class Matrix_, class Min_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, typename Matrix_::value_type, OutColumnMajor_> MatrixClampMin
	(
		const Matrix_& matrix_,
		const Min_& min_
	)
	{
		return MatrixClampMin<OutNumColumns_, OutNumRows_, typename Matrix_::value_type, OutColumnMajor_, Matrix_, Min_>(matrix_, min_);
	}
	template<bool OutColumnMajor_, class Matrix_, class Min_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<Matrix_::num_columns, Matrix_::num_rows, typename Matrix_::value_type, OutColumnMajor_> MatrixClampMin
	(
		const Matrix_& matrix_,
		const Min_& min_
	)
	{
		return MatrixClampMin<Matrix_::num_columns, Matrix_::num_rows, typename Matrix_::value_type, OutColumnMajor_, Matrix_, Min_>(matrix_, min_);
	}
	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename out_contained_type, class Matrix_, class Min_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, out_contained_type, Matrix_::is_column_major> MatrixClampMin
	(
		const Matrix_& matrix_,
		const Min_& min_
	)
	{
		return MatrixClampMin<OutNumColumns_, OutNumRows_, out_contained_type, Matrix_::is_column_major, Matrix_, Min_>(matrix_, min_);
	}
	template<typename out_contained_type, class Matrix_, class Min_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<Matrix_::num_columns, Matrix_::num_rows, out_contained_type, Matrix_::is_column_major> MatrixClampMin
	(
		const Matrix_& matrix_,
		const Min_& min_
	)
	{
		return MatrixClampMin<Matrix_::num_columns, Matrix_::num_rows, out_contained_type, Matrix_::is_column_major, Matrix_, Min_>(matrix_, min_);
	}
	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, class Matrix_, class Min_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, typename Matrix_::value_type, Matrix_::is_column_major> MatrixClampMin
	(
		const Matrix_& matrix_,
		const Min_& min_
	)
	{
		return MatrixClampMin<OutNumColumns_, OutNumRows_, typename Matrix_::value_type, Matrix_::is_column_major, Matrix_, Min_>(matrix_, min_);
	}
	template<class Matrix_, class Min_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<Matrix_::num_columns, Matrix_::num_rows, typename Matrix_::value_type, Matrix_::is_column_major> MatrixClampMin
	(
		const Matrix_& matrix_,
		const Min_& min_
	)
	{
		return MatrixClampMin<Matrix_::num_columns, Matrix_::num_rows, typename Matrix_::value_type, Matrix_::is_column_major, Matrix_, Min_>(matrix_, min_);
	}

	/// <summary>
	/// <para> Clamps the passed matrix_ so that none of its elements compares greater than max_. </para>
	/// <para> If max_ is an EmuMath matrix: Elements in the passed matrix_ are clamped to a maximum of the respective element in max_. </para>
	/// <para> If max_ is none of the above: All elements in the passed matrix_ are clamped to a maximum of the value of max_. </para>
	/// </summary>
	/// <typeparam name="out_contained_type">Type to be contained in the output matrix.</typeparam>
	/// <typeparam name="Matrix_">Type of matrix to clamp.</typeparam>
	/// <typeparam name="Max_">Type used as the naximum value to clamp to.</typeparam>
	/// <param name="matrix_">EmuMath matrix to clamp.</param>
	/// <param name="max_">Item to clamp the matrix's max_imum values to.</param>
	/// <returns>EmuMath matrix copy of the passed matrix_ with its elements clamped to a maximum via the passed max_ as defined above.</returns>
	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename out_contained_type, bool OutColumnMajor_, class Matrix_, class Max_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, out_contained_type, OutColumnMajor_> MatrixClampMax
	(
		const Matrix_& matrix_,
		const Max_& max_
	)
	{
		if constexpr (EmuMath::TMP::is_emu_matrix_v<Matrix_>)
		{
			return _underlying_matrix_funcs::_matrix_multi_arg_operation
			<
				EmuCore::do_clamp_max,
				EmuMath::Matrix<OutNumColumns_, OutNumRows_, out_contained_type, OutColumnMajor_>,
				Matrix_,
				Max_
			>(matrix_, max_);
		}
		else
		{
			static_assert(false, "Attempted to clamp the elements of an EmuMath matrix to maximum values, but the passed matrix_ was not an EmuMath matrix.");
		}
	}
	template<typename out_contained_type, bool OutColumnMajor_, class Matrix_, class Max_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<Matrix_::num_columns, Matrix_::num_rows, out_contained_type, OutColumnMajor_> MatrixClampMax
	(
		const Matrix_& matrix_,
		const Max_& max_
	)
	{
		return MatrixClampMax<Matrix_::num_columns, Matrix_::num_rows, out_contained_type, OutColumnMajor_, Matrix_, Max_>(matrix_, max_);
	}
	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, bool OutColumnMajor_, class Matrix_, class Max_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, typename Matrix_::value_type, OutColumnMajor_> MatrixClampMax
	(
		const Matrix_& matrix_,
		const Max_& max_
	)
	{
		return MatrixClampMax<OutNumColumns_, OutNumRows_, typename Matrix_::value_type, OutColumnMajor_, Matrix_, Max_>(matrix_, max_);
	}
	template<bool OutColumnMajor_, class Matrix_, class Max_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<Matrix_::num_columns, Matrix_::num_rows, typename Matrix_::value_type, OutColumnMajor_> MatrixClampMax
	(
		const Matrix_& matrix_,
		const Max_& max_
	)
	{
		return MatrixClampMax<Matrix_::num_columns, Matrix_::num_rows, typename Matrix_::value_type, OutColumnMajor_, Matrix_, Max_>(matrix_, max_);
	}
	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename out_contained_type, class Matrix_, class Max_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, out_contained_type, Matrix_::is_column_major> MatrixClampMax
	(
		const Matrix_& matrix_,
		const Max_& max_
	)
	{
		return MatrixClampMax<OutNumColumns_, OutNumRows_, out_contained_type, Matrix_::is_column_major, Matrix_, Max_>(matrix_, max_);
	}
	template<typename out_contained_type, class Matrix_, class Max_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<Matrix_::num_columns, Matrix_::num_rows, out_contained_type, Matrix_::is_column_major> MatrixClampMax
	(
		const Matrix_& matrix_,
		const Max_& max_
	)
	{
		return MatrixClampMax<Matrix_::num_columns, Matrix_::num_rows, out_contained_type, Matrix_::is_column_major, Matrix_, Max_>(matrix_, max_);
	}
	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, class Matrix_, class Max_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, typename Matrix_::value_type, Matrix_::is_column_major> MatrixClampMax
	(
		const Matrix_& matrix_,
		const Max_& max_
	)
	{
		return MatrixClampMax<OutNumColumns_, OutNumRows_, typename Matrix_::value_type, Matrix_::is_column_major, Matrix_, Max_>(matrix_, max_);
	}
	template<class Matrix_, class Max_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<Matrix_::num_columns, Matrix_::num_rows, typename Matrix_::value_type, Matrix_::is_column_major> MatrixClampMax
	(
		const Matrix_& matrix_,
		const Max_& max_
	)
	{
		return MatrixClampMax<Matrix_::num_columns, Matrix_::num_rows, typename Matrix_::value_type, Matrix_::is_column_major, Matrix_, Max_>(matrix_, max_);
	}

	/// <summary>
	/// <para> Clamps the passed matrix_ so that none of its elements compares less than min_ or greater than max_. </para>
	/// <para> If min_ is an EmuMath matrix: Elements in the passed matrix_ are clamped to a minimum of the respective element in min_. </para>
	/// <para> If min_ is none of the above: All elements in the passed matrix_ are clamped to a minimum of the value of min_. </para>
	/// <para> If max_ is an EmuMath matrix: Elements in the passed matrix_ are clamped to a maximum of the respective element in max_. </para>
	/// <para> If max_ is none of the above: All elements in the passed matrix_ are clamped to a maximum of the value of max_. </para>
	/// <para> Both min_ and max_ are assumed to be logically correct (i.e. min_ &lt;= max_, or compared respective elements where either min_ and/or max_ is a matrix). </para>
	/// </summary>
	/// <typeparam name="out_contained_type">Type to be contained in the output matrix.</typeparam>
	/// <typeparam name="Matrix_">Type of matrix to clamp.</typeparam>
	/// <typeparam name="Min_">Type used as the minimum value to clamp to.</typeparam>
	/// <typeparam name="Max_">Type used as the minimum value to clamp to.</typeparam>
	/// <param name="matrix_">EmuMath matrix to clamp.</param>
	/// <param name="min_">Item to clamp the matrix's minimum values to.</param>
	/// <param name="max_">Item to clamp the matrix's maximum values to.</param>
	/// <returns>EmuMath matrix copy of the passed matrix_ with its elements between the provided min_ and max_ as defined above.</returns>
	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename out_contained_type, bool OutColumnMajor_, class Matrix_, class Min_, class Max_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, out_contained_type, OutColumnMajor_> MatrixClamp
	(
		const Matrix_& matrix_,
		const Min_& min_,
		const Max_& max_
	)
	{
		if constexpr (EmuMath::TMP::is_emu_matrix_v<Matrix_>)
		{
			return _underlying_matrix_funcs::_matrix_multi_arg_operation
			<
				EmuCore::do_clamp,
				EmuMath::Matrix<OutNumColumns_, OutNumRows_, out_contained_type, OutColumnMajor_>,
				Matrix_,
				Min_,
				Max_
			>(matrix_, min_, max_);
		}
		else
		{
			static_assert(false, "Attempted to clamp the elements of an EmuMath matrix, but the passed matrix_ was not an EmuMath matrix.");
		}
	}
	template<typename out_contained_type, bool OutColumnMajor_, class Matrix_, class Min_, class Max_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<Matrix_::num_columns, Matrix_::num_rows, out_contained_type, OutColumnMajor_> MatrixClamp
	(
		const Matrix_& matrix_,
		const Min_& min_,
		const Max_& max_
	)
	{
		return MatrixClamp<Matrix_::num_columns, Matrix_::num_rows, out_contained_type, OutColumnMajor_, Matrix_, Min_, Max_>(matrix_, min_, max_);
	}
	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, bool OutColumnMajor_, class Matrix_, class Min_, class Max_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, typename Matrix_::value_type, OutColumnMajor_> MatrixClamp
	(
		const Matrix_& matrix_,
		const Min_& min_,
		const Max_& max_
	)
	{
		return MatrixClamp<OutNumColumns_, OutNumRows_, typename Matrix_::value_type, OutColumnMajor_, Matrix_, Min_, Max_>(matrix_, min_, max_);
	}
	template<bool OutColumnMajor_, class Matrix_, class Min_, class Max_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<Matrix_::num_columns, Matrix_::num_rows, typename Matrix_::value_type, OutColumnMajor_> MatrixClamp
	(
		const Matrix_& matrix_,
		const Min_& min_,
		const Max_& max_
	)
	{
		return MatrixClamp<Matrix_::num_columns, Matrix_::num_rows, typename Matrix_::value_type, OutColumnMajor_, Matrix_, Min_, Max_>(matrix_, min_, max_);
	}


	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename out_contained_type, class Matrix_, class Min_, class Max_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, out_contained_type, Matrix_::is_column_major> MatrixClamp
	(
		const Matrix_& matrix_,
		const Min_& min_,
		const Max_& max_
	)
	{
		return MatrixClamp<OutNumColumns_, OutNumRows_, out_contained_type, Matrix_::is_column_major, Matrix_, Min_, Max_>(matrix_, min_, max_);
	}
	template<typename out_contained_type, class Matrix_, class Min_, class Max_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<Matrix_::num_columns, Matrix_::num_rows, out_contained_type, Matrix_::is_column_major> MatrixClamp
	(
		const Matrix_& matrix_,
		const Min_& min_,
		const Max_& max_
	)
	{
		return MatrixClamp<Matrix_::num_columns, Matrix_::num_rows, out_contained_type, Matrix_::is_column_major, Matrix_, Min_, Max_>(matrix_, min_, max_);
	}
	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, class Matrix_, class Min_, class Max_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, typename Matrix_::value_type, Matrix_::is_column_major> MatrixClamp
	(
		const Matrix_& matrix_,
		const Min_& min_,
		const Max_& max_
	)
	{
		return MatrixClamp<OutNumColumns_, OutNumRows_, typename Matrix_::value_type, Matrix_::is_column_major, Matrix_, Min_, Max_>(matrix_, min_, max_);
	}
	template<class Matrix_, class Min_, class Max_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<Matrix_::num_columns, Matrix_::num_rows, typename Matrix_::value_type, Matrix_::is_column_major> MatrixClamp
	(
		const Matrix_& matrix_,
		const Min_& min_,
		const Max_& max_
	)
	{
		return MatrixClamp<Matrix_::num_columns, Matrix_::num_rows, typename Matrix_::value_type, Matrix_::is_column_major, Matrix_, Min_, Max_>(matrix_, min_, max_);
	}

	/// <summary>
	/// <para> Linearly interpolates the elements of matrix_a_ using the target b_ and weighting t_. Result may be summarised as a + ((b - a) * t). </para>
	/// <para> If b_ is an EmuMath matrix, elements in matrix_a_ will be interpolated with respective elements of b_ used as targets. </para>
	/// <para> If b_ is none of the above: elements in matrix_a_ will all be interpolated with a target of the value of b_. </para>
	/// <para> If t_ is an EmuMath matrix, elements in matrix_a_ will be interpolated with respective elements of t_ used as weightings. </para>
	/// <para> If b_ is none of the above: elements in matrix_a_ will all be interpolated with a target of the value of t_. </para>
	/// </summary>
	/// <typeparam name="MatrixA_">Type of matrix to linearly interpolate the elements of.</typeparam>
	/// <typeparam name="B_">Type representing the target for interpolation.</typeparam>
	/// <typeparam name="T_">Type representing the weighting for interpolation.</typeparam>
	/// <param name="matrix_a_">EmuMath matrix to linearly interpolate the elements of.</param>
	/// <param name="b_">Item to provide a target for elements of matrix_a_ to interpolate towards.</param>
	/// <param name="t_">Item to provide the weightings for how much matrix_a_ elements should interpolate towards their target.</param>
	/// <returns>Resulting matrix from linear interpolation using the provided arguments as defined above.</returns>
	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename out_contained_type, bool OutColumnMajor_, class MatrixA_, class B_, class T_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, out_contained_type, OutColumnMajor_> MatrixLerp
	(
		const MatrixA_& matrix_a_,
		const B_& b_,
		const T_& t_
	)
	{
		if constexpr (EmuMath::TMP::is_emu_matrix_v<MatrixA_>)
		{
			return _underlying_matrix_funcs::_matrix_multi_arg_operation
			<
				EmuCore::do_lerp,
				EmuMath::Matrix<OutNumColumns_, OutNumRows_, out_contained_type, OutColumnMajor_>,
				MatrixA_,
				B_,
				T_
			>(matrix_a_, b_, t_);
		}
		else
		{
			static_assert(false, "Attempted to lineraly interpolate the elements of an EmuMath matrix, but the passed matrix_a_ was not an EmuMath matrix.");
		}
	}
	template<typename out_contained_type, bool OutColumnMajor_, class MatrixA_, class B_, class T_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<MatrixA_::num_columns, MatrixA_::num_rows, out_contained_type, OutColumnMajor_> MatrixLerp
	(
		const MatrixA_& matrix_a_,
		const B_& b_,
		const T_& t_
	)
	{
		return MatrixLerp<MatrixA_::num_columns, MatrixA_::num_rows, out_contained_type, OutColumnMajor_, MatrixA_, B_, T_>(matrix_a_, b_, t_);
	}
	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, bool OutColumnMajor_, class MatrixA_, class B_, class T_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, typename MatrixA_::value_type, OutColumnMajor_> MatrixLerp
	(
		const MatrixA_& matrix_a_,
		const B_& b_,
		const T_& t_
	)
	{
		return MatrixLerp<OutNumColumns_, OutNumRows_, typename MatrixA_::value_type, OutColumnMajor_, MatrixA_, B_, T_>(matrix_a_, b_, t_);
	}
	template<bool OutColumnMajor_, class MatrixA_, class B_, class T_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<MatrixA_::num_columns, MatrixA_::num_rows, typename MatrixA_::value_type, OutColumnMajor_> MatrixLerp
	(
		const MatrixA_& matrix_a_,
		const B_& b_,
		const T_& t_
	)
	{
		return MatrixLerp<MatrixA_::num_columns, MatrixA_::num_rows, typename MatrixA_::value_type, OutColumnMajor_, MatrixA_, B_, T_>(matrix_a_, b_, t_);
	}


	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename out_contained_type, class MatrixA_, class B_, class T_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, out_contained_type, MatrixA_::is_column_major> MatrixLerp
	(
		const MatrixA_& matrix_a_,
		const B_& b_,
		const T_& t_
	)
	{
		return MatrixLerp<OutNumColumns_, OutNumRows_, out_contained_type, MatrixA_::is_column_major, MatrixA_, B_, T_>(matrix_a_, b_, t_);
	}
	template<typename out_contained_type, class MatrixA_, class B_, class T_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<MatrixA_::num_columns, MatrixA_::num_rows, out_contained_type, MatrixA_::is_column_major> MatrixLerp
	(
		const MatrixA_& matrix_a_,
		const B_& b_,
		const T_& t_
	)
	{
		return MatrixLerp<MatrixA_::num_columns, MatrixA_::num_rows, out_contained_type, MatrixA_::is_column_major, MatrixA_, B_, T_>(matrix_a_, b_, t_);
	}
	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, class MatrixA_, class B_, class T_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, typename MatrixA_::value_type, MatrixA_::is_column_major> MatrixLerp
	(
		const MatrixA_& matrix_a_,
		const B_& b_,
		const T_& t_
	)
	{
		return MatrixLerp<OutNumColumns_, OutNumRows_, typename MatrixA_::value_type, MatrixA_::is_column_major, MatrixA_, B_, T_>(matrix_a_, b_, t_);
	}
	template<class MatrixA_, class B_, class T_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<MatrixA_::num_columns, MatrixA_::num_rows, typename MatrixA_::value_type, MatrixA_::is_column_major> MatrixLerp
	(
		const MatrixA_& matrix_a_,
		const B_& b_,
		const T_& t_
	)
	{
		return MatrixLerp<MatrixA_::num_columns, MatrixA_::num_rows, typename MatrixA_::value_type, MatrixA_::is_column_major, MatrixA_, B_, T_>(matrix_a_, b_, t_);
	}

	/// <summary>
	/// <para> Performs a basic modulo division operation on lhs_ using the passed rhs_. </para>
	/// <para>
	///		If the passed rhs_ is a matrix, respective indices in each matrix will be divided. 
	///		Otherwise, each index in the lhs_ matrix will be divided by rhs_.
	/// </para>
	/// <para> NOTE: This is NOT a standard matrix mod operation. Such behaviour is mathematically undefined. </para>
	/// </summary>
	/// <typeparam name="out_contained_type">Type to be contained within the result matrix.</typeparam>
	/// <typeparam name="LhsMatrix_">Type of matrix appearing on the left-hand side of division.</typeparam>
	/// <typeparam name="Rhs_">Type of matrix or scalar appearing on the right-hand side of division.</typeparam>
	/// <param name="lhs_">EmuMath matrix appearing on the left-hand side of division.</param>
	/// <param name="rhs_">EmuMath matrix or scalar appearing on the right-hand side of division.</param>
	/// <returns>Matrix containing the results of performing a basic modulo division on the lhs_ matrix by the provided rhs_.</returns>
	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename out_contained_type, bool OutColumnMajor_, class LhsMatrix_, class Rhs_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, out_contained_type, OutColumnMajor_> MatrixModBasic
	(
		const LhsMatrix_& lhs_,
		const Rhs_& rhs_
	)
	{
		if constexpr (EmuMath::TMP::is_emu_matrix_v<LhsMatrix_>)
		{
			return _underlying_matrix_funcs::_matrix_multi_arg_operation
			<
				EmuCore::do_mod,
				EmuMath::Matrix<OutNumColumns_, OutNumRows_, out_contained_type, OutColumnMajor_>,
				LhsMatrix_,
				Rhs_
			>(lhs_, rhs_);
		}
		else
		{
			static_assert(false, "Attempted to perform basic matrix modulo division, but provided a non-EmuMath-matrix lhs_ argument.");
		}
	}
	template<typename out_contained_type, bool OutColumnMajor_, class LhsMatrix_, class Rhs_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<LhsMatrix_::num_columns, LhsMatrix_::num_rows, out_contained_type, OutColumnMajor_> MatrixModBasic
	(
		const LhsMatrix_& lhs_,
		const Rhs_& rhs_
	)
	{
		return MatrixModBasic<LhsMatrix_::num_columns, LhsMatrix_::num_rows, out_contained_type, OutColumnMajor_, LhsMatrix_, Rhs_>(lhs_, rhs_);
	}
	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, bool OutColumnMajor_, class LhsMatrix_, class Rhs_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, typename LhsMatrix_::value_type, OutColumnMajor_> MatrixModBasic
	(
		const LhsMatrix_& lhs_,
		const Rhs_& rhs_
	)
	{
		return MatrixModBasic<OutNumColumns_, OutNumRows_, typename LhsMatrix_::value_type, OutColumnMajor_, LhsMatrix_, Rhs_>(lhs_, rhs_);
	}
	template<bool OutColumnMajor_, class LhsMatrix_, class Rhs_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<LhsMatrix_::num_columns, LhsMatrix_::num_rows, typename LhsMatrix_::value_type, OutColumnMajor_> MatrixModBasic
	(
		const LhsMatrix_& lhs_,
		const Rhs_& rhs_
	)
	{
		return MatrixModBasic<LhsMatrix_::num_columns, LhsMatrix_::num_rows, typename LhsMatrix_::value_type, OutColumnMajor_, LhsMatrix_, Rhs_>(lhs_, rhs_);
	}

	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename out_contained_type, class LhsMatrix_, class Rhs_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, out_contained_type, LhsMatrix_::is_column_major> MatrixModBasic
	(
		const LhsMatrix_& lhs_,
		const Rhs_& rhs_
	)
	{
		return MatrixModBasic<OutNumColumns_, OutNumRows_, out_contained_type, LhsMatrix_::is_column_major, LhsMatrix_, Rhs_>(lhs_, rhs_);
	}
	template<typename out_contained_type, class LhsMatrix_, class Rhs_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<LhsMatrix_::num_columns, LhsMatrix_::num_rows, out_contained_type, LhsMatrix_::is_column_major> MatrixModBasic
	(
		const LhsMatrix_& lhs_,
		const Rhs_& rhs_
	)
	{
		return MatrixModBasic<LhsMatrix_::num_columns, LhsMatrix_::num_rows, out_contained_type, LhsMatrix_::is_column_major, LhsMatrix_, Rhs_>(lhs_, rhs_);
	}
	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, class LhsMatrix_, class Rhs_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, typename LhsMatrix_::value_type, LhsMatrix_::is_column_major> MatrixModBasic
	(
		const LhsMatrix_& lhs_,
		const Rhs_& rhs_
	)
	{
		return MatrixModBasic<OutNumColumns_, OutNumRows_, typename LhsMatrix_::value_type, LhsMatrix_::is_column_major, LhsMatrix_, Rhs_>(lhs_, rhs_);
	}
	template<class LhsMatrix_, class Rhs_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<LhsMatrix_::num_columns, LhsMatrix_::num_rows, typename LhsMatrix_::value_type, LhsMatrix_::is_column_major>
	MatrixModBasic
	(
		const LhsMatrix_& lhs_,
		const Rhs_& rhs_
	)
	{
		return MatrixModBasic<LhsMatrix_::num_columns, LhsMatrix_::num_rows, typename LhsMatrix_::value_type, LhsMatrix_::is_column_major, LhsMatrix_, Rhs_>(lhs_, rhs_);
	}
}

#endif
