#ifndef EMU_MATH_FAST_QUATERNION_OPERATORS_T_H_INC_
#define EMU_MATH_FAST_QUATERNION_OPERATORS_T_H_INC_ 1

#include "_fast_quaternion_t.h"

#pragma region CONST_ADD_OPERATORS
template<typename T_, std::size_t RegisterWidth_>
[[nodiscard]] constexpr inline auto operator+
(
	const EmuMath::FastQuaternion<T_, RegisterWidth_>& lhs_,
	const EmuMath::FastQuaternion<T_, RegisterWidth_>& rhs_
)
{
	return EmuMath::Helpers::fast_quaternion_add(lhs_, rhs_);
}
#pragma endregion

#pragma region CONST_SUBTRACT_OPERATORS
template<typename T_, std::size_t RegisterWidth_>
[[nodiscard]] constexpr inline auto operator-
(
	const EmuMath::FastQuaternion<T_, RegisterWidth_>& lhs_,
	const EmuMath::FastQuaternion<T_, RegisterWidth_>& rhs_
	)
{
	return EmuMath::Helpers::fast_quaternion_subtract(lhs_, rhs_);
}
#pragma endregion

#pragma region CONST_MULTIPLY_OPERATORS
template<typename T_, std::size_t RegisterWidth_>
[[nodiscard]] constexpr inline auto operator*
(
	const EmuMath::FastQuaternion<T_, RegisterWidth_>& lhs_,
	typename EmuMath::FastQuaternion<T_, RegisterWidth_>::register_arg_type rhs_scalar_register_
)
{
	return EmuMath::Helpers::fast_quaternion_multiply_scalar(lhs_, rhs_scalar_register_);
}

template<typename T_, std::size_t RegisterWidth_, EmuConcepts::Arithmetic RhsScalar_>
[[nodiscard]] constexpr inline auto operator*(const EmuMath::FastQuaternion<T_, RegisterWidth_>& lhs_, RhsScalar_&& rhs_scalar_)
{
	return EmuMath::Helpers::fast_quaternion_multiply_scalar(lhs_, std::forward<RhsScalar_>(rhs_scalar_));
}

template<typename T_, std::size_t RegisterWidth_>
[[nodiscard]] constexpr inline auto operator*
(
	const EmuMath::FastQuaternion<T_, RegisterWidth_>& lhs_,
	const EmuMath::FastQuaternion<T_, RegisterWidth_>& rhs_
)
{
	return EmuMath::Helpers::fast_quaternion_multiply_quaternion(lhs_, rhs_);
}
#pragma endregion

#pragma region CONST_DIVIDE_OPERATORS
template<typename T_, std::size_t RegisterWidth_>
[[nodiscard]] constexpr inline auto operator/
(
	const EmuMath::FastQuaternion<T_, RegisterWidth_>& lhs_,
	typename EmuMath::FastQuaternion<T_, RegisterWidth_>::register_arg_type rhs_scalar_register_
	)
{
	return EmuMath::Helpers::fast_quaternion_divide(lhs_, rhs_scalar_register_);
}

template<typename T_, std::size_t RegisterWidth_, EmuConcepts::Arithmetic RhsScalar_>
[[nodiscard]] constexpr inline auto operator/(const EmuMath::FastQuaternion<T_, RegisterWidth_>& lhs_, RhsScalar_&& rhs_scalar_)
{
	return EmuMath::Helpers::fast_quaternion_divide(lhs_, std::forward<RhsScalar_>(rhs_scalar_));
}
#pragma endregion

#pragma region CONST_ADD_OPERATORS
template<typename T_, std::size_t RegisterWidth_>
[[nodiscard]] constexpr inline auto operator+=
(
	EmuMath::FastQuaternion<T_, RegisterWidth_>& lhs_,
	const EmuMath::FastQuaternion<T_, RegisterWidth_>& rhs_
) -> EmuMath::FastQuaternion<T_, RegisterWidth_>&
{
	EmuMath::Helpers::fast_quaternion_add_assign(lhs_, rhs_);
	return lhs_;
}
#pragma endregion

#pragma region CONST_SUBTRACT_OPERATORS
template<typename T_, std::size_t RegisterWidth_>
[[nodiscard]] constexpr inline auto operator-=
(
	EmuMath::FastQuaternion<T_, RegisterWidth_>& lhs_,
	const EmuMath::FastQuaternion<T_, RegisterWidth_>& rhs_
) -> EmuMath::FastQuaternion<T_, RegisterWidth_>&
{
	EmuMath::Helpers::fast_quaternion_subtract_assign(lhs_, rhs_);
	return lhs_;
}
#pragma endregion

#pragma region CONST_MULTIPLY_OPERATORS
template<typename T_, std::size_t RegisterWidth_>
[[nodiscard]] constexpr inline auto operator*=
(
	EmuMath::FastQuaternion<T_, RegisterWidth_>& lhs_,
	typename EmuMath::FastQuaternion<T_, RegisterWidth_>::register_arg_type rhs_scalar_register_
) -> EmuMath::FastQuaternion<T_, RegisterWidth_>&
{
	EmuMath::Helpers::fast_quaternion_multiply_assign_scalar(lhs_, rhs_scalar_register_);
	return lhs_;
}

template<typename T_, std::size_t RegisterWidth_, EmuConcepts::Arithmetic RhsScalar_>
[[nodiscard]] constexpr inline auto operator*=(EmuMath::FastQuaternion<T_, RegisterWidth_>& lhs_, RhsScalar_&& rhs_scalar_)
	-> EmuMath::FastQuaternion<T_, RegisterWidth_>&
{
	EmuMath::Helpers::fast_quaternion_multiply_assign_scalar(lhs_, std::forward<RhsScalar_>(rhs_scalar_));
	return lhs_;
}

template<typename T_, std::size_t RegisterWidth_>
[[nodiscard]] constexpr inline auto operator*=
(
	EmuMath::FastQuaternion<T_, RegisterWidth_>& lhs_,
	const EmuMath::FastQuaternion<T_, RegisterWidth_>& rhs_
) -> EmuMath::FastQuaternion<T_, RegisterWidth_>&
{
	EmuMath::Helpers::fast_quaternion_multiply_assign_quaternion(lhs_, rhs_);
	return lhs_;
}
#pragma endregion

#pragma region DIVIDE_ASSIGN_OPERATORS
template<typename T_, std::size_t RegisterWidth_>
[[nodiscard]] constexpr inline auto operator/=
(
	EmuMath::FastQuaternion<T_, RegisterWidth_>& lhs_,
	typename EmuMath::FastQuaternion<T_, RegisterWidth_>::register_arg_type rhs_scalar_register_
) -> EmuMath::FastQuaternion<T_, RegisterWidth_>&
{
	EmuMath::Helpers::fast_quaternion_divide_assign(lhs_, rhs_scalar_register_);
	return lhs_;
}

template<typename T_, std::size_t RegisterWidth_, EmuConcepts::Arithmetic RhsScalar_>
[[nodiscard]] constexpr inline auto operator/=(EmuMath::FastQuaternion<T_, RegisterWidth_>& lhs_, RhsScalar_&& rhs_scalar_)
	-> EmuMath::FastQuaternion<T_, RegisterWidth_>&
{
	EmuMath::Helpers::fast_quaternion_divide_assign(lhs_, std::forward<RhsScalar_>(rhs_scalar_));
	return lhs_;
}
#pragma endregion

#endif
