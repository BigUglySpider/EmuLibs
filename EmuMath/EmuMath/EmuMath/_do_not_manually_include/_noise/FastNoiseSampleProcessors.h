#ifndef EMU_MATH_FAST_NOISE_SAMPLE_PROCESSORS_H_INC_
#define EMU_MATH_FAST_NOISE_SAMPLE_PROCESSORS_H_INC_ 1

#include "../../../EmuCore/Functors/Arithmetic.h"
#include "../../../EmuSIMD/SIMDHelpers.h"

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
			min_256(EmuSIMD::set1<__m256>(min_)),
			denominator_reciprocal_256(EmuSIMD::set1<__m256>(denominator_reciprocal_))
		{
		}
		inline __m128 operator()(__m128 samples_) const
		{
			samples_ = EmuSIMD::sub(samples_, _mm256_castps256_ps128(min_256));
			return EmuSIMD::mul(samples_, _mm256_castps256_ps128(denominator_reciprocal_256));
		}
		inline __m256 operator()(__m256 samples_) const
		{
			samples_ = EmuSIMD::sub(samples_, min_256);
			return EmuSIMD::mul(samples_, denominator_reciprocal_256);
		}

	private:
		static constexpr float max_ = EmuCore::CommonConstants::SQRT_N<float, std::size_t, N_> / 2.0f;
		static constexpr float min_ = -max_;
		static constexpr float denominator_reciprocal_ = 1.0f / (max_ - min_);

		__m256 min_256;
		__m256 denominator_reciprocal_256;
	};

	template<std::size_t N_>
	struct fast_noise_sample_processor_perlin_neg1_to_1
	{
	public:
		constexpr fast_noise_sample_processor_perlin_neg1_to_1() : 
			multiplier_256(EmuSIMD::set1<__m256>(multiplier_))
		{
		}
		constexpr inline __m128 operator()(__m128 sample_) const
		{
			return EmuSIMD::mul_all(sample_, _mm256_castps256_ps128(multiplier_256));
		}
		constexpr inline __m256 operator()(__m256 sample_) const
		{
			return EmuSIMD::mul_all(sample_, multiplier_256);
		}

	private:
		// Highest absolute magnitude of N-dimensional perlin noise is (sqrt(N)/2).
		static constexpr float max_magnitude_ = EmuCore::CommonConstants::SQRT_N<float, std::size_t, N_> / 2.0f;
		static constexpr float multiplier_ = 1.0f / max_magnitude_;
		__m256 multiplier_256;
	};
}

#endif
