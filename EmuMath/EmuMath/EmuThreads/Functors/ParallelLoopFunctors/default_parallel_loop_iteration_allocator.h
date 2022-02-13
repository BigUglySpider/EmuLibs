#ifndef EMU_THREADS_DEFAULT_PARALLEL_LOOP_ITERATION_ALLOCATOR_H_INC_
#define EMU_THREADS_DEFAULT_PARALLEL_LOOP_ITERATION_ALLOCATOR_H_INC_ 1

#include "../../../EmuCore/TMPHelpers/Values.h"

namespace EmuThreads::Functors
{
	template<class Executor_>
	struct default_parallel_loop_iteration_allocator
	{
		template<class Func_, class...Iterators_>
		inline void operator()(Executor_& executor_, Func_& func_, const std::tuple<Iterators_...>& iterators_) const
		{
			if constexpr (std::is_copy_constructible_v<Func_>)
			{
				if constexpr (std::is_invocable_v<Func_, std::tuple<Iterators_...>>)
				{
					executor_.AllocateTask(func_, iterators_);
				}
				else if constexpr (sizeof...(Iterators_) == 1)
				{
					if constexpr (std::is_invocable_v<Func_, std::tuple_element_t<0, std::tuple<Iterators_...>>>)
					{
						using std::get;
						executor_.AllocateTask(func_, get<0>(iterators_));
					}
					else
					{
						static_assert(EmuCore::TMP::get_false<Executor_>(), "Attempted to allocate a parallel loop iteration via default_parallel_loop_iteration_allocator, but the provided Func_ cannot be invoked with a tuple of the provided iterators, and the single iterator in the tuple cannot be used as a lone argument in the fallback operation.");
					}
				}
				else
				{
					static_assert(EmuCore::TMP::get_false<Executor_>(), "Attempted to allocate a parallel loop iteration via default_parallel_loop_iteration_allocator, but the provided Func_ cannot be invoked with a tuple of the provided iterators.");
				}
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<Executor_>(), "Attempted to allocate a parallel loop iteration via default_parallel_loop_iteration_allocator, but the provided Func_ cannot be copy constructed. As this can cause undesirable behaviours with task allocation, this behaviour has been blocked.");
			}
		}

		template<class Func_, class Iterator_, typename = std::enable_if_t<!EmuCore::TMP::is_tuple_v<Iterator_>>>
		inline void operator()(Executor_& executor_, Func_& func_, const Iterator_& iterator_) const
		{
			if constexpr (std::is_copy_constructible_v<Func_>)
			{
				if constexpr (std::is_invocable_v<Func_, Iterator_>)
				{
					executor_.AllocateTask(func_, iterator_);
				}
				else
				{
					static_assert(EmuCore::TMP::get_false<Func_>(), "Attempted to allocate a parallel loop iteration via default_parallel_loop_iteration_allocator, but the provided Func_ cannot be invoked with the provided single non-tuple Iterator_ argument type.");
				}
			}
			else
			{
				static_assert(EmuCore::TMP::get_false<Func_>(), "Attempted to allocate a parallel loop iteration via default_parallel_loop_iteration_allocator, but the provided Func_ cannot be copy constructed. As this can cause undesirable behaviours with task allocation, this behaviour has been blocked.");
			}
		}
	};
}

#endif
