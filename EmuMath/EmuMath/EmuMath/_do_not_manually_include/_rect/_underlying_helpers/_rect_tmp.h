#ifndef EMU_MATH_RECT_TMP_H_IN_
#define EMU_MATH_RECT_TMP_H_IN_ 1

#include "../../../Vector.h"

namespace EmuMath
{
	template<typename T_>
	struct Rect;
}

namespace EmuMath::TMP
{
	template<typename T_>
	struct is_emu_rect
	{
	private:
		using _t_uq = typename EmuCore::TMP::remove_ref_cv<T_>::type;

	public:
		static constexpr bool value = std::conditional_t
		<
			std::is_same_v<T_, _t_uq>,
			std::false_type,
			is_emu_rect<_t_uq>
		>::value;
	};

	template<typename T_>
	struct is_emu_rect<Rect<T_>>
	{
		static constexpr bool value = true;
	};

	template<typename T_>
	static constexpr bool is_emu_rect_v = is_emu_rect<T_>::value;

	template<typename T_>
	concept EmuRect = is_emu_rect_v<T_>;
}

#endif
