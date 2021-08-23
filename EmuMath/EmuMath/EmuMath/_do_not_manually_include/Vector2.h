#ifndef EMU_MATH_VECTOR_2_SUGAR_H_INC_
#define EMU_MATH_VECTOR_2_SUGAR_H_INC_ 1

#include "VectorT.h"

namespace EmuMath
{
	template<typename T_>
	struct Vector<2, T_>
	{
#pragma region VECTOR_INFO
		/// <summary>
		/// <para> General template info regarding this type of EmuMath vector. </para>
		/// <para> For further information on individual components within this vector, you should view components of the same name under this vector_info. </para>
		/// </summary>
		using vector_info = EmuMath::_underlying_components::VectorInfo<2, T_>;
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
		constexpr Vector() : x(), y()
		{
		}
		constexpr Vector(const this_type& toCopy_) : x(toCopy_.at<0>()), y(toCopy_.at<1>())
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
		template<typename X_, typename Y_>
		constexpr Vector(X_&& x_, Y_&& y_) : 
			x(std::forward<X_>(x_)),
			y(std::forward<Y_>(y_))
		{
			static_assert
			(
				EmuCore::TMPHelpers::are_all_comparisons_true<std::is_constructible, contained_type, X_, Y_>::value,
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
			return EmuMath::Helpers::VectorCopy(*this, toCopy_);
		}

		template<class RhsVector_>
		constexpr inline this_type& operator+=(const RhsVector_& rhs_)
		{
			(*this) = EmuMath::Helpers::VectorAdd(*this, rhs_);
			return *this;
		}

		template<class RhsVector_>
		constexpr inline this_type& operator-=(const RhsVector_& rhs_)
		{
			(*this) = EmuMath::Helpers::VectorSubtract(*this, rhs_);
			return *this;
		}

		template<class Rhs_>
		constexpr inline this_type& operator*=(const Rhs_& rhs_)
		{
			(*this) = EmuMath::Helpers::VectorMultiply(*this, rhs_);
			return *this;
		}

		template<class Rhs_>
		constexpr inline this_type& operator/=(const Rhs_& rhs_)
		{
			(*this) = EmuMath::Helpers::VectorDivide(*this, rhs_);
			return *this;
		}

		template<class Rhs_>
		constexpr inline this_type& operator&=(const Rhs_& rhs_)
		{
			(*this) = EmuMath::Helpers::VectorAnd(*this, rhs_);
			return *this;
		}

		template<class Rhs_>
		constexpr inline this_type& operator|=(const Rhs_& rhs_)
		{
			(*this) = EmuMath::Helpers::VectorOr(*this, rhs_);
			return *this;
		}

		template<class Rhs_>
		constexpr inline this_type& operator^=(const Rhs_& rhs_)
		{
			(*this) = EmuMath::Helpers::VectorXor(*this, rhs_);
			return *this;
		}

		template<class Rhs_>
		constexpr inline this_type& operator<<=(const Rhs_& rhs_)
		{
			(*this) = EmuMath::Helpers::VectorShiftLeft(*this, rhs_);
			return *this;
		}

		template<class Rhs_>
		constexpr inline this_type& operator>>=(const Rhs_& rhs_)
		{
			(*this) = EmuMath::Helpers::VectorShiftLeft(*this, rhs_);
			return *this;
		}
#pragma endregion

		/// <summary> Element 0 within this vector. </summary>
		contained_type x;
		/// <summary> Element 1 within this vector. </summary>
		contained_type y;

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
							static_assert(false, "Attempted to set a non-const-reference-containing EmuMath vector's data via constant data. If a copy is intended, use vector.at<Index_> = in_.");
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
							static_assert(false, "Attempted to set a non-const-reference-containing EmuMath vector's data via constant data. If a copy is intended, use vector.at<Index_> = in_.");
						}
					}
				}
				else
				{
					static_assert(false, "Attempted to set the references contained within an EmuMath vector via a non-reference type. If a copy is intended, use vector.at<Index_> = in_.");
				}
			}
			else
			{
				_get_index(index_) = static_cast<contained_type>(in_);
			}
		}
	};

	/// <summary> Alias shorthand for creating an EmuMath vector containing 2 elements. Specialised to provide some syntactic sugar, such as named axis elements. </summary>
	/// <typeparam name="T_">Type to be contained within the vector.</typeparam>
	template<typename T_>
	using Vector2 = EmuMath::Vector<2, T_>;
}

#endif
