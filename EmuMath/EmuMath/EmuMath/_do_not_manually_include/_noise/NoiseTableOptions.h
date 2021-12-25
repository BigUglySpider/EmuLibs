#ifndef EMU_MATH_NOISE_TABLE_OPTIONS_H_INC_
#define EMU_MATH_NOISE_TABLE_OPTIONS_H_INC_ 1

#include "NoiseTMP.h"
#include "NoiseFunctors.h"
#include "_noise_info/NoisePermutationInfo.h"
#include "_noise_info/FractalNoiseInfo.h"
#include "../../../EmuCore/TMPHelpers/Values.h"

namespace EmuMath
{
	template<std::size_t Dimensions_, typename SampleTypeFP_>
	struct NoiseTableOptions
	{
	public:
		static constexpr std::size_t num_dimensions = Dimensions_;
		static_assert(EmuMath::TMP::assert_valid_noise_dimensions<num_dimensions>(), "Invalid Dimensions_ provided to EmuMath::NoiseTableOptions.");
		static_assert(EmuMath::TMP::assert_valid_noise_table_sample_type<SampleTypeFP_>(), "Provided an invalid SampleTypeFP_ to instantiate an EmuMath::NoiseTableOptions template.");
		
		using value_type = SampleTypeFP_;
		using fractal_info_type = EmuMath::Info::FractalNoiseInfo<value_type>;

		template<typename X_, typename Y_, typename Z_>
		static constexpr inline EmuMath::Vector<num_dimensions, value_type> make_correctly_sized_vector(X_ x_, Y_ y_, Z_ z_)
		{
			if constexpr (num_dimensions == 1)
			{
				return EmuMath::Vector<1, value_type>(x_);
			}
			else if constexpr (num_dimensions == 2)
			{
				return EmuMath::Vector<2, value_type>(x_, y_);
			}
			else if constexpr (num_dimensions == 3)
			{
				return EmuMath::Vector<3, value_type>(x_, y_, z_);
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<X_>(), "Cannot created correctly sized vector for invalidly sized EmuMath::NoiseTableOptions.");
				return {};
			}
		}


		static constexpr EmuMath::Vector<num_dimensions, value_type> _default_start_point = make_correctly_sized_vector(0, 0, 0);
		static constexpr EmuMath::Vector<num_dimensions, value_type> _default_end_point = make_correctly_sized_vector(1, 1, 1);
		static constexpr EmuMath::Vector<num_dimensions, std::size_t> _default_table_resolution = make_correctly_sized_vector(32, 32, 32);
		static constexpr value_type _default_freq = value_type(1);
		static constexpr bool _default_step_mode = false;
		static constexpr bool _default_use_fractal_noise = false;

		NoiseTableOptions() : 
			NoiseTableOptions
			(
				_default_table_resolution,
				_default_start_point,
				_default_end_point,
				_default_freq,
				_default_step_mode,
				_default_use_fractal_noise,
				EmuMath::Info::NoisePermutationInfo(),
				fractal_info_type()
			)
		{
		}
		constexpr NoiseTableOptions
		(
			const EmuMath::Vector<num_dimensions, std::size_t>& table_resolution_,
			const EmuMath::Vector<num_dimensions, value_type>& start_point_,
			const EmuMath::Vector<num_dimensions, value_type>& end_point_or_step_,
			value_type freq_,
			bool step_mode_,
			bool use_fractal_noise_,
			const EmuMath::Info::NoisePermutationInfo& permutation_info_,
			const fractal_info_type& fractal_noise_info_
		) : 
			table_resolution(table_resolution_),
			start_point(start_point_),
			end_point_or_step(end_point_or_step_),
			freq(freq_),
			step_mode(step_mode_),
			use_fractal_noise(use_fractal_noise_),
			permutation_info(permutation_info_),
			fractal_noise_info(fractal_noise_info_)
		{
		}
		constexpr NoiseTableOptions(const NoiseTableOptions& to_copy_) :
			NoiseTableOptions
			(
				to_copy_.table_resolution,
				to_copy_.start_point,
				to_copy_.end_point_or_step,
				to_copy_.freq,
				to_copy_.step_mode,
				to_copy_.use_fractal_noise,
				to_copy_.permutation_info,
				to_copy_.fractal_noise_info
			)
		{
		}

		/// <summary>
		/// <para> Provides the relevant step for these options. Step is the difference between adjacent points when calculating individual samples. </para>
		/// <para> If step_mode is true, this will return a copy of end_point_or_step. </para>
		/// <para>
		///		If step_mode is false, this will calculate a step for each axis based on the rable resolution and the distance between start_point and end_point_or_step.
		/// </para>
		/// </summary>
		/// <returns>Step to use based on these options.</returns>
		[[nodiscard]] constexpr inline EmuMath::Vector<num_dimensions, value_type> MakeStep() const
		{
			if (step_mode)
			{
				return end_point_or_step;
			}
			else
			{
				return (end_point_or_step - start_point) / table_resolution;
			}
		}

		/// <summary> Number of items to be present on the table when using these options. </summary>
		EmuMath::Vector<num_dimensions, std::size_t> table_resolution;
		/// <summary> Starting point when creating noise samples using these options. </summary>
		EmuMath::Vector<num_dimensions, value_type> start_point;
		/// <summary>
		///	<para> Target point to automatically calculate step if step_mode is false </para>
		/// <para> The step per iteration (looping back every new iteration) if step_mode is true. </para>
		/// </summary>
		EmuMath::Vector<num_dimensions, value_type> end_point_or_step;
		/// <summary> Frequency multiplier to apply to points when generating samples. </summary>
		value_type freq;
		/// <summary>
		/// <para> If true, end_point_or_step will be interpreted as a custom step. </para>
		/// <para> 
		///		If false, end_point_or_step will be interpreted as a target end point and used to calculate an automatic step based on itself, 
		///		start_point and table_resolution. 
		/// </para>
		/// </summary>
		bool step_mode;
		/// <summary> Boolean indicating if fractal noise generation should be used. </summary>
		bool use_fractal_noise;
		/// <summary> Informative data structure for creating a power-of-2 collection of permutations for generating noise masks. </summary>
		EmuMath::Info::NoisePermutationInfo permutation_info;
		/// <summary> Informative data structure for use when use_fractal_noise is true only. </summary>
		fractal_info_type fractal_noise_info;

	};
}

#endif
