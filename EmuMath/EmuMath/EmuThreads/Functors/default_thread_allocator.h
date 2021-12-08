#ifndef EMU_THREADS_FUNCTORS_DEFAULT_THREAD_ALLOCATOR_H_INC_
#define EMU_THREADS_FUNCTORS_DEFAULT_THREAD_ALLOCATOR_H_INC_ 1

#include <limits>
#include <vector>
#include "../../EmuCore/Functors/Arithmetic.h"

namespace EmuThreads::Functors
{
	template<class ThreadType_>
	class default_thread_allocator
	{
	public:
		using thread_type = ThreadType_;
		using this_type = default_thread_allocator<thread_type>;
		using size_type = std::size_t;

		static constexpr size_type min_num_threads = 0;
		static constexpr size_type max_num_threads = std::numeric_limits<size_type>::max();
		
		[[nodiscard]] static constexpr inline size_type validate_num_threads(size_type num_threads_)
		{
			return EmuCore::do_clamp<size_type>()(num_threads_, min_num_threads, max_num_threads);
		}

		default_thread_allocator() : num_threads(0), threads()
		{
		}
		default_thread_allocator(this_type&& to_move_) = delete;
		default_thread_allocator(const this_type& to_copy_) = delete;

		inline void JoinAll()
		{
			for (auto& thread_ : threads)
			{
				thread_.join();
			}
		}

		inline void DeallocateAll()
		{
			JoinAll();
			_clear_threads();
		}


		inline void PrepareToAllocate(size_type target_num_threads_)
		{
			target_num_threads_ = validate_num_threads(target_num_threads_);

			// No need to do anything if the validated count == current count
			if (target_num_threads_ != num_threads)
			{
				if (target_num_threads_ < num_threads)
				{
					DeallocateAll();
				}
			}
		}

		template<class Launcher_, typename LauncherMustReturnThreadType_ = std::enable_if_t<std::is_invocable_r_v<thread_type, Launcher_>>>
		inline void Allocate(Launcher_ launcher_, size_type target_num_threads_)
		{
			_do_allocation(launcher_, validate_num_threads(target_num_threads_));
		}

		[[nodiscard]] inline size_type NumThreads() const
		{
			return num_threads;
		}

	private:
		using thread_storage_type = std::vector<thread_type>;

		inline void _clear_threads()
		{
			num_threads = 0;
			thread_storage_type().swap(threads);
		}

		template<class Launcher_, typename LauncherMustReturnThreadType_ = std::enable_if_t<std::is_invocable_r_v<thread_type, Launcher_>>>
		inline void _do_allocation(Launcher_& launcher_, size_type target_num_threads_validated_)
		{
			threads.reserve(target_num_threads_validated_);
			for (size_type i = num_threads; i < target_num_threads_validated_; ++i)
			{
				threads.emplace_back(std::move(launcher_()));
				++num_threads;
			}
		}

		thread_storage_type threads;
		size_type num_threads;
	};
}

#endif
