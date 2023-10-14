#ifndef EMU_THREADS_BASIC_THREAD_POOL_H_INC_
#define EMU_THREADS_BASIC_THREAD_POOL_H_INC_ 1

#include <algorithm>
#include <atomic>
#include <deque>
#include <future>
#include <iterator>
#include <mutex>
#include <thread>
#include <type_traits>
#include <variant>

#include "../EmuCore/CommonConcepts/CommonRequirements.h"
#include "../EmuCore/CommonPreprocessor/Warning.h"

namespace EmuThreads
{
	template<EmuConcepts::Invocable<> Func_>
	class BasicThreadPool
	{
	public:
		using func_type = Func_;
		using func_return_type = typename std::invoke_result<func_type>::type;

	private:
		using packaged_func_type = std::packaged_task<func_return_type()>;

		struct task_or_packaged_task_type
		{
		public:
			using func_variant_type = std::variant<Func_, packaged_func_type>;

			task_or_packaged_task_type() = delete;
			task_or_packaged_task_type(const task_or_packaged_task_type&) = delete;
			task_or_packaged_task_type& operator=(const task_or_packaged_task_type&) = delete;
			task_or_packaged_task_type& operator=(task_or_packaged_task_type&&) = delete;

			task_or_packaged_task_type(task_or_packaged_task_type&& to_move_) noexcept :
				is_packaged(to_move_.is_packaged),
				func(std::move(to_move_.func))
			{
			}

			template<EmuConcepts::UnqualifiedMatch<Func_> TaskFunc_>
			constexpr task_or_packaged_task_type(TaskFunc_&& task_func_) noexcept(std::is_nothrow_constructible_v<func_variant_type, TaskFunc_>) :
				is_packaged(false),
				func(std::forward<TaskFunc_>(task_func_))
			{
			}

			template<EmuConcepts::UnqualifiedMatch<packaged_func_type> PackagedTaskFunc_>
			constexpr task_or_packaged_task_type(PackagedTaskFunc_&& packaged_task_func_) noexcept(std::is_nothrow_constructible_v<func_variant_type, PackagedTaskFunc_>) :
				is_packaged(true),
				func(std::forward<PackagedTaskFunc_>(packaged_task_func_))
			{
			}

			inline void operator()()
			{
				if (is_packaged)
				{
					std::get<packaged_func_type>(func)();
				}
				else
				{
					std::get<func_type>(func)();
				}
			}

		private:
			const bool is_packaged;
			func_variant_type func;
		};

		template<class CountType_>
		struct count_guard
		{
			using count_type = CountType_;

			count_guard() = delete;
			count_guard(const count_guard&) = delete;
			count_guard(count_guard&&) = delete;
			count_guard& operator=(const count_guard&&) = delete;
			count_guard& operator=(count_guard&&) = delete;

			constexpr count_guard(count_type& count_ref_) noexcept :
				count_ref(count_ref_)
			{
				++count_ref;
			}

			~count_guard()
			{
				--count_ref;
			}

			count_type& count_ref;
		};

		friend struct thread_loop;
		struct thread_loop
		{
			thread_loop() = delete;
			thread_loop(const thread_loop&) = delete;
			thread_loop& operator=(const thread_loop&) = delete;
			thread_loop& operator=(thread_loop&&) = delete;


			constexpr thread_loop(BasicThreadPool<Func_>& parent_pool_) noexcept :
				parent_pool(parent_pool_)
			{
			}
			constexpr thread_loop(thread_loop&& to_move_) noexcept :
				parent_pool(to_move_.parent_pool)
			{
			}

			inline void operator()() const
			{
				while (!parent_pool._threads_closing)
				{
					// Either execute a task or yield
					if (!parent_pool._execute_task())
					{
						std::this_thread::yield();
					}
				}
			}

			BasicThreadPool<Func_>& parent_pool;
		};

	public:
		/// <summary>
		/// <para> The minimum number of Worker Threads that any Thread Pool may have. </para>
		/// </summary>
		static constexpr std::size_t min_num_worker_threads = 1;

		/// <summary>
		/// <para> If true, this Thread Pool will be allowed to finish all of its queued tasks before closing upon destruction. </para>
		/// <para> Also defines the default value for the respective argument when manually calling `Close`. </para>
		/// </summary>
		static constexpr bool must_finish_tasks_on_destruction = true;

		/// <summary>
		/// <para> If true, the thread invoking this Thread Pool's destructor will contribute to completing tasks before closing (if tasks must be completed). </para>
		/// <para> Also defines the default value for the respective argument when manually calling `Close`. </para>
		/// </summary>
		static constexpr bool destructing_thread_may_contribute_to_tasks = true;

		BasicThreadPool(const BasicThreadPool<Func_>&) = delete;
		BasicThreadPool<Func_>& operator=(const BasicThreadPool<Func_>&) = delete;

		/// <summary>
		/// <para> Initialises a Thread Pool with the minimum number of Worker Threads. </para>
		/// </summary>
		explicit BasicThreadPool() : 
			BasicThreadPool(min_num_worker_threads)
		{
		}

		/// <summary>
		/// <para> Initialises a Thread Pool with the number of Worker Threads of the input Thread Pool. </para>
		/// <para> Additionally, the Task Queue of the input Thread Pool is moved into the newly constructed Thread Pool. </para>
		/// </summary>
		/// <param name="to_move_">Thread Pool to move.</param>
		explicit BasicThreadPool(BasicThreadPool<Func_>&& to_move_) noexcept :
			BasicThreadPool(to_move_.num_worker_threads)
		{
			_move_pool(std::move(to_move_));
		}

		/// <summary>
		/// <para> Initialises a Thread Pool with the specified number of Worker Threads. </para>
		/// </summary>
		/// <param name="num_worker_threads_">Number of Worker Threads for this Thread Pool to use. Clamped to a minimum of `min_num_worker_threads`.</param>
		explicit BasicThreadPool(const std::size_t num_worker_threads_) :
			num_worker_threads(num_worker_threads_ <= min_num_worker_threads ? min_num_worker_threads : num_worker_threads_),
			_mutex_for_task_queue(),
			_task_queue(),
			_accepting_tasks(true),
			_tasks_currently_being_added(0),
			_num_merges_in_progress(0),
			_threads_closing(false)
		{
			_launch_threads();
		}

		~BasicThreadPool()
		{
			if (!_threads_closing)
			{
				Close<must_finish_tasks_on_destruction, destructing_thread_may_contribute_to_tasks>();
			}
		}

		/// <summary>
		/// <para> Moves the Task Queue of the right-hand Thread Pool into the end of the Task Queue of the left-hand Thread Pool. </para>
		/// </summary>
		/// <param name="to_move_">Thread Pool whose Task Queue will be moved into the end of the left-hand Thread Pool's Task Queue.</param>
		/// <returns>Reference to the left-hand Thread Pool.</returns>
		BasicThreadPool<Func_>& operator=(BasicThreadPool<Func_>&& to_move_) noexcept
		{
			auto num_merges_in_progress_guard = _make_count_guard(_num_merges_in_progress);
			_move_pool(std::move(to_move_));
			return *this;
		}

		/// <summary>
		/// <para> Prematurely closes this Thread Pool. </para>
		/// <para> All Worker Threads will be closed and their memory will be released. </para>
		/// <para> If MustFinishTasks_ is true, this Thread Pool's queued tasks will be completed before it is closed. </para>
		/// <para>
		///		If MustFinishTasks_ is false, only in-flight tasks in this Thread Pool's queued tasks will be completed. 
		///		Tasks still waiting to be allocated to a Worker Thread will never be completed.
		/// </para>
		/// <para>
		///		If ThisThreadMayContribute_ is true, the calling thread may contribute to finishing tasks before closing; 
		///		otherwise it will yield until tasks are completed. 
		///		This only has any meaning if MustFinishTasks_ is true.
		/// </para>
		/// <para> The default value of MustFinishTasks_ is equal to must_finish_tasks_on_destruction. </para>
		/// <para> The default value of ThisThreadMayContribute_ is equal to destructing_thread_may_contribute_to_tasks. </para>
		/// <para> 
		///		WARNING: This should (borderline *must*) be called only by the thread owning this Thread Pool (most likely the main thread). 
		///		As it will automatically be called upon destruction if it does not detect that the threads are currently closed, 
		///		closing on different threads can result in conflicts leading to undefined behaviour.
		/// </para>
		/// </summary>
		template<bool MustFinishTasks_ = must_finish_tasks_on_destruction, bool ThisThreadMayContribute_ = destructing_thread_may_contribute_to_tasks>
		inline void Close()
		{
			// False warnings - MSVC doesn't properly tell that control is correctly handled for locks between functions here
			EMU_CORE_MSVC_PUSH_WARNING_STACK;
			EMU_CORE_MSVC_DISABLE_WARNING(26115);
			if constexpr (MustFinishTasks_)
			{
				// Use personal task_queue_lock to check if the queue is populated
				// --- This is to allow this thread to lock if needed
				_accepting_tasks = false;
				std::unique_lock<std::mutex> task_queue_lock(_mutex_for_task_queue);
				while (_has_potential_tasks_for_calling_thread<false>())
				{
					if constexpr (ThisThreadMayContribute_)
					{
						// Contribute a task
						// --- We're dedicating this thread to helping with closing the pool, so no yields are performed
						// --- lock is released in the middle of _execute_task
						_execute_task(task_queue_lock);
					}
					else
					{
						task_queue_lock.unlock();
						std::this_thread::yield();
					}
					task_queue_lock.lock();
				}
			}
			_close_threads();
			EMU_CORE_MSVC_POP_WARNING_STACK;
		}

		/// <summary>
		/// <para> Redirects the calling thread's execution to assist with this Thread Pool's Task Queue. </para>
		/// <para> This function will only return once the current queue is cleared and no tasks are currently being added to the Queue in any way. </para>
		/// </summary>
		inline void UseThisThreadForCurrentQueue()
		{
			// False warnings - MSVC doesn't properly tell that control is correctly handled for locks between functions here
			EMU_CORE_MSVC_PUSH_WARNING_STACK;
			EMU_CORE_MSVC_DISABLE_WARNING(26115);
			std::unique_lock<std::mutex> task_queue_lock(_mutex_for_task_queue);
			while (_has_potential_tasks_for_calling_thread<false>())
			{
				// Contribute a task
				// --- We're dedicating this thread to helping with the current queue, so no yields are performed
				// --- lock is released in the middle of _execute_task
				_execute_task(task_queue_lock);
				task_queue_lock.lock();
			}
			EMU_CORE_MSVC_POP_WARNING_STACK;
		}

		/// <summary>
		/// <para> Redirects the calling thread's execution to assist with this Thread Pool's Task Queue. </para>
		/// <para> This function will return after the current queue is cleared and no tasks are currently being added to the Queue in any way. </para>
		/// <para> Alternatively, this function will return once the calling thread has contributed a number of tasks equal to MaxTasks_. </para>
		/// <para> If MaxTasks_ is 0, this function will return immediately and the calling thread will not contribute. </para>
		/// </summary>
		/// <returns>Number of tasks that the calling thread attempted to execute. This will be in the inclusive range of 0:MaxTasks_.</returns>
		template<std::size_t MaxTasks_>
		inline std::size_t UseThisThreadForCurrentQueue()
		{
			if constexpr (MaxTasks_ == 0)
			{
				return 0;
			}

			// False warnings - MSVC doesn't properly tell that control is correctly handled for locks between functions here
			EMU_CORE_MSVC_PUSH_WARNING_STACK;
			EMU_CORE_MSVC_DISABLE_WARNING(26115);
			std::size_t num_tasks_contributed = 0;
			std::unique_lock<std::mutex> task_queue_lock(_mutex_for_task_queue);
			while (_has_potential_tasks_for_calling_thread<false>())
			{
				// Contribute a task
				// --- We're dedicating this thread to helping with the current queue, so no yields are performed
				// --- lock is released in the middle of _execute_task
				_execute_task(task_queue_lock);
				++num_tasks_contributed;
				if (num_tasks_contributed == MaxTasks_)
				{
					return num_tasks_contributed;
				}
				task_queue_lock.lock();
			}
			return num_tasks_contributed;
			EMU_CORE_MSVC_POP_WARNING_STACK;
		}

		/// <summary>
		/// <para> Redirects the calling thread's execution to assist with this Thread Pool's Task Queue. </para>
		/// <para> This function will return after the current queue is cleared and no tasks are currently being added to the Queue in any way. </para>
		/// <para> Alternatively, this function will return once `early_break_test_` returns true upon being invoked with no arguments. </para>
		/// <para> The calling thread will be guaranteed to attempt executing at least 1 task. </para>
		/// </summary>
		/// <param name="early_break_test_">Object that may be invoked with no arguments to return a bool (or a type that may be interpreted as boolean in a conditional statement).</param>
		/// <returns>True if this function returns early due to `early_break_test_`; otherwise false.</returns>
		template<EmuConcepts::InvocableWithReturn<bool> EarlyBreakTest_>
		inline bool UseThisThreadForCurrentQueue(EarlyBreakTest_ early_break_test_)
		{
			// False warnings - MSVC doesn't properly tell that control is correctly handled for locks between functions here
			EMU_CORE_MSVC_PUSH_WARNING_STACK;
			EMU_CORE_MSVC_DISABLE_WARNING(26115);
			std::unique_lock<std::mutex> task_queue_lock(_mutex_for_task_queue);
			while (_has_potential_tasks_for_calling_thread<false>())
			{
				// Contribute a task
				// --- We're dedicating this thread to helping with the current queue, so no yields are performed
				// --- lock is released in the middle of _execute_task
				_execute_task(task_queue_lock);
				if (early_break_test_())
				{
					return true;
				}
				task_queue_lock.lock();
			}
			return false;
			EMU_CORE_MSVC_POP_WARNING_STACK;
		}

		/// <summary>
		/// <para> Adds a Task to this Thread Pool's Task Queue. </para>
		/// <para> If this thread Pool is not accepting tasks or is closing its threads, this will immediately execute the task without queuing. </para>
		/// <para>
		///		If ReturnFuture_ is true: this will return a future to the return value of the task being queued. 
		///		This queuing method is guaranteed to be the most expensive of the two options.
		/// </para>
		///	<para> 
		///		If ReturnFuture_ is false: this will not return anything. 
		///		You will not be able to retrieve the function's return value or be able to await its completion directly, 
		///		however this approach will queue the task at a cheaper cost than the other option.
		/// </para>
		/// </summary>
		/// <param name="func_construction_args_">Arguments to construct an instance of this Thread Pool's func_type. The resulting function will be queued.</param>
		/// <returns>
		/// <para> If ReturnFuture_ is false: void. </para>
		/// <para> If ReturnFuture_ is true: future to the return value of the queued task. </para>
		/// </returns>
		template<bool ReturnFuture_, class...FuncConstructionArgs_>
		requires(std::is_constructible_v<Func_, FuncConstructionArgs_...>)
		inline auto AddTaskToQueue(FuncConstructionArgs_&&...func_construction_args_)
			-> typename std::conditional<ReturnFuture_, std::future<func_return_type>, void>::type
		{
			auto tasks_being_added_count_guard = _make_count_guard(_tasks_currently_being_added);
			auto task = func_type(std::forward<FuncConstructionArgs_>(func_construction_args_)...);
			if (_accepting_tasks && !_threads_closing)
			{
				if constexpr (ReturnFuture_)
				{
					auto task_packaged = packaged_func_type(std::move(task));
					std::future<func_return_type> future = task_packaged.get_future();

					std::lock_guard<std::mutex> task_queue_lock(_mutex_for_task_queue);
					_task_queue.emplace_back(std::move(task_packaged));
					return future;
				}
				else
				{
					std::lock_guard<std::mutex> task_queue_lock(_mutex_for_task_queue);
					_task_queue.emplace_back(std::move(task));
				}
			}
			else
			{
				// Can't execute in pool so execute now instead of abandoning
				if constexpr (ReturnFuture_)
				{
					// Returns a future, so make a fake promise which we immediately fulfil
					auto fake_promise = std::promise<func_return_type>();
					if constexpr (std::is_void_v<func_return_type>)
					{
						task();
						fake_promise.set_value();
					}
					else
					{
						fake_promise.set_value(task());
					}
					return fake_promise.get_future();
				}
				else
				{
					task();
				}
			}
		}

		/// <summary>
		/// <para> Returns the number of tasks currently waiting to be allocated to a Worker Thread in this Thread Pool's Task Queue. </para>
		/// <para> This does not account for tasks currently being executed. </para>
		/// <para> If Lock_ is true, this will lock the Task Queue before determining the count. By default, Lock_ is true. </para>
		/// </summary>
		/// <returns>Number of tasks currently waiting to be allocated to a Worker Thread in this Thread Pool's Task Queue.</returns>
		template<bool Lock_ = true>
		[[nodiscard]] inline std::size_t GetNumTasksInQueue() const noexcept(!Lock_)
		{
			if constexpr (Lock_)
			{
				std::lock_guard<std::mutex> task_queue_lock(_mutex_for_task_queue);
				return _task_queue.size();
			}
			else
			{
				return _task_queue.size();
			}
		}

		/// <summary>
		/// <para> Returns a boolean indicating if there are currently tasks waiting to be allocated to a Worker Thread in this Thread Pool's Task Queue. </para>
		/// <para> This does not account for tasks currently being executed. </para>
		/// <para> If Lock_ is true, this will lock the Task Queue before determining the count. By default, Lock_ is true. </para>
		/// </summary>
		/// <returns>True if there are any tasks currently in this Thread Pool's Task Queue waiting to be allocated to a Worker Thread; otherwise false.</returns>
		template<bool Lock_ = true>
		[[nodiscard]] inline bool HasAnyTasksInQueue() const noexcept(!Lock_)
		{
			return GetNumTasksInQueue<Lock_>() > 0;
		}

		/// <summary>
		/// <para> Returns the number of tasks that are currently being added to this Thread Pool's Task Queue. </para>
		/// <para> If the program only adds tasks through the calling thread, this will always be 0. </para>
		/// </summary>
		/// <returns>Number of tasks currently in the process of being added to this Thread Pool's Task Queue.</returns>
		[[nodiscard]] inline std::size_t GetNumTasksCurrentlyBeingAdded() const noexcept
		{
			return _tasks_currently_being_added;
		}

		/// <summary>
		/// <para> Returns a boolean indicating if there are currently tasks being added to this Thread Pool's Task Queue. </para>
		/// <para> If the program only adds tasks through the calling thread, this will always be false. </para>
		/// </summary>
		/// <returns>True if any tasks are currently being added to this Thread Pool's Task Queue; otherwise false.</returns>
		[[nodiscard]] inline bool CurrentlyAddingTasksToQueue() const noexcept
		{
			return _tasks_currently_being_added > 0;
		}

		/// <summary>
		/// <para> Returns the number of merges that are currently in progress (i.e. the number of Thread Pools being moved into this Thread Pool). </para>
		/// <para> If the program only manages Thread Pools through the calling thread, this will always be 0. </para>
		/// </summary>
		/// <returns>Number of Thread Pools currently being moved into this Thread Pool.</returns>
		[[nodiscard]] inline std::size_t GetNumMergesCurrentlyInProgress() const noexcept
		{
			return _num_merges_in_progress;
		}

		/// <summary>
		/// <para> Returns a boolean indicating if there are any merges currently in progress (i.e. if any Thread Pools being moved into this Thread Pool). </para>
		/// <para> If the program only manages Thread Pools through the calling thread, this will always be false. </para>
		/// </summary>
		/// <returns>True if any Thread Pools are currently being moved into this Thread Pool; otherwise false.</returns>
		[[nodiscard]] inline bool CurrentlyMerging() const noexcept
		{
			return _num_merges_in_progress > 0;
		}

		/// <summary>
		/// <para> The number of worker threads that this Thread Pool makes use of. </para>
		/// <para> This is the number of Tasks that this Thread Pool can independetly execute simultaneously. </para>
		/// </summary>
		const std::size_t num_worker_threads;

	private:
		template<class T_>
		requires(!std::is_const_v<T_>)
		[[nodiscard]] static inline count_guard<T_> _make_count_guard(T_& count_ref_) noexcept
		{
			return count_guard<T_>(count_ref_);
		}

		template<bool Lock_>
		[[nodiscard]] inline bool _has_potential_tasks_for_calling_thread()
		{
			return HasAnyTasksInQueue<Lock_>() || CurrentlyAddingTasksToQueue() || CurrentlyMerging();
		}

		inline void _move_pool(BasicThreadPool<Func_>&& to_move_) noexcept
		{
			constexpr bool finish_tasks_before_moving = false;
			constexpr bool help_with_tasks_if_finishing_before_moving = true;

			// Close the moved pool's threads before moving on (we don't want any dangling references)
			to_move_.Close<finish_tasks_before_moving, help_with_tasks_if_finishing_before_moving>();

			// Transfer moved pool's remaining queue data to the end of this queue
			// --- Lock both queues to ensure nothing new is added before merge is finished
			std::lock_guard<std::mutex> moved_task_queue_lock(to_move_._mutex_for_task_queue);
			if (to_move_._task_queue.size() > 0)
			{
				std::lock_guard<std::mutex> own_task_queue_lock(_mutex_for_task_queue);
				std::move(to_move_._task_queue.begin(), to_move_._task_queue.end(), std::back_inserter(_task_queue));
				to_move_._task_queue.clear();
			}
		}

		inline void _launch_threads()
		{
			_worker_threads.reserve(num_worker_threads);
			for (std::size_t i = 0; i < num_worker_threads; ++i)
			{
				_worker_threads.emplace_back(thread_loop(*this));
			}
		}

		inline bool _execute_task()
		{
			// False warnings - MSVC doesn't properly tell that control is correctly handled for locks between functions here
			EMU_CORE_MSVC_PUSH_WARNING_STACK;
			EMU_CORE_MSVC_DISABLE_WARNING(26115);
			if (!_threads_closing)
			{
				std::unique_lock<std::mutex> task_queue_lock(_mutex_for_task_queue);
				if (_task_queue.size() > 0)
				{
					auto task = std::move(_task_queue.front());
					_task_queue.pop_front();
					task_queue_lock.unlock(); // Finished with queue; unlock so task doesn't consume bandwidth
					task();
					return true;
				}
			}
			return false;
			EMU_CORE_MSVC_POP_WARNING_STACK;
		}

		inline bool _execute_task(std::unique_lock<std::mutex>& prepared_task_queue_lock_)
		{
			// False warnings - MSVC doesn't properly tell that control is correctly handled for locks between functions here
			EMU_CORE_MSVC_PUSH_WARNING_STACK;
			EMU_CORE_MSVC_DISABLE_WARNING(26115);
			if (!_threads_closing)
			{
				if (_task_queue.size() > 0)
				{
					auto task = std::move(_task_queue.front());
					_task_queue.pop_front();
					prepared_task_queue_lock_.unlock(); // Finished with queue; unlock so task doesn't consume bandwidth
					task();
					return true;
				}
			}
			prepared_task_queue_lock_.unlock(); // Only reach this point if not already unlocked by task execution
			return false;
			EMU_CORE_MSVC_POP_WARNING_STACK;
		}

		inline void _close_threads()
		{
			_accepting_tasks = false;
			_threads_closing = true;

			if (_worker_threads.size() > 0)
			{
				for (auto& worker_thread : _worker_threads)
				{
					worker_thread.join();
				}

				// Release memory for worker threads so we don't try to join again on future closes
				// --- We do this for cases such as where a use manually calls Close before destruction
				std::vector<std::thread>().swap(_worker_threads);
			}
		}

		bool _threads_closing;
		bool _accepting_tasks;
		std::atomic<std::size_t> _num_merges_in_progress;
		std::atomic<std::size_t> _tasks_currently_being_added;
		std::deque<task_or_packaged_task_type> _task_queue;
		std::mutex _mutex_for_task_queue;
		std::vector<std::thread> _worker_threads;
	};
}

#endif
