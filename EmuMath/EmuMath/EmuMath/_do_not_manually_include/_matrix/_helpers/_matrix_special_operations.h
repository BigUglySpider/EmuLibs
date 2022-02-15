#ifndef EMU_MATH_MATRIX_SPECIAL_OPERATIONS_H_INC_
#define EMU_MATH_MATRIX_SPECIAL_OPERATIONS_H_INC_ 1

#include "_common_matrix_helper_includes.h"

// CONTAINS:
// --- transpose
// --- identity

namespace EmuMath::Helpers
{
#pragma region TRANSPOSE_LVAL_REF
	/// <summary>
	/// <para> Creates a transposed copy of the provided EmuMath Matrix. </para>
	/// <para>
	///		Supports output of reference-containing Matrices. 
	///		If outputting as a reference, the output must only require access to non-theoretical indices, 
	///		and the referenced type must be both compatible with the input Matrix's type and its const + temporary state.
	/// </para>
	/// <para> If OutNumColumns is not provided:  </para>
	/// </summary>
	/// <param name="in_matrix_">: Non-const lvalue reference to an EmuMath Matrix to output the transpose of.</param>
	/// <returns>Transposed form of the provided EmuMath Matrix.</returns>
	template
	<
		std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, bool OutColumnMajor_,
		typename InT_, std::size_t InNumColumns_, std::size_t InNumRows_, bool InColumnMajor_
	>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_> matrix_transpose
	(
		EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>& in_matrix_
	)
	{
		using in_matrix_type = EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>;
		return _matrix_underlying::_matrix_transpose<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_, in_matrix_type&>(in_matrix_);
	}

	template<typename OutT_, bool OutColumnMajor_, typename InT_, std::size_t InNumColumns_, std::size_t InNumRows_, bool InColumnMajor_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<InNumRows_, InNumColumns_, OutT_, OutColumnMajor_> matrix_transpose
	(
		EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>& in_matrix_
	)
	{
		using in_matrix_type = EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>;
		return _matrix_underlying::_matrix_transpose<InNumRows_, InNumColumns_, OutT_, OutColumnMajor_, in_matrix_type&>(in_matrix_);
	}

	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, bool OutColumnMajor_, typename InT_, std::size_t InNumColumns_, std::size_t InNumRows_, bool InColumnMajor_>
	[[nodiscard]] constexpr inline EmuMath::Matrix
	<
		OutNumColumns_,
		OutNumRows_,
		typename EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>::value_type_uq,
		OutColumnMajor_
	>
	matrix_transpose(EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>& in_matrix_)
	{
		using in_matrix_type = EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>;
		using in_value_uq = typename in_matrix_type::value_type_uq;
		return _matrix_underlying::_matrix_transpose<OutNumColumns_, OutNumRows_, in_value_uq, OutColumnMajor_, in_matrix_type&>(in_matrix_);
	}

	template<bool OutColumnMajor_, typename InT_, std::size_t InNumColumns_, std::size_t InNumRows_, bool InColumnMajor_>
	[[nodiscard]] constexpr inline EmuMath::Matrix
	<
		InNumRows_,
		InNumColumns_,
		typename EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>::value_type_uq,
		OutColumnMajor_
	>
	matrix_transpose(EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>& in_matrix_)
	{
		using in_matrix_type = EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>;
		using in_value_uq = typename in_matrix_type::value_type_uq;
		return _matrix_underlying::_matrix_transpose<InNumRows_, InNumColumns_, in_value_uq, OutColumnMajor_, in_matrix_type&>(in_matrix_);
	}

	template
	<
		std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_,
		typename InT_, std::size_t InNumColumns_, std::size_t InNumRows_, bool InColumnMajor_
	>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, InColumnMajor_> matrix_transpose
	(
		EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>& in_matrix_
	)
	{
		using in_matrix_type = EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>;
		return _matrix_underlying::_matrix_transpose<OutNumColumns_, OutNumRows_, OutT_, InColumnMajor_, in_matrix_type&>(in_matrix_);
	}

	template<typename OutT_, typename InT_, std::size_t InNumColumns_, std::size_t InNumRows_, bool InColumnMajor_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<InNumRows_, InNumColumns_, OutT_, InColumnMajor_> matrix_transpose
	(
		EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>& in_matrix_
	)
	{
		using in_matrix_type = EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>;
		return _matrix_underlying::_matrix_transpose<InNumRows_, InNumColumns_, OutT_, InColumnMajor_, in_matrix_type&>(in_matrix_);
	}

	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename InT_, std::size_t InNumColumns_, std::size_t InNumRows_, bool InColumnMajor_>
	[[nodiscard]] constexpr inline EmuMath::Matrix
	<
		OutNumColumns_,
		OutNumRows_,
		typename EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>::value_type_uq,
		InColumnMajor_
	>
	matrix_transpose(EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>& in_matrix_)
	{
		using in_matrix_type = EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>;
		using in_value_uq = typename in_matrix_type::value_type_uq;
		return _matrix_underlying::_matrix_transpose<OutNumColumns_, OutNumRows_, in_value_uq, InColumnMajor_, in_matrix_type&>(in_matrix_);
	}

	template<typename InT_, std::size_t InNumColumns_, std::size_t InNumRows_, bool InColumnMajor_>
	[[nodiscard]] constexpr inline EmuMath::Matrix
	<
		InNumRows_,
		InNumColumns_,
		typename EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>::value_type_uq,
		InColumnMajor_
	>
	matrix_transpose(EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>& in_matrix_)
	{
		using in_matrix_type = EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>;
		using in_value_uq = typename in_matrix_type::value_type_uq;
		return _matrix_underlying::_matrix_transpose<InNumRows_, InNumColumns_, in_value_uq, InColumnMajor_, in_matrix_type&>(in_matrix_);
	}
#pragma endregion

#pragma region TRANSPOSE_CONST_LVAL_REF
	/// <summary>
	/// <para> Creates a transposed copy of the provided EmuMath Matrix. </para>
	/// <para>
	///		Supports output of reference-containing Matrices. 
	///		If outputting as a reference, the output must only require access to non-theoretical indices, 
	///		and the referenced type must be both compatible with the input Matrix's type and its const + temporary state.
	/// </para>
	/// <para> If OutNumColumns is not provided:  </para>
	/// </summary>
	/// <param name="in_matrix_">: Const lvalue reference to an EmuMath Matrix to output the transpose of.</param>
	/// <returns>Transposed form of the provided EmuMath Matrix.</returns>
	template
	<
		std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, bool OutColumnMajor_,
		typename InT_, std::size_t InNumColumns_, std::size_t InNumRows_, bool InColumnMajor_
	>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_> matrix_transpose
	(
		const EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>& in_matrix_
	)
	{
		using in_matrix_type = EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>;
		return _matrix_underlying::_matrix_transpose<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_, const in_matrix_type&>(in_matrix_);
	}

	template<typename OutT_, bool OutColumnMajor_, typename InT_, std::size_t InNumColumns_, std::size_t InNumRows_, bool InColumnMajor_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<InNumRows_, InNumColumns_, OutT_, OutColumnMajor_> matrix_transpose
	(
		const EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>& in_matrix_
	)
	{
		using in_matrix_type = EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>;
		return _matrix_underlying::_matrix_transpose<InNumRows_, InNumColumns_, OutT_, OutColumnMajor_, const in_matrix_type&>(in_matrix_);
	}

	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, bool OutColumnMajor_, typename InT_, std::size_t InNumColumns_, std::size_t InNumRows_, bool InColumnMajor_>
	[[nodiscard]] constexpr inline EmuMath::Matrix
	<
		OutNumColumns_,
		OutNumRows_,
		typename EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>::value_type_uq,
		OutColumnMajor_
	>
	matrix_transpose(const EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>& in_matrix_)
	{
		using in_matrix_type = EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>;
		using in_value_uq = typename in_matrix_type::value_type_uq;
		return _matrix_underlying::_matrix_transpose<OutNumColumns_, OutNumRows_, in_value_uq, OutColumnMajor_, const in_matrix_type&>(in_matrix_);
	}

	template<bool OutColumnMajor_, typename InT_, std::size_t InNumColumns_, std::size_t InNumRows_, bool InColumnMajor_>
	[[nodiscard]] constexpr inline EmuMath::Matrix
	<
		InNumRows_,
		InNumColumns_,
		typename EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>::value_type_uq,
		OutColumnMajor_
	>
	matrix_transpose(const EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>& in_matrix_)
	{
		using in_matrix_type = EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>;
		using in_value_uq = typename in_matrix_type::value_type_uq;
		return _matrix_underlying::_matrix_transpose<InNumRows_, InNumColumns_, in_value_uq, OutColumnMajor_, const in_matrix_type&>(in_matrix_);
	}

	template
	<
		std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_,
		typename InT_, std::size_t InNumColumns_, std::size_t InNumRows_, bool InColumnMajor_
	>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, InColumnMajor_> matrix_transpose
	(
		const EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>& in_matrix_
	)
	{
		using in_matrix_type = EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>;
		return _matrix_underlying::_matrix_transpose<OutNumColumns_, OutNumRows_, OutT_, InColumnMajor_, const in_matrix_type&>(in_matrix_);
	}

	template<typename OutT_, typename InT_, std::size_t InNumColumns_, std::size_t InNumRows_, bool InColumnMajor_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<InNumRows_, InNumColumns_, OutT_, InColumnMajor_> matrix_transpose
	(
		const EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>& in_matrix_
	)
	{
		using in_matrix_type = EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>;
		return _matrix_underlying::_matrix_transpose<InNumRows_, InNumColumns_, OutT_, InColumnMajor_, const in_matrix_type&>(in_matrix_);
	}

	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename InT_, std::size_t InNumColumns_, std::size_t InNumRows_, bool InColumnMajor_>
	[[nodiscard]] constexpr inline EmuMath::Matrix
	<
		OutNumColumns_,
		OutNumRows_,
		typename EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>::value_type_uq,
		InColumnMajor_
	>
	matrix_transpose(const EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>& in_matrix_)
	{
		using in_matrix_type = EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>;
		using in_value_uq = typename in_matrix_type::value_type_uq;
		return _matrix_underlying::_matrix_transpose<OutNumColumns_, OutNumRows_, in_value_uq, InColumnMajor_, const in_matrix_type&>(in_matrix_);
	}

	template<typename InT_, std::size_t InNumColumns_, std::size_t InNumRows_, bool InColumnMajor_>
	[[nodiscard]] constexpr inline EmuMath::Matrix
	<
		InNumRows_,
		InNumColumns_,
		typename EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>::value_type_uq,
		InColumnMajor_
	>
	matrix_transpose(const EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>& in_matrix_)
	{
		using in_matrix_type = EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>;
		using in_value_uq = typename in_matrix_type::value_type_uq;
		return _matrix_underlying::_matrix_transpose<InNumRows_, InNumColumns_, in_value_uq, InColumnMajor_, const in_matrix_type&>(in_matrix_);
	}
#pragma endregion

#pragma region TRANSPOSE_RVAL_REF
	/// <summary>
	/// <para> Creates a transposed copy of the provided EmuMath Matrix. </para>
	/// <para>
	///		Supports output of reference-containing Matrices, although very few (if any) outputs will support references to an rvalue input to avoid dangling references. 
	///		If outputting as a reference, the output must only require access to non-theoretical indices, 
	///		and the referenced type must be both compatible with the input Matrix's type and its const + temporary state.
	/// </para>
	/// <para> If OutNumColumns is not provided:  </para>
	/// </summary>
	/// <param name="in_matrix_">: Rvalue reference to an EmuMath Matrix to output the transpose of.</param>
	/// <returns>Transposed form of the provided EmuMath Matrix.</returns>
	template
	<
		std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, bool OutColumnMajor_,
		typename InT_, std::size_t InNumColumns_, std::size_t InNumRows_, bool InColumnMajor_
	>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_> matrix_transpose
	(
		EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>&& in_matrix_
	)
	{
		using in_matrix_type = EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>;
		return _matrix_underlying::_matrix_transpose<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>(std::forward<in_matrix_type>(in_matrix_));
	}

	template<typename OutT_, bool OutColumnMajor_, typename InT_, std::size_t InNumColumns_, std::size_t InNumRows_, bool InColumnMajor_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<InNumRows_, InNumColumns_, OutT_, OutColumnMajor_> matrix_transpose
	(
		EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>&& in_matrix_
	)
	{
		using in_matrix_type = EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>;
		return _matrix_underlying::_matrix_transpose<InNumRows_, InNumColumns_, OutT_, OutColumnMajor_>(std::forward<in_matrix_type>(in_matrix_));
	}

	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, bool OutColumnMajor_, typename InT_, std::size_t InNumColumns_, std::size_t InNumRows_, bool InColumnMajor_>
	[[nodiscard]] constexpr inline EmuMath::Matrix
	<
		OutNumColumns_,
		OutNumRows_,
		typename EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>::value_type_uq,
		OutColumnMajor_
	>
	matrix_transpose(EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>&& in_matrix_)
	{
		using in_matrix_type = EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>;
		using in_value_uq = typename in_matrix_type::value_type_uq;
		return _matrix_underlying::_matrix_transpose<OutNumColumns_, OutNumRows_, in_value_uq, OutColumnMajor_>(std::forward<in_matrix_type>(in_matrix_));
	}

	template<bool OutColumnMajor_, typename InT_, std::size_t InNumColumns_, std::size_t InNumRows_, bool InColumnMajor_>
	[[nodiscard]] constexpr inline EmuMath::Matrix
	<
		InNumRows_,
		InNumColumns_,
		typename EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>::value_type_uq,
		OutColumnMajor_
	>
	matrix_transpose(EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>&& in_matrix_)
	{
		using in_matrix_type = EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>;
		using in_value_uq = typename in_matrix_type::value_type_uq;
		return _matrix_underlying::_matrix_transpose<InNumRows_, InNumColumns_, in_value_uq, OutColumnMajor_>(std::forward<in_matrix_type>(in_matrix_));
	}

	template
	<
		std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_,
		typename InT_, std::size_t InNumColumns_, std::size_t InNumRows_, bool InColumnMajor_
	>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, InColumnMajor_> matrix_transpose
	(
		EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>&& in_matrix_
	)
	{
		using in_matrix_type = EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>;
		return _matrix_underlying::_matrix_transpose<OutNumColumns_, OutNumRows_, OutT_, InColumnMajor_>(std::forward<in_matrix_type>(in_matrix_));
	}

	template<typename OutT_, typename InT_, std::size_t InNumColumns_, std::size_t InNumRows_, bool InColumnMajor_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<InNumRows_, InNumColumns_, OutT_, InColumnMajor_> matrix_transpose
	(
		EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>&& in_matrix_
	)
	{
		using in_matrix_type = EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>;
		return _matrix_underlying::_matrix_transpose<InNumRows_, InNumColumns_, OutT_, InColumnMajor_>(std::forward<in_matrix_type>(in_matrix_));
	}

	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename InT_, std::size_t InNumColumns_, std::size_t InNumRows_, bool InColumnMajor_>
	[[nodiscard]] constexpr inline EmuMath::Matrix
	<
		OutNumColumns_,
		OutNumRows_,
		typename EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>::value_type_uq,
		InColumnMajor_
	>
	matrix_transpose(EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>&& in_matrix_)
	{
		using in_matrix_type = EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>;
		using in_value_uq = typename in_matrix_type::value_type_uq;
		return _matrix_underlying::_matrix_transpose<OutNumColumns_, OutNumRows_, in_value_uq, InColumnMajor_>(std::forward<in_matrix_type>(in_matrix_));
	}

	template<typename InT_, std::size_t InNumColumns_, std::size_t InNumRows_, bool InColumnMajor_>
	[[nodiscard]] constexpr inline EmuMath::Matrix
	<
		InNumRows_,
		InNumColumns_,
		typename EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>::value_type_uq,
		InColumnMajor_
	>
	matrix_transpose(EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>&& in_matrix_)
	{
		using in_matrix_type = EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>;
		using in_value_uq = typename in_matrix_type::value_type_uq;
		return _matrix_underlying::_matrix_transpose<InNumRows_, InNumColumns_, in_value_uq, InColumnMajor_>(std::forward<in_matrix_type>(in_matrix_));
	}
#pragma endregion

#pragma region IDENTITY
	/// <summary> 
	/// <para> Constructs an Identity Matrix of the provided size, type, and major order. May alternatively pass an EmuMath Matrix type. </para>
		/// <para> Although this may be used to create an Identity of any size, it mainly has useful meaning within a square Matrix (where NumColumns_ == NumRows_). </para>
	/// </summary>
	/// <returns>EmuMath Matrix of the specified type, constructed as its Identity Matrix (all 1 along the main diagonal, all 0 elsewhere).</returns>
	template<std::size_t NumColumns_, std::size_t NumRows_, typename T_, bool ColumnMajor_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_> matrix_identity()
	{
		return _matrix_underlying::_matrix_identity<NumColumns_, NumRows_, T_, ColumnMajor_>();
	}

	template<class Matrix_, typename = std::enable_if_t<EmuMath::TMP::is_emu_matrix_v<Matrix_>>>
	[[nodiscard]] constexpr inline typename EmuCore::TMP::remove_ref_cv<Matrix_>::type matrix_identity()
	{
		using mat_uq = typename EmuCore::TMP::remove_ref_cv<Matrix_>::type;
		using indices = EmuMath::TMP::make_full_matrix_index_sequences<Matrix_>;
		return _matrix_underlying::_matrix_make_identity<mat_uq>(typename indices::column_index_sequence(), typename indices::row_index_sequence());
	}

	/// <summary>
	/// <para> Assigns the Identity Matrix of the passed EmuMath Matrix's type to said matrix_. </para>
	/// <para> Although this may be used to assign an Identity of any size, it mainly has useful meaning within a square Matrix (where num_columns == num_rows). </para>
	/// </summary>
	/// <param name="matrix_">: EmuMath Matrix to assign the Identity to (all 1 along the main diagonal, all 0 elsewhere).</param>
	template<std::size_t NumColumns_, std::size_t NumRows_, typename T_, bool ColumnMajor_>
	constexpr inline void matrix_identity(EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>& matrix_)
	{
		_matrix_underlying::_matrix_identity(matrix_);
	}
#pragma endregion
}

#endif
