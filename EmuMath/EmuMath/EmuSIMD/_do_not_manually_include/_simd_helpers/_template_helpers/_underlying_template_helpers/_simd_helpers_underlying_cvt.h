#ifndef EMU_SIMD_COMMON_UNDERLYING_SIMD_CVT_INCLUDES_H_INC_
#define EMU_SIMD_COMMON_UNDERLYING_SIMD_CVT_INCLUDES_H_INC_ 1

#include "_common_underlying_simd_template_helper_includes.h"
#include "_simd_helpers_underlying_cast.h"
#include "../../../../../EmuCore/TMPHelpers/Values.h"

namespace EmuSIMD::_underlying_simd_helpers
{
#pragma region CVT_F32
	template<class ToRegister_, std::size_t OutPerElementWidthIfInt_, bool OutSignedIfInt_>
	[[nodiscard]] inline ToRegister_ _cvt_f32x4(EmuSIMD::f32x4_arg from_)
	{
		using to_uq = EmuCore::TMP::remove_ref_cv_t<ToRegister_>;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<to_uq>)
		{
			if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x4>)
			{
				return from_;
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x8>)
			{
				return EmuSIMD::Funcs::cvt_f32x4_f32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x16>)
			{
				return EmuSIMD::Funcs::cvt_f32x4_f32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x2>)
			{
				return EmuSIMD::Funcs::cvt_f32x4_f64x2(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x4>)
			{
				return EmuSIMD::Funcs::cvt_f32x4_f64x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x8>)
			{
				return EmuSIMD::Funcs::cvt_f32x4_f64x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i128_generic>)
			{
				if constexpr (OutPerElementWidthIfInt_ == 8)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_f32x4_i8x16(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_f32x4_u8x16(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 16)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_f32x4_i16x8(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_f32x4_u16x8(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 32)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_f32x4_i32x4(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_f32x4_u32x4(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 64)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_f32x4_i64x2(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_f32x4_u64x2(from_);
					}
				}
				else
				{
					static_assert
					(
						EmuCore::TMP::get_false<OutPerElementWidthIfInt_>(),
						"Attempted to convert a EmuSIMD::f32x4 register to i128_generic via EmuSIMD helpers, but the provided width per element is invalid. Only 8, 16, 32, and 64 are valid values."
					);
				}
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i256_generic>)
			{
				if constexpr (OutPerElementWidthIfInt_ == 8)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_f32x4_i8x32(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_f32x4_u8x32(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 16)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_f32x4_i16x16(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_f32x4_u16x16(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 32)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_f32x4_i32x8(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_f32x4_u32x8(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 64)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_f32x4_i64x4(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_f32x4_u64x4(from_);
					}
				}
				else
				{
					static_assert
					(
						EmuCore::TMP::get_false<OutPerElementWidthIfInt_>(),
						"Attempted to convert a EmuSIMD::f32x4 register to i256_generic via EmuSIMD helpers, but the provided width per element is invalid. Only 8, 16, 32, and 64 are valid values."
					);
				}
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i512_generic>)
			{
				if constexpr (OutPerElementWidthIfInt_ == 8)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_f32x4_i8x64(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_f32x4_u8x64(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 16)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_f32x4_i16x32(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_f32x4_u16x32(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 32)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_f32x4_i32x16(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_f32x4_u32x16(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 64)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_f32x4_i64x8(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_f32x4_u64x8(from_);
					}
				}
				else
				{
					static_assert
					(
						EmuCore::TMP::get_false<OutPerElementWidthIfInt_>(),
						"Attempted to convert a EmuSIMD::f32x4 register to i512_generic via EmuSIMD helpers, but the provided width per element is invalid. Only 8, 16, 32, and 64 are valid values."
					);
				}
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i8x16>)
			{
				return EmuSIMD::Funcs::cvt_f32x4_i8x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u8x16>)
			{
				return EmuSIMD::Funcs::cvt_f32x4_u8x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i8x32>)
			{
				return EmuSIMD::Funcs::cvt_f32x4_i8x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u8x32>)
			{
				return EmuSIMD::Funcs::cvt_f32x4_u8x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i8x64>)
			{
				return EmuSIMD::Funcs::cvt_f32x4_i8x64(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u8x64>)
			{
				return EmuSIMD::Funcs::cvt_f32x4_u8x64(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i16x8>)
			{
				return EmuSIMD::Funcs::cvt_f32x4_i16x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u16x8>)
			{
				return EmuSIMD::Funcs::cvt_f32x4_u16x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i16x16>)
			{
				return EmuSIMD::Funcs::cvt_f32x4_i16x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u16x16>)
			{
				return EmuSIMD::Funcs::cvt_f32x4_u16x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i16x32>)
			{
				return EmuSIMD::Funcs::cvt_f32x4_i16x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u16x32>)
			{
				return EmuSIMD::Funcs::cvt_f32x4_u16x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i32x4>)
			{
				return EmuSIMD::Funcs::cvt_f32x4_i32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u32x4>)
			{
				return EmuSIMD::Funcs::cvt_f32x4_u32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i32x8>)
			{
				return EmuSIMD::Funcs::cvt_f32x4_i32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u32x8>)
			{
				return EmuSIMD::Funcs::cvt_f32x4_u32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i32x16>)
			{
				return EmuSIMD::Funcs::cvt_f32x4_i32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u32x16>)
			{
				return EmuSIMD::Funcs::cvt_f32x4_u32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i64x2>)
			{
				return EmuSIMD::Funcs::cvt_f32x4_i64x2(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u64x2>)
			{
				return EmuSIMD::Funcs::cvt_f32x4_u64x2(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i64x4>)
			{
				return EmuSIMD::Funcs::cvt_f32x4_i64x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u64x4>)
			{
				return EmuSIMD::Funcs::cvt_f32x4_u64x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i64x8>)
			{
				return EmuSIMD::Funcs::cvt_f32x4_i64x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u64x8>)
			{
				return EmuSIMD::Funcs::cvt_f32x4_u64x8(from_);
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<ToRegister_>(), "Attempted to convert a EmuSIMD::f32x4 register via EmuSIMD helpers, but the provided SIMD register to convert to is not supported for this operation.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<ToRegister_>(), "Attempted to convert a EmuSIMD::f32x4 register via EmuSIMD helpers, but the provided register to convert to is not recognisd as a supported SIMD register.");
		}
	}

	template<class ToRegister_, std::size_t OutPerElementWidthIfInt_, bool OutSignedIfInt_>
	[[nodiscard]] inline ToRegister_ _cvt_f32x8(EmuSIMD::f32x8_arg from_)
	{
		using to_uq = EmuCore::TMP::remove_ref_cv_t<ToRegister_>;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<to_uq>)
		{
			if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x4>)
			{
				return EmuSIMD::Funcs::cvt_f32x8_f32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x8>)
			{
				return from_;
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x16>)
			{
				return EmuSIMD::Funcs::cvt_f32x8_f32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x2>)
			{
				return EmuSIMD::Funcs::cvt_f32x8_f64x2(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x4>)
			{
				return EmuSIMD::Funcs::cvt_f32x8_f64x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x8>)
			{
				return EmuSIMD::Funcs::cvt_f32x8_f64x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i128_generic>)
			{
				if constexpr (OutPerElementWidthIfInt_ == 8)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_f32x8_i8x16(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_f32x8_u8x16(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 16)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_f32x8_i16x8(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_f32x8_u16x8(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 32)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_f32x8_i32x4(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_f32x8_u32x4(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 64)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_f32x8_i64x2(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_f32x8_u64x2(from_);
					}
				}
				else
				{
					static_assert
					(
						EmuCore::TMP::get_false<OutPerElementWidthIfInt_>(),
						"Attempted to convert a EmuSIMD::f32x8 register to i128_generic via EmuSIMD helpers, but the provided width per element is invalid. Only 8, 16, 32, and 64 are valid values."
					);
				}
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i256_generic>)
			{
				if constexpr (OutPerElementWidthIfInt_ == 8)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_f32x8_i8x32(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_f32x8_u8x32(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 16)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_f32x8_i16x16(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_f32x8_u16x16(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 32)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_f32x8_i32x8(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_f32x8_u32x8(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 64)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_f32x8_i64x4(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_f32x8_u64x4(from_);
					}
				}
				else
				{
					static_assert
					(
						EmuCore::TMP::get_false<OutPerElementWidthIfInt_>(),
						"Attempted to convert a EmuSIMD::f32x8 register to i256_generic via EmuSIMD helpers, but the provided width per element is invalid. Only 8, 16, 32, and 64 are valid values."
					);
				}
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i512_generic>)
			{
				if constexpr (OutPerElementWidthIfInt_ == 8)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_f32x8_i8x64(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_f32x8_u8x64(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 16)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_f32x8_i16x32(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_f32x8_u16x32(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 32)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_f32x8_i32x16(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_f32x8_u32x16(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 64)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_f32x8_i64x8(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_f32x8_u64x8(from_);
					}
				}
				else
				{
					static_assert
					(
						EmuCore::TMP::get_false<OutPerElementWidthIfInt_>(),
						"Attempted to convert a EmuSIMD::f32x8 register to i512_generic via EmuSIMD helpers, but the provided width per element is invalid. Only 8, 16, 32, and 64 are valid values."
					);
				}
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i8x16>)
			{
				return EmuSIMD::Funcs::cvt_f32x8_i8x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u8x16>)
			{
				return EmuSIMD::Funcs::cvt_f32x8_u8x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i8x32>)
			{
				return EmuSIMD::Funcs::cvt_f32x8_i8x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u8x32>)
			{
				return EmuSIMD::Funcs::cvt_f32x8_u8x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i8x64>)
			{
				return EmuSIMD::Funcs::cvt_f32x8_i8x64(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u8x64>)
			{
				return EmuSIMD::Funcs::cvt_f32x8_u8x64(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i16x8>)
			{
				return EmuSIMD::Funcs::cvt_f32x8_i16x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u16x8>)
			{
				return EmuSIMD::Funcs::cvt_f32x8_u16x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i16x16>)
			{
				return EmuSIMD::Funcs::cvt_f32x8_i16x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u16x16>)
			{
				return EmuSIMD::Funcs::cvt_f32x8_u16x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i16x32>)
			{
				return EmuSIMD::Funcs::cvt_f32x8_i16x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u16x32>)
			{
				return EmuSIMD::Funcs::cvt_f32x8_u16x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i32x4>)
			{
				return EmuSIMD::Funcs::cvt_f32x8_i32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u32x4>)
			{
				return EmuSIMD::Funcs::cvt_f32x8_u32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i32x8>)
			{
				return EmuSIMD::Funcs::cvt_f32x8_i32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u32x8>)
			{
				return EmuSIMD::Funcs::cvt_f32x8_u32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i32x16>)
			{
				return EmuSIMD::Funcs::cvt_f32x8_i32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u32x16>)
			{
				return EmuSIMD::Funcs::cvt_f32x8_u32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i64x2>)
			{
				return EmuSIMD::Funcs::cvt_f32x8_i64x2(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u64x2>)
			{
				return EmuSIMD::Funcs::cvt_f32x8_u64x2(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i64x4>)
			{
				return EmuSIMD::Funcs::cvt_f32x8_i64x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u64x4>)
			{
				return EmuSIMD::Funcs::cvt_f32x8_u64x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i64x8>)
			{
				return EmuSIMD::Funcs::cvt_f32x8_i64x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u64x8>)
			{
				return EmuSIMD::Funcs::cvt_f32x8_u64x8(from_);
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<ToRegister_>(), "Attempted to convert a EmuSIMD::f32x8 register via EmuSIMD helpers, but the provided SIMD register to convert to is not supported for this operation.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<ToRegister_>(), "Attempted to convert a EmuSIMD::f32x8 register via EmuSIMD helpers, but the provided register to convert to is not recognisd as a supported SIMD register.");
		}
	}

	template<class ToRegister_, std::size_t OutPerElementWidthIfInt_, bool OutSignedIfInt_>
	[[nodiscard]] inline ToRegister_ _cvt_f32x16(EmuSIMD::f32x16_arg from_)
	{
		using to_uq = EmuCore::TMP::remove_ref_cv_t<ToRegister_>;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<to_uq>)
		{
			if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x4>)
			{
				return EmuSIMD::Funcs::cvt_f32x16_f32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x8>)
			{
				return EmuSIMD::Funcs::cvt_f32x16_f32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x16>)
			{
				return from_;
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x2>)
			{
				return EmuSIMD::Funcs::cvt_f32x16_f64x2(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x4>)
			{
				return EmuSIMD::Funcs::cvt_f32x16_f64x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x8>)
			{
				return EmuSIMD::Funcs::cvt_f32x16_f64x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i128_generic>)
			{
				if constexpr (OutPerElementWidthIfInt_ == 8)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_f32x16_i8x16(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_f32x16_u8x16(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 16)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_f32x16_i16x8(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_f32x16_u16x8(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 32)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_f32x16_i32x4(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_f32x16_u32x4(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 64)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_f32x16_i64x2(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_f32x16_u64x2(from_);
					}
				}
				else
				{
					static_assert
					(
						EmuCore::TMP::get_false<OutPerElementWidthIfInt_>(),
						"Attempted to convert a EmuSIMD::f32x8 register to i128_generic via EmuSIMD helpers, but the provided width per element is invalid. Only 8, 16, 32, and 64 are valid values."
					);
				}
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i256_generic>)
			{
				if constexpr (OutPerElementWidthIfInt_ == 8)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_f32x16_i8x32(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_f32x16_u8x32(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 16)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_f32x16_i16x16(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_f32x16_u16x16(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 32)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_f32x16_i32x8(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_f32x16_u32x8(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 64)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_f32x16_i64x4(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_f32x16_u64x4(from_);
					}
				}
				else
				{
					static_assert
					(
						EmuCore::TMP::get_false<OutPerElementWidthIfInt_>(),
						"Attempted to convert a EmuSIMD::f32x8 register to i256_generic via EmuSIMD helpers, but the provided width per element is invalid. Only 8, 16, 32, and 64 are valid values."
					);
				}
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i512_generic>)
			{
				if constexpr (OutPerElementWidthIfInt_ == 8)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_f32x16_i8x64(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_f32x16_u8x64(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 16)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_f32x16_i16x32(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_f32x16_u16x32(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 32)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_f32x16_i32x16(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_f32x16_u32x16(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 64)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_f32x16_i64x8(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_f32x16_u64x8(from_);
					}
				}
				else
				{
					static_assert
					(
						EmuCore::TMP::get_false<OutPerElementWidthIfInt_>(),
						"Attempted to convert a EmuSIMD::f32x8 register to i512_generic via EmuSIMD helpers, but the provided width per element is invalid. Only 8, 16, 32, and 64 are valid values."
					);
				}
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i8x16>)
			{
				return EmuSIMD::Funcs::cvt_f32x16_i8x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u8x16>)
			{
				return EmuSIMD::Funcs::cvt_f32x16_u8x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i8x32>)
			{
				return EmuSIMD::Funcs::cvt_f32x16_i8x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u8x32>)
			{
				return EmuSIMD::Funcs::cvt_f32x16_u8x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i8x64>)
			{
				return EmuSIMD::Funcs::cvt_f32x16_i8x64(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u8x64>)
			{
				return EmuSIMD::Funcs::cvt_f32x16_u8x64(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i16x8>)
			{
				return EmuSIMD::Funcs::cvt_f32x16_i16x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u16x8>)
			{
				return EmuSIMD::Funcs::cvt_f32x16_u16x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i16x16>)
			{
				return EmuSIMD::Funcs::cvt_f32x16_i16x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u16x16>)
			{
				return EmuSIMD::Funcs::cvt_f32x16_u16x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i16x32>)
			{
				return EmuSIMD::Funcs::cvt_f32x16_i16x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u16x32>)
			{
				return EmuSIMD::Funcs::cvt_f32x16_u16x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i32x4>)
			{
				return EmuSIMD::Funcs::cvt_f32x16_i32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u32x4>)
			{
				return EmuSIMD::Funcs::cvt_f32x16_u32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i32x8>)
			{
				return EmuSIMD::Funcs::cvt_f32x16_i32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u32x8>)
			{
				return EmuSIMD::Funcs::cvt_f32x16_u32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i32x16>)
			{
				return EmuSIMD::Funcs::cvt_f32x16_i32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u32x16>)
			{
				return EmuSIMD::Funcs::cvt_f32x16_u32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i64x2>)
			{
				return EmuSIMD::Funcs::cvt_f32x16_i64x2(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u64x2>)
			{
				return EmuSIMD::Funcs::cvt_f32x16_u64x2(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i64x4>)
			{
				return EmuSIMD::Funcs::cvt_f32x16_i64x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u64x4>)
			{
				return EmuSIMD::Funcs::cvt_f32x16_u64x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i64x8>)
			{
				return EmuSIMD::Funcs::cvt_f32x16_i64x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u64x8>)
			{
				return EmuSIMD::Funcs::cvt_f32x16_u64x8(from_);
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<ToRegister_>(), "Attempted to convert a EmuSIMD::f32x8 register via EmuSIMD helpers, but the provided SIMD register to convert to is not supported for this operation.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<ToRegister_>(), "Attempted to convert a EmuSIMD::f32x8 register via EmuSIMD helpers, but the provided register to convert to is not recognisd as a supported SIMD register.");
		}
	}
#pragma endregion

#pragma region CVT_F64
	template<class ToRegister_, std::size_t OutPerElementWidthIfInt_, bool OutSignedIfInt_>
	[[nodiscard]] inline ToRegister_ _cvt_f64x2(EmuSIMD::f64x2_arg from_)
	{
		using to_uq = EmuCore::TMP::remove_ref_cv_t<ToRegister_>;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<to_uq>)
		{
			if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x4>)
			{
				return EmuSIMD::Funcs::cvt_f64x2_f32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x8>)
			{
				return EmuSIMD::Funcs::cvt_f64x2_f32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x16>)
			{
				return EmuSIMD::Funcs::cvt_f64x2_f32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x2>)
			{
				return from_;
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x4>)
			{
				return EmuSIMD::Funcs::cvt_f64x2_f64x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x8>)
			{
				return EmuSIMD::Funcs::cvt_f64x2_f64x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i128_generic>)
			{
				if constexpr (OutPerElementWidthIfInt_ == 8)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_f64x2_i8x16(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_f64x2_u8x16(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 16)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_f64x2_i16x8(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_f64x2_u16x8(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 32)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_f64x2_i32x4(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_f64x2_u32x4(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 64)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_f64x2_i64x2(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_f64x2_u64x2(from_);
					}
				}
				else
				{
					static_assert
					(
						EmuCore::TMP::get_false<OutPerElementWidthIfInt_>(),
						"Attempted to convert a EmuSIMD::f64x2 register to i128_generic via EmuSIMD helpers, but the provided width per element is invalid. Only 8, 16, 32, and 64 are valid values."
					);
				}
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i256_generic>)
			{
				if constexpr (OutPerElementWidthIfInt_ == 8)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_f64x2_i8x32(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_f64x2_u8x32(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 16)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_f64x2_i16x16(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_f64x2_u16x16(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 32)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_f64x2_i32x8(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_f64x2_u32x8(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 64)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_f64x2_i64x4(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_f64x2_u64x4(from_);
					}
				}
				else
				{
					static_assert
					(
						EmuCore::TMP::get_false<OutPerElementWidthIfInt_>(),
						"Attempted to convert a EmuSIMD::f64x2 register to i256_generic via EmuSIMD helpers, but the provided width per element is invalid. Only 8, 16, 32, and 64 are valid values."
					);
				}
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i512_generic>)
			{
				if constexpr (OutPerElementWidthIfInt_ == 8)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_f64x2_i8x64(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_f64x2_u8x64(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 16)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_f64x2_i16x32(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_f64x2_u16x32(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 32)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_f64x2_i32x16(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_f64x2_u32x16(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 64)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_f64x2_i64x8(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_f64x2_u64x8(from_);
					}
				}
				else
				{
					static_assert
					(
						EmuCore::TMP::get_false<OutPerElementWidthIfInt_>(),
						"Attempted to convert a EmuSIMD::f64x2 register to i512_generic via EmuSIMD helpers, but the provided width per element is invalid. Only 8, 16, 32, and 64 are valid values."
					);
				}
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i8x16>)
			{
				return EmuSIMD::Funcs::cvt_f64x2_i8x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u8x16>)
			{
				return EmuSIMD::Funcs::cvt_f64x2_u8x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i8x32>)
			{
				return EmuSIMD::Funcs::cvt_f64x2_i8x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u8x32>)
			{
				return EmuSIMD::Funcs::cvt_f64x2_u8x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i8x64>)
			{
				return EmuSIMD::Funcs::cvt_f64x2_i8x64(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u8x64>)
			{
				return EmuSIMD::Funcs::cvt_f64x2_u8x64(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i16x8>)
			{
				return EmuSIMD::Funcs::cvt_f64x2_i16x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u16x8>)
			{
				return EmuSIMD::Funcs::cvt_f64x2_u16x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i16x16>)
			{
				return EmuSIMD::Funcs::cvt_f64x2_i16x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u16x16>)
			{
				return EmuSIMD::Funcs::cvt_f64x2_u16x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i16x32>)
			{
				return EmuSIMD::Funcs::cvt_f64x2_i16x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u16x32>)
			{
				return EmuSIMD::Funcs::cvt_f64x2_u16x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i32x4>)
			{
				return EmuSIMD::Funcs::cvt_f64x2_i32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u32x4>)
			{
				return EmuSIMD::Funcs::cvt_f64x2_u32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i32x8>)
			{
				return EmuSIMD::Funcs::cvt_f64x2_i32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u32x8>)
			{
				return EmuSIMD::Funcs::cvt_f64x2_u32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i32x16>)
			{
				return EmuSIMD::Funcs::cvt_f64x2_i32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u32x16>)
			{
				return EmuSIMD::Funcs::cvt_f64x2_u32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i64x2>)
			{
				return EmuSIMD::Funcs::cvt_f64x2_i64x2(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u64x2>)
			{
				return EmuSIMD::Funcs::cvt_f64x2_u64x2(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i64x4>)
			{
				return EmuSIMD::Funcs::cvt_f64x2_i64x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u64x4>)
			{
				return EmuSIMD::Funcs::cvt_f64x2_u64x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i64x8>)
			{
				return EmuSIMD::Funcs::cvt_f64x2_i64x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u64x8>)
			{
				return EmuSIMD::Funcs::cvt_f64x2_u64x8(from_);
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<ToRegister_>(), "Attempted to convert a EmuSIMD::f64x2 register via EmuSIMD helpers, but the provided SIMD register to convert to is not supported for this operation.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<ToRegister_>(), "Attempted to convert a EmuSIMD::f64x2 register via EmuSIMD helpers, but the provided register to convert to is not recognisd as a supported SIMD register.");
		}
	}

	template<class ToRegister_, std::size_t OutPerElementWidthIfInt_, bool OutSignedIfInt_>
	[[nodiscard]] inline ToRegister_ _cvt_f64x4(EmuSIMD::f64x4_arg from_)
	{
		using to_uq = EmuCore::TMP::remove_ref_cv_t<ToRegister_>;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<to_uq>)
		{
			if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x4>)
			{
				return EmuSIMD::Funcs::cvt_f64x4_f32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x8>)
			{
				return EmuSIMD::Funcs::cvt_f64x4_f32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x16>)
			{
				return EmuSIMD::Funcs::cvt_f64x4_f32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x2>)
			{
				return EmuSIMD::Funcs::cvt_f64x4_f64x2(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x4>)
			{
				return from_;
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x8>)
			{
				return EmuSIMD::Funcs::cvt_f64x4_f64x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i128_generic>)
			{
				if constexpr (OutPerElementWidthIfInt_ == 8)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_f64x4_i8x16(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_f64x4_u8x16(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 16)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_f64x4_i16x8(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_f64x4_u16x8(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 32)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_f64x4_i32x4(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_f64x4_u32x4(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 64)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_f64x4_i64x2(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_f64x4_u64x2(from_);
					}
				}
				else
				{
					static_assert
					(
						EmuCore::TMP::get_false<OutPerElementWidthIfInt_>(),
						"Attempted to convert a EmuSIMD::f64x4 register to i128_generic via EmuSIMD helpers, but the provided width per element is invalid. Only 8, 16, 32, and 64 are valid values."
					);
				}
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i256_generic>)
			{
				if constexpr (OutPerElementWidthIfInt_ == 8)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_f64x4_i8x32(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_f64x4_u8x32(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 16)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_f64x4_i16x16(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_f64x4_u16x16(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 32)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_f64x4_i32x8(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_f64x4_u32x8(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 64)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_f64x4_i64x4(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_f64x4_u64x4(from_);
					}
				}
				else
				{
					static_assert
					(
						EmuCore::TMP::get_false<OutPerElementWidthIfInt_>(),
						"Attempted to convert a EmuSIMD::f64x4 register to i256_generic via EmuSIMD helpers, but the provided width per element is invalid. Only 8, 16, 32, and 64 are valid values."
					);
				}
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i512_generic>)
			{
				if constexpr (OutPerElementWidthIfInt_ == 8)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_f64x4_i8x64(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_f64x4_u8x64(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 16)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_f64x4_i16x32(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_f64x4_u16x32(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 32)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_f64x4_i32x16(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_f64x4_u32x16(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 64)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_f64x4_i64x8(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_f64x4_u64x8(from_);
					}
				}
				else
				{
					static_assert
					(
						EmuCore::TMP::get_false<OutPerElementWidthIfInt_>(),
						"Attempted to convert a EmuSIMD::f64x4 register to i512_generic via EmuSIMD helpers, but the provided width per element is invalid. Only 8, 16, 32, and 64 are valid values."
					);
				}
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i8x16>)
			{
				return EmuSIMD::Funcs::cvt_f64x4_i8x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u8x16>)
			{
				return EmuSIMD::Funcs::cvt_f64x4_u8x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i8x32>)
			{
				return EmuSIMD::Funcs::cvt_f64x4_i8x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u8x32>)
			{
				return EmuSIMD::Funcs::cvt_f64x4_u8x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i8x64>)
			{
				return EmuSIMD::Funcs::cvt_f64x4_i8x64(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u8x64>)
			{
				return EmuSIMD::Funcs::cvt_f64x4_u8x64(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i16x8>)
			{
				return EmuSIMD::Funcs::cvt_f64x4_i16x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u16x8>)
			{
				return EmuSIMD::Funcs::cvt_f64x4_u16x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i16x16>)
			{
				return EmuSIMD::Funcs::cvt_f64x4_i16x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u16x16>)
			{
				return EmuSIMD::Funcs::cvt_f64x4_u16x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i16x32>)
			{
				return EmuSIMD::Funcs::cvt_f64x4_i16x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u16x32>)
			{
				return EmuSIMD::Funcs::cvt_f64x4_u16x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i32x4>)
			{
				return EmuSIMD::Funcs::cvt_f64x4_i32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u32x4>)
			{
				return EmuSIMD::Funcs::cvt_f64x4_u32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i32x8>)
			{
				return EmuSIMD::Funcs::cvt_f64x4_i32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u32x8>)
			{
				return EmuSIMD::Funcs::cvt_f64x4_u32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i32x16>)
			{
				return EmuSIMD::Funcs::cvt_f64x4_i32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u32x16>)
			{
				return EmuSIMD::Funcs::cvt_f64x4_u32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i64x2>)
			{
				return EmuSIMD::Funcs::cvt_f64x4_i64x2(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u64x2>)
			{
				return EmuSIMD::Funcs::cvt_f64x4_u64x2(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i64x4>)
			{
				return EmuSIMD::Funcs::cvt_f64x4_i64x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u64x4>)
			{
				return EmuSIMD::Funcs::cvt_f64x4_u64x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i64x8>)
			{
				return EmuSIMD::Funcs::cvt_f64x4_i64x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u64x8>)
			{
				return EmuSIMD::Funcs::cvt_f64x4_u64x8(from_);
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<ToRegister_>(), "Attempted to convert a EmuSIMD::f64x4 register via EmuSIMD helpers, but the provided SIMD register to convert to is not supported for this operation.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<ToRegister_>(), "Attempted to convert a EmuSIMD::f64x4 register via EmuSIMD helpers, but the provided register to convert to is not recognisd as a supported SIMD register.");
		}
	}

	template<class ToRegister_, std::size_t OutPerElementWidthIfInt_, bool OutSignedIfInt_>
	[[nodiscard]] inline ToRegister_ _cvt_f64x8(EmuSIMD::f64x8_arg from_)
	{
		using to_uq = EmuCore::TMP::remove_ref_cv_t<ToRegister_>;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<to_uq>)
		{
			if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x4>)
			{
				return EmuSIMD::Funcs::cvt_f64x8_f32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x8>)
			{
				return EmuSIMD::Funcs::cvt_f64x8_f32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x16>)
			{
				return EmuSIMD::Funcs::cvt_f64x8_f32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x2>)
			{
				return EmuSIMD::Funcs::cvt_f64x8_f64x2(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x4>)
			{
				return EmuSIMD::Funcs::cvt_f64x8_f64x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x8>)
			{
				return from_;
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i128_generic>)
			{
				if constexpr (OutPerElementWidthIfInt_ == 8)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_f64x8_i8x16(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_f64x8_u8x16(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 16)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_f64x8_i16x8(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_f64x8_u16x8(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 32)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_f64x8_i32x4(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_f64x8_u32x4(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 64)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_f64x8_i64x2(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_f64x8_u64x2(from_);
					}
				}
				else
				{
					static_assert
					(
						EmuCore::TMP::get_false<OutPerElementWidthIfInt_>(),
						"Attempted to convert a EmuSIMD::f64x8 register to i128_generic via EmuSIMD helpers, but the provided width per element is invalid. Only 8, 16, 32, and 64 are valid values."
					);
				}
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i256_generic>)
			{
				if constexpr (OutPerElementWidthIfInt_ == 8)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_f64x8_i8x32(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_f64x8_u8x32(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 16)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_f64x8_i16x16(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_f64x8_u16x16(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 32)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_f64x8_i32x8(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_f64x8_u32x8(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 64)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_f64x8_i64x4(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_f64x8_u64x4(from_);
					}
				}
				else
				{
					static_assert
					(
						EmuCore::TMP::get_false<OutPerElementWidthIfInt_>(),
						"Attempted to convert a EmuSIMD::f64x8 register to i256_generic via EmuSIMD helpers, but the provided width per element is invalid. Only 8, 16, 32, and 64 are valid values."
					);
				}
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i512_generic>)
			{
				if constexpr (OutPerElementWidthIfInt_ == 8)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_f64x8_i8x64(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_f64x8_u8x64(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 16)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_f64x8_i16x32(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_f64x8_u16x32(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 32)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_f64x8_i32x16(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_f64x8_u32x16(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 64)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_f64x8_i64x8(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_f64x8_u64x8(from_);
					}
				}
				else
				{
					static_assert
					(
						EmuCore::TMP::get_false<OutPerElementWidthIfInt_>(),
						"Attempted to convert a EmuSIMD::f64x8 register to i512_generic via EmuSIMD helpers, but the provided width per element is invalid. Only 8, 16, 32, and 64 are valid values."
					);
				}
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i8x16>)
			{
				return EmuSIMD::Funcs::cvt_f64x8_i8x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u8x16>)
			{
				return EmuSIMD::Funcs::cvt_f64x8_u8x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i8x32>)
			{
				return EmuSIMD::Funcs::cvt_f64x8_i8x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u8x32>)
			{
				return EmuSIMD::Funcs::cvt_f64x8_u8x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i8x64>)
			{
				return EmuSIMD::Funcs::cvt_f64x8_i8x64(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u8x64>)
			{
				return EmuSIMD::Funcs::cvt_f64x8_u8x64(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i16x8>)
			{
				return EmuSIMD::Funcs::cvt_f64x8_i16x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u16x8>)
			{
				return EmuSIMD::Funcs::cvt_f64x8_u16x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i16x16>)
			{
				return EmuSIMD::Funcs::cvt_f64x8_i16x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u16x16>)
			{
				return EmuSIMD::Funcs::cvt_f64x8_u16x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i16x32>)
			{
				return EmuSIMD::Funcs::cvt_f64x8_i16x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u16x32>)
			{
				return EmuSIMD::Funcs::cvt_f64x8_u16x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i32x4>)
			{
				return EmuSIMD::Funcs::cvt_f64x8_i32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u32x4>)
			{
				return EmuSIMD::Funcs::cvt_f64x8_u32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i32x8>)
			{
				return EmuSIMD::Funcs::cvt_f64x8_i32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u32x8>)
			{
				return EmuSIMD::Funcs::cvt_f64x8_u32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i32x16>)
			{
				return EmuSIMD::Funcs::cvt_f64x8_i32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u32x16>)
			{
				return EmuSIMD::Funcs::cvt_f64x8_u32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i64x2>)
			{
				return EmuSIMD::Funcs::cvt_f64x8_i64x2(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u64x2>)
			{
				return EmuSIMD::Funcs::cvt_f64x8_u64x2(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i64x4>)
			{
				return EmuSIMD::Funcs::cvt_f64x8_i64x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u64x4>)
			{
				return EmuSIMD::Funcs::cvt_f64x8_u64x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i64x8>)
			{
				return EmuSIMD::Funcs::cvt_f64x8_i64x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u64x8>)
			{
				return EmuSIMD::Funcs::cvt_f64x8_u64x8(from_);
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<ToRegister_>(), "Attempted to convert a EmuSIMD::f64x8 register via EmuSIMD helpers, but the provided SIMD register to convert to is not supported for this operation.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<ToRegister_>(), "Attempted to convert a EmuSIMD::f64x8 register via EmuSIMD helpers, but the provided register to convert to is not recognisd as a supported SIMD register.");
		}
	}
#pragma endregion

#pragma region CVT_I8
	template<class ToRegister_, std::size_t OutPerElementWidthIfInt_, bool OutSignedIfInt_>
	[[nodiscard]] inline ToRegister_ _cvt_i8x16(EmuSIMD::i8x16_arg from_)
	{
		using to_uq = EmuCore::TMP::remove_ref_cv_t<ToRegister_>;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<to_uq>)
		{
			if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x4>)
			{
				return EmuSIMD::Funcs::cvt_i8x16_f32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x8>)
			{
				return EmuSIMD::Funcs::cvt_i8x16_f32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x16>)
			{
				return EmuSIMD::Funcs::cvt_i8x16_f32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x2>)
			{
				return EmuSIMD::Funcs::cvt_i8x16_f64x2(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x4>)
			{
				return EmuSIMD::Funcs::cvt_i8x16_f64x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x8>)
			{
				return EmuSIMD::Funcs::cvt_i8x16_f64x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i128_generic>)
			{
				if constexpr (OutPerElementWidthIfInt_ == 8)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_i8x16_i8x16(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_i8x16_u8x16(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 16)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_i8x16_i16x8(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_i8x16_u16x8(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 32)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_i8x16_i32x4(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_i8x16_u32x4(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 64)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_i8x16_i64x2(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_i8x16_u64x2(from_);
					}
				}
				else
				{
					static_assert
					(
						EmuCore::TMP::get_false<OutPerElementWidthIfInt_>(),
						"Attempted to convert a EmuSIMD::i8x16 register to i128_generic via EmuSIMD helpers, but the provided width per element is invalid. Only 8, 16, 32, and 64 are valid values."
					);
				}
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i256_generic>)
			{
				if constexpr (OutPerElementWidthIfInt_ == 8)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_i8x16_i8x32(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_i8x16_u8x32(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 16)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_i8x16_i16x16(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_i8x16_u16x16(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 32)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_i8x16_i32x8(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_i8x16_u32x8(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 64)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_i8x16_i64x4(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_i8x16_u64x4(from_);
					}
				}
				else
				{
					static_assert
					(
						EmuCore::TMP::get_false<OutPerElementWidthIfInt_>(),
						"Attempted to convert a EmuSIMD::i8x16 register to i256_generic via EmuSIMD helpers, but the provided width per element is invalid. Only 8, 16, 32, and 64 are valid values."
					);
				}
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i512_generic>)
			{
				if constexpr (OutPerElementWidthIfInt_ == 8)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_i8x16_i8x64(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_i8x16_u8x64(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 16)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_i8x16_i16x32(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_i8x16_u16x32(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 32)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_i8x16_i32x16(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_i8x16_u32x16(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 64)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_i8x16_i64x8(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_i8x16_u64x8(from_);
					}
				}
				else
				{
					static_assert
					(
						EmuCore::TMP::get_false<OutPerElementWidthIfInt_>(),
						"Attempted to convert a EmuSIMD::i8x16 register to i512_generic via EmuSIMD helpers, but the provided width per element is invalid. Only 8, 16, 32, and 64 are valid values."
					);
				}
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i8x16>)
			{
				return EmuSIMD::Funcs::cvt_i8x16_i8x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u8x16>)
			{
				return EmuSIMD::Funcs::cvt_i8x16_u8x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i8x32>)
			{
				return EmuSIMD::Funcs::cvt_i8x16_i8x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u8x32>)
			{
				return EmuSIMD::Funcs::cvt_i8x16_u8x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i8x64>)
			{
				return EmuSIMD::Funcs::cvt_i8x16_i8x64(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u8x64>)
			{
				return EmuSIMD::Funcs::cvt_i8x16_u8x64(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i16x8>)
			{
				return EmuSIMD::Funcs::cvt_i8x16_i16x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u16x8>)
			{
				return EmuSIMD::Funcs::cvt_i8x16_u16x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i16x16>)
			{
				return EmuSIMD::Funcs::cvt_i8x16_i16x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u16x16>)
			{
				return EmuSIMD::Funcs::cvt_i8x16_u16x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i16x32>)
			{
				return EmuSIMD::Funcs::cvt_i8x16_i16x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u16x32>)
			{
				return EmuSIMD::Funcs::cvt_i8x16_u16x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i32x4>)
			{
				return EmuSIMD::Funcs::cvt_i8x16_i32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u32x4>)
			{
				return EmuSIMD::Funcs::cvt_i8x16_u32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i32x8>)
			{
				return EmuSIMD::Funcs::cvt_i8x16_i32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u32x8>)
			{
				return EmuSIMD::Funcs::cvt_i8x16_u32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i32x16>)
			{
				return EmuSIMD::Funcs::cvt_i8x16_i32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u32x16>)
			{
				return EmuSIMD::Funcs::cvt_i8x16_u32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i64x2>)
			{
				return EmuSIMD::Funcs::cvt_i8x16_i64x2(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u64x2>)
			{
				return EmuSIMD::Funcs::cvt_i8x16_u64x2(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i64x4>)
			{
				return EmuSIMD::Funcs::cvt_i8x16_i64x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u64x4>)
			{
				return EmuSIMD::Funcs::cvt_i8x16_u64x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i64x8>)
			{
				return EmuSIMD::Funcs::cvt_i8x16_i64x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u64x8>)
			{
				return EmuSIMD::Funcs::cvt_i8x16_u64x8(from_);
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<ToRegister_>(), "Attempted to convert a EmuSIMD::i8x16 register via EmuSIMD helpers, but the provided SIMD register to convert to is not supported for this operation.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<ToRegister_>(), "Attempted to convert a EmuSIMD::i8x16 register via EmuSIMD helpers, but the provided register to convert to is not recognisd as a supported SIMD register.");
		}
	}

	template<class ToRegister_, std::size_t OutPerElementWidthIfInt_, bool OutSignedIfInt_>
	[[nodiscard]] inline ToRegister_ _cvt_i8x32(EmuSIMD::i8x32_arg from_)
	{
		using to_uq = EmuCore::TMP::remove_ref_cv_t<ToRegister_>;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<to_uq>)
		{
			if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x4>)
			{
				return EmuSIMD::Funcs::cvt_i8x32_f32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x8>)
			{
				return EmuSIMD::Funcs::cvt_i8x32_f32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x16>)
			{
				return EmuSIMD::Funcs::cvt_i8x32_f32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x2>)
			{
				return EmuSIMD::Funcs::cvt_i8x32_f64x2(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x4>)
			{
				return EmuSIMD::Funcs::cvt_i8x32_f64x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x8>)
			{
				return EmuSIMD::Funcs::cvt_i8x32_f64x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i128_generic>)
			{
				if constexpr (OutPerElementWidthIfInt_ == 8)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_i8x32_i8x16(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_i8x32_u8x16(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 16)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_i8x32_i16x8(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_i8x32_u16x8(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 32)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_i8x32_i32x4(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_i8x32_u32x4(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 64)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_i8x32_i64x2(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_i8x32_u64x2(from_);
					}
				}
				else
				{
					static_assert
					(
						EmuCore::TMP::get_false<OutPerElementWidthIfInt_>(),
						"Attempted to convert a EmuSIMD::i8x32 register to i128_generic via EmuSIMD helpers, but the provided width per element is invalid. Only 8, 16, 32, and 64 are valid values."
					);
				}
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i256_generic>)
			{
				if constexpr (OutPerElementWidthIfInt_ == 8)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_i8x32_i8x32(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_i8x32_u8x32(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 16)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_i8x32_i16x16(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_i8x32_u16x16(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 32)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_i8x32_i32x8(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_i8x32_u32x8(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 64)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_i8x32_i64x4(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_i8x32_u64x4(from_);
					}
				}
				else
				{
					static_assert
					(
						EmuCore::TMP::get_false<OutPerElementWidthIfInt_>(),
						"Attempted to convert a EmuSIMD::i8x32 register to i256_generic via EmuSIMD helpers, but the provided width per element is invalid. Only 8, 16, 32, and 64 are valid values."
					);
				}
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i512_generic>)
			{
				if constexpr (OutPerElementWidthIfInt_ == 8)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_i8x32_i8x64(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_i8x32_u8x64(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 16)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_i8x32_i16x32(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_i8x32_u16x32(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 32)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_i8x32_i32x16(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_i8x32_u32x16(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 64)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_i8x32_i64x8(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_i8x32_u64x8(from_);
					}
				}
				else
				{
					static_assert
					(
						EmuCore::TMP::get_false<OutPerElementWidthIfInt_>(),
						"Attempted to convert a EmuSIMD::i8x32 register to i512_generic via EmuSIMD helpers, but the provided width per element is invalid. Only 8, 16, 32, and 64 are valid values."
					);
				}
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i8x16>)
			{
				return EmuSIMD::Funcs::cvt_i8x32_i8x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u8x16>)
			{
				return EmuSIMD::Funcs::cvt_i8x32_u8x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i8x32>)
			{
				return EmuSIMD::Funcs::cvt_i8x32_i8x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u8x32>)
			{
				return EmuSIMD::Funcs::cvt_i8x32_u8x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i8x64>)
			{
				return EmuSIMD::Funcs::cvt_i8x32_i8x64(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u8x64>)
			{
				return EmuSIMD::Funcs::cvt_i8x32_u8x64(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i16x8>)
			{
				return EmuSIMD::Funcs::cvt_i8x32_i16x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u16x8>)
			{
				return EmuSIMD::Funcs::cvt_i8x32_u16x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i16x16>)
			{
				return EmuSIMD::Funcs::cvt_i8x32_i16x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u16x16>)
			{
				return EmuSIMD::Funcs::cvt_i8x32_u16x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i16x32>)
			{
				return EmuSIMD::Funcs::cvt_i8x32_i16x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u16x32>)
			{
				return EmuSIMD::Funcs::cvt_i8x32_u16x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i32x4>)
			{
				return EmuSIMD::Funcs::cvt_i8x32_i32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u32x4>)
			{
				return EmuSIMD::Funcs::cvt_i8x32_u32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i32x8>)
			{
				return EmuSIMD::Funcs::cvt_i8x32_i32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u32x8>)
			{
				return EmuSIMD::Funcs::cvt_i8x32_u32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i32x16>)
			{
				return EmuSIMD::Funcs::cvt_i8x32_i32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u32x16>)
			{
				return EmuSIMD::Funcs::cvt_i8x32_u32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i64x2>)
			{
				return EmuSIMD::Funcs::cvt_i8x32_i64x2(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u64x2>)
			{
				return EmuSIMD::Funcs::cvt_i8x32_u64x2(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i64x4>)
			{
				return EmuSIMD::Funcs::cvt_i8x32_i64x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u64x4>)
			{
				return EmuSIMD::Funcs::cvt_i8x32_u64x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i64x8>)
			{
				return EmuSIMD::Funcs::cvt_i8x32_i64x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u64x8>)
			{
				return EmuSIMD::Funcs::cvt_i8x32_u64x8(from_);
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<ToRegister_>(), "Attempted to convert a EmuSIMD::i8x32 register via EmuSIMD helpers, but the provided SIMD register to convert to is not supported for this operation.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<ToRegister_>(), "Attempted to convert a EmuSIMD::i8x32 register via EmuSIMD helpers, but the provided register to convert to is not recognisd as a supported SIMD register.");
		}
	}

	template<class ToRegister_, std::size_t OutPerElementWidthIfInt_, bool OutSignedIfInt_>
	[[nodiscard]] inline ToRegister_ _cvt_i8x64(EmuSIMD::i8x64_arg from_)
	{
		using to_uq = EmuCore::TMP::remove_ref_cv_t<ToRegister_>;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<to_uq>)
		{
			if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x4>)
			{
				return EmuSIMD::Funcs::cvt_i8x64_f32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x8>)
			{
				return EmuSIMD::Funcs::cvt_i8x64_f32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x16>)
			{
				return EmuSIMD::Funcs::cvt_i8x64_f32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x2>)
			{
				return EmuSIMD::Funcs::cvt_i8x64_f64x2(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x4>)
			{
				return EmuSIMD::Funcs::cvt_i8x64_f64x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x8>)
			{
				return EmuSIMD::Funcs::cvt_i8x64_f64x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i128_generic>)
			{
				if constexpr (OutPerElementWidthIfInt_ == 8)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_i8x64_i8x16(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_i8x64_u8x16(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 16)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_i8x64_i16x8(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_i8x64_u16x8(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 32)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_i8x64_i32x4(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_i8x64_u32x4(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 64)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_i8x64_i64x2(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_i8x64_u64x2(from_);
					}
				}
				else
				{
					static_assert
					(
						EmuCore::TMP::get_false<OutPerElementWidthIfInt_>(),
						"Attempted to convert a EmuSIMD::i8x64 register to i128_generic via EmuSIMD helpers, but the provided width per element is invalid. Only 8, 16, 32, and 64 are valid values."
					);
				}
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i256_generic>)
			{
				if constexpr (OutPerElementWidthIfInt_ == 8)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_i8x64_i8x32(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_i8x64_u8x32(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 16)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_i8x64_i16x16(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_i8x64_u16x16(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 32)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_i8x64_i32x8(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_i8x64_u32x8(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 64)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_i8x64_i64x4(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_i8x64_u64x4(from_);
					}
				}
				else
				{
					static_assert
					(
						EmuCore::TMP::get_false<OutPerElementWidthIfInt_>(),
						"Attempted to convert a EmuSIMD::i8x64 register to i256_generic via EmuSIMD helpers, but the provided width per element is invalid. Only 8, 16, 32, and 64 are valid values."
					);
				}
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i512_generic>)
			{
				if constexpr (OutPerElementWidthIfInt_ == 8)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_i8x64_i8x64(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_i8x64_u8x64(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 16)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_i8x64_i16x32(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_i8x64_u16x32(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 32)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_i8x64_i32x16(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_i8x64_u32x16(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 64)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_i8x64_i64x8(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_i8x64_u64x8(from_);
					}
				}
				else
				{
					static_assert
					(
						EmuCore::TMP::get_false<OutPerElementWidthIfInt_>(),
						"Attempted to convert a EmuSIMD::i8x64 register to i512_generic via EmuSIMD helpers, but the provided width per element is invalid. Only 8, 16, 32, and 64 are valid values."
					);
				}
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i8x16>)
			{
				return EmuSIMD::Funcs::cvt_i8x64_i8x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u8x16>)
			{
				return EmuSIMD::Funcs::cvt_i8x64_u8x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i8x32>)
			{
				return EmuSIMD::Funcs::cvt_i8x64_i8x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u8x32>)
			{
				return EmuSIMD::Funcs::cvt_i8x64_u8x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i8x64>)
			{
				return EmuSIMD::Funcs::cvt_i8x64_i8x64(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u8x64>)
			{
				return EmuSIMD::Funcs::cvt_i8x64_u8x64(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i16x8>)
			{
				return EmuSIMD::Funcs::cvt_i8x64_i16x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u16x8>)
			{
				return EmuSIMD::Funcs::cvt_i8x64_u16x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i16x16>)
			{
				return EmuSIMD::Funcs::cvt_i8x64_i16x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u16x16>)
			{
				return EmuSIMD::Funcs::cvt_i8x64_u16x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i16x32>)
			{
				return EmuSIMD::Funcs::cvt_i8x64_i16x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u16x32>)
			{
				return EmuSIMD::Funcs::cvt_i8x64_u16x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i32x4>)
			{
				return EmuSIMD::Funcs::cvt_i8x64_i32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u32x4>)
			{
				return EmuSIMD::Funcs::cvt_i8x64_u32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i32x8>)
			{
				return EmuSIMD::Funcs::cvt_i8x64_i32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u32x8>)
			{
				return EmuSIMD::Funcs::cvt_i8x64_u32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i32x16>)
			{
				return EmuSIMD::Funcs::cvt_i8x64_i32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u32x16>)
			{
				return EmuSIMD::Funcs::cvt_i8x64_u32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i64x2>)
			{
				return EmuSIMD::Funcs::cvt_i8x64_i64x2(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u64x2>)
			{
				return EmuSIMD::Funcs::cvt_i8x64_u64x2(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i64x4>)
			{
				return EmuSIMD::Funcs::cvt_i8x64_i64x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u64x4>)
			{
				return EmuSIMD::Funcs::cvt_i8x64_u64x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i64x8>)
			{
				return EmuSIMD::Funcs::cvt_i8x64_i64x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u64x8>)
			{
				return EmuSIMD::Funcs::cvt_i8x64_u64x8(from_);
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<ToRegister_>(), "Attempted to convert a EmuSIMD::i8x64 register via EmuSIMD helpers, but the provided SIMD register to convert to is not supported for this operation.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<ToRegister_>(), "Attempted to convert a EmuSIMD::i8x64 register via EmuSIMD helpers, but the provided register to convert to is not recognisd as a supported SIMD register.");
		}
	}
#pragma endregion

#pragma region CVT_I16
	template<class ToRegister_, std::size_t OutPerElementWidthIfInt_, bool OutSignedIfInt_>
	[[nodiscard]] inline ToRegister_ _cvt_i16x8(EmuSIMD::i16x8_arg from_)
	{
		using to_uq = EmuCore::TMP::remove_ref_cv_t<ToRegister_>;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<to_uq>)
		{
			if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x4>)
			{
				return EmuSIMD::Funcs::cvt_i16x8_f32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x8>)
			{
				return EmuSIMD::Funcs::cvt_i16x8_f32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x16>)
			{
				return EmuSIMD::Funcs::cvt_i16x8_f32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x2>)
			{
				return EmuSIMD::Funcs::cvt_i16x8_f64x2(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x4>)
			{
				return EmuSIMD::Funcs::cvt_i16x8_f64x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x8>)
			{
				return EmuSIMD::Funcs::cvt_i16x8_f64x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i128_generic>)
			{
				if constexpr (OutPerElementWidthIfInt_ == 8)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_i16x8_i8x16(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_i16x8_u8x16(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 16)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_i16x8_i16x8(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_i16x8_u16x8(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 32)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_i16x8_i32x4(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_i16x8_u32x4(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 64)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_i16x8_i64x2(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_i16x8_u64x2(from_);
					}
				}
				else
				{
					static_assert
					(
						EmuCore::TMP::get_false<OutPerElementWidthIfInt_>(),
						"Attempted to convert a EmuSIMD::i16x8 register to i128_generic via EmuSIMD helpers, but the provided width per element is invalid. Only 8, 16, 32, and 64 are valid values."
					);
				}
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i256_generic>)
			{
				if constexpr (OutPerElementWidthIfInt_ == 8)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_i16x8_i8x32(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_i16x8_u8x32(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 16)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_i16x8_i16x16(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_i16x8_u16x16(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 32)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_i16x8_i32x8(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_i16x8_u32x8(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 64)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_i16x8_i64x4(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_i16x8_u64x4(from_);
					}
				}
				else
				{
					static_assert
					(
						EmuCore::TMP::get_false<OutPerElementWidthIfInt_>(),
						"Attempted to convert a EmuSIMD::i16x8 register to i256_generic via EmuSIMD helpers, but the provided width per element is invalid. Only 8, 16, 32, and 64 are valid values."
					);
				}
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i512_generic>)
			{
				if constexpr (OutPerElementWidthIfInt_ == 8)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_i16x8_i8x64(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_i16x8_u8x64(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 16)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_i16x8_i16x32(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_i16x8_u16x32(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 32)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_i16x8_i32x16(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_i16x8_u32x16(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 64)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_i16x8_i64x8(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_i16x8_u64x8(from_);
					}
				}
				else
				{
					static_assert
					(
						EmuCore::TMP::get_false<OutPerElementWidthIfInt_>(),
						"Attempted to convert a EmuSIMD::i16x8 register to i512_generic via EmuSIMD helpers, but the provided width per element is invalid. Only 8, 16, 32, and 64 are valid values."
					);
				}
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i8x16>)
			{
				return EmuSIMD::Funcs::cvt_i16x8_i8x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u8x16>)
			{
				return EmuSIMD::Funcs::cvt_i16x8_u8x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i8x32>)
			{
				return EmuSIMD::Funcs::cvt_i16x8_i8x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u8x32>)
			{
				return EmuSIMD::Funcs::cvt_i16x8_u8x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i8x64>)
			{
				return EmuSIMD::Funcs::cvt_i16x8_i8x64(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u8x64>)
			{
				return EmuSIMD::Funcs::cvt_i16x8_u8x64(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i16x8>)
			{
				return EmuSIMD::Funcs::cvt_i16x8_i16x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u16x8>)
			{
				return EmuSIMD::Funcs::cvt_i16x8_u16x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i16x16>)
			{
				return EmuSIMD::Funcs::cvt_i16x8_i16x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u16x16>)
			{
				return EmuSIMD::Funcs::cvt_i16x8_u16x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i16x32>)
			{
				return EmuSIMD::Funcs::cvt_i16x8_i16x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u16x32>)
			{
				return EmuSIMD::Funcs::cvt_i16x8_u16x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i32x4>)
			{
				return EmuSIMD::Funcs::cvt_i16x8_i32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u32x4>)
			{
				return EmuSIMD::Funcs::cvt_i16x8_u32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i32x8>)
			{
				return EmuSIMD::Funcs::cvt_i16x8_i32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u32x8>)
			{
				return EmuSIMD::Funcs::cvt_i16x8_u32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i32x16>)
			{
				return EmuSIMD::Funcs::cvt_i16x8_i32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u32x16>)
			{
				return EmuSIMD::Funcs::cvt_i16x8_u32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i64x2>)
			{
				return EmuSIMD::Funcs::cvt_i16x8_i64x2(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u64x2>)
			{
				return EmuSIMD::Funcs::cvt_i16x8_u64x2(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i64x4>)
			{
				return EmuSIMD::Funcs::cvt_i16x8_i64x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u64x4>)
			{
				return EmuSIMD::Funcs::cvt_i16x8_u64x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i64x8>)
			{
				return EmuSIMD::Funcs::cvt_i16x8_i64x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u64x8>)
			{
				return EmuSIMD::Funcs::cvt_i16x8_u64x8(from_);
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<ToRegister_>(), "Attempted to convert a EmuSIMD::i16x8 register via EmuSIMD helpers, but the provided SIMD register to convert to is not supported for this operation.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<ToRegister_>(), "Attempted to convert a EmuSIMD::i16x8 register via EmuSIMD helpers, but the provided register to convert to is not recognisd as a supported SIMD register.");
		}
	}

	template<class ToRegister_, std::size_t OutPerElementWidthIfInt_, bool OutSignedIfInt_>
	[[nodiscard]] inline ToRegister_ _cvt_i16x16(EmuSIMD::i16x16_arg from_)
	{
		using to_uq = EmuCore::TMP::remove_ref_cv_t<ToRegister_>;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<to_uq>)
		{
			if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x4>)
			{
				return EmuSIMD::Funcs::cvt_i16x16_f32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x8>)
			{
				return EmuSIMD::Funcs::cvt_i16x16_f32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x16>)
			{
				return EmuSIMD::Funcs::cvt_i16x16_f32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x2>)
			{
				return EmuSIMD::Funcs::cvt_i16x16_f64x2(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x4>)
			{
				return EmuSIMD::Funcs::cvt_i16x16_f64x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x8>)
			{
				return EmuSIMD::Funcs::cvt_i16x16_f64x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i128_generic>)
			{
				if constexpr (OutPerElementWidthIfInt_ == 8)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_i16x16_i8x16(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_i16x16_u8x16(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 16)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_i16x16_i16x8(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_i16x16_u16x8(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 32)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_i16x16_i32x4(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_i16x16_u32x4(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 64)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_i16x16_i64x2(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_i16x16_u64x2(from_);
					}
				}
				else
				{
					static_assert
					(
						EmuCore::TMP::get_false<OutPerElementWidthIfInt_>(),
						"Attempted to convert a EmuSIMD::i16x16 register to i128_generic via EmuSIMD helpers, but the provided width per element is invalid. Only 8, 16, 32, and 64 are valid values."
					);
				}
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i256_generic>)
			{
				if constexpr (OutPerElementWidthIfInt_ == 8)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_i16x16_i8x32(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_i16x16_u8x32(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 16)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_i16x16_i16x16(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_i16x16_u16x16(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 32)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_i16x16_i32x8(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_i16x16_u32x8(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 64)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_i16x16_i64x4(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_i16x16_u64x4(from_);
					}
				}
				else
				{
					static_assert
					(
						EmuCore::TMP::get_false<OutPerElementWidthIfInt_>(),
						"Attempted to convert a EmuSIMD::i16x16 register to i256_generic via EmuSIMD helpers, but the provided width per element is invalid. Only 8, 16, 32, and 64 are valid values."
					);
				}
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i512_generic>)
			{
				if constexpr (OutPerElementWidthIfInt_ == 8)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_i16x16_i8x64(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_i16x16_u8x64(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 16)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_i16x16_i16x32(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_i16x16_u16x32(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 32)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_i16x16_i32x16(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_i16x16_u32x16(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 64)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_i16x16_i64x8(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_i16x16_u64x8(from_);
					}
				}
				else
				{
					static_assert
					(
						EmuCore::TMP::get_false<OutPerElementWidthIfInt_>(),
						"Attempted to convert a EmuSIMD::i16x16 register to i512_generic via EmuSIMD helpers, but the provided width per element is invalid. Only 8, 16, 32, and 64 are valid values."
					);
				}
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i8x16>)
			{
				return EmuSIMD::Funcs::cvt_i16x16_i8x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u8x16>)
			{
				return EmuSIMD::Funcs::cvt_i16x16_u8x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i8x32>)
			{
				return EmuSIMD::Funcs::cvt_i16x16_i8x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u8x32>)
			{
				return EmuSIMD::Funcs::cvt_i16x16_u8x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i8x64>)
			{
				return EmuSIMD::Funcs::cvt_i16x16_i8x64(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u8x64>)
			{
				return EmuSIMD::Funcs::cvt_i16x16_u8x64(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i16x8>)
			{
				return EmuSIMD::Funcs::cvt_i16x16_i16x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u16x8>)
			{
				return EmuSIMD::Funcs::cvt_i16x16_u16x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i16x16>)
			{
				return EmuSIMD::Funcs::cvt_i16x16_i16x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u16x16>)
			{
				return EmuSIMD::Funcs::cvt_i16x16_u16x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i16x32>)
			{
				return EmuSIMD::Funcs::cvt_i16x16_i16x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u16x32>)
			{
				return EmuSIMD::Funcs::cvt_i16x16_u16x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i32x4>)
			{
				return EmuSIMD::Funcs::cvt_i16x16_i32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u32x4>)
			{
				return EmuSIMD::Funcs::cvt_i16x16_u32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i32x8>)
			{
				return EmuSIMD::Funcs::cvt_i16x16_i32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u32x8>)
			{
				return EmuSIMD::Funcs::cvt_i16x16_u32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i32x16>)
			{
				return EmuSIMD::Funcs::cvt_i16x16_i32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u32x16>)
			{
				return EmuSIMD::Funcs::cvt_i16x16_u32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i64x2>)
			{
				return EmuSIMD::Funcs::cvt_i16x16_i64x2(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u64x2>)
			{
				return EmuSIMD::Funcs::cvt_i16x16_u64x2(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i64x4>)
			{
				return EmuSIMD::Funcs::cvt_i16x16_i64x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u64x4>)
			{
				return EmuSIMD::Funcs::cvt_i16x16_u64x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i64x8>)
			{
				return EmuSIMD::Funcs::cvt_i16x16_i64x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u64x8>)
			{
				return EmuSIMD::Funcs::cvt_i16x16_u64x8(from_);
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<ToRegister_>(), "Attempted to convert a EmuSIMD::i16x16 register via EmuSIMD helpers, but the provided SIMD register to convert to is not supported for this operation.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<ToRegister_>(), "Attempted to convert a EmuSIMD::i16x16 register via EmuSIMD helpers, but the provided register to convert to is not recognisd as a supported SIMD register.");
		}
	}

	template<class ToRegister_, std::size_t OutPerElementWidthIfInt_, bool OutSignedIfInt_>
	[[nodiscard]] inline ToRegister_ _cvt_i16x32(EmuSIMD::i16x32_arg from_)
	{
		using to_uq = EmuCore::TMP::remove_ref_cv_t<ToRegister_>;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<to_uq>)
		{
			if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x4>)
			{
				return EmuSIMD::Funcs::cvt_i16x32_f32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x8>)
			{
				return EmuSIMD::Funcs::cvt_i16x32_f32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x16>)
			{
				return EmuSIMD::Funcs::cvt_i16x32_f32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x2>)
			{
				return EmuSIMD::Funcs::cvt_i16x32_f64x2(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x4>)
			{
				return EmuSIMD::Funcs::cvt_i16x32_f64x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x8>)
			{
				return EmuSIMD::Funcs::cvt_i16x32_f64x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i128_generic>)
			{
				if constexpr (OutPerElementWidthIfInt_ == 8)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_i16x32_i8x16(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_i16x32_u8x16(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 16)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_i16x32_i16x8(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_i16x32_u16x8(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 32)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_i16x32_i32x4(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_i16x32_u32x4(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 64)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_i16x32_i64x2(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_i16x32_u64x2(from_);
					}
				}
				else
				{
					static_assert
					(
						EmuCore::TMP::get_false<OutPerElementWidthIfInt_>(),
						"Attempted to convert a EmuSIMD::i16x32 register to i128_generic via EmuSIMD helpers, but the provided width per element is invalid. Only 8, 16, 32, and 64 are valid values."
					);
				}
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i256_generic>)
			{
				if constexpr (OutPerElementWidthIfInt_ == 8)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_i16x32_i8x32(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_i16x32_u8x32(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 16)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_i16x32_i16x16(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_i16x32_u16x16(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 32)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_i16x32_i32x8(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_i16x32_u32x8(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 64)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_i16x32_i64x4(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_i16x32_u64x4(from_);
					}
				}
				else
				{
					static_assert
					(
						EmuCore::TMP::get_false<OutPerElementWidthIfInt_>(),
						"Attempted to convert a EmuSIMD::i16x32 register to i256_generic via EmuSIMD helpers, but the provided width per element is invalid. Only 8, 16, 32, and 64 are valid values."
					);
				}
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i512_generic>)
			{
				if constexpr (OutPerElementWidthIfInt_ == 8)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_i16x32_i8x64(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_i16x32_u8x64(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 16)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_i16x32_i16x32(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_i16x32_u16x32(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 32)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_i16x32_i32x16(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_i16x32_u32x16(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 64)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_i16x32_i64x8(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_i16x32_u64x8(from_);
					}
				}
				else
				{
					static_assert
					(
						EmuCore::TMP::get_false<OutPerElementWidthIfInt_>(),
						"Attempted to convert a EmuSIMD::i16x32 register to i512_generic via EmuSIMD helpers, but the provided width per element is invalid. Only 8, 16, 32, and 64 are valid values."
					);
				}
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i8x16>)
			{
				return EmuSIMD::Funcs::cvt_i16x32_i8x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u8x16>)
			{
				return EmuSIMD::Funcs::cvt_i16x32_u8x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i8x32>)
			{
				return EmuSIMD::Funcs::cvt_i16x32_i8x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u8x32>)
			{
				return EmuSIMD::Funcs::cvt_i16x32_u8x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i8x64>)
			{
				return EmuSIMD::Funcs::cvt_i16x32_i8x64(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u8x64>)
			{
				return EmuSIMD::Funcs::cvt_i16x32_u8x64(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i16x8>)
			{
				return EmuSIMD::Funcs::cvt_i16x32_i16x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u16x8>)
			{
				return EmuSIMD::Funcs::cvt_i16x32_u16x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i16x16>)
			{
				return EmuSIMD::Funcs::cvt_i16x32_i16x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u16x16>)
			{
				return EmuSIMD::Funcs::cvt_i16x32_u16x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i16x32>)
			{
				return EmuSIMD::Funcs::cvt_i16x32_i16x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u16x32>)
			{
				return EmuSIMD::Funcs::cvt_i16x32_u16x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i32x4>)
			{
				return EmuSIMD::Funcs::cvt_i16x32_i32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u32x4>)
			{
				return EmuSIMD::Funcs::cvt_i16x32_u32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i32x8>)
			{
				return EmuSIMD::Funcs::cvt_i16x32_i32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u32x8>)
			{
				return EmuSIMD::Funcs::cvt_i16x32_u32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i32x16>)
			{
				return EmuSIMD::Funcs::cvt_i16x32_i32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u32x16>)
			{
				return EmuSIMD::Funcs::cvt_i16x32_u32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i64x2>)
			{
				return EmuSIMD::Funcs::cvt_i16x32_i64x2(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u64x2>)
			{
				return EmuSIMD::Funcs::cvt_i16x32_u64x2(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i64x4>)
			{
				return EmuSIMD::Funcs::cvt_i16x32_i64x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u64x4>)
			{
				return EmuSIMD::Funcs::cvt_i16x32_u64x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i64x8>)
			{
				return EmuSIMD::Funcs::cvt_i16x32_i64x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u64x8>)
			{
				return EmuSIMD::Funcs::cvt_i16x32_u64x8(from_);
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<ToRegister_>(), "Attempted to convert a EmuSIMD::i16x32 register via EmuSIMD helpers, but the provided SIMD register to convert to is not supported for this operation.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<ToRegister_>(), "Attempted to convert a EmuSIMD::i16x32 register via EmuSIMD helpers, but the provided register to convert to is not recognisd as a supported SIMD register.");
		}
	}
#pragma endregion

#pragma region CVT_I32
	template<class ToRegister_, std::size_t OutPerElementWidthIfInt_, bool OutSignedIfInt_>
	[[nodiscard]] inline ToRegister_ _cvt_i32x4(EmuSIMD::i32x4_arg from_)
	{
		using to_uq = EmuCore::TMP::remove_ref_cv_t<ToRegister_>;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<to_uq>)
		{
			if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x4>)
			{
				return EmuSIMD::Funcs::cvt_i32x4_f32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x8>)
			{
				return EmuSIMD::Funcs::cvt_i32x4_f32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x16>)
			{
				return EmuSIMD::Funcs::cvt_i32x4_f32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x2>)
			{
				return EmuSIMD::Funcs::cvt_i32x4_f64x2(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x4>)
			{
				return EmuSIMD::Funcs::cvt_i32x4_f64x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x8>)
			{
				return EmuSIMD::Funcs::cvt_i32x4_f64x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i128_generic>)
			{
				if constexpr (OutPerElementWidthIfInt_ == 8)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_i32x4_i8x16(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_i32x4_u8x16(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 16)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_i32x4_i16x8(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_i32x4_u16x8(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 32)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_i32x4_i32x4(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_i32x4_u32x4(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 64)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_i32x4_i64x2(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_i32x4_u64x2(from_);
					}
				}
				else
				{
					static_assert
					(
						EmuCore::TMP::get_false<OutPerElementWidthIfInt_>(),
						"Attempted to convert a EmuSIMD::i32x4 register to i128_generic via EmuSIMD helpers, but the provided width per element is invalid. Only 8, 16, 32, and 64 are valid values."
					);
				}
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i256_generic>)
			{
				if constexpr (OutPerElementWidthIfInt_ == 8)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_i32x4_i8x32(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_i32x4_u8x32(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 16)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_i32x4_i16x16(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_i32x4_u16x16(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 32)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_i32x4_i32x8(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_i32x4_u32x8(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 64)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_i32x4_i64x4(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_i32x4_u64x4(from_);
					}
				}
				else
				{
					static_assert
					(
						EmuCore::TMP::get_false<OutPerElementWidthIfInt_>(),
						"Attempted to convert a EmuSIMD::i32x4 register to i256_generic via EmuSIMD helpers, but the provided width per element is invalid. Only 8, 16, 32, and 64 are valid values."
					);
				}
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i512_generic>)
			{
				if constexpr (OutPerElementWidthIfInt_ == 8)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_i32x4_i8x64(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_i32x4_u8x64(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 16)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_i32x4_i16x32(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_i32x4_u16x32(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 32)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_i32x4_i32x16(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_i32x4_u32x16(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 64)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_i32x4_i64x8(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_i32x4_u64x8(from_);
					}
				}
				else
				{
					static_assert
					(
						EmuCore::TMP::get_false<OutPerElementWidthIfInt_>(),
						"Attempted to convert a EmuSIMD::i32x4 register to i512_generic via EmuSIMD helpers, but the provided width per element is invalid. Only 8, 16, 32, and 64 are valid values."
					);
				}
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i8x16>)
			{
				return EmuSIMD::Funcs::cvt_i32x4_i8x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u8x16>)
			{
				return EmuSIMD::Funcs::cvt_i32x4_u8x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i8x32>)
			{
				return EmuSIMD::Funcs::cvt_i32x4_i8x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u8x32>)
			{
				return EmuSIMD::Funcs::cvt_i32x4_u8x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i8x64>)
			{
				return EmuSIMD::Funcs::cvt_i32x4_i8x64(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u8x64>)
			{
				return EmuSIMD::Funcs::cvt_i32x4_u8x64(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i16x8>)
			{
				return EmuSIMD::Funcs::cvt_i32x4_i16x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u16x8>)
			{
				return EmuSIMD::Funcs::cvt_i32x4_u16x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i16x16>)
			{
				return EmuSIMD::Funcs::cvt_i32x4_i16x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u16x16>)
			{
				return EmuSIMD::Funcs::cvt_i32x4_u16x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i16x32>)
			{
				return EmuSIMD::Funcs::cvt_i32x4_i16x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u16x32>)
			{
				return EmuSIMD::Funcs::cvt_i32x4_u16x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i32x4>)
			{
				return EmuSIMD::Funcs::cvt_i32x4_i32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u32x4>)
			{
				return EmuSIMD::Funcs::cvt_i32x4_u32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i32x8>)
			{
				return EmuSIMD::Funcs::cvt_i32x4_i32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u32x8>)
			{
				return EmuSIMD::Funcs::cvt_i32x4_u32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i32x16>)
			{
				return EmuSIMD::Funcs::cvt_i32x4_i32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u32x16>)
			{
				return EmuSIMD::Funcs::cvt_i32x4_u32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i64x2>)
			{
				return EmuSIMD::Funcs::cvt_i32x4_i64x2(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u64x2>)
			{
				return EmuSIMD::Funcs::cvt_i32x4_u64x2(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i64x4>)
			{
				return EmuSIMD::Funcs::cvt_i32x4_i64x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u64x4>)
			{
				return EmuSIMD::Funcs::cvt_i32x4_u64x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i64x8>)
			{
				return EmuSIMD::Funcs::cvt_i32x4_i64x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u64x8>)
			{
				return EmuSIMD::Funcs::cvt_i32x4_u64x8(from_);
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<ToRegister_>(), "Attempted to convert a EmuSIMD::i32x4 register via EmuSIMD helpers, but the provided SIMD register to convert to is not supported for this operation.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<ToRegister_>(), "Attempted to convert a EmuSIMD::i32x4 register via EmuSIMD helpers, but the provided register to convert to is not recognisd as a supported SIMD register.");
		}
	}

	template<class ToRegister_, std::size_t OutPerElementWidthIfInt_, bool OutSignedIfInt_>
	[[nodiscard]] inline ToRegister_ _cvt_i32x8(EmuSIMD::i32x8_arg from_)
	{
		using to_uq = EmuCore::TMP::remove_ref_cv_t<ToRegister_>;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<to_uq>)
		{
			if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x4>)
			{
				return EmuSIMD::Funcs::cvt_i32x8_f32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x8>)
			{
				return EmuSIMD::Funcs::cvt_i32x8_f32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x16>)
			{
				return EmuSIMD::Funcs::cvt_i32x8_f32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x2>)
			{
				return EmuSIMD::Funcs::cvt_i32x8_f64x2(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x4>)
			{
				return EmuSIMD::Funcs::cvt_i32x8_f64x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x8>)
			{
				return EmuSIMD::Funcs::cvt_i32x8_f64x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i128_generic>)
			{
				if constexpr (OutPerElementWidthIfInt_ == 8)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_i32x8_i8x16(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_i32x8_u8x16(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 16)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_i32x8_i16x8(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_i32x8_u16x8(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 32)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_i32x8_i32x4(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_i32x8_u32x4(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 64)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_i32x8_i64x2(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_i32x8_u64x2(from_);
					}
				}
				else
				{
					static_assert
					(
						EmuCore::TMP::get_false<OutPerElementWidthIfInt_>(),
						"Attempted to convert a EmuSIMD::i32x8 register to i128_generic via EmuSIMD helpers, but the provided width per element is invalid. Only 8, 16, 32, and 64 are valid values."
					);
				}
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i256_generic>)
			{
				if constexpr (OutPerElementWidthIfInt_ == 8)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_i32x8_i8x32(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_i32x8_u8x32(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 16)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_i32x8_i16x16(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_i32x8_u16x16(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 32)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_i32x8_i32x8(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_i32x8_u32x8(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 64)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_i32x8_i64x4(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_i32x8_u64x4(from_);
					}
				}
				else
				{
					static_assert
					(
						EmuCore::TMP::get_false<OutPerElementWidthIfInt_>(),
						"Attempted to convert a EmuSIMD::i32x8 register to i256_generic via EmuSIMD helpers, but the provided width per element is invalid. Only 8, 16, 32, and 64 are valid values."
					);
				}
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i512_generic>)
			{
				if constexpr (OutPerElementWidthIfInt_ == 8)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_i32x8_i8x64(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_i32x8_u8x64(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 16)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_i32x8_i16x32(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_i32x8_u16x32(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 32)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_i32x8_i32x16(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_i32x8_u32x16(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 64)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_i32x8_i64x8(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_i32x8_u64x8(from_);
					}
				}
				else
				{
					static_assert
					(
						EmuCore::TMP::get_false<OutPerElementWidthIfInt_>(),
						"Attempted to convert a EmuSIMD::i32x8 register to i512_generic via EmuSIMD helpers, but the provided width per element is invalid. Only 8, 16, 32, and 64 are valid values."
					);
				}
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i8x16>)
			{
				return EmuSIMD::Funcs::cvt_i32x8_i8x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u8x16>)
			{
				return EmuSIMD::Funcs::cvt_i32x8_u8x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i8x32>)
			{
				return EmuSIMD::Funcs::cvt_i32x8_i8x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u8x32>)
			{
				return EmuSIMD::Funcs::cvt_i32x8_u8x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i8x64>)
			{
				return EmuSIMD::Funcs::cvt_i32x8_i8x64(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u8x64>)
			{
				return EmuSIMD::Funcs::cvt_i32x8_u8x64(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i16x8>)
			{
				return EmuSIMD::Funcs::cvt_i32x8_i16x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u16x8>)
			{
				return EmuSIMD::Funcs::cvt_i32x8_u16x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i16x16>)
			{
				return EmuSIMD::Funcs::cvt_i32x8_i16x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u16x16>)
			{
				return EmuSIMD::Funcs::cvt_i32x8_u16x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i16x32>)
			{
				return EmuSIMD::Funcs::cvt_i32x8_i16x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u16x32>)
			{
				return EmuSIMD::Funcs::cvt_i32x8_u16x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i32x4>)
			{
				return EmuSIMD::Funcs::cvt_i32x8_i32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u32x4>)
			{
				return EmuSIMD::Funcs::cvt_i32x8_u32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i32x8>)
			{
				return EmuSIMD::Funcs::cvt_i32x8_i32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u32x8>)
			{
				return EmuSIMD::Funcs::cvt_i32x8_u32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i32x16>)
			{
				return EmuSIMD::Funcs::cvt_i32x8_i32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u32x16>)
			{
				return EmuSIMD::Funcs::cvt_i32x8_u32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i64x2>)
			{
				return EmuSIMD::Funcs::cvt_i32x8_i64x2(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u64x2>)
			{
				return EmuSIMD::Funcs::cvt_i32x8_u64x2(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i64x4>)
			{
				return EmuSIMD::Funcs::cvt_i32x8_i64x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u64x4>)
			{
				return EmuSIMD::Funcs::cvt_i32x8_u64x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i64x8>)
			{
				return EmuSIMD::Funcs::cvt_i32x8_i64x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u64x8>)
			{
				return EmuSIMD::Funcs::cvt_i32x8_u64x8(from_);
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<ToRegister_>(), "Attempted to convert a EmuSIMD::i32x8 register via EmuSIMD helpers, but the provided SIMD register to convert to is not supported for this operation.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<ToRegister_>(), "Attempted to convert a EmuSIMD::i32x8 register via EmuSIMD helpers, but the provided register to convert to is not recognisd as a supported SIMD register.");
		}
	}

	template<class ToRegister_, std::size_t OutPerElementWidthIfInt_, bool OutSignedIfInt_>
	[[nodiscard]] inline ToRegister_ _cvt_i32x16(EmuSIMD::i32x16_arg from_)
	{
		using to_uq = EmuCore::TMP::remove_ref_cv_t<ToRegister_>;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<to_uq>)
		{
			if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x4>)
			{
				return EmuSIMD::Funcs::cvt_i32x16_f32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x8>)
			{
				return EmuSIMD::Funcs::cvt_i32x16_f32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x16>)
			{
				return EmuSIMD::Funcs::cvt_i32x16_f32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x2>)
			{
				return EmuSIMD::Funcs::cvt_i32x16_f64x2(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x4>)
			{
				return EmuSIMD::Funcs::cvt_i32x16_f64x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x8>)
			{
				return EmuSIMD::Funcs::cvt_i32x16_f64x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i128_generic>)
			{
				if constexpr (OutPerElementWidthIfInt_ == 8)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_i32x16_i8x16(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_i32x16_u8x16(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 16)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_i32x16_i16x8(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_i32x16_u16x8(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 32)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_i32x16_i32x4(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_i32x16_u32x4(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 64)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_i32x16_i64x2(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_i32x16_u64x2(from_);
					}
				}
				else
				{
					static_assert
					(
						EmuCore::TMP::get_false<OutPerElementWidthIfInt_>(),
						"Attempted to convert a EmuSIMD::i32x16 register to i128_generic via EmuSIMD helpers, but the provided width per element is invalid. Only 8, 16, 32, and 64 are valid values."
					);
				}
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i256_generic>)
			{
				if constexpr (OutPerElementWidthIfInt_ == 8)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_i32x16_i8x32(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_i32x16_u8x32(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 16)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_i32x16_i16x16(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_i32x16_u16x16(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 32)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_i32x16_i32x8(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_i32x16_u32x8(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 64)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_i32x16_i64x4(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_i32x16_u64x4(from_);
					}
				}
				else
				{
					static_assert
					(
						EmuCore::TMP::get_false<OutPerElementWidthIfInt_>(),
						"Attempted to convert a EmuSIMD::i32x16 register to i256_generic via EmuSIMD helpers, but the provided width per element is invalid. Only 8, 16, 32, and 64 are valid values."
					);
				}
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i512_generic>)
			{
				if constexpr (OutPerElementWidthIfInt_ == 8)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_i32x16_i8x64(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_i32x16_u8x64(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 16)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_i32x16_i16x32(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_i32x16_u16x32(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 32)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_i32x16_i32x16(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_i32x16_u32x16(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 64)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_i32x16_i64x8(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_i32x16_u64x8(from_);
					}
				}
				else
				{
					static_assert
					(
						EmuCore::TMP::get_false<OutPerElementWidthIfInt_>(),
						"Attempted to convert a EmuSIMD::i32x16 register to i512_generic via EmuSIMD helpers, but the provided width per element is invalid. Only 8, 16, 32, and 64 are valid values."
					);
				}
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i8x16>)
			{
				return EmuSIMD::Funcs::cvt_i32x16_i8x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u8x16>)
			{
				return EmuSIMD::Funcs::cvt_i32x16_u8x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i8x32>)
			{
				return EmuSIMD::Funcs::cvt_i32x16_i8x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u8x32>)
			{
				return EmuSIMD::Funcs::cvt_i32x16_u8x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i8x64>)
			{
				return EmuSIMD::Funcs::cvt_i32x16_i8x64(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u8x64>)
			{
				return EmuSIMD::Funcs::cvt_i32x16_u8x64(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i16x8>)
			{
				return EmuSIMD::Funcs::cvt_i32x16_i16x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u16x8>)
			{
				return EmuSIMD::Funcs::cvt_i32x16_u16x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i16x16>)
			{
				return EmuSIMD::Funcs::cvt_i32x16_i16x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u16x16>)
			{
				return EmuSIMD::Funcs::cvt_i32x16_u16x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i16x32>)
			{
				return EmuSIMD::Funcs::cvt_i32x16_i16x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u16x32>)
			{
				return EmuSIMD::Funcs::cvt_i32x16_u16x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i32x4>)
			{
				return EmuSIMD::Funcs::cvt_i32x16_i32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u32x4>)
			{
				return EmuSIMD::Funcs::cvt_i32x16_u32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i32x8>)
			{
				return EmuSIMD::Funcs::cvt_i32x16_i32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u32x8>)
			{
				return EmuSIMD::Funcs::cvt_i32x16_u32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i32x16>)
			{
				return EmuSIMD::Funcs::cvt_i32x16_i32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u32x16>)
			{
				return EmuSIMD::Funcs::cvt_i32x16_u32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i64x2>)
			{
				return EmuSIMD::Funcs::cvt_i32x16_i64x2(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u64x2>)
			{
				return EmuSIMD::Funcs::cvt_i32x16_u64x2(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i64x4>)
			{
				return EmuSIMD::Funcs::cvt_i32x16_i64x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u64x4>)
			{
				return EmuSIMD::Funcs::cvt_i32x16_u64x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i64x8>)
			{
				return EmuSIMD::Funcs::cvt_i32x16_i64x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u64x8>)
			{
				return EmuSIMD::Funcs::cvt_i32x16_u64x8(from_);
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<ToRegister_>(), "Attempted to convert a EmuSIMD::i32x16 register via EmuSIMD helpers, but the provided SIMD register to convert to is not supported for this operation.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<ToRegister_>(), "Attempted to convert a EmuSIMD::i32x16 register via EmuSIMD helpers, but the provided register to convert to is not recognisd as a supported SIMD register.");
		}
	}
#pragma endregion

#pragma region CVT_I64
	template<class ToRegister_, std::size_t OutPerElementWidthIfInt_, bool OutSignedIfInt_>
	[[nodiscard]] inline ToRegister_ _cvt_i64x2(EmuSIMD::i64x2_arg from_)
	{
		using to_uq = EmuCore::TMP::remove_ref_cv_t<ToRegister_>;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<to_uq>)
		{
			if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x4>)
			{
				return EmuSIMD::Funcs::cvt_i64x2_f32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x8>)
			{
				return EmuSIMD::Funcs::cvt_i64x2_f32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x16>)
			{
				return EmuSIMD::Funcs::cvt_i64x2_f32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x2>)
			{
				return EmuSIMD::Funcs::cvt_i64x2_f64x2(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x4>)
			{
				return EmuSIMD::Funcs::cvt_i64x2_f64x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x8>)
			{
				return EmuSIMD::Funcs::cvt_i64x2_f64x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i128_generic>)
			{
				if constexpr (OutPerElementWidthIfInt_ == 8)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_i64x2_i8x16(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_i64x2_u8x16(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 16)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_i64x2_i16x8(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_i64x2_u16x8(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 32)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_i64x2_i32x4(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_i64x2_u32x4(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 64)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_i64x2_i64x2(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_i64x2_u64x2(from_);
					}
				}
				else
				{
					static_assert
					(
						EmuCore::TMP::get_false<OutPerElementWidthIfInt_>(),
						"Attempted to convert a EmuSIMD::i64x2 register to i128_generic via EmuSIMD helpers, but the provided width per element is invalid. Only 8, 16, 32, and 64 are valid values."
					);
				}
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i256_generic>)
			{
				if constexpr (OutPerElementWidthIfInt_ == 8)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_i64x2_i8x32(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_i64x2_u8x32(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 16)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_i64x2_i16x16(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_i64x2_u16x16(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 32)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_i64x2_i32x8(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_i64x2_u32x8(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 64)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_i64x2_i64x4(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_i64x2_u64x4(from_);
					}
				}
				else
				{
					static_assert
					(
						EmuCore::TMP::get_false<OutPerElementWidthIfInt_>(),
						"Attempted to convert a EmuSIMD::i64x2 register to i256_generic via EmuSIMD helpers, but the provided width per element is invalid. Only 8, 16, 32, and 64 are valid values."
					);
				}
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i512_generic>)
			{
				if constexpr (OutPerElementWidthIfInt_ == 8)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_i64x2_i8x64(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_i64x2_u8x64(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 16)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_i64x2_i16x32(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_i64x2_u16x32(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 32)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_i64x2_i32x16(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_i64x2_u32x16(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 64)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_i64x2_i64x8(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_i64x2_u64x8(from_);
					}
				}
				else
				{
					static_assert
					(
						EmuCore::TMP::get_false<OutPerElementWidthIfInt_>(),
						"Attempted to convert a EmuSIMD::i64x2 register to i512_generic via EmuSIMD helpers, but the provided width per element is invalid. Only 8, 16, 32, and 64 are valid values."
					);
				}
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i8x16>)
			{
				return EmuSIMD::Funcs::cvt_i64x2_i8x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u8x16>)
			{
				return EmuSIMD::Funcs::cvt_i64x2_u8x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i8x32>)
			{
				return EmuSIMD::Funcs::cvt_i64x2_i8x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u8x32>)
			{
				return EmuSIMD::Funcs::cvt_i64x2_u8x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i8x64>)
			{
				return EmuSIMD::Funcs::cvt_i64x2_i8x64(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u8x64>)
			{
				return EmuSIMD::Funcs::cvt_i64x2_u8x64(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i16x8>)
			{
				return EmuSIMD::Funcs::cvt_i64x2_i16x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u16x8>)
			{
				return EmuSIMD::Funcs::cvt_i64x2_u16x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i16x16>)
			{
				return EmuSIMD::Funcs::cvt_i64x2_i16x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u16x16>)
			{
				return EmuSIMD::Funcs::cvt_i64x2_u16x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i16x32>)
			{
				return EmuSIMD::Funcs::cvt_i64x2_i16x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u16x32>)
			{
				return EmuSIMD::Funcs::cvt_i64x2_u16x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i32x4>)
			{
				return EmuSIMD::Funcs::cvt_i64x2_i32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u32x4>)
			{
				return EmuSIMD::Funcs::cvt_i64x2_u32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i32x8>)
			{
				return EmuSIMD::Funcs::cvt_i64x2_i32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u32x8>)
			{
				return EmuSIMD::Funcs::cvt_i64x2_u32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i32x16>)
			{
				return EmuSIMD::Funcs::cvt_i64x2_i32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u32x16>)
			{
				return EmuSIMD::Funcs::cvt_i64x2_u32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i64x2>)
			{
				return EmuSIMD::Funcs::cvt_i64x2_i64x2(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u64x2>)
			{
				return EmuSIMD::Funcs::cvt_i64x2_u64x2(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i64x4>)
			{
				return EmuSIMD::Funcs::cvt_i64x2_i64x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u64x4>)
			{
				return EmuSIMD::Funcs::cvt_i64x2_u64x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i64x8>)
			{
				return EmuSIMD::Funcs::cvt_i64x2_i64x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u64x8>)
			{
				return EmuSIMD::Funcs::cvt_i64x2_u64x8(from_);
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<ToRegister_>(), "Attempted to convert a EmuSIMD::i64x2 register via EmuSIMD helpers, but the provided SIMD register to convert to is not supported for this operation.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<ToRegister_>(), "Attempted to convert a EmuSIMD::i64x2 register via EmuSIMD helpers, but the provided register to convert to is not recognisd as a supported SIMD register.");
		}
	}

	template<class ToRegister_, std::size_t OutPerElementWidthIfInt_, bool OutSignedIfInt_>
	[[nodiscard]] inline ToRegister_ _cvt_i64x4(EmuSIMD::i64x4_arg from_)
	{
		using to_uq = EmuCore::TMP::remove_ref_cv_t<ToRegister_>;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<to_uq>)
		{
			if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x4>)
			{
				return EmuSIMD::Funcs::cvt_i64x4_f32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x8>)
			{
				return EmuSIMD::Funcs::cvt_i64x4_f32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x16>)
			{
				return EmuSIMD::Funcs::cvt_i64x4_f32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x2>)
			{
				return EmuSIMD::Funcs::cvt_i64x4_f64x2(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x4>)
			{
				return EmuSIMD::Funcs::cvt_i64x4_f64x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x8>)
			{
				return EmuSIMD::Funcs::cvt_i64x4_f64x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i128_generic>)
			{
				if constexpr (OutPerElementWidthIfInt_ == 8)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_i64x4_i8x16(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_i64x4_u8x16(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 16)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_i64x4_i16x8(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_i64x4_u16x8(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 32)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_i64x4_i32x4(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_i64x4_u32x4(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 64)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_i64x4_i64x2(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_i64x4_u64x2(from_);
					}
				}
				else
				{
					static_assert
					(
						EmuCore::TMP::get_false<OutPerElementWidthIfInt_>(),
						"Attempted to convert a EmuSIMD::i64x4 register to i128_generic via EmuSIMD helpers, but the provided width per element is invalid. Only 8, 16, 32, and 64 are valid values."
					);
				}
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i256_generic>)
			{
				if constexpr (OutPerElementWidthIfInt_ == 8)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_i64x4_i8x32(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_i64x4_u8x32(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 16)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_i64x4_i16x16(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_i64x4_u16x16(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 32)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_i64x4_i32x8(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_i64x4_u32x8(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 64)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_i64x4_i64x4(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_i64x4_u64x4(from_);
					}
				}
				else
				{
					static_assert
					(
						EmuCore::TMP::get_false<OutPerElementWidthIfInt_>(),
						"Attempted to convert a EmuSIMD::i64x4 register to i256_generic via EmuSIMD helpers, but the provided width per element is invalid. Only 8, 16, 32, and 64 are valid values."
					);
				}
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i512_generic>)
			{
				if constexpr (OutPerElementWidthIfInt_ == 8)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_i64x4_i8x64(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_i64x4_u8x64(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 16)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_i64x4_i16x32(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_i64x4_u16x32(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 32)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_i64x4_i32x16(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_i64x4_u32x16(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 64)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_i64x4_i64x8(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_i64x4_u64x8(from_);
					}
				}
				else
				{
					static_assert
					(
						EmuCore::TMP::get_false<OutPerElementWidthIfInt_>(),
						"Attempted to convert a EmuSIMD::i64x4 register to i512_generic via EmuSIMD helpers, but the provided width per element is invalid. Only 8, 16, 32, and 64 are valid values."
					);
				}
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i8x16>)
			{
				return EmuSIMD::Funcs::cvt_i64x4_i8x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u8x16>)
			{
				return EmuSIMD::Funcs::cvt_i64x4_u8x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i8x32>)
			{
				return EmuSIMD::Funcs::cvt_i64x4_i8x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u8x32>)
			{
				return EmuSIMD::Funcs::cvt_i64x4_u8x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i8x64>)
			{
				return EmuSIMD::Funcs::cvt_i64x4_i8x64(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u8x64>)
			{
				return EmuSIMD::Funcs::cvt_i64x4_u8x64(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i16x8>)
			{
				return EmuSIMD::Funcs::cvt_i64x4_i16x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u16x8>)
			{
				return EmuSIMD::Funcs::cvt_i64x4_u16x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i16x16>)
			{
				return EmuSIMD::Funcs::cvt_i64x4_i16x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u16x16>)
			{
				return EmuSIMD::Funcs::cvt_i64x4_u16x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i16x32>)
			{
				return EmuSIMD::Funcs::cvt_i64x4_i16x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u16x32>)
			{
				return EmuSIMD::Funcs::cvt_i64x4_u16x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i32x4>)
			{
				return EmuSIMD::Funcs::cvt_i64x4_i32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u32x4>)
			{
				return EmuSIMD::Funcs::cvt_i64x4_u32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i32x8>)
			{
				return EmuSIMD::Funcs::cvt_i64x4_i32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u32x8>)
			{
				return EmuSIMD::Funcs::cvt_i64x4_u32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i32x16>)
			{
				return EmuSIMD::Funcs::cvt_i64x4_i32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u32x16>)
			{
				return EmuSIMD::Funcs::cvt_i64x4_u32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i64x2>)
			{
				return EmuSIMD::Funcs::cvt_i64x4_i64x2(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u64x2>)
			{
				return EmuSIMD::Funcs::cvt_i64x4_u64x2(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i64x4>)
			{
				return EmuSIMD::Funcs::cvt_i64x4_i64x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u64x4>)
			{
				return EmuSIMD::Funcs::cvt_i64x4_u64x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i64x8>)
			{
				return EmuSIMD::Funcs::cvt_i64x4_i64x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u64x8>)
			{
				return EmuSIMD::Funcs::cvt_i64x4_u64x8(from_);
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<ToRegister_>(), "Attempted to convert a EmuSIMD::i64x4 register via EmuSIMD helpers, but the provided SIMD register to convert to is not supported for this operation.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<ToRegister_>(), "Attempted to convert a EmuSIMD::i64x4 register via EmuSIMD helpers, but the provided register to convert to is not recognisd as a supported SIMD register.");
		}
	}

	template<class ToRegister_, std::size_t OutPerElementWidthIfInt_, bool OutSignedIfInt_>
	[[nodiscard]] inline ToRegister_ _cvt_i64x8(EmuSIMD::i64x8_arg from_)
	{
		using to_uq = EmuCore::TMP::remove_ref_cv_t<ToRegister_>;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<to_uq>)
		{
			if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x4>)
			{
				return EmuSIMD::Funcs::cvt_i64x8_f32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x8>)
			{
				return EmuSIMD::Funcs::cvt_i64x8_f32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x16>)
			{
				return EmuSIMD::Funcs::cvt_i64x8_f32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x2>)
			{
				return EmuSIMD::Funcs::cvt_i64x8_f64x2(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x4>)
			{
				return EmuSIMD::Funcs::cvt_i64x8_f64x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x8>)
			{
				return EmuSIMD::Funcs::cvt_i64x8_f64x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i128_generic>)
			{
				if constexpr (OutPerElementWidthIfInt_ == 8)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_i64x8_i8x16(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_i64x8_u8x16(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 16)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_i64x8_i16x8(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_i64x8_u16x8(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 32)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_i64x8_i32x4(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_i64x8_u32x4(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 64)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_i64x8_i64x2(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_i64x8_u64x2(from_);
					}
				}
				else
				{
					static_assert
					(
						EmuCore::TMP::get_false<OutPerElementWidthIfInt_>(),
						"Attempted to convert a EmuSIMD::i64x8 register to i128_generic via EmuSIMD helpers, but the provided width per element is invalid. Only 8, 16, 32, and 64 are valid values."
					);
				}
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i256_generic>)
			{
				if constexpr (OutPerElementWidthIfInt_ == 8)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_i64x8_i8x32(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_i64x8_u8x32(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 16)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_i64x8_i16x16(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_i64x8_u16x16(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 32)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_i64x8_i32x8(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_i64x8_u32x8(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 64)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_i64x8_i64x4(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_i64x8_u64x4(from_);
					}
				}
				else
				{
					static_assert
					(
						EmuCore::TMP::get_false<OutPerElementWidthIfInt_>(),
						"Attempted to convert a EmuSIMD::i64x8 register to i256_generic via EmuSIMD helpers, but the provided width per element is invalid. Only 8, 16, 32, and 64 are valid values."
					);
				}
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i512_generic>)
			{
				if constexpr (OutPerElementWidthIfInt_ == 8)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_i64x8_i8x64(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_i64x8_u8x64(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 16)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_i64x8_i16x32(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_i64x8_u16x32(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 32)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_i64x8_i32x16(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_i64x8_u32x16(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 64)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_i64x8_i64x8(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_i64x8_u64x8(from_);
					}
				}
				else
				{
					static_assert
					(
						EmuCore::TMP::get_false<OutPerElementWidthIfInt_>(),
						"Attempted to convert a EmuSIMD::i64x8 register to i512_generic via EmuSIMD helpers, but the provided width per element is invalid. Only 8, 16, 32, and 64 are valid values."
					);
				}
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i8x16>)
			{
				return EmuSIMD::Funcs::cvt_i64x8_i8x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u8x16>)
			{
				return EmuSIMD::Funcs::cvt_i64x8_u8x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i8x32>)
			{
				return EmuSIMD::Funcs::cvt_i64x8_i8x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u8x32>)
			{
				return EmuSIMD::Funcs::cvt_i64x8_u8x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i8x64>)
			{
				return EmuSIMD::Funcs::cvt_i64x8_i8x64(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u8x64>)
			{
				return EmuSIMD::Funcs::cvt_i64x8_u8x64(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i16x8>)
			{
				return EmuSIMD::Funcs::cvt_i64x8_i16x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u16x8>)
			{
				return EmuSIMD::Funcs::cvt_i64x8_u16x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i16x16>)
			{
				return EmuSIMD::Funcs::cvt_i64x8_i16x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u16x16>)
			{
				return EmuSIMD::Funcs::cvt_i64x8_u16x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i16x32>)
			{
				return EmuSIMD::Funcs::cvt_i64x8_i16x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u16x32>)
			{
				return EmuSIMD::Funcs::cvt_i64x8_u16x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i32x4>)
			{
				return EmuSIMD::Funcs::cvt_i64x8_i32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u32x4>)
			{
				return EmuSIMD::Funcs::cvt_i64x8_u32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i32x8>)
			{
				return EmuSIMD::Funcs::cvt_i64x8_i32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u32x8>)
			{
				return EmuSIMD::Funcs::cvt_i64x8_u32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i32x16>)
			{
				return EmuSIMD::Funcs::cvt_i64x8_i32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u32x16>)
			{
				return EmuSIMD::Funcs::cvt_i64x8_u32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i64x2>)
			{
				return EmuSIMD::Funcs::cvt_i64x8_i64x2(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u64x2>)
			{
				return EmuSIMD::Funcs::cvt_i64x8_u64x2(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i64x4>)
			{
				return EmuSIMD::Funcs::cvt_i64x8_i64x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u64x4>)
			{
				return EmuSIMD::Funcs::cvt_i64x8_u64x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i64x8>)
			{
				return EmuSIMD::Funcs::cvt_i64x8_i64x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u64x8>)
			{
				return EmuSIMD::Funcs::cvt_i64x8_u64x8(from_);
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<ToRegister_>(), "Attempted to convert a EmuSIMD::i64x8 register via EmuSIMD helpers, but the provided SIMD register to convert to is not supported for this operation.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<ToRegister_>(), "Attempted to convert a EmuSIMD::i64x8 register via EmuSIMD helpers, but the provided register to convert to is not recognisd as a supported SIMD register.");
		}
	}
#pragma endregion

#pragma region CVT_U8
	template<class ToRegister_, std::size_t OutPerElementWidthIfInt_, bool OutSignedIfInt_>
	[[nodiscard]] inline ToRegister_ _cvt_u8x16(EmuSIMD::u8x16_arg from_)
	{
		using to_uq = EmuCore::TMP::remove_ref_cv_t<ToRegister_>;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<to_uq>)
		{
			if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x4>)
			{
				return EmuSIMD::Funcs::cvt_u8x16_f32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x8>)
			{
				return EmuSIMD::Funcs::cvt_u8x16_f32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x16>)
			{
				return EmuSIMD::Funcs::cvt_u8x16_f32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x2>)
			{
				return EmuSIMD::Funcs::cvt_u8x16_f64x2(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x4>)
			{
				return EmuSIMD::Funcs::cvt_u8x16_f64x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x8>)
			{
				return EmuSIMD::Funcs::cvt_u8x16_f64x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i128_generic>)
			{
				if constexpr (OutPerElementWidthIfInt_ == 8)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_u8x16_i8x16(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_u8x16_u8x16(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 16)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_u8x16_i16x8(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_u8x16_u16x8(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 32)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_u8x16_i32x4(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_u8x16_u32x4(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 64)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_u8x16_i64x2(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_u8x16_u64x2(from_);
					}
				}
				else
				{
					static_assert
						(
							EmuCore::TMP::get_false<OutPerElementWidthIfInt_>(),
							"Attempted to convert a EmuSIMD::u8x16 register to i128_generic via EmuSIMD helpers, but the provided width per element is invalid. Only 8, 16, 32, and 64 are valid values."
							);
				}
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i256_generic>)
			{
				if constexpr (OutPerElementWidthIfInt_ == 8)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_u8x16_i8x32(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_u8x16_u8x32(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 16)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_u8x16_i16x16(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_u8x16_u16x16(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 32)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_u8x16_i32x8(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_u8x16_u32x8(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 64)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_u8x16_i64x4(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_u8x16_u64x4(from_);
					}
				}
				else
				{
					static_assert
						(
							EmuCore::TMP::get_false<OutPerElementWidthIfInt_>(),
							"Attempted to convert a EmuSIMD::u8x16 register to i256_generic via EmuSIMD helpers, but the provided width per element is invalid. Only 8, 16, 32, and 64 are valid values."
							);
				}
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i512_generic>)
			{
				if constexpr (OutPerElementWidthIfInt_ == 8)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_u8x16_i8x64(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_u8x16_u8x64(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 16)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_u8x16_i16x32(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_u8x16_u16x32(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 32)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_u8x16_i32x16(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_u8x16_u32x16(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 64)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_u8x16_i64x8(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_u8x16_u64x8(from_);
					}
				}
				else
				{
					static_assert
						(
							EmuCore::TMP::get_false<OutPerElementWidthIfInt_>(),
							"Attempted to convert a EmuSIMD::u8x16 register to i512_generic via EmuSIMD helpers, but the provided width per element is invalid. Only 8, 16, 32, and 64 are valid values."
							);
				}
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i8x16>)
			{
				return EmuSIMD::Funcs::cvt_u8x16_i8x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u8x16>)
			{
				return EmuSIMD::Funcs::cvt_u8x16_u8x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i8x32>)
			{
				return EmuSIMD::Funcs::cvt_u8x16_i8x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u8x32>)
			{
				return EmuSIMD::Funcs::cvt_u8x16_u8x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i8x64>)
			{
				return EmuSIMD::Funcs::cvt_u8x16_i8x64(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u8x64>)
			{
				return EmuSIMD::Funcs::cvt_u8x16_u8x64(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i16x8>)
			{
				return EmuSIMD::Funcs::cvt_u8x16_i16x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u16x8>)
			{
				return EmuSIMD::Funcs::cvt_u8x16_u16x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i16x16>)
			{
				return EmuSIMD::Funcs::cvt_u8x16_i16x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u16x16>)
			{
				return EmuSIMD::Funcs::cvt_u8x16_u16x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i16x32>)
			{
				return EmuSIMD::Funcs::cvt_u8x16_i16x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u16x32>)
			{
				return EmuSIMD::Funcs::cvt_u8x16_u16x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i32x4>)
			{
				return EmuSIMD::Funcs::cvt_u8x16_i32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u32x4>)
			{
				return EmuSIMD::Funcs::cvt_u8x16_u32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i32x8>)
			{
				return EmuSIMD::Funcs::cvt_u8x16_i32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u32x8>)
			{
				return EmuSIMD::Funcs::cvt_u8x16_u32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i32x16>)
			{
				return EmuSIMD::Funcs::cvt_u8x16_i32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u32x16>)
			{
				return EmuSIMD::Funcs::cvt_u8x16_u32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i64x2>)
			{
				return EmuSIMD::Funcs::cvt_u8x16_i64x2(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u64x2>)
			{
				return EmuSIMD::Funcs::cvt_u8x16_u64x2(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i64x4>)
			{
				return EmuSIMD::Funcs::cvt_u8x16_i64x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u64x4>)
			{
				return EmuSIMD::Funcs::cvt_u8x16_u64x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i64x8>)
			{
				return EmuSIMD::Funcs::cvt_u8x16_i64x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u64x8>)
			{
				return EmuSIMD::Funcs::cvt_u8x16_u64x8(from_);
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<ToRegister_>(), "Attempted to convert a EmuSIMD::u8x16 register via EmuSIMD helpers, but the provided SIMD register to convert to is not supported for this operation.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<ToRegister_>(), "Attempted to convert a EmuSIMD::u8x16 register via EmuSIMD helpers, but the provided register to convert to is not recognisd as a supported SIMD register.");
		}
	}

	template<class ToRegister_, std::size_t OutPerElementWidthIfInt_, bool OutSignedIfInt_>
	[[nodiscard]] inline ToRegister_ _cvt_u8x32(EmuSIMD::u8x32_arg from_)
	{
		using to_uq = EmuCore::TMP::remove_ref_cv_t<ToRegister_>;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<to_uq>)
		{
			if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x4>)
			{
				return EmuSIMD::Funcs::cvt_u8x32_f32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x8>)
			{
				return EmuSIMD::Funcs::cvt_u8x32_f32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x16>)
			{
				return EmuSIMD::Funcs::cvt_u8x32_f32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x2>)
			{
				return EmuSIMD::Funcs::cvt_u8x32_f64x2(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x4>)
			{
				return EmuSIMD::Funcs::cvt_u8x32_f64x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x8>)
			{
				return EmuSIMD::Funcs::cvt_u8x32_f64x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i128_generic>)
			{
				if constexpr (OutPerElementWidthIfInt_ == 8)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_u8x32_i8x16(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_u8x32_u8x16(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 16)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_u8x32_i16x8(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_u8x32_u16x8(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 32)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_u8x32_i32x4(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_u8x32_u32x4(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 64)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_u8x32_i64x2(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_u8x32_u64x2(from_);
					}
				}
				else
				{
					static_assert
						(
							EmuCore::TMP::get_false<OutPerElementWidthIfInt_>(),
							"Attempted to convert a EmuSIMD::u8x32 register to i128_generic via EmuSIMD helpers, but the provided width per element is invalid. Only 8, 16, 32, and 64 are valid values."
							);
				}
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i256_generic>)
			{
				if constexpr (OutPerElementWidthIfInt_ == 8)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_u8x32_i8x32(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_u8x32_u8x32(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 16)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_u8x32_i16x16(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_u8x32_u16x16(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 32)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_u8x32_i32x8(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_u8x32_u32x8(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 64)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_u8x32_i64x4(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_u8x32_u64x4(from_);
					}
				}
				else
				{
					static_assert
						(
							EmuCore::TMP::get_false<OutPerElementWidthIfInt_>(),
							"Attempted to convert a EmuSIMD::u8x32 register to i256_generic via EmuSIMD helpers, but the provided width per element is invalid. Only 8, 16, 32, and 64 are valid values."
							);
				}
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i512_generic>)
			{
				if constexpr (OutPerElementWidthIfInt_ == 8)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_u8x32_i8x64(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_u8x32_u8x64(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 16)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_u8x32_i16x32(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_u8x32_u16x32(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 32)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_u8x32_i32x16(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_u8x32_u32x16(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 64)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_u8x32_i64x8(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_u8x32_u64x8(from_);
					}
				}
				else
				{
					static_assert
						(
							EmuCore::TMP::get_false<OutPerElementWidthIfInt_>(),
							"Attempted to convert a EmuSIMD::u8x32 register to i512_generic via EmuSIMD helpers, but the provided width per element is invalid. Only 8, 16, 32, and 64 are valid values."
							);
				}
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i8x16>)
			{
				return EmuSIMD::Funcs::cvt_u8x32_i8x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u8x16>)
			{
				return EmuSIMD::Funcs::cvt_u8x32_u8x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i8x32>)
			{
				return EmuSIMD::Funcs::cvt_u8x32_i8x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u8x32>)
			{
				return EmuSIMD::Funcs::cvt_u8x32_u8x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i8x64>)
			{
				return EmuSIMD::Funcs::cvt_u8x32_i8x64(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u8x64>)
			{
				return EmuSIMD::Funcs::cvt_u8x32_u8x64(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i16x8>)
			{
				return EmuSIMD::Funcs::cvt_u8x32_i16x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u16x8>)
			{
				return EmuSIMD::Funcs::cvt_u8x32_u16x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i16x16>)
			{
				return EmuSIMD::Funcs::cvt_u8x32_i16x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u16x16>)
			{
				return EmuSIMD::Funcs::cvt_u8x32_u16x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i16x32>)
			{
				return EmuSIMD::Funcs::cvt_u8x32_i16x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u16x32>)
			{
				return EmuSIMD::Funcs::cvt_u8x32_u16x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i32x4>)
			{
				return EmuSIMD::Funcs::cvt_u8x32_i32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u32x4>)
			{
				return EmuSIMD::Funcs::cvt_u8x32_u32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i32x8>)
			{
				return EmuSIMD::Funcs::cvt_u8x32_i32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u32x8>)
			{
				return EmuSIMD::Funcs::cvt_u8x32_u32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i32x16>)
			{
				return EmuSIMD::Funcs::cvt_u8x32_i32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u32x16>)
			{
				return EmuSIMD::Funcs::cvt_u8x32_u32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i64x2>)
			{
				return EmuSIMD::Funcs::cvt_u8x32_i64x2(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u64x2>)
			{
				return EmuSIMD::Funcs::cvt_u8x32_u64x2(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i64x4>)
			{
				return EmuSIMD::Funcs::cvt_u8x32_i64x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u64x4>)
			{
				return EmuSIMD::Funcs::cvt_u8x32_u64x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i64x8>)
			{
				return EmuSIMD::Funcs::cvt_u8x32_i64x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u64x8>)
			{
				return EmuSIMD::Funcs::cvt_u8x32_u64x8(from_);
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<ToRegister_>(), "Attempted to convert a EmuSIMD::u8x32 register via EmuSIMD helpers, but the provided SIMD register to convert to is not supported for this operation.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<ToRegister_>(), "Attempted to convert a EmuSIMD::u8x32 register via EmuSIMD helpers, but the provided register to convert to is not recognisd as a supported SIMD register.");
		}
	}

	template<class ToRegister_, std::size_t OutPerElementWidthIfInt_, bool OutSignedIfInt_>
	[[nodiscard]] inline ToRegister_ _cvt_u8x64(EmuSIMD::u8x64_arg from_)
	{
		using to_uq = EmuCore::TMP::remove_ref_cv_t<ToRegister_>;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<to_uq>)
		{
			if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x4>)
			{
				return EmuSIMD::Funcs::cvt_u8x64_f32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x8>)
			{
				return EmuSIMD::Funcs::cvt_u8x64_f32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x16>)
			{
				return EmuSIMD::Funcs::cvt_u8x64_f32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x2>)
			{
				return EmuSIMD::Funcs::cvt_u8x64_f64x2(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x4>)
			{
				return EmuSIMD::Funcs::cvt_u8x64_f64x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x8>)
			{
				return EmuSIMD::Funcs::cvt_u8x64_f64x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i128_generic>)
			{
				if constexpr (OutPerElementWidthIfInt_ == 8)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_u8x64_i8x16(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_u8x64_u8x16(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 16)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_u8x64_i16x8(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_u8x64_u16x8(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 32)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_u8x64_i32x4(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_u8x64_u32x4(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 64)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_u8x64_i64x2(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_u8x64_u64x2(from_);
					}
				}
				else
				{
					static_assert
						(
							EmuCore::TMP::get_false<OutPerElementWidthIfInt_>(),
							"Attempted to convert a EmuSIMD::u8x64 register to i128_generic via EmuSIMD helpers, but the provided width per element is invalid. Only 8, 16, 32, and 64 are valid values."
							);
				}
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i256_generic>)
			{
				if constexpr (OutPerElementWidthIfInt_ == 8)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_u8x64_i8x32(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_u8x64_u8x32(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 16)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_u8x64_i16x16(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_u8x64_u16x16(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 32)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_u8x64_i32x8(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_u8x64_u32x8(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 64)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_u8x64_i64x4(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_u8x64_u64x4(from_);
					}
				}
				else
				{
					static_assert
						(
							EmuCore::TMP::get_false<OutPerElementWidthIfInt_>(),
							"Attempted to convert a EmuSIMD::u8x64 register to i256_generic via EmuSIMD helpers, but the provided width per element is invalid. Only 8, 16, 32, and 64 are valid values."
							);
				}
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i512_generic>)
			{
				if constexpr (OutPerElementWidthIfInt_ == 8)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_u8x64_i8x64(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_u8x64_u8x64(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 16)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_u8x64_i16x32(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_u8x64_u16x32(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 32)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_u8x64_i32x16(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_u8x64_u32x16(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 64)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_u8x64_i64x8(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_u8x64_u64x8(from_);
					}
				}
				else
				{
					static_assert
						(
							EmuCore::TMP::get_false<OutPerElementWidthIfInt_>(),
							"Attempted to convert a EmuSIMD::u8x64 register to i512_generic via EmuSIMD helpers, but the provided width per element is invalid. Only 8, 16, 32, and 64 are valid values."
							);
				}
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i8x16>)
			{
				return EmuSIMD::Funcs::cvt_u8x64_i8x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u8x16>)
			{
				return EmuSIMD::Funcs::cvt_u8x64_u8x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i8x32>)
			{
				return EmuSIMD::Funcs::cvt_u8x64_i8x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u8x32>)
			{
				return EmuSIMD::Funcs::cvt_u8x64_u8x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i8x64>)
			{
				return EmuSIMD::Funcs::cvt_u8x64_i8x64(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u8x64>)
			{
				return EmuSIMD::Funcs::cvt_u8x64_u8x64(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i16x8>)
			{
				return EmuSIMD::Funcs::cvt_u8x64_i16x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u16x8>)
			{
				return EmuSIMD::Funcs::cvt_u8x64_u16x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i16x16>)
			{
				return EmuSIMD::Funcs::cvt_u8x64_i16x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u16x16>)
			{
				return EmuSIMD::Funcs::cvt_u8x64_u16x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i16x32>)
			{
				return EmuSIMD::Funcs::cvt_u8x64_i16x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u16x32>)
			{
				return EmuSIMD::Funcs::cvt_u8x64_u16x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i32x4>)
			{
				return EmuSIMD::Funcs::cvt_u8x64_i32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u32x4>)
			{
				return EmuSIMD::Funcs::cvt_u8x64_u32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i32x8>)
			{
				return EmuSIMD::Funcs::cvt_u8x64_i32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u32x8>)
			{
				return EmuSIMD::Funcs::cvt_u8x64_u32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i32x16>)
			{
				return EmuSIMD::Funcs::cvt_u8x64_i32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u32x16>)
			{
				return EmuSIMD::Funcs::cvt_u8x64_u32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i64x2>)
			{
				return EmuSIMD::Funcs::cvt_u8x64_i64x2(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u64x2>)
			{
				return EmuSIMD::Funcs::cvt_u8x64_u64x2(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i64x4>)
			{
				return EmuSIMD::Funcs::cvt_u8x64_i64x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u64x4>)
			{
				return EmuSIMD::Funcs::cvt_u8x64_u64x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i64x8>)
			{
				return EmuSIMD::Funcs::cvt_u8x64_i64x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u64x8>)
			{
				return EmuSIMD::Funcs::cvt_u8x64_u64x8(from_);
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<ToRegister_>(), "Attempted to convert a EmuSIMD::u8x64 register via EmuSIMD helpers, but the provided SIMD register to convert to is not supported for this operation.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<ToRegister_>(), "Attempted to convert a EmuSIMD::u8x64 register via EmuSIMD helpers, but the provided register to convert to is not recognisd as a supported SIMD register.");
		}
	}
#pragma endregion

#pragma region CVT_U16
	template<class ToRegister_, std::size_t OutPerElementWidthIfInt_, bool OutSignedIfInt_>
	[[nodiscard]] inline ToRegister_ _cvt_u16x8(EmuSIMD::u16x8_arg from_)
	{
		using to_uq = EmuCore::TMP::remove_ref_cv_t<ToRegister_>;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<to_uq>)
		{
			if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x4>)
			{
				return EmuSIMD::Funcs::cvt_u16x8_f32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x8>)
			{
				return EmuSIMD::Funcs::cvt_u16x8_f32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x16>)
			{
				return EmuSIMD::Funcs::cvt_u16x8_f32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x2>)
			{
				return EmuSIMD::Funcs::cvt_u16x8_f64x2(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x4>)
			{
				return EmuSIMD::Funcs::cvt_u16x8_f64x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x8>)
			{
				return EmuSIMD::Funcs::cvt_u16x8_f64x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i128_generic>)
			{
				if constexpr (OutPerElementWidthIfInt_ == 8)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_u16x8_i8x16(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_u16x8_u8x16(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 16)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_u16x8_i16x8(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_u16x8_u16x8(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 32)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_u16x8_i32x4(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_u16x8_u32x4(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 64)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_u16x8_i64x2(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_u16x8_u64x2(from_);
					}
				}
				else
				{
					static_assert
						(
							EmuCore::TMP::get_false<OutPerElementWidthIfInt_>(),
							"Attempted to convert a EmuSIMD::u16x8 register to i128_generic via EmuSIMD helpers, but the provided width per element is invalid. Only 8, 16, 32, and 64 are valid values."
							);
				}
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i256_generic>)
			{
				if constexpr (OutPerElementWidthIfInt_ == 8)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_u16x8_i8x32(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_u16x8_u8x32(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 16)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_u16x8_i16x16(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_u16x8_u16x16(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 32)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_u16x8_i32x8(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_u16x8_u32x8(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 64)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_u16x8_i64x4(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_u16x8_u64x4(from_);
					}
				}
				else
				{
					static_assert
						(
							EmuCore::TMP::get_false<OutPerElementWidthIfInt_>(),
							"Attempted to convert a EmuSIMD::u16x8 register to i256_generic via EmuSIMD helpers, but the provided width per element is invalid. Only 8, 16, 32, and 64 are valid values."
							);
				}
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i512_generic>)
			{
				if constexpr (OutPerElementWidthIfInt_ == 8)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_u16x8_i8x64(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_u16x8_u8x64(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 16)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_u16x8_i16x32(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_u16x8_u16x32(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 32)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_u16x8_i32x16(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_u16x8_u32x16(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 64)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_u16x8_i64x8(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_u16x8_u64x8(from_);
					}
				}
				else
				{
					static_assert
						(
							EmuCore::TMP::get_false<OutPerElementWidthIfInt_>(),
							"Attempted to convert a EmuSIMD::u16x8 register to i512_generic via EmuSIMD helpers, but the provided width per element is invalid. Only 8, 16, 32, and 64 are valid values."
							);
				}
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i8x16>)
			{
				return EmuSIMD::Funcs::cvt_u16x8_i8x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u8x16>)
			{
				return EmuSIMD::Funcs::cvt_u16x8_u8x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i8x32>)
			{
				return EmuSIMD::Funcs::cvt_u16x8_i8x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u8x32>)
			{
				return EmuSIMD::Funcs::cvt_u16x8_u8x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i8x64>)
			{
				return EmuSIMD::Funcs::cvt_u16x8_i8x64(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u8x64>)
			{
				return EmuSIMD::Funcs::cvt_u16x8_u8x64(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i16x8>)
			{
				return EmuSIMD::Funcs::cvt_u16x8_i16x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u16x8>)
			{
				return EmuSIMD::Funcs::cvt_u16x8_u16x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i16x16>)
			{
				return EmuSIMD::Funcs::cvt_u16x8_i16x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u16x16>)
			{
				return EmuSIMD::Funcs::cvt_u16x8_u16x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i16x32>)
			{
				return EmuSIMD::Funcs::cvt_u16x8_i16x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u16x32>)
			{
				return EmuSIMD::Funcs::cvt_u16x8_u16x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i32x4>)
			{
				return EmuSIMD::Funcs::cvt_u16x8_i32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u32x4>)
			{
				return EmuSIMD::Funcs::cvt_u16x8_u32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i32x8>)
			{
				return EmuSIMD::Funcs::cvt_u16x8_i32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u32x8>)
			{
				return EmuSIMD::Funcs::cvt_u16x8_u32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i32x16>)
			{
				return EmuSIMD::Funcs::cvt_u16x8_i32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u32x16>)
			{
				return EmuSIMD::Funcs::cvt_u16x8_u32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i64x2>)
			{
				return EmuSIMD::Funcs::cvt_u16x8_i64x2(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u64x2>)
			{
				return EmuSIMD::Funcs::cvt_u16x8_u64x2(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i64x4>)
			{
				return EmuSIMD::Funcs::cvt_u16x8_i64x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u64x4>)
			{
				return EmuSIMD::Funcs::cvt_u16x8_u64x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i64x8>)
			{
				return EmuSIMD::Funcs::cvt_u16x8_i64x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u64x8>)
			{
				return EmuSIMD::Funcs::cvt_u16x8_u64x8(from_);
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<ToRegister_>(), "Attempted to convert a EmuSIMD::u16x8 register via EmuSIMD helpers, but the provided SIMD register to convert to is not supported for this operation.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<ToRegister_>(), "Attempted to convert a EmuSIMD::u16x8 register via EmuSIMD helpers, but the provided register to convert to is not recognisd as a supported SIMD register.");
		}
	}

	template<class ToRegister_, std::size_t OutPerElementWidthIfInt_, bool OutSignedIfInt_>
	[[nodiscard]] inline ToRegister_ _cvt_u16x16(EmuSIMD::u16x16_arg from_)
	{
		using to_uq = EmuCore::TMP::remove_ref_cv_t<ToRegister_>;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<to_uq>)
		{
			if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x4>)
			{
				return EmuSIMD::Funcs::cvt_u16x16_f32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x8>)
			{
				return EmuSIMD::Funcs::cvt_u16x16_f32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x16>)
			{
				return EmuSIMD::Funcs::cvt_u16x16_f32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x2>)
			{
				return EmuSIMD::Funcs::cvt_u16x16_f64x2(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x4>)
			{
				return EmuSIMD::Funcs::cvt_u16x16_f64x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x8>)
			{
				return EmuSIMD::Funcs::cvt_u16x16_f64x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i128_generic>)
			{
				if constexpr (OutPerElementWidthIfInt_ == 8)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_u16x16_i8x16(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_u16x16_u8x16(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 16)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_u16x16_i16x8(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_u16x16_u16x8(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 32)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_u16x16_i32x4(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_u16x16_u32x4(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 64)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_u16x16_i64x2(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_u16x16_u64x2(from_);
					}
				}
				else
				{
					static_assert
						(
							EmuCore::TMP::get_false<OutPerElementWidthIfInt_>(),
							"Attempted to convert a EmuSIMD::u16x16 register to i128_generic via EmuSIMD helpers, but the provided width per element is invalid. Only 8, 16, 32, and 64 are valid values."
							);
				}
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i256_generic>)
			{
				if constexpr (OutPerElementWidthIfInt_ == 8)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_u16x16_i8x32(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_u16x16_u8x32(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 16)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_u16x16_i16x16(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_u16x16_u16x16(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 32)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_u16x16_i32x8(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_u16x16_u32x8(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 64)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_u16x16_i64x4(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_u16x16_u64x4(from_);
					}
				}
				else
				{
					static_assert
						(
							EmuCore::TMP::get_false<OutPerElementWidthIfInt_>(),
							"Attempted to convert a EmuSIMD::u16x16 register to i256_generic via EmuSIMD helpers, but the provided width per element is invalid. Only 8, 16, 32, and 64 are valid values."
							);
				}
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i512_generic>)
			{
				if constexpr (OutPerElementWidthIfInt_ == 8)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_u16x16_i8x64(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_u16x16_u8x64(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 16)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_u16x16_i16x32(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_u16x16_u16x32(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 32)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_u16x16_i32x16(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_u16x16_u32x16(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 64)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_u16x16_i64x8(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_u16x16_u64x8(from_);
					}
				}
				else
				{
					static_assert
						(
							EmuCore::TMP::get_false<OutPerElementWidthIfInt_>(),
							"Attempted to convert a EmuSIMD::u16x16 register to i512_generic via EmuSIMD helpers, but the provided width per element is invalid. Only 8, 16, 32, and 64 are valid values."
							);
				}
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i8x16>)
			{
				return EmuSIMD::Funcs::cvt_u16x16_i8x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u8x16>)
			{
				return EmuSIMD::Funcs::cvt_u16x16_u8x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i8x32>)
			{
				return EmuSIMD::Funcs::cvt_u16x16_i8x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u8x32>)
			{
				return EmuSIMD::Funcs::cvt_u16x16_u8x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i8x64>)
			{
				return EmuSIMD::Funcs::cvt_u16x16_i8x64(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u8x64>)
			{
				return EmuSIMD::Funcs::cvt_u16x16_u8x64(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i16x8>)
			{
				return EmuSIMD::Funcs::cvt_u16x16_i16x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u16x8>)
			{
				return EmuSIMD::Funcs::cvt_u16x16_u16x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i16x16>)
			{
				return EmuSIMD::Funcs::cvt_u16x16_i16x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u16x16>)
			{
				return EmuSIMD::Funcs::cvt_u16x16_u16x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i16x32>)
			{
				return EmuSIMD::Funcs::cvt_u16x16_i16x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u16x32>)
			{
				return EmuSIMD::Funcs::cvt_u16x16_u16x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i32x4>)
			{
				return EmuSIMD::Funcs::cvt_u16x16_i32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u32x4>)
			{
				return EmuSIMD::Funcs::cvt_u16x16_u32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i32x8>)
			{
				return EmuSIMD::Funcs::cvt_u16x16_i32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u32x8>)
			{
				return EmuSIMD::Funcs::cvt_u16x16_u32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i32x16>)
			{
				return EmuSIMD::Funcs::cvt_u16x16_i32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u32x16>)
			{
				return EmuSIMD::Funcs::cvt_u16x16_u32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i64x2>)
			{
				return EmuSIMD::Funcs::cvt_u16x16_i64x2(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u64x2>)
			{
				return EmuSIMD::Funcs::cvt_u16x16_u64x2(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i64x4>)
			{
				return EmuSIMD::Funcs::cvt_u16x16_i64x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u64x4>)
			{
				return EmuSIMD::Funcs::cvt_u16x16_u64x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i64x8>)
			{
				return EmuSIMD::Funcs::cvt_u16x16_i64x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u64x8>)
			{
				return EmuSIMD::Funcs::cvt_u16x16_u64x8(from_);
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<ToRegister_>(), "Attempted to convert a EmuSIMD::u16x16 register via EmuSIMD helpers, but the provided SIMD register to convert to is not supported for this operation.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<ToRegister_>(), "Attempted to convert a EmuSIMD::u16x16 register via EmuSIMD helpers, but the provided register to convert to is not recognisd as a supported SIMD register.");
		}
	}

	template<class ToRegister_, std::size_t OutPerElementWidthIfInt_, bool OutSignedIfInt_>
	[[nodiscard]] inline ToRegister_ _cvt_u16x32(EmuSIMD::u16x32_arg from_)
	{
		using to_uq = EmuCore::TMP::remove_ref_cv_t<ToRegister_>;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<to_uq>)
		{
			if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x4>)
			{
				return EmuSIMD::Funcs::cvt_u16x32_f32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x8>)
			{
				return EmuSIMD::Funcs::cvt_u16x32_f32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x16>)
			{
				return EmuSIMD::Funcs::cvt_u16x32_f32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x2>)
			{
				return EmuSIMD::Funcs::cvt_u16x32_f64x2(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x4>)
			{
				return EmuSIMD::Funcs::cvt_u16x32_f64x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x8>)
			{
				return EmuSIMD::Funcs::cvt_u16x32_f64x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i128_generic>)
			{
				if constexpr (OutPerElementWidthIfInt_ == 8)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_u16x32_i8x16(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_u16x32_u8x16(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 16)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_u16x32_i16x8(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_u16x32_u16x8(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 32)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_u16x32_i32x4(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_u16x32_u32x4(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 64)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_u16x32_i64x2(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_u16x32_u64x2(from_);
					}
				}
				else
				{
					static_assert
						(
							EmuCore::TMP::get_false<OutPerElementWidthIfInt_>(),
							"Attempted to convert a EmuSIMD::u16x32 register to i128_generic via EmuSIMD helpers, but the provided width per element is invalid. Only 8, 16, 32, and 64 are valid values."
							);
				}
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i256_generic>)
			{
				if constexpr (OutPerElementWidthIfInt_ == 8)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_u16x32_i8x32(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_u16x32_u8x32(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 16)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_u16x32_i16x16(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_u16x32_u16x16(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 32)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_u16x32_i32x8(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_u16x32_u32x8(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 64)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_u16x32_i64x4(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_u16x32_u64x4(from_);
					}
				}
				else
				{
					static_assert
						(
							EmuCore::TMP::get_false<OutPerElementWidthIfInt_>(),
							"Attempted to convert a EmuSIMD::u16x32 register to i256_generic via EmuSIMD helpers, but the provided width per element is invalid. Only 8, 16, 32, and 64 are valid values."
							);
				}
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i512_generic>)
			{
				if constexpr (OutPerElementWidthIfInt_ == 8)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_u16x32_i8x64(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_u16x32_u8x64(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 16)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_u16x32_i16x32(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_u16x32_u16x32(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 32)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_u16x32_i32x16(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_u16x32_u32x16(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 64)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_u16x32_i64x8(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_u16x32_u64x8(from_);
					}
				}
				else
				{
					static_assert
						(
							EmuCore::TMP::get_false<OutPerElementWidthIfInt_>(),
							"Attempted to convert a EmuSIMD::u16x32 register to i512_generic via EmuSIMD helpers, but the provided width per element is invalid. Only 8, 16, 32, and 64 are valid values."
							);
				}
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i8x16>)
			{
				return EmuSIMD::Funcs::cvt_u16x32_i8x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u8x16>)
			{
				return EmuSIMD::Funcs::cvt_u16x32_u8x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i8x32>)
			{
				return EmuSIMD::Funcs::cvt_u16x32_i8x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u8x32>)
			{
				return EmuSIMD::Funcs::cvt_u16x32_u8x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i8x64>)
			{
				return EmuSIMD::Funcs::cvt_u16x32_i8x64(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u8x64>)
			{
				return EmuSIMD::Funcs::cvt_u16x32_u8x64(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i16x8>)
			{
				return EmuSIMD::Funcs::cvt_u16x32_i16x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u16x8>)
			{
				return EmuSIMD::Funcs::cvt_u16x32_u16x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i16x16>)
			{
				return EmuSIMD::Funcs::cvt_u16x32_i16x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u16x16>)
			{
				return EmuSIMD::Funcs::cvt_u16x32_u16x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i16x32>)
			{
				return EmuSIMD::Funcs::cvt_u16x32_i16x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u16x32>)
			{
				return EmuSIMD::Funcs::cvt_u16x32_u16x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i32x4>)
			{
				return EmuSIMD::Funcs::cvt_u16x32_i32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u32x4>)
			{
				return EmuSIMD::Funcs::cvt_u16x32_u32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i32x8>)
			{
				return EmuSIMD::Funcs::cvt_u16x32_i32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u32x8>)
			{
				return EmuSIMD::Funcs::cvt_u16x32_u32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i32x16>)
			{
				return EmuSIMD::Funcs::cvt_u16x32_i32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u32x16>)
			{
				return EmuSIMD::Funcs::cvt_u16x32_u32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i64x2>)
			{
				return EmuSIMD::Funcs::cvt_u16x32_i64x2(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u64x2>)
			{
				return EmuSIMD::Funcs::cvt_u16x32_u64x2(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i64x4>)
			{
				return EmuSIMD::Funcs::cvt_u16x32_i64x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u64x4>)
			{
				return EmuSIMD::Funcs::cvt_u16x32_u64x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i64x8>)
			{
				return EmuSIMD::Funcs::cvt_u16x32_i64x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u64x8>)
			{
				return EmuSIMD::Funcs::cvt_u16x32_u64x8(from_);
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<ToRegister_>(), "Attempted to convert a EmuSIMD::u16x32 register via EmuSIMD helpers, but the provided SIMD register to convert to is not supported for this operation.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<ToRegister_>(), "Attempted to convert a EmuSIMD::u16x32 register via EmuSIMD helpers, but the provided register to convert to is not recognisd as a supported SIMD register.");
		}
	}
#pragma endregion

#pragma region CVT_U32
	template<class ToRegister_, std::size_t OutPerElementWidthIfInt_, bool OutSignedIfInt_>
	[[nodiscard]] inline ToRegister_ _cvt_u32x4(EmuSIMD::u32x4_arg from_)
	{
		using to_uq = EmuCore::TMP::remove_ref_cv_t<ToRegister_>;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<to_uq>)
		{
			if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x4>)
			{
				return EmuSIMD::Funcs::cvt_u32x4_f32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x8>)
			{
				return EmuSIMD::Funcs::cvt_u32x4_f32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x16>)
			{
				return EmuSIMD::Funcs::cvt_u32x4_f32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x2>)
			{
				return EmuSIMD::Funcs::cvt_u32x4_f64x2(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x4>)
			{
				return EmuSIMD::Funcs::cvt_u32x4_f64x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x8>)
			{
				return EmuSIMD::Funcs::cvt_u32x4_f64x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i128_generic>)
			{
				if constexpr (OutPerElementWidthIfInt_ == 8)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_u32x4_i8x16(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_u32x4_u8x16(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 16)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_u32x4_i16x8(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_u32x4_u16x8(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 32)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_u32x4_i32x4(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_u32x4_u32x4(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 64)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_u32x4_i64x2(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_u32x4_u64x2(from_);
					}
				}
				else
				{
					static_assert
						(
							EmuCore::TMP::get_false<OutPerElementWidthIfInt_>(),
							"Attempted to convert a EmuSIMD::u32x4 register to i128_generic via EmuSIMD helpers, but the provided width per element is invalid. Only 8, 16, 32, and 64 are valid values."
							);
				}
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i256_generic>)
			{
				if constexpr (OutPerElementWidthIfInt_ == 8)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_u32x4_i8x32(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_u32x4_u8x32(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 16)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_u32x4_i16x16(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_u32x4_u16x16(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 32)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_u32x4_i32x8(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_u32x4_u32x8(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 64)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_u32x4_i64x4(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_u32x4_u64x4(from_);
					}
				}
				else
				{
					static_assert
						(
							EmuCore::TMP::get_false<OutPerElementWidthIfInt_>(),
							"Attempted to convert a EmuSIMD::u32x4 register to i256_generic via EmuSIMD helpers, but the provided width per element is invalid. Only 8, 16, 32, and 64 are valid values."
							);
				}
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i512_generic>)
			{
				if constexpr (OutPerElementWidthIfInt_ == 8)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_u32x4_i8x64(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_u32x4_u8x64(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 16)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_u32x4_i16x32(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_u32x4_u16x32(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 32)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_u32x4_i32x16(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_u32x4_u32x16(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 64)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_u32x4_i64x8(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_u32x4_u64x8(from_);
					}
				}
				else
				{
					static_assert
						(
							EmuCore::TMP::get_false<OutPerElementWidthIfInt_>(),
							"Attempted to convert a EmuSIMD::u32x4 register to i512_generic via EmuSIMD helpers, but the provided width per element is invalid. Only 8, 16, 32, and 64 are valid values."
							);
				}
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i8x16>)
			{
				return EmuSIMD::Funcs::cvt_u32x4_i8x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u8x16>)
			{
				return EmuSIMD::Funcs::cvt_u32x4_u8x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i8x32>)
			{
				return EmuSIMD::Funcs::cvt_u32x4_i8x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u8x32>)
			{
				return EmuSIMD::Funcs::cvt_u32x4_u8x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i8x64>)
			{
				return EmuSIMD::Funcs::cvt_u32x4_i8x64(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u8x64>)
			{
				return EmuSIMD::Funcs::cvt_u32x4_u8x64(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i16x8>)
			{
				return EmuSIMD::Funcs::cvt_u32x4_i16x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u16x8>)
			{
				return EmuSIMD::Funcs::cvt_u32x4_u16x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i16x16>)
			{
				return EmuSIMD::Funcs::cvt_u32x4_i16x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u16x16>)
			{
				return EmuSIMD::Funcs::cvt_u32x4_u16x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i16x32>)
			{
				return EmuSIMD::Funcs::cvt_u32x4_i16x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u16x32>)
			{
				return EmuSIMD::Funcs::cvt_u32x4_u16x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i32x4>)
			{
				return EmuSIMD::Funcs::cvt_u32x4_i32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u32x4>)
			{
				return EmuSIMD::Funcs::cvt_u32x4_u32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i32x8>)
			{
				return EmuSIMD::Funcs::cvt_u32x4_i32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u32x8>)
			{
				return EmuSIMD::Funcs::cvt_u32x4_u32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i32x16>)
			{
				return EmuSIMD::Funcs::cvt_u32x4_i32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u32x16>)
			{
				return EmuSIMD::Funcs::cvt_u32x4_u32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i64x2>)
			{
				return EmuSIMD::Funcs::cvt_u32x4_i64x2(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u64x2>)
			{
				return EmuSIMD::Funcs::cvt_u32x4_u64x2(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i64x4>)
			{
				return EmuSIMD::Funcs::cvt_u32x4_i64x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u64x4>)
			{
				return EmuSIMD::Funcs::cvt_u32x4_u64x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i64x8>)
			{
				return EmuSIMD::Funcs::cvt_u32x4_i64x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u64x8>)
			{
				return EmuSIMD::Funcs::cvt_u32x4_u64x8(from_);
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<ToRegister_>(), "Attempted to convert a EmuSIMD::u32x4 register via EmuSIMD helpers, but the provided SIMD register to convert to is not supported for this operation.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<ToRegister_>(), "Attempted to convert a EmuSIMD::u32x4 register via EmuSIMD helpers, but the provided register to convert to is not recognisd as a supported SIMD register.");
		}
	}

	template<class ToRegister_, std::size_t OutPerElementWidthIfInt_, bool OutSignedIfInt_>
	[[nodiscard]] inline ToRegister_ _cvt_u32x8(EmuSIMD::u32x8_arg from_)
	{
		using to_uq = EmuCore::TMP::remove_ref_cv_t<ToRegister_>;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<to_uq>)
		{
			if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x4>)
			{
				return EmuSIMD::Funcs::cvt_u32x8_f32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x8>)
			{
				return EmuSIMD::Funcs::cvt_u32x8_f32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x16>)
			{
				return EmuSIMD::Funcs::cvt_u32x8_f32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x2>)
			{
				return EmuSIMD::Funcs::cvt_u32x8_f64x2(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x4>)
			{
				return EmuSIMD::Funcs::cvt_u32x8_f64x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x8>)
			{
				return EmuSIMD::Funcs::cvt_u32x8_f64x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i128_generic>)
			{
				if constexpr (OutPerElementWidthIfInt_ == 8)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_u32x8_i8x16(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_u32x8_u8x16(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 16)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_u32x8_i16x8(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_u32x8_u16x8(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 32)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_u32x8_i32x4(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_u32x8_u32x4(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 64)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_u32x8_i64x2(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_u32x8_u64x2(from_);
					}
				}
				else
				{
					static_assert
						(
							EmuCore::TMP::get_false<OutPerElementWidthIfInt_>(),
							"Attempted to convert a EmuSIMD::u32x8 register to i128_generic via EmuSIMD helpers, but the provided width per element is invalid. Only 8, 16, 32, and 64 are valid values."
							);
				}
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i256_generic>)
			{
				if constexpr (OutPerElementWidthIfInt_ == 8)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_u32x8_i8x32(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_u32x8_u8x32(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 16)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_u32x8_i16x16(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_u32x8_u16x16(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 32)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_u32x8_i32x8(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_u32x8_u32x8(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 64)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_u32x8_i64x4(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_u32x8_u64x4(from_);
					}
				}
				else
				{
					static_assert
						(
							EmuCore::TMP::get_false<OutPerElementWidthIfInt_>(),
							"Attempted to convert a EmuSIMD::u32x8 register to i256_generic via EmuSIMD helpers, but the provided width per element is invalid. Only 8, 16, 32, and 64 are valid values."
							);
				}
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i512_generic>)
			{
				if constexpr (OutPerElementWidthIfInt_ == 8)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_u32x8_i8x64(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_u32x8_u8x64(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 16)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_u32x8_i16x32(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_u32x8_u16x32(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 32)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_u32x8_i32x16(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_u32x8_u32x16(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 64)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_u32x8_i64x8(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_u32x8_u64x8(from_);
					}
				}
				else
				{
					static_assert
						(
							EmuCore::TMP::get_false<OutPerElementWidthIfInt_>(),
							"Attempted to convert a EmuSIMD::u32x8 register to i512_generic via EmuSIMD helpers, but the provided width per element is invalid. Only 8, 16, 32, and 64 are valid values."
							);
				}
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i8x16>)
			{
				return EmuSIMD::Funcs::cvt_u32x8_i8x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u8x16>)
			{
				return EmuSIMD::Funcs::cvt_u32x8_u8x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i8x32>)
			{
				return EmuSIMD::Funcs::cvt_u32x8_i8x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u8x32>)
			{
				return EmuSIMD::Funcs::cvt_u32x8_u8x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i8x64>)
			{
				return EmuSIMD::Funcs::cvt_u32x8_i8x64(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u8x64>)
			{
				return EmuSIMD::Funcs::cvt_u32x8_u8x64(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i16x8>)
			{
				return EmuSIMD::Funcs::cvt_u32x8_i16x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u16x8>)
			{
				return EmuSIMD::Funcs::cvt_u32x8_u16x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i16x16>)
			{
				return EmuSIMD::Funcs::cvt_u32x8_i16x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u16x16>)
			{
				return EmuSIMD::Funcs::cvt_u32x8_u16x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i16x32>)
			{
				return EmuSIMD::Funcs::cvt_u32x8_i16x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u16x32>)
			{
				return EmuSIMD::Funcs::cvt_u32x8_u16x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i32x4>)
			{
				return EmuSIMD::Funcs::cvt_u32x8_i32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u32x4>)
			{
				return EmuSIMD::Funcs::cvt_u32x8_u32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i32x8>)
			{
				return EmuSIMD::Funcs::cvt_u32x8_i32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u32x8>)
			{
				return EmuSIMD::Funcs::cvt_u32x8_u32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i32x16>)
			{
				return EmuSIMD::Funcs::cvt_u32x8_i32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u32x16>)
			{
				return EmuSIMD::Funcs::cvt_u32x8_u32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i64x2>)
			{
				return EmuSIMD::Funcs::cvt_u32x8_i64x2(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u64x2>)
			{
				return EmuSIMD::Funcs::cvt_u32x8_u64x2(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i64x4>)
			{
				return EmuSIMD::Funcs::cvt_u32x8_i64x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u64x4>)
			{
				return EmuSIMD::Funcs::cvt_u32x8_u64x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i64x8>)
			{
				return EmuSIMD::Funcs::cvt_u32x8_i64x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u64x8>)
			{
				return EmuSIMD::Funcs::cvt_u32x8_u64x8(from_);
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<ToRegister_>(), "Attempted to convert a EmuSIMD::u32x8 register via EmuSIMD helpers, but the provided SIMD register to convert to is not supported for this operation.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<ToRegister_>(), "Attempted to convert a EmuSIMD::u32x8 register via EmuSIMD helpers, but the provided register to convert to is not recognisd as a supported SIMD register.");
		}
	}

	template<class ToRegister_, std::size_t OutPerElementWidthIfInt_, bool OutSignedIfInt_>
	[[nodiscard]] inline ToRegister_ _cvt_u32x16(EmuSIMD::u32x16_arg from_)
	{
		using to_uq = EmuCore::TMP::remove_ref_cv_t<ToRegister_>;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<to_uq>)
		{
			if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x4>)
			{
				return EmuSIMD::Funcs::cvt_u32x16_f32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x8>)
			{
				return EmuSIMD::Funcs::cvt_u32x16_f32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x16>)
			{
				return EmuSIMD::Funcs::cvt_u32x16_f32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x2>)
			{
				return EmuSIMD::Funcs::cvt_u32x16_f64x2(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x4>)
			{
				return EmuSIMD::Funcs::cvt_u32x16_f64x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x8>)
			{
				return EmuSIMD::Funcs::cvt_u32x16_f64x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i128_generic>)
			{
				if constexpr (OutPerElementWidthIfInt_ == 8)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_u32x16_i8x16(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_u32x16_u8x16(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 16)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_u32x16_i16x8(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_u32x16_u16x8(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 32)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_u32x16_i32x4(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_u32x16_u32x4(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 64)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_u32x16_i64x2(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_u32x16_u64x2(from_);
					}
				}
				else
				{
					static_assert
						(
							EmuCore::TMP::get_false<OutPerElementWidthIfInt_>(),
							"Attempted to convert a EmuSIMD::u32x16 register to i128_generic via EmuSIMD helpers, but the provided width per element is invalid. Only 8, 16, 32, and 64 are valid values."
							);
				}
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i256_generic>)
			{
				if constexpr (OutPerElementWidthIfInt_ == 8)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_u32x16_i8x32(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_u32x16_u8x32(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 16)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_u32x16_i16x16(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_u32x16_u16x16(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 32)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_u32x16_i32x8(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_u32x16_u32x8(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 64)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_u32x16_i64x4(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_u32x16_u64x4(from_);
					}
				}
				else
				{
					static_assert
						(
							EmuCore::TMP::get_false<OutPerElementWidthIfInt_>(),
							"Attempted to convert a EmuSIMD::u32x16 register to i256_generic via EmuSIMD helpers, but the provided width per element is invalid. Only 8, 16, 32, and 64 are valid values."
							);
				}
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i512_generic>)
			{
				if constexpr (OutPerElementWidthIfInt_ == 8)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_u32x16_i8x64(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_u32x16_u8x64(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 16)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_u32x16_i16x32(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_u32x16_u16x32(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 32)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_u32x16_i32x16(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_u32x16_u32x16(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 64)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_u32x16_i64x8(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_u32x16_u64x8(from_);
					}
				}
				else
				{
					static_assert
						(
							EmuCore::TMP::get_false<OutPerElementWidthIfInt_>(),
							"Attempted to convert a EmuSIMD::u32x16 register to i512_generic via EmuSIMD helpers, but the provided width per element is invalid. Only 8, 16, 32, and 64 are valid values."
							);
				}
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i8x16>)
			{
				return EmuSIMD::Funcs::cvt_u32x16_i8x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u8x16>)
			{
				return EmuSIMD::Funcs::cvt_u32x16_u8x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i8x32>)
			{
				return EmuSIMD::Funcs::cvt_u32x16_i8x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u8x32>)
			{
				return EmuSIMD::Funcs::cvt_u32x16_u8x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i8x64>)
			{
				return EmuSIMD::Funcs::cvt_u32x16_i8x64(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u8x64>)
			{
				return EmuSIMD::Funcs::cvt_u32x16_u8x64(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i16x8>)
			{
				return EmuSIMD::Funcs::cvt_u32x16_i16x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u16x8>)
			{
				return EmuSIMD::Funcs::cvt_u32x16_u16x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i16x16>)
			{
				return EmuSIMD::Funcs::cvt_u32x16_i16x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u16x16>)
			{
				return EmuSIMD::Funcs::cvt_u32x16_u16x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i16x32>)
			{
				return EmuSIMD::Funcs::cvt_u32x16_i16x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u16x32>)
			{
				return EmuSIMD::Funcs::cvt_u32x16_u16x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i32x4>)
			{
				return EmuSIMD::Funcs::cvt_u32x16_i32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u32x4>)
			{
				return EmuSIMD::Funcs::cvt_u32x16_u32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i32x8>)
			{
				return EmuSIMD::Funcs::cvt_u32x16_i32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u32x8>)
			{
				return EmuSIMD::Funcs::cvt_u32x16_u32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i32x16>)
			{
				return EmuSIMD::Funcs::cvt_u32x16_i32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u32x16>)
			{
				return EmuSIMD::Funcs::cvt_u32x16_u32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i64x2>)
			{
				return EmuSIMD::Funcs::cvt_u32x16_i64x2(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u64x2>)
			{
				return EmuSIMD::Funcs::cvt_u32x16_u64x2(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i64x4>)
			{
				return EmuSIMD::Funcs::cvt_u32x16_i64x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u64x4>)
			{
				return EmuSIMD::Funcs::cvt_u32x16_u64x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i64x8>)
			{
				return EmuSIMD::Funcs::cvt_u32x16_i64x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u64x8>)
			{
				return EmuSIMD::Funcs::cvt_u32x16_u64x8(from_);
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<ToRegister_>(), "Attempted to convert a EmuSIMD::u32x16 register via EmuSIMD helpers, but the provided SIMD register to convert to is not supported for this operation.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<ToRegister_>(), "Attempted to convert a EmuSIMD::u32x16 register via EmuSIMD helpers, but the provided register to convert to is not recognisd as a supported SIMD register.");
		}
	}
#pragma endregion

#pragma region CVT_U64
	template<class ToRegister_, std::size_t OutPerElementWidthIfInt_, bool OutSignedIfInt_>
	[[nodiscard]] inline ToRegister_ _cvt_u64x2(EmuSIMD::u64x2_arg from_)
	{
		using to_uq = EmuCore::TMP::remove_ref_cv_t<ToRegister_>;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<to_uq>)
		{
			if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x4>)
			{
				return EmuSIMD::Funcs::cvt_u64x2_f32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x8>)
			{
				return EmuSIMD::Funcs::cvt_u64x2_f32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x16>)
			{
				return EmuSIMD::Funcs::cvt_u64x2_f32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x2>)
			{
				return EmuSIMD::Funcs::cvt_u64x2_f64x2(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x4>)
			{
				return EmuSIMD::Funcs::cvt_u64x2_f64x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x8>)
			{
				return EmuSIMD::Funcs::cvt_u64x2_f64x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i128_generic>)
			{
				if constexpr (OutPerElementWidthIfInt_ == 8)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_u64x2_i8x16(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_u64x2_u8x16(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 16)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_u64x2_i16x8(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_u64x2_u16x8(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 32)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_u64x2_i32x4(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_u64x2_u32x4(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 64)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_u64x2_i64x2(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_u64x2_u64x2(from_);
					}
				}
				else
				{
					static_assert
						(
							EmuCore::TMP::get_false<OutPerElementWidthIfInt_>(),
							"Attempted to convert a EmuSIMD::u64x2 register to i128_generic via EmuSIMD helpers, but the provided width per element is invalid. Only 8, 16, 32, and 64 are valid values."
							);
				}
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i256_generic>)
			{
				if constexpr (OutPerElementWidthIfInt_ == 8)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_u64x2_i8x32(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_u64x2_u8x32(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 16)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_u64x2_i16x16(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_u64x2_u16x16(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 32)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_u64x2_i32x8(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_u64x2_u32x8(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 64)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_u64x2_i64x4(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_u64x2_u64x4(from_);
					}
				}
				else
				{
					static_assert
						(
							EmuCore::TMP::get_false<OutPerElementWidthIfInt_>(),
							"Attempted to convert a EmuSIMD::u64x2 register to i256_generic via EmuSIMD helpers, but the provided width per element is invalid. Only 8, 16, 32, and 64 are valid values."
							);
				}
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i512_generic>)
			{
				if constexpr (OutPerElementWidthIfInt_ == 8)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_u64x2_i8x64(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_u64x2_u8x64(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 16)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_u64x2_i16x32(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_u64x2_u16x32(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 32)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_u64x2_i32x16(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_u64x2_u32x16(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 64)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_u64x2_i64x8(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_u64x2_u64x8(from_);
					}
				}
				else
				{
					static_assert
						(
							EmuCore::TMP::get_false<OutPerElementWidthIfInt_>(),
							"Attempted to convert a EmuSIMD::u64x2 register to i512_generic via EmuSIMD helpers, but the provided width per element is invalid. Only 8, 16, 32, and 64 are valid values."
							);
				}
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i8x16>)
			{
				return EmuSIMD::Funcs::cvt_u64x2_i8x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u8x16>)
			{
				return EmuSIMD::Funcs::cvt_u64x2_u8x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i8x32>)
			{
				return EmuSIMD::Funcs::cvt_u64x2_i8x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u8x32>)
			{
				return EmuSIMD::Funcs::cvt_u64x2_u8x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i8x64>)
			{
				return EmuSIMD::Funcs::cvt_u64x2_i8x64(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u8x64>)
			{
				return EmuSIMD::Funcs::cvt_u64x2_u8x64(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i16x8>)
			{
				return EmuSIMD::Funcs::cvt_u64x2_i16x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u16x8>)
			{
				return EmuSIMD::Funcs::cvt_u64x2_u16x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i16x16>)
			{
				return EmuSIMD::Funcs::cvt_u64x2_i16x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u16x16>)
			{
				return EmuSIMD::Funcs::cvt_u64x2_u16x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i16x32>)
			{
				return EmuSIMD::Funcs::cvt_u64x2_i16x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u16x32>)
			{
				return EmuSIMD::Funcs::cvt_u64x2_u16x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i32x4>)
			{
				return EmuSIMD::Funcs::cvt_u64x2_i32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u32x4>)
			{
				return EmuSIMD::Funcs::cvt_u64x2_u32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i32x8>)
			{
				return EmuSIMD::Funcs::cvt_u64x2_i32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u32x8>)
			{
				return EmuSIMD::Funcs::cvt_u64x2_u32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i32x16>)
			{
				return EmuSIMD::Funcs::cvt_u64x2_i32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u32x16>)
			{
				return EmuSIMD::Funcs::cvt_u64x2_u32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i64x2>)
			{
				return EmuSIMD::Funcs::cvt_u64x2_i64x2(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u64x2>)
			{
				return EmuSIMD::Funcs::cvt_u64x2_u64x2(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i64x4>)
			{
				return EmuSIMD::Funcs::cvt_u64x2_i64x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u64x4>)
			{
				return EmuSIMD::Funcs::cvt_u64x2_u64x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i64x8>)
			{
				return EmuSIMD::Funcs::cvt_u64x2_i64x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u64x8>)
			{
				return EmuSIMD::Funcs::cvt_u64x2_u64x8(from_);
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<ToRegister_>(), "Attempted to convert a EmuSIMD::u64x2 register via EmuSIMD helpers, but the provided SIMD register to convert to is not supported for this operation.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<ToRegister_>(), "Attempted to convert a EmuSIMD::u64x2 register via EmuSIMD helpers, but the provided register to convert to is not recognisd as a supported SIMD register.");
		}
	}

	template<class ToRegister_, std::size_t OutPerElementWidthIfInt_, bool OutSignedIfInt_>
	[[nodiscard]] inline ToRegister_ _cvt_u64x4(EmuSIMD::u64x4_arg from_)
	{
		using to_uq = EmuCore::TMP::remove_ref_cv_t<ToRegister_>;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<to_uq>)
		{
			if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x4>)
			{
				return EmuSIMD::Funcs::cvt_u64x4_f32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x8>)
			{
				return EmuSIMD::Funcs::cvt_u64x4_f32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x16>)
			{
				return EmuSIMD::Funcs::cvt_u64x4_f32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x2>)
			{
				return EmuSIMD::Funcs::cvt_u64x4_f64x2(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x4>)
			{
				return EmuSIMD::Funcs::cvt_u64x4_f64x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x8>)
			{
				return EmuSIMD::Funcs::cvt_u64x4_f64x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i128_generic>)
			{
				if constexpr (OutPerElementWidthIfInt_ == 8)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_u64x4_i8x16(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_u64x4_u8x16(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 16)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_u64x4_i16x8(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_u64x4_u16x8(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 32)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_u64x4_i32x4(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_u64x4_u32x4(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 64)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_u64x4_i64x2(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_u64x4_u64x2(from_);
					}
				}
				else
				{
					static_assert
						(
							EmuCore::TMP::get_false<OutPerElementWidthIfInt_>(),
							"Attempted to convert a EmuSIMD::u64x4 register to i128_generic via EmuSIMD helpers, but the provided width per element is invalid. Only 8, 16, 32, and 64 are valid values."
							);
				}
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i256_generic>)
			{
				if constexpr (OutPerElementWidthIfInt_ == 8)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_u64x4_i8x32(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_u64x4_u8x32(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 16)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_u64x4_i16x16(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_u64x4_u16x16(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 32)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_u64x4_i32x8(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_u64x4_u32x8(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 64)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_u64x4_i64x4(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_u64x4_u64x4(from_);
					}
				}
				else
				{
					static_assert
						(
							EmuCore::TMP::get_false<OutPerElementWidthIfInt_>(),
							"Attempted to convert a EmuSIMD::u64x4 register to i256_generic via EmuSIMD helpers, but the provided width per element is invalid. Only 8, 16, 32, and 64 are valid values."
							);
				}
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i512_generic>)
			{
				if constexpr (OutPerElementWidthIfInt_ == 8)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_u64x4_i8x64(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_u64x4_u8x64(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 16)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_u64x4_i16x32(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_u64x4_u16x32(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 32)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_u64x4_i32x16(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_u64x4_u32x16(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 64)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_u64x4_i64x8(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_u64x4_u64x8(from_);
					}
				}
				else
				{
					static_assert
						(
							EmuCore::TMP::get_false<OutPerElementWidthIfInt_>(),
							"Attempted to convert a EmuSIMD::u64x4 register to i512_generic via EmuSIMD helpers, but the provided width per element is invalid. Only 8, 16, 32, and 64 are valid values."
							);
				}
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i8x16>)
			{
				return EmuSIMD::Funcs::cvt_u64x4_i8x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u8x16>)
			{
				return EmuSIMD::Funcs::cvt_u64x4_u8x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i8x32>)
			{
				return EmuSIMD::Funcs::cvt_u64x4_i8x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u8x32>)
			{
				return EmuSIMD::Funcs::cvt_u64x4_u8x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i8x64>)
			{
				return EmuSIMD::Funcs::cvt_u64x4_i8x64(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u8x64>)
			{
				return EmuSIMD::Funcs::cvt_u64x4_u8x64(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i16x8>)
			{
				return EmuSIMD::Funcs::cvt_u64x4_i16x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u16x8>)
			{
				return EmuSIMD::Funcs::cvt_u64x4_u16x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i16x16>)
			{
				return EmuSIMD::Funcs::cvt_u64x4_i16x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u16x16>)
			{
				return EmuSIMD::Funcs::cvt_u64x4_u16x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i16x32>)
			{
				return EmuSIMD::Funcs::cvt_u64x4_i16x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u16x32>)
			{
				return EmuSIMD::Funcs::cvt_u64x4_u16x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i32x4>)
			{
				return EmuSIMD::Funcs::cvt_u64x4_i32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u32x4>)
			{
				return EmuSIMD::Funcs::cvt_u64x4_u32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i32x8>)
			{
				return EmuSIMD::Funcs::cvt_u64x4_i32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u32x8>)
			{
				return EmuSIMD::Funcs::cvt_u64x4_u32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i32x16>)
			{
				return EmuSIMD::Funcs::cvt_u64x4_i32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u32x16>)
			{
				return EmuSIMD::Funcs::cvt_u64x4_u32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i64x2>)
			{
				return EmuSIMD::Funcs::cvt_u64x4_i64x2(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u64x2>)
			{
				return EmuSIMD::Funcs::cvt_u64x4_u64x2(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i64x4>)
			{
				return EmuSIMD::Funcs::cvt_u64x4_i64x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u64x4>)
			{
				return EmuSIMD::Funcs::cvt_u64x4_u64x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i64x8>)
			{
				return EmuSIMD::Funcs::cvt_u64x4_i64x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u64x8>)
			{
				return EmuSIMD::Funcs::cvt_u64x4_u64x8(from_);
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<ToRegister_>(), "Attempted to convert a EmuSIMD::u64x4 register via EmuSIMD helpers, but the provided SIMD register to convert to is not supported for this operation.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<ToRegister_>(), "Attempted to convert a EmuSIMD::u64x4 register via EmuSIMD helpers, but the provided register to convert to is not recognisd as a supported SIMD register.");
		}
	}

	template<class ToRegister_, std::size_t OutPerElementWidthIfInt_, bool OutSignedIfInt_>
	[[nodiscard]] inline ToRegister_ _cvt_u64x8(EmuSIMD::u64x8_arg from_)
	{
		using to_uq = EmuCore::TMP::remove_ref_cv_t<ToRegister_>;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<to_uq>)
		{
			if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x4>)
			{
				return EmuSIMD::Funcs::cvt_u64x8_f32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x8>)
			{
				return EmuSIMD::Funcs::cvt_u64x8_f32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x16>)
			{
				return EmuSIMD::Funcs::cvt_u64x8_f32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x2>)
			{
				return EmuSIMD::Funcs::cvt_u64x8_f64x2(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x4>)
			{
				return EmuSIMD::Funcs::cvt_u64x8_f64x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x8>)
			{
				return EmuSIMD::Funcs::cvt_u64x8_f64x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i128_generic>)
			{
				if constexpr (OutPerElementWidthIfInt_ == 8)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_u64x8_i8x16(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_u64x8_u8x16(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 16)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_u64x8_i16x8(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_u64x8_u16x8(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 32)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_u64x8_i32x4(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_u64x8_u32x4(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 64)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_u64x8_i64x2(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_u64x8_u64x2(from_);
					}
				}
				else
				{
					static_assert
						(
							EmuCore::TMP::get_false<OutPerElementWidthIfInt_>(),
							"Attempted to convert a EmuSIMD::u64x8 register to i128_generic via EmuSIMD helpers, but the provided width per element is invalid. Only 8, 16, 32, and 64 are valid values."
							);
				}
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i256_generic>)
			{
				if constexpr (OutPerElementWidthIfInt_ == 8)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_u64x8_i8x32(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_u64x8_u8x32(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 16)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_u64x8_i16x16(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_u64x8_u16x16(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 32)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_u64x8_i32x8(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_u64x8_u32x8(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 64)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_u64x8_i64x4(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_u64x8_u64x4(from_);
					}
				}
				else
				{
					static_assert
						(
							EmuCore::TMP::get_false<OutPerElementWidthIfInt_>(),
							"Attempted to convert a EmuSIMD::u64x8 register to i256_generic via EmuSIMD helpers, but the provided width per element is invalid. Only 8, 16, 32, and 64 are valid values."
							);
				}
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i512_generic>)
			{
				if constexpr (OutPerElementWidthIfInt_ == 8)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_u64x8_i8x64(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_u64x8_u8x64(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 16)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_u64x8_i16x32(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_u64x8_u16x32(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 32)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_u64x8_i32x16(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_u64x8_u32x16(from_);
					}
				}
				else if constexpr (OutPerElementWidthIfInt_ == 64)
				{
					if constexpr (OutSignedIfInt_)
					{
						return EmuSIMD::Funcs::cvt_u64x8_i64x8(from_);
					}
					else
					{
						return EmuSIMD::Funcs::cvt_u64x8_u64x8(from_);
					}
				}
				else
				{
					static_assert
						(
							EmuCore::TMP::get_false<OutPerElementWidthIfInt_>(),
							"Attempted to convert a EmuSIMD::u64x8 register to i512_generic via EmuSIMD helpers, but the provided width per element is invalid. Only 8, 16, 32, and 64 are valid values."
							);
				}
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i8x16>)
			{
				return EmuSIMD::Funcs::cvt_u64x8_i8x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u8x16>)
			{
				return EmuSIMD::Funcs::cvt_u64x8_u8x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i8x32>)
			{
				return EmuSIMD::Funcs::cvt_u64x8_i8x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u8x32>)
			{
				return EmuSIMD::Funcs::cvt_u64x8_u8x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i8x64>)
			{
				return EmuSIMD::Funcs::cvt_u64x8_i8x64(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u8x64>)
			{
				return EmuSIMD::Funcs::cvt_u64x8_u8x64(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i16x8>)
			{
				return EmuSIMD::Funcs::cvt_u64x8_i16x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u16x8>)
			{
				return EmuSIMD::Funcs::cvt_u64x8_u16x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i16x16>)
			{
				return EmuSIMD::Funcs::cvt_u64x8_i16x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u16x16>)
			{
				return EmuSIMD::Funcs::cvt_u64x8_u16x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i16x32>)
			{
				return EmuSIMD::Funcs::cvt_u64x8_i16x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u16x32>)
			{
				return EmuSIMD::Funcs::cvt_u64x8_u16x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i32x4>)
			{
				return EmuSIMD::Funcs::cvt_u64x8_i32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u32x4>)
			{
				return EmuSIMD::Funcs::cvt_u64x8_u32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i32x8>)
			{
				return EmuSIMD::Funcs::cvt_u64x8_i32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u32x8>)
			{
				return EmuSIMD::Funcs::cvt_u64x8_u32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i32x16>)
			{
				return EmuSIMD::Funcs::cvt_u64x8_i32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u32x16>)
			{
				return EmuSIMD::Funcs::cvt_u64x8_u32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i64x2>)
			{
				return EmuSIMD::Funcs::cvt_u64x8_i64x2(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u64x2>)
			{
				return EmuSIMD::Funcs::cvt_u64x8_u64x2(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i64x4>)
			{
				return EmuSIMD::Funcs::cvt_u64x8_i64x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u64x4>)
			{
				return EmuSIMD::Funcs::cvt_u64x8_u64x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i64x8>)
			{
				return EmuSIMD::Funcs::cvt_u64x8_i64x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u64x8>)
			{
				return EmuSIMD::Funcs::cvt_u64x8_u64x8(from_);
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<ToRegister_>(), "Attempted to convert a EmuSIMD::u64x8 register via EmuSIMD helpers, but the provided SIMD register to convert to is not supported for this operation.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<ToRegister_>(), "Attempted to convert a EmuSIMD::u64x8 register via EmuSIMD helpers, but the provided register to convert to is not recognisd as a supported SIMD register.");
		}
	}
#pragma endregion
}

#endif

