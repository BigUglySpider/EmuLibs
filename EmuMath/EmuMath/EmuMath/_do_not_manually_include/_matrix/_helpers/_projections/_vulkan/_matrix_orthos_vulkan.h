#ifndef EMU_MATH_MATRIX_PROJECTIONS_ORTHO_VK_H_INC_
#define EMU_MATH_MATRIX_PROJECTIONS_ORTHO_VK_H_INC_ 1

#include "../../_common_matrix_helper_includes.h"

namespace EmuMath::Helpers
{
	/// <summary>
	/// <para> Creates an orthographic projection Matrix designed for use with Vulkan. </para>
	/// <para> The size of the output Matrix may be omitted, in which case it will default to 4x4. </para>
	/// </summary>
	/// <param name="left_">Scalar left edge of the view perimiter.</param>
	/// <param name="top_">Scalar top edge of the view perimiter.</param>
	/// <param name="right_">Scalar right edge of the view perimiter.</param>
	/// <param name="bottom_">Scalar bottom edge of the view perimiter</param>
	/// <param name="near_">Scalar boundary of the near clipping plane.</param>
	/// <param name="far_">Scalar boundary of the far clapping plane.</param>
	/// <returns>Orthographic Projection Matrix of the specified type intended for use with Vulkan.</returns>
	template
	<
		std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, bool OutColumnMajor_ = true,
		typename Left_, typename Top_, typename Right_, typename Bottom_, typename Near_, typename Far_
	>
	[[nodiscard]] constexpr inline auto matrix_ortho_vk(Left_&& left_, Top_&& top_, Right_&& right_, Bottom_&& bottom_, Near_&& near_, Far_&& far_)
		-> EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>
	{
		return _matrix_underlying::_make_ortho_vk<EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>>
		(
			std::forward<Left_>(left_),
			std::forward<Top_>(top_),
			std::forward<Right_>(right_),
			std::forward<Bottom_>(bottom_),
			std::forward<Near_>(near_),
			std::forward<Far_>(far_)
		);
	}

	template<typename OutT_, bool OutColumnMajor_ = true, typename Left_, typename Top_, typename Right_, typename Bottom_, typename Near_, typename Far_>
	[[nodiscard]] constexpr inline auto matrix_ortho_vk(Left_&& left_, Top_&& top_, Right_&& right_, Bottom_&& bottom_, Near_&& near_, Far_&& far_)
		-> EmuMath::Matrix<4, 4, OutT_, OutColumnMajor_>
	{
		return _matrix_underlying::_make_ortho_vk<EmuMath::Matrix<4, 4, OutT_, OutColumnMajor_>>
		(
			std::forward<Left_>(left_),
			std::forward<Top_>(top_),
			std::forward<Right_>(right_),
			std::forward<Bottom_>(bottom_),
			std::forward<Near_>(near_),
			std::forward<Far_>(far_)
		);
	}

	/// <summary>
	/// <para> Creates an orthographic projection Matrix designed for use with Vulkan. </para>
	/// <para> The size of the output Matrix may be omitted, in which case it will default to 4x4. </para>
	/// </summary>
	/// <param name="view_rect_">EmuMath Rect providing the Left, Top, Right, and Bottom edges of the view perimiter.</param>
	/// <param name="near_">Scalar boundary of the near clipping plane.</param>
	/// <param name="far_">Scalar boundary of the far clapping plane.</param>
	/// <returns>Orthographic Projection Matrix of the specified type intended for use with Vulkan.</returns>
	template
	<
		std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, bool OutColumnMajor_ = true,
		EmuMath::TMP::EmuRect ViewRect_, typename Near_, typename Far_
	>
	[[nodiscard]] constexpr inline auto matrix_ortho_vk(ViewRect_&& view_rect_, Near_&& near_, Far_&& far_)
		-> EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>
	{
		return _matrix_underlying::_make_ortho_vk<EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_>>
		(
			std::forward<ViewRect_>(view_rect_),
			std::forward<Near_>(near_),
			std::forward<Far_>(far_)
		);
	}

	template<typename OutT_, bool OutColumnMajor_ = true, EmuMath::TMP::EmuRect ViewRect_, typename Near_, typename Far_>
	[[nodiscard]] constexpr inline auto matrix_ortho_vk(ViewRect_&& view_rect_, Near_&& near_, Far_&& far_)
		-> EmuMath::Matrix<4, 4, OutT_, OutColumnMajor_>
	{
		return _matrix_underlying::_make_ortho_vk<EmuMath::Matrix<4, 4, OutT_, OutColumnMajor_>>
		(
			std::forward<ViewRect_>(view_rect_),
			std::forward<Near_>(near_),
			std::forward<Far_>(far_)
		);
	}
}

#endif
