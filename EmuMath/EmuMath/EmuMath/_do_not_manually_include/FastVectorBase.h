#ifndef EMU_MATH_FAST_VECTOR_BASE_H_INC_
#define EMU_MATH_FAST_VECTOR_BASE_H_INC_

#include "../Vectors.h"
#include <immintrin.h>

namespace EmuMath
{
	template<std::size_t NumElements_, typename ContainedT_>
	struct FastVector
	{
		static constexpr bool is_specialised = false;
	};
}

#endif