#ifndef EMU_MATH_FAST_VECTOR_TMP_H_INC_
#define EMU_MATH_FAST_VECTOR_TMP_H_INC_ 1

#include "../../__common/_common_math_tmp.h"
#include "../../../../EmuCore/TMPHelpers/TypeConvertors.h"
#include <functional>
#include <type_traits>

namespace EmuMath
{
	template<std::size_t Size_, typename T_, std::size_t RegisterWidth_ = 128>
	struct FastVector;
}

namespace EmuMath::TMP
{
	template<std::size_t Size_, typename T_, std::size_t RegisterWidth_>
	struct is_emu_fast_vector<EmuMath::FastVector<Size_, T_, RegisterWidth_>>
	{
		static constexpr bool value = true;
	};	
}

#endif
