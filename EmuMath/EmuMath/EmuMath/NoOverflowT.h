#ifndef EMU_MATH_NO_OVERFLOW_T_H_INC_
#define EMU_MATH_NO_OVERFLOW_T_H_INC_

#include "../EmuCore/TMPHelpers/TypeComparators.h"
#include "../EmuCore/TMPHelpers/TypeConvertors.h"
#include <limits>
#include <ostream>
#include <type_traits>

namespace EmuMath
{
	/// <summary>
	/// <para> Wrapper for an arithmetic type to prevent it from over/underflowing. </para>
	/// <para>
	///		It is recommended to use this sparingly and only for values that need to be managed to avoid likely over/underflow issues, 
	///		as the speed may be significantly slower than simple arithmetic due to additional safety checks on most operations.
	/// </para>
	/// </summary>
	/// <typeparam name="T">Type to wrap for preventing over/underflows.</typeparam>
	template<typename T>
	struct NoOverflowT
	{
	public:
		static_assert(std::is_arithmetic_v<T>, "Attempted to form a NoOverflowT with a non-arithmetic type T.");

		using value_type = T;
		using this_type = NoOverflowT<value_type>;

		/// <summary> The lowest value that this wrapper type's val may be set to. </summary>
		static constexpr T min_val = std::numeric_limits<value_type>::lowest();
		/// <summary> The highest value that this wrapper type's val may be set to. </summary>
		static constexpr T max_val = std::numeric_limits<value_type>::max();
		/// <summary> Boolean indicating if this wrapper's underlying type is signed. </summary>
		static constexpr bool is_signed = std::is_signed_v<value_type>;
		/// <summary> Boolean indicating if this wrapper's underlying type is a floating point. </summary>
		static constexpr bool is_floating_point = std::is_floating_point_v<value_type>;
		/// <summary> Boolean indicating if this wrapper's underlying type is an integer. </summary>
		static constexpr bool is_integral = std::is_integral_v<value_type>;
		/// <summary> The number of bytes used to store this wrapper's underlying type. </summary>
		static constexpr std::size_t num_bytes = sizeof(value_type);
		/// <summary> The number of bits used to store this wrapper's underlying type. </summary>
		static constexpr std::size_t num_bits = num_bytes * CHAR_BIT;

		/// <summary> Signed variation fo this wrapper's underlying type which may be used to represent it losslessly as a signed number. </summary>
		using value_signed = EmuCore::TMPHelpers::uint_lossless_signed_rep_t<value_type>;
		/// <summary> Wrapper type containing the signed variation of this wrapper's underlying type. Same as this wrapper type if it is already signed. </summary>
		using as_signed = NoOverflowT<value_signed>;

		constexpr NoOverflowT() :
			val()
		{
		}
		constexpr NoOverflowT(const this_type& toCopy) :
			val(toCopy.val)
		{
		}
		constexpr NoOverflowT(const value_type value_) :
			val(value_)
		{
		}
		template<typename ToCopyT>
		constexpr NoOverflowT(ToCopyT toCopy_) :
			val((toCopy_ < min_val) ? min_val : (toCopy_ > max_val) ? max_val : static_cast<value_type>(toCopy_))
		{
		}
		template<typename ToCopyT>
		constexpr NoOverflowT(const NoOverflowT<ToCopyT>& toCopy_) :
			NoOverflowT(toCopy_.val)
		{
		}

		constexpr operator value_type () const
		{
			return val;
		}
		constexpr operator value_type& ()
		{
			return val;
		}
		constexpr operator const value_type& () const
		{
			return val;
		}
		constexpr operator bool() const
		{
			return val;
		}

		value_type* operator&()
		{
			return this->GetPointerToVal();
		}
		const value_type* operator&() const
		{
			return this->GetPointerToVal();
		}

		/// <summary> Provides a pointer to this wrapper's underlying value. May be called in shorthand via the ampersand operator. </summary>
		/// <returns>Pointer to this wrapper's underlying value.</returns>
		value_type* GetPointerToVal()
		{
			return &val;
		}
		/// <summary> Provides a pointer to this wrapper's underlying value. May be called in shorthand via the ampersand operator. </summary>
		/// <returns>Pointer to this wrapper's underlying value.</returns>
		const value_type* GetPointerToVal() const
		{
			return &val;
		}
		/// <summary> Provides a pointer to this wrapper. Required to use if wanting a wrapper pointer as the ampersand operator will point to the underlying value. </summary>
		/// <returns>Pointer to this wrapper.</returns>
		this_type* GetPointerToWrapper()
		{
			return this;
		}
		/// <summary> Provides a pointer to this wrapper. Required to use if wanting a wrapper pointer as the ampersand operator will point to the underlying value.  </summary>
		/// <returns>Constant pointer to this wrapper.</returns>
		const this_type* GetPointerToWrapper() const
		{
			return this;
		}
		/// <summary> Copies this wrapper as one containing the provided type. Normal requirements for the contained type apply. </summary>
		/// <typeparam name="OutT_">Type to be contained within the returned wrapper.</typeparam>
		/// <returns>Wrapper containing a copy of this wrapper's underlying value, stored as the provided type.</returns>
		template<typename OutT_>
		constexpr NoOverflowT<OutT_> As() const
		{
			return NoOverflowT<OutT_>(val);
		}
		
		constexpr this_type operator&(value_type rhs) const
		{
			return this_type(val & rhs);
		}
		constexpr this_type operator|(value_type rhs) const
		{
			return this_type(val | rhs);
		}
		constexpr this_type operator^(value_type rhs) const
		{
			return this_type(val ^ rhs);
		}
		constexpr this_type operator<<(const std::size_t numShifts) const
		{
			if (numShifts >= num_bits)
			{
				return this_type(0);
			}
			else
			{
				return this_type(val << numShifts);
			}
		}
		constexpr this_type operator>>(const std::size_t numShifts) const
		{
			if (numShifts >= num_bits)
			{
				return this_type(0);
			}
			else
			{
				return this_type(val >> numShifts);
			}
		}
		constexpr this_type operator~() const
		{
			return this_type(~val);
		}
		template<typename Rhs>
		constexpr this_type operator+(Rhs rhs_) const
		{
			if constexpr (is_signed)
			{
				return this_type(this->_perform_add_signed_lhs<Rhs>(rhs_));
			}
			else
			{
				return this_type(this->_perform_add_unsigned_lhs<Rhs>(rhs_));
			}
		}
		template<typename Rhs>
		constexpr this_type operator+(NoOverflowT<Rhs> rhs) const
		{
			return (*this) + rhs.val;
		}
		template<typename Rhs>
		constexpr this_type operator-(Rhs rhs_) const
		{
			if constexpr (is_signed)
			{
				return this_type(this->_perform_subtract_signed_lhs<Rhs>(rhs_));
			}
			else
			{
				return this_type(this->_perform_subtract_unsigned_lhs<Rhs>(rhs_));
			}
		}
		template<typename Rhs>
		constexpr this_type operator-(NoOverflowT<Rhs> rhs) const
		{
			return (*this) - rhs.val;
		}
		constexpr as_signed operator-() const
		{
			if constexpr (is_signed)
			{
				if (val == min_val)
				{
					return as_signed(max_val);
				}
				else
				{
					return as_signed(-val);
				}
			}
			else
			{
				return as_signed(-static_cast<value_signed>(val));
			}
		}
		template<typename Rhs>
		constexpr this_type operator*(Rhs rhs) const
		{
			if constexpr (is_integral && std::is_integral_v<Rhs>)
			{
				if constexpr (std::is_signed_v<Rhs>)
				{
					if (rhs < 0)
					{
						if constexpr (is_signed)
						{
							return ((-this_type(val)) * -NoOverflowT<Rhs>(rhs));
						}
						else
						{
							return this_type(0);
						}
					}
					else
					{
						if (val > (max_val / rhs))
						{
							return this_type(max_val);
						}
						else if (val < (min_val / rhs))
						{
							return this_type(min_val);
						}
						else
						{
							return this_type(static_cast<value_type>(val * rhs));
						}
					}
				}
				else
				{
					if (val > (max_val / rhs))
					{
						return this_type(max_val);
					}
					else if (val < (min_val / rhs))
					{
						return this_type(min_val);
					}
					else
					{
						return this_type(static_cast<value_type>(val * rhs));
					}
				}
			}
			else
			{
				using result_t = long double;
				const result_t result = static_cast<result_t>(val) * rhs;
				return this_type((result <= static_cast<result_t>(min_val)) ? min_val : (result >= static_cast<result_t>(max_val)) ? max_val : static_cast<value_type>(result));
			}
		}
		template<typename Rhs>
		constexpr this_type operator*(NoOverflowT<Rhs> rhs) const
		{
			return (*this) * rhs.val;
		}
		template<typename Rhs>
		constexpr this_type operator/(Rhs rhs) const
		{
			if constexpr (std::is_integral_v<Rhs>)
			{
				return this_type(static_cast<Rhs>(val) / rhs);
			}
			else
			{
				if (rhs >= 1 || rhs <= -1)
				{
					return this_type(static_cast<value_type>(val / rhs));
				}
				else
				{
					return (*this) * (1.0L / rhs);
				}
			}
		}
		template<typename Rhs>
		constexpr this_type operator/(NoOverflowT<Rhs> rhs) const
		{
			return (*this) / rhs.val;
		}

		template<typename Rhs>
		constexpr this_type& operator=(Rhs rhs)
		{
			if constexpr (std::is_same_v<value_type, Rhs>)
			{
				val = rhs;
			}
			else
			{
				if constexpr (is_signed)
				{
					if constexpr (std::is_signed_v<Rhs>)
					{
						if constexpr (sizeof(value_type) > sizeof(Rhs))
						{
							val = static_cast<value_type>(rhs);
						}
						else
						{
							val = (rhs < min_val) ? min_val : (rhs > max_val) ? max_val : static_cast<value_type>(rhs);
						}
					}
					else
					{
						val = (rhs > max_val) ? max_val : static_cast<value_type>(rhs);
					}
				}
				else
				{
					if constexpr (std::is_signed_v<Rhs>)
					{
						val = (rhs < 0) ? min_val : (rhs > max_val) ? max_val : static_cast<value_type>(rhs);
					}
					else
					{
						val = (rhs > max_val) ? max_val : static_cast<value_type>(rhs);
					}
				}
			}
			return *this;
		}
		constexpr this_type& operator&=(value_type rhs)
		{
			*this = (*this) & rhs;
			return *this;
		}
		constexpr this_type& operator|=(value_type rhs)
		{
			*this = (*this) | rhs;
			return *this;
		}
		constexpr this_type& operator^=(value_type rhs)
		{
			*this = (*this) ^ rhs;
			return *this;
		}
		constexpr this_type& operator<<=(value_type rhs)
		{
			*this = (*this) << rhs;
			return *this;
		}
		constexpr this_type& operator>>=(value_type rhs)
		{
			*this = (*this) >> rhs;
			return *this;
		}

		template<typename Rhs>
		constexpr this_type& operator+=(Rhs rhs)
		{
			val = this->operator+(rhs).val;
			return *this;
		}
		template<typename Rhs>
		constexpr this_type& operator-=(Rhs rhs)
		{
			val = this->operator-(rhs).val;
			return *this;
		}
		template<typename Rhs>
		constexpr this_type& operator*=(Rhs rhs)
		{
			val = this->operator*(rhs).val;
			return *this;
		}
		template<typename Rhs>
		constexpr this_type& operator/=(Rhs rhs)
		{
			val = this->operator/(rhs).val;
			return *this;
		}
		constexpr this_type& operator--()
		{
			if (val != min_val)
			{
				if constexpr (is_integral)
				{
					--val;
				}
				else
				{
					if (val < 0)
					{
						val = (min_val - val) > value_type(-1) ? min_val : val - value_type(1);
					}
					else
					{
						val -= value_type(1);
					}
				}
			}
			return *this;
		}
		constexpr this_type operator--(int)
		{
			const this_type out_(*this);
			this->operator--();
			return out_;
		}
		constexpr this_type& operator++()
		{
			if (val != max_val)
			{
				if constexpr (is_integral)
				{
					++val;
				}
				else
				{
					if (val > 0)
					{
						val = (max_val - val) < value_type(1) ? max_val : val + value_type(1);
					}
					else
					{
						val += value_type(1);
					}
				}
			}
			return *this;
		}
		constexpr this_type operator++(int)
		{
			const this_type out_(*this);
			this->operator++();
			return out_;
		}

		template<typename Rhs>
		constexpr bool operator==(Rhs rhs) const
		{
			return val == rhs;
		}
		template<typename Rhs>
		constexpr bool operator!=(Rhs rhs) const
		{
			return val != rhs;
		}
		template<typename Rhs>
		constexpr bool operator>(Rhs rhs) const
		{
			return val > rhs;
		}
		template<typename Rhs>
		constexpr bool operator<(Rhs rhs) const
		{
			return val < rhs;
		}
		template<typename Rhs>
		constexpr bool operator>=(Rhs rhs) const
		{
			return val >= rhs;
		}
		template<typename Rhs>
		constexpr bool operator<=(Rhs rhs) const
		{
			return val <= rhs;
		}

		/// <summary> The underlying value stored by this wrapper. Note that modifications directly through val will not have overflow safety checks. </summary>
		T val;

	private:
		template<typename Rhs>
		constexpr value_type _perform_add_unsigned_lhs(Rhs rhs_) const
		{
			if (rhs_ >= 0)
			{
				const value_type highest_possible_rhs = max_val - val;
				if constexpr (std::is_signed_v<Rhs>)
				{
					return (rhs_ >= static_cast<value_signed>(highest_possible_rhs)) ? max_val : val + static_cast<value_type>(rhs_);
				}
				else
				{
					return (rhs_ >= highest_possible_rhs) ? max_val : val + static_cast<value_type>(rhs_);
				}
			}
			else
			{
				const value_signed lowest_possible_rhs = -static_cast<value_signed>(val);
				return (rhs_ <= lowest_possible_rhs) ? 0 : static_cast<value_type>(val + static_cast<value_signed>(rhs_));
			}
		}
		template<typename Rhs>
		constexpr value_type _perform_add_signed_lhs(Rhs rhs_) const
		{
			return (val >= 0) ? this->_perform_add_positive_signed_lhs<Rhs>(rhs_) : this->_perform_add_negative_signed_lhs<Rhs>(rhs_);
		}
		template<typename Rhs>
		constexpr value_type _perform_add_positive_signed_lhs(Rhs rhs_) const
		{
			if (rhs_ >= 0)
			{
				if constexpr (std::is_unsigned_v<Rhs>)
				{
					using rhs_signed = EmuCore::TMPHelpers::uint_lossless_signed_rep_t<Rhs>;
					return (static_cast<rhs_signed>(rhs_) >= (max_val - val)) ? max_val : static_cast<value_type>(val + rhs_);
				}
				else
				{
					return (rhs_ >= (max_val - val)) ? max_val : val + static_cast<value_type>(rhs_);
				}
			}
			else
			{
				using next_size_value_type = EmuCore::TMPHelpers::next_size_up_t<value_type>;
				if constexpr (sizeof(value_type) == sizeof(next_size_value_type))
				{
					if (rhs_ < min_val)
					{
						const value_type result = val + min_val;
						const value_type lowest_possible_rhs = min_val - result;	// We know this is safe to do now as result will be a maximum of 0
						rhs_ -= static_cast<Rhs>(min_val);
						return (rhs_ <= lowest_possible_rhs) ? min_val : result + static_cast<value_type>(rhs_);
					}
					else
					{
						// No need for an additional check as we know we won't be brought below the minimum value in this case.
						return val + static_cast<value_type>(rhs_);
					}
				}
				else
				{
					const next_size_value_type lowest_possible_rhs = static_cast<next_size_value_type>(min_val) - static_cast<next_size_value_type>(val);
					return (rhs_ <= lowest_possible_rhs) ? min_val : val + static_cast<next_size_value_type>(rhs_);
				}
			}
		}
		template<typename Rhs>
		constexpr value_type _perform_add_negative_signed_lhs(Rhs rhs_) const
		{
			if (rhs_ >= 0)
			{
				if (rhs_ > max_val)
				{
					value_type result = val;
					do
					{
						if (result >= 0)
						{
							if (rhs_ >= max_val)
							{
								result = max_val;
								rhs_ = 0;
							}
							else
							{
								if constexpr (std::is_unsigned_v<Rhs>)
								{
									using rhs_signed = EmuCore::TMPHelpers::uint_lossless_signed_rep_t<Rhs>;
									result = (static_cast<rhs_signed>(rhs_) >= (max_val - result)) ? max_val : result + static_cast<value_type>(rhs_);
								}
								else
								{
									result = (rhs_ >= (max_val - result)) ? max_val : result + static_cast<value_type>(rhs_);
								}
								rhs_ = 0;
							}
						}
						else
						{
							if (rhs_ > max_val)
							{
								result += max_val;
								rhs_ -= static_cast<Rhs>(max_val);
							}
							else
							{
								result += static_cast<value_type>(rhs_);
								rhs_ = 0;
							}
						}
					} while (rhs_ != 0);
					return result;
				}
				else
				{
					return val + static_cast<value_type>(rhs_);
				}
			}
			else
			{
				// Although this unsigned state is never reached, compiler warnings will be emitted using the same return as the else branch
				if constexpr (std::is_unsigned_v<Rhs>)
				{
					using rhs_signed = EmuCore::TMPHelpers::uint_lossless_signed_rep_t<Rhs>;
					return (static_cast<rhs_signed>(rhs_) <= (min_val - val) ? min_val : val + static_cast<value_type>(rhs_));
				}
				else
				{
					return (rhs_ <= (min_val - val) ? min_val : val + static_cast<value_type>(rhs_));
				}
			}
		}

		template<typename Rhs>
		constexpr value_type _perform_subtract_unsigned_lhs(Rhs rhs_) const
		{
			if (rhs_ >= 0)
			{
				if constexpr (std::is_signed_v<Rhs>)
				{
					return (rhs_ >= static_cast<value_signed>(val)) ? 0 : val - rhs_;
				}
				else
				{
					return (rhs_ >= val) ? 0 : val - rhs_;
				}
			}
			else
			{
				const value_signed lowest_possible_rhs = -static_cast<value_signed>(max_val - val);
				return (rhs_ <= lowest_possible_rhs) ? max_val : static_cast<value_type>(val - static_cast<value_signed>(rhs_));
			}
		}
		template<typename Rhs>
		constexpr value_type _perform_subtract_signed_lhs(Rhs rhs_) const
		{
			return (val >= 0) ? this->_perform_subtract_positive_signed_lhs<Rhs>(rhs_) : this->_perform_subtract_negative_signed_lhs<Rhs>(rhs_);
		}
		template<typename Rhs>
		constexpr value_type _perform_subtract_positive_signed_lhs(Rhs rhs_) const
		{
			using next_size_value_type = EmuCore::TMPHelpers::next_size_up_t<value_type>;
			if (rhs_ >= 0)
			{
				using rhs_signed_cast = std::conditional_t<std::is_signed_v<Rhs>, Rhs, EmuCore::TMPHelpers::uint_lossless_signed_rep_t<Rhs>>;
				if constexpr (sizeof(value_type) == sizeof(next_size_value_type))
				{
					if (static_cast<rhs_signed_cast>(rhs_) > max_val)
					{
						// We subtract the additional 1 after max_val so that min_val - val result is safely convertible to a positive subtraction
						const value_type result = (val - max_val) - 1;
						const value_type highest_possible_rhs = -(min_val - val);
						rhs_ -= max_val;
						rhs_ -= 1;
						return (static_cast<rhs_signed_cast>(rhs_) >= highest_possible_rhs) ? min_val : result - static_cast<value_type>(rhs_);
					}
					else
					{
						return val + static_cast<value_type>(rhs_);
					}
				}
				else
				{
					const next_size_value_type highest_possible_rhs = -(static_cast<next_size_value_type>(min_val) - static_cast<next_size_value_type>(val));
					return (static_cast<rhs_signed_cast>(rhs_) >= highest_possible_rhs) ? min_val : static_cast<value_type>(static_cast<next_size_value_type>(val) - rhs_);
				}
			}
			else
			{
				if constexpr (std::is_signed_v<Rhs>)
				{
					return (rhs_ <= -(max_val - val)) ? max_val : val - static_cast<value_type>(rhs_);
				}
				else
				{
					using rhs_signed_cast = EmuCore::TMPHelpers::uint_lossless_signed_rep_t<Rhs>;
					return (static_cast<rhs_signed_cast>(rhs_) <= -(max_val - val)) ? max_val : val - static_cast<value_type>(rhs_);
				}
			}
		}
		template<typename Rhs>
		constexpr value_type _perform_subtract_negative_signed_lhs(Rhs rhs_) const
		{
			if (rhs_ >= 0)
			{
				if constexpr (std::is_signed_v<Rhs>)
				{
					return (rhs_ >= -(min_val - val)) ? min_val : val - static_cast<value_type>(rhs_);
				}
				else
				{
					using rhs_as_signed = EmuCore::TMPHelpers::uint_lossless_signed_rep_t<Rhs>;
					return (static_cast<rhs_as_signed>(rhs_) >= -(min_val - val)) ? min_val : val - static_cast<value_type>(rhs_);
				}
			}
			else
			{
				if (rhs_ <= min_val)
				{
					const value_type result = val - min_val;
					rhs_ -= static_cast<Rhs>(min_val);
					if constexpr (std::is_signed_v<Rhs>)
					{
						return (rhs_ <= -(max_val - result)) ? max_val : result - static_cast<value_type>(rhs_);
					}
					else
					{
						using rhs_as_signed = EmuCore::TMPHelpers::uint_lossless_signed_rep_t<Rhs>;
						return (static_cast<rhs_as_signed>(rhs_) <= -(max_val - result)) ? max_val : result - static_cast<value_type>(rhs_);
					}
				}
				else
				{
					return val - static_cast<value_type>(rhs_);
				}
			}
		}
	};
}

#pragma region STD_TEMPLATE_OVERRIDES
namespace std
{
	template<typename T>
	struct std::is_signed<EmuMath::NoOverflowT<T>> : public std::is_signed<T>
	{
	};
	template<typename T>
	static constexpr bool is_signed_v<EmuMath::NoOverflowT<T>> = std::is_signed_v<T>;

	template<typename T>
	struct std::is_unsigned<EmuMath::NoOverflowT<T>> : public std::is_unsigned<T>
	{
	};
	template<typename T>
	static constexpr bool is_unsigned_v<EmuMath::NoOverflowT<T>> = std::is_unsigned_v<T>;

	template<typename T>
	struct std::is_arithmetic<EmuMath::NoOverflowT<T>> : public std::is_arithmetic<T>
	{
	};
	template<typename T>
	static constexpr bool is_arithmetic_v<EmuMath::NoOverflowT<T>> = std::is_arithmetic_v<T>;

	template<typename T>
	struct std::is_floating_point<EmuMath::NoOverflowT<T>> : public std::is_floating_point<T>
	{
	};
	template<typename T>
	static constexpr bool is_floating_point_v<EmuMath::NoOverflowT<T>> = std::is_floating_point_v<T>;

	template<typename T>
	struct std::is_integral<EmuMath::NoOverflowT<T>> : public std::is_integral<T>
	{
	};
	template<typename T>
	static constexpr bool is_integral_v<EmuMath::NoOverflowT<T>> = std::is_integral_v<T>;
}
#pragma endregion

#pragma region EMU_CORE_TEMPLATE_OVERRIDES
namespace EmuCore::TMPHelpers
{
	template<typename UintT_>
	struct uint_lossless_signed_rep<EmuMath::NoOverflowT<UintT_>>
	{
		using type = EmuMath::NoOverflowT<EmuCore::TMPHelpers::uint_lossless_signed_rep_t<UintT_>>;
	};
}
#pragma endregion

#pragma region EMU_MATH_TEMPLATE_OVERRIDES
namespace EmuMath::TMPHelpers
{
	template<typename T>
	struct is_no_overflow
	{
		static constexpr bool value = false;
	};
	template<typename T>
	struct is_no_overflow<EmuMath::NoOverflowT<T>>
	{
		static constexpr bool value = true;
	};
	/// <summary> Boolean indicating if the passed type is an EmuMath NoOverflowT instantiation. </summary>
	/// <typeparam name="T">Type to check.</typeparam>
	template<typename T>
	static constexpr bool is_no_overflow_v = is_no_overflow<T>::value;
}
#pragma endregion

template<typename T>
inline std::ostream& operator<<(std::ostream& stream_, const EmuMath::NoOverflowT<T> noOverflowVal_)
{
	stream_ << noOverflowVal_.val;
	return stream_;
}
template<typename T>
inline std::wostream& operator<<(std::wostream& stream_, const EmuMath::NoOverflowT<T> noOverflowVal_)
{
	stream_ << noOverflowVal_.val;
	return stream_;
}

#endif
