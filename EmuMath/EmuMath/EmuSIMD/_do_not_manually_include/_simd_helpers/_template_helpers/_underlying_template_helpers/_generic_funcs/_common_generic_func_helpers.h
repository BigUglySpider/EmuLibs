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

// Flag used to identify a cmpeq comparison (==)
#define EMU_SIMD_CMP_EQ_FLAG _CMP_EQ_OS
// Flag used to identify a cmpneq comparison (!=)
#define EMU_SIMD_CMP_NEQ_FLAG _CMP_NEQ_OS
// Flag used to identify a cmpgt comparison (>)
#define EMU_SIMD_CMP_GT_FLAG _CMP_GT_OS
// Flag used to identify a cmplt comparison (<)
#define EMU_SIMD_CMP_LT_FLAG _CMP_LT_OS
// Flag used to identify a cmpge comparison (>=)
#define EMU_SIMD_CMP_GE_FLAG _CMP_GE_OS
// Flag used to identify a cmple comparison (<-)
#define EMU_SIMD_CMP_LE_FLAG _CMP_LE_OS

// Flag used to identify a floor round (toward negative infinity)
#define EMU_SIMD_FLAG_FLOOR	_MM_FROUND_FLOOR
// Flag used to identify a ceil round (toward positive infinity)
#define EMU_SIMD_FLAG_CEIL	_MM_FROUND_CEIL
// Flag used to identify a trunc round (toward 0)
#define EMU_SIMD_FLAG_TRUNC	_MM_FROUND_TRUNC

namespace EmuSIMD::Funcs
{
	/// <summary>
	/// <para> Type used as a template argument for basic shuffle masks with EmuSIMD's underlying functions. </para>
	/// </summary>
	using shuffle_mask_type = unsigned int;

	/// <summary>
	/// <para> Creates a shuffle mask for a 64-bit-element SIMD register with the same semantics as the x86/x64 _MM_SHUFFLE2 macro. </para>
	/// </summary>
	/// <returns>Shuffle mask that would result from a call to _MM_SHUFFLE(I0_, I1_) when building under x86/x64.</returns>
	template<shuffle_mask_type I0_, shuffle_mask_type I1_>
	[[nodiscard]] constexpr inline shuffle_mask_type make_shuffle_mask()
	{
		return ((I0_ << 1) | I1_);
	}

	/// <summary>
	/// <para> Creates a shuffle mask for a 32-bit-element SIMD register with the same semantics as the x86/x64 _MM_SHUFFLE macro. </para>
	/// </summary>
	/// <returns>Shuffle mask that would result from a call to _MM_SHUFFLE(I0_, I1_, I2_, I3_) when building under x86/x64.</returns>
	template<shuffle_mask_type I0_, shuffle_mask_type I1_, shuffle_mask_type I2_, shuffle_mask_type I3_>
	[[nodiscard]] constexpr inline shuffle_mask_type make_shuffle_mask()
	{
		return ((I3_ << 6) | (I2_ << 4) | (I1_ << 2) | (I0_));
	}
}

#endif
