#ifndef EMU_MATH_NEW_VECTOR_UNARY_ARITHMETIC_H_INC_
#define EMU_MATH_NEW_VECTOR_UNARY_ARITHMETIC_H_INC_ 1

#include "_common_vector_helpers.h"
#include "../../../../../EmuCore/Functors/Arithmetic.h"

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
#pragma endregion

#pragma region PRE_DECREMENT_FUNCS
	// TODO: DECREMENTS
#pragma endregion

#pragma region POST_DECREMENT_FUNCS
	// TODO: DECREMENTS
#pragma endregion
}

#endif
