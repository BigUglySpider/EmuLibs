#ifndef EMU_MATH_FAST_MATRIX_INVERSE_AND_RELATED_H_INC_
#define EMU_MATH_FAST_MATRIX_INVERSE_AND_RELATED_H_INC_ 1

#include "_common_fast_matrix_helper_includes.h"

namespace EmuMath::Helpers
{
#pragma region INVERSE_FUNCS
	/// <summary>
	/// <para> Calculates the inverse of the input square-dimensioned FastMatrix. </para>
	/// <para> This assumes that the Matrix has a valid inverse (i.e. it has a non-0 determinant). </para>
	/// </summary>
	/// <param name="in_matrix_">FastMatrix with square dimensions (i.e. `num_columns == num_rows`) to calculate the inverse of.</param>
	/// <returns>Inverse of the passed Matrix.</returns>
	template<EmuConcepts::EmuFastMatrixSquare FastMatrix_>
	[[nodiscard]] constexpr inline auto fast_matrix_inverse(FastMatrix_&& in_matrix_)
		-> typename EmuCore::TMP::remove_ref_cv<FastMatrix_>::type
	{
		typename EmuCore::TMP::remove_ref_cv_t<FastMatrix_>::register_type determinant;
		return _fast_matrix_underlying::_make_inverse_to_stage<_fast_matrix_underlying::_inverse_stage_flag::INVERSE, false>
		(
			std::forward<FastMatrix_>(in_matrix_),
			determinant
		);
	}

	/// <summary>
	/// <para> Calculates the inverse of the input square-dimensioned FastMatrix. </para>
	/// <para> This assumes that the Matrix has a valid inverse (i.e. it has a non-0 determinant). </para>
	/// <para> The calculated determinant will be output to the provided arithmetic scalar reference. </para>
	/// </summary>
	/// <param name="in_matrix_">FastMatrix with square dimensions (i.e. `num_columns == num_rows`) to calculate the inverse of.</param>
	/// <param name="out_determinant_">Non-const arithmetic scalar reference to output the determinant of the Matrix to.</param>
	/// <returns>Inverse of the passed Matrix.</returns>
	template<EmuConcepts::EmuFastMatrixSquare FastMatrix_, EmuConcepts::Arithmetic Determinant_>
	requires (!std::is_const_v<Determinant_>)
	[[nodiscard]] constexpr inline auto fast_matrix_inverse(FastMatrix_&& in_matrix_, Determinant_& out_determinant_)
		-> typename EmuCore::TMP::remove_ref_cv<FastMatrix_>::type
	{
		using _in_fast_mat_uq = typename EmuCore::TMP::remove_ref_cv<FastMatrix_>::type;
		using _offloader = _fast_matrix_underlying::_register_to_scalar_offloader
		<
			typename _in_fast_mat_uq::register_type,
			Determinant_,
			0,
			_in_fast_mat_uq::per_element_width
		>;
		_offloader determinant_offloader(out_determinant_);
		return _fast_matrix_underlying::_make_inverse_to_stage<_fast_matrix_underlying::_inverse_stage_flag::INVERSE, true>
		(
			std::forward<FastMatrix_>(in_matrix_),
			determinant_offloader.registerToOffload
		);
	}

	/// <summary>
	/// <para> Calculates the inverse of the input square-dimensioned FastMatrix. </para>
	/// <para> This assumes that the Matrix has a valid inverse (i.e. it has a non-0 determinant). </para>
	/// <para> The calculated determinant will be output as a SIMD register via the passed register reference. </para>
	/// </summary>
	/// <param name="in_matrix_">FastMatrix with square dimensions (i.e. `num_columns == num_rows`) to calculate the inverse of.</param>
	/// <param name="out_determinant_">Non-const SIMD regster reference (of the Matrix's `register_type`) to output the determinant of the Matrix to.</param>
	/// <returns>Inverse of the passed Matrix.</returns>
	template<EmuConcepts::EmuFastMatrixSquare FastMatrix_>
	[[nodiscard]] constexpr inline auto fast_matrix_inverse
	(
		FastMatrix_&& in_matrix_,
		typename EmuCore::TMP::remove_ref_cv_t<FastMatrix_>::register_type out_determinant_
	) -> typename EmuCore::TMP::remove_ref_cv<FastMatrix_>::type
	{
		return _fast_matrix_underlying::_make_inverse_to_stage<_fast_matrix_underlying::_inverse_stage_flag::INVERSE, true>
		(
			std::forward<FastMatrix_>(in_matrix_),
			out_determinant_
		);
	}
#pragma endregion

// Disabled due to inconsistencies in what has been implemented
// --- We only give access to full inverse for now
// --- This is to allow a reliable and consistent interface
#if 0
#pragma region MINORS_FUNCS
	/// <summary>
	/// <para> Calculates the matrix of minors to the input square-dimensioned FastMatrix. </para>
	/// </summary>
	/// <param name="in_matrix_">FastMatrix with square dimensions (i.e. `num_columns == num_rows`) to calculate the minors of.</param>
	/// <returns>Matrix of minors to the passed Matrix.</returns>
	template<EmuConcepts::EmuFastMatrixSquare FastMatrix_>
	[[nodiscard]] constexpr inline auto fast_matrix_minors(FastMatrix_&& in_matrix_)
		-> typename EmuCore::TMP::remove_ref_cv<FastMatrix_>::type
	{
		typename EmuCore::TMP::remove_ref_cv_t<FastMatrix_>::register_type determinant;
		return _fast_matrix_underlying::_make_inverse_to_stage<_fast_matrix_underlying::_inverse_stage_flag::MINORS, false>
		(
			std::forward<FastMatrix_>(in_matrix_),
			determinant
		);
	}

	/// <summary>
	/// <para> Calculates the matrix of minors to the input square-dimensioned FastMatrix. </para>
	/// <para> The calculated determinant will be output to the provided arithmetic scalar reference. </para>
	/// </summary>
	/// <param name="in_matrix_">FastMatrix with square dimensions (i.e. `num_columns == num_rows`) to calculate the minors of.</param>
	/// <returns>Matrix of minors to the passed Matrix.</returns>
	template<EmuConcepts::EmuFastMatrixSquare FastMatrix_, EmuConcepts::Arithmetic Determinant_>
	requires (!std::is_const_v<Determinant_>)
	[[nodiscard]] constexpr inline auto fast_matrix_minors(FastMatrix_&& in_matrix_, Determinant_& out_determinant_)
		-> typename EmuCore::TMP::remove_ref_cv<FastMatrix_>::type
	{
		using _in_fast_mat_uq = typename EmuCore::TMP::remove_ref_cv<FastMatrix_>::type;
		using _offloader = _fast_matrix_underlying::_register_to_scalar_offloader
		<
			typename _in_fast_mat_uq::register_type,
			Determinant_,
			0,
			_in_fast_mat_uq::per_element_width
		>;
		_offloader determinant_offloader(out_determinant_);
		return _fast_matrix_underlying::_make_inverse_to_stage<_fast_matrix_underlying::_inverse_stage_flag::MINORS, true>
		(
			std::forward<FastMatrix_>(in_matrix_),
			determinant_offloader.registerToOffload
		);
	}

	/// <summary>
	/// <para> Calculates the matrix of minors to the input square-dimensioned FastMatrix. </para>
	/// <para> The calculated determinant will be output as a SIMD register via the passed register reference. </para>
	/// </summary>
	/// <param name="in_matrix_">FastMatrix with square dimensions (i.e. `num_columns == num_rows`) to calculate the minors of.</param>
	/// <returns>Matrix of minors to the passed Matrix.</returns>
	template<EmuConcepts::EmuFastMatrixSquare FastMatrix_>
	[[nodiscard]] constexpr inline auto fast_matrix_minors
	(
		FastMatrix_&& in_matrix_,
		typename EmuCore::TMP::remove_ref_cv_t<FastMatrix_>::register_type out_determinant_
	) -> typename EmuCore::TMP::remove_ref_cv<FastMatrix_>::type
	{
		return _fast_matrix_underlying::_make_inverse_to_stage<_fast_matrix_underlying::_inverse_stage_flag::MINORS, true>
		(
			std::forward<FastMatrix_>(in_matrix_),
			out_determinant_
		);
	}
#pragma endregion

#pragma region COFACTORS_FUNCS
	/// <summary>
	/// <para> Calculates the matrix of cofactors to the input square-dimensioned FastMatrix. </para>
	/// </summary>
	/// <param name="in_matrix_">FastMatrix with square dimensions (i.e. `num_columns == num_rows`) to calculate the minors of.</param>
	/// <returns>Matrix of cofactors to the passed Matrix.</returns>
	template<EmuConcepts::EmuFastMatrixSquare FastMatrix_>
	[[nodiscard]] constexpr inline auto fast_matrix_cofactors(FastMatrix_&& in_matrix_)
		-> typename EmuCore::TMP::remove_ref_cv<FastMatrix_>::type
	{
		typename EmuCore::TMP::remove_ref_cv_t<FastMatrix_>::register_type determinant;
		return _fast_matrix_underlying::_make_inverse_to_stage<_fast_matrix_underlying::_inverse_stage_flag::COFACTORS, false>
		(
			std::forward<FastMatrix_>(in_matrix_),
			determinant
		);
	}

	/// <summary>
	/// <para> Calculates the matrix of cofactors to the input square-dimensioned FastMatrix. </para>
	/// <para> The calculated determinant will be output to the provided arithmetic scalar reference. </para>
	/// </summary>
	/// <param name="in_matrix_">FastMatrix with square dimensions (i.e. `num_columns == num_rows`) to calculate the minors of.</param>
	/// <returns>Matrix of cofactors to the passed Matrix.</returns>
	template<EmuConcepts::EmuFastMatrixSquare FastMatrix_, EmuConcepts::Arithmetic Determinant_>
	requires (!std::is_const_v<Determinant_>)
	[[nodiscard]] constexpr inline auto fast_matrix_cofactors(FastMatrix_&& in_matrix_, Determinant_& out_determinant_)
		-> typename EmuCore::TMP::remove_ref_cv<FastMatrix_>::type
	{
		using _in_fast_mat_uq = typename EmuCore::TMP::remove_ref_cv<FastMatrix_>::type;
		using _offloader = _fast_matrix_underlying::_register_to_scalar_offloader
		<
			typename _in_fast_mat_uq::register_type,
			Determinant_,
			0,
			_in_fast_mat_uq::per_element_width
		>;
		_offloader determinant_offloader(out_determinant_);
		return _fast_matrix_underlying::_make_inverse_to_stage<_fast_matrix_underlying::_inverse_stage_flag::COFACTORS, true>
		(
			std::forward<FastMatrix_>(in_matrix_),
			determinant_offloader.registerToOffload
		);
	}

	/// <summary>
	/// <para> Calculates the matrix of cofactors to the input square-dimensioned FastMatrix. </para>
	/// <para> The calculated determinant will be output as a SIMD register via the passed register reference. </para>
	/// </summary>
	/// <param name="in_matrix_">FastMatrix with square dimensions (i.e. `num_columns == num_rows`) to calculate the minors of.</param>
	/// <returns>Matrix of cofactors to the passed Matrix.</returns>
	template<EmuConcepts::EmuFastMatrixSquare FastMatrix_>
	[[nodiscard]] constexpr inline auto fast_matrix_cofactors
	(
		FastMatrix_&& in_matrix_,
		typename EmuCore::TMP::remove_ref_cv_t<FastMatrix_>::register_type out_determinant_
	) -> typename EmuCore::TMP::remove_ref_cv<FastMatrix_>::type
	{
		return _fast_matrix_underlying::_make_inverse_to_stage<_fast_matrix_underlying::_inverse_stage_flag::COFACTORS, true>
		(
			std::forward<FastMatrix_>(in_matrix_),
			out_determinant_
		);
	}
#pragma endregion

#pragma region ADJUGATE_FUNCS
	/// <summary>
	/// <para> Calculates the adjugate of the input square-dimensioned FastMatrix. </para>
	/// </summary>
	/// <param name="in_matrix_">FastMatrix with square dimensions (i.e. `num_columns == num_rows`) to calculate the minors of.</param>
	/// <returns>Matrix of cofactors to the passed Matrix.</returns>
	template<EmuConcepts::EmuFastMatrixSquare FastMatrix_>
	[[nodiscard]] constexpr inline auto fast_matrix_adjugate(FastMatrix_&& in_matrix_)
		-> typename EmuCore::TMP::remove_ref_cv<FastMatrix_>::type
	{
		typename EmuCore::TMP::remove_ref_cv_t<FastMatrix_>::register_type determinant;
		return _fast_matrix_underlying::_make_inverse_to_stage<_fast_matrix_underlying::_inverse_stage_flag::ADJUGATE, false>
		(
			std::forward<FastMatrix_>(in_matrix_),
			determinant
		);
	}

	/// <summary>
	/// <para> Calculates the adjugate of the input square-dimensioned FastMatrix. </para>
	/// <para> The calculated determinant will be output to the provided arithmetic scalar reference. </para>
	/// </summary>
	/// <param name="in_matrix_">FastMatrix with square dimensions (i.e. `num_columns == num_rows`) to calculate the minors of.</param>
	/// <returns>Matrix of cofactors to the passed Matrix.</returns>
	template<EmuConcepts::EmuFastMatrixSquare FastMatrix_, EmuConcepts::Arithmetic Determinant_>
	requires (!std::is_const_v<Determinant_>)
	[[nodiscard]] constexpr inline auto fast_matrix_adjugate(FastMatrix_&& in_matrix_, Determinant_& out_determinant_)
		-> typename EmuCore::TMP::remove_ref_cv<FastMatrix_>::type
	{
		using _in_fast_mat_uq = typename EmuCore::TMP::remove_ref_cv<FastMatrix_>::type;
		using _offloader = _fast_matrix_underlying::_register_to_scalar_offloader
		<
			typename _in_fast_mat_uq::register_type,
			Determinant_,
			0,
			_in_fast_mat_uq::per_element_width
		>;
		_offloader determinant_offloader(out_determinant_);
		return _fast_matrix_underlying::_make_inverse_to_stage<_fast_matrix_underlying::_inverse_stage_flag::ADJUGATE, true>
		(
			std::forward<FastMatrix_>(in_matrix_),
			determinant_offloader.registerToOffload
		);
	}

	/// <summary>
	/// <para> Calculates the adjugate of the input square-dimensioned FastMatrix. </para>
	/// <para> The calculated determinant will be output as a SIMD register via the passed register reference. </para>
	/// </summary>
	/// <param name="in_matrix_">FastMatrix with square dimensions (i.e. `num_columns == num_rows`) to calculate the minors of.</param>
	/// <returns>Matrix of cofactors to the passed Matrix.</returns>
	template<EmuConcepts::EmuFastMatrixSquare FastMatrix_>
	[[nodiscard]] constexpr inline auto fast_matrix_adjugate
	(
		FastMatrix_&& in_matrix_,
		typename EmuCore::TMP::remove_ref_cv_t<FastMatrix_>::register_type out_determinant_
	) -> typename EmuCore::TMP::remove_ref_cv<FastMatrix_>::type
	{
		return _fast_matrix_underlying::_make_inverse_to_stage<_fast_matrix_underlying::_inverse_stage_flag::ADJUGATE, true>
		(
			std::forward<FastMatrix_>(in_matrix_),
			out_determinant_
		);
	}
#pragma endregion
#endif
}

#endif
