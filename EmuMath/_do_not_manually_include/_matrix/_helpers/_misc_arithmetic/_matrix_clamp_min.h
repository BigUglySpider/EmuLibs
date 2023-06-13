#ifndef EMU_MATH_MATRIX_MISC_ARITHMETIC_CLAMP_MIN_H_INC_
#define EMU_MATH_MATRIX_MISC_ARITHMETIC_CLAMP_MIN_H_INC_ 1

#include "../_common_matrix_helper_includes.h"

// CONTAINS
// --- clamp_min
// --- clamp_min_range
// --- clamp_range_no_copy

namespace EmuMath::Helpers
{
#pragma region CLAMP_MIN_CUSTOM_MAJOR_OUT
	/// <summary>
	/// <para> Outputs a version of the input EmuMath Matrix with its elements clamped to a minimum value indicated by Min_. </para>
	/// <para> If Min_ is an EmuMath Matrix: Elements will be clamped to a minimum of the respective element of min_. Otherwise, all will be clamped to min_ directly. </para>
	/// </summary>
	/// <param name="matrix_a_">: EmuMath Matrix to clamp.</param>
	/// <param name="min_">: Scalar or EmuMath Matrix to use as the minimum to clamp the `matrix_a_`'s values to.</param>
	/// <returns>Copy of the passed EmuMath Matrix with its elements clamped to the provided minimum.</returns>
	template
	<
		std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, bool OutColumnMajor_,
		class Min_, typename TA_, std::size_t NumColumnsA_, std::size_t NumRowsA_, bool ColumnMajorA_
	>
	[[nodiscard]] constexpr inline auto matrix_clamp_min(const EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>& matrix_a_, Min_&& min_)
		-> EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>
	{
		using a_ref = const EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>&;
		return EMU_MATH_MATRIX_MUTATE_COPY_TEMPLATE(EmuCore::do_clamp_min, OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_, a_ref, 0, 0)
		(
			matrix_a_,
			matrix_a_,
			std::forward<Min_>(min_)
		);
	}

	template<typename OutT_, bool OutColumnMajor_, class Min_, typename TA_, std::size_t NumColumnsA_, std::size_t NumRowsA_, bool ColumnMajorA_>
	[[nodiscard]] constexpr inline auto matrix_clamp_min(const EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>& matrix_a_, Min_&& min_)
		-> EmuMath::Matrix<NumColumnsA_, NumRowsA_, OutT_, OutColumnMajor_>
	{
		using a_ref = const EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>&;
		return EMU_MATH_MATRIX_MUTATE_COPY_TEMPLATE(EmuCore::do_clamp_min, NumColumnsA_, NumRowsA_, OutT_, OutColumnMajor_, a_ref, 0, 0)
		(
			matrix_a_,
			matrix_a_,
			std::forward<Min_>(min_)
		);
	}

	template
	<
		std::size_t OutNumColumns_, std::size_t OutNumRows_, bool OutColumnMajor_,
		class Min_, typename TA_, std::size_t NumColumnsA_, std::size_t NumRowsA_, bool ColumnMajorA_
	>
	[[nodiscard]] constexpr inline EmuMath::Matrix
	<
		OutNumColumns_,
		OutNumRows_,
		typename EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>::preferred_floating_point,
		OutColumnMajor_
	>
	matrix_clamp_min(const EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>& matrix_a_, Min_&& min_)
	{
		using a_ref = const EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>&;
		using a_fp = typename EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>::preferred_floating_point;
		return EMU_MATH_MATRIX_MUTATE_COPY_TEMPLATE(EmuCore::do_clamp_min, OutNumColumns_, OutNumRows_, a_fp, OutColumnMajor_, a_ref, 0, 0)
		(
			matrix_a_,
			matrix_a_,
			std::forward<Min_>(min_)
		);
	}

	template
	<
		bool OutColumnMajor_,
		class Min_, typename TA_, std::size_t NumColumnsA_, std::size_t NumRowsA_, bool ColumnMajorA_
	>
	[[nodiscard]] constexpr inline EmuMath::Matrix
	<
		NumColumnsA_,
		NumRowsA_,
		typename EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>::preferred_floating_point,
		OutColumnMajor_
	>
	matrix_clamp_min(const EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>& matrix_a_, Min_&& min_)
	{
		using a_ref = const EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>&;
		using a_fp = typename EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>::preferred_floating_point;
		return EMU_MATH_MATRIX_MUTATE_COPY_TEMPLATE(EmuCore::do_clamp_min, NumColumnsA_, NumRowsA_, a_fp, OutColumnMajor_, a_ref, 0, 0)
		(
			matrix_a_,
			matrix_a_,
			std::forward<Min_>(min_)
		);
	}
#pragma endregion

#pragma region CLAMP_MIN_MATCHING_MAJOR_OUT
	template
	<
		std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_,
		class Min_, typename TA_, std::size_t NumColumnsA_, std::size_t NumRowsA_, bool ColumnMajorA_
	>
	[[nodiscard]] constexpr inline auto matrix_clamp_min(const EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>& matrix_a_, Min_&& min_)
		-> EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, ColumnMajorA_>
	{
		using a_ref = const EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>&;
		return EMU_MATH_MATRIX_MUTATE_COPY_TEMPLATE(EmuCore::do_clamp_min, OutNumColumns_, OutNumRows_, OutT_, ColumnMajorA_, a_ref, 0, 0)
		(
			matrix_a_,
			matrix_a_,
			std::forward<Min_>(min_)
		);
	}

	template<typename OutT_, class Min_, typename TA_, std::size_t NumColumnsA_, std::size_t NumRowsA_, bool ColumnMajorA_>
	[[nodiscard]] constexpr inline auto matrix_clamp_min(const EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>& matrix_a_, Min_&& min_)
		-> EmuMath::Matrix<NumColumnsA_, NumRowsA_, OutT_, ColumnMajorA_>
	{
		using a_ref = const EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>&;
		return EMU_MATH_MATRIX_MUTATE_COPY_TEMPLATE(EmuCore::do_clamp_min, NumColumnsA_, NumRowsA_, OutT_, ColumnMajorA_, a_ref, 0, 0)
		(
			matrix_a_,
			matrix_a_,
			std::forward<Min_>(min_)
		);
	}

	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, class Min_, typename TA_, std::size_t NumColumnsA_, std::size_t NumRowsA_, bool ColumnMajorA_>
	[[nodiscard]] constexpr inline EmuMath::Matrix
	<
		OutNumColumns_,
		OutNumRows_,
		typename EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>::preferred_floating_point,
		ColumnMajorA_
	>
	matrix_clamp_min(const EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>& matrix_a_, Min_&& min_)
	{
		using a_ref = const EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>&;
		using a_fp = typename EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>::preferred_floating_point;
		return EMU_MATH_MATRIX_MUTATE_COPY_TEMPLATE(EmuCore::do_clamp_min, OutNumColumns_, OutNumRows_, a_fp, ColumnMajorA_, a_ref, 0, 0)
		(
			matrix_a_,
			matrix_a_,
			std::forward<Min_>(min_)
		);
	}

	template<class Min_, typename TA_, std::size_t NumColumnsA_, std::size_t NumRowsA_, bool ColumnMajorA_>
	[[nodiscard]] constexpr inline EmuMath::Matrix
	<
		NumColumnsA_,
		NumRowsA_,
		typename EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>::preferred_floating_point,
		ColumnMajorA_
	>
	matrix_clamp_min(const EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>& matrix_a_, Min_&& min_)
	{
		using a_ref = const EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>&;
		using a_fp = typename EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>::preferred_floating_point;
		return EMU_MATH_MATRIX_MUTATE_COPY_TEMPLATE(EmuCore::do_clamp_min, NumColumnsA_, NumRowsA_, a_fp, ColumnMajorA_, a_ref, 0, 0)
		(
			matrix_a_,
			matrix_a_,
			std::forward<Min_>(min_)
		);
	}
#pragma endregion

#pragma region CLAMP_MIN_RANGE_CUSTOM_MAJOR_OUT
	/// <summary>
	/// <para> Outputs a version of the input EmuMath Matrix with its elements clamped to a minimum value indicated by Min_. </para>
	/// <para> If Min_ is an EmuMath Matrix: Elements will be clamped to a minimum of the respective element of min_. Otherwise, all will be clamped to min_ directly. </para>
	/// <para> Indices within the provided range will contain respective clamping results. </para>
	/// <para> Indices outside of the provided range will be copies of respective indices in matrix_a_. </para>
	/// </summary>
	/// <param name="matrix_a_">: EmuMath Matrix to clamp.</param>
	/// <param name="min_">: Scalar or EmuMath Matrix to use as the minimum to clamp the `matrix_a_`'s values to.</param>
	/// <returns>Copy of the matrix_a_ with elements in the provided range clamped to the provided minimum, and copied elements elsewhere.</returns>
	template
	<
		std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_,
		std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, bool OutColumnMajor_,
		class Min_, typename TA_, std::size_t NumColumnsA_, std::size_t NumRowsA_, bool ColumnMajorA_
	>
	[[nodiscard]] constexpr inline auto matrix_clamp_min_range(const EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>& matrix_a_, Min_&& min_)
		-> EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>
	{
		using a_ref = const EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>&;
		return EMU_MATH_MATRIX_MUTATE_COPY_RANGE_TEMPLATE
		(
			EmuCore::do_clamp_min, OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_, a_ref, BeginColumn_, EndColumn_, BeginRow_, EndRow_, 0, 0
		)(matrix_a_, matrix_a_, std::forward<Min_>(min_));
	}

	template
	<
		std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_,
		typename OutT_, bool OutColumnMajor_, class Min_, typename TA_, std::size_t NumColumnsA_, std::size_t NumRowsA_, bool ColumnMajorA_
	>
	[[nodiscard]] constexpr inline auto matrix_clamp_min_range(const EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>& matrix_a_, Min_&& min_)
		-> EmuMath::Matrix<NumColumnsA_, NumRowsA_, OutT_, OutColumnMajor_>
	{
		using a_ref = const EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>&;
		return EMU_MATH_MATRIX_MUTATE_COPY_RANGE_TEMPLATE
		(
			EmuCore::do_clamp_min, NumColumnsA_, NumRowsA_, OutT_, OutColumnMajor_, a_ref, BeginColumn_, EndColumn_, BeginRow_, EndRow_, 0, 0
		)(matrix_a_, matrix_a_, std::forward<Min_>(min_));
	}

	template
	<
		std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_,
		std::size_t OutNumColumns_, std::size_t OutNumRows_, bool OutColumnMajor_,
		class Min_, typename TA_, std::size_t NumColumnsA_, std::size_t NumRowsA_, bool ColumnMajorA_
	>
	[[nodiscard]] constexpr inline EmuMath::Matrix
	<
		OutNumColumns_,
		OutNumRows_,
		typename EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>::preferred_floating_point,
		OutColumnMajor_
	> matrix_clamp_min_range(const EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>& matrix_a_, Min_&& min_)
	{
		using a_ref = const EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>&;
		using a_fp = typename EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>::preferred_floating_point;
		return EMU_MATH_MATRIX_MUTATE_COPY_RANGE_TEMPLATE
		(
			EmuCore::do_clamp_min, OutNumColumns_, OutNumRows_, a_fp, OutColumnMajor_, a_ref, BeginColumn_, EndColumn_, BeginRow_, EndRow_, 0, 0
		)(matrix_a_, matrix_a_, std::forward<Min_>(min_));
	}

	template
	<
		std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_,
		bool OutColumnMajor_, class Min_, typename TA_, std::size_t NumColumnsA_, std::size_t NumRowsA_, bool ColumnMajorA_
	>
	[[nodiscard]] constexpr inline EmuMath::Matrix
	<
		NumColumnsA_,
		NumRowsA_,
		typename EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>::preferred_floating_point,
		OutColumnMajor_
	> matrix_clamp_min_range
	(
		const EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>& matrix_a_,
		Min_&& min_
	)
	{
		using a_ref = const EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>&;
		using a_fp = typename EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>::preferred_floating_point;
		return EMU_MATH_MATRIX_MUTATE_COPY_RANGE_TEMPLATE
		(
			EmuCore::do_clamp_min, NumColumnsA_, NumRowsA_, a_fp, OutColumnMajor_, a_ref, BeginColumn_, EndColumn_, BeginRow_, EndRow_, 0, 0
		)(matrix_a_, matrix_a_, std::forward<Min_>(min_));
	}
#pragma endregion

#pragma region CLAMP_MIN_RANGE_MATCHING_MAJOR_OUT
	template
	<
		std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_,
		std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_,
		class Min_, typename TA_, std::size_t NumColumnsA_, std::size_t NumRowsA_, bool ColumnMajorA_
	>
	[[nodiscard]] constexpr inline auto matrix_clamp_min_range(const EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>& matrix_a_, Min_&& min_)
		-> EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, ColumnMajorA_>
	{
		using a_ref = const EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>&;
		return EMU_MATH_MATRIX_MUTATE_COPY_RANGE_TEMPLATE
		(
			EmuCore::do_clamp_min, OutNumColumns_, OutNumRows_, OutT_, ColumnMajorA_, a_ref, BeginColumn_, EndColumn_, BeginRow_, EndRow_, 0, 0
		)(matrix_a_, matrix_a_, std::forward<Min_>(min_));
	}

	template
	<
		std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_,
		typename OutT_, class Min_, typename TA_, std::size_t NumColumnsA_, std::size_t NumRowsA_, bool ColumnMajorA_
	>
	[[nodiscard]] constexpr inline auto matrix_clamp_min_range(const EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>& matrix_a_, Min_&& min_)
		-> EmuMath::Matrix<NumColumnsA_, NumRowsA_, OutT_, ColumnMajorA_>
	{
		using a_ref = const EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>&;
		return EMU_MATH_MATRIX_MUTATE_COPY_RANGE_TEMPLATE
		(
			EmuCore::do_clamp_min, NumColumnsA_, NumRowsA_, OutT_, ColumnMajorA_, a_ref, BeginColumn_, EndColumn_, BeginRow_, EndRow_, 0, 0
		)(matrix_a_, matrix_a_, std::forward<Min_>(min_));
	}

	template
	<
		std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_,
		std::size_t OutNumColumns_, std::size_t OutNumRows_,
		class Min_, typename TA_, std::size_t NumColumnsA_, std::size_t NumRowsA_, bool ColumnMajorA_
	>
	[[nodiscard]] constexpr inline EmuMath::Matrix
	<
		OutNumColumns_,
		OutNumRows_,
		typename EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>::preferred_floating_point,
		ColumnMajorA_
	>
	matrix_clamp_min_range(const EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>& matrix_a_, Min_&& min_)
	{
		using a_ref = const EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>&;
		using a_fp = typename EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>::preferred_floating_point;
		return EMU_MATH_MATRIX_MUTATE_COPY_RANGE_TEMPLATE
		(
			EmuCore::do_clamp_min, OutNumColumns_, OutNumRows_, a_fp, ColumnMajorA_, a_ref, BeginColumn_, EndColumn_, BeginRow_, EndRow_, 0, 0
		)(matrix_a_, matrix_a_, std::forward<Min_>(min_));
	}

	template
	<
		std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_,
		class Min_, typename TA_, std::size_t NumColumnsA_, std::size_t NumRowsA_, bool ColumnMajorA_
	>
	[[nodiscard]] constexpr inline EmuMath::Matrix
	<
		NumColumnsA_,
		NumRowsA_,
		typename EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>::preferred_floating_point,
		ColumnMajorA_
	>
	matrix_clamp_min_range(const EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>& matrix_a_, Min_&& min_)
	{
		using a_ref = const EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>&;
		using a_fp = typename EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>::preferred_floating_point;
		return EMU_MATH_MATRIX_MUTATE_COPY_RANGE_TEMPLATE
		(
			EmuCore::do_clamp_min, NumColumnsA_, NumRowsA_, a_fp, ColumnMajorA_, a_ref, BeginColumn_, EndColumn_, BeginRow_, EndRow_, 0, 0
		)(matrix_a_, matrix_a_, std::forward<Min_>(min_));
	}
#pragma endregion

#pragma region CLAMP_MIN_RANGE_NO_COPY_CUSTOM_MAJOR_OUT
	/// <summary>
	/// <para> Outputs a version of the input EmuMath Matrix with its elements clamped to a minimum value indicated by Min_. </para>
	/// <para> If Min_ is an EmuMath Matrix: Elements will be clamped to a minimum of the respective element of min_. Otherwise, all will be clamped to min_ directly. </para>
	/// <para> Indices within the provided range will contain respective clamping results. </para>
	/// <para> Indices outside of the provided range will be defaulted. </para>
	/// </summary>
	/// <param name="matrix_a_">: EmuMath Matrix to clamp.</param>
	/// <param name="min_">: Scalar or EmuMath Matrix to use as the minimum to clamp the `matrix_a_`'s values to.</param>
	/// <returns>Copy of the matrix_a_ with elements in the provided range clamped to the provided minimum, and default elements elsewhere.</returns>
	template
	<
		std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_,
		std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, bool OutColumnMajor_,
		class Min_, typename TA_, std::size_t NumColumnsA_, std::size_t NumRowsA_, bool ColumnMajorA_
	>
	[[nodiscard]] constexpr inline auto matrix_clamp_min_range_no_copy(const EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>& matrix_a_, Min_&& min_)
		-> EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>
	{
		using a_ref = const EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>&;
		return EMU_MATH_MATRIX_MUTATE_TEMPLATE(EmuCore::do_clamp_min, OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_, BeginColumn_, EndColumn_, BeginRow_, EndRow_)
		(
			matrix_a_,
			std::forward<Min_>(min_)
		);
	}

	template
	<
		std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_,
		typename OutT_, bool OutColumnMajor_, class Min_, typename TA_, std::size_t NumColumnsA_, std::size_t NumRowsA_, bool ColumnMajorA_
	>
	[[nodiscard]] constexpr inline auto matrix_clamp_min_range_no_copy(const EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>& matrix_a_, Min_&& min_)
		-> EmuMath::Matrix<NumColumnsA_, NumRowsA_, OutT_, OutColumnMajor_>
	{
		using a_ref = const EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>&;
		return EMU_MATH_MATRIX_MUTATE_TEMPLATE(EmuCore::do_clamp_min, NumColumnsA_, NumRowsA_, OutT_, OutColumnMajor_, BeginColumn_, EndColumn_, BeginRow_, EndRow_)
		(
			matrix_a_,
			std::forward<Min_>(min_)
		);
	}

	template
	<
		std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_,
		std::size_t OutNumColumns_, std::size_t OutNumRows_, bool OutColumnMajor_,
		class Min_, typename TA_, std::size_t NumColumnsA_, std::size_t NumRowsA_, bool ColumnMajorA_
	>
	[[nodiscard]] constexpr inline EmuMath::Matrix
	<
		OutNumColumns_,
		OutNumRows_,
		typename EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>::preferred_floating_point,
		OutColumnMajor_
	> matrix_clamp_min_range_no_copy(const EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>& matrix_a_, Min_&& min_)
	{
		using a_ref = const EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>&;
		using a_fp = typename EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>::preferred_floating_point;
		return EMU_MATH_MATRIX_MUTATE_TEMPLATE(EmuCore::do_clamp_min, OutNumColumns_, OutNumRows_, a_fp, OutColumnMajor_, BeginColumn_, EndColumn_, BeginRow_, EndRow_)
		(
			matrix_a_,
			std::forward<Min_>(min_)
		);
	}

	template
	<
		std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_,
		bool OutColumnMajor_, class Min_, typename TA_, std::size_t NumColumnsA_, std::size_t NumRowsA_, bool ColumnMajorA_
	>
	[[nodiscard]] constexpr inline EmuMath::Matrix
	<
		NumColumnsA_,
		NumRowsA_,
		typename EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>::preferred_floating_point,
		OutColumnMajor_
	> matrix_clamp_min_range_no_copy(const EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>& matrix_a_, Min_&& min_)
	{
		using a_ref = const EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>&;
		using a_fp = typename EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>::preferred_floating_point;
		return EMU_MATH_MATRIX_MUTATE_TEMPLATE(EmuCore::do_clamp_min, NumColumnsA_, NumRowsA_, a_fp, OutColumnMajor_, BeginColumn_, EndColumn_, BeginRow_, EndRow_)
		(
			matrix_a_,
			std::forward<Min_>(min_)
		);
	}
#pragma endregion

#pragma region CLAMP_MIN_RANGE_NO_COPY_MATCHING_MAJOR_OUT
	template
	<
		std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_,
		std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, class Min_, typename TA_, std::size_t NumColumnsA_, std::size_t NumRowsA_, bool ColumnMajorA_
	>
	[[nodiscard]] constexpr inline auto matrix_clamp_min_range_no_copy(const EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>& matrix_a_, Min_&& min_)
		-> EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, ColumnMajorA_>
	{
		using a_ref = const EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>&;
		return EMU_MATH_MATRIX_MUTATE_TEMPLATE(EmuCore::do_clamp_min, OutNumColumns_, OutNumRows_, OutT_, ColumnMajorA_, BeginColumn_, EndColumn_, BeginRow_, EndRow_)
		(
			matrix_a_,
			std::forward<Min_>(min_)
		);
	}

	template
	<
		std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_,
		typename OutT_, class Min_, typename TA_, std::size_t NumColumnsA_, std::size_t NumRowsA_, bool ColumnMajorA_
	>
	[[nodiscard]] constexpr inline auto matrix_clamp_min_range_no_copy(const EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>& matrix_a_, Min_&& min_)
		-> EmuMath::Matrix<NumColumnsA_, NumRowsA_, OutT_, ColumnMajorA_>
	{
		using a_ref = const EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>&;
		return EMU_MATH_MATRIX_MUTATE_TEMPLATE(EmuCore::do_clamp_min, NumColumnsA_, NumRowsA_, OutT_, ColumnMajorA_, BeginColumn_, EndColumn_, BeginRow_, EndRow_)
		(
			matrix_a_,
			std::forward<Min_>(min_)
		);
	}

	template
	<
		std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_,
		std::size_t OutNumColumns_, std::size_t OutNumRows_, class Min_, typename TA_, std::size_t NumColumnsA_, std::size_t NumRowsA_, bool ColumnMajorA_
	>
	[[nodiscard]] constexpr inline EmuMath::Matrix
	<
		OutNumColumns_,
		OutNumRows_,
		typename EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>::preferred_floating_point,
		ColumnMajorA_
	>
	matrix_clamp_min_range_no_copy(const EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>& matrix_a_, Min_&& min_)
	{
		using a_ref = const EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>&;
		using a_fp = typename EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>::preferred_floating_point;
		return EMU_MATH_MATRIX_MUTATE_TEMPLATE(EmuCore::do_clamp_min, OutNumColumns_, OutNumRows_, a_fp, ColumnMajorA_, BeginColumn_, EndColumn_, BeginRow_, EndRow_)
		(
			matrix_a_,
			std::forward<Min_>(min_)
		);
	}

	template
	<
		std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_,
		class Min_, typename TA_, std::size_t NumColumnsA_, std::size_t NumRowsA_, bool ColumnMajorA_
	>
	[[nodiscard]] constexpr inline EmuMath::Matrix
	<
		NumColumnsA_,
		NumRowsA_,
		typename EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>::preferred_floating_point,
		ColumnMajorA_
	>
	matrix_clamp_min_range_no_copy(const EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>& matrix_a_, Min_&& min_)
	{
		using a_ref = const EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>&;
		using a_fp = typename EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>::preferred_floating_point;
		return EMU_MATH_MATRIX_MUTATE_TEMPLATE(EmuCore::do_clamp_min, NumColumnsA_, NumRowsA_, a_fp, ColumnMajorA_, BeginColumn_, EndColumn_, BeginRow_, EndRow_)
		(
			matrix_a_,
			std::forward<Min_>(min_)
		);
	}
#pragma endregion

#pragma region CLAMP_MIN_OUTPUT_ASSIGNED_VARIANTS
	/// <summary>
	/// <para> Outputs a version of the input EmuMath Matrix with its elements clamped to a minimum of min_, via the provided out_matrix_. </para>
	/// <para> If Min_ is an EmuMath Matrix: Elements will be clamped to a minimum of the respective element of min_. Otherwise, all will be clamped to min_ directly. </para>
	/// </summary>
	/// <param name="out_matrix_">: EmuMath Matrix to output to.</param>
	/// <param name="matrix_a_">: EmuMath Matrix to clamp.</param>
	/// <param name="min_">: Scalar or EmuMath Matrix to use as the minimum to clamp the `matrix_a_`'s values to.</param>
	template
	<
		std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, bool OutColumnMajor_,
		class Min_, typename TA_, std::size_t NumColumnsA_, std::size_t NumRowsA_, bool ColumnMajorA_
	>
	constexpr inline void matrix_clamp_min
	(
		EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>& out_matrix_,
		const EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>& matrix_a_,
		Min_&& min_
	)
	{
		using a_ref = const EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>&;
		EMU_MATH_MATRIX_MUTATE_COPY_ASSIGN_TEMPLATE(EmuCore::do_clamp_min, a_ref, 0, OutNumColumns_, 0, OutNumRows_, 0, 0)
		(
			out_matrix_,
			matrix_a_,
			matrix_a_,
			std::forward<Min_>(min_)
		);
	}

	/// <summary>
	/// <para> Outputs a version of the input EmuMath Matrix with its elements clamped to a minimum of min_, via the provided out_matrix_. </para>
	/// <para> If Min_ is an EmuMath Matrix: Elements will be clamped to a minimum of the respective element of min_. Otherwise, all will be clamped to min_ directly. </para>
	/// <para> Indices within the provided range will contain respective clamping results. </para>
	/// <para> Indices outside of the provided range will be copies of respective indices in matrix_a_. </para>
	/// </summary>
	/// <param name="out_matrix_">: EmuMath Matrix to output to.</param>
	/// <param name="matrix_a_">: EmuMath Matrix to clamp.</param>
	/// <param name="min_">: Scalar or EmuMath Matrix to use as the minimum to clamp the `matrix_a_`'s values to.</param>
	template
	<
		std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_,
		std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, bool OutColumnMajor_,
		class Min_, typename TA_, std::size_t NumColumnsA_, std::size_t NumRowsA_, bool ColumnMajorA_
	>
	constexpr inline void matrix_clamp_min_range
	(
		EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>& out_matrix_,
		const EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>& matrix_a_,
		Min_&& min_
	)
	{
		using a_ref = const EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>&;
		EMU_MATH_MATRIX_MUTATE_COPY_ASSIGN_RANGE_TEMPLATE(EmuCore::do_clamp_min, a_ref, BeginColumn_, EndColumn_, BeginRow_, EndRow_, 0, 0)
		(
			out_matrix_,
			matrix_a_,
			matrix_a_,
			std::forward<Min_>(min_)
		);
	}

	/// <summary>
	/// <para> Outputs a version of the input EmuMath Matrix with its elements clamped to a minimum of min_, via the provided out_matrix_. </para>
	/// <para> If Min_ is an EmuMath Matrix: Elements will be clamped to a minimum of the respective element of min_. Otherwise, all will be clamped to min_ directly. </para>
	/// <para> Indices within the provided range will contain respective clamping results. </para>
	/// <para> Indices outside of the provided range will not be modified. </para>
	/// </summary>
	/// <param name="out_matrix_">: EmuMath Matrix to output to.</param>
	/// <param name="matrix_a_">: EmuMath Matrix to clamp.</param>
	/// <param name="min_">: Scalar or EmuMath Matrix to use as the minimum to clamp the `matrix_a_`'s values to.</param>
	template
	<
		std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_,
		std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, bool OutColumnMajor_,
		class Min_, typename TA_, std::size_t NumColumnsA_, std::size_t NumRowsA_, bool ColumnMajorA_
	>
	constexpr inline void matrix_clamp_min_range_no_copy
	(
		EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>& out_matrix_,
		const EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>& matrix_a_,
		Min_&& min_
	)
	{
		EMU_MATH_MATRIX_MUTATE_ASSIGN_TEMPLATE(EmuCore::do_clamp_min, BeginColumn_, EndColumn_, BeginRow_, EndRow_, 0, 0)
		(
			out_matrix_,
			matrix_a_,
			std::forward<Min_>(min_)
		);
	}
#pragma endregion
}

#endif
