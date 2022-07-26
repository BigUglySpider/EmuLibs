#ifndef EMU_MATH_MATRIX_MISC_ARITHMETIC_MAX_H_INC_
#define EMU_MATH_MATRIX_MISC_ARITHMETIC_MAX_H_INC_ 1

#include "../_common_matrix_helper_includes.h"

// CONTAINS:
// --- max (self)
// --- max_range(self)
// --- max (a, b)
// --- max_range(a, b)
// --- max_range_no_copy(a, b)

namespace EmuMath::Helpers
{
#pragma region MAX_SELF
	/// <summary>
	/// <para> Outputs the greatest element within the passed EmuMath Matrix as the provided Out_ type, defaulting to the Matrix's value_type_uq. </para>
	/// <para> Supports output of references if the reference type is compatible with const-qualification. </para>
	/// </summary>
	/// <param name="matrix_">: EmuMath Matrix to find the greatest element of.</param>
	/// <returns>Greatest element of the provided EmuMath Matrix, as the provided Out_ type.</returns>
	template<typename Out_, std::size_t NumColumns_, std::size_t NumRows_, typename InT_, bool InColumnMajor_>
	[[nodiscard]] constexpr inline Out_ matrix_max(const EmuMath::Matrix<NumColumns_, NumRows_, InT_, InColumnMajor_>& matrix_)
	{
		return _matrix_underlying::_matrix_min_or_max<EmuCore::do_cmp_greater, Out_, 0, NumColumns_, 0, NumRows_>(matrix_);
	}

	template<std::size_t NumColumns_, std::size_t NumRows_, typename T_, bool ColumnMajor_>
	[[nodiscard]] constexpr inline typename EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>::value_type_uq matrix_max
	(
		const EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>& matrix_
	)
	{
		using in_value_uq = typename EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>::value_type_uq;
		return _matrix_underlying::_matrix_min_or_max<EmuCore::do_cmp_greater, in_value_uq, 0, NumColumns_, 0, NumRows_>(matrix_);
	}

	template<typename Out_, std::size_t NumColumns_, std::size_t NumRows_, typename InT_, bool InColumnMajor_>
	[[nodiscard]] constexpr inline Out_ matrix_max(EmuMath::Matrix<NumColumns_, NumRows_, InT_, InColumnMajor_>& matrix_)
	{
		return _matrix_underlying::_matrix_min_or_max<EmuCore::do_cmp_greater, Out_, 0, NumColumns_, 0, NumRows_>(matrix_);
	}

	template<std::size_t NumColumns_, std::size_t NumRows_, typename T_, bool ColumnMajor_>
	[[nodiscard]] constexpr inline typename EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>::value_type_uq matrix_max
	(
		EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>& matrix_
	)
	{
		using in_value_uq = typename EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>::value_type_uq;
		return _matrix_underlying::_matrix_min_or_max<EmuCore::do_cmp_greater, in_value_uq, 0, NumColumns_, 0, NumRows_>(matrix_);
	}
#pragma endregion

#pragma region MAX_RANGE_SELF
	/// <summary>
	/// <para> Outputs the greatest element within the passed EmuMath Matrix as the provided Out_ type, defaulting to the Matrix's value_type_uq. </para>
	/// <para> Only elements within the provided range will be considered. </para>
	/// <para> Supports output of references if the reference type is compatible with const-qualification, and the provided range contains no theoretical indices. </para>
	/// </summary>
	/// <param name="matrix_">: EmuMath Matrix to find the greatest element of.</param>
	/// <returns>Greatest element of the provided EmuMath Matrix within the provided range, as the provided Out_ type.</returns>
	template
	<
		std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_, typename Out_,
		std::size_t NumColumns_, std::size_t NumRows_, typename InT_, bool InColumnMajor_
	>
	[[nodiscard]] constexpr inline Out_ matrix_max_range(const EmuMath::Matrix<NumColumns_, NumRows_, InT_, InColumnMajor_>& matrix_)
	{
		return _matrix_underlying::_matrix_min_or_max<EmuCore::do_cmp_greater, Out_, BeginColumn_, EndColumn_, BeginRow_, EndRow_>(matrix_);
	}

	template
	<
		std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_,
		std::size_t NumColumns_, std::size_t NumRows_, typename InT_, bool InColumnMajor_
	>
	[[nodiscard]] constexpr inline typename EmuMath::Matrix<NumColumns_, NumRows_, InT_, InColumnMajor_>::value_type_uq matrix_max_range
	(
		const EmuMath::Matrix<NumColumns_, NumRows_, InT_, InColumnMajor_>& matrix_
	)
	{
		using in_value_uq = typename EmuMath::Matrix<NumColumns_, NumRows_, InT_, InColumnMajor_>::value_type_uq;
		return _matrix_underlying::_matrix_min_or_max<EmuCore::do_cmp_greater, in_value_uq, BeginColumn_, EndColumn_, BeginRow_, EndRow_>(matrix_);
	}

	template
	<
		std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_, typename Out_,
		std::size_t NumColumns_, std::size_t NumRows_, typename InT_, bool InColumnMajor_
	>
	[[nodiscard]] constexpr inline Out_ matrix_max_range(EmuMath::Matrix<NumColumns_, NumRows_, InT_, InColumnMajor_>& matrix_)
	{
		return _matrix_underlying::_matrix_min_or_max<EmuCore::do_cmp_greater, Out_, BeginColumn_, EndColumn_, BeginRow_, EndRow_>(matrix_);
	}

	template
	<
		std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_,
		std::size_t NumColumns_, std::size_t NumRows_, typename InT_, bool InColumnMajor_
	>
	[[nodiscard]] constexpr inline typename EmuMath::Matrix<NumColumns_, NumRows_, InT_, InColumnMajor_>::value_type_uq matrix_max_range
	(
		EmuMath::Matrix<NumColumns_, NumRows_, InT_, InColumnMajor_>& matrix_
	)
	{
		using in_value_uq = typename EmuMath::Matrix<NumColumns_, NumRows_, InT_, InColumnMajor_>::value_type_uq;
		return _matrix_underlying::_matrix_min_or_max<EmuCore::do_cmp_greater, in_value_uq, BeginColumn_, EndColumn_, BeginRow_, EndRow_>(matrix_);
	}
#pragma endregion

#pragma region MAX_AB_CUSTOM_MAJOR_OUT_CONST_A
	/// <summary>
	/// <para> Outputs an EmuMath Matrix composed of the greatest elements out of matrix_a_ and b_. </para>
	/// <para>
	///		If B_ is an EmuMath Matrix: Comparisons will be performed with respective indices in matrix_a_ and b_. 
	///		Otherwise, all matrix_a_ indices will be compared with b_ directly.
	/// </para>
	/// </summary>
	/// <param name="matrix_a_">: EmuMath Matrix appearing as a in a max(a, b) operation.</param>
	/// <param name="b_">: Scalar or EmuMath Matrix appearing as b in a max(a, b) operation.</param>
	/// <returns>EmuMath Matrix composed of max results in respective indices.</returns>
	template
	<
		std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, bool OutColumnMajor_,
		class B_, std::size_t NumColumnsA_, std::size_t NumRowsA_, typename TA_, bool ColumnMajorA_
	>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_> matrix_max
	(
		const EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>& matrix_a_,
		B_&& b_
	)
	{
		return EMU_MATH_MATRIX_MUTATE_TEMPLATE_OUT_STORED_RIGHT_ARG(EmuCore::do_max, OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_, 0, OutNumColumns_, 0, OutNumRows_)
		(
			matrix_a_,
			std::forward<B_>(b_)
		);
	}

	template<typename OutT_, bool OutColumnMajor_, class B_, std::size_t NumColumnsA_, std::size_t NumRowsA_, typename TA_, bool ColumnMajorA_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<NumColumnsA_, NumRowsA_, OutT_, OutColumnMajor_> matrix_max
	(
		const EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>& matrix_a_,
		B_&& b_
	)
	{
		return EMU_MATH_MATRIX_MUTATE_TEMPLATE_OUT_STORED_RIGHT_ARG(EmuCore::do_max, NumColumnsA_, NumRowsA_, OutT_, OutColumnMajor_, 0, NumColumnsA_, 0, NumRowsA_)
		(
			matrix_a_,
			std::forward<B_>(b_)
		);
	}

	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, bool OutColumnMajor_, class B_, std::size_t NumColumnsA_, std::size_t NumRowsA_, typename TA_, bool ColumnMajorA_>
	[[nodiscard]] constexpr inline EmuMath::Matrix
	<
		OutNumColumns_,
		OutNumRows_,
		typename EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>::preferred_floating_point,
		OutColumnMajor_
	>
	matrix_max
	(
		const EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>& matrix_a_,
		B_&& b_
	)
	{
		using a_fp = typename EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>::preferred_floating_point;
		return EMU_MATH_MATRIX_MUTATE_TEMPLATE_OUT_STORED_RIGHT_ARG(EmuCore::do_max, OutNumColumns_, OutNumRows_, a_fp, OutColumnMajor_, 0, OutNumColumns_, 0, OutNumRows_)
		(
			matrix_a_,
			std::forward<B_>(b_)
		);
	}

	template<bool OutColumnMajor_, class B_, std::size_t NumColumnsA_, std::size_t NumRowsA_, typename TA_, bool ColumnMajorA_>
	[[nodiscard]] constexpr inline EmuMath::Matrix
	<
		NumColumnsA_,
		NumRowsA_,
		typename EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>::preferred_floating_point,
		OutColumnMajor_
	>
	matrix_max
	(
		const EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>& matrix_a_,
		B_&& b_
	)
	{
		using a_fp = typename EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>::preferred_floating_point;
		return EMU_MATH_MATRIX_MUTATE_TEMPLATE_OUT_STORED_RIGHT_ARG(EmuCore::do_max, NumColumnsA_, NumRowsA_, a_fp, OutColumnMajor_, 0, NumColumnsA_, 0, NumRowsA_)
		(
			matrix_a_,
			std::forward<B_>(b_)
		);
	}
#pragma endregion

#pragma region MAX_AB_CUSTOM_MAJOR_OUT_NON_CONST_A
	template
	<
		std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, bool OutColumnMajor_,
		class B_, std::size_t NumColumnsA_, std::size_t NumRowsA_, typename TA_, bool ColumnMajorA_
	>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_> matrix_max
	(
		EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>& matrix_a_,
		B_&& b_
	)
	{
		return EMU_MATH_MATRIX_MUTATE_TEMPLATE_OUT_STORED_RIGHT_ARG(EmuCore::do_max, OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_, 0, OutNumColumns_, 0, OutNumRows_)
		(
			matrix_a_,
			std::forward<B_>(b_)
		);
	}

	template<typename OutT_, bool OutColumnMajor_, class B_, std::size_t NumColumnsA_, std::size_t NumRowsA_, typename TA_, bool ColumnMajorA_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<NumColumnsA_, NumRowsA_, OutT_, OutColumnMajor_> matrix_max
	(
		EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>& matrix_a_,
		B_&& b_
	)
	{
		return EMU_MATH_MATRIX_MUTATE_TEMPLATE_OUT_STORED_RIGHT_ARG(EmuCore::do_max, NumColumnsA_, NumRowsA_, OutT_, OutColumnMajor_, 0, NumColumnsA_, 0, NumRowsA_)
		(
			matrix_a_,
			std::forward<B_>(b_)
		);
	}

	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, bool OutColumnMajor_, class B_, std::size_t NumColumnsA_, std::size_t NumRowsA_, typename TA_, bool ColumnMajorA_>
	[[nodiscard]] constexpr inline EmuMath::Matrix
	<
		OutNumColumns_,
		OutNumRows_,
		typename EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>::preferred_floating_point,
		OutColumnMajor_
	>
	matrix_max
	(
		EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>& matrix_a_,
		B_&& b_
	)
	{
		using a_fp = typename EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>::preferred_floating_point;
		return EMU_MATH_MATRIX_MUTATE_TEMPLATE_OUT_STORED_RIGHT_ARG(EmuCore::do_max, OutNumColumns_, OutNumRows_, a_fp, OutColumnMajor_, 0, OutNumColumns_, 0, OutNumRows_)
		(
			matrix_a_,
			std::forward<B_>(b_)
		);
	}

	template<bool OutColumnMajor_, class B_, std::size_t NumColumnsA_, std::size_t NumRowsA_, typename TA_, bool ColumnMajorA_>
	[[nodiscard]] constexpr inline EmuMath::Matrix
	<
		NumColumnsA_,
		NumRowsA_,
		typename EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>::preferred_floating_point,
		OutColumnMajor_
	>
	matrix_max
	(
		EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>& matrix_a_,
		B_&& b_
	)
	{
		using a_fp = typename EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>::preferred_floating_point;
		return EMU_MATH_MATRIX_MUTATE_TEMPLATE_OUT_STORED_RIGHT_ARG(EmuCore::do_max, NumColumnsA_, NumRowsA_, a_fp, OutColumnMajor_, 0, NumColumnsA_, 0, NumRowsA_)
		(
			matrix_a_,
			std::forward<B_>(b_)
		);
	}
#pragma endregion

#pragma region MAX_AB_MATCHING_MAJOR_OUT_CONST_A
	template
	<
		std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_,
		class B_, std::size_t NumColumnsA_, std::size_t NumRowsA_, typename TA_, bool ColumnMajorA_
	>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, ColumnMajorA_> matrix_max
	(
		const EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>& matrix_a_,
		B_&& b_
	)
	{
		return EMU_MATH_MATRIX_MUTATE_TEMPLATE_OUT_STORED_RIGHT_ARG(EmuCore::do_max, OutNumColumns_, OutNumRows_, OutT_, ColumnMajorA_, 0, OutNumColumns_, 0, OutNumRows_)
		(
			matrix_a_,
			std::forward<B_>(b_)
		);
	}

	template<typename OutT_, class B_, std::size_t NumColumnsA_, std::size_t NumRowsA_, typename TA_, bool ColumnMajorA_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<NumColumnsA_, NumRowsA_, OutT_, ColumnMajorA_> matrix_max
	(
		const EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>& matrix_a_,
		B_&& b_
	)
	{
		return EMU_MATH_MATRIX_MUTATE_TEMPLATE_OUT_STORED_RIGHT_ARG(EmuCore::do_max, NumColumnsA_, NumRowsA_, OutT_, ColumnMajorA_, 0, NumColumnsA_, 0, NumRowsA_)
		(
			matrix_a_,
			std::forward<B_>(b_)
		);
	}

	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, class B_, std::size_t NumColumnsA_, std::size_t NumRowsA_, typename TA_, bool ColumnMajorA_>
	[[nodiscard]] constexpr inline EmuMath::Matrix
	<
		OutNumColumns_,
		OutNumRows_,
		typename EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>::preferred_floating_point,
		ColumnMajorA_
	>
	matrix_max
	(
		const EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>& matrix_a_,
		B_&& b_
	)
	{
		using a_fp = typename EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>::preferred_floating_point;
		return EMU_MATH_MATRIX_MUTATE_TEMPLATE_OUT_STORED_RIGHT_ARG(EmuCore::do_max, OutNumColumns_, OutNumRows_, a_fp, ColumnMajorA_, 0, OutNumColumns_, 0, OutNumRows_)
		(
			matrix_a_,
			std::forward<B_>(b_)
		);
	}

	template<class B_, std::size_t NumColumnsA_, std::size_t NumRowsA_, typename TA_, bool ColumnMajorA_>
	[[nodiscard]] constexpr inline EmuMath::Matrix
	<
		NumColumnsA_,
		NumRowsA_,
		typename EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>::preferred_floating_point,
		ColumnMajorA_
	>
	matrix_max
	(
		const EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>& matrix_a_,
		B_&& b_
	)
	{
		using a_fp = typename EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>::preferred_floating_point;
		return EMU_MATH_MATRIX_MUTATE_TEMPLATE_OUT_STORED_RIGHT_ARG(EmuCore::do_max, NumColumnsA_, NumRowsA_, a_fp, ColumnMajorA_, 0, NumColumnsA_, 0, NumRowsA_)
		(
			matrix_a_,
			std::forward<B_>(b_)
		);
	}
#pragma endregion

#pragma region MAX_AB_MATCHING_MAJOR_OUT_NON_CONST_A
	template
	<
		std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_,
		class B_, std::size_t NumColumnsA_, std::size_t NumRowsA_, typename TA_, bool ColumnMajorA_
	>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, ColumnMajorA_> matrix_max
	(
		EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>& matrix_a_,
		B_&& b_
	)
	{
		return EMU_MATH_MATRIX_MUTATE_TEMPLATE_OUT_STORED_RIGHT_ARG(EmuCore::do_max, OutNumColumns_, OutNumRows_, OutT_, ColumnMajorA_, 0, OutNumColumns_, 0, OutNumRows_)
		(
			matrix_a_,
			std::forward<B_>(b_)
		);
	}

	template<typename OutT_, class B_, std::size_t NumColumnsA_, std::size_t NumRowsA_, typename TA_, bool ColumnMajorA_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<NumColumnsA_, NumRowsA_, OutT_, ColumnMajorA_> matrix_max
	(
		EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>& matrix_a_,
		B_&& b_
	)
	{
		return EMU_MATH_MATRIX_MUTATE_TEMPLATE_OUT_STORED_RIGHT_ARG(EmuCore::do_max, NumColumnsA_, NumRowsA_, OutT_, ColumnMajorA_, 0, NumColumnsA_, 0, NumRowsA_)
		(
			matrix_a_,
			std::forward<B_>(b_)
		);
	}

	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, class B_, std::size_t NumColumnsA_, std::size_t NumRowsA_, typename TA_, bool ColumnMajorA_>
	[[nodiscard]] constexpr inline EmuMath::Matrix
	<
		OutNumColumns_,
		OutNumRows_,
		typename EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>::preferred_floating_point,
		ColumnMajorA_
	>
	matrix_max
	(
		EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>& matrix_a_,
		B_&& b_
	)
	{
		using a_fp = typename EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>::preferred_floating_point;
		return EMU_MATH_MATRIX_MUTATE_TEMPLATE_OUT_STORED_RIGHT_ARG(EmuCore::do_max, OutNumColumns_, OutNumRows_, a_fp, ColumnMajorA_, 0, OutNumColumns_, 0, OutNumRows_)
		(
			matrix_a_,
			std::forward<B_>(b_)
		);
	}

	template<class B_, std::size_t NumColumnsA_, std::size_t NumRowsA_, typename TA_, bool ColumnMajorA_>
	[[nodiscard]] constexpr inline EmuMath::Matrix
	<
		NumColumnsA_,
		NumRowsA_,
		typename EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>::preferred_floating_point,
		ColumnMajorA_
	>
	matrix_max
	(
		EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>& matrix_a_,
		B_&& b_
	)
	{
		using a_fp = typename EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>::preferred_floating_point;
		return EMU_MATH_MATRIX_MUTATE_TEMPLATE_OUT_STORED_RIGHT_ARG(EmuCore::do_max, NumColumnsA_, NumRowsA_, a_fp, ColumnMajorA_, 0, NumColumnsA_, 0, NumRowsA_)
		(
			matrix_a_,
			std::forward<B_>(b_)
		);
	}
#pragma endregion

#pragma region MAX_AB_ASSIGNED_OUT
	template
	<
		class B_, std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, bool OutColumnMajor_,
		std::size_t NumColumnsA_, std::size_t NumRowsA_, typename TA_, bool ColumnMajorA_
	>
	[[nodiscard]] constexpr inline void matrix_max
	(
		EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>& out_matrix_,
		const EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>& matrix_a_,
		B_&& b_
	)
	{
		using a_ref = const EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>&;
		EMU_MATH_MATRIX_MUTATE_COPY_ASSIGN_TEMPLATE_OUT_VALUQ_RIGHT_ARG
		(
			EmuCore::do_max, OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_, a_ref, 0, OutNumColumns_, 0, OutNumRows_, 0, 0
		)(out_matrix_, matrix_a_, matrix_a_, std::forward<B_>(b_));
	}

	template
	<
		class B_, std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, bool OutColumnMajor_,
		std::size_t NumColumnsA_, std::size_t NumRowsA_, typename TA_, bool ColumnMajorA_
	>
	[[nodiscard]] constexpr inline void matrix_max
	(
		EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>& out_matrix_,
		EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>& matrix_a_,
		B_&& b_
	)
	{
		using a_ref = EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>&;
		EMU_MATH_MATRIX_MUTATE_COPY_ASSIGN_TEMPLATE_OUT_VALUQ_RIGHT_ARG
		(
			EmuCore::do_max, OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_, a_ref, 0, OutNumColumns_, 0, OutNumRows_, 0, 0
		)(out_matrix_, matrix_a_, matrix_a_, std::forward<B_>(b_));
	}
#pragma endregion

#pragma region MAX_RANGE_AB_CUSTOM_MAJOR_OUT_CONST_A
	/// <summary>
	/// <para> Outputs an EmuMath Matrix composed of the greatest elements out of matrix_a_ and b_. </para>
	/// <para>
	///		If B_ is an EmuMath Matrix: Comparisons will be performed with respective indices in matrix_a_ and b_. 
	///		Otherwise, all matrix_a_ indices will be compared with b_ directly.
	/// </para>
	/// <para> Indices within the provided range will be the respective maximum element out of matrix_a_ and b_. </para>
	/// <para> Indices outside of the provided range will be copies of the respective element within matrix_a_. </para>
	/// </summary>
	/// <param name="matrix_a_">: EmuMath Matrix appearing as a in a max(a, b) operation.</param>
	/// <param name="b_">: Scalar or EmuMath Matrix appearing as b in a max(a, b) operation.</param>
	/// <returns>EmuMath Matrix composed of max results in respective indices within the provided range, and copies of respective indices within matrix_a_ elsewhere.</returns>
	template
	<
		std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_,
		std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, bool OutColumnMajor_,
		class B_, typename TA_, std::size_t NumColumnsA_, std::size_t NumRowsA_, bool ColumnMajorA_
	>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_> matrix_max_range
	(
		const EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>& matrix_a_,
		B_&& b_
	)
	{
		using a_ref = const EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>&;
		return EMU_MATH_MATRIX_MUTATE_COPY_RANGE_TEMPLATE_OUT_STORED_RIGHT_ARG
		(
			EmuCore::do_max, OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_, a_ref, BeginColumn_, EndColumn_, BeginRow_, EndRow_, 0, 0
		)
		(
			matrix_a_,
			matrix_a_,
			std::forward<B_>(b_)
		);
	}

	template
	<
		std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_,
		typename OutT_, bool OutColumnMajor_, class B_, typename TA_, std::size_t NumColumnsA_, std::size_t NumRowsA_, bool ColumnMajorA_
	>
	[[nodiscard]] constexpr inline EmuMath::Matrix<NumColumnsA_, NumRowsA_, OutT_, OutColumnMajor_> matrix_max_range
	(
		const EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>& matrix_a_,
		B_&& b_
	)
	{
		using a_ref = const EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>&;
		return EMU_MATH_MATRIX_MUTATE_COPY_RANGE_TEMPLATE_OUT_STORED_RIGHT_ARG
		(
			EmuCore::do_max, NumColumnsA_, NumRowsA_, OutT_, OutColumnMajor_, a_ref, BeginColumn_, EndColumn_, BeginRow_, EndRow_, 0, 0
		)
		(
			matrix_a_,
			matrix_a_,
			std::forward<B_>(b_)
		);
	}

	template
	<
		std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_,
		std::size_t OutNumColumns_, std::size_t OutNumRows_, bool OutColumnMajor_, class B_, typename TA_, std::size_t NumColumnsA_, std::size_t NumRowsA_, bool ColumnMajorA_
	>
	[[nodiscard]] constexpr inline EmuMath::Matrix
	<
		OutNumColumns_,
		OutNumRows_,
		typename EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>::value_type_uq,
		OutColumnMajor_
	>
	matrix_max_range(const EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>& matrix_a_, B_&& b_)
	{
		using a_ref = const EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>&;
		using a_value_uq = typename EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>::value_type_uq;
		return EMU_MATH_MATRIX_MUTATE_COPY_RANGE_TEMPLATE_OUT_STORED_RIGHT_ARG
		(
			EmuCore::do_max, OutNumColumns_, OutNumRows_, a_value_uq, OutColumnMajor_, a_ref, BeginColumn_, EndColumn_, BeginRow_, EndRow_, 0, 0
		)
		(
			matrix_a_,
			matrix_a_,
			std::forward<B_>(b_)
		);
	}

	template
	<
		std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_,
		bool OutColumnMajor_, class B_, typename TA_, std::size_t NumColumnsA_, std::size_t NumRowsA_, bool ColumnMajorA_
	>
	[[nodiscard]] constexpr inline EmuMath::Matrix
	<
		NumColumnsA_,
		NumRowsA_,
		typename EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>::value_type_uq,
		OutColumnMajor_
	>
	matrix_max_range(const EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>& matrix_a_, B_&& b_)
	{
		using a_ref = const EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>&;
		using a_value_uq = typename EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>::value_type_uq;
		return EMU_MATH_MATRIX_MUTATE_COPY_RANGE_TEMPLATE_OUT_STORED_RIGHT_ARG
		(
			EmuCore::do_max, NumColumnsA_, NumRowsA_, a_value_uq, OutColumnMajor_, a_ref, BeginColumn_, EndColumn_, BeginRow_, EndRow_, 0, 0
		)
		(
			matrix_a_,
			matrix_a_,
			std::forward<B_>(b_)
		);
	}
#pragma endregion

#pragma region MAX_RANGE_AB_CUSTOM_MAJOR_OUT_NON_CONST_A
	template
	<
		std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_,
		std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, bool OutColumnMajor_,
		class B_, typename TA_, std::size_t NumColumnsA_, std::size_t NumRowsA_, bool ColumnMajorA_
	>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_> matrix_max_range
	(
		EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>& matrix_a_,
		B_&& b_
	)
	{
		using a_ref = EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>&;
		return EMU_MATH_MATRIX_MUTATE_COPY_RANGE_TEMPLATE_OUT_STORED_RIGHT_ARG
		(
			EmuCore::do_max, OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_, a_ref, BeginColumn_, EndColumn_, BeginRow_, EndRow_, 0, 0
		)
		(
			matrix_a_,
			matrix_a_,
			std::forward<B_>(b_)
		);
	}

	template
	<
		std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_,
		typename OutT_, bool OutColumnMajor_, class B_, typename TA_, std::size_t NumColumnsA_, std::size_t NumRowsA_, bool ColumnMajorA_
	>
	[[nodiscard]] constexpr inline EmuMath::Matrix<NumColumnsA_, NumRowsA_, OutT_, OutColumnMajor_> matrix_max_range
	(
		EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>& matrix_a_,
		B_&& b_
	)
	{
		using a_ref = EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>&;
		return EMU_MATH_MATRIX_MUTATE_COPY_RANGE_TEMPLATE_OUT_STORED_RIGHT_ARG
		(
			EmuCore::do_max, NumColumnsA_, NumRowsA_, OutT_, OutColumnMajor_, a_ref, BeginColumn_, EndColumn_, BeginRow_, EndRow_, 0, 0
		)
		(
			matrix_a_,
			matrix_a_,
			std::forward<B_>(b_)
		);
	}

	template
	<
		std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_,
		std::size_t OutNumColumns_, std::size_t OutNumRows_, bool OutColumnMajor_, class B_, typename TA_, std::size_t NumColumnsA_, std::size_t NumRowsA_, bool ColumnMajorA_
	>
	[[nodiscard]] constexpr inline EmuMath::Matrix
	<
		OutNumColumns_,
		OutNumRows_,
		typename EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>::value_type_uq,
		OutColumnMajor_
	>
	matrix_max_range(EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>& matrix_a_, B_&& b_)
	{
		using a_ref = EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>&;
		using a_value_uq = typename EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>::value_type_uq;
		return EMU_MATH_MATRIX_MUTATE_COPY_RANGE_TEMPLATE_OUT_STORED_RIGHT_ARG
		(
			EmuCore::do_max, OutNumColumns_, OutNumRows_, a_value_uq, OutColumnMajor_, a_ref, BeginColumn_, EndColumn_, BeginRow_, EndRow_, 0, 0
		)
		(
			matrix_a_,
			matrix_a_,
			std::forward<B_>(b_)
		);
	}

	template
	<
		std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_,
		bool OutColumnMajor_, class B_, typename TA_, std::size_t NumColumnsA_, std::size_t NumRowsA_, bool ColumnMajorA_
	>
	[[nodiscard]] constexpr inline EmuMath::Matrix
	<
		NumColumnsA_,
		NumRowsA_,
		typename EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>::value_type_uq,
		OutColumnMajor_
	>
	matrix_max_range(EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>& matrix_a_, B_&& b_)
	{
		using a_ref = EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>&;
		using a_value_uq = typename EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>::value_type_uq;
		return EMU_MATH_MATRIX_MUTATE_COPY_RANGE_TEMPLATE_OUT_STORED_RIGHT_ARG
		(
			EmuCore::do_max, NumColumnsA_, NumRowsA_, a_value_uq, OutColumnMajor_, a_ref, BeginColumn_, EndColumn_, BeginRow_, EndRow_, 0, 0
		)
		(
			matrix_a_,
			matrix_a_,
			std::forward<B_>(b_)
		);
	}
#pragma endregion

#pragma region MAX_RANGE_AB_MATCHING_MAJOR_OUT_CONST_A
	/// <summary>
	/// <para> Outputs an EmuMath Matrix composed of the greatest elements out of matrix_a_ and b_. </para>
	/// <para>
	///		If B_ is an EmuMath Matrix: Comparisons will be performed with respective indices in matrix_a_ and b_. 
	///		Otherwise, all matrix_a_ indices will be compared with b_ directly.
	/// </para>
	/// <para> Indices within the provided range will be the respective maximum element out of matrix_a_ and b_. </para>
	/// <para> Indices outside of the provided range will be copies of the respective element within matrix_a_. </para>
	/// </summary>
	/// <param name="matrix_a_">: EmuMath Matrix appearing as a in a max(a, b) operation.</param>
	/// <param name="b_">: Scalar or EmuMath Matrix appearing as b in a max(a, b) operation.</param>
	/// <returns>EmuMath Matrix composed of max results in respective indices within the provided range, and copies of respective indices within matrix_a_ elsewhere.</returns>
	template
	<
		std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_,
		std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_,
		class B_, typename TA_, std::size_t NumColumnsA_, std::size_t NumRowsA_, bool ColumnMajorA_
	>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, ColumnMajorA_> matrix_max_range
	(
		const EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>& matrix_a_,
		B_&& b_
	)
	{
		using a_ref = const EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>&;

		return EMU_MATH_MATRIX_MUTATE_COPY_RANGE_TEMPLATE_OUT_STORED_RIGHT_ARG
		(
			EmuCore::do_max, OutNumColumns_, OutNumRows_, OutT_, ColumnMajorA_, a_ref, BeginColumn_, EndColumn_, BeginRow_, EndRow_, 0, 0
		)
		(
			matrix_a_,
			matrix_a_,
			std::forward<B_>(b_)
		);
	}

	template
	<
		std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_,
		typename OutT_, class B_, typename TA_, std::size_t NumColumnsA_, std::size_t NumRowsA_, bool ColumnMajorA_
	>
	[[nodiscard]] constexpr inline EmuMath::Matrix<NumColumnsA_, NumRowsA_, OutT_, ColumnMajorA_> matrix_max_range
	(
		const EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>& matrix_a_,
		B_&& b_
	)
	{
		using a_ref = const EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>&;
		return EMU_MATH_MATRIX_MUTATE_COPY_RANGE_TEMPLATE_OUT_STORED_RIGHT_ARG
		(
			EmuCore::do_max, NumColumnsA_, NumRowsA_, OutT_, ColumnMajorA_, a_ref, BeginColumn_, EndColumn_, BeginRow_, EndRow_, 0, 0
		)
		(
			matrix_a_,
			matrix_a_,
			std::forward<B_>(b_)
		);
	}

	template
	<
		std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_,
		std::size_t OutNumColumns_, std::size_t OutNumRows_, class B_, typename TA_, std::size_t NumColumnsA_, std::size_t NumRowsA_, bool ColumnMajorA_
	>
	[[nodiscard]] constexpr inline EmuMath::Matrix
	<
		OutNumColumns_,
		OutNumRows_,
		typename EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>::value_type_uq,
		ColumnMajorA_
	>
	matrix_max_range(const EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>& matrix_a_, B_&& b_)
	{
		using a_ref = const EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>&;
		using a_value_uq = typename EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>::value_type_uq;
		return EMU_MATH_MATRIX_MUTATE_COPY_RANGE_TEMPLATE_OUT_STORED_RIGHT_ARG
		(
			EmuCore::do_max, OutNumColumns_, OutNumRows_, a_value_uq, ColumnMajorA_, a_ref, BeginColumn_, EndColumn_, BeginRow_, EndRow_, 0, 0
		)
		(
			matrix_a_,
			matrix_a_,
			std::forward<B_>(b_)
		);
	}

	template
	<
		std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_,
		class B_, typename TA_, std::size_t NumColumnsA_, std::size_t NumRowsA_, bool ColumnMajorA_
	>
	[[nodiscard]] constexpr inline EmuMath::Matrix
	<
		NumColumnsA_,
		NumRowsA_,
		typename EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>::value_type_uq,
		ColumnMajorA_
	>
	matrix_max_range(const EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>& matrix_a_, B_&& b_)
	{
		using a_ref = const EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>&;
		using a_value_uq = typename EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>::value_type_uq;
		return EMU_MATH_MATRIX_MUTATE_COPY_RANGE_TEMPLATE_OUT_STORED_RIGHT_ARG
		(
			EmuCore::do_max, NumColumnsA_, NumRowsA_, a_value_uq, ColumnMajorA_, a_ref, BeginColumn_, EndColumn_, BeginRow_, EndRow_, 0, 0
		)
		(
			matrix_a_,
			matrix_a_,
			std::forward<B_>(b_)
		);
	}
#pragma endregion

#pragma region MAX_RANGE_AB_MATCHING_MAJOR_OUT_NON_CONST_A
	template
	<
		std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_,
		std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_,
		class B_, typename TA_, std::size_t NumColumnsA_, std::size_t NumRowsA_, bool ColumnMajorA_
	>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, ColumnMajorA_> matrix_max_range
	(
		EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>& matrix_a_,
		B_&& b_
	)
	{
		using a_ref = EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>&;

		return EMU_MATH_MATRIX_MUTATE_COPY_RANGE_TEMPLATE_OUT_STORED_RIGHT_ARG
		(
			EmuCore::do_max, OutNumColumns_, OutNumRows_, OutT_, ColumnMajorA_, a_ref, BeginColumn_, EndColumn_, BeginRow_, EndRow_, 0, 0
		)
		(
			matrix_a_,
			matrix_a_,
			std::forward<B_>(b_)
		);
	}

	template
	<
		std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_,
		typename OutT_, class B_, typename TA_, std::size_t NumColumnsA_, std::size_t NumRowsA_, bool ColumnMajorA_
	>
	[[nodiscard]] constexpr inline EmuMath::Matrix<NumColumnsA_, NumRowsA_, OutT_, ColumnMajorA_> matrix_max_range
	(
		EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>& matrix_a_,
		B_&& b_
	)
	{
		using a_ref = EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>&;
		return EMU_MATH_MATRIX_MUTATE_COPY_RANGE_TEMPLATE_OUT_STORED_RIGHT_ARG
		(
			EmuCore::do_max, NumColumnsA_, NumRowsA_, OutT_, ColumnMajorA_, a_ref, BeginColumn_, EndColumn_, BeginRow_, EndRow_, 0, 0
		)
		(
			matrix_a_,
			matrix_a_,
			std::forward<B_>(b_)
		);
	}

	template
	<
		std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_,
		std::size_t OutNumColumns_, std::size_t OutNumRows_, class B_, typename TA_, std::size_t NumColumnsA_, std::size_t NumRowsA_, bool ColumnMajorA_
	>
	[[nodiscard]] constexpr inline EmuMath::Matrix
	<
		OutNumColumns_,
		OutNumRows_,
		typename EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>::value_type_uq,
		ColumnMajorA_
	>
	matrix_max_range(EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>& matrix_a_, B_&& b_)
	{
		using a_ref = EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>&;
		using a_value_uq = typename EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>::value_type_uq;
		return EMU_MATH_MATRIX_MUTATE_COPY_RANGE_TEMPLATE_OUT_STORED_RIGHT_ARG
		(
			EmuCore::do_max, OutNumColumns_, OutNumRows_, a_value_uq, ColumnMajorA_, a_ref, BeginColumn_, EndColumn_, BeginRow_, EndRow_, 0, 0
		)
		(
			matrix_a_,
			matrix_a_,
			std::forward<B_>(b_)
		);
	}

	template
	<
		std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_,
		class B_, typename TA_, std::size_t NumColumnsA_, std::size_t NumRowsA_, bool ColumnMajorA_
	>
	[[nodiscard]] constexpr inline EmuMath::Matrix
	<
		NumColumnsA_,
		NumRowsA_,
		typename EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>::value_type_uq,
		ColumnMajorA_
	>
	matrix_max_range(EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>& matrix_a_, B_&& b_)
	{
		using a_ref = EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>&;
		using a_value_uq = typename EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>::value_type_uq;
		return EMU_MATH_MATRIX_MUTATE_COPY_RANGE_TEMPLATE_OUT_STORED_RIGHT_ARG
		(
			EmuCore::do_max, NumColumnsA_, NumRowsA_, a_value_uq, ColumnMajorA_, a_ref, BeginColumn_, EndColumn_, BeginRow_, EndRow_, 0, 0
		)
		(
			matrix_a_,
			matrix_a_,
			std::forward<B_>(b_)
		);
	}
#pragma endregion

#pragma region MAX_RANGE_AB_ASSIGNED_OUT
	template
	<
		std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_,
		std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, bool OutColumnMajor_,
		class B_, typename TA_, std::size_t NumColumnsA_, std::size_t NumRowsA_, bool ColumnMajorA_
	>
	constexpr inline void matrix_max_range
	(
		EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>& out_matrix_,
		const EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>& matrix_a_,
		B_&& b_
	)
	{
		using a_ref = const EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>&;
		EMU_MATH_MATRIX_MUTATE_COPY_ASSIGN_TEMPLATE_OUT_VALUQ_RIGHT_ARG
		(
			EmuCore::do_max, OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_, a_ref, BeginColumn_, EndColumn_, BeginRow_, EndRow_, 0, 0
		)(out_matrix_, matrix_a_, matrix_a_, std::forward<B_>(b_));
	}

	template
	<
		std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_,
		std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, bool OutColumnMajor_,
		class B_, typename TA_, std::size_t NumColumnsA_, std::size_t NumRowsA_, bool ColumnMajorA_
	>
	constexpr inline void matrix_max_range
	(
		EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>& out_matrix_,
		EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>& matrix_a_,
		B_&& b_
	)
	{
		using a_ref = EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>&;
		EMU_MATH_MATRIX_MUTATE_COPY_ASSIGN_TEMPLATE_OUT_VALUQ_RIGHT_ARG
		(
			EmuCore::do_max, OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_, a_ref, BeginColumn_, EndColumn_, BeginRow_, EndRow_, 0, 0
		)(out_matrix_, matrix_a_, matrix_a_, std::forward<B_>(b_));
	}
#pragma endregion

#pragma region MAX_RANGE_NO_COPY_AB_CUSTOM_MAJOR_OUT_CONST_A
	/// <summary>
	/// <para> Outputs an EmuMath Matrix composed of the greatest elements out of matrix_a_ and b_. </para>
	/// <para>
	///		If B_ is an EmuMath Matrix: Comparisons will be performed with respective indices in matrix_a_ and b_. 
	///		Otherwise, all matrix_a_ indices will be compared with b_ directly.
	/// </para>
	/// <para> Indices within the provided range will be the respective maximum element out of matrix_a_ and b_. </para>
	/// <para> Indices outside of the provided range will be defaulted. </para>
	/// </summary>
	/// <param name="matrix_a_">: EmuMath Matrix appearing as a in a max(a, b) operation.</param>
	/// <param name="b_">: Scalar or EmuMath Matrix appearing as b in a max(a, b) operation.</param>
	/// <returns>EmuMath Matrix composed of max results in respective indices within the provided range, and default-constructed elements elsewhere.</returns>
	template
	<
		std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_,
		std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, bool OutColumnMajor_,
		class B_, typename TA_, std::size_t NumColumnsA_, std::size_t NumRowsA_, bool ColumnMajorA_
	>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_> matrix_max_range_no_copy
	(
		const EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>& matrix_a_,
		B_&& b_
	)
	{
		return EMU_MATH_MATRIX_MUTATE_TEMPLATE_OUT_STORED_RIGHT_ARG
		(
			EmuCore::do_max, OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_, BeginColumn_, EndColumn_, BeginRow_, EndRow_
		)(matrix_a_, std::forward<B_>(b_));
	}

	template
	<
		std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_,
		typename OutT_, bool OutColumnMajor_, class B_, typename TA_, std::size_t NumColumnsA_, std::size_t NumRowsA_, bool ColumnMajorA_
	>
	[[nodiscard]] constexpr inline EmuMath::Matrix<NumColumnsA_, NumRowsA_, OutT_, OutColumnMajor_> matrix_max_range_no_copy
	(
		const EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>& matrix_a_,
		B_&& b_
	)
	{
		return EMU_MATH_MATRIX_MUTATE_TEMPLATE_OUT_STORED_RIGHT_ARG
		(
			EmuCore::do_max, NumColumnsA_, NumRowsA_, OutT_, OutColumnMajor_, BeginColumn_, EndColumn_, BeginRow_, EndRow_
		)(matrix_a_, std::forward<B_>(b_));
	}

	template
	<
		std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_,
		std::size_t OutNumColumns_, std::size_t OutNumRows_, bool OutColumnMajor_, class B_, typename TA_, std::size_t NumColumnsA_, std::size_t NumRowsA_, bool ColumnMajorA_
	>
	[[nodiscard]] constexpr inline EmuMath::Matrix
	<
		OutNumColumns_,
		OutNumRows_,
		typename EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>::value_type_uq,
		OutColumnMajor_
	>
	matrix_max_range_no_copy(const EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>& matrix_a_, B_&& b_)
	{
		using a_value_uq = typename EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>::value_type_uq;
		return EMU_MATH_MATRIX_MUTATE_TEMPLATE_OUT_STORED_RIGHT_ARG
		(
			EmuCore::do_max, OutNumColumns_, OutNumRows_, a_value_uq, OutColumnMajor_, BeginColumn_, EndColumn_, BeginRow_, EndRow_
		)(matrix_a_, std::forward<B_>(b_));
	}

	template
	<
		std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_,
		bool OutColumnMajor_, class B_, typename TA_, std::size_t NumColumnsA_, std::size_t NumRowsA_, bool ColumnMajorA_
	>
	[[nodiscard]] constexpr inline EmuMath::Matrix
	<
		NumColumnsA_,
		NumRowsA_,
		typename EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>::value_type_uq,
		OutColumnMajor_
	>
	matrix_max_range_no_copy(const EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>& matrix_a_, B_&& b_)
	{
		using a_value_uq = typename EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>::value_type_uq;
		return EMU_MATH_MATRIX_MUTATE_TEMPLATE_OUT_STORED_RIGHT_ARG
		(
			EmuCore::do_max, NumColumnsA_, NumRowsA_, a_value_uq, OutColumnMajor_, BeginColumn_, EndColumn_, BeginRow_, EndRow_
		)(matrix_a_, std::forward<B_>(b_));
	}
#pragma endregion

#pragma region MAX_RANGE_NO_COPY_AB_CUSTOM_MAJOR_OUT_NON_CONST_A
	template
	<
		std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_,
		std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, bool OutColumnMajor_,
		class B_, typename TA_, std::size_t NumColumnsA_, std::size_t NumRowsA_, bool ColumnMajorA_
	>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_> matrix_max_range_no_copy
	(
		EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>& matrix_a_,
		B_&& b_
	)
	{
		return EMU_MATH_MATRIX_MUTATE_TEMPLATE_OUT_STORED_RIGHT_ARG
		(
			EmuCore::do_max, OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_, BeginColumn_, EndColumn_, BeginRow_, EndRow_
		)(matrix_a_, std::forward<B_>(b_));
	}

	template
	<
		std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_,
		typename OutT_, bool OutColumnMajor_, class B_, typename TA_, std::size_t NumColumnsA_, std::size_t NumRowsA_, bool ColumnMajorA_
	>
	[[nodiscard]] constexpr inline EmuMath::Matrix<NumColumnsA_, NumRowsA_, OutT_, OutColumnMajor_> matrix_max_range_no_copy
	(
		EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>& matrix_a_,
		B_&& b_
	)
	{
		return EMU_MATH_MATRIX_MUTATE_TEMPLATE_OUT_STORED_RIGHT_ARG
		(
			EmuCore::do_max, NumColumnsA_, NumRowsA_, OutT_, OutColumnMajor_, BeginColumn_, EndColumn_, BeginRow_, EndRow_
		)(matrix_a_, std::forward<B_>(b_));
	}

	template
	<
		std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_,
		std::size_t OutNumColumns_, std::size_t OutNumRows_, bool OutColumnMajor_, class B_, typename TA_, std::size_t NumColumnsA_, std::size_t NumRowsA_, bool ColumnMajorA_
	>
	[[nodiscard]] constexpr inline EmuMath::Matrix
	<
		OutNumColumns_,
		OutNumRows_,
		typename EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>::value_type_uq,
		OutColumnMajor_
	>
	matrix_max_range_no_copy(EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>& matrix_a_, B_&& b_)
	{
		using a_value_uq = typename EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>::value_type_uq;
		return EMU_MATH_MATRIX_MUTATE_TEMPLATE_OUT_STORED_RIGHT_ARG
		(
			EmuCore::do_max, OutNumColumns_, OutNumRows_, a_value_uq, OutColumnMajor_, BeginColumn_, EndColumn_, BeginRow_, EndRow_
		)(matrix_a_, std::forward<B_>(b_));
	}

	template
	<
		std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_,
		bool OutColumnMajor_, class B_, typename TA_, std::size_t NumColumnsA_, std::size_t NumRowsA_, bool ColumnMajorA_
	>
	[[nodiscard]] constexpr inline EmuMath::Matrix
	<
		NumColumnsA_,
		NumRowsA_,
		typename EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>::value_type_uq,
		OutColumnMajor_
	>
	matrix_max_range_no_copy(EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>& matrix_a_, B_&& b_)
	{
		using a_value_uq = typename EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>::value_type_uq;
		return EMU_MATH_MATRIX_MUTATE_TEMPLATE_OUT_STORED_RIGHT_ARG
		(
			EmuCore::do_max, NumColumnsA_, NumRowsA_, a_value_uq, OutColumnMajor_, BeginColumn_, EndColumn_, BeginRow_, EndRow_
		)(matrix_a_, std::forward<B_>(b_));
	}
#pragma endregion

#pragma region MAX_RANGE_NO_COPY_AB_MATCHING_MAJOR_OUT_CONST_A
	template
	<
		std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_,
		std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_,
		class B_, typename TA_, std::size_t NumColumnsA_, std::size_t NumRowsA_, bool ColumnMajorA_
	>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, ColumnMajorA_> matrix_max_range_no_copy
	(
		const EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>& matrix_a_,
		B_&& b_
	)
	{
		return EMU_MATH_MATRIX_MUTATE_TEMPLATE_OUT_STORED_RIGHT_ARG
		(
			EmuCore::do_max, OutNumColumns_, OutNumRows_, OutT_, ColumnMajorA_, BeginColumn_, EndColumn_, BeginRow_, EndRow_
		)(matrix_a_, std::forward<B_>(b_));
	}

	template
	<
		std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_,
		typename OutT_, class B_, typename TA_, std::size_t NumColumnsA_, std::size_t NumRowsA_, bool ColumnMajorA_
	>
	[[nodiscard]] constexpr inline EmuMath::Matrix<NumColumnsA_, NumRowsA_, OutT_, ColumnMajorA_> matrix_max_range_no_copy
	(
		const EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>& matrix_a_,
		B_&& b_
	)
	{
		return EMU_MATH_MATRIX_MUTATE_TEMPLATE_OUT_STORED_RIGHT_ARG
		(
			EmuCore::do_max, NumColumnsA_, NumRowsA_, OutT_, ColumnMajorA_, BeginColumn_, EndColumn_, BeginRow_, EndRow_
		)(matrix_a_, std::forward<B_>(b_));
	}

	template
	<
		std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_,
		std::size_t OutNumColumns_, std::size_t OutNumRows_, class B_, typename TA_, std::size_t NumColumnsA_, std::size_t NumRowsA_, bool ColumnMajorA_
	>
	[[nodiscard]] constexpr inline EmuMath::Matrix
	<
		OutNumColumns_,
		OutNumRows_,
		typename EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>::value_type_uq,
		ColumnMajorA_
	>
	matrix_max_range_no_copy(const EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>& matrix_a_, B_&& b_)
	{
		using a_value_uq = typename EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>::value_type_uq;
		return EMU_MATH_MATRIX_MUTATE_TEMPLATE_OUT_STORED_RIGHT_ARG
		(
			EmuCore::do_max, OutNumColumns_, OutNumRows_, a_value_uq, ColumnMajorA_, BeginColumn_, EndColumn_, BeginRow_, EndRow_
		)(matrix_a_, std::forward<B_>(b_));
	}

	template
	<
		std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_,
		class B_, typename TA_, std::size_t NumColumnsA_, std::size_t NumRowsA_, bool ColumnMajorA_
	>
	[[nodiscard]] constexpr inline EmuMath::Matrix
	<
		NumColumnsA_,
		NumRowsA_,
		typename EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>::value_type_uq,
		ColumnMajorA_
	>
	matrix_max_range_no_copy(const EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>& matrix_a_, B_&& b_)
	{
		using a_value_uq = typename EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>::value_type_uq;
		return EMU_MATH_MATRIX_MUTATE_TEMPLATE_OUT_STORED_RIGHT_ARG
		(
			EmuCore::do_max, NumColumnsA_, NumRowsA_, a_value_uq, ColumnMajorA_, BeginColumn_, EndColumn_, BeginRow_, EndRow_
		)(matrix_a_, std::forward<B_>(b_));
	}
#pragma endregion

#pragma region MAX_RANGE_NO_COPY_AB_MATCHING_MAJOR_OUT_NON_CONST_A
	template
	<
		std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_,
		std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_,
		class B_, typename TA_, std::size_t NumColumnsA_, std::size_t NumRowsA_, bool ColumnMajorA_
	>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, ColumnMajorA_> matrix_max_range_no_copy
	(
		EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>& matrix_a_,
		B_&& b_
	)
	{
		return EMU_MATH_MATRIX_MUTATE_TEMPLATE_OUT_STORED_RIGHT_ARG
		(
			EmuCore::do_max, OutNumColumns_, OutNumRows_, OutT_, ColumnMajorA_, BeginColumn_, EndColumn_, BeginRow_, EndRow_
		)(matrix_a_, std::forward<B_>(b_));
	}

	template
	<
		std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_,
		typename OutT_, class B_, typename TA_, std::size_t NumColumnsA_, std::size_t NumRowsA_, bool ColumnMajorA_
	>
	[[nodiscard]] constexpr inline EmuMath::Matrix<NumColumnsA_, NumRowsA_, OutT_, ColumnMajorA_> matrix_max_range_no_copy
	(
		EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>& matrix_a_,
		B_&& b_
	)
	{
		return EMU_MATH_MATRIX_MUTATE_TEMPLATE_OUT_STORED_RIGHT_ARG
		(
			EmuCore::do_max, NumColumnsA_, NumRowsA_, OutT_, ColumnMajorA_, BeginColumn_, EndColumn_, BeginRow_, EndRow_
		)(matrix_a_, std::forward<B_>(b_));
	}

	template
	<
		std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_,
		std::size_t OutNumColumns_, std::size_t OutNumRows_, class B_, typename TA_, std::size_t NumColumnsA_, std::size_t NumRowsA_, bool ColumnMajorA_
	>
	[[nodiscard]] constexpr inline EmuMath::Matrix
	<
		OutNumColumns_,
		OutNumRows_,
		typename EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>::value_type_uq,
		ColumnMajorA_
	>
	matrix_max_range_no_copy(EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>& matrix_a_, B_&& b_)
	{
		using a_value_uq = typename EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>::value_type_uq;
		return EMU_MATH_MATRIX_MUTATE_TEMPLATE_OUT_STORED_RIGHT_ARG
		(
			EmuCore::do_max, OutNumColumns_, OutNumRows_, a_value_uq, ColumnMajorA_, BeginColumn_, EndColumn_, BeginRow_, EndRow_
		)(matrix_a_, std::forward<B_>(b_));
	}

	template
	<
		std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_,
		class B_, typename TA_, std::size_t NumColumnsA_, std::size_t NumRowsA_, bool ColumnMajorA_
	>
	[[nodiscard]] constexpr inline EmuMath::Matrix
	<
		NumColumnsA_,
		NumRowsA_,
		typename EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>::value_type_uq,
		ColumnMajorA_
	>
	matrix_max_range_no_copy(EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>& matrix_a_, B_&& b_)
	{
		using a_value_uq = typename EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>::value_type_uq;
		return EMU_MATH_MATRIX_MUTATE_TEMPLATE_OUT_STORED_RIGHT_ARG
		(
			EmuCore::do_max, NumColumnsA_, NumRowsA_, a_value_uq, ColumnMajorA_, BeginColumn_, EndColumn_, BeginRow_, EndRow_
		)(matrix_a_, std::forward<B_>(b_));
	}
#pragma endregion

#pragma region MAX_RANGE_NO_COPY_AB_ASSIGNED_OUT
	template
	<
		std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_,
		std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, bool OutColumnMajor_,
		class B_, typename TA_, std::size_t NumColumnsA_, std::size_t NumRowsA_, bool ColumnMajorA_
	>
	constexpr inline void matrix_max_range_no_copy
	(
		EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>& out_matrix_,
		const EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>& matrix_a_,
		B_&& b_
	)
	{
		EMU_MATH_MATRIX_MUTATE_ASSIGN_TEMPLATE_OUT_VALUQ_RIGHT_ARG
		(
			EmuCore::do_max, OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_, BeginColumn_, EndColumn_, BeginRow_, EndRow_, 0, 0
		)(out_matrix_, matrix_a_, std::forward<B_>(b_));
	}

	template
	<
		std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_,
		std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, bool OutColumnMajor_,
		class B_, typename TA_, std::size_t NumColumnsA_, std::size_t NumRowsA_, bool ColumnMajorA_
	>
	constexpr inline void matrix_max_range_no_copy
	(
		EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>& out_matrix_,
		EmuMath::Matrix<NumColumnsA_, NumRowsA_, TA_, ColumnMajorA_>& matrix_a_,
		B_&& b_
	)
	{
		EMU_MATH_MATRIX_MUTATE_ASSIGN_TEMPLATE_OUT_VALUQ_RIGHT_ARG
		(
			EmuCore::do_max, OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_, BeginColumn_, EndColumn_, BeginRow_, EndRow_, 0, 0
		)(out_matrix_, matrix_a_, std::forward<B_>(b_));
	}
#pragma endregion
}

#endif
