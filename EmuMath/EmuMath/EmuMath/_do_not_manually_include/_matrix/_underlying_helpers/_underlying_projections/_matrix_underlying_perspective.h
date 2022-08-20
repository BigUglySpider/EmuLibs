#ifndef EMU_MATH_MATRIX_UNDERLYING_PROJECTION_PERSPECTIVE_H_INC_
#define EMU_MATH_MATRIX_UNDERLYING_PROJECTION_PERSPECTIVE_H_INC_ 1

#include "../_matrix_tmp.h"

namespace EmuMath::Helpers::_matrix_underlying
{
#pragma region GENERATION_COMPONENTS_VK_REVERSE_DEPTH
	template<std::size_t ColumnIndex_, std::size_t RowIndex_, class OutMatrix_, typename CalcFP_, typename AspectRatio_>
	[[nodiscard]] constexpr inline decltype(auto) _make_perspective_arg_vk_reverse_depth
	(
		AspectRatio_&& aspect_ratio_,
		const CalcFP_& out_22_,
		const CalcFP_& far_,
		const CalcFP_& focal_length_
	)
	{
		if constexpr (ColumnIndex_ == 0 && RowIndex_ == 0)
		{
			return EmuCore::do_divide<CalcFP_, CalcFP_>()(focal_length_, static_cast<CalcFP_>(std::forward<AspectRatio_>(aspect_ratio_)));
		}
		else if constexpr (ColumnIndex_ == 1 && RowIndex_ == 1)
		{
			return EmuCore::do_negate<CalcFP_>()(focal_length_);
		}
		else if constexpr (ColumnIndex_ == 2 && RowIndex_ == 2)
		{
			return out_22_;
		}
		else if constexpr (ColumnIndex_ == 2 && RowIndex_ == 3)
		{
			using out_mat_uq = typename EmuCore::TMP::remove_ref_cv<OutMatrix_>::type;
			return typename out_mat_uq::value_type_uq(-1);
		}
		else if constexpr (ColumnIndex_ == 3 && RowIndex_ == 2)
		{
			return EmuCore::do_multiply<CalcFP_, CalcFP_>()(far_, out_22_);
		}
		else
		{
			using out_mat_uq = typename EmuCore::TMP::remove_ref_cv<OutMatrix_>::type;
			return out_mat_uq::get_implied_zero();
		}
	}

	template<class OutMatrix_, typename FocalLength_, typename AspectRatio_, typename Near_, typename Far_, std::size_t...ColumnIndices_, std::size_t...RowIndices_>
	[[nodiscard]] constexpr inline OutMatrix_ _construct_perspective_matrix_vk_reverse_depth
	(
		AspectRatio_&& aspect_ratio_,
		Near_&& near_,
		Far_&& far_,
		FocalLength_&& focal_length_,
		std::index_sequence<ColumnIndices_...> column_indices_,
		std::index_sequence<RowIndices_...> row_indices_
	)
	{
		using focal_length_uq = typename EmuCore::TMP::remove_ref_cv<FocalLength_>::type;
		using aspect_ratio_uq = typename EmuCore::TMP::remove_ref_cv<AspectRatio_>::type;
		using near_uq = typename EmuCore::TMP::remove_ref_cv<Near_>::type;
		using far_uq = typename EmuCore::TMP::remove_ref_cv<Far_>::type;
		using out_uq = typename EmuCore::TMP::remove_ref_cv<OutMatrix_>::type;
		using out_fp = typename out_uq::preferred_floating_point;
		using calc_fp = typename EmuCore::TMP::largest_floating_point<out_fp, far_uq, near_uq, aspect_ratio_uq, focal_length_uq>::type;

		calc_fp out_22 = static_cast<calc_fp>(std::forward<Near_>(near_)); // near / (far - near); output for c2r2
		calc_fp far = static_cast<calc_fp>(std::forward<Far_>(far_));
		out_22 = EmuCore::do_divide<calc_fp, calc_fp>()(out_22, EmuCore::do_subtract<calc_fp, calc_fp>()(far, out_22));
		calc_fp focal_length = static_cast<calc_fp>(std::forward<FocalLength_>(focal_length_));

#pragma warning(push)
#pragma warning(disable: 26800)
		return OutMatrix_
		(
			_make_perspective_arg_vk_reverse_depth<ColumnIndices_, RowIndices_, OutMatrix_, calc_fp>
			(
				std::forward<AspectRatio_>(aspect_ratio_),
				out_22,
				far,
				focal_length 
			)...
		);
#pragma warning(pop)
	}

	template<class OutMatrix_, bool FovRads_, bool IsConstexpr_, typename FovY_, typename AspectRatio_, typename Near_, typename Far_>
	[[nodiscard]] constexpr inline OutMatrix_ _make_perspective_matrix_vk_reverse_depth
	(
		FovY_&& fov_y_,
		AspectRatio_&& aspect_ratio_,
		Near_&& near_,
		Far_&& far_
	)
	{
		using fov_uq = typename EmuCore::TMP::remove_ref_cv<FovY_>::type;
		using aspect_ratio_uq = typename EmuCore::TMP::remove_ref_cv<AspectRatio_>::type;
		using near_uq = typename EmuCore::TMP::remove_ref_cv<Near_>::type;
		using far_uq = typename EmuCore::TMP::remove_ref_cv<Far_>::type;
		using out_mat_uq = typename EmuCore::TMP::remove_ref_cv<OutMatrix_>::type;
		using out_fp = typename out_mat_uq::preferred_floating_point;
		using calc_fp = typename EmuCore::TMP::largest_floating_point<out_fp, far_uq, near_uq, aspect_ratio_uq, fov_uq>::type;

		calc_fp focal_length = static_cast<calc_fp>(std::forward<FovY_>(fov_y_)); // focal_length = 1 / tan(fov_y_rads / 2)
		if constexpr (!FovRads_)
		{
			focal_length = EmuCore::Pi::DegsToRads<calc_fp>(focal_length);
		}
		using tan_func = typename std::conditional<IsConstexpr_, EmuCore::do_tan_constexpr<calc_fp>, EmuCore::do_tan<calc_fp>>::type;
		using div_func = EmuCore::do_divide<calc_fp, calc_fp>;
		focal_length = div_func()(calc_fp(1), tan_func()(div_func()(focal_length, calc_fp(2))));


		using out_indices = EmuMath::TMP::make_full_matrix_index_sequences<out_mat_uq>;
		using column_index_sequence = typename out_indices::column_index_sequence;
		using row_index_sequence = typename out_indices::row_index_sequence;
		return _construct_perspective_matrix_vk_reverse_depth<OutMatrix_>
		(
			std::forward<AspectRatio_>(aspect_ratio_),
			std::forward<Near_>(near_),
			std::forward<Far_>(far_),
			focal_length,
			column_index_sequence(),
			row_index_sequence()
		);
	}
#pragma endregion

#pragma region GENERATION_COMPONENTS_VK
	template<std::size_t ColumnIndex_, std::size_t RowIndex_, typename CalcFP_, EmuMath::TMP::EmuMatrix OutMatrix_>
	[[nodiscard]] constexpr inline decltype(auto) _make_perspective_arg_vk
	(
		const CalcFP_& aspect_ratio_,
		const CalcFP_& near_,
		const CalcFP_& far_,
		const CalcFP_& focal_length_
	)
	{
		using sub_func = EmuCore::do_subtract<CalcFP_, CalcFP_>;
		using mul_func = EmuCore::do_multiply<CalcFP_, CalcFP_>;
		using div_func = EmuCore::do_divide<CalcFP_, CalcFP_>;

		if constexpr (ColumnIndex_ == 0 && RowIndex_ == 0)
		{
			return div_func()(CalcFP_(1), mul_func()(aspect_ratio_, focal_length_));
		}
		else if constexpr (ColumnIndex_ == 1 && RowIndex_ == 1)
		{
			return div_func()(CalcFP_(1), focal_length_);
		}
		else if constexpr (ColumnIndex_ == 2 && RowIndex_ == 2)
		{
			return div_func()(far_, sub_func()(near_, far_));
		}
		else if constexpr (ColumnIndex_ == 2 && RowIndex_ == 3)
		{
			using out_mat_uq = typename EmuCore::TMP::remove_ref_cv<OutMatrix_>::type;
			return typename out_mat_uq::value_type_uq(-1);
		}
		else if constexpr (ColumnIndex_ == 3 && RowIndex_ == 2)
		{
			using negate_func = EmuCore::do_negate<CalcFP_>;
			return div_func()(negate_func()(mul_func()(far_, near_)), sub_func()(far_, near_));
		}
		else
		{
			using out_mat_uq = typename EmuCore::TMP::remove_ref_cv<OutMatrix_>::type;
			return out_mat_uq::get_implied_zero();
		}
	}

	template<class OutMatrix_, typename FocalLength_, typename AspectRatio_, typename Near_, typename Far_, std::size_t...ColumnIndices_, std::size_t...RowIndices_>
	[[nodiscard]] constexpr inline OutMatrix_ _construct_perspective_matrix_vk
	(
		AspectRatio_&& aspect_ratio_,
		Near_&& near_,
		Far_&& far_,
		FocalLength_&& focal_length_,
		std::index_sequence<ColumnIndices_...> column_indices_,
		std::index_sequence<RowIndices_...> row_indices_
	)
	{
		using focal_length_uq = typename EmuCore::TMP::remove_ref_cv<FocalLength_>::type;
		using aspect_ratio_uq = typename EmuCore::TMP::remove_ref_cv<AspectRatio_>::type;
		using near_uq = typename EmuCore::TMP::remove_ref_cv<Near_>::type;
		using far_uq = typename EmuCore::TMP::remove_ref_cv<Far_>::type;
		using out_uq = typename EmuCore::TMP::remove_ref_cv<OutMatrix_>::type;
		using out_fp = typename out_uq::preferred_floating_point;
		using calc_fp = typename EmuCore::TMP::largest_floating_point<out_fp, far_uq, near_uq, aspect_ratio_uq, focal_length_uq>::type;

		calc_fp aspect_ratio = static_cast<calc_fp>(std::forward<AspectRatio_>(aspect_ratio_));
		calc_fp near = static_cast<calc_fp>(std::forward<Near_>(near_));
		calc_fp far = static_cast<calc_fp>(std::forward<Far_>(far_));
		calc_fp focal_length = static_cast<calc_fp>(std::forward<FocalLength_>(focal_length_));



		return OutMatrix_
		(
			_make_perspective_arg_vk<ColumnIndices_, RowIndices_, calc_fp, OutMatrix_>
			(
				aspect_ratio,
				near,
				far,
				focal_length
			)...
		);
	}

	template<class OutMatrix_, bool FovRads_, bool IsConstexpr_, typename FovY_, typename AspectRatio_, typename Near_, typename Far_>
	[[nodiscard]] constexpr inline OutMatrix_ _make_perspective_matrix_vk
	(
		FovY_&& fov_y_,
		AspectRatio_&& aspect_ratio_,
		Near_&& near_,
		Far_&& far_
	)
	{
		using fov_uq = typename EmuCore::TMP::remove_ref_cv<FovY_>::type;
		using aspect_ratio_uq = typename EmuCore::TMP::remove_ref_cv<AspectRatio_>::type;
		using near_uq = typename EmuCore::TMP::remove_ref_cv<Near_>::type;
		using far_uq = typename EmuCore::TMP::remove_ref_cv<Far_>::type;
		using out_mat_uq = typename EmuCore::TMP::remove_ref_cv<OutMatrix_>::type;
		using out_fp = typename out_mat_uq::preferred_floating_point;
		using calc_fp = typename EmuCore::TMP::largest_floating_point<out_fp, far_uq, near_uq, aspect_ratio_uq, fov_uq>::type;

		calc_fp focal_length = static_cast<calc_fp>(std::forward<FovY_>(fov_y_)); // focal_length = 1 / tan(fov_y_rads / 2)
		if constexpr (!FovRads_)
		{
			focal_length = EmuCore::Pi::DegsToRads<calc_fp>(focal_length);
		}
		using tan_func = typename std::conditional<IsConstexpr_, EmuCore::do_tan_constexpr<calc_fp>, EmuCore::do_tan<calc_fp>>::type;
		using div_func = EmuCore::do_divide<calc_fp, calc_fp>;
		focal_length = tan_func()(div_func()(focal_length, calc_fp(2)));

		using out_indices = EmuMath::TMP::make_full_matrix_index_sequences<out_mat_uq>;
		using column_index_sequence = typename out_indices::column_index_sequence;
		using row_index_sequence = typename out_indices::row_index_sequence;
		return _construct_perspective_matrix_vk<OutMatrix_>
		(
			std::forward<AspectRatio_>(aspect_ratio_),
			std::forward<Near_>(near_),
			std::forward<Far_>(far_),
			focal_length,
			column_index_sequence(),
			row_index_sequence()
		);
	}
#pragma endregion
}

#endif