#ifndef EMU_SIMD_HELPERS_UNDERLYING_SHUFFLE_MASKS_H_INC_
#define EMU_SIMD_HELPERS_UNDERLYING_SHUFFLE_MASKS_H_INC_ 1

#include "_common_underlying_simd_template_helper_includes.h"
#include "../../../../../EmuCore/TMPHelpers/TypeComparators.h"

namespace EmuSIMD::_underlying_simd_helpers
{
	template<class Register_, std::size_t...Indices_>
	struct _shuffle_mask
	{
	};

#pragma region SHUFFLE_MASKS_128
	template<std::size_t I0_, std::size_t I1_, std::size_t I2_, std::size_t I3_>
	struct _shuffle_mask<EmuSIMD::f32x4, I0_, I1_, I2_, I3_>
	{
		static constexpr unsigned int value = static_cast<unsigned int>(((I3_ & 0b11) << 6) | ((I2_ & 0b11) << 4) | ((I1_ & 0b11) << 2) | (I0_ & 0b11));
		[[nodiscard]] static constexpr inline unsigned int get()
		{
			return value;
		}
	};
	template<std::size_t I_>
	struct _shuffle_mask<EmuSIMD::f32x4, I_> : public _shuffle_mask<EmuSIMD::f32x4, I_, I_, I_, I_>
	{
	};

	template<std::size_t I0_, std::size_t I1_>
	struct _shuffle_mask<EmuSIMD::f64x2, I0_, I1_>
	{
		static constexpr int value = static_cast<int>(((I1_ & 0b1) << 1) | (I0_ & 0b1));
		[[nodiscard]] static constexpr inline int get()
		{
			return value;
		}
	};
	template<std::size_t I_>
	struct _shuffle_mask<EmuSIMD::f64x2, I_> : public _shuffle_mask<EmuSIMD::f64x2, I_, I_>
	{
	};

	template<std::size_t I0_, std::size_t I1_, std::size_t I2_, std::size_t I3_>
	struct _shuffle_mask<EmuSIMD::i128_generic, I0_, I1_, I2_, I3_>
	{
		static constexpr int value = static_cast<int>(((I3_ & 0b11) << 6) | ((I2_ & 0b11) << 4) | ((I1_ & 0b11) << 2) | (I0_ & 0b11));
		[[nodiscard]] static constexpr inline int get()
		{
			return value;
		}
	};

	template<std::size_t I0_, std::size_t I1_, std::size_t I2_, std::size_t I3_, std::size_t I4_, std::size_t I5_, std::size_t I6_, std::size_t I7_>
	struct _shuffle_mask<EmuSIMD::i128_generic, I0_, I1_, I2_, I3_, I4_, I5_, I6_, I7_>
	{
	private:
		using _underlying_shuffle = _shuffle_mask
		<
			EmuSIMD::i128_generic,
			I0_ * 2, (I0_ * 2) + 1,
			I1_ * 2, (I1_ * 2) + 1,
			I2_ * 2, (I2_ * 2) + 1,
			I3_ * 2, (I3_ * 2) + 1,
			I4_ * 2, (I4_ * 2) + 1,
			I5_ * 2, (I5_ * 2) + 1,
			I6_ * 2, (I6_ * 2) + 1,
			I7_ * 2, (I7_ * 2) + 1
		>;

	public:
		[[nodiscard]] static inline auto get()
		{
			return _underlying_shuffle::get();
		}
	};

	template
	<
		std::size_t I0_, std::size_t I1_, std::size_t I2_, std::size_t I3_, std::size_t I4_, std::size_t I5_, std::size_t I6_, std::size_t I7_,
		std::size_t I8_, std::size_t I9_, std::size_t I10_, std::size_t I11_, std::size_t I12_, std::size_t I13_, std::size_t I14_, std::size_t I15_
	>
	struct _shuffle_mask<EmuSIMD::i128_generic, I0_, I1_, I2_, I3_, I4_, I5_, I6_, I7_, I8_, I9_, I10_, I11_, I12_, I13_, I14_, I15_>
	{
	private:
		static constexpr char _mask = 0b1111;

		template<std::size_t Index_>
		static constexpr char _val = 0;
		template<>
		static constexpr char _val<0> = I0_ & _mask;
		template<>
		static constexpr char _val<1> = I1_ & _mask;
		template<>
		static constexpr char _val<2> = I2_ & _mask;
		template<>
		static constexpr char _val<3> = I3_ & _mask;
		template<>
		static constexpr char _val<4> = I4_ & _mask;
		template<>
		static constexpr char _val<5> = I5_ & _mask;
		template<>
		static constexpr char _val<6> = I6_ & _mask;
		template<>
		static constexpr char _val<7> = I7_ & _mask;
		template<>
		static constexpr char _val<8> = I8_ & _mask;
		template<>
		static constexpr char _val<9> = I9_ & _mask;
		template<>
		static constexpr char _val<10> = I10_ & _mask;
		template<>
		static constexpr char _val<11> = I11_ & _mask;
		template<>
		static constexpr char _val<12> = I12_ & _mask;
		template<>
		static constexpr char _val<13> = I13_ & _mask;
		template<>
		static constexpr char _val<14> = I14_ & _mask;
		template<>
		static constexpr char _val<15> = I15_ & _mask;

	public:
		[[nodiscard]] static inline EmuSIMD::i128_generic get()
		{
			return _mm_set_epi8
			(
				_val<15>, _val<14>, _val<13>, _val<12>, _val<11>, _val<10>, _val<9>, _val<8>,
				_val<7>, _val<6>, _val<5>, _val<4>, _val<3>, _val<2>, _val<1>, _val<0>
			);
		}
	};
#pragma endregion

#pragma region SHUFFLE_MASKS_256
	template<std::size_t I0_, std::size_t I1_, std::size_t I2_, std::size_t I3_>
	struct _shuffle_mask<EmuSIMD::f32x8, I0_, I1_, I2_, I3_>
	{
		static constexpr int value = static_cast<int>(((I3_ & 0b11) << 6) | ((I2_ & 0b11) << 4) | ((I1_ & 0b11) << 2) | (I0_ & 0b11));
		[[nodiscard]] static constexpr inline int get()
		{
			return value;
		}
	};
	template<std::size_t I_>
	struct _shuffle_mask<EmuSIMD::f32x8, I_> : public _shuffle_mask<EmuSIMD::f32x8, I_, I_, I_, I_>
	{
	};

	template<std::size_t I0_, std::size_t I1_, std::size_t I2_, std::size_t I3_>
	struct _shuffle_mask<EmuSIMD::f64x4, I0_, I1_, I2_, I3_>
	{
		static constexpr int value = static_cast<int>(((I3_ & 0b1) << 3) | ((I2_ & 0b1) << 2) | ((I1_ & 0b1) << 1) | (I0_ & 0b1));
		[[nodiscard]] static constexpr inline int get()
		{
			return value;
		}
	};
	template<std::size_t I0_, std::size_t I1_>
	struct _shuffle_mask<EmuSIMD::f64x4, I0_, I1_> : public _shuffle_mask<EmuSIMD::f64x4, I0_, I1_, I0_, I1_>
	{
	};
	template<std::size_t I_>
	struct _shuffle_mask<EmuSIMD::f64x4, I_> : public _shuffle_mask<EmuSIMD::f64x4, I_, I_, I_, I_>
	{
	};

	template<std::size_t I0_, std::size_t I1_, std::size_t I2_, std::size_t I3_>
	struct _shuffle_mask<EmuSIMD::i256_generic, I0_, I1_, I2_, I3_>
	{
		static constexpr int value = static_cast<int>(((I3_ & 0b11) << 6) | ((I2_ & 0b11) << 4) | ((I1_ & 0b11) << 2) | (I0_ & 0b11));
		[[nodiscard]] static constexpr inline int get()
		{
			return value;
		}
	};

	template<std::size_t I0_, std::size_t I1_, std::size_t I2_, std::size_t I3_, std::size_t I4_, std::size_t I5_, std::size_t I6_, std::size_t I7_>
	struct _shuffle_mask<EmuSIMD::i256_generic, I0_, I1_, I2_, I3_, I4_, I5_, I6_, I7_>
	{
	private:
		using _underlying_shuffle = _shuffle_mask
		<
			EmuSIMD::i256_generic,
			I0_ * 2, (I0_ * 2) + 1,
			I1_ * 2, (I1_ * 2) + 1,
			I2_ * 2, (I2_ * 2) + 1,
			I3_ * 2, (I3_ * 2) + 1,
			I4_ * 2, (I4_ * 2) + 1,
			I5_ * 2, (I5_ * 2) + 1,
			I6_ * 2, (I6_ * 2) + 1,
			I7_ * 2, (I7_ * 2) + 1,
			I0_ * 2, (I0_ * 2) + 1,
			I1_ * 2, (I1_ * 2) + 1,
			I2_ * 2, (I2_ * 2) + 1,
			I3_ * 2, (I3_ * 2) + 1,
			I4_ * 2, (I4_ * 2) + 1,
			I5_ * 2, (I5_ * 2) + 1,
			I6_ * 2, (I6_ * 2) + 1,
			I7_ * 2, (I7_ * 2) + 1
		>;

	public:
		static inline auto get()
		{
			return _underlying_shuffle::get();
		}
	};

	template
	<
		std::size_t I0_, std::size_t I1_, std::size_t I2_, std::size_t I3_, std::size_t I4_, std::size_t I5_, std::size_t I6_, std::size_t I7_,
		std::size_t I8_, std::size_t I9_, std::size_t I10_, std::size_t I11_, std::size_t I12_, std::size_t I13_, std::size_t I14_, std::size_t I15_,
		std::size_t I16_, std::size_t I17_, std::size_t I18_, std::size_t I19_, std::size_t I20_, std::size_t I21_, std::size_t I22_, std::size_t I23_,
		std::size_t I24_, std::size_t I25_, std::size_t I26_, std::size_t I27_, std::size_t I28_, std::size_t I29_, std::size_t I30_, std::size_t I31_
	>
	struct _shuffle_mask
	<
		EmuSIMD::i256_generic,
		I0_, I1_, I2_, I3_, I4_, I5_, I6_, I7_, I8_, I9_, I10_, I11_, I12_, I13_, I14_, I15_,
		I16_, I17_, I18_, I19_, I20_, I21_, I22_, I23_, I24_, I25_, I26_, I27_, I28_, I29_, I30_, I31_
	>
	{
	private:
		static constexpr char _mask = 0b1111;

		template<std::size_t Index_>
		static constexpr char _val = 0;
		template<>
		static constexpr char _val<0> = I0_ & _mask;
		template<>
		static constexpr char _val<1> = I1_ & _mask;
		template<>
		static constexpr char _val<2> = I2_ & _mask;
		template<>
		static constexpr char _val<3> = I3_ & _mask;
		template<>
		static constexpr char _val<4> = I4_ & _mask;
		template<>
		static constexpr char _val<5> = I5_ & _mask;
		template<>
		static constexpr char _val<6> = I6_ & _mask;
		template<>
		static constexpr char _val<7> = I7_ & _mask;
		template<>
		static constexpr char _val<8> = I8_ & _mask;
		template<>
		static constexpr char _val<9> = I9_ & _mask;
		template<>
		static constexpr char _val<10> = I10_ & _mask;
		template<>
		static constexpr char _val<11> = I11_ & _mask;
		template<>
		static constexpr char _val<12> = I12_ & _mask;
		template<>
		static constexpr char _val<13> = I13_ & _mask;
		template<>
		static constexpr char _val<14> = I14_ & _mask;
		template<>
		static constexpr char _val<15> = I15_ & _mask;
		template<>
		static constexpr char _val<16> = I16_ & _mask;
		template<>
		static constexpr char _val<17> = I17_ & _mask;
		template<>
		static constexpr char _val<18> = I18_ & _mask;
		template<>
		static constexpr char _val<19> = I19_ & _mask;
		template<>
		static constexpr char _val<20> = I20_ & _mask;
		template<>
		static constexpr char _val<21> = I21_ & _mask;
		template<>
		static constexpr char _val<22> = I22_ & _mask;
		template<>
		static constexpr char _val<23> = I23_ & _mask;
		template<>
		static constexpr char _val<24> = I24_ & _mask;
		template<>
		static constexpr char _val<25> = I25_ & _mask;
		template<>
		static constexpr char _val<26> = I26_ & _mask;
		template<>
		static constexpr char _val<27> = I27_ & _mask;
		template<>
		static constexpr char _val<28> = I28_ & _mask;
		template<>
		static constexpr char _val<29> = I29_ & _mask;
		template<>
		static constexpr char _val<30> = I30_ & _mask;
		template<>
		static constexpr char _val<31> = I31_ & _mask;

	public:
		[[nodiscard]] static inline EmuSIMD::i256_generic get()
		{
			return _mm256_set_epi8
			(
				_val<31>, _val<30>, _val<29>, _val<28>, _val<27>, _val<26>, _val<25>, _val<24>,
				_val<23>, _val<22>, _val<21>, _val<20>, _val<19>, _val<18>, _val<17>, _val<16>,
				_val<15>, _val<14>, _val<13>, _val<12>, _val<11>, _val<10>, _val<9>, _val<8>,
				_val<7>, _val<6>, _val<5>, _val<4>, _val<3>, _val<2>, _val<1>, _val<0>
			);
		}
	};
	template
	<
		std::size_t I0_, std::size_t I1_, std::size_t I2_, std::size_t I3_, std::size_t I4_, std::size_t I5_, std::size_t I6_, std::size_t I7_,
		std::size_t I8_, std::size_t I9_, std::size_t I10_, std::size_t I11_, std::size_t I12_, std::size_t I13_, std::size_t I14_, std::size_t I15_
	>
	struct _shuffle_mask<EmuSIMD::i256_generic, I0_, I1_, I2_, I3_, I4_, I5_, I6_, I7_, I8_, I9_, I10_, I11_, I12_, I13_, I14_, I15_> :
		public _shuffle_mask
		<
			EmuSIMD::i256_generic,
			I0_, I1_, I2_, I3_, I4_, I5_, I6_, I7_, I8_, I9_, I10_, I11_, I12_, I13_, I14_, I15_,
			I0_, I1_, I2_, I3_, I4_, I5_, I6_, I7_, I8_, I9_, I10_, I11_, I12_, I13_, I14_, I15_
		>
	{
	};
#pragma endregion

#pragma region SHUFFLE_MASKS_512
	template<std::size_t I0_, std::size_t I1_, std::size_t I2_, std::size_t I3_>
	struct _shuffle_mask<EmuSIMD::f32x16, I0_, I1_, I2_, I3_>
	{
		static constexpr int value = static_cast<int>(((I3_ & 0b11) << 6) | ((I2_ & 0b11) << 4) | ((I1_ & 0b11) << 2) | (I0_ & 0b11));
		[[nodiscard]] static constexpr inline int get()
		{
			return value;
		}
	};
	template<std::size_t I_>
	struct _shuffle_mask<EmuSIMD::f32x16, I_> : public _shuffle_mask<EmuSIMD::f32x16, I_, I_, I_, I_>
	{
	};

	template<std::size_t I0_, std::size_t I1_, std::size_t I2_, std::size_t I3_, std::size_t I4_, std::size_t I5_, std::size_t I6_, std::size_t I7_>
	struct _shuffle_mask<EmuSIMD::f64x8, I0_, I1_, I2_, I3_, I4_, I5_, I6_, I7_>
	{
		static constexpr int value = static_cast<int>
		(
			((I7_ & 0b1) << 7) | ((I6_ & 0b1) << 6) | ((I5_ & 0b1) << 5) | ((I4_ & 0b1) << 4) | ((I3_ & 0b1) << 3) | ((I2_ & 0b1) << 2) | ((I1_ & 0b1) << 1) | (I0_ & 0b1)
		);
		[[nodiscard]] static constexpr inline int get()
		{
			return value;
		}
	};
	template<std::size_t I0_, std::size_t I1_, std::size_t I2_, std::size_t I3_>
	struct _shuffle_mask<EmuSIMD::f64x8, I0_, I1_, I2_, I3_> : public _shuffle_mask<EmuSIMD::f64x8, I0_, I1_, I2_, I3_, I0_, I1_, I2_, I3_>
	{
	};
	template<std::size_t I0_, std::size_t I1_>
	struct _shuffle_mask<EmuSIMD::f64x8, I0_, I1_> : public _shuffle_mask<EmuSIMD::f64x8, I0_, I1_, I0_, I1_, I0_, I1_, I0_, I1_>
	{
	};
	template<std::size_t I_>
	struct _shuffle_mask<EmuSIMD::f64x8, I_> : public _shuffle_mask<EmuSIMD::f64x8, I_, I_, I_, I_, I_, I_, I_, I_>
	{
	};

	template<std::size_t I0_, std::size_t I1_, std::size_t I2_, std::size_t I3_>
	struct _shuffle_mask<EmuSIMD::i512_generic, I0_, I1_, I2_, I3_>
	{
		static constexpr _MM_PERM_ENUM value = static_cast<_MM_PERM_ENUM>(((I3_ & 0b11) << 6) | ((I2_ & 0b11) << 4) | ((I1_ & 0b11) << 2) | (I0_ & 0b11));
		static constexpr inline _MM_PERM_ENUM get()
		{
			return value;
		}
	};

	template
	<
		std::size_t I0_, std::size_t I1_, std::size_t I2_, std::size_t I3_, std::size_t I4_, std::size_t I5_, std::size_t I6_, std::size_t I7_,
		std::size_t I8_, std::size_t I9_, std::size_t I10_, std::size_t I11_, std::size_t I12_, std::size_t I13_, std::size_t I14_, std::size_t I15_,
		std::size_t I16_, std::size_t I17_, std::size_t I18_, std::size_t I19_, std::size_t I20_, std::size_t I21_, std::size_t I22_, std::size_t I23_,
		std::size_t I24_, std::size_t I25_, std::size_t I26_, std::size_t I27_, std::size_t I28_, std::size_t I29_, std::size_t I30_, std::size_t I31_,
		std::size_t I32_, std::size_t I33_, std::size_t I34_, std::size_t I35_, std::size_t I36_, std::size_t I37_, std::size_t I38_, std::size_t I39_,
		std::size_t I40_, std::size_t I41_, std::size_t I42_, std::size_t I43_, std::size_t I44_, std::size_t I45_, std::size_t I46_, std::size_t I47_,
		std::size_t I48_, std::size_t I49_, std::size_t I50_, std::size_t I51_, std::size_t I52_, std::size_t I53_, std::size_t I54_, std::size_t I55_,
		std::size_t I56_, std::size_t I57_, std::size_t I58_, std::size_t I59_, std::size_t I60_, std::size_t I61_, std::size_t I62_, std::size_t I63_
	>
	struct _shuffle_mask
	<
		EmuSIMD::i512_generic, I0_, I1_, I2_, I3_, I4_, I5_, I6_, I7_, I8_, I9_, I10_, I11_, I12_, I13_, I14_, I15_,
		I16_, I17_, I18_, I19_, I20_, I21_, I22_, I23_, I24_, I25_, I26_, I27_, I28_, I29_, I30_, I31_,
		I32_, I33_, I34_, I35_, I36_, I37_, I38_, I39_, I40_, I41_, I42_, I43_, I44_, I45_, I46_, I47_,
		I48_, I49_, I50_, I51_, I52_, I53_, I54_, I55_, I56_, I57_, I58_, I59_, I60_, I61_, I62_, I63_
	>
	{
	private:
		static constexpr char _mask = 0b1111;

		template<std::size_t Index_>
		static constexpr char _val = 0;
		template<>
		static constexpr char _val<0> = I0_ & _mask;
		template<>
		static constexpr char _val<1> = I1_ & _mask;
		template<>
		static constexpr char _val<2> = I2_ & _mask;
		template<>
		static constexpr char _val<3> = I3_ & _mask;
		template<>
		static constexpr char _val<4> = I4_ & _mask;
		template<>
		static constexpr char _val<5> = I5_ & _mask;
		template<>
		static constexpr char _val<6> = I6_ & _mask;
		template<>
		static constexpr char _val<7> = I7_ & _mask;
		template<>
		static constexpr char _val<8> = I8_ & _mask;
		template<>
		static constexpr char _val<9> = I9_ & _mask;
		template<>
		static constexpr char _val<10> = I10_ & _mask;
		template<>
		static constexpr char _val<11> = I11_ & _mask;
		template<>
		static constexpr char _val<12> = I12_ & _mask;
		template<>
		static constexpr char _val<13> = I13_ & _mask;
		template<>
		static constexpr char _val<14> = I14_ & _mask;
		template<>
		static constexpr char _val<15> = I15_ & _mask;
		template<>
		static constexpr char _val<16> = I16_ & _mask;
		template<>
		static constexpr char _val<17> = I17_ & _mask;
		template<>
		static constexpr char _val<18> = I18_ & _mask;
		template<>
		static constexpr char _val<19> = I19_ & _mask;
		template<>
		static constexpr char _val<20> = I20_ & _mask;
		template<>
		static constexpr char _val<21> = I21_ & _mask;
		template<>
		static constexpr char _val<22> = I22_ & _mask;
		template<>
		static constexpr char _val<23> = I23_ & _mask;
		template<>
		static constexpr char _val<24> = I24_ & _mask;
		template<>
		static constexpr char _val<25> = I25_ & _mask;
		template<>
		static constexpr char _val<26> = I26_ & _mask;
		template<>
		static constexpr char _val<27> = I27_ & _mask;
		template<>
		static constexpr char _val<28> = I28_ & _mask;
		template<>
		static constexpr char _val<29> = I29_ & _mask;
		template<>
		static constexpr char _val<30> = I30_ & _mask;
		template<>
		static constexpr char _val<31> = I31_ & _mask;
		template<>
		static constexpr char _val<32> = I32_ & _mask;
		template<>
		static constexpr char _val<33> = I33_ & _mask;
		template<>
		static constexpr char _val<34> = I34_ & _mask;
		template<>
		static constexpr char _val<35> = I35_ & _mask;
		template<>
		static constexpr char _val<36> = I36_ & _mask;
		template<>
		static constexpr char _val<37> = I37_ & _mask;
		template<>
		static constexpr char _val<38> = I38_ & _mask;
		template<>
		static constexpr char _val<39> = I39_ & _mask;
		template<>
		static constexpr char _val<40> = I40_ & _mask;
		template<>
		static constexpr char _val<41> = I41_ & _mask;
		template<>
		static constexpr char _val<42> = I42_ & _mask;
		template<>
		static constexpr char _val<43> = I43_ & _mask;
		template<>
		static constexpr char _val<44> = I44_ & _mask;
		template<>
		static constexpr char _val<45> = I45_ & _mask;
		template<>
		static constexpr char _val<46> = I46_ & _mask;
		template<>
		static constexpr char _val<47> = I47_ & _mask;
		template<>
		static constexpr char _val<48> = I48_ & _mask;
		template<>
		static constexpr char _val<49> = I49_ & _mask;
		template<>
		static constexpr char _val<50> = I50_ & _mask;
		template<>
		static constexpr char _val<51> = I51_ & _mask;
		template<>
		static constexpr char _val<52> = I52_ & _mask;
		template<>
		static constexpr char _val<53> = I53_ & _mask;
		template<>
		static constexpr char _val<54> = I54_ & _mask;
		template<>
		static constexpr char _val<55> = I55_ & _mask;
		template<>
		static constexpr char _val<56> = I56_ & _mask;
		template<>
		static constexpr char _val<57> = I57_ & _mask;
		template<>
		static constexpr char _val<58> = I58_ & _mask;
		template<>
		static constexpr char _val<59> = I59_ & _mask;
		template<>
		static constexpr char _val<60> = I60_ & _mask;
		template<>
		static constexpr char _val<61> = I61_ & _mask;
		template<>
		static constexpr char _val<62> = I62_ & _mask;
		template<>
		static constexpr char _val<63> = I63_ & _mask;

	public:
		[[nodiscard]] static inline EmuSIMD::i512_generic get()
		{
			return _mm512_set_epi8
			(
				_val<63>, _val<62>, _val<61>, _val<60>, _val<59>, _val<58>, _val<57>, _val<56>,
				_val<55>, _val<54>, _val<53>, _val<52>, _val<51>, _val<50>, _val<49>, _val<48>,
				_val<47>, _val<46>, _val<45>, _val<44>, _val<43>, _val<42>, _val<41>, _val<40>,
				_val<39>, _val<38>, _val<37>, _val<36>, _val<35>, _val<34>, _val<33>, _val<32>,
				_val<31>, _val<30>, _val<29>, _val<28>, _val<27>, _val<26>, _val<25>, _val<24>,
				_val<23>, _val<22>, _val<21>, _val<20>, _val<19>, _val<18>, _val<17>, _val<16>,
				_val<15>, _val<14>, _val<13>, _val<12>, _val<11>, _val<10>, _val<9>, _val<8>,
				_val<7>, _val<6>, _val<5>, _val<4>, _val<3>, _val<2>, _val<1>, _val<0>
			);
		}
	};
	template
	<
		std::size_t I0_, std::size_t I1_, std::size_t I2_, std::size_t I3_, std::size_t I4_, std::size_t I5_, std::size_t I6_, std::size_t I7_,
		std::size_t I8_, std::size_t I9_, std::size_t I10_, std::size_t I11_, std::size_t I12_, std::size_t I13_, std::size_t I14_, std::size_t I15_,
		std::size_t I16_, std::size_t I17_, std::size_t I18_, std::size_t I19_, std::size_t I20_, std::size_t I21_, std::size_t I22_, std::size_t I23_,
		std::size_t I24_, std::size_t I25_, std::size_t I26_, std::size_t I27_, std::size_t I28_, std::size_t I29_, std::size_t I30_, std::size_t I31_
	>
	struct _shuffle_mask
	<
		EmuSIMD::i512_generic, I0_, I1_, I2_, I3_, I4_, I5_, I6_, I7_, I8_, I9_, I10_, I11_, I12_, I13_, I14_, I15_,
		I16_, I17_, I18_, I19_, I20_, I21_, I22_, I23_, I24_, I25_, I26_, I27_, I28_, I29_, I30_, I31_
	> : public _shuffle_mask
		<
			EmuSIMD::i512_generic, 
			I0_, I1_, I2_, I3_, I4_, I5_, I6_, I7_, I8_, I9_, I10_, I11_, I12_, I13_, I14_, I15_,
			I16_, I17_, I18_, I19_, I20_, I21_, I22_, I23_, I24_, I25_, I26_, I27_, I28_, I29_, I30_, I31_,
			I0_, I1_, I2_, I3_, I4_, I5_, I6_, I7_, I8_, I9_, I10_, I11_, I12_, I13_, I14_, I15_,
			I16_, I17_, I18_, I19_, I20_, I21_, I22_, I23_, I24_, I25_, I26_, I27_, I28_, I29_, I30_, I31_
		>
	{
	};
	template
	<
		std::size_t I0_, std::size_t I1_, std::size_t I2_, std::size_t I3_, std::size_t I4_, std::size_t I5_, std::size_t I6_, std::size_t I7_,
		std::size_t I8_, std::size_t I9_, std::size_t I10_, std::size_t I11_, std::size_t I12_, std::size_t I13_, std::size_t I14_, std::size_t I15_
	>
	struct _shuffle_mask<EmuSIMD::i512_generic, I0_, I1_, I2_, I3_, I4_, I5_, I6_, I7_, I8_, I9_, I10_, I11_, I12_, I13_, I14_, I15_> :
		public _shuffle_mask
		<
			EmuSIMD::i512_generic, 
			I0_, I1_, I2_, I3_, I4_, I5_, I6_, I7_, I8_, I9_, I10_, I11_, I12_, I13_, I14_, I15_,
			I0_, I1_, I2_, I3_, I4_, I5_, I6_, I7_, I8_, I9_, I10_, I11_, I12_, I13_, I14_, I15_,
			I0_, I1_, I2_, I3_, I4_, I5_, I6_, I7_, I8_, I9_, I10_, I11_, I12_, I13_, I14_, I15_,
			I0_, I1_, I2_, I3_, I4_, I5_, I6_, I7_, I8_, I9_, I10_, I11_, I12_, I13_, I14_, I15_
		>
	{
	};
#pragma endregion

#pragma region VALIDITY_TMP
	template<class ShuffleMaskInstance_>
	struct is_valid_shuffle_mask_instance
	{
		static constexpr bool value = false;
	};
	template<class Register_, std::size_t...Indices_>
	struct is_valid_shuffle_mask_instance<_shuffle_mask<Register_, Indices_...>>
	{
		static constexpr bool value = EmuCore::TMP::has_static_get<_shuffle_mask<Register_, Indices_...>>::value;
	};
#pragma endregion
}

#endif
