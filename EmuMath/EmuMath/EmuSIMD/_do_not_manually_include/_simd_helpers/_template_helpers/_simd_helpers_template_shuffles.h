#ifndef EMU_SIMD_HELPERS_SHUFFLES_H_INC_
#define EMU_SIMD_HELPERS_SHUFFLES_H_INC_ 1

#include "_underlying_template_helpers/_all_underlying_templates.h"
#include "_underlying_template_helpers/_generic_funcs/_forward_declarations/_forward_template_gets.h"
#include "_simd_helpers_template_gets.h"

namespace EmuSIMD
{
	template<std::size_t...Indices_, EmuConcepts::KnownSIMD Register_>
	[[nodiscard]] inline auto shuffle(Register_&& ab_)
		-> typename std::remove_cvref<Register_>::type
	{
		using permuter = _underlying_simd_helpers::_permuter<typename std::remove_cvref<Register_>::type, Indices_...>;
		return permuter::execute(std::forward<Register_>(ab_));
	}

	template<std::size_t...Indices_, EmuConcepts::KnownSIMD RegisterA_, EmuConcepts::UnqualifiedMatch<RegisterA_> RegisterB_>
	[[nodiscard]] inline auto shuffle(RegisterA_&& a_, RegisterB_&& b_)
		-> typename std::remove_cvref<RegisterA_>::type
	{
		using shuffler = _underlying_simd_helpers::_shuffler<typename std::remove_cvref<RegisterA_>::type, typename std::remove_cvref<RegisterB_>::type, Indices_...>;
		return shuffler::execute(std::forward<RegisterA_>(a_), std::forward<RegisterB_>(b_));
	}

	template<std::uint64_t ShuffleMask_, std::size_t PerElementWidthIfGenericInt_, EmuConcepts::KnownSIMD Register_>
	[[nodiscard]] inline auto shuffle_with_mask(Register_&& ab_)
		-> typename std::remove_cvref<Register_>::type
	{
		using _register_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (std::is_same_v<_register_uq, EmuSIMD::f32x4>)
		{
			return EmuSIMD::Funcs::permute_f32x4<ShuffleMask_>(std::forward<Register_>(ab_));
		}
		else if constexpr (std::is_same_v<_register_uq, EmuSIMD::f32x8>)
		{
			return EmuSIMD::Funcs::permute_f32x8<ShuffleMask_>(std::forward<Register_>(ab_));
		}
		else if constexpr (std::is_same_v<_register_uq, EmuSIMD::f32x16>)
		{
			return EmuSIMD::Funcs::permute_f32x16<ShuffleMask_>(std::forward<Register_>(ab_));
		}
		else if constexpr (std::is_same_v<_register_uq, EmuSIMD::f64x2>)
		{
			return EmuSIMD::Funcs::permute_f64x2<ShuffleMask_>(std::forward<Register_>(ab_));
		}
		else if constexpr (std::is_same_v<_register_uq, EmuSIMD::f64x4>)
		{
			return EmuSIMD::Funcs::permute_f64x4<ShuffleMask_>(std::forward<Register_>(ab_));
		}
		else if constexpr (std::is_same_v<_register_uq, EmuSIMD::f64x8>)
		{
			return EmuSIMD::Funcs::permute_f64x8<ShuffleMask_>(std::forward<Register_>(ab_));
		}
		else if constexpr (std::is_same_v<_register_uq, EmuSIMD::i128_generic>)
		{
			if constexpr (PerElementWidthIfGenericInt_ == 8)
			{
				return EmuSIMD::Funcs::permute_i8x16<ShuffleMask_>(std::forward<Register_>(ab_));
			}
			else if constexpr (PerElementWidthIfGenericInt_ == 16)
			{
				return EmuSIMD::Funcs::permute_i16x8<ShuffleMask_>(std::forward<Register_>(ab_));
			}
			else if constexpr (PerElementWidthIfGenericInt_ == 32)
			{
				return EmuSIMD::Funcs::permute_i32x4<ShuffleMask_>(std::forward<Register_>(ab_));
			}
			else if constexpr (PerElementWidthIfGenericInt_ == 64)
			{
				return EmuSIMD::Funcs::permute_i64x2<ShuffleMask_>(std::forward<Register_>(ab_));
			}
			else
			{
				static_assert
				(
					EmuCore::TMP::get_false<std::size_t, PerElementWidthIfGenericInt_>(),
					"Invalid PerElementWidthIfGenericInt_ passed to `EmuSIMD::shuffle_with_mask` with a generic 128-bit integral register. Valid values are: 8, 16, 32, 64."
				);
			}
		}
		else if constexpr (std::is_same_v<_register_uq, EmuSIMD::i256_generic>)
		{
			if constexpr (PerElementWidthIfGenericInt_ == 8)
			{
				return EmuSIMD::Funcs::permute_i8x32<ShuffleMask_>(std::forward<Register_>(ab_));
			}
			else if constexpr (PerElementWidthIfGenericInt_ == 16)
			{
				return EmuSIMD::Funcs::permute_i16x16<ShuffleMask_>(std::forward<Register_>(ab_));
			}
			else if constexpr (PerElementWidthIfGenericInt_ == 32)
			{
				return EmuSIMD::Funcs::permute_i32x8<ShuffleMask_>(std::forward<Register_>(ab_));
			}
			else if constexpr (PerElementWidthIfGenericInt_ == 64)
			{
				return EmuSIMD::Funcs::permute_i64x4<ShuffleMask_>(std::forward<Register_>(ab_));
			}
			else
			{
				static_assert
				(
					EmuCore::TMP::get_false<std::size_t, PerElementWidthIfGenericInt_>(),
					"Invalid PerElementWidthIfGenericInt_ passed to `EmuSIMD::shuffle_with_mask` with a generic 256-bit integral register. Valid values are: 8, 16, 32, 64."
				);
			}
		}
		else if constexpr (std::is_same_v<_register_uq, EmuSIMD::i512_generic>)
		{
			if constexpr (PerElementWidthIfGenericInt_ == 8)
			{
				return EmuSIMD::Funcs::permute_i8x64<ShuffleMask_>(std::forward<Register_>(ab_));
			}
			else if constexpr (PerElementWidthIfGenericInt_ == 16)
			{
				return EmuSIMD::Funcs::permute_i16x32<ShuffleMask_>(std::forward<Register_>(ab_));
			}
			else if constexpr (PerElementWidthIfGenericInt_ == 32)
			{
				return EmuSIMD::Funcs::permute_i32x16<ShuffleMask_>(std::forward<Register_>(ab_));
			}
			else if constexpr (PerElementWidthIfGenericInt_ == 64)
			{
				return EmuSIMD::Funcs::permute_i64x8<ShuffleMask_>(std::forward<Register_>(ab_));
			}
			else
			{
				static_assert
				(
					EmuCore::TMP::get_false<std::size_t, PerElementWidthIfGenericInt_>(),
					"Invalid PerElementWidthIfGenericInt_ passed to `EmuSIMD::shuffle_with_mask` with a generic 512-bit integral register. Valid values are: 8, 16, 32, 64."
				);
			}
		}
		else if constexpr (std::is_same_v<_register_uq, EmuSIMD::i8x16>)
		{
			return EmuSIMD::Funcs::permute_i8x16<ShuffleMask_>(std::forward<Register_>(ab_));
		}
		else if constexpr (std::is_same_v<_register_uq, EmuSIMD::i16x8>)
		{
			return EmuSIMD::Funcs::permute_i16x8<ShuffleMask_>(std::forward<Register_>(ab_));
		}
		else if constexpr (std::is_same_v<_register_uq, EmuSIMD::i32x4>)
		{
			return EmuSIMD::Funcs::permute_i32x4<ShuffleMask_>(std::forward<Register_>(ab_));
		}
		else if constexpr (std::is_same_v<_register_uq, EmuSIMD::i64x2>)
		{
			return EmuSIMD::Funcs::permute_i64x2<ShuffleMask_>(std::forward<Register_>(ab_));
		}
		else if constexpr (std::is_same_v<_register_uq, EmuSIMD::i8x32>)
		{
			return EmuSIMD::Funcs::permute_i8x32<ShuffleMask_>(std::forward<Register_>(ab_));
		}
		else if constexpr (std::is_same_v<_register_uq, EmuSIMD::i16x16>)
		{
			return EmuSIMD::Funcs::permute_i16x16<ShuffleMask_>(std::forward<Register_>(ab_));
		}
		else if constexpr (std::is_same_v<_register_uq, EmuSIMD::i32x8>)
		{
			return EmuSIMD::Funcs::permute_i32x8<ShuffleMask_>(std::forward<Register_>(ab_));
		}
		else if constexpr (std::is_same_v<_register_uq, EmuSIMD::i64x4>)
		{
			return EmuSIMD::Funcs::permute_i64x4<ShuffleMask_>(std::forward<Register_>(ab_));
		}
		else if constexpr (std::is_same_v<_register_uq, EmuSIMD::i8x64>)
		{
			return EmuSIMD::Funcs::permute_i8x64<ShuffleMask_>(std::forward<Register_>(ab_));
		}
		else if constexpr (std::is_same_v<_register_uq, EmuSIMD::i16x32>)
		{
			return EmuSIMD::Funcs::permute_i16x32<ShuffleMask_>(std::forward<Register_>(ab_));
		}
		else if constexpr (std::is_same_v<_register_uq, EmuSIMD::i32x16>)
		{
			return EmuSIMD::Funcs::permute_i32x16<ShuffleMask_>(std::forward<Register_>(ab_));
		}
		else if constexpr (std::is_same_v<_register_uq, EmuSIMD::i64x8>)
		{
			return EmuSIMD::Funcs::permute_i64x8<ShuffleMask_>(std::forward<Register_>(ab_));
		}		
		else if constexpr (std::is_same_v<_register_uq, EmuSIMD::u8x16>)
		{
			return EmuSIMD::Funcs::permute_u8x16<ShuffleMask_>(std::forward<Register_>(ab_));
		}
		else if constexpr (std::is_same_v<_register_uq, EmuSIMD::u16x8>)
		{
			return EmuSIMD::Funcs::permute_u16x8<ShuffleMask_>(std::forward<Register_>(ab_));
		}
		else if constexpr (std::is_same_v<_register_uq, EmuSIMD::u32x4>)
		{
			return EmuSIMD::Funcs::permute_u32x4<ShuffleMask_>(std::forward<Register_>(ab_));
		}
		else if constexpr (std::is_same_v<_register_uq, EmuSIMD::u64x2>)
		{
			return EmuSIMD::Funcs::permute_u64x2<ShuffleMask_>(std::forward<Register_>(ab_));
		}
		else if constexpr (std::is_same_v<_register_uq, EmuSIMD::u8x32>)
		{
			return EmuSIMD::Funcs::permute_u8x32<ShuffleMask_>(std::forward<Register_>(ab_));
		}
		else if constexpr (std::is_same_v<_register_uq, EmuSIMD::u16x16>)
		{
			return EmuSIMD::Funcs::permute_u16x16<ShuffleMask_>(std::forward<Register_>(ab_));
		}
		else if constexpr (std::is_same_v<_register_uq, EmuSIMD::u32x8>)
		{
			return EmuSIMD::Funcs::permute_u32x8<ShuffleMask_>(std::forward<Register_>(ab_));
		}
		else if constexpr (std::is_same_v<_register_uq, EmuSIMD::u64x4>)
		{
			return EmuSIMD::Funcs::permute_u64x4<ShuffleMask_>(std::forward<Register_>(ab_));
		}
		else if constexpr (std::is_same_v<_register_uq, EmuSIMD::u8x64>)
		{
			return EmuSIMD::Funcs::permute_u8x64<ShuffleMask_>(std::forward<Register_>(ab_));
		}
		else if constexpr (std::is_same_v<_register_uq, EmuSIMD::u16x32>)
		{
			return EmuSIMD::Funcs::permute_u16x32<ShuffleMask_>(std::forward<Register_>(ab_));
		}
		else if constexpr (std::is_same_v<_register_uq, EmuSIMD::u32x16>)
		{
			return EmuSIMD::Funcs::permute_u32x16<ShuffleMask_>(std::forward<Register_>(ab_));
		}
		else if constexpr (std::is_same_v<_register_uq, EmuSIMD::u64x8>)
		{
			return EmuSIMD::Funcs::permute_u64x8<ShuffleMask_>(std::forward<Register_>(ab_));
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to use `EmuSIMD::shuffle_with_mask` with an unsupported input type.");
		}
	}

	template<std::uint64_t ShuffleMask_, std::size_t PerElementWidthIfGenericInt_, EmuConcepts::KnownSIMD RegisterA_, EmuConcepts::UnqualifiedMatch<RegisterA_> RegisterB_>
	[[nodiscard]] inline auto shuffle_with_mask(RegisterA_&& a_, RegisterB_&& b_)
		-> typename std::remove_cvref<RegisterA_>::type
	{
		using _register_uq = typename EmuCore::TMP::remove_ref_cv<RegisterA_>::type;
		if constexpr (std::is_same_v<_register_uq, EmuSIMD::f32x4>)
		{
			return EmuSIMD::Funcs::shuffle_f32x4<ShuffleMask_>(std::forward<RegisterA_>(a_), std::forward<RegisterB_>(b_));
		}
		else if constexpr (std::is_same_v<_register_uq, EmuSIMD::f32x8>)
		{
			return EmuSIMD::Funcs::shuffle_f32x8<ShuffleMask_>(std::forward<RegisterA_>(a_), std::forward<RegisterB_>(b_));
		}
		else if constexpr (std::is_same_v<_register_uq, EmuSIMD::f32x16>)
		{
			return EmuSIMD::Funcs::shuffle_f32x16<ShuffleMask_>(std::forward<RegisterA_>(a_), std::forward<RegisterB_>(b_));
		}
		else if constexpr (std::is_same_v<_register_uq, EmuSIMD::f64x2>)
		{
			return EmuSIMD::Funcs::shuffle_f64x2<ShuffleMask_>(std::forward<RegisterA_>(a_), std::forward<RegisterB_>(b_));
		}
		else if constexpr (std::is_same_v<_register_uq, EmuSIMD::f64x4>)
		{
			return EmuSIMD::Funcs::shuffle_f64x4<ShuffleMask_>(std::forward<RegisterA_>(a_), std::forward<RegisterB_>(b_));
		}
		else if constexpr (std::is_same_v<_register_uq, EmuSIMD::f64x8>)
		{
			return EmuSIMD::Funcs::shuffle_f64x8<ShuffleMask_>(std::forward<RegisterA_>(a_), std::forward<RegisterB_>(b_));
		}
		else if constexpr (std::is_same_v<_register_uq, EmuSIMD::i128_generic>)
		{
			if constexpr (PerElementWidthIfGenericInt_ == 8)
			{
				return EmuSIMD::Funcs::shuffle_i8x16<ShuffleMask_>(std::forward<RegisterA_>(a_), std::forward<RegisterB_>(b_));
			}
			else if constexpr (PerElementWidthIfGenericInt_ == 16)
			{
				return EmuSIMD::Funcs::shuffle_i16x8<ShuffleMask_>(std::forward<RegisterA_>(a_), std::forward<RegisterB_>(b_));
			}
			else if constexpr (PerElementWidthIfGenericInt_ == 32)
			{
				return EmuSIMD::Funcs::shuffle_i32x4<ShuffleMask_>(std::forward<RegisterA_>(a_), std::forward<RegisterB_>(b_));
			}
			else if constexpr (PerElementWidthIfGenericInt_ == 64)
			{
				return EmuSIMD::Funcs::shuffle_i64x2<ShuffleMask_>(std::forward<RegisterA_>(a_), std::forward<RegisterB_>(b_));
			}
			else
			{
				static_assert
				(
					EmuCore::TMP::get_false<std::size_t, PerElementWidthIfGenericInt_>(),
					"Invalid PerElementWidthIfGenericInt_ passed to `EmuSIMD::shuffle_with_mask` with a generic 128-bit integral register. Valid values are: 8, 16, 32, 64."
				);
			}
		}
		else if constexpr (std::is_same_v<_register_uq, EmuSIMD::i256_generic>)
		{
			if constexpr (PerElementWidthIfGenericInt_ == 8)
			{
				return EmuSIMD::Funcs::shuffle_i8x32<ShuffleMask_>(std::forward<RegisterA_>(a_), std::forward<RegisterB_>(b_));
			}
			else if constexpr (PerElementWidthIfGenericInt_ == 16)
			{
				return EmuSIMD::Funcs::shuffle_i16x16<ShuffleMask_>(std::forward<RegisterA_>(a_), std::forward<RegisterB_>(b_));
			}
			else if constexpr (PerElementWidthIfGenericInt_ == 32)
			{
				return EmuSIMD::Funcs::shuffle_i32x8<ShuffleMask_>(std::forward<RegisterA_>(a_), std::forward<RegisterB_>(b_));
			}
			else if constexpr (PerElementWidthIfGenericInt_ == 64)
			{
				return EmuSIMD::Funcs::shuffle_i64x4<ShuffleMask_>(std::forward<RegisterA_>(a_), std::forward<RegisterB_>(b_));
			}
			else
			{
				static_assert
				(
					EmuCore::TMP::get_false<std::size_t, PerElementWidthIfGenericInt_>(),
					"Invalid PerElementWidthIfGenericInt_ passed to `EmuSIMD::shuffle_with_mask` with a generic 256-bit integral register. Valid values are: 8, 16, 32, 64."
				);
			}
		}
		else if constexpr (std::is_same_v<_register_uq, EmuSIMD::i512_generic>)
		{
			if constexpr (PerElementWidthIfGenericInt_ == 8)
			{
				return EmuSIMD::Funcs::shuffle_i8x64<ShuffleMask_>(std::forward<RegisterA_>(a_), std::forward<RegisterB_>(b_));
			}
			else if constexpr (PerElementWidthIfGenericInt_ == 16)
			{
				return EmuSIMD::Funcs::shuffle_i16x32<ShuffleMask_>(std::forward<RegisterA_>(a_), std::forward<RegisterB_>(b_));
			}
			else if constexpr (PerElementWidthIfGenericInt_ == 32)
			{
				return EmuSIMD::Funcs::shuffle_i32x16<ShuffleMask_>(std::forward<RegisterA_>(a_), std::forward<RegisterB_>(b_));
			}
			else if constexpr (PerElementWidthIfGenericInt_ == 64)
			{
				return EmuSIMD::Funcs::shuffle_i64x8<ShuffleMask_>(std::forward<RegisterA_>(a_), std::forward<RegisterB_>(b_));
			}
			else
			{
				static_assert
				(
					EmuCore::TMP::get_false<std::size_t, PerElementWidthIfGenericInt_>(),
					"Invalid PerElementWidthIfGenericInt_ passed to `EmuSIMD::shuffle_with_mask` with a generic 512-bit integral register. Valid values are: 8, 16, 32, 64."
				);
			}
		}
		else if constexpr (std::is_same_v<_register_uq, EmuSIMD::i8x16>)
		{
			return EmuSIMD::Funcs::shuffle_i8x16<ShuffleMask_>(std::forward<RegisterA_>(a_), std::forward<RegisterB_>(b_));
		}
		else if constexpr (std::is_same_v<_register_uq, EmuSIMD::i16x8>)
		{
			return EmuSIMD::Funcs::shuffle_i16x8<ShuffleMask_>(std::forward<RegisterA_>(a_), std::forward<RegisterB_>(b_));
		}
		else if constexpr (std::is_same_v<_register_uq, EmuSIMD::i32x4>)
		{
			return EmuSIMD::Funcs::shuffle_i32x4<ShuffleMask_>(std::forward<RegisterA_>(a_), std::forward<RegisterB_>(b_));
		}
		else if constexpr (std::is_same_v<_register_uq, EmuSIMD::i64x2>)
		{
			return EmuSIMD::Funcs::shuffle_i64x2<ShuffleMask_>(std::forward<RegisterA_>(a_), std::forward<RegisterB_>(b_));
		}
		else if constexpr (std::is_same_v<_register_uq, EmuSIMD::i8x32>)
		{
			return EmuSIMD::Funcs::shuffle_i8x32<ShuffleMask_>(std::forward<RegisterA_>(a_), std::forward<RegisterB_>(b_));
		}
		else if constexpr (std::is_same_v<_register_uq, EmuSIMD::i16x16>)
		{
			return EmuSIMD::Funcs::shuffle_i16x16<ShuffleMask_>(std::forward<RegisterA_>(a_), std::forward<RegisterB_>(b_));
		}
		else if constexpr (std::is_same_v<_register_uq, EmuSIMD::i32x8>)
		{
			return EmuSIMD::Funcs::shuffle_i32x8<ShuffleMask_>(std::forward<RegisterA_>(a_), std::forward<RegisterB_>(b_));
		}
		else if constexpr (std::is_same_v<_register_uq, EmuSIMD::i64x4>)
		{
			return EmuSIMD::Funcs::shuffle_i64x4<ShuffleMask_>(std::forward<RegisterA_>(a_), std::forward<RegisterB_>(b_));
		}
		else if constexpr (std::is_same_v<_register_uq, EmuSIMD::i8x64>)
		{
			return EmuSIMD::Funcs::shuffle_i8x64<ShuffleMask_>(std::forward<RegisterA_>(a_), std::forward<RegisterB_>(b_));
		}
		else if constexpr (std::is_same_v<_register_uq, EmuSIMD::i16x32>)
		{
			return EmuSIMD::Funcs::shuffle_i16x32<ShuffleMask_>(std::forward<RegisterA_>(a_), std::forward<RegisterB_>(b_));
		}
		else if constexpr (std::is_same_v<_register_uq, EmuSIMD::i32x16>)
		{
			return EmuSIMD::Funcs::shuffle_i32x16<ShuffleMask_>(std::forward<RegisterA_>(a_), std::forward<RegisterB_>(b_));
		}
		else if constexpr (std::is_same_v<_register_uq, EmuSIMD::i64x8>)
		{
			return EmuSIMD::Funcs::shuffle_i64x8<ShuffleMask_>(std::forward<RegisterA_>(a_), std::forward<RegisterB_>(b_));
		}		
		else if constexpr (std::is_same_v<_register_uq, EmuSIMD::u8x16>)
		{
			return EmuSIMD::Funcs::shuffle_u8x16<ShuffleMask_>(std::forward<RegisterA_>(a_), std::forward<RegisterB_>(b_));
		}
		else if constexpr (std::is_same_v<_register_uq, EmuSIMD::u16x8>)
		{
			return EmuSIMD::Funcs::shuffle_u16x8<ShuffleMask_>(std::forward<RegisterA_>(a_), std::forward<RegisterB_>(b_));
		}
		else if constexpr (std::is_same_v<_register_uq, EmuSIMD::u32x4>)
		{
			return EmuSIMD::Funcs::shuffle_u32x4<ShuffleMask_>(std::forward<RegisterA_>(a_), std::forward<RegisterB_>(b_));
		}
		else if constexpr (std::is_same_v<_register_uq, EmuSIMD::u64x2>)
		{
			return EmuSIMD::Funcs::shuffle_u64x2<ShuffleMask_>(std::forward<RegisterA_>(a_), std::forward<RegisterB_>(b_));
		}
		else if constexpr (std::is_same_v<_register_uq, EmuSIMD::u8x32>)
		{
			return EmuSIMD::Funcs::shuffle_u8x32<ShuffleMask_>(std::forward<RegisterA_>(a_), std::forward<RegisterB_>(b_));
		}
		else if constexpr (std::is_same_v<_register_uq, EmuSIMD::u16x16>)
		{
			return EmuSIMD::Funcs::shuffle_u16x16<ShuffleMask_>(std::forward<RegisterA_>(a_), std::forward<RegisterB_>(b_));
		}
		else if constexpr (std::is_same_v<_register_uq, EmuSIMD::u32x8>)
		{
			return EmuSIMD::Funcs::shuffle_u32x8<ShuffleMask_>(std::forward<RegisterA_>(a_), std::forward<RegisterB_>(b_));
		}
		else if constexpr (std::is_same_v<_register_uq, EmuSIMD::u64x4>)
		{
			return EmuSIMD::Funcs::shuffle_u64x4<ShuffleMask_>(std::forward<RegisterA_>(a_), std::forward<RegisterB_>(b_));
		}
		else if constexpr (std::is_same_v<_register_uq, EmuSIMD::u8x64>)
		{
			return EmuSIMD::Funcs::shuffle_u8x64<ShuffleMask_>(std::forward<RegisterA_>(a_), std::forward<RegisterB_>(b_));
		}
		else if constexpr (std::is_same_v<_register_uq, EmuSIMD::u16x32>)
		{
			return EmuSIMD::Funcs::shuffle_u16x32<ShuffleMask_>(std::forward<RegisterA_>(a_), std::forward<RegisterB_>(b_));
		}
		else if constexpr (std::is_same_v<_register_uq, EmuSIMD::u32x16>)
		{
			return EmuSIMD::Funcs::shuffle_u32x16<ShuffleMask_>(std::forward<RegisterA_>(a_), std::forward<RegisterB_>(b_));
		}
		else if constexpr (std::is_same_v<_register_uq, EmuSIMD::u64x8>)
		{
			return EmuSIMD::Funcs::shuffle_u64x8<ShuffleMask_>(std::forward<RegisterA_>(a_), std::forward<RegisterB_>(b_));
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<RegisterA_, RegisterB_>(), "Attempted to use `EmuSIMD::shuffle_with_mask` with an unsupported input type.");
		}
	}

#pragma region FULL_WIDTH_SHUFFLES
	/// <summary>
	/// <para> Performs a full-width shuffle of the passed SIMD register's indices. </para>
	/// <para> For 128-bit registers, this is the same as a normal shuffle. </para>
	/// </summary>
	/// <param name="a_">128-bit register to shuffle for the lo bytes of the output register.</param>
	/// <param name="b_">128-bit register to shuffle for the hi bytes of the output register.</param>
	/// <returns>Result of shuffling the passed Registers with the provided indices.</returns>
	template<std::size_t...Indices_, EmuConcepts::KnownSIMD RegisterA_, EmuConcepts::UnqualifiedMatch<RegisterA_> RegisterB_>
	requires (EmuSIMD::TMP::simd_register_width_v<RegisterA_> == 128)
	[[nodiscard]] constexpr inline auto shuffle_full_width(RegisterA_&& a_, RegisterB_&& b_)
		-> typename std::remove_cvref<RegisterA_>::type
	{
		using shuffler = _underlying_simd_helpers::_shuffler<typename std::remove_cvref<RegisterA_>::type, typename std::remove_cvref<RegisterB_>::type, Indices_...>;
		return shuffler::execute(std::forward<RegisterA_>(a_), std::forward<RegisterB_>(b_));
	}

	/// <summary>
	/// <para> Performs a full-width shuffle of the passed SIMD register's indices. </para>
	/// <para> For 128-bit registers, this is the same as a normal shuffle. </para>
	/// </summary>
	/// <param name="ab_">128-bit register to shuffle.</param>
	/// <returns>Result of shuffling the passed Register with the provided indices.</returns>
	template<std::size_t...Indices_, EmuConcepts::KnownSIMD Register_>
	requires (EmuSIMD::TMP::simd_register_width_v<Register_> == 128)
	[[nodiscard]] constexpr inline auto shuffle_full_width(Register_&& ab_)
		-> typename std::remove_cvref<Register_>::type
	{
		using permuter = _underlying_simd_helpers::_permuter<typename std::remove_cvref<Register_>::type, Indices_...>;
		return permuter::execute(std::forward<Register_>(ab_));
	}

	/// <summary>
	/// <para> Performs a full-width shuffle of the passed SIMD register's indices, allowing shuffles between lanes unlike a normal shuffle. </para>
	/// </summary>
	/// <param name="a_">256-bit register to shuffle for the lo 128-bit lane of the output register.</param>
	/// <param name="b_">256-bit register to shuffle for the hi 128-bit lane of the output register.</param>
	/// <returns>Result of full-width-shuffling the passed Registers with the provided indices.</returns>
	template<std::size_t I0_, std::size_t I1_, std::size_t I2_, std::size_t I3_, EmuConcepts::KnownSIMD RegisterA_, EmuConcepts::UnqualifiedMatch<RegisterA_> RegisterB_>
	requires (EmuSIMD::TMP::simd_register_width_v<RegisterA_> == 256 && EmuSIMD::TMP::register_element_count_v<RegisterA_, 64> == 4)
	[[nodiscard]] constexpr inline auto shuffle_full_width(RegisterA_&& a_, RegisterB_&& b_)
		-> typename std::remove_cvref<RegisterA_>::type
	{
		using _register_uq = typename EmuCore::TMP::remove_ref_cv<RegisterA_>::type;
		using _generic_register_type = EmuSIMD::f64x4;
		using _generic_lane_register = typename EmuSIMD::TMP::half_width<_generic_register_type>::type;
		_generic_register_type out;

		constexpr std::size_t max_lo_index = 1;
		constexpr std::size_t lowest_index = EmuCore::TMP::smallest_constant_v<std::size_t, I0_, I1_, I2_, I3_>;
		if constexpr (lowest_index > max_lo_index)
		{
			// All hi indices, we can just shuffle hi lane
			auto hi_a = EmuSIMD::extract_lane<1, _generic_lane_register>(std::forward<RegisterA_>(a_));
			auto hi_b = EmuSIMD::extract_lane<1, _generic_lane_register>(std::forward<RegisterB_>(b_));
			hi_b = EmuSIMD::shuffle<I2_ - 2, I3_ - 2>(hi_b);

			out = EmuSIMD::cast<_generic_register_type>(EmuSIMD::shuffle<I0_ - 2, I1_ - 2>(hi_a));
			out = _mm256_insertf128_pd(out, hi_b, 1);
		}
		else
		{
			constexpr std::size_t highest_index = EmuCore::TMP::greatest_constant_v<std::size_t, I0_, I1_, I2_, I3_>;
			if constexpr (highest_index <= max_lo_index)
			{
				// All lo indices, we can just shuffle lo lane
				auto lo_a = EmuSIMD::cast<_generic_lane_register>(std::forward<RegisterA_>(a_));
				auto lo_b = EmuSIMD::cast<_generic_lane_register>(std::forward<RegisterB_>(b_));

				out = EmuSIMD::cast<_generic_register_type>(EmuSIMD::shuffle<I0_, I1_>(lo_a));
				lo_b = EmuSIMD::shuffle<I2_, I3_>(lo_b);
				out = _mm256_insertf128_pd(out, lo_b, 1);
			}
			else // Mixed lanes, we need to actually try
			{
				// Lo
				constexpr int i0_lane = (I0_ <= max_lo_index) ? 0 : 1;
				constexpr int i1_lane = (I1_ <= max_lo_index) ? 0 : 1;
				_generic_lane_register lane_0, lane_1;
				if constexpr (i0_lane == i1_lane)
				{
					lane_0 = EmuSIMD::extract_lane<i0_lane, _generic_lane_register>(std::forward<RegisterA_>(a_));
					lane_1 = lane_0;
				}
				else
				{
					lane_0 = EmuSIMD::extract_lane<i0_lane, _generic_lane_register>(std::forward<RegisterA_>(a_));
					lane_1 = EmuSIMD::extract_lane<i1_lane, _generic_lane_register>(std::forward<RegisterA_>(a_));
				}
				out = EmuSIMD::cast<_generic_register_type>(EmuSIMD::shuffle<I0_ % 2, I1_ % 2>(lane_0, lane_1));

				// Hi
				constexpr int i2_lane = (I2_ <= max_lo_index) ? 0 : 1;
				constexpr int i3_lane = (I3_ <= max_lo_index) ? 0 : 1;
				if constexpr (i2_lane == i3_lane)
				{
					lane_0 = EmuSIMD::extract_lane<i2_lane, _generic_lane_register>(std::forward<RegisterB_>(b_));
					lane_1 = lane_0;
				}
				else
				{
					lane_0 = EmuSIMD::extract_lane<i2_lane, _generic_lane_register>(std::forward<RegisterB_>(b_));
					lane_1 = EmuSIMD::extract_lane<i3_lane, _generic_lane_register>(std::forward<RegisterB_>(b_));
				}

				auto tmp_shuffle = EmuSIMD::cast<_generic_lane_register>(EmuSIMD::shuffle<I2_ % 2, I3_ % 2>(lane_0, lane_1));
				out = _mm256_insertf128_pd(out, tmp_shuffle, 1);
			}
		}

		if constexpr (std::is_same_v<_register_uq, _generic_register_type>)
		{
			return out;
		}
		else
		{
			return EmuSIMD::cast<typename std::remove_cvref<RegisterA_>::type>(out);
		}
	}

	/// <summary>
	/// <para> Performs a full-width shuffle of the passed SIMD register's indices, allowing shuffles between lanes unlike a normal shuffle. </para>
	/// </summary>
	/// <param name="ab_">256-bit register to shuffle.</param>
	/// <returns>Result of full-width-shuffling the passed Register with the provided indices.</returns>
	template<std::size_t I0_, std::size_t I1_, std::size_t I2_, std::size_t I3_, EmuConcepts::KnownSIMD Register_>
	requires (EmuSIMD::TMP::simd_register_width_v<Register_> == 256 && EmuSIMD::TMP::register_element_count_v<Register_> == 4)
	[[nodiscard]] constexpr inline auto shuffle_full_width(Register_&& ab_)
		-> typename std::remove_cvref<Register_>::type
	{
		const auto& ab_ref = std::forward<Register_>(ab_);
		return shuffle_full_width<I0_, I1_, I2_, I3_>(ab_ref, ab_ref);
	}
#pragma endregion
}

#endif
