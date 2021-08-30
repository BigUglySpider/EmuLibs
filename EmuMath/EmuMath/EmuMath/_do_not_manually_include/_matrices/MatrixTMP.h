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

	template<typename out_contained_type, class Matrix_>
	struct emu_matrix_transpose
	{
		using type = void;
	};
	template<typename out_contained_type, std::size_t NumColumns_, std::size_t NumRows_, typename T_, bool ColumnMajor_>
	struct emu_matrix_transpose<out_contained_type, EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>>
	{
		using type = EmuMath::Matrix<NumRows_, NumColumns_, out_contained_type, ColumnMajor_>;
	};
	template<typename out_contained_type, class Matrix_>
	using emu_matrix_transpose_t = typename emu_matrix_transpose<out_contained_type, Matrix_>::type;
	template<class Matrix_>
	using emu_matrix_transpose_copy_t = emu_matrix_transpose_t<typename Matrix_::value_type, Matrix_>;
	template<class Matrix_>
	using emu_matrix_transpose_same_contained_t = emu_matrix_transpose_t<typename Matrix_::contained_type, Matrix_>;
}

#endif
