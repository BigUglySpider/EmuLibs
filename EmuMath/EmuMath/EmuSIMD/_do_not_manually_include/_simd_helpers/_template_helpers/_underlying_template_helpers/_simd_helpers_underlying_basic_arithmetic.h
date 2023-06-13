#ifndef EMU_SIMD_HELPERS_UNDERLYING_ARITHMETIC_H_INC_
#define EMU_SIMD_HELPERS_UNDERLYING_ARITHMETIC_H_INC_ 1

#include "_common_underlying_simd_template_helper_includes.h"
#include "_simd_helpers_underlying_bitwise.h"
#include "_simd_helpers_underlying_cmp.h"
#include "_simd_helpers_underlying_set.h"
#include "../../../../../EmuCore/TMPHelpers/Values.h"

namespace EmuSIMD::_underlying_simd_helpers
{
#pragma region ADDITION_FUNCS
	template<class Register_>
	[[nodiscard]] inline Register_ _add_fp(Register_ lhs_, Register_ rhs_)
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			using namespace EmuSIMD::Funcs;
			if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x4>)
			{
				return add_f32x4(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x8>)
			{
				return add_f32x8(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x16>)
			{
				return add_f32x16(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x2>)
			{
				return add_f64x2(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x4>)
			{
				return add_f64x4(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x8>)
			{
				return add_f64x8(lhs_, rhs_);
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform addition of floating-point SIMD registers via EmuSIMD helpers, but the provided Register_ type was not a supported floating-point SIMD register.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform addition of floating-point SIMD registers via EmuSIMD helpers, but the provided Register_ type is not a supported SIMD register.");
		}
	}

	template<std::size_t PerElementWidth_, class Register_>
	[[nodiscard]] inline Register_ _add_int(Register_ lhs_, Register_ rhs_)
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			if constexpr (EmuSIMD::TMP::_assert_valid_simd_int_element_width<PerElementWidth_>())
			{
				using namespace EmuSIMD::Funcs;
				if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i128_generic>)
				{
					if constexpr (PerElementWidth_ == 8)
					{
						return add_i8x16(lhs_, rhs_);
					}
					else if constexpr (PerElementWidth_ == 16)
					{
						return add_i16x8(lhs_, rhs_);
					}
					else if constexpr (PerElementWidth_ == 32)
					{
						return add_i32x4(lhs_, rhs_);
					}
					else
					{
						return add_i64x2(lhs_, rhs_);
					}
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i256_generic>)
				{
					if constexpr (PerElementWidth_ == 8)
					{
						return add_i8x32(lhs_, rhs_);
					}
					else if constexpr (PerElementWidth_ == 16)
					{
						return add_i16x16(lhs_, rhs_);
					}
					else if constexpr (PerElementWidth_ == 32)
					{
						return add_i32x8(lhs_, rhs_);
					}
					else
					{
						return add_i64x4(lhs_, rhs_);
					}
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i512_generic>)
				{
					if constexpr (PerElementWidth_ == 8)
					{
						return add_i8x64(lhs_, rhs_);
					}
					else if constexpr (PerElementWidth_ == 16)
					{
						return add_i16x32(lhs_, rhs_);
					}
					else if constexpr (PerElementWidth_ == 32)
					{
						return add_i32x16(lhs_, rhs_);
					}
					else
					{
						return add_i64x8(lhs_, rhs_);
					}
				}
				else
				{
					static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform addition of integral SIMD registers via EmuSIMD helpers, but provided an unsupported integral SIMD register.");
				}
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform addition of integral SIMD registers via EmuSIMD helpers, but provided an invalid PerElementWidth_.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform addition of integral SIMD registers via EmuSIMD helpers, but the provided Register_ type was not a supported integral SIMD register.");
		}
	}
#pragma endregion

#pragma region SUBTRACTION_FUNCS
	template<class Register_>
	[[nodiscard]] inline Register_ _sub_fp(Register_ lhs_, Register_ rhs_)
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			using namespace EmuSIMD::Funcs;
			if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x4>)
			{
				return sub_f32x4(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x8>)
			{
				return sub_f32x8(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x16>)
			{
				return sub_f32x16(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x2>)
			{
				return sub_f64x2(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x4>)
			{
				return sub_f64x4(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x8>)
			{
				return sub_f64x8(lhs_, rhs_);
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform subtraction of floating-point SIMD registers via EmuSIMD helpers, but the provided Register_ type was not a supported floating-point SIMD register.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform subtraction of floating-point SIMD registers via EmuSIMD helpers, but the provided Register_ type is not a supported SIMD register.");
		}
	}

	template<std::size_t PerElementWidth_, class Register_>
	[[nodiscard]] inline Register_ _sub_int(Register_ lhs_, Register_ rhs_)
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			if constexpr (EmuSIMD::TMP::_assert_valid_simd_int_element_width<PerElementWidth_>())
			{
				using namespace EmuSIMD::Funcs;
				if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i128_generic>)
				{
					if constexpr (PerElementWidth_ == 8)
					{
						return sub_i8x16(lhs_, rhs_);
					}
					else if constexpr (PerElementWidth_ == 16)
					{
						return sub_i16x8(lhs_, rhs_);
					}
					else if constexpr (PerElementWidth_ == 32)
					{
						return sub_i32x4(lhs_, rhs_);
					}
					else
					{
						return sub_i64x2(lhs_, rhs_);
					}
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i256_generic>)
				{
					if constexpr (PerElementWidth_ == 8)
					{
						return sub_i8x32(lhs_, rhs_);
					}
					else if constexpr (PerElementWidth_ == 16)
					{
						return sub_i16x16(lhs_, rhs_);
					}
					else if constexpr (PerElementWidth_ == 32)
					{
						return sub_i32x8(lhs_, rhs_);
					}
					else
					{
						return sub_i64x4(lhs_, rhs_);
					}
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i512_generic>)
				{
					if constexpr (PerElementWidth_ == 8)
					{
						return sub_i8x64(lhs_, rhs_);
					}
					else if constexpr (PerElementWidth_ == 16)
					{
						return sub_i16x32(lhs_, rhs_);
					}
					else if constexpr (PerElementWidth_ == 32)
					{
						return sub_i32x16(lhs_, rhs_);
					}
					else
					{
						return sub_i64x8(lhs_, rhs_);
					}
				}
				else
				{
					static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform subtraction of integral SIMD registers via EmuSIMD helpers, but provided an unsupported integral SIMD register.");
				}
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform subtraction of integral SIMD registers via EmuSIMD helpers, but provided an invalid PerElementWidth_.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform subtraction of integral SIMD registers via EmuSIMD helpers, but the provided Register_ type was not a supported integral SIMD register.");
		}
	}
#pragma endregion

#pragma region MULTIPLICATION_FUNCS
	template<class Register_>
	[[nodiscard]] inline Register_ _mul_fp(Register_ lhs_, Register_ rhs_)
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			using namespace EmuSIMD::Funcs;
			if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x4>)
			{
				return mul_all_f32x4(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x8>)
			{
				return mul_all_f32x8(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x16>)
			{
				return mul_all_f32x16(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x2>)
			{
				return mul_all_f64x2(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x4>)
			{
				return mul_all_f64x4(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x8>)
			{
				return mul_all_f64x8(lhs_, rhs_);
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform multiplication of floating-point SIMD registers via EmuSIMD helpers, but the provided Register_ type was not a supported floating-point SIMD register.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform multiplication of floating-point SIMD registers via EmuSIMD helpers, but the provided Register_ type is not a supported SIMD register.");
		}
	}

	template<std::size_t PerElementWidth_, class Register_>
	[[nodiscard]] inline Register_ _mul_all_int(Register_ lhs_, Register_ rhs_)
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			if constexpr (EmuSIMD::TMP::_assert_valid_simd_int_element_width<PerElementWidth_>())
			{
				if constexpr (EmuSIMD::TMP::is_integral_simd_register_v<Register_>)
				{
					using namespace EmuSIMD::Funcs;
					if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i128_generic>)
					{
						if constexpr (PerElementWidth_ == 8)
						{
							return mul_all_i8x16(lhs_, rhs_);
						}
						else if constexpr (PerElementWidth_ == 16)
						{
							return mul_all_i16x8(lhs_, rhs_);
						}
						else if constexpr (PerElementWidth_ == 32)
						{
							return mul_all_i32x4(lhs_, rhs_);
						}
						else
						{
							return mul_all_i64x2(lhs_, rhs_);
						}
					}
					else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i256_generic>)
					{
						if constexpr (PerElementWidth_ == 8)
						{
							return mul_all_i8x32(lhs_, rhs_);
						}
						else if constexpr (PerElementWidth_ == 16)
						{
							return mul_all_i16x16(lhs_, rhs_);
						}
						else if constexpr (PerElementWidth_ == 32)
						{
							return mul_all_i32x8(lhs_, rhs_);
						}
						else
						{
							return mul_all_i64x4(lhs_, rhs_);
						}
					}
					else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i512_generic>)
					{
						if constexpr (PerElementWidth_ == 8)
						{
							return mul_all_i8x64(lhs_, rhs_);
						}
						else if constexpr (PerElementWidth_ == 16)
						{
							return mul_all_i16x32(lhs_, rhs_);
						}
						else if constexpr (PerElementWidth_ == 32)
						{
							return mul_all_i32x16(lhs_, rhs_);
						}
						else
						{
							return mul_all_i64x8(lhs_, rhs_);
						}
					}
					else
					{
						static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform all-element multiplication of integral SIMD registers via EmuSIMD helpers, but provided an unsupported integral SIMD register.");
					}
				}
				else
				{
					static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform all-element multiplication of integral SIMD registers via EmuSIMD helpers, but provided a non-integral (or unsupported integral) SIMD register.");
				}
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform all-element multiplication of integral SIMD registers via EmuSIMD helpers, but provided an invalid PerElementWidth_.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform all-element multiplication of integral SIMD registers via EmuSIMD helpers, but the provided Register_ type was not a supported integral SIMD register.");
		}
	}
#pragma endregion

#pragma region DIVISION_FUNCS
	template<class Register_>
	[[nodiscard]] inline Register_ _div_fp(Register_ lhs_, Register_ rhs_)
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			using namespace EmuSIMD::Funcs;
			if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x4>)
			{
				return div_f32x4(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x8>)
			{
				return div_f32x8(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x16>)
			{
				return div_f32x16(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x2>)
			{
				return div_f64x2(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x4>)
			{
				return div_f64x4(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x8>)
			{
				return div_f64x8(lhs_, rhs_);
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform division of floating-point SIMD registers via EmuSIMD helpers, but the provided Register_ type was not a supported floating-point SIMD register.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform division of floating-point SIMD registers via EmuSIMD helpers, but the provided Register_ type is not a supported SIMD register.");
		}
	}

	template<std::size_t PerElementWidth_, bool Signed_, class Register_>
	[[nodiscard]] inline Register_ _div_int(Register_ lhs_, Register_ rhs_)
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			if constexpr (EmuSIMD::TMP::_assert_valid_simd_int_element_width<PerElementWidth_>())
			{
				using namespace EmuSIMD::Funcs;
				if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i128_generic>)
				{
					if constexpr (PerElementWidth_ == 8)
					{
						if constexpr (Signed_)
						{
							return div_i8x16(lhs_, rhs_);
						}
						else
						{
							return div_u8x16(lhs_, rhs_);
						}
					}
					else if constexpr (PerElementWidth_ == 16)
					{
						if constexpr (Signed_)
						{
							return div_i16x8(lhs_, rhs_);
						}
						else
						{
							return div_u16x8(lhs_, rhs_);
						}
					}
					else if constexpr (PerElementWidth_ == 32)
					{
						if constexpr (Signed_)
						{
							return div_i32x4(lhs_, rhs_);
						}
						else
						{
							return div_u32x4(lhs_, rhs_);
						}
					}
					else
					{
						if constexpr (Signed_)
						{
							return div_i64x2(lhs_, rhs_);
						}
						else
						{
							return div_u64x2(lhs_, rhs_);
						}
					}
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i256_generic>)
				{
					if constexpr (PerElementWidth_ == 8)
					{
						if constexpr (Signed_)
						{
							return div_i8x32(lhs_, rhs_);
						}
						else
						{
							return div_u8x32(lhs_, rhs_);
						}
					}
					else if constexpr (PerElementWidth_ == 16)
					{
						if constexpr (Signed_)
						{
							return div_i16x16(lhs_, rhs_);
						}
						else
						{
							return div_u16x16(lhs_, rhs_);
						}
					}
					else if constexpr (PerElementWidth_ == 32)
					{
						if constexpr (Signed_)
						{
							return div_i32x8(lhs_, rhs_);
						}
						else
						{
							return div_u32x8(lhs_, rhs_);
						}
					}
					else
					{
						if constexpr (Signed_)
						{
							return div_i64x4(lhs_, rhs_);
						}
						else
						{
							return div_u64x4(lhs_, rhs_);
						}
					}
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i512_generic>)
				{
					if constexpr (PerElementWidth_ == 8)
					{
						if constexpr (Signed_)
						{
							return div_i8x64(lhs_, rhs_);
						}
						else
						{
							return div_u8x64(lhs_, rhs_);
						}
					}
					else if constexpr (PerElementWidth_ == 16)
					{
						if constexpr (Signed_)
						{
							return div_i16x32(lhs_, rhs_);
						}
						else
						{
							return div_u16x32(lhs_, rhs_);
						}
					}
					else if constexpr (PerElementWidth_ == 32)
					{
						if constexpr (Signed_)
						{
							return div_i32x16(lhs_, rhs_);
						}
						else
						{
							return div_u32x16(lhs_, rhs_);
						}
					}
					else
					{
						if constexpr (Signed_)
						{
							return div_i64x8(lhs_, rhs_);
						}
						else
						{
							return div_u64x8(lhs_, rhs_);
						}
					}
				}
				else
				{
					static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform division of integral SIMD registers via EmuSIMD helpers, but provided an unsupported integral SIMD register.");
				}
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform division of integral SIMD registers via EmuSIMD helpers, but provided an invalid PerElementWidth_.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform division of integral SIMD registers via EmuSIMD helpers, but the provided Register_ type was not a supported integral SIMD register.");
		}
	}
#pragma endregion

#pragma region MOD_FUNCS
	template<class Register_>
	[[nodiscard]] inline Register_ _mod_fp(Register_ lhs_, Register_ rhs_)
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			using namespace EmuSIMD::Funcs;
			if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x4>)
			{
				EmuSIMD::f32x4 res = div_f32x4(lhs_, rhs_);
				res = trunc_f32x4(res);
				return fnmadd_f32x4(res, rhs_, lhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x8>)
			{
				EmuSIMD::f32x8 res = div_f32x8(lhs_, rhs_);
				res = trunc_f32x8(res);
				return fnmadd_f32x8(res, rhs_, lhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x16>)
			{
				EmuSIMD::f32x16 res = div_f32x16(lhs_, rhs_);
				res = trunc_f32x16(res);
				return fnmadd_f32x16(res, rhs_, lhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x2>)
			{
				EmuSIMD::f64x2 res = div_f64x2(lhs_, rhs_);
				res = trunc_f64x2(res);
				return fnmadd_f64x2(res, rhs_, lhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x4>)
			{
				EmuSIMD::f64x4 res = div_f64x4(lhs_, rhs_);
				res = trunc_f64x4(res);
				return fnmadd_f64x4(res, rhs_, lhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x8>)
			{
				EmuSIMD::f64x8 res = div_f64x8(lhs_, rhs_);
				res = trunc_f64x8(res);
				return fnmadd_f64x8(res, rhs_, lhs_);
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform modulo division of floating-point SIMD registers via EmuSIMD helpers, but the provided Register_ type was not a supported floating-point SIMD register.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform modulo division of floating-point SIMD registers via EmuSIMD helpers, but the provided Register_ type is not a supported SIMD register.");
		}
	}

	template<std::size_t PerElementWidth_, bool Signed_, class Register_>
	[[nodiscard]] inline Register_ _mod_int(Register_ lhs_, Register_ rhs_)
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			if constexpr (EmuSIMD::TMP::_assert_valid_simd_int_element_width<PerElementWidth_>())
			{
				using namespace EmuSIMD::Funcs;
				if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i128_generic>)
				{
					if constexpr (PerElementWidth_ == 8)
					{
						if constexpr (Signed_)
						{
							return mod_i8x16(lhs_, rhs_);
						}
						else
						{
							return mod_u8x16(lhs_, rhs_);
						}
					}
					else if constexpr (PerElementWidth_ == 16)
					{
						if constexpr (Signed_)
						{
							return mod_i16x8(lhs_, rhs_);
						}
						else
						{
							return mod_u16x8(lhs_, rhs_);
						}
					}
					else if constexpr (PerElementWidth_ == 32)
					{
						if constexpr (Signed_)
						{
							return mod_i32x4(lhs_, rhs_);
						}
						else
						{
							return mod_u32x4(lhs_, rhs_);
						}
					}
					else
					{
						if constexpr (Signed_)
						{
							return mod_i64x2(lhs_, rhs_);
						}
						else
						{
							return mod_u64x2(lhs_, rhs_);
						}
					}
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i256_generic>)
				{
					if constexpr (PerElementWidth_ == 8)
					{
						if constexpr (Signed_)
						{
							return mod_i8x32(lhs_, rhs_);
						}
						else
						{
							return mod_u8x32(lhs_, rhs_);
						}
					}
					else if constexpr (PerElementWidth_ == 16)
					{
						if constexpr (Signed_)
						{
							return mod_i16x16(lhs_, rhs_);
						}
						else
						{
							return mod_u16x16(lhs_, rhs_);
						}
					}
					else if constexpr (PerElementWidth_ == 32)
					{
						if constexpr (Signed_)
						{
							return mod_i32x8(lhs_, rhs_);
						}
						else
						{
							return mod_u32x8(lhs_, rhs_);
						}
					}
					else
					{
						if constexpr (Signed_)
						{
							return mod_i64x4(lhs_, rhs_);
						}
						else
						{
							return mod_u64x4(lhs_, rhs_);
						}
					}
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i512_generic>)
				{
					if constexpr (PerElementWidth_ == 8)
					{
						if constexpr (Signed_)
						{
							return mod_i8x64(lhs_, rhs_);
						}
						else
						{
							return mod_u8x64(lhs_, rhs_);
						}
					}
					else if constexpr (PerElementWidth_ == 16)
					{
						if constexpr (Signed_)
						{
							return mod_i16x32(lhs_, rhs_);
						}
						else
						{
							return mod_u16x32(lhs_, rhs_);
						}
					}
					else if constexpr (PerElementWidth_ == 32)
					{
						if constexpr (Signed_)
						{
							return mod_i32x16(lhs_, rhs_);
						}
						else
						{
							return mod_u32x16(lhs_, rhs_);
						}
					}
					else
					{
						if constexpr (Signed_)
						{
							return mod_i64x8(lhs_, rhs_);
						}
						else
						{
							return mod_u64x8(lhs_, rhs_);
						}
					}
				}
				else
				{
					static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform mod of integral SIMD registers via EmuSIMD helpers, but provided an unsupported integral SIMD register.");
				}
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform mod of integral SIMD registers via EmuSIMD helpers, but provided an invalid PerElementWidth_.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform mod of integral SIMD registers via EmuSIMD helpers, but the provided Register_ type was not a supported integral SIMD register.");
		}
	}
#pragma endregion

#pragma region NEGATION_OPERATIONS
	template<std::size_t PerElementWidthIfInt_, class Register_>
	[[nodiscard]] inline Register_ _negate(Register_ register_)
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			using namespace EmuSIMD::Funcs;
			if constexpr (EmuSIMD::TMP::is_floating_point_simd_register_v<register_type_uq>)
			{
				if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x4>)
				{
					return negate_f32x4(register_);
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x8>)
				{
					return negate_f32x8(register_);
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x16>)
				{
					return negate_f32x16(register_);
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x2>)
				{
					return negate_f64x2(register_);
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x4>)
				{
					return negate_f64x4(register_);
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x8>)
				{
					return negate_f64x8(register_);
				}
				else
				{
					static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to perform negation of floating-point SIMD registers via EmuSIMD helpers, but the provided Register_ type was not a supported floating-point SIMD register.");
				}
			}
			else if constexpr (EmuSIMD::TMP::is_integral_simd_register_v<register_type_uq>)
			{
				if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i128_generic>)
				{
					if constexpr (PerElementWidthIfInt_ == 8)
					{
						return negate_i8x16(register_);
					}
					else if constexpr (PerElementWidthIfInt_ == 16)
					{
						return negate_i16x8(register_);
					}
					else if constexpr (PerElementWidthIfInt_ == 32)
					{
						return negate_i32x4(register_);
					}
					else if constexpr (PerElementWidthIfInt_ == 64)
					{
						return negate_i64x2(register_);
					}
					else
					{
						static_assert(EmuCore::TMP::get_false<std::size_t, PerElementWidthIfInt_>(), "Attempted to negate a generic 128-bit integral SIMD register via EmuSIMD helpers, but the provided PerElementWidth is invalid. Valid values are: 8, 16, 32, 64.");
					}
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i256_generic>)
				{
					if constexpr (PerElementWidthIfInt_ == 8)
					{
						return negate_i8x32(register_);
					}
					else if constexpr (PerElementWidthIfInt_ == 16)
					{
						return negate_i16x16(register_);
					}
					else if constexpr (PerElementWidthIfInt_ == 32)
					{
						return negate_i32x8(register_);
					}
					else if constexpr (PerElementWidthIfInt_ == 64)
					{
						return negate_i64x4(register_);
					}
					else
					{
						static_assert(EmuCore::TMP::get_false<std::size_t, PerElementWidthIfInt_>(), "Attempted to negate a generic 256-bit integral SIMD register via EmuSIMD helpers, but the provided PerElementWidth is invalid. Valid values are: 8, 16, 32, 64.");
					}
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i512_generic>)
				{
					if constexpr (PerElementWidthIfInt_ == 8)
					{
						return negate_i8x64(register_);
					}
					else if constexpr (PerElementWidthIfInt_ == 16)
					{
						return negate_i16x32(register_);
					}
					else if constexpr (PerElementWidthIfInt_ == 32)
					{
						return negate_i32x16(register_);
					}
					else if constexpr (PerElementWidthIfInt_ == 64)
					{
						return negate_i64x8(register_);
					}
					else
					{
						static_assert(EmuCore::TMP::get_false<std::size_t, PerElementWidthIfInt_>(), "Attempted to negate a generic 512-bit integral SIMD register via EmuSIMD helpers, but the provided PerElementWidth is invalid. Valid values are: 8, 16, 32, 64.");
					}
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i8x16>)
				{
					return negate_i8x16(register_);
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i8x32>)
				{
					return negate_i8x32(register_);
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i8x64>)
				{
					return negate_i8x64(register_);
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u8x16>)
				{
					return negate_u8x16(register_);
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u8x32>)
				{
					return negate_u8x32(register_);
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u8x64>)
				{
					return negate_u8x64(register_);
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i16x8>)
				{
					return negate_i16x8(register_);
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i16x16>)
				{
					return negate_i16x16(register_);
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i16x32>)
				{
					return negate_i16x32(register_);
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u16x8>)
				{
					return negate_u16x8(register_);
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u16x16>)
				{
					return negate_u16x16(register_);
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u16x32>)
				{
					return negate_u16x32(register_);
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i32x4>)
				{
					return negate_i32x4(register_);
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i32x8>)
				{
					return negate_i32x8(register_);
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i32x16>)
				{
					return negate_i32x16(register_);
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u32x4>)
				{
					return negate_u32x4(register_);
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u32x8>)
				{
					return negate_u32x8(register_);
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u32x16>)
				{
					return negate_u32x16(register_);
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i64x2>)
				{
					return negate_i64x2(register_);
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i64x4>)
				{
					return negate_i64x4(register_);
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i64x8>)
				{
					return negate_i64x8(register_);
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u64x2>)
				{
					return negate_u64x2(register_);
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u64x4>)
				{
					return negate_u64x4(register_);
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u64x8>)
				{
					return negate_u64x8(register_);
				}
				else
				{
					static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to negate an integral SIMD register via EmuSIMD helpers, but the provided integral SIMD register is not supported for this operation.");
				}
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to negate a SIMD register via EmuSIMD helpers, but the provided SIMD register is not supported for this operation.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to negate a SIMD register via EmuSIMD helpers, but the provided Register_ type is not recognised as a support SIMD register.");
		}
	}
#pragma endregion

#pragma region ALTERNATING_OPERATIONS
	template<class Register_>
	[[nodiscard]] inline Register_ _addsub_fp(Register_ lhs_, Register_ rhs_)
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			using namespace EmuSIMD::Funcs;
			if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x4>)
			{
				return addsub_f32x4(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x8>)
			{
				return addsub_f32x8(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x16>)
			{
				return addsub_f32x16(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x2>)
			{
				return addsub_f64x2(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x4>)
			{
				return addsub_f64x4(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x8>)
			{
				return addsub_f64x8(lhs_, rhs_);
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to add/subtract (addsub) two SIMD registers via EmuSIMD helpers, but the provided SIMD register is not a supported floating-point SIMD register.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to add/subtract (addsub) two SIMD registers via EmuSIMD helpers, but the provided Register_ type is not recognised as a supported SIMD register.");
		}
	}

	template<std::size_t PerElementWidth_, class Register_>
	[[nodiscard]] inline Register_ _addsub_int(Register_ lhs_, Register_ rhs_)
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			if constexpr (EmuSIMD::TMP::_assert_valid_simd_int_element_width<PerElementWidth_>())
			{
				using namespace EmuSIMD::Funcs;
				if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i128_generic>)
				{
					if constexpr (PerElementWidth_ == 8)
					{
						return addsub_i8x16(lhs_, rhs_);
					}
					else if constexpr (PerElementWidth_ == 16)
					{
						return addsub_i16x8(lhs_, rhs_);
					}
					else if constexpr (PerElementWidth_ == 32)
					{
						return addsub_i32x4(lhs_, rhs_);
					}
					else if constexpr (PerElementWidth_ == 64)
					{
						return addsub_i64x2(lhs_, rhs_);
					}
					else
					{
						static_assert(EmuCore::TMP::get_false<std::size_t, PerElementWidth_>(), "Attempted to add/subtract (addsub) two generic 128-bit integral SIMD registers via EmuSIMD helpers, but the provided PerElementWidth is invalid. Valid values are: 8, 16, 32, 64.");
					}
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i256_generic>)
				{
					if constexpr (PerElementWidth_ == 8)
					{
						return addsub_i8x32(lhs_, rhs_);
					}
					else if constexpr (PerElementWidth_ == 16)
					{
						return addsub_i16x16(lhs_, rhs_);
					}
					else if constexpr (PerElementWidth_ == 32)
					{
						return addsub_i32x8(lhs_, rhs_);
					}
					else if constexpr (PerElementWidth_ == 64)
					{
						return addsub_i64x4(lhs_, rhs_);
					}
					else
					{
						static_assert(EmuCore::TMP::get_false<std::size_t, PerElementWidth_>(), "Attempted to add/subtract (addsub) two generic 256-bit integral SIMD registers via EmuSIMD helpers, but the provided PerElementWidth is invalid. Valid values are: 8, 16, 32, 64.");
					}
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i512_generic>)
				{
					if constexpr (PerElementWidth_ == 8)
					{
						return addsub_i8x64(lhs_, rhs_);
					}
					else if constexpr (PerElementWidth_ == 16)
					{
						return addsub_i16x32(lhs_, rhs_);
					}
					else if constexpr (PerElementWidth_ == 32)
					{
						return addsub_i32x16(lhs_, rhs_);
					}
					else if constexpr (PerElementWidth_ == 64)
					{
						return addsub_i64x8(lhs_, rhs_);
					}
					else
					{
						static_assert(EmuCore::TMP::get_false<std::size_t, PerElementWidth_>(), "Attempted to add/subtract (addsub) two generic 512-bit integral SIMD registers via EmuSIMD helpers, but the provided PerElementWidth is invalid. Valid values are: 8, 16, 32, 64.");
					}
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i8x16>)
				{
					return addsub_i8x16(lhs_, rhs_);
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i8x32>)
				{
					return addsub_i8x32(lhs_, rhs_);
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i8x64>)
				{
					return addsub_i8x64(lhs_, rhs_);
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u8x16>)
				{
					return addsub_u8x16(lhs_, rhs_);
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u8x32>)
				{
					return addsub_u8x32(lhs_, rhs_);
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u8x64>)
				{
					return addsub_u8x64(lhs_, rhs_);
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i16x8>)
				{
					return addsub_i16x8(lhs_, rhs_);
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i16x16>)
				{
					return addsub_i16x16(lhs_, rhs_);
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i16x32>)
				{
					return addsub_i16x32(lhs_, rhs_);
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u16x8>)
				{
					return addsub_u16x8(lhs_, rhs_);
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u16x16>)
				{
					return addsub_u16x16(lhs_, rhs_);
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u16x32>)
				{
					return addsub_u16x32(lhs_, rhs_);
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i32x4>)
				{
					return addsub_i32x4(lhs_, rhs_);
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i32x8>)
				{
					return addsub_i32x8(lhs_, rhs_);
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i32x16>)
				{
					return addsub_i32x16(lhs_, rhs_);
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u32x4>)
				{
					return addsub_u32x4(lhs_, rhs_);
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u32x8>)
				{
					return addsub_u32x8(lhs_, rhs_);
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u32x16>)
				{
					return addsub_u32x16(lhs_, rhs_);
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i64x2>)
				{
					return addsub_i64x2(lhs_, rhs_);
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i64x4>)
				{
					return addsub_i64x4(lhs_, rhs_);
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i64x8>)
				{
					return addsub_i64x8(lhs_, rhs_);
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u64x2>)
				{
					return addsub_u64x2(lhs_, rhs_);
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u64x4>)
				{
					return addsub_u64x4(lhs_, rhs_);
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u64x8>)
				{
					return addsub_u64x8(lhs_, rhs_);
				}
				else
				{
					static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to add/subtract (addsub) two integral SIMD registers via EmuSIMD helpers, but the provided integral SIMD register type is not supported for this operation.");
				}
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to add/subtract (addsub) two integral SIMD registers via EmuSIMD helpers, but the provided SIMD register is not a supported integral SIMD register for this operation.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to add/subtract (addsub) two integral SIMD registers via EmuSIMD helpers, but the provided Register_ type is not recognised as a supported SIMD register.");
		}
	}

	template<class Register_>
	[[nodiscard]] inline Register_ _subadd_fp(Register_ lhs_, Register_ rhs_)
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			using namespace EmuSIMD::Funcs;
			if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x4>)
			{
				return subadd_f32x4(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x8>)
			{
				return subadd_f32x8(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x16>)
			{
				return subadd_f32x16(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x2>)
			{
				return subadd_f64x2(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x4>)
			{
				return subadd_f64x4(lhs_, rhs_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x8>)
			{
				return subadd_f64x8(lhs_, rhs_);
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to subtract/add (subadd) two SIMD registers via EmuSIMD helpers, but the provided SIMD register is not a supported floating-point SIMD register.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to subtract/add (subadd) two SIMD registers via EmuSIMD helpers, but the provided Register_ type is not recognised as a supported SIMD register.");
		}
	}

	template<std::size_t PerElementWidth_, class Register_>
	[[nodiscard]] inline Register_ _subadd_int(Register_ lhs_, Register_ rhs_)
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			if constexpr (EmuSIMD::TMP::_assert_valid_simd_int_element_width<PerElementWidth_>())
			{
				using namespace EmuSIMD::Funcs;
				if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i128_generic>)
				{
					if constexpr (PerElementWidth_ == 8)
					{
						return subadd_i8x16(lhs_, rhs_);
					}
					else if constexpr (PerElementWidth_ == 16)
					{
						return subadd_i16x8(lhs_, rhs_);
					}
					else if constexpr (PerElementWidth_ == 32)
					{
						return subadd_i32x4(lhs_, rhs_);
					}
					else if constexpr (PerElementWidth_ == 64)
					{
						return subadd_i64x2(lhs_, rhs_);
					}
					else
					{
						static_assert(EmuCore::TMP::get_false<std::size_t, PerElementWidth_>(), "Attempted to subtract/add (subadd) two generic 128-bit integral SIMD registers via EmuSIMD helpers, but the provided PerElementWidth is invalid. Valid values are: 8, 16, 32, 64.");
					}
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i256_generic>)
				{
					if constexpr (PerElementWidth_ == 8)
					{
						return subadd_i8x32(lhs_, rhs_);
					}
					else if constexpr (PerElementWidth_ == 16)
					{
						return subadd_i16x16(lhs_, rhs_);
					}
					else if constexpr (PerElementWidth_ == 32)
					{
						return subadd_i32x8(lhs_, rhs_);
					}
					else if constexpr (PerElementWidth_ == 64)
					{
						return subadd_i64x4(lhs_, rhs_);
					}
					else
					{
						static_assert(EmuCore::TMP::get_false<std::size_t, PerElementWidth_>(), "Attempted to subtract/add (subadd) two generic 256-bit integral SIMD registers via EmuSIMD helpers, but the provided PerElementWidth is invalid. Valid values are: 8, 16, 32, 64.");
					}
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i512_generic>)
				{
					if constexpr (PerElementWidth_ == 8)
					{
						return subadd_i8x64(lhs_, rhs_);
					}
					else if constexpr (PerElementWidth_ == 16)
					{
						return subadd_i16x32(lhs_, rhs_);
					}
					else if constexpr (PerElementWidth_ == 32)
					{
						return subadd_i32x16(lhs_, rhs_);
					}
					else if constexpr (PerElementWidth_ == 64)
					{
						return subadd_i64x8(lhs_, rhs_);
					}
					else
					{
						static_assert(EmuCore::TMP::get_false<std::size_t, PerElementWidth_>(), "Attempted to subtract/add (subadd) two generic 512-bit integral SIMD registers via EmuSIMD helpers, but the provided PerElementWidth is invalid. Valid values are: 8, 16, 32, 64.");
					}
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i8x16>)
				{
					return subadd_i8x16(lhs_, rhs_);
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i8x32>)
				{
					return subadd_i8x32(lhs_, rhs_);
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i8x64>)
				{
					return subadd_i8x64(lhs_, rhs_);
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u8x16>)
				{
					return subadd_u8x16(lhs_, rhs_);
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u8x32>)
				{
					return subadd_u8x32(lhs_, rhs_);
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u8x64>)
				{
					return subadd_u8x64(lhs_, rhs_);
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i16x8>)
				{
					return subadd_i16x8(lhs_, rhs_);
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i16x16>)
				{
					return subadd_i16x16(lhs_, rhs_);
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i16x32>)
				{
					return subadd_i16x32(lhs_, rhs_);
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u16x8>)
				{
					return subadd_u16x8(lhs_, rhs_);
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u16x16>)
				{
					return subadd_u16x16(lhs_, rhs_);
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u16x32>)
				{
					return subadd_u16x32(lhs_, rhs_);
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i32x4>)
				{
					return subadd_i32x4(lhs_, rhs_);
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i32x8>)
				{
					return subadd_i32x8(lhs_, rhs_);
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i32x16>)
				{
					return subadd_i32x16(lhs_, rhs_);
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u32x4>)
				{
					return subadd_u32x4(lhs_, rhs_);
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u32x8>)
				{
					return subadd_u32x8(lhs_, rhs_);
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u32x16>)
				{
					return subadd_u32x16(lhs_, rhs_);
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i64x2>)
				{
					return subadd_i64x2(lhs_, rhs_);
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i64x4>)
				{
					return subadd_i64x4(lhs_, rhs_);
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i64x8>)
				{
					return subadd_i64x8(lhs_, rhs_);
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u64x2>)
				{
					return subadd_u64x2(lhs_, rhs_);
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u64x4>)
				{
					return subadd_u64x4(lhs_, rhs_);
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u64x8>)
				{
					return subadd_u64x8(lhs_, rhs_);
				}
				else
				{
					static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to subtract/add (subadd) two integral SIMD registers via EmuSIMD helpers, but the provided integral SIMD register type is not supported for this operation.");
				}
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to subtract/add (subadd) two integral SIMD registers via EmuSIMD helpers, but the provided SIMD register is not a supported integral SIMD register for this operation.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to subtract/add (subadd) two integral SIMD registers via EmuSIMD helpers, but the provided Register_ type is not recognised as a supported SIMD register.");
		}
	}
#pragma endregion

#pragma region FUSED_OPERATIONS
	template<class Register_>
	[[nodiscard]] inline Register_ _fmadd_fp(Register_ to_mult_lhs_, Register_ to_mult_rhs_, Register_ to_add_after_mult_)
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			using namespace EmuSIMD::Funcs;
			if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x4>)
			{
				return fmadd_f32x4(to_mult_lhs_, to_mult_rhs_, to_add_after_mult_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x8>)
			{
				return fmadd_f32x8(to_mult_lhs_, to_mult_rhs_, to_add_after_mult_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x16>)
			{
				return fmadd_f32x16(to_mult_lhs_, to_mult_rhs_, to_add_after_mult_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x2>)
			{
				return fmadd_f64x2(to_mult_lhs_, to_mult_rhs_, to_add_after_mult_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x4>)
			{
				return fmadd_f64x4(to_mult_lhs_, to_mult_rhs_, to_add_after_mult_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x8>)
			{
				return fmadd_f64x8(to_mult_lhs_, to_mult_rhs_, to_add_after_mult_);
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to fused multiply add (fmadd) three SIMD registers via EmuSIMD helpers, but the provided SIMD register is not a supported floating-point SIMD register.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to fused multiply add (fmadd) three SIMD registers via EmuSIMD helpers, but the provided Register_ type is not recognised as a support SIMD register.");
		}
	}
	template<std::size_t PerElementWidth_, class Register_>
	[[nodiscard]] inline Register_ _fmadd_int(Register_ to_mult_lhs_, Register_ to_mult_rhs_, Register_ to_add_after_mult_)
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			if constexpr (EmuSIMD::TMP::_assert_valid_simd_int_element_width<PerElementWidth_>())
			{
				using namespace EmuSIMD::Funcs;
				if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i128_generic>)
				{
					if constexpr (PerElementWidth_ == 8)
					{
						return fmadd_i8x16(to_mult_lhs_, to_mult_rhs_, to_add_after_mult_);
					}
					else if constexpr (PerElementWidth_ == 16)
					{
						return fmadd_i16x8(to_mult_lhs_, to_mult_rhs_, to_add_after_mult_);
					}
					else if constexpr (PerElementWidth_ == 32)
					{
						return fmadd_i32x4(to_mult_lhs_, to_mult_rhs_, to_add_after_mult_);
					}
					else if constexpr (PerElementWidth_ == 64)
					{
						return fmadd_i64x2(to_mult_lhs_, to_mult_rhs_, to_add_after_mult_);
					}
					else
					{
						static_assert(EmuCore::TMP::get_false<std::size_t, PerElementWidth_>(), "Attempted to fused multiply add (fmadd) generic 128-bit integral SIMD registers via EmuSIMD helpers, but the provided PerElementWidth is invalid. Valid values are: 8, 16, 32, 64.");
					}
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i256_generic>)
				{
					if constexpr (PerElementWidth_ == 8)
					{
						return fmadd_i8x32(to_mult_lhs_, to_mult_rhs_, to_add_after_mult_);
					}
					else if constexpr (PerElementWidth_ == 16)
					{
						return fmadd_i16x16(to_mult_lhs_, to_mult_rhs_, to_add_after_mult_);
					}
					else if constexpr (PerElementWidth_ == 32)
					{
						return fmadd_i32x8(to_mult_lhs_, to_mult_rhs_, to_add_after_mult_);
					}
					else if constexpr (PerElementWidth_ == 64)
					{
						return fmadd_i64x4(to_mult_lhs_, to_mult_rhs_, to_add_after_mult_);
					}
					else
					{
						static_assert(EmuCore::TMP::get_false<std::size_t, PerElementWidth_>(), "Attempted to fused multiply add (fmadd) generic 256-bit integral SIMD registers via EmuSIMD helpers, but the provided PerElementWidth is invalid. Valid values are: 8, 16, 32, 64.");
					}
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i512_generic>)
				{
					if constexpr (PerElementWidth_ == 8)
					{
						return fmadd_i8x64(to_mult_lhs_, to_mult_rhs_, to_add_after_mult_);
					}
					else if constexpr (PerElementWidth_ == 16)
					{
						return fmadd_i16x32(to_mult_lhs_, to_mult_rhs_, to_add_after_mult_);
					}
					else if constexpr (PerElementWidth_ == 32)
					{
						return fmadd_i32x16(to_mult_lhs_, to_mult_rhs_, to_add_after_mult_);
					}
					else if constexpr (PerElementWidth_ == 64)
					{
						return fmadd_i64x8(to_mult_lhs_, to_mult_rhs_, to_add_after_mult_);
					}
					else
					{
						static_assert(EmuCore::TMP::get_false<std::size_t, PerElementWidth_>(), "Attempted to fused multiply add (fmadd) generic 512-bit integral SIMD registers via EmuSIMD helpers, but the provided PerElementWidth is invalid. Valid values are: 8, 16, 32, 64.");
					}
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i8x16>)
				{
					return fmadd_i8x16(to_mult_lhs_, to_mult_rhs_, to_add_after_mult_);
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i8x32>)
				{
					return fmadd_i8x32(to_mult_lhs_, to_mult_rhs_, to_add_after_mult_);
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i8x64>)
				{
					return fmadd_i8x64(to_mult_lhs_, to_mult_rhs_, to_add_after_mult_);
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u8x16>)
				{
					return fmadd_u8x16(to_mult_lhs_, to_mult_rhs_, to_add_after_mult_);
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u8x32>)
				{
					return fmadd_u8x32(to_mult_lhs_, to_mult_rhs_, to_add_after_mult_);
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u8x64>)
				{
					return fmadd_u8x64(to_mult_lhs_, to_mult_rhs_, to_add_after_mult_);
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i16x8>)
				{
					return fmadd_i16x8(to_mult_lhs_, to_mult_rhs_, to_add_after_mult_);
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i16x16>)
				{
					return fmadd_i16x16(to_mult_lhs_, to_mult_rhs_, to_add_after_mult_);
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i16x32>)
				{
					return fmadd_i16x32(to_mult_lhs_, to_mult_rhs_, to_add_after_mult_);
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u16x8>)
				{
					return fmadd_u16x8(to_mult_lhs_, to_mult_rhs_, to_add_after_mult_);
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u16x16>)
				{
					return fmadd_u16x16(to_mult_lhs_, to_mult_rhs_, to_add_after_mult_);
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u16x32>)
				{
					return fmadd_u16x32(to_mult_lhs_, to_mult_rhs_, to_add_after_mult_);
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i32x4>)
				{
					return fmadd_i32x4(to_mult_lhs_, to_mult_rhs_, to_add_after_mult_);
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i32x8>)
				{
					return fmadd_i32x8(to_mult_lhs_, to_mult_rhs_, to_add_after_mult_);
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i32x16>)
				{
					return fmadd_i32x16(to_mult_lhs_, to_mult_rhs_, to_add_after_mult_);
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u32x4>)
				{
					return fmadd_u32x4(to_mult_lhs_, to_mult_rhs_, to_add_after_mult_);
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u32x8>)
				{
					return fmadd_u32x8(to_mult_lhs_, to_mult_rhs_, to_add_after_mult_);
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u32x16>)
				{
					return fmadd_u32x16(to_mult_lhs_, to_mult_rhs_, to_add_after_mult_);
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i64x2>)
				{
					return fmadd_i64x2(to_mult_lhs_, to_mult_rhs_, to_add_after_mult_);
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i64x4>)
				{
					return fmadd_i64x4(to_mult_lhs_, to_mult_rhs_, to_add_after_mult_);
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i64x8>)
				{
					return fmadd_i64x8(to_mult_lhs_, to_mult_rhs_, to_add_after_mult_);
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u64x2>)
				{
					return fmadd_u64x2(to_mult_lhs_, to_mult_rhs_, to_add_after_mult_);
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u64x4>)
				{
					return fmadd_u64x4(to_mult_lhs_, to_mult_rhs_, to_add_after_mult_);
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u64x8>)
				{
					return fmadd_u64x8(to_mult_lhs_, to_mult_rhs_, to_add_after_mult_);
				}
				else
				{
					static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to fused multiply add (fmadd) integral SIMD registers via EmuSIMD helpers, but the provided integral SIMD register type is not supported for this operation.");
				}
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to fused multiply add (fmadd) integral SIMD registers via EmuSIMD helpers, but the provided SIMD register is not a supported integral SIMD register for this operation.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to fused multiply add (fmadd) integral SIMD registers via EmuSIMD helpers, but the provided Register_ type is not recognised as a supported SIMD register.");
		}
	}

	template<class Register_>
	[[nodiscard]] inline Register_ _fmsub_fp(Register_ to_mult_lhs_, Register_ to_mult_rhs_, Register_ to_sub_after_mult_)
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			using namespace EmuSIMD::Funcs;
			if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x4>)
			{
				return fmsub_f32x4(to_mult_lhs_, to_mult_rhs_, to_sub_after_mult_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x8>)
			{
				return fmsub_f32x8(to_mult_lhs_, to_mult_rhs_, to_sub_after_mult_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x16>)
			{
				return fmsub_f32x16(to_mult_lhs_, to_mult_rhs_, to_sub_after_mult_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x2>)
			{
				return fmsub_f64x2(to_mult_lhs_, to_mult_rhs_, to_sub_after_mult_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x4>)
			{
				return fmsub_f64x4(to_mult_lhs_, to_mult_rhs_, to_sub_after_mult_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x8>)
			{
				return fmsub_f64x8(to_mult_lhs_, to_mult_rhs_, to_sub_after_mult_);
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to fused multiply subtract (fmsub) three SIMD registers via EmuSIMD helpers, but the provided SIMD register is not a supported floating-point SIMD register.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to fused multiply subtract (fmsub) three SIMD registers via EmuSIMD helpers, but the provided Register_ type is not recognised as a support SIMD register.");
		}
	}
	template<std::size_t PerElementWidth_, class Register_>
	[[nodiscard]] inline Register_ _fmsub_int(Register_ to_mult_lhs_, Register_ to_mult_rhs_, Register_ to_sub_after_mult_)
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			if constexpr (EmuSIMD::TMP::_assert_valid_simd_int_element_width<PerElementWidth_>())
			{
				using namespace EmuSIMD::Funcs;
				if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i128_generic>)
				{
					if constexpr (PerElementWidth_ == 8)
					{
						return fmsub_i8x16(to_mult_lhs_, to_mult_rhs_, to_sub_after_mult_);
					}
					else if constexpr (PerElementWidth_ == 16)
					{
						return fmsub_i16x8(to_mult_lhs_, to_mult_rhs_, to_sub_after_mult_);
					}
					else if constexpr (PerElementWidth_ == 32)
					{
						return fmsub_i32x4(to_mult_lhs_, to_mult_rhs_, to_sub_after_mult_);
					}
					else if constexpr (PerElementWidth_ == 64)
					{
						return fmsub_i64x2(to_mult_lhs_, to_mult_rhs_, to_sub_after_mult_);
					}
					else
					{
						static_assert(EmuCore::TMP::get_false<std::size_t, PerElementWidth_>(), "Attempted to fused multiply subtract (fmsub) generic 128-bit integral SIMD registers via EmuSIMD helpers, but the provided PerElementWidth is invalid. Valid values are: 8, 16, 32, 64.");
					}
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i256_generic>)
				{
					if constexpr (PerElementWidth_ == 8)
					{
						return fmsub_i8x32(to_mult_lhs_, to_mult_rhs_, to_sub_after_mult_);
					}
					else if constexpr (PerElementWidth_ == 16)
					{
						return fmsub_i16x16(to_mult_lhs_, to_mult_rhs_, to_sub_after_mult_);
					}
					else if constexpr (PerElementWidth_ == 32)
					{
						return fmsub_i32x8(to_mult_lhs_, to_mult_rhs_, to_sub_after_mult_);
					}
					else if constexpr (PerElementWidth_ == 64)
					{
						return fmsub_i64x4(to_mult_lhs_, to_mult_rhs_, to_sub_after_mult_);
					}
					else
					{
						static_assert(EmuCore::TMP::get_false<std::size_t, PerElementWidth_>(), "Attempted to fused multiply subtract (fmsub) generic 256-bit integral SIMD registers via EmuSIMD helpers, but the provided PerElementWidth is invalid. Valid values are: 8, 16, 32, 64.");
					}
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i512_generic>)
				{
					if constexpr (PerElementWidth_ == 8)
					{
						return fmsub_i8x64(to_mult_lhs_, to_mult_rhs_, to_sub_after_mult_);
					}
					else if constexpr (PerElementWidth_ == 16)
					{
						return fmsub_i16x32(to_mult_lhs_, to_mult_rhs_, to_sub_after_mult_);
					}
					else if constexpr (PerElementWidth_ == 32)
					{
						return fmsub_i32x16(to_mult_lhs_, to_mult_rhs_, to_sub_after_mult_);
					}
					else if constexpr (PerElementWidth_ == 64)
					{
						return fmsub_i64x8(to_mult_lhs_, to_mult_rhs_, to_sub_after_mult_);
					}
					else
					{
						static_assert(EmuCore::TMP::get_false<std::size_t, PerElementWidth_>(), "Attempted to fused multiply subtract (fmsub) generic 512-bit integral SIMD registers via EmuSIMD helpers, but the provided PerElementWidth is invalid. Valid values are: 8, 16, 32, 64.");
					}
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i8x16>)
				{
					return fmsub_i8x16(to_mult_lhs_, to_mult_rhs_, to_sub_after_mult_);
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i8x32>)
				{
					return fmsub_i8x32(to_mult_lhs_, to_mult_rhs_, to_sub_after_mult_);
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i8x64>)
				{
					return fmsub_i8x64(to_mult_lhs_, to_mult_rhs_, to_sub_after_mult_);
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u8x16>)
				{
					return fmsub_u8x16(to_mult_lhs_, to_mult_rhs_, to_sub_after_mult_);
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u8x32>)
				{
					return fmsub_u8x32(to_mult_lhs_, to_mult_rhs_, to_sub_after_mult_);
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u8x64>)
				{
					return fmsub_u8x64(to_mult_lhs_, to_mult_rhs_, to_sub_after_mult_);
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i16x8>)
				{
					return fmsub_i16x8(to_mult_lhs_, to_mult_rhs_, to_sub_after_mult_);
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i16x16>)
				{
					return fmsub_i16x16(to_mult_lhs_, to_mult_rhs_, to_sub_after_mult_);
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i16x32>)
				{
					return fmsub_i16x32(to_mult_lhs_, to_mult_rhs_, to_sub_after_mult_);
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u16x8>)
				{
					return fmsub_u16x8(to_mult_lhs_, to_mult_rhs_, to_sub_after_mult_);
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u16x16>)
				{
					return fmsub_u16x16(to_mult_lhs_, to_mult_rhs_, to_sub_after_mult_);
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u16x32>)
				{
					return fmsub_u16x32(to_mult_lhs_, to_mult_rhs_, to_sub_after_mult_);
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i32x4>)
				{
					return fmsub_i32x4(to_mult_lhs_, to_mult_rhs_, to_sub_after_mult_);
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i32x8>)
				{
					return fmsub_i32x8(to_mult_lhs_, to_mult_rhs_, to_sub_after_mult_);
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i32x16>)
				{
					return fmsub_i32x16(to_mult_lhs_, to_mult_rhs_, to_sub_after_mult_);
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u32x4>)
				{
					return fmsub_u32x4(to_mult_lhs_, to_mult_rhs_, to_sub_after_mult_);
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u32x8>)
				{
					return fmsub_u32x8(to_mult_lhs_, to_mult_rhs_, to_sub_after_mult_);
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u32x16>)
				{
					return fmsub_u32x16(to_mult_lhs_, to_mult_rhs_, to_sub_after_mult_);
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i64x2>)
				{
					return fmsub_i64x2(to_mult_lhs_, to_mult_rhs_, to_sub_after_mult_);
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i64x4>)
				{
					return fmsub_i64x4(to_mult_lhs_, to_mult_rhs_, to_sub_after_mult_);
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i64x8>)
				{
					return fmsub_i64x8(to_mult_lhs_, to_mult_rhs_, to_sub_after_mult_);
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u64x2>)
				{
					return fmsub_u64x2(to_mult_lhs_, to_mult_rhs_, to_sub_after_mult_);
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u64x4>)
				{
					return fmsub_u64x4(to_mult_lhs_, to_mult_rhs_, to_sub_after_mult_);
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u64x8>)
				{
					return fmsub_u64x8(to_mult_lhs_, to_mult_rhs_, to_sub_after_mult_);
				}
				else
				{
					static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to fused multiply subtract (fmsub) integral SIMD registers via EmuSIMD helpers, but the provided integral SIMD register type is not supported for this operation.");
				}
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to fused multiply subtract (fmsub) integral SIMD registers via EmuSIMD helpers, but the provided SIMD register is not a supported integral SIMD register for this operation.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to fused multiply subtract (fmsub) integral SIMD registers via EmuSIMD helpers, but the provided Register_ type is not recognised as a supported SIMD register.");
		}
	}

	template<class Register_>
	[[nodiscard]] inline Register_ _fmaddsub_fp(Register_ to_mult_lhs_, Register_ to_mult_rhs_, Register_ to_add_sub_after_mult_)
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			using namespace EmuSIMD::Funcs;
			if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x4>)
			{
				return fmaddsub_f32x4(to_mult_lhs_, to_mult_rhs_, to_add_sub_after_mult_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x8>)
			{
				return fmaddsub_f32x8(to_mult_lhs_, to_mult_rhs_, to_add_sub_after_mult_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x16>)
			{
				return fmaddsub_f32x16(to_mult_lhs_, to_mult_rhs_, to_add_sub_after_mult_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x2>)
			{
				return fmaddsub_f64x2(to_mult_lhs_, to_mult_rhs_, to_add_sub_after_mult_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x4>)
			{
				return fmaddsub_f64x4(to_mult_lhs_, to_mult_rhs_, to_add_sub_after_mult_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x8>)
			{
				return fmaddsub_f64x8(to_mult_lhs_, to_mult_rhs_, to_add_sub_after_mult_);
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to fused multiply add/subtract (fmaddsub) three SIMD registers via EmuSIMD helpers, but the provided SIMD register is not a supported floating-point SIMD register.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to fused multiply add/subtract (fmaddsub) three SIMD registers via EmuSIMD helpers, but the provided Register_ type is not recognised as a support SIMD register.");
		}
	}
	template<std::size_t PerElementWidth_, class Register_>
	[[nodiscard]] inline Register_ _fmaddsub_int(Register_ to_mult_lhs_, Register_ to_mult_rhs_, Register_ to_add_sub_after_mult_)
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			if constexpr (EmuSIMD::TMP::_assert_valid_simd_int_element_width<PerElementWidth_>())
			{
				using namespace EmuSIMD::Funcs;
				if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i128_generic>)
				{
					if constexpr (PerElementWidth_ == 8)
					{
						return fmaddsub_i8x16(to_mult_lhs_, to_mult_rhs_, to_add_sub_after_mult_);
					}
					else if constexpr (PerElementWidth_ == 16)
					{
						return fmaddsub_i16x8(to_mult_lhs_, to_mult_rhs_, to_add_sub_after_mult_);
					}
					else if constexpr (PerElementWidth_ == 32)
					{
						return fmaddsub_i32x4(to_mult_lhs_, to_mult_rhs_, to_add_sub_after_mult_);
					}
					else if constexpr (PerElementWidth_ == 64)
					{
						return fmaddsub_i64x2(to_mult_lhs_, to_mult_rhs_, to_add_sub_after_mult_);
					}
					else
					{
						static_assert(EmuCore::TMP::get_false<std::size_t, PerElementWidth_>(), "Attempted to fused multiply add/subtract (fmaddsub) generic 128-bit integral SIMD registers via EmuSIMD helpers, but the provided PerElementWidth is invalid. Valid values are: 8, 16, 32, 64.");
					}
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i256_generic>)
				{
					if constexpr (PerElementWidth_ == 8)
					{
						return fmaddsub_i8x32(to_mult_lhs_, to_mult_rhs_, to_add_sub_after_mult_);
					}
					else if constexpr (PerElementWidth_ == 16)
					{
						return fmaddsub_i16x16(to_mult_lhs_, to_mult_rhs_, to_add_sub_after_mult_);
					}
					else if constexpr (PerElementWidth_ == 32)
					{
						return fmaddsub_i32x8(to_mult_lhs_, to_mult_rhs_, to_add_sub_after_mult_);
					}
					else if constexpr (PerElementWidth_ == 64)
					{
						return fmaddsub_i64x4(to_mult_lhs_, to_mult_rhs_, to_add_sub_after_mult_);
					}
					else
					{
						static_assert(EmuCore::TMP::get_false<std::size_t, PerElementWidth_>(), "Attempted to fused multiply add/subtract (fmaddsub) generic 256-bit integral SIMD registers via EmuSIMD helpers, but the provided PerElementWidth is invalid. Valid values are: 8, 16, 32, 64.");
					}
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i512_generic>)
				{
					if constexpr (PerElementWidth_ == 8)
					{
						return fmaddsub_i8x64(to_mult_lhs_, to_mult_rhs_, to_add_sub_after_mult_);
					}
					else if constexpr (PerElementWidth_ == 16)
					{
						return fmaddsub_i16x32(to_mult_lhs_, to_mult_rhs_, to_add_sub_after_mult_);
					}
					else if constexpr (PerElementWidth_ == 32)
					{
						return fmaddsub_i32x16(to_mult_lhs_, to_mult_rhs_, to_add_sub_after_mult_);
					}
					else if constexpr (PerElementWidth_ == 64)
					{
						return fmaddsub_i64x8(to_mult_lhs_, to_mult_rhs_, to_add_sub_after_mult_);
					}
					else
					{
						static_assert(EmuCore::TMP::get_false<std::size_t, PerElementWidth_>(), "Attempted to fused multiply add/subtract (fmaddsub) generic 512-bit integral SIMD registers via EmuSIMD helpers, but the provided PerElementWidth is invalid. Valid values are: 8, 16, 32, 64.");
					}
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i8x16>)
				{
					return fmaddsub_i8x16(to_mult_lhs_, to_mult_rhs_, to_add_sub_after_mult_);
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i8x32>)
				{
					return fmaddsub_i8x32(to_mult_lhs_, to_mult_rhs_, to_add_sub_after_mult_);
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i8x64>)
				{
					return fmaddsub_i8x64(to_mult_lhs_, to_mult_rhs_, to_add_sub_after_mult_);
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u8x16>)
				{
					return fmaddsub_u8x16(to_mult_lhs_, to_mult_rhs_, to_add_sub_after_mult_);
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u8x32>)
				{
					return fmaddsub_u8x32(to_mult_lhs_, to_mult_rhs_, to_add_sub_after_mult_);
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u8x64>)
				{
					return fmaddsub_u8x64(to_mult_lhs_, to_mult_rhs_, to_add_sub_after_mult_);
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i16x8>)
				{
					return fmaddsub_i16x8(to_mult_lhs_, to_mult_rhs_, to_add_sub_after_mult_);
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i16x16>)
				{
					return fmaddsub_i16x16(to_mult_lhs_, to_mult_rhs_, to_add_sub_after_mult_);
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i16x32>)
				{
					return fmaddsub_i16x32(to_mult_lhs_, to_mult_rhs_, to_add_sub_after_mult_);
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u16x8>)
				{
					return fmaddsub_u16x8(to_mult_lhs_, to_mult_rhs_, to_add_sub_after_mult_);
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u16x16>)
				{
					return fmaddsub_u16x16(to_mult_lhs_, to_mult_rhs_, to_add_sub_after_mult_);
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u16x32>)
				{
					return fmaddsub_u16x32(to_mult_lhs_, to_mult_rhs_, to_add_sub_after_mult_);
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i32x4>)
				{
					return fmaddsub_i32x4(to_mult_lhs_, to_mult_rhs_, to_add_sub_after_mult_);
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i32x8>)
				{
					return fmaddsub_i32x8(to_mult_lhs_, to_mult_rhs_, to_add_sub_after_mult_);
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i32x16>)
				{
					return fmaddsub_i32x16(to_mult_lhs_, to_mult_rhs_, to_add_sub_after_mult_);
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u32x4>)
				{
					return fmaddsub_u32x4(to_mult_lhs_, to_mult_rhs_, to_add_sub_after_mult_);
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u32x8>)
				{
					return fmaddsub_u32x8(to_mult_lhs_, to_mult_rhs_, to_add_sub_after_mult_);
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u32x16>)
				{
					return fmaddsub_u32x16(to_mult_lhs_, to_mult_rhs_, to_add_sub_after_mult_);
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i64x2>)
				{
					return fmaddsub_i64x2(to_mult_lhs_, to_mult_rhs_, to_add_sub_after_mult_);
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i64x4>)
				{
					return fmaddsub_i64x4(to_mult_lhs_, to_mult_rhs_, to_add_sub_after_mult_);
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i64x8>)
				{
					return fmaddsub_i64x8(to_mult_lhs_, to_mult_rhs_, to_add_sub_after_mult_);
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u64x2>)
				{
					return fmaddsub_u64x2(to_mult_lhs_, to_mult_rhs_, to_add_sub_after_mult_);
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u64x4>)
				{
					return fmaddsub_u64x4(to_mult_lhs_, to_mult_rhs_, to_add_sub_after_mult_);
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u64x8>)
				{
					return fmaddsub_u64x8(to_mult_lhs_, to_mult_rhs_, to_add_sub_after_mult_);
				}
				else
				{
					static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to fused multiply add/subtract (fmaddsub) integral SIMD registers via EmuSIMD helpers, but the provided integral SIMD register type is not supported for this operation.");
				}
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to fused multiply add/subtract (fmaddsub) integral SIMD registers via EmuSIMD helpers, but the provided SIMD register is not a supported integral SIMD register for this operation.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to fused multiply add/subtract (fmaddsub) integral SIMD registers via EmuSIMD helpers, but the provided Register_ type is not recognised as a supported SIMD register.");
		}
	}

	template<class Register_>
	[[nodiscard]] inline Register_ _fmsubadd_fp(Register_ to_mult_lhs_, Register_ to_mult_rhs_, Register_ to_sub_add_after_mult_)
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			using namespace EmuSIMD::Funcs;
			if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x4>)
			{
				return fmsubadd_f32x4(to_mult_lhs_, to_mult_rhs_, to_sub_add_after_mult_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x8>)
			{
				return fmsubadd_f32x8(to_mult_lhs_, to_mult_rhs_, to_sub_add_after_mult_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x16>)
			{
				return fmsubadd_f32x16(to_mult_lhs_, to_mult_rhs_, to_sub_add_after_mult_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x2>)
			{
				return fmsubadd_f64x2(to_mult_lhs_, to_mult_rhs_, to_sub_add_after_mult_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x4>)
			{
				return fmsubadd_f64x4(to_mult_lhs_, to_mult_rhs_, to_sub_add_after_mult_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x8>)
			{
				return fmsubadd_f64x8(to_mult_lhs_, to_mult_rhs_, to_sub_add_after_mult_);
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to fused multiply subtract/add (fmsubadd) three SIMD registers via EmuSIMD helpers, but the provided SIMD register is not a supported floating-point SIMD register.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to fused multiply subtract/add (fmsubadd) three SIMD registers via EmuSIMD helpers, but the provided Register_ type is not recognised as a support SIMD register.");
		}
	}
	template<std::size_t PerElementWidth_, class Register_>
	[[nodiscard]] inline Register_ _fmsubadd_int(Register_ to_mult_lhs_, Register_ to_mult_rhs_, Register_ to_sub_add_after_mult_)
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			if constexpr (EmuSIMD::TMP::_assert_valid_simd_int_element_width<PerElementWidth_>())
			{
				using namespace EmuSIMD::Funcs;
				if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i128_generic>)
				{
					if constexpr (PerElementWidth_ == 8)
					{
						return fmsubadd_i8x16(to_mult_lhs_, to_mult_rhs_, to_sub_add_after_mult_);
					}
					else if constexpr (PerElementWidth_ == 16)
					{
						return fmsubadd_i16x8(to_mult_lhs_, to_mult_rhs_, to_sub_add_after_mult_);
					}
					else if constexpr (PerElementWidth_ == 32)
					{
						return fmsubadd_i32x4(to_mult_lhs_, to_mult_rhs_, to_sub_add_after_mult_);
					}
					else if constexpr (PerElementWidth_ == 64)
					{
						return fmsubadd_i64x2(to_mult_lhs_, to_mult_rhs_, to_sub_add_after_mult_);
					}
					else
					{
						static_assert(EmuCore::TMP::get_false<std::size_t, PerElementWidth_>(), "Attempted to fused multiply subtract/add (fmsubadd) generic 128-bit integral SIMD registers via EmuSIMD helpers, but the provided PerElementWidth is invalid. Valid values are: 8, 16, 32, 64.");
					}
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i256_generic>)
				{
					if constexpr (PerElementWidth_ == 8)
					{
						return fmsubadd_i8x32(to_mult_lhs_, to_mult_rhs_, to_sub_add_after_mult_);
					}
					else if constexpr (PerElementWidth_ == 16)
					{
						return fmsubadd_i16x16(to_mult_lhs_, to_mult_rhs_, to_sub_add_after_mult_);
					}
					else if constexpr (PerElementWidth_ == 32)
					{
						return fmsubadd_i32x8(to_mult_lhs_, to_mult_rhs_, to_sub_add_after_mult_);
					}
					else if constexpr (PerElementWidth_ == 64)
					{
						return fmsubadd_i64x4(to_mult_lhs_, to_mult_rhs_, to_sub_add_after_mult_);
					}
					else
					{
						static_assert(EmuCore::TMP::get_false<std::size_t, PerElementWidth_>(), "Attempted to fused multiply subtract/add (fmsubadd) generic 256-bit integral SIMD registers via EmuSIMD helpers, but the provided PerElementWidth is invalid. Valid values are: 8, 16, 32, 64.");
					}
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i512_generic>)
				{
					if constexpr (PerElementWidth_ == 8)
					{
						return fmsubadd_i8x64(to_mult_lhs_, to_mult_rhs_, to_sub_add_after_mult_);
					}
					else if constexpr (PerElementWidth_ == 16)
					{
						return fmsubadd_i16x32(to_mult_lhs_, to_mult_rhs_, to_sub_add_after_mult_);
					}
					else if constexpr (PerElementWidth_ == 32)
					{
						return fmsubadd_i32x16(to_mult_lhs_, to_mult_rhs_, to_sub_add_after_mult_);
					}
					else if constexpr (PerElementWidth_ == 64)
					{
						return fmsubadd_i64x8(to_mult_lhs_, to_mult_rhs_, to_sub_add_after_mult_);
					}
					else
					{
						static_assert(EmuCore::TMP::get_false<std::size_t, PerElementWidth_>(), "Attempted to fused multiply subtract/add (fmsubadd) generic 512-bit integral SIMD registers via EmuSIMD helpers, but the provided PerElementWidth is invalid. Valid values are: 8, 16, 32, 64.");
					}
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i8x16>)
				{
					return fmsubadd_i8x16(to_mult_lhs_, to_mult_rhs_, to_sub_add_after_mult_);
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i8x32>)
				{
					return fmsubadd_i8x32(to_mult_lhs_, to_mult_rhs_, to_sub_add_after_mult_);
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i8x64>)
				{
					return fmsubadd_i8x64(to_mult_lhs_, to_mult_rhs_, to_sub_add_after_mult_);
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u8x16>)
				{
					return fmsubadd_u8x16(to_mult_lhs_, to_mult_rhs_, to_sub_add_after_mult_);
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u8x32>)
				{
					return fmsubadd_u8x32(to_mult_lhs_, to_mult_rhs_, to_sub_add_after_mult_);
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u8x64>)
				{
					return fmsubadd_u8x64(to_mult_lhs_, to_mult_rhs_, to_sub_add_after_mult_);
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i16x8>)
				{
					return fmsubadd_i16x8(to_mult_lhs_, to_mult_rhs_, to_sub_add_after_mult_);
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i16x16>)
				{
					return fmsubadd_i16x16(to_mult_lhs_, to_mult_rhs_, to_sub_add_after_mult_);
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i16x32>)
				{
					return fmsubadd_i16x32(to_mult_lhs_, to_mult_rhs_, to_sub_add_after_mult_);
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u16x8>)
				{
					return fmsubadd_u16x8(to_mult_lhs_, to_mult_rhs_, to_sub_add_after_mult_);
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u16x16>)
				{
					return fmsubadd_u16x16(to_mult_lhs_, to_mult_rhs_, to_sub_add_after_mult_);
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u16x32>)
				{
					return fmsubadd_u16x32(to_mult_lhs_, to_mult_rhs_, to_sub_add_after_mult_);
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i32x4>)
				{
					return fmsubadd_i32x4(to_mult_lhs_, to_mult_rhs_, to_sub_add_after_mult_);
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i32x8>)
				{
					return fmsubadd_i32x8(to_mult_lhs_, to_mult_rhs_, to_sub_add_after_mult_);
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i32x16>)
				{
					return fmsubadd_i32x16(to_mult_lhs_, to_mult_rhs_, to_sub_add_after_mult_);
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u32x4>)
				{
					return fmsubadd_u32x4(to_mult_lhs_, to_mult_rhs_, to_sub_add_after_mult_);
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u32x8>)
				{
					return fmsubadd_u32x8(to_mult_lhs_, to_mult_rhs_, to_sub_add_after_mult_);
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u32x16>)
				{
					return fmsubadd_u32x16(to_mult_lhs_, to_mult_rhs_, to_sub_add_after_mult_);
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i64x2>)
				{
					return fmsubadd_i64x2(to_mult_lhs_, to_mult_rhs_, to_sub_add_after_mult_);
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i64x4>)
				{
					return fmsubadd_i64x4(to_mult_lhs_, to_mult_rhs_, to_sub_add_after_mult_);
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i64x8>)
				{
					return fmsubadd_i64x8(to_mult_lhs_, to_mult_rhs_, to_sub_add_after_mult_);
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u64x2>)
				{
					return fmsubadd_u64x2(to_mult_lhs_, to_mult_rhs_, to_sub_add_after_mult_);
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u64x4>)
				{
					return fmsubadd_u64x4(to_mult_lhs_, to_mult_rhs_, to_sub_add_after_mult_);
				}
				else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u64x8>)
				{
					return fmsubadd_u64x8(to_mult_lhs_, to_mult_rhs_, to_sub_add_after_mult_);
				}
				else
				{
					static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to fused multiply subtract/add (fmsubadd) integral SIMD registers via EmuSIMD helpers, but the provided integral SIMD register type is not supported for this operation.");
				}
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to fused multiply subtract/add (fmsubadd) integral SIMD registers via EmuSIMD helpers, but the provided SIMD register is not a supported integral SIMD register for this operation.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to fused multiply subtract/add (fmsubadd) integral SIMD registers via EmuSIMD helpers, but the provided Register_ type is not recognised as a supported SIMD register.");
		}
	}
#pragma endregion

#pragma region ROUNDS
	template<int RoundingMode_, class Register_>
	[[nodiscard]] inline Register_ _round(Register_ register_)
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			using namespace EmuSIMD::Funcs;
			if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x4>)
			{
				return round_f32x4<RoundingMode_>(register_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x8>)
			{
				return round_f32x8<RoundingMode_>(register_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x16>)
			{
				return round_f64x8<RoundingMode_>(register_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x2>)
			{
				return round_f64x2<RoundingMode_>(register_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x4>)
			{
				return round_f64x4<RoundingMode_>(register_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x8>)
			{
				return round_f64x8<RoundingMode_>(register_);
			}
			else if constexpr (EmuSIMD::TMP::is_integral_simd_register_v<register_type_uq>)
			{
				// If integral, there is no round to be done
				return register_;
			}
			else
			{
				// Potentially requires a round but we don't know how to do it
				static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to round a SIMD register via EmuSIMD helpers, but the provided non-integral SIMD register is not supported for this operation.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to round a SIMD register via EmuSIMD helpers, but the provided Register_ type is not recognised as a supported SIMD register.");
		}
	}

	template<class Register_>
	[[nodiscard]] inline Register_ _floor(Register_ register_)
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			using namespace EmuSIMD::Funcs;
			if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x4>)
			{
				return floor_f32x4(register_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x8>)
			{
				return floor_f32x8(register_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x16>)
			{
				return floor_f32x16(register_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x2>)
			{
				return floor_f64x2(register_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x4>)
			{
				return floor_f64x4(register_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x8>)
			{
				return floor_f64x8(register_);
			}
			else if constexpr (EmuSIMD::TMP::is_integral_simd_register_v<register_type_uq>)
			{
				// If integral, there is no round to be done
				return register_;
			}
			else
			{
				// Potentially requires a round but we don't know how to do it
				static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to floor a SIMD register via EmuSIMD helpers, but the provided non-integral SIMD register is not supported for this operation.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to floor a SIMD register via EmuSIMD helpers, but the provided Register_ type is not recognised as a supported SIMD register.");
		}
	}

	template<class Register_>
	[[nodiscard]] inline Register_ _ceil(Register_ register_)
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			using namespace EmuSIMD::Funcs;
			if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x4>)
			{
				return ceil_f32x4(register_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x8>)
			{
				return ceil_f32x8(register_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x16>)
			{
				return ceil_f32x16(register_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x2>)
			{
				return ceil_f64x2(register_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x4>)
			{
				return ceil_f64x4(register_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x8>)
			{
				return ceil_f64x8(register_);
			}
			else if constexpr (EmuSIMD::TMP::is_integral_simd_register_v<register_type_uq>)
			{
				// If integral, there is no round to be done
				return register_;
			}
			else
			{
				// Potentially requires a round but we don't know how to do it
				static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to ceil a SIMD register via EmuSIMD helpers, but the provided non-integral SIMD register is not supported for this operation.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to ceil a SIMD register via EmuSIMD helpers, but the provided Register_ type is not recognised as a supported SIMD register.");
		}
	}

	template<class Register_>
	[[nodiscard]] inline Register_ _trunc(Register_ register_)
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			using namespace EmuSIMD::Funcs;
			if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x4>)
			{
				return trunc_f32x4(register_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x8>)
			{
				return trunc_f32x8(register_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x16>)
			{
				return trunc_f32x16(register_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x2>)
			{
				return trunc_f64x2(register_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x4>)
			{
				return trunc_f64x4(register_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x8>)
			{
				return trunc_f64x8(register_);
			}
			else if constexpr (EmuSIMD::TMP::is_integral_simd_register_v<register_type_uq>)
			{
				// If integral, there is no round to be done
				return register_;
			}
			else
			{
				// Potentially requires a round but we don't know how to do it
				static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to truncate a SIMD register via EmuSIMD helpers, but the provided non-integral SIMD register is not supported for this operation.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to truncate a SIMD register via EmuSIMD helpers, but the provided Register_ type is not recognised as a supported SIMD register.");
		}
	}
#pragma endregion

#pragma region MIN_MAX_OPS
	template<std::size_t PerElementWidthIfInt_, bool SignedIfInt_, class Register_>
	[[nodiscard]] inline Register_ _min(Register_ a_, Register_ b_)
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			using namespace EmuSIMD::Funcs;
			if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x4>)
			{
				return min_f32x4(a_, b_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x8>)
			{
				return min_f32x8(a_, b_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x16>)
			{
				return min_f32x16(a_, b_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x2>)
			{
				return min_f64x2(a_, b_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x4>)
			{
				return min_f64x4(a_, b_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x8>)
			{
				return min_f64x8(a_, b_);
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
								return min_i8x16(a_, b_);
							}
							else
							{
								return min_u8x16(a_, b_);
							}
						}
						else if constexpr (PerElementWidthIfInt_ == 16)
						{
							if constexpr (SignedIfInt_)
							{
								return min_i16x8(a_, b_);
							}
							else
							{
								return min_u16x8(a_, b_);
							}
						}
						else if constexpr (PerElementWidthIfInt_ == 32)
						{
							if constexpr (SignedIfInt_)
							{
								return min_i32x4(a_, b_);
							}
							else
							{
								return min_u32x4(a_, b_);
							}
						}
						else
						{
							if constexpr (SignedIfInt_)
							{
								return min_i64x2(a_, b_);
							}
							else
							{
								return min_u64x2(a_, b_);
							}
						}
					}
					else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i256_generic>)
					{
						if constexpr (PerElementWidthIfInt_ == 8)
						{
							if constexpr (SignedIfInt_)
							{
								return min_i8x32(a_, b_);
							}
							else
							{
								return min_u8x32(a_, b_);
							}
						}
						else if constexpr (PerElementWidthIfInt_ == 16)
						{
							if constexpr (SignedIfInt_)
							{
								return min_i16x16(a_, b_);
							}
							else
							{
								return min_u16x16(a_, b_);
							}
						}
						else if constexpr (PerElementWidthIfInt_ == 32)
						{
							if constexpr (SignedIfInt_)
							{
								return min_i32x8(a_, b_);
							}
							else
							{
								return min_u32x8(a_, b_);
							}
						}
						else
						{
							if constexpr (SignedIfInt_)
							{
								return min_i64x4(a_, b_);
							}
							else
							{
								return min_u64x4(a_, b_);
							}
						}
					}
					else
					{
						if constexpr (PerElementWidthIfInt_ == 8)
						{
							if constexpr (SignedIfInt_)
							{
								return min_i8x64(a_, b_);
							}
							else
							{
								return min_u8x64(a_, b_);
							}
						}
						else if constexpr (PerElementWidthIfInt_ == 16)
						{
							if constexpr (SignedIfInt_)
							{
								return min_i16x32(a_, b_);
							}
							else
							{
								return min_u16x32(a_, b_);
							}
						}
						else if constexpr (PerElementWidthIfInt_ == 32)
						{
							if constexpr (SignedIfInt_)
							{
								return min_i32x16(a_, b_);
							}
							else
							{
								return min_u32x16(a_, b_);
							}
						}
						else
						{
							if constexpr (SignedIfInt_)
							{
								return min_i64x8(a_, b_);
							}
							else
							{
								return min_u64x8(a_, b_);
							}
						}
					}
				}
				else
				{
					static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to find the minimum elements in two SIMD registers via EmuSIMD helpers, but the provided PerElementWidth_ is invalid.");
				}
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i8x16>)
			{
				return min_i8x16(a_, b_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i8x32>)
			{
				return min_i8x32(a_, b_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i8x64>)
			{
				return min_i8x64(a_, b_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u8x16>)
			{
				return min_u8x16(a_, b_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u8x32>)
			{
				return min_u8x32(a_, b_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u8x64>)
			{
				return min_u8x64(a_, b_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i16x8>)
			{
				return min_i16x8(a_, b_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i16x16>)
			{
				return min_i16x16(a_, b_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i16x32>)
			{
				return min_i16x32(a_, b_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u16x8>)
			{
				return min_u16x8(a_, b_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u16x16>)
			{
				return min_u16x16(a_, b_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u16x32>)
			{
				return min_u16x32(a_, b_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i32x4>)
			{
				return min_i32x4(a_, b_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i32x8>)
			{
				return min_i32x8(a_, b_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i32x16>)
			{
				return min_i32x16(a_, b_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u32x4>)
			{
				return min_u32x4(a_, b_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u32x8>)
			{
				return min_u32x8(a_, b_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u32x16>)
			{
				return min_u32x16(a_, b_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i64x2>)
			{
				return min_i64x2(a_, b_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i64x4>)
			{
				return min_i64x4(a_, b_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i64x8>)
			{
				return min_i64x8(a_, b_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u64x2>)
			{
				return min_u64x2(a_, b_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u64x4>)
			{
				return min_u64x4(a_, b_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u64x8>)
			{
				return min_u64x8(a_, b_);
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to find the minimum elements in two SIMD registers via EmuSIMD registers, but the passed Register_ type is not supported for this operation.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to find the minimum elements in two SIMD registers via EmuSIMD helpers, but the provided Register_ type is not recognised as a supported SIMD register.");
		}
	}

	template<std::size_t PerElementWidthIfInt_, bool SignedIfInt_, class Register_>
	[[nodiscard]] inline Register_ _max(Register_ a_, Register_ b_)
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			using namespace EmuSIMD::Funcs;
			if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x4>)
			{
				return max_f32x4(a_, b_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x8>)
			{
				return max_f32x8(a_, b_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x16>)
			{
				return max_f32x16(a_, b_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x2>)
			{
				return max_f64x2(a_, b_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x4>)
			{
				return max_f64x4(a_, b_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x8>)
			{
				return max_f64x8(a_, b_);
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
								return max_i8x16(a_, b_);
							}
							else
							{
								return max_u8x16(a_, b_);
							}
						}
						else if constexpr (PerElementWidthIfInt_ == 16)
						{
							if constexpr (SignedIfInt_)
							{
								return max_i16x8(a_, b_);
							}
							else
							{
								return max_u16x8(a_, b_);
							}
						}
						else if constexpr (PerElementWidthIfInt_ == 32)
						{
							if constexpr (SignedIfInt_)
							{
								return max_i32x4(a_, b_);
							}
							else
							{
								return max_u32x4(a_, b_);
							}
						}
						else
						{
							if constexpr (SignedIfInt_)
							{
								return max_i64x2(a_, b_);
							}
							else
							{
								return max_u64x2(a_, b_);
							}
						}
					}
					else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i256_generic>)
					{
						if constexpr (PerElementWidthIfInt_ == 8)
						{
							if constexpr (SignedIfInt_)
							{
								return max_i8x32(a_, b_);
							}
							else
							{
								return max_u8x32(a_, b_);
							}
						}
						else if constexpr (PerElementWidthIfInt_ == 16)
						{
							if constexpr (SignedIfInt_)
							{
								return max_i16x16(a_, b_);
							}
							else
							{
								return max_u16x16(a_, b_);
							}
						}
						else if constexpr (PerElementWidthIfInt_ == 32)
						{
							if constexpr (SignedIfInt_)
							{
								return max_i32x8(a_, b_);
							}
							else
							{
								return max_u32x8(a_, b_);
							}
						}
						else
						{
							if constexpr (SignedIfInt_)
							{
								return max_i64x4(a_, b_);
							}
							else
							{
								return max_u64x4(a_, b_);
							}
						}
					}
					else
					{
						if constexpr (PerElementWidthIfInt_ == 8)
						{
							if constexpr (SignedIfInt_)
							{
								return max_i8x64(a_, b_);
							}
							else
							{
								return max_u8x64(a_, b_);
							}
						}
						else if constexpr (PerElementWidthIfInt_ == 16)
						{
							if constexpr (SignedIfInt_)
							{
								return max_i16x32(a_, b_);
							}
							else
							{
								return max_u16x32(a_, b_);
							}
						}
						else if constexpr (PerElementWidthIfInt_ == 32)
						{
							if constexpr (SignedIfInt_)
							{
								return max_i32x16(a_, b_);
							}
							else
							{
								return max_u32x16(a_, b_);
							}
						}
						else
						{
							if constexpr (SignedIfInt_)
							{
								return max_i64x8(a_, b_);
							}
							else
							{
								return max_u64x8(a_, b_);
							}
						}
					}
				}
				else
				{
					static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to find the maximum elements in two SIMD registers via EmuSIMD helpers, but the provided PerElementWidth_ is invalid.");
				}
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i8x16>)
			{
				return max_i8x16(a_, b_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i8x32>)
			{
				return max_i8x32(a_, b_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i8x64>)
			{
				return max_i8x64(a_, b_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u8x16>)
			{
				return max_u8x16(a_, b_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u8x32>)
			{
				return max_u8x32(a_, b_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u8x64>)
			{
				return max_u8x64(a_, b_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i16x8>)
			{
				return max_i16x8(a_, b_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i16x16>)
			{
				return max_i16x16(a_, b_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i16x32>)
			{
				return max_i16x32(a_, b_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u16x8>)
			{
				return max_u16x8(a_, b_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u16x16>)
			{
				return max_u16x16(a_, b_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u16x32>)
			{
				return max_u16x32(a_, b_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i32x4>)
			{
				return max_i32x4(a_, b_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i32x8>)
			{
				return max_i32x8(a_, b_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i32x16>)
			{
				return max_i32x16(a_, b_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u32x4>)
			{
				return max_u32x4(a_, b_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u32x8>)
			{
				return max_u32x8(a_, b_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u32x16>)
			{
				return max_u32x16(a_, b_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i64x2>)
			{
				return max_i64x2(a_, b_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i64x4>)
			{
				return max_i64x4(a_, b_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i64x8>)
			{
				return max_i64x8(a_, b_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u64x2>)
			{
				return max_u64x2(a_, b_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u64x4>)
			{
				return max_u64x4(a_, b_);
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u64x8>)
			{
				return max_u64x8(a_, b_);
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to find the maximum elements in two SIMD registers via EmuSIMD registers, but the passed Register_ type is not supported for this operation.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to find the maximum elements in two SIMD registers via EmuSIMD helpers, but the provided Register_ type is not recognised as a supported SIMD register.");
		}
	}

	template<std::size_t PerElementWidthIfInt_, bool SignedIfInt_, EmuConcepts::KnownSIMD Register_>
	[[nodiscard]] inline auto _horizontal_max(Register_&& a_)
		-> typename std::remove_cvref<Register_>::type
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			using namespace EmuSIMD::Funcs;
			if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x4>)
			{
				return horizontal_max_f32x4(std::forward<Register_>(a_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x8>)
			{
				return horizontal_max_f32x8(std::forward<Register_>(a_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x16>)
			{
				return horizontal_max_f32x16(std::forward<Register_>(a_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x2>)
			{
				return horizontal_max_f64x2(std::forward<Register_>(a_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x4>)
			{
				return horizontal_max_f64x4(std::forward<Register_>(a_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x8>)
			{
				return horizontal_max_f64x8(std::forward<Register_>(a_));
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
								return horizontal_max_i8x16(std::forward<Register_>(a_));
							}
							else
							{
								return horizontal_max_u8x16(std::forward<Register_>(a_));
							}
						}
						else if constexpr (PerElementWidthIfInt_ == 16)
						{
							if constexpr (SignedIfInt_)
							{
								return horizontal_max_i16x8(std::forward<Register_>(a_));
							}
							else
							{
								return horizontal_max_u16x8(std::forward<Register_>(a_));
							}
						}
						else if constexpr (PerElementWidthIfInt_ == 32)
						{
							if constexpr (SignedIfInt_)
							{
								return horizontal_max_i32x4(std::forward<Register_>(a_));
							}
							else
							{
								return horizontal_max_u32x4(std::forward<Register_>(a_));
							}
						}
						else
						{
							if constexpr (SignedIfInt_)
							{
								return horizontal_max_i64x2(std::forward<Register_>(a_));
							}
							else
							{
								return horizontal_max_u64x2(std::forward<Register_>(a_));
							}
						}
					}
					else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i256_generic>)
					{
						if constexpr (PerElementWidthIfInt_ == 8)
						{
							if constexpr (SignedIfInt_)
							{
								return horizontal_max_i8x32(std::forward<Register_>(a_));
							}
							else
							{
								return horizontal_max_u8x32(std::forward<Register_>(a_));
							}
						}
						else if constexpr (PerElementWidthIfInt_ == 16)
						{
							if constexpr (SignedIfInt_)
							{
								return horizontal_max_i16x16(std::forward<Register_>(a_));
							}
							else
							{
								return horizontal_max_u16x16(std::forward<Register_>(a_));
							}
						}
						else if constexpr (PerElementWidthIfInt_ == 32)
						{
							if constexpr (SignedIfInt_)
							{
								return horizontal_max_i32x8(std::forward<Register_>(a_));
							}
							else
							{
								return horizontal_max_u32x8(std::forward<Register_>(a_));
							}
						}
						else
						{
							if constexpr (SignedIfInt_)
							{
								return horizontal_max_i64x4(std::forward<Register_>(a_));
							}
							else
							{
								return horizontal_max_u64x4(std::forward<Register_>(a_));
							}
						}
					}
					else
					{
						if constexpr (PerElementWidthIfInt_ == 8)
						{
							if constexpr (SignedIfInt_)
							{
								return horizontal_max_i8x64(std::forward<Register_>(a_));
							}
							else
							{
								return horizontal_max_u8x64(std::forward<Register_>(a_));
							}
						}
						else if constexpr (PerElementWidthIfInt_ == 16)
						{
							if constexpr (SignedIfInt_)
							{
								return horizontal_max_i16x32(std::forward<Register_>(a_));
							}
							else
							{
								return horizontal_max_u16x32(std::forward<Register_>(a_));
							}
						}
						else if constexpr (PerElementWidthIfInt_ == 32)
						{
							if constexpr (SignedIfInt_)
							{
								return horizontal_max_i32x16(std::forward<Register_>(a_));
							}
							else
							{
								return horizontal_max_u32x16(std::forward<Register_>(a_));
							}
						}
						else
						{
							if constexpr (SignedIfInt_)
							{
								return horizontal_max_i64x8(std::forward<Register_>(a_));
							}
							else
							{
								return horizontal_max_u64x8(std::forward<Register_>(a_));
							}
						}
					}
				}
				else
				{
					static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to find the maximum element in a SIMD register via EmuSIMD helpers, but the provided PerElementWidth_ is invalid.");
				}
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i8x16>)
			{
				return horizontal_max_i8x16(std::forward<Register_>(a_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i8x32>)
			{
				return horizontal_max_i8x32(std::forward<Register_>(a_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i8x64>)
			{
				return horizontal_max_i8x64(std::forward<Register_>(a_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u8x16>)
			{
				return horizontal_max_u8x16(std::forward<Register_>(a_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u8x32>)
			{
				return horizontal_max_u8x32(std::forward<Register_>(a_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u8x64>)
			{
				return horizontal_max_u8x64(std::forward<Register_>(a_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i16x8>)
			{
				return horizontal_max_i16x8(std::forward<Register_>(a_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i16x16>)
			{
				return horizontal_max_i16x16(std::forward<Register_>(a_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i16x32>)
			{
				return horizontal_max_i16x32(std::forward<Register_>(a_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u16x8>)
			{
				return horizontal_max_u16x8(std::forward<Register_>(a_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u16x16>)
			{
				return horizontal_max_u16x16(std::forward<Register_>(a_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u16x32>)
			{
				return horizontal_max_u16x32(std::forward<Register_>(a_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i32x4>)
			{
				return horizontal_max_i32x4(std::forward<Register_>(a_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i32x8>)
			{
				return horizontal_max_i32x8(std::forward<Register_>(a_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i32x16>)
			{
				return horizontal_max_i32x16(std::forward<Register_>(a_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u32x4>)
			{
				return horizontal_max_u32x4(std::forward<Register_>(a_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u32x8>)
			{
				return horizontal_max_u32x8(std::forward<Register_>(a_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u32x16>)
			{
				return horizontal_max_u32x16(std::forward<Register_>(a_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i64x2>)
			{
				return horizontal_max_i64x2(std::forward<Register_>(a_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i64x4>)
			{
				return horizontal_max_i64x4(std::forward<Register_>(a_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i64x8>)
			{
				return horizontal_max_i64x8(std::forward<Register_>(a_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u64x2>)
			{
				return horizontal_max_u64x2(std::forward<Register_>(a_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u64x4>)
			{
				return horizontal_max_u64x4(std::forward<Register_>(a_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u64x8>)
			{
				return horizontal_max_u64x8(std::forward<Register_>(a_));
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to find the maximum element in a SIMD register via EmuSIMD registers, but the passed Register_ type is not supported for this operation.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to find the maximum element in a SIMD register via EmuSIMD helpers, but the provided Register_ type is not recognised as a supported SIMD register.");
		}
	}

	template<std::size_t PerElementWidthIfInt_, bool SignedIfInt_, EmuConcepts::KnownSIMD Register_>
	[[nodiscard]] inline auto _horizontal_max_fill(Register_&& a_)
		-> typename std::remove_cvref<Register_>::type
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			using namespace EmuSIMD::Funcs;
			if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x4>)
			{
				return horizontal_max_fill_f32x4(std::forward<Register_>(a_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x8>)
			{
				return horizontal_max_fill_f32x8(std::forward<Register_>(a_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x16>)
			{
				return horizontal_max_fill_f32x16(std::forward<Register_>(a_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x2>)
			{
				return horizontal_max_fill_f64x2(std::forward<Register_>(a_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x4>)
			{
				return horizontal_max_fill_f64x4(std::forward<Register_>(a_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x8>)
			{
				return horizontal_max_fill_f64x8(std::forward<Register_>(a_));
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
								return horizontal_max_fill_i8x16(std::forward<Register_>(a_));
							}
							else
							{
								return horizontal_max_fill_u8x16(std::forward<Register_>(a_));
							}
						}
						else if constexpr (PerElementWidthIfInt_ == 16)
						{
							if constexpr (SignedIfInt_)
							{
								return horizontal_max_fill_i16x8(std::forward<Register_>(a_));
							}
							else
							{
								return horizontal_max_fill_u16x8(std::forward<Register_>(a_));
							}
						}
						else if constexpr (PerElementWidthIfInt_ == 32)
						{
							if constexpr (SignedIfInt_)
							{
								return horizontal_max_fill_i32x4(std::forward<Register_>(a_));
							}
							else
							{
								return horizontal_max_fill_u32x4(std::forward<Register_>(a_));
							}
						}
						else
						{
							if constexpr (SignedIfInt_)
							{
								return horizontal_max_fill_i64x2(std::forward<Register_>(a_));
							}
							else
							{
								return horizontal_max_fill_u64x2(std::forward<Register_>(a_));
							}
						}
					}
					else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i256_generic>)
					{
						if constexpr (PerElementWidthIfInt_ == 8)
						{
							if constexpr (SignedIfInt_)
							{
								return horizontal_max_fill_i8x32(std::forward<Register_>(a_));
							}
							else
							{
								return horizontal_max_fill_u8x32(std::forward<Register_>(a_));
							}
						}
						else if constexpr (PerElementWidthIfInt_ == 16)
						{
							if constexpr (SignedIfInt_)
							{
								return horizontal_max_fill_i16x16(std::forward<Register_>(a_));
							}
							else
							{
								return horizontal_max_fill_u16x16(std::forward<Register_>(a_));
							}
						}
						else if constexpr (PerElementWidthIfInt_ == 32)
						{
							if constexpr (SignedIfInt_)
							{
								return horizontal_max_fill_i32x8(std::forward<Register_>(a_));
							}
							else
							{
								return horizontal_max_fill_u32x8(std::forward<Register_>(a_));
							}
						}
						else
						{
							if constexpr (SignedIfInt_)
							{
								return horizontal_max_fill_i64x4(std::forward<Register_>(a_));
							}
							else
							{
								return horizontal_max_fill_u64x4(std::forward<Register_>(a_));
							}
						}
					}
					else
					{
						if constexpr (PerElementWidthIfInt_ == 8)
						{
							if constexpr (SignedIfInt_)
							{
								return horizontal_max_fill_i8x64(std::forward<Register_>(a_));
							}
							else
							{
								return horizontal_max_fill_u8x64(std::forward<Register_>(a_));
							}
						}
						else if constexpr (PerElementWidthIfInt_ == 16)
						{
							if constexpr (SignedIfInt_)
							{
								return horizontal_max_fill_i16x32(std::forward<Register_>(a_));
							}
							else
							{
								return horizontal_max_fill_u16x32(std::forward<Register_>(a_));
							}
						}
						else if constexpr (PerElementWidthIfInt_ == 32)
						{
							if constexpr (SignedIfInt_)
							{
								return horizontal_max_fill_i32x16(std::forward<Register_>(a_));
							}
							else
							{
								return horizontal_max_fill_u32x16(std::forward<Register_>(a_));
							}
						}
						else
						{
							if constexpr (SignedIfInt_)
							{
								return horizontal_max_fill_i64x8(std::forward<Register_>(a_));
							}
							else
							{
								return horizontal_max_fill_u64x8(std::forward<Register_>(a_));
							}
						}
					}
				}
				else
				{
					static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to find the maximum element in a SIMD register via EmuSIMD helpers, but the provided PerElementWidth_ is invalid.");
				}
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i8x16>)
			{
				return horizontal_max_fill_i8x16(std::forward<Register_>(a_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i8x32>)
			{
				return horizontal_max_fill_i8x32(std::forward<Register_>(a_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i8x64>)
			{
				return horizontal_max_fill_i8x64(std::forward<Register_>(a_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u8x16>)
			{
				return horizontal_max_fill_u8x16(std::forward<Register_>(a_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u8x32>)
			{
				return horizontal_max_fill_u8x32(std::forward<Register_>(a_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u8x64>)
			{
				return horizontal_max_fill_u8x64(std::forward<Register_>(a_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i16x8>)
			{
				return horizontal_max_fill_i16x8(std::forward<Register_>(a_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i16x16>)
			{
				return horizontal_max_fill_i16x16(std::forward<Register_>(a_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i16x32>)
			{
				return horizontal_max_fill_i16x32(std::forward<Register_>(a_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u16x8>)
			{
				return horizontal_max_fill_u16x8(std::forward<Register_>(a_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u16x16>)
			{
				return horizontal_max_fill_u16x16(std::forward<Register_>(a_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u16x32>)
			{
				return horizontal_max_fill_u16x32(std::forward<Register_>(a_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i32x4>)
			{
				return horizontal_max_fill_i32x4(std::forward<Register_>(a_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i32x8>)
			{
				return horizontal_max_fill_i32x8(std::forward<Register_>(a_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i32x16>)
			{
				return horizontal_max_fill_i32x16(std::forward<Register_>(a_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u32x4>)
			{
				return horizontal_max_fill_u32x4(std::forward<Register_>(a_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u32x8>)
			{
				return horizontal_max_fill_u32x8(std::forward<Register_>(a_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u32x16>)
			{
				return horizontal_max_fill_u32x16(std::forward<Register_>(a_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i64x2>)
			{
				return horizontal_max_fill_i64x2(std::forward<Register_>(a_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i64x4>)
			{
				return horizontal_max_fill_i64x4(std::forward<Register_>(a_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i64x8>)
			{
				return horizontal_max_fill_i64x8(std::forward<Register_>(a_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u64x2>)
			{
				return horizontal_max_fill_u64x2(std::forward<Register_>(a_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u64x4>)
			{
				return horizontal_max_fill_u64x4(std::forward<Register_>(a_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u64x8>)
			{
				return horizontal_max_fill_u64x8(std::forward<Register_>(a_));
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to find the maximum element in a SIMD register via EmuSIMD registers, but the passed Register_ type is not supported for this operation.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to find the maximum element in a SIMD register via EmuSIMD helpers, but the provided Register_ type is not recognised as a supported SIMD register.");
		}
	}

	template<typename OutScalar_, std::size_t PerElementWidthIfInt_, bool SignedIfInt_, EmuConcepts::KnownSIMD Register_>
	[[nodiscard]] inline auto _horizontal_max_scalar(Register_&& a_)
		-> typename std::remove_cvref<OutScalar_>::type
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			using namespace EmuSIMD::Funcs;
			if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x4>)
			{
				return horizontal_max_scalar_f32x4<typename std::remove_cvref<OutScalar_>::type>(std::forward<Register_>(a_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x8>)
			{
				return horizontal_max_scalar_f32x8<typename std::remove_cvref<OutScalar_>::type>(std::forward<Register_>(a_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x16>)
			{
				return horizontal_max_scalar_f32x16<typename std::remove_cvref<OutScalar_>::type>(std::forward<Register_>(a_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x2>)
			{
				return horizontal_max_scalar_f64x2<typename std::remove_cvref<OutScalar_>::type>(std::forward<Register_>(a_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x4>)
			{
				return horizontal_max_scalar_f64x4<typename std::remove_cvref<OutScalar_>::type>(std::forward<Register_>(a_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x8>)
			{
				return horizontal_max_scalar_f64x8<typename std::remove_cvref<OutScalar_>::type>(std::forward<Register_>(a_));
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
								return horizontal_max_scalar_i8x16<typename std::remove_cvref<OutScalar_>::type>(std::forward<Register_>(a_));
							}
							else
							{
								return horizontal_max_scalar_u8x16<typename std::remove_cvref<OutScalar_>::type>(std::forward<Register_>(a_));
							}
						}
						else if constexpr (PerElementWidthIfInt_ == 16)
						{
							if constexpr (SignedIfInt_)
							{
								return horizontal_max_scalar_i16x8<typename std::remove_cvref<OutScalar_>::type>(std::forward<Register_>(a_));
							}
							else
							{
								return horizontal_max_scalar_u16x8<typename std::remove_cvref<OutScalar_>::type>(std::forward<Register_>(a_));
							}
						}
						else if constexpr (PerElementWidthIfInt_ == 32)
						{
							if constexpr (SignedIfInt_)
							{
								return horizontal_max_scalar_i32x4<typename std::remove_cvref<OutScalar_>::type>(std::forward<Register_>(a_));
							}
							else
							{
								return horizontal_max_scalar_u32x4<typename std::remove_cvref<OutScalar_>::type>(std::forward<Register_>(a_));
							}
						}
						else
						{
							if constexpr (SignedIfInt_)
							{
								return horizontal_max_scalar_i64x2<typename std::remove_cvref<OutScalar_>::type>(std::forward<Register_>(a_));
							}
							else
							{
								return horizontal_max_scalar_u64x2<typename std::remove_cvref<OutScalar_>::type>(std::forward<Register_>(a_));
							}
						}
					}
					else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i256_generic>)
					{
						if constexpr (PerElementWidthIfInt_ == 8)
						{
							if constexpr (SignedIfInt_)
							{
								return horizontal_max_scalar_i8x32<typename std::remove_cvref<OutScalar_>::type>(std::forward<Register_>(a_));
							}
							else
							{
								return horizontal_max_scalar_u8x32<typename std::remove_cvref<OutScalar_>::type>(std::forward<Register_>(a_));
							}
						}
						else if constexpr (PerElementWidthIfInt_ == 16)
						{
							if constexpr (SignedIfInt_)
							{
								return horizontal_max_scalar_i16x16<typename std::remove_cvref<OutScalar_>::type>(std::forward<Register_>(a_));
							}
							else
							{
								return horizontal_max_scalar_u16x16<typename std::remove_cvref<OutScalar_>::type>(std::forward<Register_>(a_));
							}
						}
						else if constexpr (PerElementWidthIfInt_ == 32)
						{
							if constexpr (SignedIfInt_)
							{
								return horizontal_max_scalar_i32x8<typename std::remove_cvref<OutScalar_>::type>(std::forward<Register_>(a_));
							}
							else
							{
								return horizontal_max_scalar_u32x8<typename std::remove_cvref<OutScalar_>::type>(std::forward<Register_>(a_));
							}
						}
						else
						{
							if constexpr (SignedIfInt_)
							{
								return horizontal_max_scalar_i64x4<typename std::remove_cvref<OutScalar_>::type>(std::forward<Register_>(a_));
							}
							else
							{
								return horizontal_max_scalar_u64x4<typename std::remove_cvref<OutScalar_>::type>(std::forward<Register_>(a_));
							}
						}
					}
					else
					{
						if constexpr (PerElementWidthIfInt_ == 8)
						{
							if constexpr (SignedIfInt_)
							{
								return horizontal_max_scalar_i8x64<typename std::remove_cvref<OutScalar_>::type>(std::forward<Register_>(a_));
							}
							else
							{
								return horizontal_max_scalar_u8x64<typename std::remove_cvref<OutScalar_>::type>(std::forward<Register_>(a_));
							}
						}
						else if constexpr (PerElementWidthIfInt_ == 16)
						{
							if constexpr (SignedIfInt_)
							{
								return horizontal_max_scalar_i16x32<typename std::remove_cvref<OutScalar_>::type>(std::forward<Register_>(a_));
							}
							else
							{
								return horizontal_max_scalar_u16x32<typename std::remove_cvref<OutScalar_>::type>(std::forward<Register_>(a_));
							}
						}
						else if constexpr (PerElementWidthIfInt_ == 32)
						{
							if constexpr (SignedIfInt_)
							{
								return horizontal_max_scalar_i32x16<typename std::remove_cvref<OutScalar_>::type>(std::forward<Register_>(a_));
							}
							else
							{
								return horizontal_max_scalar_u32x16<typename std::remove_cvref<OutScalar_>::type>(std::forward<Register_>(a_));
							}
						}
						else
						{
							if constexpr (SignedIfInt_)
							{
								return horizontal_max_scalar_i64x8<typename std::remove_cvref<OutScalar_>::type>(std::forward<Register_>(a_));
							}
							else
							{
								return horizontal_max_scalar_u64x8<typename std::remove_cvref<OutScalar_>::type>(std::forward<Register_>(a_));
							}
						}
					}
				}
				else
				{
					static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to find the maximum element in a SIMD register via EmuSIMD helpers, but the provided PerElementWidth_ is invalid.");
				}
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i8x16>)
			{
				return horizontal_max_scalar_i8x16<typename std::remove_cvref<OutScalar_>::type>(std::forward<Register_>(a_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i8x32>)
			{
				return horizontal_max_scalar_i8x32<typename std::remove_cvref<OutScalar_>::type>(std::forward<Register_>(a_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i8x64>)
			{
				return horizontal_max_scalar_i8x64<typename std::remove_cvref<OutScalar_>::type>(std::forward<Register_>(a_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u8x16>)
			{
				return horizontal_max_scalar_u8x16<typename std::remove_cvref<OutScalar_>::type>(std::forward<Register_>(a_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u8x32>)
			{
				return horizontal_max_scalar_u8x32<typename std::remove_cvref<OutScalar_>::type>(std::forward<Register_>(a_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u8x64>)
			{
				return horizontal_max_scalar_u8x64<typename std::remove_cvref<OutScalar_>::type>(std::forward<Register_>(a_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i16x8>)
			{
				return horizontal_max_scalar_i16x8<typename std::remove_cvref<OutScalar_>::type>(std::forward<Register_>(a_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i16x16>)
			{
				return horizontal_max_scalar_i16x16<typename std::remove_cvref<OutScalar_>::type>(std::forward<Register_>(a_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i16x32>)
			{
				return horizontal_max_scalar_i16x32<typename std::remove_cvref<OutScalar_>::type>(std::forward<Register_>(a_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u16x8>)
			{
				return horizontal_max_scalar_u16x8<typename std::remove_cvref<OutScalar_>::type>(std::forward<Register_>(a_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u16x16>)
			{
				return horizontal_max_scalar_u16x16<typename std::remove_cvref<OutScalar_>::type>(std::forward<Register_>(a_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u16x32>)
			{
				return horizontal_max_scalar_u16x32<typename std::remove_cvref<OutScalar_>::type>(std::forward<Register_>(a_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i32x4>)
			{
				return horizontal_max_scalar_i32x4<typename std::remove_cvref<OutScalar_>::type>(std::forward<Register_>(a_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i32x8>)
			{
				return horizontal_max_scalar_i32x8<typename std::remove_cvref<OutScalar_>::type>(std::forward<Register_>(a_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i32x16>)
			{
				return horizontal_max_scalar_i32x16<typename std::remove_cvref<OutScalar_>::type>(std::forward<Register_>(a_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u32x4>)
			{
				return horizontal_max_scalar_u32x4<typename std::remove_cvref<OutScalar_>::type>(std::forward<Register_>(a_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u32x8>)
			{
				return horizontal_max_scalar_u32x8<typename std::remove_cvref<OutScalar_>::type>(std::forward<Register_>(a_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u32x16>)
			{
				return horizontal_max_scalar_u32x16<typename std::remove_cvref<OutScalar_>::type>(std::forward<Register_>(a_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i64x2>)
			{
				return horizontal_max_scalar_i64x2<typename std::remove_cvref<OutScalar_>::type>(std::forward<Register_>(a_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i64x4>)
			{
				return horizontal_max_scalar_i64x4<typename std::remove_cvref<OutScalar_>::type>(std::forward<Register_>(a_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i64x8>)
			{
				return horizontal_max_scalar_i64x8<typename std::remove_cvref<OutScalar_>::type>(std::forward<Register_>(a_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u64x2>)
			{
				return horizontal_max_scalar_u64x2<typename std::remove_cvref<OutScalar_>::type>(std::forward<Register_>(a_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u64x4>)
			{
				return horizontal_max_scalar_u64x4<typename std::remove_cvref<OutScalar_>::type>(std::forward<Register_>(a_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u64x8>)
			{
				return horizontal_max_scalar_u64x8<typename std::remove_cvref<OutScalar_>::type>(std::forward<Register_>(a_));
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to find the maximum element in a SIMD register via EmuSIMD registers, but the passed Register_ type is not supported for this operation.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to find the maximum element in a SIMD register via EmuSIMD helpers, but the provided Register_ type is not recognised as a supported SIMD register.");
		}
	}

	template<std::size_t PerElementWidthIfInt_, bool SignedIfInt_, EmuConcepts::KnownSIMD Register_>
	[[nodiscard]] inline auto _horizontal_min(Register_&& a_)
		-> typename std::remove_cvref<Register_>::type
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			using namespace EmuSIMD::Funcs;
			if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x4>)
			{
				return horizontal_min_f32x4(std::forward<Register_>(a_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x8>)
			{
				return horizontal_min_f32x8(std::forward<Register_>(a_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x16>)
			{
				return horizontal_min_f32x16(std::forward<Register_>(a_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x2>)
			{
				return horizontal_min_f64x2(std::forward<Register_>(a_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x4>)
			{
				return horizontal_min_f64x4(std::forward<Register_>(a_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x8>)
			{
				return horizontal_min_f64x8(std::forward<Register_>(a_));
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
								return horizontal_min_i8x16(std::forward<Register_>(a_));
							}
							else
							{
								return horizontal_min_u8x16(std::forward<Register_>(a_));
							}
						}
						else if constexpr (PerElementWidthIfInt_ == 16)
						{
							if constexpr (SignedIfInt_)
							{
								return horizontal_min_i16x8(std::forward<Register_>(a_));
							}
							else
							{
								return horizontal_min_u16x8(std::forward<Register_>(a_));
							}
						}
						else if constexpr (PerElementWidthIfInt_ == 32)
						{
							if constexpr (SignedIfInt_)
							{
								return horizontal_min_i32x4(std::forward<Register_>(a_));
							}
							else
							{
								return horizontal_min_u32x4(std::forward<Register_>(a_));
							}
						}
						else
						{
							if constexpr (SignedIfInt_)
							{
								return horizontal_min_i64x2(std::forward<Register_>(a_));
							}
							else
							{
								return horizontal_min_u64x2(std::forward<Register_>(a_));
							}
						}
					}
					else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i256_generic>)
					{
						if constexpr (PerElementWidthIfInt_ == 8)
						{
							if constexpr (SignedIfInt_)
							{
								return horizontal_min_i8x32(std::forward<Register_>(a_));
							}
							else
							{
								return horizontal_min_u8x32(std::forward<Register_>(a_));
							}
						}
						else if constexpr (PerElementWidthIfInt_ == 16)
						{
							if constexpr (SignedIfInt_)
							{
								return horizontal_min_i16x16(std::forward<Register_>(a_));
							}
							else
							{
								return horizontal_min_u16x16(std::forward<Register_>(a_));
							}
						}
						else if constexpr (PerElementWidthIfInt_ == 32)
						{
							if constexpr (SignedIfInt_)
							{
								return horizontal_min_i32x8(std::forward<Register_>(a_));
							}
							else
							{
								return horizontal_min_u32x8(std::forward<Register_>(a_));
							}
						}
						else
						{
							if constexpr (SignedIfInt_)
							{
								return horizontal_min_i64x4(std::forward<Register_>(a_));
							}
							else
							{
								return horizontal_min_u64x4(std::forward<Register_>(a_));
							}
						}
					}
					else
					{
						if constexpr (PerElementWidthIfInt_ == 8)
						{
							if constexpr (SignedIfInt_)
							{
								return horizontal_min_i8x64(std::forward<Register_>(a_));
							}
							else
							{
								return horizontal_min_u8x64(std::forward<Register_>(a_));
							}
						}
						else if constexpr (PerElementWidthIfInt_ == 16)
						{
							if constexpr (SignedIfInt_)
							{
								return horizontal_min_i16x32(std::forward<Register_>(a_));
							}
							else
							{
								return horizontal_min_u16x32(std::forward<Register_>(a_));
							}
						}
						else if constexpr (PerElementWidthIfInt_ == 32)
						{
							if constexpr (SignedIfInt_)
							{
								return horizontal_min_i32x16(std::forward<Register_>(a_));
							}
							else
							{
								return horizontal_min_u32x16(std::forward<Register_>(a_));
							}
						}
						else
						{
							if constexpr (SignedIfInt_)
							{
								return horizontal_min_i64x8(std::forward<Register_>(a_));
							}
							else
							{
								return horizontal_min_u64x8(std::forward<Register_>(a_));
							}
						}
					}
				}
				else
				{
					static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to find the minimum element in a SIMD register via EmuSIMD helpers, but the provided PerElementWidth_ is invalid.");
				}
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i8x16>)
			{
				return horizontal_min_i8x16(std::forward<Register_>(a_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i8x32>)
			{
				return horizontal_min_i8x32(std::forward<Register_>(a_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i8x64>)
			{
				return horizontal_min_i8x64(std::forward<Register_>(a_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u8x16>)
			{
				return horizontal_min_u8x16(std::forward<Register_>(a_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u8x32>)
			{
				return horizontal_min_u8x32(std::forward<Register_>(a_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u8x64>)
			{
				return horizontal_min_u8x64(std::forward<Register_>(a_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i16x8>)
			{
				return horizontal_min_i16x8(std::forward<Register_>(a_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i16x16>)
			{
				return horizontal_min_i16x16(std::forward<Register_>(a_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i16x32>)
			{
				return horizontal_min_i16x32(std::forward<Register_>(a_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u16x8>)
			{
				return horizontal_min_u16x8(std::forward<Register_>(a_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u16x16>)
			{
				return horizontal_min_u16x16(std::forward<Register_>(a_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u16x32>)
			{
				return horizontal_min_u16x32(std::forward<Register_>(a_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i32x4>)
			{
				return horizontal_min_i32x4(std::forward<Register_>(a_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i32x8>)
			{
				return horizontal_min_i32x8(std::forward<Register_>(a_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i32x16>)
			{
				return horizontal_min_i32x16(std::forward<Register_>(a_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u32x4>)
			{
				return horizontal_min_u32x4(std::forward<Register_>(a_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u32x8>)
			{
				return horizontal_min_u32x8(std::forward<Register_>(a_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u32x16>)
			{
				return horizontal_min_u32x16(std::forward<Register_>(a_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i64x2>)
			{
				return horizontal_min_i64x2(std::forward<Register_>(a_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i64x4>)
			{
				return horizontal_min_i64x4(std::forward<Register_>(a_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i64x8>)
			{
				return horizontal_min_i64x8(std::forward<Register_>(a_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u64x2>)
			{
				return horizontal_min_u64x2(std::forward<Register_>(a_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u64x4>)
			{
				return horizontal_min_u64x4(std::forward<Register_>(a_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u64x8>)
			{
				return horizontal_min_u64x8(std::forward<Register_>(a_));
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to find the minimum element in a SIMD register via EmuSIMD registers, but the passed Register_ type is not supported for this operation.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to find the minimum element in a SIMD register via EmuSIMD helpers, but the provided Register_ type is not recognised as a supported SIMD register.");
		}
	}

	template<std::size_t PerElementWidthIfInt_, bool SignedIfInt_, EmuConcepts::KnownSIMD Register_>
	[[nodiscard]] inline auto _horizontal_min_fill(Register_&& a_)
		-> typename std::remove_cvref<Register_>::type
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			using namespace EmuSIMD::Funcs;
			if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x4>)
			{
				return horizontal_min_fill_f32x4(std::forward<Register_>(a_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x8>)
			{
				return horizontal_min_fill_f32x8(std::forward<Register_>(a_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x16>)
			{
				return horizontal_min_fill_f32x16(std::forward<Register_>(a_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x2>)
			{
				return horizontal_min_fill_f64x2(std::forward<Register_>(a_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x4>)
			{
				return horizontal_min_fill_f64x4(std::forward<Register_>(a_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x8>)
			{
				return horizontal_min_fill_f64x8(std::forward<Register_>(a_));
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
								return horizontal_min_fill_i8x16(std::forward<Register_>(a_));
							}
							else
							{
								return horizontal_min_fill_u8x16(std::forward<Register_>(a_));
							}
						}
						else if constexpr (PerElementWidthIfInt_ == 16)
						{
							if constexpr (SignedIfInt_)
							{
								return horizontal_min_fill_i16x8(std::forward<Register_>(a_));
							}
							else
							{
								return horizontal_min_fill_u16x8(std::forward<Register_>(a_));
							}
						}
						else if constexpr (PerElementWidthIfInt_ == 32)
						{
							if constexpr (SignedIfInt_)
							{
								return horizontal_min_fill_i32x4(std::forward<Register_>(a_));
							}
							else
							{
								return horizontal_min_fill_u32x4(std::forward<Register_>(a_));
							}
						}
						else
						{
							if constexpr (SignedIfInt_)
							{
								return horizontal_min_fill_i64x2(std::forward<Register_>(a_));
							}
							else
							{
								return horizontal_min_fill_u64x2(std::forward<Register_>(a_));
							}
						}
					}
					else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i256_generic>)
					{
						if constexpr (PerElementWidthIfInt_ == 8)
						{
							if constexpr (SignedIfInt_)
							{
								return horizontal_min_fill_i8x32(std::forward<Register_>(a_));
							}
							else
							{
								return horizontal_min_fill_u8x32(std::forward<Register_>(a_));
							}
						}
						else if constexpr (PerElementWidthIfInt_ == 16)
						{
							if constexpr (SignedIfInt_)
							{
								return horizontal_min_fill_i16x16(std::forward<Register_>(a_));
							}
							else
							{
								return horizontal_min_fill_u16x16(std::forward<Register_>(a_));
							}
						}
						else if constexpr (PerElementWidthIfInt_ == 32)
						{
							if constexpr (SignedIfInt_)
							{
								return horizontal_min_fill_i32x8(std::forward<Register_>(a_));
							}
							else
							{
								return horizontal_min_fill_u32x8(std::forward<Register_>(a_));
							}
						}
						else
						{
							if constexpr (SignedIfInt_)
							{
								return horizontal_min_fill_i64x4(std::forward<Register_>(a_));
							}
							else
							{
								return horizontal_min_fill_u64x4(std::forward<Register_>(a_));
							}
						}
					}
					else
					{
						if constexpr (PerElementWidthIfInt_ == 8)
						{
							if constexpr (SignedIfInt_)
							{
								return horizontal_min_fill_i8x64(std::forward<Register_>(a_));
							}
							else
							{
								return horizontal_min_fill_u8x64(std::forward<Register_>(a_));
							}
						}
						else if constexpr (PerElementWidthIfInt_ == 16)
						{
							if constexpr (SignedIfInt_)
							{
								return horizontal_min_fill_i16x32(std::forward<Register_>(a_));
							}
							else
							{
								return horizontal_min_fill_u16x32(std::forward<Register_>(a_));
							}
						}
						else if constexpr (PerElementWidthIfInt_ == 32)
						{
							if constexpr (SignedIfInt_)
							{
								return horizontal_min_fill_i32x16(std::forward<Register_>(a_));
							}
							else
							{
								return horizontal_min_fill_u32x16(std::forward<Register_>(a_));
							}
						}
						else
						{
							if constexpr (SignedIfInt_)
							{
								return horizontal_min_fill_i64x8(std::forward<Register_>(a_));
							}
							else
							{
								return horizontal_min_fill_u64x8(std::forward<Register_>(a_));
							}
						}
					}
				}
				else
				{
					static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to find the minimum element in a SIMD register via EmuSIMD helpers, but the provided PerElementWidth_ is invalid.");
				}
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i8x16>)
			{
				return horizontal_min_fill_i8x16(std::forward<Register_>(a_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i8x32>)
			{
				return horizontal_min_fill_i8x32(std::forward<Register_>(a_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i8x64>)
			{
				return horizontal_min_fill_i8x64(std::forward<Register_>(a_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u8x16>)
			{
				return horizontal_min_fill_u8x16(std::forward<Register_>(a_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u8x32>)
			{
				return horizontal_min_fill_u8x32(std::forward<Register_>(a_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u8x64>)
			{
				return horizontal_min_fill_u8x64(std::forward<Register_>(a_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i16x8>)
			{
				return horizontal_min_fill_i16x8(std::forward<Register_>(a_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i16x16>)
			{
				return horizontal_min_fill_i16x16(std::forward<Register_>(a_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i16x32>)
			{
				return horizontal_min_fill_i16x32(std::forward<Register_>(a_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u16x8>)
			{
				return horizontal_min_fill_u16x8(std::forward<Register_>(a_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u16x16>)
			{
				return horizontal_min_fill_u16x16(std::forward<Register_>(a_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u16x32>)
			{
				return horizontal_min_fill_u16x32(std::forward<Register_>(a_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i32x4>)
			{
				return horizontal_min_fill_i32x4(std::forward<Register_>(a_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i32x8>)
			{
				return horizontal_min_fill_i32x8(std::forward<Register_>(a_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i32x16>)
			{
				return horizontal_min_fill_i32x16(std::forward<Register_>(a_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u32x4>)
			{
				return horizontal_min_fill_u32x4(std::forward<Register_>(a_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u32x8>)
			{
				return horizontal_min_fill_u32x8(std::forward<Register_>(a_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u32x16>)
			{
				return horizontal_min_fill_u32x16(std::forward<Register_>(a_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i64x2>)
			{
				return horizontal_min_fill_i64x2(std::forward<Register_>(a_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i64x4>)
			{
				return horizontal_min_fill_i64x4(std::forward<Register_>(a_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i64x8>)
			{
				return horizontal_min_fill_i64x8(std::forward<Register_>(a_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u64x2>)
			{
				return horizontal_min_fill_u64x2(std::forward<Register_>(a_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u64x4>)
			{
				return horizontal_min_fill_u64x4(std::forward<Register_>(a_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u64x8>)
			{
				return horizontal_min_fill_u64x8(std::forward<Register_>(a_));
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to find the minimum element in a SIMD register via EmuSIMD registers, but the passed Register_ type is not supported for this operation.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to find the minimum element in a SIMD register via EmuSIMD helpers, but the provided Register_ type is not recognised as a supported SIMD register.");
		}
	}

	template<typename OutScalar_, std::size_t PerElementWidthIfInt_, bool SignedIfInt_, EmuConcepts::KnownSIMD Register_>
	[[nodiscard]] inline auto _horizontal_min_scalar(Register_&& a_)
		-> typename std::remove_cvref<OutScalar_>::type
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			using namespace EmuSIMD::Funcs;
			if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x4>)
			{
				return horizontal_min_scalar_f32x4<typename std::remove_cvref<OutScalar_>::type>(std::forward<Register_>(a_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x8>)
			{
				return horizontal_min_scalar_f32x8<typename std::remove_cvref<OutScalar_>::type>(std::forward<Register_>(a_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f32x16>)
			{
				return horizontal_min_scalar_f32x16<typename std::remove_cvref<OutScalar_>::type>(std::forward<Register_>(a_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x2>)
			{
				return horizontal_min_scalar_f64x2<typename std::remove_cvref<OutScalar_>::type>(std::forward<Register_>(a_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x4>)
			{
				return horizontal_min_scalar_f64x4<typename std::remove_cvref<OutScalar_>::type>(std::forward<Register_>(a_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::f64x8>)
			{
				return horizontal_min_scalar_f64x8<typename std::remove_cvref<OutScalar_>::type>(std::forward<Register_>(a_));
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
								return horizontal_min_scalar_i8x16<typename std::remove_cvref<OutScalar_>::type>(std::forward<Register_>(a_));
							}
							else
							{
								return horizontal_min_scalar_u8x16<typename std::remove_cvref<OutScalar_>::type>(std::forward<Register_>(a_));
							}
						}
						else if constexpr (PerElementWidthIfInt_ == 16)
						{
							if constexpr (SignedIfInt_)
							{
								return horizontal_min_scalar_i16x8<typename std::remove_cvref<OutScalar_>::type>(std::forward<Register_>(a_));
							}
							else
							{
								return horizontal_min_scalar_u16x8<typename std::remove_cvref<OutScalar_>::type>(std::forward<Register_>(a_));
							}
						}
						else if constexpr (PerElementWidthIfInt_ == 32)
						{
							if constexpr (SignedIfInt_)
							{
								return horizontal_min_scalar_i32x4<typename std::remove_cvref<OutScalar_>::type>(std::forward<Register_>(a_));
							}
							else
							{
								return horizontal_min_scalar_u32x4<typename std::remove_cvref<OutScalar_>::type>(std::forward<Register_>(a_));
							}
						}
						else
						{
							if constexpr (SignedIfInt_)
							{
								return horizontal_min_scalar_i64x2<typename std::remove_cvref<OutScalar_>::type>(std::forward<Register_>(a_));
							}
							else
							{
								return horizontal_min_scalar_u64x2<typename std::remove_cvref<OutScalar_>::type>(std::forward<Register_>(a_));
							}
						}
					}
					else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i256_generic>)
					{
						if constexpr (PerElementWidthIfInt_ == 8)
						{
							if constexpr (SignedIfInt_)
							{
								return horizontal_min_scalar_i8x32<typename std::remove_cvref<OutScalar_>::type>(std::forward<Register_>(a_));
							}
							else
							{
								return horizontal_min_scalar_u8x32<typename std::remove_cvref<OutScalar_>::type>(std::forward<Register_>(a_));
							}
						}
						else if constexpr (PerElementWidthIfInt_ == 16)
						{
							if constexpr (SignedIfInt_)
							{
								return horizontal_min_scalar_i16x16<typename std::remove_cvref<OutScalar_>::type>(std::forward<Register_>(a_));
							}
							else
							{
								return horizontal_min_scalar_u16x16<typename std::remove_cvref<OutScalar_>::type>(std::forward<Register_>(a_));
							}
						}
						else if constexpr (PerElementWidthIfInt_ == 32)
						{
							if constexpr (SignedIfInt_)
							{
								return horizontal_min_scalar_i32x8<typename std::remove_cvref<OutScalar_>::type>(std::forward<Register_>(a_));
							}
							else
							{
								return horizontal_min_scalar_u32x8<typename std::remove_cvref<OutScalar_>::type>(std::forward<Register_>(a_));
							}
						}
						else
						{
							if constexpr (SignedIfInt_)
							{
								return horizontal_min_scalar_i64x4<typename std::remove_cvref<OutScalar_>::type>(std::forward<Register_>(a_));
							}
							else
							{
								return horizontal_min_scalar_u64x4<typename std::remove_cvref<OutScalar_>::type>(std::forward<Register_>(a_));
							}
						}
					}
					else
					{
						if constexpr (PerElementWidthIfInt_ == 8)
						{
							if constexpr (SignedIfInt_)
							{
								return horizontal_min_scalar_i8x64<typename std::remove_cvref<OutScalar_>::type>(std::forward<Register_>(a_));
							}
							else
							{
								return horizontal_min_scalar_u8x64<typename std::remove_cvref<OutScalar_>::type>(std::forward<Register_>(a_));
							}
						}
						else if constexpr (PerElementWidthIfInt_ == 16)
						{
							if constexpr (SignedIfInt_)
							{
								return horizontal_min_scalar_i16x32<typename std::remove_cvref<OutScalar_>::type>(std::forward<Register_>(a_));
							}
							else
							{
								return horizontal_min_scalar_u16x32<typename std::remove_cvref<OutScalar_>::type>(std::forward<Register_>(a_));
							}
						}
						else if constexpr (PerElementWidthIfInt_ == 32)
						{
							if constexpr (SignedIfInt_)
							{
								return horizontal_min_scalar_i32x16<typename std::remove_cvref<OutScalar_>::type>(std::forward<Register_>(a_));
							}
							else
							{
								return horizontal_min_scalar_u32x16<typename std::remove_cvref<OutScalar_>::type>(std::forward<Register_>(a_));
							}
						}
						else
						{
							if constexpr (SignedIfInt_)
							{
								return horizontal_min_scalar_i64x8<typename std::remove_cvref<OutScalar_>::type>(std::forward<Register_>(a_));
							}
							else
							{
								return horizontal_min_scalar_u64x8<typename std::remove_cvref<OutScalar_>::type>(std::forward<Register_>(a_));
							}
						}
					}
				}
				else
				{
					static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to find the minimum element in a SIMD register via EmuSIMD helpers, but the provided PerElementWidth_ is invalid.");
				}
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i8x16>)
			{
				return horizontal_min_scalar_i8x16<typename std::remove_cvref<OutScalar_>::type>(std::forward<Register_>(a_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i8x32>)
			{
				return horizontal_min_scalar_i8x32<typename std::remove_cvref<OutScalar_>::type>(std::forward<Register_>(a_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i8x64>)
			{
				return horizontal_min_scalar_i8x64<typename std::remove_cvref<OutScalar_>::type>(std::forward<Register_>(a_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u8x16>)
			{
				return horizontal_min_scalar_u8x16<typename std::remove_cvref<OutScalar_>::type>(std::forward<Register_>(a_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u8x32>)
			{
				return horizontal_min_scalar_u8x32<typename std::remove_cvref<OutScalar_>::type>(std::forward<Register_>(a_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u8x64>)
			{
				return horizontal_min_scalar_u8x64<typename std::remove_cvref<OutScalar_>::type>(std::forward<Register_>(a_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i16x8>)
			{
				return horizontal_min_scalar_i16x8<typename std::remove_cvref<OutScalar_>::type>(std::forward<Register_>(a_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i16x16>)
			{
				return horizontal_min_scalar_i16x16<typename std::remove_cvref<OutScalar_>::type>(std::forward<Register_>(a_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i16x32>)
			{
				return horizontal_min_scalar_i16x32<typename std::remove_cvref<OutScalar_>::type>(std::forward<Register_>(a_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u16x8>)
			{
				return horizontal_min_scalar_u16x8<typename std::remove_cvref<OutScalar_>::type>(std::forward<Register_>(a_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u16x16>)
			{
				return horizontal_min_scalar_u16x16<typename std::remove_cvref<OutScalar_>::type>(std::forward<Register_>(a_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u16x32>)
			{
				return horizontal_min_scalar_u16x32<typename std::remove_cvref<OutScalar_>::type>(std::forward<Register_>(a_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i32x4>)
			{
				return horizontal_min_scalar_i32x4<typename std::remove_cvref<OutScalar_>::type>(std::forward<Register_>(a_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i32x8>)
			{
				return horizontal_min_scalar_i32x8<typename std::remove_cvref<OutScalar_>::type>(std::forward<Register_>(a_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i32x16>)
			{
				return horizontal_min_scalar_i32x16<typename std::remove_cvref<OutScalar_>::type>(std::forward<Register_>(a_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u32x4>)
			{
				return horizontal_min_scalar_u32x4<typename std::remove_cvref<OutScalar_>::type>(std::forward<Register_>(a_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u32x8>)
			{
				return horizontal_min_scalar_u32x8<typename std::remove_cvref<OutScalar_>::type>(std::forward<Register_>(a_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u32x16>)
			{
				return horizontal_min_scalar_u32x16<typename std::remove_cvref<OutScalar_>::type>(std::forward<Register_>(a_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i64x2>)
			{
				return horizontal_min_scalar_i64x2<typename std::remove_cvref<OutScalar_>::type>(std::forward<Register_>(a_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i64x4>)
			{
				return horizontal_min_scalar_i64x4<typename std::remove_cvref<OutScalar_>::type>(std::forward<Register_>(a_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::i64x8>)
			{
				return horizontal_min_scalar_i64x8<typename std::remove_cvref<OutScalar_>::type>(std::forward<Register_>(a_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u64x2>)
			{
				return horizontal_min_scalar_u64x2<typename std::remove_cvref<OutScalar_>::type>(std::forward<Register_>(a_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u64x4>)
			{
				return horizontal_min_scalar_u64x4<typename std::remove_cvref<OutScalar_>::type>(std::forward<Register_>(a_));
			}
			else if constexpr (std::is_same_v<register_type_uq, EmuSIMD::u64x8>)
			{
				return horizontal_min_scalar_u64x8<typename std::remove_cvref<OutScalar_>::type>(std::forward<Register_>(a_));
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to find the minimum element in a SIMD register via EmuSIMD registers, but the passed Register_ type is not supported for this operation.");
			}
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to find the minimum element in a SIMD register via EmuSIMD helpers, but the provided Register_ type is not recognised as a supported SIMD register.");
		}
	}

	template<std::size_t PerElementWidthIfInt_, bool SignedIfInt_, class Register_>
	[[nodiscard]] inline Register_ _clamp(Register_ register_, Register_ min_, Register_ max_)
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			return _min<PerElementWidthIfInt_, SignedIfInt_>
			(
				_max<PerElementWidthIfInt_, SignedIfInt_>(register_, min_),
				max_
			);
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Register_>(), "Attempted to clamp the values in a SIMD register to an inclusive min:max range, but the provided Register_ type is not recognised as a supported SIMD register.");
		}
	}
#pragma endregion
}

#endif
