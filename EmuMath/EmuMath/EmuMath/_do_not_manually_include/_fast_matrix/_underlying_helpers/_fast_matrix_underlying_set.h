#ifndef EMU_MATH_FAST_MATRIX_UNDERLYING_SET_H_INC_
#define EMU_MATH_FAST_MATRIX_UNDERLYING_SET_H_INC_ 1

#include "_fast_matrix_tmp.h"
#include "_fast_matrix_underlying_get.h"

namespace EmuMath::Helpers::_fast_matrix_underlying
{
	template<EmuConcepts::EmuFastMatrix OutMatrix_, EmuConcepts::KnownSIMD RegisterForAll_, std::size_t...MajorIndices_, std::size_t...RegisterIndices_>
	[[nodiscard]] constexpr inline auto _fast_matrix_set1_from_register
	(
		const RegisterForAll_& register_for_all_,
		std::index_sequence<MajorIndices_...> major_indices_,
		std::index_sequence<RegisterIndices_...> register_indices_
	) -> typename std::remove_cvref<OutMatrix_>::type
	{
		return OutMatrix_
		(
			_get_matrix_arg_register<MajorIndices_, RegisterIndices_, false>(register_for_all_)...
		);
	}
}

#endif
