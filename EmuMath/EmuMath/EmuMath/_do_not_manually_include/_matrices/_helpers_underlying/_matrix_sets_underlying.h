#ifndef EMU_MATH__UNDERLYING_MATRIX_SETS_H_INC_
#define EMU_MATH__UNDERLYING_MATRIX_SETS_H_INC_ 1

#include "_common_underlying_matrix_helper_includes.h"
#include "_matrix_gets_underlying.h"

namespace EmuMath::Helpers::_underlying_matrix_funcs
{
	
	template<std::size_t ColumnIndex_, std::size_t RowIndex_, class Matrix_, typename Arg_>
	constexpr inline Matrix_& _matrix_set(Matrix_& matrix_, Arg_& arg_)
	{
		if constexpr (Matrix_::is_column_major)
		{
			auto& column_ = matrix_.template GetMajor<ColumnIndex_>();
			column_.template Set<RowIndex_>(arg_);
		}
		else
		{
			auto& row_ = matrix_.template GetMajor<RowIndex_>();
			row_.template Set<ColumnIndex_>(arg_);
		}
		return matrix_;
	}
	template<std::size_t ColumnIndex_, std::size_t RowIndex_, class Matrix_, typename Arg_>
	constexpr inline Matrix_& _matrix_set(Matrix_& matrix_, const Arg_& arg_)
	{
		if constexpr (Matrix_::is_column_major)
		{
			auto& column_ = matrix_.template GetMajor<ColumnIndex_>();
			column_.template Set<RowIndex_>(arg_);
		}
		else
		{
			auto& row_ = matrix_.template GetMajor<RowIndex_>();
			row_.template Set<ColumnIndex_>(arg_);
		}
		return matrix_;
	}

	template<std::size_t Index_, class Matrix_, typename Arg_>
	constexpr inline Matrix_& _matrix_set_trace_region(Matrix_& matrix_,  Arg_& arg_)
	{
		if constexpr ((Index_ < Matrix_::num_columns) && (Index_ < Matrix_::num_rows))
		{
			matrix_.template GetMajor<Index_>().template Set<Index_>(arg_);
			_matrix_set_trace_region<Index_ + 1, Matrix_, Arg_>(matrix_, arg_);
		}
		return matrix_;
	}
	template<std::size_t Index_, class Matrix_, typename Arg_>
	constexpr inline Matrix_& _matrix_set_trace_region(Matrix_& matrix_, const Arg_& arg_)
	{
		if constexpr ((Index_ < Matrix_::num_columns) && (Index_ < Matrix_::num_rows))
		{
			matrix_.template GetMajor<Index_>().template Set<Index_>(arg_);
			_matrix_set_trace_region<Index_ + 1, Matrix_, Arg_>(matrix_, arg_);
		}
		return matrix_;
	}

	template<std::size_t ColumnIndex_, std::size_t RowIndex_, class LhsMatrix_, typename RhsScalar_>
	constexpr inline void _matrix_copy_scalar_to_column(LhsMatrix_& lhs_, const RhsScalar_& rhs_)
	{
		if constexpr (ColumnIndex_ < LhsMatrix_::num_columns)
		{
			if constexpr (RowIndex_ < LhsMatrix_::num_rows)
			{
				using lhs_value = typename LhsMatrix_::value_type;
				constexpr bool is_same_type = std::is_same_v<lhs_value, std::remove_cv_t<std::remove_reference_t<RhsScalar_>>>;
				static_assert
				(
					is_same_type || EmuCore::TMP::is_static_castable_v<RhsScalar_, lhs_value>,
					"Attempted to copy a type to a matrix which cannot be converted to the matrix's value_type."
				);
				if constexpr (is_same_type)
				{
					_get_matrix_data<ColumnIndex_, RowIndex_>(lhs_) = rhs_;
				}
				else
				{
					_get_matrix_data<ColumnIndex_, RowIndex_>(lhs_) = static_cast<lhs_value>(rhs_);
				}
				_matrix_copy_scalar_to_column<ColumnIndex_, RowIndex_ + 1, LhsMatrix_, RhsScalar_>(lhs_, rhs_);
			}
		}
	}
	template<std::size_t ColumnIndex_, std::size_t RowIndex_, class LhsMatrix_, typename RhsScalar_>
	constexpr inline void _matrix_copy_scalar(LhsMatrix_& lhs_, const RhsScalar_& rhs_)
	{
		if constexpr (ColumnIndex_ < LhsMatrix_::num_columns)
		{
			if constexpr (RowIndex_ < LhsMatrix_::num_rows)
			{
				using lhs_value = typename LhsMatrix_::value_type;
				constexpr bool is_same_type = std::is_same_v<lhs_value, std::remove_cv_t<std::remove_reference_t<RhsScalar_>>>;
				static_assert
				(
					is_same_type || EmuCore::TMP::is_static_castable_v<RhsScalar_, lhs_value>,
					"Attempted to copy a type to a matrix which cannot be converted to the matrix's value_type."
				);
				if constexpr (is_same_type)
				{
					// Defer copying per column to a full column copy to avoid stack depth going too far with larger matrices
					_matrix_copy_scalar_to_column<ColumnIndex_, RowIndex_>(lhs_, rhs_);
					_matrix_copy_scalar<ColumnIndex_ + 1, 0, LhsMatrix_, RhsScalar_>(lhs_, rhs_);
				}
				else
				{
					_matrix_copy_scalar<ColumnIndex_, RowIndex_, LhsMatrix_, lhs_value>(lhs_, static_cast<lhs_value>(rhs_));
				}
			}
			else
			{
				_matrix_copy_scalar<ColumnIndex_ + 1, 0, LhsMatrix_, RhsScalar_>(lhs_, rhs_);
			}
		}
	}
	template<std::size_t ColumnIndex_, std::size_t RowIndex_, class LhsMatrix_, class RhsMatrix_>
	constexpr inline void _matrix_copy_matrix(LhsMatrix_& lhs_, const RhsMatrix_& rhs_)
	{
		if constexpr (ColumnIndex_ < LhsMatrix_::num_columns)
		{
			if constexpr (RowIndex_ < LhsMatrix_::num_rows)
			{
				using lhs_value = typename LhsMatrix_::value_type;
				using rhs_value = typename RhsMatrix_::value_type;
				static_assert
				(
					EmuCore::TMP::is_static_castable_v<rhs_value, lhs_value>,
					"Attempted to copy a matrix to another matrix, but the right-hand (source) matrix contains types which cannot be converted to those in the left-hand (destination) matrix."
				);
				if constexpr (ColumnIndex_ < RhsMatrix_::num_columns)
				{
					if constexpr (RowIndex_ < RhsMatrix_::num_rows)
					{
						_get_matrix_data<ColumnIndex_, RowIndex_>(lhs_) = static_cast<lhs_value>(_get_matrix_data<ColumnIndex_, RowIndex_>(rhs_));
						_matrix_copy_matrix<ColumnIndex_, RowIndex_ + 1, LhsMatrix_, RhsMatrix_>(lhs_, rhs_);
					}
					else
					{
						// Limit casts by copying the same default value to all rows that do not exist in rhs, and then move to next column straight away
						_matrix_copy_scalar_to_column<ColumnIndex_, RowIndex_, LhsMatrix_, lhs_value>(lhs_, static_cast<lhs_value>(rhs_value()));
						_matrix_copy_matrix<ColumnIndex_ + 1, 0, LhsMatrix_, RhsMatrix_>(lhs_, rhs_);
					}
				}
				else
				{
					// Defer the rest of copying to a scalar copy of rhs default cast to lhs value.
					// --- Since the column index has surpassed rhs columns, we will never find another rhs value, so this can improve our efficiency by only casting once
					_matrix_copy_scalar<ColumnIndex_, RowIndex_, LhsMatrix_, lhs_value>(lhs_, static_cast<lhs_value>(rhs_value()));
				}
			}
			else
			{
				_matrix_copy_matrix<ColumnIndex_ + 1, 0, LhsMatrix_, RhsMatrix_>(lhs_, rhs_);
			}
		}
	}
	template<class LhsMatrix_, class Rhs_>
	constexpr inline LhsMatrix_& _matrix_copy(LhsMatrix_& lhs_, const Rhs_& rhs_)
	{
		if constexpr (EmuMath::TMP::is_emu_matrix_v<Rhs_>)
		{
			_matrix_copy_matrix<0, 0, LhsMatrix_, Rhs_>(lhs_, rhs_);
		}
		else
		{
			_matrix_copy_scalar<0, 0, LhsMatrix_, Rhs_>(lhs_, rhs_);
		}
		return lhs_;
	}
	template<class OutMatrix_, class Src_>
	[[nodiscard]] constexpr inline OutMatrix_ _matrix_create_from_src(const Src_& src_)
	{
		OutMatrix_ out_ = OutMatrix_();
		_matrix_copy<OutMatrix_, Src_>(out_, src_);
		return out_;
	}

	template<std::size_t ColumnIndex_, std::size_t RowIndex_, class LhsMatrix_, class RhsScalar_>
	constexpr inline void _matrix_set_column_scalar(LhsMatrix_& lhs_, RhsScalar_& rhs_)
	{
		if constexpr (ColumnIndex_ < LhsMatrix_::num_columns && RowIndex_ < LhsMatrix_::num_rows)
		{
			_matrix_set<ColumnIndex_, RowIndex_>(lhs_, rhs_);
			_matrix_set_column_scalar<ColumnIndex_, RowIndex_ + 1, LhsMatrix_, RhsScalar_>(lhs_, rhs_);
		}
	}
	template<std::size_t ColumnIndex_, std::size_t RowIndex_, class LhsMatrix_, class RhsScalar_>
	constexpr inline void _matrix_set_full_scalar(LhsMatrix_& lhs_, RhsScalar_& rhs_)
	{
		if constexpr (ColumnIndex_ < LhsMatrix_::num_columns)
		{
			// Defer to column set to avoid stack depth overflowing too quickly with larger matrices
			_matrix_set_column_scalar<ColumnIndex_, RowIndex_, LhsMatrix_, RhsScalar_>(lhs_, rhs_);
			_matrix_set_full_scalar<ColumnIndex_ + 1, RowIndex_, LhsMatrix_, RhsScalar_>(lhs_, rhs_);
		}
	}
	template<std::size_t ColumnIndex_, std::size_t RowIndex_, class LhsMatrix_, class RhsMatrix_>
	constexpr inline void _matrix_set_column_matrix(LhsMatrix_& lhs_, RhsMatrix_& rhs_)
	{
		if constexpr (ColumnIndex_ < LhsMatrix_::num_columns && RowIndex_ < LhsMatrix_::num_rows)
		{
			if constexpr (ColumnIndex_ < RhsMatrix_::num_columns && RowIndex_ < RhsMatrix_::num_rows)
			{
				_matrix_set<ColumnIndex_, RowIndex_>(lhs_, _get_matrix_data<ColumnIndex_, RowIndex_>(rhs_));
				_matrix_set_column_matrix<ColumnIndex_, RowIndex_ + 1, LhsMatrix_, RhsMatrix_>(lhs_, rhs_);
			}
			else
			{
				// Defer to scalar set since all remaining values in this column will be the same
				using lhs_contained = typename LhsMatrix_::contained_type;
				using rhs_raw_value_type = typename RhsMatrix_::rhs_raw_value_type;
				static_assert
				(
					std::is_same_v<lhs_contained, rhs_raw_value_type> || std::is_constructible_v<lhs_contained, rhs_raw_value_type>,
					"Attempted to set a matrix via another matrix whose values may not be conveted to the destination matrix's contained_type."
				);
				if constexpr (!LhsMatrix_::contains_reference_wrappers)
				{
					_matrix_set_full_scalar<ColumnIndex_, RowIndex_, LhsMatrix_, const lhs_contained>(lhs_, lhs_contained(rhs_raw_value_type()));
				}
				else
				{
					static_assert(false, "Attempted to set a reference-containing matrix via a source matrix whose size does not support the destination matrix.");
				}
			}
		}
	}
	template<std::size_t ColumnIndex_, std::size_t RowIndex_, class LhsMatrix_, class RhsMatrix_>
	constexpr inline void _matrix_set_full_matrix(LhsMatrix_& lhs_, RhsMatrix_& rhs_)
	{
		if constexpr (ColumnIndex_ < LhsMatrix_::num_columns)
		{
			if constexpr (ColumnIndex_ < RhsMatrix_::num_columns)
			{
				// Defer to column set to avoid stack depth overflowing too quickly with larger matrices
				_matrix_set_column_matrix<ColumnIndex_, RowIndex_, LhsMatrix_, RhsMatrix_>(lhs_, rhs_);
				_matrix_set_full_matrix<ColumnIndex_ + 1, RowIndex_, LhsMatrix_, RhsMatrix_>(lhs_, rhs_);
			}
			else
			{
				// Defer to full scalar set if possible since all remaining values will be the same
				using lhs_contained = typename LhsMatrix_::contained_type;
				using rhs_raw_value_type = typename RhsMatrix_::raw_value_type;
				static_assert
				(
					std::is_same_v<lhs_contained, rhs_raw_value_type> || std::is_constructible_v<lhs_contained, rhs_raw_value_type>,
					"Attempted to set a matrix via another matrix whose values may not be conveted to the destination matrix's contained_type."
				);
				if constexpr (!LhsMatrix_::contains_reference_wrappers)
				{
					_matrix_set_full_scalar<ColumnIndex_, RowIndex_, LhsMatrix_, const lhs_contained>(lhs_, lhs_contained(rhs_raw_value_type()));
				}
				else
				{
					static_assert(false, "Attempted to set a reference-containing matrix via a source matrix whose size does not support the destination matrix.");
				}
			}
		}
	}
	template<class LhsMatrix_, class Rhs_>
	constexpr inline LhsMatrix_& _matrix_set_full(LhsMatrix_& lhs_, Rhs_& rhs_)
	{
		if constexpr (EmuMath::TMP::is_emu_matrix_v<Rhs_>)
		{
			_matrix_set_full_matrix<0, 0, LhsMatrix_, Rhs_>(lhs_, rhs_);
		}
		else
		{
			_matrix_set_full_scalar<0, 0, LhsMatrix_, Rhs_>(lhs_, rhs_);
		}
		return lhs_;
	}
	template<class OutMatrix_, class Src_>
	[[nodiscard]] constexpr inline OutMatrix_ _matrix_make_and_set_full(Src_& src_)
	{
		OutMatrix_ out_ = OutMatrix_();
		_matrix_set_full<OutMatrix_, Src_>(out_, src_);
		return out_;
	}

	template<class Matrix_>
	struct _matrix_maker
	{
	private:
		template<std::size_t Index_, typename Arg_>
		static constexpr bool _set_index(Matrix_& out_, Arg_&& arg_)
		{
			constexpr std::size_t major_index_ = Index_ / Matrix_::num_non_major_elements;
			constexpr std::size_t non_major_index_ = Index_ % Matrix_::num_non_major_elements;
			if constexpr (Matrix_::is_column_major)
			{
				_matrix_set<major_index_, non_major_index_>(out_, std::forward<Arg_>(arg_));
			}
			else
			{
				_matrix_set<non_major_index_, major_index_>(out_, std::forward<Arg_>(arg_));
			}
			return true;
		}

		/// <summary> Used as a dummy to allow variadic unpacking of one item per _set_index call. </summary>
		struct _build_instructor
		{
			template<typename...Args_>
			constexpr _build_instructor(Args_&&...args_)
			{
			}
		};

	public:
		constexpr _matrix_maker()
		{
		}
		template<typename...Args_, std::size_t...Indices_>
		constexpr inline void operator()(Matrix_& out_, std::index_sequence<Indices_...> indices_, Args_&&...args_)
		{
			// There must be some other way to do this, since it looks a little bit hacky
			_build_instructor(_set_index<Indices_>(out_, args_)...);
		}
	};
	template<class Matrix_, typename...Args_>
	[[nodiscard]] constexpr inline Matrix_ _make_matrix(Args_&&...args_)
	{
		Matrix_ matrix_ = Matrix_();
		_matrix_maker<Matrix_>()(matrix_, std::make_index_sequence<sizeof...(Args_)>(), args_...);
		return matrix_;
	}
}

#endif
