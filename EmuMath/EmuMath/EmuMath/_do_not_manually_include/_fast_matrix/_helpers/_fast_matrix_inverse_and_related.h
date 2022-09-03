#ifndef EMU_MATH_FAST_MATRIX_INVERSE_AND_RELATED_H_INC_
#define EMU_MATH_FAST_MATRIX_INVERSE_AND_RELATED_H_INC_ 1

#include "_common_fast_matrix_helper_includes.h"

namespace EmuMath::Helpers
{
	template<EmuConcepts::EmuFastMatrix FastMatUq_>
	[[nodiscard]] constexpr inline bool _valid_for_4x4_square_inverse_f32()
	{
		return
		(
			FastMatUq_::num_major_elements == 4 &&
			FastMatUq_::num_registers_per_major == 1 &&
			FastMatUq_::register_width == 128 &&
			FastMatUq_::num_columns == FastMatUq_::num_rows &&
			FastMatUq_::per_element_width == 32 &&
			std::is_floating_point_v<typename FastMatUq_::value_type>
		);
	}

	template<EmuConcepts::EmuFastMatrix FastMatrix_>
	[[nodiscard]] constexpr inline auto fast_matrix_inverse_4x4_square_f32(const FastMatrix_& in_matrix_)
		-> typename EmuMath::TMP::fast_matrix_transpose_result<FastMatrix_>::type
	{
		using _fast_mat_uq = typename EmuCore::TMP::remove_ref_cv<FastMatrix_>::type;
		using _register_type = typename _fast_mat_uq::register_type;
		constexpr std::size_t width = _fast_mat_uq::per_element_width;

		_register_type det_sub = EmuSIMD::mul_all<width>
		(
			EmuSIMD::shuffle<1, 3, 1, 3>(in_matrix_.major_chunks[0], in_matrix_.major_chunks[2]),
			EmuSIMD::shuffle<0, 2, 0, 2>(in_matrix_.major_chunks[1], in_matrix_.major_chunks[3])
		);
		det_sub = EmuSIMD::fmsub<width>
		(
			EmuSIMD::shuffle<0, 2, 0, 2>(in_matrix_.major_chunks[0], in_matrix_.major_chunks[2]),
			EmuSIMD::shuffle<1, 3, 1, 3>(in_matrix_.major_chunks[1], in_matrix_.major_chunks[3]),
			det_sub
		);

		_register_type temp_det_0 = EmuSIMD::shuffle<0>(det_sub);
		_register_type temp_det_1 = EmuSIMD::shuffle<3>(det_sub);
		_register_type a = EmuSIMD::shuffle<0, 1, 0, 1>(in_matrix_.major_chunks[0], in_matrix_.major_chunks[1]);
		_register_type b = EmuSIMD::shuffle<2, 3, 2, 3>(in_matrix_.major_chunks[0], in_matrix_.major_chunks[1]);
		_register_type c = EmuSIMD::shuffle<0, 1, 0, 1>(in_matrix_.major_chunks[2], in_matrix_.major_chunks[3]);
		_register_type d = EmuSIMD::shuffle<2, 3, 2, 3>(in_matrix_.major_chunks[2], in_matrix_.major_chunks[3]);

		_register_type adj_d_MUL_c = EmuSIMD::matrix_2x2_multiply_adj_norm_rm<width>(d, c);
		_register_type adj_a_MUL_b = EmuSIMD::matrix_2x2_multiply_adj_norm_rm<width>(a, b);
		_register_type x = EmuSIMD::sub<width>(EmuSIMD::mul_all<width>(temp_det_1, a), EmuSIMD::matrix_2x2_multiply_rm<width>(b, adj_d_MUL_c));
		_register_type w = EmuSIMD::sub<width>(EmuSIMD::mul_all<width>(temp_det_0, d), EmuSIMD::matrix_2x2_multiply_rm<width>(c, adj_a_MUL_b));

		_register_type det = EmuSIMD::mul_all<width>(temp_det_0, temp_det_1);
		temp_det_1 = EmuSIMD::shuffle<2>(det_sub);
		temp_det_0 = EmuSIMD::shuffle<1>(det_sub);
		det = EmuSIMD::fmadd<width>(temp_det_0, temp_det_1, det);

		_register_type y = EmuSIMD::sub<width>(EmuSIMD::mul_all<width>(temp_det_0, c), EmuSIMD::matrix_2x2_multiply_norm_adj_rm<width>(d, adj_a_MUL_b));
		_register_type z = EmuSIMD::sub<width>(EmuSIMD::mul_all<width>(temp_det_1, b), EmuSIMD::matrix_2x2_multiply_norm_adj_rm<width>(a, adj_d_MUL_c));

		_register_type trace_of_submat_product = EmuSIMD::mul_all<width>(adj_a_MUL_b, EmuSIMD::shuffle<0, 2, 1, 3>(adj_d_MUL_c));
		trace_of_submat_product = EmuSIMD::horizontal_sum_fill<width>(trace_of_submat_product);
		det = EmuSIMD::sub<width>(det, trace_of_submat_product);

		_register_type det_reciprocal = EmuSIMD::div(EmuSIMD::set<_register_type, width>(1, -1, -1, 1), det);
		x = EmuSIMD::mul_all(x, det_reciprocal);
		y = EmuSIMD::mul_all(y, det_reciprocal);
		z = EmuSIMD::mul_all(z, det_reciprocal);
		w = EmuSIMD::mul_all(w, det_reciprocal);

		return typename EmuMath::TMP::fast_matrix_transpose_result<FastMatrix_>::type
		(
			EmuSIMD::shuffle<3, 1, 3, 1>(x, y),
			EmuSIMD::shuffle<2, 0, 2, 0>(x, y),
			EmuSIMD::shuffle<3, 1, 3, 1>(z, w),
			EmuSIMD::shuffle<2, 0, 2, 0>(z, w)
		);
	}

	template<EmuConcepts::EmuFastMatrix FastMatrix_>
	[[nodiscard]] constexpr inline auto fast_matrix_inverse(FastMatrix_&& in_matrix_)
		-> typename EmuMath::TMP::fast_matrix_transpose_result<FastMatrix_>::type
	{
		using _fast_mat_uq = typename EmuCore::TMP::remove_ref_cv<FastMatrix_>::type;
		if constexpr (_valid_for_4x4_square_inverse_f32<_fast_mat_uq>())
		{
			return fast_matrix_inverse_4x4_square_f32
			(
				EmuCore::TMP::const_lval_ref_cast<FastMatrix_>(std::forward<FastMatrix_>(in_matrix_))
			);
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<FastMatrix_>(), "Generic case for `fast_matrix_inverse` not implemented.");
		}
	}
}

#endif
