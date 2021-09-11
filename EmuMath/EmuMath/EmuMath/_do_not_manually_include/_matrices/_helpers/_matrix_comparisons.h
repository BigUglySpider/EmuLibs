#ifndef EMU_MATH_HELPERS_MATRIX_COMPARISONS_H_INC_
#define EMU_MATH_HELPERS_MATRIX_COMPARISONS_H_INC_ 1

#include "_common_matrix_helper_includes.h"

namespace EmuMath::Helpers
{
	/// <summary>
	/// <para>
	///		Compares the equality of each element in the passed lhs_matrix_ to rhs_ and returns the results of comparisons in respective indices of a matrix of booleans.
	/// </para>
	/// <para> If rhs_ is an EmuMath matrix: Comparisons for elements in lhs_matrix_ will be performed with respective elements in rhs_. </para>
	/// <para> If rhs_ is none of the above: Comparisons for elements in lhs_matrix_ will all be performed with the value of rhs_. </para>
	/// </summary>
	/// <typeparam name="LhsMatrix_">Type of matrix appearing on the left-hand side of comparisons.</typeparam>
	/// <typeparam name="Rhs_">Type of item appearing on the right-hand side of comparisons.</typeparam>
	/// <param name="lhs_matrix_">EmuMath matrix appearing on the left-hand side of comparisons.</param>
	/// <param name="rhs_">Item appearing on the right-hand side of comparisons.</param>
	/// <returns>Matrix of booleans containing the results of comparisons of each respective element in lhs_matrix_ with rhs_ as defined above.</returns>
	template<std::size_t NumColumnsToTest_, std::size_t NumRowsToTest_, bool OutColumnMajor_, class LhsMatrix_, class Rhs_>
	constexpr inline EmuMath::Matrix<NumColumnsToTest_, NumRowsToTest_, bool, OutColumnMajor_> MatrixCmpPerElementEqual
	(
		const LhsMatrix_& lhs_matrix_,
		const Rhs_& rhs_
	)
	{
		if constexpr (EmuMath::TMP::is_emu_matrix_v<LhsMatrix_>)
		{
			if constexpr (EmuMath::TMP::is_emu_matrix_v<Rhs_>)
			{
				using comparator = EmuCore::do_cmp_equal_to<typename LhsMatrix_::value_type, typename Rhs_::value_type>;
				return _underlying_matrix_funcs::_matrix_lhs_rhs_operation
				<
					EmuMath::Matrix<NumColumnsToTest_, NumRowsToTest_, bool, OutColumnMajor_>,
					LhsMatrix_,
					Rhs_,
					comparator
				>(lhs_matrix_, rhs_);
			}
			else
			{
				using comparator = EmuCore::do_cmp_equal_to<typename LhsMatrix_::value_type, Rhs_>;
				return _underlying_matrix_funcs::_matrix_lhs_rhs_operation
				<
					EmuMath::Matrix<NumColumnsToTest_, NumRowsToTest_, bool, OutColumnMajor_>,
					LhsMatrix_,
					Rhs_,
					comparator
				>(lhs_matrix_, rhs_);
			}
		}
		else
		{
			static_assert(false, "Attempted to compare equality of each element within a matrix, but the passed lhs_matrix_ was not an EmuMath matrix.");
		}
	}
	template<std::size_t NumColumnsToTest_, std::size_t NumRowsToTest_, class LhsMatrix_, class Rhs_>
	constexpr inline EmuMath::Matrix<NumColumnsToTest_, NumRowsToTest_, bool, LhsMatrix_::is_column_major> MatrixCmpPerElementEqual
	(
		const LhsMatrix_& lhs_matrix_,
		const Rhs_& rhs_
	)
	{
		return MatrixCmpPerElementEqual<NumColumnsToTest_, NumRowsToTest_, LhsMatrix_::is_column_major, LhsMatrix_, Rhs_>(lhs_matrix_, rhs_);
	}
	template<bool OutColumnMajor_, class LhsMatrix_, class Rhs_>
	constexpr inline EmuMath::Matrix<LhsMatrix_::num_columns, LhsMatrix_::num_rows, bool, OutColumnMajor_> MatrixCmpPerElementEqual
	(
		const LhsMatrix_& lhs_matrix_,
		const Rhs_& rhs_
	)
	{
		return MatrixCmpPerElementEqual<LhsMatrix_::num_columns, LhsMatrix_::num_rows, OutColumnMajor_, LhsMatrix_, Rhs_>(lhs_matrix_, rhs_);
	}
	template<class LhsMatrix_, class Rhs_>
	constexpr inline EmuMath::Matrix<LhsMatrix_::num_columns, LhsMatrix_::num_rows, bool, LhsMatrix_::is_column_major> MatrixCmpPerElementEqual
	(
		const LhsMatrix_& lhs_matrix_,
		const Rhs_& rhs_
	)
	{
		return MatrixCmpPerElementEqual<LhsMatrix_::num_columns, LhsMatrix_::num_rows, LhsMatrix_::is_column_major, LhsMatrix_, Rhs_>(lhs_matrix_, rhs_);
	}

	/// <summary>
	/// <para>
	///		Compares the inequality of each element in the passed lhs_matrix_ to rhs_ and returns the results of comparisons in respective indices of a matrix of booleans.
	/// </para>
	/// <para> If rhs_ is an EmuMath matrix: Comparisons for elements in lhs_matrix_ will be performed with respective elements in rhs_. </para>
	/// <para> If rhs_ is none of the above: Comparisons for elements in lhs_matrix_ will all be performed with the value of rhs_. </para>
	/// </summary>
	/// <typeparam name="LhsMatrix_">Type of matrix appearing on the left-hand side of comparisons.</typeparam>
	/// <typeparam name="Rhs_">Type of item appearing on the right-hand side of comparisons.</typeparam>
	/// <param name="lhs_matrix_">EmuMath matrix appearing on the left-hand side of comparisons.</param>
	/// <param name="rhs_">Item appearing on the right-hand side of comparisons.</param>
	/// <returns>Matrix of booleans containing the results of comparisons of each respective element in lhs_matrix_ with rhs_ as defined above.</returns>
	template<std::size_t NumColumnsToTest_, std::size_t NumRowsToTest_, bool OutColumnMajor_, class LhsMatrix_, class Rhs_>
	constexpr inline EmuMath::Matrix<NumColumnsToTest_, NumRowsToTest_, bool, OutColumnMajor_> MatrixCmpPerElementNotEqual
	(
		const LhsMatrix_& lhs_matrix_,
		const Rhs_& rhs_
	)
	{
		if constexpr (EmuMath::TMP::is_emu_matrix_v<LhsMatrix_>)
		{
			if constexpr (EmuMath::TMP::is_emu_matrix_v<Rhs_>)
			{
				using comparator = EmuCore::do_cmp_not_equal_to<typename LhsMatrix_::value_type, typename Rhs_::value_type>;
				return _underlying_matrix_funcs::_matrix_lhs_rhs_operation
				<
					EmuMath::Matrix<NumColumnsToTest_, NumRowsToTest_, bool, OutColumnMajor_>,
					LhsMatrix_,
					Rhs_,
					comparator
				>(lhs_matrix_, rhs_);
			}
			else
			{
				using comparator = EmuCore::do_cmp_not_equal_to<typename LhsMatrix_::value_type, Rhs_>;
				return _underlying_matrix_funcs::_matrix_lhs_rhs_operation
				<
					EmuMath::Matrix<NumColumnsToTest_, NumRowsToTest_, bool, OutColumnMajor_>,
					LhsMatrix_,
					Rhs_,
					comparator
				>(lhs_matrix_, rhs_);
			}
		}
		else
		{
			static_assert(false, "Attempted to compare inequality of each element within a matrix, but the passed lhs_matrix_ was not an EmuMath matrix.");
		}
	}
	template<std::size_t NumColumnsToTest_, std::size_t NumRowsToTest_, class LhsMatrix_, class Rhs_>
	constexpr inline EmuMath::Matrix<NumColumnsToTest_, NumRowsToTest_, bool, LhsMatrix_::is_column_major> MatrixCmpPerElementNotEqual
	(
		const LhsMatrix_& lhs_matrix_,
		const Rhs_& rhs_
	)
	{
		return MatrixCmpPerElementNotEqual<NumColumnsToTest_, NumRowsToTest_, LhsMatrix_::is_column_major, LhsMatrix_, Rhs_>(lhs_matrix_, rhs_);
	}
	template<bool OutColumnMajor_, class LhsMatrix_, class Rhs_>
	constexpr inline EmuMath::Matrix<LhsMatrix_::num_columns, LhsMatrix_::num_rows, bool, OutColumnMajor_> MatrixCmpPerElementNotEqual
	(
		const LhsMatrix_& lhs_matrix_,
		const Rhs_& rhs_
	)
	{
		return MatrixCmpPerElementNotEqual<LhsMatrix_::num_columns, LhsMatrix_::num_rows, OutColumnMajor_, LhsMatrix_, Rhs_>(lhs_matrix_, rhs_);
	}
	template<class LhsMatrix_, class Rhs_>
	constexpr inline EmuMath::Matrix<LhsMatrix_::num_columns, LhsMatrix_::num_rows, bool, LhsMatrix_::is_column_major> MatrixCmpPerElementNotEqual
	(
		const LhsMatrix_& lhs_matrix_,
		const Rhs_& rhs_
	)
	{
		return MatrixCmpPerElementNotEqual<LhsMatrix_::num_columns, LhsMatrix_::num_rows, LhsMatrix_::is_column_major, LhsMatrix_, Rhs_>(lhs_matrix_, rhs_);
	}

	/// <summary>
	/// <para>
	///		Compares the magnitude of each element in the passed lhs_matrix_ to rhs_ and returns the results of comparisons in respective indices of a matrix of booleans.
	/// </para>
	/// <para> If rhs_ is an EmuMath matrix: Comparisons for elements in lhs_matrix_ will be performed with respective elements in rhs_. </para>
	/// <para> If rhs_ is none of the above: Comparisons for elements in lhs_matrix_ will all be performed with the value of rhs_. </para>
	/// </summary>
	/// <typeparam name="LhsMatrix_">Type of matrix appearing on the left-hand side of comparisons.</typeparam>
	/// <typeparam name="Rhs_">Type of item appearing on the right-hand side of comparisons.</typeparam>
	/// <param name="lhs_matrix_">EmuMath matrix appearing on the left-hand side of comparisons.</param>
	/// <param name="rhs_">Item appearing on the right-hand side of comparisons.</param>
	/// <returns>Matrix of booleans containing the results of comparisons of each respective element in lhs_matrix_ with rhs_ as defined above.</returns>
	template<std::size_t NumColumnsToTest_, std::size_t NumRowsToTest_, bool OutColumnMajor_, class LhsMatrix_, class Rhs_>
	constexpr inline EmuMath::Matrix<NumColumnsToTest_, NumRowsToTest_, bool, OutColumnMajor_> MatrixCmpPerElementGreater
	(
		const LhsMatrix_& lhs_matrix_,
		const Rhs_& rhs_
	)
	{
		if constexpr (EmuMath::TMP::is_emu_matrix_v<LhsMatrix_>)
		{
			if constexpr (EmuMath::TMP::is_emu_matrix_v<Rhs_>)
			{
				using comparator = EmuCore::do_cmp_greater<typename LhsMatrix_::value_type, typename Rhs_::value_type>;
				return _underlying_matrix_funcs::_matrix_lhs_rhs_operation
				<
					EmuMath::Matrix<NumColumnsToTest_, NumRowsToTest_, bool, OutColumnMajor_>,
					LhsMatrix_,
					Rhs_,
					comparator
				>(lhs_matrix_, rhs_);
			}
			else
			{
				using comparator = EmuCore::do_cmp_greater<typename LhsMatrix_::value_type, Rhs_>;
				return _underlying_matrix_funcs::_matrix_lhs_rhs_operation
				<
					EmuMath::Matrix<NumColumnsToTest_, NumRowsToTest_, bool, OutColumnMajor_>,
					LhsMatrix_,
					Rhs_,
					comparator
				>(lhs_matrix_, rhs_);
			}
		}
		else
		{
			static_assert(false, "Attempted to compare magnitude of each element within a matrix, but the passed lhs_matrix_ was not an EmuMath matrix.");
		}
	}
	template<std::size_t NumColumnsToTest_, std::size_t NumRowsToTest_, class LhsMatrix_, class Rhs_>
	constexpr inline EmuMath::Matrix<NumColumnsToTest_, NumRowsToTest_, bool, LhsMatrix_::is_column_major> MatrixCmpPerElementGreater
	(
		const LhsMatrix_& lhs_matrix_,
		const Rhs_& rhs_
	)
	{
		return MatrixCmpPerElementGreater<NumColumnsToTest_, NumRowsToTest_, LhsMatrix_::is_column_major, LhsMatrix_, Rhs_>(lhs_matrix_, rhs_);
	}
	template<bool OutColumnMajor_, class LhsMatrix_, class Rhs_>
	constexpr inline EmuMath::Matrix<LhsMatrix_::num_columns, LhsMatrix_::num_rows, bool, OutColumnMajor_> MatrixCmpPerElementGreater
	(
		const LhsMatrix_& lhs_matrix_,
		const Rhs_& rhs_
	)
	{
		return MatrixCmpPerElementGreater<LhsMatrix_::num_columns, LhsMatrix_::num_rows, OutColumnMajor_, LhsMatrix_, Rhs_>(lhs_matrix_, rhs_);
	}
	template<class LhsMatrix_, class Rhs_>
	constexpr inline EmuMath::Matrix<LhsMatrix_::num_columns, LhsMatrix_::num_rows, bool, LhsMatrix_::is_column_major> MatrixCmpPerElementGreater
	(
		const LhsMatrix_& lhs_matrix_,
		const Rhs_& rhs_
	)
	{
		return MatrixCmpPerElementGreater<LhsMatrix_::num_columns, LhsMatrix_::num_rows, LhsMatrix_::is_column_major, LhsMatrix_, Rhs_>(lhs_matrix_, rhs_);
	}

	/// <summary>
	/// <para>
	///		Compares the magnitude of each element in the passed lhs_matrix_ to rhs_ and returns the results of comparisons in respective indices of a matrix of booleans.
	/// </para>
	/// <para> If rhs_ is an EmuMath matrix: Comparisons for elements in lhs_matrix_ will be performed with respective elements in rhs_. </para>
	/// <para> If rhs_ is none of the above: Comparisons for elements in lhs_matrix_ will all be performed with the value of rhs_. </para>
	/// </summary>
	/// <typeparam name="LhsMatrix_">Type of matrix appearing on the left-hand side of comparisons.</typeparam>
	/// <typeparam name="Rhs_">Type of item appearing on the right-hand side of comparisons.</typeparam>
	/// <param name="lhs_matrix_">EmuMath matrix appearing on the left-hand side of comparisons.</param>
	/// <param name="rhs_">Item appearing on the right-hand side of comparisons.</param>
	/// <returns>Matrix of booleans containing the results of comparisons of each respective element in lhs_matrix_ with rhs_ as defined above.</returns>
	template<std::size_t NumColumnsToTest_, std::size_t NumRowsToTest_, bool OutColumnMajor_, class LhsMatrix_, class Rhs_>
	constexpr inline EmuMath::Matrix<NumColumnsToTest_, NumRowsToTest_, bool, OutColumnMajor_> MatrixCmpPerElementLess
	(
		const LhsMatrix_& lhs_matrix_,
		const Rhs_& rhs_
	)
	{
		if constexpr (EmuMath::TMP::is_emu_matrix_v<LhsMatrix_>)
		{
			if constexpr (EmuMath::TMP::is_emu_matrix_v<Rhs_>)
			{
				using comparator = EmuCore::do_cmp_less<typename LhsMatrix_::value_type, typename Rhs_::value_type>;
				return _underlying_matrix_funcs::_matrix_lhs_rhs_operation
				<
					EmuMath::Matrix<NumColumnsToTest_, NumRowsToTest_, bool, OutColumnMajor_>,
					LhsMatrix_,
					Rhs_,
					comparator
				>(lhs_matrix_, rhs_);
			}
			else
			{
				using comparator = EmuCore::do_cmp_less<typename LhsMatrix_::value_type, Rhs_>;
				return _underlying_matrix_funcs::_matrix_lhs_rhs_operation
				<
					EmuMath::Matrix<NumColumnsToTest_, NumRowsToTest_, bool, OutColumnMajor_>,
					LhsMatrix_,
					Rhs_,
					comparator
				>(lhs_matrix_, rhs_);
			}
		}
		else
		{
			static_assert(false, "Attempted to compare magnitude of each element within a matrix, but the passed lhs_matrix_ was not an EmuMath matrix.");
		}
	}
	template<std::size_t NumColumnsToTest_, std::size_t NumRowsToTest_, class LhsMatrix_, class Rhs_>
	constexpr inline EmuMath::Matrix<NumColumnsToTest_, NumRowsToTest_, bool, LhsMatrix_::is_column_major> MatrixCmpPerElementLess
	(
		const LhsMatrix_& lhs_matrix_,
		const Rhs_& rhs_
	)
	{
		return MatrixCmpPerElementLess<NumColumnsToTest_, NumRowsToTest_, LhsMatrix_::is_column_major, LhsMatrix_, Rhs_>(lhs_matrix_, rhs_);
	}
	template<bool OutColumnMajor_, class LhsMatrix_, class Rhs_>
	constexpr inline EmuMath::Matrix<LhsMatrix_::num_columns, LhsMatrix_::num_rows, bool, OutColumnMajor_> MatrixCmpPerElementLess
	(
		const LhsMatrix_& lhs_matrix_,
		const Rhs_& rhs_
	)
	{
		return MatrixCmpPerElementLess<LhsMatrix_::num_columns, LhsMatrix_::num_rows, OutColumnMajor_, LhsMatrix_, Rhs_>(lhs_matrix_, rhs_);
	}
	template<class LhsMatrix_, class Rhs_>
	constexpr inline EmuMath::Matrix<LhsMatrix_::num_columns, LhsMatrix_::num_rows, bool, LhsMatrix_::is_column_major> MatrixCmpPerElementLess
	(
		const LhsMatrix_& lhs_matrix_,
		const Rhs_& rhs_
	)
	{
		return MatrixCmpPerElementLess<LhsMatrix_::num_columns, LhsMatrix_::num_rows, LhsMatrix_::is_column_major, LhsMatrix_, Rhs_>(lhs_matrix_, rhs_);
	}

	/// <summary>
	/// <para>
	///		Compares the magnitude of each element in the passed lhs_matrix_ to rhs_ and returns the results of comparisons in respective indices of a matrix of booleans.
	/// </para>
	/// <para> If rhs_ is an EmuMath matrix: Comparisons for elements in lhs_matrix_ will be performed with respective elements in rhs_. </para>
	/// <para> If rhs_ is none of the above: Comparisons for elements in lhs_matrix_ will all be performed with the value of rhs_. </para>
	/// </summary>
	/// <typeparam name="LhsMatrix_">Type of matrix appearing on the left-hand side of comparisons.</typeparam>
	/// <typeparam name="Rhs_">Type of item appearing on the right-hand side of comparisons.</typeparam>
	/// <param name="lhs_matrix_">EmuMath matrix appearing on the left-hand side of comparisons.</param>
	/// <param name="rhs_">Item appearing on the right-hand side of comparisons.</param>
	/// <returns>Matrix of booleans containing the results of comparisons of each respective element in lhs_matrix_ with rhs_ as defined above.</returns>
	template<std::size_t NumColumnsToTest_, std::size_t NumRowsToTest_, bool OutColumnMajor_, class LhsMatrix_, class Rhs_>
	constexpr inline EmuMath::Matrix<NumColumnsToTest_, NumRowsToTest_, bool, OutColumnMajor_> MatrixCmpPerElementGreaterEqual
	(
		const LhsMatrix_& lhs_matrix_,
		const Rhs_& rhs_
	)
	{
		if constexpr (EmuMath::TMP::is_emu_matrix_v<LhsMatrix_>)
		{
			if constexpr (EmuMath::TMP::is_emu_matrix_v<Rhs_>)
			{
				using comparator = EmuCore::do_cmp_greater_equal<typename LhsMatrix_::value_type, typename Rhs_::value_type>;
				return _underlying_matrix_funcs::_matrix_lhs_rhs_operation
				<
					EmuMath::Matrix<NumColumnsToTest_, NumRowsToTest_, bool, OutColumnMajor_>,
					LhsMatrix_,
					Rhs_,
					comparator
				>(lhs_matrix_, rhs_);
			}
			else
			{
				using comparator = EmuCore::do_cmp_greater_equal<typename LhsMatrix_::value_type, Rhs_>;
				return _underlying_matrix_funcs::_matrix_lhs_rhs_operation
				<
					EmuMath::Matrix<NumColumnsToTest_, NumRowsToTest_, bool, OutColumnMajor_>,
					LhsMatrix_,
					Rhs_,
					comparator
				>(lhs_matrix_, rhs_);
			}
		}
		else
		{
			static_assert(false, "Attempted to compare magnitude of each element within a matrix, but the passed lhs_matrix_ was not an EmuMath matrix.");
		}
	}
	template<std::size_t NumColumnsToTest_, std::size_t NumRowsToTest_, class LhsMatrix_, class Rhs_>
	constexpr inline EmuMath::Matrix<NumColumnsToTest_, NumRowsToTest_, bool, LhsMatrix_::is_column_major> MatrixCmpPerElementGreaterEqual
	(
		const LhsMatrix_& lhs_matrix_,
		const Rhs_& rhs_
	)
	{
		return MatrixCmpPerElementGreaterEqual<NumColumnsToTest_, NumRowsToTest_, LhsMatrix_::is_column_major, LhsMatrix_, Rhs_>(lhs_matrix_, rhs_);
	}
	template<bool OutColumnMajor_, class LhsMatrix_, class Rhs_>
	constexpr inline EmuMath::Matrix<LhsMatrix_::num_columns, LhsMatrix_::num_rows, bool, OutColumnMajor_> MatrixCmpPerElementGreaterEqual
	(
		const LhsMatrix_& lhs_matrix_,
		const Rhs_& rhs_
	)
	{
		return MatrixCmpPerElementGreaterEqual<LhsMatrix_::num_columns, LhsMatrix_::num_rows, OutColumnMajor_, LhsMatrix_, Rhs_>(lhs_matrix_, rhs_);
	}
	template<class LhsMatrix_, class Rhs_>
	constexpr inline EmuMath::Matrix<LhsMatrix_::num_columns, LhsMatrix_::num_rows, bool, LhsMatrix_::is_column_major> MatrixCmpPerElementGreaterEqual
	(
		const LhsMatrix_& lhs_matrix_,
		const Rhs_& rhs_
	)
	{
		return MatrixCmpPerElementGreaterEqual<LhsMatrix_::num_columns, LhsMatrix_::num_rows, LhsMatrix_::is_column_major, LhsMatrix_, Rhs_>(lhs_matrix_, rhs_);
	}

	/// <summary>
	/// <para>
	///		Compares the magnitude of each element in the passed lhs_matrix_ to rhs_ and returns the results of comparisons in respective indices of a matrix of booleans.
	/// </para>
	/// <para> If rhs_ is an EmuMath matrix: Comparisons for elements in lhs_matrix_ will be performed with respective elements in rhs_. </para>
	/// <para> If rhs_ is none of the above: Comparisons for elements in lhs_matrix_ will all be performed with the value of rhs_. </para>
	/// </summary>
	/// <typeparam name="LhsMatrix_">Type of matrix appearing on the left-hand side of comparisons.</typeparam>
	/// <typeparam name="Rhs_">Type of item appearing on the right-hand side of comparisons.</typeparam>
	/// <param name="lhs_matrix_">EmuMath matrix appearing on the left-hand side of comparisons.</param>
	/// <param name="rhs_">Item appearing on the right-hand side of comparisons.</param>
	/// <returns>Matrix of booleans containing the results of comparisons of each respective element in lhs_matrix_ with rhs_ as defined above.</returns>
	template<std::size_t NumColumnsToTest_, std::size_t NumRowsToTest_, bool OutColumnMajor_, class LhsMatrix_, class Rhs_>
	constexpr inline EmuMath::Matrix<NumColumnsToTest_, NumRowsToTest_, bool, OutColumnMajor_> MatrixCmpPerElementLessEqual
	(
		const LhsMatrix_& lhs_matrix_,
		const Rhs_& rhs_
	)
	{
		if constexpr (EmuMath::TMP::is_emu_matrix_v<LhsMatrix_>)
		{
			if constexpr (EmuMath::TMP::is_emu_matrix_v<Rhs_>)
			{
				using comparator = EmuCore::do_cmp_less_equal<typename LhsMatrix_::value_type, typename Rhs_::value_type>;
				return _underlying_matrix_funcs::_matrix_lhs_rhs_operation
				<
					EmuMath::Matrix<NumColumnsToTest_, NumRowsToTest_, bool, OutColumnMajor_>,
					LhsMatrix_,
					Rhs_,
					comparator
				>(lhs_matrix_, rhs_);
			}
			else
			{
				using comparator = EmuCore::do_cmp_less_equal<typename LhsMatrix_::value_type, Rhs_>;
				return _underlying_matrix_funcs::_matrix_lhs_rhs_operation
				<
					EmuMath::Matrix<NumColumnsToTest_, NumRowsToTest_, bool, OutColumnMajor_>,
					LhsMatrix_,
					Rhs_,
					comparator
				>(lhs_matrix_, rhs_);
			}
		}
		else
		{
			static_assert(false, "Attempted to compare magnitude of each element within a matrix, but the passed lhs_matrix_ was not an EmuMath matrix.");
		}
	}
	template<std::size_t NumColumnsToTest_, std::size_t NumRowsToTest_, class LhsMatrix_, class Rhs_>
	constexpr inline EmuMath::Matrix<NumColumnsToTest_, NumRowsToTest_, bool, LhsMatrix_::is_column_major> MatrixCmpPerElementLessEqual
	(
		const LhsMatrix_& lhs_matrix_,
		const Rhs_& rhs_
	)
	{
		return MatrixCmpPerElementLessEqual<NumColumnsToTest_, NumRowsToTest_, LhsMatrix_::is_column_major, LhsMatrix_, Rhs_>(lhs_matrix_, rhs_);
	}
	template<bool OutColumnMajor_, class LhsMatrix_, class Rhs_>
	constexpr inline EmuMath::Matrix<LhsMatrix_::num_columns, LhsMatrix_::num_rows, bool, OutColumnMajor_> MatrixCmpPerElementLessEqual
	(
		const LhsMatrix_& lhs_matrix_,
		const Rhs_& rhs_
	)
	{
		return MatrixCmpPerElementLessEqual<LhsMatrix_::num_columns, LhsMatrix_::num_rows, OutColumnMajor_, LhsMatrix_, Rhs_>(lhs_matrix_, rhs_);
	}
	template<class LhsMatrix_, class Rhs_>
	constexpr inline EmuMath::Matrix<LhsMatrix_::num_columns, LhsMatrix_::num_rows, bool, LhsMatrix_::is_column_major> MatrixCmpPerElementLessEqual
	(
		const LhsMatrix_& lhs_matrix_,
		const Rhs_& rhs_
	)
	{
		return MatrixCmpPerElementLessEqual<LhsMatrix_::num_columns, LhsMatrix_::num_rows, LhsMatrix_::is_column_major, LhsMatrix_, Rhs_>(lhs_matrix_, rhs_);
	}

	/// <summary>
	/// <para> Returns true if all comparisons performed with the provided callable return true. </para>
	/// <para>
	///		The callable type will be discerned from a provided template type. 
	///		The final callable type will amount to one of the following:
	/// </para>
	/// <para> 1: FuncTemplate_&lt;LhsMatrix_::raw_value_type, Rhs_::raw_value_type&gt; in the scenario that Rhs_ is an EmuMath Matrix. </para>
	/// <para> 2: FuncTemplate_&lt;LhsMatrix_::raw_value_type, Rhs_&gt; in the scenario that none of the above scenarios are met. </para>
	/// <para>
	///		If a state is required for the callable, use the overload of this function which takes a finished Func_ instead. 
	///		Note that use of said function will require you to find the template arguments yourself.
	/// </para>
	/// <para> 
	///		If rhs_ is an EmuMath matrix: respective elements within the two matrices will be compared. 
	///		If this is the case, comparisons will only be performed on shared elements by default. To test all elements regardless of size, set TestAllIndices_ to true.
	/// </para>
	/// </summary>
	/// <typeparam name="LhsMatrix_">Type of matrix to appear on the left-hand side of the comparison.</typeparam>
	/// <typeparam name="Rhs_">Type appearing on the right-hand side of the comparison.</typeparam>
	/// <param name="lhs_matrix_">EmuMath matrix appearing on the left-hand side of the comparison.</param>
	/// <param name="rhs_">Item appearing on the right-hand side of the comparison.</param>
	/// <returns>Boolean indcating if comparisons on all elements within lhs_matrix_ with rhs_ as defined above returned true.</returns>
	template<template<class Lhs__, class Rhs__> class FuncTemplate_, bool TestAllIndices_ = false, class LhsMatrix_, class Rhs_>
	constexpr inline bool MatrixCmpAllTrue(const LhsMatrix_& lhs_matrix_, const Rhs_& rhs_)
	{
		if constexpr (EmuMath::TMP::is_emu_matrix_v<LhsMatrix_>)
		{
			return _underlying_matrix_funcs::_matrix_cmp_all<TestAllIndices_, FuncTemplate_, LhsMatrix_, Rhs_>(lhs_matrix_, rhs_);
		}
		else
		{
			static_assert(false, "Attempted to perform a CmpAll operation on a matrix, but the passed lhs_matrix_ was not an EmuMath matrix.");
		}
	}
	/// <summary>
	/// <para> Returns true if all comparisons performed with the provided callable return true. </para>
	/// <para> 
	///		If rhs_ is an EmuMath matrix: respective elements within the two matrices will be compared. 
	///		If this is the case, comparisons will only be performed on shared elements by default. To test all elements regardless of size, set TestAllIndices_ to true.
	/// </para>
	/// <para> The provided callable will be provided arguments depending on the provided arguments: </para>
	/// <para> 1: If rhs_ is an EmuMath matrix: The callable will be invoked with (const LhsMatrix_::raw_value_type&amp;, const Rhs_::raw_value_type&amp;) arguments. </para>
	/// <para> 2: If rhs_ is none of the above: The callable will be invoked with (const LhsMatrix_::raw_value_type&amp;, const Rhs_&amp;) arguments. </para>
	/// <para> In both above scenarios, invocation will be required to return a type that may be interpreted as a bool. </para>
	/// </summary>
	/// <typeparam name="LhsMatrix_">Type of matrix to appear on the left-hand side of the comparison.</typeparam>
	/// <typeparam name="Rhs_">Type appearing on the right-hand side of the comparison.</typeparam>
	/// <typeparam name="Func_">Type of callable to perform comparisons.</typeparam>
	/// <param name="lhs_matrix_">EmuMath matrix appearing on the left-hand side of the comparison.</param>
	/// <param name="rhs_">Item appearing on the right-hand side of the comparison.</param>
	/// <param name="func_">Callable to perform comparisons, meeting the constraints defined above.</param>
	/// <returns>Boolean indcating if comparisons on all elements within lhs_matrix_ with rhs_ as defined above returned true.</returns>
	template<class Func_, bool TestAllIndices_ = false, class LhsMatrix_, class Rhs_>
	constexpr inline bool MatrixCmpAllTrue(const LhsMatrix_& lhs_matrix_, const Rhs_& rhs_, Func_ func_)
	{
		if constexpr (EmuMath::TMP::is_emu_matrix_v<LhsMatrix_>)
		{
			return _underlying_matrix_funcs::_matrix_cmp_all<Func_&, TestAllIndices_, LhsMatrix_, Rhs_>(lhs_matrix_, rhs_, func_);
		}
		else
		{
			static_assert(false, "Attempted to perform a CmpAll operation on a matrix, but the passed lhs_matrix_ was not an EmuMath matrix.");
		}
	}

	/// <summary>
	/// <para> Returns true if all equal_to comparisons between lhs_matrix_ and rhs_ return true. </para>
	/// <para> 
	///		If rhs_ is an EmuMath matrix: respective elements within the two matrices will be compared. 
	///		If this is the case, comparisons will only be performed on shared elements by default. To test all elements regardless of size, set TestAllIndices_ to true.
	/// </para>
	/// </summary>
	/// <typeparam name="LhsMatrix_">Matrix appearing on the left-hand side of equal_to comparisons.</typeparam>
	/// <typeparam name="Rhs_">Item appearing on the right-hand side of equal_to comparisons.</typeparam>
	/// <param name="lhs_matrix_">EmuMath matrix appearing on the left-hand side of equal_to comparisons.</param>
	/// <param name="rhs_">Item appearing on the right-hand side of equal_to comparisons.</param>
	/// <returns>Boolean indcating if comparisons on all elements within lhs_matrix_ with rhs_ as defined above returned true.</returns>
	template<bool TestAllIndices_ = false, class LhsMatrix_, class Rhs_>
	constexpr inline bool MatrixCmpAllEqual(const LhsMatrix_& lhs_matrix_, const Rhs_& rhs_)
	{
		if constexpr (EmuMath::TMP::is_emu_matrix_v<LhsMatrix_>)
		{
			return _underlying_matrix_funcs::_matrix_cmp_all<TestAllIndices_, EmuCore::do_cmp_equal_to, LhsMatrix_, Rhs_>(lhs_matrix_, rhs_);
		}
		else
		{
			static_assert(false, "Attempted to perform a CmpAllEqual operation on a matrix, but the passed lhs_matrix_ was not an EmuMath matrix.");
		}
	}

	/// <summary>
	/// <para> Returns true if all not_equal_to comparisons between lhs_matrix_ and rhs_ return true. </para>
	/// <para> 
	///		If rhs_ is an EmuMath matrix: respective elements within the two matrices will be compared. 
	///		If this is the case, comparisons will only be performed on shared elements by default. To test all elements regardless of size, set TestAllIndices_ to true.
	/// </para>
	/// </summary>
	/// <typeparam name="LhsMatrix_">Matrix appearing on the left-hand side of equal_to comparisons.</typeparam>
	/// <typeparam name="Rhs_">Item appearing on the right-hand side of equal_to comparisons.</typeparam>
	/// <param name="lhs_matrix_">EmuMath matrix appearing on the left-hand side of equal_to comparisons.</param>
	/// <param name="rhs_">Item appearing on the right-hand side of equal_to comparisons.</param>
	/// <returns>Boolean indcating if comparisons on all elements within lhs_matrix_ with rhs_ as defined above returned true.</returns>
	template<bool TestAllIndices_ = false, class LhsMatrix_, class Rhs_>
	constexpr inline bool MatrixCmpAllNotEqual(const LhsMatrix_& lhs_matrix_, const Rhs_& rhs_)
	{
		if constexpr (EmuMath::TMP::is_emu_matrix_v<LhsMatrix_>)
		{
			return _underlying_matrix_funcs::_matrix_cmp_all<TestAllIndices_, EmuCore::do_cmp_not_equal_to, LhsMatrix_, Rhs_>(lhs_matrix_, rhs_);
		}
		else
		{
			static_assert(false, "Attempted to perform a CmpAllNotEqual operation on a matrix, but the passed lhs_matrix_ was not an EmuMath matrix.");
		}
	}

	/// <summary>
	/// <para> Returns true if all greater_than comparisons between lhs_matrix_ and rhs_ return true. </para>
	/// <para> 
	///		If rhs_ is an EmuMath matrix: respective elements within the two matrices will be compared. 
	///		If this is the case, comparisons will only be performed on shared elements by default. To test all elements regardless of size, set TestAllIndices_ to true.
	/// </para>
	/// </summary>
	/// <typeparam name="LhsMatrix_">Matrix appearing on the left-hand side of equal_to comparisons.</typeparam>
	/// <typeparam name="Rhs_">Item appearing on the right-hand side of equal_to comparisons.</typeparam>
	/// <param name="lhs_matrix_">EmuMath matrix appearing on the left-hand side of equal_to comparisons.</param>
	/// <param name="rhs_">Item appearing on the right-hand side of equal_to comparisons.</param>
	/// <returns>Boolean indcating if comparisons on all elements within lhs_matrix_ with rhs_ as defined above returned true.</returns>
	template<bool TestAllIndices_ = false, class LhsMatrix_, class Rhs_>
	constexpr inline bool MatrixCmpAllGreater(const LhsMatrix_& lhs_matrix_, const Rhs_& rhs_)
	{
		if constexpr (EmuMath::TMP::is_emu_matrix_v<LhsMatrix_>)
		{
			return _underlying_matrix_funcs::_matrix_cmp_all<TestAllIndices_, EmuCore::do_cmp_greater, LhsMatrix_, Rhs_>(lhs_matrix_, rhs_);
		}
		else
		{
			static_assert(false, "Attempted to perform a CmpAllGreater operation on a matrix, but the passed lhs_matrix_ was not an EmuMath matrix.");
		}
	}

	/// <summary>
	/// <para> Returns true if all less_than comparisons between lhs_matrix_ and rhs_ return true. </para>
	/// <para> 
	///		If rhs_ is an EmuMath matrix: respective elements within the two matrices will be compared. 
	///		If this is the case, comparisons will only be performed on shared elements by default. To test all elements regardless of size, set TestAllIndices_ to true.
	/// </para>
	/// </summary>
	/// <typeparam name="LhsMatrix_">Matrix appearing on the left-hand side of equal_to comparisons.</typeparam>
	/// <typeparam name="Rhs_">Item appearing on the right-hand side of equal_to comparisons.</typeparam>
	/// <param name="lhs_matrix_">EmuMath matrix appearing on the left-hand side of equal_to comparisons.</param>
	/// <param name="rhs_">Item appearing on the right-hand side of equal_to comparisons.</param>
	/// <returns>Boolean indcating if comparisons on all elements within lhs_matrix_ with rhs_ as defined above returned true.</returns>
	template<bool TestAllIndices_ = false, class LhsMatrix_, class Rhs_>
	constexpr inline bool MatrixCmpAllLess(const LhsMatrix_& lhs_matrix_, const Rhs_& rhs_)
	{
		if constexpr (EmuMath::TMP::is_emu_matrix_v<LhsMatrix_>)
		{
			return _underlying_matrix_funcs::_matrix_cmp_all<TestAllIndices_, EmuCore::do_cmp_less, LhsMatrix_, Rhs_>(lhs_matrix_, rhs_);
		}
		else
		{
			static_assert(false, "Attempted to perform a CmpAllLess operation on a matrix, but the passed lhs_matrix_ was not an EmuMath matrix.");
		}
	}

	/// <summary>
	/// <para> Returns true if all greater_equal comparisons between lhs_matrix_ and rhs_ return true. </para>
	/// <para> 
	///		If rhs_ is an EmuMath matrix: respective elements within the two matrices will be compared. 
	///		If this is the case, comparisons will only be performed on shared elements by default. To test all elements regardless of size, set TestAllIndices_ to true.
	/// </para>
	/// </summary>
	/// <typeparam name="LhsMatrix_">Matrix appearing on the left-hand side of equal_to comparisons.</typeparam>
	/// <typeparam name="Rhs_">Item appearing on the right-hand side of equal_to comparisons.</typeparam>
	/// <param name="lhs_matrix_">EmuMath matrix appearing on the left-hand side of equal_to comparisons.</param>
	/// <param name="rhs_">Item appearing on the right-hand side of equal_to comparisons.</param>
	/// <returns>Boolean indcating if comparisons on all elements within lhs_matrix_ with rhs_ as defined above returned true.</returns>
	template<bool TestAllIndices_ = false, class LhsMatrix_, class Rhs_>
	constexpr inline bool MatrixCmpAllGreaterEqual(const LhsMatrix_& lhs_matrix_, const Rhs_& rhs_)
	{
		if constexpr (EmuMath::TMP::is_emu_matrix_v<LhsMatrix_>)
		{
			return _underlying_matrix_funcs::_matrix_cmp_all<TestAllIndices_, EmuCore::do_cmp_greater_equal, LhsMatrix_, Rhs_>(lhs_matrix_, rhs_);
		}
		else
		{
			static_assert(false, "Attempted to perform a CmpAllGreaterEqual operation on a matrix, but the passed lhs_matrix_ was not an EmuMath matrix.");
		}
	}

	/// <summary>
	/// <para> Returns true if all less_equal comparisons between lhs_matrix_ and rhs_ return true. </para>
	/// <para> 
	///		If rhs_ is an EmuMath matrix: respective elements within the two matrices will be compared. 
	///		If this is the case, comparisons will only be performed on shared elements by default. To test all elements regardless of size, set TestAllIndices_ to true.
	/// </para>
	/// </summary>
	/// <typeparam name="LhsMatrix_">Matrix appearing on the left-hand side of equal_to comparisons.</typeparam>
	/// <typeparam name="Rhs_">Item appearing on the right-hand side of equal_to comparisons.</typeparam>
	/// <param name="lhs_matrix_">EmuMath matrix appearing on the left-hand side of equal_to comparisons.</param>
	/// <param name="rhs_">Item appearing on the right-hand side of equal_to comparisons.</param>
	/// <returns>Boolean indcating if comparisons all elements within lhs_matrix_ with rhs_ as defined above returned true.</returns>
	template<bool TestAllIndices_ = false, class LhsMatrix_, class Rhs_>
	constexpr inline bool MatrixCmpAllLessEqual(const LhsMatrix_& lhs_matrix_, const Rhs_& rhs_)
	{
		if constexpr (EmuMath::TMP::is_emu_matrix_v<LhsMatrix_>)
		{
			return _underlying_matrix_funcs::_matrix_cmp_all<TestAllIndices_, EmuCore::do_cmp_less_equal, LhsMatrix_, Rhs_>(lhs_matrix_, rhs_);
		}
		else
		{
			static_assert(false, "Attempted to perform a CmpAllLessEqual operation on a matrix, but the passed lhs_matrix_ was not an EmuMath matrix.");
		}
	}

	/// <summary>
	/// <para> Returns true if any comparisons performed with the provided callable return true. </para>
	/// <para>
	///		The callable type will be discerned from a provided template type. 
	///		The final callable type will amount to one of the following:
	/// </para>
	/// <para> 1: FuncTemplate_&lt;LhsMatrix_::raw_value_type, Rhs_::raw_value_type&gt; in the scenario that Rhs_ is an EmuMath Matrix. </para>
	/// <para> 2: FuncTemplate_&lt;LhsMatrix_::raw_value_type, Rhs_&gt; in the scenario that none of the above scenarios are met. </para>
	/// <para>
	///		If a state is required for the callable, use the overload of this function which takes a finished Func_ instead. 
	///		Note that use of said function will require you to find the template arguments yourself.
	/// </para>
	/// <para> 
	///		If rhs_ is an EmuMath matrix: respective elements within the two matrices will be compared. 
	///		If this is the case, comparisons will only be performed on shared elements by default. To test all elements regardless of size, set TestAllIndices_ to true.
	/// </para>
	/// </summary>
	/// <typeparam name="LhsMatrix_">Type of matrix to appear on the left-hand side of the comparison.</typeparam>
	/// <typeparam name="Rhs_">Type appearing on the right-hand side of the comparison.</typeparam>
	/// <param name="lhs_matrix_">EmuMath matrix appearing on the left-hand side of the comparison.</param>
	/// <param name="rhs_">Item appearing on the right-hand side of the comparison.</param>
	/// <returns>Boolean indcating if comparisons on at least one element within lhs_matrix_ with rhs_ as defined above returned true.</returns>
	template<template<class Lhs__, class Rhs__> class FuncTemplate_, bool TestAllIndices_ = false, class LhsMatrix_, class Rhs_>
	constexpr inline bool MatrixCmpAnyTrue(const LhsMatrix_& lhs_matrix_, const Rhs_& rhs_)
	{
		if constexpr (EmuMath::TMP::is_emu_matrix_v<LhsMatrix_>)
		{
			return _underlying_matrix_funcs::_matrix_cmp_any<TestAllIndices_, FuncTemplate_, LhsMatrix_, Rhs_>(lhs_matrix_, rhs_);
		}
		else
		{
			static_assert(false, "Attempted to perform a CmpAny operation on a matrix, but the passed lhs_matrix_ was not an EmuMath matrix.");
		}
	}
	/// <summary>
	/// <para> Returns true if any comparisons performed with the provided callable return true. </para>
	/// <para> 
	///		If rhs_ is an EmuMath matrix: respective elements within the two matrices will be compared. 
	///		If this is the case, comparisons will only be performed on shared elements by default. To test all elements regardless of size, set TestAllIndices_ to true.
	/// </para>
	/// <para> The provided callable will be provided arguments depending on the provided arguments: </para>
	/// <para> 1: If rhs_ is an EmuMath matrix: The callable will be invoked with (const LhsMatrix_::raw_value_type&amp;, const Rhs_::raw_value_type&amp;) arguments. </para>
	/// <para> 2: If rhs_ is none of the above: The callable will be invoked with (const LhsMatrix_::raw_value_type&amp;, const Rhs_&amp;) arguments. </para>
	/// <para> In both above scenarios, invocation will be required to return a type that may be interpreted as a bool. </para>
	/// </summary>
	/// <typeparam name="LhsMatrix_">Type of matrix to appear on the left-hand side of the comparison.</typeparam>
	/// <typeparam name="Rhs_">Type appearing on the right-hand side of the comparison.</typeparam>
	/// <typeparam name="Func_">Type of callable to perform comparisons.</typeparam>
	/// <param name="lhs_matrix_">EmuMath matrix appearing on the left-hand side of the comparison.</param>
	/// <param name="rhs_">Item appearing on the right-hand side of the comparison.</param>
	/// <param name="func_">Callable to perform comparisons, meeting the constraints defined above.</param>
	/// <returns>Boolean indcating if comparisons on at least one element within lhs_matrix_ with rhs_ as defined above returned true.</returns>
	template<class Func_, bool TestAllIndices_ = false, class LhsMatrix_, class Rhs_>
	constexpr inline bool MatrixCmpAnyTrue(const LhsMatrix_& lhs_matrix_, const Rhs_& rhs_, Func_ func_)
	{
		if constexpr (EmuMath::TMP::is_emu_matrix_v<LhsMatrix_>)
		{
			return _underlying_matrix_funcs::_matrix_cmp_any<Func_&, TestAllIndices_, LhsMatrix_, Rhs_>(lhs_matrix_, rhs_, func_);
		}
		else
		{
			static_assert(false, "Attempted to perform a CmpAny operation on a matrix, but the passed lhs_matrix_ was not an EmuMath matrix.");
		}
	}

	/// <summary>
	/// <para> Returns true if any equal_to comparisons between lhs_matrix_ and rhs_ return true. </para>
	/// <para> 
	///		If rhs_ is an EmuMath matrix: respective elements within the two matrices will be compared. 
	///		If this is the case, comparisons will only be performed on shared elements by default. To test all elements regardless of size, set TestAllIndices_ to true.
	/// </para>
	/// </summary>
	/// <typeparam name="LhsMatrix_">Matrix appearing on the left-hand side of equal_to comparisons.</typeparam>
	/// <typeparam name="Rhs_">Item appearing on the right-hand side of equal_to comparisons.</typeparam>
	/// <param name="lhs_matrix_">EmuMath matrix appearing on the left-hand side of equal_to comparisons.</param>
	/// <param name="rhs_">Item appearing on the right-hand side of equal_to comparisons.</param>
	/// <returns>Boolean indcating if comparisons on at least one element within lhs_matrix_ with rhs_ as defined above returned true.</returns>
	template<bool TestAllIndices_ = false, class LhsMatrix_, class Rhs_>
	constexpr inline bool MatrixCmpAnyEqual(const LhsMatrix_& lhs_matrix_, const Rhs_& rhs_)
	{
		if constexpr (EmuMath::TMP::is_emu_matrix_v<LhsMatrix_>)
		{
			return _underlying_matrix_funcs::_matrix_cmp_any<TestAllIndices_, EmuCore::do_cmp_equal_to, LhsMatrix_, Rhs_>(lhs_matrix_, rhs_);
		}
		else
		{
			static_assert(false, "Attempted to perform a CmpAnyEqual operation on a matrix, but the passed lhs_matrix_ was not an EmuMath matrix.");
		}
	}

	/// <summary>
	/// <para> Returns true if any not_equal_to comparisons between lhs_matrix_ and rhs_ return true. </para>
	/// <para> 
	///		If rhs_ is an EmuMath matrix: respective elements within the two matrices will be compared. 
	///		If this is the case, comparisons will only be performed on shared elements by default. To test all elements regardless of size, set TestAllIndices_ to true.
	/// </para>
	/// </summary>
	/// <typeparam name="LhsMatrix_">Matrix appearing on the left-hand side of equal_to comparisons.</typeparam>
	/// <typeparam name="Rhs_">Item appearing on the right-hand side of equal_to comparisons.</typeparam>
	/// <param name="lhs_matrix_">EmuMath matrix appearing on the left-hand side of equal_to comparisons.</param>
	/// <param name="rhs_">Item appearing on the right-hand side of equal_to comparisons.</param>
	/// <returns>Boolean indcating if comparisons on at least one element within lhs_matrix_ with rhs_ as defined above returned true.</returns>
	template<bool TestAllIndices_ = false, class LhsMatrix_, class Rhs_>
	constexpr inline bool MatrixCmpAnyNotEqual(const LhsMatrix_& lhs_matrix_, const Rhs_& rhs_)
	{
		if constexpr (EmuMath::TMP::is_emu_matrix_v<LhsMatrix_>)
		{
			return _underlying_matrix_funcs::_matrix_cmp_any<TestAllIndices_, EmuCore::do_cmp_not_equal_to, LhsMatrix_, Rhs_>(lhs_matrix_, rhs_);
		}
		else
		{
			static_assert(false, "Attempted to perform a CmpAnyNotEqual operation on a matrix, but the passed lhs_matrix_ was not an EmuMath matrix.");
		}
	}

	/// <summary>
	/// <para> Returns true if any greater_than comparisons between lhs_matrix_ and rhs_ return true. </para>
	/// <para> 
	///		If rhs_ is an EmuMath matrix: respective elements within the two matrices will be compared. 
	///		If this is the case, comparisons will only be performed on shared elements by default. To test all elements regardless of size, set TestAllIndices_ to true.
	/// </para>
	/// </summary>
	/// <typeparam name="LhsMatrix_">Matrix appearing on the left-hand side of equal_to comparisons.</typeparam>
	/// <typeparam name="Rhs_">Item appearing on the right-hand side of equal_to comparisons.</typeparam>
	/// <param name="lhs_matrix_">EmuMath matrix appearing on the left-hand side of equal_to comparisons.</param>
	/// <param name="rhs_">Item appearing on the right-hand side of equal_to comparisons.</param>
	/// <returns>Boolean indcating if comparisons on at least one element within lhs_matrix_ with rhs_ as defined above returned true.</returns>
	template<bool TestAllIndices_ = false, class LhsMatrix_, class Rhs_>
	constexpr inline bool MatrixCmpAnyGreater(const LhsMatrix_& lhs_matrix_, const Rhs_& rhs_)
	{
		if constexpr (EmuMath::TMP::is_emu_matrix_v<LhsMatrix_>)
		{
			return _underlying_matrix_funcs::_matrix_cmp_any<TestAllIndices_, EmuCore::do_cmp_greater, LhsMatrix_, Rhs_>(lhs_matrix_, rhs_);
		}
		else
		{
			static_assert(false, "Attempted to perform a CmpAnyGreater operation on a matrix, but the passed lhs_matrix_ was not an EmuMath matrix.");
		}
	}

	/// <summary>
	/// <para> Returns true if any less_than comparisons between lhs_matrix_ and rhs_ return true. </para>
	/// <para> 
	///		If rhs_ is an EmuMath matrix: respective elements within the two matrices will be compared. 
	///		If this is the case, comparisons will only be performed on shared elements by default. To test all elements regardless of size, set TestAllIndices_ to true.
	/// </para>
	/// </summary>
	/// <typeparam name="LhsMatrix_">Matrix appearing on the left-hand side of equal_to comparisons.</typeparam>
	/// <typeparam name="Rhs_">Item appearing on the right-hand side of equal_to comparisons.</typeparam>
	/// <param name="lhs_matrix_">EmuMath matrix appearing on the left-hand side of equal_to comparisons.</param>
	/// <param name="rhs_">Item appearing on the right-hand side of equal_to comparisons.</param>
	/// <returns>Boolean indcating if comparisons on at least one element within lhs_matrix_ with rhs_ as defined above returned true.</returns>
	template<bool TestAllIndices_ = false, class LhsMatrix_, class Rhs_>
	constexpr inline bool MatrixCmpAnyLess(const LhsMatrix_& lhs_matrix_, const Rhs_& rhs_)
	{
		if constexpr (EmuMath::TMP::is_emu_matrix_v<LhsMatrix_>)
		{
			return _underlying_matrix_funcs::_matrix_cmp_any<TestAllIndices_, EmuCore::do_cmp_less, LhsMatrix_, Rhs_>(lhs_matrix_, rhs_);
		}
		else
		{
			static_assert(false, "Attempted to perform a CmpAnyLess operation on a matrix, but the passed lhs_matrix_ was not an EmuMath matrix.");
		}
	}

	/// <summary>
	/// <para> Returns true if any greater_equal comparisons between lhs_matrix_ and rhs_ return true. </para>
	/// <para> 
	///		If rhs_ is an EmuMath matrix: respective elements within the two matrices will be compared. 
	///		If this is the case, comparisons will only be performed on shared elements by default. To test all elements regardless of size, set TestAllIndices_ to true.
	/// </para>
	/// </summary>
	/// <typeparam name="LhsMatrix_">Matrix appearing on the left-hand side of equal_to comparisons.</typeparam>
	/// <typeparam name="Rhs_">Item appearing on the right-hand side of equal_to comparisons.</typeparam>
	/// <param name="lhs_matrix_">EmuMath matrix appearing on the left-hand side of equal_to comparisons.</param>
	/// <param name="rhs_">Item appearing on the right-hand side of equal_to comparisons.</param>
	/// <returns>Boolean indcating if comparisons on at least one element within lhs_matrix_ with rhs_ as defined above returned true.</returns>
	template<bool TestAllIndices_ = false, class LhsMatrix_, class Rhs_>
	constexpr inline bool MatrixCmpAnyGreaterEqual(const LhsMatrix_& lhs_matrix_, const Rhs_& rhs_)
	{
		if constexpr (EmuMath::TMP::is_emu_matrix_v<LhsMatrix_>)
		{
			return _underlying_matrix_funcs::_matrix_cmp_any<TestAllIndices_, EmuCore::do_cmp_greater_equal, LhsMatrix_, Rhs_>(lhs_matrix_, rhs_);
		}
		else
		{
			static_assert(false, "Attempted to perform a CmpAnyGreaterEqual operation on a matrix, but the passed lhs_matrix_ was not an EmuMath matrix.");
		}
	}

	/// <summary>
	/// <para> Returns true if any less_equal comparisons between lhs_matrix_ and rhs_ return true. </para>
	/// <para> 
	///		If rhs_ is an EmuMath matrix: respective elements within the two matrices will be compared. 
	///		If this is the case, comparisons will only be performed on shared elements by default. To test all elements regardless of size, set TestAllIndices_ to true.
	/// </para>
	/// </summary>
	/// <typeparam name="LhsMatrix_">Matrix appearing on the left-hand side of equal_to comparisons.</typeparam>
	/// <typeparam name="Rhs_">Item appearing on the right-hand side of equal_to comparisons.</typeparam>
	/// <param name="lhs_matrix_">EmuMath matrix appearing on the left-hand side of equal_to comparisons.</param>
	/// <param name="rhs_">Item appearing on the right-hand side of equal_to comparisons.</param>
	/// <returns>Boolean indcating if comparisons on at least one element within lhs_matrix_ with rhs_ as defined above returned true.</returns>
	template<bool TestAllIndices_ = false, class LhsMatrix_, class Rhs_>
	constexpr inline bool MatrixCmpAnyLessEqual(const LhsMatrix_& lhs_matrix_, const Rhs_& rhs_)
	{
		if constexpr (EmuMath::TMP::is_emu_matrix_v<LhsMatrix_>)
		{
			return _underlying_matrix_funcs::_matrix_cmp_any<TestAllIndices_, EmuCore::do_cmp_less_equal, LhsMatrix_, Rhs_>(lhs_matrix_, rhs_);
		}
		else
		{
			static_assert(false, "Attempted to perform a CmpAnyLessEqual operation on a matrix, but the passed lhs_matrix_ was not an EmuMath matrix.");
		}
	}
}

#endif
