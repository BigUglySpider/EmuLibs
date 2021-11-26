#ifndef EMU_THREADS_THREAD_POOL_TMP_H_INC_
#define EMU_THREADS_THREAD_POOL_TMP_H_INC_ 1

#include "BindTMP.h"
#include <type_traits>

namespace EmuThreads::TMP
{
	template<class WorkAllocator_, typename = void>
	struct work_allocator_priority_type
	{
		using type = std::false_type;
	};
	template<class WorkAllocator_>
	struct work_allocator_priority_type<WorkAllocator_, std::void_t<typename WorkAllocator_::priority_type>>
	{
		using type = typename WorkAllocator_::priority_type;
	};

	template<class ThreadAllocator_, typename = void>
	struct thread_allocator_size_type
	{
		using type = std::false_type;
	};
	template<class ThreadAllocator_>
	struct thread_allocator_size_type<ThreadAllocator_, std::void_t<typename ThreadAllocator_::size_type>>
	{
		using type = typename ThreadAllocator_::size_type;
	};

	template<class WorkAllocator_>
	[[nodiscard]] constexpr inline bool work_allocator_has_priority()
	{
		return !std::is_same_v
		<
			typename work_allocator_priority_type<WorkAllocator_>::type,
			std::false_type
		>;
	}

	template<class WorkAllocator_, typename = void>
	struct has_activate_member_func
	{
		static constexpr bool value = false;
	};
	template<class WorkAllocator_>
	struct has_activate_member_func<WorkAllocator_, std::void_t<decltype(std::declval<WorkAllocator_>().Activate())>>
	{
		static constexpr bool value = true;
	};

	template<class WorkAllocator_, typename = void>
	struct has_deactivate_member_func
	{
		static constexpr bool value = false;
	};
	template<class WorkAllocator_>
	struct has_deactivate_member_func<WorkAllocator_, std::void_t<decltype(std::declval<WorkAllocator_>().Deactivate())>>
	{
		static constexpr bool value = true;
	};

	template<class WorkAllocator_, class Thread_, typename = void>
	struct has_launch_thread_template_member_func
	{
		static constexpr bool value = false;
	};
	template<class WorkAllocator_, class Thread_>
	struct has_launch_thread_template_member_func<WorkAllocator_, Thread_, std::void_t<decltype(std::declval<WorkAllocator_>().template LaunchThread<Thread_>())>>
	{
		static constexpr bool value = true;
	};

	template<class ThreadAllocator_, typename = void>
	struct has_join_all_member_func
	{
		static constexpr bool value = false;
	};
	template<class ThreadAllocator_>
	struct has_join_all_member_func<ThreadAllocator_, std::void_t<decltype(std::declval<ThreadAllocator_>().JoinAll())>>
	{
		static constexpr bool value = true;
	};

	template<class ThreadAllocator_, class SizeType_, typename = void>
	struct has_prepare_to_allocate_member_func
	{
		static constexpr bool value = false;
	};
	template<class ThreadAllocator_, class SizeType_>
	struct has_prepare_to_allocate_member_func<ThreadAllocator_, SizeType_, std::void_t<decltype(std::declval<ThreadAllocator_>().PrepareToAllocate(std::declval<SizeType_>()))>>
	{
		static constexpr bool value = true;
	};

	template<class Allocator_, class SizeType_, class Launcher_, typename = void>
	struct has_allocate_member_func
	{
		static constexpr bool value = false;
	};
	template<class Allocator_, class SizeType_, class Launcher_>
	struct has_allocate_member_func
	<
		Allocator_,
		SizeType_,
		Launcher_,
		std::void_t<decltype(std::declval<Allocator_>().Allocate(std::declval<Launcher_>(), std::declval<SizeType_>()))>
	>
	{
		static constexpr bool value = true;
	};

	template<class Item_, typename = void>
	struct has_num_threads_member_func
	{
		static constexpr bool value = false;
	};
	template<class Item_>
	struct has_num_threads_member_func<Item_, std::void_t<decltype(std::declval<Item_>().NumThreads())>>
	{
		static constexpr bool value = true;
	};

	template<class Allocator_, typename = void>
	struct has_deallocate_all_member_func
	{
		static constexpr bool value = false;
	};
	template<class Allocator_>
	struct has_deallocate_all_member_func<Allocator_, std::void_t<decltype(std::declval<Allocator_>().DeallocateAll())>>
	{
		static constexpr bool value = true;
	};

	template<class Item_, typename = void>
	struct has_size_type_alias
	{
		static constexpr bool value = false;
	};
	template<class Item_>
	struct has_size_type_alias<Item_, std::void_t<typename Item_::size_type>>
	{
		static constexpr bool value = true;
	};

	template<class Item_, class DesiredOutputType_, typename = void>
	struct has_const_waiting_time_ms_member_func
	{
		static constexpr bool value = false;
	};
	template<class Item_, class DesiredOutputType_>
	struct has_const_waiting_time_ms_member_func<Item_, DesiredOutputType_, std::void_t<decltype(std::declval<const Item_>().WaitingTimeMs())>>
	{
		static constexpr bool value = std::is_convertible_v<decltype(std::declval<const Item_>().WaitingTimeMs()), DesiredOutputType_>;
	};

	template<class Item_, class InputType_, typename = void>
	struct has_modifying_waiting_time_ms_member_func
	{
		static constexpr bool value = false;
	};
	template<class Item_, class InputType_>
	struct has_modifying_waiting_time_ms_member_func<Item_, InputType_, std::void_t<decltype(std::declval<Item_>().WaitingTimeMs(std::declval<InputType_>()))>>
	{
		static constexpr bool value = true;
	};

	template<class Item_, class DesiredOutputType_, typename = void>
	struct has_const_waiting_time_us_member_func
	{
		static constexpr bool value = false;
	};
	template<class Item_, class DesiredOutputType_>
	struct has_const_waiting_time_us_member_func<Item_, DesiredOutputType_, std::void_t<decltype(std::declval<const Item_>().WaitingTimeUs())>>
	{
		static constexpr bool value = std::is_convertible_v<decltype(std::declval<const Item_>().WaitingTimeUs()), DesiredOutputType_>;
	};

	template<class Item_, class InputType_, typename = void>
	struct has_modifying_waiting_time_us_member_func
	{
		static constexpr bool value = false;
	};
	template<class Item_, class InputType_>
	struct has_modifying_waiting_time_us_member_func<Item_, InputType_, std::void_t<decltype(std::declval<Item_>().WaitingTimeUs(std::declval<InputType_>()))>>
	{
		static constexpr bool value = true;
	};

	template<class ThreadAllocator_, class Launcher_, bool DoAssertion_>
	[[nodiscard]] constexpr inline bool is_valid_thread_allocator_for_thread_pool()
	{
		if constexpr (has_size_type_alias<ThreadAllocator_>::value)
		{
			using size_type = typename ThreadAllocator_::size_type;
			if constexpr (has_prepare_to_allocate_member_func<ThreadAllocator_, size_type>::value)
			{
				if constexpr (has_allocate_member_func<ThreadAllocator_, size_type, Launcher_>::value)
				{
					if constexpr (has_deallocate_all_member_func<ThreadAllocator_>::value)
					{
						if constexpr (has_join_all_member_func<ThreadAllocator_>::value)
						{
							if constexpr (has_num_threads_member_func<ThreadAllocator_>::value)
							{
								return true;
							}
							else
							{
								static_assert(!DoAssertion_, "Assertion failed for an EmuThreads::ThreadPool Thread Allocator: A Thread Allocator must have a public `NumThreads` member function.");
								return false;
							}
						}
						else
						{
							static_assert(!DoAssertion_, "Assertion failed for an EmuThreads::ThreadPool Thread Allocator: A Thread Allocator must have a public `JoinAll` member function.");
							return false;
						}
					}
					else
					{
						static_assert(!DoAssertion_, "Assertion failed for an EmuThreads::ThreadPool Thread Allocator: A Thread Allocator must have a public `DeallocateAll` member function.");
						return false;
					}
				}
				else
				{
					static_assert(!DoAssertion_, "Assertion failed for an EmuThreads::ThreadPool Thread Allocator: A Thread Allocator must have a public `Allocate(Launcher_, size_type)` member function, which takes a thread Launcher_ and the allocator's size_type as an argument. The thread Launcher_ is typically a functor which is called with no arguments, and returns the stored thread type for the allocator.");
					return false;
				}
			}
			else
			{
				static_assert(!DoAssertion_, "Assertion failed for an EmuThreads::ThreadPool Thread Allocator: A Thread Allocator must have a public `PrepareToAllocate(size_type)` member function, which takes its size_type as an argument.");
				return false;
			}
		}
		else
		{
			static_assert(!DoAssertion_, "Assertion failed for an EmuThreads::ThreadPool Thread Allocator: A Thread Allocator must have a public alias `size_type`.");
			return false;
		}
	}

	/// <summary>
	/// <para> Function which may be used to check if a functor type is valid for an EmuThreads::ThreadPool instance's WorkAllocator_ with the provided Thread_ type. </para>
	/// <para> Note that this is only guaranteed to expand to the generic, unspecialised EmuThreads::ThreadPool template. </para>
	/// <para> May optionally contain assertions. Static assertions will be performed if necessary when DoAssertion_ is false. </para>
	/// </summary>
	template<class WorkAllocator_, class Thread_, bool DoAssertion_>
	[[nodiscard]] constexpr inline bool is_valid_work_allocator_for_thread_pool()
	{
		if constexpr (has_activate_member_func<WorkAllocator_>::value)
		{
			if constexpr (has_deactivate_member_func<WorkAllocator_>::value)
			{
				if constexpr (has_launch_thread_template_member_func<WorkAllocator_, Thread_>::value)
				{
					using return_type = decltype(std::declval<WorkAllocator_>().template LaunchThread<std::thread>());
					if constexpr (std::is_same_v<return_type, Thread_>)
					{
						if constexpr
						(
							has_const_waiting_time_ms_member_func<WorkAllocator_, double>::value ||
							has_const_waiting_time_us_member_func<WorkAllocator_, double>::value
						)
						{
							if constexpr
							(
								has_modifying_waiting_time_ms_member_func<WorkAllocator_, double>::value ||
								has_modifying_waiting_time_us_member_func<WorkAllocator_, double>::value
							)
							{
								return true;
							}
							else
							{
								static_assert(!DoAssertion_, "Assertion failed for an EmuThreads::ThreadPool Work Allocator: A Work Allocator must have a public `WaitingTimeMs` and/or `WaitingTimeUs` member function which takes a `double` argument.");
								return false;
							}
						}
						else
						{
							static_assert(!DoAssertion_, "Assertion failed for an EmuThreads::ThreadPool Work Allocator: A Work Allocator must have a public constant `WaitingTimeMs` and/or `WaitingTimeUs` member function which returns a type of or static_cast-able to `double`.");
							return false;
						}
					}
					else
					{
						static_assert(!DoAssertion_, "Assertion failed for an EmuThreads::ThreadPool Work Allocator: A Work Allocator's `LaunchThread<Thread_>()` function must return a newly constructed Thread_.");
						return false;
					}
				}
				else
				{
					static_assert(!DoAssertion_, "Assertion failed for an EmuThreads::ThreadPool Work Allocator: A Work Allocator must have a public `LaunchThread<Thread_>()` template member function.");
					return false;
				}
			}
			else
			{
				static_assert(!DoAssertion_, "Assertion failed for an EmuThreads::ThreadPool Work Allocator: A Work Allocator must have a public `Deactivate()` member function.");
				return false;
			}
		}
		else
		{
			static_assert(!DoAssertion_, "Assertion failed for an EmuThreads::ThreadPool Work Allocator: A Work Allocator must have a public `Activate()` member function.");
			return false;
		}
	}

	template<class T_, typename Out_, typename = void>
	struct has_static_default_priority_func
	{
		static constexpr bool value = false;
	};
	template<class T_, typename Out_>
	struct has_static_default_priority_func<T_, Out_, std::void_t<std::invoke_result_t<decltype(T_::default_priority)>>>
	{
	private:
		using return_type = typename std::invoke_result<decltype(T_::default_priority)>::type;

	public:
		static constexpr bool return_matches_out = std::is_same_v<return_type, Out_>;
		static constexpr bool value = return_matches_out || std::is_convertible_v<return_type, Out_>;
	};
}

#endif
