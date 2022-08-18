#ifndef EMU_MATH_RECT_GET_H_INC_
#define EMU_MATH_RECT_GET_H_INC_ 1

#include "_common_rect_helper_includes.h"

namespace EmuMath::Helpers
{
	/// <summary>
	/// <para> Retrieves a reference to the value indicating the X coordinate of corners on the left of the passed Rect. </para>
	/// </summary>
	/// <param name="rect_">EmuMath Rect to retrieve to `left` value of.</param>
	/// <returns>Lvalue or Rvalue reference to the X coordinate of left corners in the passed Rect, depending on the qualification of `rect_`.</returns>
	template<EmuMath::TMP::EmuRect Rect_>
	[[nodiscard]] constexpr inline decltype(auto) rect_get_left(Rect_&& rect_)
	{
		return std::forward<Rect_>(rect_).Left();
	}

	/// <summary>
	/// <para> Retrieves a reference to the value indicating the X coordinate of corners on the right of the passed Rect. </para>
	/// </summary>
	/// <param name="rect_">EmuMath Rect to retrieve to `right` value of.</param>
	/// <returns>Lvalue or Rvalue reference to the X coordinate of right corners in the passed Rect, depending on the qualification of `rect_`.</returns>
	template<EmuMath::TMP::EmuRect Rect_>
	[[nodiscard]] constexpr inline decltype(auto) rect_get_right(Rect_&& rect_)
	{
		return std::forward<Rect_>(rect_).Right();
	}

	/// <summary>
	/// <para> Retrieves a reference to the value indicating the Y coordinate of corners on the top of the passed Rect. </para>
	/// </summary>
	/// <param name="rect_">EmuMath Rect to retrieve to `top` value of.</param>
	/// <returns>Lvalue or Rvalue reference to the Y coordinate of top corners in the passed Rect, depending on the qualification of `rect_`.</returns>
	template<EmuMath::TMP::EmuRect Rect_>
	[[nodiscard]] constexpr inline decltype(auto) rect_get_top(Rect_&& rect_)
	{
		return std::forward<Rect_>(rect_).Top();
	}

	/// <summary>
	/// <para> Retrieves a reference to the value indicating the Y coordinate of corners on the bottom of the passed Rect. </para>
	/// </summary>
	/// <param name="rect_">EmuMath Rect to retrieve to `bottom` value of.</param>
	/// <returns>Lvalue or Rvalue reference to the Y coordinate of bottom corners in the passed Rect, depending on the qualification of `rect_`.</returns>
	template<EmuMath::TMP::EmuRect Rect_>
	[[nodiscard]] constexpr inline decltype(auto) rect_get_bottom(Rect_&& rect_)
	{
		return std::forward<Rect_>(rect_).Bottom();
	}

	/// <summary>
	/// <para> Calculates the width of the passed Rect based on the distance between its left and right points. </para>
	/// <para> This assumes that the Rect is well-formed. </para>
	/// </summary>
	/// <returns>The width of the passed Rect, based on `Right - Left`.</returns>
	template<typename OutT_, EmuMath::TMP::EmuRect Rect_>
	[[nodiscard]] constexpr inline OutT_ rect_get_width(Rect_&& rect_)
	{
		using rect_uq = typename EmuCore::TMP::remove_ref_cv<Rect_>::type;
		using sub_func = EmuCore::do_subtract<typename rect_uq::value_type_uq, typename rect_uq::value_type_uq>;
		return static_cast<OutT_>(sub_func()(rect_get_right(std::forward<Rect_>(rect_)), rect_get_left(std::forward<Rect_>(rect_))));
	}

	/// <summary>
	/// <para> Calculates the height of the passed Rect based on the distance between its top and bottom points. </para>
	/// <para> This assumes that the Rect is well-formed. </para>
	/// </summary>
	/// <returns>The height of the passed Rect, based on `Bottom - Top`.</returns>
	template<typename OutT_, EmuMath::TMP::EmuRect Rect_>
	[[nodiscard]] constexpr inline OutT_ rect_get_height(Rect_&& rect_)
	{
		using rect_uq = typename EmuCore::TMP::remove_ref_cv<Rect_>::type;
		using sub_func = EmuCore::do_subtract<typename rect_uq::value_type_uq, typename rect_uq::value_type_uq>;
		return static_cast<OutT_>(sub_func()(rect_get_bottom(std::forward<Rect_>(rect_)), rect_get_top(std::forward<Rect_>(rect_))));
	}

	/// <summary>
	/// <para>
	///		Calculates the width of the passed Rect based on the distance between its left and right points, 
	///		and its height based on the distance between its top and bottom points.
	/// </para>
	/// <para> This assumes that the Rect is well-formed. </para>
	/// </summary>
	/// <returns>2D Vector containing the width of the passed Rect in index 0, and its height in index 1.</returns>
	template<typename OutT_, EmuMath::TMP::EmuRect Rect_>
	[[nodiscard]] constexpr inline EmuMath::Vector<2, OutT_> rect_get_size(Rect_&& rect_)
	{
		return EmuMath::Vector<2, OutT_>
		(
			rect_get_width<OutT_>(std::forward<Rect_>(rect_)),
			rect_get_height<OutT_>(std::forward<Rect_>(rect_))
		);
	}

	/// <summary>
	/// <para> Calculates the squared length of the passed Rectangle's diagonal. </para>
	/// <para> This assumes that the Rect is well-formed, and is based on the `Size` of the passed Rectangle. </para>
	/// </summary>
	/// <returns>The squared length of the passed Rectangle.</returns>
	template<typename Out_, EmuMath::TMP::EmuRect Rect_>
	[[nodiscard]] constexpr inline Out_ rect_get_diagonal_length_squared(Rect_&& rect_)
	{
		return EmuMath::Helpers::vector_square_magnitude<Out_>(rect_get_size<Out_>(std::forward<Rect_>(rect_)));
	}

	/// <summary>
	/// <para> Calculates the length of the passed Rectangle's diagonal. </para>
	/// <para> This assumes that the Rect is well-formed, and is based on the `Size` of the passed Rectangle. </para>
	/// </summary>
	/// <returns>The length of the passed Rectangle.</returns>
	template<typename Out_, EmuMath::TMP::EmuRect Rect_>
	[[nodiscard]] constexpr inline Out_ rect_get_diagonal_length(Rect_&& rect_)
	{
		return EmuMath::Helpers::vector_magnitude<Out_>(rect_get_size<Out_>(std::forward<Rect_>(rect_)));
	}

	/// <summary>
	/// <para> Calculates the length of the passed Rectangle's diagonal. </para>
	/// <para> This assumes that the Rect is well-formed, and is based on the `Size` of the passed Rectangle. </para>
	/// <para> Calculation will aim to be constexpr-evaluable if possible, which may affect accuracy and/or performance. </para>
	/// </summary>
	/// <returns>The length of the passed Rectangle.</returns>
	template<typename Out_, EmuMath::TMP::EmuRect Rect_>
	[[nodiscard]] constexpr inline Out_ rect_get_diagonal_length_constexpr(Rect_&& rect_)
	{
		return EmuMath::Helpers::vector_magnitude_constexpr<Out_>(rect_get_size<Out_>(std::forward<Rect_>(rect_)));
	}

	/// <summary>
	/// <para> Calculates the central point of the passed Rectangle in the X-axis. </para>
	/// <para> This assumes that the Rect is well-formed, and is based on the `Width` of the passed Rectangle. </para>
	/// </summary>
	/// <returns>Central point of the passed Rectangle in the X-axis.</returns>
	template<typename Out_, EmuMath::TMP::EmuRect Rect_>
	[[nodiscard]] constexpr inline Out_ rect_get_centre_x(Rect_&& rect_)
	{
		using rect_uq = typename EmuCore::TMP::remove_ref_cv<Rect_>::type;
		using out_uq = typename EmuCore::TMP::remove_ref_cv<Out_>::type;
		using calc_fp = typename EmuCore::TMP::largest_floating_point<out_uq, typename rect_uq::preferred_floating_point, float>::type;
		using sub_func = EmuCore::do_subtract<calc_fp, calc_fp>;
		using div_func = EmuCore::do_divide<calc_fp, calc_fp>;

		calc_fp right = static_cast<calc_fp>(rect_get_right(std::forward<Rect_>(rect_)));
		return static_cast<Out_>
		(
			sub_func()
			(
				right,
				div_func()
				(
					sub_func()(right, static_cast<calc_fp>(rect_get_left(std::forward<Rect_>(rect_)))),
					calc_fp(2)
				)
			)
		);
	}

	/// <summary>
	/// <para> Calculates the central point of the passed Rectangle in the Y-axis. </para>
	/// <para> This assumes that the Rect is well-formed, and is based on the `Height` of the passed Rectangle. </para>
	/// </summary>
	/// <returns>Central point of the passed Rectangle in the Y-axis.</returns>
	template<typename Out_, EmuMath::TMP::EmuRect Rect_>
	[[nodiscard]] constexpr inline Out_ rect_get_centre_y(Rect_&& rect_)
	{
		using rect_uq = typename EmuCore::TMP::remove_ref_cv<Rect_>::type;
		using out_uq = typename EmuCore::TMP::remove_ref_cv<Out_>::type;
		using calc_fp = typename EmuCore::TMP::largest_floating_point<out_uq, typename rect_uq::preferred_floating_point, float>::type;
		using sub_func = EmuCore::do_subtract<calc_fp, calc_fp>;
		using div_func = EmuCore::do_divide<calc_fp, calc_fp>;

		calc_fp bottom = static_cast<calc_fp>(rect_get_bottom(std::forward<Rect_>(rect_)));
		return static_cast<Out_>
		(
			sub_func()
			(
				bottom,
				div_func()
				(
					sub_func()(bottom, static_cast<calc_fp>(rect_get_top(std::forward<Rect_>(rect_)))),
					calc_fp(2)
				)
			)
		);
	}

	/// <summary>
	/// <para> Calculates the central point of the passed Rectangle, and outputs the X- and Y-axes' points as indices 0 and 1 (respectively) of a 2D Vector. </para>
	/// <para> This assumes that the Rect is well-formed, and is based on the `Width` and `Height` of the passed Rectangle. </para>
	/// </summary>
	/// <returns>2D EmuMath Vector containing the passed Rect's central X and Y points in indices 0 and 1 respectively.</returns>
	template<typename OutT_, EmuMath::TMP::EmuRect Rect_>
	[[nodiscard]] constexpr inline EmuMath::Vector<2, OutT_> rect_get_centre(Rect_&& rect_)
	{
		return EmuMath::Vector<2, OutT_>
		(
			rect_get_centre_x<OutT_>(std::forward<Rect_>(rect_)),
			rect_get_centre_y<OutT_>(std::forward<Rect_>(rect_))
		);
	}
}

#endif
