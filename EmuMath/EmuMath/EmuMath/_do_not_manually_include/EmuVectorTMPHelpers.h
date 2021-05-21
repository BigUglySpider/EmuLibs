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

		/// <summary>
		///	<para> Finds the type used to create a copy of the passed EmuMath Vector type. If the passed type is not an EmuMath vector, the type will be std::false_type. </para>
		/// <para> This copy type is primarily used to consistently get non-reference copies from EmuMath Vectors containing references. </para>
		/// </summary>
		/// <typeparam name="EmuVector_">EmuMath Vector type to get the copy type of.</typeparam>
		template<typename EmuVector_>
		struct emu_vector_copy
		{
		private:
			static constexpr bool _is_valid = EmuMath::TMPHelpers::is_emu_vector_v<EmuVector_>;

		public:
			static_assert(_is_valid, "Attempted to get the copy type for an EmuMath Vector using a type that is not an EmuMath Vector.");

			using type = std::conditional_t
			<
				_is_valid,
				EmuMath::TMPHelpers::emu_vector_from_size_t<EmuVector_::size(), typename EmuVector_::nonref_value_type_without_qualifiers>,
				std::false_type
			>;
		};
		/// <summary>
		/// <para> Type used to create a copy of the passed EmuMath Vector type. If the passed type is not an EmuMath vector, this will be std::false_type. </para>
		/// <para> This copy type is primarily used to consistently get non-reference copies from EmuMath Vectors containing references. </para>
		/// </summary>
		/// <typeparam name="EmuVector_">EmuMath Vector type to get the copy type of.</typeparam>
		template<typename EmuVector_>
		using emu_vector_copy_t = typename emu_vector_copy<EmuVector_>::type;

		template<typename LhsVector_, typename RhsVector_>
		struct emu_vector_with_most_elements
		{
		private:
			static constexpr bool _is_valid = EmuCore::TMPHelpers::are_all_check<EmuMath::TMPHelpers::is_emu_vector_v, LhsVector_, RhsVector_>::value;

		public:
			static_assert(_is_valid, "Attempted to find the EmuMath VEctor type with the most elements using at least one type that is not an EmuMath Vector.");

			using type = std::conditional_t
			<
				_is_valid,
				std::conditional_t<(LhsVector_::size() >= RhsVector_::size()), LhsVector_, RhsVector_>,
				std::false_type
			>;
		};
		template<typename LhsVector_, typename RhsVector_>
		using emu_vector_with_most_elements_t = typename emu_vector_with_most_elements<LhsVector_, RhsVector_>::type;

		/// <summary> Helper for arbitrarily accessing X, Y, Z or W of an EmuMath Vector, representing non-contained values as a copy of the stored type's zero. </summary>
		/// <typeparam name="EmuVec_">Type of EmuMath vector to get the element from.</typeparam>
		template<class EmuVec__>
		struct emu_vector_get_element
		{
		private:
			using _non_qualified_vec = std::remove_cv_t<EmuVec__>;
			static constexpr bool _is_emu_vector = EmuMath::TMPHelpers::is_emu_vector_v<_non_qualified_vec>;
			static_assert
			(
				_is_emu_vector,
				"Failed to retrieve an element from an EmuMath::Vector type as the passed type was not an EmuMath::Vector."
			);
			using _value_type = std::conditional_t<_is_emu_vector, typename _non_qualified_vec::value_type, int>;

			static constexpr bool _has_z = _non_qualified_vec::size() >= 3;
			static constexpr bool _has_w = _non_qualified_vec::size() >= 4;

			using _ref_value_type = typename EmuMath::_info::VectorInfo<_value_type>::ref_value_type;
			using _const_ref_value_type = typename EmuMath::_info::VectorInfo<_value_type>::const_ref_value_type;
			using _nonref_value_type = typename EmuMath::_info::VectorInfo<_value_type>::nonref_value_type;

		public:
			using out_x = _ref_value_type;
			using out_y = _ref_value_type;
			using out_z = std::conditional_t<_has_z, _ref_value_type, _nonref_value_type>;
			using out_w = std::conditional_t<_has_w, _ref_value_type, _nonref_value_type>;

			using out_const_x = _const_ref_value_type;
			using out_const_y = _const_ref_value_type;
			using out_const_z = std::conditional_t<_has_z, _const_ref_value_type, _nonref_value_type>;
			using out_const_w = std::conditional_t<_has_w, _const_ref_value_type, _nonref_value_type>;

			static constexpr out_x X(_non_qualified_vec& vec_)
			{
				return vec_.x;
			}
			static constexpr out_const_x X(const _non_qualified_vec& vec_)
			{
				return vec_.x;
			}
			static constexpr out_y Y(_non_qualified_vec& vec_)
			{
				return vec_.y;
			}
			static constexpr out_const_y Y(const _non_qualified_vec& vec_)
			{
				return vec_.y;
			}
			static constexpr out_z Z(_non_qualified_vec& vec_)
			{
				if constexpr (_has_z)
				{
					return vec_.z;
				}
				else
				{
					return out_const_z();
				}
			}
			static constexpr out_const_z Z(const _non_qualified_vec& vec_)
			{
				if constexpr (_has_z)
				{
					return vec_.z;
				}
				else
				{
					return out_const_z();
				}
			}
			static constexpr out_w W(_non_qualified_vec& vec_)
			{
				if constexpr (_has_w)
				{
					return vec_.w;
				}
				else
				{
					return out_const_w();
				}
			}
			static constexpr out_const_w W(const _non_qualified_vec& vec_)
			{
				if constexpr (_has_w)
				{
					return vec_.w;
				}
				else
				{
					return out_const_w();
				}
			}
		};
		/// <summary> Returns a reference to the passed Vector's x element. </summary>
		/// <typeparam name="EmuVec_">Type of EmuMath Vector to retrieve the x element of.</typeparam>
		/// <param name="vec_">EmuMath Vector to retrieve the x element of.</param>
		/// <returns>Reference to the passed Vector's x element.</returns>
		template<typename EmuVec_>
		inline constexpr typename emu_vector_get_element<EmuVec_>::out_x emu_vector_x(EmuVec_& vec_)
		{
			return emu_vector_get_element<EmuVec_>::X(vec_);
		}
		/// <summary> Returns a constant reference to the passed Vector's x element. </summary>
		/// <typeparam name="EmuVec_">Type of EmuMath Vector to retrieve the x element of.</typeparam>
		/// <param name="vec_">EmuMath Vector to retrieve the x element of.</param>
		/// <returns>Constant reference to the passed Vector's x element.</returns>
		template<typename EmuVec_>
		inline constexpr typename emu_vector_get_element<EmuVec_>::out_const_x emu_vector_x(const EmuVec_& vec_)
		{
			return emu_vector_get_element<EmuVec_>::X(vec_);
		}
		/// <summary> Returns a reference to the passed Vector's y element. </summary>
		/// <typeparam name="EmuVec_">Type of EmuMath Vector to retrieve the y element of.</typeparam>
		/// <param name="vec_">EmuMath Vector to retrieve the y element of.</param>
		/// <returns>Reference to the passed Vector's y element.</returns>
		template<typename EmuVec_>
		inline constexpr typename emu_vector_get_element<EmuVec_>::out_y emu_vector_y(EmuVec_& vec_)
		{
			return emu_vector_get_element<EmuVec_>::Y(vec_);
		}
		/// <summary> Returns a constant reference to the passed Vector's y element. </summary>
		/// <typeparam name="EmuVec_">Type of EmuMath Vector to retrieve the y element of.</typeparam>
		/// <param name="vec_">EmuMath Vector to retrieve the y element of.</param>
		/// <returns>Constant reference to the passed Vector's y element.</returns>
		template<typename EmuVec_>
		inline constexpr typename emu_vector_get_element<EmuVec_>::out_const_y emu_vector_y(const EmuVec_& vec_)
		{
			return emu_vector_get_element<EmuVec_>::Y(vec_);
		}
		/// <summary>
		/// Returns a reference to the passed Vector's z element if it has one, or a default constructed item of the Vector's contained type if it does not have one.
		/// </summary>
		/// <typeparam name="EmuVec_">Type of EmuMath Vector to retrieve the z element of.</typeparam>
		/// <param name="vec_">EmuMath Vector to retrieve the z element of.</param>
		/// <returns>Reference to the passed Vector's z element, or a zero-initialised item of the Vector's contained type if it does not have one.</returns>
		template<typename EmuVec_>
		inline constexpr typename emu_vector_get_element<EmuVec_>::out_z emu_vector_z(EmuVec_& vec_)
		{
			return emu_vector_get_element<EmuVec_>::Z(vec_);
		}
		/// <summary>
		/// Returns a constant reference to the passed Vector's z element if it has one, or a default constructed item of the Vector's contained type if it does not have one.
		/// </summary>
		/// <typeparam name="EmuVec_">Type of EmuMath Vector to retrieve the z element of.</typeparam>
		/// <param name="vec_">EmuMath Vector to retrieve the z element of.</param>
		/// <returns>Constant reference to the passed Vector's z element, or a zero-initialised item of the Vector's contained type if it does not have one.</returns>
		template<typename EmuVec_>
		inline constexpr typename emu_vector_get_element<EmuVec_>::out_const_z emu_vector_z(const EmuVec_& vec_)
		{
			return emu_vector_get_element<EmuVec_>::Z(vec_);
		}
		/// <summary>
		/// Returns a reference to the passed Vector's w element if it has one, or a default constructed item of the Vector's contained type if it does not have one.
		/// </summary>
		/// <typeparam name="EmuVec_">Type of EmuMath Vector to retrieve the w element of.</typeparam>
		/// <param name="vec_">EmuMath Vector to retrieve the w element of.</param>
		/// <returns>Reference to the passed Vector's w element, or a zero-initialised item of the Vector's contained type if it does not have one.</returns>
		template<typename EmuVec_>
		inline constexpr typename emu_vector_get_element<EmuVec_>::out_w emu_vector_w(EmuVec_& vec_)
		{
			return emu_vector_get_element<EmuVec_>::W(vec_);
		}
		/// <summary>
		/// Returns a constant reference to the passed Vector's w element if it has one, or a default constructed item of the Vector's contained type if it does not have one.
		/// </summary>
		/// <typeparam name="EmuVec_">Type of EmuMath Vector to retrieve the w element of.</typeparam>
		/// <param name="vec_">EmuMath Vector to retrieve the w element of.</param>
		/// <returns>Constant reference to the passed Vector's w element, or a zero-initialised item of the Vector's contained type if it does not have one.</returns>
		template<typename EmuVec_>
		static constexpr typename emu_vector_get_element<EmuVec_>::out_const_w emu_vector_w(const EmuVec_& vec_)
		{
			return emu_vector_get_element<EmuVec_>::W(vec_);
		}

		template<std::size_t N_, class EmuVec_>
		inline constexpr auto emu_vector_element_n(const EmuVec_& vec_)
		{
			if constexpr (EmuMath::TMPHelpers::is_emu_vector_v<EmuVec_>)
			{
				if constexpr (N_ == 0)
				{
					return emu_vector_x(vec_);
				}
				else if constexpr (N_ == 1)
				{
					return emu_vector_y(vec_);
				}
				else if constexpr (N_ == 2)
				{
					return emu_vector_z(vec_);
				}
				else if constexpr (N_ == 3)
				{
					return emu_vector_w(vec_);
				}
				else
				{
					static_assert(false, "Attempted to get element N of an EmuMath Vector with an invalid N value. Only 0, 1, 2, and 3 are valid values.");
				}
			}
			else
			{
				static_assert(false, "Attempted to get element N of an EmuMath Vector, but the passed operand was not an EmuMath Vector.");
			}
		}
	}
}

#endif
