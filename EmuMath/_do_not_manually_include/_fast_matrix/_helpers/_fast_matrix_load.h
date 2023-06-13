#ifndef EMU_MATH_FAST_MATRIX_LOAD_H_INC_
#define EMU_MATH_FAST_MATRIX_LOAD_H_INC_ 1

#include "_common_fast_matrix_helper_includes.h"

namespace EmuMath::Helpers
{
	template<EmuConcepts::EmuFastMatrix OutFastMatrix_, EmuConcepts::EmuMatrix ScalarMatrix_>
	[[nodiscard]] constexpr inline auto fast_matrix_load(ScalarMatrix_&& scalar_matrix_)
		-> typename EmuCore::TMP::remove_ref_cv<OutFastMatrix_>::type
	{
		using _out_fast_mat_uq = typename EmuCore::TMP::remove_ref_cv<OutFastMatrix_>::type;
		return _fast_matrix_underlying::_load_from_scalar_matrix<OutFastMatrix_>
		(
			std::forward<ScalarMatrix_>(scalar_matrix_),
			std::make_index_sequence<_out_fast_mat_uq::total_num_registers>(),
			std::make_index_sequence<_out_fast_mat_uq::num_elements_per_register>()
		);
	}

	template<EmuConcepts::EmuFastMatrix OutFastMatrix_, EmuConcepts::EmuMatrix ScalarMatrix_>
	[[nodiscard]] constexpr inline auto fast_matrix_load_data_type(ScalarMatrix_&& scalar_matrix_)
		-> typename EmuCore::TMP::remove_ref_cv_t<OutFastMatrix_>::data_type
	{
		using _out_fast_mat_uq = typename EmuCore::TMP::remove_ref_cv<OutFastMatrix_>::type;
		return _fast_matrix_underlying::_load_major_chunks_from_scalar_matrix<OutFastMatrix_>
		(
			std::forward<ScalarMatrix_>(scalar_matrix_),
			std::make_index_sequence<_out_fast_mat_uq::num_elements_per_register>(),
			std::make_index_sequence<_out_fast_mat_uq::num_major_elements>(),
			std::make_index_sequence<_out_fast_mat_uq::num_registers_per_major>()
		);
	}
}

#endif
