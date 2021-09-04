#ifndef EMU_MATH_MATRIX_HELPERS_TRANSFORMATIONS_H_INC_
#define EMU_MATH_MATRIX_HELPERS_TRANSFORMATIONS_H_INC_ 1

#include "_common_matrix_helper_includes.h"

namespace EmuMath::Helpers
{
	/// <summary>
	/// <para> Creates a 4x4 transformation matrix which may be used to perform a translation of x_ in the X-dimension, y_ in the Y-dimension, and z_ in the Z-dimension. </para>
	/// <para> x_, y_, and z_ may be any types, but they must be convertible to the output matrix's contained type (provided as the out_contained_type argument). </para>
	/// </summary>
	/// <typeparam name="out_contained_type">Type to be contained within the output matrix.</typeparam>
	/// <typeparam name="X_">Type use for the argument representing the translation in the X-dimension.</typeparam>
	/// <typeparam name="Y_">Type use for the argument representing the translation in the Y-dimension.</typeparam>
	/// <typeparam name="Z_">Type use for the argument representing the translation in the Z-dimension.</typeparam>
	/// <param name="x_">Distance to translate in the X-dimension.</param>
	/// <param name="y_">Distance to translate in the Y-dimension.</param>
	/// <param name="z_">Distance to translate in the Z-dimension.</param>
	/// <returns>4x4 EmuMath matrix which may be used to perform a translation of the specified amounts in respective dimensions.</returns>
	template<typename out_contained_type = float, bool OutColumnMajor_ = true, typename X_, typename Y_, typename Z_>
	constexpr inline EmuMath::Matrix<4, 4, out_contained_type, OutColumnMajor_> MatrixTranslation(const X_& x_, const Y_& y_, const Z_& z_)
	{
		return _underlying_matrix_funcs::_make_translation_matrix<EmuMath::Matrix<4, 4, out_contained_type, OutColumnMajor_>, X_, Y_, Z_>(x_, y_, z_);
	}

	/// <summary>
	/// <para> Creates a 4x4 transformation matrix which may be used to rotate a point about the X-axis by the provided number of radians. </para>
	/// <para> This function may make sacrifices to be evaluable at compile time. If it is being called at runtime, it is recommended to use MatrixRotationXRads instead. </para>
	/// <para> NumIterations_ may be increased to improve accuracy at the cost of performance, or decreased to reduce accuracy and increase performance. </para>
	/// </summary>
	/// <typeparam name="out_contained_type">Type to be contained in the output rotation matrix.</typeparam>
	/// <typeparam name="RotX_">Type used to provide the amount of radians to rotate about the X-axis.</typeparam>
	/// <param name="rotation_x_rads_">The amount of radians to rotate about the X-axis.</param>
	/// <returns>4x4 EmuMath matrix which may be used to perform a rotation about the X-axis by the passed number of radians.</returns>
	template<std::size_t NumIterations_ = 3, typename out_contained_type = float, bool OutColumnMajor_ = true, typename RotX_>
	constexpr inline EmuMath::Matrix<4, 4, out_contained_type, OutColumnMajor_> MatrixRotationXRadsConstexpr(const RotX_& rotation_x_rads_)
	{
		return _underlying_matrix_funcs::_make_rotation_matrix_x
		<
			EmuMath::Matrix<4, 4, out_contained_type, OutColumnMajor_>,
			RotX_,
			EmuCore::do_cos_constexpr<typename EmuMath::Matrix<4, 4, out_contained_type, OutColumnMajor_>::value_type, NumIterations_>,
			EmuCore::do_sin_constexpr<typename EmuMath::Matrix<4, 4, out_contained_type, OutColumnMajor_>::value_type, NumIterations_>
		>(rotation_x_rads_);
	}
	/// <summary>
	/// <para> Creates a 4x4 transformation matrix which may be used to rotate a point about the X-axis by the provided number of degrees. </para>
	/// <para> This function may make sacrifices to be evaluable at compile time. If it is being called at runtime, it is recommended to use MatrixRotationXDegs instead. </para>
	/// <para> NumIterations_ may be increased to improve accuracy at the cost of performance, or decreased to reduce accuracy and increase performance. </para>
	/// </summary>
	/// <typeparam name="out_contained_type">Type to be contained in the output rotation matrix.</typeparam>
	/// <typeparam name="RotX_">Type used to provide the amount of degrees to rotate about the X-axis.</typeparam>
	/// <param name="rotation_x_rads_">The amount of degrees to rotate about the X-axis.</param>
	/// <returns>4x4 EmuMath matrix which may be used to perform a rotation about the X-axis by the passed number of degrees.</returns>
	template<std::size_t NumIterations_ = 3, typename out_contained_type = float, bool OutColumnMajor_ = true, typename RotX_>
	constexpr inline EmuMath::Matrix<4, 4, out_contained_type, OutColumnMajor_> MatrixRotationXDegsConstexpr(const RotX_& rotation_x_degs_)
	{
		return MatrixRotationXRadsConstexpr<NumIterations_, out_contained_type, OutColumnMajor_, RotX_>(EmuCore::Pi::DegsToRads(rotation_x_degs_));
	}

	/// <summary>
	/// <para> Creates a 4x4 transformation matrix which may be used to rotate a point about the Y-axis by the provided number of radians. </para>
	/// <para> This function may make sacrifices to be evaluable at compile time. If it is being called at runtime, it is recommended to use MatrixRotationYRads instead. </para>
	/// <para> NumIterations_ may be increased to improve accuracy at the cost of performance, or decreased to reduce accuracy and increase performance. </para>
	/// </summary>
	/// <typeparam name="out_contained_type">Type to be contained in the output rotation matrix.</typeparam>
	/// <typeparam name="RotX_">Type used to provide the amount of radians to rotate about the Y-axis.</typeparam>
	/// <param name="rotation_x_rads_">The amount of radians to rotate about the Y-axis.</param>
	/// <returns>4x4 EmuMath matrix which may be used to perform a rotation about the Y-axis by the passed number of radians.</returns>
	template<std::size_t NumIterations_ = 3, typename out_contained_type = float, bool OutColumnMajor_ = true, typename RotX_>
	constexpr inline EmuMath::Matrix<4, 4, out_contained_type, OutColumnMajor_> MatrixRotationYRadsConstexpr(const RotX_& rotation_x_rads_)
	{
		return _underlying_matrix_funcs::_make_rotation_matrix_y
		<
			EmuMath::Matrix<4, 4, out_contained_type, OutColumnMajor_>,
			RotX_,
			EmuCore::do_cos_constexpr<typename EmuMath::Matrix<4, 4, out_contained_type, OutColumnMajor_>::value_type, NumIterations_>,
			EmuCore::do_sin_constexpr<typename EmuMath::Matrix<4, 4, out_contained_type, OutColumnMajor_>::value_type, NumIterations_>
		>(rotation_x_rads_);
	}
	/// <summary>
	/// <para> Creates a 4x4 transformation matrix which may be used to rotate a point about the Y-axis by the provided number of degrees. </para>
	/// <para> This function may make sacrifices to be evaluable at compile time. If it is being called at runtime, it is recommended to use MatrixRotationYDegs instead. </para>
	/// <para> NumIterations_ may be increased to improve accuracy at the cost of performance, or decreased to reduce accuracy and increase performance. </para>
	/// </summary>
	/// <typeparam name="out_contained_type">Type to be contained in the output rotation matrix.</typeparam>
	/// <typeparam name="RotX_">Type used to provide the amount of degrees to rotate about the Y-axis.</typeparam>
	/// <param name="rotation_x_rads_">The amount of degrees to rotate about the Y-axis.</param>
	/// <returns>4x4 EmuMath matrix which may be used to perform a rotation about the Y-axis by the passed number of degrees.</returns>
	template<std::size_t NumIterations_ = 3, typename out_contained_type = float, bool OutColumnMajor_ = true, typename RotX_>
	constexpr inline EmuMath::Matrix<4, 4, out_contained_type, OutColumnMajor_> MatrixRotationYDegsConstexpr(const RotX_& rotation_x_degs_)
	{
		return MatrixRotationYRadsConstexpr<NumIterations_, out_contained_type, OutColumnMajor_, RotX_>(EmuCore::Pi::DegsToRads(rotation_x_degs_));
	}

	/// <summary>
	/// <para> Creates a 4x4 transformation matrix which may be used to rotate a point about the Z-axis by the provided number of radians. </para>
	/// <para> This function may make sacrifices to be evaluable at compile time. If it is being called at runtime, it is recommended to use MatrixRotationZRads instead. </para>
	/// <para> NumIterations_ may be increased to improve accuracy at the cost of performance, or decreased to reduce accuracy and increase performance. </para>
	/// </summary>
	/// <typeparam name="out_contained_type">Type to be contained in the output rotation matrix.</typeparam>
	/// <typeparam name="RotX_">Type used to provide the amount of radians to rotate about the Z-axis.</typeparam>
	/// <param name="rotation_x_rads_">The amount of radians to rotate about the Z-axis.</param>
	/// <returns>4x4 EmuMath matrix which may be used to perform a rotation about the Z-axis by the passed number of radians.</returns>
	template<std::size_t NumIterations_ = 3, typename out_contained_type = float, bool OutColumnMajor_ = true, typename RotX_>
	constexpr inline EmuMath::Matrix<4, 4, out_contained_type, OutColumnMajor_> MatrixRotationZRadsConstexpr(const RotX_& rotation_x_rads_)
	{
		return _underlying_matrix_funcs::_make_rotation_matrix_z
		<
			EmuMath::Matrix<4, 4, out_contained_type, OutColumnMajor_>,
			RotX_,
			EmuCore::do_cos_constexpr<typename EmuMath::Matrix<4, 4, out_contained_type, OutColumnMajor_>::value_type, NumIterations_>,
			EmuCore::do_sin_constexpr<typename EmuMath::Matrix<4, 4, out_contained_type, OutColumnMajor_>::value_type, NumIterations_>
		>(rotation_x_rads_);
	}
	/// <summary>
	/// <para> Creates a 4x4 transformation matrix which may be used to rotate a point about the Z-axis by the provided number of degrees. </para>
	/// <para> This function may make sacrifices to be evaluable at compile time. If it is being called at runtime, it is recommended to use MatrixRotationZDegs instead. </para>
	/// <para> NumIterations_ may be increased to improve accuracy at the cost of performance, or decreased to reduce accuracy and increase performance. </para>
	/// </summary>
	/// <typeparam name="out_contained_type">Type to be contained in the output rotation matrix.</typeparam>
	/// <typeparam name="RotX_">Type used to provide the amount of degrees to rotate about the Z-axis.</typeparam>
	/// <param name="rotation_x_rads_">The amount of degrees to rotate about the Z-axis.</param>
	/// <returns>4x4 EmuMath matrix which may be used to perform a rotation about the Z-axis by the passed number of degrees.</returns>
	template<std::size_t NumIterations_ = 3, typename out_contained_type = float, bool OutColumnMajor_ = true, typename RotX_>
	constexpr inline EmuMath::Matrix<4, 4, out_contained_type, OutColumnMajor_> MatrixRotationZDegsConstexpr(const RotX_& rotation_x_degs_)
	{
		return MatrixRotationZRadsConstexpr<NumIterations_, out_contained_type, OutColumnMajor_, RotX_>(EmuCore::Pi::DegsToRads(rotation_x_degs_));
	}

	/// <summary> Creates a 4x4 transformation matrix which may be used to rotate a point about the X-axis by the provided number of radians. </summary>
	/// <typeparam name="out_contained_type">Type to be contained in the output rotation matrix.</typeparam>
	/// <typeparam name="RotX_">Type used to provide the amount of radians to rotate about the X-axis.</typeparam>
	/// <param name="rotation_x_rads_">The amount of radians to rotate about the X-axis.</param>
	/// <returns>4x4 EmuMath matrix which may be used to perform a rotation about the X-axis by the passed number of radians.</returns>
	template<typename out_contained_type = float, bool OutColumnMajor_ = true, typename RotX_>
	inline EmuMath::Matrix<4, 4, out_contained_type, OutColumnMajor_> MatrixRotationXRads(const RotX_& rotation_x_rads_)
	{
		return _underlying_matrix_funcs::_make_rotation_matrix_x
		<
			EmuMath::Matrix<4, 4, out_contained_type, OutColumnMajor_>,
			RotX_,
			EmuCore::do_cos<typename EmuMath::Matrix<4, 4, out_contained_type, OutColumnMajor_>::value_type>,
			EmuCore::do_sin<typename EmuMath::Matrix<4, 4, out_contained_type, OutColumnMajor_>::value_type>
		>(rotation_x_rads_);
	}
	/// <summary> Creates a 4x4 transformation matrix which may be used to rotate a point about the X-axis by the provided number of degrees. </summary>
	/// <typeparam name="out_contained_type">Type to be contained in the output rotation matrix.</typeparam>
	/// <typeparam name="RotX_">Type used to provide the amount of degrees to rotate about the X-axis.</typeparam>
	/// <param name="rotation_x_rads_">The amount of degrees to rotate about the X-axis.</param>
	/// <returns>4x4 EmuMath matrix which may be used to perform a rotation about the X-axis by the passed number of degrees.</returns>
	template<typename out_contained_type = float, bool OutColumnMajor_ = true, typename RotX_>
	inline EmuMath::Matrix<4, 4, out_contained_type, OutColumnMajor_> MatrixRotationXDegs(const RotX_& rotation_x_degs_)
	{
		return MatrixRotationXRads<out_contained_type, OutColumnMajor_, RotX_>(EmuCore::Pi::DegsToRads(rotation_x_degs_));
	}

	/// <summary> Creates a 4x4 transformation matrix which may be used to rotate a point about the Y-axis by the provided number of radians. </summary>
	/// <typeparam name="out_contained_type">Type to be contained in the output rotation matrix.</typeparam>
	/// <typeparam name="RotX_">Type used to provide the amount of radians to rotate about the Y-axis.</typeparam>
	/// <param name="rotation_x_rads_">The amount of radians to rotate about the Y-axis.</param>
	/// <returns>4x4 EmuMath matrix which may be used to perform a rotation about the Y-axis by the passed number of radians.</returns>
	template<typename out_contained_type = float, bool OutColumnMajor_ = true, typename RotX_>
	inline EmuMath::Matrix<4, 4, out_contained_type, OutColumnMajor_> MatrixRotationYRads(const RotX_& rotation_x_rads_)
	{
		return _underlying_matrix_funcs::_make_rotation_matrix_y
		<
			EmuMath::Matrix<4, 4, out_contained_type, OutColumnMajor_>,
			RotX_,
			EmuCore::do_cos<typename EmuMath::Matrix<4, 4, out_contained_type, OutColumnMajor_>::value_type>,
			EmuCore::do_sin<typename EmuMath::Matrix<4, 4, out_contained_type, OutColumnMajor_>::value_type>
		>(rotation_x_rads_);
	}
	/// <summary> Creates a 4x4 transformation matrix which may be used to rotate a point about the Y-axis by the provided number of degrees. </summary>
	/// <typeparam name="out_contained_type">Type to be contained in the output rotation matrix.</typeparam>
	/// <typeparam name="RotX_">Type used to provide the amount of degrees to rotate about the Y-axis.</typeparam>
	/// <param name="rotation_x_rads_">The amount of degrees to rotate about the Y-axis.</param>
	/// <returns>4x4 EmuMath matrix which may be used to perform a rotation about the Y-axis by the passed number of degrees.</returns>
	template<typename out_contained_type = float, bool OutColumnMajor_ = true, typename RotX_>
	inline EmuMath::Matrix<4, 4, out_contained_type, OutColumnMajor_> MatrixRotationYDegs(const RotX_& rotation_x_degs_)
	{
		return MatrixRotationYRads<out_contained_type, OutColumnMajor_, RotX_>(EmuCore::Pi::DegsToRads(rotation_x_degs_));
	}

	/// <summary> Creates a 4x4 transformation matrix which may be used to rotate a point about the Z-axis by the provided number of radians. </summary>
	/// <typeparam name="out_contained_type">Type to be contained in the output rotation matrix.</typeparam>
	/// <typeparam name="RotX_">Type used to provide the amount of radians to rotate about the Z-axis.</typeparam>
	/// <param name="rotation_x_rads_">The amount of radians to rotate about the Z-axis.</param>
	/// <returns>4x4 EmuMath matrix which may be used to perform a rotation about the Z-axis by the passed number of radians.</returns>
	template<typename out_contained_type = float, bool OutColumnMajor_ = true, typename RotX_>
	inline EmuMath::Matrix<4, 4, out_contained_type, OutColumnMajor_> MatrixRotationZRads(const RotX_& rotation_x_rads_)
	{
		return _underlying_matrix_funcs::_make_rotation_matrix_z
		<
			EmuMath::Matrix<4, 4, out_contained_type, OutColumnMajor_>,
			RotX_,
			EmuCore::do_cos<typename EmuMath::Matrix<4, 4, out_contained_type, OutColumnMajor_>::value_type>,
			EmuCore::do_sin<typename EmuMath::Matrix<4, 4, out_contained_type, OutColumnMajor_>::value_type>
		>(rotation_x_rads_);
	}
	/// <summary> Creates a 4x4 transformation matrix which may be used to rotate a point about the Z-axis by the provided number of degrees. </summary>
	/// <typeparam name="out_contained_type">Type to be contained in the output rotation matrix.</typeparam>
	/// <typeparam name="RotX_">Type used to provide the amount of degrees to rotate about the Z-axis.</typeparam>
	/// <param name="rotation_x_rads_">The amount of degrees to rotate about the Z-axis.</param>
	/// <returns>4x4 EmuMath matrix which may be used to perform a rotation about the Z-axis by the passed number of degrees.</returns>
	template<typename out_contained_type = float, bool OutColumnMajor_ = true, typename RotX_>
	inline EmuMath::Matrix<4, 4, out_contained_type, OutColumnMajor_> MatrixRotationZDegs(const RotX_& rotation_x_degs_)
	{
		return MatrixRotationZRads<out_contained_type, OutColumnMajor_, RotX_>(EmuCore::Pi::DegsToRads(rotation_x_degs_));
	}
}

#endif
