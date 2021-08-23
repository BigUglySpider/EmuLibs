#ifndef EMU_MATH_VECTOR_INFO_H_INC_
#define EMU_MATH_VECTOR_INFO_H_INC_

#include "../../EmuCore/TMPHelpers/TypeConvertors.h"


namespace EmuMath::_underlying_components
{
	/// <summary>
	/// <para> Type used to provide generic info to EmuMath vectors. Useful for easing common types and constexpr data implementations in specialisation. </para>
	/// </summary>
	template<std::size_t Size_, typename T_>
	struct VectorInfo
	{
		static_assert(Size_ > 0, "Unable to create an EmuMath Vector which contains 0 elements.");
		static_assert(!std::is_same_v<T_, void>, "Unable to create an EmuMath Vector which contains void elements.");
		static_assert(!std::is_reference_v<T_>, "Attempted to form an EmuMath vector with an internal reference type. To have a vector storing references, use EmuMath::InternalVectorReference<T> as the vector's stored type, or create a vector via the EmuMath::RefVector or EmuMath::ConstRefVector aliases to achieve the same with cleaner semantics.");

		/// <summary> The type contained within this vector. </summary>
		using contained_type = T_;
		/// <summary> Boolean indicating if this vector contains reference wrapping types. </summary>
		static constexpr bool contains_reference_wrappers = EmuCore::TMPHelpers::is_reference_wrapper<contained_type>::value;
		/// <summary> The raw value_type within this vector before its const qualifier is forcibly removed. </summary>
		using raw_value_type = typename EmuCore::TMPHelpers::get_reference_wrapper_contained_type<contained_type>::type;
		/// <summary> Value type of the items stored within this vector, without const qualifiers where applicable. </summary>
		using value_type = std::remove_const_t<raw_value_type>;
		/// <summary> The preferred floating point type for this vector. Float if this vector contains non-floating-point types, otherwise matches value_type. </summary>
		using preferred_floating_point = EmuCore::TMPHelpers::first_floating_point_t<value_type, float>;
		/// <summary> Boolean indicating if the reference wrappers within this vector contain constant references. Always false if contains_reference_wrappers is false. </summary>
		static constexpr bool contains_const_reference_wrappers = std::is_const_v<raw_value_type> && contains_reference_wrappers;
		/// <summary> Boolean indicating if the reference wrappers within this vector contain non-constant references. Always false if contains_reference_wrappers is false. </summary>
		static constexpr bool contains_non_const_reference_wrappers = contains_reference_wrappers && !contains_const_reference_wrappers;

		/// <summary> The number of elements contained in this vector. </summary>
		static constexpr std::size_t size = Size_;

		static constexpr bool has_integral_elements = std::is_integral_v<std::remove_cv_t<value_type>>;
		static constexpr bool has_floating_point_elements = std::is_floating_point_v<std::remove_cv_t<value_type>>;
		static constexpr bool has_const_values = std::is_const_v<raw_value_type>;
	};
}

#endif
