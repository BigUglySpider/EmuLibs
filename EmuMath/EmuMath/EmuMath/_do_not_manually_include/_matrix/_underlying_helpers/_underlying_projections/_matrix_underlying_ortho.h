#ifndef EMU_MATH_MATRIX_UNDERLYING_PROJECTION_ORTHO_H_INC_
#define EMU_MATH_MATRIX_UNDERLYING_PROJECTION_ORTHO_H_INC_ 1

#include "../_matrix_tmp.h"

namespace EmuMath::Helpers::_matrix_underlying
{
#pragma region GENERATION_COMPONENTS_VK_ORTHO
	template
	<
		std::size_t ColumnIndex_, std::size_t RowIndex_, EmuMath::TMP::EmuMatrix OutMatrix_,
		typename Out00_, typename Out11_, typename Out22_, typename Out30_, typename Out31_, typename Out32_
	>
	[[nodiscard]] constexpr inline decltype(auto) _make_orth_vk_arg_for_index
	(
		Out00_&& out_00_,
		Out11_&& out_11_,
		Out22_&& out_22_,
		Out30_&& out_30_,
		Out31_&& out_31_,
		Out32_&& out_32_
	)
	{
		if constexpr (ColumnIndex_ == 0 && RowIndex_ == 0)
		{
			return std::forward<Out00_>(out_00_);
		}
		else if constexpr (ColumnIndex_ == 1 && RowIndex_ == 1)
		{
			return std::forward<Out11_>(out_11_);
		}
		else if constexpr (ColumnIndex_ == 2 && RowIndex_ == 2)
		{
			return std::forward<Out22_>(out_22_);
		}
		else if constexpr (ColumnIndex_ == 3)
		{
			if constexpr (RowIndex_ == 0)
			{
				return std::forward<Out30_>(out_30_);
			}
			else if constexpr (RowIndex_ == 1)
			{
				return std::forward<Out31_>(out_31_);
			}
			else if constexpr (RowIndex_ == 2)
			{
				return std::forward<Out32_>(out_32_);
			}
			else if constexpr (RowIndex_ == 3)
			{
				using out_mat_uq = typename EmuCore::TMP::remove_ref_cv<OutMatrix_>::type;
				return typename out_mat_uq::value_type_uq(1);
			}
		}
		else if constexpr (ColumnIndex_ == RowIndex_)
		{
			// All 1 on remaining main diagonal
			using out_mat_uq = typename EmuCore::TMP::remove_ref_cv<OutMatrix_>::type;
			return typename out_mat_uq::value_type_uq(1);
		}
		else
		{
			// All zero elsewhere
			using out_mat_uq = typename EmuCore::TMP::remove_ref_cv<OutMatrix_>::type;
			return out_mat_uq::get_implied_zero();
		}
	}

	template
	<
		typename CalcType_, EmuMath::TMP::EmuMatrix OutMatrix_, typename Left_, typename Top_, typename Right_, typename Bottom_, typename Near_, typename Far_,
		std::size_t...ColumnIndices_, std::size_t...RowIndices_
	>
	[[nodiscard]] constexpr inline OutMatrix_ _make_ortho_vk
	(
		Left_&& left_,
		Top_&& top_,
		Right_&& right_,
		Bottom_&& bottom_,
		Near_&& near_,
		Far_&& far_,
		std::index_sequence<ColumnIndices_...> column_indices_,
		std::index_sequence<RowIndices_...> row_indices_
	)
	{
		CalcType_ left = static_cast<CalcType_>(std::forward<Left_>(left_));
		CalcType_ top = static_cast<CalcType_>(std::forward<Top_>(top_));
		CalcType_ right = static_cast<CalcType_>(std::forward<Right_>(right_));
		CalcType_ bottom = static_cast<CalcType_>(std::forward<Bottom_>(bottom_));
		CalcType_ near = static_cast<CalcType_>(std::forward<Near_>(near_));
		CalcType_ far = static_cast<CalcType_>(std::forward<Far_>(far_));

		using add_func = EmuCore::do_add<CalcType_, CalcType_>;
		using sub_func = EmuCore::do_subtract<CalcType_, CalcType_>;
		using div_func = EmuCore::do_divide<CalcType_, CalcType_>;
		using negate_func = EmuCore::do_negate<CalcType_>;

		// Prepare 3x3 diagonal
		CalcType_ out_00 = sub_func()(right, left); // 2 / (right - left); Divides at end as (right - left) is used more than once
		CalcType_ out_11 = sub_func()(bottom, top); // 2 / (bottom - top); Divides at end as (bottom - top) is used more than once
		CalcType_ out_22 = sub_func()(near, far);	// 1 / (near - far); Divides at end as (near - far) is used more than once

		// End chunk
		CalcType_ out_30 = div_func()(negate_func()(add_func()(right, left)), out_00); // -(right + left) / (right - left)
		CalcType_ out_31 = div_func()(negate_func()(add_func()(bottom, top)), out_11); // -(bottom + top) / (bottom - top)
		CalcType_ out_32 = div_func()(near, out_22); // near / (near - far)

		// Divide 3x3 diagonals
		out_00 = div_func()(CalcType_(2), out_00);
		out_11 = div_func()(CalcType_(2), out_11);
		out_22 = div_func()(CalcType_(1), out_22);

#pragma warning(push) // Silence duplicate move warnings here as no input value will be used twice
#pragma warning(disable: 26800)
		return OutMatrix_
		(
			_make_orth_vk_arg_for_index<ColumnIndices_, RowIndices_, OutMatrix_>
			(
				std::move(out_00),
				std::move(out_11),
				std::move(out_22),
				std::move(out_30),
				std::move(out_31),
				std::move(out_32)
			)...
		);
#pragma warning(pop)
	}

	template<EmuMath::TMP::EmuMatrix OutMatrix_, typename Left_, typename Top_, typename Right_, typename Bottom_, typename Near_, typename Far_>
	[[nodiscard]] constexpr inline OutMatrix_ _make_ortho_vk(Left_&& left_, Top_&& top_, Right_&& right_, Bottom_&& bottom_, Near_&& near_, Far_&& far_)
	{
		using out_uq = typename EmuCore::TMP::remove_ref_cv<OutMatrix_>::type;
		using out_fp = typename out_uq::preferred_floating_point;
		using left_uq = typename EmuCore::TMP::remove_ref_cv<Left_>::type;
		using top_uq = typename EmuCore::TMP::remove_ref_cv<Top_>::type;
		using right_uq = typename EmuCore::TMP::remove_ref_cv<Right_>::type;
		using bottom_uq = typename EmuCore::TMP::remove_ref_cv<Bottom_>::type;
		using near_uq = typename EmuCore::TMP::remove_ref_cv<Near_>::type;
		using far_uq = typename EmuCore::TMP::remove_ref_cv<Far_>::type;
		using calc_fp = typename EmuCore::TMP::largest_floating_point<out_fp, left_uq, top_uq, right_uq, bottom_uq, near_uq, far_uq>::type;

		using out_indices = EmuMath::TMP::make_full_matrix_index_sequences<out_uq>;
		using out_column_indices = typename out_indices::column_index_sequence;
		using out_row_indices = typename out_indices::row_index_sequence;

		return _make_ortho_vk<calc_fp, OutMatrix_>
		(
			std::forward<Left_>(left_),
			std::forward<Top_>(top_),
			std::forward<Right_>(right_),
			std::forward<Bottom_>(bottom_),
			std::forward<Near_>(near_),
			std::forward<Far_>(far_),
			out_column_indices(),
			out_row_indices()
		);
	}

	template<EmuMath::TMP::EmuMatrix OutMatrix_, EmuMath::TMP::EmuRect ViewRect_, typename Near_, typename Far_>
	[[nodiscard]] constexpr inline OutMatrix_ _make_ortho_vk(ViewRect_&& view_rect_, Near_&& near_, Far_&& far_)
	{
		using EmuMath::Helpers::rect_get_left;
		using EmuMath::Helpers::rect_get_top;
		using EmuMath::Helpers::rect_get_right;
		using EmuMath::Helpers::rect_get_bottom;

		using get_left_result = decltype(rect_get_left(std::forward<ViewRect_>(view_rect_)));
		using get_top_result = decltype(rect_get_top(std::forward<ViewRect_>(view_rect_)));
		using get_right_result = decltype(rect_get_right(std::forward<ViewRect_>(view_rect_)));
		using get_bottom_result = decltype(rect_get_bottom(std::forward<ViewRect_>(view_rect_)));

		using out_uq = typename EmuCore::TMP::remove_ref_cv<OutMatrix_>::type;
		using rect_uq = typename EmuCore::TMP::remove_ref_cv<ViewRect_>::type;
		using out_fp = typename out_uq::preferred_floating_point;
		using rect_fp = typename rect_uq::preferred_floating_point;
		using near_uq = typename EmuCore::TMP::remove_ref_cv<Near_>::type;
		using far_uq = typename EmuCore::TMP::remove_ref_cv<Far_>::type;
		using calc_fp = typename EmuCore::TMP::largest_floating_point<out_fp, rect_fp, near_uq, far_uq>::type;

		using out_indices = EmuMath::TMP::make_full_matrix_index_sequences<out_uq>;
		using out_column_indices = typename out_indices::column_index_sequence;
		using out_row_indices = typename out_indices::row_index_sequence;

		return _make_ortho_vk<calc_fp, OutMatrix_>
		(
#pragma warning(push) // Specifically silence the rect retrieval functions since we know there are no duplicate moves happening there
#pragma warning(disable: 26800)
			std::forward<get_left_result>(rect_get_left(std::forward<ViewRect_>(view_rect_))),
			std::forward<get_top_result>(rect_get_top(std::forward<ViewRect_>(view_rect_))),
			std::forward<get_right_result>(rect_get_right(std::forward<ViewRect_>(view_rect_))),
			std::forward<get_bottom_result>(rect_get_bottom(std::forward<ViewRect_>(view_rect_))),
#pragma warning(pop)
			std::forward<Near_>(near_),
			std::forward<Far_>(far_),
			out_column_indices(),
			out_row_indices()
		);
	}
#pragma endregion
}
#endif
