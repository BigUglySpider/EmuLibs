#ifndef EMU_CORE_TMP_DESCRIPTIVE_ENABLE_IF_H_INC_
#define EMU_CORE_TMP_DESCRIPTIVE_ENABLE_IF_H_INC_ 1

#include <functional>
#include <type_traits>

namespace EmuCore::TMP
{
	template<std::size_t Count_>
	struct min_arg_count {};

	template<std::size_t Count_>
	struct max_arg_count {};

	template<std::size_t Min_, std::size_t Max_>
	struct min_max_arg_count {};

	template<std::size_t Min_, class...T_>
	using enable_if_min_typeargs_t = std::enable_if_t<(sizeof...(T_) >= Min_), min_arg_count<Min_>>;

	template<std::size_t Max_, class...T_>
	using enable_if_max_typeargs_t = std::enable_if_t<(sizeof...(T_) <= Max_), max_arg_count<Max_>>;

	template<std::size_t Min_, std::size_t Max_, class...T_>
	using enable_if_min_max_typeargs_t = std::enable_if_t<(sizeof...(T_) >= Min_ &&sizeof...(T_) <= Max_), min_max_arg_count<Min_, Max_>>;

	template<std::size_t Min_, auto...Vals_>
	using enable_if_min_val_args_t = std::enable_if_t<(sizeof...(Vals_) >= Min_), min_arg_count<Min_>>;

	template<std::size_t Max_, auto...Vals_>
	using enable_if_max_val_args_t = std::enable_if_t<(sizeof...(Vals_) <= Max_), max_arg_count<Max_>>;

	template<std::size_t Min_, std::size_t Max_, auto...Vals_>
	using enable_if_min_max_val_args_t = std::enable_if_t<(sizeof...(Vals_) >= Min_ && sizeof...(Vals_) <= Max_), min_max_arg_count<Min_, Max_>>;
}

#endif
