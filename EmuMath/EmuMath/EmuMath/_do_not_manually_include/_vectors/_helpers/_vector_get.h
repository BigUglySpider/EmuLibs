#ifndef EMU_MATH_VECTOR_GET_H_INC_
#define EMU_MATH_VECTOR_GET_H_INC_ 1

#include "_common_vector_helpers.h"

// CONTAINS:
// --- get_non_contained
// --- get
// --- get_theoretical
// --- try_get

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
	[[nodiscard]] constexpr inline typename EmuMath::Vector<Size_, T_>::value_type_uq vector_get_non_contained()
	{
		return _vector_underlying::_vector_get_non_contained_value<Size_, T_>();
	}
	template<class Vector_, typename = std::enable_if_t<EmuMath::TMP::is_emu_vector_v<Vector_>>>
	[[nodiscard]] constexpr inline typename Vector_::value_type_uq vector_get_non_contained()
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
	[[nodiscard]] constexpr inline typename EmuMath::Vector<Size_, T_>::value_type& vector_get(EmuMath::Vector<Size_, T_>& vector_)
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
	[[nodiscard]] constexpr inline const typename EmuMath::Vector<Size_, T_>::value_type& vector_get(const EmuMath::Vector<Size_, T_>& vector_)
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
	[[nodiscard]] constexpr inline typename EmuMath::Vector<Size_, T_>::value_type& vector_get
	(
		EmuMath::Vector<Size_, T_>& vector_,
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
	[[nodiscard]] constexpr inline const typename EmuMath::Vector<Size_, T_>::value_type& vector_get
	(
		const EmuMath::Vector<Size_, T_>& vector_,
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
	[[nodiscard]] constexpr inline const EmuMath::TMP::emu_vector_from_args_theoretical_return_t<Index_, Size_, T_> vector_get_theoretical
	(
		EmuMath::Vector<Size_, T_>& vector_
	)
	{
		return _vector_underlying::_vector_get_theoretical<Index_, Size_, T_>(vector_);
	}
	template<std::size_t Index_, std::size_t Size_, typename T_>
	[[nodiscard]] constexpr inline const EmuMath::TMP::emu_const_vector_from_args_theoretical_return_t<Index_, Size_, T_> vector_get_theoretical
	(
		const EmuMath::Vector<Size_, T_>& vector_
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
	[[nodiscard]] constexpr inline typename EmuMath::Vector<Size_, T_>::stored_type* vector_data(EmuMath::Vector<Size_, T_>& vector_)
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
	[[nodiscard]] constexpr inline const typename EmuMath::Vector<Size_, T_>::stored_type* vector_data(const EmuMath::Vector<Size_, T_>& vector_)
	{
		return _vector_underlying::_vector_data<Size_, T_>(vector_);
	}

	/// <summary>
	/// <para> Attempts to retrieve the specified index_ within the provided EmuMath Vector, outputting the element via out_ if the index_ is valid. </para>
	/// <para>
	///		Out_ must be assignable, constructible, or convertible-to from a reference to the Vector's value_type. 
	///		Assignment will be prioritised over construction, and construction will be prioritised over conversion.
	/// </para>
	/// </summary>
	/// <typeparam name="Out_">Type of reference provided to output to via out_.</typeparam>
	/// <param name="vector_">: Non-const reference to an EmuMath Vector to try to retrieve an element of.</param>
	/// <param name="index_">: Index to try and retrieve an element from within the passed vector_.</param>
	/// <param name="out_"> 
	///		: Reference to output to if the get is successful. Must be assignable, constructible, or convertible-to from a reference to vector_'s value_type.
	/// </param>
	/// <returns>True if the provided index is valid, otherwise false.</returns>
	template<class Out_, std::size_t Size_, typename T_, typename = std::enable_if_t<EmuMath::Vector<Size_, T_>::template is_valid_try_get_output_ref<Out_, false>()>>
	[[nodiscard]] constexpr inline bool vector_try_get(EmuMath::Vector<Size_, T_>& vector_, std::size_t index_, Out_& out_)
	{
		return _vector_underlying::_vector_try_get<Out_>(vector_, index_, out_);
	}

	/// <summary>
	/// <para> Attempts to retrieve the specified index_ within the provided EmuMath Vector, outputting the element via out_ if the index_ is valid. </para>
	/// <para>
	///		Out_ must be assignable, constructible, or convertible-to from a const reference to the Vector's value_type. 
	///		Assignment will be prioritised over construction, and construction will be prioritised over conversion.
	/// </para>
	/// </summary>
	/// <typeparam name="Out_">Type of reference provided to output to via out_.</typeparam>
	/// <param name="vector_">: Const reference to an EmuMath Vector to try to retrieve an element of.</param>
	/// <param name="index_">: Index to try and retrieve an element from within the passed vector_.</param>
	/// <param name="out_"> 
	///		: Reference to output to if the get is successful. Must be assignable, constructible, or convertible-to from a const reference to vector_'s value_type.
	/// </param>
	/// <returns>True if the provided index is valid, otherwise false.</returns>
	template<class Out_, std::size_t Size_, typename T_, typename = std::enable_if_t<EmuMath::Vector<Size_, T_>::template is_valid_try_get_output_ref<Out_, true>()>>
	[[nodiscard]] constexpr inline bool vector_try_get(const EmuMath::Vector<Size_, T_>& vector_, std::size_t index_, Out_& out_)
	{
		return _vector_underlying::_vector_try_get<Out_, Size_, T_>(vector_, index_, out_);
	}

	/// <summary>
	/// <para> 
	///		Attempts to retrieve the specified index_ within the provided EmuMath Vector,
	///		outputting a pointer to the element to the pointer pointed to by pp_out_
	/// </para>
	/// <para> If index_ is a valid index: The pointer pointed to by pp_out_ will be set to point to the element at the provided index in vector_. </para>
	/// <para> If index_ is an invalid index: The pointer pointed to by pp_out_ will be set to nullptr if NullptrIfFailed_ is true; otherwise it will be unmodified. </para>
	/// </summary>
	/// <param name="vector_">: Non-const reference to an EmuMath Vector to try to retrieve a pointer to an element of.</param>
	/// <param name="index_">: Index to try and retrieve a pointer to within the passed vector_.</param>
	/// <param name="pp_out_">Non-const pointer to the pointer to output to.</param>
	/// <returns>True if the provided index is valid, otherwise false.</returns>
	template<bool NullptrIfFailed_ = false, std::size_t Size_, typename T_>
	[[nodiscard]] constexpr inline bool vector_try_get
	(
		EmuMath::Vector<Size_, T_>& vector_,
		std::size_t index_,
		typename EmuMath::Vector<Size_, T_>::value_type** pp_out_
	)
	{
		return _vector_underlying::_vector_try_get<NullptrIfFailed_, Size_, T_>(vector_, index_, pp_out_);
	}

	/// <summary>
	/// <para> 
	///		Attempts to retrieve the specified index_ within the provided EmuMath Vector,
	///		outputting a const pointer to the element to the pointer pointed to by pp_const_out_.
	/// </para>
	/// <para> If index_ is a valid index: The const pointer pointed to by pp_const_out_ will be set to point to the element at the provided index in vector_. </para>
	/// <para> 
	///		If index_ is an invalid index: The const pointer pointed to by pp_const_out_ will be set to nullptr if NullptrIfFailed_ is true;
	///		otherwise it will be unmodified.
	/// </para>
	/// </summary>
	/// <param name="vector_">: Const reference to an EmuMath Vector to try to retrieve a constant pointer to an element of.</param>
	/// <param name="index_">: Index to try and retrieve a constant pointer to within the passed vector_.</param>
	/// <param name="pp_const_out_">Const pointer to the pointer to output to.</param>
	/// <returns>True if the provided index is valid, otherwise false.</returns>
	template<bool NullptrIfFailed_ = false, std::size_t Size_, typename T_>
	[[nodiscard]] constexpr inline bool vector_try_get
	(
		const EmuMath::Vector<Size_, T_>& vector_,
		std::size_t index_,
		const typename EmuMath::Vector<Size_, T_>::value_type** pp_const_out_
	)
	{
		return _vector_underlying::_vector_try_get<NullptrIfFailed_, Size_, T_>(vector_, index_, pp_const_out_);
	}
}

#endif
