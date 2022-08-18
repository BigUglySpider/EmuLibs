#ifndef EMU_MATH_RECT_MUTATE_H_INC_
#define EMU_MATH_RECT_MUTATE_H_INC_ 1

#include "_common_rect_helper_includes.h"
#include "_rect_get.h"

namespace EmuMath::Helpers
{
	/// <summary>
	/// <para> Creates an adjusted form of the passed Rect which is centred on the provided points in the X- and Y-axes respectively. </para>
	/// <para> One should be wary of potential inaccuracies when outputting integral types. This issue can be avoided by outputting floating-point types. </para>
	/// </summary>
	/// <param name="rect_">EmuMath Rect to create a centred form of.</param>
	/// <param name="centre_x_">Point in the X-axis to centre the new Rect on.</param>
	/// <param name="centre_y_">Point in the Y-axis to centre the new Rect on.</param>
	/// <returns>Copy of the passed Rect adjusted to be centred on the provided coordinates in respective axes.</returns>
	template<typename OutT_, typename X_, typename Y_, EmuMath::TMP::EmuRect Rect_>
	[[nodiscard]] constexpr inline EmuMath::Rect<OutT_> rect_make_centred(Rect_&& rect_, X_&& centre_x_, Y_&& centre_y_)
	{
		using rect_uq = typename EmuCore::TMP::remove_ref_cv<Rect_>::type;
		using out_uq = typename EmuCore::TMP::remove_ref_cv<OutT_>::type;
		using x_uq = typename EmuCore::TMP::remove_ref_cv<X_>::type;
		using y_uq = typename EmuCore::TMP::remove_ref_cv<Y_>::type;
		using out_fp = typename EmuMath::Rect<OutT_>::preferred_floating_point;
		using in_fp = typename rect_uq::preferred_floating_point;
		using calc_fp = typename EmuCore::TMP::largest_floating_point<out_uq, x_uq, y_uq, out_fp, in_fp>::type;

		using add_func = EmuCore::do_add<calc_fp, calc_fp>;
		using sub_func = EmuCore::do_subtract<calc_fp, calc_fp>;
		using div_func = EmuCore::do_divide<calc_fp, calc_fp>;

		calc_fp width_div_2 = div_func()(rect_get_width<calc_fp>(std::forward<Rect_>(rect_)), calc_fp(2));
		calc_fp height_div_2 = div_func()(rect_get_height<calc_fp>(std::forward<Rect_>(rect_)), calc_fp(2));
		calc_fp x = static_cast<calc_fp>(std::forward<X_>(centre_x_));
		calc_fp y = static_cast<calc_fp>(std::forward<Y_>(centre_y_));

		return EmuMath::Rect<OutT_>
		(
			sub_func()(x, width_div_2),
			sub_func()(y, height_div_2),
			add_func()(x, width_div_2),
			add_func()(y, height_div_2)
		);
	}

	/// <summary>
	/// <para> Creates an adjusted form of the passed Rect which is centred on the provided points in the X- and Y-axes respectively. </para>
	/// <para> One should be wary of potential inaccuracies when outputting integral types. This issue can be avoided by outputting floating-point types. </para>
	/// </summary>
	/// <param name="rect_">EmuMath Rect to create a centred form of.</param>
	/// <param name="vector_centre_2d_">
	///		EmuMath Vector containing the points to centre the new Rect on in the X- and Y-axes in theoretical indices 0 and 1, respectively.
	/// </param>
	/// <returns>Copy of the passed Rect adjusted to be centred on the provided coordinates in respective axes.</returns>
	template<typename OutT_, EmuMath::TMP::EmuVector CentreVector_, EmuMath::TMP::EmuRect Rect_>
	[[nodiscard]] constexpr inline EmuMath::Rect<OutT_> rect_make_centred(Rect_&& rect_, CentreVector_&& vector_centre_2d_)
	{
		return rect_make_centred<OutT_>
		(
			std::forward<Rect_>(rect_),
			std::forward<CentreVector_>(vector_centre_2d_).template AtTheoretical<0>(),
			std::forward<CentreVector_>(vector_centre_2d_).template AtTheoretical<1>()
		);
	}

	/// <summary>
	/// <para> Creates an adjusted form of the passed Rect which is centred on the provided point in both the X- and Y-axes. </para>
	/// <para> One should be wary of potential inaccuracies when outputting integral types. This issue can be avoided by outputting floating-point types. </para>
	/// </summary>
	/// <param name="rect_">EmuMath Rect to create a centred form of.</param>
	/// <param name="shared_centre_x_and_y_">Scalar point in both the X- and Y-axes to centre the new Rect on.</param>
	/// <returns>Copy of the passed Rect adjusted to be centred on the provided coordinate in both axes.</returns>
	template<typename OutT_, typename ScalarSharedCentre_, EmuMath::TMP::EmuRect Rect_>
	[[nodiscard]] constexpr inline auto rect_make_centred(Rect_&& rect_, ScalarSharedCentre_&& shared_centre_x_and_y_)
		-> std::enable_if_t<!EmuMath::TMP::is_emu_vector_v<ScalarSharedCentre_>, EmuMath::Rect<OutT_>>
	{
		using rect_uq = typename EmuCore::TMP::remove_ref_cv<Rect_>::type;
		using out_uq = typename EmuCore::TMP::remove_ref_cv<OutT_>::type;
		using centre_uq = typename EmuCore::TMP::remove_ref_cv<ScalarSharedCentre_>::type;
		using out_fp = typename EmuMath::Rect<OutT_>::preferred_floating_point;
		using in_fp = typename rect_uq::preferred_floating_point;
		using calc_fp = typename EmuCore::TMP::largest_floating_point<out_uq, centre_uq, out_fp, in_fp>::type;

		using add_func = EmuCore::do_add<calc_fp, calc_fp>;
		using sub_func = EmuCore::do_subtract<calc_fp, calc_fp>;
		using div_func = EmuCore::do_divide<calc_fp, calc_fp>;

		calc_fp width_div_2 = div_func()(rect_get_width<calc_fp>(std::forward<Rect_>(rect_)), calc_fp(2));
		calc_fp height_div_2 = div_func()(rect_get_height<calc_fp>(std::forward<Rect_>(rect_)), calc_fp(2));
		calc_fp x_and_y = static_cast<calc_fp>(std::forward<ScalarSharedCentre_>(shared_centre_x_and_y_)); 

		return EmuMath::Rect<OutT_>
		(
			sub_func()(x_and_y, width_div_2),
			sub_func()(x_and_y, height_div_2),
			add_func()(x_and_y, width_div_2),
			add_func()(x_and_y, height_div_2)
		);
	}

	/// <summary>
	/// <para>
	///		Creates a copy of the passed Rect scaled about its centre, 
	///		changing all boundaries to scale its size in respective axes whilst maintaining the same central point.
	/// </para>
	/// <para> This assumes that the Rect is well-formed. </para>
	/// </summary>
	/// <param name="rect_">EmuMath Rect to create a scaled form of.</param>
	/// <param name="scale_x_">Scale to apply to the passed Rect's width.</param>
	/// <param name="scale_y_">Scale to apply to the passed Rect's height.</param>
	/// <returns>The passed Rect scaled by the provided factors in respective axes, with the same central point.</returns>
	template<typename OutT_, typename X_, typename Y_, EmuMath::TMP::EmuRect Rect_>
	[[nodiscard]] constexpr inline EmuMath::Rect<OutT_> rect_scale(Rect_&& rect_, X_&& scale_x_, Y_&& scale_y_)
	{
		using rect_uq = typename EmuCore::TMP::remove_ref_cv<Rect_>::type;
		using out_uq = typename EmuCore::TMP::remove_ref_cv<OutT_>::type;
		using x_uq = typename EmuCore::TMP::remove_ref_cv<X_>::type;
		using y_uq = typename EmuCore::TMP::remove_ref_cv<Y_>::type;
		using out_fp = typename EmuMath::Rect<OutT_>::preferred_floating_point;
		using in_fp = typename rect_uq::preferred_floating_point;
		using calc_fp = typename EmuCore::TMP::largest_floating_point<out_uq, x_uq, y_uq, out_fp, in_fp>::type;


		using add_func = EmuCore::do_add<calc_fp, calc_fp>;
		using sub_func = EmuCore::do_subtract<calc_fp, calc_fp>;
		using mul_func = EmuCore::do_multiply<calc_fp, calc_fp>;
		using div_func = EmuCore::do_divide<calc_fp, calc_fp>;

		// Central values start as value in of the boundary in the negative direction
		calc_fp centre_x = static_cast<calc_fp>(rect_get_left(std::forward<Rect_>(rect_)));
		calc_fp centre_y = static_cast<calc_fp>(rect_get_top(std::forward<Rect_>(rect_)));

		// Calculate half-sizes manually (in case moves were used above)
		// --- Reminder: centre_x and centre_y are actually the negative-direction boundaries at this stage, so this is (bottom - top) and (right - left)
		calc_fp half_height = div_func()(sub_func()(static_cast<calc_fp>(rect_get_bottom(std::forward<Rect_>(rect_))), centre_y), calc_fp(2));
		calc_fp half_width = div_func()(sub_func()(static_cast<calc_fp>(rect_get_right(std::forward<Rect_>(rect_))), centre_x), calc_fp(2));

		// Actually centre these values
		centre_x = add_func()(centre_x, half_width);
		centre_y = add_func()(centre_y, half_height);

		// Scale half-sizes and then apply them to the centres to make new boundaries
		half_height = mul_func()(half_height, static_cast<calc_fp>(std::forward<Y_>(scale_y_)));
		half_width = mul_func()(half_width, static_cast<calc_fp>(std::forward<X_>(scale_x_)));

		return EmuMath::Rect<OutT_>
		(
			sub_func()(centre_x, half_width),
			sub_func()(centre_y, half_height),
			add_func()(centre_x, half_width),
			add_func()(centre_y, half_height)
		);
	}

	/// <summary>
	/// <para>
	///		Creates a copy of the passed Rect scaled about its centre, 
	///		changing all boundaries to scale its size in all axes whilst maintaining the same central point.
	/// </para>
	/// <para> This assumes that the Rect is well-formed. </para>
	/// </summary>
	/// <param name="rect_">EmuMath Rect to create a scaled form of.</param>
	/// <param name="scale_x_and_y_">Scale to apply to the passed Rect's width and height.</param>
	/// <returns>The passed Rect scaled by the provided factors in all axes, with the same central point.</returns>
	template<typename OutT_, EmuMath::TMP::EmuVector ScaleVector_, EmuMath::TMP::EmuRect Rect_>
	[[nodiscard]] constexpr inline EmuMath::Rect<OutT_> rect_scale(Rect_&& rect_, ScaleVector_&& scale_vector_2d_)
	{
		return rect_scale<OutT_>
		(
			std::forward<Rect_>(rect_),
			std::forward<ScaleVector_>(scale_vector_2d_).template AtTheoretical<0>(),
			std::forward<ScaleVector_>(scale_vector_2d_).template AtTheoretical<1>()
		);
	}

	/// <summary>
	/// <para>
	///		Creates a copy of the passed Rect scaled about its centre, 
	///		changing all boundaries to scale its size in respective axes whilst maintaining the same central point.
	/// </para>
	/// <para> This assumes that the Rect is well-formed. </para>
	/// </summary>
	/// <param name="rect_">EmuMath Rect to create a scaled form of.</param>
	/// <param name="scale_vector_2d_">EmuMath Vector of scales to apply to the passed Rect, with X and Y at theoretical indices 0 and 1 respectively.</param>
	/// <returns>The passed Rect scaled by the provided factors in respective axes, with the same central point.</returns>
	template<typename OutT_, typename ScaleScalar_, EmuMath::TMP::EmuRect Rect_>
	[[nodiscard]] constexpr inline auto rect_scale(Rect_&& rect_, ScaleScalar_&& scale_x_and_y_)
		-> std::enable_if_t<!EmuMath::TMP::is_emu_vector_v<ScaleScalar_>, EmuMath::Rect<OutT_>>
	{
		const auto& scale_x_and_y_lval = EmuCore::TMP::const_lval_ref_cast<ScaleScalar_>(std::forward<ScaleScalar_>(scale_x_and_y_));
		return rect_scale<OutT_>(std::forward<Rect_>(rect_), scale_x_and_y_lval, scale_x_and_y_lval);
	}

	/// <summary>
	/// <para> Creates a copy of the passed Rect scaled about the specified anchor. </para>
	/// <para> XAnchorDirection_: 0: Centre of the X-axis; Negative: Left boundary of the X-axis; Positive non-0: Right boundary of the X-axis. </para>
	/// <para> YAnchorDirection_: 0: Centre of the Y-axis; Negative: Top boundary of the Y-axis; Positive non-0: Bottom boundary of the Y-axis. </para>
	/// <para> When anchored to a boundary, that boundary will not be modified and the opposite boundary will receive the full effect of the scale. </para>
	/// <para> When anchored to a central point, both of that axis's boundaries scaled by half the amount to maintain the same central point. </para>
	/// <para> This assumes that the Rect is well-formed. </para>
	/// </summary>
	/// <param name="rect_">EmuMath Rect to create a scaled form of.</param>
	/// <param name="scale_x_">Scale to apply to the passed Rect's width.</param>
	/// <param name="scale_y_">Scale to apply to the passed Rect's height.</param>
	/// <returns>The passed Rect scaled by the provided factor in respective axes, with points of specified anchors maintained as the same value.</returns>
	template<signed int XAnchorDirection_, signed int YAnchorDirection_, typename OutT_, typename X_, typename Y_, EmuMath::TMP::EmuRect Rect_>
	[[nodiscard]] constexpr inline EmuMath::Rect<OutT_> rect_scale_anchored(Rect_&& rect_, X_&& scale_x_, Y_&& scale_y_)
	{
		if constexpr (XAnchorDirection_ == 0 && YAnchorDirection_ == 0)
		{
			return rect_scale<OutT_>(std::forward<Rect_>(rect_), std::forward<X_>(scale_x_), std::forward<Y_>(scale_y_));
		}
		else
		{
			using rect_uq = typename EmuCore::TMP::remove_ref_cv<Rect_>::type;
			using out_uq = typename EmuCore::TMP::remove_ref_cv<OutT_>::type;
			using x_uq = typename EmuCore::TMP::remove_ref_cv<X_>::type;
			using y_uq = typename EmuCore::TMP::remove_ref_cv<Y_>::type;
			using out_fp = typename EmuMath::Rect<OutT_>::preferred_floating_point;
			using in_fp = typename rect_uq::preferred_floating_point;
			using calc_fp = typename EmuCore::TMP::largest_floating_point<out_uq, x_uq, y_uq, out_fp, in_fp>::type;


			using add_func = EmuCore::do_add<calc_fp, calc_fp>;
			using sub_func = EmuCore::do_subtract<calc_fp, calc_fp>;
			using mul_func = EmuCore::do_multiply<calc_fp, calc_fp>;
			using div_func = EmuCore::do_divide<calc_fp, calc_fp>;

			// Central values start as value of the boundary in the negative direction
			calc_fp anchored_x = static_cast<calc_fp>(rect_get_left(std::forward<Rect_>(rect_)));
			calc_fp anchored_y = static_cast<calc_fp>(rect_get_top(std::forward<Rect_>(rect_)));

			// Calculate sizes manually (in case moves were used above)
			// --- Reminder: centre_x and centre_y are actually the negative-direction boundaries at this stage, so this is (bottom - top) and (right - left)
			// --- Respective sizes will be halved later for anchors in the positive direction
			calc_fp height = sub_func()(static_cast<calc_fp>(rect_get_bottom(std::forward<Rect_>(rect_))), anchored_y);
			calc_fp width = sub_func()(static_cast<calc_fp>(rect_get_right(std::forward<Rect_>(rect_))), anchored_x);

			// Actually anchor these values, and update sizes to correctly calculate end results
			// --- No need to modify if anchor direction is negative, as we are already bound to that anchor with the correct width for calculation
			if constexpr (XAnchorDirection_ >= 0)
			{
				if constexpr (XAnchorDirection_ == 0)
				{
					width = div_func()(width, calc_fp(2));
				}
				anchored_x = add_func()(anchored_x, width);
			}

			if constexpr (YAnchorDirection_ >= 0)
			{
				if constexpr (YAnchorDirection_ == 0)
				{
					height = div_func()(height, calc_fp(2));
				}
				anchored_y = add_func()(anchored_y, height);
			}

			// Scale sizes and then apply them to the centres to make new boundaries
			height = mul_func()(height, static_cast<calc_fp>(std::forward<Y_>(scale_y_)));
			width = mul_func()(width, static_cast<calc_fp>(std::forward<X_>(scale_x_)));

			// Declare output boundaries as their anchors
			calc_fp left = anchored_x;
			calc_fp top = anchored_y;
			calc_fp right = anchored_x;
			calc_fp bottom = anchored_y;

			// Follows the pattern:
			// --- Negative boundaries need respective size subtracted with non-negative anchors, otherwise ready
			// --- Positive boundaries need respective size added with centred or negative anchors, otherwise ready
			if constexpr (XAnchorDirection_ >= 0)
			{
				left = sub_func()(left, width);
			}

			if constexpr (YAnchorDirection_ >= 0)
			{
				top = sub_func()(top, height);
			}

			if constexpr (XAnchorDirection_ <= 0)
			{
				right = add_func()(right, width);
			}

			if constexpr (YAnchorDirection_ <= 0)
			{
				bottom = add_func()(bottom, height);
			}

			return EmuMath::Rect<OutT_>
			(
				std::move(left),
				std::move(top),
				std::move(right),
				std::move(bottom)
			);
		}
	}

	/// <summary>
	/// <para> Creates a copy of the passed Rect scaled about the specified anchor. </para>
	/// <para> XAnchorDirection_: 0: Centre of the X-axis; Negative: Left boundary of the X-axis; Positive non-0: Right boundary of the X-axis. </para>
	/// <para> YAnchorDirection_: 0: Centre of the Y-axis; Negative: Top boundary of the Y-axis; Positive non-0: Bottom boundary of the Y-axis. </para>
	/// <para> When anchored to a boundary, that boundary will not be modified and the opposite boundary will receive the full effect of the scale. </para>
	/// <para> When anchored to a central point, both of that axis's boundaries scaled by half the amount to maintain the same central point. </para>
	/// <para> This assumes that the Rect is well-formed. </para>
	/// </summary>
	/// <param name="rect_">EmuMath Rect to create a scaled form of.</param>
	/// <param name="scale_vector_2d_">EmuMath Vector of scales to apply to the passed Rect, with X and Y at theoretical indices 0 and 1 respectively.</param>
	/// <returns>The passed Rect scaled by the provided factor in respective axes, with points of specified anchors maintained as the same value.</returns>
	template<signed int XAnchorDirection_, signed int YAnchorDirection_, typename OutT_, EmuMath::TMP::EmuVector ScaleVector_,  EmuMath::TMP::EmuRect Rect_>
	[[nodiscard]] constexpr inline EmuMath::Rect<OutT_> rect_scale_anchored(Rect_&& rect_, ScaleVector_&& scale_vector_2d_)
	{
		return rect_scale_anchored<XAnchorDirection_, YAnchorDirection_, OutT_>
		(
			std::forward<Rect_>(rect_),
			std::forward<ScaleVector_>(scale_vector_2d_).template AtTheoretical<0>(),
			std::forward<ScaleVector_>(scale_vector_2d_).template AtTheoretical<1>()
		);
	}

	/// <summary>
	/// <para> Creates a copy of the passed Rect scaled about the specified anchor. </para>
	/// <para> XAnchorDirection_: 0: Centre of the X-axis; Negative: Left boundary of the X-axis; Positive non-0: Right boundary of the X-axis. </para>
	/// <para> YAnchorDirection_: 0: Centre of the Y-axis; Negative: Top boundary of the Y-axis; Positive non-0: Bottom boundary of the Y-axis. </para>
	/// <para> When anchored to a boundary, that boundary will not be modified and the opposite boundary will receive the full effect of the scale. </para>
	/// <para> When anchored to a central point, both of that axis's boundaries scaled by half the amount to maintain the same central point. </para>
	/// <para> This assumes that the Rect is well-formed. </para>
	/// </summary>
	/// <param name="rect_">EmuMath Rect to create a scaled form of.</param>
	/// <param name="scale_x_and_y_">Scale to apply to the passed Rect's width and height.</param>
	/// <returns>The passed Rect scaled by the provided factor in all axes, with points of specified anchors maintained as the same value.</returns>
	template<signed int XAnchorDirection_, signed int YAnchorDirection_, typename OutT_, typename ScaleScalar_,  EmuMath::TMP::EmuRect Rect_>
	[[nodiscard]] constexpr inline auto rect_scale_anchored(Rect_&& rect_, ScaleScalar_&& scale_x_and_y_)
		-> std::enable_if_t<!EmuMath::TMP::is_emu_vector_v<ScaleScalar_>, EmuMath::Rect<OutT_>>
	{
		const auto& scale_x_and_y_lval = EmuCore::TMP::const_lval_ref_cast<ScaleScalar_>(std::forward<ScaleScalar_>(scale_x_and_y_));
		return rect_scale_anchored<XAnchorDirection_, YAnchorDirection_, OutT_>(std::forward<Rect_>(rect_), scale_x_and_y_lval, scale_x_and_y_lval);
	}
}

#endif
