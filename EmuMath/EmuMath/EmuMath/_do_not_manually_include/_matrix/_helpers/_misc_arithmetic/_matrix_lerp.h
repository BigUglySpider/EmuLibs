#ifndef EMU_MATH_MATRIX_MISC_ARITHMETIC_LERP_H_INC_
#define EMU_MATH_MATRIX_MISC_ARITHMETIC_LERP_H_INC_ 1

#include "../_common_matrix_helper_includes.h"

// CONTAINS
// --- lerp
// --- lerp_range
// --- lerp_range_no_copy

namespace EmuMath::Helpers
{
#pragma region LERP_CUSTOM_MAJOR_OUT
	/// <summary>
	/// <para> Outputs a version of the input EmuMath Matrix with its elements linearly interpolated with b_ using a weighting of t_. </para>
	/// <para> If B_ is an EmuMath Matrix: Elements in matrix_a_ will be interpolated with respective elements of b_. Otherwise, all will be interpolated with b_ directly. </para>
	/// <para> If T_ is an EmuMath Matrix: Linear interpolations will use respective elements in t_ as weightings. Otherwise, all interpolations will use t_ directly. </para>
	/// </summary>
	/// <param name="matrix_a_">: EmuMath Matrix to use as the starting point for linear interpolation.</param>
	/// <param name="b_">: Scalar or EmuMath Matrix to use as the target point for linear interpolation.</param>
	/// <param name="t_">: Scalar or EmuMath Matrix to use as weighting for linear interpolations, where lerp(a, b, 0) = a, lerp(a, b, 1) = b.</param>
	/// <returns>Copy of the passed EmuMath Matrix with its elements linearly interpolated, summarised as `out = a + ((b - a) * t)`.</returns>
	template
	<
		std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, bool OutColumnMajor_,
		class B_, class T_, typename TA_, std::size_t NumColumnsA_, std::size_t NumRowsA_, bool ColumnMajorA_
	>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_> matrix_lerp
	(
		const EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>& matrix_a_,
		B_&& b_,
		T_&& t_
	)
	{
		using a_ref = const EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>&;
		return EMU_MATH_MATRIX_MUTATE_COPY_TEMPLATE(EmuCore::do_lerp, OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_, a_ref, 0, 0)
		(
			matrix_a_,
			matrix_a_,
			std::forward<B_>(b_),
			std::forward<T_>(t_)
		);
	}

	template<typename OutT_, bool OutColumnMajor_, class B_, class T_, typename TA_, std::size_t NumColumnsA_, std::size_t NumRowsA_, bool ColumnMajorA_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<NumColumnsA_, NumRowsA_, OutT_, OutColumnMajor_> matrix_lerp
	(
		const EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>& matrix_a_,
		B_&& b_,
		T_&& t_
	)
	{
		using a_ref = const EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>&;
		return EMU_MATH_MATRIX_MUTATE_COPY_TEMPLATE(EmuCore::do_lerp, NumColumnsA_, NumRowsA_, OutT_, OutColumnMajor_, a_ref, 0, 0)
		(
			matrix_a_,
			matrix_a_,
			std::forward<B_>(b_),
			std::forward<T_>(t_)
		);
	}

	template
	<
		std::size_t OutNumColumns_, std::size_t OutNumRows_, bool OutColumnMajor_,
		class B_, class T_, typename TA_, std::size_t NumColumnsA_, std::size_t NumRowsA_, bool ColumnMajorA_
	>
	[[nodiscard]] constexpr inline EmuMath::Matrix
	<
		OutNumColumns_,
		OutNumRows_,
		typename EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>::preferred_floating_point,
		OutColumnMajor_
	>
	matrix_lerp(const EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>& matrix_a_, B_&& b_, T_&& t_)
	{
		using a_ref = const EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>&;
		using a_fp = typename EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>::preferred_floating_point;
		return EMU_MATH_MATRIX_MUTATE_COPY_TEMPLATE(EmuCore::do_lerp, OutNumColumns_, OutNumRows_, a_fp, OutColumnMajor_, a_ref, 0, 0)
		(
			matrix_a_,
			matrix_a_,
			std::forward<B_>(b_),
			std::forward<T_>(t_)
		);
	}

	template
	<
		bool OutColumnMajor_,
		class B_, class T_, typename TA_, std::size_t NumColumnsA_, std::size_t NumRowsA_, bool ColumnMajorA_
	>
	[[nodiscard]] constexpr inline EmuMath::Matrix
	<
		NumColumnsA_,
		NumRowsA_,
		typename EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>::preferred_floating_point,
		OutColumnMajor_
	>
	matrix_lerp(const EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>& matrix_a_, B_&& b_, T_&& t_)
	{
		using a_ref = const EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>&;
		using a_fp = typename EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>::preferred_floating_point;
		return EMU_MATH_MATRIX_MUTATE_COPY_TEMPLATE(EmuCore::do_lerp, NumColumnsA_, NumRowsA_, a_fp, OutColumnMajor_, a_ref, 0, 0)
		(
			matrix_a_,
			matrix_a_,
			std::forward<B_>(b_),
			std::forward<T_>(t_)
		);
	}
#pragma endregion

#pragma region LERP_MATCHING_MAJOR_OUT
	template
	<
		std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_,
		class B_, class T_, typename TA_, std::size_t NumColumnsA_, std::size_t NumRowsA_, bool ColumnMajorA_
	>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, ColumnMajorA_> matrix_lerp
	(
		const EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>& matrix_a_,
		B_&& b_,
		T_&& t_
	)
	{
		using a_ref = const EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>&;
		return EMU_MATH_MATRIX_MUTATE_COPY_TEMPLATE(EmuCore::do_lerp, OutNumColumns_, OutNumRows_, OutT_, ColumnMajorA_, a_ref, 0, 0)
		(
			matrix_a_,
			matrix_a_,
			std::forward<B_>(b_),
			std::forward<T_>(t_)
		);
	}

	template<typename OutT_, class B_, class T_, typename TA_, std::size_t NumColumnsA_, std::size_t NumRowsA_, bool ColumnMajorA_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<NumColumnsA_, NumRowsA_, OutT_, ColumnMajorA_> matrix_lerp
	(
		const EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>& matrix_a_,
		B_&& b_,
		T_&& t_
	)
	{
		using a_ref = const EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>&;
		return EMU_MATH_MATRIX_MUTATE_COPY_TEMPLATE(EmuCore::do_lerp, NumColumnsA_, NumRowsA_, OutT_, ColumnMajorA_, a_ref, 0, 0)
		(
			matrix_a_,
			matrix_a_,
			std::forward<B_>(b_),
			std::forward<T_>(t_)
		);
	}

	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, class B_, class T_, typename TA_, std::size_t NumColumnsA_, std::size_t NumRowsA_, bool ColumnMajorA_>
	[[nodiscard]] constexpr inline EmuMath::Matrix
	<
		OutNumColumns_,
		OutNumRows_,
		typename EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>::preferred_floating_point,
		ColumnMajorA_
	>
	matrix_lerp(const EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>& matrix_a_, B_&& b_, T_&& t_)
	{
		using a_ref = const EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>&;
		using a_fp = typename EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>::preferred_floating_point;
		return EMU_MATH_MATRIX_MUTATE_COPY_TEMPLATE(EmuCore::do_lerp, OutNumColumns_, OutNumRows_, a_fp, ColumnMajorA_, a_ref, 0, 0)
		(
			matrix_a_,
			matrix_a_,
			std::forward<B_>(b_),
			std::forward<T_>(t_)
		);
	}

	template<class B_, class T_, typename TA_, std::size_t NumColumnsA_, std::size_t NumRowsA_, bool ColumnMajorA_>
	[[nodiscard]] constexpr inline EmuMath::Matrix
	<
		NumColumnsA_,
		NumRowsA_,
		typename EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>::preferred_floating_point,
		ColumnMajorA_
	>
	matrix_lerp(const EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>& matrix_a_, B_&& b_, T_&& t_)
	{
		using a_ref = const EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>&;
		using a_fp = typename EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>::preferred_floating_point;
		return EMU_MATH_MATRIX_MUTATE_COPY_TEMPLATE(EmuCore::do_lerp, NumColumnsA_, NumRowsA_, a_fp, ColumnMajorA_, a_ref, 0, 0)
		(
			matrix_a_,
			matrix_a_,
			std::forward<B_>(b_),
			std::forward<T_>(t_)
		);
	}
#pragma endregion

#pragma region LERP_RANGE_CUSTOM_MAJOR_OUT
	/// <summary>
	/// <para> Outputs a version of the input EmuMath Matrix with its elements linearly interpolated with b_ using a weighting of t_. </para>
	/// <para> If B_ is an EmuMath Matrix: Elements in matrix_a_ will be interpolated with respective elements of b_. Otherwise, all will be interpolated with b_ directly. </para>
	/// <para> If T_ is an EmuMath Matrix: Linear interpolations will use respective elements in t_ as weightings. Otherwise, all interpolations will use t_ directly. </para>
	/// <para> Indices within the provided range will contain respective linear interpolation results. </para>
	/// <para> Indices outside of the provided range will be copies of respective indices in matrix_a_. </para>
	/// </summary>
	/// <param name="matrix_a_">: EmuMath Matrix to use as the starting point for linear interpolation.</param>
	/// <param name="b_">: Scalar or EmuMath Matrix to use as the target point for linear interpolation.</param>
	/// <param name="t_">: Scalar or EmuMath Matrix to use as weighting for linear interpolations, where lerp(a, b, 0) = a, lerp(a, b, 1) = b.</param>
	/// <returns>Copy of the matrix_a_ with elements in the provided range linearly interpolated, summarised as `out = a + ((b - a) * t)`, and copied elements elsewhere.</returns>
	template
	<
		std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_,
		std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, bool OutColumnMajor_,
		class B_, class T_, typename TA_, std::size_t NumColumnsA_, std::size_t NumRowsA_, bool ColumnMajorA_
	>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_> matrix_lerp_range
	(
		const EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>& matrix_a_,
		B_&& b_,
		T_&& t_
	)
	{
		using a_ref = const EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>&;
		return EMU_MATH_MATRIX_MUTATE_COPY_RANGE_TEMPLATE
		(
			EmuCore::do_lerp, OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_, a_ref, BeginColumn_, EndColumn_, BeginRow_, EndRow_, 0, 0
		)(matrix_a_, matrix_a_, std::forward<B_>(b_), std::forward<T_>(t_));
	}

	template
	<
		std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_,
		typename OutT_, bool OutColumnMajor_, class B_, class T_, typename TA_, std::size_t NumColumnsA_, std::size_t NumRowsA_, bool ColumnMajorA_
	>
	[[nodiscard]] constexpr inline EmuMath::Matrix<NumColumnsA_, NumRowsA_, OutT_, OutColumnMajor_> matrix_lerp_range
	(
		const EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>& matrix_a_,
		B_&& b_,
		T_&& t_
	)
	{
		using a_ref = const EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>&;
		return EMU_MATH_MATRIX_MUTATE_COPY_RANGE_TEMPLATE
		(
			EmuCore::do_lerp, NumColumnsA_, NumRowsA_, OutT_, OutColumnMajor_, a_ref, BeginColumn_, EndColumn_, BeginRow_, EndRow_, 0, 0
		)(matrix_a_, matrix_a_, std::forward<B_>(b_), std::forward<T_>(t_));
	}

	template
	<
		std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_,
		std::size_t OutNumColumns_, std::size_t OutNumRows_, bool OutColumnMajor_,
		class B_, class T_, typename TA_, std::size_t NumColumnsA_, std::size_t NumRowsA_, bool ColumnMajorA_
	>
	[[nodiscard]] constexpr inline EmuMath::Matrix
	<
		OutNumColumns_,
		OutNumRows_,
		typename EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>::preferred_floating_point,
		OutColumnMajor_
	> matrix_lerp_range
	(
		const EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>& matrix_a_,
		B_&& b_,
		T_&& t_
	)
	{
		using a_ref = const EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>&;
		using a_fp = typename EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>::preferred_floating_point;
		return EMU_MATH_MATRIX_MUTATE_COPY_RANGE_TEMPLATE
		(
			EmuCore::do_lerp, OutNumColumns_, OutNumRows_, a_fp, OutColumnMajor_, a_ref, BeginColumn_, EndColumn_, BeginRow_, EndRow_, 0, 0
		)(matrix_a_, matrix_a_, std::forward<B_>(b_), std::forward<T_>(t_));
	}

	template
	<
		std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_,
		bool OutColumnMajor_, class B_, class T_, typename TA_, std::size_t NumColumnsA_, std::size_t NumRowsA_, bool ColumnMajorA_
	>
	[[nodiscard]] constexpr inline EmuMath::Matrix
	<
		NumColumnsA_,
		NumRowsA_,
		typename EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>::preferred_floating_point,
		OutColumnMajor_
	> matrix_lerp_range
	(
		const EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>& matrix_a_,
		B_&& b_,
		T_&& t_
	)
	{
		using a_ref = const EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>&;
		using a_fp = typename EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>::preferred_floating_point;
		return EMU_MATH_MATRIX_MUTATE_COPY_RANGE_TEMPLATE
		(
			EmuCore::do_lerp, NumColumnsA_, NumRowsA_, a_fp, OutColumnMajor_, a_ref, BeginColumn_, EndColumn_, BeginRow_, EndRow_, 0, 0
		)(matrix_a_, matrix_a_, std::forward<B_>(b_), std::forward<T_>(t_));
	}
#pragma endregion

#pragma region LERP_RANGE_MATCHING_MAJOR_OUT
	template
	<
		std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_,
		std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_,
		class B_, class T_, typename TA_, std::size_t NumColumnsA_, std::size_t NumRowsA_, bool ColumnMajorA_
	>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, ColumnMajorA_> matrix_lerp_range
	(
		const EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>& matrix_a_,
		B_&& b_,
		T_&& t_
	)
	{
		using a_ref = const EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>&;
		return EMU_MATH_MATRIX_MUTATE_COPY_RANGE_TEMPLATE
		(
			EmuCore::do_lerp, OutNumColumns_, OutNumRows_, OutT_, ColumnMajorA_, a_ref, BeginColumn_, EndColumn_, BeginRow_, EndRow_, 0, 0
		)(matrix_a_, matrix_a_, std::forward<B_>(b_), std::forward<T_>(t_));
	}

	template
	<
		std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_,
		typename OutT_, class B_, class T_, typename TA_, std::size_t NumColumnsA_, std::size_t NumRowsA_, bool ColumnMajorA_
	>
	[[nodiscard]] constexpr inline EmuMath::Matrix<NumColumnsA_, NumRowsA_, OutT_, ColumnMajorA_> matrix_lerp_range
	(
		const EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>& matrix_a_,
		B_&& b_,
		T_&& t_
	)
	{
		using a_ref = const EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>&;
		return EMU_MATH_MATRIX_MUTATE_COPY_RANGE_TEMPLATE
		(
			EmuCore::do_lerp, NumColumnsA_, NumRowsA_, OutT_, ColumnMajorA_, a_ref, BeginColumn_, EndColumn_, BeginRow_, EndRow_, 0, 0
		)(matrix_a_, matrix_a_, std::forward<B_>(b_), std::forward<T_>(t_));
	}

	template
	<
		std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_,
		std::size_t OutNumColumns_, std::size_t OutNumRows_,
		class B_, class T_, typename TA_, std::size_t NumColumnsA_, std::size_t NumRowsA_, bool ColumnMajorA_
	>
	[[nodiscard]] constexpr inline EmuMath::Matrix
	<
		OutNumColumns_,
		OutNumRows_,
		typename EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>::preferred_floating_point,
		ColumnMajorA_
	>
	matrix_lerp_range
	(
		const EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>& matrix_a_,
		B_&& b_,
		T_&& t_
	)
	{
		using a_ref = const EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>&;
		using a_fp = typename EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>::preferred_floating_point;
		return EMU_MATH_MATRIX_MUTATE_COPY_RANGE_TEMPLATE
		(
			EmuCore::do_lerp, OutNumColumns_, OutNumRows_, a_fp, ColumnMajorA_, a_ref, BeginColumn_, EndColumn_, BeginRow_, EndRow_, 0, 0
		)(matrix_a_, matrix_a_, std::forward<B_>(b_), std::forward<T_>(t_));
	}

	template
	<
		std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_,
		class B_, class T_, typename TA_, std::size_t NumColumnsA_, std::size_t NumRowsA_, bool ColumnMajorA_
	>
	[[nodiscard]] constexpr inline EmuMath::Matrix
	<
		NumColumnsA_,
		NumRowsA_,
		typename EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>::preferred_floating_point,
		ColumnMajorA_
	>
	matrix_lerp_range
	(
		const EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>& matrix_a_,
		B_&& b_,
		T_&& t_
	)
	{
		using a_ref = const EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>&;
		using a_fp = typename EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>::preferred_floating_point;
		return EMU_MATH_MATRIX_MUTATE_COPY_RANGE_TEMPLATE
		(
			EmuCore::do_lerp, NumColumnsA_, NumRowsA_, a_fp, ColumnMajorA_, a_ref, BeginColumn_, EndColumn_, BeginRow_, EndRow_, 0, 0
		)(matrix_a_, matrix_a_, std::forward<B_>(b_), std::forward<T_>(t_));
	}
#pragma endregion

#pragma region LERP_RANGE_NO_COPY_CUSTOM_MAJOR_OUT
	/// <summary>
	/// <para> Outputs a version of the input EmuMath Matrix with its elements linearly interpolated with b_ using a weighting of t_. </para>
	/// <para> If B_ is an EmuMath Matrix: Elements in matrix_a_ will be interpolated with respective elements of b_. Otherwise, all will be interpolated with b_ directly. </para>
	/// <para> If T_ is an EmuMath Matrix: Linear interpolations will use respective elements in t_ as weightings. Otherwise, all interpolations will use t_ directly. </para>
	/// <para> Indices within the provided range will contain respective linear interpolation results. </para>
	/// <para> Indices outside of the provided range will be defaulted. </para>
	/// </summary>
	/// <param name="matrix_a_">: EmuMath Matrix to use as the starting point for linear interpolation.</param>
	/// <param name="b_">: Scalar or EmuMath Matrix to use as the target point for linear interpolation.</param>
	/// <param name="t_">: Scalar or EmuMath Matrix to use as weighting for linear interpolations, where lerp(a, b, 0) = a, lerp(a, b, 1) = b.</param>
	/// <returns>Copy of the matrix_a_ with elements in the provided range linearly interpolated, summarised as `out = a + ((b - a) * t)`, and default elements elsewhere.</returns>
	template
	<
		std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_,
		std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, bool OutColumnMajor_,
		class B_, class T_, typename TA_, std::size_t NumColumnsA_, std::size_t NumRowsA_, bool ColumnMajorA_
	>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_> matrix_lerp_range_no_copy
	(
		const EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>& matrix_a_,
		B_&& b_,
		T_&& t_
	)
	{
		using a_ref = const EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>&;
		return EMU_MATH_MATRIX_MUTATE_TEMPLATE(EmuCore::do_lerp, OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_, BeginColumn_, EndColumn_, BeginRow_, EndRow_)
		(
			matrix_a_,
			std::forward<B_>(b_),
			std::forward<T_>(t_)
		);
	}

	template
	<
		std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_,
		typename OutT_, bool OutColumnMajor_, class B_, class T_, typename TA_, std::size_t NumColumnsA_, std::size_t NumRowsA_, bool ColumnMajorA_
	>
	[[nodiscard]] constexpr inline EmuMath::Matrix<NumColumnsA_, NumRowsA_, OutT_, OutColumnMajor_> matrix_lerp_range_no_copy
	(
		const EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>& matrix_a_,
		B_&& b_,
		T_&& t_
	)
	{
		using a_ref = const EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>&;
		return EMU_MATH_MATRIX_MUTATE_TEMPLATE(EmuCore::do_lerp, NumColumnsA_, NumRowsA_, OutT_, OutColumnMajor_, BeginColumn_, EndColumn_, BeginRow_, EndRow_)
		(
			matrix_a_,
			std::forward<B_>(b_),
			std::forward<T_>(t_)
		);
	}

	template
	<
		std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_,
		std::size_t OutNumColumns_, std::size_t OutNumRows_, bool OutColumnMajor_,
		class B_, class T_, typename TA_, std::size_t NumColumnsA_, std::size_t NumRowsA_, bool ColumnMajorA_
	>
	[[nodiscard]] constexpr inline EmuMath::Matrix
	<
		OutNumColumns_,
		OutNumRows_,
		typename EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>::preferred_floating_point,
		OutColumnMajor_
	> matrix_lerp_range_no_copy
	(
		const EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>& matrix_a_,
		B_&& b_,
		T_&& t_
	)
	{
		using a_ref = const EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>&;
		using a_fp = typename EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>::preferred_floating_point;
		return EMU_MATH_MATRIX_MUTATE_TEMPLATE(EmuCore::do_lerp, OutNumColumns_, OutNumRows_, a_fp, OutColumnMajor_, BeginColumn_, EndColumn_, BeginRow_, EndRow_)
		(
			matrix_a_,
			std::forward<B_>(b_),
			std::forward<T_>(t_)
		);
	}

	template
	<
		std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_,
		bool OutColumnMajor_, class B_, class T_, typename TA_, std::size_t NumColumnsA_, std::size_t NumRowsA_, bool ColumnMajorA_
	>
	[[nodiscard]] constexpr inline EmuMath::Matrix
	<
		NumColumnsA_,
		NumRowsA_,
		typename EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>::preferred_floating_point,
		OutColumnMajor_
	> matrix_lerp_range_no_copy
	(
		const EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>& matrix_a_,
		B_&& b_,
		T_&& t_
	)
	{
		using a_ref = const EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>&;
		using a_fp = typename EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>::preferred_floating_point;
		return EMU_MATH_MATRIX_MUTATE_TEMPLATE(EmuCore::do_lerp, NumColumnsA_, NumRowsA_, a_fp, OutColumnMajor_, BeginColumn_, EndColumn_, BeginRow_, EndRow_)
		(
			matrix_a_,
			std::forward<B_>(b_),
			std::forward<T_>(t_)
		);
	}
#pragma endregion

#pragma region LERP_RANGE_NO_COPY_MATCHING_MAJOR_OUT
	template
	<
		std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_,
		std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, class B_, class T_, typename TA_, std::size_t NumColumnsA_, std::size_t NumRowsA_, bool ColumnMajorA_
	>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, ColumnMajorA_> matrix_lerp_range_no_copy
	(
		const EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>& matrix_a_,
		B_&& b_,
		T_&& t_
	)
	{
		using a_ref = const EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>&;
		return EMU_MATH_MATRIX_MUTATE_TEMPLATE(EmuCore::do_lerp, OutNumColumns_, OutNumRows_, OutT_, ColumnMajorA_, BeginColumn_, EndColumn_, BeginRow_, EndRow_)
		(
			matrix_a_,
			std::forward<B_>(b_),
			std::forward<T_>(t_)
		);
	}

	template
	<
		std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_,
		typename OutT_, class B_, class T_, typename TA_, std::size_t NumColumnsA_, std::size_t NumRowsA_, bool ColumnMajorA_
	>
	[[nodiscard]] constexpr inline EmuMath::Matrix<NumColumnsA_, NumRowsA_, OutT_, ColumnMajorA_> matrix_lerp_range_no_copy
	(
		const EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>& matrix_a_,
		B_&& b_,
		T_&& t_
	)
	{
		using a_ref = const EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>&;
		return EMU_MATH_MATRIX_MUTATE_TEMPLATE(EmuCore::do_lerp, NumColumnsA_, NumRowsA_, OutT_, ColumnMajorA_, BeginColumn_, EndColumn_, BeginRow_, EndRow_)
		(
			matrix_a_,
			std::forward<B_>(b_),
			std::forward<T_>(t_)
		);
	}

	template
	<
		std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_,
		std::size_t OutNumColumns_, std::size_t OutNumRows_, class B_, class T_, typename TA_, std::size_t NumColumnsA_, std::size_t NumRowsA_, bool ColumnMajorA_
	>
	[[nodiscard]] constexpr inline EmuMath::Matrix
	<
		OutNumColumns_,
		OutNumRows_,
		typename EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>::preferred_floating_point,
		ColumnMajorA_
	>
	matrix_lerp_range_no_copy
	(
		const EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>& matrix_a_,
		B_&& b_,
		T_&& t_
	)
	{
		using a_ref = const EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>&;
		using a_fp = typename EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>::preferred_floating_point;
		return EMU_MATH_MATRIX_MUTATE_TEMPLATE(EmuCore::do_lerp, OutNumColumns_, OutNumRows_, a_fp, ColumnMajorA_, BeginColumn_, EndColumn_, BeginRow_, EndRow_)
		(
			matrix_a_,
			std::forward<B_>(b_),
			std::forward<T_>(t_)
		);
	}

	template
	<
		std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_,
		class B_, class T_, typename TA_, std::size_t NumColumnsA_, std::size_t NumRowsA_, bool ColumnMajorA_
	>
	[[nodiscard]] constexpr inline EmuMath::Matrix
	<
		NumColumnsA_,
		NumRowsA_,
		typename EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>::preferred_floating_point,
		ColumnMajorA_
	>
	matrix_lerp_range_no_copy
	(
		const EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>& matrix_a_,
		B_&& b_,
		T_&& t_
	)
	{
		using a_ref = const EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>&;
		using a_fp = typename EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>::preferred_floating_point;
		return EMU_MATH_MATRIX_MUTATE_TEMPLATE(EmuCore::do_lerp, NumColumnsA_, NumRowsA_, a_fp, ColumnMajorA_, BeginColumn_, EndColumn_, BeginRow_, EndRow_)
		(
			matrix_a_,
			std::forward<B_>(b_),
			std::forward<T_>(t_)
		);
	}
#pragma endregion

#pragma region LERP_OUTPUT_ASSIGNED_VARIANTS
	/// <summary>
	/// <para> Outputs a version of the input EmuMath Matrix with its elements linearly interpolated with b_ using a weighting of t_, via the provided out_matrix_. </para>
	/// <para> If B_ is an EmuMath Matrix: Elements in matrix_a_ will be interpolated with respective elements of b_. Otherwise, all will be interpolated with b_ directly. </para>
	/// <para> If T_ is an EmuMath Matrix: Linear interpolations will use respective elements in t_ as weightings. Otherwise, all interpolations will use t_ directly. </para>
	/// </summary>
	/// <param name="out_matrix_">: EmuMath Matrix to output to.</param>
	/// <param name="matrix_a_">: EmuMath Matrix to use as the starting point for linear interpolation.</param>
	/// <param name="b_">: Scalar or EmuMath Matrix to use as the target point for linear interpolation.</param>
	/// <param name="t_">: Scalar or EmuMath Matrix to use as weighting for linear interpolations, where lerp(a, b, 0) = a, lerp(a, b, 1) = b.</param>
	template
	<
		std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, bool OutColumnMajor_,
		class B_, class T_, typename TA_, std::size_t NumColumnsA_, std::size_t NumRowsA_, bool ColumnMajorA_
	>
	constexpr inline void matrix_lerp
	(
		EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>& out_matrix_,
		const EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>& matrix_a_,
		B_&& b_,
		T_&& t_
	)
	{
		using a_ref = const EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>&;
		EMU_MATH_MATRIX_MUTATE_COPY_ASSIGN_TEMPLATE(EmuCore::do_lerp, a_ref, 0, OutNumColumns_, 0, OutNumRows_, 0, 0)
		(
			out_matrix_,
			matrix_a_,
			matrix_a_,
			std::forward<B_>(b_),
			std::forward<T_>(t_)
		);
	}

	/// <summary>
	/// <para> Outputs a version of the input EmuMath Matrix with its elements linearly interpolated with b_ using a weighting of t_, via the provided out_matrix_. </para>
	/// <para> If B_ is an EmuMath Matrix: Elements in matrix_a_ will be interpolated with respective elements of b_. Otherwise, all will be interpolated with b_ directly. </para>
	/// <para> If T_ is an EmuMath Matrix: Linear interpolations will use respective elements in t_ as weightings. Otherwise, all interpolations will use t_ directly. </para>
	/// <para> Indices within the provided range will contain respective linear interpolation results. </para>
	/// <para> Indices outside of the provided range will be copies of respective indices in matrix_a_. </para>
	/// </summary>
	/// <param name="out_matrix_">: EmuMath Matrix to output to.</param>
	/// <param name="matrix_a_">: EmuMath Matrix to use as the starting point for linear interpolation.</param>
	/// <param name="b_">: Scalar or EmuMath Matrix to use as the target point for linear interpolation.</param>
	/// <param name="t_">: Scalar or EmuMath Matrix to use as weighting for linear interpolations, where lerp(a, b, 0) = a, lerp(a, b, 1) = b.</param>
	template
	<
		std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_,
		std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, bool OutColumnMajor_,
		class B_, class T_, typename TA_, std::size_t NumColumnsA_, std::size_t NumRowsA_, bool ColumnMajorA_
	>
	constexpr inline void matrix_lerp_range
	(
		EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>& out_matrix_,
		const EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>& matrix_a_,
		B_&& b_,
		T_&& t_
	)
	{
		using a_ref = const EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>&;
		EMU_MATH_MATRIX_MUTATE_COPY_ASSIGN_RANGE_TEMPLATE(EmuCore::do_lerp, a_ref, BeginColumn_, EndColumn_, BeginRow_, EndRow_, 0, 0)
		(
			out_matrix_,
			matrix_a_,
			matrix_a_,
			std::forward<B_>(b_),
			std::forward<T_>(t_)
		);
	}

	/// <summary>
	/// <para> Outputs a version of the input EmuMath Matrix with its elements linearly interpolated with b_ using a weighting of t_, via the provided out_matrix_. </para>
	/// <para> If B_ is an EmuMath Matrix: Elements in matrix_a_ will be interpolated with respective elements of b_. Otherwise, all will be interpolated with b_ directly. </para>
	/// <para> If T_ is an EmuMath Matrix: Linear interpolations will use respective elements in t_ as weightings. Otherwise, all interpolations will use t_ directly. </para>
	/// <para> Indices within the provided range will contain respective linear interpolation results. </para>
	/// <para> Indices outside of the provided range will not be modified. </para>
	/// </summary>
	/// <param name="out_matrix_">: EmuMath Matrix to output to.</param>
	/// <param name="matrix_a_">: EmuMath Matrix to use as the starting point for linear interpolation.</param>
	/// <param name="b_">: Scalar or EmuMath Matrix to use as the target point for linear interpolation.</param>
	/// <param name="t_">: Scalar or EmuMath Matrix to use as weighting for linear interpolations, where lerp(a, b, 0) = a, lerp(a, b, 1) = b.</param>
	template
	<
		std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_,
		std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, bool OutColumnMajor_,
		class B_, class T_, typename TA_, std::size_t NumColumnsA_, std::size_t NumRowsA_, bool ColumnMajorA_
	>
	[[nodiscard]] constexpr inline void matrix_lerp_range_no_copy
	(
		EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>& out_matrix_,
		const EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>& matrix_a_,
		B_&& b_,
		T_&& t_
	)
	{
		EMU_MATH_MATRIX_MUTATE_ASSIGN_TEMPLATE(EmuCore::do_lerp, BeginColumn_, EndColumn_, BeginRow_, EndRow_, 0, 0)
		(
			out_matrix_,
			matrix_a_,
			std::forward<B_>(b_),
			std::forward<T_>(t_)
		);
	}
#pragma endregion
}

#endif
