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
	[[nodiscard]] constexpr inline EmuMath::Matrix<4, 4, out_contained_type, OutColumnMajor_> matrix_translation(const X_& x_, const Y_& y_, const Z_& z_)
	{
		return _underlying_matrix_funcs::_make_translation_matrix<EmuMath::Matrix<4, 4, out_contained_type, OutColumnMajor_>, X_, Y_, Z_>(x_, y_, z_);
	}

	/// <summary>
	/// <para> Creates a 4x4 transformation matrix which may be used to rotate a point about the X-axis by the provided number of radians or degrees. </para>
	/// <para> This function may make sacrifices to be evaluable at compile time. If it is being called at runtime, it is recommended to use matrix_rotation_x instead. </para>
	/// <para> NumIterations_ may be increased to improve accuracy at the cost of performance, or decreased to reduce accuracy and increase performance. </para>
	/// </summary>
	/// <typeparam name="out_contained_type">Type to be contained in the output rotation matrix.</typeparam>
	/// <typeparam name="RotX_">Type used to provide the amount of radians or degrees to rotate about the X-axis.</typeparam>
	/// <param name="rot_x_">The amount of radians or degrees to rotate about the X-axis.</param>
	/// <returns>4x4 EmuMath matrix which may be used to perform a rotation about the X-axis by the passed number of radians or degrees.</returns>
	template<bool RotIsRads_ = true, std::size_t NumIterations_ = 3, bool DoMod_ = true, typename out_contained_type = float, bool OutColumnMajor_ = true, typename RotX_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<4, 4, out_contained_type, OutColumnMajor_> matrix_rotation_x_constexpr(const RotX_& rot_x_)
	{
		if constexpr(RotIsRads_)
		{
			return _underlying_matrix_funcs::_make_rotation_matrix_x
			<
				EmuMath::Matrix<4, 4, out_contained_type, OutColumnMajor_>,
				RotX_,
				EmuCore::do_cos_constexpr<typename EmuMath::Matrix<4, 4, out_contained_type, OutColumnMajor_>::value_type, NumIterations_, DoMod_>,
				EmuCore::do_sin_constexpr<typename EmuMath::Matrix<4, 4, out_contained_type, OutColumnMajor_>::value_type, NumIterations_, DoMod_>
			>(rot_x_);
		}
		else
		{
			using rot_x_floating_point = typename EmuCore::TMPHelpers::first_floating_point<RotX_, float>::type;
			return matrix_rotation_x_constexpr<true, NumIterations_, DoMod_, out_contained_type, OutColumnMajor_, rot_x_floating_point>
			(
				EmuCore::Pi::DegsToRads(static_cast<rot_x_floating_point>(rot_x_))
			);
		}
	}

	/// <summary>
	/// <para> Creates a 4x4 transformation matrix which may be used to rotate a point about the Y-axis by the provided number of radians or degrees. </para>
	/// <para> This function may make sacrifices to be evaluable at compile time. If it is being called at runtime, it is recommended to use matrix_rotation_y instead. </para>
	/// <para> NumIterations_ may be increased to improve accuracy at the cost of performance, or decreased to reduce accuracy and increase performance. </para>
	/// </summary>
	/// <typeparam name="out_contained_type">Type to be contained in the output rotation matrix.</typeparam>
	/// <typeparam name="RotY_">Type used to provide the amount of radians or degrees to rotate about the Y-axis.</typeparam>
	/// <param name="rot_y_">The amount of radians or degrees to rotate about the Y-axis.</param>
	/// <returns>4x4 EmuMath matrix which may be used to perform a rotation about the Y-axis by the passed number of radians or degrees.</returns>
	template<bool RotIsRads_ = true, std::size_t NumIterations_ = 3, bool DoMod_ = true, typename out_contained_type = float, bool OutColumnMajor_ = true, typename RotY_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<4, 4, out_contained_type, OutColumnMajor_> matrix_rotation_y_constexpr(const RotY_& rot_y_)
	{
		if constexpr (RotIsRads_)
		{
			return _underlying_matrix_funcs::_make_rotation_matrix_y
			<
				EmuMath::Matrix<4, 4, out_contained_type, OutColumnMajor_>,
				RotY_,
				EmuCore::do_cos_constexpr<typename EmuMath::Matrix<4, 4, out_contained_type, OutColumnMajor_>::value_type, NumIterations_, DoMod_>,
				EmuCore::do_sin_constexpr<typename EmuMath::Matrix<4, 4, out_contained_type, OutColumnMajor_>::value_type, NumIterations_, DoMod_>
			>(rot_y_);
		}
		else
		{
			using rot_y_floating_point = typename EmuCore::TMPHelpers::first_floating_point<RotY_, float>::type;
			return matrix_rotation_y_constexpr<true, NumIterations_, DoMod_, out_contained_type, OutColumnMajor_, rot_y_floating_point>
			(
				EmuCore::Pi::DegsToRads(static_cast<rot_y_floating_point>(rot_y_))
			);
		}
	}

	/// <summary>
	/// <para> Creates a 4x4 transformation matrix which may be used to rotate a point about the Z-axis by the provided number of radians or degrees. </para>
	/// <para> This function may make sacrifices to be evaluable at compile time. If it is being called at runtime, it is recommended to use matrix_rotation_z instead. </para>
	/// <para> NumIterations_ may be increased to improve accuracy at the cost of performance, or decreased to reduce accuracy and increase performance. </para>
	/// </summary>
	/// <typeparam name="out_contained_type">Type to be contained in the output rotation matrix.</typeparam>
	/// <typeparam name="RotZ_">Type used to provide the amount of radians or degrees to rotate about the Z-axis.</typeparam>
	/// <param name="rot_z_">The amount of radians or degrees to rotate about the Z-axis.</param>
	/// <returns>4x4 EmuMath matrix which may be used to perform a rotation about the Z-axis by the passed number of radians or degrees.</returns>
	template<bool RotIsRads_ = true, std::size_t NumIterations_ = 3, bool DoMod_ = true, typename out_contained_type = float, bool OutColumnMajor_ = true, typename RotZ_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<4, 4, out_contained_type, OutColumnMajor_> matrix_rotation_z_constexpr(const RotZ_& rot_z_)
	{
		if constexpr (RotIsRads_)
		{
			return _underlying_matrix_funcs::_make_rotation_matrix_z
			<
				EmuMath::Matrix<4, 4, out_contained_type, OutColumnMajor_>,
				RotZ_,
				EmuCore::do_cos_constexpr<typename EmuMath::Matrix<4, 4, out_contained_type, OutColumnMajor_>::value_type, NumIterations_, DoMod_>,
				EmuCore::do_sin_constexpr<typename EmuMath::Matrix<4, 4, out_contained_type, OutColumnMajor_>::value_type, NumIterations_, DoMod_>
			>(rot_z_);
		}
		else
		{
			using rot_z_floating_point = typename EmuCore::TMPHelpers::first_floating_point<RotZ_, float>::type;
			return matrix_rotation_z_constexpr<true, NumIterations_, DoMod_, out_contained_type, OutColumnMajor_, rot_z_floating_point>
			(
				EmuCore::Pi::DegsToRads(static_cast<rot_z_floating_point>(rot_z_))
			);
		}
	}

	/// <summary> Creates a 4x4 transformation matrix which may be used to rotate a point about the X-axis by the provided number of radians or degrees. </summary>
	/// <typeparam name="out_contained_type">Type to be contained in the output rotation matrix.</typeparam>
	/// <typeparam name="RotX_">Type used to provide the amount of radians or degrees to rotate about the X-axis.</typeparam>
	/// <param name="rot_x_">The amount of radians or degrees to rotate about the X-axis.</param>
	/// <returns>4x4 EmuMath matrix which may be used to perform a rotation about the X-axis by the passed number of radians or degrees.</returns>
	template<bool RotIsRads_ = true, typename out_contained_type = float, bool OutColumnMajor_ = true, typename RotX_>
	[[nodiscard]] inline EmuMath::Matrix<4, 4, out_contained_type, OutColumnMajor_> matrix_rotation_x(const RotX_& rot_x_)
	{
		if constexpr (RotIsRads_)
		{
			return _underlying_matrix_funcs::_make_rotation_matrix_x
			<
				EmuMath::Matrix<4, 4, out_contained_type, OutColumnMajor_>,
				RotX_,
				EmuCore::do_cos<typename EmuMath::Matrix<4, 4, out_contained_type, OutColumnMajor_>::value_type>,
				EmuCore::do_sin<typename EmuMath::Matrix<4, 4, out_contained_type, OutColumnMajor_>::value_type>
			>(rot_x_);
		}
		else
		{
			using rot_x_floating_point = typename EmuCore::TMPHelpers::first_floating_point<RotX_, float>::type;
			return matrix_rotation_x<true, out_contained_type, OutColumnMajor_, rot_x_floating_point>
			(
				EmuCore::Pi::DegsToRads(static_cast<rot_x_floating_point>(rot_x_))
			);
		}
	}

	/// <summary> Creates a 4x4 transformation matrix which may be used to rotate a point about the Y-axis by the provided number of radians or degrees. </summary>
	/// <typeparam name="out_contained_type">Type to be contained in the output rotation matrix.</typeparam>
	/// <typeparam name="RotY_">Type used to provide the amount of radians or degrees to rotate about the Y-axis.</typeparam>
	/// <param name="rot_y_">The amount of radians or degrees to rotate about the Y-axis.</param>
	/// <returns>4x4 EmuMath matrix which may be used to perform a rotation about the Y-axis by the passed number of radians or degrees.</returns>
	template<bool RotIsRads_ = true, typename out_contained_type = float, bool OutColumnMajor_ = true, typename RotY_>
	[[nodiscard]] inline EmuMath::Matrix<4, 4, out_contained_type, OutColumnMajor_> matrix_rotation_y(const RotY_& rot_y_)
	{
		if constexpr (RotIsRads_)
		{
			return _underlying_matrix_funcs::_make_rotation_matrix_y
			<
				EmuMath::Matrix<4, 4, out_contained_type, OutColumnMajor_>,
				RotY_,
				EmuCore::do_cos<typename EmuMath::Matrix<4, 4, out_contained_type, OutColumnMajor_>::value_type>,
				EmuCore::do_sin<typename EmuMath::Matrix<4, 4, out_contained_type, OutColumnMajor_>::value_type>
			>(rot_y_);
		}
		else
		{
			using rot_y_floating_point = typename EmuCore::TMPHelpers::first_floating_point<RotY_, float>::type;
			return matrix_rotation_y<true, out_contained_type, OutColumnMajor_, rot_y_floating_point>
			(
				EmuCore::Pi::DegsToRads(static_cast<rot_y_floating_point>(rot_y_))
			);
		}
	}

	/// <summary> Creates a 4x4 transformation matrix which may be used to rotate a point about the Y-axis by the provided number of radians or degrees. </summary>
	/// <typeparam name="out_contained_type">Type to be contained in the output rotation matrix.</typeparam>
	/// <typeparam name="RotZ_">Type used to provide the amount of radians or degrees to rotate about the Y-axis.</typeparam>
	/// <param name="rot_z_">The amount of radians or degrees to rotate about the Y-axis.</param>
	/// <returns>4x4 EmuMath matrix which may be used to perform a rotation about the Y-axis by the passed number of radians or degrees.</returns>
	template<bool RotIsRads_ = true, typename out_contained_type = float, bool OutColumnMajor_ = true, typename RotZ_>
	[[nodiscard]] inline EmuMath::Matrix<4, 4, out_contained_type, OutColumnMajor_> matrix_rotation_z(const RotZ_& rot_z_)
	{
		if constexpr (RotIsRads_)
		{
			return _underlying_matrix_funcs::_make_rotation_matrix_z
			<
				EmuMath::Matrix<4, 4, out_contained_type, OutColumnMajor_>,
				RotZ_,
				EmuCore::do_cos<typename EmuMath::Matrix<4, 4, out_contained_type, OutColumnMajor_>::value_type>,
				EmuCore::do_sin<typename EmuMath::Matrix<4, 4, out_contained_type, OutColumnMajor_>::value_type>
			>(rot_z_);
		}
		else
		{
			using rot_z_floating_point = typename EmuCore::TMPHelpers::first_floating_point<RotZ_, float>::type;
			return matrix_rotation_z<true, out_contained_type, OutColumnMajor_, rot_z_floating_point>
			(
				EmuCore::Pi::DegsToRads(static_cast<rot_z_floating_point>(rot_z_))
			);
		}
	}

	/// <summary>
	/// <para>
	///		Creates a 4x4 transformation matrix which may be used to perform a scale of 
	///		x_ in the X-dimension, y_ in the Y-dimension, and z_ in the Z-dimension.
	/// </para>
	/// <para> x_, y_, and z_ may be any types, but they must be convertible to the output matrix's contained type (provided as the out_contained_type argument). </para>
	/// </summary>
	/// <typeparam name="out_contained_type">Type to be contained within the output matrix.</typeparam>
	/// <typeparam name="X_">Type use for the argument representing the scaling in the X-dimension.</typeparam>
	/// <typeparam name="Y_">Type use for the argument representing the scaling in the Y-dimension.</typeparam>
	/// <typeparam name="Z_">Type use for the argument representing the scaling in the Z-dimension.</typeparam>
	/// <param name="x_">Percentage to scale in the X-dimension, where 0 is 0%, and 1 is 100%.</param>
	/// <param name="y_">Percentage to scale in the Y-dimension, where 0 is 0%, and 1 is 100%.</param>
	/// <param name="z_">Percentage to scale in the Z-dimension, where 0 is 0%, and 1 is 100%.</param>
	/// <returns>4x4 EmuMath matrix which may be used to perform a scale of the specified amounts in respective dimensions.</returns>
	template<typename out_contained_type = float, bool OutColumnMajor_ = true, typename X_, typename Y_, typename Z_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<4, 4, out_contained_type, OutColumnMajor_> matrix_scale(const X_& x_, const Y_& y_, const Z_& z_)
	{
		return _underlying_matrix_funcs::_make_scale_matrix
		<
			EmuMath::Matrix<4, 4, out_contained_type, OutColumnMajor_>,
			X_,
			Y_,
			Z_
		>(x_, y_, z_);
	}
}

#endif
