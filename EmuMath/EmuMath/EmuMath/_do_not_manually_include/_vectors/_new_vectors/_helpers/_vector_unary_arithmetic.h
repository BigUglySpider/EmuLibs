#ifndef EMU_MATH_NEW_VECTOR_UNARY_ARITHMETIC_H_INC_
#define EMU_MATH_NEW_VECTOR_UNARY_ARITHMETIC_H_INC_ 1

#include "_common_vector_helpers.h"
#include "../../../../../EmuCore/Functors/Arithmetic.h"

// CONTAINS:
// --- pre_increment
// --- post_increment
// --- pre_decrement
// --- post_decrement
// --- negate

namespace EmuMath::Helpers
{
#pragma region PRE_INCREMENT_FUNCS
	// --- NOTE: No output arg funcs behave differently for pre-increments as we can more efficiently return just a reference to the passed vector_

	/// <summary>
	/// <para> Performs a pre-increment operation on the passed EmuMath Vector, equivalent to `++vector_`. </para>
	/// <para> If no output arguments are provided, the returned Vector will be a direct reference to the passed vector_. </para>
	/// <para>
	///		If an OutSize_ or OutT_ argument is provided, this will instead return a copy of this Vector after incrementing, 
	///		with the output Vector type formed from the provided OutSize_ (vector_'s size if not provided) and OutT_ (vector_'s value_type_uq if not provided).
	/// </para>
	/// </summary>
	/// <param name="vector_">EmuMath vector to perform the increment operation on.</param>
	/// <returns>Reference to vector_ if no OutSize_ or OutT_ argument is provided; otherwise, a copy of vector_ after incrementing.</returns>
	template<std::size_t BeginIndex_, std::size_t EndIndex_, typename T_, std::size_t Size_>
	constexpr inline EmuMath::NewVector<Size_, T_>& new_vector_pre_increment(EmuMath::NewVector<Size_, T_>& vector_)
	{
		using Func_ = EmuCore::do_pre_increment<typename EmuMath::NewVector<Size_, T_>::value_type>;
		_vector_underlying::_vector_mutate_invoke_only_no_func_passed<Func_, BeginIndex_, EndIndex_>(vector_);
		return vector_;
	}
	template<typename T_, std::size_t Size_>
	constexpr inline EmuMath::NewVector<Size_, T_>& new_vector_pre_increment(EmuMath::NewVector<Size_, T_>& vector_)
	{
		using Func_ = EmuCore::do_pre_increment<typename EmuMath::NewVector<Size_, T_>::value_type>;
		_vector_underlying::_vector_mutate_invoke_only_no_func_passed<Func_, 0, Size_>(vector_);
		return vector_;
	}

	/// <summary>
	/// <para> Performs a pre-increment operation on the passed EmuMath Vector, equivalent to `++vector_`. </para>
	/// <para> If no output arguments are provided, the returned Vector will be a direct reference to the passed vector_. </para>
	/// <para>
	///		If an OutSize_ or OutT_ argument is provided, this will instead return a copy of this Vector after incrementing, 
	///		with the output Vector type formed from the provided OutSize_ (vector_'s size if not provided) and OutT_ (vector_'s value_type_uq if not provided).
	/// </para>
	/// </summary>
	/// <param name="vector_">EmuMath vector to perform the increment operation on.</param>
	/// <returns>Reference to vector_ if no OutSize_ or OutT_ argument is provided; otherwise, a copy of vector_ after incrementing.</returns>
	template<std::size_t OutSize_, typename OutT_, std::size_t BeginIndex_, std::size_t EndIndex_, typename T_, std::size_t Size_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> new_vector_pre_increment(EmuMath::NewVector<Size_, T_>& vector_)
	{
		using Func_ = EmuCore::do_pre_increment<typename EmuMath::NewVector<Size_, T_>::value_type>;
		return _vector_underlying::_vector_copy_mutate_invoke_only_no_func_passed<false, Func_, OutSize_, OutT_, BeginIndex_, EndIndex_>(vector_, vector_);
	}
	template<typename OutT_, std::size_t BeginIndex_, std::size_t EndIndex_, typename T_, std::size_t Size_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<Size_, OutT_> new_vector_pre_increment(EmuMath::NewVector<Size_, T_>& vector_)
	{
		using Func_ = EmuCore::do_pre_increment<typename EmuMath::NewVector<Size_, T_>::value_type>;
		return _vector_underlying::_vector_copy_mutate_invoke_only_no_func_passed<false, Func_, Size_, OutT_, BeginIndex_, EndIndex_>(vector_, vector_);
	}
	template<std::size_t OutSize_, std::size_t BeginIndex_, std::size_t EndIndex_, std::size_t Size_, typename T_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, typename EmuMath::NewVector<Size_, T_>::value_type_uq>
	new_vector_pre_increment(EmuMath::NewVector<Size_, T_>& vector_)
	{
		using Func_ = EmuCore::do_pre_increment<typename EmuMath::NewVector<Size_, T_>::value_type>;
		using value_type_uq = typename EmuMath::NewVector<Size_, T_>::value_type_uq;
		return _vector_underlying::_vector_copy_mutate_invoke_only_no_func_passed<false, Func_, OutSize_, value_type_uq, BeginIndex_, EndIndex_>(vector_, vector_);
	}

	/// <summary>
	/// <para> Performs a pre-increment operation on the passed EmuMath Vector, equivalent to `++vector_`. </para>
	/// <para> If no output arguments are provided, the returned Vector will be a direct reference to the passed vector_. </para>
	/// <para>
	///		If an OutSize_ or OutT_ argument is provided, this will instead return a copy of this Vector after incrementing, 
	///		with the output Vector type formed from the provided OutSize_ (vector_'s size if not provided) and OutT_ (vector_'s value_type_uq if not provided).
	/// </para>
	/// <para> BeginIndex_ is the inclusive index at which to start incrementing elements. </para>
	/// <para> EndIndex_ is the exclusive index at which to stop incrementing elements. </para>
	/// </summary>
	/// <param name="vector_">EmuMath vector to perform the increment operation on.</param>
	/// <returns>Reference to vector_ if no OutSize_ or OutT_ argument is provided; otherwise, a copy of vector_ after incrementing.</returns>
	template<std::size_t OutSize_, typename OutT_, typename T_, std::size_t Size_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> new_vector_pre_increment(EmuMath::NewVector<Size_, T_>& vector_)
	{
		using Func_ = EmuCore::do_pre_increment<typename EmuMath::NewVector<Size_, T_>::value_type>;
		return _vector_underlying::_vector_copy_mutate_invoke_only_no_func_passed<false, Func_, OutSize_, OutT_, 0, Size_>(vector_, vector_);
	}
	template<typename OutT_, typename T_, std::size_t Size_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<Size_, OutT_> new_vector_pre_increment(EmuMath::NewVector<Size_, T_>& vector_)
	{
		using Func_ = EmuCore::do_pre_increment<typename EmuMath::NewVector<Size_, T_>::value_type>;
		return _vector_underlying::_vector_copy_mutate_invoke_only_no_func_passed<false, Func_, Size_, OutT_, 0, Size_>(vector_, vector_);
	}
	template<std::size_t OutSize_, std::size_t Size_, typename T_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, typename EmuMath::NewVector<Size_, T_>::value_type_uq>
	new_vector_pre_increment(EmuMath::NewVector<Size_, T_>& vector_)
	{
		using Func_ = EmuCore::do_pre_increment<typename EmuMath::NewVector<Size_, T_>::value_type>;
		using value_type_uq = typename EmuMath::NewVector<Size_, T_>::value_type_uq;
		return _vector_underlying::_vector_copy_mutate_invoke_only_no_func_passed<false, Func_, OutSize_, value_type_uq, 0, Size_>(vector_, vector_);
	}
#pragma endregion

#pragma region POST_INCREMENT_FUNCS
	/// <summary>
	/// <para> Performs a post-increment operation on the passed EmuMath Vector, equivalent to `vector_++`. </para>
	/// <para> The returned Vector will be a full copy of vector_ before the increment occurs. </para>
	/// <para> BeginIndex_ is the inclusive index at which to start incrementing elements. </para>
	/// <para> EndIndex_ is the exclusive index at which to stop incrementing elements. </para>
	/// </summary>
	/// <param name="vector_">EmuMath vector to perform the increment operation on.</param>
	/// <returns>EmuMath Vector of the specified OutSize_ (defaults to vector_'s size) and OutT_ (defaults to vector_'s value_type_uq), copying vector_ before incrementing.</returns>
	template<std::size_t OutSize_, typename OutT_, std::size_t BeginIndex_, std::size_t EndIndex_, typename T_, std::size_t Size_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> new_vector_post_increment(EmuMath::NewVector<Size_, T_>& vector_)
	{
		using Func_ = EmuCore::do_post_increment<typename EmuMath::NewVector<Size_, T_>::value_type>;
		return _vector_underlying::_vector_copy_mutate_invoke_only_no_func_passed<true, Func_, OutSize_, OutT_, BeginIndex_, EndIndex_>(vector_, vector_);
	}

	template<typename OutT_, std::size_t BeginIndex_, std::size_t EndIndex_, typename T_, std::size_t Size_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<Size_, T_> new_vector_post_increment(EmuMath::NewVector<Size_, T_>& vector_)
	{
		using Func_ = EmuCore::do_post_increment<typename EmuMath::NewVector<Size_, T_>::value_type>;
		return _vector_underlying::_vector_copy_mutate_invoke_only_no_func_passed<true, Func_, Size_, OutT_, BeginIndex_, EndIndex_>(vector_, vector_);
	}

	template<std::size_t OutSize_, std::size_t BeginIndex_, std::size_t EndIndex_, typename T_, std::size_t Size_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, typename EmuMath::NewVector<Size_, T_>::value_type_uq>
	new_vector_post_increment(EmuMath::NewVector<Size_, T_>& vector_)
	{
		using Func_ = EmuCore::do_post_increment<typename EmuMath::NewVector<Size_, T_>::value_type>;
		using value_type_uq = typename EmuMath::NewVector<Size_, T_>::value_type_uq;
		return _vector_underlying::_vector_copy_mutate_invoke_only_no_func_passed<true, Func_, OutSize_, value_type_uq, BeginIndex_, EndIndex_>(vector_, vector_);
	}

	template<std::size_t BeginIndex_, std::size_t EndIndex_, typename T_, std::size_t Size_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<Size_, typename EmuMath::NewVector<Size_, T_>::value_type_uq>
	new_vector_post_increment(EmuMath::NewVector<Size_, T_>& vector_)
	{
		using Func_ = EmuCore::do_post_increment<typename EmuMath::NewVector<Size_, T_>::value_type>;
		using value_type_uq = typename EmuMath::NewVector<Size_, T_>::value_type_uq;
		return _vector_underlying::_vector_copy_mutate_invoke_only_no_func_passed<true, Func_, Size_, value_type_uq, BeginIndex_, EndIndex_>(vector_, vector_);
	}

	/// <summary>
	/// <para> Performs a post-increment operation on the passed EmuMath Vector, equivalent to `vector_++`. </para>
	/// <para> The returned Vector will be a full copy of vector_ before the increment occurs. </para>
	/// </summary>
	/// <param name="vector_">EmuMath vector to perform the increment operation on.</param>
	/// <returns>EmuMath Vector of the specified OutSize_ (defaults to vector_'s size) and OutT_ (defaults to vector_'s value_type_uq), copying vector_ before incrementing.</returns>
	template<std::size_t OutSize_, typename OutT_, typename T_, std::size_t Size_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> new_vector_post_increment(EmuMath::NewVector<Size_, T_>& vector_)
	{
		using Func_ = EmuCore::do_post_increment<typename EmuMath::NewVector<Size_, T_>::value_type>;
		return _vector_underlying::_vector_copy_mutate_invoke_only_no_func_passed<true, Func_, OutSize_, OutT_, 0, Size_>(vector_, vector_);
	}
	template<typename OutT_, typename T_, std::size_t Size_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<Size_, OutT_> new_vector_post_increment(EmuMath::NewVector<Size_, T_>& vector_)
	{
		using Func_ = EmuCore::do_post_increment<typename EmuMath::NewVector<Size_, T_>::value_type>;
		return _vector_underlying::_vector_copy_mutate_invoke_only_no_func_passed<true, Func_, Size_, OutT_, 0, Size_>(vector_, vector_);
	}
	template<std::size_t OutSize_, std::size_t Size_, typename T_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, typename EmuMath::NewVector<Size_, T_>::value_type_uq>
	new_vector_post_increment(EmuMath::NewVector<Size_, T_>& vector_)
	{
		using Func_ = EmuCore::do_post_increment<typename EmuMath::NewVector<Size_, T_>::value_type>;
		using value_type_uq = typename EmuMath::NewVector<Size_, T_>::value_type_uq;
		return _vector_underlying::_vector_copy_mutate_invoke_only_no_func_passed<true, Func_, OutSize_, value_type_uq, 0, Size_>(vector_, vector_);
	}
	template<typename T_, std::size_t Size_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<Size_, typename EmuMath::NewVector<Size_, T_>::value_type_uq>
	new_vector_post_increment(EmuMath::NewVector<Size_, T_>& vector_)
	{
		using Func_ = EmuCore::do_post_increment<typename EmuMath::NewVector<Size_, T_>::value_type>;
		using value_type_uq = typename EmuMath::NewVector<Size_, T_>::value_type_uq;
		return _vector_underlying::_vector_copy_mutate_invoke_only_no_func_passed<true, Func_, Size_, value_type_uq, 0, Size_>(vector_, vector_);
	}

	/// <summary>
	/// <para> Performs a post-increment operation on the passed EmuMath Vector, equivalent to `vector_++`. </para>
	/// <para> This is purely for invoking a post-increment (or emulating such if possible), and will not create and return a copy. </para>
	/// </summary>
	/// <param name="vector_">EmuMath vector to perform the increment operation on.</param>
	/// <returns>Reference to the provided vector_.</returns>
	template<std::size_t BeginIndex_, std::size_t EndIndex_, typename T_, std::size_t Size_>
	constexpr inline EmuMath::NewVector<Size_, T_>& new_vector_post_increment_no_copy(EmuMath::NewVector<Size_, T_>& vector_)
	{
		using Func_ = EmuCore::do_post_increment<typename EmuMath::NewVector<Size_, T_>::value_type>;
		_vector_underlying::_vector_mutate_invoke_only_no_func_passed<Func_, BeginIndex_, EndIndex_>(vector_);
		return vector_;
	}
	template<typename T_, std::size_t Size_>
	constexpr inline EmuMath::NewVector<Size_, T_>& new_vector_post_increment_no_copy(EmuMath::NewVector<Size_, T_>& vector_)
	{
		using Func_ = EmuCore::do_post_increment<typename EmuMath::NewVector<Size_, T_>::value_type>;
		_vector_underlying::_vector_mutate_invoke_only_no_func_passed<Func_, 0, Size_>(vector_);
		return vector_;
	}
#pragma endregion

#pragma region PRE_DECREMENT_FUNCS
	// --- NOTE: No output arg funcs behave differently for pre-decrements as we can more efficiently return just a reference to the passed vector_

	/// <summary>
	/// <para> Performs a pre-decrement operation on the passed EmuMath Vector, equivalent to `--vector_`. </para>
	/// <para> If no output arguments are provided, the returned Vector will be a direct reference to the passed vector_. </para>
	/// <para>
	///		If an OutSize_ or OutT_ argument is provided, this will instead return a copy of this Vector after decrementing, 
	///		with the output Vector type formed from the provided OutSize_ (vector_'s size if not provided) and OutT_ (vector_'s value_type_uq if not provided).
	/// </para>
	/// </summary>
	/// <param name="vector_">EmuMath vector to perform the decrement operation on.</param>
	/// <returns>Reference to vector_ if no OutSize_ or OutT_ argument is provided; otherwise, a copy of vector_ after dcrementing.</returns>
	template<std::size_t BeginIndex_, std::size_t EndIndex_, typename T_, std::size_t Size_>
	constexpr inline EmuMath::NewVector<Size_, T_>& new_vector_pre_decrement(EmuMath::NewVector<Size_, T_>& vector_)
	{
		using Func_ = EmuCore::do_pre_decrement<typename EmuMath::NewVector<Size_, T_>::value_type>;
		_vector_underlying::_vector_mutate_invoke_only_no_func_passed<Func_, BeginIndex_, EndIndex_>(vector_);
		return vector_;
	}
	template<typename T_, std::size_t Size_>
	constexpr inline EmuMath::NewVector<Size_, T_>& new_vector_pre_decrement(EmuMath::NewVector<Size_, T_>& vector_)
	{
		using Func_ = EmuCore::do_pre_decrement<typename EmuMath::NewVector<Size_, T_>::value_type>;
		_vector_underlying::_vector_mutate_invoke_only_no_func_passed<Func_, 0, Size_>(vector_);
		return vector_;
	}

	/// <summary>
	/// <para> Performs a pre-decrement operation on the passed EmuMath Vector, equivalent to `--vector_`. </para>
	/// <para> If no output arguments are provided, the returned Vector will be a direct reference to the passed vector_. </para>
	/// <para>
	///		If an OutSize_ or OutT_ argument is provided, this will instead return a copy of this Vector after decrementing, 
	///		with the output Vector type formed from the provided OutSize_ (vector_'s size if not provided) and OutT_ (vector_'s value_type_uq if not provided).
	/// </para>
	/// </summary>
	/// <param name="vector_">EmuMath vector to perform the decrement operation on.</param>
	/// <returns>Reference to vector_ if no OutSize_ or OutT_ argument is provided; otherwise, a copy of vector_ after decrementing.</returns>
	template<std::size_t OutSize_, typename OutT_, std::size_t BeginIndex_, std::size_t EndIndex_, typename T_, std::size_t Size_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> new_vector_pre_decrement(EmuMath::NewVector<Size_, T_>& vector_)
	{
		using Func_ = EmuCore::do_pre_decrement<typename EmuMath::NewVector<Size_, T_>::value_type>;
		return _vector_underlying::_vector_copy_mutate_invoke_only_no_func_passed<false, Func_, OutSize_, OutT_, BeginIndex_, EndIndex_>(vector_, vector_);
	}
	template<typename OutT_, std::size_t BeginIndex_, std::size_t EndIndex_, typename T_, std::size_t Size_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<Size_, OutT_> new_vector_pre_decrement(EmuMath::NewVector<Size_, T_>& vector_)
	{
		using Func_ = EmuCore::do_pre_decrement<typename EmuMath::NewVector<Size_, T_>::value_type>;
		return _vector_underlying::_vector_copy_mutate_invoke_only_no_func_passed<false, Func_, Size_, OutT_, BeginIndex_, EndIndex_>(vector_, vector_);
	}
	template<std::size_t OutSize_, std::size_t BeginIndex_, std::size_t EndIndex_, std::size_t Size_, typename T_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, typename EmuMath::NewVector<Size_, T_>::value_type_uq>
	new_vector_pre_decrement(EmuMath::NewVector<Size_, T_>& vector_)
	{
		using Func_ = EmuCore::do_pre_decrement<typename EmuMath::NewVector<Size_, T_>::value_type>;
		using value_type_uq = typename EmuMath::NewVector<Size_, T_>::value_type_uq;
		return _vector_underlying::_vector_copy_mutate_invoke_only_no_func_passed<false, Func_, OutSize_, value_type_uq, BeginIndex_, EndIndex_>(vector_, vector_);
	}

	/// <summary>
	/// <para> Performs a pre-decrement operation on the passed EmuMath Vector, equivalent to `--vector_`. </para>
	/// <para> If no output arguments are provided, the returned Vector will be a direct reference to the passed vector_. </para>
	/// <para>
	///		If an OutSize_ or OutT_ argument is provided, this will instead return a copy of this Vector after decrementing, 
	///		with the output Vector type formed from the provided OutSize_ (vector_'s size if not provided) and OutT_ (vector_'s value_type_uq if not provided).
	/// </para>
	/// <para> BeginIndex_ is the inclusive index at which to start incrementing elements. </para>
	/// <para> EndIndex_ is the exclusive index at which to stop incrementing elements. </para>
	/// </summary>
	/// <param name="vector_">EmuMath vector to perform the decrement operation on.</param>
	/// <returns>Reference to vector_ if no OutSize_ or OutT_ argument is provided; otherwise, a copy of vector_ after decrementing.</returns>
	template<std::size_t OutSize_, typename OutT_, typename T_, std::size_t Size_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> new_vector_pre_decrement(EmuMath::NewVector<Size_, T_>& vector_)
	{
		using Func_ = EmuCore::do_pre_decrement<typename EmuMath::NewVector<Size_, T_>::value_type>;
		return _vector_underlying::_vector_copy_mutate_invoke_only_no_func_passed<false, Func_, OutSize_, OutT_, 0, Size_>(vector_, vector_);
	}
	template<typename OutT_, typename T_, std::size_t Size_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<Size_, OutT_> new_vector_pre_decrement(EmuMath::NewVector<Size_, T_>& vector_)
	{
		using Func_ = EmuCore::do_pre_decrement<typename EmuMath::NewVector<Size_, T_>::value_type>;
		return _vector_underlying::_vector_copy_mutate_invoke_only_no_func_passed<false, Func_, Size_, OutT_, 0, Size_>(vector_, vector_);
	}
	template<std::size_t OutSize_, std::size_t Size_, typename T_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, typename EmuMath::NewVector<Size_, T_>::value_type_uq>
	new_vector_pre_decrement(EmuMath::NewVector<Size_, T_>& vector_)
	{
		using Func_ = EmuCore::do_pre_decrement<typename EmuMath::NewVector<Size_, T_>::value_type>;
		using value_type_uq = typename EmuMath::NewVector<Size_, T_>::value_type_uq;
		return _vector_underlying::_vector_copy_mutate_invoke_only_no_func_passed<false, Func_, OutSize_, value_type_uq, 0, Size_>(vector_, vector_);
	}
#pragma endregion

#pragma region POST_DECREMENT_FUNCS
	/// <summary>
	/// <para> Performs a post-decrement operation on the passed EmuMath Vector, equivalent to `vector_--`. </para>
	/// <para> The returned Vector will be a full copy of vector_ before the decrement occurs. </para>
	/// <para> BeginIndex_ is the inclusive index at which to start decrementing elements. </para>
	/// <para> EndIndex_ is the exclusive index at which to stop decrementing elements. </para>
	/// </summary>
	/// <param name="vector_">EmuMath vector to perform the decrement operation on.</param>
	/// <returns>EmuMath Vector of the specified OutSize_ (defaults to vector_'s size) and OutT_ (defaults to vector_'s value_type_uq), copying vector_ before decrementing.</returns>
	template<std::size_t OutSize_, typename OutT_, std::size_t BeginIndex_, std::size_t EndIndex_, typename T_, std::size_t Size_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> new_vector_post_decrement(EmuMath::NewVector<Size_, T_>& vector_)
	{
		using Func_ = EmuCore::do_post_decrement<typename EmuMath::NewVector<Size_, T_>::value_type>;
		return _vector_underlying::_vector_copy_mutate_invoke_only_no_func_passed<true, Func_, OutSize_, OutT_, BeginIndex_, EndIndex_>(vector_, vector_);
	}

	template<typename OutT_, std::size_t BeginIndex_, std::size_t EndIndex_, typename T_, std::size_t Size_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<Size_, T_> new_vector_post_decrement(EmuMath::NewVector<Size_, T_>& vector_)
	{
		using Func_ = EmuCore::do_post_decrement<typename EmuMath::NewVector<Size_, T_>::value_type>;
		return _vector_underlying::_vector_copy_mutate_invoke_only_no_func_passed<true, Func_, Size_, OutT_, BeginIndex_, EndIndex_>(vector_, vector_);
	}

	template<std::size_t OutSize_, std::size_t BeginIndex_, std::size_t EndIndex_, typename T_, std::size_t Size_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, typename EmuMath::NewVector<Size_, T_>::value_type_uq>
	new_vector_post_decrement(EmuMath::NewVector<Size_, T_>& vector_)
	{
		using Func_ = EmuCore::do_post_decrement<typename EmuMath::NewVector<Size_, T_>::value_type>;
		using value_type_uq = typename EmuMath::NewVector<Size_, T_>::value_type_uq;
		return _vector_underlying::_vector_copy_mutate_invoke_only_no_func_passed<true, Func_, OutSize_, value_type_uq, BeginIndex_, EndIndex_>(vector_, vector_);
	}

	template<std::size_t BeginIndex_, std::size_t EndIndex_, typename T_, std::size_t Size_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<Size_, typename EmuMath::NewVector<Size_, T_>::value_type_uq>
	new_vector_post_decrement(EmuMath::NewVector<Size_, T_>& vector_)
	{
		using Func_ = EmuCore::do_post_decrement<typename EmuMath::NewVector<Size_, T_>::value_type>;
		using value_type_uq = typename EmuMath::NewVector<Size_, T_>::value_type_uq;
		return _vector_underlying::_vector_copy_mutate_invoke_only_no_func_passed<true, Func_, Size_, value_type_uq, BeginIndex_, EndIndex_>(vector_, vector_);
	}

	/// <summary>
	/// <para> Performs a post-decrement operation on the passed EmuMath Vector, equivalent to `vector_--`. </para>
	/// <para> The returned Vector will be a full copy of vector_ before the decrement occurs. </para>
	/// </summary>
	/// <param name="vector_">EmuMath vector to perform the decrement operation on.</param>
	/// <returns>EmuMath Vector of the specified OutSize_ (defaults to vector_'s size) and OutT_ (defaults to vector_'s value_type_uq), copying vector_ before decrementing.</returns>
	template<std::size_t OutSize_, typename OutT_, typename T_, std::size_t Size_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> new_vector_post_decrement(EmuMath::NewVector<Size_, T_>& vector_)
	{
		using Func_ = EmuCore::do_post_decrement<typename EmuMath::NewVector<Size_, T_>::value_type>;
		return _vector_underlying::_vector_copy_mutate_invoke_only_no_func_passed<true, Func_, OutSize_, OutT_, 0, Size_>(vector_, vector_);
	}
	template<typename OutT_, typename T_, std::size_t Size_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<Size_, OutT_> new_vector_post_decrement(EmuMath::NewVector<Size_, T_>& vector_)
	{
		using Func_ = EmuCore::do_post_decrement<typename EmuMath::NewVector<Size_, T_>::value_type>;
		return _vector_underlying::_vector_copy_mutate_invoke_only_no_func_passed<true, Func_, Size_, OutT_, 0, Size_>(vector_, vector_);
	}
	template<std::size_t OutSize_, std::size_t Size_, typename T_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, typename EmuMath::NewVector<Size_, T_>::value_type_uq>
	new_vector_post_decrement(EmuMath::NewVector<Size_, T_>& vector_)
	{
		using Func_ = EmuCore::do_post_decrement<typename EmuMath::NewVector<Size_, T_>::value_type>;
		using value_type_uq = typename EmuMath::NewVector<Size_, T_>::value_type_uq;
		return _vector_underlying::_vector_copy_mutate_invoke_only_no_func_passed<true, Func_, OutSize_, value_type_uq, 0, Size_>(vector_, vector_);
	}
	template<typename T_, std::size_t Size_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<Size_, typename EmuMath::NewVector<Size_, T_>::value_type_uq>
	new_vector_post_decrement(EmuMath::NewVector<Size_, T_>& vector_)
	{
		using Func_ = EmuCore::do_post_decrement<typename EmuMath::NewVector<Size_, T_>::value_type>;
		using value_type_uq = typename EmuMath::NewVector<Size_, T_>::value_type_uq;
		return _vector_underlying::_vector_copy_mutate_invoke_only_no_func_passed<true, Func_, Size_, value_type_uq, 0, Size_>(vector_, vector_);
	}

	/// <summary>
	/// <para> Performs a post-decrement operation on the passed EmuMath Vector, equivalent to `vector_--`. </para>
	/// <para> This is purely for invoking a post-decrement (or emulating such if possible), and will not create and return a copy. </para>
	/// </summary>
	/// <param name="vector_">EmuMath vector to perform the decrement operation on.</param>
	/// <returns>Reference to the provided vector_.</returns>
	template<std::size_t BeginIndex_, std::size_t EndIndex_, typename T_, std::size_t Size_>
	constexpr inline EmuMath::NewVector<Size_, T_>& new_vector_post_decrement_no_copy(EmuMath::NewVector<Size_, T_>& vector_)
	{
		using Func_ = EmuCore::do_post_decrement<typename EmuMath::NewVector<Size_, T_>::value_type>;
		_vector_underlying::_vector_mutate_invoke_only_no_func_passed<Func_, BeginIndex_, EndIndex_>(vector_);
		return vector_;
	}
	template<typename T_, std::size_t Size_>
	constexpr inline EmuMath::NewVector<Size_, T_>& new_vector_post_decrement_no_copy(EmuMath::NewVector<Size_, T_>& vector_)
	{
		using Func_ = EmuCore::do_post_decrement<typename EmuMath::NewVector<Size_, T_>::value_type>;
		_vector_underlying::_vector_mutate_invoke_only_no_func_passed<Func_, 0, Size_>(vector_);
		return vector_;
	}
#pragma endregion

#pragma region NEGATION_FUNCS
	/// <summary>
	/// <para> Outputs a negated form of the provided EmuMath Vector, with the output Vector using the provided OutSize_ and OutT_ template arguments. </para>
	/// <para> OutSize_: Optional argument used as the Size_ argument for the output EmuMath Vector type. Defaults to the input Vector's Size_. </para>
	/// <para> OutT_: Optional argument used as the T_ argument for the output EmuMath Vector type. Defaults to the input Vector's T_. </para>
	/// </summary>
	/// <param name="in_vector_">EmuMath Vector to output the negated form of.</param>
	/// <returns>Negated form of in_vector_ (i.e. -in_vector_) as an EmuMath Vector type formed from the provided OutSize_ and OutT_ arguments.</returns>
	template<std::size_t OutSize_, typename OutT_, std::size_t InSize_, typename InT_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> new_vector_negate(const EmuMath::NewVector<InSize_, InT_>& in_vector_)
	{
		using Func_ = EmuCore::do_negate<typename EmuMath::NewVector<InSize_, InT_>::value_type_uq>;
		return EMU_MATH_VECTOR_MUTATION(Func_, OutSize_, OutT_, InSize_, InT_)(in_vector_);
	}
	template<typename OutT_, std::size_t InSize_, typename InT_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<InSize_, OutT_> new_vector_negate(const EmuMath::NewVector<InSize_, InT_>& in_vector_)
	{
		using Func_ = EmuCore::do_negate<typename EmuMath::NewVector<InSize_, InT_>::value_type_uq>;
		return EMU_MATH_VECTOR_MUTATION(Func_, InSize_, OutT_, InSize_, InT_)(in_vector_);
	}
	template<std::size_t OutSize_, std::size_t InSize_, typename InT_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, typename EmuMath::NewVector<InSize_, InT_>::value_type_uq>
	new_vector_negate(const EmuMath::NewVector<InSize_, InT_>& in_vector_)
	{
		using in_value_uq = typename EmuMath::NewVector<InSize_, InT_>::value_type_uq;
		using Func_ = EmuCore::do_negate<in_value_uq>;
		return EMU_MATH_VECTOR_MUTATION(Func_, OutSize_, in_value_uq, InSize_, InT_)(in_vector_);
	}
	template<typename InT_, std::size_t InSize_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<InSize_, typename EmuMath::NewVector<InSize_, InT_>::value_type_uq>
	new_vector_negate(const EmuMath::NewVector<InSize_, InT_>& in_vector_)
	{
		using in_value_uq = typename EmuMath::NewVector<InSize_, InT_>::value_type_uq;
		using Func_ = EmuCore::do_negate<in_value_uq>;
		return EMU_MATH_VECTOR_MUTATION(Func_, InSize_, in_value_uq, InSize_, InT_)(in_vector_);
	}

	/// <summary>
	/// <para> Outputs a negated form of the provided in_vector_ to the provided out_vector_. </para>
	/// </summary>
	/// <param name="out_vector_">EmuMath Vector to output to.</param>
	/// <param name="in_vector_">EmuMath Vector to output the negated form of.</param>
	template<std::size_t OutSize_, typename OutT_, std::size_t InSize_, typename InT_>
	constexpr inline void new_vector_negate(EmuMath::NewVector<OutSize_, OutT_>& out_vector_, const EmuMath::NewVector<InSize_, InT_>& in_vector_)
	{
		using Func_ = EmuCore::do_negate<typename EmuMath::NewVector<InSize_, InT_>::value_type_uq>;
		return EMU_MATH_VECTOR_MUTATION_REF(Func_, OutSize_, OutT_, InSize_, InT_)(out_vector_, in_vector_);
	}

	/// <summary>
	/// <para> Outputs a copy of the provided in_vector_, with values within the provided index range negated. </para>
	/// <para> BeginIndex_ is the inclusive index at which to start writing negated values to the output Vector. </para>
	/// <para> EndIndex_ is the exclusive index at which to stop writing negated values to the output Vector. </para>
	/// </summary>
	/// <param name="in_vector_">EmuMath Vector to copy, with negated values within the specified index range.</param>
	/// <returns>EmuMath Vector copy of the provided in_vector_, formed with the provided OutSize_ and OutT_ args, with indices in the specified range negated. </returns>
	template<std::size_t OutSize_, typename OutT_, std::size_t BeginIndex_, std::size_t EndIndex_, std::size_t InSize_, typename InT_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> new_vector_negate_range(const EmuMath::NewVector<InSize_, InT_>& in_vector_)
	{
		using Func_ = EmuCore::do_negate<typename EmuMath::NewVector<InSize_, InT_>::value_type_uq>;
		return EMU_MATH_VECTOR_MUTATION_RANGE(Func_, OutSize_, OutT_, InSize_, InT_, BeginIndex_, EndIndex_)(in_vector_, in_vector_);
	}
	template<typename OutT_, std::size_t BeginIndex_, std::size_t EndIndex_, typename InT_, std::size_t InSize_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<InSize_, OutT_> new_vector_negate_range(const EmuMath::NewVector<InSize_, InT_>& in_vector_)
	{
		using Func_ = EmuCore::do_negate<typename EmuMath::NewVector<InSize_, InT_>::value_type_uq>;
		return EMU_MATH_VECTOR_MUTATION_RANGE(Func_, InSize_, OutT_, InSize_, InT_, BeginIndex_, EndIndex_)(in_vector_, in_vector_);
	}
	template<std::size_t OutSize_, std::size_t BeginIndex_, std::size_t EndIndex_, typename InT_, std::size_t InSize_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, typename EmuMath::NewVector<InSize_, InT_>::value_type_uq>
	new_vector_negate_range(const EmuMath::NewVector<InSize_, InT_>& in_vector_)
	{
		using in_value_uq = typename EmuMath::NewVector<InSize_, InT_>::value_type_uq;
		using Func_ = EmuCore::do_negate<in_value_uq>;
		return EMU_MATH_VECTOR_MUTATION_RANGE(Func_, OutSize_, in_value_uq, InSize_, InT_, BeginIndex_, EndIndex_)(in_vector_, in_vector_);
	}
	template<std::size_t BeginIndex_, std::size_t EndIndex_, typename InT_, std::size_t InSize_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<InSize_, typename EmuMath::NewVector<InSize_, InT_>::value_type_uq>
	new_vector_negate_range(const EmuMath::NewVector<InSize_, InT_>& in_vector_)
	{
		using in_value_uq = typename EmuMath::NewVector<InSize_, InT_>::value_type_uq;
		using Func_ = EmuCore::do_negate<in_value_uq>;
		return EMU_MATH_VECTOR_MUTATION_RANGE(Func_, InSize_, in_value_uq, InSize_, InT_, BeginIndex_, EndIndex_)(in_vector_, in_vector_);
	}

	/// <summary>
	/// <para> Outputs a copy of the provided in_vector_ to out_vector_, with values within the provided index range negated. </para>
	/// <para> BeginIndex_ is the inclusive index at which to start writing negated values to the output Vector. </para>
	/// <para> EndIndex_ is the exclusive index at which to stop writing negated values to the output Vector. </para>
	/// </summary>
	/// <param name="out_vector_">EmuMath Vector to write copied and negated values to.</param>
	/// <param name="in_vector_">EmuMath Vector to copy, with negated values within the specified index range.</param>
	template<std::size_t BeginIndex_, std::size_t EndIndex_, std::size_t OutSize_, typename OutT_, std::size_t InSize_, typename InT_>
	constexpr inline void new_vector_negate_range(EmuMath::NewVector<OutSize_, OutT_>& out_vector_, const EmuMath::NewVector<InSize_, InT_>& in_vector_)
	{
		using Func_ = EmuCore::do_negate<typename EmuMath::NewVector<InSize_, InT_>::value_type_uq>;
		EMU_MATH_VECTOR_MUTATION_REF_RANGE(Func_, OutT_, OutSize_, InSize_, InT_, BeginIndex_, EndIndex_, BeginIndex_)(out_vector_, in_vector_, in_vector_);
	}

	/// <summary>
	/// <para>
	///		Outputs a partial negated copy of the provided in_vector_ to an output vector with template arguments OutSize_ and OutT_, 
	///		which are optional and default to the Size_ and T_ arguments of in_vector_.
	/// </para>
	/// <para> Non-negated indices in the output Vector will be default constructed. </para>
	/// <para> OutBegin_ is the inclusve index at which to start writing negated values to the output Vector. </para>
	/// <para> OutEnd_ is the exclusive index at which to stop writing negated values to the output Vector. </para>
	/// <para> 
	///		NegateBegin_ is the inclusive index at which to start reading values from in_vector_ in order to negate. 
	///		This is incremented per mutation, but is not changed when not in the negation range. 
	/// </para>
	/// </summary>
	/// <param name="in_vector_">: EmuMath Vector to read elements from when performing negations.</param>
	/// <returns>EmuMath Vector with negated values from the specified indices of in_vector_ within the OutBegin_:OutEnd_ range, and default values elsewhere.</returns>
	template<std::size_t OutSize_, typename OutT_, std::size_t OutBegin_, std::size_t OutEnd_, std::size_t NegateBegin_, typename InT_, std::size_t InSize_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> new_vector_negate_range_no_copy(const EmuMath::NewVector<InSize_, InT_>& in_vector_)
	{
		using Func_ = EmuCore::do_negate<typename EmuMath::NewVector<InSize_, InT_>::value_type_uq>;
		return EMU_MATH_VECTOR_MUTATION_RANGE_NO_COPY(Func_, OutSize_, OutT_, InSize_, InT_, OutBegin_, OutEnd_, NegateBegin_)(in_vector_);
	}
	template<typename OutT_, std::size_t OutBegin_, std::size_t OutEnd_, std::size_t NegateBegin_, typename InT_, std::size_t InSize_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<InSize_, OutT_> new_vector_negate_range_no_copy(const EmuMath::NewVector<InSize_, InT_>& in_vector_)
	{
		using Func_ = EmuCore::do_negate<typename EmuMath::NewVector<InSize_, InT_>::value_type_uq>;
		return EMU_MATH_VECTOR_MUTATION_RANGE_NO_COPY(Func_, InSize_, OutT_, InSize_, InT_, OutBegin_, OutEnd_, NegateBegin_)(in_vector_);
	}
	template<std::size_t OutSize_, std::size_t OutBegin_, std::size_t OutEnd_, std::size_t NegateBegin_, typename InT_, std::size_t InSize_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, typename EmuMath::NewVector<InSize_, InT_>::value_type_uq>
	new_vector_negate_range_no_copy(const EmuMath::NewVector<InSize_, InT_>& in_vector_)
	{
		using in_value_uq = typename EmuMath::NewVector<InSize_, InT_>::value_type_uq;
		using Func_ = EmuCore::do_negate<in_value_uq>;
		return EMU_MATH_VECTOR_MUTATION_RANGE_NO_COPY(Func_, OutSize_, in_value_uq, InSize_, InT_, OutBegin_, OutEnd_, NegateBegin_)(in_vector_);
	}
	template<std::size_t OutBegin_, std::size_t OutEnd_, std::size_t NegateBegin_, typename InT_, std::size_t InSize_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<InSize_, typename EmuMath::NewVector<InSize_, InT_>::value_type_uq>
	new_vector_negate_range_no_copy(const EmuMath::NewVector<InSize_, InT_>& in_vector_)
	{
		using in_value_uq = typename EmuMath::NewVector<InSize_, InT_>::value_type_uq;
		using Func_ = EmuCore::do_negate<in_value_uq>;
		return EMU_MATH_VECTOR_MUTATION_RANGE_NO_COPY(Func_, InSize_, in_value_uq, InSize_, InT_, OutBegin_, OutEnd_, NegateBegin_)(in_vector_);
	}

	/// <summary>
	/// <para> Outputs a partial negated copy of the provided in_vector_ to the provided out_vector_ </para>
	/// <para> Indices in out_vector_ not in the specified range will not be modified. </para>
	/// <para> OutBegin_ is the inclusve index at which to start writing negated values to the output Vector. </para>
	/// <para> OutEnd_ is the exclusive index at which to stop writing negated values to the output Vector. </para>
	/// <para> 
	///		NegateBegin_ is the inclusive index at which to start reading values from in_vector_ in order to negate. 
	///		This is incremented per mutation, but is not changed when not in the negation range. 
	/// </para>
	/// </summary>
	/// <param name="out_vector_">: EmuMath Vector to write negated elements to.</param>
	/// <param name="in_vector_">: EmuMath Vector to read elements from when performing negations.</param>
	template<std::size_t OutBegin_, std::size_t OutEnd_, std::size_t NegateBegin_ = 0, typename OutT_, std::size_t OutSize_, typename InT_, std::size_t InSize_>
	constexpr inline void new_vector_negate_range_no_copy(EmuMath::NewVector<OutSize_, OutT_>& out_vector_, const EmuMath::NewVector<InSize_, InT_>& in_vector_)
	{
		using Func_ = EmuCore::do_negate<typename EmuMath::NewVector<InSize_, InT_>::value_type_uq>;
		return EMU_MATH_VECTOR_MUTATION_REF_RANGE_NO_COPY(Func_, OutSize_, OutT_, InSize_, InT_, OutBegin_, OutEnd_, NegateBegin_)(out_vector_, in_vector_);
	}
#pragma endregion
}

#endif
