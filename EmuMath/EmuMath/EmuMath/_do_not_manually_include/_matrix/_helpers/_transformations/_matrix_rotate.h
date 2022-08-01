#ifndef EMU_MATH_MATRIX_ROTATION_TRANSFORMATIONS_H_INC_
#define EMU_MATH_MATRIX_ROTATION_TRANSFORMATIONS_H_INC_ 1

#include "../_common_matrix_helper_includes.h"

namespace EmuMath::Helpers
{
#pragma region ROTATE_X_NORMAL
	/// <summary>
	/// <para> Creates an EmuMath Matrix of the specified type which represents a 3D rotation transformation of `angle_` radians or degrees about the X-axis. </para>
	/// <para> If `AngleIsRads_` is true, `angle_` will be interpreted as radians. If it is false, `angle_` will be interpreted as degrees. </para>
	/// <para> The size of the Matrix may be omitted, in which case the output will be a 4x4 Matrix. </para>
	/// <para> If the output Matrix cannot fit the full rotation Matrix, as much as can be filled in will be provided. </para>
	/// <para> `AngleIsRads_` may be omitted in some cases. If it is omitted, `angle_` will be interpreted as radians. </para>
	/// </summary>
	/// <param name="angle_">Angle of rotation in either radians or degrees.</param>
	/// <returns>EmuMath Matrix representing a 3D rotation transformation about the X-axis based on the provided `angle_` argument.</returns>
	template<bool AngleIsRads_, std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, bool OutColumnMajor_ = true, class Angle_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_> matrix_make_rotation_3d_x(Angle_&& angle_)
	{
		return EmuMath::Helpers::_matrix_underlying::_matrix_make_rotate_3_in_axis<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_, AngleIsRads_, 0, 0, false, true>
		(
			std::forward<Angle_>(angle_)
		);
	}

	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, bool OutColumnMajor_ = true, class Angle_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_> matrix_make_rotation_3d_x(Angle_&& angle_)
	{
		return EmuMath::Helpers::_matrix_underlying::_matrix_make_rotate_3_in_axis<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_, true, 0, 0, false, true>
		(
			std::forward<Angle_>(angle_)
		);
	}

	template<bool AngleIsRads_, typename OutT_, bool OutColumnMajor_ = true, class Angle_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<4, 4, OutT_, OutColumnMajor_> matrix_make_rotation_3d_x(Angle_&& angle_)
	{
		return EmuMath::Helpers::_matrix_underlying::_matrix_make_rotate_3_in_axis<4, 4, OutT_, OutColumnMajor_, AngleIsRads_, 0, 0, false, true>
		(
			std::forward<Angle_>(angle_)
		);
	}

	template<typename OutT_, bool OutColumnMajor_ = true, class Angle_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<4, 4, OutT_, OutColumnMajor_> matrix_make_rotation_3d_x(Angle_&& angle_)
	{
		return EmuMath::Helpers::_matrix_underlying::_matrix_make_rotate_3_in_axis<4, 4, OutT_, OutColumnMajor_, true, 0, 0, false, true>
		(
			std::forward<Angle_>(angle_)
		);
	}

	/// <summary>
	/// <para> Assigns the passed EmuMath Matrix to represent a 3D rotation transformation of `angle_` radians or degrees about the X-axis. </para>
	/// <para> If `AngleIsRads_` is true, `angle_` will be interpreted as radians. If it is false, `angle_` will be interpreted as degrees. </para>
	/// <para> If the output Matrix cannot fit the full rotation Matrix, as much as can be filled in will be provided. </para>
	/// <para> `AngleIsRads_` may be omitted in some cases. If it is omitted, `angle_` will be interpreted as radians. </para>
	/// </summary>
	/// <param name="out_matrix_">EmuMath Matrix to output to.</param>
	/// <param name="angle_">Angle of rotation in either radians or degrees.</param>
	template<bool AngleIsRads_ = true, std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, bool OutColumnMajor_, class Angle_>
	constexpr inline void matrix_assign_rotation_3d_x(EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>& out_matrix_, Angle_&& angle_)
	{
		EmuMath::Helpers::_matrix_underlying::_matrix_assign_rotate_3_in_axis<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_, AngleIsRads_, 0, 0, false, true>
		(
			out_matrix_,
			std::forward<Angle_>(angle_)
		);
	}
#pragma endregion

#pragma region ROTATE_X_CONSTEXPR
	/// <summary>
	/// <para> Creates an EmuMath Matrix of the specified type which represents a 3D rotation transformation of `angle_` radians or degrees about the X-axis. </para>
	/// <para> Calculation will aim to be constexpr-evaluable if possible. </para>
	/// <para> `NumIterations_` is the number of iterations to perform for performing trigonometric functions such as cos and sin. It must be greater than 0. </para>
	/// <para> 
	///		`TrigMod_` is a boolean indicating if a safety modulo calculation should be performed. 
	///		If it is known that `angle_` is not greater than 6.28319 radians (or the degree equivalent after conversion), this modulo has no effect and can be safely skipped.
	/// </para>
	/// <para> If `AngleIsRads_` is true, `angle_` will be interpreted as radians. If it is false, `angle_` will be interpreted as degrees. </para>
	/// <para> The size of the Matrix may be omitted, in which case the output will be a 4x4 Matrix. </para>
	/// <para> If the output Matrix cannot fit the full rotation Matrix, as much as can be filled in will be provided. </para>
	/// <para> `AngleIsRads_` may be omitted in some cases. If it is omitted, `angle_` will be interpreted as radians. </para>
	/// </summary>
	/// <param name="angle_">Angle of rotation in either radians or degrees.</param>
	/// <returns>EmuMath Matrix representing a 3D rotation transformation about the X-axis based on the provided `angle_` argument.</returns>
	template
	<
		std::size_t NumIterations_, bool TrigMod_,
		bool AngleIsRads_, std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, bool OutColumnMajor_ = true, class Angle_
	>
	[[nodiscard]] constexpr inline auto matrix_make_rotation_3d_x_constexpr(Angle_&& angle_)
		-> std::enable_if_t<NumIterations_ != 0, EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>>
	{
		return EmuMath::Helpers::_matrix_underlying::_matrix_make_rotate_3_in_axis
		<
			OutNumColumns_,
			OutNumRows_,
			OutT_,
			OutColumnMajor_,
			AngleIsRads_,
			0,
			NumIterations_,
			TrigMod_,
			true
		>(std::forward<Angle_>(angle_));
	}

	template
	<
		std::size_t NumIterations_, bool TrigMod_,
		std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, bool OutColumnMajor_ = true, class Angle_
	>
	[[nodiscard]] constexpr inline auto matrix_make_rotation_3d_x_constexpr(Angle_&& angle_)
		-> std::enable_if_t<NumIterations_ != 0, EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>>
	{
		return EmuMath::Helpers::_matrix_underlying::_matrix_make_rotate_3_in_axis
		<
			OutNumColumns_,
			OutNumRows_,
			OutT_,
			OutColumnMajor_,
			true,
			0,
			NumIterations_,
			TrigMod_,
			true
		>(std::forward<Angle_>(angle_));
	}

	template
	<
		std::size_t NumIterations_, bool TrigMod_,
		bool AngleIsRads_, typename OutT_, bool OutColumnMajor_ = true, class Angle_
	>
	[[nodiscard]] constexpr inline auto matrix_make_rotation_3d_x_constexpr(Angle_&& angle_)
		-> std::enable_if_t<NumIterations_ != 0, EmuMath::Matrix<4, 4, OutT_, OutColumnMajor_>>
	{
		return EmuMath::Helpers::_matrix_underlying::_matrix_make_rotate_3_in_axis
		<
			4,
			4,
			OutT_,
			OutColumnMajor_,
			AngleIsRads_,
			0,
			NumIterations_,
			TrigMod_,
			true
		>(std::forward<Angle_>(angle_));
	}

	template<std::size_t NumIterations_, bool TrigMod_, typename OutT_, bool OutColumnMajor_ = true, class Angle_>
	[[nodiscard]] constexpr inline auto matrix_make_rotation_3d_x_constexpr(Angle_&& angle_)
		-> std::enable_if_t<NumIterations_ != 0, EmuMath::Matrix<4, 4, OutT_, OutColumnMajor_>>
	{
		return EmuMath::Helpers::_matrix_underlying::_matrix_make_rotate_3_in_axis
		<
			4,
			4,
			OutT_,
			OutColumnMajor_,
			true,
			0,
			NumIterations_,
			TrigMod_,
			true
		>(std::forward<Angle_>(angle_));
	}

	/// <summary>
	/// <para> Assigns the passed EmuMath Matrix to represent a 3D rotation transformation of `angle_` radians or degrees about the X-axis. </para>
	/// <para> Calculation will aim to be constexpr-evaluable if possible. </para>
	/// <para> `NumIterations_` is the number of iterations to perform for performing trigonometric functions such as cos and sin. It must be greater than 0. </para>
	/// <para> 
	///		`TrigMod_` is a boolean indicating if a safety modulo calculation should be performed. 
	///		If it is known that `angle_` is not greater than 6.28319 radians (or the degree equivalent after conversion), this modulo has no effect and can be safely skipped.
	/// </para>
	/// <para> If `AngleIsRads_` is true, `angle_` will be interpreted as radians. If it is false, `angle_` will be interpreted as degrees. </para>
	/// <para> If the output Matrix cannot fit the full rotation Matrix, as much as can be filled in will be provided. </para>
	/// <para> `AngleIsRads_` may be omitted in some cases. If it is omitted, `angle_` will be interpreted as radians. </para>
	/// </summary>
	/// <param name="out_matrix_">EmuMath Matrix to output to.</param>
	/// <param name="angle_">Angle of rotation in either radians or degrees.</param>
	template
	<
		std::size_t NumIterations_, bool TrigMod_, bool AngleIsRads_ = true,
		std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, bool OutColumnMajor_, class Angle_
	>
	constexpr inline auto matrix_assign_rotation_3d_x_constexpr(EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>& out_matrix_, Angle_&& angle_)
		-> std::enable_if_t<NumIterations_ != 0, void>
	{
		EmuMath::Helpers::_matrix_underlying::_matrix_assign_rotate_3_in_axis
		<
			OutNumColumns_,
			OutNumRows_,
			OutT_,
			OutColumnMajor_,
			AngleIsRads_,
			0,
			NumIterations_,
			TrigMod_,
			true
		>(out_matrix_, std::forward<Angle_>(angle_));
	}
#pragma endregion
}

#endif
