#ifndef EMU_MATH_VECTOR_2_T_H_INC_
#define EMU_MATH_VECTOR_2_T_H_INC_

#include "EmuVectorInfo.h"
#include "../../EmuCore/TMPHelpers/Functors.h"
#include "../../EmuCore/TMPHelpers/TypeComparators.h"
#include "../../EmuCore/TMPHelpers/TypeConvertors.h"
#include "EmuVectorTMPHelpers.h"
#include "VectorHelpers.h"
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
		/// <summary> The overall type of EmuMath Vector that this type is. </summary>
		using emu_vector_type = Vector2<T>;
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

		/// <summary> The type of Vector created when getting a copy of this Vector's data (used to get copy values instead of references). </summary>
		using copy_vector = typename EmuMath::TMPHelpers::emu_vector_copy<emu_vector_type>::type;
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
		/// <summary> Constructs a 2-dimensional vector with its x and y components set to copies of the passed vector's respective components, performing casts where needed. </summary>
		/// <typeparam name="OtherT">The contained type within the passed Vector3.</typeparam>
		/// <param name="toCopy">Vector to copy the elements of.</param>
		template<typename OtherT>
		explicit constexpr Vector2(const EmuMath::Vector4<OtherT>& toCopy) :
			Vector2(toCopy.x, toCopy.y)
		{
		}
		/// <summary> Constructs a 2-dimensional vector with its x and y components set to copies of the passed vector's respective components, performing casts where needed. </summary>
		/// <typeparam name="OtherT">The contained type within the passed Vector3.</typeparam>
		/// <param name="toCopy">Vector to copy the elements of.</param>
		template<typename OtherT>
		explicit constexpr Vector2(EmuMath::Vector4<OtherT>& toCopy) :
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
			return EmuMath::Helpers::VectorAddition<Vector2<nonref_value_type>>(*this, rhs);
		}
		template<typename RhsT>
		constexpr Vector2<nonref_value_type> operator+(const Vector3<RhsT>& rhs) const
		{
			return EmuMath::Helpers::VectorAddition<Vector2<nonref_value_type>>(*this, rhs);
		}
		template<typename RhsT>
		constexpr Vector2<nonref_value_type> operator+(const Vector4<RhsT>& rhs) const
		{
			return EmuMath::Helpers::VectorAddition<Vector2<nonref_value_type>>(*this, rhs);
		}

		template<typename RhsT>
		constexpr Vector2<nonref_value_type> operator-(const Vector2<RhsT>& rhs) const
		{
			return EmuMath::Helpers::VectorSubtraction<Vector2<nonref_value_type>>(*this, rhs);
		}
		template<typename RhsT>
		constexpr Vector2<nonref_value_type> operator-(const Vector3<RhsT>& rhs) const
		{
			return EmuMath::Helpers::VectorSubtraction<Vector2<nonref_value_type>>(*this, rhs);
		}
		constexpr Vector2<nonref_value_type> operator-() const
		{
			return this->Reverse();
		}

		template<typename RhsT>
		constexpr Vector2<nonref_value_type> operator*(const RhsT& rhs) const
		{
			return EmuMath::Helpers::VectorMultiplication<Vector2<nonref_value_type>>(*this, rhs);
		}

		template<typename RhsT>
		constexpr Vector2<nonref_value_type> operator/(const RhsT& rhs) const
		{
			return EmuMath::Helpers::VectorDivision<Vector2<nonref_value_type>>(*this, rhs);
		}

		template<typename RhsT>
		constexpr Vector2<nonref_value_type> operator%(const RhsT& rhs) const
		{
			return EmuMath::Helpers::VectorMod<Vector2<nonref_value_type>>(*this, rhs);
		}
#pragma endregion

#pragma region BITWISE_CONST_OPERATORS
		template<typename OtherT>
		constexpr Vector2<nonref_value_type> operator&(const Vector2<OtherT>& rhs) const
		{
			return this->And<size(), nonref_value_type, OtherT>(rhs);
		}
		template<typename OtherT>
		constexpr Vector2<nonref_value_type> operator&(const Vector3<OtherT>& rhs) const
		{
			return this->And<size(), nonref_value_type, OtherT>(rhs);
		}
		template<typename OtherT>
		constexpr Vector2<nonref_value_type> operator&(const Vector4<OtherT>& rhs) const
		{
			return this->And<size(), nonref_value_type, OtherT>(rhs);
		}
		template<typename RhsT>
		constexpr Vector2<nonref_value_type> operator&(const RhsT& rhs) const
		{
			return this->And<size(), nonref_value_type, RhsT>(rhs);
		}
		template<typename OtherT>
		constexpr Vector2<nonref_value_type> operator|(const Vector2<OtherT>& rhs) const
		{
			return this->Or<size(), nonref_value_type, OtherT>(rhs);
		}
		template<typename OtherT>
		constexpr Vector2<nonref_value_type> operator|(const Vector3<OtherT>& rhs) const
		{
			return this->Or<size(), nonref_value_type, OtherT>(rhs);
		}
		template<typename OtherT>
		constexpr Vector2<nonref_value_type> operator|(const Vector4<OtherT>& rhs) const
		{
			return this->Or<size(), nonref_value_type, OtherT>(rhs);
		}
		template<typename RhsT>
		constexpr Vector2<nonref_value_type> operator|(const RhsT& rhs) const
		{
			return this->Or<size(), nonref_value_type, RhsT>(rhs);
		}
		template<typename OtherT>
		constexpr Vector2<nonref_value_type> operator^(const Vector2<OtherT>& rhs) const
		{
			return this->Xor<size(), nonref_value_type, OtherT>(rhs);
		}
		template<typename OtherT>
		constexpr Vector2<nonref_value_type> operator^(const Vector3<OtherT>& rhs) const
		{
			return this->Xor<size(), nonref_value_type, OtherT>(rhs);
		}
		template<typename OtherT>
		constexpr Vector2<nonref_value_type> operator^(const Vector4<OtherT>& rhs) const
		{
			return this->Xor<size(), nonref_value_type, OtherT>(rhs);
		}
		template<typename RhsT>
		constexpr Vector2<nonref_value_type> operator^(const RhsT& rhs) const
		{
			return this->Xor<size(), nonref_value_type, RhsT>(rhs);
		}
		template<typename OtherT>
		constexpr Vector2<nonref_value_type> operator<<(const Vector2<OtherT>& rhs) const
		{
			return this->LeftShiftPerElement<size(), nonref_value_type, OtherT>(rhs);
		}
		template<typename OtherT>
		constexpr Vector2<nonref_value_type> operator<<(const Vector3<OtherT>& rhs) const
		{
			return this->LeftShiftPerElement<size(), nonref_value_type, OtherT>(rhs);
		}
		template<typename OtherT>
		constexpr Vector2<nonref_value_type> operator<<(const Vector4<OtherT>& rhs) const
		{
			return this->LeftShiftPerElement<size(), nonref_value_type, OtherT>(rhs);
		}
		template<typename RhsT>
		constexpr Vector2<nonref_value_type> operator<<(const RhsT& rhs) const
		{
			return this->LeftShiftPerElement<size(), nonref_value_type, RhsT>(rhs);
		}
		template<typename OtherT>
		constexpr Vector2<nonref_value_type> operator>>(const Vector2<OtherT>& rhs) const
		{
			return this->RightShiftPerElement<size(), nonref_value_type, OtherT>(rhs);
		}
		template<typename OtherT>
		constexpr Vector2<nonref_value_type> operator>>(const Vector3<OtherT>& rhs) const
		{
			return this->RightShiftPerElement<size(), nonref_value_type, OtherT>(rhs);
		}
		template<typename OtherT>
		constexpr Vector2<nonref_value_type> operator>>(const Vector4<OtherT>& rhs) const
		{
			return this->RightShiftPerElement<size(), nonref_value_type, OtherT>(rhs);
		}
		template<typename RhsT>
		constexpr Vector2<nonref_value_type> operator>>(const RhsT& rhs) const
		{
			return this->RightShiftPerElement<size(), nonref_value_type, RhsT>(rhs);
		}
		constexpr Vector2<nonref_value_type> operator~() const
		{
			return this->Not();
		}

#pragma endregion

#pragma region ARITHMETIC_NONCONST_OPERATORS
		template<typename OtherT>
		constexpr Vector2<value_type>& operator+=(const Vector2<OtherT>& rhs)
		{
			*this = (*this + rhs);
			return *this;
		}
		template<typename OtherT>
		constexpr Vector2<value_type>& operator+=(const Vector3<OtherT>& rhs)
		{
			*this = (*this + rhs);
			return *this;
		}
		template<typename OtherT>
		constexpr Vector2<value_type>& operator+=(const Vector4<OtherT>& rhs)
		{
			*this = (*this + rhs);
			return *this;
		}

		template<typename OtherT>
		constexpr Vector2<value_type>& operator-=(const Vector2<OtherT>& rhs)
		{
			*this = (*this - rhs);
			return *this;
		}
		template<typename OtherT>
		constexpr Vector2<value_type>& operator-=(const Vector3<OtherT>& rhs)
		{
			*this = (*this - rhs);
			return *this;
		}
		template<typename OtherT>
		constexpr Vector2<value_type>& operator-=(const Vector4<OtherT>& rhs)
		{
			*this = (*this - rhs);
			return *this;
		}

		template<typename OtherT>
		constexpr Vector2<value_type>& operator*=(const Vector2<OtherT>& rhs)
		{
			*this = (*this * rhs);
			return *this;
		}
		template<typename OtherT>
		constexpr Vector2<value_type>& operator*=(const Vector3<OtherT>& rhs)
		{
			*this = (*this * rhs);
			return *this;
		}
		template<typename OtherT>
		constexpr Vector2<value_type>& operator*=(const Vector4<OtherT>& rhs)
		{
			*this = (*this * rhs);
			return *this;
		}
		template<typename RhsT>
		constexpr Vector2<value_type>& operator*=(const RhsT& rhs)
		{
			*this = (*this * rhs);
			return *this;
		}

		template<typename OtherT>
		constexpr Vector2<value_type>& operator/=(const Vector2<OtherT>& rhs)
		{
			*this = (*this / rhs);
			return *this;
		}
		template<typename OtherT>
		constexpr Vector2<value_type>& operator/=(const Vector3<OtherT>& rhs)
		{
			*this = (*this / rhs);
			return *this;
		}
		template<typename OtherT>
		constexpr Vector2<value_type>& operator/=(const Vector4<OtherT>& rhs)
		{
			*this = (*this / rhs);
			return *this;
		}
		template<typename RhsT>
		constexpr Vector2<value_type>& operator/=(const RhsT& rhs)
		{
			*this = (*this / rhs);
			return *this;
		}

		template<typename OtherT>
		constexpr Vector2<value_type>& operator%=(const Vector2<OtherT>& rhs)
		{
			*this = (*this % rhs);
			return *this;
		}
		template<typename OtherT>
		constexpr Vector2<value_type>& operator%=(const Vector3<OtherT>& rhs)
		{
			*this = (*this % rhs);
			return *this;
		}
		template<typename OtherT>
		constexpr Vector2<value_type>& operator%=(const Vector4<OtherT>& rhs)
		{
			*this = (*this % rhs);
			return *this;
		}
		template<typename RhsT>
		constexpr Vector2<value_type>& operator%=(const RhsT& rhs)
		{
			*this = (*this % rhs);
			return *this;
		}
#pragma endregion

#pragma region BITWISE_NONCONST_OPERATORS
		template<typename OtherT>
		constexpr Vector2<value_type>& operator&=(const Vector2<OtherT>& rhs)
		{
			*this = (*this & rhs);
			return *this;
		}
		template<typename OtherT>
		constexpr Vector2<value_type>& operator&=(const Vector3<OtherT>& rhs)
		{
			*this = (*this & rhs);
			return *this;
		}
		template<typename OtherT>
		constexpr Vector2<value_type>& operator&=(const Vector4<OtherT>& rhs)
		{
			*this = (*this & rhs);
			return *this;
		}
		template<typename RhsT>
		constexpr Vector2<value_type>& operator&=(const RhsT& rhs)
		{
			*this = (*this & rhs);
			return *this;
		}

		template<typename OtherT>
		constexpr Vector2<value_type>& operator|=(const Vector2<OtherT>& rhs)
		{
			*this = (*this | rhs);
			return *this;
		}
		template<typename OtherT>
		constexpr Vector2<value_type>& operator|=(const Vector3<OtherT>& rhs)
		{
			*this = (*this | rhs);
			return *this;
		}
		template<typename OtherT>
		constexpr Vector2<value_type>& operator|=(const Vector4<OtherT>& rhs)
		{
			*this = (*this | rhs);
			return *this;
		}
		template<typename RhsT>
		constexpr Vector2<value_type>& operator|=(const RhsT& rhs)
		{
			*this = (*this | rhs);
			return *this;
		}

		template<typename OtherT>
		constexpr Vector2<value_type>& operator^=(const Vector2<OtherT>& rhs)
		{
			*this = (*this ^ rhs);
			return *this;
		}
		template<typename OtherT>
		constexpr Vector2<value_type>& operator^=(const Vector3<OtherT>& rhs)
		{
			*this = (*this ^ rhs);
			return *this;
		}
		template<typename OtherT>
		constexpr Vector2<value_type>& operator^=(const Vector4<OtherT>& rhs)
		{
			*this = (*this ^ rhs);
			return *this;
		}
		template<typename RhsT>
		constexpr Vector2<value_type>& operator^=(const RhsT& rhs)
		{
			*this = (*this ^ rhs);
			return *this;
		}

		template<typename OtherT>
		constexpr Vector2<value_type>& operator<<=(const Vector2<OtherT>& rhs)
		{
			*this = (*this << rhs);
			return *this;
		}
		template<typename OtherT>
		constexpr Vector2<value_type>& operator<<=(const Vector3<OtherT>& rhs)
		{
			*this = (*this << rhs);
			return *this;
		}
		template<typename OtherT>
		constexpr Vector2<value_type>& operator<<=(const Vector4<OtherT>& rhs)
		{
			*this = (*this << rhs);
			return *this;
		}
		template<typename RhsT>
		constexpr Vector2<value_type>& operator<<=(const RhsT& rhs)
		{
			*this = (*this << rhs);
			return *this;
		}

		template<typename OtherT>
		constexpr Vector2<value_type>& operator>>=(const Vector2<OtherT>& rhs)
		{
			*this = (*this >> rhs);
			return *this;
		}
		template<typename OtherT>
		constexpr Vector2<value_type>& operator>>=(const Vector3<OtherT>& rhs)
		{
			*this = (*this >> rhs);
			return *this;
		}
		template<typename OtherT>
		constexpr Vector2<value_type>& operator>>=(const Vector4<OtherT>& rhs)
		{
			*this = (*this >> rhs);
			return *this;
		}
		template<typename RhsT>
		constexpr Vector2<value_type>& operator>>=(const RhsT& rhs)
		{
			*this = (*this >> rhs);
			return *this;
		}
#pragma endregion

#pragma region BOOLEAN_COMPARISON_OPERATORS
		template<typename OtherT>
		constexpr bool operator==(const Vector2<OtherT>& rhs) const
		{
			return EmuMath::Helpers::VectorComparisonEqual(*this, rhs);
		}
		template<typename OtherT>
		constexpr bool operator==(const Vector3<OtherT>& rhs) const
		{
			return EmuMath::Helpers::VectorComparisonEqual(*this, rhs);
		}
		template<typename OtherT>
		constexpr bool operator==(const Vector4<OtherT>& rhs) const
		{
			return EmuMath::Helpers::VectorComparisonEqual(*this, rhs);
		}

		template<typename OtherT>
		constexpr bool operator!=(const Vector2<OtherT>& rhs) const
		{
			return EmuMath::Helpers::VectorComparisonNotEqual(*this, rhs);
		}
		template<typename OtherT>
		constexpr bool operator!=(const Vector3<OtherT>& rhs) const
		{
			return EmuMath::Helpers::VectorComparisonNotEqual(*this, rhs);
		}
		template<typename OtherT>
		constexpr bool operator!=(const Vector4<OtherT>& rhs) const
		{
			return EmuMath::Helpers::VectorComparisonNotEqual(*this, rhs);
		}

		template<typename RhsT>
		constexpr bool operator>(const RhsT& rhs) const
		{
			return EmuMath::Helpers::VectorComparisonGreater(*this, rhs);
		}
		template<typename RhsT>
		constexpr bool operator>=(const RhsT& rhs) const
		{
			return EmuMath::Helpers::VectorComparisonGreaterEqual(*this, rhs);
		}

		template<typename RhsT>
		constexpr bool operator<(const RhsT& rhs) const
		{
			return EmuMath::Helpers::VectorComparisonLess(*this, rhs);
		}
		template<typename RhsT>
		constexpr bool operator<=(const RhsT& rhs) const
		{
			return EmuMath::Helpers::VectorComparisonLessEqual(*this, rhs);
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
		template<typename OtherT>
		constexpr Vector2<value_type>& operator=(const Vector4<OtherT>& rhs)
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
		template<std::size_t OutSize_ = size(), typename OutT = nonref_value_type, typename RhsT = nonref_value_type>
		constexpr EmuMath::TMPHelpers::emu_vector_from_size_t<OutSize_, OutT> Plus(const Vector2<RhsT>& rhs) const
		{
			return EmuMath::Helpers::VectorAddition<EmuMath::TMPHelpers::emu_vector_from_size_t<OutSize_, OutT>>(*this, rhs);
		}
		template<std::size_t OutSize_ = size(), typename OutT = nonref_value_type, typename RhsT = nonref_value_type>
		constexpr EmuMath::TMPHelpers::emu_vector_from_size_t<OutSize_, OutT> Plus(const Vector3<RhsT>& rhs) const
		{
			return EmuMath::Helpers::VectorAddition<EmuMath::TMPHelpers::emu_vector_from_size_t<OutSize_, OutT>>(*this, rhs);
		}
		template<std::size_t OutSize_ = size(), typename OutT = nonref_value_type, typename RhsT = nonref_value_type>
		constexpr EmuMath::TMPHelpers::emu_vector_from_size_t<OutSize_, OutT> Plus(const Vector4<RhsT>& rhs) const
		{
			return EmuMath::Helpers::VectorAddition<EmuMath::TMPHelpers::emu_vector_from_size_t<OutSize_, OutT>>(*this, rhs);
		}

		template<std::size_t OutSize_ = size(), typename OutT = nonref_value_type, typename RhsT = nonref_value_type>
		constexpr EmuMath::TMPHelpers::emu_vector_from_size_t<OutSize_, OutT> Minus(const Vector2<RhsT>& rhs) const
		{
			return EmuMath::Helpers::VectorSubtraction<EmuMath::TMPHelpers::emu_vector_from_size_t<OutSize_, OutT>>(*this, rhs);
		}
		template<std::size_t OutSize_ = size(), typename OutT = nonref_value_type, typename RhsT = nonref_value_type>
		constexpr EmuMath::TMPHelpers::emu_vector_from_size_t<OutSize_, OutT> Minus(const Vector3<RhsT>& rhs) const
		{
			return EmuMath::Helpers::VectorSubtraction<EmuMath::TMPHelpers::emu_vector_from_size_t<OutSize_, OutT>>(*this, rhs);
		}
		template<std::size_t OutSize_ = size(), typename OutT = nonref_value_type, typename RhsT = nonref_value_type>
		constexpr EmuMath::TMPHelpers::emu_vector_from_size_t<OutSize_, OutT> Minus(const Vector4<RhsT>& rhs) const
		{
			return EmuMath::Helpers::VectorSubtraction<EmuMath::TMPHelpers::emu_vector_from_size_t<OutSize_, OutT>>(*this, rhs);
		}

		template<std::size_t OutSize_ = size(), typename OutT = nonref_value_type, typename RhsT = nonref_value_type>
		constexpr EmuMath::TMPHelpers::emu_vector_from_size_t<OutSize_, OutT> Mult(const RhsT& rhs) const
		{
			return EmuMath::Helpers::VectorMultiplication<EmuMath::TMPHelpers::emu_vector_from_size_t<OutSize_, OutT>>(*this, rhs);
		}

		template<std::size_t OutSize_ = size(), typename OutT = nonref_value_type, typename RhsT = nonref_value_type>
		constexpr EmuMath::TMPHelpers::emu_vector_from_size_t<OutSize_, OutT> Div(const RhsT& rhs) const
		{
			return EmuMath::Helpers::VectorDivision<EmuMath::TMPHelpers::emu_vector_from_size_t<OutSize_, OutT>>(*this, rhs);
		}

		template<std::size_t OutSize_ = size(), typename OutT = nonref_value_type, typename RhsT = nonref_value_type>
		constexpr EmuMath::TMPHelpers::emu_vector_from_size_t<OutSize_, OutT> Mod(const RhsT& rhs) const
		{
			return EmuMath::Helpers::VectorMod<EmuMath::TMPHelpers::emu_vector_from_size_t<OutSize_, OutT>>(*this, rhs);
		}
#pragma endregion

#pragma region BITWISE_TEMPLATES
		/// <summary>
		/// <para>
		///		Returns a Vector of customisable size containing customisable types representing the result of a
		///		bitwise AND with each of this Vector's elements and the passed scalar value.
		/// </para>
		/// <para> The default output Vector size is the same as this Vector, and the contained type is the nonref_value_type of this Vector. </para>
		/// </summary>
		/// <typeparam name="OutT">Type contained in the output Vector.</typeparam>
		/// <typeparam name="RhsT">Type of the passed scalar.</typeparam>
		/// <param name="rhs">Scalar to perform the AND operation with each elements of this Vector.</param>
		/// <returns>
		///		Vector of the provided size (defaulting to this Vector's size) containing the results of a bitwise AND with the passed scalar on each value, 
		///		contained as the provided OutT (defaulting to this Vector's nonref_value_type).
		/// </returns>
		template<std::size_t OutSize_ = size(), typename OutT = nonref_value_type, typename RhsT = nonref_value_type>
		constexpr EmuMath::TMPHelpers::emu_vector_from_size_t<OutSize_, OutT> And(const RhsT& rhs) const
		{
			using OutVector = EmuMath::TMPHelpers::emu_vector_from_size_t<OutSize_, OutT>;
			return EmuMath::Helpers::VectorBitwiseAnd<OutVector>(*this, rhs);
		}

		/// <summary>
		/// <para>
		///		Returns a Vector of customisable size containing customisable types representing the result of a
		///		bitwise OR with each of this Vector's elements and the passed scalar value.
		/// </para>
		/// <para> The default output Vector size is the same as this Vector, and the contained type is the nonref_value_type of this Vector. </para>
		/// </summary>
		/// <typeparam name="OutT">Type contained in the output Vector.</typeparam>
		/// <typeparam name="RhsT">Type of the passed scalar.</typeparam>
		/// <param name="rhs">Scalar to perform the OR operation with each elements of this Vector.</param>
		/// <returns>
		///		Vector of the provided size (defaulting to this Vector's size) containing the results of a bitwise OR with the passed scalar on each value, 
		///		contained as the provided OutT (defaulting to this Vector's nonref_value_type).
		/// </returns>
		template<std::size_t OutSize_ = size(), typename OutT = nonref_value_type, typename RhsT = nonref_value_type>
		constexpr EmuMath::TMPHelpers::emu_vector_from_size_t<OutSize_, OutT> Or(const RhsT& rhs) const
		{
			using OutVector = EmuMath::TMPHelpers::emu_vector_from_size_t<OutSize_, OutT>;
			return EmuMath::Helpers::VectorBitwiseOr<OutVector>(*this, rhs);
		}

		/// <summary>
		/// <para>
		///		Returns a Vector of customisable size containing customisable types representing the result of a
		///		bitwise XOR with each of this Vector's elements and the passed scalar value.
		/// </para>
		/// <para> The default output Vector size is the same as this Vector, and the contained type is the nonref_value_type of this Vector. </para>
		/// </summary>
		/// <typeparam name="OutT">Type contained in the output Vector.</typeparam>
		/// <typeparam name="RhsT">Type of the passed scalar.</typeparam>
		/// <param name="rhs">Scalar to perform the XOR operation with each elements of this Vector.</param>
		/// <returns>
		///		Vector of the provided size (defaulting to this Vector's size) containing the results of a bitwise XOR with the passed scalar on each value, 
		///		contained as the provided OutT (defaulting to this Vector's nonref_value_type).
		/// </returns>
		template<std::size_t OutSize_ = size(), typename OutT = nonref_value_type, typename RhsT = nonref_value_type>
		constexpr EmuMath::TMPHelpers::emu_vector_from_size_t<OutSize_, OutT> Xor(const RhsT& rhs) const
		{
			using OutVector = EmuMath::TMPHelpers::emu_vector_from_size_t<OutSize_, OutT>;
			return EmuMath::Helpers::VectorBitwiseXor<OutVector>(*this, rhs);
		}

		/// <summary>
		/// <para>
		///		Returns a Vector of customisable size containing customisable types representing the result of a
		///		bitwise left shift with each of this Vector's elements and the passed scalar value.
		/// </para>
		/// <para> The default output Vector size is the same as this Vector, and the contained type is the nonref_value_type of this Vector. </para>
		/// </summary>
		/// <typeparam name="OutT">Type contained in the output Vector.</typeparam>
		/// <typeparam name="RhsT">Type of the passed scalar.</typeparam>
		/// <param name="rhs">Scalar to perform the left shift operation with each elements of this Vector.</param>
		/// <returns>
		///		Vector of the provided size (defaulting to this Vector's size) containing the results of a bitwise left shift with the passed scalar on each value, 
		///		contained as the provided OutT (defaulting to this Vector's nonref_value_type).
		/// </returns>
		template<std::size_t OutSize_ = size(), typename OutT = nonref_value_type, typename RhsT = nonref_value_type>
		constexpr EmuMath::TMPHelpers::emu_vector_from_size_t<OutSize_, OutT> LeftShiftPerElement(const RhsT& numShifts) const
		{
			using OutVector = EmuMath::TMPHelpers::emu_vector_from_size_t<OutSize_, OutT>;
			return EmuMath::Helpers::VectorLeftShiftPerElement<OutVector>(*this, numShifts);
		}

		/// <summary>
		/// <para>
		///		Returns a Vector of customisable size containing customisable types representing the result of a
		///		bitwise right shift with each of this Vector's elements and the passed scalar value.
		/// </para>
		/// <para> The default output Vector size is the same as this Vector, and the contained type is the nonref_value_type of this Vector. </para>
		/// </summary>
		/// <typeparam name="OutT">Type contained in the output Vector.</typeparam>
		/// <typeparam name="RhsT">Type of the passed scalar.</typeparam>
		/// <param name="rhs">Scalar to perform the right shift operation with each elements of this Vector.</param>
		/// <returns>
		///		Vector of the provided size (defaulting to this Vector's size) containing the results of a bitwise right shift with the passed scalar on each value, 
		///		contained as the provided OutT (defaulting to this Vector's nonref_value_type).
		/// </returns>
		template<std::size_t OutSize_ = size(), typename OutT = nonref_value_type, typename RhsT = nonref_value_type>
		constexpr EmuMath::TMPHelpers::emu_vector_from_size_t<OutSize_, OutT> RightShiftPerElement(const RhsT& numShifts) const
		{
			using OutVector = EmuMath::TMPHelpers::emu_vector_from_size_t<OutSize_, OutT>;
			return EmuMath::Helpers::VectorRightShiftPerElement<OutVector>(*this, numShifts);
		}

		/// <summary>
		/// <para> Returns a copy of this Vector with the bits of its elements shifted left the provided number of times. </para>
		/// <para> Bits are shifted as one contiguous spread of memory; bits from one element may be shifted into the elements to the left of their origin. </para>
		/// </summary>
		/// <param name="numShifts">Number of times to shift this Vector's bits to the left.</param>
		/// <returns>Copy of this Vector with its elements' bits shifted to the left the provided number of times.</returns>
		constexpr copy_vector LeftShiftVectorwise(const std::size_t numShifts) const
		{
			return EmuMath::Helpers::VectorLeftShiftVectorwise(*this, numShifts);
		}

		/// <summary>
		/// <para> Returns a copy of this Vector with the bits of its elements shifted right the provided number of times. </para>
		/// <para> Bits are shifted as one contiguous spread of memory; bits from one element may be shifted into the elements to the right of their origin. </para>
		/// </summary>
		/// <param name="numShifts">Number of times to shift this Vector's bits to the left.</param>
		/// <returns>Copy of this Vector with its elements' bits shifted to the left the provided number of times.</returns>
		constexpr copy_vector RightShiftVectorwise(const std::size_t numShifts) const
		{
			return EmuMath::Helpers::VectorRightShiftVectorwise(*this, numShifts);
		}

		template<std::size_t OutSize_ = size(), typename OutContainedT = nonref_value_type>
		constexpr EmuMath::TMPHelpers::emu_vector_from_size_t<OutSize_, OutContainedT> Not() const
		{
			return EmuMath::Helpers::VectorBitwiseNot<OutSize_, OutContainedT>(*this);
		}
#pragma endregion

#pragma region BOOLEAN_PER_ELEMENT_COMPARISON_FUNCTIONS

#pragma endregion

#pragma region SHUFFLES
		/// <summary> Returns a Vector4 with elements X, Y, Z and W copying the elements at the respective provided indices within this Vector. </summary>
		/// <returns>This vector shuffled as a Vector4.</returns>
		template<std::size_t X_, std::size_t Y_, std::size_t Z_, std::size_t W_, typename OutT = nonref_value_type>
		constexpr Vector4<OutT> Shuffle() const
		{
			return Vector4<OutT>(at<X_>(), at<Y_>(), at<Z_>(), at<W_>());
		}
		/// <summary> Returns a Vector3 with elements X, Y and Z copying the elements at the respective provided indices within this Vector. </summary>
		/// <returns>This vector shuffled as a Vector3.</returns>
		template<std::size_t X_, std::size_t Y_, std::size_t Z_, typename OutT = nonref_value_type>
		constexpr Vector3<OutT> Shuffle() const
		{
			return Vector3<OutT>(at<X_>(), at<Y_>(), at<Z_>());
		}
		/// <summary> Returns a Vector2 with elements X and Y copying the elements at the respective provided indices within this Vector. </summary>
		/// <returns>This vector shuffled as a Vector2.</returns>
		template<std::size_t X_, std::size_t Y_, typename OutT = nonref_value_type>
		constexpr Vector2<OutT> Shuffle() const
		{
			return Vector2<OutT>(at<X_>(), at<Y_>());
		}
		/// <summary>
		///	<para> Returns a Vector4 with elements X, Y, Z and W copying the elements at the respective provided indices within this Vector. </para>
		/// <para> If possible, it is recommended to use the templatised version of this function. </para>
		/// </summary>
		/// <returns>This Vector shuffled as a Vector4.</returns>
		template<typename OutT = nonref_value_type>
		Vector4<OutT> Shuffle(const std::size_t x_, const std::size_t y_, const std::size_t z_, const std::size_t w_) const
		{
			return Vector4<OutT>(at(x_), at(y_), at(z_), at(w_));
		}
		/// <summary>
		///	<para> Returns a Vector3 with elements X, Y and Z copying the elements at the respective provided indices within this Vector. </para>
		/// <para> If possible, it is recommended to use the templatised version of this function. </para>
		/// </summary>
		/// <returns>This Vector shuffled as a Vector3.</returns>
		template<typename OutT = nonref_value_type>
		Vector3<OutT> Shuffle(const std::size_t x_, const std::size_t y_, const std::size_t z_) const
		{
			return Vector3<OutT>(at(x_), at(y_), at(z_));
		}
		/// <summary>
		/// <para> Returns a Vector2 with elements X and Y copying the elements at the respective provided indices within this Vector. </para>
		/// <para> If possible, it is recommended to use the templatised version of this function. </para>
		/// </summary>
		/// <returns>This Vector shuffled as a Vector2.</returns>
		template<typename OutT = nonref_value_type>
		Vector2<OutT> Shuffle(const std::size_t x_, const std::size_t y_) const
		{
			return Vector2<OutT>(at(x_), at(y_));
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
		/// <summary> Determines the lowest element within this Vector. </summary>
		/// <returns>Copy of the lowest element within this Vector.</returns>
		template<typename OutT = nonref_value_type>
		constexpr OutT Min() const
		{
			return EmuMath::Helpers::VectorMin<OutT>(*this);
		}
		/// <summary> Determines the highest element within this Vector. </summary>
		/// <returns>Copy of the highest element within this Vector.</returns>
		template<typename OutT = nonref_value_type>
		constexpr OutT Max() const
		{
			return EmuMath::Helpers::VectorMax<OutT>(*this);
		}

		/// <summary>
		/// <para> Returns a copy of this Vector with its elements clamped to the passed minimum. </para>
		/// <para> If the passed min_ is an EmuMath Vector, minimum values will be a per element basis (e.g. x will be clamped to min_.x, y to min_.y, etc). </para>
		/// </summary>
		/// <typeparam name="OutT_">Type contained within the output Vector.</typeparam>
		/// <typeparam name="MinT_">Type for the passed minimum clamp.</typeparam>
		/// <param name="min_">Minimum value for elements to be clamped to, or minimum values for respective elements if an EmuMath Vector.</param>
		/// <returns>
		///		Copy of this Vector with its values clamped to the provided minimum, with custom size (defaults to the size of this Vector) 
		///		and contained types (defaults to this Vector's nonref_value_type).
		/// </returns>
		template<std::size_t OutSize_ = size(), typename OutT_ = nonref_value_type, typename MinT_ = nonref_value_type>
		constexpr typename EmuMath::TMPHelpers::emu_vector_from_size<OutSize_, OutT_>::type ClampMin(const MinT_& min_) const
		{
			return EmuMath::Helpers::VectorClampMin<OutSize_, OutT_>(*this, min_);
		}
		/// <summary>
		/// <para> Returns a copy of this Vector with its elements clamped to the passed maximum. </para>
		/// <para> If the passed max_ is an EmuMath Vector, maximum values will be a per element basis (e.g. x will be clamped to max_.x, y to max_.y, etc). </para>
		/// </summary>
		/// <typeparam name="OutT_">Type contained within the output Vector.</typeparam>
		/// <typeparam name="MinT_">Type for the passed minimum clamp.</typeparam>
		/// <typeparam name="MaxT_">Type for the passed maximum clamp.</typeparam>
		/// <param name="min_">Minimum value for elements to be clamped to, or minimum values for respective elements if an EmuMath Vector.</param>
		/// <param name="max_">Maximum value for elements to be clamped to, or maximum values for respective elements if an EmuMath Vector.</param>
		/// <returns>
		///		Copy of this Vector with its values clamped to the provided maximum, with custom size (defaults to the size of this Vector) 
		///		and contained types (defaults to this Vector's nonref_value_type).
		/// </returns>
		template<std::size_t OutSize_ = size(), typename OutT_ = nonref_value_type, typename MaxT_ = nonref_value_type>
		constexpr typename EmuMath::TMPHelpers::emu_vector_from_size<OutSize_, OutT_>::type ClampMax(const MaxT_& max_) const
		{
			return EmuMath::Helpers::VectorClampMax<OutSize_, OutT_>(*this, max_);
		}
		/// <summary>
		/// <para> Returns a copy of this Vector with its elements clamped to the passed minimum and maximum. </para>
		/// <para>
		///		If the passed min_ or max_ is an EmuMath Vector, respective values will be clamped on a per element basis (e.g. x will be clamped to max_.x, y to max_.y, etc).
		/// </para>
		/// </summary>
		/// <typeparam name="OutT_">Type contained within the output Vector.</typeparam>
		/// <typeparam name="MaxT_">Type for the passed maximum clamp.</typeparam>
		/// <param name="max_">Maximum value for elements to be clamped to, or maximum values for respective elements if an EmuMath Vector.</param>
		/// <returns>
		///		Copy of this Vector with its values clamped to the provided maximum, with custom size (defaults to the size of this Vector) 
		///		and contained types (defaults to this Vector's nonref_value_type).
		/// </returns>
		template<std::size_t OutSize_ = size(), typename OutT_ = nonref_value_type, typename MinT_ = nonref_value_type, typename MaxT_ = nonref_value_type>
		constexpr typename EmuMath::TMPHelpers::emu_vector_from_size<OutSize_, OutT_>::type Clamp(const MinT_& min_, const MaxT_& max_) const
		{
			return EmuMath::Helpers::VectorClamp<OutSize_, OutT_>(*this, min_, max_);
		}

		/// <summary> Calculates the values of this Vector's elements when rounded toward negative infinity. </summary>
		/// <returns>Copy of this Vector with its elements rounded toward negative infinity.</returns>
		template<std::size_t OutSize_ = size(), typename OutT = nonref_value_type>
		Vector2<nonref_value_type> Floor() const
		{
			return EmuMath::Helpers::VectorFloor<OutSize_, OutT>(*this);
		}
		/// <summary> Calculates the values of this Vector's elements when rounded toward positive infinity. </summary>
		/// <returns>Copy of this Vector with its elements rounded toward positive infinity.</returns>
		template<std::size_t OutSize_ = size(), typename OutT = nonref_value_type>
		Vector2<nonref_value_type> Ceil() const
		{
			return EmuMath::Helpers::VectorCeil<OutSize_, OutT>(*this);
		}
		/// <summary> Calculates the values of this Vector's elements when rounded toward 0. </summary>
		/// <returns>Copy of this Vector with its elements rounded toward 0.</returns>
		template<std::size_t OutSize_ = size(), typename OutT = nonref_value_type>
		Vector2<nonref_value_type> Trunc() const
		{
			return EmuMath::Helpers::VectorTrunc<OutSize_, OutT>(*this);
		}

		template<std::size_t OutSize_ = size(), typename OutT = nonref_value_type>
		constexpr Vector2<nonref_value_type> FloorConstexpr() const
		{
			return EmuMath::Helpers::VectorFloorConstexpr<OutSize_, OutT>(*this);
		}
		template<std::size_t OutSize_ = size(), typename OutT = nonref_value_type>
		constexpr Vector2<nonref_value_type> CeilConstexpr() const
		{
			return EmuMath::Helpers::VectorCeilConstexpr<OutSize_, OutT>(*this);
		}
		template<std::size_t OutSize_ = size(), typename OutT = nonref_value_type>
		constexpr Vector2<nonref_value_type> TruncConstexpr() const
		{
			return EmuMath::Helpers::VectorTruncConstexpr<OutSize_, OutT>(*this);
		}

		template<std::size_t OutSize_ = size(), typename OutT_ = default_floating_point, typename B_ = emu_vector_type, typename T_ = default_floating_point>
		constexpr typename EmuMath::TMPHelpers::emu_vector_from_size<OutSize_, OutT_>::type Lerp(const B_& b_, const T_& t_) const
		{
			return EmuMath::Helpers::VectorLerp<OutSize_, OutT_>(*this, b_, t_);
		}
#pragma endregion

#pragma region VECTOR_OPERATIONS
		/// <summary>
		/// <para> Returns the magnitude of this Vector, represented as the passed floating point OutFP_ type (defaults to this Vector's default_floating_point). </para>
		/// <para> It is recommended to only use this for compile time constants, and instead use Magnitude for code that will execute at runtime. </para>
		/// </summary>
		/// <typeparam name="OutFP">Type to return, representing the magnitude of the passed Vector.</typeparam>
		/// <returns>Magnitude of this vector, represented as the passed OutFP_ type.</returns>
		template<typename OutFP_ = default_floating_point>
		constexpr OutFP_ MagnitudeConstexpr() const
		{
			return EmuMath::Helpers::VectorMagnitudeConstexpr<OutFP_>(*this);
		}
		/// <summary>
		/// <para> Returns the magnitude of this Vector, represented as the passed OutT type (defaults to this Vector's default_floating_point). </para>
		/// <para> It is recommended to use this instead of MagnitudeConstexpr for runtime-executed code. </para>
		/// </summary>
		/// <typeparam name="OutT">Type to return, representing the magnitude of the passed Vector.</typeparam>
		/// <returns>Magnitude of this vector, represented as the passed Out_ type (first and only required template parameter).</returns>
		template<typename OutT = default_floating_point>
		OutT Magnitude() const
		{
			return EmuMath::Helpers::VectorMagnitude<OutT>(*this);
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
			return EmuMath::Helpers::VectorSquareMagnitude<OutT>(*this);
		}
		/// <summary>
		/// <para> Returns a normalised Vector from this Vector's components, stored as optionally customisable floating point types. </para>
		/// <para> Note that the output type must be a valid floating point type. </para>
		/// </summary>
		/// <typeparam name="OutT">Type to output as. Must be a floating point type.</typeparam>
		/// <returns>Normalised version of this Vector, with its contained elements stored as the provided OutT (defaults to this Vector's default_floating_point).</returns>
		template<typename OutFP = default_floating_point>
		Vector2<OutFP> Normalise() const
		{
			return EmuMath::Helpers::VectorNormalise<OutFP>(*this);
		}
		template<typename OutFP = default_floating_point>
		constexpr Vector2<OutFP> NormaliseConstexpr() const
		{
			return EmuMath::Helpers::VectorNormaliseConstexpr<OutFP>(*this);
		}
		/// <summary>
		/// <para> Returns the dot product of this Vector and the provided Vector, output as an optionally customisable type. </para>
		/// </summary>
		/// <typeparam name="RhsT">Type contained within the passed Vector.</typeparam>
		/// <typeparam name="OutT">Type to output. Defaults to this Vector's nonref_value_type.</typeparam>
		/// <param name="rhs">Vector to calculate a dot product with.</param>
		/// <returns>Dot product of this Vector and the provided Vector, represented as this Vector's nonref_value_type or an optional provided type.</returns>
		template<typename OutT = default_floating_point, typename RhsT = nonref_value_type>
		constexpr OutT DotProduct(const Vector2<RhsT>& rhs) const
		{
			return EmuMath::Helpers::VectorDotProduct<OutT>(*this, rhs);
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
		constexpr Vector2<OutT> Reverse() const
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
#pragma endregion
	};
}

#endif
