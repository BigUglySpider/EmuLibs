#ifndef EMU_MATH_FAST_QUATERNION_UNDERLYING_QUATERNION_GET_H_INC_
#define EMU_MATH_FAST_QUATERNION_UNDERLYING_QUATERNION_GET_H_INC_ 1

#include "_fast_quaternion_tmp.h"

namespace EmuMath::Helpers::_fast_quaternion_underlying
{
	template<std::size_t RegisterIndex_, class Arg_>
	[[nodiscard]] constexpr inline decltype(auto) _fast_quaternion_get_register_arg_for_index(Arg_&& arg_)
	{
		using _arg_uq = typename std::remove_cvref<Arg_>::type;
		if constexpr (EmuConcepts::EmuFastQuaternion<_arg_uq> || EmuConcepts::EmuFastVector<_arg_uq>)
		{
			if constexpr (RegisterIndex_ < _arg_uq::num_registers)
			{
				return arg_.template GetRegister<RegisterIndex_>();
			}
			else
			{
				return EmuSIMD::setzero<typename _arg_uq::register_type>();
			}
		}
		else if constexpr (EmuConcepts::KnownSIMD<_arg_uq>)
		{
			return std::forward<Arg_>(arg_);
		}
		else
		{
			static_assert(EmuCore::TMP::get_false<Arg_>(), "INTERNAL EMUMATH ERROR: Could not select a FastQuaternion register argument for a specified index as the input Arg_ type is not a FastQuaternion, FastVector, or EmuSIMD-recognised register.");
		}
	}
}

#endif
