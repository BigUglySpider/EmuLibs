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

#pragma warning(push)
#pragma warning(disable: 26800)
		return EmuMath::Rect<OutT_>
		(
			sub_func()(x, width_div_2),
			sub_func()(y, height_div_2),
			add_func()(x, width_div_2),
			add_func()(y, height_div_2)
		);
#pragma warning(pop)
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
#pragma warning(push)
#pragma warning(disable: 26800)
		return rect_make_centred<OutT_>
		(
			std::forward<Rect_>(rect_),
			std::forward<CentreVector_>(vector_centre_2d_).template AtTheoretical<0>(),
			std::forward<CentreVector_>(vector_centre_2d_).template AtTheoretical<1>()
		);
#pragma warning(pop)
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

#pragma warning(push)
#pragma warning(disable: 26800)
		calc_fp width_div_2 = div_func()(rect_get_width<calc_fp>(std::forward<Rect_>(rect_)), calc_fp(2));
		calc_fp height_div_2 = div_func()(rect_get_height<calc_fp>(std::forward<Rect_>(rect_)), calc_fp(2));
		calc_fp x_and_y = static_cast<calc_fp>(std::forward<ScalarSharedCentre_>(shared_centre_x_and_y_));
#pragma warning(pop)

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

#pragma warning(push)
#pragma warning(disable: 26800)
		// Central values start as value in of the boundary in the negative direction
		calc_fp centre_x = static_cast<calc_fp>(rect_get_left(std::forward<Rect_>(rect_)));
		calc_fp centre_y = static_cast<calc_fp>(rect_get_top(std::forward<Rect_>(rect_)));

		// Calculate half-sizes manually (in case moves were used above)
		// --- Reminder: centre_x and centre_y are actually the negative-direction boundaries at this stage, so this is (bottom - top) and (right - left)
		calc_fp half_height = div_func()(sub_func()(static_cast<calc_fp>(rect_get_bottom(std::forward<Rect_>(rect_))), centre_y), calc_fp(2));
		calc_fp half_width = div_func()(sub_func()(static_cast<calc_fp>(rect_get_right(std::forward<Rect_>(rect_))), centre_x), calc_fp(2));
#pragma warning(pop)

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
#pragma warning(push)
#pragma warning(disable: 26800)
		return rect_scale<OutT_>
		(
			std::forward<Rect_>(rect_),
			std::forward<ScaleVector_>(scale_vector_2d_).template AtTheoretical<0>(),
			std::forward<ScaleVector_>(scale_vector_2d_).template AtTheoretical<1>()
		);
#pragma warning(pop)
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

#pragma warning(push)
#pragma warning(disable: 26800)
			// Central values start as value of the boundary in the negative direction
			calc_fp anchored_x = static_cast<calc_fp>(rect_get_left(std::forward<Rect_>(rect_)));
			calc_fp anchored_y = static_cast<calc_fp>(rect_get_top(std::forward<Rect_>(rect_)));

			// Calculate sizes manually (in case moves were used above)
			// --- Reminder: centre_x and centre_y are actually the negative-direction boundaries at this stage, so this is (bottom - top) and (right - left)
			// --- Respective sizes will be halved later for anchors in the positive direction
			calc_fp height = sub_func()(static_cast<calc_fp>(rect_get_bottom(std::forward<Rect_>(rect_))), anchored_y);
			calc_fp width = sub_func()(static_cast<calc_fp>(rect_get_right(std::forward<Rect_>(rect_))), anchored_x);
#pragma warning(pop)

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
#pragma warning(push)
#pragma warning(disable: 26800)
		return rect_scale_anchored<XAnchorDirection_, YAnchorDirection_, OutT_>
		(
			std::forward<Rect_>(rect_),
			std::forward<ScaleVector_>(scale_vector_2d_).template AtTheoretical<0>(),
			std::forward<ScaleVector_>(scale_vector_2d_).template AtTheoretical<1>()
		);
#pragma warning(pop)
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

	/// <summary>
	/// <para> Creates a copy of the passed Rect moved by the specified amounts in respective axes. </para>
	/// <para> This effectively adds the `x_` translation to `Left` and `Right`, and adds `y_` to `Top` and `Bottom`. </para>
	/// </summary>
	/// <param name="x_">Amount to move the passed Rectangle by in the X-axis.</param>
	/// <param name="y_">Amount to move the passed Rectangle by in the Y-axis.</param>
	/// <returns>The passed Rect translated by the specified amounts in respective axes.</returns>
	template<typename OutT_, typename X_, typename Y_, EmuMath::TMP::EmuRect Rect_>
	[[nodiscard]] constexpr inline EmuMath::Rect<OutT_> rect_translate(Rect_&& rect_, X_&& x_, Y_&& y_)
	{
		using x_uq = typename EmuCore::TMP::remove_ref_cv<X_>::type;
		using y_uq = typename EmuCore::TMP::remove_ref_cv<Y_>::type;
		using in_uq = typename EmuCore::TMP::remove_ref_cv<Rect_>::type;
		using out_value_uq = typename EmuMath::Rect<OutT_>::value_type_uq;
		using in_value_uq = typename in_uq::value_type_uq;
		using in_fp = typename in_uq::preferred_floating_point;
		using out_fp = typename EmuMath::Rect<OutT_>::preferred_floating_point;
		using calc_type = typename std::conditional
		<
			EmuCore::TMP::is_any_floating_point_v<x_uq, y_uq, in_value_uq>,
			typename EmuCore::TMP::largest_floating_point<x_uq, y_uq, in_value_uq, in_fp, out_value_uq, out_fp>::type,
			typename EmuCore::TMP::highest_byte_size<x_uq, y_uq, in_value_uq>::type
		>::type;

		using add_func = EmuCore::do_add<calc_type, calc_type>;
		calc_type x = static_cast<calc_type>(std::forward<X_>(x_));
		calc_type y = static_cast<calc_type>(std::forward<Y_>(y_));

#pragma warning(push)
#pragma warning(disable: 26800)
		return EmuMath::Rect<OutT_>
		(
			add_func()(rect_get_left(std::forward<Rect_>(rect_)), x),
			add_func()(rect_get_top(std::forward<Rect_>(rect_)), y),
			add_func()(rect_get_right(std::forward<Rect_>(rect_)), x),
			add_func()(rect_get_bottom(std::forward<Rect_>(rect_)), y)
		);
#pragma warning(pop)
	}

	/// <summary>
	/// <para> Creates a copy of the passed Rect moved by the specified amounts in respective axes. </para>
	/// <para> This effectively adds the `x_` translation to `Left` and `Right`, and adds `y_` to `Top` and `Bottom`. </para>
	/// </summary>
	/// <param name="translation_vector_2d_">
	///		EmuMath Vector of translations to apply to the passed Rect, with X and Y at theoretical indices 0 and 1 respectively.
	/// </param>
	/// <returns>The passed Rect translated by the specified amounts in respective axes.</returns>
	template<typename OutT_, EmuMath::TMP::EmuVector TranslationVector_, EmuMath::TMP::EmuRect Rect_>
	[[nodiscard]] constexpr inline EmuMath::Rect<OutT_> rect_translate(Rect_&& rect_, TranslationVector_&& translation_vector_2d_)
	{
#pragma warning(push)
#pragma warning(disable: 26800)
		return rect_translate<OutT_>
		(
			std::forward<Rect_>(rect_),
			std::forward<TranslationVector_>(translation_vector_2d_).template AtTheoretical<0>(),
			std::forward<TranslationVector_>(translation_vector_2d_).template AtTheoretical<1>()
		);
#pragma warning(pop)
	}

	/// <summary>
	/// <para> Creates a reflected copy of the passed Rect in the specified X- and Y-directions </para>
	/// <para> XDirection_: 0: No X-axis reflection; Positive: Reflect against Right boundary; Negative: Reflect against Left boundary. </para>
	/// <para> YDirection_: 0: No Y-axis reflection; Positive: Reflect against Bottom boundary; Negative: Reflect against Top boundary. </para>
	/// <para> This assumes that the Rect is well-formed. </para>
	/// </summary>
	/// <returns>The passed Rect reflected as specified by the passed template arguments.</returns>
	template<signed int XDirection_, signed int YDirection_, typename OutT_, EmuMath::TMP::EmuRect Rect_>
	[[nodiscard]] constexpr inline EmuMath::Rect<OutT_> rect_reflect(Rect_&& rect_)
	{
		using in_uq = typename EmuCore::TMP::remove_ref_cv<Rect_>::type;
		using in_value_uq = typename in_uq::value_type_uq;

		using add_func = EmuCore::do_add<in_value_uq, in_value_uq>;
		using sub_func = EmuCore::do_subtract<in_value_uq, in_value_uq>;

#pragma warning(push)
#pragma warning(disable: 26800)
		in_value_uq left = rect_get_left(std::forward<Rect_>(rect_));
		in_value_uq top = rect_get_top(std::forward<Rect_>(rect_));
		in_value_uq right = rect_get_right(std::forward<Rect_>(rect_));
		in_value_uq bottom = rect_get_bottom(std::forward<Rect_>(rect_));
#pragma warning(pop)

		// If a direction is 0, there is no reflection in that axis and thus boundaries remain the same
		// --- If reflecting in negative direction, negative boundary has size subtracted and positive boundary becomes old negative boundary
		// --- If reflecting in positive direction, negative boundary becomes old positive boundary and positive boundary has size added
		if constexpr (XDirection_ < 0)
		{
			// left = (old_left - width), right = old_left
			in_value_uq width = sub_func()(right, left);
			right = std::move(left);
			left = sub_func()(right, std::move(width));
		}
		else if constexpr (XDirection_ > 0)
		{
			// left = old_right, right = (old_right + width)
			in_value_uq width = sub_func()(right, left);
			left = std::move(right);
			right = add_func()(left, std::move(width));
		}

		if constexpr (YDirection_ < 0)
		{
			// top = (old_top - height), right = old_top
			in_value_uq height = sub_func()(bottom, top);
			bottom = std::move(top);
			top = sub_func()(bottom, std::move(height));
		}
		else if constexpr (YDirection_ > 0)
		{
			// top = old_bottom, bottom = (old_bottom + height)
			in_value_uq height = sub_func()(bottom, top);
			top = std::move(bottom);
			bottom = add_func()(top, std::move(height));
		}

		return EmuMath::Rect<OutT_>
		(
			std::move(left),
			std::move(top),
			std::move(right),
			std::move(bottom)
		);
	}

	/// <summary>
	/// <para> Creates a reflected copy of the passed Rect in the specified X- and Y-directions </para>
	/// <para> If `x_direction_` and `y_direction_` are known compile-time constants, it is recommended to pass them as template arguments instead. </para>
	/// <para> This assumes that the Rect is well-formed. </para>
	/// </summary>
	/// <param name="x_direction_">0: No X-axis reflection; Positive: Reflect against Right boundary; Negative: Reflect against Left boundary.</param>
	/// <param name="y_direction_">0: No Y-axis reflection; Positive: Reflect against Bottom boundary; Negative: Reflect against Top boundary.</param>
	/// <returns>The passed Rect reflected as specified by the passed arguments.</returns>
	template<typename OutT_, EmuMath::TMP::EmuRect Rect_>
	[[nodiscard]] constexpr inline EmuMath::Rect<OutT_> rect_reflect(Rect_&& rect_, signed int x_direction_, signed int y_direction_)
	{
		// Identical to above version, but runtime conditional branches
		using in_uq = typename EmuCore::TMP::remove_ref_cv<Rect_>::type;
		using in_value_uq = typename in_uq::value_type_uq;

		using add_func = EmuCore::do_add<in_value_uq, in_value_uq>;
		using sub_func = EmuCore::do_subtract<in_value_uq, in_value_uq>;

#pragma warning(push)
#pragma warning(disable: 26800)
		in_value_uq left = rect_get_left(std::forward<Rect_>(rect_));
		in_value_uq top = rect_get_top(std::forward<Rect_>(rect_));
		in_value_uq right = rect_get_right(std::forward<Rect_>(rect_));
		in_value_uq bottom = rect_get_bottom(std::forward<Rect_>(rect_));
#pragma warning(pop)

		// If a direction is 0, there is no reflection in that axis and thus boundaries remain the same
		// --- If reflecting in negative direction, negative boundary has size subtracted and positive boundary becomes old negative boundary
		// --- If reflecting in positive direction, negative boundary becomes old positive boundary and positive boundary has size added
		if (x_direction_ < 0)
		{
			// left = (old_left - width), right = old_left
			in_value_uq width = sub_func()(right, left);
			right = std::move(left);
			left = sub_func()(right, std::move(width));
		}
		else if (x_direction_ > 0)
		{
			// left = old_right, right = (old_right + width)
			in_value_uq width = sub_func()(right, left);
			left = std::move(right);
			right = add_func()(left, std::move(width));
		}

		if (y_direction_ < 0)
		{
			// top = (old_top - height), right = old_top
			in_value_uq height = sub_func()(bottom, top);
			bottom = std::move(top);
			top = sub_func()(bottom, std::move(height));
		}
		else if (y_direction_ > 0)
		{
			// top = old_bottom, bottom = (old_bottom + height)
			in_value_uq height = sub_func()(bottom, top);
			top = std::move(bottom);
			bottom = add_func()(top, std::move(height));
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

#endif
