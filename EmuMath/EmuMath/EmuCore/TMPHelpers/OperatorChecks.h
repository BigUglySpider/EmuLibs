#ifndef EMU_CORE_OPERATOR_CHECKS_H_INC_
#define EMU_CORE_OPERATOR_CHECKS_H_INC_ 1

#include <type_traits>
#include <utility>

namespace EmuCore::TMP
{
#pragma region EXISTENCE_CHECKS
	template<class Stream_, typename Arg_, typename = void>
	struct is_stream_appendable
	{
		static constexpr bool value = false;
	};

	template<class Stream_, typename Arg_>
	struct is_stream_appendable<Stream_, Arg_, std::void_t<decltype(std::declval<std::remove_reference_t<Stream_>&>() << std::declval<Arg_>())>>
	{
		static constexpr bool value = true;
	};

	template<class Stream_, typename Arg_>
	static constexpr bool is_stream_appendable_v = is_stream_appendable<Stream_, Arg_>::value;

	/// <summary> Struct that may be used to check if a type T_ has a subscript operator (operator[]) callable with the provided Arg_ type. </summary>
	template<class T_, typename Arg_, typename = void>
	struct has_subscript_operator
	{
		static constexpr bool value = false;
	};
	template<class T_, typename Arg_>
	struct has_subscript_operator<T_, Arg_, std::void_t<decltype(std::declval<T_>().operator[](std::declval<Arg_>()))>>
	{
		static constexpr bool value = true;
	};
	template<class T_, typename Arg_>
	static constexpr bool has_subscript_operator_v = has_subscript_operator<T_, Arg_>::value;

	/// <summary> Struct that may be used to check if a type T_ has a plus operator (operator+) callable with the provided Arg_ type. </summary>
	template<class T_, typename Arg_, typename = void>
	struct has_plus_operator
	{
		static constexpr bool value = false;
	};
	template<class T_, typename Arg_>
	struct has_plus_operator<T_, Arg_, std::void_t<decltype(std::declval<T_>() + std::declval<Arg_>())>>
	{
		static constexpr bool value = true;
	};
	template<class T_, typename Arg_>
	static constexpr bool has_plus_operator_v = has_plus_operator<T_, Arg_>::value;

	/// <summary> Struct that may be used to check if a type T_ has a plus-assign operator (operator+=) callable with the provided Arg_ type. </summary>
	template<class T_, typename Arg_, typename = void>
	struct has_plus_assign_operator
	{
		static constexpr bool value = false;
	};
	template<class T_, typename Arg_>
	struct has_plus_assign_operator<T_, Arg_, std::void_t<decltype(std::declval<T_>() += std::declval<Arg_>())>>
	{
		static constexpr bool value = true;
	};
	template<class T_, typename Arg_>
	static constexpr bool has_plus_assign_operator_v = has_plus_assign_operator<T_, Arg_>::value;

	/// <summary> Struct that may be used to check if a type T_ has a subtract operator (operator-) callable with the provided Arg_ type. </summary>
	template<class T_, typename Arg_, typename = void>
	struct has_subtract_operator
	{
		static constexpr bool value = false;
	};
	template<class T_, typename Arg_>
	struct has_subtract_operator<T_, Arg_, std::void_t<decltype(std::declval<T_>() - std::declval<Arg_>())>>
	{
		static constexpr bool value = true;
	};
	template<class T_, typename Arg_>
	static constexpr bool has_subtract_operator_v = has_subtract_operator<T_, Arg_>::value;

	/// <summary> Struct that may be used to check if a type T_ has a subtract-assign operator (operator-=) callable with the provided Arg_ type. </summary>
	template<class T_, typename Arg_, typename = void>
	struct has_subtract_assign_operator
	{
		static constexpr bool value = false;
	};
	template<class T_, typename Arg_>
	struct has_subtract_assign_operator<T_, Arg_, std::void_t<decltype(std::declval<T_>() -= std::declval<Arg_>())>>
	{
		static constexpr bool value = true;
	};
	template<class T_, typename Arg_>
	static constexpr bool has_subtract_assign_operator_v = has_subtract_assign_operator<T_, Arg_>::value;

	/// <summary> Struct that may be used to check if a type T_ has a multiply operator (operator*) callable with the provided Arg_ type. </summary>
	template<class T_, typename Arg_, typename = void>
	struct has_multiply_operator
	{
		static constexpr bool value = false;
	};
	template<class T_, typename Arg_>
	struct has_multiply_operator<T_, Arg_, std::void_t<decltype(std::declval<T_>() * std::declval<Arg_>())>>
	{
		static constexpr bool value = true;
	};
	template<class T_, typename Arg_>
	static constexpr bool has_multiply_operator_v = has_multiply_operator<T_, Arg_>::value;

	/// <summary> Struct that may be used to check if a type T_ has a multiply-assign operator (operator*=) callable with the provided Arg_ type. </summary>
	template<class T_, typename Arg_, typename = void>
	struct has_multiply_assign_operator
	{
		static constexpr bool value = false;
	};
	template<class T_, typename Arg_>
	struct has_multiply_assign_operator<T_, Arg_, std::void_t<decltype(std::declval<T_>() *= std::declval<Arg_>())>>
	{
		static constexpr bool value = true;
	};
	template<class T_, typename Arg_>
	static constexpr bool has_multiply_assign_operator_v = has_multiply_assign_operator<T_, Arg_>::value;

	/// <summary> Struct that may be used to check if a type T_ has a divide operator (operator/) callable with the provided Arg_ type. </summary>
	template<class T_, typename Arg_, typename = void>
	struct has_divide_operator
	{
		static constexpr bool value = false;
	};
	template<class T_, typename Arg_>
	struct has_divide_operator<T_, Arg_, std::void_t<decltype(std::declval<T_>() / std::declval<Arg_>())>>
	{
		static constexpr bool value = true;
	};
	template<class T_, typename Arg_>
	static constexpr bool has_divide_operator_v = has_divide_operator<T_, Arg_>::value;

	/// <summary> Struct that may be used to check if a type T_ has a divide-assign operator (operator/=) callable with the provided Arg_ type. </summary>
	template<class T_, typename Arg_, typename = void>
	struct has_divide_assign_operator
	{
		static constexpr bool value = false;
	};
	template<class T_, typename Arg_>
	struct has_divide_assign_operator<T_, Arg_, std::void_t<decltype(std::declval<T_>() /= std::declval<Arg_>())>>
	{
		static constexpr bool value = true;
	};
	template<class T_, typename Arg_>
	static constexpr bool has_divide_assign_operator_v = has_divide_assign_operator<T_, Arg_>::value;

	/// <summary> Struct that may be used to check if a type T_ has a modulo-divide operator (operator%) callable with the provided Arg_ type. </summary>
	template<class T_, typename Arg_, typename = void>
	struct has_mod_operator
	{
		static constexpr bool value = false;
	};
	template<class T_, typename Arg_>
	struct has_mod_operator<T_, Arg_, std::void_t<decltype(std::declval<T_>() % std::declval<Arg_>())>>
	{
		static constexpr bool value = true;
	};
	template<class T_, typename Arg_>
	static constexpr bool has_mod_operator_v = has_mod_operator<T_, Arg_>::value;

	/// <summary> Struct that may be used to check if a type T_ has a modulo-divide-assign operator (operator%=) callable with the provided Arg_ type. </summary>
	template<class T_, typename Arg_, typename = void>
	struct has_mod_assign_operator
	{
		static constexpr bool value = false;
	};
	template<class T_, typename Arg_>
	struct has_mod_assign_operator<T_, Arg_, std::void_t<decltype(std::declval<T_>() %= std::declval<Arg_>())>>
	{
		static constexpr bool value = true;
	};
	template<class T_, typename Arg_>
	static constexpr bool has_mod_assign_operator_v = has_mod_assign_operator<T_, Arg_>::value;

	/// <summary> Struct that may be used to check if a type T_ has a bitwise AND operator (operator&) callable with the provided Arg_ type. </summary>
	template<class T_, typename Arg_, typename = void>
	struct has_bitwise_and_operator
	{
		static constexpr bool value = false;
	};
	template<class T_, typename Arg_>
	struct has_bitwise_and_operator<T_, Arg_, std::void_t<decltype(std::declval<T_>() & std::declval<Arg_>())>>
	{
		static constexpr bool value = true;
	};
	template<class T_, typename Arg_>
	static constexpr bool has_bitwise_and_operator_v = has_bitwise_and_operator<T_, Arg_>::value;

	/// <summary> Struct that may be used to check if a type T_ has a bitwise AND-assign operator (operator&=) callable with the provided Arg_ type. </summary>
	template<class T_, typename Arg_, typename = void>
	struct has_bitwise_and_assign_operator
	{
		static constexpr bool value = false;
	};
	template<class T_, typename Arg_>
	struct has_bitwise_and_assign_operator<T_, Arg_, std::void_t<decltype(std::declval<T_>() &= std::declval<Arg_>())>>
	{
		static constexpr bool value = true;
	};
	template<class T_, typename Arg_>
	static constexpr bool has_bitwise_and_assign_operator_v = has_bitwise_and_assign_operator<T_, Arg_>::value;

	/// <summary> Struct that may be used to check if a type T_ has a bitwise OR operator (operator|) callable with the provided Arg_ type. </summary>
	template<class T_, typename Arg_, typename = void>
	struct has_bitwise_or_operator
	{
		static constexpr bool value = false;
	};
	template<class T_, typename Arg_>
	struct has_bitwise_or_operator<T_, Arg_, std::void_t<decltype(std::declval<T_>() | std::declval<Arg_>())>>
	{
		static constexpr bool value = true;
	};
	template<class T_, typename Arg_>
	static constexpr bool has_bitwise_or_operator_v = has_bitwise_or_operator<T_, Arg_>::value;

	/// <summary> Struct that may be used to check if a type T_ has a bitwise OR-assign operator (operator|=) callable with the provided Arg_ type. </summary>
	template<class T_, typename Arg_, typename = void>
	struct has_bitwise_or_assign_operator
	{
		static constexpr bool value = false;
	};
	template<class T_, typename Arg_>
	struct has_bitwise_or_assign_operator<T_, Arg_, std::void_t<decltype(std::declval<T_>() |= std::declval<Arg_>())>>
	{
		static constexpr bool value = true;
	};
	template<class T_, typename Arg_>
	static constexpr bool has_bitwise_or_assign_operator_v = has_bitwise_or_assign_operator<T_, Arg_>::value;

	/// <summary> Struct that may be used to check if a type T_ has a bitwise XOR operator (operator^) callable with the provided Arg_ type. </summary>
	template<class T_, typename Arg_, typename = void>
	struct has_bitwise_xor_operator
	{
		static constexpr bool value = false;
	};
	template<class T_, typename Arg_>
	struct has_bitwise_xor_operator<T_, Arg_, std::void_t<decltype(std::declval<T_>() ^ std::declval<Arg_>())>>
	{
		static constexpr bool value = true;
	};
	template<class T_, typename Arg_>
	static constexpr bool has_bitwise_xor_operator_v = has_bitwise_xor_operator<T_, Arg_>::value;

	/// <summary> Struct that may be used to check if a type T_ has a bitwise XOR-assign operator (operator^=) callable with the provided Arg_ type. </summary>
	template<class T_, typename Arg_, typename = void>
	struct has_bitwise_xor_assign_operator
	{
		static constexpr bool value = false;
	};
	template<class T_, typename Arg_>
	struct has_bitwise_xor_assign_operator<T_, Arg_, std::void_t<decltype(std::declval<T_>() ^= std::declval<Arg_>())>>
	{
		static constexpr bool value = true;
	};
	template<class T_, typename Arg_>
	static constexpr bool has_bitwise_xor_assign_operator_v = has_bitwise_xor_assign_operator<T_, Arg_>::value;

	/// <summary> Struct that may be used to check if a type T_ has a left-shift operator (operator<<) callable with the provided Arg_ type. </summary>
	template<class T_, typename Arg_, typename = void>
	struct has_left_shift_operator
	{
		static constexpr bool value = false;
	};
	template<class T_, typename Arg_>
	struct has_left_shift_operator<T_, Arg_, std::void_t<decltype(std::declval<T_>() << std::declval<Arg_>())>>
	{
		static constexpr bool value = true;
	};
	template<class T_, typename Arg_>
	static constexpr bool has_left_shift_operator_v = has_left_shift_operator<T_, Arg_>::value;

	/// <summary> Struct that may be used to check if a type T_ has a left-shift-assign operator (operator<<=) callable with the provided Arg_ type. </summary>
	template<class T_, typename Arg_, typename = void>
	struct has_left_shift_assign_operator
	{
		static constexpr bool value = false;
	};
	template<class T_, typename Arg_>
	struct has_left_shift_assign_operator<T_, Arg_, std::void_t<decltype(std::declval<T_>() <<= std::declval<Arg_>())>>
	{
		static constexpr bool value = true;
	};
	template<class T_, typename Arg_>
	static constexpr bool has_left_shift_assign_operator_v = has_left_shift_assign_operator<T_, Arg_>::value;

	/// <summary> Struct that may be used to check if a type T_ has a right-shift operator (operator>>) callable with the provided Arg_ type. </summary>
	template<class T_, typename Arg_, typename = void>
	struct has_right_shift_operator
	{
		static constexpr bool value = false;
	};
	template<class T_, typename Arg_>
	struct has_right_shift_operator<T_, Arg_, std::void_t<decltype(std::declval<T_>() >> std::declval<Arg_>())>>
	{
		static constexpr bool value = true;
	};
	template<class T_, typename Arg_>
	static constexpr bool has_right_shift_operator_v = has_right_shift_operator<T_, Arg_>::value;

	/// <summary> Struct that may be used to check if a type T_ has a right-shift-assign operator (operator>>=) callable with the provided Arg_ type. </summary>
	template<class T_, typename Arg_, typename = void>
	struct has_right_shift_assign_operator
	{
		static constexpr bool value = false;
	};
	template<class T_, typename Arg_>
	struct has_right_shift_assign_operator<T_, Arg_, std::void_t<decltype(std::declval<T_>() >>= std::declval<Arg_>())>>
	{
		static constexpr bool value = true;
	};
	template<class T_, typename Arg_>
	static constexpr bool has_right_shift_assign_operator_v = has_right_shift_assign_operator<T_, Arg_>::value;

	/// <summary> Struct that may be used to check if a type T_ has a logical AND operator (operator&&) callable with the provided Arg_ type. </summary>
	template<class T_, typename Arg_, typename = void>
	struct has_logical_and_operator
	{
		static constexpr bool value = false;
	};
	template<class T_, typename Arg_>
	struct has_logical_and_operator<T_, Arg_, std::void_t<decltype(std::declval<T_>() && std::declval<Arg_>())>>
	{
		static constexpr bool value = true;
	};
	template<class T_, typename Arg_>
	static constexpr bool has_logical_and_operator_v = has_logical_and_operator<T_, Arg_>::value;

	/// <summary> Struct that may be used to check if a type T_ has a logical OR operator (operator||) callable with the provided Arg_ type. </summary>
	template<class T_, typename Arg_, typename = void>
	struct has_logical_or_operator
	{
		static constexpr bool value = false;
	};
	template<class T_, typename Arg_>
	struct has_logical_or_operator<T_, Arg_, std::void_t<decltype(std::declval<T_>() || std::declval<Arg_>())>>
	{
		static constexpr bool value = true;
	};
	template<class T_, typename Arg_>
	static constexpr bool has_logical_or_operator_v = has_logical_or_operator<T_, Arg_>::value;

	/// <summary> Struct that may be used to check if a type T_ has an equal comparison operator (operator==) callable with the provided Arg_ type. </summary>
	template<class T_, typename Arg_, typename = void>
	struct has_cmp_equal_operator
	{
		static constexpr bool value = false;
	};
	template<class T_, typename Arg_>
	struct has_cmp_equal_operator<T_, Arg_, std::void_t<decltype(std::declval<T_>() == std::declval<Arg_>())>>
	{
		static constexpr bool value = true;
	};
	template<class T_, typename Arg_>
	static constexpr bool has_cmp_equal_operator_v = has_cmp_equal_operator<T_, Arg_>::value;

	/// <summary> Struct that may be used to check if a type T_ has a not-equal comparison operator (operator!=) callable with the provided Arg_ type. </summary>
	template<class T_, typename Arg_, typename = void>
	struct has_cmp_not_equal_operator
	{
		static constexpr bool value = false;
	};
	template<class T_, typename Arg_>
	struct has_cmp_not_equal_operator<T_, Arg_, std::void_t<decltype(std::declval<T_>() != std::declval<Arg_>())>>
	{
		static constexpr bool value = true;
	};
	template<class T_, typename Arg_>
	static constexpr bool has_cmp_not_equal_operator_v = has_cmp_not_equal_operator<T_, Arg_>::value;

	/// <summary> Struct that may be used to check if a type T_ has a greater-than comparison operator (operator>) callable with the provided Arg_ type. </summary>
	template<class T_, typename Arg_, typename = void>
	struct has_cmp_greater_operator
	{
		static constexpr bool value = false;
	};
	template<class T_, typename Arg_>
	struct has_cmp_greater_operator<T_, Arg_, std::void_t<decltype(std::declval<T_>() > std::declval<Arg_>())>>
	{
		static constexpr bool value = true;
	};
	template<class T_, typename Arg_>
	static constexpr bool has_cmp_greater_operator_v = has_cmp_greater_operator<T_, Arg_>::value;

	/// <summary> Struct that may be used to check if a type T_ has a less-than comparison operator (operator<) callable with the provided Arg_ type. </summary>
	template<class T_, typename Arg_, typename = void>
	struct has_cmp_less_operator
	{
		static constexpr bool value = false;
	};
	template<class T_, typename Arg_>
	struct has_cmp_less_operator<T_, Arg_, std::void_t<decltype(std::declval<T_>() < std::declval<Arg_>())>>
	{
		static constexpr bool value = true;
	};
	template<class T_, typename Arg_>
	static constexpr bool has_cmp_less_operator_v = has_cmp_less_operator<T_, Arg_>::value;

	/// <summary> Struct that may be used to check if a type T_ has a greater-equal comparison operator (operator>=) callable with the provided Arg_ type. </summary>
	template<class T_, typename Arg_, typename = void>
	struct has_cmp_greater_equal_operator
	{
		static constexpr bool value = false;
	};
	template<class T_, typename Arg_>
	struct has_cmp_greater_equal_operator<T_, Arg_, std::void_t<decltype(std::declval<T_>() >= std::declval<Arg_>())>>
	{
		static constexpr bool value = true;
	};
	template<class T_, typename Arg_>
	static constexpr bool has_cmp_greater_equal_operator_v = has_cmp_greater_equal_operator<T_, Arg_>::value;

	/// <summary> Struct that may be used to check if a type T_ has a less-equal comparison operator (operator<=) callable with the provided Arg_ type. </summary>
	template<class T_, typename Arg_, typename = void>
	struct has_cmp_less_equal_operator
	{
		static constexpr bool value = false;
	};
	template<class T_, typename Arg_>
	struct has_cmp_less_equal_operator<T_, Arg_, std::void_t<decltype(std::declval<T_>() <= std::declval<Arg_>())>>
	{
		static constexpr bool value = true;
	};
	template<class T_, typename Arg_>
	static constexpr bool has_cmp_less_equal_operator_v = has_cmp_less_equal_operator<T_, Arg_>::value;

#if (__cplusplus >= 201907L)
	/// <summary> Struct that may be used to check if a type T_ has a three-way comparison operator (operator<=>) callable with the provided Arg_ type. </summary>
	template<class T_, typename Arg_, typename = void>
	struct has_three_way_cmp_operator
	{
		static constexpr bool value = false;
	};
	template<class T_, typename Arg_>
	struct has_three_way_cmp_operator<T_, Arg_, std::void_t<decltype(std::declval<T_>() <=> std::declval<Arg_>())>>
	{
		static constexpr bool value = true;
	};
	template<class T_, typename Arg_>
	static constexpr bool has_three_way_cmp_operator_v = has_three_way_cmp_operator<T_, Arg_>::value;

	/// <summary> Struct that may be used to check if a type T_ has a three-way comparison (spaceship) operator (operator<=>) callable with the provided Arg_ type. </summary>
	template<class T_, typename Arg_>
	using has_spaceship_operator = has_three_way_cmp_operator<T_, Arg_>;
	template<class T_, typename Arg_>
	static constexpr bool has_spaceship_operator_v = has_three_way_cmp_operator_v<T_, Arg_>;
#endif // (__cplusplus >= 201907L) (NOTE: This can be a false-negative with MSVC compiling for C++20)

	/// <summary> Struct that may be used to check if a type T_ has a post-increment operator (operator++, called as `val++`). </summary>
	template<class T_, typename = void>
	struct has_post_increment_operator
	{
		static constexpr bool value = false;
	};
	template<class T_>
	struct has_post_increment_operator<T_, std::void_t<decltype((std::declval<T_>())++)>>
	{
		static constexpr bool value = true;
	};
	template<class T_>
	static constexpr bool has_post_increment_operator_v = has_post_increment_operator<T_>::value;

	/// <summary> Struct that may be used to check if a type T_ has a pre-increment operator (operator++, called as `++val`). </summary>
	template<class T_, typename = void>
	struct has_pre_increment_operator
	{
		static constexpr bool value = false;
	};
	template<class T_>
	struct has_pre_increment_operator<T_, std::void_t<decltype(++(std::declval<T_>()))>>
	{
		static constexpr bool value = true;
	};
	template<class T_>
	static constexpr bool has_pre_increment_operator_v = has_pre_increment_operator<T_>::value;

	/// <summary> Struct that may be used to check if a type T_ has a post-decrement operator (operator--, called as `val--`). </summary>
	template<class T_, typename = void>
	struct has_post_decrement_operator
	{
		static constexpr bool value = false;
	};
	template<class T_>
	struct has_post_decrement_operator<T_, std::void_t<decltype((std::declval<T_>())--)>>
	{
		static constexpr bool value = true;
	};
	template<class T_>
	static constexpr bool has_post_decrement_operator_v = has_post_decrement_operator<T_>::value;

	/// <summary> Struct that may be used to check if a type T_ has a pre-decrement operator (operator--, called as `--val`). </summary>
	template<class T_, typename = void>
	struct has_pre_decrement_operator
	{
		static constexpr bool value = false;
	};
	template<class T_>
	struct has_pre_decrement_operator<T_, std::void_t<decltype(--(std::declval<T_>()))>>
	{
		static constexpr bool value = true;
	};
	template<class T_>
	static constexpr bool has_pre_decrement_operator_v = has_pre_decrement_operator<T_>::value;

	/// <summary> Struct that may be used to check if a type T_ has a unary plus operator (operator+, called as `+val`). </summary>
	template<class T_, typename = void>
	struct has_unary_plus_operator
	{
		static constexpr bool value = false;
	};
	template<class T_>
	struct has_unary_plus_operator<T_, std::void_t<decltype(+(std::declval<T_>()))>>
	{
		static constexpr bool value = true;
	};
	template<class T_>
	static constexpr bool has_unary_plus_operator_v = has_unary_plus_operator<T_>::value;

	/// <summary> Struct that may be used to check if a type T_ has a unary minus operator (operator-, called as `-val`). </summary>
	template<class T_, typename = void>
	struct has_unary_minus_operator
	{
		static constexpr bool value = false;
	};
	template<class T_>
	struct has_unary_minus_operator<T_, std::void_t<decltype(-(std::declval<T_>()))>>
	{
		static constexpr bool value = true;
	};
	template<class T_>
	static constexpr bool has_unary_minus_operator_v = has_unary_minus_operator<T_>::value;

	/// <summary> Struct that may be used to check if a type T_ has a bitwise NOT operator (operator~). </summary>
	template<class T_, typename = void>
	struct has_bitwise_not_operator
	{
		static constexpr bool value = false;
	};
	template<class T_>
	struct has_bitwise_not_operator<T_, std::void_t<decltype(~(std::declval<T_>()))>>
	{
		static constexpr bool value = true;
	};
	template<class T_>
	static constexpr bool has_bitwise_not_operator_v = has_bitwise_not_operator<T_>::value;

	/// <summary> Struct that may be used to check if a type T_ has a logical NOT operator (operator!). </summary>
	template<class T_, typename = void>
	struct has_logical_not_operator
	{
		static constexpr bool value = false;
	};
	template<class T_>
	struct has_logical_not_operator<T_, std::void_t<decltype(!(std::declval<T_>()))>>
	{
		static constexpr bool value = true;
	};
	template<class T_>
	static constexpr bool has_logical_not_operator_v = has_logical_not_operator<T_>::value;

	template<class From_, class To_, typename = void>
	struct is_static_castable
	{
		static constexpr bool value = false;
	};
	template<class From_, class To_>
	struct is_static_castable<From_, To_, std::void_t<decltype(static_cast<To_>(std::declval<From_>()))>>
	{
		static constexpr bool value = true;
	};
	template<class From_, class To_>
	static constexpr bool is_static_castable_v = is_static_castable<From_, To_>::value;

	template<class From_, class To_, typename = void>
	struct is_c_style_castable
	{
		static constexpr bool value = false;
	};
	template<class From_, class To_>
	struct is_c_style_castable<From_, To_, std::void_t<decltype((To_)std::declval<From_>())>>
	{
		static constexpr bool value = true;
	};
	template<class From_, class To_>
	static constexpr bool is_c_style_castable_v = is_c_style_castable<From_, To_>::value;
#pragma endregion

#pragma region RESULT_CHECKS
	/// <summary>
	/// <para>
	///		Struct that may be used to determine the result of using the subscript operator (operator[]) with type T_,
	///		taking an argument of type Arg_.
	/// </para>
	/// <para> The type will be void if this operator does not exist, but this should not be used as an indicator; consider the `has_..._operator` types. </para>
	/// </summary>
	template<class T_, typename Arg_, bool Exists_ = EmuCore::TMP::has_subscript_operator_v<T_, Arg_>>
	struct subscript_operator_result
	{
		using type = void;
	};
	template<class T_, typename Arg_>
	struct subscript_operator_result<T_, Arg_, true>
	{
		using type = decltype(std::declval<T_>()[(std::declval<Arg_>())]);
	};
	template<class T_, typename Arg_>
	using subscript_operator_result_t = typename subscript_operator_result<T_, Arg_>::type;

	/// <summary>
	/// <para>
	///		Struct that may be used to determine the result of using the plus operator (operator+) with type T_,
	///		taking an argument of type Arg_.
	/// </para>
	/// <para> The type will be void if this operator does not exist, but this should not be used as an indicator; consider the `has_..._operator` types. </para>
	/// </summary>
	template<class T_, typename Arg_, bool Exists_ = EmuCore::TMP::has_plus_operator_v<T_, Arg_>>
	struct plus_operator_result
	{
		using type = void;
	};
	template<class T_, typename Arg_>
	struct plus_operator_result<T_, Arg_, true>
	{
		using type = decltype(std::declval<T_>() + std::declval<Arg_>());
	};
	template<class T_, typename Arg_>
	using plus_operator_result_t = typename plus_operator_result<T_, Arg_>::type;

	/// <summary>
	/// <para>
	///		Struct that may be used to determine the result of using the plus-assign operator (operator+=) with type T_,
	///		taking an argument of type Arg_.
	/// </para>
	/// <para> The type will be void if this operator does not exist, but this should not be used as an indicator; consider the `has_..._operator` types. </para>
	/// </summary>
	template<class T_, typename Arg_, bool Exists_ = EmuCore::TMP::has_plus_assign_operator_v<T_, Arg_>>
	struct plus_assign_operator_result
	{
		using type = void;
	};
	template<class T_, typename Arg_>
	struct plus_assign_operator_result<T_, Arg_, true>
	{
		using type = decltype(std::declval<T_>() += std::declval<Arg_>());
	};
	template<class T_, typename Arg_>
	using plus_assign_operator_result_t = typename plus_assign_operator_result<T_, Arg_>::type;

	/// <summary>
	/// <para>
	///		Struct that may be used to determine the result of using the subtract operator (operator-) with type T_,
	///		taking an argument of type Arg_.
	/// </para>
	/// <para> The type will be void if this operator does not exist, but this should not be used as an indicator; consider the `has_..._operator` types. </para>
	/// </summary>
	template<class T_, typename Arg_, bool Exists_ = EmuCore::TMP::has_subtract_operator_v<T_, Arg_>>
	struct subtract_operator_result
	{
		using type = void;
	};
	template<class T_, typename Arg_>
	struct subtract_operator_result<T_, Arg_, true>
	{
		using type = decltype(std::declval<T_>() - std::declval<Arg_>());
	};
	template<class T_, typename Arg_>
	using subtract_operator_result_t = typename subtract_operator_result<T_, Arg_>::type;

	/// <summary>
	/// <para>
	///		Struct that may be used to determine the result of using the subtract-assign operator (operator-=) with type T_,
	///		taking an argument of type Arg_.
	/// </para>
	/// <para> The type will be void if this operator does not exist, but this should not be used as an indicator; consider the `has_..._operator` types. </para>
	/// </summary>
	template<class T_, typename Arg_, bool Exists_ = EmuCore::TMP::has_subtract_assign_operator_v<T_, Arg_>>
	struct subtract_assign_operator_result
	{
		using type = void;
	};
	template<class T_, typename Arg_>
	struct subtract_assign_operator_result<T_, Arg_, true>
	{
		using type = decltype(std::declval<T_>() -= std::declval<Arg_>());
	};
	template<class T_, typename Arg_>
	using subtract_assign_operator_result_t = typename subtract_assign_operator_result<T_, Arg_>::type;

	/// <summary>
	/// <para>
	///		Struct that may be used to determine the result of using the multiply operator (operator*) with type T_,
	///		taking an argument of type Arg_.
	/// </para>
	/// <para> The type will be void if this operator does not exist, but this should not be used as an indicator; consider the `has_..._operator` types. </para>
	/// </summary>
	template<class T_, typename Arg_, bool Exists_ = EmuCore::TMP::has_multiply_operator_v<T_, Arg_>>
	struct multiply_operator_result
	{
		using type = void;
	};
	template<class T_, typename Arg_>
	struct multiply_operator_result<T_, Arg_, true>
	{
		using type = decltype(std::declval<T_>()* std::declval<Arg_>());
	};
	template<class T_, typename Arg_>
	using multiply_operator_result_t = typename multiply_operator_result<T_, Arg_>::type;

	/// <summary>
	/// <para>
	///		Struct that may be used to determine the result of using the multiply-assign operator (operator*=) with type T_,
	///		taking an argument of type Arg_.
	/// </para>
	/// <para> The type will be void if this operator does not exist, but this should not be used as an indicator; consider the `has_..._operator` types. </para>
	/// </summary>
	template<class T_, typename Arg_, bool Exists_ = EmuCore::TMP::has_multiply_assign_operator_v<T_, Arg_>>
	struct multiply_assign_operator_result
	{
		using type = void;
	};
	template<class T_, typename Arg_>
	struct multiply_assign_operator_result<T_, Arg_, true>
	{
		using type = decltype(std::declval<T_>() *= std::declval<Arg_>());
	};
	template<class T_, typename Arg_>
	using multiply_assign_operator_result_t = typename multiply_assign_operator_result<T_, Arg_>::type;

	/// <summary>
	/// <para>
	///		Struct that may be used to determine the result of using the divide operator (operator/) with type T_,
	///		taking an argument of type Arg_.
	/// </para>
	/// <para> The type will be void if this operator does not exist, but this should not be used as an indicator; consider the `has_..._operator` types. </para>
	/// </summary>
	template<class T_, typename Arg_, bool Exists_ = EmuCore::TMP::has_divide_operator_v<T_, Arg_>>
	struct divide_operator_result
	{
		using type = void;
	};
	template<class T_, typename Arg_>
	struct divide_operator_result<T_, Arg_, true>
	{
		using type = decltype(std::declval<T_>() / std::declval<Arg_>());
	};
	template<class T_, typename Arg_>
	using divide_operator_result_t = typename divide_operator_result<T_, Arg_>::type;

	/// <summary>
	/// <para>
	///		Struct that may be used to determine the result of using the divide-assign operator (operator/=) with type T_,
	///		taking an argument of type Arg_.
	/// </para>
	/// <para> The type will be void if this operator does not exist, but this should not be used as an indicator; consider the `has_..._operator` types. </para>
	/// </summary>
	template<class T_, typename Arg_, bool Exists_ = EmuCore::TMP::has_divide_assign_operator_v<T_, Arg_>>
	struct divide_assign_operator_result
	{
		using type = void;
	};
	template<class T_, typename Arg_>
	struct divide_assign_operator_result<T_, Arg_, true>
	{
		using type = decltype(std::declval<T_>() /= std::declval<Arg_>());
	};
	template<class T_, typename Arg_>
	using divide_assign_operator_result_t = typename divide_operator_result<T_, Arg_>::type;

	/// <summary>
	/// <para>
	///		Struct that may be used to determine the result of using the modulo-divide operator (operator%) with type T_,
	///		taking an argument of type Arg_.
	/// </para>
	/// <para> The type will be void if this operator does not exist, but this should not be used as an indicator; consider the `has_..._operator` types. </para>
	/// </summary>
	template<class T_, typename Arg_, bool Exists_ = EmuCore::TMP::has_mod_operator_v<T_, Arg_>>
	struct mod_operator_result
	{
		using type = void;
	};
	template<class T_, typename Arg_>
	struct mod_operator_result<T_, Arg_, true>
	{
		using type = decltype(std::declval<T_>() % std::declval<Arg_>());
	};
	template<class T_, typename Arg_>
	using mod_operator_result_t = typename mod_operator_result<T_, Arg_>::type;

	/// <summary>
	/// <para>
	///		Struct that may be used to determine the result of using the modulo-divide-assign operator (operator%=) with type T_,
	///		taking an argument of type Arg_.
	/// </para>
	/// <para> The type will be void if this operator does not exist, but this should not be used as an indicator; consider the `has_..._operator` types. </para>
	/// </summary>
	template<class T_, typename Arg_, bool Exists_ = EmuCore::TMP::has_mod_assign_operator_v<T_, Arg_>>
	struct mod_assign_operator_result
	{
		using type = void;
	};
	template<class T_, typename Arg_>
	struct mod_assign_operator_result<T_, Arg_, true>
	{
		using type = decltype(std::declval<T_>() %= std::declval<Arg_>());
	};
	template<class T_, typename Arg_>
	using mod_assign_operator_result_t = typename mod_assign_operator_result<T_, Arg_>::type;

	/// <summary>
	/// <para>
	///		Struct that may be used to determine the result of using the bitwise AND operator (operator&) with type T_,
	///		taking an argument of type Arg_.
	/// </para>
	/// <para> The type will be void if this operator does not exist, but this should not be used as an indicator; consider the `has_..._operator` types. </para>
	/// </summary>
	template<class T_, typename Arg_, bool Exists_ = EmuCore::TMP::has_bitwise_and_operator_v<T_, Arg_>>
	struct bitwise_and_operator_result
	{
		using type = void;
	};
	template<class T_, typename Arg_>
	struct bitwise_and_operator_result<T_, Arg_, true>
	{
		using type = decltype(std::declval<T_>()& std::declval<Arg_>());
	};
	template<class T_, typename Arg_>
	using bitwise_and_operator_result_t = typename bitwise_and_operator_result<T_, Arg_>::type;

	/// <summary>
	/// <para>
	///		Struct that may be used to determine the result of using the bitwise AND-assign operator (operator&=) with type T_,
	///		taking an argument of type Arg_.
	/// </para>
	/// <para> The type will be void if this operator does not exist, but this should not be used as an indicator; consider the `has_..._operator` types. </para>
	/// </summary>
	template<class T_, typename Arg_, bool Exists_ = EmuCore::TMP::has_bitwise_and_assign_operator_v<T_, Arg_>>
	struct bitwise_and_assign_operator_result
	{
		using type = void;
	};
	template<class T_, typename Arg_>
	struct bitwise_and_assign_operator_result<T_, Arg_, true>
	{
		using type = decltype(std::declval<T_>() &= std::declval<Arg_>());
	};
	template<class T_, typename Arg_>
	using bitwise_and_assign_operator_result_t = typename bitwise_and_assign_operator_result<T_, Arg_>::type;

	/// <summary>
	/// <para>
	///		Struct that may be used to determine the result of using the bitwise OR operator (operator|) with type T_,
	///		taking an argument of type Arg_.
	/// </para>
	/// <para> The type will be void if this operator does not exist, but this should not be used as an indicator; consider the `has_..._operator` types. </para>
	/// </summary>
	template<class T_, typename Arg_, bool Exists_ = EmuCore::TMP::has_bitwise_or_operator_v<T_, Arg_>>
	struct bitwise_or_operator_result
	{
		using type = void;
	};
	template<class T_, typename Arg_>
	struct bitwise_or_operator_result<T_, Arg_, true>
	{
		using type = decltype(std::declval<T_>() | std::declval<Arg_>());
	};
	template<class T_, typename Arg_>
	using bitwise_or_operator_result_t = typename bitwise_or_operator_result<T_, Arg_>::type;

	/// <summary>
	/// <para>
	///		Struct that may be used to determine the result of using the bitwise OR-assign operator (operator|) with type T_,
	///		taking an argument of type Arg_.
	/// </para>
	/// <para> The type will be void if this operator does not exist, but this should not be used as an indicator; consider the `has_..._operator` types. </para>
	/// </summary>
	template<class T_, typename Arg_, bool Exists_ = EmuCore::TMP::has_bitwise_or_assign_operator_v<T_, Arg_>>
	struct bitwise_or_assign_operator_result
	{
		using type = void;
	};
	template<class T_, typename Arg_>
	struct bitwise_or_assign_operator_result<T_, Arg_, true>
	{
		using type = decltype(std::declval<T_>() |= std::declval<Arg_>());
	};
	template<class T_, typename Arg_>
	using bitwise_or_assign_operator_result_t = typename bitwise_or_assign_operator_result<T_, Arg_>::type;

	/// <summary>
	/// <para>
	///		Struct that may be used to determine the result of using the bitwise XOR operator (operator^) with type T_,
	///		taking an argument of type Arg_.
	/// </para>
	/// <para> The type will be void if this operator does not exist, but this should not be used as an indicator; consider the `has_..._operator` types. </para>
	/// </summary>
	template<class T_, typename Arg_, bool Exists_ = EmuCore::TMP::has_bitwise_xor_operator_v<T_, Arg_>>
	struct bitwise_xor_operator_result
	{
		using type = void;
	};
	template<class T_, typename Arg_>
	struct bitwise_xor_operator_result<T_, Arg_, true>
	{
		using type = decltype(std::declval<T_>() ^ std::declval<Arg_>());
	};
	template<class T_, typename Arg_>
	using bitwise_xor_operator_result_t = typename bitwise_xor_operator_result<T_, Arg_>::type;

	/// <summary>
	/// <para>
	///		Struct that may be used to determine the result of using the bitwise XOR-assign operator (operator^=) with type T_,
	///		taking an argument of type Arg_.
	/// </para>
	/// <para> The type will be void if this operator does not exist, but this should not be used as an indicator; consider the `has_..._operator` types. </para>
	/// </summary>
	template<class T_, typename Arg_, bool Exists_ = EmuCore::TMP::has_bitwise_xor_assign_operator_v<T_, Arg_>>
	struct bitwise_xor_assign_operator_result
	{
		using type = void;
	};
	template<class T_, typename Arg_>
	struct bitwise_xor_assign_operator_result<T_, Arg_, true>
	{
		using type = decltype(std::declval<T_>() ^= std::declval<Arg_>());
	};
	template<class T_, typename Arg_>
	using bitwise_xor_assign_operator_result_t = typename bitwise_xor_assign_operator_result<T_, Arg_>::type;

	/// <summary>
	/// <para>
	///		Struct that may be used to determine the result of using the left-shift operator (operator&lt;&lt;) with type T_,
	///		taking an argument of type Arg_.
	/// </para>
	/// <para> The type will be void if this operator does not exist, but this should not be used as an indicator; consider the `has_..._operator` types. </para>
	/// </summary>
	template<class T_, typename Arg_, bool Exists_ = EmuCore::TMP::has_left_shift_operator_v<T_, Arg_>>
	struct left_shift_operator_result
	{
		using type = void;
	};
	template<class T_, typename Arg_>
	struct left_shift_operator_result<T_, Arg_, true>
	{
		using type = decltype(std::declval<T_>() << std::declval<Arg_>());
	};
	template<class T_, typename Arg_>
	using left_shift_operator_result_t = typename left_shift_operator_result<T_, Arg_>::type;

	/// <summary>
	/// <para>
	///		Struct that may be used to determine the result of using the left-shift-assign operator (operator&lt;&lt;=) with type T_,
	///		taking an argument of type Arg_.
	/// </para>
	/// <para> The type will be void if this operator does not exist, but this should not be used as an indicator; consider the `has_..._operator` types. </para>
	/// </summary>
	template<class T_, typename Arg_, bool Exists_ = EmuCore::TMP::has_left_shift_assign_operator_v<T_, Arg_>>
	struct left_shift_assign_operator_result
	{
		using type = void;
	};
	template<class T_, typename Arg_>
	struct left_shift_assign_operator_result<T_, Arg_, true>
	{
		using type = decltype(std::declval<T_>() <<= std::declval<Arg_>());
	};
	template<class T_, typename Arg_>
	using left_shift_assign_operator_result_t = typename left_shift_assign_operator_result<T_, Arg_>::type;

	/// <summary>
	/// <para>
	///		Struct that may be used to determine the result of using the right-shift operator (operator>>) with type T_,
	///		taking an argument of type Arg_.
	/// </para>
	/// <para> The type will be void if this operator does not exist, but this should not be used as an indicator; consider the `has_..._operator` types. </para>
	/// </summary>
	template<class T_, typename Arg_, bool Exists_ = EmuCore::TMP::has_right_shift_operator_v<T_, Arg_>>
	struct right_shift_operator_result
	{
		using type = void;
	};
	template<class T_, typename Arg_>
	struct right_shift_operator_result<T_, Arg_, true>
	{
		using type = decltype(std::declval<T_>() >> std::declval<Arg_>());
	};
	template<class T_, typename Arg_>
	using right_shift_operator_result_t = typename right_shift_operator_result<T_, Arg_>::type;

	/// <summary>
	/// <para>
	///		Struct that may be used to determine the result of using the right-shift-assign operator (operator>>=) with type T_,
	///		taking an argument of type Arg_.
	/// </para>
	/// <para> The type will be void if this operator does not exist, but this should not be used as an indicator; consider the `has_..._operator` types. </para>
	/// </summary>
	template<class T_, typename Arg_, bool Exists_ = EmuCore::TMP::has_right_shift_assign_operator_v<T_, Arg_>>
	struct right_shift_assign_operator_result
	{
		using type = void;
	};
	template<class T_, typename Arg_>
	struct right_shift_assign_operator_result<T_, Arg_, true>
	{
		using type = decltype(std::declval<T_>() >>= std::declval<Arg_>());
	};
	template<class T_, typename Arg_>
	using right_shift_assign_operator_result_t = typename right_shift_assign_operator_result<T_, Arg_>::type;

	/// <summary>
	/// <para>
	///		Struct that may be used to determine the result of using the logical AND operator (operator&&) with type T_,
	///		taking an argument of type Arg_.
	/// </para>
	/// <para> The type will be void if this operator does not exist, but this should not be used as an indicator; consider the `has_..._operator` types. </para>
	/// </summary>
	template<class T_, typename Arg_, bool Exists_ = EmuCore::TMP::has_logical_and_operator_v<T_, Arg_>>
	struct logical_and_operator_result
	{
		using type = void;
	};
	template<class T_, typename Arg_>
	struct logical_and_operator_result<T_, Arg_, true>
	{
		using type = decltype(std::declval<T_>() && std::declval<Arg_>());
	};
	template<class T_, typename Arg_>
	using logical_and_operator_result_t = typename logical_and_operator_result<T_, Arg_>::type;

	/// <summary>
	/// <para>
	///		Struct that may be used to determine the result of using the logical OR operator (operator||) with type T_,
	///		taking an argument of type Arg_.
	/// </para>
	/// <para> The type will be void if this operator does not exist, but this should not be used as an indicator; consider the `has_..._operator` types. </para>
	/// </summary>
	template<class T_, typename Arg_, bool Exists_ = EmuCore::TMP::has_logical_or_operator_v<T_, Arg_>>
	struct logical_or_operator_result
	{
		using type = void;
	};
	template<class T_, typename Arg_>
	struct logical_or_operator_result<T_, Arg_, true>
	{
		using type = decltype(std::declval<T_>() || std::declval<Arg_>());
	};
	template<class T_, typename Arg_>
	using logical_or_operator_result_t = typename logical_or_operator_result<T_, Arg_>::type;

	/// <summary>
	/// <para>
	///		Struct that may be used to determine the result of using the equal comparison operator (operator==) with type T_,
	///		taking an argument of type Arg_.
	/// </para>
	/// <para> The type will be void if this operator does not exist, but this should not be used as an indicator; consider the `has_..._operator` types. </para>
	/// </summary>
	template<class T_, typename Arg_, bool Exists_ = EmuCore::TMP::has_cmp_equal_operator_v<T_, Arg_>>
	struct cmp_equal_operator_result
	{
		using type = void;
	};
	template<class T_, typename Arg_>
	struct cmp_equal_operator_result<T_, Arg_, true>
	{
		using type = decltype(std::declval<T_>() == std::declval<Arg_>());
	};
	template<class T_, typename Arg_>
	using cmp_equal_operator_result_t = typename cmp_equal_operator_result<T_, Arg_>::type;

	/// <summary>
	/// <para>
	///		Struct that may be used to determine the result of using the not-equal comparison operator (operator!=) with type T_,
	///		taking an argument of type Arg_.
	/// </para>
	/// <para> The type will be void if this operator does not exist, but this should not be used as an indicator; consider the `has_..._operator` types. </para>
	/// </summary>
	template<class T_, typename Arg_, bool Exists_ = EmuCore::TMP::has_cmp_not_equal_operator_v<T_, Arg_>>
	struct cmp_not_equal_operator_result
	{
		using type = void;
	};
	template<class T_, typename Arg_>
	struct cmp_not_equal_operator_result<T_, Arg_, true>
	{
		using type = decltype(std::declval<T_>() != std::declval<Arg_>());
	};
	template<class T_, typename Arg_>
	using cmp_not_equal_operator_result_t = typename cmp_not_equal_operator_result<T_, Arg_>::type;

	/// <summary>
	/// <para>
	///		Struct that may be used to determine the result of using the greater comparison operator (operator&gt;) with type T_,
	///		taking an argument of type Arg_.
	/// </para>
	/// <para> The type will be void if this operator does not exist, but this should not be used as an indicator; consider the `has_..._operator` types. </para>
	/// </summary>
	template<class T_, typename Arg_, bool Exists_ = EmuCore::TMP::has_cmp_greater_operator_v<T_, Arg_>>
	struct cmp_greater_operator_result
	{
		using type = void;
	};
	template<class T_, typename Arg_>
	struct cmp_greater_operator_result<T_, Arg_, true>
	{
		using type = decltype(std::declval<T_>() > std::declval<Arg_>());
	};
	template<class T_, typename Arg_>
	using cmp_greater_operator_result_t = typename cmp_greater_operator_result<T_, Arg_>::type;

	/// <summary>
	/// <para>
	///		Struct that may be used to determine the result of using the less comparison operator (operator&lt;) with type T_,
	///		taking an argument of type Arg_.
	/// </para>
	/// <para> The type will be void if this operator does not exist, but this should not be used as an indicator; consider the `has_..._operator` types. </para>
	/// </summary>
	template<class T_, typename Arg_, bool Exists_ = EmuCore::TMP::has_cmp_less_operator_v<T_, Arg_>>
	struct cmp_less_operator_result
	{
		using type = void;
	};
	template<class T_, typename Arg_>
	struct cmp_less_operator_result<T_, Arg_, true>
	{
		using type = decltype(std::declval<T_>() < std::declval<Arg_>());
	};
	template<class T_, typename Arg_>
	using cmp_less_operator_result_t = typename cmp_less_operator_result<T_, Arg_>::type;

	/// <summary>
	/// <para>
	///		Struct that may be used to determine the result of using the greater-equal comparison operator (operator>=) with type T_,
	///		taking an argument of type Arg_.
	/// </para>
	/// <para> The type will be void if this operator does not exist, but this should not be used as an indicator; consider the `has_..._operator` types. </para>
	/// </summary>
	template<class T_, typename Arg_, bool Exists_ = EmuCore::TMP::has_cmp_greater_equal_operator_v<T_, Arg_>>
	struct cmp_greater_equal_operator_result
	{
		using type = void;
	};
	template<class T_, typename Arg_>
	struct cmp_greater_equal_operator_result<T_, Arg_, true>
	{
		using type = decltype(std::declval<T_>() >= std::declval<Arg_>());
	};
	template<class T_, typename Arg_>
	using cmp_greater_equal_operator_result_t = typename cmp_greater_equal_operator_result<T_, Arg_>::type;

	/// <summary>
	/// <para>
	///		Struct that may be used to determine the result of using the less-equal comparison operator (operator&lt;=) with type T_,
	///		taking an argument of type Arg_.
	/// </para>
	/// <para> The type will be void if this operator does not exist, but this should not be used as an indicator; consider the `has_..._operator` types. </para>
	/// </summary>
	template<class T_, typename Arg_, bool Exists_ = EmuCore::TMP::has_cmp_less_equal_operator_v<T_, Arg_>>
	struct cmp_less_equal_operator_result
	{
		using type = void;
	};
	template<class T_, typename Arg_>
	struct cmp_less_equal_operator_result<T_, Arg_, true>
	{
		using type = decltype(std::declval<T_>() <= std::declval<Arg_>());
	};
	template<class T_, typename Arg_>
	using cmp_less_equal_operator_result_t = typename cmp_less_equal_operator_result<T_, Arg_>::type;

#if (__cplusplus >= 201907L)
	/// <summary>
	/// <para>
	///		Struct that may be used to determine the result of using the three-way comparison operator (operator&lt;=&gt;) with type T_,
	///		taking an argument of type Arg_.
	/// </para>
	/// <para> The type will be void if this operator does not exist, but this should not be used as an indicator; consider the `has_..._operator` types. </para>
	/// </summary>
	template<class T_, typename Arg_, bool Exists_ = EmuCore::TMP::has_three_way_cmp_operator_v<T_, Arg_>>
	struct three_way_cmp_operator_result
	{
		using type = void;
	};
	template<class T_, typename Arg_>
	struct three_way_cmp_operator_result<T_, Arg_, true>
	{
		using type = decltype(std::declval<T_>() <=> std::declval<Arg_>());
	};
	template<class T_, typename Arg_>
	using three_way_cmp_operator_result_t = typename three_way_cmp_operator_result<T_, Arg_>::type;

	/// <summary>
	/// <para>
	///		Struct that may be used to determine the result of using the three-way comparison (spaceship) operator (operator&lt;=&gt;) with type T_,
	///		taking an argument of type Arg_.
	/// </para>
	/// <para> The type will be void if this operator does not exist, but this should not be used as an indicator; consider the `has_..._operator` types. </para>
	/// </summary>
	template<class T_, typename Arg_>
	using spaceship_operator_result = three_way_cmp_operator_result<T_, Arg_>;
	template<class T_, typename Arg_>
	using spaceship_operator_result_t = three_way_cmp_operator_result_t<T_, Arg_>;
#endif // (__cplusplus >= 201907L) (NOTE: This can be a false-negative with MSVC compiling for C++20)

	/// <summary>
	/// <para> Struct that may be used to determine the result of using the post-increment operator (operator++, called as `value++`) with type T_. </para>
	/// <para> The type will be void if this operator does not exist, but this should not be used as an indicator; consider the `has_..._operator` types. </para>
	/// </summary>
	template<class T_, bool Exists_ = EmuCore::TMP::has_post_increment_operator_v<T_>>
	struct post_increment_operator_result
	{
		using type = void;
	};
	template<class T_>
	struct post_increment_operator_result<T_, true>
	{
		using type = decltype((std::declval<T_>())++);
	};
	template<class T_>
	using post_increment_operator_result_t = typename post_increment_operator_result<T_>::type;

	/// <summary>
	/// <para> Struct that may be used to determine the result of using the pre-increment operator (operator++, called as `++value`) with type T_. </para>
	/// <para> The type will be void if this operator does not exist, but this should not be used as an indicator; consider the `has_..._operator` types. </para>
	/// </summary>
	template<class T_, bool Exists_ = EmuCore::TMP::has_pre_increment_operator_v<T_>>
	struct pre_increment_operator_result
	{
		using type = void;
	};
	template<class T_>
	struct pre_increment_operator_result<T_, true>
	{
		using type = decltype(++(std::declval<T_>()));
	};
	template<class T_>
	using pre_increment_operator_result_t = typename pre_increment_operator_result<T_>::type;

	/// <summary>
	/// <para> Struct that may be used to determine the result of using the post-decrement operator (operator--, called as `value--`) with type T_. </para>
	/// <para> The type will be void if this operator does not exist, but this should not be used as an indicator; consider the `has_..._operator` types. </para>
	/// </summary>
	template<class T_, bool Exists_ = EmuCore::TMP::has_post_decrement_operator_v<T_>>
	struct post_decrement_operator_result
	{
		using type = void;
	};
	template<class T_>
	struct post_decrement_operator_result<T_, true>
	{
		using type = decltype((std::declval<T_>())--);
	};
	template<class T_>
	using post_decrement_operator_result_t = typename post_decrement_operator_result<T_>::type;

	/// <summary>
	/// <para> Struct that may be used to determine the result of using the pre-decrement operator (operator--, called as `--value`) with type T_. </para>
	/// <para> The type will be void if this operator does not exist, but this should not be used as an indicator; consider the `has_..._operator` types. </para>
	/// </summary>
	template<class T_, bool Exists_ = EmuCore::TMP::has_pre_decrement_operator_v<T_>>
	struct pre_decrement_operator_result
	{
		using type = void;
	};
	template<class T_>
	struct pre_decrement_operator_result<T_, true>
	{
		using type = decltype(--(std::declval<T_>()));
	};
	template<class T_>
	using pre_decrement_operator_result_t = typename pre_decrement_operator_result<T_>::type;

	/// <summary>
	/// <para> Struct that may be used to determine the result of using the unary plus operator (operator+, called as `+value`) with type T_. </para>
	/// <para> The type will be void if this operator does not exist, but this should not be used as an indicator; consider the `has_..._operator` types. </para>
	/// </summary>
	template<class T_, bool Exists_ = EmuCore::TMP::has_unary_plus_operator_v<T_>>
	struct unary_plus_operator_result
	{
		using type = void;
	};
	template<class T_>
	struct unary_plus_operator_result<T_, true>
	{
		using type = decltype(+(std::declval<T_>()));
	};
	template<class T_>
	using unary_plus_operator_result_t = typename unary_plus_operator_result<T_>::type;

	/// <summary>
	/// <para> Struct that may be used to determine the result of using the unary minus operator (operator-, called as `-value`) with type T_. </para>
	/// <para> The type will be void if this operator does not exist, but this should not be used as an indicator; consider the `has_..._operator` types. </para>
	/// </summary>
	template<class T_, bool Exists_ = EmuCore::TMP::has_unary_minus_operator_v<T_>>
	struct unary_minus_operator_result
	{
		using type = void;
	};
	template<class T_>
	struct unary_minus_operator_result<T_, true>
	{
		using type = decltype(-(std::declval<T_>()));
	};
	template<class T_>
	using unary_minus_operator_result_t = typename unary_minus_operator_result<T_>::type;

	/// <summary>
	/// <para> Struct that may be used to determine the result of using the bitwise NOT operator (operator~, called as `~value`) with type T_. </para>
	/// <para> The type will be void if this operator does not exist, but this should not be used as an indicator; consider the `has_..._operator` types. </para>
	/// </summary>
	template<class T_, bool Exists_ = EmuCore::TMP::has_bitwise_not_operator_v<T_>>
	struct bitwise_not_operator_result
	{
		using type = void;
	};
	template<class T_>
	struct bitwise_not_operator_result<T_, true>
	{
		using type = decltype(~(std::declval<T_>()));
	};
	template<class T_>
	using bitwise_not_operator_result_t = typename bitwise_not_operator_result<T_>::type;

	/// <summary>
	/// <para> Struct that may be used to determine the result of using the logical NOT operator (operator!, called as `!value`) with type T_. </para>
	/// <para> The type will be void if this operator does not exist, but this should not be used as an indicator; consider the `has_..._operator` types. </para>
	/// </summary>
	template<class T_, bool Exists_ = EmuCore::TMP::has_logical_not_operator_v<T_>>
	struct logical_not_operator_result
	{
		using type = void;
	};
	template<class T_>
	struct logical_not_operator_result<T_, true>
	{
		using type = decltype(~(std::declval<T_>()));
	};
	template<class T_>
	using logical_not_operator_result_t = typename logical_not_operator_result<T_>::type;
#pragma endregion
}

#endif
