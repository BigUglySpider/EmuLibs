#ifndef EMU_MATH_COMMON_NOISE_GEN_FUNCTOR_INCLUDES_H_INC_
#define EMU_MATH_COMMON_NOISE_GEN_FUNCTOR_INCLUDES_H_INC_ 1

#include "NoisePermutations.h"
#include "../_noise_info/NoiseType.h"
#include "../../../Random.h"
#include "../../../Vector.h"
#include "../../../../EmuCore/Functors/Arithmetic.h"
#include "../../../../EmuCore/TMPHelpers/TypeComparators.h"

namespace EmuMath::Functors::_underlying_noise_gen
{
	/// <summary>Function applied to t_ to smooth it for smooth noise generation algorithms defined in EmuMath. </summary>
	/// <returns>Smoothed float t_, resulting from 6(t^5) - 15(t^4) + 10(t^3) (where t^x == t to the power of x).</returns>
	template<typename T_>
	constexpr inline T_ SmoothT(T_ t_)
	{
		return t_ * t_ * t_ * (t_ * (t_ * T_(6) - T_(15)) + T_(10));
	}

	/// <summary>Function to perform a dot product with an EmuMath vector using precalculated values outside of a vector without needing to construct one.</summary>
	/// <param name="vec_">Vector to form a dot product with.</param>
	/// <param name="x_">X-component of a theoretical vector to form a dot product with.</param>
	/// <param name="y_">Y-component of a theoretical vector to form a dot product with.</param>
	/// <returns>Dot product of the passed vector and scalar values.</returns>
	template<typename T_>
	constexpr inline T_ DotWithScalar(const EmuMath::Vector<2, T_>& vector_, T_ x_, T_ y_)
	{
		return vector_.at<0>() * x_ + vector_.at<1>() * y_;
	}
	/// <summary>Function to perform a dot product with an EmuMath vector using precalculated values outside of a vector without needing to construct one.</summary>
	/// <param name="vec_">Vector to form a dot product with.</param>
	/// <param name="x_">X-component of a theoretical vector to form a dot product with.</param>
	/// <param name="y_">Y-component of a theoretical vector to form a dot product with.</param>
	/// <param name="z_">Z-component of a theoretical vector to form a dot product with.</param>
	/// <returns>Dot product of the passed vector and scalar values.</returns>
	template<typename T_>
	constexpr inline T_ DotWithScalar(const EmuMath::Vector<3, T_>& vector_, T_ x_, T_ y_, T_ z_)
	{
		return (vector_.at<0>() * x_) + (vector_.at<1>() * y_) + (vector_.at<2>() * z_);
	}
}

#endif
