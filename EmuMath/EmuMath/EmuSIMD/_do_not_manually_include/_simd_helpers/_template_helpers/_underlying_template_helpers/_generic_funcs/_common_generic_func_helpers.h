#ifndef EMU_SIMD_COMMON_GENERIC_FUNC_HELPERS_H_INC_
#define EMU_SIMD_COMMON_GENERIC_FUNC_HELPERS_H_INC_ 1

#include "../_simd_helpers_underlying_aliases.h"
#include "../../../../../../EmuCore/ArithmeticHelpers/BitHelpers.h"
#include "../../../../../../EmuCore/ArithmeticHelpers/CommonMath.h"
#include "../../../../../../EmuCore/CommonPreprocessor/All.h"
#include "../../../../../../EmuCore/TMPHelpers/TypeConvertors.h"
#include "../../../../../../EmuCore/TMPHelpers/Values.h"
#include "../../../../../../EmuCore/TMPHelpers/VariadicHelpers.h"

#include <bit>
#include <cstdint>
#include <immintrin.h>
#include <utility>

/// <summary>
/// <para> Specifiers used by most - if not all - common functions defined within the EmuSIMD::Funcs namespace. </para>
/// </summary>
#define EMU_SIMD_COMMON_FUNC_SPEC inline

// Flag used to identify a cmpeq comparison (==)
#define EMU_SIMD_CMP_EQ_FLAG _CMP_EQ_OS
// Flag used to identify a cmpneq comparison (!=)
#define EMU_SIMD_CMP_NEQ_FLAG _CMP_NEQ_OS
// Flag used to identify a cmpgt comparison (>)
#define EMU_SIMD_CMP_GT_FLAG _CMP_GT_OS
// Flag used to identify a cmplt comparison (<)
#define EMU_SIMD_CMP_LT_FLAG _CMP_LT_OS
// Flag used to identify a cmpge comparison (>=)
#define EMU_SIMD_CMP_GE_FLAG _CMP_GE_OS
// Flag used to identify a cmple comparison (<-)
#define EMU_SIMD_CMP_LE_FLAG _CMP_LE_OS

// Flag used to identify a floor round (toward negative infinity)
#define EMU_SIMD_FLAG_FLOOR	_MM_FROUND_FLOOR
// Flag used to identify a ceil round (toward positive infinity)
#define EMU_SIMD_FLAG_CEIL	_MM_FROUND_CEIL
// Flag used to identify a trunc round (toward 0)
#define EMU_SIMD_FLAG_TRUNC	_MM_FROUND_TRUNC

namespace EmuSIMD::Funcs
{
	/// <summary>
	/// <para> Type used as a template argument for basic shuffle masks with EmuSIMD's underlying functions. </para>
	/// <para> Guaranteed to be 64-bit. </para>
	/// </summary>
	using shuffle_mask_type = std::uint64_t;

	/// <summary>
	/// <para> Duplicates one of the 32-bit lanes from the 64-bit ShuffleMask_ and places it in the other lane. </para>
	/// <para> If `HiLane_` is `true`, the hi lane will be duplicated into the lo lane; otherwise, the lo lane will be duplicated into the hi lane. </para>
	/// </summary>
	/// <returns>The passed ShuffleMask_ with the designated lane duplicated to replace the other lane.</returns>
	template<shuffle_mask_type ShuffleMask_, bool HiLane_>
	[[nodiscard]] constexpr inline shuffle_mask_type duplicate_shuffle_mask_32bit_lane()
	{
		if constexpr (HiLane_)
		{
			constexpr shuffle_mask_type hi_as_lo = ShuffleMask_ >> 32;
			constexpr shuffle_mask_type hi_only = hi_as_lo << 32;
			return hi_as_lo | hi_only;
		}
		else
		{
			constexpr shuffle_mask_type lo_as_hi = ShuffleMask_ << 32;
			constexpr shuffle_mask_type lo_only = lo_as_hi >> 32;
			return lo_as_hi | lo_only;
		}
	}

	namespace _underlying_funcs
	{
		template<std::size_t PerIndexWidth_, shuffle_mask_type...IndexArgs_, std::size_t...Indices_>
		[[nodiscard]] constexpr inline shuffle_mask_type _create_generic_shuffle_mask(std::integer_sequence<shuffle_mask_type, IndexArgs_...> index_args_, std::index_sequence<Indices_...> indices_)
		{
			constexpr std::size_t num_index_args = sizeof...(IndexArgs_);
			constexpr std::size_t end_index_shift = (PerIndexWidth_ * num_index_args) - PerIndexWidth_;

			return (shuffle_mask_type(0) | ... | (IndexArgs_ << (end_index_shift - (PerIndexWidth_ * Indices_))));
		}

		template<shuffle_mask_type Index_, std::size_t NumIndices_, std::size_t BitsPerShuffleIndex_>
		[[nodiscard]] constexpr inline shuffle_mask_type _create_generic_looping_shuffle_mask()
		{
			return _create_generic_shuffle_mask<BitsPerShuffleIndex_>
			(
				EmuCore::TMP::make_looped_integer_sequence<std::index_sequence<Index_>, NumIndices_ - 1>(),
				std::make_index_sequence<NumIndices_>()
			);
		}
	}

	/// <summary>
	/// <para> Creates a shuffle mask for a 64-bit-element SIMD register with the same semantics as the x86/x64 _MM_SHUFFLE2 macro. </para>
	/// </summary>
	/// <returns>Shuffle mask that would result from a call to _MM_SHUFFLE2(I0_, I1_) when building under x86/x64.</returns>
	template<shuffle_mask_type I0_, shuffle_mask_type I1_>
	[[nodiscard]] constexpr inline shuffle_mask_type make_shuffle_mask_64()
	{
		return _underlying_funcs::_create_generic_shuffle_mask<1>
		(
			std::integer_sequence<shuffle_mask_type, I0_, I1_>(),
			std::make_index_sequence<2>()
		);
	}

	template<shuffle_mask_type I0_, shuffle_mask_type I1_>
	[[nodiscard]] constexpr inline shuffle_mask_type make_shuffle_mask_64x2()
	{
		return _underlying_funcs::_create_generic_shuffle_mask<1>
		(
			std::integer_sequence<shuffle_mask_type, I0_, I1_>(),
			std::make_index_sequence<2>()
		);
	}

	/// <summary>
	/// <para> Creates a reversed shuffle mask for a 64-bit-element SIMD register with the same semantics as the x86/x64 _MM_SHUFFLE2 macro. </para>
	/// </summary>
	/// <returns>Shuffle mask that would result from a call to _MM_SHUFFLE2(I1_, I0_) when building under x86/x64.</returns>
	template<shuffle_mask_type I0_, shuffle_mask_type I1_>
	[[nodiscard]] constexpr inline shuffle_mask_type make_reverse_shuffle_mask_64()
	{
		return _underlying_funcs::_create_generic_shuffle_mask<1>
		(
			std::integer_sequence<shuffle_mask_type, I1_, I0_>(),
			std::make_index_sequence<2>()
		);
	}

	template<shuffle_mask_type I0_, shuffle_mask_type I1_>
	[[nodiscard]] constexpr inline shuffle_mask_type make_reverse_shuffle_mask_64x2()
	{
		return _underlying_funcs::_create_generic_shuffle_mask<1>
		(
			std::integer_sequence<shuffle_mask_type, I1_, I0_>(),
			std::make_index_sequence<2>()
		);
	}

	template<shuffle_mask_type I0_, shuffle_mask_type I1_, shuffle_mask_type I2_, shuffle_mask_type I3_>
	[[nodiscard]] constexpr inline shuffle_mask_type make_shuffle_mask_64()
	{
		return _underlying_funcs::_create_generic_shuffle_mask<1>
		(
			std::integer_sequence<shuffle_mask_type, I0_, I1_, I2_, I3_>(),
			std::make_index_sequence<4>()
		);
	}

	template<shuffle_mask_type I0_, shuffle_mask_type I1_>
	[[nodiscard]] constexpr inline shuffle_mask_type make_shuffle_mask_64x4()
	{
		return _underlying_funcs::_create_generic_shuffle_mask<1>
		(
			std::integer_sequence<shuffle_mask_type, I0_, I1_, I0_, I1_>(),
			std::make_index_sequence<4>()
		);
	}

	template<shuffle_mask_type I0_, shuffle_mask_type I1_, shuffle_mask_type I2_, shuffle_mask_type I3_>
	[[nodiscard]] constexpr inline shuffle_mask_type make_reverse_shuffle_mask_64()
	{
		return _underlying_funcs::_create_generic_shuffle_mask<1>
		(
			std::integer_sequence<shuffle_mask_type, I3_, I2_, I1_, I0_>(),
			std::make_index_sequence<4>()
		);
	}

	template<shuffle_mask_type I0_, shuffle_mask_type I1_>
	[[nodiscard]] constexpr inline shuffle_mask_type make_reverse_shuffle_mask_64x4()
	{
		return _underlying_funcs::_create_generic_shuffle_mask<1>
		(
			std::integer_sequence<shuffle_mask_type, I1_, I0_, I1_, I0_>(),
			std::make_index_sequence<4>()
		);
	}

	template<shuffle_mask_type I0_, shuffle_mask_type I1_, shuffle_mask_type I2_, shuffle_mask_type I3_, shuffle_mask_type I4_, shuffle_mask_type I5_, shuffle_mask_type I6_, shuffle_mask_type I7_>
	[[nodiscard]] constexpr inline shuffle_mask_type make_shuffle_mask_64()
	{
		return _underlying_funcs::_create_generic_shuffle_mask<1>
		(
			std::integer_sequence<shuffle_mask_type, I0_, I1_, I2_, I3_, I4_, I5_, I6_, I7_>(),
			std::make_index_sequence<8>()
		);
	}

	template<shuffle_mask_type I0_, shuffle_mask_type I1_>
	[[nodiscard]] constexpr inline shuffle_mask_type make_shuffle_mask_64x8()
	{
		return _underlying_funcs::_create_generic_shuffle_mask<1>
		(
			std::integer_sequence<shuffle_mask_type, I0_, I1_, I0_, I1_, I0_, I1_, I0_, I1_>(),
			std::make_index_sequence<8>()
		);
	}

	template<shuffle_mask_type I0_, shuffle_mask_type I1_, shuffle_mask_type I2_, shuffle_mask_type I3_, shuffle_mask_type I4_, shuffle_mask_type I5_, shuffle_mask_type I6_, shuffle_mask_type I7_>
	[[nodiscard]] constexpr inline shuffle_mask_type make_reverse_shuffle_mask_64()
	{
		return _underlying_funcs::_create_generic_shuffle_mask<1>
		(
			std::integer_sequence<shuffle_mask_type, I7_, I6_, I5_, I4_, I3_, I2_, I1_, I0_>(),
			std::make_index_sequence<8>()
		);
	}

	template<shuffle_mask_type I0_, shuffle_mask_type I1_>
	[[nodiscard]] constexpr inline shuffle_mask_type make_reverse_shuffle_mask_64x8()
	{
		return _underlying_funcs::_create_generic_shuffle_mask<1>
		(
			std::integer_sequence<shuffle_mask_type, I1_, I0_, I1_, I0_, I1_, I0_, I1_, I0_>(),
			std::make_index_sequence<8>()
		);
	}

	template<shuffle_mask_type Index_>
	[[nodiscard]] constexpr inline shuffle_mask_type make_looping_shuffle_mask_64x2()
	{
		return _underlying_funcs::_create_generic_looping_shuffle_mask<Index_, 2, 1>();
	}

	template<shuffle_mask_type Index_>
	[[nodiscard]] constexpr inline shuffle_mask_type make_looping_shuffle_mask_64x4()
	{
		return _underlying_funcs::_create_generic_looping_shuffle_mask<Index_, 4, 1>();
	}

	template<shuffle_mask_type Index_>
	[[nodiscard]] constexpr inline shuffle_mask_type make_looping_shuffle_mask_64x8()
	{
		return _underlying_funcs::_create_generic_looping_shuffle_mask<Index_, 8, 1>();
	}

	/// <summary>
	/// <para> Creates a shuffle mask for a 32-bit-element SIMD register with the same semantics as the x86/x64 _MM_SHUFFLE macro. </para>
	/// </summary>
	/// <returns>Shuffle mask that would result from a call to _MM_SHUFFLE(I0_, I1_, I2_, I3_) when building under x86/x64.</returns>
	template<shuffle_mask_type I0_, shuffle_mask_type I1_, shuffle_mask_type I2_, shuffle_mask_type I3_>
	[[nodiscard]] constexpr inline shuffle_mask_type make_shuffle_mask_32()
	{
		return _underlying_funcs::_create_generic_shuffle_mask<2>
		(
			std::integer_sequence<shuffle_mask_type, I0_, I1_, I2_, I3_>(),
			std::make_index_sequence<4>()
		);
	}

	/// <summary>
	/// <para> Creates a reversed shuffle mask for a 32-bit-element SIMD register with the same semantics as the x86/x64 _MM_SHUFFLE macro. </para>
	/// </summary>
	/// <returns>Shuffle mask that would result from a call to _MM_SHUFFLE(I3_, I2_, I1_, I0_) when building under x86/x64.</returns>
	template<shuffle_mask_type I0_, shuffle_mask_type I1_, shuffle_mask_type I2_, shuffle_mask_type I3_>
	[[nodiscard]] constexpr inline shuffle_mask_type make_reverse_shuffle_mask_32()
	{
		return _underlying_funcs::_create_generic_shuffle_mask<2>
		(
			std::integer_sequence<shuffle_mask_type, I3_, I2_, I1_, I0_>(),
			std::make_index_sequence<4>()
		);
	}

	template<shuffle_mask_type Index_>
	[[nodiscard]] constexpr inline shuffle_mask_type make_looping_shuffle_mask_32x4()
	{
		return _underlying_funcs::_create_generic_looping_shuffle_mask<Index_, 4, 2>();
	}

	template
	<
		shuffle_mask_type I0_,  shuffle_mask_type I1_,  shuffle_mask_type I2_,  shuffle_mask_type I3_,
		shuffle_mask_type I4_,  shuffle_mask_type I5_,  shuffle_mask_type I6_,  shuffle_mask_type I7_,
		shuffle_mask_type I8_,  shuffle_mask_type I9_,  shuffle_mask_type I10_, shuffle_mask_type I11_,
		shuffle_mask_type I12_, shuffle_mask_type I13_, shuffle_mask_type I14_, shuffle_mask_type I15_
	>
		[[nodiscard]] constexpr inline shuffle_mask_type make_shuffle_mask_8()
	{
		return _underlying_funcs::_create_generic_shuffle_mask<4>
		(
			std::integer_sequence<shuffle_mask_type, I0_, I1_, I2_, I3_, I4_, I5_, I6_, I7_, I8_, I9_, I10_, I11_, I12_, I13_, I14_, I15_>(),
			std::make_index_sequence<16>()
		);
	}

	template<shuffle_mask_type Index_>
	[[nodiscard]] constexpr inline shuffle_mask_type make_looping_shuffle_mask_8x16()
	{
		return _underlying_funcs::_create_generic_looping_shuffle_mask<Index_, 16, 4>();
	}

	template
	<
		shuffle_mask_type I0_,  shuffle_mask_type I1_,  shuffle_mask_type I2_,  shuffle_mask_type I3_,
		shuffle_mask_type I4_,  shuffle_mask_type I5_,  shuffle_mask_type I6_,  shuffle_mask_type I7_,
		shuffle_mask_type I8_,  shuffle_mask_type I9_,  shuffle_mask_type I10_, shuffle_mask_type I11_,
		shuffle_mask_type I12_, shuffle_mask_type I13_, shuffle_mask_type I14_, shuffle_mask_type I15_
	>
		[[nodiscard]] constexpr inline shuffle_mask_type make_reverse_shuffle_mask_8()
	{
		return _underlying_funcs::_create_generic_shuffle_mask<4>
		(
			std::integer_sequence<shuffle_mask_type, I15_, I14_, I13_, I12_, I11_, I10_, I9_, I8_, I7_, I6_, I5_, I4_, I3_, I2_, I1_, I0_>(),
			std::make_index_sequence<16>()
		);
	}

	namespace _underlying_funcs
	{
		template<shuffle_mask_type ShuffleMask, bool Reverse_, std::size_t ArgumentWidth_, std::size_t IndicesPerLane_, typename TargetType_, std::size_t...LoopedIndices_, class SettingFunc_>
		[[nodiscard]] constexpr inline decltype(auto) _shuffle_mask_to_vector(std::index_sequence<LoopedIndices_...> looped_indices_, SettingFunc_&& setter_) noexcept
		{
			constexpr shuffle_mask_type all_element_bits = (shuffle_mask_type(1) << ArgumentWidth_) - 1;

			if constexpr (Reverse_)
			{
				return std::forward<SettingFunc_>(setter_)
				(
					std::integral_constant<TargetType_, static_cast<TargetType_>((ShuffleMask >> (ArgumentWidth_ * LoopedIndices_)) & all_element_bits)>::value...
				);
			}
			else
			{
				constexpr std::size_t final_index = IndicesPerLane_ - 1;
				return std::forward<SettingFunc_>(setter_)
				(
					std::integral_constant<TargetType_, static_cast<TargetType_>((ShuffleMask >> (ArgumentWidth_ * (final_index - LoopedIndices_)))) & all_element_bits>::value...
				);
			}
		}
	}

	template<shuffle_mask_type ShuffleMask, bool Reverse_, std::size_t ArgumentWidth_, std::size_t Num128Lanes_, typename TargetType_, std::size_t...SingleLaneIndices_, class SettingFunc_>
	[[nodiscard]] constexpr inline decltype(auto) shuffle_mask_to_vector(std::index_sequence<SingleLaneIndices_...> indices_, SettingFunc_&& setter_) noexcept
	{
		constexpr std::size_t num_indices_per_lane = sizeof...(SingleLaneIndices_);
		static_assert
		(
			(num_indices_per_lane * ArgumentWidth_) <= (sizeof(shuffle_mask_type) * 8),
			"Error with EmuSIMD::Funcs::shuffle_mask_to_vector: The number of indices per lane multiplied by the width for an individual argument is greater than the width of the shuffle_mask_type, meaning all indices cannot be accounted for within a 128-bit lane."
		);

		if constexpr (Num128Lanes_ <= 1)
		{
			return _underlying_funcs::_shuffle_mask_to_vector<ShuffleMask, Reverse_, ArgumentWidth_, num_indices_per_lane, TargetType_>(std::index_sequence<SingleLaneIndices_...>(), std::forward<SettingFunc_>(setter_));
		}
		else
		{
			using looping_indices = EmuCore::TMP::make_looped_integer_sequence<std::index_sequence<SingleLaneIndices_...>, Num128Lanes_ - 1>;
			return _underlying_funcs::_shuffle_mask_to_vector<ShuffleMask, Reverse_, ArgumentWidth_, num_indices_per_lane, TargetType_>(looping_indices(), std::forward<SettingFunc_>(setter_));
		}
	}

	using blend_mask_type = std::uint64_t;

	namespace _underlying_funcs
	{
		template<bool ThisBit_, std::size_t Pos_>
		[[nodiscard]] constexpr inline blend_mask_type _shift_blend_mask_bit()
		{
			return static_cast<blend_mask_type>(ThisBit_) << Pos_;
		}

		template<bool...Bits_, std::size_t...Indices_>
		[[nodiscard]] constexpr inline blend_mask_type _make_blend_mask(EmuCore::TMP::bool_sequence<Bits_...> bits_, std::index_sequence<Indices_...> indices_)
		{
			constexpr std::size_t num_bits = sizeof...(Bits_);
			constexpr std::size_t num_indices = sizeof...(Indices_);
			static_assert(num_bits == num_indices, "Error with EmuSIMD::Funcs::_underlying_funcs::_make_blend_mask: The number of boolean bits passed is not equal to the number of indices in the passed index sequence.");

			if constexpr (num_bits == sizeof...(Indices_))
			{
				constexpr std::size_t end_shift = num_indices - 1;
				return (... | _shift_blend_mask_bit<Bits_, end_shift - Indices_>());
			}
		}

		template<bool...Bits_, std::size_t...Indices_>
		[[nodiscard]] constexpr inline blend_mask_type _make_reverse_blend_mask(EmuCore::TMP::bool_sequence<Bits_...> bits_, std::index_sequence<Indices_...> indices_)
		{
			constexpr std::size_t num_bits = sizeof...(Bits_);
			constexpr std::size_t num_indices = sizeof...(Indices_);
			static_assert(num_bits == num_indices, "Error with EmuSIMD::Funcs::_underlying_funcs::_make_reverse_blend_mask: The number of boolean bits passed is not equal to the number of indices in the passed index sequence.");

			if constexpr (num_bits == sizeof...(Indices_))
			{
				return (... | _shift_blend_mask_bit<Bits_, Indices_>());
			}
		}
	}

	template<blend_mask_type BlendMask, bool Reverse_, typename TargetType_, std::size_t...Indices_, class SettingFunc_>
	[[nodiscard]] constexpr inline decltype(auto) blend_mask_to_vector(std::index_sequence<Indices_...> indices_, SettingFunc_&& setter_)
	{
		if constexpr (std::is_integral_v<TargetType_>)
		{
			constexpr TargetType_ all_bits = EmuCore::ArithmeticHelpers::set_all_bits_one<TargetType_>();
			constexpr TargetType_ one = TargetType_(1);
			if constexpr (Reverse_)
			{
				return std::forward<SettingFunc_>(setter_)
				(
					std::integral_constant<TargetType_, static_cast<TargetType_>((BlendMask >> Indices_) & one) * all_bits>::value...
				);
			}
			else
			{
				constexpr std::size_t end_index = sizeof...(Indices_) - 1;
				return std::forward<SettingFunc_>(setter_)
				(
					std::integral_constant<TargetType_, static_cast<TargetType_>((BlendMask >> (end_index - Indices_)) & one) * all_bits>::value...
				);
			}
		}
		else
		{
			using _int_type = EmuCore::TMP::uint_of_size_t<sizeof(TargetType_)>;
			if constexpr (!std::is_same_v<_int_type, EmuCore::TMP::emu_tmp_err>)
			{
				constexpr _int_type all_bits = EmuCore::ArithmeticHelpers::set_all_bits_one<_int_type>();
				constexpr _int_type one = _int_type(1);
				if constexpr (Reverse_)
				{
					return std::forward<SettingFunc_>(setter_)
					(
						std::bit_cast<TargetType_>(_int_type(((BlendMask >> Indices_) & one) * all_bits))...
					);
				}
				else
				{
					constexpr std::size_t end_index = sizeof...(Indices_) - 1;
					return std::forward<SettingFunc_>(setter_)
					(
						std::bit_cast<TargetType_>(_int_type(((BlendMask >> (end_index - Indices_)) & one) * all_bits))...
					);
				}
			}
			else
			{
				static_assert
				(
					EmuCore::TMP::get_false<TargetType_>(),
					"Error calling EmuSIMD::Funcs::blend_mask_to_vector: The input TargetType_ is not integral, and is not of a size with a matching unsigned integral type."
				);
			}
		}
	}

	[[nodiscard]] inline EmuSIMD::i8x16 blend_mask_vector_16_to_8(EmuSIMD::i16x8_arg mask_16bit_elements_)
	{
		return _mm_shuffle_epi8
		(
			mask_16bit_elements_,
			_mm_set_epi8(14, 14, 12, 12, 10, 10, 8, 8, 6, 6, 4, 4, 2, 2, 0, 0)
		);
	}

	[[nodiscard]] inline EmuSIMD::i8x32 blend_mask_vector_16_to_8(EmuSIMD::i16x16_arg mask_16bit_elements_)
	{
		return _mm256_shuffle_epi8
		(
			mask_16bit_elements_,
			_mm256_set_epi8(30, 30, 28, 28, 26, 26, 24, 24, 22, 22, 20, 20, 18, 18, 16, 16, 14, 14, 12, 12, 10, 10, 8, 8, 6, 6, 4, 4, 2, 2, 0, 0)
		);
	}

	[[nodiscard]] inline EmuSIMD::i8x64 blend_mask_vector_16_to_8(EmuSIMD::i16x32_arg mask_16bit_elements_)
	{
		return _mm512_shuffle_epi8
		(
			mask_16bit_elements_,
			_mm512_set_epi8
			(
				62, 62, 60, 60, 58, 58, 56, 56, 54, 54, 52, 52, 50, 50, 48, 48, 46, 46, 44, 44, 42, 42, 40, 40, 38, 38, 36, 36, 34, 34, 32, 32,
				30, 30, 28, 28, 26, 26, 24, 24, 22, 22, 20, 20, 18, 18, 16, 16, 14, 14, 12, 12, 10, 10, 8,  8,  6,  6,  4,  4,  2,  2,  0,  0
			)
		);
	}

	template<bool I0_, bool I1_>
	[[nodiscard]] constexpr inline blend_mask_type make_blend_mask()
	{
		return EmuSIMD::Funcs::_underlying_funcs::_make_blend_mask(EmuCore::TMP::bool_sequence<I0_, I1_>(), std::make_index_sequence<2>());
	}

	template<bool I0_, bool I1_, bool I2_, bool I3_>
	[[nodiscard]] constexpr inline blend_mask_type make_blend_mask()
	{
		return EmuSIMD::Funcs::_underlying_funcs::_make_blend_mask(EmuCore::TMP::bool_sequence<I0_, I1_, I2_, I3_>(), std::make_index_sequence<4>());
	}

	template<bool I0_, bool I1_, bool I2_, bool I3_, bool I4_, bool I5_, bool I6_, bool I7_>
	[[nodiscard]] constexpr inline blend_mask_type make_blend_mask()
	{
		return EmuSIMD::Funcs::_underlying_funcs::_make_blend_mask(EmuCore::TMP::bool_sequence<I0_, I1_, I2_, I3_, I4_, I5_, I6_, I7_>(), std::make_index_sequence<8>());
	}

	template<bool I0_, bool I1_, bool I2_, bool I3_, bool I4_, bool I5_, bool I6_, bool I7_, bool I8_, bool I9_, bool I10_, bool I11_, bool I12_, bool I13_, bool I14_, bool I15_>
	[[nodiscard]] constexpr inline blend_mask_type make_blend_mask()
	{
		return EmuSIMD::Funcs::_underlying_funcs::_make_blend_mask(EmuCore::TMP::bool_sequence<I0_, I1_, I2_, I3_, I4_, I5_, I6_, I7_, I8_, I9_, I10_, I11_, I12_, I13_, I14_, I15_>(), std::make_index_sequence<16>());
	}

	template
	<
		bool I0_,  bool I1_,  bool I2_,  bool I3_,  bool I4_,  bool I5_,  bool I6_,  bool I7_,  bool I8_,  bool I9_,  bool I10_, bool I11_ ,bool I12_, bool I13_, bool I14_, bool I15_,
		bool I16_, bool I17_, bool I18_, bool I19_, bool I20_, bool I21_, bool I22_, bool I23_, bool I24_, bool I25_, bool I26_, bool I27_, bool I28_, bool I29_, bool I30_, bool I31_
	>
	[[nodiscard]] constexpr inline blend_mask_type make_blend_mask()
	{
		return EmuSIMD::Funcs::_underlying_funcs::_make_blend_mask
		(
			EmuCore::TMP::bool_sequence<I0_, I1_, I2_, I3_, I4_, I5_, I6_, I7_, I8_, I9_, I10_, I11_, I12_, I13_, I14_, I15_, I16_, I17_, I18_, I19_, I20_, I21_, I22_, I23_, I24_, I25_, I26_, I27_, I28_, I29_, I30_, I31_>(),
			std::make_index_sequence<32>()
		);
	}

	template
	<
		bool I0_,  bool I1_,  bool I2_,  bool I3_,  bool I4_,  bool I5_,  bool I6_,  bool I7_,  bool I8_,  bool I9_,  bool I10_, bool I11_ ,bool I12_, bool I13_, bool I14_, bool I15_,
		bool I16_, bool I17_, bool I18_, bool I19_, bool I20_, bool I21_, bool I22_, bool I23_, bool I24_, bool I25_, bool I26_, bool I27_, bool I28_, bool I29_, bool I30_, bool I31_,
		bool I32_, bool I33_, bool I34_, bool I35_, bool I36_, bool I37_, bool I38_, bool I39_, bool I40_, bool I41_, bool I42_, bool I43_, bool I44_, bool I45_, bool I46_, bool I47_,
		bool I48_, bool I49_, bool I50_, bool I51_, bool I52_, bool I53_, bool I54_, bool I55_, bool I56_, bool I57_, bool I58_, bool I59_, bool I60_, bool I61_, bool I62_, bool I63_
	>
	[[nodiscard]] constexpr inline blend_mask_type make_blend_mask()
	{
		return EmuSIMD::Funcs::_underlying_funcs::_make_blend_mask
		(
			EmuCore::TMP::bool_sequence
			<
				I0_,  I1_,  I2_,  I3_,  I4_,  I5_,  I6_,  I7_,  I8_,  I9_,  I10_, I11_, I12_, I13_, I14_, I15_, I16_, I17_, I18_, I19_, I20_, I21_, I22_, I23_, I24_, I25_, I26_, I27_, I28_, I29_, I30_, I31_,
				I32_, I33_, I34_, I35_, I36_, I37_, I38_, I39_, I40_, I41_, I42_, I43_, I44_, I45_, I46_, I47_, I48_, I49_, I50_, I51_, I52_, I53_, I54_, I55_, I56_, I57_, I58_, I59_, I60_, I61_, I62_, I63_
			>(),
			std::make_index_sequence<64>()
		);
	}

	template<bool I0_, bool I1_>
	[[nodiscard]] constexpr inline blend_mask_type make_reverse_blend_mask()
	{
		return EmuSIMD::Funcs::_underlying_funcs::_make_reverse_blend_mask(EmuCore::TMP::bool_sequence<I0_, I1_>(), std::make_index_sequence<2>());
	}

	template<bool I0_, bool I1_, bool I2_, bool I3_>
	[[nodiscard]] constexpr inline blend_mask_type make_reverse_blend_mask()
	{
		return EmuSIMD::Funcs::_underlying_funcs::_make_reverse_blend_mask(EmuCore::TMP::bool_sequence<I0_, I1_, I2_, I3_>(), std::make_index_sequence<4>());
	}

	template<bool I0_, bool I1_, bool I2_, bool I3_, bool I4_, bool I5_, bool I6_, bool I7_>
	[[nodiscard]] constexpr inline blend_mask_type make_reverse_blend_mask()
	{
		return EmuSIMD::Funcs::_underlying_funcs::_make_reverse_blend_mask(EmuCore::TMP::bool_sequence<I0_, I1_, I2_, I3_, I4_, I5_, I6_, I7_>(), std::make_index_sequence<8>());
	}

	template<bool I0_, bool I1_, bool I2_, bool I3_, bool I4_, bool I5_, bool I6_, bool I7_, bool I8_, bool I9_, bool I10_, bool I11_, bool I12_, bool I13_, bool I14_, bool I15_>
	[[nodiscard]] constexpr inline blend_mask_type make_reverse_blend_mask()
	{
		return EmuSIMD::Funcs::_underlying_funcs::_make_reverse_blend_mask(EmuCore::TMP::bool_sequence<I0_, I1_, I2_, I3_, I4_, I5_, I6_, I7_, I8_, I9_, I10_, I11_, I12_, I13_, I14_, I15_>(), std::make_index_sequence<16>());
	}

	template
	<
		bool I0_,  bool I1_,  bool I2_,  bool I3_,  bool I4_,  bool I5_,  bool I6_,  bool I7_,  bool I8_,  bool I9_,  bool I10_, bool I11_ ,bool I12_, bool I13_, bool I14_, bool I15_,
		bool I16_, bool I17_, bool I18_, bool I19_, bool I20_, bool I21_, bool I22_, bool I23_, bool I24_, bool I25_, bool I26_, bool I27_, bool I28_, bool I29_, bool I30_, bool I31_
	>
	[[nodiscard]] constexpr inline blend_mask_type make_reverse_blend_mask()
	{
		return EmuSIMD::Funcs::_underlying_funcs::_make_reverse_blend_mask
		(
			EmuCore::TMP::bool_sequence<I0_, I1_, I2_, I3_, I4_, I5_, I6_, I7_, I8_, I9_, I10_, I11_, I12_, I13_, I14_, I15_, I16_, I17_, I18_, I19_, I20_, I21_, I22_, I23_, I24_, I25_, I26_, I27_, I28_, I29_, I30_, I31_>(),
			std::make_index_sequence<32>()
		);
	}

	template
	<
		bool I0_,  bool I1_,  bool I2_,  bool I3_,  bool I4_,  bool I5_,  bool I6_,  bool I7_,  bool I8_,  bool I9_,  bool I10_, bool I11_ ,bool I12_, bool I13_, bool I14_, bool I15_,
		bool I16_, bool I17_, bool I18_, bool I19_, bool I20_, bool I21_, bool I22_, bool I23_, bool I24_, bool I25_, bool I26_, bool I27_, bool I28_, bool I29_, bool I30_, bool I31_,
		bool I32_, bool I33_, bool I34_, bool I35_, bool I36_, bool I37_, bool I38_, bool I39_, bool I40_, bool I41_, bool I42_, bool I43_, bool I44_, bool I45_, bool I46_, bool I47_,
		bool I48_, bool I49_, bool I50_, bool I51_, bool I52_, bool I53_, bool I54_, bool I55_, bool I56_, bool I57_, bool I58_, bool I59_, bool I60_, bool I61_, bool I62_, bool I63_
	>
	[[nodiscard]] constexpr inline blend_mask_type make_reverse_blend_mask()
	{
		return EmuSIMD::Funcs::_underlying_funcs::_make_reverse_blend_mask
		(
			EmuCore::TMP::bool_sequence
			<
				I0_,  I1_,  I2_,  I3_,  I4_,  I5_,  I6_,  I7_,  I8_,  I9_,  I10_, I11_, I12_, I13_, I14_, I15_, I16_, I17_, I18_, I19_, I20_, I21_, I22_, I23_, I24_, I25_, I26_, I27_, I28_, I29_, I30_, I31_,
				I32_, I33_, I34_, I35_, I36_, I37_, I38_, I39_, I40_, I41_, I42_, I43_, I44_, I45_, I46_, I47_, I48_, I49_, I50_, I51_, I52_, I53_, I54_, I55_, I56_, I57_, I58_, I59_, I60_, I61_, I62_, I63_
			>(),
			std::make_index_sequence<64>()
		);
	}

	template<blend_mask_type BlendMask_, std::size_t NumIndices_, bool Reverse_ = false>
	struct bool_sequence_from_index_mask_maker
	{
	private:
		template<std::size_t...Indices_>
		[[nodiscard]] static constexpr auto _make_bool_seq(std::index_sequence<Indices_...> index_sequence_)
		{
			return EmuCore::TMP::bool_sequence
			<
				static_cast<bool>((BlendMask_ >> Indices_) & 1)...
			>();
		}

		[[nodiscard]] static constexpr auto _make_index_seq()
		{
			// Ironically, reversed index sequence will create an unreversed bool sequence as we're basing interactions on the x86 SIMD interface. Thanks, endianness!
			if constexpr (Reverse_)
			{
				return std::make_index_sequence<NumIndices_>();
			}
			else
			{
				return EmuCore::TMP::make_reverse_index_sequence<NumIndices_>();
			}
		}

	public:
		using type = decltype(_make_bool_seq(_make_index_seq()));
	};
	template<blend_mask_type BlendMask_, std::size_t NumIndices_, bool Reverse_ = false>
	using make_bool_sequence_from_index_mask = typename bool_sequence_from_index_mask_maker<BlendMask_, NumIndices_, Reverse_>::type;

	namespace _underlying_funcs
	{
		template<std::size_t MsbIndex_, typename OutT_, typename InT_, std::size_t...OutIndices_>
		[[nodiscard]] constexpr inline auto _convert_movemask_width_less_elements(const InT_& in_, std::index_sequence<OutIndices_...>) noexcept
		{
			constexpr std::size_t input_bits_per_output_bit = MsbIndex_ + 1;
			return static_cast<OutT_>
			((
				... |
				((in_ >> ((input_bits_per_output_bit * OutIndices_) + MsbIndex_) & 1) << OutIndices_)
			));
		}
	}

	template<std::size_t FromElements_, std::size_t ToElements_, typename OutT_, typename InT_>
	[[nodiscard]] constexpr inline auto convert_movemask_width(const InT_& in_) noexcept
		-> typename std::remove_cvref<OutT_>::type
	{
		if constexpr (FromElements_ == ToElements_)
		{
			return static_cast<typename std::remove_cvref<OutT_>::type>(in_);
		}
		else
		{
			if constexpr (EmuCore::TMP::is_one_of<ToElements_, 2, 4, 8, 16, 32, 64>())
			{
				if constexpr (EmuCore::TMP::is_one_of<FromElements_, 2, 4, 8, 16, 32, 64>())
				{
					if constexpr (ToElements_ < FromElements_)
					{
						constexpr std::size_t msb_index = (FromElements_ / ToElements_) - 1;
						return _underlying_funcs::_convert_movemask_width_less_elements<msb_index, OutT_>(in_, std::make_index_sequence<ToElements_>());
					}
					else
					{
						static_assert(EmuCore::TMP::get_false<std::size_t, ToElements_>(), "Invalid `ToElements_`/`FromElements_` counts provided to EmuSIMD::Funcs::convert_movemask_width: `ToElements_` cannot be greater than `FromElements_`.");
					}
				}
				else
				{
					static_assert(EmuCore::TMP::get_false<std::size_t, FromElements_>(), "Invalid `FromElements_` count provided to `EmuSIMD::Funcs::convert_movemask_width`. Valid values are: 2, 4, 8, 16, 32, 64.");
				}
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<std::size_t, ToElements_>(), "Invalid `ToElements_` count provided to `EmuSIMD::Funcs::convert_movemask_width`. Valid values are: 2, 4, 8, 16, 32, 64.");
			}
		}
	}
}

#endif
