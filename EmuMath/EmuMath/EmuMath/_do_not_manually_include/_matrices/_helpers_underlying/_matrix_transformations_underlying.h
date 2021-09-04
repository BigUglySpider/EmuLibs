#ifndef EMU_MATH__UNDERLYING_MATRIX_TRANSFORMATIONS_H_INC_
#define EMU_MATH__UNDERLYING_MATRIX_TRANSFORMATIONS_H_INC_ 1

#include "_common_matrix_helper_includes.h"
#include "_matrix_gets_underlying.h"
#include "_matrix_sets_underlying.h"

namespace EmuMath::Helpers::_underlying_matrix_funcs
{
	template<class Matrix_, class FirstArg_, class...AdditionalArgs_>
	struct _translation_matrix_builder
	{
		constexpr _translation_matrix_builder()
		{
		}
		template<std::size_t RowIndex_ = 0>
		constexpr inline void operator()(Matrix_& out_, const FirstArg_& first_arg_, const AdditionalArgs_&...additional_args_) const
		{
			if constexpr (RowIndex_ < Matrix_::num_rows)
			{
				_translation_matrix_builder<Matrix_, FirstArg_>().operator()<RowIndex_>(out_, first_arg_);
				_translation_matrix_builder<Matrix_, AdditionalArgs_...>().operator()<RowIndex_ + 1>(out_, additional_args_...);
			}
		}
	};
	template<class Matrix_, class Arg_>
	struct _translation_matrix_builder<Matrix_, Arg_>
	{
		constexpr _translation_matrix_builder()
		{
		}
		// This is called independetnly from a recursive loop, and does not need to recursively call itself for further indices.
		template<std::size_t RowIndex_ = 0>
		constexpr inline void operator()(Matrix_& out_, const Arg_& arg_) const
		{
			if constexpr (RowIndex_ < Matrix_::num_rows)
			{
				using out_value = typename Matrix_::value_type;
				if constexpr (std::is_convertible_v<Arg_, out_value>)
				{
					_get_matrix_data<Matrix_::num_columns - 1, RowIndex_, Matrix_>(out_) = static_cast<out_value>(arg_);
				}
				else
				{
					static_assert(false, "Attempted to create an EmuMath translation matrix using a coordinate argument which cannot be converted to the output matrix's value type.");
				}
			}
		}
	};

	template<class OutMatrix_, class...Args_>
	constexpr inline OutMatrix_ _make_translation_matrix(const Args_&...args_)
	{
		OutMatrix_ out_ = OutMatrix_();
		_matrix_set_trace_region<0, OutMatrix_, typename OutMatrix_::contained_type>(out_, typename OutMatrix_::contained_type(1));
		_translation_matrix_builder<OutMatrix_, Args_...>()(out_, args_...);
		return out_;
	}

	template<class OutMatrix_, class Theta_, class CosCalculator_, class SinCalculator_>
	constexpr inline OutMatrix_ _make_rotation_matrix_x(const Theta_& theta_)
	{
		using out_value = typename OutMatrix_::value_type;

		OutMatrix_ out_ = OutMatrix_();
		out_value cos_ = static_cast<out_value>(CosCalculator_()(theta_));
		out_value sin_ = static_cast<out_value>(SinCalculator_()(theta_));
		_get_matrix_data<1, 1>(out_) = cos_;
		_get_matrix_data<2, 1>(out_) = sin_;
		_get_matrix_data<1, 2>(out_) = EmuCore::do_negate<out_value>()(sin_);
		_get_matrix_data<2, 2>(out_) = cos_;

		// Set unfilled trace elements to 1 before returning.
		const out_value one_ = out_value(1);
		_get_matrix_data<0, 0>(out_) = one_;
		if constexpr (OutMatrix_::num_columns >= 4 && OutMatrix_::num_rows >= 4)
		{
			_matrix_set_trace_region<3, OutMatrix_, out_value>(out_, one_);
		}
		return out_;
	}
	template<class OutMatrix_, class Theta_, class CosCalculator_, class SinCalculator_>
	constexpr inline OutMatrix_ _make_rotation_matrix_y(const Theta_& theta_)
	{
		using out_value = typename OutMatrix_::value_type;

		OutMatrix_ out_ = OutMatrix_();
		out_value cos_ = static_cast<out_value>(CosCalculator_()(theta_));
		out_value sin_ = static_cast<out_value>(SinCalculator_()(theta_));
		_get_matrix_data<0, 0>(out_) = cos_;
		_get_matrix_data<2, 0>(out_) = EmuCore::do_negate<out_value>()(sin_);
		_get_matrix_data<0, 2>(out_) = sin_;
		_get_matrix_data<2, 2>(out_) = cos_;

		// Set unfilled trace elements to 1 before returning.
		const out_value one_ = out_value(1);
		_get_matrix_data<1, 1>(out_) = one_;
		if constexpr (OutMatrix_::num_columns >= 4 && OutMatrix_::num_rows >= 4)
		{
			_matrix_set_trace_region<3, OutMatrix_, out_value>(out_, one_);
		}
		return out_;
	}
	template<class OutMatrix_, class Theta_, class CosCalculator_, class SinCalculator_>
	constexpr inline OutMatrix_ _make_rotation_matrix_z(const Theta_& theta_)
	{
		using out_value = typename OutMatrix_::value_type;

		OutMatrix_ out_ = OutMatrix_();
		out_value cos_ = static_cast<out_value>(CosCalculator_()(theta_));
		out_value sin_ = static_cast<out_value>(SinCalculator_()(theta_));
		_get_matrix_data<0, 0>(out_) = cos_;
		_get_matrix_data<1, 0>(out_) = EmuCore::do_negate<out_value>()(sin_);
		_get_matrix_data<0, 1>(out_) = sin_;
		_get_matrix_data<1, 1>(out_) = cos_;

		// Set unfilled trace elements to 1 before returning.
		if constexpr (OutMatrix_::num_columns >= 3 && OutMatrix_::num_rows >= 3)
		{
			_matrix_set_trace_region<2, OutMatrix_, out_value>(out_, out_value(1));
		}
		return out_;
	}
}

#endif
