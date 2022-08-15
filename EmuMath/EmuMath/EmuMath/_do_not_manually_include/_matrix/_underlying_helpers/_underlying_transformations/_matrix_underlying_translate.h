#ifndef EMU_MATH_MATRIX_UNDERLYING_TRANSLATE_H_INC_
#define EMU_MATH_MATRIX_UNDERLYING_TRANSLATE_H_INC_ 1

#include "../_matrix_tmp.h"

namespace EmuMath::Helpers::_matrix_underlying
{
#pragma region GETS
	template<std::size_t ColumnIndex_, std::size_t RowIndex_, class OutMatrix_, class...Args_>
	[[nodiscard]] constexpr inline decltype(auto) _matrix_translate_multi_args_get_for_index(std::tuple<Args_...>& args_tuple_)
	{
		using out_mat_uq = typename EmuCore::TMP::remove_ref_cv<OutMatrix_>::type;
		if constexpr (ColumnIndex_ != RowIndex_)
		{
			if constexpr (ColumnIndex_ == (out_mat_uq::num_columns - 1))
			{
				constexpr std::size_t tuple_index = RowIndex_;
				if constexpr (tuple_index < std::tuple_size_v<std::tuple<Args_...>>)
				{
					// Retrieve translation for the dimension, which will be the respective element in the tuple
					// --- Move if not lvalue reference
					using std::get;
					using arg = typename std::tuple_element<tuple_index, std::tuple<Args_...>>::type;
					if constexpr (std::is_lvalue_reference_v<arg>)
					{
						return get<tuple_index>(args_tuple_);
					}
					else
					{
						return std::move(get<tuple_index>(args_tuple_));
					}
				}
				else
				{
					// No argument for dimension, so assume no translation
					return out_mat_uq::get_implied_zero();
				}
			}
			else
			{
				// Anything before the final column outside of the main diagonal is 0
				return out_mat_uq::get_implied_zero();
			}
		}
		else
		{
			// Main diagonal is 1
			return EmuCore::TMP::construct_or_cast<typename out_mat_uq::value_type_uq>(1);
		}
	}

	template<std::size_t ColumnIndex_, std::size_t RowIndex_, class OutMatrix_, class Arg_>
	[[nodiscard]] constexpr inline decltype(auto) _matrix_translate_single_arg_get_for_index(Arg_&& arg_)
	{
		using out_mat_uq = typename EmuCore::TMP::remove_ref_cv<OutMatrix_>::type;
		if constexpr (ColumnIndex_ != RowIndex_)
		{
			if constexpr (ColumnIndex_ == (out_mat_uq::num_columns - 1))
			{
				using arg_uq = typename EmuCore::TMP::remove_ref_cv<Arg_>::type;
				if constexpr (EmuMath::TMP::is_emu_vector_v<arg_uq>)
				{
					if constexpr (RowIndex_ < arg_uq::size)
					{
						// Allow moves from non-lvalue reference Vectors *if* they do not contain references
						if constexpr (std::is_lvalue_reference_v<Arg_> || arg_uq::contains_ref)
						{
							return arg_.template at<RowIndex_>();
						}
						else
						{
							return std::move(arg_.template at<RowIndex_>());
						}
					}
					else
					{
						// No element for this dimension, so return the Matrix's implied zero directly instead of a conversion from the Vector's
						return out_mat_uq::get_implied_zero();
					}
				}
				else
				{
					// Unique case where if a scalar is only needed once, we can forward it and allow potential moves
					// --- Otherwise, force it to be interpreted as lval to prevent moves
					if constexpr (RowIndex_ == 0 && out_mat_uq::num_rows == 2)
					{
						return std::forward<Arg_>(arg_);
					}
					else
					{
						return EmuCore::TMP::lval_ref_cast<Arg_>(std::forward<Arg_>(arg_));
					}
				}
			}
			else
			{
				// Anything before the final column outside of the main diagonal is 0
				return out_mat_uq::get_implied_zero();
			}
		}
		else
		{
			// Main diagonal is 1
			return EmuCore::TMP::construct_or_cast<typename out_mat_uq::value_type_uq>(1);
		}
	}
#pragma endregion

#pragma region VALIDITY_CHECKS
	template<class OutMatrix_, class ArgsTuple_, bool Assigning_, std::size_t...ColumnIndices_, std::size_t...RowIndices_>
	[[nodiscard]] constexpr inline bool _matrix_translate_multi_args_is_valid
	(
		std::index_sequence<ColumnIndices_...> column_indices_,
		std::index_sequence<RowIndices_...> row_indices_
	)
	{
		using tuple_no_ref = typename std::remove_reference<ArgsTuple_>::type;
		if constexpr (Assigning_)
		{
			using out_mat_uq = typename EmuCore::TMP::remove_ref_cv<OutMatrix_>::type;
			using out_value_uq = typename out_mat_uq::value_type_uq;

			// 6287 silenced here as there is a warning for function calls due to potential side-effects
			// --- In this context, side-effects are not expected. If there are any, it will be due to an ill-formed specialisation
#pragma warning(push)
#pragma warning(disable: 6287)
			return
			(
				... &&
				EmuCore::TMP::valid_assign_direct_or_cast
				<
					out_value_uq,
					decltype(_matrix_translate_multi_args_get_for_index<ColumnIndices_, RowIndices_, OutMatrix_>(std::declval<tuple_no_ref&>())),
					decltype(std::declval<OutMatrix_>().template at<ColumnIndices_, RowIndices_>())
				>()
			);
#pragma warning(pop)
		}
		else
		{
			return std::is_constructible_v
			<
				OutMatrix_,
				decltype(_matrix_translate_multi_args_get_for_index<ColumnIndices_, RowIndices_, OutMatrix_>(std::declval<tuple_no_ref&>()))...
			>;
		}
	}

	template<class OutMatrix_, class TranslateArg_, bool Assigning_, std::size_t...ColumnIndices_, std::size_t...RowIndices_>
	[[nodiscard]] constexpr inline bool _matrix_translate_single_arg_is_valid
	(
		std::index_sequence<ColumnIndices_...> column_indices_,
		std::index_sequence<RowIndices_...> row_indices_
	)
	{
		if constexpr (Assigning_)
		{
			using out_mat_uq = typename EmuCore::TMP::remove_ref_cv<OutMatrix_>::type;
			using out_value_uq = typename out_mat_uq::value_type_uq;
			// 6287 silenced here as there is a warning for function calls due to potential side-effects
			// --- In this context, side-effects are not expected. If there are any, it will be due to an ill-formed specialisation
#pragma warning(push)
#pragma warning(disable: 6287)
			return
			(
				... &&
				EmuCore::TMP::valid_assign_direct_or_cast
				<
					out_value_uq,
					decltype(_matrix_translate_single_arg_get_for_index<ColumnIndices_, RowIndices_, OutMatrix_>(std::forward<TranslateArg_>(std::declval<TranslateArg_>()))),
					decltype(std::declval<OutMatrix_>().template at<ColumnIndices_, RowIndices_>())
				>()
			);
#pragma warning(pop)
		}
		else
		{
			return std::is_constructible_v
			<
				OutMatrix_,
				decltype(_matrix_translate_single_arg_get_for_index<ColumnIndices_, RowIndices_, OutMatrix_>(std::forward<TranslateArg_>(std::declval<TranslateArg_>())))...
			>;
		}
	}

	template<class OutMatrix_, bool Assigning_, class...TranslateArgs_>
	[[nodiscard]] constexpr inline bool _matrix_translate_is_valid()
	{
		using out_indices = EmuMath::TMP::make_full_matrix_index_sequences<typename EmuCore::TMP::remove_ref_cv<OutMatrix_>::type>;
		using column_index_sequence = typename out_indices::column_index_sequence;
		using row_index_sequence = typename out_indices::row_index_sequence;
		constexpr std::size_t num_args = sizeof...(TranslateArgs_);
		if constexpr (num_args == 0)
		{
			return false;
		}
		else if constexpr(num_args == 1)
		{
			using first_arg = typename EmuCore::TMP::first_variadic_arg<TranslateArgs_...>::type;
			using first_arg_uq = typename EmuCore::TMP::remove_ref_cv<first_arg>::type;
			if constexpr (EmuCore::TMP::is_tuple_v<first_arg_uq>)
			{
				using tuple_ref = decltype(EmuCore::TMP::lval_ref_cast<first_arg>(std::declval<first_arg>()));
				return _matrix_translate_multi_args_is_valid<OutMatrix_, tuple_ref, Assigning_>(column_index_sequence(), row_index_sequence());
			}
			else
			{
				return _matrix_translate_single_arg_is_valid<OutMatrix_, first_arg, Assigning_>(column_index_sequence(), row_index_sequence());
			}
		}
		else
		{
			using tuple_type = decltype(std::forward_as_tuple(std::forward<TranslateArgs_>(std::declval<TranslateArgs_>())...));
			return _matrix_translate_multi_args_is_valid<OutMatrix_, tuple_type, Assigning_>(column_index_sequence(), row_index_sequence());
		}
	}
#pragma endregion

#pragma region MAKERS
	template<class OutMatrix_, class...Args_, std::size_t...ColumnIndices_, std::size_t...RowIndices_>
	[[nodiscard]] constexpr inline OutMatrix_ _matrix_translate_multi_args
	(
		std::index_sequence<ColumnIndices_...> column_indices_,
		std::index_sequence<RowIndices_...> row_indices_,
		std::tuple<Args_...> args_tuple_
	)
	{
		using column_index_sequence = std::index_sequence<ColumnIndices_...>;
		using row_index_sequence = std::index_sequence<RowIndices_...>;
		if constexpr (_matrix_translate_multi_args_is_valid<OutMatrix_, std::tuple<Args_...>, false>(column_index_sequence(), row_index_sequence()))
		{
			return OutMatrix_
			(
				_matrix_translate_multi_args_get_for_index<ColumnIndices_, RowIndices_, OutMatrix_>(args_tuple_)...
			);
		}
		else
		{
			static_assert
			(
				EmuCore::TMP::get_false<OutMatrix_>(),
				"Attempted to create a translation EmuMath Matrix, but at least one element of the provided output Matrix type cannot be constructed with the respective argument, a default 1 value, or a default 0 value."
			);
		}
	}

	template<class OutMatrix_, class TranslateArg_, std::size_t...ColumnIndices_, std::size_t...RowIndices_>
	[[nodiscard]] constexpr inline OutMatrix_ _matrix_translate_single_arg
	(
		std::index_sequence<ColumnIndices_...> column_indices_,
		std::index_sequence<RowIndices_...> row_indices_,
		TranslateArg_&& translate_args_
	)
	{
		using column_index_sequence = std::index_sequence<ColumnIndices_...>;
		using row_index_sequence = std::index_sequence<RowIndices_...>;
		using arg_uq = typename EmuCore::TMP::remove_ref_cv<TranslateArg_>::type;
		if constexpr (EmuCore::TMP::is_tuple_v<arg_uq>)
		{
			// Defer to multi-arg with tuples
			return _matrix_translate_multi_args<OutMatrix_>
			(
				column_index_sequence(),
				row_index_sequence(),
				EmuCore::TMP::lval_ref_cast<TranslateArg_>(std::forward<TranslateArg_>(translate_args_))
			);
		}
		else
		{
			if constexpr(_matrix_translate_single_arg_is_valid<OutMatrix_, TranslateArg_, false>(column_index_sequence(), row_index_sequence()))
			{
#pragma warning(push)
#pragma warning(disable: 26800)
				return OutMatrix_
				(
					_matrix_translate_single_arg_get_for_index<ColumnIndices_, RowIndices_, OutMatrix_>
					(
						std::forward<TranslateArg_>(translate_args_)
					)...
				);
#pragma warning(pop)
			}
			else
			{
				static_assert
				(
					EmuCore::TMP::get_false<OutMatrix_>(),
					"Attempted to create a translation EmuMath Matrix, but at least one element of the provided output Matrix type cannot be constructed with the provided argument, a default 1 value, or a default 0 value."
				);
			}
		}
	}

	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, bool OutColumnMajor_, class...TranslateArgs_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_> _matrix_translate(TranslateArgs_&&...translate_args_)
	{
		using out_matrix = EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>;
		using out_indices = EmuMath::TMP::make_full_matrix_index_sequences<out_matrix>;
		using column_indices = typename out_indices::column_index_sequence;
		using row_indices = typename out_indices::row_index_sequence;

		if constexpr (sizeof...(TranslateArgs_) == 1)
		{
			return _matrix_translate_single_arg<out_matrix>(column_indices(), row_indices(), std::forward<TranslateArgs_>(translate_args_)...);
		}
		else
		{
			return _matrix_translate_multi_args<out_matrix>
			(
				column_indices(),
				row_indices(),
				std::forward_as_tuple<TranslateArgs_...>(std::forward<TranslateArgs_>(translate_args_)...)
			);
		}
	}
#pragma endregion

#pragma region ASSIGNERS
	template<class OutMatrix_, class...Args_, std::size_t...ColumnIndices_, std::size_t...RowIndices_>
	constexpr inline void _matrix_translate_assign_multi_args
	(
		OutMatrix_& out_matrix_,
		std::index_sequence<ColumnIndices_...> column_indices_,
		std::index_sequence<RowIndices_...> row_indices_,
		std::tuple<Args_...> args_tuple_
	)
	{
		using column_index_sequence = std::index_sequence<ColumnIndices_...>;
		using row_index_sequence = std::index_sequence<RowIndices_...>;
		if constexpr (_matrix_translate_multi_args_is_valid<OutMatrix_, std::tuple<Args_...>, true>(column_index_sequence(), row_index_sequence()))
		{
			using out_mat_uq = typename EmuCore::TMP::remove_ref_cv<OutMatrix_>::type;
			using out_value_uq = typename out_mat_uq::value_type_uq;
			(
				(
					EmuCore::TMP::assign_direct_or_cast<out_value_uq>
					(
						out_matrix_.template at<ColumnIndices_, RowIndices_>(),
						_matrix_translate_multi_args_get_for_index<ColumnIndices_, RowIndices_, out_mat_uq>(args_tuple_)
					)
				), ...
			);
		}
		else
		{
			static_assert
			(
				EmuCore::TMP::get_false<OutMatrix_>(),
				"Attempted to assign a translation Matrix to an existing EmuMath Matrix, but the provided output Matrix type cannot be assigned to at least one index with the provided arguments, a default 1 value, or a default 0 value."
			);
		}
	}

	template<class OutMatrix_, class TranslateArg_, std::size_t...ColumnIndices_, std::size_t...RowIndices_>
	constexpr inline void _matrix_translate_assign_single_arg
	(
		OutMatrix_& out_matrix_,
		std::index_sequence<ColumnIndices_...> column_indices_,
		std::index_sequence<RowIndices_...> row_indices_,
		TranslateArg_&& translate_arg_
	)
	{
		using arg_uq = typename EmuCore::TMP::remove_ref_cv<TranslateArg_>::type;
		if constexpr (EmuCore::TMP::is_tuple_v<arg_uq>)
		{
			// Defer to multi-arg with tuples
			_matrix_translate_assign_multi_args<OutMatrix_>
			(
				out_matrix_,
				std::index_sequence<ColumnIndices_...>(),
				std::index_sequence<RowIndices_...>(),
				EmuCore::TMP::lval_ref_cast<TranslateArg_>(std::forward<TranslateArg_>(translate_arg_))
			);
		}
		else
		{
			using column_index_sequence = std::index_sequence<ColumnIndices_...>;
			using row_index_sequence = std::index_sequence<RowIndices_...>;
			if constexpr (_matrix_translate_single_arg_is_valid<OutMatrix_, TranslateArg_, true>(column_index_sequence(), row_index_sequence()))
			{
				using out_mat_uq = typename EmuCore::TMP::remove_ref_cv<OutMatrix_>::type;
				using out_value_uq = typename out_mat_uq::value_type_uq;
#pragma warning(push)
#pragma warning(disable: 26800)
				(
					(
						EmuCore::TMP::assign_direct_or_cast<out_value_uq>
						(
							out_matrix_.template at<ColumnIndices_, RowIndices_>(),
							_matrix_translate_single_arg_get_for_index<ColumnIndices_, RowIndices_, out_mat_uq>(std::forward<TranslateArg_>(translate_arg_))
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
					"Attempted to assign a translation Matrix to an existing EmuMath Matrix, but the provided output Matrix type cannot be assigned to at least one index with the provided arguments, a default 1 value, or a default 0 value."
				);
			}
		}
	}

	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, bool OutColumnMajor_, class...TranslateArgs_>
	constexpr inline void _matrix_translate_assign(EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>& out_matrix_, TranslateArgs_&&...translate_args_)
	{
		using out_matrix = EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>;
		using out_indices = EmuMath::TMP::make_full_matrix_index_sequences<out_matrix>;
		using column_indices = typename out_indices::column_index_sequence;
		using row_indices = typename out_indices::row_index_sequence;

		if constexpr (sizeof...(TranslateArgs_) == 1)
		{
			_matrix_translate_assign_single_arg<out_matrix>(out_matrix_, column_indices(), row_indices(), std::forward<TranslateArgs_>(translate_args_)...);
		}
		else
		{
			_matrix_translate_assign_multi_args<out_matrix>
			(
				out_matrix_,
				column_indices(),
				row_indices(),
				std::forward_as_tuple<TranslateArgs_...>(std::forward<TranslateArgs_>(translate_args_)...)
			);
		}
	}
#pragma endregion
}
#endif
