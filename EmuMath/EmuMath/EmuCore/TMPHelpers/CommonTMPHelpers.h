#ifndef EMU_CORE_COMMON_TMP_HELPERS_H_INC_
#define EMU_CORE_COMMON_TMP_HELPERS_H_INC_ 1

#include <type_traits>

namespace EmuCore::TMP
{
	/// <summary>
	/// <para> Error type provided by Emu library TMP functions when a type cannot be successfully deduced. </para>
	/// </summary>
	using emu_tmp_err = std::false_type;

	template<typename T_>
	struct is_emu_tmp_err
	{
		static constexpr bool value = std::is_same_v<emu_tmp_err, typename std::remove_cvref<T_>::type>;
	};
}

#endif
