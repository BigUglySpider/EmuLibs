#ifndef EMU_MATH_RNG_WRAPPER_H_INC_
#define EMU_MATH_RNG_WRAPPER_H_INC_ 1

#include "../../../EmuCore/TMPHelpers/TypeConvertors.h"
#include <chrono>
#include <limits>
#include <random>

namespace EmuMath
{
	template<bool Is64Bit_ = false>
	class RngWrapper
	{
	public:
#pragma region STATIC_INFO
		using int_type = typename std::conditional<Is64Bit_, std::int64_t, std::int32_t>::type;
		using unsigned_int_type = typename std::make_unsigned<int_type>::type;
		static constexpr bool is_64_bit = Is64Bit_;

		/// <summary> Default minimum value to use in construction when a custom range is not provided. </summary>
		static constexpr float _default_min = std::numeric_limits<float>::lowest();
		/// <summary> Default maximum value to use in construction when a custom range is not provided. </summary>
		static constexpr float _default_max = std::numeric_limits<float>::max();
		static constexpr int_type _lowest_possible_int = std::numeric_limits<int_type>::lowest();
		static constexpr int_type _highest_possible_int = std::numeric_limits<int_type>::max();

		/// <summary> Default seed used when one is not provided. Equates to a cast of time(0) to this wrapper's unsigned_int_type at the time of calling. </summary>
		/// <returns>Default seed to be used by constructors where a seed is not provided.</returns>
		static inline unsigned_int_type _default_seed()
		{
			return static_cast<unsigned_int_type>(time(0));
		}
		static inline int_type IntFromFloat(const float in_float_)
		{
			if (in_float_ <= _lowest_possible_int)
			{
				return _lowest_possible_int;
			}
			else if (in_float_ >= _highest_possible_int)
			{
				return _highest_possible_int;
			}
			else
			{
				return static_cast<int_type>(in_float_);
			}
		}
		template<typename Out_>
		static inline Out_ ValueFromInt(const int_type in_int_)
		{
			if constexpr (std::is_integral_v<Out_> && std::is_signed_v<Out_> && sizeof(Out_) >= sizeof(int_type))
			{
				return static_cast<Out_>(in_int_);
			}
			else if constexpr (std::is_integral_v<Out_> && std::is_unsigned_v<Out_> && sizeof(Out_) >= sizeof(int_type))
			{
				return (in_int_ <= 0) ? 0 : static_cast<Out_>(in_int_);
			}
			else
			{
				if (in_int_ <= std::numeric_limits<Out_>::lowest())
				{
					return std::numeric_limits<Out_>::lowest();
				}
				else if (in_int_ >= std::numeric_limits<Out_>::max())
				{
					return std::numeric_limits<Out_>::max();
				}
				else
				{
					return static_cast<Out_>(in_int_);
				}
			}
		}
		template<>
		static inline int_type ValueFromInt<int_type>(const int_type in_int_)
		{
			return in_int_;
		}
#pragma endregion

		/// <summary> Creates a wrapper with all default arguments. See all static RngWrapper items prefixed with _default_. </summary>
		RngWrapper() : RngWrapper(_default_seed())
		{
		}
		/// <summary> Creates a wrapper with a custom seed and the default min-max range. See RngWrapper::_default_min and RngWrapper::_default_max. </summary>
		/// <param name="seed_">Seed to initialise this wrapper's underlying engine with.</param>
		RngWrapper(unsigned_int_type seed_) : RngWrapper(_default_min, _default_max, seed_)
		{
		}
		/// <summary> Creates a wrapper with a custom min-max range and the default seed. See RngWrapper::_default_seed. </summary>
		/// <param name="min_">Minimum value for this wrapper to output.</param>
		/// <param name="max_">Maximum value for this wrapper to output.</param>
		RngWrapper(const float min_, const float max_) : RngWrapper(min_, max_, _default_seed())
		{
		}
		/// <summary> Creates a fully custom wrapper, making use of no defaults. </summary>
		/// <param name="min_">Minimum value for this wrapper to output.</param>
		/// <param name="max_">Maximum value for this wrapper to output.</param>
		/// <param name="seed_">Seed to initialise this wrapper's underlying engine with.</param>
		RngWrapper(const float min_, const float max_, unsigned_int_type seed_) : rng(seed_)
		{
			SetMinMax(min_, max_);
		}

		/// <summary>
		/// <para> Sets the minimum and maximum values that this wrapper may output. </para>
		/// <para> Input will be logically corrected if the passed min_ is greater than max_. </para>
		/// <para> Minimum and maximum integral values will be clamped within their valid range if min_ or max_ exceed their range in either direction. </para>
		/// </summary>
		/// <param name="min_">Value to set the minimum output from this wrapper to.</param>
		/// <param name="max_">Value to set the maximum output from this wrapper to.</param>
		inline void SetMinMax(float min_, float max_)
		{
			if (min_ <= max_)
			{
				minf = min_;
				maxf = max_;
			}
			else
			{
				minf = max_;
				maxf = min_;
			}
			_set_min_max_ints_from_floats();
		}

		/// <summary> Provides a copy of the minimum value this wrapper may output. </summary>
		/// <returns>The minimum value that this wrapper may output.</returns>
		inline float GetMin() const
		{
			return minf;
		}
		/// <summary> Provides a copy of the maximum value this wrapper may output. </summary>
		/// <returns>The maximum value that this wrapper may output.</returns>
		inline float GetMax() const
		{
			return maxf;
		}
		/// <summary> Provides a copy of the clamped minimum integral value this wrapper may output. </summary>
		/// <returns>The clamped minimum integral value that this wrapper may output.</returns>
		inline int_type GetMinInt() const
		{
			return min_int;
		}
		/// <summary> Provides a copy of the clamped maximum integral value this wrapper may output. </summary>
		/// <returns>The clamped maximum integral value that this wrapper may output.</returns>
		inline int_type GetMaxInt() const
		{
			return max_int;
		}

		/// <summary> Seeds the underlying RNG engine of this wrapper via the provided seed. </summary>
		/// <param name="seed_">Seed to apply to this wrapper's underlying engine.</param>
		inline void Seed(unsigned_int_type seed_)
		{
			rng.seed(seed_);
		}

		/// <summary>
		/// <para> Produces the next output from this wrapper's engine as the provided OutInt_, within the range of the stored MinInt and MaxInt. </para>
		/// <para> Minimum and maximum values will be clamped into a valid range if they exceed the passed type of integer's storage in any direction. </para>
		/// </summary>
		/// <typeparam name="OutInt_">Type to output, defaulting to this wrapper's int_type. Must be integral.</typeparam>
		/// <returns>Next value from this wrapper's engine using a uniform int distribution.</returns>
		template<typename OutInt_ = int_type, typename RequiresIntOutput_ = std::enable_if_t<std::is_integral_v<OutInt_>>>
		inline OutInt_ NextInt()
		{
			std::uniform_int_distribution<OutInt_> dist_(ValueFromInt<OutInt_>(min_int), ValueFromInt<OutInt_>(max_int));
			return dist_(rng);
		}
		/// <summary>
		/// <para> Produces the next output from this wrapper's engine as the provided OutInt_, using a custom min-max range which ignores that set for this wrapper. </para>
		/// </summary>
		/// <typeparam name="OutInt_">Type to output, defaulting to this wrapper's int_type. Must be integral.</typeparam>
		/// <returns>Next value from this wrapper's engine using a uniform int distribution.</returns>
		template<typename OutInt_ = int_type, typename RequiresIntOutput_ = std::enable_if_t<std::is_integral_v<OutInt_>>>
		inline OutInt_ NextInt(OutInt_ custom_min_, OutInt_ custom_max_)
		{
			std::uniform_int_distribution<OutInt_> dist_(custom_min_, custom_max_);
			return dist_(rng);
		}

		/// <summary>
		/// <para> Produces the next output from this wrapper's engine as the provided OutFP_, within the range of the stored Min and Max. </para>
		/// </summary>
		/// <typeparam name="OutFP_">Type to output, defaulting to this wrapper's int_type. Must be a floating point type.</typeparam>
		/// <returns>Next value from this wrapper's engine using a uniform real distribution.</returns>
		template<typename OutFP_ = double, typename RequiresFloatingPointOutput_ = std::enable_if_t<std::is_floating_point_v<OutFP_>>>
		inline OutFP_ NextReal()
		{
			std::uniform_real_distribution<OutFP_> dist_(static_cast<OutFP_>(minf), static_cast<OutFP_>(maxf));
			return dist_(rng);
		}
		/// <summary>
		/// <para> Produces the next output from this wrapper's engine as the provided OutFP_, using a custom min-max range which ignores that set for this wrapper. </para>
		/// </summary>
		/// <typeparam name="OutFP_">Type to output, defaulting to this wrapper's int_type. Must be a floating point type.</typeparam>
		/// <returns>Next value from this wrapper's engine using a uniform real distribution.</returns>
		template<typename OutFP_ = double, typename RequiresFloatingPointOutput_ = std::enable_if_t<std::is_floating_point_v<OutFP_>>>
		inline OutFP_ NextReal(OutFP_ custom_min_, OutFP_ custom_max_)
		{
			std::uniform_real_distribution<OutFP_> dist_(custom_min_, custom_max_);
			return dist_(rng);
		}

	private:
		using rng_type = typename std::conditional<Is64Bit_, std::mt19937_64, std::mt19937>::type;
		rng_type rng;
		float minf;
		float maxf;
		int_type min_int;
		int_type max_int;

		inline void _set_min_max_ints_from_floats()
		{
			min_int = IntFromFloat(minf);
			max_int = IntFromFloat(maxf);
		}
	};
}

#endif
