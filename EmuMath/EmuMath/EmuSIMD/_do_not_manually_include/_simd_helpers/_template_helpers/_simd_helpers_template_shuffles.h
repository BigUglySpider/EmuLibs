#ifndef EMU_SIMD_HELPERS_SHUFFLES_H_INC_
#define EMU_SIMD_HELPERS_SHUFFLES_H_INC_ 1

#include "_underlying_template_helpers/_all_underlying_templates.h"
#include "_simd_helpers_template_gets.h"

namespace EmuSIMD
{
	template<std::size_t...Indices_, class Register_>
	[[nodiscard]] inline Register_ shuffle(Register_ ab_)
	{
		return _underlying_simd_helpers::_execute_shuffle<Indices_...>(ab_);
	}
	template<std::size_t...Indices_, class Register_>
	[[nodiscard]] inline Register_ shuffle(Register_ a_, Register_ b_)
	{
		return _underlying_simd_helpers::_execute_shuffle<Indices_...>(a_, b_);
	}

#pragma region FULL_WIDTH_SHUFFLES
	/// <summary>
	/// <para> Performs a full-width shuffle of the passed SIMD register's indices. </para>
	/// <para> For 128-bit registers, this is the same as a normal shuffle. </para>
	/// </summary>
	/// <param name="ab_">128-bit register to shuffle.</param>
	/// <returns>Result of shuffling the passed Register with the provided indices.</returns>
	template<std::size_t...Indices_, EmuConcepts::KnownSIMD Register_>
	requires (EmuSIMD::TMP::simd_register_width_v<Register_> == 128)
	[[nodiscard]] constexpr inline Register_ shuffle_full_width(Register_ ab_)
	{
		return shuffle<Indices_...>(ab_);
	}

	/// <summary>
	/// <para> Performs a full-width shuffle of the passed SIMD register's indices. </para>
	/// <para> For 128-bit registers, this is the same as a normal shuffle. </para>
	/// </summary>
	/// <param name="a_">128-bit register to shuffle for the lo bytes of the output register.</param>
	/// <param name="b_">128-bit register to shuffle for the hi bytes of the output register.</param>
	/// <returns>Result of shuffling the passed Registers with the provided indices.</returns>
	template<std::size_t...Indices_, EmuConcepts::KnownSIMD Register_>
	requires (EmuSIMD::TMP::simd_register_width_v<Register_> == 128)
	[[nodiscard]] constexpr inline Register_ shuffle_full_width(Register_ a_, Register_ b_)
	{
		return shuffle<Indices_...>(a_, b_);
	}

	/// <summary>
	/// <para> Performs a full-width shuffle of the passed SIMD register's indices, allowing shuffles between lanes unlike a normal shuffle. </para>
	/// </summary>
	/// <param name="a_">256-bit register to shuffle for the lo 128-bit lane of the output register.</param>
	/// <param name="b_">256-bit register to shuffle for the hi 128-bit lane of the output register.</param>
	/// <returns>Result of full-width-shuffling the passed Registers with the provided indices.</returns>
	template<std::size_t I0_, std::size_t I1_, std::size_t I2_, std::size_t I3_, EmuConcepts::KnownSIMD Register_>
	requires (EmuSIMD::TMP::simd_register_width_v<Register_> == 256 && EmuSIMD::TMP::register_element_count_v<Register_> == 4)
	[[nodiscard]] constexpr inline Register_ shuffle_full_width(Register_ a_, Register_ b_)
	{
		using _register_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		using _generic_register_type = EmuSIMD::f64x4;
		using _generic_lane_register = typename EmuSIMD::TMP::half_width<_generic_register_type>::type;
		_generic_register_type out;

		constexpr std::size_t max_lo_index = 1;
		constexpr std::size_t lowest_index = EmuCore::TMP::smallest_constant_v<std::size_t, I0_, I1_, I2_, I3_>;
		if constexpr (lowest_index > max_lo_index)
		{
			// All hi indices, we can just shuffle hi lane
			auto hi_a = EmuSIMD::extract_lane<1, _generic_lane_register>(a_);
			auto hi_b = EmuSIMD::extract_lane<1, _generic_lane_register>(b_);

			out = EmuSIMD::cast<_generic_register_type>(EmuSIMD::shuffle<I0_ - 2, I1_ - 2>(hi_a));
			out = _mm256_insertf128_pd(out, EmuSIMD::shuffle<I2_ - 2, I3_ - 2>(hi_b), 1);
		}
		else
		{
			constexpr std::size_t highest_index = EmuCore::TMP::greatest_constant_v<std::size_t, I0_, I1_, I2_, I3_>;
			if constexpr (highest_index <= max_lo_index)
			{
				// All lo indices, we can just shuffle lo lane
				auto lo_a = EmuSIMD::cast<_generic_lane_register>(a_);
				auto lo_b = EmuSIMD::cast<_generic_lane_register>(b_);

				out = EmuSIMD::cast<_generic_register_type>(EmuSIMD::shuffle<I0_, I1_>(lo_a));
				out = _mm256_insertf128_pd(out, EmuSIMD::shuffle<I2_, I3_>(lo_b), 1);
			}
			else // Mixed lanes, we need to actually try
			{
				// Lo
				constexpr int i0_lane = (I0_ <= max_lo_index) ? 0 : 1;
				constexpr int i1_lane = (I1_ <= max_lo_index) ? 0 : 1;
				_generic_lane_register lane_0, lane_1;
				if constexpr (i0_lane == i1_lane)
				{
					lane_0 = EmuSIMD::extract_lane<i0_lane, _generic_lane_register>(a_);
					lane_1 = lane_0;
				}
				else
				{
					lane_0 = EmuSIMD::extract_lane<i0_lane, _generic_lane_register>(a_);
					lane_1 = EmuSIMD::extract_lane<i1_lane, _generic_lane_register>(a_);
				}
				out = EmuSIMD::cast<_generic_register_type>(EmuSIMD::shuffle<I0_ % 2, I1_ % 2>(lane_0, lane_1));

				// Hi
				constexpr int i2_lane = (I2_ <= max_lo_index) ? 0 : 1;
				constexpr int i3_lane = (I3_ <= max_lo_index) ? 0 : 1;
				if constexpr (i2_lane == i3_lane)
				{
					lane_0 = EmuSIMD::extract_lane<i2_lane, _generic_lane_register>(b_);
					lane_1 = lane_0;
				}
				else
				{
					lane_0 = EmuSIMD::extract_lane<i2_lane, _generic_lane_register>(b_);
					lane_1 = EmuSIMD::extract_lane<i3_lane, _generic_lane_register>(b_);
				}

				out = _mm256_insertf128_pd(out, EmuSIMD::cast<_generic_lane_register>(EmuSIMD::shuffle<I2_ % 2, I3_ % 2>(lane_0, lane_1)), 1);
			}
		}

		if constexpr (std::is_same_v<_register_uq, _generic_register_type>)
		{
			return out;
		}
		else
		{
			return EmuSIMD::cast<Register_>(out);
		}
	}

	/// <summary>
	/// <para> Performs a full-width shuffle of the passed SIMD register's indices, allowing shuffles between lanes unlike a normal shuffle. </para>
	/// </summary>
	/// <param name="ab_">256-bit register to shuffle.</param>
	/// <returns>Result of full-width-shuffling the passed Register with the provided indices.</returns>
	template<std::size_t I0_, std::size_t I1_, std::size_t I2_, std::size_t I3_, EmuConcepts::KnownSIMD Register_>
	requires (EmuSIMD::TMP::simd_register_width_v<Register_> == 256 && EmuSIMD::TMP::register_element_count_v<Register_> == 4)
	[[nodiscard]] constexpr inline Register_ shuffle_full_width(Register_ ab_)
	{
		return shuffle_full_width<I0_, I1_, I2_, I3_>(ab_, ab_);
	}
#pragma endregion
}

#endif
