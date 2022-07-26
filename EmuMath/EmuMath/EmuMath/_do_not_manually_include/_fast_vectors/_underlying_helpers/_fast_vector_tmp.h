#ifndef EMU_MATH_FAST_VECTOR_TMP_H_INC_
#define EMU_MATH_FAST_VECTOR_TMP_H_INC_ 1

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
	template<class T_>
	struct is_emu_fast_vector
	{
		static constexpr bool value = std::conditional_t
		<
			std::is_same_v<T_, EmuCore::TMP::remove_ref_cv_t<T_>>,
			std::false_type,
			is_emu_fast_vector<EmuCore::TMP::remove_ref_cv_t<T_>>
		>::value;
	};

	template<std::size_t Size_, typename T_, std::size_t RegisterWidth_>
	struct is_emu_fast_vector<EmuMath::FastVector<Size_, T_, RegisterWidth_>>
	{
		static constexpr bool value = true;
	};
}

#endif
