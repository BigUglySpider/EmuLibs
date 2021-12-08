#ifndef EMU_MATH_NEW_VECTOR_GET_H_INC_
#define EMU_MATH_NEW_VECTOR_GET_H_INC_ 1

#include "_common_vector_helpers.h"

namespace EmuMath::Helpers
{
	/// <summary>
	/// <para> Generation used to safely acquire a non-contained value from an EmuMath Vector. </para>
	/// <para> The Vector's value_type_uq must be one of the following, with earlier listed items taking top priority: </para>
	/// <para> 1: Default-constructible </para>
	/// <para> 2: Constructible with an integral value of 0. </para>
	/// <para> 3: Constructible with an floating-point value of 0.0. </para>
	/// <para> If none of the above conditions are met, this will generate a compile-time error. </para>
	/// </summary>
	/// <returns>Value for any non-contained index of an EmuMath Vector created with the provided template parameters.</returns>
	template<std::size_t Size_, typename T_>
	[[nodiscard]] constexpr inline typename EmuMath::NewVector<Size_, T_>::value_type_uq new_vector_get_non_contained()
	{
		return _vector_underlying::_vector_get_non_contained_value<Size_, T_>();
	}
	template<class Vector_, typename = std::enable_if_t<EmuMath::TMP::is_emu_new_vector_v<Vector_>>>
	[[nodiscard]] constexpr inline typename Vector_::value_type_uq new_vector_get_non_contained()
	{
		return _vector_underlying::_vector_get_non_contained_value<Vector_>();
	}

	template<std::size_t Index_, std::size_t Size_, typename T_>
	[[nodiscard]] constexpr inline typename EmuMath::NewVector<Size_, T_>::value_type& new_vector_get(EmuMath::NewVector<Size_, T_>& vector_)
	{
		return _vector_underlying::_vector_get<Index_, Size_, T_>(vector_);
	}
	template<std::size_t Index_, std::size_t Size_, typename T_>
	[[nodiscard]] constexpr inline const typename EmuMath::NewVector<Size_, T_>::value_type& new_vector_get(const EmuMath::NewVector<Size_, T_>& vector_)
	{
		return _vector_underlying::_vector_get<Index_, Size_, T_>(vector_);
	}

	template<std::size_t Size_, typename T_>
	[[nodiscard]] constexpr inline typename EmuMath::NewVector<Size_, T_>::value_type& new_vector_get
	(
		EmuMath::NewVector<Size_, T_>& vector_,
		std::size_t index_
	)
	{
		return _vector_underlying::_vector_get<Size_, T_>(vector_, index_);
	}
	template<std::size_t Size_, typename T_>
	[[nodiscard]] constexpr inline const typename EmuMath::NewVector<Size_, T_>::value_type& new_vector_get
	(
		const EmuMath::NewVector<Size_, T_>& vector_,
		std::size_t index_
	)
	{
		return _vector_underlying::_vector_get<Size_, T_>(vector_, index_);
	}

	template<std::size_t Index_, std::size_t Size_, typename T_>
	[[nodiscard]] constexpr inline const EmuMath::TMP::emu_vector_from_args_theoretical_return_t<Index_, Size_, T_> new_vector_get_theoretical
	(
		EmuMath::NewVector<Size_, T_>& vector_
	)
	{
		return _vector_underlying::_vector_get_theoretical<Index_, Size_, T_>(vector_);
	}
	template<std::size_t Index_, std::size_t Size_, typename T_>
	[[nodiscard]] constexpr inline const EmuMath::TMP::emu_const_vector_from_args_theoretical_return_t<Index_, Size_, T_> new_vector_get_theoretical
	(
		const EmuMath::NewVector<Size_, T_>& vector_
	)
	{
		return _vector_underlying::_vector_get_theoretical<Index_, Size_, T_>(vector_);
	}
}

#endif
