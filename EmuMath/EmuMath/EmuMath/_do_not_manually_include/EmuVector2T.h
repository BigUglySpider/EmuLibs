#ifndef EMU_MATH_VECTOR_2_T_H_INC_
#define EMU_MATH_VECTOR_2_T_H_INC_

#include "EmuVectorInfo.h"
#include "../../EmuCore/TMPHelpers/Functors.h"
#include "../../EmuCore/TMPHelpers/TypeComparators.h"
#include "../../EmuCore/TMPHelpers/TypeConvertors.h"
#include "../../EmuMath/_do_not_manually_include/EmuVectorTMPHelpers.h"
#include <exception>

namespace EmuMath
{
	template<typename T>
	struct Vector3;
	template<typename T>
	struct Vector4;

	/// <summary> Generic Vector type which contains 2 elements of the provided type, representing the X- and Y-axes respectively. </summary>
	/// <typeparam name="T">Type to store within the Vector.</typeparam>
	template<typename T>
	struct Vector2
	{
#pragma region ALIASES_AND_STATIC_CONSTANT_EXPRESSIONS
	protected:
		/// <summary> Templatised type containing info for all sizes of vectors containing the passed type T_. </summary>
		/// <typeparam name="T_">Type contained within the vector for which the info is required.</typeparam>
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
		/// <summary> The constant reference variant of value types stored within this vector. </summary>
		using const_ref_value_type = typename info_type::const_ref_value_type;
		/// <summary> The non-qualified, non-reference variant of the value types stored within this vector. </summary>
		using nonref_value_type_without_qualifiers = typename info_type::nonref_value_type_without_qualifiers;
		/// <summary> The default floating point value used by relevant functions for this vector type. </summary>
		using default_floating_point = typename info_type::default_floating_point;

		/// <summary> The number of elements contained within this vector. </summary>
		/// <returns>2</returns>
		static constexpr std::size_t size()
		{
			return 2;
		}
#pragma endregion

#pragma region CONSTRUCTORS
		/// <summary> Constructs a 2-dimensional Vector with its x and y elements set to their default constructors. </summary>
		constexpr Vector2() :
			x(),
			y()
		{
		}
		/// <summary> Constructs a 2-dimensional Vector with its x and y elements set to copies of the respective passed values. </summary>
		/// <param name="x_">Value to copy to the Vector's x component.</param>
		/// <param name="y_">Value to copy to the Vector's y component.</param>
		constexpr Vector2(const value_type& x_, const value_type& y_) :
			x(x_),
			y(y_)
		{
		}
		/// <summary> Constructs a 2-dimensional Vector with its x and y elements set to copies of the respective passed values after a static_cast. </summary>
		/// <typeparam name="X_">Non value_type type used for the passed x_ value.</typeparam>
		/// <typeparam name="Y_">Non value_type type used for the passed y_ value.</typeparam>
		/// <param name="x_">Value to cast and copy to the Vector's x component.</param>
		/// <param name="y_">Value to cast and copy to the Vector's y component.</param>
		template<typename X_, typename Y_>
		constexpr Vector2(const X_& x_, const Y_& y_) :
			x(static_cast<value_type>(x_)),
			y(static_cast<value_type>(y_))
		{
		}
		/// <summary> Constructs a 2-dimensional Vector with its x set to a copy of the passed x_ value after a static_cast, and y a direct copy of the passed y_ value. </summary>
		/// <typeparam name="X_">Non value_type type used for the passed x_ value.</typeparam>
		/// <param name="x_">Value to cast and copy to the Vector's x component.</param>
		/// <param name="y_">Value to copy to the Vector's y component.</param>
		template<typename X_>
		constexpr Vector2(const X_& x_, const value_type& y_) :
			x(static_cast<value_type>(x_)),
			y(y_)
		{
		}
		/// <summary> Constructs a 2-dimensional Vector with its x set to a copy of the passed x_ value, and y a copy of the passed y_ value after a static_cast. </summary>
		/// <typeparam name="Y_">Non value_type type used for the passed y_ value.</typeparam>
		/// <param name="x_">Value to copy to the Vector's x component.</param>
		/// <param name="y_">Value to cast and copy to the Vector's y component.</param>
		template<typename Y_>
		constexpr Vector2(const value_type& x_, const Y_& y_) :
			x(x_),
			y(static_cast<value_type>(y_))
		{
		}
		/// <summary> Constructs a 2-dimensional vector with its x and y components set to copies of the passed vector's respective components, performing casts where needed. </summary>
		/// <typeparam name="OtherT">The contained type within the passed Vector2.</typeparam>
		/// <param name="toCopy">Vector to copy the elements of.</param>
		template<typename OtherT>
		constexpr Vector2(const Vector2<OtherT>& toCopy) :
			Vector2(toCopy.x, toCopy.y)
		{
		}
		/// <summary> Constructs a 2-dimensional vector with its x and y components set to copies of the passed vector's respective components, performing casts where needed. </summary>
		/// <typeparam name="OtherT">The contained type within the passed Vector2.</typeparam>
		/// <param name="toCopy">Vector to copy the elements of.</param>
		template<typename OtherT>
		constexpr Vector2(Vector2<OtherT>& toCopy) :
			Vector2(toCopy.x, toCopy.y)
		{
		}
		/// <summary> Constructs a 2-dimensional vector with its x and y components set to copies of the passed vector's respective components, performing casts where needed. </summary>
		/// <typeparam name="OtherT">The contained type within the passed Vector3.</typeparam>
		/// <param name="toCopy">Vector to copy the elements of.</param>
		template<typename OtherT>
		explicit constexpr Vector2(const EmuMath::Vector3<OtherT>& toCopy) :
			Vector2(toCopy.x, toCopy.y)
		{
		}
		/// <summary> Constructs a 2-dimensional vector with its x and y components set to copies of the passed vector's respective components, performing casts where needed. </summary>
		/// <typeparam name="OtherT">The contained type within the passed Vector3.</typeparam>
		/// <param name="toCopy">Vector to copy the elements of.</param>
		template<typename OtherT>
		explicit constexpr Vector2(EmuMath::Vector3<OtherT>& toCopy) :
			Vector2(toCopy.x, toCopy.y)
		{
		}
#pragma endregion

#pragma region RANDOM_ACCESS
		/// <summary>
		///	<para> Access the element of this vector at the provided index, where x is index 0 and y is index 1. </para>
		/// <para> If possible, it is recommended to use the templatised at function instead. </para>
		/// </summary>
		/// <param name="index">Index of the element to access.</param>
		/// <returns>Reference to the element at the provided index.</returns>
		ref_value_type operator[](const std::size_t index)
		{
			return at(index);
		}
		/// <summary>
		///	<para> Access the element of this vector at the provided index, where x is index 0 and y is index 1. </para>
		/// <para> If possible, it is recommended to use the templatised at function instead. </para>
		/// </summary>
		/// <param name="index">Index of the element to access.</param>
		/// <returns>Constant reference to the element at the provided index.</returns>
		const_ref_value_type operator[](const std::size_t index) const
		{
			return at(index);
		}
		/// <summary>
		///	<para> Access the element of this vector at the provided index, where x is index 0 and y is index 1. </para>
		/// <para> If possible, it is recommended to use the templatised version of this function. </para>
		/// </summary>
		/// <param name="index">Index of the element to access.</param>
		/// <returns>Reference to the element at the provided index.</returns>
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
		/// <summary>
		///	<para> Access the element of this vector at the provided index, where x is index 0 and y is index 1. </para>
		/// <para> If possible, it is recommended to use the templatised version of this function. </para>
		/// </summary>
		/// <param name="index">Index of the element to access.</param>
		/// <returns>Constant reference to the element at the provided index.</returns>
		const_ref_value_type at(std::size_t index) const
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
		/// <summary> Access the element of this vector at the provided index, where x is index 0 and y is index 1. </summary>
		/// <returns>Reference to the element at the provided index.</returns>
		template<std::size_t Index_>
		constexpr ref_value_type at()
		{
			if constexpr (Index_ == 0)
			{
				return x;
			}
			else if constexpr (Index_ == 1)
			{
				return y;
			}
			else
			{
				static_assert(false, "Attempted to access an EmuMath::Vector2 element by an index which does not exist.");
			}
		}
		/// <summary> Access the element of this vector at the provided index, where x is index 0 and y is index 1. </summary>
		/// <returns>Constant reference to the element at the provided index.</returns>
		template<std::size_t Index_>
		constexpr const_ref_value_type at() const
		{
			if constexpr (Index_ == 0)
			{
				return x;
			}
			else if constexpr (Index_ == 1)
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
		template<typename RhsT>
		constexpr Vector2<nonref_value_type> operator+(const Vector2<RhsT>& rhs) const
		{
			return this->AsAdded<size(), nonref_value_type, RhsT>(rhs);
		}
		template<typename RhsT>
		constexpr Vector2<nonref_value_type> operator+(const Vector3<RhsT>& rhs) const
		{
			return this->AsAdded<size(), nonref_value_type, RhsT>(rhs);
		}

		template<typename RhsT>
		constexpr Vector2<nonref_value_type> operator-(const Vector2<RhsT>& rhs) const
		{
			return this->AsSubtracted<size(), nonref_value_type, RhsT>(rhs);
		}
		template<typename RhsT>
		constexpr Vector2<nonref_value_type> operator-(const Vector3<RhsT>& rhs) const
		{
			return this->AsSubtracted<size(), nonref_value_type, RhsT>(rhs);
		}
		constexpr Vector2<nonref_value_type> operator-() const
		{
			return this->AsReversed<nonref_value_type>();
		}

		template<typename RhsT>
		constexpr Vector2<nonref_value_type> operator*(const Vector2<RhsT>& rhs) const
		{
			return this->AsMultiplied<size(), nonref_value_type, RhsT>(rhs);
		}
		template<typename RhsT>
		constexpr Vector2<nonref_value_type> operator*(const Vector3<RhsT>& rhs) const
		{
			return this->AsMultiplied<size(), nonref_value_type, RhsT>(rhs);
		}
		template<typename RhsT>
		constexpr Vector2<nonref_value_type> operator*(const RhsT& rhs) const
		{
			return this->AsMultiplied<size(), nonref_value_type, RhsT>(rhs);
		}

		template<typename RhsT>
		constexpr Vector2<nonref_value_type> operator/(const Vector2<RhsT>& rhs) const
		{
			return this->AsDivided<size(), nonref_value_type, RhsT>(rhs);
		}
		template<typename RhsT>
		constexpr Vector2<nonref_value_type> operator/(const Vector3<RhsT>& rhs) const
		{
			return this->AsDivided<size(), nonref_value_type, RhsT>(rhs);
		}
		template<typename RhsT>
		constexpr Vector2<nonref_value_type> operator/(const RhsT& rhs) const
		{
			return this->AsDivided<size(), nonref_value_type, RhsT>(rhs);
		}

		template<typename RhsT>
		constexpr Vector2<nonref_value_type> operator%(const Vector2<RhsT>& rhs) const
		{
			return this->AsMod<size(), nonref_value_type, RhsT>(rhs);
		}
		template<typename RhsT>
		constexpr Vector2<nonref_value_type> operator%(const Vector3<RhsT>& rhs) const
		{
			return this->AsMod<size(), nonref_value_type, RhsT>(rhs);
		}
		template<typename RhsT>
		constexpr Vector2<nonref_value_type> operator%(const RhsT& rhs) const
		{
			return this->AsMod<size(), nonref_value_type, RhsT>(rhs);
		}
#pragma endregion

#pragma region BITWISE_CONST_OPERATORS
		template<typename OtherT>
		constexpr Vector2<nonref_value_type> operator&(const Vector2<OtherT>& rhs) const
		{
			return this->AsBitwiseAnded<size(), nonref_value_type, OtherT>(rhs);
		}
		template<typename OtherT>
		constexpr Vector2<nonref_value_type> operator&(const Vector3<OtherT>& rhs) const
		{
			return this->AsBitwiseAnded<size(), nonref_value_type, OtherT>(rhs);
		}
		template<typename OtherT>
		constexpr Vector2<nonref_value_type> operator&(const Vector4<OtherT>& rhs) const
		{
			return this->AsBitwiseAnded<size(), nonref_value_type, OtherT>(rhs);
		}
		template<typename RhsT>
		constexpr Vector2<nonref_value_type> operator&(const RhsT& rhs) const
		{
			return this->AsBitwiseAnded<size(), nonref_value_type, RhsT>(rhs);
		}
		template<typename OtherT>
		constexpr Vector2<nonref_value_type> operator|(const Vector2<OtherT>& rhs) const
		{
			return this->AsBitwiseOred<size(), nonref_value_type, OtherT>(rhs);
		}
		template<typename OtherT>
		constexpr Vector2<nonref_value_type> operator|(const Vector3<OtherT>& rhs) const
		{
			return this->AsBitwiseOred<size(), nonref_value_type, OtherT>(rhs);
		}
		template<typename OtherT>
		constexpr Vector2<nonref_value_type> operator|(const Vector4<OtherT>& rhs) const
		{
			return this->AsBitwiseOred<size(), nonref_value_type, OtherT>(rhs);
		}
		template<typename RhsT>
		constexpr Vector2<nonref_value_type> operator|(const RhsT& rhs) const
		{
			return this->AsBitwiseOred<size(), nonref_value_type, RhsT>(rhs);
		}
		template<typename OtherT>
		constexpr Vector2<nonref_value_type> operator^(const Vector2<OtherT>& rhs) const
		{
			return this->AsBitwiseXored<size(), nonref_value_type, OtherT>(rhs);
		}
		template<typename OtherT>
		constexpr Vector2<nonref_value_type> operator^(const Vector3<OtherT>& rhs) const
		{
			return this->AsBitwiseXored<size(), nonref_value_type, OtherT>(rhs);
		}
		template<typename OtherT>
		constexpr Vector2<nonref_value_type> operator^(const Vector4<OtherT>& rhs) const
		{
			return this->AsBitwiseXored<size(), nonref_value_type, OtherT>(rhs);
		}
		template<typename RhsT>
		constexpr Vector2<nonref_value_type> operator^(const RhsT& rhs) const
		{
			return this->AsBitwiseXored<size(), nonref_value_type, RhsT>(rhs);
		}
		template<typename OtherT>
		constexpr Vector2<nonref_value_type> operator<<(const Vector2<OtherT>& rhs) const
		{
			return this->AsLeftShiftedPerElement<size(), nonref_value_type, OtherT>(rhs);
		}
		template<typename OtherT>
		constexpr Vector2<nonref_value_type> operator<<(const Vector3<OtherT>& rhs) const
		{
			return this->AsLeftShiftedPerElement<size(), nonref_value_type, OtherT>(rhs);
		}
		template<typename OtherT>
		constexpr Vector2<nonref_value_type> operator<<(const Vector4<OtherT>& rhs) const
		{
			return this->AsLeftShiftedPerElement<size(), nonref_value_type, OtherT>(rhs);
		}
		template<typename RhsT>
		constexpr Vector2<nonref_value_type> operator<<(const RhsT& rhs) const
		{
			return this->AsLeftShiftedPerElement<size(), nonref_value_type, RhsT>(rhs);
		}
		template<typename OtherT>
		constexpr Vector2<nonref_value_type> operator>>(const Vector2<OtherT>& rhs) const
		{
			return this->AsRightShiftedPerElement<size(), nonref_value_type, OtherT>(rhs);
		}
		template<typename OtherT>
		constexpr Vector2<nonref_value_type> operator>>(const Vector3<OtherT>& rhs) const
		{
			return this->AsRightShiftedPerElement<size(), nonref_value_type, OtherT>(rhs);
		}
		template<typename OtherT>
		constexpr Vector2<nonref_value_type> operator>>(const Vector4<OtherT>& rhs) const
		{
			return this->AsRightShiftedPerElement<size(), nonref_value_type, OtherT>(rhs);
		}
		template<typename RhsT>
		constexpr Vector2<nonref_value_type> operator>>(const RhsT& rhs) const
		{
			return this->AsRightShiftedPerElement<size(), nonref_value_type, RhsT>(rhs);
		}
		constexpr Vector2<nonref_value_type> operator~() const
		{
			return this->AsNot<size(), nonref_value_type>();
		}
#pragma endregion

#pragma region ARITHMETIC_NONCONST_OPERATORS
		template<typename OtherT>
		constexpr Vector2<value_type>& operator+=(const Vector2<OtherT>& rhs)
		{
			if constexpr (!info_type::has_const_values)
			{
				if constexpr (std::is_same_v<nonref_value_type_without_qualifiers, typename Vector2<OtherT>::nonref_value_type_without_qualifiers>)
				{
					x += rhs.x;
					y += rhs.y;
				}
				else
				{
					x += static_cast<nonref_value_type>(rhs.x);
					y += static_cast<nonref_value_type>(rhs.y);
				}
			}
			else
			{
				static_assert(false, "Attempted to perform a non-const function (+=) on an EmuMath::Vector2 which contains constant values.");
			}
			return *this;
		}
		template<typename OtherT>
		constexpr Vector2<value_type>& operator-=(const Vector2<OtherT>& rhs)
		{
			if constexpr (!info_type::has_const_values)
			{
				if constexpr (std::is_same_v<nonref_value_type_without_qualifiers, typename Vector2<OtherT>::nonref_value_type_without_qualifiers>)
				{
					x -= rhs.x;
					y -= rhs.y;
				}
				else
				{
					x -= static_cast<nonref_value_type>(rhs.x);
					y -= static_cast<nonref_value_type>(rhs.y);
				}
			}
			else
			{
				static_assert(false, "Attempted to perform a non-const function (-=) on an EmuMath::Vector2 which contains constant values.");
			}
			return *this;
		}
		template<typename OtherT>
		constexpr Vector2<value_type>& operator*=(const Vector2<OtherT>& rhs)
		{
			if constexpr (!info_type::has_const_values)
			{
				if constexpr (std::is_same_v<nonref_value_type_without_qualifiers, typename Vector2<OtherT>::nonref_value_type_without_qualifiers>)
				{
					x *= rhs.x;
					y *= rhs.y;
				}
				else
				{
					x *= static_cast<nonref_value_type>(rhs.x);
					y *= static_cast<nonref_value_type>(rhs.y);
				}
			}
			else
			{
				static_assert(false, "Attempted to perform a non-const function (*=) on an EmuMath::Vector2 which contains constant values.");
			}
			return *this;
		}
		template<typename RhsT>
		constexpr Vector2<value_type>& operator*=(const RhsT& rhs)
		{
			if constexpr (!info_type::has_const_values)
			{
				if constexpr (std::is_same_v<nonref_value_type_without_qualifiers, typename Vector2<RhsT>::nonref_value_type_without_qualifiers>)
				{
					x *= rhs;
					y *= rhs;
				}
				else
				{
					x *= static_cast<nonref_value_type>(rhs);
					y *= static_cast<nonref_value_type>(rhs);
				}
			}
			else
			{
				static_assert(false, "Attempted to perform a non-const function (*=) on an EmuMath::Vector2 which contains constant values.");
			}
			return *this;
		}
		template<typename OtherT>
		constexpr Vector2<value_type>& operator/=(const Vector2<OtherT>& rhs)
		{
			if constexpr (!info_type::has_const_values)
			{
				if constexpr (std::is_same_v<nonref_value_type_without_qualifiers, typename Vector2<OtherT>::nonref_value_type_without_qualifiers>)
				{
					x /= rhs.x;
					y /= rhs.y;
				}
				else
				{
					x /= static_cast<nonref_value_type>(rhs.x);
					y /= static_cast<nonref_value_type>(rhs.y);
				}
			}
			else
			{
				static_assert(false, "Attempted to perform a non-const function (/=) on an EmuMath::Vector2 which contains constant values.");
			}
			return *this;
		}
		template<typename RhsT>
		constexpr Vector2<value_type>& operator/=(const RhsT& rhs)
		{
			if constexpr (!info_type::has_const_values)
			{
				using NonRefRhs = std::remove_reference_t<RhsT>;
				if constexpr (info_type::has_floating_point_values && std::is_arithmetic_v<NonRefRhs>)
				{
					// Early return from this func, which defers division to a reciprocal multiplication
					return this->operator*=(info_type::value_one / rhs);
				}
				else
				{
					x /= static_cast<nonref_value_type>(rhs.x);
					y /= static_cast<nonref_value_type>(rhs.y);
				}
			}
			else
			{
				static_assert(false, "Attempted to perform a non-const function (/=) on an EmuMath::Vector2 which contains constant values.");
			}
			return *this;
		}
		template<typename OtherT>
		constexpr Vector2<value_type>& operator%=(const Vector2<OtherT>& rhs)
		{
			if constexpr (!info_type::has_const_values)
			{
				if constexpr (!(info_type::has_floating_point_values || info_type_t<OtherT>::has_floating_point_values))
				{
					x %= rhs.x;
					y %= rhs.y;
				}
				else
				{
					static_assert(false, "Attempted to use modulus operator (%) with an EmuMath::Vector2 using incompatible floating point values.");
				}
			}
			else
			{
				static_assert(false, "Attempted to perform a non-const function (%=) on an EmuMath::Vector2 which contains constant values.");
			}
			return *this;
		}
		template<typename RhsT>
		constexpr Vector2<value_type>& operator%=(const RhsT& rhs)
		{
			if constexpr (!info_type::has_const_values)
			{
				if constexpr (!(info_type::has_floating_point_values || std::is_floating_point_v<RhsT>))
				{
					x %= rhs;
					y %= rhs;
				}
				else
				{
					static_assert(false, "Attempted to use modulus operator (%) with an EmuMath::Vector2 using incompatible floating point values.");
				}
			}
			else
			{
				static_assert(false, "Attempted to perform a non-const function (%=) on an EmuMath::Vector2 which contains constant values.");
			}
			return *this;
		}
#pragma endregion

#pragma region BITWISE_NONCONST_OPERATORS
		template<typename OtherT>
		constexpr Vector2<value_type>& operator&=(const Vector2<OtherT>& rhs)
		{
			if constexpr (!info_type::has_const_values)
			{
				if constexpr (info_type::has_integral_values && info_type_t<OtherT>::has_integral_values)
				{
					if constexpr (std::is_same_v<nonref_value_type_without_qualifiers, typename Vector2<OtherT>::nonref_value_type_without_qualifiers>)
					{
						x &= rhs.x;
						y &= rhs.y;
					}
					else
					{
						x &= static_cast<nonref_value_type>(rhs.x);
						y &= static_cast<nonref_value_type>(rhs.y);
					}
				}
				else
				{
					static_assert(false, "Attempted to use a bitwise AND (&) operation on an EmuMath::Vector2 using non-integral values.");
				}
			}
			else
			{
				static_assert(false, "Attempted to perform a non-const function (&=) on an EmuMath::Vector2 which contains constant values.");
			}
			return *this;
		}
		template<typename RhsT>
		constexpr Vector2<value_type>& operator&=(const RhsT& rhs)
		{
			using NonRefRhs = std::remove_reference_t<RhsT>;
			if constexpr (!info_type::has_const_values)
			{
				if constexpr (info_type::has_integral_values && std::is_integral_v<NonRefRhs>)
				{
					if constexpr (std::is_same_v<nonref_value_type_without_qualifiers, NonRefRhs>)
					{
						x &= rhs;
						y &= rhs;
					}
					else
					{
						const NonRefRhs castRhs = static_cast<nonref_value_type>(rhs);
						x &= static_cast<nonref_value_type>(castRhs);
						y &= static_cast<nonref_value_type>(castRhs);
					}
				}
				else
				{
					static_assert(false, "Attempted to use a bitwise AND (&) operation on an EmuMath::Vector2 using non-integral values.");
				}
			}
			else
			{
				static_assert(false, "Attempted to perform a non-const function (&=) on an EmuMath::Vector2 which contains constant values.");
			}
			return *this;
		}
		template<typename OtherT>
		constexpr Vector2<value_type>& operator|=(const Vector2<OtherT>& rhs)
		{
			if constexpr (!info_type::has_const_values)
			{
				if constexpr (info_type::has_integral_values && info_type_t<OtherT>::has_integral_values)
				{
					if constexpr (std::is_same_v<nonref_value_type_without_qualifiers, typename Vector2<OtherT>::nonref_value_type_without_qualifiers>)
					{
						x |= rhs.x;
						y |= rhs.y;
					}
					else
					{
						x |= static_cast<nonref_value_type>(rhs.x);
						y |= static_cast<nonref_value_type>(rhs.y);
					}
				}
				else
				{
					static_assert(false, "Attempted to use a bitwise AND (&) operation on an EmuMath::Vector2 using non-integral values.");
				}
			}
			else
			{
				static_assert(false, "Attempted to perform a non-const function (|=) on an EmuMath::Vector2 which contains constant values.");
			}
			return *this;
		}
		template<typename RhsT>
		constexpr Vector2<value_type>& operator|=(const RhsT& rhs)
		{
			using NonRefRhs = std::remove_reference_t<RhsT>;
			if constexpr (!info_type::has_const_values)
			{
				if constexpr (info_type::has_integral_values && std::is_integral_v<NonRefRhs>)
				{
					if constexpr (std::is_same_v<nonref_value_type_without_qualifiers, NonRefRhs>)
					{
						x |= rhs;
						y |= rhs;
					}
					else
					{
						const NonRefRhs castRhs = static_cast<nonref_value_type>(rhs);
						x |= static_cast<nonref_value_type>(castRhs);
						y |= static_cast<nonref_value_type>(castRhs);
					}
				}
				else
				{
					static_assert(false, "Attempted to use a bitwise AND (&) operation on an EmuMath::Vector2 using non-integral values.");
				}
			}
			else
			{
				static_assert(false, "Attempted to perform a non-const function (|=) on an EmuMath::Vector2 which contains constant values.");
			}
			return *this;
		}
		template<typename OtherT>
		constexpr Vector2<value_type>& operator^=(const Vector2<OtherT>& rhs)
		{
			if constexpr (!info_type::has_const_values)
			{
				if constexpr (info_type::has_integral_values && info_type_t<OtherT>::has_integral_values)
				{
					if constexpr (std::is_same_v<nonref_value_type_without_qualifiers, typename Vector2<OtherT>::nonref_value_type_without_qualifiers>)
					{
						x ^= rhs.x;
						y ^= rhs.y;
					}
					else
					{
						x ^= static_cast<nonref_value_type>(rhs.x);
						y ^= static_cast<nonref_value_type>(rhs.y);
					}
				}
				else
				{
					static_assert(false, "Attempted to use a bitwise AND (&) operation on an EmuMath::Vector2 using non-integral values.");
				}
			}
			else
			{
				static_assert(false, "Attempted to perform a non-const function (^=) on an EmuMath::Vector2 which contains constant values.");
			}
			return *this;
		}
		template<typename RhsT>
		constexpr Vector2<value_type>& operator^=(const RhsT& rhs)
		{
			using NonRefRhs = std::remove_reference_t<RhsT>;
			if constexpr (!info_type::has_const_values)
			{
				if constexpr (info_type::has_integral_values && std::is_integral_v<NonRefRhs>)
				{
					if constexpr (std::is_same_v<nonref_value_type_without_qualifiers, NonRefRhs>)
					{
						x ^= rhs;
						y ^= rhs;
					}
					else
					{
						const NonRefRhs castRhs = static_cast<nonref_value_type>(rhs);
						x ^= static_cast<nonref_value_type>(castRhs);
						y ^= static_cast<nonref_value_type>(castRhs);
					}
				}
				else
				{
					static_assert(false, "Attempted to use a bitwise AND (&) operation on an EmuMath::Vector2 using non-integral values.");
				}
			}
			else
			{
				static_assert(false, "Attempted to perform a non-const function (^=) on an EmuMath::Vector2 which contains constant values.");
			}
			return *this;
		}
		template<typename OtherT>
		constexpr Vector2<value_type>& operator<<=(const Vector2<OtherT>& rhs)
		{
			if constexpr (!info_type::has_const_values)
			{
				if constexpr (info_type::has_integral_values && info_type_t<OtherT>::has_integral_values)
				{
					x <<= rhs.x;
					y <<= rhs.y;
				}
				else
				{
					static_assert(false, "Attempted to use a bitwise left shift (<<) operation on an EmuMath::Vector2 using non-integral values.");
				}
			}
			else
			{
				static_assert(false, "Attempted to perform a non-const function (<<=) on an EmuMath::Vector2 which contains constant values.");
			}
			return *this;
		}
		template<typename RhsT>
		constexpr Vector2<value_type>& operator<<=(const RhsT& rhs)
		{
			if constexpr (!info_type::has_const_values)
			{
				if constexpr (info_type::has_integral_values && std::is_integral_v<RhsT>)
				{
					x <<= rhs;
					y <<= rhs;
				}
				else
				{
					static_assert(false, "Attempted to use a bitwise left shift (<<) operation on an EmuMath::Vector2 using non-integral values.");
				}
			}
			else
			{
				static_assert(false, "Attempted to perform a non-const function (<<=) on an EmuMath::Vector2 which contains constant values.");
			}
			return *this;
		}
		template<typename OtherT>
		constexpr Vector2<value_type>& operator>>=(const Vector2<OtherT>& rhs)
		{
			if constexpr (!info_type::has_const_values)
			{
				if constexpr (info_type::has_integral_values && info_type_t<OtherT>::has_integral_values)
				{
					x >>= rhs.x;
					y >>= rhs.y;
				}
				else
				{
					static_assert(false, "Attempted to use a bitwise left shift (<<) operation on an EmuMath::Vector2 using non-integral values.");
				}
			}
			else
			{
				static_assert(false, "Attempted to perform a non-const function (>>=) on an EmuMath::Vector2 which contains constant values.");
			}
			return *this;
		}
		template<typename RhsT>
		constexpr Vector2<value_type>& operator>>=(const RhsT& rhs)
		{
			if constexpr (!info_type::has_const_values)
			{
				if constexpr (info_type::has_integral_values && std::is_integral_v<RhsT>)
				{
					x >>= rhs;
					y >>= rhs;
				}
				else
				{
					static_assert(false, "Attempted to use a bitwise left shift (<<) operation on an EmuMath::Vector2 using non-integral values.");
				}
			}
			else
			{
				static_assert(false, "Attempted to perform a non-const function (>>=) on an EmuMath::Vector2 which contains constant values.");
			}
			return *this;
		}
#pragma endregion

#pragma region BOOLEAN_COMPARISON_OPERATORS
		template<typename OtherT>
		constexpr bool operator==(const Vector2<OtherT>& rhs) const
		{
			return x == rhs.x && y == rhs.y;
		}
		template<typename OtherT>
		constexpr bool operator==(const Vector3<OtherT>& rhs) const
		{
			return x == rhs.x && y == rhs.y && rhs.z == info_type::value_zero;
		}
		template<typename OtherT>
		constexpr bool operator!=(const Vector2<OtherT>& rhs) const
		{
			return x != rhs.x || y != rhs.y;
		}
		template<typename OtherT>
		constexpr bool operator!=(const Vector3<OtherT>& rhs) const
		{
			return x != rhs.x || y != rhs.y || rhs.z != info_type::value_zero;
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
		template<typename OtherT>
		constexpr bool operator>(const Vector3<OtherT>& rhs) const
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
		template<typename OtherT>
		constexpr bool operator<(const Vector3<OtherT>& rhs) const
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
		template<typename OtherT>
		constexpr bool operator>=(const Vector3<OtherT>& rhs) const
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
		template<typename OtherT>
		constexpr bool operator<=(const Vector3<OtherT>& rhs) const
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
		template<typename OtherT>
		constexpr Vector2<value_type>& operator=(const Vector3<OtherT>& rhs)
		{
			if constexpr (std::is_same_v<nonref_value_type, typename info_type_t<OtherT>::nonref_value_type>)
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

#pragma region ARITHMETIC_TEMPLATES
		template<std::size_t OutSize_ = 2, typename OutT = nonref_value_type, typename RhsT = nonref_value_type>
		constexpr EmuMath::TMPHelpers::emu_vector_from_size_t<OutSize_, OutT> AsAdded(const Vector2<RhsT>& rhs) const
		{
			return this->_perform_addition<Vector2<RhsT>, EmuMath::TMPHelpers::emu_vector_from_size_t<OutSize_, OutT>>(rhs);
		}
		template<std::size_t OutSize_ = 2, typename OutT = nonref_value_type, typename RhsT = nonref_value_type>
		constexpr EmuMath::TMPHelpers::emu_vector_from_size_t<OutSize_, OutT> AsAdded(const Vector3<RhsT>& rhs) const
		{
			return this->_perform_addition<Vector3<RhsT>, EmuMath::TMPHelpers::emu_vector_from_size_t<OutSize_, OutT>>(rhs);
		}
		template<std::size_t OutSize_ = 2, typename OutT = nonref_value_type, typename RhsT = nonref_value_type>
		constexpr EmuMath::TMPHelpers::emu_vector_from_size_t<OutSize_, OutT> AsAdded(const Vector4<RhsT>& rhs) const
		{
			return this->_perform_addition<Vector4<RhsT>, EmuMath::TMPHelpers::emu_vector_from_size_t<OutSize_, OutT>>(rhs);
		}

		template<std::size_t OutSize_ = 2, typename OutT = nonref_value_type, typename RhsT = nonref_value_type>
		constexpr EmuMath::TMPHelpers::emu_vector_from_size_t<OutSize_, OutT> AsSubtracted(const Vector2<RhsT>& rhs) const
		{
			return this->_perform_subtraction<Vector2<RhsT>, EmuMath::TMPHelpers::emu_vector_from_size_t<OutSize_, OutT>>(rhs);
		}
		template<std::size_t OutSize_ = 2, typename OutT = nonref_value_type, typename RhsT = nonref_value_type>
		constexpr EmuMath::TMPHelpers::emu_vector_from_size_t<OutSize_, OutT> AsSubtracted(const Vector3<RhsT>& rhs) const
		{
			return this->_perform_subtraction<Vector3<RhsT>, EmuMath::TMPHelpers::emu_vector_from_size_t<OutSize_, OutT>>(rhs);
		}
		template<std::size_t OutSize_ = 2, typename OutT = nonref_value_type, typename RhsT = nonref_value_type>
		constexpr EmuMath::TMPHelpers::emu_vector_from_size_t<OutSize_, OutT> AsSubtracted(const Vector4<RhsT>& rhs) const
		{
			return this->_perform_subtraction<Vector4<RhsT>, EmuMath::TMPHelpers::emu_vector_from_size_t<OutSize_, OutT>>(rhs);
		}

		template<std::size_t OutSize_ = 2, typename OutT = nonref_value_type, typename RhsT = nonref_value_type>
		constexpr EmuMath::TMPHelpers::emu_vector_from_size_t<OutSize_, OutT> AsMultiplied(const Vector2<RhsT>& rhs) const
		{
			return this->_perform_vector_multiplication<Vector2<RhsT>, EmuMath::TMPHelpers::emu_vector_from_size_t<OutSize_, OutT>>(rhs);
		}
		template<std::size_t OutSize_ = 2, typename OutT = nonref_value_type, typename RhsT = nonref_value_type>
		constexpr EmuMath::TMPHelpers::emu_vector_from_size_t<OutSize_, OutT> AsMultiplied(const Vector3<RhsT>& rhs) const
		{
			return this->_perform_vector_multiplication<Vector3<RhsT>, EmuMath::TMPHelpers::emu_vector_from_size_t<OutSize_, OutT>>(rhs);
		}
		template<std::size_t OutSize_ = 2, typename OutT = nonref_value_type, typename RhsT = nonref_value_type>
		constexpr EmuMath::TMPHelpers::emu_vector_from_size_t<OutSize_, OutT> AsMultiplied(const Vector4<RhsT>& rhs) const
		{
			return this->_perform_vector_multiplication<Vector4<RhsT>, EmuMath::TMPHelpers::emu_vector_from_size_t<OutSize_, OutT>>(rhs);
		}
		template<std::size_t OutSize_ = 2, typename OutT = nonref_value_type, typename RhsT = nonref_value_type>
		constexpr EmuMath::TMPHelpers::emu_vector_from_size_t<OutSize_, OutT> AsMultiplied(const RhsT& rhs) const
		{
			return this->_perform_scalar_multiplication<RhsT, EmuMath::TMPHelpers::emu_vector_from_size_t<OutSize_, OutT>>(rhs);
		}

		template<std::size_t OutSize_ = 2, typename OutT = nonref_value_type, typename RhsT = nonref_value_type>
		constexpr EmuMath::TMPHelpers::emu_vector_from_size_t<OutSize_, OutT> AsDivided(const Vector2<RhsT>& rhs) const
		{
			return this->_perform_vector_division<Vector2<RhsT>, EmuMath::TMPHelpers::emu_vector_from_size_t<OutSize_, OutT>>(rhs);
		}
		template<std::size_t OutSize_ = 2, typename OutT = nonref_value_type, typename RhsT = nonref_value_type>
		constexpr EmuMath::TMPHelpers::emu_vector_from_size_t<OutSize_, OutT> AsDivided(const Vector3<RhsT>& rhs) const
		{
			return this->_perform_vector_division<Vector3<RhsT>, EmuMath::TMPHelpers::emu_vector_from_size_t<OutSize_, OutT>>(rhs);
		}
		template<std::size_t OutSize_ = 2, typename OutT = nonref_value_type, typename RhsT = nonref_value_type>
		constexpr EmuMath::TMPHelpers::emu_vector_from_size_t<OutSize_, OutT> AsDivided(const Vector4<RhsT>& rhs) const
		{
			return this->_perform_vector_division<Vector4<RhsT>, EmuMath::TMPHelpers::emu_vector_from_size_t<OutSize_, OutT>>(rhs);
		}
		template<std::size_t OutSize_ = 2, typename OutT = nonref_value_type, typename RhsT = nonref_value_type>
		constexpr EmuMath::TMPHelpers::emu_vector_from_size_t<OutSize_, OutT> AsDivided(const RhsT& rhs) const
		{
			return this->_perform_scalar_division<RhsT, EmuMath::TMPHelpers::emu_vector_from_size_t<OutSize_, OutT>>(rhs);
		}

		template<std::size_t OutSize_ = 2, typename OutT = nonref_value_type, typename RhsT = nonref_value_type>
		constexpr EmuMath::TMPHelpers::emu_vector_from_size_t<OutSize_, OutT> AsMod(const Vector2<RhsT>& rhs) const
		{
			return this->_perform_vector_mod<Vector2<RhsT>, EmuMath::TMPHelpers::emu_vector_from_size_t<OutSize_, OutT>>(rhs);
		}
		template<std::size_t OutSize_ = 2, typename OutT = nonref_value_type, typename RhsT = nonref_value_type>
		constexpr EmuMath::TMPHelpers::emu_vector_from_size_t<OutSize_, OutT> AsMod(const Vector3<RhsT>& rhs) const
		{
			return this->_perform_vector_mod<Vector3<RhsT>, EmuMath::TMPHelpers::emu_vector_from_size_t<OutSize_, OutT>>(rhs);
		}
		template<std::size_t OutSize_ = 2, typename OutT = nonref_value_type, typename RhsT = nonref_value_type>
		constexpr EmuMath::TMPHelpers::emu_vector_from_size_t<OutSize_, OutT> AsMod(const Vector4<RhsT>& rhs) const
		{
			return this->_perform_vector_mod<Vector4<RhsT>, EmuMath::TMPHelpers::emu_vector_from_size_t<OutSize_, OutT>>(rhs);
		}
		template<std::size_t OutSize_ = 2, typename OutT = nonref_value_type, typename RhsT = nonref_value_type>
		constexpr EmuMath::TMPHelpers::emu_vector_from_size_t<OutSize_, OutT> AsMod(const RhsT& rhs) const
		{
			return this->_perform_scalar_mod<RhsT, EmuMath::TMPHelpers::emu_vector_from_size_t<OutSize_, OutT>>(rhs);
		}
#pragma endregion

#pragma region BITWISE_TEMPLATES
		template<std::size_t OutSize_ = 2, typename OutT = nonref_value_type, typename RhsT = nonref_value_type>
		constexpr EmuMath::TMPHelpers::emu_vector_from_size_t<OutSize_, OutT> AsBitwiseAnded(const Vector2<RhsT>& rhs) const
		{
			return this->_perform_vector_and<Vector2<RhsT>, EmuMath::TMPHelpers::emu_vector_from_size_t<OutSize_, OutT>>(rhs);
		}
		template<std::size_t OutSize_ = 2, typename OutT = nonref_value_type, typename RhsT = nonref_value_type>
		constexpr EmuMath::TMPHelpers::emu_vector_from_size_t<OutSize_, OutT> AsBitwiseAnded(const Vector3<RhsT>& rhs) const
		{
			return this->_perform_vector_and<Vector3<RhsT>, EmuMath::TMPHelpers::emu_vector_from_size_t<OutSize_, OutT>>(rhs);
		}
		template<std::size_t OutSize_ = 2, typename OutT = nonref_value_type, typename RhsT = nonref_value_type>
		constexpr EmuMath::TMPHelpers::emu_vector_from_size_t<OutSize_, OutT> AsBitwiseAnded(const Vector4<RhsT>& rhs) const
		{
			return this->_perform_vector_and<Vector4<RhsT>, EmuMath::TMPHelpers::emu_vector_from_size_t<OutSize_, OutT>>(rhs);
		}
		template<std::size_t OutSize_ = 2, typename OutT = nonref_value_type, typename RhsT = nonref_value_type>
		constexpr EmuMath::TMPHelpers::emu_vector_from_size_t<OutSize_, OutT> AsBitwiseAnded(const RhsT& rhs) const
		{
			return this->_perform_scalar_and<RhsT, EmuMath::TMPHelpers::emu_vector_from_size_t<OutSize_, OutT>>(rhs);
		}

		template<std::size_t OutSize_ = 2, typename OutT = nonref_value_type, typename RhsT = nonref_value_type>
		constexpr EmuMath::TMPHelpers::emu_vector_from_size_t<OutSize_, OutT> AsBitwiseOred(const Vector2<RhsT>& rhs) const
		{
			return this->_perform_vector_or<Vector2<RhsT>, EmuMath::TMPHelpers::emu_vector_from_size_t<OutSize_, OutT>>(rhs);
		}
		template<std::size_t OutSize_ = 2, typename OutT = nonref_value_type, typename RhsT = nonref_value_type>
		constexpr EmuMath::TMPHelpers::emu_vector_from_size_t<OutSize_, OutT> AsBitwiseOred(const Vector3<RhsT>& rhs) const
		{
			return this->_perform_vector_or<Vector3<RhsT>, EmuMath::TMPHelpers::emu_vector_from_size_t<OutSize_, OutT>>(rhs);
		}
		template<std::size_t OutSize_ = 2, typename OutT = nonref_value_type, typename RhsT = nonref_value_type>
		constexpr EmuMath::TMPHelpers::emu_vector_from_size_t<OutSize_, OutT> AsBitwiseOred(const Vector4<RhsT>& rhs) const
		{
			return this->_perform_vector_or<Vector4<RhsT>, EmuMath::TMPHelpers::emu_vector_from_size_t<OutSize_, OutT>>(rhs);
		}
		template<std::size_t OutSize_ = 2, typename OutT = nonref_value_type, typename RhsT = nonref_value_type>
		constexpr EmuMath::TMPHelpers::emu_vector_from_size_t<OutSize_, OutT> AsBitwiseOred(const RhsT& rhs) const
		{
			return this->_perform_scalar_or<RhsT, EmuMath::TMPHelpers::emu_vector_from_size_t<OutSize_, OutT>>(rhs);
		}

		template<std::size_t OutSize_ = 2, typename OutT = nonref_value_type, typename RhsT = nonref_value_type>
		constexpr EmuMath::TMPHelpers::emu_vector_from_size_t<OutSize_, OutT> AsBitwiseXored(const Vector2<RhsT>& rhs) const
		{
			return this->_perform_vector_xor<Vector2<RhsT>, EmuMath::TMPHelpers::emu_vector_from_size_t<OutSize_, OutT>>(rhs);
		}
		template<std::size_t OutSize_ = 2, typename OutT = nonref_value_type, typename RhsT = nonref_value_type>
		constexpr EmuMath::TMPHelpers::emu_vector_from_size_t<OutSize_, OutT> AsBitwiseXored(const Vector3<RhsT>& rhs) const
		{
			return this->_perform_vector_xor<Vector3<RhsT>, EmuMath::TMPHelpers::emu_vector_from_size_t<OutSize_, OutT>>(rhs);
		}
		template<std::size_t OutSize_ = 2, typename OutT = nonref_value_type, typename RhsT = nonref_value_type>
		constexpr EmuMath::TMPHelpers::emu_vector_from_size_t<OutSize_, OutT> AsBitwiseXored(const Vector4<RhsT>& rhs) const
		{
			return this->_perform_vector_xor<Vector4<RhsT>, EmuMath::TMPHelpers::emu_vector_from_size_t<OutSize_, OutT>>(rhs);
		}
		template<std::size_t OutSize_ = 2, typename OutT = nonref_value_type, typename RhsT = nonref_value_type>
		constexpr EmuMath::TMPHelpers::emu_vector_from_size_t<OutSize_, OutT> AsBitwiseXored(const RhsT& rhs) const
		{
			return this->_perform_scalar_xor<RhsT, EmuMath::TMPHelpers::emu_vector_from_size_t<OutSize_, OutT>>(rhs);
		}

		template<std::size_t OutSize_ = 2, typename OutT = nonref_value_type, typename RhsT = nonref_value_type>
		constexpr EmuMath::TMPHelpers::emu_vector_from_size_t<OutSize_, OutT> AsLeftShiftedPerElement(const Vector2<RhsT>& numShifts) const
		{
			return this->_perform_vector_per_element_leftshift<Vector2<RhsT>, EmuMath::TMPHelpers::emu_vector_from_size_t<OutSize_, OutT>>(numShifts);
		}
		template<std::size_t OutSize_ = 2, typename OutT = nonref_value_type, typename RhsT = nonref_value_type>
		constexpr EmuMath::TMPHelpers::emu_vector_from_size_t<OutSize_, OutT> AsLeftShiftedPerElement(const Vector3<RhsT>& numShifts) const
		{
			return this->_perform_vector_per_element_leftshift<Vector3<RhsT>, EmuMath::TMPHelpers::emu_vector_from_size_t<OutSize_, OutT>>(numShifts);
		}
		template<std::size_t OutSize_ = 2, typename OutT = nonref_value_type, typename RhsT = nonref_value_type>
		constexpr EmuMath::TMPHelpers::emu_vector_from_size_t<OutSize_, OutT> AsLeftShiftedPerElement(const Vector4<RhsT>& numShifts) const
		{
			return this->_perform_vector_per_element_leftshift<Vector4<RhsT>, EmuMath::TMPHelpers::emu_vector_from_size_t<OutSize_, OutT>>(numShifts);
		}
		template<std::size_t OutSize_ = 2, typename OutT = nonref_value_type, typename RhsT = nonref_value_type>
		constexpr EmuMath::TMPHelpers::emu_vector_from_size_t<OutSize_, OutT> AsLeftShiftedPerElement(const RhsT& numShifts) const
		{
			return this->_perform_scalar_per_element_leftshift<RhsT, EmuMath::TMPHelpers::emu_vector_from_size_t<OutSize_, OutT>>(numShifts);
		}

		template<std::size_t OutSize_ = 2, typename OutT = nonref_value_type, typename RhsT = nonref_value_type>
		constexpr EmuMath::TMPHelpers::emu_vector_from_size_t<OutSize_, OutT> AsRightShiftedPerElement(const Vector2<RhsT>& numShifts) const
		{
			return this->_perform_vector_per_element_rightshift<Vector2<RhsT>, EmuMath::TMPHelpers::emu_vector_from_size_t<OutSize_, OutT>>(numShifts);
		}
		template<std::size_t OutSize_ = 2, typename OutT = nonref_value_type, typename RhsT = nonref_value_type>
		constexpr EmuMath::TMPHelpers::emu_vector_from_size_t<OutSize_, OutT> AsRightShiftedPerElement(const Vector3<RhsT>& numShifts) const
		{
			return this->_perform_vector_per_element_rightshift<Vector3<RhsT>, EmuMath::TMPHelpers::emu_vector_from_size_t<OutSize_, OutT>>(numShifts);
		}
		template<std::size_t OutSize_ = 2, typename OutT = nonref_value_type, typename RhsT = nonref_value_type>
		constexpr EmuMath::TMPHelpers::emu_vector_from_size_t<OutSize_, OutT> AsRightShiftedPerElement(const Vector4<RhsT>& numShifts) const
		{
			return this->_perform_vector_per_element_rightshift<Vector4<RhsT>, EmuMath::TMPHelpers::emu_vector_from_size_t<OutSize_, OutT>>(numShifts);
		}
		template<std::size_t OutSize_ = 2, typename OutT = nonref_value_type, typename RhsT = nonref_value_type>
		constexpr EmuMath::TMPHelpers::emu_vector_from_size_t<OutSize_, OutT> AsRightShiftedPerElement(const RhsT& numShifts) const
		{
			return this->_perform_scalar_per_element_rightshift<RhsT, EmuMath::TMPHelpers::emu_vector_from_size_t<OutSize_, OutT>>(numShifts);
		}

		template<std::size_t OutSize_ = size(), typename OutT = nonref_value_type>
		constexpr EmuMath::TMPHelpers::emu_vector_from_size_t<OutSize_, OutT> AsNot() const
		{
			return this->_perform_inversion<EmuMath::TMPHelpers::emu_vector_from_size_t<OutSize_, OutT>>();
		}
#pragma endregion

#pragma region BOOLEAN_PER_ELEMENT_COMPARISON_FUNCTIONS
		/// <summary> Compares the equality of the elements in this Vector with the respecitve elements in the passed Vector. </summary>
		/// <typeparam name="OtherT">Type stored within the passed Vector.</typeparam>
		/// <param name="rhs">Vector to compare respective elements of.</param>
		/// <returns>Vector of booleans indicating if respective values were equal.</returns>
		template<typename OtherT>
		constexpr Vector2<bool> CompareElementsEqual(const Vector2<OtherT>& rhs) const
		{
			return { x == rhs.x, y == rhs.y };
		}
		/// <summary> Compares the inequality of the elements in this Vector with the respecitve elements in the passed Vector. </summary>
		/// <typeparam name="OtherT">Type stored within the passed Vector.</typeparam>
		/// <param name="rhs">Vector to compare respective elements of.</param>
		/// <returns>Vector of booleans indicating if respective values were unequal.</returns>
		template<typename OtherT>
		constexpr Vector2<bool> CompareElementsNotEqual(const Vector2<OtherT>& rhs) const
		{
			return { x != rhs.x, y != rhs.y };
		}
		/// <summary> Compares if the elements of this Vector are greater than the respective elements in the passed Vector. </summary>
		/// <typeparam name="OtherT">Type stored within the passed Vector.</typeparam>
		/// <param name="rhs">Vector to compare respective elements of.</param>
		/// <returns>Vector of booleans indicating if respective values of this Vector are greater than the values in the passed Vector.</returns>
		template<typename OtherT>
		constexpr Vector2<bool> CompareElementsGreater(const Vector2<OtherT>& rhs) const
		{
			return { x > rhs.x, y > rhs.y };
		}
		/// <summary> Compares if the elements of this Vector are less than the respective elements in the passed Vector. </summary>
		/// <typeparam name="OtherT">Type stored within the passed Vector.</typeparam>
		/// <param name="rhs">Vector to compare respective elements of.</param>
		/// <returns>Vector of booleans indicating if respective values of this Vector are less than the values in the passed Vector.</returns>
		template<typename OtherT>
		constexpr Vector2<bool> CompareElementsLess(const Vector2<OtherT>& rhs) const
		{
			return { x < rhs.x, y < rhs.y };
		}
		/// <summary> Compares if the elements of this Vector are greater than or equal to the respective elements in the passed Vector. </summary>
		/// <typeparam name="OtherT">Type stored within the passed Vector.</typeparam>
		/// <param name="rhs">Vector to compare respective elements of.</param>
		/// <returns>Vector of booleans indicating if respective values of this Vector are greater than or equal to the values in the passed Vector.</returns>
		template<typename OtherT>
		constexpr Vector2<bool> CompareElementsGreaterEqual(const Vector2<OtherT>& rhs) const
		{
			return { x >= rhs.x, y >= rhs.y };
		}
		/// <summary> Compares if the elements of this Vector are less than or equal to the respective elements in the passed Vector. </summary>
		/// <typeparam name="OtherT">Type stored within the passed Vector.</typeparam>
		/// <param name="rhs">Vector to compare respective elements of.</param>
		/// <returns>Vector of booleans indicating if respective values of this Vector are less than or equal to the values in the passed Vector.</returns>
		template<typename OtherT>
		constexpr Vector2<bool> CompareElementsLessEqual(const Vector2<OtherT>& rhs) const
		{
			return { x <= rhs.x, y <= rhs.y };
		}
#pragma endregion

#pragma region SHUFFLES
		/// <summary> Returns a Vector3 with elements X, Y and Z copying the elements at the respective provided indices within this Vector. </summary>
		/// <returns>This vector shuffled as a Vector3.</returns>
		template<std::size_t X_, std::size_t Y_, std::size_t Z_>
		constexpr Vector3<nonref_value_type> AsShuffled() const
		{
			return { at<X_>(), at<Y_>(), at<Z_>() };
		}
		/// <summary> Returns a Vector2 with elements X and Y copying the elements at the respective provided indices within this Vector. </summary>
		/// <returns>This vector shuffled as a Vector2.</returns>
		template<std::size_t X_, std::size_t Y_>
		constexpr Vector2<nonref_value_type> AsShuffled() const
		{
			return { at<X_>(), at<Y_>() };
		}
		/// <summary>
		///	<para> Returns a Vector3 with elements X, Y and Z copying the elements at the respective provided indices within this Vector. </para>
		/// <para> If possible, it is recommended to use the templatised version of this function. </para>
		/// </summary>
		/// <returns>This vector shuffled as a Vector3.</returns>
		Vector3<nonref_value_type> AsShuffled(const std::size_t x_, const std::size_t y_, const std::size_t z_) const
		{
			return { at(x_), at(y_), at(z_) };
		}
		/// <summary>
		/// <para> Returns a Vector2 with elements X and Y copying the elements at the respective provided indices within this Vector. </para>
		/// <para> If possible, it is recommended to use the templatised version of this function. </para>
		/// </summary>
		/// <returns>This vector shuffled as a Vector2.</returns>
		Vector2<nonref_value_type> AsShuffled(const std::size_t x_, const std::size_t y_) const
		{
			return { at(x_), at(y_) };
		}
		/// <summary>
		/// <para> Returns a Vector3 containing references to the elements at the respective provided indices within this vector. </para>
		/// </summary>
		/// <returns>Vector3 of references to the elements at the provided indices within this Vector.</returns>
		template<std::size_t X_, std::size_t Y_, std::size_t Z_>
		constexpr Vector3<ref_value_type> ShuffledReference()
		{
			return { at<X_>(), at<Y_>(), at<Z_>() };
		}
		/// <summary>
		/// <para> Returns a Vector3 containing constant references to the elements at the respective provided indices within this vector. </para>
		/// </summary>
		/// <returns>Vector3 of constant references to the elements at the provided indices within this Vector.</returns>
		template<std::size_t X_, std::size_t Y_, std::size_t Z_>
		constexpr Vector3<const_ref_value_type> ShuffledReference() const
		{
			return { at<X_>(), at<Y_>(), at<Z_>() };
		}
		/// <summary>
		/// <para> Returns a Vector2 containing references to the elements at the respective provided indices within this vector. </para>
		/// </summary>
		/// <returns>Vector2 of references to the elements at the provided indices within this Vector.</returns>
		template<std::size_t X_, std::size_t Y_>
		constexpr Vector2<ref_value_type> ShuffledReference()
		{
			return { at<X_>(), at<Y_>() };
		}
		/// <summary>
		/// <para> Returns a Vector2 containing constant references to the elements at the respective provided indices within this vector. </para>
		/// </summary>
		/// <returns>Vector2 of constant references to the elements at the provided indices within this Vector.</returns>
		template<std::size_t X_, std::size_t Y_>
		constexpr Vector2<const_ref_value_type> ShuffledReference() const
		{
			return { at<X_>(), at<Y_>() };
		}
		/// <summary>
		/// <para> Returns a Vector3 containing references to the elements at the respective provided indices within this vector. </para>
		/// <para> If possible, it is recommended to use the templatised version of this function. </para>
		/// </summary>
		/// <returns>Vector3 of references to the elements at the provided indices within this Vector.</returns>
		Vector3<ref_value_type> ShuffledReference(const std::size_t x_, const std::size_t y_, const std::size_t z_)
		{
			return { at(x_), at(y_), at(z_) };
		}
		/// <summary>
		/// <para> Returns a Vector3 containing constant references to the elements at the respective provided indices within this vector. </para>
		/// <para> If possible, it is recommended to use the templatised version of this function. </para>
		/// </summary>
		/// <returns>Vector3 of constant references to the elements at the provided indices within this Vector.</returns>
		Vector3<const_ref_value_type> ShuffledReference(const std::size_t x_, const std::size_t y_, const std::size_t z_) const
		{
			return { at(x_), at(y_), at(z_) };
		}
		/// <summary>
		/// <para> Returns a Vector2 containing references to the elements at the respective provided indices within this vector. </para>
		/// <para> If possible, it is recommended to use the templatised version of this function. </para>
		/// </summary>
		/// <returns>Vector2 of references to the elements at the provided indices within this Vector.</returns>
		Vector2<ref_value_type> ShuffledReference(const std::size_t x_, const std::size_t y_)
		{
			return { at(x_), at(y_) };
		}
		/// <summary>
		/// <para> Returns a Vector2 containing constant references to the elements at the respective provided indices within this vector. </para>
		/// <para> If possible, it is recommended to use the templatised version of this function. </para>
		/// </summary>
		/// <returns>Vector2 of constant references to the elements at the provided indices within this Vector.</returns>
		Vector2<const_ref_value_type> ShuffledReference(const std::size_t x_, const std::size_t y_) const
		{
			return { at(x_), at(y_) };
		}
#pragma endregion

#pragma region SETS
		/// <summary> Sets all values within this Vector to the respective passed values. </summary>
		/// <typeparam name="X_">Type of the value to set this Vector's x component to.</typeparam>
		/// <typeparam name="Y_">Type of the value to set this Vector's y component to.</typeparam>
		/// <param name="x_">Value to set this Vector's x component to.</param>
		/// <param name="y_">Value to set this Vector's y component to.</param>
		template<typename X_, typename Y_>
		constexpr void SetAll(const X_& x_, const Y_& y_)
		{
			if constexpr (!info_type::has_const_values)
			{
				_set_individual_value<0, X_>(x_);
				_set_individual_value<1, Y_>(y_);
			}
			else
			{
				static_assert(false, "Attempted to perform a non-const function (SetAll<X_, Y_>) on an EmuMath::Vector2 which contains constant values.");
			}
		}
		/// <summary> Sets all elements of this Vector to match the provided value. </summary>
		/// <typeparam name="T_">Type of the value to set this Vector's components to.</typeparam>
		/// <param name="val_">Value to set this Vector's componenets to.</param>
		template<typename T_>
		constexpr void SetAll(const T_& val_)
		{
			if constexpr (!info_type::has_const_values)
			{
				if constexpr (std::is_same_v<nonref_value_type_without_qualifiers, std::remove_reference_t<T_>>)
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
			else
			{
				static_assert(false, "Attempted to perform a non-const function (SetAll<T_>) on an EmuMath::Vector2 which contains constant values.");
			}
		}
#pragma endregion

#pragma region OVERALL_OPERATIONS
		/// <summary>
		/// <para> Calculates the reciprocals of this Vector's elements, with an optionally customisable floating-point output type. </para>
		/// <para> Note that the output type must be a valid floating point type. If not, a static assertion will be triggered. </para>
		/// </summary>
		/// <typeparam name="OutT">Floating-point type to output the reciprocals as.</typeparam>
		/// <returns>Vector of reciprocals to this Vector's respective elements, stored as the provided OutT (defaults to this Vector's default_floating_point).</returns>
		template<typename OutT = default_floating_point>
		constexpr Vector2<OutT> Reciprocal() const
		{
			if constexpr (std::is_floating_point_v<OutT>)
			{
				constexpr OutT one_ = EmuCore::ArithmeticHelpers::OneT<OutT>;
				if constexpr (std::is_same_v<nonref_value_type_without_qualifiers, OutT>)
				{
					return { one_ / x, one_ / y };
				}
				else
				{
					return { one_ / static_cast<OutT>(x), one_ / static_cast<OutT>(y) };
				}
			}
			else
			{
				static_assert(false, "Attempted to retrieve a non-floating-point reciprocal from an EmuMath::Vector2, which is not allowed.");
			}
		}
		/// <summary>
		/// <para> Calculates the total of all of this Vector's elements added together and outputs the result as an optionally customisable type. </para>
		/// </summary>
		/// <typeparam name="OutT">Type to output the sum as.</typeparam>
		/// <returns>The total of all elements in this Vector added together, represented as the provided OutT (defaults to this Vector's nonref_value_type).</returns>
		template<typename OutT = nonref_value_type>
		constexpr OutT OverallSum() const
		{
			if constexpr (std::is_same_v<nonref_value_type_without_qualifiers, OutT>)
			{
				return x + y;
			}
			else
			{
				return static_cast<OutT>(x) + static_cast<OutT>(y);
			}
		}
		/// <summary>
		/// <para> Calculates the total of all of this Vector's elements multiplied together and outputs the result as an optionally customisable type. </para>
		/// </summary>
		/// <typeparam name="OutT">Type to output the product as.</typeparam>
		/// <returns>The total of all elements in this Vector multiplied together, represented as the provided OutT (defaults to this Vector's nonref_value_type).</returns>
		template<typename OutT = nonref_value_type>
		constexpr OutT OverallProduct() const
		{
			if constexpr (std::is_same_v<nonref_value_type_without_qualifiers, OutT>)
			{
				return x * y;
			}
			else
			{
				return static_cast<OutT>(x) * static_cast<OutT>(y);
			}
		}
		/// <summary> Returns a boolean indicating if all elements within this Vector are zero. </summary>
		/// <returns> True if all elements in this Vector are zero, otherwise false. </returns>
		constexpr bool AllZero() const
		{
			return x == info_type::value_zero && y == info_type::value_zero;
		}
		/// <summary> Determines the lowest element within this Vector. </summary>
		/// <returns>Copy of the lowest element within this Vector.</returns>
		constexpr nonref_value_type Min() const
		{
			return x < y ? x : y;
		}
		/// <summary> Determines the highest element within this Vector. </summary>
		/// <returns>Copy of the highest element within this Vector.</returns>
		constexpr nonref_value_type Max() const
		{
			return x > y ? x : y;
		}
		/// <summary> Calculates the values of this Vector's elements when clamped to the provided minimum respective values of the passed Vector. </summary>
		/// <param name="min_">Minimum values for the respective elements of this Vector.</param>
		/// <returns>Copy of this Vector with its elements clamped to a minimum of the respective elements in the provided Vector.</returns>
		constexpr Vector2<nonref_value_type> AsClampedMin(const Vector2<value_type>& min_) const
		{
			return { x > min_.x ? x : min_.x, y > min_.y ? y : min_.y };
		}
		/// <summary> Calculates the values of this vector's elements when clamped to the provided minimum value for all elements. </summary>
		/// <param name="min_">Minimum value that any element within this Vector may be.</param>
		/// <returns>Copy of this Vector with its elements clamped to a minimum of the provided value.</returns>
		constexpr Vector2<nonref_value_type> AsClampedMin(const_ref_value_type min_) const
		{
			AsClampedMin(min_, min_);
		}
		/// <summary> Calculates the values of this Vector's elements when clamped to the provided maximum respective values of the passed Vector. </summary>
		/// <param name="max_">Maximum values for the respective elements of this Vector.</param>
		/// <returns>Copy of this Vector with its elements clamped to a maximum of the respective elements in the provided Vector.</returns>
		constexpr Vector2<nonref_value_type> AsClampedMax(const Vector2<value_type>& max_) const
		{
			return { x < max_.x ? x : max_.x, y < max_.y ? y : max_.y };
		}
		/// <summary> Calculates the values of this vector's elements when clamped to the provided maximum value for all elements. </summary>
		/// <param name="max_">Maximum value that any element within this Vector may be.</param>
		/// <returns>Copy of this Vector with its elements clamped to a maximum of the provided value.</returns>
		constexpr Vector2<nonref_value_type> AsClampedMax(const value_type& max_) const
		{
			return this->AsClampedMax(Vector2<value_type>(max_, max_));
		}
		/// <summary> Calculates the values of this Vector's elements when clamped between the provided minimum and maximum respective values of the passed Vectors. </summary>
		/// <param name="min_">Minimum values for the respective elements of this Vector.</param>
		/// <param name="max_">Maximum values for the respective elements of this Vector.</param>
		/// <returns>Copy of this Vector with its elements clamped between the minimum and maximum of the respective elements in ths provided Vectors.</returns>
		constexpr Vector2<nonref_value_type> AsClamped(const Vector2<value_type>& min_, const Vector2<value_type>& max_) const
		{
			return
			{
				x < min_.x ? min_.x : x > max_.x ? max_.x : x,
				y < min_.y ? min_.y : y > max_.y ? max_.y : y
			};
		}
		/// <summary> Calculates the values of this Vector's elements when clamped between the provided minimum and maximum respective values of the passed Vectors. </summary>
		/// <param name="min_">Minimum value that each element of this Vector may be.</param>
		/// <param name="max_">Maximum value that each element of this Vector may be.</param>
		/// <returns>Copy of this Vector with its elements clamped between the provided minimum and maximum values.</returns>
		constexpr Vector2<nonref_value_type> AsClamped(const value_type& min_, const value_type& max_) const
		{
			return this->AsClamped(Vector2<value_type>(min_, min_), Vector2<value_type>(max_, max_));
		}
		/// <summary> Calculates the values of this Vector's elements when rounded toward negative infinity. </summary>
		/// <returns>Copy of this Vector with its elements rounded toward negative infinity.</returns>
		Vector2<nonref_value_type> AsFloored() const
		{
			if constexpr (info_type::has_integral_values)
			{
				return { x, y };
			}
			else if constexpr(info_type::has_floating_point_values)
			{
				if constexpr (std::is_same_v<nonref_value_type_without_qualifiers, float>)
				{
					return { floorf(x), floorf(y) };
				}
				else if constexpr (std::is_same_v<nonref_value_type_without_qualifiers, double>)
				{
					return { floor(x), floor(y) };
				}
				else
				{
					return { floorl(x), floorl(y) };
				}
			}
			else
			{
				static_assert(false, "Attempted to floor an EmuMath::Vector2 which contains a type which may not be arbitrarily rounded.");
			}
		}
		/// <summary> Calculates the values of this Vector's elements when rounded toward positive infinity. </summary>
		/// <returns>Copy of this Vector with its elements rounded toward positive infinity.</returns>
		Vector2<nonref_value_type> AsCeiled() const
		{
			if constexpr (info_type::has_integral_values)
			{
				return { x, y };
			}
			else if constexpr (info_type::has_floating_point_values)
			{
				if constexpr (std::is_same_v<nonref_value_type_without_qualifiers, float>)
				{
					return { ceilf(x), ceilf(y) };
				}
				else if constexpr (std::is_same_v<nonref_value_type_without_qualifiers, double>)
				{
					return { ceil(x), ceil(y) };
				}
				else
				{
					return { ceill(x), ceill(y) };
				}
			}
			else
			{
				static_assert(false, "Attempted to floor an EmuMath::Vector2 which contains a type which may not be arbitrarily rounded.");
				return *this;
			}
		}
		/// <summary> Calculates the values of this Vector's elements when rounded toward 0. </summary>
		/// <returns>Copy of this Vector with its elements rounded toward 0.</returns>
		constexpr Vector2<nonref_value_type> AsTrunced() const
		{
			if constexpr (info_type::has_integral_values)
			{
				return { x, y };
			}
			else if constexpr (info_type::has_floating_point_values)
			{
				// Faster to do a double cast than call trunc functions
				using IntRep = EmuCore::TMPHelpers::best_signed_int_rep_t<nonref_value_type_without_qualifiers>;
				return
				{
					static_cast<nonref_value_type>(static_cast<IntRep>(x)),
					static_cast<nonref_value_type>(static_cast<IntRep>(y))
				};
			}
			else
			{
				static_assert(false, "Attempted to floor an EmuMath::Vector2 which contains a type which may not be arbitrarily rounded.");
				return *this;
			}
		}
		/// <summary>
		/// <para> Returns a Vector resulting from a linear interpolation between this Vector and Vector b, using t as the weighting. </para>
		/// <para> The output Vector's contained types may be optionally customised, and default to this Vector's default_floating_point. </para>
		/// </summary>
		/// <typeparam name="OutT">Type for the result Vector to contain.</typeparam>
		/// <typeparam name="BContainedT_">The type contained in Vector b.</typeparam>
		/// <typeparam name="T_">The type used for the t argument.</typeparam>
		/// <param name="b">Vector to interpolate this Vector with. b in the equation a + (b - a) * t.</param>
		/// <param name="t">Weighting to apply to the interpolation. t in the equation a + (b - a) * t.</param>
		/// <returns>
		///		Vector containing the passed OutT (defaults to this Vector's default_floating_point), with elements being the results of the equation
		///		a + (b - a) * t, where a is this Vector, b the passed Vector, and t the passed weighting.
		/// </returns>
		template<typename OutT = default_floating_point, typename BContainedT_ = nonref_value_type, typename T_ = default_floating_point>
		constexpr Vector2<OutT> AsLerped(const Vector2<BContainedT_>& b, const T_& t) const
		{
			using OutFP = EmuCore::TMPHelpers::best_floating_point_rep_t<OutT>;
			using TFP = EmuCore::TMPHelpers::best_floating_point_rep_t<T_>;
			using BContainedTFP = EmuCore::TMPHelpers::best_floating_point_rep_t<BContainedT_>;
			using HighestFP = EmuCore::TMPHelpers::highest_byte_size_t<default_floating_point, OutFP, TFP, BContainedTFP>;

			const HighestFP tfp = static_cast<HighestFP>(t);
			if constexpr (std::is_same_v<nonref_value_type_without_qualifiers, HighestFP>)
			{
				if constexpr (std::is_same_v<typename Vector2<BContainedT_>::nonref_value_type_without_qualifiers, HighestFP>)
				{
					return Vector2<OutT>
					(
						x + (b.x - x) * tfp,
						y + (b.y - y) * tfp
					);
				}
				else
				{
					return Vector2<OutT>
					(
						x + (static_cast<HighestFP>(b.x) - x) * tfp,
						y + (static_cast<HighestFP>(b.y) - y) * tfp
					);
				}
			}
			else
			{
				const HighestFP xfp = static_cast<HighestFP>(x);
				const HighestFP yfp = static_cast<HighestFP>(y);
				if constexpr (std::is_same_v<typename Vector2<BContainedT_>::nonref_value_type_without_qualifiers, HighestFP>)
				{
					return Vector2<OutT>
					(
						xfp + (b.x - xfp) * tfp,
						y + (b.y - yfp) * tfp
					);
				}
				else
				{
					return Vector2<OutT>
					(
						xfp + (static_cast<HighestFP>(b.x) - xfp) * tfp,
						yfp + (static_cast<HighestFP>(b.y) - yfp) * tfp
					);
				}
			}
		}
#pragma endregion

#pragma region VECTOR_OPERATIONS
		/// <summary>
		/// <para> Calculates the magnitude of this Vector. </para>
		/// <para> It is recommended to use SquareMagnitude over this where the final magnitude is not required, due to avoiding a square root calculation. </para>
		/// <para> Note that the output type must be a valid floating point type. If not, a static assertion will be triggered. </para>
		/// </summary>
		/// <typeparam name="OutT">Type to output the magnitude as.</typeparam>
		/// <returns>The magnitude of this Vector, represented as the provided OutT type (defaults to this Vector's default_floating_point).</returns>
		template<typename OutT = default_floating_point>
		OutT Magnitude() const
		{
			if constexpr (std::is_floating_point_v<OutT>)
			{
				using NonQualifiedOutT = std::remove_cv_t<OutT>;
				if constexpr (std::is_same_v<NonQualifiedOutT, float>)
				{
					return sqrtf(this->SquareMagnitude<float>());
				}
				else if constexpr (std::is_same_v<NonQualifiedOutT, double>)
				{
					return sqrt(this->SquareMagnitude<double>());
				}
				else if constexpr (std::is_same_v<NonQualifiedOutT, long double>)
				{
					return sqrtl(this->SquareMagnitude<long double>());
				}
				else
				{
					return static_cast<OutT>(info_type::_default_floating_point_sqrt(this->SquareMagnitude<default_floating_point>()));
				}
			}
			else
			{
				static_assert(false, "Attempted to retrieve a non-floating-point magnitude from an EmuMath::Vector2, which is not allowed.");
			}
		}
		/// <summary>
		/// <para> Calculates the square magnitude of this Vector (that is, the magnitude of this Vector before finding the square root). </para>
		/// <para> It is recommended to use this instead of Magnitude where the final magnitude is not required, due to avoiding a square root calculation. </para>
		/// </summary>
		/// <typeparam name="OutT">Type to output the square magnitude as.</typeparam>
		/// <returns>The square magnitude of this Vector, represented as the provided OutT type (defaults to this Vector's nonref_value_type).</returns>
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
		/// <summary>
		/// <para> Returns a normalised Vector from this Vector's components, stored as optionally customisable floating point types. </para>
		/// <para> Note that the output type must be a valid floating point type. If not, a static assertion will be triggered. </para>
		/// </summary>
		/// <typeparam name="OutT">Type to output as. Must be a floating point type.</typeparam>
		/// <returns>Normalised version of this Vector, with its contained elements stored as the provided OutT (defaults to this Vector's default_floating_point).</returns>
		template<typename OutT = default_floating_point>
		Vector2<OutT> AsNormalised() const
		{
			if constexpr (std::is_floating_point_v<OutT>)
			{
				using NonQualifiedOutT = std::remove_cv_t<OutT>;
				const NonQualifiedOutT reciprocal = EmuCore::ArithmeticHelpers::OneT<NonQualifiedOutT> / this->Magnitude<NonQualifiedOutT>();
				if constexpr (std::is_same_v<nonref_value_type_without_qualifiers, NonQualifiedOutT>)
				{
					return { x * reciprocal, y * reciprocal };
				}
				else
				{
					return { static_cast<NonQualifiedOutT>(x) * reciprocal, static_cast<NonQualifiedOutT>(y) * reciprocal };
				}
			}
			else
			{
				static_assert(false, "Attempted to retrieve a non-floating-point normalised Vector from an EmuMath::Vector2, which is not allowed.");
				return {};
			}
		}
		/// <summary>
		/// <para> Returns the dot product of this Vector and the provided Vector, output as an optionally customisable type. </para>
		/// </summary>
		/// <typeparam name="RhsT">Type contained within the passed Vector.</typeparam>
		/// <typeparam name="OutT">Type to output. Defaults to this Vector's nonref_value_type.</typeparam>
		/// <param name="rhs">Vector to calculate a dot product with.</param>
		/// <returns>Dot product of this Vector and the provided Vector, represented as this Vector's nonref_value_type or an optional provided type.</returns>
		template<typename RhsT, typename OutT = nonref_value_type>
		constexpr OutT DotProduct(const Vector2<RhsT>& rhs) const
		{
			if constexpr (info_type::has_floating_point_values || info_type_t<RhsT>::has_floating_point_values)
			{
				using ThisFP = EmuCore::TMPHelpers::best_floating_point_rep_t<nonref_value_type_without_qualifiers>;
				using RhsFP = EmuCore::TMPHelpers::best_floating_point_rep_t<typename Vector2<RhsT>::nonref_value_type_without_qualifiers>;
				using OutFP = EmuCore::TMPHelpers::best_floating_point_rep_t<OutT>;
				using CalcT = EmuCore::TMPHelpers::highest_byte_size_t<ThisFP, RhsFP, OutFP>;

				return static_cast<OutT>
				(
					(static_cast<CalcT>(x) * rhs.x) +
					(static_cast<CalcT>(y) * rhs.y)
				);
			}
			else
			{
				using HighestVecT = EmuCore::TMPHelpers::highest_byte_size<nonref_value_type_without_qualifiers, typename Vector2<RhsT>::nonref_value_type_without_qualifiers>;
				using HighestT = EmuCore::TMPHelpers::highest_byte_size_t<HighestVecT, OutT>;
				using CalcT = std::conditional_t
				<
					EmuCore::TMPHelpers::is_any_signed_v<nonref_value_type_without_qualifiers, typename Vector2<RhsT>::nonref_value_type_without_qualifiers>,
					EmuCore::TMPHelpers::best_signed_rep_t<HighestT>,
					HighestT
				>;

				return static_cast<OutT>
				(
					(static_cast<CalcT>(x) * rhs.x) +
					(static_cast<CalcT>(y) * rhs.y)
				);
			}
		}
		/// <summary>
		/// <para> Returns the dot product of this Vector and the provided Vector, output as an optionally customisable type. </para>
		/// </summary>
		/// <typeparam name="RhsT">Type contained within the passed Vector.</typeparam>
		/// <typeparam name="OutT">Type to output. Defaults to this Vector's nonref_value_type.</typeparam>
		/// <param name="rhs">Vector to calculate a dot product with.</param>
		/// <returns>Dot product of this Vector and the provided Vector, represented as this Vector's nonref_value_type or an optional provided type.</returns>
		template<typename RhsT, typename OutT = nonref_value_type>
		constexpr OutT DotProduct(const Vector3<RhsT>& rhs) const
		{
			using RhsNonRef = typename info_type_t<RhsT>::nonref_value_type;
			return this->DotProduct<RhsNonRef, OutT>(Vector2<RhsNonRef>(rhs.x, rhs.y));
		}
		/// <summary>
		/// <para> Returns a boolean indicating if the provided target vector is within the provided distance of this vector. </para>
		/// <para>
		///		Recommended to use WithinSquareDistance over this if possible as it avoids a square root and may be evaluable at compile time if needed. 
		///		The only change needed for your parameters to do so will be to multiply maxDistance by itself.
		/// </para>
		/// </summary>
		/// <typeparam name="OtherT">Type contained within the target vector.</typeparam>
		/// <typeparam name="MaxDistT">Type used to represent the max distance.</typeparam>
		/// <param name="target">Target vector to calculate the distance between.</param>
		/// <param name="maxDistance">Maximum distance between this vector and the target vector before this function returns false.</param>
		/// <returns>Boolean indicating if the target vector was within maxDistance (true) or not (false).</returns>
		template<typename OtherT, typename MaxDistT>
		bool WithinDistance(const Vector2<OtherT>& target, const MaxDistT& maxDistance) const
		{
			using ThisFP = EmuCore::TMPHelpers::best_floating_point_rep_t<nonref_value_type_without_qualifiers>;
			using TargetFP = EmuCore::TMPHelpers::best_floating_point_rep_t<typename Vector2<OtherT>::nonref_value_type_without_qualifiers>;
			using MaxDistFP = EmuCore::TMPHelpers::best_floating_point_rep_t<MaxDistT>;
			using HighestFP = EmuCore::TMPHelpers::highest_byte_size_t<ThisFP, TargetFP, MaxDistFP>;

			return Vector2<HighestFP>
			(
				static_cast<HighestFP>(target.x) - x,
				static_cast<HighestFP>(target.y - y)
			).Magnitude<HighestFP>() <= maxDistance;
		}
		/// <summary>
		/// <para> Returns a boolean indicating if the provided target vector is within the provided square distance of this vector. </para>
		/// <para> Recommended to use this over WithinDistance if possible as it avoids a square root and may be evaluable at compile time if needed. </para>
		/// </summary>
		/// <typeparam name="OtherT">Type contained within the target vector.</typeparam>
		/// <typeparam name="MaxDistT">Type used to represent the max square distance.</typeparam>
		/// <param name="target">Target vector to calculate the square distance between.</param>
		/// <param name="maxSquareDistance">Maximum square distance between this vector and the target vector before this function returns false.</param>
		/// <returns>Boolean indicating if the target vector was within maxSquareDistance (true) or not (false).</returns>
		template<typename OtherT, typename MaxDistT>
		constexpr bool WithinSquareDistance(const Vector2<OtherT>& target, const MaxDistT& maxSquareDistance) const
		{
			constexpr bool ThisOrTargetIsFP = info_type::has_floating_point_values || info_type_t<OtherT>::has_floating_point_values;
			constexpr bool MaxDistTIsFP = std::is_floating_point_v<MaxDistT>;
			if constexpr (!(ThisOrTargetIsFP || MaxDistTIsFP))
			{
				// Since we know we're working with integers, use the highest-sized type as an unsigned rep to support higher bound values.
				using HighestType = EmuCore::TMPHelpers::highest_byte_size_t
				<
					nonref_value_type_without_qualifiers,
					typename Vector2<OtherT>::nonref_value_type_without_qualifiers,
					MaxDistT
				>;
				using HighestUnsigned = EmuCore::TMPHelpers::best_unsigned_int_rep_t<HighestType>;

				return Vector2<HighestUnsigned>
				(
					static_cast<HighestUnsigned>(target.x) - x,
					static_cast<HighestUnsigned>(target.y) - y
				).SquareMagnitude<HighestUnsigned>() <= maxSquareDistance;
			}
			else
			{
				using ThisFP = EmuCore::TMPHelpers::best_floating_point_rep_t<nonref_value_type_without_qualifiers>;
				using TargetFP = EmuCore::TMPHelpers::best_floating_point_rep_t<typename Vector2<OtherT>::nonref_value_type_without_qualifiers>;
				using MaxDistFP = EmuCore::TMPHelpers::best_floating_point_rep_t<MaxDistT>;
				using HighestFP = EmuCore::TMPHelpers::highest_byte_size_t<ThisFP, TargetFP, MaxDistFP>;

				return Vector2<HighestFP>
				(
					static_cast<HighestFP>(target.x) - x,
					static_cast<HighestFP>(target.y) - y
				).SquareMagnitude<HighestFP>() <= maxSquareDistance;
			}
		}
		/// <summary>
		/// <para> Returns a reversed version of this Vector, with an optional different type. </para>
		/// </summary>
		/// <typeparam name="OutT">Type for the returned Vector to contain. Defaults to this Vector's nonref_value_type.</typeparam>
		/// <returns>Reversed version of this Vector.</returns>
		template<typename OutT = nonref_value_type>
		constexpr Vector2<OutT> AsReversed() const
		{
			if constexpr (std::is_signed_v<nonref_value_type>)
			{
				return { -x, -y };
			}
			else
			{
				using HighestSigned = EmuCore::TMPHelpers::best_signed_rep_t<EmuCore::TMPHelpers::highest_byte_size_t<OutT, nonref_value_type>>;
				return { -static_cast<HighestSigned>(x), -static_cast<HighestSigned>(y) };
			}
		}
#pragma endregion

		/// <summary> The first component of this vector, representing the X-axis. </summary>
		value_type x;
		/// <summary> The second component of this vector, representing the Y-axis. </summary>
		value_type y;

	private:
#pragma region PRIVATE_HELPERS
		template<std::size_t Index, typename T_>
		constexpr void _set_individual_value(const T_& val_)
		{
			if constexpr (std::is_same_v<nonref_value_type_without_qualifiers, std::remove_reference_t<T_>>)
			{
				at<Index>() = val_;
			}
			else
			{
				at<Index>() = static_cast<nonref_value_type>(val_);
			}
		}

		template<typename RhsVec, typename OutVector>
		constexpr OutVector _perform_addition(const RhsVec& rhs) const
		{
			return this->_perform_vector_arithmetic_emu<RhsVec, OutVector, EmuCore::TMPHelpers::plus_diff_types>(rhs);
		}
		template<typename RhsVec, typename OutVector>
		constexpr OutVector _perform_subtraction(const RhsVec& rhs) const
		{
			return this->_perform_vector_arithmetic_emu<RhsVec, OutVector, EmuCore::TMPHelpers::minus_diff_types>(rhs);
		}
		template<typename RhsVec, typename OutVector>
		constexpr OutVector _perform_vector_multiplication(const RhsVec& rhs) const
		{
			return this->_perform_vector_arithmetic_emu<RhsVec, OutVector, EmuCore::TMPHelpers::multiplies_diff_types>(rhs);
		}
		template<typename RhsT, typename OutVector>
		constexpr OutVector _perform_scalar_multiplication(const RhsT& rhs) const
		{
			return this->_perform_scalar_arithmetic_emu<RhsT, OutVector, EmuCore::TMPHelpers::multiplies_diff_types>(rhs);
		}
		template<typename RhsVec, typename OutVector>
		constexpr OutVector _perform_vector_division(const RhsVec& rhs) const
		{
			return this->_perform_vector_arithmetic_emu<RhsVec, OutVector, EmuCore::TMPHelpers::divides_diff_types>(rhs);
		}
		template<typename RhsT, typename OutVector>
		constexpr OutVector _perform_scalar_division(const RhsT& rhs) const
		{
			return this->_perform_scalar_arithmetic_emu<RhsT, OutVector, EmuCore::TMPHelpers::divides_diff_types>(rhs);
		}
		template<typename RhsVec, typename OutVector>
		constexpr OutVector _perform_vector_mod(const RhsVec& rhs) const
		{
			return this->_perform_vector_arithmetic_emu<RhsVec, OutVector, EmuCore::TMPHelpers::modulus_diff_types>(rhs);
		}
		template<typename RhsT, typename OutVector>
		constexpr OutVector _perform_scalar_mod(const RhsT& rhs) const
		{
			return this->_perform_scalar_arithmetic_emu<RhsT, OutVector, EmuCore::TMPHelpers::modulus_diff_types>(rhs);
		}

		template<typename RhsVec, typename OutVector>
		constexpr OutVector _perform_vector_and(const RhsVec& rhs) const
		{
			return this->_perform_vector_bitwise_op_emu<RhsVec, OutVector, EmuCore::TMPHelpers::logical_and_diff_types>(rhs);
		}
		template<typename RhsT, typename OutVector>
		constexpr OutVector _perform_scalar_and(const RhsT& rhs) const
		{
			return this->_perform_scalar_bitwise_op_emu<RhsT, OutVector, EmuCore::TMPHelpers::logical_and_diff_types>(rhs);
		}

		template<typename RhsVec, typename OutVector>
		constexpr OutVector _perform_vector_or(const RhsVec& rhs) const
		{
			return this->_perform_vector_bitwise_op_emu<RhsVec, OutVector, EmuCore::TMPHelpers::logical_or_diff_types>(rhs);
		}
		template<typename RhsT, typename OutVector>
		constexpr OutVector _perform_scalar_or(const RhsT& rhs) const
		{
			return this->_perform_scalar_bitwise_op_emu<RhsT, OutVector, EmuCore::TMPHelpers::logical_or_diff_types>(rhs);
		}

		template<typename RhsVec, typename OutVector>
		constexpr OutVector _perform_vector_xor(const RhsVec& rhs) const
		{
			return this->_perform_vector_bitwise_op_emu<RhsVec, OutVector, EmuCore::TMPHelpers::logical_xor_diff_types>(rhs);
		}
		template<typename RhsT, typename OutVector>
		constexpr OutVector _perform_scalar_xor(const RhsT& rhs) const
		{
			return this->_perform_scalar_bitwise_op_emu<RhsT, OutVector, EmuCore::TMPHelpers::logical_xor_diff_types>(rhs);
		}

		template<typename RhsVec, typename OutVector>
		constexpr OutVector _perform_vector_per_element_leftshift(const RhsVec& numShifts) const
		{
			return this->_perform_vector_bitwise_op_emu<RhsVec, OutVector, EmuCore::TMPHelpers::bitwise_shift_left_diff_types>(numShifts);
		}
		template<typename RhsT, typename OutVector>
		constexpr OutVector _perform_scalar_per_element_leftshift(const RhsT& numShifts) const
		{
			return this->_perform_scalar_bitwise_op_emu<RhsT, OutVector, EmuCore::TMPHelpers::bitwise_shift_left_diff_types>(numShifts);
		}

		template<typename RhsVec, typename OutVector>
		constexpr OutVector _perform_vector_per_element_rightshift(const RhsVec& numShifts) const
		{
			return this->_perform_vector_bitwise_op_emu<RhsVec, OutVector, EmuCore::TMPHelpers::bitwise_shift_right_diff_types>(numShifts);
		}
		template<typename RhsT, typename OutVector>
		constexpr OutVector _perform_scalar_per_element_rightshift(const RhsT& numShifts) const
		{
			return this->_perform_scalar_bitwise_op_emu<RhsT, OutVector, EmuCore::TMPHelpers::bitwise_shift_right_diff_types>(numShifts);
		}

		template<typename OutVector>
		constexpr OutVector _perform_inversion() const
		{
			using Func = EmuCore::TMPHelpers::bit_inversion_diff_types<nonref_value_type_without_qualifiers, typename OutVector::value_type>;
			Func func = Func();
			if constexpr (OutVector::size() == 2)
			{
				return OutVector
				(
					func(x),
					func(y)
				);
			}
			else if constexpr (OutVector::size() == 3)
			{
				return OutVector
				(
					func(x),
					func(y),
					func(info_type::value_zero)
				);
			}
			else if constexpr (OutVector::size() == 4)
			{
				const auto& zero_ = info_type::value_zero;
				return OutVector
				(
					func(x),
					func(y),
					func(zero_),
					func(zero_)
				);
			}
			else
			{
				static_assert(false, "Attempted to perform a bit inversion on an EmuMath::Vector2 with an unsupported size of output Vector.");
			}
		}

		/// <summary> Template for performing bitwise operations on this Vector via another Vector, using EmuCore bitwise op functors. </summary>
		/// <typeparam name="RhsVec">Type of the right-hand side Vector.</typeparam>
		/// <typeparam name="OutVector">Type of Vector to output the result as.</typeparam>
		/// <param name="rhs">Vector to perform bitwise operations on the respective values of this Vector with.</param>
		/// <returns>Result of the bitwise operation stored as the provided OutVector type.</returns>
		template<typename RhsVec, typename OutVector, template<typename LhsT_, typename RhsT_, typename OutT_> typename Func_>
		constexpr OutVector _perform_vector_bitwise_op_emu(const RhsVec& rhs) const
		{
			using EndFunc = Func_
			<
				nonref_value_type_without_qualifiers,
				typename RhsVec::nonref_value_type_without_qualifiers,
				typename OutVector::value_type
			>;
			EndFunc func = EndFunc();
			if constexpr (OutVector::size() == 2)
			{
				return OutVector
				(
					func(x, rhs.x),
					func(y, rhs.y)
				);
			}
			else if constexpr (OutVector::size() == 3)
			{
				return OutVector
				(
					func(x, rhs.x),
					func(y, rhs.y),
					func(info_type::value_zero, EmuMath::TMPHelpers::emu_vector_z(rhs))
				);
			}
			else if constexpr (OutVector::size() == 4)
			{
				return OutVector
				(
					func(x, rhs.x),
					func(y, rhs.y),
					func(info_type::value_zero, EmuMath::TMPHelpers::emu_vector_z(rhs)),
					func(info_type::value_zero, EmuMath::TMPHelpers::emu_vector_w(rhs))
				);
			}
			else
			{
				static_assert(false, "Attempted to perform a bitwise operation on an EmuMath::Vector2 with an unsupported size of output Vector.");
			}
		}

		/// <summary> Template for performing bitwise operations on this Vector via a scalar value, using EmuCore bitwise op functors. </summary>
		/// <typeparam name="RhsT">Type of the right-hand side scalar.</typeparam>
		/// <typeparam name="OutVector">Type of Vector to output the result as.</typeparam>
		/// <param name="rhs">Scalar value to perform bitwise operations on all values of this Vector with.</param>
		/// <returns>Result of the bitwise operation stored as the provided OutVector type.</returns>
		template<typename RhsT, typename OutVector, template<typename LhsT_, typename RhsT_, typename OutT_> typename Func_>
		constexpr OutVector _perform_scalar_bitwise_op_emu(const RhsT& rhs) const
		{
			using EndFunc = Func_
			<
				nonref_value_type_without_qualifiers,
				RhsT,
				typename OutVector::value_type
			>;
			EndFunc func = EndFunc();
			if constexpr (OutVector::size() == 2)
			{
				return OutVector
				(
					func(x, rhs),
					func(y, rhs)
				);
			}
			else if constexpr (OutVector::size() == 3)
			{
				return OutVector
				(
					func(x, rhs),
					func(y, rhs),
					func(info_type::value_zero, rhs)
				);
			}
			else if constexpr (OutVector::size() == 4)
			{
				return OutVector
				(
					func(x, rhs),
					func(y, rhs),
					func(info_type::value_zero, rhs),
					func(info_type::value_zero, rhs)
				);
			}
			else
			{
				static_assert(false, "Attempted to perform a bitwise operation on an EmuMath::Vector2 with an unsupported size of output Vector.");
			}
		}

		/// <summary> Template for performing arithmetic on this Vector via another Vector, using EmuCore arithmetic functors. </summary>
		/// <typeparam name="RhsVec">Type of the right-hand side Vector.</typeparam>
		/// <typeparam name="OutVector">Type of Vector to output the result as.</typeparam>
		/// <param name="rhs">Vector to perform arithmetic on the respective values of this Vector with.</param>
		/// <returns>Result of the arithmetic operation stored as the provided OutVector type.</returns>
		template<typename RhsVec, typename OutVector, template<typename LhsT_, typename RhsT_, typename OutT_> typename Func_>
		constexpr OutVector _perform_vector_arithmetic_emu(const RhsVec& rhs) const
		{
			using OutT = typename OutVector::nonref_value_type_without_qualifiers;
			using RhsT = typename RhsVec::nonref_value_type_without_qualifiers;
			if constexpr (info_type::has_floating_point_values || info_type_t<typename RhsVec::value_type>::has_floating_point_values)
			{
				// Floating points involved in addition so care needs to be taken to not accidentally lose fractions if needed in output
				using ThisFP = EmuCore::TMPHelpers::best_floating_point_rep_t<nonref_value_type_without_qualifiers>;
				using RhsFP = EmuCore::TMPHelpers::best_floating_point_rep_t<RhsT>;
				using OutFP = EmuCore::TMPHelpers::best_floating_point_rep_t<OutT>;
				using HighestFP = EmuCore::TMPHelpers::highest_byte_size_t<ThisFP, RhsFP, OutFP>;

				using EndFunc = Func_<HighestFP, RhsT, HighestFP>;
				EndFunc func = EndFunc();
				if constexpr (OutVector::size() == 2)
				{
					return OutVector
					(
						func(static_cast<HighestFP>(x), rhs.x),
						func(static_cast<HighestFP>(y), rhs.y)
					);
				}
				else if constexpr (OutVector::size() == 3)
				{
					return OutVector
					(
						func(static_cast<HighestFP>(x), rhs.x),
						func(static_cast<HighestFP>(y), rhs.y),
						func(EmuCore::ArithmeticHelpers::ZeroT<HighestFP>, EmuMath::TMPHelpers::emu_vector_z<RhsVec>(rhs))
					);
				}
				else if constexpr (OutVector::size() == 4)
				{
					const HighestFP zeroHighest = EmuCore::ArithmeticHelpers::ZeroT<HighestFP>;
					return OutVector
					(
						func(static_cast<HighestFP>(x) + rhs.x),
						func(static_cast<HighestFP>(y) + rhs.y),
						func(zeroHighest, EmuMath::TMPHelpers::emu_vector_z(rhs)),
						func(zeroHighest, EmuMath::TMPHelpers::emu_vector_w(rhs))
					);
				}
			}
			else
			{
				// No floating points to worry about in addition
				using HighestT = EmuCore::TMPHelpers::highest_byte_size_t<nonref_value_type_without_qualifiers, RhsT, OutT>;
				using EndFunc = Func_<HighestT, RhsT, HighestT>;
				EndFunc func = EndFunc();

				if constexpr (OutVector::size() == 2)
				{
					return Vector2<OutT>
					(
						func(static_cast<HighestT>(x), rhs.x),
						func(static_cast<HighestT>(y), rhs.y)
					);
				}
				else if constexpr (OutVector::size() == 3)
				{
					return OutVector
					(
						func(static_cast<HighestT>(x), rhs.x),
						func(static_cast<HighestT>(y), rhs.y),
						func(EmuCore::ArithmeticHelpers::ZeroT<HighestT>, EmuMath::TMPHelpers::emu_vector_z(rhs))
					);
				}
				else if constexpr (OutVector::size() == 4)
				{
					const HighestT zeroHighest = EmuCore::ArithmeticHelpers::ZeroT<HighestT>;
					return OutVector
					(
						func(static_cast<HighestT>(x), rhs.x),
						func(static_cast<HighestT>(y), rhs.y),
						func(zeroHighest, EmuMath::TMPHelpers::emu_vector_z(rhs)),
						func(zeroHighest, EmuMath::TMPHelpers::emu_vector_w(rhs))
					);
				}
			}
		}

		/// <summary> Template for performing arithmetic on this Vector via a scalar value, using EmuCore arithmetic functors. </summary>
		/// <typeparam name="RhsT">Type of the right-hand side scalar.</typeparam>
		/// <typeparam name="OutVector">Type of Vector to output the result as.</typeparam>
		/// <param name="rhs">Scalar value to perform arithmetic on all values of this Vector with.</param>
		/// <returns>Result of the arithmetic operation stored as the provided OutVector type.</returns>
		template<typename RhsT, typename OutVector, template<typename LhsT_, typename RhsT_, typename OutT_> typename Func_>
		constexpr OutVector _perform_scalar_arithmetic_emu(const RhsT& rhs) const
		{
			using OutT = typename OutVector::nonref_value_type_without_qualifiers;
			if constexpr (info_type::has_floating_point_values || std::is_floating_point_v<RhsT>)
			{
				// Floating points involved so care needs to be taken to not accidentally lose fractions if needed in output
				using ThisFP = EmuCore::TMPHelpers::best_floating_point_rep_t<nonref_value_type_without_qualifiers>;
				using RhsFP = EmuCore::TMPHelpers::best_floating_point_rep_t<RhsT>;
				using OutFP = EmuCore::TMPHelpers::best_floating_point_rep_t<OutT>;
				using HighestFP = EmuCore::TMPHelpers::highest_byte_size_t<ThisFP, RhsFP, OutFP>;
				using EndFunc = Func_<HighestFP, HighestFP, HighestFP>;
				EndFunc func = EndFunc();
				const HighestFP rhsFp = static_cast<HighestFP>(rhs);
				if constexpr (OutVector::size() == 2)
				{
					return OutVector
					(
						func(static_cast<HighestFP>(x), rhsFp),
						func(static_cast<HighestFP>(y), rhsFp)
					);
				}
				else if constexpr (OutVector::size() == 3)
				{
					return OutVector
					(
						func(static_cast<HighestFP>(x), rhsFp),
						func(static_cast<HighestFP>(y), rhsFp),
						func(EmuCore::ArithmeticHelpers::ZeroT<HighestFP>, rhsFp)
					);
				}
				else if constexpr (OutVector::size() == 4)
				{
					const HighestFP zeroHighest = EmuCore::ArithmeticHelpers::ZeroT<HighestFP>;
					return OutVector
					(
						func(static_cast<HighestFP>(x), rhsFp),
						func(static_cast<HighestFP>(y), rhsFp),
						func(zeroHighest, rhsFp),
						func(zeroHighest, rhsFp)
					);
				}
			}
			else
			{
				// No floating points to worry about
				using HighestT = EmuCore::TMPHelpers::highest_byte_size_t<nonref_value_type_without_qualifiers, RhsT, OutT>;
				using EndFunc = Func_<HighestT, HighestT, HighestT>;
				EndFunc func = EndFunc();
				const HighestT rhsHighest = static_cast<HighestT>(rhs);


				if constexpr (OutVector::size() == 2)
				{
					return Vector2<OutT>
					(
						func(static_cast<HighestT>(x), rhsHighest),
						func(static_cast<HighestT>(y), rhsHighest)
					);
				}
				else if constexpr (OutVector::size() == 3)
				{
					return OutVector
					(
						func(static_cast<HighestT>(x), rhsHighest),
						func(static_cast<HighestT>(y), rhsHighest),
						func(EmuCore::ArithmeticHelpers::ZeroT<HighestT>, rhsHighest)
					);
				}
				else if constexpr (OutVector::size() == 4)
				{
					const HighestT zeroHighest = EmuCore::ArithmeticHelpers::ZeroT<HighestT>;
					return OutVector
					(
						func(static_cast<HighestT>(x), rhsHighest),
						func(static_cast<HighestT>(y), rhsHighest),
						func(zeroHighest, rhsHighest),
						func(zeroHighest, rhsHighest)
					);
				}
			}
		}

		/// <summary> Template for performing arithmetic on this Vector via another Vector, using standard arithmetic functors. </summary>
		/// <typeparam name="RhsVec">Type of the right-hand side Vector.</typeparam>
		/// <typeparam name="OutVector">Type of Vector to output the result as.</typeparam>
		/// <param name="rhs">Vector to perform arithmetic on the respective values of this Vector with.</param>
		/// <returns>Result of the arithmetic operation stored as the provided OutVector type.</returns>
		template<typename RhsVec, typename OutVector, template<typename FuncT_> typename Func_>
		constexpr OutVector _perform_vector_arithmetic_std(const RhsVec& rhs) const
		{
			using OutT = typename OutVector::nonref_value_type_without_qualifiers;
			using RhsT = typename RhsVec::nonref_value_type_without_qualifiers;
			if constexpr (info_type::has_floating_point_values || info_type_t<typename RhsVec::value_type>::has_floating_point_values)
			{
				// Floating points involved in addition so care needs to be taken to not accidentally lose fractions if needed in output
				using ThisFP = EmuCore::TMPHelpers::best_floating_point_rep_t<nonref_value_type_without_qualifiers>;
				using RhsFP = EmuCore::TMPHelpers::best_floating_point_rep_t<RhsT>;
				using OutFP = EmuCore::TMPHelpers::best_floating_point_rep_t<OutT>;
				using HighestFP = EmuCore::TMPHelpers::highest_byte_size_t<ThisFP, RhsFP, OutFP>;
		
				using EndFunc = Func_<HighestFP>;
				EndFunc func = EndFunc();
				if constexpr (OutVector::size() == 2)
				{
					return OutVector
					(
						func(static_cast<HighestFP>(x), static_cast<HighestFP>(rhs.x)),
						func(static_cast<HighestFP>(y), static_cast<HighestFP>(rhs.y))
					);
				}
				else if constexpr (OutVector::size() == 3)
				{
					return OutVector
					(
						func(static_cast<HighestFP>(x), static_cast<HighestFP>(rhs.x)),
						func(static_cast<HighestFP>(y), static_cast<HighestFP>(rhs.y)),
						func(EmuCore::ArithmeticHelpers::ZeroT<HighestFP>, EmuMath::TMPHelpers::emu_vector_z<RhsVec>(rhs))
					);
				}
				else if constexpr (OutVector::size() == 4)
				{
					const HighestFP zeroHighest = EmuCore::ArithmeticHelpers::ZeroT<HighestFP>;
					return OutVector
					(
						func(static_cast<HighestFP>(x) + rhs.x),
						func(static_cast<HighestFP>(y) + rhs.y),
						func(zeroHighest, static_cast<HighestFP>(EmuMath::TMPHelpers::emu_vector_z(rhs))),
						func(zeroHighest, static_cast<HighestFP>(EmuMath::TMPHelpers::emu_vector_w(rhs)))
					);
				}
			}
			else
			{
				// No floating points to worry about in addition
				using HighestT = EmuCore::TMPHelpers::highest_byte_size_t<nonref_value_type_without_qualifiers, RhsT, OutT>;
				using EndFunc = Func_<HighestT>;
				EndFunc func = EndFunc();
		
				if constexpr (OutVector::size() == 2)
				{
					return Vector2<OutT>
					(
						func(static_cast<HighestT>(x), static_cast<HighestT>(rhs.x)),
						func(static_cast<HighestT>(y), static_cast<HighestT>(rhs.y))
					);
				}
				else if constexpr (OutVector::size() == 3)
				{
					return OutVector
					(
						func(static_cast<HighestT>(x), rhs.x),
						func(static_cast<HighestT>(y), rhs.y),
						func(EmuCore::ArithmeticHelpers::ZeroT<HighestT>, static_cast<HighestT>(EmuMath::TMPHelpers::emu_vector_z(rhs)))
					);
				}
				else if constexpr (OutVector::size() == 4)
				{
					const HighestT zeroHighest = EmuCore::ArithmeticHelpers::ZeroT<HighestT>;
					return OutVector
					(
						func(static_cast<HighestT>(x), rhs.x),
						func(static_cast<HighestT>(y), rhs.y),
						func(zeroHighest, static_cast<HighestT>(EmuMath::TMPHelpers::emu_vector_z(rhs))),
						func(zeroHighest, static_cast<HighestT>(EmuMath::TMPHelpers::emu_vector_w(rhs)))
					);
				}
			}
		}
#pragma endregion
	};
}

#endif
