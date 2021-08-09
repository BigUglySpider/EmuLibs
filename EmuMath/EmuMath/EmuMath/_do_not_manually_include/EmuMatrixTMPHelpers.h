#ifndef EMU_MATRIX_TMP_COMPARATORS_H_INC_
#define EMU_MATRIX_TMP_COMPARATORS_H_INC_

#include <cstddef>

namespace EmuMath
{
	template<std::size_t NumColumns_, std::size_t NumRows_, typename T_>
	struct MatrixCM;
}

namespace EmuMath::TMPHelpers
{
	template<class T>
	struct is_emu_matrix
	{
		static constexpr bool value = false;
	};
	template<std::size_t NumColumns_, std::size_t NumRows_, typename T_>
	struct is_emu_matrix<EmuMath::MatrixCM<NumColumns_, NumRows_, T_>>
	{
		static constexpr bool value = true;
	};
	template<class T>
	static constexpr bool is_emu_matrix_v = is_emu_matrix<T>::value;
}

#endif
