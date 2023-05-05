#ifndef EMU_SIMD_HELPERS_UNDERLYING_MOVEMASKS_H_INC_
#define EMU_SIMD_HELPERS_UNDERLYING_MOVEMASKS_H_INC_ 1

#include "_common_underlying_simd_template_helper_includes.h"
#include "../../../../../EmuCore/TMPHelpers/VariadicHelpers.h"

namespace EmuSIMD::_underlying_simd_helpers
{
	template<typename OutT_, bool...ActiveIndices_, std::size_t...Indices_>
	[[nodiscard]] constexpr inline OutT_ _construct_movemask_value(EmuCore::TMP::bool_sequence<ActiveIndices_...> active_indices_, std::index_sequence<Indices_...> indices_)
	{
		return static_cast<OutT_>((... | (static_cast<OutT_>(ActiveIndices_) << Indices_)));
	}

	template<class Register_, bool...ActiveIndices_>
	struct _make_movemask
	{
	};

	template<bool I0_, bool I1_, bool I2_, bool I3_>
	struct _make_movemask<EmuSIMD::f32x4, I0_, I1_, I2_, I3_>
	{
		static constexpr std::uint8_t value = _construct_movemask_value<std::uint8_t>
		(
			EmuCore::TMP::bool_sequence<I0_, I1_, I2_, I3_>(),
			std::make_index_sequence<4>()
		);
	};

	template<bool I0_, bool I1_, bool I2_, bool I3_, bool I4_, bool I5_, bool I6_, bool I7_>
	struct _make_movemask<EmuSIMD::f32x8, I0_, I1_, I2_, I3_, I4_, I5_, I6_, I7_>
	{
		static constexpr std::uint8_t value = _construct_movemask_value<std::uint8_t>
		(
			EmuCore::TMP::bool_sequence<I0_, I1_, I2_, I3_, I4_, I5_, I6_, I7_>(),
			std::make_index_sequence<8>()
		);
	};

	template<bool I0_, bool I1_, bool I2_, bool I3_, bool I4_, bool I5_, bool I6_, bool I7_, bool I8_, bool I9_, bool I10_, bool I11_, bool I12_, bool I13_, bool I14_, bool I15_>
	struct _make_movemask<EmuSIMD::f32x16, I0_, I1_, I2_, I3_, I4_, I5_, I6_, I7_, I8_, I9_, I10_, I11_, I12_, I13_, I14_, I15_>
	{
		static constexpr std::uint8_t value = _construct_movemask_value<std::uint16_t>
		(
			EmuCore::TMP::bool_sequence<I0_, I1_, I2_, I3_, I4_, I5_, I6_, I7_, I8_, I9_, I10_, I11_, I12_, I13_, I14_, I15_>(),
			std::make_index_sequence<16>()
		);
	};

	template<bool I0_, bool I1_>
	struct _make_movemask<EmuSIMD::f64x2, I0_, I1_>
	{
		static constexpr std::uint8_t value = _construct_movemask_value<std::uint8_t>
			(
				EmuCore::TMP::bool_sequence<I0_, I1_>(),
				std::make_index_sequence<2>()
			);
	};

	template<bool I0_, bool I1_, bool I2_, bool I3_>
	struct _make_movemask<EmuSIMD::f64x4, I0_, I1_, I2_, I3_>
	{
		static constexpr std::uint8_t value = _construct_movemask_value<std::uint8_t>
		(
			EmuCore::TMP::bool_sequence<I0_, I1_, I2_, I3_>(),
			std::make_index_sequence<4>()
		);
	};

	template<bool I0_, bool I1_, bool I2_, bool I3_, bool I4_, bool I5_, bool I6_, bool I7_>
	struct _make_movemask<EmuSIMD::f64x8, I0_, I1_, I2_, I3_, I4_, I5_, I6_, I7_>
	{
		static constexpr std::uint8_t value = _construct_movemask_value<std::uint8_t>
		(
			EmuCore::TMP::bool_sequence<I0_, I1_, I2_, I3_, I4_, I5_, I6_, I7_>(),
			std::make_index_sequence<8>()
		);
	};

#if EMU_SIMD_USE_GENERIC_INT_REGISTERS
	template<bool I0_, bool I1_, bool I2_, bool I3_, bool I4_, bool I5_, bool I6_, bool I7_, bool I8_, bool I9_, bool I10_, bool I11_, bool I12_, bool I13_, bool I14_, bool I15_>
	struct _make_movemask<EmuSIMD::i128_generic, I0_, I1_, I2_, I3_, I4_, I5_, I6_, I7_, I8_, I9_, I10_, I11_, I12_, I13_, I14_, I15_>
	{
		static constexpr std::uint8_t value = _construct_movemask_value<std::uint16_t>
		(
			EmuCore::TMP::bool_sequence<I0_, I1_, I2_, I3_, I4_, I5_, I6_, I7_, I8_, I9_, I10_, I11_, I12_, I13_, I14_, I15_>(),
			std::make_index_sequence<16>()
		);
	};

	template<bool I0_, bool I1_, bool I2_, bool I3_, bool I4_, bool I5_, bool I6_, bool I7_>
	struct _make_movemask<EmuSIMD::i128_generic, I0_, I1_, I2_, I3_, I4_, I5_, I6_, I7_>
	{
		static constexpr std::uint8_t value = _construct_movemask_value<std::uint8_t>
		(
			EmuCore::TMP::bool_sequence<I0_, I1_, I2_, I3_, I4_, I5_, I6_, I7_>(),
			std::make_index_sequence<8>()
		);
	};

	template<bool I0_, bool I1_, bool I2_, bool I3_>
	struct _make_movemask<EmuSIMD::i128_generic, I0_, I1_, I2_, I3_>
	{
		static constexpr std::uint8_t value = _construct_movemask_value<std::uint8_t>
		(
			EmuCore::TMP::bool_sequence<I0_, I1_, I2_, I3_>(),
			std::make_index_sequence<4>()
		);
	};

	template<bool I0_, bool I1_>
	struct _make_movemask<EmuSIMD::i128_generic, I0_, I1_>
	{
		static constexpr std::uint8_t value = _construct_movemask_value<std::uint8_t>
		(
			EmuCore::TMP::bool_sequence<I0_, I1_>(),
			std::make_index_sequence<2>()
		);
	};

	template
	<
		bool I0_,  bool I1_,  bool I2_,  bool I3_,  bool I4_,  bool I5_,  bool I6_,  bool I7_,  bool I8_,  bool I9_,  bool I10_, bool I11_, bool I12_, bool I13_, bool I14_, bool I15_,
		bool I16_, bool I17_, bool I18_, bool I19_, bool I20_, bool I21_, bool I22_, bool I23_, bool I24_, bool I25_, bool I26_, bool I27_, bool I28_, bool I29_, bool I30_, bool I31_
	>
	struct _make_movemask<EmuSIMD::i256_generic, I0_, I1_, I2_, I3_, I4_, I5_, I6_, I7_, I8_, I9_, I10_, I11_, I12_, I13_, I14_, I15_, I16_, I17_, I18_, I19_, I20_, I21_, I22_, I23_, I24_, I25_, I26_, I27_, I28_, I29_, I30_, I31_>
	{
		static constexpr std::uint8_t value = _construct_movemask_value<std::uint32_t>
		(
			EmuCore::TMP::bool_sequence<I0_, I1_, I2_, I3_, I4_, I5_, I6_, I7_, I8_, I9_, I10_, I11_, I12_, I13_, I14_, I15_, I16_, I17_, I18_, I19_, I20_, I21_, I22_, I23_, I24_, I25_, I26_, I27_, I28_, I29_, I30_, I31_>(),
			std::make_index_sequence<32>()
		);
	};

	template<bool I0_, bool I1_, bool I2_, bool I3_, bool I4_, bool I5_, bool I6_, bool I7_, bool I8_, bool I9_, bool I10_, bool I11_, bool I12_, bool I13_, bool I14_, bool I15_>
	struct _make_movemask<EmuSIMD::i256_generic, I0_, I1_, I2_, I3_, I4_, I5_, I6_, I7_, I8_, I9_, I10_, I11_, I12_, I13_, I14_, I15_>
	{
		static constexpr std::uint8_t value = _construct_movemask_value<std::uint16_t>
		(
			EmuCore::TMP::bool_sequence<I0_, I1_, I2_, I3_, I4_, I5_, I6_, I7_, I8_, I9_, I10_, I11_, I12_, I13_, I14_, I15_>(),
			std::make_index_sequence<16>()
		);
	};

	template<bool I0_, bool I1_, bool I2_, bool I3_, bool I4_, bool I5_, bool I6_, bool I7_>
	struct _make_movemask<EmuSIMD::i256_generic, I0_, I1_, I2_, I3_, I4_, I5_, I6_, I7_>
	{
		static constexpr std::uint8_t value = _construct_movemask_value<std::uint8_t>
		(
			EmuCore::TMP::bool_sequence<I0_, I1_, I2_, I3_, I4_, I5_, I6_, I7_>(),
			std::make_index_sequence<8>()
		);
	};

	template<bool I0_, bool I1_, bool I2_, bool I3_>
	struct _make_movemask<EmuSIMD::i256_generic, I0_, I1_, I2_, I3_>
	{
		static constexpr std::uint8_t value = _construct_movemask_value<std::uint8_t>
		(
			EmuCore::TMP::bool_sequence<I0_, I1_, I2_, I3_>(),
			std::make_index_sequence<4>()
		);
	};

	template
	<
		bool I0_,  bool I1_,  bool I2_,  bool I3_,  bool I4_,  bool I5_,  bool I6_,  bool I7_,  bool I8_,  bool I9_,  bool I10_, bool I11_, bool I12_, bool I13_, bool I14_, bool I15_,
		bool I16_, bool I17_, bool I18_, bool I19_, bool I20_, bool I21_, bool I22_, bool I23_, bool I24_, bool I25_, bool I26_, bool I27_, bool I28_, bool I29_, bool I30_, bool I31_,
		bool I32_, bool I33_, bool I34_, bool I35_, bool I36_, bool I37_, bool I38_, bool I39_, bool I40_, bool I41_, bool I42_, bool I43_, bool I44_, bool I45_, bool I46_, bool I47_,
		bool I48_, bool I49_, bool I50_, bool I51_, bool I52_, bool I53_, bool I54_, bool I55_, bool I56_, bool I57_, bool I58_, bool I59_, bool I60_, bool I61_, bool I62_, bool I63_
	>
	struct _make_movemask
	<
		EmuSIMD::i512_generic,
		I0_,  I1_,  I2_,  I3_,  I4_,  I5_,  I6_,  I7_,  I8_,  I9_,  I10_, I11_, I12_, I13_, I14_, I15_, I16_, I17_, I18_, I19_, I20_, I21_, I22_, I23_, I24_, I25_, I26_, I27_, I28_, I29_, I30_, I31_,
		I32_, I33_, I34_, I35_, I36_, I37_, I38_, I39_, I40_, I41_, I42_, I43_, I44_, I45_, I46_, I47_, I48_, I49_, I50_, I51_, I52_, I53_, I54_, I55_, I56_, I57_, I58_, I59_, I60_, I61_, I62_, I63_
	>
	{
		static constexpr std::uint8_t value = _construct_movemask_value<std::uint32_t>
		(
			EmuCore::TMP::bool_sequence
			<
				I0_,  I1_,  I2_,  I3_,  I4_,  I5_,  I6_,  I7_,  I8_,  I9_,  I10_, I11_, I12_, I13_, I14_, I15_, I16_, I17_, I18_, I19_, I20_, I21_, I22_, I23_, I24_, I25_, I26_, I27_, I28_, I29_, I30_, I31_,
				I32_, I33_, I34_, I35_, I36_, I37_, I38_, I39_, I40_, I41_, I42_, I43_, I44_, I45_, I46_, I47_, I48_, I49_, I50_, I51_, I52_, I53_, I54_, I55_, I56_, I57_, I58_, I59_, I60_, I61_, I62_, I63_
			>(),
			std::make_index_sequence<64>()
		);
	};

	template
	<
		bool I0_,  bool I1_,  bool I2_,  bool I3_,  bool I4_,  bool I5_,  bool I6_,  bool I7_,  bool I8_,  bool I9_,  bool I10_, bool I11_, bool I12_, bool I13_, bool I14_, bool I15_,
		bool I16_, bool I17_, bool I18_, bool I19_, bool I20_, bool I21_, bool I22_, bool I23_, bool I24_, bool I25_, bool I26_, bool I27_, bool I28_, bool I29_, bool I30_, bool I31_
	>
	struct _make_movemask<EmuSIMD::i512_generic, I0_, I1_, I2_, I3_, I4_, I5_, I6_, I7_, I8_, I9_, I10_, I11_, I12_, I13_, I14_, I15_, I16_, I17_, I18_, I19_, I20_, I21_, I22_, I23_, I24_, I25_, I26_, I27_, I28_, I29_, I30_, I31_>
	{
		static constexpr std::uint8_t value = _construct_movemask_value<std::uint32_t>
		(
			EmuCore::TMP::bool_sequence<I0_, I1_, I2_, I3_, I4_, I5_, I6_, I7_, I8_, I9_, I10_, I11_, I12_, I13_, I14_, I15_, I16_, I17_, I18_, I19_, I20_, I21_, I22_, I23_, I24_, I25_, I26_, I27_, I28_, I29_, I30_, I31_>(),
			std::make_index_sequence<32>()
		);
	};

	template<bool I0_, bool I1_, bool I2_, bool I3_, bool I4_, bool I5_, bool I6_, bool I7_, bool I8_, bool I9_, bool I10_, bool I11_, bool I12_, bool I13_, bool I14_, bool I15_>
	struct _make_movemask<EmuSIMD::i512_generic, I0_, I1_, I2_, I3_, I4_, I5_, I6_, I7_, I8_, I9_, I10_, I11_, I12_, I13_, I14_, I15_>
	{
		static constexpr std::uint8_t value = _construct_movemask_value<std::uint16_t>
		(
			EmuCore::TMP::bool_sequence<I0_, I1_, I2_, I3_, I4_, I5_, I6_, I7_, I8_, I9_, I10_, I11_, I12_, I13_, I14_, I15_>(),
			std::make_index_sequence<16>()
		);
	};

	template<bool I0_, bool I1_, bool I2_, bool I3_, bool I4_, bool I5_, bool I6_, bool I7_>
	struct _make_movemask<EmuSIMD::i512_generic, I0_, I1_, I2_, I3_, I4_, I5_, I6_, I7_>
	{
		static constexpr std::uint8_t value = _construct_movemask_value<std::uint8_t>
		(
			EmuCore::TMP::bool_sequence<I0_, I1_, I2_, I3_, I4_, I5_, I6_, I7_>(),
			std::make_index_sequence<8>()
		);
	};
#else
	template<bool I0_, bool I1_, bool I2_, bool I3_, bool I4_, bool I5_, bool I6_, bool I7_, bool I8_, bool I9_, bool I10_, bool I11_, bool I12_, bool I13_, bool I14_, bool I15_>
	struct _make_movemask<EmuSIMD::i8x16, I0_, I1_, I2_, I3_, I4_, I5_, I6_, I7_, I8_, I9_, I10_, I11_, I12_, I13_, I14_, I15_>
	{
		static constexpr std::uint8_t value = _construct_movemask_value<std::uint16_t>
		(
			EmuCore::TMP::bool_sequence<I0_, I1_, I2_, I3_, I4_, I5_, I6_, I7_, I8_, I9_, I10_, I11_, I12_, I13_, I14_, I15_>(),
			std::make_index_sequence<16>()
		);
	};

	template<bool I0_, bool I1_, bool I2_, bool I3_, bool I4_, bool I5_, bool I6_, bool I7_, bool I8_, bool I9_, bool I10_, bool I11_, bool I12_, bool I13_, bool I14_, bool I15_>
	struct _make_movemask<EmuSIMD::u8x16, I0_, I1_, I2_, I3_, I4_, I5_, I6_, I7_, I8_, I9_, I10_, I11_, I12_, I13_, I14_, I15_>
	{
		static constexpr std::uint8_t value = _construct_movemask_value<std::uint16_t>
		(
			EmuCore::TMP::bool_sequence<I0_, I1_, I2_, I3_, I4_, I5_, I6_, I7_, I8_, I9_, I10_, I11_, I12_, I13_, I14_, I15_>(),
			std::make_index_sequence<16>()
		);
	};

	template<bool I0_, bool I1_, bool I2_, bool I3_, bool I4_, bool I5_, bool I6_, bool I7_>
	struct _make_movemask<EmuSIMD::i16x8, I0_, I1_, I2_, I3_, I4_, I5_, I6_, I7_>
	{
		static constexpr std::uint8_t value = _construct_movemask_value<std::uint8_t>
		(
			EmuCore::TMP::bool_sequence<I0_, I1_, I2_, I3_, I4_, I5_, I6_, I7_>(),
			std::make_index_sequence<8>()
		);
	};

	template<bool I0_, bool I1_, bool I2_, bool I3_, bool I4_, bool I5_, bool I6_, bool I7_>
	struct _make_movemask<EmuSIMD::u16x8, I0_, I1_, I2_, I3_, I4_, I5_, I6_, I7_>
	{
		static constexpr std::uint8_t value = _construct_movemask_value<std::uint8_t>
		(
			EmuCore::TMP::bool_sequence<I0_, I1_, I2_, I3_, I4_, I5_, I6_, I7_>(),
			std::make_index_sequence<8>()
		);
	};

	template<bool I0_, bool I1_, bool I2_, bool I3_>
	struct _make_movemask<EmuSIMD::i32x4, I0_, I1_, I2_, I3_>
	{
		static constexpr std::uint8_t value = _construct_movemask_value<std::uint8_t>
		(
			EmuCore::TMP::bool_sequence<I0_, I1_, I2_, I3_>(),
			std::make_index_sequence<4>()
		);
	};

	template<bool I0_, bool I1_, bool I2_, bool I3_>
	struct _make_movemask<EmuSIMD::u32x4, I0_, I1_, I2_, I3_>
	{
		static constexpr std::uint8_t value = _construct_movemask_value<std::uint8_t>
		(
			EmuCore::TMP::bool_sequence<I0_, I1_, I2_, I3_>(),
			std::make_index_sequence<4>()
		);
	};

	template<bool I0_, bool I1_>
	struct _make_movemask<EmuSIMD::i64x2, I0_, I1_>
	{
		static constexpr std::uint8_t value = _construct_movemask_value<std::uint8_t>
		(
			EmuCore::TMP::bool_sequence<I0_, I1_>(),
			std::make_index_sequence<2>()
		);
	};

	template<bool I0_, bool I1_>
	struct _make_movemask<EmuSIMD::u64x2, I0_, I1_>
	{
		static constexpr std::uint8_t value = _construct_movemask_value<std::uint8_t>
		(
			EmuCore::TMP::bool_sequence<I0_, I1_>(),
			std::make_index_sequence<2>()
		);
	};

	template
	<
		bool I0_,  bool I1_,  bool I2_,  bool I3_,  bool I4_,  bool I5_,  bool I6_,  bool I7_,  bool I8_,  bool I9_,  bool I10_, bool I11_, bool I12_, bool I13_, bool I14_, bool I15_,
		bool I16_, bool I17_, bool I18_, bool I19_, bool I20_, bool I21_, bool I22_, bool I23_, bool I24_, bool I25_, bool I26_, bool I27_, bool I28_, bool I29_, bool I30_, bool I31_
	>
	struct _make_movemask<EmuSIMD::i8x32, I0_, I1_, I2_, I3_, I4_, I5_, I6_, I7_, I8_, I9_, I10_, I11_, I12_, I13_, I14_, I15_, I16_, I17_, I18_, I19_, I20_, I21_, I22_, I23_, I24_, I25_, I26_, I27_, I28_, I29_, I30_, I31_>
	{
		static constexpr std::uint8_t value = _construct_movemask_value<std::uint32_t>
		(
			EmuCore::TMP::bool_sequence<I0_, I1_, I2_, I3_, I4_, I5_, I6_, I7_, I8_, I9_, I10_, I11_, I12_, I13_, I14_, I15_, I16_, I17_, I18_, I19_, I20_, I21_, I22_, I23_, I24_, I25_, I26_, I27_, I28_, I29_, I30_, I31_>(),
			std::make_index_sequence<32>()
		);
	};

	template
	<
		bool I0_,  bool I1_,  bool I2_,  bool I3_,  bool I4_,  bool I5_,  bool I6_,  bool I7_,  bool I8_,  bool I9_,  bool I10_, bool I11_, bool I12_, bool I13_, bool I14_, bool I15_,
		bool I16_, bool I17_, bool I18_, bool I19_, bool I20_, bool I21_, bool I22_, bool I23_, bool I24_, bool I25_, bool I26_, bool I27_, bool I28_, bool I29_, bool I30_, bool I31_
	>
	struct _make_movemask<EmuSIMD::u8x32, I0_, I1_, I2_, I3_, I4_, I5_, I6_, I7_, I8_, I9_, I10_, I11_, I12_, I13_, I14_, I15_, I16_, I17_, I18_, I19_, I20_, I21_, I22_, I23_, I24_, I25_, I26_, I27_, I28_, I29_, I30_, I31_>
	{
		static constexpr std::uint8_t value = _construct_movemask_value<std::uint32_t>
		(
			EmuCore::TMP::bool_sequence<I0_, I1_, I2_, I3_, I4_, I5_, I6_, I7_, I8_, I9_, I10_, I11_, I12_, I13_, I14_, I15_, I16_, I17_, I18_, I19_, I20_, I21_, I22_, I23_, I24_, I25_, I26_, I27_, I28_, I29_, I30_, I31_>(),
			std::make_index_sequence<32>()
		);
	};

	template<bool I0_, bool I1_, bool I2_, bool I3_, bool I4_, bool I5_, bool I6_, bool I7_, bool I8_, bool I9_, bool I10_, bool I11_, bool I12_, bool I13_, bool I14_, bool I15_>
	struct _make_movemask<EmuSIMD::i16x16, I0_, I1_, I2_, I3_, I4_, I5_, I6_, I7_, I8_, I9_, I10_, I11_, I12_, I13_, I14_, I15_>
	{
		static constexpr std::uint8_t value = _construct_movemask_value<std::uint16_t>
		(
			EmuCore::TMP::bool_sequence<I0_, I1_, I2_, I3_, I4_, I5_, I6_, I7_, I8_, I9_, I10_, I11_, I12_, I13_, I14_, I15_>(),
			std::make_index_sequence<16>()
		);
	};

	template<bool I0_, bool I1_, bool I2_, bool I3_, bool I4_, bool I5_, bool I6_, bool I7_, bool I8_, bool I9_, bool I10_, bool I11_, bool I12_, bool I13_, bool I14_, bool I15_>
	struct _make_movemask<EmuSIMD::u16x16, I0_, I1_, I2_, I3_, I4_, I5_, I6_, I7_, I8_, I9_, I10_, I11_, I12_, I13_, I14_, I15_>
	{
		static constexpr std::uint8_t value = _construct_movemask_value<std::uint16_t>
		(
			EmuCore::TMP::bool_sequence<I0_, I1_, I2_, I3_, I4_, I5_, I6_, I7_, I8_, I9_, I10_, I11_, I12_, I13_, I14_, I15_>(),
			std::make_index_sequence<16>()
		);
	};

	template<bool I0_, bool I1_, bool I2_, bool I3_, bool I4_, bool I5_, bool I6_, bool I7_>
	struct _make_movemask<EmuSIMD::i32x8, I0_, I1_, I2_, I3_, I4_, I5_, I6_, I7_>
	{
		static constexpr std::uint8_t value = _construct_movemask_value<std::uint8_t>
		(
			EmuCore::TMP::bool_sequence<I0_, I1_, I2_, I3_, I4_, I5_, I6_, I7_>(),
			std::make_index_sequence<8>()
		);
	};

	template<bool I0_, bool I1_, bool I2_, bool I3_, bool I4_, bool I5_, bool I6_, bool I7_>
	struct _make_movemask<EmuSIMD::u32x8, I0_, I1_, I2_, I3_, I4_, I5_, I6_, I7_>
	{
		static constexpr std::uint8_t value = _construct_movemask_value<std::uint8_t>
		(
			EmuCore::TMP::bool_sequence<I0_, I1_, I2_, I3_, I4_, I5_, I6_, I7_>(),
			std::make_index_sequence<8>()
		);
	};

	template<bool I0_, bool I1_, bool I2_, bool I3_>
	struct _make_movemask<EmuSIMD::i64x4, I0_, I1_, I2_, I3_>
	{
		static constexpr std::uint8_t value = _construct_movemask_value<std::uint8_t>
		(
			EmuCore::TMP::bool_sequence<I0_, I1_, I2_, I3_>(),
			std::make_index_sequence<4>()
		);
	};

	template<bool I0_, bool I1_, bool I2_, bool I3_>
	struct _make_movemask<EmuSIMD::u64x4, I0_, I1_, I2_, I3_>
	{
		static constexpr std::uint8_t value = _construct_movemask_value<std::uint8_t>
		(
			EmuCore::TMP::bool_sequence<I0_, I1_, I2_, I3_>(),
			std::make_index_sequence<4>()
		);
	};

	template
	<
		bool I0_,  bool I1_,  bool I2_,  bool I3_,  bool I4_,  bool I5_,  bool I6_,  bool I7_,  bool I8_,  bool I9_,  bool I10_, bool I11_, bool I12_, bool I13_, bool I14_, bool I15_,
		bool I16_, bool I17_, bool I18_, bool I19_, bool I20_, bool I21_, bool I22_, bool I23_, bool I24_, bool I25_, bool I26_, bool I27_, bool I28_, bool I29_, bool I30_, bool I31_,
		bool I32_, bool I33_, bool I34_, bool I35_, bool I36_, bool I37_, bool I38_, bool I39_, bool I40_, bool I41_, bool I42_, bool I43_, bool I44_, bool I45_, bool I46_, bool I47_,
		bool I48_, bool I49_, bool I50_, bool I51_, bool I52_, bool I53_, bool I54_, bool I55_, bool I56_, bool I57_, bool I58_, bool I59_, bool I60_, bool I61_, bool I62_, bool I63_
	>
	struct _make_movemask
	<
		EmuSIMD::i8x64,
		I0_,  I1_,  I2_,  I3_,  I4_,  I5_,  I6_,  I7_,  I8_,  I9_,  I10_, I11_, I12_, I13_, I14_, I15_, I16_, I17_, I18_, I19_, I20_, I21_, I22_, I23_, I24_, I25_, I26_, I27_, I28_, I29_, I30_, I31_,
		I32_, I33_, I34_, I35_, I36_, I37_, I38_, I39_, I40_, I41_, I42_, I43_, I44_, I45_, I46_, I47_, I48_, I49_, I50_, I51_, I52_, I53_, I54_, I55_, I56_, I57_, I58_, I59_, I60_, I61_, I62_, I63_
	>
	{
		static constexpr std::uint8_t value = _construct_movemask_value<std::uint32_t>
		(
			EmuCore::TMP::bool_sequence
			<
				I0_,  I1_,  I2_,  I3_,  I4_,  I5_,  I6_,  I7_,  I8_,  I9_,  I10_, I11_, I12_, I13_, I14_, I15_, I16_, I17_, I18_, I19_, I20_, I21_, I22_, I23_, I24_, I25_, I26_, I27_, I28_, I29_, I30_, I31_,
				I32_, I33_, I34_, I35_, I36_, I37_, I38_, I39_, I40_, I41_, I42_, I43_, I44_, I45_, I46_, I47_, I48_, I49_, I50_, I51_, I52_, I53_, I54_, I55_, I56_, I57_, I58_, I59_, I60_, I61_, I62_, I63_
			>(),
			std::make_index_sequence<64>()
		);
	};

	template
	<
		bool I0_,  bool I1_,  bool I2_,  bool I3_,  bool I4_,  bool I5_,  bool I6_,  bool I7_,  bool I8_,  bool I9_,  bool I10_, bool I11_, bool I12_, bool I13_, bool I14_, bool I15_,
		bool I16_, bool I17_, bool I18_, bool I19_, bool I20_, bool I21_, bool I22_, bool I23_, bool I24_, bool I25_, bool I26_, bool I27_, bool I28_, bool I29_, bool I30_, bool I31_,
		bool I32_, bool I33_, bool I34_, bool I35_, bool I36_, bool I37_, bool I38_, bool I39_, bool I40_, bool I41_, bool I42_, bool I43_, bool I44_, bool I45_, bool I46_, bool I47_,
		bool I48_, bool I49_, bool I50_, bool I51_, bool I52_, bool I53_, bool I54_, bool I55_, bool I56_, bool I57_, bool I58_, bool I59_, bool I60_, bool I61_, bool I62_, bool I63_
	>
	struct _make_movemask
	<
		EmuSIMD::u8x64,
		I0_,  I1_,  I2_,  I3_,  I4_,  I5_,  I6_,  I7_,  I8_,  I9_,  I10_, I11_, I12_, I13_, I14_, I15_, I16_, I17_, I18_, I19_, I20_, I21_, I22_, I23_, I24_, I25_, I26_, I27_, I28_, I29_, I30_, I31_,
		I32_, I33_, I34_, I35_, I36_, I37_, I38_, I39_, I40_, I41_, I42_, I43_, I44_, I45_, I46_, I47_, I48_, I49_, I50_, I51_, I52_, I53_, I54_, I55_, I56_, I57_, I58_, I59_, I60_, I61_, I62_, I63_
	>
	{
		static constexpr std::uint8_t value = _construct_movemask_value<std::uint32_t>
		(
			EmuCore::TMP::bool_sequence
			<
				I0_,  I1_,  I2_,  I3_,  I4_,  I5_,  I6_,  I7_,  I8_,  I9_,  I10_, I11_, I12_, I13_, I14_, I15_, I16_, I17_, I18_, I19_, I20_, I21_, I22_, I23_, I24_, I25_, I26_, I27_, I28_, I29_, I30_, I31_,
				I32_, I33_, I34_, I35_, I36_, I37_, I38_, I39_, I40_, I41_, I42_, I43_, I44_, I45_, I46_, I47_, I48_, I49_, I50_, I51_, I52_, I53_, I54_, I55_, I56_, I57_, I58_, I59_, I60_, I61_, I62_, I63_
			>(),
			std::make_index_sequence<64>()
		);
	};

	template
	<
		bool I0_,  bool I1_,  bool I2_,  bool I3_,  bool I4_,  bool I5_,  bool I6_,  bool I7_,  bool I8_,  bool I9_,  bool I10_, bool I11_, bool I12_, bool I13_, bool I14_, bool I15_,
		bool I16_, bool I17_, bool I18_, bool I19_, bool I20_, bool I21_, bool I22_, bool I23_, bool I24_, bool I25_, bool I26_, bool I27_, bool I28_, bool I29_, bool I30_, bool I31_
	>
	struct _make_movemask<EmuSIMD::i16x32, I0_, I1_, I2_, I3_, I4_, I5_, I6_, I7_, I8_, I9_, I10_, I11_, I12_, I13_, I14_, I15_, I16_, I17_, I18_, I19_, I20_, I21_, I22_, I23_, I24_, I25_, I26_, I27_, I28_, I29_, I30_, I31_>
	{
		static constexpr std::uint8_t value = _construct_movemask_value<std::uint32_t>
		(
			EmuCore::TMP::bool_sequence<I0_, I1_, I2_, I3_, I4_, I5_, I6_, I7_, I8_, I9_, I10_, I11_, I12_, I13_, I14_, I15_, I16_, I17_, I18_, I19_, I20_, I21_, I22_, I23_, I24_, I25_, I26_, I27_, I28_, I29_, I30_, I31_>(),
			std::make_index_sequence<32>()
		);
	};

	template
	<
		bool I0_,  bool I1_,  bool I2_,  bool I3_,  bool I4_,  bool I5_,  bool I6_,  bool I7_,  bool I8_,  bool I9_,  bool I10_, bool I11_, bool I12_, bool I13_, bool I14_, bool I15_,
		bool I16_, bool I17_, bool I18_, bool I19_, bool I20_, bool I21_, bool I22_, bool I23_, bool I24_, bool I25_, bool I26_, bool I27_, bool I28_, bool I29_, bool I30_, bool I31_
	>
	struct _make_movemask<EmuSIMD::u16x32, I0_, I1_, I2_, I3_, I4_, I5_, I6_, I7_, I8_, I9_, I10_, I11_, I12_, I13_, I14_, I15_, I16_, I17_, I18_, I19_, I20_, I21_, I22_, I23_, I24_, I25_, I26_, I27_, I28_, I29_, I30_, I31_>
	{
		static constexpr std::uint8_t value = _construct_movemask_value<std::uint32_t>
		(
			EmuCore::TMP::bool_sequence<I0_, I1_, I2_, I3_, I4_, I5_, I6_, I7_, I8_, I9_, I10_, I11_, I12_, I13_, I14_, I15_, I16_, I17_, I18_, I19_, I20_, I21_, I22_, I23_, I24_, I25_, I26_, I27_, I28_, I29_, I30_, I31_>(),
			std::make_index_sequence<32>()
		);
	};

	template<bool I0_, bool I1_, bool I2_, bool I3_, bool I4_, bool I5_, bool I6_, bool I7_, bool I8_, bool I9_, bool I10_, bool I11_, bool I12_, bool I13_, bool I14_, bool I15_>
	struct _make_movemask<EmuSIMD::i32x16, I0_, I1_, I2_, I3_, I4_, I5_, I6_, I7_, I8_, I9_, I10_, I11_, I12_, I13_, I14_, I15_>
	{
		static constexpr std::uint8_t value = _construct_movemask_value<std::uint16_t>
		(
			EmuCore::TMP::bool_sequence<I0_, I1_, I2_, I3_, I4_, I5_, I6_, I7_, I8_, I9_, I10_, I11_, I12_, I13_, I14_, I15_>(),
			std::make_index_sequence<16>()
		);
	};

	template<bool I0_, bool I1_, bool I2_, bool I3_, bool I4_, bool I5_, bool I6_, bool I7_, bool I8_, bool I9_, bool I10_, bool I11_, bool I12_, bool I13_, bool I14_, bool I15_>
	struct _make_movemask<EmuSIMD::u32x16, I0_, I1_, I2_, I3_, I4_, I5_, I6_, I7_, I8_, I9_, I10_, I11_, I12_, I13_, I14_, I15_>
	{
		static constexpr std::uint8_t value = _construct_movemask_value<std::uint16_t>
		(
			EmuCore::TMP::bool_sequence<I0_, I1_, I2_, I3_, I4_, I5_, I6_, I7_, I8_, I9_, I10_, I11_, I12_, I13_, I14_, I15_>(),
			std::make_index_sequence<16>()
		);
	};

	template<bool I0_, bool I1_, bool I2_, bool I3_, bool I4_, bool I5_, bool I6_, bool I7_>
	struct _make_movemask<EmuSIMD::i64x8, I0_, I1_, I2_, I3_, I4_, I5_, I6_, I7_>
	{
		static constexpr std::uint8_t value = _construct_movemask_value<std::uint8_t>
		(
			EmuCore::TMP::bool_sequence<I0_, I1_, I2_, I3_, I4_, I5_, I6_, I7_>(),
			std::make_index_sequence<8>()
		);
	};

	template<bool I0_, bool I1_, bool I2_, bool I3_, bool I4_, bool I5_, bool I6_, bool I7_>
	struct _make_movemask<EmuSIMD::u64x8, I0_, I1_, I2_, I3_, I4_, I5_, I6_, I7_>
	{
		static constexpr std::uint8_t value = _construct_movemask_value<std::uint8_t>
		(
			EmuCore::TMP::bool_sequence<I0_, I1_, I2_, I3_, I4_, I5_, I6_, I7_>(),
			std::make_index_sequence<8>()
		);
	};
#endif

	template<class MakeMovemaskInstance_>
	struct _is_valid_make_movemask_instance
	{
		static constexpr bool value = false;
	};
	template<class Register_, bool...ActiveIndices_>
	struct _is_valid_make_movemask_instance<_make_movemask<Register_, ActiveIndices_...>>
	{
		static constexpr bool value = EmuCore::TMP::has_static_value<_make_movemask<Register_, ActiveIndices_...>>::value;
	};
}

#endif
