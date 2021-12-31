#ifndef EMU_MATH_NEW_VECTOR_BITWISE_ASSIGN_H_INC_
#define EMU_MATH_NEW_VECTOR_BITWISE_ASSIGN_H_INC_ 1

#include "_common_vector_helpers.h"
#include "../../../../../EmuCore/Functors/Bitwise.h"

// CONTAINS:
// --- bitwise_and_assign
// --- bitwise_or_assign
// --- bitwise_xor_assign

namespace EmuMath::Helpers
{
	/// <summary>
	/// <para> Performs a bitwise AND-assign operation on the passed EmuMath Vector, equivalent to `vector_ &= rhs_`. </para>
	/// <para> If rhs_ is an EmuMath Vector: Respective indices will be used for each bitwise operation; otherwise, all operations will use rhs_ directly. </para>
	/// <para> If both a BeginIndex_ and EndIndex_ is provided, the operation will only be performed for indices within the specified range. </para>
	/// </summary>
	/// <param name="lhs_vector_">EmuMath vector to perform the AND-assign operation on, appearing on the left-hand side.</param>
	/// <param name="rhs_">: Scalar or EmuMath Vector appearing on the right-hand side of bitwise operations.</param>
	/// <returns>Reference to lhs_vector_.</returns>
	template<std::size_t BeginIndex_, std::size_t EndIndex_, typename T_, std::size_t Size_, typename Rhs_>
	constexpr inline EmuMath::NewVector<Size_, T_>& new_vector_bitwise_and_assign(EmuMath::NewVector<Size_, T_>& lhs_vector_, Rhs_&& rhs_)
	{
		_vector_underlying::_vector_mutate_with_func_template_invoke_only_no_func_passed<EmuCore::do_bitwise_and_assign, BeginIndex_, EndIndex_>
		(
			lhs_vector_,
			std::forward<Rhs_>(rhs_)
		);
		return lhs_vector_;
	}
	template<typename T_, std::size_t Size_, typename Rhs_>
	constexpr inline EmuMath::NewVector<Size_, T_>& new_vector_bitwise_and_assign(EmuMath::NewVector<Size_, T_>& lhs_vector_, Rhs_&& rhs_)
	{
		_vector_underlying::_vector_mutate_with_func_template_invoke_only_no_func_passed<EmuCore::do_bitwise_and_assign, 0, Size_>
		(
			lhs_vector_,
			std::forward<Rhs_>(rhs_)
		);
		return lhs_vector_;
	}

	/// <summary>
	/// <para> Performs a bitwise OR-assign operation on the passed EmuMath Vector, equivalent to `vector_ |= rhs_`. </para>
	/// <para> If rhs_ is an EmuMath Vector: Respective indices will be used for each bitwise operation; otherwise, all operations will use rhs_ directly. </para>
	/// <para> If both a BeginIndex_ and EndIndex_ is provided, the operation will only be performed for indices within the specified range. </para>
	/// </summary>
	/// <param name="lhs_vector_">EmuMath vector to perform the OR-assign operation on, appearing on the left-hand side.</param>
	/// <param name="rhs_">: Scalar or EmuMath Vector appearing on the right-hand side of bitwise operations.</param>
	/// <returns>Reference to lhs_vector_.</returns>
	template<std::size_t BeginIndex_, std::size_t EndIndex_, typename T_, std::size_t Size_, typename Rhs_>
	constexpr inline EmuMath::NewVector<Size_, T_>& new_vector_bitwise_or_assign(EmuMath::NewVector<Size_, T_>& lhs_vector_, Rhs_&& rhs_)
	{
		_vector_underlying::_vector_mutate_with_func_template_invoke_only_no_func_passed<EmuCore::do_bitwise_or_assign, BeginIndex_, EndIndex_>
		(
			lhs_vector_,
			std::forward<Rhs_>(rhs_)
		);
		return lhs_vector_;
	}
	template<typename T_, std::size_t Size_, typename Rhs_>
	constexpr inline EmuMath::NewVector<Size_, T_>& new_vector_bitwise_or_assign(EmuMath::NewVector<Size_, T_>& lhs_vector_, Rhs_&& rhs_)
	{
		_vector_underlying::_vector_mutate_with_func_template_invoke_only_no_func_passed<EmuCore::do_bitwise_or_assign, 0, Size_>
		(
			lhs_vector_,
			std::forward<Rhs_>(rhs_)
		);
		return lhs_vector_;
	}

	/// <summary>
	/// <para> Performs a bitwise XOR-assign operation on the passed EmuMath Vector, equivalent to `vector_ ^= rhs_`. </para>
	/// <para> If rhs_ is an EmuMath Vector: Respective indices will be used for each bitwise operation; otherwise, all operations will use rhs_ directly. </para>
	/// <para> If both a BeginIndex_ and EndIndex_ is provided, the operation will only be performed for indices within the specified range. </para>
	/// </summary>
	/// <param name="lhs_vector_">EmuMath vector to perform the XOR-assign operation on, appearing on the left-hand side.</param>
	/// <param name="rhs_">: Scalar or EmuMath Vector appearing on the right-hand side of bitwise operations.</param>
	/// <returns>Reference to lhs_vector_.</returns>
	template<std::size_t BeginIndex_, std::size_t EndIndex_, typename T_, std::size_t Size_, typename Rhs_>
	constexpr inline EmuMath::NewVector<Size_, T_>& new_vector_bitwise_xor_assign(EmuMath::NewVector<Size_, T_>& lhs_vector_, Rhs_&& rhs_)
	{
		_vector_underlying::_vector_mutate_with_func_template_invoke_only_no_func_passed<EmuCore::do_bitwise_xor_assign, BeginIndex_, EndIndex_>
		(
			lhs_vector_,
			std::forward<Rhs_>(rhs_)
		);
		return lhs_vector_;
	}
	template<typename T_, std::size_t Size_, typename Rhs_>
	constexpr inline EmuMath::NewVector<Size_, T_>& new_vector_bitwise_xor_assign(EmuMath::NewVector<Size_, T_>& lhs_vector_, Rhs_&& rhs_)
	{
		_vector_underlying::_vector_mutate_with_func_template_invoke_only_no_func_passed<EmuCore::do_bitwise_xor_assign, 0, Size_>
		(
			lhs_vector_,
			std::forward<Rhs_>(rhs_)
		);
		return lhs_vector_;
	}
}

#endif
