#ifndef EMU_MATH_FAST_NOISE_SAMPLE_PROCESSORS_H_INC_
#define EMU_MATH_FAST_NOISE_SAMPLE_PROCESSORS_H_INC_ 1

#include "../../SIMDHelpers.h"
#include "../../../EmuCore/Functors/Arithmetic.h"

namespace EmuMath::Functors
{
	struct fast_noise_sample_processor_default
	{
		constexpr fast_noise_sample_processor_default()
		{
		}
		template<typename T_>
		constexpr inline T_ operator()(T_ sample_) const
		{
			return sample_;
		}
	};

	template<std::size_t N_>
	struct fast_noise_sample_processor_perlin_normalise
	{
	public:
		fast_noise_sample_processor_perlin_normalise() :
			min_128(_mm_set1_ps(min_)),
			denominator_reciprocal_128(_mm_set1_ps(denominator_reciprocal_))
		{
		}
		inline __m128 operator()(__m128 samples_) const
		{
			samples_ = _mm_sub_ps(samples_, min_128);
			return _mm_mul_ps(samples_, denominator_reciprocal_128);
		}

	private:
		static constexpr float max_ = EmuCore::CommonConstants::SQRT_N<float, std::size_t, N_> / 2.0f;
		static constexpr float min_ = -max_;
		static constexpr float denominator_reciprocal_ = 1.0f / (max_ - min_);

		__m128 min_128;
		__m128 denominator_reciprocal_128;
	};

	template<std::size_t N_>
	struct fast_noise_sample_processor_perlin_neg1_to_1
	{
	public:
		constexpr fast_noise_sample_processor_perlin_neg1_to_1() : 
			multiplier_128(_mm_set1_ps(multiplier_))
		{
		}
		constexpr inline __m128 operator()(__m128 sample_) const
		{
			return _mm_mul_ps(sample_, multiplier_128);
		}

	private:
		// Highest absolute magnitude of N-dimensional perlin noise is (sqrt(N)/2).
		static constexpr float max_magnitude_ = EmuCore::CommonConstants::SQRT_N<float, std::size_t, N_> / 2.0f;
		static constexpr float multiplier_ = 1.0f / max_magnitude_;
		__m128 multiplier_128;
	};
}

#endif
