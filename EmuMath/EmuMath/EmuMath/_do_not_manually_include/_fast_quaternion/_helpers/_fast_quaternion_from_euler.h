#ifndef EMU_MATH_FAST_QUATERNION_FROM_EULER_H_INC_
#define EMU_MATH_FAST_QUATERNION_FROM_EULER_H_INC_ 1

#include "_common_fast_quaternion_includes.h"

namespace EmuMath::Helpers
{
	template
	<
		EmuConcepts::EmuFastQuaternion OutQuaternion_, bool InRads_ = true, bool Normalise_ = true,
		EmuConcepts::Arithmetic X_, EmuConcepts::Arithmetic Y_, EmuConcepts::Arithmetic Z_
	>
	[[nodiscard]] constexpr inline auto fast_quaternion_from_euler(X_&& euler_x_, Y_&& euler_y_, Z_&& euler_z_)
		-> typename EmuCore::TMP::remove_ref_cv<OutQuaternion_>::type
	{
		return _fast_quaternion_underlying::_make_fast_quat_from_euler<OutQuaternion_, InRads_, Normalise_>
		(
			_fast_quaternion_underlying::_make_euler_registers<OutQuaternion_>
			(
				std::forward<X_>(euler_x_),
				std::forward<Y_>(euler_y_),
				std::forward<Z_>(euler_z_)
			)
		);
	}
}

#endif
