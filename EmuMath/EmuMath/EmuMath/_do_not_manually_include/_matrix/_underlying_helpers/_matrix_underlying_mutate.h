#ifndef EMU_MATH_MATRIX_MUTATE_UNDERLYING_H_INC_
#define EMU_MATH_MATRIX_MUTATE_UNDERLYING_H_INC_ 1

#include "_matrix_tmp.h"
#include "_matrix_underlying_get.h"
#include "../../../../EmuCore/TMPHelpers/VariadicHelpers.h"

namespace EmuMath::Helpers::_matrix_underlying
{
#pragma region HELPER_RANGE_CHECKS
	template<std::size_t ColumnIndex_, std::size_t RowIndex_, std::size_t MutBeginColumn_, std::size_t MutEndColumn_, std::size_t MutBeginRow_, std::size_t MutEndRow_>
	[[nodiscard]] static constexpr inline bool _matrix_mutate_invocation_in_mut_range()
	{
		constexpr std::size_t in_colunn_mut_range_ = (ColumnIndex_ >= MutBeginColumn_) && (ColumnIndex_ < MutEndColumn_);
		return in_colunn_mut_range_ && (RowIndex_ >= MutBeginRow_) && (RowIndex_ < MutEndRow_);
	}
#pragma endregion

#pragma region HELPER_TYPE_FINDERS
	template<typename InT_, std::size_t ColumnIndex_, std::size_t RowIndex_>
	struct _matrix_get_mutation_argument_return
	{
	private:
		template<typename In_, bool InIsMatrix_ = EmuMath::TMP::is_emu_matrix_v<In_>>
		struct _type_finder
		{
			using type = In_;
		};

		template<typename In_>
		struct _type_finder<In_, false>
		{
			using type = std::add_lvalue_reference_t<In_>;
		};

		template<typename In_>
		struct _type_finder<In_, true>
		{
			using type = typename EmuMath::TMP::matrix_theoretical_get_result<ColumnIndex_, RowIndex_, In_>::type;
		};

	public:
		using type = typename _type_finder<InT_>::type;
	};

	template
	<
		std::size_t ColumnIndex_,
		std::size_t RowIndex_,
		class OutMatrix_,
		class Func_,
		std::size_t MutBeginColumn_,
		std::size_t MutEndColumn_,
		std::size_t MutBeginRow_,
		std::size_t MutEndRow_,
		class...Args_
	>
	struct _matrix_mutate_execution_invoke_result
	{
	private:
		template
		<
			std::size_t Column_,
			std::size_t Row_,
			bool InMutRange_ = _matrix_mutate_invocation_in_mut_range<Column_, Row_, MutBeginColumn_, MutEndColumn_, MutBeginRow_, MutEndRow_>()
		>
		struct _type_finder_template
		{
			static constexpr bool success = false;
			using type = void;
		};

		template<std::size_t Column_, std::size_t Row_>
		struct _type_finder_template<Column_, Row_, false>
		{
			static constexpr bool success = true;
			using type = decltype(_matrix_get_non_contained<OutMatrix_>());
		};

		template<std::size_t Column_, std::size_t Row_>
		struct _type_finder_template<Column_, Row_, true>
		{
		private:
			using _safe_invoke_result = EmuCore::TMP::safe_invoke_result<Func_, typename _matrix_get_mutation_argument_return<Args_, Column_, Row_>::type...>;

		public:
			using type = typename _safe_invoke_result::type;
			static constexpr bool success = _safe_invoke_result::value && !std::is_void_v<type>;
		};

		using _type_finder = _type_finder_template<ColumnIndex_, RowIndex_>;

	public:
		static constexpr bool success = _type_finder::success;
		using type = typename _type_finder::type;
	};
#pragma endregion

#pragma region HELPER_EXTRACTORS
	template<class T_, std::size_t ColumnIndex_, std::size_t RowIndex_>
	[[nodiscard]] constexpr inline typename _matrix_get_mutation_argument_return<T_, ColumnIndex_, RowIndex_>::type _matrix_get_mutation_argument
	(
		std::add_lvalue_reference_t<T_> arg_
	)
	{
		if constexpr (EmuMath::TMP::is_emu_matrix_v<T_>)
		{
			return _matrix_get_theoretical<ColumnIndex_, RowIndex_>(arg_);
		}
		else
		{
			return arg_;
		}
	}
#pragma endregion

#pragma region MUTATION_EXECUTION
	template<std::size_t ColumnIndex_, std::size_t RowIndex_, class Func_, class...Args_>
	[[nodiscard]] constexpr inline typename EmuCore::TMP::safe_invoke_result
	<
		std::add_lvalue_reference_t<Func_>,
		typename _matrix_get_mutation_argument_return<std::add_lvalue_reference_t<Args_>, ColumnIndex_, RowIndex_>::type...
	>::type _matrix_mutate_invoke_func(std::add_lvalue_reference_t<Func_> func_, std::add_lvalue_reference_t<Args_>...args_)
	{
		using func_ref = std::add_lvalue_reference_t<Func_>;
		if constexpr (std::is_invocable_v<func_ref, decltype(_matrix_get_mutation_argument<Args_, ColumnIndex_, RowIndex_>(args_))...>)
		{
			return func_
			(
				_matrix_get_mutation_argument<Args_, ColumnIndex_, RowIndex_>(args_)...
			);
		}
		else
		{
			static_assert
			(
				EmuCore::TMP::get_false<Func_>(),
				"Attempted to invoke a function for EmuMath Matrix mutation, but the provided func_ could not be invoked with the provided args_."
			);
		}
	}

	template
	<
		std::size_t ColumnIndex_,
		std::size_t RowIndex_,
		class OutMatrix_,
		class Func_,
		std::size_t MutBeginColumn_,
		std::size_t MutEndColumnn_,
		std::size_t MutBeginRow_,
		std::size_t MutEndRow_,
		class...Args_
	>
	[[nodiscard]] constexpr inline typename EmuCore::TMP::remove_ref_cv_t<OutMatrix_>::stored_type
	_matrix_mutate_execution_for_index_stored_type_out(std::add_lvalue_reference_t<Func_> func_, std::add_lvalue_reference_t<Args_>...args_)
	{
		using out_type = typename EmuCore::TMP::remove_ref_cv_t<OutMatrix_>::stored_type;

		if constexpr (_matrix_mutate_invocation_in_mut_range<ColumnIndex_, RowIndex_, MutBeginColumn_, MutEndColumnn_, MutBeginRow_, MutEndRow_>())
		{
			using result_finder = _matrix_mutate_execution_invoke_result
			<
				ColumnIndex_, RowIndex_, OutMatrix_, Func_, MutBeginColumn_, MutEndColumnn_, MutBeginRow_, MutEndRow_, Args_&...
			>;

			if constexpr (result_finder::success)
			{
				using result_type = typename result_finder::type;
				if constexpr (std::is_constructible_v<out_type, result_type>)
				{
					return out_type(_matrix_mutate_invoke_func<ColumnIndex_, RowIndex_, Func_, Args_...>(func_, args_...));
				}
				else if constexpr (EmuCore::TMP::is_static_castable_v<result_type, out_type>)
				{
					return static_cast<out_type>(_matrix_mutate_invoke_func<ColumnIndex_, RowIndex_, Func_, Args_...>(func_, args_...));
				}
				else
				{
					static_assert
					(
						EmuCore::TMP::get_false<Func_>(),
						"Attempted to perform an EmuMath Matrix mutation with a newly constructed output, but at least one invocation of the provided mutation Func_ returned a result that could not be used to create the output Matrix's stored_type."
					);
				}
			}
			else
			{
				static_assert
				(
					EmuCore::TMP::get_false<Func_>(),
					"Attempted to perform an EmuMath Matrix mutation with a newly constructed output, but at least one iteration could not invoke the provided mutation Func_ successfully."
				);
			}
		}
		else
		{
			using result_type = decltype(_matrix_get_non_contained<OutMatrix_>());
			if constexpr (std::is_constructible_v<out_type, result_type>)
			{
				return out_type(_matrix_get_non_contained<OutMatrix_>());
			}
			else if constexpr (EmuCore::TMP::is_static_castable_v<result_type, out_type>)
			{
				return static_cast<out_type>(_matrix_get_non_contained<OutMatrix_>());
			}
			else
			{
				static_assert
				(
					EmuCore::TMP::get_false<OutMatrix_>(),
					"Attempted to perform an EmuMath Matrix mutation with a newly constructed output and some indices in the output Matrix not performing mutation, but the output Matrix's stored_type could not be formed from the result of retrieving one of its non-contained, implied-zero values."
				);
			}
		}
	}

	template
	<
		class OutMatrix_,
		class Func_,
		std::size_t MutBeginColumn_,
		std::size_t MutEndColumn_,
		std::size_t MutBeginRow_,
		std::size_t MutEndRow_,
		class...Args_,
		std::size_t...OutColumnIndices_,
		std::size_t...OutRowIndices_
	>
	[[nodiscard]] constexpr inline OutMatrix_ _matrix_mutate_execution_return_out
	(
		std::index_sequence<OutColumnIndices_...> out_column_indices_,
		std::index_sequence<OutRowIndices_...> out_row_indices_,
		std::add_lvalue_reference_t<Func_> func_,
		std::add_lvalue_reference_t<Args_>...args_
	)
	{
		constexpr bool is_constructible = std::is_constructible_v
		<
			OutMatrix_,
			decltype
			(
				_matrix_mutate_execution_for_index_stored_type_out
				<
					OutColumnIndices_,
					OutRowIndices_,
					OutMatrix_,
					Func_,
					MutBeginColumn_,
					MutEndColumn_,
					MutBeginRow_,
					MutEndRow_,
					Args_...
				>(func_, args_...)
			)...
		>;

		if constexpr (is_constructible)
		{
			return OutMatrix_
			(
				_matrix_mutate_execution_for_index_stored_type_out
				<
					OutColumnIndices_,
					OutRowIndices_,
					OutMatrix_,
					Func_,
					MutBeginColumn_,
					MutEndColumn_,
					MutBeginRow_,
					MutEndRow_,
					Args_...
				>(func_, args_...)...
			);
		}
		else
		{
			static_assert
			(
				EmuCore::TMP::get_false<OutMatrix_>(),
				"Attempted to perform an EmuMath Matrix mutation with a newly constructed output, but the provided output Matrix cannot be formed from arguments of its stored_type for every element (i.e. 1 stored_type per element)."
			);
		}
	}
#pragma endregion

#pragma region MUTATION_INVOCATION
	template
	<
		class Func_,
		std::size_t OutNumColumns_,
		std::size_t OutNumRows_,
		typename OutT_,
		bool OutColumnMajor_,
		std::size_t MutBeginColumn_,
		std::size_t MutEndColumn_,
		std::size_t MutBeginRow_,
		std::size_t MutEndRow_,
		class...Args_
	>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_> _matrix_mutate_return_out(Func_&& func_, Args_&&...args_)
	{
		using out_matrix = EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>;
		using out_indices = EmuMath::TMP::make_full_matrix_index_sequences<out_matrix>;
		using column_indices = typename out_indices::column_index_sequence;
		using row_indices = typename out_indices::row_index_sequence;
		using func_lval_ref_type = decltype(EmuCore::TMP::lval_ref_cast<Func_>(std::forward<Func_>(func_)));
		func_lval_ref_type func_lval_ref_ = EmuCore::TMP::lval_ref_cast<Func_>(std::forward<Func_>(func_));

		return _matrix_mutate_execution_return_out
		<
			out_matrix,
			func_lval_ref_type,
			MutBeginColumn_,
			MutEndColumn_,
			MutBeginRow_,
			MutEndRow_,
			decltype(EmuCore::TMP::lval_ref_cast<Args_>(std::forward<Args_>(args_)))...
		>(column_indices(), row_indices(), func_lval_ref_, EmuCore::TMP::lval_ref_cast<Args_>(std::forward<Args_>(args_))...);
	}

	template
	<
		class Func_,
		std::size_t OutNumColumns_,
		std::size_t OutNumRows_,
		typename OutT_,
		bool OutColumnMajor_,
		std::size_t MutBeginColumn_,
		std::size_t MutEndColumn_,
		std::size_t MutBeginRow_,
		std::size_t MutEndRow_,
		class...Args_
	>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_> _matrix_mutate_return_out_no_func_passed(Args_&&...args_)
	{
		if constexpr (std::is_default_constructible_v<Func_>)
		{
			return _matrix_mutate_return_out
			<
				Func_,
				OutNumColumns_,
				OutNumRows_,
				OutT_,
				OutColumnMajor_,
				MutBeginColumn_,
				MutEndColumn_,
				MutBeginRow_,
				MutEndRow_
			>(Func_(), std::forward<Args_>(args_)...);
		}
		else
		{
			static_assert
			(
				EmuCore::TMP::get_false<Func_>(),
				"Attempted to perform an EmuMath Matrix mutation without passing a func_ instance. This is allowed if the provided Func_ type must be default-constructible, but the current provided Func_ is not default-constructible."
			);
		}
	}

	template
	<
		std::size_t ColumnIndex_,
		std::size_t RowIndex_,
		class Func_,
		class OutMatrix_,
		std::int64_t ArgColumnOffset_,
		std::int64_t ArgRowOffset_,
		class...Args_
	>
	constexpr inline void _matrix_mutate_assign_index(OutMatrix_& out_matrix_, std::add_lvalue_reference_t<Func_> func_, std::add_lvalue_reference_t<Args_>...args_)
	{
		if constexpr(_matrix_index_is_contained<ColumnIndex_, RowIndex_, OutMatrix_>())
		{
			using safe_result_finder = EmuCore::TMP::safe_invoke_result
			<
				std::add_lvalue_reference_t<Func_>,
				typename _matrix_get_mutation_argument_return<std::add_lvalue_reference_t<Args_>, ColumnIndex_, RowIndex_>::type...
			>;

			if constexpr (safe_result_finder::value)
			{
				constexpr std::size_t arg_column_ = static_cast<std::size_t>(ColumnIndex_ + ArgColumnOffset_);
				constexpr std::size_t arg_row_ = static_cast<std::size_t>(RowIndex_ + ArgRowOffset_);
				using result_type = typename safe_result_finder::type;
				using out_get_type = decltype(_matrix_get<ColumnIndex_, RowIndex_>(out_matrix_));
				if constexpr (std::is_assignable_v<out_get_type, result_type>)
				{
					using out_get_uq = EmuCore::TMP::remove_ref_cv_t<out_get_type>;
					using result_uq = EmuCore::TMP::remove_ref_cv_t<result_type>;
					if constexpr (std::is_arithmetic_v<out_get_uq> && std::is_arithmetic_v<result_uq> && !std::is_same_v<out_get_uq, result_uq>)
					{
						// Perform a static_cast if target and result are different arithmetic types
						_matrix_get<ColumnIndex_, RowIndex_>(out_matrix_) = static_cast<out_get_uq>
						(
							_matrix_mutate_invoke_func<arg_column_, arg_row_, Func_, Args_...>(func_, args_...)
						);
					}
					else
					{
						_matrix_get<ColumnIndex_, RowIndex_>(out_matrix_) = _matrix_mutate_invoke_func<arg_column_, arg_row_, Func_, Args_...>(func_, args_...);
					}
				}
				else
				{
					using out_value_type_uq = typename EmuCore::TMP::remove_ref_cv_t<OutMatrix_>::value_type_uq;
					if constexpr (std::is_assignable_v<out_get_type, out_value_type_uq>)
					{
						if constexpr (std::is_constructible_v<out_value_type_uq, result_type>)
						{
							_matrix_get<ColumnIndex_, RowIndex_>(out_matrix_) = out_value_type_uq
							(
								_matrix_mutate_invoke_func<arg_column_, arg_row_, Func_, Args_...>(func_, args_...)
							);
						}
						else if constexpr (EmuCore::TMP::is_static_castable_v<result_type, out_value_type_uq>)
						{
							_matrix_get<ColumnIndex_, RowIndex_>(out_matrix_) = static_cast<out_value_type_uq>
							(
								_matrix_mutate_invoke_func<arg_column_, arg_row_, Func_, Args_...>(func_, args_...)
							);
						}
						else
						{
							static_assert
							(
								EmuCore::TMP::get_false<OutMatrix_>(),
								"Attempted to perform an EmuMath Matrix mutation with results assigned to an existing output Matrix, but at least one mutation result could neither be used to directly assign to one of the output Matrix's elements, nor to create a value_type_uq of the output Matrix to assign an element via."
							);
						}
					}
					else
					{
						static_assert
						(
							EmuCore::TMP::get_false<OutMatrix_>(),
							"Attempted to perform an EmuMath Matrix mutation with results assigned to an existing output Matrix, but at least one mutation result could not be used to assign an item within the output Matrix, and the output Matrix cannot have an element assigned via its value_type_uq."
						);
					}
				}
			}
			else
			{
				static_assert
				(
					EmuCore::TMP::get_false<Func_>(),
					"Attempted to perform an EmuMath Matrix mutation with results assigned to an existing output Matrix, but at least one iteration could not invoke the provided mutation Func_ successfully."
				);
			}
		}
		else
		{
			static_assert
			(
				EmuCore::TMP::get_false<OutMatrix_>(),
				"Attempted to perform an EmuMath Matrix mutation with results assigned to an existing output Matrix, but at least one index in the provided output range is not contained within the output Matrix."
			);
		}
	}

	template
	<
		class Func_,
		class OutMatrix_,
		std::int64_t ArgColumnOffset_,
		std::int64_t ArgRowOffset_,
		class...Args_,
		std::size_t...OutColumnIndices_,
		std::size_t...OutRowIndices_
	>
	constexpr inline void _matrix_mutate_assign_execution
	(
		std::index_sequence<OutColumnIndices_...> out_column_indices_,
		std::index_sequence<OutRowIndices_...> out_row_indices_,
		std::add_lvalue_reference_t<OutMatrix_> out_matrix_,
		std::add_lvalue_reference_t<Func_> func_,
		std::add_lvalue_reference_t<Args_>...args_
	)
	{
		(
			_matrix_mutate_assign_index<OutColumnIndices_, OutRowIndices_, Func_, OutMatrix_, ArgColumnOffset_, ArgRowOffset_, Args_...>
			(
				out_matrix_,
				func_,
				args_...
			), ...
		);
	}

	template
	<
		class Func_,
		std::size_t OutBeginColumn_,
		std::size_t OutEndColumn_,
		std::size_t OutBeginRow_,
		std::size_t OutEndRow_,
		std::size_t ArgColumnOffset_,
		std::size_t ArgRowOffset_,
		std::size_t OutNumColumns_,
		std::size_t OutNumRows_,
		typename OutT_,
		bool OutColumnMajor_,
		class...Args_
	>
	constexpr inline void _matrix_mutate_assign(EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>& out_matrix_, Func_&& func_, Args_&&...args_)
	{
		using output_indices = EmuMath::TMP::make_ranged_matrix_index_sequences<OutBeginColumn_, OutEndColumn_, OutBeginRow_, OutEndRow_, OutColumnMajor_>;
		using column_index_sequence = typename output_indices::column_index_sequence;
		using row_index_sequence = typename output_indices::row_index_sequence;
		using out_matrix = EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>;
		using func_lval_ref_type = decltype(EmuCore::TMP::lval_ref_cast<Func_>(std::forward<Func_>(func_)));
		func_lval_ref_type func_lval_ref_ = EmuCore::TMP::lval_ref_cast<Func_>(std::forward<Func_>(func_));

		return _matrix_mutate_assign_execution
		<
			func_lval_ref_type,
			out_matrix,
			ArgColumnOffset_,
			ArgRowOffset_,
			decltype(EmuCore::TMP::lval_ref_cast<Args_>(std::forward<Args_>(args_)))...
		>(column_index_sequence(), row_index_sequence(), out_matrix_, func_lval_ref_, EmuCore::TMP::lval_ref_cast<Args_>(std::forward<Args_>(args_))...);
	}

	template
	<
		class Func_,
		std::size_t OutBeginColumn_,
		std::size_t OutEndColumn_,
		std::size_t OutBeginRow_,
		std::size_t OutEndRow_,
		std::size_t ArgColumnOffset_,
		std::size_t ArgRowOffset_,
		std::size_t OutNumColumns_,
		std::size_t OutNumRows_,
		typename OutT_,
		bool OutColumnMajor_,
		class...Args_
	>
	constexpr inline void _matrix_mutate_assign_no_func_passed(EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>& out_matrix_, Args_&&...args_)
	{
		if constexpr (std::is_default_constructible_v<Func_>)
		{
			return _matrix_mutate_assign<Func_, OutBeginColumn_, OutEndColumn_, OutBeginRow_, OutEndRow_, ArgColumnOffset_, ArgRowOffset_>
			(
				out_matrix_,
				Func_(),
				std::forward<Args_>(args_)...
			);
		}
		else
		{
			static_assert
			(
				EmuCore::TMP::get_false<Func_>(),
				"Attempted to perform an EmuMath Matrix mutation, with mutation results assigned to an existing Matrix, without providing an instance of the provided Func_ type. This is allowed, but the provided Func_ type is not default-constructible. Being default-constructible is a requirement if not passing an instance of Func_."
			);
		}
	}
#pragma endregion
}

#endif
