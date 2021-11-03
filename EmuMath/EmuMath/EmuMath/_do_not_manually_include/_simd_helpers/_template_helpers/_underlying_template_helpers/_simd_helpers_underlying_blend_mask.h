#ifndef EMU_MATH_SIMD_HELPERS_UNDERLYING_BLEND_MASK_H_INC_
#define EMU_MATH_SIMD_HELPERS_UNDERLYING_BLEND_MASK_H_INC_ 1

#include "_common_underlying_simd_template_helper_includes.h"
#include "_simd_helpers_underlying_index_masks.h"

namespace EmuMath::SIMD::_underlying_simd_helpers
{
	template<class Register_, bool...TakeIndexFromB_>
	struct _blend_mask
	{
	};

#pragma region BLEND_MASK_128
	template<bool I0_, bool I1_, bool I2_, bool I3_>
	struct _blend_mask<__m128, I0_, I1_, I2_, I3_>
	{
	private:
		template<std::size_t Index_>
		[[nodiscard]] static constexpr inline int _bit(bool bit_)
		{
			return static_cast<int>(bit_) << Index_;
		}

	public:
		static constexpr int value = _bit<3>(I3_) | _bit<2>(I2_) | _bit<1>(I1_) | _bit<0>(I0_);
		[[nodiscard]] static constexpr inline int get()
		{
			return value;
		}
	};

	template<bool I0_, bool I1_>
	struct _blend_mask<__m128d, I0_, I1_>
	{
	private:
		template<std::size_t Index_>
		[[nodiscard]] static constexpr inline int _bit(bool bit_)
		{
			return static_cast<int>(bit_) << Index_;
		}

	public:
		static constexpr int value = _bit<1>(I1_) | _bit<0>(I0_);
		[[nodiscard]] static constexpr inline int get()
		{
			return value;
		}
	};

	template
	<
		bool I0_, bool I1_, bool I2_, bool I3_, bool I4_, bool I5_, bool I6_, bool I7_,
		bool I8_, bool I9_, bool I10_, bool I11_, bool I12_, bool I13_, bool I14_, bool I15_
	>
	struct _blend_mask<__m128i, I0_, I1_, I2_, I3_, I4_, I5_, I6_, I7_, I8_, I9_, I10_, I11_, I12_, I13_, I14_, I15_>
	{
	private:
		using _mask_generator = _underlying_simd_helpers::_per_index_mask
		<
			__m128i,
			I15_, I14_, I13_, I12_, I11_, I10_, I9_,  I8_,  I7_,  I6_,  I5_,  I4_,  I3_,  I2_,  I1_,  I0_
		>;

	public:
		[[nodiscard]] static inline __m128i get()
		{
			return _mask_generator::get();
		}
	};

	template<bool I0_, bool I1_, bool I2_, bool I3_, bool I4_, bool I5_, bool I6_, bool I7_>
	struct _blend_mask<__m128i, I0_, I1_, I2_, I3_, I4_, I5_, I6_, I7_>
	{
	private:
		template<std::size_t Index_>
		[[nodiscard]] static constexpr inline int _bit(bool bit_)
		{
			return static_cast<int>(bit_) << Index_;
		}

	public:
		static constexpr int value = (_bit<7>(I7_) | _bit<6>(I6_) | _bit<5>(I5_) | _bit<4>(I4_) | _bit<3>(I3_) | _bit<2>(I2_) | _bit<1>(I1_) | _bit<0>(I0_));
		[[nodiscard]] static constexpr inline int get()
		{
			return value;
		}
	};

	template<bool I0_, bool I1_, bool I2_, bool I3_>
	struct _blend_mask<__m128i, I0_, I1_, I2_, I3_>
	{
	private:
		template<std::size_t Index_>
		[[nodiscard]] static constexpr inline int _bit(bool bit_)
		{
			return static_cast<int>(bit_) << Index_;
		}

	public:
		static constexpr int value = (_bit<3>(I3_) | _bit<2>(I2_) | _bit<1>(I1_) | _bit<0>(I0_));
		[[nodiscard]] static constexpr inline int get()
		{
			return value;
		}
	};

	template<bool I0_, bool I1_>
	struct _blend_mask<__m128i, I0_, I1_>
	{
	private:
		using _mask_generator = _blend_mask<__m128i, I0_, I0_, I1_, I1_>;

	public:
		static constexpr int value = _mask_generator::value;
		[[nodiscard]] static constexpr inline int get()
		{
			return value;
		}
	};
#pragma endregion

#pragma region BLEND_MASK_256
	template<bool I0_, bool I1_, bool I2_, bool I3_, bool I4_, bool I5_, bool I6_, bool I7_>
	struct _blend_mask<__m256, I0_, I1_, I2_, I3_, I4_, I5_, I6_, I7_>
	{
	private:
		template<std::size_t Index_>
		[[nodiscard]] static constexpr inline int _bit(bool bit_)
		{
			return static_cast<int>(bit_) << Index_;
		}

	public:
		static constexpr int value = (_bit<7>(I7_) | _bit<6>(I6_) | _bit<5>(I5_) | _bit<4>(I4_) | _bit<3>(I3_) | _bit<2>(I2_) | _bit<1>(I1_) | _bit<0>(I0_));
		[[nodiscard]] static constexpr inline int get()
		{
			return value;
		}
	};

	template<bool I0_, bool I1_, bool I2_, bool I3_>
	struct _blend_mask<__m256d, I0_, I1_, I2_, I3_>
	{
	private:
		template<std::size_t Index_>
		[[nodiscard]] static constexpr inline int _bit(bool bit_)
		{
			return static_cast<int>(bit_) << Index_;
		}

	public:
		static constexpr int value = (_bit<3>(I3_) | _bit<2>(I2_) | _bit<1>(I1_) | _bit<0>(I0_));
		[[nodiscard]] static constexpr inline int get()
		{
			return value;
		}
	};

	template
	<
		bool I0_,  bool I1_,  bool I2_,  bool I3_,  bool I4_,  bool I5_,  bool I6_,  bool I7_,
		bool I8_,  bool I9_,  bool I10_, bool I11_, bool I12_, bool I13_, bool I14_, bool I15_,
		bool I16_, bool I17_, bool I18_, bool I19_, bool I20_, bool I21_, bool I22_, bool I23_,
		bool I24_, bool I25_, bool I26_, bool I27_, bool I28_, bool I29_, bool I30_, bool I31_
	>
	struct _blend_mask
	<
		__m256i,
		I0_,  I1_,  I2_,  I3_,  I4_,  I5_,  I6_,  I7_,  I8_,  I9_,  I10_, I11_, I12_, I13_, I14_, I15_,
		I16_, I17_, I18_, I19_, I20_, I21_, I22_, I23_, I24_, I25_, I26_, I27_, I28_, I29_, I30_, I31_
	>
	{
	private:
		using _mask_generator = _underlying_simd_helpers::_per_index_mask
		<
			__m256i,
			I31_, I30_, I29_, I28_, I27_, I26_, I25_, I24_, I23_, I22_, I21_, I20_, I19_, I18_, I17_, I16_,
			I15_, I14_, I13_, I12_, I11_, I10_, I9_,  I8_,  I7_,  I6_,  I5_,  I4_,  I3_,  I2_,  I1_,  I0_
		>;

	public:
		[[nodiscard]] static inline __m256i get()
		{
			return _mask_generator::get();
		}
	};

	template
	<
		bool I0_,  bool I1_,  bool I2_,  bool I3_,  bool I4_,  bool I5_,  bool I6_,  bool I7_,
		bool I8_,  bool I9_,  bool I10_, bool I11_, bool I12_, bool I13_, bool I14_, bool I15_
	>
	struct _blend_mask<__m256i, I0_,  I1_,  I2_,  I3_,  I4_,  I5_,  I6_,  I7_,  I8_,  I9_,  I10_, I11_, I12_, I13_, I14_, I15_>
	{
	private:
		using _mask_generator = _blend_mask
		<
			__m256i,
			I0_, I0_, I1_, I1_, I2_,  I2_,  I3_,  I3_,  I4_,  I4_,  I5_,  I5_,  I6_,  I6_,  I7_,  I7_,
			I8_, I8_, I9_, I9_, I10_, I10_, I11_, I11_, I12_, I12_, I13_, I13_, I14_, I14_, I15_, I15_
		>;

	public:
		[[nodiscard]] static inline __m256i get()
		{
			return _mask_generator::get();
		}
	};

	template<bool I0_,  bool I1_,  bool I2_,  bool I3_,  bool I4_,  bool I5_,  bool I6_,  bool I7_>
	struct _blend_mask<__m256i, I0_,  I1_,  I2_,  I3_,  I4_,  I5_,  I6_,  I7_>
	{
	private:
		template<std::size_t Index_>
		[[nodiscard]] static constexpr inline int _bit(bool bit_)
		{
			return static_cast<int>(bit_) << Index_;
		}

	public:
		static constexpr int value = (_bit<7>(I7_) | _bit<6>(I6_) | _bit<5>(I5_) | _bit<4>(I4_) | _bit<3>(I3_) | _bit<2>(I2_) | _bit<1>(I1_) | _bit<0>(I0_));
		[[nodiscard]] static constexpr inline int get()
		{
			return value;
		}
	};

	template<bool I0_, bool I1_, bool I2_, bool I3_>
	struct _blend_mask<__m256i, I0_, I1_, I2_, I3_>
	{
	private:
		using _mask_generator = _blend_mask<__m256i, I0_, I0_, I1_, I1_, I2_, I2_, I3_, I3_>;

	public:
		static constexpr int value = _mask_generator::value;
		[[nodiscard]] static constexpr inline int get()
		{
			return value;
		}
	};
#pragma endregion

#pragma region BLEND_MASK_512
	template
	<
		bool I0_,  bool I1_,  bool I2_,  bool I3_,  bool I4_,  bool I5_,  bool I6_,  bool I7_,
		bool I8_,  bool I9_,  bool I10_, bool I11_, bool I12_, bool I13_, bool I14_, bool I15_
	>
	struct _blend_mask<__m512, I0_,  I1_,  I2_,  I3_,  I4_,  I5_,  I6_,  I7_,  I8_,  I9_,  I10_, I11_, I12_, I13_, I14_, I15_>
	{
	private:
		template<std::size_t Index_>
		[[nodiscard]] static constexpr inline __mmask16 _bit(bool bit_)
		{
			return static_cast<__mmask16>(bit_) << Index_;
		}

	public:
		static constexpr __mmask16 value =
		(
			_bit<15>(I15_) | _bit<14>(I14_) | _bit<13>(I13_) | _bit<12>(I12_) | _bit<11>(I11_) | _bit<10>(I10_) | _bit<9>(I9_)   | _bit<8>(I8_)   |
			_bit<7>(I7_)   | _bit<6>(I6_)   | _bit<5>(I5_)   | _bit<4>(I4_)   | _bit<3>(I3_)   | _bit<2>(I2_)   | _bit<1>(I1_)   | _bit<0>(I0_)
		);
		[[nodiscard]] static constexpr inline __mmask16 get()
		{
			return value;
		}
	};

	template<bool I0_,  bool I1_,  bool I2_,  bool I3_,  bool I4_,  bool I5_,  bool I6_,  bool I7_>
	struct _blend_mask<__m512d, I0_,  I1_,  I2_,  I3_,  I4_,  I5_,  I6_,  I7_>
	{
	private:
		template<std::size_t Index_>
		[[nodiscard]] static constexpr inline __mmask8 _bit(bool bit_)
		{
			return static_cast<__mmask8>(bit_) << Index_;
		}

	public:
		static constexpr __mmask8 value = (_bit<7>(I7_) | _bit<6>(I6_) | _bit<5>(I5_) | _bit<4>(I4_) | _bit<3>(I3_) | _bit<2>(I2_) | _bit<1>(I1_) | _bit<0>(I0_));
		[[nodiscard]] static constexpr inline __mmask8 get()
		{
			return value;
		}
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
	struct _blend_mask
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
		[[nodiscard]] static constexpr inline __mmask64 _bit(bool bit_)
		{
			return static_cast<__mmask64>(bit_) << Index_;
		}

	public:
		static constexpr __mmask64 value =
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
		[[nodiscard]] static constexpr inline __mmask64 get()
		{
			return value;
		}
	};

	template
	<
		bool I0_,  bool I1_,  bool I2_,  bool I3_,  bool I4_,  bool I5_,  bool I6_,  bool I7_,
		bool I8_,  bool I9_,  bool I10_, bool I11_, bool I12_, bool I13_, bool I14_, bool I15_,
		bool I16_, bool I17_, bool I18_, bool I19_, bool I20_, bool I21_, bool I22_, bool I23_,
		bool I24_, bool I25_, bool I26_, bool I27_, bool I28_, bool I29_, bool I30_, bool I31_
	>
	struct _blend_mask
	<
		__m512i,
		I0_,  I1_,  I2_,  I3_,  I4_,  I5_,  I6_,  I7_,  I8_,  I9_,  I10_, I11_, I12_, I13_, I14_, I15_,
		I16_, I17_, I18_, I19_, I20_, I21_, I22_, I23_, I24_, I25_, I26_, I27_, I28_, I29_, I30_, I31_
	>
	{
	private:
		template<std::size_t Index_>
		[[nodiscard]] static constexpr inline __mmask32 _bit(bool bit_)
		{
			return static_cast<__mmask32>(bit_) << Index_;
		}

	public:
		static constexpr __mmask32 value =
		(
			_bit<31>(I31_) | _bit<30>(I30_) | _bit<29>(I29_) | _bit<28>(I28_) | _bit<27>(I27_) | _bit<26>(I26_) | _bit<25>(I25_) | _bit<24>(I24_) |
			_bit<23>(I23_) | _bit<22>(I22_) | _bit<21>(I21_) | _bit<20>(I20_) | _bit<19>(I19_) | _bit<18>(I18_) | _bit<17>(I17_) | _bit<16>(I16_) |
			_bit<15>(I15_) | _bit<14>(I14_) | _bit<13>(I13_) | _bit<12>(I12_) | _bit<11>(I11_) | _bit<10>(I10_) | _bit<9>(I9_)   | _bit<8>(I8_)   |
			_bit<7>(I7_)   | _bit<6>(I6_)   | _bit<5>(I5_)   | _bit<4>(I4_)   | _bit<3>(I3_)   | _bit<2>(I2_)   | _bit<1>(I1_)   | _bit<0>(I0_)
		);
		[[nodiscard]] static constexpr inline __mmask32 get()
		{
			return value;
		}
	};

	template
	<
		bool I0_,  bool I1_,  bool I2_,  bool I3_,  bool I4_,  bool I5_,  bool I6_,  bool I7_,
		bool I8_,  bool I9_,  bool I10_, bool I11_, bool I12_, bool I13_, bool I14_, bool I15_
	>
	struct _blend_mask<__m512i,I0_,  I1_,  I2_,  I3_,  I4_,  I5_,  I6_,  I7_,  I8_,  I9_,  I10_, I11_, I12_, I13_, I14_, I15_>
	{
	private:
		template<std::size_t Index_>
		[[nodiscard]] static constexpr inline __mmask16 _bit(bool bit_)
		{
			return static_cast<__mmask16>(bit_) << Index_;
		}

	public:
		static constexpr __mmask16 value =
		(
			_bit<15>(I15_) | _bit<14>(I14_) | _bit<13>(I13_) | _bit<12>(I12_) | _bit<11>(I11_) | _bit<10>(I10_) | _bit<9>(I9_)   | _bit<8>(I8_)   |
			_bit<7>(I7_)   | _bit<6>(I6_)   | _bit<5>(I5_)   | _bit<4>(I4_)   | _bit<3>(I3_)   | _bit<2>(I2_)   | _bit<1>(I1_)   | _bit<0>(I0_)
		);
		[[nodiscard]] static constexpr inline __mmask16 get()
		{
			return value;
		}
	};

	template<bool I0_,  bool I1_,  bool I2_,  bool I3_,  bool I4_,  bool I5_,  bool I6_,  bool I7_>
	struct _blend_mask<__m512i,I0_,  I1_,  I2_,  I3_,  I4_,  I5_,  I6_,  I7_>
	{
	private:
		template<std::size_t Index_>
		[[nodiscard]] static constexpr inline __mmask8 _bit(bool bit_)
		{
			return static_cast<__mmask8>(bit_) << Index_;
		}

	public:
		static constexpr __mmask8 value = (_bit<7>(I7_) | _bit<6>(I6_) | _bit<5>(I5_) | _bit<4>(I4_) | _bit<3>(I3_) | _bit<2>(I2_) | _bit<1>(I1_) | _bit<0>(I0_));
		[[nodiscard]] static constexpr inline __mmask8 get()
		{
			return value;
		}
	};
#pragma endregion

#pragma region BLEND_MASK_TMP
	template<class BlendMaskInstance_>
	struct _is_valid_blend_mask
	{
		static constexpr bool value = false;
	};
	template<class Register_, bool...IndexArgs_>
	struct _is_valid_blend_mask<_blend_mask<Register_, IndexArgs_...>>
	{
		static constexpr bool value = EmuCore::TMPHelpers::has_static_get<_blend_mask<Register_, IndexArgs_...>>::value;
	};

	template<class BlendMaskInstance_>
	struct _blend_mask_is_simd_register
	{
		static constexpr bool value = false;
	};
	template<class Register_, bool...IndexArgs_>
	struct _blend_mask_is_simd_register<_blend_mask<Register_, IndexArgs_...>>
	{
	private:
		[[nodiscard]] static constexpr inline bool _do_check()
		{
			using mask_generator = _blend_mask<Register_, IndexArgs_...>;
			if constexpr (_is_valid_blend_mask<mask_generator>::value)
			{
				using return_type = std::invoke_result_t<decltype(mask_generator::get)>;
				return EmuMath::SIMD::TMP::is_simd_register_v<return_type>;
			}
			else
			{
				return false;
			}
		}

	public:
		static constexpr bool value = _do_check();
	};
#pragma endregion
}

#endif
