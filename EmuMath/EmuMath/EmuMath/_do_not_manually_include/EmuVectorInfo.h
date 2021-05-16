#ifndef EMU_MATH_VECTOR_INFO_H_INC_
#define EMU_MATH_VECTOR_INFO_H_INC_

#include "../../EmuCore/ArithmeticHelpers/CommonValues.h"
#include "../../EmuCore/TMPHelpers/TypeConvertors.h"

namespace EmuMath
{
	namespace _info
	{
		/// <summary> Type used to provide universal information about EmuMath Vectors regardless of size. </summary>
		/// <typeparam name="T">Type stored within the vector.</typeparam>
		template<typename T>
		struct VectorInfo
		{
			/// <summary> The type passed as a parameter and stored within the vector. </summary>
			using value_type = T;
			/// <summary> Non-reference variant of value_type. </summary>
			using nonref_value_type = std::remove_reference_t<value_type>;
			/// <summary> Variant of nonref_value_type without volatile/const qualifiers. </summary>
			using nonref_value_type_without_qualifiers = std::remove_volatile_t<std::remove_const_t<nonref_value_type>>;
			/// <summary> Variant of value_type which represents a reference. </summary>
			using ref_value_type = std::conditional_t<std::is_reference_v<value_type>, value_type, value_type&>;
			/// <summary> Pointer to a nonref_value_type. </summary>
			using pointer_value_type = nonref_value_type*;

			/// <summary> Boolean indicating if the Vector's contained values are constant. </summary>
			static constexpr bool has_const_values = std::is_const_v<nonref_value_type>;
			/// <summary> Boolean indicating if the Vector's contained values are arithmetic. </summary>
			static constexpr bool has_arithmetic_values = std::is_arithmetic_v<nonref_value_type>;
			/// <summary> Boolean indicating if the Vector's contained values are integers. </summary>
			static constexpr bool has_integral_values = std::is_integral_v<nonref_value_type>;
			/// <summary> Boolean indicating if the Vector's contained values are floating point/real numbers. </summary>
			static constexpr bool has_floating_point_values = std::is_floating_point_v<nonref_value_type>;
			/// <summary> Boolean indicating if the Vector's contained values are signed numbers. </summary>
			static constexpr bool has_signed_values = std::is_signed_v<nonref_value_type>;
			/// <summary> Boolean indicating if the Vector's contained values are references. </summary>
			static constexpr bool has_reference_values = std::is_reference_v<value_type>;
			/// <summary> Boolean indicating if the Vector's contained values are constant references. </summary>
			static constexpr bool has_const_reference_values = has_const_values && has_reference_values;
			/// <summary> The size of an individual value_type. </summary>
			static constexpr std::size_t value_type_size = sizeof(value_type);
			/// <summary> The size of an individual nonref_value_type. </summary>
			static constexpr std::size_t nonref_value_type_size = sizeof(nonref_value_type);
			/// <summary> Value of a nonref_value_type when constructed with 0. </summary>
			static constexpr nonref_value_type_without_qualifiers value_zero = EmuCore::ArithmeticHelpers::ZeroT<nonref_value_type_without_qualifiers>;
			/// <summary> Value of a nonref_value_type when constructed with 1. </summary>
			static constexpr nonref_value_type_without_qualifiers value_one = EmuCore::ArithmeticHelpers::OneT<nonref_value_type_without_qualifiers>;

			/// <summary> Constant variant of ref_value_type. </summary>
			using const_ref_value_type = std::conditional_t<has_const_reference_values, ref_value_type, const nonref_value_type&>;
			/// <summary> Constant variant of pointer_value_type. </summary>
			using const_pointer_value_type = std::conditional_t<has_const_values, pointer_value_type, const nonref_value_type*>;

			/// <summary> The default floating point type used by this vector type. </summary>
			using default_floating_point = EmuCore::TMPHelpers::best_floating_point_rep_t<nonref_value_type_without_qualifiers>;
			using default_int = std::conditional_t
			<
				std::is_signed_v<nonref_value_type_without_qualifiers>,
				EmuCore::TMPHelpers::best_signed_int_rep_t<nonref_value_type_without_qualifiers>,
				EmuCore::TMPHelpers::best_unsigned_int_rep_t<nonref_value_type_without_qualifiers>
			>;

			/// <summary> Simplification for calling a square root function for the default_floating_point type. </summary>
			/// <typeparam name="Val_">Type of the passed value to get the square root of.</typeparam>
			/// <param name="val_">Value to get the square root of.</param>
			/// <returns>Square root of the passed value, calculated and represented as a default_floating_point type.</returns>
			template<typename Val_>
			static default_floating_point _default_floating_point_sqrt(const Val_& val_)
			{
				using UnqualifiedVal = std::remove_cv_t<Val_>;
				if constexpr (std::is_same_v<default_floating_point, float>)
				{
					if constexpr (std::is_same_v<default_floating_point, UnqualifiedVal>)
					{
						return sqrtf(val_);
					}
					else
					{
						return sqrtf(static_cast<default_floating_point>(val_));
					}
				}
				else if constexpr (std::is_same_v<default_floating_point, double>)
				{
					if constexpr (std::is_same_v<default_floating_point, UnqualifiedVal>)
					{
						return sqrt(val_);
					}
					else
					{
						return sqrt(static_cast<default_floating_point>(val_));
					}
				}
				else if constexpr (std::is_same_v<default_floating_point, long double>)
				{
					if constexpr (std::is_same_v<default_floating_point, UnqualifiedVal>)
					{
						return sqrtl(val_);
					}
					else
					{
						return sqrtl(static_cast<default_floating_point>(val_));
					}
				}
				else
				{
					static_assert(false, "An EmuVectorInfo's default_floating_point is not a supported type. This is an internal EmuMath error.");
				}
			}
		};
	}
}

#endif
