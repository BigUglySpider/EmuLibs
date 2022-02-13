#ifndef EMU_MATH_VECTOR_CORE_DO_SWAP_SPECIALISATION_H_INC_
#define EMU_MATH_VECTOR_CORE_DO_SWAP_SPECIALISATION_H_INC_ 1

#include "../_vector_t.h"

namespace EmuCore
{
	template<std::size_t SizeA_, typename TA_, std::size_t SizeB_, typename TB_>
	struct do_swap<EmuMath::Vector<SizeA_, TA_>, EmuMath::Vector<SizeB_, TB_>>
	{
		constexpr inline do_swap()
		{
		}

		template<bool IncludeNonContained_ = true>
		constexpr inline void operator()(EmuMath::Vector<SizeA_, TA_>& a_, EmuMath::Vector<SizeB_, TB_>& b_)
		{
			EmuMath::Helpers::vector_swap<IncludeNonContained_>(a_, b_);
		}
	};
}

#endif
