#ifndef EMU_SIMD_HELPERS_UNDERLYING_BLEND_H_INC_
#define EMU_SIMD_HELPERS_UNDERLYING_BLEND_H_INC_ 1

#include "_common_underlying_simd_template_helper_includes.h"
#include "../../../../../EmuCore/TMPHelpers/Values.h"

namespace EmuSIMD::_underlying_simd_helpers
{
	template<std::size_t PerElementWidthIfInt_ = 32, class Register_>
	[[nodiscard]] inline Register_ _blendv(Register_ a_, Register_ b_, Register_ mask_)
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			using namespace EmuSIMD::Funcs;
			if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x4>)
			{
				return blendv_f32x4(a_, b_, mask_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x8>)
			{
				return blendv_f32x8(a_, b_, mask_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x16>)
			{
				return blendv_f32x16(a_, b_, mask_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x2>)
			{
				return blendv_f64x2(a_, b_, mask_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x4>)
			{
				return blendv_f64x4(a_, b_, mask_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x8>)
			{
				return blendv_f64x8(a_, b_, mask_);
			}
			else if constexpr (EmuCore::TMP::is_any_comparison_true<std::is_same, register_type_uq, EmuSIMD::i128_generic, EmuSIMD::i256_generic, EmuSIMD::i512_generic>::value)
			{
				if constexpr (EmuSIMD::TMP::_assert_valid_simd_int_element_width<PerElementWidthIfInt_>())
				{
					if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i128_generic>)
					{
						if constexpr (PerElementWidthIfInt_ == 8)
						{
							return blendv_i8x16(a_, b_, mask_);
						}
						else if constexpr (PerElementWidthIfInt_ == 16)
						{
							return blendv_i16x8(a_, b_, mask_);
						}
						else if constexpr (PerElementWidthIfInt_ == 32)
						{
							return blendv_i32x4(a_, b_, mask_);
						}
						else if constexpr(PerElementWidthIfInt_ == 64)
						{
							return blendv_i64x2(a_, b_, mask_);
						}
						else
						{
							static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to execute a SIMD vectorwise blend (blendv) on a 128-bit generic integral register, but the provided bit-width per element is invalid.");
						}
					}
					else if constexpr(std::is_same_v<register_type_uq, EmuSIMD::i256_generic>)
					{
						if constexpr (PerElementWidthIfInt_ == 8)
						{
							return blendv_i8x32(a_, b_, mask_);
						}
						else if constexpr (PerElementWidthIfInt_ == 16)
						{
							return blendv_i16x16(a_, b_, mask_);
						}
						else if constexpr (PerElementWidthIfInt_ == 32)
						{
							return blendv_i32x8(a_, b_, mask_);
						}
						else if constexpr (PerElementWidthIfInt_ == 64)
						{
							return blendv_i64x4(a_, b_, mask_);
						}
						else
						{
							static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to execute a SIMD vectorwise blend (blendv) on a 256-bit generic integral register, but the provided bit-width per element is invalid.");
						}
					}
					else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i512_generic>)
					{
						if constexpr (PerElementWidthIfInt_ == 8)
						{
							return blendv_i8x64(a_, b_, mask_);
						}
						else if constexpr (PerElementWidthIfInt_ == 16)
						{
							return blendv_i16x32(a_, b_, mask_);
						}
						else if constexpr (PerElementWidthIfInt_ == 32)
						{
							return blendv_i32x16(a_, b_, mask_);
						}
						else if constexpr (PerElementWidthIfInt_ == 64)
						{
							return blendv_i64x8(a_, b_, mask_);
						}
						else
						{
							static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to execute a SIMD vectorwise blend (blendv) on a 512-bit generic integral register, but the provided bit-width per element is invalid.");
						}
					}
					else if constexpr(std::is_same_v<register_type_uq, EmuSIMD::i8x16>)
					{
						return blendv_i8x16(a_, b_, mask_);
					}
					else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u8x16>)
					{
						return blendv_u8x16(a_, b_, mask_);
					}
					else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i8x32>)
					{
						return blendv_i8x32(a_, b_, mask_);
					}
					else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u8x32>)
					{
						return blendv_u8x32(a_, b_, mask_);
					}
					else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i8x64>)
					{
						return blendv_i8x64(a_, b_, mask_);
					}
					else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u8x64>)
					{
						return blendv_u8x64(a_, b_, mask_);
					}
					else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i16x8>)
					{
						return blendv_i16x8(a_, b_, mask_);
					}
					else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u16x8>)
					{
						return blendv_u16x8(a_, b_, mask_);
					}
					else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i16x16>)
					{
						return blendv_i16x16(a_, b_, mask_);
					}
					else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u16x16>)
					{
						return blendv_u16x16(a_, b_, mask_);
					}
					else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i16x32>)
					{
						return blendv_i16x32(a_, b_, mask_);
					}
					else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u16x32>)
					{
						return blendv_u16x32(a_, b_, mask_);
					}
					else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i32x4>)
					{
						return blendv_i32x4(a_, b_, mask_);
					}
					else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u32x4>)
					{
						return blendv_u32x4(a_, b_, mask_);
					}
					else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i32x8>)
					{
						return blendv_i32x8(a_, b_, mask_);
					}
					else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u32x8>)
					{
						return blendv_u32x8(a_, b_, mask_);
					}
					else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i32x16>)
					{
						return blendv_i32x16(a_, b_, mask_);
					}
					else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u32x16>)
					{
						return blendv_u32x16(a_, b_, mask_);
					}
					else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i64x2>)
					{
						return blendv_i64x2(a_, b_, mask_);
					}
					else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u64x2>)
					{
						return blendv_u64x2(a_, b_, mask_);
					}
					else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i64x4>)
					{
						return blendv_i64x4(a_, b_, mask_);
					}
					else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u64x4>)
					{
						return blendv_u64x4(a_, b_, mask_);
					}
					else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i64x8>)
					{
						return blendv_i64x8(a_, b_, mask_);
					}
					else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u64x8>)
					{
						return blendv_u64x8(a_, b_, mask_);
					}
					else
					{
						static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to execute a SIMD vectorwise blend (blendv) on an integral register, but the passed register type is not supported for this operation.");
					}
				}
				else
				{
					static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to execute a SIMD vectorwise blend (blendv) on an integral register, but the bit-width per element is invalid.");
				}
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to execute a SIMD vectorwise blend (blendv), but the provided SIMD register is not supported for this operation.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to execute a SIMD vectorwise blend (blendv), but the provided Register_ type is not recognised as a supported SIMD register.");
		}
	}

	template<bool...IndexUsesB_, class Register_>
	[[nodiscard]] inline Register_ _blend(Register_ a_, Register_ b_)
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			constexpr std::size_t num_blend_args = sizeof...(IndexUsesB_);
			if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x4>)
			{
				if constexpr (num_blend_args == 4)
				{
					constexpr auto blend_mask = EmuSIMD::Funcs::make_reverse_blend_mask<IndexUsesB_...>();
					return EmuSIMD::Funcs::blend_f32x4<blend_mask>(a_, b_);
				}
				else
				{
					static_assert(EmuCore::TMP::get_false<std::size_t, num_blend_args>(), "Invalid number of boolean arguments passed to execute a f32x4 blend operation; expected 4.");
				}
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x8>)
			{
				if constexpr (num_blend_args == 8)
				{
					constexpr auto blend_mask = EmuSIMD::Funcs::make_reverse_blend_mask<IndexUsesB_...>();
					return EmuSIMD::Funcs::blend_f32x8<blend_mask>(a_, b_);
				}
				else
				{
					static_assert(EmuCore::TMP::get_false<std::size_t, num_blend_args>(), "Invalid number of boolean arguments passed to execute a f32x8 blend operation; expected 8.");
				}
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x16>)
			{
				if constexpr (num_blend_args == 16)
				{
					constexpr auto blend_mask = EmuSIMD::Funcs::make_reverse_blend_mask<IndexUsesB_...>();
					return EmuSIMD::Funcs::blend_f32x16<blend_mask>(a_, b_);
				}
				else
				{
					static_assert(EmuCore::TMP::get_false<std::size_t, num_blend_args>(), "Invalid number of boolean arguments passed to execute a f32x16 blend operation; expected 16.");
				}
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x2>)
			{
				if constexpr (num_blend_args == 2)
				{
					constexpr auto blend_mask = EmuSIMD::Funcs::make_reverse_blend_mask<IndexUsesB_...>();
					return EmuSIMD::Funcs::blend_f64x2<blend_mask>(a_, b_);
				}
				else
				{
					static_assert(EmuCore::TMP::get_false<std::size_t, num_blend_args>(), "Invalid number of boolean arguments passed to execute a f64x2 blend operation; expected 2.");
				}
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x4>)
			{
				if constexpr (num_blend_args == 4)
				{
					constexpr auto blend_mask = EmuSIMD::Funcs::make_reverse_blend_mask<IndexUsesB_...>();
					return EmuSIMD::Funcs::blend_f64x4<blend_mask>(a_, b_);
				}
				else
				{
					static_assert(EmuCore::TMP::get_false<std::size_t, num_blend_args>(), "Invalid number of boolean arguments passed to execute a f64x4 blend operation; expected 4.");
				}
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x8>)
			{
				if constexpr (num_blend_args == 8)
				{
					constexpr auto blend_mask = EmuSIMD::Funcs::make_reverse_blend_mask<IndexUsesB_...>();
					return EmuSIMD::Funcs::blend_f64x8<blend_mask>(a_, b_);
				}
				else
				{
					static_assert(EmuCore::TMP::get_false<std::size_t, num_blend_args>(), "Invalid number of boolean arguments passed to execute a f64x8 blend operation; expected 8.");
				}
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i128_generic>)
			{
				if constexpr (num_blend_args == 2)
				{
					constexpr auto blend_mask = EmuSIMD::Funcs::make_reverse_blend_mask<IndexUsesB_...>();
					return EmuSIMD::Funcs::blend_i64x2<blend_mask>(a_, b_);
				}
				else if constexpr (num_blend_args == 4)
				{
					constexpr auto blend_mask = EmuSIMD::Funcs::make_reverse_blend_mask<IndexUsesB_...>();
					return EmuSIMD::Funcs::blend_i32x4<blend_mask>(a_, b_);
				}
				else if constexpr (num_blend_args == 8)
				{
					constexpr auto blend_mask = EmuSIMD::Funcs::make_reverse_blend_mask<IndexUsesB_...>();
					return EmuSIMD::Funcs::blend_i16x8<blend_mask>(a_, b_);
				}
				else if constexpr (num_blend_args == 16)
				{
					constexpr auto blend_mask = EmuSIMD::Funcs::make_reverse_blend_mask<IndexUsesB_...>();
					return EmuSIMD::Funcs::blend_i8x16<blend_mask>(a_, b_);
				}
				else
				{
					static_assert(EmuCore::TMP::get_false<std::size_t, num_blend_args>(), "Invalid number of boolean arguments passed to execute a blend operation on a generic 128-bit integral SIMD register; expected one of: 16 [8-bit], 8 [16-bit], 4 [32-bit], 2 [64-bit].");
				}
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i256_generic>)
			{
				if constexpr (num_blend_args == 4)
				{
					constexpr auto blend_mask = EmuSIMD::Funcs::make_reverse_blend_mask<IndexUsesB_...>();
					return EmuSIMD::Funcs::blend_i64x4<blend_mask>(a_, b_);
				}
				else if constexpr (num_blend_args == 8)
				{
					constexpr auto blend_mask = EmuSIMD::Funcs::make_reverse_blend_mask<IndexUsesB_...>();
					return EmuSIMD::Funcs::blend_i32x8<blend_mask>(a_, b_);
				}
				else if constexpr (num_blend_args == 16)
				{
					constexpr auto blend_mask = EmuSIMD::Funcs::make_reverse_blend_mask<IndexUsesB_...>();
					return EmuSIMD::Funcs::blend_i16x16<blend_mask>(a_, b_);
				}
				else if constexpr (num_blend_args == 32)
				{
					constexpr auto blend_mask = EmuSIMD::Funcs::make_reverse_blend_mask<IndexUsesB_...>();
					return EmuSIMD::Funcs::blend_i8x32<blend_mask>(a_, b_);
				}
				else
				{
					static_assert(EmuCore::TMP::get_false<std::size_t, num_blend_args>(), "Invalid number of boolean arguments passed to execute a blend operation on a generic 128-bit integral SIMD register; expected one of: 32 [8-bit], 16 [16-bit], 8 [32-bit], 4 [64-bit].");
				}
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i512_generic>)
			{
				if constexpr (num_blend_args == 8)
				{
					constexpr auto blend_mask = EmuSIMD::Funcs::make_reverse_blend_mask<IndexUsesB_...>();
					return EmuSIMD::Funcs::blend_i64x8<blend_mask>(a_, b_);
				}
				else if constexpr (num_blend_args == 16)
				{
					constexpr auto blend_mask = EmuSIMD::Funcs::make_reverse_blend_mask<IndexUsesB_...>();
					return EmuSIMD::Funcs::blend_i32x16<blend_mask>(a_, b_);
				}
				else if constexpr (num_blend_args == 32)
				{
					constexpr auto blend_mask = EmuSIMD::Funcs::make_reverse_blend_mask<IndexUsesB_...>();
					return EmuSIMD::Funcs::blend_i16x32<blend_mask>(a_, b_);
				}
				else if constexpr (num_blend_args == 64)
				{
					constexpr auto blend_mask = EmuSIMD::Funcs::make_reverse_blend_mask<IndexUsesB_...>();
					return EmuSIMD::Funcs::blend_i8x64<blend_mask>(a_, b_);
				}
				else
				{
					static_assert(EmuCore::TMP::get_false<std::size_t, num_blend_args>(), "Invalid number of boolean arguments passed to execute a blend operation on a generic 128-bit integral SIMD register; expected one of: 64 [8-bit], 32 [16-bit], 16 [32-bit], 8 [64-bit].");
				}
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i8x16>)
			{
				if constexpr (num_blend_args == 16)
				{
					constexpr auto blend_mask = EmuSIMD::Funcs::make_reverse_blend_mask<IndexUsesB_...>();
					return EmuSIMD::Funcs::blend_i8x16<blend_mask>(a_, b_);
				}
				else
				{
					static_assert(EmuCore::TMP::get_false<std::size_t, num_blend_args>(), "Invalid number of boolean arguments passed to execute a i8x16 blend operation; expected 16.");
				}
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i16x8>)
			{
				if constexpr (num_blend_args == 8)
				{
					constexpr auto blend_mask = EmuSIMD::Funcs::make_reverse_blend_mask<IndexUsesB_...>();
					return EmuSIMD::Funcs::blend_i16x8<blend_mask>(a_, b_);
				}
				else
				{
					static_assert(EmuCore::TMP::get_false<std::size_t, num_blend_args>(), "Invalid number of boolean arguments passed to execute a i16x8 blend operation; expected 8.");
				}
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i32x4>)
			{
				if constexpr (num_blend_args == 4)
				{
					constexpr auto blend_mask = EmuSIMD::Funcs::make_reverse_blend_mask<IndexUsesB_...>();
					return EmuSIMD::Funcs::blend_i32x4<blend_mask>(a_, b_);
				}
				else
				{
					static_assert(EmuCore::TMP::get_false<std::size_t, num_blend_args>(), "Invalid number of boolean arguments passed to execute a i32x4 blend operation; expected 4.");
				}
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i64x2>)
			{
				if constexpr (num_blend_args == 2)
				{
					constexpr auto blend_mask = EmuSIMD::Funcs::make_reverse_blend_mask<IndexUsesB_...>();
					return EmuSIMD::Funcs::blend_i64x2<blend_mask>(a_, b_);
				}
				else
				{
					static_assert(EmuCore::TMP::get_false<std::size_t, num_blend_args>(), "Invalid number of boolean arguments passed to execute a i64x2 blend operation; expected 2.");
				}
			}			
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i8x32>)
			{
				if constexpr (num_blend_args == 32)
				{
					constexpr auto blend_mask = EmuSIMD::Funcs::make_reverse_blend_mask<IndexUsesB_...>();
					return EmuSIMD::Funcs::blend_i8x32<blend_mask>(a_, b_);
				}
				else
				{
					static_assert(EmuCore::TMP::get_false<std::size_t, num_blend_args>(), "Invalid number of boolean arguments passed to execute a i8x32 blend operation; expected 32.");
				}
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i16x16>)
			{
				if constexpr (num_blend_args == 16)
				{
					constexpr auto blend_mask = EmuSIMD::Funcs::make_reverse_blend_mask<IndexUsesB_...>();
					return EmuSIMD::Funcs::blend_i16x16<blend_mask>(a_, b_);
				}
				else
				{
					static_assert(EmuCore::TMP::get_false<std::size_t, num_blend_args>(), "Invalid number of boolean arguments passed to execute a i16x16 blend operation; expected 16.");
				}
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i32x8>)
			{
				if constexpr (num_blend_args == 8)
				{
					constexpr auto blend_mask = EmuSIMD::Funcs::make_reverse_blend_mask<IndexUsesB_...>();
					return EmuSIMD::Funcs::blend_i32x8<blend_mask>(a_, b_);
				}
				else
				{
					static_assert(EmuCore::TMP::get_false<std::size_t, num_blend_args>(), "Invalid number of boolean arguments passed to execute a i32x8 blend operation; expected 8.");
				}
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i64x4>)
			{
				if constexpr (num_blend_args == 4)
				{
					constexpr auto blend_mask = EmuSIMD::Funcs::make_reverse_blend_mask<IndexUsesB_...>();
					return EmuSIMD::Funcs::blend_i64x4<blend_mask>(a_, b_);
				}
				else
				{
					static_assert(EmuCore::TMP::get_false<std::size_t, num_blend_args>(), "Invalid number of boolean arguments passed to execute a i64x4 blend operation; expected 4.");
				}
			}			
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i8x64>)
			{
				if constexpr (num_blend_args == 64)
				{
					constexpr auto blend_mask = EmuSIMD::Funcs::make_reverse_blend_mask<IndexUsesB_...>();
					return EmuSIMD::Funcs::blend_i8x64<blend_mask>(a_, b_);
				}
				else
				{
					static_assert(EmuCore::TMP::get_false<std::size_t, num_blend_args>(), "Invalid number of boolean arguments passed to execute a i8x64 blend operation; expected 64.");
				}
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i16x32>)
			{
				if constexpr (num_blend_args == 32)
				{
					constexpr auto blend_mask = EmuSIMD::Funcs::make_reverse_blend_mask<IndexUsesB_...>();
					return EmuSIMD::Funcs::blend_i16x32<blend_mask>(a_, b_);
				}
				else
				{
					static_assert(EmuCore::TMP::get_false<std::size_t, num_blend_args>(), "Invalid number of boolean arguments passed to execute a i16x32 blend operation; expected 32.");
				}
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i32x16>)
			{
				if constexpr (num_blend_args == 16)
				{
					constexpr auto blend_mask = EmuSIMD::Funcs::make_reverse_blend_mask<IndexUsesB_...>();
					return EmuSIMD::Funcs::blend_i32x16<blend_mask>(a_, b_);
				}
				else
				{
					static_assert(EmuCore::TMP::get_false<std::size_t, num_blend_args>(), "Invalid number of boolean arguments passed to execute a i32x16 blend operation; expected 16.");
				}
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i64x8>)
			{
				if constexpr (num_blend_args == 8)
				{
					constexpr auto blend_mask = EmuSIMD::Funcs::make_reverse_blend_mask<IndexUsesB_...>();
					return EmuSIMD::Funcs::blend_i64x8<blend_mask>(a_, b_);
				}
				else
				{
					static_assert(EmuCore::TMP::get_false<std::size_t, num_blend_args>(), "Invalid number of boolean arguments passed to execute a i64x8 blend operation; expected 8.");
				}
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u8x16>)
			{
				if constexpr (num_blend_args == 16)
				{
					constexpr auto blend_mask = EmuSIMD::Funcs::make_reverse_blend_mask<IndexUsesB_...>();
					return EmuSIMD::Funcs::blend_u8x16<blend_mask>(a_, b_);
				}
				else
				{
					static_assert(EmuCore::TMP::get_false<std::size_t, num_blend_args>(), "Invalid number of boolean arguments passed to execute a u8x16 blend operation; expected 16.");
				}
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u16x8>)
			{
				if constexpr (num_blend_args == 8)
				{
					constexpr auto blend_mask = EmuSIMD::Funcs::make_reverse_blend_mask<IndexUsesB_...>();
					return EmuSIMD::Funcs::blend_u16x8<blend_mask>(a_, b_);
				}
				else
				{
					static_assert(EmuCore::TMP::get_false<std::size_t, num_blend_args>(), "Invalid number of boolean arguments passed to execute a u16x8 blend operation; expected 8.");
				}
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u32x4>)
			{
				if constexpr (num_blend_args == 4)
				{
					constexpr auto blend_mask = EmuSIMD::Funcs::make_reverse_blend_mask<IndexUsesB_...>();
					return EmuSIMD::Funcs::blend_u32x4<blend_mask>(a_, b_);
				}
				else
				{
					static_assert(EmuCore::TMP::get_false<std::size_t, num_blend_args>(), "Invalid number of boolean arguments passed to execute a u32x4 blend operation; expected 4.");
				}
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u64x2>)
			{
				if constexpr (num_blend_args == 2)
				{
					constexpr auto blend_mask = EmuSIMD::Funcs::make_reverse_blend_mask<IndexUsesB_...>();
					return EmuSIMD::Funcs::blend_u64x2<blend_mask>(a_, b_);
				}
				else
				{
					static_assert(EmuCore::TMP::get_false<std::size_t, num_blend_args>(), "Invalid number of boolean arguments passed to execute a u64x2 blend operation; expected 2.");
				}
			}			
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u8x32>)
			{
				if constexpr (num_blend_args == 32)
				{
					constexpr auto blend_mask = EmuSIMD::Funcs::make_reverse_blend_mask<IndexUsesB_...>();
					return EmuSIMD::Funcs::blend_u8x32<blend_mask>(a_, b_);
				}
				else
				{
					static_assert(EmuCore::TMP::get_false<std::size_t, num_blend_args>(), "Invalid number of boolean arguments passed to execute a u8x32 blend operation; expected 32.");
				}
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u16x16>)
			{
				if constexpr (num_blend_args == 16)
				{
					constexpr auto blend_mask = EmuSIMD::Funcs::make_reverse_blend_mask<IndexUsesB_...>();
					return EmuSIMD::Funcs::blend_u16x16<blend_mask>(a_, b_);
				}
				else
				{
					static_assert(EmuCore::TMP::get_false<std::size_t, num_blend_args>(), "Invalid number of boolean arguments passed to execute a u16x16 blend operation; expected 16.");
				}
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u32x8>)
			{
				if constexpr (num_blend_args == 8)
				{
					constexpr auto blend_mask = EmuSIMD::Funcs::make_reverse_blend_mask<IndexUsesB_...>();
					return EmuSIMD::Funcs::blend_u32x8<blend_mask>(a_, b_);
				}
				else
				{
					static_assert(EmuCore::TMP::get_false<std::size_t, num_blend_args>(), "Invalid number of boolean arguments passed to execute a u32x8 blend operation; expected 8.");
				}
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u64x4>)
			{
				if constexpr (num_blend_args == 4)
				{
					constexpr auto blend_mask = EmuSIMD::Funcs::make_reverse_blend_mask<IndexUsesB_...>();
					return EmuSIMD::Funcs::blend_u64x4<blend_mask>(a_, b_);
				}
				else
				{
					static_assert(EmuCore::TMP::get_false<std::size_t, num_blend_args>(), "Invalid number of boolean arguments passed to execute a u64x4 blend operation; expected 4.");
				}
			}			
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u8x64>)
			{
				if constexpr (num_blend_args == 64)
				{
					constexpr auto blend_mask = EmuSIMD::Funcs::make_reverse_blend_mask<IndexUsesB_...>();
					return EmuSIMD::Funcs::blend_u8x64<blend_mask>(a_, b_);
				}
				else
				{
					static_assert(EmuCore::TMP::get_false<std::size_t, num_blend_args>(), "Invalid number of boolean arguments passed to execute a u8x64 blend operation; expected 64.");
				}
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u16x32>)
			{
				if constexpr (num_blend_args == 32)
				{
					constexpr auto blend_mask = EmuSIMD::Funcs::make_reverse_blend_mask<IndexUsesB_...>();
					return EmuSIMD::Funcs::blend_u16x32<blend_mask>(a_, b_);
				}
				else
				{
					static_assert(EmuCore::TMP::get_false<std::size_t, num_blend_args>(), "Invalid number of boolean arguments passed to execute a u16x32 blend operation; expected 32.");
				}
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u32x16>)
			{
				if constexpr (num_blend_args == 16)
				{
					constexpr auto blend_mask = EmuSIMD::Funcs::make_reverse_blend_mask<IndexUsesB_...>();
					return EmuSIMD::Funcs::blend_u32x16<blend_mask>(a_, b_);
				}
				else
				{
					static_assert(EmuCore::TMP::get_false<std::size_t, num_blend_args>(), "Invalid number of boolean arguments passed to execute a u32x16 blend operation; expected 16.");
				}
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u64x8>)
			{
				if constexpr (num_blend_args == 8)
				{
					constexpr auto blend_mask = EmuSIMD::Funcs::make_reverse_blend_mask<IndexUsesB_...>();
					return EmuSIMD::Funcs::blend_u64x8<blend_mask>(a_, b_);
				}
				else
				{
					static_assert(EmuCore::TMP::get_false<std::size_t, num_blend_args>(), "Invalid number of boolean arguments passed to execute a u64x8 blend operation; expected 8.");
				}
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to execute a SIMD blend, but the provided Register_ type is not recognised as a supported SIMD register.");
		}
	}
}

#endif
