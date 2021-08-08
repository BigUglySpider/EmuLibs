#ifndef EMU_MATH_VECTOR_4_T_H_INC_
#define EMU_MATH_VECTOR_4_T_H_INC_

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
	struct Vector2;
	template<typename T>
	struct Vector3;

	/// <summary> Generic Vector type which contains 4 elements of the provided type, representing the X-, Y-, Z- and W-axes respectively. </summary>
	/// <typeparam name="T">Type to store within the Vector.</typeparam>
	template<typename T>
	struct Vector4
	{
#pragma region ALIASES_AND_STATIC_CONSTANT_EXPRESSIONS
	protected:
		/// <summary> Templatised type containing info for all sizes of vectors containing the passed type T_. </summary>
		/// <typeparam name="T_">Type contained within the vector for which the info is required.</typeparam>
		template<typename T_>
		using info_type_t = EmuMath::_info::VectorInfo<T_>;

	public:
		/// <summary> The overall type of EmuMath Vector that this type is. </summary>
		using emu_vector_type = Vector4<T>;
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
		/// <returns>4</returns>
		static constexpr std::size_t size()
		{
			return 4;
		}
		/// <summary> The reciprocal of the number of elements contained within this vector. Recommended to multiply this instead of dividing by size. </summary>
		/// <typeparam name="OutT_">Type to output the reciprocal as. Must be a floating point value. Defaults to this vector's default_floating_point.</typeparam>
		/// <returns>The result of 1/size, where both values are interpreted as the provided OutT_ type.</returns>
		template<typename OutT_ = default_floating_point>
		static constexpr OutT_ size_reciprocal()
		{
			static_assert(std::is_floating_point_v<OutT_>, "Provided a non-floating-point data type for an EmuMath Vector's size reciprocal. A floating-point must be provided.");
			return OutT_(1) / static_cast<OutT_>(size());
		}

		/// <summary> The type of Vector created when getting a copy of this Vector's data (used to get copy values instead of references). </summary>
		using copy_vector = Vector4<nonref_value_type_without_qualifiers>;
#pragma endregion

#pragma region CONSTRUCTORS
		constexpr Vector4() :
			x(),
			y(),
			z(),
			w()
		{
		}
		constexpr Vector4(const value_type& x_, const value_type& y_, const value_type& z_, const value_type& w_) :
			x(x_),
			y(y_),
			z(z_),
			w(w_)
		{
		}
		template<typename X_>
		constexpr Vector4(const X_& x_, const value_type& y_, const value_type& z_, const value_type& w_) :
			x(static_cast<value_type>(x_)),
			y(y_),
			z(z_),
			w(w_)
		{
		}
		template<typename Y_>
		constexpr Vector4(const value_type& x_, const Y_& y_, const value_type& z_, const value_type& w_) :
			x(x_),
			y(static_cast<value_type>(y_)),
			z(z_),
			w(w_)
		{
		}
		template<typename Z_>
		constexpr Vector4(const value_type& x_, const value_type& y_, const Z_& z_, const value_type& w_) :
			x(x_),
			y(y_),
			z(static_cast<value_type>(z_)),
			w(w_)
		{
		}
		template<typename W_>
		constexpr Vector4(const value_type& x_, const value_type& y_, const value_type& z_, const W_& w_) :
			x(x_),
			y(y_),
			z(z_),
			w(static_cast<value_type>(w_))
		{
		}
		template<typename X_, typename Y_>
		constexpr Vector4(const X_& x_, const Y_& y_, const value_type& z_, const value_type& w_) :
			x(static_cast<value_type>(x_)),
			y(static_cast<value_type>(y_)),
			z(z_),
			w(w_)
		{
		}
		template<typename X_, typename Z_>
		constexpr Vector4(const X_& x_, const value_type& y_, const Z_& z_, const value_type& w_) :
			x(static_cast<value_type>(x_)),
			y(y_),
			z(static_cast<value_type>(z_)),
			w(w_)
		{
		}
		template<typename X_, typename W_>
		constexpr Vector4(const X_& x_, const value_type& y_, const value_type& z_, const W_& w_) :
			x(static_cast<value_type>(x_)),
			y(y_),
			z(z_),
			w(static_cast<value_type>(w_))
		{
		}
		template<typename Y_, typename Z_>
		constexpr Vector4(const value_type& x_, const Y_& y_, const Z_& z_, const value_type& w_) :
			x(x_),
			y(static_cast<value_type>(y_)),
			z(static_cast<value_type>(z_)),
			w(w_)
		{
		}
		template<typename Y_, typename W_>
		constexpr Vector4(const value_type& x_, const Y_& y_, const value_type& z_, const W_& w_) :
			x(x_),
			y(static_cast<value_type>(y_)),
			z(z_),
			w(static_cast<value_type>(w_))
		{
		}
		template<typename Z_, typename W_>
		constexpr Vector4(const value_type& x_, const value_type& y_, const Z_& z_, const W_& w_) :
			x(x_),
			y(y_),
			z(static_cast<value_type>(z_)),
			w(static_cast<value_type>(w_))
		{
		}
		template<typename X_, typename Y_, typename Z_>
		constexpr Vector4(const X_& x_, const Y_& y_, const Z_& z_, const value_type& w_) :
			x(static_cast<value_type>(x_)),
			y(static_cast<value_type>(y_)),
			z(static_cast<value_type>(z_)),
			w(w_)
		{
		}
		template<typename X_, typename Y_, typename W_>
		constexpr Vector4(const X_& x_, const Y_& y_, const value_type& z_, const W_& w_) :
			x(static_cast<value_type>(x_)),
			y(static_cast<value_type>(y_)),
			z(z_),
			w(static_cast<value_type>(w_))
		{
		}
		template<typename Y_, typename Z_, typename W_>
		constexpr Vector4(const value_type& x_, const Y_& y_, const Z_& z_, const W_& w_) :
			x(x_),
			y(static_cast<value_type>(y_)),
			z(static_cast<value_type>(z_)),
			w(static_cast<value_type>(w_))
		{
		}
		template<typename X_, typename Y_, typename Z_, typename W_>
		constexpr Vector4(const X_& x_, const Y_& y_, const Z_& z_, const W_& w_) :
			x(static_cast<value_type>(x_)),
			y(static_cast<value_type>(y_)),
			z(static_cast<value_type>(z_)),
			w(static_cast<value_type>(w_))
		{
		}
		template<typename OtherT>
		constexpr Vector4(const Vector4<OtherT>& toCopy) :
			Vector4(toCopy.x, toCopy.y, toCopy.z, toCopy.w)
		{
		}
		template<typename OtherT>
		constexpr Vector4(Vector4<OtherT>& toCopy) :
			Vector4(toCopy.x, toCopy.y, toCopy.z, toCopy.w)
		{
		}
		template<typename OtherT>
		explicit constexpr Vector4(const Vector3<OtherT>& toCopy) :
			Vector4(toCopy.x, toCopy.y, toCopy.z, value_type())
		{
		}
		template<typename OtherT, typename W_>
		explicit constexpr Vector4(const Vector3<OtherT>& toCopy, const W_& w_) :
			Vector4(toCopy.x, toCopy.y, toCopy.z, w_)
		{
		}
		template<typename OtherT, typename W_>
		explicit constexpr Vector4(Vector3<OtherT>& toCopy, W_& w_) :
			Vector4(toCopy.x, toCopy.y, toCopy.z, w_)
		{
		}
		template<typename OtherT>
		explicit constexpr Vector4(const Vector2<OtherT>& toCopy) :
			Vector4(toCopy.x, toCopy.y, value_type(), value_type())
		{
		}
		template<typename OtherT, typename Z_, typename W_>
		explicit constexpr Vector4(const Vector2<OtherT>& toCopy, const Z_& z_, const W_& w_) :
			Vector4(toCopy.x, toCopy.y, z_, w_)
		{
		}
		template<typename OtherT, typename Z_, typename W_>
		explicit constexpr Vector4(Vector2<OtherT>& toCopy, Z_& z_, W_& w_) :
			Vector4(toCopy.x, toCopy.y, z_, w_)
		{
		}
#pragma endregion

#pragma region RANDOM_ACCESS
		/// <summary>
		///	<para> Access the element of this vector at the provided index, where x is index 0 and w is index 3. </para>
		/// <para> If possible, it is recommended to use the templatised at function instead. </para>
		/// </summary>
		/// <param name="index">Index of the element to access.</param>
		/// <returns>Reference to the element at the provided index.</returns>
		ref_value_type operator[](const std::size_t index)
		{
			return at(index);
		}
		/// <summary>
		///	<para> Access the element of this vector at the provided index, where x is index 0 and w is index 3. </para>
		/// <para> If possible, it is recommended to use the templatised at function instead. </para>
		/// </summary>
		/// <param name="index">Index of the element to access.</param>
		/// <returns>Constant reference to the element at the provided index.</returns>
		const_ref_value_type operator[](const std::size_t index) const
		{
			return at(index);
		}
		/// <summary>
		///	<para> Access the element of this vector at the provided index, where x is index 0 and w is index 3. </para>
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
				case 2:
					return z;
				case 3:
					return w;
				default:
					throw std::logic_error("Attempted to access an EmuMath::Vector4 element by an index which does not exist.");
			}
		}
		/// <summary>
		///	<para> Access the element of this vector at the provided index, where x is index 0 and w is index 3. </para>
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
				case 2:
					return z;
				case 3:
					return w;
				default:
					throw std::logic_error("Attempted to access an EmuMath::Vector4 element by an index which does not exist.");
			}
		}
		/// <summary> Access the element of this vector at the provided index, where x is index 0 and w is index 3. </summary>
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
			else if constexpr (Index_ == 2)
			{
				return z;
			}
			else if constexpr (Index_ == 3)
			{
				return w;
			}
			else
			{
				static_assert(false, "Attempted to access an EmuMath::Vector4 element by an index which does not exist.");
			}
		}
		/// <summary> Access the element of this vector at the provided index, where x is index 0 and w is index 3. </summary>
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
			else if constexpr (Index_ == 2)
			{
				return z;
			}
			else if constexpr (Index_ == 3)
			{
				return w;
			}
			else
			{
				static_assert(false, "Attempted to access an EmuMath::Vector4 element by an index which does not exist.");
			}
		}
#pragma endregion

#pragma region ARITHMETIC_CONST_OPERATORS
		template<typename RhsT>
		constexpr copy_vector operator+(const Vector2<RhsT>& rhs) const
		{
			return EmuMath::Helpers::VectorAddition<copy_vector>(*this, rhs);
		}
		template<typename RhsT>
		constexpr copy_vector operator+(const Vector3<RhsT>& rhs) const
		{
			return EmuMath::Helpers::VectorAddition<copy_vector>(*this, rhs);
		}
		template<typename RhsT>
		constexpr copy_vector operator+(const Vector4<RhsT>& rhs) const
		{
			return EmuMath::Helpers::VectorAddition<copy_vector>(*this, rhs);
		}

		template<typename RhsT>
		constexpr copy_vector operator-(const Vector2<RhsT>& rhs) const
		{
			return EmuMath::Helpers::VectorSubtraction<copy_vector>(*this, rhs);
		}
		template<typename RhsT>
		constexpr copy_vector operator-(const Vector3<RhsT>& rhs) const
		{
			return EmuMath::Helpers::VectorSubtraction<copy_vector>(*this, rhs);
		}
		template<typename RhsT>
		constexpr copy_vector operator-(const Vector4<RhsT>& rhs) const
		{
			return EmuMath::Helpers::VectorSubtraction<copy_vector>(*this, rhs);
		}
		constexpr copy_vector operator-() const
		{
			return this->Reverse();
		}

		template<typename RhsT>
		constexpr copy_vector operator*(const RhsT& rhs) const
		{
			return EmuMath::Helpers::VectorMultiplication<copy_vector>(*this, rhs);
		}

		template<typename RhsT>
		constexpr copy_vector operator/(const RhsT& rhs) const
		{
			return EmuMath::Helpers::VectorDivision<copy_vector>(*this, rhs);
		}

		template<typename RhsT>
		constexpr copy_vector operator%(const RhsT& rhs) const
		{
			return EmuMath::Helpers::VectorMod<copy_vector>(*this, rhs);
		}
#pragma endregion

#pragma region BITWISE_CONST_OPERATORS
		template<typename OtherT>
		constexpr copy_vector operator&(const Vector2<OtherT>& rhs) const
		{
			return this->And<size(), typename copy_vector::value_type, OtherT>(rhs);
		}
		template<typename OtherT>
		constexpr copy_vector operator&(const Vector3<OtherT>& rhs) const
		{
			return this->And<size(), typename copy_vector::value_type, OtherT>(rhs);
		}
		template<typename OtherT>
		constexpr copy_vector operator&(const Vector4<OtherT>& rhs) const
		{
			return this->And<size(), typename copy_vector::value_type, OtherT>(rhs);
		}
		template<typename RhsT>
		constexpr copy_vector operator&(const RhsT& rhs) const
		{
			return this->And<size(), typename copy_vector::value_type, RhsT>(rhs);
		}
		template<typename OtherT>
		constexpr copy_vector operator|(const Vector2<OtherT>& rhs) const
		{
			return this->Or<size(), typename copy_vector::value_type, OtherT>(rhs);
		}
		template<typename OtherT>
		constexpr copy_vector operator|(const Vector3<OtherT>& rhs) const
		{
			return this->Or<size(), typename copy_vector::value_type, OtherT>(rhs);
		}
		template<typename OtherT>
		constexpr copy_vector operator|(const Vector4<OtherT>& rhs) const
		{
			return this->Or<size(), typename copy_vector::value_type, OtherT>(rhs);
		}
		template<typename RhsT>
		constexpr copy_vector operator|(const RhsT& rhs) const
		{
			return this->Or<size(), typename copy_vector::value_type, RhsT>(rhs);
		}
		template<typename OtherT>
		constexpr copy_vector operator^(const Vector2<OtherT>& rhs) const
		{
			return this->Xor<size(), typename copy_vector::value_type, OtherT>(rhs);
		}
		template<typename OtherT>
		constexpr copy_vector operator^(const Vector3<OtherT>& rhs) const
		{
			return this->Xor<size(), typename copy_vector::value_type, OtherT>(rhs);
		}
		template<typename OtherT>
		constexpr copy_vector operator^(const Vector4<OtherT>& rhs) const
		{
			return this->Xor<size(), typename copy_vector::value_type, OtherT>(rhs);
		}
		template<typename RhsT>
		constexpr copy_vector operator^(const RhsT& rhs) const
		{
			return this->Xor<size(), typename copy_vector::value_type, RhsT>(rhs);
		}
		template<typename OtherT>
		constexpr copy_vector operator<<(const Vector2<OtherT>& rhs) const
		{
			return this->LeftShiftPerElement<size(), typename copy_vector::value_type, OtherT>(rhs);
		}
		template<typename OtherT>
		constexpr copy_vector operator<<(const Vector3<OtherT>& rhs) const
		{
			return this->LeftShiftPerElement<size(), typename copy_vector::value_type, OtherT>(rhs);
		}
		template<typename OtherT>
		constexpr copy_vector operator<<(const Vector4<OtherT>& rhs) const
		{
			return this->LeftShiftPerElement<size(), typename copy_vector::value_type, OtherT>(rhs);
		}
		template<typename RhsT>
		constexpr copy_vector operator<<(const RhsT& rhs) const
		{
			return this->LeftShiftPerElement<size(), typename copy_vector::value_type, RhsT>(rhs);
		}
		template<typename OtherT>
		constexpr copy_vector operator>>(const Vector2<OtherT>& rhs) const
		{
			return this->RightShiftPerElement<size(), typename copy_vector::value_type, OtherT>(rhs);
		}
		template<typename OtherT>
		constexpr copy_vector operator>>(const Vector3<OtherT>& rhs) const
		{
			return this->RightShiftPerElement<size(), typename copy_vector::value_type, OtherT>(rhs);
		}
		template<typename OtherT>
		constexpr copy_vector operator>>(const Vector4<OtherT>& rhs) const
		{
			return this->RightShiftPerElement<size(), typename copy_vector::value_type, OtherT>(rhs);
		}
		template<typename RhsT>
		constexpr copy_vector operator>>(const RhsT& rhs) const
		{
			return this->RightShiftPerElement<size(), typename copy_vector::value_type, RhsT>(rhs);
		}
		constexpr copy_vector operator~() const
		{
			return this->Not();
		}
#pragma endregion

#pragma region ARITHMETIC_NONCONST_OPERATORS
		template<typename OtherT>
		emu_vector_type& operator+=(const Vector2<OtherT>& rhs)
		{
			*this = (*this + rhs);
			return *this;
		}
		template<typename OtherT>
		emu_vector_type& operator+=(const Vector3<OtherT>& rhs)
		{
			*this = (*this + rhs);
			return *this;
		}
		template<typename OtherT>
		emu_vector_type& operator+=(const Vector4<OtherT>& rhs)
		{
			*this = (*this + rhs);
			return *this;
		}

		template<typename OtherT>
		emu_vector_type& operator-=(const Vector2<OtherT>& rhs)
		{
			*this = (*this - rhs);
			return *this;
		}
		template<typename OtherT>
		emu_vector_type& operator-=(const Vector3<OtherT>& rhs)
		{
			*this = (*this - rhs);
			return *this;
		}
		template<typename OtherT>
		emu_vector_type& operator-=(const Vector4<OtherT>& rhs)
		{
			*this = (*this - rhs);
			return *this;
		}

		template<typename OtherT>
		emu_vector_type& operator*=(const Vector2<OtherT>& rhs)
		{
			*this = (*this * rhs);
			return *this;
		}
		template<typename OtherT>
		emu_vector_type& operator*=(const Vector3<OtherT>& rhs)
		{
			*this = (*this * rhs);
			return *this;
		}
		template<typename OtherT>
		emu_vector_type& operator*=(const Vector4<OtherT>& rhs)
		{
			*this = (*this * rhs);
			return *this;
		}
		template<typename RhsT>
		emu_vector_type& operator*=(const RhsT& rhs)
		{
			*this = (*this * rhs);
			return *this;
		}

		template<typename OtherT>
		emu_vector_type& operator/=(const Vector2<OtherT>& rhs)
		{
			*this = (*this / rhs);
			return *this;
		}
		template<typename OtherT>
		emu_vector_type& operator/=(const Vector3<OtherT>& rhs)
		{
			*this = (*this / rhs);
			return *this;
		}
		template<typename OtherT>
		emu_vector_type& operator/=(const Vector4<OtherT>& rhs)
		{
			*this = (*this / rhs);
			return *this;
		}
		template<typename RhsT>
		emu_vector_type& operator/=(const RhsT& rhs)
		{
			*this = (*this / rhs);
			return *this;
		}

		template<typename OtherT>
		emu_vector_type& operator%=(const Vector2<OtherT>& rhs)
		{
			*this = (*this % rhs);
			return *this;
		}
		template<typename OtherT>
		emu_vector_type& operator%=(const Vector3<OtherT>& rhs)
		{
			*this = (*this % rhs);
			return *this;
		}
		template<typename OtherT>
		emu_vector_type& operator%=(const Vector4<OtherT>& rhs)
		{
			*this = (*this % rhs);
			return *this;
		}
		template<typename RhsT>
		emu_vector_type& operator%=(const RhsT& rhs)
		{
			*this = (*this % rhs);
			return *this;
		}
#pragma endregion

#pragma region BITWISE_NONCONST_OPERATORS
		template<typename OtherT>
		constexpr emu_vector_type& operator&=(const Vector2<OtherT>& rhs)
		{
			*this = (*this & rhs);
			return *this;
		}
		template<typename OtherT>
		constexpr emu_vector_type& operator&=(const Vector3<OtherT>& rhs)
		{
			*this = (*this & rhs);
			return *this;
		}
		template<typename OtherT>
		constexpr emu_vector_type& operator&=(const Vector4<OtherT>& rhs)
		{
			*this = (*this & rhs);
			return *this;
		}
		template<typename RhsT>
		constexpr emu_vector_type& operator&=(const RhsT& rhs)
		{
			*this = (*this & rhs);
			return *this;
		}

		template<typename OtherT>
		constexpr emu_vector_type& operator|=(const Vector2<OtherT>& rhs)
		{
			*this = (*this | rhs);
			return *this;
		}
		template<typename OtherT>
		constexpr emu_vector_type& operator|=(const Vector3<OtherT>& rhs)
		{
			*this = (*this | rhs);
			return *this;
		}
		template<typename OtherT>
		constexpr emu_vector_type& operator|=(const Vector4<OtherT>& rhs)
		{
			*this = (*this | rhs);
			return *this;
		}
		template<typename RhsT>
		constexpr emu_vector_type& operator|=(const RhsT& rhs)
		{
			*this = (*this | rhs);
			return *this;
		}

		template<typename OtherT>
		constexpr emu_vector_type& operator^=(const Vector2<OtherT>& rhs)
		{
			*this = (*this ^ rhs);
			return *this;
		}
		template<typename OtherT>
		constexpr emu_vector_type& operator^=(const Vector3<OtherT>& rhs)
		{
			*this = (*this ^ rhs);
			return *this;
		}
		template<typename OtherT>
		constexpr emu_vector_type& operator^=(const Vector4<OtherT>& rhs)
		{
			*this = (*this ^ rhs);
			return *this;
		}
		template<typename RhsT>
		constexpr emu_vector_type& operator^=(const RhsT& rhs)
		{
			*this = (*this ^ rhs);
			return *this;
		}

		template<typename OtherT>
		constexpr emu_vector_type& operator<<=(const Vector2<OtherT>& rhs)
		{
			*this = (*this << rhs);
			return *this;
		}
		template<typename OtherT>
		constexpr emu_vector_type& operator<<=(const Vector3<OtherT>& rhs)
		{
			*this = (*this << rhs);
			return *this;
		}
		template<typename OtherT>
		constexpr emu_vector_type& operator<<=(const Vector4<OtherT>& rhs)
		{
			*this = (*this << rhs);
			return *this;
		}
		template<typename RhsT>
		constexpr emu_vector_type& operator<<=(const RhsT& rhs)
		{
			*this = (*this << rhs);
			return *this;
		}

		template<typename OtherT>
		constexpr emu_vector_type& operator>>=(const Vector2<OtherT>& rhs)
		{
			*this = (*this >> rhs);
			return *this;
		}
		template<typename OtherT>
		constexpr emu_vector_type& operator>>=(const Vector3<OtherT>& rhs)
		{
			*this = (*this >> rhs);
			return *this;
		}
		template<typename OtherT>
		constexpr emu_vector_type& operator>>=(const Vector4<OtherT>& rhs)
		{
			*this = (*this >> rhs);
			return *this;
		}
		template<typename RhsT>
		constexpr emu_vector_type& operator>>=(const RhsT& rhs)
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
		constexpr emu_vector_type& operator=(const Vector2<OtherT>& rhs)
		{
			return EmuMath::Helpers::VectorSet(*this, rhs);
		}
		template<typename OtherT>
		constexpr emu_vector_type& operator=(const Vector3<OtherT>& rhs)
		{
			return EmuMath::Helpers::VectorSet(*this, rhs);
		}
		template<typename OtherT>
		constexpr emu_vector_type& operator=(const Vector4<OtherT>& rhs)
		{
			return EmuMath::Helpers::VectorSet(*this, rhs);
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

#pragma region COMPARISON_TEMPLATES
		template<std::size_t OutSize_ = size(), class Rhs_ = emu_vector_type>
		constexpr typename EmuMath::TMPHelpers::emu_vector_from_size_t<OutSize_, bool> ComparePerElement_Equal(const Rhs_& rhs_) const
		{
			return EmuMath::Helpers::VectorComparisonPerElement_Equal<OutSize_>(*this, rhs_);
		}
		template<std::size_t OutSize_ = size(), class Rhs_ = emu_vector_type>
		constexpr typename EmuMath::TMPHelpers::emu_vector_from_size_t<OutSize_, bool> ComparePerElement_NotEqual(const Rhs_& rhs_) const
		{
			return EmuMath::Helpers::VectorComparisonPerElement_NotEqual<OutSize_>(*this, rhs_);
		}
		template<std::size_t OutSize_ = size(), class Rhs_ = emu_vector_type>
		constexpr typename EmuMath::TMPHelpers::emu_vector_from_size_t<OutSize_, bool> ComparePerElement_Less(const Rhs_& rhs_) const
		{
			return EmuMath::Helpers::VectorComparisonPerElement_Less<OutSize_>(*this, rhs_);
		}
		template<std::size_t OutSize_ = size(), class Rhs_ = emu_vector_type>
		constexpr typename EmuMath::TMPHelpers::emu_vector_from_size_t<OutSize_, bool> ComparePerElement_LessEqual(const Rhs_& rhs_) const
		{
			return EmuMath::Helpers::VectorComparisonPerElement_LessEqual<OutSize_>(*this, rhs_);
		}
		template<std::size_t OutSize_ = size(), class Rhs_ = emu_vector_type>
		constexpr typename EmuMath::TMPHelpers::emu_vector_from_size_t<OutSize_, bool> ComparePerElement_Greater(const Rhs_& rhs_) const
		{
			return EmuMath::Helpers::VectorComparisonPerElement_Greater<OutSize_>(*this, rhs_);
		}
		template<std::size_t OutSize_ = size(), class Rhs_ = emu_vector_type>
		constexpr typename EmuMath::TMPHelpers::emu_vector_from_size_t<OutSize_, bool> ComparePerElement_GreaterEqual(const Rhs_& rhs_) const
		{
			return EmuMath::Helpers::VectorComparisonPerElement_GreaterEqual<OutSize_>(*this, rhs_);
		}

		template<bool IncludeNonContained_ = false, class Rhs_ = emu_vector_type>
		constexpr bool CompareAll_Equal(const Rhs_& rhs_) const
		{
			return EmuMath::Helpers::VectorComparisonAll_Equal<IncludeNonContained_>(*this, rhs_);
		}
		template<bool IncludeNonContained_ = false, class Rhs_ = emu_vector_type>
		constexpr bool CompareAll_NotEqual(const Rhs_& rhs_) const
		{
			return EmuMath::Helpers::VectorComparisonAll_NotEqual<IncludeNonContained_>(*this, rhs_);
		}
		template<bool IncludeNonContained_ = false, class Rhs_ = emu_vector_type>
		constexpr bool CompareAll_Less(const Rhs_& rhs_) const
		{
			return EmuMath::Helpers::VectorComparisonAll_Less<IncludeNonContained_>(*this, rhs_);
		}
		template<bool IncludeNonContained_ = false, class Rhs_ = emu_vector_type>
		constexpr bool CompareAll_LessEqual(const Rhs_& rhs_) const
		{
			return EmuMath::Helpers::VectorComparisonAll_LessEqual<IncludeNonContained_>(*this, rhs_);
		}
		template<bool IncludeNonContained_ = false, class Rhs_ = emu_vector_type>
		constexpr bool CompareAll_Greater(const Rhs_& rhs_) const
		{
			return EmuMath::Helpers::VectorComparisonAll_Greater<IncludeNonContained_>(*this, rhs_);
		}
		template<bool IncludeNonContained_ = false, class Rhs_ = emu_vector_type>
		constexpr bool CompareAll_GreaterEqual(const Rhs_& rhs_) const
		{
			return EmuMath::Helpers::VectorComparisonAll_GreaterEqual<IncludeNonContained_>(*this, rhs_);
		}

		template<bool IncludeNonContained_ = false, class Rhs_ = emu_vector_type>
		constexpr bool CompareAny_Equal(const Rhs_& rhs_) const
		{
			return EmuMath::Helpers::VectorComparisonAny_Equal<IncludeNonContained_>(*this, rhs_);
		}
		template<bool IncludeNonContained_ = false, class Rhs_ = emu_vector_type>
		constexpr bool CompareAny_NotEqual(const Rhs_& rhs_) const
		{
			return EmuMath::Helpers::VectorComparisonAny_NotEqual<IncludeNonContained_>(*this, rhs_);
		}
		template<bool IncludeNonContained_ = false, class Rhs_ = emu_vector_type>
		constexpr bool CompareAny_Less(const Rhs_& rhs_) const
		{
			return EmuMath::Helpers::VectorComparisonAny_Less<IncludeNonContained_>(*this, rhs_);
		}
		template<bool IncludeNonContained_ = false, class Rhs_ = emu_vector_type>
		constexpr bool CompareAny_LessEqual(const Rhs_& rhs_) const
		{
			return EmuMath::Helpers::VectorComparisonAny_LessEqual<IncludeNonContained_>(*this, rhs_);
		}
		template<bool IncludeNonContained_ = false, class Rhs_ = emu_vector_type>
		constexpr bool CompareAny_Greater(const Rhs_& rhs_) const
		{
			return EmuMath::Helpers::VectorComparisonAny_Greater<IncludeNonContained_>(*this, rhs_);
		}
		template<bool IncludeNonContained_ = false, class Rhs_ = emu_vector_type>
		constexpr bool CompareAny_GreaterEqual(const Rhs_& rhs_) const
		{
			return EmuMath::Helpers::VectorComparisonAny_GreaterEqual<IncludeNonContained_>(*this, rhs_);
		}
#pragma endregion

#pragma region SHUFFLES
		/// <summary> Returns a Vector4 with elements X, Y, Z and W copying the elements at the respective provided indices within this Vector. </summary>
		/// <returns>This vector shuffled as a Vector4.</returns>
		template<std::size_t X_, std::size_t Y_, std::size_t Z_, std::size_t W_, typename OutT = nonref_value_type>
		constexpr Vector4<OutT> Shuffle() const
		{
			return EmuMath::Helpers::VectorShuffle<X_, Y_, Z_, W_, OutT>(*this);
		}
		/// <summary> Returns a Vector3 with elements X, Y and Z copying the elements at the respective provided indices within this Vector. </summary>
		/// <returns>This vector shuffled as a Vector3.</returns>
		template<std::size_t X_, std::size_t Y_, std::size_t Z_, typename OutT = nonref_value_type>
		constexpr Vector3<OutT> Shuffle() const
		{
			return EmuMath::Helpers::VectorShuffle<X_, Y_, Z_, OutT>(*this);
		}
		/// <summary> Returns a Vector2 with elements X and Y copying the elements at the respective provided indices within this Vector. </summary>
		/// <returns>This vector shuffled as a Vector2.</returns>
		template<std::size_t X_, std::size_t Y_, typename OutT = nonref_value_type>
		constexpr Vector2<OutT> Shuffle() const
		{
			return EmuMath::Helpers::VectorShuffle<X_, Y_, OutT>(*this);
		}

		template<std::size_t X_, std::size_t Y_, std::size_t Z_, std::size_t W_>
		Vector4<const_ref_value_type> ShuffleReference() const
		{
			return EmuMath::Helpers::VectorShuffledReference<X_, Y_, Z_, W_>(*this);
		}
		template<std::size_t X_, std::size_t Y_, std::size_t Z_>
		Vector3<const_ref_value_type> ShuffleReference() const
		{
			return EmuMath::Helpers::VectorShuffledReference<X_, Y_, Z_>(*this);
		}
		template<std::size_t X_, std::size_t Y_>
		Vector2<const_ref_value_type> ShuffleReference() const
		{
			return EmuMath::Helpers::VectorShuffledReference<X_, Y_>(*this);
		}

		template<std::size_t X_, std::size_t Y_, std::size_t Z_, std::size_t W_>
		Vector4<ref_value_type> ShuffleReference()
		{
			return EmuMath::Helpers::VectorShuffledReference<X_, Y_, Z_, W_>(*this);
		}
		template<std::size_t X_, std::size_t Y_, std::size_t Z_>
		Vector3<ref_value_type> ShuffleReference()
		{
			return EmuMath::Helpers::VectorShuffledReference<X_, Y_, Z_>(*this);
		}
		template<std::size_t X_, std::size_t Y_>
		Vector2<ref_value_type> ShuffleReference()
		{
			return EmuMath::Helpers::VectorShuffledReference<X_, Y_>(*this);
		}
#pragma endregion

#pragma region SETS
		template<class Rhs_>
		emu_vector_type& Set(const Rhs_& rhs_)
		{
			return EmuMath::Helpers::VectorSet(*this, rhs_);
		}
		template<typename X_, typename Y_>
		emu_vector_type& Set(const X_& x_, const Y_& y_)
		{
			return EmuMath::Helpers::VectorSet(*this, x_, y_);
		}
		template<typename X_, typename Y_, typename Z_>
		emu_vector_type& Set(const X_& x_, const Y_& y_, const Z_& z_)
		{
			return EmuMath::Helpers::VectorSet(*this, x_, y_, z_);
		}
		template<typename X_, typename Y_, typename Z_, typename W_>
		emu_vector_type& Set(const X_& x_, const Y_& y_, const Z_& z_, const W_& w_)
		{
			return EmuMath::Helpers::VectorSet(*this, x_, y_, z_, w_);
		}
#pragma endregion

#pragma region OVERALL_OPERATIONS
		/// <summary>
		/// <para> Calculates the reciprocals of this Vector's elements, with an optionally customisable floating-point output type. </para>
		/// <para> Note that the output type must be a valid floating point type. </para>
		/// </summary>
		/// <typeparam name="OutT">Floating-point type to output the reciprocals as.</typeparam>
		/// <returns>Vector of reciprocals to this Vector's respective elements, stored as the provided OutT (defaults to this Vector's default_floating_point).</returns>
		template<std::size_t OutSize_ = size(), typename OutFP_ = default_floating_point>
		constexpr typename EmuMath::TMPHelpers::emu_vector_from_size<OutSize_, OutFP_>::type Reciprocal() const
		{
			return EmuMath::Helpers::VectorReciprocal<OutSize_, OutFP_>(*this);
		}
		/// <summary>
		/// <para> Calculates the total of all of this Vector's elements added together and outputs the result as an optionally customisable type. </para>
		/// </summary>
		/// <typeparam name="OutT">Type to output the sum as.</typeparam>
		/// <returns>The total of all elements in this Vector added together, represented as the provided OutT (defaults to this Vector's nonref_value_type).</returns>
		template<typename OutT = nonref_value_type>
		constexpr OutT TotalSum() const
		{
			return EmuMath::Helpers::VectorTotalSum<OutT>(*this);
		}
		/// <summary>
		/// <para> Calculates the total of all of this Vector's elements multiplied together and outputs the result as an optionally customisable type. </para>
		/// </summary>
		/// <typeparam name="OutT">Type to output the product as.</typeparam>
		/// <returns>The total of all elements in this Vector multiplied together, represented as the provided OutT (defaults to this Vector's nonref_value_type).</returns>
		template<typename OutT = nonref_value_type>
		constexpr OutT TotalProduct() const
		{
			return EmuMath::Helpers::VectorTotalProduct<OutT>(*this);
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
		/// <summary> Determines the mean average of this Vector's elements (the sum of all elements divided by the size number of elements). </summary>
		/// <typeparam name="OutT">Type to output the mean as. Defaults as this Vector's default_floating_point.</typeparam>
		/// <returns>The mean of this Vector's elements, represented as the provided type.</returns>
		template<typename OutT = default_floating_point>
		constexpr OutT Mean() const
		{
			if constexpr (std::is_floating_point_v<OutT>)
			{
				return (x + y + z + w) * size_reciprocal<OutT>();
			}
			else
			{
				return static_cast<OutT>((x + y + z + w) * size_reciprocal());
			}
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
		typename EmuMath::TMPHelpers::emu_vector_from_size<OutSize_, OutT>::type Floor() const
		{
			return EmuMath::Helpers::VectorFloor<OutSize_, OutT>(*this);
		}
		/// <summary> Calculates the values of this Vector's elements when rounded toward positive infinity. </summary>
		/// <returns>Copy of this Vector with its elements rounded toward positive infinity.</returns>
		template<std::size_t OutSize_ = size(), typename OutT = nonref_value_type>
		typename EmuMath::TMPHelpers::emu_vector_from_size<OutSize_, OutT>::type Ceil() const
		{
			return EmuMath::Helpers::VectorCeil<OutSize_, OutT>(*this);
		}
		/// <summary> Calculates the values of this Vector's elements when rounded toward 0. </summary>
		/// <returns>Copy of this Vector with its elements rounded toward 0.</returns>
		template<std::size_t OutSize_ = size(), typename OutT = nonref_value_type>
		typename EmuMath::TMPHelpers::emu_vector_from_size<OutSize_, OutT>::type Trunc() const
		{
			return EmuMath::Helpers::VectorTrunc<OutSize_, OutT>(*this);
		}

		template<std::size_t OutSize_ = size(), typename OutT = nonref_value_type>
		constexpr typename EmuMath::TMPHelpers::emu_vector_from_size<OutSize_, OutT>::type FloorConstexpr() const
		{
			return EmuMath::Helpers::VectorFloorConstexpr<OutSize_, OutT>(*this);
		}
		template<std::size_t OutSize_ = size(), typename OutT = nonref_value_type>
		constexpr typename EmuMath::TMPHelpers::emu_vector_from_size<OutSize_, OutT>::type CeilConstexpr() const
		{
			return EmuMath::Helpers::VectorCeilConstexpr<OutSize_, OutT>(*this);
		}
		template<std::size_t OutSize_ = size(), typename OutT = nonref_value_type>
		constexpr typename EmuMath::TMPHelpers::emu_vector_from_size<OutSize_, OutT>::type TruncConstexpr() const
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
		Vector4<OutFP> Normalise() const
		{
			return EmuMath::Helpers::VectorNormalise<OutFP>(*this);
		}
		template<typename OutFP = default_floating_point>
		constexpr Vector4<OutFP> NormaliseConstexpr() const
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
		template<typename OutT = default_floating_point, typename RhsVector_ = copy_vector>
		constexpr OutT DotProduct(const RhsVector_& rhs) const
		{
			return EmuMath::Helpers::VectorDotProduct<OutT>(*this, rhs);
		}
		/// <summary>
		/// <para> Returns a reversed version of this Vector, with an optional different type. </para>
		/// </summary>
		/// <typeparam name="OutT_">Type for the returned Vector to contain. Defaults to this Vector's nonref_value_type.</typeparam>
		/// <returns>Reversed version of this Vector.</returns>
		template<std::size_t OutSize_ = size(), typename OutT_ = nonref_value_type>
		constexpr typename EmuMath::TMPHelpers::emu_vector_from_size<OutSize_, OutT_>::type Reverse() const
		{
			return EmuMath::Helpers::VectorReverse<OutSize_, OutT_>(*this);
		}

		template<typename OutT_ = nonref_value_type, typename BT_>
		constexpr Vector3<OutT_> CrossProductV3(const Vector3<BT_>& b_) const
		{
			return EmuMath::Helpers::VectorCrossProductV3<OutT_>(*this, b_);
		}
		template<typename OutT_ = nonref_value_type, typename BT_>
		constexpr Vector3<OutT_> CrossProductV3(const Vector4<BT_>& b_) const
		{
			return EmuMath::Helpers::VectorCrossProductV3<OutT_>(*this, b_);
		}
#pragma endregion

		/// <summary> The first component of this vector, representing the X-axis. </summary>
		value_type x;
		/// <summary> The second component of this vector, representing the Y-axis. </summary>
		value_type y;
		/// <summary> The third component of this vector, representing the Z-axis. </summary>
		value_type z;
		/// <summary> The fourth component of this vector, representing the W-axis. </summary>
		value_type w;
	};
}

#endif
