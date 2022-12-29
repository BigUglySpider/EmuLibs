#ifndef EMU_SIMD_HELPERS_TEMPLATE_INDEX_MASKS_H_INC_
#define EMU_SIMD_HELPERS_TEMPLATE_INDEX_MASKS_H_INC_ 1

#include "_underlying_template_helpers/_all_underlying_templates.h"
#include "../../../../EmuCore/TMPHelpers/Values.h"
#include "../../../../EmuCore/TMPHelpers/VariadicHelpers.h"

namespace EmuSIMD
{
	/// <summary>
	/// <para> Generator for forming a SIMD mask with true indices having all bits set to 1, and false indices having all bits set to 0. </para>
	/// <para> If you are not working generically, shorthand functions for specified registers may be found in the format index_mask_register[_ElementWidthIfIntegral]. </para>
	/// <para> In cases where the generic nature of this item is not required, it is recommended to use these explicit named functions to enforce correct arguments. </para>
	/// </summary>
	template<class Register_, bool...IsIndexActive_>
	struct index_mask
	{
	private:
		using mask_generator = _underlying_simd_helpers::_per_index_mask<Register_, IsIndexActive_...>;
		static constexpr bool _is_valid = _underlying_simd_helpers::_is_valid_per_index_mask_instance<mask_generator>::value;
		static_assert
		(
			_is_valid,
			"Attempted to form an invalid EmuSIMD::index_mask. The provided register type does not support the provided number of index arguments, or the passed Register_ type is not a supported SIMD register."
		);

	public:
		[[nodiscard]] static inline Register_ get()
		{
			if constexpr (_is_valid)
			{
				return mask_generator::get();
			}
			else
			{
				return Register_();
			}
		}
	};

	/// <summary>
	/// <para> Generator for forming a SIMD mask with the specified index's bits all set to 1, and all remaining indices' bits set to 0. </para>
	/// <para> PerElementWidthIfInt_ is used to determine how wide an element should be interpreted as (in bits) if the passed register type is integral. </para>
	/// <para> 
	///		If you are not working generically, shorthand functions for specified registers may be found in the format single_index_mask_register[_ElementWidthIfIntegral].
	/// </para>
	/// </summary>
	template<class Register_, std::size_t Index_, std::size_t PerElementWidthIfInt_ = 32>
	struct single_index_mask
	{
	private:
		using mask_generator = _underlying_simd_helpers::_single_index_mask<Register_, Index_, PerElementWidthIfInt_>;
		static constexpr bool _is_valid = _underlying_simd_helpers::_is_valid_single_index_mask_instance<mask_generator>::value;
		static_assert
		(
			_is_valid,
			"Attempted to form an invalid EmuSIMD::single_index_mask. The provided register does not support the provided Index_, or the passed Register_ type is not a supported SIMD register."
		);

	public:
		[[nodiscard]] static inline Register_ get()
		{
			if constexpr (_is_valid)
			{
				return mask_generator::get();
			}
			else
			{
				return Register_();
			}
		}
	};

	template<class Register_, bool FirstActive_, std::size_t PerElementWidthIfInt_ = 32>
	struct alternating_index_mask
	{
	private:
		using mask_generator = _underlying_simd_helpers::_alternating_index_mask<Register_, FirstActive_, PerElementWidthIfInt_>;
		static constexpr bool _is_valid = _underlying_simd_helpers::_is_valid_alternating_index_mask_instance<mask_generator>::value;
		static_assert
		(
			_is_valid,
			"Attempted to form an invalid EmuSIMD::alternating_index_mask. The provided register type is not supported, or an invalid PerElementWidth may have been provided if the register is integral."
		);

	public:
		[[nodiscard]] static inline Register_ get()
		{
			if constexpr (_is_valid)
			{
				return mask_generator::get();
			}
			else
			{
				return Register_();
			}
		}
	};

	template<class Register_, bool...IndexActive_>
	[[nodiscard]] constexpr inline auto make_index_mask(EmuCore::TMP::bool_sequence<IndexActive_...> indices_active_) noexcept
		-> typename EmuCore::TMP::remove_ref_cv<Register_>::type
	{
		return index_mask<Register_, IndexActive_...>::get();
	}

	template<class Register_, bool...IndexActive_>
	[[nodiscard]] constexpr inline auto make_index_mask() noexcept
		-> typename EmuCore::TMP::remove_ref_cv<Register_>::type
	{
		return index_mask<Register_, IndexActive_...>::get();
	}

	template<class Register_, bool...IndexActive_>
	[[nodiscard]] constexpr inline auto make_index_mask_reverse(EmuCore::TMP::bool_sequence<IndexActive_...> indices_active_) noexcept
		-> typename EmuCore::TMP::remove_ref_cv<Register_>::type
	{
		return make_index_mask<Register_>(EmuCore::TMP::make_inverted_integer_sequence<EmuCore::TMP::bool_sequence<IndexActive_...>>());
	}

	template<class Register_, bool...IndexActive_>
	[[nodiscard]] constexpr inline auto make_index_mask_reverse() noexcept
		-> typename EmuCore::TMP::remove_ref_cv<Register_>::type
	{
		return make_index_mask<Register_>(EmuCore::TMP::make_inverted_integer_sequence<EmuCore::TMP::bool_sequence<IndexActive_...>>());
	}
	
	// NOTE FOR FUNCS: Integral functions have their adaptive nature based on arguments as _per_index_mask does, but an extra subset of _width functions are provided
	// --- These functions are used to enforce safety and sanity checks when working with known size integral registers, if desired

#pragma region FUNCS_128
	template<bool AllIndices_>
	[[nodiscard]] inline EmuSIMD::f32x4 index_mask_m128()
	{
		return index_mask<EmuSIMD::f32x4, AllIndices_>::get();
	}
	template<bool I0_, bool I1_, bool I2_, bool I3_>
	[[nodiscard]] inline EmuSIMD::f32x4 index_mask_m128()
	{
		return index_mask<EmuSIMD::f32x4, I0_, I1_, I2_, I3_>::get();
	}

	template<bool AllIndices_>
	[[nodiscard]] inline EmuSIMD::f64x2 index_mask_m128d()
	{
		return index_mask<EmuSIMD::f64x2, AllIndices_>::get();
	}
	template<bool I0_, bool I1_>
	[[nodiscard]] inline EmuSIMD::f64x2 index_mask_m128d()
	{
		return index_mask<EmuSIMD::f64x2, I0_, I1_>::get();
	}

	template<bool AllIndices_>
	[[nodiscard]] inline EmuSIMD::i128_generic index_mask_m128i()
	{
		return index_mask<EmuSIMD::i128_generic, AllIndices_>;
	}
	template
	<
		bool I0_, bool I1_, bool I2_, bool I3_, bool I4_, bool I5_, bool I6_, bool I7_,
		bool I8_, bool I9_, bool I10_, bool I11_, bool I12_, bool I13_, bool I14_, bool I15_
	>
	[[nodiscard]] inline EmuSIMD::i128_generic index_mask_m128i()
	{
		return index_mask<EmuSIMD::i128_generic, I0_, I1_, I2_, I3_, I4_, I5_, I6_, I7_, I8_, I9_, I10_, I11_, I12_, I13_, I14_, I15_>::get();
	}
	template<bool I0_, bool I1_, bool I2_, bool I3_, bool I4_, bool I5_, bool I6_, bool I7_>
	[[nodiscard]] inline EmuSIMD::i128_generic index_mask_m128i()
	{
		return index_mask<EmuSIMD::i128_generic, I0_, I1_, I2_, I3_, I4_, I5_, I6_, I7_>::get();
	}
	template<bool I0_, bool I1_, bool I2_, bool I3_>
	[[nodiscard]] inline EmuSIMD::i128_generic index_mask_m128i()
	{
		return index_mask<EmuSIMD::i128_generic, I0_, I1_, I2_, I3_>::get();
	}
	template<bool I0_, bool I1_>
	[[nodiscard]] inline EmuSIMD::i128_generic index_mask_m128i()
	{
		return index_mask<EmuSIMD::i128_generic, I0_, I1_>::get();
	}

	template<bool AllIndices_>
	[[nodiscard]] inline EmuSIMD::i128_generic index_mask_m128i_8()
	{
		return index_mask<EmuSIMD::i128_generic, AllIndices_>::get();
	}
	template
	<
		bool I0_, bool I1_, bool I2_, bool I3_, bool I4_, bool I5_, bool I6_, bool I7_,
		bool I8_, bool I9_, bool I10_, bool I11_, bool I12_, bool I13_, bool I14_, bool I15_
	>
	[[nodiscard]] inline EmuSIMD::i128_generic index_mask_m128i_8()
	{
		return index_mask<EmuSIMD::i128_generic, I0_, I1_, I2_, I3_, I4_, I5_, I6_, I7_, I8_, I9_, I10_, I11_, I12_, I13_, I14_, I15_>::get();
	}

	template<bool AllIndices_>
	[[nodiscard]] inline EmuSIMD::i128_generic index_mask_m128i_16()
	{
		return index_mask<EmuSIMD::i128_generic, AllIndices_>::get();
	}
	template<bool I0_, bool I1_, bool I2_, bool I3_, bool I4_, bool I5_, bool I6_, bool I7_>
	[[nodiscard]] inline EmuSIMD::i128_generic index_mask_m128i_16()
	{
		return index_mask<EmuSIMD::i128_generic, I0_, I1_, I2_, I3_, I4_, I5_, I6_, I7_>::get();
	}

	template<bool AllIndices_>
	[[nodiscard]] inline EmuSIMD::i128_generic index_mask_m128i_32()
	{
		return index_mask<EmuSIMD::i128_generic, AllIndices_>::get();
	}
	template<bool I0_, bool I1_, bool I2_, bool I3_>
	[[nodiscard]] inline EmuSIMD::i128_generic index_mask_m128i_32()
	{
		return index_mask<EmuSIMD::i128_generic, I0_, I1_, I2_, I3_>::get();
	}

	template<bool AllIndices_>
	[[nodiscard]] inline EmuSIMD::i128_generic index_mask_m128i_64()
	{
		return index_mask<EmuSIMD::i128_generic, AllIndices_>::get();
	}
	template<bool I0_, bool I1_>
	[[nodiscard]] inline EmuSIMD::i128_generic index_mask_m128i_64()
	{
		return index_mask<EmuSIMD::i128_generic, I0_, I1_>::get();
	}

	template<std::size_t Index_>
	[[nodiscard]] inline EmuSIMD::f32x4 single_index_mask_m128()
	{
		return single_index_mask<EmuSIMD::f32x4, Index_>::get();
	}

	template<std::size_t Index_>
	[[nodiscard]] inline EmuSIMD::f64x2 single_index_mask_m128d()
	{
		return single_index_mask<EmuSIMD::f64x2, Index_>::get();
	}

	template<std::size_t Index_, std::size_t PerElementWidth_>
	[[nodiscard]] inline EmuSIMD::i128_generic single_index_mask_m128i()
	{
		if constexpr (EmuSIMD::TMP::_assert_valid_simd_int_element_width<PerElementWidth_>())
		{
			return single_index_mask<EmuSIMD::i128_generic, Index_, PerElementWidth_>::get();
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<std::size_t, Index_>(), "Provided an invalid PerElementWidth_ when calling EmuSIMD::single_index_mask_m128i.");
		}
	}

	template<std::size_t Index_>
	[[nodiscard]] inline EmuSIMD::i128_generic single_index_mask_m128i_8()
	{
		return single_index_mask<EmuSIMD::i128_generic, Index_, 8>::get();
	}

	template<std::size_t Index_>
	[[nodiscard]] inline EmuSIMD::i128_generic single_index_mask_m128i_16()
	{
		return single_index_mask<EmuSIMD::i128_generic, Index_, 16>::get();
	}

	template<std::size_t Index_>
	[[nodiscard]] inline EmuSIMD::i128_generic single_index_mask_m128i_32()
	{
		return single_index_mask<EmuSIMD::i128_generic, Index_, 32>::get();
	}

	template<std::size_t Index_>
	[[nodiscard]] inline EmuSIMD::i128_generic single_index_mask_m128i_64()
	{
		return single_index_mask<EmuSIMD::i128_generic, Index_, 64>::get();
	}

	template<bool FirstActive_>
	[[nodiscard]] inline EmuSIMD::f32x4 alternating_index_mask_m128()
	{
		return alternating_index_mask<EmuSIMD::f32x4, FirstActive_>::get();
	}

	template<bool FirstActive_>
	[[nodiscard]] inline EmuSIMD::f64x2 alternating_index_mask_m128d()
	{
		return alternating_index_mask<EmuSIMD::f64x2, FirstActive_>::get();
	}

	template<bool FirstActive_, std::size_t PerElementWidth_>
	[[nodiscard]] inline EmuSIMD::i128_generic alternating_index_mask_m128i()
	{
		if constexpr (EmuSIMD::TMP::_assert_valid_simd_int_element_width<PerElementWidth_>())
		{
			return alternating_index_mask<EmuSIMD::i128_generic, FirstActive_>::get();
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<std::size_t, PerElementWidth_>(), "Provided an invalid PerElementWidth_ when calling EmuSIMD::alternating_index_mask_m128i.");
		}
	}

	template<bool FirstActive_>
	[[nodiscard]] inline EmuSIMD::i128_generic alternating_index_mask_m128i_8()
	{
		return alternating_index_mask<EmuSIMD::i128_generic, FirstActive_, 8>::get();
	}

	template<bool FirstActive_>
	[[nodiscard]] inline EmuSIMD::i128_generic alternating_index_mask_m128i_16()
	{
		return alternating_index_mask<EmuSIMD::i128_generic, FirstActive_, 16>::get();
	}

	template<bool FirstActive_>
	[[nodiscard]] inline EmuSIMD::i128_generic alternating_index_mask_m128i_32()
	{
		return alternating_index_mask<EmuSIMD::i128_generic, FirstActive_, 32>::get();
	}

	template<bool FirstActive_>
	[[nodiscard]] inline EmuSIMD::i128_generic alternating_index_mask_m128i_64()
	{
		return alternating_index_mask<EmuSIMD::i128_generic, FirstActive_, 64>::get();
	}
#pragma endregion

#pragma region FUNCS_256
	template<bool AllIndices_>
	[[nodiscard]] inline EmuSIMD::f32x8 index_mask_m256()
	{
		return index_mask<EmuSIMD::f32x8, AllIndices_>::get();
	}
	template<bool I0_, bool I1_, bool I2_, bool I3_, bool I4_, bool I5_, bool I6_, bool I7_>
	[[nodiscard]] inline EmuSIMD::f32x8 index_mask_m256()
	{
		return index_mask<EmuSIMD::f32x8, I0_, I1_, I2_, I3_, I4_, I5_, I6_, I7_>::get();
	}

	template<bool AllIndices_>
	[[nodiscard]] inline EmuSIMD::f64x4 index_mask_m256d()
	{
		return index_mask<EmuSIMD::f64x4, AllIndices_>::get();
	}
	template<bool I0_, bool I1_, bool I2_, bool I3_>
	[[nodiscard]] inline EmuSIMD::f64x4 index_mask_m256d()
	{
		return index_mask<EmuSIMD::f64x4, I0_, I1_, I2_, I3_>::get();
	}

	template<bool AllIndices_>
	[[nodiscard]] inline EmuSIMD::i256_generic index_mask_m256i()
	{
		return index_mask<EmuSIMD::i256_generic, AllIndices_>;
	}
	template
	<
		bool I0_,  bool I1_,  bool I2_,  bool I3_,  bool I4_,  bool I5_,  bool I6_,  bool I7_,
		bool I8_,  bool I9_,  bool I10_, bool I11_, bool I12_, bool I13_, bool I14_, bool I15_,
		bool I16_, bool I17_, bool I18_, bool I19_, bool I20_, bool I21_, bool I22_, bool I23_,
		bool I24_, bool I25_, bool I26_, bool I27_, bool I28_, bool I29_, bool I30_, bool I31_
	>
	[[nodiscard]] inline EmuSIMD::i256_generic index_mask_m256i()
	{
		return index_mask
		<
			EmuSIMD::i256_generic,
			I0_,  I1_, I2_ , I3_,  I4_,  I5_,  I6_,  I7_,  I8_,  I9_,  I10_,  I11_, I12_, I13_, I14_, I15_,
			I16_, I17_, I18_, I19_, I20_, I21_, I22_, I23_, I24_, I25_, I26_, I27_, I28_, I29_, I30_, I31_
		>::get();
	}
	template
	<
		bool I0_,  bool I1_,  bool I2_,  bool I3_,  bool I4_,  bool I5_,  bool I6_,  bool I7_,
		bool I8_,  bool I9_,  bool I10_, bool I11_, bool I12_, bool I13_, bool I14_, bool I15_
	>
	[[nodiscard]] inline EmuSIMD::i256_generic index_mask_m256i()
	{
		return index_mask<EmuSIMD::i256_generic, I0_,  I1_, I2_ , I3_,  I4_,  I5_,  I6_,  I7_,  I8_,  I9_,  I10_,  I11_, I12_, I13_, I14_, I15_>::get();
	}
	template<bool I0_, bool I1_, bool I2_, bool I3_, bool I4_, bool I5_, bool I6_, bool I7_>
	[[nodiscard]] inline EmuSIMD::i256_generic index_mask_m256i()
	{
		return index_mask<EmuSIMD::i256_generic, I0_, I1_, I2_, I3_, I4_, I5_, I6_, I7_>::get();
	}
	template<bool I0_, bool I1_, bool I2_, bool I3_>
	[[nodiscard]] inline EmuSIMD::i256_generic index_mask_m256i()
	{
		return index_mask<EmuSIMD::i256_generic, I0_, I1_, I2_, I3_>::get();
	}

	template<bool AllIndices_>
	[[nodiscard]] inline EmuSIMD::i256_generic index_mask_m256i_8()
	{
		return index_mask<EmuSIMD::i256_generic, AllIndices_>::get();
	}
	template
	<
		bool I0_,  bool I1_,  bool I2_,  bool I3_,  bool I4_,  bool I5_,  bool I6_,  bool I7_,
		bool I8_,  bool I9_,  bool I10_, bool I11_, bool I12_, bool I13_, bool I14_, bool I15_,
		bool I16_, bool I17_, bool I18_, bool I19_, bool I20_, bool I21_, bool I22_, bool I23_,
		bool I24_, bool I25_, bool I26_, bool I27_, bool I28_, bool I29_, bool I30_, bool I31_
	>
	[[nodiscard]] inline EmuSIMD::i256_generic index_mask_m256i_8()
	{
		return index_mask
		<
			EmuSIMD::i256_generic,
			I0_,  I1_, I2_ , I3_,  I4_,  I5_,  I6_,  I7_,  I8_,  I9_,  I10_,  I11_, I12_, I13_, I14_, I15_,
			I16_, I17_, I18_, I19_, I20_, I21_, I22_, I23_, I24_, I25_, I26_, I27_, I28_, I29_, I30_, I31_
		>::get();
	}

	template<bool AllIndices_>
	[[nodiscard]] inline EmuSIMD::i256_generic index_mask_m256i_16()
	{
		return index_mask<EmuSIMD::i256_generic, AllIndices_>::get();
	}
	template
	<
		bool I0_,  bool I1_,  bool I2_,  bool I3_,  bool I4_,  bool I5_,  bool I6_,  bool I7_,
		bool I8_,  bool I9_,  bool I10_, bool I11_, bool I12_, bool I13_, bool I14_, bool I15_
	>
	[[nodiscard]] inline EmuSIMD::i256_generic index_mask_m256i_16()
	{
		return index_mask<EmuSIMD::i256_generic, I0_,  I1_, I2_ , I3_,  I4_,  I5_,  I6_,  I7_,  I8_,  I9_,  I10_,  I11_, I12_, I13_, I14_, I15_>::get();
	}

	template<bool AllIndices_>
	[[nodiscard]] inline EmuSIMD::i256_generic index_mask_m256i_32()
	{
		return index_mask<EmuSIMD::i256_generic, AllIndices_>::get();
	}
	template<bool I0_, bool I1_, bool I2_, bool I3_, bool I4_, bool I5_, bool I6_, bool I7_>
	[[nodiscard]] inline EmuSIMD::i256_generic index_mask_m256i_32()
	{
		return index_mask<EmuSIMD::i256_generic, I0_, I1_, I2_, I3_, I4_, I5_, I6_, I7_>::get();
	}

	template<bool AllIndices_>
	[[nodiscard]] inline EmuSIMD::i256_generic index_mask_m256i_64()
	{
		return index_mask<EmuSIMD::i256_generic, AllIndices_>::get();
	}
	template<bool I0_, bool I1_, bool I2_, bool I3_>
	[[nodiscard]] inline EmuSIMD::i256_generic index_mask_m256i_64()
	{
		return index_mask<EmuSIMD::i256_generic, I0_, I1_, I2_, I3_>::get();
	}

	template<std::size_t Index_>
	[[nodiscard]] inline EmuSIMD::f32x8 single_index_mask_m256()
	{
		return single_index_mask<EmuSIMD::f32x8, Index_>::get();
	}

	template<std::size_t Index_>
	[[nodiscard]] inline EmuSIMD::f64x4 single_index_mask_m256d()
	{
		return single_index_mask<EmuSIMD::f64x4, Index_>::get();
	}

	template<std::size_t Index_, std::size_t PerElementWidth_>
	[[nodiscard]] inline EmuSIMD::i256_generic single_index_mask_m256i()
	{
		if constexpr (EmuSIMD::TMP::_assert_valid_simd_int_element_width<PerElementWidth_>())
		{
			return single_index_mask<EmuSIMD::i256_generic, Index_, PerElementWidth_>::get();
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<std::size_t, PerElementWidth_>(), "Provided an invalid PerElementWidth_ when calling EmuSIMD::single_index_mask_m256i.");
		}
	}

	template<std::size_t Index_>
	[[nodiscard]] inline EmuSIMD::i256_generic single_index_mask_m256i_8()
	{
		return single_index_mask<EmuSIMD::i256_generic, Index_, 8>::get();
	}

	template<std::size_t Index_>
	[[nodiscard]] inline EmuSIMD::i256_generic single_index_mask_m256i_16()
	{
		return single_index_mask<EmuSIMD::i256_generic, Index_, 16>::get();
	}

	template<std::size_t Index_>
	[[nodiscard]] inline EmuSIMD::i256_generic single_index_mask_m256i_32()
	{
		return single_index_mask<EmuSIMD::i256_generic, Index_, 32>::get();
	}

	template<std::size_t Index_>
	[[nodiscard]] inline EmuSIMD::i256_generic single_index_mask_m256i_64()
	{
		return single_index_mask<EmuSIMD::i256_generic, Index_, 64>::get();
	}

	template<bool FirstActive_>
	[[nodiscard]] inline EmuSIMD::f32x8 alternating_index_mask_m256()
	{
		return alternating_index_mask<EmuSIMD::f32x8, FirstActive_>::get();
	}

	template<bool FirstActive_>
	[[nodiscard]] inline EmuSIMD::f64x4 alternating_index_mask_m256d()
	{
		return alternating_index_mask<EmuSIMD::f64x4, FirstActive_>::get();
	}

	template<bool FirstActive_, std::size_t PerElementWidth_>
	[[nodiscard]] inline EmuSIMD::i256_generic alternating_index_mask_m256i()
	{
		if constexpr (EmuSIMD::TMP::_assert_valid_simd_int_element_width<PerElementWidth_>())
		{
			return alternating_index_mask<EmuSIMD::i256_generic, FirstActive_>::get();
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<std::size_t, PerElementWidth_>(), "Provided an invalid PerElementWidth_ when calling EmuSIMD::alternating_index_mask_m256i.");
		}
	}

	template<bool FirstActive_>
	[[nodiscard]] inline EmuSIMD::i256_generic alternating_index_mask_m256i_8()
	{
		return alternating_index_mask<EmuSIMD::i256_generic, FirstActive_, 8>::get();
	}

	template<bool FirstActive_>
	[[nodiscard]] inline EmuSIMD::i256_generic alternating_index_mask_m256i_16()
	{
		return alternating_index_mask<EmuSIMD::i256_generic, FirstActive_, 16>::get();
	}

	template<bool FirstActive_>
	[[nodiscard]] inline EmuSIMD::i256_generic alternating_index_mask_m256i_32()
	{
		return alternating_index_mask<EmuSIMD::i256_generic, FirstActive_, 32>::get();
	}

	template<bool FirstActive_>
	[[nodiscard]] inline EmuSIMD::i256_generic alternating_index_mask_m256i_64()
	{
		return alternating_index_mask<EmuSIMD::i256_generic, FirstActive_, 64>::get();
	}
#pragma endregion

#pragma region FUNCS_512
	template<bool AllIndices_>
	[[nodiscard]] inline EmuSIMD::f32x16 index_mask_m512()
	{
		return index_mask<EmuSIMD::f32x16, AllIndices_>::get();
	}
	template
	<
		bool I0_, bool I1_, bool I2_,  bool I3_,  bool I4_,  bool I5_,  bool I6_,  bool I7_,
		bool I8_, bool I9_, bool I10_, bool I11_, bool I12_, bool I13_, bool I14_, bool I15_
	>
	[[nodiscard]] inline EmuSIMD::f32x16 index_mask_m256()
	{
		return index_mask<EmuSIMD::f32x16, I0_, I1_, I2_, I3_, I4_, I5_, I6_, I7_, I8_, I9_, I10_, I11_, I12_, I13_, I14_, I15_>::get();
	}

	template<bool AllIndices_>
	[[nodiscard]] inline EmuSIMD::f64x8 index_mask_m512d()
	{
		return index_mask<EmuSIMD::f64x8, AllIndices_>::get();
	}
	template<bool I0_, bool I1_, bool I2_, bool I3_, bool I4_, bool I5_, bool I6_, bool I7_>
	[[nodiscard]] inline EmuSIMD::f64x8 index_mask_m512d()
	{
		return index_mask<EmuSIMD::f64x8, I0_, I1_, I2_, I3_, I4_, I5_, I6_, I7_>::get();
	}

	template<bool AllIndices_>
	[[nodiscard]] inline EmuSIMD::i512_generic index_mask_m512i()
	{
		return index_mask<EmuSIMD::i512_generic, AllIndices_>;
	}
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
	[[nodiscard]] inline EmuSIMD::i512_generic index_mask_m512i()
	{
		return index_mask
		<
			EmuSIMD::i512_generic,
			I0_,  I1_,  I2_ , I3_,  I4_,  I5_,  I6_,  I7_,  I8_,  I9_,  I10_, I11_, I12_, I13_, I14_, I15_,
			I16_, I17_, I18_, I19_, I20_, I21_, I22_, I23_, I24_, I25_, I26_, I27_, I28_, I29_, I30_, I31_,
			I32_, I33_, I34_, I35_, I36_, I37_, I38_, I39_, I40_, I41_, I42_, I43_, I44_, I45_, I46_, I47_,
			I48_, I49_, I50_, I51_, I52_, I53_, I54_, I55_, I56_, I57_, I58_, I59_, I60_, I61_, I62_, I63_
		>::get();
	}
	template
	<
		bool I0_,  bool I1_,  bool I2_,  bool I3_,  bool I4_,  bool I5_,  bool I6_,  bool I7_,
		bool I8_,  bool I9_,  bool I10_, bool I11_, bool I12_, bool I13_, bool I14_, bool I15_,
		bool I16_, bool I17_, bool I18_, bool I19_, bool I20_, bool I21_, bool I22_, bool I23_,
		bool I24_, bool I25_, bool I26_, bool I27_, bool I28_, bool I29_, bool I30_, bool I31_
	>
	[[nodiscard]] inline EmuSIMD::i512_generic index_mask_m512i()
	{
		return index_mask
		<
			EmuSIMD::i512_generic,
			I0_,  I1_,  I2_ , I3_,  I4_,  I5_,  I6_,  I7_,  I8_,  I9_,  I10_, I11_, I12_, I13_, I14_, I15_,
			I16_, I17_, I18_, I19_, I20_, I21_, I22_, I23_, I24_, I25_, I26_, I27_, I28_, I29_, I30_, I31_
		>::get();
	}
	template
	<
		bool I0_,  bool I1_,  bool I2_,  bool I3_,  bool I4_,  bool I5_,  bool I6_,  bool I7_,
		bool I8_,  bool I9_,  bool I10_, bool I11_, bool I12_, bool I13_, bool I14_, bool I15_
	>
	[[nodiscard]] inline EmuSIMD::i512_generic index_mask_m512i()
	{
		return index_mask<EmuSIMD::i512_generic, I0_,  I1_, I2_ , I3_,  I4_,  I5_,  I6_,  I7_,  I8_,  I9_,  I10_,  I11_, I12_, I13_, I14_, I15_>::get();
	}
	template<bool I0_, bool I1_, bool I2_, bool I3_, bool I4_, bool I5_, bool I6_, bool I7_>
	[[nodiscard]] inline EmuSIMD::i512_generic index_mask_m512i()
	{
		return index_mask<EmuSIMD::i512_generic, I0_, I1_, I2_, I3_, I4_, I5_, I6_, I7_>::get();
	}

	template<bool AllIndices_>
	[[nodiscard]] inline EmuSIMD::i512_generic index_mask_m512i_8()
	{
		return index_mask<EmuSIMD::i512_generic, AllIndices_>::get();
	}
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
	[[nodiscard]] inline EmuSIMD::i512_generic index_mask_m512i_8()
	{
		return index_mask
		<
			EmuSIMD::i512_generic,
			I0_,  I1_,  I2_ , I3_,  I4_,  I5_,  I6_,  I7_,  I8_,  I9_,  I10_, I11_, I12_, I13_, I14_, I15_,
			I16_, I17_, I18_, I19_, I20_, I21_, I22_, I23_, I24_, I25_, I26_, I27_, I28_, I29_, I30_, I31_,
			I32_, I33_, I34_, I35_, I36_, I37_, I38_, I39_, I40_, I41_, I42_, I43_, I44_, I45_, I46_, I47_,
			I48_, I49_, I50_, I51_, I52_, I53_, I54_, I55_, I56_, I57_, I58_, I59_, I60_, I61_, I62_, I63_
		>::get();
	}

	template<bool AllIndices_>
	[[nodiscard]] inline EmuSIMD::i512_generic index_mask_m512i_16()
	{
		return index_mask<EmuSIMD::i512_generic, AllIndices_>::get();
	}
	template
	<
		bool I0_,  bool I1_,  bool I2_,  bool I3_,  bool I4_,  bool I5_,  bool I6_,  bool I7_,
		bool I8_,  bool I9_,  bool I10_, bool I11_, bool I12_, bool I13_, bool I14_, bool I15_,
		bool I16_, bool I17_, bool I18_, bool I19_, bool I20_, bool I21_, bool I22_, bool I23_,
		bool I24_, bool I25_, bool I26_, bool I27_, bool I28_, bool I29_, bool I30_, bool I31_
	>
	[[nodiscard]] inline EmuSIMD::i512_generic index_mask_m512i_16()
	{
		return index_mask
		<
			EmuSIMD::i512_generic,
			I0_,  I1_,  I2_ , I3_,  I4_,  I5_,  I6_,  I7_,  I8_,  I9_,  I10_, I11_, I12_, I13_, I14_, I15_,
			I16_, I17_, I18_, I19_, I20_, I21_, I22_, I23_, I24_, I25_, I26_, I27_, I28_, I29_, I30_, I31_
		>::get();
	}

	template<bool AllIndices_>
	[[nodiscard]] inline EmuSIMD::i512_generic index_mask_m512i_32()
	{
		return index_mask<EmuSIMD::i512_generic, AllIndices_>::get();
	}
	template
	<
		bool I0_,  bool I1_,  bool I2_,  bool I3_,  bool I4_,  bool I5_,  bool I6_,  bool I7_,
		bool I8_,  bool I9_,  bool I10_, bool I11_, bool I12_, bool I13_, bool I14_, bool I15_
	>
	[[nodiscard]] inline EmuSIMD::i512_generic index_mask_m512i_32()
	{
		return index_mask<EmuSIMD::i512_generic, I0_,  I1_, I2_ , I3_,  I4_,  I5_,  I6_,  I7_,  I8_,  I9_,  I10_,  I11_, I12_, I13_, I14_, I15_>::get();
	}

	template<bool AllIndices_>
	[[nodiscard]] inline EmuSIMD::i512_generic index_mask_m512i_64()
	{
		return index_mask<EmuSIMD::i512_generic, AllIndices_>::get();
	}
	template<bool I0_, bool I1_, bool I2_, bool I3_, bool I4_, bool I5_, bool I6_, bool I7_>
	[[nodiscard]] inline EmuSIMD::i512_generic index_mask_m512i_64()
	{
		return index_mask<EmuSIMD::i512_generic, I0_, I1_, I2_, I3_, I4_, I5_, I6_, I7_>::get();
	}

	template<std::size_t Index_>
	[[nodiscard]] inline EmuSIMD::f32x16 single_index_mask_m512()
	{
		return single_index_mask<EmuSIMD::f32x16, Index_>::get();
	}

	template<std::size_t Index_>
	[[nodiscard]] inline EmuSIMD::f64x8 single_index_mask_m512d()
	{
		return single_index_mask<EmuSIMD::f64x8, Index_>::get();
	}

	template<std::size_t Index_, std::size_t PerElementWidth_>
	[[nodiscard]] inline EmuSIMD::i512_generic single_index_mask_m512i()
	{
		if constexpr (EmuSIMD::TMP::_assert_valid_simd_int_element_width<PerElementWidth_>())
		{
			return single_index_mask<EmuSIMD::i512_generic, Index_, PerElementWidth_>::get();
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<std::size_t, PerElementWidth_>(), "Provided an invalid PerElementWidth_ when calling EmuSIMD::single_index_mask_m512i.");
		}
	}

	template<std::size_t Index_>
	[[nodiscard]] inline EmuSIMD::i512_generic single_index_mask_m512i_8()
	{
		return single_index_mask<EmuSIMD::i512_generic, Index_, 8>::get();
	}

	template<std::size_t Index_>
	[[nodiscard]] inline EmuSIMD::i512_generic single_index_mask_m512i_16()
	{
		return single_index_mask<EmuSIMD::i512_generic, Index_, 16>::get();
	}

	template<std::size_t Index_>
	[[nodiscard]] inline EmuSIMD::i512_generic single_index_mask_m512i_32()
	{
		return single_index_mask<EmuSIMD::i512_generic, Index_, 32>::get();
	}

	template<std::size_t Index_>
	[[nodiscard]] inline EmuSIMD::i512_generic single_index_mask_m512i_64()
	{
		return single_index_mask<EmuSIMD::i512_generic, Index_, 64>::get();
	}



	template<bool FirstActive_>
	[[nodiscard]] inline EmuSIMD::f32x16 alternating_index_mask_m512()
	{
		return alternating_index_mask<EmuSIMD::f32x16, FirstActive_>::get();
	}

	template<bool FirstActive_>
	[[nodiscard]] inline EmuSIMD::f64x8 alternating_index_mask_m512d()
	{
		return alternating_index_mask<EmuSIMD::f64x8, FirstActive_>::get();
	}

	template<bool FirstActive_, std::size_t PerElementWidth_>
	[[nodiscard]] inline EmuSIMD::i512_generic alternating_index_mask_m512i()
	{
		if constexpr (EmuSIMD::TMP::_assert_valid_simd_int_element_width<PerElementWidth_>())
		{
			return alternating_index_mask<EmuSIMD::i512_generic, FirstActive_>::get();
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<std::size_t, PerElementWidth_>(), "Provided an invalid PerElementWidth_ when calling EmuSIMD::alternating_index_mask_m512i.");
		}
	}

	template<bool FirstActive_>
	[[nodiscard]] inline EmuSIMD::i512_generic alternating_index_mask_m512i_8()
	{
		return alternating_index_mask<EmuSIMD::i512_generic, FirstActive_, 8>::get();
	}

	template<bool FirstActive_>
	[[nodiscard]] inline EmuSIMD::i512_generic alternating_index_mask_m512i_16()
	{
		return alternating_index_mask<EmuSIMD::i512_generic, FirstActive_, 16>::get();
	}

	template<bool FirstActive_>
	[[nodiscard]] inline EmuSIMD::i512_generic alternating_index_mask_m512i_32()
	{
		return alternating_index_mask<EmuSIMD::i512_generic, FirstActive_, 32>::get();
	}

	template<bool FirstActive_>
	[[nodiscard]] inline EmuSIMD::i512_generic alternating_index_mask_m512i_64()
	{
		return alternating_index_mask<EmuSIMD::i512_generic, FirstActive_, 64>::get();
	}
#pragma endregion
}

#endif
