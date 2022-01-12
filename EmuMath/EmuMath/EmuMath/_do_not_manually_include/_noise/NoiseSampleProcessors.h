#ifndef EMU_MATH_NOISE_SAMPLE_PROCESSORS_H_INC_
#define EMU_MATH_NOISE_SAMPLE_PROCESSORS_H_INC_

#include "../../../EmuCore/Functors/Arithmetic.h"

namespace EmuMath::Functors
{
	/// <summary> Default functor for processing noise samples to their finalised form. Does nothing to modify the sample. </summary>
	struct noise_sample_processor_default
	{
		constexpr noise_sample_processor_default()
		{
		}
		template<typename T_>
		[[nodiscard]] constexpr inline T_ operator()(T_ sample_) const
		{
			return sample_;
		}
	};

	/// <summary> Normalises a sample assumed to be in the range of N-dimensional perlin noise, which is -(sqrt(N)/2):(sqrt(N)/2), into the range 0:1. </summary>
	template<std::size_t N_>
	struct noise_sample_processor_perlin_normalise
	{
		constexpr noise_sample_processor_perlin_normalise()
		{
		}
		template<typename T_>
		[[nodiscard]] constexpr inline T_ operator()(T_ sample_) const
		{
			constexpr T_ max_ = EmuCore::CommonConstants::SQRT_N<T_, std::size_t, N_> / T_(2);
			constexpr T_ min_ = -max_;
			constexpr T_ denominator_reciprocal_ = T_(1) / (max_ - min_);

			return (sample_ - min_) * denominator_reciprocal_;
		}
	};

	/// <summary> Normalises a sample assumed to be in the range of N-dimensional perlin noise, which is -(sqrt(N)/2):(sqrt(N)/2), into the range -1:1. </summary>
	template<std::size_t N_>
	struct noise_sample_processor_perlin_neg1_to_1
	{
		constexpr noise_sample_processor_perlin_neg1_to_1()
		{
		}
		template<typename T_>
		[[nodiscard]] constexpr inline T_ operator()(T_ sample_) const
		{
			// Highest absolute magnitude of N-dimensional perlin noise is (sqrt(N)/2).
			constexpr T_ max_magnitude_ = EmuCore::CommonConstants::SQRT_N<T_, std::size_t, N_> / T_(2);
			constexpr T_ multiplier_ = T_(1) / max_magnitude_;
			
			return sample_ * multiplier_;
		}
	};
}

#endif
