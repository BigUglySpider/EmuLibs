#ifndef EMU_MATH_MATRIX_MUTATE_H_INC_
#define EMU_MATH_MATRIX_MUTATE_H_INC_ 1

#include "_common_matrix_helper_includes.h"

// CONTAINS:
// --- mutate
// --- mutate_to
// --- mutate_copy
// --- mutate_copy_to
// --- mutate_invoke_only

namespace EmuMath::Helpers
{
#pragma region MUTATE_FUNCS
	/// <summary>
	/// <para> Outputs an EmuMath Matrix resulting from invoking invocations of the provided Func_ with the provided Args_ for every index. </para>
	/// <para> If a provided Arg_ is an EmuMath Matrix: The respective theoretical column/row index will be used as an argument instead of the Matrix itself. </para>
	/// <para> If a provided Arg_ is none of the above: All function invocations will use the provided Arg_ as is. </para>
	/// </summary>
	/// <param name="func_">Function to invoke for each mutation. This is considered not explicitly provided if the first template parameter is the Func_ type.</param>
	/// <param name="args_">: Arguments to invoke the mutation function via.</param>
	/// <returns>EmuMath Matrix containing the results of mutation invocation at respective indices using the provided arguments.</returns>
	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, bool OutColumnMajor_ = true, class Func_, class...Args_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_> matrix_mutate(Func_ func_, Args_&&...args_)
	{
		using func_lval_ref_type = decltype(EmuCore::TMP::lval_ref_cast<Func_>(std::forward<Func_>(func_)));
		func_lval_ref_type func_lval_ref_ = EmuCore::TMP::lval_ref_cast<Func_>(std::forward<Func_>(func_));
		return _matrix_underlying::_matrix_mutate_return_out<func_lval_ref_type, OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_, 0, OutNumColumns_, 0, OutNumRows_>
		(
			func_lval_ref_,
			std::forward<Args_>(args_)...
		);
	}

	/// <summary>
	/// <para> Outputs an EmuMath Matrix resulting from invoking invocations of the provided Func_ with the provided Args_ for every index. </para>
	/// <para> If a provided Arg_ is an EmuMath Matrix: The respective theoretical column/row index will be used as an argument instead of the Matrix itself. </para>
	/// <para> If a provided Arg_ is none of the above: All function invocations will use the provided Arg_ as is. </para>
	/// <para> The type arguments of the provided FuncTemplate_ will be decided based on the provided arguments on a per-iteration basis. </para>
	/// </summary>
	/// <param name="args_">: Arguments to invoke the mutation function via.</param>
	/// <returns>EmuMath Matrix containing the results of mutation invocation at respective indices using the provided arguments.</returns>
	template<template<class...> class FuncTemplate_, std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, bool OutColumnMajor_ = true, class...Args_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_> matrix_mutate(Args_&&...args_)
	{
		return _matrix_underlying::_matrix_mutate_return_out_func_template<FuncTemplate_, OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_, 0, OutNumColumns_, 0, OutNumRows_>
		(
			std::forward<Args_>(args_)...
		);
	}
#pragma endregion

#pragma region MUTATE_RANGE_FUNCS
	/// <summary>
	/// <para> Outputs an EmuMath Matrix resulting from invoking invocations of the provided Func_ with the provided Args_ for every index in the provided range. </para>
	/// <para> Indices outside of the specified range will be default constructed. </para>
	/// <para> If a provided Arg_ is an EmuMath Matrix: The respective theoretical column/row index will be used as an argument instead of the Matrix itself. </para>
	/// <para> If a provided Arg_ is none of the above: All function invocations will use the provided Arg_ as is. </para>
	/// </summary>
	/// <param name="func_">Function to invoke for each mutation. This is considered not explicitly provided if the first template parameter is the Func_ type.</param>
	/// <param name="args_">: Arguments to invoke the mutation function via.</param>
	/// <returns>
	///		EmuMath Matrix containing the results of mutation invocation at respective indices using the provided arguments, 
	///		and default elements outside of the provided range.
	/// </returns>
	template
	<
		std::size_t BeginColumn_,
		std::size_t EndColumn_,
		std::size_t BeginRow_,
		std::size_t EndRow_,
		std::size_t OutNumColumns_,
		std::size_t OutNumRows_,
		typename OutT_,
		bool OutColumnMajor_ = true,
		class Func_,
		class...Args_
	>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_> matrix_mutate_range(Func_ func_, Args_&&...args_)
	{
		using func_lval_ref_type = decltype(EmuCore::TMP::lval_ref_cast<Func_>(std::forward<Func_>(func_)));
		func_lval_ref_type func_lval_ref_ = EmuCore::TMP::lval_ref_cast<Func_>(std::forward<Func_>(func_));
		return _matrix_underlying::_matrix_mutate_return_out<func_lval_ref_type, OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_, BeginColumn_, EndColumn_, BeginRow_, EndRow_>
		(
			func_lval_ref_,
			std::forward<Args_>(args_)...
		);
	}

	template
	<
		template<class...> class FuncTemplate_,
		std::size_t BeginColumn_,
		std::size_t EndColumn_,
		std::size_t BeginRow_,
		std::size_t EndRow_,
		std::size_t OutNumColumns_,
		std::size_t OutNumRows_,
		typename OutT_,
		bool OutColumnMajor_ = true,
		class...Args_
	>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_> matrix_mutate_range(Args_&&...args_)
	{
		return _matrix_underlying::_matrix_mutate_return_out_func_template
		<
			FuncTemplate_,
			OutNumColumns_,
			OutNumRows_,
			OutT_,
			OutColumnMajor_,
			BeginColumn_,
			EndColumn_,
			BeginRow_,
			EndRow_
		>(std::forward<Args_>(args_)...);
	}
#pragma endregion

#pragma region MUTATE_TO_FUNCS
	/// <summary>
	/// <para> Outputs to the provided EmuMath Matrix via the results of invoking the provided mutation Func_ with the provided Args_. </para>
	/// <para> If a provided Arg_ is an EmuMath Matrix: The correct theoretical column/row index will be used as an argument instead of the Matrix itself. </para>
	/// <para> If a provided Arg_ is none of the above: All function invocations will use the provided Arg_ as is. </para>
	/// <para> ArgColumnOffset_: Offset from the output column index to use for reading Matrix arguments. Defaults to 0. </para>
	/// <para> ArgRowOffset_: Offset from the output row index to use for reading Matrix arguments. Defaults to 0. </para>
	/// </summary>
	/// <param name="out_matrix_">: EmuMath Matrix to output to.</param>
	/// <param name="func_">: Item to invoke for every mutation iteration.</param>
	/// <param name="args_">: All arguments to provide to the mutation function.</param>
	template
	<
		std::size_t ArgColumnOffset_ = 0,
		std::size_t ArgRowOffset_ = 0,
		class Func_,
		std::size_t OutNumColumns_,
		std::size_t OutNumRows_,
		typename OutT_,
		bool OutColumnMajor_,
		class...Args_
	>
	constexpr inline void matrix_mutate_to(EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>& out_matrix_, Func_ func_, Args_&&...args_)
	{
		using func_ref = std::add_lvalue_reference_t<Func_>;
		_matrix_underlying::_matrix_mutate_assign<func_ref, 0, OutNumColumns_, 0, OutNumRows_, ArgColumnOffset_, ArgRowOffset_>
		(
			out_matrix_,
			func_,
			std::forward<Args_>(args_)...
		);
	}

	/// <summary>
	/// <para> Outputs to the provided EmuMath Matrix via the results of invoking the provided mutation Func_ with the provided Args_. </para>
	/// <para> If a provided Arg_ is an EmuMath Matrix: The correct theoretical column/row index will be used as an argument instead of the Matrix itself. </para>
	/// <para> If a provided Arg_ is none of the above: All function invocations will use the provided Arg_ as is. </para>
	/// <para> ArgColumnOffset_: Offset from the output column index to use for reading Matrix arguments. Defaults to 0. </para>
	/// <para> ArgRowOffset_: Offset from the output row index to use for reading Matrix arguments. Defaults to 0. </para>
	/// <para> The type arguments of the provided FuncTemplate_ will be decided based on the provided arguments on a per-iteration basis. </para>
	/// </summary>
	/// <param name="out_matrix_">: EmuMath Matrix to output to.</param>
	/// <param name="args_">: All arguments to provide to the mutation function.</param>
	template
	<
		template<class...> class FuncTemplate_,
		std::size_t ArgColumnOffset_ = 0,
		std::size_t ArgRowOffset_ = 0,
		std::size_t OutNumColumns_,
		std::size_t OutNumRows_,
		typename OutT_,
		bool OutColumnMajor_,
		class...Args_
	>
	constexpr inline void matrix_mutate_to(EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>& out_matrix_, Args_&&...args_)
	{
		_matrix_underlying::_matrix_mutate_assign_func_template<FuncTemplate_, 0, OutNumColumns_, 0, OutNumRows_, ArgColumnOffset_, ArgRowOffset_>
		(
			out_matrix_,
			std::forward<Args_>(args_)...
		);
	} 

	/// <summary>
	/// <para> Outputs to the provided EmuMath Matrix within the provided range via the results of invoking the provided mutation Func_ with the provided Args_. </para>
	/// <para> If a provided Arg_ is an EmuMath Matrix: The correct theoretical column/row index will be used as an argument instead of the Matrix itself. </para>
	/// <para> If a provided Arg_ is none of the above: All function invocations will use the provided Arg_ as is. </para>
	/// <para> OutBeginColumn_: Inclusive column index at which to start outputting to the provided Matrix. </para>
	/// <para> OutEndColumn_: Exclusive column index at which to stop outputting to the provided Matrix. </para>
	/// <para> OutBeginRow_: Inclusive row index at which to start outputting to the provided Matrix. </para>
	/// <para> OutEndRow_: Exclusive row index at which to stop outputting to the provided Matrix. </para>
	/// <para> ArgColumnOffset_: Offset from the output column index to use for reading Matrix arguments. Defaults to 0. </para>
	/// <para> ArgRowOffset_: Offset from the output row index to use for reading Matrix arguments. Defaults to 0. </para>
	/// </summary>
	/// <param name="out_matrix_">: EmuMath Matrix to output to.</param>
	/// <param name="func_">: Function to invoke for each mutation.</param>
	/// <param name="args_">: All arguments to provide to the mutation function.</param>
	template
	<
		std::size_t OutBeginColumn_,
		std::size_t OutEndColumn_,
		std::size_t OutBeginRow_,
		std::size_t OutEndRow_,
		std::size_t ArgColumnOffset_ = 0,
		std::size_t ArgRowOffset_ = 0,
		class Func_,
		typename OutT_,
		std::size_t OutNumColumns_,
		std::size_t OutNumRows_,
		bool OutColumnMajor_,
		class...Args_
	>
	constexpr inline void matrix_mutate_to(EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>& out_matrix_, Func_ func_, Args_&&...args_)
	{
		using func_ref = std::add_lvalue_reference_t<Func_>;
		_matrix_underlying::_matrix_mutate_assign<func_ref, OutBeginColumn_, OutEndColumn_, OutBeginRow_, OutEndRow_, ArgColumnOffset_, ArgRowOffset_>
		(
			out_matrix_,
			func_,
			std::forward<Args_>(args_)...
		);
	}

	/// <summary>
	/// <para> Outputs to the provided EmuMath Matrix within the provided range via the results of invoking the provided mutation Func_ with the provided Args_. </para>
	/// <para> If a provided Arg_ is an EmuMath Matrix: The correct theoretical column/row index will be used as an argument instead of the Matrix itself. </para>
	/// <para> If a provided Arg_ is none of the above: All function invocations will use the provided Arg_ as is. </para>
	/// <para> OutBeginColumn_: Inclusive column index at which to start outputting to the provided Matrix. </para>
	/// <para> OutEndColumn_: Exclusive column index at which to stop outputting to the provided Matrix. </para>
	/// <para> OutBeginRow_: Inclusive row index at which to start outputting to the provided Matrix. </para>
	/// <para> OutEndRow_: Exclusive row index at which to stop outputting to the provided Matrix. </para>
	/// <para> ArgColumnOffset_: Offset from the output column index to use for reading Matrix arguments. Defaults to 0. </para>
	/// <para> ArgRowOffset_: Offset from the output row index to use for reading Matrix arguments. Defaults to 0. </para>
	/// <para> The type arguments of the provided FuncTemplate_ will be decided based on the provided arguments on a per-iteration basis. </para>
	/// </summary>
	/// <param name="out_matrix_">: EmuMath Matrix to output to.</param>
	/// <param name="args_">: All arguments to provide to the mutation function.</param>
	template
	<
		template<class...> class FuncTemplate_,
		std::size_t OutBeginColumn_,
		std::size_t OutEndColumn_,
		std::size_t OutBeginRow_,
		std::size_t OutEndRow_,
		std::size_t ArgColumnOffset_ = 0,
		std::size_t ArgRowOffset_ = 0,
		typename OutT_,
		std::size_t OutNumColumns_,
		std::size_t OutNumRows_,
		bool OutColumnMajor_,
		class...Args_
	>
	constexpr inline void matrix_mutate_to(EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>& out_matrix_, Args_&&...args_)
	{
		_matrix_underlying::_matrix_mutate_assign_func_template<FuncTemplate_, OutBeginColumn_, OutEndColumn_, OutBeginRow_, OutEndRow_, ArgColumnOffset_, ArgRowOffset_>
		(
			out_matrix_,
			std::forward<Args_>(args_)...
		);
	}
#pragma endregion

#pragma region MATRIX_MUTATE_COPY_FUNCS
	/// <summary>
	/// <para> Performs a partial copy-mutation of the provided EmuMath Matrix, using the provided args_ for the mutation function only. </para>
	/// <para> Note that in_matrix_ is not used as an argument for the mutation function; it must be provided a second time if this behaviour is wanted. </para>
	/// <para>
	///		The mutation function will be used within the specified inclusive:exclusive range MutBeginColumn_:MutEndColumn_, MutBeginRow_:MutEndRow_ for output indices. 
	///		Indices in the output Matrix outside of said range will be copies of respective indices in matrix_to_copy_.
	/// </para>
	/// <para>
	///		All arguments will have their column and row indices offset by ArgColumnOffset_ and ArgRowOffset_ respectively, 
	///		which are treated as offsets from the output Matrix's indices. This offset is used regardless of whether a copy or mutation operation is performed.
	/// </para>
	/// <para> The arguments for FuncTemplate_ will be automatically determined based on the provided arguments to this function. </para>
	/// </summary>
	/// <param name="matrix_to_copy_">: EmuMath Matrix to copy when mutations are not performed. This will not be passed to the mutation function.</param>
	/// <param name="args_">: All arguments to pass to the mutation function when it is invoked.</param>
	/// <returns>EmuMath Matrix with indices in the specified range containing mutation results, and those outside of said range copying indices of the passed in_matrix_.</returns>
	template
	<
		template<class...> class FuncTemplate_,
		std::size_t OutNumColumns_,
		std::size_t OutNumRows_,
		typename OutT_,
		bool OutColumnMajor_,
		std::size_t MutBeginColumn_,
		std::size_t MutEndColumn_,
		std::size_t MutBeginRow_,
		std::size_t MutEndRow_,
		std::size_t ArgColumnOffset_ = 0,
		std::size_t ArgRowOffset_ = 0,
		typename InT_,
		std::size_t InNumColumns_,
		std::size_t InNumRows_,
		bool InColumnMajor_,
		class...Args_
	>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_> matrix_mutate_copy
	(
		EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>& matrix_to_copy_,
		Args_&&...args_
	)
	{
		using in_matrix = EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>&;
		return _matrix_underlying::_matrix_mutate_copy_func_template
		<
			FuncTemplate_,
			in_matrix,
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
		>(matrix_to_copy_, std::forward<Args_>(args_)...);
	}

	template
	<
		template<class...> class FuncTemplate_,
		std::size_t OutNumColumns_,
		std::size_t OutNumRows_,
		typename OutT_,
		bool OutColumnMajor_,
		std::size_t MutBeginColumn_,
		std::size_t MutEndColumn_,
		std::size_t MutBeginRow_,
		std::size_t MutEndRow_,
		std::size_t ArgColumnOffset_ = 0,
		std::size_t ArgRowOffset_ = 0,
		typename InT_,
		std::size_t InNumColumns_,
		std::size_t InNumRows_,
		bool InColumnMajor_,
		class...Args_
	>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_> matrix_mutate_copy
	(
		const EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>& matrix_to_copy_,
		Args_&&...args_
	)
	{
		using in_matrix = const EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>&;
		return _matrix_underlying::_matrix_mutate_copy_func_template
		<
			FuncTemplate_,
			in_matrix,
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
		>(matrix_to_copy_, std::forward<Args_>(args_)...);
	}

	template
	<
		template<class...> class FuncTemplate_,
		std::size_t OutNumColumns_,
		std::size_t OutNumRows_,
		typename OutT_,
		bool OutColumnMajor_,
		std::size_t MutBeginColumn_,
		std::size_t MutEndColumn_,
		std::size_t MutBeginRow_,
		std::size_t MutEndRow_,
		std::size_t ArgColumnOffset_ = 0,
		std::size_t ArgRowOffset_ = 0,
		typename InT_,
		std::size_t InNumColumns_,
		std::size_t InNumRows_,
		bool InColumnMajor_,
		class...Args_
	>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_> matrix_mutate_copy
	(
		EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>&& matrix_to_copy_,
		Args_&&...args_
	)
	{
		using in_matrix = EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>;
		return _matrix_underlying::_matrix_mutate_copy_func_template
		<
			FuncTemplate_,
			in_matrix,
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
		>(std::forward<in_matrix>(matrix_to_copy_), std::forward<Args_>(args_)...);
	}

	/// <summary>
	/// <para> Performs a partial copy-mutation of the provided EmuMath Matrix, using the provided args_ for the mutation function only. </para>
	/// <para> Note that in_matrix_ is not used as an argument for the mutation function; it must be provided a second time if this behaviour is wanted. </para>
	/// <para>
	///		The mutation function will be used within the specified inclusive:exclusive range MutBeginColumn_:MutEndColumn_, MutBeginRow_:MutEndRow_ for output indices. 
	///		Indices in the output Matrix outside of said range will be copies of respective indices in matrix_to_copy_.
	/// </para>
	/// <para>
	///		All arguments will have their column and row indices offset by ArgColumnOffset_ and ArgRowOffset_ respectively, 
	///		which are treated as offsets from the output Matrix's indices. This offset is used regardless of whether a copy or mutation operation is performed.
	/// </para>
	/// </summary>
	/// <param name="matrix_to_copy_">: EmuMath Matrix to copy when mutations are not performed. This will not be passed to the mutation function.</param>
	/// <param name="func_">: Mutation function to invoke whenever a mutation is performed.</param>
	/// <param name="args_">: All arguments to pass to the mutation function when it is invoked.</param>
	/// <returns>EmuMath Matrix with indices in the specified range containing mutation results, and those outside of said range copying indices of the passed in_matrix_.</returns>
	template
	<
		std::size_t OutNumColumns_,
		std::size_t OutNumRows_,
		typename OutT_,
		bool OutColumnMajor_,
		std::size_t MutBeginColumn_,
		std::size_t MutEndColumn_,
		std::size_t MutBeginRow_,
		std::size_t MutEndRow_,
		std::size_t ArgColumnOffset_ = 0,
		std::size_t ArgRowOffset_ = 0,
		class Func_,
		typename InT_,
		std::size_t InNumColumns_,
		std::size_t InNumRows_,
		bool InColumnMajor_,
		class...Args_
	>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_> matrix_mutate_copy
	(
		EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>& in_matrix_,
		Func_ func_,
		Args_&&...args_
	)
	{
		using func_ref = std::add_lvalue_reference_t<Func_>;
		return _matrix_underlying::_matrix_mutate_copy
		<
			func_ref,
			EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>&,
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
		>(func_, in_matrix_, std::forward<Args_>(args_)...);
	}

	template
	<
		std::size_t OutNumColumns_,
		std::size_t OutNumRows_,
		typename OutT_,
		bool OutColumnMajor_,
		std::size_t MutBeginColumn_,
		std::size_t MutEndColumn_,
		std::size_t MutBeginRow_,
		std::size_t MutEndRow_,
		std::size_t ArgColumnOffset_ = 0,
		std::size_t ArgRowOffset_ = 0,
		class Func_,
		typename InT_,
		std::size_t InNumColumns_,
		std::size_t InNumRows_,
		bool InColumnMajor_,
		class...Args_
	>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_> matrix_mutate_copy
	(
		const EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>& in_matrix_,
		Func_ func_,
		Args_&&...args_
	)
	{
		using func_ref = std::add_lvalue_reference_t<Func_>;
		return _matrix_underlying::_matrix_mutate_copy
		<
			func_ref,
			const EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>&,
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
		>(func_, in_matrix_, std::forward<Args_>(args_)...);
	}

	template
	<
		std::size_t OutNumColumns_,
		std::size_t OutNumRows_,
		typename OutT_,
		bool OutColumnMajor_,
		std::size_t MutBeginColumn_,
		std::size_t MutEndColumn_,
		std::size_t MutBeginRow_,
		std::size_t MutEndRow_,
		std::size_t ArgColumnOffset_ = 0,
		std::size_t ArgRowOffset_ = 0,
		class Func_,
		typename InT_,
		std::size_t InNumColumns_,
		std::size_t InNumRows_,
		bool InColumnMajor_,
		class...Args_
	>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_> matrix_mutate_copy
	(
		EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>&& in_matrix_,
		Func_ func_,
		Args_&&...args_
	)
	{
		using func_ref = std::add_lvalue_reference_t<Func_>;
		using in_matrix_type = EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>;
		return _matrix_underlying::_matrix_mutate_copy
		<
			func_ref,
			in_matrix_type,
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
		>(func_, std::forward<in_matrix_type>(in_matrix_), std::forward<Args_>(args_)...);
	}
#pragma endregion

#pragma region MATRIX_MUTATE_COPY_TO_FUNCS
	/// <summary>
	/// <para> Performs a partial copy-mutation of the provided EmuMath Matrix, using the provided args_ for the mutation function only. </para>
	/// <para> Note that in_matrix_ is not used as an argument for the mutation function; it must be provided a second time if this behaviour is wanted. </para>
	/// <para>
	///		The mutation function will be used within the specified inclusive:exclusive range MutBeginColumn_:MutEndColumn_, MutBeginRow_:MutEndRow_ for output indices. 
	///		Indices in the output Matrix outside of said range will be copies of respective indices in matrix_to_copy_.
	/// </para>
	/// <para>
	///		All arguments will have their column and row indices offset by ArgColumnOffset_ and ArgRowOffset_ respectively, 
	///		which are treated as offsets from the output Matrix's indices. This offset is used regardless of whether a copy or mutation operation is performed.
	/// </para>
	/// </summary>
	/// <param name="out_matrix_">: EmuMath Matrix to output to.</param>
	/// <param name="matrix_to_copy_">: EmuMath Matrix to copy when mutations are not performed. This will not be passed to the mutation function.</param>
	/// <param name="func_">: Mutation function to invoke whenever a mutation is performed.</param>
	/// <param name="args_">: All arguments to pass to the mutation function when it is invoked.</param>
	template
	<
		std::size_t MutBeginColumn_,
		std::size_t MutEndColumn_,
		std::size_t MutBeginRow_,
		std::size_t MutEndRow_,
		std::size_t ArgColumnOffset_ = 0,
		std::size_t ArgRowOffset_ = 0,
		class Func_,
		typename OutT_,
		std::size_t OutNumColumns_,
		std::size_t OutNumRows_,
		bool OutColumnMajor_,
		typename InT_,
		std::size_t InNumColumns_,
		std::size_t InNumRows_,
		bool InColumnMajor_,
		class...Args_
	>
	[[nodiscard]] constexpr inline void matrix_mutate_copy_to
	(
		EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>& out_matrix_,
		EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>& in_matrix_,
		Func_ func_,
		Args_&&...args_
	)
	{
		using func_ref = std::add_lvalue_reference_t<Func_>;
		_matrix_underlying::_matrix_mutate_copy_assign
		<
			func_ref,
			EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>&,
			MutBeginColumn_,
			MutEndColumn_,
			MutBeginRow_,
			MutEndRow_,
			ArgColumnOffset_,
			ArgRowOffset_
		>(out_matrix_, in_matrix_, func_, std::forward<Args_>(args_)...);
	}

	template
	<
		std::size_t MutBeginColumn_,
		std::size_t MutEndColumn_,
		std::size_t MutBeginRow_,
		std::size_t MutEndRow_,
		std::size_t ArgColumnOffset_ = 0,
		std::size_t ArgRowOffset_ = 0,
		class Func_,
		typename OutT_,
		std::size_t OutNumColumns_,
		std::size_t OutNumRows_,
		bool OutColumnMajor_,
		typename InT_,
		std::size_t InNumColumns_,
		std::size_t InNumRows_,
		bool InColumnMajor_,
		class...Args_
	>
	[[nodiscard]] constexpr inline void matrix_mutate_copy_to
	(
		EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>& out_matrix_,
		const EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>& in_matrix_,
		Func_ func_,
		Args_&&...args_
	)
	{
		using func_ref = std::add_lvalue_reference_t<Func_>;
		_matrix_underlying::_matrix_mutate_copy_assign
		<
			func_ref,
			const EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>&,
			MutBeginColumn_,
			MutEndColumn_,
			MutBeginRow_,
			MutEndRow_,
			ArgColumnOffset_,
			ArgRowOffset_
		>(out_matrix_, in_matrix_, func_, std::forward<Args_>(args_)...);
	}

	template
	<
		std::size_t MutBeginColumn_,
		std::size_t MutEndColumn_,
		std::size_t MutBeginRow_,
		std::size_t MutEndRow_,
		std::size_t ArgColumnOffset_ = 0,
		std::size_t ArgRowOffset_ = 0,
		class Func_,
		typename OutT_,
		std::size_t OutNumColumns_,
		std::size_t OutNumRows_,
		bool OutColumnMajor_,
		typename InT_,
		std::size_t InNumColumns_,
		std::size_t InNumRows_,
		bool InColumnMajor_,
		class...Args_
	>
	[[nodiscard]] constexpr inline void matrix_mutate_copy_to
	(
		EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>& out_matrix_,
		EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>&& in_matrix_,
		Func_ func_,
		Args_&&...args_
	)
	{
		using in_matrix_type = EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>;
		using func_ref = std::add_lvalue_reference_t<Func_>;
		_matrix_underlying::_matrix_mutate_copy_assign
		<
			func_ref,
			in_matrix_type,
			MutBeginColumn_,
			MutEndColumn_,
			MutBeginRow_,
			MutEndRow_,
			ArgColumnOffset_,
			ArgRowOffset_
		>(out_matrix_, std::forward<in_matrix_type>(in_matrix_), func_, std::forward<Args_>(args_)...);
	}

	/// <summary>
	/// <para> Performs a partial copy-mutation of the provided EmuMath Matrix, using the provided args_ for the mutation function only. </para>
	/// <para> Note that in_matrix_ is not used as an argument for the mutation function; it must be provided a second time if this behaviour is wanted. </para>
	/// <para>
	///		The mutation function will be used within the specified inclusive:exclusive range MutBeginColumn_:MutEndColumn_, MutBeginRow_:MutEndRow_ for output indices. 
	///		Indices in the output Matrix outside of said range will be copies of respective indices in matrix_to_copy_.
	/// </para>
	/// <para>
	///		All arguments will have their column and row indices offset by ArgColumnOffset_ and ArgRowOffset_ respectively, 
	///		which are treated as offsets from the output Matrix's indices. This offset is used regardless of whether a copy or mutation operation is performed.
	/// </para>
	/// <para> The arguments for FuncTemplate_ will be automatically determined based on the provided arguments to this function. </para>
	/// </summary>
	/// <param name="out_matrix_">: EmuMath Matrix to output to.</param>
	/// <param name="matrix_to_copy_">: EmuMath Matrix to copy when mutations are not performed. This will not be passed to the mutation function.</param>
	/// <param name="func_">: Mutation function to invoke whenever a mutation is performed.</param>
	/// <param name="args_">: All arguments to pass to the mutation function when it is invoked.</param>
	template
	<
		template<class...> class FuncTemplate_,
		std::size_t MutBeginColumn_,
		std::size_t MutEndColumn_,
		std::size_t MutBeginRow_,
		std::size_t MutEndRow_,
		std::size_t ArgColumnOffset_ = 0,
		std::size_t ArgRowOffset_ = 0,
		typename OutT_,
		std::size_t OutNumColumns_,
		std::size_t OutNumRows_,
		bool OutColumnMajor_,
		typename InT_,
		std::size_t InNumColumns_,
		std::size_t InNumRows_,
		bool InColumnMajor_,
		class...Args_
	>
	[[nodiscard]] constexpr inline void matrix_mutate_copy_to
	(
		EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>& out_matrix_,
		EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>& in_matrix_,
		Args_&&...args_
	)
	{
		_matrix_underlying::_matrix_mutate_copy_assign_func_template
		<
			FuncTemplate_,
			EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>&,
			MutBeginColumn_,
			MutEndColumn_,
			MutBeginRow_,
			MutEndRow_,
			ArgColumnOffset_,
			ArgRowOffset_
		>(out_matrix_, in_matrix_, std::forward<Args_>(args_)...);
	}

	template
	<
		template<class...> class FuncTemplate_,
		std::size_t MutBeginColumn_,
		std::size_t MutEndColumn_,
		std::size_t MutBeginRow_,
		std::size_t MutEndRow_,
		std::size_t ArgColumnOffset_ = 0,
		std::size_t ArgRowOffset_ = 0,
		typename OutT_,
		std::size_t OutNumColumns_,
		std::size_t OutNumRows_,
		bool OutColumnMajor_,
		typename InT_,
		std::size_t InNumColumns_,
		std::size_t InNumRows_,
		bool InColumnMajor_,
		class...Args_
	>
	[[nodiscard]] constexpr inline void matrix_mutate_copy_to
	(
		EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>& out_matrix_,
		const EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>& in_matrix_,
		Args_&&...args_
	)
	{
		_matrix_underlying::_matrix_mutate_copy_assign_func_template
		<
			FuncTemplate_,
			const EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>&,
			MutBeginColumn_,
			MutEndColumn_,
			MutBeginRow_,
			MutEndRow_,
			ArgColumnOffset_,
			ArgRowOffset_
		>(out_matrix_, in_matrix_, std::forward<Args_>(args_)...);
	}

	template
	<
		template<class...> class FuncTemplate_,
		std::size_t MutBeginColumn_,
		std::size_t MutEndColumn_,
		std::size_t MutBeginRow_,
		std::size_t MutEndRow_,
		std::size_t ArgColumnOffset_ = 0,
		std::size_t ArgRowOffset_ = 0,
		typename OutT_,
		std::size_t OutNumColumns_,
		std::size_t OutNumRows_,
		bool OutColumnMajor_,
		typename InT_,
		std::size_t InNumColumns_,
		std::size_t InNumRows_,
		bool InColumnMajor_,
		class...Args_
	>
	[[nodiscard]] constexpr inline void matrix_mutate_copy_to
	(
		EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>& out_matrix_,
		EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>&& in_matrix_,
		Args_&&...args_
	)
	{
		using in_matrix_type = EmuMath::Matrix<InNumColumns_, InNumRows_, InT_, InColumnMajor_>;
		_matrix_underlying::_matrix_mutate_copy_assign_func_template
		<
			FuncTemplate_,
			in_matrix_type,
			MutBeginColumn_,
			MutEndColumn_,
			MutBeginRow_,
			MutEndRow_,
			ArgColumnOffset_,
			ArgRowOffset_
		>(out_matrix_, std::forward<in_matrix_type>(in_matrix_), std::forward<Args_>(args_)...);
	}
#pragma endregion

#pragma region MATRIX_MUTATE_INVOKE_ONLY_FUNCS
	/// <summary>
	/// <para> Performs an EmuMath Matrix mutation without producing any output. Ideal for operations with similar semantics to operator++. </para>
	/// <para> As there is no output, a custom range and execution order must be provided. </para>
	/// <para> BeginColumn_: Inclusive column index at which to start reading EmuMath Matrix arguments. </para>
	/// <para> EndColumn_: Exclusive column index at which to stop reading EmuMath Matrix arguments. </para>
	/// <para> BeginRow_: Inclusive row index at which to start reading EmuMath Matrix arguments. </para>
	/// <para> EndRow_: Exclusive row index at which to stop reading EmuMath Matrix arguments. </para>
	/// <para> ColumnMajor_: True to execute in column-major order, false to execute in row-major order. </para>
	/// </summary>
	/// <param name="func_">: Function to invoke with the provided arguments.</param>
	/// <param name="args_">: Arguments to provide to function invocation.</param>
	template<std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_, bool ColumnMajor_, class Func_, class...Args_>
	constexpr inline void matrix_mutate_invoke_only(Func_ func_, Args_&&...args_)
	{
		using func_lval_ref_type = decltype(EmuCore::TMP::lval_ref_cast<Func_>(std::forward<Func_>(func_)));
		func_lval_ref_type func_lval_ref_ = EmuCore::TMP::lval_ref_cast<Func_>(std::forward<Func_>(func_));
		_matrix_underlying::_matrix_mutate_invoke_only<BeginColumn_, EndColumn_, BeginRow_, EndRow_, ColumnMajor_, func_lval_ref_type>
		(
			func_lval_ref_,
			std::forward<Args_>(args_)...
		);
	}

	/// <summary>
	/// <para> Performs an EmuMath Matrix mutation without producing any output. Ideal for operations with similar semantics to operator++. </para>
	/// <para> As there is no output, a custom range and execution order must be provided. </para>
	/// <para> BeginColumn_: Inclusive column index at which to start reading EmuMath Matrix arguments. </para>
	/// <para> EndColumn_: Exclusive column index at which to stop reading EmuMath Matrix arguments. </para>
	/// <para> BeginRow_: Inclusive row index at which to start reading EmuMath Matrix arguments. </para>
	/// <para> EndRow_: Exclusive row index at which to stop reading EmuMath Matrix arguments. </para>
	/// <para> ColumnMajor_: True to execute in column-major order, false to execute in row-major order. </para>
	/// <para> The typeargs for FuncTemplate_ will be decided based on the provided arguments on a per-iteration basis. </para>
	/// </summary>
	/// <param name="args_">: Arguments to provide to function invocation.</param>
	template<template<class...> class FuncTemplate_, std::size_t BeginColumn_, std::size_t EndColumn_, std::size_t BeginRow_, std::size_t EndRow_, bool ColumnMajor_, class...Args_>
	constexpr inline void matrix_mutate_invoke_only(Args_&&...args_)
	{
		_matrix_underlying::_matrix_mutate_invoke_only_func_template<FuncTemplate_, BeginColumn_, EndColumn_, BeginRow_, EndRow_, ColumnMajor_>(std::forward<Args_>(args_)...);
	}
#pragma endregion
}

#endif
