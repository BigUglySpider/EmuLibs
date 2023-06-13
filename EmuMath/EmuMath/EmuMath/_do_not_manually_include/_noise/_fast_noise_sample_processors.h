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
		[[nodiscard]] constexpr inline T_ operator()(T_ sample_) const
		{
			return sample_;
		}
	};

	template<std::size_t N_, EmuConcepts::KnownSIMD SIMDRegister_>
	struct _underlying_fast_noise_sample_processor_perlin_normalise
	{
	public:
		_underlying_fast_noise_sample_processor_perlin_normalise() :
			min_reg(EmuSIMD::set1<SIMDRegister_>(min_)),
			denominator_reciprocal_reg(EmuSIMD::set1<SIMDRegister_>(denominator_reciprocal_))
		{
		}
		[[nodiscard]] inline SIMDRegister_ operator()(typename EmuSIMD::TMP::register_to_arg_type<SIMDRegister_>::type samples_) const
		{
			samples_ = EmuSIMD::sub(samples_, min_reg);
			return EmuSIMD::mul_all(samples_, denominator_reciprocal_reg);
		}

	protected:
		const SIMDRegister_ min_reg;
		const SIMDRegister_ denominator_reciprocal_reg;

	private:
		static constexpr float max_ = EmuCore::CommonConstants::SQRT_N<float, std::size_t, N_> / 2.0f;
		static constexpr float min_ = -max_;
		static constexpr float denominator_reciprocal_ = 1.0f / (max_ - min_);
	};

	template<std::size_t N_>
	struct fast_noise_sample_processor_perlin_normalise : private _underlying_fast_noise_sample_processor_perlin_normalise<N_, EmuSIMD::f32x16>
	{
	public:
		fast_noise_sample_processor_perlin_normalise() :
			_underlying_fast_noise_sample_processor_perlin_normalise<N_, EmuSIMD::f32x16>()
		{
		}
		[[nodiscard]] inline EmuSIMD::f32x4 operator()(EmuSIMD::f32x4_arg samples_) const
		{
			EmuSIMD::f32x4 result = EmuSIMD::sub(samples_, EmuSIMD::cast<EmuSIMD::f32x4>(this->min_reg));
			return EmuSIMD::mul_all(result, EmuSIMD::cast<EmuSIMD::f32x4>(this->denominator_reciprocal_reg));
		}
		[[nodiscard]] inline EmuSIMD::f32x8 operator()(EmuSIMD::f32x8_arg samples_) const
		{
			EmuSIMD::f32x8 result = EmuSIMD::sub(samples_, EmuSIMD::cast<EmuSIMD::f32x8>(this->min_reg));
			return EmuSIMD::mul_all(result, EmuSIMD::cast<EmuSIMD::f32x8>(this->denominator_reciprocal_reg));
		}
		[[nodiscard]] inline EmuSIMD::f32x16 operator()(EmuSIMD::f32x16_arg samples_) const
		{
			EmuSIMD::f32x16 result = EmuSIMD::sub(samples_, EmuSIMD::cast<EmuSIMD::f32x16>(this->min_reg));
			return EmuSIMD::mul_all(result, EmuSIMD::cast<EmuSIMD::f32x16>(this->denominator_reciprocal_reg));
		}
	};

	template<std::size_t N_>
	struct fast_noise_sample_processor_perlin_neg1_to_1
	{
	public:
		constexpr fast_noise_sample_processor_perlin_neg1_to_1() : 
			multiplier_256(EmuSIMD::set1<__m256>(multiplier_))
		{
		}
		[[nodiscard]] constexpr inline __m128 operator()(__m128 sample_) const
		{
			return EmuSIMD::mul_all(sample_, _mm256_castps256_ps128(multiplier_256));
		}
		[[nodiscard]] constexpr inline __m256 operator()(__m256 sample_) const
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
