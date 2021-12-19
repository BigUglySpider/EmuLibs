#ifndef EMU_CORE_TYPE_OBFUSCATION_H_INC_
#define EMU_CORE_TYPE_OBFUSCATION_H_INC_ 1

#include "OperatorChecks.h"
#include "TypeComparators.h"
#include "TypeConvertors.h"
#include <ostream>

namespace EmuCore::TMP
{
	template<class T_>
	struct type_obfuscator
	{
	public:
		using this_type = type_obfuscator<T_>;

		using value_type = T_;
		using const_value_type = const T_;

		using ref_type = std::conditional_t<std::is_rvalue_reference_v<value_type>, value_type, std::add_lvalue_reference_t<value_type>>;
		using const_ref_type = std::conditional_t<std::is_rvalue_reference_v<value_type>, const_value_type, std::add_lvalue_reference_t<const_value_type>>;
		using rvalue_ref_type = std::add_rvalue_reference_t<T_>;

#pragma region CONSTRUCTORS
	public:
		template<typename = std::enable_if_t<std::is_default_constructible_v<T_>>>
		constexpr inline type_obfuscator() : wrapped_value()
		{
		}

		template<typename OtherT_, typename = std::enable_if_t<std::is_constructible_v<T_, type_obfuscator<T_>::ref_type>>>
		constexpr inline type_obfuscator(type_obfuscator<T_>& other_) : wrapped_value(other_.wrapped_value)
		{
		}

		template<typename OtherT_, typename = std::enable_if_t<std::is_constructible_v<T_, type_obfuscator<T_>::const_ref_type>>>
		constexpr inline type_obfuscator(const type_obfuscator<T_>& other_) : wrapped_value(other_.wrapped_value)
		{
		}

		template<typename OtherT_, typename = std::enable_if_t<std::is_constructible_v<T_, type_obfuscator<T_>::rvalue_ref_type>>>
		constexpr inline type_obfuscator(type_obfuscator<T_>&& other_) noexcept : wrapped_value(std::move(other_.wrapped_value))
		{
		}

		template<class...ConstructionArgs_, typename = std::enable_if_t<std::is_constructible_v<T_, ConstructionArgs_...>>>
		constexpr inline type_obfuscator(ConstructionArgs_&&...construction_args_) : wrapped_value(std::forward<ConstructionArgs_>(construction_args_)...)
		{
		}
#pragma endregion

#pragma region SELF_FUNCS
		/// <summary> Returns the memory address of this wrapper. May only be access this way, as the &amp; operator returns the address of the wrapped item. </summary>
		/// <returns>Memory address of this obfuscation wrapper.</returns>
		[[nodiscard]] constexpr inline this_type* Address()
		{
			return this;
		}
		[[nodiscard]] constexpr inline const this_type* Address() const
		{
			return this;
		}
#pragma endregion

#pragma region CONVERSIONS
	public:
		constexpr inline operator ref_type ()
		{
			return wrapped_value;
		}
		
		constexpr inline operator const_ref_type() const
		{
			return wrapped_value;
		}

		template<typename Out_, typename = std::enable_if_t<std::is_convertible_v<T_, Out_>>>
		explicit constexpr inline operator Out_()
		{
			return static_cast<Out_>(wrapped_value);
		}
		template<typename Out_, typename = std::enable_if_t<std::is_convertible_v<const T_, Out_>>>
		explicit constexpr inline operator Out_() const
		{
			return static_cast<Out_>(wrapped_value);
		}
#pragma endregion

#pragma region UNARY_OPERATORS
		template<typename = std::enable_if_t<EmuCore::TMP::has_unary_plus_operator_v<ref_type>>>
		constexpr inline EmuCore::TMP::unary_plus_operator_result_t<ref_type> operator+()
		{
			if constexpr (std::is_void_v<EmuCore::TMP::unary_plus_operator_result_t<ref_type>>)
			{
				+wrapped_value;
			}
			else
			{
				return +wrapped_value;
			}
		}
		template<typename = std::enable_if_t<EmuCore::TMP::has_unary_plus_operator_v<const_ref_type>>>
		constexpr inline EmuCore::TMP::unary_plus_operator_result_t<const_ref_type> operator+() const
		{
			if constexpr (std::is_void_v<EmuCore::TMP::unary_plus_operator_result_t<const_ref_type>>)
			{
				+wrapped_value;
			}
			else
			{
				return +wrapped_value;
			}
		}

		template<typename = std::enable_if_t<EmuCore::TMP::has_unary_minus_operator_v<ref_type>>>
		constexpr inline EmuCore::TMP::unary_minus_operator_result_t<ref_type> operator-()
		{
			if constexpr (std::is_void_v<EmuCore::TMP::unary_minus_operator_result_t<ref_type>>)
			{
				-wrapped_value;
			}
			else
			{
				return -wrapped_value;
			}
		}
		template<typename = std::enable_if_t<EmuCore::TMP::has_unary_minus_operator_v<const_ref_type>>>
		constexpr inline EmuCore::TMP::unary_minus_operator_result_t<const_ref_type> operator-() const
		{
			if constexpr (std::is_void_v<EmuCore::TMP::unary_minus_operator_result_t<const_ref_type>>)
			{
				-wrapped_value;
			}
			else
			{
				return -wrapped_value;
			}
		}

		template<typename = std::enable_if_t<EmuCore::TMP::has_pre_increment_operator_v<ref_type>>>
		constexpr inline EmuCore::TMP::pre_increment_operator_result_t<ref_type> operator++()
		{
			if constexpr (std::is_void_v<EmuCore::TMP::pre_increment_operator_result_t<ref_type>>)
			{
				++wrapped_value;
			}
			else
			{
				return ++wrapped_value;
			}
		}

		template<typename = std::enable_if_t<EmuCore::TMP::has_post_increment_operator_v<ref_type>>>
		constexpr inline EmuCore::TMP::post_increment_operator_result_t<ref_type> operator++(int)
		{
			if constexpr (std::is_void_v<EmuCore::TMP::post_increment_operator_result_t<ref_type>>)
			{
				wrapped_value++;
			}
			else
			{
				return wrapped_value++;
			}
		}

		template<typename = std::enable_if_t<EmuCore::TMP::has_pre_decrement_operator_v<ref_type>>>
		constexpr inline EmuCore::TMP::pre_decrement_operator_result_t<ref_type> operator--()
		{
			if constexpr (std::is_void_v<EmuCore::TMP::pre_decrement_operator_result_t<ref_type>>)
			{
				--wrapped_value;
			}
			else
			{
				return --wrapped_value;
			}
		}

		template<typename = std::enable_if_t<EmuCore::TMP::has_post_decrement_operator_v<ref_type>>>
		constexpr inline EmuCore::TMP::post_decrement_operator_result_t<ref_type> operator--(int)
		{
			if constexpr (std::is_void_v<EmuCore::TMP::post_decrement_operator_result_t<ref_type>>)
			{
				wrapped_value--;
			}
			else
			{
				return wrapped_value--;
			}
		}

		template<typename = std::enable_if_t<EmuCore::TMP::has_bitwise_not_operator_v<ref_type>>>
		constexpr inline EmuCore::TMP::bitwise_not_operator_result_t<ref_type> operator~()
		{
			if constexpr (std::is_void_v<EmuCore::TMP::bitwise_not_operator_result_t<ref_type>>)
			{
				~wrapped_value;
			}
			else
			{
				return ~wrapped_value;
			}
		}
		template<typename = std::enable_if_t<EmuCore::TMP::has_bitwise_not_operator_v<const_ref_type>>>
		constexpr inline EmuCore::TMP::bitwise_not_operator_result_t<const_ref_type> operator~() const
		{
			if constexpr (std::is_void_v<EmuCore::TMP::bitwise_not_operator_result_t<const_ref_type>>)
			{
				~wrapped_value;
			}
			else
			{
				return ~wrapped_value;
			}
		}

		template<typename = std::enable_if_t<EmuCore::TMP::has_logical_not_operator_v<ref_type>>>
		constexpr inline EmuCore::TMP::logical_not_operator_result_t<ref_type> operator!()
		{
			if constexpr (std::is_void_v<EmuCore::TMP::logical_not_operator_result_t<ref_type>>)
			{
				!wrapped_value;
			}
			else
			{
				return !wrapped_value;
			}
		}
		template<typename = std::enable_if_t<EmuCore::TMP::has_logical_not_operator_v<const_ref_type>>>
		constexpr inline EmuCore::TMP::logical_not_operator_result_t<const_ref_type> operator!() const
		{
			if constexpr (std::is_void_v<EmuCore::TMP::logical_not_operator_result_t<const_ref_type>>)
			{
				!wrapped_value;
			}
			else
			{
				return !wrapped_value;
			}
		}
#pragma endregion

#pragma region ARITHMETIC_OPERATORS
		template<typename Rhs_, typename = std::enable_if_t<EmuCore::TMP::has_plus_operator_v<ref_type, Rhs_>>>
		constexpr inline EmuCore::TMP::plus_operator_result_t<ref_type, Rhs_> operator+(Rhs_&& rhs_)
		{
			if constexpr (std::is_void_v<EmuCore::TMP::plus_operator_result_t<ref_type, Rhs_>>)
			{
				wrapped_value + std::forward<Rhs_>(rhs_);
			}
			else
			{
				return wrapped_value + std::forward<Rhs_>(rhs_);
			}
		}
		template<typename Rhs_, typename = std::enable_if_t<EmuCore::TMP::has_plus_operator_v<const_ref_type, Rhs_>>>
		constexpr inline EmuCore::TMP::plus_operator_result_t<const_ref_type, Rhs_> operator+(Rhs_&& rhs_) const
		{
			if constexpr (std::is_void_v<EmuCore::TMP::plus_operator_result_t<const_ref_type, Rhs_>>)
			{
				wrapped_value + std::forward<Rhs_>(rhs_);
			}
			else
			{
				return wrapped_value + std::forward<Rhs_>(rhs_);
			}
		}

		template<typename Rhs_, typename = std::enable_if_t<EmuCore::TMP::has_subtract_operator_v<ref_type, Rhs_>>>
		constexpr inline EmuCore::TMP::subtract_operator_result_t<ref_type, Rhs_> operator-(Rhs_&& rhs_)
		{
			if constexpr (std::is_void_v<EmuCore::TMP::subtract_operator_result_t<ref_type, Rhs_>>)
			{
				wrapped_value - std::forward<Rhs_>(rhs_);
			}
			else
			{
				return wrapped_value - std::forward<Rhs_>(rhs_);
			}
		}
		template<typename Rhs_, typename = std::enable_if_t<EmuCore::TMP::has_subtract_operator_v<const_ref_type, Rhs_>>>
		constexpr inline EmuCore::TMP::subtract_operator_result_t<const_ref_type, Rhs_> operator-(Rhs_&& rhs_) const
		{
			if constexpr (std::is_void_v<EmuCore::TMP::subtract_operator_result_t<const_ref_type, Rhs_>>)
			{
				wrapped_value - std::forward<Rhs_>(rhs_);
			}
			else
			{
				return wrapped_value - std::forward<Rhs_>(rhs_);
			}
		}

		template<typename Rhs_, typename = std::enable_if_t<EmuCore::TMP::has_multiply_operator_v<ref_type, Rhs_>>>
		constexpr inline EmuCore::TMP::multiply_operator_result_t<ref_type, Rhs_> operator*(Rhs_&& rhs_)
		{
			if constexpr (std::is_void_v<EmuCore::TMP::multiply_operator_result_t<ref_type, Rhs_>>)
			{
				wrapped_value * std::forward<Rhs_>(rhs_);
			}
			else
			{
				return wrapped_value * std::forward<Rhs_>(rhs_);
			}
		}
		template<typename Rhs_, typename = std::enable_if_t<EmuCore::TMP::has_multiply_operator_v<const_ref_type, Rhs_>>>
		constexpr inline EmuCore::TMP::multiply_operator_result_t<const_ref_type, Rhs_> operator*(Rhs_&& rhs_) const
		{
			if constexpr (std::is_void_v<EmuCore::TMP::multiply_operator_result_t<const_ref_type, Rhs_>>)
			{
				wrapped_value * std::forward<Rhs_>(rhs_);
			}
			else
			{
				return wrapped_value * std::forward<Rhs_>(rhs_);
			}
		}

		template<typename Rhs_, typename = std::enable_if_t<EmuCore::TMP::has_divide_operator_v<ref_type, Rhs_>>>
		constexpr inline EmuCore::TMP::divide_operator_result_t<ref_type, Rhs_> operator/(Rhs_&& rhs_)
		{
			if constexpr (std::is_void_v<EmuCore::TMP::divide_operator_result_t<ref_type, Rhs_>>)
			{
				wrapped_value / std::forward<Rhs_>(rhs_);
			}
			else
			{
				return wrapped_value / std::forward<Rhs_>(rhs_);
			}
		}
		template<typename Rhs_, typename = std::enable_if_t<EmuCore::TMP::has_divide_operator_v<const_ref_type, Rhs_>>>
		constexpr inline EmuCore::TMP::divide_operator_result_t<const_ref_type, Rhs_> operator/(Rhs_&& rhs_) const
		{
			if constexpr (std::is_void_v<EmuCore::TMP::divide_operator_result_t<const_ref_type, Rhs_>>)
			{
				wrapped_value / std::forward<Rhs_>(rhs_);
			}
			else
			{
				return wrapped_value / std::forward<Rhs_>(rhs_);
			}
		}

		template<typename Rhs_, typename = std::enable_if_t<EmuCore::TMP::has_mod_operator_v<ref_type, Rhs_>>>
		constexpr inline EmuCore::TMP::mod_operator_result_t<ref_type, Rhs_> operator%(Rhs_&& rhs_)
		{
			if constexpr (std::is_void_v<EmuCore::TMP::mod_operator_result_t<ref_type, Rhs_>>)
			{
				wrapped_value % std::forward<Rhs_>(rhs_);
			}
			else
			{
				return wrapped_value % std::forward<Rhs_>(rhs_);
			}
		}
		template<typename Rhs_, typename = std::enable_if_t<EmuCore::TMP::has_mod_operator_v<const_ref_type, Rhs_>>>
		constexpr inline EmuCore::TMP::mod_operator_result_t<const_ref_type, Rhs_> operator%(Rhs_&& rhs_) const
		{
			if constexpr (std::is_void_v<EmuCore::TMP::mod_operator_result_t<const_ref_type, Rhs_>>)
			{
				wrapped_value % std::forward<Rhs_>(rhs_);
			}
			else
			{
				return wrapped_value % std::forward<Rhs_>(rhs_);
			}
		}
#pragma endregion

#pragma region ARITHMETIC_ASSIGN_OPERATORS
		template<typename Rhs_, typename = std::enable_if_t<EmuCore::TMP::has_plus_assign_operator_v<ref_type, Rhs_>>>
		constexpr inline EmuCore::TMP::plus_assign_operator_result_t<ref_type, Rhs_> operator+=(Rhs_&& rhs_)
		{
			if constexpr (std::is_void_v<EmuCore::TMP::plus_assign_operator_result_t<ref_type, Rhs_>>)
			{
				wrapped_value += std::forward<Rhs_>(rhs_);
			}
			else
			{
				return wrapped_value += std::forward<Rhs_>(rhs_);
			}
		}
		template<typename Rhs_, typename = std::enable_if_t<EmuCore::TMP::has_plus_assign_operator_v<const_ref_type, Rhs_>>>
		constexpr inline EmuCore::TMP::plus_assign_operator_result_t<const_ref_type, Rhs_> operator+=(Rhs_&& rhs_) const
		{
			if constexpr (std::is_void_v<EmuCore::TMP::plus_assign_operator_result_t<const_ref_type, Rhs_>>)
			{
				wrapped_value += std::forward<Rhs_>(rhs_);
			}
			else
			{
				return wrapped_value += std::forward<Rhs_>(rhs_);
			}
		}

		template<typename Rhs_, typename = std::enable_if_t<EmuCore::TMP::has_subtract_assign_operator_v<ref_type, Rhs_>>>
		constexpr inline EmuCore::TMP::subtract_assign_operator_result_t<ref_type, Rhs_> operator-=(Rhs_&& rhs_)
		{
			if constexpr (std::is_void_v<EmuCore::TMP::subtract_assign_operator_result_t<ref_type, Rhs_>>)
			{
				wrapped_value -= std::forward<Rhs_>(rhs_);
			}
			else
			{
				return wrapped_value -= std::forward<Rhs_>(rhs_);
			}
		}
		template<typename Rhs_, typename = std::enable_if_t<EmuCore::TMP::has_subtract_assign_operator_v<const_ref_type, Rhs_>>>
		constexpr inline EmuCore::TMP::subtract_assign_operator_result_t<const_ref_type, Rhs_> operator-=(Rhs_&& rhs_) const
		{
			if constexpr (std::is_void_v<EmuCore::TMP::subtract_assign_operator_result_t<const_ref_type, Rhs_>>)
			{
				wrapped_value -= std::forward<Rhs_>(rhs_);
			}
			else
			{
				return wrapped_value -= std::forward<Rhs_>(rhs_);
			}
		}

		template<typename Rhs_, typename = std::enable_if_t<EmuCore::TMP::has_multiply_assign_operator_v<ref_type, Rhs_>>>
		constexpr inline EmuCore::TMP::multiply_assign_operator_result_t<ref_type, Rhs_> operator*=(Rhs_&& rhs_)
		{
			if constexpr (std::is_void_v<EmuCore::TMP::multiply_assign_operator_result_t<ref_type, Rhs_>>)
			{
				wrapped_value *= std::forward<Rhs_>(rhs_);
			}
			else
			{
				return wrapped_value *= std::forward<Rhs_>(rhs_);
			}
		}
		template<typename Rhs_, typename = std::enable_if_t<EmuCore::TMP::has_multiply_assign_operator_v<const_ref_type, Rhs_>>>
		constexpr inline EmuCore::TMP::multiply_assign_operator_result_t<const_ref_type, Rhs_> operator*=(Rhs_&& rhs_) const
		{
			if constexpr (std::is_void_v<EmuCore::TMP::multiply_assign_operator_result_t<const_ref_type, Rhs_>>)
			{
				wrapped_value *= std::forward<Rhs_>(rhs_);
			}
			else
			{
				return wrapped_value *= std::forward<Rhs_>(rhs_);
			}
		}

		template<typename Rhs_, typename = std::enable_if_t<EmuCore::TMP::has_divide_assign_operator_v<ref_type, Rhs_>>>
		constexpr inline EmuCore::TMP::divide_assign_operator_result_t<ref_type, Rhs_> operator/=(Rhs_&& rhs_)
		{
			if constexpr (std::is_void_v<EmuCore::TMP::divide_assign_operator_result_t<ref_type, Rhs_>>)
			{
				wrapped_value /= std::forward<Rhs_>(rhs_);
			}
			else
			{
				return wrapped_value /= std::forward<Rhs_>(rhs_);
			}
		}
		template<typename Rhs_, typename = std::enable_if_t<EmuCore::TMP::has_divide_assign_operator_v<const_ref_type, Rhs_>>>
		constexpr inline EmuCore::TMP::divide_assign_operator_result_t<const_ref_type, Rhs_> operator/=(Rhs_&& rhs_) const
		{
			if constexpr (std::is_void_v<EmuCore::TMP::divide_assign_operator_result_t<const_ref_type, Rhs_>>)
			{
				wrapped_value /= std::forward<Rhs_>(rhs_);
			}
			else
			{
				return wrapped_value /= std::forward<Rhs_>(rhs_);
			}
		}

		template<typename Rhs_, typename = std::enable_if_t<EmuCore::TMP::has_mod_assign_operator_v<ref_type, Rhs_>>>
		constexpr inline EmuCore::TMP::mod_assign_operator_result_t<ref_type, Rhs_> operator%=(Rhs_&& rhs_)
		{
			if constexpr (std::is_void_v<EmuCore::TMP::mod_assign_operator_result_t<ref_type, Rhs_>>)
			{
				wrapped_value %= std::forward<Rhs_>(rhs_);
			}
			else
			{
				return wrapped_value %= std::forward<Rhs_>(rhs_);
			}
		}
		template<typename Rhs_, typename = std::enable_if_t<EmuCore::TMP::has_mod_assign_operator_v<const_ref_type, Rhs_>>>
		constexpr inline EmuCore::TMP::mod_assign_operator_result_t<const_ref_type, Rhs_> operator%=(Rhs_&& rhs_) const
		{
			if constexpr (std::is_void_v<EmuCore::TMP::mod_assign_operator_result_t<const_ref_type, Rhs_>>)
			{
				wrapped_value %= std::forward<Rhs_>(rhs_);
			}
			else
			{
				return wrapped_value %= std::forward<Rhs_>(rhs_);
			}
		}
#pragma endregion

#pragma region BITWISE_OPERATORS
		template<typename Rhs_, typename = std::enable_if_t<EmuCore::TMP::has_bitwise_and_operator_v<ref_type, Rhs_>>>
		constexpr inline EmuCore::TMP::bitwise_and_operator_result_t<ref_type, Rhs_> operator&(Rhs_&& rhs_)
		{
			if constexpr (std::is_void_v<EmuCore::TMP::bitwise_and_operator_result_t<ref_type, Rhs_>>)
			{
				wrapped_value & std::forward<Rhs_>(rhs_);
			}
			else
			{
				return wrapped_value & std::forward<Rhs_>(rhs_);
			}
		}
		template<typename Rhs_, typename = std::enable_if_t<EmuCore::TMP::has_bitwise_and_operator_v<const_ref_type, Rhs_>>>
		constexpr inline EmuCore::TMP::bitwise_and_operator_result_t<const_ref_type, Rhs_> operator&(Rhs_&& rhs_) const
		{
			if constexpr (std::is_void_v<EmuCore::TMP::bitwise_and_operator_result_t<const_ref_type, Rhs_>>)
			{
				wrapped_value & std::forward<Rhs_>(rhs_);
			}
			else
			{
				return wrapped_value & std::forward<Rhs_>(rhs_);
			}
		}

		template<typename Rhs_, typename = std::enable_if_t<EmuCore::TMP::has_bitwise_or_operator_v<ref_type, Rhs_>>>
		constexpr inline EmuCore::TMP::bitwise_or_operator_result_t<ref_type, Rhs_> operator|(Rhs_&& rhs_)
		{
			if constexpr (std::is_void_v<EmuCore::TMP::bitwise_or_operator_result_t<ref_type, Rhs_>>)
			{
				wrapped_value | std::forward<Rhs_>(rhs_);
			}
			else
			{
				return wrapped_value | std::forward<Rhs_>(rhs_);
			}
		}
		template<typename Rhs_, typename = std::enable_if_t<EmuCore::TMP::has_bitwise_or_operator_v<const_ref_type, Rhs_>>>
		constexpr inline EmuCore::TMP::bitwise_or_operator_result_t<const_ref_type, Rhs_> operator|(Rhs_&& rhs_) const
		{
			if constexpr (std::is_void_v<EmuCore::TMP::bitwise_or_operator_result_t<const_ref_type, Rhs_>>)
			{
				wrapped_value | std::forward<Rhs_>(rhs_);
			}
			else
			{
				return wrapped_value | std::forward<Rhs_>(rhs_);
			}
		}

		template<typename Rhs_, typename = std::enable_if_t<EmuCore::TMP::has_bitwise_xor_operator_v<ref_type, Rhs_>>>
		constexpr inline EmuCore::TMP::bitwise_xor_operator_result_t<ref_type, Rhs_> operator^(Rhs_&& rhs_)
		{
			if constexpr (std::is_void_v<EmuCore::TMP::bitwise_xor_operator_result_t<ref_type, Rhs_>>)
			{
				wrapped_value ^ std::forward<Rhs_>(rhs_);
			}
			else
			{
				return wrapped_value ^ std::forward<Rhs_>(rhs_);
			}
		}
		template<typename Rhs_, typename = std::enable_if_t<EmuCore::TMP::has_bitwise_xor_operator_v<const_ref_type, Rhs_>>>
		constexpr inline EmuCore::TMP::bitwise_xor_operator_result_t<const_ref_type, Rhs_> operator^(Rhs_&& rhs_) const
		{
			if constexpr (std::is_void_v<EmuCore::TMP::bitwise_xor_operator_result_t<const_ref_type, Rhs_>>)
			{
				wrapped_value ^ std::forward<Rhs_>(rhs_);
			}
			else
			{
				return wrapped_value ^ std::forward<Rhs_>(rhs_);
			}
		}

		template<typename Rhs_, typename = std::enable_if_t<EmuCore::TMP::has_left_shift_operator_v<ref_type, Rhs_>>>
		constexpr inline EmuCore::TMP::left_shift_operator_result_t<ref_type, Rhs_> operator<<(Rhs_&& rhs_)
		{
			if constexpr (std::is_void_v<EmuCore::TMP::left_shift_operator_result_t<ref_type, Rhs_>>)
			{
				wrapped_value << std::forward<Rhs_>(rhs_);
			}
			else
			{
				return wrapped_value << std::forward<Rhs_>(rhs_);
			}
		}
		template<typename Rhs_, typename = std::enable_if_t<EmuCore::TMP::has_left_shift_operator_v<const_ref_type, Rhs_>>>
		constexpr inline EmuCore::TMP::left_shift_operator_result_t<const_ref_type, Rhs_> operator<<(Rhs_&& rhs_) const
		{
			if constexpr (std::is_void_v<EmuCore::TMP::left_shift_operator_result_t<const_ref_type, Rhs_>>)
			{
				wrapped_value << std::forward<Rhs_>(rhs_);
			}
			else
			{
				return wrapped_value << std::forward<Rhs_>(rhs_);
			}
		}

		template<typename Rhs_, typename = std::enable_if_t<EmuCore::TMP::has_right_shift_operator_v<ref_type, Rhs_>>>
		constexpr inline EmuCore::TMP::right_shift_operator_result_t<ref_type, Rhs_> operator>>(Rhs_&& rhs_)
		{
			if constexpr (std::is_void_v<EmuCore::TMP::right_shift_operator_result_t<ref_type, Rhs_>>)
			{
				wrapped_value >> std::forward<Rhs_>(rhs_);
			}
			else
			{
				return wrapped_value >> std::forward<Rhs_>(rhs_);
			}
		}
		template<typename Rhs_, typename = std::enable_if_t<EmuCore::TMP::has_right_shift_operator_v<const_ref_type, Rhs_>>>
		constexpr inline EmuCore::TMP::right_shift_operator_result_t<const_ref_type, Rhs_> operator>>(Rhs_&& rhs_) const
		{
			if constexpr (std::is_void_v<EmuCore::TMP::right_shift_operator_result_t<const_ref_type, Rhs_>>)
			{
				wrapped_value >> std::forward<Rhs_>(rhs_);
			}
			else
			{
				return wrapped_value >> std::forward<Rhs_>(rhs_);
			}
		}
#pragma endregion

#pragma region BITWISE_ASSIGN_OPERATORS
		template<typename Rhs_, typename = std::enable_if_t<EmuCore::TMP::has_bitwise_and_assign_operator_v<ref_type, Rhs_>>>
		constexpr inline EmuCore::TMP::bitwise_and_assign_operator_result_t<ref_type, Rhs_> operator&=(Rhs_&& rhs_)
		{
			if constexpr (std::is_void_v<EmuCore::TMP::bitwise_and_assign_operator_result_t<ref_type, Rhs_>>)
			{
				wrapped_value &= std::forward<Rhs_>(rhs_);
			}
			else
			{
				return wrapped_value &= std::forward<Rhs_>(rhs_);
			}
		}
		template<typename Rhs_, typename = std::enable_if_t<EmuCore::TMP::has_bitwise_and_assign_operator_v<const_ref_type, Rhs_>>>
		constexpr inline EmuCore::TMP::bitwise_and_assign_operator_result_t<const_ref_type, Rhs_> operator&=(Rhs_&& rhs_) const
		{
			if constexpr (std::is_void_v<EmuCore::TMP::bitwise_and_assign_operator_result_t<const_ref_type, Rhs_>>)
			{
				wrapped_value &= std::forward<Rhs_>(rhs_);
			}
			else
			{
				return wrapped_value &= std::forward<Rhs_>(rhs_);
			}
		}

		template<typename Rhs_, typename = std::enable_if_t<EmuCore::TMP::has_bitwise_or_assign_operator_v<ref_type, Rhs_>>>
		constexpr inline EmuCore::TMP::bitwise_or_assign_operator_result_t<ref_type, Rhs_> operator|=(Rhs_&& rhs_)
		{
			if constexpr (std::is_void_v<EmuCore::TMP::bitwise_or_assign_operator_result_t<ref_type, Rhs_>>)
			{
				wrapped_value |= std::forward<Rhs_>(rhs_);
			}
			else
			{
				return wrapped_value |= std::forward<Rhs_>(rhs_);
			}
		}
		template<typename Rhs_, typename = std::enable_if_t<EmuCore::TMP::has_bitwise_or_assign_operator_v<const_ref_type, Rhs_>>>
		constexpr inline EmuCore::TMP::bitwise_or_assign_operator_result_t<const_ref_type, Rhs_> operator|=(Rhs_&& rhs_) const
		{
			if constexpr (std::is_void_v<EmuCore::TMP::bitwise_or_assign_operator_result_t<const_ref_type, Rhs_>>)
			{
				wrapped_value |= std::forward<Rhs_>(rhs_);
			}
			else
			{
				return wrapped_value |= std::forward<Rhs_>(rhs_);
			}
		}

		template<typename Rhs_, typename = std::enable_if_t<EmuCore::TMP::has_bitwise_xor_assign_operator_v<ref_type, Rhs_>>>
		constexpr inline EmuCore::TMP::bitwise_xor_assign_operator_result_t<ref_type, Rhs_> operator^=(Rhs_&& rhs_)
		{
			if constexpr (std::is_void_v<EmuCore::TMP::bitwise_xor_assign_operator_result_t<ref_type, Rhs_>>)
			{
				wrapped_value ^= std::forward<Rhs_>(rhs_);
			}
			else
			{
				return wrapped_value ^= std::forward<Rhs_>(rhs_);
			}
		}
		template<typename Rhs_, typename = std::enable_if_t<EmuCore::TMP::has_bitwise_xor_assign_operator_v<const_ref_type, Rhs_>>>
		constexpr inline EmuCore::TMP::bitwise_xor_assign_operator_result_t<const_ref_type, Rhs_> operator^=(Rhs_&& rhs_) const
		{
			if constexpr (std::is_void_v<EmuCore::TMP::bitwise_xor_assign_operator_result_t<const_ref_type, Rhs_>>)
			{
				wrapped_value ^= std::forward<Rhs_>(rhs_);
			}
			else
			{
				return wrapped_value ^= std::forward<Rhs_>(rhs_);
			}
		}

		template<typename Rhs_, typename = std::enable_if_t<EmuCore::TMP::has_left_shift_assign_operator_v<ref_type, Rhs_>>>
		constexpr inline EmuCore::TMP::left_shift_assign_operator_result_t<ref_type, Rhs_> operator<<=(Rhs_&& rhs_)
		{
			if constexpr (std::is_void_v<EmuCore::TMP::left_shift_assign_operator_result_t<ref_type, Rhs_>>)
			{
				wrapped_value <<= std::forward<Rhs_>(rhs_);
			}
			else
			{
				return wrapped_value <<= std::forward<Rhs_>(rhs_);
			}
		}
		template<typename Rhs_, typename = std::enable_if_t<EmuCore::TMP::has_left_shift_assign_operator_v<const_ref_type, Rhs_>>>
		constexpr inline EmuCore::TMP::left_shift_assign_operator_result_t<const_ref_type, Rhs_> operator<<=(Rhs_&& rhs_) const
		{
			if constexpr (std::is_void_v<EmuCore::TMP::left_shift_assign_operator_result_t<const_ref_type, Rhs_>>)
			{
				wrapped_value <<= std::forward<Rhs_>(rhs_);
			}
			else
			{
				return wrapped_value <<= std::forward<Rhs_>(rhs_);
			}
		}

		template<typename Rhs_, typename = std::enable_if_t<EmuCore::TMP::has_right_shift_assign_operator_v<ref_type, Rhs_>>>
		constexpr inline EmuCore::TMP::right_shift_assign_operator_result_t<ref_type, Rhs_> operator>>=(Rhs_&& rhs_)
		{
			if constexpr (std::is_void_v<EmuCore::TMP::right_shift_assign_operator_result_t<ref_type, Rhs_>>)
			{
				wrapped_value >>= std::forward<Rhs_>(rhs_);
			}
			else
			{
				return wrapped_value >>= std::forward<Rhs_>(rhs_);
			}
		}
		template<typename Rhs_, typename = std::enable_if_t<EmuCore::TMP::has_right_shift_assign_operator_v<const_ref_type, Rhs_>>>
		constexpr inline EmuCore::TMP::right_shift_assign_operator_result_t<const_ref_type, Rhs_> operator>>=(Rhs_&& rhs_) const
		{
			if constexpr (std::is_void_v<EmuCore::TMP::right_shift_assign_operator_result_t<const_ref_type, Rhs_>>)
			{
				wrapped_value >>= std::forward<Rhs_>(rhs_);
			}
			else
			{
				return wrapped_value >>= std::forward<Rhs_>(rhs_);
			}
		}
#pragma endregion

#pragma region LOGICAL_OPERATORS
		template<typename Rhs_, typename = std::enable_if_t<EmuCore::TMP::has_logical_and_operator_v<ref_type, Rhs_>>>
		constexpr inline EmuCore::TMP::logical_and_operator_result_t<ref_type, Rhs_> operator&&(Rhs_&& rhs_)
		{
			if constexpr (std::is_void_v<EmuCore::TMP::logical_and_operator_result_t<ref_type, Rhs_>>)
			{
				wrapped_value && std::forward<Rhs_>(rhs_);
			}
			else
			{
				return wrapped_value && std::forward<Rhs_>(rhs_);
			}
		}
		template<typename Rhs_, typename = std::enable_if_t<EmuCore::TMP::has_logical_and_operator_v<const_ref_type, Rhs_>>>
		constexpr inline EmuCore::TMP::logical_and_operator_result_t<const_ref_type, Rhs_> operator&&(Rhs_&& rhs_) const
		{
			if constexpr (std::is_void_v<EmuCore::TMP::logical_and_operator_result_t<const_ref_type, Rhs_>>)
			{
				wrapped_value && std::forward<Rhs_>(rhs_);
			}
			else
			{
				return wrapped_value && std::forward<Rhs_>(rhs_);
			}
		}

		template<typename Rhs_, typename = std::enable_if_t<EmuCore::TMP::has_logical_or_operator_v<ref_type, Rhs_>>>
		constexpr inline EmuCore::TMP::logical_or_operator_result_t<ref_type, Rhs_> operator||(Rhs_&& rhs_)
		{
			if constexpr (std::is_void_v<EmuCore::TMP::logical_or_operator_result_t<ref_type, Rhs_>>)
			{
				wrapped_value || std::forward<Rhs_>(rhs_);
			}
			else
			{
				return wrapped_value || std::forward<Rhs_>(rhs_);
			}
		}
		template<typename Rhs_, typename = std::enable_if_t<EmuCore::TMP::has_logical_or_operator_v<const_ref_type, Rhs_>>>
		constexpr inline EmuCore::TMP::logical_or_operator_result_t<const_ref_type, Rhs_> operator||(Rhs_&& rhs_) const
		{
			if constexpr (std::is_void_v<EmuCore::TMP::logical_or_operator_result_t<const_ref_type, Rhs_>>)
			{
				wrapped_value || std::forward<Rhs_>(rhs_);
			}
			else
			{
				return wrapped_value || std::forward<Rhs_>(rhs_);
			}
		}
#pragma endregion

#pragma region ASSIGNMENT_OPERATORS
		template<typename Rhs_, typename = std::enable_if_t<std::is_assignable_v<ref_type, typename type_obfuscator<Rhs_>::rvalue_ref_type>>>
		constexpr inline ref_type operator=(type_obfuscator<Rhs_>&& to_move_) noexcept
		{
			wrapped_value = std::move(to_move_.wrapped_value);
			return wrapped_value;
		}

		template<typename Rhs_, typename = std::enable_if_t<std::is_assignable_v<ref_type, typename type_obfuscator<Rhs_>::ref_type>>>
		constexpr inline ref_type operator=(type_obfuscator<Rhs_>& to_copy_) noexcept
		{
			wrapped_value = to_copy_.wrapped_value;
			return wrapped_value;
		}

		template<typename Rhs_, typename = std::enable_if_t<std::is_assignable_v<ref_type, typename type_obfuscator<Rhs_>::const_ref_type>>>
		constexpr inline ref_type operator=(const type_obfuscator<Rhs_>& to_copy_) noexcept
		{
			wrapped_value = to_copy_.wrapped_value;
			return wrapped_value;
		}

		template<typename Rhs_, typename = std::enable_if_t<std::is_assignable_v<ref_type, Rhs_>>>
		constexpr inline ref_type operator=(Rhs_&& rhs_)
		{
			wrapped_value = std::forward<Rhs_>(rhs_);
			return wrapped_value;
		}
#pragma endregion

#pragma region OTHER_OPERATORS
		template<class...InvokeArgs_, typename = std::enable_if_t<std::is_invocable_v<ref_type, InvokeArgs_...>>>
		constexpr inline std::invoke_result_t<ref_type, InvokeArgs_...> operator()(InvokeArgs_&&...invoke_args_)
		{
			if constexpr (std::is_void_v<std::invoke_result_t<ref_type, InvokeArgs_...>>)
			{
				wrapped_value(std::forward<InvokeArgs_>(invoke_args_)...);
			}
			else
			{
				return wrapped_value(std::forward<InvokeArgs_>(invoke_args_)...);
			}
		}
		template<class...InvokeArgs_, typename = std::enable_if_t<std::is_invocable_v<const ref_type, InvokeArgs_...>>>
		constexpr inline std::invoke_result_t<const ref_type, InvokeArgs_...> operator()(InvokeArgs_&&...invoke_args_) const
		{
			if constexpr (std::is_void_v<std::invoke_result_t<const ref_type, InvokeArgs_...>>)
			{
				wrapped_value(std::forward<InvokeArgs_>(invoke_args_)...);
			}
			else
			{
				return wrapped_value(std::forward<InvokeArgs_>(invoke_args_)...);
			}
		}

		template<typename Val_, typename = std::enable_if_t<EmuCore::TMP::has_subscript_operator_v<ref_type, Val_>>>
		constexpr inline EmuCore::TMP::subscript_operator_result_t<ref_type, Val_> operator[](Val_&& val_)
		{
			if constexpr (std::is_void_v<EmuCore::TMP::subscript_operator_result_t<ref_type, Val_>>)
			{
				wrapped_value[std::forward<Val_>(val_)];
			}
			else
			{
				return wrapped_value[std::forward<Val_>(val_)];
			}
		}
		template<typename Val_, typename = std::enable_if_t<EmuCore::TMP::has_subscript_operator_v<const ref_type, Val_>>>
		constexpr inline EmuCore::TMP::subscript_operator_result_t<const ref_type, Val_> operator[](Val_&& val_) const
		{
			if constexpr (std::is_void_v<EmuCore::TMP::subscript_operator_result_t<const ref_type, Val_>>)
			{
				wrapped_value[std::forward<Val_>(val_)];
			}
			else
			{
				return wrapped_value[std::forward<Val_>(val_)];
			}
		}

		constexpr inline decltype(&(std::declval<ref_type>())) operator&()
		{
			return &wrapped_value;
		}

		constexpr inline decltype(&(std::declval<const_ref_type>())) operator&() const
		{
			return &wrapped_value;
		}
#pragma endregion

		/// <summary> The underlying item wrapped by this obfuscator. </summary>
		T_ wrapped_value;
	};

	/// <summary>
	/// <para> Wraps the passed argument in an EmuCore type_obfuscator for that type. </para>
	/// <para> Obfuscation may be used to partially hide an item's type, while still allowing it to be used with valid operators and passing to functions. </para>
	/// <para>
	///		This is intended for use in avoiding template specialisations that may result in undesirable results, 
	///		or to avoid compile-time decisions based on an item's type.
	/// </para>
	/// <para> Note that implicit conversion may not be possible for all cases, but this exposes the following operators if required: </para>
	/// <para> --- Arithmetic (+, -, *, /, %, ++, --, +=, -=, *=, /=, %=) </para>
	/// <para> --- Bitwise (&amp;, |, ^, &lt;&lt;, &gt;&gt;, ~, &amp;=, |=, ^=, &lt;&lt;=, &gt;&gt;=) </para>
	/// <para> --- Logical (!, ||, &amp;&amp;) </para>
	/// <para> --- Others ([], (), =) </para>
	/// </summary>
	/// <param name="val_">Item to obfuscate the type of.</param>
	/// <returns>The passed item wrapped in an type_obfuscator instance.</returns>
	template<typename T_>
	[[nodiscard]] constexpr inline EmuCore::TMP::type_obfuscator<T_> obfuscate(T_&& val_)
	{
		return type_obfuscator<T_>(std::forward<T_>(val_));
	}
}

template
<
	typename Elem_,
	typename Traits_,
	typename T_,
	typename = std::enable_if_t<EmuCore::TMP::has_left_shift_operator_v<std::basic_ostream<Elem_, Traits_>&, typename EmuCore::TMP::type_obfuscator<T_>::ref_type>>
>
constexpr inline std::basic_ostream<Elem_, Traits_>& operator<<(std::basic_ostream<Elem_, Traits_>& str_, EmuCore::TMP::type_obfuscator<T_>& val_)
{
	return str_ << val_.wrapped_value;
}

template
<
	typename Elem_,
	typename Traits_,
	typename T_,
	typename = std::enable_if_t<EmuCore::TMP::has_left_shift_operator_v<std::basic_ostream<Elem_, Traits_>&, typename EmuCore::TMP::type_obfuscator<T_>::const_ref_type>>
>
constexpr inline std::basic_ostream<Elem_, Traits_>& operator<<(std::basic_ostream<Elem_, Traits_>& str_, const EmuCore::TMP::type_obfuscator<T_>& val_)
{
	return str_ << val_.wrapped_value;
}

#endif
