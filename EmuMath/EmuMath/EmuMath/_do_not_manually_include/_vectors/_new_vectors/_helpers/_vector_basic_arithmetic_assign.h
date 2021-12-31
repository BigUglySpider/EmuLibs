#ifndef EMU_MATH_NEW_VECTOR_BASIC_ARITHMETIC_ASSIGN_H_INC_
#define EMU_MATH_NEW_VECTOR_BASIC_ARITHMETIC_ASSIGN_H_INC_ 1

#include "_common_vector_helpers.h"
#include "../../../../../EmuCore/Functors/Arithmetic.h"

// CONTAINS:
// --- add_assign
// --- subtract_assign
// --- multiply_assign
// --- divide_assign
// --- mod_assign

namespace EmuMath::Helpers
{
	/// <summary>
	/// <para> Performs an add-assign operation on the passed EmuMath Vector, equivalent to `vector_ += rhs_`. </para>
	/// <para> If rhs_ is an EmuMath Vector: Respective indices will be used for each arithmetic operation; otherwise, all operations will use rhs_ directly. </para>
	/// <para> If both a BeginIndex_ and EndIndex_ is provided, the operation will only be performed for indices within the specified range. </para>
	/// </summary>
	/// <param name="lhs_vector_">EmuMath vector to perform the subtract-assign operation on, appearing on the left-hand side.</param>
	/// <param name="rhs_">: Scalar or EmuMath Vector appearing on the right-hand side of arithmetic operations.</param>
	/// <returns>Reference to lhs_vector_.</returns>
	template<std::size_t BeginIndex_, std::size_t EndIndex_, typename T_, std::size_t Size_, typename Rhs_>
	constexpr inline EmuMath::NewVector<Size_, T_>& new_vector_add_assign(EmuMath::NewVector<Size_, T_>& lhs_vector_, Rhs_&& rhs_)
	{
		_vector_underlying::_vector_mutate_with_func_template_invoke_only_no_func_passed<EmuCore::do_add_assign, BeginIndex_, EndIndex_>(lhs_vector_, std::forward<Rhs_>(rhs_));
		return lhs_vector_;
	}
	template<typename T_, std::size_t Size_, typename Rhs_>
	constexpr inline EmuMath::NewVector<Size_, T_>& new_vector_add_assign(EmuMath::NewVector<Size_, T_>& lhs_vector_, Rhs_&& rhs_)
	{
		_vector_underlying::_vector_mutate_with_func_template_invoke_only_no_func_passed<EmuCore::do_add_assign, 0, Size_>(lhs_vector_, std::forward<Rhs_>(rhs_));
		return lhs_vector_;
	}

	/// <summary>
	/// <para> Performs a subtract-assign operation on the passed EmuMath Vector, equivalent to `vector_ -= rhs_`. </para>
	/// <para> If rhs_ is an EmuMath Vector: Respective indices will be used for each arithmetic operation; otherwise, all operations will use rhs_ directly. </para>
	/// <para> If both a BeginIndex_ and EndIndex_ is provided, the operation will only be performed for indices within the specified range. </para>
	/// </summary>
	/// <param name="lhs_vector_">EmuMath vector to perform the subtract-assign operation on, appearing on the left-hand side.</param>
	/// <param name="rhs_">: Scalar or EmuMath Vector appearing on the right-hand side of arithmetic operations.</param>
	/// <returns>Reference to lhs_vector_.</returns>
	template<std::size_t BeginIndex_, std::size_t EndIndex_, typename T_, std::size_t Size_, typename Rhs_>
	constexpr inline EmuMath::NewVector<Size_, T_>& new_vector_subtract_assign(EmuMath::NewVector<Size_, T_>& lhs_vector_, Rhs_&& rhs_)
	{
		_vector_underlying::_vector_mutate_with_func_template_invoke_only_no_func_passed<EmuCore::do_subtract_assign, BeginIndex_, EndIndex_>(lhs_vector_, std::forward<Rhs_>(rhs_));
		return lhs_vector_;
	}
	template<typename T_, std::size_t Size_, typename Rhs_>
	constexpr inline EmuMath::NewVector<Size_, T_>& new_vector_subtract_assign(EmuMath::NewVector<Size_, T_>& lhs_vector_, Rhs_&& rhs_)
	{
		_vector_underlying::_vector_mutate_with_func_template_invoke_only_no_func_passed<EmuCore::do_subtract_assign, 0, Size_>(lhs_vector_, std::forward<Rhs_>(rhs_));
		return lhs_vector_;
	}

	/// <summary>
	/// <para> Performs a multiply-assign operation on the passed EmuMath Vector, equivalent to `vector_ *= rhs_`. </para>
	/// <para> If rhs_ is an EmuMath Vector: Respective indices will be used for each arithmetic operation; otherwise, all operations will use rhs_ directly. </para>
	/// <para> If both a BeginIndex_ and EndIndex_ is provided, the operation will only be performed for indices within the specified range. </para>
	/// </summary>
	/// <param name="lhs_vector_">EmuMath vector to perform the multiply-assign operation on, appearing on the left-hand side.</param>
	/// <param name="rhs_">: Scalar or EmuMath Vector appearing on the right-hand side of arithmetic operations.</param>
	/// <returns>Reference to lhs_vector_.</returns>
	template<std::size_t BeginIndex_, std::size_t EndIndex_, typename T_, std::size_t Size_, typename Rhs_>
	constexpr inline EmuMath::NewVector<Size_, T_>& new_vector_multiply_assign(EmuMath::NewVector<Size_, T_>& lhs_vector_, Rhs_&& rhs_)
	{
		_vector_underlying::_vector_mutate_with_func_template_invoke_only_no_func_passed<EmuCore::do_multiply_assign, BeginIndex_, EndIndex_>(lhs_vector_, std::forward<Rhs_>(rhs_));
		return lhs_vector_;
	}
	template<typename T_, std::size_t Size_, typename Rhs_>
	constexpr inline EmuMath::NewVector<Size_, T_>& new_vector_multiply_assign(EmuMath::NewVector<Size_, T_>& lhs_vector_, Rhs_&& rhs_)
	{
		_vector_underlying::_vector_mutate_with_func_template_invoke_only_no_func_passed<EmuCore::do_multiply_assign, 0, Size_>(lhs_vector_, std::forward<Rhs_>(rhs_));
		return lhs_vector_;
	}

	/// <summary>
	/// <para> Performs a divide-assign operation on the passed EmuMath Vector, equivalent to `vector_ *= rhs_`. </para>
	/// <para> If rhs_ is an EmuMath Vector: Respective indices will be used for each arithmetic operation; otherwise, all operations will use rhs_ directly. </para>
	/// <para> If both a BeginIndex_ and EndIndex_ is provided, the operation will only be performed for indices within the specified range. </para>
	/// </summary>
	/// <param name="lhs_vector_">EmuMath vector to perform the divide-assign operation on, appearing on the left-hand side.</param>
	/// <param name="rhs_">: Scalar or EmuMath Vector appearing on the right-hand side of arithmetic operations.</param>
	/// <returns>Reference to lhs_vector_.</returns>
	template<std::size_t BeginIndex_, std::size_t EndIndex_, typename T_, std::size_t Size_, typename Rhs_>
	constexpr inline EmuMath::NewVector<Size_, T_>& new_vector_divide_assign(EmuMath::NewVector<Size_, T_>& lhs_vector_, Rhs_&& rhs_)
	{
		_vector_underlying::_vector_mutate_with_func_template_invoke_only_no_func_passed<EmuCore::do_divide_assign, BeginIndex_, EndIndex_>(lhs_vector_, std::forward<Rhs_>(rhs_));
		return lhs_vector_;
	}
	template<typename T_, std::size_t Size_, typename Rhs_>
	constexpr inline EmuMath::NewVector<Size_, T_>& new_vector_divide_assign(EmuMath::NewVector<Size_, T_>& lhs_vector_, Rhs_&& rhs_)
	{
		_vector_underlying::_vector_mutate_with_func_template_invoke_only_no_func_passed<EmuCore::do_divide_assign, 0, Size_>(lhs_vector_, std::forward<Rhs_>(rhs_));
		return lhs_vector_;
	}

	/// <summary>
	/// <para> Performs a modulo-divide-assign operation on the passed EmuMath Vector, equivalent to `vector_ *= rhs_`. </para>
	/// <para> If rhs_ is an EmuMath Vector: Respective indices will be used for each arithmetic operation; otherwise, all operations will use rhs_ directly. </para>
	/// <para> If both a BeginIndex_ and EndIndex_ is provided, the operation will only be performed for indices within the specified range. </para>
	/// </summary>
	/// <param name="lhs_vector_">EmuMath vector to perform the modulo-divide-assign operation on, appearing on the left-hand side.</param>
	/// <param name="rhs_">: Scalar or EmuMath Vector appearing on the right-hand side of arithmetic operations.</param>
	/// <returns>Reference to lhs_vector_.</returns>
	template<std::size_t BeginIndex_, std::size_t EndIndex_, typename T_, std::size_t Size_, typename Rhs_>
	constexpr inline EmuMath::NewVector<Size_, T_>& new_vector_mod_assign(EmuMath::NewVector<Size_, T_>& lhs_vector_, Rhs_&& rhs_)
	{
		_vector_underlying::_vector_mutate_with_func_template_invoke_only_no_func_passed<EmuCore::do_mod_assign, BeginIndex_, EndIndex_>(lhs_vector_, std::forward<Rhs_>(rhs_));
		return lhs_vector_;
	}
	template<typename T_, std::size_t Size_, typename Rhs_>
	constexpr inline EmuMath::NewVector<Size_, T_>& new_vector_mod_assign(EmuMath::NewVector<Size_, T_>& lhs_vector_, Rhs_&& rhs_)
	{
		_vector_underlying::_vector_mutate_with_func_template_invoke_only_no_func_passed<EmuCore::do_mod_assign, 0, Size_>(lhs_vector_, std::forward<Rhs_>(rhs_));
		return lhs_vector_;
	}
}

#endif
