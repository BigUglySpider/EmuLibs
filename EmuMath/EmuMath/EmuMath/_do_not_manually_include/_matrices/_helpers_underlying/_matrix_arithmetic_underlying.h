#ifndef EMU_MATH__UNDERLYING_MATRIX_ARITHMETIC_H_INC_
#define EMU_MATH__UNDERLYING_MATRIX_ARITHMETIC_H_INC_ 1

#include "_common_underlying_matrix_helper_includes.h"
#include "_matrix_gets_underlying.h"
#include "_matrix_sets_underlying.h"
#include "_matrix_validity_checks_underlying.h"

namespace EmuMath::Helpers::_underlying_matrix_funcs
{
	template<std::size_t ColumnIndex_, std::size_t RowIndex_, class OutMatrix_, class LhsMatrix_, class Rhs_, class Func_>
	constexpr inline void _matrix_lhs_rhs_operation_rhs_scalar(const LhsMatrix_& lhs_, const Rhs_& rhs_, Func_& func_, OutMatrix_& out_)
	{
		if constexpr (ColumnIndex_ < OutMatrix_::num_columns)
		{
			if constexpr (RowIndex_ < OutMatrix_::num_rows)
			{
				using out_value = typename OutMatrix_::value_type;
				_get_matrix_data<ColumnIndex_, RowIndex_>(out_) = static_cast<out_value>(func_(_get_matrix_theoretical_data<ColumnIndex_, RowIndex_>(lhs_), rhs_));
				_matrix_lhs_rhs_operation_rhs_scalar<ColumnIndex_, RowIndex_ + 1, OutMatrix_, LhsMatrix_, Rhs_, Func_>(lhs_, rhs_, func_, out_);
			}
			else
			{
				_matrix_lhs_rhs_operation_rhs_scalar<ColumnIndex_ + 1, 0, OutMatrix_, LhsMatrix_, Rhs_, Func_>(lhs_, rhs_, func_, out_);
			}
		}
	}
	template<std::size_t ColumnIndex_, std::size_t RowIndex_, class OutMatrix_, class LhsMatrix_, class Rhs_, class Func_>
	constexpr inline void _matrix_lhs_rhs_operation_rhs_matrix(const LhsMatrix_& lhs_, const Rhs_& rhs_, Func_& func_, OutMatrix_& out_)
	{
		if constexpr (ColumnIndex_ < OutMatrix_::num_columns)
		{
			if constexpr (RowIndex_ < OutMatrix_::num_rows)
			{
				using out_value = typename OutMatrix_::value_type;
				_get_matrix_data<ColumnIndex_, RowIndex_>(out_) = static_cast<out_value>
				(
					func_
					(
						_get_matrix_theoretical_data<ColumnIndex_, RowIndex_>(lhs_),
						_get_matrix_theoretical_data<ColumnIndex_, RowIndex_>(rhs_)
					)
				);
				_matrix_lhs_rhs_operation_rhs_matrix<ColumnIndex_, RowIndex_ + 1, OutMatrix_, LhsMatrix_, Rhs_, Func_>(lhs_, rhs_, func_, out_);
			}
			else
			{
				_matrix_lhs_rhs_operation_rhs_matrix<ColumnIndex_ + 1, 0, OutMatrix_, LhsMatrix_, Rhs_, Func_>(lhs_, rhs_, func_, out_);
			}
		}
	}
	template<class OutMatrix_, class LhsMatrix_, class Rhs_, class Func_>
	[[nodiscard]] constexpr inline OutMatrix_ _matrix_lhs_rhs_operation(const LhsMatrix_& lhs_, const Rhs_& rhs_, Func_& func_)
	{
		OutMatrix_ out_ = OutMatrix_();
		if constexpr (EmuMath::TMP::is_emu_matrix_v<Rhs_>)
		{
			_matrix_lhs_rhs_operation_rhs_matrix<0, 0, OutMatrix_, LhsMatrix_, Rhs_, Func_>(lhs_, rhs_, func_, out_);
		}
		else
		{
			_matrix_lhs_rhs_operation_rhs_scalar<0, 0, OutMatrix_, LhsMatrix_, Rhs_, Func_>(lhs_, rhs_, func_, out_);
		}
		return out_;
	}
	template<class OutMatrix_, class LhsMatrix_, class Rhs_, class Func_>
	[[nodiscard]] constexpr inline OutMatrix_ _matrix_lhs_rhs_operation(const LhsMatrix_& lhs_, const Rhs_& rhs_)
	{
		Func_ func_ = Func_();
		return _matrix_lhs_rhs_operation<OutMatrix_, LhsMatrix_, Rhs_, Func_&>(lhs_, rhs_, func_);
	}

	template<class Matrix_, std::size_t...Indices_>
	[[nodiscard]] constexpr inline std::array<EmuMath::Vector<Matrix_::num_rows, typename Matrix_::value_type>, sizeof...(Indices_)> _get_matrix_columns
	(
		const Matrix_& matrix_,
		std::index_sequence<Indices_...>
	)
	{
		return std::array<EmuMath::Vector<Matrix_::num_rows, typename Matrix_::value_type>, sizeof...(Indices_)>
		({
			_get_matrix_column<Indices_>(matrix_)...
		});
	}
	template<class Matrix_, std::size_t...Indices_>
	[[nodiscard]] constexpr inline std::array<EmuMath::Vector<Matrix_::num_columns, typename Matrix_::value_type>, sizeof...(Indices_)> _get_matrix_rows
	(
		const Matrix_& matrix_,
		std::index_sequence<Indices_...>
	)
	{
		return std::array<EmuMath::Vector<Matrix_::num_columns, typename Matrix_::value_type>, sizeof...(Indices_)>
		({
			_get_matrix_row<Indices_>(matrix_)...
		});
	}
	template<std::size_t ColumnIndex_, std::size_t RowIndex_, class OutMatrix_, class LhsRows_, class RhsColumns_>
	constexpr inline void _matrix_std_multiply(OutMatrix_& out_, const LhsRows_& lhs_rows_, const RhsColumns_& rhs_columns_)
	{
		if constexpr (ColumnIndex_ < OutMatrix_::num_columns)
		{
			if constexpr (RowIndex_ < OutMatrix_::num_rows)
			{
				_get_matrix_data<ColumnIndex_, RowIndex_>(out_) = EmuMath::Helpers::VectorDotProduct<typename OutMatrix_::value_type>
				(
					std::get<RowIndex_>(lhs_rows_),
					std::get<ColumnIndex_>(rhs_columns_)
				);
				_matrix_std_multiply<ColumnIndex_, RowIndex_ + 1, OutMatrix_, LhsRows_, RhsColumns_>(out_, lhs_rows_, rhs_columns_);
			}
			else
			{
				_matrix_std_multiply<ColumnIndex_ + 1, 0, OutMatrix_, LhsRows_, RhsColumns_>(out_, lhs_rows_, rhs_columns_);
			}
		}
	}
	template<class OutMatrix_, class LhsMatrix_, class Rhs_>
	[[nodiscard]] constexpr inline OutMatrix_ _matrix_std_multiply(const LhsMatrix_& lhs_, const Rhs_& rhs_)
	{
		if constexpr (EmuMath::TMP::is_emu_matrix_v<Rhs_>)
		{
			auto lhs_rows_ = _get_matrix_rows<LhsMatrix_>(lhs_, std::make_index_sequence<LhsMatrix_::num_rows>());
			auto rhs_columns_ = _get_matrix_columns<Rhs_>(rhs_, std::make_index_sequence<Rhs_::num_columns>());
			OutMatrix_ out_ = OutMatrix_();
			_matrix_std_multiply<0, 0, OutMatrix_>(out_, lhs_rows_, rhs_columns_);
			return out_;
		}
		else
		{
			// Defer to basic lhs_rhs functor executor since A * scalar_x is effectively A[00]-A[XX] * scalar_x.
			return _matrix_lhs_rhs_operation<OutMatrix_, LhsMatrix_, Rhs_, EmuCore::do_multiply<typename LhsMatrix_::value_type, Rhs_>>(lhs_, rhs_);
		}
	}

	template<std::size_t ColumnIndex_, std::size_t RowIndex_, class Func_, class InMatrix_, class OutMatrix_>
	constexpr inline void _matrix_mutate_column(const InMatrix_& in_, OutMatrix_& out_, Func_& func_)
	{
		if constexpr (ColumnIndex_ < OutMatrix_::num_columns)
		{
			if constexpr (RowIndex_ < OutMatrix_::num_rows)
			{
				using out_value = typename OutMatrix_::value_type;
				if constexpr (ColumnIndex_ < InMatrix_::num_columns && RowIndex_ < InMatrix_::num_rows)
				{
					_get_matrix_data<ColumnIndex_, RowIndex_>(out_) = static_cast<out_value>(func_(_get_matrix_data<ColumnIndex_, RowIndex_>(in_)));
				}
				else
				{
					using in_raw_value = typename InMatrix_::raw_value_type;
					_get_matrix_data<ColumnIndex_, RowIndex_>(out_) = static_cast<out_value>(func_(in_raw_value()));
				}
				_matrix_mutate_column<ColumnIndex_, RowIndex_ + 1, Func_, InMatrix_, OutMatrix_>(in_, out_, func_);
			}
		}
	}
	template<std::size_t ColumnIndex_, std::size_t RowIndex_, class Func_, class InMatrix_, class OutMatrix_>
	constexpr inline void _matrix_mutate(const InMatrix_& in_, OutMatrix_& out_, Func_& func_)
	{
		if constexpr (ColumnIndex_ < OutMatrix_::num_columns)
		{
			_matrix_mutate_column<ColumnIndex_, RowIndex_, Func_, InMatrix_, OutMatrix_>(in_, out_, func_);
			_matrix_mutate<ColumnIndex_ + 1, RowIndex_, Func_, InMatrix_, OutMatrix_>(in_, out_, func_);
		}
	}
	template<class Func_, class OutMatrix_, class InMatrix_>
	constexpr inline OutMatrix_& _matrix_mutate(const InMatrix_& in_, OutMatrix_& out_, Func_ func_)
	{
		_matrix_mutate<0, 0, Func_, InMatrix_, OutMatrix_>(in_, out_, func_);
		return out_;
	}
	template<class Func_, class OutMatrix_, class InMatrix_>
	constexpr inline OutMatrix_& _matrix_mutate(const InMatrix_& in_, OutMatrix_& out_)
	{
		return _matrix_mutate<Func_, OutMatrix_, InMatrix_>(in_, out_, Func_());
	}

	template<class Func_, class OutMatrix_, class InMatrix_>
	[[nodiscard]] constexpr inline OutMatrix_ _make_mutated_matrix(const InMatrix_& in_, Func_ func_)
	{
		OutMatrix_ out_ = OutMatrix_();
		_matrix_mutate<Func_&, OutMatrix_, InMatrix_>(in_, out_, func_);
		return out_;
	}
	template<class Func_, class OutMatrix_, class InMatrix_>
	[[nodiscard]] constexpr inline OutMatrix_ _make_mutated_matrix(const InMatrix_& in_)
	{
		OutMatrix_ out_ = OutMatrix_();
		_matrix_mutate<Func_, OutMatrix_, InMatrix_>(in_, out_);
		return out_;
	}
}

#endif
