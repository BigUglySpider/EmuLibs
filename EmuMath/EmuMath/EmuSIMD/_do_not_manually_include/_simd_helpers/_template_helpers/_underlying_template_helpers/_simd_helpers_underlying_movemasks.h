#ifndef EMU_SIMD_HELPERS_UNDERLYING_MOVEMASKS_H_INC_
#define EMU_SIMD_HELPERS_UNDERLYING_MOVEMASKS_H_INC_ 1

#include "_common_underlying_simd_template_helper_includes.h"

namespace EmuSIMD::_underlying_simd_helpers
{
	template<class Register_, bool...ActiveIndices_>
	struct _make_movemask
	{
	};

	template<bool I0_, bool I1_, bool I2_, bool I3_>
	struct _make_movemask<__m128, I0_, I1_, I2_, I3_>
	{
	private:
		template<std::size_t Index_>
		[[nodiscard]] static constexpr inline int _bit(bool bit_) { return static_cast<int>(bit_) << Index_; };

	public:
		static constexpr int value = _bit<3>(I3_) | _bit<2>(I2_) | _bit<1>(I1_) | _bit<0>(I0_);
	};
	template<bool I_>
	struct _make_movemask<__m128, I_> : public _make_movemask<__m128, I_, I_, I_, I_>
	{
	};

	template<bool I0_, bool I1_, bool I2_, bool I3_, bool I4_, bool I5_, bool I6_, bool I7_>
	struct _make_movemask<__m256, I0_, I1_, I2_, I3_, I4_, I5_, I6_, I7_>
	{
	private:
		template<std::size_t Index_>
		[[nodiscard]] static constexpr inline int _bit(bool bit_) { return static_cast<int>(bit_) << Index_; };

	public:
		static constexpr int value = _bit<7>(I7_) | _bit<6>(I6_) | _bit<5>(I5_) | _bit<4>(I4_) | _bit<3>(I3_) | _bit<2>(I2_) | _bit<1>(I1_) | _bit<0>(I0_);
	};
	template<bool I_>
	struct _make_movemask<__m256, I_> : public _make_movemask<__m256, I_, I_, I_, I_, I_, I_, I_, I_>
	{
	};

	template
	<
		bool I0_, bool I1_, bool I2_,  bool I3_,  bool I4_,  bool I5_,  bool I6_,  bool I7_,
		bool I8_, bool I9_, bool I10_, bool I11_, bool I12_, bool I13_, bool I14_, bool I15_
	>
	struct _make_movemask<__m512, I0_, I1_, I2_, I3_, I4_, I5_, I6_, I7_, I8_, I9_, I10_, I11_, I12_, I13_, I14_, I15_>
	{
	private:
		template<std::size_t Index_>
		[[nodiscard]] static constexpr inline int _bit(bool bit_) { return static_cast<int>(bit_) << Index_; };

	public:
		static constexpr int value = 
		(
			_bit<15>(I15_) | _bit<14>(I14_) | _bit<13>(I13_) | _bit<12>(I12_) | _bit<11>(I11_) | _bit<10>(I10_) | _bit<9>(I9_) | _bit<8>(I8_) |
			_bit<7>(I7_)   | _bit<6>(I6_)   | _bit<5>(I5_)   | _bit<4>(I4_)   | _bit<3>(I3_)   | _bit<2>(I2_)   | _bit<1>(I1_) | _bit<0>(I0_)
		);
	};
	template<bool I_>
	struct _make_movemask<__m512, I_> : public _make_movemask<__m512, I_, I_, I_, I_, I_, I_, I_, I_, I_, I_, I_, I_, I_, I_, I_, I_>
	{
	};

	template<bool I0_, bool I1_>
	struct _make_movemask<__m128d, I0_, I1_>
	{
	private:
		template<std::size_t Index_>
		[[nodiscard]] static constexpr inline int _bit(bool bit_) { return static_cast<int>(bit_) << Index_; };

	public:
		static constexpr int value = _bit<1>(I1_) | _bit<0>(I0_);
	};
	template<bool I_>
	struct _make_movemask<__m128d, I_> : public _make_movemask<__m128d, I_, I_>
	{
	};

	template<bool I0_, bool I1_, bool I2_, bool I3_>
	struct _make_movemask<__m256d, I0_, I1_, I2_, I3_>
	{
	private:
		template<std::size_t Index_>
		[[nodiscard]] static constexpr inline int _bit(bool bit_) { return static_cast<int>(bit_) << Index_; };

	public:
		static constexpr int value = _bit<3>(I3_) | _bit<2>(I2_) | _bit<1>(I1_) | _bit<0>(I0_);
	};
	template<bool I_>
	struct _make_movemask<__m256d, I_> : public _make_movemask<__m256d, I_, I_, I_, I_>
	{
	};

	template<bool I0_, bool I1_, bool I2_, bool I3_, bool I4_, bool I5_, bool I6_, bool I7_>
	struct _make_movemask<__m512d, I0_, I1_, I2_, I3_, I4_, I5_, I6_, I7_>
	{
	private:
		template<std::size_t Index_>
		[[nodiscard]] static constexpr inline int _bit(bool bit_) { return static_cast<int>(bit_) << Index_; };

	public:
		static constexpr int value = _bit<7>(I7_) | _bit<6>(I6_) | _bit<5>(I5_) | _bit<4>(I4_) | _bit<3>(I3_) | _bit<2>(I2_) | _bit<1>(I1_) | _bit<0>(I0_);
	};
	template<bool I_>
	struct _make_movemask<__m512d, I_> : public _make_movemask<__m512d, I_, I_, I_, I_, I_, I_, I_, I_>
	{
	};

	template
	<
		bool I0_, bool I1_, bool I2_,  bool I3_,  bool I4_,  bool I5_,  bool I6_,  bool I7_,
		bool I8_, bool I9_, bool I10_, bool I11_, bool I12_, bool I13_, bool I14_, bool I15_
	>
	struct _make_movemask<__m128i, I0_, I1_, I2_, I3_, I4_, I5_, I6_, I7_, I8_, I9_, I10_, I11_, I12_, I13_, I14_, I15_>
	{
	private:
		template<std::size_t Index_>
		[[nodiscard]] static constexpr inline int _bit(bool bit_) { return static_cast<int>(bit_) << Index_; };

	public:
		static constexpr int value = 
		(
			_bit<15>(I15_) | _bit<14>(I14_) | _bit<13>(I13_) | _bit<12>(I12_) | _bit<11>(I11_) | _bit<10>(I10_) | _bit<9>(I9_) | _bit<8>(I8_) |
			_bit<7>(I7_)   | _bit<6>(I6_)   | _bit<5>(I5_)   | _bit<4>(I4_)   | _bit<3>(I3_)   | _bit<2>(I2_)   | _bit<1>(I1_) | _bit<0>(I0_)
		);
	};
	template<bool I0_, bool I1_, bool I2_, bool I3_, bool I4_, bool I5_, bool I6_, bool I7_>
	struct _make_movemask<__m128i, I0_, I1_, I2_, I3_, I4_, I5_, I6_, I7_> : 
		public _make_movemask<__m128i, I0_, I0_, I1_, I1_, I2_, I2_, I3_, I3_, I4_, I4_, I5_, I5_, I6_, I6_, I7_, I7_>
	{
	};
	template<bool I0_, bool I1_, bool I2_, bool I3_>
	struct _make_movemask<__m128i, I0_, I1_, I2_, I3_> : public _make_movemask<__m128i, I0_, I0_, I0_, I0_, I1_, I1_, I1_, I1_, I2_, I2_, I2_, I2_, I3_, I3_, I3_, I3_>
	{
	};
	template<bool I0_, bool I1_>
	struct _make_movemask<__m128i, I0_, I1_> : public _make_movemask<__m128i, I0_, I0_, I0_, I0_, I0_, I0_, I0_, I0_, I1_, I1_, I1_, I1_, I1_, I1_, I1_, I1_>
	{
	};
	template<bool I_>
	struct _make_movemask<__m128i, I_> : public _make_movemask<__m128i, I_, I_, I_, I_, I_, I_, I_, I_, I_, I_, I_, I_, I_, I_, I_, I_>
	{
	};

	template
	<
		bool I0_,  bool I1_,  bool I2_,  bool I3_,  bool I4_,  bool I5_,  bool I6_,  bool I7_,
		bool I8_,  bool I9_,  bool I10_, bool I11_, bool I12_, bool I13_, bool I14_, bool I15_,
		bool I16_, bool I17_, bool I18_, bool I19_, bool I20_, bool I21_, bool I22_, bool I23_,
		bool I24_, bool I25_, bool I26_, bool I27_, bool I28_, bool I29_, bool I30_, bool I31_
	>
	struct _make_movemask
	<
		__m256i,
		I0_,  I1_,  I2_,  I3_,  I4_,  I5_,  I6_,  I7_,  I8_,  I9_,  I10_, I11_, I12_, I13_, I14_, I15_,
		I16_, I17_, I18_, I19_, I20_, I21_, I22_, I23_, I24_, I25_, I26_, I27_, I28_, I29_, I30_, I31_
	>
	{
	private:
		template<std::size_t Index_>
		[[nodiscard]] static constexpr inline int _bit(bool bit_) { return static_cast<int>(bit_) << Index_; };

	public:
		static constexpr int value = 
		(
			_bit<31>(I31_) | _bit<30>(I30_) | _bit<29>(I29_) | _bit<28>(I28_) | _bit<27>(I27_) | _bit<26>(I26_) | _bit<25>(I25_) | _bit<24>(I24_) |
			_bit<23>(I23_) | _bit<22>(I22_) | _bit<21>(I21_) | _bit<20>(I20_) | _bit<19>(I19_) | _bit<18>(I18_) | _bit<17>(I17_) | _bit<16>(I16_) |
			_bit<15>(I15_) | _bit<14>(I14_) | _bit<13>(I13_) | _bit<12>(I12_) | _bit<11>(I11_) | _bit<10>(I10_) | _bit<9>(I9_)   | _bit<8>(I8_)   |
			_bit<7>(I7_)   | _bit<6>(I6_)   | _bit<5>(I5_)   | _bit<4>(I4_)   | _bit<3>(I3_)   | _bit<2>(I2_)   | _bit<1>(I1_)   | _bit<0>(I0_)
		);
	};
	template
	<
		bool I0_, bool I1_, bool I2_,  bool I3_,  bool I4_,  bool I5_,  bool I6_,  bool I7_,
		bool I8_, bool I9_, bool I10_, bool I11_, bool I12_, bool I13_, bool I14_, bool I15_
	>
	struct _make_movemask<__m256i, I0_, I1_, I2_, I3_, I4_, I5_, I6_, I7_, I8_, I9_, I10_, I11_, I12_, I13_, I14_, I15_> : 
		public _make_movemask
		<
			__m256i,
			I0_,  I0_,  I1_,  I1_,  I2_,  I2_,  I3_,  I3_,  I4_,  I4_,  I5_,  I5_,  I6_,  I6_,  I7_,  I7_,
			I8_,  I8_,  I9_,  I9_,  I10_, I10_, I11_, I11_, I12_, I12_, I13_, I13_, I14_, I14_, I15_, I15_
		>
	{
	};
	template<bool I0_, bool I1_, bool I2_, bool I3_, bool I4_, bool I5_, bool I6_, bool I7_>
	struct _make_movemask<__m256i, I0_, I1_, I2_, I3_, I4_, I5_, I6_, I7_> : 
		public _make_movemask
		<
			__m256i,
			I0_, I0_, I0_, I0_, I1_, I1_, I1_, I1_, I2_, I2_, I2_, I2_, I3_, I3_, I3_, I3_,
			I4_, I4_, I4_, I4_, I5_, I5_, I5_, I5_, I6_, I6_, I6_, I6_, I7_, I7_, I7_, I7_
		>
	{
	};
	template<bool I0_, bool I1_, bool I2_, bool I3_>
	struct _make_movemask<__m256i, I0_, I1_, I2_, I3_> : 
		public _make_movemask
		<
			__m256i,
			I0_, I0_, I0_, I0_, I0_, I0_, I0_, I0_, I1_, I1_, I1_, I1_, I1_, I1_, I1_, I1_,
			I2_, I2_, I2_, I2_, I2_, I2_, I2_, I2_, I3_, I3_, I3_, I3_, I3_, I3_, I3_, I3_
		>
	{
	};
	template<bool I_>
	struct _make_movemask<__m256i, I_> : 
		public _make_movemask
		<
			__m256i,
			I_, I_, I_, I_, I_, I_, I_, I_, I_, I_, I_, I_, I_, I_, I_, I_,
			I_, I_, I_, I_, I_, I_, I_, I_, I_, I_, I_, I_, I_, I_, I_, I_
		>
	{
	};

	template
	<
		bool I0_,  bool I1_,  bool I2_,  bool I3_,  bool I4_,  bool I5_,  bool I6_,  bool I7_,
		bool I8_,  bool I9_,  bool I10_, bool I11_, bool I12_, bool I13_, bool I14_, bool I15_,
		bool I16_, bool I17_, bool I18_, bool I19_, bool I20_, bool I21_, bool I22_, bool I23_,
		bool I24_, bool I25_, bool I26_, bool I27_, bool I28_, bool I29_, bool I30_, bool I31_,
		bool I32_, bool I33_, bool I34_, bool I35_, bool I36_, bool I37_, bool I38_, bool I39_,
		bool I40_, bool I41_, bool I42_, bool I43_, bool I44_, bool I45_, bool I46_, bool I47_,
		bool I48_, bool I49_, bool I50_, bool I51_, bool I52_, bool I53_, bool I54_, bool I55_,
		bool I56_, bool I57_, bool I58_, bool I59_, bool I60_, bool I61_, bool I62_, bool I63_
	>
	struct _make_movemask
	<
		__m512i,
		I0_,  I1_,  I2_,  I3_,  I4_,  I5_,  I6_,  I7_,  I8_,  I9_,  I10_, I11_, I12_, I13_, I14_, I15_,
		I16_, I17_, I18_, I19_, I20_, I21_, I22_, I23_, I24_, I25_, I26_, I27_, I28_, I29_, I30_, I31_,
		I32_, I33_, I34_, I35_, I36_, I37_, I38_, I39_, I40_, I41_, I42_, I43_, I44_, I45_, I46_, I47_,
		I48_, I49_, I50_, I51_, I52_, I53_, I54_, I55_, I56_, I57_, I58_, I59_, I60_, I61_, I62_, I63_
	>
	{
	private:
		template<std::size_t Index_>
		[[nodiscard]] static constexpr inline std::uint64_t _bit(bool bit_) { return static_cast<std::uint64_t>(bit_) << Index_; };

	public:
		static constexpr std::uint64_t value = 
		(
			_bit<63>(I63_) | _bit<62>(I62_) | _bit<61>(I61_) | _bit<60>(I60_) | _bit<59>(I59_) | _bit<58>(I58_) | _bit<57>(I57_) | _bit<56>(I56_) |
			_bit<55>(I55_) | _bit<54>(I54_) | _bit<53>(I53_) | _bit<52>(I52_) | _bit<51>(I51_) | _bit<50>(I50_) | _bit<49>(I49_) | _bit<48>(I48_) |
			_bit<47>(I47_) | _bit<46>(I46_) | _bit<45>(I45_) | _bit<44>(I44_) | _bit<43>(I43_) | _bit<42>(I42_) | _bit<41>(I41_) | _bit<40>(I40_) |
			_bit<39>(I39_) | _bit<38>(I38_) | _bit<37>(I37_) | _bit<36>(I36_) | _bit<35>(I35_) | _bit<34>(I34_) | _bit<33>(I33_) | _bit<32>(I32_) |
			_bit<31>(I31_) | _bit<30>(I30_) | _bit<29>(I29_) | _bit<28>(I28_) | _bit<27>(I27_) | _bit<26>(I26_) | _bit<25>(I25_) | _bit<24>(I24_) |
			_bit<23>(I23_) | _bit<22>(I22_) | _bit<21>(I21_) | _bit<20>(I20_) | _bit<19>(I19_) | _bit<18>(I18_) | _bit<17>(I17_) | _bit<16>(I16_) |
			_bit<15>(I15_) | _bit<14>(I14_) | _bit<13>(I13_) | _bit<12>(I12_) | _bit<11>(I11_) | _bit<10>(I10_) | _bit<9>(I9_)   | _bit<8>(I8_)   |
			_bit<7>(I7_)   | _bit<6>(I6_)   | _bit<5>(I5_)   | _bit<4>(I4_)   | _bit<3>(I3_)   | _bit<2>(I2_)   | _bit<1>(I1_)   | _bit<0>(I0_)
		);
	};
	template
	<
		bool I0_,  bool I1_,  bool I2_,  bool I3_,  bool I4_,  bool I5_,  bool I6_,  bool I7_,
		bool I8_,  bool I9_,  bool I10_, bool I11_, bool I12_, bool I13_, bool I14_, bool I15_,
		bool I16_, bool I17_, bool I18_, bool I19_, bool I20_, bool I21_, bool I22_, bool I23_,
		bool I24_, bool I25_, bool I26_, bool I27_, bool I28_, bool I29_, bool I30_, bool I31_
	>
	struct _make_movemask
	<
		__m512i,
		I0_,  I0_,  I1_,  I1_,  I2_,  I2_,  I3_,  I3_,  I4_,  I4_,  I5_,  I5_,  I6_,  I6_,  I7_,  I7_,
		I8_,  I8_,  I9_,  I9_,  I10_, I10_, I11_, I11_, I12_, I12_, I13_, I13_, I14_, I14_, I15_, I15_,
		I16_, I16_, I17_, I17_, I18_, I18_, I19_, I19_, I20_, I20_, I21_, I21_, I22_, I22_, I23_, I23_,
		I24_, I24_, I25_, I25_, I26_, I26_, I27_, I27_, I28_, I28_, I29_, I29_, I30_, I30_, I31_, I31_
	>
	{
	};
	template
	<
		bool I0_, bool I1_, bool I2_,  bool I3_,  bool I4_,  bool I5_,  bool I6_,  bool I7_,
		bool I8_, bool I9_, bool I10_, bool I11_, bool I12_, bool I13_, bool I14_, bool I15_
	>
	struct _make_movemask<__m512i, I0_, I1_, I2_, I3_, I4_, I5_, I6_, I7_, I8_, I9_, I10_, I11_, I12_, I13_, I14_, I15_> :
		public _make_movemask
		<
			__m512i,
			I0_,  I0_,  I0_,  I0_,  I1_,  I1_,  I1_,  I1_,  I2_,  I2_,  I2_,  I2_,  I3_,  I3_,  I3_,  I3_,
			I4_,  I4_,  I4_,  I4_,  I5_,  I5_,  I5_,  I5_,  I6_,  I6_,  I6_,  I6_,  I7_,  I7_,  I7_,  I7_,
			I8_,  I8_,  I8_,  I8_,  I9_,  I9_,  I9_,  I9_,  I10_, I10_, I10_, I10_, I11_, I11_, I11_, I11_,
			I12_, I12_, I12_, I12_, I13_, I13_, I13_, I13_, I14_, I14_, I14_, I14_, I15_, I15_, I15_, I15_
		>
	{
	};
	template<bool I0_, bool I1_, bool I2_, bool I3_, bool I4_, bool I5_, bool I6_, bool I7_>
	struct _make_movemask<__m512i, I0_, I1_, I2_, I3_, I4_, I5_, I6_, I7_> :
		public _make_movemask
		<
			__m512i,
			I0_, I0_, I0_, I0_, I0_, I0_, I0_, I0_, I1_, I1_, I1_, I1_, I1_, I1_, I1_, I1_,
			I2_, I2_, I2_, I2_, I2_, I2_, I2_, I2_, I3_, I3_, I3_, I3_, I3_, I3_, I3_, I3_,
			I4_, I4_, I4_, I4_, I4_, I4_, I4_, I4_, I5_, I5_, I5_, I5_, I5_, I5_, I5_, I5_,
			I6_, I6_, I6_, I6_, I6_, I6_, I6_, I6_, I7_, I7_, I7_, I7_, I7_, I7_, I7_, I7_
		>
	{
	};

	template<class MakeMovemaskInstance_>
	struct _is_valid_make_movemask_instance
	{
		static constexpr bool value = false;
	};
	template<class Register_, bool...ActiveIndices_>
	struct _is_valid_make_movemask_instance<_make_movemask<Register_, ActiveIndices_...>>
	{
		static constexpr bool value = EmuCore::TMPHelpers::has_static_value<_make_movemask<Register_, ActiveIndices_...>>::value;
	};
}

#endif
