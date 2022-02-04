#ifndef EMU_MATH_MATRIX_BASIC_ARITHMETIC_FMADD_H_INC_
#define EMU_MATH_MATRIX_BASIC_ARITHMETIC_FMADD_H_INC_ 1

#include "../_common_matrix_helper_includes.h"

// CONTAINS:
// --- fmadd
// --- fmadd_range
// --- fmadd_range_no_copy

namespace EmuMath::Helpers
{
#pragma region FMADD_CUSTOM_COLUMN_MAJOR_OUT
	/// <summary>
	/// <para>
	///		Outputs the result of a fused multiply-add operation on the provided matrix_x_, using arguments y_ and z_,
	///		with output size/column-major arguments matching those of matrix_x_ if not provided, and value_type_uq for its T_ argument if OutT_ is not provided.
	/// </para>
	/// <para> If Y_ is an EmuMath Matrix: Respective elements in matrix_x_ and y_ will be multiplied. Otherwise, all elements in matrix_x_ will be multiplied by y_. </para>
	/// <para>
	///		If Z_ is an EmuMath Matrix: Intermediate results from each multiplication in specific indices will have the respective indices of z_ added. 
	///		Otherwise, all intermediate multiplication results will have z_ added directly.
	/// </para>
	/// </summary>
	/// <param name="matrix_x_">: EmuMath Matrix to perform a fused multiply-add on.</param>
	/// <param name="y_">: Scalar or EmuMath Matrix to multiply matrix_x_ by.</param>
	/// <param name="z_">: Scalar or EmuMath Matrix to add to intermediate multiplication results.</param>
	/// <returns>EmuMath Matrix containing the results of fmadd operations with the provided arguments in respective indices.</returns>
	template
	<
		std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, bool OutColumnMajor_,
		typename TX_, std::size_t NumColumnsX_, std::size_t NumRowsX_, bool ColumnMajorX_, class Y_, class Z_
	>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_> matrix_fmadd
	(
		const EmuMath::Matrix<NumColumnsX_, NumRowsX_, TX_, ColumnMajorX_>& matrix_x_,
		Y_&& y_,
		Z_&& z_
	)
	{
		using x_mat_ref = const EmuMath::Matrix<NumColumnsX_, NumRowsX_, TX_, ColumnMajorX_>&;
		return EMU_MATH_MATRIX_MUTATE_COPY_TEMPLATE(EmuCore::do_fmadd, OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_, x_mat_ref, 0, 0)
		(
			matrix_x_,
			matrix_x_,
			std::forward<Y_>(y_),
			std::forward<Z_>(z_)
		);
	}

	template<typename OutT_, bool OutColumnMajor_, typename TX_, std::size_t NumColumnsX_, std::size_t NumRowsX_, bool ColumnMajorX_, class Y_, class Z_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<NumColumnsX_, NumRowsX_, OutT_, OutColumnMajor_> matrix_fmadd
	(
		const EmuMath::Matrix<NumColumnsX_, NumRowsX_, TX_, ColumnMajorX_>& matrix_x_,
		Y_&& y_,
		Z_&& z_
	)
	{
		using x_mat_ref = const EmuMath::Matrix<NumColumnsX_, NumRowsX_, TX_, ColumnMajorX_>&;
		return EMU_MATH_MATRIX_MUTATE_COPY_TEMPLATE(EmuCore::do_fmadd, NumColumnsX_, NumRowsX_, OutT_, OutColumnMajor_, x_mat_ref, 0, 0)
		(
			matrix_x_,
			matrix_x_,
			std::forward<Y_>(y_),
			std::forward<Z_>(z_)
		);
	}

	template
	<
		std::size_t OutNumColumns_, std::size_t OutNumRows_, bool OutColumnMajor_,
		typename TX_, std::size_t NumColumnsX_, std::size_t NumRowsX_, bool ColumnMajorX_, class Y_, class Z_
	>
	[[nodiscard]] constexpr inline EmuMath::Matrix
	<
		OutNumColumns_,
		OutNumRows_,
		typename EmuMath::Matrix<NumColumnsX_, NumRowsX_, TX_, ColumnMajorX_>::value_type_uq,
		OutColumnMajor_
	>
	matrix_fmadd(const EmuMath::Matrix<NumColumnsX_, NumRowsX_, TX_, ColumnMajorX_>& matrix_x_, Y_&& y_, Z_&& z_)
	{
		using x_mat_ref = const EmuMath::Matrix<NumColumnsX_, NumRowsX_, TX_, ColumnMajorX_>&;
		using x_value_uq = typename EmuMath::Matrix<NumColumnsX_, NumRowsX_, TX_, ColumnMajorX_>::value_type_uq;
		return EMU_MATH_MATRIX_MUTATE_COPY_TEMPLATE(EmuCore::do_fmadd, OutNumColumns_, OutNumRows_, x_value_uq, OutColumnMajor_, x_mat_ref, 0, 0)
		(
			matrix_x_,
			matrix_x_,
			std::forward<Y_>(y_),
			std::forward<Z_>(z_)
		);
	}

	template<bool OutColumnMajor_, typename TX_, std::size_t NumColumnsX_, std::size_t NumRowsX_, bool ColumnMajorX_, class Y_, class Z_>
	[[nodiscard]] constexpr inline EmuMath::Matrix
	<
		NumColumnsX_,
		NumRowsX_,
		typename EmuMath::Matrix<NumColumnsX_, NumRowsX_, TX_, ColumnMajorX_>::value_type_uq,
		OutColumnMajor_
	>
	matrix_fmadd(const EmuMath::Matrix<NumColumnsX_, NumRowsX_, TX_, ColumnMajorX_>& matrix_x_, Y_&& y_, Z_&& z_)
	{
		using x_mat_ref = const EmuMath::Matrix<NumColumnsX_, NumRowsX_, TX_, ColumnMajorX_>&;
		using x_value_uq = typename EmuMath::Matrix<NumColumnsX_, NumRowsX_, TX_, ColumnMajorX_>::value_type_uq;
		return EMU_MATH_MATRIX_MUTATE_COPY_TEMPLATE(EmuCore::do_fmadd, NumColumnsX_, NumRowsX_, x_value_uq, OutColumnMajor_, x_mat_ref, 0, 0)
		(
			matrix_x_,
			matrix_x_,
			std::forward<Y_>(y_),
			std::forward<Z_>(z_)
		);
	}
#pragma endregion

#pragma region FMADD_MATCHING_COLUMN_MAJOR_OUT
	template
	<
		std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_,
		typename TX_, std::size_t NumColumnsX_, std::size_t NumRowsX_, bool ColumnMajorX_, class Y_, class Z_
	>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, ColumnMajorX_> matrix_fmadd
	(
		const EmuMath::Matrix<NumColumnsX_, NumRowsX_, TX_, ColumnMajorX_>& matrix_x_,
		Y_&& y_,
		Z_&& z_
	)
	{
		using x_mat_ref = const EmuMath::Matrix<NumColumnsX_, NumRowsX_, TX_, ColumnMajorX_>&;
		return EMU_MATH_MATRIX_MUTATE_COPY_TEMPLATE(EmuCore::do_fmadd, OutNumColumns_, OutNumRows_, OutT_, ColumnMajorX_, x_mat_ref, 0, 0)
		(
			matrix_x_,
			matrix_x_,
			std::forward<Y_>(y_),
			std::forward<Z_>(z_)
		);
	}

	template<typename OutT_, typename TX_, std::size_t NumColumnsX_, std::size_t NumRowsX_, bool ColumnMajorX_, class Y_, class Z_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<NumColumnsX_, NumRowsX_, OutT_, ColumnMajorX_> matrix_fmadd
	(
		const EmuMath::Matrix<NumColumnsX_, NumRowsX_, TX_, ColumnMajorX_>& matrix_x_,
		Y_&& y_,
		Z_&& z_
	)
	{
		using x_mat_ref = const EmuMath::Matrix<NumColumnsX_, NumRowsX_, TX_, ColumnMajorX_>&;
		return EMU_MATH_MATRIX_MUTATE_COPY_TEMPLATE(EmuCore::do_fmadd, NumColumnsX_, NumRowsX_, OutT_, ColumnMajorX_, x_mat_ref, 0, 0)
		(
			matrix_x_,
			matrix_x_,
			std::forward<Y_>(y_),
			std::forward<Z_>(z_)
		);
	}

	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename TX_, std::size_t NumColumnsX_, std::size_t NumRowsX_, bool ColumnMajorX_, class Y_, class Z_>
	[[nodiscard]] constexpr inline EmuMath::Matrix
	<
		OutNumColumns_,
		OutNumRows_,
		typename EmuMath::Matrix<NumColumnsX_, NumRowsX_, TX_, ColumnMajorX_>::value_type_uq,
		ColumnMajorX_
	>
	matrix_fmadd(const EmuMath::Matrix<NumColumnsX_, NumRowsX_, TX_, ColumnMajorX_>& matrix_x_, Y_&& y_, Z_&& z_)
	{
		using x_mat_ref = const EmuMath::Matrix<NumColumnsX_, NumRowsX_, TX_, ColumnMajorX_>&;
		using x_value_uq = typename EmuMath::Matrix<NumColumnsX_, NumRowsX_, TX_, ColumnMajorX_>::value_type_uq;
		return EMU_MATH_MATRIX_MUTATE_COPY_TEMPLATE(EmuCore::do_fmadd, OutNumColumns_, OutNumRows_, x_value_uq, ColumnMajorX_, x_mat_ref, 0, 0)
		(
			matrix_x_,
			matrix_x_,
			std::forward<Y_>(y_),
			std::forward<Z_>(z_)
		);
	}

	template<typename TX_, std::size_t NumColumnsX_, std::size_t NumRowsX_, bool ColumnMajorX_, class Y_, class Z_>
	[[nodiscard]] constexpr inline EmuMath::Matrix
	<
		NumColumnsX_,
		NumRowsX_,
		typename EmuMath::Matrix<NumColumnsX_, NumRowsX_, TX_, ColumnMajorX_>::value_type_uq,
		ColumnMajorX_
	>
	matrix_fmadd(const EmuMath::Matrix<NumColumnsX_, NumRowsX_, TX_, ColumnMajorX_>& matrix_x_, Y_&& y_, Z_&& z_)
	{
		using x_mat_ref = const EmuMath::Matrix<NumColumnsX_, NumRowsX_, TX_, ColumnMajorX_>&;
		using x_value_uq = typename EmuMath::Matrix<NumColumnsX_, NumRowsX_, TX_, ColumnMajorX_>::value_type_uq;
		return EMU_MATH_MATRIX_MUTATE_COPY_TEMPLATE(EmuCore::do_fmadd, NumColumnsX_, NumRowsX_, x_value_uq, ColumnMajorX_, x_mat_ref, 0, 0)
		(
			matrix_x_,
			matrix_x_,
			std::forward<Y_>(y_),
			std::forward<Z_>(z_)
		);
	}
#pragma endregion

#pragma region FMADD_RANGE_CUSTOM_COLUMN_MAJOR_OUT
	/// <summary>
	/// <para>
	///		Outputs the result of a fused multiply-add operation on the provided matrix_x_, using arguments y_ and z_,
	///		with output size/column-major arguments matching those of matrix_x_ if not provided, and value_type_uq for its T_ argument if OutT_ is not provided.
	/// </para>
	/// <para> If Y_ is an EmuMath Matrix: Respective elements in matrix_x_ and y_ will be multiplied. Otherwise, all elements in matrix_x_ will be multiplied by y_. </para>
	/// <para>
	///		If Z_ is an EmuMath Matrix: Intermediate results from each multiplication in specific indices will have the respective indices of z_ added. 
	///		Otherwise, all intermediate multiplication results will have z_ added directly.
	/// </para>
	/// <para> Indices within the provided range will contain results of respective fused multiply-addition operations. </para>
	/// <para> Indices outside of the provided range will be copies of the respective indices in matrix_x_. </para>
	/// </summary>
	/// <param name="matrix_x_">: EmuMath Matrix to perform a fused multiply-add on.</param>
	/// <param name="y_">: Scalar or EmuMath Matrix to multiply matrix_x_ by.</param>
	/// <param name="z_">: Scalar or EmuMath Matrix to add to intermediate multiplication results.</param>
	/// <returns>EmuMath Matrix containing the results of fmadd in respective indices within the provided range, and copied respective elements of matrix_x_ elsewhere.</returns>
	template
	<
		std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_,
		std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, bool OutColumnMajor_,
		typename TX_, std::size_t NumColumnsX_, std::size_t NumRowsX_, bool ColumnMajorX_, class Y_, class Z_
	>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_> matrix_fmadd_range
	(
		const EmuMath::Matrix<NumColumnsX_, NumRowsX_, TX_, ColumnMajorX_>& matrix_x_,
		Y_&& y_,
		Z_&& z_
	)
	{
		using x_mat_ref = const EmuMath::Matrix<NumColumnsX_, NumRowsX_, TX_, ColumnMajorX_>&;
		return EMU_MATH_MATRIX_MUTATE_COPY_RANGE_TEMPLATE
		(
			EmuCore::do_fmadd, OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_, x_mat_ref, BeginColumn_, EndColumn_, BeginRow_, EndRow_, 0, 0
		)(matrix_x_, matrix_x_, std::forward<Y_>(y_), std::forward<Z_>(z_));
	}

	template
	<
		std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_, typename OutT_, bool OutColumnMajor_,
		typename TX_, std::size_t NumColumnsX_, std::size_t NumRowsX_, bool ColumnMajorX_, class Y_, class Z_
	>
	[[nodiscard]] constexpr inline EmuMath::Matrix<NumColumnsX_, NumRowsX_, OutT_, OutColumnMajor_> matrix_fmadd_range
	(
		const EmuMath::Matrix<NumColumnsX_, NumRowsX_, TX_, ColumnMajorX_>& matrix_x_,
		Y_&& y_,
		Z_&& z_
	)
	{
		using x_mat_ref = const EmuMath::Matrix<NumColumnsX_, NumRowsX_, TX_, ColumnMajorX_>&;
		return EMU_MATH_MATRIX_MUTATE_COPY_RANGE_TEMPLATE
		(
			EmuCore::do_fmadd, NumColumnsX_, NumRowsX_, OutT_, OutColumnMajor_, x_mat_ref, BeginColumn_, EndColumn_, BeginRow_, EndRow_, 0, 0
		)(matrix_x_, matrix_x_, std::forward<Y_>(y_), std::forward<Z_>(z_));
	}

	template
	<
		std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_, std::size_t OutNumColumns_, std::size_t OutNumRows_, bool OutColumnMajor_,
		typename TX_, std::size_t NumColumnsX_, std::size_t NumRowsX_, bool ColumnMajorX_, class Y_, class Z_
	>
	[[nodiscard]] constexpr inline EmuMath::Matrix
	<
		OutNumColumns_,
		OutNumRows_,
		typename EmuMath::Matrix<NumColumnsX_, NumRowsX_, TX_, ColumnMajorX_>::value_type_uq,
		OutColumnMajor_
	>
	matrix_fmadd_range(const EmuMath::Matrix<NumColumnsX_, NumRowsX_, TX_, ColumnMajorX_>& matrix_x_, Y_&& y_, Z_&& z_)
	{
		using x_mat_ref = const EmuMath::Matrix<NumColumnsX_, NumRowsX_, TX_, ColumnMajorX_>&;
		using x_value_uq = typename EmuMath::Matrix<NumColumnsX_, NumRowsX_, TX_, ColumnMajorX_>::value_type_uq;
		return EMU_MATH_MATRIX_MUTATE_COPY_RANGE_TEMPLATE
		(
			EmuCore::do_fmadd, OutNumColumns_, OutNumRows_, x_value_uq, OutColumnMajor_, x_mat_ref, BeginColumn_, EndColumn_, BeginRow_, EndRow_, 0, 0
		)(matrix_x_, matrix_x_, std::forward<Y_>(y_), std::forward<Z_>(z_));
	}

	template
	<
		std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_, bool OutColumnMajor_,
		typename TX_, std::size_t NumColumnsX_, std::size_t NumRowsX_, bool ColumnMajorX_, class Y_, class Z_
	>
	[[nodiscard]] constexpr inline EmuMath::Matrix
	<
		NumColumnsX_,
		NumRowsX_,
		typename EmuMath::Matrix<NumColumnsX_, NumRowsX_, TX_, ColumnMajorX_>::value_type_uq,
		OutColumnMajor_
	>
	matrix_fmadd_range(const EmuMath::Matrix<NumColumnsX_, NumRowsX_, TX_, ColumnMajorX_>& matrix_x_, Y_&& y_, Z_&& z_)
	{
		using x_mat_ref = const EmuMath::Matrix<NumColumnsX_, NumRowsX_, TX_, ColumnMajorX_>&;
		using x_value_uq = typename EmuMath::Matrix<NumColumnsX_, NumRowsX_, TX_, ColumnMajorX_>::value_type_uq;
		return EMU_MATH_MATRIX_MUTATE_COPY_RANGE_TEMPLATE
		(
			EmuCore::do_fmadd, NumColumnsX_, NumRowsX_, x_value_uq, OutColumnMajor_, x_mat_ref, BeginColumn_, EndColumn_, BeginRow_, EndRow_, 0, 0
		)(matrix_x_, matrix_x_, std::forward<Y_>(y_), std::forward<Z_>(z_));
	}
#pragma endregion

#pragma region FMADD_RANGE_MATCHING_COLUMN_MAJOR_OUT
	template
	<
		std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_,
		std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_,
		typename TX_, std::size_t NumColumnsX_, std::size_t NumRowsX_, bool ColumnMajorX_, class Y_, class Z_
	>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, ColumnMajorX_> matrix_fmadd_range
	(
		const EmuMath::Matrix<NumColumnsX_, NumRowsX_, TX_, ColumnMajorX_>& matrix_x_,
		Y_&& y_,
		Z_&& z_
	)
	{
		using x_mat_ref = const EmuMath::Matrix<NumColumnsX_, NumRowsX_, TX_, ColumnMajorX_>&;
		return EMU_MATH_MATRIX_MUTATE_COPY_RANGE_TEMPLATE
		(
			EmuCore::do_fmadd, OutNumColumns_, OutNumRows_, OutT_, ColumnMajorX_, x_mat_ref, BeginColumn_, EndColumn_, BeginRow_, EndRow_, 0, 0
		)(matrix_x_, matrix_x_, std::forward<Y_>(y_), std::forward<Z_>(z_));
	}

	template
	<
		std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_, typename OutT_,
		typename TX_, std::size_t NumColumnsX_, std::size_t NumRowsX_, bool ColumnMajorX_, class Y_, class Z_
	>
	[[nodiscard]] constexpr inline EmuMath::Matrix<NumColumnsX_, NumRowsX_, OutT_, ColumnMajorX_> matrix_fmadd_range
	(
		const EmuMath::Matrix<NumColumnsX_, NumRowsX_, TX_, ColumnMajorX_>& matrix_x_,
		Y_&& y_,
		Z_&& z_
	)
	{
		using x_mat_ref = const EmuMath::Matrix<NumColumnsX_, NumRowsX_, TX_, ColumnMajorX_>&;
		return EMU_MATH_MATRIX_MUTATE_COPY_RANGE_TEMPLATE
		(
			EmuCore::do_fmadd, NumColumnsX_, NumRowsX_, OutT_, ColumnMajorX_, x_mat_ref, BeginColumn_, EndColumn_, BeginRow_, EndRow_, 0, 0
		)(matrix_x_, matrix_x_, std::forward<Y_>(y_), std::forward<Z_>(z_));
	}

	template
	<
		std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_, std::size_t OutNumColumns_, std::size_t OutNumRows_,
		typename TX_, std::size_t NumColumnsX_, std::size_t NumRowsX_, bool ColumnMajorX_, class Y_, class Z_
	>
	[[nodiscard]] constexpr inline EmuMath::Matrix
	<
		OutNumColumns_,
		OutNumRows_,
		typename EmuMath::Matrix<NumColumnsX_, NumRowsX_, TX_, ColumnMajorX_>::value_type_uq,
		ColumnMajorX_
	>
	matrix_fmadd_range(const EmuMath::Matrix<NumColumnsX_, NumRowsX_, TX_, ColumnMajorX_>& matrix_x_, Y_&& y_, Z_&& z_)
	{
		using x_mat_ref = const EmuMath::Matrix<NumColumnsX_, NumRowsX_, TX_, ColumnMajorX_>&;
		using x_value_uq = typename EmuMath::Matrix<NumColumnsX_, NumRowsX_, TX_, ColumnMajorX_>::value_type_uq;
		return EMU_MATH_MATRIX_MUTATE_COPY_RANGE_TEMPLATE
		(
			EmuCore::do_fmadd, OutNumColumns_, OutNumRows_, x_value_uq, ColumnMajorX_, x_mat_ref, BeginColumn_, EndColumn_, BeginRow_, EndRow_, 0, 0
		)(matrix_x_, matrix_x_, std::forward<Y_>(y_), std::forward<Z_>(z_));
	}

	template
	<
		std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_,
		typename TX_, std::size_t NumColumnsX_, std::size_t NumRowsX_, bool ColumnMajorX_, class Y_, class Z_
	>
	[[nodiscard]] constexpr inline EmuMath::Matrix
	<
		NumColumnsX_,
		NumRowsX_,
		typename EmuMath::Matrix<NumColumnsX_, NumRowsX_, TX_, ColumnMajorX_>::value_type_uq,
		ColumnMajorX_
	>
	matrix_fmadd_range(const EmuMath::Matrix<NumColumnsX_, NumRowsX_, TX_, ColumnMajorX_>& matrix_x_, Y_&& y_, Z_&& z_)
	{
		using x_mat_ref = const EmuMath::Matrix<NumColumnsX_, NumRowsX_, TX_, ColumnMajorX_>&;
		using x_value_uq = typename EmuMath::Matrix<NumColumnsX_, NumRowsX_, TX_, ColumnMajorX_>::value_type_uq;
		return EMU_MATH_MATRIX_MUTATE_COPY_RANGE_TEMPLATE
		(
			EmuCore::do_fmadd, NumColumnsX_, NumRowsX_, x_value_uq, ColumnMajorX_, x_mat_ref, BeginColumn_, EndColumn_, BeginRow_, EndRow_, 0, 0
		)(matrix_x_, matrix_x_, std::forward<Y_>(y_), std::forward<Z_>(z_));
	}
#pragma endregion

#pragma region FMADD_RANGE_NO_COPY_CUSTOM_COLUMN_MAJOR_OUT
	/// <summary>
	/// <para>
	///		Outputs the result of a fused multiply-add operation on the provided matrix_x_, using arguments y_ and z_,
	///		with output size/column-major arguments matching those of matrix_x_ if not provided, and value_type_uq for its T_ argument if OutT_ is not provided.
	/// </para>
	/// <para> If Y_ is an EmuMath Matrix: Respective elements in matrix_x_ and y_ will be multiplied. Otherwise, all elements in matrix_x_ will be multiplied by y_. </para>
	/// <para>
	///		If Z_ is an EmuMath Matrix: Intermediate results from each multiplication in specific indices will have the respective indices of z_ added. 
	///		Otherwise, all intermediate multiplication results will have z_ added directly.
	/// </para>
	/// <para> Indices within the provided range will contain results of respective fused multiply-addition operations. </para>
	/// <para> Indices outside of the provided range will be default-constructed. </para>
	/// </summary>
	/// <param name="matrix_x_">: EmuMath Matrix to perform a fused multiply-add on.</param>
	/// <param name="y_">: Scalar or EmuMath Matrix to multiply matrix_x_ by.</param>
	/// <param name="z_">: Scalar or EmuMath Matrix to add to intermediate multiplication results.</param>
	/// <returns>EmuMath Matrix containing the results of fmadd in respective indices within the provided range, and default-constructed elements elsewhere.</returns>
	template
	<
		std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_,
		std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, bool OutColumnMajor_,
		std::size_t NumColumnsX_, std::size_t NumRowsX_, typename TX_, bool ColumnMajorX_, class Y_, class Z_
	>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_> matrix_fmadd_range_no_copy
	(
		const EmuMath::Matrix<NumColumnsX_, NumRowsX_, TX_, ColumnMajorX_>& matrix_x_,
		Y_&& y_,
		Z_&& z_
	)
	{
		return EMU_MATH_MATRIX_MUTATE_TEMPLATE(EmuCore::do_fmadd, OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_, BeginColumn_, EndColumn_, BeginRow_, EndRow_)
		(
			matrix_x_,
			std::forward<Y_>(y_),
			std::forward<Z_>(z_)
		);
	}

	template
	<
		std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_, typename OutT_, bool OutColumnMajor_,
		std::size_t NumColumnsX_, std::size_t NumRowsX_, typename TX_, bool ColumnMajorX_, class Y_, class Z_
	>
	[[nodiscard]] constexpr inline EmuMath::Matrix<NumColumnsX_, NumRowsX_, OutT_, OutColumnMajor_> matrix_fmadd_range_no_copy
	(
		const EmuMath::Matrix<NumColumnsX_, NumRowsX_, TX_, ColumnMajorX_>& matrix_x_,
		Y_&& y_,
		Z_&& z_
	)
	{
		return EMU_MATH_MATRIX_MUTATE_TEMPLATE(EmuCore::do_fmadd, NumColumnsX_, NumRowsX_, OutT_, OutColumnMajor_, BeginColumn_, EndColumn_, BeginRow_, EndRow_)
		(
			matrix_x_,
			std::forward<Y_>(y_),
			std::forward<Z_>(z_)
		);
	}

	template
	<
		std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_, std::size_t OutNumColumns_, std::size_t OutNumRows_, bool OutColumnMajor_,
		std::size_t NumColumnsX_, std::size_t NumRowsX_, typename TX_, bool ColumnMajorX_, class Y_, class Z_
	>
	[[nodiscard]] constexpr inline EmuMath::Matrix
	<
		OutNumColumns_,
		OutNumRows_,
		typename EmuMath::Matrix<NumColumnsX_, NumRowsX_, TX_, ColumnMajorX_>::value_type_uq,
		OutColumnMajor_
	>
	matrix_fmadd_range_no_copy(const EmuMath::Matrix<NumColumnsX_, NumRowsX_, TX_, ColumnMajorX_>& matrix_x_, Y_&& y_, Z_&& z_)
	{
		using x_value_uq = typename EmuMath::Matrix<NumColumnsX_, NumRowsX_, TX_, ColumnMajorX_>::value_type_uq;
		return EMU_MATH_MATRIX_MUTATE_TEMPLATE(EmuCore::do_fmadd, OutNumColumns_, OutNumRows_, x_value_uq, OutColumnMajor_, BeginColumn_, EndColumn_, BeginRow_, EndRow_)
		(
			matrix_x_,
			std::forward<Y_>(y_),
			std::forward<Z_>(z_)
		);
	}

	template
	<
		std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_, bool OutColumnMajor_,
		std::size_t NumColumnsX_, std::size_t NumRowsX_, typename TX_, bool ColumnMajorX_, class Y_, class Z_
	>
	[[nodiscard]] constexpr inline EmuMath::Matrix
	<
		NumColumnsX_,
		NumRowsX_,
		typename EmuMath::Matrix<NumColumnsX_, NumRowsX_, TX_, ColumnMajorX_>::value_type_uq,
		OutColumnMajor_
	>
	matrix_fmadd_range_no_copy(const EmuMath::Matrix<NumColumnsX_, NumRowsX_, TX_, ColumnMajorX_>& matrix_x_, Y_&& y_, Z_&& z_)
	{
		using x_value_uq = typename EmuMath::Matrix<NumColumnsX_, NumRowsX_, TX_, ColumnMajorX_>::value_type_uq;
		return EMU_MATH_MATRIX_MUTATE_TEMPLATE(EmuCore::do_fmadd, NumColumnsX_, NumRowsX_, x_value_uq, OutColumnMajor_, BeginColumn_, EndColumn_, BeginRow_, EndRow_)
		(
			matrix_x_,
			std::forward<Y_>(y_),
			std::forward<Z_>(z_)
		);
	}
#pragma endregion

#pragma region FMADD_RANGE_NO_COPY_MATCHING_COLUMN_MAJOR_OUT
	template
	<
		std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_,
		std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_,
		std::size_t NumColumnsX_, std::size_t NumRowsX_, typename TX_, bool ColumnMajorX_, class Y_, class Z_
	>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, ColumnMajorX_> matrix_fmadd_range_no_copy
	(
		const EmuMath::Matrix<NumColumnsX_, NumRowsX_, TX_, ColumnMajorX_>& matrix_x_,
		Y_&& y_,
		Z_&& z_
	)
	{
		return EMU_MATH_MATRIX_MUTATE_TEMPLATE(EmuCore::do_fmadd, OutNumColumns_, OutNumRows_, OutT_, ColumnMajorX_, BeginColumn_, EndColumn_, BeginRow_, EndRow_)
		(
			matrix_x_,
			std::forward<Y_>(y_),
			std::forward<Z_>(z_)
		);
	}

	template
	<
		std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_, typename OutT_,
		std::size_t NumColumnsX_, std::size_t NumRowsX_, typename TX_, bool ColumnMajorX_, class Y_, class Z_
	>
	[[nodiscard]] constexpr inline EmuMath::Matrix<NumColumnsX_, NumRowsX_, OutT_, ColumnMajorX_> matrix_fmadd_range_no_copy
	(
		const EmuMath::Matrix<NumColumnsX_, NumRowsX_, TX_, ColumnMajorX_>& matrix_x_,
		Y_&& y_,
		Z_&& z_
	)
	{
		return EMU_MATH_MATRIX_MUTATE_TEMPLATE(EmuCore::do_fmadd, NumColumnsX_, NumRowsX_, OutT_, ColumnMajorX_, BeginColumn_, EndColumn_, BeginRow_, EndRow_)
		(
			matrix_x_,
			std::forward<Y_>(y_),
			std::forward<Z_>(z_)
		);
	}

	template
	<
		std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_, std::size_t OutNumColumns_, std::size_t OutNumRows_,
		std::size_t NumColumnsX_, std::size_t NumRowsX_, typename TX_, bool ColumnMajorX_, class Y_, class Z_
	>
	[[nodiscard]] constexpr inline EmuMath::Matrix
	<
		OutNumColumns_,
		OutNumRows_,
		typename EmuMath::Matrix<NumColumnsX_, NumRowsX_, TX_, ColumnMajorX_>::value_type_uq,
		ColumnMajorX_
	>
	matrix_fmadd_range_no_copy(const EmuMath::Matrix<NumColumnsX_, NumRowsX_, TX_, ColumnMajorX_>& matrix_x_, Y_&& y_, Z_&& z_)
	{
		using x_value_uq = typename EmuMath::Matrix<NumColumnsX_, NumRowsX_, TX_, ColumnMajorX_>::value_type_uq;
		return EMU_MATH_MATRIX_MUTATE_TEMPLATE(EmuCore::do_fmadd, OutNumColumns_, OutNumRows_, x_value_uq, ColumnMajorX_, BeginColumn_, EndColumn_, BeginRow_, EndRow_)
		(
			matrix_x_,
			std::forward<Y_>(y_),
			std::forward<Z_>(z_)
		);
	}

	template
	<
		std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_,
		std::size_t NumColumnsX_, std::size_t NumRowsX_, typename TX_, bool ColumnMajorX_, class Y_, class Z_
	>
	[[nodiscard]] constexpr inline EmuMath::Matrix
	<
		NumColumnsX_,
		NumRowsX_,
		typename EmuMath::Matrix<NumColumnsX_, NumRowsX_, TX_, ColumnMajorX_>::value_type_uq,
		ColumnMajorX_
	>
	matrix_fmadd_range_no_copy(const EmuMath::Matrix<NumColumnsX_, NumRowsX_, TX_, ColumnMajorX_>& matrix_x_, Y_&& y_, Z_&& z_)
	{
		using x_value_uq = typename EmuMath::Matrix<NumColumnsX_, NumRowsX_, TX_, ColumnMajorX_>::value_type_uq;
		return EMU_MATH_MATRIX_MUTATE_TEMPLATE(EmuCore::do_fmadd, NumColumnsX_, NumRowsX_, x_value_uq, ColumnMajorX_, BeginColumn_, EndColumn_, BeginRow_, EndRow_)
		(
			matrix_x_,
			std::forward<Y_>(y_),
			std::forward<Z_>(z_)
		);
	}
#pragma endregion

#pragma region FMADD_OUTPUT_ASSIGNED_VARIANTS
	/// <summary>
	/// <para> Outputs the result of a fused multiply-add operation on the provided matrix_x_, using arguments y_ and z_, via the provided out_matrix_. </para>
	/// <para> If Y_ is an EmuMath Matrix: Respective elements in matrix_x_ and y_ will be multiplied. Otherwise, all elements in matrix_x_ will be multiplied by y_. </para>
	/// <para>
	///		If Z_ is an EmuMath Matrix: Intermediate results from each multiplication in specific indices will have the respective indices of z_ added. 
	///		Otherwise, all intermediate multiplication results will have z_ added directly.
	/// </para>
	/// </summary>
	/// <param name="out_matrix_">: EmuMath Matrix to output to.</param>
	/// <param name="matrix_x_">: EmuMath Matrix to perform a fused multiply-add on.</param>
	/// <param name="y_">: Scalar or EmuMath Matrix to multiply matrix_x_ by.</param>
	/// <param name="z_">: Scalar or EmuMath Matrix to add to intermediate multiplication results.</param>
	template
	<
		class Y_, class Z_, typename TX_, std::size_t NumColumnsX_, std::size_t NumRowsX_, bool ColumnMajorX_,
		std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, bool OutColumnMajor_
	>
	constexpr inline void matrix_fmadd
	(
		EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>& out_matrix_,
		const EmuMath::Matrix<NumColumnsX_, NumRowsX_, TX_, ColumnMajorX_>& matrix_x_,
		Y_&& y_,
		Z_&& z_
	)
	{
		using x_mat_ref = const EmuMath::Matrix<NumColumnsX_, NumRowsX_, TX_, ColumnMajorX_>&;
		EMU_MATH_MATRIX_MUTATE_COPY_ASSIGN_TEMPLATE(EmuCore::do_fmadd, x_mat_ref, 0, OutNumColumns_, 0, OutNumRows_, 0, 0)
		(
			out_matrix_,
			matrix_x_,
			matrix_x_,
			std::forward<Y_>(y_),
			std::forward<Z_>(z_)
		);
	}

	/// <summary>
	/// <para> Outputs the result of a fused multiply-add operation on the provided matrix_x_, using arguments y_ and z_, via the provided out_matrix_.</para>
	/// <para> If Y_ is an EmuMath Matrix: Respective elements in matrix_x_ and y_ will be multiplied. Otherwise, all elements in matrix_x_ will be multiplied by y_. </para>
	/// <para>
	///		If Z_ is an EmuMath Matrix: Intermediate results from each multiplication in specific indices will have the respective indices of z_ added. 
	///		Otherwise, all intermediate multiplication results will have z_ added directly.
	/// </para>
	/// <para> Indices within the provided range will contain results of respective fused multiply-addition operations. </para>
	/// <para> Indices outside of the provided range will be copies of the respective indices in matrix_x_. </para>
	/// </summary>
	/// <param name="out_matrix_">: EmuMath Matrix to output to.</param>
	/// <param name="matrix_x_">: EmuMath Matrix to perform a fused multiply-add on.</param>
	/// <param name="y_">: Scalar or EmuMath Matrix to multiply matrix_x_ by.</param>
	/// <param name="z_">: Scalar or EmuMath Matrix to add to intermediate multiplication results.</param>
	template
	<
		std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_,
		class Y_, class Z_, typename TX_, std::size_t NumColumnsX_, std::size_t NumRowsX_, bool ColumnMajorX_,
		std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, bool OutColumnMajor_
	>
	constexpr inline void matrix_fmadd_range
	(
		EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>& out_matrix_,
		const EmuMath::Matrix<NumColumnsX_, NumRowsX_, TX_, ColumnMajorX_>& matrix_x_,
		Y_&& y_,
		Z_&& z_
	)
	{
		using x_mat_ref = const EmuMath::Matrix<NumColumnsX_, NumRowsX_, TX_, ColumnMajorX_>&;
		EMU_MATH_MATRIX_MUTATE_COPY_ASSIGN_RANGE_TEMPLATE(EmuCore::do_fmadd, x_mat_ref, BeginColumn_, EndColumn_, BeginRow_, EndRow_, 0, 0)
		(
			out_matrix_,
			matrix_x_,
			matrix_x_,
			std::forward<Y_>(y_),
			std::forward<Z_>(z_)
		);
	}

	/// <summary>
	/// <para> Outputs the result of a fused multiply-add operation on the provided matrix_x_, using arguments y_ and z_, via the provided out_matrix_. </para>
	/// <para> If Y_ is an EmuMath Matrix: Respective elements in matrix_x_ and y_ will be multiplied. Otherwise, all elements in matrix_x_ will be multiplied by y_. </para>
	/// <para>
	///		If Z_ is an EmuMath Matrix: Intermediate results from each multiplication in specific indices will have the respective indices of z_ added. 
	///		Otherwise, all intermediate multiplication results will have z_ added directly.
	/// </para>
	/// <para> Indices within the provided range will contain results of respective fused multiply-addition operations. </para>
	/// <para> Indices outside of the provided range will not be modified. </para>
	/// </summary>
	/// <param name="out_matrix_">: EmuMath Matrix to output to.</param>
	/// <param name="matrix_x_">: EmuMath Matrix to perform a fused multiply-add on.</param>
	/// <param name="y_">: Scalar or EmuMath Matrix to multiply matrix_x_ by.</param>
	/// <param name="z_">: Scalar or EmuMath Matrix to add to intermediate multiplication results.</param>
	template
	<
		std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_,
		class Y_, class Z_, typename TX_, std::size_t NumColumnsX_, std::size_t NumRowsX_, bool ColumnMajorX_,
		std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, bool OutColumnMajor_
	>
	constexpr inline void matrix_fmadd_range_no_copy
	(
		EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>& out_matrix_,
		const EmuMath::Matrix<NumColumnsX_, NumRowsX_, TX_, ColumnMajorX_>& matrix_x_,
		Y_&& y_,
		Z_&& z_
	)
	{
		EMU_MATH_MATRIX_MUTATE_ASSIGN_TEMPLATE(EmuCore::do_fmadd, BeginColumn_, EndColumn_, BeginRow_, EndRow_, 0, 0)
		(
			out_matrix_,
			matrix_x_,
			std::forward<Y_>(y_),
			std::forward<Z_>(z_)
		);
	}
#pragma endregion
}

#endif
