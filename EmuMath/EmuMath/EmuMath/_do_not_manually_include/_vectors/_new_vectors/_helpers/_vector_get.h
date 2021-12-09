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

	/// <summary>
	/// <para> Retrieves a reference to the element at the specified Index_ within the provided EmuMath Vector. </para>
	/// <para> The valid Index_ range for the provided Vector is 0:Vector::size-1 (inclusive). Invalid indices will generate a compile-time error. </para>
	/// <para> 
	///		This will always provided a value_type reference; this may not be used to directly access the vector's stored_type 
	///		(it should be noted that this is the same as accessing a stored_type for Vectors that do not contain references).
	/// </para>
	/// </summary>
	/// <param name="vector_">EmuMath Vector to access the specified Index_ of.</param>
	/// <returns>Reference to the provided EmuMath Vector's value_type located at the specified Index_ within the passed Vector.</returns>
	template<std::size_t Index_, std::size_t Size_, typename T_>
	[[nodiscard]] constexpr inline typename EmuMath::NewVector<Size_, T_>::value_type& new_vector_get(EmuMath::NewVector<Size_, T_>& vector_)
	{
		return _vector_underlying::_vector_get<Index_, Size_, T_>(vector_);
	}

	/// <summary>
	/// <para> Retrieves a constant reference to the element at the specified Index_ within the provided EmuMath Vector. </para>
	/// <para> The valid Index_ range for the provided Vector is 0:Vector::size-1 (inclusive). Invalid indices will generate a compile-time error. </para>
	/// <para> 
	///		This will always provided a const value_type reference; this may not be used to directly access the vector's stored_type 
	///		(it should be noted that this is the same as accessing a const stored_type for Vectors that do not contain references).
	/// </para>
	/// </summary>
	/// <param name="vector_">EmuMath Vector to access the specified Index_ of.</param>
	/// <returns>Constant reference to the provided EmuMath Vector's value_type located at the specified Index_ within the passed Vector.</returns>
	template<std::size_t Index_, std::size_t Size_, typename T_>
	[[nodiscard]] constexpr inline const typename EmuMath::NewVector<Size_, T_>::value_type& new_vector_get(const EmuMath::NewVector<Size_, T_>& vector_)
	{
		return _vector_underlying::_vector_get<Index_, Size_, T_>(vector_);
	}

	/// <summary>
	/// <para> Retrieves a reference to the element at the specified index_ within the provided EmuMath Vector. </para>
	/// <para> The valid index_ range for the provided Vector is 0:Vector::size-1 (inclusive). Invalid index behaviour is undefined. </para>
	/// <para>
	///		If index_ is known at compile time, it is recommended to use the version of this function which takes a template Index_ argument instead, 
	///		as that function has well-defined behaviours for invalid index accesses.
	/// </para>
	/// <para> 
	///		This will always provided a value_type reference; this may not be used to directly access the vector's stored_type 
	///		(it should be noted that this is the same as accessing a stored_type for Vectors that do not contain references).
	/// </para>
	/// </summary>
	/// <param name="vector_">EmuMath Vector to access the specified Index_ of.</param>
	/// <returns>Reference to the provided EmuMath Vector's value_type located at the specified Index_ within the passed Vector.</returns>
	template<std::size_t Size_, typename T_>
	[[nodiscard]] constexpr inline typename EmuMath::NewVector<Size_, T_>::value_type& new_vector_get
	(
		EmuMath::NewVector<Size_, T_>& vector_,
		std::size_t index_
	)
	{
		return _vector_underlying::_vector_get<Size_, T_>(vector_, index_);
	}

	/// <summary>
	/// <para> Retrieves a constant reference to the element at the specified index_ within the provided EmuMath Vector. </para>
	/// <para> The valid index_ range for the provided Vector is 0:Vector::size-1 (inclusive). Invalid index behaviour is undefined. </para>
	/// <para>
	///		If index_ is known at compile time, it is recommended to use the version of this function which takes a template Index_ argument instead, 
	///		as that function has well-defined behaviours for invalid index accesses.
	/// </para>
	/// <para> 
	///		This will always provided a value_type reference; this may not be used to directly access the vector's stored_type 
	///		(it should be noted that this is the same as accessing a stored_type for Vectors that do not contain references).
	/// </para>
	/// </summary>
	/// <param name="vector_">EmuMath Vector to access the specified Index_ of.</param>
	/// <returns>Constant reference to the provided EmuMath Vector's value_type located at the specified Index_ within the passed Vector.</returns>
	template<std::size_t Size_, typename T_>
	[[nodiscard]] constexpr inline const typename EmuMath::NewVector<Size_, T_>::value_type& new_vector_get
	(
		const EmuMath::NewVector<Size_, T_>& vector_,
		std::size_t index_
	)
	{
		return _vector_underlying::_vector_get<Size_, T_>(vector_, index_);
	}

	/// <summary>
	/// <para> Retrieves a theoretical element at the specified Index_ within the provided EmuMath Vector. </para>
	/// <para> If the provided Index_ is within the Vector's valid index range (0:Vector::size-1 (inclusive)): Returns a reference to the specified element. </para>
	/// <para> If the provided Index_ is outside of the Vector's valid index range: Returns an implied-zero value of the Vector's value_type_uq (unqualified value_type). </para>
	/// <para> The return type of this function may be found ahead of time via the `EmuMath::TMP::emu_vector_from_args_theoretical_return_t` template. </para>
	/// </summary>
	/// <param name="vector_">EmuMath Vector to access the specified theoretical Index_ of.</param>
	/// <returns>Result of vector_get&lt;Index_&gt; if Index_ is within the valid index range; otherwise, result of vector_get_non_contained for the provided Vector.</returns>
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

	/// <summary>
	/// <para> Retrieves a pointer to the contiguous data stored within the passed EmuMath Vector. </para>
	/// <para> This behaviour is prohibited with reference-containing Vectors by default. </para>
	/// </summary>
	/// <param name="vector_">EmuMath Vector to retrieve a data pointer for.</param>
	/// <returns>Pointer to the start of the provided EmuMath Vector's contiguous data.</returns>
	template<std::size_t Size_, typename T_>
	[[nodiscard]] constexpr inline typename EmuMath::NewVector<Size_, T_>::stored_type* new_vector_data(EmuMath::NewVector<Size_, T_>& vector_)
	{
		return _vector_underlying::_vector_data<Size_, T_>(vector_);
	}

	/// <summary>
	/// <para> Retrieves a constant pointer to the contiguous data stored within the passed EmuMath Vector. </para>
	/// <para> This behaviour is prohibited with reference-containing Vectors by default. </para>
	/// </summary>
	/// <param name="vector_">EmuMath Vector to retrieve a data pointer for.</param>
	/// <returns>Constant pointer to the start of the provided EmuMath Vector's contiguous data.</returns>
	template<std::size_t Size_, typename T_>
	[[nodiscard]] constexpr inline const typename EmuMath::NewVector<Size_, T_>::stored_type* new_vector_data(const EmuMath::NewVector<Size_, T_>& vector_)
	{
		return _vector_underlying::_vector_data<Size_, T_>(vector_);
	}
}

#endif
