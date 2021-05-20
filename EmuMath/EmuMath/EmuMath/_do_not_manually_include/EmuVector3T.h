#ifndef EMU_MATH_VECTOR_3_T_H_INC_
#define EMU_MATH_VECTOR_3_T_H_INC_

#include "EmuVectorInfo.h"
#include <exception>

namespace EmuMath
{
	template<typename T>
	struct Vector2;
	template<typename T>
	struct Vector4;

	/// <summary> Generic Vector type which contains 3 elements of the provided type, representing the X-, Y- and Z-axes respectively. </summary>
	/// <typeparam name="T">Type to store within the Vector.</typeparam>
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
		/// <summary> The non-qualified, non-reference variant of the value types stored within this vector. </summary>
		using nonref_value_type_without_qualifiers = typename info_type::nonref_value_type_without_qualifiers;
		/// <summary> The default floating point value used by relevant functions for this vector type. </summary>
		using default_floating_point = typename info_type::default_floating_point;

		/// <summary> The number of elements contained within this vector. </summary>
		/// <returns>3</returns>
		static constexpr std::size_t size()
		{
			return 3;
		}
#pragma endregion

#pragma region CONSTRUCTORS
		/// <summary> Constructs a 3-dimensional Vector with its x, y and z elements set to their default constructors. </summary>
		constexpr Vector3() :
			x(),
			y(),
			z()
		{
		}
		/// <summary> Constructs a 3-dimensional Vector with its x, y and z elements set to copies of the respective passed values. </summary>
		/// <param name="x_">Value to copy to the Vector's x component.</param>
		/// <param name="y_">Value to copy to the Vector's y component.</param>
		/// <param name="z_">Value to copy to the Vector's z component.</param>
		constexpr Vector3(const value_type& x_, const value_type& y_, const value_type& z_) :
			x(x_),
			y(y_),
			z(z_)
		{
		}
		/// <summary> Constructs a 3-dimensional Vector with its x set to a copy of the passed x_ value after a static_cast, and y and z direct copies of their respective values. </summary>
		/// <typeparam name="X_">Non value_type type used for the passed x_ value.</typeparam>
		/// <param name="x_">Value to cast and copy to the Vector's x component.</param>
		/// <param name="y_">Value to copy to the Vector's y component.</param>
		/// <param name="z_">Value to copy to the Vector's z component.</param>
		template<typename X_>
		constexpr Vector3(const X_& x_, const value_type& y_, const value_type& z_) :
			x(static_cast<value_type>(x_)),
			y(y_),
			z(z_)
		{
		}
		/// <summary> Constructs a 3-dimensional Vector with its y set to a copy of the passed y_ value after a static_cast, and x and z direct copies of their respective values. </summary>
		/// <typeparam name="X_">Non value_type type used for the passed x_ value.</typeparam>
		/// <param name="x_">Value to copy to the Vector's x component.</param>
		/// <param name="y_">Value to cast and copy to the Vector's y component.</param>
		/// <param name="z_">Value to copy to the Vector's z component.</param>
		template<typename Y_>
		constexpr Vector3(const value_type& x_, const Y_& y_, const value_type& z_) :
			x(x_),
			y(static_cast<value_type>(y_)),
			z(z_)
		{
		}
		/// <summary> Constructs a 3-dimensional Vector with its z set to a copy of the passed z_ value after a static_cast, and x and y direct copies of their respective values. </summary>
		/// <typeparam name="X_">Non value_type type used for the passed x_ value.</typeparam>
		/// <param name="x_">Value to copy to the Vector's x component.</param>
		/// <param name="y_">Value to copy to the Vector's y component.</param>
		/// <param name="z_">Value to cast and copy to the Vector's z component.</param>
		template<typename Z_>
		constexpr Vector3(const value_type& x_, const value_type& y_, const Z_& z_) :
			x(x_),
			y(y_),
			z(static_cast<value_type>(z_))
		{
		}
		/// <summary>
		/// Constructs a 3-dimensional Vector with its x and y set to a copy of the respective passed values after a static_cast, and z a direct copy of the passed z_.
		/// </summary>
		/// <typeparam name="X_">Non value_type type used for the passed x_ value.</typeparam>
		/// <typeparam name="Y_">Non value_type type used for the passed y_ value.</typeparam>
		/// <param name="x_">Value to cast and copy to the Vector's x component.</param>
		/// <param name="y_">Value to cast and copy to the Vector's y component.</param>
		/// <param name="z_">Value to copy to the Vector's z component.</param>
		template<typename X_, typename Y_>
		constexpr Vector3(const X_& x_, const Y_& y_, const value_type& z_) :
			x(static_cast<value_type>(x_)),
			y(static_cast<value_type>(y_)),
			z(z_)
		{
		}
		/// <summary>
		/// Constructs a 3-dimensional Vector with its x and z set to a copy of the respective passed values after a static_cast, and y a direct copy of the passed y_.
		/// </summary>
		/// <typeparam name="X_">Non value_type type used for the passed x_ value.</typeparam>
		/// <typeparam name="Z_">Non value_type type used for the passed z_ value.</typeparam>
		/// <param name="x_">Value to cast and copy to the Vector's x component.</param>
		/// <param name="y_">Value to copy to the Vector's y component.</param>
		/// <param name="z_">Value to cast and copy to the Vector's z component.</param>
		template<typename X_, typename Z_>
		constexpr Vector3(const X_& x_, const value_type& y_, const Z_& z_) :
			x(static_cast<value_type>(x_)),
			y(y_),
			z(static_cast<value_type>(z_))
		{
		}
		/// <summary>
		/// Constructs a 3-dimensional Vector with its y and z set to a copy of the respective passed values after a static_cast, and x a direct copy of the passed x_.
		/// </summary>
		/// <typeparam name="Y_">Non value_type type used for the passed x_ value.</typeparam>
		/// <typeparam name="Z_">Non value_type type used for the passed y_ value.</typeparam>
		/// <param name="x_">Value to copy to the Vector's x component.</param>
		/// <param name="y_">Value to cast and copy to the Vector's y component.</param>
		/// <param name="z_">Value to cast and copy to the Vector's z component.</param>
		template<typename Y_, typename Z_>
		constexpr Vector3(const value_type& x_, const Y_& y_, const Z_& z_) :
			x(x_),
			y(static_cast<value_type>(y_)),
			z(static_cast<value_type>(z_))
		{
		}
		/// <summary> Constructs a 2-dimensional Vector with its x, y and z elements set to copies of the respective passed values after a static_cast. </summary>
		/// <typeparam name="X_">Non value_type type used for the passed x_ value.</typeparam>
		/// <typeparam name="Y_">Non value_type type used for the passed y_ value.</typeparam>
		/// <typeparam name="Z_">Non value_type type used for the passed z_ value.</typeparam>
		/// <param name="x_">Value to cast and copy to the Vector's x component.</param>
		/// <param name="y_">Value to cast and copy to the Vector's y component.</param>
		/// <param name="z_">Value to cast and copy to the Vector's z component.</param>
		template<typename X_, typename Y_, typename Z_>
		constexpr Vector3(const X_& x_, const Y_& y_, const Z_& z_) :
			x(static_cast<value_type>(x_)),
			y(static_cast<value_type>(y_)),
			z(static_cast<value_type>(z_))
		{
		}
		/// <summary> Constructs a 3-dimensional vector with its x, y and z components set to copies of the passed vector's respective components, performing casts where needed. </summary>
		/// <typeparam name="OtherT">The contained type within the passed Vector3.</typeparam>
		/// <param name="toCopy">Vector to copy the elements of.</param>
		template<typename OtherT>
		constexpr Vector3(const Vector3<OtherT>& toCopy) :
			Vector3(toCopy.x, toCopy.y, toCopy.z)
		{
		}
		/// <summary> Constructs a 3-dimensional vector with its x, y and z components set to copies of the passed vector's respective components, performing casts where needed. </summary>
		/// <typeparam name="OtherT">The contained type within the passed Vector3.</typeparam>
		/// <param name="toCopy">Vector to copy the elements of.</param>
		template<typename OtherT>
		constexpr Vector3(Vector3<OtherT>& toCopy) :
			Vector3(toCopy.x, toCopy.y, toCopy.z)
		{
		}
		/// <summary> Constructs a 3-dimensional vector with its x, y and z components set to copies of the passed vector's respective components, performing casts where needed. </summary>
		/// <typeparam name="OtherT">The contained type within the passed Vector3.</typeparam>
		/// <param name="toCopy">Vector to copy the elements of.</param>
		template<typename OtherT>
		constexpr Vector3(const Vector4<OtherT>& toCopy) :
			Vector3(toCopy.x, toCopy.y, toCopy.z)
		{
		}
		/// <summary> Constructs a 3-dimensional vector with its x, y and z components set to copies of the passed vector's respective components, performing casts where needed. </summary>
		/// <typeparam name="OtherT">The contained type within the passed Vector3.</typeparam>
		/// <param name="toCopy">Vector to copy the elements of.</param>
		template<typename OtherT>
		constexpr Vector3(Vector4<OtherT>& toCopy) :
			Vector3(toCopy.x, toCopy.y, toCopy.z)
		{
		}
		/// <summary>
		/// <para>Constructs a 3-dimensional vector with its x and y components set to copies of the passed vector's respective components, performing casts where needed.</para>
		/// <para>The vector's z value will be set to a default constructed value_type.</para>
		/// </summary>
		/// <typeparam name="OtherT">The contained type within the passed Vector3.</typeparam>
		/// <param name="toCopy">Vector to copy the elements of.</param>
		template<typename OtherT>
		explicit constexpr Vector3(const Vector2<OtherT>& toCopy) :
			Vector3(toCopy.x, toCopy.y, value_type())
		{
		}
		/// <summary>
		/// <para>Constructs a 3-dimensional vector with its x and y components set to copies of the passed vector's respective components, performing casts where needed.</para>
		/// <para>The vector's z value will be set via the passed z_ value..</para>
		/// </summary>
		/// <typeparam name="OtherT">The contained type within the passed Vector3.</typeparam>
		/// <typeparam name="Z_">The type of the passed z_ value.</typeparam>
		/// <param name="toCopy">Vector to copy the elements of.</param>
		/// <param name="z_">Value to set the vector's z component via.</param>
		template<typename OtherT, typename Z_>
		explicit constexpr Vector3(const Vector2<OtherT>& toCopy, const Z_& z_) :
			Vector3(toCopy.x, toCopy.y, z_)
		{
		}
		/// <summary>
		/// <para>Constructs a 3-dimensional vector with its x and y components set to copies of the passed vector's respective components, performing casts where needed.</para>
		/// <para>The vector's z value will be set to the default value_type.</para>
		/// </summary>
		/// <typeparam name="OtherT">The contained type within the passed Vector3.</typeparam>
		/// <param name="toCopy">Vector to copy the elements of.</param>
		template<typename OtherT>
		explicit constexpr Vector3(Vector2<OtherT>& toCopy) :
			Vector3(toCopy.x, toCopy.y, value_type())
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

#pragma region ASSIGNMENT_OPERATORS
		template<typename OtherT>
		constexpr Vector3<value_type>& operator=(const Vector3<OtherT>& rhs)
		{
			if constexpr (std::is_same_v<nonref_value_type, typename info_type_t<OtherT>::nonref_value_type>)
			{
				x = rhs.x;
				y = rhs.y;
				z = rhs.z;
			}
			else
			{
				x = static_cast<nonref_value_type>(rhs.x);
				y = static_cast<nonref_value_type>(rhs.y);
				z = static_cast<nonref_value_type>(rhs.z);
			}
			return *this;
		}
		template<typename OtherT>
		constexpr Vector3<value_type>& operator=(const Vector2<OtherT>& rhs)
		{
			if constexpr (std::is_same_v<nonref_value_type, typename Vector2<OtherT>::nonref_value_type>)
			{
				x = rhs.x;
				y = rhs.y;
				z = info_type::value_zero;
			}
			else
			{
				x = static_cast<nonref_value_type>(rhs.x);
				y = static_cast<nonref_value_type>(rhs.y);
				z = info_type::value_zero;
			}
			return *this;
		}
		template<typename OtherT>
		constexpr Vector3<value_type>& operator=(const Vector4<OtherT>& rhs)
		{
			if constexpr (std::is_same_v<nonref_value_type, typename Vector2<OtherT>::nonref_value_type>)
			{
				x = rhs.x;
				y = rhs.y;
				z = rhs.z;
			}
			else
			{
				x = static_cast<nonref_value_type>(rhs.x);
				y = static_cast<nonref_value_type>(rhs.y);
				z = static_cast<nonref_value_type>(rhs.z);
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
			return this->_perform_vector_bitwise_op_emu<RhsVec, OutVector, EmuCore::TMPHelpers::bitwise_and_diff_types>(rhs);
		}
		template<typename RhsT, typename OutVector>
		constexpr OutVector _perform_scalar_and(const RhsT& rhs) const
		{
			return this->_perform_scalar_bitwise_op_emu<RhsT, OutVector, EmuCore::TMPHelpers::bitwise_and_diff_types>(rhs);
		}

		template<typename RhsVec, typename OutVector>
		constexpr OutVector _perform_vector_or(const RhsVec& rhs) const
		{
			return this->_perform_vector_bitwise_op_emu<RhsVec, OutVector, EmuCore::TMPHelpers::bitwise_or_diff_types>(rhs);
		}
		template<typename RhsT, typename OutVector>
		constexpr OutVector _perform_scalar_or(const RhsT& rhs) const
		{
			return this->_perform_scalar_bitwise_op_emu<RhsT, OutVector, EmuCore::TMPHelpers::bitwise_or_diff_types>(rhs);
		}

		template<typename RhsVec, typename OutVector>
		constexpr OutVector _perform_vector_xor(const RhsVec& rhs) const
		{
			return this->_perform_vector_bitwise_op_emu<RhsVec, OutVector, EmuCore::TMPHelpers::bitwise_xor_diff_types>(rhs);
		}
		template<typename RhsT, typename OutVector>
		constexpr OutVector _perform_scalar_xor(const RhsT& rhs) const
		{
			return this->_perform_scalar_bitwise_op_emu<RhsT, OutVector, EmuCore::TMPHelpers::bitwise_xor_diff_types>(rhs);
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

		template<std::size_t Size_, typename RhsVector>
		constexpr EmuMath::TMPHelpers::emu_vector_from_size_t<Size_, bool> _perform_vector_compare_equal(const RhsVector& rhs) const
		{
			return this->_perform_vector_comparison_std<Size_, RhsVector, std::equal_to>(rhs);
		}
		template<std::size_t Size_, typename RhsVector>
		constexpr EmuMath::TMPHelpers::emu_vector_from_size_t<Size_, bool> _perform_scalar_compare_equal(const RhsVector& rhs) const
		{
			return this->_perform_scalar_comparison_std<Size_, RhsVector, std::equal_to>(rhs);
		}

		template<std::size_t Size_, typename RhsVector>
		constexpr EmuMath::TMPHelpers::emu_vector_from_size_t<Size_, bool> _perform_vector_compare_not_equal(const RhsVector& rhs) const
		{
			return this->_perform_vector_comparison_std<Size_, RhsVector, std::not_equal_to>(rhs);
		}
		template<std::size_t Size_, typename RhsVector>
		constexpr EmuMath::TMPHelpers::emu_vector_from_size_t<Size_, bool> _perform_scalar_compare_not_equal(const RhsVector& rhs) const
		{
			return this->_perform_scalar_comparison_std<Size_, RhsVector, std::not_equal_to>(rhs);
		}

		template<std::size_t Size_, typename RhsVector>
		constexpr EmuMath::TMPHelpers::emu_vector_from_size_t<Size_, bool> _perform_vector_compare_less(const RhsVector& rhs) const
		{
			return this->_perform_vector_comparison_std<Size_, RhsVector, std::less>(rhs);
		}
		template<std::size_t Size_, typename RhsVector>
		constexpr EmuMath::TMPHelpers::emu_vector_from_size_t<Size_, bool> _perform_scalar_compare_less(const RhsVector& rhs) const
		{
			return this->_perform_scalar_comparison_std<Size_, RhsVector, std::less>(rhs);
		}

		template<std::size_t Size_, typename RhsVector>
		constexpr EmuMath::TMPHelpers::emu_vector_from_size_t<Size_, bool> _perform_vector_compare_greater(const RhsVector& rhs) const
		{
			return this->_perform_vector_comparison_std<Size_, RhsVector, std::greater>(rhs);
		}
		template<std::size_t Size_, typename RhsVector>
		constexpr EmuMath::TMPHelpers::emu_vector_from_size_t<Size_, bool> _perform_scalar_compare_greater(const RhsVector& rhs) const
		{
			return this->_perform_scalar_comparison_std<Size_, RhsVector, std::greater>(rhs);
		}

		template<std::size_t Size_, typename RhsVector>
		constexpr EmuMath::TMPHelpers::emu_vector_from_size_t<Size_, bool> _perform_vector_compare_less_equal(const RhsVector& rhs) const
		{
			return this->_perform_vector_comparison_std<Size_, RhsVector, std::less_equal>(rhs);
		}
		template<std::size_t Size_, typename RhsVector>
		constexpr EmuMath::TMPHelpers::emu_vector_from_size_t<Size_, bool> _perform_scalar_compare_less_equal(const RhsVector& rhs) const
		{
			return this->_perform_scalar_comparison_std<Size_, RhsVector, std::less_equal>(rhs);
		}

		template<std::size_t Size_, typename RhsVector>
		constexpr EmuMath::TMPHelpers::emu_vector_from_size_t<Size_, bool> _perform_vector_compare_greater_equal(const RhsVector& rhs) const
		{
			return this->_perform_vector_comparison_std<Size_, RhsVector, std::greater_equal>(rhs);
		}
		template<std::size_t Size_, typename RhsVector>
		constexpr EmuMath::TMPHelpers::emu_vector_from_size_t<Size_, bool> _perform_scalar_compare_greater_equal(const RhsVector& rhs) const
		{
			return this->_perform_scalar_comparison_std<Size_, RhsVector, std::greater_equal>(rhs);
		}

		template<std::size_t NumElementsToCheck_, typename RhsT, template<class> class Func_>
		constexpr bool _perform_overall_comparison_std(const RhsT& rhs) const
		{
			using Func = Func_<nonref_value_type_without_qualifiers>;
			Func func = Func();
			if constexpr (EmuMath::TMPHelpers::is_emu_vector_v<RhsT>)
			{
				if constexpr (NumElementsToCheck_ == 1)
				{
					return func(x, rhs.x);
				}
				else if constexpr (NumElementsToCheck_ == 2)
				{
					return func(x, rhs.x) && func(y, rhs.y);
				}
				else if constexpr (NumElementsToCheck_ == 3)
				{
					return func(x, rhs.x) && func(y, rhs.y) && func(z, EmuMath::TMPHelpers::emu_vector_z(rhs));
				}
				else if constexpr (NumElementsToCheck_ == 4)
				{
					return
					(
						func(x, rhs.x) &&
						func(y, rhs.y) &&
						func(z, EmuMath::TMPHelpers::emu_vector_z(rhs)) &&
						func(info_type::value_zero, EmuMath::TMPHelpers::emu_vector_w(rhs))
					);
				}
				else
				{
					static_assert(false, "Attempted to perform a per-element comparison on an EmuMath::Vector2 with an unsupported number of elements in the comparison.");
				}
			}
			else
			{
				if constexpr (NumElementsToCheck_ == 1)
				{
					return func(x, rhs);
				}
				else if constexpr (NumElementsToCheck_ == 2)
				{
					return func(x, rhs) && func(y, rhs);
				}
				else if constexpr (NumElementsToCheck_ == 3 || NumElementsToCheck_ == 4)
				{
					// z and w result in the same output when comparisng to a scalar since they are both implied zero comparisons in a Vector2
					return func(x, rhs) && func(y, rhs) && func(z, rhs);
				}
				else
				{
					static_assert(false, "Attempted to perform a per-element comparison on an EmuMath::Vector2 with an unsupported number of elements in the comparison.");
				}
			}
		}

		template<std::size_t Size_, typename RhsVector, template<class> class Func_>
		constexpr EmuMath::TMPHelpers::emu_vector_from_size_t<Size_, bool> _perform_vector_comparison_std(const RhsVector& rhs) const
		{
			using OutVector = EmuMath::TMPHelpers::emu_vector_from_size_t<Size_, bool>;
			using Func = Func_<nonref_value_type>;
			Func func = Func();
			if constexpr (Size_ == 2)
			{
				return OutVector
				(
					func(x, rhs.x),
					func(y, rhs.y)
				);
			}
			else if constexpr (Size_ == 3)
			{
				return OutVector
				(
					func(x, rhs.x),
					func(y, rhs.y),
					func(z, EmuMath::TMPHelpers::emu_vector_z(rhs))
				);
			}
			else if constexpr (Size_ == 4)
			{
				return OutVector
				(
					func(x, rhs.x),
					func(y, rhs.y),
					func(z, EmuMath::TMPHelpers::emu_vector_z(rhs)),
					func(info_type::value_zero, EmuMath::TMPHelpers::emu_vector_w(rhs))
				);
			}
			else
			{
				static_assert(false, "Attempted to perform a per-element comparison on an EmuMath::Vector2 with an unsupported size of output Vector.");
			}
		}
		template<std::size_t Size_, typename RhsVector, template<class> class Func_>
		constexpr EmuMath::TMPHelpers::emu_vector_from_size_t<Size_, bool> _perform_scalar_comparison_std(const RhsVector& rhs) const
		{
			using OutVector = EmuMath::TMPHelpers::emu_vector_from_size_t<Size_, bool>;
			using Func = Func_<nonref_value_type>;
			Func func = Func();
			if constexpr (Size_ == 2)
			{
				return OutVector
				(
					func(x, rhs),
					func(y, rhs)
				);
			}
			else if constexpr (Size_ == 3)
			{
				return OutVector
				(
					func(x, rhs),
					func(y, rhs),
					func(info_type::value_zero, rhs)
				);
			}
			else if constexpr (Size_ == 4)
			{
				return OutVector
				(
					func(x, rhs.x),
					func(y, rhs.y),
					func(info_type::value_zero, rhs),
					func(info_type::value_zero, rhs)
				);
			}
			else
			{
				static_assert(false, "Attempted to perform a per-element comparison on an EmuMath::Vector2 with an unsupported size of output Vector.");
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