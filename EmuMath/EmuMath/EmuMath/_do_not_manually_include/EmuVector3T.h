#ifndef EMU_MATH_VECTOR_3_T_H_INC_
#define EMU_MATH_VECTOR_3_T_H_INC_

#include "EmuVectorInfo.h"
#include <exception>

namespace EmuMath
{
	template<typename T>
	struct Vector2;

	template<typename T>
	struct Vector3
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
		using nonref_value_type_without_qualifiers = typename info_type::nonref_value_type_without_qualifiers;

		/// <summary> The number of elements contained within this vector. </summary>
		/// <returns>3</returns>
		static constexpr std::size_t size()
		{
			return 3;
		}
#pragma endregion

#pragma region CONSTRUCTORS
		constexpr Vector3() :
			x(),
			y(),
			z()
		{
		}
		constexpr Vector3(const value_type& x_, const value_type& y_, const value_type& z_) :
			x(x_),
			y(y_),
			z(z_)
		{
		}
		template<typename X_>
		constexpr Vector3(const X_& x_, const value_type& y_, const value_type& z_) :
			x(static_cast<value_type>(x_)),
			y(y_),
			z(z_)
		{
		}
		template<typename Y_>
		constexpr Vector3(const value_type& x_, const Y_& y_, const value_type& z_) :
			x(x_),
			y(static_cast<value_type>(y_)),
			z(z_)
		{
		}
		template<typename Z_>
		constexpr Vector3(const value_type& x_, const value_type& y_, const Z_& z_) :
			x(x_),
			y(y_),
			z(static_cast<value_type>(z_))
		{
		}
		template<typename X_, typename Y_>
		constexpr Vector3(const X_& x_, const Y_& y_, const value_type& z_) :
			x(static_cast<value_type>(x_)),
			y(static_cast<value_type>(y_)),
			z(z_)
		{
		}
		template<typename X_, typename Z_>
		constexpr Vector3(const X_& x_, const value_type& y_, const Z_& z_) :
			x(static_cast<value_type>(x_)),
			y(y_),
			z(static_cast<value_type>(z_))
		{
		}
		template<typename Y_, typename Z_>
		constexpr Vector3(const value_type& x_, const Y_& y_, const Z_& z_) :
			x(x_),
			y(static_cast<value_type>(y_)),
			z(static_cast<value_type>(z_))
		{
		}
		template<typename X_, typename Y_, typename Z_>
		constexpr Vector3(const X_& x_, const Y_& y_, const Z_& z_) :
			x(static_cast<value_type>(x_)),
			y(static_cast<value_type>(y_)),
			z(static_cast<value_type>(z_))
		{
		}
		template<typename OtherT>
		constexpr Vector3(const Vector3<OtherT>& toCopy) :
			Vector3(toCopy.x, toCopy.y, toCopy.z)
		{
		}
		template<typename OtherT>
		constexpr Vector3(Vector3<OtherT>& toCopy) :
			Vector3(toCopy.x, toCopy.y, toCopy.z)
		{
		}
		template<typename OtherT>
		constexpr Vector3(const Vector2<OtherT>& toCopy) :
			Vector3(toCopy.x, toCopy.y, value_type())
		{
		}
		template<typename OtherT>
		constexpr Vector3(Vector2<OtherT>& toCopy) :
			Vector3(toCopy.x, toCopy.y, value_type())
		{
		}
		template<typename OtherT, typename Z_>
		constexpr Vector3(const Vector2<OtherT>& toCopy, const Z_& z_) :
			Vector3(toCopy.x, toCopy.y, z_)
		{
		}
		template<typename OtherT, typename Z_>
		constexpr Vector3(Vector2<OtherT>& toCopy, const Z_& z_) :
			Vector3(toCopy.x, toCopy.y, z_)
		{
		}
		template<typename OtherT, typename Z_>
		constexpr Vector3(Vector2<OtherT>& toCopy, Z_& z_) :
			Vector3(toCopy.x, toCopy.y, z_)
		{
		}
#pragma endregion

		/// <summary> The first component of this vector, representing the X-axis. </summary>
		value_type x;
		/// <summary> The second component of this vector, representing the Y-axis. </summary>
		value_type y;
		/// <summary> The third component of this vector, representing the Z-axis. </summary>
		value_type z;
	};
}

#endif