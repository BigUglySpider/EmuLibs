#ifndef EMU_MATH_COMMON_MATH_TMP_H_INC_
#define EMU_MATH_COMMON_MATH_TMP_H_INC_ 1

#include "../../../EmuCore/TMPHelpers/TypeConvertors.h"

namespace EmuMath::TMP
{
	/// <summary>
	/// <para> Type to determine if the passed T_ is a type of EmuMath Colour. </para>
	/// <para> The value will also be true if T_ is a reference to an EmuMath Colour, and ignores const/ref qualifiers. Pointers remain false. </para>
	/// </summary>
	template<class T_>
	struct is_emu_colour : public EmuCore::TMP::type_check_ignore_ref_cv_base<is_emu_colour, std::false_type, T_>
	{
	};
	template<class T_>
	static constexpr bool is_emu_colour_v = is_emu_colour<T_>::value;

	/// <summary>
	/// <para> Type to determine if the passed T_ is a type of EmuMath Fast Vector. </para>
	/// <para> The value will also be true if T_ is a reference to an EmuMath Fast Vector, and ignores const/ref qualifiers. Pointers remain false. </para>
	/// </summary>
	template<class T_>
	struct is_emu_fast_vector : public EmuCore::TMP::type_check_ignore_ref_cv_base<is_emu_fast_vector, std::false_type, T_>
	{
	};
	template<class T_>
	static constexpr bool is_emu_fast_vector_v = is_emu_fast_vector<T_>::value;

	/// <summary>
	/// <para> Type to determine if the passed T_ is a type of EmuMath Matrix. </para>
	/// <para> The value will also be true if T_ is a reference to an EmuMath Matrix, and ignores const/ref qualifiers. Pointers remain false. </para>
	/// </summary>
	template<class T_>
	struct is_emu_matrix : public EmuCore::TMP::type_check_ignore_ref_cv_base<is_emu_matrix, std::false_type, T_>
	{
	};
	template<class T_>
	static constexpr bool is_emu_matrix_v = is_emu_matrix<T_>::value;

	/// <summary>
	/// <para> Type to determine if the passed T_ is a type of EmuMath Quaternion. </para>
	/// <para> The value will also be true if T_ is a reference to an EmuMath Quaternion, and ignores const/ref qualifiers. Pointers remain false. </para>
	/// </summary>
	template<class T_>
	struct is_emu_quaternion : public EmuCore::TMP::type_check_ignore_ref_cv_base<is_emu_quaternion, std::false_type, T_>
	{
	};
	template<class T_>
	static constexpr bool is_emu_quaternion_v = is_emu_quaternion<T_>::value;

	/// <summary>
	/// <para> Type to determine if the passed T_ is a type of EmuMath Rect. </para>
	/// <para> The value will also be true if T_ is a reference to an EmuMath Rect, and ignores const/ref qualifiers. Pointers remain false. </para>
	/// </summary>
	template<class T_>
	struct is_emu_rect : public EmuCore::TMP::type_check_ignore_ref_cv_base<is_emu_rect, std::false_type, T_>
	{
	};
	template<class T_>
	static constexpr bool is_emu_rect_v = is_emu_rect<T_>::value;

	/// <summary>
	/// <para> Type to determine if the passed T_ is a type of EmuMath Vector. </para>
	/// <para> The value will also be true if T_ is a reference to an EmuMath Vector, and ignores const/ref qualifiers. Pointers remain false. </para>
	/// </summary>
	template<class T_>
	struct is_emu_vector : public EmuCore::TMP::type_check_ignore_ref_cv_base<is_emu_vector, std::false_type, T_>
	{
	};
	template<class T_>
	static constexpr bool is_emu_vector_v = is_emu_vector<T_>::value;
}

namespace EmuMath::Concepts
{
	/// <summary>
	/// <para> Concept that determines if the passed type T_ is an EmuMath Colour. Effectively a check that `is_emu_colour::value` is true. </para>
	/// </summary>
	template<class T_>
	concept EmuColour = EmuMath::TMP::is_emu_colour_v<T_>;

	/// <summary>
	/// <para> Concept that determines if the passed type T_ is an EmuMath Fast Vector. Effectively a check that `is_emu_fast_vector::value` is true. </para>
	/// </summary>
	template<class T_>
	concept EmuFastVector = EmuMath::TMP::is_emu_fast_vector_v<T_>;

	/// <summary>
	/// <para> Concept that determines if the passed type T_ is an EmuMath Matrix. Effectively a check that `is_emu_matrix::value` is true. </para>
	/// </summary>
	template<class T_>
	concept EmuMatrix = EmuMath::TMP::is_emu_matrix_v<T_>;

	/// <summary>
	/// <para> Concept that determines if the passed type T_ is an EmuMath Quaternion. Effectively a check that `is_emu_quaternion::value` is true. </para>
	/// </summary>
	template<class T_>
	concept EmuQuaternion = EmuMath::TMP::is_emu_quaternion_v<T_>;

	/// <summary>
	/// <para> Concept that determines if the passed type T_ is an EmuMath Rect. Effectively a check that `is_emu_rect::value` is true. </para>
	/// </summary>
	template<class T_>
	concept EmuRect = EmuMath::TMP::is_emu_rect_v<T_>;

	/// <summary>
	/// <para> Concept that determines if the passed type T_ is an EmuMath Vector. Effectively a check that `is_emu_vector::value` is true. </para>
	/// </summary>
	template<class T_>
	concept EmuVector = EmuMath::TMP::is_emu_vector_v<T_>;
}

namespace EmuConcepts
{
	using namespace EmuMath::Concepts;
}

#endif
