#ifndef EMU_THREADS_PARALLEL_FOR_H_INC_
#define EMU_THREADS_PARALLEL_FOR_H_INC_ 1

#include <functional>
#include <type_traits>
#include "../EmuCore/TMPHelpers/TypeComparators.h"
#include "../EmuCore/TMPHelpers/TypeConvertors.h"
#include "../EmuCore/TMPHelpers/Values.h"
#include "ThreadPool.h"
#include "Functors/ParallelLoopFunctors/default_parallel_loop_custom_incrementer.h"
#include "Functors/ParallelLoopFunctors/default_parallel_loop_incrementer.h"
#include "Functors/ParallelLoopFunctors/default_parallel_loop_iteration_allocator.h"
#include "TMP/BindTMP.h"
#include <tuple>

namespace EmuThreads
{
	/// <summary>
	/// <para> Functor for performing a for-loop of arbitrary depth which invokes the provided Func_ with provided iterators, executed via a thread pool. </para>
	/// <para> This is not intended to make an individual loop faster, but to allow it to be executed in parallel to the main thread's execution. </para>
	/// <para> Task allocation may still take a significant sum of time, although this may be alleviated with built-in async execution. </para>
	/// </summary>
	template
	<
		class Func_,
		class ThreadPool_ = EmuThreads::DefaultThreadPool,
		class IterationAllocator_ = EmuThreads::Functors::default_parallel_loop_iteration_allocator<std::remove_pointer_t<ThreadPool_>>
	>
	class ParallelFor
	{
	private:
		template<class Iterator_>
		struct _non_reference_iterator
		{
			using type = EmuCore::TMP::remove_ref_cv_t<Iterator_>;
		};
		template<class Iterator_>
		struct _non_reference_iterator<std::reference_wrapper<Iterator_>>
		{
			using type = std::remove_cv_t<Iterator_>;
		};

		template<class Iterator_, class Comparator_, class Incrementer_>
		struct _async_execution
		{
			using iterator_arg = typename EmuThreads::TMP::_suitable_bind_arg_return<Iterator_>::type;
			using comparator_arg = typename EmuThreads::TMP::_suitable_bind_arg_return<Comparator_>::type;
			using incrementer_arg = typename EmuThreads::TMP::_suitable_bind_arg_return<Incrementer_>::type;

			constexpr _async_execution()
			{
			}

			constexpr inline std::future<void> operator()
			(
				ParallelFor<Func_, ThreadPool_, IterationAllocator_>* this_ptr_,
				iterator_arg begin_,
				iterator_arg end_,
				comparator_arg cmp_,
				incrementer_arg incrementer_
			) const
			{
				return std::async
				(
					std::bind
					(
						&ParallelFor<Func_, ThreadPool_, IterationAllocator_>::template Execute<Iterator_, Comparator_, Incrementer_>,
						this_ptr_,
						EmuThreads::TMP::get_suitable_bind_arg<iterator_arg>(begin_),
						EmuThreads::TMP::get_suitable_bind_arg<iterator_arg>(end_),
						EmuThreads::TMP::get_suitable_bind_arg<comparator_arg>(cmp_),
						EmuThreads::TMP::get_suitable_bind_arg<incrementer_arg>(incrementer_)
					)
				);
			}
		};

	public:
		using this_type = ParallelFor<Func_, ThreadPool_, IterationAllocator_>;
		using thread_pool_type = std::remove_pointer_t<std::remove_reference_t<ThreadPool_>>;
		using stored_thread_pool_type = std::conditional_t
		<
			std::is_reference_v<ThreadPool_>, 
			std::reference_wrapper<std::remove_reference_t<ThreadPool_>>,
			ThreadPool_
		>;
		using function_type = Func_;
		using iteration_allocator_type = IterationAllocator_;

#pragma region CONSTRUCTORS
		template
		<
			class...ThreadPoolConstructionParams_,
			typename = std::enable_if_t<std::is_constructible_v<stored_thread_pool_type, ThreadPoolConstructionParams_...>>
		>
		explicit ParallelFor(ThreadPoolConstructionParams_&&...thread_pool_construction_params_) :
			thread_pool(thread_pool_construction_params_...),
			iteration_allocator(),
			func_unsynced()
		{
		}

		template
		<
			class...ThreadPoolConstructionParams_,
			typename = std::enable_if_t<std::is_constructible_v<stored_thread_pool_type, ThreadPoolConstructionParams_...> && std::is_copy_constructible_v<function_type>>
		>
		explicit ParallelFor(const Func_& func_to_copy_, ThreadPoolConstructionParams_&&...thread_pool_construction_params_) :
			thread_pool(thread_pool_construction_params_...),
			iteration_allocator(),
			func_unsynced(func_to_copy_)
		{
		}

		template
		<
			class...ThreadPoolConstructionParams_,
			typename = std::enable_if_t<std::is_constructible_v<stored_thread_pool_type, ThreadPoolConstructionParams_...> && std::is_move_constructible_v<function_type>>
		>
		explicit ParallelFor(Func_&& func_to_move_, ThreadPoolConstructionParams_&&...thread_pool_construction_params_) :
			thread_pool(thread_pool_construction_params_...),
			iteration_allocator(),
			func_unsynced(func_to_move_)
		{
		}

		ParallelFor() = delete;
		ParallelFor(this_type&&) = delete;
		ParallelFor(const this_type&) = delete;
#pragma endregion

#pragma region THREAD_POOL_ACCESS
		/// <summary> Provides constant access to this ParallelFor's underlying thread pool. </summary>
		[[nodiscard]] const thread_pool_type& ViewThreadPool() const
		{
			return _get_thread_pool();
		}

		/// <summary> Allocates the provided target number of worker threads to this parallel for's underlying thread pool. </summary>
		inline void AllocateWorkers(std::size_t target_num_threads_)
		{
			_get_thread_pool().AllocateWorkers(target_num_threads_);
		}

		/// <summary> Sets the waiting time (in milliseconds_ that pooled threads will wait for when idle there there are no iterations to execute. </summary>
		inline void ThreadWaitingTimeMs(double waiting_time_ms_)
		{
			_get_thread_pool().WaitingTimeMs(waiting_time_ms_);
		}
		/// <summary> Provides the waiting time (in milliseconds) that pooled threads will wait for when idle if there are no iterations to execute. </summary>
		/// <returns>Double representing the time (in milliseconds) that underlying pooled threads will wait for when idle.</returns>
		[[nodiscard]] inline double ThreadWaitingTimeMs() const
		{
			return _get_thread_pool().WaitingTimeMs();
		}
#pragma endregion

#pragma region LOOP_EXECUTION
		/// <summary>
		/// <para> Executes a parallel for loop using the provided begin_ and end_ iterators. </para>
		/// <para> Dimensions of the loop may scale infinitely using tuple arguments. </para>
		/// <para> 
		///		If an argument is the same throughout (e.g. all comparisons use the same functor), 
		///		that argument may be a single non-tuple even if tuple iterators are provided. 
		/// </para>
		/// <para> This function only allocates iterations to the thread pool; the return of control to the calling thread does not indicate completion of the loop. </para>
		/// </summary>
		/// <typeparam name="Iterator_">Single type of iterator or tuple of iterators for loop iterations to work with.</typeparam>
		/// <typeparam name="Comparator_">Single type of comparator or tuple of comparators to determine if loop iterations should continue.</typeparam>
		/// <typeparam name="Incrementer_">Single type of incrementer or tuple of incrementers to use for modifying an iterator after a loop iteration.</typeparam>
		/// <param name="begin_">Value or tuple of values at which iterators should begin at. Shares its type with end_.</param>
		/// <param name="end_">Value or tuple of values at which iterators should end at. Shares its type with begin_.</param>
		/// <param name="cmp_">Function or tuple of functions (or functors) to use to determine if a loop iteration should execute.</param>
		/// <param name="incrementer_">Function or tuple of functions (or functors) to increment an iterator per iteration of a loop.</param>
		template<class Iterator_, class Comparator_ = std::less<void>, class Incrementer_ = EmuThreads::Functors::default_parallel_loop_incrementer>
		inline void Execute(Iterator_ begin_, Iterator_ end_, Comparator_ cmp_ = Comparator_(), Incrementer_ incrementer_ = Incrementer_())
		{
			typename _non_reference_iterator<Iterator_>::type iterator_(begin_);

			if constexpr (_is_tuple<Iterator_>())
			{
				constexpr std::size_t num_iterators_ = std::tuple_size_v<Iterator_>;
				if constexpr (num_iterators_ != 0)
				{
					if constexpr (_is_tuple<Comparator_>())
					{
						constexpr std::size_t num_comparators_ = std::tuple_size_v<Comparator_>;
						if constexpr (num_comparators_ == 1 || num_comparators_ == num_iterators_)
						{
							if constexpr (_is_tuple<Incrementer_>())
							{
								constexpr std::size_t num_incrementers_ = std::tuple_size_v<Incrementer_>;
								if constexpr (num_incrementers_ == 1 || num_incrementers_ == num_iterators_)
								{
									// All valid tuples
									_do_execution<0, num_iterators_, Iterator_&, Comparator_&, Incrementer_&>(iterator_, begin_, end_, cmp_, incrementer_, std::ref(func_unsynced));
								}
								else
								{
									static_assert(EmuCore::TMP::get_false<Iterator_>(), "Provided a tuple for all arguments (excluding Func_) for EmuThreads::ParallelFor::Execute, but the Incrementer_ tuple does not contain a number of types equal to 1 or the number of iterators. There must be 1 incrementer for all iterators, or 1 incrementer per iterator.");
								}
							}
							else
							{
								// TUPLES: Iterator_, Comparator_
								// SCALAR: Incrementer_
								_do_execution<0, num_iterators_, Iterator_&, Comparator_&, Incrementer_&>(iterator_, begin_, end_, cmp_, incrementer_, std::ref(func_unsynced));
							}
						}
						else
						{
							static_assert(EmuCore::TMP::get_false<Iterator_>(), "Provided a tuple as the Iterator_ and Comparator_ for EmuThreads::ParallelFor::Execute, but the Comparator_ tuple does not contain a number of types equal to 1 or the number of iterators. There must be 1 comparator for all iterators, or 1 comparator per iterator.");
						}
					}
					else
					{
						if constexpr (_is_tuple<Incrementer_>())
						{
							constexpr std::size_t num_incrementers_ = std::tuple_size_v<Incrementer_>;
							if constexpr (num_incrementers_ == 1 || num_incrementers_ == num_iterators_)
							{
								// TUPLES: Iterator_, Incrementer_
								// SCALAR: Comparator_
								_do_execution<0, num_iterators_, Iterator_&, Comparator_&, Incrementer_&>(iterator_, begin_, end_, cmp_, incrementer_, std::ref(func_unsynced));
							}
							else
							{
								static_assert(EmuCore::TMP::get_false<Iterator_>(), "Provided a tuple as the Iterator_ and Incrementer_ for EmuThreads::ParallelFor::Execute, but the Incrementer_ tuple does not contain a number of types equal to 1 or the number of iterators. There must be 1 incrementer for all iterators, or 1 incrementer per iterator.");
							}
						}
						else
						{
							// TUPLES: Iterator_
							// SCALAR: Comparator_, Incrementer_
							_do_execution<0, num_iterators_, Iterator_&, Comparator_&, Incrementer_&>(iterator_, begin_, end_, cmp_, incrementer_, std::ref(func_unsynced));
						}
					}
				}
				else
				{
					static_assert(EmuCore::TMP::get_false<Iterator_>(), "Provided a tuple as the Iterator_ for EmuThreads::ParallelFor::Execute with a size of 0. There must be at least one Iterator_. within a tuple of iterators");
				}
			}
			else
			{
				if constexpr (_is_tuple<Comparator_>())
				{
					constexpr std::size_t num_comparators_ = std::tuple_size_v<Comparator_>;
					if constexpr (num_comparators_ == 1)
					{
						if constexpr (_is_tuple<Incrementer_>())
						{
							constexpr std::size_t num_incrementers_ = std::tuple_size_v<Incrementer_>;
							if constexpr (num_incrementers_ == 1)
							{
								// TUPLES: Comparator_, Incrementer_
								// SCALAR: Iterator_
								_do_execution<0, 1, Iterator_&, Comparator_&, Incrementer_&>(iterator_, begin_, end_, cmp_, incrementer_, std::ref(func_unsynced));
							}
							else
							{
								static_assert(EmuCore::TMP::get_false<Iterator_>(), "Provided a tuple for Comparator_ and Incrementer_ with a non-tuple Iterator_ for EmuThreads::ParallelFor::Execute, but the size of the Incrementer_ tuple is not equal to 1. Non-tuple iterator arguments are interpreted as 1-dimensional loops, and thus require a single incrementer (which may or may not be contained within a tuple).");
							}
						}
						else
						{
							// TUPLES: Comparator_
							// SCALAR: Iterator_, Incrementer_
							_do_execution<0, 1, Iterator_&, Comparator_&, Incrementer_&>(iterator_, begin_, end_, cmp_, incrementer_, std::ref(func_unsynced));
						}
					}
					else
					{
						static_assert(EmuCore::TMP::get_false<Iterator_>(), "Provided a tuple for Comparator_ with a non-tuple Iterator_ for EmuThreads::ParallelFor::Execute, but the size of the Comparator_ tuple is not equal to 1. Non-tuple iterator arguments are interpreted as 1-dimensional loops, and thus require a single comparator (which may or nay not be contained within a tuple).");
					}
				}
				else
				{
					if constexpr (_is_tuple<Incrementer_>())
					{
						constexpr std::size_t num_incrementers_ = std::tuple_size_v<Incrementer_>;
						if constexpr (num_incrementers_ == 1)
						{
							_do_execution<0, 1, Iterator_&, Comparator_&, Incrementer_&>(iterator_, begin_, end_, cmp_, incrementer_, std::ref(func_unsynced));
						}
						else
						{
							static_assert(EmuCore::TMP::get_false<Iterator_>(), "Provided a tuple for Incrementer_ with a non-tuple Iterator_ for EmuThreads::ParallelFor::Execute, but the size of the Incrementer_ tuple is not equal to 1.  Non-tuple iterator arguments are interpreted as 1-dimensional loops, and thus require a single incrementer (which may or may not be contained within a tuple).");
						}
					}
					else
					{
						// All scalars
						_do_execution<0, 1, Iterator_&, Comparator_&, Incrementer_&>(iterator_, begin_, end_, cmp_, incrementer_, std::ref(func_unsynced));
					}
				}
			}
		}

		/// <summary>
		/// <para> Executes a parallel for loop using the provided begin_ and end_ iterators. </para>
		/// <para> Dimensions of the loop may scale infinitely using tuple arguments. </para>
		/// <para> 
		///		If an argument is the same throughout (e.g. all comparisons use the same functor), 
		///		that argument may be a single non-tuple even if tuple iterators are provided. 
		/// </para>
		/// <para> This function only allocates iterations to the thread pool; the return of control to the calling thread does not indicate completion of the loop. </para>
		/// <para> 
		///		Uses `EmuThreads::Functors::default_parallel_loop_custom_incrementer&lt;Increment_&gt; constructed with CustomIncrement_ as the incrementer. 
		///		This will be used as the increment for all dimensions within the full loop.
		/// </para>
		/// </summary>
		/// <typeparam name="Iterator_">Single type of iterator or tuple of iterators for loop iterations to work with.</typeparam>
		/// <typeparam name="Comparator_">Single type of comparator or tuple of comparators to determine if loop iterations should continue.</typeparam>
		/// <typeparam name="Incrementer_">Single type of incrementer or tuple of incrementers to use for modifying an iterator after a loop iteration.</typeparam>
		/// <param name="begin_">Value or tuple of values at which iterators should begin at. Shares its type with end_.</param>
		/// <param name="end_">Value or tuple of values at which iterators should end at. Shares its type with begin_.</param>
		/// <param name="cmp_">Function or tuple of functions (or functors) to use to determine if a loop iteration should execute.</param>
		template<class Increment_, Increment_ CustomIncrement_, class Iterator_, class Comparator_ = std::less<void>>
		inline void Execute(Iterator_ begin_, Iterator_ end_, Comparator_ cmp_ = Comparator_())
		{
			return Execute
			(
				EmuThreads::TMP::get_suitable_bind_arg<Iterator_>(begin_),
				EmuThreads::TMP::get_suitable_bind_arg<Iterator_>(end_),
				EmuThreads::TMP::get_suitable_bind_arg<Comparator_>(cmp_),
				EmuThreads::Functors::default_parallel_loop_custom_incrementer<Increment_>(CustomIncrement_)
			);
		}

		/// <summary>
		/// <para> Performs `Execute` with the same arguments asynchronously, allowing the calling thread to perform other tasks while iterations are allocated. </para>
		/// <para> Results of this function's execution upon completion are the same as `Execute` with the same arguments. </para>
		/// <para> Additional details regarding this function are mimicked by `Execute`, and may be found there. </para>
		/// <para> 
		///		Uses `EmuThreads::Functors::default_parallel_loop_custom_incrementer&lt;Increment_&gt; constructed with CustomIncrement_ as the incrementer. 
		///		This will be used as the increment for all dimensions within the full loop.
		/// </para>
		/// </summary>
		/// <param name="begin_">Value or tuple of values at which iterators should begin at. Shares its type with end_.</param>
		/// <param name="end_">Value or tuple of values at which iterators should end at. Shares its type with begin_.</param>
		/// <param name="cmp_">Function or tuple of functions (or functors) to use to determine if a loop iteration should execute.</param>
		/// <returns>
		///		Future for the allocation of loop iterations.
		///		This only indicates when loop iterations are allocated, and does not guarantee that they have all been executed.
		/// </returns>
		template<class Iterator_, class Comparator_ = std::less<void>, class Incrementer_ = EmuThreads::Functors::default_parallel_loop_incrementer>
		inline std::future<void> ExecuteAsync(Iterator_ begin_, Iterator_ end_, Comparator_ cmp_ = Comparator_(), Incrementer_ incrementer_ = Incrementer_())
		{
			return _async_execution<Iterator_, Comparator_, Incrementer_>()
			(
				this,
				EmuThreads::TMP::get_suitable_bind_arg<Iterator_>(begin_),
				EmuThreads::TMP::get_suitable_bind_arg<Iterator_>(end_),
				EmuThreads::TMP::get_suitable_bind_arg<Comparator_>(cmp_),
				EmuThreads::TMP::get_suitable_bind_arg<Incrementer_>(incrementer_)
			);
		}

		/// <summary>
		/// <para> Performs `Execute` with the same arguments asynchronously, allowing the calling thread to perform other tasks while iterations are allocated. </para>
		/// <para> Results of this function's execution upon completion are the same as `Execute` with the same arguments. </para>
		/// <para> Additional details regarding this function are mimicked by `Execute`, and may be found there. </para>
		/// </summary>
		/// <param name="begin_">Value or tuple of values at which iterators should begin at. Shares its type with end_.</param>
		/// <param name="end_">Value or tuple of values at which iterators should end at. Shares its type with begin_.</param>
		/// <param name="cmp_">Function or tuple of functions (or functors) to use to determine if a loop iteration should execute.</param>
		/// <param name="incrementer_">Function or tuple of functions (or functors) to increment an iterator per iteration of a loop.</param>
		/// <returns>
		///		Future for the allocation of loop iterations.
		///		This only indicates when loop iterations are allocated, and does not guarantee that they have all been executed.
		/// </returns>
		template<class Increment_, Increment_ CustomIncrement_, class Iterator_, class Comparator_ = std::less<void>>
		inline std::future<void> ExecuteAsync(Iterator_ begin_, Iterator_ end_, Comparator_ cmp_ = Comparator_())
		{
			using incrementer_type = EmuThreads::Functors::default_parallel_loop_custom_incrementer<Increment_>;
			incrementer_type incrementer_ = incrementer_type(CustomIncrement_);
			return _async_execution<Iterator_, Comparator_, incrementer_type>()
			(
				this,
				EmuThreads::TMP::get_suitable_bind_arg<Iterator_>(begin_),
				EmuThreads::TMP::get_suitable_bind_arg<Iterator_>(end_),
				EmuThreads::TMP::get_suitable_bind_arg<Comparator_>(cmp_),
				EmuThreads::TMP::get_suitable_bind_arg<incrementer_type>(incrementer_)
			);
		}
#pragma endregion

		/// <summary>
		/// <para> The underlying function performed whenever this ParallelFor is executed. </para>
		/// <para> This is publicly visible to allow for easy modifications to state and access to results, but there is no enforced thread safety. </para>
		/// <para> It is the user's responsibility to ensure that changes made to this do not interfere currently executing loops. </para>
		/// </summary>
		function_type func_unsynced;

	private:
		template<std::size_t Index_, class Item_>
		struct _item_get_result
		{
			using type = Item_&;
		};
		template<std::size_t Index_, class...TupleArgs_>
		struct _item_get_result<Index_, std::tuple<TupleArgs_...>>
		{
			using std::get;
			static_assert(Index_ < sizeof...(TupleArgs_), "Attempted to get an invalid index within an EmuThreads::ParallelFor's underlying execution. This is an internal EmuThreads error.");
			using type = decltype(get<Index_>(std::declval<std::tuple<TupleArgs_...>>()))&;
		};

		template<std::size_t Index_, class Item_>
		[[nodiscard]] static constexpr inline typename _item_get_result<Index_, Item_>::type _item_get(Item_& item_)
		{
			if constexpr (_is_tuple<Item_>())
			{
				using std::get;
				return get<Index_>(item_);
			}
			else
			{
				return item_;
			}
		}

		template<std::size_t Index_, std::size_t End_, class Iterator_, class Comparator_, class Incrementer_, class FuncRef_>
		inline void _do_execution
		(
			typename _non_reference_iterator<Iterator_>::type iterator_,
			Iterator_ begin_,
			Iterator_ end_,
			Comparator_ cmp_,
			Incrementer_ incrementer_,
			FuncRef_ funcRef_
		)
		{
			auto& current_iterator_ = _item_get<Index_>(iterator_);
			auto& current_end_ = _item_get<Index_>(end_);
			auto& current_cmp_ = _item_get<Index_>(cmp_);
			auto& current_incrementer_ = _item_get<Index_>(incrementer_);

			for (current_iterator_ = _item_get<Index_>(begin_); current_cmp_(current_iterator_, current_end_); current_incrementer_(current_iterator_))
			{
				if constexpr ((Index_ + 1) < End_)
				{
					// Further loops embedded...
					_do_execution<Index_ + 1, End_>(iterator_, begin_, end_, cmp_, incrementer_, funcRef_);
				}
				else
				{
					// Final loop dimension, so tasks allocate here
					iteration_allocator(_get_thread_pool(), funcRef_, iterator_);
				}
			}
		}
		
		template<class T_>
		[[nodiscard]] static constexpr inline bool _is_tuple()
		{
			return EmuCore::TMP::is_tuple_v<EmuCore::TMP::remove_ref_cv_t<T_>>;
		}

		[[nodiscard]] constexpr inline thread_pool_type& _get_thread_pool()
		{
			if constexpr (std::is_pointer_v<stored_thread_pool_type>)
			{
				return *thread_pool;
			}
			else
			{
				return thread_pool;
			}
		}
		[[nodiscard]] constexpr inline const thread_pool_type& _get_thread_pool() const
		{
			if constexpr (std::is_pointer_v<stored_thread_pool_type>)
			{
				return *thread_pool;
			}
			else
			{
				return thread_pool;
			}
		}

		stored_thread_pool_type thread_pool;
		iteration_allocator_type iteration_allocator;
	};

	template<class Func_, class ThreadPool_ = EmuThreads::DefaultThreadPool>
	using DefaultParallelFor = ParallelFor<Func_, ThreadPool_, EmuThreads::Functors::default_parallel_loop_iteration_allocator<std::remove_pointer_t<ThreadPool_>>>;
}

#endif