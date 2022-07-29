#ifndef EMU_MATH_MATRIX_UNDERLYING_SCALE_H_INC_
#define EMU_MATH_MATRIX_UNDERLYING_SCALE_H_INC_ 1

#include "../_matrix_tmp.h"

namespace EmuMath::Helpers::_matrix_underlying
{
	template<std::size_t ColumnIndex_, std::size_t RowIndex_, class OutMatrix_, class...Args_>
	[[nodiscard]] constexpr inline decltype(auto) _matrix_scale_multi_args_get_for_index(std::tuple<Args_...>& args_)
	{
		if constexpr (ColumnIndex_ == RowIndex_)
		{
			constexpr bool is_scale_end = ColumnIndex_ == (OutMatrix_::smallest_direction_size - 1);
			if constexpr (is_scale_end)
			{
				return EmuCore::TMP::construct_or_cast<typename OutMatrix_::value_type>(1);
			}
			else
			{
				constexpr std::size_t tuple_size = sizeof...(Args_);
				if constexpr (ColumnIndex_ < sizeof...(Args_))
				{
					using std::get;
					using arg = typename std::tuple_element<ColumnIndex_, std::tuple<Args_...>>::type;
					if constexpr (std::is_lvalue_reference_v<arg>)
					{
						return get<ColumnIndex_>(args_);
					}
					else
					{
						return std::move(get<ColumnIndex_>(args_));
					}
				}
				else
				{
					return EmuCore::TMP::construct_or_cast<typename OutMatrix_::value_type>(1);
				}
			}
		}
		else
		{
			return OutMatrix_::get_implied_zero();
		}
	}

	template<class OutMatrix_, class...Args_, std::size_t...ColumnIndices_, std::size_t...RowIndices_>
	[[nodiscard]] constexpr inline OutMatrix_ _matrix_scale_multi_args
	(
		std::index_sequence<ColumnIndices_...> column_indices_,
		std::index_sequence<RowIndices_...> row_indices_,
		std::tuple<Args_...> args_tuple_
	)
	{
		constexpr bool is_constructible = std::is_constructible_v
		<
			OutMatrix_,
			decltype(_matrix_scale_multi_args_get_for_index<ColumnIndices_, RowIndices_, OutMatrix_>(args_tuple_))...
		>;

		if constexpr (is_constructible)
		{
			return OutMatrix_
			(
				_matrix_scale_multi_args_get_for_index<ColumnIndices_, RowIndices_, OutMatrix_>(args_tuple_)...
			);
		}
		else
		{
			static_assert
			(
				EmuCore::TMP::get_false<OutMatrix_>(),
				"Attempted to create a scaling EmuMath Matrix, but at least one element of the provided output Matrix type cannot construct be constructed with the resoectuve argument, a default 1 value, or a default 0 value."
			);
		}
	}

	template<std::size_t ColumnIndex_, std::size_t RowIndex_, class OutMatrix_, class Arg_>
	[[nodiscard]] constexpr inline decltype(auto) _matrix_scale_single_arg_get_for_index(Arg_&& arg_)
	{
		if constexpr (ColumnIndex_ == RowIndex_)
		{
			constexpr std::size_t matched_index = ColumnIndex_; // Column and Row are the same, so choice doesn't matter
			constexpr bool is_scale_end = matched_index == (OutMatrix_::smallest_direction_size - 1);
			if constexpr (is_scale_end)
			{
				return EmuCore::TMP::construct_or_cast<typename OutMatrix_::value_type>(1);
			}
			else
			{
				using arg_uq = typename EmuCore::TMP::remove_ref_cv<Arg_>::type;
				if constexpr (EmuMath::TMP::is_emu_vector_v<arg_uq>)
				{
					if constexpr (matched_index < arg_uq::size)
					{
						// Switching system here allows us to move values from rvalue vectors
						if constexpr (std::is_lvalue_reference_v<Arg_> || arg_uq::contains_ref)
						{
							return arg_.template at<matched_index>();
						}
						else
						{
							return std::move(arg_.template at<matched_index>());
						}
					}
					else
					{
						// Non-contained indices are interpreted as 1 to allow partial inputs for larger matrices (e.g. only scale in 2D for a 3D transformation matrix)
						return EmuCore::TMP::construct_or_cast<typename OutMatrix_::value_type>(1);
					}
				}
				else
				{
					// Unique case where if a scalar is only needed once, we can forward it and allow potential moves
					// --- Otherwise, force it to be interpreted as lval to prevent moves
					if constexpr (matched_index == 0 && OutMatrix_::smallest_direction_size == 2)
					{
						return std::forward<Arg_>(arg_);
					}
					else
					{
						return EmuCore::TMP::lval_ref_cast<Arg_>(std::forward<Arg_>(arg_));
					}
				}
			}
		}
		else
		{
			return OutMatrix_::get_implied_zero();
		}
	}

	template<class OutMatrix_, class ScaleArg_, std::size_t...ColumnIndices_, std::size_t...RowIndices_>
	[[nodiscard]] constexpr inline OutMatrix_ _matrix_scale_single_arg
	(
		std::index_sequence<ColumnIndices_...> column_indices_,
		std::index_sequence<RowIndices_...> row_indices_,
		ScaleArg_&& scale_arg_
	)
	{
		using arg_uq = typename EmuCore::TMP::remove_ref_cv<ScaleArg_>::type;
		if constexpr (EmuCore::TMP::is_tuple_v<arg_uq>)
		{
			// Defer to multi-arg with tuples
			return _matrix_scale_multi_args<OutMatrix_>
			(
				std::index_sequence<ColumnIndices_...>(),
				std::index_sequence<RowIndices_...>(),
				EmuCore::TMP::lval_ref_cast<ScaleArg_>(std::forward<ScaleArg_>(scale_arg_))
			);
		}
		else
		{
			constexpr bool is_constructible = std::is_constructible_v
			<
				OutMatrix_,
				decltype(_matrix_scale_single_arg_get_for_index<ColumnIndices_, RowIndices_, OutMatrix_>(std::forward<ScaleArg_>(scale_arg_)))...
			>;

			if constexpr(is_constructible)
			{
#pragma warning(push)
#pragma warning(disable: 26800)
				return OutMatrix_
				(
					_matrix_scale_single_arg_get_for_index<ColumnIndices_, RowIndices_, OutMatrix_>
					(
						std::forward<ScaleArg_>(scale_arg_)
					)...
				);
#pragma warning(pop)
			}
			else
			{
				static_assert
				(
					EmuCore::TMP::get_false<OutMatrix_>(),
					"Attempted to create a scaling EmuMath Matrix, but at least one element of the provided output Matrix type cannot construct be constructed with the provided argument, a default 1 value, or a default 0 value."
				);
			}
		}
	}

	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, bool OutColumnMajor_, class...ScaleArgs_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_> _matrix_scale(ScaleArgs_&&...scale_args_)
	{
		using out_matrix = EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>;
		using out_indices = EmuMath::TMP::make_full_matrix_index_sequences<out_matrix>;
		using column_indices = typename out_indices::column_index_sequence;
		using row_indices = typename out_indices::row_index_sequence;

		if constexpr (sizeof...(ScaleArgs_) == 1)
		{
			return _matrix_scale_single_arg<out_matrix>(column_indices(), row_indices(), std::forward<ScaleArgs_>(scale_args_)...);
		}
		else
		{
			return _matrix_scale_multi_args<out_matrix>(column_indices(), row_indices(), std::forward_as_tuple<ScaleArgs_...>(std::forward<ScaleArgs_>(scale_args_)...));
		}
	}
	
	template<class OutMatrix_, class...Args_, std::size_t...ColumnIndices_, std::size_t...RowIndices_>
	constexpr inline void _matrix_scale_assign_multi_args
	(
		OutMatrix_& out_matrix_,
		std::index_sequence<ColumnIndices_...> column_indices_,
		std::index_sequence<RowIndices_...> row_indices_,
		std::tuple<Args_...> args_tuple_
	)
	{
		using out_mat_uq = typename EmuCore::TMP::remove_ref_cv<OutMatrix_>::type;
		using out_value_uq = typename out_mat_uq::value_type_uq;
		constexpr bool valid_assign_or_casts = 
		(
			... &&
			EmuCore::TMP::valid_assign_direct_or_cast
			<
				out_value_uq,
				decltype(_matrix_scale_multi_args_get_for_index<ColumnIndices_, RowIndices_, out_mat_uq>(args_tuple_)),
				decltype(out_matrix_.template at<ColumnIndices_, RowIndices_>())
			>()
		);

		if constexpr (valid_assign_or_casts)
		{
			(
				(
					EmuCore::TMP::assign_direct_or_cast<out_value_uq>
					(
						out_matrix_.template at<ColumnIndices_, RowIndices_>(),
						_matrix_scale_multi_args_get_for_index<ColumnIndices_, RowIndices_, out_mat_uq>(args_tuple_)
					)
				), ...
			);
		}
		else
		{
			static_assert
			(
				EmuCore::TMP::get_false<OutMatrix_>(),
				"Attempted to assign a scaling Matrix to an existing EmuMath Matrix, but the provided output Matrix type cannot be assigned to at least one index with the provided arguments, a default 1 value, or a default 0 value."
			);
		}
	}

	template<class OutMatrix_, class ScaleArg_, std::size_t...ColumnIndices_, std::size_t...RowIndices_>
	[[nodiscard]] constexpr inline void _matrix_scale_assign_single_arg
	(
		OutMatrix_& out_matrix_,
		std::index_sequence<ColumnIndices_...> column_indices_,
		std::index_sequence<RowIndices_...> row_indices_,
		ScaleArg_&& scale_arg_
	)
	{
		using arg_uq = typename EmuCore::TMP::remove_ref_cv<ScaleArg_>::type;
		if constexpr (EmuCore::TMP::is_tuple_v<arg_uq>)
		{
			// Defer to multi-arg with tuples
			_matrix_scale_assign_multi_args<OutMatrix_>
			(
				out_matrix_,
				std::index_sequence<ColumnIndices_...>(),
				std::index_sequence<RowIndices_...>(),
				EmuCore::TMP::lval_ref_cast<ScaleArg_>(std::forward<ScaleArg_>(scale_arg_))
			);
		}
		else
		{
			using out_mat_uq = typename EmuCore::TMP::remove_ref_cv<OutMatrix_>::type;
			using out_value_uq = typename out_mat_uq::value_type_uq;
			constexpr bool valid_assign_or_casts = 
			(
				... &&
				EmuCore::TMP::valid_assign_direct_or_cast
				<
					out_value_uq,
					decltype(_matrix_scale_single_arg_get_for_index<ColumnIndices_, RowIndices_, out_mat_uq>(std::forward<ScaleArg_>(scale_arg_))),
					decltype(out_matrix_.template at<ColumnIndices_, RowIndices_>())
				>()
			);

			if constexpr (valid_assign_or_casts)
			{
#pragma warning(push)
#pragma warning(disable: 26800)
				(
					(
						EmuCore::TMP::assign_direct_or_cast<out_value_uq>
						(
							out_matrix_.template at<ColumnIndices_, RowIndices_>(),
							_matrix_scale_single_arg_get_for_index<ColumnIndices_, RowIndices_, out_mat_uq>(std::forward<ScaleArg_>(scale_arg_))
						)
					), ...
				);
#pragma warning(pop)
			}
			else
			{
				static_assert
				(
					EmuCore::TMP::get_false<OutMatrix_>(),
					"Attempted to assign a scaling Matrix to an existing EmuMath Matrix, but the provided output Matrix type cannot be assigned to at least one index with the provided arguments, a default 1 value, or a default 0 value."
				);
			}
		}
	}

	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, bool OutColumnMajor_, class...ScaleArgs_>
	constexpr inline void _matrix_scale_assign(EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>& out_matrix_, ScaleArgs_&&...scale_args_)
	{
		using out_matrix = EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>;
		using out_indices = EmuMath::TMP::make_full_matrix_index_sequences<out_matrix>;
		using column_indices = typename out_indices::column_index_sequence;
		using row_indices = typename out_indices::row_index_sequence;

		if constexpr (sizeof...(ScaleArgs_) == 1)
		{
			_matrix_scale_assign_single_arg<out_matrix>(out_matrix_, column_indices(), row_indices(), std::forward<ScaleArgs_>(scale_args_)...);
		}
		else
		{
			_matrix_scale_assign_multi_args<out_matrix>
			(
				out_matrix_,
				column_indices(),
				row_indices(),
				std::forward_as_tuple<ScaleArgs_...>(std::forward<ScaleArgs_>(scale_args_)...)
			);
		}
	}
}

#endif
