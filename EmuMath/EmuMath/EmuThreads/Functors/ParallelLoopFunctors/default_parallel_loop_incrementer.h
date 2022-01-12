#ifndef EMU_THREADS_DEFAULT_PARALLEL_LOOP_INCREMENTER_H_INC_
#define EMU_THREADS_DEFAULT_PARALLEL_LOOP_INCREMENTER_H_INC_ 1

#include <type_traits>

namespace EmuThreads::Functors
{
	struct default_parallel_loop_incrementer
	{
		constexpr default_parallel_loop_incrementer()
		{
		}

		template<class T_, typename = std::enable_if_t<!std::is_const_v<T_>>>
		constexpr inline void operator()(T_& iterator_) const
		{
			++iterator_;
		}
	};
}

#endif
