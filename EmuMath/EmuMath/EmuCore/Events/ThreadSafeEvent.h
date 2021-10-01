#ifndef EMU_CORE_THREAD_SAFE_EVENT_H_INC_
#define EMU_CORE_THREAD_SAFE_EVENT_H_INC_ 1

#include "Event.h"
#include <mutex>

namespace EmuCore::Events
{
	/// <summary> 
	/// <para> Wrapper for EmuCore events which makes access to an event thread safe. </para>
	/// <para>
	///		Note that thread-safety is not entirely guaranteed as the dispatcher may divert work to other threads and return before all work is complete. 
	///		By default, thread safety is guaranteed, but this may change with different Dispatcher_ arguments.
	/// </para>
	/// <para> For more information, review EmuCore::Events::Event. </para>
	/// </summary>
	/// <typeparam name="Listener_">Listeners that will await this event to be invoked.</typeparam>
	/// <typeparam name="Dispatcher_">Functor used to dispatch invocation to listeners when this event is invoked.</typeparam>
	/// <typeparam name="Args_">Argument types passed to this event and its listeners when invoked.</typeparam>
	template<class Listener_, class Dispatcher_, class...Args_>
	class ThreadSafeEvent
	{
	private:
		using underlying_event_type = Event<Listener_, Dispatcher_, Args_...>;

	public:
		using id_type = typename underlying_event_type::id_type;
		using listener_type = typename underlying_event_type::listener_type;
		using dispatcher_type = typename underlying_event_type::dispatcher_type;
		using this_type = ThreadSafeEvent<listener_type, dispatcher_type>;

		template<typename = std::enable_if_t<std::is_default_constructible_v<underlying_event_type>>>
		ThreadSafeEvent() : underlying_event(), mutex_()
		{
		}
		template<class...UnderlyingConstructionArgs_, typename = std::enable_if_t<std::is_constructible_v<underlying_event_type, UnderlyingConstructionArgs_...>>>
		ThreadSafeEvent(UnderlyingConstructionArgs_...underlying_construction_args_) : underlying_event(underlying_construction_args_), mutex_()
		{
		}

		/// <summary>
		/// <para> Invokes the contained listeners. </para>
		/// <para>
		///		Note that the const-variant of this function will NOT invoke the const-variant of contained listeners. 
		///		This behaviour is intended to allow Events to prohibit listeners being added or removed, while maintaining non-const invocability for contained listeners.
		/// </para>
		/// <para> If you wish to invoke const-variants of the contained listeners, use InvokeConst instead. </para>
		/// </summary>
		/// <typeparam name="Args_">Types of arguments to pass when invoking listeners.</typeparam>
		/// <param name="args_">Arguments to pass to listeners when invoking them.</param>
		template<bool ForwardArgsAsReferences_ = true>
		inline void Invoke(Args_...args_)
		{
			std::lock_guard<std::mutex> guard_(mutex_);
			underlying_event.Invoke<ForwardArgsAsReferences_>(args_...);
		}
		/// <summary>
		/// <para> Invokes the contained listeners. </para>
		/// <para>
		///		Note that the const-variant of this function will NOT invoke the const-variant of contained listeners. 
		///		This behaviour is intended to allow Events to prohibit listeners being added or removed, while maintaining non-const invocability for contained listeners.
		/// </para>
		/// <para> If you wish to invoke const-variants of the contained listeners, use InvokeConst instead. </para>
		/// </summary>
		/// <typeparam name="Args_">Types of arguments to pass when invoking listeners.</typeparam>
		/// <param name="args_">Arguments to pass to listeners when invoking them.</param>
		template<bool ForwardArgsAsReferences_ = true>
		inline void Invoke(Args_...args_) const
		{
			std::lock_guard<std::mutex> guard_(mutex_);
			underlying_event.Invoke<ForwardArgsAsReferences_>(args_...);
		}

		/// <summary>
		/// <para> Invokes a const-variant of the contained listeners. </para>
		/// <para> Note that this is NOT called if Invoke is called on a const Event object. </para>
		/// </summary>
		/// <typeparam name="Args_">Types of arguments to pass when invoking listeners.</typeparam>
		/// <param name="args_">Arguments to pass to listeners when invoking them.</param>
		template<bool ForwardArgsAsReferences_ = true>
		inline void InvokeConst(Args_...args_) const
		{
			std::lock_guard<std::mutex> guard_(mutex_);
			underlying_event.InvokeConst<ForwardArgsAsReferences_>(args_...);
		}

		/// <summary> Adds a new listener for this event and returns the ID that refers to said listener. </summary>
		/// <param name="listener_">Listener to await this event's invocation.</param>
		/// <returns>ID of the listener once it is linked to this event. If the listener's removal may be desired, it is important that this ID is recorded.</returns>
		inline id_type AddListener(listener_type& listener_)
		{
			std::lock_guard<std::mutex> guard_(mutex_);
			return underlying_event.AddListener(listener_);
		}
		inline id_type AddListener(const listener_type& listener_)
		{
			std::lock_guard<std::mutex> guard_(mutex_);
			return underlying_event.AddListener(listener_);
		}

		/// <summary> Default constructs a new listener and adds it to wait for this event to be invoked, returning the ID once it is linked to this event. </summary>
		/// <returns>ID of the listener once it is linked to this event. If the listener's removal may be desired, it is important that this ID is recorded.</returns>
		template<typename = std::enable_if_t<std::is_default_constructible_v<listener_type>>>
		inline id_type ConstructListener()
		{
			std::lock_guard<std::mutex> guard_(mutex_);
			return underlying_event.ConstructListener();
		}
		/// <summary>
		///		Constructs a new listener with the provided arguments and adds it to wait for this event to be invoked, returning the ID once it is linked to this event.
		/// </summary>
		/// <returns>ID of the listener once it is linked to this event. If the listener's removal may be desired, it is important that this ID is recorded.</returns>
		template<class FirstArg_, class...AdditionalArgs_, typename = std::enable_if_t<std::is_constructible_v<listener_type, FirstArg_, AdditionalArgs_...>>>
		inline id_type ConstructListener(FirstArg_ firstArg_, AdditionalArgs_...additionalArgs_)
		{
			std::lock_guard<std::mutex> guard_(mutex_);
			return underlying_event.ConstructListener<FirstArg_, AdditionalArgs_...>(firstArg_, additionalArgs_...);
		}

		/// <summary> 
		/// <para> Removes all listeners which match the provided listener, and returns the number of listeners removed. </para>
		/// <para> This function makes use of operator==. If the contained listeners may not be compared via operator==, this function may not be used. </para>
		/// </summary>
		/// <param name="listener_">Listener to remove from this event.</param>
		/// <returns>Total number of listeners removed by this function call.</returns>
		inline std::size_t RemoveMatchingListeners(const listener_type& listener_)
		{
			std::lock_guard<std::mutex> guard_(mutex_);
			return underlying_event.RemoveMatchingListeners(listener_);
		}

		/// <summary> Removes the listener of the passed ID within this event. Returns a boolean indicating if anything was removed. </summary>
		/// <param name="id_">ID of the listener to remove.</param>
		/// <returns>Boolean indicating if a listener was removed. If this is false, it means no listener with the provided ID existed for this event.</returns>
		inline bool RemoveListener(const id_type id_)
		{
			std::lock_guard<std::mutex> guard_(mutex_);
			return underlying_event.RemoveListener(id_);
		}

		/// <summary> Removes all listeners for this event and resets the IDs for this event. </summary>
		inline void RemoveAllListeners()
		{
			std::lock_guard<std::mutex> guard_(mutex_);
			underlying_event.RemoveAllListeners();
		}
	private:
		underlying_event_type underlying_event;
		std::mutex mutex_;
	};

	/// <summary> Thread safe variant of EmuCore::Events::DefaultEvent. </summary>
	template<class Listener_, class...Args_>
	using DefaultThreadSafeEvent = EmuCore::Events::ThreadSafeEvent<Listener_, EmuCore::Events::EventDispatcher<EmuCore::Events::EventInvoker>, Args_...>;

	/// <summary> Thread safe variant of EmuCore::Events::DefaultEventStdFuncs. </summary>
	template<class...Args_>
	using DefaultThreadSafeEventStdFuncs = EmuCore::Events::DefaultThreadSafeEvent<std::function<void(Args_...)>, Args_...>;
}

#endif
