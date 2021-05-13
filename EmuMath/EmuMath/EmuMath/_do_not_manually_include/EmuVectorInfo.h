#ifndef EMU_MATH_VECTOR_INFO_H_INC_
#define EMU_MATH_VECTOR_INFO_H_INC_

namespace EmuMath
{
	namespace _info
	{
		/// <summary> Type used to provide universal information about EmuMath Vectors regardless of size. </summary>
		/// <typeparam name="T">Type stored within the vector.</typeparam>
		template<typename T>
		struct VectorInfo
		{
			using value_type = T;
			using nonref_value_type = std::remove_reference_t<value_type>;
			using ref_value_type = std::conditional_t<std::is_reference_v<value_type>, value_type, value_type&>;

			static constexpr bool has_arithmetic_values = std::is_arithmetic_v<nonref_value_type>;
			static constexpr bool has_integral_values = std::is_integral_v<nonref_value_type>;
			static constexpr bool has_floating_point_values = std::is_floating_point_v<nonref_value_type>;
			static constexpr bool has_signed_values = std::is_signed_v<nonref_value_type>;
			static constexpr bool has_reference_values = std::is_reference_v<nonref_value_type>;
			static constexpr std::size_t value_type_size = sizeof(value_type);
			static constexpr std::size_t nonref_value_type_size = sizeof(nonref_value_type);
		};
	}
}

#endif
