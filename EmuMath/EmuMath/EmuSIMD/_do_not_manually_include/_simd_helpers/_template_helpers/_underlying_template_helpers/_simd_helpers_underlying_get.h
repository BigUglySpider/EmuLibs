#ifndef EMU_SIMD_HELPERS_UNDERLYING_GET_H_INC_
#define EMU_SIMD_HELPERS_UNDERLYING_GET_H_INC_ 1

#include "_common_underlying_simd_template_helper_includes.h"
#include "_simd_helpers_underlying_shuffle.h"
#include "../../../../../EmuCore/TMPHelpers/Values.h"

namespace EmuSIMD::_underlying_simd_helpers
{
	template<std::size_t PerElementWidthIfGenericInt_, EmuConcepts::KnownSIMD Register_>
	[[nodiscard]] inline decltype(auto) _movemask(Register_&& register_)
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x4>)
			{
				return EmuSIMD::Funcs::movemask_f32x4(std::forward<Register_>(register_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x2>)
			{
				return EmuSIMD::Funcs::movemask_f64x2(std::forward<Register_>(register_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x8>)
			{
				return EmuSIMD::Funcs::movemask_f32x8(std::forward<Register_>(register_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x4>)
			{
				return EmuSIMD::Funcs::movemask_f64x4(std::forward<Register_>(register_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x16>)
			{
				return EmuSIMD::Funcs::movemask_f32x16(std::forward<Register_>(register_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x8>)
			{
				return EmuSIMD::Funcs::movemask_f64x8(std::forward<Register_>(register_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i128_generic>)
			{
				if constexpr (PerElementWidthIfGenericInt_ == 8)
				{
					return EmuSIMD::Funcs::movemask_i8x16(std::forward<Register_>(register_));
				}
				else if constexpr (PerElementWidthIfGenericInt_ == 16)
				{
					return EmuSIMD::Funcs::movemask_i16x8(std::forward<Register_>(register_));
				}
				else if constexpr (PerElementWidthIfGenericInt_ == 32)
				{
					return EmuSIMD::Funcs::movemask_i32x4(std::forward<Register_>(register_));
				}
				else if constexpr (PerElementWidthIfGenericInt_ == 64)
				{
					return EmuSIMD::Funcs::movemask_i64x2(std::forward<Register_>(register_));
				}
				else
				{
					static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to retrieve a movemask from a generic 128-bit integral SIMD register via an EmuSIMD helper, but the provided per-element width is invalid.");
				}
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i256_generic>)
			{
				if constexpr (PerElementWidthIfGenericInt_ == 8)
				{
					return EmuSIMD::Funcs::movemask_i8x32(std::forward<Register_>(register_));
				}
				else if constexpr (PerElementWidthIfGenericInt_ == 16)
				{
					return EmuSIMD::Funcs::movemask_i16x16(std::forward<Register_>(register_));
				}
				else if constexpr (PerElementWidthIfGenericInt_ == 32)
				{
					return EmuSIMD::Funcs::movemask_i32x8(std::forward<Register_>(register_));
				}
				else if constexpr (PerElementWidthIfGenericInt_ == 64)
				{
					return EmuSIMD::Funcs::movemask_i64x4(std::forward<Register_>(register_));
				}
				else
				{
					static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to retrieve a movemask from a generic 256-bit integral SIMD register via an EmuSIMD helper, but the provided per-element width is invalid.");
				}
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i512_generic>)
			{
				if constexpr (PerElementWidthIfGenericInt_ == 8)
				{
					return EmuSIMD::Funcs::movemask_i8x64(std::forward<Register_>(register_));
				}
				else if constexpr (PerElementWidthIfGenericInt_ == 16)
				{
					return EmuSIMD::Funcs::movemask_i16x32(std::forward<Register_>(register_));
				}
				else if constexpr (PerElementWidthIfGenericInt_ == 32)
				{
					return EmuSIMD::Funcs::movemask_i32x16(std::forward<Register_>(register_));
				}
				else if constexpr (PerElementWidthIfGenericInt_ == 64)
				{
					return EmuSIMD::Funcs::movemask_i64x8(std::forward<Register_>(register_));
				}
				else
				{
					static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to retrieve a movemask from a generic 512-bit integral SIMD register via an EmuSIMD helper, but the provided per-element width is invalid.");
				}
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i8x16>)
			{
				return EmuSIMD::Funcs::movemask_i8x16(std::forward<Register_>(register_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i8x32>)
			{
				return EmuSIMD::Funcs::movemask_i8x32(std::forward<Register_>(register_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i8x64>)
			{
				return EmuSIMD::Funcs::movemask_i8x64(std::forward<Register_>(register_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i16x8>)
			{
				return EmuSIMD::Funcs::movemask_i16x8(std::forward<Register_>(register_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i16x16>)
			{
				return EmuSIMD::Funcs::movemask_i16x16(std::forward<Register_>(register_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i16x32>)
			{
				return EmuSIMD::Funcs::movemask_i16x32(std::forward<Register_>(register_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i32x4>)
			{
				return EmuSIMD::Funcs::movemask_i32x4(std::forward<Register_>(register_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i32x8>)
			{
				return EmuSIMD::Funcs::movemask_i32x8(std::forward<Register_>(register_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i32x16>)
			{
				return EmuSIMD::Funcs::movemask_i32x16(std::forward<Register_>(register_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i64x2>)
			{
				return EmuSIMD::Funcs::movemask_i64x2(std::forward<Register_>(register_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i64x4>)
			{
				return EmuSIMD::Funcs::movemask_i64x4(std::forward<Register_>(register_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i64x8>)
			{
				return EmuSIMD::Funcs::movemask_i64x8(std::forward<Register_>(register_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u8x16>)
			{
				return EmuSIMD::Funcs::movemask_u8x16(std::forward<Register_>(register_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u8x32>)
			{
				return EmuSIMD::Funcs::movemask_u8x32(std::forward<Register_>(register_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u8x64>)
			{
				return EmuSIMD::Funcs::movemask_u8x64(std::forward<Register_>(register_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u16x8>)
			{
				return EmuSIMD::Funcs::movemask_u16x8(std::forward<Register_>(register_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u16x16>)
			{
				return EmuSIMD::Funcs::movemask_u16x16(std::forward<Register_>(register_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u16x32>)
			{
				return EmuSIMD::Funcs::movemask_u16x32(std::forward<Register_>(register_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u32x4>)
			{
				return EmuSIMD::Funcs::movemask_u32x4(std::forward<Register_>(register_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u32x8>)
			{
				return EmuSIMD::Funcs::movemask_u32x8(std::forward<Register_>(register_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u32x16>)
			{
				return EmuSIMD::Funcs::movemask_u32x16(std::forward<Register_>(register_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u64x2>)
			{
				return EmuSIMD::Funcs::movemask_u64x2(std::forward<Register_>(register_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u64x4>)
			{
				return EmuSIMD::Funcs::movemask_u64x4(std::forward<Register_>(register_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u64x8>)
			{
				return EmuSIMD::Funcs::movemask_u64x8(std::forward<Register_>(register_));
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to retrieve a movemask from a SIMD register via an EmuSIMD helper, but the provided register_ could not be recognised.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to retrieve a movemask from a SIMD register via an EmuSIMD helper, but the provided register_ was not a supported SIMD register.");
		}
	}

	template<std::size_t Index_, typename OutT_, std::size_t PerElementWidthIfGenericInt_ = 32, class SIMDRegister_>
	[[nodiscard]] inline auto _get_register_index(SIMDRegister_&& register_)
		-> typename std::remove_cvref<OutT_>::type
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<SIMDRegister_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x4>)
			{
				return EmuSIMD::Funcs::extract_element_f32x4<Index_, OutT_>(std::forward<SIMDRegister_>(register_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x8>)
			{
				return EmuSIMD::Funcs::extract_element_f32x8<Index_, OutT_>(std::forward<SIMDRegister_>(register_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x16>)
			{
				return EmuSIMD::Funcs::extract_element_f32x16<Index_, OutT_>(std::forward<SIMDRegister_>(register_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x2>)
			{
				return EmuSIMD::Funcs::extract_element_f64x2<Index_, OutT_>(std::forward<SIMDRegister_>(register_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x4>)
			{
				return EmuSIMD::Funcs::extract_element_f64x4<Index_, OutT_>(std::forward<SIMDRegister_>(register_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x8>)
			{
				return EmuSIMD::Funcs::extract_element_f64x8<Index_, OutT_>(std::forward<SIMDRegister_>(register_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i128_generic>)
			{
				if constexpr (PerElementWidthIfGenericInt_ == 8)
				{
					return EmuSIMD::Funcs::extract_element_i8x16<Index_, OutT_>(std::forward<SIMDRegister_>(register_));
				}
				else if constexpr (PerElementWidthIfGenericInt_ == 16)
				{
					return EmuSIMD::Funcs::extract_element_i16x8<Index_, OutT_>(std::forward<SIMDRegister_>(register_));
				}
				else if constexpr (PerElementWidthIfGenericInt_ == 32)
				{
					return EmuSIMD::Funcs::extract_element_i32x4<Index_, OutT_>(std::forward<SIMDRegister_>(register_));
				}
				else if constexpr (PerElementWidthIfGenericInt_ == 64)
				{
					return EmuSIMD::Funcs::extract_element_i64x2<Index_, OutT_>(std::forward<SIMDRegister_>(register_));
				}
				else
				{
					static_assert(EmuCore::TMP::get_false<std::size_t, PerElementWidthIfGenericInt_>(), "Invalid PerElementWidthIfGenericInt_ passed when retrieving an element at a specified index of a 128-bit generic integral SIMD register. Valid values are 8, 16, 32, 64.");
				}
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i256_generic>)
			{
				if constexpr (PerElementWidthIfGenericInt_ == 8)
				{
					return EmuSIMD::Funcs::extract_element_i8x32<Index_, OutT_>(std::forward<SIMDRegister_>(register_));
				}
				else if constexpr (PerElementWidthIfGenericInt_ == 16)
				{
					return EmuSIMD::Funcs::extract_element_i16x16<Index_, OutT_>(std::forward<SIMDRegister_>(register_));
				}
				else if constexpr (PerElementWidthIfGenericInt_ == 32)
				{
					return EmuSIMD::Funcs::extract_element_i32x8<Index_, OutT_>(std::forward<SIMDRegister_>(register_));
				}
				else if constexpr (PerElementWidthIfGenericInt_ == 64)
				{
					return EmuSIMD::Funcs::extract_element_i64x4<Index_, OutT_>(std::forward<SIMDRegister_>(register_));
				}
				else
				{
					static_assert(EmuCore::TMP::get_false<std::size_t, PerElementWidthIfGenericInt_>(), "Invalid PerElementWidthIfGenericInt_ passed when retrieving an element at a specified index of a 256-bit generic integral SIMD register. Valid values are 8, 16, 32, 64.");
				}
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i512_generic>)
			{
				if constexpr (PerElementWidthIfGenericInt_ == 8)
				{
					return EmuSIMD::Funcs::extract_element_i8x64<Index_, OutT_>(std::forward<SIMDRegister_>(register_));
				}
				else if constexpr (PerElementWidthIfGenericInt_ == 16)
				{
					return EmuSIMD::Funcs::extract_element_i16x32<Index_, OutT_>(std::forward<SIMDRegister_>(register_));
				}
				else if constexpr (PerElementWidthIfGenericInt_ == 32)
				{
					return EmuSIMD::Funcs::extract_element_i32x16<Index_, OutT_>(std::forward<SIMDRegister_>(register_));
				}
				else if constexpr (PerElementWidthIfGenericInt_ == 64)
				{
					return EmuSIMD::Funcs::extract_element_i64x8<Index_, OutT_>(std::forward<SIMDRegister_>(register_));
				}
				else
				{
					static_assert(EmuCore::TMP::get_false<std::size_t, PerElementWidthIfGenericInt_>(), "Invalid PerElementWidthIfGenericInt_ passed when retrieving an element at a specified index of a 512-bit generic integral SIMD register. Valid values are 8, 16, 32, 64.");
				}
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i8x16>)
			{
				return EmuSIMD::Funcs::extract_element_i8x16<Index_, OutT_>(std::forward<SIMDRegister_>(register_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i16x8>)
			{
				return EmuSIMD::Funcs::extract_element_i16x8<Index_, OutT_>(std::forward<SIMDRegister_>(register_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i32x4>)
			{
				return EmuSIMD::Funcs::extract_element_i32x4<Index_, OutT_>(std::forward<SIMDRegister_>(register_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i64x2>)
			{
				return EmuSIMD::Funcs::extract_element_i64x2<Index_, OutT_>(std::forward<SIMDRegister_>(register_));
			}			
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i8x32>)
			{
				return EmuSIMD::Funcs::extract_element_i8x32<Index_, OutT_>(std::forward<SIMDRegister_>(register_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i16x16>)
			{
				return EmuSIMD::Funcs::extract_element_i16x16<Index_, OutT_>(std::forward<SIMDRegister_>(register_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i32x8>)
			{
				return EmuSIMD::Funcs::extract_element_i32x8<Index_, OutT_>(std::forward<SIMDRegister_>(register_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i64x4>)
			{
				return EmuSIMD::Funcs::extract_element_i64x4<Index_, OutT_>(std::forward<SIMDRegister_>(register_));
			}			
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i8x64>)
			{
				return EmuSIMD::Funcs::extract_element_i8x64<Index_, OutT_>(std::forward<SIMDRegister_>(register_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i16x32>)
			{
				return EmuSIMD::Funcs::extract_element_i16x32<Index_, OutT_>(std::forward<SIMDRegister_>(register_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i32x16>)
			{
				return EmuSIMD::Funcs::extract_element_i32x16<Index_, OutT_>(std::forward<SIMDRegister_>(register_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i64x8>)
			{
				return EmuSIMD::Funcs::extract_element_i64x8<Index_, OutT_>(std::forward<SIMDRegister_>(register_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u8x16>)
			{
				return EmuSIMD::Funcs::extract_element_u8x16<Index_, OutT_>(std::forward<SIMDRegister_>(register_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u16x8>)
			{
				return EmuSIMD::Funcs::extract_element_u16x8<Index_, OutT_>(std::forward<SIMDRegister_>(register_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u32x4>)
			{
				return EmuSIMD::Funcs::extract_element_u32x4<Index_, OutT_>(std::forward<SIMDRegister_>(register_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u64x2>)
			{
				return EmuSIMD::Funcs::extract_element_u64x2<Index_, OutT_>(std::forward<SIMDRegister_>(register_));
			}			
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u8x32>)
			{
				return EmuSIMD::Funcs::extract_element_u8x32<Index_, OutT_>(std::forward<SIMDRegister_>(register_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u16x16>)
			{
				return EmuSIMD::Funcs::extract_element_u16x16<Index_, OutT_>(std::forward<SIMDRegister_>(register_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u32x8>)
			{
				return EmuSIMD::Funcs::extract_element_u32x8<Index_, OutT_>(std::forward<SIMDRegister_>(register_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u64x4>)
			{
				return EmuSIMD::Funcs::extract_element_u64x4<Index_, OutT_>(std::forward<SIMDRegister_>(register_));
			}			
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u8x64>)
			{
				return EmuSIMD::Funcs::extract_element_u8x64<Index_, OutT_>(std::forward<SIMDRegister_>(register_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u16x32>)
			{
				return EmuSIMD::Funcs::extract_element_u16x32<Index_, OutT_>(std::forward<SIMDRegister_>(register_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u32x16>)
			{
				return EmuSIMD::Funcs::extract_element_u32x16<Index_, OutT_>(std::forward<SIMDRegister_>(register_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u64x8>)
			{
				return EmuSIMD::Funcs::extract_element_u64x8<Index_, OutT_>(std::forward<SIMDRegister_>(register_));
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<SIMDRegister_>(), "Attempted to extract an index from a SIMD register using EmuSIMD helpers, but the provided SIMD register is not supported for this operation.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<SIMDRegister_>(), "Attempted to extract an index from a SIMD register using EmuSIMD helpers, but the provided register is not a supported SIMD register type.");
		}
	}

	template<typename Out_, class Register_, typename NoConstReq_ = std::enable_if_t<!std::is_const_v<Out_>>>
	inline void _store_register(Register_ register_, Out_* p_out_)
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x4>)
			{
				EmuSIMD::Funcs::store_f32x4(reinterpret_cast<float*>(p_out_), register_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x2>)
			{
				EmuSIMD::Funcs::store_f64x2(reinterpret_cast<double*>(p_out_), register_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x8>)
			{
				EmuSIMD::Funcs::store_f32x8(reinterpret_cast<float*>(p_out_), register_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x4>)
			{
				EmuSIMD::Funcs::store_f64x4(reinterpret_cast<double*>(p_out_), register_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x16>)
			{
				EmuSIMD::Funcs::store_f32x16(reinterpret_cast<float*>(p_out_), register_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x8>)
			{
				EmuSIMD::Funcs::store_f64x8(reinterpret_cast<double*>(p_out_), register_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i128_generic>)
			{
				EmuSIMD::Funcs::store_i8x16(reinterpret_cast<std::int8_t*>(p_out_), register_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i256_generic>)
			{
				EmuSIMD::Funcs::store_i8x32(reinterpret_cast<std::int8_t*>(p_out_), register_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i512_generic>)
			{
				EmuSIMD::Funcs::store_i8x64(reinterpret_cast<std::int8_t*>(p_out_), register_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i8x16>)
			{
				EmuSIMD::Funcs::store_i8x16(reinterpret_cast<std::int8_t*>(p_out_), register_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i8x32>)
			{
				EmuSIMD::Funcs::store_i8x32(reinterpret_cast<std::int8_t*>(p_out_), register_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i8x64>)
			{
				EmuSIMD::Funcs::store_i8x64(reinterpret_cast<std::int8_t*>(p_out_), register_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i16x8>)
			{
				EmuSIMD::Funcs::store_i16x8(reinterpret_cast<std::int16_t*>(p_out_), register_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i16x16>)
			{
				EmuSIMD::Funcs::store_i16x16(reinterpret_cast<std::int16_t*>(p_out_), register_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i16x32>)
			{
				EmuSIMD::Funcs::store_i16x32(reinterpret_cast<std::int16_t*>(p_out_), register_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i32x4>)
			{
				EmuSIMD::Funcs::store_i32x4(reinterpret_cast<std::int32_t*>(p_out_), register_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i32x8>)
			{
				EmuSIMD::Funcs::store_i32x8(reinterpret_cast<std::int32_t*>(p_out_), register_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i32x16>)
			{
				EmuSIMD::Funcs::store_i32x16(reinterpret_cast<std::int32_t*>(p_out_), register_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i64x2>)
			{
				EmuSIMD::Funcs::store_i64x2(reinterpret_cast<std::int64_t*>(p_out_), register_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i64x4>)
			{
				EmuSIMD::Funcs::store_i64x4(reinterpret_cast<std::int64_t*>(p_out_), register_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i64x8>)
			{
				EmuSIMD::Funcs::store_i64x8(reinterpret_cast<std::int64_t*>(p_out_), register_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u8x16>)
			{
				EmuSIMD::Funcs::store_u8x16(reinterpret_cast<std::uint8_t*>(p_out_), register_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u8x32>)
			{
				EmuSIMD::Funcs::store_u8x32(reinterpret_cast<std::uint8_t*>(p_out_), register_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u8x64>)
			{
				EmuSIMD::Funcs::store_u8x64(reinterpret_cast<std::uint8_t*>(p_out_), register_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u16x8>)
			{
				EmuSIMD::Funcs::store_u16x8(reinterpret_cast<std::uint16_t*>(p_out_), register_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u16x16>)
			{
				EmuSIMD::Funcs::store_u16x16(reinterpret_cast<std::uint16_t*>(p_out_), register_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u16x32>)
			{
				EmuSIMD::Funcs::store_u16x32(reinterpret_cast<std::uint16_t*>(p_out_), register_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u32x4>)
			{
				EmuSIMD::Funcs::store_u32x4(reinterpret_cast<std::uint32_t*>(p_out_), register_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u32x8>)
			{
				EmuSIMD::Funcs::store_u32x8(reinterpret_cast<std::uint32_t*>(p_out_), register_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u32x16>)
			{
				EmuSIMD::Funcs::store_u32x16(reinterpret_cast<std::uint32_t*>(p_out_), register_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u64x2>)
			{
				EmuSIMD::Funcs::store_u64x2(reinterpret_cast<std::uint64_t*>(p_out_), register_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u64x4>)
			{
				EmuSIMD::Funcs::store_u64x4(reinterpret_cast<std::uint64_t*>(p_out_), register_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u64x8>)
			{
				EmuSIMD::Funcs::store_u64x8(reinterpret_cast<std::uint64_t*>(p_out_), register_);
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to store a SIMD register to a pointer via an EmuSIMD helper, but the provided register_ could not be recognised.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to store a SIMD register to a pointer via an EmuSIMD helper, but the provided register_ was not a supported SIMD register.");
		}
	}

	template<typename Out_, class Register_, typename NoConstReq_ = std::enable_if_t<!std::is_const_v<Out_>>>
	inline void _aligned_store_register(Register_ register_, Out_* p_out_)
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x4>)
			{
				EmuSIMD::Funcs::aligned_store_f32x4(reinterpret_cast<float*>(p_out_), register_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x2>)
			{
				EmuSIMD::Funcs::aligned_store_f64x2(reinterpret_cast<double*>(p_out_), register_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x8>)
			{
				EmuSIMD::Funcs::aligned_store_f32x8(reinterpret_cast<float*>(p_out_), register_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x4>)
			{
				EmuSIMD::Funcs::aligned_store_f64x4(reinterpret_cast<double*>(p_out_), register_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x16>)
			{
				EmuSIMD::Funcs::aligned_store_f32x16(reinterpret_cast<void*>(p_out_), register_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x8>)
			{
				EmuSIMD::Funcs::aligned_store_f64x8(reinterpret_cast<void*>(p_out_), register_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i128_generic>)
			{
				EmuSIMD::Funcs::aligned_store_i8x16(reinterpret_cast<std::int8_t*>(p_out_), register_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i256_generic>)
			{
				EmuSIMD::Funcs::aligned_store_i8x32(reinterpret_cast<std::int8_t*>(p_out_), register_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i512_generic>)
			{
				EmuSIMD::Funcs::aligned_store_i8x64(reinterpret_cast<std::int8_t*>(p_out_), register_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i8x16>)
			{
				EmuSIMD::Funcs::aligned_store_i8x16(reinterpret_cast<std::int8_t*>(p_out_), register_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i8x32>)
			{
				EmuSIMD::Funcs::aligned_store_i8x32(reinterpret_cast<std::int8_t*>(p_out_), register_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i8x64>)
			{
				EmuSIMD::Funcs::aligned_store_i8x64(reinterpret_cast<std::int8_t*>(p_out_), register_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i16x8>)
			{
				EmuSIMD::Funcs::aligned_store_i16x8(reinterpret_cast<std::int16_t*>(p_out_), register_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i16x16>)
			{
				EmuSIMD::Funcs::aligned_store_i16x16(reinterpret_cast<std::int16_t*>(p_out_), register_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i16x32>)
			{
				EmuSIMD::Funcs::aligned_store_i16x32(reinterpret_cast<std::int16_t*>(p_out_), register_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i32x4>)
			{
				EmuSIMD::Funcs::aligned_store_i32x4(reinterpret_cast<std::int32_t*>(p_out_), register_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i32x8>)
			{
				EmuSIMD::Funcs::aligned_store_i32x8(reinterpret_cast<std::int32_t*>(p_out_), register_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i32x16>)
			{
				EmuSIMD::Funcs::aligned_store_i32x16(reinterpret_cast<std::int32_t*>(p_out_), register_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i64x2>)
			{
				EmuSIMD::Funcs::aligned_store_i64x2(reinterpret_cast<std::int64_t*>(p_out_), register_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i64x4>)
			{
				EmuSIMD::Funcs::aligned_store_i64x4(reinterpret_cast<std::int64_t*>(p_out_), register_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i64x8>)
			{
				EmuSIMD::Funcs::aligned_store_i64x8(reinterpret_cast<std::int64_t*>(p_out_), register_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u8x16>)
			{
				EmuSIMD::Funcs::aligned_store_u8x16(reinterpret_cast<std::uint8_t*>(p_out_), register_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u8x32>)
			{
				EmuSIMD::Funcs::aligned_store_u8x32(reinterpret_cast<std::uint8_t*>(p_out_), register_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u8x64>)
			{
				EmuSIMD::Funcs::aligned_store_u8x64(reinterpret_cast<std::uint8_t*>(p_out_), register_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u16x8>)
			{
				EmuSIMD::Funcs::aligned_store_u16x8(reinterpret_cast<std::uint16_t*>(p_out_), register_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u16x16>)
			{
				EmuSIMD::Funcs::aligned_store_u16x16(reinterpret_cast<std::uint16_t*>(p_out_), register_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u16x32>)
			{
				EmuSIMD::Funcs::aligned_store_u16x32(reinterpret_cast<std::uint16_t*>(p_out_), register_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u32x4>)
			{
				EmuSIMD::Funcs::aligned_store_u32x4(reinterpret_cast<std::uint32_t*>(p_out_), register_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u32x8>)
			{
				EmuSIMD::Funcs::aligned_store_u32x8(reinterpret_cast<std::uint32_t*>(p_out_), register_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u32x16>)
			{
				EmuSIMD::Funcs::aligned_store_u32x16(reinterpret_cast<std::uint32_t*>(p_out_), register_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u64x2>)
			{
				EmuSIMD::Funcs::aligned_store_u64x2(reinterpret_cast<std::uint64_t*>(p_out_), register_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u64x4>)
			{
				EmuSIMD::Funcs::aligned_store_u64x4(reinterpret_cast<std::uint64_t*>(p_out_), register_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u64x8>)
			{
				EmuSIMD::Funcs::aligned_store_u64x8(reinterpret_cast<std::uint64_t*>(p_out_), register_);
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to aligned-store a SIMD register to a pointer via an EmuSIMD helper, but the provided register_ could not be recognised.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to aligned-store a SIMD register to a pointer via an EmuSIMD helper, but the provided register_ was not a supported SIMD register.");
		}
	}

	template<std::size_t LaneIndex_, class In_>
	[[nodiscard]] constexpr inline EmuSIMD::f32x4 _extract_lane_f32x4_prevalidated(In_&& in_)
	{
		using in_uq = typename EmuCore::TMP::remove_ref_cv<In_>::type;
		if constexpr (std::is_same_v<in_uq, EmuSIMD::f32x4>)
		{
			return EmuSIMD::Funcs::extract_f32x4_lane_f32x4<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::f32x8>)
		{
			return EmuSIMD::Funcs::extract_f32x8_lane_f32x4<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::f32x16>)
		{
			return EmuSIMD::Funcs::extract_f32x16_lane_f32x4<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::f64x2>)
		{
			return EmuSIMD::Funcs::extract_f64x2_lane_f32x4<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::f64x4>)
		{
			return EmuSIMD::Funcs::extract_f64x4_lane_f32x4<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::f64x8>)
		{
			return EmuSIMD::Funcs::extract_f64x8_lane_f32x4<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i128_generic>)
		{
			return EmuSIMD::Funcs::extract_i32x4_lane_f32x4<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i256_generic>)
		{
			return EmuSIMD::Funcs::extract_i32x8_lane_f32x4<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i512_generic>)
		{
			return EmuSIMD::Funcs::extract_i32x16_lane_f32x4<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i8x16>)
		{
			return EmuSIMD::Funcs::extract_i8x16_lane_f32x4<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i16x8>)
		{
			return EmuSIMD::Funcs::extract_i16x8_lane_f32x4<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i32x4>)
		{
			return EmuSIMD::Funcs::extract_i32x4_lane_f32x4<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i64x2>)
		{
			return EmuSIMD::Funcs::extract_i64x2_lane_f32x4<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i8x32>)
		{
			return EmuSIMD::Funcs::extract_i8x32_lane_f32x4<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i16x16>)
		{
			return EmuSIMD::Funcs::extract_i16x16_lane_f32x4<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i32x8>)
		{
			return EmuSIMD::Funcs::extract_i32x8_lane_f32x4<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i64x4>)
		{
			return EmuSIMD::Funcs::extract_i64x4_lane_f32x4<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i8x64>)
		{
			return EmuSIMD::Funcs::extract_i8x64_lane_f32x4<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i16x32>)
		{
			return EmuSIMD::Funcs::extract_i16x32_lane_f32x4<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i32x16>)
		{
			return EmuSIMD::Funcs::extract_i32x16_lane_f32x4<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i64x8>)
		{
			return EmuSIMD::Funcs::extract_i64x8_lane_f32x4<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u8x16>)
		{
			return EmuSIMD::Funcs::extract_u8x16_lane_f32x4<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u16x8>)
		{
			return EmuSIMD::Funcs::extract_u16x8_lane_f32x4<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u32x4>)
		{
			return EmuSIMD::Funcs::extract_u32x4_lane_f32x4<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u64x2>)
		{
			return EmuSIMD::Funcs::extract_u64x2_lane_f32x4<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u8x32>)
		{
			return EmuSIMD::Funcs::extract_u8x32_lane_f32x4<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u16x16>)
		{
			return EmuSIMD::Funcs::extract_u16x16_lane_f32x4<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u32x8>)
		{
			return EmuSIMD::Funcs::extract_u32x8_lane_f32x4<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u64x4>)
		{
			return EmuSIMD::Funcs::extract_u64x4_lane_f32x4<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u8x64>)
		{
			return EmuSIMD::Funcs::extract_u8x64_lane_f32x4<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u16x32>)
		{
			return EmuSIMD::Funcs::extract_u16x32_lane_f32x4<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u32x16>)
		{
			return EmuSIMD::Funcs::extract_u32x16_lane_f32x4<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u64x8>)
		{
			return EmuSIMD::Funcs::extract_u64x8_lane_f32x4<LaneIndex_>(in_);
		}
		else
		{
			static_assert
			(
				EmuCore::TMP::get_false<in_uq>(),
				"Attempted to extract a lane from a SIMD register as a f32x4 register via EmuSIMD helpers, but the provided input register is not supported for such an extraction."
			);
		}
	}

	template<std::size_t LaneIndex_, class In_>
	[[nodiscard]] constexpr inline EmuSIMD::f32x8 _extract_lane_f32x8_prevalidated(In_&& in_)
	{
		using in_uq = typename EmuCore::TMP::remove_ref_cv<In_>::type;
		if constexpr (std::is_same_v<in_uq, EmuSIMD::f32x8>)
		{
			return EmuSIMD::Funcs::extract_f32x8_lane_f32x8<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::f32x16>)
		{
			return EmuSIMD::Funcs::extract_f32x16_lane_f32x8<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::f64x4>)
		{
			return EmuSIMD::Funcs::extract_f64x4_lane_f32x8<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::f64x8>)
		{
			return EmuSIMD::Funcs::extract_f64x8_lane_f32x8<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i256_generic>)
		{
			return EmuSIMD::Funcs::extract_i32x8_lane_f32x8<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i512_generic>)
		{
			return EmuSIMD::Funcs::extract_i32x16_lane_f32x8<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i8x32>)
		{
			return EmuSIMD::Funcs::extract_i8x32_lane_f32x8<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i16x16>)
		{
			return EmuSIMD::Funcs::extract_i16x16_lane_f32x8<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i32x8>)
		{
			return EmuSIMD::Funcs::extract_i32x8_lane_f32x8<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i64x4>)
		{
			return EmuSIMD::Funcs::extract_i64x4_lane_f32x8<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i8x64>)
		{
			return EmuSIMD::Funcs::extract_i8x64_lane_f32x8<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i16x32>)
		{
			return EmuSIMD::Funcs::extract_i16x32_lane_f32x8<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i32x16>)
		{
			return EmuSIMD::Funcs::extract_i32x16_lane_f32x8<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i64x8>)
		{
			return EmuSIMD::Funcs::extract_i64x8_lane_f32x8<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u8x32>)
		{
			return EmuSIMD::Funcs::extract_u8x32_lane_f32x8<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u16x16>)
		{
			return EmuSIMD::Funcs::extract_u16x16_lane_f32x8<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u32x8>)
		{
			return EmuSIMD::Funcs::extract_u32x8_lane_f32x8<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u64x4>)
		{
			return EmuSIMD::Funcs::extract_u64x4_lane_f32x8<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u8x64>)
		{
			return EmuSIMD::Funcs::extract_u8x64_lane_f32x8<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u16x32>)
		{
			return EmuSIMD::Funcs::extract_u16x32_lane_f32x8<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u32x16>)
		{
			return EmuSIMD::Funcs::extract_u32x16_lane_f32x8<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u64x8>)
		{
			return EmuSIMD::Funcs::extract_u64x8_lane_f32x8<LaneIndex_>(std::forward<In_>(in_));
		}
		else
		{
			static_assert
			(
				EmuCore::TMP::get_false<in_uq>(),
				"Attempted to extract a lane from a SIMD register as a f32x8 register via EmuSIMD helpers, but the provided input register is not supported for such an extraction."
			);
		}
	}

	template<std::size_t LaneIndex_, class In_>
	[[nodiscard]] constexpr inline EmuSIMD::f32x16 _extract_lane_f32x16_prevalidated(In_&& in_)
	{
		using in_uq = typename EmuCore::TMP::remove_ref_cv<In_>::type;
		if constexpr (std::is_same_v<in_uq, EmuSIMD::f32x16>)
		{
			return EmuSIMD::Funcs::extract_f32x16_lane_f32x16<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::f64x8>)
		{
			return EmuSIMD::Funcs::extract_f64x8_lane_f32x16<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i512_generic>)
		{
			return EmuSIMD::Funcs::extract_i32x16_lane_f32x16<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i8x64>)
		{
			return EmuSIMD::Funcs::extract_i8x64_lane_f32x16<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i16x32>)
		{
			return EmuSIMD::Funcs::extract_i16x32_lane_f32x16<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i32x16>)
		{
			return EmuSIMD::Funcs::extract_i32x16_lane_f32x16<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i64x8>)
		{
			return EmuSIMD::Funcs::extract_i64x8_lane_f32x16<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u8x64>)
		{
			return EmuSIMD::Funcs::extract_u8x64_lane_f32x16<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u16x32>)
		{
			return EmuSIMD::Funcs::extract_u16x32_lane_f32x16<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u32x16>)
		{
			return EmuSIMD::Funcs::extract_u32x16_lane_f32x16<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u64x8>)
		{
			return EmuSIMD::Funcs::extract_u64x8_lane_f32x16<LaneIndex_>(std::forward<In_>(in_));
		}
		else
		{
			static_assert
			(
				EmuCore::TMP::get_false<in_uq>(),
				"Attempted to extract a lane from a SIMD register as a f32x16 register via EmuSIMD helpers, but the provided input register is not supported for such an extraction."
			);
		}
	}

	template<std::size_t LaneIndex_, class In_>
	[[nodiscard]] constexpr inline EmuSIMD::f64x2 _extract_lane_f64x2_prevalidated(In_&& in_)
	{
		using in_uq = typename EmuCore::TMP::remove_ref_cv<In_>::type;
		if constexpr (std::is_same_v<in_uq, EmuSIMD::f32x4>)
		{
			return EmuSIMD::Funcs::extract_f32x4_lane_f64x2<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::f32x8>)
		{
			return EmuSIMD::Funcs::extract_f32x8_lane_f64x2<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::f32x16>)
		{
			return EmuSIMD::Funcs::extract_f32x16_lane_f64x2<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::f64x2>)
		{
			return EmuSIMD::Funcs::extract_f64x2_lane_f64x2<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::f64x4>)
		{
			return EmuSIMD::Funcs::extract_f64x4_lane_f64x2<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::f64x8>)
		{
			return EmuSIMD::Funcs::extract_f64x8_lane_f64x2<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i128_generic>)
		{
			return EmuSIMD::Funcs::extract_i32x4_lane_f64x2<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i256_generic>)
		{
			return EmuSIMD::Funcs::extract_i32x8_lane_f64x2<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i512_generic>)
		{
			return EmuSIMD::Funcs::extract_i32x16_lane_f64x2<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i8x16>)
		{
			return EmuSIMD::Funcs::extract_i8x16_lane_f64x2<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i16x8>)
		{
			return EmuSIMD::Funcs::extract_i16x8_lane_f64x2<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i32x4>)
		{
			return EmuSIMD::Funcs::extract_i32x4_lane_f64x2<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i64x2>)
		{
			return EmuSIMD::Funcs::extract_i64x2_lane_f64x2<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i8x32>)
		{
			return EmuSIMD::Funcs::extract_i8x32_lane_f64x2<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i16x16>)
		{
			return EmuSIMD::Funcs::extract_i16x16_lane_f64x2<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i32x8>)
		{
			return EmuSIMD::Funcs::extract_i32x8_lane_f64x2<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i64x4>)
		{
			return EmuSIMD::Funcs::extract_i64x4_lane_f64x2<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i8x64>)
		{
			return EmuSIMD::Funcs::extract_i8x64_lane_f64x2<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i16x32>)
		{
			return EmuSIMD::Funcs::extract_i16x32_lane_f64x2<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i32x16>)
		{
			return EmuSIMD::Funcs::extract_i32x16_lane_f64x2<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i64x8>)
		{
			return EmuSIMD::Funcs::extract_i64x8_lane_f64x2<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u8x16>)
		{
			return EmuSIMD::Funcs::extract_u8x16_lane_f64x2<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u16x8>)
		{
			return EmuSIMD::Funcs::extract_u16x8_lane_f64x2<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u32x4>)
		{
			return EmuSIMD::Funcs::extract_u32x4_lane_f64x2<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u64x2>)
		{
			return EmuSIMD::Funcs::extract_u64x2_lane_f64x2<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u8x32>)
		{
			return EmuSIMD::Funcs::extract_u8x32_lane_f64x2<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u16x16>)
		{
			return EmuSIMD::Funcs::extract_u16x16_lane_f64x2<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u32x8>)
		{
			return EmuSIMD::Funcs::extract_u32x8_lane_f64x2<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u64x4>)
		{
			return EmuSIMD::Funcs::extract_u64x4_lane_f64x2<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u8x64>)
		{
			return EmuSIMD::Funcs::extract_u8x64_lane_f64x2<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u16x32>)
		{
			return EmuSIMD::Funcs::extract_u16x32_lane_f64x2<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u32x16>)
		{
			return EmuSIMD::Funcs::extract_u32x16_lane_f64x2<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u64x8>)
		{
			return EmuSIMD::Funcs::extract_u64x8_lane_f64x2<LaneIndex_>(in_);
		}
		else
		{
			static_assert
			(
				EmuCore::TMP::get_false<in_uq>(),
				"Attempted to extract a lane from a SIMD register as a f64x2 register via EmuSIMD helpers, but the provided input register is not supported for such an extraction."
			);
		}
	}

	template<std::size_t LaneIndex_, class In_>
	[[nodiscard]] constexpr inline EmuSIMD::f64x4 _extract_lane_f64x4_prevalidated(In_&& in_)
	{
		using in_uq = typename EmuCore::TMP::remove_ref_cv<In_>::type;
		if constexpr (std::is_same_v<in_uq, EmuSIMD::f32x8>)
		{
			return EmuSIMD::Funcs::extract_f32x8_lane_f64x4<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::f32x16>)
		{
			return EmuSIMD::Funcs::extract_f32x16_lane_f64x4<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::f64x4>)
		{
			return EmuSIMD::Funcs::extract_f64x4_lane_f64x4<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::f64x8>)
		{
			return EmuSIMD::Funcs::extract_f64x8_lane_f64x4<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i256_generic>)
		{
			return EmuSIMD::Funcs::extract_i32x8_lane_f64x4<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i512_generic>)
		{
			return EmuSIMD::Funcs::extract_i32x16_lane_f64x4<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i8x32>)
		{
			return EmuSIMD::Funcs::extract_i8x32_lane_f64x4<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i16x16>)
		{
			return EmuSIMD::Funcs::extract_i16x16_lane_f64x4<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i32x8>)
		{
			return EmuSIMD::Funcs::extract_i32x8_lane_f64x4<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i64x4>)
		{
			return EmuSIMD::Funcs::extract_i64x4_lane_f64x4<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i8x64>)
		{
			return EmuSIMD::Funcs::extract_i8x64_lane_f64x4<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i16x32>)
		{
			return EmuSIMD::Funcs::extract_i16x32_lane_f64x4<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i32x16>)
		{
			return EmuSIMD::Funcs::extract_i32x16_lane_f64x4<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i64x8>)
		{
			return EmuSIMD::Funcs::extract_i64x8_lane_f64x4<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u8x32>)
		{
			return EmuSIMD::Funcs::extract_u8x32_lane_f64x4<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u16x16>)
		{
			return EmuSIMD::Funcs::extract_u16x16_lane_f64x4<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u32x8>)
		{
			return EmuSIMD::Funcs::extract_u32x8_lane_f64x4<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u64x4>)
		{
			return EmuSIMD::Funcs::extract_u64x4_lane_f64x4<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u8x64>)
		{
			return EmuSIMD::Funcs::extract_u8x64_lane_f64x4<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u16x32>)
		{
			return EmuSIMD::Funcs::extract_u16x32_lane_f64x4<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u32x16>)
		{
			return EmuSIMD::Funcs::extract_u32x16_lane_f64x4<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u64x8>)
		{
			return EmuSIMD::Funcs::extract_u64x8_lane_f64x4<LaneIndex_>(std::forward<In_>(in_));
		}
		else
		{
			static_assert
			(
				EmuCore::TMP::get_false<in_uq>(),
				"Attempted to extract a lane from a SIMD register as a f64x4 register via EmuSIMD helpers, but the provided input register is not supported for such an extraction."
			);
		}
	}

	template<std::size_t LaneIndex_, class In_>
	[[nodiscard]] constexpr inline EmuSIMD::f64x8 _extract_lane_f64x8_prevalidated(In_&& in_)
	{
		using in_uq = typename EmuCore::TMP::remove_ref_cv<In_>::type;
		if constexpr (std::is_same_v<in_uq, EmuSIMD::f32x16>)
		{
			return EmuSIMD::Funcs::extract_f32x16_lane_f64x8<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::f64x8>)
		{
			return EmuSIMD::Funcs::extract_f64x8_lane_f64x8<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i512_generic>)
		{
			return EmuSIMD::Funcs::extract_i32x16_lane_f64x8<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i8x64>)
		{
			return EmuSIMD::Funcs::extract_i8x64_lane_f64x8<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i16x32>)
		{
			return EmuSIMD::Funcs::extract_i16x32_lane_f64x8<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i32x16>)
		{
			return EmuSIMD::Funcs::extract_i32x16_lane_f64x8<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i64x8>)
		{
			return EmuSIMD::Funcs::extract_i64x8_lane_f64x8<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u8x64>)
		{
			return EmuSIMD::Funcs::extract_u8x64_lane_f64x8<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u16x32>)
		{
			return EmuSIMD::Funcs::extract_u16x32_lane_f64x8<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u32x16>)
		{
			return EmuSIMD::Funcs::extract_u32x16_lane_f64x8<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u64x8>)
		{
			return EmuSIMD::Funcs::extract_u64x8_lane_f64x8<LaneIndex_>(std::forward<In_>(in_));
		}
		else
		{
			static_assert
			(
				EmuCore::TMP::get_false<in_uq>(),
				"Attempted to extract a lane from a SIMD register as a f64x8 register via EmuSIMD helpers, but the provided input register is not supported for such an extraction."
			);
		}
	}

	template<std::size_t LaneIndex_, class In_>
	[[nodiscard]] constexpr inline EmuSIMD::i8x16 _extract_lane_i8x16_prevalidated(In_&& in_)
	{
		using in_uq = typename EmuCore::TMP::remove_ref_cv<In_>::type;
		if constexpr (std::is_same_v<in_uq, EmuSIMD::f32x4>)
		{
			return EmuSIMD::Funcs::extract_f32x4_lane_i8x16<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::f32x8>)
		{
			return EmuSIMD::Funcs::extract_f32x8_lane_i8x16<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::f32x16>)
		{
			return EmuSIMD::Funcs::extract_f32x16_lane_i8x16<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::f64x2>)
		{
			return EmuSIMD::Funcs::extract_f64x2_lane_i8x16<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::f64x4>)
		{
			return EmuSIMD::Funcs::extract_f64x4_lane_i8x16<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::f64x8>)
		{
			return EmuSIMD::Funcs::extract_f64x8_lane_i8x16<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i128_generic>)
		{
			return EmuSIMD::Funcs::extract_i32x4_lane_i8x16<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i256_generic>)
		{
			return EmuSIMD::Funcs::extract_i32x8_lane_i8x16<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i512_generic>)
		{
			return EmuSIMD::Funcs::extract_i32x16_lane_i8x16<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i8x16>)
		{
			return EmuSIMD::Funcs::extract_i8x16_lane_i8x16<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i16x8>)
		{
			return EmuSIMD::Funcs::extract_i16x8_lane_i8x16<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i32x4>)
		{
			return EmuSIMD::Funcs::extract_i32x4_lane_i8x16<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i64x2>)
		{
			return EmuSIMD::Funcs::extract_i64x2_lane_i8x16<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i8x32>)
		{
			return EmuSIMD::Funcs::extract_i8x32_lane_i8x16<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i16x16>)
		{
			return EmuSIMD::Funcs::extract_i16x16_lane_i8x16<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i32x8>)
		{
			return EmuSIMD::Funcs::extract_i32x8_lane_i8x16<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i64x4>)
		{
			return EmuSIMD::Funcs::extract_i64x4_lane_i8x16<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i8x64>)
		{
			return EmuSIMD::Funcs::extract_i8x64_lane_i8x16<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i16x32>)
		{
			return EmuSIMD::Funcs::extract_i16x32_lane_i8x16<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i32x16>)
		{
			return EmuSIMD::Funcs::extract_i32x16_lane_i8x16<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i64x8>)
		{
			return EmuSIMD::Funcs::extract_i64x8_lane_i8x16<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u8x16>)
		{
			return EmuSIMD::Funcs::extract_u8x16_lane_i8x16<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u16x8>)
		{
			return EmuSIMD::Funcs::extract_u16x8_lane_i8x16<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u32x4>)
		{
			return EmuSIMD::Funcs::extract_u32x4_lane_i8x16<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u64x2>)
		{
			return EmuSIMD::Funcs::extract_u64x2_lane_i8x16<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u8x32>)
		{
			return EmuSIMD::Funcs::extract_u8x32_lane_i8x16<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u16x16>)
		{
			return EmuSIMD::Funcs::extract_u16x16_lane_i8x16<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u32x8>)
		{
			return EmuSIMD::Funcs::extract_u32x8_lane_i8x16<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u64x4>)
		{
			return EmuSIMD::Funcs::extract_u64x4_lane_i8x16<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u8x64>)
		{
			return EmuSIMD::Funcs::extract_u8x64_lane_i8x16<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u16x32>)
		{
			return EmuSIMD::Funcs::extract_u16x32_lane_i8x16<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u32x16>)
		{
			return EmuSIMD::Funcs::extract_u32x16_lane_i8x16<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u64x8>)
		{
			return EmuSIMD::Funcs::extract_u64x8_lane_i8x16<LaneIndex_>(in_);
		}
		else
		{
			static_assert
			(
				EmuCore::TMP::get_false<in_uq>(),
				"Attempted to extract a lane from a SIMD register as a i8x16 register via EmuSIMD helpers, but the provided input register is not supported for such an extraction."
			);
		}
	}

	template<std::size_t LaneIndex_, class In_>
	[[nodiscard]] constexpr inline EmuSIMD::i8x32 _extract_lane_i8x32_prevalidated(In_&& in_)
	{
		using in_uq = typename EmuCore::TMP::remove_ref_cv<In_>::type;
		if constexpr (std::is_same_v<in_uq, EmuSIMD::f32x8>)
		{
			return EmuSIMD::Funcs::extract_f32x8_lane_i8x32<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::f32x16>)
		{
			return EmuSIMD::Funcs::extract_f32x16_lane_i8x32<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::f64x4>)
		{
			return EmuSIMD::Funcs::extract_f64x4_lane_i8x32<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::f64x8>)
		{
			return EmuSIMD::Funcs::extract_f64x8_lane_i8x32<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i256_generic>)
		{
			return EmuSIMD::Funcs::extract_i32x8_lane_i8x32<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i512_generic>)
		{
			return EmuSIMD::Funcs::extract_i32x16_lane_i8x32<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i8x32>)
		{
			return EmuSIMD::Funcs::extract_i8x32_lane_i8x32<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i16x16>)
		{
			return EmuSIMD::Funcs::extract_i16x16_lane_i8x32<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i32x8>)
		{
			return EmuSIMD::Funcs::extract_i32x8_lane_i8x32<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i64x4>)
		{
			return EmuSIMD::Funcs::extract_i64x4_lane_i8x32<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i8x64>)
		{
			return EmuSIMD::Funcs::extract_i8x64_lane_i8x32<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i16x32>)
		{
			return EmuSIMD::Funcs::extract_i16x32_lane_i8x32<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i32x16>)
		{
			return EmuSIMD::Funcs::extract_i32x16_lane_i8x32<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i64x8>)
		{
			return EmuSIMD::Funcs::extract_i64x8_lane_i8x32<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u8x32>)
		{
			return EmuSIMD::Funcs::extract_u8x32_lane_i8x32<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u16x16>)
		{
			return EmuSIMD::Funcs::extract_u16x16_lane_i8x32<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u32x8>)
		{
			return EmuSIMD::Funcs::extract_u32x8_lane_i8x32<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u64x4>)
		{
			return EmuSIMD::Funcs::extract_u64x4_lane_i8x32<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u8x64>)
		{
			return EmuSIMD::Funcs::extract_u8x64_lane_i8x32<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u16x32>)
		{
			return EmuSIMD::Funcs::extract_u16x32_lane_i8x32<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u32x16>)
		{
			return EmuSIMD::Funcs::extract_u32x16_lane_i8x32<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u64x8>)
		{
			return EmuSIMD::Funcs::extract_u64x8_lane_i8x32<LaneIndex_>(std::forward<In_>(in_));
		}
		else
		{
			static_assert
			(
				EmuCore::TMP::get_false<in_uq>(),
				"Attempted to extract a lane from a SIMD register as a i8x32 register via EmuSIMD helpers, but the provided input register is not supported for such an extraction."
			);
		}
	}

	template<std::size_t LaneIndex_, class In_>
	[[nodiscard]] constexpr inline EmuSIMD::i8x64 _extract_lane_i8x64_prevalidated(In_&& in_)
	{
		using in_uq = typename EmuCore::TMP::remove_ref_cv<In_>::type;
		if constexpr (std::is_same_v<in_uq, EmuSIMD::f32x16>)
		{
			return EmuSIMD::Funcs::extract_f32x16_lane_i8x64<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::f64x8>)
		{
			return EmuSIMD::Funcs::extract_f64x8_lane_i8x64<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i512_generic>)
		{
			return EmuSIMD::Funcs::extract_i32x16_lane_i8x64<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i8x64>)
		{
			return EmuSIMD::Funcs::extract_i8x64_lane_i8x64<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i16x32>)
		{
			return EmuSIMD::Funcs::extract_i16x32_lane_i8x64<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i32x16>)
		{
			return EmuSIMD::Funcs::extract_i32x16_lane_i8x64<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i64x8>)
		{
			return EmuSIMD::Funcs::extract_i64x8_lane_i8x64<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u8x64>)
		{
			return EmuSIMD::Funcs::extract_u8x64_lane_i8x64<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u16x32>)
		{
			return EmuSIMD::Funcs::extract_u16x32_lane_i8x64<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u32x16>)
		{
			return EmuSIMD::Funcs::extract_u32x16_lane_i8x64<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u64x8>)
		{
			return EmuSIMD::Funcs::extract_u64x8_lane_i8x64<LaneIndex_>(std::forward<In_>(in_));
		}
		else
		{
			static_assert
			(
				EmuCore::TMP::get_false<in_uq>(),
				"Attempted to extract a lane from a SIMD register as a i8x64 register via EmuSIMD helpers, but the provided input register is not supported for such an extraction."
			);
		}
	}

	template<std::size_t LaneIndex_, class In_>
	[[nodiscard]] constexpr inline EmuSIMD::i16x8 _extract_lane_i16x8_prevalidated(In_&& in_)
	{
		using in_uq = typename EmuCore::TMP::remove_ref_cv<In_>::type;
		if constexpr (std::is_same_v<in_uq, EmuSIMD::f32x4>)
		{
			return EmuSIMD::Funcs::extract_f32x4_lane_i16x8<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::f32x8>)
		{
			return EmuSIMD::Funcs::extract_f32x8_lane_i16x8<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::f32x16>)
		{
			return EmuSIMD::Funcs::extract_f32x16_lane_i16x8<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::f64x2>)
		{
			return EmuSIMD::Funcs::extract_f64x2_lane_i16x8<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::f64x4>)
		{
			return EmuSIMD::Funcs::extract_f64x4_lane_i16x8<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::f64x8>)
		{
			return EmuSIMD::Funcs::extract_f64x8_lane_i16x8<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i128_generic>)
		{
			return EmuSIMD::Funcs::extract_i32x4_lane_i16x8<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i256_generic>)
		{
			return EmuSIMD::Funcs::extract_i32x8_lane_i16x8<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i512_generic>)
		{
			return EmuSIMD::Funcs::extract_i32x16_lane_i16x8<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i8x16>)
		{
			return EmuSIMD::Funcs::extract_i8x16_lane_i16x8<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i16x8>)
		{
			return EmuSIMD::Funcs::extract_i16x8_lane_i16x8<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i32x4>)
		{
			return EmuSIMD::Funcs::extract_i32x4_lane_i16x8<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i64x2>)
		{
			return EmuSIMD::Funcs::extract_i64x2_lane_i16x8<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i8x32>)
		{
			return EmuSIMD::Funcs::extract_i8x32_lane_i16x8<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i16x16>)
		{
			return EmuSIMD::Funcs::extract_i16x16_lane_i16x8<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i32x8>)
		{
			return EmuSIMD::Funcs::extract_i32x8_lane_i16x8<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i64x4>)
		{
			return EmuSIMD::Funcs::extract_i64x4_lane_i16x8<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i8x64>)
		{
			return EmuSIMD::Funcs::extract_i8x64_lane_i16x8<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i16x32>)
		{
			return EmuSIMD::Funcs::extract_i16x32_lane_i16x8<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i32x16>)
		{
			return EmuSIMD::Funcs::extract_i32x16_lane_i16x8<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i64x8>)
		{
			return EmuSIMD::Funcs::extract_i64x8_lane_i16x8<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u8x16>)
		{
			return EmuSIMD::Funcs::extract_u8x16_lane_i16x8<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u16x8>)
		{
			return EmuSIMD::Funcs::extract_u16x8_lane_i16x8<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u32x4>)
		{
			return EmuSIMD::Funcs::extract_u32x4_lane_i16x8<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u64x2>)
		{
			return EmuSIMD::Funcs::extract_u64x2_lane_i16x8<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u8x32>)
		{
			return EmuSIMD::Funcs::extract_u8x32_lane_i16x8<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u16x16>)
		{
			return EmuSIMD::Funcs::extract_u16x16_lane_i16x8<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u32x8>)
		{
			return EmuSIMD::Funcs::extract_u32x8_lane_i16x8<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u64x4>)
		{
			return EmuSIMD::Funcs::extract_u64x4_lane_i16x8<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u8x64>)
		{
			return EmuSIMD::Funcs::extract_u8x64_lane_i16x8<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u16x32>)
		{
			return EmuSIMD::Funcs::extract_u16x32_lane_i16x8<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u32x16>)
		{
			return EmuSIMD::Funcs::extract_u32x16_lane_i16x8<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u64x8>)
		{
			return EmuSIMD::Funcs::extract_u64x8_lane_i16x8<LaneIndex_>(in_);
		}
		else
		{
			static_assert
			(
				EmuCore::TMP::get_false<in_uq>(),
				"Attempted to extract a lane from a SIMD register as a i16x8 register via EmuSIMD helpers, but the provided input register is not supported for such an extraction."
			);
		}
	}

	template<std::size_t LaneIndex_, class In_>
	[[nodiscard]] constexpr inline EmuSIMD::i16x16 _extract_lane_i16x16_prevalidated(In_&& in_)
	{
		using in_uq = typename EmuCore::TMP::remove_ref_cv<In_>::type;
		if constexpr (std::is_same_v<in_uq, EmuSIMD::f32x8>)
		{
			return EmuSIMD::Funcs::extract_f32x8_lane_i16x16<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::f32x16>)
		{
			return EmuSIMD::Funcs::extract_f32x16_lane_i16x16<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::f64x4>)
		{
			return EmuSIMD::Funcs::extract_f64x4_lane_i16x16<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::f64x8>)
		{
			return EmuSIMD::Funcs::extract_f64x8_lane_i16x16<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i256_generic>)
		{
			return EmuSIMD::Funcs::extract_i32x8_lane_i16x16<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i512_generic>)
		{
			return EmuSIMD::Funcs::extract_i32x16_lane_i16x16<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i8x32>)
		{
			return EmuSIMD::Funcs::extract_i8x32_lane_i16x16<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i16x16>)
		{
			return EmuSIMD::Funcs::extract_i16x16_lane_i16x16<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i32x8>)
		{
			return EmuSIMD::Funcs::extract_i32x8_lane_i16x16<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i64x4>)
		{
			return EmuSIMD::Funcs::extract_i64x4_lane_i16x16<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i8x64>)
		{
			return EmuSIMD::Funcs::extract_i8x64_lane_i16x16<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i16x32>)
		{
			return EmuSIMD::Funcs::extract_i16x32_lane_i16x16<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i32x16>)
		{
			return EmuSIMD::Funcs::extract_i32x16_lane_i16x16<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i64x8>)
		{
			return EmuSIMD::Funcs::extract_i64x8_lane_i16x16<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u8x32>)
		{
			return EmuSIMD::Funcs::extract_u8x32_lane_i16x16<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u16x16>)
		{
			return EmuSIMD::Funcs::extract_u16x16_lane_i16x16<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u32x8>)
		{
			return EmuSIMD::Funcs::extract_u32x8_lane_i16x16<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u64x4>)
		{
			return EmuSIMD::Funcs::extract_u64x4_lane_i16x16<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u8x64>)
		{
			return EmuSIMD::Funcs::extract_u8x64_lane_i16x16<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u16x32>)
		{
			return EmuSIMD::Funcs::extract_u16x32_lane_i16x16<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u32x16>)
		{
			return EmuSIMD::Funcs::extract_u32x16_lane_i16x16<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u64x8>)
		{
			return EmuSIMD::Funcs::extract_u64x8_lane_i16x16<LaneIndex_>(std::forward<In_>(in_));
		}
		else
		{
			static_assert
			(
				EmuCore::TMP::get_false<in_uq>(),
				"Attempted to extract a lane from a SIMD register as a i16x16 register via EmuSIMD helpers, but the provided input register is not supported for such an extraction."
			);
		}
	}

	template<std::size_t LaneIndex_, class In_>
	[[nodiscard]] constexpr inline EmuSIMD::i16x32 _extract_lane_i16x32_prevalidated(In_&& in_)
	{
		using in_uq = typename EmuCore::TMP::remove_ref_cv<In_>::type;
		if constexpr (std::is_same_v<in_uq, EmuSIMD::f32x16>)
		{
			return EmuSIMD::Funcs::extract_f32x16_lane_i16x32<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::f64x8>)
		{
			return EmuSIMD::Funcs::extract_f64x8_lane_i16x32<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i512_generic>)
		{
			return EmuSIMD::Funcs::extract_i32x16_lane_i16x32<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i8x64>)
		{
			return EmuSIMD::Funcs::extract_i8x64_lane_i16x32<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i16x32>)
		{
			return EmuSIMD::Funcs::extract_i16x32_lane_i16x32<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i32x16>)
		{
			return EmuSIMD::Funcs::extract_i32x16_lane_i16x32<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i64x8>)
		{
			return EmuSIMD::Funcs::extract_i64x8_lane_i16x32<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u8x64>)
		{
			return EmuSIMD::Funcs::extract_u8x64_lane_i16x32<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u16x32>)
		{
			return EmuSIMD::Funcs::extract_u16x32_lane_i16x32<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u32x16>)
		{
			return EmuSIMD::Funcs::extract_u32x16_lane_i16x32<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u64x8>)
		{
			return EmuSIMD::Funcs::extract_u64x8_lane_i16x32<LaneIndex_>(std::forward<In_>(in_));
		}
		else
		{
			static_assert
			(
				EmuCore::TMP::get_false<in_uq>(),
				"Attempted to extract a lane from a SIMD register as a i16x32 register via EmuSIMD helpers, but the provided input register is not supported for such an extraction."
			);
		}
	}

	template<std::size_t LaneIndex_, class In_>
	[[nodiscard]] constexpr inline EmuSIMD::i32x4 _extract_lane_i32x4_prevalidated(In_&& in_)
	{
		using in_uq = typename EmuCore::TMP::remove_ref_cv<In_>::type;
		if constexpr (std::is_same_v<in_uq, EmuSIMD::f32x4>)
		{
			return EmuSIMD::Funcs::extract_f32x4_lane_i32x4<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::f32x8>)
		{
			return EmuSIMD::Funcs::extract_f32x8_lane_i32x4<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::f32x16>)
		{
			return EmuSIMD::Funcs::extract_f32x16_lane_i32x4<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::f64x2>)
		{
			return EmuSIMD::Funcs::extract_f64x2_lane_i32x4<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::f64x4>)
		{
			return EmuSIMD::Funcs::extract_f64x4_lane_i32x4<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::f64x8>)
		{
			return EmuSIMD::Funcs::extract_f64x8_lane_i32x4<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i128_generic>)
		{
			return EmuSIMD::Funcs::extract_i32x4_lane_i32x4<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i256_generic>)
		{
			return EmuSIMD::Funcs::extract_i32x8_lane_i32x4<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i512_generic>)
		{
			return EmuSIMD::Funcs::extract_i32x16_lane_i32x4<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i8x16>)
		{
			return EmuSIMD::Funcs::extract_i8x16_lane_i32x4<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i16x8>)
		{
			return EmuSIMD::Funcs::extract_i16x8_lane_i32x4<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i32x4>)
		{
			return EmuSIMD::Funcs::extract_i32x4_lane_i32x4<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i64x2>)
		{
			return EmuSIMD::Funcs::extract_i64x2_lane_i32x4<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i8x32>)
		{
			return EmuSIMD::Funcs::extract_i8x32_lane_i32x4<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i16x16>)
		{
			return EmuSIMD::Funcs::extract_i16x16_lane_i32x4<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i32x8>)
		{
			return EmuSIMD::Funcs::extract_i32x8_lane_i32x4<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i64x4>)
		{
			return EmuSIMD::Funcs::extract_i64x4_lane_i32x4<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i8x64>)
		{
			return EmuSIMD::Funcs::extract_i8x64_lane_i32x4<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i16x32>)
		{
			return EmuSIMD::Funcs::extract_i16x32_lane_i32x4<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i32x16>)
		{
			return EmuSIMD::Funcs::extract_i32x16_lane_i32x4<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i64x8>)
		{
			return EmuSIMD::Funcs::extract_i64x8_lane_i32x4<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u8x16>)
		{
			return EmuSIMD::Funcs::extract_u8x16_lane_i32x4<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u16x8>)
		{
			return EmuSIMD::Funcs::extract_u16x8_lane_i32x4<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u32x4>)
		{
			return EmuSIMD::Funcs::extract_u32x4_lane_i32x4<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u64x2>)
		{
			return EmuSIMD::Funcs::extract_u64x2_lane_i32x4<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u8x32>)
		{
			return EmuSIMD::Funcs::extract_u8x32_lane_i32x4<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u16x16>)
		{
			return EmuSIMD::Funcs::extract_u16x16_lane_i32x4<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u32x8>)
		{
			return EmuSIMD::Funcs::extract_u32x8_lane_i32x4<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u64x4>)
		{
			return EmuSIMD::Funcs::extract_u64x4_lane_i32x4<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u8x64>)
		{
			return EmuSIMD::Funcs::extract_u8x64_lane_i32x4<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u16x32>)
		{
			return EmuSIMD::Funcs::extract_u16x32_lane_i32x4<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u32x16>)
		{
			return EmuSIMD::Funcs::extract_u32x16_lane_i32x4<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u64x8>)
		{
			return EmuSIMD::Funcs::extract_u64x8_lane_i32x4<LaneIndex_>(in_);
		}
		else
		{
			static_assert
			(
				EmuCore::TMP::get_false<in_uq>(),
				"Attempted to extract a lane from a SIMD register as a i32x4 register via EmuSIMD helpers, but the provided input register is not supported for such an extraction."
			);
		}
	}

	template<std::size_t LaneIndex_, class In_>
	[[nodiscard]] constexpr inline EmuSIMD::i32x8 _extract_lane_i32x8_prevalidated(In_&& in_)
	{
		using in_uq = typename EmuCore::TMP::remove_ref_cv<In_>::type;
		if constexpr (std::is_same_v<in_uq, EmuSIMD::f32x8>)
		{
			return EmuSIMD::Funcs::extract_f32x8_lane_i32x8<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::f32x16>)
		{
			return EmuSIMD::Funcs::extract_f32x16_lane_i32x8<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::f64x4>)
		{
			return EmuSIMD::Funcs::extract_f64x4_lane_i32x8<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::f64x8>)
		{
			return EmuSIMD::Funcs::extract_f64x8_lane_i32x8<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i256_generic>)
		{
			return EmuSIMD::Funcs::extract_i32x8_lane_i32x8<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i512_generic>)
		{
			return EmuSIMD::Funcs::extract_i32x16_lane_i32x8<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i8x32>)
		{
			return EmuSIMD::Funcs::extract_i8x32_lane_i32x8<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i16x16>)
		{
			return EmuSIMD::Funcs::extract_i16x16_lane_i32x8<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i32x8>)
		{
			return EmuSIMD::Funcs::extract_i32x8_lane_i32x8<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i64x4>)
		{
			return EmuSIMD::Funcs::extract_i64x4_lane_i32x8<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i8x64>)
		{
			return EmuSIMD::Funcs::extract_i8x64_lane_i32x8<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i16x32>)
		{
			return EmuSIMD::Funcs::extract_i16x32_lane_i32x8<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i32x16>)
		{
			return EmuSIMD::Funcs::extract_i32x16_lane_i32x8<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i64x8>)
		{
			return EmuSIMD::Funcs::extract_i64x8_lane_i32x8<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u8x32>)
		{
			return EmuSIMD::Funcs::extract_u8x32_lane_i32x8<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u16x16>)
		{
			return EmuSIMD::Funcs::extract_u16x16_lane_i32x8<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u32x8>)
		{
			return EmuSIMD::Funcs::extract_u32x8_lane_i32x8<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u64x4>)
		{
			return EmuSIMD::Funcs::extract_u64x4_lane_i32x8<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u8x64>)
		{
			return EmuSIMD::Funcs::extract_u8x64_lane_i32x8<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u16x32>)
		{
			return EmuSIMD::Funcs::extract_u16x32_lane_i32x8<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u32x16>)
		{
			return EmuSIMD::Funcs::extract_u32x16_lane_i32x8<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u64x8>)
		{
			return EmuSIMD::Funcs::extract_u64x8_lane_i32x8<LaneIndex_>(std::forward<In_>(in_));
		}
		else
		{
			static_assert
			(
				EmuCore::TMP::get_false<in_uq>(),
				"Attempted to extract a lane from a SIMD register as a i32x8 register via EmuSIMD helpers, but the provided input register is not supported for such an extraction."
			);
		}
	}

	template<std::size_t LaneIndex_, class In_>
	[[nodiscard]] constexpr inline EmuSIMD::i32x16 _extract_lane_i32x16_prevalidated(In_&& in_)
	{
		using in_uq = typename EmuCore::TMP::remove_ref_cv<In_>::type;
		if constexpr (std::is_same_v<in_uq, EmuSIMD::f32x16>)
		{
			return EmuSIMD::Funcs::extract_f32x16_lane_i32x16<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::f64x8>)
		{
			return EmuSIMD::Funcs::extract_f64x8_lane_i32x16<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i512_generic>)
		{
			return EmuSIMD::Funcs::extract_i32x16_lane_i32x16<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i8x64>)
		{
			return EmuSIMD::Funcs::extract_i8x64_lane_i32x16<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i16x32>)
		{
			return EmuSIMD::Funcs::extract_i16x32_lane_i32x16<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i32x16>)
		{
			return EmuSIMD::Funcs::extract_i32x16_lane_i32x16<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i64x8>)
		{
			return EmuSIMD::Funcs::extract_i64x8_lane_i32x16<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u8x64>)
		{
			return EmuSIMD::Funcs::extract_u8x64_lane_i32x16<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u16x32>)
		{
			return EmuSIMD::Funcs::extract_u16x32_lane_i32x16<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u32x16>)
		{
			return EmuSIMD::Funcs::extract_u32x16_lane_i32x16<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u64x8>)
		{
			return EmuSIMD::Funcs::extract_u64x8_lane_i32x16<LaneIndex_>(std::forward<In_>(in_));
		}
		else
		{
			static_assert
			(
				EmuCore::TMP::get_false<in_uq>(),
				"Attempted to extract a lane from a SIMD register as a i32x16 register via EmuSIMD helpers, but the provided input register is not supported for such an extraction."
			);
		}
	}

	template<std::size_t LaneIndex_, class In_>
	[[nodiscard]] constexpr inline EmuSIMD::i64x2 _extract_lane_i64x2_prevalidated(In_&& in_)
	{
		using in_uq = typename EmuCore::TMP::remove_ref_cv<In_>::type;
		if constexpr (std::is_same_v<in_uq, EmuSIMD::f32x4>)
		{
			return EmuSIMD::Funcs::extract_f32x4_lane_i64x2<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::f32x8>)
		{
			return EmuSIMD::Funcs::extract_f32x8_lane_i64x2<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::f32x16>)
		{
			return EmuSIMD::Funcs::extract_f32x16_lane_i64x2<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::f64x2>)
		{
			return EmuSIMD::Funcs::extract_f64x2_lane_i64x2<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::f64x4>)
		{
			return EmuSIMD::Funcs::extract_f64x4_lane_i64x2<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::f64x8>)
		{
			return EmuSIMD::Funcs::extract_f64x8_lane_i64x2<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i128_generic>)
		{
			return EmuSIMD::Funcs::extract_i32x4_lane_i64x2<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i256_generic>)
		{
			return EmuSIMD::Funcs::extract_i32x8_lane_i64x2<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i512_generic>)
		{
			return EmuSIMD::Funcs::extract_i32x16_lane_i64x2<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i8x16>)
		{
			return EmuSIMD::Funcs::extract_i8x16_lane_i64x2<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i16x8>)
		{
			return EmuSIMD::Funcs::extract_i16x8_lane_i64x2<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i32x4>)
		{
			return EmuSIMD::Funcs::extract_i32x4_lane_i64x2<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i64x2>)
		{
			return EmuSIMD::Funcs::extract_i64x2_lane_i64x2<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i8x32>)
		{
			return EmuSIMD::Funcs::extract_i8x32_lane_i64x2<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i16x16>)
		{
			return EmuSIMD::Funcs::extract_i16x16_lane_i64x2<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i32x8>)
		{
			return EmuSIMD::Funcs::extract_i32x8_lane_i64x2<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i64x4>)
		{
			return EmuSIMD::Funcs::extract_i64x4_lane_i64x2<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i8x64>)
		{
			return EmuSIMD::Funcs::extract_i8x64_lane_i64x2<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i16x32>)
		{
			return EmuSIMD::Funcs::extract_i16x32_lane_i64x2<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i32x16>)
		{
			return EmuSIMD::Funcs::extract_i32x16_lane_i64x2<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i64x8>)
		{
			return EmuSIMD::Funcs::extract_i64x8_lane_i64x2<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u8x16>)
		{
			return EmuSIMD::Funcs::extract_u8x16_lane_i64x2<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u16x8>)
		{
			return EmuSIMD::Funcs::extract_u16x8_lane_i64x2<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u32x4>)
		{
			return EmuSIMD::Funcs::extract_u32x4_lane_i64x2<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u64x2>)
		{
			return EmuSIMD::Funcs::extract_u64x2_lane_i64x2<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u8x32>)
		{
			return EmuSIMD::Funcs::extract_u8x32_lane_i64x2<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u16x16>)
		{
			return EmuSIMD::Funcs::extract_u16x16_lane_i64x2<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u32x8>)
		{
			return EmuSIMD::Funcs::extract_u32x8_lane_i64x2<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u64x4>)
		{
			return EmuSIMD::Funcs::extract_u64x4_lane_i64x2<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u8x64>)
		{
			return EmuSIMD::Funcs::extract_u8x64_lane_i64x2<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u16x32>)
		{
			return EmuSIMD::Funcs::extract_u16x32_lane_i64x2<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u32x16>)
		{
			return EmuSIMD::Funcs::extract_u32x16_lane_i64x2<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u64x8>)
		{
			return EmuSIMD::Funcs::extract_u64x8_lane_i64x2<LaneIndex_>(in_);
		}
		else
		{
			static_assert
			(
				EmuCore::TMP::get_false<in_uq>(),
				"Attempted to extract a lane from a SIMD register as a i64x2 register via EmuSIMD helpers, but the provided input register is not supported for such an extraction."
			);
		}
	}

	template<std::size_t LaneIndex_, class In_>
	[[nodiscard]] constexpr inline EmuSIMD::i64x4 _extract_lane_i64x4_prevalidated(In_&& in_)
	{
		using in_uq = typename EmuCore::TMP::remove_ref_cv<In_>::type;
		if constexpr (std::is_same_v<in_uq, EmuSIMD::f32x8>)
		{
			return EmuSIMD::Funcs::extract_f32x8_lane_i64x4<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::f32x16>)
		{
			return EmuSIMD::Funcs::extract_f32x16_lane_i64x4<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::f64x4>)
		{
			return EmuSIMD::Funcs::extract_f64x4_lane_i64x4<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::f64x8>)
		{
			return EmuSIMD::Funcs::extract_f64x8_lane_i64x4<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i256_generic>)
		{
			return EmuSIMD::Funcs::extract_i32x8_lane_i64x4<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i512_generic>)
		{
			return EmuSIMD::Funcs::extract_i32x16_lane_i64x4<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i8x32>)
		{
			return EmuSIMD::Funcs::extract_i8x32_lane_i64x4<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i16x16>)
		{
			return EmuSIMD::Funcs::extract_i16x16_lane_i64x4<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i32x8>)
		{
			return EmuSIMD::Funcs::extract_i32x8_lane_i64x4<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i64x4>)
		{
			return EmuSIMD::Funcs::extract_i64x4_lane_i64x4<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i8x64>)
		{
			return EmuSIMD::Funcs::extract_i8x64_lane_i64x4<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i16x32>)
		{
			return EmuSIMD::Funcs::extract_i16x32_lane_i64x4<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i32x16>)
		{
			return EmuSIMD::Funcs::extract_i32x16_lane_i64x4<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i64x8>)
		{
			return EmuSIMD::Funcs::extract_i64x8_lane_i64x4<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u8x32>)
		{
			return EmuSIMD::Funcs::extract_u8x32_lane_i64x4<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u16x16>)
		{
			return EmuSIMD::Funcs::extract_u16x16_lane_i64x4<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u32x8>)
		{
			return EmuSIMD::Funcs::extract_u32x8_lane_i64x4<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u64x4>)
		{
			return EmuSIMD::Funcs::extract_u64x4_lane_i64x4<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u8x64>)
		{
			return EmuSIMD::Funcs::extract_u8x64_lane_i64x4<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u16x32>)
		{
			return EmuSIMD::Funcs::extract_u16x32_lane_i64x4<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u32x16>)
		{
			return EmuSIMD::Funcs::extract_u32x16_lane_i64x4<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u64x8>)
		{
			return EmuSIMD::Funcs::extract_u64x8_lane_i64x4<LaneIndex_>(std::forward<In_>(in_));
		}
		else
		{
			static_assert
			(
				EmuCore::TMP::get_false<in_uq>(),
				"Attempted to extract a lane from a SIMD register as a i64x4 register via EmuSIMD helpers, but the provided input register is not supported for such an extraction."
			);
		}
	}

	template<std::size_t LaneIndex_, class In_>
	[[nodiscard]] constexpr inline EmuSIMD::i64x8 _extract_lane_i64x8_prevalidated(In_&& in_)
	{
		using in_uq = typename EmuCore::TMP::remove_ref_cv<In_>::type;
		if constexpr (std::is_same_v<in_uq, EmuSIMD::f32x16>)
		{
			return EmuSIMD::Funcs::extract_f32x16_lane_i64x8<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::f64x8>)
		{
			return EmuSIMD::Funcs::extract_f64x8_lane_i64x8<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i512_generic>)
		{
			return EmuSIMD::Funcs::extract_i32x16_lane_i64x8<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i8x64>)
		{
			return EmuSIMD::Funcs::extract_i8x64_lane_i64x8<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i16x32>)
		{
			return EmuSIMD::Funcs::extract_i16x32_lane_i64x8<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i32x16>)
		{
			return EmuSIMD::Funcs::extract_i32x16_lane_i64x8<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i64x8>)
		{
			return EmuSIMD::Funcs::extract_i64x8_lane_i64x8<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u8x64>)
		{
			return EmuSIMD::Funcs::extract_u8x64_lane_i64x8<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u16x32>)
		{
			return EmuSIMD::Funcs::extract_u16x32_lane_i64x8<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u32x16>)
		{
			return EmuSIMD::Funcs::extract_u32x16_lane_i64x8<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u64x8>)
		{
			return EmuSIMD::Funcs::extract_u64x8_lane_i64x8<LaneIndex_>(std::forward<In_>(in_));
		}
		else
		{
			static_assert
			(
				EmuCore::TMP::get_false<in_uq>(),
				"Attempted to extract a lane from a SIMD register as a i64x8 register via EmuSIMD helpers, but the provided input register is not supported for such an extraction."
			);
		}
	}

	template<std::size_t LaneIndex_, class In_>
	[[nodiscard]] constexpr inline EmuSIMD::u8x16 _extract_lane_u8x16_prevalidated(In_&& in_)
	{
		using in_uq = typename EmuCore::TMP::remove_ref_cv<In_>::type;
		if constexpr (std::is_same_v<in_uq, EmuSIMD::f32x4>)
		{
			return EmuSIMD::Funcs::extract_f32x4_lane_u8x16<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::f32x8>)
		{
			return EmuSIMD::Funcs::extract_f32x8_lane_u8x16<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::f32x16>)
		{
			return EmuSIMD::Funcs::extract_f32x16_lane_u8x16<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::f64x2>)
		{
			return EmuSIMD::Funcs::extract_f64x2_lane_u8x16<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::f64x4>)
		{
			return EmuSIMD::Funcs::extract_f64x4_lane_u8x16<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::f64x8>)
		{
			return EmuSIMD::Funcs::extract_f64x8_lane_u8x16<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i128_generic>)
		{
			return EmuSIMD::Funcs::extract_i32x4_lane_u8x16<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i256_generic>)
		{
			return EmuSIMD::Funcs::extract_i32x8_lane_u8x16<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i512_generic>)
		{
			return EmuSIMD::Funcs::extract_i32x16_lane_u8x16<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i8x16>)
		{
			return EmuSIMD::Funcs::extract_i8x16_lane_u8x16<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i16x8>)
		{
			return EmuSIMD::Funcs::extract_i16x8_lane_u8x16<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i32x4>)
		{
			return EmuSIMD::Funcs::extract_i32x4_lane_u8x16<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i64x2>)
		{
			return EmuSIMD::Funcs::extract_i64x2_lane_u8x16<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i8x32>)
		{
			return EmuSIMD::Funcs::extract_i8x32_lane_u8x16<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i16x16>)
		{
			return EmuSIMD::Funcs::extract_i16x16_lane_u8x16<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i32x8>)
		{
			return EmuSIMD::Funcs::extract_i32x8_lane_u8x16<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i64x4>)
		{
			return EmuSIMD::Funcs::extract_i64x4_lane_u8x16<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i8x64>)
		{
			return EmuSIMD::Funcs::extract_i8x64_lane_u8x16<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i16x32>)
		{
			return EmuSIMD::Funcs::extract_i16x32_lane_u8x16<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i32x16>)
		{
			return EmuSIMD::Funcs::extract_i32x16_lane_u8x16<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i64x8>)
		{
			return EmuSIMD::Funcs::extract_i64x8_lane_u8x16<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u8x16>)
		{
			return EmuSIMD::Funcs::extract_u8x16_lane_u8x16<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u16x8>)
		{
			return EmuSIMD::Funcs::extract_u16x8_lane_u8x16<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u32x4>)
		{
			return EmuSIMD::Funcs::extract_u32x4_lane_u8x16<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u64x2>)
		{
			return EmuSIMD::Funcs::extract_u64x2_lane_u8x16<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u8x32>)
		{
			return EmuSIMD::Funcs::extract_u8x32_lane_u8x16<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u16x16>)
		{
			return EmuSIMD::Funcs::extract_u16x16_lane_u8x16<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u32x8>)
		{
			return EmuSIMD::Funcs::extract_u32x8_lane_u8x16<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u64x4>)
		{
			return EmuSIMD::Funcs::extract_u64x4_lane_u8x16<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u8x64>)
		{
			return EmuSIMD::Funcs::extract_u8x64_lane_u8x16<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u16x32>)
		{
			return EmuSIMD::Funcs::extract_u16x32_lane_u8x16<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u32x16>)
		{
			return EmuSIMD::Funcs::extract_u32x16_lane_u8x16<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u64x8>)
		{
			return EmuSIMD::Funcs::extract_u64x8_lane_u8x16<LaneIndex_>(in_);
		}
		else
		{
			static_assert
			(
				EmuCore::TMP::get_false<in_uq>(),
				"Attempted to extract a lane from a SIMD register as a u8x16 register via EmuSIMD helpers, but the provided input register is not supported for such an extraction."
			);
		}
	}

	template<std::size_t LaneIndex_, class In_>
	[[nodiscard]] constexpr inline EmuSIMD::u8x32 _extract_lane_u8x32_prevalidated(In_&& in_)
	{
		using in_uq = typename EmuCore::TMP::remove_ref_cv<In_>::type;
		if constexpr (std::is_same_v<in_uq, EmuSIMD::f32x8>)
		{
			return EmuSIMD::Funcs::extract_f32x8_lane_u8x32<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::f32x16>)
		{
			return EmuSIMD::Funcs::extract_f32x16_lane_u8x32<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::f64x4>)
		{
			return EmuSIMD::Funcs::extract_f64x4_lane_u8x32<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::f64x8>)
		{
			return EmuSIMD::Funcs::extract_f64x8_lane_u8x32<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i256_generic>)
		{
			return EmuSIMD::Funcs::extract_i32x8_lane_u8x32<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i512_generic>)
		{
			return EmuSIMD::Funcs::extract_i32x16_lane_u8x32<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i8x32>)
		{
			return EmuSIMD::Funcs::extract_i8x32_lane_u8x32<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i16x16>)
		{
			return EmuSIMD::Funcs::extract_i16x16_lane_u8x32<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i32x8>)
		{
			return EmuSIMD::Funcs::extract_i32x8_lane_u8x32<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i64x4>)
		{
			return EmuSIMD::Funcs::extract_i64x4_lane_u8x32<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i8x64>)
		{
			return EmuSIMD::Funcs::extract_i8x64_lane_u8x32<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i16x32>)
		{
			return EmuSIMD::Funcs::extract_i16x32_lane_u8x32<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i32x16>)
		{
			return EmuSIMD::Funcs::extract_i32x16_lane_u8x32<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i64x8>)
		{
			return EmuSIMD::Funcs::extract_i64x8_lane_u8x32<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u8x32>)
		{
			return EmuSIMD::Funcs::extract_u8x32_lane_u8x32<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u16x16>)
		{
			return EmuSIMD::Funcs::extract_u16x16_lane_u8x32<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u32x8>)
		{
			return EmuSIMD::Funcs::extract_u32x8_lane_u8x32<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u64x4>)
		{
			return EmuSIMD::Funcs::extract_u64x4_lane_u8x32<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u8x64>)
		{
			return EmuSIMD::Funcs::extract_u8x64_lane_u8x32<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u16x32>)
		{
			return EmuSIMD::Funcs::extract_u16x32_lane_u8x32<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u32x16>)
		{
			return EmuSIMD::Funcs::extract_u32x16_lane_u8x32<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u64x8>)
		{
			return EmuSIMD::Funcs::extract_u64x8_lane_u8x32<LaneIndex_>(std::forward<In_>(in_));
		}
		else
		{
			static_assert
			(
				EmuCore::TMP::get_false<in_uq>(),
				"Attempted to extract a lane from a SIMD register as a u8x32 register via EmuSIMD helpers, but the provided input register is not supported for such an extraction."
			);
		}
	}

	template<std::size_t LaneIndex_, class In_>
	[[nodiscard]] constexpr inline EmuSIMD::u8x64 _extract_lane_u8x64_prevalidated(In_&& in_)
	{
		using in_uq = typename EmuCore::TMP::remove_ref_cv<In_>::type;
		if constexpr (std::is_same_v<in_uq, EmuSIMD::f32x16>)
		{
			return EmuSIMD::Funcs::extract_f32x16_lane_u8x64<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::f64x8>)
		{
			return EmuSIMD::Funcs::extract_f64x8_lane_u8x64<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i512_generic>)
		{
			return EmuSIMD::Funcs::extract_i32x16_lane_u8x64<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i8x64>)
		{
			return EmuSIMD::Funcs::extract_i8x64_lane_u8x64<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i16x32>)
		{
			return EmuSIMD::Funcs::extract_i16x32_lane_u8x64<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i32x16>)
		{
			return EmuSIMD::Funcs::extract_i32x16_lane_u8x64<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i64x8>)
		{
			return EmuSIMD::Funcs::extract_i64x8_lane_u8x64<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u8x64>)
		{
			return EmuSIMD::Funcs::extract_u8x64_lane_u8x64<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u16x32>)
		{
			return EmuSIMD::Funcs::extract_u16x32_lane_u8x64<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u32x16>)
		{
			return EmuSIMD::Funcs::extract_u32x16_lane_u8x64<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u64x8>)
		{
			return EmuSIMD::Funcs::extract_u64x8_lane_u8x64<LaneIndex_>(std::forward<In_>(in_));
		}
		else
		{
			static_assert
			(
				EmuCore::TMP::get_false<in_uq>(),
				"Attempted to extract a lane from a SIMD register as a u8x64 register via EmuSIMD helpers, but the provided input register is not supported for such an extraction."
			);
		}
	}

	template<std::size_t LaneIndex_, class In_>
	[[nodiscard]] constexpr inline EmuSIMD::u16x8 _extract_lane_u16x8_prevalidated(In_&& in_)
	{
		using in_uq = typename EmuCore::TMP::remove_ref_cv<In_>::type;
		if constexpr (std::is_same_v<in_uq, EmuSIMD::f32x4>)
		{
			return EmuSIMD::Funcs::extract_f32x4_lane_u16x8<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::f32x8>)
		{
			return EmuSIMD::Funcs::extract_f32x8_lane_u16x8<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::f32x16>)
		{
			return EmuSIMD::Funcs::extract_f32x16_lane_u16x8<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::f64x2>)
		{
			return EmuSIMD::Funcs::extract_f64x2_lane_u16x8<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::f64x4>)
		{
			return EmuSIMD::Funcs::extract_f64x4_lane_u16x8<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::f64x8>)
		{
			return EmuSIMD::Funcs::extract_f64x8_lane_u16x8<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i128_generic>)
		{
			return EmuSIMD::Funcs::extract_i32x4_lane_u16x8<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i256_generic>)
		{
			return EmuSIMD::Funcs::extract_i32x8_lane_u16x8<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i512_generic>)
		{
			return EmuSIMD::Funcs::extract_i32x16_lane_u16x8<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i8x16>)
		{
			return EmuSIMD::Funcs::extract_i8x16_lane_u16x8<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i16x8>)
		{
			return EmuSIMD::Funcs::extract_i16x8_lane_u16x8<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i32x4>)
		{
			return EmuSIMD::Funcs::extract_i32x4_lane_u16x8<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i64x2>)
		{
			return EmuSIMD::Funcs::extract_i64x2_lane_u16x8<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i8x32>)
		{
			return EmuSIMD::Funcs::extract_i8x32_lane_u16x8<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i16x16>)
		{
			return EmuSIMD::Funcs::extract_i16x16_lane_u16x8<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i32x8>)
		{
			return EmuSIMD::Funcs::extract_i32x8_lane_u16x8<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i64x4>)
		{
			return EmuSIMD::Funcs::extract_i64x4_lane_u16x8<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i8x64>)
		{
			return EmuSIMD::Funcs::extract_i8x64_lane_u16x8<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i16x32>)
		{
			return EmuSIMD::Funcs::extract_i16x32_lane_u16x8<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i32x16>)
		{
			return EmuSIMD::Funcs::extract_i32x16_lane_u16x8<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i64x8>)
		{
			return EmuSIMD::Funcs::extract_i64x8_lane_u16x8<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u8x16>)
		{
			return EmuSIMD::Funcs::extract_u8x16_lane_u16x8<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u16x8>)
		{
			return EmuSIMD::Funcs::extract_u16x8_lane_u16x8<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u32x4>)
		{
			return EmuSIMD::Funcs::extract_u32x4_lane_u16x8<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u64x2>)
		{
			return EmuSIMD::Funcs::extract_u64x2_lane_u16x8<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u8x32>)
		{
			return EmuSIMD::Funcs::extract_u8x32_lane_u16x8<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u16x16>)
		{
			return EmuSIMD::Funcs::extract_u16x16_lane_u16x8<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u32x8>)
		{
			return EmuSIMD::Funcs::extract_u32x8_lane_u16x8<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u64x4>)
		{
			return EmuSIMD::Funcs::extract_u64x4_lane_u16x8<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u8x64>)
		{
			return EmuSIMD::Funcs::extract_u8x64_lane_u16x8<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u16x32>)
		{
			return EmuSIMD::Funcs::extract_u16x32_lane_u16x8<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u32x16>)
		{
			return EmuSIMD::Funcs::extract_u32x16_lane_u16x8<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u64x8>)
		{
			return EmuSIMD::Funcs::extract_u64x8_lane_u16x8<LaneIndex_>(in_);
		}
		else
		{
			static_assert
			(
				EmuCore::TMP::get_false<in_uq>(),
				"Attempted to extract a lane from a SIMD register as a u16x8 register via EmuSIMD helpers, but the provided input register is not supported for such an extraction."
			);
		}
	}

	template<std::size_t LaneIndex_, class In_>
	[[nodiscard]] constexpr inline EmuSIMD::u16x16 _extract_lane_u16x16_prevalidated(In_&& in_)
	{
		using in_uq = typename EmuCore::TMP::remove_ref_cv<In_>::type;
		if constexpr (std::is_same_v<in_uq, EmuSIMD::f32x8>)
		{
			return EmuSIMD::Funcs::extract_f32x8_lane_u16x16<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::f32x16>)
		{
			return EmuSIMD::Funcs::extract_f32x16_lane_u16x16<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::f64x4>)
		{
			return EmuSIMD::Funcs::extract_f64x4_lane_u16x16<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::f64x8>)
		{
			return EmuSIMD::Funcs::extract_f64x8_lane_u16x16<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i256_generic>)
		{
			return EmuSIMD::Funcs::extract_i32x8_lane_u16x16<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i512_generic>)
		{
			return EmuSIMD::Funcs::extract_i32x16_lane_u16x16<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i8x32>)
		{
			return EmuSIMD::Funcs::extract_i8x32_lane_u16x16<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i16x16>)
		{
			return EmuSIMD::Funcs::extract_i16x16_lane_u16x16<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i32x8>)
		{
			return EmuSIMD::Funcs::extract_i32x8_lane_u16x16<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i64x4>)
		{
			return EmuSIMD::Funcs::extract_i64x4_lane_u16x16<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i8x64>)
		{
			return EmuSIMD::Funcs::extract_i8x64_lane_u16x16<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i16x32>)
		{
			return EmuSIMD::Funcs::extract_i16x32_lane_u16x16<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i32x16>)
		{
			return EmuSIMD::Funcs::extract_i32x16_lane_u16x16<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i64x8>)
		{
			return EmuSIMD::Funcs::extract_i64x8_lane_u16x16<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u8x32>)
		{
			return EmuSIMD::Funcs::extract_u8x32_lane_u16x16<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u16x16>)
		{
			return EmuSIMD::Funcs::extract_u16x16_lane_u16x16<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u32x8>)
		{
			return EmuSIMD::Funcs::extract_u32x8_lane_u16x16<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u64x4>)
		{
			return EmuSIMD::Funcs::extract_u64x4_lane_u16x16<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u8x64>)
		{
			return EmuSIMD::Funcs::extract_u8x64_lane_u16x16<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u16x32>)
		{
			return EmuSIMD::Funcs::extract_u16x32_lane_u16x16<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u32x16>)
		{
			return EmuSIMD::Funcs::extract_u32x16_lane_u16x16<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u64x8>)
		{
			return EmuSIMD::Funcs::extract_u64x8_lane_u16x16<LaneIndex_>(std::forward<In_>(in_));
		}
		else
		{
			static_assert
			(
				EmuCore::TMP::get_false<in_uq>(),
				"Attempted to extract a lane from a SIMD register as a u16x16 register via EmuSIMD helpers, but the provided input register is not supported for such an extraction."
			);
		}
	}

	template<std::size_t LaneIndex_, class In_>
	[[nodiscard]] constexpr inline EmuSIMD::u16x32 _extract_lane_u16x32_prevalidated(In_&& in_)
	{
		using in_uq = typename EmuCore::TMP::remove_ref_cv<In_>::type;
		if constexpr (std::is_same_v<in_uq, EmuSIMD::f32x16>)
		{
			return EmuSIMD::Funcs::extract_f32x16_lane_u16x32<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::f64x8>)
		{
			return EmuSIMD::Funcs::extract_f64x8_lane_u16x32<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i512_generic>)
		{
			return EmuSIMD::Funcs::extract_i32x16_lane_u16x32<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i8x64>)
		{
			return EmuSIMD::Funcs::extract_i8x64_lane_u16x32<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i16x32>)
		{
			return EmuSIMD::Funcs::extract_i16x32_lane_u16x32<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i32x16>)
		{
			return EmuSIMD::Funcs::extract_i32x16_lane_u16x32<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i64x8>)
		{
			return EmuSIMD::Funcs::extract_i64x8_lane_u16x32<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u8x64>)
		{
			return EmuSIMD::Funcs::extract_u8x64_lane_u16x32<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u16x32>)
		{
			return EmuSIMD::Funcs::extract_u16x32_lane_u16x32<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u32x16>)
		{
			return EmuSIMD::Funcs::extract_u32x16_lane_u16x32<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u64x8>)
		{
			return EmuSIMD::Funcs::extract_u64x8_lane_u16x32<LaneIndex_>(std::forward<In_>(in_));
		}
		else
		{
			static_assert
			(
				EmuCore::TMP::get_false<in_uq>(),
				"Attempted to extract a lane from a SIMD register as a u16x32 register via EmuSIMD helpers, but the provided input register is not supported for such an extraction."
			);
		}
	}

	template<std::size_t LaneIndex_, class In_>
	[[nodiscard]] constexpr inline EmuSIMD::u32x4 _extract_lane_u32x4_prevalidated(In_&& in_)
	{
		using in_uq = typename EmuCore::TMP::remove_ref_cv<In_>::type;
		if constexpr (std::is_same_v<in_uq, EmuSIMD::f32x4>)
		{
			return EmuSIMD::Funcs::extract_f32x4_lane_u32x4<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::f32x8>)
		{
			return EmuSIMD::Funcs::extract_f32x8_lane_u32x4<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::f32x16>)
		{
			return EmuSIMD::Funcs::extract_f32x16_lane_u32x4<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::f64x2>)
		{
			return EmuSIMD::Funcs::extract_f64x2_lane_u32x4<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::f64x4>)
		{
			return EmuSIMD::Funcs::extract_f64x4_lane_u32x4<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::f64x8>)
		{
			return EmuSIMD::Funcs::extract_f64x8_lane_u32x4<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i128_generic>)
		{
			return EmuSIMD::Funcs::extract_i32x4_lane_u32x4<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i256_generic>)
		{
			return EmuSIMD::Funcs::extract_i32x8_lane_u32x4<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i512_generic>)
		{
			return EmuSIMD::Funcs::extract_i32x16_lane_u32x4<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i8x16>)
		{
			return EmuSIMD::Funcs::extract_i8x16_lane_u32x4<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i16x8>)
		{
			return EmuSIMD::Funcs::extract_i16x8_lane_u32x4<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i32x4>)
		{
			return EmuSIMD::Funcs::extract_i32x4_lane_u32x4<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i64x2>)
		{
			return EmuSIMD::Funcs::extract_i64x2_lane_u32x4<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i8x32>)
		{
			return EmuSIMD::Funcs::extract_i8x32_lane_u32x4<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i16x16>)
		{
			return EmuSIMD::Funcs::extract_i16x16_lane_u32x4<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i32x8>)
		{
			return EmuSIMD::Funcs::extract_i32x8_lane_u32x4<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i64x4>)
		{
			return EmuSIMD::Funcs::extract_i64x4_lane_u32x4<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i8x64>)
		{
			return EmuSIMD::Funcs::extract_i8x64_lane_u32x4<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i16x32>)
		{
			return EmuSIMD::Funcs::extract_i16x32_lane_u32x4<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i32x16>)
		{
			return EmuSIMD::Funcs::extract_i32x16_lane_u32x4<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i64x8>)
		{
			return EmuSIMD::Funcs::extract_i64x8_lane_u32x4<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u8x16>)
		{
			return EmuSIMD::Funcs::extract_u8x16_lane_u32x4<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u16x8>)
		{
			return EmuSIMD::Funcs::extract_u16x8_lane_u32x4<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u32x4>)
		{
			return EmuSIMD::Funcs::extract_u32x4_lane_u32x4<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u64x2>)
		{
			return EmuSIMD::Funcs::extract_u64x2_lane_u32x4<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u8x32>)
		{
			return EmuSIMD::Funcs::extract_u8x32_lane_u32x4<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u16x16>)
		{
			return EmuSIMD::Funcs::extract_u16x16_lane_u32x4<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u32x8>)
		{
			return EmuSIMD::Funcs::extract_u32x8_lane_u32x4<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u64x4>)
		{
			return EmuSIMD::Funcs::extract_u64x4_lane_u32x4<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u8x64>)
		{
			return EmuSIMD::Funcs::extract_u8x64_lane_u32x4<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u16x32>)
		{
			return EmuSIMD::Funcs::extract_u16x32_lane_u32x4<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u32x16>)
		{
			return EmuSIMD::Funcs::extract_u32x16_lane_u32x4<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u64x8>)
		{
			return EmuSIMD::Funcs::extract_u64x8_lane_u32x4<LaneIndex_>(in_);
		}
		else
		{
			static_assert
			(
				EmuCore::TMP::get_false<in_uq>(),
				"Attempted to extract a lane from a SIMD register as a u32x4 register via EmuSIMD helpers, but the provided input register is not supported for such an extraction."
			);
		}
	}

	template<std::size_t LaneIndex_, class In_>
	[[nodiscard]] constexpr inline EmuSIMD::u32x8 _extract_lane_u32x8_prevalidated(In_&& in_)
	{
		using in_uq = typename EmuCore::TMP::remove_ref_cv<In_>::type;
		if constexpr (std::is_same_v<in_uq, EmuSIMD::f32x8>)
		{
			return EmuSIMD::Funcs::extract_f32x8_lane_u32x8<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::f32x16>)
		{
			return EmuSIMD::Funcs::extract_f32x16_lane_u32x8<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::f64x4>)
		{
			return EmuSIMD::Funcs::extract_f64x4_lane_u32x8<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::f64x8>)
		{
			return EmuSIMD::Funcs::extract_f64x8_lane_u32x8<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i256_generic>)
		{
			return EmuSIMD::Funcs::extract_i32x8_lane_u32x8<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i512_generic>)
		{
			return EmuSIMD::Funcs::extract_i32x16_lane_u32x8<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i8x32>)
		{
			return EmuSIMD::Funcs::extract_i8x32_lane_u32x8<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i16x16>)
		{
			return EmuSIMD::Funcs::extract_i16x16_lane_u32x8<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i32x8>)
		{
			return EmuSIMD::Funcs::extract_i32x8_lane_u32x8<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i64x4>)
		{
			return EmuSIMD::Funcs::extract_i64x4_lane_u32x8<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i8x64>)
		{
			return EmuSIMD::Funcs::extract_i8x64_lane_u32x8<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i16x32>)
		{
			return EmuSIMD::Funcs::extract_i16x32_lane_u32x8<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i32x16>)
		{
			return EmuSIMD::Funcs::extract_i32x16_lane_u32x8<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i64x8>)
		{
			return EmuSIMD::Funcs::extract_i64x8_lane_u32x8<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u8x32>)
		{
			return EmuSIMD::Funcs::extract_u8x32_lane_u32x8<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u16x16>)
		{
			return EmuSIMD::Funcs::extract_u16x16_lane_u32x8<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u32x8>)
		{
			return EmuSIMD::Funcs::extract_u32x8_lane_u32x8<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u64x4>)
		{
			return EmuSIMD::Funcs::extract_u64x4_lane_u32x8<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u8x64>)
		{
			return EmuSIMD::Funcs::extract_u8x64_lane_u32x8<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u16x32>)
		{
			return EmuSIMD::Funcs::extract_u16x32_lane_u32x8<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u32x16>)
		{
			return EmuSIMD::Funcs::extract_u32x16_lane_u32x8<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u64x8>)
		{
			return EmuSIMD::Funcs::extract_u64x8_lane_u32x8<LaneIndex_>(std::forward<In_>(in_));
		}
		else
		{
			static_assert
			(
				EmuCore::TMP::get_false<in_uq>(),
				"Attempted to extract a lane from a SIMD register as a u32x8 register via EmuSIMD helpers, but the provided input register is not supported for such an extraction."
			);
		}
	}

	template<std::size_t LaneIndex_, class In_>
	[[nodiscard]] constexpr inline EmuSIMD::u32x16 _extract_lane_u32x16_prevalidated(In_&& in_)
	{
		using in_uq = typename EmuCore::TMP::remove_ref_cv<In_>::type;
		if constexpr (std::is_same_v<in_uq, EmuSIMD::f32x16>)
		{
			return EmuSIMD::Funcs::extract_f32x16_lane_u32x16<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::f64x8>)
		{
			return EmuSIMD::Funcs::extract_f64x8_lane_u32x16<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i512_generic>)
		{
			return EmuSIMD::Funcs::extract_i32x16_lane_u32x16<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i8x64>)
		{
			return EmuSIMD::Funcs::extract_i8x64_lane_u32x16<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i16x32>)
		{
			return EmuSIMD::Funcs::extract_i16x32_lane_u32x16<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i32x16>)
		{
			return EmuSIMD::Funcs::extract_i32x16_lane_u32x16<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i64x8>)
		{
			return EmuSIMD::Funcs::extract_i64x8_lane_u32x16<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u8x64>)
		{
			return EmuSIMD::Funcs::extract_u8x64_lane_u32x16<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u16x32>)
		{
			return EmuSIMD::Funcs::extract_u16x32_lane_u32x16<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u32x16>)
		{
			return EmuSIMD::Funcs::extract_u32x16_lane_u32x16<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u64x8>)
		{
			return EmuSIMD::Funcs::extract_u64x8_lane_u32x16<LaneIndex_>(std::forward<In_>(in_));
		}
		else
		{
			static_assert
			(
				EmuCore::TMP::get_false<in_uq>(),
				"Attempted to extract a lane from a SIMD register as a u32x16 register via EmuSIMD helpers, but the provided input register is not supported for such an extraction."
			);
		}
	}

	template<std::size_t LaneIndex_, class In_>
	[[nodiscard]] constexpr inline EmuSIMD::u64x2 _extract_lane_u64x2_prevalidated(In_&& in_)
	{
		using in_uq = typename EmuCore::TMP::remove_ref_cv<In_>::type;
		if constexpr (std::is_same_v<in_uq, EmuSIMD::f32x4>)
		{
			return EmuSIMD::Funcs::extract_f32x4_lane_u64x2<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::f32x8>)
		{
			return EmuSIMD::Funcs::extract_f32x8_lane_u64x2<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::f32x16>)
		{
			return EmuSIMD::Funcs::extract_f32x16_lane_u64x2<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::f64x2>)
		{
			return EmuSIMD::Funcs::extract_f64x2_lane_u64x2<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::f64x4>)
		{
			return EmuSIMD::Funcs::extract_f64x4_lane_u64x2<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::f64x8>)
		{
			return EmuSIMD::Funcs::extract_f64x8_lane_u64x2<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i128_generic>)
		{
			return EmuSIMD::Funcs::extract_i32x4_lane_u64x2<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i256_generic>)
		{
			return EmuSIMD::Funcs::extract_i32x8_lane_u64x2<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i512_generic>)
		{
			return EmuSIMD::Funcs::extract_i32x16_lane_u64x2<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i8x16>)
		{
			return EmuSIMD::Funcs::extract_i8x16_lane_u64x2<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i16x8>)
		{
			return EmuSIMD::Funcs::extract_i16x8_lane_u64x2<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i32x4>)
		{
			return EmuSIMD::Funcs::extract_i32x4_lane_u64x2<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i64x2>)
		{
			return EmuSIMD::Funcs::extract_i64x2_lane_u64x2<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i8x32>)
		{
			return EmuSIMD::Funcs::extract_i8x32_lane_u64x2<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i16x16>)
		{
			return EmuSIMD::Funcs::extract_i16x16_lane_u64x2<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i32x8>)
		{
			return EmuSIMD::Funcs::extract_i32x8_lane_u64x2<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i64x4>)
		{
			return EmuSIMD::Funcs::extract_i64x4_lane_u64x2<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i8x64>)
		{
			return EmuSIMD::Funcs::extract_i8x64_lane_u64x2<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i16x32>)
		{
			return EmuSIMD::Funcs::extract_i16x32_lane_u64x2<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i32x16>)
		{
			return EmuSIMD::Funcs::extract_i32x16_lane_u64x2<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i64x8>)
		{
			return EmuSIMD::Funcs::extract_i64x8_lane_u64x2<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u8x16>)
		{
			return EmuSIMD::Funcs::extract_u8x16_lane_u64x2<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u16x8>)
		{
			return EmuSIMD::Funcs::extract_u16x8_lane_u64x2<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u32x4>)
		{
			return EmuSIMD::Funcs::extract_u32x4_lane_u64x2<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u64x2>)
		{
			return EmuSIMD::Funcs::extract_u64x2_lane_u64x2<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u8x32>)
		{
			return EmuSIMD::Funcs::extract_u8x32_lane_u64x2<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u16x16>)
		{
			return EmuSIMD::Funcs::extract_u16x16_lane_u64x2<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u32x8>)
		{
			return EmuSIMD::Funcs::extract_u32x8_lane_u64x2<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u64x4>)
		{
			return EmuSIMD::Funcs::extract_u64x4_lane_u64x2<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u8x64>)
		{
			return EmuSIMD::Funcs::extract_u8x64_lane_u64x2<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u16x32>)
		{
			return EmuSIMD::Funcs::extract_u16x32_lane_u64x2<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u32x16>)
		{
			return EmuSIMD::Funcs::extract_u32x16_lane_u64x2<LaneIndex_>(in_);
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u64x8>)
		{
			return EmuSIMD::Funcs::extract_u64x8_lane_u64x2<LaneIndex_>(in_);
		}
		else
		{
			static_assert
			(
				EmuCore::TMP::get_false<in_uq>(),
				"Attempted to extract a lane from a SIMD register as a u64x2 register via EmuSIMD helpers, but the provided input register is not supported for such an extraction."
			);
		}
	}

	template<std::size_t LaneIndex_, class In_>
	[[nodiscard]] constexpr inline EmuSIMD::u64x4 _extract_lane_u64x4_prevalidated(In_&& in_)
	{
		using in_uq = typename EmuCore::TMP::remove_ref_cv<In_>::type;
		if constexpr (std::is_same_v<in_uq, EmuSIMD::f32x8>)
		{
			return EmuSIMD::Funcs::extract_f32x8_lane_u64x4<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::f32x16>)
		{
			return EmuSIMD::Funcs::extract_f32x16_lane_u64x4<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::f64x4>)
		{
			return EmuSIMD::Funcs::extract_f64x4_lane_u64x4<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::f64x8>)
		{
			return EmuSIMD::Funcs::extract_f64x8_lane_u64x4<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i256_generic>)
		{
			return EmuSIMD::Funcs::extract_i32x8_lane_u64x4<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i512_generic>)
		{
			return EmuSIMD::Funcs::extract_i32x16_lane_u64x4<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i8x32>)
		{
			return EmuSIMD::Funcs::extract_i8x32_lane_u64x4<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i16x16>)
		{
			return EmuSIMD::Funcs::extract_i16x16_lane_u64x4<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i32x8>)
		{
			return EmuSIMD::Funcs::extract_i32x8_lane_u64x4<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i64x4>)
		{
			return EmuSIMD::Funcs::extract_i64x4_lane_u64x4<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i8x64>)
		{
			return EmuSIMD::Funcs::extract_i8x64_lane_u64x4<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i16x32>)
		{
			return EmuSIMD::Funcs::extract_i16x32_lane_u64x4<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i32x16>)
		{
			return EmuSIMD::Funcs::extract_i32x16_lane_u64x4<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i64x8>)
		{
			return EmuSIMD::Funcs::extract_i64x8_lane_u64x4<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u8x32>)
		{
			return EmuSIMD::Funcs::extract_u8x32_lane_u64x4<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u16x16>)
		{
			return EmuSIMD::Funcs::extract_u16x16_lane_u64x4<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u32x8>)
		{
			return EmuSIMD::Funcs::extract_u32x8_lane_u64x4<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u64x4>)
		{
			return EmuSIMD::Funcs::extract_u64x4_lane_u64x4<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u8x64>)
		{
			return EmuSIMD::Funcs::extract_u8x64_lane_u64x4<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u16x32>)
		{
			return EmuSIMD::Funcs::extract_u16x32_lane_u64x4<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u32x16>)
		{
			return EmuSIMD::Funcs::extract_u32x16_lane_u64x4<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u64x8>)
		{
			return EmuSIMD::Funcs::extract_u64x8_lane_u64x4<LaneIndex_>(std::forward<In_>(in_));
		}
		else
		{
			static_assert
			(
				EmuCore::TMP::get_false<in_uq>(),
				"Attempted to extract a lane from a SIMD register as a u64x4 register via EmuSIMD helpers, but the provided input register is not supported for such an extraction."
			);
		}
	}

	template<std::size_t LaneIndex_, class In_>
	[[nodiscard]] constexpr inline EmuSIMD::u64x8 _extract_lane_u64x8_prevalidated(In_&& in_)
	{
		using in_uq = typename EmuCore::TMP::remove_ref_cv<In_>::type;
		if constexpr (std::is_same_v<in_uq, EmuSIMD::f32x16>)
		{
			return EmuSIMD::Funcs::extract_f32x16_lane_u64x8<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::f64x8>)
		{
			return EmuSIMD::Funcs::extract_f64x8_lane_u64x8<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i512_generic>)
		{
			return EmuSIMD::Funcs::extract_i32x16_lane_u64x8<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i8x64>)
		{
			return EmuSIMD::Funcs::extract_i8x64_lane_u64x8<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i16x32>)
		{
			return EmuSIMD::Funcs::extract_i16x32_lane_u64x8<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i32x16>)
		{
			return EmuSIMD::Funcs::extract_i32x16_lane_u64x8<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::i64x8>)
		{
			return EmuSIMD::Funcs::extract_i64x8_lane_u64x8<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u8x64>)
		{
			return EmuSIMD::Funcs::extract_u8x64_lane_u64x8<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u16x32>)
		{
			return EmuSIMD::Funcs::extract_u16x32_lane_u64x8<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u32x16>)
		{
			return EmuSIMD::Funcs::extract_u32x16_lane_u64x8<LaneIndex_>(std::forward<In_>(in_));
		}
		else if constexpr (std::is_same_v<in_uq, EmuSIMD::u64x8>)
		{
			return EmuSIMD::Funcs::extract_u64x8_lane_u64x8<LaneIndex_>(std::forward<In_>(in_));
		}
		else
		{
			static_assert
			(
				EmuCore::TMP::get_false<in_uq>(),
				"Attempted to extract a lane from a SIMD register as a u64x8 register via EmuSIMD helpers, but the provided input register is not supported for such an extraction."
			);
		}
	}
}

#endif
