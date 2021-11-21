#ifndef EMU_THREADS_THREAD_POOL_H_INC_
#define EMU_THREADS_THREAD_POOL_H_INC_ 1

#include <functional>
#include <queue>
#include <thread>
#include "Functors/default_thread_allocator.h"
#include "Functors/default_work_allocator.h"
#include "Functors/prioritised_work_allocator.h"
#include "TMP/CommonThreadingAliases.h"
#include "TMP/ThreadPoolTMP.h"

namespace EmuThreads
{
	template
	<
		class ThreadType_ = std::thread,
		class WorkAllocator_= EmuThreads::Functors::default_work_allocator,
		class ThreadAllocator_ = EmuThreads::Functors::default_thread_allocator<ThreadType_>
	>
	class ThreadPool
	{
	public:
		using thread_type = ThreadType_;
		using thread_allocator_type = ThreadAllocator_;
		using work_allocator_type = WorkAllocator_;
		using this_type = ThreadPool<thread_type, work_allocator_type>;
		using priority_type = typename EmuThreads::TMP::work_allocator_priority_type<work_allocator_type>::type;
		using size_type = typename EmuThreads::TMP::thread_allocator_size_type<thread_allocator_type>::type;
		
	private:
		/// <summary> Functor used for launching threads. Functor type instead of lambda to allow cleaner use in template arguments. </summary>
		struct _thread_launcher_type
		{
			_thread_launcher_type(work_allocator_type& work_allocator_ref_) : work_allocator_ref(work_allocator_ref_)
			{
			}
			inline thread_type operator()() const
			{
				return std::move(work_allocator_ref.template LaunchThread<thread_type>());
			}
			work_allocator_type& work_allocator_ref;
		};

		template<bool ShouldCancelValidation_>
		[[nodiscard]] static constexpr inline bool _do_thread_allocator_validation()
		{
			if constexpr (ShouldCancelValidation_)
			{
				return false;
			}
			else
			{
				return EmuThreads::TMP::is_valid_thread_allocator_for_thread_pool<thread_allocator_type, _thread_launcher_type, true>();
			}
		}

		static constexpr bool _valid_work_allocator = EmuThreads::TMP::is_valid_work_allocator_for_thread_pool<work_allocator_type, thread_type, true>();
		static constexpr bool _valid_thread_allocator = _do_thread_allocator_validation<!_valid_work_allocator>();

		static_assert
		(
			_valid_work_allocator,
			"Could not validate a ThreadAllocator_ for an EmuThreads::ThreadPool instantiation as the pool's WorkAllocator_ is invalid."
		);

		static_assert(_valid_work_allocator, "Invalid WorkAllocator_ provided to EmuThreads::ThreadPool instantiation.");
		// Cancel this static assertion  if thread allocator validation was cancelled for a previous reason, to avoid misleading compiler errors.
		static_assert(_valid_thread_allocator || !_valid_work_allocator, "Invalid ThreadAllocator_ provided to EmuThreads::ThreadPool instantiation.");

	public:
		static constexpr bool has_task_priorities = EmuThreads::TMP::work_allocator_has_priority<work_allocator_type>();

		/// <summary>
		/// <para> Makes a priority value for this thread pool's priority type. Only useful when the WorkAllocator_ supports prioritised tasks. </para>
		/// <para> If no arguments are passed AND WorkAllocator_ has a static default_priority function: Defers to `WorkAllocator_::default_priority`. </para>
		/// <para> If none of the above conditions are met: Will construct a priority type with the provided arguments. </para>
		/// </summary>
		template<class...Args_, typename = std::enable_if_t<std::is_constructible_v<priority_type, Args_...>>>
		[[nodiscard]] static constexpr inline priority_type make_priority(Args_&&...construction_args_)
		{
			if constexpr (sizeof...(Args_) == 0)
			{
				if constexpr (EmuThreads::TMP::has_static_default_priority_func<work_allocator_type, priority_type>::value)
				{
					if constexpr (EmuThreads::TMP::has_static_default_priority_func<work_allocator_type, priority_type>::return_matches_out)
					{
						return work_allocator_type::default_priority();
					}
					else
					{
						return static_cast<priority_type>(work_allocator_type::default_priority());
					}
				}
				else
				{
					return priority_type();
				}
			}
			else
			{
				return priority_type(construction_args_...);
			}
		}

		/// <summary>
		/// <para> Default constructs a thread pool with no threads allocated. Threads will need to be allocated at a later point. </para>
		/// </summary>
		ThreadPool() :
			thread_allocator(),
			work_allocator()
		{
		}
		/// <summary> Constructs a thread pool with the specified number of threads to perform allocated tasks, clamped into a valid range. </summary>
		/// <param name="num_threads_">Number of threads to attempt to allocate. Will be clamped to the inclusive range min_num_threads:max_num_threads.</param>
		inline ThreadPool(size_type num_threads_) : ThreadPool()
		{
			AllocateWorkers(num_threads_);
		}
		/// <summary>
		/// <para> Constructs a thread pool from the provided pool, transferring data to the newly formed pool. </para>
		/// <para> Queued work will be transferred to the new pool, but new threads will have to be allocated for it. </para>
		/// </summary>
		/// <param name="to_move_">Thread pool to move for constructing this new pool.</param>
		/// <param name="num_threads_">Custom number of threads to allocate to this pool. Will be clamped to the inclusive range min_num_threads:max_num_threads.</param>
		inline ThreadPool(this_type&& to_move_, size_type num_threads_) noexcept :
			thread_allocator(),
			work_allocator(std::move(to_move_.work_allocator))
		{
			work_allocator.Activate();
			AllocateWorkers(num_threads_);
		}
		/// <summary>
		/// <para> Constructs a thread pool from the provided pool, transferring data to the newly formed pool. </para>
		/// <para> Queued work will be transferred to the new pool, but new threads will have to be allocated for it. </para>
		/// <para> The provided thread pool to_move_ will have all of its threads deallocated. </para>
		/// <para> The number of threads allocated to this pool will be the same as the number of threads allocated to the pool being moved. </para>
		/// </summary>
		/// <param name="to_move_">Thread pool to move for constructing this new pool.</param>
		inline ThreadPool(this_type&& to_move_) noexcept : ThreadPool(std::forward<this_type>(to_move_), to_move_.NumThreads())
		{
		}

		~ThreadPool()
		{
			work_allocator.Deactivate();
			thread_allocator.JoinAll();
		}

		/// <summary>
		/// <para> Allocates the provided target number of threads to this pool, clamped into the inclusive range min_num_threads:max_num_threads. </para>
		/// <para> If target_num_threads_ is larger than the existing number of threads, the new threads will be allocated as work continues. </para>
		/// <para> If target_num_threads_ is lower than the existing number of threads, task execution will be paused to safely deallocate threads. </para>
		/// </summary>
		/// <param name="target_num_threads_">Target number of threads to allocate to this pool. Will be clamped into inclusive range min_num_threads:max_num_threads.</param>
		inline void AllocateWorkers(size_type target_num_threads_)
		{
			// Deactivate in case any deallocation needs to be performed
			work_allocator.Deactivate();
			thread_allocator.PrepareToAllocate(target_num_threads_);

			// Reactivate as allocation begins
			work_allocator.Activate();
			thread_allocator.Allocate(_thread_launcher_type(work_allocator), target_num_threads_);
		}

		/// <summary> Returns the number of threads currently allocated to this thread pool by its thread allocator. </summary>
		[[nodiscard]] inline size_type NumThreads() const
		{
			return thread_allocator.NumThreads();
		}

		/// <summary>
		/// <para> Provides constant access to this thread pool's thread allocator. </para>
		/// <para> This should not be manipulated to be modifiable, and such use is undefined behaviour. </para>
		/// <para> 
		///		This is intended to allow access to additional constant functionalities that are not available by default within a thread pool. 
		///		It will not be used by any Emu library functionalities.
		/// </para>
		/// </summary>
		/// <returns>Constant reference to this thread pool's underlying thread allocator.</returns>
		[[nodiscard]] inline const thread_allocator_type& ViewThreadAllocator() const
		{
			return thread_allocator;
		}

		/// <summary>
		/// <para> Provides constant access to this thread pool's work allocator. </para>
		/// <para> This should not be manipulated to be modifiable, and such use is undefined behaviour. </para>
		/// <para> 
		///		This is intended to allow access to additional constant functionalities that are not available by default within a thread pool. 
		///		It will not be used by any Emu library functionalities.
		/// </para>
		/// </summary>
		/// <returns>Constant reference to this thread pool's underlying work allocator.</returns>
		[[nodiscard]] inline const work_allocator_type& ViewWorkAllocator() const
		{
			return work_allocator;
		}

		/// <summary>
		/// <para> Deallocates all threads that have been allocated to this thread pool. </para>
		/// </summary>
		inline void DeallocateThreads()
		{
			// Deactivates work allocator to prevent new tasks from being allocated, removes threads when safe, then reactivates work allocator
			work_allocator.Deactivate();
			thread_allocator.DeallocateAll();
			work_allocator.Activate();
		}

		/// <summary> Returns the time that an individual thread will sleep for if there is no work available for it to execute, measured in milliseconds. </summary>
		[[nodiscard]] inline double WaitingTimeMs() const
		{
			// APPLIES FOR ALL WaitingTime FUNCTIONS:
			// If work_allocator_type does not implement the function of the same measurement, the function of the other measurement is assumed to be implemented.
			// --- Well-formed thread pools are guaranteed to have at least one time scale implemented as a static_assert will be triggered otherwise.
			// --- As such, we emulate a scale if it is not implemented by the underlying work_allocator_type.
			if constexpr (EmuThreads::TMP::has_const_waiting_time_ms_member_func<work_allocator_type, double>::value)
			{
				return static_cast<double>(work_allocator.WaitingTimeMs());
			}
			else
			{
				return WaitingTimeUs() * 0.001;
			}
		}
		/// <summary>
		/// <para> Updates the time that an individual thread will sleep for if there is no work available for it to execute, measured in milliseconds. </para>
		/// <para> The passed value may be subject to validation, which is performed by this thread pool's underlying work allocator. </para>
		/// </summary>
		/// <param name="new_waiting_time_ms_">Time for threads to wait when idle, in milliseconds.</param>
		/// <returns>Waiting time (in milliseconds) that threads are set to sleep for by this function. Typically matches new_waiting_time_ms_ if it is fully valid.</returns>
		inline double WaitingTimeMs(double new_waiting_time_ms_)
		{
			if constexpr (EmuThreads::TMP::has_modifying_waiting_time_ms_member_func<work_allocator_type, double>::value)
			{
				work_allocator.WaitingTimeMs(new_waiting_time_ms_);
			}
			else
			{
				WaitingTimeUs(new_waiting_time_ms_ * 1000.0);
			}
			return WaitingTimeMs();
		}

		/// <summary> Returns the time that an individual thread will sleep for if there is no work available for it to execute, measured in microseconds. </summary>
		[[nodiscard]] inline double WaitingTimeUs() const
		{
			if constexpr (EmuThreads::TMP::has_const_waiting_time_us_member_func<work_allocator_type, double>::value)
			{
				return static_cast<double>(work_allocator.WaitingTimeUs());
			}
			else
			{
				return WaitingTimeMs() * 1000;
			}
		}
		/// <summary>
		/// <para> Updates the time that an individual thread will sleep for if there is no work available for it to execute, measured in microseconds. </para>
		/// <para> The passed value may be subject to validation, which is performed by this thread pool's underlying work allocator. </para>
		/// </summary>
		/// <param name="new_waiting_time_us_">Time for threads to wait when idle, in microseconds.</param>
		/// <returns>Waiting time (in microseconds) that threads are set to sleep for by this function. Typically matches new_waiting_time_us_ if it is fully valid.</returns>
		inline double WaitingTimeUs(double new_waiting_time_us_)
		{
			if constexpr (EmuThreads::TMP::has_modifying_waiting_time_us_member_func<work_allocator_type, double>::value)
			{
				work_allocator.WaitingTimeUs(new_waiting_time_us_);
			}
			else
			{
				WaitingTimeMs(new_waiting_time_us_ * 0.001);
			}
			return WaitingTimeUs();
		}

		/// <summary>
		/// <para> Performs allocation of any valid generic task to be performed by one of this pool's worker threads. </para>
		/// <para> The provided args_ must be valid arguments to invoke the provided func_ via the syntax `func_(args_...)`. </para>
		/// <para> A future to the task's results is also returned by this allocation. </para>
		/// <para> If non-value arguments are being provided, it is highly recommended to explicitly type provided Args_ template types, or use std wrappers. </para>
		/// <para> If this thread pool's work allocator supports prorities, this will apply the default priority to the provided task. </para>
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
			if constexpr (has_task_priorities)
			{
				return work_allocator.AllocateTask(make_priority(), std::bind(func_, EmuThreads::TMP::get_suitable_bind_arg<Args_>(args_)...));
			}
			else
			{
				return work_allocator.AllocateTask(std::bind(func_, EmuThreads::TMP::get_suitable_bind_arg<Args_>(args_)...));
			}
		}

		/// <summary>
		/// <para> Performs allocation of any valid generic task to be performed by one of this pool's worker threads. </para>
		/// <para> The provided args_ must be valid arguments to invoke the provided func_ via the syntax `func_(args_...)`. </para>
		/// <para> A future to the task's results is also returned by this allocation. </para>
		/// <para> If non-value arguments are being provided, it is highly recommended to explicitly type provided Args_ template types, or use std wrappers. </para>
		/// <para> If this thread pool's work allocator does not support priorities, this will trigger a static assertion as the priority cannot be used as intended. </para>
		/// </summary>
		/// <typeparam name="Args_">All argument types to pass in the provided order when invoking the provided func_.</typeparam>
		/// <typeparam name="Func_">Type of invocable to be called.</typeparam>
		/// <param name="priority_">Priority level to provide to the passed task. For default EmuThreads allocators, lower priority values are allocated first.</param>
		/// <param name="func_">Invocable item (such as a functor or function pointer) to be invoked.</param>
		/// <param name="args_">Arguments to pass when invoking the provided func_.</param>
		/// <returns>
		///		Future to the provided task, allowing retrieval of results at a later point. 
		///		Note that this future indicating completion does not necessarily guarantee that other allocated tasks - before or after - have been completed.
		/// </returns>
		template<class...Args_, class Func_, typename RequiresValidArgs_ = std::enable_if_t<std::is_invocable_v<Func_, Args_...>>>
		inline auto AllocateTask(const priority_type& priority_, Func_ func_, Args_...args_)
		{
			if constexpr (has_task_priorities)
			{
				return work_allocator.AllocateTask(priority_, std::bind(func_, EmuThreads::TMP::get_suitable_bind_arg<Args_>(args_)...));
			}
			else
			{
				static_assert(false, "Attempted to allocate a task to an EmuThreads::ThreadPool with a designated priority, but the underlying work allocator does not take priority arguments.");
			}
		}

	private:
		thread_allocator_type thread_allocator;
		work_allocator_type work_allocator;
	};

	/// <summary>
	/// <para> Alias for EmuThreads::ThreadPool with all default arguments. </para>
	/// <para> Recommended when wanting the default parameters in a context where at least some arguments are required. </para>
	/// </summary>
	using DefaultThreadPool = ThreadPool
	<
		std::thread,
		EmuThreads::Functors::default_work_allocator,
		EmuThreads::Functors::default_thread_allocator<std::thread>
	>;

	/// <summary>
	/// <para>
	///		Alias for EmuThreads::ThreadPool with default arguments except for the work allocator, which is the default EmuThreads::Functors::prioritised_work_allocator.
	/// </para>
	/// </summary>
	template<typename PriorityType_>
	using PrioritisedThreadPool = ThreadPool
	<
		std::thread,
		EmuThreads::Functors::prioritised_work_allocator<PriorityType_>,
		EmuThreads::Functors::default_thread_allocator<std::thread>
	>;
	/// <summary>
	/// <para> Alias for EmuThreads::PrioritisedThreadPool with EmuThreads::TMP::default_priority_type as the priority type. </para>
	/// </summary>
	using DefaultPrioritisedThreadPool = PrioritisedThreadPool<EmuThreads::TMP::default_priority_type>;
}

#endif
