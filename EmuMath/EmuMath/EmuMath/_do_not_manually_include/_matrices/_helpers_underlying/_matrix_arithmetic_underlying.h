#ifndef EMU_MATH__UNDERLYING_MATRIX_ARITHMETIC_H_INC_
#define EMU_MATH__UNDERLYING_MATRIX_ARITHMETIC_H_INC_ 1

#include "_common_underlying_matrix_helper_includes.h"
#include "_matrix_gets_underlying.h"
#include "_matrix_sets_underlying.h"
#include "_matrix_validity_checks_underlying.h"

namespace EmuMath::Helpers::_underlying_matrix_funcs
{
	template<class T_ >
	struct _matrix_mutli_arg_individual_template_arg
	{
		using type = T_;
	};
	template<std::size_t NumColumns_, std::size_t NumRows_, typename T_, bool ColumnMajor_>
	struct _matrix_mutli_arg_individual_template_arg<EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>>
	{
		using type = typename EmuMath::Matrix<NumColumns_, NumRows_, T_, ColumnMajor_>::raw_value_type;
	};
	template<std::size_t ColumnIndex_, std::size_t RowIndex_, class Func_, class OutMatrix_, class MatrixA_, class...OtherArgs_>
	constexpr inline void _matrix_multi_arg_operation(Func_& func_, OutMatrix_& out_, const MatrixA_& a_, const OtherArgs_&...other_args_)
	{
		if constexpr (ColumnIndex_ < OutMatrix_::num_columns)
		{
			if constexpr (RowIndex_ < OutMatrix_::num_rows)
			{
				_get_matrix_data<ColumnIndex_, RowIndex_>(out_) = static_cast<typename OutMatrix_::value_type>
				(
					func_
					(
						_get_theoretical_arg<ColumnIndex_, RowIndex_>(a_),
						_get_theoretical_arg<ColumnIndex_, RowIndex_, OtherArgs_>(other_args_)...
					)
				);
				_matrix_multi_arg_operation<ColumnIndex_, RowIndex_ + 1, Func_, OutMatrix_, MatrixA_, OtherArgs_...>(func_, out_, a_, other_args_...);
			}
			else
			{
				_matrix_multi_arg_operation<ColumnIndex_ + 1, 0, Func_, OutMatrix_, MatrixA_, OtherArgs_...>(func_, out_, a_, other_args_...);
			}
		}
	}
	template<class Func_, class OutMatrix_, class MatrixA_, class...OtherArgs_>
	[[nodiscard]] constexpr inline OutMatrix_ _matrix_multi_arg_operation(Func_ func_, const MatrixA_& matrix_a_, const OtherArgs_&...other_args_)
	{
		OutMatrix_ out_ = OutMatrix_();
		_matrix_multi_arg_operation<0, 0, Func_, OutMatrix_, MatrixA_, OtherArgs_...>(func_, out_, matrix_a_, other_args_...);
		return out_;
	}
	template<class Func_, class OutMatrix_, class MatrixA_, class...OtherArgs_>
	[[nodiscard]] constexpr inline OutMatrix_ _matrix_multi_arg_operation(const MatrixA_& matrix_a_, const OtherArgs_&...other_args_)
	{
		return _matrix_multi_arg_operation<Func_, OutMatrix_, MatrixA_, OtherArgs_...>(Func_(), matrix_a_, other_args_...);
	}

	template<template<class...Args__> class FuncTemplate_, class OutMatrix_, class MatrixA_, class...OtherArgs_>
	[[nodiscard]] constexpr inline OutMatrix_ _matrix_multi_arg_operation(const MatrixA_& matrix_a_, const OtherArgs_&...other_args_)
	{
		using Func_ = FuncTemplate_
		<
			typename _matrix_mutli_arg_individual_template_arg<MatrixA_>::type,
			typename _matrix_mutli_arg_individual_template_arg<OtherArgs_>::type...
		>;
		return _matrix_multi_arg_operation<Func_, OutMatrix_, MatrixA_, OtherArgs_...>(matrix_a_, other_args_...);
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
			// A * scalar_x is effectively A[00]-A[XX] * scalar_x, so defer to simple multi_arg operation.
			return _matrix_multi_arg_operation<EmuCore::do_multiply, OutMatrix_, LhsMatrix_, Rhs_>(lhs_, rhs_);
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

	/// <summary>
	///	Finds the final element to compare true within the passed matrix with the passed cmp_. 
	///	When a cmp_ is true, future comparisons are performed with that index's value. 
	///	Primarily for operations such as finding the lowest value within a matrix.
	/// </summary>
	template<std::size_t ColumnIndex_, std::size_t RowIndex_, class Matrix_, class Cmp_>
	[[nodiscard]] constexpr inline void _matrix_final_index_to_cmp_true
	(
		EmuMath::Vector<2, std::size_t>& out_,
		const Matrix_& matrix_,
		typename Matrix_::value_type& prev_val_,
		Cmp_& cmp_
	)
	{
		if constexpr (ColumnIndex_ < Matrix_::num_columns)
		{
			if constexpr (RowIndex_ < Matrix_::num_rows)
			{
				const auto& current_val_ = _get_matrix_data<ColumnIndex_, RowIndex_>(matrix_);
				if (cmp_(current_val_, prev_val_))
				{
					prev_val_ = current_val_;
					out_.at<0>() = ColumnIndex_;
					out_.at<1>() = RowIndex_;
				}
				_matrix_final_index_to_cmp_true<ColumnIndex_, RowIndex_ + 1, Matrix_, Cmp_>(out_, matrix_, prev_val_, cmp_);
			}
			else
			{
				_matrix_final_index_to_cmp_true<ColumnIndex_ + 1, 0, Matrix_, Cmp_>(out_, matrix_, prev_val_, cmp_);
			}
		}
	}
	template<class Matrix_, class Cmp_>
	[[nodiscard]] constexpr inline EmuMath::Vector<2, std::size_t> _matrix_final_index_to_cmp_true(const Matrix_ matrix_, typename Matrix_::value_type starting_val_)
	{
		Cmp_ cmp_ = Cmp_();
		EmuMath::Vector<2, std::size_t> out_(std::size_t(0), std::size_t(0));
		_matrix_final_index_to_cmp_true<0, 0, Matrix_, Cmp_>(out_, matrix_, starting_val_, cmp_);
		return out_;
	}
	template<typename Out_, class Cmp_, class Matrix_>
	[[nodiscard]] constexpr inline Out_ _matrix_final_element_to_cmp_true(Matrix_& matrix_, typename Matrix_::value_type starting_val_)
	{
		EmuMath::Vector<2, std::size_t> index_ = _matrix_final_index_to_cmp_true<Matrix_, Cmp_>(matrix_, starting_val_);
		return static_cast<Out_>(_get_matrix_data(matrix_, index_.at<0>(), index_.at<1>()));
	}
}

#endif
