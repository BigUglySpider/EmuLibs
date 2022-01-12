#ifndef EMU_CORE_SAFE_ENUM_FUNCS_INC_H_
#define EMU_CORE_SAFE_ENUM_FUNCS_INC_H_ 1

#include <type_traits>

namespace EmuCore::TMP
{
#pragma region CONST_LHS
	/// <summary> Template function to easily cast a provided Enum to its underlying type. </summary>
	/// <param name="to_cast_">Enum value to cast to its underlying type.</param>
	/// <returns>Result of a static cast of the passed enum to_cast_ to its underlying type.</returns>
	template<class Enum_, typename = std::enable_if_t<std::is_enum_v<Enum_>>>
	[[nodiscard]] constexpr inline std::underlying_type_t<Enum_> underlying_cast(Enum_ to_cast_)
	{
		return static_cast<std::underlying_type_t<Enum_>>(to_cast_);
	}

	/// <summary> Template function to form a value of zero for a safe enum. </summary>
	/// <returns>The passed Enum_ type's underlying type at value 0, cast to the Enum_ type.</returns>
	template<class Enum_, typename = std::enable_if_t<std::is_enum_v<Enum_>>>
	[[nodiscard]] constexpr inline Enum_ safe_enum_zero()
	{
		using underlying_type = std::underlying_type_t<Enum_>;
		constexpr underlying_type underlying_zero = underlying_type(0);
		return static_cast<Enum_>(underlying_zero);
	}
	/// <summary> Shorthand to ensure safe_enum_zero with the same Enum_ argument is evaluated at compile-time. </summary>
	template<class Enum_, typename = std::enable_if_t<std::is_enum_v<Enum_>>>
	static constexpr Enum_ safe_enum_zero_v = safe_enum_zero<Enum_>();

	/// <summary> Template function to provide bitwise AND functionality to a safe enum type. </summary>
	/// <param name="lhs_">Enum appearing on the left of a bitwise AND operation.</param>
	/// <param name="rhs_">Enum appearing on the right of a bitwise AND operation.</param>
	/// <returns>Result of a bitwise AND of the two passed enums.</returns>
	template<class Enum_, typename = std::enable_if_t<std::is_enum_v<Enum_>>>
	[[nodiscard]] constexpr inline Enum_ safe_enum_and(Enum_ lhs_, Enum_ rhs_)
	{
		return static_cast<Enum_>(underlying_cast<Enum_>(lhs_) & underlying_cast<Enum_>(rhs_));
	}

	/// <summary> Template function to provide bitwise OR functionality to a safe enum type. </summary>
	/// <param name="lhs_">Enum appearing on the left of a bitwise OR operation.</param>
	/// <param name="rhs_">Enum appearing on the right of a bitwise OR operation.</param>
	/// <returns>Result of a bitwise OR of the two passed enums.</returns>
	template<class Enum_, typename = std::enable_if_t<std::is_enum_v<Enum_>>>
	[[nodiscard]] constexpr inline Enum_ safe_enum_or(Enum_ lhs_, Enum_ rhs_)
	{
		return static_cast<Enum_>(underlying_cast<Enum_>(lhs_) | underlying_cast<Enum_>(rhs_));
	}

	/// <summary> Template function to provide bitwise XOR functionality to a safe enum type. </summary>
	/// <param name="lhs_">Enum appearing on the left of a bitwise XOR operation.</param>
	/// <param name="rhs_">Enum appearing on the right of a bitwise XOR operation.</param>
	/// <returns>Result of a bitwise XOR of the two passed enums.</returns>
	template<class Enum_, typename = std::enable_if_t<std::is_enum_v<Enum_>>>
	[[nodiscard]] constexpr inline Enum_ safe_enum_xor(Enum_ lhs_, Enum_ rhs_)
	{
		return static_cast<Enum_>(underlying_cast<Enum_>(lhs_) ^ underlying_cast<Enum_>(rhs_));
	}

	/// <summary> Template function to provide bitwise left-shift functionality to a safe enum type. </summary>
	/// <param name="lhs_">Enum to perform the bitwise left-shift on.</param>
	/// <param name="num_shifts_">Number of bits to shift to the left.</param>
	/// <returns>Result of a bitwise left-shift of the passed lhs_ enum for num_shifts_ bits.</returns>
	template<class Enum_, typename = std::enable_if_t<std::is_enum_v<Enum_>>>
	[[nodiscard]] constexpr inline Enum_ safe_enum_left_shift(Enum_ lhs_, std::size_t num_shifts_)
	{
		return static_cast<Enum_>(underlying_cast<Enum_>(lhs_) << num_shifts_);
	}

	/// <summary> Template function to provide bitwise right-shift functionality to a safe enum type. </summary>
	/// <param name="lhs_">Enum to perform the bitwise right-shift on.</param>
	/// <param name="num_shifts_">Number of bits to shift to the right.</param>
	/// <returns>Result of a bitwise right-shift of the passed lhs_ enum for num_shifts_ bits.</returns>
	template<class Enum_, typename = std::enable_if_t<std::is_enum_v<Enum_>>>
	[[nodiscard]] constexpr inline Enum_ safe_enum_right_shift(Enum_ lhs_, std::size_t num_shifts_)
	{
		return static_cast<Enum_>(underlying_cast<Enum_>(lhs_) >> num_shifts_);
	}

	/// <summary> Template function to provide bitwise NOT functionality to a safe enum type. </summary>
	/// <param name="to_invert_">Enum to perform the bitwise NOT on.</param>
	/// <returns>Result of a bitwise NOT of the passed to_invert_ enum.</returns>
	template<class Enum_, typename = std::enable_if_t<std::is_enum_v<Enum_>>>
	[[nodiscard]] constexpr inline Enum_ safe_enum_not(Enum_ to_invert_)
	{
		using underlying_type = std::underlying_type_t<Enum_>;
		return static_cast<Enum_>(~underlying_cast<Enum_>(to_invert_));
	}
#pragma endregion

#pragma region NON_CONST_LHS
	/// <summary> Template function to provide bitwise AND functionality to a safe enum type. </summary>
	/// <param name="lhs_">Enum reference appearing on the left of a bitwise AND operation, which the result will be stored to.</param>
	/// <param name="rhs_">Enum appearing on the right of a bitwise AND operation.</param>
	/// <returns>Reference to lhs_ after it is set to the result of a bitwise AND of the two passed enums.</returns>
	template<class Enum_, typename = std::enable_if_t<std::is_enum_v<Enum_>>>
	constexpr inline Enum_& safe_enum_and_equals(Enum_& lhs_, Enum_ rhs_)
	{
		return lhs_ = safe_enum_and<Enum_>(lhs_, rhs_);
	}

	/// <summary> Template function to provide bitwise OR functionality to a safe enum type. </summary>
	/// <param name="lhs_">Enum reference appearing on the left of a bitwise OR operation, which the result will be stored to.</param>
	/// <param name="rhs_">Enum appearing on the right of a bitwise OR operation.</param>
	/// <returns>Reference to lhs_ after it is set to the result of a bitwise OR of the two passed enums.</returns>
	template<class Enum_, typename = std::enable_if_t<std::is_enum_v<Enum_>>>
	constexpr inline Enum_& safe_enum_or_equals(Enum_& lhs_, Enum_ rhs_)
	{
		return lhs_ = safe_enum_or<Enum_>(lhs_, rhs_);
	}

	/// <summary> Template function to provide bitwise XOR functionality to a safe enum type. </summary>
	/// <param name="lhs_">Enum reference appearing on the left of a bitwise XOR operation, which the result will be stored to.</param>
	/// <param name="rhs_">Enum appearing on the right of a bitwise XOR operation.</param>
	/// <returns>Reference to lhs_ after it is set to the result of a bitwise XOR of the two passed enums.</returns>
	template<class Enum_, typename = std::enable_if_t<std::is_enum_v<Enum_>>>
	constexpr inline Enum_& safe_enum_xor_equals(Enum_& lhs_, Enum_ rhs_)
	{
		return lhs_ = safe_enum_xor<Enum_>(lhs_, rhs_);
	}

	/// <summary> Template function to provide bitwise left-shift functionality to a safe enum type. </summary>
	/// <param name="lhs_">Enum reference to perform the bitwise left-shift on, which the result will be stored to.</param>
	/// <param name="num_shifts_">Number of bits to shift to the left.</param>
	/// <returns>Reference to lhs_ after it is set to the result of a bitwise left-shift of the passed lhs_ enum for num_shifts_ bits.</returns>
	template<class Enum_, typename = std::enable_if_t<std::is_enum_v<Enum_>>>
	constexpr inline Enum_& safe_enum_left_shift_equals(Enum_& lhs_, Enum_ rhs_)
	{
		return lhs_ = safe_enum_left_shift<Enum_>(lhs_, rhs_);
	}

	/// <summary> Template function to provide bitwise right-shift functionality to a safe enum type. </summary>
	/// <param name="lhs_">Enum reference to perform the bitwise right-shift on, which the result will be stored to.</param>
	/// <param name="num_shifts_">Number of bits to shift to the right.</param>
	/// <returns>Reference to lhs_ after it is set to the result of a bitwise right-shift of the passed lhs_ enum for num_shifts_ bits.</returns>
	template<class Enum_, typename = std::enable_if_t<std::is_enum_v<Enum_>>>
	constexpr inline Enum_& safe_enum_right_shift_equals(Enum_& lhs_, Enum_ rhs_)
	{
		return lhs_ = safe_enum_right_shift<Enum_>(lhs_, rhs_);
	}
#pragma endregion
}

#endif
