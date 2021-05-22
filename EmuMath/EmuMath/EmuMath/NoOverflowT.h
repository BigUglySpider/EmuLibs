#ifndef EMU_MATH_NO_OVERFLOW_T_H_INC_
#define EMU_MATH_NO_OVERFLOW_T_H_INC_

#include "../EmuCore/TMPHelpers/TypeComparators.h"
#include "../EmuCore/TMPHelpers/TypeConvertors.h"
#include <limits>
#include <type_traits>

namespace EmuMath
{
	template<typename T>
	struct NoOverflowT
	{
		static_assert(std::is_arithmetic_v<T>, "Attempted to form a NoOverflowT with a non-arithmetic type T.");

		using value_type = T;
		using this_type = NoOverflowT<value_type>;

		static constexpr T min_val = std::numeric_limits<value_type>::lowest();
		static constexpr T max_val = std::numeric_limits<value_type>::max();
		static constexpr bool is_signed = std::is_signed_v<value_type>;
		static constexpr bool is_floating_point = std::is_floating_point_v<value_type>;
		static constexpr bool is_integral = std::is_integral_v<value_type>;
		static constexpr std::size_t num_bytes = sizeof(value_type);
		static constexpr std::size_t num_bits = num_bytes * CHAR_BIT;

		using as_signed = NoOverflowT<std::conditional_t<is_signed, value_type, EmuCore::TMPHelpers::signed_if_int_t<value_type>>>;

		constexpr NoOverflowT() :
			val()
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
		value_type* operator&()
		{
			return this->GetPointerToVal();
		}
		const value_type* operator&() const
		{
			return this->GetPointerToVal();
		}

		value_type* GetPointerToVal()
		{
			return &val;
		}
		const value_type* GetPointerToVal() const
		{
			return &val;
		}
		this_type* GetPointerToThis()
		{
			return this;
		}
		const this_type* GetPointerToThis() const
		{
			return this;
		}

		template<typename Rhs>
		constexpr this_type _add_negative_lhs_positive_rhs(Rhs rhs) const
		{
			using conversion_type = std::conditional_t<is_integral, EmuCore::TMPHelpers::unsigned_if_int_t<value_type>, EmuCore::TMPHelpers::next_size_up_t<value_type>>;
			if constexpr (std::is_same_v<conversion_type, value_type>)
			{
				if (rhs > max_val)
				{
					value_type result = val + max_val;
					rhs -= max_val;
					while (result < 0 && rhs != 0)
					{
						if (rhs > max_val)
						{
							result += max_val;
							rhs -= max_val;
						}
						else
						{
							result += static_cast<value_type>(rhs);
							rhs = 0;
						}
					}
					if (rhs != 0)
					{
						const value_type highest_possible_rhs = max_val - val;
						return this_type((rhs >= highest_possible_rhs) ? max_val : static_cast<value_type>(val + rhs));
					}
					else
					{
						return this_type(result);
					}
				}
				else
				{
					return this_type(val + rhs);
				}
			}
			else
			{
				const conversion_type highest_possible_rhs = static_cast<conversion_type>(max_val) - val;
				return this_type((rhs >= highest_possible_rhs) ? max_val : static_cast<value_type>(val + rhs));
			}
		}
		
		template<typename Rhs>
		constexpr this_type _add_negative_lhs_negative_rhs(Rhs rhs) const
		{
			const value_type lowest_possible_rhs = min_val - val;
			return this_type((lowest_possible_rhs <= rhs) ? min_val : static_cast<value_type>(val + rhs));
		}
		
		template<typename Rhs>
		constexpr this_type _add_negative_lhs(Rhs rhs) const
		{
			if constexpr (std::is_signed_v<Rhs>)
			{
				if (rhs > 0)
				{
					return _add_negative_lhs_positive_rhs<Rhs>(rhs);
				}
				else
				{
					return _add_negative_lhs_negative_rhs<Rhs>(rhs);
				}
			}
			else
			{
				return _add_negative_lhs_positive_rhs<Rhs>(rhs);
			}
		}
		
		template<typename Rhs>
		constexpr this_type _add_positive_lhs_positive_rhs(Rhs rhs) const
		{
			const value_type highest_possible_rhs = max_val - val;
			return this_type((highest_possible_rhs <= rhs) ? max_val : static_cast<value_type>(val + rhs));
		}
		
		template<typename Rhs>
		constexpr this_type _add_positive_lhs_negative_rhs(Rhs rhs) const
		{
			if constexpr (is_signed)
			{
				using conversion_type = EmuCore::TMPHelpers::next_size_up_t<value_type>;
				if constexpr (std::is_same_v<conversion_type, value_type>)
				{
					if (rhs < min_val)
					{
						//value_type result = val + max_val;
						//rhs -= max_val;
						//while (result < 0 && rhs != 0)
						//{
						//	if (rhs > max_val)
						//	{
						//		result += max_val;
						//		rhs -= max_val;
						//	}
						//	else
						//	{
						//		result += static_cast<value_type>(rhs);
						//		rhs = 0;
						//	}
						//}
						//if (rhs != 0)
						//{
						//	const value_type highest_possible_rhs = max_val - val;
						//	return this_type((rhs >= highest_possible_rhs) ? max_val : static_cast<value_type>(val + rhs));
						//}
						//else
						//{
						//	return this_type(result);
						//}
					}
					else
					{
						return this_type(val + rhs);
					}
				}
				else
				{
					const conversion_type lowest_possible_rhs = static_cast<conversion_type>(min_val) - static_cast<conversion_type>(val);
					return this_type((lowest_possible_rhs >= rhs) ? min_val : static_cast<value_type>(val + rhs));
				}
			}
			else
			{
				using signed_type = std::make_signed_t<value_type>;
				using conversion_type = EmuCore::TMPHelpers::next_size_up_t<signed_type>;
				if constexpr (std::is_same_v<signed_type, conversion_type>)
				{
					constexpr signed_type max_signed = std::numeric_limits<signed_type>::max();
					constexpr signed_type min_signed_from_max = -max_signed;
					value_type result = val;
					while (result != 0 && rhs != 0)
					{
						if (min_signed_from_max >= rhs)
						{
							if (result <= max_signed)
							{
								return this_type(0);
							}
							else
							{
								result += min_signed_from_max;
								rhs += min_signed_from_max;
							}
						}
						else
						{
							signed_type positive_rhs = -static_cast<signed_type>(rhs);
							return this_type((result <= positive_rhs) ? 0 : static_cast<value_type>(result + rhs));
						}
					}
					return this_type(result);
				}
				else
				{
					conversion_type lowest_possible_rhs = -static_cast<conversion_type>(val);
					return this_type((val <= lowest_possible_rhs) ? min_val : static_cast<value_type>(max_val + rhs));
				}
			}
		}
		
		template<typename Rhs>
		constexpr this_type _add_positive_lhs(Rhs rhs) const
		{
			if constexpr (std::is_signed_v<Rhs>)
			{
				if (rhs < 0)
				{
					return _add_positive_lhs_negative_rhs<Rhs>(rhs);
				}
				else
				{
					return _add_positive_lhs_positive_rhs<Rhs>(rhs);
				}
			}
			else
			{
				return _add_positive_lhs_positive_rhs<Rhs>(rhs);
			}
		}
		
		template<typename Rhs>
		constexpr this_type operator+(Rhs rhs) const
		{
			if constexpr (is_floating_point != std::is_floating_point_v<Rhs>)
			{
				if constexpr (is_floating_point)
				{
					return (*this) + static_cast<long double>(rhs);
				}
				else
				{
					return (*this) + (EmuMath::NoOverflowT<std::int64_t>(rhs).val);
				}
			}
			else if constexpr (is_signed)
			{
				if (val < 0)
				{

					return _add_negative_lhs<Rhs>(rhs);
				}
				else
				{
					return _add_positive_lhs<Rhs>(rhs);
				}
			}
			else
			{
				if constexpr (std::is_signed_v<Rhs>)
				{
					if (rhs < 0)
					{
						return _add_positive_lhs_negative_rhs<Rhs>(rhs);
					}
					else
					{
						return _add_positive_lhs_positive_rhs<Rhs>(rhs);
					}
				}
				else
				{
					return _add_positive_lhs_positive_rhs<Rhs>(rhs);
				}
			}
		}
		constexpr as_signed operator-() const
		{
			if constexpr (is_signed)
			{
				if (val != min_val)
				{
					return as_signed(-val);
				}
				else
				{
					return as_signed(max_val);
				}
			}
			else
			{
				if (val > as_signed::max_val)
				{
					return as_signed(as_signed::min_val);
				}
				else
				{
					return as_signed(-static_cast<typename as_signed::value_type>(val));
				}
			}
		}

		template<typename Rhs>
		this_type& operator=(Rhs rhs)
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

		/// <summary> The underlying value stored here. Note that modifications directly through val will not have overflow safety. </summary>
		T val;
	};

	namespace TMPHelpers
	{
		template<typename T>
		static constexpr bool is_no_overflow_v = false;
		template<typename T>
		static constexpr bool is_no_overflow_v<EmuMath::NoOverflowT<T>> = true;
	}
}

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

#endif
