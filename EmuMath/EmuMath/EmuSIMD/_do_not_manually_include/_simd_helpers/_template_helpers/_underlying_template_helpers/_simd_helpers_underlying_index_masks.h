#ifndef EMU_SIMD_HELPERS_UNDERLYING_INDEX_MASKS_H_INC_
#define EMU_SIMD_HELPERS_UNDERLYING_INDEX_MASKS_H_INC_ 1

#include "_common_underlying_simd_template_helper_includes.h"
#include "../../../../../EmuCore/TMPHelpers/TypeComparators.h"
#include "../../../../../EmuCore/TMPHelpers/Values.h"
#include "../../../../../EmuCore/TMPHelpers/VariadicHelpers.h"

namespace EmuSIMD::_underlying_simd_helpers
{
	template<typename OutFlags_, bool...IndexArgs_, std::size_t...Indices_>
	[[nodiscard]] static constexpr inline auto _construct_index_mask_flags(EmuCore::TMP::bool_sequence<IndexArgs_...> index_args_, std::index_sequence<Indices_...> indices_)
	{
		return static_cast<OutFlags_>((... | (static_cast<OutFlags_>(IndexArgs_) << Indices_)));
	}

	/// <summary>
	/// <para> Type for creating a per-index mask, where true indices will be set to active (all bits 1) and false indices will be inactive (all bits 0). </para>
	/// <para> The size of elements in integral registers will adapt to the provided amount of index arguments. </para>
	/// </summary>
	template<class Register_, bool...ActiveIndices_>
	struct _per_index_mask
	{
	};

#pragma region PER_INDEX_MASK_GENERATORS
	template<bool I0_, bool I1_, bool I2_, bool I3_>
	struct _per_index_mask<EmuSIMD::f32x4, I0_, I1_, I2_, I3_>
	{
		[[nodiscard]] static inline EmuSIMD::f32x4 get()
		{
			return EmuSIMD::Funcs::set_index_mask_f32x4<I0_, I1_, I2_, I3_>();
		}
	};
	template<bool AllIndices_>
	struct _per_index_mask<EmuSIMD::f32x4, AllIndices_>
	{
		[[nodiscard]] static inline EmuSIMD::f32x4 get()
		{
			return EmuSIMD::Funcs::set_index_mask_f32x4<AllIndices_>();
		}
	};

	template<bool I0_, bool I1_, bool I2_, bool I3_, bool I4_, bool I5_, bool I6_, bool I7_>
	struct _per_index_mask<EmuSIMD::f32x8, I0_, I1_, I2_, I3_, I4_, I5_, I6_, I7_>
	{
		[[nodiscard]] static inline EmuSIMD::f32x8 get()
		{
			return EmuSIMD::Funcs::set_index_mask_f32x8<I0_, I1_, I2_, I3_, I4_, I5_, I6_, I7_>();
		}
	};
	template<bool AllIndices_>
	struct _per_index_mask<EmuSIMD::f32x8, AllIndices_>
	{
		[[nodiscard]] static inline EmuSIMD::f32x8 get()
		{
			return EmuSIMD::Funcs::set_index_mask_f32x8<AllIndices_>();
		}
	};

	template<bool I0_, bool I1_, bool I2_, bool I3_, bool I4_, bool I5_, bool I6_, bool I7_, bool I8_, bool I9_, bool I10_, bool I11_, bool I12_, bool I13_, bool I14_, bool I15_>
	struct _per_index_mask<EmuSIMD::f32x16, I0_, I1_, I2_, I3_, I4_, I5_, I6_, I7_, I8_, I9_, I10_, I11_, I12_, I13_, I14_, I15_>
	{
		[[nodiscard]] static inline EmuSIMD::f32x16 get()
		{
			return EmuSIMD::Funcs::set_index_mask_f32x16<I0_, I1_, I2_, I3_, I4_, I5_, I6_, I7_, I8_, I9_, I10_, I11_, I12_, I13_, I14_, I15_>();
		}
	};
	template<bool AllIndices_>
	struct _per_index_mask<EmuSIMD::f32x16, AllIndices_>
	{
		[[nodiscard]] static inline EmuSIMD::f32x16 get()
		{
			return EmuSIMD::Funcs::set_index_mask_f32x16<AllIndices_>();
		}
	};

	template<bool I0_, bool I1_>
	struct _per_index_mask<EmuSIMD::f64x2, I0_, I1_>
	{
		[[nodiscard]] static inline EmuSIMD::f64x2 get()
		{
			return EmuSIMD::Funcs::set_index_mask_f64x2<I0_, I1_>();
		}
	};
	template<bool AllIndices_>
	struct _per_index_mask<EmuSIMD::f64x2, AllIndices_>
	{
		[[nodiscard]] static inline EmuSIMD::f64x2 get()
		{
			return EmuSIMD::Funcs::set_index_mask_f64x2<AllIndices_>();
		}
	};

	template<bool I0_, bool I1_, bool I2_, bool I3_>
	struct _per_index_mask<EmuSIMD::f64x4, I0_, I1_, I2_, I3_>
	{
		[[nodiscard]] static inline EmuSIMD::f64x4 get()
		{
			return EmuSIMD::Funcs::set_index_mask_f64x4<I0_, I1_, I2_, I3_>();
		}
	};
	template<bool AllIndices_>
	struct _per_index_mask<EmuSIMD::f64x4, AllIndices_>
	{
		[[nodiscard]] static inline EmuSIMD::f64x4 get()
		{
			return EmuSIMD::Funcs::set_index_mask_f64x4<AllIndices_>();
		}
	};

	template<bool I0_, bool I1_, bool I2_, bool I3_, bool I4_, bool I5_, bool I6_, bool I7_>
	struct _per_index_mask<EmuSIMD::f64x8, I0_, I1_, I2_, I3_, I4_, I5_, I6_, I7_>
	{
		[[nodiscard]] static inline EmuSIMD::f64x8 get()
		{
			return EmuSIMD::Funcs::set_index_mask_f64x8<I0_, I1_, I2_, I3_, I4_, I5_, I6_, I7_>();
		}
	};
	template<bool AllIndices_>
	struct _per_index_mask<EmuSIMD::f64x8, AllIndices_>
	{
		[[nodiscard]] static inline EmuSIMD::f64x8 get()
		{
			return EmuSIMD::Funcs::set_index_mask_f64x8<AllIndices_>();
		}
	};

#if EMU_SIMD_USE_GENERIC_INT_REGISTERS
	template<bool I0_, bool I1_, bool I2_, bool I3_, bool I4_, bool I5_, bool I6_, bool I7_, bool I8_, bool I9_, bool I10_, bool I11_, bool I12_, bool I13_, bool I14_, bool I15_>
	struct _per_index_mask<EmuSIMD::i128_generic, I0_, I1_, I2_, I3_, I4_, I5_, I6_, I7_, I8_, I9_, I10_, I11_, I12_, I13_, I14_, I15_>
	{
		[[nodiscard]] static inline EmuSIMD::i8x16 get()
		{
			return EmuSIMD::Funcs::set_index_mask_i8x16<I0_, I1_, I2_, I3_, I4_, I5_, I6_, I7_, I8_, I9_, I10_, I11_, I12_, I13_, I14_, I15_>();
		}
	};
	template<bool I0_, bool I1_, bool I2_, bool I3_, bool I4_, bool I5_, bool I6_, bool I7_>
	struct _per_index_mask<EmuSIMD::i128_generic, I0_, I1_, I2_, I3_, I4_, I5_, I6_, I7_>
	{
		[[nodiscard]] static inline EmuSIMD::i16x8 get()
		{
			return EmuSIMD::Funcs::set_index_mask_i16x8<I0_, I1_, I2_, I3_, I4_, I5_, I6_, I7_>();
		}
	};
	template<bool I0_, bool I1_, bool I2_, bool I3_>
	struct _per_index_mask<EmuSIMD::i128_generic, I0_, I1_, I2_, I3_>
	{
		[[nodiscard]] static inline EmuSIMD::i32x4 get()
		{
			return EmuSIMD::Funcs::set_index_mask_i32x4<I0_, I1_, I2_, I3_>();
		}
	};
	template<bool I0_, bool I1_>
	struct _per_index_mask<EmuSIMD::i128_generic, I0_, I1_>
	{
		[[nodiscard]] static inline EmuSIMD::i64x2 get()
		{
			return EmuSIMD::Funcs::set_index_mask_i64x2<I0_, I1_>();
		}
	};
	template<bool AllIndices_>
	struct _per_index_mask<EmuSIMD::i128_generic, AllIndices_>
	{
		[[nodiscard]] static inline EmuSIMD::i128_generic get()
		{
			return EmuSIMD::Funcs::set_index_mask_i64x2<AllIndices_>();
		}
	};
	
	template
	<
		bool I0_,  bool I1_,  bool I2_,  bool I3_,  bool I4_,  bool I5_,  bool I6_,  bool I7_,  bool I8_,  bool I9_,  bool I10_, bool I11_, bool I12_, bool I13_, bool I14_, bool I15_,
		bool I16_, bool I17_, bool I18_, bool I19_, bool I20_, bool I21_, bool I22_, bool I23_, bool I24_, bool I25_, bool I26_, bool I27_, bool I28_, bool I29_, bool I30_, bool I31_
	>
	struct _per_index_mask
	<
		EmuSIMD::i256_generic,
		I0_,  I1_,  I2_,  I3_,  I4_,  I5_,  I6_,  I7_,  I8_,  I9_,  I10_, I11_, I12_, I13_, I14_, I15_,
		I16_, I17_, I18_, I19_, I20_, I21_, I22_, I23_, I24_, I25_, I26_, I27_, I28_, I29_, I30_, I31_
	>
	{
		[[nodiscard]] static inline EmuSIMD::i8x32 get()
		{
			return EmuSIMD::Funcs::set_index_mask_i8x32
			<
				I0_,  I1_,  I2_,  I3_,  I4_,  I5_,  I6_,  I7_,  I8_,  I9_,  I10_, I11_, I12_, I13_, I14_, I15_,
				I16_, I17_, I18_, I19_, I20_, I21_, I22_, I23_, I24_, I25_, I26_, I27_, I28_, I29_, I30_, I31_
			>();
		}
	};
	template<bool I0_, bool I1_, bool I2_, bool I3_, bool I4_, bool I5_, bool I6_, bool I7_, bool I8_, bool I9_, bool I10_, bool I11_, bool I12_, bool I13_, bool I14_, bool I15_>
	struct _per_index_mask<EmuSIMD::i256_generic, I0_, I1_, I2_, I3_, I4_, I5_, I6_, I7_, I8_, I9_, I10_, I11_, I12_, I13_, I14_, I15_>
	{
		[[nodiscard]] static inline EmuSIMD::i16x16 get()
		{
			return EmuSIMD::Funcs::set_index_mask_i16x16<I0_, I1_, I2_, I3_, I4_, I5_, I6_, I7_, I8_, I9_, I10_, I11_, I12_, I13_, I14_, I15_>();
		}
	};
	template<bool I0_, bool I1_, bool I2_, bool I3_, bool I4_, bool I5_, bool I6_, bool I7_>
	struct _per_index_mask<EmuSIMD::i256_generic, I0_, I1_, I2_, I3_, I4_, I5_, I6_, I7_>
	{
		[[nodiscard]] static inline EmuSIMD::i32x8 get()
		{
			return EmuSIMD::Funcs::set_index_mask_i32x8<I0_, I1_, I2_, I3_, I4_, I5_, I6_, I7_>();
		}
	};
	template<bool I0_, bool I1_, bool I2_, bool I3_>
	struct _per_index_mask<EmuSIMD::i256_generic, I0_, I1_, I2_, I3_>
	{
		[[nodiscard]] static inline EmuSIMD::i64x4 get()
		{
			return EmuSIMD::Funcs::set_index_mask_i64x4<I0_, I1_, I2_, I3_>();
		}
	};
	template<bool AllIndices_>
	struct _per_index_mask<EmuSIMD::i256_generic, AllIndices_>
	{
		[[nodiscard]] static inline EmuSIMD::i256_generic get()
		{
			return EmuSIMD::Funcs::set_index_mask_i64x4<AllIndices_>();
		}
	};

	template
	<
		bool I0_,  bool I1_,  bool I2_,  bool I3_,  bool I4_,  bool I5_,  bool I6_,  bool I7_,  bool I8_,  bool I9_,  bool I10_, bool I11_, bool I12_, bool I13_, bool I14_, bool I15_,
		bool I16_, bool I17_, bool I18_, bool I19_, bool I20_, bool I21_, bool I22_, bool I23_, bool I24_, bool I25_, bool I26_, bool I27_, bool I28_, bool I29_, bool I30_, bool I31_,
		bool I32_, bool I33_, bool I34_, bool I35_, bool I36_, bool I37_, bool I38_, bool I39_, bool I40_, bool I41_, bool I42_, bool I43_, bool I44_, bool I45_, bool I46_, bool I47_,
		bool I48_, bool I49_, bool I50_, bool I51_, bool I52_, bool I53_, bool I54_, bool I55_, bool I56_, bool I57_, bool I58_, bool I59_, bool I60_, bool I61_, bool I62_, bool I63_
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
		[[nodiscard]] static inline EmuSIMD::i8x64 get()
		{
			return EmuSIMD::Funcs::set_index_mask_i8x64
			<
				I0_,  I1_,  I2_,  I3_,  I4_,  I5_,  I6_,  I7_,  I8_,  I9_,  I10_, I11_, I12_, I13_, I14_, I15_,
				I16_, I17_, I18_, I19_, I20_, I21_, I22_, I23_, I24_, I25_, I26_, I27_, I28_, I29_, I30_, I31_,
				I32_, I33_, I34_, I35_, I36_, I37_, I38_, I39_, I40_, I41_, I42_, I43_, I44_, I45_, I46_, I47_,
				I48_, I49_, I50_, I51_, I52_, I53_, I54_, I55_, I56_, I57_, I58_, I59_, I60_, I61_, I62_, I63_
			>();
		}
	};
	template
	<
		bool I0_,  bool I1_,  bool I2_,  bool I3_,  bool I4_,  bool I5_,  bool I6_,  bool I7_,  bool I8_,  bool I9_,  bool I10_, bool I11_, bool I12_, bool I13_, bool I14_, bool I15_,
		bool I16_, bool I17_, bool I18_, bool I19_, bool I20_, bool I21_, bool I22_, bool I23_, bool I24_, bool I25_, bool I26_, bool I27_, bool I28_, bool I29_, bool I30_, bool I31_
	>
	struct _per_index_mask
	<
		EmuSIMD::i512_generic,
		I0_,  I1_,  I2_,  I3_,  I4_,  I5_,  I6_,  I7_,  I8_,  I9_,  I10_, I11_, I12_, I13_, I14_, I15_,
		I16_, I17_, I18_, I19_, I20_, I21_, I22_, I23_, I24_, I25_, I26_, I27_, I28_, I29_, I30_, I31_
	>
	{
		[[nodiscard]] static inline EmuSIMD::i16x32 get()
		{
			return EmuSIMD::Funcs::set_index_mask_i16x32
			<
				I0_,  I1_,  I2_,  I3_,  I4_,  I5_,  I6_,  I7_,  I8_,  I9_,  I10_, I11_, I12_, I13_, I14_, I15_,
				I16_, I17_, I18_, I19_, I20_, I21_, I22_, I23_, I24_, I25_, I26_, I27_, I28_, I29_, I30_, I31_
			>();
		}
	};
	template<bool I0_, bool I1_, bool I2_, bool I3_, bool I4_, bool I5_, bool I6_, bool I7_, bool I8_, bool I9_, bool I10_, bool I11_, bool I12_, bool I13_, bool I14_, bool I15_>
	struct _per_index_mask<EmuSIMD::i512_generic, I0_, I1_, I2_, I3_, I4_, I5_, I6_, I7_, I8_, I9_, I10_, I11_, I12_, I13_, I14_, I15_>
	{
		[[nodiscard]] static inline EmuSIMD::i32x16 get()
		{
			return EmuSIMD::Funcs::set_index_mask_i32x16<I0_, I1_, I2_, I3_, I4_, I5_, I6_, I7_, I8_, I9_, I10_, I11_, I12_, I13_, I14_, I15_>();
		}
	};
	template<bool I0_, bool I1_, bool I2_, bool I3_, bool I4_, bool I5_, bool I6_, bool I7_>
	struct _per_index_mask<EmuSIMD::i512_generic, I0_, I1_, I2_, I3_, I4_, I5_, I6_, I7_>
	{
		[[nodiscard]] static inline EmuSIMD::i64x8 get()
		{
			return EmuSIMD::Funcs::set_index_mask_i64x8<I0_, I1_, I2_, I3_, I4_, I5_, I6_, I7_>();
		}
	};
	template<bool AllIndices_>
	struct _per_index_mask<EmuSIMD::i512_generic, AllIndices_>
	{
		[[nodiscard]] static inline EmuSIMD::i512_generic get()
		{
			return EmuSIMD::Funcs::set_index_mask_i64x8<AllIndices_>();
		}
	};
#else
	template<bool I0_, bool I1_, bool I2_, bool I3_, bool I4_, bool I5_, bool I6_, bool I7_, bool I8_, bool I9_, bool I10_, bool I11_, bool I12_, bool I13_, bool I14_, bool I15_>
	struct _per_index_mask<EmuSIMD::i8x16, I0_, I1_, I2_, I3_, I4_, I5_, I6_, I7_, I8_, I9_, I10_, I11_, I12_, I13_, I14_, I15_>
	{
		[[nodiscard]] static inline EmuSIMD::i8x16 get()
		{
			return EmuSIMD::Funcs::set_index_mask_i8x16<I0_, I1_, I2_, I3_, I4_, I5_, I6_, I7_, I8_, I9_, I10_, I11_, I12_, I13_, I14_, I15_>();
		}
	};
	template<bool AllIndices_>
	struct _per_index_mask<EmuSIMD::i8x16, AllIndices_>
	{
		[[nodiscard]] static inline EmuSIMD::i8x16 get()
		{
			return EmuSIMD::Funcs::set_index_mask_i8x16<AllIndices_>();
		}
	};

	template<bool I0_, bool I1_, bool I2_, bool I3_, bool I4_, bool I5_, bool I6_, bool I7_>
	struct _per_index_mask<EmuSIMD::i16x8, I0_, I1_, I2_, I3_, I4_, I5_, I6_, I7_>
	{
		[[nodiscard]] static inline EmuSIMD::i16x8 get()
		{
			return EmuSIMD::Funcs::set_index_mask_i16x8<I0_, I1_, I2_, I3_, I4_, I5_, I6_, I7_>();
		}
	};
	template<bool AllIndices_>
	struct _per_index_mask<EmuSIMD::i16x8, AllIndices_>
	{
		[[nodiscard]] static inline EmuSIMD::i16x8 get()
		{
			return EmuSIMD::Funcs::set_index_mask_i16x8<AllIndices_>();
		}
	};

	template<bool I0_, bool I1_, bool I2_, bool I3_>
	struct _per_index_mask<EmuSIMD::i32x4, I0_, I1_, I2_, I3_>
	{
		[[nodiscard]] static inline EmuSIMD::i32x4 get()
		{
			return EmuSIMD::Funcs::set_index_mask_i32x4<I0_, I1_, I2_, I3_>();
		}
	};
	template<bool AllIndices_>
	struct _per_index_mask<EmuSIMD::i32x4, AllIndices_>
	{
		[[nodiscard]] static inline EmuSIMD::i32x4 get()
		{
			return EmuSIMD::Funcs::set_index_mask_i32x4<AllIndices_>();
		}
	};

	template<bool I0_, bool I1_>
	struct _per_index_mask<EmuSIMD::i64x2, I0_, I1_>
	{
		[[nodiscard]] static inline EmuSIMD::i64x2 get()
		{
			return EmuSIMD::Funcs::set_index_mask_i64x2<I0_, I1_>();
		}
	};
	template<bool AllIndices_>
	struct _per_index_mask<EmuSIMD::i64x2, AllIndices_>
	{
		[[nodiscard]] static inline EmuSIMD::i64x2 get()
		{
			return EmuSIMD::Funcs::set_index_mask_i64x2<AllIndices_>();
		}
	};
	
	template
	<
		bool I0_,  bool I1_,  bool I2_,  bool I3_,  bool I4_,  bool I5_,  bool I6_,  bool I7_,  bool I8_,  bool I9_,  bool I10_, bool I11_, bool I12_, bool I13_, bool I14_, bool I15_,
		bool I16_, bool I17_, bool I18_, bool I19_, bool I20_, bool I21_, bool I22_, bool I23_, bool I24_, bool I25_, bool I26_, bool I27_, bool I28_, bool I29_, bool I30_, bool I31_
	>
	struct _per_index_mask
	<
		EmuSIMD::i8x32,
		I0_,  I1_,  I2_,  I3_,  I4_,  I5_,  I6_,  I7_,  I8_,  I9_,  I10_, I11_, I12_, I13_, I14_, I15_,
		I16_, I17_, I18_, I19_, I20_, I21_, I22_, I23_, I24_, I25_, I26_, I27_, I28_, I29_, I30_, I31_
	>
	{
		[[nodiscard]] static inline EmuSIMD::i8x32 get()
		{
			return EmuSIMD::Funcs::set_index_mask_i8x32
			<
				I0_,  I1_,  I2_,  I3_,  I4_,  I5_,  I6_,  I7_,  I8_,  I9_,  I10_, I11_, I12_, I13_, I14_, I15_,
				I16_, I17_, I18_, I19_, I20_, I21_, I22_, I23_, I24_, I25_, I26_, I27_, I28_, I29_, I30_, I31_
			>();
		}
	};
	template<bool AllIndices_>
	struct _per_index_mask<EmuSIMD::i8x32, AllIndices_>
	{
		[[nodiscard]] static inline EmuSIMD::i8x32 get()
		{
			return EmuSIMD::Funcs::set_index_mask_i8x32<AllIndices_>();
		}
	};

	template<bool I0_, bool I1_, bool I2_, bool I3_, bool I4_, bool I5_, bool I6_, bool I7_, bool I8_, bool I9_, bool I10_, bool I11_, bool I12_, bool I13_, bool I14_, bool I15_>
	struct _per_index_mask<EmuSIMD::i16x16, I0_, I1_, I2_, I3_, I4_, I5_, I6_, I7_, I8_, I9_, I10_, I11_, I12_, I13_, I14_, I15_>
	{
		[[nodiscard]] static inline EmuSIMD::i16x16 get()
		{
			return EmuSIMD::Funcs::set_index_mask_i16x16<I0_, I1_, I2_, I3_, I4_, I5_, I6_, I7_, I8_, I9_, I10_, I11_, I12_, I13_, I14_, I15_>();
		}
	};
	template<bool AllIndices_>
	struct _per_index_mask<EmuSIMD::i16x16, AllIndices_>
	{
		[[nodiscard]] static inline EmuSIMD::i16x16 get()
		{
			return EmuSIMD::Funcs::set_index_mask_i16x16<AllIndices_>();
		}
	};

	template<bool I0_, bool I1_, bool I2_, bool I3_, bool I4_, bool I5_, bool I6_, bool I7_>
	struct _per_index_mask<EmuSIMD::i32x8, I0_, I1_, I2_, I3_, I4_, I5_, I6_, I7_>
	{
		[[nodiscard]] static inline EmuSIMD::i32x8 get()
		{
			return EmuSIMD::Funcs::set_index_mask_i32x8<I0_, I1_, I2_, I3_, I4_, I5_, I6_, I7_>();
		}
	};
	template<bool AllIndices_>
	struct _per_index_mask<EmuSIMD::i32x8, AllIndices_>
	{
		[[nodiscard]] static inline EmuSIMD::i32x8 get()
		{
			return EmuSIMD::Funcs::set_index_mask_i32x8<AllIndices_>();
		}
	};

	template<bool I0_, bool I1_, bool I2_, bool I3_>
	struct _per_index_mask<EmuSIMD::i64x4, I0_, I1_, I2_, I3_>
	{
		[[nodiscard]] static inline EmuSIMD::i64x4 get()
		{
			return EmuSIMD::Funcs::set_index_mask_i64x4<I0_, I1_, I2_, I3_>();
		}
	};
	template<bool AllIndices_>
	struct _per_index_mask<EmuSIMD::i64x4, AllIndices_>
	{
		[[nodiscard]] static inline EmuSIMD::i64x4 get()
		{
			return EmuSIMD::Funcs::set_index_mask_i64x4<AllIndices_>();
		}
	};

	template
	<
		bool I0_,  bool I1_,  bool I2_,  bool I3_,  bool I4_,  bool I5_,  bool I6_,  bool I7_,  bool I8_,  bool I9_,  bool I10_, bool I11_, bool I12_, bool I13_, bool I14_, bool I15_,
		bool I16_, bool I17_, bool I18_, bool I19_, bool I20_, bool I21_, bool I22_, bool I23_, bool I24_, bool I25_, bool I26_, bool I27_, bool I28_, bool I29_, bool I30_, bool I31_,
		bool I32_, bool I33_, bool I34_, bool I35_, bool I36_, bool I37_, bool I38_, bool I39_, bool I40_, bool I41_, bool I42_, bool I43_, bool I44_, bool I45_, bool I46_, bool I47_,
		bool I48_, bool I49_, bool I50_, bool I51_, bool I52_, bool I53_, bool I54_, bool I55_, bool I56_, bool I57_, bool I58_, bool I59_, bool I60_, bool I61_, bool I62_, bool I63_
	>
	struct _per_index_mask
	<
		EmuSIMD::i8x64,
		I0_,  I1_,  I2_,  I3_,  I4_,  I5_,  I6_,  I7_,  I8_,  I9_,  I10_, I11_, I12_, I13_, I14_, I15_,
		I16_, I17_, I18_, I19_, I20_, I21_, I22_, I23_, I24_, I25_, I26_, I27_, I28_, I29_, I30_, I31_,
		I32_, I33_, I34_, I35_, I36_, I37_, I38_, I39_, I40_, I41_, I42_, I43_, I44_, I45_, I46_, I47_,
		I48_, I49_, I50_, I51_, I52_, I53_, I54_, I55_, I56_, I57_, I58_, I59_, I60_, I61_, I62_, I63_
	>
	{
		[[nodiscard]] static inline EmuSIMD::i8x64 get()
		{
			return EmuSIMD::Funcs::set_index_mask_i8x64
			<
				I0_,  I1_,  I2_,  I3_,  I4_,  I5_,  I6_,  I7_,  I8_,  I9_,  I10_, I11_, I12_, I13_, I14_, I15_,
				I16_, I17_, I18_, I19_, I20_, I21_, I22_, I23_, I24_, I25_, I26_, I27_, I28_, I29_, I30_, I31_,
				I32_, I33_, I34_, I35_, I36_, I37_, I38_, I39_, I40_, I41_, I42_, I43_, I44_, I45_, I46_, I47_,
				I48_, I49_, I50_, I51_, I52_, I53_, I54_, I55_, I56_, I57_, I58_, I59_, I60_, I61_, I62_, I63_
			>();
		}
	};
	template<bool AllIndices_>
	struct _per_index_mask<EmuSIMD::i8x64, AllIndices_>
	{
		[[nodiscard]] static inline EmuSIMD::i8x64 get()
		{
			return EmuSIMD::Funcs::set_index_mask_i8x64<AllIndices_>();
		}
	};

	template
	<
		bool I0_,  bool I1_,  bool I2_,  bool I3_,  bool I4_,  bool I5_,  bool I6_,  bool I7_,  bool I8_,  bool I9_,  bool I10_, bool I11_, bool I12_, bool I13_, bool I14_, bool I15_,
		bool I16_, bool I17_, bool I18_, bool I19_, bool I20_, bool I21_, bool I22_, bool I23_, bool I24_, bool I25_, bool I26_, bool I27_, bool I28_, bool I29_, bool I30_, bool I31_
	>
	struct _per_index_mask
	<
		EmuSIMD::i16x32,
		I0_,  I1_,  I2_,  I3_,  I4_,  I5_,  I6_,  I7_,  I8_,  I9_,  I10_, I11_, I12_, I13_, I14_, I15_,
		I16_, I17_, I18_, I19_, I20_, I21_, I22_, I23_, I24_, I25_, I26_, I27_, I28_, I29_, I30_, I31_
	>
	{
		[[nodiscard]] static inline EmuSIMD::i16x32 get()
		{
			return EmuSIMD::Funcs::set_index_mask_i16x32
			<
				I0_,  I1_,  I2_,  I3_,  I4_,  I5_,  I6_,  I7_,  I8_,  I9_,  I10_, I11_, I12_, I13_, I14_, I15_,
				I16_, I17_, I18_, I19_, I20_, I21_, I22_, I23_, I24_, I25_, I26_, I27_, I28_, I29_, I30_, I31_
			>();
		}
	};
	template<bool AllIndices_>
	struct _per_index_mask<EmuSIMD::i16x32, AllIndices_>
	{
		[[nodiscard]] static inline EmuSIMD::i16x32 get()
		{
			return EmuSIMD::Funcs::set_index_mask_i16x32<AllIndices_>();
		}
	};

	template<bool I0_, bool I1_, bool I2_, bool I3_, bool I4_, bool I5_, bool I6_, bool I7_, bool I8_, bool I9_, bool I10_, bool I11_, bool I12_, bool I13_, bool I14_, bool I15_>
	struct _per_index_mask<EmuSIMD::i32x16, I0_, I1_, I2_, I3_, I4_, I5_, I6_, I7_, I8_, I9_, I10_, I11_, I12_, I13_, I14_, I15_>
	{
		[[nodiscard]] static inline EmuSIMD::i32x16 get()
		{
			return EmuSIMD::Funcs::set_index_mask_i32x16<I0_, I1_, I2_, I3_, I4_, I5_, I6_, I7_, I8_, I9_, I10_, I11_, I12_, I13_, I14_, I15_>();
		}
	};
	template<bool AllIndices_>
	struct _per_index_mask<EmuSIMD::i32x16, AllIndices_>
	{
		[[nodiscard]] static inline EmuSIMD::i32x16 get()
		{
			return EmuSIMD::Funcs::set_index_mask_i32x16<AllIndices_>();
		}
	};

	template<bool I0_, bool I1_, bool I2_, bool I3_, bool I4_, bool I5_, bool I6_, bool I7_>
	struct _per_index_mask<EmuSIMD::i64x8, I0_, I1_, I2_, I3_, I4_, I5_, I6_, I7_>
	{
		[[nodiscard]] static inline EmuSIMD::i64x8 get()
		{
			return EmuSIMD::Funcs::set_index_mask_i64x8<I0_, I1_, I2_, I3_, I4_, I5_, I6_, I7_>();
		}
	};
	template<bool AllIndices_>
	struct _per_index_mask<EmuSIMD::i64x8, AllIndices_>
	{
		[[nodiscard]] static inline EmuSIMD::i64x8 get()
		{
			return EmuSIMD::Funcs::set_index_mask_i64x8<AllIndices_>();
		}
	};

	template<bool I0_, bool I1_, bool I2_, bool I3_, bool I4_, bool I5_, bool I6_, bool I7_, bool I8_, bool I9_, bool I10_, bool I11_, bool I12_, bool I13_, bool I14_, bool I15_>
	struct _per_index_mask<EmuSIMD::u8x16, I0_, I1_, I2_, I3_, I4_, I5_, I6_, I7_, I8_, I9_, I10_, I11_, I12_, I13_, I14_, I15_>
	{
		[[nodiscard]] static inline EmuSIMD::u8x16 get()
		{
			return EmuSIMD::Funcs::set_index_mask_u8x16<I0_, I1_, I2_, I3_, I4_, I5_, I6_, I7_, I8_, I9_, I10_, I11_, I12_, I13_, I14_, I15_>();
		}
	};
	template<bool AllIndices_>
	struct _per_index_mask<EmuSIMD::u8x16, AllIndices_>
	{
		[[nodiscard]] static inline EmuSIMD::u8x16 get()
		{
			return EmuSIMD::Funcs::set_index_mask_u8x16<AllIndices_>();
		}
	};

	template<bool I0_, bool I1_, bool I2_, bool I3_, bool I4_, bool I5_, bool I6_, bool I7_>
	struct _per_index_mask<EmuSIMD::u16x8, I0_, I1_, I2_, I3_, I4_, I5_, I6_, I7_>
	{
		[[nodiscard]] static inline EmuSIMD::u16x8 get()
		{
			return EmuSIMD::Funcs::set_index_mask_u16x8<I0_, I1_, I2_, I3_, I4_, I5_, I6_, I7_>();
		}
	};
	template<bool AllIndices_>
	struct _per_index_mask<EmuSIMD::u16x8, AllIndices_>
	{
		[[nodiscard]] static inline EmuSIMD::u16x8 get()
		{
			return EmuSIMD::Funcs::set_index_mask_u16x8<AllIndices_>();
		}
	};

	template<bool I0_, bool I1_, bool I2_, bool I3_>
	struct _per_index_mask<EmuSIMD::u32x4, I0_, I1_, I2_, I3_>
	{
		[[nodiscard]] static inline EmuSIMD::u32x4 get()
		{
			return EmuSIMD::Funcs::set_index_mask_u32x4<I0_, I1_, I2_, I3_>();
		}
	};
	template<bool AllIndices_>
	struct _per_index_mask<EmuSIMD::u32x4, AllIndices_>
	{
		[[nodiscard]] static inline EmuSIMD::u32x4 get()
		{
			return EmuSIMD::Funcs::set_index_mask_u32x4<AllIndices_>();
		}
	};

	template<bool I0_, bool I1_>
	struct _per_index_mask<EmuSIMD::u64x2, I0_, I1_>
	{
		[[nodiscard]] static inline EmuSIMD::u64x2 get()
		{
			return EmuSIMD::Funcs::set_index_mask_u64x2<I0_, I1_>();
		}
	};
	template<bool AllIndices_>
	struct _per_index_mask<EmuSIMD::u64x2, AllIndices_>
	{
		[[nodiscard]] static inline EmuSIMD::u64x2 get()
		{
			return EmuSIMD::Funcs::set_index_mask_u64x2<AllIndices_>();
		}
	};
	
	template
	<
		bool I0_,  bool I1_,  bool I2_,  bool I3_,  bool I4_,  bool I5_,  bool I6_,  bool I7_,  bool I8_,  bool I9_,  bool I10_, bool I11_, bool I12_, bool I13_, bool I14_, bool I15_,
		bool I16_, bool I17_, bool I18_, bool I19_, bool I20_, bool I21_, bool I22_, bool I23_, bool I24_, bool I25_, bool I26_, bool I27_, bool I28_, bool I29_, bool I30_, bool I31_
	>
	struct _per_index_mask
	<
		EmuSIMD::u8x32,
		I0_,  I1_,  I2_,  I3_,  I4_,  I5_,  I6_,  I7_,  I8_,  I9_,  I10_, I11_, I12_, I13_, I14_, I15_,
		I16_, I17_, I18_, I19_, I20_, I21_, I22_, I23_, I24_, I25_, I26_, I27_, I28_, I29_, I30_, I31_
	>
	{
		[[nodiscard]] static inline EmuSIMD::u8x32 get()
		{
			return EmuSIMD::Funcs::set_index_mask_u8x32
			<
				I0_,  I1_,  I2_,  I3_,  I4_,  I5_,  I6_,  I7_,  I8_,  I9_,  I10_, I11_, I12_, I13_, I14_, I15_,
				I16_, I17_, I18_, I19_, I20_, I21_, I22_, I23_, I24_, I25_, I26_, I27_, I28_, I29_, I30_, I31_
			>();
		}
	};
	template<bool AllIndices_>
	struct _per_index_mask<EmuSIMD::u8x32, AllIndices_>
	{
		[[nodiscard]] static inline EmuSIMD::u8x32 get()
		{
			return EmuSIMD::Funcs::set_index_mask_u8x32<AllIndices_>();
		}
	};

	template<bool I0_, bool I1_, bool I2_, bool I3_, bool I4_, bool I5_, bool I6_, bool I7_, bool I8_, bool I9_, bool I10_, bool I11_, bool I12_, bool I13_, bool I14_, bool I15_>
	struct _per_index_mask<EmuSIMD::u16x16, I0_, I1_, I2_, I3_, I4_, I5_, I6_, I7_, I8_, I9_, I10_, I11_, I12_, I13_, I14_, I15_>
	{
		[[nodiscard]] static inline EmuSIMD::u16x16 get()
		{
			return EmuSIMD::Funcs::set_index_mask_u16x16<I0_, I1_, I2_, I3_, I4_, I5_, I6_, I7_, I8_, I9_, I10_, I11_, I12_, I13_, I14_, I15_>();
		}
	};
	template<bool AllIndices_>
	struct _per_index_mask<EmuSIMD::u16x16, AllIndices_>
	{
		[[nodiscard]] static inline EmuSIMD::u16x16 get()
		{
			return EmuSIMD::Funcs::set_index_mask_u16x16<AllIndices_>();
		}
	};

	template<bool I0_, bool I1_, bool I2_, bool I3_, bool I4_, bool I5_, bool I6_, bool I7_>
	struct _per_index_mask<EmuSIMD::u32x8, I0_, I1_, I2_, I3_, I4_, I5_, I6_, I7_>
	{
		[[nodiscard]] static inline EmuSIMD::u32x8 get()
		{
			return EmuSIMD::Funcs::set_index_mask_u32x8<I0_, I1_, I2_, I3_, I4_, I5_, I6_, I7_>();
		}
	};
	template<bool AllIndices_>
	struct _per_index_mask<EmuSIMD::u32x8, AllIndices_>
	{
		[[nodiscard]] static inline EmuSIMD::u32x8 get()
		{
			return EmuSIMD::Funcs::set_index_mask_u32x8<AllIndices_>();
		}
	};

	template<bool I0_, bool I1_, bool I2_, bool I3_>
	struct _per_index_mask<EmuSIMD::u64x4, I0_, I1_, I2_, I3_>
	{
		[[nodiscard]] static inline EmuSIMD::u64x4 get()
		{
			return EmuSIMD::Funcs::set_index_mask_u64x4<I0_, I1_, I2_, I3_>();
		}
	};
	template<bool AllIndices_>
	struct _per_index_mask<EmuSIMD::u64x4, AllIndices_>
	{
		[[nodiscard]] static inline EmuSIMD::u64x4 get()
		{
			return EmuSIMD::Funcs::set_index_mask_u64x4<AllIndices_>();
		}
	};

	template
	<
		bool I0_,  bool I1_,  bool I2_,  bool I3_,  bool I4_,  bool I5_,  bool I6_,  bool I7_,  bool I8_,  bool I9_,  bool I10_, bool I11_, bool I12_, bool I13_, bool I14_, bool I15_,
		bool I16_, bool I17_, bool I18_, bool I19_, bool I20_, bool I21_, bool I22_, bool I23_, bool I24_, bool I25_, bool I26_, bool I27_, bool I28_, bool I29_, bool I30_, bool I31_,
		bool I32_, bool I33_, bool I34_, bool I35_, bool I36_, bool I37_, bool I38_, bool I39_, bool I40_, bool I41_, bool I42_, bool I43_, bool I44_, bool I45_, bool I46_, bool I47_,
		bool I48_, bool I49_, bool I50_, bool I51_, bool I52_, bool I53_, bool I54_, bool I55_, bool I56_, bool I57_, bool I58_, bool I59_, bool I60_, bool I61_, bool I62_, bool I63_
	>
	struct _per_index_mask
	<
		EmuSIMD::u8x64,
		I0_,  I1_,  I2_,  I3_,  I4_,  I5_,  I6_,  I7_,  I8_,  I9_,  I10_, I11_, I12_, I13_, I14_, I15_,
		I16_, I17_, I18_, I19_, I20_, I21_, I22_, I23_, I24_, I25_, I26_, I27_, I28_, I29_, I30_, I31_,
		I32_, I33_, I34_, I35_, I36_, I37_, I38_, I39_, I40_, I41_, I42_, I43_, I44_, I45_, I46_, I47_,
		I48_, I49_, I50_, I51_, I52_, I53_, I54_, I55_, I56_, I57_, I58_, I59_, I60_, I61_, I62_, I63_
	>
	{
		[[nodiscard]] static inline EmuSIMD::u8x64 get()
		{
			return EmuSIMD::Funcs::set_index_mask_u8x64
			<
				I0_,  I1_,  I2_,  I3_,  I4_,  I5_,  I6_,  I7_,  I8_,  I9_,  I10_, I11_, I12_, I13_, I14_, I15_,
				I16_, I17_, I18_, I19_, I20_, I21_, I22_, I23_, I24_, I25_, I26_, I27_, I28_, I29_, I30_, I31_,
				I32_, I33_, I34_, I35_, I36_, I37_, I38_, I39_, I40_, I41_, I42_, I43_, I44_, I45_, I46_, I47_,
				I48_, I49_, I50_, I51_, I52_, I53_, I54_, I55_, I56_, I57_, I58_, I59_, I60_, I61_, I62_, I63_
			>();
		}
	};
	template<bool AllIndices_>
	struct _per_index_mask<EmuSIMD::u8x64, AllIndices_>
	{
		[[nodiscard]] static inline EmuSIMD::u8x64 get()
		{
			return EmuSIMD::Funcs::set_index_mask_u8x64<AllIndices_>();
		}
	};

	template
	<
		bool I0_,  bool I1_,  bool I2_,  bool I3_,  bool I4_,  bool I5_,  bool I6_,  bool I7_,  bool I8_,  bool I9_,  bool I10_, bool I11_, bool I12_, bool I13_, bool I14_, bool I15_,
		bool I16_, bool I17_, bool I18_, bool I19_, bool I20_, bool I21_, bool I22_, bool I23_, bool I24_, bool I25_, bool I26_, bool I27_, bool I28_, bool I29_, bool I30_, bool I31_
	>
	struct _per_index_mask
	<
		EmuSIMD::u16x32,
		I0_,  I1_,  I2_,  I3_,  I4_,  I5_,  I6_,  I7_,  I8_,  I9_,  I10_, I11_, I12_, I13_, I14_, I15_,
		I16_, I17_, I18_, I19_, I20_, I21_, I22_, I23_, I24_, I25_, I26_, I27_, I28_, I29_, I30_, I31_
	>
	{
		[[nodiscard]] static inline EmuSIMD::u16x32 get()
		{
			return EmuSIMD::Funcs::set_index_mask_u16x32
			<
				I0_,  I1_,  I2_,  I3_,  I4_,  I5_,  I6_,  I7_,  I8_,  I9_,  I10_, I11_, I12_, I13_, I14_, I15_,
				I16_, I17_, I18_, I19_, I20_, I21_, I22_, I23_, I24_, I25_, I26_, I27_, I28_, I29_, I30_, I31_
			>();
		}
	};
	template<bool AllIndices_>
	struct _per_index_mask<EmuSIMD::u16x32, AllIndices_>
	{
		[[nodiscard]] static inline EmuSIMD::u16x32 get()
		{
			return EmuSIMD::Funcs::set_index_mask_u16x32<AllIndices_>();
		}
	};

	template<bool I0_, bool I1_, bool I2_, bool I3_, bool I4_, bool I5_, bool I6_, bool I7_, bool I8_, bool I9_, bool I10_, bool I11_, bool I12_, bool I13_, bool I14_, bool I15_>
	struct _per_index_mask<EmuSIMD::u32x16, I0_, I1_, I2_, I3_, I4_, I5_, I6_, I7_, I8_, I9_, I10_, I11_, I12_, I13_, I14_, I15_>
	{
		[[nodiscard]] static inline EmuSIMD::u32x16 get()
		{
			return EmuSIMD::Funcs::set_index_mask_u32x16<I0_, I1_, I2_, I3_, I4_, I5_, I6_, I7_, I8_, I9_, I10_, I11_, I12_, I13_, I14_, I15_>();
		}
	};
	template<bool AllIndices_>
	struct _per_index_mask<EmuSIMD::u32x16, AllIndices_>
	{
		[[nodiscard]] static inline EmuSIMD::u32x16 get()
		{
			return EmuSIMD::Funcs::set_index_mask_u32x16<AllIndices_>();
		}
	};

	template<bool I0_, bool I1_, bool I2_, bool I3_, bool I4_, bool I5_, bool I6_, bool I7_>
	struct _per_index_mask<EmuSIMD::u64x8, I0_, I1_, I2_, I3_, I4_, I5_, I6_, I7_>
	{
		[[nodiscard]] static inline EmuSIMD::u64x8 get()
		{
			return EmuSIMD::Funcs::set_index_mask_u64x8<I0_, I1_, I2_, I3_, I4_, I5_, I6_, I7_>();
		}
	};
	template<bool AllIndices_>
	struct _per_index_mask<EmuSIMD::u64x8, AllIndices_>
	{
		[[nodiscard]] static inline EmuSIMD::u64x8 get()
		{
			return EmuSIMD::Funcs::set_index_mask_u64x8<AllIndices_>();
		}
	};
#endif
#pragma endregion

#pragma region SINGLE_INDEX_MASK_ABSTRACTIONS
	template<class Register_, std::size_t Index_, std::size_t PerElementWidthIfGenericInt_ = 32>
	struct _single_index_mask
	{
	};

	template<std::size_t Index_, std::size_t PerElementWidthIfGenericInt_>
	struct _single_index_mask<EmuSIMD::f32x4, Index_, PerElementWidthIfGenericInt_> : 
		public _per_index_mask<EmuSIMD::f32x4, Index_ == 0, Index_ == 1, Index_ == 2, Index_ == 3>
	{
		static_assert(EmuSIMD::TMP::valid_register_index_v<EmuSIMD::f32x4, Index_>, "Invalid index provided when attempting to retrieve a single index mask for a EmuSIMD::f32x4 SIMD register.");
	};

	template<std::size_t Index_, std::size_t PerElementWidthIfGenericInt_>
	struct _single_index_mask<EmuSIMD::f32x8, Index_, PerElementWidthIfGenericInt_> : 
		public _per_index_mask<EmuSIMD::f32x8, Index_ == 0, Index_ == 1, Index_ == 2, Index_ == 3, Index_ == 4, Index_ == 5, Index_ == 6, Index_ == 7>
	{
		static_assert(EmuSIMD::TMP::valid_register_index_v<EmuSIMD::f32x8, Index_>, "Invalid index provided when attempting to retrieve a single index mask for a EmuSIMD::f32x8 SIMD register.");
	};

	template<std::size_t Index_, std::size_t PerElementWidthIfGenericInt_>
	struct _single_index_mask<EmuSIMD::f32x16, Index_, PerElementWidthIfGenericInt_> :
		public _per_index_mask
		<
			EmuSIMD::f32x16,
			Index_ == 0, Index_ == 1, Index_ == 2,  Index_ == 3,  Index_ == 4,  Index_ == 5,  Index_ == 6,  Index_ == 7,
			Index_ == 8, Index_ == 9, Index_ == 10, Index_ == 11, Index_ == 12, Index_ == 13, Index_ == 14, Index_ == 15
		>
	{
		static_assert(EmuSIMD::TMP::valid_register_index_v<EmuSIMD::f32x16, Index_>, "Invalid index provided when attempting to retrieve a single index mask for a EmuSIMD::f32x16 SIMD register.");
	};

	template<std::size_t Index_, std::size_t PerElementWidthIfGenericInt_>
	struct _single_index_mask<EmuSIMD::f64x2, Index_, PerElementWidthIfGenericInt_> :
		public _per_index_mask<EmuSIMD::f64x2, Index_ == 0, Index_ == 1>
	{
		static_assert(EmuSIMD::TMP::valid_register_index_v<EmuSIMD::f64x2, Index_>, "Invalid index provided when attempting to retrieve a single index mask for a EmuSIMD::f64x2 SIMD register.");
	};

	template<std::size_t Index_, std::size_t PerElementWidthIfGenericInt_>
	struct _single_index_mask<EmuSIMD::f64x4, Index_, PerElementWidthIfGenericInt_> : 
		public _per_index_mask<EmuSIMD::f64x4, Index_ == 0, Index_ == 1, Index_ == 2, Index_ == 3>
	{
		static_assert(EmuSIMD::TMP::valid_register_index_v<EmuSIMD::f64x4, Index_>, "Invalid index provided when attempting to retrieve a single index mask for a EmuSIMD::f64x4 SIMD register.");
	};

	template<std::size_t Index_, std::size_t PerElementWidthIfGenericInt_>
	struct _single_index_mask<EmuSIMD::f64x8, Index_, PerElementWidthIfGenericInt_> : 
		public _per_index_mask<EmuSIMD::f64x8, Index_ == 0, Index_ == 1, Index_ == 2, Index_ == 3, Index_ == 4, Index_ == 5, Index_ == 6, Index_ == 7>
	{
		static_assert(EmuSIMD::TMP::valid_register_index_v<EmuSIMD::f64x8, Index_>, "Invalid index provided when attempting to retrieve a single index mask for a EmuSIMD::f64x8 SIMD register.");
	};

#if EMU_SIMD_USE_GENERIC_INT_REGISTERS
	template<std::size_t Index_>
	struct _single_index_mask<EmuSIMD::i128_generic, Index_, 8> :
		public _per_index_mask
		<
			EmuSIMD::i128_generic,
			Index_ == 0, Index_ == 1, Index_ == 2,  Index_ == 3,  Index_ == 4,  Index_ == 5,  Index_ == 6,  Index_ == 7,
			Index_ == 8, Index_ == 9, Index_ == 10, Index_ == 11, Index_ == 12, Index_ == 13, Index_ == 14, Index_ == 15
		>
	{
		static_assert(EmuSIMD::TMP::valid_register_index_v<EmuSIMD::i128_generic, Index_, 8>, "Invalid index provided when attempting to retrieve a single index mask for a EmuSIMD::i128_generic SIMD register identified to have 8-bit elements.");
	};	
	template<std::size_t Index_>
	struct _single_index_mask<EmuSIMD::i128_generic, Index_, 16> :
		public _per_index_mask<EmuSIMD::i128_generic, Index_ == 0, Index_ == 1, Index_ == 2, Index_ == 3, Index_ == 4, Index_ == 5, Index_ == 6, Index_ == 7>
	{
		static_assert(EmuSIMD::TMP::valid_register_index_v<EmuSIMD::i128_generic, Index_, 16>, "Invalid index provided when attempting to retrieve a single index mask for a EmuSIMD::i128_generic SIMD register identified to have 16-bit elements.");
	};
	template<std::size_t Index_>
	struct _single_index_mask<EmuSIMD::i128_generic, Index_, 32> :
		public _per_index_mask<EmuSIMD::i128_generic, Index_ == 0, Index_ == 1, Index_ == 2, Index_ == 3>
	{
		static_assert(EmuSIMD::TMP::valid_register_index_v<EmuSIMD::i128_generic, Index_, 32>, "Invalid index provided when attempting to retrieve a single index mask for a EmuSIMD::i128_generic SIMD register identified to have 32-bit elements.");
	};
	template<std::size_t Index_>
	struct _single_index_mask<EmuSIMD::i128_generic, Index_, 64> :
		public _per_index_mask<EmuSIMD::i128_generic, Index_ == 0, Index_ == 1>
	{
		static_assert(EmuSIMD::TMP::valid_register_index_v<EmuSIMD::i128_generic, Index_, 64>, "Invalid index provided when attempting to retrieve a single index mask for a EmuSIMD::i128_generic SIMD register identified to have 64-bit elements.");
	};
	
	template<std::size_t Index_>
	struct _single_index_mask<EmuSIMD::i256_generic, Index_, 8> :
		public _per_index_mask
		<
			EmuSIMD::i256_generic,
			Index_ == 0,  Index_ == 1,  Index_ == 2,  Index_ == 3,  Index_ == 4,  Index_ == 5,  Index_ == 6,  Index_ == 7,
			Index_ == 8,  Index_ == 9,  Index_ == 10, Index_ == 11, Index_ == 12, Index_ == 13, Index_ == 14, Index_ == 15,
			Index_ == 16, Index_ == 17, Index_ == 18, Index_ == 19, Index_ == 20, Index_ == 21, Index_ == 22, Index_ == 23,
			Index_ == 24, Index_ == 25, Index_ == 26, Index_ == 27, Index_ == 28, Index_ == 29, Index_ == 30, Index_ == 31
		>
	{
		static_assert(EmuSIMD::TMP::valid_register_index_v<EmuSIMD::i256_generic, Index_, 8>, "Invalid index provided when attempting to retrieve a single index mask for a EmuSIMD::i256_generic SIMD register identified to have 8-bit elements.");
	};	
	template<std::size_t Index_>
	struct _single_index_mask<EmuSIMD::i256_generic, Index_, 16> :
		public _per_index_mask
		<
			EmuSIMD::i256_generic,
			Index_ == 0, Index_ == 1, Index_ == 2,  Index_ == 3,  Index_ == 4,  Index_ == 5,  Index_ == 6,  Index_ == 7,
			Index_ == 8, Index_ == 9, Index_ == 10, Index_ == 11, Index_ == 12, Index_ == 13, Index_ == 14, Index_ == 15
		>
	{
		static_assert(EmuSIMD::TMP::valid_register_index_v<EmuSIMD::i256_generic, Index_, 16>, "Invalid index provided when attempting to retrieve a single index mask for a EmuSIMD::i256_generic SIMD register identified to have 16-bit elements.");
	};	
	template<std::size_t Index_>
	struct _single_index_mask<EmuSIMD::i256_generic, Index_, 32> :
		public _per_index_mask<EmuSIMD::i256_generic, Index_ == 0, Index_ == 1, Index_ == 2, Index_ == 3, Index_ == 4, Index_ == 5, Index_ == 6, Index_ == 7>
	{
		static_assert(EmuSIMD::TMP::valid_register_index_v<EmuSIMD::i256_generic, Index_, 32>, "Invalid index provided when attempting to retrieve a single index mask for a EmuSIMD::i256_generic SIMD register identified to have 32-bit elements.");
	};
	template<std::size_t Index_>
	struct _single_index_mask<EmuSIMD::i256_generic, Index_, 64> :
		public _per_index_mask<EmuSIMD::i256_generic, Index_ == 0, Index_ == 1, Index_ == 2, Index_ == 3>
	{
		static_assert(EmuSIMD::TMP::valid_register_index_v<EmuSIMD::i256_generic, Index_, 64>, "Invalid index provided when attempting to retrieve a single index mask for a EmuSIMD::i256_generic SIMD register identified to have 64-bit elements.");
	};
	
	template<std::size_t Index_>
	struct _single_index_mask<EmuSIMD::i512_generic, Index_, 8> :
		public _per_index_mask
		<
			EmuSIMD::i512_generic,
			Index_ == 0,  Index_ == 1,  Index_ == 2,  Index_ == 3,  Index_ == 4,  Index_ == 5,  Index_ == 6,  Index_ == 7,
			Index_ == 8,  Index_ == 9,  Index_ == 10, Index_ == 11, Index_ == 12, Index_ == 13, Index_ == 14, Index_ == 15,
			Index_ == 16, Index_ == 17, Index_ == 18, Index_ == 19, Index_ == 20, Index_ == 21, Index_ == 22, Index_ == 23,
			Index_ == 24, Index_ == 25, Index_ == 26, Index_ == 27, Index_ == 28, Index_ == 29, Index_ == 30, Index_ == 31,
			Index_ == 32, Index_ == 33, Index_ == 34, Index_ == 35, Index_ == 36, Index_ == 37, Index_ == 38, Index_ == 39,
			Index_ == 40, Index_ == 41, Index_ == 42, Index_ == 43, Index_ == 44, Index_ == 45, Index_ == 46, Index_ == 47,
			Index_ == 48, Index_ == 49, Index_ == 50, Index_ == 51, Index_ == 52, Index_ == 53, Index_ == 54, Index_ == 55,
			Index_ == 56, Index_ == 57, Index_ == 58, Index_ == 59, Index_ == 60, Index_ == 61, Index_ == 62, Index_ == 63
		>
	{
		static_assert(EmuSIMD::TMP::valid_register_index_v<EmuSIMD::i512_generic, Index_, 8>, "Invalid index provided when attempting to retrieve a single index mask for a EmuSIMD::i512_generic SIMD register identified to have 8-bit elements.");
	};	
	template<std::size_t Index_>
	struct _single_index_mask<EmuSIMD::i512_generic, Index_, 16> :
		public _per_index_mask
		<
			EmuSIMD::i512_generic,
			Index_ == 0,  Index_ == 1,  Index_ == 2,  Index_ == 3,  Index_ == 4,  Index_ == 5,  Index_ == 6,  Index_ == 7,
			Index_ == 8,  Index_ == 9,  Index_ == 10, Index_ == 11, Index_ == 12, Index_ == 13, Index_ == 14, Index_ == 15,
			Index_ == 16, Index_ == 17, Index_ == 18, Index_ == 19, Index_ == 20, Index_ == 21, Index_ == 22, Index_ == 23,
			Index_ == 24, Index_ == 25, Index_ == 26, Index_ == 27, Index_ == 28, Index_ == 29, Index_ == 30, Index_ == 31
		>
	{
		static_assert(EmuSIMD::TMP::valid_register_index_v<EmuSIMD::i512_generic, Index_, 16>, "Invalid index provided when attempting to retrieve a single index mask for a EmuSIMD::i512_generic SIMD register identified to have 16-bit elements.");
	};	
	template<std::size_t Index_>
	struct _single_index_mask<EmuSIMD::i512_generic, Index_, 32> :
		public _per_index_mask
		<
			EmuSIMD::i512_generic,
			Index_ == 0, Index_ == 1, Index_ == 2,  Index_ == 3,  Index_ == 4,  Index_ == 5,  Index_ == 6,  Index_ == 7,
			Index_ == 8, Index_ == 9, Index_ == 10, Index_ == 11, Index_ == 12, Index_ == 13, Index_ == 14, Index_ == 15
		>
	{
		static_assert(EmuSIMD::TMP::valid_register_index_v<EmuSIMD::i512_generic, Index_, 32>, "Invalid index provided when attempting to retrieve a single index mask for a EmuSIMD::i512_generic SIMD register identified to have 32-bit elements.");
	};	
	template<std::size_t Index_>
	struct _single_index_mask<EmuSIMD::i512_generic, Index_, 64> :
		public _per_index_mask<EmuSIMD::i512_generic, Index_ == 0, Index_ == 1, Index_ == 2, Index_ == 3, Index_ == 4, Index_ == 5, Index_ == 6, Index_ == 7>
	{
		static_assert(EmuSIMD::TMP::valid_register_index_v<EmuSIMD::i512_generic, Index_, 64>, "Invalid index provided when attempting to retrieve a single index mask for a EmuSIMD::i512_generic SIMD register identified to have 64-bit elements.");
	};
#else
	template<std::size_t Index_, std::size_t PerElementWidthIfGenericInt_>
	struct _single_index_mask<EmuSIMD::i8x16, Index_, PerElementWidthIfGenericInt_> :
		public _per_index_mask
		<
			EmuSIMD::i8x16,
			Index_ == 0, Index_ == 1, Index_ == 2,  Index_ == 3,  Index_ == 4,  Index_ == 5,  Index_ == 6,  Index_ == 7,
			Index_ == 8, Index_ == 9, Index_ == 10, Index_ == 11, Index_ == 12, Index_ == 13, Index_ == 14, Index_ == 15
		>
	{
		static_assert(EmuSIMD::TMP::valid_register_index_v<EmuSIMD::i8x16, Index_>, "Invalid index provided when attempting to retrieve a single index mask for a EmuSIMD::i8x16 SIMD register.");
	};	
	template<std::size_t Index_, std::size_t PerElementWidthIfGenericInt_>
	struct _single_index_mask<EmuSIMD::i16x8, Index_, PerElementWidthIfGenericInt_> :
		public _per_index_mask<EmuSIMD::i16x8, Index_ == 0, Index_ == 1, Index_ == 2, Index_ == 3, Index_ == 4, Index_ == 5, Index_ == 6, Index_ == 7>
	{
		static_assert(EmuSIMD::TMP::valid_register_index_v<EmuSIMD::i16x8, Index_>, "Invalid index provided when attempting to retrieve a single index mask for a EmuSIMD::i16x8 SIMD register.");
	};
	template<std::size_t Index_, std::size_t PerElementWidthIfGenericInt_>
	struct _single_index_mask<EmuSIMD::i32x4, Index_, PerElementWidthIfGenericInt_> :
		public _per_index_mask<EmuSIMD::i32x4, Index_ == 0, Index_ == 1, Index_ == 2, Index_ == 3>
	{
		static_assert(EmuSIMD::TMP::valid_register_index_v<EmuSIMD::i32x4, Index_>, "Invalid index provided when attempting to retrieve a single index mask for a EmuSIMD::i32x4 SIMD register.");
	};
	template<std::size_t Index_, std::size_t PerElementWidthIfGenericInt_>
	struct _single_index_mask<EmuSIMD::i64x2, Index_, PerElementWidthIfGenericInt_> :
		public _per_index_mask<EmuSIMD::i64x2, Index_ == 0, Index_ == 1>
	{
		static_assert(EmuSIMD::TMP::valid_register_index_v<EmuSIMD::i64x2, Index_>, "Invalid index provided when attempting to retrieve a single index mask for a EmuSIMD::i64x2 SIMD register.");
	};
	
	template<std::size_t Index_, std::size_t PerElementWidthIfGenericInt_>
	struct _single_index_mask<EmuSIMD::i8x32, Index_, PerElementWidthIfGenericInt_> :
		public _per_index_mask
		<
			EmuSIMD::i8x32,
			Index_ == 0,  Index_ == 1,  Index_ == 2,  Index_ == 3,  Index_ == 4,  Index_ == 5,  Index_ == 6,  Index_ == 7,
			Index_ == 8,  Index_ == 9,  Index_ == 10, Index_ == 11, Index_ == 12, Index_ == 13, Index_ == 14, Index_ == 15,
			Index_ == 16, Index_ == 17, Index_ == 18, Index_ == 19, Index_ == 20, Index_ == 21, Index_ == 22, Index_ == 23,
			Index_ == 24, Index_ == 25, Index_ == 26, Index_ == 27, Index_ == 28, Index_ == 29, Index_ == 30, Index_ == 31
		>
	{
		static_assert(EmuSIMD::TMP::valid_register_index_v<EmuSIMD::i8x32, Index_>, "Invalid index provided when attempting to retrieve a single index mask for a EmuSIMD::i8x32 SIMD register.");
	};	
	template<std::size_t Index_, std::size_t PerElementWidthIfGenericInt_>
	struct _single_index_mask<EmuSIMD::i16x16, Index_, PerElementWidthIfGenericInt_> :
		public _per_index_mask
		<
			EmuSIMD::i16x16,
			Index_ == 0, Index_ == 1, Index_ == 2,  Index_ == 3,  Index_ == 4,  Index_ == 5,  Index_ == 6,  Index_ == 7,
			Index_ == 8, Index_ == 9, Index_ == 10, Index_ == 11, Index_ == 12, Index_ == 13, Index_ == 14, Index_ == 15
		>
	{
		static_assert(EmuSIMD::TMP::valid_register_index_v<EmuSIMD::i16x16, Index_>, "Invalid index provided when attempting to retrieve a single index mask for a EmuSIMD::i16x16 SIMD register.");
	};	
	template<std::size_t Index_, std::size_t PerElementWidthIfGenericInt_>
	struct _single_index_mask<EmuSIMD::i32x8, Index_, PerElementWidthIfGenericInt_> :
		public _per_index_mask<EmuSIMD::i32x8, Index_ == 0, Index_ == 1, Index_ == 2, Index_ == 3, Index_ == 4, Index_ == 5, Index_ == 6, Index_ == 7>
	{
		static_assert(EmuSIMD::TMP::valid_register_index_v<EmuSIMD::i32x8, Index_>, "Invalid index provided when attempting to retrieve a single index mask for a EmuSIMD::i32x8 SIMD register.");
	};
	template<std::size_t Index_, std::size_t PerElementWidthIfGenericInt_>
	struct _single_index_mask<EmuSIMD::i64x4, Index_, PerElementWidthIfGenericInt_> :
		public _per_index_mask<EmuSIMD::i64x4, Index_ == 0, Index_ == 1, Index_ == 2, Index_ == 3>
	{
		static_assert(EmuSIMD::TMP::valid_register_index_v<EmuSIMD::i64x4, Index_>, "Invalid index provided when attempting to retrieve a single index mask for a EmuSIMD::i64x4 SIMD register.");
	};
	
	template<std::size_t Index_, std::size_t PerElementWidthIfGenericInt_>
	struct _single_index_mask<EmuSIMD::i8x64, Index_, PerElementWidthIfGenericInt_> :
		public _per_index_mask
		<
			EmuSIMD::i8x64,
			Index_ == 0,  Index_ == 1,  Index_ == 2,  Index_ == 3,  Index_ == 4,  Index_ == 5,  Index_ == 6,  Index_ == 7,
			Index_ == 8,  Index_ == 9,  Index_ == 10, Index_ == 11, Index_ == 12, Index_ == 13, Index_ == 14, Index_ == 15,
			Index_ == 16, Index_ == 17, Index_ == 18, Index_ == 19, Index_ == 20, Index_ == 21, Index_ == 22, Index_ == 23,
			Index_ == 24, Index_ == 25, Index_ == 26, Index_ == 27, Index_ == 28, Index_ == 29, Index_ == 30, Index_ == 31,
			Index_ == 32, Index_ == 33, Index_ == 34, Index_ == 35, Index_ == 36, Index_ == 37, Index_ == 38, Index_ == 39,
			Index_ == 40, Index_ == 41, Index_ == 42, Index_ == 43, Index_ == 44, Index_ == 45, Index_ == 46, Index_ == 47,
			Index_ == 48, Index_ == 49, Index_ == 50, Index_ == 51, Index_ == 52, Index_ == 53, Index_ == 54, Index_ == 55,
			Index_ == 56, Index_ == 57, Index_ == 58, Index_ == 59, Index_ == 60, Index_ == 61, Index_ == 62, Index_ == 63
		>
	{
		static_assert(EmuSIMD::TMP::valid_register_index_v<EmuSIMD::i8x64, Index_>, "Invalid index provided when attempting to retrieve a single index mask for a EmuSIMD::i8x64 SIMD register.");
	};	
	template<std::size_t Index_, std::size_t PerElementWidthIfGenericInt_>
	struct _single_index_mask<EmuSIMD::i16x32, Index_, PerElementWidthIfGenericInt_> :
		public _per_index_mask
		<
			EmuSIMD::i16x32,
			Index_ == 0,  Index_ == 1,  Index_ == 2,  Index_ == 3,  Index_ == 4,  Index_ == 5,  Index_ == 6,  Index_ == 7,
			Index_ == 8,  Index_ == 9,  Index_ == 10, Index_ == 11, Index_ == 12, Index_ == 13, Index_ == 14, Index_ == 15,
			Index_ == 16, Index_ == 17, Index_ == 18, Index_ == 19, Index_ == 20, Index_ == 21, Index_ == 22, Index_ == 23,
			Index_ == 24, Index_ == 25, Index_ == 26, Index_ == 27, Index_ == 28, Index_ == 29, Index_ == 30, Index_ == 31
		>
	{
		static_assert(EmuSIMD::TMP::valid_register_index_v<EmuSIMD::i16x32, Index_>, "Invalid index provided when attempting to retrieve a single index mask for a EmuSIMD::i16x32 SIMD register.");
	};	
	template<std::size_t Index_, std::size_t PerElementWidthIfGenericInt_>
	struct _single_index_mask<EmuSIMD::i32x16, Index_, PerElementWidthIfGenericInt_> :
		public _per_index_mask
		<
			EmuSIMD::i32x16,
			Index_ == 0, Index_ == 1, Index_ == 2,  Index_ == 3,  Index_ == 4,  Index_ == 5,  Index_ == 6,  Index_ == 7,
			Index_ == 8, Index_ == 9, Index_ == 10, Index_ == 11, Index_ == 12, Index_ == 13, Index_ == 14, Index_ == 15
		>
	{
		static_assert(EmuSIMD::TMP::valid_register_index_v<EmuSIMD::i32x16, Index_>, "Invalid index provided when attempting to retrieve a single index mask for a EmuSIMD::i32x16 SIMD register.");
	};	
	template<std::size_t Index_, std::size_t PerElementWidthIfGenericInt_>
	struct _single_index_mask<EmuSIMD::i64x8, Index_, PerElementWidthIfGenericInt_> :
		public _per_index_mask<EmuSIMD::i64x8, Index_ == 0, Index_ == 1, Index_ == 2, Index_ == 3, Index_ == 4, Index_ == 5, Index_ == 6, Index_ == 7>
	{
		static_assert(EmuSIMD::TMP::valid_register_index_v<EmuSIMD::i64x8, Index_>, "Invalid index provided when attempting to retrieve a single index mask for a EmuSIMD::i64x8 SIMD register.");
	};

	template<std::size_t Index_, std::size_t PerElementWidthIfGenericInt_>
	struct _single_index_mask<EmuSIMD::u8x16, Index_, PerElementWidthIfGenericInt_> :
		public _per_index_mask
		<
			EmuSIMD::u8x16,
			Index_ == 0, Index_ == 1, Index_ == 2,  Index_ == 3,  Index_ == 4,  Index_ == 5,  Index_ == 6,  Index_ == 7,
			Index_ == 8, Index_ == 9, Index_ == 10, Index_ == 11, Index_ == 12, Index_ == 13, Index_ == 14, Index_ == 15
		>
	{
		static_assert(EmuSIMD::TMP::valid_register_index_v<EmuSIMD::u8x16, Index_>, "Invalid index provided when attempting to retrieve a single index mask for a EmuSIMD::u8x16 SIMD register.");
	};	
	template<std::size_t Index_, std::size_t PerElementWidthIfGenericInt_>
	struct _single_index_mask<EmuSIMD::u16x8, Index_, PerElementWidthIfGenericInt_> :
		public _per_index_mask<EmuSIMD::u16x8, Index_ == 0, Index_ == 1, Index_ == 2, Index_ == 3, Index_ == 4, Index_ == 5, Index_ == 6, Index_ == 7>
	{
		static_assert(EmuSIMD::TMP::valid_register_index_v<EmuSIMD::u16x8, Index_>, "Invalid index provided when attempting to retrieve a single index mask for a EmuSIMD::u16x8 SIMD register.");
	};
	template<std::size_t Index_, std::size_t PerElementWidthIfGenericInt_>
	struct _single_index_mask<EmuSIMD::u32x4, Index_, PerElementWidthIfGenericInt_> :
		public _per_index_mask<EmuSIMD::u32x4, Index_ == 0, Index_ == 1, Index_ == 2, Index_ == 3>
	{
		static_assert(EmuSIMD::TMP::valid_register_index_v<EmuSIMD::u32x4, Index_>, "Invalid index provided when attempting to retrieve a single index mask for a EmuSIMD::u32x4 SIMD register.");
	};
	template<std::size_t Index_, std::size_t PerElementWidthIfGenericInt_>
	struct _single_index_mask<EmuSIMD::u64x2, Index_, PerElementWidthIfGenericInt_> :
		public _per_index_mask<EmuSIMD::u64x2, Index_ == 0, Index_ == 1>
	{
		static_assert(EmuSIMD::TMP::valid_register_index_v<EmuSIMD::u64x2, Index_>, "Invalid index provided when attempting to retrieve a single index mask for a EmuSIMD::u64x2 SIMD register.");
	};
	
	template<std::size_t Index_, std::size_t PerElementWidthIfGenericInt_>
	struct _single_index_mask<EmuSIMD::u8x32, Index_, PerElementWidthIfGenericInt_> :
		public _per_index_mask
		<
			EmuSIMD::u8x32,
			Index_ == 0,  Index_ == 1,  Index_ == 2,  Index_ == 3,  Index_ == 4,  Index_ == 5,  Index_ == 6,  Index_ == 7,
			Index_ == 8,  Index_ == 9,  Index_ == 10, Index_ == 11, Index_ == 12, Index_ == 13, Index_ == 14, Index_ == 15,
			Index_ == 16, Index_ == 17, Index_ == 18, Index_ == 19, Index_ == 20, Index_ == 21, Index_ == 22, Index_ == 23,
			Index_ == 24, Index_ == 25, Index_ == 26, Index_ == 27, Index_ == 28, Index_ == 29, Index_ == 30, Index_ == 31
		>
	{
		static_assert(EmuSIMD::TMP::valid_register_index_v<EmuSIMD::u8x32, Index_>, "Invalid index provided when attempting to retrieve a single index mask for a EmuSIMD::u8x32 SIMD register.");
	};	
	template<std::size_t Index_, std::size_t PerElementWidthIfGenericInt_>
	struct _single_index_mask<EmuSIMD::u16x16, Index_, PerElementWidthIfGenericInt_> :
		public _per_index_mask
		<
			EmuSIMD::u16x16,
			Index_ == 0, Index_ == 1, Index_ == 2,  Index_ == 3,  Index_ == 4,  Index_ == 5,  Index_ == 6,  Index_ == 7,
			Index_ == 8, Index_ == 9, Index_ == 10, Index_ == 11, Index_ == 12, Index_ == 13, Index_ == 14, Index_ == 15
		>
	{
		static_assert(EmuSIMD::TMP::valid_register_index_v<EmuSIMD::u16x16, Index_>, "Invalid index provided when attempting to retrieve a single index mask for a EmuSIMD::u16x16 SIMD register.");
	};	
	template<std::size_t Index_, std::size_t PerElementWidthIfGenericInt_>
	struct _single_index_mask<EmuSIMD::u32x8, Index_, PerElementWidthIfGenericInt_> :
		public _per_index_mask<EmuSIMD::u32x8, Index_ == 0, Index_ == 1, Index_ == 2, Index_ == 3, Index_ == 4, Index_ == 5, Index_ == 6, Index_ == 7>
	{
		static_assert(EmuSIMD::TMP::valid_register_index_v<EmuSIMD::u32x8, Index_>, "Invalid index provided when attempting to retrieve a single index mask for a EmuSIMD::u32x8 SIMD register.");
	};
	template<std::size_t Index_, std::size_t PerElementWidthIfGenericInt_>
	struct _single_index_mask<EmuSIMD::u64x4, Index_, PerElementWidthIfGenericInt_> :
		public _per_index_mask<EmuSIMD::u64x4, Index_ == 0, Index_ == 1, Index_ == 2, Index_ == 3>
	{
		static_assert(EmuSIMD::TMP::valid_register_index_v<EmuSIMD::u64x4, Index_>, "Invalid index provided when attempting to retrieve a single index mask for a EmuSIMD::u64x4 SIMD register.");
	};
	
	template<std::size_t Index_, std::size_t PerElementWidthIfGenericInt_>
	struct _single_index_mask<EmuSIMD::u8x64, Index_, PerElementWidthIfGenericInt_> :
		public _per_index_mask
		<
			EmuSIMD::u8x64,
			Index_ == 0,  Index_ == 1,  Index_ == 2,  Index_ == 3,  Index_ == 4,  Index_ == 5,  Index_ == 6,  Index_ == 7,
			Index_ == 8,  Index_ == 9,  Index_ == 10, Index_ == 11, Index_ == 12, Index_ == 13, Index_ == 14, Index_ == 15,
			Index_ == 16, Index_ == 17, Index_ == 18, Index_ == 19, Index_ == 20, Index_ == 21, Index_ == 22, Index_ == 23,
			Index_ == 24, Index_ == 25, Index_ == 26, Index_ == 27, Index_ == 28, Index_ == 29, Index_ == 30, Index_ == 31,
			Index_ == 32, Index_ == 33, Index_ == 34, Index_ == 35, Index_ == 36, Index_ == 37, Index_ == 38, Index_ == 39,
			Index_ == 40, Index_ == 41, Index_ == 42, Index_ == 43, Index_ == 44, Index_ == 45, Index_ == 46, Index_ == 47,
			Index_ == 48, Index_ == 49, Index_ == 50, Index_ == 51, Index_ == 52, Index_ == 53, Index_ == 54, Index_ == 55,
			Index_ == 56, Index_ == 57, Index_ == 58, Index_ == 59, Index_ == 60, Index_ == 61, Index_ == 62, Index_ == 63
		>
	{
		static_assert(EmuSIMD::TMP::valid_register_index_v<EmuSIMD::u8x64, Index_>, "Invalid index provided when attempting to retrieve a single index mask for a EmuSIMD::u8x64 SIMD register.");
	};	
	template<std::size_t Index_, std::size_t PerElementWidthIfGenericInt_>
	struct _single_index_mask<EmuSIMD::u16x32, Index_, PerElementWidthIfGenericInt_> :
		public _per_index_mask
		<
			EmuSIMD::u16x32,
			Index_ == 0,  Index_ == 1,  Index_ == 2,  Index_ == 3,  Index_ == 4,  Index_ == 5,  Index_ == 6,  Index_ == 7,
			Index_ == 8,  Index_ == 9,  Index_ == 10, Index_ == 11, Index_ == 12, Index_ == 13, Index_ == 14, Index_ == 15,
			Index_ == 16, Index_ == 17, Index_ == 18, Index_ == 19, Index_ == 20, Index_ == 21, Index_ == 22, Index_ == 23,
			Index_ == 24, Index_ == 25, Index_ == 26, Index_ == 27, Index_ == 28, Index_ == 29, Index_ == 30, Index_ == 31
		>
	{
		static_assert(EmuSIMD::TMP::valid_register_index_v<EmuSIMD::u16x32, Index_>, "Invalid index provided when attempting to retrieve a single index mask for a EmuSIMD::u16x32 SIMD register.");
	};	
	template<std::size_t Index_, std::size_t PerElementWidthIfGenericInt_>
	struct _single_index_mask<EmuSIMD::u32x16, Index_, PerElementWidthIfGenericInt_> :
		public _per_index_mask
		<
			EmuSIMD::u32x16,
			Index_ == 0, Index_ == 1, Index_ == 2,  Index_ == 3,  Index_ == 4,  Index_ == 5,  Index_ == 6,  Index_ == 7,
			Index_ == 8, Index_ == 9, Index_ == 10, Index_ == 11, Index_ == 12, Index_ == 13, Index_ == 14, Index_ == 15
		>
	{
		static_assert(EmuSIMD::TMP::valid_register_index_v<EmuSIMD::u32x16, Index_>, "Invalid index provided when attempting to retrieve a single index mask for a EmuSIMD::u32x16 SIMD register.");
	};	
	template<std::size_t Index_, std::size_t PerElementWidthIfGenericInt_>
	struct _single_index_mask<EmuSIMD::u64x8, Index_, PerElementWidthIfGenericInt_> :
		public _per_index_mask<EmuSIMD::u64x8, Index_ == 0, Index_ == 1, Index_ == 2, Index_ == 3, Index_ == 4, Index_ == 5, Index_ == 6, Index_ == 7>
	{
		static_assert(EmuSIMD::TMP::valid_register_index_v<EmuSIMD::u64x8, Index_>, "Invalid index provided when attempting to retrieve a single index mask for a EmuSIMD::u64x8 SIMD register.");
	};
#endif
#pragma endregion

#pragma region VARYING_MASK_TEMPLATE
	template<class Register_, bool FirstActive_, std::size_t PerElementWidthIfIntegral_ = 32>
	struct _alternating_index_mask
	{
	};

	template<bool FirstActive_, std::size_t PerElementWidthIfIntegral_>
	struct _alternating_index_mask<EmuSIMD::f32x4, FirstActive_, PerElementWidthIfIntegral_> :
		public _per_index_mask<EmuSIMD::f32x4, FirstActive_, !FirstActive_, FirstActive_, !FirstActive_>
	{
	};

	template<bool FirstActive_, std::size_t PerElementWidthIfIntegral_>
	struct _alternating_index_mask<EmuSIMD::f32x8, FirstActive_, PerElementWidthIfIntegral_> :
		public _per_index_mask<EmuSIMD::f32x8, FirstActive_, !FirstActive_, FirstActive_, !FirstActive_, FirstActive_, !FirstActive_, FirstActive_, !FirstActive_>
	{
	};
	
	template<bool FirstActive_, std::size_t PerElementWidthIfIntegral_>
	struct _alternating_index_mask<EmuSIMD::f32x16, FirstActive_, PerElementWidthIfIntegral_> :
		public _per_index_mask
		<
			EmuSIMD::f32x16,
			FirstActive_, !FirstActive_, FirstActive_, !FirstActive_, FirstActive_, !FirstActive_, FirstActive_, !FirstActive_,
			FirstActive_, !FirstActive_, FirstActive_, !FirstActive_, FirstActive_, !FirstActive_, FirstActive_, !FirstActive_
		>
	{
	};
	
	template<bool FirstActive_, std::size_t PerElementWidthIfIntegral_>
	struct _alternating_index_mask<EmuSIMD::f64x2, FirstActive_, PerElementWidthIfIntegral_> :
		public _per_index_mask<EmuSIMD::f64x4, FirstActive_, !FirstActive_>
	{
	};

	template<bool FirstActive_, std::size_t PerElementWidthIfIntegral_>
	struct _alternating_index_mask<EmuSIMD::f64x4, FirstActive_, PerElementWidthIfIntegral_> :
		public _per_index_mask<EmuSIMD::f64x4, FirstActive_, !FirstActive_, FirstActive_, !FirstActive_>
	{
	};

	template<bool FirstActive_, std::size_t PerElementWidthIfIntegral_>
	struct _alternating_index_mask<EmuSIMD::f64x8, FirstActive_, PerElementWidthIfIntegral_> :
		public _per_index_mask<EmuSIMD::f64x8, FirstActive_, !FirstActive_, FirstActive_, !FirstActive_, FirstActive_, !FirstActive_, FirstActive_, !FirstActive_>
	{
	};

#if EMU_SIMD_USE_GENERIC_INT_REGISTERS
	template<bool FirstActive_>
	struct _alternating_index_mask<EmuSIMD::i128_generic, FirstActive_, 8> :
		public _per_index_mask
		<
			EmuSIMD::i128_generic,
			FirstActive_, !FirstActive_, FirstActive_, !FirstActive_, FirstActive_, !FirstActive_, FirstActive_, !FirstActive_,
			FirstActive_, !FirstActive_, FirstActive_, !FirstActive_, FirstActive_, !FirstActive_, FirstActive_, !FirstActive_
		>
	{
	};
	template<bool FirstActive_>
	struct _alternating_index_mask<EmuSIMD::i128_generic, FirstActive_, 16> :
		public _per_index_mask<EmuSIMD::i128_generic, FirstActive_, !FirstActive_, FirstActive_, !FirstActive_, FirstActive_, !FirstActive_, FirstActive_, !FirstActive_>
	{
	};
	template<bool FirstActive_>
	struct _alternating_index_mask<EmuSIMD::i128_generic, FirstActive_, 32> :
		public _per_index_mask<EmuSIMD::i128_generic, FirstActive_, !FirstActive_, FirstActive_, !FirstActive_>
	{
	};
	template<bool FirstActive_>
	struct _alternating_index_mask<EmuSIMD::i128_generic, FirstActive_, 64> :
		public _per_index_mask<EmuSIMD::i128_generic, FirstActive_, !FirstActive_>
	{
	};
	
	template<bool FirstActive_>
	struct _alternating_index_mask<EmuSIMD::i256_generic, FirstActive_, 8> :
		public _per_index_mask
		<
			EmuSIMD::i256_generic,
			FirstActive_, !FirstActive_, FirstActive_, !FirstActive_, FirstActive_, !FirstActive_, FirstActive_, !FirstActive_,
			FirstActive_, !FirstActive_, FirstActive_, !FirstActive_, FirstActive_, !FirstActive_, FirstActive_, !FirstActive_,
			FirstActive_, !FirstActive_, FirstActive_, !FirstActive_, FirstActive_, !FirstActive_, FirstActive_, !FirstActive_,
			FirstActive_, !FirstActive_, FirstActive_, !FirstActive_, FirstActive_, !FirstActive_, FirstActive_, !FirstActive_
		>
	{
	};
	template<bool FirstActive_>
	struct _alternating_index_mask<EmuSIMD::i256_generic, FirstActive_, 16> :
		public _per_index_mask
		<
			EmuSIMD::i256_generic,
			FirstActive_, !FirstActive_, FirstActive_, !FirstActive_, FirstActive_, !FirstActive_, FirstActive_, !FirstActive_,
			FirstActive_, !FirstActive_, FirstActive_, !FirstActive_, FirstActive_, !FirstActive_, FirstActive_, !FirstActive_
		>
	{
	};
	template<bool FirstActive_>
	struct _alternating_index_mask<EmuSIMD::i256_generic, FirstActive_, 32> :
		public _per_index_mask<EmuSIMD::i256_generic, FirstActive_, !FirstActive_, FirstActive_, !FirstActive_, FirstActive_, !FirstActive_, FirstActive_, !FirstActive_>
	{
	};
	template<bool FirstActive_>
	struct _alternating_index_mask<EmuSIMD::i256_generic, FirstActive_, 64> :
		public _per_index_mask<EmuSIMD::i256_generic, FirstActive_, !FirstActive_, FirstActive_, !FirstActive_>
	{
	};
	
	template<bool FirstActive_>
	struct _alternating_index_mask<EmuSIMD::i512_generic, FirstActive_, 8> :
		public _per_index_mask
		<
			EmuSIMD::i512_generic,
			FirstActive_, !FirstActive_, FirstActive_, !FirstActive_, FirstActive_, !FirstActive_, FirstActive_, !FirstActive_,
			FirstActive_, !FirstActive_, FirstActive_, !FirstActive_, FirstActive_, !FirstActive_, FirstActive_, !FirstActive_,
			FirstActive_, !FirstActive_, FirstActive_, !FirstActive_, FirstActive_, !FirstActive_, FirstActive_, !FirstActive_,
			FirstActive_, !FirstActive_, FirstActive_, !FirstActive_, FirstActive_, !FirstActive_, FirstActive_, !FirstActive_,
			FirstActive_, !FirstActive_, FirstActive_, !FirstActive_, FirstActive_, !FirstActive_, FirstActive_, !FirstActive_,
			FirstActive_, !FirstActive_, FirstActive_, !FirstActive_, FirstActive_, !FirstActive_, FirstActive_, !FirstActive_,
			FirstActive_, !FirstActive_, FirstActive_, !FirstActive_, FirstActive_, !FirstActive_, FirstActive_, !FirstActive_,
			FirstActive_, !FirstActive_, FirstActive_, !FirstActive_, FirstActive_, !FirstActive_, FirstActive_, !FirstActive_
		>
	{
	};
	template<bool FirstActive_>
	struct _alternating_index_mask<EmuSIMD::i512_generic, FirstActive_, 16> :
		public _per_index_mask
		<
			EmuSIMD::i512_generic,
			FirstActive_, !FirstActive_, FirstActive_, !FirstActive_, FirstActive_, !FirstActive_, FirstActive_, !FirstActive_,
			FirstActive_, !FirstActive_, FirstActive_, !FirstActive_, FirstActive_, !FirstActive_, FirstActive_, !FirstActive_,
			FirstActive_, !FirstActive_, FirstActive_, !FirstActive_, FirstActive_, !FirstActive_, FirstActive_, !FirstActive_,
			FirstActive_, !FirstActive_, FirstActive_, !FirstActive_, FirstActive_, !FirstActive_, FirstActive_, !FirstActive_
		>
	{
	};
	template<bool FirstActive_>
	struct _alternating_index_mask<EmuSIMD::i512_generic, FirstActive_, 32> :
		public _per_index_mask
		<
			EmuSIMD::i512_generic,
			FirstActive_, !FirstActive_, FirstActive_, !FirstActive_, FirstActive_, !FirstActive_, FirstActive_, !FirstActive_,
			FirstActive_, !FirstActive_, FirstActive_, !FirstActive_, FirstActive_, !FirstActive_, FirstActive_, !FirstActive_
		>
	{
	};
	template<bool FirstActive_>
	struct _alternating_index_mask<EmuSIMD::i512_generic, FirstActive_, 64> :
		public _per_index_mask<EmuSIMD::i512_generic, FirstActive_, !FirstActive_, FirstActive_, !FirstActive_, FirstActive_, !FirstActive_, FirstActive_, !FirstActive_>
	{
	};
#else
	template<bool FirstActive_, std::size_t PerElementWidthIfGenericInt_>
	struct _alternating_index_mask<EmuSIMD::i8x16, FirstActive_, PerElementWidthIfGenericInt_> :
		public _per_index_mask
		<
			EmuSIMD::i8x16,
			FirstActive_, !FirstActive_, FirstActive_, !FirstActive_, FirstActive_, !FirstActive_, FirstActive_, !FirstActive_,
			FirstActive_, !FirstActive_, FirstActive_, !FirstActive_, FirstActive_, !FirstActive_, FirstActive_, !FirstActive_
		>
	{
	};

	template<bool FirstActive_, std::size_t PerElementWidthIfGenericInt_>
	struct _alternating_index_mask<EmuSIMD::i16x8, FirstActive_, PerElementWidthIfGenericInt_> :
		public _per_index_mask<EmuSIMD::i16x8, FirstActive_, !FirstActive_, FirstActive_, !FirstActive_, FirstActive_, !FirstActive_, FirstActive_, !FirstActive_>
	{
	};

	template<bool FirstActive_, std::size_t PerElementWidthIfGenericInt_>
	struct _alternating_index_mask<EmuSIMD::i32x4, FirstActive_, PerElementWidthIfGenericInt_> :
		public _per_index_mask<EmuSIMD::i32x4, FirstActive_, !FirstActive_, FirstActive_, !FirstActive_>
	{
	};

	template<bool FirstActive_, std::size_t PerElementWidthIfGenericInt_>
	struct _alternating_index_mask<EmuSIMD::i64x2, FirstActive_, PerElementWidthIfGenericInt_> :
		public _per_index_mask<EmuSIMD::i64x2, FirstActive_, !FirstActive_>
	{
	};
	
	template<bool FirstActive_, std::size_t PerElementWidthIfGenericInt_>
	struct _alternating_index_mask<EmuSIMD::i8x32, FirstActive_, PerElementWidthIfGenericInt_> :
		public _per_index_mask
		<
			EmuSIMD::i8x32,
			FirstActive_, !FirstActive_, FirstActive_, !FirstActive_, FirstActive_, !FirstActive_, FirstActive_, !FirstActive_,
			FirstActive_, !FirstActive_, FirstActive_, !FirstActive_, FirstActive_, !FirstActive_, FirstActive_, !FirstActive_,
			FirstActive_, !FirstActive_, FirstActive_, !FirstActive_, FirstActive_, !FirstActive_, FirstActive_, !FirstActive_,
			FirstActive_, !FirstActive_, FirstActive_, !FirstActive_, FirstActive_, !FirstActive_, FirstActive_, !FirstActive_
		>
	{
	};

	template<bool FirstActive_, std::size_t PerElementWidthIfGenericInt_>
	struct _alternating_index_mask<EmuSIMD::i16x16, FirstActive_, PerElementWidthIfGenericInt_> :
		public _per_index_mask
		<
			EmuSIMD::i16x16,
			FirstActive_, !FirstActive_, FirstActive_, !FirstActive_, FirstActive_, !FirstActive_, FirstActive_, !FirstActive_,
			FirstActive_, !FirstActive_, FirstActive_, !FirstActive_, FirstActive_, !FirstActive_, FirstActive_, !FirstActive_
		>
	{
	};

	template<bool FirstActive_, std::size_t PerElementWidthIfGenericInt_>
	struct _alternating_index_mask<EmuSIMD::i32x8, FirstActive_, PerElementWidthIfGenericInt_> :
		public _per_index_mask<EmuSIMD::i32x8, FirstActive_, !FirstActive_, FirstActive_, !FirstActive_, FirstActive_, !FirstActive_, FirstActive_, !FirstActive_>
	{
	};

	template<bool FirstActive_, std::size_t PerElementWidthIfGenericInt_>
	struct _alternating_index_mask<EmuSIMD::i64x4, FirstActive_, PerElementWidthIfGenericInt_> :
		public _per_index_mask<EmuSIMD::i64x4, FirstActive_, !FirstActive_, FirstActive_, !FirstActive_>
	{
	};
	
	template<bool FirstActive_, std::size_t PerElementWidthIfGenericInt_>
	struct _alternating_index_mask<EmuSIMD::i8x64, FirstActive_, PerElementWidthIfGenericInt_> :
		public _per_index_mask
		<
			EmuSIMD::i8x64,
			FirstActive_, !FirstActive_, FirstActive_, !FirstActive_, FirstActive_, !FirstActive_, FirstActive_, !FirstActive_,
			FirstActive_, !FirstActive_, FirstActive_, !FirstActive_, FirstActive_, !FirstActive_, FirstActive_, !FirstActive_,
			FirstActive_, !FirstActive_, FirstActive_, !FirstActive_, FirstActive_, !FirstActive_, FirstActive_, !FirstActive_,
			FirstActive_, !FirstActive_, FirstActive_, !FirstActive_, FirstActive_, !FirstActive_, FirstActive_, !FirstActive_,
			FirstActive_, !FirstActive_, FirstActive_, !FirstActive_, FirstActive_, !FirstActive_, FirstActive_, !FirstActive_,
			FirstActive_, !FirstActive_, FirstActive_, !FirstActive_, FirstActive_, !FirstActive_, FirstActive_, !FirstActive_,
			FirstActive_, !FirstActive_, FirstActive_, !FirstActive_, FirstActive_, !FirstActive_, FirstActive_, !FirstActive_,
			FirstActive_, !FirstActive_, FirstActive_, !FirstActive_, FirstActive_, !FirstActive_, FirstActive_, !FirstActive_
		>
	{
	};

	template<bool FirstActive_, std::size_t PerElementWidthIfGenericInt_>
	struct _alternating_index_mask<EmuSIMD::i16x32, FirstActive_, PerElementWidthIfGenericInt_> :
		public _per_index_mask
		<
			EmuSIMD::i16x32,
			FirstActive_, !FirstActive_, FirstActive_, !FirstActive_, FirstActive_, !FirstActive_, FirstActive_, !FirstActive_,
			FirstActive_, !FirstActive_, FirstActive_, !FirstActive_, FirstActive_, !FirstActive_, FirstActive_, !FirstActive_,
			FirstActive_, !FirstActive_, FirstActive_, !FirstActive_, FirstActive_, !FirstActive_, FirstActive_, !FirstActive_,
			FirstActive_, !FirstActive_, FirstActive_, !FirstActive_, FirstActive_, !FirstActive_, FirstActive_, !FirstActive_
		>
	{
	};

	template<bool FirstActive_, std::size_t PerElementWidthIfGenericInt_>
	struct _alternating_index_mask<EmuSIMD::i32x16, FirstActive_, PerElementWidthIfGenericInt_> :
		public _per_index_mask
		<
			EmuSIMD::i32x16,
			FirstActive_, !FirstActive_, FirstActive_, !FirstActive_, FirstActive_, !FirstActive_, FirstActive_, !FirstActive_,
			FirstActive_, !FirstActive_, FirstActive_, !FirstActive_, FirstActive_, !FirstActive_, FirstActive_, !FirstActive_
		>
	{
	};

	template<bool FirstActive_, std::size_t PerElementWidthIfGenericInt_>
	struct _alternating_index_mask<EmuSIMD::i64x8, FirstActive_, PerElementWidthIfGenericInt_> :
		public _per_index_mask<EmuSIMD::i64x8, FirstActive_, !FirstActive_, FirstActive_, !FirstActive_, FirstActive_, !FirstActive_, FirstActive_, !FirstActive_>
	{
	};

	template<bool FirstActive_, std::size_t PerElementWidthIfGenericInt_>
	struct _alternating_index_mask<EmuSIMD::u8x16, FirstActive_, PerElementWidthIfGenericInt_> :
		public _per_index_mask
		<
			EmuSIMD::u8x16,
			FirstActive_, !FirstActive_, FirstActive_, !FirstActive_, FirstActive_, !FirstActive_, FirstActive_, !FirstActive_,
			FirstActive_, !FirstActive_, FirstActive_, !FirstActive_, FirstActive_, !FirstActive_, FirstActive_, !FirstActive_
		>
	{
	};

	template<bool FirstActive_, std::size_t PerElementWidthIfGenericInt_>
	struct _alternating_index_mask<EmuSIMD::u16x8, FirstActive_, PerElementWidthIfGenericInt_> :
		public _per_index_mask<EmuSIMD::u16x8, FirstActive_, !FirstActive_, FirstActive_, !FirstActive_, FirstActive_, !FirstActive_, FirstActive_, !FirstActive_>
	{
	};

	template<bool FirstActive_, std::size_t PerElementWidthIfGenericInt_>
	struct _alternating_index_mask<EmuSIMD::u32x4, FirstActive_, PerElementWidthIfGenericInt_> :
		public _per_index_mask<EmuSIMD::u32x4, FirstActive_, !FirstActive_, FirstActive_, !FirstActive_>
	{
	};

	template<bool FirstActive_, std::size_t PerElementWidthIfGenericInt_>
	struct _alternating_index_mask<EmuSIMD::u64x2, FirstActive_, PerElementWidthIfGenericInt_> :
		public _per_index_mask<EmuSIMD::u64x2, FirstActive_, !FirstActive_>
	{
	};
	
	template<bool FirstActive_, std::size_t PerElementWidthIfGenericInt_>
	struct _alternating_index_mask<EmuSIMD::u8x32, FirstActive_, PerElementWidthIfGenericInt_> :
		public _per_index_mask
		<
			EmuSIMD::u8x32,
			FirstActive_, !FirstActive_, FirstActive_, !FirstActive_, FirstActive_, !FirstActive_, FirstActive_, !FirstActive_,
			FirstActive_, !FirstActive_, FirstActive_, !FirstActive_, FirstActive_, !FirstActive_, FirstActive_, !FirstActive_,
			FirstActive_, !FirstActive_, FirstActive_, !FirstActive_, FirstActive_, !FirstActive_, FirstActive_, !FirstActive_,
			FirstActive_, !FirstActive_, FirstActive_, !FirstActive_, FirstActive_, !FirstActive_, FirstActive_, !FirstActive_
		>
	{
	};

	template<bool FirstActive_, std::size_t PerElementWidthIfGenericInt_>
	struct _alternating_index_mask<EmuSIMD::u16x16, FirstActive_, PerElementWidthIfGenericInt_> :
		public _per_index_mask
		<
			EmuSIMD::u16x16,
			FirstActive_, !FirstActive_, FirstActive_, !FirstActive_, FirstActive_, !FirstActive_, FirstActive_, !FirstActive_,
			FirstActive_, !FirstActive_, FirstActive_, !FirstActive_, FirstActive_, !FirstActive_, FirstActive_, !FirstActive_
		>
	{
	};

	template<bool FirstActive_, std::size_t PerElementWidthIfGenericInt_>
	struct _alternating_index_mask<EmuSIMD::u32x8, FirstActive_, PerElementWidthIfGenericInt_> :
		public _per_index_mask<EmuSIMD::u32x8, FirstActive_, !FirstActive_, FirstActive_, !FirstActive_, FirstActive_, !FirstActive_, FirstActive_, !FirstActive_>
	{
	};

	template<bool FirstActive_, std::size_t PerElementWidthIfGenericInt_>
	struct _alternating_index_mask<EmuSIMD::u64x4, FirstActive_, PerElementWidthIfGenericInt_> :
		public _per_index_mask<EmuSIMD::u64x4, FirstActive_, !FirstActive_, FirstActive_, !FirstActive_>
	{
	};
	
	template<bool FirstActive_, std::size_t PerElementWidthIfGenericInt_>
	struct _alternating_index_mask<EmuSIMD::u8x64, FirstActive_, PerElementWidthIfGenericInt_> :
		public _per_index_mask
		<
			EmuSIMD::u8x64,
			FirstActive_, !FirstActive_, FirstActive_, !FirstActive_, FirstActive_, !FirstActive_, FirstActive_, !FirstActive_,
			FirstActive_, !FirstActive_, FirstActive_, !FirstActive_, FirstActive_, !FirstActive_, FirstActive_, !FirstActive_,
			FirstActive_, !FirstActive_, FirstActive_, !FirstActive_, FirstActive_, !FirstActive_, FirstActive_, !FirstActive_,
			FirstActive_, !FirstActive_, FirstActive_, !FirstActive_, FirstActive_, !FirstActive_, FirstActive_, !FirstActive_,
			FirstActive_, !FirstActive_, FirstActive_, !FirstActive_, FirstActive_, !FirstActive_, FirstActive_, !FirstActive_,
			FirstActive_, !FirstActive_, FirstActive_, !FirstActive_, FirstActive_, !FirstActive_, FirstActive_, !FirstActive_,
			FirstActive_, !FirstActive_, FirstActive_, !FirstActive_, FirstActive_, !FirstActive_, FirstActive_, !FirstActive_,
			FirstActive_, !FirstActive_, FirstActive_, !FirstActive_, FirstActive_, !FirstActive_, FirstActive_, !FirstActive_
		>
	{
	};

	template<bool FirstActive_, std::size_t PerElementWidthIfGenericInt_>
	struct _alternating_index_mask<EmuSIMD::u16x32, FirstActive_, PerElementWidthIfGenericInt_> :
		public _per_index_mask
		<
			EmuSIMD::u16x32,
			FirstActive_, !FirstActive_, FirstActive_, !FirstActive_, FirstActive_, !FirstActive_, FirstActive_, !FirstActive_,
			FirstActive_, !FirstActive_, FirstActive_, !FirstActive_, FirstActive_, !FirstActive_, FirstActive_, !FirstActive_,
			FirstActive_, !FirstActive_, FirstActive_, !FirstActive_, FirstActive_, !FirstActive_, FirstActive_, !FirstActive_,
			FirstActive_, !FirstActive_, FirstActive_, !FirstActive_, FirstActive_, !FirstActive_, FirstActive_, !FirstActive_
		>
	{
	};

	template<bool FirstActive_, std::size_t PerElementWidthIfGenericInt_>
	struct _alternating_index_mask<EmuSIMD::u32x16, FirstActive_, PerElementWidthIfGenericInt_> :
		public _per_index_mask
		<
			EmuSIMD::u32x16,
			FirstActive_, !FirstActive_, FirstActive_, !FirstActive_, FirstActive_, !FirstActive_, FirstActive_, !FirstActive_,
			FirstActive_, !FirstActive_, FirstActive_, !FirstActive_, FirstActive_, !FirstActive_, FirstActive_, !FirstActive_
		>
	{
	};

	template<bool FirstActive_, std::size_t PerElementWidthIfGenericInt_>
	struct _alternating_index_mask<EmuSIMD::u64x8, FirstActive_, PerElementWidthIfGenericInt_> :
		public _per_index_mask<EmuSIMD::u64x8, FirstActive_, !FirstActive_, FirstActive_, !FirstActive_, FirstActive_, !FirstActive_, FirstActive_, !FirstActive_>
	{
	};
#endif
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
