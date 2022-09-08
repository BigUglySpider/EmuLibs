#ifndef EMU_SIMD_HELPERS_SHUFFLES_H_INC_
#define EMU_SIMD_HELPERS_SHUFFLES_H_INC_ 1

#include "_underlying_template_helpers/_all_underlying_templates.h"
#include "_simd_helpers_template_gets.h"

namespace EmuSIMD
{
	template<class Register_, std::size_t...Indices_>
	struct shuffle_mask : public _underlying_simd_helpers::_shuffle_mask<Register_, Indices_...>
	{
		static constexpr bool is_valid = _underlying_simd_helpers::is_valid_shuffle_mask_instance
		<
			_underlying_simd_helpers::_shuffle_mask<Register_, Indices_...>
		>::value;
	};

#pragma region SHUFFLE_MASK_ALIASES
	template<std::size_t I0_, std::size_t I1_, std::size_t I2_, std::size_t I3_>
	using shuffle_mask_m128 = shuffle_mask<EmuSIMD::f32x4, I0_, I1_, I2_, I3_>;

	template<std::size_t I0_, std::size_t I1_>
	using shuffle_mask_m128d = shuffle_mask<EmuSIMD::f64x2, I0_, I1_>;

	template<std::size_t I0_, std::size_t I1_, std::size_t I2_, std::size_t I3_>
	using shuffle_mask_m128i16 = shuffle_mask<EmuSIMD::i128_generic, I0_, I1_, I2_, I3_>;

	template<std::size_t I0_, std::size_t I1_, std::size_t I2_, std::size_t I3_>
	using shuffle_mask_m128i32 = shuffle_mask<EmuSIMD::i128_generic, I0_, I1_, I2_, I3_>;

	template
	<
		std::size_t I0_, std::size_t I1_, std::size_t I2_, std::size_t I3_, std::size_t I4_, std::size_t I5_, std::size_t I6_, std::size_t I7_,
		std::size_t I8_, std::size_t I9_, std::size_t I10_, std::size_t I11_, std::size_t I12_, std::size_t I13_, std::size_t I14_, std::size_t I15_
	>
	using shuffle_mask_m128i8 = shuffle_mask<EmuSIMD::i128_generic, I0_, I1_, I2_, I3_, I4_, I5_, I6_, I7_, I8_, I9_, I10_, I11_, I12_, I13_, I14_, I15_>;

	template<std::size_t I0_, std::size_t I1_, std::size_t I2_, std::size_t I3_>
	using shuffle_mask_m256 = shuffle_mask<EmuSIMD::f32x8, I0_, I1_, I2_, I3_>;

	template<std::size_t I0_, std::size_t I1_, std::size_t I2_, std::size_t I3_>
	using shuffle_mask_m256d = shuffle_mask<EmuSIMD::f64x4, I0_, I1_, I2_, I3_>;

	template<std::size_t I0_, std::size_t I1_, std::size_t I2_, std::size_t I3_>
	using shuffle_mask_m256i16 = shuffle_mask<EmuSIMD::i256_generic, I0_, I1_, I2_, I3_>;

	template<std::size_t I0_, std::size_t I1_, std::size_t I2_, std::size_t I3_>
	using shuffle_mask_m256i32 = shuffle_mask<EmuSIMD::i256_generic, I0_, I1_, I2_, I3_>;

	template
	<
		std::size_t I0_, std::size_t I1_, std::size_t I2_, std::size_t I3_, std::size_t I4_, std::size_t I5_, std::size_t I6_, std::size_t I7_,
		std::size_t I8_, std::size_t I9_, std::size_t I10_, std::size_t I11_, std::size_t I12_, std::size_t I13_, std::size_t I14_, std::size_t I15_,
		std::size_t I16_, std::size_t I17_, std::size_t I18_, std::size_t I19_, std::size_t I20_, std::size_t I21_, std::size_t I22_, std::size_t I23_,
		std::size_t I24_, std::size_t I25_, std::size_t I26_, std::size_t I27_, std::size_t I28_, std::size_t I29_, std::size_t I30_, std::size_t I31_
	>
	using shuffle_mask_m256i8 = shuffle_mask
	<
		EmuSIMD::i256_generic,
		I0_, I1_, I2_, I3_, I4_, I5_, I6_, I7_, I8_, I9_, I10_, I11_, I12_, I13_, I14_, I15_,
		I16_, I17_, I18_, I19_, I20_, I21_, I22_, I23_, I24_, I25_, I26_, I27_, I28_, I29_, I30_, I31_
	>;

	template<std::size_t I0_, std::size_t I1_, std::size_t I2_, std::size_t I3_>
	using shuffle_mask_m512 = shuffle_mask<EmuSIMD::f32x16, I0_, I1_, I2_, I3_>;

	template<std::size_t I0_, std::size_t I1_, std::size_t I2_, std::size_t I3_, std::size_t I4_, std::size_t I5_, std::size_t I6_, std::size_t I7_>
	using shuffle_mask_m512d = shuffle_mask<EmuSIMD::f64x8, I0_, I1_, I2_, I3_, I4_, I5_, I6_, I7_>;

	template<std::size_t I0_, std::size_t I1_, std::size_t I2_, std::size_t I3_>
	using shuffle_mask_m512i16 = shuffle_mask<EmuSIMD::i512_generic, I0_, I1_, I2_, I3_>;

	template<std::size_t I0_, std::size_t I1_, std::size_t I2_, std::size_t I3_>
	using shuffle_mask_m512i32 = shuffle_mask<EmuSIMD::i512_generic, I0_, I1_, I2_, I3_>;

	template
	<
		std::size_t I0_,  std::size_t I1_,  std::size_t I2_,  std::size_t I3_,  std::size_t I4_,  std::size_t I5_,  std::size_t I6_,  std::size_t I7_,
		std::size_t I8_,  std::size_t I9_,  std::size_t I10_, std::size_t I11_, std::size_t I12_, std::size_t I13_, std::size_t I14_, std::size_t I15_,
		std::size_t I16_, std::size_t I17_, std::size_t I18_, std::size_t I19_, std::size_t I20_, std::size_t I21_, std::size_t I22_, std::size_t I23_,
		std::size_t I24_, std::size_t I25_, std::size_t I26_, std::size_t I27_, std::size_t I28_, std::size_t I29_, std::size_t I30_, std::size_t I31_,
		std::size_t I32_, std::size_t I33_, std::size_t I34_, std::size_t I35_, std::size_t I36_, std::size_t I37_, std::size_t I38_, std::size_t I39_,
		std::size_t I40_, std::size_t I41_, std::size_t I42_, std::size_t I43_, std::size_t I44_, std::size_t I45_, std::size_t I46_, std::size_t I47_,
		std::size_t I48_, std::size_t I49_, std::size_t I50_, std::size_t I51_, std::size_t I52_, std::size_t I53_, std::size_t I54_, std::size_t I55_,
		std::size_t I56_, std::size_t I57_, std::size_t I58_, std::size_t I59_, std::size_t I60_, std::size_t I61_, std::size_t I62_, std::size_t I63_
	>
	using shuffle_mask_m512i8 = shuffle_mask
	<
		EmuSIMD::i512_generic,
		I0_,  I1_,  I2_,  I3_,  I4_,  I5_,  I6_,  I7_,  I8_,  I9_,  I10_, I11_, I12_, I13_, I14_, I15_,
		I16_, I17_, I18_, I19_, I20_, I21_, I22_, I23_, I24_, I25_, I26_, I27_, I28_, I29_, I30_, I31_,
		I32_, I33_, I34_, I35_, I36_, I37_, I38_, I39_, I40_, I41_, I42_, I43_, I44_, I45_, I46_, I47_,
		I48_, I49_, I50_, I51_, I52_, I53_, I54_, I55_, I56_, I57_, I58_, I59_, I60_, I61_, I62_, I63_
	>;
#pragma endregion

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
	template<std::size_t...Indices_, EmuConcepts::KnownSIMD Register_>
	requires (EmuSIMD::TMP::simd_register_width_v<Register_> == 128)
	[[nodiscard]] constexpr inline Register_ shuffle_full_width(Register_ ab_)
	{
		return shuffle<Indices_...>(ab_);
	}

	template<std::size_t...Indices_, EmuConcepts::KnownSIMD Register_>
	requires (EmuSIMD::TMP::simd_register_width_v<Register_> == 128)
	[[nodiscard]] constexpr inline Register_ shuffle_full_width(Register_ a_, Register_ b_)
	{
		return shuffle<Indices_...>(a_, b_);
	}

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

	template<std::size_t I0_, std::size_t I1_, std::size_t I2_, std::size_t I3_, EmuConcepts::KnownSIMD Register_>
	requires (EmuSIMD::TMP::simd_register_width_v<Register_> == 256 && EmuSIMD::TMP::register_element_count_v<Register_> == 4)
	[[nodiscard]] constexpr inline Register_ shuffle_full_width(Register_ ab_)
	{
		return shuffle_full_width<I0_, I1_, I2_, I3_>(ab_, ab_);
	}
#pragma endregion
}

#endif
