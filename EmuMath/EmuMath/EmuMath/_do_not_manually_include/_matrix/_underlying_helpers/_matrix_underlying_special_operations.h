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
EMU_CORE_MSVC_PUSH_WARNING_STACK
EMU_CORE_MSVC_DISABLE_WARNING(EMU_CORE_WARNING_BAD_MOVE)
			return OutMatrix_
			(
				_matrix_create_out_from_index<OutMatrix_, InMatrix_, OutRowIndices_, OutColumnIndices_>(std::forward<InMatrix_>(in_matrix_))...
			);
EMU_CORE_MSVC_POP_WARNING_STACK
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

	template<std::size_t ColumnIndex_, std::size_t RowIndex_, class Matrix_>
	[[nodiscard]] constexpr inline typename EmuCore::TMP::remove_ref_cv_t<Matrix_>::stored_type _matrix_identity_element()
	{
		if constexpr (ColumnIndex_ == RowIndex_)
		{
			using stored_type = typename EmuCore::TMP::remove_ref_cv_t<Matrix_>::stored_type;
			if constexpr (EmuCore::TMP::valid_construct_or_cast<stored_type, decltype(1)>())
			{
				return EmuCore::TMP::construct_or_cast<stored_type>(1);
			}
			else
			{
				static_assert
				(
					EmuCore::TMP::get_false<Matrix_>(),
					"Attempted to make an Identity Matrix for a specified EmuMath Matrix type, but the provided Matrix's stored_type cannot be constructed or static_cast to with an argument of 1."
				);
			}
		}
		else
		{
			return _matrix_get_non_contained<Matrix_>();
		}
	}

	template<std::size_t ColumnIndex_, std::size_t RowIndex_, class Matrix_>
	constexpr inline void _matrix_assign_identity_element(Matrix_& matrix_)
	{
		using get_result = decltype(_matrix_get<ColumnIndex_, RowIndex_>(matrix_));
		if constexpr (ColumnIndex_ == RowIndex_)
		{
			using value_uq = typename EmuCore::TMP::remove_ref_cv_t<Matrix_>::value_type_uq;
			if constexpr (EmuCore::TMP::valid_assign_direct_or_cast<value_uq, decltype(1), get_result>())
			{
				EmuCore::TMP::assign_direct_or_cast<value_uq>(_matrix_get<ColumnIndex_, RowIndex_>(matrix_), 1);
			}
			else
			{
				static_assert
				(
					EmuCore::TMP::get_false<Matrix_>(),
					"Attempted to assign the Identity Matrix to a provided EmuMath Matrix, but the Matrix cannot have one of its main diagonal elements assigned by a value of 1, or the value of 1 static_cast to its value_type_uq."
				);
			}
		}
		else
		{
			if constexpr (std::is_assignable_v<get_result, decltype(0)>)
			{
				_matrix_get<ColumnIndex_, RowIndex_>(matrix_) = 0;
			}
			else if constexpr (std::is_assignable_v<get_result, decltype(_matrix_get_non_contained<Matrix_>())>)
			{
				_matrix_get<ColumnIndex_, RowIndex_>(matrix_) = _matrix_get_non_contained<Matrix_>();
			}
			else
			{
				static_assert
				(
					EmuCore::TMP::get_false<Matrix_>(),
					"Attempted to assign the Identity Matrix to a provided EmuMath Matrix, but the Matrix cannot have one of its non-main-diagonal elements assigned by a value of 0, or its implied-zero non-contained value."
				);
			}
		}
	}

	template<class Matrix_, std::size_t...ColumnIndices_, std::size_t...RowIndices_>
	[[nodiscard]] constexpr inline Matrix_ _matrix_make_identity(std::index_sequence<ColumnIndices_...> column_indices_, std::index_sequence<RowIndices_...> row_indices_)
	{
		if constexpr (std::is_constructible_v<Matrix_, decltype(_matrix_identity_element<ColumnIndices_, RowIndices_, Matrix_>())...>)
		{
			return Matrix_(_matrix_identity_element<ColumnIndices_, RowIndices_, Matrix_>()...);
		}
		else
		{
			static_assert
			(
				EmuCore::TMP::get_false<Matrix_>(),
				"Attempted to make an Identy Matrix for a specified EmuMath Matrix type, but the provided Matrix_ cannot be constructed with a value argument of its stored_type per element."
			);
		}
	}

	template<class Matrix_, std::size_t...ColumnIndices_, std::size_t...RowIndices_>
	constexpr inline void _matrix_assign_identity(Matrix_& matrix_, std::index_sequence<ColumnIndices_...> column_indices_, std::index_sequence<RowIndices_...> row_indices_)
	{
		(_matrix_assign_identity_element<ColumnIndices_, RowIndices_>(matrix_), ...);
	}

	template<std::size_t NumColumns_, std::size_t NumRows_, typename T_, bool ColumnMajor_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_> _matrix_identity()
	{
		using matrix_type = EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>;
		using indices = EmuMath::TMP::make_full_matrix_index_sequences<matrix_type>;
		return _matrix_make_identity<matrix_type>(typename indices::column_index_sequence(), typename indices::row_index_sequence());
	}

	template<std::size_t NumColumns_, std::size_t NumRows_, typename T_, bool ColumnMajor_>
	constexpr inline void _matrix_identity(EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>& matrix_)
	{
		using matrix_type = EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>;
		using indices = EmuMath::TMP::make_full_matrix_index_sequences<matrix_type>;
		return _matrix_assign_identity(matrix_, typename indices::column_index_sequence(), typename indices::row_index_sequence());
	}

	template<std::size_t NumColumns_, std::size_t NumRows_, typename T_, bool ColumnMajor_>
	constexpr inline auto _matrix_inverse_gauss_jordan(const EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>& matrix_)
		-> EmuMath::Matrix<NumColumns_, NumRows_, typename EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>::value_type_uq, ColumnMajor_>
	{

	}
}

#endif
