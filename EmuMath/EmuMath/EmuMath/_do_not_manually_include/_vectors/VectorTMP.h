#ifndef EMU_MATH_VECTOR_T_TMP_H_INC_
#define EMU_MATH_VECTOR_T_TMP_H_INC_ 1

#include "../../../EmuCore/CommonTypes/DeferrableReferenceWrapper.h"
#include <cstddef>

namespace EmuMath
{
	template<std::size_t Size_, typename T_>
	struct Vector;

	/// <summary>
	/// <para> The type of reference wrapper used to store references within an EmuMath vector. </para>
	/// <para> This is the standard type for any references stored within an EmuMath vector. References of other types are undefined and unsupported. </para>
	/// </summary>
	/// <typeparam name="T_"></typeparam>
	template<typename T_>
	using InternalVectorReference = EmuCore::DeferrableReferenceWrapper<T_>;

	/// <summary>
	/// <para> Alias for EmuMath vectors which contain non-const reference wrappers. </para>
	/// <para> This is the EmuMath standard for storing such references within a vector. The behaviour of storing other types of references is undefined and unsupported. </para>
	/// </summary>
	/// <typeparam name="T_">Type to be referencing. T_ itself should not be a reference type; the reference will be applied automatically.</typeparam>
	template<std::size_t Size_, typename T_>
	using RefVector = EmuMath::Vector<Size_, InternalVectorReference<T_>>;
	/// <summary>
	/// <para> Alias for EmuMath vectors which contain const reference wrappers. </para>
	/// <para> This is the EmuMath standard for storing such references within a vector. The behaviour of storing other types of references is undefined and unsupported. </para>
	/// </summary>
	/// <typeparam name="T_">Type to be referencing. T_ itself should not be a reference type; the reference will be applied automatically.</typeparam>
	template<std::size_t Size_, typename T_>
	using ConstRefVector = EmuMath::Vector<Size_, InternalVectorReference<const T_>>;
}

namespace EmuMath::TMP
{
	template<class T_>
	struct is_emu_vector
	{
		static constexpr bool value = std::conditional_t
		<
			// This is a recursive check to make sure that T_ does not have modifiers that may lead to false negatives
			std::is_same_v<T_, std::remove_reference_t<std::remove_cv_t<T_>>>,
			std::false_type,
			is_emu_vector<std::remove_reference_t<std::remove_cv_t<T_>>>
		>::value;
	};
	template<std::size_t Size_, typename T_>
	struct is_emu_vector<EmuMath::Vector<Size_, T_>>
	{
		static constexpr bool value = true;
	};
	template<class T_>
	static constexpr bool is_emu_vector_v = is_emu_vector<T_>::value;

	template<template<std::size_t Size__, typename T__> class Template_>
	struct is_emu_vector_template
	{
		static constexpr bool value = false;
	};
	template<>
	struct is_emu_vector_template<EmuMath::Vector>
	{
		static constexpr bool value = true;
	};
	template<template<std::size_t Size__, typename T__> class Template_>
	static constexpr bool is_emu_vector_template_v = is_emu_vector_template<Template_>::value;

	template<typename value_type, class Vector_>
	struct copy_emu_vector_size
	{
		static_assert(is_emu_vector_v<Vector_>, "Attempted to copy an EmuMath vector's size via copy_emu_vector_size, but a non-EmuMath-vector was passed as the Vector_ arg.");
		using type = EmuMath::Vector<Vector_::size, value_type>;
	};
	template<typename value_type, class Vector_>
	using copy_emu_vector_size_t = typename copy_emu_vector_size<value_type, Vector_>::type;

	template<class Vector_, std::size_t FirstIndex_, std::size_t...OtherIndices_>
	struct valid_vector_indices
	{
		static constexpr bool value = valid_vector_indices<Vector_, FirstIndex_>::value ? valid_vector_indices<Vector_, OtherIndices_...>::value : false;
	};
	template<class Vector_, std::size_t FirstIndex_>
	struct valid_vector_indices<Vector_, FirstIndex_>
	{
		static constexpr bool value = (FirstIndex_ < Vector_::size);
	};
	template<class Vector_, std::size_t...Indices_>
	static constexpr bool valid_vector_indices_v = valid_vector_indices<Vector_, Indices_...>::value;

	/// <summary>
	/// <para> Function to construct an EmuMath vector with the provided data. The output vector's size will be equal to the number of arguments provided. </para>
	/// <para> The provided value_type must be constructible by all all types passed as args_. </para>
	/// </summary>
	/// <typeparam name="value_type">Type to be contained within the vector.</typeparam>
	/// <typeparam name="Args_">Types of the arguments provided to the vector.</typeparam>
	/// <param name="args_">Arguments to be provided to the vector on construction. For every argument, the vector's size will increase by one.</param>
	/// <returns>
	///		EmuMath vector containing the specified value_type, with a number of elements equal to the provided number of args_. 
	///		All elements of the returned vector are constructed by the provided args_..
	/// </returns>
	template<typename value_type, typename...Args_>
	[[nodiscard]] constexpr inline EmuMath::Vector<sizeof...(Args_), value_type> make_emu_vector(Args_&&...args_)
	{
		return EmuMath::Vector<sizeof...(Args_), value_type>(std::forward<Args_>(args_)...);
	}
}

#endif