#ifndef EMU_MATH_MATRIX_MUTATE_UNDERLYING_H_INC_
#define EMU_MATH_MATRIX_MUTATE_UNDERLYING_H_INC_ 1

#include "_matrix_tmp.h"
#include "_matrix_underlying_copy.h"
#include "_matrix_underlying_get.h"
#include "../../../../EmuCore/TMPHelpers/Tuples.h"
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

	

	template<template<class...> class FuncTemplate_, std::size_t ColumnIndex_, std::size_t RowIndex_, class LeftTuple_, class RightTuple_, class...Args_>
	struct _matrix_make_mutation_func_from_args
	{
	private:
		static constexpr bool _valid_args = EmuCore::TMP::is_tuple_v<LeftTuple_> && EmuCore::TMP::is_tuple_v<RightTuple_>;
		static_assert
		(
			_valid_args,
			"Underlying EmuMath Failure: Provided a non-tuple type argument to _matrix_make_mutation_func_from_args for either its LeftTuple_ or RightTuple_ arguments."
		);

		template<class FullTuple_>
		struct _builder
		{
			using type = void;
		};

		template<class...FullArgs_>
		struct _builder<std::tuple<FullArgs_...>>
		{
			using type = EmuCore::TMP::safe_template_instantiate
			<
				FuncTemplate_,
				EmuCore::TMP::remove_ref_cv_t<typename _matrix_get_mutation_argument_return<FullArgs_, ColumnIndex_, RowIndex_>::type>...
			>;
		};

		using _left_and_centre = EmuCore::TMP::join_tuples_t<LeftTuple_, std::tuple<Args_...>>;
		using _full_tuple = EmuCore::TMP::join_tuples_t<_left_and_centre, RightTuple_>;
		using _safe_instantiation = typename _builder<_full_tuple>::type;

	public:
		using type = typename _safe_instantiation::type;;
		static constexpr bool is_valid = std::conditional_t<_valid_args, _safe_instantiation, std::false_type>::value;
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
		std::size_t ColumnIndex_,
		std::size_t RowIndex_,
		template<class...> class FuncTemplate_,
		class OutMatrix_,
		std::int64_t ArgColumnOffset_,
		std::int64_t ArgRowOffset_,
		class LeftArgTuple_,
		class RightArgTuple_,
		class...Args_
	>
	constexpr inline void _matrix_mutate_assign_index_func_template(OutMatrix_& out_matrix_, std::add_lvalue_reference_t<Args_>...args_)
	{
		using func_instantiator = _matrix_make_mutation_func_from_args<FuncTemplate_, ColumnIndex_, RowIndex_, LeftArgTuple_, RightArgTuple_, Args_...>;
		if constexpr (func_instantiator::is_valid)
		{
			using Func_ = typename func_instantiator::type;
			if constexpr (std::is_default_constructible_v<Func_>)
			{
				Func_ func_ = Func_();
				_matrix_mutate_assign_index<ColumnIndex_, RowIndex_, Func_, OutMatrix_, ArgColumnOffset_, ArgRowOffset_, Args_...>(out_matrix_, func_, args_...);
			}
			else
			{
				static_assert
				(
					EmuCore::TMP::get_false<Func_>(),
					"Attempted to perform an EmuMath Matrix mutation with a mutation template function whose type arguments are decided based on passed arguments, but the instantiated Func_ cannot be default constructed."
				);
			}
		}
		else
		{
			static_assert
			(
				EmuCore::TMP::get_false<Args_...>(),
				"Attempted to perform an EmuMath Matrix mutation with a mutation template function whose type arguments are decided based on passed arguments, but the provided FuncTemplate_ could not be instantiated using all unqualified arguments (or their value_type_uq if they are an EmuMath Matrix)."
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
		OutMatrix_& out_matrix_,
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

#pragma region AUTO_FUNC_TEMPLATE_MUTATIONS
	template
	<
		template<class...> class FuncTemplate_,
		std::size_t ColumnIndex_,
		std::size_t RowIndex_,
		class OutMatrix_,
		class LeftArgsTuple_,
		class RightArgsTuple_,
		class...Args_
	>
	[[nodiscard]] constexpr inline typename OutMatrix_::stored_type _matrix_mutate_for_index_func_template_stored_type_out(std::add_lvalue_reference_t<Args_>...args_)
	{
		using instantiator = _matrix_make_mutation_func_from_args<FuncTemplate_, ColumnIndex_, RowIndex_, LeftArgsTuple_, RightArgsTuple_, Args_...>;
		if constexpr (instantiator::is_valid)
		{
			using Func_ = typename instantiator::type;
			if constexpr (std::is_default_constructible_v<Func_>)
			{
				Func_ func_ = Func_();
				return _matrix_mutate_execution_for_index_stored_type_out
				<
					ColumnIndex_,
					RowIndex_,
					OutMatrix_,
					Func_,
					ColumnIndex_,
					ColumnIndex_ + 1,
					RowIndex_,
					RowIndex_ + 1,
					Args_...
				>(func_, args_...);
			}
			else
			{
				static_assert
				(
					EmuCore::TMP::get_false<Func_>(),
					"Attempted to perform an EmuMath Matrix mutation with a function template whose arguments are automatically decided based on unqualified arguments, but the determined template instance cannot be default-constructed."
				);
			}
		}
		else
		{
			static_assert
			(
				EmuCore::TMP::get_false<instantiator>(),
				"Attempted to perform an EmuMath Matrix mutation with a function template whose arguments are automatically decided based on unqualified arguments, but the provided template could not successfully be instantiated with the all of the provided arguments."
			);
		}
	}
#pragma endregion

#pragma region MUTATE_COPY_HYBRID_FUNCS_EXECUTION
	template
	<
		class Func_,
		std::size_t ColumnIndex_,
		std::size_t RowIndex_,
		class OutMatrix_,
		class InMatrix_,
		std::size_t MutBeginColumn_,
		std::size_t MutEndColumn_,
		std::size_t MutBeginRow_,
		std::size_t MutEndRow_,
		std::size_t ArgColumnOffset_,
		std::size_t ArgRowOffset_,
		class...Args_
	>
	[[nodiscard]] constexpr inline typename OutMatrix_::stored_type _matrix_mutate_copy_execution_for_index_stored_type_out
	(
		InMatrix_&& in_matrix_,
		std::add_lvalue_reference_t<Func_> func_,
		std::add_lvalue_reference_t<Args_>...args_
	)
	{
		constexpr bool is_mut_column_ = (ColumnIndex_ >= MutBeginColumn_) && (ColumnIndex_ < MutEndColumn_);
		constexpr std::size_t arg_column_ = ColumnIndex_ + ArgColumnOffset_;
		constexpr std::size_t arg_row_ = RowIndex_ + ArgRowOffset_;
		if constexpr (is_mut_column_ && (RowIndex_ >= MutBeginRow_) && (RowIndex_ < MutEndRow_))
		{
			return _matrix_mutate_execution_for_index_stored_type_out<arg_column_, arg_row_, OutMatrix_, Func_, arg_column_, arg_column_ + 1, arg_row_, arg_row_ + 1, Args_...>
			(
				func_,
				args_...
			);
		}
		else
		{	// Disable Visual Studio warning about using moved-from object, as we aren't accessing anything after it is moved (if a move occurs)
#pragma warning(push)
#pragma warning(disable: 26800)
			return _matrix_create_out_from_index<OutMatrix_, InMatrix_, arg_column_, arg_row_>(std::forward<InMatrix_>(in_matrix_));
#pragma warning(pop)
		}
	}

	template
	<
		template<class...> class FuncTemplate_,
		std::size_t ColumnIndex_,
		std::size_t RowIndex_,
		class OutMatrix_,
		class InMatrix_,
		std::size_t MutBeginColumn_,
		std::size_t MutEndColumn_,
		std::size_t MutBeginRow_,
		std::size_t MutEndRow_,
		std::size_t ArgColumnOffset_,
		std::size_t ArgRowOffset_,
		class LeftArgsTuple_,
		class RightArgsTuple_,
		class...Args_
	>
	[[nodiscard]] constexpr inline typename OutMatrix_::stored_type _matrix_mutate_copy_execution_for_index_func_template_stored_type_out
	(
		InMatrix_&& in_matrix_,
		std::add_lvalue_reference_t<Args_>...args_
	)
	{
		constexpr bool is_mut_column_ = (ColumnIndex_ >= MutBeginColumn_) && (ColumnIndex_ < MutEndColumn_);
		constexpr std::size_t arg_column_ = ColumnIndex_ + ArgColumnOffset_;
		constexpr std::size_t arg_row_ = RowIndex_ + ArgRowOffset_;
		if constexpr (is_mut_column_ && (RowIndex_ >= MutBeginRow_) && (RowIndex_ < MutEndRow_))
		{
			return _matrix_mutate_for_index_func_template_stored_type_out<FuncTemplate_, arg_column_, arg_row_, OutMatrix_, LeftArgsTuple_, RightArgsTuple_, Args_...>
			(
				args_...
			);
		}
		else
		{	// Disable Visual Studio warning about using moved-from object, as we aren't accessing anything after it is moved (if a move occurs)
#pragma warning(push)
#pragma warning(disable: 26800)
			return _matrix_create_out_from_index<OutMatrix_, InMatrix_, arg_column_, arg_row_>(std::forward<InMatrix_>(in_matrix_));
#pragma warning(pop)
		}
	}

	template
	<
		class Func_,
		std::size_t ColumnIndex_,
		std::size_t RowIndex_,
		class OutMatrix_,
		class InMatrix_,
		std::size_t MutBeginColumn_,
		std::size_t MutEndColumn_,
		std::size_t MutBeginRow_,
		std::size_t MutEndRow_,
		std::size_t ArgColumnOffset_,
		std::size_t ArgRowOffset_,
		class...Args_
	>
	constexpr inline void _matrix_mutate_copy_assign_execution_for_index
	(
		OutMatrix_& out_matrix_,
		InMatrix_&& in_matrix_,
		std::add_lvalue_reference_t<Func_> func_,
		std::add_lvalue_reference_t<Args_>...args_
	)
	{
		constexpr bool is_mut_column_ = (ColumnIndex_ >= MutBeginColumn_) && (ColumnIndex_ < MutEndColumn_);
		if constexpr (is_mut_column_ && (RowIndex_ >= MutBeginRow_) && (RowIndex_ < MutEndRow_))
		{
			_matrix_mutate_assign_index<ColumnIndex_, RowIndex_, Func_, OutMatrix_, ArgColumnOffset_, ArgRowOffset_, Args_...>(out_matrix_, func_, args_...);
		}
		else
		{
			constexpr std::size_t arg_column_ = ColumnIndex_ + ArgColumnOffset_;
			constexpr std::size_t arg_row_ = RowIndex_ + ArgRowOffset_;
			_matrix_copy_index<OutMatrix_, InMatrix_, ColumnIndex_, RowIndex_, arg_column_, arg_row_>(out_matrix_, std::forward<InMatrix_>(in_matrix_));
		}
	}

	template
	<
		template<class...> class FuncTemplate_,
		std::size_t ColumnIndex_,
		std::size_t RowIndex_,
		class OutMatrix_,
		class InMatrix_,
		std::size_t MutBeginColumn_,
		std::size_t MutEndColumn_,
		std::size_t MutBeginRow_,
		std::size_t MutEndRow_,
		std::size_t ArgColumnOffset_,
		std::size_t ArgRowOffset_,
		class LeftArgTuple_,
		class RightArgTuple_,
		class...Args_
	>
	constexpr inline void _matrix_mutate_copy_assign_execution_for_index_func_template
	(
		OutMatrix_& out_matrix_,
		InMatrix_&& in_matrix_,
		std::add_lvalue_reference_t<Args_>...args_
	)
	{
		constexpr bool is_mut_column_ = (ColumnIndex_ >= MutBeginColumn_) && (ColumnIndex_ < MutEndColumn_);
		if constexpr (is_mut_column_ && (RowIndex_ >= MutBeginRow_) && (RowIndex_ < MutEndRow_))
		{
			_matrix_mutate_assign_index_func_template<ColumnIndex_, RowIndex_, FuncTemplate_, OutMatrix_, ArgColumnOffset_, ArgRowOffset_, LeftArgTuple_, RightArgTuple_, Args_...>
			(
				out_matrix_,
				args_...
			);
		}
		else
		{
			constexpr std::size_t arg_column_ = ColumnIndex_ + ArgColumnOffset_;
			constexpr std::size_t arg_row_ = RowIndex_ + ArgRowOffset_;
			_matrix_copy_index<OutMatrix_, InMatrix_, ColumnIndex_, RowIndex_, arg_column_, arg_row_>(out_matrix_, std::forward<InMatrix_>(in_matrix_));
		}
	}

	template
	<
		class Func_,
		class OutMatrix_,
		class InMatrix_,
		std::size_t MutBeginColumn_,
		std::size_t MutEndColumn_,
		std::size_t MutBeginRow_,
		std::size_t MutEndRow_,
		std::size_t ArgColumnOffset_,
		std::size_t ArgRowOffset_,
		class...Args_,
		std::size_t...OutColumnIndices_,
		std::size_t...OutRowIndices_
	>
	constexpr inline void _matrix_mutate_copy_assign_execution
	(
		std::index_sequence<OutColumnIndices_...> out_column_indices_,
		std::index_sequence<OutRowIndices_...> out_row_indices_,
		OutMatrix_& out_matrix_,
		InMatrix_&& in_matrix_,
		std::add_lvalue_reference_t<Func_> func_,
		std::add_lvalue_reference_t<Args_>...args_
	)
	{
		(
			_matrix_mutate_copy_assign_execution_for_index
			<
				Func_,
				OutColumnIndices_,
				OutRowIndices_,
				OutMatrix_,
				InMatrix_,
				MutBeginColumn_,
				MutEndColumn_,
				MutBeginRow_,
				MutEndRow_,
				ArgColumnOffset_,
				ArgRowOffset_,
				Args_...
			>(out_matrix_, std::forward<InMatrix_>(in_matrix_), func_, args_...), ...
		);
	}

	template
	<
		template<class...> class FuncTemplate_,
		class OutMatrix_,
		class InMatrix_,
		std::size_t MutBeginColumn_,
		std::size_t MutEndColumn_,
		std::size_t MutBeginRow_,
		std::size_t MutEndRow_,
		std::size_t ArgColumnOffset_,
		std::size_t ArgRowOffset_,
		class LeftArgTuple_,
		class RightArgTuple_,
		class...Args_,
		std::size_t...OutColumnIndices_,
		std::size_t...OutRowIndices_
	>
	constexpr inline void _matrix_mutate_copy_assign_execution_func_template
	(
		std::index_sequence<OutColumnIndices_...> out_column_indices_,
		std::index_sequence<OutRowIndices_...> out_row_indices_,
		OutMatrix_& out_matrix_,
		InMatrix_&& in_matrix_,
		std::add_lvalue_reference_t<Args_>...args_
	)
	{
		(
			_matrix_mutate_copy_assign_execution_for_index_func_template
			<
				FuncTemplate_,
				OutColumnIndices_,
				OutRowIndices_,
				OutMatrix_,
				InMatrix_,
				MutBeginColumn_,
				MutEndColumn_,
				MutBeginRow_,
				MutEndRow_,
				ArgColumnOffset_,
				ArgRowOffset_,
				LeftArgTuple_,
				RightArgTuple_,
				Args_...
			>(out_matrix_, std::forward<InMatrix_>(in_matrix_), args_...), ...
		);
	}

	template
	<
		class Func_,
		class OutMatrix_,
		class InMatrix_,
		std::size_t MutBeginColumn_,
		std::size_t MutEndColumn_,
		std::size_t MutBeginRow_,
		std::size_t MutEndRow_,
		std::size_t ArgColumnOffset_,
		std::size_t ArgRowOffset_,
		class...Args_,
		std::size_t...OutColumnIndices_,
		std::size_t...OutRowIndices_
	>
	[[nodiscard]] constexpr inline OutMatrix_ _matrix_mutate_copy_execution
	(
		std::index_sequence<OutColumnIndices_...> out_column_indices_,
		std::index_sequence<OutRowIndices_...> out_row_indices_,
		InMatrix_&& in_matrix_,
		std::add_lvalue_reference_t<Func_> func_,
		std::add_lvalue_reference_t<Args_>...args_
	)
	{
		constexpr bool is_constructible_ = std::is_constructible_v
		<
			OutMatrix_,
			decltype
			(
				_matrix_mutate_copy_execution_for_index_stored_type_out
				<
					Func_,
					OutColumnIndices_,
					OutRowIndices_,
					OutMatrix_,
					InMatrix_,
					MutBeginColumn_,
					MutEndColumn_,
					MutBeginRow_,
					MutEndRow_,
					ArgColumnOffset_,
					ArgRowOffset_,
					Args_...
				>(std::forward<InMatrix_>(in_matrix_), func_, args_...)
			)...
		>;

		if constexpr (is_constructible_)
		{
			return OutMatrix_
			(
				_matrix_mutate_copy_execution_for_index_stored_type_out
				<
					Func_,
					OutColumnIndices_,
					OutRowIndices_,
					OutMatrix_,
					InMatrix_,
					MutBeginColumn_,
					MutEndColumn_,
					MutBeginRow_,
					MutEndRow_,
					ArgColumnOffset_,
					ArgRowOffset_,
					Args_...
				>(std::forward<InMatrix_>(in_matrix_), func_, args_...)...
			);
		}
		else
		{
			static_assert
			(
				EmuCore::TMP::get_false<OutMatrix_>(),
				"Attempted to perform a partial EmuMath Matrix copy-mutate operation, but the provided output Matrix type cannot be constructed from a stored_type for each element (i.e. one stored_type argument per element)."
			);
		}
	}

	template
	<
		template<class...> class FuncTemplate_,
		class OutMatrix_,
		class InMatrix_,
		std::size_t MutBeginColumn_,
		std::size_t MutEndColumn_,
		std::size_t MutBeginRow_,
		std::size_t MutEndRow_,
		std::size_t ArgColumnOffset_,
		std::size_t ArgRowOffset_,
		class LeftArgsTuple_,
		class RightArgsTuple_,
		class...Args_,
		std::size_t...OutColumnIndices_,
		std::size_t...OutRowIndices_
	>
	[[nodiscard]] constexpr inline OutMatrix_ _matrix_mutate_copy_execution_func_template
	(
		std::index_sequence<OutColumnIndices_...> out_column_indices_,
		std::index_sequence<OutRowIndices_...> out_row_indices_,
		InMatrix_&& in_matrix_,
		std::add_lvalue_reference_t<Args_>...args_
	)
	{
		constexpr bool is_constructible_ = std::is_constructible_v
		<
			OutMatrix_,
			decltype
			(
				_matrix_mutate_copy_execution_for_index_func_template_stored_type_out
				<
					FuncTemplate_,
					OutColumnIndices_,
					OutRowIndices_,
					OutMatrix_,
					InMatrix_,
					MutBeginColumn_,
					MutEndColumn_,
					MutBeginRow_,
					MutEndRow_,
					ArgColumnOffset_,
					ArgRowOffset_,
					LeftArgsTuple_,
					RightArgsTuple_,
					Args_...
				>(std::forward<InMatrix_>(in_matrix_), args_...)
			)...
		>;

		if constexpr (is_constructible_)
		{
			return OutMatrix_
			(
				_matrix_mutate_copy_execution_for_index_func_template_stored_type_out
				<
					FuncTemplate_,
					OutColumnIndices_,
					OutRowIndices_,
					OutMatrix_,
					InMatrix_,
					MutBeginColumn_,
					MutEndColumn_,
					MutBeginRow_,
					MutEndRow_,
					ArgColumnOffset_,
					ArgRowOffset_,
					LeftArgsTuple_,
					RightArgsTuple_,
					Args_...
				>(std::forward<InMatrix_>(in_matrix_), args_...)...
			);
		}
		else
		{
			static_assert
			(
				EmuCore::TMP::get_false<OutMatrix_>(),
				"Attempted to perform a partial EmuMath Matrix copy-mutate operation, but the provided output Matrix type cannot be constructed from a stored_type for each element (i.e. one stored_type argument per element)."
			);
		}
	}
#pragma endregion

#pragma region MUTATE_COPY_HYBRID_FUNCS_INVOCATION
	template
	<
		class Func_,
		class InMatrix_,
		std::size_t MutBeginColumn_,
		std::size_t MutEndColumn_,
		std::size_t MutBeginRow_,
		std::size_t MutEndRow_,
		std::size_t ArgColumnOffset_,
		std::size_t ArgRowOffset_,
		typename OutT_,
		std::size_t OutNumColumns_,
		std::size_t OutNumRows_,
		bool OutColumnMajor_,
		class...Args_
	>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_> _matrix_mutate_copy(Func_&& func_, InMatrix_&& in_matrix_, Args_&&...args_)
	{
		using out_matrix = EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>;
		using output_indices = EmuMath::TMP::make_full_matrix_index_sequences<out_matrix>;
		using column_index_sequence = typename output_indices::column_index_sequence;
		using row_index_sequence = typename output_indices::row_index_sequence;
		auto& func_lval_ref_ = EmuCore::TMP::lval_ref_cast<Func_>(std::forward<Func_>(func_));
		using func_lval_ref_type = decltype(func_lval_ref_);
		return _matrix_mutate_copy_execution
		<
			func_lval_ref_type,
			out_matrix,
			InMatrix_,
			MutBeginColumn_,
			MutEndColumn_,
			MutBeginRow_,
			MutEndRow_,
			ArgColumnOffset_,
			ArgRowOffset_,
			decltype(EmuCore::TMP::lval_ref_cast<Args_>(std::forward<Args_>(args_)))...
		>(column_index_sequence(), row_index_sequence(), std::forward<InMatrix_>(in_matrix_), func_lval_ref_, EmuCore::TMP::lval_ref_cast<Args_>(std::forward<Args_>(args_))...);
	}

	template
	<
		template<class...> class FuncTemplate_,
		class InMatrix_,
		class LeftExtraArgsTuple_,
		class RightExtraArgsTuple_,
		std::size_t MutBeginColumn_,
		std::size_t MutEndColumn_,
		std::size_t MutBeginRow_,
		std::size_t MutEndRow_,
		std::size_t ArgColumnOffset_,
		std::size_t ArgRowOffset_,
		typename OutT_,
		std::size_t OutNumColumns_,
		std::size_t OutNumRows_,
		bool OutColumnMajor_,
		class...Args_
	>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_> _matrix_mutate_copy_func_template(InMatrix_&& in_matrix_, Args_&&...args_)
	{
		using out_matrix = EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>;
		using output_indices = EmuMath::TMP::make_full_matrix_index_sequences<out_matrix>;
		using column_index_sequence = typename output_indices::column_index_sequence;
		using row_index_sequence = typename output_indices::row_index_sequence;
		return _matrix_mutate_copy_execution_func_template
		<
			FuncTemplate_,
			out_matrix,
			InMatrix_,
			MutBeginColumn_,
			MutEndColumn_,
			MutBeginRow_,
			MutEndRow_,
			ArgColumnOffset_,
			ArgRowOffset_,
			LeftExtraArgsTuple_,
			RightExtraArgsTuple_,
			decltype(EmuCore::TMP::lval_ref_cast<Args_>(std::forward<Args_>(args_)))...
		>(column_index_sequence(), row_index_sequence(), std::forward<InMatrix_>(in_matrix_), EmuCore::TMP::lval_ref_cast<Args_>(std::forward<Args_>(args_))...);
	}

	template
	<
		template<class...> class FuncTemplate_,
		class InMatrix_,
		std::size_t MutBeginColumn_,
		std::size_t MutEndColumn_,
		std::size_t MutBeginRow_,
		std::size_t MutEndRow_,
		std::size_t ArgColumnOffset_,
		std::size_t ArgRowOffset_,
		typename OutT_,
		std::size_t OutNumColumns_,
		std::size_t OutNumRows_,
		bool OutColumnMajor_,
		class...Args_
	>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_> _matrix_mutate_copy_func_template(InMatrix_&& in_matrix_, Args_&&...args_)
	{
		// Well this looks horrifying
		return _matrix_mutate_copy_func_template
		<
			FuncTemplate_,
			InMatrix_,
			std::tuple<>,
			std::tuple<>,
			MutBeginColumn_,
			MutEndColumn_,
			MutBeginRow_,
			MutEndRow_,
			ArgColumnOffset_,
			ArgRowOffset_,
			OutT_,
			OutNumColumns_,
			OutNumRows_,
			OutColumnMajor_
		>(std::forward<InMatrix_>(in_matrix_), std::forward<Args_>(args_)...);
	}

	template
	<
		class Func_,
		class InMatrix_,
		std::size_t MutBeginColumn_,
		std::size_t MutEndColumn_,
		std::size_t MutBeginRow_,
		std::size_t MutEndRow_,
		std::size_t ArgColumnOffset_,
		std::size_t ArgRowOffset_,
		typename OutT_,
		std::size_t OutNumColumns_,
		std::size_t OutNumRows_,
		bool OutColumnMajor_,
		class...Args_
	>
	constexpr inline void _matrix_mutate_copy_assign
	(
		EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>& out_matrix_,
		InMatrix_&& in_matrix_,
		Func_&& func_,
		Args_&&...args_
	)
	{
		using out_matrix = EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>;
		using output_indices = EmuMath::TMP::make_full_matrix_index_sequences<out_matrix>;
		using column_indices = typename output_indices::column_index_sequence;
		using row_indices = typename output_indices::row_index_sequence;
		auto& func_lval_ref_ = EmuCore::TMP::lval_ref_cast<Func_>(std::forward<Func_>(func_));
		using func_lval_ref_type = decltype(func_lval_ref_);
		_matrix_mutate_copy_assign_execution
		<
			func_lval_ref_type,
			out_matrix,
			InMatrix_,
			MutBeginColumn_,
			MutEndColumn_,
			MutBeginRow_,
			MutEndRow_,
			ArgColumnOffset_,
			ArgRowOffset_,
			decltype(EmuCore::TMP::lval_ref_cast<Args_>(std::forward<Args_>(args_)))...
		>(column_indices(), row_indices(), out_matrix_, std::forward<InMatrix_>(in_matrix_), func_lval_ref_, EmuCore::TMP::lval_ref_cast<Args_>(std::forward<Args_>(args_))...);
	}

	template
	<
		template<class...> class FuncTemplate_,
		class InMatrix_,
		std::size_t MutBeginColumn_,
		std::size_t MutEndColumn_,
		std::size_t MutBeginRow_,
		std::size_t MutEndRow_,
		std::size_t ArgColumnOffset_,
		std::size_t ArgRowOffset_,
		typename OutT_,
		std::size_t OutNumColumns_,
		std::size_t OutNumRows_,
		bool OutColumnMajor_,
		class LeftExtraArgsTuple_,
		class RightExtraArgsTuple_,
		class...Args_
	>
	constexpr inline void _matrix_mutate_copy_assign_func_template
	(
		EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>& out_matrix_,
		InMatrix_&& in_matrix_,
		Args_&&...args_
	)
	{
		using out_matrix = EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>;
		using output_indices = EmuMath::TMP::make_full_matrix_index_sequences<out_matrix>;
		using column_indices = typename output_indices::column_index_sequence;
		using row_indices = typename output_indices::row_index_sequence;
		_matrix_mutate_copy_assign_execution_func_template
		<
			FuncTemplate_,
			out_matrix,
			InMatrix_,
			MutBeginColumn_,
			MutEndColumn_,
			MutBeginRow_,
			MutEndRow_,
			ArgColumnOffset_,
			ArgRowOffset_,
			LeftExtraArgsTuple_,
			RightExtraArgsTuple_,
			decltype(EmuCore::TMP::lval_ref_cast<Args_>(std::forward<Args_>(args_)))...
		>(column_indices(), row_indices(), out_matrix_, std::forward<InMatrix_>(in_matrix_), EmuCore::TMP::lval_ref_cast<Args_>(std::forward<Args_>(args_))...);
	}

	template
	<
		template<class...> class FuncTemplate_,
		class InMatrix_,
		std::size_t MutBeginColumn_,
		std::size_t MutEndColumn_,
		std::size_t MutBeginRow_,
		std::size_t MutEndRow_,
		std::size_t ArgColumnOffset_,
		std::size_t ArgRowOffset_,
		typename OutT_,
		std::size_t OutNumColumns_,
		std::size_t OutNumRows_,
		bool OutColumnMajor_,
		class...Args_
	>
	constexpr inline void _matrix_mutate_copy_assign_func_template
	(
		EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>& out_matrix_,
		InMatrix_&& in_matrix_,
		Args_&&...args_
	)
	{
		_matrix_mutate_copy_assign_func_template
		<
			FuncTemplate_,
			InMatrix_,
			MutBeginColumn_,
			MutEndColumn_,
			MutBeginRow_,
			MutEndRow_,
			ArgColumnOffset_,
			ArgRowOffset_,
			OutT_,
			OutNumColumns_,
			OutNumRows_,
			OutColumnMajor_,
			std::tuple<>,
			std::tuple<>
		>(out_matrix_, std::forward<InMatrix_>(in_matrix_), std::forward<Args_>(args_)...);
	}
#pragma endregion
}

#endif
