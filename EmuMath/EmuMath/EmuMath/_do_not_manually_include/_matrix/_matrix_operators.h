#ifndef EMU_MATH_MATRIX_OPERATORS_H_INC_
#define EMU_MATH_MATRIX_OPERATORS_H_INC_ 1

#include "_matrix_t.h"

namespace EmuMath::Helpers
{
	template<EmuConcepts::EmuMatrix LhsMatrix_, std::size_t RhsSize_>
	[[nodiscard]] static constexpr inline bool matrix_valid_vector_multiply_arg_size()
	{
		constexpr std::size_t num_rows = std::remove_cvref_t<LhsMatrix_>::num_rows;
		return RhsSize_ == num_rows || (RhsSize_ == (num_rows - 1));
	}

	template<EmuConcepts::EmuMatrix LhsMatrix_, std::size_t RhsNumColumns_, std::size_t RhsNumRows_>
	[[nodiscard]] static constexpr inline bool matrix_valid_matrix_multiply_arg_size()
	{
		constexpr std::size_t num_columns = std::remove_cvref_t<LhsMatrix_>::num_columns;
		return num_columns == RhsNumRows_;
	}

	template<EmuConcepts::EmuMatrix LhsMatrix_, std::size_t RhsNumColumns_, std::size_t RhsNumRows_>
	[[nodiscard]] static constexpr inline bool matrix_valid_matrix_multiply_assign_arg_size()
	{
		constexpr std::size_t num_columns = std::remove_cvref_t<LhsMatrix_>::num_columns;
		constexpr std::size_t num_rows = std::remove_cvref_t<LhsMatrix_>::num_rows;
		return (num_columns == RhsNumRows_) && (num_columns == num_rows) && (RhsNumColumns_ == RhsNumRows_);
	}
}

#pragma region CONST_ARITHMETIC
// BASIC ARITHMETIC OPERATOR+
template<std::size_t LhsNumColumns_, std::size_t LhsNumRows_, typename LhsT_, bool LhsColumnMajor_, class Rhs_>
[[nodiscard]] constexpr inline auto operator+(const EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>& lhs_matrix_, Rhs_&& rhs_)
	-> EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, typename EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>::value_type_uq, LhsColumnMajor_>
{
	return EmuMath::Helpers::matrix_add<LhsNumColumns_, LhsNumRows_, typename EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>::value_type_uq, LhsColumnMajor_>
	(
		lhs_matrix_,
		std::forward<Rhs_>(rhs_)
	);
}

// BASIC ARITHMETIC OPERATOR-
template<std::size_t LhsNumColumns_, std::size_t LhsNumRows_, typename LhsT_, bool LhsColumnMajor_, class Rhs_>
[[nodiscard]] constexpr inline auto operator-(const EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>& lhs_matrix_, Rhs_&& rhs_)
	-> EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, typename EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>::value_type_uq, LhsColumnMajor_>
{
	return EmuMath::Helpers::matrix_subtract<LhsNumColumns_, LhsNumRows_, typename EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>::value_type_uq, LhsColumnMajor_>
	(
		lhs_matrix_,
		std::forward<Rhs_>(rhs_)
	);
}

// BASIC ARITHMETIC OPERATOR/
template<std::size_t LhsNumColumns_, std::size_t LhsNumRows_, typename LhsT_, bool LhsColumnMajor_, class Rhs_>
[[nodiscard]] constexpr inline auto operator/(const EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>& lhs_matrix_, Rhs_&& rhs_)
	-> EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, typename EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>::value_type_uq, LhsColumnMajor_>
{
	return EmuMath::Helpers::matrix_divide<LhsNumColumns_, LhsNumRows_, typename EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>::value_type_uq, LhsColumnMajor_>
	(
		lhs_matrix_,
		std::forward<Rhs_>(rhs_)
	);
}

// BASIC ARITHMETIC OPERATOR%
template<std::size_t LhsNumColumns_, std::size_t LhsNumRows_, typename LhsT_, bool LhsColumnMajor_, class Rhs_>
[[nodiscard]] constexpr inline auto operator%(const EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>& lhs_matrix_, Rhs_&& rhs_)
	-> EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, typename EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>::value_type_uq, LhsColumnMajor_>
{
	return EmuMath::Helpers::matrix_mod<LhsNumColumns_, LhsNumRows_, typename EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>::value_type_uq, LhsColumnMajor_>
	(
		lhs_matrix_,
		std::forward<Rhs_>(rhs_)
	);
}

// ADAPTIVE ARITHMETIC OPERATOR* : UNSPECIALISED, FALLBACK TO BASIC MULTIPLICATION
template<std::size_t LhsNumColumns_, std::size_t LhsNumRows_, typename LhsT_, bool LhsColumnMajor_, class Rhs_>
requires(!EmuMath::TMP::is_specialised_matrix_multiply_arg<Rhs_>())
[[nodiscard]] constexpr inline auto operator*(const EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>& lhs_matrix_, Rhs_&& rhs_)
	-> EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, typename EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>::value_type_uq, LhsColumnMajor_>
{
	return EmuMath::Helpers::matrix_multiply_basic<LhsNumColumns_, LhsNumRows_, typename EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>::value_type_uq, LhsColumnMajor_>
	(
		lhs_matrix_,
		std::forward<Rhs_>(rhs_)
	);
}

// ADAPTIVE ARITHMETIC OPERATOR*: SPECIALISED VECTOR MULTIPLY
template<std::size_t LhsNumColumns_, std::size_t LhsNumRows_, typename LhsT_, bool LhsColumnMajor_, std::size_t RhsSize_, typename RhsT_>
requires(EmuMath::Helpers::matrix_valid_vector_multiply_arg_size<EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>, RhsSize_>())
[[nodiscard]] constexpr inline auto operator*(const EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>& lhs_matrix_, const EmuMath::Vector<RhsSize_, RhsT_>& rhs_vector_)
	-> EmuMath::Vector<RhsSize_, typename EmuMath::Vector<RhsSize_, RhsT_>::preferred_floating_point>
{
	return EmuMath::Helpers::matrix_multiply<typename EmuMath::Vector<RhsSize_, RhsT_>::preferred_floating_point, LhsColumnMajor_>
	(
		lhs_matrix_,
		rhs_vector_
	);
}

// ADAPTIVE ARITHMETIC OPERATOR*: SPECIALISED MATRIX MULTIPLY
template<std::size_t LhsNumColumns_, std::size_t LhsNumRows_, typename LhsT_, bool LhsColumnMajor_, std::size_t RhsNumColumns_, std::size_t RhsNumRows_, typename RhsT_, bool RhsColumnMajor_>
requires(EmuMath::Helpers::matrix_valid_matrix_multiply_arg_size<EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>, RhsNumColumns_, RhsNumRows_>())
[[nodiscard]] constexpr inline auto operator*
(
	const EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>& lhs_matrix_,
	const EmuMath::Matrix<RhsNumColumns_, RhsNumRows_, RhsT_, RhsColumnMajor_>& rhs_matrix_
) -> EmuMath::Matrix<RhsNumColumns_, RhsNumRows_, typename EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>::preferred_floating_point, LhsColumnMajor_>
{
	return EmuMath::Helpers::matrix_multiply<typename EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>::preferred_floating_point, LhsColumnMajor_>
	(
		lhs_matrix_,
		rhs_matrix_
	);
}
#pragma endregion

#pragma region ARITHMETIC_ASSIGN_OPERATORS
// BASIC ARITHMETIC OPERATOR+=
template<std::size_t LhsNumColumns_, std::size_t LhsNumRows_, typename LhsT_, bool LhsColumnMajor_, class Rhs_>
[[nodiscard]] constexpr inline auto operator+=(EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>& lhs_matrix_, Rhs_&& rhs_)
	-> EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>&
{
	EmuMath::Helpers::matrix_add_assign<LhsColumnMajor_>
	(
		lhs_matrix_,
		std::forward<Rhs_>(rhs_)
	);
	return lhs_matrix_;
}

// BASIC ARITHMETIC OPERATOR-=
template<std::size_t LhsNumColumns_, std::size_t LhsNumRows_, typename LhsT_, bool LhsColumnMajor_, class Rhs_>
[[nodiscard]] constexpr inline auto operator-=(EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>& lhs_matrix_, Rhs_&& rhs_)
	-> EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>&
{
	EmuMath::Helpers::matrix_subtract_assign<LhsColumnMajor_>
	(
		lhs_matrix_,
		std::forward<Rhs_>(rhs_)
	);
	return lhs_matrix_;
}

// BASIC ARITHMETIC OPERATOR+=
template<std::size_t LhsNumColumns_, std::size_t LhsNumRows_, typename LhsT_, bool LhsColumnMajor_, class Rhs_>
[[nodiscard]] constexpr inline auto operator/=(EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>& lhs_matrix_, Rhs_&& rhs_)
	-> EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>&
{
	EmuMath::Helpers::matrix_divide_assign<LhsColumnMajor_>
	(
		lhs_matrix_,
		std::forward<Rhs_>(rhs_)
	);
	return lhs_matrix_;
}

// BASIC ARITHMETIC OPERATOR%=
template<std::size_t LhsNumColumns_, std::size_t LhsNumRows_, typename LhsT_, bool LhsColumnMajor_, class Rhs_>
[[nodiscard]] constexpr inline auto operator%=(EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>& lhs_matrix_, Rhs_&& rhs_)
	-> EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>&
{
	EmuMath::Helpers::matrix_mod_assign<LhsColumnMajor_>
	(
		lhs_matrix_,
		std::forward<Rhs_>(rhs_)
	);
	return lhs_matrix_;
}

// ADAPTIVE ARITHMETIC OPERATOR*= : UNSPECIALISED, FALLBACK TO BASIC MULTIPLICATION
template<std::size_t LhsNumColumns_, std::size_t LhsNumRows_, typename LhsT_, bool LhsColumnMajor_, class Rhs_>
requires(!EmuMath::TMP::is_specialised_matrix_multiply_arg<Rhs_>())
[[nodiscard]] constexpr inline auto operator*=(EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>& lhs_matrix_, Rhs_&& rhs_)
	-> EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>&
{
	return EmuMath::Helpers::matrix_multiply_basic_assign<LhsColumnMajor_>
	(
		lhs_matrix_,
		std::forward<Rhs_>(rhs_)
	);
}

// ADAPTIVE ARITHMETIC OPERATOR*=: SPECIALISED VECTOR MULTIPLY
template<std::size_t LhsNumColumns_, std::size_t LhsNumRows_, typename LhsT_, bool LhsColumnMajor_, std::size_t RhsSize_, typename RhsT_>
requires(EmuMath::Helpers::matrix_valid_vector_multiply_arg_size<EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>, RhsSize_>())
[[nodiscard]] constexpr inline auto operator*=(const EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>& lhs_matrix_, EmuMath::Vector<RhsSize_, RhsT_>& rhs_vector_)
	-> EmuMath::Vector<RhsSize_, RhsT_>&
{
	return EmuMath::Helpers::matrix_multiply_assign<LhsColumnMajor_>
	(
		lhs_matrix_,
		rhs_vector_
	);
}

// ADAPTIVE ARITHMETIC OPERATOR*: SPECIALISED MATRIX MULTIPLY
template<std::size_t LhsNumColumns_, std::size_t LhsNumRows_, typename LhsT_, bool LhsColumnMajor_, std::size_t RhsNumColumns_, std::size_t RhsNumRows_, typename RhsT_, bool RhsColumnMajor_>
requires(EmuMath::Helpers::matrix_valid_matrix_multiply_assign_arg_size<EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>, RhsNumColumns_, RhsNumRows_>())
[[nodiscard]] constexpr inline auto operator*=
(
	EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>& lhs_matrix_,
	const EmuMath::Matrix<RhsNumColumns_, RhsNumRows_, RhsT_, RhsColumnMajor_>& rhs_matrix_
) -> EmuMath::Matrix<RhsNumColumns_, RhsNumRows_, LhsT_, LhsColumnMajor_>&
{
	return EmuMath::Helpers::matrix_multiply_assign<LhsColumnMajor_>
	(
		lhs_matrix_,
		rhs_matrix_
	);
}
#pragma endregion

// TODO
#if 0
#pragma region CONST_BITWISE
template<std::size_t LhsNumColumns_, std::size_t LhsNumRows_, typename LhsT_, bool LhsColumnMajor_, class Rhs_>
[[nodiscard]] constexpr inline auto operator&(const EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>& lhs_matrix_, Rhs_&& rhs_)
	-> EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, typename EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>::value_type_uq, LhsColumnMajor_>
{
	return EmuMath::Helpers::matrix_bitwise_and<LhsNumColumns_, LhsNumRows_, typename EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>::value_type_uq, LhsColumnMajor_>
	(
		lhs_matrix_,
		std::forward<Rhs_>(rhs_)
	);
}

template<std::size_t LhsNumColumns_, std::size_t LhsNumRows_, typename LhsT_, bool LhsColumnMajor_, class Rhs_>
[[nodiscard]] constexpr inline auto operator|(const EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>& lhs_matrix_, Rhs_&& rhs_)
	-> EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, typename EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>::value_type_uq, LhsColumnMajor_>
{
	return EmuMath::Helpers::matrix_bitwise_or<LhsNumColumns_, LhsNumRows_, typename EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>::value_type_uq, LhsColumnMajor_>
	(
		lhs_matrix_,
		std::forward<Rhs_>(rhs_)
	);
}

template<std::size_t LhsNumColumns_, std::size_t LhsNumRows_, typename LhsT_, bool LhsColumnMajor_, class Rhs_>
[[nodiscard]] constexpr inline auto operator^(const EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>& lhs_matrix_, Rhs_&& rhs_)
	-> EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, typename EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>::value_type_uq, LhsColumnMajor_>
{
	return EmuMath::Helpers::matrix_bitwise_xor<LhsNumColumns_, LhsNumRows_, typename EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>::value_type_uq, LhsColumnMajor_>
	(
		lhs_matrix_,
		std::forward<Rhs_>(rhs_)
	);
}

template<std::size_t LhsNumColumns_, std::size_t LhsNumRows_, typename LhsT_, bool LhsColumnMajor_, class Rhs_>
[[nodiscard]] constexpr inline auto operator<<(const EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>& lhs_matrix_, Rhs_&& rhs_)
	-> EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, typename EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>::value_type_uq, LhsColumnMajor_>
{
	return EmuMath::Helpers::matrix_shift_left<LhsNumColumns_, LhsNumRows_, typename EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>::value_type_uq, LhsColumnMajor_>
	(
		lhs_matrix_,
		std::forward<Rhs_>(rhs_)
	);
}


template<std::size_t LhsNumColumns_, std::size_t LhsNumRows_, typename LhsT_, bool LhsColumnMajor_, class Rhs_>
[[nodiscard]] constexpr inline auto operator>>(const EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>& lhs_matrix_, Rhs_&& rhs_)
	-> EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, typename EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>::value_type_uq, LhsColumnMajor_>
{
	return EmuMath::Helpers::matrix_shift_right<LhsNumColumns_, LhsNumRows_, typename EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>::value_type_uq, LhsColumnMajor_>
	(
		lhs_matrix_,
		std::forward<Rhs_>(rhs_)
	);
}

template<std::size_t LhsNumColumns_, std::size_t LhsNumRows_, typename LhsT_, bool LhsColumnMajor_, class Rhs_>
[[nodiscard]] constexpr inline auto operator~(const EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>& lhs_matrix_)
	-> EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, typename EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>::value_type_uq, LhsColumnMajor_>
{
	return EmuMath::Helpers::matrix_bitwise_not<LhsNumColumns_, LhsNumRows_, typename EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>::value_type_uq, LhsColumnMajor_>
	(
		lhs_matrix_,
		std::forward<Rhs_>(rhs_)
	);
}
#pragma endregion

#pragma region BITWISE_ASSIGN
template<std::size_t LhsNumColumns_, std::size_t LhsNumRows_, typename LhsT_, bool LhsColumnMajor_, class Rhs_>
[[nodiscard]] constexpr inline auto operator&=(EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>& lhs_matrix_, Rhs_&& rhs_)
	-> EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>&
{
	EmuMath::Helpers::matrix_bitwise_and_assign<LhsNumColumns_, LhsNumRows_, typename EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>::value_type_uq, LhsColumnMajor_>
	(
		lhs_matrix_,
		std::forward<Rhs_>(rhs_)
	);
	return lhs_matrix_;
}

template<std::size_t LhsNumColumns_, std::size_t LhsNumRows_, typename LhsT_, bool LhsColumnMajor_, class Rhs_>
[[nodiscard]] constexpr inline auto operator|=(EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>& lhs_matrix_, Rhs_&& rhs_)
	-> EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>&
{
	EmuMath::Helpers::matrix_bitwise_or_assign<LhsNumColumns_, LhsNumRows_, typename EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>::value_type_uq, LhsColumnMajor_>
	(
		lhs_matrix_,
		std::forward<Rhs_>(rhs_)
	);
	return lhs_matrix_;
}

template<std::size_t LhsNumColumns_, std::size_t LhsNumRows_, typename LhsT_, bool LhsColumnMajor_, class Rhs_>
[[nodiscard]] constexpr inline auto operator^=(EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>& lhs_matrix_, Rhs_&& rhs_)
	-> EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>&
{
	EmuMath::Helpers::matrix_bitwise_xor_assign<LhsNumColumns_, LhsNumRows_, typename EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>::value_type_uq, LhsColumnMajor_>
	(
		lhs_matrix_,
		std::forward<Rhs_>(rhs_)
	);
	return lhs_matrix_;
}

template<std::size_t LhsNumColumns_, std::size_t LhsNumRows_, typename LhsT_, bool LhsColumnMajor_, class Rhs_>
[[nodiscard]] constexpr inline auto operator<<=(EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>& lhs_matrix_, Rhs_&& rhs_)
	-> EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>&
{
	EmuMath::Helpers::matrix_shift_left_assign<LhsNumColumns_, LhsNumRows_, typename EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>::value_type_uq, LhsColumnMajor_>
	(
		lhs_matrix_,
		std::forward<Rhs_>(rhs_)
	);
	return lhs_matrix_;
}


template<std::size_t LhsNumColumns_, std::size_t LhsNumRows_, typename LhsT_, bool LhsColumnMajor_, class Rhs_>
[[nodiscard]] constexpr inline auto operator>>=(EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>& lhs_matrix_, Rhs_&& rhs_)
	-> EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>&
{
	EmuMath::Helpers::matrix_shift_right_assign<LhsNumColumns_, LhsNumRows_, typename EmuMath::Matrix<LhsNumColumns_, LhsNumRows_, LhsT_, LhsColumnMajor_>::value_type_uq, LhsColumnMajor_>
	(
		lhs_matrix_,
		std::forward<Rhs_>(rhs_)
	);
	return lhs_matrix_;
}
#pragma endregion
#endif

// TODO
#pragma region CMP_OPERATORS

#pragma endregion

#endif
