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

	template<typename out_contained_type = float, bool OutColumnMajor_ = true, typename X_, typename Y_, typename Z_>
	constexpr inline EmuMath::Matrix<4, 4, out_contained_type, OutColumnMajor_> MatrixScale(const X_& x_, const Y_& y_, const Z_& z_)
	{
		return _underlying_matrix_funcs::_make_scale_matrix<EmuMath::Matrix<4, 4, out_contained_type, OutColumnMajor_>, X_, Y_, Z_>(x_, y_, z_);
	}

	/// <summary> Calculates near and far normalisation cofactors and ouputs them via the passed out_a_ and out_b_ references. </summary>
	/// <typeparam name="Near_">Type used to provide the near_ argument.</typeparam>
	/// <typeparam name="Far_">Type used to provided the far_ argument.</typeparam>
	/// <typeparam name="OutA_">Type referenced for the output of out_a_.</typeparam>
	/// <typeparam name="OutB_">Type referenced for the output of out_b_.</typeparam>
	/// <param name="near_">Near value when creating the normalisation cofactors.</param>
	/// <param name="far_">Far value when creating the normalisation cofactors.</param>
	/// <param name="out_a_">Reference to output the first cofactor to be used via. Output will be the result of -(far / (far - near)).</param>
	/// <param name="out_b_">Reference to output the second cofactor to be used via. Output will be the result of -((f * n) / (f - n)).</param>
	template<typename Near_, typename Far_, typename OutA_, typename OutB_>
	constexpr inline void MatrixBasicPerspectiveNearFarCofactors(const Near_& near_, const Far_& far_, OutA_& out_a_, OutB_& out_b_)
	{
		out_a_ = _underlying_matrix_funcs::_calculate_basic_perspective_near_far_cofactor_a<Near_, Far_, OutA_>(near_, far_);
		out_b_ = _underlying_matrix_funcs::_calculate_basic_perspective_near_far_cofactor_b<Near_, Far_, OutB_>(near_, far_);
	}

	/// <summary> Calculates cofactor a from _calculate_near_far_normalise_values, which will be the result of -(far / (far - near)). </summary>
	/// <typeparam name="Near_">Type used to provide the near_ argument.</typeparam>
	/// <typeparam name="Far_">Type used to provided the far_ argument.</typeparam>
	/// <typeparam name="Out_">Type to output the cofactor as.</typeparam>
	/// <param name="near_">Near value when creating the normalisation cofactor.</param>
	/// <param name="far_">Far value when creating the normalisation cofactor.</param>
	/// <returns>Result of -(far / (far - near)).</returns>
	template<typename Out_ = float, typename Near_, typename Far_>
	constexpr inline Out_ MatrixBasicPerspectiveNearFarCofactorA(const Near_& near_, const Far_& far_)
	{
		return _underlying_matrix_funcs::_calculate_basic_perspective_near_far_cofactor_a<Near_, Far_, Out_>(near_, far_);
	}

	/// <summary> Calculates cofactor b from _calculate_near_far_normalise_values, which will be the result of -((far * near) / (far - near)). </summary>
	/// <typeparam name="Near_">Type used to provide the near_ argument.</typeparam>
	/// <typeparam name="Far_">Type used to provided the far_ argument.</typeparam>
	/// <typeparam name="Out_">Type to output the cofactor as.</typeparam>
	/// <param name="near_">Near value when creating the normalisation cofactor.</param>
	/// <param name="far_">Far value when creating the normalisation cofactor.</param>
	/// <returns>Result of -((f * n) / (f - n)).</returns>
	template<typename Out_ = float, typename Near_, typename Far_>
	constexpr inline Out_ MatrixBasicPerspectiveNearFarCofactorB(const Near_& near_, const Far_& far_)
	{
		return _underlying_matrix_funcs::_calculate_basic_perspective_near_far_cofactor_b<Near_, Far_, Out_>(near_, far_);
	}

	template<std::size_t NumIterations_ = 5, bool Rads_ = true, typename Out_ = float, typename Fov_>
	constexpr inline Out_ MatrixBasicPerspectiveFovScale(const Fov_& fov_)
	{
		if constexpr (Rads_)
		{
			return _underlying_matrix_funcs::_calculate_basic_perspective_fov_scale_rads<NumIterations_, Fov_, Out_>(fov_);
		}
		else
		{
			auto rads_ = fov_ * EmuCore::Pi::PI_DIV_180<EmuCore::TMPHelpers::first_floating_point_t<Fov_, float>>;
			return _underlying_matrix_funcs::_calculate_basic_perspective_fov_scale_rads<NumIterations_, decltype(rads_), Out_>(rads_);
		}
	}

	template<std::size_t NumIterations_ = 5, bool RadsFov_ = true, typename out_contained_type = float, bool OutColumnMajor_ = true, typename Near_, typename Far_, typename Fov_>
	constexpr inline EmuMath::Matrix<4, 4, out_contained_type, OutColumnMajor_> MatrixBasicPerspective(const Near_& near_, const Far_& far_, const Fov_& fov_)
	{
		if constexpr (RadsFov_)
		{
			return _underlying_matrix_funcs::_make_basic_perspective_projection_matrix_rads
			<
				NumIterations_,
				EmuMath::Matrix<4, 4, out_contained_type, OutColumnMajor_>,
				Near_,
				Far_,
				Fov_
			>(near_, far_, fov_); 
		}
		else
		{
			auto fov_rads_ = fov_ * EmuCore::Pi::PI_DIV_180<EmuCore::TMPHelpers::first_floating_point_t<Fov_, float>>;
			return _underlying_matrix_funcs::_make_basic_perspective_projection_matrix_rads
			<
				NumIterations_,
				EmuMath::Matrix<4, 4, out_contained_type, OutColumnMajor_>,
				Near_,
				Far_,
				decltype(fov_rads_)
			>(near_, far_, fov_rads_);
		}
	}

	template<bool FovYIsRads_ = true, typename Out_ = float, std::size_t NumTanIterations_ = 5, bool DoTanMod_ = true, typename FovY_, typename Near_>
	constexpr inline Out_ MatrixPerspectiveScale(const FovY_& fov_angle_y_, const Near_& near_)
	{
		// Output type takes priority for calculation type; this way if less precision than input values, we can save time; if more precision, we can get better approximations
		using calc_type = EmuCore::TMPHelpers::first_floating_point_t<Out_, FovY_, Near_, float>;
		if constexpr (FovYIsRads_)
		{
			return _underlying_matrix_funcs::_calculate_matrix_perspective_projection_scale_rads
			<
				Out_,
				FovY_,
				Near_,
				calc_type,
				EmuCore::do_tan_constexpr<calc_type, NumTanIterations_, DoTanMod_>
			>(fov_angle_y_, near_);
		}
		else
		{
			return MatrixPerspectiveScale<true, Out_, NumTanIterations_, DoTanMod_, calc_type, Near_>
			(
				EmuCore::Pi::DegsToRads(static_cast<calc_type>(fov_angle_y_)),
				near_
			);
		}
	}

	template<bool FovYIsRads_ = true, typename Out_ = float, std::size_t NumTanIterations_ = 5, bool DoTanMod_ = true, typename FovY_, typename Near_>
	constexpr inline Out_ MatrixPerspectiveFrustumEdgeTop(const FovY_& fov_angle_y_, const Near_& near_)
	{
		using calc_type = EmuCore::TMPHelpers::first_floating_point_t<Out_, FovY_, Near_, float>;
		if constexpr (FovYIsRads_)
		{
			return _underlying_matrix_funcs::_calculate_matrix_perspective_edge_top_rads
			<
				Out_,
				FovY_,
				Near_,
				calc_type,
				EmuCore::do_tan_constexpr<calc_type, NumTanIterations_, DoTanMod_>
			>(fov_angle_y_, near_);
		}
		else
		{
			return MatrixPerspectiveFrustumEdgeTop<true, Out_, NumTanIterations_, DoTanMod_, calc_type, Near_>
			(
				EmuCore::Pi::DegsToRads(static_cast<calc_type>(fov_angle_y_)),
				near_
			);
		}
	}

	template<bool FovYIsRads_ = true, typename Out_ = float, std::size_t NumTanIterations_ = 5, bool DoTanMod_ = true, typename FovY_, typename Near_>
	constexpr inline Out_ MatrixPerspectiveFrustumEdgeBottom(const FovY_& fov_angle_y_, const Near_& near_)
	{
		using calc_type = EmuCore::TMPHelpers::first_floating_point_t<Out_, FovY_, Near_, float>;
		if constexpr (FovYIsRads_)
		{
			return _underlying_matrix_funcs::_calculate_matrix_perspective_edge_bottom_rads
			<
				Out_,
				FovY_,
				Near_,
				calc_type,
				EmuCore::do_tan_constexpr<calc_type, NumTanIterations_, DoTanMod_>
			>(fov_angle_y_, near_);
		}
		else
		{
			return MatrixPerspectiveFrustumEdgeBottom<true, Out_, NumTanIterations_, DoTanMod_, calc_type, Near_>
			(
				EmuCore::Pi::DegsToRads(static_cast<calc_type>(fov_angle_y_)),
				near_
			);
		}
	}

	template<bool FovYIsRads_ = true, typename Out_ = float, std::size_t NumTanIterations_ = 5, bool DoTanMod_ = true, typename FovY_, typename Near_, typename AspectRatio_>
	constexpr inline Out_ MatrixPerspectiveFrustumEdgeRight(const FovY_& fov_angle_y_, const Near_& near_, const AspectRatio_& aspect_ratio_)
	{
		using calc_type = EmuCore::TMPHelpers::first_floating_point_t<Out_, FovY_, Near_, AspectRatio_, float>;
		if constexpr (FovYIsRads_)
		{
			return _underlying_matrix_funcs::_calculate_matrix_perspective_edge_right_rads
			<
				Out_,
				FovY_,
				Near_,
				AspectRatio_,
				calc_type,
				EmuCore::do_tan_constexpr<calc_type, NumTanIterations_, DoTanMod_>
			>(fov_angle_y_, near_, aspect_ratio_);
		}
		else
		{
			return MatrixPerspectiveFrustumEdgeRight<true, Out_, NumTanIterations_, DoTanMod_, calc_type, Near_, AspectRatio_>
			(
				EmuCore::Pi::DegsToRads(static_cast<calc_type>(fov_angle_y_)),
				near_,
				aspect_ratio_
			);
		}
	}

	template<bool FovYIsRads_ = true, typename Out_ = float, std::size_t NumTanIterations_ = 5, bool DoTanMod_ = true, typename FovY_, typename Near_, typename AspectRatio_>
	constexpr inline Out_ MatrixPerspectiveFrustumEdgeLeft(const FovY_& fov_angle_y_, const Near_& near_, const AspectRatio_& aspect_ratio_)
	{
		using calc_type = EmuCore::TMPHelpers::first_floating_point_t<Out_, FovY_, Near_, AspectRatio_, float>;
		if constexpr (FovYIsRads_)
		{
			return _underlying_matrix_funcs::_calculate_matrix_perspective_edge_left_rads
			<
				Out_,
				FovY_,
				Near_,
				AspectRatio_,
				calc_type,
				EmuCore::do_tan_constexpr<calc_type, NumTanIterations_, DoTanMod_>
			>(fov_angle_y_, near_, aspect_ratio_);
		}
		else
		{
			return MatrixPerspectiveFrustumEdgeLeft<true, Out_, NumTanIterations_, DoTanMod_, calc_type, Near_, AspectRatio_>
			(
				EmuCore::Pi::DegsToRads(static_cast<calc_type>(fov_angle_y_)),
				near_,
				aspect_ratio_
			);
		}
	}

	template
	<
		bool FovYIsRads_ = true,
		std::size_t NumTanIterations_ = 5,
		bool DoTanMod_ = true,
		typename FovY_,
		typename Near_,
		typename AspectRatio_,
		typename OutLeft_,
		typename OutRight_,
		typename OutBottom_,
		typename OutTop_
	>
	constexpr inline void MatrixPerspectiveFrustumEdges
	(
		const FovY_& fov_angle_y_,
		const Near_& near_,
		const AspectRatio_& aspect_ratio_,
		OutLeft_& out_left_,
		OutRight_& out_right_,
		OutBottom_& out_bottom_,
		OutTop_& out_top_
	)
	{
		using calc_type = EmuCore::TMPHelpers::first_floating_point_t<FovY_, Near_, AspectRatio_, OutLeft_, OutRight_, OutBottom_, OutTop_, float>;
		if constexpr (FovYIsRads_)
		{
			_underlying_matrix_funcs::_calculate_matrix_perspective_edges_rads
			<
				FovY_,
				Near_,
				AspectRatio_,
				OutLeft_,
				OutRight_,
				OutBottom_,
				OutTop_,
				calc_type,
				EmuCore::do_tan_constexpr<calc_type, NumTanIterations_, DoTanMod_>
			>(fov_angle_y_, near_, aspect_ratio_, out_left_, out_right_, out_bottom_, out_top_);
		}
		else
		{
			MatrixPerspectiveFrustumEdges<true, NumTanIterations_, DoTanMod_, calc_type, Near_, AspectRatio_, OutLeft_, OutRight_, OutBottom_, OutTop_>
			(
				EmuCore::Pi::DegsToRads(static_cast<calc_type>(fov_angle_y_)),
				near_,
				aspect_ratio_,
				out_left_,
				out_right_,
				out_bottom_,
				out_top_
			);
		}
	}

	template
	<
		bool FovYIsRads_ = true,
		typename out_contained_type = float,
		bool OutColumnMajor_ = true,
		std::size_t NumTanIterations_ = 5,
		bool DoTanMod_ = true,
		typename FovY_,
		typename Near_,
		typename Far_,
		typename AspectRatio_
	>
	constexpr inline EmuMath::Matrix<4, 4, out_contained_type, OutColumnMajor_> MatrixPerspectiveWithFrustum
	(
		const FovY_& fov_angle_y_,
		const Near_& near_,
		const Far_& far_,
		const AspectRatio_& aspect_ratio_
	)
	{
		using calc_type = EmuCore::TMPHelpers::first_floating_point_t<out_contained_type, FovY_, Near_, Far_, AspectRatio_, float>;
		if constexpr (FovYIsRads_)
		{
			return _underlying_matrix_funcs::_make_perspective_matrix_with_frustum_rads
			<
				EmuMath::Matrix<4, 4, out_contained_type, OutColumnMajor_>,
				FovY_,
				Near_,
				Far_,
				AspectRatio_,
				calc_type,
				EmuCore::do_tan_constexpr<calc_type, NumTanIterations_, DoTanMod_>
			>(fov_angle_y_, near_, far_, aspect_ratio_);
		}
		else
		{
			return MatrixPerspectiveWithFrustum<true, out_contained_type, OutColumnMajor_, NumTanIterations_, DoTanMod_, FovY_, Near_, Far_, AspectRatio_>
			(
				fov_angle_y_,
				near_,
				far_,
				aspect_ratio_
			);
		}
	}

	template
	<
		typename out_contained_type = float,
		bool OutColumnMajor_ = true,
		typename Near_,
		typename Far_,
		typename Left_,
		typename Right_,
		typename Bottom_,
		typename Top_
	>
	constexpr inline EmuMath::Matrix<4, 4, out_contained_type, OutColumnMajor_> MatrixPerspectiveWithFrustum
	(
		const Near_& near_,
		const Far_& far_,
		const Left_& left_,
		const Right_& right_,
		const Bottom_& bottom_,
		const Top_& top_
	)
	{
		using calc_type = EmuCore::TMPHelpers::first_floating_point_t<out_contained_type, Near_, Far_, Left_, Right_, Bottom_, Top_, float>;
		return _underlying_matrix_funcs::_make_perspective_matrix_with_frustum_rads
		<
			EmuMath::Matrix<4, 4, out_contained_type, OutColumnMajor_>,
			Near_,
			Far_,
			Left_,
			Right_,
			Bottom_,
			Top_,
			calc_type
		>(near_, far_, left_, right_, bottom_, top_);
	}

	template<typename out_contained_type = float, bool OutColumnMajor_ = true, typename Left_, typename Right_, typename Bottom_, typename Top_, typename Near_, typename Far_>
	constexpr inline EmuMath::Matrix<4, 4, out_contained_type, OutColumnMajor_> MatrixOrthographic
	(
		const Left_& left_,
		const Right_& right_,
		const Bottom_& bottom_,
		const Top_& top_,
		const Near_& near_,
		const Far_& far_
	)
	{
		using calc_type = EmuCore::TMPHelpers::first_floating_point_t<out_contained_type, Left_, Right_, Bottom_, Top_, Near_, Far_, float>;
		return _underlying_matrix_funcs::_make_orthograhpic_projection_matrix_
		<
			EmuMath::Matrix<4, 4, out_contained_type, OutColumnMajor_>,
			Left_,
			Right_,
			Bottom_,
			Top_,
			Near_,
			Far_,
			calc_type
		>(left_, right_, bottom_, top_, near_, far_);
	}
	template<typename out_contained_type = float, bool OutColumnMajor_ = true, typename Width_, typename Height_, typename Near_, typename Far_>
	constexpr inline EmuMath::Matrix<4, 4, out_contained_type, OutColumnMajor_> MatrixOrthographic
	(
		const Width_ width_,
		const Height_& height_,
		const Near_& near_,
		const Far_& far_
	)
	{
		using calc_type = EmuCore::TMPHelpers::first_floating_point_t<out_contained_type, Width_, Height_, Near_, Far_, float>;
		const calc_type zero_ = calc_type(0);
		return _underlying_matrix_funcs::_make_orthograhpic_projection_matrix_
		<
			EmuMath::Matrix<4, 4, out_contained_type, OutColumnMajor_>,
			calc_type,
			Width_,
			calc_type,
			Height_,
			Near_,
			Far_,
			calc_type
		>(zero_, width_, zero_, height_, near_, far_);
	}
}

#endif
