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
	/// <para> `NumIterations_` is the number of iterations to perform for executing trigonometric functions such as cos and sin. It must be greater than 0. </para>
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
	/// <para> `NumIterations_` is the number of iterations to perform for executing trigonometric functions such as cos and sin. It must be greater than 0. </para>
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

#pragma region ROTATE_Y_NORMAL
	/// <summary>
	/// <para> Creates an EmuMath Matrix of the specified type which represents a 3D rotation transformation of `angle_` radians or degrees about the Y-axis. </para>
	/// <para> If `AngleIsRads_` is true, `angle_` will be interpreted as radians. If it is false, `angle_` will be interpreted as degrees. </para>
	/// <para> The size of the Matrix may be omitted, in which case the output will be a 4x4 Matrix. </para>
	/// <para> If the output Matrix cannot fit the full rotation Matrix, as much as can be filled in will be provided. </para>
	/// <para> `AngleIsRads_` may be omitted in some cases. If it is omitted, `angle_` will be interpreted as radians. </para>
	/// </summary>
	/// <param name="angle_">Angle of rotation in either radians or degrees.</param>
	/// <returns>EmuMath Matrix representing a 3D rotation transformation about the Y-axis based on the provided `angle_` argument.</returns>
	template<bool AngleIsRads_, std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, bool OutColumnMajor_ = true, class Angle_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_> matrix_make_rotation_3d_y(Angle_&& angle_)
	{
		return EmuMath::Helpers::_matrix_underlying::_matrix_make_rotate_3_in_axis<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_, AngleIsRads_, 1, 0, false, true>
		(
			std::forward<Angle_>(angle_)
		);
	}

	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, bool OutColumnMajor_ = true, class Angle_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_> matrix_make_rotation_3d_y(Angle_&& angle_)
	{
		return EmuMath::Helpers::_matrix_underlying::_matrix_make_rotate_3_in_axis<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_, true, 1, 0, false, true>
		(
			std::forward<Angle_>(angle_)
		);
	}

	template<bool AngleIsRads_, typename OutT_, bool OutColumnMajor_ = true, class Angle_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<4, 4, OutT_, OutColumnMajor_> matrix_make_rotation_3d_y(Angle_&& angle_)
	{
		return EmuMath::Helpers::_matrix_underlying::_matrix_make_rotate_3_in_axis<4, 4, OutT_, OutColumnMajor_, AngleIsRads_, 1, 0, false, true>
		(
			std::forward<Angle_>(angle_)
		);
	}

	template<typename OutT_, bool OutColumnMajor_ = true, class Angle_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<4, 4, OutT_, OutColumnMajor_> matrix_make_rotation_3d_y(Angle_&& angle_)
	{
		return EmuMath::Helpers::_matrix_underlying::_matrix_make_rotate_3_in_axis<4, 4, OutT_, OutColumnMajor_, true, 1, 0, false, true>
		(
			std::forward<Angle_>(angle_)
		);
	}

	/// <summary>
	/// <para> Assigns the passed EmuMath Matrix to represent a 3D rotation transformation of `angle_` radians or degrees about the Y-axis. </para>
	/// <para> If `AngleIsRads_` is true, `angle_` will be interpreted as radians. If it is false, `angle_` will be interpreted as degrees. </para>
	/// <para> If the output Matrix cannot fit the full rotation Matrix, as much as can be filled in will be provided. </para>
	/// <para> `AngleIsRads_` may be omitted in some cases. If it is omitted, `angle_` will be interpreted as radians. </para>
	/// </summary>
	/// <param name="out_matrix_">EmuMath Matrix to output to.</param>
	/// <param name="angle_">Angle of rotation in either radians or degrees.</param>
	template<bool AngleIsRads_ = true, std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, bool OutColumnMajor_, class Angle_>
	constexpr inline void matrix_assign_rotation_3d_y(EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>& out_matrix_, Angle_&& angle_)
	{
		EmuMath::Helpers::_matrix_underlying::_matrix_assign_rotate_3_in_axis<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_, AngleIsRads_, 1, 0, false, true>
		(
			out_matrix_,
			std::forward<Angle_>(angle_)
		);
	}
#pragma endregion

#pragma region ROTATE_Y_CONSTEXPR
	/// <summary>
	/// <para> Creates an EmuMath Matrix of the specified type which represents a 3D rotation transformation of `angle_` radians or degrees about the Y-axis. </para>
	/// <para> Calculation will aim to be constexpr-evaluable if possible. </para>
	/// <para> `NumIterations_` is the number of iterations to perform for executing trigonometric functions such as cos and sin. It must be greater than 0. </para>
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
	/// <returns>EmuMath Matrix representing a 3D rotation transformation about the Y-axis based on the provided `angle_` argument.</returns>
	template
	<
		std::size_t NumIterations_, bool TrigMod_,
		bool AngleIsRads_, std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, bool OutColumnMajor_ = true, class Angle_
	>
	[[nodiscard]] constexpr inline auto matrix_make_rotation_3d_y_constexpr(Angle_&& angle_)
		-> std::enable_if_t<NumIterations_ != 0, EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>>
	{
		return EmuMath::Helpers::_matrix_underlying::_matrix_make_rotate_3_in_axis
		<
			OutNumColumns_,
			OutNumRows_,
			OutT_,
			OutColumnMajor_,
			AngleIsRads_,
			1,
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
	[[nodiscard]] constexpr inline auto matrix_make_rotation_3d_y_constexpr(Angle_&& angle_)
		-> std::enable_if_t<NumIterations_ != 0, EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>>
	{
		return EmuMath::Helpers::_matrix_underlying::_matrix_make_rotate_3_in_axis
		<
			OutNumColumns_,
			OutNumRows_,
			OutT_,
			OutColumnMajor_,
			true,
			1,
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
	[[nodiscard]] constexpr inline auto matrix_make_rotation_3d_y_constexpr(Angle_&& angle_)
		-> std::enable_if_t<NumIterations_ != 0, EmuMath::Matrix<4, 4, OutT_, OutColumnMajor_>>
	{
		return EmuMath::Helpers::_matrix_underlying::_matrix_make_rotate_3_in_axis
		<
			4,
			4,
			OutT_,
			OutColumnMajor_,
			AngleIsRads_,
			1,
			NumIterations_,
			TrigMod_,
			true
		>(std::forward<Angle_>(angle_));
	}

	template<std::size_t NumIterations_, bool TrigMod_, typename OutT_, bool OutColumnMajor_ = true, class Angle_>
	[[nodiscard]] constexpr inline auto matrix_make_rotation_3d_y_constexpr(Angle_&& angle_)
		-> std::enable_if_t<NumIterations_ != 0, EmuMath::Matrix<4, 4, OutT_, OutColumnMajor_>>
	{
		return EmuMath::Helpers::_matrix_underlying::_matrix_make_rotate_3_in_axis
		<
			4,
			4,
			OutT_,
			OutColumnMajor_,
			true,
			1,
			NumIterations_,
			TrigMod_,
			true
		>(std::forward<Angle_>(angle_));
	}

	/// <summary>
	/// <para> Assigns the passed EmuMath Matrix to represent a 3D rotation transformation of `angle_` radians or degrees about the X-axis. </para>
	/// <para> Calculation will aim to be constexpr-evaluable if possible. </para>
	/// <para> `NumIterations_` is the number of iterations to perform for executing trigonometric functions such as cos and sin. It must be greater than 0. </para>
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
	constexpr inline auto matrix_assign_rotation_3d_y_constexpr(EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>& out_matrix_, Angle_&& angle_)
		-> std::enable_if_t<NumIterations_ != 0, void>
	{
		EmuMath::Helpers::_matrix_underlying::_matrix_assign_rotate_3_in_axis
		<
			OutNumColumns_,
			OutNumRows_,
			OutT_,
			OutColumnMajor_,
			AngleIsRads_,
			1,
			NumIterations_,
			TrigMod_,
			true
		>(out_matrix_, std::forward<Angle_>(angle_));
	}
#pragma endregion

#pragma region ROTATE_Z_NORMAL
	/// <summary>
	/// <para> Creates an EmuMath Matrix of the specified type which represents a 3D rotation transformation of `angle_` radians or degrees about the Z-axis. </para>
	/// <para> If `AngleIsRads_` is true, `angle_` will be interpreted as radians. If it is false, `angle_` will be interpreted as degrees. </para>
	/// <para> The size of the Matrix may be omitted, in which case the output will be a 4x4 Matrix. </para>
	/// <para> If the output Matrix cannot fit the full rotation Matrix, as much as can be filled in will be provided. </para>
	/// <para> `AngleIsRads_` may be omitted in some cases. If it is omitted, `angle_` will be interpreted as radians. </para>
	/// </summary>
	/// <param name="angle_">Angle of rotation in either radians or degrees.</param>
	/// <returns>EmuMath Matrix representing a 3D rotation transformation about the Z-axis based on the provided `angle_` argument.</returns>
	template<bool AngleIsRads_, std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, bool OutColumnMajor_ = true, class Angle_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_> matrix_make_rotation_3d_z(Angle_&& angle_)
	{
		return EmuMath::Helpers::_matrix_underlying::_matrix_make_rotate_3_in_axis<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_, AngleIsRads_, 2, 0, false, true>
		(
			std::forward<Angle_>(angle_)
		);
	}

	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, bool OutColumnMajor_ = true, class Angle_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_> matrix_make_rotation_3d_z(Angle_&& angle_)
	{
		return EmuMath::Helpers::_matrix_underlying::_matrix_make_rotate_3_in_axis<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_, true, 2, 0, false, true>
		(
			std::forward<Angle_>(angle_)
		);
	}

	template<bool AngleIsRads_, typename OutT_, bool OutColumnMajor_ = true, class Angle_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<4, 4, OutT_, OutColumnMajor_> matrix_make_rotation_3d_z(Angle_&& angle_)
	{
		return EmuMath::Helpers::_matrix_underlying::_matrix_make_rotate_3_in_axis<4, 4, OutT_, OutColumnMajor_, AngleIsRads_, 2, 0, false, true>
		(
			std::forward<Angle_>(angle_)
		);
	}

	template<typename OutT_, bool OutColumnMajor_ = true, class Angle_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<4, 4, OutT_, OutColumnMajor_> matrix_make_rotation_3d_z(Angle_&& angle_)
	{
		return EmuMath::Helpers::_matrix_underlying::_matrix_make_rotate_3_in_axis<4, 4, OutT_, OutColumnMajor_, true, 2, 0, false, true>
		(
			std::forward<Angle_>(angle_)
		);
	}

	/// <summary>
	/// <para> Assigns the passed EmuMath Matrix to represent a 3D rotation transformation of `angle_` radians or degrees about the Z-axis. </para>
	/// <para> If `AngleIsRads_` is true, `angle_` will be interpreted as radians. If it is false, `angle_` will be interpreted as degrees. </para>
	/// <para> If the output Matrix cannot fit the full rotation Matrix, as much as can be filled in will be provided. </para>
	/// <para> `AngleIsRads_` may be omitted in some cases. If it is omitted, `angle_` will be interpreted as radians. </para>
	/// </summary>
	/// <param name="out_matrix_">EmuMath Matrix to output to.</param>
	/// <param name="angle_">Angle of rotation in either radians or degrees.</param>
	template<bool AngleIsRads_ = true, std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, bool OutColumnMajor_, class Angle_>
	constexpr inline void matrix_assign_rotation_3d_z(EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>& out_matrix_, Angle_&& angle_)
	{
		EmuMath::Helpers::_matrix_underlying::_matrix_assign_rotate_3_in_axis<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_, AngleIsRads_, 2, 0, false, true>
		(
			out_matrix_,
			std::forward<Angle_>(angle_)
		);
	}
#pragma endregion

#pragma region ROTATE_Z_CONSTEXPR
	/// <summary>
	/// <para> Creates an EmuMath Matrix of the specified type which represents a 3D rotation transformation of `angle_` radians or degrees about the Z-axis. </para>
	/// <para> Calculation will aim to be constexpr-evaluable if possible. </para>
	/// <para> `NumIterations_` is the number of iterations to perform for executing trigonometric functions such as cos and sin. It must be greater than 0. </para>
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
	/// <returns>EmuMath Matrix representing a 3D rotation transformation about the Z-axis based on the provided `angle_` argument.</returns>
	template
	<
		std::size_t NumIterations_, bool TrigMod_,
		bool AngleIsRads_, std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, bool OutColumnMajor_ = true, class Angle_
	>
	[[nodiscard]] constexpr inline auto matrix_make_rotation_3d_z_constexpr(Angle_&& angle_)
		-> std::enable_if_t<NumIterations_ != 0, EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>>
	{
		return EmuMath::Helpers::_matrix_underlying::_matrix_make_rotate_3_in_axis
		<
			OutNumColumns_,
			OutNumRows_,
			OutT_,
			OutColumnMajor_,
			AngleIsRads_,
			2,
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
	[[nodiscard]] constexpr inline auto matrix_make_rotation_3d_z_constexpr(Angle_&& angle_)
		-> std::enable_if_t<NumIterations_ != 0, EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>>
	{
		return EmuMath::Helpers::_matrix_underlying::_matrix_make_rotate_3_in_axis
		<
			OutNumColumns_,
			OutNumRows_,
			OutT_,
			OutColumnMajor_,
			true,
			2,
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
	[[nodiscard]] constexpr inline auto matrix_make_rotation_3d_z_constexpr(Angle_&& angle_)
		-> std::enable_if_t<NumIterations_ != 0, EmuMath::Matrix<4, 4, OutT_, OutColumnMajor_>>
	{
		return EmuMath::Helpers::_matrix_underlying::_matrix_make_rotate_3_in_axis
		<
			4,
			4,
			OutT_,
			OutColumnMajor_,
			AngleIsRads_,
			2,
			NumIterations_,
			TrigMod_,
			true
		>(std::forward<Angle_>(angle_));
	}

	template<std::size_t NumIterations_, bool TrigMod_, typename OutT_, bool OutColumnMajor_ = true, class Angle_>
	[[nodiscard]] constexpr inline auto matrix_make_rotation_3d_z_constexpr(Angle_&& angle_)
		-> std::enable_if_t<NumIterations_ != 0, EmuMath::Matrix<4, 4, OutT_, OutColumnMajor_>>
	{
		return EmuMath::Helpers::_matrix_underlying::_matrix_make_rotate_3_in_axis
		<
			4,
			4,
			OutT_,
			OutColumnMajor_,
			true,
			2,
			NumIterations_,
			TrigMod_,
			true
		>(std::forward<Angle_>(angle_));
	}

	/// <summary>
	/// <para> Assigns the passed EmuMath Matrix to represent a 3D rotation transformation of `angle_` radians or degrees about the Z-axis. </para>
	/// <para> Calculation will aim to be constexpr-evaluable if possible. </para>
	/// <para> `NumIterations_` is the number of iterations to perform for executing trigonometric functions such as cos and sin. It must be greater than 0. </para>
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
	constexpr inline auto matrix_assign_rotation_3d_z_constexpr(EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>& out_matrix_, Angle_&& angle_)
		-> std::enable_if_t<NumIterations_ != 0, void>
	{
		EmuMath::Helpers::_matrix_underlying::_matrix_assign_rotate_3_in_axis
		<
			OutNumColumns_,
			OutNumRows_,
			OutT_,
			OutColumnMajor_,
			AngleIsRads_,
			2,
			NumIterations_,
			TrigMod_,
			true
		>(out_matrix_, std::forward<Angle_>(angle_));
	}
#pragma endregion

#pragma region QUAT_TO_MAT_VALIDITY_CHECKS
	/// <summary>
	/// <para> Check to see if a Matrix of the provided type can be calculated from Quaternions with the provided typeargs. </para>
	/// <para>
	///		If no arguments are provided for `OptionalQuaternionTs_`: 
	///		This is a check to see if a direct Quaternion-to-Matrix conversion can be performed. 
	/// </para>
	/// <para>
	///		If at least 1 additional argument is provided for `OptionalQuaternionTs_`:
	///		This is a check to see if Quaternions can be sequentially multiplied with results assigned to an intermediate calculation-type Quaternion, 
	///		and said Quaternion can be converted to the output Matrix.
	/// </para>
	/// </summary>
	/// <returns>
	///		<para> 
	///			1: If no arguments are provided for `OptionalQuaternionTs_`: 
	///			True if a Quaternion with `FirstQuaternionT_` as its type argument can be converted to the specified output Matrix; otherwise false.
	///		</para>
	///		<para>
	///			2: If at least 1 additional argument is provided for `OptionalQuaternionTs_`: True if all of the following are met, otherwise false:
	///			<para>
	///				--- A: The first 2 Quaternions can be multiplied and the result output as an intermediate calculation-type Quaternion.
	///			</para>
	///			<para>
	///				--- B: If the number of `OptionalQuaternionTs_` is greater than 1, 
	///				this intermediate must also be multiply-assignable with all remaining Quaternions. 
	///				(Note: If the number of `OptionalQuaternionTs_` is greater than 1, this check is not performed).
	///			</para>
	///			<para>
	///				--- C: A Quaternion of the determined calculation type can be converted to the specified output Matrix.
	///			</para>
	///		</para>
	/// </returns>
	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, bool OutColumnMajor_, typename FirstQuaternionT_, typename...OptionalQuaternionTs_>
	[[nodiscard]] constexpr inline bool matrix_can_make_from_quaternion()
	{
		return _matrix_underlying::_matrix_can_make_from_quaternions
		<
			false,
			false,
			EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>,
			FirstQuaternionT_,
			OptionalQuaternionTs_...
		>();
	}

	/// <summary>
	/// <para> Check to see if a Matrix of the provided type can be calculated from Quaternions with the provided typeargs. </para>
	/// <para>
	///		If no arguments are provided for `OptionalQuaternionTs_`: 
	///		This is a check to see if a direct Quaternion-to-Matrix conversion can be performed. 
	/// </para>
	/// <para>
	///		If at least 1 additional argument is provided for `OptionalQuaternionTs_`:
	///		This is a check to see if Quaternions can be sequentially multiplied with results assigned to an intermediate calculation-type Quaternion, 
	///		and said Quaternion can be converted to the output Matrix.
	/// </para>
	/// <para> Where this returns false, it will also trigger static assertions. </para>
	/// </summary>
	/// <returns>
	///		<para> 
	///			1: If no arguments are provided for `OptionalQuaternionTs_`: 
	///			True if a Quaternion with `FirstQuaternionT_` as its type argument can be converted to the specified output Matrix; otherwise false.
	///		</para>
	///		<para>
	///			2: If at least 1 additional argument is provided for `OptionalQuaternionTs_`: True if all of the following are met, otherwise false:
	///			<para>
	///				--- A: The first 2 Quaternions can be multiplied and the result output as an intermediate calculation-type Quaternion.
	///			</para>
	///			<para>
	///				--- B: If the number of `OptionalQuaternionTs_` is greater than 1, 
	///				this intermediate must also be multiply-assignable with all remaining Quaternions. 
	///				(Note: If the number of `OptionalQuaternionTs_` is greater than 1, this check is not performed).
	///			</para>
	///			<para>
	///				--- C: A Quaternion of the determined calculation type can be converted to the specified output Matrix.
	///			</para>
	///		</para>
	/// </returns>
	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, bool OutColumnMajor_, typename FirstQuaternionT_, typename...OptionalQuaternionTs_>
	[[nodiscard]] constexpr inline bool matrix_assert_can_make_from_quaternion()
	{
		return _matrix_underlying::_matrix_can_make_from_quaternions
		<
			true,
			false,
			EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>,
			FirstQuaternionT_,
			OptionalQuaternionTs_...
		>();
	}
	
	/// <summary>
	/// <para>
	///		Check to see if a Matrix of the provided type can be calculated from Quaternions with the provided typeargs, 
	///		attempting to use fused operations where applicable.
	/// </para>
	/// <para>
	///		If no arguments are provided for `OptionalQuaternionTs_`: 
	///		This is a check to see if a direct Quaternion-to-Matrix conversion can be performed. 
	/// </para>
	/// <para>
	///		If at least 1 additional argument is provided for `OptionalQuaternionTs_`:
	///		This is a check to see if Quaternions can be sequentially multiplied with results assigned to an intermediate calculation-type Quaternion, 
	///		and said Quaternion can be converted to the output Matrix.
	/// </para>
	/// </summary>
	/// <returns>
	///		<para> 
	///			1: If no arguments are provided for `OptionalQuaternionTs_`: 
	///			True if a Quaternion with `FirstQuaternionT_` as its type argument can be converted to the specified output Matrix; otherwise false.
	///		</para>
	///		<para>
	///			2: If at least 1 additional argument is provided for `OptionalQuaternionTs_`: True if all of the following are met, otherwise false:
	///			<para>
	///				--- A: The first 2 Quaternions can be fused-multiplied and the result output as an intermediate calculation-type Quaternion.
	///			</para>
	///			<para>
	///				--- B: If the number of `OptionalQuaternionTs_` is greater than 1, 
	///				this intermediate must also be fused-multiply-assignable with all remaining Quaternions. 
	///				(Note: If the number of `OptionalQuaternionTs_` is greater than 1, this check is not performed).
	///			</para>
	///			<para>
	///				--- C: A Quaternion of the determined calculation type can be converted to the specified output Matrix.
	///			</para>
	///		</para>
	/// </returns>
	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, bool OutColumnMajor_, typename FirstQuaternionT_, typename...OptionalQuaternionTs_>
	[[nodiscard]] constexpr inline bool matrix_can_fused_make_from_quaternion()
	{
		return _matrix_underlying::_matrix_can_make_from_quaternions
		<
			false,
			true,
			EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>,
			FirstQuaternionT_,
			OptionalQuaternionTs_...
		>();
	}

	/// <summary>
	/// <para>
	///		Check to see if a Matrix of the provided type can be calculated from Quaternions with the provided typeargs, 
	///		attempting to use fused operations where applicable.
	/// </para>
	/// <para>
	///		If no arguments are provided for `OptionalQuaternionTs_`: 
	///		This is a check to see if a direct Quaternion-to-Matrix conversion can be performed. 
	/// </para>
	/// <para>
	///		If at least 1 additional argument is provided for `OptionalQuaternionTs_`:
	///		This is a check to see if Quaternions can be sequentially multiplied with results assigned to an intermediate calculation-type Quaternion, 
	///		and said Quaternion can be converted to the output Matrix.
	/// </para>
	/// <para> Where this returns false, it will also trigger static assertions. </para>
	/// </summary>
	/// <returns>
	///		<para> 
	///			1:  If no arguments are provided for `OptionalQuaternionTs_`: 
	///			True if a Quaternion with `FirstQuaternionT_` as its type argument can be converted to the specified output Matrix; otherwise false.
	///		</para>
	///		<para>
	///			2: If at least 1 additional argument is provided for `OptionalQuaternionTs_`: True if all of the following are met, otherwise false:
	///			<para>
	///				--- A: The first 2 Quaternions can be fused-multiplied and the result output as an intermediate calculation-type Quaternion.
	///			</para>
	///			<para>
	///				--- B: If the number of `OptionalQuaternionTs_` is greater than 1, 
	///				this intermediate must also be fused-multiply-assignable with all remaining Quaternions. 
	///				(Note: If the number of `OptionalQuaternionTs_` is greater than 1, this check is not performed).
	///			</para>
	///			<para>
	///				--- C: A Quaternion of the determined calculation type can be converted to the specified output Matrix.
	///			</para>
	///		</para>
	/// </returns>
	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, bool OutColumnMajor_, typename FirstQuaternionT_, typename...OptionalQuaternionTs_>
	[[nodiscard]] constexpr inline bool matrix_assert_can_fused_make_from_quaternion()
	{
		return _matrix_underlying::_matrix_can_make_from_quaternions
		<
			true,
			true,
			EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>,
			FirstQuaternionT_,
			OptionalQuaternionTs_...
		>();
	}
#pragma endregion

#pragma region MAKE_FROM_QUATERNIONS
	/// <summary>
	/// <para> Converts the passed Quaternion into a Matrix of the specified type, representing a 3D rotation transformation. </para>
	/// <para> The size of the output Matrix may be omitted, in which case it will default to 4x4. </para>
	/// </summary>
	/// <param name="quaternion_">EmuMath Quaternion to convert to a 3D rotation transformation Matrix.</param>
	/// <returns>3D transformation Matrix of the specified type, representing the same rotation as the passed Quaternion.</returns>
	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, bool OutColumnMajor_ = true, typename QuaternionT_>
	[[nodiscard]] constexpr inline auto matrix_make_rotation_3d(const EmuMath::Quaternion<QuaternionT_>& quaternion_)
		-> std::enable_if_t
		<
			matrix_can_make_from_quaternion<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_, QuaternionT_>(),
			EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>
		>
	{
		return _matrix_underlying::_matrix_rotate_3_from_quaternion<EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>>(quaternion_);
	}

	template<typename OutT_, bool OutColumnMajor_ = true, typename QuaternionT_>
	[[nodiscard]] constexpr inline auto matrix_make_rotation_3d(const EmuMath::Quaternion<QuaternionT_>& quaternion_)
		-> std::enable_if_t
		<
			matrix_can_make_from_quaternion<4, 4, OutT_, OutColumnMajor_, QuaternionT_>(),
			EmuMath::Matrix<4, 4, OutT_, OutColumnMajor_>
		>
	{
		return _matrix_underlying::_matrix_rotate_3_from_quaternion<EmuMath::Matrix<4, 4, OutT_, OutColumnMajor_>>(quaternion_);
	}
	
	/// <summary>
	/// <para> Combines the passed Quaternions and converts the result into a Matrix of the specified type, representing a 3D rotation transformation. </para>
	/// <para> The Quaternions will be combined in sequence from left-to-right. </para>
	/// <para> The size of the output Matrix may be omitted, in which case it will default to 4x4. </para>
	/// </summary>
	/// <param name="first_quaternion_">EmuMath Quaternion appearing first in the rotation sequence.</param>
	/// <param name="second_quaternion_">EmuMath Quaternion appearing second in the rotation sequence.</param>
	/// <returns>3D transformation Matrix of the specified type, representing the rotation resulting from sequentially combining the passed Quaternions.</returns>
	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, bool OutColumnMajor_ = true, typename FirstQuatT_, typename SecondQuatT_>
	[[nodiscard]] constexpr inline auto matrix_make_rotation_3d
	(
		const EmuMath::Quaternion<FirstQuatT_>& first_quaternion_,
		const EmuMath::Quaternion<SecondQuatT_>& second_quaternion_
	)
		-> std::enable_if_t
		<
			matrix_can_make_from_quaternion<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_, FirstQuatT_, SecondQuatT_>(),
			EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>
		>
	{
		return _matrix_underlying::_matrix_rotate_3_from_quaternion_sequence<EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>, false>
		(
			first_quaternion_,
			second_quaternion_
		);
	}

	template<typename OutT_, bool OutColumnMajor_ = true, typename FirstQuatT_, typename SecondQuatT_>
	[[nodiscard]] constexpr inline auto matrix_make_rotation_3d
	(
		const EmuMath::Quaternion<FirstQuatT_>& first_quaternion_,
		const EmuMath::Quaternion<SecondQuatT_>& second_quaternion_
	)
		-> std::enable_if_t
		<
			matrix_can_make_from_quaternion<4, 4, OutT_, OutColumnMajor_, FirstQuatT_, SecondQuatT_>(),
			EmuMath::Matrix<4, 4, OutT_, OutColumnMajor_>
		>
	{
		return _matrix_underlying::_matrix_rotate_3_from_quaternion_sequence<EmuMath::Matrix<4, 4, OutT_, OutColumnMajor_>, false>
		(
			first_quaternion_,
			second_quaternion_
		);
	}

	/// <summary>
	/// <para> Combines the passed Quaternions and converts the result into a Matrix of the specified type, representing a 3D rotation transformation. </para>
	/// <para> The Quaternions will be combined in sequence from left-to-right. </para>
	/// <para> The size of the output Matrix may be omitted, in which case it will default to 4x4. </para>
	/// </summary>
	/// <param name="first_quaternion_">EmuMath Quaternion appearing first in the rotation sequence.</param>
	/// <param name="second_quaternion_">EmuMath Quaternion appearing second in the rotation sequence.</param>
	/// <returns>3D transformation Matrix of the specified type, representing the rotation resulting from sequentially combining the passed Quaternions.</returns>
	template
	<
		std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, bool OutColumnMajor_ = true,
		typename FirstQuatT_, typename SecondQuatT_, typename...RemainingQuatTs_
	>
	[[nodiscard]] constexpr inline auto matrix_make_rotation_3d
	(
		const EmuMath::Quaternion<FirstQuatT_>& first_quaternion_,
		const EmuMath::Quaternion<SecondQuatT_>& second_quaternion_,
		const EmuMath::Quaternion<RemainingQuatTs_>&...remaining_quaternions_in_sequence_
	)
		-> std::enable_if_t
		<
			matrix_can_make_from_quaternion<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_, FirstQuatT_, SecondQuatT_, RemainingQuatTs_...>(),
			EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>
		>
	{
		return _matrix_underlying::_matrix_rotate_3_from_quaternion_sequence<EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>, false>
		(
			first_quaternion_,
			second_quaternion_,
			remaining_quaternions_in_sequence_...
		);
	}

	template<typename OutT_, bool OutColumnMajor_ = true, typename FirstQuatT_, typename SecondQuatT_, typename...RemainingQuatTs_>
	[[nodiscard]] constexpr inline auto matrix_make_rotation_3d
	(
		const EmuMath::Quaternion<FirstQuatT_>& first_quaternion_,
		const EmuMath::Quaternion<SecondQuatT_>& second_quaternion_,
		const EmuMath::Quaternion<RemainingQuatTs_>&...remaining_quaternions_in_sequence_
	)
		-> std::enable_if_t
		<
			matrix_can_make_from_quaternion<4, 4, OutT_, OutColumnMajor_, FirstQuatT_, SecondQuatT_, RemainingQuatTs_...>(),
			EmuMath::Matrix<4, 4, OutT_, OutColumnMajor_>
		>
	{
		return _matrix_underlying::_matrix_rotate_3_from_quaternion_sequence<EmuMath::Matrix<4, 4, OutT_, OutColumnMajor_>, false>
		(
			first_quaternion_,
			second_quaternion_,
			remaining_quaternions_in_sequence_...
		);
	}
#pragma endregion

#pragma region FUSED_MAKE_FROM_QUATERNIONS
	/// <summary>
	/// <para> Converts the passed Quaternion into a Matrix of the specified type, representing a 3D rotation transformation. </para>
	/// <para> The size of the output Matrix may be omitted, in which case it will default to 4x4. </para>
	/// <para>
	///		This function will attempt to take advantage of fused instructions (such as FMADD) if possible, or emulate them otherwise. 
	///		Use of such instructions may improve accuracy and/or performance.
	/// </para>
	/// </summary>
	/// <param name="quaternion_">EmuMath Quaternion to convert to a 3D rotation transformation Matrix.</param>
	/// <returns>3D transformation Matrix of the specified type, representing the same rotation as the passed Quaternion.</returns>
	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, bool OutColumnMajor_ = true, typename QuaternionT_>
	[[nodiscard]] constexpr inline auto matrix_make_rotation_3d_fused(const EmuMath::Quaternion<QuaternionT_>& quaternion_)
		-> std::enable_if_t
		<
			matrix_can_fused_make_from_quaternion<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_, QuaternionT_>(),
			EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>
		>
	{
		return _matrix_underlying::_matrix_rotate_3_from_quaternion<EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>>(quaternion_);
	}

	template<typename OutT_, bool OutColumnMajor_ = true, typename QuaternionT_>
	[[nodiscard]] constexpr inline auto matrix_make_rotation_3d_fused(const EmuMath::Quaternion<QuaternionT_>& quaternion_)
		-> std::enable_if_t
		<
			matrix_can_fused_make_from_quaternion<4, 4, OutT_, OutColumnMajor_, QuaternionT_>(),
			EmuMath::Matrix<4, 4, OutT_, OutColumnMajor_>
		>
	{
		return _matrix_underlying::_matrix_rotate_3_from_quaternion<EmuMath::Matrix<4, 4, OutT_, OutColumnMajor_>>(quaternion_);
	}
	
	/// <summary>
	/// <para> Combines the passed Quaternions and converts the result into a Matrix of the specified type, representing a 3D rotation transformation. </para>
	/// <para> The Quaternions will be combined in sequence from left-to-right. </para>
	/// <para> The size of the output Matrix may be omitted, in which case it will default to 4x4. </para>
	/// <para>
	///		This function will attempt to take advantage of fused instructions (such as FMADD) if possible, or emulate them otherwise. 
	///		Use of such instructions may improve accuracy and/or performance.
	/// </para>
	/// </summary>
	/// <param name="first_quaternion_">EmuMath Quaternion appearing first in the rotation sequence.</param>
	/// <param name="second_quaternion_">EmuMath Quaternion appearing second in the rotation sequence.</param>
	/// <returns>3D transformation Matrix of the specified type, representing the rotation resulting from sequentially combining the passed Quaternions.</returns>
	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, bool OutColumnMajor_ = true, typename FirstQuatT_, typename SecondQuatT_>
	[[nodiscard]] constexpr inline auto matrix_make_rotation_3d_fused
	(
		const EmuMath::Quaternion<FirstQuatT_>& first_quaternion_,
		const EmuMath::Quaternion<SecondQuatT_>& second_quaternion_
	)
		-> std::enable_if_t
		<
			matrix_can_fused_make_from_quaternion<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_, FirstQuatT_, SecondQuatT_>(),
			EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>
		>
	{
		return _matrix_underlying::_matrix_rotate_3_from_quaternion_sequence<EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>, true>
		(
			first_quaternion_,
			second_quaternion_
		);
	}

	template<typename OutT_, bool OutColumnMajor_ = true, typename FirstQuatT_, typename SecondQuatT_>
	[[nodiscard]] constexpr inline auto matrix_make_rotation_3d_fused
	(
		const EmuMath::Quaternion<FirstQuatT_>& first_quaternion_,
		const EmuMath::Quaternion<SecondQuatT_>& second_quaternion_
	)
		-> std::enable_if_t
		<
			matrix_can_fused_make_from_quaternion<4, 4, OutT_, OutColumnMajor_, FirstQuatT_, SecondQuatT_>(),
			EmuMath::Matrix<4, 4, OutT_, OutColumnMajor_>
		>
	{
		return _matrix_underlying::_matrix_rotate_3_from_quaternion_sequence<EmuMath::Matrix<4, 4, OutT_, OutColumnMajor_>, true>
		(
			first_quaternion_,
			second_quaternion_
		);
	}

	/// <summary>
	/// <para> Combines the passed Quaternions and converts the result into a Matrix of the specified type, representing a 3D rotation transformation. </para>
	/// <para> The Quaternions will be combined in sequence from left-to-right. </para>
	/// <para> The size of the output Matrix may be omitted, in which case it will default to 4x4. </para>
	/// <para>
	///		This function will attempt to take advantage of fused instructions (such as FMADD) if possible, or emulate them otherwise. 
	///		Use of such instructions may improve accuracy and/or performance.
	/// </para>
	/// </summary>
	/// <param name="first_quaternion_">EmuMath Quaternion appearing first in the rotation sequence.</param>
	/// <param name="second_quaternion_">EmuMath Quaternion appearing second in the rotation sequence.</param>
	/// <returns>3D transformation Matrix of the specified type, representing the rotation resulting from sequentially combining the passed Quaternions.</returns>
	template
	<
		std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, bool OutColumnMajor_ = true,
		typename FirstQuatT_, typename SecondQuatT_, typename...RemainingQuatTs_
	>
	[[nodiscard]] constexpr inline auto matrix_make_rotation_3d_fused
	(
		const EmuMath::Quaternion<FirstQuatT_>& first_quaternion_,
		const EmuMath::Quaternion<SecondQuatT_>& second_quaternion_,
		const EmuMath::Quaternion<RemainingQuatTs_>&...remaining_quaternions_in_sequence_
	)
		-> std::enable_if_t
		<
			matrix_can_fused_make_from_quaternion<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_, FirstQuatT_, SecondQuatT_, RemainingQuatTs_...>(),
			EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>
		>
	{
		return _matrix_underlying::_matrix_rotate_3_from_quaternion_sequence<EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>, true>
		(
			first_quaternion_,
			second_quaternion_,
			remaining_quaternions_in_sequence_...
		);
	}

	template<typename OutT_, bool OutColumnMajor_ = true, typename FirstQuatT_, typename SecondQuatT_, typename...RemainingQuatTs_>
	[[nodiscard]] constexpr inline auto matrix_make_rotation_3d_fused
	(
		const EmuMath::Quaternion<FirstQuatT_>& first_quaternion_,
		const EmuMath::Quaternion<SecondQuatT_>& second_quaternion_,
		const EmuMath::Quaternion<RemainingQuatTs_>&...remaining_quaternions_in_sequence_
	)
		-> std::enable_if_t
		<
			matrix_can_fused_make_from_quaternion<4, 4, OutT_, OutColumnMajor_, FirstQuatT_, SecondQuatT_, RemainingQuatTs_...>(),
			EmuMath::Matrix<4, 4, OutT_, OutColumnMajor_>
		>
	{
		return _matrix_underlying::_matrix_rotate_3_from_quaternion_sequence<EmuMath::Matrix<4, 4, OutT_, OutColumnMajor_>, true>
		(
			first_quaternion_,
			second_quaternion_,
			remaining_quaternions_in_sequence_...
		);
	}
#pragma endregion
}

#endif
