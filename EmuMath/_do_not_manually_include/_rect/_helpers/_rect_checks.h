#ifndef EMU_MATH_RECT_CHECKS_H_INC_
#define EMU_MATH_RECT_CHECKS_H_INC_ 1

#include "_common_rect_helper_includes.h"
#include "_rect_get.h"

namespace EmuMath::Helpers
{
	/// <summary>
	/// <para> Checks if the current state of the passed Rect has a well-formed X axis. </para>
	/// <para> A well-formed X-axis will have a Left value less than or equal to its Right value. </para>
	/// </summary>
	/// <returns>True if the passed Rect's X-axis is well-formed; otherwise false.</returns>
	template<EmuConcepts::EmuRect Rect_>
	[[nodiscard]] constexpr inline bool rect_has_well_formed_x(Rect_&& rect_)
	{
		using get_left_result = decltype(rect_get_left(std::forward<Rect_>(rect_)));
		using get_right_result = decltype(rect_get_right(std::forward<Rect_>(rect_)));
		using get_left_uq = typename EmuCore::TMP::remove_ref_cv<get_left_result>::type;
		using get_right_uq = typename EmuCore::TMP::remove_ref_cv<get_right_result>::type;
		using cmp = EmuCore::do_cmp_less_equal<get_left_uq, get_right_uq>;

EMU_CORE_MSVC_PUSH_WARNING_STACK
EMU_CORE_MSVC_DISABLE_WARNING(EMU_CORE_WARNING_BAD_MOVE)
		return cmp()
		(
			std::forward<get_left_result>(rect_get_left(std::forward<Rect_>(rect_))),
			std::forward<get_right_result>(rect_get_right(std::forward<Rect_>(rect_)))
		);
EMU_CORE_MSVC_POP_WARNING_STACK
	}

	/// <summary>
	/// <para> Checks if the current state of the passed Rect has a well-formed Y axis. </para>
	/// <para> A well-formed Y-axis will have a Top value less than or equal to its Bottom value. </para>
	/// </summary>
	/// <returns>True if the passed Rect's Y-axis is well-formed; otherwise false.</returns>
	template<EmuConcepts::EmuRect Rect_>
	[[nodiscard]] constexpr inline bool rect_has_well_formed_y(Rect_&& rect_)
	{
		using get_top_result = decltype(rect_get_top(std::forward<Rect_>(rect_)));
		using get_bottom_result = decltype(rect_get_bottom(std::forward<Rect_>(rect_)));
		using get_left_uq = typename EmuCore::TMP::remove_ref_cv<get_top_result>::type;
		using get_right_uq = typename EmuCore::TMP::remove_ref_cv<get_bottom_result>::type;
		using cmp = EmuCore::do_cmp_less_equal<get_left_uq, get_right_uq>;

EMU_CORE_MSVC_PUSH_WARNING_STACK
EMU_CORE_MSVC_DISABLE_WARNING(EMU_CORE_WARNING_BAD_MOVE)
		return cmp()
		(
			std::forward<get_top_result>(rect_get_top(std::forward<Rect_>(rect_))),
			std::forward<get_bottom_result>(rect_get_bottom(std::forward<Rect_>(rect_)))
		);
EMU_CORE_MSVC_POP_WARNING_STACK
	}

	/// <summary>
	/// <para> Checks if the current state of the passed Rect is well-formed.</para>
	/// <para> A well-formed Rect will have a Left value less than or equal to its Right value, and a Top value less than or equal to its Bottom value. </para>
	/// </summary>
	/// <returns>True if the passed Rect's X- and Y-axes are both well-formed; otherwise false.</returns>
	template<EmuConcepts::EmuRect Rect_>
	[[nodiscard]] constexpr inline bool rect_is_well_formed(Rect_&& rect_)
	{
		return rect_has_well_formed_x(std::forward<Rect_>(rect_)) && rect_has_well_formed_y(std::forward<Rect_>(rect_));
	}

	/// <summary>
	/// <para> Determines if a given point is contained within the passed Rect based on its current Left, Top, Right, and Bottom boundaries </para>
	/// <para> This assumes that the Rect is well-formed. </para>
	/// <para> May customise whether the point is classed as outside if on the boundaries of the Rect via IgnoreEqual_. If omitted, this defaults to `true`. </para>
	/// </summary>
	/// <param name="x_">X coordinate to check for.</param>
	/// <param name="y_">Y coordinate to check for.</param>
	/// <returns>True if the provided X and Y coordinates are contained within the passed Rect's boundaries.</returns>
	template<bool IgnoreEqual_ = true, typename X_, typename Y_, EmuConcepts::EmuRect Rect_>
	[[nodiscard]] constexpr inline bool rect_contains_point(Rect_&& rect_, X_&& x_, Y_&& y_)
	{
		using rect_uq = typename EmuCore::TMP::remove_ref_cv<Rect_>::type;
		using get_left_result = decltype(rect_get_left(std::forward<Rect_>(rect_)));
		using get_left_uq = typename EmuCore::TMP::remove_ref_cv<get_left_result>::type;
		using get_top_result = decltype(rect_get_top(std::forward<Rect_>(rect_)));
		using get_top_uq = typename EmuCore::TMP::remove_ref_cv<get_top_result>::type;
		using get_right_result = decltype(rect_get_right(std::forward<Rect_>(rect_)));
		using get_right_uq = typename EmuCore::TMP::remove_ref_cv<get_right_result>::type;
		using get_bottom_result = decltype(rect_get_bottom(std::forward<Rect_>(rect_)));
		using get_bottom_uq = typename EmuCore::TMP::remove_ref_cv<get_bottom_result>::type;

		using x_type = typename std::conditional<std::is_lvalue_reference_v<X_>, X_, typename rect_uq::preferred_floating_point>::type;
		using y_type = typename std::conditional<std::is_lvalue_reference_v<Y_>, Y_, typename rect_uq::preferred_floating_point>::type;
		using x_uq = typename EmuCore::TMP::remove_ref_cv<x_type>::type;
		using y_uq = typename EmuCore::TMP::remove_ref_cv<y_type>::type;
		x_type x = static_cast<x_type>(std::forward<X_>(x_));
		y_type y = static_cast<y_type>(std::forward<Y_>(y_));

		using cmp_less = typename std::conditional<IgnoreEqual_, EmuCore::do_cmp_less<void, void>, EmuCore::do_cmp_less_equal<void, void>>::type;
		using cmp_greater = typename std::conditional<IgnoreEqual_, EmuCore::do_cmp_greater<void, void>, EmuCore::do_cmp_greater_equal<void, void>>::type;

EMU_CORE_MSVC_PUSH_WARNING_STACK
EMU_CORE_MSVC_DISABLE_WARNING(EMU_CORE_WARNING_BAD_MOVE)
		return
		(
			cmp_less()(rect_get_left(std::forward<Rect_>(rect_)), x) &&
			cmp_less()(rect_get_top(std::forward<Rect_>(rect_)), y) &&
			cmp_greater()(rect_get_right(std::forward<Rect_>(rect_)), x) &&
			cmp_greater()(rect_get_bottom(std::forward<Rect_>(rect_)), y)
		);
EMU_CORE_MSVC_POP_WARNING_STACK
	}


	/// <summary>
	/// <para> Determines if a given point is contained within the passed Rect based on its current Left, Top, Right, and Bottom boundaries </para>
	/// <para> This assumes that the Rect is well-formed. </para>
	/// <para> May customise whether the point is classed as outside if on the boundaries of the Rect via IgnoreEqual_. If omitted, this defaults to `true`. </para>
	/// </summary>
	/// <param name="point_vec_2d_">EmuMath Vector with coordinates to search for in the X- and Y-axes in theoretical indices 0 and 1 respectively..</param>
	/// <returns>True if the provided coordinates are contained within the passed Rect's boundaries.</returns>
	template<bool IgnoreEqual_ = true, EmuConcepts::EmuVector PointVector_, EmuConcepts::EmuRect Rect_>
	[[nodiscard]] constexpr inline bool rect_contains_point(Rect_&& rect_, PointVector_&& point_vector_2d_)
	{
EMU_CORE_MSVC_PUSH_WARNING_STACK
EMU_CORE_MSVC_DISABLE_WARNING(EMU_CORE_WARNING_BAD_MOVE)
		return rect_contains_point<IgnoreEqual_>
		(
			std::forward<Rect_>(rect_),
			std::forward<PointVector_>(point_vector_2d_).template AtTheoretical<0>(),
			std::forward<PointVector_>(point_vector_2d_).template AtTheoretical<1>()
		);
EMU_CORE_MSVC_POP_WARNING_STACK
	}

	/// <summary>
	/// <para> Checks if the two passed Rects are colliding in an axis-aligned context (i.e. they are considered not rotated or warped in any way). </para>
	/// <para> This assumes that both Rects are well-formed. </para>
	/// <para> May customise whether a point is classed as outside if on the boundaries of a Rect via IgnoreEqual_. If omitted, this defaults to `true`. </para>
	/// </summary>
	/// <param name="rect_a_">First Rect involved in the collision check.</param>
	/// <param name="rect_b_">Second Rect involved in the collision check.</param>
	/// <returns>If the two passed Rects are colliding, `true`; otherwise `false`.</returns>
	template<bool IgnoreEqual_ = true, EmuConcepts::EmuRect RectA_, EmuConcepts::EmuRect RectB_>
	[[nodiscard]] constexpr inline bool rect_colliding_axis_aligned(RectA_&& rect_a_, RectB_&& rect_b_)
	{
		using cmp_less = typename std::conditional<IgnoreEqual_, EmuCore::do_cmp_less<void, void>, EmuCore::do_cmp_less_equal<void, void>>::type;
		using cmp_greater = typename std::conditional<IgnoreEqual_, EmuCore::do_cmp_greater<void, void>, EmuCore::do_cmp_greater_equal<void, void>>::type;

EMU_CORE_MSVC_PUSH_WARNING_STACK
EMU_CORE_MSVC_DISABLE_WARNING(EMU_CORE_WARNING_BAD_MOVE)
		return
		(
			cmp_less()(rect_get_left(std::forward<RectA_>(rect_a_)), rect_get_right(std::forward<RectB_>(rect_b_))) &&
			cmp_greater()(rect_get_right(std::forward<RectA_>(rect_a_)), rect_get_left(std::forward<RectB_>(rect_b_))) &&
			cmp_less()(rect_get_top(std::forward<RectA_>(rect_a_)), rect_get_bottom(std::forward<RectB_>(rect_b_))) &&
			cmp_greater()(rect_get_bottom(std::forward<RectA_>(rect_a_)), rect_get_top(std::forward<RectB_>(rect_b_)))
		);
EMU_CORE_MSVC_POP_WARNING_STACK
	}
}

#endif
