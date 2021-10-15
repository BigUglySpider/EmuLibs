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
		constexpr inline T_ operator()(T_ sample_) const
		{
			return sample_;
		}
	};

	/// <summary> Modifies a sample assumed to be perlin noise from make_noise_1d so that it is in the range -1:1. </summary>
	struct noise_sample_processor_perlin1d_neg_1_to_1
	{
		constexpr noise_sample_processor_perlin1d_neg_1_to_1()
		{
		}
		template<typename T_>
		constexpr inline T_ operator()(T_ sample_) const
		{
			return sample_ * 2;
		}
	};

	/// <summary> Modifies a sample assumed to be perlin noise from make_noise_1d so that it is in the range 0:1. </summary>
	struct noise_sample_processor_perlin1d_normalise
	{
		constexpr noise_sample_processor_perlin1d_normalise()
		{
		}
		template<typename T_>
		constexpr inline T_ operator()(T_ sample_) const
		{
			return sample_ + T_(0.5);
		}
	};

	/// <summary> Modifies a sample assumed to be perlin noise from make_noise_2d so that it is in the range -1:1 </summary>
	struct noise_sample_processor_perlin2d_neg_1_to_1
	{
		constexpr noise_sample_processor_perlin2d_neg_1_to_1()
		{
		}
		template<typename T_>
		constexpr inline T_ operator()(T_ sample_) const
		{
			constexpr T_ max_magnitude_ = EmuCore::CommonConstants::SQRT_2<T_> * T_(0.5);
			constexpr T_ multiplier_ = T_(1) / max_magnitude_;
			return sample_ * multiplier_;
		}
	};

	/// <summary> Modifies a sample assumed to be perlin noise from make_noise_2d so that it is in the range 0:1. </summary>
	struct noise_sample_processor_perlin2d_normalise
	{
		constexpr noise_sample_processor_perlin2d_normalise()
		{
		}
		template<typename T_>
		constexpr inline T_ operator()(T_ sample_) const
		{
			// Do the bulk of the operation at compile time, since these are all constants
			// --- Additionally use a reciprocal so we can avoid floating-point division at runtime
			constexpr T_ min_ = -(EmuCore::CommonConstants::SQRT_2<T_> * T_(0.5));
			constexpr T_ max_ = EmuCore::CommonConstants::SQRT_2<T_> * T_(0.5);
			constexpr T_ denominator_reciprocal_ = T_(1) / (max_ - min_);

			// Norm(x) = (x - min) / (max - min)
			return (sample_ - min_) * denominator_reciprocal_;
		}
	};

	/// <summary> Modifies a sample assumed to be perlin noise from make_noise_3d so that it is in the range -1:1 </summary>
	struct noise_sample_processor_perlin3d_neg_1_to_1
	{
		constexpr noise_sample_processor_perlin3d_neg_1_to_1()
		{
		}
		template<typename T_>
		constexpr inline T_ operator()(T_ sample_) const
		{
			constexpr T_ max_magnitude_ = EmuCore::CommonConstants::SQRT_3<T_> * T_(0.5);
			constexpr T_ multiplier_ = T_(1) / max_magnitude_;
			return sample_ * multiplier_;
		}
	};

	/// <summary> Modifies a sample assumed to be perlin noise from make_noise_3d so that it is in the range 0:1. </summary>
	struct noise_sample_processor_perlin3d_normalise
	{
		constexpr noise_sample_processor_perlin3d_normalise()
		{
		}
		template<typename T_>
		constexpr inline T_ operator()(T_ sample_) const
		{
			constexpr T_ min_ = -(EmuCore::CommonConstants::SQRT_3<T_> * T_(0.5));
			constexpr T_ max_ = EmuCore::CommonConstants::SQRT_3<T_> * T_(0.5);
			constexpr T_ denominator_reciprocal_ = T_(1) / (max_ - min_);

			return (sample_ - min_) * denominator_reciprocal_;
		}
	};
}

#endif
