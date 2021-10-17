#ifndef EMU_MATH_FRACTAL_NOISE_INFO_H_INC_
#define EMU_MATH_FRACTAL_NOISE_INFO_H_INC_ 1

#include <cstddef>

namespace EmuMath::Info
{
	struct FractalNoiseInfo
	{
	public:
		static constexpr std::size_t _default_octaves = 1;
		static constexpr float _default_lacunarity = 2.0f;
		static constexpr float _default_gain = 0.5f;

		static constexpr std::size_t min_octaves = 1;
		static constexpr float min_lacunarity = 1.0f;
		static constexpr float min_gain = 0.000001f;

		static constexpr inline std::size_t make_valid_octaves(std::size_t val_)
		{
			return _get_valid_min_clamp<std::size_t>(val_, min_octaves);
		}
		static constexpr inline float make_valid_lacunarity(float val_)
		{
			return _get_valid_min_clamp<float>(val_, min_lacunarity);
		}
		static constexpr inline float make_valid_gain(float val_)
		{
			return _get_valid_min_clamp<float>(val_, min_gain);
		}

		constexpr FractalNoiseInfo() noexcept : 
			octaves(_default_octaves),
			lacunarity(_default_lacunarity),
			gain(_default_gain)
		{
		}
		constexpr FractalNoiseInfo(std::size_t octaves_, float lacunarity_, float gain_) noexcept :
			octaves(make_valid_octaves(octaves_)),
			lacunarity(make_valid_lacunarity(lacunarity_)),
			gain(make_valid_gain(gain_))
		{
		}
		constexpr FractalNoiseInfo(const FractalNoiseInfo& to_copy) :
			octaves(to_copy.octaves),
			lacunarity(to_copy.lacunarity),
			gain(to_copy.gain)
		{
		}

		inline FractalNoiseInfo& operator=(const FractalNoiseInfo& to_copy)
		{
			octaves = to_copy.octaves;
			lacunarity = to_copy.lacunarity;
			gain = to_copy.gain;
		}

		[[nodiscard]] constexpr inline std::size_t GetOctaves() const noexcept
		{
			return octaves;
		}
		[[nodiscard]] constexpr inline float GetLacunarity() const noexcept
		{
			return lacunarity;
		}
		[[nodiscard]] constexpr inline float GetGain() const noexcept
		{
			return gain;
		}

		inline std::size_t SetOctaves(std::size_t octaves_) noexcept
		{
			octaves = make_valid_octaves(octaves_);
			return octaves;
		}
		inline float SetLacunarity(float lacunarity_) noexcept
		{
			lacunarity = make_valid_lacunarity(lacunarity_);
			return lacunarity;
		}
		inline float SetGain(float gain_) noexcept
		{
			gain = make_valid_gain(gain_);
			return gain;
		}

	private:
		std::size_t octaves;
		float lacunarity;
		float gain;

		template<typename T_>
		static constexpr inline T_ _get_valid_min_clamp(T_ val_, T_ min_)
		{
			return val_ < min_ ? min_ : val_;
		}
	};
}

#endif
