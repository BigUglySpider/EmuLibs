#ifndef EMU_MATH_VECTOR_OPERATORS_H_INC_
#define EMU_MATH_VECTOR_OPERATORS_H_INC_ 1

#include "_vector_t.h"

#pragma region CONST_ARITHMETIC
/// <summary>
/// <para> Default addition operator for EmuMath Vectors. </para>
/// <para> Outputs a Vector of the input left-hand size with the input Vector's `value_type_uq` as its type argument. </para>
/// </summary>
/// <param name="lhs_vector_">EmuMath Vector appearing on the left-hand side of addition.</param>
/// <param name="rhs_">Argument appearing on the right-hand side of addition as in `EmuMath::Helpers::vector_add`.</param>
/// <returns>EmuMath Vector of the left-hand size and `value_type_uq` containing the results of `EmuMath::Helpers::vector_add` with the given args.</returns>
template<std::size_t LhsSize_, typename LhsT_, typename Rhs_>
[[nodiscard]] constexpr inline auto operator+(const EmuMath::Vector<LhsSize_, LhsT_>& lhs_vector_, Rhs_&& rhs_)
	-> EmuMath::Vector<LhsSize_, typename EmuMath::Vector<LhsSize_, LhsT_>::value_type_uq>
{
	return EmuMath::Helpers::vector_add<LhsSize_, typename EmuMath::Vector<LhsSize_, LhsT_>::value_type_uq>(lhs_vector_, std::forward<Rhs_>(rhs_));
}

/// <summary>
/// <para> Default subtraction operator for EmuMath Vectors. </para>
/// <para> Outputs a Vector of the input left-hand size with the input Vector's `value_type_uq` as its type argument. </para>
/// </summary>
/// <param name="lhs_vector_">EmuMath Vector appearing on the left-hand side of subtraction.</param>
/// <param name="rhs_">Argument appearing on the right-hand side of subtraction as in `EmuMath::Helpers::vector_subtract`.</param>
/// <returns>EmuMath Vector of the left-hand size and `value_type_uq` containing the results of `EmuMath::Helpers::vector_subtract` with the given args.</returns>
template<std::size_t LhsSize_, typename LhsT_, typename Rhs_>
[[nodiscard]] constexpr inline auto operator-(const EmuMath::Vector<LhsSize_, LhsT_>& lhs_vector_, Rhs_&& rhs_)
	-> EmuMath::Vector<LhsSize_, typename EmuMath::Vector<LhsSize_, LhsT_>::value_type_uq>
{
	return EmuMath::Helpers::vector_subtract<LhsSize_, typename EmuMath::Vector<LhsSize_, LhsT_>::value_type_uq>(lhs_vector_, std::forward<Rhs_>(rhs_));
}

/// <summary>
/// <para> Default negation operator for EmuMath Vectors. </para>
/// <para> Outputs a Vector of the input left-hand size with the input Vector's `value_type_uq` as its type argument. </para>
/// </summary>
/// <param name="vector_">EmuMath Vector to negate.</param>
/// <returns>EmuMath Vector of the left-hand size and `value_type_uq` containing the results of `EmuMath::Helpers::vector_subtract` with the given args.</returns>
template<std::size_t LhsSize_, typename LhsT_>
[[nodiscard]] constexpr inline auto operator-(const EmuMath::Vector<LhsSize_, LhsT_>& vector_)
	-> EmuMath::Vector<LhsSize_, typename EmuMath::Vector<LhsSize_, LhsT_>::value_type_uq>
{
	return EmuMath::Helpers::vector_negate<LhsSize_, typename EmuMath::Vector<LhsSize_, LhsT_>::value_type_uq>(vector_);
}

/// <summary>
/// <para> Default multiplication operator for EmuMath Vectors. </para>
/// <para> Does not accept items identified as an EmuMatrix; such a default implementation is deferred to an extension included by the Matrix module. </para>
/// <para> Outputs a Vector of the input left-hand size with the input Vector's `value_type_uq` as its type argument. </para>
/// </summary>
/// <param name="lhs_vector_">EmuMath Vector appearing on the left-hand side of multiplication.</param>
/// <param name="rhs_">Argument appearing on the right-hand side of addition as in `EmuMath::Helpers::vector_multiply`.</param>
/// <returns>EmuMath Vector of the left-hand size and `value_type_uq` containing the results of `EmuMath::Helpers::vector_multiply` with the given args.</returns>
template<std::size_t LhsSize_, typename LhsT_, typename Rhs_>
requires(!EmuMath::TMP::is_emu_matrix_v<Rhs_>)
[[nodiscard]] constexpr inline auto operator*(const EmuMath::Vector<LhsSize_, LhsT_>& lhs_vector_, Rhs_&& rhs_)
	-> EmuMath::Vector<LhsSize_, typename EmuMath::Vector<LhsSize_, LhsT_>::value_type_uq>
{
	return EmuMath::Helpers::vector_multiply<LhsSize_, typename EmuMath::Vector<LhsSize_, LhsT_>::value_type_uq>(lhs_vector_, std::forward<Rhs_>(rhs_));
}

/// <summary>
/// <para> Default division operator for EmuMath Vectors. </para>
/// <para> Outputs a Vector of the input left-hand size with the input Vector's `value_type_uq` as its type argument. </para>
/// </summary>
/// <param name="lhs_vector_">EmuMath Vector appearing on the left-hand side of division.</param>
/// <param name="rhs_">Argument appearing on the right-hand side of subtraction as in `EmuMath::Helpers::vector_divide`.</param>
/// <returns>EmuMath Vector of the left-hand size and `value_type_uq` containing the results of `EmuMath::Helpers::vector_divide` with the given args.</returns>
template<std::size_t LhsSize_, typename LhsT_, typename Rhs_>
[[nodiscard]] constexpr inline auto operator/(const EmuMath::Vector<LhsSize_, LhsT_>& lhs_vector_, Rhs_&& rhs_)
	-> EmuMath::Vector<LhsSize_, typename EmuMath::Vector<LhsSize_, LhsT_>::value_type_uq>
{
	return EmuMath::Helpers::vector_divide<LhsSize_, typename EmuMath::Vector<LhsSize_, LhsT_>::value_type_uq>(lhs_vector_, std::forward<Rhs_>(rhs_));
}

/// <summary>
/// <para> Default modulo division operator for EmuMath Vectors. </para>
/// <para> Outputs a Vector of the input left-hand size with the input Vector's `value_type_uq` as its type argument. </para>
/// </summary>
/// <param name="lhs_vector_">EmuMath Vector appearing on the left-hand side of modulo division.</param>
/// <param name="rhs_">Argument appearing on the right-hand side of subtraction as in `EmuMath::Helpers::vector_mod`.</param>
/// <returns>EmuMath Vector of the left-hand size and `value_type_uq` containing the results of `EmuMath::Helpers::vector_mod` with the given args.</returns>
template<std::size_t LhsSize_, typename LhsT_, typename Rhs_>
[[nodiscard]] constexpr inline auto operator%(const EmuMath::Vector<LhsSize_, LhsT_>& lhs_vector_, Rhs_&& rhs_)
	-> EmuMath::Vector<LhsSize_, typename EmuMath::Vector<LhsSize_, LhsT_>::value_type_uq>
{
	return EmuMath::Helpers::vector_mod<LhsSize_, typename EmuMath::Vector<LhsSize_, LhsT_>::value_type_uq>(lhs_vector_, std::forward<Rhs_>(rhs_));
}
#pragma endregion

#pragma region ARITHMETIC_ASSIGN
/// <summary>
/// <para> Default addition-assign operator for EmuMath Vectors. </para>
/// </summary>
/// <param name="lhs_vector_">EmuMath Vector appearing on the left-hand side of addition, and to which respective results will be assigned.</param>
/// <param name="rhs_">Argument appearing on the right-hand side of addition as in `EmuMath::Helpers::vector_add_assign`.</param>
/// <returns>Reference to the left-hand Vector.</returns>
template<std::size_t LhsSize_, typename LhsT_, typename Rhs_>
constexpr inline auto operator+=(EmuMath::Vector<LhsSize_, LhsT_>& lhs_vector_, Rhs_&& rhs_)
	-> EmuMath::Vector<LhsSize_, LhsT_>&
{
	EmuMath::Helpers::vector_add_assign(lhs_vector_, std::forward<Rhs_>(rhs_));
	return lhs_vector_;
}

/// <summary>
/// <para> Default subtraction-assign operator for EmuMath Vectors. </para>
/// </summary>
/// <param name="lhs_vector_">EmuMath Vector appearing on the left-hand side of subtraction, and to which respective results will be assigned.</param>
/// <param name="rhs_">Argument appearing on the right-hand side of subtraction as in `EmuMath::Helpers::vector_subtract_assign`.</param>
/// <returns>Reference to the left-hand Vector.</returns>
template<std::size_t LhsSize_, typename LhsT_, typename Rhs_>
constexpr inline auto operator-=(EmuMath::Vector<LhsSize_, LhsT_>& lhs_vector_, Rhs_&& rhs_)
	-> EmuMath::Vector<LhsSize_, LhsT_>&
{
	EmuMath::Helpers::vector_subtract_assign(lhs_vector_, std::forward<Rhs_>(rhs_));
	return lhs_vector_;
}

/// <summary>
/// <para> Default multiplication-assign operator for EmuMath Vectors. </para>
/// <para> Does not accept items identified as an EmuMatrix; such a default implementation is deferred to an extension included by the Matrix module. </para>
/// </summary>
/// <param name="lhs_vector_">EmuMath Vector appearing on the left-hand side of multiplication, and to which respective results will be assigned.</param>
/// <param name="rhs_">Argument appearing on the right-hand side of addition as in `EmuMath::Helpers::vector_multiply_assign`.</param>
/// <returns>Reference to the left-hand Vector.</returns>
template<std::size_t LhsSize_, typename LhsT_, typename Rhs_>
requires(!EmuMath::TMP::is_emu_matrix_v<Rhs_>)
constexpr inline auto operator*=(EmuMath::Vector<LhsSize_, LhsT_>& lhs_vector_, Rhs_&& rhs_)
	-> EmuMath::Vector<LhsSize_, LhsT_>&
{
	EmuMath::Helpers::vector_multiply_assign(lhs_vector_, std::forward<Rhs_>(rhs_));
	return lhs_vector_;
}

/// <summary>
/// <para> Default division-assign operator for EmuMath Vectors. </para>
/// </summary>
/// <param name="lhs_vector_">EmuMath Vector appearing on the left-hand side of division, and to which respective results will be assigned.</param>
/// <param name="rhs_">Argument appearing on the right-hand side of subtraction as in `EmuMath::Helpers::vector_divide_assign`.</param>
/// <returns>Reference to the left-hand Vector.</returns>
template<std::size_t LhsSize_, typename LhsT_, typename Rhs_>
constexpr inline auto operator/=(EmuMath::Vector<LhsSize_, LhsT_>& lhs_vector_, Rhs_&& rhs_)
	-> EmuMath::Vector<LhsSize_, LhsT_>&
{
	EmuMath::Helpers::vector_divide_assign(lhs_vector_, std::forward<Rhs_>(rhs_));
	return lhs_vector_;
}

/// <summary>
/// <para> Default modulo division-assign operator for EmuMath Vectors. </para>
/// </summary>
/// <param name="lhs_vector_">EmuMath Vector appearing on the left-hand side of modulo division, and to which respective results will be assigned.</param>
/// <param name="rhs_">Argument appearing on the right-hand side of subtraction as in `EmuMath::Helpers::vector_mod_assign`.</param>
/// <returns>Reference to the left-hand Vector.</returns>
template<std::size_t LhsSize_, typename LhsT_, typename Rhs_>
constexpr inline auto operator%=(EmuMath::Vector<LhsSize_, LhsT_>& lhs_vector_, Rhs_&& rhs_)
	-> EmuMath::Vector<LhsSize_, LhsT_>&
{
	EmuMath::Helpers::vector_mod_assign(lhs_vector_, std::forward<Rhs_>(rhs_));
	return lhs_vector_;
}

/// <summary>
/// <para> Default pre-increment operator for EmuMath Vectors. </para>
/// </summary>
/// <param name="vector_">EmuMath Vector to perform the pre-increment operation on as per `EmuMath::Helpers::vector_pre_increment`.</param>
/// <returns>Reference to the left-hand Vector.</returns>
template<std::size_t Size_, typename T_>
constexpr inline auto operator++(EmuMath::Vector<Size_, T_>& vector_)
	-> EmuMath::Vector<Size_, T_>&
{
	return EmuMath::Helpers::vector_pre_increment(vector_);
}

/// <summary>
/// <para> Default post-increment operator for EmuMath Vectors. </para>
/// </summary>
/// <param name="vector_">EmuMath Vector to perform the post-increment operation on as per `EmuMath::Helpers::vector_post_increment`.</param>
/// <returns>Copy to the left-hand Vector before the increment operation was performed.</returns>
template<std::size_t Size_, typename T_>
constexpr inline auto operator++(EmuMath::Vector<Size_, T_>& vector_, int)
	-> EmuMath::Vector<Size_, T_>
{
	return EmuMath::Helpers::vector_post_increment(vector_);
}

/// <summary>
/// <para> Default pre-decrement operator for EmuMath Vectors. </para>
/// </summary>
/// <param name="vector_">EmuMath Vector to perform the pre-decrement operation on as per `EmuMath::Helpers::vector_pre_decrement`.</param>
/// <returns>Reference to the left-hand Vector.</returns>
template<std::size_t Size_, typename T_>
constexpr inline auto operator--(EmuMath::Vector<Size_, T_>& vector_)
	-> EmuMath::Vector<Size_, T_>&
{
	return EmuMath::Helpers::vector_pre_decrement(vector_);
}

/// <summary>
/// <para> Default post-decrement operator for EmuMath Vectors. </para>
/// </summary>
/// <param name="vector_">EmuMath Vector to perform the post-decrement operation on as per `EmuMath::Helpers::vector_post_decrement`.</param>
/// <returns>Copy to the left-hand Vector before the decrement operation was performed.</returns>
template<std::size_t Size_, typename T_>
constexpr inline auto operator--(EmuMath::Vector<Size_, T_>& vector_, int)
	-> EmuMath::Vector<Size_, T_>
{
	return EmuMath::Helpers::vector_post_decrement(vector_);
}
#pragma endregion

#pragma region CONST_BITWISE
/// <summary>
/// <para> Default bitwise AND operator for EmuMath Vectors. </para>
/// <para> Outputs a Vector of the input left-hand size with the input Vector's `value_type_uq` as its type argument. </para>
/// </summary>
/// <param name="lhs_vector_">EmuMath Vector appearing on the left-hand side of the bitwise AND.</param>
/// <param name="rhs_">Argument appearing on the right-hand side of the bitwise AND as in `EmuMath::Helpers::vector_bitwise_and`.</param>
/// <returns>EmuMath Vector of the left-hand size and `value_type_uq` containing the results of `EmuMath::Helpers::vector_bitwise_and` with the given args.</returns>
template<std::size_t LhsSize_, typename LhsT_, typename Rhs_>
[[nodiscard]] constexpr inline auto operator&(const EmuMath::Vector<LhsSize_, LhsT_>& lhs_vector_, Rhs_&& rhs_)
	-> EmuMath::Vector<LhsSize_, typename EmuMath::Vector<LhsSize_, LhsT_>::value_type_uq>
{
	return EmuMath::Helpers::vector_bitwise_and<LhsSize_, typename EmuMath::Vector<LhsSize_, LhsT_>::value_type_uq>(lhs_vector_, std::forward<Rhs_>(rhs_));
}

/// <summary>
/// <para> Default bitiwse OR operator for EmuMath Vectors. </para>
/// <para> Outputs a Vector of the input left-hand size with the input Vector's `value_type_uq` as its type argument. </para>
/// </summary>
/// <param name="lhs_vector_">EmuMath Vector appearing on the left-hand side of the bitwise OR.</param>
/// <param name="rhs_">Argument appearing on the right-hand side of subtraction as in `EmuMath::Helpers::vector_bitwise_or`.</param>
/// <returns>EmuMath Vector of the left-hand size and `value_type_uq` containing the results of `EmuMath::Helpers::vector_bitwise_or` with the given args.</returns>
template<std::size_t LhsSize_, typename LhsT_, typename Rhs_>
[[nodiscard]] constexpr inline auto operator|(const EmuMath::Vector<LhsSize_, LhsT_>& lhs_vector_, Rhs_&& rhs_)
	-> EmuMath::Vector<LhsSize_, typename EmuMath::Vector<LhsSize_, LhsT_>::value_type_uq>
{
	return EmuMath::Helpers::vector_bitwise_or<LhsSize_, typename EmuMath::Vector<LhsSize_, LhsT_>::value_type_uq>(lhs_vector_, std::forward<Rhs_>(rhs_));
}

/// <summary>
/// <para> Default bitwise XOR operator for EmuMath Vectors. </para>
/// <para> Outputs a Vector of the input left-hand size with the input Vector's `value_type_uq` as its type argument. </para>
/// </summary>
/// <param name="lhs_vector_">EmuMath Vector appearing on the left-hand side of the bitwise XOR.</param>
/// <param name="rhs_">Argument appearing on the right-hand side of addition as in `EmuMath::Helpers::vector_bitwise_xor`.</param>
/// <returns>EmuMath Vector of the left-hand size and `value_type_uq` containing the results of `EmuMath::Helpers::vector_bitwise_xor` with the given args.</returns>
template<std::size_t LhsSize_, typename LhsT_, typename Rhs_>
[[nodiscard]] constexpr inline auto operator^(const EmuMath::Vector<LhsSize_, LhsT_>& lhs_vector_, Rhs_&& rhs_)
	-> EmuMath::Vector<LhsSize_, typename EmuMath::Vector<LhsSize_, LhsT_>::value_type_uq>
{
	return EmuMath::Helpers::vector_bitwise_xor<LhsSize_, typename EmuMath::Vector<LhsSize_, LhsT_>::value_type_uq>(lhs_vector_, std::forward<Rhs_>(rhs_));
}

/// <summary>
/// <para> Default left-shift operator for EmuMath Vectors. </para>
/// <para> Outputs a Vector of the input left-hand size with the input Vector's `value_type_uq` as its type argument. </para>
/// </summary>
/// <param name="lhs_vector_">EmuMath Vector appearing on the left-hand side of left-shift.</param>
/// <param name="rhs_">Argument appearing on the right-hand side of subtraction as in `EmuMath::Helpers::vector_shift_left`.</param>
/// <returns>EmuMath Vector of the left-hand size and `value_type_uq` containing the results of `EmuMath::Helpers::vector_shift_left` with the given args.</returns>
template<std::size_t LhsSize_, typename LhsT_, typename Rhs_>
[[nodiscard]] constexpr inline auto operator<<(const EmuMath::Vector<LhsSize_, LhsT_>& lhs_vector_, Rhs_&& rhs_)
	-> EmuMath::Vector<LhsSize_, typename EmuMath::Vector<LhsSize_, LhsT_>::value_type_uq>
{
	return EmuMath::Helpers::vector_shift_left<LhsSize_, typename EmuMath::Vector<LhsSize_, LhsT_>::value_type_uq>(lhs_vector_, std::forward<Rhs_>(rhs_));
}

/// <summary>
/// <para> Default right-shift operator for EmuMath Vectors. </para>
/// <para> Outputs a Vector of the input left-hand size with the input Vector's `value_type_uq` as its type argument. </para>
/// </summary>
/// <param name="lhs_vector_">EmuMath Vector appearing on the right-hand side of left-shift.</param>
/// <param name="rhs_">Argument appearing on the right-hand side of subtraction as in `EmuMath::Helpers::vector_shift_right`.</param>
/// <returns>EmuMath Vector of the left-hand size and `value_type_uq` containing the results of `EmuMath::Helpers::vector_shift_right` with the given args.</returns>
template<std::size_t LhsSize_, typename LhsT_, typename Rhs_>
[[nodiscard]] constexpr inline auto operator>>(const EmuMath::Vector<LhsSize_, LhsT_>& lhs_vector_, Rhs_&& rhs_)
	-> EmuMath::Vector<LhsSize_, typename EmuMath::Vector<LhsSize_, LhsT_>::value_type_uq>
{
	return EmuMath::Helpers::vector_shift_right<LhsSize_, typename EmuMath::Vector<LhsSize_, LhsT_>::value_type_uq>(lhs_vector_, std::forward<Rhs_>(rhs_));
}

/// <summary>
/// <para> Default bitwise NOT operator for EmuMath Vectors. </para>
/// <para> Outputs a Vector of the input left-hand size with the input Vector's `value_type_uq` as its type argument. </para>
/// </summary>
/// <param name="lhs_vector_">EmuMath Vector to calculate the bitwise NOT of.</param>
/// <returns>EmuMath Vector of the input size and `value_type_uq` containing the results of `EmuMath::Helpers::vector_bitwise_not` with the given arg.</returns>
template<std::size_t LhsSize_, typename LhsT_>
[[nodiscard]] constexpr inline auto operator~(const EmuMath::Vector<LhsSize_, LhsT_>& lhs_vector_)
	-> EmuMath::Vector<LhsSize_, typename EmuMath::Vector<LhsSize_, LhsT_>::value_type_uq>
{
	return EmuMath::Helpers::vector_bitwise_not<LhsSize_, typename EmuMath::Vector<LhsSize_, LhsT_>::value_type_uq>(lhs_vector_);
}
#pragma endregion

#pragma region BITWISE_ASSIGN
/// <summary>
/// <para> Default bitwise AND-assign operator for EmuMath Vectors. </para>
/// <para> Outputs a Vector of the input left-hand size with the input Vector's `value_type_uq` as its type argument. </para>
/// </summary>
/// <param name="lhs_vector_">EmuMath Vector appearing on the left-hand side of the bitwise AND.</param>
/// <param name="rhs_">Argument appearing on the right-hand side of the bitwise AND as in `EmuMath::Helpers::vector_bitwise_and_assign`.</param>
/// <returns>Reference to the left-hand Vector.</returns>
template<std::size_t LhsSize_, typename LhsT_, typename Rhs_>
[[nodiscard]] constexpr inline auto operator&=(EmuMath::Vector<LhsSize_, LhsT_>& lhs_vector_, Rhs_&& rhs_)
	-> EmuMath::Vector<LhsSize_, LhsT_>&
{
	EmuMath::Helpers::vector_bitwise_and_assign<LhsSize_, typename EmuMath::Vector<LhsSize_, LhsT_>::value_type_uq>(lhs_vector_, std::forward<Rhs_>(rhs_));
	return lhs_vector_;
}

/// <summary>
/// <para> Default bitiwse OR-assign operator for EmuMath Vectors. </para>
/// <para> Outputs a Vector of the input left-hand size with the input Vector's `value_type_uq` as its type argument. </para>
/// </summary>
/// <param name="lhs_vector_">EmuMath Vector appearing on the left-hand side of the bitwise OR.</param>
/// <param name="rhs_">Argument appearing on the right-hand side of subtraction as in `EmuMath::Helpers::vector_bitwise_or_assign`.</param>
/// <returns>Reference to the left-hand Vector.</returns>
template<std::size_t LhsSize_, typename LhsT_, typename Rhs_>
[[nodiscard]] constexpr inline auto operator|=(EmuMath::Vector<LhsSize_, LhsT_>& lhs_vector_, Rhs_&& rhs_)
	-> EmuMath::Vector<LhsSize_, LhsT_>&
{
	EmuMath::Helpers::vector_bitwise_or_assign<LhsSize_, typename EmuMath::Vector<LhsSize_, LhsT_>::value_type_uq>(lhs_vector_, std::forward<Rhs_>(rhs_));
	return lhs_vector_;
}

/// <summary>
/// <para> Default bitwise XOR-assign operator for EmuMath Vectors. </para>
/// <para> Outputs a Vector of the input left-hand size with the input Vector's `value_type_uq` as its type argument. </para>
/// </summary>
/// <param name="lhs_vector_">EmuMath Vector appearing on the left-hand side of the bitwise XOR.</param>
/// <param name="rhs_">Argument appearing on the right-hand side of addition as in `EmuMath::Helpers::vector_bitwise_xor_assign`.</param>
/// <returns>Reference to the left-hand Vector.</returns>
template<std::size_t LhsSize_, typename LhsT_, typename Rhs_>
[[nodiscard]] constexpr inline auto operator^=(EmuMath::Vector<LhsSize_, LhsT_>& lhs_vector_, Rhs_&& rhs_)
	-> EmuMath::Vector<LhsSize_, LhsT_>&
{
	EmuMath::Helpers::vector_bitwise_xor_assign<LhsSize_, typename EmuMath::Vector<LhsSize_, LhsT_>::value_type_uq>(lhs_vector_, std::forward<Rhs_>(rhs_));
	return lhs_vector_;
}
#pragma endregion

#pragma region CMP
/// <summary>
/// <para> Default equality comparison operator for EmuMath Vectors. </para>
/// <para> 
///		By default, non-contained indices are included in the comparison. To limit only to the size of the smallest included Vector (if rhs is a Vector), 
///		`IncludeNonContained_` may be set to false.
/// </para>
/// </summary>
/// <param name="lhs_vector_">EmuMath Vector appearing on the left-hand side of the comparison.</param>
/// <param name="rhs_">Argument appearing on the right-hand side of the comparison as in `EmuMath::Helpers::vector_cmp_equal`.</param>
/// <returns>Boolean result of the comparison.</returns>
template<bool IncludeNonContained_ = true, std::size_t LhsSize_, typename LhsT_, typename Rhs_>
[[nodiscard]] constexpr inline bool operator==(EmuMath::Vector<LhsSize_, LhsT_>& lhs_vector_, Rhs_&& rhs_)
{
	return EmuMath::Helpers::vector_cmp_equal<IncludeNonContained_>(lhs_vector_, std::forward<Rhs_>(rhs_));
}

/// <summary>
/// <para> Default inequality comparison operator for EmuMath Vectors. </para>
/// <para> 
///		By default, non-contained indices are included in the comparison. To limit only to the size of the smallest included Vector (if rhs is a Vector), 
///		`IncludeNonContained_` may be set to false.
/// </para>
/// </summary>
/// <param name="lhs_vector_">EmuMath Vector appearing on the left-hand side of the comparison.</param>
/// <param name="rhs_">Argument appearing on the right-hand side of the comparison as in `EmuMath::Helpers::vector_cmp_not_equal`.</param>
/// <returns>Boolean result of the comparison.</returns>
template<bool IncludeNonContained_ = true, std::size_t LhsSize_, typename LhsT_, typename Rhs_>
[[nodiscard]] constexpr inline bool operator!=(EmuMath::Vector<LhsSize_, LhsT_>& lhs_vector_, Rhs_&& rhs_)
{
	return EmuMath::Helpers::vector_cmp_not_equal<IncludeNonContained_>(lhs_vector_, std::forward<Rhs_>(rhs_));
}

/// <summary>
/// <para> Default less-than comparison operator for EmuMath Vectors. </para>
/// <para> 
///		By default, non-contained indices are included in the comparison. To limit only to the size of the smallest included Vector (if rhs is a Vector), 
///		`IncludeNonContained_` may be set to false.
/// </para>
/// <para> If `rhs_` is an EmuMath Vector, this compares the magnitudes of thw two Vectors. </para>
/// </summary>
/// <param name="lhs_vector_">EmuMath Vector appearing on the left-hand side of the comparison.</param>
/// <param name="rhs_">Argument appearing on the right-hand side of the comparison as in `EmuMath::Helpers::vector_cmp_less`.</param>
/// <returns>Boolean result of the comparison.</returns>
template<bool IncludeNonContained_ = true, std::size_t LhsSize_, typename LhsT_, typename Rhs_>
[[nodiscard]] constexpr inline bool operator<(EmuMath::Vector<LhsSize_, LhsT_>& lhs_vector_, Rhs_&& rhs_)
{
	return EmuMath::Helpers::vector_cmp_less<IncludeNonContained_>(lhs_vector_, std::forward<Rhs_>(rhs_));
}

/// <summary>
/// <para> Default greater-than comparison operator for EmuMath Vectors. </para>
/// <para> 
///		By default, non-contained indices are included in the comparison. To limit only to the size of the smallest included Vector (if rhs is a Vector), 
///		`IncludeNonContained_` may be set to false.
/// </para>
/// <para> If `rhs_` is an EmuMath Vector, this compares the magnitudes of thw two Vectors. </para>
/// </summary>
/// <param name="lhs_vector_">EmuMath Vector appearing on the left-hand side of the comparison.</param>
/// <param name="rhs_">Argument appearing on the right-hand side of the comparison as in `EmuMath::Helpers::vector_cmp_greater`.</param>
/// <returns>Boolean result of the comparison.</returns>
template<bool IncludeNonContained_ = true, std::size_t LhsSize_, typename LhsT_, typename Rhs_>
[[nodiscard]] constexpr inline bool operator>(EmuMath::Vector<LhsSize_, LhsT_>& lhs_vector_, Rhs_&& rhs_)
{
	return EmuMath::Helpers::vector_cmp_greater<IncludeNonContained_>(lhs_vector_, std::forward<Rhs_>(rhs_));
}

/// <summary>
/// <para> Default less-equal comparison operator for EmuMath Vectors. </para>
/// <para> 
///		By default, non-contained indices are included in the comparison. To limit only to the size of the smallest included Vector (if rhs is a Vector), 
///		`IncludeNonContained_` may be set to false.
/// </para>
/// <para> If `rhs_` is an EmuMath Vector, this compares the magnitudes of thw two Vectors. </para>
/// </summary>
/// <param name="lhs_vector_">EmuMath Vector appearing on the left-hand side of the comparison.</param>
/// <param name="rhs_">Argument appearing on the right-hand side of the comparison as in `EmuMath::Helpers::vector_cmp_less_equal`.</param>
/// <returns>Boolean result of the comparison.</returns>
template<bool IncludeNonContained_ = true, std::size_t LhsSize_, typename LhsT_, typename Rhs_>
[[nodiscard]] constexpr inline bool operator<=(EmuMath::Vector<LhsSize_, LhsT_>& lhs_vector_, Rhs_&& rhs_)
{
	return EmuMath::Helpers::vector_cmp_less_equal<IncludeNonContained_>(lhs_vector_, std::forward<Rhs_>(rhs_));
}

/// <summary>
/// <para> Default greater-equal comparison operator for EmuMath Vectors. </para>
/// <para> 
///		By default, non-contained indices are included in the comparison. To limit only to the size of the smallest included Vector (if rhs is a Vector), 
///		`IncludeNonContained_` may be set to false.
/// </para>
/// <para> If `rhs_` is an EmuMath Vector, this compares the magnitudes of thw two Vectors. </para>
/// </summary>
/// <param name="lhs_vector_">EmuMath Vector appearing on the left-hand side of the comparison.</param>
/// <param name="rhs_">Argument appearing on the right-hand side of the comparison as in `EmuMath::Helpers::vector_cmp_greater_equal`.</param>
/// <returns>Boolean result of the comparison.</returns>
template<bool IncludeNonContained_ = true, std::size_t LhsSize_, typename LhsT_, typename Rhs_>
[[nodiscard]] constexpr inline bool operator>=(EmuMath::Vector<LhsSize_, LhsT_>& lhs_vector_, Rhs_&& rhs_)
{
	return EmuMath::Helpers::vector_cmp_greater_equal<IncludeNonContained_>(lhs_vector_, std::forward<Rhs_>(rhs_));
}
#pragma endregion

#endif
