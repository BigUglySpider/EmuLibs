#ifndef EMU_MATH_VECTOR_T_H_INC_
#define EMU_MATH_VECTOR_T_H_INC_ 1

#include "VectorHelpers.h"
#include "VectorInfo.h"
#include <array>
#include <ostream>

namespace EmuMath
{
	template<std::size_t Size_, typename T_>
	struct Vector
	{
	public:
#pragma region VECTOR_INFO
		/// <summary>
		/// <para> General template info regarding this type of EmuMath vector. </para>
		/// <para> For further information on individual components within this vector, you should view components of the same name under this vector_info. </para>
		/// </summary>
		using vector_info = EmuMath::_underlying_components::VectorInfo<Size_, T_>;
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
		constexpr Vector() : data()
		{
		}
		constexpr Vector(const this_type& toCopy_) : data(toCopy_.data)
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
		/// <summary>
		/// <para> Constructs this vector with its elements matching the passed data, in contiguous order of the 0th to the (size - 1)th element. </para>
		/// <para> This constructor requires a number of arguments equal to the number of elements in the vector. </para>
		/// </summary>
		/// <typeparam name="Args">All arguments passed to construct this vector via.</typeparam>
		/// <typeparam name="RequiresArgumentCountEqualToSize">Dummy parameter used to make use of std::enable_if.</typeparam>
		/// <param name="contiguousData_">Arguments to create this vector's elements, in contiguous order from the 0th-(size - 1)th element in this vector.</param>
		template<typename...Args, typename RequiresArgumentCountEqualToSize = std::enable_if_t<sizeof...(Args) == size>>
		constexpr Vector(Args&&...contiguousData_) : data({ static_cast<contained_type>(std::forward<Args>(contiguousData_))... })
		{
			static_assert(sizeof...(Args) == size, "Provided an amount of arguments to an EmuMath Vector constructor that is not equal to the number of elements in the Vector.");
			static_assert
			(
				EmuCore::TMPHelpers::are_all_comparisons_true<std::is_constructible, contained_type, Args...>::value,
				"Attempted to construct an EmuMath Vector via it's template constructor, but at least one provided argument cannot be used to construct the Vector's contained_type."
			);
		}
#pragma endregion

#pragma region RANDOM_ACCESS
		template<std::size_t Index_>
		[[nodiscard]] constexpr inline raw_value_type& at()
		{
			if constexpr (Index_ < size)
			{
				return std::get<Index_>(data);
			}
			else
			{
				static_assert(false, "Attempted to retrieve data from an EmuMath vector using an out-of-range index.");
			}
		}
		template<std::size_t Index_>
		[[nodiscard]] constexpr inline const raw_value_type& at() const
		{
			if constexpr (Index_ < size)
			{
				return std::get<Index_>(data);
			}
			else
			{
				static_assert(false, "Attempted to retrieve data from an EmuMath vector using an out-of-range index.");
			}
		}
		[[nodiscard]] constexpr inline raw_value_type& at(const std::size_t index_)
		{
			return data[index_];
		}
		[[nodiscard]] constexpr inline const raw_value_type& at(const std::size_t index_) const
		{
			return data[index_];
		}
		[[nodiscard]] constexpr inline raw_value_type& operator[](const std::size_t index_)
		{
			return this->at(index_);
		}
		[[nodiscard]] constexpr inline const raw_value_type& operator[](const std::size_t index_) const
		{
			return this->at(index_);
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

	private:
		/// <summary> The type used to store this vector's data. </summary>
		using data_storage_type = std::array<contained_type, size>;

		/// <summary> Contiguous data stored within this matrix. </summary>
		data_storage_type data;

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
						data[Index_] = contained_type(in_);
					}
					else
					{
						if constexpr (!std::is_const_v<In_>)
						{
							data[Index_] = contained_type(in_);
						}
						else
						{
							static_assert(false, "Attempted to set a non-const-reference-containing EmuMath vector's data via constant data. If a copy is intended, use vector.at<Index_> = in_.");
						}
					}
				}
				else
				{
					data[Index_] = static_cast<contained_type>(in_);
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
						data[index_] = contained_type(in_);
					}
					else
					{
						if constexpr (!std::is_const_v<In_>)
						{
							data[index_] = contained_type(in_);
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
				data[index_] = static_cast<contained_type>(in_);
			}
		}
	};
}

template<std::size_t Size_, typename T_>
inline std::ostream& operator<<(std::ostream& stream_, const EmuMath::Vector<Size_, T_>& vector_)
{
	return EmuMath::Helpers::_underlying_vector_funcs::_append_vector_to_stream(stream_, vector_);
}
template<std::size_t Size_, typename T_>
inline std::wostream& operator<<(std::wostream& stream_, const EmuMath::Vector<Size_, T_>& vector_)
{
	return EmuMath::Helpers::_underlying_vector_funcs::_append_vector_to_wide_stream(stream_, vector_);
}

#endif
