#ifndef EMU_MATH_VECTOR_ITERATOR_H_INC_
#define EMU_MATH_VECTOR_ITERATOR_H_INC_

#include "_common_vector_helpers.h"

// CONTAINS:
// --- vector_iterator
// --- vector_const_iterator
// --- vector_reverse_iterator
// --- vector_const_reverse_iterator

namespace EmuMath
{
	template<class Vector_>
	using vector_iterator = EmuMath::Helpers::_vector_underlying::_vector_iterator_underlying<Vector_, false>;

	template<class Vector_>
	using vector_const_iterator = EmuMath::Helpers::_vector_underlying::_vector_iterator_underlying<const Vector_, false>;

	template<class Vector_>
	using vector_reverse_iterator = EmuMath::Helpers::_vector_underlying::_vector_iterator_underlying<Vector_, true>;

	template<class Vector_>
	using vector_const_reverse_iterator = EmuMath::Helpers::_vector_underlying::_vector_iterator_underlying<const Vector_, true>;
}

#endif
