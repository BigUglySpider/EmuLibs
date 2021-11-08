#ifndef EMU_THREADS_THREAD_POOL_H_INC_
#define EMU_THREADS_THREAD_POOL_H_INC_ 1

#include <functional>
#include <queue>
#include <thread>
#include "Functors/default_work_allocator.h"

namespace EmuThreads
{
	template
	<
		class ThreadType_ = std::thread,
		class WorkAllocator_= EmuThreads::Functors::default_work_allocator
	>
	class ThreadPool
	{
	public:
		using thread_type = ThreadType_;
		using work_allocator_type = WorkAllocator_;
		using this_type = ThreadPool<thread_type, work_allocator_type>;

		/// <summary> The lowest number of threads that may be allocated to a thread pool of this type. </summary>
		static constexpr std::size_t min_num_threads = 0;
		/// <summary> The largest number of threads that may be allocated to a thread pool of this type. </summary>
		static constexpr std::size_t max_num_threads = std::numeric_limits<std::size_t>::max();

		[[nodiscard]] static constexpr inline std::size_t validate_num_threads(std::size_t num_to_validate_)
		{
			return (num_to_validate_ <= min_num_threads) ? min_num_threads : (num_to_validate_ >= max_num_threads) ? max_num_threads : num_to_validate_;
		}

		/// <summary>
		/// <para> Default constructs a thread pool with no threads allocated. Threads will need to be allocated at a later point. </para>
		/// </summary>
		ThreadPool() :
			num_threads(0),
			worker_threads(),
			work_allocator()
		{
		}
		/// <summary> Constructs a thread pool with the specified number of threads to perform allocated tasks, clamped into a valid range. </summary>
		/// <param name="num_threads_">Number of threads to attempt to allocate. Will be clamped to the inclusive range min_num_threads:max_num_threads.</param>
		inline ThreadPool(std::size_t num_threads_) : ThreadPool()
		{
			AllocateWorkers(num_threads_);
		}
		/// <summary>
		/// <para> Constructs a thread pool from the provided pool, transferring data to the newly formed pool. </para>
		/// <para> Queued work will be transferred to the new pool, but new threads will have to be allocated for it. </para>
		/// </summary>
		/// <param name="to_move_">Thread pool to move for constructing this new pool.</param>
		/// <param name="num_threads_">Custom number of threads to allocate to this pool. Will be clamped to the inclusive range min_num_threads:max_num_threads.</param>
		inline ThreadPool(this_type&& to_move_, std::size_t num_threads_) noexcept :
			num_threads(0),
			worker_threads(),
			work_allocator(std::move(to_move_.work_allocator))
		{
			AllocateWorkers(num_threads_);
		}
		/// <summary>
		/// <para> Constructs a thread pool from the provided pool, transferring data to the newly formed pool. </para>
		/// <para> Queued work will be transferred to the new pool, but new threads will have to be allocated for it. </para>
		/// <para> The provided thread pool to_move_ will have all of its threads deallocated. </para>
		/// <para> The number of threads allocated to this pool will be the same as the number of threads allocated to the pool being moved. </para>
		/// </summary>
		/// <param name="to_move_">Thread pool to move for constructing this new pool.</param>
		inline ThreadPool(this_type&& to_move_) noexcept : ThreadPool(std::forward<this_type>(to_move_), to_move_.num_threads)
		{
			AllocateWorkers(to_move_.num_threads);
			to_move_.DeallocateThreads();
		}

		~ThreadPool()
		{
			work_allocator.Deactivate();
			_join_threads();
		}

		/// <summary>
		/// <para> Allocates the provided target number of threads to this pool, clamped into the inclusive range min_num_threads:max_num_threads. </para>
		/// <para> If target_num_threads_ is larger than the existing number of threads, the new threads will be allocated as work continues. </para>
		/// <para> If target_num_threads_ is lower than the existing number of threads, task execution will be paused to safely deallocate threads. </para>
		/// </summary>
		/// <param name="target_num_threads_">Target number of threads to allocate to this pool. Will be clamped into inclusive range min_num_threads:max_num_threads.</param>
		inline void AllocateWorkers(std::size_t target_num_threads_)
		{
			target_num_threads_ = validate_num_threads(target_num_threads_);

			// No need to do anything if the validated count == current count
			if (target_num_threads_ != num_threads)
			{
				if (target_num_threads_ < num_threads)
				{
					DeallocateThreads();
				}
				_allocate_threads(target_num_threads_);
			}
		}

		/// <summary>
		/// <para> Deallocates all  </para>
		/// </summary>
		inline void DeallocateThreads()
		{
			// Deactivates work allocator to prevent new tasks from being allocated, removes threads when safe, then reactivates work allocator
			work_allocator.Deactivate();
			_join_threads();
			_clear_threads();
			work_allocator.Activate();
		}

		/// <summary>
		/// <para> Performs allocation of any valid generic task to be performed by one of this pool's worker threads. </para>
		/// <para> The provided args_ must be valid arguments to invoke the provided func_ via the syntax `func_(args_...)`. </para>
		/// <para> A future to the task's results is also returned by this allocation. </para>
		/// <para> If non-value arguments are being provided, it is highly recommended to explicitly type provided Args_ template types. </para>
		/// </summary>
		/// <typeparam name="Args_">All argument types to pass in the provided order when invoking the provided func_.</typeparam>
		/// <typeparam name="Func_">Type of invocable to be called.</typeparam>
		/// <param name="func_">Invocable item (such as a functor or function pointer) to be invoked.</param>
		/// <param name="args_">Arguments to pass when invoking the provided func_.</param>
		/// <returns>
		///		Future to the provided task, allowing retrieval of results at a later point. 
		///		Note that this future indicating completion does not necessarily guarantee that other allocated tasks - before or after - have been completed.
		/// </returns>
		template<class...Args_, class Func_, typename RequiresValidArgs_ = std::enable_if_t<std::is_invocable_v<Func_, Args_...>>>
		inline auto AllocateTask(Func_ func_, Args_...args_)
		{
			return work_allocator.AllocateTask(std::bind(func_, _get_suitable_arg<Args_>(args_)...));
		}

	private:
		using worker_thread_collection = std::vector<thread_type>;

		template<class Arg_>
		[[nodiscard]] inline std::conditional_t<std::is_reference_v<Arg_>, std::reference_wrapper<std::remove_reference_t<Arg_>>, Arg_&> _get_suitable_arg(Arg_& arg_)
		{
			if constexpr (std::is_reference_v<Arg_>)
			{
				return std::ref(arg_);
			}
			else
			{
				return arg_;
			}
		}

		std::size_t num_threads;
		worker_thread_collection worker_threads;
		work_allocator_type work_allocator;

		inline void _join_threads()
		{
			for (auto& thread_ : worker_threads)
			{
				thread_.join();
			}
		}

		inline void _clear_threads()
		{
			num_threads = 0;
			worker_thread_collection().swap(worker_threads);
		}

		inline void _allocate_threads(std::size_t target_num_threads_validated_)
		{
			work_allocator.Activate();

			worker_threads.reserve(target_num_threads_validated_);
			for (std::size_t i = num_threads; i < target_num_threads_validated_; ++i)
			{
				worker_threads.emplace_back(work_allocator.LaunchThread<thread_type>());
				++num_threads; // Increment one at a time so previous allocations are accounted for if an exception is thrown
			}
		}
	};
}

#endif
