#ifndef EMU_SIMD_COMMON_GENERIC_FUNC_HELPERS_H_INC_
#define EMU_SIMD_COMMON_GENERIC_FUNC_HELPERS_H_INC_ 1

#include "../_simd_helpers_underlying_aliases.h"
#include "../../../../../../EmuCore/ArithmeticHelpers/CommonMath.h"
#include "../../../../../../EmuCore/CommonPreprocessor/All.h"

#include <cstdint>
#include <immintrin.h>

/// <summary>
/// <para> Specifiers used by most - if not all - common functions defined within the EmuSIMD::Funcs namespace. </para>
/// </summary>
#define EMU_SIMD_COMMON_FUNC_SPEC inline

#define EMU_SIMD_CMP_EQ_FLAG _CMP_EQ_OS
#define EMU_SIMD_CMP_NEQ_FLAG _CMP_NEQ_OS
#define EMU_SIMD_CMP_GT_FLAG _CMP_GT_OS
#define EMU_SIMD_CMP_LT_FLAG _CMP_LT_OS
#define EMU_SIMD_CMP_GE_FLAG _CMP_GE_OS
#define EMU_SIMD_CMP_LE_FLAG _CMP_LE_OS

namespace EmuSIMD::Funcs
{
	using shuffle_mask_type = unsigned int;

	template<shuffle_mask_type I0_, shuffle_mask_type I1_, shuffle_mask_type I2_, shuffle_mask_type I3_>
	[[nodiscard]] constexpr inline shuffle_mask_type make_shuffle_mask()
	{
		return ((I3_ << 6) | (I2_ << 4) | (I1_ << 2) | (I0_));
	}
}

#endif
