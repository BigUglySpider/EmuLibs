#ifndef EMU_MATH__UNDERLYING_MATRIX_REINTERPRETATIONS_H_INC_
#define EMU_MATH__UNDERLYING_MATRIX_REINTERPRETATIONS_H_INC_ 1

#include "_common_underlying_matrix_helper_includes.h"
#include "_matrix_sets_underlying.h"

namespace EmuMath::Helpers::_underlying_matrix_funcs
{
	template<class Vector_, class OutMatrix_>
	[[nodiscard]] constexpr inline OutMatrix_ _vector_to_matrix(const Vector_& vector_)
	{
		return OutMatrix_(static_cast<EmuMath::Vector<Vector_::size, typename OutMatrix_::contained_type>>(vector_));
	}

	template<class OutMatrix_, class InMatrix_>
	[[nodiscard]] constexpr inline OutMatrix_ _matrix_as(const InMatrix_& in_)
	{
		OutMatrix_ out_ = OutMatrix_();
		_matrix_copy<OutMatrix_, InMatrix_>(out_, in_);
		return out_;
	}
}

#endif
