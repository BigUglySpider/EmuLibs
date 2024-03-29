#ifndef EMU_MATH_COMMON_MATH_TMP_H_INC_
#define EMU_MATH_COMMON_MATH_TMP_H_INC_ 1

#include "../../../EmuCore/CommonConcepts/Arithmetic.h"
#include "../../../EmuCore/CommonConcepts/StdTypes.h"
#include "../../../EmuCore/CommonPreprocessor/All.h"
#include "../../../EmuCore/TMPHelpers/TypeConvertors.h"

#pragma region CHECKS
namespace EmuMath::TMP
{
	/// <summary>
	/// <para> Type to determine if the passed T_ is a type of EmuMath Colour. </para>
	/// <para> The value will also be true if T_ is a reference to an EmuMath Colour, and ignores const/volatile qualifiers. Pointers remain false. </para>
	/// </summary>
	template<class T_>
	struct is_emu_colour : public EmuCore::TMP::type_check_ignore_ref_cv_base<is_emu_colour, std::false_type, T_>
	{
	};
	template<class T_>
	static constexpr bool is_emu_colour_v = is_emu_colour<T_>::value;

	/// <summary>
	/// <para> Type to determine if the passed T_ is a type of EmuMath Fast Matrix. </para>
	/// <para> The value will also be true if T_ is a reference to an EmuMath Fast Matrix, and ignores const/volatile qualifiers. Pointers remain false. </para>
	/// </summary>
	template<class T_>
	struct is_emu_fast_matrix : public EmuCore::TMP::type_check_ignore_ref_cv_base<is_emu_fast_matrix, std::false_type, T_>
	{
	};
	template<class T_>
	static constexpr bool is_emu_fast_matrix_v = is_emu_fast_matrix<T_>::value;

	/// <summary>
	/// <para> Type to determine if the passed T_ is a type of EmuMath Fast Quaternion. </para>
	/// <para> The value will also be true if T_ is a reference to an EmuMath Fast Quaternion, and ignores const/volatile qualifiers. Pointers remain false. </para>
	/// </summary>
	template<class T_>
	struct is_emu_fast_quaternion : public EmuCore::TMP::type_check_ignore_ref_cv_base<is_emu_fast_quaternion, std::false_type, T_>
	{
	};
	template<class T_>
	static constexpr bool is_emu_fast_quaternion_v = is_emu_fast_quaternion<T_>::value;

	/// <summary>
	/// <para> Type to determine if the passed T_ is a type of EmuMath Fast Vector. </para>
	/// <para> The value will also be true if T_ is a reference to an EmuMath Fast Vector, and ignores const/volatile qualifiers. Pointers remain false. </para>
	/// </summary>
	template<class T_>
	struct is_emu_fast_vector : public EmuCore::TMP::type_check_ignore_ref_cv_base<is_emu_fast_vector, std::false_type, T_>
	{
	};
	template<class T_>
	static constexpr bool is_emu_fast_vector_v = is_emu_fast_vector<T_>::value;

	/// <summary>
	/// <para> Type to determine if the passed T_ is a type of EmuMath Matrix. </para>
	/// <para> The value will also be true if T_ is a reference to an EmuMath Matrix, and ignores const/volatile qualifiers. Pointers remain false. </para>
	/// </summary>
	template<class T_>
	struct is_emu_matrix : public EmuCore::TMP::type_check_ignore_ref_cv_base<is_emu_matrix, std::false_type, T_>
	{
	};
	template<class T_>
	static constexpr bool is_emu_matrix_v = is_emu_matrix<T_>::value;

	/// <summary>
	/// <para> Type to determine if the passed T_ is a type of EmuMath Quaternion. </para>
	/// <para> The value will also be true if T_ is a reference to an EmuMath Quaternion, and ignores const/volatile qualifiers. Pointers remain false. </para>
	/// </summary>
	template<class T_>
	struct is_emu_quaternion : public EmuCore::TMP::type_check_ignore_ref_cv_base<is_emu_quaternion, std::false_type, T_>
	{
	};
	template<class T_>
	static constexpr bool is_emu_quaternion_v = is_emu_quaternion<T_>::value;

	/// <summary>
	/// <para> Type to determine if the passed T_ is a type of EmuMath Rect. </para>
	/// <para> The value will also be true if T_ is a reference to an EmuMath Rect, and ignores const/volatile qualifiers. Pointers remain false. </para>
	/// </summary>
	template<class T_>
	struct is_emu_rect : public EmuCore::TMP::type_check_ignore_ref_cv_base<is_emu_rect, std::false_type, T_>
	{
	};
	template<class T_>
	static constexpr bool is_emu_rect_v = is_emu_rect<T_>::value;

	/// <summary>
	/// <para> Type to determine if the passed T_ is a type of EmuMath Vector. </para>
	/// <para> The value will also be true if T_ is a reference to an EmuMath Vector, and ignores const/volatile qualifiers. Pointers remain false. </para>
	/// </summary>
	template<class T_>
	struct is_emu_vector : public EmuCore::TMP::type_check_ignore_ref_cv_base<is_emu_vector, std::false_type, T_>
	{
	};
	template<class T_>
	static constexpr bool is_emu_vector_v = is_emu_vector<T_>::value;
}
#pragma endregion

#pragma region CONCEPTS
namespace EmuMath::Concepts
{
	/// <summary>
	/// <para> Concept that determines if the passed type T_ is an EmuMath Colour. Effectively a check that `is_emu_colour::value` is true. </para>
	/// </summary>
	template<class T_>
	concept EmuColour = EmuMath::TMP::is_emu_colour_v<T_>;

	/// <summary>
	/// <para> Concept that determines if the passed type T_ is an EmuMath Fast Matrix. Effectively a check that `is_emu_fast_vector::value` is true. </para>
	/// </summary>
	template<class T_>
	concept EmuFastMatrix = EmuMath::TMP::is_emu_fast_matrix_v<T_>;

	/// <summary>
	/// <para> Concept that determines if the passed type T_ is an EmuMath Fast Matrix with square dimensions. </para>
	/// </summary>
	template<class T_>
	concept EmuFastMatrixSquare =
	(
		(EmuFastMatrix<T_>) &&
		(EmuCore::TMP::remove_ref_cv_t<T_>::num_columns  == EmuCore::TMP::remove_ref_cv_t<T_>::num_rows)
	);

	/// <summary>
	/// <para> 
	///		Concept that determines if the passed type T_ is an EmuMath Fast Quaternion. 
	///		Effectively a check that `is_emu_fast_quaternion::value` is true.
	/// </para>
	/// </summary>
	template<class T_>
	concept EmuFastQuaternion = EmuMath::TMP::is_emu_fast_quaternion_v<T_>;

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
	/// <para> Concept that determines if the passed type T_ is an EmuMath Matrix with square dimensions. </para>
	/// </summary>
	template<class T_>
	concept EmuMatrixSquare =
	(
		(EmuMatrix<T_>) &&
		(EmuCore::TMP::remove_ref_cv_t<T_>::num_columns  == EmuCore::TMP::remove_ref_cv_t<T_>::num_rows)
	);

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

	/// <summary>
	/// <para> Concept that determines if the passed type Arg_ is suitable for a lerp argument (b or t) with a FastQuaternion of the specified FastQuaternion_ type. </para>
	/// <para> True if FastQuaternion_ is an EmuFastQuaternion, and one of: </para>
	/// <para> 1: Arg_ is the same FastQuaternion type; or </para>
	/// <para> 2: Arg_ is the same type as the FastQuaternion's register_type; or </para>
	/// <para> 3: Arg_ is a scalar arithmetic type recognised by EmuConcepts::Arithmetic. </para>
	/// </summary>
	template<class Arg_, class FastQuaternion_>
	concept EmuFastQuaternionLerpArg =
	(
		(EmuFastQuaternion<FastQuaternion_>) &&
		(
			(std::is_same_v<typename std::remove_cvref<FastQuaternion_>::type, typename std::remove_cvref<Arg_>::type>) ||
			(std::is_same_v<typename std::remove_cvref_t<FastQuaternion_>::register_type, typename std::remove_cvref<Arg_>::type>) ||
			(EmuConcepts::Arithmetic<Arg_>)
		)
	);

	template<class FastQuaternion_, class FastMatrix_>
	concept EmuFastMatrixCompatibleQuaternion =
	(
		(EmuFastMatrix<FastMatrix_>) &&
		(EmuFastQuaternion<FastQuaternion_>) &&
		(std::is_same_v<typename std::remove_cvref_t<FastMatrix_>::register_type, typename std::remove_cvref_t<FastQuaternion_>::register_type>)
	);
}

namespace EmuConcepts
{
	using namespace EmuMath::Concepts;
}
#pragma endregion

#endif
