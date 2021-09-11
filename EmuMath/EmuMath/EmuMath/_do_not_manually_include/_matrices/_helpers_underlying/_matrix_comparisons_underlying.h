#ifndef EMU_MATH__UNDERLYING_MATRIX_COMPARISONS_H_INC_
#define EMU_MATH__UNDERLYING_MATRIX_COMPARISONS_H_INC_ 1

#include "_common_underlying_matrix_helper_includes.h"
#include "_matrix_gets_underlying.h"

namespace EmuMath::Helpers::_underlying_matrix_funcs
{
	template<std::size_t ColumnIndex_, std::size_t RowIndex_, class LhsMatrix_, class RhsMatrix_, class Cmp_, class Joiner_>
	constexpr inline bool _matrix_cmp_matrix_until_one_ends(const LhsMatrix_& lhs_, const RhsMatrix_& rhs_, Cmp_& cmp_, Joiner_& joiner_, const bool& default_result_)
	{
		if constexpr ((ColumnIndex_ < LhsMatrix_::num_columns) && (ColumnIndex_ < RhsMatrix_::num_columns))
		{
			if constexpr (RowIndex_ < LhsMatrix_::num_rows && RowIndex_ < RhsMatrix_::num_rows)
			{
				return joiner_
				(
					cmp_(_get_matrix_data<ColumnIndex_, RowIndex_>(lhs_), _get_matrix_data<ColumnIndex_, RowIndex_>(rhs_)),
					_matrix_cmp_matrix_until_one_ends<ColumnIndex_, RowIndex_ + 1>(lhs_, rhs_, cmp_, joiner_, default_result_)
				);
			}
			else
			{
				return _matrix_cmp_matrix_until_one_ends<ColumnIndex_ + 1, 0, LhsMatrix_, RhsMatrix_, Cmp_, Joiner_>(lhs_, rhs_, cmp_, joiner_, default_result_);
			}
		}
		else
		{
			return default_result_;
		}
	}

	template<std::size_t ColumnIndex_, std::size_t RowIndex_, class LhsMatrix_, class RhsMatrix_, class Cmp_, class Joiner_>
	constexpr inline bool _matrix_cmp_matrix_do_all_indices(const LhsMatrix_& lhs_, const RhsMatrix_& rhs_, Cmp_& cmp_, Joiner_& joiner_, const bool& default_result_)
	{
		if constexpr((ColumnIndex_ < LhsMatrix_::num_columns) || (ColumnIndex_ < RhsMatrix_::num_columns))
		{
			if constexpr (RowIndex_ < LhsMatrix_::num_rows || RowIndex_ < RhsMatrix_::num_rows)
			{
				return joiner_
				(
					cmp_(_get_matrix_theoretical_data<ColumnIndex_, RowIndex_>(lhs_), _get_matrix_theoretical_data<ColumnIndex_, RowIndex_>(rhs_)),
					_matrix_cmp_matrix_do_all_indices<ColumnIndex_, RowIndex_ + 1, LhsMatrix_, RhsMatrix_, Cmp_, Joiner_>(lhs_, rhs_, cmp_, joiner_, default_result_)
				);
			}
			else
			{
				return _matrix_cmp_matrix_do_all_indices<ColumnIndex_ + 1, 0, LhsMatrix_, RhsMatrix_, Cmp_, Joiner_>(lhs_, rhs_, cmp_, joiner_, default_result_);
			}
		}
		else
		{
			return default_result_;
		}
	}

	template<std::size_t ColumnIndex_, std::size_t RowIndex_, class LhsMatrix_, class RhsScalar_, class Cmp_, class Joiner_>
	constexpr inline bool _matrix_cmp_scalar(const LhsMatrix_& lhs_, const RhsScalar_& rhs_, Cmp_& cmp_, Joiner_& joiner_, const bool& default_result_)
	{
		if constexpr ((ColumnIndex_ < LhsMatrix_::num_columns))
		{
			if constexpr (RowIndex_ < LhsMatrix_::num_rows)
			{
				return joiner_
				(
					cmp_(_get_matrix_data<ColumnIndex_, RowIndex_>(lhs_), rhs_),
					_matrix_cmp_scalar<ColumnIndex_, RowIndex_ + 1, LhsMatrix_, RhsScalar_, Cmp_, Joiner_>(lhs_, rhs_, cmp_, joiner_, default_result_)
				);
			}
			else
			{
				return _matrix_cmp_scalar<ColumnIndex_ + 1, 0, LhsMatrix_, RhsScalar_, Cmp_, Joiner_>(lhs_, rhs_, cmp_, joiner_, default_result_);
			}
		}
		else
		{
			return default_result_;
		}
	}

	template<bool CompareAllIndices_, template<class Lhs__, class Rhs__> class CmpTemplate_, class LhsMatrix_, class Rhs_>
	constexpr inline bool _matrix_cmp_all(const LhsMatrix_& lhs_, const Rhs_& rhs_)
	{
		using Joiner_ = std::logical_and<bool>;
		Joiner_ joiner_ = Joiner_();
		if constexpr (EmuMath::TMP::is_emu_matrix_v<Rhs_>)
		{
			using Cmp_ = CmpTemplate_<typename LhsMatrix_::raw_value_type, typename Rhs_::raw_value_type>;
			Cmp_ cmp_ = Cmp_();
			if constexpr (CompareAllIndices_)
			{
				return _matrix_cmp_matrix_do_all_indices<0, 0, LhsMatrix_, Rhs_, Cmp_, Joiner_>(lhs_, rhs_, cmp_, joiner_, true);
			}
			else
			{
				return _matrix_cmp_matrix_until_one_ends<0, 0, LhsMatrix_, Rhs_, Cmp_, Joiner_>(lhs_, rhs_, cmp_, joiner_, true);
			}
		}
		else
		{
			using Cmp_ = CmpTemplate_<typename LhsMatrix_::raw_value_type, Rhs_>;
			Cmp_ cmp_ = Cmp_();
			return _matrix_cmp_scalar<0, 0, LhsMatrix_, Rhs_, Cmp_, Joiner_>(lhs_, rhs_, cmp_, joiner_, true);
		}
	}

	template<bool CompareAllIndices_, template<class Lhs__, class Rhs__> class CmpTemplate_, class LhsMatrix_, class Rhs_>
	constexpr inline bool _matrix_cmp_any(const LhsMatrix_& lhs_, const Rhs_& rhs_)
	{
		using Joiner_ = std::logical_or<bool>;
		Joiner_ joiner_ = Joiner_();
		if constexpr (EmuMath::TMP::is_emu_matrix_v<Rhs_>)
		{
			using Cmp_ = CmpTemplate_<typename LhsMatrix_::raw_value_type, typename Rhs_::raw_value_type>;
			Cmp_ cmp_ = Cmp_();
			if constexpr (CompareAllIndices_)
			{
				return _matrix_cmp_matrix_do_all_indices<0, 0, LhsMatrix_, Rhs_, Cmp_, Joiner_>(lhs_, rhs_, cmp_, joiner_, false);
			}
			else
			{
				return _matrix_cmp_matrix_until_one_ends<0, 0, LhsMatrix_, Rhs_, Cmp_, Joiner_>(lhs_, rhs_, cmp_, joiner_, false);
			}
		}
		else
		{
			using Cmp_ = CmpTemplate_<typename LhsMatrix_::raw_value_type, Rhs_>;
			Cmp_ cmp_ = Cmp_();
			return _matrix_cmp_scalar<0, 0, LhsMatrix_, Rhs_, Cmp_, Joiner_>(lhs_, rhs_, cmp_, joiner_, false);
		}
	}
}

#endif