#ifndef EMU_MATH_HELPERS_MATRIX_BITWISE_H_INC_
#define EMU_MATH_HELPERS_MATRIX_BITWISE_H_INC_

#include "_common_matrix_helper_includes.h"

namespace EmuMath::Helpers
{
	/// <summary>
	/// <para> Performs a bitwise AND operation on the elements of the lhs_ matrix and provided rhs_. </para>
	/// <para> If rhs_ is an EmuMath matrix: Respective elements will be ANDed. </para>
	/// <para> If rhs_ is none of the above: All elements within lhs_ will be ANDed with the value of rhs_. </para>
	/// </summary>
	/// <typeparam name="out_contained_type">Type to be contained in the output matrix.</typeparam>
	/// <typeparam name="LhsMatrix_">Type of matrix appearing on the left of a bitwise AND.</typeparam>
	/// <typeparam name="Rhs_">Type appearing of the right of a bitwise AND.</typeparam>
	/// <param name="lhs_">EmuMath matrix appearing of the left of a bitwise AND.</param>
	/// <param name="rhs_">Item appearing on the right of a bitwise AND.</param>
	/// <returns>Matrix resulting from a bitwise AND between lhs_ and rhs_.</returns>
	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename out_contained_type, bool OutColumnMajor_, class LhsMatrix_, class Rhs_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, out_contained_type, OutColumnMajor_> MatrixAnd
	(
		const LhsMatrix_& lhs_,
		const Rhs_& rhs_
	)
	{
		if constexpr (EmuMath::TMP::is_emu_matrix_v<LhsMatrix_>)
		{
			return _underlying_matrix_funcs::_matrix_multi_arg_operation
			<
				EmuCore::do_bitwise_and,
				EmuMath::Matrix<OutNumColumns_, OutNumRows_, out_contained_type, OutColumnMajor_>,
				LhsMatrix_,
				Rhs_
			>(lhs_, rhs_);
		}
		else
		{
			static_assert(false, "Attempted to perform matrix bitwise AND, but provided a non-EmuMath-matrix lhs_ argument.");
		}
	}
	template<typename out_contained_type, bool OutColumnMajor_, class LhsMatrix_, class Rhs_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<LhsMatrix_::num_columns, LhsMatrix_::num_rows, out_contained_type, OutColumnMajor_> MatrixAnd
	(
		const LhsMatrix_& lhs_,
		const Rhs_& rhs_
	)
	{
		return MatrixAnd<LhsMatrix_::num_columns, LhsMatrix_::num_rows, out_contained_type, OutColumnMajor_, LhsMatrix_, Rhs_>(lhs_, rhs_);
	}
	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, bool OutColumnMajor_, class LhsMatrix_, class Rhs_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, typename LhsMatrix_::value_type, OutColumnMajor_> MatrixAnd
	(
		const LhsMatrix_& lhs_,
		const Rhs_& rhs_
	)
	{
		return MatrixAnd<OutNumColumns_, OutNumRows_, typename LhsMatrix_::value_type, OutColumnMajor_, LhsMatrix_, Rhs_>(lhs_, rhs_);
	}
	template<bool OutColumnMajor_, class LhsMatrix_, class Rhs_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<LhsMatrix_::num_columns, LhsMatrix_::num_rows, typename LhsMatrix_::value_type, OutColumnMajor_> MatrixAnd
	(
		const LhsMatrix_& lhs_,
		const Rhs_& rhs_
	)
	{
		return MatrixAnd<LhsMatrix_::num_columns, LhsMatrix_::num_rows, typename LhsMatrix_::value_type, OutColumnMajor_, LhsMatrix_, Rhs_>(lhs_, rhs_);
	}

	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename out_contained_type, class LhsMatrix_, class Rhs_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, out_contained_type, LhsMatrix_::is_column_major> MatrixAnd
	(
		const LhsMatrix_& lhs_,
		const Rhs_& rhs_
	)
	{
		return MatrixAnd<OutNumColumns_, OutNumRows_, out_contained_type, LhsMatrix_::is_column_major, LhsMatrix_, Rhs_>(lhs_, rhs_);
	}
	template<typename out_contained_type, class LhsMatrix_, class Rhs_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<LhsMatrix_::num_columns, LhsMatrix_::num_rows, out_contained_type, LhsMatrix_::is_column_major> MatrixAnd
	(
		const LhsMatrix_& lhs_,
		const Rhs_& rhs_
	)
	{
		return MatrixAnd<LhsMatrix_::num_columns, LhsMatrix_::num_rows, out_contained_type, LhsMatrix_::is_column_major, LhsMatrix_, Rhs_>(lhs_, rhs_);
	}
	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, class LhsMatrix_, class Rhs_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, typename LhsMatrix_::value_type, LhsMatrix_::is_column_major> MatrixAnd
	(
		const LhsMatrix_& lhs_,
		const Rhs_& rhs_
	)
	{
		return MatrixAnd<OutNumColumns_, OutNumRows_, typename LhsMatrix_::value_type, LhsMatrix_::is_column_major, LhsMatrix_, Rhs_>(lhs_, rhs_);
	}
	template<class LhsMatrix_, class Rhs_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<LhsMatrix_::num_columns, LhsMatrix_::num_rows, typename LhsMatrix_::value_type, LhsMatrix_::is_column_major> MatrixAnd
	(
		const LhsMatrix_& lhs_,
		const Rhs_& rhs_
	)
	{
		return MatrixAnd<LhsMatrix_::num_columns, LhsMatrix_::num_rows, typename LhsMatrix_::value_type, LhsMatrix_::is_column_major, LhsMatrix_, Rhs_>(lhs_, rhs_);
	}

	/// <summary>
	/// <para> Performs a bitwise OR operation on the elements of the lhs_ matrix and provided rhs_. </para>
	/// <para> If rhs_ is an EmuMath matrix: Respective elements will be ORed. </para>
	/// <para> If rhs_ is none of the above: All elements within lhs_ will be ORed with the value of rhs_. </para>
	/// </summary>
	/// <typeparam name="out_contained_type">Type to be contained in the output matrix.</typeparam>
	/// <typeparam name="LhsMatrix_">Type of matrix appearing on the left of a bitwise OR.</typeparam>
	/// <typeparam name="Rhs_">Type appearing of the right of a bitwise OR.</typeparam>
	/// <param name="lhs_">EmuMath matrix appearing of the left of a bitwise OR.</param>
	/// <param name="rhs_">Item appearing on the right of a bitwise OR.</param>
	/// <returns>Matrix resulting from a bitwise OR between lhs_ and rhs_.</returns>
	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename out_contained_type, bool OutColumnMajor_, class LhsMatrix_, class Rhs_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, out_contained_type, OutColumnMajor_> MatrixOr
	(
		const LhsMatrix_& lhs_,
		const Rhs_& rhs_
	)
	{
		if constexpr (EmuMath::TMP::is_emu_matrix_v<LhsMatrix_>)
		{
			return _underlying_matrix_funcs::_matrix_multi_arg_operation
			<
				EmuCore::do_bitwise_or,
				EmuMath::Matrix<OutNumColumns_, OutNumRows_, out_contained_type, OutColumnMajor_>,
				LhsMatrix_,
				Rhs_
			>(lhs_, rhs_);
		}
		else
		{
			static_assert(false, "Attempted to perform matrix bitwise OR, but provided a non-EmuMath-matrix lhs_ argument.");
		}
	}
	template<typename out_contained_type, bool OutColumnMajor_, class LhsMatrix_, class Rhs_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<LhsMatrix_::num_columns, LhsMatrix_::num_rows, out_contained_type, OutColumnMajor_> MatrixOr
	(
		const LhsMatrix_& lhs_,
		const Rhs_& rhs_
	)
	{
		return MatrixOr<LhsMatrix_::num_columns, LhsMatrix_::num_rows, out_contained_type, OutColumnMajor_, LhsMatrix_, Rhs_>(lhs_, rhs_);
	}
	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, bool OutColumnMajor_, class LhsMatrix_, class Rhs_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, typename LhsMatrix_::value_type, OutColumnMajor_> MatrixOr
	(
		const LhsMatrix_& lhs_,
		const Rhs_& rhs_
	)
	{
		return MatrixOr<OutNumColumns_, OutNumRows_, typename LhsMatrix_::value_type, OutColumnMajor_, LhsMatrix_, Rhs_>(lhs_, rhs_);
	}
	template<bool OutColumnMajor_, class LhsMatrix_, class Rhs_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<LhsMatrix_::num_columns, LhsMatrix_::num_rows, typename LhsMatrix_::value_type, OutColumnMajor_> MatrixOr
	(
		const LhsMatrix_& lhs_,
		const Rhs_& rhs_
	)
	{
		return MatrixOr<LhsMatrix_::num_columns, LhsMatrix_::num_rows, typename LhsMatrix_::value_type, OutColumnMajor_, LhsMatrix_, Rhs_>(lhs_, rhs_);
	}

	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename out_contained_type, class LhsMatrix_, class Rhs_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, out_contained_type, LhsMatrix_::is_column_major> MatrixOr
	(
		const LhsMatrix_& lhs_,
		const Rhs_& rhs_
	)
	{
		return MatrixOr<OutNumColumns_, OutNumRows_, out_contained_type, LhsMatrix_::is_column_major, LhsMatrix_, Rhs_>(lhs_, rhs_);
	}
	template<typename out_contained_type, class LhsMatrix_, class Rhs_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<LhsMatrix_::num_columns, LhsMatrix_::num_rows, out_contained_type, LhsMatrix_::is_column_major> MatrixOr
	(
		const LhsMatrix_& lhs_,
		const Rhs_& rhs_
	)
	{
		return MatrixOr<LhsMatrix_::num_columns, LhsMatrix_::num_rows, out_contained_type, LhsMatrix_::is_column_major, LhsMatrix_, Rhs_>(lhs_, rhs_);
	}
	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, class LhsMatrix_, class Rhs_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, typename LhsMatrix_::value_type, LhsMatrix_::is_column_major> MatrixOr
	(
		const LhsMatrix_& lhs_,
		const Rhs_& rhs_
	)
	{
		return MatrixOr<OutNumColumns_, OutNumRows_, typename LhsMatrix_::value_type, LhsMatrix_::is_column_major, LhsMatrix_, Rhs_>(lhs_, rhs_);
	}
	template<class LhsMatrix_, class Rhs_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<LhsMatrix_::num_columns, LhsMatrix_::num_rows, typename LhsMatrix_::value_type, LhsMatrix_::is_column_major> MatrixOr
	(
		const LhsMatrix_& lhs_,
		const Rhs_& rhs_
	)
	{
		return MatrixOr<LhsMatrix_::num_columns, LhsMatrix_::num_rows, typename LhsMatrix_::value_type, LhsMatrix_::is_column_major, LhsMatrix_, Rhs_>(lhs_, rhs_);
	}

	/// <summary>
	/// <para> Performs a bitwise XOR operation on the elements of the lhs_ matrix and provided rhs_. </para>
	/// <para> If rhs_ is an EmuMath matrix: Respective elements will be XORed. </para>
	/// <para> If rhs_ is none of the above: All elements within lhs_ will be XORed with the value of rhs_. </para>
	/// </summary>
	/// <typeparam name="out_contained_type">Type to be contained in the output matrix.</typeparam>
	/// <typeparam name="LhsMatrix_">Type of matrix appearing on the left of a bitwise XOR.</typeparam>
	/// <typeparam name="Rhs_">Type appearing of the right of a bitwise XOR.</typeparam>
	/// <param name="lhs_">EmuMath matrix appearing of the left of a bitwise XOR.</param>
	/// <param name="rhs_">Item appearing on the right of a bitwise XOR.</param>
	/// <returns>Matrix resulting from a bitwise XOR between lhs_ and rhs_.</returns>
	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename out_contained_type, bool OutColumnMajor_, class LhsMatrix_, class Rhs_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, out_contained_type, OutColumnMajor_> MatrixXor
	(
		const LhsMatrix_& lhs_,
		const Rhs_& rhs_
	)
	{
		if constexpr (EmuMath::TMP::is_emu_matrix_v<LhsMatrix_>)
		{
			return _underlying_matrix_funcs::_matrix_multi_arg_operation
			<
				EmuCore::do_bitwise_xor,
				EmuMath::Matrix<OutNumColumns_, OutNumRows_, out_contained_type, OutColumnMajor_>,
				LhsMatrix_,
				Rhs_
			>(lhs_, rhs_);
		}
		else
		{
			static_assert(false, "Attempted to perform matrix bitwise XOR, but provided a non-EmuMath-matrix lhs_ argument.");
		}
	}
	template<typename out_contained_type, bool OutColumnMajor_, class LhsMatrix_, class Rhs_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<LhsMatrix_::num_columns, LhsMatrix_::num_rows, out_contained_type, OutColumnMajor_> MatrixXor
	(
		const LhsMatrix_& lhs_,
		const Rhs_& rhs_
	)
	{
		return MatrixXor<LhsMatrix_::num_columns, LhsMatrix_::num_rows, out_contained_type, OutColumnMajor_, LhsMatrix_, Rhs_>(lhs_, rhs_);
	}
	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, bool OutColumnMajor_, class LhsMatrix_, class Rhs_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, typename LhsMatrix_::value_type, OutColumnMajor_> MatrixXor
	(
		const LhsMatrix_& lhs_,
		const Rhs_& rhs_
	)
	{
		return MatrixXor<OutNumColumns_, OutNumRows_, typename LhsMatrix_::value_type, OutColumnMajor_, LhsMatrix_, Rhs_>(lhs_, rhs_);
	}
	template<bool OutColumnMajor_, class LhsMatrix_, class Rhs_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<LhsMatrix_::num_columns, LhsMatrix_::num_rows, typename LhsMatrix_::value_type, OutColumnMajor_> MatrixXor
	(
		const LhsMatrix_& lhs_,
		const Rhs_& rhs_
	)
	{
		return MatrixXor<LhsMatrix_::num_columns, LhsMatrix_::num_rows, typename LhsMatrix_::value_type, OutColumnMajor_, LhsMatrix_, Rhs_>(lhs_, rhs_);
	}

	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename out_contained_type, class LhsMatrix_, class Rhs_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, out_contained_type, LhsMatrix_::is_column_major> MatrixXor
	(
		const LhsMatrix_& lhs_,
		const Rhs_& rhs_
	)
	{
		return MatrixXor<OutNumColumns_, OutNumRows_, out_contained_type, LhsMatrix_::is_column_major, LhsMatrix_, Rhs_>(lhs_, rhs_);
	}
	template<typename out_contained_type, class LhsMatrix_, class Rhs_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<LhsMatrix_::num_columns, LhsMatrix_::num_rows, out_contained_type, LhsMatrix_::is_column_major> MatrixXor
	(
		const LhsMatrix_& lhs_,
		const Rhs_& rhs_
	)
	{
		return MatrixXor<LhsMatrix_::num_columns, LhsMatrix_::num_rows, out_contained_type, LhsMatrix_::is_column_major, LhsMatrix_, Rhs_>(lhs_, rhs_);
	}
	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, class LhsMatrix_, class Rhs_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, typename LhsMatrix_::value_type, LhsMatrix_::is_column_major> MatrixXor
	(
		const LhsMatrix_& lhs_,
		const Rhs_& rhs_
	)
	{
		return MatrixXor<OutNumColumns_, OutNumRows_, typename LhsMatrix_::value_type, LhsMatrix_::is_column_major, LhsMatrix_, Rhs_>(lhs_, rhs_);
	}
	template<class LhsMatrix_, class Rhs_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<LhsMatrix_::num_columns, LhsMatrix_::num_rows, typename LhsMatrix_::value_type, LhsMatrix_::is_column_major> MatrixXor
	(
		const LhsMatrix_& lhs_,
		const Rhs_& rhs_
	)
	{
		return MatrixXor<LhsMatrix_::num_columns, LhsMatrix_::num_rows, typename LhsMatrix_::value_type, LhsMatrix_::is_column_major, LhsMatrix_, Rhs_>(lhs_, rhs_);
	}

	/// <summary> Returns a bit-inverted version of the passed EmuMath matrix, where all elements [x][y] can be summarised as ~[x][y]. </summary>
	/// <typeparam name="out_contained_type">Type to be contained in the output matrix.</typeparam>
	/// <typeparam name="Matrix_">Type of matrix to negate.</typeparam>
	/// <param name="matrix_">EmuMath matrix to negate.</param>
	/// <returns>Copy of the provided matrix after a bitwise NOT operation.</returns>
	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename out_contained_type, bool OutColumnMajor_, class Matrix_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, out_contained_type, OutColumnMajor_> MatrixNot(const Matrix_& matrix_)
	{
		if constexpr (EmuMath::TMP::is_emu_matrix_v<Matrix_>)
		{
			return _underlying_matrix_funcs::_make_mutated_matrix
			<
				EmuCore::do_bitwise_not<typename Matrix_::value_type>,
				EmuMath::Matrix<OutNumColumns_, OutNumRows_, out_contained_type, OutColumnMajor_>,
				Matrix_
			>(matrix_);
		}
		else
		{
			static_assert(false, "Attempted to perform a bitwise NOT on a matrix, but the passed matrix_ was not an EmuMath matrix.");
		}
	}
	template<typename out_contained_type, bool OutColumnMajor_, class Matrix_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<Matrix_::num_columns, Matrix_::num_rows, out_contained_type, OutColumnMajor_> MatrixNot(const Matrix_& matrix_)
	{
		return MatrixNot<Matrix_::num_columns, Matrix_::num_rows, out_contained_type, OutColumnMajor_, Matrix_>(matrix_);
	}
	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, bool OutColumnMajor_, class Matrix_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, typename Matrix_::value_type, OutColumnMajor_> MatrixNot(const Matrix_& matrix_)
	{
		return MatrixNot<OutNumColumns_, OutNumRows_, typename Matrix_::value_type, OutColumnMajor_, Matrix_>(matrix_);
	}
	template<bool OutColumnMajor_, class Matrix_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<Matrix_::num_columns, Matrix_::num_rows, typename Matrix_::value_type, OutColumnMajor_> MatrixNot
	(
		const Matrix_& matrix_
	)
	{
		return MatrixNot<Matrix_::num_columns, Matrix_::num_rows, typename Matrix_::value_type, OutColumnMajor_, Matrix_>(matrix_);
	}


	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename out_contained_type, class Matrix_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, out_contained_type, Matrix_::is_column_major> MatrixNot(const Matrix_& matrix_)
	{
		return MatrixNot<OutNumColumns_, OutNumRows_, out_contained_type, Matrix_::is_column_major, Matrix_>(matrix_);
	}
	template<typename out_contained_type, class Matrix_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<Matrix_::num_columns, Matrix_::num_rows, out_contained_type, Matrix_::is_column_major> MatrixNot(const Matrix_& matrix_)
	{
		return MatrixNot<Matrix_::num_columns, Matrix_::num_rows, out_contained_type, Matrix_::is_column_major, Matrix_>(matrix_);
	}
	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, class Matrix_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, typename Matrix_::value_type, Matrix_::is_column_major> MatrixNot(const Matrix_& matrix_)
	{
		return MatrixNot<OutNumColumns_, OutNumRows_, typename Matrix_::value_type, Matrix_::is_column_major, Matrix_>(matrix_);
	}
	template<class Matrix_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<Matrix_::num_columns, Matrix_::num_rows, typename Matrix_::value_type, Matrix_::is_column_major> MatrixNot
	(
		const Matrix_& matrix_
	)
	{
		return MatrixNot<Matrix_::num_columns, Matrix_::num_rows, typename Matrix_::value_type, Matrix_::is_column_major, Matrix_>(matrix_);
	}

	/// <summary>
	/// <para> Shifts all elements of the passed matrix_ to the left the specified number of times within num_shifts_. </para>
	/// <para> If num_shifts_ is an EmuMath matrix: each element of the passed matrix_ will be shifted by the respective element in num_shifts_. </para>
	/// <para> If num_shifts_ is none of the above: every element of the passed matrix_ will be shifted by the value of num_shifts_. </para>
	/// </summary>
	/// <typeparam name="out_contained_type">Type to be contained in the output matrix.</typeparam>
	/// <typeparam name="Matrix_">Type of matrix to shift the elements of.</typeparam>
	/// <typeparam name="Shifts_">Type of argument indicating the number of shifts.</typeparam>
	/// <param name="matrix_">EmuMath matrix to shift the elements of.</param>
	/// <param name="num_shifts_">Number of shifts to perform on the passed matrix as defined above.</param>
	/// <returns>EmuMath matrix copy of the passed matrix with each element shifted to the left a number of times indicated by num_shifts_.</returns>
	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename out_contained_type, bool OutColumnMajor_, class Matrix_, class Shifts_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, out_contained_type, OutColumnMajor_> MatrixShiftLeft
	(
		const Matrix_& matrix_,
		const Shifts_& num_shifts_
	)
	{
		if constexpr (EmuMath::TMP::is_emu_matrix_v<Matrix_>)
		{
			return _underlying_matrix_funcs::_matrix_multi_arg_operation
			<
				EmuCore::do_left_shift,
				EmuMath::Matrix<OutNumColumns_, OutNumRows_, out_contained_type, OutColumnMajor_>,
				Matrix_,
				Shifts_
			>(matrix_, num_shifts_);
		}
		else
		{
			static_assert(false, "Attempted to shift a matrix left, but the provided matrix_ argument was not an EmuMath matrix.");
		}
	}
	template<typename out_contained_type, bool OutColumnMajor_, class Matrix_, class Shifts_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<Matrix_::num_columns, Matrix_::num_rows, out_contained_type, OutColumnMajor_> MatrixShiftLeft
	(
		const Matrix_& matrix_,
		const Shifts_& num_shifts_
	)
	{
		return MatrixShiftLeft<Matrix_::num_columns, Matrix_::num_rows, out_contained_type, OutColumnMajor_, Matrix_, Shifts_>(matrix_, num_shifts_);
	}
	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, bool OutColumnMajor_, class Matrix_, class Shifts_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, typename Matrix_::value_type, OutColumnMajor_> MatrixShiftLeft
	(
		const Matrix_& matrix_,
		const Shifts_& num_shifts_
	)
	{
		return MatrixShiftLeft<OutNumColumns_, OutNumRows_, typename Matrix_::value_type, OutColumnMajor_, Matrix_, Shifts_>(matrix_, num_shifts_);
	}
	template<bool OutColumnMajor_, class Matrix_, class Shifts_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<Matrix_::num_columns, Matrix_::num_rows, typename Matrix_::value_type, OutColumnMajor_> MatrixShiftLeft
	(
		const Matrix_& matrix_,
		const Shifts_& num_shifts_
	)
	{
		return MatrixShiftLeft<Matrix_::num_columns, Matrix_::num_rows, typename Matrix_::value_type, OutColumnMajor_, Matrix_, Shifts_>(matrix_, num_shifts_);
	}
	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename out_contained_type, class Matrix_, class Shifts_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, out_contained_type, Matrix_::is_column_major> MatrixShiftLeft
	(
		const Matrix_& matrix_,
		const Shifts_& num_shifts_
	)
	{
		return MatrixShiftLeft<OutNumColumns_, OutNumRows_, out_contained_type, Matrix_::is_column_major, Matrix_, Shifts_>(matrix_, num_shifts_);
	}
	template<typename out_contained_type, class Matrix_, class Shifts_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<Matrix_::num_columns, Matrix_::num_rows, out_contained_type, Matrix_::is_column_major> MatrixShiftLeft
	(
		const Matrix_& matrix_,
		const Shifts_& num_shifts_
	)
	{
		return MatrixShiftLeft<Matrix_::num_columns, Matrix_::num_rows, out_contained_type, Matrix_::is_column_major, Matrix_, Shifts_>(matrix_, num_shifts_);
	}
	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, class Matrix_, class Shifts_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, typename Matrix_::value_type, Matrix_::is_column_major> MatrixShiftLeft
	(
		const Matrix_& matrix_,
		const Shifts_& num_shifts_
	)
	{
		return MatrixShiftLeft<OutNumColumns_, OutNumRows_, typename Matrix_::value_type, Matrix_::is_column_major, Matrix_, Shifts_>(matrix_, num_shifts_);
	}
	template<class Matrix_, class Shifts_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<Matrix_::num_columns, Matrix_::num_rows, typename Matrix_::value_type, Matrix_::is_column_major> MatrixShiftLeft
	(
		const Matrix_& matrix_,
		const Shifts_& num_shifts_
	)
	{
		return MatrixShiftLeft<Matrix_::num_columns, Matrix_::num_rows, typename Matrix_::value_type, Matrix_::is_column_major, Matrix_, Shifts_>(matrix_, num_shifts_);
	}

	/// <summary>
	/// <para> Shifts all elements of the passed matrix_ to the right the specified number of times within num_shifts_. </para>
	/// <para> If num_shifts_ is an EmuMath matrix: each element of the passed matrix_ will be shifted by the respective element in num_shifts_. </para>
	/// <para> If num_shifts_ is none of the above: every element of the passed matrix_ will be shifted by the value of num_shifts_. </para>
	/// </summary>
	/// <typeparam name="out_contained_type">Type to be contained in the output matrix.</typeparam>
	/// <typeparam name="Matrix_">Type of matrix to shift the elements of.</typeparam>
	/// <typeparam name="Shifts_">Type of argument indicating the number of shifts.</typeparam>
	/// <param name="matrix_">EmuMath matrix to shift the elements of.</param>
	/// <param name="num_shifts_">Number of shifts to perform on the passed matrix as defined above.</param>
	/// <returns>EmuMath matrix copy of the passed matrix with each element shifted to the right a number of times indicated by num_shifts_.</returns>
	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename out_contained_type, bool OutColumnMajor_, class Matrix_, class Shifts_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, out_contained_type, OutColumnMajor_> MatrixShiftRight
	(
		const Matrix_& matrix_,
		const Shifts_& num_shifts_
	)
	{
		if constexpr (EmuMath::TMP::is_emu_matrix_v<Matrix_>)
		{
			return _underlying_matrix_funcs::_matrix_multi_arg_operation
			<
				EmuCore::do_right_shift,
				EmuMath::Matrix<OutNumColumns_, OutNumRows_, out_contained_type, OutColumnMajor_>,
				Matrix_,
				Shifts_
			>(matrix_, num_shifts_);
		}
		else
		{
			static_assert(false, "Attempted to shift a matrix right, but the provided matrix_ argument was not an EmuMath matrix.");
		}
	}
	template<typename out_contained_type, bool OutColumnMajor_, class Matrix_, class Shifts_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<Matrix_::num_columns, Matrix_::num_rows, out_contained_type, OutColumnMajor_> MatrixShiftRight
	(
		const Matrix_& matrix_,
		const Shifts_& num_shifts_
	)
	{
		return MatrixShiftRight<Matrix_::num_columns, Matrix_::num_rows, out_contained_type, OutColumnMajor_, Matrix_, Shifts_>(matrix_, num_shifts_);
	}
	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, bool OutColumnMajor_, class Matrix_, class Shifts_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, typename Matrix_::value_type, OutColumnMajor_> MatrixShiftRight
	(
		const Matrix_& matrix_,
		const Shifts_& num_shifts_
	)
	{
		return MatrixShiftRight<OutNumColumns_, OutNumRows_, typename Matrix_::value_type, OutColumnMajor_, Matrix_, Shifts_>(matrix_, num_shifts_);
	}
	template<bool OutColumnMajor_, class Matrix_, class Shifts_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<Matrix_::num_columns, Matrix_::num_rows, typename Matrix_::value_type, OutColumnMajor_> MatrixShiftRight
	(
		const Matrix_& matrix_,
		const Shifts_& num_shifts_
	)
	{
		return MatrixShiftRight<Matrix_::num_columns, Matrix_::num_rows, typename Matrix_::value_type, OutColumnMajor_, Matrix_, Shifts_>(matrix_, num_shifts_);
	}
	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename out_contained_type, class Matrix_, class Shifts_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, out_contained_type, Matrix_::is_column_major> MatrixShiftRight
	(
		const Matrix_& matrix_,
		const Shifts_& num_shifts_
	)
	{
		return MatrixShiftRight<OutNumColumns_, OutNumRows_, out_contained_type, Matrix_::is_column_major, Matrix_, Shifts_>(matrix_, num_shifts_);
	}
	template<typename out_contained_type, class Matrix_, class Shifts_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<Matrix_::num_columns, Matrix_::num_rows, out_contained_type, Matrix_::is_column_major> MatrixShiftRight
	(
		const Matrix_& matrix_,
		const Shifts_& num_shifts_
	)
	{
		return MatrixShiftRight<Matrix_::num_columns, Matrix_::num_rows, out_contained_type, Matrix_::is_column_major, Matrix_, Shifts_>(matrix_, num_shifts_);
	}
	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, class Matrix_, class Shifts_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, typename Matrix_::value_type, Matrix_::is_column_major> MatrixShiftRight
	(
		const Matrix_& matrix_,
		const Shifts_& num_shifts_
	)
	{
		return MatrixShiftRight<OutNumColumns_, OutNumRows_, typename Matrix_::value_type, Matrix_::is_column_major, Matrix_, Shifts_>(matrix_, num_shifts_);
	}
	template<class Matrix_, class Shifts_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<Matrix_::num_columns, Matrix_::num_rows, typename Matrix_::value_type, Matrix_::is_column_major> MatrixShiftRight
	(
		const Matrix_& matrix_,
		const Shifts_& num_shifts_
	)
	{
		return MatrixShiftRight<Matrix_::num_columns, Matrix_::num_rows, typename Matrix_::value_type, Matrix_::is_column_major, Matrix_, Shifts_>(matrix_, num_shifts_);
	}
}

#endif
