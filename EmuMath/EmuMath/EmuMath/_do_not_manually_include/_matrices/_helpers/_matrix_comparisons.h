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
	[[nodiscard]] constexpr inline EmuMath::Matrix<NumColumnsToTest_, NumRowsToTest_, bool, OutColumnMajor_> matrix_cmp_per_element_equal
	(
		const LhsMatrix_& lhs_matrix_,
		const Rhs_& rhs_
	)
	{
		if constexpr (EmuMath::TMP::is_emu_matrix_v<LhsMatrix_>)
		{
			return _underlying_matrix_funcs::_matrix_multi_arg_operation
			<
				EmuCore::do_cmp_equal_to,
				EmuMath::Matrix<NumColumnsToTest_, NumRowsToTest_, bool, OutColumnMajor_>,
				LhsMatrix_,
				Rhs_
			>(lhs_matrix_, rhs_);
		}
		else
		{
			static_assert(false, "Attempted to compare equality of each element within a matrix, but the passed lhs_matrix_ was not an EmuMath matrix.");
		}
	}
	template<std::size_t NumColumnsToTest_, std::size_t NumRowsToTest_, class LhsMatrix_, class Rhs_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<NumColumnsToTest_, NumRowsToTest_, bool, LhsMatrix_::is_column_major> matrix_cmp_per_element_equal
	(
		const LhsMatrix_& lhs_matrix_,
		const Rhs_& rhs_
	)
	{
		return matrix_cmp_per_element_equal<NumColumnsToTest_, NumRowsToTest_, LhsMatrix_::is_column_major, LhsMatrix_, Rhs_>(lhs_matrix_, rhs_);
	}
	template<bool OutColumnMajor_, class LhsMatrix_, class Rhs_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<LhsMatrix_::num_columns, LhsMatrix_::num_rows, bool, OutColumnMajor_> matrix_cmp_per_element_equal
	(
		const LhsMatrix_& lhs_matrix_,
		const Rhs_& rhs_
	)
	{
		return matrix_cmp_per_element_equal<LhsMatrix_::num_columns, LhsMatrix_::num_rows, OutColumnMajor_, LhsMatrix_, Rhs_>(lhs_matrix_, rhs_);
	}
	template<class LhsMatrix_, class Rhs_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<LhsMatrix_::num_columns, LhsMatrix_::num_rows, bool, LhsMatrix_::is_column_major> matrix_cmp_per_element_equal
	(
		const LhsMatrix_& lhs_matrix_,
		const Rhs_& rhs_
	)
	{
		return matrix_cmp_per_element_equal<LhsMatrix_::num_columns, LhsMatrix_::num_rows, LhsMatrix_::is_column_major, LhsMatrix_, Rhs_>(lhs_matrix_, rhs_);
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
	[[nodiscard]] constexpr inline EmuMath::Matrix<NumColumnsToTest_, NumRowsToTest_, bool, OutColumnMajor_> matrix_cmp_per_element_not_equal
	(
		const LhsMatrix_& lhs_matrix_,
		const Rhs_& rhs_
	)
	{
		if constexpr (EmuMath::TMP::is_emu_matrix_v<LhsMatrix_>)
		{
			return _underlying_matrix_funcs::_matrix_multi_arg_operation
			<
				EmuCore::do_cmp_not_equal_to,
				EmuMath::Matrix<NumColumnsToTest_, NumRowsToTest_, bool, OutColumnMajor_>,
				LhsMatrix_,
				Rhs_
			>(lhs_matrix_, rhs_);
		}
		else
		{
			static_assert(false, "Attempted to compare inequality of each element within a matrix, but the passed lhs_matrix_ was not an EmuMath matrix.");
		}
	}
	template<std::size_t NumColumnsToTest_, std::size_t NumRowsToTest_, class LhsMatrix_, class Rhs_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<NumColumnsToTest_, NumRowsToTest_, bool, LhsMatrix_::is_column_major> matrix_cmp_per_element_not_equal
	(
		const LhsMatrix_& lhs_matrix_,
		const Rhs_& rhs_
	)
	{
		return matrix_cmp_per_element_not_equal<NumColumnsToTest_, NumRowsToTest_, LhsMatrix_::is_column_major, LhsMatrix_, Rhs_>(lhs_matrix_, rhs_);
	}
	template<bool OutColumnMajor_, class LhsMatrix_, class Rhs_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<LhsMatrix_::num_columns, LhsMatrix_::num_rows, bool, OutColumnMajor_> matrix_cmp_per_element_not_equal
	(
		const LhsMatrix_& lhs_matrix_,
		const Rhs_& rhs_
	)
	{
		return matrix_cmp_per_element_not_equal<LhsMatrix_::num_columns, LhsMatrix_::num_rows, OutColumnMajor_, LhsMatrix_, Rhs_>(lhs_matrix_, rhs_);
	}
	template<class LhsMatrix_, class Rhs_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<LhsMatrix_::num_columns, LhsMatrix_::num_rows, bool, LhsMatrix_::is_column_major> matrix_cmp_per_element_not_equal
	(
		const LhsMatrix_& lhs_matrix_,
		const Rhs_& rhs_
	)
	{
		return matrix_cmp_per_element_not_equal<LhsMatrix_::num_columns, LhsMatrix_::num_rows, LhsMatrix_::is_column_major, LhsMatrix_, Rhs_>(lhs_matrix_, rhs_);
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
	[[nodiscard]] constexpr inline EmuMath::Matrix<NumColumnsToTest_, NumRowsToTest_, bool, OutColumnMajor_> matrix_cmp_per_element_greater
	(
		const LhsMatrix_& lhs_matrix_,
		const Rhs_& rhs_
	)
	{
		if constexpr (EmuMath::TMP::is_emu_matrix_v<LhsMatrix_>)
		{
			return _underlying_matrix_funcs::_matrix_multi_arg_operation
			<
				EmuCore::do_cmp_greater,
				EmuMath::Matrix<NumColumnsToTest_, NumRowsToTest_, bool, OutColumnMajor_>,
				LhsMatrix_,
				Rhs_
			>(lhs_matrix_, rhs_);
		}
		else
		{
			static_assert(false, "Attempted to compare magnitude of each element within a matrix, but the passed lhs_matrix_ was not an EmuMath matrix.");
		}
	}
	template<std::size_t NumColumnsToTest_, std::size_t NumRowsToTest_, class LhsMatrix_, class Rhs_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<NumColumnsToTest_, NumRowsToTest_, bool, LhsMatrix_::is_column_major> matrix_cmp_per_element_greater
	(
		const LhsMatrix_& lhs_matrix_,
		const Rhs_& rhs_
	)
	{
		return matrix_cmp_per_element_greater<NumColumnsToTest_, NumRowsToTest_, LhsMatrix_::is_column_major, LhsMatrix_, Rhs_>(lhs_matrix_, rhs_);
	}
	template<bool OutColumnMajor_, class LhsMatrix_, class Rhs_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<LhsMatrix_::num_columns, LhsMatrix_::num_rows, bool, OutColumnMajor_> matrix_cmp_per_element_greater
	(
		const LhsMatrix_& lhs_matrix_,
		const Rhs_& rhs_
	)
	{
		return matrix_cmp_per_element_greater<LhsMatrix_::num_columns, LhsMatrix_::num_rows, OutColumnMajor_, LhsMatrix_, Rhs_>(lhs_matrix_, rhs_);
	}
	template<class LhsMatrix_, class Rhs_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<LhsMatrix_::num_columns, LhsMatrix_::num_rows, bool, LhsMatrix_::is_column_major> matrix_cmp_per_element_greater
	(
		const LhsMatrix_& lhs_matrix_,
		const Rhs_& rhs_
	)
	{
		return matrix_cmp_per_element_greater<LhsMatrix_::num_columns, LhsMatrix_::num_rows, LhsMatrix_::is_column_major, LhsMatrix_, Rhs_>(lhs_matrix_, rhs_);
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
	[[nodiscard]] constexpr inline EmuMath::Matrix<NumColumnsToTest_, NumRowsToTest_, bool, OutColumnMajor_> matrix_cmp_per_element_less
	(
		const LhsMatrix_& lhs_matrix_,
		const Rhs_& rhs_
	)
	{
		if constexpr (EmuMath::TMP::is_emu_matrix_v<LhsMatrix_>)
		{
			return _underlying_matrix_funcs::_matrix_multi_arg_operation
			<
				EmuCore::do_cmp_less,
				EmuMath::Matrix<NumColumnsToTest_, NumRowsToTest_, bool, OutColumnMajor_>,
				LhsMatrix_,
				Rhs_
			>(lhs_matrix_, rhs_);
		}
		else
		{
			static_assert(false, "Attempted to compare magnitude of each element within a matrix, but the passed lhs_matrix_ was not an EmuMath matrix.");
		}
	}
	template<std::size_t NumColumnsToTest_, std::size_t NumRowsToTest_, class LhsMatrix_, class Rhs_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<NumColumnsToTest_, NumRowsToTest_, bool, LhsMatrix_::is_column_major> matrix_cmp_per_element_less
	(
		const LhsMatrix_& lhs_matrix_,
		const Rhs_& rhs_
	)
	{
		return matrix_cmp_per_element_less<NumColumnsToTest_, NumRowsToTest_, LhsMatrix_::is_column_major, LhsMatrix_, Rhs_>(lhs_matrix_, rhs_);
	}
	template<bool OutColumnMajor_, class LhsMatrix_, class Rhs_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<LhsMatrix_::num_columns, LhsMatrix_::num_rows, bool, OutColumnMajor_> matrix_cmp_per_element_less
	(
		const LhsMatrix_& lhs_matrix_,
		const Rhs_& rhs_
	)
	{
		return matrix_cmp_per_element_less<LhsMatrix_::num_columns, LhsMatrix_::num_rows, OutColumnMajor_, LhsMatrix_, Rhs_>(lhs_matrix_, rhs_);
	}
	template<class LhsMatrix_, class Rhs_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<LhsMatrix_::num_columns, LhsMatrix_::num_rows, bool, LhsMatrix_::is_column_major> matrix_cmp_per_element_less
	(
		const LhsMatrix_& lhs_matrix_,
		const Rhs_& rhs_
	)
	{
		return matrix_cmp_per_element_less<LhsMatrix_::num_columns, LhsMatrix_::num_rows, LhsMatrix_::is_column_major, LhsMatrix_, Rhs_>(lhs_matrix_, rhs_);
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
	[[nodiscard]] constexpr inline EmuMath::Matrix<NumColumnsToTest_, NumRowsToTest_, bool, OutColumnMajor_> matrix_cmp_per_element_greater_equal
	(
		const LhsMatrix_& lhs_matrix_,
		const Rhs_& rhs_
	)
	{
		if constexpr (EmuMath::TMP::is_emu_matrix_v<LhsMatrix_>)
		{
			return _underlying_matrix_funcs::_matrix_multi_arg_operation
			<
				EmuCore::do_cmp_greater_equal,
				EmuMath::Matrix<NumColumnsToTest_, NumRowsToTest_, bool, OutColumnMajor_>,
				LhsMatrix_,
				Rhs_
			>(lhs_matrix_, rhs_);
		}
		else
		{
			static_assert(false, "Attempted to compare magnitude of each element within a matrix, but the passed lhs_matrix_ was not an EmuMath matrix.");
		}
	}
	template<std::size_t NumColumnsToTest_, std::size_t NumRowsToTest_, class LhsMatrix_, class Rhs_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<NumColumnsToTest_, NumRowsToTest_, bool, LhsMatrix_::is_column_major> matrix_cmp_per_element_greater_equal
	(
		const LhsMatrix_& lhs_matrix_,
		const Rhs_& rhs_
	)
	{
		return matrix_cmp_per_element_greater_equal<NumColumnsToTest_, NumRowsToTest_, LhsMatrix_::is_column_major, LhsMatrix_, Rhs_>(lhs_matrix_, rhs_);
	}
	template<bool OutColumnMajor_, class LhsMatrix_, class Rhs_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<LhsMatrix_::num_columns, LhsMatrix_::num_rows, bool, OutColumnMajor_> matrix_cmp_per_element_greater_equal
	(
		const LhsMatrix_& lhs_matrix_,
		const Rhs_& rhs_
	)
	{
		return matrix_cmp_per_element_greater_equal<LhsMatrix_::num_columns, LhsMatrix_::num_rows, OutColumnMajor_, LhsMatrix_, Rhs_>(lhs_matrix_, rhs_);
	}
	template<class LhsMatrix_, class Rhs_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<LhsMatrix_::num_columns, LhsMatrix_::num_rows, bool, LhsMatrix_::is_column_major> matrix_cmp_per_element_greater_equal
	(
		const LhsMatrix_& lhs_matrix_,
		const Rhs_& rhs_
	)
	{
		return matrix_cmp_per_element_greater_equal<LhsMatrix_::num_columns, LhsMatrix_::num_rows, LhsMatrix_::is_column_major, LhsMatrix_, Rhs_>(lhs_matrix_, rhs_);
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
	[[nodiscard]] constexpr inline EmuMath::Matrix<NumColumnsToTest_, NumRowsToTest_, bool, OutColumnMajor_> matrix_cmp_per_element_less_equal
	(
		const LhsMatrix_& lhs_matrix_,
		const Rhs_& rhs_
	)
	{
		if constexpr (EmuMath::TMP::is_emu_matrix_v<LhsMatrix_>)
		{
			return _underlying_matrix_funcs::_matrix_multi_arg_operation
			<
				EmuCore::do_cmp_less_equal,
				EmuMath::Matrix<NumColumnsToTest_, NumRowsToTest_, bool, OutColumnMajor_>,
				LhsMatrix_,
				Rhs_
			>(lhs_matrix_, rhs_);
		}
		else
		{
			static_assert(false, "Attempted to compare magnitude of each element within a matrix, but the passed lhs_matrix_ was not an EmuMath matrix.");
		}
	}
	template<std::size_t NumColumnsToTest_, std::size_t NumRowsToTest_, class LhsMatrix_, class Rhs_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<NumColumnsToTest_, NumRowsToTest_, bool, LhsMatrix_::is_column_major> matrix_cmp_per_element_less_equal
	(
		const LhsMatrix_& lhs_matrix_,
		const Rhs_& rhs_
	)
	{
		return matrix_cmp_per_element_less_equal<NumColumnsToTest_, NumRowsToTest_, LhsMatrix_::is_column_major, LhsMatrix_, Rhs_>(lhs_matrix_, rhs_);
	}
	template<bool OutColumnMajor_, class LhsMatrix_, class Rhs_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<LhsMatrix_::num_columns, LhsMatrix_::num_rows, bool, OutColumnMajor_> matrix_cmp_per_element_less_equal
	(
		const LhsMatrix_& lhs_matrix_,
		const Rhs_& rhs_
	)
	{
		return matrix_cmp_per_element_less_equal<LhsMatrix_::num_columns, LhsMatrix_::num_rows, OutColumnMajor_, LhsMatrix_, Rhs_>(lhs_matrix_, rhs_);
	}
	template<class LhsMatrix_, class Rhs_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<LhsMatrix_::num_columns, LhsMatrix_::num_rows, bool, LhsMatrix_::is_column_major> matrix_cmp_per_element_less_equal
	(
		const LhsMatrix_& lhs_matrix_,
		const Rhs_& rhs_
	)
	{
		return matrix_cmp_per_element_less_equal<LhsMatrix_::num_columns, LhsMatrix_::num_rows, LhsMatrix_::is_column_major, LhsMatrix_, Rhs_>(lhs_matrix_, rhs_);
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
	[[nodiscard]] constexpr inline bool matrix_cmp_all_true(const LhsMatrix_& lhs_matrix_, const Rhs_& rhs_)
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
	[[nodiscard]] constexpr inline bool matrix_cmp_all_true(const LhsMatrix_& lhs_matrix_, const Rhs_& rhs_, Func_ func_)
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
	[[nodiscard]] constexpr inline bool matrix_cmp_all_equal(const LhsMatrix_& lhs_matrix_, const Rhs_& rhs_)
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
	[[nodiscard]] constexpr inline bool matrix_cmp_all_not_equal(const LhsMatrix_& lhs_matrix_, const Rhs_& rhs_)
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
	[[nodiscard]] constexpr inline bool matrix_cmp_all_greater(const LhsMatrix_& lhs_matrix_, const Rhs_& rhs_)
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
	[[nodiscard]] constexpr inline bool matrix_cmp_all_less(const LhsMatrix_& lhs_matrix_, const Rhs_& rhs_)
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
	[[nodiscard]] constexpr inline bool matrix_cmp_all_greater_equal(const LhsMatrix_& lhs_matrix_, const Rhs_& rhs_)
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
	[[nodiscard]] constexpr inline bool matrix_cmp_all_less_equal(const LhsMatrix_& lhs_matrix_, const Rhs_& rhs_)
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
	[[nodiscard]] constexpr inline bool matrix_cmp_any_true(const LhsMatrix_& lhs_matrix_, const Rhs_& rhs_)
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
	[[nodiscard]] constexpr inline bool matrix_cmp_any_true(const LhsMatrix_& lhs_matrix_, const Rhs_& rhs_, Func_ func_)
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
	[[nodiscard]] constexpr inline bool matrix_cmp_any_equal(const LhsMatrix_& lhs_matrix_, const Rhs_& rhs_)
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
	[[nodiscard]] constexpr inline bool matrix_cmp_any_not_equal(const LhsMatrix_& lhs_matrix_, const Rhs_& rhs_)
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
	[[nodiscard]] constexpr inline bool matrix_cmp_any_greater(const LhsMatrix_& lhs_matrix_, const Rhs_& rhs_)
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
	[[nodiscard]] constexpr inline bool matrix_cmp_any_less(const LhsMatrix_& lhs_matrix_, const Rhs_& rhs_)
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
	[[nodiscard]] constexpr inline bool matrix_cmp_any_greater_equal(const LhsMatrix_& lhs_matrix_, const Rhs_& rhs_)
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
	[[nodiscard]] constexpr inline bool matrix_cmp_any_less_equal(const LhsMatrix_& lhs_matrix_, const Rhs_& rhs_)
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

	/// <summary>
	/// <para> Returns true if the two passed matrices are equal. </para>
	/// <para>
	///		By default, only the lowest-sized matrix indices are compared.
	///		To compare even non-existent indices, set the TestAllIndices_ template argument to true.
	/// </para>
	/// </summary>
	/// <typeparam name="LhsMatrix_">Type of matrix appearing on the left of the comparison.</typeparam>
	/// <typeparam name="RhsMatrix_">Type of matrix appearing on the right of the comparison.</typeparam>
	/// <param name="lhs_matrix_">EmuMath matrix appearing on the left of the comparison.</param>
	/// <param name="rhs_matrix_">EmuMath matrix appearing on the right of the comparison.</param>
	/// <returns>
	///		True if all respective elements (overall or smallest-size, depending on TestAllIndices_ value) of the passed matrices are equal; otherwise false.
	/// </returns>
	template<bool TestAllIndices_ = false, class LhsMatrix_, class RhsMatrix_>
	[[nodiscard]] constexpr inline bool matrix_cmp_equal(const LhsMatrix_& lhs_matrix_, const RhsMatrix_& rhs_matrix_)
	{
		if constexpr (EmuMath::TMP::is_emu_matrix_v<LhsMatrix_>)
		{
			if constexpr (EmuMath::TMP::is_emu_matrix_v<RhsMatrix_>)
			{
				return matrix_cmp_all_equal<TestAllIndices_, LhsMatrix_, RhsMatrix_>(lhs_matrix_, rhs_matrix_);
			}
			else
			{
				static_assert(false, "Attempted to compare two matrices for equality, but the provided rhs_matrix_ was not an EmuMath matrix.");
			}
		}
		else
		{
			static_assert(false, "Attempted to compare two matrices for equality, but the provided lhs_matrix_ was not an EmuMath matrix.");
		}
	}

	/// <summary>
	/// <para> Returns true if the two passed matrices are unequal. </para>
	/// <para>
	///		By default, only the lowest-sized matrix indices are compared.
	///		To compare even non-existent indices, set the TestAllIndices_ template argument to true.
	/// </para>
	/// </summary>
	/// <typeparam name="LhsMatrix_">Type of matrix appearing on the left of the comparison.</typeparam>
	/// <typeparam name="RhsMatrix_">Type of matrix appearing on the right of the comparison.</typeparam>
	/// <param name="lhs_matrix_">EmuMath matrix appearing on the left of the comparison.</param>
	/// <param name="rhs_matrix_">EmuMath matrix appearing on the right of the comparison.</param>
	/// <returns>
	///		True if at least one respective element (overall or smallest-size, depending on TestAllIndices_ value) of the passed matrices is not equal; otherwise false.
	/// </returns>
	template<bool TestAllIndices_ = false, class LhsMatrix_, class RhsMatrix_>
	[[nodiscard]] constexpr inline bool matrix_cmp_not_equal(const LhsMatrix_& lhs_matrix_, const RhsMatrix_& rhs_matrix_)
	{
		if constexpr (EmuMath::TMP::is_emu_matrix_v<LhsMatrix_>)
		{
			if constexpr (EmuMath::TMP::is_emu_matrix_v<RhsMatrix_>)
			{
				return matrix_cmp_any_not_equal<TestAllIndices_, LhsMatrix_, RhsMatrix_>(lhs_matrix_, rhs_matrix_);
			}
			else
			{
				static_assert(false, "Attempted to compare two matrices for inequality, but the provided rhs_matrix_ was not an EmuMath matrix.");
			}
		}
		else
		{
			static_assert(false, "Attempted to compare two matrices for inequality, but the provided lhs_matrix_ was not an EmuMath matrix.");
		}
	}
}

#endif
