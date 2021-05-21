#ifndef EMU_MATH_VECTOR_4_T_H_INC_
#define EMU_MATH_VECTOR_4_T_H_INC_

#include "EmuVectorInfo.h"
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

#pragma region ASSIGNMENT_OPERATORS
		template<typename OtherT>
		constexpr Vector4<value_type>& operator=(const Vector4<OtherT>& rhs)
		{
			if constexpr (std::is_same_v<nonref_value_type, typename Vector2<OtherT>::nonref_value_type>)
			{
				x = rhs.x;
				y = rhs.y;
				z = rhs.z;
				w = rhs.w;
			}
			else
			{
				x = static_cast<nonref_value_type>(rhs.x);
				y = static_cast<nonref_value_type>(rhs.y);
				z = static_cast<nonref_value_type>(rhs.z);
				w = static_cast<nonref_value_type>(rhs.w);
			}
			return *this;
		}
		template<typename OtherT>
		constexpr Vector4<value_type>& operator=(const Vector3<OtherT>& rhs)
		{
			if constexpr (std::is_same_v<nonref_value_type, typename info_type_t<OtherT>::nonref_value_type>)
			{
				x = rhs.x;
				y = rhs.y;
				z = rhs.z;
				w = info_type::value_zero;
			}
			else
			{
				x = static_cast<nonref_value_type>(rhs.x);
				y = static_cast<nonref_value_type>(rhs.y);
				z = static_cast<nonref_value_type>(rhs.z);
				w = info_type::value_zero;
			}
			return *this;
		}
		template<typename OtherT>
		constexpr Vector4<value_type>& operator=(const Vector2<OtherT>& rhs)
		{
			if constexpr (std::is_same_v<nonref_value_type, typename Vector2<OtherT>::nonref_value_type>)
			{
				x = rhs.x;
				y = rhs.y;
				z = info_type::value_zero;
				w = info_type::value_zero;
			}
			else
			{
				x = static_cast<nonref_value_type>(rhs.x);
				y = static_cast<nonref_value_type>(rhs.y);
				z = info_type::value_zero;
				w = info_type::value_zero;
			}
			return *this;
		}
#pragma endregion

#pragma region SHUFFLES
		/// <summary> Returns a Vector4 with elements X, Y, Z and W copying the elements at the respective provided indices within this Vector. </summary>
		/// <returns>This vector shuffled as a Vector4.</returns>
		template<std::size_t X_, std::size_t Y_, std::size_t Z_, std::size_t W_, typename OutT = nonref_value_type>
		constexpr Vector4<OutT> AsShuffled() const
		{
			return Vector4<OutT>(at<X_>(), at<Y_>(), at<Z_>(), at<W_>());
		}
		/// <summary> Returns a Vector3 with elements X, Y and Z copying the elements at the respective provided indices within this Vector. </summary>
		/// <returns>This vector shuffled as a Vector3.</returns>
		template<std::size_t X_, std::size_t Y_, std::size_t Z_, typename OutT = nonref_value_type>
		constexpr Vector3<OutT> AsShuffled() const
		{
			return Vector3<OutT>(at<X_>(), at<Y_>(), at<Z_>());
		}
		/// <summary> Returns a Vector2 with elements X and Y copying the elements at the respective provided indices within this Vector. </summary>
		/// <returns>This vector shuffled as a Vector2.</returns>
		template<std::size_t X_, std::size_t Y_, typename OutT = nonref_value_type>
		constexpr Vector2<OutT> AsShuffled() const
		{
			return Vector2<OutT>(at<X_>(), at<Y_>());
		}
		/// <summary>
		///	<para> Returns a Vector4 with elements X, Y, Z and W copying the elements at the respective provided indices within this Vector. </para>
		/// <para> If possible, it is recommended to use the templatised version of this function. </para>
		/// </summary>
		/// <returns>This Vector shuffled as a Vector4.</returns>
		template<typename OutT = nonref_value_type>
		Vector4<OutT> AsShuffled(const std::size_t x_, const std::size_t y_, const std::size_t z_, const std::size_t w_) const
		{
			return Vector4<OutT>(at(x_), at(y_), at(z_), at(w_));
		}
		/// <summary>
		///	<para> Returns a Vector3 with elements X, Y and Z copying the elements at the respective provided indices within this Vector. </para>
		/// <para> If possible, it is recommended to use the templatised version of this function. </para>
		/// </summary>
		/// <returns>This Vector shuffled as a Vector3.</returns>
		template<typename OutT = nonref_value_type>
		Vector3<OutT> AsShuffled(const std::size_t x_, const std::size_t y_, const std::size_t z_) const
		{
			return Vector3<OutT>(at(x_), at(y_), at(z_));
		}
		/// <summary>
		/// <para> Returns a Vector2 with elements X and Y copying the elements at the respective provided indices within this Vector. </para>
		/// <para> If possible, it is recommended to use the templatised version of this function. </para>
		/// </summary>
		/// <returns>This Vector shuffled as a Vector2.</returns>
		template<typename OutT = nonref_value_type>
		Vector2<OutT> AsShuffled(const std::size_t x_, const std::size_t y_) const
		{
			return Vector2<OutT>(at(x_), at(y_));
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

	private:
	};
}

#endif
