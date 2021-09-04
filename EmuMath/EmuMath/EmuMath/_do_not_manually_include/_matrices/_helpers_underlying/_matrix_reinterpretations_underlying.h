#ifndef EMU_MATH__UNDERLYING_MATRIX_REINTERPRETATIONS_H_INC_
#define EMU_MATH__UNDERLYING_MATRIX_REINTERPRETATIONS_H_INC_ 1

#include "_common_matrix_helper_includes.h"

namespace EmuMath::Helpers::_underlying_matrix_funcs
{
	template<class Vector_, class OutMatrix_>
	constexpr inline OutMatrix_ _vector_to_matrix(const Vector_& vector_)
	{
		return OutMatrix_(static_cast<EmuMath::Vector<Vector_::size, typename OutMatrix_::contained_type>>(vector_));
	}
}

#endif
