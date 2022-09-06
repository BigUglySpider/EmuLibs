#ifndef EMU_MATH_FAST_MATRIX_UNDERLYING_ROTATION_3D_H_INC_
#define EMU_MATH_FAST_MATRIX_UNDERLYING_ROTATION_3D_H_INC_ 1

#include "_fast_matrix_tmp.h"

namespace EmuMath::Helpers::_fast_matrix_underlying
{
	template<std::size_t Index_, EmuConcepts::EmuFastMatrix OutFastMatrix_>
	constexpr inline void _write_one_to_main_diagonal_index_for_rotation(typename EmuCore::TMP::remove_ref_cv_t<OutFastMatrix_>::value_type* p_data_)
	{
		using _fast_mat_uq = typename EmuCore::TMP::remove_ref_cv<OutFastMatrix_>::type;
		constexpr std::size_t offset = (Index_ * _fast_mat_uq::num_non_major_elements) + Index_;
		(*(p_data_ + offset)) = typename _fast_mat_uq::value_type(1);
	}

	template<EmuConcepts::EmuFastMatrix OutFastMatrix_, std::size_t...Indices_>
	constexpr inline void _write_one_to_main_diagonal_indices_for_rotation
	(
		typename EmuCore::TMP::remove_ref_cv_t<OutFastMatrix_>::value_type* p_data_,
		std::index_sequence<Indices_...> indices_
	)
	{
		(
			_write_one_to_main_diagonal_index_for_rotation<Indices_, OutFastMatrix_>
			(
				p_data_
			), ...
		);
	}

	template<EmuConcepts::EmuFastMatrix OutFastMatrix_, EmuConcepts::Arithmetic QuaternionT_>
	constexpr inline void _write_quaternion_to_loading_data
	(
		const EmuMath::Quaternion<QuaternionT_>& quaternion_,
		typename EmuCore::TMP::remove_ref_cv_t<OutFastMatrix_>::value_type* p_loading_data_
	)
	{
		using _fast_mat_uq = typename EmuCore::TMP::remove_ref_cv<OutFastMatrix_>::type;
		using calc_fp = typename _fast_mat_uq::preferred_floating_point;

		calc_fp x = static_cast<calc_fp>(quaternion_.X());
		calc_fp y = static_cast<calc_fp>(quaternion_.Y());
		calc_fp z = static_cast<calc_fp>(quaternion_.Z());
		calc_fp w = static_cast<calc_fp>(quaternion_.W());

		using add_func = EmuCore::do_add<calc_fp, calc_fp>;
		using sub_func = EmuCore::do_subtract<calc_fp, calc_fp>;
		using mul_func = EmuCore::do_multiply<calc_fp, calc_fp>;

		// Common calculation values
		calc_fp x_MUL_2 = mul_func()(x, calc_fp(2));
		calc_fp y_MUL_2 = mul_func()(y, calc_fp(2));
		calc_fp z_MUL_2 = mul_func()(z, calc_fp(2));

		calc_fp one_SUB_x_MUL_2_MUL_x = sub_func()(calc_fp(1), mul_func()(x_MUL_2, x));
		calc_fp x_MUL_2_MUL_y = mul_func()(x_MUL_2, y);
		calc_fp x_MUL_2_MUL_z = mul_func()(x_MUL_2, z);
		calc_fp x_MUL_2_MUL_w = mul_func()(x_MUL_2, w);

		calc_fp y_MUL_2_MUL_y = mul_func()(y_MUL_2, y);
		calc_fp y_MUL_2_MUL_z = mul_func()(y_MUL_2, z);
		calc_fp y_MUL_2_MUL_w = mul_func()(y_MUL_2, w);

		calc_fp z_MUL_2_MUL_z = mul_func()(z_MUL_2, z);
		calc_fp z_MUL_2_MUL_w = mul_func()(z_MUL_2, w);

		// Calculate pointer offsets to assign to
		using _fast_mat_uq = typename EmuCore::TMP::remove_ref_cv<OutFastMatrix_>::type;
		using _fast_mat_value = typename _fast_mat_uq::value_type;
		constexpr std::size_t per_column_offset = _fast_mat_uq::is_column_major ? _fast_mat_uq::num_rows : 1;
		constexpr std::size_t per_row_offset = _fast_mat_uq::is_column_major ? 1 : _fast_mat_uq::num_columns;

		constexpr std::size_t offset_c0r1 = per_row_offset;
		constexpr std::size_t offset_c0r2 = per_row_offset * 2;

		constexpr std::size_t offset_c1r0 = per_column_offset;
		constexpr std::size_t offset_c1r1 = per_column_offset + per_row_offset;
		constexpr std::size_t offset_c1r2 = per_column_offset + (per_row_offset * 2);

		constexpr std::size_t offset_c2r0 = per_column_offset * 2;
		constexpr std::size_t offset_c2r1 = (per_column_offset * 2) + per_row_offset;
		constexpr std::size_t offset_c2r2 = (per_column_offset * 2) + (per_row_offset * 2);

		// Bools for checking if we should calculate certain column/row indices
		constexpr bool do_c1 = _fast_mat_uq::num_columns >= 2;
		constexpr bool do_c2 = _fast_mat_uq::num_columns >= 3;
		constexpr bool do_r1 = _fast_mat_uq::num_rows >= 2;
		constexpr bool do_r2 = _fast_mat_uq::num_rows >= 3;


		// Column 0
		(*p_loading_data_) = static_cast<_fast_mat_value>(sub_func()(sub_func()(calc_fp(1), y_MUL_2_MUL_y), z_MUL_2_MUL_z)); // c0r0
		if constexpr (do_r1) (*(p_loading_data_ + offset_c0r1)) = static_cast<_fast_mat_value>(add_func()(x_MUL_2_MUL_y, z_MUL_2_MUL_w)); // c0r1
		if constexpr (do_r2) (*(p_loading_data_ + offset_c0r2)) = static_cast<_fast_mat_value>(sub_func()(x_MUL_2_MUL_z, y_MUL_2_MUL_w)); // c0r2

		// Column 1
		if constexpr (do_c1)
		{
			(*(p_loading_data_ + offset_c1r0)) = static_cast<_fast_mat_value>(sub_func()(x_MUL_2_MUL_y, z_MUL_2_MUL_w)); // c1r0
			if constexpr (do_r1) (*(p_loading_data_ + offset_c1r1)) = static_cast<_fast_mat_value>(sub_func()(one_SUB_x_MUL_2_MUL_x, z_MUL_2_MUL_z)); // c1r1
			if constexpr (do_r2) (*(p_loading_data_ + offset_c1r2)) = static_cast<_fast_mat_value>(add_func()(y_MUL_2_MUL_z, x_MUL_2_MUL_w)); // c1r2
		}

		// Column 2
		if constexpr (do_c2)
		{
			(*(p_loading_data_ + offset_c2r0)) = static_cast<_fast_mat_value>(add_func()(x_MUL_2_MUL_z, y_MUL_2_MUL_w)); // c2r0
			if constexpr (do_r1) (*(p_loading_data_ + offset_c2r1)) = static_cast<_fast_mat_value>(sub_func()(y_MUL_2_MUL_z, x_MUL_2_MUL_w)); // c2r1
			if constexpr (do_r2) (*(p_loading_data_ + offset_c2r2)) = static_cast<_fast_mat_value>(sub_func()(one_SUB_x_MUL_2_MUL_x, y_MUL_2_MUL_y)); // c2r2
		}

		// Set main diagonal to 1 after the initial 3x3
		if constexpr (_fast_mat_uq::num_columns >= 4 && _fast_mat_uq::num_rows >= 4)
		{
			constexpr std::size_t smallest_size = EmuCore::TMP::smallest_constant_v<std::size_t, _fast_mat_uq::num_columns, _fast_mat_uq::num_rows>;
			using remaining_main_diagonal_indices = EmuCore::TMP::make_offset_index_sequence<3, smallest_size - 3>;
			_write_one_to_main_diagonal_indices_for_rotation<OutFastMatrix_>(p_loading_data_, remaining_main_diagonal_indices());
		}
	}

	template<EmuConcepts::EmuFastMatrix OutFastMatrix_, EmuConcepts::Arithmetic QuaternionT_>
	[[nodiscard]] constexpr inline auto _make_matrix_rotate_3d_quat(const EmuMath::Quaternion<QuaternionT_>& quaternion_)
	{
		// Note: this function calculates everything regardless of Matrix size, since chances are that the output is at least 3x3 in this context
		// --- The extra layer of abstraction would be either difficult to maintain or a potential performance sacrifice with little gain
		using _fast_mat_uq = typename EmuCore::TMP::remove_ref_cv<OutFastMatrix_>::type;

		typename _fast_mat_uq::value_type data_to_load[_fast_mat_uq::expected_count_for_default_load_pointer] = { 0 };
		_write_quaternion_to_loading_data<OutFastMatrix_>(quaternion_, data_to_load);
		return _fast_mat_uq(data_to_load);
	}
}

#endif
