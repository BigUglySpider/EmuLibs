#ifndef EMU_MATH_FAST_VECTOR_H_INC_
#define EMU_MATH_FAST_VECTOR_H_INC_ 1

#include "_do_not_manually_include/_vectors/FastVector4f.h"

namespace EmuMath::SIMD
{
	template<std::size_t Size_, typename contained_type>
	__m128 m128_from_emu_math_vector(const EmuMath::Vector<Size_, contained_type>& vector_)
	{
		if constexpr (Size_ >= 4)
		{
			return _mm_set_ps
			(
				static_cast<float>(vector_.at<3>(vector_)),
				static_cast<float>(vector_.at<2>(vector_)),
				static_cast<float>(vector_.at<1>(vector_)),
				static_cast<float>(vector_.at<0>(vector_))
			);
		}
		else if constexpr (Size_ == 3)
		{
			return _mm_set_ps
			(
				0.0f,
				static_cast<float>(vector_.at<2>(vector_)),
				static_cast<float>(vector_.at<1>(vector_)),
				static_cast<float>(vector_.at<0>(vector_))
			);
		}
		else if constexpr (Size_ == 2)
		{
			return _mm_set_ps
			(
				0.0f,
				0.0f,
				static_cast<float>(vector_.at<1>(vector_)),
				static_cast<float>(vector_.at<0>(vector_))
			);
		}
		else if constexpr (Size_ == 1)
		{
			return _mm_set_ps
			(
				0.0f,
				0.0f,
				0.0f,
				static_cast<float>(vector_.at<0>(vector_))
			);
		}
		else
		{
			return _mm_setzero_ps();
		}
	}
}

#endif
