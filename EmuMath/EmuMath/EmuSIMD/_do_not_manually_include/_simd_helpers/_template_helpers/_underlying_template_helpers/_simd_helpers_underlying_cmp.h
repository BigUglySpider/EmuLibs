#ifndef EMU_SIMD_HELPERS_UNDERLYING_CMP_H_INC_
#define EMU_SIMD_HELPERS_UNDERLYING_CMP_H_INC_ 1

#include "_common_underlying_simd_template_helper_includes.h"
#include "_simd_helpers_underlying_cast.h"
#include "../../../../../EmuCore/CommonConcepts/Arithmetic.h"
#include "../../../../../EmuCore/TMPHelpers/Values.h"

namespace EmuSIMD::_underlying_simd_helpers
{
#pragma region CMP_EQ_FUNCS
	template<std::size_t PerElementWidthIfGenericInt_, bool SignedIfGenericInt_, class Register_>
	[[nodiscard]] inline Register_ _cmp_eq(Register_ lhs_, Register_ rhs_)
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x4>)
			{
				return EmuSIMD::Funcs::cmpeq_f32x4(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x8>)
			{
				return EmuSIMD::Funcs::cmpeq_f32x8(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x16>)
			{
				return EmuSIMD::Funcs::cmpeq_f32x16(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x2>)
			{
				return EmuSIMD::Funcs::cmpeq_f64x2(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x4>)
			{
				return EmuSIMD::Funcs::cmpeq_f64x4(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x8>)
			{
				return EmuSIMD::Funcs::cmpeq_f64x8(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i128_generic>)
			{
				if constexpr (PerElementWidthIfGenericInt_ == 8)
				{
					if constexpr (SignedIfGenericInt_)
					{
						return EmuSIMD::Funcs::cmpeq_i8x16(lhs_, rhs_);
					}
					else
					{
						return EmuSIMD::Funcs::cmpeq_u8x16(lhs_, rhs_);
					}
				}
				else if constexpr (PerElementWidthIfGenericInt_ == 16)
				{
					if constexpr (SignedIfGenericInt_)
					{
						return EmuSIMD::Funcs::cmpeq_i16x8(lhs_, rhs_);
					}
					else
					{
						return EmuSIMD::Funcs::cmpeq_u16x8(lhs_, rhs_);
					}
				}
				else if constexpr (PerElementWidthIfGenericInt_ == 32)
				{
					if constexpr (SignedIfGenericInt_)
					{
						return EmuSIMD::Funcs::cmpeq_i32x4(lhs_, rhs_);
					}
					else
					{
						return EmuSIMD::Funcs::cmpeq_u32x4(lhs_, rhs_);
					}
				}
				else if constexpr (PerElementWidthIfGenericInt_ == 64)
				{
					if constexpr (SignedIfGenericInt_)
					{
						return EmuSIMD::Funcs::cmpeq_i64x2(lhs_, rhs_);
					}
					else
					{
						return EmuSIMD::Funcs::cmpeq_u64x2(lhs_, rhs_);
					}
				}
				else
				{
					static_assert(EmuCore::TMP::get_false<std::size_t, PerElementWidthIfGenericInt_>(), "Attempted to perform an equal comparison of generic 128-bit integral SIMD registers via EmuSIMD helpers, but the provided per-element width is invalid.");
				}
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i256_generic>)
			{
				if constexpr (PerElementWidthIfGenericInt_ == 8)
				{
					if constexpr (SignedIfGenericInt_)
					{
						return EmuSIMD::Funcs::cmpeq_i8x32(lhs_, rhs_);
					}
					else
					{
						return EmuSIMD::Funcs::cmpeq_u8x32(lhs_, rhs_);
					}
				}
				else if constexpr (PerElementWidthIfGenericInt_ == 16)
				{
					if constexpr (SignedIfGenericInt_)
					{
						return EmuSIMD::Funcs::cmpeq_i16x16(lhs_, rhs_);
					}
					else
					{
						return EmuSIMD::Funcs::cmpeq_u16x16(lhs_, rhs_);
					}
				}
				else if constexpr (PerElementWidthIfGenericInt_ == 32)
				{
					if constexpr (SignedIfGenericInt_)
					{
						return EmuSIMD::Funcs::cmpeq_i32x8(lhs_, rhs_);
					}
					else
					{
						return EmuSIMD::Funcs::cmpeq_u32x8(lhs_, rhs_);
					}
				}
				else if constexpr (PerElementWidthIfGenericInt_ == 64)
				{
					if constexpr (SignedIfGenericInt_)
					{
						return EmuSIMD::Funcs::cmpeq_i64x4(lhs_, rhs_);
					}
					else
					{
						return EmuSIMD::Funcs::cmpeq_u64x4(lhs_, rhs_);
					}
				}
				else
				{
					static_assert(EmuCore::TMP::get_false<std::size_t, PerElementWidthIfGenericInt_>(), "Attempted to perform an equal comparison of generic 256-bit integral SIMD registers via EmuSIMD helpers, but the provided per-element width is invalid.");
				}
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i512_generic>)
			{
				if constexpr (PerElementWidthIfGenericInt_ == 8)
				{
					if constexpr (SignedIfGenericInt_)
					{
						return EmuSIMD::Funcs::cmpeq_i8x64(lhs_, rhs_);
					}
					else
					{
						return EmuSIMD::Funcs::cmpeq_u8x64(lhs_, rhs_);
					}
				}
				else if constexpr (PerElementWidthIfGenericInt_ == 16)
				{
					if constexpr (SignedIfGenericInt_)
					{
						return EmuSIMD::Funcs::cmpeq_i16x32(lhs_, rhs_);
					}
					else
					{
						return EmuSIMD::Funcs::cmpeq_u16x32(lhs_, rhs_);
					}
				}
				else if constexpr (PerElementWidthIfGenericInt_ == 32)
				{
					if constexpr (SignedIfGenericInt_)
					{
						return EmuSIMD::Funcs::cmpeq_i32x16(lhs_, rhs_);
					}
					else
					{
						return EmuSIMD::Funcs::cmpeq_u32x16(lhs_, rhs_);
					}
				}
				else if constexpr (PerElementWidthIfGenericInt_ == 64)
				{
					if constexpr (SignedIfGenericInt_)
					{
						return EmuSIMD::Funcs::cmpeq_i64x8(lhs_, rhs_);
					}
					else
					{
						return EmuSIMD::Funcs::cmpeq_u64x8(lhs_, rhs_);
					}
				}
				else
				{
					static_assert(EmuCore::TMP::get_false<std::size_t, PerElementWidthIfGenericInt_>(), "Attempted to perform an equal comparison of generic 512-bit integral SIMD registers via EmuSIMD helpers, but the provided per-element width is invalid.");
				}
			}
			else if constexpr(std::is_same_v<register_type_uq, EmuSIMD::i8x16>)
			{
				return EmuSIMD::Funcs::cmpeq_i8x16(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i8x32>)
			{
				return EmuSIMD::Funcs::cmpeq_i8x32(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i8x64>)
			{
				return EmuSIMD::Funcs::cmpeq_i8x64(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i16x8>)
			{
				return EmuSIMD::Funcs::cmpeq_i16x8(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i16x16>)
			{
				return EmuSIMD::Funcs::cmpeq_i16x16(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i16x32>)
			{
				return EmuSIMD::Funcs::cmpeq_i16x32(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i32x4>)
			{
				return EmuSIMD::Funcs::cmpeq_i32x4(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i32x8>)
			{
				return EmuSIMD::Funcs::cmpeq_i32x8(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i32x16>)
			{
				return EmuSIMD::Funcs::cmpeq_i32x16(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i64x2>)
			{
				return EmuSIMD::Funcs::cmpeq_i64x2(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i64x4>)
			{
				return EmuSIMD::Funcs::cmpeq_i64x4(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i64x8>)
			{
				return EmuSIMD::Funcs::cmpeq_i64x8(lhs_, rhs_);
			}
			
			else if constexpr(std::is_same_v<register_type_uq, EmuSIMD::u8x16>)
			{
				return EmuSIMD::Funcs::cmpeq_u8x16(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u8x32>)
			{
				return EmuSIMD::Funcs::cmpeq_u8x32(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u8x64>)
			{
				return EmuSIMD::Funcs::cmpeq_u8x64(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u16x8>)
			{
				return EmuSIMD::Funcs::cmpeq_u16x8(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u16x16>)
			{
				return EmuSIMD::Funcs::cmpeq_u16x16(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u16x32>)
			{
				return EmuSIMD::Funcs::cmpeq_u16x32(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u32x4>)
			{
				return EmuSIMD::Funcs::cmpeq_u32x4(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u32x8>)
			{
				return EmuSIMD::Funcs::cmpeq_u32x8(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u32x16>)
			{
				return EmuSIMD::Funcs::cmpeq_u32x16(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u64x2>)
			{
				return EmuSIMD::Funcs::cmpeq_u64x2(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u64x4>)
			{
				return EmuSIMD::Funcs::cmpeq_u64x4(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u64x8>)
			{
				return EmuSIMD::Funcs::cmpeq_u64x8(lhs_, rhs_);
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform an equal comparison of SIMD registers using EmuSIMD helpers, but the provided Register_ type is not a supported SIMD register type.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform an equal comparison of SIMD registers using EmuSIMD helpers, but the provided Register_ type was not recognised as a SIMD register.");
		}
	}
#pragma endregion

#pragma region CMP_NEQ_FUNCS
	template<std::size_t PerElementWidthIfGenericInt_, bool SignedIfGenericInt_, class Register_>
	[[nodiscard]] inline Register_ _cmp_neq(Register_ lhs_, Register_ rhs_)
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x4>)
			{
				return EmuSIMD::Funcs::cmpneq_f32x4(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x8>)
			{
				return EmuSIMD::Funcs::cmpneq_f32x8(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x16>)
			{
				return EmuSIMD::Funcs::cmpneq_f32x16(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x2>)
			{
				return EmuSIMD::Funcs::cmpneq_f64x2(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x4>)
			{
				return EmuSIMD::Funcs::cmpneq_f64x4(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x8>)
			{
				return EmuSIMD::Funcs::cmpneq_f64x8(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i128_generic>)
			{
				if constexpr (PerElementWidthIfGenericInt_ == 8)
				{
					if constexpr (SignedIfGenericInt_)
					{
						return EmuSIMD::Funcs::cmpneq_i8x16(lhs_, rhs_);
					}
					else
					{
						return EmuSIMD::Funcs::cmpneq_u8x16(lhs_, rhs_);
					}
				}
				else if constexpr (PerElementWidthIfGenericInt_ == 16)
				{
					if constexpr (SignedIfGenericInt_)
					{
						return EmuSIMD::Funcs::cmpneq_i16x8(lhs_, rhs_);
					}
					else
					{
						return EmuSIMD::Funcs::cmpneq_u16x8(lhs_, rhs_);
					}
				}
				else if constexpr (PerElementWidthIfGenericInt_ == 32)
				{
					if constexpr (SignedIfGenericInt_)
					{
						return EmuSIMD::Funcs::cmpneq_i32x4(lhs_, rhs_);
					}
					else
					{
						return EmuSIMD::Funcs::cmpneq_u32x4(lhs_, rhs_);
					}
				}
				else if constexpr (PerElementWidthIfGenericInt_ == 64)
				{
					if constexpr (SignedIfGenericInt_)
					{
						return EmuSIMD::Funcs::cmpneq_i64x2(lhs_, rhs_);
					}
					else
					{
						return EmuSIMD::Funcs::cmpneq_u64x2(lhs_, rhs_);
					}
				}
				else
				{
					static_assert(EmuCore::TMP::get_false<std::size_t, PerElementWidthIfGenericInt_>(), "Attempted to perform a not-equal comparison of generic 128-bit integral SIMD registers via EmuSIMD helpers, but the provided per-element width is invalid.");
				}
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i256_generic>)
			{
				if constexpr (PerElementWidthIfGenericInt_ == 8)
				{
					if constexpr (SignedIfGenericInt_)
					{
						return EmuSIMD::Funcs::cmpneq_i8x32(lhs_, rhs_);
					}
					else
					{
						return EmuSIMD::Funcs::cmpneq_u8x32(lhs_, rhs_);
					}
				}
				else if constexpr (PerElementWidthIfGenericInt_ == 16)
				{
					if constexpr (SignedIfGenericInt_)
					{
						return EmuSIMD::Funcs::cmpeq_i16x16(lhs_, rhs_);
					}
					else
					{
						return EmuSIMD::Funcs::cmpneq_u16x16(lhs_, rhs_);
					}
				}
				else if constexpr (PerElementWidthIfGenericInt_ == 32)
				{
					if constexpr (SignedIfGenericInt_)
					{
						return EmuSIMD::Funcs::cmpneq_i32x8(lhs_, rhs_);
					}
					else
					{
						return EmuSIMD::Funcs::cmpneq_u32x8(lhs_, rhs_);
					}
				}
				else if constexpr (PerElementWidthIfGenericInt_ == 64)
				{
					if constexpr (SignedIfGenericInt_)
					{
						return EmuSIMD::Funcs::cmpneq_i64x4(lhs_, rhs_);
					}
					else
					{
						return EmuSIMD::Funcs::cmpneq_u64x4(lhs_, rhs_);
					}
				}
				else
				{
					static_assert(EmuCore::TMP::get_false<std::size_t, PerElementWidthIfGenericInt_>(), "Attempted to perform a not-equal comparison of generic 256-bit integral SIMD registers via EmuSIMD helpers, but the provided per-element width is invalid.");
				}
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i512_generic>)
			{
				if constexpr (PerElementWidthIfGenericInt_ == 8)
				{
					if constexpr (SignedIfGenericInt_)
					{
						return EmuSIMD::Funcs::cmpneq_i8x64(lhs_, rhs_);
					}
					else
					{
						return EmuSIMD::Funcs::cmpneq_u8x64(lhs_, rhs_);
					}
				}
				else if constexpr (PerElementWidthIfGenericInt_ == 16)
				{
					if constexpr (SignedIfGenericInt_)
					{
						return EmuSIMD::Funcs::cmpneq_i16x32(lhs_, rhs_);
					}
					else
					{
						return EmuSIMD::Funcs::cmpneq_u16x32(lhs_, rhs_);
					}
				}
				else if constexpr (PerElementWidthIfGenericInt_ == 32)
				{
					if constexpr (SignedIfGenericInt_)
					{
						return EmuSIMD::Funcs::cmpneq_i32x16(lhs_, rhs_);
					}
					else
					{
						return EmuSIMD::Funcs::cmpneq_u32x16(lhs_, rhs_);
					}
				}
				else if constexpr (PerElementWidthIfGenericInt_ == 64)
				{
					if constexpr (SignedIfGenericInt_)
					{
						return EmuSIMD::Funcs::cmpneq_i64x8(lhs_, rhs_);
					}
					else
					{
						return EmuSIMD::Funcs::cmpneq_u64x8(lhs_, rhs_);
					}
				}
				else
				{
					static_assert(EmuCore::TMP::get_false<std::size_t, PerElementWidthIfGenericInt_>(), "Attempted to perform a not-equal comparison of generic 512-bit integral SIMD registers via EmuSIMD helpers, but the provided per-element width is invalid.");
				}
			}
			else if constexpr(std::is_same_v<register_type_uq, EmuSIMD::i8x16>)
			{
				return EmuSIMD::Funcs::cmpneq_i8x16(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i8x32>)
			{
				return EmuSIMD::Funcs::cmpneq_i8x32(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i8x64>)
			{
				return EmuSIMD::Funcs::cmpneq_i8x64(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i16x8>)
			{
				return EmuSIMD::Funcs::cmpneq_i16x8(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i16x16>)
			{
				return EmuSIMD::Funcs::cmpneq_i16x16(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i16x32>)
			{
				return EmuSIMD::Funcs::cmpneq_i16x32(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i32x4>)
			{
				return EmuSIMD::Funcs::cmpneq_i32x4(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i32x8>)
			{
				return EmuSIMD::Funcs::cmpneq_i32x8(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i32x16>)
			{
				return EmuSIMD::Funcs::cmpneq_i32x16(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i64x2>)
			{
				return EmuSIMD::Funcs::cmpneq_i64x2(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i64x4>)
			{
				return EmuSIMD::Funcs::cmpneq_i64x4(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i64x8>)
			{
				return EmuSIMD::Funcs::cmpneq_i64x8(lhs_, rhs_);
			}
			
			else if constexpr(std::is_same_v<register_type_uq, EmuSIMD::u8x16>)
			{
				return EmuSIMD::Funcs::cmpneq_u8x16(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u8x32>)
			{
				return EmuSIMD::Funcs::cmpneq_u8x32(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u8x64>)
			{
				return EmuSIMD::Funcs::cmpneq_u8x64(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u16x8>)
			{
				return EmuSIMD::Funcs::cmpneq_u16x8(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u16x16>)
			{
				return EmuSIMD::Funcs::cmpneq_u16x16(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u16x32>)
			{
				return EmuSIMD::Funcs::cmpneq_u16x32(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u32x4>)
			{
				return EmuSIMD::Funcs::cmpneq_u32x4(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u32x8>)
			{
				return EmuSIMD::Funcs::cmpneq_u32x8(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u32x16>)
			{
				return EmuSIMD::Funcs::cmpneq_u32x16(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u64x2>)
			{
				return EmuSIMD::Funcs::cmpneq_u64x2(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u64x4>)
			{
				return EmuSIMD::Funcs::cmpneq_u64x4(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u64x8>)
			{
				return EmuSIMD::Funcs::cmpneq_u64x8(lhs_, rhs_);
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform a not-equal comparison of SIMD registers using EmuSIMD helpers, but the provided Register_ type is not a supported SIMD register type.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform a not-equal comparison of SIMD registers using EmuSIMD helpers, but the provided Register_ type was not recognised as a SIMD register.");
		}
	}
#pragma endregion

#pragma region CMP_LT_FUNCS
	template<std::size_t PerElementWidthIfGenericInt_, bool SignedIfGenericInt_, class Register_>
	[[nodiscard]] inline Register_ _cmp_lt(Register_ lhs_, Register_ rhs_)
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x4>)
			{
				return EmuSIMD::Funcs::cmplt_f32x4(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x8>)
			{
				return EmuSIMD::Funcs::cmplt_f32x8(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x16>)
			{
				return EmuSIMD::Funcs::cmplt_f32x16(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x2>)
			{
				return EmuSIMD::Funcs::cmplt_f64x2(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x4>)
			{
				return EmuSIMD::Funcs::cmplt_f64x4(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x8>)
			{
				return EmuSIMD::Funcs::cmplt_f64x8(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i128_generic>)
			{
				if constexpr (PerElementWidthIfGenericInt_ == 8)
				{
					if constexpr (SignedIfGenericInt_)
					{
						return EmuSIMD::Funcs::cmplt_i8x16(lhs_, rhs_);
					}
					else
					{
						return EmuSIMD::Funcs::cmplt_u8x16(lhs_, rhs_);
					}
				}
				else if constexpr (PerElementWidthIfGenericInt_ == 16)
				{
					if constexpr (SignedIfGenericInt_)
					{
						return EmuSIMD::Funcs::cmplt_i16x8(lhs_, rhs_);
					}
					else
					{
						return EmuSIMD::Funcs::cmplt_u16x8(lhs_, rhs_);
					}
				}
				else if constexpr (PerElementWidthIfGenericInt_ == 32)
				{
					if constexpr (SignedIfGenericInt_)
					{
						return EmuSIMD::Funcs::cmplt_i32x4(lhs_, rhs_);
					}
					else
					{
						return EmuSIMD::Funcs::cmplt_u32x4(lhs_, rhs_);
					}
				}
				else if constexpr (PerElementWidthIfGenericInt_ == 64)
				{
					if constexpr (SignedIfGenericInt_)
					{
						return EmuSIMD::Funcs::cmplt_i64x2(lhs_, rhs_);
					}
					else
					{
						return EmuSIMD::Funcs::cmplt_u64x2(lhs_, rhs_);
					}
				}
				else
				{
					static_assert(EmuCore::TMP::get_false<std::size_t, PerElementWidthIfGenericInt_>(), "Attempted to perform less-than comparison (<) of generic 128-bit integral SIMD registers via EmuSIMD helpers, but the provided per-element width is invalid.");
				}
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i256_generic>)
			{
				if constexpr (PerElementWidthIfGenericInt_ == 8)
				{
					if constexpr (SignedIfGenericInt_)
					{
						return EmuSIMD::Funcs::cmplt_i8x32(lhs_, rhs_);
					}
					else
					{
						return EmuSIMD::Funcs::cmplt_u8x32(lhs_, rhs_);
					}
				}
				else if constexpr (PerElementWidthIfGenericInt_ == 16)
				{
					if constexpr (SignedIfGenericInt_)
					{
						return EmuSIMD::Funcs::cmplt_i16x16(lhs_, rhs_);
					}
					else
					{
						return EmuSIMD::Funcs::cmplt_u16x16(lhs_, rhs_);
					}
				}
				else if constexpr (PerElementWidthIfGenericInt_ == 32)
				{
					if constexpr (SignedIfGenericInt_)
					{
						return EmuSIMD::Funcs::cmplt_i32x8(lhs_, rhs_);
					}
					else
					{
						return EmuSIMD::Funcs::cmplt_u32x8(lhs_, rhs_);
					}
				}
				else if constexpr (PerElementWidthIfGenericInt_ == 64)
				{
					if constexpr (SignedIfGenericInt_)
					{
						return EmuSIMD::Funcs::cmplt_i64x4(lhs_, rhs_);
					}
					else
					{
						return EmuSIMD::Funcs::cmplt_u64x4(lhs_, rhs_);
					}
				}
				else
				{
					static_assert(EmuCore::TMP::get_false<std::size_t, PerElementWidthIfGenericInt_>(), "Attempted to perform a less-than comparison (<) of generic 256-bit integral SIMD registers via EmuSIMD helpers, but the provided per-element width is invalid.");
				}
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i512_generic>)
			{
				if constexpr (PerElementWidthIfGenericInt_ == 8)
				{
					if constexpr (SignedIfGenericInt_)
					{
						return EmuSIMD::Funcs::cmplt_i8x64(lhs_, rhs_);
					}
					else
					{
						return EmuSIMD::Funcs::cmplt_u8x64(lhs_, rhs_);
					}
				}
				else if constexpr (PerElementWidthIfGenericInt_ == 16)
				{
					if constexpr (SignedIfGenericInt_)
					{
						return EmuSIMD::Funcs::cmplt_i16x32(lhs_, rhs_);
					}
					else
					{
						return EmuSIMD::Funcs::cmplt_u16x32(lhs_, rhs_);
					}
				}
				else if constexpr (PerElementWidthIfGenericInt_ == 32)
				{
					if constexpr (SignedIfGenericInt_)
					{
						return EmuSIMD::Funcs::cmplt_i32x16(lhs_, rhs_);
					}
					else
					{
						return EmuSIMD::Funcs::cmplt_u32x16(lhs_, rhs_);
					}
				}
				else if constexpr (PerElementWidthIfGenericInt_ == 64)
				{
					if constexpr (SignedIfGenericInt_)
					{
						return EmuSIMD::Funcs::cmplt_i64x8(lhs_, rhs_);
					}
					else
					{
						return EmuSIMD::Funcs::cmplt_u64x8(lhs_, rhs_);
					}
				}
				else
				{
					static_assert(EmuCore::TMP::get_false<std::size_t, PerElementWidthIfGenericInt_>(), "Attempted to perform a less-than comparison (<) of generic 512-bit integral SIMD registers via EmuSIMD helpers, but the provided per-element width is invalid.");
				}
			}
			else if constexpr(std::is_same_v<register_type_uq, EmuSIMD::i8x16>)
			{
				return EmuSIMD::Funcs::cmplt_i8x16(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i8x32>)
			{
				return EmuSIMD::Funcs::cmplt_i8x32(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i8x64>)
			{
				return EmuSIMD::Funcs::cmplt_i8x64(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i16x8>)
			{
				return EmuSIMD::Funcs::cmplt_i16x8(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i16x16>)
			{
				return EmuSIMD::Funcs::cmplt_i16x16(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i16x32>)
			{
				return EmuSIMD::Funcs::cmplt_i16x32(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i32x4>)
			{
				return EmuSIMD::Funcs::cmplt_i32x4(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i32x8>)
			{
				return EmuSIMD::Funcs::cmplt_i32x8(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i32x16>)
			{
				return EmuSIMD::Funcs::cmplt_i32x16(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i64x2>)
			{
				return EmuSIMD::Funcs::cmplt_i64x2(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i64x4>)
			{
				return EmuSIMD::Funcs::cmplt_i64x4(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i64x8>)
			{
				return EmuSIMD::Funcs::cmplt_i64x8(lhs_, rhs_);
			}			
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u8x16>)
			{
				return EmuSIMD::Funcs::cmplt_u8x16(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u8x32>)
			{
				return EmuSIMD::Funcs::cmplt_u8x32(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u8x64>)
			{
				return EmuSIMD::Funcs::cmplt_u8x64(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u16x8>)
			{
				return EmuSIMD::Funcs::cmplt_u16x8(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u16x16>)
			{
				return EmuSIMD::Funcs::cmplt_u16x16(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u16x32>)
			{
				return EmuSIMD::Funcs::cmplt_u16x32(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u32x4>)
			{
				return EmuSIMD::Funcs::cmplt_u32x4(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u32x8>)
			{
				return EmuSIMD::Funcs::cmplt_u32x8(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u32x16>)
			{
				return EmuSIMD::Funcs::cmplt_u32x16(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u64x2>)
			{
				return EmuSIMD::Funcs::cmplt_u64x2(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u64x4>)
			{
				return EmuSIMD::Funcs::cmplt_u64x4(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u64x8>)
			{
				return EmuSIMD::Funcs::cmplt_u64x8(lhs_, rhs_);
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform a less-than comparison (<) of SIMD registers using EmuSIMD helpers, but the provided Register_ type is not a supported SIMD register type.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform a less-than comparison (<) of SIMD registers using EmuSIMD helpers, but the provided Register_ type was not recognised as a SIMD register.");
		}
	}
#pragma endregion

#pragma region CMP_GT_FUNCS
	template<std::size_t PerElementWidthIfGenericInt_, bool SignedIfGenericInt_, class Register_>
	[[nodiscard]] inline Register_ _cmp_gt(Register_ lhs_, Register_ rhs_)
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x4>)
			{
				return EmuSIMD::Funcs::cmpgt_f32x4(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x8>)
			{
				return EmuSIMD::Funcs::cmpgt_f32x8(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x16>)
			{
				return EmuSIMD::Funcs::cmpgt_f32x16(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x2>)
			{
				return EmuSIMD::Funcs::cmpgt_f64x2(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x4>)
			{
				return EmuSIMD::Funcs::cmpgt_f64x4(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x8>)
			{
				return EmuSIMD::Funcs::cmpgt_f64x8(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i128_generic>)
			{
				if constexpr (PerElementWidthIfGenericInt_ == 8)
				{
					if constexpr (SignedIfGenericInt_)
					{
						return EmuSIMD::Funcs::cmpgt_i8x16(lhs_, rhs_);
					}
					else
					{
						return EmuSIMD::Funcs::cmpgt_u8x16(lhs_, rhs_);
					}
				}
				else if constexpr (PerElementWidthIfGenericInt_ == 16)
				{
					if constexpr (SignedIfGenericInt_)
					{
						return EmuSIMD::Funcs::cmpgt_i16x8(lhs_, rhs_);
					}
					else
					{
						return EmuSIMD::Funcs::cmpgt_u16x8(lhs_, rhs_);
					}
				}
				else if constexpr (PerElementWidthIfGenericInt_ == 32)
				{
					if constexpr (SignedIfGenericInt_)
					{
						return EmuSIMD::Funcs::cmpgt_i32x4(lhs_, rhs_);
					}
					else
					{
						return EmuSIMD::Funcs::cmpgt_u32x4(lhs_, rhs_);
					}
				}
				else if constexpr (PerElementWidthIfGenericInt_ == 64)
				{
					if constexpr (SignedIfGenericInt_)
					{
						return EmuSIMD::Funcs::cmpgt_i64x2(lhs_, rhs_);
					}
					else
					{
						return EmuSIMD::Funcs::cmpgt_u64x2(lhs_, rhs_);
					}
				}
				else
				{
					static_assert(EmuCore::TMP::get_false<std::size_t, PerElementWidthIfGenericInt_>(), "Attempted to perform greater-than comparison (>) of generic 128-bit integral SIMD registers via EmuSIMD helpers, but the provided per-element width is invalid.");
				}
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i256_generic>)
			{
				if constexpr (PerElementWidthIfGenericInt_ == 8)
				{
					if constexpr (SignedIfGenericInt_)
					{
						return EmuSIMD::Funcs::cmpgt_i8x32(lhs_, rhs_);
					}
					else
					{
						return EmuSIMD::Funcs::cmpgt_u8x32(lhs_, rhs_);
					}
				}
				else if constexpr (PerElementWidthIfGenericInt_ == 16)
				{
					if constexpr (SignedIfGenericInt_)
					{
						return EmuSIMD::Funcs::cmpgt_i16x16(lhs_, rhs_);
					}
					else
					{
						return EmuSIMD::Funcs::cmpgt_u16x16(lhs_, rhs_);
					}
				}
				else if constexpr (PerElementWidthIfGenericInt_ == 32)
				{
					if constexpr (SignedIfGenericInt_)
					{
						return EmuSIMD::Funcs::cmpgt_i32x8(lhs_, rhs_);
					}
					else
					{
						return EmuSIMD::Funcs::cmpgt_u32x8(lhs_, rhs_);
					}
				}
				else if constexpr (PerElementWidthIfGenericInt_ == 64)
				{
					if constexpr (SignedIfGenericInt_)
					{
						return EmuSIMD::Funcs::cmpgt_i64x4(lhs_, rhs_);
					}
					else
					{
						return EmuSIMD::Funcs::cmpgt_u64x4(lhs_, rhs_);
					}
				}
				else
				{
					static_assert(EmuCore::TMP::get_false<std::size_t, PerElementWidthIfGenericInt_>(), "Attempted to perform a greater-than comparison (>) of generic 256-bit integral SIMD registers via EmuSIMD helpers, but the provided per-element width is invalid.");
				}
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i512_generic>)
			{
				if constexpr (PerElementWidthIfGenericInt_ == 8)
				{
					if constexpr (SignedIfGenericInt_)
					{
						return EmuSIMD::Funcs::cmpgt_i8x64(lhs_, rhs_);
					}
					else
					{
						return EmuSIMD::Funcs::cmpgt_u8x64(lhs_, rhs_);
					}
				}
				else if constexpr (PerElementWidthIfGenericInt_ == 16)
				{
					if constexpr (SignedIfGenericInt_)
					{
						return EmuSIMD::Funcs::cmpgt_i16x32(lhs_, rhs_);
					}
					else
					{
						return EmuSIMD::Funcs::cmpgt_u16x32(lhs_, rhs_);
					}
				}
				else if constexpr (PerElementWidthIfGenericInt_ == 32)
				{
					if constexpr (SignedIfGenericInt_)
					{
						return EmuSIMD::Funcs::cmpgt_i32x16(lhs_, rhs_);
					}
					else
					{
						return EmuSIMD::Funcs::cmpgt_u32x16(lhs_, rhs_);
					}
				}
				else if constexpr (PerElementWidthIfGenericInt_ == 64)
				{
					if constexpr (SignedIfGenericInt_)
					{
						return EmuSIMD::Funcs::cmpgt_i64x8(lhs_, rhs_);
					}
					else
					{
						return EmuSIMD::Funcs::cmpgt_u64x8(lhs_, rhs_);
					}
				}
				else
				{
					static_assert(EmuCore::TMP::get_false<std::size_t, PerElementWidthIfGenericInt_>(), "Attempted to perform a greater-than comparison (>) of generic 512-bit integral SIMD registers via EmuSIMD helpers, but the provided per-element width is invalid.");
				}
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i8x16>)
			{
				return EmuSIMD::Funcs::cmpgt_i8x16(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i8x32>)
			{
				return EmuSIMD::Funcs::cmpgt_i8x32(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i8x64>)
			{
				return EmuSIMD::Funcs::cmpgt_i8x64(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i16x8>)
			{
				return EmuSIMD::Funcs::cmpgt_i16x8(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i16x16>)
			{
				return EmuSIMD::Funcs::cmpgt_i16x16(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i16x32>)
			{
				return EmuSIMD::Funcs::cmpgt_i16x32(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i32x4>)
			{
				return EmuSIMD::Funcs::cmpgt_i32x4(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i32x8>)
			{
				return EmuSIMD::Funcs::cmpgt_i32x8(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i32x16>)
			{
				return EmuSIMD::Funcs::cmpgt_i32x16(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i64x2>)
			{
				return EmuSIMD::Funcs::cmpgt_i64x2(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i64x4>)
			{
				return EmuSIMD::Funcs::cmpgt_i64x4(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i64x8>)
			{
				return EmuSIMD::Funcs::cmpgt_i64x8(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u8x16>)
			{
				return EmuSIMD::Funcs::cmpgt_u8x16(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u8x32>)
			{
				return EmuSIMD::Funcs::cmpgt_u8x32(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u8x64>)
			{
				return EmuSIMD::Funcs::cmpgt_u8x64(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u16x8>)
			{
				return EmuSIMD::Funcs::cmpgt_u16x8(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u16x16>)
			{
				return EmuSIMD::Funcs::cmpgt_u16x16(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u16x32>)
			{
				return EmuSIMD::Funcs::cmpgt_u16x32(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u32x4>)
			{
				return EmuSIMD::Funcs::cmpgt_u32x4(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u32x8>)
			{
				return EmuSIMD::Funcs::cmpgt_u32x8(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u32x16>)
			{
				return EmuSIMD::Funcs::cmpgt_u32x16(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u64x2>)
			{
				return EmuSIMD::Funcs::cmpgt_u64x2(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u64x4>)
			{
				return EmuSIMD::Funcs::cmpgt_u64x4(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u64x8>)
			{
				return EmuSIMD::Funcs::cmpgt_u64x8(lhs_, rhs_);
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform a greater-than comparison (>) of SIMD registers using EmuSIMD helpers, but the provided Register_ type is not a supported SIMD register type.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform a greater-than comparison (>) of SIMD registers using EmuSIMD helpers, but the provided Register_ type was not recognised as a SIMD register.");
		}
	}
#pragma endregion

#pragma region CMP_LE_FUNCS
	template<std::size_t PerElementWidthIfGenericInt_, bool SignedIfGenericInt_, class Register_>
	[[nodiscard]] inline Register_ _cmp_le(Register_ lhs_, Register_ rhs_)
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x4>)
			{
				return EmuSIMD::Funcs::cmple_f32x4(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x8>)
			{
				return EmuSIMD::Funcs::cmple_f32x8(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x16>)
			{
				return EmuSIMD::Funcs::cmple_f32x16(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x2>)
			{
				return EmuSIMD::Funcs::cmple_f64x2(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x4>)
			{
				return EmuSIMD::Funcs::cmple_f64x4(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x8>)
			{
				return EmuSIMD::Funcs::cmple_f64x8(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i128_generic>)
			{
				if constexpr (PerElementWidthIfGenericInt_ == 8)
				{
					if constexpr (SignedIfGenericInt_)
					{
						return EmuSIMD::Funcs::cmple_i8x16(lhs_, rhs_);
					}
					else
					{
						return EmuSIMD::Funcs::cmple_u8x16(lhs_, rhs_);
					}
				}
				else if constexpr (PerElementWidthIfGenericInt_ == 16)
				{
					if constexpr (SignedIfGenericInt_)
					{
						return EmuSIMD::Funcs::cmple_i16x8(lhs_, rhs_);
					}
					else
					{
						return EmuSIMD::Funcs::cmple_u16x8(lhs_, rhs_);
					}
				}
				else if constexpr (PerElementWidthIfGenericInt_ == 32)
				{
					if constexpr (SignedIfGenericInt_)
					{
						return EmuSIMD::Funcs::cmple_i32x4(lhs_, rhs_);
					}
					else
					{
						return EmuSIMD::Funcs::cmple_u32x4(lhs_, rhs_);
					}
				}
				else if constexpr (PerElementWidthIfGenericInt_ == 64)
				{
					if constexpr (SignedIfGenericInt_)
					{
						return EmuSIMD::Funcs::cmple_i64x2(lhs_, rhs_);
					}
					else
					{
						return EmuSIMD::Funcs::cmple_u64x2(lhs_, rhs_);
					}
				}
				else
				{
					static_assert(EmuCore::TMP::get_false<std::size_t, PerElementWidthIfGenericInt_>(), "Attempted to perform less-than-or-equal comparison (<=) of generic 128-bit integral SIMD registers via EmuSIMD helpers, but the provided per-element width is invalid.");
				}
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i256_generic>)
			{
				if constexpr (PerElementWidthIfGenericInt_ == 8)
				{
					if constexpr (SignedIfGenericInt_)
					{
						return EmuSIMD::Funcs::cmple_i8x32(lhs_, rhs_);
					}
					else
					{
						return EmuSIMD::Funcs::cmple_u8x32(lhs_, rhs_);
					}
				}
				else if constexpr (PerElementWidthIfGenericInt_ == 16)
				{
					if constexpr (SignedIfGenericInt_)
					{
						return EmuSIMD::Funcs::cmple_i16x16(lhs_, rhs_);
					}
					else
					{
						return EmuSIMD::Funcs::cmple_u16x16(lhs_, rhs_);
					}
				}
				else if constexpr (PerElementWidthIfGenericInt_ == 32)
				{
					if constexpr (SignedIfGenericInt_)
					{
						return EmuSIMD::Funcs::cmple_i32x8(lhs_, rhs_);
					}
					else
					{
						return EmuSIMD::Funcs::cmple_u32x8(lhs_, rhs_);
					}
				}
				else if constexpr (PerElementWidthIfGenericInt_ == 64)
				{
					if constexpr (SignedIfGenericInt_)
					{
						return EmuSIMD::Funcs::cmple_i64x4(lhs_, rhs_);
					}
					else
					{
						return EmuSIMD::Funcs::cmple_u64x4(lhs_, rhs_);
					}
				}
				else
				{
					static_assert(EmuCore::TMP::get_false<std::size_t, PerElementWidthIfGenericInt_>(), "Attempted to perform a less-than-or-equal comparison (<=) of generic 256-bit integral SIMD registers via EmuSIMD helpers, but the provided per-element width is invalid.");
				}
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i512_generic>)
			{
				if constexpr (PerElementWidthIfGenericInt_ == 8)
				{
					if constexpr (SignedIfGenericInt_)
					{
						return EmuSIMD::Funcs::cmple_i8x64(lhs_, rhs_);
					}
					else
					{
						return EmuSIMD::Funcs::cmple_u8x64(lhs_, rhs_);
					}
				}
				else if constexpr (PerElementWidthIfGenericInt_ == 16)
				{
					if constexpr (SignedIfGenericInt_)
					{
						return EmuSIMD::Funcs::cmple_i16x32(lhs_, rhs_);
					}
					else
					{
						return EmuSIMD::Funcs::cmple_u16x32(lhs_, rhs_);
					}
				}
				else if constexpr (PerElementWidthIfGenericInt_ == 32)
				{
					if constexpr (SignedIfGenericInt_)
					{
						return EmuSIMD::Funcs::cmple_i32x16(lhs_, rhs_);
					}
					else
					{
						return EmuSIMD::Funcs::cmple_u32x16(lhs_, rhs_);
					}
				}
				else if constexpr (PerElementWidthIfGenericInt_ == 64)
				{
					if constexpr (SignedIfGenericInt_)
					{
						return EmuSIMD::Funcs::cmple_i64x8(lhs_, rhs_);
					}
					else
					{
						return EmuSIMD::Funcs::cmple_u64x8(lhs_, rhs_);
					}
				}
				else
				{
					static_assert(EmuCore::TMP::get_false<std::size_t, PerElementWidthIfGenericInt_>(), "Attempted to perform a less-than-or-equal comparison (<=) of generic 512-bit integral SIMD registers via EmuSIMD helpers, but the provided per-element width is invalid.");
				}
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i8x16>)
			{
				return EmuSIMD::Funcs::cmple_i8x16(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i8x32>)
			{
				return EmuSIMD::Funcs::cmple_i8x32(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i8x64>)
			{
				return EmuSIMD::Funcs::cmple_i8x64(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i16x8>)
			{
				return EmuSIMD::Funcs::cmple_i16x8(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i16x16>)
			{
				return EmuSIMD::Funcs::cmple_i16x16(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i16x32>)
			{
				return EmuSIMD::Funcs::cmple_i16x32(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i32x4>)
			{
				return EmuSIMD::Funcs::cmple_i32x4(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i32x8>)
			{
				return EmuSIMD::Funcs::cmple_i32x8(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i32x16>)
			{
				return EmuSIMD::Funcs::cmple_i32x16(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i64x2>)
			{
				return EmuSIMD::Funcs::cmple_i64x2(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i64x4>)
			{
				return EmuSIMD::Funcs::cmple_i64x4(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i64x8>)
			{
				return EmuSIMD::Funcs::cmple_i64x8(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u8x16>)
			{
				return EmuSIMD::Funcs::cmple_u8x16(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u8x32>)
			{
				return EmuSIMD::Funcs::cmple_u8x32(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u8x64>)
			{
				return EmuSIMD::Funcs::cmple_u8x64(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u16x8>)
			{
				return EmuSIMD::Funcs::cmple_u16x8(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u16x16>)
			{
				return EmuSIMD::Funcs::cmple_u16x16(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u16x32>)
			{
				return EmuSIMD::Funcs::cmple_u16x32(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u32x4>)
			{
				return EmuSIMD::Funcs::cmple_u32x4(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u32x8>)
			{
				return EmuSIMD::Funcs::cmple_u32x8(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u32x16>)
			{
				return EmuSIMD::Funcs::cmple_u32x16(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u64x2>)
			{
				return EmuSIMD::Funcs::cmple_u64x2(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u64x4>)
			{
				return EmuSIMD::Funcs::cmple_u64x4(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u64x8>)
			{
				return EmuSIMD::Funcs::cmple_u64x8(lhs_, rhs_);
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform a less-than-or-equal comparison (<=) of SIMD registers using EmuSIMD helpers, but the provided Register_ type is not a supported SIMD register type.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform a less-than-or-equal comparison (<=) of SIMD registers using EmuSIMD helpers, but the provided Register_ type was not recognised as a SIMD register.");
		}
	}
#pragma endregion

#pragma region CMP_GE_FUNCS
	template<std::size_t PerElementWidthIfGenericInt_, bool SignedIfGenericInt_, class Register_>
	[[nodiscard]] inline Register_ _cmp_ge(Register_ lhs_, Register_ rhs_)
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x4>)
			{
				return EmuSIMD::Funcs::cmpge_f32x4(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x8>)
			{
				return EmuSIMD::Funcs::cmpge_f32x8(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x16>)
			{
				return EmuSIMD::Funcs::cmpge_f32x16(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x2>)
			{
				return EmuSIMD::Funcs::cmpge_f64x2(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x4>)
			{
				return EmuSIMD::Funcs::cmpge_f64x4(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x8>)
			{
				return EmuSIMD::Funcs::cmpge_f64x8(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i128_generic>)
			{
				if constexpr (PerElementWidthIfGenericInt_ == 8)
				{
					if constexpr (SignedIfGenericInt_)
					{
						return EmuSIMD::Funcs::cmpge_i8x16(lhs_, rhs_);
					}
					else
					{
						return EmuSIMD::Funcs::cmpge_u8x16(lhs_, rhs_);
					}
				}
				else if constexpr (PerElementWidthIfGenericInt_ == 16)
				{
					if constexpr (SignedIfGenericInt_)
					{
						return EmuSIMD::Funcs::cmpge_i16x8(lhs_, rhs_);
					}
					else
					{
						return EmuSIMD::Funcs::cmpge_u16x8(lhs_, rhs_);
					}
				}
				else if constexpr (PerElementWidthIfGenericInt_ == 32)
				{
					if constexpr (SignedIfGenericInt_)
					{
						return EmuSIMD::Funcs::cmpge_i32x4(lhs_, rhs_);
					}
					else
					{
						return EmuSIMD::Funcs::cmpge_u32x4(lhs_, rhs_);
					}
				}
				else if constexpr (PerElementWidthIfGenericInt_ == 64)
				{
					if constexpr (SignedIfGenericInt_)
					{
						return EmuSIMD::Funcs::cmpge_i64x2(lhs_, rhs_);
					}
					else
					{
						return EmuSIMD::Funcs::cmpge_u64x2(lhs_, rhs_);
					}
				}
				else
				{
					static_assert(EmuCore::TMP::get_false<std::size_t, PerElementWidthIfGenericInt_>(), "Attempted to perform greater-than-or-equal comparison (>=) of generic 128-bit integral SIMD registers via EmuSIMD helpers, but the provided per-element width is invalid.");
				}
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i256_generic>)
			{
				if constexpr (PerElementWidthIfGenericInt_ == 8)
				{
					if constexpr (SignedIfGenericInt_)
					{
						return EmuSIMD::Funcs::cmpge_i8x32(lhs_, rhs_);
					}
					else
					{
						return EmuSIMD::Funcs::cmpge_u8x32(lhs_, rhs_);
					}
				}
				else if constexpr (PerElementWidthIfGenericInt_ == 16)
				{
					if constexpr (SignedIfGenericInt_)
					{
						return EmuSIMD::Funcs::cmpge_i16x16(lhs_, rhs_);
					}
					else
					{
						return EmuSIMD::Funcs::cmpge_u16x16(lhs_, rhs_);
					}
				}
				else if constexpr (PerElementWidthIfGenericInt_ == 32)
				{
					if constexpr (SignedIfGenericInt_)
					{
						return EmuSIMD::Funcs::cmpge_i32x8(lhs_, rhs_);
					}
					else
					{
						return EmuSIMD::Funcs::cmpge_u32x8(lhs_, rhs_);
					}
				}
				else if constexpr (PerElementWidthIfGenericInt_ == 64)
				{
					if constexpr (SignedIfGenericInt_)
					{
						return EmuSIMD::Funcs::cmpge_i64x4(lhs_, rhs_);
					}
					else
					{
						return EmuSIMD::Funcs::cmpge_u64x4(lhs_, rhs_);
					}
				}
				else
				{
					static_assert(EmuCore::TMP::get_false<std::size_t, PerElementWidthIfGenericInt_>(), "Attempted to perform a greater-than-or-equal comparison (>=) of generic 256-bit integral SIMD registers via EmuSIMD helpers, but the provided per-element width is invalid.");
				}
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i512_generic>)
			{
				if constexpr (PerElementWidthIfGenericInt_ == 8)
				{
					if constexpr (SignedIfGenericInt_)
					{
						return EmuSIMD::Funcs::cmpge_i8x64(lhs_, rhs_);
					}
					else
					{
						return EmuSIMD::Funcs::cmpge_u8x64(lhs_, rhs_);
					}
				}
				else if constexpr (PerElementWidthIfGenericInt_ == 16)
				{
					if constexpr (SignedIfGenericInt_)
					{
						return EmuSIMD::Funcs::cmpge_i16x32(lhs_, rhs_);
					}
					else
					{
						return EmuSIMD::Funcs::cmpge_u16x32(lhs_, rhs_);
					}
				}
				else if constexpr (PerElementWidthIfGenericInt_ == 32)
				{
					if constexpr (SignedIfGenericInt_)
					{
						return EmuSIMD::Funcs::cmpge_i32x16(lhs_, rhs_);
					}
					else
					{
						return EmuSIMD::Funcs::cmpge_u32x16(lhs_, rhs_);
					}
				}
				else if constexpr (PerElementWidthIfGenericInt_ == 64)
				{
					if constexpr (SignedIfGenericInt_)
					{
						return EmuSIMD::Funcs::cmpge_i64x8(lhs_, rhs_);
					}
					else
					{
						return EmuSIMD::Funcs::cmpge_u64x8(lhs_, rhs_);
					}
				}
				else
				{
					static_assert(EmuCore::TMP::get_false<std::size_t, PerElementWidthIfGenericInt_>(), "Attempted to perform a greater-than-or-equal comparison (>=) of generic 512-bit integral SIMD registers via EmuSIMD helpers, but the provided per-element width is invalid.");
				}
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i8x16>)
			{
				return EmuSIMD::Funcs::cmpge_i8x16(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i8x32>)
			{
				return EmuSIMD::Funcs::cmpge_i8x32(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i8x64>)
			{
				return EmuSIMD::Funcs::cmpge_i8x64(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i16x8>)
			{
				return EmuSIMD::Funcs::cmpge_i16x8(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i16x16>)
			{
				return EmuSIMD::Funcs::cmpge_i16x16(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i16x32>)
			{
				return EmuSIMD::Funcs::cmpge_i16x32(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i32x4>)
			{
				return EmuSIMD::Funcs::cmpge_i32x4(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i32x8>)
			{
				return EmuSIMD::Funcs::cmpge_i32x8(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i32x16>)
			{
				return EmuSIMD::Funcs::cmpge_i32x16(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i64x2>)
			{
				return EmuSIMD::Funcs::cmpge_i64x2(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i64x4>)
			{
				return EmuSIMD::Funcs::cmpge_i64x4(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i64x8>)
			{
				return EmuSIMD::Funcs::cmpge_i64x8(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u8x16>)
			{
				return EmuSIMD::Funcs::cmpge_u8x16(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u8x32>)
			{
				return EmuSIMD::Funcs::cmpge_u8x32(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u8x64>)
			{
				return EmuSIMD::Funcs::cmpge_u8x64(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u16x8>)
			{
				return EmuSIMD::Funcs::cmpge_u16x8(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u16x16>)
			{
				return EmuSIMD::Funcs::cmpge_u16x16(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u16x32>)
			{
				return EmuSIMD::Funcs::cmpge_u16x32(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u32x4>)
			{
				return EmuSIMD::Funcs::cmpge_u32x4(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u32x8>)
			{
				return EmuSIMD::Funcs::cmpge_u32x8(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u32x16>)
			{
				return EmuSIMD::Funcs::cmpge_u32x16(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u64x2>)
			{
				return EmuSIMD::Funcs::cmpge_u64x2(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u64x4>)
			{
				return EmuSIMD::Funcs::cmpge_u64x4(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u64x8>)
			{
				return EmuSIMD::Funcs::cmpge_u64x8(lhs_, rhs_);
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform a greater-than-or-equal comparison (>=) of SIMD registers using EmuSIMD helpers, but the provided Register_ type is not a supported SIMD register type.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform a greater-than-or-equal comparison (>=) of SIMD registers using EmuSIMD helpers, but the provided Register_ type was not recognised as a SIMD register.");
		}
	}
#pragma endregion

#pragma region CMP_NEAR_HELPERS
	template<std::size_t PerElementWidthIfInt_, bool SignedIfInt_, class Register_>
	[[nodiscard]] inline Register_ _cmp_near_equal(Register_ a_, Register_ b_)
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x4>)
			{
				return EmuSIMD::Funcs::cmpnear_f32x4(a_, b_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x8>)
			{
				return EmuSIMD::Funcs::cmpnear_f32x8(a_, b_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x16>)
			{
				return EmuSIMD::Funcs::cmpnear_f32x16(a_, b_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x2>)
			{
				return EmuSIMD::Funcs::cmpnear_f64x2(a_, b_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x4>)
			{
				return EmuSIMD::Funcs::cmpnear_f64x4(a_, b_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x8>)
			{
				return EmuSIMD::Funcs::cmpnear_f64x8(a_, b_);
			}
			else if constexpr (EmuCore::TMP::is_any_comparison_true<std::is_same, register_type_uq, EmuSIMD::i128_generic, EmuSIMD::i256_generic, EmuSIMD::i512_generic>::value)
			{
				if constexpr (EmuSIMD::TMP::_assert_valid_simd_int_element_width<PerElementWidthIfInt_>())
				{
					if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i128_generic>)
					{
						if constexpr (PerElementWidthIfInt_ == 8)
						{
							if constexpr (SignedIfInt_)
							{
								return EmuSIMD::Funcs::cmpnear_i8x16(a_, b_);
							}
							else
							{
								return EmuSIMD::Funcs::cmpnear_u8x16(a_, b_);
							}
						}
						else if constexpr (PerElementWidthIfInt_ == 16)
						{
							if constexpr (SignedIfInt_)
							{
								return EmuSIMD::Funcs::cmpnear_i16x8(a_, b_);
							}
							else
							{
								return EmuSIMD::Funcs::cmpnear_u16x8(a_, b_);
							}
						}
						else if constexpr (PerElementWidthIfInt_ == 32)
						{
							if constexpr (SignedIfInt_)
							{
								return EmuSIMD::Funcs::cmpnear_i32x4(a_, b_);
							}
							else
							{
								return EmuSIMD::Funcs::cmpnear_u32x4(a_, b_);
							}
						}
						else
						{
							if constexpr (SignedIfInt_)
							{
								return EmuSIMD::Funcs::cmpnear_i64x2(a_, b_);
							}
							else
							{
								return EmuSIMD::Funcs::cmpnear_u64x2(a_, b_);
							}
						}
					}
					else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i256_generic>)
					{
						if constexpr (PerElementWidthIfInt_ == 8)
						{
							if constexpr (SignedIfInt_)
							{
								return EmuSIMD::Funcs::cmpnear_i8x32(a_, b_);
							}
							else
							{
								return EmuSIMD::Funcs::cmpnear_u8x32(a_, b_);
							}
						}
						else if constexpr (PerElementWidthIfInt_ == 16)
						{
							if constexpr (SignedIfInt_)
							{
								return EmuSIMD::Funcs::cmpnear_i16x16(a_, b_);
							}
							else
							{
								return EmuSIMD::Funcs::cmpnear_u16x16(a_, b_);
							}
						}
						else if constexpr (PerElementWidthIfInt_ == 32)
						{
							if constexpr (SignedIfInt_)
							{
								return EmuSIMD::Funcs::cmpnear_i32x8(a_, b_);
							}
							else
							{
								return EmuSIMD::Funcs::cmpnear_u32x8(a_, b_);
							}
						}
						else
						{
							if constexpr (SignedIfInt_)
							{
								return EmuSIMD::Funcs::cmpnear_i64x4(a_, b_);
							}
							else
							{
								return EmuSIMD::Funcs::cmpnear_u64x4(a_, b_);
							}
						}
					}
					else
					{
						if constexpr (PerElementWidthIfInt_ == 8)
						{
							if constexpr (SignedIfInt_)
							{
								return EmuSIMD::Funcs::cmpnear_i8x64(a_, b_);
							}
							else
							{
								return EmuSIMD::Funcs::cmpnear_u8x64(a_, b_);
							}
						}
						else if constexpr (PerElementWidthIfInt_ == 16)
						{
							if constexpr (SignedIfInt_)
							{
								return EmuSIMD::Funcs::cmpnear_i16x32(a_, b_);
							}
							else
							{
								return EmuSIMD::Funcs::cmpnear_u16x32(a_, b_);
							}
						}
						else if constexpr (PerElementWidthIfInt_ == 32)
						{
							if constexpr (SignedIfInt_)
							{
								return EmuSIMD::Funcs::cmpnear_i32x16(a_, b_);
							}
							else
							{
								return EmuSIMD::Funcs::cmpnear_u32x16(a_, b_);
							}
						}
						else
						{
							if constexpr (SignedIfInt_)
							{
								return EmuSIMD::Funcs::cmpnear_i64x8(a_, b_);
							}
							else
							{
								return EmuSIMD::Funcs::cmpnear_u64x8(a_, b_);
							}
						}
					}
				}
				else
				{
					static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to determine if the elements of two SIMD registers are near-equal via EmuSIMD helpers, but the provided PerElementWidth_ is invalid.");
				}
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i8x16>)
			{
				return EmuSIMD::Funcs::cmpnear_i8x16(a_, b_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i8x32>)
			{
				return EmuSIMD::Funcs::cmpnear_i8x32(a_, b_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i8x64>)
			{
				return EmuSIMD::Funcs::cmpnear_i8x64(a_, b_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u8x16>)
			{
				return EmuSIMD::Funcs::cmpnear_u8x16(a_, b_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u8x32>)
			{
				return EmuSIMD::Funcs::cmpnear_u8x32(a_, b_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u8x64>)
			{
				return EmuSIMD::Funcs::cmpnear_u8x64(a_, b_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i16x8>)
			{
				return EmuSIMD::Funcs::cmpnear_i16x8(a_, b_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i16x16>)
			{
				return EmuSIMD::Funcs::cmpnear_i16x16(a_, b_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i16x32>)
			{
				return EmuSIMD::Funcs::cmpnear_i16x32(a_, b_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u16x8>)
			{
				return EmuSIMD::Funcs::cmpnear_u16x8(a_, b_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u16x16>)
			{
				return EmuSIMD::Funcs::cmpnear_u16x16(a_, b_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u16x32>)
			{
				return EmuSIMD::Funcs::cmpnear_u16x32(a_, b_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i32x4>)
			{
				return EmuSIMD::Funcs::cmpnear_i32x4(a_, b_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i32x8>)
			{
				return EmuSIMD::Funcs::cmpnear_i32x8(a_, b_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i32x16>)
			{
				return EmuSIMD::Funcs::cmpnear_i32x16(a_, b_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u32x4>)
			{
				return EmuSIMD::Funcs::cmpnear_u32x4(a_, b_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u32x8>)
			{
				return EmuSIMD::Funcs::cmpnear_u32x8(a_, b_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u32x16>)
			{
				return EmuSIMD::Funcs::cmpnear_u32x16(a_, b_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i64x2>)
			{
				return EmuSIMD::Funcs::cmpnear_i64x2(a_, b_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i64x4>)
			{
				return EmuSIMD::Funcs::cmpnear_i64x4(a_, b_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i64x8>)
			{
				return EmuSIMD::Funcs::cmpnear_i64x8(a_, b_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u64x2>)
			{
				return EmuSIMD::Funcs::cmpnear_u64x2(a_, b_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u64x4>)
			{
				return EmuSIMD::Funcs::cmpnear_u64x4(a_, b_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u64x8>)
			{
				return EmuSIMD::Funcs::cmpnear_u64x8(a_, b_);
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to determine if the elements of two SIMD registers are near-equal via EmuSIMD registers, but the passed Register_ type is not supported for this operation.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to determine if the elements of two SIMD registers are near-equal via EmuSIMD helpers, but the provided Register_ type is not recognised as a supported SIMD register.");
		}
	}

	template<std::size_t PerElementWidthIfInt_, bool SignedIfInt_, class Register_>
	[[nodiscard]] inline Register_ _cmp_near_equal(Register_ a_, Register_ b_, Register_ epsilon_)
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x4>)
			{
				return EmuSIMD::Funcs::cmpnear_f32x4(a_, b_, epsilon_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x8>)
			{
				return EmuSIMD::Funcs::cmpnear_f32x8(a_, b_, epsilon_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x16>)
			{
				return EmuSIMD::Funcs::cmpnear_f32x16(a_, b_, epsilon_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x2>)
			{
				return EmuSIMD::Funcs::cmpnear_f64x2(a_, b_, epsilon_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x4>)
			{
				return EmuSIMD::Funcs::cmpnear_f64x4(a_, b_, epsilon_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x8>)
			{
				return EmuSIMD::Funcs::cmpnear_f64x8(a_, b_, epsilon_);
			}
			else if constexpr (EmuCore::TMP::is_any_comparison_true<std::is_same, register_type_uq, EmuSIMD::i128_generic, EmuSIMD::i256_generic, EmuSIMD::i512_generic>::value)
			{
				if constexpr (EmuSIMD::TMP::_assert_valid_simd_int_element_width<PerElementWidthIfInt_>())
				{
					if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i128_generic>)
					{
						if constexpr (PerElementWidthIfInt_ == 8)
						{
							if constexpr (SignedIfInt_)
							{
								return EmuSIMD::Funcs::cmpnear_i8x16(a_, b_, epsilon_);
							}
							else
							{
								return EmuSIMD::Funcs::cmpnear_u8x16(a_, b_, epsilon_);
							}
						}
						else if constexpr (PerElementWidthIfInt_ == 16)
						{
							if constexpr (SignedIfInt_)
							{
								return EmuSIMD::Funcs::cmpnear_i16x8(a_, b_, epsilon_);
							}
							else
							{
								return EmuSIMD::Funcs::cmpnear_u16x8(a_, b_, epsilon_);
							}
						}
						else if constexpr (PerElementWidthIfInt_ == 32)
						{
							if constexpr (SignedIfInt_)
							{
								return EmuSIMD::Funcs::cmpnear_i32x4(a_, b_, epsilon_);
							}
							else
							{
								return EmuSIMD::Funcs::cmpnear_u32x4(a_, b_, epsilon_);
							}
						}
						else
						{
							if constexpr (SignedIfInt_)
							{
								return EmuSIMD::Funcs::cmpnear_i64x2(a_, b_, epsilon_);
							}
							else
							{
								return EmuSIMD::Funcs::cmpnear_u64x2(a_, b_, epsilon_);
							}
						}
					}
					else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i256_generic>)
					{
						if constexpr (PerElementWidthIfInt_ == 8)
						{
							if constexpr (SignedIfInt_)
							{
								return EmuSIMD::Funcs::cmpnear_i8x32(a_, b_, epsilon_);
							}
							else
							{
								return EmuSIMD::Funcs::cmpnear_u8x32(a_, b_, epsilon_);
							}
						}
						else if constexpr (PerElementWidthIfInt_ == 16)
						{
							if constexpr (SignedIfInt_)
							{
								return EmuSIMD::Funcs::cmpnear_i16x16(a_, b_, epsilon_);
							}
							else
							{
								return EmuSIMD::Funcs::cmpnear_u16x16(a_, b_, epsilon_);
							}
						}
						else if constexpr (PerElementWidthIfInt_ == 32)
						{
							if constexpr (SignedIfInt_)
							{
								return EmuSIMD::Funcs::cmpnear_i32x8(a_, b_, epsilon_);
							}
							else
							{
								return EmuSIMD::Funcs::cmpnear_u32x8(a_, b_, epsilon_);
							}
						}
						else
						{
							if constexpr (SignedIfInt_)
							{
								return EmuSIMD::Funcs::cmpnear_i64x4(a_, b_, epsilon_);
							}
							else
							{
								return EmuSIMD::Funcs::cmpnear_u64x4(a_, b_, epsilon_);
							}
						}
					}
					else
					{
						if constexpr (PerElementWidthIfInt_ == 8)
						{
							if constexpr (SignedIfInt_)
							{
								return EmuSIMD::Funcs::cmpnear_i8x64(a_, b_, epsilon_);
							}
							else
							{
								return EmuSIMD::Funcs::cmpnear_u8x64(a_, b_, epsilon_);
							}
						}
						else if constexpr (PerElementWidthIfInt_ == 16)
						{
							if constexpr (SignedIfInt_)
							{
								return EmuSIMD::Funcs::cmpnear_i16x32(a_, b_, epsilon_);
							}
							else
							{
								return EmuSIMD::Funcs::cmpnear_u16x32(a_, b_, epsilon_);
							}
						}
						else if constexpr (PerElementWidthIfInt_ == 32)
						{
							if constexpr (SignedIfInt_)
							{
								return EmuSIMD::Funcs::cmpnear_i32x16(a_, b_, epsilon_);
							}
							else
							{
								return EmuSIMD::Funcs::cmpnear_u32x16(a_, b_, epsilon_);
							}
						}
						else
						{
							if constexpr (SignedIfInt_)
							{
								return EmuSIMD::Funcs::cmpnear_i64x8(a_, b_, epsilon_);
							}
							else
							{
								return EmuSIMD::Funcs::cmpnear_u64x8(a_, b_, epsilon_);
							}
						}
					}
				}
				else
				{
					static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to determine if the elements of two SIMD registers are near-equal via EmuSIMD helpers, but the provided PerElementWidth_ is invalid.");
				}
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i8x16>)
			{
				return EmuSIMD::Funcs::cmpnear_i8x16(a_, b_, epsilon_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i8x32>)
			{
				return EmuSIMD::Funcs::cmpnear_i8x32(a_, b_, epsilon_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i8x64>)
			{
				return EmuSIMD::Funcs::cmpnear_i8x64(a_, b_, epsilon_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u8x16>)
			{
				return EmuSIMD::Funcs::cmpnear_u8x16(a_, b_, epsilon_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u8x32>)
			{
				return EmuSIMD::Funcs::cmpnear_u8x32(a_, b_, epsilon_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u8x64>)
			{
				return EmuSIMD::Funcs::cmpnear_u8x64(a_, b_, epsilon_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i16x8>)
			{
				return EmuSIMD::Funcs::cmpnear_i16x8(a_, b_, epsilon_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i16x16>)
			{
				return EmuSIMD::Funcs::cmpnear_i16x16(a_, b_, epsilon_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i16x32>)
			{
				return EmuSIMD::Funcs::cmpnear_i16x32(a_, b_, epsilon_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u16x8>)
			{
				return EmuSIMD::Funcs::cmpnear_u16x8(a_, b_, epsilon_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u16x16>)
			{
				return EmuSIMD::Funcs::cmpnear_u16x16(a_, b_, epsilon_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u16x32>)
			{
				return EmuSIMD::Funcs::cmpnear_u16x32(a_, b_, epsilon_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i32x4>)
			{
				return EmuSIMD::Funcs::cmpnear_i32x4(a_, b_, epsilon_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i32x8>)
			{
				return EmuSIMD::Funcs::cmpnear_i32x8(a_, b_, epsilon_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i32x16>)
			{
				return EmuSIMD::Funcs::cmpnear_i32x16(a_, b_, epsilon_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u32x4>)
			{
				return EmuSIMD::Funcs::cmpnear_u32x4(a_, b_, epsilon_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u32x8>)
			{
				return EmuSIMD::Funcs::cmpnear_u32x8(a_, b_, epsilon_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u32x16>)
			{
				return EmuSIMD::Funcs::cmpnear_u32x16(a_, b_, epsilon_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i64x2>)
			{
				return EmuSIMD::Funcs::cmpnear_i64x2(a_, b_, epsilon_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i64x4>)
			{
				return EmuSIMD::Funcs::cmpnear_i64x4(a_, b_, epsilon_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i64x8>)
			{
				return EmuSIMD::Funcs::cmpnear_i64x8(a_, b_, epsilon_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u64x2>)
			{
				return EmuSIMD::Funcs::cmpnear_u64x2(a_, b_, epsilon_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u64x4>)
			{
				return EmuSIMD::Funcs::cmpnear_u64x4(a_, b_, epsilon_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u64x8>)
			{
				return EmuSIMD::Funcs::cmpnear_u64x8(a_, b_, epsilon_);
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to determine if the elements of two SIMD registers are near-equal via EmuSIMD helpers, but the passed Register_ type is not supported for this operation.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to determine if the elements of two SIMD registers are near-equal via EmuSIMD helpers, but the provided Register_ type is not recognised as a supported SIMD register.");
		}
	}
#pragma endregion
}

#endif
