#ifndef EMU_SIMD_HELPERS_SHUFFLES_H_INC_
#define EMU_SIMD_HELPERS_SHUFFLES_H_INC_ 1

#include "_underlying_template_helpers/_common_underlying_simd_template_helper_includes.h"
#include "_underlying_template_helpers/_simd_helpers_underlying_shuffle.h"

namespace EmuSIMD
{
	template<class Register_, std::size_t...Indices_>
	struct shuffle_mask : public _underlying_simd_helpers::_shuffle_mask<Register_, Indices_...>
	{
		static constexpr bool is_valid = _underlying_simd_helpers::is_valid_shuffle_mask_instance
		<
			shuffle_mask<Register_, Indices_...>
		>::value;
	};

#pragma region SHUFFLE_MASK_ALIASES
	template<std::size_t I0_, std::size_t I1_, std::size_t I2_, std::size_t I3_>
	using shuffle_mask_m128 = shuffle_mask<__m128, I0_, I1_, I2_, I3_>;

	template<std::size_t I0_, std::size_t I1_>
	using shuffle_mask_m128d = shuffle_mask<__m128d, I0_, I1_>;

	template<std::size_t I0_, std::size_t I1_, std::size_t I2_, std::size_t I3_>
	using shuffle_mask_m128i16 = shuffle_mask<__m128i, I0_, I1_, I2_, I3_>;

	template<std::size_t I0_, std::size_t I1_, std::size_t I2_, std::size_t I3_>
	using shuffle_mask_m128i32 = shuffle_mask<__m128i, I0_, I1_, I2_, I3_>;

	template
	<
		std::size_t I0_, std::size_t I1_, std::size_t I2_, std::size_t I3_, std::size_t I4_, std::size_t I5_, std::size_t I6_, std::size_t I7_,
		std::size_t I8_, std::size_t I9_, std::size_t I10_, std::size_t I11_, std::size_t I12_, std::size_t I13_, std::size_t I14_, std::size_t I15_
	>
	using shuffle_mask_m128i8 = shuffle_mask<__m128i, I0_, I1_, I2_, I3_, I4_, I5_, I6_, I7_, I8_, I9_, I10_, I11_, I12_, I13_, I14_, I15_>;

	template<std::size_t I0_, std::size_t I1_, std::size_t I2_, std::size_t I3_>
	using shuffle_mask_m256 = shuffle_mask<__m256, I0_, I1_, I2_, I3_>;

	template<std::size_t I0_, std::size_t I1_, std::size_t I2_, std::size_t I3_>
	using shuffle_mask_m256d = shuffle_mask<__m256d, I0_, I1_, I2_, I3_>;

	template<std::size_t I0_, std::size_t I1_, std::size_t I2_, std::size_t I3_>
	using shuffle_mask_m256i16 = shuffle_mask<__m256i, I0_, I1_, I2_, I3_>;

	template<std::size_t I0_, std::size_t I1_, std::size_t I2_, std::size_t I3_>
	using shuffle_mask_m256i32 = shuffle_mask<__m256i, I0_, I1_, I2_, I3_>;

	template
	<
		std::size_t I0_, std::size_t I1_, std::size_t I2_, std::size_t I3_, std::size_t I4_, std::size_t I5_, std::size_t I6_, std::size_t I7_,
		std::size_t I8_, std::size_t I9_, std::size_t I10_, std::size_t I11_, std::size_t I12_, std::size_t I13_, std::size_t I14_, std::size_t I15_,
		std::size_t I16_, std::size_t I17_, std::size_t I18_, std::size_t I19_, std::size_t I20_, std::size_t I21_, std::size_t I22_, std::size_t I23_,
		std::size_t I24_, std::size_t I25_, std::size_t I26_, std::size_t I27_, std::size_t I28_, std::size_t I29_, std::size_t I30_, std::size_t I31_
	>
	using shuffle_mask_m256i8 = shuffle_mask
	<
		__m256i,
		I0_, I1_, I2_, I3_, I4_, I5_, I6_, I7_, I8_, I9_, I10_, I11_, I12_, I13_, I14_, I15_,
		I16_, I17_, I18_, I19_, I20_, I21_, I22_, I23_, I24_, I25_, I26_, I27_, I28_, I29_, I30_, I31_
	>;

	template<std::size_t I0_, std::size_t I1_, std::size_t I2_, std::size_t I3_>
	using shuffle_mask_m512 = shuffle_mask<__m512, I0_, I1_, I2_, I3_>;

	template<std::size_t I0_, std::size_t I1_, std::size_t I2_, std::size_t I3_, std::size_t I4_, std::size_t I5_, std::size_t I6_, std::size_t I7_>
	using shuffle_mask_m512d = shuffle_mask<__m512d, I0_, I1_, I2_, I3_, I4_, I5_, I6_, I7_>;

	template<std::size_t I0_, std::size_t I1_, std::size_t I2_, std::size_t I3_>
	using shuffle_mask_m512i16 = shuffle_mask<__m512i, I0_, I1_, I2_, I3_>;

	template<std::size_t I0_, std::size_t I1_, std::size_t I2_, std::size_t I3_>
	using shuffle_mask_m512i32 = shuffle_mask<__m512i, I0_, I1_, I2_, I3_>;

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
		__m512i,
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
}

#endif
