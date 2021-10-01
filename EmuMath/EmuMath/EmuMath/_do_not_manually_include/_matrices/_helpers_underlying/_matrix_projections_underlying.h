#ifndef EMU_MATH__UNDERLYING_MATRIX_PROJECTIONS_H_INC_
#define EMU_MATH__UNDERLYING_MATRIX_PROJECTIONS_H_INC_ 1

#include "_common_underlying_matrix_helper_includes.h"
#include "_matrix_gets_underlying.h"
#include "_matrix_sets_underlying.h"

namespace EmuMath::Helpers::_underlying_matrix_funcs
{
	/// <summary> Calculates cofactor a from the provided near_ and far_ values, which will be the result of -(far / (far - near)). </summary>
	/// <typeparam name="Near_">Type used to provide the near_ argument.</typeparam>
	/// <typeparam name="Far_">Type used to provided the far_ argument.</typeparam>
	/// <typeparam name="Out_">Type to output the cofactor as.</typeparam>
	/// <param name="near_">Near value when creating the normalisation cofactor.</param>
	/// <param name="far_">Far value when creating the normalisation cofactor.</param>
	/// <returns>Result of -(far / (far - near)).</returns>
	template<typename Near_, typename Far_, typename Out_>
	[[nodiscard]] constexpr inline Out_ _calculate_basic_perspective_near_far_cofactor_a(const Near_& near_, const Far_& far_)
	{
		auto far_sub_near = EmuCore::do_subtract<Far_, Near_>()(far_, near_);
		auto out_ = EmuCore::do_divide<Far_, decltype(far_sub_near)>()(far_, far_sub_near);
		return static_cast<Out_>(EmuCore::do_negate<decltype(out_)>()(out_));
	}

	/// <summary> Calculates cofactor b from the provided near_ and far_ values, which will be the result of -((far * near) / (far - near)). </summary>
	/// <typeparam name="Near_">Type used to provide the near_ argument.</typeparam>
	/// <typeparam name="Far_">Type used to provided the far_ argument.</typeparam>
	/// <typeparam name="Out_">Type to output the cofactor as.</typeparam>
	/// <param name="near_">Near value when creating the normalisation cofactor.</param>
	/// <param name="far_">Far value when creating the normalisation cofactor.</param>
	/// <returns>Result of -((f * n) / (f - n)).</returns>
	template<typename Near_, typename Far_, typename Out_>
	[[nodiscard]] constexpr inline Out_ _calculate_basic_perspective_near_far_cofactor_b(const Near_& near_, const Far_& far_)
	{
		auto far_sub_near = EmuCore::do_subtract<Far_, Near_>()(far_, near_);
		auto far_mult_near_ = EmuCore::do_multiply<Far_, Near_>()(far_, near_);
		auto out_ = EmuCore::do_divide<decltype(far_mult_near_), decltype(far_sub_near)>()(far_mult_near_, far_sub_near);
		return static_cast<Out_>(EmuCore::do_negate<decltype(out_)>()(out_));
	}

	/// <summary> Calculates the FOV scale for a perspective projection matrix with the provided FOV. </summary>
	/// <typeparam name="Fov_">Type used to represent the passed FOV.</typeparam>
	/// <typeparam name="Out_">Type to output the scale as.</typeparam>
	/// <param name="fov_">FOV to use for the scale calculation, measured in radians.</param>
	/// <returns>Result of 1 / tan((fov_ / 2)). </returns>
	template<std::size_t NumIterations_, typename Fov_, typename Out_>
	[[nodiscard]] constexpr inline Out_ _calculate_basic_perspective_fov_scale_rads(const Fov_& fov_rads_)
	{
		using floating_point = EmuCore::TMPHelpers::first_floating_point_t<Fov_, Out_, float>;
		constexpr floating_point one_ = floating_point(1);
		constexpr floating_point half_ = floating_point(0.5);

		using Mul_ = EmuCore::do_multiply<floating_point, floating_point>;
		using Div_ = EmuCore::do_divide<floating_point, floating_point>;
		using Tan_ = EmuCore::do_tan_constexpr<floating_point, NumIterations_, true>;

		floating_point out_ = Mul_()(fov_rads_, half_);
		out_ = Tan_()(out_);
		return Div_()(one_, out_);
	}

	template<std::size_t NumIterations_, class Matrix_, typename Near_, typename Far_, typename Fov_>
	[[nodiscard]] constexpr inline Matrix_ _make_basic_perspective_projection_matrix_rads(const Near_& near_, const Far_& far_, const Fov_& fov_rads_)
	{
		using out_value = typename Matrix_::value_type;

		Matrix_ out_ = Matrix_();
		out_value scale_ = _calculate_basic_perspective_fov_scale_rads<NumIterations_, Fov_, out_value>(fov_rads_);
		_get_matrix_data<0, 0>(out_) = scale_;
		_get_matrix_data<1, 1>(out_) = scale_;
		_get_matrix_data<2, 2>(out_) = _calculate_basic_perspective_near_far_cofactor_a<Near_, Far_, out_value>(near_, far_);
		_get_matrix_data<3, 2>(out_) = _calculate_basic_perspective_near_far_cofactor_b<Near_, Far_, out_value>(near_, far_);
		_get_matrix_data<2, 3>(out_) = out_value(-1);

		return out_;
	}

	template<typename Out_, typename FovYRads_, typename Near_, typename CalcType_, class Tan_>
	[[nodiscard]] constexpr inline Out_ _calculate_matrix_perspective_projection_scale_rads(const FovYRads_& fov_angle_y_rads_, const Near_& near_)
	{
		using Mul_ = EmuCore::do_multiply<CalcType_, CalcType_>;
		Mul_ mul_ = Mul_();
		CalcType_ out_ = static_cast<CalcType_>(fov_angle_y_rads_);
		out_ = mul_(out_, CalcType_(0.5));
		out_ = static_cast<CalcType_>(Tan_()(out_));
		out_ = mul_(out_, static_cast<CalcType_>(near_));
		return static_cast<Out_>(out_);
	}

	template<typename Out_, typename Scale_>
	[[nodiscard]] constexpr inline Out_ _calculate_matrix_perspective_edge_top_rads(const Scale_& scale_)
	{
		return static_cast<Out_>(scale_);
	}
	template<typename Out_, typename FovYRads_, typename Near_, typename CalcType_, class Tan_>
	[[nodiscard]] constexpr inline Out_ _calculate_matrix_perspective_edge_top_rads(const FovYRads_& fov_angle_y_rads_, const Near_& near_)
	{
		return _calculate_matrix_perspective_edge_top_rads<Out_, CalcType_>
		(
			_calculate_matrix_perspective_projection_scale_rads<CalcType_, FovYRads_, Near_, CalcType_, Tan_>(fov_angle_y_rads_, near_)
		);
	}

	template<typename Out_, typename Scale_>
	[[nodiscard]] constexpr inline Out_ _calculate_matrix_perspective_edge_bottom_rads(const Scale_& scale_)
	{
		return EmuCore::do_negate<Out_>()
		(
			_calculate_matrix_perspective_edge_top_rads<Out_, Scale_>(scale_)
		);
	}
	template<typename Out_, typename FovYRads_, typename Near_, typename CalcType_, class Tan_>
	[[nodiscard]] constexpr inline Out_ _calculate_matrix_perspective_edge_bottom_rads(const FovYRads_& fov_angle_y_rads_, const Near_& near_)
	{
		return _calculate_matrix_perspective_edge_bottom_rads<Out_, CalcType_>
		(
			_calculate_matrix_perspective_projection_scale_rads<CalcType_, FovYRads_, Near_, CalcType_, Tan_>(fov_angle_y_rads_, near_)
		);
	}

	template<typename Out_, typename AspectRatio_, typename Scale_>
	[[nodiscard]] constexpr inline Out_ _calculate_matrix_perspective_edge_right_rads(const AspectRatio_& aspect_ratio_, const Scale_& scale_)
	{
		if constexpr (std::is_floating_point_v<AspectRatio_> && std::is_floating_point_v<Scale_>)
		{
			return static_cast<Out_>(EmuCore::do_multiply<AspectRatio_, Scale_>()(aspect_ratio_, scale_));
		}
		else
		{
			using floating_point = EmuCore::TMPHelpers::first_floating_point_t<Out_, AspectRatio_, Scale_, float>;
			return static_cast<Out_>
			(
				EmuCore::do_multiply<floating_point, floating_point>()
				(
					static_cast<floating_point>(aspect_ratio_),
					static_cast<floating_point>(scale_)
				)
			);
		}
	}
	template<typename Out_, typename FovYRads_, typename Near_, typename AspectRatio_, typename CalcType_, class Tan_>
	[[nodiscard]] constexpr inline Out_ _calculate_matrix_perspective_edge_right_rads(const FovYRads_& fov_angle_y_rads_, const Near_& near_, const AspectRatio_& aspect_ratio_)
	{
		return _calculate_matrix_perspective_edge_right_rads<Out_, AspectRatio_, CalcType_>
		(
			aspect_ratio_,
			_calculate_matrix_perspective_projection_scale_rads<CalcType_, FovYRads_, Near_, CalcType_, Tan_>(fov_angle_y_rads_, near_)
		);
	}

	template<typename Out_, typename AspectRatio_, typename Scale_>
	[[nodiscard]] constexpr inline Out_ _calculate_matrix_perspective_edge_left_rads(const AspectRatio_& aspect_ratio_, const Scale_& scale_)
	{
		return EmuCore::do_negate<Out_>()
		(
			_calculate_matrix_perspective_edge_right_rads<Out_, Scale_>(aspect_ratio_, scale_)
		);
	}
	template<typename Out_, typename FovYRads_, typename Near_, typename AspectRatio_, typename CalcType_, class Tan_>
	[[nodiscard]] constexpr inline Out_ _calculate_matrix_perspective_edge_left_rads(const FovYRads_& fov_angle_y_rads_, const Near_& near_, const AspectRatio_& aspect_ratio_)
	{
		return _calculate_matrix_perspective_edge_left_rads<Out_, AspectRatio_, CalcType_>
		(
			aspect_ratio_,
			_calculate_matrix_perspective_projection_scale_rads<CalcType_, FovYRads_, Near_, CalcType_, Tan_>(fov_angle_y_rads_, near_)
		);
	}

	template<typename AspectRatio_, typename Scale_, typename OutLeft_, typename OutRight_, typename OutBottom_, typename OutTop_, typename CalcType_>
	constexpr inline void _calculate_matrix_perspective_edges_rads
	(
		const AspectRatio_& aspect_ratio_,
		const Scale_& scale_,
		OutLeft_& out_left_,
		OutRight_& out_right_,
		OutBottom_& out_bottom_,
		OutTop_& out_top_
	)
	{
		out_right_ = _calculate_matrix_perspective_edge_right_rads<OutRight_, AspectRatio_, CalcType_>(aspect_ratio_, scale_);
		out_left_ = _calculate_matrix_perspective_edge_left_rads<OutLeft_, AspectRatio_, CalcType_>(aspect_ratio_, scale_);
		out_top_ = _calculate_matrix_perspective_edge_top_rads<OutTop_, CalcType_>(scale_);
		out_bottom_ = _calculate_matrix_perspective_edge_bottom_rads<OutBottom_, CalcType_>(scale_);
	}
	template
	<
		typename FovYRads_,
		typename Near_,
		typename AspectRatio_,
		typename OutLeft_,
		typename OutRight_,
		typename OutBottom_,
		typename OutTop_,
		typename CalcType,
		class Tan_
	>
	constexpr inline void _calculate_matrix_perspective_edges_rads
	(
		const FovYRads_& fov_angle_y_rads_,
		const Near_& near_,
		const AspectRatio_& aspect_ratio_,
		OutLeft_& out_left_,
		OutRight_& out_right_,
		OutBottom_& out_bottom_,
		OutTop_& out_top_
	)
	{
		CalcType scale_ = _calculate_matrix_perspective_projection_scale_rads<CalcType, FovYRads_, Near_, CalcType, Tan_>(fov_angle_y_rads_, near_);
		_calculate_matrix_perspective_edges_rads<AspectRatio_, CalcType, OutLeft_, OutRight_, OutBottom_, OutTop_, CalcType>
		(
			aspect_ratio_,
			scale_,
			out_left_,
			out_right_,
			out_bottom_,
			out_top_
		);
	}

	template<class OutMatrix_, typename Near_, typename Far_, typename Left_, typename Right_, typename Bottom_, typename Top_, typename CalcType_>
	[[nodiscard]] constexpr inline OutMatrix_ _make_perspective_matrix_with_frustum_rads_gl
	(
		const Near_& near_,
		const Far_& far_,
		const Left_& left_,
		const Right_& right_,
		const Bottom_& bottom_,
		const Top_& top_
	)
	{
		// Create arithmetic functors ready to call later on
		using Add_ = EmuCore::do_add<CalcType_, CalcType_>;
		using Sub_ = EmuCore::do_subtract<CalcType_, CalcType_>;
		using Mul_ = EmuCore::do_multiply<CalcType_, CalcType_>;
		using Div_ = EmuCore::do_divide<CalcType_, CalcType_>;
		using Negate_ = EmuCore::do_negate<CalcType_>;
		Add_ add_ = Add_();
		Sub_ sub_ = Sub_();
		Mul_ mul_ = Mul_();
		Div_ div_ = Div_();
		Negate_ negate_ = Negate_();
		
		// Calculate common constants to be used more than once throughout calculations
		CalcType_ near_calc_cast_ = static_cast<CalcType_>(near_);
		CalcType_ far_calc_cast_ = static_cast<CalcType_>(far_);
		CalcType_ one_ = CalcType_(1);
		CalcType_ two_ = CalcType_(2);
		
		CalcType_ right_minus_left_reciprocal_ = div_(one_, sub_(right_, left_));
		CalcType_ top_minus_bottom_reciprocal_ = div_(one_, sub_(top_, bottom_));
		CalcType_ double_near_ = mul_(near_calc_cast_, two_);
		CalcType_ far_minus_near_reciprocal_neg = negate_(div_(one_, sub_(far_calc_cast_, near_calc_cast_)));
		
		// Fill the matrix
		using out_value = typename OutMatrix_::value_type;
		OutMatrix_ out_ = OutMatrix_();
		// Column 0
		_get_matrix_data<0, 0>(out_) = static_cast<out_value>(mul_(double_near_, right_minus_left_reciprocal_)); // (2*near)/(right-left)
		// Columnn 1
		_get_matrix_data<1, 1>(out_) = static_cast<out_value>(mul_(double_near_, top_minus_bottom_reciprocal_)); // (2*near)/(top-bottom)
		// Column 2
		_get_matrix_data<2, 0>(out_) = static_cast<out_value>(mul_(add_(right_, left_), right_minus_left_reciprocal_)); // (right+left)/(right-left)
		_get_matrix_data<2, 1>(out_) = static_cast<out_value>(mul_(add_(top_, bottom_), top_minus_bottom_reciprocal_)); // (top+bottom)/(top-bottom)
		_get_matrix_data<2, 2>(out_) = static_cast<out_value>(mul_(add_(far_calc_cast_, near_calc_cast_), far_minus_near_reciprocal_neg)); // -((far+near)/(far-near))
		_get_matrix_data<2, 3>(out_) = out_value(-1);
		// Column 3
		_get_matrix_data<3, 2>(out_) = static_cast<out_value>
		(
			mul_
			(
				mul_
				(
					mul_(two_, far_calc_cast_),
					near_calc_cast_
				),
				far_minus_near_reciprocal_neg
			)
		); // -((2*far*near)/(far-near))
		return out_;
	}
	template<class OutMatrix_, typename FovYRads_, typename Near_, typename Far_, typename AspectRatio_, typename CalcType_, class Tan_>
	[[nodiscard]] constexpr inline OutMatrix_ _make_perspective_matrix_with_frustum_rads_gl
	(
		const FovYRads_& fov_angle_y_rads_,
		const Near_& near_,
		const Far_& far_,
		const AspectRatio_& aspect_ratio_
	)
	{
		// Calculate frustum edges
		CalcType_ scale_ = _calculate_matrix_perspective_projection_scale_rads<CalcType_, FovYRads_, Near_, CalcType_, Tan_>(fov_angle_y_rads_, near_);
		CalcType_ right_ = CalcType_();
		CalcType_ left_ = CalcType_();
		CalcType_ top_ = CalcType_();
		CalcType_ bottom_ = CalcType_();
		_calculate_matrix_perspective_edges_rads<AspectRatio_, CalcType_, CalcType_, CalcType_, CalcType_, CalcType_, CalcType_>
		(
			aspect_ratio_,
			scale_,
			left_,
			right_,
			bottom_,
			top_
		);
		return _make_perspective_matrix_with_frustum_rads_gl<OutMatrix_, Near_, Far_, CalcType_, CalcType_, CalcType_, CalcType_, CalcType_>
		(
			near_,
			far_,
			left_,
			right_,
			bottom_,
			top_
		);
	}

	template<class OutMatrix_, typename Near_, typename Far_, typename Left_, typename Right_, typename Bottom_, typename Top_, typename CalcType_>
	[[nodiscard]] constexpr inline OutMatrix_ _make_perspective_matrix_with_frustum_rads_vk
	(
		const Near_& near_,
		const Far_& far_,
		const Left_& left_,
		const Right_& right_,
		const Bottom_& bottom_,
		const Top_& top_
	)
	{
		// Create arithmetic functors ready to call later on
		using Add_ = EmuCore::do_add<CalcType_, CalcType_>;
		using Sub_ = EmuCore::do_subtract<CalcType_, CalcType_>;
		using Mul_ = EmuCore::do_multiply<CalcType_, CalcType_>;
		using Div_ = EmuCore::do_divide<CalcType_, CalcType_>;
		using Negate_ = EmuCore::do_negate<CalcType_>;
		Add_ add_ = Add_();
		Sub_ sub_ = Sub_();
		Mul_ mul_ = Mul_();
		Div_ div_ = Div_();
		Negate_ negate_ = Negate_();
		
		// Calculate common constants to be used more than once throughout calculations
		CalcType_ near_calc_cast_ = static_cast<CalcType_>(near_);
		CalcType_ far_calc_cast_ = static_cast<CalcType_>(far_);
		CalcType_ one_ = CalcType_(1);
		CalcType_ two_ = CalcType_(2);
		
		CalcType_ right_minus_left_reciprocal_ = div_(one_, sub_(right_, left_));
		CalcType_ top_minus_bottom_reciprocal_ = div_(one_, sub_(top_, bottom_));
		CalcType_ double_near_ = mul_(near_calc_cast_, two_);
		CalcType_ far_minus_near_reciprocal_neg = negate_(div_(one_, sub_(far_calc_cast_, near_calc_cast_)));
		
		// Fill the matrix
		using out_value = typename OutMatrix_::value_type;
		OutMatrix_ out_ = OutMatrix_();
		// Column 0
		_get_matrix_data<0, 0>(out_) = static_cast<out_value>(mul_(double_near_, right_minus_left_reciprocal_)); // (2*near)/(right-left)
		// Columnn 1
		_get_matrix_data<1, 1>(out_) = static_cast<out_value>(mul_(double_near_, top_minus_bottom_reciprocal_)); // (2*near)/(top-bottom)
		// Column 2
		_get_matrix_data<2, 0>(out_) = static_cast<out_value>(mul_(add_(right_, left_), right_minus_left_reciprocal_)); // (right+left)/(right-left)
		_get_matrix_data<2, 1>(out_) = static_cast<out_value>(mul_(add_(top_, bottom_), top_minus_bottom_reciprocal_)); // (top+bottom)/(top-bottom)
		//_get_matrix_data<2, 2>(out_) = static_cast<out_value>(mul_(add_(far_calc_cast_, near_calc_cast_), far_minus_near_reciprocal_neg)); // -((far+near)/(far-near))
		_get_matrix_data<2, 2>(out_) = static_cast<out_value>(mul_(far_calc_cast_, far_minus_near_reciprocal_neg)); // -(far/(far-near))
		_get_matrix_data<2, 3>(out_) = out_value(-1);
		// Column 3
		_get_matrix_data<3, 2>(out_) = static_cast<out_value>(mul_(mul_(far_calc_cast_, near_calc_cast_), far_minus_near_reciprocal_neg)); // -((far*near)/(far-near))
		return out_;
	}
	template<class OutMatrix_, typename FovYRads_, typename Near_, typename Far_, typename AspectRatio_, typename CalcType_, class Tan_>
	[[nodiscard]] constexpr inline OutMatrix_ _make_perspective_matrix_with_frustum_rads_vk
	(
		const FovYRads_& fov_angle_y_rads_,
		const Near_& near_,
		const Far_& far_,
		const AspectRatio_& aspect_ratio_
	)
	{
		// Calculate frustum edges
		CalcType_ scale_ = _calculate_matrix_perspective_projection_scale_rads<CalcType_, FovYRads_, Near_, CalcType_, Tan_>(fov_angle_y_rads_, near_);
		CalcType_ right_ = CalcType_();
		CalcType_ left_ = CalcType_();
		CalcType_ top_ = CalcType_();
		CalcType_ bottom_ = CalcType_();
		_calculate_matrix_perspective_edges_rads<AspectRatio_, CalcType_, CalcType_, CalcType_, CalcType_, CalcType_, CalcType_>
		(
			aspect_ratio_,
			scale_,
			left_,
			right_,
			bottom_,
			top_
		);
		return _make_perspective_matrix_with_frustum_rads_vk<OutMatrix_, Near_, Far_, CalcType_, CalcType_, CalcType_, CalcType_, CalcType_>
		(
			near_,
			far_,
			left_,
			right_,
			bottom_,
			top_
		);
	}

	template<class OutMatrix_, typename Left_, typename Right_, typename Bottom_, typename Top_, typename Near_, typename Far_, typename CalcType_>
	[[nodiscard]] constexpr inline OutMatrix_ _make_orthograhpic_projection_matrix_gl
	(
		const Left_& left_,
		const Right_& right_,
		const Bottom_& bottom_,
		const Top_& top_,
		const Near_& near_,
		const Far_& far_
	)
	{
		// Arithmetic Functors
		using Add_ = EmuCore::do_add<CalcType_, CalcType_>;
		using Sub_ = EmuCore::do_subtract<CalcType_, CalcType_>;
		using Mul_ = EmuCore::do_multiply<CalcType_, CalcType_>;
		using Div_ = EmuCore::do_divide<CalcType_, CalcType_>;
		using Negate_ = EmuCore::do_negate<CalcType_>;
		Add_ add_ = Add_();
		Sub_ sub_ = Sub_();
		Mul_ mul_ = Mul_();
		Div_ div_ = Div_();
		Negate_ negate_ = Negate_();

		// Calculate common constants
		CalcType_ left_calc_cast_ = static_cast<CalcType_>(left_);
		CalcType_ right_calc_cast_ = static_cast<CalcType_>(right_);
		CalcType_ bottom_calc_cast_ = static_cast<CalcType_>(bottom_);
		CalcType_ top_calc_cast_ = static_cast<CalcType_>(top_);
		CalcType_ near_calc_cast_ = static_cast<CalcType_>(near_);
		CalcType_ far_calc_cast_ = static_cast<CalcType_>(far_);
		CalcType_ two_ = CalcType_(2);

		CalcType_ right_minus_left_ = sub_(right_calc_cast_, left_calc_cast_);
		CalcType_ top_minus_bottom_ = sub_(top_calc_cast_, bottom_calc_cast_);
		CalcType_ far_minus_near_reciprocal = div_(CalcType_(1), sub_(far_calc_cast_, near_calc_cast_));

		// Fill matrix
		using out_value = typename OutMatrix_::value_type;
		OutMatrix_ out_ = OutMatrix_();
		// Column 0
		_get_matrix_data<0, 0>(out_) = static_cast<out_value>(div_(two_, right_minus_left_)); // 2/(right-left)
		_get_matrix_data<0, 3>(out_) = static_cast<out_value>
		(
			negate_
			(
				div_
				(
					add_(right_calc_cast_, left_calc_cast_),
					right_minus_left_
				)
			)
		); // -((right+left)/(right-left))
		// Column 1
		_get_matrix_data<1, 1>(out_) = static_cast<out_value>(div_(two_, top_minus_bottom_));
		_get_matrix_data<1, 3>(out_) = static_cast<out_value>
		(
			negate_
			(
				div_
				(
					add_(top_calc_cast_, bottom_calc_cast_),
					top_minus_bottom_
				)
			)
		); // -((top+bottom)/(top-bottom))
		// Column 2
		_get_matrix_data<2, 2>(out_) = static_cast<out_value>(mul_(CalcType_(-2), far_minus_near_reciprocal)); // (-2)/(far-near)
		_get_matrix_data<2, 3>(out_) = static_cast<out_value>
		(
			negate_
			(
				mul_
				(
					add_(far_calc_cast_, near_calc_cast_),
					far_minus_near_reciprocal
				)
			)
		); // -((far+near)/(far-near))
		// Column 3
		_get_matrix_data<3, 3>(out_) = out_value(1);
		return out_;
	}

	template<class OutMatrix_, typename Left_, typename Right_, typename Bottom_, typename Top_, typename Near_, typename Far_, typename CalcType_>
	[[nodiscard]] constexpr inline OutMatrix_ _make_orthograhpic_projection_matrix_vk
	(
		const Left_& left_,
		const Right_& right_,
		const Bottom_& bottom_,
		const Top_& top_,
		const Near_& near_,
		const Far_& far_
	)
	{
		// Arithmetic Functors
		using Add_ = EmuCore::do_add<CalcType_, CalcType_>;
		using Sub_ = EmuCore::do_subtract<CalcType_, CalcType_>;
		using Mul_ = EmuCore::do_multiply<CalcType_, CalcType_>;
		using Div_ = EmuCore::do_divide<CalcType_, CalcType_>;
		using Negate_ = EmuCore::do_negate<CalcType_>;
		Add_ add_ = Add_();
		Sub_ sub_ = Sub_();
		Mul_ mul_ = Mul_();
		Div_ div_ = Div_();
		Negate_ negate_ = Negate_();

		// Calculate common constants
		CalcType_ left_calc_cast_ = static_cast<CalcType_>(left_);
		CalcType_ right_calc_cast_ = static_cast<CalcType_>(right_);
		CalcType_ bottom_calc_cast_ = static_cast<CalcType_>(bottom_);
		CalcType_ top_calc_cast_ = static_cast<CalcType_>(top_);
		CalcType_ near_calc_cast_ = static_cast<CalcType_>(near_);
		CalcType_ far_calc_cast_ = static_cast<CalcType_>(far_);
		CalcType_ one_ = CalcType_(1);
		CalcType_ two_ = CalcType_(2);

		CalcType_ right_minus_left_ = sub_(right_calc_cast_, left_calc_cast_);
		CalcType_ top_minus_bottom_ = sub_(top_calc_cast_, bottom_calc_cast_);
		CalcType_ far_minus_near_reciprocal = div_(one_, sub_(far_calc_cast_, near_calc_cast_));

		// Fill matrix
		using out_value = typename OutMatrix_::value_type;
		OutMatrix_ out_ = OutMatrix_();
		// Column 0
		_get_matrix_data<0, 0>(out_) = static_cast<out_value>(div_(two_, right_minus_left_));
		// Column 1
		_get_matrix_data<1, 1>(out_) = static_cast<out_value>(div_(two_, top_minus_bottom_));
		// Column 2
		_get_matrix_data<2, 2>(out_) = static_cast<out_value>(negate_(far_minus_near_reciprocal));
		// Column 3
		//_get_matrix_data<3, 0>(out_) = static_cast<out_value>(div_(negate_(add_(right_calc_cast_, left_calc_cast_)), right_minus_left_));
		//_get_matrix_data<3, 1>(out_) = static_cast<out_value>(div_(negate_(add_(top_calc_cast_, bottom_calc_cast_)), top_minus_bottom_));
		_get_matrix_data<3, 2>(out_) = static_cast<out_value>(mul_(negate_(near_calc_cast_), far_minus_near_reciprocal));
		_get_matrix_data<3, 3>(out_) = out_value(1);

		return out_;
	}
}

#endif
