#ifndef EMU_MATH_MATRIX_COPY_H_INC_
#define EMU_MATH_MATRIX_COPY_H_INC_ 1

#include "_common_matrix_helper_includes.h"

// CONTAINS:
// --- copy_is_valid
// --- copy (non-const reference)
// --- copy (const reference)
// --- copy (non-const move-or-copy)
// --- copy (const move-or-copy)

namespace EmuMath::Helpers
{
#pragma region COPY_IS_VALID_FUNCS
	template
	<
		std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, bool OutColumnMajor_,
		class InMatrix_,
		typename = std::enable_if_t<EmuMath::TMP::is_emu_matrix_v<InMatrix_>>
	>
	[[nodiscard]] constexpr inline bool matrix_copy_is_valid()
	{
		using out_matrix_type = EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>;
		using out_indices = EmuMath::TMP::make_full_matrix_index_sequences<out_matrix_type>;
		return _matrix_underlying::_matrix_create_from_matrix_is_valid
		<
			out_matrix_type,
			InMatrix_,
			false
		>(typename out_indices::column_index_sequence(), typename out_indices::row_index_sequence());
	}

	template
	<
		std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, bool OutColumnMajor_,
		class InMatrix_,
		typename = std::enable_if_t<EmuMath::TMP::is_emu_matrix_v<InMatrix_>>
	>
	[[nodiscard]] constexpr inline bool matrix_assert_copy_is_valid()
	{
		using out_matrix_type = EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>;
		using out_indices = EmuMath::TMP::make_full_matrix_index_sequences<out_matrix_type>;
		return _matrix_underlying::_matrix_create_from_matrix_is_valid
		<
			out_matrix_type,
			InMatrix_,
			true
		>(typename out_indices::column_index_sequence(), typename out_indices::row_index_sequence());
	}
#pragma endregion

#pragma region NON_CONST_REF_COPY_FUNCS
	/// <summary>
	/// <para> Produces an EmuMath Matrix which copies the respective indices of the provided in_matrix_. </para>
	/// <para> OutNumColumns_ and OutNumRows_: Number of columns and rows (respectively) for the output Matrix to contain. Default to those of in_matrix_ if not provided. </para>
	/// <para> OutT_: T_ argument for the output Matrix. Defaults to the value_type_uq of in_matrix_ if not provided. </para>
	/// <para> OutColumnMajor_: ColumnMajor_ argument for the output Matrix. Defaults to that of in_matrix_ if not provided. </para>
	/// </summary>
	/// <param name="in_matrix_">: Non-const reference to an EmuMath Matrix to copy.</param>
	/// <returns>Copy of the provided input EmuMath Matrix, as the desired type of EmuMath Matrix.</returns>
	template
	<
		std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, bool OutColumnMajor_,
		typename InT_, std::size_t InNumColumns_, std::size_t InNumRows_, bool InColumnMajor_
	>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_> matrix_copy
	(
		EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>& in_matrix_
	)
	{
		return _matrix_underlying::_matrix_copy<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>(in_matrix_);
	}

	template<typename OutT_, bool OutColumnMajor_, typename InT_, std::size_t InNumColumns_, std::size_t InNumRows_, bool InColumnMajor_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<InNumColumns_, InNumRows_, OutT_, OutColumnMajor_> matrix_copy
	(
		EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>& in_matrix_
	)
	{
		return _matrix_underlying::_matrix_copy<InNumColumns_, InNumRows_, OutT_, OutColumnMajor_>(in_matrix_);
	}

	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, bool OutColumnMajor_, typename InT_, std::size_t InNumColumns_, std::size_t InNumRows_, bool InColumnMajor_>
	[[nodiscard]] constexpr inline EmuMath::Matrix
	<
		OutNumColumns_,
		OutNumRows_,
		typename EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>::value_type_uq,
		OutColumnMajor_
	>
	matrix_copy(EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>& in_matrix_)
	{
		using in_value_uq = typename EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>::value_type_uq;
		return _matrix_underlying::_matrix_copy<OutNumColumns_, OutNumRows_, in_value_uq, OutColumnMajor_>(in_matrix_);
	}

	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, typename InT_, std::size_t InNumColumns_, std::size_t InNumRows_, bool InColumnMajor_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, InColumnMajor_> matrix_copy
	(
		EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>& in_matrix_
	)
	{
		return _matrix_underlying::_matrix_copy<OutNumColumns_, OutNumRows_, OutT_, InColumnMajor_>(in_matrix_);
	}

	template<typename OutT_, typename InT_, std::size_t InNumColumns_, std::size_t InNumRows_, bool InColumnMajor_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<InNumColumns_, InNumRows_, OutT_, InColumnMajor_> matrix_copy
	(
		EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>& in_matrix_
	)
	{
		return _matrix_underlying::_matrix_copy<InNumColumns_, InNumRows_, OutT_, InColumnMajor_>(in_matrix_);
	}

	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename InT_, std::size_t InNumColumns_, std::size_t InNumRows_, bool InColumnMajor_>
	[[nodiscard]] constexpr inline EmuMath::Matrix
	<
		OutNumColumns_,
		OutNumRows_,
		typename EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>::value_type_uq,
		InColumnMajor_
	>
	matrix_copy(EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>& in_matrix_)
	{
		using in_value_uq = typename EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>::value_type_uq;
		return _matrix_underlying::_matrix_copy<OutNumColumns_, OutNumRows_, in_value_uq, InColumnMajor_>(in_matrix_);
	}

	template<typename InT_, std::size_t InNumColumns_, std::size_t InNumRows_, bool InColumnMajor_>
	[[nodiscard]] constexpr inline EmuMath::Matrix
	<
		InNumColumns_,
		InNumRows_,
		typename EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>::value_type_uq,
		InColumnMajor_
	>
	matrix_copy(EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>& in_matrix_)
	{
		using in_value_uq = typename EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>::value_type_uq;
		return _matrix_underlying::_matrix_copy<InNumColumns_, InNumRows_, in_value_uq, InColumnMajor_>(in_matrix_);
	}
#pragma endregion

#pragma region CONST_REF_COPY_FUNCS
	/// <summary>
	/// <para> Produces an EmuMath Matrix which copies the respective indices of the provided in_matrix_. </para>
	/// <para> OutNumColumns_ and OutNumRows_: Number of columns and rows (respectively) for the output Matrix to contain. Default to those of in_matrix_ if not provided. </para>
	/// <para> OutT_: T_ argument for the output Matrix. Defaults to the value_type_uq of in_matrix_ if not provided. </para>
	/// <para> OutColumnMajor_: ColumnMajor_ argument for the output Matrix. Defaults to that of in_matrix_ if not provided. </para>
	/// </summary>
	/// <param name="in_matrix_">: Const reference to an EmuMath Matrix to copy.</param>
	/// <returns>Copy of the provided input EmuMath Matrix, as the desired type of EmuMath Matrix.</returns>
	template
	<
		std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, bool OutColumnMajor_,
		typename InT_, std::size_t InNumColumns_, std::size_t InNumRows_, bool InColumnMajor_
	>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_> matrix_copy
	(
		const EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>& in_matrix_
	)
	{
		return _matrix_underlying::_matrix_copy<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>(in_matrix_);
	}

	template<typename OutT_, bool OutColumnMajor_, typename InT_, std::size_t InNumColumns_, std::size_t InNumRows_, bool InColumnMajor_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<InNumColumns_, InNumRows_, OutT_, OutColumnMajor_> matrix_copy
	(
		const EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>& in_matrix_
	)
	{
		return _matrix_underlying::_matrix_copy<InNumColumns_, InNumRows_, OutT_, OutColumnMajor_>(in_matrix_);
	}

	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, bool OutColumnMajor_, typename InT_, std::size_t InNumColumns_, std::size_t InNumRows_, bool InColumnMajor_>
	[[nodiscard]] constexpr inline EmuMath::Matrix
	<
		OutNumColumns_,
		OutNumRows_,
		typename EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>::value_type_uq,
		OutColumnMajor_
	>
	matrix_copy(const EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>& in_matrix_)
	{
		using in_value_uq = typename EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>::value_type_uq;
		return _matrix_underlying::_matrix_copy<OutNumColumns_, OutNumRows_, in_value_uq, OutColumnMajor_>(in_matrix_);
	}

	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, typename InT_, std::size_t InNumColumns_, std::size_t InNumRows_, bool InColumnMajor_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, InColumnMajor_> matrix_copy
	(
		const EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>& in_matrix_
	)
	{
		return _matrix_underlying::_matrix_copy<OutNumColumns_, OutNumRows_, OutT_, InColumnMajor_>(in_matrix_);
	}

	template<typename OutT_, typename InT_, std::size_t InNumColumns_, std::size_t InNumRows_, bool InColumnMajor_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<InNumColumns_, InNumRows_, OutT_, InColumnMajor_> matrix_copy
	(
		const EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>& in_matrix_
	)
	{
		return _matrix_underlying::_matrix_copy<InNumColumns_, InNumRows_, OutT_, InColumnMajor_>(in_matrix_);
	}

	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename InT_, std::size_t InNumColumns_, std::size_t InNumRows_, bool InColumnMajor_>
	[[nodiscard]] constexpr inline EmuMath::Matrix
	<
		OutNumColumns_,
		OutNumRows_,
		typename EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>::value_type_uq,
		InColumnMajor_
	>
	matrix_copy(const EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>& in_matrix_)
	{
		using in_value_uq = typename EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>::value_type_uq;
		return _matrix_underlying::_matrix_copy<OutNumColumns_, OutNumRows_, in_value_uq, InColumnMajor_>(in_matrix_);
	}

	template<typename InT_, std::size_t InNumColumns_, std::size_t InNumRows_, bool InColumnMajor_>
	[[nodiscard]] constexpr inline EmuMath::Matrix
	<
		InNumColumns_,
		InNumRows_,
		typename EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>::value_type_uq,
		InColumnMajor_
	>
	matrix_copy(const EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>& in_matrix_)
	{
		using in_value_uq = typename EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>::value_type_uq;
		return _matrix_underlying::_matrix_copy<InNumColumns_, InNumRows_, in_value_uq, InColumnMajor_>(in_matrix_);
	}
#pragma endregion

#pragma region NON_CONST_MOVE_COPY_FUNCS
	/// <summary>
	/// <para> Produces an EmuMath Matrix which moves or copies the respective indices of the provided in_matrix_. </para>
	/// <para> OutNumColumns_ and OutNumRows_: Number of columns and rows (respectively) for the output Matrix to contain. Default to those of in_matrix_ if not provided. </para>
	/// <para> OutT_: T_ argument for the output Matrix. Defaults to the value_type_uq of in_matrix_ if not provided. </para>
	/// <para> OutColumnMajor_: ColumnMajor_ argument for the output Matrix. Defaults to that of in_matrix_ if not provided. </para>
	/// </summary>
	/// <param name="in_matrix_">: Non-const rvalue-reference to an EmuMath Matrix to move-or-copy.</param>
	/// <returns>Copy of the provided input EmuMath Matrix, as the desired type of EmuMath Matrix.</returns>
	template
	<
		std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, bool OutColumnMajor_,
		typename InT_, std::size_t InNumColumns_, std::size_t InNumRows_, bool InColumnMajor_
	>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_> matrix_copy
	(
		EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>&& in_matrix_
	)
	{
		using in_matrix_type = EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>;
		return _matrix_underlying::_matrix_copy<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>(std::forward<in_matrix_type>(in_matrix_));
	}

	template<typename OutT_, bool OutColumnMajor_, typename InT_, std::size_t InNumColumns_, std::size_t InNumRows_, bool InColumnMajor_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<InNumColumns_, InNumRows_, OutT_, OutColumnMajor_> matrix_copy
	(
		EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>&& in_matrix_
	)
	{
		using in_matrix_type = EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>;
		return _matrix_underlying::_matrix_copy<InNumColumns_, InNumRows_, OutT_, OutColumnMajor_>(std::forward<in_matrix_type>(in_matrix_));
	}

	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, bool OutColumnMajor_, typename InT_, std::size_t InNumColumns_, std::size_t InNumRows_, bool InColumnMajor_>
	[[nodiscard]] constexpr inline EmuMath::Matrix
	<
		OutNumColumns_,
		OutNumRows_,
		typename EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>::value_type_uq,
		OutColumnMajor_
	>
	matrix_copy(EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>&& in_matrix_)
	{
		using in_matrix_type = EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>;
		using in_value_uq = typename EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>::value_type_uq;
		return _matrix_underlying::_matrix_copy<OutNumColumns_, OutNumRows_, in_value_uq, OutColumnMajor_>(std::forward<in_matrix_type>(in_matrix_));
	}

	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, typename InT_, std::size_t InNumColumns_, std::size_t InNumRows_, bool InColumnMajor_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, InColumnMajor_> matrix_copy
	(
		EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>&& in_matrix_
	)
	{
		using in_matrix_type = EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>;
		return _matrix_underlying::_matrix_copy<OutNumColumns_, OutNumRows_, OutT_, InColumnMajor_>(std::forward<in_matrix_type>(in_matrix_));
	}

	template<typename OutT_, typename InT_, std::size_t InNumColumns_, std::size_t InNumRows_, bool InColumnMajor_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<InNumColumns_, InNumRows_, OutT_, InColumnMajor_> matrix_copy
	(
		EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>&& in_matrix_
	)
	{
		using in_matrix_type = EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>;
		return _matrix_underlying::_matrix_copy<InNumColumns_, InNumRows_, OutT_, InColumnMajor_>(std::forward<in_matrix_type>(in_matrix_));
	}

	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename InT_, std::size_t InNumColumns_, std::size_t InNumRows_, bool InColumnMajor_>
	[[nodiscard]] constexpr inline EmuMath::Matrix
	<
		OutNumColumns_,
		OutNumRows_,
		typename EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>::value_type_uq,
		InColumnMajor_
	>
	matrix_copy(EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>&& in_matrix_)
	{
		using in_matrix_type = EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>;
		using in_value_uq = typename EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>::value_type_uq;
		return _matrix_underlying::_matrix_copy<OutNumColumns_, OutNumRows_, in_value_uq, InColumnMajor_>(std::forward<in_matrix_type>(in_matrix_));
	}

	template<typename InT_, std::size_t InNumColumns_, std::size_t InNumRows_, bool InColumnMajor_>
	[[nodiscard]] constexpr inline EmuMath::Matrix
	<
		InNumColumns_,
		InNumRows_,
		typename EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>::value_type_uq,
		InColumnMajor_
	>
	matrix_copy(EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>&& in_matrix_)
	{
		using in_matrix_type = EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>;
		using in_value_uq = typename EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>::value_type_uq;
		return _matrix_underlying::_matrix_copy<InNumColumns_, InNumRows_, in_value_uq, InColumnMajor_>(std::forward<in_matrix_type>(in_matrix_));
	}
#pragma endregion

#pragma region CONST_MOVE_COPY_FUNCS
	/// <summary>
	/// <para> Produces an EmuMath Matrix which moves or copies the respective indices of the provided in_matrix_. </para>
	/// <para> OutNumColumns_ and OutNumRows_: Number of columns and rows (respectively) for the output Matrix to contain. Default to those of in_matrix_ if not provided. </para>
	/// <para> OutT_: T_ argument for the output Matrix. Defaults to the value_type_uq of in_matrix_ if not provided. </para>
	/// <para> OutColumnMajor_: ColumnMajor_ argument for the output Matrix. Defaults to that of in_matrix_ if not provided. </para>
	/// </summary>
	/// <param name="in_matrix_">: Const rvalue-reference to an EmuMath Matrix to move-or-copy.</param>
	/// <returns>Copy of the provided input EmuMath Matrix, as the desired type of EmuMath Matrix.</returns>
	template
	<
		std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, bool OutColumnMajor_,
		typename InT_, std::size_t InNumColumns_, std::size_t InNumRows_, bool InColumnMajor_
	>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_> matrix_copy
	(
		const EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>&& in_matrix_
	)
	{
		using in_matrix_type = const EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>;
		return _matrix_underlying::_matrix_copy<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>(std::forward<in_matrix_type>(in_matrix_));
	}

	template<typename OutT_, bool OutColumnMajor_, typename InT_, std::size_t InNumColumns_, std::size_t InNumRows_, bool InColumnMajor_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<InNumColumns_, InNumRows_, OutT_, OutColumnMajor_> matrix_copy
	(
		const EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>&& in_matrix_
	)
	{
		using in_matrix_type = const EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>;
		return _matrix_underlying::_matrix_copy<InNumColumns_, InNumRows_, OutT_, OutColumnMajor_>(std::forward<in_matrix_type>(in_matrix_));
	}

	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, bool OutColumnMajor_, typename InT_, std::size_t InNumColumns_, std::size_t InNumRows_, bool InColumnMajor_>
	[[nodiscard]] constexpr inline EmuMath::Matrix
	<
		OutNumColumns_,
		OutNumRows_,
		typename EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>::value_type_uq,
		OutColumnMajor_
	>
	matrix_copy(const EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>&& in_matrix_)
	{
		using in_matrix_type = const EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>;
		using in_value_uq = typename EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>::value_type_uq;
		return _matrix_underlying::_matrix_copy<OutNumColumns_, OutNumRows_, in_value_uq, OutColumnMajor_>(std::forward<in_matrix_type>(in_matrix_));
	}

	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, typename InT_, std::size_t InNumColumns_, std::size_t InNumRows_, bool InColumnMajor_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, InColumnMajor_> matrix_copy
	(
		const EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>&& in_matrix_
	)
	{
		using in_matrix_type = const EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>;
		return _matrix_underlying::_matrix_copy<OutNumColumns_, OutNumRows_, OutT_, InColumnMajor_>(std::forward<in_matrix_type>(in_matrix_));
	}

	template<typename OutT_, typename InT_, std::size_t InNumColumns_, std::size_t InNumRows_, bool InColumnMajor_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<InNumColumns_, InNumRows_, OutT_, InColumnMajor_> matrix_copy
	(
		const EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>&& in_matrix_
	)
	{
		using in_matrix_type = const EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>;
		return _matrix_underlying::_matrix_copy<InNumColumns_, InNumRows_, OutT_, InColumnMajor_>(std::forward<in_matrix_type>(in_matrix_));
	}

	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename InT_, std::size_t InNumColumns_, std::size_t InNumRows_, bool InColumnMajor_>
	[[nodiscard]] constexpr inline EmuMath::Matrix
	<
		OutNumColumns_,
		OutNumRows_,
		typename EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>::value_type_uq,
		InColumnMajor_
	>
	matrix_copy(const EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>&& in_matrix_)
	{
		using in_matrix_type = const EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>;
		using in_value_uq = typename EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>::value_type_uq;
		return _matrix_underlying::_matrix_copy<OutNumColumns_, OutNumRows_, in_value_uq, InColumnMajor_>(std::forward<in_matrix_type>(in_matrix_));
	}

	template<typename InT_, std::size_t InNumColumns_, std::size_t InNumRows_, bool InColumnMajor_>
	[[nodiscard]] constexpr inline EmuMath::Matrix
	<
		InNumColumns_,
		InNumRows_,
		typename EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>::value_type_uq,
		InColumnMajor_
	>
	matrix_copy(const EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>&& in_matrix_)
	{
		using in_matrix_type = const EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>;
		using in_value_uq = typename EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>::value_type_uq;
		return _matrix_underlying::_matrix_copy<InNumColumns_, InNumRows_, in_value_uq, InColumnMajor_>(std::forward<in_matrix_type>(in_matrix_));
	}
#pragma endregion
}

#endif
