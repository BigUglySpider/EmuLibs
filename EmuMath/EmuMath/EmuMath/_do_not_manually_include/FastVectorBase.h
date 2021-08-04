#ifndef EMU_MATH_FAST_VECTOR_BASE_H_INC_
#define EMU_MATH_FAST_VECTOR_BASE_H_INC_

#include "../SIMDHelpers.h"
#include "../Vectors.h"

namespace EmuMath
{
	template<std::size_t NumElements_, typename ContainedT_>
	struct FastVector
	{
		static constexpr bool is_specialised = false;
	};
}

template<std::size_t Size_, typename T_>
std::ostream& operator<<(std::ostream& stream_, const EmuMath::FastVector<Size_, T_>& fastVector_)
{
	stream_ << fastVector_.AsEmuVector();
	return stream_;
}

#endif