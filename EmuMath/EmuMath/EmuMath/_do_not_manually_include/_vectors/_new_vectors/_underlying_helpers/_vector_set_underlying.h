#ifndef EMU_MATH_NEW_VECTOR_SET_UNDERLYING_H_INC_
#define EMU_MATH_NEW_VECTOR_SET_UNDERLYING_H_INC_ 1

#include "_vector_tmp.h"
#include "_vector_get_underlying.h"

namespace EmuMath::Helpers::_vector_underlying
{
	template<std::size_t Index_, typename...Args_, std::size_t Size_, typename T_>
	constexpr inline void _vector_set(EmuMath::NewVector<Size_, T_>& vector_, Args_&&...args_)
	{
		vector_.template Set<Index_, Args_...>(std::forward<Args_>(args_)...);
	}
}

#endif
