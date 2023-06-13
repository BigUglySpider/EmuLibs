#ifndef EMU_MATH_MATRIX_PROJECTIONS_PERSPECTIVE_VK_H_INC_
#define EMU_MATH_MATRIX_PROJECTIONS_PERSPECTIVE_VK_H_INC_ 1

#include "../../_common_matrix_helper_includes.h"

namespace EmuMath::Helpers
{
#pragma region SIMPLE
	/// <summary>
	/// <para> Creates a perspective Matrix designed for use with Vulkan. </para>
	/// <para> The size of the output Matrix may be omitted, in which case it will default to 4x4. </para>
	/// <para> 
	///		Input FOV angles may be interpreted as either radians or degrees, based on `FovIsRads_`, where `true` = radians, `false` = degrees. 
	///		This may be omitted, in which case it defaults to `true`. 
	/// </para>
	/// </summary>
	/// <param name="fov_y_">Scalar Y-axis FOV angle for the projection view.</param>
	/// <param name="aspect_ratio_">Scalar aspect ratio of the projection view target.</param>
	/// <param name="near_">Scalar boundary of the near clipping plane.</param>
	/// <param name="far_">Scalar boundary of the far clapping plane.</param>
	/// <returns>EmuMath Matrix of the specified type containing a perspective projection Matrix for Vulkan.</returns>
	template
	<
		bool FovIsRads_, std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, bool OutColumnMajor_ = true,
		typename FovY_, typename AspectRatio_, typename Near_, typename Far_
	>
	[[nodiscard]] constexpr inline auto matrix_perspective_vk(FovY_&& fov_y_, AspectRatio_&& aspect_ratio_, Near_&& near_, Far_&& far_)
		-> EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>
	{
		return _matrix_underlying::_make_perspective_matrix_vk
		<
			EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>,
			FovIsRads_,
			false
		>(std::forward<FovY_>(fov_y_), std::forward<AspectRatio_>(aspect_ratio_), std::forward<Near_>(near_), std::forward<Far_>(far_));
	}

	template
	<
		std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, bool OutColumnMajor_ = true,
		typename FovY_, typename AspectRatio_, typename Near_, typename Far_
	>
	[[nodiscard]] constexpr inline auto matrix_perspective_vk(FovY_&& fov_y_, AspectRatio_&& aspect_ratio_, Near_&& near_, Far_&& far_)
		-> EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>
	{
		return _matrix_underlying::_make_perspective_matrix_vk
		<
			EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>,
			true,
			false
		>(std::forward<FovY_>(fov_y_), std::forward<AspectRatio_>(aspect_ratio_), std::forward<Near_>(near_), std::forward<Far_>(far_));
	}
		
	template<bool FovIsRads_, typename OutT_, bool OutColumnMajor_ = true, typename FovY_, typename AspectRatio_, typename Near_, typename Far_>
	[[nodiscard]] constexpr inline auto matrix_perspective_vk(FovY_&& fov_y_, AspectRatio_&& aspect_ratio_, Near_&& near_, Far_&& far_)
		-> EmuMath::Matrix<4, 4, OutT_, OutColumnMajor_>
	{
		return _matrix_underlying::_make_perspective_matrix_vk
		<
			EmuMath::Matrix<4, 4, OutT_, OutColumnMajor_>,
			FovIsRads_,
			false
		>(std::forward<FovY_>(fov_y_), std::forward<AspectRatio_>(aspect_ratio_), std::forward<Near_>(near_), std::forward<Far_>(far_));
	}

	template<typename OutT_, bool OutColumnMajor_ = true, typename FovY_, typename AspectRatio_, typename Near_, typename Far_>
	[[nodiscard]] constexpr inline auto matrix_perspective_vk(FovY_&& fov_y_, AspectRatio_&& aspect_ratio_, Near_&& near_, Far_&& far_)
		-> EmuMath::Matrix<4, 4, OutT_, OutColumnMajor_>
	{
		return _matrix_underlying::_make_perspective_matrix_vk
		<
			EmuMath::Matrix<4, 4, OutT_, OutColumnMajor_>,
			true,
			false
		>(std::forward<FovY_>(fov_y_), std::forward<AspectRatio_>(aspect_ratio_), std::forward<Near_>(near_), std::forward<Far_>(far_));
	}
#pragma endregion

#pragma region SIMPLE_CONSTEXPR
	/// <summary>
	/// <para> Creates a perspective Matrix designed for use with Vulkan. </para>
	/// <para> The size of the output Matrix may be omitted, in which case it will default to 4x4. </para>
	/// <para> 
	///		Input FOV angles may be interpreted as either radians or degrees, based on `FovIsRads_`, where `true` = radians, `false` = degrees. 
	///		This may be omitted, in which case it defaults to `true`. 
	/// </para>
	/// <para> Calculation will aim to be constexpr-evaluable if possible, which may affect accuracy and/or performance. </para>
	/// </summary>
	/// <param name="fov_y_">Scalar Y-axis FOV angle for the projection view.</param>
	/// <param name="aspect_ratio_">Scalar aspect ratio of the projection view target.</param>
	/// <param name="near_">Scalar boundary of the near clipping plane.</param>
	/// <param name="far_">Scalar boundary of the far clapping plane.</param>
	/// <returns>EmuMath Matrix of the specified type containing a perspective projection Matrix for Vulkan.</returns>
	template
	<
		bool FovIsRads_, std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, bool OutColumnMajor_ = true,
		typename FovY_, typename AspectRatio_, typename Near_, typename Far_
	>
	[[nodiscard]] constexpr inline auto matrix_perspective_vk_constexpr(FovY_&& fov_y_, AspectRatio_&& aspect_ratio_, Near_&& near_, Far_&& far_)
		-> EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>
	{
		return _matrix_underlying::_make_perspective_matrix_vk
		<
			EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>,
			FovIsRads_,
			true
		>(std::forward<FovY_>(fov_y_), std::forward<AspectRatio_>(aspect_ratio_), std::forward<Near_>(near_), std::forward<Far_>(far_));
	}

	template
	<
		std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, bool OutColumnMajor_ = true,
		typename FovY_, typename AspectRatio_, typename Near_, typename Far_
	>
	[[nodiscard]] constexpr inline auto matrix_perspective_vk_constexpr(FovY_&& fov_y_, AspectRatio_&& aspect_ratio_, Near_&& near_, Far_&& far_)
		-> EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>
	{
		return _matrix_underlying::_make_perspective_matrix_vk
		<
			EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>,
			true,
			true
		>(std::forward<FovY_>(fov_y_), std::forward<AspectRatio_>(aspect_ratio_), std::forward<Near_>(near_), std::forward<Far_>(far_));
	}
		
	template<bool FovIsRads_, typename OutT_, bool OutColumnMajor_ = true, typename FovY_, typename AspectRatio_, typename Near_, typename Far_>
	[[nodiscard]] constexpr inline auto matrix_perspective_vk_constexpr(FovY_&& fov_y_, AspectRatio_&& aspect_ratio_, Near_&& near_, Far_&& far_)
		-> EmuMath::Matrix<4, 4, OutT_, OutColumnMajor_>
	{
		return _matrix_underlying::_make_perspective_matrix_vk
		<
			EmuMath::Matrix<4, 4, OutT_, OutColumnMajor_>,
			FovIsRads_,
			true
		>(std::forward<FovY_>(fov_y_), std::forward<AspectRatio_>(aspect_ratio_), std::forward<Near_>(near_), std::forward<Far_>(far_));
	}

	template<typename OutT_, bool OutColumnMajor_ = true, typename FovY_, typename AspectRatio_, typename Near_, typename Far_>
	[[nodiscard]] constexpr inline auto matrix_perspective_vk_constexpr(FovY_&& fov_y_, AspectRatio_&& aspect_ratio_, Near_&& near_, Far_&& far_)
		-> EmuMath::Matrix<4, 4, OutT_, OutColumnMajor_>
	{
		return _matrix_underlying::_make_perspective_matrix_vk
		<
			EmuMath::Matrix<4, 4, OutT_, OutColumnMajor_>,
			true,
			true
		>(std::forward<FovY_>(fov_y_), std::forward<AspectRatio_>(aspect_ratio_), std::forward<Near_>(near_), std::forward<Far_>(far_));
	}
#pragma endregion


#pragma region REVERSE_DEPTH
	/// <summary>
	/// <para> Creates a perspective Matrix designed for use with Vulkan and a reverse Z-buffer. </para>
	/// <para> The size of the output Matrix may be omitted, in which case it will default to 4x4. </para>
	/// <para> 
	///		Input FOV angles may be interpreted as either radians or degrees, based on `FovIsRads_`, where `true` = radians, `false` = degrees. 
	///		This may be omitted, in which case it defaults to `true`. 
	/// </para>
	/// </summary>
	/// <param name="fov_y_">Scalar Y-axis FOV angle for the projection view.</param>
	/// <param name="aspect_ratio_">Scalar aspect ratio of the projection view target.</param>
	/// <param name="near_">Scalar boundary of the near clipping plane.</param>
	/// <param name="far_">Scalar boundary of the far clapping plane.</param>
	/// <returns>EmuMath Matrix of the specified type containing a perspective projection Matrix for Vulkan with a reverse Z-buffer.</returns>
	template
	<
		bool FovIsRads_, std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, bool OutColumnMajor_ = true,
		typename FovY_, typename AspectRatio_, typename Near_, typename Far_
	>
	[[nodiscard]] constexpr inline auto matrix_perspective_vk_reverse_depth(FovY_&& fov_y_, AspectRatio_&& aspect_ratio_, Near_&& near_, Far_&& far_)
		-> EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>
	{
		return _matrix_underlying::_make_perspective_matrix_vk_reverse_depth
		<
			EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>,
			FovIsRads_,
			false
		>(std::forward<FovY_>(fov_y_), std::forward<AspectRatio_>(aspect_ratio_), std::forward<Near_>(near_), std::forward<Far_>(far_));
	}

	template
	<
		std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, bool OutColumnMajor_ = true,
		typename FovY_, typename AspectRatio_, typename Near_, typename Far_
	>
	[[nodiscard]] constexpr inline auto matrix_perspective_vk_reverse_depth(FovY_&& fov_y_, AspectRatio_&& aspect_ratio_, Near_&& near_, Far_&& far_)
		-> EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>
	{
		return _matrix_underlying::_make_perspective_matrix_vk_reverse_depth
		<
			EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>,
			true,
			false
		>(std::forward<FovY_>(fov_y_), std::forward<AspectRatio_>(aspect_ratio_), std::forward<Near_>(near_), std::forward<Far_>(far_));
	}
		
	template<bool FovIsRads_, typename OutT_, bool OutColumnMajor_ = true, typename FovY_, typename AspectRatio_, typename Near_, typename Far_>
	[[nodiscard]] constexpr inline auto matrix_perspective_vk_reverse_depth(FovY_&& fov_y_, AspectRatio_&& aspect_ratio_, Near_&& near_, Far_&& far_)
		-> EmuMath::Matrix<4, 4, OutT_, OutColumnMajor_>
	{
		return _matrix_underlying::_make_perspective_matrix_vk_reverse_depth
		<
			EmuMath::Matrix<4, 4, OutT_, OutColumnMajor_>,
			FovIsRads_,
			false
		>(std::forward<FovY_>(fov_y_), std::forward<AspectRatio_>(aspect_ratio_), std::forward<Near_>(near_), std::forward<Far_>(far_));
	}

	template<typename OutT_, bool OutColumnMajor_ = true, typename FovY_, typename AspectRatio_, typename Near_, typename Far_>
	[[nodiscard]] constexpr inline auto matrix_perspective_vk_reverse_depth(FovY_&& fov_y_, AspectRatio_&& aspect_ratio_, Near_&& near_, Far_&& far_)
		-> EmuMath::Matrix<4, 4, OutT_, OutColumnMajor_>
	{
		return _matrix_underlying::_make_perspective_matrix_vk_reverse_depth
		<
			EmuMath::Matrix<4, 4, OutT_, OutColumnMajor_>,
			true,
			false
		>(std::forward<FovY_>(fov_y_), std::forward<AspectRatio_>(aspect_ratio_), std::forward<Near_>(near_), std::forward<Far_>(far_));
	}
#pragma endregion

#pragma region REVERSE_DEPTH_CONSTEXPR
	/// <summary>
	/// <para> Creates a perspective Matrix designed for use with Vulkan and a reverse Z-buffer. </para>
	/// <para> The size of the output Matrix may be omitted, in which case it will default to 4x4. </para>
	/// <para> 
	///		Input FOV angles may be interpreted as either radians or degrees, based on `FovIsRads_`, where `true` = radians, `false` = degrees. 
	///		This may be omitted, in which case it defaults to `true`. 
	/// </para>
	/// <para> Calculation will aim to be constexpr-evaluable if possible, which may affect accuracy and/or performance. </para>
	/// </summary>
	/// <param name="fov_y_">Scalar Y-axis FOV angle for the projection view.</param>
	/// <param name="aspect_ratio_">Scalar aspect ratio of the projection view target.</param>
	/// <param name="near_">Scalar boundary of the near clipping plane.</param>
	/// <param name="far_">Scalar boundary of the far clapping plane.</param>
	/// <returns>EmuMath Matrix of the specified type containing a perspective projection Matrix for Vulkan with a reverse Z-buffer.</returns>
	template
	<
		bool FovIsRads_, std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, bool OutColumnMajor_ = true,
		typename FovY_, typename AspectRatio_, typename Near_, typename Far_
	>
	[[nodiscard]] constexpr inline auto matrix_perspective_vk_reverse_depth_constexpr(FovY_&& fov_y_, AspectRatio_&& aspect_ratio_, Near_&& near_, Far_&& far_)
		-> EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>
	{
		return _matrix_underlying::_make_perspective_matrix_vk_reverse_depth
		<
			EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>,
			FovIsRads_,
			true
		>(std::forward<FovY_>(fov_y_), std::forward<AspectRatio_>(aspect_ratio_), std::forward<Near_>(near_), std::forward<Far_>(far_));
	}

	template
	<
		std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, bool OutColumnMajor_ = true,
		typename FovY_, typename AspectRatio_, typename Near_, typename Far_
	>
	[[nodiscard]] constexpr inline auto matrix_perspective_vk_reverse_depth_constexpr(FovY_&& fov_y_, AspectRatio_&& aspect_ratio_, Near_&& near_, Far_&& far_)
		-> EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>
	{
		return _matrix_underlying::_make_perspective_matrix_vk_reverse_depth
		<
			EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>,
			true,
			true
		>(std::forward<FovY_>(fov_y_), std::forward<AspectRatio_>(aspect_ratio_), std::forward<Near_>(near_), std::forward<Far_>(far_));
	}
		
	template<bool FovIsRads_, typename OutT_, bool OutColumnMajor_ = true, typename FovY_, typename AspectRatio_, typename Near_, typename Far_>
	[[nodiscard]] constexpr inline auto matrix_perspective_vk_reverse_depth_constexpr(FovY_&& fov_y_, AspectRatio_&& aspect_ratio_, Near_&& near_, Far_&& far_)
		-> EmuMath::Matrix<4, 4, OutT_, OutColumnMajor_>
	{
		return _matrix_underlying::_make_perspective_matrix_vk_reverse_depth
		<
			EmuMath::Matrix<4, 4, OutT_, OutColumnMajor_>,
			FovIsRads_,
			true
		>(std::forward<FovY_>(fov_y_), std::forward<AspectRatio_>(aspect_ratio_), std::forward<Near_>(near_), std::forward<Far_>(far_));
	}

	template<typename OutT_, bool OutColumnMajor_ = true, typename FovY_, typename AspectRatio_, typename Near_, typename Far_>
	[[nodiscard]] constexpr inline auto matrix_perspective_vk_reverse_depth_constexpr(FovY_&& fov_y_, AspectRatio_&& aspect_ratio_, Near_&& near_, Far_&& far_)
		-> EmuMath::Matrix<4, 4, OutT_, OutColumnMajor_>
	{
		return _matrix_underlying::_make_perspective_matrix_vk_reverse_depth
		<
			EmuMath::Matrix<4, 4, OutT_, OutColumnMajor_>,
			true,
			true
		>(std::forward<FovY_>(fov_y_), std::forward<AspectRatio_>(aspect_ratio_), std::forward<Near_>(near_), std::forward<Far_>(far_));
	}
#pragma endregion
}

#endif
