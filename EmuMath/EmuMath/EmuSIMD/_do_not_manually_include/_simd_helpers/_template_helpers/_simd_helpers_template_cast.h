#ifndef EMU_SIMD_HELPERS_TEMPLATE_CAST_H_INC_
#define EMU_SIMD_HELPERS_TEMPLATE_CAST_H_INC_ 1

#include "_underlying_template_helpers/_all_underlying_templates.h"
#include "_underlying_template_helpers/_generic_funcs/_forward_declarations/_forward_template_casts.h"
#include "../../../../EmuCore/TMPHelpers/Values.h"

namespace EmuSIMD
{
	template<EmuConcepts::KnownSIMD ToRegister_, EmuConcepts::KnownSIMD FromRegister_>
	[[nodiscard]] inline auto cast(FromRegister_&& from_)
		-> typename std::remove_cvref<ToRegister_>::type
	{
		using from_uq = EmuCore::TMP::remove_ref_cv_t<FromRegister_>;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<from_uq>)
		{
			using to_uq = EmuCore::TMP::remove_ref_cv_t<ToRegister_>;
			if constexpr (EmuSIMD::TMP::is_simd_register_v<to_uq>)
			{
				if constexpr (std::is_same_v<from_uq, EmuSIMD::f32x4>)
				{
					return EmuSIMD::_underlying_simd_helpers::_cast_f32x4<ToRegister_>(std::forward<FromRegister_>(from_));
				}
				else if constexpr (std::is_same_v<from_uq, EmuSIMD::f32x8>)
				{
					return EmuSIMD::_underlying_simd_helpers::_cast_f32x8<ToRegister_>(std::forward<FromRegister_>(from_));
				}
				else if constexpr (std::is_same_v<from_uq, EmuSIMD::f32x16>)
				{
					return EmuSIMD::_underlying_simd_helpers::_cast_f32x16<ToRegister_>(std::forward<FromRegister_>(from_));
				}
				else if constexpr (std::is_same_v<from_uq, EmuSIMD::f64x2>)
				{
					return EmuSIMD::_underlying_simd_helpers::_cast_f64x2<ToRegister_>(std::forward<FromRegister_>(from_));
				}
				else if constexpr (std::is_same_v<from_uq, EmuSIMD::f64x4>)
				{
					return EmuSIMD::_underlying_simd_helpers::_cast_f64x4<ToRegister_>(std::forward<FromRegister_>(from_));
				}
				else if constexpr (std::is_same_v<from_uq, EmuSIMD::f64x8>)
				{
					return EmuSIMD::_underlying_simd_helpers::_cast_f64x8<ToRegister_>(std::forward<FromRegister_>(from_));
				}
				else if constexpr (std::is_same_v<from_uq, EmuSIMD::i128_generic>)
				{
					return EmuSIMD::_underlying_simd_helpers::_cast_i32x4<ToRegister_>(std::forward<FromRegister_>(from_));
				}
				else if constexpr (std::is_same_v<from_uq, EmuSIMD::i256_generic>)
				{
					return EmuSIMD::_underlying_simd_helpers::_cast_i32x8<ToRegister_>(std::forward<FromRegister_>(from_));
				}
				else if constexpr (std::is_same_v<from_uq, EmuSIMD::i512_generic>)
				{
					return EmuSIMD::_underlying_simd_helpers::_cast_i32x16<ToRegister_>(std::forward<FromRegister_>(from_));
				}
				else if constexpr (std::is_same_v<from_uq, EmuSIMD::i8x16>)
				{
					return EmuSIMD::_underlying_simd_helpers::_cast_i8x16<ToRegister_>(std::forward<FromRegister_>(from_));
				}
				else if constexpr (std::is_same_v<from_uq, EmuSIMD::i8x32>)
				{
					return EmuSIMD::_underlying_simd_helpers::_cast_i8x32<ToRegister_>(std::forward<FromRegister_>(from_));
				}
				else if constexpr (std::is_same_v<from_uq, EmuSIMD::i8x64>)
				{
					return EmuSIMD::_underlying_simd_helpers::_cast_i8x64<ToRegister_>(std::forward<FromRegister_>(from_));
				}
				else if constexpr (std::is_same_v<from_uq, EmuSIMD::i16x8>)
				{
					return EmuSIMD::_underlying_simd_helpers::_cast_i16x8<ToRegister_>(std::forward<FromRegister_>(from_));
				}
				else if constexpr (std::is_same_v<from_uq, EmuSIMD::i16x16>)
				{
					return EmuSIMD::_underlying_simd_helpers::_cast_i16x16<ToRegister_>(std::forward<FromRegister_>(from_));
				}
				else if constexpr (std::is_same_v<from_uq, EmuSIMD::i16x32>)
				{
					return EmuSIMD::_underlying_simd_helpers::_cast_i16x32<ToRegister_>(std::forward<FromRegister_>(from_));
				}
				else if constexpr (std::is_same_v<from_uq, EmuSIMD::i32x4>)
				{
					return EmuSIMD::_underlying_simd_helpers::_cast_i32x4<ToRegister_>(std::forward<FromRegister_>(from_));
				}
				else if constexpr (std::is_same_v<from_uq, EmuSIMD::i32x8>)
				{
					return EmuSIMD::_underlying_simd_helpers::_cast_i32x8<ToRegister_>(std::forward<FromRegister_>(from_));
				}
				else if constexpr (std::is_same_v<from_uq, EmuSIMD::i32x16>)
				{
					return EmuSIMD::_underlying_simd_helpers::_cast_i32x16<ToRegister_>(std::forward<FromRegister_>(from_));
				}
				else if constexpr (std::is_same_v<from_uq, EmuSIMD::i64x2>)
				{
					return EmuSIMD::_underlying_simd_helpers::_cast_i64x2<ToRegister_>(std::forward<FromRegister_>(from_));
				}
				else if constexpr (std::is_same_v<from_uq, EmuSIMD::i64x4>)
				{
					return EmuSIMD::_underlying_simd_helpers::_cast_i64x4<ToRegister_>(std::forward<FromRegister_>(from_));
				}
				else if constexpr (std::is_same_v<from_uq, EmuSIMD::i64x8>)
				{
					return EmuSIMD::_underlying_simd_helpers::_cast_i64x8<ToRegister_>(std::forward<FromRegister_>(from_));
				}
				else if constexpr (std::is_same_v<from_uq, EmuSIMD::u8x16>)
				{
					return EmuSIMD::_underlying_simd_helpers::_cast_u8x16<ToRegister_>(std::forward<FromRegister_>(from_));
				}
				else if constexpr (std::is_same_v<from_uq, EmuSIMD::u8x32>)
				{
					return EmuSIMD::_underlying_simd_helpers::_cast_u8x32<ToRegister_>(std::forward<FromRegister_>(from_));
				}
				else if constexpr (std::is_same_v<from_uq, EmuSIMD::u8x64>)
				{
					return EmuSIMD::_underlying_simd_helpers::_cast_u8x64<ToRegister_>(std::forward<FromRegister_>(from_));
				}
				else if constexpr (std::is_same_v<from_uq, EmuSIMD::u16x8>)
				{
					return EmuSIMD::_underlying_simd_helpers::_cast_u16x8<ToRegister_>(std::forward<FromRegister_>(from_));
				}
				else if constexpr (std::is_same_v<from_uq, EmuSIMD::u16x16>)
				{
					return EmuSIMD::_underlying_simd_helpers::_cast_u16x16<ToRegister_>(std::forward<FromRegister_>(from_));
				}
				else if constexpr (std::is_same_v<from_uq, EmuSIMD::u16x32>)
				{
					return EmuSIMD::_underlying_simd_helpers::_cast_u16x32<ToRegister_>(std::forward<FromRegister_>(from_));
				}
				else if constexpr (std::is_same_v<from_uq, EmuSIMD::u32x4>)
				{
					return EmuSIMD::_underlying_simd_helpers::_cast_u32x4<ToRegister_>(std::forward<FromRegister_>(from_));
				}
				else if constexpr (std::is_same_v<from_uq, EmuSIMD::u32x8>)
				{
					return EmuSIMD::_underlying_simd_helpers::_cast_u32x8<ToRegister_>(std::forward<FromRegister_>(from_));
				}
				else if constexpr (std::is_same_v<from_uq, EmuSIMD::u32x16>)
				{
					return EmuSIMD::_underlying_simd_helpers::_cast_u32x16<ToRegister_>(std::forward<FromRegister_>(from_));
				}
				else if constexpr (std::is_same_v<from_uq, EmuSIMD::u64x2>)
				{
					return EmuSIMD::_underlying_simd_helpers::_cast_u64x2<ToRegister_>(std::forward<FromRegister_>(from_));
				}
				else if constexpr (std::is_same_v<from_uq, EmuSIMD::u64x4>)
				{
					return EmuSIMD::_underlying_simd_helpers::_cast_u64x4<ToRegister_>(std::forward<FromRegister_>(from_));
				}
				else if constexpr (std::is_same_v<from_uq, EmuSIMD::u64x8>)
				{
					return EmuSIMD::_underlying_simd_helpers::_cast_u64x8<ToRegister_>(std::forward<FromRegister_>(from_));
				}
				else
				{
					static_assert(EmuCore::TMP::get_false<ToRegister_>(), "Attempted to cast a SIMD register via EmuSIMD helpers, but the provided SIMD register to cast from is not supported for this operation.");
				}
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<ToRegister_>(), "Attempted to perform EmuSIMD::cast, but the provided ToRegister_ (the output type) is not recognised as a supported SIMD register.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<ToRegister_>(), "Attempted to perform EmuSIMD::cast, but the provided FromRegister_ (the input type) is not recognised as a supported SIMD register.");
		}
	}
}

#endif
