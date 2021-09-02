#ifndef EMU_MATH_MATRIX_TMP_H_INC_
#define EMU_MATH_MATRIX_TMP_H_INC_ 1

#include "../../Vector.h"
#include <cstddef>
#include <cstdint>
#include <type_traits>

namespace EmuMath
{
	template<std::size_t NumColumns_, std::size_t NumRows_, typename T_, bool ColumnMajor_>
	struct Matrix;

	/// <summary>
	/// <para> The type of reference wrapper used to store references within an EmuMath matrix. </para>
	/// <para> This is the standard type for any references stored within an EmuMath matrix. References of other types are undefined and unsupported. </para>
	/// </summary>
	/// <typeparam name="T_">Type to be referencing. T_ itself should not be a reference type; the reference will be applied automatically.</typeparam>
	template<typename T_>
	using InternalMatrixReference = EmuMath::InternalVectorReference<T_>;

	/// <summary>
	/// <para> Alias for EmuMath matrices which contain non-const reference wrappers. </para>
	/// <para> This is the EmuMath standard for storing such references within a matrix. The behaviour of storing other types of references is undefined and unsupported. </para>
	/// </summary>
	/// <typeparam name="T_">Type to be referencing. T_ itself should not be a reference type; the reference will be applied automatically.</typeparam>
	template<std::size_t NumColumns_, std::size_t NumRows_, typename T_, bool ColumnMajor_ = true>
	using RefMatrix = EmuMath::Matrix<NumColumns_, NumRows_, EmuMath::InternalMatrixReference<T_>, ColumnMajor_>;
	/// <summary>
	/// <para> Alias for EmuMath matrices which contain const reference wrappers. </para>
	/// <para> This is the EmuMath standard for storing such references within a matrix. The behaviour of storing other types of references is undefined and unsupported. </para>
	/// </summary>
	/// <typeparam name="T_">Type to be referencing. T_ itself should not be a reference type; the reference will be applied automatically.</typeparam>
	template<std::size_t NumColumns_, std::size_t NumRows_, typename T_, bool ColumnMajor_ = true>
	using ConstRefMatrix = EmuMath::Matrix<NumColumns_, NumRows_, EmuMath::InternalMatrixReference<const T_>, ColumnMajor_>;
}

namespace EmuMath::TMP
{
	template<class T_>
	struct is_emu_matrix
	{
		static constexpr bool value = std::conditional_t
		<
			// This is a recursive check to make sure that T_ does not have modifiers that may lead to false negatives
			std::is_same_v<T_, std::remove_reference_t<std::remove_cv_t<T_>>>,
			std::false_type,
			is_emu_matrix<std::remove_reference_t<std::remove_cv_t<T_>>>
		>::value;
	};
	template<std::size_t NumColumns_, std::size_t NumRows_, typename T_, bool ColumnMajor_>
	struct is_emu_matrix<EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>>
	{
		static constexpr bool value = true;
	};
	template<class T_>
	static constexpr bool is_emu_matrix_v = is_emu_matrix<T_>::value;

	template<template<std::size_t NumColumns_, std::size_t NumRows_, typename T_, bool ColumnMajor_> class Template_>
	struct is_emu_matrix_template
	{
		static constexpr bool value = false;
	};
	template<>
	struct is_emu_matrix_template<EmuMath::Matrix>
	{
		static constexpr bool value = true;
	};

	template<std::size_t ColumnIndex_, std::size_t RowIndex_, class Matrix_>
	struct emu_matrix_theoretical_data
	{
		using type = void;
	};
	template<std::size_t ColumnIndex_, std::size_t RowIndex_, std::size_t NumColumns_, std::size_t NumRows_, typename T_, bool ColumnMajor_>
	struct emu_matrix_theoretical_data<ColumnIndex_, RowIndex_, EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>>
	{
		using type = std::conditional_t
		<
			(ColumnIndex_ < NumColumns_) && (RowIndex_ < NumRows_),
			const typename EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>::raw_value_type&,
			typename EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>::value_type
		>;
	};
	template<std::size_t ColumnIndex_, std::size_t RowIndex_, class Matrix_>
	using emu_matrix_theoretical_data_t = typename emu_matrix_theoretical_data<ColumnIndex_, RowIndex_, Matrix_>::type;

	template<std::size_t MajorOrderIndex_, class Matrix_>
	struct emu_matrix_theoretical_major_order_index_data
	{
		using type = void;
	};
	template<std::size_t MajorOrderIndex_, std::size_t NumColumns_, std::size_t NumRows_, typename T_, bool ColumnMajor_>
	struct emu_matrix_theoretical_major_order_index_data<MajorOrderIndex_, EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>>
	{
		using type = std::conditional_t
		<
			(MajorOrderIndex_ < EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>::size),
			const typename EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>::raw_value_type&,
			typename EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>::value_type
		>;
	};

	/// <summary>
	/// <para> Used to determine the type that will result from multiplying a Lhs_ matrix by a Rhs_ value. </para>
	/// <para> If Rhs_ is not an EmuMath matrix, the determined type will be of matching dimensions to the Lhs_ matrix. </para>
	/// <para> If the provided Lhs_ and Rhs_ types are invalid for matrix multiplication, the determined type will be void. </para>
	/// </summary>
	/// <typeparam name="out_contained_type">Type to be contained within the determined matrix.</typeparam>
	/// <typeparam name="Lhs_">Type of EmuMath matrix that would appear on the left-hand side of multiplication.</typeparam>
	/// <typeparam name="Rhs_">Type of EmuMath matrix or scalar that would appear on the right-hand side of multiplication.</typeparam>
	template<typename out_contained_type, bool OutColumnMajor_, class Lhs_, class Rhs_>
	struct emu_matrix_multiplication_result
	{
		using type = void;
	};
	template<typename out_contained_type, bool OutColumnMajor_, std::size_t LhsNumColumns_, std::size_t LhsNumRows_, typename LhsT_, bool LhsColumnMajor_, class Rhs_>
	struct emu_matrix_multiplication_result
	<
		out_contained_type,
		OutColumnMajor_,
		EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>,
		Rhs_
	>
	{
		using type = EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, out_contained_type, OutColumnMajor_>;
	};
	template
	<
		typename out_contained_type,
		bool OutColumnMajor_,
		std::size_t LhsNumColumns_,
		std::size_t LhsNumRows_,
		typename LhsT_,
		bool LhsColumnMajor_,
		std::size_t RhsNumColumns_,
		std::size_t RhsNumRows_,
		typename RhsT_,
		bool RhsColumnMajor_
	>
	struct emu_matrix_multiplication_result
	<
		out_contained_type,
		OutColumnMajor_,
		EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>,
		EmuMath::Matrix<RhsNumColumns_, RhsNumRows_, RhsT_, RhsColumnMajor_>
	>
	{
		using type = std::conditional_t
		<
			LhsNumColumns_ == RhsNumRows_,
			EmuMath::Matrix<RhsNumColumns_, LhsNumRows_, out_contained_type, OutColumnMajor_>,
			void
		>;
	};
	template<typename out_contained_type, bool OutColumnMajor_, class Lhs_, class Rhs_>
	using emu_matrix_multiplication_result_t = typename emu_matrix_multiplication_result<out_contained_type, OutColumnMajor_, Lhs_, Rhs_>::type;

	template<class Lhs_, class Rhs_>
	struct emu_matrix_multiplication_result_no_custom : public emu_matrix_multiplication_result<typename Lhs_::value_type, Lhs_::is_column_major, Lhs_, Rhs_>
	{
	};
	template<class Lhs_, class Rhs_>
	using emu_matrix_multiplication_result_no_custom_t = typename emu_matrix_multiplication_result_no_custom<Lhs_, Rhs_>::type;

	template<typename out_contained_type, bool OutColumnMajor_, class Matrix_>
	struct emu_matrix_transpose
	{
		using type = void;
	};
	template<typename out_contained_type, bool OutColumnMajor_, std::size_t NumColumns_, std::size_t NumRows_, typename T_, bool ColumnMajor_>
	struct emu_matrix_transpose<out_contained_type, OutColumnMajor_, EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>>
	{
		using type = EmuMath::Matrix<NumRows_, NumColumns_, out_contained_type, OutColumnMajor_>;
	};
	template<typename out_contained_type, bool OutColumnMajor_, class Matrix_>
	using emu_matrix_transpose_t = typename emu_matrix_transpose<out_contained_type, OutColumnMajor_, Matrix_>::type;

	template<typename out_contained_type, class Matrix_>
	struct emu_matrix_transpose_maintain_major : public emu_matrix_transpose<out_contained_type, Matrix_::is_column_major, Matrix_>
	{
	};
	template<typename out_contained_type, class Matrix_>
	using emu_matrix_transpose_maintain_major_t = typename emu_matrix_transpose_maintain_major<out_contained_type, Matrix_>::type;

	template<bool OutColumnMajor_, class Matrix_>
	struct emu_matrix_transpose_maintain_contained_type : public emu_matrix_transpose<typename Matrix_::contained_type, OutColumnMajor_, Matrix_>
	{
	};
	template<bool OutColumnMajor_, class Matrix_>
	using emu_matrix_transpose_maintain_contained_type_t = typename emu_matrix_transpose_maintain_contained_type<OutColumnMajor_, Matrix_>::type;

	template<class Matrix_>
	struct emu_matrix_transpose_match : public emu_matrix_transpose<typename Matrix_::contained_type, Matrix_::is_column_major, Matrix_>
	{
	};
	template<class Matrix_>
	using emu_matrix_transpose_match_t = typename emu_matrix_transpose_match<Matrix_>::type;

	template<typename out_contained_type, bool OutColumnMajor_, class Matrix_>
	struct emu_matrix_submatrix_excluding_element_region
	{
		using type = typename std::conditional_t
		<
			std::is_same_v<Matrix_, std::remove_cv_t<std::remove_reference_t<Matrix_>>>,
			EmuCore::TMPHelpers::void_type,
			emu_matrix_submatrix_excluding_element_region<out_contained_type, OutColumnMajor_, std::remove_cv_t<std::remove_reference_t<Matrix_>>>
		>::type;
	};
	template<typename out_contained_type, bool OutColumnMajor_, std::size_t NumColumns_, std::size_t NumRows_, typename T_, bool ColumnMajor_>
	struct emu_matrix_submatrix_excluding_element_region<out_contained_type, OutColumnMajor_, EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>>
	{
		using type = std::conditional_t
		<
			(NumColumns_ > 1) && (NumRows_ > 1),
			EmuMath::Matrix<NumColumns_ - 1, NumRows_ - 1, out_contained_type, OutColumnMajor_>,
			void
		>;
	};
	template<typename out_contained_type, bool OutColumnMajor_, class Matrix_>
	using emu_matrix_submatrix_excluding_element_region_t = typename emu_matrix_submatrix_excluding_element_region<out_contained_type, OutColumnMajor_, Matrix_>::type;
}

#endif

