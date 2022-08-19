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
	template<EmuMath::TMP::EmuRect Rect_>
	[[nodiscard]] constexpr inline bool rect_has_well_formed_x(Rect_&& rect_)
	{
		using get_left_result = decltype(rect_get_left(std::forward<Rect_>(rect_)));
		using get_right_result = decltype(rect_get_right(std::forward<Rect_>(rect_)));
		using get_left_uq = typename EmuCore::TMP::remove_ref_cv<get_left_result>::type;
		using get_right_uq = typename EmuCore::TMP::remove_ref_cv<get_right_result>::type;
		using cmp = EmuCore::do_cmp_less_equal<get_left_uq, get_right_uq>;

#pragma warning(push)
#pragma warning(disable: 26800)
		return cmp()
		(
			std::forward<get_left_result>(rect_get_left(std::forward<Rect_>(rect_))),
			std::forward<get_right_result>(rect_get_right(std::forward<Rect_>(rect_)))
		);
#pragma warning(pop)
	}

	/// <summary>
	/// <para> Checks if the current state of the passed Rect has a well-formed Y axis. </para>
	/// <para> A well-formed Y-axis will have a Top value less than or equal to its Bottom value. </para>
	/// </summary>
	/// <returns>True if the passed Rect's Y-axis is well-formed; otherwise false.</returns>
	template<EmuMath::TMP::EmuRect Rect_>
	[[nodiscard]] constexpr inline bool rect_has_well_formed_y(Rect_&& rect_)
	{
		using get_top_result = decltype(rect_get_top(std::forward<Rect_>(rect_)));
		using get_bottom_result = decltype(rect_get_bottom(std::forward<Rect_>(rect_)));
		using get_left_uq = typename EmuCore::TMP::remove_ref_cv<get_top_result>::type;
		using get_right_uq = typename EmuCore::TMP::remove_ref_cv<get_bottom_result>::type;
		using cmp = EmuCore::do_cmp_less_equal<get_left_uq, get_right_uq>;

#pragma warning(push)
#pragma warning(disable: 26800)
		return cmp()
		(
			std::forward<get_top_result>(rect_get_top(std::forward<Rect_>(rect_))),
			std::forward<get_bottom_result>(rect_get_bottom(std::forward<Rect_>(rect_)))
		);
#pragma warning(pop)
	}

	/// <summary>
	/// <para> Checks if the current state of the passed Rect is well-formed.</para>
	/// <para> A well-formed Rect will have a Left value less than or equal to its Right value, and a Top value less than or equal to its Bottom value. </para>
	/// </summary>
	/// <returns>True if the passed Rect's X- and Y-axes are both well-formed; otherwise false.</returns>
	template<EmuMath::TMP::EmuRect Rect_>
	[[nodiscard]] constexpr inline bool rect_is_well_formed(Rect_&& rect_)
	{
		return rect_has_well_formed_x(std::forward<Rect_>(rect_)) && rect_has_well_formed_y(std::forward<Rect_>(rect_));
	}

	template<typename X_, typename Y_, EmuMath::TMP::EmuRect Rect_>
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

#pragma warning(push)
#pragma warning(disable: 26800)
		return
		(
			EmuCore::do_cmp_less_equal<get_left_uq, x_uq>()(rect_get_left(std::forward<Rect_>(rect_)), x) &&
			EmuCore::do_cmp_less_equal<get_top_uq, y_uq>()(rect_get_top(std::forward<Rect_>(rect_)), y) &&
			EmuCore::do_cmp_greater_equal<get_right_uq, x_uq>()(rect_get_right(std::forward<Rect_>(rect_)), x) &&
			EmuCore::do_cmp_greater_equal<get_bottom_uq, y_uq>()(rect_get_bottom(std::forward<Rect_>(rect_)), y)
		);
#pragma warning(pop)
	}

	template<EmuMath::TMP::EmuVector PointVector_, EmuMath::TMP::EmuRect Rect_>
	[[nodiscard]] constexpr inline bool rect_contains_point(Rect_&& rect_, PointVector_&& point_vector_2d_)
	{
#pragma warning(push)
#pragma warning(disable: 26800)
		return rect_contains_point
		(
			std::forward<Rect_>(rect_),
			std::forward<PointVector_>(point_vector_2d_).template AtTheoretical<0>(),
			std::forward<PointVector_>(point_vector_2d_).template AtTheoretical<1>()
		);
#pragma warning(pop)
	}

	template<bool IgnoreEqual_ = true, EmuMath::TMP::EmuRect RectA_, EmuMath::TMP::EmuRect RectB_>
	[[nodiscard]] constexpr inline bool rect_colliding_axis_aligned(RectA_&& rect_a_, RectB_&& rect_b_)
	{
		using cmp_less = typename std::conditional<IgnoreEqual_, EmuCore::do_cmp_less<void, void>, EmuCore::do_cmp_less_equal<void, void>>::type;
		using cmp_greater = typename std::conditional<IgnoreEqual_, EmuCore::do_cmp_greater<void, void>, EmuCore::do_cmp_greater_equal<void, void>>::type;

#pragma warning(push)
#pragma warning(disable: 26800)
		return
		(
			cmp_less()(rect_get_left(std::forward<RectA_>(rect_a_)), rect_get_right(std::forward<RectB_>(rect_b_))) &&
			cmp_greater()(rect_get_right(std::forward<RectA_>(rect_a_)), rect_get_left(std::forward<RectB_>(rect_b_))) &&
			cmp_less()(rect_get_top(std::forward<RectA_>(rect_a_)), rect_get_bottom(std::forward<RectB_>(rect_b_))) &&
			cmp_greater()(rect_get_bottom(std::forward<RectA_>(rect_a_)), rect_get_top(std::forward<RectB_>(rect_b_)))
		);
#pragma warning(pop)
	}
}

#endif
