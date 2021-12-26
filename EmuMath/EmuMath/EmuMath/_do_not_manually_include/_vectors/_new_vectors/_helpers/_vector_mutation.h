#ifndef EMU_MATH_NEW_VECTOR_MUTATION_H_INC_
#define EMU_MATH_NEW_VECTOR_MUTATION_H_INC_ 1

#include "_common_vector_helpers.h"

// CONTAINS:
// --- shuffle
// --- shuffle_theoretical
// --- mutate

namespace EmuMath::Helpers
{
#pragma region SHUFFLE_FUNCS
	/// <summary>
	/// <para> Creates a new EmuMath Vector, with the provided OutT_ used as the output Vector's T_ argument, via specified indices within the input vector_. </para>
	/// <para> The Size_ of the output Vector will be equal to the provided number of Indices_. </para>
	/// <para> OutT_ is optional, and defaults to the passed vector_'s value_type_uq. </para>
	/// <para> There is no upper limit for the amount of indices to be provided, but at least 1 argument must be provided for Indices_. </para>
	/// <para> This may not be used to access theoretical indices; for such behaviour, use `vector_shuffle_theoretical` instead. </para>
	/// </summary>
	/// <typeparam name="OutT_">T_ argument for the output Vector. Defaults to the passed vector_'s value_type_uq.</typeparam>
	/// <param name="vector_">EmuMath Vector to retrieve indices from.</param>
	/// <returns>EmuMath Vector with a number of elements equal to the number of Indices_ arguments, constructed from shuffled indices within the passed vector_.</returns>
	template<typename OutT_, std::size_t...Indices_, std::size_t Size_, typename T_, typename = std::enable_if_t<sizeof...(Indices_) != 0>>
	[[nodiscard]] constexpr inline EmuMath::NewVector<sizeof...(Indices_), OutT_> new_vector_shuffle(EmuMath::NewVector<Size_, T_>& vector_)
	{
		return _vector_underlying::_vector_shuffle<OutT_, false, Indices_...>(vector_);
	}
	template<std::size_t...Indices_, std::size_t Size_, typename T_, typename = std::enable_if_t<sizeof...(Indices_) != 0>>
	[[nodiscard]] constexpr inline EmuMath::NewVector<sizeof...(Indices_), typename EmuMath::NewVector<Size_, T_>::value_type_uq> new_vector_shuffle
	(
		EmuMath::NewVector<Size_, T_>& vector_
	)
	{
		return _vector_underlying::_vector_shuffle<typename EmuMath::NewVector<Size_, T_>::value_type_uq, false, Indices_...>(vector_);
	}

	template<typename OutT_, std::size_t...Indices_, std::size_t Size_, typename T_, typename = std::enable_if_t<sizeof...(Indices_) != 0>>
	[[nodiscard]] constexpr inline EmuMath::NewVector<sizeof...(Indices_), OutT_> new_vector_shuffle(const EmuMath::NewVector<Size_, T_>& vector_)
	{
		return _vector_underlying::_vector_shuffle<OutT_, false, Indices_...>(vector_);
	}
	template<std::size_t...Indices_, std::size_t Size_, typename T_, typename = std::enable_if_t<sizeof...(Indices_) != 0>>
	[[nodiscard]] constexpr inline EmuMath::NewVector<sizeof...(Indices_), typename EmuMath::NewVector<Size_, T_>::value_type_uq> new_vector_shuffle
	(
		const EmuMath::NewVector<Size_, T_>& vector_
	)
	{
		return _vector_underlying::_vector_shuffle<typename EmuMath::NewVector<Size_, T_>::value_type_uq, false, Indices_...>(vector_);
	}

	/// <summary>
	/// <para> Creates a new EmuMath Vector, with the provided OutT_ used as the output Vector's T_ argument, via specified theoretical indices within the input vector_. </para>
	/// <para> The Size_ of the output Vector will be equal to the provided number of Indices_. </para>
	/// <para> OutT_ is optional, and defaults to the passed vector_'s value_type_uq. </para>
	/// <para> There is no upper limit for the amount of indices to be provided, but at least 1 argument must be provided for Indices_. </para>
	/// <para> This may be used to access theoretical indices; to prohibit use of non-contained indices, use `vector_shuffle` instead. </para>
	/// </summary>
	/// <typeparam name="OutT_">T_ argument for the output Vector. Defaults to the passed vector_'s value_type_uq.</typeparam>
	/// <param name="vector_">EmuMath Vector to retrieve indices from.</param>
	/// <returns>EmuMath Vector with a number of elements equal to the number of Indices_ arguments, constructed from shuffled indices within the passed vector_.</returns>
	template<typename OutT_, std::size_t...Indices_, std::size_t Size_, typename T_, typename = std::enable_if_t<sizeof...(Indices_) != 0>>
	[[nodiscard]] constexpr inline EmuMath::NewVector<sizeof...(Indices_), OutT_> new_vector_shuffle_theoretical(EmuMath::NewVector<Size_, T_>& vector_)
	{
		return _vector_underlying::_vector_shuffle<OutT_, true, Indices_...>(vector_);
	}
	template<std::size_t...Indices_, std::size_t Size_, typename T_, typename = std::enable_if_t<sizeof...(Indices_) != 0>>
	[[nodiscard]] constexpr inline EmuMath::NewVector<sizeof...(Indices_), typename EmuMath::NewVector<Size_, T_>::value_type_uq> new_vector_shuffle_theoretical
	(
		EmuMath::NewVector<Size_, T_>& vector_
	)
	{
		return _vector_underlying::_vector_shuffle<typename EmuMath::NewVector<Size_, T_>::value_type_uq, true, Indices_...>(vector_);
	}

	template<typename OutT_, std::size_t...Indices_, std::size_t Size_, typename T_, typename = std::enable_if_t<sizeof...(Indices_) != 0>>
	[[nodiscard]] constexpr inline EmuMath::NewVector<sizeof...(Indices_), OutT_> new_vector_shuffle_theoretical(const EmuMath::NewVector<Size_, T_>& vector_)
	{
		return _vector_underlying::_vector_shuffle<OutT_, true, Indices_...>(vector_);
	}
	template<std::size_t...Indices_, std::size_t Size_, typename T_, typename = std::enable_if_t<sizeof...(Indices_) != 0>>
	[[nodiscard]] constexpr inline EmuMath::NewVector<sizeof...(Indices_), typename EmuMath::NewVector<Size_, T_>::value_type_uq> new_vector_shuffle_theoretical
	(
		const EmuMath::NewVector<Size_, T_>& vector_
	)
	{
		return _vector_underlying::_vector_shuffle<typename EmuMath::NewVector<Size_, T_>::value_type_uq, true, Indices_...>(vector_);
	}
#pragma endregion

#pragma region MUTATION_TEMPLATE_FUNCS
	/// <summary>
	/// <para> 
	///		Creates an EmuMath Vector using the provided mutation Func_ type,
	///		with the output Vector type using the provided OutSize_ and OutT_ as its Size_ and T_ arguments.
	/// </para>
	/// <para> The provided arguments will be provided to an instance of Func_ for every index within the output Vector. </para>
	/// <para> For any Arg_ that is an EmuMath Vector: The argument at the matching index will be passed to the Func_ instance, instead of the full Vector. </para>
	/// </summary>
	/// <typeparam name="Func_">Mutation function to invoke for every index within the output Vector.</typeparam>
	/// <typeparam name="Args_">All argument types being passed to the mutation function.</typeparam>
	/// <param name="args_">All arguments to pass to the mutation function on every iteration. May provide EmuMath Vectors for unique arguments per iteration. </param>
	/// <returns>EmuMath Vector created from mutating the provided arguments via an instance of the provided Func_ at every index within the output Vector.</returns>
	template<class Func_, std::size_t OutSize_, typename OutT_, class...Args_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> new_vector_mutate(Args_&&...args_)
	{
		return _vector_underlying::_vector_mutate_args_only<Func_, EmuMath::NewVector<OutSize_, OutT_>, 0, EmuMath::NewVector<OutSize_, OutT_>::size, 0>
		(
			std::forward<Args_>(args_)...
		);
	}

	/// <summary>
	/// <para> 
	///		Creates an EmuMath Vector using the provided mutation func_,
	///		with the output Vector type using the provided OutSize_ and OutT_ as its Size_ and T_ arguments.
	/// </para>
	/// <para> The provided arguments will be provided to func_ for every index within the output Vector. </para>
	/// <para> For any Arg_ that is an EmuMath Vector: The argument at the matching index will be passed to the Func_ instance, instead of the full Vector. </para>
	/// </summary>
	/// <typeparam name="Func_">Mutation function to invoke for every index within the output Vector.</typeparam>
	/// <typeparam name="Args_">All argument types being passed to the mutation function.</typeparam>
	/// <param name="func_">Mutation function to execute with all passed arguments (as described) for every index within the output Vector.</param>
	/// <param name="args_">All arguments to pass to the mutation function on every iteration. May provide EmuMath Vectors for unique arguments per iteration. </param>
	/// <returns>EmuMath Vector created from mutating the provided arguments via the provided func_ at every index within the output Vector.</returns>
	template<std::size_t OutSize_, typename OutT_, class Func_, class...Args_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> new_vector_mutate(Func_ func_, Args_&&...args_)
	{
		return _vector_underlying::_vector_mutate_return_out<EmuMath::NewVector<OutSize_, OutT_>, Func_&,  0, EmuMath::NewVector<OutSize_, OutT_>::size, 0>
		(
			func_,
			std::forward<Args_>(args_)...
		);
	}

	/// <summary>
	/// <para> Outputs to an EmuMath Vector using the provided mutation Func_ type. </para>
	/// <para> The provided arguments will be provided to an instance of Func_ for every index within the output Vector. </para>
	/// <para> For any Arg_ that is an EmuMath Vector: The argument at the matching index will be passed to the Func_ instance, instead of the full Vector. </para>
	/// </summary>
	/// <typeparam name="Func_">Mutation function to invoke for every index within the output Vector.</typeparam>
	/// <typeparam name="Args_">All argument types being passed to the mutation function.</typeparam>
	/// <param name="out_vector_">: EmuMath Vector to output the results of mutation to.</param>
	/// <param name="args_">: All arguments to pass to the mutation function on every iteration. May provide EmuMath Vectors for unique arguments per iteration. </param>
	template<class Func_, std::size_t OutSize_, typename OutT_, class...Args_>
	constexpr inline void new_vector_mutate_to(EmuMath::NewVector<OutSize_, OutT_>& out_vector_, Args_&&...args_)
	{
		_vector_underlying::_vector_mutate_no_func_passed<Func_, EmuMath::NewVector<OutSize_, OutT_>, 0, EmuMath::NewVector<OutSize_, OutT_>::size, 0>
		(
			out_vector_,
			std::forward<Args_>(args_)...
		);
	}

	/// <summary>
	/// <para> Outputs to an EmuMath Vector using the provided mutation func_. </para>
	/// <para> The provided arguments will be provided to func_ for every index within the output Vector. </para>
	/// <para> For any Arg_ that is an EmuMath Vector: The argument at the matching index will be passed to the Func_ instance, instead of the full Vector. </para>
	/// </summary>
	/// <typeparam name="Func_">Mutation function to invoke for every index within the output Vector.</typeparam>
	/// <typeparam name="Args_">All argument types being passed to the mutation function.</typeparam>
	/// <param name="out_vector_">: EmuMath Vector to output the results of mutation to.</param>
	/// <param name="func_">Mutation function to execute with all passed arguments (as described) for every index within the output Vector.</param>
	/// <param name="args_">All arguments to pass to the mutation function on every iteration. May provide EmuMath Vectors for unique arguments per iteration. </param>
	template<class Func_, class...Args_, std::size_t OutSize_, typename OutT_>
	constexpr inline void new_vector_mutate_to(Func_ func_, EmuMath::NewVector<OutSize_, OutT_>& out_vector_, Args_&&...args_)
	{
		_vector_underlying::_vector_mutate<Func_&, EmuMath::NewVector<OutSize_, OutT_>, 0, EmuMath::NewVector<OutSize_, OutT_>::size, 0>
		(
			func_,
			out_vector_,
			std::forward<Args_>(args_)...
		);
	}

	/// <summary>
	/// <para>
	///		Outputs to the provided index range within the passed EmuMath Vector using the results of the provided mutation Func_ type,
	///		 when invoked with all of the provided args_.
	/// </para>
	/// <para> For any Arg_ that is an EmuMath Vector: The argument at the current ArgIndex_ will be used. This is increased by 1 for every iteration. </para>
	/// <para> BeginIndex_ is the inclusive first index at which to start writing to out_vector_. This is required. </para>
	/// <para> EndIndex_ is the exclusive final index at which to stop writing to out_vector_. This is required. </para>
	/// <para> ArgBeginIndex_ is the inclusive first index to read EmuMath Vector arguments from. This is optional, and defaults to 0. </para>
	/// </summary>
	/// <typeparam name="Func_">Type of mutation function to invoke. This must be default-constructible.</typeparam>
	/// <typeparam name="Args_">All argument types that will be used to pass arguments to the mutation function on every iteration.</typeparam>
	/// <param name="out_vector_">: Non-const EmuMath Vector reference to output to.</param>
	/// <param name="args_">: All arguments that will be used to pass arguments to the mutation function on every iteration, as described.</param>
	template<class Func_, std::size_t BeginIndex_, std::size_t EndIndex_, std::size_t ArgBeginIndex_ = 0, class...Args_, std::size_t OutSize_, typename OutT_>
	constexpr inline void new_vector_mutate_range(EmuMath::NewVector<OutSize_, OutT_>& out_vector_, Args_&&...args_)
	{
		_vector_underlying::_vector_mutate_no_func_passed<Func_, EmuMath::NewVector<OutSize_, OutT_>, BeginIndex_, EndIndex_, ArgBeginIndex_>
		(
			out_vector_,
			std::forward<Args_>(args_)...
		);
	}

	/// <summary>
	/// <para>
	///		Outputs to the provided index range within the passed EmuMath Vector using the results of the provided mutation func_,
	///		when invoked with all of the provided args_.
	/// </para>
	/// <para> For any Arg_ that is an EmuMath Vector: The argument at the current ArgIndex_ will be used. This is increased by 1 for every iteration. </para>
	/// <para> BeginIndex_ is the inclusive first index at which to start writing to out_vector_. This is required. </para>
	/// <para> EndIndex_ is the exclusive final index at which to stop writing to out_vector_. This is required. </para>
	/// <para> ArgBeginIndex_ is the inclusive first index to read EmuMath Vector arguments from. This is optional, and defaults to 0. </para>
	/// </summary>
	/// <typeparam name="Func_">Type of mutation function being passed.</typeparam>
	/// <typeparam name="Args_">All argument types that will be used to pass arguments to the mutation function on every iteration.</typeparam>
	/// <param name="func_">
	///		: Function invocable with each of the provided arguments (or theoretical index equivalents for EmuMath Vector args_), 
	///		which additionally returns a type that may be copied to a value within out_vector_.
	/// </param>
	/// <param name="out_vector_">: Non-const EmuMath Vector reference to output to.</param>
	/// <param name="args_">: All arguments that will be used to pass arguments to the mutation function on every iteration, as described.</param>
	template<std::size_t BeginIndex_, std::size_t EndIndex_, std::size_t ArgBeginIndex_, class Func_, class...Args_, std::size_t OutSize_, typename OutT_>
	constexpr inline void new_vector_mutate_range(Func_ func_, EmuMath::NewVector<OutSize_, OutT_>& out_vector_, Args_&&...args_)
	{
		_vector_underlying::_vector_mutate<Func_&, EmuMath::NewVector<OutSize_, OutT_>, BeginIndex_, EndIndex_, ArgBeginIndex_>
		(
			func_,
			out_vector_,
			std::forward<Args_>(args_)...
		);
	}
	template<std::size_t BeginIndex_, std::size_t EndIndex_, class Func_, class...Args_, std::size_t OutSize_, typename OutT_>
	constexpr inline void new_vector_mutate_range(Func_ func_, EmuMath::NewVector<OutSize_, OutT_>& out_vector_, Args_&&...args_)
	{
		_vector_underlying::_vector_mutate<Func_&, EmuMath::NewVector<OutSize_, OutT_>, BeginIndex_, EndIndex_, 0>
		(
			func_,
			out_vector_,
			std::forward<Args_>(args_)...
		);
	}

	/// <summary>
	/// <para>
	///		Outputs an EmuMath Vector with the provided OutSize_ and OutT_ template arguments,
	///		using the results of invoking a default instance of Func_ with all provided args_ for all indices in the specified range.
	/// </para>
	/// <para> For any Arg_ that is an EmuMath Vector: The argument at the current ArgIndex_ will be used. This is increased by 1 for every iteration. </para>
	/// <para> BeginIndex_ is the inclusive first index at which to start writing mutation results to the output Vector. This is required. </para>
	/// <para> EndIndex_ is the exclusive final index at which to stop writing mutation results to the output Vector. This is required. </para>
	/// <para> ArgBeginIndex_ is the inclusive first index to read EmuMath Vector arguments from. This is optional, and defaults to 0. </para>
	/// </summary>
	/// <typeparam name="Func_">Type of function to invoke with the provided arguments. Must be default-constructible.</typeparam>
	/// <typeparam name="Args_">All argument types that will be used to pass arguments to the mutation function on every iteration.</typeparam>
	/// <param name="args_">: All arguments that will be used to pass arguments to the mutation function on every iteration, as described.</param>
	/// <returns>A new instance of an EmuMath Vector of the specified OutSize_ and OutT_, with indices in the specified range set to mutation results.</returns>
	template<class Func_, std::size_t OutSize_, typename OutT_, std::size_t BeginIndex_, std::size_t EndIndex_, std::size_t ArgBeginIndex_ = 0, class...Args_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> new_vector_mutate_range(Args_&&...args_)
	{
		return _vector_underlying::_vector_mutate_args_only<Func_, EmuMath::NewVector<OutSize_, OutT_>, BeginIndex_, EndIndex_, ArgBeginIndex_>
		(
			std::forward<Args_>(args_)...
		);
	}

	/// <summary>
	/// <para>
	///		Outputs an EmuMath Vector with the provided OutSize_ and OutT_ template arguments,
	///		using the results of invoking func_ with all provided args_ for all indices in the specified range.
	/// </para>
	/// <para> For any Arg_ that is an EmuMath Vector: The argument at the current ArgIndex_ will be used. This is increased by 1 for every iteration. </para>
	/// <para> BeginIndex_ is the inclusive first index at which to start writing mutation results to the output Vector. This is required. </para>
	/// <para> EndIndex_ is the exclusive final index at which to stop writing mutation results to the output Vector. This is required. </para>
	/// <para> ArgBeginIndex_ is the inclusive first index to read EmuMath Vector arguments from. This is optional, and defaults to 0. </para>
	/// </summary>
	/// <typeparam name="Args_">All argument types that will be used to pass arguments to the mutation function on every iteration.</typeparam>
	/// <param name="args_">: All arguments that will be used to pass arguments to the mutation function on every iteration, as described.</param>
	/// <returns>A new instance of an EmuMath Vector of the specified OutSize_ and OutT_, with indices in the specified range set to mutation results.</returns>
	template<std::size_t OutSize_, typename OutT_, std::size_t BeginIndex_, std::size_t EndIndex_, std::size_t ArgBeginIndex_, class Func_, class...Args_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> new_vector_mutate_range(Func_ func_, Args_&&...args_)
	{
		return _vector_underlying::_vector_mutate_return_out<EmuMath::NewVector<OutSize_, OutT_>, Func_&, BeginIndex_, EndIndex_, ArgBeginIndex_>
		(
			func_,
			std::forward<Args_>(args_)...
		);
	}
	template<std::size_t OutSize_, typename OutT_, std::size_t BeginIndex_, std::size_t EndIndex_, class Func_, class...Args_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> new_vector_mutate_range(Func_ func_, Args_&&...args_)
	{
		return _vector_underlying::_vector_mutate_return_out<EmuMath::NewVector<OutSize_, OutT_>, Func_&, BeginIndex_, EndIndex_, 0>
		(
			func_,
			std::forward<Args_>(args_)...
		);
	}
#pragma endregion
}

#endif
