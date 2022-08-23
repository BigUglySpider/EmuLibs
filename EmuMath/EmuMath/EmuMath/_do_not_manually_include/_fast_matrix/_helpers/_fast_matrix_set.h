#ifndef EMU_MATH_FAST_MATRIX_SET_H_INC_
#define EMU_MATH_FAST_MATRIX_SET_H_INC_ 1

#include "_common_fast_matrix_helper_includes.h"

namespace EmuMath::Helpers
{
	/// <summary>
	/// <para> Copies the array of major Vectors of the passed Matrix (or moves them if it is not an lvalue reference). </para>
	/// </summary>
	/// <param name="matrix_">EmuMath Fast Matrix to copy or move the major Vectors of.</param>
	/// <param name="major_index_sequence_">Index sequence of major indices to be copied/moved. This should be a sequence of all of Matrix_'s major indices.</param>
	/// <returns>Copy (or moved result) of the passed Matrix's array of major Vectors.</returns>
	template<class Matrix_, std::size_t...MajorIndices_>
	requires EmuConcepts::EmuFastMatrix<Matrix_>
	[[nodiscard]] constexpr inline auto fast_matrix_copy_data_type(Matrix_&& matrix_, std::index_sequence<MajorIndices_...> major_index_sequence_)
		-> typename EmuCore::TMP::remove_ref_cv_t<Matrix_>::data_type
	{
		if constexpr (std::is_lvalue_reference_v<Matrix_>)
		{
			return typename EmuCore::TMP::remove_ref_cv_t<Matrix_>::data_type({ matrix_.major_vectors[MajorIndices_]... });
		}
		else
		{
			// False positive warnings if `matrix_` is rvalue, since we're moving component data sequentially w/no repeats
#pragma warning(push)
#pragma warning(disable: 26800)
			return typename EmuCore::TMP::remove_ref_cv_t<Matrix_>::data_type({ std::move(matrix_.major_vectors[MajorIndices_])... });
#pragma warning(pop)
		}		
	}

	/// <summary>
	/// <para> Moves the array of major Vectors of the passed Matrix. </para>
	/// </summary>
	/// <param name="matrix_">EmuMath Fast Matrix to move the major Vectors of.</param>
	/// <param name="major_index_sequence_">Index sequence of major indices to be move. This should be a sequence of all of Matrix_'s major indices.</param>
	/// <returns>Moved result of the passed Matrix's array of major Vectors.</returns>
	template<class Matrix_, std::size_t...MajorIndices_>
	requires EmuConcepts::EmuFastMatrix<Matrix_>
	[[nodiscard]] constexpr inline auto fast_matrix_move_data_type(Matrix_&& matrix_, std::index_sequence<MajorIndices_...> major_index_sequence_)
		-> typename EmuCore::TMP::remove_ref_cv_t<Matrix_>::data_type
	{
#pragma warning(push)
#pragma warning(disable: 26800)
		return typename EmuCore::TMP::remove_ref_cv_t<Matrix_>::data_type({ std::move(matrix_.major_vectors[MajorIndices_])... });
#pragma warning(pop)
	}

	/// <summary>
	/// <para> Creates an array of major Vectors for a FastMatrix of the specified `OutMatrix_` type. </para>
	/// <para> Output registers will be loaded or set via respective data within the passed Matrix. </para>
	/// <para> 
	///		Optimised loads will be used where possible if the input Matrix has the same `stored_type` as the output FastMatrix type's `value_type`, 
	///		and it shares the same major storage order. Otherwise, only sets will be used.
	/// </para>
	/// </summary>
	/// <param name="scalar_matrix_">Normal EmuMath Matrix to load or set the new FastMatrix's registers via.</param>
	/// <returns>Array of major Vectors used by an EmuMath FastMatrix of the specified `OutMatrix_` type.</returns>
	template<EmuConcepts::EmuFastMatrix OutMatrix_, EmuConcepts::EmuMatrix ScalarMatrix_, std::size_t...MajorIndices_>
	[[nodiscard]] constexpr inline auto fast_matrix_make_majors_from_scalar_matrix
	(
		ScalarMatrix_&& scalar_matrix_,
		std::index_sequence<MajorIndices_...> major_index_sequence_
	) -> typename EmuCore::TMP::remove_ref_cv_t<OutMatrix_>::data_type
	{
		using out_mat_uq = typename EmuCore::TMP::remove_ref_cv<OutMatrix_>::type;
		using in_mat_uq = typename EmuCore::TMP::remove_ref_cv<ScalarMatrix_>::type;

		constexpr bool matching_major = out_mat_uq::is_column_major == in_mat_uq::is_column_major;
		constexpr bool matching_type = std::is_same_v
		<
			typename out_mat_uq::value_type, 
			typename std::remove_cv<typename in_mat_uq::stored_type>::type
		>;

		if constexpr (matching_major && matching_type)
		{
			return _fast_matrix_underlying::_load_from_scalar_matrix<OutMatrix_, ScalarMatrix_, MajorIndices_...>
			(
				std::forward<ScalarMatrix_>(scalar_matrix_)
			);
		}
		else
		{
			// Can't load as different contiguous order and/or contained type, so fallback to setting
			using non_major_index_sequence = std::make_index_sequence<out_mat_uq::num_non_major_elements>;
#pragma warning(push)
#pragma warning(disable: 26800)
			return typename out_mat_uq::data_type
			({
				_fast_matrix_underlying::_make_major_vector_from_scalar_matrix<MajorIndices_, OutMatrix_>
				(
					std::forward<ScalarMatrix_>(scalar_matrix_),
					non_major_index_sequence()
				)...
			});
#pragma warning(pop)
		}
	}
}

#endif
