#ifndef EMU_MATH_NEW_VECTOR_MUTATION_H_INC_
#define EMU_MATH_NEW_VECTOR_MUTATION_H_INC_ 1

#include "_common_vector_helpers.h"

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
	[[nodiscard]] constexpr inline void new_vector_mutate_to(EmuMath::NewVector<OutSize_, OutT_>& out_vector_, Args_&&...args_)
	{
		return _vector_underlying::_vector_mutate_no_func_passed<Func_, EmuMath::NewVector<OutSize_, OutT_>, 0, EmuMath::NewVector<OutSize_, OutT_>::size, 0>
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
	template<std::size_t OutSize_, typename OutT_, class Func_, class...Args_>
	[[nodiscard]] constexpr inline void new_vector_mutate_to(EmuMath::NewVector<OutSize_, OutT_>& out_vector_, Func_ func_, Args_&&...args_)
	{
		return _vector_underlying::_vector_mutate<Func_&, EmuMath::NewVector<OutSize_, OutT_>, 0, EmuMath::NewVector<OutSize_, OutT_>::size, 0>
		(
			func_,
			out_vector_,
			std::forward<Args_>(args_)...
		);
	}
#pragma endregion
}

#endif
