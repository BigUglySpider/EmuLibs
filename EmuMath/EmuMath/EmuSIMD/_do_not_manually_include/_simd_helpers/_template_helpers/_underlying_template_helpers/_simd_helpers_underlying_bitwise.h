#ifndef EMU_SIMD_HELPERS_UNDERLYING_BITWISE_H_INC_
#define EMU_SIMD_HELPERS_UNDERLYING_BITWISE_H_INC_ 1

#include "_common_underlying_simd_template_helper_includes.h"
#include "_simd_helpers_underlying_index_masks.h"
#include "../../../../../EmuCore/TMPHelpers/Values.h"

namespace EmuSIMD::_underlying_simd_helpers
{
	template<class Register_>
	[[nodiscard]] inline Register_ _and(Register_ lhs_, Register_ rhs_)
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x4>)
			{
				return EmuSIMD::Funcs::and_f32x4(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x8>)
			{
				return EmuSIMD::Funcs::and_f32x8(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x16>)
			{
				return EmuSIMD::Funcs::and_f32x16(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x2>)
			{
				return EmuSIMD::Funcs::and_f64x2(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x4>)
			{
				return EmuSIMD::Funcs::and_f64x4(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x8>)
			{
				return EmuSIMD::Funcs::and_f64x8(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i128_generic>)
			{
				return EmuSIMD::Funcs::and_i32x4(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i256_generic>)
			{
				return EmuSIMD::Funcs::and_i32x8(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i512_generic>)
			{
				return EmuSIMD::Funcs::and_i32x16(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i8x16>)
			{
				return EmuSIMD::Funcs::and_i8x16(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i16x8>)
			{
				return EmuSIMD::Funcs::and_i16x8(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i32x4>)
			{
				return EmuSIMD::Funcs::and_i32x4(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i64x2>)
			{
				return EmuSIMD::Funcs::and_i64x2(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i8x32>)
			{
				return EmuSIMD::Funcs::and_i8x32(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i16x16>)
			{
				return EmuSIMD::Funcs::and_i16x16(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i32x8>)
			{
				return EmuSIMD::Funcs::and_i32x8(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i64x4>)
			{
				return EmuSIMD::Funcs::and_i64x4(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i8x64>)
			{
				return EmuSIMD::Funcs::and_i8x64(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i16x32>)
			{
				return EmuSIMD::Funcs::and_i16x32(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i32x16>)
			{
				return EmuSIMD::Funcs::and_i32x16(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i64x8>)
			{
				return EmuSIMD::Funcs::and_i64x8(lhs_, rhs_);
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform bitwise AND of a SIMD register using EmuSIMD helpers, but the provided SIMD register is not supported for this operation");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform bitwise AND of a SIMD register using EmuSIMD helpers, but provided a type that is not a supported SIMD register.");
		}
	}

	template<class Register_>
	[[nodiscard]] inline Register_ _or(Register_ lhs_, Register_ rhs_)
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x4>)
			{
				return EmuSIMD::Funcs::or_f32x4(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x8>)
			{
				return EmuSIMD::Funcs::or_f32x8(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x16>)
			{
				return EmuSIMD::Funcs::or_f32x16(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x2>)
			{
				return EmuSIMD::Funcs::or_f64x2(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x4>)
			{
				return EmuSIMD::Funcs::or_f64x4(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x8>)
			{
				return EmuSIMD::Funcs::or_f64x8(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i128_generic>)
			{
				return EmuSIMD::Funcs::or_i32x4(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i256_generic>)
			{
				return EmuSIMD::Funcs::or_i32x8(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i512_generic>)
			{
				return EmuSIMD::Funcs::or_i32x16(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i8x16>)
			{
				return EmuSIMD::Funcs::or_i8x16(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i16x8>)
			{
				return EmuSIMD::Funcs::or_i16x8(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i32x4>)
			{
				return EmuSIMD::Funcs::or_i32x4(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i64x2>)
			{
				return EmuSIMD::Funcs::or_i64x2(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i8x32>)
			{
				return EmuSIMD::Funcs::or_i8x32(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i16x16>)
			{
				return EmuSIMD::Funcs::or_i16x16(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i32x8>)
			{
				return EmuSIMD::Funcs::or_i32x8(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i64x4>)
			{
				return EmuSIMD::Funcs::or_i64x4(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i8x64>)
			{
				return EmuSIMD::Funcs::or_i8x64(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i16x32>)
			{
				return EmuSIMD::Funcs::or_i16x32(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i32x16>)
			{
				return EmuSIMD::Funcs::or_i32x16(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i64x8>)
			{
				return EmuSIMD::Funcs::or_i64x8(lhs_, rhs_);
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform bitwise OR of a SIMD register using EmuSIMD helpers, but the provided SIMD register is not supported for this operation");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform bitwise OR of a SIMD register using EmuSIMD helpers, but provided a type that is not a supported SIMD register.");
		}
	}

	template<class Register_>
	[[nodiscard]] inline Register_ _xor(Register_ lhs_, Register_ rhs_)
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x4>)
			{
				return EmuSIMD::Funcs::xor_f32x4(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x8>)
			{
				return EmuSIMD::Funcs::xor_f32x8(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x16>)
			{
				return EmuSIMD::Funcs::xor_f32x16(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x2>)
			{
				return EmuSIMD::Funcs::xor_f64x2(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x4>)
			{
				return EmuSIMD::Funcs::xor_f64x4(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x8>)
			{
				return EmuSIMD::Funcs::xor_f64x8(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i128_generic>)
			{
				return EmuSIMD::Funcs::xor_i32x4(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i256_generic>)
			{
				return EmuSIMD::Funcs::xor_i32x8(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i512_generic>)
			{
				return EmuSIMD::Funcs::xor_i32x16(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i8x16>)
			{
				return EmuSIMD::Funcs::xor_i8x16(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i16x8>)
			{
				return EmuSIMD::Funcs::xor_i16x8(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i32x4>)
			{
				return EmuSIMD::Funcs::xor_i32x4(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i64x2>)
			{
				return EmuSIMD::Funcs::xor_i64x2(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i8x32>)
			{
				return EmuSIMD::Funcs::xor_i8x32(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i16x16>)
			{
				return EmuSIMD::Funcs::xor_i16x16(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i32x8>)
			{
				return EmuSIMD::Funcs::xor_i32x8(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i64x4>)
			{
				return EmuSIMD::Funcs::xor_i64x4(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i8x64>)
			{
				return EmuSIMD::Funcs::xor_i8x64(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i16x32>)
			{
				return EmuSIMD::Funcs::xor_i16x32(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i32x16>)
			{
				return EmuSIMD::Funcs::xor_i32x16(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i64x8>)
			{
				return EmuSIMD::Funcs::xor_i64x8(lhs_, rhs_);
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform bitwise XOR of a SIMD register using EmuSIMD helpers, but the provided SIMD register is not supported for this operation");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform bitwise XOR of a SIMD register using EmuSIMD helpers, but provided a type that is not a supported SIMD register.");
		}
	}

	template<class Register_>
	[[nodiscard]] inline Register_ _andnot(Register_ lhs_, Register_ rhs_)
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x4>)
			{
				return EmuSIMD::Funcs::andnot_f32x4(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x8>)
			{
				return EmuSIMD::Funcs::andnot_f32x8(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x16>)
			{
				return EmuSIMD::Funcs::andnot_f32x16(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x2>)
			{
				return EmuSIMD::Funcs::andnot_f64x2(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x4>)
			{
				return EmuSIMD::Funcs::andnot_f64x4(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x8>)
			{
				return EmuSIMD::Funcs::andnot_f64x8(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i128_generic>)
			{
				return EmuSIMD::Funcs::andnot_i32x4(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i256_generic>)
			{
				return EmuSIMD::Funcs::andnot_i32x8(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i512_generic>)
			{
				return EmuSIMD::Funcs::andnot_i32x16(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i8x16>)
			{
				return EmuSIMD::Funcs::andnot_i8x16(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i16x8>)
			{
				return EmuSIMD::Funcs::andnot_i16x8(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i32x4>)
			{
				return EmuSIMD::Funcs::andnot_i32x4(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i64x2>)
			{
				return EmuSIMD::Funcs::andnot_i64x2(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i8x32>)
			{
				return EmuSIMD::Funcs::andnot_i8x32(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i16x16>)
			{
				return EmuSIMD::Funcs::andnot_i16x16(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i32x8>)
			{
				return EmuSIMD::Funcs::andnot_i32x8(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i64x4>)
			{
				return EmuSIMD::Funcs::andnot_i64x4(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i8x64>)
			{
				return EmuSIMD::Funcs::andnot_i8x64(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i16x32>)
			{
				return EmuSIMD::Funcs::andnot_i16x32(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i32x16>)
			{
				return EmuSIMD::Funcs::andnot_i32x16(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i64x8>)
			{
				return EmuSIMD::Funcs::andnot_i64x8(lhs_, rhs_);
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform bitwise ANDNOT of a SIMD register using EmuSIMD helpers, but the provided SIMD register is not supported for this operation");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform bitwise ANDNOT of a SIMD register using EmuSIMD helpers, but provided a type that is not a supported SIMD register.");
		}
	}

	template<class SIMDRegister_>
	[[nodiscard]] inline auto _not(SIMDRegister_&& to_not_)
		-> typename std::remove_cvref<SIMDRegister_>::type
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<SIMDRegister_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			constexpr bool is_supported_register_ = EmuCore::TMP::is_any_comparison_true
			<
				std::is_same,
				register_type_uq,
				EmuSIMD::f32x4, EmuSIMD::f32x8, EmuSIMD::f32x16,
				EmuSIMD::f64x2, EmuSIMD::f64x4, EmuSIMD::f64x8,
				EmuSIMD::i128_generic, EmuSIMD::i256_generic, EmuSIMD::i512_generic
			>::value;
			if constexpr (is_supported_register_)
			{
				using all_indices_mask_generator = _underlying_simd_helpers::_per_index_mask<register_type_uq, true>;
				if constexpr (_is_valid_per_index_mask_instance<all_indices_mask_generator>::value)
				{
					// A XOR (11...11) == ~A
					return _xor(std::forward<SIMDRegister_>(to_not_), all_indices_mask_generator::get());
				}
				else
				{
					static_assert(EmuCore::TMP::get_false<SIMDRegister_>(), "Attempted to perform bitwise NOT of a SIMD register using EmuSIMD helpers, but a mask to perform the operation could not be successfully generated.");
				}
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<SIMDRegister_>(), "Attempted to perform bitwise NOT of a SIMD register using EmuSIMD helpers, but provided a SIMD register that is not supported for this operation.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<SIMDRegister_>(), "Attempted to perform bitwise NOT of a SIMD register using EmuSIMD helpers, but provided a type that is not a supported SIMD register.");
		}
	}

#pragma region LEFT_SHIFTS
	template<class Register_, std::int32_t NumShifts_, std::size_t PerElementWidthIfInt_>
	[[nodiscard]] inline Register_ _shift_left(Register_ lhs_)
	{
		using _register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<_register_type_uq>)
		{
			if constexpr (std::is_same_v<_register_type_uq, EmuSIMD::f32x4>)
			{
				return EmuSIMD::Funcs::shift_left_f32x4<NumShifts_>(lhs_);
			}
			else if constexpr (std::is_same_v<_register_type_uq, EmuSIMD::f32x8>)
			{
				return EmuSIMD::Funcs::shift_left_f32x8<NumShifts_>(lhs_);
			}
			else if constexpr (std::is_same_v<_register_type_uq, EmuSIMD::f32x16>)
			{
				return EmuSIMD::Funcs::shift_left_f32x16<NumShifts_>(lhs_);
			}
			else if constexpr (std::is_same_v<_register_type_uq, EmuSIMD::f64x2>)
			{
				return EmuSIMD::Funcs::shift_left_f64x2<NumShifts_>(lhs_);
			}
			else if constexpr (std::is_same_v<_register_type_uq, EmuSIMD::f64x4>)
			{
				return EmuSIMD::Funcs::shift_left_f64x4<NumShifts_>(lhs_);
			}
			else if constexpr (std::is_same_v<_register_type_uq, EmuSIMD::f64x8>)
			{
				return EmuSIMD::Funcs::shift_left_f64x8<NumShifts_>(lhs_);
			}
			else if constexpr (std::is_same_v<_register_type_uq, EmuSIMD::i128_generic>)
			{
				if constexpr (PerElementWidthIfInt_ == 8)
				{
					return EmuSIMD::Funcs::shift_left_i8x16<NumShifts_>(lhs_);
				}
				else if constexpr (PerElementWidthIfInt_ == 16)
				{
					return EmuSIMD::Funcs::shift_left_i16x8<NumShifts_>(lhs_);
				}
				else if constexpr (PerElementWidthIfInt_ == 32)
				{
					return EmuSIMD::Funcs::shift_left_i32x4<NumShifts_>(lhs_);
				}
				else if constexpr (PerElementWidthIfInt_ == 64)
				{
					return EmuSIMD::Funcs::shift_left_i64x2<NumShifts_>(lhs_);
				}
				else
				{
					static_assert
					(
						EmuCore::TMP::get_false<std::size_t, PerElementWidthIfInt_>(),
						"Attempted to perform bitwise left shift of a 128-bit generic integral ISMD register using EmuSIMD helpers, but the provided per-element width is invalid."
					);
				}
			}
			else if constexpr (std::is_same_v<_register_type_uq, EmuSIMD::i256_generic>)
			{
				if constexpr (PerElementWidthIfInt_ == 8)
				{
					return EmuSIMD::Funcs::shift_left_i8x32<NumShifts_>(lhs_);
				}
				else if constexpr (PerElementWidthIfInt_ == 16)
				{
					return EmuSIMD::Funcs::shift_left_i16x16<NumShifts_>(lhs_);
				}
				else if constexpr (PerElementWidthIfInt_ == 32)
				{
					return EmuSIMD::Funcs::shift_left_i32x8<NumShifts_>(lhs_);
				}
				else if constexpr (PerElementWidthIfInt_ == 64)
				{
					return EmuSIMD::Funcs::shift_left_i64x4<NumShifts_>(lhs_);
				}
				else
				{
					static_assert
					(
						EmuCore::TMP::get_false<std::size_t, PerElementWidthIfInt_>(),
						"Attempted to perform bitwise left shift of a 256-bit generic integral ISMD register using EmuSIMD helpers, but the provided per-element width is invalid."
					);
				}
			}
			else if constexpr (std::is_same_v<_register_type_uq, EmuSIMD::i512_generic>)
			{
				if constexpr (PerElementWidthIfInt_ == 8)
				{
					return EmuSIMD::Funcs::shift_left_i8x64<NumShifts_>(lhs_);
				}
				else if constexpr (PerElementWidthIfInt_ == 16)
				{
					return EmuSIMD::Funcs::shift_left_i16x32<NumShifts_>(lhs_);
				}
				else if constexpr (PerElementWidthIfInt_ == 32)
				{
					return EmuSIMD::Funcs::shift_left_i32x16<NumShifts_>(lhs_);
				}
				else if constexpr (PerElementWidthIfInt_ == 64)
				{
					return EmuSIMD::Funcs::shift_left_i64x8<NumShifts_>(lhs_);
				}
				else
				{
					static_assert
					(
						EmuCore::TMP::get_false<std::size_t, PerElementWidthIfInt_>(),
						"Attempted to perform bitwise left shift of a 512-bit generic integral ISMD register using EmuSIMD helpers, but the provided per-element width is invalid."
					);
				}
			}
			else if constexpr (std::is_same_v<_register_type_uq, EmuSIMD::i8x16>)
			{
				return EmuSIMD::Funcs::shift_left_i8x16<NumShifts_>(lhs_);
			}
			else if constexpr (std::is_same_v<_register_type_uq, EmuSIMD::i16x8>)
			{
				return EmuSIMD::Funcs::shift_left_i16x8<NumShifts_>(lhs_);
			}
			else if constexpr (std::is_same_v<_register_type_uq, EmuSIMD::i32x4>)
			{
				return EmuSIMD::Funcs::shift_left_i32x4<NumShifts_>(lhs_);
			}
			else if constexpr (std::is_same_v<_register_type_uq, EmuSIMD::i64x2>)
			{
				return EmuSIMD::Funcs::shift_left_i64x2<NumShifts_>(lhs_);
			}			
			else if constexpr (std::is_same_v<_register_type_uq, EmuSIMD::i8x32>)
			{
				return EmuSIMD::Funcs::shift_left_i8x32<NumShifts_>(lhs_);
			}
			else if constexpr (std::is_same_v<_register_type_uq, EmuSIMD::i16x16>)
			{
				return EmuSIMD::Funcs::shift_left_i16x16<NumShifts_>(lhs_);
			}
			else if constexpr (std::is_same_v<_register_type_uq, EmuSIMD::i32x8>)
			{
				return EmuSIMD::Funcs::shift_left_i32x8<NumShifts_>(lhs_);
			}
			else if constexpr (std::is_same_v<_register_type_uq, EmuSIMD::i64x4>)
			{
				return EmuSIMD::Funcs::shift_left_i64x4<NumShifts_>(lhs_);
			}			
			else if constexpr (std::is_same_v<_register_type_uq, EmuSIMD::i8x64>)
			{
				return EmuSIMD::Funcs::shift_left_i8x64<NumShifts_>(lhs_);
			}
			else if constexpr (std::is_same_v<_register_type_uq, EmuSIMD::i16x32>)
			{
				return EmuSIMD::Funcs::shift_left_i16x32<NumShifts_>(lhs_);
			}
			else if constexpr (std::is_same_v<_register_type_uq, EmuSIMD::i32x16>)
			{
				return EmuSIMD::Funcs::shift_left_i32x16<NumShifts_>(lhs_);
			}
			else if constexpr (std::is_same_v<_register_type_uq, EmuSIMD::i64x8>)
			{
				return EmuSIMD::Funcs::shift_left_i64x8<NumShifts_>(lhs_);
			}			
			else if constexpr (std::is_same_v<_register_type_uq, EmuSIMD::u8x16>)
			{
				return EmuSIMD::Funcs::shift_left_u8x16<NumShifts_>(lhs_);
			}
			else if constexpr (std::is_same_v<_register_type_uq, EmuSIMD::u16x8>)
			{
				return EmuSIMD::Funcs::shift_left_u16x8<NumShifts_>(lhs_);
			}
			else if constexpr (std::is_same_v<_register_type_uq, EmuSIMD::u32x4>)
			{
				return EmuSIMD::Funcs::shift_left_u32x4<NumShifts_>(lhs_);
			}
			else if constexpr (std::is_same_v<_register_type_uq, EmuSIMD::u64x2>)
			{
				return EmuSIMD::Funcs::shift_left_u64x2<NumShifts_>(lhs_);
			}			
			else if constexpr (std::is_same_v<_register_type_uq, EmuSIMD::u8x32>)
			{
				return EmuSIMD::Funcs::shift_left_u8x32<NumShifts_>(lhs_);
			}
			else if constexpr (std::is_same_v<_register_type_uq, EmuSIMD::u16x16>)
			{
				return EmuSIMD::Funcs::shift_left_u16x16<NumShifts_>(lhs_);
			}
			else if constexpr (std::is_same_v<_register_type_uq, EmuSIMD::u32x8>)
			{
				return EmuSIMD::Funcs::shift_left_u32x8<NumShifts_>(lhs_);
			}
			else if constexpr (std::is_same_v<_register_type_uq, EmuSIMD::u64x4>)
			{
				return EmuSIMD::Funcs::shift_left_u64x4<NumShifts_>(lhs_);
			}			
			else if constexpr (std::is_same_v<_register_type_uq, EmuSIMD::u8x64>)
			{
				return EmuSIMD::Funcs::shift_left_u8x64<NumShifts_>(lhs_);
			}
			else if constexpr (std::is_same_v<_register_type_uq, EmuSIMD::u16x32>)
			{
				return EmuSIMD::Funcs::shift_left_u16x32<NumShifts_>(lhs_);
			}
			else if constexpr (std::is_same_v<_register_type_uq, EmuSIMD::u32x16>)
			{
				return EmuSIMD::Funcs::shift_left_u32x16<NumShifts_>(lhs_);
			}
			else if constexpr (std::is_same_v<_register_type_uq, EmuSIMD::u64x8>)
			{
				return EmuSIMD::Funcs::shift_left_u64x8<NumShifts_>(lhs_);
			}
			else
			{
				static_assert
				(
					EmuCore::TMP::get_false<Register_>(),
					"Attempted to perform bitwise left shift of a SIMD register using EmuSIMD helpers, but provided a SIMD register type that is not supported for this operation."
				);
			}
		}
		else
		{
			static_assert
			(
				EmuCore::TMP::get_false<Register_>(),
				"Attempted to perform bitwise left shift of a SIMD register using EmuSIMD helpers, but provided a type that is not a supported SIMD register."
			);
		}
	}
#pragma endregion

#pragma region ARITHMETIC_RIGHT_SHIFTS
	template<class Register_, std::int32_t NumShifts_, std::size_t PerElementWidthIfInt_>
	[[nodiscard]] inline Register_ _shift_right_arithmetic(Register_ lhs_)
	{
		using _register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<_register_type_uq>)
		{
			if constexpr (std::is_same_v<_register_type_uq, EmuSIMD::f32x4>)
			{
				return EmuSIMD::Funcs::shift_right_arithmetic_f32x4<NumShifts_>(lhs_);
			}
			else if constexpr (std::is_same_v<_register_type_uq, EmuSIMD::f32x8>)
			{
				return EmuSIMD::Funcs::shift_right_arithmetic_f32x8<NumShifts_>(lhs_);
			}
			else if constexpr (std::is_same_v<_register_type_uq, EmuSIMD::f32x16>)
			{
				return EmuSIMD::Funcs::shift_right_arithmetic_f32x16<NumShifts_>(lhs_);
			}
			else if constexpr (std::is_same_v<_register_type_uq, EmuSIMD::f64x2>)
			{
				return EmuSIMD::Funcs::shift_right_arithmetic_f64x2<NumShifts_>(lhs_);
			}
			else if constexpr (std::is_same_v<_register_type_uq, EmuSIMD::f64x4>)
			{
				return EmuSIMD::Funcs::shift_right_arithmetic_f64x4<NumShifts_>(lhs_);
			}
			else if constexpr (std::is_same_v<_register_type_uq, EmuSIMD::f64x8>)
			{
				return EmuSIMD::Funcs::shift_right_arithmetic_f64x8<NumShifts_>(lhs_);
			}
			else if constexpr (std::is_same_v<_register_type_uq, EmuSIMD::i128_generic>)
			{
				if constexpr (PerElementWidthIfInt_ == 8)
				{
					return EmuSIMD::Funcs::shift_right_arithmetic_i8x16<NumShifts_>(lhs_);
				}
				else if constexpr (PerElementWidthIfInt_ == 16)
				{
					return EmuSIMD::Funcs::shift_right_arithmetic_i16x8<NumShifts_>(lhs_);
				}
				else if constexpr (PerElementWidthIfInt_ == 32)
				{
					return EmuSIMD::Funcs::shift_right_arithmetic_i32x4<NumShifts_>(lhs_);
				}
				else if constexpr (PerElementWidthIfInt_ == 64)
				{
					return EmuSIMD::Funcs::shift_right_arithmetic_i64x2<NumShifts_>(lhs_);
				}
				else
				{
					static_assert
					(
						EmuCore::TMP::get_false<std::size_t, PerElementWidthIfInt_>(),
						"Attempted to perform bitwise arithmetic right shift of a 128-bit generic integral ISMD register using EmuSIMD helpers, but the provided per-element width is invalid."
					);
				}
			}
			else if constexpr (std::is_same_v<_register_type_uq, EmuSIMD::i256_generic>)
			{
				if constexpr (PerElementWidthIfInt_ == 8)
				{
					return EmuSIMD::Funcs::shift_right_arithmetic_i8x32<NumShifts_>(lhs_);
				}
				else if constexpr (PerElementWidthIfInt_ == 16)
				{
					return EmuSIMD::Funcs::shift_right_arithmetic_i16x16<NumShifts_>(lhs_);
				}
				else if constexpr (PerElementWidthIfInt_ == 32)
				{
					return EmuSIMD::Funcs::shift_right_arithmetic_i32x8<NumShifts_>(lhs_);
				}
				else if constexpr (PerElementWidthIfInt_ == 64)
				{
					return EmuSIMD::Funcs::shift_right_arithmetic_i64x4<NumShifts_>(lhs_);
				}
				else
				{
					static_assert
					(
						EmuCore::TMP::get_false<std::size_t, PerElementWidthIfInt_>(),
						"Attempted to perform bitwise arithmetic right shift of a 256-bit generic integral ISMD register using EmuSIMD helpers, but the provided per-element width is invalid."
					);
				}
			}
			else if constexpr (std::is_same_v<_register_type_uq, EmuSIMD::i512_generic>)
			{
				if constexpr (PerElementWidthIfInt_ == 8)
				{
					return EmuSIMD::Funcs::shift_right_arithmetic_i8x64<NumShifts_>(lhs_);
				}
				else if constexpr (PerElementWidthIfInt_ == 16)
				{
					return EmuSIMD::Funcs::shift_right_arithmetic_i16x32<NumShifts_>(lhs_);
				}
				else if constexpr (PerElementWidthIfInt_ == 32)
				{
					return EmuSIMD::Funcs::shift_right_arithmetic_i32x16<NumShifts_>(lhs_);
				}
				else if constexpr (PerElementWidthIfInt_ == 64)
				{
					return EmuSIMD::Funcs::shift_right_arithmetic_i64x8<NumShifts_>(lhs_);
				}
				else
				{
					static_assert
					(
						EmuCore::TMP::get_false<std::size_t, PerElementWidthIfInt_>(),
						"Attempted to perform bitwise arithmetic right shift of a 512-bit generic integral ISMD register using EmuSIMD helpers, but the provided per-element width is invalid."
					);
				}
			}
			else if constexpr (std::is_same_v<_register_type_uq, EmuSIMD::i8x16>)
			{
				return EmuSIMD::Funcs::shift_right_arithmetic_i8x16<NumShifts_>(lhs_);
			}
			else if constexpr (std::is_same_v<_register_type_uq, EmuSIMD::i16x8>)
			{
				return EmuSIMD::Funcs::shift_right_arithmetic_i16x8<NumShifts_>(lhs_);
			}
			else if constexpr (std::is_same_v<_register_type_uq, EmuSIMD::i32x4>)
			{
				return EmuSIMD::Funcs::shift_right_arithmetic_i32x4<NumShifts_>(lhs_);
			}
			else if constexpr (std::is_same_v<_register_type_uq, EmuSIMD::i64x2>)
			{
				return EmuSIMD::Funcs::shift_right_arithmetic_i64x2<NumShifts_>(lhs_);
			}			
			else if constexpr (std::is_same_v<_register_type_uq, EmuSIMD::i8x32>)
			{
				return EmuSIMD::Funcs::shift_right_arithmetic_i8x32<NumShifts_>(lhs_);
			}
			else if constexpr (std::is_same_v<_register_type_uq, EmuSIMD::i16x16>)
			{
				return EmuSIMD::Funcs::shift_right_arithmetic_i16x16<NumShifts_>(lhs_);
			}
			else if constexpr (std::is_same_v<_register_type_uq, EmuSIMD::i32x8>)
			{
				return EmuSIMD::Funcs::shift_right_arithmetic_i32x8<NumShifts_>(lhs_);
			}
			else if constexpr (std::is_same_v<_register_type_uq, EmuSIMD::i64x4>)
			{
				return EmuSIMD::Funcs::shift_right_arithmetic_i64x4<NumShifts_>(lhs_);
			}			
			else if constexpr (std::is_same_v<_register_type_uq, EmuSIMD::i8x64>)
			{
				return EmuSIMD::Funcs::shift_right_arithmetic_i8x64<NumShifts_>(lhs_);
			}
			else if constexpr (std::is_same_v<_register_type_uq, EmuSIMD::i16x32>)
			{
				return EmuSIMD::Funcs::shift_right_arithmetic_i16x32<NumShifts_>(lhs_);
			}
			else if constexpr (std::is_same_v<_register_type_uq, EmuSIMD::i32x16>)
			{
				return EmuSIMD::Funcs::shift_right_arithmetic_i32x16<NumShifts_>(lhs_);
			}
			else if constexpr (std::is_same_v<_register_type_uq, EmuSIMD::i64x8>)
			{
				return EmuSIMD::Funcs::shift_right_arithmetic_i64x8<NumShifts_>(lhs_);
			}			
			else if constexpr (std::is_same_v<_register_type_uq, EmuSIMD::u8x16>)
			{
				return EmuSIMD::Funcs::shift_right_arithmetic_u8x16<NumShifts_>(lhs_);
			}
			else if constexpr (std::is_same_v<_register_type_uq, EmuSIMD::u16x8>)
			{
				return EmuSIMD::Funcs::shift_right_arithmetic_u16x8<NumShifts_>(lhs_);
			}
			else if constexpr (std::is_same_v<_register_type_uq, EmuSIMD::u32x4>)
			{
				return EmuSIMD::Funcs::shift_right_arithmetic_u32x4<NumShifts_>(lhs_);
			}
			else if constexpr (std::is_same_v<_register_type_uq, EmuSIMD::u64x2>)
			{
				return EmuSIMD::Funcs::shift_right_arithmetic_u64x2<NumShifts_>(lhs_);
			}			
			else if constexpr (std::is_same_v<_register_type_uq, EmuSIMD::u8x32>)
			{
				return EmuSIMD::Funcs::shift_right_arithmetic_u8x32<NumShifts_>(lhs_);
			}
			else if constexpr (std::is_same_v<_register_type_uq, EmuSIMD::u16x16>)
			{
				return EmuSIMD::Funcs::shift_right_arithmetic_u16x16<NumShifts_>(lhs_);
			}
			else if constexpr (std::is_same_v<_register_type_uq, EmuSIMD::u32x8>)
			{
				return EmuSIMD::Funcs::shift_right_arithmetic_u32x8<NumShifts_>(lhs_);
			}
			else if constexpr (std::is_same_v<_register_type_uq, EmuSIMD::u64x4>)
			{
				return EmuSIMD::Funcs::shift_right_arithmetic_u64x4<NumShifts_>(lhs_);
			}			
			else if constexpr (std::is_same_v<_register_type_uq, EmuSIMD::u8x64>)
			{
				return EmuSIMD::Funcs::shift_right_arithmetic_u8x64<NumShifts_>(lhs_);
			}
			else if constexpr (std::is_same_v<_register_type_uq, EmuSIMD::u16x32>)
			{
				return EmuSIMD::Funcs::shift_right_arithmetic_u16x32<NumShifts_>(lhs_);
			}
			else if constexpr (std::is_same_v<_register_type_uq, EmuSIMD::u32x16>)
			{
				return EmuSIMD::Funcs::shift_right_arithmetic_u32x16<NumShifts_>(lhs_);
			}
			else if constexpr (std::is_same_v<_register_type_uq, EmuSIMD::u64x8>)
			{
				return EmuSIMD::Funcs::shift_right_arithmetic_u64x8<NumShifts_>(lhs_);
			}
			else
			{
				static_assert
				(
					EmuCore::TMP::get_false<Register_>(),
					"Attempted to perform bitwise arithmetic right shift of a SIMD register using EmuSIMD helpers, but provided a SIMD register type that is not supported for this operation."
				);
			}
		}
		else
		{
			static_assert
			(
				EmuCore::TMP::get_false<Register_>(),
				"Attempted to perform bitwise arithmetic right shift of a SIMD register using EmuSIMD helpers, but provided a type that is not a supported SIMD register."
			);
		}
	}
#pragma endregion

#pragma region LOGCAL_RIGHT_SHIFTS
	template<class Register_, std::int32_t NumShifts_, std::size_t PerElementWidthIfInt_>
	[[nodiscard]] inline Register_ _shift_right_logical(Register_ lhs_)
	{
		using _register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<_register_type_uq>)
		{
			if constexpr (std::is_same_v<_register_type_uq, EmuSIMD::f32x4>)
			{
				return EmuSIMD::Funcs::shift_right_logical_f32x4<NumShifts_>(lhs_);
			}
			else if constexpr (std::is_same_v<_register_type_uq, EmuSIMD::f32x8>)
			{
				return EmuSIMD::Funcs::shift_right_logical_f32x8<NumShifts_>(lhs_);
			}
			else if constexpr (std::is_same_v<_register_type_uq, EmuSIMD::f32x16>)
			{
				return EmuSIMD::Funcs::shift_right_logical_f32x16<NumShifts_>(lhs_);
			}
			else if constexpr (std::is_same_v<_register_type_uq, EmuSIMD::f64x2>)
			{
				return EmuSIMD::Funcs::shift_right_logical_f64x2<NumShifts_>(lhs_);
			}
			else if constexpr (std::is_same_v<_register_type_uq, EmuSIMD::f64x4>)
			{
				return EmuSIMD::Funcs::shift_right_logical_f64x4<NumShifts_>(lhs_);
			}
			else if constexpr (std::is_same_v<_register_type_uq, EmuSIMD::f64x8>)
			{
				return EmuSIMD::Funcs::shift_right_logical_f64x8<NumShifts_>(lhs_);
			}
			else if constexpr (std::is_same_v<_register_type_uq, EmuSIMD::i128_generic>)
			{
				if constexpr (PerElementWidthIfInt_ == 8)
				{
					return EmuSIMD::Funcs::shift_right_logical_i8x16<NumShifts_>(lhs_);
				}
				else if constexpr (PerElementWidthIfInt_ == 16)
				{
					return EmuSIMD::Funcs::shift_right_logical_i16x8<NumShifts_>(lhs_);
				}
				else if constexpr (PerElementWidthIfInt_ == 32)
				{
					return EmuSIMD::Funcs::shift_right_logical_i32x4<NumShifts_>(lhs_);
				}
				else if constexpr (PerElementWidthIfInt_ == 64)
				{
					return EmuSIMD::Funcs::shift_right_logical_i64x2<NumShifts_>(lhs_);
				}
				else
				{
					static_assert
					(
						EmuCore::TMP::get_false<std::size_t, PerElementWidthIfInt_>(),
						"Attempted to perform bitwise logical right shift of a 128-bit generic integral ISMD register using EmuSIMD helpers, but the provided per-element width is invalid."
					);
				}
			}
			else if constexpr (std::is_same_v<_register_type_uq, EmuSIMD::i256_generic>)
			{
				if constexpr (PerElementWidthIfInt_ == 8)
				{
					return EmuSIMD::Funcs::shift_right_logical_i8x32<NumShifts_>(lhs_);
				}
				else if constexpr (PerElementWidthIfInt_ == 16)
				{
					return EmuSIMD::Funcs::shift_right_logical_i16x16<NumShifts_>(lhs_);
				}
				else if constexpr (PerElementWidthIfInt_ == 32)
				{
					return EmuSIMD::Funcs::shift_right_logical_i32x8<NumShifts_>(lhs_);
				}
				else if constexpr (PerElementWidthIfInt_ == 64)
				{
					return EmuSIMD::Funcs::shift_right_logical_i64x4<NumShifts_>(lhs_);
				}
				else
				{
					static_assert
					(
						EmuCore::TMP::get_false<std::size_t, PerElementWidthIfInt_>(),
						"Attempted to perform bitwise logical right shift of a 256-bit generic integral ISMD register using EmuSIMD helpers, but the provided per-element width is invalid."
					);
				}
			}
			else if constexpr (std::is_same_v<_register_type_uq, EmuSIMD::i512_generic>)
			{
				if constexpr (PerElementWidthIfInt_ == 8)
				{
					return EmuSIMD::Funcs::shift_right_logical_i8x64<NumShifts_>(lhs_);
				}
				else if constexpr (PerElementWidthIfInt_ == 16)
				{
					return EmuSIMD::Funcs::shift_right_logical_i16x32<NumShifts_>(lhs_);
				}
				else if constexpr (PerElementWidthIfInt_ == 32)
				{
					return EmuSIMD::Funcs::shift_right_logical_i32x16<NumShifts_>(lhs_);
				}
				else if constexpr (PerElementWidthIfInt_ == 64)
				{
					return EmuSIMD::Funcs::shift_right_logical_i64x8<NumShifts_>(lhs_);
				}
				else
				{
					static_assert
					(
						EmuCore::TMP::get_false<std::size_t, PerElementWidthIfInt_>(),
						"Attempted to perform bitwise logical right shift of a 512-bit generic integral ISMD register using EmuSIMD helpers, but the provided per-element width is invalid."
					);
				}
			}
			else if constexpr (std::is_same_v<_register_type_uq, EmuSIMD::i8x16>)
			{
				return EmuSIMD::Funcs::shift_right_logical_i8x16<NumShifts_>(lhs_);
			}
			else if constexpr (std::is_same_v<_register_type_uq, EmuSIMD::i16x8>)
			{
				return EmuSIMD::Funcs::shift_right_logical_i16x8<NumShifts_>(lhs_);
			}
			else if constexpr (std::is_same_v<_register_type_uq, EmuSIMD::i32x4>)
			{
				return EmuSIMD::Funcs::shift_right_logical_i32x4<NumShifts_>(lhs_);
			}
			else if constexpr (std::is_same_v<_register_type_uq, EmuSIMD::i64x2>)
			{
				return EmuSIMD::Funcs::shift_right_logical_i64x2<NumShifts_>(lhs_);
			}			
			else if constexpr (std::is_same_v<_register_type_uq, EmuSIMD::i8x32>)
			{
				return EmuSIMD::Funcs::shift_right_logical_i8x32<NumShifts_>(lhs_);
			}
			else if constexpr (std::is_same_v<_register_type_uq, EmuSIMD::i16x16>)
			{
				return EmuSIMD::Funcs::shift_right_logical_i16x16<NumShifts_>(lhs_);
			}
			else if constexpr (std::is_same_v<_register_type_uq, EmuSIMD::i32x8>)
			{
				return EmuSIMD::Funcs::shift_right_logical_i32x8<NumShifts_>(lhs_);
			}
			else if constexpr (std::is_same_v<_register_type_uq, EmuSIMD::i64x4>)
			{
				return EmuSIMD::Funcs::shift_right_logical_i64x4<NumShifts_>(lhs_);
			}			
			else if constexpr (std::is_same_v<_register_type_uq, EmuSIMD::i8x64>)
			{
				return EmuSIMD::Funcs::shift_right_logical_i8x64<NumShifts_>(lhs_);
			}
			else if constexpr (std::is_same_v<_register_type_uq, EmuSIMD::i16x32>)
			{
				return EmuSIMD::Funcs::shift_right_logical_i16x32<NumShifts_>(lhs_);
			}
			else if constexpr (std::is_same_v<_register_type_uq, EmuSIMD::i32x16>)
			{
				return EmuSIMD::Funcs::shift_right_logical_i32x16<NumShifts_>(lhs_);
			}
			else if constexpr (std::is_same_v<_register_type_uq, EmuSIMD::i64x8>)
			{
				return EmuSIMD::Funcs::shift_right_logical_i64x8<NumShifts_>(lhs_);
			}			
			else if constexpr (std::is_same_v<_register_type_uq, EmuSIMD::u8x16>)
			{
				return EmuSIMD::Funcs::shift_right_logical_u8x16<NumShifts_>(lhs_);
			}
			else if constexpr (std::is_same_v<_register_type_uq, EmuSIMD::u16x8>)
			{
				return EmuSIMD::Funcs::shift_right_logical_u16x8<NumShifts_>(lhs_);
			}
			else if constexpr (std::is_same_v<_register_type_uq, EmuSIMD::u32x4>)
			{
				return EmuSIMD::Funcs::shift_right_logical_u32x4<NumShifts_>(lhs_);
			}
			else if constexpr (std::is_same_v<_register_type_uq, EmuSIMD::u64x2>)
			{
				return EmuSIMD::Funcs::shift_right_logical_u64x2<NumShifts_>(lhs_);
			}			
			else if constexpr (std::is_same_v<_register_type_uq, EmuSIMD::u8x32>)
			{
				return EmuSIMD::Funcs::shift_right_logical_u8x32<NumShifts_>(lhs_);
			}
			else if constexpr (std::is_same_v<_register_type_uq, EmuSIMD::u16x16>)
			{
				return EmuSIMD::Funcs::shift_right_logical_u16x16<NumShifts_>(lhs_);
			}
			else if constexpr (std::is_same_v<_register_type_uq, EmuSIMD::u32x8>)
			{
				return EmuSIMD::Funcs::shift_right_logical_u32x8<NumShifts_>(lhs_);
			}
			else if constexpr (std::is_same_v<_register_type_uq, EmuSIMD::u64x4>)
			{
				return EmuSIMD::Funcs::shift_right_logical_u64x4<NumShifts_>(lhs_);
			}			
			else if constexpr (std::is_same_v<_register_type_uq, EmuSIMD::u8x64>)
			{
				return EmuSIMD::Funcs::shift_right_logical_u8x64<NumShifts_>(lhs_);
			}
			else if constexpr (std::is_same_v<_register_type_uq, EmuSIMD::u16x32>)
			{
				return EmuSIMD::Funcs::shift_right_logical_u16x32<NumShifts_>(lhs_);
			}
			else if constexpr (std::is_same_v<_register_type_uq, EmuSIMD::u32x16>)
			{
				return EmuSIMD::Funcs::shift_right_logical_u32x16<NumShifts_>(lhs_);
			}
			else if constexpr (std::is_same_v<_register_type_uq, EmuSIMD::u64x8>)
			{
				return EmuSIMD::Funcs::shift_right_logical_u64x8<NumShifts_>(lhs_);
			}
			else
			{
				static_assert
				(
					EmuCore::TMP::get_false<Register_>(),
					"Attempted to perform bitwise logical right shift of a SIMD register using EmuSIMD helpers, but provided a SIMD register type that is not supported for this operation."
				);
			}
		}
		else
		{
			static_assert
			(
				EmuCore::TMP::get_false<Register_>(),
				"Attempted to perform bitwise logical right shift of a SIMD register using EmuSIMD helpers, but provided a type that is not a supported SIMD register."
			);
		}
	}
#pragma endregion
}

#endif
