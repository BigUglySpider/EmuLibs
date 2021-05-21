#ifndef EMU_CORE_ARITHMETIC_HELPERS_COMMON_VALUES_H_INC_
#define EMU_CORE_ARITHMETIC_HELPERS_COMMON_VALUES_H_INC_

namespace EmuCore::ArithmeticHelpers
{
	/// <summary> Value of T when constructed with 0. </summary>
	template<typename T>
	static constexpr T ZeroT = T(0);

	/// <summary> Value of T when constructed with 1. </summary>
	template<typename T>
	static constexpr T OneT = T(1);

	/// <summary> Value of T when constructed with the passed value. </summary>
	template<typename T, typename ValType, ValType Val_>
	static constexpr T ValT = T(Val_);
}

#endif
