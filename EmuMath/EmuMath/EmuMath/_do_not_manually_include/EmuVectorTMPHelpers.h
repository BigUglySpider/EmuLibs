#ifndef EMU_VECTOR_TMP_HELPERS_H_INC_
#define EMU_VECTOR_TMP_HELPERS_H_INC_

#include "EmuVectorInfo.h"
#include "../../EmuCore/TMPHelpers/TypeComparators.h"
#include <type_traits>

namespace EmuMath
{
	template<typename T>
	struct Vector2;
	template<typename T>
	struct Vector3;
	template<typename T>
	struct Vector4;

	namespace TMPHelpers
	{

		/// <summary> Determines if the passed type T is an EmuMath Vector type. </summary>
		/// <typeparam name="T">Type to check for being an EmuMath Vector.</typeparam>
		template<class T>
		struct is_emu_vector
		{
			static constexpr bool value =
			(
				EmuCore::TMPHelpers::is_instance_of_typeparams_only_v<T, EmuMath::Vector2> ||
				EmuCore::TMPHelpers::is_instance_of_typeparams_only_v<T, EmuMath::Vector3> ||
				EmuCore::TMPHelpers::is_instance_of_typeparams_only_v<T, EmuMath::Vector4>
			);
		};
		/// <summary> Boolean indicating if the passed type T is an EmuMath Vector type. </summary>
		/// <typeparam name="T">Type to check for being an EmuMath Vector.</typeparam>
		template<class T>
		static constexpr bool is_emu_vector_v = is_emu_vector<T>::value;

		/// <summary> Determines if the passed template type T taking 1 typeparam is an EmuMath Vector. </summary>
		template<template<class> class T>
		struct is_emu_vector_template
		{
			static constexpr bool value = false;
		};
		template<>
		struct is_emu_vector_template<Vector2>
		{
			static constexpr bool value = true;
		};
		template<>
		struct is_emu_vector_template<Vector3>
		{
			static constexpr bool value = true;
		};
		template<>
		struct is_emu_vector_template<Vector4>
		{
			static constexpr bool value = true;
		};
		/// <summary> Boolean indicating if the passed template type T taking 1 typeparam is an EmuMath Vector. </summary>
		template<template<class> class T>
		static constexpr bool is_emu_vector_template_v = is_emu_vector_template<T>::value;

		/// <summary>
		/// <para> Determines an EmuMath Vector type with the provided Size_ of elements of the provided ContainedType. </para>
		/// <para> The only valid values for Size_ are 2, 3, and 4; everything else will result in a static assertion being triggered. </para>
		/// </summary>
		/// <typeparam name="ContainedType">Type contained within the resulting Vector.</typeparam>
		template<std::size_t Size_, typename ContainedType>
		struct emu_vector_from_size
		{
			static_assert
			(
				Size_ == 2 || Size_ == 3 || Size_ == 4,
				"Invalid size provided to emu_vector_from_size. Only 2, 3, and 4 are valid values."
			);

			using type = std::conditional_t
			<
				Size_ == 2,
				Vector2<ContainedType>,
				std::conditional_t
				<
					Size_ == 3,
					Vector3<ContainedType>,
					std::conditional_t
					<
						Size_ == 4,
						Vector4<ContainedType>,
						std::false_type
					>
				>
			>;
		};
		/// <summary>
		/// <para> EmuMath Vector type of the provided Size_ containing the provided ContainedType. </para>
		/// <para> The only valid values for Size_ are 2, 3, and 4; everything else will result in a static assertion being triggered. </para>
		/// </summary>
		/// <typeparam name="ContainedType">Type contained within the resulting Vector.</typeparam>
		template<std::size_t Size_, typename ContainedType>
		using emu_vector_from_size_t = typename emu_vector_from_size<Size_, ContainedType>::type;

		/// <summary> Helper for arbitrarily accessing X, Y, Z or W of an EmuMath Vector, representing non-contained values as the stored type's zero. </summary>
		/// <typeparam name="EmuVec_">Type of EmuMath vector to get the element from.</typeparam>
		template<class EmuVec__>
		struct emu_vector_get_element
		{
			using _non_qualified_vec = std::remove_cv_t<EmuVec__>;
			static constexpr bool _is_emu_vector = EmuMath::TMPHelpers::is_emu_vector_v<_non_qualified_vec>;
			static_assert
			(
				_is_emu_vector,
				"Failed to retrieve an element from an EmuMath::Vector type as the passed type was not an EmuMath::Vector."
			);
			using _temp_value_type = typename _non_qualified_vec::value_type;
			using _value_type = std::conditional_t<_is_emu_vector, _temp_value_type, int>;

			static constexpr bool _has_z = _non_qualified_vec::size() >= 3;
			static constexpr bool _has_w = _non_qualified_vec::size() >= 4;

			using _ref_value_type = typename EmuMath::_info::VectorInfo<_value_type>::ref_value_type;
			using _const_ref_value_type = typename EmuMath::_info::VectorInfo<_value_type>::const_ref_value_type;
			using _nonref_value_type = typename EmuMath::_info::VectorInfo<_value_type>::nonref_value_type;

			using _out_x = _ref_value_type;
			using _out_y = _ref_value_type;
			using _out_z = std::conditional_t<_has_z, _ref_value_type, _nonref_value_type>;
			using _out_w = std::conditional_t<_has_w, _ref_value_type, _nonref_value_type>;

			using _out_const_x = _const_ref_value_type;
			using _out_const_y = _const_ref_value_type;
			using _out_const_z = std::conditional_t<_has_z, _const_ref_value_type, _nonref_value_type>;
			using _out_const_w = std::conditional_t<_has_w, _const_ref_value_type, _nonref_value_type>;

			static constexpr _out_x X(_non_qualified_vec& vec_)
			{
				return vec_.x;
			}
			static constexpr _out_const_x X(const _non_qualified_vec& vec_)
			{
				return vec_.x;
			}
			static constexpr _out_y Y(_non_qualified_vec& vec_)
			{
				return vec_.y;
			}
			static constexpr _out_const_y Y(const _non_qualified_vec& vec_)
			{
				return vec_.y;
			}
			static constexpr _out_z Z(_non_qualified_vec& vec_)
			{
				if constexpr (_has_z)
				{
					return vec_.z;
				}
				else
				{
					return EmuCore::ArithmeticHelpers::ZeroT<_nonref_value_type>;
				}
			}
			static constexpr _out_const_z Z(const _non_qualified_vec& vec_)
			{
				if constexpr (_has_z)
				{
					return vec_.z;
				}
				else
				{
					return EmuCore::ArithmeticHelpers::ZeroT<_nonref_value_type>;
				}
			}
			static constexpr _out_w W(_non_qualified_vec& vec_)
			{
				if constexpr (_has_w)
				{
					return vec_.w;
				}
				else
				{
					return EmuCore::ArithmeticHelpers::ZeroT<_nonref_value_type>;
				}
			}
			static constexpr _out_const_w W(const _non_qualified_vec& vec_)
			{
				if constexpr (_has_w)
				{
					return vec_.w;
				}
				else
				{
					return EmuCore::ArithmeticHelpers::ZeroT<_nonref_value_type>;
				}
			}
		};
		/// <summary> Returns a reference to the passed Vector's x element. </summary>
		/// <typeparam name="EmuVec_">Type of EmuMath Vector to retrieve the x element of.</typeparam>
		/// <param name="vec_">EmuMath Vector to retrieve the x element of.</param>
		/// <returns>Reference to the passed Vector's x element.</returns>
		template<typename EmuVec_>
		static constexpr typename emu_vector_get_element<EmuVec_>::_out_x emu_vector_x(EmuVec_& vec_)
		{
			return emu_vector_get_element<EmuVec_>::X(vec_);
		}
		/// <summary> Returns a constant reference to the passed Vector's x element. </summary>
		/// <typeparam name="EmuVec_">Type of EmuMath Vector to retrieve the x element of.</typeparam>
		/// <param name="vec_">EmuMath Vector to retrieve the x element of.</param>
		/// <returns>Constant reference to the passed Vector's x element.</returns>
		template<typename EmuVec_>
		static constexpr typename emu_vector_get_element<EmuVec_>::_out_const_x emu_vector_x(const EmuVec_& vec_)
		{
			return emu_vector_get_element<EmuVec_>::X(vec_);
		}
		/// <summary> Returns a reference to the passed Vector's y element. </summary>
		/// <typeparam name="EmuVec_">Type of EmuMath Vector to retrieve the y element of.</typeparam>
		/// <param name="vec_">EmuMath Vector to retrieve the y element of.</param>
		/// <returns>Reference to the passed Vector's y element.</returns>
		template<typename EmuVec_>
		static constexpr typename emu_vector_get_element<EmuVec_>::_out_y emu_vector_y(EmuVec_& vec_)
		{
			return emu_vector_get_element<EmuVec_>::Y(vec_);
		}
		/// <summary> Returns a constant reference to the passed Vector's y element. </summary>
		/// <typeparam name="EmuVec_">Type of EmuMath Vector to retrieve the y element of.</typeparam>
		/// <param name="vec_">EmuMath Vector to retrieve the y element of.</param>
		/// <returns>Constant reference to the passed Vector's y element.</returns>
		template<typename EmuVec_>
		static constexpr typename emu_vector_get_element<EmuVec_>::_out_const_y emu_vector_y(const EmuVec_& vec_)
		{
			return emu_vector_get_element<EmuVec_>::Y(vec_);
		}
		/// <summary>
		/// Returns a reference to the passed Vector's z element if it has one, or a zero-initialised item of the Vector's contained type if it does not have one.
		/// </summary>
		/// <typeparam name="EmuVec_">Type of EmuMath Vector to retrieve the z element of.</typeparam>
		/// <param name="vec_">EmuMath Vector to retrieve the z element of.</param>
		/// <returns>Reference to the passed Vector's z element, or a zero-initialised item of the Vector's contained type if it does not have one.</returns>
		template<typename EmuVec_>
		static constexpr typename emu_vector_get_element<EmuVec_>::_out_z emu_vector_z(EmuVec_& vec_)
		{
			return emu_vector_get_element<EmuVec_>::Z(vec_);
		}
		/// <summary>
		/// Returns a constant reference to the passed Vector's z element if it has one, or a zero-initialised item of the Vector's contained type if it does not have one.
		/// </summary>
		/// <typeparam name="EmuVec_">Type of EmuMath Vector to retrieve the z element of.</typeparam>
		/// <param name="vec_">EmuMath Vector to retrieve the z element of.</param>
		/// <returns>Constant reference to the passed Vector's z element, or a zero-initialised item of the Vector's contained type if it does not have one.</returns>
		template<typename EmuVec_>
		static constexpr typename emu_vector_get_element<EmuVec_>::_out_const_z emu_vector_z(const EmuVec_& vec_)
		{
			return emu_vector_get_element<EmuVec_>::Z(vec_);
		}
		/// <summary>
		/// Returns a reference to the passed Vector's w element if it has one, or a zero-initialised item of the Vector's contained type if it does not have one.
		/// </summary>
		/// <typeparam name="EmuVec_">Type of EmuMath Vector to retrieve the w element of.</typeparam>
		/// <param name="vec_">EmuMath Vector to retrieve the w element of.</param>
		/// <returns>Reference to the passed Vector's w element, or a zero-initialised item of the Vector's contained type if it does not have one.</returns>
		template<typename EmuVec_>
		static constexpr typename emu_vector_get_element<EmuVec_>::_out_w emu_vector_w(EmuVec_& vec_)
		{
			return emu_vector_get_element<EmuVec_>::W(vec_);
		}
		/// <summary>
		/// Returns a constant reference to the passed Vector's w element if it has one, or a zero-initialised item of the Vector's contained type if it does not have one.
		/// </summary>
		/// <typeparam name="EmuVec_">Type of EmuMath Vector to retrieve the w element of.</typeparam>
		/// <param name="vec_">EmuMath Vector to retrieve the w element of.</param>
		/// <returns>Constant reference to the passed Vector's w element, or a zero-initialised item of the Vector's contained type if it does not have one.</returns>
		template<typename EmuVec_>
		static constexpr typename emu_vector_get_element<EmuVec_>::_out_const_w emu_vector_w(const EmuVec_& vec_)
		{
			return emu_vector_get_element<EmuVec_>::W(vec_);
		}
	}
}

#endif
