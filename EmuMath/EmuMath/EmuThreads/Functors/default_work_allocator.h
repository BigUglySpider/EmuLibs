#ifndef EMU_THREADS_FUNCTORS_DEFAULT_WORK_ALLOCATOR_H_INC_
#define EMU_THREADS_FUNCTORS_DEFAULT_WORK_ALLOCATOR_H_INC_ 1

#include <atomic>
#include <chrono>
#include <functional>
#include <future>
#include <limits>
#include <mutex>
#include <queue>
#include <type_traits>

namespace EmuThreads::Functors
{
	class default_work_allocator
	{
	public:
		using this_type = default_work_allocator;

		/// <summary> The waiting time (in milliseconds) used when no other time is provided. </summary>
		static constexpr double default_waiting_time_ms = 0.01;
		/// <summary> Minimum waiting time (in milliseconds) that may be used in this allocator's downtime. </summary>
		static constexpr double min_waiting_time_ms = 0.0000000001;
		/// <summary> Maximum waiting time (in milliseconds) that may be used in this allocator's downtime. </summary>
		static constexpr double max_waiting_time_ms = std::numeric_limits<double>::max();

		/// <summary> Helper to reduce verbosity when creating a duration in milliseconds. The passed time value is not validated. </summary>
		/// <param name="time_in_ms_">Number of milliseconds to use for creating the resulting duration.</param>
		/// <returns>Chrono duration in milliseconds, with `double` representation, using the provided time_in_ms_. </returns>
		template<typename InNum_>
		[[nodiscard]] static constexpr inline std::chrono::duration<double, std::milli> time_in_ms(const InNum_& time_in_ms_)
		{
			return std::chrono::duration<double, std::milli>(static_cast<double>(time_in_ms_));
		}

		/// <summary> Creates a version of the passed waiting_time_ms_ which is valid for use with this allocator. </summary>
		/// <param name="waiting_time_ms_">Waiting time to validate.</param>
		/// <returns>The passed waiting_time_ms_ value clamped into the inclusive range min_waiting_time_ms:max_waiting_time_ms.</returns>
		[[nodiscard]] static constexpr inline double validate_waiting_time_ms(double waiting_time_ms_)
		{
			return (waiting_time_ms_ <= min_waiting_time_ms) ? min_waiting_time_ms : (waiting_time_ms_ >= max_waiting_time_ms) ? max_waiting_time_ms : waiting_time_ms_;
		}

		default_work_allocator() : 
			is_active(true),
			work_queue(),
			queue_mutex(),
			working_thread_count(0),
			waiting_time_ms(default_waiting_time_ms)
		{
		}

		default_work_allocator(double waiting_time_ms_) :
			is_active(true),
			work_queue(),
			queue_mutex(),
			working_thread_count(0),
			waiting_time_ms(validate_waiting_time_ms(waiting_time_ms_))
		{
		}

		/// <summary>
		/// <para> Creates a work allocator from the passed allocator, taking tasks from the passed to_move_ allocator. </para>
		/// <para> This construction will not retain the linked threads of the moved allocator, only its queued tasks. </para>
		/// </summary>
		/// <param name="to_move_">Work allocator to move into the newly constructed allocator.</param>
		/// <param name="waiting_time_ms_">Custom time for threads linked to this allocator to wait for during downtime (in milliseconds).</param>
		inline default_work_allocator(this_type&& to_move_, double waiting_time_ms_) noexcept :
			is_active(true),
			work_queue(),
			queue_mutex(),
			working_thread_count(0),
			waiting_time_ms(validate_waiting_time_ms(waiting_time_ms_))
		{
			std::lock_guard<mutex_type> lock_(to_move_.queue_mutex);
			work_queue.swap(to_move_.work_queue);
			to_move_.num_queued_tasks = 0;
		}
		/// <summary>
		/// <para> Creates a work allocator from the passed allocator, taking tasks from the passed to_move_ allocator. </para>
		/// <para> This construction will not retain the linked threads of the moved allocator, only its queued tasks and waiting time. </para>
		/// </summary>
		/// <param name="to_move_">Work allocator to move into the newly constructed allocator.</param>
		inline default_work_allocator(this_type&& to_move_) noexcept : default_work_allocator(std::forward<this_type>(to_move_), to_move_.waiting_time_ms)
		{
		}

		default_work_allocator(const this_type&) = delete;

		inline ~default_work_allocator()
		{
			Deactivate();
			ClearWorkQueue();
			WaitForAllTasksToComplete();
		}

		/// <summary>
		/// <para> Constructs a thread which is launched into this allocator's task execution loop. </para>
		/// <para> The thread will remain looping for as long as this allocator is in the active state, even when no tasks are queued. </para>
		/// <para> It is the caller's responsibility to ensure that this thread is safely stored and, when needed, closed. </para>
		/// <para> 
		///		Note: this object will gracefully finish active tasks upon destruction. 
		///		However, if threads are deallocated before this object's destruction, 
		///		it is the caller's responsibility to ensure it is not using threads before they are deallocated
		///		(this can be achieved through Deactivate, followed by joining the threads in question (or equivalent)).
		/// </para>
		/// </summary>
		/// <typeparam name="Thread_">Type of thread to construct.</typeparam>
		/// <returns>Thread of the provided Thread_ type, constructed to be executing within this allocator's work loop for as long as it is active.</returns>
		template<class Thread_>
		[[nodiscard]] inline Thread_ LaunchThread()
		{
			return Thread_(&this_type::_worker_execution, this);
		}

		/// <summary>
		/// <para> Removes any work that has not yet been allocated to a thread. </para>
		/// <para> This will not stop work that is currently being executed. </para>
		/// </summary>
		inline void ClearWorkQueue()
		{
			std::lock_guard<mutex_type> lock_(queue_mutex);
			decltype(work_queue)().swap(work_queue);
		}

		/// <summary> Returns a boolean indicating if this allocator has any tasks queued and waiting for a thread. </summary>
		[[nodiscard]] inline bool HasWork() const
		{
			return num_queued_tasks != 0;
		}

		/// <summary> The number of threads currently performing work from this allocator. </summary>
		[[nodiscard]] inline std::size_t NumWorkingThreads() const
		{
			return working_thread_count;
		}

		/// <summary> Returns true if this allocator is active. While active, all threads created by it will be performing its execution loop until inactive. </summary>
		[[nodiscard]] inline bool IsActive() const
		{
			return is_active;
		}

		/// <summary> The number of tasks that this allocator is waiting to provide to a thread for execution. </summary>
		[[nodiscard]] inline std::size_t NumQueuedTasks() const
		{
			return num_queued_tasks;
		}

		/// <summary>
		/// <para> Waits for all of this allocator's tasks to be completed, using only its linked threads to do so. </para>
		/// <para> WARNING: if no threads are linked with this allocator, this will cause a program crash if any work is queued. </para>
		/// </summary>
		inline void WaitForAllTasksToCompleteNoJoin() const
		{
			while (HasWork())
			{
				std::this_thread::sleep_for(time_in_ms(waiting_time_ms));
			}
		}

		/// <summary>
		/// <para> Waits for all of this allocator's tasks to be completed, and the calling thread may contribute to completing said tasks. </para>
		/// <para> If the calling thread's contribution is undesired, call WaitForAllTasksToCompleteNoJoin instead. </para>
		/// </summary>
		inline void WaitForAllTasksToComplete()
		{
			// The waiting thread will contribute to work as it is allowed to pop the queue
			while (HasWork())
			{
				_look_for_work();
			}
		}
		inline void WaitForAllTasksToComplete() const
		{
			// Work will only be poppable (and well-formed) if this is non-const, so this is conceptually safe to allow the calling thread to join in with work.
			const_cast<this_type*>(this)->WaitForAllTasksToComplete();
		}

		/// <summary> Returns the amount of time that this allocator's linked threads will wait before checking for a new task, in milliseconds. </summary>
		[[nodiscard]] inline double WaitingTimeMs() const
		{
			return waiting_time_ms;
		}

		/// <summary>
		/// <para> Sets the amount of time (in milliseconds) that this allocator's linked threads will wait before checking for a new task. </para>
		/// </summary>
		/// <param name="waiting_time_ms_">
		///		Amount of time to wait in milliseconds. 
		///		This will be clamped into the inclusive range min_waiting_time_ms:max_waiting_time_ms.
		/// </param>
		/// <returns>Validated value that the waiting time for this allocator is set to via the passed argument.</returns>
		inline double WaitingTimeMs(double waiting_time_ms_)
		{
			waiting_time_ms = validate_waiting_time_ms(waiting_time_ms_);
			return waiting_time_ms;
		}

		/// <summary> Marks this allocator as active, allowing threads linked to it to participate in its execution loop. </summary>
		inline void Activate()
		{
			is_active = true;
		}

		/// <summary> 
		/// <para> Marks this allocator as inactive, preventing new threads from participating in its execution loop. </para>
		/// <para> Additionally, currently linked threads will unlink once they have finished executing their current task if this allocator remains inactive. </para>
		/// </summary>
		inline void Deactivate()
		{
			is_active = false;
		}

		/// <summary>
		/// <para> Allocates a task to be queued and executed by threads linked to this allocator. </para>
		/// <para> The provided args_ must be compatible with the provided func_. </para>
		/// <para> This does not enforce reference protection, or perform binds where they may be preferred. Such tasks are the responsibility of the caller, if needed. </para>
		/// </summary>
		/// <param name="func_">Invocable item to call.</param>
		/// <param name="args_">Arguments to provide when invoking the passed func_, with the syntax `func_(args_...)`.</param>
		/// <returns>Future to the task, allowing its result to be retrieved. A complete future does not guarantee that previously allocated tasks are complete.</returns>
		template<class Func_, class...Args_>
		inline auto AllocateTask(Func_ func_, Args_...args_)->std::future<decltype(func_(args_...))>
		{
			if constexpr (std::is_invocable_v<Func_, Args_...>)
			{
				auto wrapped_func_ = std::make_shared<std::packaged_task<decltype(func_(args_...))(Args_...)>>(func_);
				std::lock_guard<mutex_type> lock_(queue_mutex);
				work_queue.emplace([=]() { (*wrapped_func_)(args_...); });
				++num_queued_tasks;
				return wrapped_func_->get_future();
			}
			else
			{
				static_assert(false, "Attempted to allocate a task via EmuThreading::Functors::default_work_allocator, but the provided Func_ type cannot be invoked with the provided Args_.");
			}
		}

	private:
		using work_type = std::function<void()>;
		using work_queue_type = std::queue<work_type>;
		using mutex_type = std::mutex;

		/// <summary> This is designed to run on a separate worker thread, and not the main thread. Constantly looks for work. </summary>
		inline void _worker_execution()
		{
			while (is_active)
			{
				_look_for_work();
			}
		}

		inline void _look_for_work()
		{
			std::unique_lock<mutex_type> lock_(queue_mutex);
			if (is_active && num_queued_tasks != 0)
			{
				// Get task and unlock as soon as reasonable
				work_type next_task_ = std::move(_pop_next_task());
				lock_.unlock();

				// Include incrementing/decrementing work counter as a part of the task
				// --- Since it's atomic, we don't need to worry about the lock
				++working_thread_count;
				next_task_();
				--working_thread_count;
			}
			else
			{
				lock_.unlock();
				std::this_thread::sleep_for(time_in_ms(waiting_time_ms));
			}
		}

		inline work_type _pop_next_task()
		{
			work_type out_task_ = std::move(work_queue.front());
			work_queue.pop();
			--num_queued_tasks;
			return out_task_;
		}

		std::atomic_bool is_active;
		std::atomic_size_t working_thread_count;
		std::atomic_size_t num_queued_tasks;
		mutex_type queue_mutex;
		work_queue_type work_queue;
		double waiting_time_ms;
	};
}

#endif
