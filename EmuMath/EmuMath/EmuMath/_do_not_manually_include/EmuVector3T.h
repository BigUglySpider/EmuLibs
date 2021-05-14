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

#pragma region RANDOM_ACCESS
		/// <summary>
		///	<para> Access the element of this vector at the provided index, where x is index 0 and z is index 2. </para>
		/// <para> If possible, it is recommended to use the templatised at function instead. </para>
		/// </summary>
		/// <param name="index">Index of the element to access.</param>
		/// <returns>Reference to the element at the provided index.</returns>
		ref_value_type operator[](const std::size_t index)
		{
			return at(index);
		}
		/// <summary>
		///	<para> Access the element of this vector at the provided index, where x is index 0 and z is index 2. </para>
		/// <para> If possible, it is recommended to use the templatised at function instead. </para>
		/// </summary>
		/// <param name="index">Index of the element to access.</param>
		/// <returns>Constant reference to the element at the provided index.</returns>
		const_ref_value_type operator[](const std::size_t index) const
		{
			return at(index);
		}
		/// <summary>
		///	<para> Access the element of this vector at the provided index, where x is index 0 and z is index 2. </para>
		/// <para> If possible, it is recommended to use the templatised version of this function. </para>
		/// </summary>
		/// <param name="index">Index of the element to access.</param>
		/// <returns>Reference to the element at the provided index.</returns>
		ref_value_type at(const std::size_t index)
		{
			switch (index)
			{
				case 0:
					return x;
				case 1:
					return y;
				case 2:
					return z;
				default:
					throw std::logic_error("Attempted to access an EmuMath::Vector3 element by an index which does not exist.");
			}
		}
		/// <summary>
		///	<para> Access the element of this vector at the provided index, where x is index 0 and z is index 2. </para>
		/// <para> If possible, it is recommended to use the templatised version of this function. </para>
		/// </summary>
		/// <param name="index">Index of the element to access.</param>
		/// <returns>Constant reference to the element at the provided index.</returns>
		const_ref_value_type at(const std::size_t index) const
		{
			switch (index)
			{
			case 0:
				return x;
			case 1:
				return y;
			case 2:
				return z;
			default:
				throw std::logic_error("Attempted to access an EmuMath::Vector3 element by an index which does not exist.");
			}
		}
		/// <summary> Access the element of this vector at the provided index, where x is index 0 and z is index 2. </summary>
		/// <returns>Reference to the element at the provided index.</returns>
		template<std::size_t Index_>
		ref_value_type at()
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
			else
			{
				static_assert(false, "Attempted to access an EmuMath::Vector3 element by an index which does not exist.");
			}
		}
		/// <summary> Access the element of this vector at the provided index, where x is index 0 and z is index 2. </summary>
		/// <returns>Constant reference to the element at the provided index.</returns>
		template<std::size_t Index_>
		const_ref_value_type at() const
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
			else
			{
				static_assert(false, "Attempted to access an EmuMath::Vector3 element by an index which does not exist.");
			}
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
		/// <typeparam name="Z_">Type of the value to set this Vector's z component to.</typeparam>
		/// <param name="x_">Value to set this Vector's x component to.</param>
		/// <param name="y_">Value to set this Vector's y component to.</param>
		/// <param name="z_">Value to set this Vector's z component to.</param>
		template<typename X_, typename Y_, typename Z_>
		constexpr void SetAll(const X_& x_, const Y_& y_, const Z_& z_)
		{
			if constexpr (!info_type::has_const_values)
			{
				_set_individual_value<0, X_>(x_);
				_set_individual_value<1, Y_>(y_);
				_set_individual_value<2, Z_>(z_);
			}
			else
			{
				static_assert(false, "Attempted to perform a non-const function (SetAll<X_, Y_>) on an EmuMath::Vector3 which contains constant values.");
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
					z = val_;
				}
				else
				{
					const nonref_value_type castVal = static_cast<nonref_value_type>(val_);
					x = castVal;
					y = castVal;
					z = castVal;
				}
			}
			else
			{
				static_assert(false, "Attempted to perform a non-const function (SetAll<T_>) on an EmuMath::Vector3 which contains constant values.");
			}
		}
#pragma endregion

		/// <summary> The first component of this vector, representing the X-axis. </summary>
		value_type x;
		/// <summary> The second component of this vector, representing the Y-axis. </summary>
		value_type y;
		/// <summary> The third component of this vector, representing the Z-axis. </summary>
		value_type z;

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