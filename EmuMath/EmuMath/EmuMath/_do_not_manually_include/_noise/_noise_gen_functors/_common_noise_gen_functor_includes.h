#ifndef EMU_MATH_COMMON_NOISE_GEN_FUNCTOR_INCLUDES_H_INC_
#define EMU_MATH_COMMON_NOISE_GEN_FUNCTOR_INCLUDES_H_INC_ 1

#include "NoisePermutations.h"
#include "../_noise_info/NoiseType.h"
#include "../../../Random.h"
#include "../../../Vector.h"
#include "../../../../EmuCore/Functors/Arithmetic.h"
#include "../../../../EmuCore/TMPHelpers/TypeComparators.h"
#include "../../../../EmuCore/TMPHelpers/Values.h"

namespace EmuMath::Functors::_underlying_noise_gen
{
	template<std::size_t Dimensions_, typename T_>
	struct perlin_gradients
	{
		constexpr perlin_gradients()
		{
			static_assert(EmuCore::TMP::get_false<T_>(), "Attempted to construct an unspecialised perlin_gradients instance.");
		}
	};
	template<typename T_>
	struct perlin_gradients<1, T_>
	{
		using gradient_type = EmuMath::Vector<1, T_>;
		static constexpr std::size_t num_gradients = 2;
		static constexpr std::size_t mask = 1;
		static constexpr gradient_type values[num_gradients] = { gradient_type(1), gradient_type(-1) };

		template<std::size_t Index_>
		[[nodiscard]] static constexpr inline const gradient_type& at()
		{
			if constexpr (Index_ < num_gradients)
			{
				return values[Index_];
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<std::size_t, Index_>(), "Attempted to retrieve a 1D perlin noise gradient via compile-time index, but the provided Index_ was not in the valid range. The valid range is 0:1 (inclusive).");
			}
		}

		constexpr perlin_gradients()
		{
		}
	};
	template<typename T_>
	struct perlin_gradients<2, T_>
	{
		using gradient_type = EmuMath::Vector<2, T_>;
		static constexpr std::size_t num_gradients = 8;
		static constexpr std::size_t mask = 7;
		static constexpr gradient_type values[num_gradients] = 
		{
			gradient_type(1, 0),
			gradient_type(-1, 0),
			gradient_type(0, 1),
			gradient_type(0, -1),
			gradient_type(1, 1).NormaliseConstexpr(),
			gradient_type(-1, 1).NormaliseConstexpr(),
			gradient_type(1, -1).NormaliseConstexpr(),
			gradient_type(-1, -1).NormaliseConstexpr()
		};

		template<std::size_t Index_>
		[[nodiscard]] static constexpr inline const gradient_type& at()
		{
			if constexpr (Index_ < num_gradients)
			{
				return values[Index_];
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<std::size_t, Index_>(), "Attempted to retrieve a 2D perlin noise gradient via compile-time index, but the provided Index_ was not in the valid range. The valid range is 0:7 (inclusive).");
			}
		}

		constexpr perlin_gradients()
		{
		}
	};
	template<typename T_>
	struct perlin_gradients<3, T_>
	{
		using gradient_type = EmuMath::Vector<3, T_>;
		static constexpr std::size_t num_gradients = 16;
		static constexpr std::size_t mask = 15;
		static constexpr gradient_type values[num_gradients] =
		{
			gradient_type(1, 1, 0),
			gradient_type(-1, 1, 0),
			gradient_type(1, -1, 0),
			gradient_type(-1, -1, 0),
			gradient_type(1, 0, 1),
			gradient_type(-1, 0, 1),
			gradient_type(1, 0, -1),
			gradient_type(-1, 0, -1),
			gradient_type(0, 1,  1),
			gradient_type(0, -1,  1),
			gradient_type(0, 1, -1),
			gradient_type(0, -1, -1),
			// Filler values for successful bit masking; specific values are used to introduce no directional bias as per Ken Perlin
			gradient_type(1, 1, 0),
			gradient_type(-1, 1, 0),
			gradient_type(0, -1, 1),
			gradient_type(0, -1, -1)
		};

		template<std::size_t Index_>
		[[nodiscard]] static constexpr inline const gradient_type& at()
		{
			if constexpr (Index_ < num_gradients)
			{
				return values[Index_];
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<std::size_t, Index_>(), "Attempted to retrieve a 3D perlin noise gradient via compile-time index, but the provided Index_ was not in the valid range. The valid range is 0:15 (inclusive).");
			}
		}

		constexpr perlin_gradients()
		{
		}
	};

	/// <summary>Function applied to t_ to smooth it for smooth noise generation algorithms defined in EmuMath. </summary>
	/// <returns>Smoothed float t_, resulting from 6(t^5) - 15(t^4) + 10(t^3) (where t^x == t to the power of x).</returns>
	template<typename T_>
	constexpr inline T_ smooth_t(T_ t_)
	{
		return t_ * t_ * t_ * (t_ * (t_ * T_(6) - T_(15)) + T_(10));
	}

	/// <summary>Function to perform a dot product with an EmuMath vector using precalculated values outside of a vector without needing to construct one.</summary>
	/// <param name="vec_">Vector to form a dot product with.</param>
	/// <param name="x_">X-component of a theoretical vector to form a dot product with.</param>
	/// <param name="y_">Y-component of a theoretical vector to form a dot product with.</param>
	/// <returns>Dot product of the passed vector and scalar values.</returns>
	template<typename T_>
	constexpr inline T_ dot_with_scalar(const EmuMath::Vector<2, T_>& vector_, T_ x_, T_ y_)
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
	constexpr inline T_ dot_with_scalar(const EmuMath::Vector<3, T_>& vector_, T_ x_, T_ y_, T_ z_)
	{
		return (vector_.at<0>() * x_) + (vector_.at<1>() * y_) + (vector_.at<2>() * z_);
	}
}

#endif
