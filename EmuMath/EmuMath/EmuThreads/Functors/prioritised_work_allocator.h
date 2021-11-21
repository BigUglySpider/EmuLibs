#ifndef EMU_THREADS_FUNCTORS_PRIORITISED_WORK_ALLOCATOR_H_INC_
#define EMU_THREADS_FUNCTORS_PRIORITISED_WORK_ALLOCATOR_H_INC_ 1

#include <atomic>
#include <chrono>
#include <functional>
#include <future>
#include <limits>
#include <map>
#include <mutex>
#include <queue>
#include <type_traits>
#include "default_work_allocator.h"
#include "../TMP/CommonThreadingAliases.h"

namespace EmuThreads::Functors
{
	/// <summary>
	/// <para> </para>
	/// </summary>
	/// <typeparam name="PriorityType_"></typeparam>
	template<class PriorityType_ = EmuThreads::TMP::default_priority_type>
	class prioritised_work_allocator
	{
	public:
		using priority_type = PriorityType_;
		using this_type = prioritised_work_allocator<priority_type>;

		/// <summary>
		/// <para> The default priority level applied to tasks if no custom priority is provided. </para>
		/// <para> For signed arithmetic types, this will be 0. </para>
		/// <para> For unsigned arithmetic types, this will be its maximum value / 2. </para>
		/// <para> For any other types, this will be a default constructed priority_type. </para>
		/// </summary>
		[[nodiscard]] static constexpr priority_type default_priority()
		{
			if constexpr (std::is_arithmetic_v<priority_type>)
			{
				if constexpr (std::is_signed_v<priority_type>)
				{
					return priority_type(0);
				}
				else
				{
					// Make constexpr intermediate result to guarantee that this division is avoided at runtime
					constexpr priority_type half_point_ = std::numeric_limits<priority_type>::max() / priority_type(2);
					return half_point_;
				}
			}
			else
			{
				return priority_type();
			}
		}

		/// <summary> The waiting time (in milliseconds) used when no other time is provided. </summary>
		static constexpr double default_waiting_time_ms = default_work_allocator::default_waiting_time_ms;
		/// <summary> Minimum waiting time (in milliseconds) that may be used in this allocator's downtime. </summary>
		static constexpr double min_waiting_time_ms = default_work_allocator::min_waiting_time_ms;
		/// <summary> Maximum waiting time (in milliseconds) that may be used in this allocator's downtime. </summary>
		static constexpr double max_waiting_time_ms = default_work_allocator::max_waiting_time_ms;

		/// <summary> Helper to reduce verbosity when creating a duration in milliseconds. The passed time value is not validated. </summary>
		/// <param name="time_in_ms_">Number of milliseconds to use for creating the resulting duration.</param>
		/// <returns>Chrono duration in milliseconds, with `double` representation, using the provided time_in_ms_. </returns>
		template<typename InNum_>
		[[nodiscard]] static constexpr inline std::chrono::duration<double, std::milli> time_in_ms(const InNum_& time_in_ms_)
		{
			return default_work_allocator::time_in_ms(time_in_ms_);
		}

		/// <summary> Creates a version of the passed waiting_time_ms_ which is valid for use with this allocator. </summary>
		/// <param name="waiting_time_ms_">Waiting time to validate.</param>
		/// <returns>The passed waiting_time_ms_ value clamped into the inclusive range min_waiting_time_ms:max_waiting_time_ms.</returns>
		[[nodiscard]] static constexpr inline double validate_waiting_time_ms(double waiting_time_ms_)
		{
			return default_work_allocator::validate_waiting_time_ms(waiting_time_ms_);
		}

		prioritised_work_allocator() :
			is_active(true),
			work_queues(),
			queues_mutex(),
			working_thread_count(0),
			waiting_time_ms(default_waiting_time_ms)
		{
		}

		prioritised_work_allocator(double waiting_time_ms_) :
			is_active(true),
			work_queues(),
			queues_mutex(),
			working_thread_count(0),
			waiting_time_ms(validate_waiting_time_ms(waiting_time_ms_))
		{
		}

		inline prioritised_work_allocator(this_type&& to_move_, double waiting_time_ms_) noexcept :
			is_active(true),
			work_queues(),
			queues_mutex(),
			working_thread_count(0),
			waiting_time_ms(validate_waiting_time_ms(waiting_time_ms_))
		{
			std::lock_guard<mutex_type> lock_(to_move_.queues_mutex);
			work_queues.swap(to_move_.work_queues);
			to_move_.num_queued_tasks = 0;
		}
		inline prioritised_work_allocator(this_type&& to_move_) noexcept : prioritised_work_allocator(std::forward<this_type>(to_move_), to_move_.waiting_time_ms)
		{
		}

		prioritised_work_allocator(const this_type&) = delete;

		inline ~prioritised_work_allocator()
		{
			Deactivate();
			ClearAllQueues();
			WaitForAllTasksToComplete();
		}

		template<class Thread_>
		[[nodiscard]] inline Thread_ LaunchThread()
		{
			return Thread_(&this_type::_worker_execution, this);
		}

		inline void ClearAllQueues()
		{
			std::lock_guard<mutex_type> lock_(queues_mutex);
			decltype(work_queues)().swap(work_queues);
		}

		[[nodiscard]] inline bool HasWork() const
		{
			return num_queued_tasks != 0;
		}

		[[nodiscard]] inline std::size_t NumWorkingThreads() const
		{
			return working_thread_count;
		}

		[[nodiscard]] inline bool IsActive() const
		{
			return is_active;
		}

		[[nodiscard]] inline std::size_t NumQueuedTasks() const
		{
			return num_queued_tasks;
		}

		inline void WaitForAllTasksToCompleteNoJoin() const
		{
			if (HasWork())
			{
				auto wait_ = time_in_ms(waiting_time_ms);
				do
				{
					std::this_thread::sleep_for(wait_);
				} while (HasWork());
			}
		}

		inline void WaitForAllTasksToComplete()
		{
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

		[[nodiscard]] inline double WaitingTimeMs() const
		{
			return waiting_time_ms;
		}
		inline double WaitingTimeMs(double waiting_time_ms_)
		{
			waiting_time_ms = validate_waiting_time_ms(waiting_time_ms_);
			return waiting_time_ms;
		}

		inline void Activate()
		{
			is_active = true;
		}

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

				std::unique_lock<mutex_type> lock_(queues_mutex);
				work_queue_type& work_queue = _get_work_queue(default_priority());
				work_queue.emplace([=]() { (*wrapped_func_)(args_...); });
				lock_.unlock();
				++num_queued_tasks;
				return wrapped_func_->get_future();
			}
			else
			{
				static_assert(false, "Attempted to allocate a task via EmuThreading::Functors::prioritised_work_allocator, but the provided Func_ type cannot be invoked with the provided Args_.");
			}
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
		inline auto AllocateTask(const priority_type& priority_, Func_ func_, Args_...args_)->std::future<decltype(func_(args_...))>
		{
			if constexpr (std::is_invocable_v<Func_, Args_...>)
			{
				auto wrapped_func_ = std::make_shared<std::packaged_task<decltype(func_(args_...))(Args_...)>>(func_);

				std::unique_lock<mutex_type> lock_(queues_mutex);
				work_queue_type& work_queue = _get_work_queue(priority_);
				work_queue.emplace([=]() { (*wrapped_func_)(args_...); });
				lock_.unlock();
				++num_queued_tasks;
				return wrapped_func_->get_future();
			}
			else
			{
				static_assert(false, "Attempted to allocate a task via EmuThreading::Functors::prioritised_work_allocator, but the provided Func_ type cannot be invoked with the provided Args_.");
			}
		}

	private:
		using work_type = std::function<void()>;
		using work_queue_type = std::queue<work_type>;
		using priority_queue_type = std::map<priority_type, work_queue_type>;
		using mutex_type = std::mutex;

		std::atomic_bool is_active;
		std::atomic_size_t working_thread_count;
		std::atomic_size_t num_queued_tasks;
		mutex_type queues_mutex;
		priority_queue_type work_queues;
		double waiting_time_ms;

		[[nodiscard]] inline work_queue_type& _get_work_queue(const priority_type& priority_)
		{
			return work_queues[priority_];
		}
		[[nodiscard]] inline const work_queue_type& _get_work_queue(const priority_type& priority_) const
		{
			return work_queues[priority_];
		}

		inline void _worker_execution()
		{
			while (is_active)
			{
				_look_for_work();
			}
		}

		inline void _look_for_work()
		{
			std::unique_lock<mutex_type> lock_(queues_mutex);
			if (is_active && num_queued_tasks != 0)
			{
				work_type next_task_ = std::move(_pop_next_task());
				lock_.unlock();

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
			// Access the queue appearing first in the sorted collection of priority queues
			auto queue_iterator_ = work_queues.begin();
			auto& queue_ = queue_iterator_->second;

			// Pop queue and erase it from the priority collection if this is its last task
			work_type out_task_ = std::move(queue_.front());
			queue_.pop();
			--num_queued_tasks;
			if (queue_.size() == 0)
			{
				work_queues.erase(queue_iterator_);
			}
			return out_task_;
		}
	};
}

#endif
