#ifndef EMU_MATH_FAST_MATRIX_IDENTITY_H_INC_
#define EMU_MATH_FAST_MATRIX_IDENTITY_H_INC_ 1

#include "_common_fast_matrix_helper_includes.h"

namespace EmuMath::Helpers
{
	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, bool OutColumnMajor_ = true, std::size_t OutRegisterWidth_ = 128>
	[[nodiscard]] constexpr inline auto fast_matrix_identity()
		-> EmuMath::FastMatrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_, OutRegisterWidth_>
	{
		return _fast_matrix_underlying::_make_identity_matrix<EmuMath::FastMatrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_, OutRegisterWidth_>>
		(
			std::make_index_sequence<EmuMath::FastMatrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_, OutRegisterWidth_>::num_major_elements>(),
			std::make_index_sequence<EmuMath::FastMatrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_, OutRegisterWidth_>::num_registers_per_major>()
		);
	}

	template<EmuConcepts::EmuFastMatrix OutFastMatrix_>
	[[nodiscard]] constexpr inline auto fast_matrix_identity()
		-> typename EmuCore::TMP::remove_ref_cv<OutFastMatrix_>::type
	{
		using _out_fast_mat_uq = typename EmuCore::TMP::remove_ref_cv<OutFastMatrix_>::type;
		return _fast_matrix_underlying::_make_identity_matrix<_out_fast_mat_uq>
		(
			std::make_index_sequence<_out_fast_mat_uq::num_major_elements>(),
			std::make_index_sequence<_out_fast_mat_uq::num_registers_per_major>()
		);
	}

	template<EmuConcepts::EmuFastMatrix FastMatrix_>
	requires (!std::is_const_v<FastMatrix_>)
	constexpr inline void fast_matrix_assign_identity(FastMatrix_& fast_matrix_)
	{
		using _out_fast_mat_uq = typename EmuCore::TMP::remove_ref_cv<FastMatrix_>::type;
		_fast_matrix_underlying::_assign_identity_matrix<FastMatrix_>
		(
			fast_matrix_.RegistersPointer(),
			std::make_index_sequence<_out_fast_mat_uq::num_major_elements>(),
			std::make_index_sequence<_out_fast_mat_uq::num_registers_per_major>()
		);
	}
}

#endif
