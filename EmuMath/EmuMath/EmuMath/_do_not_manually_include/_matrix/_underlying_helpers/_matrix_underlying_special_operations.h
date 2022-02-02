#ifndef EMU_MATH_MATRIX_UNDERLYING_SPECIAL_OPERATIONS_H_INC_
#define EMU_MATH_MATRIX_UNDERLYING_SPECIAL_OPERATIONS_H_INC_ 1

#include "_matrix_underlying_copy.h"
#include "_matrix_tmp.h"

namespace EmuMath::Helpers::_matrix_underlying
{
	template<class OutMatrix_, class InMatrix_, bool DoAssertions_, std::size_t...OutColumnIndices_, std::size_t...OutRowIndices_>
	[[nodiscard]] constexpr inline bool _matrix_transpose_is_valid
	(
		std::index_sequence<OutColumnIndices_...> out_column_indices_,
		std::index_sequence<OutRowIndices_...> out_row_indices_
	)
	{
		using out_matrix_uq = EmuCore::TMP::remove_ref_cv_t<OutMatrix_>;
		constexpr bool copy_success_ = (... && _matrix_create_from_matrix_index_is_valid<out_matrix_uq, InMatrix_, DoAssertions_, OutRowIndices_, OutColumnIndices_>());
		if constexpr (copy_success_)
		{
			constexpr bool is_constructible_ = std::is_constructible_v
			<
				out_matrix_uq,
				decltype(_matrix_create_out_from_index<out_matrix_uq, InMatrix_, OutRowIndices_, OutColumnIndices_>(std::declval<InMatrix_>()))...
			>;
			if constexpr (is_constructible_)
			{
				return true;
			}
			else
			{
				static_assert(!DoAssertions_, "Invalid EmuMath Matrix Transpose output: The output Matrix cannot be constructed from one stored_type argument per contained element.");
				return false;
			}
		}
		else
		{
			static_assert(!DoAssertions_, "Invalid EmuMath Matrix Transpose Parameters: The output Matrix's stored_type cannot be created from the input Matrix for all indices.");
			return false;
		}
	}

	template<class OutMatrix_, class InMatrix_, bool DoAssertions_>
	[[nodiscard]] constexpr inline bool _matrix_transpose_is_valid()
	{
		using out_matrix_uq = EmuCore::TMP::remove_ref_cv_t<OutMatrix_>;
		using out_indices = EmuMath::TMP::make_full_matrix_index_sequences<out_matrix_uq>;
		using column_index_sequence = typename out_indices::column_index_sequence;
		using row_index_sequence = typename out_indices::row_index_sequence;
		return _matrix_transpose_is_valid<out_matrix_uq, InMatrix_, true>(column_index_sequence(), row_index_sequence());
	}

	template<class OutMatrix_, class InMatrix_, std::size_t...OutColumnIndices_, std::size_t...OutRowIndices_>
	[[nodiscard]] constexpr inline OutMatrix_ _matrix_transpose_execution
	(
		std::index_sequence<OutColumnIndices_...> out_column_indices_,
		std::index_sequence<OutRowIndices_...> out_row_indices_,
		InMatrix_&& in_matrix_
	)
	{
		if constexpr (_matrix_transpose_is_valid<OutMatrix_, InMatrix_, true>(std::index_sequence<OutColumnIndices_...>(), std::index_sequence<OutRowIndices_...>()))
		{
			// Disable warning as intended use will never duplicate an index access, so we are never actually moving from the same object
#pragma warning(push)
#pragma warning(disable: 26800)
			return OutMatrix_
			(
				_matrix_create_out_from_index<OutMatrix_, InMatrix_, OutRowIndices_, OutColumnIndices_>(std::forward<InMatrix_>(in_matrix_))...
			);
#pragma warning(pop)
		}
		else
		{
			static_assert
			(
				EmuCore::TMP::get_false<OutMatrix_>(),
				"Could not successfully determine the transpose of an EmuMath Matrix."
			);
		}
	}

	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, bool OutColumnMajor_, class InMatrix_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_> _matrix_transpose(InMatrix_&& in_matrix_)
	{
		using out_matrix = EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>;
		using out_indices = EmuMath::TMP::make_full_matrix_index_sequences<out_matrix>;
		using column_index_sequence = typename out_indices::column_index_sequence;
		using row_index_sequence = typename out_indices::row_index_sequence;
		return _matrix_transpose_execution<out_matrix, InMatrix_>(column_index_sequence(), row_index_sequence(), std::forward<InMatrix_>(in_matrix_));
	}
}

#endif
