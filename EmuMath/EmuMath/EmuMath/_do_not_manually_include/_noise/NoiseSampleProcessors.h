#ifndef EMU_MATH_NOISE_SAMPLE_PROCESSORS_H_INC_
#define EMU_MATH_NOISE_SAMPLE_PROCESSORS_H_INC_

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
}

#endif
