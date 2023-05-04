#ifndef EMU_SIMD_COMMON_UNDERLYING_SIMD_CAST_INCLUDES_H_INC_
#define EMU_SIMD_COMMON_UNDERLYING_SIMD_CAST_INCLUDES_H_INC_ 1

#include "_common_underlying_simd_template_helper_includes.h"
#include "../../../../../EmuCore/TMPHelpers/Values.h"

namespace EmuSIMD::_underlying_simd_helpers
{
	template<class ToRegister_>
	[[nodiscard]] inline auto _cast_f32x4(EmuSIMD::f32x4_arg from_)
		-> typename std::remove_cvref<ToRegister_>::type
	{
		using to_uq = EmuCore::TMP::remove_ref_cv_t<ToRegister_>;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<to_uq>)
		{
			if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x4>)
			{
				return EmuSIMD::Funcs::cast_f32x4_f32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x8>)
			{
				return EmuSIMD::Funcs::cast_f32x4_f32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x16>)
			{
				return EmuSIMD::Funcs::cast_f32x4_f32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x2>)
			{
				return EmuSIMD::Funcs::cast_f32x4_f64x2(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x4>)
			{
				return EmuSIMD::Funcs::cast_f32x4_f64x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x8>)
			{
				return EmuSIMD::Funcs::cast_f32x4_f64x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i128_generic>)
			{
				return EmuSIMD::Funcs::cast_f32x4_i32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i256_generic>)
			{
				return EmuSIMD::Funcs::cast_f32x4_i32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i512_generic>)
			{
				return EmuSIMD::Funcs::cast_f32x4_i32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i8x16>)
			{
				return EmuSIMD::Funcs::cast_f32x4_i8x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i16x8>)
			{
				return EmuSIMD::Funcs::cast_f32x4_i16x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i32x4>)
			{
				return EmuSIMD::Funcs::cast_f32x4_i32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i64x2>)
			{
				return EmuSIMD::Funcs::cast_f32x4_i64x2(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i8x32>)
			{
				return EmuSIMD::Funcs::cast_f32x4_i8x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i16x16>)
			{
				return EmuSIMD::Funcs::cast_f32x4_i16x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i32x8>)
			{
				return EmuSIMD::Funcs::cast_f32x4_i32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i64x4>)
			{
				return EmuSIMD::Funcs::cast_f32x4_i64x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i8x64>)
			{
				return EmuSIMD::Funcs::cast_f32x4_i8x64(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i16x32>)
			{
				return EmuSIMD::Funcs::cast_f32x4_i16x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i32x16>)
			{
				return EmuSIMD::Funcs::cast_f32x4_i32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i64x8>)
			{
				return EmuSIMD::Funcs::cast_f32x4_i64x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u8x16>)
			{
				return EmuSIMD::Funcs::cast_f32x4_u8x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u16x8>)
			{
				return EmuSIMD::Funcs::cast_f32x4_u16x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u32x4>)
			{
				return EmuSIMD::Funcs::cast_f32x4_u32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u64x2>)
			{
				return EmuSIMD::Funcs::cast_f32x4_u64x2(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u8x32>)
			{
				return EmuSIMD::Funcs::cast_f32x4_u8x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u16x16>)
			{
				return EmuSIMD::Funcs::cast_f32x4_u16x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u32x8>)
			{
				return EmuSIMD::Funcs::cast_f32x4_u32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u64x4>)
			{
				return EmuSIMD::Funcs::cast_f32x4_u64x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u8x64>)
			{
				return EmuSIMD::Funcs::cast_f32x4_u8x64(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u16x32>)
			{
				return EmuSIMD::Funcs::cast_f32x4_u16x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u32x16>)
			{
				return EmuSIMD::Funcs::cast_f32x4_u32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u64x8>)
			{
				return EmuSIMD::Funcs::cast_f32x4_u64x8(from_);
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<ToRegister_>(), "Attempted to cast a EmuSIMD::f32x4 register via EmuSIMD helpers, but the provided SIMD register to cast to is not supported for this operation.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<ToRegister_>(), "Attempted to cast a EmuSIMD::f32x4 register via EmuSIMD helpers, but the provided register to cast to is not recognised as a supported SIMD register.");
		}
	}

	template<class ToRegister_>
	[[nodiscard]] inline auto _cast_f32x8(EmuSIMD::f32x8_arg from_)
		-> typename std::remove_cvref<ToRegister_>::type
	{
		using to_uq = EmuCore::TMP::remove_ref_cv_t<ToRegister_>;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<to_uq>)
		{
			if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x4>)
			{
				return EmuSIMD::Funcs::cast_f32x8_f32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x8>)
			{
				return EmuSIMD::Funcs::cast_f32x8_f32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x16>)
			{
				return EmuSIMD::Funcs::cast_f32x8_f32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x2>)
			{
				return EmuSIMD::Funcs::cast_f32x8_f64x2(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x4>)
			{
				return EmuSIMD::Funcs::cast_f32x8_f64x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x8>)
			{
				return EmuSIMD::Funcs::cast_f32x8_f64x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i128_generic>)
			{
				return EmuSIMD::Funcs::cast_f32x8_i32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i256_generic>)
			{
				return EmuSIMD::Funcs::cast_f32x8_i32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i512_generic>)
			{
				return EmuSIMD::Funcs::cast_f32x8_i32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i8x16>)
			{
				return EmuSIMD::Funcs::cast_f32x8_i8x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i16x8>)
			{
				return EmuSIMD::Funcs::cast_f32x8_i16x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i32x4>)
			{
				return EmuSIMD::Funcs::cast_f32x8_i32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i64x2>)
			{
				return EmuSIMD::Funcs::cast_f32x8_i64x2(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i8x32>)
			{
				return EmuSIMD::Funcs::cast_f32x8_i8x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i16x16>)
			{
				return EmuSIMD::Funcs::cast_f32x8_i16x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i32x8>)
			{
				return EmuSIMD::Funcs::cast_f32x8_i32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i64x4>)
			{
				return EmuSIMD::Funcs::cast_f32x8_i64x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i8x64>)
			{
				return EmuSIMD::Funcs::cast_f32x8_i8x64(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i16x32>)
			{
				return EmuSIMD::Funcs::cast_f32x8_i16x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i32x16>)
			{
				return EmuSIMD::Funcs::cast_f32x8_i32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i64x8>)
			{
				return EmuSIMD::Funcs::cast_f32x8_i64x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u8x16>)
			{
				return EmuSIMD::Funcs::cast_f32x8_u8x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u16x8>)
			{
				return EmuSIMD::Funcs::cast_f32x8_u16x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u32x4>)
			{
				return EmuSIMD::Funcs::cast_f32x8_u32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u64x2>)
			{
				return EmuSIMD::Funcs::cast_f32x8_u64x2(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u8x32>)
			{
				return EmuSIMD::Funcs::cast_f32x8_u8x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u16x16>)
			{
				return EmuSIMD::Funcs::cast_f32x8_u16x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u32x8>)
			{
				return EmuSIMD::Funcs::cast_f32x8_u32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u64x4>)
			{
				return EmuSIMD::Funcs::cast_f32x8_u64x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u8x64>)
			{
				return EmuSIMD::Funcs::cast_f32x8_u8x64(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u16x32>)
			{
				return EmuSIMD::Funcs::cast_f32x8_u16x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u32x16>)
			{
				return EmuSIMD::Funcs::cast_f32x8_u32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u64x8>)
			{
				return EmuSIMD::Funcs::cast_f32x8_u64x8(from_);
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<ToRegister_>(), "Attempted to cast a EmuSIMD::f32x8 register via EmuSIMD helpers, but the provided SIMD register to cast to is not supported for this operation.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<ToRegister_>(), "Attempted to cast a EmuSIMD::f32x8 register via EmuSIMD helpers, but the provided register to cast to is not recognised as a supported SIMD register.");
		}
	}

	template<class ToRegister_>
	[[nodiscard]] inline auto _cast_f32x16(EmuSIMD::f32x16_arg from_)
		-> typename std::remove_cvref<ToRegister_>::type
	{
		using to_uq = EmuCore::TMP::remove_ref_cv_t<ToRegister_>;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<to_uq>)
		{
			if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x4>)
			{
				return EmuSIMD::Funcs::cast_f32x16_f32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x8>)
			{
				return EmuSIMD::Funcs::cast_f32x16_f32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x16>)
			{
				return EmuSIMD::Funcs::cast_f32x16_f32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x2>)
			{
				return EmuSIMD::Funcs::cast_f32x16_f64x2(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x4>)
			{
				return EmuSIMD::Funcs::cast_f32x16_f64x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x8>)
			{
				return EmuSIMD::Funcs::cast_f32x16_f64x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i128_generic>)
			{
				return EmuSIMD::Funcs::cast_f32x16_i32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i256_generic>)
			{
				return EmuSIMD::Funcs::cast_f32x16_i32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i512_generic>)
			{
				return EmuSIMD::Funcs::cast_f32x16_i32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i8x16>)
			{
				return EmuSIMD::Funcs::cast_f32x16_i8x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i16x8>)
			{
				return EmuSIMD::Funcs::cast_f32x16_i16x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i32x4>)
			{
				return EmuSIMD::Funcs::cast_f32x16_i32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i64x2>)
			{
				return EmuSIMD::Funcs::cast_f32x16_i64x2(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i8x32>)
			{
				return EmuSIMD::Funcs::cast_f32x16_i8x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i16x16>)
			{
				return EmuSIMD::Funcs::cast_f32x16_i16x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i32x8>)
			{
				return EmuSIMD::Funcs::cast_f32x16_i32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i64x4>)
			{
				return EmuSIMD::Funcs::cast_f32x16_i64x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i8x64>)
			{
				return EmuSIMD::Funcs::cast_f32x16_i8x64(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i16x32>)
			{
				return EmuSIMD::Funcs::cast_f32x16_i16x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i32x16>)
			{
				return EmuSIMD::Funcs::cast_f32x16_i32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i64x8>)
			{
				return EmuSIMD::Funcs::cast_f32x16_i64x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u8x16>)
			{
				return EmuSIMD::Funcs::cast_f32x16_u8x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u16x8>)
			{
				return EmuSIMD::Funcs::cast_f32x16_u16x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u32x4>)
			{
				return EmuSIMD::Funcs::cast_f32x16_u32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u64x2>)
			{
				return EmuSIMD::Funcs::cast_f32x16_u64x2(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u8x32>)
			{
				return EmuSIMD::Funcs::cast_f32x16_u8x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u16x16>)
			{
				return EmuSIMD::Funcs::cast_f32x16_u16x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u32x8>)
			{
				return EmuSIMD::Funcs::cast_f32x16_u32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u64x4>)
			{
				return EmuSIMD::Funcs::cast_f32x16_u64x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u8x64>)
			{
				return EmuSIMD::Funcs::cast_f32x16_u8x64(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u16x32>)
			{
				return EmuSIMD::Funcs::cast_f32x16_u16x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u32x16>)
			{
				return EmuSIMD::Funcs::cast_f32x16_u32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u64x8>)
			{
				return EmuSIMD::Funcs::cast_f32x16_u64x8(from_);
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<ToRegister_>(), "Attempted to cast a EmuSIMD::f32x16 register via EmuSIMD helpers, but the provided SIMD register to cast to is not supported for this operation.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<ToRegister_>(), "Attempted to cast a EmuSIMD::f32x16 register via EmuSIMD helpers, but the provided register to cast to is not recognised as a supported SIMD register.");
		}
	}

	template<class ToRegister_>
	[[nodiscard]] inline auto _cast_f64x2(EmuSIMD::f64x2_arg from_)
		-> typename std::remove_cvref<ToRegister_>::type
	{
		using to_uq = EmuCore::TMP::remove_ref_cv_t<ToRegister_>;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<to_uq>)
		{
			if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x4>)
			{
				return EmuSIMD::Funcs::cast_f64x2_f32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x8>)
			{
				return EmuSIMD::Funcs::cast_f64x2_f32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x16>)
			{
				return EmuSIMD::Funcs::cast_f64x2_f32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x2>)
			{
				return EmuSIMD::Funcs::cast_f64x2_f64x2(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x4>)
			{
				return EmuSIMD::Funcs::cast_f64x2_f64x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x8>)
			{
				return EmuSIMD::Funcs::cast_f64x2_f64x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i128_generic>)
			{
				return EmuSIMD::Funcs::cast_f64x2_i32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i256_generic>)
			{
				return EmuSIMD::Funcs::cast_f64x2_i32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i512_generic>)
			{
				return EmuSIMD::Funcs::cast_f64x2_i32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i8x16>)
			{
				return EmuSIMD::Funcs::cast_f64x2_i8x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i16x8>)
			{
				return EmuSIMD::Funcs::cast_f64x2_i16x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i32x4>)
			{
				return EmuSIMD::Funcs::cast_f64x2_i32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i64x2>)
			{
				return EmuSIMD::Funcs::cast_f64x2_i64x2(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i8x32>)
			{
				return EmuSIMD::Funcs::cast_f64x2_i8x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i16x16>)
			{
				return EmuSIMD::Funcs::cast_f64x2_i16x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i32x8>)
			{
				return EmuSIMD::Funcs::cast_f64x2_i32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i64x4>)
			{
				return EmuSIMD::Funcs::cast_f64x2_i64x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i8x64>)
			{
				return EmuSIMD::Funcs::cast_f64x2_i8x64(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i16x32>)
			{
				return EmuSIMD::Funcs::cast_f64x2_i16x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i32x16>)
			{
				return EmuSIMD::Funcs::cast_f64x2_i32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i64x8>)
			{
				return EmuSIMD::Funcs::cast_f64x2_i64x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u8x16>)
			{
				return EmuSIMD::Funcs::cast_f64x2_u8x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u16x8>)
			{
				return EmuSIMD::Funcs::cast_f64x2_u16x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u32x4>)
			{
				return EmuSIMD::Funcs::cast_f64x2_u32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u64x2>)
			{
				return EmuSIMD::Funcs::cast_f64x2_u64x2(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u8x32>)
			{
				return EmuSIMD::Funcs::cast_f64x2_u8x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u16x16>)
			{
				return EmuSIMD::Funcs::cast_f64x2_u16x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u32x8>)
			{
				return EmuSIMD::Funcs::cast_f64x2_u32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u64x4>)
			{
				return EmuSIMD::Funcs::cast_f64x2_u64x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u8x64>)
			{
				return EmuSIMD::Funcs::cast_f64x2_u8x64(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u16x32>)
			{
				return EmuSIMD::Funcs::cast_f64x2_u16x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u32x16>)
			{
				return EmuSIMD::Funcs::cast_f64x2_u32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u64x8>)
			{
				return EmuSIMD::Funcs::cast_f64x2_u64x8(from_);
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<ToRegister_>(), "Attempted to cast a EmuSIMD::f64x2 register via EmuSIMD helpers, but the provided SIMD register to cast to is not supported for this operation.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<ToRegister_>(), "Attempted to cast a EmuSIMD::f64x2 register via EmuSIMD helpers, but the provided register to cast to is not recognised as a supported SIMD register.");
		}
	}

	template<class ToRegister_>
	[[nodiscard]] inline auto _cast_f64x4(EmuSIMD::f64x4_arg from_)
		-> typename std::remove_cvref<ToRegister_>::type
	{
		using to_uq = EmuCore::TMP::remove_ref_cv_t<ToRegister_>;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<to_uq>)
		{
			if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x4>)
			{
				return EmuSIMD::Funcs::cast_f64x4_f32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x8>)
			{
				return EmuSIMD::Funcs::cast_f64x4_f32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x16>)
			{
				return EmuSIMD::Funcs::cast_f64x4_f32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x2>)
			{
				return EmuSIMD::Funcs::cast_f64x4_f64x2(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x4>)
			{
				return EmuSIMD::Funcs::cast_f64x4_f64x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x8>)
			{
				return EmuSIMD::Funcs::cast_f64x4_f64x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i128_generic>)
			{
				return EmuSIMD::Funcs::cast_f64x4_i32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i256_generic>)
			{
				return EmuSIMD::Funcs::cast_f64x4_i32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i512_generic>)
			{
				return EmuSIMD::Funcs::cast_f64x4_i32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i8x16>)
			{
				return EmuSIMD::Funcs::cast_f64x4_i8x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i16x8>)
			{
				return EmuSIMD::Funcs::cast_f64x4_i16x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i32x4>)
			{
				return EmuSIMD::Funcs::cast_f64x4_i32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i64x2>)
			{
				return EmuSIMD::Funcs::cast_f64x4_i64x2(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i8x32>)
			{
				return EmuSIMD::Funcs::cast_f64x4_i8x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i16x16>)
			{
				return EmuSIMD::Funcs::cast_f64x4_i16x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i32x8>)
			{
				return EmuSIMD::Funcs::cast_f64x4_i32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i64x4>)
			{
				return EmuSIMD::Funcs::cast_f64x4_i64x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i8x64>)
			{
				return EmuSIMD::Funcs::cast_f64x4_i8x64(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i16x32>)
			{
				return EmuSIMD::Funcs::cast_f64x4_i16x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i32x16>)
			{
				return EmuSIMD::Funcs::cast_f64x4_i32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i64x8>)
			{
				return EmuSIMD::Funcs::cast_f64x4_i64x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u8x16>)
			{
				return EmuSIMD::Funcs::cast_f64x4_u8x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u16x8>)
			{
				return EmuSIMD::Funcs::cast_f64x4_u16x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u32x4>)
			{
				return EmuSIMD::Funcs::cast_f64x4_u32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u64x2>)
			{
				return EmuSIMD::Funcs::cast_f64x4_u64x2(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u8x32>)
			{
				return EmuSIMD::Funcs::cast_f64x4_u8x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u16x16>)
			{
				return EmuSIMD::Funcs::cast_f64x4_u16x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u32x8>)
			{
				return EmuSIMD::Funcs::cast_f64x4_u32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u64x4>)
			{
				return EmuSIMD::Funcs::cast_f64x4_u64x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u8x64>)
			{
				return EmuSIMD::Funcs::cast_f64x4_u8x64(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u16x32>)
			{
				return EmuSIMD::Funcs::cast_f64x4_u16x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u32x16>)
			{
				return EmuSIMD::Funcs::cast_f64x4_u32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u64x8>)
			{
				return EmuSIMD::Funcs::cast_f64x4_u64x8(from_);
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<ToRegister_>(), "Attempted to cast a EmuSIMD::f64x4 register via EmuSIMD helpers, but the provided SIMD register to cast to is not supported for this operation.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<ToRegister_>(), "Attempted to cast a EmuSIMD::f64x4 register via EmuSIMD helpers, but the provided register to cast to is not recognised as a supported SIMD register.");
		}
	}

	template<class ToRegister_>
	[[nodiscard]] inline auto _cast_f64x8(EmuSIMD::f64x8_arg from_)
		-> typename std::remove_cvref<ToRegister_>::type
	{
		using to_uq = EmuCore::TMP::remove_ref_cv_t<ToRegister_>;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<to_uq>)
		{
			if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x4>)
			{
				return EmuSIMD::Funcs::cast_f64x8_f32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x8>)
			{
				return EmuSIMD::Funcs::cast_f64x8_f32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x16>)
			{
				return EmuSIMD::Funcs::cast_f64x8_f32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x2>)
			{
				return EmuSIMD::Funcs::cast_f64x8_f64x2(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x4>)
			{
				return EmuSIMD::Funcs::cast_f64x8_f64x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x8>)
			{
				return EmuSIMD::Funcs::cast_f64x8_f64x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i128_generic>)
			{
				return EmuSIMD::Funcs::cast_f64x8_i32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i256_generic>)
			{
				return EmuSIMD::Funcs::cast_f64x8_i32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i512_generic>)
			{
				return EmuSIMD::Funcs::cast_f64x8_i32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i8x16>)
			{
				return EmuSIMD::Funcs::cast_f64x8_i8x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i16x8>)
			{
				return EmuSIMD::Funcs::cast_f64x8_i16x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i32x4>)
			{
				return EmuSIMD::Funcs::cast_f64x8_i32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i64x2>)
			{
				return EmuSIMD::Funcs::cast_f64x8_i64x2(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i8x32>)
			{
				return EmuSIMD::Funcs::cast_f64x8_i8x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i16x16>)
			{
				return EmuSIMD::Funcs::cast_f64x8_i16x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i32x8>)
			{
				return EmuSIMD::Funcs::cast_f64x8_i32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i64x4>)
			{
				return EmuSIMD::Funcs::cast_f64x8_i64x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i8x64>)
			{
				return EmuSIMD::Funcs::cast_f64x8_i8x64(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i16x32>)
			{
				return EmuSIMD::Funcs::cast_f64x8_i16x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i32x16>)
			{
				return EmuSIMD::Funcs::cast_f64x8_i32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i64x8>)
			{
				return EmuSIMD::Funcs::cast_f64x8_i64x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u8x16>)
			{
				return EmuSIMD::Funcs::cast_f64x8_u8x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u16x8>)
			{
				return EmuSIMD::Funcs::cast_f64x8_u16x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u32x4>)
			{
				return EmuSIMD::Funcs::cast_f64x8_u32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u64x2>)
			{
				return EmuSIMD::Funcs::cast_f64x8_u64x2(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u8x32>)
			{
				return EmuSIMD::Funcs::cast_f64x8_u8x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u16x16>)
			{
				return EmuSIMD::Funcs::cast_f64x8_u16x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u32x8>)
			{
				return EmuSIMD::Funcs::cast_f64x8_u32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u64x4>)
			{
				return EmuSIMD::Funcs::cast_f64x8_u64x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u8x64>)
			{
				return EmuSIMD::Funcs::cast_f64x8_u8x64(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u16x32>)
			{
				return EmuSIMD::Funcs::cast_f64x8_u16x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u32x16>)
			{
				return EmuSIMD::Funcs::cast_f64x8_u32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u64x8>)
			{
				return EmuSIMD::Funcs::cast_f64x8_u64x8(from_);
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<ToRegister_>(), "Attempted to cast a EmuSIMD::f64x8 register via EmuSIMD helpers, but the provided SIMD register to cast to is not supported for this operation.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<ToRegister_>(), "Attempted to cast a EmuSIMD::f64x8 register via EmuSIMD helpers, but the provided register to cast to is not recognised as a supported SIMD register.");
		}
	}

	template<class ToRegister_>
	[[nodiscard]] inline auto _cast_i8x16(EmuSIMD::i8x16_arg from_)
		-> typename std::remove_cvref<ToRegister_>::type
	{
		using to_uq = EmuCore::TMP::remove_ref_cv_t<ToRegister_>;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<to_uq>)
		{
			if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x4>)
			{
				return EmuSIMD::Funcs::cast_i8x16_f32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x8>)
			{
				return EmuSIMD::Funcs::cast_i8x16_f32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x16>)
			{
				return EmuSIMD::Funcs::cast_i8x16_f32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x2>)
			{
				return EmuSIMD::Funcs::cast_i8x16_f64x2(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x4>)
			{
				return EmuSIMD::Funcs::cast_i8x16_f64x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x8>)
			{
				return EmuSIMD::Funcs::cast_i8x16_f64x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i128_generic>)
			{
				return EmuSIMD::Funcs::cast_i8x16_i32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i256_generic>)
			{
				return EmuSIMD::Funcs::cast_i8x16_i32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i512_generic>)
			{
				return EmuSIMD::Funcs::cast_i8x16_i32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i8x16>)
			{
				return EmuSIMD::Funcs::cast_i8x16_i8x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i16x8>)
			{
				return EmuSIMD::Funcs::cast_i8x16_i16x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i32x4>)
			{
				return EmuSIMD::Funcs::cast_i8x16_i32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i64x2>)
			{
				return EmuSIMD::Funcs::cast_i8x16_i64x2(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i8x32>)
			{
				return EmuSIMD::Funcs::cast_i8x16_i8x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i16x16>)
			{
				return EmuSIMD::Funcs::cast_i8x16_i16x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i32x8>)
			{
				return EmuSIMD::Funcs::cast_i8x16_i32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i64x4>)
			{
				return EmuSIMD::Funcs::cast_i8x16_i64x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i8x64>)
			{
				return EmuSIMD::Funcs::cast_i8x16_i8x64(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i16x32>)
			{
				return EmuSIMD::Funcs::cast_i8x16_i16x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i32x16>)
			{
				return EmuSIMD::Funcs::cast_i8x16_i32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i64x8>)
			{
				return EmuSIMD::Funcs::cast_i8x16_i64x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u8x16>)
			{
				return EmuSIMD::Funcs::cast_i8x16_u8x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u16x8>)
			{
				return EmuSIMD::Funcs::cast_i8x16_u16x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u32x4>)
			{
				return EmuSIMD::Funcs::cast_i8x16_u32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u64x2>)
			{
				return EmuSIMD::Funcs::cast_i8x16_u64x2(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u8x32>)
			{
				return EmuSIMD::Funcs::cast_i8x16_u8x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u16x16>)
			{
				return EmuSIMD::Funcs::cast_i8x16_u16x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u32x8>)
			{
				return EmuSIMD::Funcs::cast_i8x16_u32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u64x4>)
			{
				return EmuSIMD::Funcs::cast_i8x16_u64x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u8x64>)
			{
				return EmuSIMD::Funcs::cast_i8x16_u8x64(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u16x32>)
			{
				return EmuSIMD::Funcs::cast_i8x16_u16x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u32x16>)
			{
				return EmuSIMD::Funcs::cast_i8x16_u32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u64x8>)
			{
				return EmuSIMD::Funcs::cast_i8x16_u64x8(from_);
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<ToRegister_>(), "Attempted to cast a EmuSIMD::i8x16 register via EmuSIMD helpers, but the provided SIMD register to cast to is not supported for this operation.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<ToRegister_>(), "Attempted to cast a EmuSIMD::i8x16 register via EmuSIMD helpers, but the provided register to cast to is not recognised as a supported SIMD register.");
		}
	}

	template<class ToRegister_>
	[[nodiscard]] inline auto _cast_i8x32(EmuSIMD::i8x32_arg from_)
		-> typename std::remove_cvref<ToRegister_>::type
	{
		using to_uq = EmuCore::TMP::remove_ref_cv_t<ToRegister_>;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<to_uq>)
		{
			if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x4>)
			{
				return EmuSIMD::Funcs::cast_i8x32_f32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x8>)
			{
				return EmuSIMD::Funcs::cast_i8x32_f32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x16>)
			{
				return EmuSIMD::Funcs::cast_i8x32_f32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x2>)
			{
				return EmuSIMD::Funcs::cast_i8x32_f64x2(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x4>)
			{
				return EmuSIMD::Funcs::cast_i8x32_f64x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x8>)
			{
				return EmuSIMD::Funcs::cast_i8x32_f64x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i128_generic>)
			{
				return EmuSIMD::Funcs::cast_i8x32_i32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i256_generic>)
			{
				return EmuSIMD::Funcs::cast_i8x32_i32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i512_generic>)
			{
				return EmuSIMD::Funcs::cast_i8x32_i32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i8x16>)
			{
				return EmuSIMD::Funcs::cast_i8x32_i8x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i16x8>)
			{
				return EmuSIMD::Funcs::cast_i8x32_i16x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i32x4>)
			{
				return EmuSIMD::Funcs::cast_i8x32_i32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i64x2>)
			{
				return EmuSIMD::Funcs::cast_i8x32_i64x2(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i8x32>)
			{
				return EmuSIMD::Funcs::cast_i8x32_i8x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i16x16>)
			{
				return EmuSIMD::Funcs::cast_i8x32_i16x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i32x8>)
			{
				return EmuSIMD::Funcs::cast_i8x32_i32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i64x4>)
			{
				return EmuSIMD::Funcs::cast_i8x32_i64x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i8x64>)
			{
				return EmuSIMD::Funcs::cast_i8x32_i8x64(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i16x32>)
			{
				return EmuSIMD::Funcs::cast_i8x32_i16x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i32x16>)
			{
				return EmuSIMD::Funcs::cast_i8x32_i32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i64x8>)
			{
				return EmuSIMD::Funcs::cast_i8x32_i64x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u8x16>)
			{
				return EmuSIMD::Funcs::cast_i8x32_u8x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u16x8>)
			{
				return EmuSIMD::Funcs::cast_i8x32_u16x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u32x4>)
			{
				return EmuSIMD::Funcs::cast_i8x32_u32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u64x2>)
			{
				return EmuSIMD::Funcs::cast_i8x32_u64x2(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u8x32>)
			{
				return EmuSIMD::Funcs::cast_i8x32_u8x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u16x16>)
			{
				return EmuSIMD::Funcs::cast_i8x32_u16x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u32x8>)
			{
				return EmuSIMD::Funcs::cast_i8x32_u32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u64x4>)
			{
				return EmuSIMD::Funcs::cast_i8x32_u64x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u8x64>)
			{
				return EmuSIMD::Funcs::cast_i8x32_u8x64(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u16x32>)
			{
				return EmuSIMD::Funcs::cast_i8x32_u16x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u32x16>)
			{
				return EmuSIMD::Funcs::cast_i8x32_u32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u64x8>)
			{
				return EmuSIMD::Funcs::cast_i8x32_u64x8(from_);
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<ToRegister_>(), "Attempted to cast a EmuSIMD::i8x32 register via EmuSIMD helpers, but the provided SIMD register to cast to is not supported for this operation.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<ToRegister_>(), "Attempted to cast a EmuSIMD::i8x32 register via EmuSIMD helpers, but the provided register to cast to is not recognised as a supported SIMD register.");
		}
	}

	template<class ToRegister_>
	[[nodiscard]] inline auto _cast_i8x64(EmuSIMD::i8x64_arg from_)
		-> typename std::remove_cvref<ToRegister_>::type
	{
		using to_uq = EmuCore::TMP::remove_ref_cv_t<ToRegister_>;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<to_uq>)
		{
			if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x4>)
			{
				return EmuSIMD::Funcs::cast_i8x64_f32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x8>)
			{
				return EmuSIMD::Funcs::cast_i8x64_f32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x16>)
			{
				return EmuSIMD::Funcs::cast_i8x64_f32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x2>)
			{
				return EmuSIMD::Funcs::cast_i8x64_f64x2(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x4>)
			{
				return EmuSIMD::Funcs::cast_i8x64_f64x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x8>)
			{
				return EmuSIMD::Funcs::cast_i8x64_f64x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i128_generic>)
			{
				return EmuSIMD::Funcs::cast_i8x64_i32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i256_generic>)
			{
				return EmuSIMD::Funcs::cast_i8x64_i32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i512_generic>)
			{
				return EmuSIMD::Funcs::cast_i8x64_i32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i8x16>)
			{
				return EmuSIMD::Funcs::cast_i8x64_i8x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i16x8>)
			{
				return EmuSIMD::Funcs::cast_i8x64_i16x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i32x4>)
			{
				return EmuSIMD::Funcs::cast_i8x64_i32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i64x2>)
			{
				return EmuSIMD::Funcs::cast_i8x64_i64x2(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i8x32>)
			{
				return EmuSIMD::Funcs::cast_i8x64_i8x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i16x16>)
			{
				return EmuSIMD::Funcs::cast_i8x64_i16x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i32x8>)
			{
				return EmuSIMD::Funcs::cast_i8x64_i32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i64x4>)
			{
				return EmuSIMD::Funcs::cast_i8x64_i64x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i8x64>)
			{
				return EmuSIMD::Funcs::cast_i8x64_i8x64(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i16x32>)
			{
				return EmuSIMD::Funcs::cast_i8x64_i16x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i32x16>)
			{
				return EmuSIMD::Funcs::cast_i8x64_i32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i64x8>)
			{
				return EmuSIMD::Funcs::cast_i8x64_i64x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u8x16>)
			{
				return EmuSIMD::Funcs::cast_i8x64_u8x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u16x8>)
			{
				return EmuSIMD::Funcs::cast_i8x64_u16x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u32x4>)
			{
				return EmuSIMD::Funcs::cast_i8x64_u32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u64x2>)
			{
				return EmuSIMD::Funcs::cast_i8x64_u64x2(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u8x32>)
			{
				return EmuSIMD::Funcs::cast_i8x64_u8x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u16x16>)
			{
				return EmuSIMD::Funcs::cast_i8x64_u16x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u32x8>)
			{
				return EmuSIMD::Funcs::cast_i8x64_u32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u64x4>)
			{
				return EmuSIMD::Funcs::cast_i8x64_u64x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u8x64>)
			{
				return EmuSIMD::Funcs::cast_i8x64_u8x64(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u16x32>)
			{
				return EmuSIMD::Funcs::cast_i8x64_u16x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u32x16>)
			{
				return EmuSIMD::Funcs::cast_i8x64_u32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u64x8>)
			{
				return EmuSIMD::Funcs::cast_i8x64_u64x8(from_);
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<ToRegister_>(), "Attempted to cast a EmuSIMD::i8x64 register via EmuSIMD helpers, but the provided SIMD register to cast to is not supported for this operation.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<ToRegister_>(), "Attempted to cast a EmuSIMD::i8x64 register via EmuSIMD helpers, but the provided register to cast to is not recognised as a supported SIMD register.");
		}
	}

	template<class ToRegister_>
	[[nodiscard]] inline auto _cast_i16x8(EmuSIMD::i16x8_arg from_)
		-> typename std::remove_cvref<ToRegister_>::type
	{
		using to_uq = EmuCore::TMP::remove_ref_cv_t<ToRegister_>;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<to_uq>)
		{
			if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x4>)
			{
				return EmuSIMD::Funcs::cast_i16x8_f32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x8>)
			{
				return EmuSIMD::Funcs::cast_i16x8_f32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x16>)
			{
				return EmuSIMD::Funcs::cast_i16x8_f32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x2>)
			{
				return EmuSIMD::Funcs::cast_i16x8_f64x2(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x4>)
			{
				return EmuSIMD::Funcs::cast_i16x8_f64x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x8>)
			{
				return EmuSIMD::Funcs::cast_i16x8_f64x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i128_generic>)
			{
				return EmuSIMD::Funcs::cast_i16x8_i32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i256_generic>)
			{
				return EmuSIMD::Funcs::cast_i16x8_i32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i512_generic>)
			{
				return EmuSIMD::Funcs::cast_i16x8_i32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i8x16>)
			{
				return EmuSIMD::Funcs::cast_i16x8_i8x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i16x8>)
			{
				return EmuSIMD::Funcs::cast_i16x8_i16x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i32x4>)
			{
				return EmuSIMD::Funcs::cast_i16x8_i32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i64x2>)
			{
				return EmuSIMD::Funcs::cast_i16x8_i64x2(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i8x32>)
			{
				return EmuSIMD::Funcs::cast_i16x8_i8x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i16x16>)
			{
				return EmuSIMD::Funcs::cast_i16x8_i16x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i32x8>)
			{
				return EmuSIMD::Funcs::cast_i16x8_i32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i64x4>)
			{
				return EmuSIMD::Funcs::cast_i16x8_i64x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i8x64>)
			{
				return EmuSIMD::Funcs::cast_i16x8_i8x64(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i16x32>)
			{
				return EmuSIMD::Funcs::cast_i16x8_i16x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i32x16>)
			{
				return EmuSIMD::Funcs::cast_i16x8_i32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i64x8>)
			{
				return EmuSIMD::Funcs::cast_i16x8_i64x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u8x16>)
			{
				return EmuSIMD::Funcs::cast_i16x8_u8x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u16x8>)
			{
				return EmuSIMD::Funcs::cast_i16x8_u16x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u32x4>)
			{
				return EmuSIMD::Funcs::cast_i16x8_u32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u64x2>)
			{
				return EmuSIMD::Funcs::cast_i16x8_u64x2(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u8x32>)
			{
				return EmuSIMD::Funcs::cast_i16x8_u8x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u16x16>)
			{
				return EmuSIMD::Funcs::cast_i16x8_u16x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u32x8>)
			{
				return EmuSIMD::Funcs::cast_i16x8_u32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u64x4>)
			{
				return EmuSIMD::Funcs::cast_i16x8_u64x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u8x64>)
			{
				return EmuSIMD::Funcs::cast_i16x8_u8x64(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u16x32>)
			{
				return EmuSIMD::Funcs::cast_i16x8_u16x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u32x16>)
			{
				return EmuSIMD::Funcs::cast_i16x8_u32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u64x8>)
			{
				return EmuSIMD::Funcs::cast_i16x8_u64x8(from_);
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<ToRegister_>(), "Attempted to cast a EmuSIMD::i16x8 register via EmuSIMD helpers, but the provided SIMD register to cast to is not supported for this operation.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<ToRegister_>(), "Attempted to cast a EmuSIMD::i16x8 register via EmuSIMD helpers, but the provided register to cast to is not recognised as a supported SIMD register.");
		}
	}



	template<class ToRegister_>
	[[nodiscard]] inline auto _cast_i16x16(EmuSIMD::i16x16_arg from_)
		-> typename std::remove_cvref<ToRegister_>::type
	{
		using to_uq = EmuCore::TMP::remove_ref_cv_t<ToRegister_>;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<to_uq>)
		{
			if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x4>)
			{
				return EmuSIMD::Funcs::cast_i16x16_f32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x8>)
			{
				return EmuSIMD::Funcs::cast_i16x16_f32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x16>)
			{
				return EmuSIMD::Funcs::cast_i16x16_f32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x2>)
			{
				return EmuSIMD::Funcs::cast_i16x16_f64x2(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x4>)
			{
				return EmuSIMD::Funcs::cast_i16x16_f64x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x8>)
			{
				return EmuSIMD::Funcs::cast_i16x16_f64x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i128_generic>)
			{
				return EmuSIMD::Funcs::cast_i16x16_i32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i256_generic>)
			{
				return EmuSIMD::Funcs::cast_i16x16_i32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i512_generic>)
			{
				return EmuSIMD::Funcs::cast_i16x16_i32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i8x16>)
			{
				return EmuSIMD::Funcs::cast_i16x16_i8x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i16x8>)
			{
				return EmuSIMD::Funcs::cast_i16x16_i16x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i32x4>)
			{
				return EmuSIMD::Funcs::cast_i16x16_i32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i64x2>)
			{
				return EmuSIMD::Funcs::cast_i16x16_i64x2(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i8x32>)
			{
				return EmuSIMD::Funcs::cast_i16x16_i8x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i16x16>)
			{
				return EmuSIMD::Funcs::cast_i16x16_i16x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i32x8>)
			{
				return EmuSIMD::Funcs::cast_i16x16_i32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i64x4>)
			{
				return EmuSIMD::Funcs::cast_i16x16_i64x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i8x64>)
			{
				return EmuSIMD::Funcs::cast_i16x16_i8x64(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i16x32>)
			{
				return EmuSIMD::Funcs::cast_i16x16_i16x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i32x16>)
			{
				return EmuSIMD::Funcs::cast_i16x16_i32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i64x8>)
			{
				return EmuSIMD::Funcs::cast_i16x16_i64x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u8x16>)
			{
				return EmuSIMD::Funcs::cast_i16x16_u8x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u16x8>)
			{
				return EmuSIMD::Funcs::cast_i16x16_u16x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u32x4>)
			{
				return EmuSIMD::Funcs::cast_i16x16_u32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u64x2>)
			{
				return EmuSIMD::Funcs::cast_i16x16_u64x2(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u8x32>)
			{
				return EmuSIMD::Funcs::cast_i16x16_u8x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u16x16>)
			{
				return EmuSIMD::Funcs::cast_i16x16_u16x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u32x8>)
			{
				return EmuSIMD::Funcs::cast_i16x16_u32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u64x4>)
			{
				return EmuSIMD::Funcs::cast_i16x16_u64x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u8x64>)
			{
				return EmuSIMD::Funcs::cast_i16x16_u8x64(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u16x32>)
			{
				return EmuSIMD::Funcs::cast_i16x16_u16x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u32x16>)
			{
				return EmuSIMD::Funcs::cast_i16x16_u32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u64x8>)
			{
				return EmuSIMD::Funcs::cast_i16x16_u64x8(from_);
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<ToRegister_>(), "Attempted to cast a EmuSIMD::i16x16 register via EmuSIMD helpers, but the provided SIMD register to cast to is not supported for this operation.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<ToRegister_>(), "Attempted to cast a EmuSIMD::i16x16 register via EmuSIMD helpers, but the provided register to cast to is not recognised as a supported SIMD register.");
		}
	}

	template<class ToRegister_>
	[[nodiscard]] inline auto _cast_i16x32(EmuSIMD::i16x32_arg from_)
		-> typename std::remove_cvref<ToRegister_>::type
	{
		using to_uq = EmuCore::TMP::remove_ref_cv_t<ToRegister_>;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<to_uq>)
		{
			if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x4>)
			{
				return EmuSIMD::Funcs::cast_i16x32_f32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x8>)
			{
				return EmuSIMD::Funcs::cast_i16x32_f32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x16>)
			{
				return EmuSIMD::Funcs::cast_i16x32_f32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x2>)
			{
				return EmuSIMD::Funcs::cast_i16x32_f64x2(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x4>)
			{
				return EmuSIMD::Funcs::cast_i16x32_f64x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x8>)
			{
				return EmuSIMD::Funcs::cast_i16x32_f64x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i128_generic>)
			{
				return EmuSIMD::Funcs::cast_i16x32_i32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i256_generic>)
			{
				return EmuSIMD::Funcs::cast_i16x32_i32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i512_generic>)
			{
				return EmuSIMD::Funcs::cast_i16x32_i32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i8x16>)
			{
				return EmuSIMD::Funcs::cast_i16x32_i8x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i16x8>)
			{
				return EmuSIMD::Funcs::cast_i16x32_i16x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i32x4>)
			{
				return EmuSIMD::Funcs::cast_i16x32_i32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i64x2>)
			{
				return EmuSIMD::Funcs::cast_i16x32_i64x2(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i8x32>)
			{
				return EmuSIMD::Funcs::cast_i16x32_i8x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i16x16>)
			{
				return EmuSIMD::Funcs::cast_i16x32_i16x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i32x8>)
			{
				return EmuSIMD::Funcs::cast_i16x32_i32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i64x4>)
			{
				return EmuSIMD::Funcs::cast_i16x32_i64x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i8x64>)
			{
				return EmuSIMD::Funcs::cast_i16x32_i8x64(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i16x32>)
			{
				return EmuSIMD::Funcs::cast_i16x32_i16x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i32x16>)
			{
				return EmuSIMD::Funcs::cast_i16x32_i32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i64x8>)
			{
				return EmuSIMD::Funcs::cast_i16x32_i64x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u8x16>)
			{
				return EmuSIMD::Funcs::cast_i16x32_u8x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u16x8>)
			{
				return EmuSIMD::Funcs::cast_i16x32_u16x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u32x4>)
			{
				return EmuSIMD::Funcs::cast_i16x32_u32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u64x2>)
			{
				return EmuSIMD::Funcs::cast_i16x32_u64x2(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u8x32>)
			{
				return EmuSIMD::Funcs::cast_i16x32_u8x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u16x16>)
			{
				return EmuSIMD::Funcs::cast_i16x32_u16x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u32x8>)
			{
				return EmuSIMD::Funcs::cast_i16x32_u32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u64x4>)
			{
				return EmuSIMD::Funcs::cast_i16x32_u64x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u8x64>)
			{
				return EmuSIMD::Funcs::cast_i16x32_u8x64(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u16x32>)
			{
				return EmuSIMD::Funcs::cast_i16x32_u16x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u32x16>)
			{
				return EmuSIMD::Funcs::cast_i16x32_u32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u64x8>)
			{
				return EmuSIMD::Funcs::cast_i16x32_u64x8(from_);
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<ToRegister_>(), "Attempted to cast a EmuSIMD::i16x32 register via EmuSIMD helpers, but the provided SIMD register to cast to is not supported for this operation.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<ToRegister_>(), "Attempted to cast a EmuSIMD::i16x32 register via EmuSIMD helpers, but the provided register to cast to is not recognised as a supported SIMD register.");
		}
	}

	template<class ToRegister_>
	[[nodiscard]] inline auto _cast_i32x4(EmuSIMD::i32x4_arg from_)
		-> typename std::remove_cvref<ToRegister_>::type
	{
		using to_uq = EmuCore::TMP::remove_ref_cv_t<ToRegister_>;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<to_uq>)
		{
			if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x4>)
			{
				return EmuSIMD::Funcs::cast_i32x4_f32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x8>)
			{
				return EmuSIMD::Funcs::cast_i32x4_f32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x16>)
			{
				return EmuSIMD::Funcs::cast_i32x4_f32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x2>)
			{
				return EmuSIMD::Funcs::cast_i32x4_f64x2(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x4>)
			{
				return EmuSIMD::Funcs::cast_i32x4_f64x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x8>)
			{
				return EmuSIMD::Funcs::cast_i32x4_f64x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i128_generic>)
			{
				return EmuSIMD::Funcs::cast_i32x4_i32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i256_generic>)
			{
				return EmuSIMD::Funcs::cast_i32x4_i32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i512_generic>)
			{
				return EmuSIMD::Funcs::cast_i32x4_i32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i8x16>)
			{
				return EmuSIMD::Funcs::cast_i32x4_i8x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i16x8>)
			{
				return EmuSIMD::Funcs::cast_i32x4_i16x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i32x4>)
			{
				return EmuSIMD::Funcs::cast_i32x4_i32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i64x2>)
			{
				return EmuSIMD::Funcs::cast_i32x4_i64x2(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i8x32>)
			{
				return EmuSIMD::Funcs::cast_i32x4_i8x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i16x16>)
			{
				return EmuSIMD::Funcs::cast_i32x4_i16x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i32x8>)
			{
				return EmuSIMD::Funcs::cast_i32x4_i32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i64x4>)
			{
				return EmuSIMD::Funcs::cast_i32x4_i64x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i8x64>)
			{
				return EmuSIMD::Funcs::cast_i32x4_i8x64(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i16x32>)
			{
				return EmuSIMD::Funcs::cast_i32x4_i16x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i32x16>)
			{
				return EmuSIMD::Funcs::cast_i32x4_i32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i64x8>)
			{
				return EmuSIMD::Funcs::cast_i32x4_i64x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u8x16>)
			{
				return EmuSIMD::Funcs::cast_i32x4_u8x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u16x8>)
			{
				return EmuSIMD::Funcs::cast_i32x4_u16x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u32x4>)
			{
				return EmuSIMD::Funcs::cast_i32x4_u32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u64x2>)
			{
				return EmuSIMD::Funcs::cast_i32x4_u64x2(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u8x32>)
			{
				return EmuSIMD::Funcs::cast_i32x4_u8x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u16x16>)
			{
				return EmuSIMD::Funcs::cast_i32x4_u16x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u32x8>)
			{
				return EmuSIMD::Funcs::cast_i32x4_u32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u64x4>)
			{
				return EmuSIMD::Funcs::cast_i32x4_u64x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u8x64>)
			{
				return EmuSIMD::Funcs::cast_i32x4_u8x64(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u16x32>)
			{
				return EmuSIMD::Funcs::cast_i32x4_u16x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u32x16>)
			{
				return EmuSIMD::Funcs::cast_i32x4_u32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u64x8>)
			{
				return EmuSIMD::Funcs::cast_i32x4_u64x8(from_);
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<ToRegister_>(), "Attempted to cast a EmuSIMD::i32x4 register via EmuSIMD helpers, but the provided SIMD register to cast to is not supported for this operation.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<ToRegister_>(), "Attempted to cast a EmuSIMD::i32x4 register via EmuSIMD helpers, but the provided register to cast to is not recognised as a supported SIMD register.");
		}
	}

	template<class ToRegister_>
	[[nodiscard]] inline auto _cast_i32x8(EmuSIMD::i32x8_arg from_)
		-> typename std::remove_cvref<ToRegister_>::type
	{
		using to_uq = EmuCore::TMP::remove_ref_cv_t<ToRegister_>;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<to_uq>)
		{
			if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x4>)
			{
				return EmuSIMD::Funcs::cast_i32x8_f32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x8>)
			{
				return EmuSIMD::Funcs::cast_i32x8_f32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x16>)
			{
				return EmuSIMD::Funcs::cast_i32x8_f32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x2>)
			{
				return EmuSIMD::Funcs::cast_i32x8_f64x2(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x4>)
			{
				return EmuSIMD::Funcs::cast_i32x8_f64x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x8>)
			{
				return EmuSIMD::Funcs::cast_i32x8_f64x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i128_generic>)
			{
				return EmuSIMD::Funcs::cast_i32x8_i32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i256_generic>)
			{
				return EmuSIMD::Funcs::cast_i32x8_i32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i512_generic>)
			{
				return EmuSIMD::Funcs::cast_i32x8_i32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i8x16>)
			{
				return EmuSIMD::Funcs::cast_i32x8_i8x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i16x8>)
			{
				return EmuSIMD::Funcs::cast_i32x8_i16x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i32x4>)
			{
				return EmuSIMD::Funcs::cast_i32x8_i32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i64x2>)
			{
				return EmuSIMD::Funcs::cast_i32x8_i64x2(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i8x32>)
			{
				return EmuSIMD::Funcs::cast_i32x8_i8x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i16x16>)
			{
				return EmuSIMD::Funcs::cast_i32x8_i16x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i32x8>)
			{
				return EmuSIMD::Funcs::cast_i32x8_i32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i64x4>)
			{
				return EmuSIMD::Funcs::cast_i32x8_i64x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i8x64>)
			{
				return EmuSIMD::Funcs::cast_i32x8_i8x64(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i16x32>)
			{
				return EmuSIMD::Funcs::cast_i32x8_i16x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i32x16>)
			{
				return EmuSIMD::Funcs::cast_i32x8_i32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i64x8>)
			{
				return EmuSIMD::Funcs::cast_i32x8_i64x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u8x16>)
			{
				return EmuSIMD::Funcs::cast_i32x8_u8x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u16x8>)
			{
				return EmuSIMD::Funcs::cast_i32x8_u16x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u32x4>)
			{
				return EmuSIMD::Funcs::cast_i32x8_u32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u64x2>)
			{
				return EmuSIMD::Funcs::cast_i32x8_u64x2(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u8x32>)
			{
				return EmuSIMD::Funcs::cast_i32x8_u8x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u16x16>)
			{
				return EmuSIMD::Funcs::cast_i32x8_u16x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u32x8>)
			{
				return EmuSIMD::Funcs::cast_i32x8_u32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u64x4>)
			{
				return EmuSIMD::Funcs::cast_i32x8_u64x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u8x64>)
			{
				return EmuSIMD::Funcs::cast_i32x8_u8x64(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u16x32>)
			{
				return EmuSIMD::Funcs::cast_i32x8_u16x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u32x16>)
			{
				return EmuSIMD::Funcs::cast_i32x8_u32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u64x8>)
			{
				return EmuSIMD::Funcs::cast_i32x8_u64x8(from_);
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<ToRegister_>(), "Attempted to cast a EmuSIMD::i32x8 register via EmuSIMD helpers, but the provided SIMD register to cast to is not supported for this operation.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<ToRegister_>(), "Attempted to cast a EmuSIMD::i32x8 register via EmuSIMD helpers, but the provided register to cast to is not recognised as a supported SIMD register.");
		}
	}

	template<class ToRegister_>
	[[nodiscard]] inline auto _cast_i32x16(EmuSIMD::i32x16_arg from_)
		-> typename std::remove_cvref<ToRegister_>::type
	{
		using to_uq = EmuCore::TMP::remove_ref_cv_t<ToRegister_>;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<to_uq>)
		{
			if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x4>)
			{
				return EmuSIMD::Funcs::cast_i32x16_f32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x8>)
			{
				return EmuSIMD::Funcs::cast_i32x16_f32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x16>)
			{
				return EmuSIMD::Funcs::cast_i32x16_f32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x2>)
			{
				return EmuSIMD::Funcs::cast_i32x16_f64x2(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x4>)
			{
				return EmuSIMD::Funcs::cast_i32x16_f64x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x8>)
			{
				return EmuSIMD::Funcs::cast_i32x16_f64x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i128_generic>)
			{
				return EmuSIMD::Funcs::cast_i32x16_i32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i256_generic>)
			{
				return EmuSIMD::Funcs::cast_i32x16_i32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i512_generic>)
			{
				return EmuSIMD::Funcs::cast_i32x16_i32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i8x16>)
			{
				return EmuSIMD::Funcs::cast_i32x16_i8x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i16x8>)
			{
				return EmuSIMD::Funcs::cast_i32x16_i16x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i32x4>)
			{
				return EmuSIMD::Funcs::cast_i32x16_i32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i64x2>)
			{
				return EmuSIMD::Funcs::cast_i32x16_i64x2(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i8x32>)
			{
				return EmuSIMD::Funcs::cast_i32x16_i8x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i16x16>)
			{
				return EmuSIMD::Funcs::cast_i32x16_i16x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i32x8>)
			{
				return EmuSIMD::Funcs::cast_i32x16_i32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i64x4>)
			{
				return EmuSIMD::Funcs::cast_i32x16_i64x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i8x64>)
			{
				return EmuSIMD::Funcs::cast_i32x16_i8x64(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i16x32>)
			{
				return EmuSIMD::Funcs::cast_i32x16_i16x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i32x16>)
			{
				return EmuSIMD::Funcs::cast_i32x16_i32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i64x8>)
			{
				return EmuSIMD::Funcs::cast_i32x16_i64x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u8x16>)
			{
				return EmuSIMD::Funcs::cast_i32x16_u8x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u16x8>)
			{
				return EmuSIMD::Funcs::cast_i32x16_u16x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u32x4>)
			{
				return EmuSIMD::Funcs::cast_i32x16_u32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u64x2>)
			{
				return EmuSIMD::Funcs::cast_i32x16_u64x2(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u8x32>)
			{
				return EmuSIMD::Funcs::cast_i32x16_u8x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u16x16>)
			{
				return EmuSIMD::Funcs::cast_i32x16_u16x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u32x8>)
			{
				return EmuSIMD::Funcs::cast_i32x16_u32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u64x4>)
			{
				return EmuSIMD::Funcs::cast_i32x16_u64x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u8x64>)
			{
				return EmuSIMD::Funcs::cast_i32x16_u8x64(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u16x32>)
			{
				return EmuSIMD::Funcs::cast_i32x16_u16x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u32x16>)
			{
				return EmuSIMD::Funcs::cast_i32x16_u32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u64x8>)
			{
				return EmuSIMD::Funcs::cast_i32x16_u64x8(from_);
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<ToRegister_>(), "Attempted to cast a EmuSIMD::i32x16 register via EmuSIMD helpers, but the provided SIMD register to cast to is not supported for this operation.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<ToRegister_>(), "Attempted to cast a EmuSIMD::i32x16 register via EmuSIMD helpers, but the provided register to cast to is not recognised as a supported SIMD register.");
		}
	}

	template<class ToRegister_>
	[[nodiscard]] inline auto _cast_i64x2(EmuSIMD::i64x2_arg from_)
		-> typename std::remove_cvref<ToRegister_>::type
	{
		using to_uq = EmuCore::TMP::remove_ref_cv_t<ToRegister_>;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<to_uq>)
		{
			if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x4>)
			{
				return EmuSIMD::Funcs::cast_i64x2_f32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x8>)
			{
				return EmuSIMD::Funcs::cast_i64x2_f32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x16>)
			{
				return EmuSIMD::Funcs::cast_i64x2_f32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x2>)
			{
				return EmuSIMD::Funcs::cast_i64x2_f64x2(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x4>)
			{
				return EmuSIMD::Funcs::cast_i64x2_f64x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x8>)
			{
				return EmuSIMD::Funcs::cast_i64x2_f64x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i128_generic>)
			{
				return EmuSIMD::Funcs::cast_i64x2_i32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i256_generic>)
			{
				return EmuSIMD::Funcs::cast_i64x2_i32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i512_generic>)
			{
				return EmuSIMD::Funcs::cast_i64x2_i32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i8x16>)
			{
				return EmuSIMD::Funcs::cast_i64x2_i8x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i16x8>)
			{
				return EmuSIMD::Funcs::cast_i64x2_i16x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i32x4>)
			{
				return EmuSIMD::Funcs::cast_i64x2_i32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i64x2>)
			{
				return EmuSIMD::Funcs::cast_i64x2_i64x2(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i8x32>)
			{
				return EmuSIMD::Funcs::cast_i64x2_i8x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i16x16>)
			{
				return EmuSIMD::Funcs::cast_i64x2_i16x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i32x8>)
			{
				return EmuSIMD::Funcs::cast_i64x2_i32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i64x4>)
			{
				return EmuSIMD::Funcs::cast_i64x2_i64x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i8x64>)
			{
				return EmuSIMD::Funcs::cast_i64x2_i8x64(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i16x32>)
			{
				return EmuSIMD::Funcs::cast_i64x2_i16x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i32x16>)
			{
				return EmuSIMD::Funcs::cast_i64x2_i32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i64x8>)
			{
				return EmuSIMD::Funcs::cast_i64x2_i64x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u8x16>)
			{
				return EmuSIMD::Funcs::cast_i64x2_u8x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u16x8>)
			{
				return EmuSIMD::Funcs::cast_i64x2_u16x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u32x4>)
			{
				return EmuSIMD::Funcs::cast_i64x2_u32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u64x2>)
			{
				return EmuSIMD::Funcs::cast_i64x2_u64x2(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u8x32>)
			{
				return EmuSIMD::Funcs::cast_i64x2_u8x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u16x16>)
			{
				return EmuSIMD::Funcs::cast_i64x2_u16x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u32x8>)
			{
				return EmuSIMD::Funcs::cast_i64x2_u32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u64x4>)
			{
				return EmuSIMD::Funcs::cast_i64x2_u64x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u8x64>)
			{
				return EmuSIMD::Funcs::cast_i64x2_u8x64(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u16x32>)
			{
				return EmuSIMD::Funcs::cast_i64x2_u16x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u32x16>)
			{
				return EmuSIMD::Funcs::cast_i64x2_u32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u64x8>)
			{
				return EmuSIMD::Funcs::cast_i64x2_u64x8(from_);
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<ToRegister_>(), "Attempted to cast a EmuSIMD::i64x2 register via EmuSIMD helpers, but the provided SIMD register to cast to is not supported for this operation.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<ToRegister_>(), "Attempted to cast a EmuSIMD::i64x2 register via EmuSIMD helpers, but the provided register to cast to is not recognised as a supported SIMD register.");
		}
	}

	template<class ToRegister_>
	[[nodiscard]] inline auto _cast_i64x4(EmuSIMD::i64x4_arg from_)
		-> typename std::remove_cvref<ToRegister_>::type
	{
		using to_uq = EmuCore::TMP::remove_ref_cv_t<ToRegister_>;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<to_uq>)
		{
			if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x4>)
			{
				return EmuSIMD::Funcs::cast_i64x4_f32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x8>)
			{
				return EmuSIMD::Funcs::cast_i64x4_f32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x16>)
			{
				return EmuSIMD::Funcs::cast_i64x4_f32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x2>)
			{
				return EmuSIMD::Funcs::cast_i64x4_f64x2(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x4>)
			{
				return EmuSIMD::Funcs::cast_i64x4_f64x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x8>)
			{
				return EmuSIMD::Funcs::cast_i64x4_f64x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i128_generic>)
			{
				return EmuSIMD::Funcs::cast_i64x4_i32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i256_generic>)
			{
				return EmuSIMD::Funcs::cast_i64x4_i32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i512_generic>)
			{
				return EmuSIMD::Funcs::cast_i64x4_i32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i8x16>)
			{
				return EmuSIMD::Funcs::cast_i64x4_i8x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i16x8>)
			{
				return EmuSIMD::Funcs::cast_i64x4_i16x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i32x4>)
			{
				return EmuSIMD::Funcs::cast_i64x4_i32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i64x2>)
			{
				return EmuSIMD::Funcs::cast_i64x4_i64x2(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i8x32>)
			{
				return EmuSIMD::Funcs::cast_i64x4_i8x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i16x16>)
			{
				return EmuSIMD::Funcs::cast_i64x4_i16x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i32x8>)
			{
				return EmuSIMD::Funcs::cast_i64x4_i32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i64x4>)
			{
				return EmuSIMD::Funcs::cast_i64x4_i64x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i8x64>)
			{
				return EmuSIMD::Funcs::cast_i64x4_i8x64(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i16x32>)
			{
				return EmuSIMD::Funcs::cast_i64x4_i16x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i32x16>)
			{
				return EmuSIMD::Funcs::cast_i64x4_i32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i64x8>)
			{
				return EmuSIMD::Funcs::cast_i64x4_i64x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u8x16>)
			{
				return EmuSIMD::Funcs::cast_i64x4_u8x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u16x8>)
			{
				return EmuSIMD::Funcs::cast_i64x4_u16x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u32x4>)
			{
				return EmuSIMD::Funcs::cast_i64x4_u32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u64x2>)
			{
				return EmuSIMD::Funcs::cast_i64x4_u64x2(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u8x32>)
			{
				return EmuSIMD::Funcs::cast_i64x4_u8x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u16x16>)
			{
				return EmuSIMD::Funcs::cast_i64x4_u16x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u32x8>)
			{
				return EmuSIMD::Funcs::cast_i64x4_u32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u64x4>)
			{
				return EmuSIMD::Funcs::cast_i64x4_u64x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u8x64>)
			{
				return EmuSIMD::Funcs::cast_i64x4_u8x64(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u16x32>)
			{
				return EmuSIMD::Funcs::cast_i64x4_u16x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u32x16>)
			{
				return EmuSIMD::Funcs::cast_i64x4_u32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u64x8>)
			{
				return EmuSIMD::Funcs::cast_i64x4_u64x8(from_);
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<ToRegister_>(), "Attempted to cast a EmuSIMD::i64x4 register via EmuSIMD helpers, but the provided SIMD register to cast to is not supported for this operation.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<ToRegister_>(), "Attempted to cast a EmuSIMD::i64x4 register via EmuSIMD helpers, but the provided register to cast to is not recognised as a supported SIMD register.");
		}
	}

	template<class ToRegister_>
	[[nodiscard]] inline auto _cast_i64x8(EmuSIMD::i64x8_arg from_)
		-> typename std::remove_cvref<ToRegister_>::type
	{
		using to_uq = EmuCore::TMP::remove_ref_cv_t<ToRegister_>;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<to_uq>)
		{
			if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x4>)
			{
				return EmuSIMD::Funcs::cast_i64x8_f32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x8>)
			{
				return EmuSIMD::Funcs::cast_i64x8_f32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x16>)
			{
				return EmuSIMD::Funcs::cast_i64x8_f32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x2>)
			{
				return EmuSIMD::Funcs::cast_i64x8_f64x2(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x4>)
			{
				return EmuSIMD::Funcs::cast_i64x8_f64x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x8>)
			{
				return EmuSIMD::Funcs::cast_i64x8_f64x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i128_generic>)
			{
				return EmuSIMD::Funcs::cast_i64x8_i32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i256_generic>)
			{
				return EmuSIMD::Funcs::cast_i64x8_i32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i512_generic>)
			{
				return EmuSIMD::Funcs::cast_i64x8_i32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i8x16>)
			{
				return EmuSIMD::Funcs::cast_i64x8_i8x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i16x8>)
			{
				return EmuSIMD::Funcs::cast_i64x8_i16x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i32x4>)
			{
				return EmuSIMD::Funcs::cast_i64x8_i32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i64x2>)
			{
				return EmuSIMD::Funcs::cast_i64x8_i64x2(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i8x32>)
			{
				return EmuSIMD::Funcs::cast_i64x8_i8x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i16x16>)
			{
				return EmuSIMD::Funcs::cast_i64x8_i16x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i32x8>)
			{
				return EmuSIMD::Funcs::cast_i64x8_i32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i64x4>)
			{
				return EmuSIMD::Funcs::cast_i64x8_i64x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i8x64>)
			{
				return EmuSIMD::Funcs::cast_i64x8_i8x64(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i16x32>)
			{
				return EmuSIMD::Funcs::cast_i64x8_i16x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i32x16>)
			{
				return EmuSIMD::Funcs::cast_i64x8_i32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i64x8>)
			{
				return EmuSIMD::Funcs::cast_i64x8_i64x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u8x16>)
			{
				return EmuSIMD::Funcs::cast_i64x8_u8x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u16x8>)
			{
				return EmuSIMD::Funcs::cast_i64x8_u16x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u32x4>)
			{
				return EmuSIMD::Funcs::cast_i64x8_u32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u64x2>)
			{
				return EmuSIMD::Funcs::cast_i64x8_u64x2(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u8x32>)
			{
				return EmuSIMD::Funcs::cast_i64x8_u8x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u16x16>)
			{
				return EmuSIMD::Funcs::cast_i64x8_u16x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u32x8>)
			{
				return EmuSIMD::Funcs::cast_i64x8_u32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u64x4>)
			{
				return EmuSIMD::Funcs::cast_i64x8_u64x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u8x64>)
			{
				return EmuSIMD::Funcs::cast_i64x8_u8x64(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u16x32>)
			{
				return EmuSIMD::Funcs::cast_i64x8_u16x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u32x16>)
			{
				return EmuSIMD::Funcs::cast_i64x8_u32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u64x8>)
			{
				return EmuSIMD::Funcs::cast_i64x8_u64x8(from_);
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<ToRegister_>(), "Attempted to cast a EmuSIMD::i64x8 register via EmuSIMD helpers, but the provided SIMD register to cast to is not supported for this operation.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<ToRegister_>(), "Attempted to cast a EmuSIMD::i64x8 register via EmuSIMD helpers, but the provided register to cast to is not recognised as a supported SIMD register.");
		}
	}

	// #########################################################################
	// # TODO: ALL REMAINING CASTS: UNSIGNED INTS                              #
	// # TODO: ALSO CALLING THESE FUNCTIONS FROM _simd_helpers_template_cast.h #
	// #########################################################################

	template<class ToRegister_>
	[[nodiscard]] inline auto _cast_u8x16(EmuSIMD::u8x16_arg from_)
		-> typename std::remove_cvref<ToRegister_>::type
	{
		using to_uq = EmuCore::TMP::remove_ref_cv_t<ToRegister_>;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<to_uq>)
		{
			if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x4>)
			{
				return EmuSIMD::Funcs::cast_u8x16_f32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x8>)
			{
				return EmuSIMD::Funcs::cast_u8x16_f32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x16>)
			{
				return EmuSIMD::Funcs::cast_u8x16_f32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x2>)
			{
				return EmuSIMD::Funcs::cast_u8x16_f64x2(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x4>)
			{
				return EmuSIMD::Funcs::cast_u8x16_f64x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x8>)
			{
				return EmuSIMD::Funcs::cast_u8x16_f64x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i128_generic>)
			{
				return EmuSIMD::Funcs::cast_u8x16_i32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i256_generic>)
			{
				return EmuSIMD::Funcs::cast_u8x16_i32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i512_generic>)
			{
				return EmuSIMD::Funcs::cast_u8x16_i32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i8x16>)
			{
				return EmuSIMD::Funcs::cast_u8x16_i8x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i16x8>)
			{
				return EmuSIMD::Funcs::cast_u8x16_i16x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i32x4>)
			{
				return EmuSIMD::Funcs::cast_u8x16_i32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i64x2>)
			{
				return EmuSIMD::Funcs::cast_u8x16_i64x2(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i8x32>)
			{
				return EmuSIMD::Funcs::cast_u8x16_i8x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i16x16>)
			{
				return EmuSIMD::Funcs::cast_u8x16_i16x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i32x8>)
			{
				return EmuSIMD::Funcs::cast_u8x16_i32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i64x4>)
			{
				return EmuSIMD::Funcs::cast_u8x16_i64x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i8x64>)
			{
				return EmuSIMD::Funcs::cast_u8x16_i8x64(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i16x32>)
			{
				return EmuSIMD::Funcs::cast_u8x16_i16x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i32x16>)
			{
				return EmuSIMD::Funcs::cast_u8x16_i32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i64x8>)
			{
				return EmuSIMD::Funcs::cast_u8x16_i64x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u8x16>)
			{
				return EmuSIMD::Funcs::cast_u8x16_u8x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u16x8>)
			{
				return EmuSIMD::Funcs::cast_u8x16_u16x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u32x4>)
			{
				return EmuSIMD::Funcs::cast_u8x16_u32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u64x2>)
			{
				return EmuSIMD::Funcs::cast_u8x16_u64x2(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u8x32>)
			{
				return EmuSIMD::Funcs::cast_u8x16_u8x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u16x16>)
			{
				return EmuSIMD::Funcs::cast_u8x16_u16x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u32x8>)
			{
				return EmuSIMD::Funcs::cast_u8x16_u32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u64x4>)
			{
				return EmuSIMD::Funcs::cast_u8x16_u64x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u8x64>)
			{
				return EmuSIMD::Funcs::cast_u8x16_u8x64(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u16x32>)
			{
				return EmuSIMD::Funcs::cast_u8x16_u16x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u32x16>)
			{
				return EmuSIMD::Funcs::cast_u8x16_u32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u64x8>)
			{
				return EmuSIMD::Funcs::cast_u8x16_u64x8(from_);
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<ToRegister_>(), "Attempted to cast a EmuSIMD::u8x16 register via EmuSIMD helpers, but the provided SIMD register to cast to is not supported for this operation.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<ToRegister_>(), "Attempted to cast a EmuSIMD::u8x16 register via EmuSIMD helpers, but the provided register to cast to is not recognised as a supported SIMD register.");
		}
	}

	template<class ToRegister_>
	[[nodiscard]] inline auto _cast_u8x32(EmuSIMD::u8x32_arg from_)
		-> typename std::remove_cvref<ToRegister_>::type
	{
		using to_uq = EmuCore::TMP::remove_ref_cv_t<ToRegister_>;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<to_uq>)
		{
			if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x4>)
			{
				return EmuSIMD::Funcs::cast_u8x32_f32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x8>)
			{
				return EmuSIMD::Funcs::cast_u8x32_f32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x16>)
			{
				return EmuSIMD::Funcs::cast_u8x32_f32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x2>)
			{
				return EmuSIMD::Funcs::cast_u8x32_f64x2(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x4>)
			{
				return EmuSIMD::Funcs::cast_u8x32_f64x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x8>)
			{
				return EmuSIMD::Funcs::cast_u8x32_f64x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i128_generic>)
			{
				return EmuSIMD::Funcs::cast_u8x32_i32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i256_generic>)
			{
				return EmuSIMD::Funcs::cast_u8x32_i32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i512_generic>)
			{
				return EmuSIMD::Funcs::cast_u8x32_i32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i8x16>)
			{
				return EmuSIMD::Funcs::cast_u8x32_i8x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i16x8>)
			{
				return EmuSIMD::Funcs::cast_u8x32_i16x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i32x4>)
			{
				return EmuSIMD::Funcs::cast_u8x32_i32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i64x2>)
			{
				return EmuSIMD::Funcs::cast_u8x32_i64x2(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i8x32>)
			{
				return EmuSIMD::Funcs::cast_u8x32_i8x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i16x16>)
			{
				return EmuSIMD::Funcs::cast_u8x32_i16x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i32x8>)
			{
				return EmuSIMD::Funcs::cast_u8x32_i32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i64x4>)
			{
				return EmuSIMD::Funcs::cast_u8x32_i64x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i8x64>)
			{
				return EmuSIMD::Funcs::cast_u8x32_i8x64(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i16x32>)
			{
				return EmuSIMD::Funcs::cast_u8x32_i16x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i32x16>)
			{
				return EmuSIMD::Funcs::cast_u8x32_i32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i64x8>)
			{
				return EmuSIMD::Funcs::cast_u8x32_i64x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u8x16>)
			{
				return EmuSIMD::Funcs::cast_u8x32_u8x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u16x8>)
			{
				return EmuSIMD::Funcs::cast_u8x32_u16x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u32x4>)
			{
				return EmuSIMD::Funcs::cast_u8x32_u32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u64x2>)
			{
				return EmuSIMD::Funcs::cast_u8x32_u64x2(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u8x32>)
			{
				return EmuSIMD::Funcs::cast_u8x32_u8x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u16x16>)
			{
				return EmuSIMD::Funcs::cast_u8x32_u16x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u32x8>)
			{
				return EmuSIMD::Funcs::cast_u8x32_u32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u64x4>)
			{
				return EmuSIMD::Funcs::cast_u8x32_u64x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u8x64>)
			{
				return EmuSIMD::Funcs::cast_u8x32_u8x64(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u16x32>)
			{
				return EmuSIMD::Funcs::cast_u8x32_u16x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u32x16>)
			{
				return EmuSIMD::Funcs::cast_u8x32_u32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u64x8>)
			{
				return EmuSIMD::Funcs::cast_u8x32_u64x8(from_);
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<ToRegister_>(), "Attempted to cast a EmuSIMD::u8x32 register via EmuSIMD helpers, but the provided SIMD register to cast to is not supported for this operation.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<ToRegister_>(), "Attempted to cast a EmuSIMD::u8x32 register via EmuSIMD helpers, but the provided register to cast to is not recognised as a supported SIMD register.");
		}
	}

	template<class ToRegister_>
	[[nodiscard]] inline auto _cast_u8x64(EmuSIMD::u8x64_arg from_)
		-> typename std::remove_cvref<ToRegister_>::type
	{
		using to_uq = EmuCore::TMP::remove_ref_cv_t<ToRegister_>;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<to_uq>)
		{
			if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x4>)
			{
				return EmuSIMD::Funcs::cast_u8x64_f32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x8>)
			{
				return EmuSIMD::Funcs::cast_u8x64_f32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x16>)
			{
				return EmuSIMD::Funcs::cast_u8x64_f32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x2>)
			{
				return EmuSIMD::Funcs::cast_u8x64_f64x2(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x4>)
			{
				return EmuSIMD::Funcs::cast_u8x64_f64x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x8>)
			{
				return EmuSIMD::Funcs::cast_u8x64_f64x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i128_generic>)
			{
				return EmuSIMD::Funcs::cast_u8x64_i32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i256_generic>)
			{
				return EmuSIMD::Funcs::cast_u8x64_i32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i512_generic>)
			{
				return EmuSIMD::Funcs::cast_u8x64_i32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i8x16>)
			{
				return EmuSIMD::Funcs::cast_u8x64_i8x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i16x8>)
			{
				return EmuSIMD::Funcs::cast_u8x64_i16x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i32x4>)
			{
				return EmuSIMD::Funcs::cast_u8x64_i32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i64x2>)
			{
				return EmuSIMD::Funcs::cast_u8x64_i64x2(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i8x32>)
			{
				return EmuSIMD::Funcs::cast_u8x64_i8x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i16x16>)
			{
				return EmuSIMD::Funcs::cast_u8x64_i16x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i32x8>)
			{
				return EmuSIMD::Funcs::cast_u8x64_i32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i64x4>)
			{
				return EmuSIMD::Funcs::cast_u8x64_i64x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i8x64>)
			{
				return EmuSIMD::Funcs::cast_u8x64_i8x64(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i16x32>)
			{
				return EmuSIMD::Funcs::cast_u8x64_i16x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i32x16>)
			{
				return EmuSIMD::Funcs::cast_u8x64_i32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i64x8>)
			{
				return EmuSIMD::Funcs::cast_u8x64_i64x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u8x16>)
			{
				return EmuSIMD::Funcs::cast_u8x64_u8x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u16x8>)
			{
				return EmuSIMD::Funcs::cast_u8x64_u16x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u32x4>)
			{
				return EmuSIMD::Funcs::cast_u8x64_u32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u64x2>)
			{
				return EmuSIMD::Funcs::cast_u8x64_u64x2(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u8x32>)
			{
				return EmuSIMD::Funcs::cast_u8x64_u8x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u16x16>)
			{
				return EmuSIMD::Funcs::cast_u8x64_u16x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u32x8>)
			{
				return EmuSIMD::Funcs::cast_u8x64_u32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u64x4>)
			{
				return EmuSIMD::Funcs::cast_u8x64_u64x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u8x64>)
			{
				return EmuSIMD::Funcs::cast_u8x64_u8x64(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u16x32>)
			{
				return EmuSIMD::Funcs::cast_u8x64_u16x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u32x16>)
			{
				return EmuSIMD::Funcs::cast_u8x64_u32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u64x8>)
			{
				return EmuSIMD::Funcs::cast_u8x64_u64x8(from_);
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<ToRegister_>(), "Attempted to cast a EmuSIMD::u8x64 register via EmuSIMD helpers, but the provided SIMD register to cast to is not supported for this operation.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<ToRegister_>(), "Attempted to cast a EmuSIMD::u8x64 register via EmuSIMD helpers, but the provided register to cast to is not recognised as a supported SIMD register.");
		}
	}

	template<class ToRegister_>
	[[nodiscard]] inline auto _cast_u16x8(EmuSIMD::u16x8_arg from_)
		-> typename std::remove_cvref<ToRegister_>::type
	{
		using to_uq = EmuCore::TMP::remove_ref_cv_t<ToRegister_>;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<to_uq>)
		{
			if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x4>)
			{
				return EmuSIMD::Funcs::cast_u16x8_f32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x8>)
			{
				return EmuSIMD::Funcs::cast_u16x8_f32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x16>)
			{
				return EmuSIMD::Funcs::cast_u16x8_f32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x2>)
			{
				return EmuSIMD::Funcs::cast_u16x8_f64x2(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x4>)
			{
				return EmuSIMD::Funcs::cast_u16x8_f64x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x8>)
			{
				return EmuSIMD::Funcs::cast_u16x8_f64x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i128_generic>)
			{
				return EmuSIMD::Funcs::cast_u16x8_i32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i256_generic>)
			{
				return EmuSIMD::Funcs::cast_u16x8_i32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i512_generic>)
			{
				return EmuSIMD::Funcs::cast_u16x8_i32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i8x16>)
			{
				return EmuSIMD::Funcs::cast_u16x8_i8x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i16x8>)
			{
				return EmuSIMD::Funcs::cast_u16x8_i16x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i32x4>)
			{
				return EmuSIMD::Funcs::cast_u16x8_i32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i64x2>)
			{
				return EmuSIMD::Funcs::cast_u16x8_i64x2(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i8x32>)
			{
				return EmuSIMD::Funcs::cast_u16x8_i8x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i16x16>)
			{
				return EmuSIMD::Funcs::cast_u16x8_i16x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i32x8>)
			{
				return EmuSIMD::Funcs::cast_u16x8_i32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i64x4>)
			{
				return EmuSIMD::Funcs::cast_u16x8_i64x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i8x64>)
			{
				return EmuSIMD::Funcs::cast_u16x8_i8x64(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i16x32>)
			{
				return EmuSIMD::Funcs::cast_u16x8_i16x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i32x16>)
			{
				return EmuSIMD::Funcs::cast_u16x8_i32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i64x8>)
			{
				return EmuSIMD::Funcs::cast_u16x8_i64x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u8x16>)
			{
				return EmuSIMD::Funcs::cast_u16x8_u8x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u16x8>)
			{
				return EmuSIMD::Funcs::cast_u16x8_u16x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u32x4>)
			{
				return EmuSIMD::Funcs::cast_u16x8_u32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u64x2>)
			{
				return EmuSIMD::Funcs::cast_u16x8_u64x2(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u8x32>)
			{
				return EmuSIMD::Funcs::cast_u16x8_u8x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u16x16>)
			{
				return EmuSIMD::Funcs::cast_u16x8_u16x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u32x8>)
			{
				return EmuSIMD::Funcs::cast_u16x8_u32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u64x4>)
			{
				return EmuSIMD::Funcs::cast_u16x8_u64x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u8x64>)
			{
				return EmuSIMD::Funcs::cast_u16x8_u8x64(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u16x32>)
			{
				return EmuSIMD::Funcs::cast_u16x8_u16x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u32x16>)
			{
				return EmuSIMD::Funcs::cast_u16x8_u32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u64x8>)
			{
				return EmuSIMD::Funcs::cast_u16x8_u64x8(from_);
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<ToRegister_>(), "Attempted to cast a EmuSIMD::u16x8 register via EmuSIMD helpers, but the provided SIMD register to cast to is not supported for this operation.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<ToRegister_>(), "Attempted to cast a EmuSIMD::u16x8 register via EmuSIMD helpers, but the provided register to cast to is not recognised as a supported SIMD register.");
		}
	}



	template<class ToRegister_>
	[[nodiscard]] inline auto _cast_u16x16(EmuSIMD::u16x16_arg from_)
		-> typename std::remove_cvref<ToRegister_>::type
	{
		using to_uq = EmuCore::TMP::remove_ref_cv_t<ToRegister_>;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<to_uq>)
		{
			if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x4>)
			{
				return EmuSIMD::Funcs::cast_u16x16_f32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x8>)
			{
				return EmuSIMD::Funcs::cast_u16x16_f32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x16>)
			{
				return EmuSIMD::Funcs::cast_u16x16_f32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x2>)
			{
				return EmuSIMD::Funcs::cast_u16x16_f64x2(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x4>)
			{
				return EmuSIMD::Funcs::cast_u16x16_f64x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x8>)
			{
				return EmuSIMD::Funcs::cast_u16x16_f64x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i128_generic>)
			{
				return EmuSIMD::Funcs::cast_u16x16_i32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i256_generic>)
			{
				return EmuSIMD::Funcs::cast_u16x16_i32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i512_generic>)
			{
				return EmuSIMD::Funcs::cast_u16x16_i32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i8x16>)
			{
				return EmuSIMD::Funcs::cast_u16x16_i8x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i16x8>)
			{
				return EmuSIMD::Funcs::cast_u16x16_i16x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i32x4>)
			{
				return EmuSIMD::Funcs::cast_u16x16_i32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i64x2>)
			{
				return EmuSIMD::Funcs::cast_u16x16_i64x2(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i8x32>)
			{
				return EmuSIMD::Funcs::cast_u16x16_i8x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i16x16>)
			{
				return EmuSIMD::Funcs::cast_u16x16_i16x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i32x8>)
			{
				return EmuSIMD::Funcs::cast_u16x16_i32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i64x4>)
			{
				return EmuSIMD::Funcs::cast_u16x16_i64x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i8x64>)
			{
				return EmuSIMD::Funcs::cast_u16x16_i8x64(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i16x32>)
			{
				return EmuSIMD::Funcs::cast_u16x16_i16x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i32x16>)
			{
				return EmuSIMD::Funcs::cast_u16x16_i32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i64x8>)
			{
				return EmuSIMD::Funcs::cast_u16x16_i64x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u8x16>)
			{
				return EmuSIMD::Funcs::cast_u16x16_u8x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u16x8>)
			{
				return EmuSIMD::Funcs::cast_u16x16_u16x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u32x4>)
			{
				return EmuSIMD::Funcs::cast_u16x16_u32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u64x2>)
			{
				return EmuSIMD::Funcs::cast_u16x16_u64x2(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u8x32>)
			{
				return EmuSIMD::Funcs::cast_u16x16_u8x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u16x16>)
			{
				return EmuSIMD::Funcs::cast_u16x16_u16x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u32x8>)
			{
				return EmuSIMD::Funcs::cast_u16x16_u32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u64x4>)
			{
				return EmuSIMD::Funcs::cast_u16x16_u64x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u8x64>)
			{
				return EmuSIMD::Funcs::cast_u16x16_u8x64(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u16x32>)
			{
				return EmuSIMD::Funcs::cast_u16x16_u16x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u32x16>)
			{
				return EmuSIMD::Funcs::cast_u16x16_u32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u64x8>)
			{
				return EmuSIMD::Funcs::cast_u16x16_u64x8(from_);
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<ToRegister_>(), "Attempted to cast a EmuSIMD::u16x16 register via EmuSIMD helpers, but the provided SIMD register to cast to is not supported for this operation.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<ToRegister_>(), "Attempted to cast a EmuSIMD::u16x16 register via EmuSIMD helpers, but the provided register to cast to is not recognised as a supported SIMD register.");
		}
	}

	template<class ToRegister_>
	[[nodiscard]] inline auto _cast_u16x32(EmuSIMD::u16x32_arg from_)
		-> typename std::remove_cvref<ToRegister_>::type
	{
		using to_uq = EmuCore::TMP::remove_ref_cv_t<ToRegister_>;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<to_uq>)
		{
			if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x4>)
			{
				return EmuSIMD::Funcs::cast_u16x32_f32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x8>)
			{
				return EmuSIMD::Funcs::cast_u16x32_f32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x16>)
			{
				return EmuSIMD::Funcs::cast_u16x32_f32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x2>)
			{
				return EmuSIMD::Funcs::cast_u16x32_f64x2(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x4>)
			{
				return EmuSIMD::Funcs::cast_u16x32_f64x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x8>)
			{
				return EmuSIMD::Funcs::cast_u16x32_f64x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i128_generic>)
			{
				return EmuSIMD::Funcs::cast_u16x32_i32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i256_generic>)
			{
				return EmuSIMD::Funcs::cast_u16x32_i32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i512_generic>)
			{
				return EmuSIMD::Funcs::cast_u16x32_i32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i8x16>)
			{
				return EmuSIMD::Funcs::cast_u16x32_i8x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i16x8>)
			{
				return EmuSIMD::Funcs::cast_u16x32_i16x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i32x4>)
			{
				return EmuSIMD::Funcs::cast_u16x32_i32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i64x2>)
			{
				return EmuSIMD::Funcs::cast_u16x32_i64x2(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i8x32>)
			{
				return EmuSIMD::Funcs::cast_u16x32_i8x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i16x16>)
			{
				return EmuSIMD::Funcs::cast_u16x32_i16x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i32x8>)
			{
				return EmuSIMD::Funcs::cast_u16x32_i32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i64x4>)
			{
				return EmuSIMD::Funcs::cast_u16x32_i64x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i8x64>)
			{
				return EmuSIMD::Funcs::cast_u16x32_i8x64(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i16x32>)
			{
				return EmuSIMD::Funcs::cast_u16x32_i16x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i32x16>)
			{
				return EmuSIMD::Funcs::cast_u16x32_i32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i64x8>)
			{
				return EmuSIMD::Funcs::cast_u16x32_i64x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u8x16>)
			{
				return EmuSIMD::Funcs::cast_u16x32_u8x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u16x8>)
			{
				return EmuSIMD::Funcs::cast_u16x32_u16x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u32x4>)
			{
				return EmuSIMD::Funcs::cast_u16x32_u32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u64x2>)
			{
				return EmuSIMD::Funcs::cast_u16x32_u64x2(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u8x32>)
			{
				return EmuSIMD::Funcs::cast_u16x32_u8x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u16x16>)
			{
				return EmuSIMD::Funcs::cast_u16x32_u16x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u32x8>)
			{
				return EmuSIMD::Funcs::cast_u16x32_u32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u64x4>)
			{
				return EmuSIMD::Funcs::cast_u16x32_u64x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u8x64>)
			{
				return EmuSIMD::Funcs::cast_u16x32_u8x64(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u16x32>)
			{
				return EmuSIMD::Funcs::cast_u16x32_u16x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u32x16>)
			{
				return EmuSIMD::Funcs::cast_u16x32_u32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u64x8>)
			{
				return EmuSIMD::Funcs::cast_u16x32_u64x8(from_);
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<ToRegister_>(), "Attempted to cast a EmuSIMD::u16x32 register via EmuSIMD helpers, but the provided SIMD register to cast to is not supported for this operation.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<ToRegister_>(), "Attempted to cast a EmuSIMD::u16x32 register via EmuSIMD helpers, but the provided register to cast to is not recognised as a supported SIMD register.");
		}
	}

	template<class ToRegister_>
	[[nodiscard]] inline auto _cast_u32x4(EmuSIMD::u32x4_arg from_)
		-> typename std::remove_cvref<ToRegister_>::type
	{
		using to_uq = EmuCore::TMP::remove_ref_cv_t<ToRegister_>;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<to_uq>)
		{
			if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x4>)
			{
				return EmuSIMD::Funcs::cast_u32x4_f32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x8>)
			{
				return EmuSIMD::Funcs::cast_u32x4_f32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x16>)
			{
				return EmuSIMD::Funcs::cast_u32x4_f32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x2>)
			{
				return EmuSIMD::Funcs::cast_u32x4_f64x2(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x4>)
			{
				return EmuSIMD::Funcs::cast_u32x4_f64x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x8>)
			{
				return EmuSIMD::Funcs::cast_u32x4_f64x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i128_generic>)
			{
				return EmuSIMD::Funcs::cast_u32x4_i32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i256_generic>)
			{
				return EmuSIMD::Funcs::cast_u32x4_i32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i512_generic>)
			{
				return EmuSIMD::Funcs::cast_u32x4_i32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i8x16>)
			{
				return EmuSIMD::Funcs::cast_u32x4_i8x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i16x8>)
			{
				return EmuSIMD::Funcs::cast_u32x4_i16x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i32x4>)
			{
				return EmuSIMD::Funcs::cast_u32x4_i32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i64x2>)
			{
				return EmuSIMD::Funcs::cast_u32x4_i64x2(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i8x32>)
			{
				return EmuSIMD::Funcs::cast_u32x4_i8x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i16x16>)
			{
				return EmuSIMD::Funcs::cast_u32x4_i16x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i32x8>)
			{
				return EmuSIMD::Funcs::cast_u32x4_i32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i64x4>)
			{
				return EmuSIMD::Funcs::cast_u32x4_i64x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i8x64>)
			{
				return EmuSIMD::Funcs::cast_u32x4_i8x64(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i16x32>)
			{
				return EmuSIMD::Funcs::cast_u32x4_i16x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i32x16>)
			{
				return EmuSIMD::Funcs::cast_u32x4_i32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i64x8>)
			{
				return EmuSIMD::Funcs::cast_u32x4_i64x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u8x16>)
			{
				return EmuSIMD::Funcs::cast_u32x4_u8x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u16x8>)
			{
				return EmuSIMD::Funcs::cast_u32x4_u16x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u32x4>)
			{
				return EmuSIMD::Funcs::cast_u32x4_u32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u64x2>)
			{
				return EmuSIMD::Funcs::cast_u32x4_u64x2(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u8x32>)
			{
				return EmuSIMD::Funcs::cast_u32x4_u8x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u16x16>)
			{
				return EmuSIMD::Funcs::cast_u32x4_u16x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u32x8>)
			{
				return EmuSIMD::Funcs::cast_u32x4_u32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u64x4>)
			{
				return EmuSIMD::Funcs::cast_u32x4_u64x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u8x64>)
			{
				return EmuSIMD::Funcs::cast_u32x4_u8x64(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u16x32>)
			{
				return EmuSIMD::Funcs::cast_u32x4_u16x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u32x16>)
			{
				return EmuSIMD::Funcs::cast_u32x4_u32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u64x8>)
			{
				return EmuSIMD::Funcs::cast_u32x4_u64x8(from_);
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<ToRegister_>(), "Attempted to cast a EmuSIMD::u32x4 register via EmuSIMD helpers, but the provided SIMD register to cast to is not supported for this operation.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<ToRegister_>(), "Attempted to cast a EmuSIMD::u32x4 register via EmuSIMD helpers, but the provided register to cast to is not recognised as a supported SIMD register.");
		}
	}

	template<class ToRegister_>
	[[nodiscard]] inline auto _cast_u32x8(EmuSIMD::u32x8_arg from_)
		-> typename std::remove_cvref<ToRegister_>::type
	{
		using to_uq = EmuCore::TMP::remove_ref_cv_t<ToRegister_>;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<to_uq>)
		{
			if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x4>)
			{
				return EmuSIMD::Funcs::cast_u32x8_f32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x8>)
			{
				return EmuSIMD::Funcs::cast_u32x8_f32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x16>)
			{
				return EmuSIMD::Funcs::cast_u32x8_f32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x2>)
			{
				return EmuSIMD::Funcs::cast_u32x8_f64x2(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x4>)
			{
				return EmuSIMD::Funcs::cast_u32x8_f64x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x8>)
			{
				return EmuSIMD::Funcs::cast_u32x8_f64x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i128_generic>)
			{
				return EmuSIMD::Funcs::cast_u32x8_i32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i256_generic>)
			{
				return EmuSIMD::Funcs::cast_u32x8_i32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i512_generic>)
			{
				return EmuSIMD::Funcs::cast_u32x8_i32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i8x16>)
			{
				return EmuSIMD::Funcs::cast_u32x8_i8x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i16x8>)
			{
				return EmuSIMD::Funcs::cast_u32x8_i16x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i32x4>)
			{
				return EmuSIMD::Funcs::cast_u32x8_i32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i64x2>)
			{
				return EmuSIMD::Funcs::cast_u32x8_i64x2(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i8x32>)
			{
				return EmuSIMD::Funcs::cast_u32x8_i8x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i16x16>)
			{
				return EmuSIMD::Funcs::cast_u32x8_i16x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i32x8>)
			{
				return EmuSIMD::Funcs::cast_u32x8_i32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i64x4>)
			{
				return EmuSIMD::Funcs::cast_u32x8_i64x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i8x64>)
			{
				return EmuSIMD::Funcs::cast_u32x8_i8x64(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i16x32>)
			{
				return EmuSIMD::Funcs::cast_u32x8_i16x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i32x16>)
			{
				return EmuSIMD::Funcs::cast_u32x8_i32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i64x8>)
			{
				return EmuSIMD::Funcs::cast_u32x8_i64x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u8x16>)
			{
				return EmuSIMD::Funcs::cast_u32x8_u8x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u16x8>)
			{
				return EmuSIMD::Funcs::cast_u32x8_u16x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u32x4>)
			{
				return EmuSIMD::Funcs::cast_u32x8_u32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u64x2>)
			{
				return EmuSIMD::Funcs::cast_u32x8_u64x2(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u8x32>)
			{
				return EmuSIMD::Funcs::cast_u32x8_u8x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u16x16>)
			{
				return EmuSIMD::Funcs::cast_u32x8_u16x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u32x8>)
			{
				return EmuSIMD::Funcs::cast_u32x8_u32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u64x4>)
			{
				return EmuSIMD::Funcs::cast_u32x8_u64x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u8x64>)
			{
				return EmuSIMD::Funcs::cast_u32x8_u8x64(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u16x32>)
			{
				return EmuSIMD::Funcs::cast_u32x8_u16x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u32x16>)
			{
				return EmuSIMD::Funcs::cast_u32x8_u32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u64x8>)
			{
				return EmuSIMD::Funcs::cast_u32x8_u64x8(from_);
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<ToRegister_>(), "Attempted to cast a EmuSIMD::u32x8 register via EmuSIMD helpers, but the provided SIMD register to cast to is not supported for this operation.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<ToRegister_>(), "Attempted to cast a EmuSIMD::u32x8 register via EmuSIMD helpers, but the provided register to cast to is not recognised as a supported SIMD register.");
		}
	}

	template<class ToRegister_>
	[[nodiscard]] inline auto _cast_u32x16(EmuSIMD::u32x16_arg from_)
		-> typename std::remove_cvref<ToRegister_>::type
	{
		using to_uq = EmuCore::TMP::remove_ref_cv_t<ToRegister_>;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<to_uq>)
		{
			if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x4>)
			{
				return EmuSIMD::Funcs::cast_u32x16_f32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x8>)
			{
				return EmuSIMD::Funcs::cast_u32x16_f32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x16>)
			{
				return EmuSIMD::Funcs::cast_u32x16_f32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x2>)
			{
				return EmuSIMD::Funcs::cast_u32x16_f64x2(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x4>)
			{
				return EmuSIMD::Funcs::cast_u32x16_f64x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x8>)
			{
				return EmuSIMD::Funcs::cast_u32x16_f64x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i128_generic>)
			{
				return EmuSIMD::Funcs::cast_u32x16_i32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i256_generic>)
			{
				return EmuSIMD::Funcs::cast_u32x16_i32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i512_generic>)
			{
				return EmuSIMD::Funcs::cast_u32x16_i32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i8x16>)
			{
				return EmuSIMD::Funcs::cast_u32x16_i8x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i16x8>)
			{
				return EmuSIMD::Funcs::cast_u32x16_i16x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i32x4>)
			{
				return EmuSIMD::Funcs::cast_u32x16_i32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i64x2>)
			{
				return EmuSIMD::Funcs::cast_u32x16_i64x2(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i8x32>)
			{
				return EmuSIMD::Funcs::cast_u32x16_i8x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i16x16>)
			{
				return EmuSIMD::Funcs::cast_u32x16_i16x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i32x8>)
			{
				return EmuSIMD::Funcs::cast_u32x16_i32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i64x4>)
			{
				return EmuSIMD::Funcs::cast_u32x16_i64x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i8x64>)
			{
				return EmuSIMD::Funcs::cast_u32x16_i8x64(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i16x32>)
			{
				return EmuSIMD::Funcs::cast_u32x16_i16x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i32x16>)
			{
				return EmuSIMD::Funcs::cast_u32x16_i32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i64x8>)
			{
				return EmuSIMD::Funcs::cast_u32x16_i64x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u8x16>)
			{
				return EmuSIMD::Funcs::cast_u32x16_u8x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u16x8>)
			{
				return EmuSIMD::Funcs::cast_u32x16_u16x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u32x4>)
			{
				return EmuSIMD::Funcs::cast_u32x16_u32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u64x2>)
			{
				return EmuSIMD::Funcs::cast_u32x16_u64x2(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u8x32>)
			{
				return EmuSIMD::Funcs::cast_u32x16_u8x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u16x16>)
			{
				return EmuSIMD::Funcs::cast_u32x16_u16x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u32x8>)
			{
				return EmuSIMD::Funcs::cast_u32x16_u32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u64x4>)
			{
				return EmuSIMD::Funcs::cast_u32x16_u64x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u8x64>)
			{
				return EmuSIMD::Funcs::cast_u32x16_u8x64(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u16x32>)
			{
				return EmuSIMD::Funcs::cast_u32x16_u16x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u32x16>)
			{
				return EmuSIMD::Funcs::cast_u32x16_u32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u64x8>)
			{
				return EmuSIMD::Funcs::cast_u32x16_u64x8(from_);
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<ToRegister_>(), "Attempted to cast a EmuSIMD::u32x16 register via EmuSIMD helpers, but the provided SIMD register to cast to is not supported for this operation.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<ToRegister_>(), "Attempted to cast a EmuSIMD::u32x16 register via EmuSIMD helpers, but the provided register to cast to is not recognised as a supported SIMD register.");
		}
	}

	template<class ToRegister_>
	[[nodiscard]] inline auto _cast_u64x2(EmuSIMD::u64x2_arg from_)
		-> typename std::remove_cvref<ToRegister_>::type
	{
		using to_uq = EmuCore::TMP::remove_ref_cv_t<ToRegister_>;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<to_uq>)
		{
			if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x4>)
			{
				return EmuSIMD::Funcs::cast_u64x2_f32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x8>)
			{
				return EmuSIMD::Funcs::cast_u64x2_f32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x16>)
			{
				return EmuSIMD::Funcs::cast_u64x2_f32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x2>)
			{
				return EmuSIMD::Funcs::cast_u64x2_f64x2(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x4>)
			{
				return EmuSIMD::Funcs::cast_u64x2_f64x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x8>)
			{
				return EmuSIMD::Funcs::cast_u64x2_f64x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i128_generic>)
			{
				return EmuSIMD::Funcs::cast_u64x2_i32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i256_generic>)
			{
				return EmuSIMD::Funcs::cast_u64x2_i32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i512_generic>)
			{
				return EmuSIMD::Funcs::cast_u64x2_i32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i8x16>)
			{
				return EmuSIMD::Funcs::cast_u64x2_i8x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i16x8>)
			{
				return EmuSIMD::Funcs::cast_u64x2_i16x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i32x4>)
			{
				return EmuSIMD::Funcs::cast_u64x2_i32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i64x2>)
			{
				return EmuSIMD::Funcs::cast_u64x2_i64x2(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i8x32>)
			{
				return EmuSIMD::Funcs::cast_u64x2_i8x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i16x16>)
			{
				return EmuSIMD::Funcs::cast_u64x2_i16x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i32x8>)
			{
				return EmuSIMD::Funcs::cast_u64x2_i32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i64x4>)
			{
				return EmuSIMD::Funcs::cast_u64x2_i64x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i8x64>)
			{
				return EmuSIMD::Funcs::cast_u64x2_i8x64(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i16x32>)
			{
				return EmuSIMD::Funcs::cast_u64x2_i16x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i32x16>)
			{
				return EmuSIMD::Funcs::cast_u64x2_i32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i64x8>)
			{
				return EmuSIMD::Funcs::cast_u64x2_i64x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u8x16>)
			{
				return EmuSIMD::Funcs::cast_u64x2_u8x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u16x8>)
			{
				return EmuSIMD::Funcs::cast_u64x2_u16x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u32x4>)
			{
				return EmuSIMD::Funcs::cast_u64x2_u32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u64x2>)
			{
				return EmuSIMD::Funcs::cast_u64x2_u64x2(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u8x32>)
			{
				return EmuSIMD::Funcs::cast_u64x2_u8x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u16x16>)
			{
				return EmuSIMD::Funcs::cast_u64x2_u16x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u32x8>)
			{
				return EmuSIMD::Funcs::cast_u64x2_u32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u64x4>)
			{
				return EmuSIMD::Funcs::cast_u64x2_u64x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u8x64>)
			{
				return EmuSIMD::Funcs::cast_u64x2_u8x64(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u16x32>)
			{
				return EmuSIMD::Funcs::cast_u64x2_u16x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u32x16>)
			{
				return EmuSIMD::Funcs::cast_u64x2_u32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u64x8>)
			{
				return EmuSIMD::Funcs::cast_u64x2_u64x8(from_);
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<ToRegister_>(), "Attempted to cast a EmuSIMD::u64x2 register via EmuSIMD helpers, but the provided SIMD register to cast to is not supported for this operation.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<ToRegister_>(), "Attempted to cast a EmuSIMD::u64x2 register via EmuSIMD helpers, but the provided register to cast to is not recognised as a supported SIMD register.");
		}
	}

	template<class ToRegister_>
	[[nodiscard]] inline auto _cast_u64x4(EmuSIMD::u64x4_arg from_)
		-> typename std::remove_cvref<ToRegister_>::type
	{
		using to_uq = EmuCore::TMP::remove_ref_cv_t<ToRegister_>;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<to_uq>)
		{
			if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x4>)
			{
				return EmuSIMD::Funcs::cast_u64x4_f32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x8>)
			{
				return EmuSIMD::Funcs::cast_u64x4_f32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x16>)
			{
				return EmuSIMD::Funcs::cast_u64x4_f32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x2>)
			{
				return EmuSIMD::Funcs::cast_u64x4_f64x2(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x4>)
			{
				return EmuSIMD::Funcs::cast_u64x4_f64x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x8>)
			{
				return EmuSIMD::Funcs::cast_u64x4_f64x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i128_generic>)
			{
				return EmuSIMD::Funcs::cast_u64x4_i32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i256_generic>)
			{
				return EmuSIMD::Funcs::cast_u64x4_i32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i512_generic>)
			{
				return EmuSIMD::Funcs::cast_u64x4_i32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i8x16>)
			{
				return EmuSIMD::Funcs::cast_u64x4_i8x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i16x8>)
			{
				return EmuSIMD::Funcs::cast_u64x4_i16x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i32x4>)
			{
				return EmuSIMD::Funcs::cast_u64x4_i32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i64x2>)
			{
				return EmuSIMD::Funcs::cast_u64x4_i64x2(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i8x32>)
			{
				return EmuSIMD::Funcs::cast_u64x4_i8x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i16x16>)
			{
				return EmuSIMD::Funcs::cast_u64x4_i16x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i32x8>)
			{
				return EmuSIMD::Funcs::cast_u64x4_i32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i64x4>)
			{
				return EmuSIMD::Funcs::cast_u64x4_i64x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i8x64>)
			{
				return EmuSIMD::Funcs::cast_u64x4_i8x64(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i16x32>)
			{
				return EmuSIMD::Funcs::cast_u64x4_i16x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i32x16>)
			{
				return EmuSIMD::Funcs::cast_u64x4_i32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i64x8>)
			{
				return EmuSIMD::Funcs::cast_u64x4_i64x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u8x16>)
			{
				return EmuSIMD::Funcs::cast_u64x4_u8x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u16x8>)
			{
				return EmuSIMD::Funcs::cast_u64x4_u16x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u32x4>)
			{
				return EmuSIMD::Funcs::cast_u64x4_u32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u64x2>)
			{
				return EmuSIMD::Funcs::cast_u64x4_u64x2(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u8x32>)
			{
				return EmuSIMD::Funcs::cast_u64x4_u8x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u16x16>)
			{
				return EmuSIMD::Funcs::cast_u64x4_u16x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u32x8>)
			{
				return EmuSIMD::Funcs::cast_u64x4_u32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u64x4>)
			{
				return EmuSIMD::Funcs::cast_u64x4_u64x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u8x64>)
			{
				return EmuSIMD::Funcs::cast_u64x4_u8x64(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u16x32>)
			{
				return EmuSIMD::Funcs::cast_u64x4_u16x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u32x16>)
			{
				return EmuSIMD::Funcs::cast_u64x4_u32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u64x8>)
			{
				return EmuSIMD::Funcs::cast_u64x4_u64x8(from_);
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<ToRegister_>(), "Attempted to cast a EmuSIMD::u64x4 register via EmuSIMD helpers, but the provided SIMD register to cast to is not supported for this operation.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<ToRegister_>(), "Attempted to cast a EmuSIMD::u64x4 register via EmuSIMD helpers, but the provided register to cast to is not recognised as a supported SIMD register.");
		}
	}

	template<class ToRegister_>
	[[nodiscard]] inline auto _cast_u64x8(EmuSIMD::u64x8_arg from_)
		-> typename std::remove_cvref<ToRegister_>::type
	{
		using to_uq = EmuCore::TMP::remove_ref_cv_t<ToRegister_>;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<to_uq>)
		{
			if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x4>)
			{
				return EmuSIMD::Funcs::cast_u64x8_f32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x8>)
			{
				return EmuSIMD::Funcs::cast_u64x8_f32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f32x16>)
			{
				return EmuSIMD::Funcs::cast_u64x8_f32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x2>)
			{
				return EmuSIMD::Funcs::cast_u64x8_f64x2(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x4>)
			{
				return EmuSIMD::Funcs::cast_u64x8_f64x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::f64x8>)
			{
				return EmuSIMD::Funcs::cast_u64x8_f64x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i128_generic>)
			{
				return EmuSIMD::Funcs::cast_u64x8_i32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i256_generic>)
			{
				return EmuSIMD::Funcs::cast_u64x8_i32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i512_generic>)
			{
				return EmuSIMD::Funcs::cast_u64x8_i32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i8x16>)
			{
				return EmuSIMD::Funcs::cast_u64x8_i8x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i16x8>)
			{
				return EmuSIMD::Funcs::cast_u64x8_i16x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i32x4>)
			{
				return EmuSIMD::Funcs::cast_u64x8_i32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i64x2>)
			{
				return EmuSIMD::Funcs::cast_u64x8_i64x2(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i8x32>)
			{
				return EmuSIMD::Funcs::cast_u64x8_i8x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i16x16>)
			{
				return EmuSIMD::Funcs::cast_u64x8_i16x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i32x8>)
			{
				return EmuSIMD::Funcs::cast_u64x8_i32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i64x4>)
			{
				return EmuSIMD::Funcs::cast_u64x8_i64x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i8x64>)
			{
				return EmuSIMD::Funcs::cast_u64x8_i8x64(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i16x32>)
			{
				return EmuSIMD::Funcs::cast_u64x8_i16x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i32x16>)
			{
				return EmuSIMD::Funcs::cast_u64x8_i32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::i64x8>)
			{
				return EmuSIMD::Funcs::cast_u64x8_i64x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u8x16>)
			{
				return EmuSIMD::Funcs::cast_u64x8_u8x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u16x8>)
			{
				return EmuSIMD::Funcs::cast_u64x8_u16x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u32x4>)
			{
				return EmuSIMD::Funcs::cast_u64x8_u32x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u64x2>)
			{
				return EmuSIMD::Funcs::cast_u64x8_u64x2(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u8x32>)
			{
				return EmuSIMD::Funcs::cast_u64x8_u8x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u16x16>)
			{
				return EmuSIMD::Funcs::cast_u64x8_u16x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u32x8>)
			{
				return EmuSIMD::Funcs::cast_u64x8_u32x8(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u64x4>)
			{
				return EmuSIMD::Funcs::cast_u64x8_u64x4(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u8x64>)
			{
				return EmuSIMD::Funcs::cast_u64x8_u8x64(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u16x32>)
			{
				return EmuSIMD::Funcs::cast_u64x8_u16x32(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u32x16>)
			{
				return EmuSIMD::Funcs::cast_u64x8_u32x16(from_);
			}
			else if constexpr (std::is_same_v<to_uq, EmuSIMD::u64x8>)
			{
				return EmuSIMD::Funcs::cast_u64x8_u64x8(from_);
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<ToRegister_>(), "Attempted to cast a EmuSIMD::u64x8 register via EmuSIMD helpers, but the provided SIMD register to cast to is not supported for this operation.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<ToRegister_>(), "Attempted to cast a EmuSIMD::u64x8 register via EmuSIMD helpers, but the provided register to cast to is not recognised as a supported SIMD register.");
		}
	}
}

#endif
