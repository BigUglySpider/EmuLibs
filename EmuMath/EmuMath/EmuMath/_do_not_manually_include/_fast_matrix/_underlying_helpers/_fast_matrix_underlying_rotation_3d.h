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

	template<EmuConcepts::EmuFastMatrix OutFastMatrix_, EmuConcepts::EmuFastQuaternion FastQuaternion_>
	constexpr inline void _write_quaternion_to_loading_data_fast
	(
		FastQuaternion_&& quaternion_,
		typename EmuCore::TMP::remove_ref_cv_t<OutFastMatrix_>::value_type* p_loading_data_
	)
	{
		// Quaternion Info
		using _fast_quat_uq = typename std::remove_cvref<FastQuaternion_>::type;
		using _register_type = typename _fast_quat_uq::register_type;
		using _value_type = typename _fast_quat_uq::value_type;
		constexpr std::size_t per_element_width = _fast_quat_uq::per_element_width;
		constexpr bool is_signed = _fast_quat_uq::is_signed;
		constexpr std::size_t num_registers = (_fast_quat_uq::num_registers < 1) ? 1 : _fast_quat_uq::num_registers;
		constexpr std::size_t num_elements_per_register = _fast_quat_uq::num_elements_per_register;
		constexpr std::size_t data_dump_size = num_registers * num_elements_per_register;

		// Fast Matrix info
		using _fast_mat_uq = typename EmuCore::TMP::remove_ref_cv<OutFastMatrix_>::type;
		using _fast_mat_value = typename _fast_mat_uq::value_type;
		constexpr std::size_t per_column_offset = _fast_mat_uq::is_column_major ? _fast_mat_uq::num_rows : 1;
		constexpr std::size_t per_row_offset = _fast_mat_uq::is_column_major ? 1 : _fast_mat_uq::num_columns;

		// Output offsets
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
		constexpr bool requires_one_SUB_x_MUL_2_MUL_x = (do_c1 && do_r1) || (do_c2 && do_r2);

		// Functor info
		using sub_func = EmuCore::do_subtract<_value_type, _value_type>;
		using add_func = EmuCore::do_add<_value_type, _value_type>;

		// Common data dumps
		// --- Indices correspond to the respective element on the leftmost point, e.g. xyzw_blah[0] = x_blah, xyzw_blah[2] = z_blah
		_value_type one_SUB_x_MUL_2_MUL_x;
		_value_type xyzw_MUL_2_MUL_y[data_dump_size]; // [2, 3] never used
		_value_type xyzw_MUL_2_MUL_z[data_dump_size]; // [3] never used
		_value_type xyzw_MUL_2_MUL_w[data_dump_size]; // [3] never used

		// Calculate common constants via SIMD
		_register_type two = EmuSIMD::set1<per_element_width>(_value_type(1));
		if constexpr (num_registers <= 1)
		{
			_register_type xyzw = std::forward<FastQuaternion_>(quaternion_).template GetRegister<0>();
			_register_type xyzw_MUL_2 = EmuSIMD::mul_all<per_element_width>(xyzw, two);

			EmuSIMD::store
			(
				EmuSIMD::mul_all<per_element_width>(xyzw_MUL_2, EmuSIMD::set_all_to_index<1, per_element_width>(xyzw)),
				xyzw_MUL_2_MUL_y
			);
			EmuSIMD::store
			(
				EmuSIMD::mul_all<per_element_width>(xyzw_MUL_2, EmuSIMD::set_all_to_index<2, per_element_width>(xyzw)),
				xyzw_MUL_2_MUL_z
			);
			EmuSIMD::store
			(
				EmuSIMD::mul_all<per_element_width>(xyzw_MUL_2, EmuSIMD::set_all_to_index<3, per_element_width>(xyzw)),
				xyzw_MUL_2_MUL_w
			);

			if constexpr (requires_one_SUB_x_MUL_2_MUL_x)
			{
				one_SUB_x_MUL_2_MUL_x = EmuSIMD::get_index<0>(xyzw);
				one_SUB_x_MUL_2_MUL_x *= (2 * one_SUB_x_MUL_2_MUL_x);
				one_SUB_x_MUL_2_MUL_x = _value_type(1) - one_SUB_x_MUL_2_MUL_x;
			}
		}
		else
		{
			_register_type xy = std::forward<FastQuaternion_>(quaternion_).template GetRegister<0>();
			_register_type zw = std::forward<FastQuaternion_>(quaternion_).template GetRegister<1>();
			_register_type xy_MUL_2 = EmuSIMD::mul_all<per_element_width>(xy, two);
			_register_type zw_MUL_2 = EmuSIMD::mul_all<per_element_width>(zw, two);

			_register_type all_same_element = EmuSIMD::set_all_to_index<1, per_element_width>(xy);
			EmuSIMD::store(EmuSIMD::mul_all<per_element_width>(xy_MUL_2, all_same_element), xyzw_MUL_2_MUL_y);
			// Don't do zw for this part as it isn't used anyway

			all_same_element = EmuSIMD::set_all_to_index<0, per_element_width>(zw);
			EmuSIMD::store(EmuSIMD::mul_all<per_element_width>(xy_MUL_2, all_same_element), xyzw_MUL_2_MUL_z);
			EmuSIMD::store(EmuSIMD::mul_all<per_element_width>(zw_MUL_2, all_same_element), xyzw_MUL_2_MUL_z + num_elements_per_register);

			all_same_element = EmuSIMD::set_all_to_index<1, per_element_width>(zw);
			EmuSIMD::store(EmuSIMD::mul_all<per_element_width>(xy_MUL_2, all_same_element), xyzw_MUL_2_MUL_w);
			EmuSIMD::store(EmuSIMD::mul_all<per_element_width>(zw_MUL_2, all_same_element), xyzw_MUL_2_MUL_w + num_elements_per_register);

			if constexpr (requires_one_SUB_x_MUL_2_MUL_x)
			{
				one_SUB_x_MUL_2_MUL_x = EmuSIMD::get_index<0>(xy);
				one_SUB_x_MUL_2_MUL_x *= (2 * one_SUB_x_MUL_2_MUL_x);
				one_SUB_x_MUL_2_MUL_x = _value_type(1) - one_SUB_x_MUL_2_MUL_x;
			}
		}

		// Calculate Matrix points as scalar for 2 reasons
		// --- 1: Calculations don't contiguously use what we have from above calculations, so would use a lot of shuffles that may ultimately harm performance
		// --- 2: Generic matrix could have any configuration that is not necessarily compatible with the register setup (semi-explicit specialised branches may be possible later)
		// Column 0
		(*p_loading_data_) = static_cast<_fast_mat_value>(sub_func()(sub_func()(_value_type(1), xyzw_MUL_2_MUL_y[1]), xyzw_MUL_2_MUL_z[2])); // c0r0
		if constexpr (do_r1) (*(p_loading_data_ + offset_c0r1)) = static_cast<_fast_mat_value>(add_func()(xyzw_MUL_2_MUL_y[0], xyzw_MUL_2_MUL_w[2])); // c0r1
		if constexpr (do_r2) (*(p_loading_data_ + offset_c0r2)) = static_cast<_fast_mat_value>(sub_func()(xyzw_MUL_2_MUL_z[0], xyzw_MUL_2_MUL_w[1])); // c0r2

		// Column 1
		if constexpr (do_c1)
		{
			(*(p_loading_data_ + offset_c1r0)) = static_cast<_fast_mat_value>(sub_func()(xyzw_MUL_2_MUL_y[0], xyzw_MUL_2_MUL_w[2])); // c1r0
			if constexpr (do_r1) (*(p_loading_data_ + offset_c1r1)) = static_cast<_fast_mat_value>(sub_func()(one_SUB_x_MUL_2_MUL_x, xyzw_MUL_2_MUL_z[2])); // c1r1
			if constexpr (do_r2) (*(p_loading_data_ + offset_c1r2)) = static_cast<_fast_mat_value>(add_func()(xyzw_MUL_2_MUL_z[1], xyzw_MUL_2_MUL_w[0])); // c1r2
		}

		// Column 2
		if constexpr (do_c2)
		{
			(*(p_loading_data_ + offset_c2r0)) = static_cast<_fast_mat_value>(add_func()(xyzw_MUL_2_MUL_z[0], xyzw_MUL_2_MUL_w[1])); // c2r0
			if constexpr (do_r1) (*(p_loading_data_ + offset_c2r1)) = static_cast<_fast_mat_value>(sub_func()(xyzw_MUL_2_MUL_z[1], xyzw_MUL_2_MUL_w[0])); // c2r1
			if constexpr (do_r2) (*(p_loading_data_ + offset_c2r2)) = static_cast<_fast_mat_value>(sub_func()(one_SUB_x_MUL_2_MUL_x, xyzw_MUL_2_MUL_y[1])); // c2r2
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

	template<EmuConcepts::EmuFastMatrix OutFastMatrix_, EmuConcepts::EmuFastQuaternion FastQuaternion_>
	[[nodiscard]] constexpr inline auto _make_matrix_rotate_3d_fast_quat(FastQuaternion_& quaternion_)
	{
		// Note: this function calculates everything regardless of Matrix size, since chances are that the output is at least 3x3 in this context
		// --- The extra layer of abstraction would be either difficult to maintain or a potential performance sacrifice with little gain
		using _fast_mat_uq = typename EmuCore::TMP::remove_ref_cv<OutFastMatrix_>::type;

		typename _fast_mat_uq::value_type data_to_load[_fast_mat_uq::expected_count_for_default_load_pointer] = { 0 };
		_write_quaternion_to_loading_data_fast<OutFastMatrix_>
		(
			std::forward<FastQuaternion_>(quaternion_),
			data_to_load
		);
		return _fast_mat_uq(data_to_load);
	}
}

#endif
