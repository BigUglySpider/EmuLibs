#ifndef EMU_SIMD_HELPERS_UNDERLYING_BLEND_H_INC_
#define EMU_SIMD_HELPERS_UNDERLYING_BLEND_H_INC_ 1

#include "_common_underlying_simd_template_helper_includes.h"
#include "_simd_helpers_underlying_blend_mask.h"
#include "_simd_helpers_underlying_shuffle.h"
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
			using mask_generator = _underlying_simd_helpers::_blend_mask<register_type_uq, IndexUsesB_...>;
			if constexpr (_underlying_simd_helpers::_is_valid_blend_mask<mask_generator>::value)
			{
				if constexpr (_underlying_simd_helpers::_blend_mask_is_simd_register<mask_generator>::value)
				{
					// Defer to blendv for executing a register mask
					if constexpr (EmuCore::TMP::is_any_comparison_true<std::is_same, register_type_uq, EmuSIMD::f32x4, EmuSIMD::f32x8, EmuSIMD::f32x16, EmuSIMD::f64x2, EmuSIMD::f64x4, EmuSIMD::f64x8>::value)
					{
						// Nothing extra needed
						return _blendv(a_, b_, mask_generator::get());
					}
					else if constexpr (EmuCore::TMP::is_any_comparison_true<std::is_same, register_type_uq, EmuSIMD::i128_generic, EmuSIMD::i256_generic, EmuSIMD::i512_generic>::value)
					{
						constexpr std::size_t register_width_ = EmuSIMD::TMP::simd_register_width_v<register_type_uq>;
						constexpr std::size_t num_index_args_ = sizeof...(IndexUsesB_);
						constexpr std::size_t per_element_width_ = register_width_ / num_index_args_;
						if constexpr (EmuSIMD::TMP::_valid_simd_int_element_width(per_element_width_))
						{
							return _blendv<per_element_width_>(a_, b_, mask_generator::get());
						}
						else
						{
							static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to execute SIMD blend with index arguments which result in a vectorwise blend mask for a blendv operation, however the index argument count cannot be successfully used to determine a per-element width (in bits) for the register.");
						}
					}
					else
					{
						static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to execute SIMD blend with index arguments which result in a vectorwise blend mask for a blendv operation, however the passed SIMD register is not supported for EmuMath's blendv functionality.");
					}
				}
				else
				{
					// We have a non-register mask to use
					if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x4>)
					{
						return _mm_blend_ps(a_, b_, mask_generator::get());
					}
					else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x8>)
					{
						return _mm256_blend_ps(a_, b_, mask_generator::get());
					}
					else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x16>)
					{
						return _mm512_mask_blend_ps(mask_generator::get(), a_, b_);
					}
					else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x2>)
					{
						return _mm_blend_pd(a_, b_, mask_generator::get());
					}
					else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x4>)
					{
						return _mm256_blend_pd(a_, b_, mask_generator::get());
					}
					else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x8>)
					{
						return _mm512_mask_blend_pd(mask_generator::get(), a_, b_);
					}
					else if constexpr (EmuCore::TMP::is_any_comparison_true<std::is_same, register_type_uq, EmuSIMD::i128_generic, EmuSIMD::i256_generic, EmuSIMD::i512_generic>::value)
					{
						constexpr std::size_t register_width_ = EmuSIMD::TMP::simd_register_width_v<register_type_uq>;
						constexpr std::size_t num_index_args_ = sizeof...(IndexUsesB_);
						constexpr std::size_t per_element_width_ = register_width_ / num_index_args_;

						if constexpr (EmuSIMD::TMP::_assert_valid_simd_int_element_width<per_element_width_>() && (per_element_width_ != 8))
						{
							// 8-bit is handled as vectorwise blend, so these cover the entire valid range in just an if...else
							if constexpr (per_element_width_ == 16)
							{
								// We know we have one of the 3 integral registers, so simple else...elif...else covers all scenarios
								if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i128_generic>)
								{
									return _mm_blend_epi16(a_, b_, mask_generator::get());
								}
								else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i256_generic>)
								{
									return _mm256_blend_epi16(a_, b_, mask_generator::get());
								}
								else
								{
									return _mm512_mask_blend_epi16(mask_generator::get(), a_, b_);
								}
							}
							else
							{
								// Blending 64-bit boundaries is emulated through a 32-bit blend; arguments are duplicated before moving to the next
								// --- e.g. 64-bit blend<false, true> translates to 32-bit blend<false, false, true, true>
								if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i128_generic>)
								{
									return _mm_blend_epi32(a_, b_, mask_generator::get());
								}
								else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i256_generic>)
								{
									return _mm256_blend_epi32(a_, b_, mask_generator::get());
								}
								else
								{
									return _mm512_mask_blend_epi32(mask_generator::get(), a_, b_);
								}
							}
						}
						else
						{
							if constexpr (per_element_width_ == 8)
							{
								static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to execute a SIMD blend, but the provided arguments and register resulted in an attempt at blending an integral register in 8-bit fields without deferring to blendv. This behaviour is prohibited.");
							}
							else
							{
								static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to execute SIMD blend with integral registers, however the index argument count cannot be successfully used to determine a per-element width (in bits) for the register.");
							}
						}
					}
					else
					{
						static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to execute a SIMD blend via EmuSIMD helpers using a SIMD register that is not supported for this operation.");
					}
				}
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to execute a SIMD blend, but the provided IndexUsesB_ arguments were not valid for creating a mask for the provided SIMD register type.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to execute a SIMD blend, but the provided Register_ type is not recognised as a supported SIMD register.");
		}
	}
}

#endif
