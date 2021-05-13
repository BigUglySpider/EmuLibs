#ifndef EMU_MATH_VECTOR_2_T_H_INC_
#define EMU_MATH_VECTOR_2_T_H_INC_

#include "EmuVectorInfo.h"
#include <exception>

namespace EmuMath
{
	template<typename T>
	struct Vector2
	{
#pragma region ALIASES_AND_STATIC_CONSTANT_EXPRESSIONS
	protected:
		template<typename T_>
		using info_type_t = EmuMath::_info::VectorInfo<T_>;

	public:
		/// <summary> Type containing info regarding EmuMath vectors containing the type within this vector. </summary>
		using info_type = info_type_t<T>;
		/// <summary> The value types stored within this vector. </summary>
		using value_type = typename info_type::value_type;
		/// <summary> The non-reference variant of value types stored within this vector. </summary>
		using nonref_value_type = typename info_type::nonref_value_type;
		/// <summary> The reference variant of value types stored within this vector. </summary>
		using ref_value_type = typename info_type::ref_value_type;

		static constexpr std::size_t size()
		{
			return 2;
		}
#pragma endregion

#pragma region CONSTRUCTORS
		constexpr Vector2() :
			x(),
			y()
		{
		}
		constexpr Vector2(const Vector2<value_type>& toCopy) :
			Vector2(toCopy.x, toCopy.y)
		{
		}
		constexpr Vector2(const value_type& x_, const value_type& y_) :
			x(x_),
			y(y_)
		{
		}
#pragma endregion

#pragma region RANDOM_ACCESS
		ref_value_type operator[](const std::size_t index)
		{
			return at(index);
		}
		const ref_value_type operator[](const std::size_t index) const
		{
			return at(index);
		}
		ref_value_type at(std::size_t index)
		{
			switch (index)
			{
				case 0:
					return x;
				case 1:
					return y;
				default:
					throw std::logic_error("Attempted to access an EmuMath::Vector2 element by an index which does not exist.");
			}
		}
		const ref_value_type at(std::size_t index) const
		{
			switch (index)
			{
				case 0:
					return x;
				case 1:
					return y;
				default:
					throw std::logic_error("Attempted to access an EmuMath::Vector2 element by an index which does not exist.");
			}
		}
		template<std::size_t index>
		constexpr ref_value_type at()
		{
			if constexpr (index == 0)
			{
				return x;
			}
			else if constexpr (index == 1)
			{
				return y;
			}
			else
			{
				static_assert(false, "Attempted to access an EmuMath::Vector2 element by an index which does not exist.");
			}
		}
		template<std::size_t index>
		constexpr const ref_value_type at() const
		{
			if constexpr (index == 0)
			{
				return x;
			}
			else if constexpr (index == 1)
			{
				return y;
			}
			else
			{
				static_assert(false, "Attempted to access an EmuMath::Vector2 element by an index which does not exist.");
			}
		}
#pragma endregion

#pragma region ARITHMETIC_CONST_OPERATORS
		template<typename OtherT>
		constexpr Vector2<nonref_value_type> operator+(const Vector2<OtherT>& rhs) const
		{
			if constexpr (std::is_same_v<nonref_value_type, typename Vector2<OtherT>::nonref_value_type>)
			{
				return { x + rhs.x, y + rhs.y };
			}
			else
			{
				return { x + static_cast<nonref_value_type>(rhs.x), y + static_cast<nonref_value_type>(rhs.y) };
			}
		}
		template<typename OtherT>
		constexpr Vector2<nonref_value_type> operator-(const Vector2<OtherT>& rhs) const
		{
			if constexpr (std::is_same_v<nonref_value_type, typename Vector2<OtherT>::nonref_value_type>)
			{
				return { x - rhs.x, y - rhs.y };
			}
			else
			{
				return { x - static_cast<nonref_value_type>(rhs.x), y - static_cast<nonref_value_type>(rhs.y) };
			}
		}
		template<typename OtherT>
		constexpr Vector2<nonref_value_type> operator*(const Vector2<OtherT>& rhs) const
		{
			if constexpr (std::is_same_v<nonref_value_type, Vector2<OtherT>::nonref_value_type>)
			{
				return { x * rhs.x, y * rhs.y };
			}
			else
			{
				return { static_cast<nonref_value_type>(x * rhs.x), static_cast<nonref_value_type>(y * rhs.y) };
			}
		}
		template<typename RhsT>
		constexpr Vector2<nonref_value_type> operator*(const RhsT& rhs) const
		{
			using NonRefRhs = std::remove_reference_t<RhsT>;
			if constexpr (std::is_same_v<nonref_value_type, NonRefRhs> || !info_type::has_arithmetic_values || !std::is_arithmetic_v<NonRefRhs>)
			{
				return { x * rhs, y * rhs };
			}
			else
			{
				return { static_cast<nonref_value_type>(x * rhs), static_cast<nonref_value_type>(y * rhs) };
			}
		}
		template<typename OtherT>
		constexpr Vector2<nonref_value_type> operator/(const Vector2<OtherT>& rhs) const
		{
			if constexpr (std::is_same_v<nonref_value_type, typename Vector2<OtherT>::nonref_value_type>)
			{
				return { x / rhs.x, y / rhs.y };
			}
			else
			{
				return { static_cast<nonref_value_type>(x / rhs.x), static_cast<nonref_value_type>(y / rhs.y) };
			}
		}
		template<typename RhsT>
		constexpr Vector2<nonref_value_type> operator/(const RhsT& rhs) const
		{
			using NonRefRhs = std::remove_reference_t<RhsT>;
			if constexpr (info_type::has_floating_point_values && std::is_arithmetic_v<NonRefRhs>)
			{
				return this->operator*(_value_one() / rhs);
			}
			else
			{
				return { static_cast<nonref_value_type>(x / rhs), static_cast<nonref_value_type>(y / rhs) };
			}
		}
		template<typename OtherT>
		constexpr Vector2<nonref_value_type> operator%(const Vector2<OtherT>& rhs) const
		{
			if constexpr (!(info_type::has_floating_point_values || info_type_t<OtherT>::has_floating_point_values))
			{
				return { x % rhs.x, y % rhs.y };
			}
			else
			{
				static_assert(false, "Attempted to use modulus operator (%) with an EmuMath::Vector2 which stores incompatible floating point values.");
			}
		}
		template<typename RhsT>
		constexpr Vector2<nonref_value_type> operator%(const RhsT& rhs) const
		{
			if constexpr (!(info_type::has_floating_point_values || std::is_floating_point_v<RhsT>))
			{
				return { x % rhs, y % rhs };
			}
			else
			{
				static_assert(false, "Attempted to use modulus operator (%) with an EmuMath::Vector2 which stores incompatible floating point values.");
			}
		}
#pragma endregion

#pragma region BITWISE_CONST_OPERATORS
		template<typename OtherT>
		constexpr Vector2<nonref_value_type> operator&(const Vector2<OtherT>& rhs) const
		{
			if constexpr (info_type::has_integral_values && info_type_t<OtherT>::has_integral_values)
			{
				if constexpr (std::is_same_v<nonref_value_type, typename Vector2<OtherT>::nonref_value_type>)
				{
					return { x & rhs.x, y & rhs.y };
				}
				else
				{
					return { x & static_cast<nonref_value_type>(rhs.x), y & static_cast<nonref_value_type>(rhs.y) };
				}
			}
			else
			{
				static_assert(false, "Attempted to use a bitwise AND (&) operation on an EmuMath::Vector2 using non-integral values.");
				return *this;
			}
		}
		template<typename RhsT>
		constexpr Vector2<nonref_value_type> operator&(const RhsT& rhs) const
		{
			using NonRefRhs = std::remove_reference_t<RhsT>;
			if constexpr (info_type::has_integral_values && std::is_integral_v<NonRefRhs>)
			{
				if constexpr (std::is_same_v<nonref_value_type, NonRefRhs>)
				{
					return { x & rhs, y & rhs };
				}
				else
				{
					return { x & static_cast<nonref_value_type>(rhs), y & static_cast<nonref_value_type>(rhs) };
				}
			}
			else
			{
				static_assert(false, "Attempted to use a bitwise AND (&) operation on an EmuMath::Vector2 using non-integral values.");
				return *this;
			}
		}
		template<typename OtherT>
		constexpr Vector2<nonref_value_type> operator|(const Vector2<OtherT>& rhs) const
		{
			if constexpr (info_type::has_integral_values && info_type_t<OtherT>::has_integral_values)
			{
				if constexpr (std::is_same_v<nonref_value_type, typename Vector2<OtherT>::nonref_value_type>)
				{
					return { x | rhs.x, y | rhs.y };
				}
				else
				{
					return { x | static_cast<nonref_value_type>(rhs.x), y | static_cast<nonref_value_type>(rhs.y) };
				}
			}
			else
			{
				static_assert(false, "Attempted to use a bitwise OR (|) operation on an EmuMath::Vector2 using non-integral values.");
				return *this;
			}
		}
		template<typename RhsT>
		constexpr Vector2<nonref_value_type> operator|(const RhsT& rhs) const
		{
			using NonRefRhs = std::remove_reference_t<RhsT>;
			if constexpr (info_type::has_integral_values && std::is_integral_v<NonRefRhs>)
			{
				if constexpr (std::is_same_v<nonref_value_type, NonRefRhs>)
				{
					return { x | rhs, y | rhs };
				}
				else
				{
					return { x | static_cast<nonref_value_type>(rhs), y | static_cast<nonref_value_type>(rhs) };
				}
			}
			else
			{
				static_assert(false, "Attempted to use a bitwise OR (|) operation on an EmuMath::Vector2 using non-integral values.");
				return *this;
			}
		}
		template<typename OtherT>
		constexpr Vector2<nonref_value_type> operator^(const Vector2<OtherT>& rhs) const
		{
			if constexpr (info_type::has_integral_values && info_type_t<OtherT>::has_integral_values)
			{
				if constexpr (std::is_same_v<nonref_value_type, typename Vector2<OtherT>::nonref_value_type>)
				{
					return { x ^ rhs.x, y ^ rhs.y };
				}
				else
				{
					return { x ^ static_cast<nonref_value_type>(rhs.x), y ^ static_cast<nonref_value_type>(rhs.y) };
				}
			}
			else
			{
				static_assert(false, "Attempted to use a bitwise XOR (^) operation on an EmuMath::Vector2 using non-integral values.");
				return *this;
			}
		}
		template<typename RhsT>
		constexpr Vector2<nonref_value_type> operator^(const RhsT& rhs) const
		{
			using NonRefRhs = std::remove_reference_t<RhsT>;
			if constexpr (info_type::has_integral_values && std::is_integral_v<NonRefRhs>)
			{
				if constexpr (std::is_same_v<nonref_value_type, NonRefRhs>)
				{
					return { x ^ rhs, y ^ rhs };
				}
				else
				{
					return { x ^ static_cast<nonref_value_type>(rhs), y ^ static_cast<nonref_value_type>(rhs) };
				}
			}
			else
			{
				static_assert(false, "Attempted to use a bitwise XOR (^) operation on an EmuMath::Vector2 using non-integral values.");
				return *this;
			}
		}
		template<typename OtherT>
		constexpr Vector2<nonref_value_type> operator<<(const Vector2<OtherT>& rhs) const
		{
			if constexpr (info_type::has_integral_values && info_type_t<OtherT>::has_integral_values)
			{
				return { x << rhs.x, y << rhs.y };
			}
			else
			{
				static_assert(false, "Attempted to use a bitwise left shift (<<) operation on an EmuMath::Vector2 using non-integral values.");
				return *this;
			}
		}
		template<typename RhsT>
		constexpr Vector2<nonref_value_type> operator<<(const RhsT& rhs) const
		{
			using NonRefRhs = std::remove_reference_t<RhsT>;
			if constexpr (info_type::has_integral_values && std::is_integral_v<NonRefRhs>)
			{
				return { x << rhs, y << rhs };
			}
			else
			{
				static_assert(false, "Attempted to use a bitwise left shift (<<) operation on an EmuMath::Vector2 using non-integral values.");
				return *this;
			}
		}
		template<typename OtherT>
		constexpr Vector2<nonref_value_type> operator>>(const Vector2<OtherT>& rhs) const
		{
			if constexpr (info_type::has_integral_values && info_type_t<OtherT>::has_integral_values)
			{
				return { x >> rhs.x, y >> rhs.y };
			}
			else
			{
				static_assert(false, "Attempted to use a bitwise right shift (>>) operation on an EmuMath::Vector2 using non-integral values.");
				return *this;
			}
		}
		template<typename RhsT>
		constexpr Vector2<nonref_value_type> operator>>(const RhsT& rhs) const
		{
			if constexpr (info_type::has_integral_values && std::is_integral_v<RhsT>)
			{
				return { x >> rhs, y >> rhs };
			}
			else
			{
				static_assert(false, "Attempted to use a bitwise right shift (>>) operation on an EmuMath::Vector2 using non-integral values.");
				return *this;
			}
		}
		constexpr Vector2<nonref_value_type> operator~() const
		{
			if constexpr (info_type::has_integral_values)
			{
				return { ~x, ~y };
			}
			else
			{
				static_assert(false, "Attempted to use a bitwise NOT (~) operation on an EmuMath::Vector2 using non-integral values.");
				return *this;
			}
		}
#pragma endregion

#pragma region BOOLEAN_COMPARISON_OPERATORS
		template<typename OtherT>
		constexpr bool operator==(const Vector2<OtherT>& rhs) const
		{
			return x == rhs.x && y == rhs.y;
		}
		template<typename RhsT>
		constexpr bool operator==(const RhsT& rhs) const
		{
			if constexpr (info_type::has_integral_values)
			{
				return this->SquareMagnitude<std::uint64_t>() == rhs;
			}
			else
			{
				return this->SquareMagnitude<long double>() == rhs;
			}
		}
		template<typename OtherT>
		constexpr bool operator!=(const Vector2<OtherT>& rhs) const
		{
			return x != rhs.x || y != rhs.y;
		}
		template<typename RhsT>
		constexpr bool operator!=(const RhsT& rhs) const
		{
			if constexpr (info_type::has_integral_values)
			{
				return this->SquareMagnitude<std::uint64_t>() != rhs;
			}
			else
			{
				return this->SquareMagnitude<long double>() != rhs;
			}
		}
		template<typename OtherT>
		constexpr bool operator>(const Vector2<OtherT>& rhs) const
		{
			if constexpr (info_type::has_integral_values && info_type_t<OtherT>::has_integral_values)
			{
				return SquareMagnitude<std::uint64_t>() > rhs.SquareMagnitude<std::uint64_t>();
			}
			else
			{
				return SquareMagnitude<long double>() > rhs.SquareMagnitude<long double>();
			}
		}
		template<typename RhsT>
		constexpr bool operator>(const RhsT& rhs) const
		{
			if constexpr (info_type::has_integral_values)
			{
				return this->SquareMagnitude<std::uint64_t>() > rhs;
			}
			else
			{
				return this->SquareMagnitude<long double>() > rhs;
			}
		}
		template<typename OtherT>
		constexpr bool operator<(const Vector2<OtherT>& rhs) const
		{
			if constexpr (info_type::has_integral_values && info_type_t<OtherT>::has_integral_values)
			{
				return SquareMagnitude<std::uint64_t>() < rhs.SquareMagnitude<std::uint64_t>();
			}
			else
			{
				return SquareMagnitude<long double>() < rhs.SquareMagnitude<long double>();
			}
		}
		template<typename RhsT>
		constexpr bool operator<(const RhsT& rhs) const
		{
			if constexpr (info_type::has_integral_values)
			{
				return this->SquareMagnitude<std::uint64_t>() < rhs;
			}
			else
			{
				return this->SquareMagnitude<long double>() < rhs;
			}
		}
		template<typename OtherT>
		constexpr bool operator>=(const Vector2<OtherT>& rhs) const
		{
			if constexpr (info_type::has_integral_values && info_type_t<OtherT>::has_integral_values)
			{
				return SquareMagnitude<std::uint64_t>() >= rhs.SquareMagnitude<std::uint64_t>();
			}
			else
			{
				return SquareMagnitude<long double>() >= rhs.SquareMagnitude<long double>();
			}
		}
		template<typename RhsT>
		constexpr bool operator>=(const RhsT& rhs) const
		{
			if constexpr (info_type::has_integral_values)
			{
				return this->SquareMagnitude<std::uint64_t>() >= rhs;
			}
			else
			{
				return this->SquareMagnitude<long double>() >= rhs;
			}
		}
		template<typename OtherT>
		constexpr bool operator<=(const Vector2<OtherT>& rhs) const
		{
			if constexpr (info_type::has_integral_values && info_type_t<OtherT>::has_integral_values)
			{
				return SquareMagnitude<std::uint64_t>() <= rhs.SquareMagnitude<std::uint64_t>();
			}
			else
			{
				return SquareMagnitude<long double>() <= rhs.SquareMagnitude<long double>();
			}
		}
		template<typename RhsT>
		constexpr bool operator<=(const RhsT& rhs) const
		{
			if constexpr (info_type::has_integral_values)
			{
				return this->SquareMagnitude<std::uint64_t>() <= rhs;
			}
			else
			{
				return this->SquareMagnitude<long double>() <= rhs;
			}
		}
#pragma endregion

#pragma region ASSIGNMENT_OPERATORS
		template<typename OtherT>
		constexpr Vector2<value_type>& operator=(const Vector2<OtherT>& rhs)
		{
			if constexpr (std::is_same_v<nonref_value_type, typename Vector2<OtherT>::nonref_value_type>)
			{
				x = rhs.x;
				y = rhs.y;
			}
			else
			{
				x = static_cast<nonref_value_type>(rhs.x);
				y = static_cast<nonref_value_type>(rhs.y);
			}
			return *this;
		}
#pragma endregion

#pragma region BOOLEAN_PER_ELEMENT_COMPARISON_FUNCTIONS
		template<typename OtherT>
		constexpr Vector2<bool> CompareElementsEqual(const Vector2<OtherT>& rhs) const
		{
			return { x == rhs.x, y == rhs.y };
		}
		template<typename OtherT>
		constexpr Vector2<bool> CompareElementsNotEqual(const Vector2<OtherT>& rhs) const
		{
			return { x != rhs.x, y != rhs.y };
		}
		template<typename OtherT>
		constexpr Vector2<bool> CompareElementsGreater(const Vector2<OtherT>& rhs) const
		{
			return { x > rhs.x, y > rhs.y };
		}
		template<typename OtherT>
		constexpr Vector2<bool> CompareElementsLess(const Vector2<OtherT>& rhs) const
		{
			return { x < rhs.x, y < rhs.y };
		}
		template<typename OtherT>
		constexpr Vector2<bool> CompareElementsGreaterEqual(const Vector2<OtherT>& rhs) const
		{
			return { x >= rhs.x, y >= rhs.y };
		}
		template<typename OtherT>
		constexpr Vector2<bool> CompareElementsLessEqual(const Vector2<OtherT>& rhs) const
		{
			return { x <= rhs.x, y <= rhs.y };
		}
#pragma endregion

#pragma region SHUFFLES
		template<std::size_t X_, std::size_t Y_>
		constexpr Vector2<nonref_value_type> AsShuffled() const
		{
			return { at<X_>(), at<Y_>() };
		}
		Vector2<nonref_value_type> AsShuffled(const std::size_t x_, const std::size_t y_) const
		{
			return { at(x_), at(y_) };
		}
		template<std::size_t X_, std::size_t Y_>
		constexpr Vector2<ref_value_type> ShuffledReference()
		{
			return { at<X_>(), at<Y_>() };
		}
		template<std::size_t X_, std::size_t Y_>
		constexpr Vector2<ref_value_type> ShuffledReference() const
		{
			return { at<X_>(), at<Y_>() };
		}
		Vector2<ref_value_type> ShuffledReference(const std::size_t x_, const std::size_t y_)
		{
			return { at(x_), at(y_) };
		}
		Vector2<const ref_value_type> ShuffledReference(const std::size_t x_, const std::size_t y_) const
		{
			return { at(x_), at(y_) };
		}
#pragma endregion

#pragma region SETS
		template<typename X_, typename Y_>
		void SetAll(const X_& x_, const Y_& y_)
		{
			_set_individual_value<0, X_>(x_);
			_set_individual_value<1, Y_>(y_);
		}

		template<typename T_>
		void SetAll(const T_& val_)
		{
			if constexpr (std::is_same_v<nonref_value_type, std::remove_reference_t<T_>>)
			{
				x = val_;
				y = val_;
			}
			else
			{
				const nonref_value_type castVal = static_cast<nonref_value_type>(val_);
				x = castVal;
				y = castVal;
			}
		}
#pragma endregion

#pragma region VECTOR_OPERATIONS
		float Magnitudef() const
		{
			return sqrtf(SquareMagnitude<float>());
		}
		double Magnituded() const
		{
			return sqrt(SquareMagnitude<double>());
		}
		long double Magnitudeld() const
		{
			return sqrt(SquareMagnitude<long double>());
		}
		template<typename OutT = nonref_value_type>
		constexpr OutT SquareMagnitude() const
		{
			if constexpr (std::is_same_v<nonref_value_type, OutT>)
			{
				return x * x + y * y;
			}
			else
			{
				if constexpr (sizeof(OutT) > sizeof(nonref_value_type))
				{
					return (static_cast<OutT>(x) * x) + (static_cast<OutT>(y) * y);
				}
				else
				{
					return static_cast<OutT>(x * x + y * y);
				}
			}
		}
		template<typename RhsT, typename OutT = nonref_value_type>
		constexpr OutT DotProduct(const Vector2<RhsT>& rhs) const
		{
			if constexpr (std::is_same_v<nonref_value_type, typename info_type_t<RhsT>::nonref_value_type>)
			{
				if constexpr (std::is_same_v<nonref_value_type, OutT>)
				{
					return x * rhs.x + y * rhs.y;
				}
				else
				{
					if constexpr (sizeof(OutT) > sizeof(nonref_value_type))
					{
						return (static_cast<OutT>(x) * rhs.x) + (static_cast<OutT>(y) * rhs.y);
					}
					else
					{
						return static_cast<OutT>(x * rhs.x + y * rhs.y);
					}
				}
			}
			else
			{
				if constexpr (sizeof(OutT) > sizeof(nonref_value_type))
				{
					return (static_cast<OutT>(x) * rhs.x) + (static_cast<OutT>(y) * rhs.y);
				}
				else
				{
					return static_cast<OutT>(x * static_cast<nonref_value_type>(rhs.x) + y * static_cast<nonref_value_type>(rhs.y));
				}
			}
		}
		Vector2<float> AsNormalisedf() const
		{
			const float reciprocal = 1.0f / Magnitudef();
			if constexpr (std::is_same_v<nonref_value_type, float>)
			{
				return { x * reciprocal, y * reciprocal };
			}
			else
			{
				return { static_cast<float>(x * reciprocal), static_cast<float>(y * reciprocal) };
			}
		}
		Vector2<double> AsNormalisedd() const
		{
			const double reciprocal = 1.0f / Magnituded();
			if constexpr (std::is_same_v<nonref_value_type, double>)
			{
				return { x * reciprocal, y * reciprocal };
			}
			else
			{
				return { static_cast<double>(x * reciprocal), static_cast<double>(y * reciprocal) };
			}
		}
		Vector2<long double> AsNormalisedld() const
		{
			const long double reciprocal = 1.0f / Magnituded();
			if constexpr (std::is_same_v<nonref_value_type, long double>)
			{
				return { x * reciprocal, y * reciprocal };
			}
			else
			{
				return { static_cast<long double>(x * reciprocal), static_cast<long double>(y * reciprocal) };
			}
		}
#pragma endregion

		value_type x, y;

	private:
		template<std::size_t Index, typename T_>
		constexpr void _set_individual_value(const T_& val_)
		{
			if constexpr (std::is_same_v<nonref_value_type, std::remove_reference_t<T_>>)
			{
				at<Index>() = val_;
			}
			else
			{
				at<Index>() = static_cast<nonref_value_type>(val_);
			}
		}

		static constexpr value_type _value_one()
		{
			if constexpr (info_type::has_integral_values)
			{
				return 1;
			}
			else if constexpr (info_type::has_floating_point_values)
			{
				if constexpr (std::is_same_v<float, value_type>)
				{
					return 1.0f;
				}
				else
				{
					return 1.0;
				}
			}
			else
			{
				static_assert(false, "Attempted to use _value_one for an EmuMath::Vector2 variant which does not have a solid representation of 1.");
			}
		}
	};
}

#endif
