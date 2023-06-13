#ifndef EMU_SIMD_HELPERS_TEMPLATE_TRIG_H_INC_
#define EMU_SIMD_HELPERS_TEMPLATE_TRIG_H_INC_ 1

#include "_underlying_template_helpers/_all_underlying_templates.h"
#include "../../../../EmuCore/TMPHelpers/Values.h"

namespace EmuSIMD
{
#pragma region COS_SIN_TAN
	template<std::size_t PerElementWidthIfInt_ = 32, bool SignedIfInt_ = true, class Register_>
	[[nodiscard]] constexpr inline Register_ cos(Register_ in_)
	{
		using in_uq = EmuCore::TMP::remove_ref_cv_t<Register_>;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<in_uq>)
		{
			if constexpr (std::is_same_v<in_uq, EmuSIMD::f32x4>)
			{
				return EmuSIMD::Funcs::cos_f32x4(in_);
			}
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::f32x8>)
			{
				return EmuSIMD::Funcs::cos_f32x8(in_);
			}
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::f32x16>)
			{
				return EmuSIMD::Funcs::cos_f32x16(in_);
			}
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::f64x2>)
			{
				return EmuSIMD::Funcs::cos_f64x2(in_);
			}
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::f64x4>)
			{
				return EmuSIMD::Funcs::cos_f64x4(in_);
			}
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::f64x8>)
			{
				return EmuSIMD::Funcs::cos_f64x8(in_);
			}
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::i128_generic>)
			{
				if constexpr (PerElementWidthIfInt_ == 8)
				{
					if constexpr (SignedIfInt_)
					{
						return EmuSIMD::Funcs::cos_i8x16(in_);
					}
					else
					{
						return EmuSIMD::Funcs::cos_u8x16(in_);
					}
				}
				else if constexpr (PerElementWidthIfInt_ == 16)
				{
					if constexpr (SignedIfInt_)
					{
						return EmuSIMD::Funcs::cos_i16x8(in_);
					}
					else
					{
						return EmuSIMD::Funcs::cos_u16x8(in_);
					}
				}
				else if constexpr (PerElementWidthIfInt_ == 32)
				{
					if constexpr (SignedIfInt_)
					{
						return EmuSIMD::Funcs::cos_i32x4(in_);
					}
					else
					{
						return EmuSIMD::Funcs::cos_u32x4(in_);
					}
				}
				else if constexpr (PerElementWidthIfInt_ == 64)
				{
					if constexpr (SignedIfInt_)
					{
						return EmuSIMD::Funcs::cos_i64x2(in_);
					}
					else
					{
						return EmuSIMD::Funcs::cos_u64x2(in_);
					}
				}
				else
				{
					static_assert
					(
						EmuCore::TMP::get_false<PerElementWidthIfInt_>(),
						"Attempted to calculate the cosine of elements in a generic 128-bit integral SIMD register, but the provided width per element is invalid. Valid values are 8, 16, 32, and 64."
					);
				}
			}
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::i256_generic>)
			{
				if constexpr (PerElementWidthIfInt_ == 8)
				{
					if constexpr (SignedIfInt_)
					{
						return EmuSIMD::Funcs::cos_i8x32(in_);
					}
					else
					{
						return EmuSIMD::Funcs::cos_u8x32(in_);
					}
				}
				else if constexpr (PerElementWidthIfInt_ == 16)
				{
					if constexpr (SignedIfInt_)
					{
						return EmuSIMD::Funcs::cos_i16x16(in_);
					}
					else
					{
						return EmuSIMD::Funcs::cos_u16x16(in_);
					}
				}
				else if constexpr (PerElementWidthIfInt_ == 32)
				{
					if constexpr (SignedIfInt_)
					{
						return EmuSIMD::Funcs::cos_i32x8(in_);
					}
					else
					{
						return EmuSIMD::Funcs::cos_u32x8(in_);
					}
				}
				else if constexpr (PerElementWidthIfInt_ == 64)
				{
					if constexpr (SignedIfInt_)
					{
						return EmuSIMD::Funcs::cos_i64x4(in_);
					}
					else
					{
						return EmuSIMD::Funcs::cos_u64x4(in_);
					}
				}
				else
				{
					static_assert
					(
						EmuCore::TMP::get_false<PerElementWidthIfInt_>(),
						"Attempted to calculate the cosine of elements in a generic 256-bit integral SIMD register, but the provided width per element is invalid. Valid values are 8, 16, 32, and 64."
					);
				}
			}
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::i512_generic>)
			{
				if constexpr (PerElementWidthIfInt_ == 8)
				{
					if constexpr (SignedIfInt_)
					{
						return EmuSIMD::Funcs::cos_i8x64(in_);
					}
					else
					{
						return EmuSIMD::Funcs::cos_u8x64(in_);
					}
				}
				else if constexpr (PerElementWidthIfInt_ == 16)
				{
					if constexpr (SignedIfInt_)
					{
						return EmuSIMD::Funcs::cos_i16x32(in_);
					}
					else
					{
						return EmuSIMD::Funcs::cos_u16x32(in_);
					}
				}
				else if constexpr (PerElementWidthIfInt_ == 32)
				{
					if constexpr (SignedIfInt_)
					{
						return EmuSIMD::Funcs::cos_i32x16(in_);
					}
					else
					{
						return EmuSIMD::Funcs::cos_u32x16(in_);
					}
				}
				else if constexpr (PerElementWidthIfInt_ == 64)
				{
					if constexpr (SignedIfInt_)
					{
						return EmuSIMD::Funcs::cos_i64x8(in_);
					}
					else
					{
						return EmuSIMD::Funcs::cos_u64x8(in_);
					}
				}
				else
				{
					static_assert
					(
						EmuCore::TMP::get_false<PerElementWidthIfInt_>(),
						"Attempted to calculate the cosine of elements in a generic 512-bit integral SIMD register, but the provided width per element is invalid. Valid values are 8, 16, 32, and 64."
					);
				}
			}
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::i8x16>)
			{
				return EmuSIMD::Funcs::cos_i8x16(in_);
			}
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::i8x32>)
			{
				return EmuSIMD::Funcs::cos_i8x32(in_);
			}
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::i8x64>)
			{
				return EmuSIMD::Funcs::cos_i8x64(in_);
			}
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::u8x16>)
			{
				return EmuSIMD::Funcs::cos_u8x16(in_);
			}
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::u8x32>)
			{
				return EmuSIMD::Funcs::cos_u8x32(in_);
			}
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::u8x64>)
			{
				return EmuSIMD::Funcs::cos_u8x64(in_);
			}			
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::i16x8>)
			{
				return EmuSIMD::Funcs::cos_i16x8(in_);
			}
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::i16x16>)
			{
				return EmuSIMD::Funcs::cos_i16x16(in_);
			}
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::i16x32>)
			{
				return EmuSIMD::Funcs::cos_i16x32(in_);
			}
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::u16x8>)
			{
				return EmuSIMD::Funcs::cos_u16x8(in_);
			}
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::u16x16>)
			{
				return EmuSIMD::Funcs::cos_u16x16(in_);
			}
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::u16x32>)
			{
				return EmuSIMD::Funcs::cos_u16x32(in_);
			}			
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::i32x4>)
			{
				return EmuSIMD::Funcs::cos_i32x4(in_);
			}
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::i32x8>)
			{
				return EmuSIMD::Funcs::cos_i32x8(in_);
			}
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::i32x16>)
			{
				return EmuSIMD::Funcs::cos_i32x16(in_);
			}
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::u32x4>)
			{
				return EmuSIMD::Funcs::cos_u32x4(in_);
			}
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::u32x8>)
			{
				return EmuSIMD::Funcs::cos_u32x8(in_);
			}
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::u32x16>)
			{
				return EmuSIMD::Funcs::cos_u32x16(in_);
			}
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::i64x2>)
			{
				return EmuSIMD::Funcs::cos_i64x2(in_);
			}
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::i64x4>)
			{
				return EmuSIMD::Funcs::cos_i64x4(in_);
			}
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::i64x8>)
			{
				return EmuSIMD::Funcs::cos_i64x8(in_);
			}
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::u64x2>)
			{
				return EmuSIMD::Funcs::cos_u64x2(in_);
			}
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::u64x4>)
			{
				return EmuSIMD::Funcs::cos_u64x4(in_);
			}
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::u64x8>)
			{
				return EmuSIMD::Funcs::cos_u64x8(in_);
			}
			else
			{
				static_assert
				(
					EmuCore::TMP::get_false<in_uq>(),
					"Attempted to calculate the cosine of a SIMD register via EmuSIMD helpers, but the provided in_ register is not a support register type for this operation."
				);
			}
		}
		else
		{
			static_assert
			(
				EmuCore::TMP::get_false<Register_>(),
				"Attempted to calculate the cosine of a SIMD register via EmuSIMD helpers, but the provided in_ register is not a recognised SIMD register type."
			);
		}
	}

	template<std::size_t PerElementWidthIfInt_ = 32, bool SignedIfInt_ = true, class Register_>
	[[nodiscard]] constexpr inline Register_ sin(Register_ in_)
	{
		using in_uq = EmuCore::TMP::remove_ref_cv_t<Register_>;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<in_uq>)
		{
			if constexpr (std::is_same_v<in_uq, EmuSIMD::f32x4>)
			{
				return EmuSIMD::Funcs::sin_f32x4(in_);
			}
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::f32x8>)
			{
				return EmuSIMD::Funcs::sin_f32x8(in_);
			}
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::f32x16>)
			{
				return EmuSIMD::Funcs::sin_f32x16(in_);
			}
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::f64x2>)
			{
				return EmuSIMD::Funcs::sin_f64x2(in_);
			}
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::f64x4>)
			{
				return EmuSIMD::Funcs::sin_f64x4(in_);
			}
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::f64x8>)
			{
				return EmuSIMD::Funcs::sin_f64x8(in_);
			}
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::i128_generic>)
			{
				if constexpr (PerElementWidthIfInt_ == 8)
				{
					if constexpr (SignedIfInt_)
					{
						return EmuSIMD::Funcs::sin_i8x16(in_);
					}
					else
					{
						return EmuSIMD::Funcs::sin_u8x16(in_);
					}
				}
				else if constexpr (PerElementWidthIfInt_ == 16)
				{
					if constexpr (SignedIfInt_)
					{
						return EmuSIMD::Funcs::sin_i16x8(in_);
					}
					else
					{
						return EmuSIMD::Funcs::sin_u16x8(in_);
					}
				}
				else if constexpr (PerElementWidthIfInt_ == 32)
				{
					if constexpr (SignedIfInt_)
					{
						return EmuSIMD::Funcs::sin_i32x4(in_);
					}
					else
					{
						return EmuSIMD::Funcs::sin_u32x4(in_);
					}
				}
				else if constexpr (PerElementWidthIfInt_ == 64)
				{
					if constexpr (SignedIfInt_)
					{
						return EmuSIMD::Funcs::sin_i64x2(in_);
					}
					else
					{
						return EmuSIMD::Funcs::sin_u64x2(in_);
					}
				}
				else
				{
					static_assert
					(
						EmuCore::TMP::get_false<PerElementWidthIfInt_>(),
						"Attempted to calculate the sine of elements in a generic 128-bit integral SIMD register, but the provided width per element is invalid. Valid values are 8, 16, 32, and 64."
					);
				}
			}
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::i256_generic>)
			{
				if constexpr (PerElementWidthIfInt_ == 8)
				{
					if constexpr (SignedIfInt_)
					{
						return EmuSIMD::Funcs::sin_i8x32(in_);
					}
					else
					{
						return EmuSIMD::Funcs::sin_u8x32(in_);
					}
				}
				else if constexpr (PerElementWidthIfInt_ == 16)
				{
					if constexpr (SignedIfInt_)
					{
						return EmuSIMD::Funcs::sin_i16x16(in_);
					}
					else
					{
						return EmuSIMD::Funcs::sin_u16x16(in_);
					}
				}
				else if constexpr (PerElementWidthIfInt_ == 32)
				{
					if constexpr (SignedIfInt_)
					{
						return EmuSIMD::Funcs::sin_i32x8(in_);
					}
					else
					{
						return EmuSIMD::Funcs::sin_u32x8(in_);
					}
				}
				else if constexpr (PerElementWidthIfInt_ == 64)
				{
					if constexpr (SignedIfInt_)
					{
						return EmuSIMD::Funcs::sin_i64x4(in_);
					}
					else
					{
						return EmuSIMD::Funcs::sin_u64x4(in_);
					}
				}
				else
				{
					static_assert
					(
						EmuCore::TMP::get_false<PerElementWidthIfInt_>(),
						"Attempted to calculate the sine of elements in a generic 256-bit integral SIMD register, but the provided width per element is invalid. Valid values are 8, 16, 32, and 64."
					);
				}
			}
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::i512_generic>)
			{
				if constexpr (PerElementWidthIfInt_ == 8)
				{
					if constexpr (SignedIfInt_)
					{
						return EmuSIMD::Funcs::sin_i8x64(in_);
					}
					else
					{
						return EmuSIMD::Funcs::sin_u8x64(in_);
					}
				}
				else if constexpr (PerElementWidthIfInt_ == 16)
				{
					if constexpr (SignedIfInt_)
					{
						return EmuSIMD::Funcs::sin_i16x32(in_);
					}
					else
					{
						return EmuSIMD::Funcs::sin_u16x32(in_);
					}
				}
				else if constexpr (PerElementWidthIfInt_ == 32)
				{
					if constexpr (SignedIfInt_)
					{
						return EmuSIMD::Funcs::sin_i32x16(in_);
					}
					else
					{
						return EmuSIMD::Funcs::sin_u32x16(in_);
					}
				}
				else if constexpr (PerElementWidthIfInt_ == 64)
				{
					if constexpr (SignedIfInt_)
					{
						return EmuSIMD::Funcs::sin_i64x8(in_);
					}
					else
					{
						return EmuSIMD::Funcs::sin_u64x8(in_);
					}
				}
				else
				{
					static_assert
					(
						EmuCore::TMP::get_false<PerElementWidthIfInt_>(),
						"Attempted to calculate the sine of elements in a generic 512-bit integral SIMD register, but the provided width per element is invalid. Valid values are 8, 16, 32, and 64."
					);
				}
			}
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::i8x16>)
			{
				return EmuSIMD::Funcs::sin_i8x16(in_);
			}
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::i8x32>)
			{
				return EmuSIMD::Funcs::sin_i8x32(in_);
			}
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::i8x64>)
			{
				return EmuSIMD::Funcs::sin_i8x64(in_);
			}
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::u8x16>)
			{
				return EmuSIMD::Funcs::sin_u8x16(in_);
			}
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::u8x32>)
			{
				return EmuSIMD::Funcs::sin_u8x32(in_);
			}
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::u8x64>)
			{
				return EmuSIMD::Funcs::sin_u8x64(in_);
			}			
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::i16x8>)
			{
				return EmuSIMD::Funcs::sin_i16x8(in_);
			}
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::i16x16>)
			{
				return EmuSIMD::Funcs::sin_i16x16(in_);
			}
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::i16x32>)
			{
				return EmuSIMD::Funcs::sin_i16x32(in_);
			}
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::u16x8>)
			{
				return EmuSIMD::Funcs::sin_u16x8(in_);
			}
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::u16x16>)
			{
				return EmuSIMD::Funcs::sin_u16x16(in_);
			}
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::u16x32>)
			{
				return EmuSIMD::Funcs::sin_u16x32(in_);
			}			
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::i32x4>)
			{
				return EmuSIMD::Funcs::sin_i32x4(in_);
			}
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::i32x8>)
			{
				return EmuSIMD::Funcs::sin_i32x8(in_);
			}
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::i32x16>)
			{
				return EmuSIMD::Funcs::sin_i32x16(in_);
			}
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::u32x4>)
			{
				return EmuSIMD::Funcs::sin_u32x4(in_);
			}
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::u32x8>)
			{
				return EmuSIMD::Funcs::sin_u32x8(in_);
			}
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::u32x16>)
			{
				return EmuSIMD::Funcs::sin_u32x16(in_);
			}
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::i64x2>)
			{
				return EmuSIMD::Funcs::sin_i64x2(in_);
			}
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::i64x4>)
			{
				return EmuSIMD::Funcs::sin_i64x4(in_);
			}
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::i64x8>)
			{
				return EmuSIMD::Funcs::sin_i64x8(in_);
			}
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::u64x2>)
			{
				return EmuSIMD::Funcs::sin_u64x2(in_);
			}
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::u64x4>)
			{
				return EmuSIMD::Funcs::sin_u64x4(in_);
			}
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::u64x8>)
			{
				return EmuSIMD::Funcs::sin_u64x8(in_);
			}
			else
			{
				static_assert
				(
					EmuCore::TMP::get_false<in_uq>(),
					"Attempted to calculate the sine of a SIMD register via EmuSIMD helpers, but the provided in_ register is not a support register type for this operation."
				);
			}
		}
		else
		{
			static_assert
			(
				EmuCore::TMP::get_false<Register_>(),
				"Attempted to calculate the sine of a SIMD register via EmuSIMD helpers, but the provided in_ register is not a recognised SIMD register type."
			);
		}
	}

	template<std::size_t PerElementWidthIfInt_ = 32, bool SignedIfInt_ = true, class Register_>
	[[nodiscard]] constexpr inline Register_ tan(Register_ in_)
	{
		using in_uq = EmuCore::TMP::remove_ref_cv_t<Register_>;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<in_uq>)
		{
			if constexpr (std::is_same_v<in_uq, EmuSIMD::f32x4>)
			{
				return EmuSIMD::Funcs::tan_f32x4(in_);
			}
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::f32x8>)
			{
				return EmuSIMD::Funcs::tan_f32x8(in_);
			}
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::f32x16>)
			{
				return EmuSIMD::Funcs::tan_f32x16(in_);
			}
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::f64x2>)
			{
				return EmuSIMD::Funcs::tan_f64x2(in_);
			}
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::f64x4>)
			{
				return EmuSIMD::Funcs::tan_f64x4(in_);
			}
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::f64x8>)
			{
				return EmuSIMD::Funcs::tan_f64x8(in_);
			}
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::i128_generic>)
			{
				if constexpr (PerElementWidthIfInt_ == 8)
				{
					if constexpr (SignedIfInt_)
					{
						return EmuSIMD::Funcs::tan_i8x16(in_);
					}
					else
					{
						return EmuSIMD::Funcs::tan_u8x16(in_);
					}
				}
				else if constexpr (PerElementWidthIfInt_ == 16)
				{
					if constexpr (SignedIfInt_)
					{
						return EmuSIMD::Funcs::tan_i16x8(in_);
					}
					else
					{
						return EmuSIMD::Funcs::tan_u16x8(in_);
					}
				}
				else if constexpr (PerElementWidthIfInt_ == 32)
				{
					if constexpr (SignedIfInt_)
					{
						return EmuSIMD::Funcs::tan_i32x4(in_);
					}
					else
					{
						return EmuSIMD::Funcs::tan_u32x4(in_);
					}
				}
				else if constexpr (PerElementWidthIfInt_ == 64)
				{
					if constexpr (SignedIfInt_)
					{
						return EmuSIMD::Funcs::tan_i64x2(in_);
					}
					else
					{
						return EmuSIMD::Funcs::tan_u64x2(in_);
					}
				}
				else
				{
					static_assert
					(
						EmuCore::TMP::get_false<PerElementWidthIfInt_>(),
						"Attempted to calculate the tangent of elements in a generic 128-bit integral SIMD register, but the provided width per element is invalid. Valid values are 8, 16, 32, and 64."
					);
				}
			}
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::i256_generic>)
			{
				if constexpr (PerElementWidthIfInt_ == 8)
				{
					if constexpr (SignedIfInt_)
					{
						return EmuSIMD::Funcs::tan_i8x32(in_);
					}
					else
					{
						return EmuSIMD::Funcs::tan_u8x32(in_);
					}
				}
				else if constexpr (PerElementWidthIfInt_ == 16)
				{
					if constexpr (SignedIfInt_)
					{
						return EmuSIMD::Funcs::tan_i16x16(in_);
					}
					else
					{
						return EmuSIMD::Funcs::tan_u16x16(in_);
					}
				}
				else if constexpr (PerElementWidthIfInt_ == 32)
				{
					if constexpr (SignedIfInt_)
					{
						return EmuSIMD::Funcs::tan_i32x8(in_);
					}
					else
					{
						return EmuSIMD::Funcs::tan_u32x8(in_);
					}
				}
				else if constexpr (PerElementWidthIfInt_ == 64)
				{
					if constexpr (SignedIfInt_)
					{
						return EmuSIMD::Funcs::tan_i64x4(in_);
					}
					else
					{
						return EmuSIMD::Funcs::tan_u64x4(in_);
					}
				}
				else
				{
					static_assert
					(
						EmuCore::TMP::get_false<PerElementWidthIfInt_>(),
						"Attempted to calculate the tangent of elements in a generic 256-bit integral SIMD register, but the provided width per element is invalid. Valid values are 8, 16, 32, and 64."
					);
				}
			}
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::i512_generic>)
			{
				if constexpr (PerElementWidthIfInt_ == 8)
				{
					if constexpr (SignedIfInt_)
					{
						return EmuSIMD::Funcs::tan_i8x64(in_);
					}
					else
					{
						return EmuSIMD::Funcs::tan_u8x64(in_);
					}
				}
				else if constexpr (PerElementWidthIfInt_ == 16)
				{
					if constexpr (SignedIfInt_)
					{
						return EmuSIMD::Funcs::tan_i16x32(in_);
					}
					else
					{
						return EmuSIMD::Funcs::tan_u16x32(in_);
					}
				}
				else if constexpr (PerElementWidthIfInt_ == 32)
				{
					if constexpr (SignedIfInt_)
					{
						return EmuSIMD::Funcs::tan_i32x16(in_);
					}
					else
					{
						return EmuSIMD::Funcs::tan_u32x16(in_);
					}
				}
				else if constexpr (PerElementWidthIfInt_ == 64)
				{
					if constexpr (SignedIfInt_)
					{
						return EmuSIMD::Funcs::tan_i64x8(in_);
					}
					else
					{
						return EmuSIMD::Funcs::tan_u64x8(in_);
					}
				}
				else
				{
					static_assert
					(
						EmuCore::TMP::get_false<PerElementWidthIfInt_>(),
						"Attempted to calculate the tangent of elements in a generic 512-bit integral SIMD register, but the provided width per element is invalid. Valid values are 8, 16, 32, and 64."
					);
				}
			}
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::i8x16>)
			{
				return EmuSIMD::Funcs::tan_i8x16(in_);
			}
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::i8x32>)
			{
				return EmuSIMD::Funcs::tan_i8x32(in_);
			}
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::i8x64>)
			{
				return EmuSIMD::Funcs::tan_i8x64(in_);
			}
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::u8x16>)
			{
				return EmuSIMD::Funcs::tan_u8x16(in_);
			}
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::u8x32>)
			{
				return EmuSIMD::Funcs::tan_u8x32(in_);
			}
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::u8x64>)
			{
				return EmuSIMD::Funcs::tan_u8x64(in_);
			}			
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::i16x8>)
			{
				return EmuSIMD::Funcs::tan_i16x8(in_);
			}
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::i16x16>)
			{
				return EmuSIMD::Funcs::tan_i16x16(in_);
			}
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::i16x32>)
			{
				return EmuSIMD::Funcs::tan_i16x32(in_);
			}
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::u16x8>)
			{
				return EmuSIMD::Funcs::tan_u16x8(in_);
			}
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::u16x16>)
			{
				return EmuSIMD::Funcs::tan_u16x16(in_);
			}
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::u16x32>)
			{
				return EmuSIMD::Funcs::tan_u16x32(in_);
			}			
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::i32x4>)
			{
				return EmuSIMD::Funcs::tan_i32x4(in_);
			}
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::i32x8>)
			{
				return EmuSIMD::Funcs::tan_i32x8(in_);
			}
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::i32x16>)
			{
				return EmuSIMD::Funcs::tan_i32x16(in_);
			}
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::u32x4>)
			{
				return EmuSIMD::Funcs::tan_u32x4(in_);
			}
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::u32x8>)
			{
				return EmuSIMD::Funcs::tan_u32x8(in_);
			}
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::u32x16>)
			{
				return EmuSIMD::Funcs::tan_u32x16(in_);
			}
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::i64x2>)
			{
				return EmuSIMD::Funcs::tan_i64x2(in_);
			}
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::i64x4>)
			{
				return EmuSIMD::Funcs::tan_i64x4(in_);
			}
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::i64x8>)
			{
				return EmuSIMD::Funcs::tan_i64x8(in_);
			}
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::u64x2>)
			{
				return EmuSIMD::Funcs::tan_u64x2(in_);
			}
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::u64x4>)
			{
				return EmuSIMD::Funcs::tan_u64x4(in_);
			}
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::u64x8>)
			{
				return EmuSIMD::Funcs::tan_u64x8(in_);
			}
			else
			{
				static_assert
				(
					EmuCore::TMP::get_false<in_uq>(),
					"Attempted to calculate the tangent of a SIMD register via EmuSIMD helpers, but the provided in_ register is not a support register type for this operation."
				);
			}
		}
		else
		{
			static_assert
			(
				EmuCore::TMP::get_false<Register_>(),
				"Attempted to calculate the tangent of a SIMD register via EmuSIMD helpers, but the provided in_ register is not a recognised SIMD register type."
			);
		}
	}
#pragma endregion

#pragma region ACOS_ASIN_ATAN
	template<std::size_t PerElementWidthIfInt_ = 32, bool SignedIfInt_ = true, class Register_>
	[[nodiscard]] constexpr inline Register_ acos(Register_ in_)
	{
		using in_uq = EmuCore::TMP::remove_ref_cv_t<Register_>;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<in_uq>)
		{
			if constexpr (std::is_same_v<in_uq, EmuSIMD::f32x4>)
			{
				return EmuSIMD::Funcs::acos_f32x4(in_);
			}
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::f32x8>)
			{
				return EmuSIMD::Funcs::acos_f32x8(in_);
			}
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::f32x16>)
			{
				return EmuSIMD::Funcs::acos_f32x16(in_);
			}
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::f64x2>)
			{
				return EmuSIMD::Funcs::acos_f64x2(in_);
			}
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::f64x4>)
			{
				return EmuSIMD::Funcs::acos_f64x4(in_);
			}
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::f64x8>)
			{
				return EmuSIMD::Funcs::acos_f64x8(in_);
			}
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::i128_generic>)
			{
				if constexpr (PerElementWidthIfInt_ == 8)
				{
					if constexpr (SignedIfInt_)
					{
						return EmuSIMD::Funcs::acos_i8x16(in_);
					}
					else
					{
						return EmuSIMD::Funcs::acos_u8x16(in_);
					}
				}
				else if constexpr (PerElementWidthIfInt_ == 16)
				{
					if constexpr (SignedIfInt_)
					{
						return EmuSIMD::Funcs::acos_i16x8(in_);
					}
					else
					{
						return EmuSIMD::Funcs::acos_u16x8(in_);
					}
				}
				else if constexpr (PerElementWidthIfInt_ == 32)
				{
					if constexpr (SignedIfInt_)
					{
						return EmuSIMD::Funcs::acos_i32x4(in_);
					}
					else
					{
						return EmuSIMD::Funcs::acos_u32x4(in_);
					}
				}
				else if constexpr (PerElementWidthIfInt_ == 64)
				{
					if constexpr (SignedIfInt_)
					{
						return EmuSIMD::Funcs::acos_i64x2(in_);
					}
					else
					{
						return EmuSIMD::Funcs::acos_u64x2(in_);
					}
				}
				else
				{
					static_assert
					(
						EmuCore::TMP::get_false<PerElementWidthIfInt_>(),
						"Attempted to calculate the arc cosine of elements in a generic 128-bit integral SIMD register, but the provided width per element is invalid. Valid values are 8, 16, 32, and 64."
					);
				}
			}
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::i256_generic>)
			{
				if constexpr (PerElementWidthIfInt_ == 8)
				{
					if constexpr (SignedIfInt_)
					{
						return EmuSIMD::Funcs::acos_i8x32(in_);
					}
					else
					{
						return EmuSIMD::Funcs::acos_u8x32(in_);
					}
				}
				else if constexpr (PerElementWidthIfInt_ == 16)
				{
					if constexpr (SignedIfInt_)
					{
						return EmuSIMD::Funcs::acos_i16x16(in_);
					}
					else
					{
						return EmuSIMD::Funcs::acos_u16x16(in_);
					}
				}
				else if constexpr (PerElementWidthIfInt_ == 32)
				{
					if constexpr (SignedIfInt_)
					{
						return EmuSIMD::Funcs::acos_i32x8(in_);
					}
					else
					{
						return EmuSIMD::Funcs::acos_u32x8(in_);
					}
				}
				else if constexpr (PerElementWidthIfInt_ == 64)
				{
					if constexpr (SignedIfInt_)
					{
						return EmuSIMD::Funcs::acos_i64x4(in_);
					}
					else
					{
						return EmuSIMD::Funcs::acos_u64x4(in_);
					}
				}
				else
				{
					static_assert
					(
						EmuCore::TMP::get_false<PerElementWidthIfInt_>(),
						"Attempted to calculate the arc cosine of elements in a generic 256-bit integral SIMD register, but the provided width per element is invalid. Valid values are 8, 16, 32, and 64."
					);
				}
			}
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::i512_generic>)
			{
				if constexpr (PerElementWidthIfInt_ == 8)
				{
					if constexpr (SignedIfInt_)
					{
						return EmuSIMD::Funcs::acos_i8x64(in_);
					}
					else
					{
						return EmuSIMD::Funcs::acos_u8x64(in_);
					}
				}
				else if constexpr (PerElementWidthIfInt_ == 16)
				{
					if constexpr (SignedIfInt_)
					{
						return EmuSIMD::Funcs::acos_i16x32(in_);
					}
					else
					{
						return EmuSIMD::Funcs::acos_u16x32(in_);
					}
				}
				else if constexpr (PerElementWidthIfInt_ == 32)
				{
					if constexpr (SignedIfInt_)
					{
						return EmuSIMD::Funcs::acos_i32x16(in_);
					}
					else
					{
						return EmuSIMD::Funcs::acos_u32x16(in_);
					}
				}
				else if constexpr (PerElementWidthIfInt_ == 64)
				{
					if constexpr (SignedIfInt_)
					{
						return EmuSIMD::Funcs::acos_i64x8(in_);
					}
					else
					{
						return EmuSIMD::Funcs::acos_u64x8(in_);
					}
				}
				else
				{
					static_assert
					(
						EmuCore::TMP::get_false<PerElementWidthIfInt_>(),
						"Attempted to calculate the arc cosine of elements in a generic 512-bit integral SIMD register, but the provided width per element is invalid. Valid values are 8, 16, 32, and 64."
					);
				}
			}
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::i8x16>)
			{
				return EmuSIMD::Funcs::acos_i8x16(in_);
			}
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::i8x32>)
			{
				return EmuSIMD::Funcs::acos_i8x32(in_);
			}
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::i8x64>)
			{
				return EmuSIMD::Funcs::acos_i8x64(in_);
			}
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::u8x16>)
			{
				return EmuSIMD::Funcs::acos_u8x16(in_);
			}
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::u8x32>)
			{
				return EmuSIMD::Funcs::acos_u8x32(in_);
			}
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::u8x64>)
			{
				return EmuSIMD::Funcs::acos_u8x64(in_);
			}			
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::i16x8>)
			{
				return EmuSIMD::Funcs::acos_i16x8(in_);
			}
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::i16x16>)
			{
				return EmuSIMD::Funcs::acos_i16x16(in_);
			}
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::i16x32>)
			{
				return EmuSIMD::Funcs::acos_i16x32(in_);
			}
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::u16x8>)
			{
				return EmuSIMD::Funcs::acos_u16x8(in_);
			}
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::u16x16>)
			{
				return EmuSIMD::Funcs::acos_u16x16(in_);
			}
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::u16x32>)
			{
				return EmuSIMD::Funcs::acos_u16x32(in_);
			}			
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::i32x4>)
			{
				return EmuSIMD::Funcs::acos_i32x4(in_);
			}
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::i32x8>)
			{
				return EmuSIMD::Funcs::acos_i32x8(in_);
			}
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::i32x16>)
			{
				return EmuSIMD::Funcs::acos_i32x16(in_);
			}
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::u32x4>)
			{
				return EmuSIMD::Funcs::acos_u32x4(in_);
			}
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::u32x8>)
			{
				return EmuSIMD::Funcs::acos_u32x8(in_);
			}
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::u32x16>)
			{
				return EmuSIMD::Funcs::acos_u32x16(in_);
			}
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::i64x2>)
			{
				return EmuSIMD::Funcs::acos_i64x2(in_);
			}
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::i64x4>)
			{
				return EmuSIMD::Funcs::acos_i64x4(in_);
			}
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::i64x8>)
			{
				return EmuSIMD::Funcs::acos_i64x8(in_);
			}
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::u64x2>)
			{
				return EmuSIMD::Funcs::acos_u64x2(in_);
			}
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::u64x4>)
			{
				return EmuSIMD::Funcs::acos_u64x4(in_);
			}
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::u64x8>)
			{
				return EmuSIMD::Funcs::acos_u64x8(in_);
			}
			else
			{
				static_assert
				(
					EmuCore::TMP::get_false<in_uq>(),
					"Attempted to calculate the arc cosine of a SIMD register via EmuSIMD helpers, but the provided in_ register is not a support register type for this operation."
				);
			}
		}
		else
		{
			static_assert
			(
				EmuCore::TMP::get_false<Register_>(),
				"Attempted to calculate the arc cosine of a SIMD register via EmuSIMD helpers, but the provided in_ register is not a recognised SIMD register type."
			);
		}
	}

	template<std::size_t PerElementWidthIfInt_ = 32, bool SignedIfInt_ = true, class Register_>
	[[nodiscard]] constexpr inline Register_ asin(Register_ in_)
	{
		using in_uq = EmuCore::TMP::remove_ref_cv_t<Register_>;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<in_uq>)
		{
			if constexpr (std::is_same_v<in_uq, EmuSIMD::f32x4>)
			{
				return EmuSIMD::Funcs::asin_f32x4(in_);
			}
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::f32x8>)
			{
				return EmuSIMD::Funcs::asin_f32x8(in_);
			}
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::f32x16>)
			{
				return EmuSIMD::Funcs::asin_f32x16(in_);
			}
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::f64x2>)
			{
				return EmuSIMD::Funcs::asin_f64x2(in_);
			}
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::f64x4>)
			{
				return EmuSIMD::Funcs::asin_f64x4(in_);
			}
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::f64x8>)
			{
				return EmuSIMD::Funcs::asin_f64x8(in_);
			}
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::i128_generic>)
			{
				if constexpr (PerElementWidthIfInt_ == 8)
				{
					if constexpr (SignedIfInt_)
					{
						return EmuSIMD::Funcs::asin_i8x16(in_);
					}
					else
					{
						return EmuSIMD::Funcs::asin_u8x16(in_);
					}
				}
				else if constexpr (PerElementWidthIfInt_ == 16)
				{
					if constexpr (SignedIfInt_)
					{
						return EmuSIMD::Funcs::asin_i16x8(in_);
					}
					else
					{
						return EmuSIMD::Funcs::asin_u16x8(in_);
					}
				}
				else if constexpr (PerElementWidthIfInt_ == 32)
				{
					if constexpr (SignedIfInt_)
					{
						return EmuSIMD::Funcs::asin_i32x4(in_);
					}
					else
					{
						return EmuSIMD::Funcs::asin_u32x4(in_);
					}
				}
				else if constexpr (PerElementWidthIfInt_ == 64)
				{
					if constexpr (SignedIfInt_)
					{
						return EmuSIMD::Funcs::asin_i64x2(in_);
					}
					else
					{
						return EmuSIMD::Funcs::asin_u64x2(in_);
					}
				}
				else
				{
					static_assert
					(
						EmuCore::TMP::get_false<PerElementWidthIfInt_>(),
						"Attempted to calculate the arcsine of elements in a generic 128-bit integral SIMD register, but the provided width per element is invalid. Valid values are 8, 16, 32, and 64."
					);
				}
			}
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::i256_generic>)
			{
				if constexpr (PerElementWidthIfInt_ == 8)
				{
					if constexpr (SignedIfInt_)
					{
						return EmuSIMD::Funcs::asin_i8x32(in_);
					}
					else
					{
						return EmuSIMD::Funcs::asin_u8x32(in_);
					}
				}
				else if constexpr (PerElementWidthIfInt_ == 16)
				{
					if constexpr (SignedIfInt_)
					{
						return EmuSIMD::Funcs::asin_i16x16(in_);
					}
					else
					{
						return EmuSIMD::Funcs::asin_u16x16(in_);
					}
				}
				else if constexpr (PerElementWidthIfInt_ == 32)
				{
					if constexpr (SignedIfInt_)
					{
						return EmuSIMD::Funcs::asin_i32x8(in_);
					}
					else
					{
						return EmuSIMD::Funcs::asin_u32x8(in_);
					}
				}
				else if constexpr (PerElementWidthIfInt_ == 64)
				{
					if constexpr (SignedIfInt_)
					{
						return EmuSIMD::Funcs::asin_i64x4(in_);
					}
					else
					{
						return EmuSIMD::Funcs::asin_u64x4(in_);
					}
				}
				else
				{
					static_assert
					(
						EmuCore::TMP::get_false<PerElementWidthIfInt_>(),
						"Attempted to calculate the arcsine of elements in a generic 256-bit integral SIMD register, but the provided width per element is invalid. Valid values are 8, 16, 32, and 64."
					);
				}
			}
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::i512_generic>)
			{
				if constexpr (PerElementWidthIfInt_ == 8)
				{
					if constexpr (SignedIfInt_)
					{
						return EmuSIMD::Funcs::asin_i8x64(in_);
					}
					else
					{
						return EmuSIMD::Funcs::asin_u8x64(in_);
					}
				}
				else if constexpr (PerElementWidthIfInt_ == 16)
				{
					if constexpr (SignedIfInt_)
					{
						return EmuSIMD::Funcs::asin_i16x32(in_);
					}
					else
					{
						return EmuSIMD::Funcs::asin_u16x32(in_);
					}
				}
				else if constexpr (PerElementWidthIfInt_ == 32)
				{
					if constexpr (SignedIfInt_)
					{
						return EmuSIMD::Funcs::asin_i32x16(in_);
					}
					else
					{
						return EmuSIMD::Funcs::asin_u32x16(in_);
					}
				}
				else if constexpr (PerElementWidthIfInt_ == 64)
				{
					if constexpr (SignedIfInt_)
					{
						return EmuSIMD::Funcs::asin_i64x8(in_);
					}
					else
					{
						return EmuSIMD::Funcs::asin_u64x8(in_);
					}
				}
				else
				{
					static_assert
					(
						EmuCore::TMP::get_false<PerElementWidthIfInt_>(),
						"Attempted to calculate the arcsine of elements in a generic 512-bit integral SIMD register, but the provided width per element is invalid. Valid values are 8, 16, 32, and 64."
					);
				}
			}
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::i8x16>)
			{
				return EmuSIMD::Funcs::asin_i8x16(in_);
			}
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::i8x32>)
			{
				return EmuSIMD::Funcs::asin_i8x32(in_);
			}
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::i8x64>)
			{
				return EmuSIMD::Funcs::asin_i8x64(in_);
			}
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::u8x16>)
			{
				return EmuSIMD::Funcs::asin_u8x16(in_);
			}
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::u8x32>)
			{
				return EmuSIMD::Funcs::asin_u8x32(in_);
			}
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::u8x64>)
			{
				return EmuSIMD::Funcs::asin_u8x64(in_);
			}			
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::i16x8>)
			{
				return EmuSIMD::Funcs::asin_i16x8(in_);
			}
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::i16x16>)
			{
				return EmuSIMD::Funcs::asin_i16x16(in_);
			}
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::i16x32>)
			{
				return EmuSIMD::Funcs::asin_i16x32(in_);
			}
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::u16x8>)
			{
				return EmuSIMD::Funcs::asin_u16x8(in_);
			}
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::u16x16>)
			{
				return EmuSIMD::Funcs::asin_u16x16(in_);
			}
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::u16x32>)
			{
				return EmuSIMD::Funcs::asin_u16x32(in_);
			}			
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::i32x4>)
			{
				return EmuSIMD::Funcs::asin_i32x4(in_);
			}
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::i32x8>)
			{
				return EmuSIMD::Funcs::asin_i32x8(in_);
			}
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::i32x16>)
			{
				return EmuSIMD::Funcs::asin_i32x16(in_);
			}
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::u32x4>)
			{
				return EmuSIMD::Funcs::asin_u32x4(in_);
			}
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::u32x8>)
			{
				return EmuSIMD::Funcs::asin_u32x8(in_);
			}
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::u32x16>)
			{
				return EmuSIMD::Funcs::asin_u32x16(in_);
			}
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::i64x2>)
			{
				return EmuSIMD::Funcs::asin_i64x2(in_);
			}
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::i64x4>)
			{
				return EmuSIMD::Funcs::asin_i64x4(in_);
			}
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::i64x8>)
			{
				return EmuSIMD::Funcs::asin_i64x8(in_);
			}
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::u64x2>)
			{
				return EmuSIMD::Funcs::asin_u64x2(in_);
			}
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::u64x4>)
			{
				return EmuSIMD::Funcs::asin_u64x4(in_);
			}
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::u64x8>)
			{
				return EmuSIMD::Funcs::asin_u64x8(in_);
			}
			else
			{
				static_assert
				(
					EmuCore::TMP::get_false<in_uq>(),
					"Attempted to calculate the arcsine of a SIMD register via EmuSIMD helpers, but the provided in_ register is not a support register type for this operation."
				);
			}
		}
		else
		{
			static_assert
			(
				EmuCore::TMP::get_false<Register_>(),
				"Attempted to calculate the arcsine of a SIMD register via EmuSIMD helpers, but the provided in_ register is not a recognised SIMD register type."
			);
		}
	}

	template<std::size_t PerElementWidthIfInt_ = 32, bool SignedIfInt_ = true, class Register_>
	[[nodiscard]] constexpr inline Register_ atan(Register_ in_)
	{
		using in_uq = EmuCore::TMP::remove_ref_cv_t<Register_>;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<in_uq>)
		{
			if constexpr (std::is_same_v<in_uq, EmuSIMD::f32x4>)
			{
				return EmuSIMD::Funcs::atan_f32x4(in_);
			}
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::f32x8>)
			{
				return EmuSIMD::Funcs::atan_f32x8(in_);
			}
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::f32x16>)
			{
				return EmuSIMD::Funcs::atan_f32x16(in_);
			}
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::f64x2>)
			{
				return EmuSIMD::Funcs::atan_f64x2(in_);
			}
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::f64x4>)
			{
				return EmuSIMD::Funcs::atan_f64x4(in_);
			}
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::f64x8>)
			{
				return EmuSIMD::Funcs::atan_f64x8(in_);
			}
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::i128_generic>)
			{
				if constexpr (PerElementWidthIfInt_ == 8)
				{
					if constexpr (SignedIfInt_)
					{
						return EmuSIMD::Funcs::atan_i8x16(in_);
					}
					else
					{
						return EmuSIMD::Funcs::atan_u8x16(in_);
					}
				}
				else if constexpr (PerElementWidthIfInt_ == 16)
				{
					if constexpr (SignedIfInt_)
					{
						return EmuSIMD::Funcs::atan_i16x8(in_);
					}
					else
					{
						return EmuSIMD::Funcs::atan_u16x8(in_);
					}
				}
				else if constexpr (PerElementWidthIfInt_ == 32)
				{
					if constexpr (SignedIfInt_)
					{
						return EmuSIMD::Funcs::atan_i32x4(in_);
					}
					else
					{
						return EmuSIMD::Funcs::atan_u32x4(in_);
					}
				}
				else if constexpr (PerElementWidthIfInt_ == 64)
				{
					if constexpr (SignedIfInt_)
					{
						return EmuSIMD::Funcs::atan_i64x2(in_);
					}
					else
					{
						return EmuSIMD::Funcs::atan_u64x2(in_);
					}
				}
				else
				{
					static_assert
					(
						EmuCore::TMP::get_false<PerElementWidthIfInt_>(),
						"Attempted to calculate the arc tangent of elements in a generic 128-bit integral SIMD register, but the provided width per element is invalid. Valid values are 8, 16, 32, and 64."
					);
				}
			}
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::i256_generic>)
			{
				if constexpr (PerElementWidthIfInt_ == 8)
				{
					if constexpr (SignedIfInt_)
					{
						return EmuSIMD::Funcs::atan_i8x32(in_);
					}
					else
					{
						return EmuSIMD::Funcs::atan_u8x32(in_);
					}
				}
				else if constexpr (PerElementWidthIfInt_ == 16)
				{
					if constexpr (SignedIfInt_)
					{
						return EmuSIMD::Funcs::atan_i16x16(in_);
					}
					else
					{
						return EmuSIMD::Funcs::atan_u16x16(in_);
					}
				}
				else if constexpr (PerElementWidthIfInt_ == 32)
				{
					if constexpr (SignedIfInt_)
					{
						return EmuSIMD::Funcs::atan_i32x8(in_);
					}
					else
					{
						return EmuSIMD::Funcs::atan_u32x8(in_);
					}
				}
				else if constexpr (PerElementWidthIfInt_ == 64)
				{
					if constexpr (SignedIfInt_)
					{
						return EmuSIMD::Funcs::atan_i64x4(in_);
					}
					else
					{
						return EmuSIMD::Funcs::atan_u64x4(in_);
					}
				}
				else
				{
					static_assert
					(
						EmuCore::TMP::get_false<PerElementWidthIfInt_>(),
						"Attempted to calculate the arc tangent of elements in a generic 256-bit integral SIMD register, but the provided width per element is invalid. Valid values are 8, 16, 32, and 64."
					);
				}
			}
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::i512_generic>)
			{
				if constexpr (PerElementWidthIfInt_ == 8)
				{
					if constexpr (SignedIfInt_)
					{
						return EmuSIMD::Funcs::atan_i8x64(in_);
					}
					else
					{
						return EmuSIMD::Funcs::atan_u8x64(in_);
					}
				}
				else if constexpr (PerElementWidthIfInt_ == 16)
				{
					if constexpr (SignedIfInt_)
					{
						return EmuSIMD::Funcs::atan_i16x32(in_);
					}
					else
					{
						return EmuSIMD::Funcs::atan_u16x32(in_);
					}
				}
				else if constexpr (PerElementWidthIfInt_ == 32)
				{
					if constexpr (SignedIfInt_)
					{
						return EmuSIMD::Funcs::atan_i32x16(in_);
					}
					else
					{
						return EmuSIMD::Funcs::atan_u32x16(in_);
					}
				}
				else if constexpr (PerElementWidthIfInt_ == 64)
				{
					if constexpr (SignedIfInt_)
					{
						return EmuSIMD::Funcs::atan_i64x8(in_);
					}
					else
					{
						return EmuSIMD::Funcs::atan_u64x8(in_);
					}
				}
				else
				{
					static_assert
					(
						EmuCore::TMP::get_false<PerElementWidthIfInt_>(),
						"Attempted to calculate the arc tangent of elements in a generic 512-bit integral SIMD register, but the provided width per element is invalid. Valid values are 8, 16, 32, and 64."
					);
				}
			}
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::i8x16>)
			{
				return EmuSIMD::Funcs::atan_i8x16(in_);
			}
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::i8x32>)
			{
				return EmuSIMD::Funcs::atan_i8x32(in_);
			}
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::i8x64>)
			{
				return EmuSIMD::Funcs::atan_i8x64(in_);
			}
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::u8x16>)
			{
				return EmuSIMD::Funcs::atan_u8x16(in_);
			}
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::u8x32>)
			{
				return EmuSIMD::Funcs::atan_u8x32(in_);
			}
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::u8x64>)
			{
				return EmuSIMD::Funcs::atan_u8x64(in_);
			}			
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::i16x8>)
			{
				return EmuSIMD::Funcs::atan_i16x8(in_);
			}
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::i16x16>)
			{
				return EmuSIMD::Funcs::atan_i16x16(in_);
			}
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::i16x32>)
			{
				return EmuSIMD::Funcs::atan_i16x32(in_);
			}
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::u16x8>)
			{
				return EmuSIMD::Funcs::atan_u16x8(in_);
			}
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::u16x16>)
			{
				return EmuSIMD::Funcs::atan_u16x16(in_);
			}
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::u16x32>)
			{
				return EmuSIMD::Funcs::atan_u16x32(in_);
			}			
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::i32x4>)
			{
				return EmuSIMD::Funcs::atan_i32x4(in_);
			}
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::i32x8>)
			{
				return EmuSIMD::Funcs::atan_i32x8(in_);
			}
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::i32x16>)
			{
				return EmuSIMD::Funcs::atan_i32x16(in_);
			}
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::u32x4>)
			{
				return EmuSIMD::Funcs::atan_u32x4(in_);
			}
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::u32x8>)
			{
				return EmuSIMD::Funcs::atan_u32x8(in_);
			}
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::u32x16>)
			{
				return EmuSIMD::Funcs::atan_u32x16(in_);
			}
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::i64x2>)
			{
				return EmuSIMD::Funcs::atan_i64x2(in_);
			}
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::i64x4>)
			{
				return EmuSIMD::Funcs::atan_i64x4(in_);
			}
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::i64x8>)
			{
				return EmuSIMD::Funcs::atan_i64x8(in_);
			}
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::u64x2>)
			{
				return EmuSIMD::Funcs::atan_u64x2(in_);
			}
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::u64x4>)
			{
				return EmuSIMD::Funcs::atan_u64x4(in_);
			}
			else if constexpr (std::is_same_v<in_uq, EmuSIMD::u64x8>)
			{
				return EmuSIMD::Funcs::atan_u64x8(in_);
			}
			else
			{
				static_assert
				(
					EmuCore::TMP::get_false<in_uq>(),
					"Attempted to calculate the arc tangent of a SIMD register via EmuSIMD helpers, but the provided in_ register is not a support register type for this operation."
				);
			}
		}
		else
		{
			static_assert
			(
				EmuCore::TMP::get_false<Register_>(),
				"Attempted to calculate the arc tangent of a SIMD register via EmuSIMD helpers, but the provided in_ register is not a recognised SIMD register type."
			);
		}
	}
#pragma endregion
}

#endif