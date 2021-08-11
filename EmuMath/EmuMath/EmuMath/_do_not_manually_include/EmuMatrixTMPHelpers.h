#ifndef EMU_MATRIX_TMP_COMPARATORS_H_INC_
#define EMU_MATRIX_TMP_COMPARATORS_H_INC_

#include <cstddef>

namespace EmuMath
{
	template<std::size_t NumColumns_, std::size_t NumRows_, typename T_>
	struct MatrixCM;
}

namespace EmuMath::TMPHelpers
{
	template<class T>
	struct is_emu_matrix
	{
		static constexpr bool value = false;
	};
	template<std::size_t NumColumns_, std::size_t NumRows_, typename T_>
	struct is_emu_matrix<EmuMath::MatrixCM<NumColumns_, NumRows_, T_>>
	{
		static constexpr bool value = true;
	};
	template<class T>
	static constexpr bool is_emu_matrix_v = is_emu_matrix<T>::value;

	template<template<std::size_t NumColumns__, std::size_t NumRows__, typename T__> class Template_>
	struct is_emu_matrix_template
	{
		static constexpr bool value = is_emu_matrix_v<Template_<4, 4, float>>;
	};
	template<template<std::size_t NumColumns__, std::size_t NumRows__, typename T__> class Template_>
	static constexpr bool is_emu_matrix_template_v = is_emu_matrix_template<Template_>::value;

	/// <summary> May be used to guarantee that a certain matrix type's identity matrix will be evaluated at compile time. </summary>
	template
	<
		std::size_t num_columns,
		std::size_t num_rows,
		typename value_type,
		template<std::size_t NumColumns__, std::size_t NumRows__, typename T__> class matrix_template
	>
	struct emu_matrix_identity
	{
	private:
		using matrix_type = matrix_template<num_columns, num_rows, value_type>;
		static_assert(is_emu_matrix_v<matrix_type>, "Provided a non-EmuMath-matrix template when attempting to access its identity matrix via emu_matrix_identity.");
		static_assert(num_columns == num_rows, "Provided a non-square size of columns and rows when attempting to access an identity matrix via emu_matrix_identity.");

	public:
		static constexpr matrix_type value = matrix_type::Identity();
	};
	/// <summary> Shorthand to access the value of emu_matrix_identity with the same template arguments. </summary>
	template
	<
		std::size_t num_columns,
		std::size_t num_rows,
		typename value_type,
		template<std::size_t NumColumns__, std::size_t NumRows__, typename T__> class matrix_template
	>
	static constexpr matrix_template<num_columns, num_rows, value_type> emu_matrix_identity_v = emu_matrix_identity<num_columns, num_rows, value_type, matrix_template>::value;

	template<std::size_t num_columns, std::size_t num_rows, typename value_type, class Matrix_>
	struct emu_matrix_matching_template
	{
		static_assert(is_emu_matrix_v<Matrix_>, "Passed a non-EmuMath-matrix type when attempting to instantiate a new template instance based on it via emu_matrix_matching_template.");
		using type = std::false_type;
	};
	template
	<
		std::size_t num_columns, std::size_t num_rows, typename value_type,
		std::size_t copy_columns, std::size_t copy_rows, typename copy_value_type, template<std::size_t Columns__, std::size_t Rows__, typename T__> class MatrixTemplate_
	>
	struct emu_matrix_matching_template<num_columns, num_rows, value_type, MatrixTemplate_<copy_columns, copy_rows, copy_value_type>>
	{
	private:
		using matrix_type = MatrixTemplate_<copy_columns, copy_rows, copy_value_type>;
		static_assert(is_emu_matrix_v<matrix_type>, "Passed a non-EmuMath-matrix type when attempting to instantiate a new template instance based on it via emu_matrix_matching_template.");

	public:
		using type = MatrixTemplate_<num_columns, num_rows, value_type>;
	};
	template<std::size_t num_columns, std::size_t num_rows, typename value_type, class Matrix_>
	using emu_matrix_matching_template_t = typename emu_matrix_matching_template<num_columns, num_rows, value_type, Matrix_>::type;
}

#endif
