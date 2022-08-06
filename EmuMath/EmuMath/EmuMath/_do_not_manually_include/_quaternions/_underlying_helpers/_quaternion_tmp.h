#ifndef EMU_MATH_QUATERNION_TMP_H_INC_
#define EMU_MATH_QUATERNION_TMP_H_INC_ 1

#include "../../../Vector.h"

namespace EmuMath
{
	template<typename T_>
	struct Quaternion;
}

namespace EmuMath::TMP
{
	template<typename T_>
	struct is_emu_quaternion
	{
	private:
		using _t_uq = typename EmuCore::TMP::remove_ref_cv<T_>::type;

	public:
		static constexpr bool value = std::conditional_t
		<
			std::is_same_v<T_, _t_uq>,
			std::false_type,
			EmuMath::TMP::is_emu_quaternion<_t_uq>
		>::value;
	};

	template<typename T_>
	struct is_emu_quaternion<EmuMath::Quaternion<T_>>
	{
		static constexpr bool value = true;
	};

	template<typename T_>
	static constexpr bool is_emu_quaternion_v = is_emu_quaternion<T_>::value;
}

#endif
