#ifndef EMU_MATH_FRACTAL_NOISE_INFO_H_INC_
#define EMU_MATH_FRACTAL_NOISE_INFO_H_INC_ 1

#include <cstddef>
#include "../_noise_tmp.h"

namespace EmuMath::Info
{
	template<typename FP_>
	struct FractalNoiseInfo
	{
	public:
		static_assert(EmuMath::TMP::assert_valid_noise_table_sample_type<FP_>(), "Provided an invalid FP_ to instantiate an EmuMath::Info::FractalNoiseInfo template.");
		using value_type = FP_;

		static constexpr std::size_t _default_octaves = 1;
		static constexpr value_type _default_lacunarity = value_type(2);
		static constexpr value_type _default_gain = value_type(0.5);

		static constexpr std::size_t min_octaves = 1;
		static constexpr value_type min_lacunarity = value_type(1);
		static constexpr value_type min_gain = value_type(0.000001);

		[[nodiscard]] static constexpr inline std::size_t make_valid_octaves(std::size_t val_)
		{
			return _get_valid_min_clamp<std::size_t>(val_, min_octaves);
		}
		[[nodiscard]] static constexpr inline value_type make_valid_lacunarity(value_type val_)
		{
			return _get_valid_min_clamp<value_type>(val_, min_lacunarity);
		}
		[[nodiscard]] static constexpr inline value_type make_valid_gain(value_type val_)
		{
			return _get_valid_min_clamp<value_type>(val_, min_gain);
		}

		constexpr FractalNoiseInfo() noexcept : 
			octaves(_default_octaves),
			lacunarity(_default_lacunarity),
			gain(_default_gain)
		{
		}
		constexpr FractalNoiseInfo(std::size_t octaves_, value_type lacunarity_, value_type gain_) noexcept :
			octaves(make_valid_octaves(octaves_)),
			lacunarity(make_valid_lacunarity(lacunarity_)),
			gain(make_valid_gain(gain_))
		{
		}
		constexpr FractalNoiseInfo(const FractalNoiseInfo& to_copy) noexcept :
			octaves(to_copy.octaves),
			lacunarity(to_copy.lacunarity),
			gain(to_copy.gain)
		{
		}

		inline FractalNoiseInfo& operator=(const FractalNoiseInfo& to_copy) noexcept
		{
			octaves = to_copy.octaves;
			lacunarity = to_copy.lacunarity;
			gain = to_copy.gain;
			return *this;
		}

		[[nodiscard]] constexpr inline std::size_t GetOctaves() const noexcept
		{
			return octaves;
		}
		[[nodiscard]] constexpr inline value_type GetLacunarity() const noexcept
		{
			return lacunarity;
		}
		[[nodiscard]] constexpr inline value_type GetGain() const noexcept
		{
			return gain;
		}

		inline std::size_t SetOctaves(std::size_t octaves_) noexcept
		{
			octaves = make_valid_octaves(octaves_);
			return octaves;
		}
		inline value_type SetLacunarity(value_type lacunarity_) noexcept
		{
			lacunarity = make_valid_lacunarity(lacunarity_);
			return lacunarity;
		}
		inline value_type SetGain(value_type gain_) noexcept
		{
			gain = make_valid_gain(gain_);
			return gain;
		}

	private:
		std::size_t octaves;
		value_type lacunarity;
		value_type gain;

		template<typename T_>
		static constexpr inline T_ _get_valid_min_clamp(T_ val_, T_ min_)
		{
			return val_ < min_ ? min_ : val_;
		}
	};
}

#endif
