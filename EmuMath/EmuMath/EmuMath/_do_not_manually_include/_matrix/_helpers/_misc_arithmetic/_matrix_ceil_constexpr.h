#ifndef EMU_MATH_MATRIX_MISC_ARITHMETIC_CEIL_CONSTEXPR_H_INC_
#define EMU_MATH_MATRIX_MISC_ARITHMETIC_CEIL_CONSTEXPR_H_INC_ 1

#include "../_common_matrix_helper_includes.h"

// CONTAINS
// --- ceil_constexpr
// --- ceil_constexpr_range
// --- ceil_constexpr_range_no_copy

namespace EmuMath::Helpers
{
#pragma region CEIL_CONSTEXPR_CUSTOM_MAJOR_OUT
	/// <summary>
	/// <para> Returns a version of the input EmuMath Matrix with all of its elements rounded toward positive infinity. </para>
	/// <para>
	///		Provides a guarantee to be constexpr-evaluable if possible. Note that this may make sacrifices to accuracy and/or performance, 
	///		and as a result one may prefer to use the non-constexpr variant of this function if it is guaranteed to be executed at runtime.
	/// </para>
	/// </summary>
	/// <param name="in_matrix_">: EmuMath Matrix to ceil.</param>
	/// <returns>Copy of the passed EmuMath Matrix with its elements rounded toward positive infinity.</returns>
	template
	<
		std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, bool OutColumnMajor_,
		typename InT_, std::size_t InNumColumns_, std::size_t InNumRows_, bool InColumnMajor_
	>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_> matrix_ceil_constexpr
	(
		const EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>& in_matrix_
	)
	{
		using in_mat_ref = const EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>&;
		return EMU_MATH_MATRIX_MUTATE_COPY_TEMPLATE(EmuCore::do_ceil_constexpr, OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_, in_mat_ref, 0, 0)
		(
			in_matrix_,
			in_matrix_
		);
	}

	template<typename OutT_, bool OutColumnMajor_, typename InT_, std::size_t InNumColumns_, std::size_t InNumRows_, bool InColumnMajor_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<InNumColumns_, InNumRows_, OutT_, OutColumnMajor_> matrix_ceil_constexpr
	(
		const EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>& in_matrix_
	)
	{
		using in_mat_ref = const EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>&;
		return EMU_MATH_MATRIX_MUTATE_COPY_TEMPLATE(EmuCore::do_ceil_constexpr, InNumColumns_, InNumRows_, OutT_, OutColumnMajor_, in_mat_ref, 0, 0)
		(
			in_matrix_,
			in_matrix_
		);
	}

	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, bool OutColumnMajor_, typename InT_, std::size_t InNumColumns_, std::size_t InNumRows_, bool InColumnMajor_>
	[[nodiscard]] constexpr inline EmuMath::Matrix
	<
		OutNumColumns_,
		OutNumRows_,
		typename EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>::value_type_uq,
		OutColumnMajor_
	>
	matrix_ceil_constexpr(const EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>& in_matrix_)
	{
		using in_mat_ref = const EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>&;
		using in_value_uq = typename EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>::value_type_uq;
		return EMU_MATH_MATRIX_MUTATE_COPY_TEMPLATE(EmuCore::do_ceil_constexpr, OutNumColumns_, OutNumRows_, in_value_uq, OutColumnMajor_, in_mat_ref, 0, 0)
		(
			in_matrix_,
			in_matrix_
		);
	}

	template<bool OutColumnMajor_, typename InT_, std::size_t InNumColumns_, std::size_t InNumRows_, bool InColumnMajor_>
	[[nodiscard]] constexpr inline EmuMath::Matrix
	<
		InNumColumns_,
		InNumRows_,
		typename EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>::value_type_uq,
		OutColumnMajor_
	>
	matrix_ceil_constexpr(const EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>& in_matrix_)
	{
		using in_mat_ref = const EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>&;
		using in_value_uq = typename EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>::value_type_uq;
		return EMU_MATH_MATRIX_MUTATE_COPY_TEMPLATE(EmuCore::do_ceil_constexpr, InNumColumns_, InNumRows_, in_value_uq, OutColumnMajor_, in_mat_ref, 0, 0)
		(
			in_matrix_,
			in_matrix_
		);
	}
#pragma endregion

#pragma region CEIL_CONSTEXPR_MATCHING_MAJOR_OUT
	template
	<
		std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_,
		typename InT_, std::size_t InNumColumns_, std::size_t InNumRows_, bool InColumnMajor_
	>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, InColumnMajor_> matrix_ceil_constexpr
	(
		const EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>& in_matrix_
	)
	{
		using in_mat_ref = const EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>&;
		return EMU_MATH_MATRIX_MUTATE_COPY_TEMPLATE(EmuCore::do_ceil_constexpr, OutNumColumns_, OutNumRows_, OutT_, InColumnMajor_, in_mat_ref, 0, 0)
		(
			in_matrix_,
			in_matrix_
		);
	}

	template<typename OutT_, typename InT_, std::size_t InNumColumns_, std::size_t InNumRows_, bool InColumnMajor_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<InNumColumns_, InNumRows_, OutT_, InColumnMajor_> matrix_ceil_constexpr
	(
		const EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>& in_matrix_
	)
	{
		using in_mat_ref = const EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>&;
		return EMU_MATH_MATRIX_MUTATE_COPY_TEMPLATE(EmuCore::do_ceil_constexpr, InNumColumns_, InNumRows_, OutT_, InColumnMajor_, in_mat_ref, 0, 0)
		(
			in_matrix_,
			in_matrix_
		);
	}

	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename InT_, std::size_t InNumColumns_, std::size_t InNumRows_, bool InColumnMajor_>
	[[nodiscard]] constexpr inline EmuMath::Matrix
	<
		OutNumColumns_,
		OutNumRows_,
		typename EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>::value_type_uq,
		InColumnMajor_
	>
	matrix_ceil_constexpr(const EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>& in_matrix_)
	{
		using in_mat_ref = const EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>&;
		using in_value_uq = typename EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>::value_type_uq;
		return EMU_MATH_MATRIX_MUTATE_COPY_TEMPLATE(EmuCore::do_ceil_constexpr, OutNumColumns_, OutNumRows_, in_value_uq, InColumnMajor_, in_mat_ref, 0, 0)
		(
			in_matrix_,
			in_matrix_
		);
	}

	template<typename InT_, std::size_t InNumColumns_, std::size_t InNumRows_, bool InColumnMajor_>
	[[nodiscard]] constexpr inline EmuMath::Matrix
	<
		InNumColumns_,
		InNumRows_,
		typename EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>::value_type_uq,
		InColumnMajor_
	>
	matrix_ceil_constexpr(const EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>& in_matrix_)
	{
		using in_mat_ref = const EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>&;
		using in_value_uq = typename EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>::value_type_uq;
		return EMU_MATH_MATRIX_MUTATE_COPY_TEMPLATE(EmuCore::do_ceil_constexpr, InNumColumns_, InNumRows_, in_value_uq, InColumnMajor_, in_mat_ref, 0, 0)
		(
			in_matrix_,
			in_matrix_
		);
	}
#pragma endregion

#pragma region CEIL_CONSTEXPR_RANGE_CUSTOM_MAJOR_OUT
	/// <summary>
	/// <para> Returns a version of the input EmuMath Matrix with all of its elements rounded toward positive infinity. </para>
	/// <para> Indices within the provided range will contain results of respective rounding operations. </para>
	/// <para> Indices outside of the provided range will be copies of the respective indices within in_matrix_. </para>
	/// <para>
	///		Provides a guarantee to be constexpr-evaluable if possible. Note that this may make sacrifices to accuracy and/or performance, 
	///		and as a result one may prefer to use the non-constexpr variant of this function if it is guaranteed to be executed at runtime.
	/// </para>
	/// </summary>
	/// <param name="in_matrix_">: EmuMath Matrix to ceil.</param>
	/// <returns>Copy of the passed EmuMath Matrix with its elements rounded toward positive infinity.</returns>
	template
	<
		std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_,
		std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, bool OutColumnMajor_,
		typename InT_, std::size_t InNumColumns_, std::size_t InNumRows_, bool InColumnMajor_
	>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_> matrix_ceil_range_constexpr
	(
		const EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>& in_matrix_
	)
	{
		using in_mat_ref = const EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>&;
		return EMU_MATH_MATRIX_MUTATE_COPY_RANGE_TEMPLATE
		(
			EmuCore::do_ceil_constexpr, OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_, in_mat_ref, BeginColumn_, EndColumn_, BeginRow_, EndRow_, 0, 0
		)(in_matrix_, in_matrix_);
	}

	template
	<
		std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_,
		typename OutT_, bool OutColumnMajor_, typename InT_, std::size_t InNumColumns_, std::size_t InNumRows_, bool InColumnMajor_
	>
	[[nodiscard]] constexpr inline EmuMath::Matrix<InNumColumns_, InNumRows_, OutT_, OutColumnMajor_> matrix_ceil_range_constexpr
	(
		const EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>& in_matrix_
	)
	{
		using in_mat_ref = const EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>&;
		return EMU_MATH_MATRIX_MUTATE_COPY_RANGE_TEMPLATE
		(
			EmuCore::do_ceil_constexpr, InNumColumns_, InNumRows_, OutT_, OutColumnMajor_, in_mat_ref, BeginColumn_, EndColumn_, BeginRow_, EndRow_, 0, 0
		)(in_matrix_, in_matrix_);
	}

	template
	<
		std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_,
		std::size_t OutNumColumns_, std::size_t OutNumRows_, bool OutColumnMajor_, typename InT_, std::size_t InNumColumns_, std::size_t InNumRows_, bool InColumnMajor_
	>
	[[nodiscard]] constexpr inline EmuMath::Matrix
	<
		OutNumColumns_,
		OutNumRows_,
		typename EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>::value_type_uq,
		OutColumnMajor_
	>
	matrix_ceil_range_constexpr(const EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>& in_matrix_)
	{
		using in_value_uq = typename EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>::value_type_uq;
		using in_mat_ref = const EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>&;
		return EMU_MATH_MATRIX_MUTATE_COPY_RANGE_TEMPLATE
		(
			EmuCore::do_ceil_constexpr, OutNumColumns_, OutNumRows_, in_value_uq, OutColumnMajor_, in_mat_ref, BeginColumn_, EndColumn_, BeginRow_, EndRow_, 0, 0
		)(in_matrix_, in_matrix_);
	}

	template
	<
		std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_,
		bool OutColumnMajor_, typename InT_, std::size_t InNumColumns_, std::size_t InNumRows_, bool InColumnMajor_
	>
	[[nodiscard]] constexpr inline EmuMath::Matrix
	<
		InNumColumns_,
		InNumRows_,
		typename EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>::value_type_uq,
		OutColumnMajor_
	>
	matrix_ceil_range_constexpr(const EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>& in_matrix_)
	{
		using in_value_uq = typename EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>::value_type_uq;
		using in_mat_ref = const EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>&;
		return EMU_MATH_MATRIX_MUTATE_COPY_RANGE_TEMPLATE
		(
			EmuCore::do_ceil_constexpr, InNumColumns_, InNumRows_, in_value_uq, OutColumnMajor_, in_mat_ref, BeginColumn_, EndColumn_, BeginRow_, EndRow_, 0, 0
		)(in_matrix_, in_matrix_);
	}
#pragma endregion

#pragma region CEIL_CONSTEXPR_RANGE_MATCHING_MAJOR_OUT
	template
	<
		std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_,
		std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_,
		typename InT_, std::size_t InNumColumns_, std::size_t InNumRows_, bool InColumnMajor_
	>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, InColumnMajor_> matrix_ceil_range_constexpr
	(
		const EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>& in_matrix_
	)
	{
		using in_mat_ref = const EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>&;
		return EMU_MATH_MATRIX_MUTATE_COPY_RANGE_TEMPLATE
		(
			EmuCore::do_ceil_constexpr, OutNumColumns_, OutNumRows_, OutT_, InColumnMajor_, in_mat_ref, BeginColumn_, EndColumn_, BeginRow_, EndRow_, 0, 0
		)(in_matrix_, in_matrix_);
	}

	template
	<
		std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_,
		typename OutT_, typename InT_, std::size_t InNumColumns_, std::size_t InNumRows_, bool InColumnMajor_
	>
	[[nodiscard]] constexpr inline EmuMath::Matrix<InNumColumns_, InNumRows_, OutT_, InColumnMajor_> matrix_ceil_range_constexpr
	(
		const EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>& in_matrix_
	)
	{
		using in_mat_ref = const EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>&;
		return EMU_MATH_MATRIX_MUTATE_COPY_RANGE_TEMPLATE
		(
			EmuCore::do_ceil_constexpr, InNumColumns_, InNumRows_, OutT_, InColumnMajor_, in_mat_ref, BeginColumn_, EndColumn_, BeginRow_, EndRow_, 0, 0
		)(in_matrix_, in_matrix_);
	}

	template
	<
		std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_,
		std::size_t OutNumColumns_, std::size_t OutNumRows_, typename InT_, std::size_t InNumColumns_, std::size_t InNumRows_, bool InColumnMajor_
	>
	[[nodiscard]] constexpr inline EmuMath::Matrix
	<
		OutNumColumns_,
		OutNumRows_,
		typename EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>::value_type_uq,
		InColumnMajor_
	>
	matrix_ceil_range_constexpr(const EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>& in_matrix_)
	{
		using in_value_uq = typename EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>::value_type_uq;
		using in_mat_ref = const EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>&;
		return EMU_MATH_MATRIX_MUTATE_COPY_RANGE_TEMPLATE
		(
			EmuCore::do_ceil_constexpr, OutNumColumns_, OutNumRows_, in_value_uq, InColumnMajor_, in_mat_ref, BeginColumn_, EndColumn_, BeginRow_, EndRow_, 0, 0
		)(in_matrix_, in_matrix_);
	}

	template
	<
		std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_,
		typename InT_, std::size_t InNumColumns_, std::size_t InNumRows_, bool InColumnMajor_
	>
	[[nodiscard]] constexpr inline EmuMath::Matrix
	<
		InNumColumns_,
		InNumRows_,
		typename EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>::value_type_uq,
		InColumnMajor_
	>
	matrix_ceil_range_constexpr(const EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>& in_matrix_)
	{
		using in_value_uq = typename EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>::value_type_uq;
		using in_mat_ref = const EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>&;
		return EMU_MATH_MATRIX_MUTATE_COPY_RANGE_TEMPLATE
		(
			EmuCore::do_ceil_constexpr, InNumColumns_, InNumRows_, in_value_uq, InColumnMajor_, in_mat_ref, BeginColumn_, EndColumn_, BeginRow_, EndRow_, 0, 0
		)(in_matrix_, in_matrix_);
	}
#pragma endregion

#pragma region CEIL_CONSTEXPR_RANGE_NO_COPY_CUSTOM_MAJOR_OUT
	/// <summary>
	/// <para> Returns a version of the input EmuMath Matrix with all of its elements rounded toward positive infinity. </para>
	/// <para> Indices within the provided range will contain results of respective rounding operations. </para>
	/// <para> Indices outside of the provided range will be default-constructed. </para>
	/// <para>
	///		Provides a guarantee to be constexpr-evaluable if possible. Note that this may make sacrifices to accuracy and/or performance, 
	///		and as a result one may prefer to use the non-constexpr variant of this function if it is guaranteed to be executed at runtime.
	/// </para>
	/// </summary>
	/// <param name="in_matrix_">: EmuMath Matrix to ceil.</param>
	/// <returns>Copy of the passed EmuMath Matrix with its elements rounded toward positive infinity.</returns>
	template
	<
		std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_,
		std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, bool OutColumnMajor_,
		typename InT_, std::size_t InNumColumns_, std::size_t InNumRows_, bool InColumnMajor_
	>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_> matrix_ceil_range_no_copy_constexpr
	(
		const EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>& in_matrix_
	)
	{
		using in_mat_ref = const EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>&;
		return EMU_MATH_MATRIX_MUTATE_TEMPLATE(EmuCore::do_ceil_constexpr, OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_, BeginColumn_, EndColumn_, BeginRow_, EndRow_)
		(
			in_matrix_
		);
	}

	template
	<
		std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_,
		typename OutT_, bool OutColumnMajor_, typename InT_, std::size_t InNumColumns_, std::size_t InNumRows_, bool InColumnMajor_
	>
	[[nodiscard]] constexpr inline EmuMath::Matrix<InNumColumns_, InNumRows_, OutT_, OutColumnMajor_> matrix_ceil_range_no_copy_constexpr
	(
		const EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>& in_matrix_
	)
	{
		using in_mat_ref = const EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>&;
		return EMU_MATH_MATRIX_MUTATE_TEMPLATE(EmuCore::do_ceil_constexpr, InNumColumns_, InNumRows_, OutT_, OutColumnMajor_, BeginColumn_, EndColumn_, BeginRow_, EndRow_)
		(
			in_matrix_
		);
	}

	template
	<
		std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_,
		std::size_t OutNumColumns_, std::size_t OutNumRows_, bool OutColumnMajor_, typename InT_, std::size_t InNumColumns_, std::size_t InNumRows_, bool InColumnMajor_
	>
	[[nodiscard]] constexpr inline EmuMath::Matrix
	<
		OutNumColumns_,
		OutNumRows_,
		typename EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>::value_type_uq,
		OutColumnMajor_
	>
	matrix_ceil_range_no_copy_constexpr(const EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>& in_matrix_)
	{
		using in_mat_ref = const EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>&;
		using in_value_uq = typename EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>::value_type_uq;
		return EMU_MATH_MATRIX_MUTATE_TEMPLATE(EmuCore::do_ceil_constexpr, OutNumColumns_, OutNumRows_, in_value_uq, OutColumnMajor_, BeginColumn_, EndColumn_, BeginRow_, EndRow_)
		(
			in_matrix_
		);
	}

	template
	<
		std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_,
		bool OutColumnMajor_, typename InT_, std::size_t InNumColumns_, std::size_t InNumRows_, bool InColumnMajor_
	>
	[[nodiscard]] constexpr inline EmuMath::Matrix
	<
		InNumColumns_,
		InNumRows_,
		typename EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>::value_type_uq,
		OutColumnMajor_
	>
	matrix_ceil_range_no_copy_constexpr(const EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>& in_matrix_)
	{
		using in_mat_ref = const EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>&;
		using in_value_uq = typename EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>::value_type_uq;
		return EMU_MATH_MATRIX_MUTATE_TEMPLATE(EmuCore::do_ceil_constexpr, InNumColumns_, InNumRows_, in_value_uq, OutColumnMajor_, BeginColumn_, EndColumn_, BeginRow_, EndRow_)
		(
			in_matrix_
		);
	}
#pragma endregion

#pragma region CEIL_CONSTEXPR_RANGE_NO_COPY_MATCHING_MAJOR_OUT
	template
	<
		std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_,
		std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_,
		typename InT_, std::size_t InNumColumns_, std::size_t InNumRows_, bool InColumnMajor_
	>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, InColumnMajor_> matrix_ceil_range_no_copy_constexpr
	(
		const EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>& in_matrix_
	)
	{
		using in_mat_ref = const EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>&;
		return EMU_MATH_MATRIX_MUTATE_TEMPLATE(EmuCore::do_ceil_constexpr, OutNumColumns_, OutNumRows_, OutT_, InColumnMajor_, BeginColumn_, EndColumn_, BeginRow_, EndRow_)
		(
			in_matrix_
		);
	}

	template
	<
		std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_,
		typename OutT_, typename InT_, std::size_t InNumColumns_, std::size_t InNumRows_, bool InColumnMajor_
	>
	[[nodiscard]] constexpr inline EmuMath::Matrix<InNumColumns_, InNumRows_, OutT_, InColumnMajor_> matrix_ceil_range_no_copy_constexpr
	(
		const EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>& in_matrix_
	)
	{
		using in_mat_ref = const EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>&;
		return EMU_MATH_MATRIX_MUTATE_TEMPLATE(EmuCore::do_ceil_constexpr, InNumColumns_, InNumRows_, OutT_, InColumnMajor_, BeginColumn_, EndColumn_, BeginRow_, EndRow_)
		(
			in_matrix_
		);
	}

	template
	<
		std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_,
		std::size_t OutNumColumns_, std::size_t OutNumRows_, typename InT_, std::size_t InNumColumns_, std::size_t InNumRows_, bool InColumnMajor_
	>
	[[nodiscard]] constexpr inline EmuMath::Matrix
	<
		OutNumColumns_,
		OutNumRows_,
		typename EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>::value_type_uq,
		InColumnMajor_
	>
	matrix_ceil_range_no_copy_constexpr(const EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>& in_matrix_)
	{
		using in_mat_ref = const EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>&;
		using in_value_uq = typename EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>::value_type_uq;
		return EMU_MATH_MATRIX_MUTATE_TEMPLATE(EmuCore::do_ceil_constexpr, OutNumColumns_, OutNumRows_, in_value_uq, InColumnMajor_, BeginColumn_, EndColumn_, BeginRow_, EndRow_)
		(
			in_matrix_
		);
	}

	template
	<
		std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_,
		typename InT_, std::size_t InNumColumns_, std::size_t InNumRows_, bool InColumnMajor_
	>
	[[nodiscard]] constexpr inline EmuMath::Matrix
	<
		InNumColumns_,
		InNumRows_,
		typename EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>::value_type_uq,
		InColumnMajor_
	>
	matrix_ceil_range_no_copy_constexpr(const EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>& in_matrix_)
	{
		using in_mat_ref = const EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>&;
		using in_value_uq = typename EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>::value_type_uq;
		return EMU_MATH_MATRIX_MUTATE_TEMPLATE(EmuCore::do_ceil_constexpr, InNumColumns_, InNumRows_, in_value_uq, InColumnMajor_, BeginColumn_, EndColumn_, BeginRow_, EndRow_)
		(
			in_matrix_
		);
	}
#pragma endregion

#pragma region CEIL_CONSTEXPR_OUTPUT_ASSIGNED_VARIANTS
	/// <summary>
	/// <para> Outputs a version of the input EmuMath Matrix with all of its elements rounded toward positive infinity via the provided out_matrix_. </para>
	/// <para>
	///		Provides a guarantee to be constexpr-evaluable if possible. Note that this may make sacrifices to accuracy and/or performance, 
	///		and as a result one may prefer to use the non-constexpr variant of this function if it is guaranteed to be executed at runtime.
	/// </para>
	/// </summary>
	/// <param name="out_matrix_">: EmuMath Matrix to output to.</param>
	/// <param name="in_matrix_">: EmuMath Matrix to ceil.</param>
	template
	<
		std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, bool OutColumnMajor_,
		std::size_t InNumColumns_, std::size_t InNumRows_, typename InT_, bool InColumnMajor_
	>
	constexpr inline void matrix_ceil_constexpr
	(
		EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>& out_matrix_,
		const EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>& in_matrix_
	)
	{
		using in_mat_ref = const EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>&;
		EMU_MATH_MATRIX_MUTATE_COPY_ASSIGN_TEMPLATE(EmuCore::do_ceil_constexpr, in_mat_ref, 0, OutNumColumns_, 0, OutNumRows_, 0, 0)
		(
			out_matrix_,
			in_matrix_,
			in_matrix_
		);
	}

	/// <summary>
	/// <para> Outputs a version of the input EmuMath Matrix with all of its elements rounded toward positive infinity via the provided out_matrix_. </para>
	/// <para> Indices within the provided range will contain results of respective rounding operations. </para>
	/// <para> Indices outside of the provided range will be copies of the respective indices within in_matrix_. </para>
	/// <para>
	///		Provides a guarantee to be constexpr-evaluable if possible. Note that this may make sacrifices to accuracy and/or performance, 
	///		and as a result one may prefer to use the non-constexpr variant of this function if it is guaranteed to be executed at runtime.
	/// </para>
	/// </summary>
	/// <param name="out_matrix_">: EmuMath Matrix to output to.</param>
	/// <param name="in_matrix_">: EmuMath Matrix to ceil.</param>
	template
	<
		std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_,
		std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, bool OutColumnMajor_,
		std::size_t InNumColumns_, std::size_t InNumRows_, typename InT_, bool InColumnMajor_
	>
	constexpr inline void matrix_ceil_range_constexpr
	(
		EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>& out_matrix_,
		const EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>& in_matrix_
	)
	{
		using in_mat_ref = const EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>&;
		EMU_MATH_MATRIX_MUTATE_COPY_ASSIGN_RANGE_TEMPLATE(EmuCore::do_ceil_constexpr, in_mat_ref, BeginColumn_, EndColumn_, BeginRow_, EndRow_, 0, 0)
		(
			out_matrix_,
			in_matrix_,
			in_matrix_
		);
	}

	/// <summary>
	/// <para> Outputs a version of the input EmuMath Matrix with all of its elements rounded toward positive infinity via the provided out_matrix_. </para>
	/// <para> Indices within the provided range will contain results of respective rounding operations. </para>
	/// <para> Indices outside of the provided range will not be modified. </para>
	/// <para>
	///		Provides a guarantee to be constexpr-evaluable if possible. Note that this may make sacrifices to accuracy and/or performance, 
	///		and as a result one may prefer to use the non-constexpr variant of this function if it is guaranteed to be executed at runtime.
	/// </para>
	/// </summary>
	/// <param name="out_matrix_">: EmuMath Matrix to output to.</param>
	/// <param name="in_matrix_">: EmuMath Matrix to ceil.</param>
	template
	<
		std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_,
		std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, bool OutColumnMajor_,
		std::size_t InNumColumns_, std::size_t InNumRows_, typename InT_, bool InColumnMajor_
	>
	constexpr inline void matrix_ceil_range_no_copy_constexpr
	(
		EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>& out_matrix_,
		const EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>& in_matrix_
	)
	{
		EMU_MATH_MATRIX_MUTATE_ASSIGN_TEMPLATE(EmuCore::do_ceil_constexpr, BeginColumn_, EndColumn_, BeginRow_, EndRow_, 0, 0)
		(
			out_matrix_,
			in_matrix_
		);
	}
#pragma endregion
}


#endif
