#ifndef EMU_SIMD_HELPERS_UNDERLYING_INDEX_MASKS_H_INC_
#define EMU_SIMD_HELPERS_UNDERLYING_INDEX_MASKS_H_INC_ 1

#include "_common_underlying_simd_template_helper_includes.h"
#include "../../../../../EmuCore/TMPHelpers/TypeComparators.h"
#include "../../../../../EmuCore/TMPHelpers/Values.h"

namespace EmuSIMD::_underlying_simd_helpers
{
	/// <summary>
	/// <para> Type for creating a per-index mask, where true indices will be set to active (all bits 1) and false indices will be inactive (all bits 0). </para>
	/// <para> The size of elements in integral registers will adapt to the provided amount of index arguments. </para>
	/// </summary>
	template<class Register_, bool...ActiveIndices_>
	struct _per_index_mask
	{
	};

#pragma region MASK_GENERATORS_128
	template<>
	struct _per_index_mask<EmuSIMD::i128_generic, false>
	{
		[[nodiscard]] static inline EmuSIMD::i128_generic get()
		{
			return EmuSIMD::Funcs::setzero_i32x4();
		}
	};
	template<>
	struct _per_index_mask<EmuSIMD::i128_generic, true>
	{
		[[nodiscard]] static inline EmuSIMD::i128_generic get()
		{
			return EmuSIMD::Funcs::set1_u32x4(0xFFFFFFFF);
		}
	};

	template
	<
		bool I0_, bool I1_, bool I2_, bool I3_, bool I4_, bool I5_, bool I6_, bool I7_,
		bool I8_, bool I9_, bool I10_, bool I11_, bool I12_, bool I13_, bool I14_, bool I15_
	>
	struct _per_index_mask<EmuSIMD::i128_generic, I0_, I1_, I2_, I3_, I4_, I5_, I6_, I7_, I8_, I9_, I10_, I11_, I12_, I13_, I14_, I15_>
	{
		[[nodiscard]] static inline EmuSIMD::i128_generic get()
		{
			return _mm_set_epi8
			(
				EmuCore::TMP::conditional_value_v<I0_,  std::int8_t, std::int8_t(0xFF), 0x00>,
				EmuCore::TMP::conditional_value_v<I1_,  std::int8_t, std::int8_t(0xFF), 0x00>,
				EmuCore::TMP::conditional_value_v<I2_,  std::int8_t, std::int8_t(0xFF), 0x00>,
				EmuCore::TMP::conditional_value_v<I3_,  std::int8_t, std::int8_t(0xFF), 0x00>,
				EmuCore::TMP::conditional_value_v<I4_,  std::int8_t, std::int8_t(0xFF), 0x00>,
				EmuCore::TMP::conditional_value_v<I5_,  std::int8_t, std::int8_t(0xFF), 0x00>,
				EmuCore::TMP::conditional_value_v<I6_,  std::int8_t, std::int8_t(0xFF), 0x00>,
				EmuCore::TMP::conditional_value_v<I7_,  std::int8_t, std::int8_t(0xFF), 0x00>,
				EmuCore::TMP::conditional_value_v<I8_,  std::int8_t, std::int8_t(0xFF), 0x00>,
				EmuCore::TMP::conditional_value_v<I9_,  std::int8_t, std::int8_t(0xFF), 0x00>,
				EmuCore::TMP::conditional_value_v<I10_, std::int8_t, std::int8_t(0xFF), 0x00>,
				EmuCore::TMP::conditional_value_v<I11_, std::int8_t, std::int8_t(0xFF), 0x00>,
				EmuCore::TMP::conditional_value_v<I12_, std::int8_t, std::int8_t(0xFF), 0x00>,
				EmuCore::TMP::conditional_value_v<I13_, std::int8_t, std::int8_t(0xFF), 0x00>,
				EmuCore::TMP::conditional_value_v<I14_, std::int8_t, std::int8_t(0xFF), 0x00>,
				EmuCore::TMP::conditional_value_v<I15_, std::int8_t, std::int8_t(0xFF), 0x00>
			);
		}
	};
	template<>
	struct _per_index_mask<EmuSIMD::i128_generic, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false>
	{
		[[nodiscard]] static inline EmuSIMD::i128_generic get()
		{
			return _per_index_mask<EmuSIMD::i128_generic, false>::get();
		}
	};
	template<>
	struct _per_index_mask<EmuSIMD::i128_generic, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true>
	{
		[[nodiscard]] static inline EmuSIMD::i128_generic get()
		{
			return _per_index_mask<EmuSIMD::i128_generic, true>::get();
		}
	};

	template<bool I0_, bool I1_, bool I2_, bool I3_, bool I4_, bool I5_, bool I6_, bool I7_>
	struct _per_index_mask<EmuSIMD::i128_generic, I0_, I1_, I2_, I3_, I4_, I5_, I6_, I7_>
	{
		[[nodiscard]] static inline EmuSIMD::i128_generic get()
		{
			return _mm_set_epi16
			(
				EmuCore::TMP::conditional_value_v<I0_, std::int16_t, std::int16_t(0xFFFF), 0x0000>,
				EmuCore::TMP::conditional_value_v<I1_, std::int16_t, std::int16_t(0xFFFF), 0x0000>,
				EmuCore::TMP::conditional_value_v<I2_, std::int16_t, std::int16_t(0xFFFF), 0x0000>,
				EmuCore::TMP::conditional_value_v<I3_, std::int16_t, std::int16_t(0xFFFF), 0x0000>,
				EmuCore::TMP::conditional_value_v<I4_, std::int16_t, std::int16_t(0xFFFF), 0x0000>,
				EmuCore::TMP::conditional_value_v<I5_, std::int16_t, std::int16_t(0xFFFF), 0x0000>,
				EmuCore::TMP::conditional_value_v<I6_, std::int16_t, std::int16_t(0xFFFF), 0x0000>,
				EmuCore::TMP::conditional_value_v<I7_, std::int16_t, std::int16_t(0xFFFF), 0x0000>
			);
		}
	};
	template<>
	struct _per_index_mask<EmuSIMD::i128_generic, false, false, false, false, false, false, false, false>
	{
		[[nodiscard]] static inline EmuSIMD::i128_generic get()
		{
			return _per_index_mask<EmuSIMD::i128_generic, false>::get();
		}
	};
	template<>
	struct _per_index_mask<EmuSIMD::i128_generic, true, true, true, true, true, true, true, true>
	{
		[[nodiscard]] static inline EmuSIMD::i128_generic get()
		{
			return _per_index_mask<EmuSIMD::i128_generic, true>::get();
		}
	};

	template<bool I0_, bool I1_, bool I2_, bool I3_>
	struct _per_index_mask<EmuSIMD::i128_generic, I0_, I1_, I2_, I3_>
	{
		[[nodiscard]] static inline EmuSIMD::i128_generic get()
		{
			return _mm_set_epi32
			(
				EmuCore::TMP::conditional_value_v<I0_, std::int32_t, std::int32_t(0xFFFFFFFF), 0x00000000>,
				EmuCore::TMP::conditional_value_v<I1_, std::int32_t, std::int32_t(0xFFFFFFFF), 0x00000000>,
				EmuCore::TMP::conditional_value_v<I2_, std::int32_t, std::int32_t(0xFFFFFFFF), 0x00000000>,
				EmuCore::TMP::conditional_value_v<I3_, std::int32_t, std::int32_t(0xFFFFFFFF), 0x00000000>
			);
		}
	};
	template<>
	struct _per_index_mask<EmuSIMD::i128_generic, false, false, false, false>
	{
		[[nodiscard]] static inline EmuSIMD::i128_generic get()
		{
			return _per_index_mask<EmuSIMD::i128_generic, false>::get();
		}
	};
	template<>
	struct _per_index_mask<EmuSIMD::i128_generic, true, true, true, true>
	{
		[[nodiscard]] static inline EmuSIMD::i128_generic get()
		{
			return _per_index_mask<EmuSIMD::i128_generic, true>::get();
		}
	};

	template<bool I0_, bool I1_>
	struct _per_index_mask<EmuSIMD::i128_generic, I0_, I1_>
	{
		[[nodiscard]] static inline EmuSIMD::i128_generic get()
		{
			return _mm_set_epi64x
			(
				EmuCore::TMP::conditional_value_v<I0_, std::int64_t, std::int64_t(0xFFFFFFFFFFFFFFFF), 0x0000000000000000>,
				EmuCore::TMP::conditional_value_v<I1_, std::int64_t, std::int64_t(0xFFFFFFFFFFFFFFFF), 0x0000000000000000>
			);
		}
	};
	template<>
	struct _per_index_mask<EmuSIMD::i128_generic, false, false>
	{
		[[nodiscard]] static inline EmuSIMD::i128_generic get()
		{
			return _per_index_mask<EmuSIMD::i128_generic, false>::get();
		}
	};
	template<>
	struct _per_index_mask<EmuSIMD::i128_generic, true, true>
	{
		[[nodiscard]] static inline EmuSIMD::i128_generic get()
		{
			return _per_index_mask<EmuSIMD::i128_generic, true>::get();
		}
	};

	template<bool I0_, bool I1_, bool I2_, bool I3_>
	struct _per_index_mask<EmuSIMD::f32x4, I0_, I1_, I2_, I3_>
	{
	private:
		using _integral_mask_generator = _per_index_mask<EmuSIMD::i128_generic, I0_, I1_, I2_, I3_>;

	public:
		[[nodiscard]] static inline EmuSIMD::f32x4 get()
		{
			return _mm_castsi128_ps(_integral_mask_generator::get());
		}
	};
	template<bool AllIndices_>
	struct _per_index_mask<EmuSIMD::f32x4, AllIndices_>
	{
	private:
		using _integral_mask_generator = _per_index_mask<EmuSIMD::i128_generic, AllIndices_>;

	public:
		[[nodiscard]] static inline EmuSIMD::f32x4 get()
		{
			return _mm_castsi128_ps(_integral_mask_generator::get());
		}
	};

	template<bool I0_, bool I1_>
	struct _per_index_mask<EmuSIMD::f64x2, I0_, I1_>
	{
	private:
		using _integral_mask_generator = _per_index_mask<EmuSIMD::i128_generic, I0_, I1_>;

	public:
		[[nodiscard]] static inline EmuSIMD::f64x2 get()
		{
			return _mm_castsi128_pd(_integral_mask_generator::get());
		}
	};
	template<bool AllIndices_>
	struct _per_index_mask<EmuSIMD::f64x2, AllIndices_>
	{
	private:
		using _integral_mask_generator = _per_index_mask<EmuSIMD::i128_generic, AllIndices_>;

	public:
		[[nodiscard]] static inline EmuSIMD::f64x2 get()
		{
			return _mm_castsi128_pd(_integral_mask_generator::get());
		}
	};
#pragma endregion

#pragma region MASK_GENERATORS_256
	template<>
	struct _per_index_mask<EmuSIMD::i256_generic, false>
	{
		[[nodiscard]] static inline EmuSIMD::i256_generic get()
		{
			return _mm256_setzero_si256();
		}
	};
	template<>
	struct _per_index_mask<EmuSIMD::i256_generic, true>
	{
		[[nodiscard]] static inline EmuSIMD::i256_generic get()
		{
			return _mm256_set1_epi64x(0xFFFFFFFFFFFFFFFF);
		}
	};

	template
	<
		bool I0_, bool I1_, bool I2_, bool I3_, bool I4_, bool I5_, bool I6_, bool I7_,
		bool I8_, bool I9_, bool I10_, bool I11_, bool I12_, bool I13_, bool I14_, bool I15_,
		bool I16_, bool I17_, bool I18_, bool I19_, bool I20_, bool I21_, bool I22_, bool I23_,
		bool I24_, bool I25_, bool I26_, bool I27_, bool I28_, bool I29_, bool I30_, bool I31_
	>
	struct _per_index_mask
	<
		EmuSIMD::i256_generic,
		I0_, I1_, I2_, I3_, I4_, I5_, I6_, I7_, I8_, I9_, I10_, I11_, I12_, I13_, I14_, I15_,
		I16_, I17_, I18_, I19_, I20_, I21_, I22_, I23_, I24_, I25_, I26_, I27_, I28_, I29_, I30_, I31_
	>
	{
		[[nodiscard]] static inline EmuSIMD::i256_generic get()
		{
			return _mm256_set_epi8
			(
				EmuCore::TMP::conditional_value_v<I0_,  std::int8_t, std::int8_t(0xFF), 0x00>,
				EmuCore::TMP::conditional_value_v<I1_,  std::int8_t, std::int8_t(0xFF), 0x00>,
				EmuCore::TMP::conditional_value_v<I2_,  std::int8_t, std::int8_t(0xFF), 0x00>,
				EmuCore::TMP::conditional_value_v<I3_,  std::int8_t, std::int8_t(0xFF), 0x00>,
				EmuCore::TMP::conditional_value_v<I4_,  std::int8_t, std::int8_t(0xFF), 0x00>,
				EmuCore::TMP::conditional_value_v<I5_,  std::int8_t, std::int8_t(0xFF), 0x00>,
				EmuCore::TMP::conditional_value_v<I6_,  std::int8_t, std::int8_t(0xFF), 0x00>,
				EmuCore::TMP::conditional_value_v<I7_,  std::int8_t, std::int8_t(0xFF), 0x00>,
				EmuCore::TMP::conditional_value_v<I8_,  std::int8_t, std::int8_t(0xFF), 0x00>,
				EmuCore::TMP::conditional_value_v<I9_,  std::int8_t, std::int8_t(0xFF), 0x00>,
				EmuCore::TMP::conditional_value_v<I10_, std::int8_t, std::int8_t(0xFF), 0x00>,
				EmuCore::TMP::conditional_value_v<I11_, std::int8_t, std::int8_t(0xFF), 0x00>,
				EmuCore::TMP::conditional_value_v<I12_, std::int8_t, std::int8_t(0xFF), 0x00>,
				EmuCore::TMP::conditional_value_v<I13_, std::int8_t, std::int8_t(0xFF), 0x00>,
				EmuCore::TMP::conditional_value_v<I14_, std::int8_t, std::int8_t(0xFF), 0x00>,
				EmuCore::TMP::conditional_value_v<I15_, std::int8_t, std::int8_t(0xFF), 0x00>,
				EmuCore::TMP::conditional_value_v<I16_, std::int8_t, std::int8_t(0xFF), 0x00>,
				EmuCore::TMP::conditional_value_v<I17_, std::int8_t, std::int8_t(0xFF), 0x00>,
				EmuCore::TMP::conditional_value_v<I18_, std::int8_t, std::int8_t(0xFF), 0x00>,
				EmuCore::TMP::conditional_value_v<I19_, std::int8_t, std::int8_t(0xFF), 0x00>,
				EmuCore::TMP::conditional_value_v<I20_, std::int8_t, std::int8_t(0xFF), 0x00>,
				EmuCore::TMP::conditional_value_v<I21_, std::int8_t, std::int8_t(0xFF), 0x00>,
				EmuCore::TMP::conditional_value_v<I22_, std::int8_t, std::int8_t(0xFF), 0x00>,
				EmuCore::TMP::conditional_value_v<I23_, std::int8_t, std::int8_t(0xFF), 0x00>,
				EmuCore::TMP::conditional_value_v<I24_, std::int8_t, std::int8_t(0xFF), 0x00>,
				EmuCore::TMP::conditional_value_v<I25_, std::int8_t, std::int8_t(0xFF), 0x00>,
				EmuCore::TMP::conditional_value_v<I26_, std::int8_t, std::int8_t(0xFF), 0x00>,
				EmuCore::TMP::conditional_value_v<I27_, std::int8_t, std::int8_t(0xFF), 0x00>,
				EmuCore::TMP::conditional_value_v<I28_, std::int8_t, std::int8_t(0xFF), 0x00>,
				EmuCore::TMP::conditional_value_v<I29_, std::int8_t, std::int8_t(0xFF), 0x00>,
				EmuCore::TMP::conditional_value_v<I30_, std::int8_t, std::int8_t(0xFF), 0x00>,
				EmuCore::TMP::conditional_value_v<I31_, std::int8_t, std::int8_t(0xFF), 0x00>
			);
		}
	};
	template<>
	struct _per_index_mask
	<
		EmuSIMD::i256_generic,
		false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false,
		false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false
	>
	{
		[[nodiscard]] static inline EmuSIMD::i256_generic get()
		{
			return _per_index_mask<EmuSIMD::i256_generic, false>::get();
		}
	};
	template<>
	struct _per_index_mask
	<
		EmuSIMD::i256_generic,
		true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true,
		true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true
	>
	{
		[[nodiscard]] static inline EmuSIMD::i256_generic get()
		{
			return _per_index_mask<EmuSIMD::i256_generic, true>::get();
		}
	};

	template
	<
		bool I0_, bool I1_, bool I2_, bool I3_, bool I4_, bool I5_, bool I6_, bool I7_,
		bool I8_, bool I9_, bool I10_, bool I11_, bool I12_, bool I13_, bool I14_, bool I15_
	>
	struct _per_index_mask<EmuSIMD::i256_generic, I0_, I1_, I2_, I3_, I4_, I5_, I6_, I7_, I8_, I9_, I10_, I11_, I12_, I13_, I14_, I15_>
	{
		[[nodiscard]] static inline EmuSIMD::i256_generic get()
		{
			return _mm256_set_epi16
			(
				EmuCore::TMP::conditional_value_v<I0_,  std::int16_t, std::int16_t(0xFFFF), 0x0000>,
				EmuCore::TMP::conditional_value_v<I1_,  std::int16_t, std::int16_t(0xFFFF), 0x0000>,
				EmuCore::TMP::conditional_value_v<I2_,  std::int16_t, std::int16_t(0xFFFF), 0x0000>,
				EmuCore::TMP::conditional_value_v<I3_,  std::int16_t, std::int16_t(0xFFFF), 0x0000>,
				EmuCore::TMP::conditional_value_v<I4_,  std::int16_t, std::int16_t(0xFFFF), 0x0000>,
				EmuCore::TMP::conditional_value_v<I5_,  std::int16_t, std::int16_t(0xFFFF), 0x0000>,
				EmuCore::TMP::conditional_value_v<I6_,  std::int16_t, std::int16_t(0xFFFF), 0x0000>,
				EmuCore::TMP::conditional_value_v<I7_,  std::int16_t, std::int16_t(0xFFFF), 0x0000>,
				EmuCore::TMP::conditional_value_v<I8_,  std::int16_t, std::int16_t(0xFFFF), 0x0000>,
				EmuCore::TMP::conditional_value_v<I9_,  std::int16_t, std::int16_t(0xFFFF), 0x0000>,
				EmuCore::TMP::conditional_value_v<I10_, std::int16_t, std::int16_t(0xFFFF), 0x0000>,
				EmuCore::TMP::conditional_value_v<I11_, std::int16_t, std::int16_t(0xFFFF), 0x0000>,
				EmuCore::TMP::conditional_value_v<I12_, std::int16_t, std::int16_t(0xFFFF), 0x0000>,
				EmuCore::TMP::conditional_value_v<I13_, std::int16_t, std::int16_t(0xFFFF), 0x0000>,
				EmuCore::TMP::conditional_value_v<I14_, std::int16_t, std::int16_t(0xFFFF), 0x0000>,
				EmuCore::TMP::conditional_value_v<I15_, std::int16_t, std::int16_t(0xFFFF), 0x0000>
			);
		}
	};
	template<>
	struct _per_index_mask<EmuSIMD::i256_generic, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false>
	{
		[[nodiscard]] static inline EmuSIMD::i256_generic get()
		{
			return _per_index_mask<EmuSIMD::i256_generic, false>::get();
		}
	};
	template<>
	struct _per_index_mask<EmuSIMD::i256_generic, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true>
	{
		[[nodiscard]] static inline EmuSIMD::i256_generic get()
		{
			return _per_index_mask<EmuSIMD::i256_generic, true>::get();
		}
	};

	template<bool I0_, bool I1_, bool I2_, bool I3_, bool I4_, bool I5_, bool I6_, bool I7_>
	struct _per_index_mask<EmuSIMD::i256_generic, I0_, I1_, I2_, I3_, I4_, I5_, I6_, I7_>
	{
		[[nodiscard]] static inline EmuSIMD::i256_generic get()
		{
			return _mm256_set_epi32
			(
				EmuCore::TMP::conditional_value_v<I0_,  std::int32_t, std::int32_t(0xFFFFFFFF), 0x00000000>,
				EmuCore::TMP::conditional_value_v<I1_,  std::int32_t, std::int32_t(0xFFFFFFFF), 0x00000000>,
				EmuCore::TMP::conditional_value_v<I2_,  std::int32_t, std::int32_t(0xFFFFFFFF), 0x00000000>,
				EmuCore::TMP::conditional_value_v<I3_,  std::int32_t, std::int32_t(0xFFFFFFFF), 0x00000000>,
				EmuCore::TMP::conditional_value_v<I4_,  std::int32_t, std::int32_t(0xFFFFFFFF), 0x00000000>,
				EmuCore::TMP::conditional_value_v<I5_,  std::int32_t, std::int32_t(0xFFFFFFFF), 0x00000000>,
				EmuCore::TMP::conditional_value_v<I6_,  std::int32_t, std::int32_t(0xFFFFFFFF), 0x00000000>,
				EmuCore::TMP::conditional_value_v<I7_,  std::int32_t, std::int32_t(0xFFFFFFFF), 0x00000000>
			);
		}
	};
	template<>
	struct _per_index_mask<EmuSIMD::i256_generic, false, false, false, false, false, false, false, false>
	{
		[[nodiscard]] static inline EmuSIMD::i256_generic get()
		{
			return _per_index_mask<EmuSIMD::i256_generic, false>::get();
		}
	};
	template<>
	struct _per_index_mask<EmuSIMD::i256_generic, true, true, true, true, true, true, true, true>
	{
		[[nodiscard]] static inline EmuSIMD::i256_generic get()
		{
			return _per_index_mask<EmuSIMD::i256_generic, true>::get();
		}
	};

	template<bool I0_, bool I1_, bool I2_, bool I3_>
	struct _per_index_mask<EmuSIMD::i256_generic, I0_, I1_, I2_, I3_>
	{
		[[nodiscard]] static inline EmuSIMD::i256_generic get()
		{
			return _mm256_set_epi64x
			(
				EmuCore::TMP::conditional_value_v<I0_,  std::int64_t, std::int64_t(0xFFFFFFFFFFFFFFFF), 0x0000000000000000>,
				EmuCore::TMP::conditional_value_v<I1_,  std::int64_t, std::int64_t(0xFFFFFFFFFFFFFFFF), 0x0000000000000000>,
				EmuCore::TMP::conditional_value_v<I2_,  std::int64_t, std::int64_t(0xFFFFFFFFFFFFFFFF), 0x0000000000000000>,
				EmuCore::TMP::conditional_value_v<I3_,  std::int64_t, std::int64_t(0xFFFFFFFFFFFFFFFF), 0x0000000000000000>
			);
		}
	};
	template<>
	struct _per_index_mask<EmuSIMD::i256_generic, false, false, false, false>
	{
		[[nodiscard]] static inline EmuSIMD::i256_generic get()
		{
			return _per_index_mask<EmuSIMD::i256_generic, false>::get();
		}
	};
	template<>
	struct _per_index_mask<EmuSIMD::i256_generic, true, true, true, true>
	{
		[[nodiscard]] static inline EmuSIMD::i256_generic get()
		{
			return _per_index_mask<EmuSIMD::i256_generic, true>::get();
		}
	};

	template<bool I0_, bool I1_, bool I2_, bool I3_, bool I4_, bool I5_, bool I6_, bool I7_>
	struct _per_index_mask<EmuSIMD::f32x8, I0_, I1_, I2_, I3_, I4_, I5_, I6_, I7_>
	{
	private:
		using _integral_mask_generator = _per_index_mask<EmuSIMD::i256_generic, I0_, I1_, I2_, I3_, I4_, I5_, I6_, I7_>;

	public:
		[[nodiscard]] static inline EmuSIMD::f32x8 get()
		{
			return _mm256_castsi256_ps(_integral_mask_generator::get());
		}
	};
	template<bool AllIndices_>
	struct _per_index_mask<EmuSIMD::f32x8, AllIndices_>
	{
	private:
		using _integral_mask_generator = _per_index_mask<EmuSIMD::i256_generic, AllIndices_>;

	public:
		[[nodiscard]] static inline EmuSIMD::f32x8 get()
		{
			return _mm256_castsi256_ps(_integral_mask_generator::get());
		}
	};

	template<bool I0_, bool I1_, bool I2_, bool I3_>
	struct _per_index_mask<EmuSIMD::f64x4, I0_, I1_, I2_, I3_>
	{
	private:
		using _integral_mask_generator = _per_index_mask<EmuSIMD::i256_generic, I0_, I1_, I2_, I3_>;

	public:
		[[nodiscard]] static inline EmuSIMD::f64x4 get()
		{
			return _mm256_castsi256_pd(_integral_mask_generator::get());
		}
	};
	template<bool AllIndices_>
	struct _per_index_mask<EmuSIMD::f64x4, AllIndices_>
	{
	private:
		using _integral_mask_generator = _per_index_mask<EmuSIMD::i256_generic, AllIndices_>;

	public:
		[[nodiscard]] static inline EmuSIMD::f64x4 get()
		{
			return _mm256_castsi256_pd(_integral_mask_generator::get());
		}
	};
#pragma endregion

#pragma region MASK_GENERATORS_512
	template<>
	struct _per_index_mask<EmuSIMD::i512_generic, false>
	{
		[[nodiscard]] static inline EmuSIMD::i512_generic get()
		{
			return _mm512_setzero_si512();
		}
	};
	template<>
	struct _per_index_mask<EmuSIMD::i512_generic, true>
	{
		[[nodiscard]] static inline EmuSIMD::i512_generic get()
		{
			return _mm512_set1_epi64(0xFFFFFFFFFFFFFFFF);
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
	struct _per_index_mask
	<
		EmuSIMD::i512_generic,
		I0_,  I1_,  I2_,  I3_,  I4_,  I5_,  I6_,  I7_,  I8_,  I9_,  I10_, I11_, I12_, I13_, I14_, I15_,
		I16_, I17_, I18_, I19_, I20_, I21_, I22_, I23_, I24_, I25_, I26_, I27_, I28_, I29_, I30_, I31_,
		I32_, I33_, I34_, I35_, I36_, I37_, I38_, I39_, I40_, I41_, I42_, I43_, I44_, I45_, I46_, I47_,
		I48_, I49_, I50_, I51_, I52_, I53_, I54_, I55_, I56_, I57_, I58_, I59_, I60_, I61_, I62_, I63_
	>
	{
		[[nodiscard]] static inline EmuSIMD::i512_generic get()
		{
			return _mm512_set_epi8
			(
				EmuCore::TMP::conditional_value_v<I0_,  std::int8_t, std::int8_t(0xFF), 0x00>,
				EmuCore::TMP::conditional_value_v<I1_,  std::int8_t, std::int8_t(0xFF), 0x00>,
				EmuCore::TMP::conditional_value_v<I2_,  std::int8_t, std::int8_t(0xFF), 0x00>,
				EmuCore::TMP::conditional_value_v<I3_,  std::int8_t, std::int8_t(0xFF), 0x00>,
				EmuCore::TMP::conditional_value_v<I4_,  std::int8_t, std::int8_t(0xFF), 0x00>,
				EmuCore::TMP::conditional_value_v<I5_,  std::int8_t, std::int8_t(0xFF), 0x00>,
				EmuCore::TMP::conditional_value_v<I6_,  std::int8_t, std::int8_t(0xFF), 0x00>,
				EmuCore::TMP::conditional_value_v<I7_,  std::int8_t, std::int8_t(0xFF), 0x00>,
				EmuCore::TMP::conditional_value_v<I8_,  std::int8_t, std::int8_t(0xFF), 0x00>,
				EmuCore::TMP::conditional_value_v<I9_,  std::int8_t, std::int8_t(0xFF), 0x00>,
				EmuCore::TMP::conditional_value_v<I10_, std::int8_t, std::int8_t(0xFF), 0x00>,
				EmuCore::TMP::conditional_value_v<I11_, std::int8_t, std::int8_t(0xFF), 0x00>,
				EmuCore::TMP::conditional_value_v<I12_, std::int8_t, std::int8_t(0xFF), 0x00>,
				EmuCore::TMP::conditional_value_v<I13_, std::int8_t, std::int8_t(0xFF), 0x00>,
				EmuCore::TMP::conditional_value_v<I14_, std::int8_t, std::int8_t(0xFF), 0x00>,
				EmuCore::TMP::conditional_value_v<I15_, std::int8_t, std::int8_t(0xFF), 0x00>,
				EmuCore::TMP::conditional_value_v<I16_, std::int8_t, std::int8_t(0xFF), 0x00>,
				EmuCore::TMP::conditional_value_v<I17_, std::int8_t, std::int8_t(0xFF), 0x00>,
				EmuCore::TMP::conditional_value_v<I18_, std::int8_t, std::int8_t(0xFF), 0x00>,
				EmuCore::TMP::conditional_value_v<I19_, std::int8_t, std::int8_t(0xFF), 0x00>,
				EmuCore::TMP::conditional_value_v<I20_, std::int8_t, std::int8_t(0xFF), 0x00>,
				EmuCore::TMP::conditional_value_v<I21_, std::int8_t, std::int8_t(0xFF), 0x00>,
				EmuCore::TMP::conditional_value_v<I22_, std::int8_t, std::int8_t(0xFF), 0x00>,
				EmuCore::TMP::conditional_value_v<I23_, std::int8_t, std::int8_t(0xFF), 0x00>,
				EmuCore::TMP::conditional_value_v<I24_, std::int8_t, std::int8_t(0xFF), 0x00>,
				EmuCore::TMP::conditional_value_v<I25_, std::int8_t, std::int8_t(0xFF), 0x00>,
				EmuCore::TMP::conditional_value_v<I26_, std::int8_t, std::int8_t(0xFF), 0x00>,
				EmuCore::TMP::conditional_value_v<I27_, std::int8_t, std::int8_t(0xFF), 0x00>,
				EmuCore::TMP::conditional_value_v<I28_, std::int8_t, std::int8_t(0xFF), 0x00>,
				EmuCore::TMP::conditional_value_v<I29_, std::int8_t, std::int8_t(0xFF), 0x00>,
				EmuCore::TMP::conditional_value_v<I30_, std::int8_t, std::int8_t(0xFF), 0x00>,
				EmuCore::TMP::conditional_value_v<I31_, std::int8_t, std::int8_t(0xFF), 0x00>,
				EmuCore::TMP::conditional_value_v<I32_, std::int8_t, std::int8_t(0xFF), 0x00>,
				EmuCore::TMP::conditional_value_v<I33_, std::int8_t, std::int8_t(0xFF), 0x00>,
				EmuCore::TMP::conditional_value_v<I34_, std::int8_t, std::int8_t(0xFF), 0x00>,
				EmuCore::TMP::conditional_value_v<I35_, std::int8_t, std::int8_t(0xFF), 0x00>,
				EmuCore::TMP::conditional_value_v<I36_, std::int8_t, std::int8_t(0xFF), 0x00>,
				EmuCore::TMP::conditional_value_v<I37_, std::int8_t, std::int8_t(0xFF), 0x00>,
				EmuCore::TMP::conditional_value_v<I38_, std::int8_t, std::int8_t(0xFF), 0x00>,
				EmuCore::TMP::conditional_value_v<I39_, std::int8_t, std::int8_t(0xFF), 0x00>,
				EmuCore::TMP::conditional_value_v<I40_, std::int8_t, std::int8_t(0xFF), 0x00>,
				EmuCore::TMP::conditional_value_v<I41_, std::int8_t, std::int8_t(0xFF), 0x00>,
				EmuCore::TMP::conditional_value_v<I42_, std::int8_t, std::int8_t(0xFF), 0x00>,
				EmuCore::TMP::conditional_value_v<I43_, std::int8_t, std::int8_t(0xFF), 0x00>,
				EmuCore::TMP::conditional_value_v<I44_, std::int8_t, std::int8_t(0xFF), 0x00>,
				EmuCore::TMP::conditional_value_v<I45_, std::int8_t, std::int8_t(0xFF), 0x00>,
				EmuCore::TMP::conditional_value_v<I46_, std::int8_t, std::int8_t(0xFF), 0x00>,
				EmuCore::TMP::conditional_value_v<I47_, std::int8_t, std::int8_t(0xFF), 0x00>,
				EmuCore::TMP::conditional_value_v<I48_, std::int8_t, std::int8_t(0xFF), 0x00>,
				EmuCore::TMP::conditional_value_v<I49_, std::int8_t, std::int8_t(0xFF), 0x00>,
				EmuCore::TMP::conditional_value_v<I50_, std::int8_t, std::int8_t(0xFF), 0x00>,
				EmuCore::TMP::conditional_value_v<I51_, std::int8_t, std::int8_t(0xFF), 0x00>,
				EmuCore::TMP::conditional_value_v<I52_, std::int8_t, std::int8_t(0xFF), 0x00>,
				EmuCore::TMP::conditional_value_v<I53_, std::int8_t, std::int8_t(0xFF), 0x00>,
				EmuCore::TMP::conditional_value_v<I54_, std::int8_t, std::int8_t(0xFF), 0x00>,
				EmuCore::TMP::conditional_value_v<I55_, std::int8_t, std::int8_t(0xFF), 0x00>,
				EmuCore::TMP::conditional_value_v<I56_, std::int8_t, std::int8_t(0xFF), 0x00>,
				EmuCore::TMP::conditional_value_v<I57_, std::int8_t, std::int8_t(0xFF), 0x00>,
				EmuCore::TMP::conditional_value_v<I58_, std::int8_t, std::int8_t(0xFF), 0x00>,
				EmuCore::TMP::conditional_value_v<I59_, std::int8_t, std::int8_t(0xFF), 0x00>,
				EmuCore::TMP::conditional_value_v<I60_, std::int8_t, std::int8_t(0xFF), 0x00>,
				EmuCore::TMP::conditional_value_v<I61_, std::int8_t, std::int8_t(0xFF), 0x00>,
				EmuCore::TMP::conditional_value_v<I62_, std::int8_t, std::int8_t(0xFF), 0x00>,
				EmuCore::TMP::conditional_value_v<I63_, std::int8_t, std::int8_t(0xFF), 0x00>
			);
		}
	};
	template<>
	struct _per_index_mask
	<
		EmuSIMD::i512_generic,
		false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false,
		false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false,
		false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false,
		false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false
	>
	{
		[[nodiscard]] static inline EmuSIMD::i512_generic get()
		{
			return _per_index_mask<EmuSIMD::i512_generic, false>::get();
		}
	};
	template<>
	struct _per_index_mask
	<
		EmuSIMD::i512_generic,
		true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true,
		true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true,
		true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true,
		true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true
	>
	{
		[[nodiscard]] static inline EmuSIMD::i512_generic get()
		{
			return _per_index_mask<EmuSIMD::i512_generic, true>::get();
		}
	};

	template
	<
		bool I0_, bool I1_, bool I2_, bool I3_, bool I4_, bool I5_, bool I6_, bool I7_,
		bool I8_, bool I9_, bool I10_, bool I11_, bool I12_, bool I13_, bool I14_, bool I15_,
		bool I16_, bool I17_, bool I18_, bool I19_, bool I20_, bool I21_, bool I22_, bool I23_,
		bool I24_, bool I25_, bool I26_, bool I27_, bool I28_, bool I29_, bool I30_, bool I31_
	>
	struct _per_index_mask
	<
		EmuSIMD::i512_generic,
		I0_, I1_, I2_, I3_, I4_, I5_, I6_, I7_, I8_, I9_, I10_, I11_, I12_, I13_, I14_, I15_,
		I16_, I17_, I18_, I19_, I20_, I21_, I22_, I23_, I24_, I25_, I26_, I27_, I28_, I29_, I30_, I31_
	>
	{
		[[nodiscard]] static inline EmuSIMD::i512_generic get()
		{
			return _mm256_set_epi16
			(
				EmuCore::TMP::conditional_value_v<I0_,  std::int16_t, std::int16_t(0xFFFF), 0x0000>,
				EmuCore::TMP::conditional_value_v<I1_,  std::int16_t, std::int16_t(0xFFFF), 0x0000>,
				EmuCore::TMP::conditional_value_v<I2_,  std::int16_t, std::int16_t(0xFFFF), 0x0000>,
				EmuCore::TMP::conditional_value_v<I3_,  std::int16_t, std::int16_t(0xFFFF), 0x0000>,
				EmuCore::TMP::conditional_value_v<I4_,  std::int16_t, std::int16_t(0xFFFF), 0x0000>,
				EmuCore::TMP::conditional_value_v<I5_,  std::int16_t, std::int16_t(0xFFFF), 0x0000>,
				EmuCore::TMP::conditional_value_v<I6_,  std::int16_t, std::int16_t(0xFFFF), 0x0000>,
				EmuCore::TMP::conditional_value_v<I7_,  std::int16_t, std::int16_t(0xFFFF), 0x0000>,
				EmuCore::TMP::conditional_value_v<I8_,  std::int16_t, std::int16_t(0xFFFF), 0x0000>,
				EmuCore::TMP::conditional_value_v<I9_,  std::int16_t, std::int16_t(0xFFFF), 0x0000>,
				EmuCore::TMP::conditional_value_v<I10_, std::int16_t, std::int16_t(0xFFFF), 0x0000>,
				EmuCore::TMP::conditional_value_v<I11_, std::int16_t, std::int16_t(0xFFFF), 0x0000>,
				EmuCore::TMP::conditional_value_v<I12_, std::int16_t, std::int16_t(0xFFFF), 0x0000>,
				EmuCore::TMP::conditional_value_v<I13_, std::int16_t, std::int16_t(0xFFFF), 0x0000>,
				EmuCore::TMP::conditional_value_v<I14_, std::int16_t, std::int16_t(0xFFFF), 0x0000>,
				EmuCore::TMP::conditional_value_v<I15_, std::int16_t, std::int16_t(0xFFFF), 0x0000>,
				EmuCore::TMP::conditional_value_v<I16_, std::int16_t, std::int16_t(0xFFFF), 0x0000>,
				EmuCore::TMP::conditional_value_v<I17_, std::int16_t, std::int16_t(0xFFFF), 0x0000>,
				EmuCore::TMP::conditional_value_v<I18_, std::int16_t, std::int16_t(0xFFFF), 0x0000>,
				EmuCore::TMP::conditional_value_v<I19_, std::int16_t, std::int16_t(0xFFFF), 0x0000>,
				EmuCore::TMP::conditional_value_v<I20_, std::int16_t, std::int16_t(0xFFFF), 0x0000>,
				EmuCore::TMP::conditional_value_v<I21_, std::int16_t, std::int16_t(0xFFFF), 0x0000>,
				EmuCore::TMP::conditional_value_v<I22_, std::int16_t, std::int16_t(0xFFFF), 0x0000>,
				EmuCore::TMP::conditional_value_v<I23_, std::int16_t, std::int16_t(0xFFFF), 0x0000>,
				EmuCore::TMP::conditional_value_v<I24_, std::int16_t, std::int16_t(0xFFFF), 0x0000>,
				EmuCore::TMP::conditional_value_v<I25_, std::int16_t, std::int16_t(0xFFFF), 0x0000>,
				EmuCore::TMP::conditional_value_v<I26_, std::int16_t, std::int16_t(0xFFFF), 0x0000>,
				EmuCore::TMP::conditional_value_v<I27_, std::int16_t, std::int16_t(0xFFFF), 0x0000>,
				EmuCore::TMP::conditional_value_v<I28_, std::int16_t, std::int16_t(0xFFFF), 0x0000>,
				EmuCore::TMP::conditional_value_v<I29_, std::int16_t, std::int16_t(0xFFFF), 0x0000>,
				EmuCore::TMP::conditional_value_v<I30_, std::int16_t, std::int16_t(0xFFFF), 0x0000>,
				EmuCore::TMP::conditional_value_v<I31_, std::int16_t, std::int16_t(0xFFFF), 0x0000>
			);
		}
	};
	template<>
	struct _per_index_mask
	<
		EmuSIMD::i512_generic,
		false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false,
		false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false
	>
	{
		[[nodiscard]] static inline EmuSIMD::i512_generic get()
		{
			return _per_index_mask<EmuSIMD::i512_generic, false>::get();
		}
	};
	template<>
	struct _per_index_mask
	<
		EmuSIMD::i512_generic,
		true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true,
		true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true
	>
	{
		[[nodiscard]] static inline EmuSIMD::i512_generic get()
		{
			return _per_index_mask<EmuSIMD::i512_generic, true>::get();
		}
	};

	template
	<
		bool I0_, bool I1_, bool I2_, bool I3_, bool I4_, bool I5_, bool I6_, bool I7_,
		bool I8_, bool I9_, bool I10_, bool I11_, bool I12_, bool I13_, bool I14_, bool I15_
	>
	struct _per_index_mask<EmuSIMD::i512_generic, I0_, I1_, I2_, I3_, I4_, I5_, I6_, I7_, I8_, I9_, I10_, I11_, I12_, I13_, I14_, I15_>
	{
		[[nodiscard]] static inline EmuSIMD::i512_generic get()
		{
			return _mm512_set_epi32
			(
				EmuCore::TMP::conditional_value_v<I0_,  std::int32_t, std::int32_t(0xFFFFFFFF), 0x00000000>,
				EmuCore::TMP::conditional_value_v<I1_,  std::int32_t, std::int32_t(0xFFFFFFFF), 0x00000000>,
				EmuCore::TMP::conditional_value_v<I2_,  std::int32_t, std::int32_t(0xFFFFFFFF), 0x00000000>,
				EmuCore::TMP::conditional_value_v<I3_,  std::int32_t, std::int32_t(0xFFFFFFFF), 0x00000000>,
				EmuCore::TMP::conditional_value_v<I4_,  std::int32_t, std::int32_t(0xFFFFFFFF), 0x00000000>,
				EmuCore::TMP::conditional_value_v<I5_,  std::int32_t, std::int32_t(0xFFFFFFFF), 0x00000000>,
				EmuCore::TMP::conditional_value_v<I6_,  std::int32_t, std::int32_t(0xFFFFFFFF), 0x00000000>,
				EmuCore::TMP::conditional_value_v<I7_,  std::int32_t, std::int32_t(0xFFFFFFFF), 0x00000000>,
				EmuCore::TMP::conditional_value_v<I8_,  std::int32_t, std::int32_t(0xFFFFFFFF), 0x00000000>,
				EmuCore::TMP::conditional_value_v<I9_,  std::int32_t, std::int32_t(0xFFFFFFFF), 0x00000000>,
				EmuCore::TMP::conditional_value_v<I10_, std::int32_t, std::int32_t(0xFFFFFFFF), 0x00000000>,
				EmuCore::TMP::conditional_value_v<I11_, std::int32_t, std::int32_t(0xFFFFFFFF), 0x00000000>,
				EmuCore::TMP::conditional_value_v<I12_, std::int32_t, std::int32_t(0xFFFFFFFF), 0x00000000>,
				EmuCore::TMP::conditional_value_v<I13_, std::int32_t, std::int32_t(0xFFFFFFFF), 0x00000000>,
				EmuCore::TMP::conditional_value_v<I14_, std::int32_t, std::int32_t(0xFFFFFFFF), 0x00000000>,
				EmuCore::TMP::conditional_value_v<I15_, std::int32_t, std::int32_t(0xFFFFFFFF), 0x00000000>
			);
		}
	};
	template<>
	struct _per_index_mask<EmuSIMD::i512_generic, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false>
	{
		[[nodiscard]] static inline EmuSIMD::i512_generic get()
		{
			return _per_index_mask<EmuSIMD::i512_generic, false>::get();
		}
	};
	template<>
	struct _per_index_mask<EmuSIMD::i512_generic, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true>
	{
		[[nodiscard]] static inline EmuSIMD::i512_generic get()
		{
			return _per_index_mask<EmuSIMD::i512_generic, true>::get();
		}
	};

	template<bool I0_, bool I1_, bool I2_, bool I3_, bool I4_, bool I5_, bool I6_, bool I7_>
	struct _per_index_mask<EmuSIMD::i512_generic, I0_, I1_, I2_, I3_, I4_, I5_, I6_, I7_>
	{
		[[nodiscard]] static inline EmuSIMD::i512_generic get()
		{
			return _mm512_set_epi64
			(
				EmuCore::TMP::conditional_value_v<I0_,  std::int64_t, std::int64_t(0xFFFFFFFFFFFFFFFF), 0x0000000000000000>,
				EmuCore::TMP::conditional_value_v<I1_,  std::int64_t, std::int64_t(0xFFFFFFFFFFFFFFFF), 0x0000000000000000>,
				EmuCore::TMP::conditional_value_v<I2_,  std::int64_t, std::int64_t(0xFFFFFFFFFFFFFFFF), 0x0000000000000000>,
				EmuCore::TMP::conditional_value_v<I3_,  std::int64_t, std::int64_t(0xFFFFFFFFFFFFFFFF), 0x0000000000000000>,
				EmuCore::TMP::conditional_value_v<I4_,  std::int64_t, std::int64_t(0xFFFFFFFFFFFFFFFF), 0x0000000000000000>,
				EmuCore::TMP::conditional_value_v<I5_,  std::int64_t, std::int64_t(0xFFFFFFFFFFFFFFFF), 0x0000000000000000>,
				EmuCore::TMP::conditional_value_v<I6_,  std::int64_t, std::int64_t(0xFFFFFFFFFFFFFFFF), 0x0000000000000000>,
				EmuCore::TMP::conditional_value_v<I7_,  std::int64_t, std::int64_t(0xFFFFFFFFFFFFFFFF), 0x0000000000000000>
			);
		}
	};
	template<>
	struct _per_index_mask<EmuSIMD::i512_generic, false, false, false, false, false, false, false, false>
	{
		[[nodiscard]] static inline EmuSIMD::i512_generic get()
		{
			return _per_index_mask<EmuSIMD::i512_generic, false>::get();
		}
	};
	template<>
	struct _per_index_mask<EmuSIMD::i512_generic, true, true, true, true, true, true, true, true>
	{
		[[nodiscard]] static inline EmuSIMD::i512_generic get()
		{
			return _per_index_mask<EmuSIMD::i512_generic, true>::get();
		}
	};

	template
	<
		bool I0_, bool I1_, bool I2_,  bool I3_,  bool I4_,  bool I5_,  bool I6_,  bool I7_,
		bool I8_, bool I9_, bool I10_, bool I11_, bool I12_, bool I13_, bool I14_, bool I15_
	>
	struct _per_index_mask<EmuSIMD::f32x16, I0_, I1_, I2_, I3_, I4_, I5_, I6_, I7_, I8_, I9_, I10_, I11_, I12_, I13_, I14_, I15_>
	{
	private:
		using _integral_mask_generator = _per_index_mask<EmuSIMD::i512_generic, I0_, I1_, I2_, I3_, I4_, I5_, I6_, I7_, I8_, I9_, I10_, I11_, I12_, I13_, I14_, I15_>;

	public:
		[[nodiscard]] static inline EmuSIMD::f32x16 get()
		{
			return _mm512_castsi512_ps(_integral_mask_generator::get());
		}
	};
	template<bool AllIndices_>
	struct _per_index_mask<EmuSIMD::f32x16, AllIndices_>
	{
	private:
		using _integral_mask_generator = _per_index_mask<EmuSIMD::i512_generic, AllIndices_>;

	public:
		[[nodiscard]] static inline EmuSIMD::f32x16 get()
		{
			return _mm512_castsi512_ps(_integral_mask_generator::get());
		}
	};

	template<bool I0_, bool I1_, bool I2_,  bool I3_,  bool I4_,  bool I5_,  bool I6_,  bool I7_>
	struct _per_index_mask<EmuSIMD::f64x8, I0_, I1_, I2_, I3_, I4_, I5_, I6_, I7_>
	{
	private:
		using _integral_mask_generator = _per_index_mask<EmuSIMD::i512_generic, I0_, I1_, I2_, I3_, I4_, I5_, I6_, I7_>;

	public:
		[[nodiscard]] static inline EmuSIMD::f64x8 get()
		{
			return _mm512_castsi512_pd(_integral_mask_generator::get());
		}
	};
	template<bool AllIndices_>
	struct _per_index_mask<EmuSIMD::f64x8, AllIndices_>
	{
	private:
		using _integral_mask_generator = _per_index_mask<EmuSIMD::i512_generic, AllIndices_>;

	public:
		[[nodiscard]] static inline EmuSIMD::f64x8 get()
		{
			return _mm512_castsi512_pd(_integral_mask_generator::get());
		}
	};
#pragma endregion

#pragma region SINGLE_INDEX_MASK_ABSTRACTIONS
	template<class Register_, std::size_t Index_, std::size_t PerElementWidthIfInt_ = 32>
	struct _single_index_mask
	{
	};

	template<std::size_t Index_, std::size_t PerElementWidthIfInt_>
	struct _single_index_mask<EmuSIMD::f32x4, Index_, PerElementWidthIfInt_>
	{
	private:
		static_assert(EmuSIMD::TMP::valid_register_index_v<EmuSIMD::f32x4, Index_>, "Invalid index provided when attempting to retrieve a single index mask for a EmuSIMD::f32x4 SIMD register.");
		
		using _mask_generator = _per_index_mask
		<
			EmuSIMD::f32x4,
			Index_ == 0,
			Index_ == 1,
			Index_ == 2,
			Index_ == 3
		>;

	public:
		[[nodiscard]] static inline EmuSIMD::f32x4 get()
		{
			return _mask_generator::get();
		}
	};

	template<std::size_t Index_, std::size_t PerElementWidthIfInt_>
	struct _single_index_mask<EmuSIMD::f32x8, Index_, PerElementWidthIfInt_>
	{
	private:
		static_assert(EmuSIMD::TMP::valid_register_index_v<EmuSIMD::f32x8, Index_>, "Invalid index provided when attempting to retrieve a single index mask for a EmuSIMD::f32x8 SIMD register.");

		using _mask_generator = _per_index_mask
		<
			EmuSIMD::f32x8,
			Index_ == 0,
			Index_ == 1,
			Index_ == 2,
			Index_ == 3,
			Index_ == 4,
			Index_ == 5,
			Index_ == 6,
			Index_ == 7
		>;

	public:
		[[nodiscard]] static inline EmuSIMD::f32x8 get()
		{
			return _mask_generator::get();
		}
	};

	template<std::size_t Index_, std::size_t PerElementWidthIfInt_>
	struct _single_index_mask<EmuSIMD::f32x16, Index_, PerElementWidthIfInt_>
	{
	private:
		static_assert(EmuSIMD::TMP::valid_register_index_v<EmuSIMD::f32x16, Index_>, "Invalid index provided when attempting to retrieve a single index mask for a EmuSIMD::f32x16 SIMD register.");

		using _mask_generator = _per_index_mask
		<
			EmuSIMD::f32x16,
			Index_ == 0,
			Index_ == 1,
			Index_ == 2,
			Index_ == 3,
			Index_ == 4,
			Index_ == 5,
			Index_ == 6,
			Index_ == 7,
			Index_ == 8,
			Index_ == 9,
			Index_ == 10,
			Index_ == 11,
			Index_ == 12,
			Index_ == 13,
			Index_ == 14,
			Index_ == 15
		>;

	public:
		[[nodiscard]] static inline EmuSIMD::f32x16 get()
		{
			return _mask_generator::get();
		}
	};

	template<std::size_t Index_, std::size_t PerElementWidthIfInt_>
	struct _single_index_mask<EmuSIMD::f64x2, Index_, PerElementWidthIfInt_>
	{
	private:
		static_assert(EmuSIMD::TMP::valid_register_index_v<EmuSIMD::f64x2, Index_>, "Invalid index provided when attempting to retrieve a single index mask for a EmuSIMD::f64x2 SIMD register.");

		using _mask_generator = _per_index_mask
		<
			EmuSIMD::f64x2,
			Index_ == 0,
			Index_ == 1
		>;

	public:
		[[nodiscard]] static inline EmuSIMD::f64x2 get()
		{
			return _mask_generator::get();
		}
	};

	template<std::size_t Index_, std::size_t PerElementWidthIfInt_>
	struct _single_index_mask<EmuSIMD::f64x4, Index_, PerElementWidthIfInt_>
	{
	private:
		static_assert(EmuSIMD::TMP::valid_register_index_v<EmuSIMD::f64x4, Index_>, "Invalid index provided when attempting to retrieve a single index mask for a EmuSIMD::f64x4 SIMD register.");

		using _mask_generator = _per_index_mask
		<
			EmuSIMD::f64x4,
			Index_ == 0,
			Index_ == 1,
			Index_ == 2,
			Index_ == 3
		>;

	public:
		[[nodiscard]] static inline EmuSIMD::f64x4 get()
		{
			return _mask_generator::get();
		}
	};

	template<std::size_t Index_, std::size_t PerElementWidthIfInt_>
	struct _single_index_mask<EmuSIMD::f64x8, Index_, PerElementWidthIfInt_>
	{
	private:
		static_assert(EmuSIMD::TMP::valid_register_index_v<EmuSIMD::f64x8, Index_>, "Invalid index provided when attempting to retrieve a single index mask for a EmuSIMD::f64x8 SIMD register.");

		using _mask_generator = _per_index_mask
		<
			EmuSIMD::f64x8,
			Index_ == 0,
			Index_ == 1,
			Index_ == 2,
			Index_ == 3,
			Index_ == 4,
			Index_ == 5,
			Index_ == 6,
			Index_ == 7
		>;

	public:
		[[nodiscard]] static inline EmuSIMD::f64x8 get()
		{
			return _mask_generator::get();
		}
	};

	template<std::size_t Index_>
	struct _single_index_mask<EmuSIMD::i128_generic, Index_, 8>
	{
	private:
		static_assert(EmuSIMD::TMP::valid_register_index_v<EmuSIMD::i128_generic, Index_, 8>, "Invalid index provided when attempting to retrieve a single index mask for a EmuSIMD::i128_generic SIMD register with 8-bit elements.");

		using _mask_generator = _per_index_mask
		<
			EmuSIMD::i128_generic,
			Index_ == 0,
			Index_ == 1,
			Index_ == 2,
			Index_ == 3,
			Index_ == 4,
			Index_ == 5,
			Index_ == 6,
			Index_ == 7,
			Index_ == 8,
			Index_ == 9,
			Index_ == 10,
			Index_ == 11,
			Index_ == 12,
			Index_ == 13,
			Index_ == 14,
			Index_ == 15
		>;

	public:
		[[nodiscard]] static inline EmuSIMD::i128_generic get()
		{
			return _mask_generator::get();
		}
	};

	template<std::size_t Index_>
	struct _single_index_mask<EmuSIMD::i128_generic, Index_, 16>
	{
	private:
		static_assert(EmuSIMD::TMP::valid_register_index_v<EmuSIMD::i128_generic, Index_, 16>, "Invalid index provided when attempting to retrieve a single index mask for a EmuSIMD::i128_generic SIMD register with 16-bit elements.");

		using _mask_generator = _per_index_mask
		<
			EmuSIMD::i128_generic,
			Index_ == 0,
			Index_ == 1,
			Index_ == 2,
			Index_ == 3,
			Index_ == 4,
			Index_ == 5,
			Index_ == 6,
			Index_ == 7
		>;

	public:
		[[nodiscard]] static inline EmuSIMD::i128_generic get()
		{
			return _mask_generator::get();
		}
	};

	template<std::size_t Index_>
	struct _single_index_mask<EmuSIMD::i128_generic, Index_, 32>
	{
	private:
		static_assert(EmuSIMD::TMP::valid_register_index_v<EmuSIMD::i128_generic, Index_, 32>, "Invalid index provided when attempting to retrieve a single index mask for a EmuSIMD::i128_generic SIMD register with 32-bit elements.");

		using _mask_generator = _per_index_mask
		<
			EmuSIMD::i128_generic,
			Index_ == 0,
			Index_ == 1,
			Index_ == 2,
			Index_ == 3
		>;

	public:
		[[nodiscard]] static inline EmuSIMD::i128_generic get()
		{
			return _mask_generator::get();
		}
	};

	template<std::size_t Index_>
	struct _single_index_mask<EmuSIMD::i128_generic, Index_, 64>
	{
	private:
		static_assert(EmuSIMD::TMP::valid_register_index_v<EmuSIMD::i128_generic, Index_, 64>, "Invalid index provided when attempting to retrieve a single index mask for a EmuSIMD::i128_generic SIMD register with 64-bit elements.");

		using _mask_generator = _per_index_mask
		<
			EmuSIMD::i128_generic,
			Index_ == 0,
			Index_ == 1
		>;

	public:
		[[nodiscard]] static inline EmuSIMD::i128_generic get()
		{
			return _mask_generator::get();
		}
	};

	template<std::size_t Index_>
	struct _single_index_mask<EmuSIMD::i256_generic, Index_, 8>
	{
	private:
		static_assert(EmuSIMD::TMP::valid_register_index_v<EmuSIMD::i256_generic, Index_, 8>, "Invalid index provided when attempting to retrieve a single index mask for a EmuSIMD::i256_generic SIMD register with 8-bit elements.");

		using _mask_generator = _per_index_mask
		<
			EmuSIMD::i256_generic,
			Index_ == 0,
			Index_ == 1,
			Index_ == 2,
			Index_ == 3,
			Index_ == 4,
			Index_ == 5,
			Index_ == 6,
			Index_ == 7,
			Index_ == 8,
			Index_ == 9,
			Index_ == 10,
			Index_ == 11,
			Index_ == 12,
			Index_ == 13,
			Index_ == 14,
			Index_ == 15,
			Index_ == 16,
			Index_ == 17,
			Index_ == 18,
			Index_ == 19,
			Index_ == 20,
			Index_ == 21,
			Index_ == 22,
			Index_ == 23,
			Index_ == 24,
			Index_ == 25,
			Index_ == 26,
			Index_ == 27,
			Index_ == 28,
			Index_ == 29,
			Index_ == 30,
			Index_ == 31
		>;

	public:
		[[nodiscard]] static inline EmuSIMD::i256_generic get()
		{
			return _mask_generator::get();
		}
	};

	template<std::size_t Index_>
	struct _single_index_mask<EmuSIMD::i256_generic, Index_, 16>
	{
	private:
		static_assert(EmuSIMD::TMP::valid_register_index_v<EmuSIMD::i256_generic, Index_, 16>, "Invalid index provided when attempting to retrieve a single index mask for a EmuSIMD::i256_generic SIMD register with 16-bit elements.");

		using _mask_generator = _per_index_mask
		<
			EmuSIMD::i256_generic,
			Index_ == 0,
			Index_ == 1,
			Index_ == 2,
			Index_ == 3,
			Index_ == 4,
			Index_ == 5,
			Index_ == 6,
			Index_ == 7,
			Index_ == 8,
			Index_ == 9,
			Index_ == 10,
			Index_ == 11,
			Index_ == 12,
			Index_ == 13,
			Index_ == 14,
			Index_ == 15
		>;

	public:
		[[nodiscard]] static inline EmuSIMD::i256_generic get()
		{
			return _mask_generator::get();
		}
	};

	template<std::size_t Index_>
	struct _single_index_mask<EmuSIMD::i256_generic, Index_, 32>
	{
	private:
		static_assert(EmuSIMD::TMP::valid_register_index_v<EmuSIMD::i256_generic, Index_, 32>, "Invalid index provided when attempting to retrieve a single index mask for a EmuSIMD::i256_generic SIMD register with 32-bit elements.");

		using _mask_generator = _per_index_mask
		<
			EmuSIMD::i256_generic,
			Index_ == 0,
			Index_ == 1,
			Index_ == 2,
			Index_ == 3,
			Index_ == 4,
			Index_ == 5,
			Index_ == 6,
			Index_ == 7
		>;

	public:
		[[nodiscard]] static inline EmuSIMD::i256_generic get()
		{
			return _mask_generator::get();
		}
	};

	template<std::size_t Index_>
	struct _single_index_mask<EmuSIMD::i256_generic, Index_, 64>
	{
	private:
		static_assert(EmuSIMD::TMP::valid_register_index_v<EmuSIMD::i256_generic, Index_, 64>, "Invalid index provided when attempting to retrieve a single index mask for a EmuSIMD::i256_generic SIMD register with 64-bit elements.");

		using _mask_generator = _per_index_mask
		<
			EmuSIMD::i256_generic,
			Index_ == 0,
			Index_ == 1,
			Index_ == 2,
			Index_ == 3
		>;

	public:
		[[nodiscard]] static inline EmuSIMD::i256_generic get()
		{
			return _mask_generator::get();
		}
	};





	template<std::size_t Index_>
	struct _single_index_mask<EmuSIMD::i512_generic, Index_, 8>
	{
	private:
		static_assert(EmuSIMD::TMP::valid_register_index_v<EmuSIMD::i512_generic, Index_, 8>, "Invalid index provided when attempting to retrieve a single index mask for a EmuSIMD::i512_generic SIMD register with 8-bit elements.");

		using _mask_generator = _per_index_mask
		<
			EmuSIMD::i512_generic,
			Index_ == 0,
			Index_ == 1,
			Index_ == 2,
			Index_ == 3,
			Index_ == 4,
			Index_ == 5,
			Index_ == 6,
			Index_ == 7,
			Index_ == 8,
			Index_ == 9,
			Index_ == 10,
			Index_ == 11,
			Index_ == 12,
			Index_ == 13,
			Index_ == 14,
			Index_ == 15,
			Index_ == 16,
			Index_ == 17,
			Index_ == 18,
			Index_ == 19,
			Index_ == 20,
			Index_ == 21,
			Index_ == 22,
			Index_ == 23,
			Index_ == 24,
			Index_ == 25,
			Index_ == 26,
			Index_ == 27,
			Index_ == 28,
			Index_ == 29,
			Index_ == 30,
			Index_ == 31,
			Index_ == 32,
			Index_ == 33,
			Index_ == 34,
			Index_ == 35,
			Index_ == 36,
			Index_ == 37,
			Index_ == 38,
			Index_ == 39,
			Index_ == 40,
			Index_ == 41,
			Index_ == 42,
			Index_ == 43,
			Index_ == 44,
			Index_ == 45,
			Index_ == 46,
			Index_ == 47,
			Index_ == 48,
			Index_ == 49,
			Index_ == 50,
			Index_ == 51,
			Index_ == 52,
			Index_ == 53,
			Index_ == 54,
			Index_ == 55,
			Index_ == 56,
			Index_ == 57,
			Index_ == 58,
			Index_ == 59,
			Index_ == 60,
			Index_ == 61,
			Index_ == 62,
			Index_ == 63
		>;

	public:
		[[nodiscard]] static inline EmuSIMD::i512_generic get()
		{
			return _mask_generator::get();
		}
	};

	template<std::size_t Index_>
	struct _single_index_mask<EmuSIMD::i512_generic, Index_, 16>
	{
	private:
		static_assert(EmuSIMD::TMP::valid_register_index_v<EmuSIMD::i512_generic, Index_, 16>, "Invalid index provided when attempting to retrieve a single index mask for a EmuSIMD::i512_generic SIMD register with 16-bit elements.");

		using _mask_generator = _per_index_mask
		<
			EmuSIMD::i512_generic,
			Index_ == 0,
			Index_ == 1,
			Index_ == 2,
			Index_ == 3,
			Index_ == 4,
			Index_ == 5,
			Index_ == 6,
			Index_ == 7,
			Index_ == 8,
			Index_ == 9,
			Index_ == 10,
			Index_ == 11,
			Index_ == 12,
			Index_ == 13,
			Index_ == 14,
			Index_ == 15,
			Index_ == 16,
			Index_ == 17,
			Index_ == 18,
			Index_ == 19,
			Index_ == 20,
			Index_ == 21,
			Index_ == 22,
			Index_ == 23,
			Index_ == 24,
			Index_ == 25,
			Index_ == 26,
			Index_ == 27,
			Index_ == 28,
			Index_ == 29,
			Index_ == 30,
			Index_ == 31
		>;

	public:
		[[nodiscard]] static inline EmuSIMD::i512_generic get()
		{
			return _mask_generator::get();
		}
	};

	template<std::size_t Index_>
	struct _single_index_mask<EmuSIMD::i512_generic, Index_, 32>
	{
	private:
		static_assert(EmuSIMD::TMP::valid_register_index_v<EmuSIMD::i512_generic, Index_, 32>, "Invalid index provided when attempting to retrieve a single index mask for a EmuSIMD::i512_generic SIMD register with 32-bit elements.");

		using _mask_generator = _per_index_mask
		<
			EmuSIMD::i512_generic,
			Index_ == 0,
			Index_ == 1,
			Index_ == 2,
			Index_ == 3,
			Index_ == 4,
			Index_ == 5,
			Index_ == 6,
			Index_ == 7,
			Index_ == 8,
			Index_ == 9,
			Index_ == 10,
			Index_ == 11,
			Index_ == 12,
			Index_ == 13,
			Index_ == 14,
			Index_ == 15
		>;

	public:
		[[nodiscard]] static inline EmuSIMD::i512_generic get()
		{
			return _mask_generator::get();
		}
	};

	template<std::size_t Index_>
	struct _single_index_mask<EmuSIMD::i512_generic, Index_, 64>
	{
	private:
		static_assert(EmuSIMD::TMP::valid_register_index_v<EmuSIMD::i512_generic, Index_, 64>, "Invalid index provided when attempting to retrieve a single index mask for a EmuSIMD::i512_generic SIMD register with 64-bit elements.");

		using _mask_generator = _per_index_mask
		<
			EmuSIMD::i512_generic,
			Index_ == 0,
			Index_ == 1,
			Index_ == 2,
			Index_ == 3,
			Index_ == 4,
			Index_ == 5,
			Index_ == 6,
			Index_ == 7
		>;

	public:
		[[nodiscard]] static inline EmuSIMD::i512_generic get()
		{
			return _mask_generator::get();
		}
	};
#pragma endregion

#pragma region VARYING_MASK_TEMPLATE
	template<class Register_, bool FirstActive_, std::size_t PerElementWidthIfIntegral_ = 32>
	struct _alternating_index_mask
	{
	};

	template<bool FirstActive_, std::size_t PerElementWidthIfIntegral_>
	struct _alternating_index_mask<EmuSIMD::f32x4, FirstActive_, PerElementWidthIfIntegral_>
	{
	private:
		static constexpr bool even = FirstActive_;
		static constexpr bool odd = !even;
		using _mask_generator = _per_index_mask<EmuSIMD::f32x4, even, odd, even, odd>;

	public:
		[[nodiscard]] static inline EmuSIMD::f32x4 get()
		{
			return _mask_generator::get();
		}
	};

	template<bool FirstActive_, std::size_t PerElementWidthIfIntegral_>
	struct _alternating_index_mask<EmuSIMD::f32x8, FirstActive_, PerElementWidthIfIntegral_>
	{
	private:
		static constexpr bool even = FirstActive_;
		static constexpr bool odd = !even;
		using _mask_generator = _per_index_mask<EmuSIMD::f32x8, even, odd, even, odd, even, odd, even, odd>;

	public:
		[[nodiscard]] static inline EmuSIMD::f32x8 get()
		{
			return _mask_generator::get();
		}
	};

	template<bool FirstActive_, std::size_t PerElementWidthIfIntegral_>
	struct _alternating_index_mask<EmuSIMD::f32x16, FirstActive_, PerElementWidthIfIntegral_>
	{
	private:
		static constexpr bool even = FirstActive_;
		static constexpr bool odd = !even;
		using _mask_generator = _per_index_mask<EmuSIMD::f32x16, even, odd, even, odd, even, odd, even, odd, even, odd, even, odd, even, odd, even, odd>;

	public:
		[[nodiscard]] static inline EmuSIMD::f32x16 get()
		{
			return _mask_generator::get();
		}
	};

	template<bool FirstActive_, std::size_t PerElementWidthIfIntegral_>
	struct _alternating_index_mask<EmuSIMD::f64x2, FirstActive_, PerElementWidthIfIntegral_>
	{
	private:
		static constexpr bool even = FirstActive_;
		static constexpr bool odd = !even;
		using _mask_generator = _per_index_mask<EmuSIMD::f64x2, even, odd>;

	public:
		[[nodiscard]] static inline EmuSIMD::f64x2 get()
		{
			return _mask_generator::get();
		}
	};

	template<bool FirstActive_, std::size_t PerElementWidthIfIntegral_>
	struct _alternating_index_mask<EmuSIMD::f64x4, FirstActive_, PerElementWidthIfIntegral_>
	{
	private:
		static constexpr bool even = FirstActive_;
		static constexpr bool odd = !even;
		using _mask_generator = _per_index_mask<EmuSIMD::f64x4, even, odd, even, odd>;

	public:
		[[nodiscard]] static inline EmuSIMD::f64x4 get()
		{
			return _mask_generator::get();
		}
	};

	template<bool FirstActive_, std::size_t PerElementWidthIfIntegral_>
	struct _alternating_index_mask<EmuSIMD::f64x8, FirstActive_, PerElementWidthIfIntegral_>
	{
	private:
		static constexpr bool even = FirstActive_;
		static constexpr bool odd = !even;
		using _mask_generator = _per_index_mask<EmuSIMD::f64x8, even, odd, even, odd, even, odd, even, odd>;

	public:
		[[nodiscard]] static inline EmuSIMD::f64x8 get()
		{
			return _mask_generator::get();
		}
	};

	template<bool FirstActive_>
	struct _alternating_index_mask<EmuSIMD::i128_generic, FirstActive_, 8>
	{
	private:
		static constexpr bool even = FirstActive_;
		static constexpr bool odd = !even;
		using _mask_generator = _per_index_mask<EmuSIMD::i128_generic, even, odd, even, odd, even, odd, even, odd, even, odd, even, odd, even, odd, even, odd>;

	public:
		[[nodiscard]] static inline EmuSIMD::i128_generic get()
		{
			return _mask_generator::get();
		}
	};
	template<bool FirstActive_>
	struct _alternating_index_mask<EmuSIMD::i128_generic, FirstActive_, 16>
	{
	private:
		static constexpr bool even = FirstActive_;
		static constexpr bool odd = !even;
		using _mask_generator = _per_index_mask<EmuSIMD::i128_generic, even, odd, even, odd, even, odd, even, odd>;

	public:
		[[nodiscard]] static inline EmuSIMD::i128_generic get()
		{
			return _mask_generator::get();
		}
	};
	template<bool FirstActive_>
	struct _alternating_index_mask<EmuSIMD::i128_generic, FirstActive_, 32>
	{
	private:
		static constexpr bool even = FirstActive_;
		static constexpr bool odd = !even;
		using _mask_generator = _per_index_mask<EmuSIMD::i128_generic, even, odd, even, odd>;

	public:
		[[nodiscard]] static inline EmuSIMD::i128_generic get()
		{
			return _mask_generator::get();
		}
	};
	template<bool FirstActive_>
	struct _alternating_index_mask<EmuSIMD::i128_generic, FirstActive_, 64>
	{
	private:
		static constexpr bool even = FirstActive_;
		static constexpr bool odd = !even;
		using _mask_generator = _per_index_mask<EmuSIMD::i128_generic, even, odd>;

	public:
		[[nodiscard]] static inline EmuSIMD::i128_generic get()
		{
			return _mask_generator::get();
		}
	};

	template<bool FirstActive_>
	struct _alternating_index_mask<EmuSIMD::i256_generic, FirstActive_, 8>
	{
	private:
		static constexpr bool even = FirstActive_;
		static constexpr bool odd = !even;
		using _mask_generator = _per_index_mask
		<
			EmuSIMD::i256_generic,
			even, odd, even, odd, even, odd, even, odd, even, odd, even, odd, even, odd, even, odd,
			even, odd, even, odd, even, odd, even, odd, even, odd, even, odd, even, odd, even, odd
		>;

	public:
		[[nodiscard]] static inline EmuSIMD::i256_generic get()
		{
			return _mask_generator::get();
		}
	};
	template<bool FirstActive_>
	struct _alternating_index_mask<EmuSIMD::i256_generic, FirstActive_, 16>
	{
	private:
		static constexpr bool even = FirstActive_;
		static constexpr bool odd = !even;
		using _mask_generator = _per_index_mask<EmuSIMD::i256_generic, even, odd, even, odd, even, odd, even, odd, even, odd, even, odd, even, odd, even, odd>;

	public:
		[[nodiscard]] static inline EmuSIMD::i256_generic get()
		{
			return _mask_generator::get();
		}
	};
	template<bool FirstActive_>
	struct _alternating_index_mask<EmuSIMD::i256_generic, FirstActive_, 32>
	{
	private:
		static constexpr bool even = FirstActive_;
		static constexpr bool odd = !even;
		using _mask_generator = _per_index_mask<EmuSIMD::i256_generic, even, odd, even, odd, even, odd, even, odd>;

	public:
		[[nodiscard]] static inline EmuSIMD::i256_generic get()
		{
			return _mask_generator::get();
		}
	};
	template<bool FirstActive_>
	struct _alternating_index_mask<EmuSIMD::i256_generic, FirstActive_, 64>
	{
	private:
		static constexpr bool even = FirstActive_;
		static constexpr bool odd = !even;
		using _mask_generator = _per_index_mask<EmuSIMD::i256_generic, even, odd, even, odd>;

	public:
		[[nodiscard]] static inline EmuSIMD::i256_generic get()
		{
			return _mask_generator::get();
		}
	};

	template<bool FirstActive_>
	struct _alternating_index_mask<EmuSIMD::i512_generic, FirstActive_, 8>
	{
	private:
		static constexpr bool even = FirstActive_;
		static constexpr bool odd = !even;
		using _mask_generator = _per_index_mask
		<
			EmuSIMD::i512_generic,
			even, odd, even, odd, even, odd, even, odd, even, odd, even, odd, even, odd, even, odd,
			even, odd, even, odd, even, odd, even, odd, even, odd, even, odd, even, odd, even, odd,
			even, odd, even, odd, even, odd, even, odd, even, odd, even, odd, even, odd, even, odd,
			even, odd, even, odd, even, odd, even, odd, even, odd, even, odd, even, odd, even, odd
		>;

	public:
		[[nodiscard]] static inline EmuSIMD::i512_generic get()
		{
			return _mask_generator::get();
		}
	};
	template<bool FirstActive_>
	struct _alternating_index_mask<EmuSIMD::i512_generic, FirstActive_, 16>
	{
	private:
		static constexpr bool even = FirstActive_;
		static constexpr bool odd = !even;
		using _mask_generator = _per_index_mask
		<
			EmuSIMD::i512_generic,
			even, odd, even, odd, even, odd, even, odd, even, odd, even, odd, even, odd, even, odd,
			even, odd, even, odd, even, odd, even, odd, even, odd, even, odd, even, odd, even, odd
		>;

	public:
		[[nodiscard]] static inline EmuSIMD::i512_generic get()
		{
			return _mask_generator::get();
		}
	};
	template<bool FirstActive_>
	struct _alternating_index_mask<EmuSIMD::i512_generic, FirstActive_, 32>
	{
	private:
		static constexpr bool even = FirstActive_;
		static constexpr bool odd = !even;
		using _mask_generator = _per_index_mask<EmuSIMD::i512_generic, even, odd, even, odd, even, odd, even, odd, even, odd, even, odd, even, odd, even, odd>;

	public:
		[[nodiscard]] static inline EmuSIMD::i512_generic get()
		{
			return _mask_generator::get();
		}
	};
	template<bool FirstActive_>
	struct _alternating_index_mask<EmuSIMD::i512_generic, FirstActive_, 64>
	{
	private:
		static constexpr bool even = FirstActive_;
		static constexpr bool odd = !even;
		using _mask_generator = _per_index_mask<EmuSIMD::i512_generic, even, odd, even, odd, even, odd, even, odd>;

	public:
		[[nodiscard]] static inline EmuSIMD::i512_generic get()
		{
			return _mask_generator::get();
		}
	};
#pragma endregion
	
#pragma region VALIDITY_TMP
	template<class PerIndexMaskInstance_>
	struct _is_valid_per_index_mask_instance
	{
		static constexpr bool value = false;
	};
	template<class Register_, bool...ActiveIndices_>
	struct _is_valid_per_index_mask_instance<_per_index_mask<Register_, ActiveIndices_...>>
	{
		static constexpr bool value = EmuCore::TMP::has_static_get<_per_index_mask<Register_, ActiveIndices_...>>::value;
	};

	template<class SingleIndexMaskInstance_>
	struct _is_valid_single_index_mask_instance
	{
		static constexpr bool value = false;
	};
	template<class Register_, std::size_t Index_, std::size_t PerElementWidthIfInt_>
	struct _is_valid_single_index_mask_instance<_single_index_mask<Register_, Index_, PerElementWidthIfInt_>>
	{
		static constexpr bool value = EmuCore::TMP::has_static_get<_single_index_mask<Register_, Index_, PerElementWidthIfInt_>>::value;
	};

	template<class AlternatingIndexMaskInstance_>
	struct _is_valid_alternating_index_mask_instance
	{
		static constexpr bool value = false;
	};
	template<class Register_, bool FirstActive_, std::size_t PerElementWidthIfInt_>
	struct _is_valid_alternating_index_mask_instance<_alternating_index_mask<Register_, FirstActive_, PerElementWidthIfInt_>>
	{
		static constexpr bool value = EmuCore::TMP::has_static_get<_alternating_index_mask<Register_, FirstActive_, PerElementWidthIfInt_>>::value;
	};
#pragma endregion
}


#endif
