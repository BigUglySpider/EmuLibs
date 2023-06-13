#ifndef EMU_MATH_MATRIX_UNDERLYING_CMP_H_INC_
#define EMU_MATH_MATRIX_UNDERLYING_CMP_H_INC_ 1

#include "_matrix_tmp.h"
#include "_matrix_underlying_get.h"

namespace EmuMath::Helpers::_matrix_underlying
{
	template<EmuConcepts::EmuMatrix LhsMatrix_, class Cmp_, std::size_t...ColumnIndices_, std::size_t...RowIndices_, class...Args_>
	[[nodiscard]] constexpr inline bool _matrix_cmp_and
	(
		LhsMatrix_&& lhs_matrix_,
		Cmp_& cmp_,
		std::index_sequence<ColumnIndices_...> column_indices_,
		std::index_sequence<RowIndices_...> row_indices_,
		Args_&&...args_
	)
	{
		EMU_CORE_MSVC_PUSH_WARNING_STACK
		EMU_CORE_MSVC_DISABLE_WARNING(EMU_CORE_WARNING_BAD_MOVE)
		return
		(
			... &&
			cmp_
			(
				_matrix_get_theoretical<ColumnIndices_, RowIndices_>(lhs_matrix_),
				_matrix_get_arg<ColumnIndices_, RowIndices_, LhsMatrix_>(std::forward<Args_>(args_))...
			)
		);
		EMU_CORE_MSVC_POP_WARNING_STACK
	}

	template<EmuConcepts::EmuMatrix LhsMatrix_, class Cmp_, std::size_t...ColumnIndices_, std::size_t...RowIndices_, class...Args_>
	[[nodiscard]] constexpr inline bool _matrix_cmp_or
	(
		LhsMatrix_&& lhs_matrix_,
		Cmp_& cmp_,
		std::index_sequence<ColumnIndices_...> column_indices_,
		std::index_sequence<RowIndices_...> row_indices_,
		Args_&&...args_
	)
	{
		EMU_CORE_MSVC_PUSH_WARNING_STACK
		EMU_CORE_MSVC_DISABLE_WARNING(EMU_CORE_WARNING_BAD_MOVE)
		return
		(
			... ||
			cmp_
			(
				_matrix_get_theoretical<ColumnIndices_, RowIndices_>(lhs_matrix_),
				_matrix_get_arg<ColumnIndices_, RowIndices_, LhsMatrix_>(std::forward<Args_>(args_))...
			)
		);
		EMU_CORE_MSVC_POP_WARNING_STACK
	}

	template<bool IsAnd_, std::size_t BeginColumn_, std::size_t BeginRow_, std::size_t EndColumn_, std::size_t EndRow_, EmuConcepts::EmuMatrix LhsMatrix_, class Cmp_, class...Args_>
	[[nodiscard]] constexpr inline bool _matrix_cmp_range(Cmp_&& cmp_, LhsMatrix_&& lhs_matrix_, Args_&&...args_)
	{
		using indices = EmuMath::TMP::make_ranged_matrix_index_sequences<BeginColumn_, EndColumn_, BeginRow_, EndRow_, std::remove_cvref_t<LhsMatrix_>::is_column_major>;
		using column_indices = typename indices::column_index_sequence;
		using row_indices = typename indices::row_index_sequence;
		if constexpr (IsAnd_)
		{
			return _matrix_cmp_and
			(
				std::forward<LhsMatrix_>(lhs_matrix_),
				EmuCore::TMP::lval_ref_cast<Cmp_>(std::forward<Cmp_>(cmp_)),
				column_indices(),
				row_indices(),
				std::forward<Args_>(args_)...
			);
		}
		else
		{
			return _matrix_cmp_or
			(
				std::forward<LhsMatrix_>(lhs_matrix_),
				EmuCore::TMP::lval_ref_cast<Cmp_>(std::forward<Cmp_>(cmp_)),
				column_indices(),
				row_indices(),
				std::forward<Args_>(args_)...
			);
		}
	}

	template<bool IncludeNonContained_, bool IsAnd_, EmuConcepts::EmuMatrix LhsMatrix_, class Cmp_, class...Args_>
	[[nodiscard]] constexpr inline bool _matrix_cmp(Cmp_&& cmp_, LhsMatrix_&& lhs_matrix_, Args_&&...args_)
	{
		constexpr std::size_t num_columns =
		(
			IncludeNonContained_ ?
			EmuCore::TMP::greatest_constant_v<std::size_t, _matrix_arg_num_columns<LhsMatrix_>(), _matrix_arg_num_columns<Args_>()...> :
			_matrix_arg_num_columns<LhsMatrix_>()
		);
		constexpr std::size_t num_rows =
		(
			IncludeNonContained_ ?
			EmuCore::TMP::greatest_constant_v<std::size_t, _matrix_arg_num_columns<LhsMatrix_>(), _matrix_arg_num_rows<Args_>()...> :
			_matrix_arg_num_rows<LhsMatrix_>()
		);

		using indices = EmuMath::TMP::make_matrix_index_sequences<typename std::remove_cvref<LhsMatrix_>::type, std::make_index_sequence<num_columns>, std::make_index_sequence<num_rows>>;
		using column_indices = typename indices::column_index_sequence;
		using row_indices = typename indices::row_index_sequence;
		if constexpr (IsAnd_)
		{
			return _matrix_cmp_and
			(
				std::forward<LhsMatrix_>(lhs_matrix_),
				EmuCore::TMP::lval_ref_cast<Cmp_>(std::forward<Cmp_>(cmp_)),
				column_indices(),
				row_indices(),
				std::forward<Args_>(args_)...
			);
		}
		else
		{
			return _matrix_cmp_and
			(
				std::forward<LhsMatrix_>(lhs_matrix_),
				EmuCore::TMP::lval_ref_cast<Cmp_>(std::forward<Cmp_>(cmp_)),
				column_indices(),
				row_indices(),
				std::forward<Args_>(args_)...
			);
		}
	}
}

#endif
