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

namespace EmuConcepts
{
	template<class Lhs_, class Rhs_>
	concept EmuFastMatrixMultPair =
	(
		(EmuConcepts::EmuFastMatrix<Lhs_>) &&
		(EmuConcepts::EmuFastMatrix<Rhs_>) &&
		(EmuCore::TMP::remove_ref_cv_t<Lhs_>::num_columns == EmuCore::TMP::remove_ref_cv_t<Rhs_>::num_rows) &&
		(EmuCore::TMP::remove_ref_cv_t<Lhs_>::register_width == EmuCore::TMP::remove_ref_cv_t<Rhs_>::register_width) &&
		(std::is_same_v<typename EmuCore::TMP::remove_ref_cv_t<Lhs_>::value_type, typename EmuCore::TMP::remove_ref_cv_t<Rhs_>::value_type>)
	);
}

#endif
