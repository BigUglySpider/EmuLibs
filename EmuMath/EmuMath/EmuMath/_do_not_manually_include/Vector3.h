#ifndef EMU_MATH_VECTOR_3_SUGAR_H_INC_
#define EMU_MATH_VECTOR_3_SUGAR_H_INC_ 1

#include "VectorT.h"

namespace EmuMath
{
	template<typename T_>
	struct Vector<3, T_>
	{
#pragma region VECTOR_INFO
		/// <summary>
		/// <para> General template info regarding this type of EmuMath vector. </para>
		/// <para> For further information on individual components within this vector, you should view components of the same name under this vector_info. </para>
		/// </summary>
		using vector_info = EmuMath::_underlying_components::VectorInfo<3, T_>;
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
		constexpr Vector() : x(), y(), z()
		{
		}
		constexpr Vector(const this_type& toCopy_) : x(toCopy_.at<0>()), y(toCopy_.at<1>()), z(toCopy_.at<2>())
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
		template<typename X_, typename Y_, typename Z_>
		constexpr Vector(X_&& x_, Y_&& y_, Z_&& z_) :
			x(std::forward<X_>(x_)),
			y(std::forward<Y_>(y_)),
			z(std::forward<Z_>(z_))
		{
			static_assert
			(
				EmuCore::TMPHelpers::are_all_comparisons_true<std::is_constructible, contained_type, X_, Y_, Z_>::value,
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

#pragma region OPERATORS
		template<class ToCopy_>
		constexpr inline this_type& operator=(const ToCopy_& toCopy_)
		{
			return EmuMath::Helpers::VectorCopy<this_type, ToCopy_>(*this, toCopy_);
		}
#pragma endregion

		/// <summary> Element 0 within this vector. </summary>
		contained_type x;
		/// <summary> Element 1 within this vector. </summary>
		contained_type y;
		/// <summary> Element 2 within this vector. </summary>
		contained_type z;

	private:
		constexpr inline contained_type* _data()
		{
			return &x;
		}
		constexpr inline const contained_type* _data() const
		{
			return &x;
		}

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
			else
			{
				static_assert(false, "Attempted to retrieve data from an EmuMath vector using an out-of-range index.");
			}
		}
		constexpr inline contained_type& _get_index(const std::size_t index_)
		{
			return *(_data() + index_);
		}
		constexpr inline const contained_type& _get_index(const std::size_t index_) const
		{
			return *(_data() + index_);
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

	/// <summary> Alias shorthand for creating an EmuMath vector containing 3 elements. Specialised to provide some syntactic sugar, such as named axis elements. </summary>
	/// <typeparam name="T_">Type to be contained within the vector.</typeparam>
	template<typename T_>
	using Vector3 = EmuMath::Vector<3, T_>;
}

#endif
