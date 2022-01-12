#ifndef EMU_SIMD_HELPERS_TEMPLATE_BITWISE_H_INC_
#define EMU_SIMD_HELPERS_TEMPLATE_BITWISE_H_INC_ 1

#include "_underlying_template_helpers/_common_underlying_simd_template_helper_includes.h"
#include "_underlying_template_helpers/_simd_helpers_underlying_bitwise.h"

namespace EmuSIMD
{
	template<class Register_>
	[[nodiscard]] inline Register_ bitwise_and(Register_ lhs_, Register_ rhs_)
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			return _underlying_simd_helpers::_and(lhs_, rhs_);
		}
		else
		{
			static_assert(false, "Attempted to use EmuSIMD::bitwise_and with a non-SIMD register type, or a SIMD register that is not supported.");
		}
	}

	template<class Register_>
	[[nodiscard]] inline Register_ bitwise_or(Register_ lhs_, Register_ rhs_)
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			return _underlying_simd_helpers::_or(lhs_, rhs_);
		}
		else
		{
			static_assert(false, "Attempted to use EmuSIMD::bitwise_or with a non-SIMD register type, or a SIMD register that is not supported.");
		}
	}

	template<class Register_>
	[[nodiscard]] inline Register_ bitwise_xor(Register_ lhs_, Register_ rhs_)
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			return _underlying_simd_helpers::_xor(lhs_, rhs_);
		}
		else
		{
			static_assert(false, "Attempted to use EmuSIMD::bitwise_xor with a non-SIMD register type, or a SIMD register that is not supported.");
		}
	}

	template<class Register_>
	[[nodiscard]] inline Register_ bitwise_andnot(Register_ lhs_, Register_ rhs_)
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			return _underlying_simd_helpers::_andnot(lhs_, rhs_);
		}
		else
		{
			static_assert(false, "Attempted to use EmuSIMD::bitwise_andnot with a non-SIMD register type, or a SIMD register that is not supported.");
		}
	}

	template<class Register_>
	[[nodiscard]] inline Register_ bitwise_not(Register_ lhs_)
	{
		using register_type_uq = typename EmuCore::TMP::remove_ref_cv<Register_>::type;
		if constexpr (EmuSIMD::TMP::is_simd_register_v<register_type_uq>)
		{
			return _underlying_simd_helpers::_not(lhs_);
		}
		else
		{
			static_assert(false, "Attempted to use EmuSIMD::bitwise_andnot with a non-SIMD register type, or a SIMD register that is not supported.");
		}
	}
}

#endif
