#ifndef EMU_THREADS_DEFAULT_PARALLEL_LOOP_CUSTOM_INCREMENTER_H_INC_
#define EMU_THREADS_DEFAULT_PARALLEL_LOOP_CUSTOM_INCREMENTER_H_INC_ 1

namespace EmuThreads::Functors
{
	template<class Increment_>
	struct default_parallel_loop_custom_incrementer
	{
		using this_type = default_parallel_loop_custom_incrementer<Increment_>;

		constexpr default_parallel_loop_custom_incrementer(const this_type& to_copy_) : increment(to_copy_.increment)
		{
		}
		
		template<typename = std::enable_if_t<std::is_move_constructible_v<Increment_>>>
		constexpr default_parallel_loop_custom_incrementer(this_type&& to_move_) : increment(to_move_.increment)
		{
		}

		template<class...IncrementConstructionArgs_, typename = std::enable_if_t<std::is_constructible_v<Increment_, IncrementConstructionArgs_...>>>
		constexpr default_parallel_loop_custom_incrementer(IncrementConstructionArgs_&&...increment_construction_args_) :
			increment(increment_construction_args_...)
		{
		}

		template<class T_>
		constexpr inline void operator()(T_& iterator_) const
		{
			iterator_ += increment;
		}

		const Increment_ increment;
	};
}

#endif