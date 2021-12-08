#ifndef EMU_MATH_NEW_VECTOR_GET_UNDERLYING_H_INC_
#define EMU_MATH_NEW_VECTOR_GET_UNDERLYING_H_INC_ 1

#include "_vector_tmp.h"

namespace EmuMath::Helpers::_vector_underlying
{
	template<class Vector_, typename = std::enable_if_t<EmuMath::TMP::is_emu_new_vector_v<Vector_>>>
	[[nodiscard]] constexpr inline typename Vector_::value_type_uq _vector_get_non_contained_value()
	{
		using out_type = typename Vector_::value_type_uq;
		if constexpr (std::is_default_constructible_v<out_type>)
		{
			return out_type();
		}
		else if constexpr (std::is_constructible_v<out_type, decltype(0)>)
		{
			return out_type(0);
		}
		else if constexpr (std::is_constructible_v<out_type, decltype(0.0)>)
		{
			return out_type(0.0);
		}
		else
		{
			static_assert(false, "Attempted to safely retrieve a non-contained value from an EmuMath Vector, but the contained type cannot be default-constructed or constructed with an argument of either `0` or `0.0`. As non-contained elements are implied default/zero, this behaviour is required to safely retrieve a non-contained element.");
		}
	}
	template<std::size_t Size_, typename T_>
	[[nodiscard]] constexpr inline typename EmuMath::NewVector<Size_, T_>::value_type_uq _vector_get_non_contained_value()
	{
		return _vector_get_non_contained_value<EmuMath::NewVector<Size_, T_>>();
	}

	template<std::size_t Index_, std::size_t Size_, typename T_>
	[[nodiscard]] constexpr inline typename EmuMath::NewVector<Size_, T_>::value_type& _vector_get(EmuMath::NewVector<Size_, T_>& vector_)
	{
		return vector_.template at<Index_>();
	}
	template<std::size_t Index_, std::size_t Size_, typename T_>
	[[nodiscard]] constexpr inline const typename EmuMath::NewVector<Size_, T_>::value_type& _vector_get(const EmuMath::NewVector<Size_, T_>& vector_)
	{
		return vector_.template at<Index_>();
	}

	template<std::size_t Size_, typename T_>
	[[nodiscard]] constexpr inline typename EmuMath::NewVector<Size_, T_>::value_type& _vector_get
	(
		EmuMath::NewVector<Size_, T_>& vector_,
		std::size_t index_
	)
	{
		return vector_.at(index_);
	}
	template<std::size_t Size_, typename T_>
	[[nodiscard]] constexpr inline const typename EmuMath::NewVector<Size_, T_>::value_type& _vector_get
	(
		const EmuMath::NewVector<Size_, T_>& vector_,
		std::size_t index_
	)
	{
		return vector_.at(index_);
	}

	template<std::size_t Index_, std::size_t Size_, typename T_>
	[[nodiscard]] constexpr inline const EmuMath::TMP::emu_vector_from_args_theoretical_return_t<Index_, Size_, T_> _vector_get_theoretical
	(
		EmuMath::NewVector<Size_, T_>& vector_
	)
	{
		if constexpr (Index_ < EmuMath::NewVector<Size_, T_>::size)
		{
			return vector_.template at<Index_>();
		}
		else
		{
			return _vector_get_non_contained_value<Size_, T_>();
		}
	}
	template<std::size_t Index_, std::size_t Size_, typename T_>
	[[nodiscard]] constexpr inline const EmuMath::TMP::emu_const_vector_from_args_theoretical_return_t<Index_, Size_, T_> _vector_get_theoretical
	(
		const EmuMath::NewVector<Size_, T_>& vector_
	)
	{
		if constexpr (Index_ < EmuMath::NewVector<Size_, T_>::size)
		{
			return vector_.template at<Index_>();
		}
		else
		{
			return _vector_get_non_contained_value<Size_, T_>();
		}
	}
}

#endif
