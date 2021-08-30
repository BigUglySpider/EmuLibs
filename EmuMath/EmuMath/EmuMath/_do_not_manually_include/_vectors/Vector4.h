#ifndef EMU_MATH_VECTOR_4_SUGAR_H_INC_
#define EMU_MATH_VECTOR_4_SUGAR_H_INC_ 1

#include "VectorT.h"

namespace EmuMath
{
	template<typename T_>
	struct Vector<4, T_>
	{
#pragma region VECTOR_INFO
		/// <summary>
		/// <para> General template info regarding this type of EmuMath vector. </para>
		/// <para> For further information on individual components within this vector, you should view components of the same name under this vector_info. </para>
		/// </summary>
		using vector_info = EmuMath::_underlying_components::VectorInfo<4, T_>;
		using contained_type = typename vector_info::contained_type;
		static constexpr bool contains_reference_wrappers = vector_info::contains_reference_wrappers;
		using raw_value_type = typename vector_info::raw_value_type;
		using value_type = typename vector_info::value_type;
		using preferred_floating_point = typename vector_info::preferred_floating_point;

		static constexpr std::size_t size = vector_info::size;
		static constexpr bool contains_const_reference_wrappers = vector_info::contains_const_reference_wrappers;
		static constexpr bool contains_non_const_reference_wrappers = vector_info::contains_non_const_reference_wrappers;
		static constexpr bool has_integral_elements = vector_info::has_integral_elements;
		static constexpr bool has_floating_point_elements = vector_info::has_floating_point_elements;

		/// <summary> This vector's instantiated type. </summary>
		using this_type = Vector<size, contained_type>;
		/// <summary> The type used to contain a copy of this vector. Same size of this vector, instantiated with its value_type. </summary>
		using copy_type = Vector<size, value_type>;
#pragma endregion

#pragma region CONSTRUCTORS
		constexpr Vector() : x(), y(), z(), w()
		{
		}
		constexpr Vector(this_type& toCopy_) : x(toCopy_.at<0>()), y(toCopy_.at<1>()), z(toCopy_.at<2>()), w(toCopy_.at<3>())
		{
		}
		constexpr Vector(const this_type& toCopy_) : x(toCopy_.at<0>()), y(toCopy_.at<1>()), z(toCopy_.at<2>()), w(toCopy_.at<3>())
		{
		}
		template<std::size_t ToCopySize_, typename ToCopyValueType_>
		constexpr Vector(const EmuMath::Vector<ToCopySize_, ToCopyValueType_>& toCopy_) : Vector()
		{
			EmuMath::Helpers::VectorSet(*this, toCopy_);
		}
		template<std::size_t ToCopySize_, typename ToCopyValueType_>
		constexpr Vector(EmuMath::Vector<ToCopySize_, ToCopyValueType_>& toCopy_) : Vector()
		{
			EmuMath::Helpers::VectorSet(*this, toCopy_);
		}
		constexpr Vector(const contained_type* pDataToLoad, std::size_t numBytes_) : Vector()
		{
			memcpy(data(), pDataToLoad, numBytes_);
		}
		template<typename X_, typename Y_, typename Z_, typename W_>
		constexpr Vector(X_&& x_, Y_&& y_, Z_&& z_, W_&& w_) :
			x(static_cast<contained_type>(std::forward<X_>(x_))),
			y(static_cast<contained_type>(std::forward<Y_>(y_))),
			z(static_cast<contained_type>(std::forward<Z_>(z_))),
			w(static_cast<contained_type>(std::forward<W_>(w_)))
		{
			static_assert
			(
				EmuCore::TMPHelpers::are_all_comparisons_true<std::is_constructible, contained_type, X_, Y_, Z_, W_>::value,
				"Attempted to construct an EmuMath Vector via it's template constructor, but at least one provided argument cannot be used to construct the Vector's contained_type."
			);
		}
#pragma endregion

#pragma region RANDOM_ACCESS
		template<std::size_t Index_>
		[[nodiscard]] constexpr inline raw_value_type& at()
		{
			return _get_index<Index_>();
		}
		template<std::size_t Index_>
		[[nodiscard]] constexpr inline const raw_value_type& at() const
		{
			return _get_index<Index_>();
		}
		[[nodiscard]] constexpr inline raw_value_type& at(const std::size_t index_)
		{
			return _get_index(index_);
		}
		[[nodiscard]] constexpr inline const raw_value_type& at(const std::size_t index_) const
		{
			return _get_index(index_);
		}
		[[nodiscard]] constexpr inline raw_value_type& operator[](const std::size_t index_)
		{
			return _get_index(index_);
		}
		[[nodiscard]] constexpr inline const raw_value_type& operator[](const std::size_t index_) const
		{
			return _get_index(index_);
		}

		/// <summary> Provides a pointer to the start of this vector's data (i.e. the memory location of the start of element 0). </summary>
		[[nodiscard]] constexpr inline contained_type* data()
		{
			return &x;
		}
		/// <summary> Provides a constant pointer to the start of this vector's data (i.e. the memory location of the start of element 0). </summary>
		[[nodiscard]] constexpr inline const contained_type* data() const
		{
			return &x;
		}
#pragma endregion

#pragma region SETS
		template<std::size_t Index_, typename In_>
		constexpr inline void Set(In_& in_)
		{
			_set_data_at_index<Index_, In_>(in_);
		}
		template<typename In_>
		constexpr inline void Set(In_& in_, const std::size_t index_)
		{
			_set_data_at_index<In_>(in_, index_);
		}

		template<class ToCopy_>
		constexpr inline this_type& Copy(const ToCopy_& toCopy_)
		{
			return EmuMath::Helpers::VectorCopy<this_type, ToCopy_>(*this, toCopy_);
		}

		template<typename In_>
		constexpr inline void Set(In_& in_)
		{
			EmuMath::Helpers::VectorSet<this_type, In_>(*this, in_);
		}
		template<typename In_>
		constexpr inline void Set(const In_& in_)
		{
			EmuMath::Helpers::VectorSet<this_type, const In_>(*this, in_);
		}

#pragma endregion

#pragma region CONST_OPERATORS
		template<class Rhs_>
		constexpr inline bool operator==(const Rhs_& rhs_) const
		{
			return EmuMath::Helpers::VectorCmpEqualTo(*this, rhs_);
		}

		template<class Rhs_>
		constexpr inline bool operator!=(const Rhs_& rhs_) const
		{
			return EmuMath::Helpers::VectorCmpNotEqualTo(*this, rhs_);
		}

		template<class Rhs_>
		constexpr inline bool operator>(const Rhs_& rhs_) const
		{
			return EmuMath::Helpers::VectorCmpGreater(*this, rhs_);
		}

		template<class Rhs_>
		constexpr inline bool operator<(const Rhs_& rhs_) const
		{
			return EmuMath::Helpers::VectorCmpLess(*this, rhs_);
		}

		template<class Rhs_>
		constexpr inline bool operator>=(const Rhs_& rhs_) const
		{
			return EmuMath::Helpers::VectorCmpGreaterEqual(*this, rhs_);
		}

		template<class Rhs_>
		constexpr inline bool operator<=(const Rhs_& rhs_) const
		{
			return EmuMath::Helpers::VectorCmpLessEqual(*this, rhs_);
		}

		template<class RhsVector_>
		constexpr inline copy_type operator+(const RhsVector_& rhs_) const
		{
			return EmuMath::Helpers::VectorAdd<copy_type::size, typename copy_type::contained_type>(*this, rhs_);
		}
		constexpr inline copy_type operator+() const
		{
			return copy_type(*this);
		}

		template<class RhsVector_>
		constexpr inline copy_type operator-(const RhsVector_& rhs_) const
		{
			return EmuMath::Helpers::VectorSubtract<copy_type::size, typename copy_type::contained_type>(*this, rhs_);
		}
		constexpr inline copy_type operator-() const
		{
			return EmuMath::Helpers::VectorNegate<copy_type::size, typename copy_type::contained_type>(*this);
		}

		template<typename Rhs_>
		constexpr inline copy_type operator*(const Rhs_& rhs_) const
		{
			return EmuMath::Helpers::VectorMultiply<copy_type::size, typename copy_type::contained_type>(*this, rhs_);
		}

		template<typename Rhs_>
		constexpr inline copy_type operator/(const Rhs_& rhs_) const
		{
			return EmuMath::Helpers::VectorDivide<copy_type::size, typename copy_type::contained_type>(*this, rhs_);
		}

		template<typename Rhs_>
		[[nodiscard]] constexpr inline copy_type operator%(const Rhs_& rhs_) const
		{
			return EmuMath::Helpers::VectorMod<copy_type::size, typename copy_type::contained_type, this_type, Rhs_>(*this, rhs_);
		}

		template<typename Rhs_>
		constexpr inline copy_type operator&(const Rhs_& rhs_) const
		{
			return EmuMath::Helpers::VectorAnd<copy_type::size, typename copy_type::contained_type>(*this, rhs_);
		}

		template<typename Rhs_>
		constexpr inline copy_type operator|(const Rhs_& rhs_) const
		{
			return EmuMath::Helpers::VectorOr<copy_type::size, typename copy_type::contained_type>(*this, rhs_);
		}

		template<typename Rhs_>
		constexpr inline copy_type operator^(const Rhs_& rhs_) const
		{
			return EmuMath::Helpers::VectorXor<copy_type::size, typename copy_type::contained_type>(*this, rhs_);
		}

		constexpr inline copy_type operator~() const
		{
			return EmuMath::Helpers::VectorNot<copy_type::size, typename copy_type::contained_type>(*this);
		}

		template<typename Rhs_>
		constexpr inline copy_type operator<<(const Rhs_& rhs_) const
		{
			return EmuMath::Helpers::VectorShiftLeft<copy_type::size, typename copy_type::contained_type>(*this, rhs_);
		}

		template<typename Rhs_>
		constexpr inline copy_type operator>>(const Rhs_& rhs_) const
		{
			return EmuMath::Helpers::VectorShiftRight<copy_type::size, typename copy_type::contained_type>(*this, rhs_);
		}
#pragma endregion

#pragma region NON_CONST_OPERATORS
		template<class ToCopy_>
		constexpr inline this_type& operator=(const ToCopy_& toCopy_)
		{
			if constexpr (!vector_info::has_const_values)
			{
				return EmuMath::Helpers::VectorCopy(*this, toCopy_);
			}
			else
			{
				static_assert(false, "Attempted to set the data of an EmuMath vector which contains constant values via operator=.");
			}
		}

		template<class RhsVector_>
		constexpr inline this_type& operator+=(const RhsVector_& rhs_)
		{
			if constexpr (!vector_info::has_const_values)
			{
				(*this) = EmuMath::Helpers::VectorAdd(*this, rhs_);
				return *this;
			}
			else
			{
				static_assert(false, "Attempted to set the data of an EmuMath vector which contains constant values via operator+=.");
			}
		}

		template<class RhsVector_>
		constexpr inline this_type& operator-=(const RhsVector_& rhs_)
		{
			if constexpr (!vector_info::has_const_values)
			{
				(*this) = EmuMath::Helpers::VectorSubtract(*this, rhs_);
				return *this;
			}
			else
			{
				static_assert(false, "Attempted to set the data of an EmuMath vector which contains constant values via operator-=.");
			}
		}

		template<class Rhs_>
		constexpr inline this_type& operator*=(const Rhs_& rhs_)
		{
			if constexpr (!vector_info::has_const_values)
			{
				(*this) = EmuMath::Helpers::VectorMultiply(*this, rhs_);
				return *this;
			}
			else
			{
				static_assert(false, "Attempted to set the data of an EmuMath vector which contains constant values via operator*=.");
			}
		}

		template<class Rhs_>
		constexpr inline this_type& operator/=(const Rhs_& rhs_)
		{
			if constexpr (!vector_info::has_const_values)
			{
				(*this) = EmuMath::Helpers::VectorDivide(*this, rhs_);
				return *this;
			}
			else
			{
				static_assert(false, "Attempted to set the data of an EmuMath vector which contains constant values via operator/=.");
			}
		}

		template<class Rhs_>
		constexpr inline this_type& operator%=(const Rhs_& rhs_)
		{
			if constexpr (!vector_info::has_const_values)
			{
				(*this) = EmuMath::Helpers::VectorMod(*this, rhs_);
				return *this;
			}
			else
			{
				static_assert(false, "Attempted to set the data of an EmuMath vector which contains constant values via operator%=.");
			}
		}

		template<class Rhs_>
		constexpr inline this_type& operator&=(const Rhs_& rhs_)
		{
			if constexpr (!vector_info::has_const_values)
			{
				(*this) = EmuMath::Helpers::VectorAnd(*this, rhs_);
				return *this;
			}
			else
			{
				static_assert(false, "Attempted to set the data of an EmuMath vector which contains constant values via operator&=.");
			}
		}

		template<class Rhs_>
		constexpr inline this_type& operator|=(const Rhs_& rhs_)
		{
			if constexpr (!vector_info::has_const_values)
			{
				(*this) = EmuMath::Helpers::VectorOr(*this, rhs_);
				return *this;
			}
			else
			{
				static_assert(false, "Attempted to set the data of an EmuMath vector which contains constant values via operator|=.");
			}
		}

		template<class Rhs_>
		constexpr inline this_type& operator^=(const Rhs_& rhs_)
		{
			if constexpr (!vector_info::has_const_values)
			{
				(*this) = EmuMath::Helpers::VectorXor(*this, rhs_);
				return *this;
			}
			else
			{
				static_assert(false, "Attempted to set the data of an EmuMath vector which contains constant values via operator^=.");
			}
		}

		template<class Rhs_>
		constexpr inline this_type& operator<<=(const Rhs_& rhs_)
		{
			if constexpr (!vector_info::has_const_values)
			{
				(*this) = EmuMath::Helpers::VectorShiftLeft(*this, rhs_);
				return *this;
			}
			else
			{
				static_assert(false, "Attempted to set the data of an EmuMath vector which contains constant values via operator<<=.");
			}
		}

		template<class Rhs_>
		constexpr inline this_type& operator>>=(const Rhs_& rhs_)
		{
			if constexpr (!vector_info::has_const_values)
			{
				(*this) = EmuMath::Helpers::VectorShiftLeft(*this, rhs_);
				return *this;
			}
			else
			{
				static_assert(false, "Attempted to set the data of an EmuMath vector which contains constant values via operator>>=.");
			}
		}
#pragma endregion

#pragma region PERMUTATIONS
		template<std::size_t X_, std::size_t...RemainingShuffleIndices_>
		constexpr EmuMath::Vector<sizeof...(RemainingShuffleIndices_) + 1, value_type> Shuffle() const
		{
			return EmuMath::Helpers::VectorShuffle<value_type, X_, RemainingShuffleIndices_...>(*this);
		}
		template<typename out_contained_type, std::size_t X_, std::size_t...RemainingShuffleIndices_>
		constexpr EmuMath::Vector<sizeof...(RemainingShuffleIndices_) + 1, out_contained_type> Shuffle() const
		{
			return EmuMath::Helpers::VectorShuffle<out_contained_type, X_, RemainingShuffleIndices_...>(*this);
		}

		template<std::size_t X_, std::size_t...RemainingShuffleIndices_>
		[[nodiscard]] constexpr inline EmuMath::ConstRefVector<sizeof...(RemainingShuffleIndices_) + 1, value_type> ShuffledConstReference() const
		{
			return EmuMath::Helpers::VectorShuffledConstReference<X_, RemainingShuffleIndices_...>(*this);
		}

		template<std::size_t X_, std::size_t...RemainingShuffleIndices_>
		[[nodiscard]] constexpr inline EmuMath::RefVector<sizeof...(RemainingShuffleIndices_) + 1, value_type> ShuffledReference()
		{
			return EmuMath::Helpers::VectorShuffledReference<X_, RemainingShuffleIndices_...>(*this);
		}
		template<std::size_t X_, std::size_t...RemainingShuffleIndices_>
		[[nodiscard]] constexpr inline EmuMath::ConstRefVector<sizeof...(RemainingShuffleIndices_) + 1, value_type> ShuffledReference() const
		{
			return EmuMath::Helpers::VectorShuffledReference<X_, RemainingShuffleIndices_...>(*this);
		}
#pragma endregion

#pragma region ARITHMETIC
		/// <summary> Returns the result of adding the passed rhs_ vector to this vector. </summary>
		/// <typeparam name="out_contained_type">Type to be contained in the result vector.</typeparam>
		/// <typeparam name="RhsVector_">Type of the passed vector to add.</typeparam>
		/// <param name="rhs_">EmuMath vector to add to this vector.</param>
		/// <returns>Vector containing the results of adding the passed vector to this vector.</returns>
		template<std::size_t OutSize_ = size, typename out_contained_type = value_type, class RhsVector_>
		[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, out_contained_type> Add(const RhsVector_& rhs_) const
		{
			return EmuMath::Helpers::VectorAdd<OutSize_, out_contained_type, this_type, RhsVector_>(*this, rhs_);
		}

		/// <summary> Returns the result of subtracting the passed rhs_ vector from this vector. </summary>
		/// <typeparam name="out_contained_type">Type to be contained in the result vector.</typeparam>
		/// <typeparam name="RhsVector_">Type of the passed vector to subtract.</typeparam>
		/// <param name="rhs_">EmuMath vector to subtract from this vector.</param>
		/// <returns>Vector containing the results of subtracting the passed vector from this vector.</returns>
		template<std::size_t OutSize_ = size, typename out_contained_type = value_type, class RhsVector_>
		[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, out_contained_type> Subtract(const RhsVector_& rhs_) const
		{
			return EmuMath::Helpers::VectorSubtract<OutSize_, out_contained_type, this_type, RhsVector_>(*this, rhs_);
		}

		/// <summary> Returns the result of multiplying this vector by the passed rhs_ argument. </summary>
		/// <typeparam name="out_contained_type">Type to be contained in the result vector.</typeparam>
		/// <typeparam name="RhsVector_">Type to be multiplying by..</typeparam>
		/// <param name="rhs_">EmuMath vector or scalar to multiply this vector by.</param>
		/// <returns>Vector containing the results of multiplying this vector by the passed rhs_ argument.</returns>
		template<std::size_t OutSize_ = size, typename out_contained_type = value_type, class Rhs_>
		[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, out_contained_type> Multiply(const Rhs_& rhs_) const
		{
			return EmuMath::Helpers::VectorMultiply<OutSize_, out_contained_type, this_type, Rhs_>(*this, rhs_);
		}

		/// <summary> Returns the result of dividing this vector by the passed rhs_ argument. </summary>
		/// <typeparam name="out_contained_type">Type to be contained in the result vector.</typeparam>
		/// <typeparam name="RhsVector_">Type to be dividing by.</typeparam>
		/// <param name="rhs_">EmuMath vector or scalar to divide this vector by.</param>
		/// <returns>Vector containing the results of dividing this vector by the passed rhs_ argument.</returns>
		template<std::size_t OutSize_ = size, typename out_contained_type = value_type, class Rhs_>
		[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, out_contained_type> Divide(const Rhs_& rhs_) const
		{
			return EmuMath::Helpers::VectorDivide<OutSize_, out_contained_type, this_type, Rhs_>(*this, rhs_);
		}

		/// <summary> Returns the result of modulo division of this vector by the passed rhs_ argument. </summary>
		/// <typeparam name="out_contained_type">Type to be contained in the result vector.</typeparam>
		/// <typeparam name="RhsVector_">Type to be dividing by.</typeparam>
		/// <param name="rhs_">EmuMath vector or scalar to perform modulo division on this vector by.</param>
		/// <returns>Vector containing the results of modulo division on this vector by the passed rhs_ argument..</returns>
		template<std::size_t OutSize_ = size, typename out_contained_type = value_type, class Rhs_>
		[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, out_contained_type> Mod(const Rhs_& rhs_) const
		{
			return EmuMath::Helpers::VectorMod<OutSize_, out_contained_type, this_type, Rhs_>(*this, rhs_);
		}

		/// <summary> Returns a negated form of this vector (i.e. one where each element is the negative of this vector's element at the respective index). </summary>
		/// <typeparam name="out_contained_type">Type to be contained in the output vector.</typeparam>
		/// <returns>Negated form of this vector.</returns>
		template<std::size_t OutSize_ = size, typename out_contained_type = value_type>
		[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, out_contained_type> Negate() const
		{
			return EmuMath::Helpers::VectorNegate<OutSize_, out_contained_type, this_type>(*this);
		}
#pragma endregion

#pragma region VECTOR_OPERATIONS
		/// <summary> Calculates the product of all elements within this vector and outputs the result as the provided OutT_, defaulting to this vector's value_type. </summary>
		/// <typeparam name="OutT_">Type to output the product as.</typeparam>
		/// <returns>Product of all elements within this vector.</returns>
		template<typename OutT_ = value_type>
		[[nodiscard]] constexpr inline OutT_ TotalProduct() const
		{
			return EmuMath::Helpers::VectorElementProduct<OutT_, this_type>(*this);
		}
		/// <summary> Calculates the sum of all elements within this vector and outputs the result as the provided OutT_, defaulting to this vector's value_type. </summary>
		/// <typeparam name="OutT_">Type to output the sum as.</typeparam>
		/// <returns>Sum of all elements within this vector.</returns>
		template<typename OutT_ = value_type>
		[[nodiscard]] constexpr inline OutT_ TotalSum() const
		{
			return EmuMath::Helpers::VectorElementSum<OutT_, this_type>(*this);
		}

		/// <summary>
		///		Calculates the dot product between this vector and EmuMath vector b_. 
		///		The dot product will be output as the provided OutT_, which defaults to this vector's preferred_floating_point.
		/// </summary>
		/// <typeparam name="OutT_">Type to output the dot product as.</typeparam>
		/// <typeparam name="VectorB_">Type of EmuMath vector passed as argument b_.</typeparam>
		/// <param name="b_">EmuMath vector to calculate the dot product of with this vector.</param>
		/// <returns>Dot product of this vector and vector b_.</returns>
		template<typename OutT_ = preferred_floating_point, class VectorB_>
		[[nodiscard]] constexpr inline OutT_ DotProduct(const VectorB_& b_) const
		{
			return EmuMath::Helpers::VectorDotProduct<OutT_, this_type, VectorB_>(*this, b_);
		}

		/// <summary>
		/// Calculates the square magnitude of this vector and outputs it as the provided OutT_, which defaults to this vector's preferred_floating_point.
		/// </summary>
		/// <typeparam name="OutT_"><Type to output this vector's square magnitude as./typeparam>
		/// <returns>Square magnitude of this vector.</returns>
		template<typename OutT_ = preferred_floating_point>
		[[nodiscard]] constexpr inline OutT_ SquareMagnitude() const
		{
			return EmuMath::Helpers::VectorSquareMagnitude<OutT_, this_type>(*this);
		}

		/// <summary>
		/// <para> Calculates the magnitude of this vector and outputs it as the provided OutT_, which defaults to this vector's preferred_floating_point. </para>
		/// <para> This function may make sacrifices to be evaluable at compile time. If it is being called at runtime, it is recommended to call Magnitude instead. </para>
		/// </summary>
		/// <typeparam name="OutT_">Type to output this vector's magnitude as.</typeparam>
		/// <returns>Magnitude of this vector.</returns>
		template<typename OutT_ = preferred_floating_point>
		[[nodiscard]] constexpr inline OutT_ MagnitudeConstexpr() const
		{
			return EmuMath::Helpers::VectorMagnitudeConstexpr<OutT_, this_type>(*this);
		}

		/// <summary>
		/// <para> Calculates the magnitude of this vector and outputs it as the provided OutT_, which defaults to this vector's preferred_floating_point. </para>
		/// </summary>
		/// <typeparam name="OutT_">Type to output this vector's magnitude as.</typeparam>
		/// <returns>Magnitude of this vector.</returns>
		template<typename OutT_ = preferred_floating_point>
		[[nodiscard]] inline OutT_ Magnitude() const
		{
			return EmuMath::Helpers::VectorMagnitude<OutT_, this_type>(*this);
		}

		/// <summary>
		/// <para> Calculates the reciprocal to this vector's magnitude (i.e. the number that may be multiplied by to achieve the same effect as dividing by magnitude). </para>
		/// <para> This is output as the provided OutFloatingPoint_, which must be a floating-point type. It defaults to this vector's preferred_floating_point. </para>
		/// <para> 
		///		This function may make sacrifices to be evaluable at compile time. 
		///		If it is being called at runtime, it is recommended to call MagnitudeReciprocal or MagnitudeReciprocalQrsqrt instead.
		/// </para>
		/// </summary>
		/// <typeparam name="OutFloatingPoint_">Type to output this vector's magnitude reciprocal as. Must be a floating-point type.</typeparam>
		/// <returns>Reciprocal to this vector's magnitude.</returns>
		template<typename OutFloatingPoint_ = preferred_floating_point>
		[[nodiscard]] constexpr inline OutFloatingPoint_ MagnitudeReciprocalConstexpr() const
		{
			return EmuMath::Helpers::VectorMagnitudeReciprocalConstexpr<OutFloatingPoint_, this_type>(*this);
		}

		/// <summary>
		/// <para> Calculates the reciprocal to this vector's magnitude (i.e. the number that may be multiplied by to achieve the same effect as dividing by magnitude). </para>
		/// <para> This is output as the provided OutFloatingPoint_, which must be a floating-point type. It defaults to this vector's preferred_floating_point. </para>
		/// </summary>
		/// <typeparam name="OutFloatingPoint_">Type to output this vector's magnitude reciprocal as. Must be a floating-point type.</typeparam>
		/// <returns>Reciprocal to this vector's magnitude.</returns>
		template<typename OutFloatingPoint_ = preferred_floating_point>
		[[nodiscard]] inline OutFloatingPoint_ MagnitudeReciprocal() const
		{
			return EmuMath::Helpers::VectorMagnitudeReciprocal<OutFloatingPoint_, this_type>(*this);
		}

		/// <summary>
		/// <para>
		///		Calculates the reciprocal to this vector's magnitude (i.e. the number that may be multiplied by to achieve the same effect as dividing by magnitude),
		///		using the Q_rsqrt method.
		/// </para>
		/// <para> A custom number of newton iterations may be provided to increase accuracy. Additionally, the magic constant may also be changed from 0x5F3759DF. </para>
		/// </summary>
		/// <typeparam name="OutFloatingPoint_">Type to output the magnitude reciprocal as.</typeparam>
		/// <typeparam name="Vector_">Type of vector to find the reciprocal to the magnitude of.</typeparam>
		/// <param name="vector_">EmuMath vector to find the reciprocal to the magnitude of.</param>
		/// <returns>Reciprocal to the passed EmuMath vector's magnitude, represented as the provided OutFloatingPoint_ type.</returns>
		template<typename OutFloatingPoint_ = preferred_floating_point, std::size_t NumNewtonIterations_ = 1, std::int32_t MagicConstant_ = 0x5F3759DF>
		[[nodiscard]] inline OutFloatingPoint_ MagnitudeReciprocalQrsqrt() const
		{
			return EmuMath::Helpers::VectorMagnitudeReciprocalQrsqrt<OutFloatingPoint_, NumNewtonIterations_, MagicConstant_, this_type>(*this);
		}

		/// <summary> Returns a copy of the lowest value within this vector, represented as the provided OutT_ (which defaults to this vector's value_type). </summary>
		/// <typeparam name="OutT_">Type to output the lowest value as.</typeparam>
		/// <returns>Lowest value contained within this vector.</returns>
		template<typename OutT_ = value_type>
		[[nodiscard]] constexpr inline OutT_ Min() const
		{
			return EmuMath::Helpers::VectorMin<OutT_, this_type>(*this);
		}

		/// <summary> Returns a copy of the greatest value within this vector, represented as the provided OutT_ (which defaults to this vector's value_type). </summary>
		/// <typeparam name="OutT_">Type to output the greatest value as.</typeparam>
		/// <returns>Greater value contained within this vector.</returns>
		template<typename OutT_ = value_type>
		[[nodiscard]] constexpr inline OutT_ Max() const
		{
			return EmuMath::Helpers::VectorMax<OutT_, this_type>(*this);
		}

		/// <summary>
		/// <para> Returns a two-dimensional EmuMath vector containing copies of this vector's lowest and highest values, in indices 0 and 1 respectively. </para>
		/// <para> The output vector's contained type is determined by the provided OutT_, which defaults to this vector's value_type. </para>
		/// </summary>
		/// <typeparam name="OutT_">Type to output the lowest and greatest values as.</typeparam>
		/// <returns>EmuMath two-dimensional vector containing with this vector's lowest value in index 0, and its highest value in index 1.</returns>
		template<typename OutT_ = value_type>
		[[nodiscard]] constexpr inline EmuMath::Vector<2, OutT_> MinMax() const
		{
			return EmuMath::Helpers::VectorMinMax<OutT_, this_type>(*this);
		}
		/// <summary> Finds the lowest and greatest values within this vector and outputs them via the passed min_ and max_ references, respectively. </summary>
		/// <typeparam name="OutMin_">Type to output this vector's lowest value to.</typeparam>
		/// <typeparam name="OutMax_">Type to output this vector's greatest value to.</typeparam>
		/// <param name="min_">Reference to output this vector's lowest value to.</param>
		/// <param name="max_">Reference to output this vector's greatest value to.</param>
		template<typename OutMin_, typename OutMax_>
		constexpr inline void MinMax(OutMin_& min_, OutMax_& max_) const
		{
			return EmuMath::Helpers::VectorMinMax<OutMin_, OutMax_, this_type>(*this, min_, max_);
		}

		/// <summary> Returns a vector containing copies of values stored at the respective indices of this vector or b_, whichever contains the lowest value. </summary>
		/// <typeparam name="out_contained_type">Type to be contained within the output vector.</typeparam>
		/// <typeparam name="B_">Type to compare the elements of this vector to.</typeparam>
		/// <param name="b_">EmuMath vector or scalar to compare the elements of this vector to.</param>
		/// <returns>Vector containing the lowest values in respective indices between this vector and b_.</returns>
		template<std::size_t OutSize_ = size, typename out_contained_type = value_type, class B_>
		[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, out_contained_type> MinVector(const B_& b_) const
		{
			return EmuMath::Helpers::VectorMinVector<OutSize_, out_contained_type, this_type, B_>(*this, b_);
		}

		/// <summary> Returns a vector containing copies of values stored at the respective indices of this vector or b_, whichever contains the greatest value. </summary>
		/// <typeparam name="out_contained_type">Type to be contained within the output vector.</typeparam>
		/// <typeparam name="B_">Type to compare the elements of this vector to.</typeparam>
		/// <param name="b_">EmuMath vector or scalar to compare the elements of this vector to.</param>
		/// <returns>Vector containing the greatest values in respective indices between this vector and b_.</returns>
		template<std::size_t OutSize_ = size, typename out_contained_type = value_type, class B_>
		[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, out_contained_type> MaxVector(const B_& b_) const
		{
			return EmuMath::Helpers::VectorMaxVector<OutSize_, out_contained_type, this_type, B_>(*this, b_);
		}

		/// <summary>
		/// <para> Returns a vector containing copies of values stored at the respective indices of this vector or b_, whichever contains the lowest/greatest value. </para>
		/// <para>
		///		Boolean arguments are taken on a per-index basis.
		///		Each respective argument determines if a copied value is the lowest (true) or greatest (false) of this vector and b_.
		/// </para>
		/// <para> Additionally, the size of the output vector is determined by the provided number of boolean arguments. </para>
		/// <para> E.g. MinMaxVector&lt;false, true, true&gt;(b_) would result in a vector [Max(this[0], b_[0]), Min(this[1], b_[1]), Min(this[2], b_[2])]. </para>
		/// </summary>
		/// <typeparam name="out_contained_type">Type to be contained in the output vector.</typeparam>
		/// <typeparam name="B_">Type to compare the elements of this vector to.</typeparam>
		/// <param name="b_">EmuMath vector or scalar to compare the elements of this vector to.</param>
		/// <returns>Vector containing the lowest or greatest values in respective indices between this vector and b_, depending on provided boolean template arguments.</returns>
		template<typename out_contained_type, bool Min0_, bool...OtherMins_, class B_>
		constexpr inline EmuMath::Vector<sizeof...(OtherMins_) + 1, out_contained_type> MinMaxVector(const B_& b_) const
		{
			return EmuMath::Helpers::VectorMinMaxVector<out_contained_type, Min0_, OtherMins_...>(*this, b_);
		}
		template<bool Min0_, bool...OtherMins_, class B_>
		constexpr inline EmuMath::Vector<sizeof...(OtherMins_) + 1, value_type> MinMaxVector(const B_& b_) const
		{
			return EmuMath::Helpers::VectorMinMaxVector<value_type, Min0_, OtherMins_...>(*this, b_);
		}

		/// <summary> Finds the index of the lowest value within this vector. </summary>
		/// <returns>Index of the lowest value within this vector.</returns>
		[[nodiscard]] constexpr inline std::size_t MinIndex() const
		{
			return EmuMath::Helpers::VectorMinIndex<this_type>(*this);
		}

		/// <summary> Finds the index of the greatest value within this vector. </summary>
		/// <returns>Index of the greatest value within this vector.</returns>
		[[nodiscard]] constexpr inline std::size_t MaxIndex() const
		{
			return EmuMath::Helpers::VectorMaxIndex<this_type>(*this);
		}

		/// <summary>
		///		Finds the indices of the lowest and greatest values within this vector and outputs them in a two-dimensional EmuMath vector,
		///		at indices 0 and 1 respectively.
		/// </summary>
		/// <returns>Two-dimensional EmuMath vector containing the idnex of the lowest value in this matrix at index 0, and the index of the greatest value at index 1.</returns>
		[[nodiscard]] constexpr inline EmuMath::Vector<2, std::size_t> MinMaxIndices() const
		{
			return EmuMath::Helpers::VectorMinMaxIndices<this_type>(*this);
		}
		/// <summary> Finds the lowest and greatest values within this vector and outputs their indices via the passed min_ and max_ references, respectively. </summary>
		/// <param name="minIndex_">Reference to output the lowest value's index to.</param>
		/// <param name="maxIndex_">Reference to output the greatest value's index to.</param>
		[[nodiscard]] constexpr inline void MinMaxIndices(std::size_t& minIndex_, std::size_t& maxIndex_) const
		{
			return EmuMath::Helpers::VectorMinMaxIndices<this_type>(*this, minIndex_, maxIndex_);
		}

		/// <summary>
		/// <para> Calculates the resulting vector from linearly interpolating this vector with the passed operands. </para>
		/// <para> Where this vector is represented as a, the resulting vector from this operation can be summarised as "a_ + ((b_ - a_) * t_)". </para>
		/// <para>
		///		B_ may be either a vector or a scalar. If it is a vector, all of this vector's elements will be interpolated with their respective elements in b_. 
		///		Otherwise, all elements will be interpolated with the value of b_.
		/// </para>
		/// <para>
		///		T_ may be either a vector or a scalar. If it is a vector, all linear interpolations will be weighted by the value in the respective element in t_. 
		///		Otherwise, all linear interpolations will be weighted by the value of t_.
		/// </para>
		/// <para> A custom output size may be provided, which defaults to this vector's size. </para>
		/// <para> A custom output type may be provided, which defaults to this vector's preferred_floating_point. </para>
		/// </summary>
		/// <typeparam name="out_contained_type">Type to be contained in the output vector.</typeparam>
		/// <typeparam name="B_">Type of b in the equation a + ((b - a) * t).</typeparam>
		/// <typeparam name="T_">Type of t in the equation a + ((b - a) * t).</typeparam>
		/// <param name="b_">EmuMath vector or scalar that acts as b in the equation a + ((b - a) * t), where this vector is a.</param>
		/// <param name="t_">EmuMath vector or scalar that acts as t in the equation a + ((b - a) * t), where this vector is a.</param>
		/// <returns>Vector containing the result of linear interpolation of this vector with the provided arguments.</returns>
		template<std::size_t OutSize_ = size, typename out_contained_type = preferred_floating_point, class B_, typename T_>
		[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, out_contained_type> Lerp(const B_& b_, const T_& t_) const
		{
			return EmuMath::Helpers::VectorLerp<OutSize_, out_contained_type, this_type, B_, T_>(*this, b_, t_);
		}

		/// <summary>
		/// <para> Calculates the reciprocal of each element in this vector and outputs a vector containing said reciprocals. </para>
		/// <para>
		///		The output vector will contain the provided out_floating_point_contained_type, which must be a floating-point type 
		///		and defaults to this vector's preferred_floating_point.
		/// </para>
		/// </summary>
		/// <typeparam name="out_floating_point_contained_type">Floating-point type to be contained in the output vector.</typeparam>
		/// <returns>EmuMath vector containing the reciprocals of elements in respective indices within this vector.</returns>
		template<std::size_t OutSize_ = size, typename out_floating_point_contained_type = preferred_floating_point>
		[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, out_floating_point_contained_type> Reciprocal() const
		{
			return EmuMath::Helpers::VectorReciprocal<OutSize_, out_floating_point_contained_type, this_type>(*this);
		}

		/// <summary>
		/// <para> Clamps the elements of this vector so that no values evaluate as less than the provided min_. </para>
		/// <para> 
		///		If min_ is an EmuMath vector, elements will be clamped to a minimum of the respective elements in the min_ vector. 
		///		Otherwise, all elements will be clamped to a minimum of the value of min_.
		/// </para>
		/// </summary>
		/// <typeparam name="out_contained_type">Type to contain within the output clamped vector.</typeparam>
		/// <typeparam name="Min_">Type used for the provided minimum value.</typeparam>
		/// <param name="min_">Minimum value that any element within this vector may be.</param>
		/// <returns>Copy of this vector with its elements clamped to the provided min_.</returns>
		template<std::size_t OutSize_ = size, typename out_contained_type = value_type, class Min_>
		[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, out_contained_type> ClampMin(const Min_& min_) const
		{
			return EmuMath::Helpers::VectorClampMin<OutSize_, out_contained_type, this_type, Min_>(*this, min_);
		}

		/// <summary>
		/// <para> Clamps the elements of this vector so that no values evaluate as greater than the provided max_. </para>
		/// <para> 
		///		If max_ is an EmuMath vector, elements will be clamped to a maximum of the respective elements in the max_ vector. 
		///		Otherwise, all elements will be clamped to a maximum of the value of max_.
		/// </para>
		/// </summary>
		/// <typeparam name="out_contained_type">Type to contain within the output clamped vector.</typeparam>
		/// <typeparam name="Max_">Type used for the provided maximum value.</typeparam>
		/// <param name="max_">Maximum value that any element within this vector may be.</param>
		/// <returns>Copy of this vector with its elements clamped to the provided max_.</returns>
		template<std::size_t OutSize_ = size, typename out_contained_type = value_type, class Max_>
		[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, out_contained_type> ClampMax(const Max_& max_) const
		{
			return EmuMath::Helpers::VectorClampMax<OutSize_, out_contained_type, this_type, Max_>(*this, max_);
		}

		/// <summary>
		/// <para> Clamps the elements of this vector so that no values evaluate as less than the provided min_, or greater than the provided max_. </para>
		/// <para> This function assumes that min_ and max_ are logically correct (i.e. min_ is less than or equal to max_, max_ is greater than or equal to min_). </para>
		/// <para> 
		///		If min_ is an EmuMath vector, elements will be clamped to a minimum of the respective elements in the min_ vector. 
		///		Otherwise, all elements will be clamped to a minimum of the value of min_.
		/// </para>
		/// <para> 
		///		If max_ is an EmuMath vector, elements will be clamped to a maximum of the respective elements in the max_ vector. 
		///		Otherwise, all elements will be clamped to a maximum of the value of max_.
		/// </para>
		/// </summary>
		/// <typeparam name="out_contained_type">Type to contain within the output clamped vector.</typeparam>
		/// <typeparam name="Min_">Type used for the provided minimum value.</typeparam>
		/// <typeparam name="Max_">Type used for the provided maximum value.</typeparam>
		/// <param name="min_">Minimum value that any element within this vector may be.</param>
		/// <param name="max_">Maximum value that any element within this vector may be.</param>
		/// <returns>Copy of this vector with its elements clamped within the inclusive range between min_ and max_.</returns>
		template<std::size_t OutSize_ = size, typename out_contained_type = value_type, class Min_, class Max_>
		[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, out_contained_type> Clamp(const Min_& min_, const Max_& max_) const
		{
			return EmuMath::Helpers::VectorClamp<OutSize_, out_contained_type, this_type, Min_, Max_>(*this, min_, max_);
		}

		/// <summary>
		/// <para> Mutates the elements of this vector, outputting the results in the returned vector. </para>
		/// <para> The function type may be provided before other template arguments if there is no item of the type to pass to this function. </para>
		/// <para>
		///		The provided func_ must be invokable via the function operator() which outputs a value of or castable to this vector's value_type, 
		///		and takes a single argument of this vector's value_type.
		/// </para>
		/// </summary>
		/// <typeparam name="out_contained_type">Type to be contained within the output mutated vector.</typeparam>
		/// <typeparam name="Func_">Type to be invoked in order to perform the mutation function.</typeparam>
		/// <param name="func_">Item to be invoked to perform the mutation function on each element within this vector.</param>
		/// <returns>Copy of this vector with its elements mutated via the provided function.</returns>
		template<std::size_t OutSize_ = size, typename out_contained_type = value_type, class Func_>
		[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, out_contained_type> Mutate(Func_ func_) const
		{
			return EmuMath::Helpers::VectorMutate<OutSize_, out_contained_type, Func_&, this_type>(*this, func_);
		}
		/// <summary>
		/// <para> Mutates the elements of this vector, outputting the results in the returned vector. </para>
		/// <para> The function type may be provided before other template arguments if there is no item of the type to pass to this function. </para>
		/// <para>
		///		The provided func_ must be invokable via the function operator() which outputs a value of or castable to this vector's value_type, 
		///		and takes a single argument of this vector's value_type.
		/// </para>
		/// </summary>
		/// <typeparam name="out_contained_type">Type to be contained within the output mutated vector.</typeparam>
		/// <typeparam name="Func_">Type to be invoked in order to perform the mutation function.</typeparam>
		/// <returns>Copy of this vector with its elements mutated via the provided function type.</returns>
		template<class Func_, std::size_t OutSize_ = size, typename out_contained_type = value_type>
		[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, out_contained_type> Mutate() const
		{
			return EmuMath::Helpers::VectorMutate<OutSize_, out_contained_type, Func_, this_type>(*this);
		}

		/// <summary>
		/// <para> Rounds all elements within this vector toward negative infinity. </para>
		/// <para> This vector's value_type specialisation of EmuCore::do_floor will be used to perform this operation. </para>
		/// </summary>
		/// <typeparam name="out_contained_type">Type to be contained within the output floored vector.</typeparam>
		/// <returns>Copy of this vector with all of its elements rounded toward negative infinity.</returns>
		template<std::size_t OutSize_ = size, typename out_contained_type = value_type>
		[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, out_contained_type> Floor() const
		{
			return EmuMath::Helpers::VectorFloor<OutSize_, out_contained_type, this_type>(*this);
		}

		/// <summary>
		/// <para> Rounds all elements within this vector toward positive infinity. </para>
		/// <para> This vector's value_type specialisation of EmuCore::do_ceil will be used to perform this operation. </para>
		/// </summary>
		/// <typeparam name="out_contained_type">Type to be contained within the output ceiled vector.</typeparam>
		/// <returns>Copy of this vector with all of its elements rounded toward positive infinity.</returns>
		template<std::size_t OutSize_ = size, typename out_contained_type = value_type>
		[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, out_contained_type> Ceil() const
		{
			return EmuMath::Helpers::VectorCeil<OutSize_, out_contained_type, this_type>(*this);
		}

		/// <summary>
		/// <para> Rounds all elements within this vector toward 0. </para>
		/// <para> This vector's value_type specialisation of EmuCore::do_trunc will be used to perform this operation. </para>
		/// </summary>
		/// <typeparam name="out_contained_type">Type to be contained within the output trunced vector.</typeparam>
		/// <returns>Copy of this vector with all of its elements rounded toward 0.</returns>
		template<std::size_t OutSize_ = size, typename out_contained_type = value_type>
		[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, out_contained_type> Trunc() const
		{
			return EmuMath::Helpers::VectorTrunc<OutSize_, out_contained_type, this_type>(*this);
		}

		/// <summary>
		/// <para> Calculates the square root of all elements within this vector. </para>
		/// <para> This vector's value_type specialisation of EmuCore::do_sqrt_constexpr will be used to perform this operation. </para>
		/// <para> This function may make sacrifices to be evaluable at compile time. If it is being called at runtime, it is recommended to call Sqrt instead. </para>
		/// </summary>
		/// <typeparam name="out_contained_type">Type to be contained within the output sqrt vector.</typeparam>
		/// <returns>Vector containing the square roots of elements at respective indices within this vector.</returns>
		template<std::size_t OutSize_ = size, typename out_contained_type = preferred_floating_point>
		[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, out_contained_type> SqrtConstexpr() const
		{
			return EmuMath::Helpers::VectorSqrtConstexpr<OutSize_, out_contained_type, this_type>(*this);
		}

		/// <summary>
		/// <para> Calculates the square root of all elements within this vector. </para>
		/// <para> This vector's value_type specialisation of EmuCore::do_sqrt will be used to perform this operation. </para>
		/// <para> This function may make sacrifices to be evaluable at compile time. If it is being called at runtime, it is recommended to call Sqrt instead. </para>
		/// </summary>
		/// <typeparam name="out_contained_type">Type to be contained within the output sqrt vector.</typeparam>
		/// <returns>Vector containing the square roots of elements at respective indices within this vector.</returns>
		template<std::size_t OutSize_ = size, typename out_contained_type = preferred_floating_point>
		[[nodiscard]] inline EmuMath::Vector<OutSize_, out_contained_type> Sqrt() const
		{
			return EmuMath::Helpers::VectorSqrtConstexpr<OutSize_, out_contained_type, this_type>(*this);
		}

		/// <summary>
		/// <para> Calculates the normalised form of this vector. </para>
		/// <para> 
		///		This function may make sacrifices to be evaluable at compile time. 
		///		If it is being called at runtime, it is recommended to call Normalise or NormaliseQrsqrt instead. 
		/// </para>
		/// </summary>
		/// <typeparam name="out_floating_point_contained_type">Type to be contained within the output normalised vector.</typeparam>
		/// <typeparam name="MagFloatingPointType_">Type to use for calculating the magnitude.</typeparam>
		/// <returns>Normalised form of this vector.</returns>
		template<typename out_floating_point_contained_type = preferred_floating_point, typename MagFloatingPointType_ = out_floating_point_contained_type>
		[[nodiscard]] constexpr inline EmuMath::Vector<size, out_floating_point_contained_type> NormaliseConstexpr() const
		{
			return EmuMath::Helpers::VectorNormaliseConstexpr<out_floating_point_contained_type, MagFloatingPointType_, this_type>(*this);
		}

		/// <summary> Calculates the normalised form of this vector. </summary>
		/// <typeparam name="out_floating_point_contained_type">Type to be contained within the output normalised vector.</typeparam>
		/// <typeparam name="MagFloatingPointType_">Type to use for calculating the magnitude.</typeparam>
		/// <returns>Normalised form of this vector.</returns>
		template<typename out_floating_point_contained_type = preferred_floating_point, typename MagFloatingPointType_ = out_floating_point_contained_type>
		[[nodiscard]] inline EmuMath::Vector<size, out_floating_point_contained_type> Normalise() const
		{
			return EmuMath::Helpers::VectorNormalise<out_floating_point_contained_type, MagFloatingPointType_, this_type>(*this);
		}

		/// <summary>
		/// <para> Calculates the normalised form of this vector using the magnitude reciprocal calculated via Q_rsqrt. </para>
		///	<para> NumNewtonIterations_ can be increased to improve accuracy. </para>
		///	<para>
		///		MagicConstant_ may be changed to modify bitwise operations, but is recommended to be left to the default (0x5F3759DF) unless you know what you are doing.
		/// </para>
		/// </summary>
		/// <typeparam name="MagFloatingPointType_">Type of floating-point to calculate the magnitude as and use for arithmetic in normalisation. Defaults to float.</typeparam>
		/// <returns>Normalised form of this vector.</returns>
		template
			<
			typename out_floating_point_contained_type = preferred_floating_point,
			typename MagFloatingPointType_ = out_floating_point_contained_type,
			std::size_t NumNewtonIterations_ = 1,
			std::int32_t MagicConstant_ = 0x5F3759DF,
			class Vector_
			>
			[[nodiscard]] inline EmuMath::Vector<size, out_floating_point_contained_type> NormaliseQrsqrt() const
		{
			return EmuMath::Helpers::VectorNormaliseQrsqrt<out_floating_point_contained_type, MagFloatingPointType_, NumNewtonIterations_, MagicConstant_, this_type>(*this);
		}

		/// <summary>
		/// <para> Calculatse the cosine of the angle between this vector and the passed vector b_. </para>
		/// <para> This function may make sacrifices to be evaluable at compile time. If it is being called at runtime, it is recommended to call AngleCosine instead. </para>
		/// </summary>
		/// <typeparam name="OutCosine_">Type to output the cosine of the angle between this vector and b_ as.</typeparam>
		/// <typeparam name="VectorB_">Type of vector to calculate the cosine of the angle with.</typeparam>
		/// <param name="b_">EmuMath vector to calculate the cosine of the angle between itself and this vector.</param>
		/// <returns>Cosine of the angle between this vector and the passed vector b_.</returns>
		template<typename OutCosine_ = preferred_floating_point, class VectorB_>
		[[nodiscard]] constexpr inline OutCosine_ AngleCosineConstexpr(const VectorB_& b_) const
		{
			return EmuMath::Helpers::VectorAngleCosineConstexpr<OutCosine_, this_type, VectorB_>(*this, b_);
		}

		/// <summary>
		/// <para> Calculatse the cosine of the angle between this vector and the passed vector b_. </para>
		/// </summary>
		/// <typeparam name="OutCosine_">Type to output the cosine of the angle between this vector and b_ as.</typeparam>
		/// <typeparam name="VectorB_">Type of vector to calculate the cosine of the angle with.</typeparam>
		/// <param name="b_">EmuMath vector to calculate the cosine of the angle between itself and this vector.</param>
		/// <returns>Cosine of the angle between this vector and the passed vector b_.</returns>
		template<typename OutCosine_ = preferred_floating_point, class VectorB_>
		[[nodiscard]] inline OutCosine_ AngleCosine(const VectorB_& b_) const
		{
			return EmuMath::Helpers::VectorAngleCosine<OutCosine_, this_type, VectorB_>(*this, b_);
		}

		/// <summary>
		/// <para> Calculatse the angle between this vector and the passed vector b_. </para>
		/// <para> If Rads_ is true, the output angle will be in radians. Otherwise, it will be in degrees. </para>
		/// </summary>
		/// <typeparam name="OutAngle_">Type to output the angle between this vector and b_ as.</typeparam>
		/// <typeparam name="VectorB_">Type of vector to calculate the angle with.</typeparam>
		/// <param name="b_">EmuMath vector to calculate the angle between itself and this vector.</param>
		/// <returns>Angle between this vector and the passed vector b_, in radian units if Rads_ is true, otherwise in degree units.</returns>
		template<bool Rads_ = true, typename OutAngle_ = preferred_floating_point, class VectorB_>
		[[nodiscard]] inline OutAngle_ Angle(const VectorB_& b_) const
		{
			return EmuMath::Helpers::VectorAngle<OutAngle_, Rads_, this_type, VectorB_>(*this, b_);
		}

		/// <summary>
		/// <para> Calculates the vector that may be added to this vector to reach the provided target_ vector. </para>
		/// </summary>
		/// <typeparam name="out_contained_type">Type to be contained in the output distance vector.</typeparam>
		/// <typeparam name="TargetVector_">Type of the vector representing the target.</typeparam>
		/// <param name="target_">The target point for this vector to be able to reach with the output vector.</param>
		/// <returns>Vector that may be added to this vector to be equal to the target vector.</returns>
		template<std::size_t OutSize_ = size, typename out_contained_type = preferred_floating_point, class TargetVector_>
		[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, out_contained_type> Distance(const TargetVector_& target_) const
		{
			return EmuMath::Helpers::VectorDistance<OutSize_, out_contained_type, this_type, TargetVector_>(*this, target_);
		}

		/// <summary>
		/// <para> Calculates the 3D cross product of this vector and b_, where this vector is a_, using the provided template indices as the X, Y, and Z for A and B. </para>
		/// <para> The provided indices default to the logical x, y, and z components of both A and B, but may be modified to refer to different areas of the vectors. </para>
		/// <para> 
		///		Unless explicitly stated otherwise, the indices for B will mimic those of A. 
		///		As such, providing custom indices for A will implicitly provide the same indices for B, unless additional indices are explicitly provided for B.
		/// </para>
		/// <para> The end vector can be summarised as: </para>
		///	<para> [0] = (a_[AY_] * b_[BZ_]) - (a_[AZ_] * b_[BY_]) </para>
		/// <para> [1] = (a_[AZ_] * b_[BX_]) - (a_[AX_] * b_[BZ_]) </para>
		/// <para> [2] = (a_[AX_] * b_[BY_]) - (a_[AY_] * b_[BX_]) </para>
		/// </summary>
		/// <typeparam name="out_contained_type">Type to be contained within the output vector.</typeparam>
		/// <typeparam name="VectorB_">Type of vector representing b_ in the above formulae.</typeparam>
		/// <param name="b_">EmuMath vector representing b_ in the above formulae.</param>
		/// <returns>Cross product of this vector and the passed vector b_, using the provided indices for 3 elements from each of the respective vectors.</returns>
		template
		<
			std::size_t AX_ = 0,
			std::size_t AY_ = 1,
			std::size_t AZ_ = 2,
			std::size_t BX_ = AX_,
			std::size_t BY_ = AY_,
			std::size_t BZ_ = AZ_,
			std::size_t OutSize_ = 3,
			typename out_contained_type = preferred_floating_point,
			class VectorB_
		>
		[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, out_contained_type> CrossProduct3D(const VectorB_& b_) const
		{
			return EmuMath::Helpers::VectorCrossProduct3D<AX_, AY_, AZ_, BX_, BY_, BZ_, OutSize_, out_contained_type, this_type, VectorB_>(*this, b_);
		}
#pragma endregion

#pragma region COMPARISONS
		/// <summary>
		/// <para> Returns a boolean indicating if any elements in this vector are equal to rhs_, depending on the type of rhs_. </para>
		/// <para> If rhs_ is an EmuMath vector, respective elements will be compared. Otherwise, all elements will be compared to the same rhs_ value. </para>
		/// <para> By default, all indices are tested. To test only up to the end of the smallest vector, pass false as the argument for TestAllIndices_. </para>
		/// </summary>
		/// <typeparam name="Rhs_">Type of EmuMath vector or scalar that appears on the right hand side of comparisons.</typeparam>
		/// <param name="rhs_">EmuMath vector or scalar that appears on the right hand side of comparisons.</param>
		/// <returns>True if any executed comparisons returned true, otherwise false.</returns>
		template<bool TestAllIndices_ = true, class Rhs_>
		[[nodiscard]] constexpr inline bool CmpAnyEqualTo(const Rhs_& rhs_) const
		{
			return EmuMath::Helpers::VectorCmpAnyEqualTo<TestAllIndices_, this_type, Rhs_>(*this, rhs_);
		}

		/// <summary>
		/// <para> Returns a boolean indicating if any elements in this vector are not equal to rhs_, depending on the type of rhs_. </para>
		/// <para> If rhs_ is an EmuMath vector, respective elements will be compared. Otherwise, all elements will be compared to the same rhs_ value. </para>
		/// <para> By default, all indices are tested. To test only up to the end of the smallest vector, pass false as the argument for TestAllIndices_. </para>
		/// </summary>
		/// <typeparam name="Rhs_">Type of EmuMath vector or scalar that appears on the right hand side of comparisons.</typeparam>
		/// <param name="rhs_">EmuMath vector or scalar that appears on the right hand side of comparisons.</param>
		/// <returns>True if any executed comparisons returned true, otherwise false.</returns>
		template<bool TestAllIndices_ = true, class Rhs_>
		[[nodiscard]] constexpr inline bool CmpAnyNotEqualTo(const Rhs_& rhs_) const
		{
			return EmuMath::Helpers::VectorCmpAnyNotEqualTo<TestAllIndices_, this_type, Rhs_>(*this, rhs_);
		}

		/// <summary>
		/// <para> Returns a boolean indicating if any elements in this vector are greater than rhs_, depending on the type of rhs_. </para>
		/// <para> If rhs_ is an EmuMath vector, respective elements will be compared. Otherwise, all elements will be compared to the same rhs_ value. </para>
		/// <para> By default, all indices are tested. To test only up to the end of the smallest vector, pass false as the argument for TestAllIndices_. </para>
		/// </summary>
		/// <typeparam name="Rhs_">Type of EmuMath vector or scalar that appears on the right hand side of comparisons.</typeparam>
		/// <param name="rhs_">EmuMath vector or scalar that appears on the right hand side of comparisons.</param>
		/// <returns>True if any executed comparisons returned true, otherwise false.</returns>
		template<bool TestAllIndices_ = true, class Rhs_>
		[[nodiscard]] constexpr inline bool CmpAnyGreater(const Rhs_& rhs_) const
		{
			return EmuMath::Helpers::VectorCmpAnyGreater<TestAllIndices_, this_type, Rhs_>(*this, rhs_);
		}

		/// <summary>
		/// <para> Returns a boolean indicating if any elements in this vector are less than rhs_, depending on the type of rhs_. </para>
		/// <para> If rhs_ is an EmuMath vector, respective elements will be compared. Otherwise, all elements will be compared to the same rhs_ value. </para>
		/// <para> By default, all indices are tested. To test only up to the end of the smallest vector, pass false as the argument for TestAllIndices_. </para>
		/// </summary>
		/// <typeparam name="Rhs_">Type of EmuMath vector or scalar that appears on the right hand side of comparisons.</typeparam>
		/// <param name="rhs_">EmuMath vector or scalar that appears on the right hand side of comparisons.</param>
		/// <returns>True if any executed comparisons returned true, otherwise false.</returns>
		template<bool TestAllIndices_ = true, class Rhs_>
		[[nodiscard]] constexpr inline bool CmpAnyLess(const Rhs_& rhs_) const
		{
			return EmuMath::Helpers::VectorCmpAnyLess<TestAllIndices_, this_type, Rhs_>(*this, rhs_);
		}

		/// <summary>
		/// <para> Returns a boolean indicating if any elements in this vector are greater than or equal to rhs_, depending on the type of rhs_. </para>
		/// <para> If rhs_ is an EmuMath vector, respective elements will be compared. Otherwise, all elements will be compared to the same rhs_ value. </para>
		/// <para> By default, all indices are tested. To test only up to the end of the smallest vector, pass false as the argument for TestAllIndices_. </para>
		/// </summary>
		/// <typeparam name="Rhs_">Type of EmuMath vector or scalar that appears on the right hand side of comparisons.</typeparam>
		/// <param name="rhs_">EmuMath vector or scalar that appears on the right hand side of comparisons.</param>
		/// <returns>True if any executed comparisons returned true, otherwise false.</returns>
		template<bool TestAllIndices_ = true, class Rhs_>
		[[nodiscard]] constexpr inline bool CmpAnyGreaterEqual(const Rhs_& rhs_) const
		{
			return EmuMath::Helpers::VectorCmpAnyGreaterEqual<TestAllIndices_, this_type, Rhs_>(*this, rhs_);
		}

		/// <summary>
		/// <para> Returns a boolean indicating if any elements in this vector are greater than or equal to rhs_, depending on the type of rhs_. </para>
		/// <para> If rhs_ is an EmuMath vector, respective elements will be compared. Otherwise, all elements will be compared to the same rhs_ value. </para>
		/// <para> By default, all indices are tested. To test only up to the end of the smallest vector, pass false as the argument for TestAllIndices_. </para>
		/// </summary>
		/// <typeparam name="Rhs_">Type of EmuMath vector or scalar that appears on the right hand side of comparisons.</typeparam>
		/// <param name="rhs_">EmuMath vector or scalar that appears on the right hand side of comparisons.</param>
		/// <returns>True if any executed comparisons returned true, otherwise false.</returns>
		template<bool TestAllIndices_ = true, class Rhs_>
		[[nodiscard]] constexpr inline bool CmpAnyLessEqual(const Rhs_& rhs_) const
		{
			return EmuMath::Helpers::VectorCmpAnyLessEqual<TestAllIndices_, this_type, Rhs_>(*this, rhs_);
		}

		/// <summary>
		/// <para> Returns a boolean indicating if all elements in this vector are equal to rhs_, depending on the type of rhs_. </para>
		/// <para> If rhs_ is an EmuMath vector, respective elements will be compared. Otherwise, all elements will be compared to the same rhs_ value. </para>
		/// <para> By default, all indices are tested. To test only up to the end of the smallest vector, pass false as the argument for TestAllIndices_. </para>
		/// </summary>
		/// <typeparam name="Rhs_">Type of EmuMath vector or scalar that appears on the right hand side of comparisons.</typeparam>
		/// <param name="rhs_">EmuMath vector or scalar that appears on the right hand side of comparisons.</param>
		/// <returns>True if all executed comparisons returned true, otherwise false.</returns>
		template<bool TestAllIndices_ = true, class Rhs_>
		[[nodiscard]] constexpr inline bool CmpAllEqualTo(const Rhs_& rhs_) const
		{
			return EmuMath::Helpers::VectorCmpAllEqualTo<TestAllIndices_, this_type, Rhs_>(*this, rhs_);
		}

		/// <summary>
		/// <para> Returns a boolean indicating if all elements in this vector are not equal to rhs_, depending on the type of rhs_. </para>
		/// <para> If rhs_ is an EmuMath vector, respective elements will be compared. Otherwise, all elements will be compared to the same rhs_ value. </para>
		/// <para> By default, all indices are tested. To test only up to the end of the smallest vector, pass false as the argument for TestAllIndices_. </para>
		/// </summary>
		/// <typeparam name="Rhs_">Type of EmuMath vector or scalar that appears on the right hand side of comparisons.</typeparam>
		/// <param name="rhs_">EmuMath vector or scalar that appears on the right hand side of comparisons.</param>
		/// <returns>True if all executed comparisons returned true, otherwise false.</returns>
		template<bool TestAllIndices_ = true, class Rhs_>
		[[nodiscard]] constexpr inline bool CmpAllNotEqualTo(const Rhs_& rhs_) const
		{
			return EmuMath::Helpers::VectorCmpAllNotEqualTo<TestAllIndices_, this_type, Rhs_>(*this, rhs_);
		}

		/// <summary>
		/// <para> Returns a boolean indicating if all elements in this vector are greater than rhs_, depending on the type of rhs_. </para>
		/// <para> If rhs_ is an EmuMath vector, respective elements will be compared. Otherwise, all elements will be compared to the same rhs_ value. </para>
		/// <para> By default, all indices are tested. To test only up to the end of the smallest vector, pass false as the argument for TestAllIndices_. </para>
		/// </summary>
		/// <typeparam name="Rhs_">Type of EmuMath vector or scalar that appears on the right hand side of comparisons.</typeparam>
		/// <param name="rhs_">EmuMath vector or scalar that appears on the right hand side of comparisons.</param>
		/// <returns>True if all executed comparisons returned true, otherwise false.</returns>
		template<bool TestAllIndices_ = true, class Rhs_>
		[[nodiscard]] constexpr inline bool CmpAllGreater(const Rhs_& rhs_) const
		{
			return EmuMath::Helpers::VectorCmpAllGreater<TestAllIndices_, this_type, Rhs_>(*this, rhs_);
		}

		/// <summary>
		/// <para> Returns a boolean indicating if all elements in this vector are less than rhs_, depending on the type of rhs_. </para>
		/// <para> If rhs_ is an EmuMath vector, respective elements will be compared. Otherwise, all elements will be compared to the same rhs_ value. </para>
		/// <para> By default, all indices are tested. To test only up to the end of the smallest vector, pass false as the argument for TestAllIndices_. </para>
		/// </summary>
		/// <typeparam name="Rhs_">Type of EmuMath vector or scalar that appears on the right hand side of comparisons.</typeparam>
		/// <param name="rhs_">EmuMath vector or scalar that appears on the right hand side of comparisons.</param>
		/// <returns>True if all executed comparisons returned true, otherwise false.</returns>
		template<bool TestAllIndices_ = true, class Rhs_>
		[[nodiscard]] constexpr inline bool CmpAllLess(const Rhs_& rhs_) const
		{
			return EmuMath::Helpers::VectorCmpAllLess<TestAllIndices_, this_type, Rhs_>(*this, rhs_);
		}

		/// <summary>
		/// <para> Returns a boolean indicating if all elements in this vector are greater than or equal to rhs_, depending on the type of rhs_. </para>
		/// <para> If rhs_ is an EmuMath vector, respective elements will be compared. Otherwise, all elements will be compared to the same rhs_ value. </para>
		/// <para> By default, all indices are tested. To test only up to the end of the smallest vector, pass false as the argument for TestAllIndices_. </para>
		/// </summary>
		/// <typeparam name="Rhs_">Type of EmuMath vector or scalar that appears on the right hand side of comparisons.</typeparam>
		/// <param name="rhs_">EmuMath vector or scalar that appears on the right hand side of comparisons.</param>
		/// <returns>True if all executed comparisons returned true, otherwise false.</returns>
		template<bool TestAllIndices_ = true, class Rhs_>
		[[nodiscard]] constexpr inline bool CmpAllGreaterEqual(const Rhs_& rhs_) const
		{
			return EmuMath::Helpers::VectorCmpAllGreaterEqual<TestAllIndices_, this_type, Rhs_>(*this, rhs_);
		}

		/// <summary>
		/// <para> Returns a boolean indicating if all elements in this vector are greater than or equal to rhs_, depending on the type of rhs_. </para>
		/// <para> If rhs_ is an EmuMath vector, respective elements will be compared. Otherwise, all elements will be compared to the same rhs_ value. </para>
		/// <para> By default, all indices are tested. To test only up to the end of the smallest vector, pass false as the argument for TestAllIndices_. </para>
		/// </summary>
		/// <typeparam name="Rhs_">Type of EmuMath vector or scalar that appears on the right hand side of comparisons.</typeparam>
		/// <param name="rhs_">EmuMath vector or scalar that appears on the right hand side of comparisons.</param>
		/// <returns>True if all executed comparisons returned true, otherwise false.</returns>
		template<bool TestAllIndices_ = true, class Rhs_>
		[[nodiscard]] constexpr inline bool CmpAllLessEqual(const Rhs_& rhs_) const
		{
			return EmuMath::Helpers::VectorCmpAllLessEqual<TestAllIndices_, this_type, Rhs_>(*this, rhs_);
		}

		/// <summary>
		/// <para>
		///		Returns a vector of booleans containing the results of comparing the equality of respective elements of this vector with either those of the rhs_ vector,
		///		or with the value of a rhs_ scalar.
		/// </para>
		/// <para> If rhs_ is an EmuMath vector, it will be compared on a per-respective-element basis. If it is a scalar, all elements will be compared with it. </para>
		/// <para> May provide an optional OutSize_ for the output vector to perform more or less comparisons than there are elements within this vector. </para>
		/// </summary>
		/// <typeparam name="Rhs_">EmuMath vector or scalar type for the right-hand argument.</typeparam>
		/// <param name="rhs_">EmuMath vector to compare respective elements of this vector with, or scalar to compare all elements of this vector with.</param>
		/// <returns>Vector of booleans containing the results of the comparison of respective elements within this vector with rhs_.</returns>
		template<std::size_t OutSize_ = size, class Rhs_>
		[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, bool> CmpPerElementEqualTo(const Rhs_& rhs_) const
		{
			return EmuMath::Helpers::VectorPerElementCmpEqualTo<OutSize_, this_type, Rhs_>(*this, rhs_);
		}

		/// <summary>
		/// <para>
		///		Returns a vector of booleans containing the results of comparing the inequality of respective elements of this vector with either those of the rhs_ vector,
		///		or with the value of a rhs_ scalar.
		/// </para>
		/// <para> If rhs_ is an EmuMath vector, it will be compared on a per-respective-element basis. If it is a scalar, all elements will be compared with it. </para>
		/// <para> May provide an optional OutSize_ for the output vector to perform more or less comparisons than there are elements within this vector. </para>
		/// </summary>
		/// <typeparam name="Rhs_">EmuMath vector or scalar type for the right-hand argument.</typeparam>
		/// <param name="rhs_">EmuMath vector to compare respective elements of this vector with, or scalar to compare all elements of this vector with.</param>
		/// <returns>Vector of booleans containing the results of the comparison of respective elements within this vector with rhs_.</returns>
		template<std::size_t OutSize_ = size, class Rhs_>
		[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, bool> CmpPerElementNotEqualTo(const Rhs_& rhs_) const
		{
			return EmuMath::Helpers::VectorPerElementCmpNotEqualTo<OutSize_, this_type, Rhs_>(*this, rhs_);
		}

		/// <summary>
		/// <para>
		///		Returns a vector of booleans containing the results of comparing the magnitude of respective elements of this vector with either those of the rhs_ vector,
		///		or with the value of a rhs_ scalar.
		/// </para>
		/// <para> If rhs_ is an EmuMath vector, it will be compared on a per-respective-element basis. If it is a scalar, all elements will be compared with it. </para>
		/// <para> May provide an optional OutSize_ for the output vector to perform more or less comparisons than there are elements within this vector. </para>
		/// </summary>
		/// <typeparam name="Rhs_">EmuMath vector or scalar type for the right-hand argument.</typeparam>
		/// <param name="rhs_">EmuMath vector to compare respective elements of this vector with, or scalar to compare all elements of this vector with.</param>
		/// <returns>Vector of booleans containing the results of the comparison of respective elements within this vector with rhs_.</returns>
		template<std::size_t OutSize_ = size, class Rhs_>
		[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, bool> CmpPerElementGreater(const Rhs_& rhs_) const
		{
			return EmuMath::Helpers::VectorPerElementCmpGreater<OutSize_, this_type, Rhs_>(*this, rhs_);
		}

		/// <summary>
		/// <para>
		///		Returns a vector of booleans containing the results of comparing the magnitude of respective elements of this vector with either those of the rhs_ vector,
		///		or with the value of a rhs_ scalar.
		/// </para>
		/// <para> If rhs_ is an EmuMath vector, it will be compared on a per-respective-element basis. If it is a scalar, all elements will be compared with it. </para>
		/// <para> May provide an optional OutSize_ for the output vector to perform more or less comparisons than there are elements within this vector. </para>
		/// </summary>
		/// <typeparam name="Rhs_">EmuMath vector or scalar type for the right-hand argument.</typeparam>
		/// <param name="rhs_">EmuMath vector to compare respective elements of this vector with, or scalar to compare all elements of this vector with.</param>
		/// <returns>Vector of booleans containing the results of the comparison of respective elements within this vector with rhs_.</returns>
		template<std::size_t OutSize_ = size, class Rhs_>
		[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, bool> CmpPerElementLess(const Rhs_& rhs_) const
		{
			return EmuMath::Helpers::VectorPerElementCmpLess<OutSize_, this_type, Rhs_>(*this, rhs_);
		}

		/// <summary>
		/// <para>
		///		Returns a vector of booleans containing the results of comparing the magnitude of respective elements of this vector with either those of the rhs_ vector,
		///		or with the value of a rhs_ scalar.
		/// </para>
		/// <para> If rhs_ is an EmuMath vector, it will be compared on a per-respective-element basis. If it is a scalar, all elements will be compared with it. </para>
		/// <para> May provide an optional OutSize_ for the output vector to perform more or less comparisons than there are elements within this vector. </para>
		/// </summary>
		/// <typeparam name="Rhs_">EmuMath vector or scalar type for the right-hand argument.</typeparam>
		/// <param name="rhs_">EmuMath vector to compare respective elements of this vector with, or scalar to compare all elements of this vector with.</param>
		/// <returns>Vector of booleans containing the results of the comparison of respective elements within this vector with rhs_.</returns>
		template<std::size_t OutSize_ = size, class Rhs_>
		[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, bool> CmpPerElementGreaterEqual(const Rhs_& rhs_) const
		{
			return EmuMath::Helpers::VectorPerElementCmpGreaterEqual<OutSize_, this_type, Rhs_>(*this, rhs_);
		}

		/// <summary>
		/// <para>
		///		Returns a vector of booleans containing the results of comparing the magnitude of respective elements of this vector with either those of the rhs_ vector,
		///		or with the value of a rhs_ scalar.
		/// </para>
		/// <para> If rhs_ is an EmuMath vector, it will be compared on a per-respective-element basis. If it is a scalar, all elements will be compared with it. </para>
		/// <para> May provide an optional OutSize_ for the output vector to perform more or less comparisons than there are elements within this vector. </para>
		/// </summary>
		/// <typeparam name="Rhs_">EmuMath vector or scalar type for the right-hand argument.</typeparam>
		/// <param name="rhs_">EmuMath vector to compare respective elements of this vector with, or scalar to compare all elements of this vector with.</param>
		/// <returns>Vector of booleans containing the results of the comparison of respective elements within this vector with rhs_.</returns>
		template<std::size_t OutSize_ = size, class Rhs_>
		[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, bool> CmpPerElementLessEqual(const Rhs_& rhs_) const
		{
			return EmuMath::Helpers::VectorPerElementCmpLessEqual<OutSize_, this_type, Rhs_>(*this, rhs_);
		}
#pragma endregion

#pragma region BITWISE
		/// <summary>
		/// <para> Shifts each element in this vector to the left the specified number of times, outputting the results in a new vector. </para>
		/// <para>
		///		The passed num_shifts_ may be a scalar type or an EmuMath vector. 
		///		If it is an EmuMath vector, shifts for each element will be performed a number of times equal to the value in the respective index of this vector. 
		///		Otherwise, all elements will be shifted by this value.
		/// </para>
		/// <para> This function uses an instantiation of EmuCore::do_left_shift&lt;this_vector::value_type, Shifts_&gt; to perform each shift. </para>
		/// </summary>
		/// <typeparam name="out_contained_type">Type to be contained within the output vector.</typeparam>
		/// <typeparam name="Shifts_">Scalar type or EmuMath vector used to represent the number of shifts.</typeparam>
		/// <param name="num_shifts_">Scalar or EmuMath vector representing the number of shifts to apply to every element or to each respective element.</param>
		/// <returns>Result of left-shifting the elements of this vector the specified number of times in num_shifts_.</returns>
		template<std::size_t OutSize_ = size, typename out_contained_type = value_type, class Shifts_>
		constexpr inline EmuMath::Vector<OutSize_, out_contained_type> ShiftLeft(const Shifts_& num_shifts_) const
		{
			return EmuMath::Helpers::VectorShiftLeft<OutSize_, out_contained_type, this_type, Shifts_>(*this, num_shifts_);
		}

		/// <summary>
		/// <para> Shifts each element in this vector to the right the specified number of times, outputting the results in a new vector. </para>
		/// <para>
		///		The passed num_shifts_ may be a scalar type or an EmuMath vector. 
		///		If it is an EmuMath vector, shifts for each element will be performed a number of times equal to the value in the respective index of this vector. 
		///		Otherwise, all elements will be shifted by this value.
		/// </para>
		/// <para> This function uses an instantiation of EmuCore::do_right_shift&lt;this_vector::value_type, Shifts_&gt; to perform each shift. </para>
		/// </summary>
		/// <typeparam name="out_contained_type">Type to be contained within the output vector.</typeparam>
		/// <typeparam name="Shifts_">Scalar type or EmuMath vector used to represent the number of shifts.</typeparam>
		/// <param name="num_shifts_">Scalar or EmuMath vector representing the number of shifts to apply to every element or to each respective element.</param>
		/// <returns>Result of right-shifting the elements of this vector the specified number of times in num_shifts_.</returns>
		template<std::size_t OutSize_ = size, typename out_contained_type = value_type, class Shifts_>
		constexpr inline EmuMath::Vector<OutSize_, out_contained_type> ShiftRight(const Shifts_& num_shifts_) const
		{
			return EmuMath::Helpers::VectorShiftRight<OutSize_, out_contained_type, this_type, Shifts_>(*this, num_shifts_);
		}

		/// <summary>
		/// <para> Perform a bitwise AND on all elements of this vector with rhs_, depending on the type rhs_ is passed as. </para>
		/// <para> If rhs_ is an EmuMath vector, respective elements will be ANDed, otherwise all elements in this vector will be ANDed with the value of rhs_ itself. </para>
		/// <para> This operation is carried out by EmuCore::do_bitwise_and&lt;this_vector::value_type, Rhs_::value_type (or just Rhs_ if not a vector)&gt;. </para>
		/// </summary>
		/// <typeparam name="out_contained_type">Type to be contained within the output vector.</typeparam>
		/// <typeparam name="Rhs_">Type of vector or scalar appearing the the right-hand side of AND operations.</typeparam>
		/// <param name="rhs_">EmuMath vector or scalar appearing on the right-hand side of AND operations.</param>
		/// <returns>EmuMath vector containing the results of bitwise ANDing this vector with the passed rhs_.</returns>
		template<std::size_t OutSize_ = size, typename out_contained_type = value_type, class Rhs_>
		constexpr inline EmuMath::Vector<OutSize_, out_contained_type> And(const Rhs_& rhs_) const
		{
			return EmuMath::Helpers::VectorAnd<OutSize_, out_contained_type, this_type, Rhs_>(*this, rhs_);
		}

		/// <summary>
		/// <para> Perform a bitwise OR on all elements of this vector with rhs_, depending on the type rhs_ is passed as. </para>
		/// <para> If rhs_ is an EmuMath vector, respective elements will be ORed, otherwise all elements in this vector will be ORed with the value of rhs_ itself. </para>
		/// <para> This operation is carried out by EmuCore::do_bitwise_or&lt;this_vector::value_type, Rhs_::value_type (or just Rhs_ if not a vector)&gt;. </para>
		/// </summary>
		/// <typeparam name="out_contained_type">Type to be contained within the output vector.</typeparam>
		/// <typeparam name="Rhs_">Type of vector or scalar appearing the the right-hand side of OR operations.</typeparam>
		/// <param name="rhs_">EmuMath vector or scalar appearing on the right-hand side of OR operations.</param>
		/// <returns>EmuMath vector containing the results of bitwise ORing this vector with the passed rhs_.</returns>
		template<std::size_t OutSize_ = size, typename out_contained_type = value_type, class Rhs_>
		constexpr inline EmuMath::Vector<OutSize_, out_contained_type> Or(const Rhs_& rhs_) const
		{
			return EmuMath::Helpers::VectorOr<OutSize_, out_contained_type, this_type, Rhs_>(*this, rhs_);
		}

		/// <summary>
		/// <para> Perform a bitwise XOR on all elements of this vector with rhs_, depending on the type rhs_ is passed as. </para>
		/// <para> If rhs_ is an EmuMath vector, respective elements will be XORed, otherwise all elements in this vector will be ORed with the value of rhs_ itself. </para>
		/// <para> This operation is carried out by EmuCore::do_bitwise_xor&lt;this_vector::value_type, Rhs_::value_type (or just Rhs_ if not a vector)&gt;. </para>
		/// </summary>
		/// <typeparam name="out_contained_type">Type to be contained within the output vector.</typeparam>
		/// <typeparam name="Rhs_">Type of vector or scalar appearing the the right-hand side of XOR operations.</typeparam>
		/// <param name="rhs_">EmuMath vector or scalar appearing on the right-hand side of XOR operations.</param>
		/// <returns>EmuMath vector containing the results of bitwise XORing this vector with the passed rhs_.</returns>
		template<std::size_t OutSize_ = size, typename out_contained_type = value_type, class Rhs_>
		constexpr inline EmuMath::Vector<OutSize_, out_contained_type> Xor(const Rhs_& rhs_) const
		{
			return EmuMath::Helpers::VectorXor<OutSize_, out_contained_type, this_type, Rhs_>(*this, rhs_);
		}

		/// <summary>
		/// <para> Performs a bitwise NOT on all elements within this vector and outputs the results in the return vector. </para>
		/// <para> This operation is carried out by EmuCore::do_bitwise_not&lt;this_vector::value_type&gt;. </para>
		/// </summary>
		/// <typeparam name="out_contained_type">Type to be contained within the output vector.</typeparam>
		/// <returns>EmuMath vector containing the results of the bitwise NOT operation on this vector_.</returns>
		template<std::size_t OutSize_ = size, typename out_contained_type = value_type>
		constexpr inline EmuMath::Vector<OutSize_, out_contained_type> Not() const
		{
			return EmuMath::Helpers::VectorNot<OutSize_, out_contained_type, this_type>(*this);
		}
#pragma endregion

#pragma region CONVERSIONS
		/// <summary> Function to convert this vector to a different EmuMath vector of the specified size and contained type. </summary>
		/// <typeparam name="out_contained_type">Type to be contained within the output vector.</typeparam>
		/// <returns>This vector represented as an EmuMath vector with the provided size and contained type.</returns>
		template<std::size_t OutSize_, typename out_contained_type>
		[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, out_contained_type> As()
		{
			return EmuMath::Vector<OutSize_, out_contained_type>(*this);
		}
		/// <summary> Function to convert this vector to a different EmuMath vector of the specified size and contained type. </summary>
		/// <typeparam name="out_contained_type">Type to be contained within the output vector.</typeparam>
		/// <returns>This vector represented as an EmuMath vector with the provided size and contained type.</returns>
		template<std::size_t OutSize_, typename out_contained_type>
		[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, out_contained_type> As() const
		{
			return EmuMath::Vector<OutSize_, out_contained_type>(*this);
		}

		/// <summary> Conversion of this vector to a different type of EmuMath vector. Identical to As&lt;OutSize_, out_contained_type&gt;. </summary>
		/// <typeparam name="out_contained_type"></typeparam>
		template<std::size_t OutSize_, typename out_contained_type>
		explicit constexpr inline operator EmuMath::Vector<OutSize_, out_contained_type>()
		{
			return this->template As<OutSize_, out_contained_type>();
		}
		/// <summary> Conversion of this vector to a different type of EmuMath vector. Identical to As&lt;OutSize_, out_contained_type&gt;. </summary>
		/// <typeparam name="out_contained_type"></typeparam>
		template<std::size_t OutSize_, typename out_contained_type>
		explicit constexpr inline operator EmuMath::Vector<OutSize_, out_contained_type>() const
		{
			return this->template As<OutSize_, out_contained_type>();
		}

		/// <summary>
		///	Boolean interpretation of this vector. 
		///	As the all-zero vector is considered the fully default constructed vector, this will be true if at least 1 element is not equal to a default value_type.
		/// </summary>
		explicit constexpr inline operator bool() const
		{
			return EmuMath::Helpers::VectorCmpAnyNotEqualTo<true, this_type, value_type>(*this, value_type());
		}
		/// <summary>
		///	Vectorwise boolean interpretation of this vector. 
		/// As the zero of this vector is considered the default constructed value_type, an index will be true if it's respective element is not equal to a default value_type.
		/// </summary>
		explicit constexpr inline operator EmuMath::Vector<size, bool>() const
		{
			return EmuMath::Helpers::VectorPerElementCmpNotEqualTo<size, bool, this_type, value_type>(*this, value_type());
		}
		/// <summary>
		///	Inversion of this vector's bool cast. As such, this will only be true if all values within this vactor are equal to its default-constructed value_type.
		/// </summary>
		/// <returns>True if all elements of this vector are equal to a default-constructed value_type, otherwise false.</returns>
		constexpr inline bool operator!() const
		{
			return !static_cast<bool>(*this);
		}
#pragma endregion

		/// <summary> Element 0 within this vector. </summary>
		contained_type x;
		/// <summary> Element 1 within this vector. </summary>
		contained_type y;
		/// <summary> Element 2 within this vector. </summary>
		contained_type z;
		/// <summary> Element 3 within this vector. </summary>
		contained_type w;

	private:
		template<std::size_t Index_>
		constexpr inline contained_type& _get_index()
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
				static_assert(false, "Attempted to retrieve data from an EmuMath vector using an out-of-range index.");
			}
		}
		template<std::size_t Index_>
		constexpr inline const contained_type& _get_index() const
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
				static_assert(false, "Attempted to retrieve data from an EmuMath vector using an out-of-range index.");
			}
		}
		constexpr inline contained_type& _get_index(const std::size_t index_)
		{
			return *(data() + index_);
		}
		constexpr inline const contained_type& _get_index(const std::size_t index_) const
		{
			return *(data() + index_);
		}

		template<std::size_t Index_, typename In_>
		constexpr inline void _set_data_at_index(In_& in_)
		{
			if constexpr (Index_ < size)
			{
				if constexpr (contains_reference_wrappers)
				{
					if constexpr (contains_const_reference_wrappers)
					{
						// May set any type of reference to a const since non-const will be implicitly interpreted as const in such contexts
						_get_index<Index_>() = contained_type(in_);
					}
					else
					{
						if constexpr (!std::is_const_v<In_>)
						{
							_get_index<Index_>() = contained_type(in_);
						}
						else
						{
							static_assert(false, "Attempted to set a non-const-reference-containing EmuMath vector's data via constant data. If a copy is intended, use vector.at<Index_>() = in_.");
						}
					}
				}
				else
				{
					_get_index<Index_>() = static_cast<contained_type>(in_);
				}
			}
			else
			{
				static_assert(false, "Attempted to set the index of an EmuMath vector using an out-of-range index.");
			}
		}
		template<typename In_>
		constexpr inline void _set_data_at_index(In_& in_, const std::size_t index_)
		{
			if constexpr (contains_reference_wrappers)
			{
				if constexpr (std::is_reference_v<In_>)
				{
					if constexpr (contains_const_reference_wrappers)
					{
						// May set any type of reference to a const since non-const will be implicitly interpreted as const in such contexts
						_get_index(index_) = contained_type(in_);
					}
					else
					{
						if constexpr (!std::is_const_v<In_>)
						{
							_get_index(index_) = contained_type(in_);
						}
						else
						{
							static_assert(false, "Attempted to set a non-const-reference-containing EmuMath vector's data via constant data. If a copy is intended, use vector.at<Index_>() = in_.");
						}
					}
				}
				else
				{
					static_assert(false, "Attempted to set the references contained within an EmuMath vector via a non-reference type. If a copy is intended, use vector.at<Index_>() = in_.");
				}
			}
			else
			{
				_get_index(index_) = static_cast<contained_type>(in_);
			}
		}
	};

	/// <summary> Alias shorthand for creating an EmuMath vector containing 4 elements. Specialised to provide some syntactic sugar, such as named axis elements. </summary>
	/// <typeparam name="T_">Type to be contained within the vector.</typeparam>
	template<typename T_>
	using Vector4 = EmuMath::Vector<4, T_>;
}

#endif
