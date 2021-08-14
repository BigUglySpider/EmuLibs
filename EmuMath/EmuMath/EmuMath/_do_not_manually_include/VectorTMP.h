#ifndef EMU_MATH_VECTOR_T_TMP_H_INC_
#define EMU_MATH_VECTOR_T_TMP_H_INC_

#include <cstddef>

namespace EmuMath
{
	template<std::size_t Size_, typename T_>
	struct Vector;
}

namespace EmuMath::TMP
{
	template<class T_>
	struct is_emu_vector
	{
		static constexpr bool value = false;
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
}

#endif
