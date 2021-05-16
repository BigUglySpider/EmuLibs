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

		template<typename T>
		struct is_emu_vector
		{
		private:
			using _value_type = typename T::value_type;

		public:
			static constexpr bool value = EmuCore::TMPHelpers::is_any_same_v
			<
				T,
				EmuMath::Vector2<_value_type>,
				EmuMath::Vector3<_value_type>,
				EmuMath::Vector4<_value_type>
			>;
		};
		template<typename T>
		static constexpr bool is_emu_vector_v = is_emu_vector<T>::value;

		template<template<typename> typename T, typename DummyTemplateParam_ = int>
		static constexpr bool is_emu_vector_template_v = EmuCore::TMPHelpers::is_any_same_v
		<
			T<DummyTemplateParam_>,
			EmuMath::Vector2<DummyTemplateParam_>,
			EmuMath::Vector3<DummyTemplateParam_>,
			EmuMath::Vector4<DummyTemplateParam_>
		>;

		template<std::size_t Size_, typename ContainedType>
		struct emu_vector_from_size
		{
			static_assert(Size_ == 2 || Size_ == 3, "Invalid size provided to emu_vector_from_size. Only 2 and 3 are valid values.");

			using type = std::conditional_t
			<
				Size_ == 2,
				Vector2<ContainedType>,
				std::conditional_t
				<
				Size_ == 3,
				Vector3<ContainedType>,
				std::false_type
				>
			>;
		};
		template<std::size_t Size_, typename ContainedType>
		using emu_vector_from_size_t = typename emu_vector_from_size<Size_, ContainedType>::type;

		/// <summary> Helper for arbitrarily accessing X, Y, Z or W of an EmuMath Vector, representing non-contained values as the stored type's zero. </summary>
		/// <typeparam name="EmuVec_">Type of EmuMath vector to get the element from.</typeparam>
		template<typename EmuVec__>
		struct emu_vector_get_element
		{
			using _non_qualified_vec = std::remove_cv_t<EmuVec__>;
			using _temp_value_type = typename _non_qualified_vec::value_type;
			static constexpr bool _is_emu_vector = EmuMath::TMPHelpers::is_emu_vector_v<_non_qualified_vec>;
			static_assert
			(
				_is_emu_vector,
				"Failed to retrieve an element from an EmuMath::Vector type as the passed type was not an EmuMath::Vector."
			);
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
		template<typename EmuVec_>
		static constexpr typename emu_vector_get_element<EmuVec_>::_out_x emu_vector_x(EmuVec_& vec_)
		{
			return emu_vector_get_element<EmuVec_>::X(vec_);
		}
		template<typename EmuVec_>
		static constexpr typename emu_vector_get_element<EmuVec_>::_out_const_x emu_vector_x(const EmuVec_& vec_)
		{
			return emu_vector_get_element<EmuVec_>::X(vec_);
		}
		template<typename EmuVec_>
		static constexpr typename emu_vector_get_element<EmuVec_>::_out_y emu_vector_y(EmuVec_& vec_)
		{
			return emu_vector_get_element<EmuVec_>::Y(vec_);
		}
		template<typename EmuVec_>
		static constexpr typename emu_vector_get_element<EmuVec_>::_out_const_y emu_vector_y(const EmuVec_& vec_)
		{
			return emu_vector_get_element<EmuVec_>::Y(vec_);
		}
		template<typename EmuVec_>
		static constexpr typename emu_vector_get_element<EmuVec_>::_out_z emu_vector_z(EmuVec_& vec_)
		{
			return emu_vector_get_element<EmuVec_>::Z(vec_);
		}
		template<typename EmuVec_>
		static constexpr typename emu_vector_get_element<EmuVec_>::_out_const_z emu_vector_z(const EmuVec_& vec_)
		{
			return emu_vector_get_element<EmuVec_>::Z(vec_);
		}
		template<typename EmuVec_>
		static constexpr typename emu_vector_get_element<EmuVec_>::_out_w emu_vector_w(EmuVec_& vec_)
		{
			return emu_vector_get_element<EmuVec_>::W(vec_);
		}
		template<typename EmuVec_>
		static constexpr typename emu_vector_get_element<EmuVec_>::_out_const_w emu_vector_w(const EmuVec_& vec_)
		{
			return emu_vector_get_element<EmuVec_>::W(vec_);
		}
	}
}

#endif
