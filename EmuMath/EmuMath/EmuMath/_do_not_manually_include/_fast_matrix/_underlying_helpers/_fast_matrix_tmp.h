#ifndef EMU_MATH_FAST_MATRIX_TMP_H_INC_
#define EMU_MATH_FAST_MATRIX_TMP_H_INC_ 1

#include "../../__common/_common_math_tmp.h"
#include "../../../FastVector.h"
#include "../../../Matrix.h"
#include "../../../../EmuCore/TMPHelpers/TypeConvertors.h"
#include <functional>
#include <type_traits>

namespace EmuMath
{
	template<std::size_t NumColumns_, std::size_t NumRows_, typename T_, bool IsColumnMajor_ = true, std::size_t RegisterWidth_ = 128>
	struct FastMatrix;
}

namespace EmuMath::TMP
{
	template<std::size_t NumColumns_, std::size_t NumRows_, typename T_, bool IsColumnMajor_, std::size_t RegisterWidth_>
	struct is_emu_fast_matrix<EmuMath::FastMatrix<NumColumns_, NumRows_, T_, IsColumnMajor_, RegisterWidth_>>
	{
		static constexpr bool value = true;
	};
}

#endif
