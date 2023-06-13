#ifndef EMU_CORE_EVENT_H_INC_
#define EMU_CORE_EVENT_H_INC_

#include <any>
#include <functional>
#include <type_traits>
#include <unordered_map>

#include "EventDispatcher.h"
#include "../TMPHelpers/Values.h"

namespace EmuCore::Events
{
	/// <summary>
	/// <para> Event which may have an arbitrary number of listeners passed, which will be called with provided arguments whenever the event is invoked. </para>
	/// <para> It is recommended to use DefaultEvent and its variants unless you know exactly what you are doing with the provided Dispatcher_. </para>
	/// </summary>
	/// <typeparam name="Listener_">Type that will be used as the listeners to this event.</typeparam>
	/// <typeparam name="Dispatcher_">
	///	<para> Functor used to dispatch invocation to listeners whenever this event is invoked. </para>
	/// <para>
	///		This functor will be called via operator(), passing 1: a const or non-const reference to this event's listeners, and 2: the arguments for invocation. 
	///		Operator() is additionally provided multiple template arguments: the type of listeners (non-reference, with const-qualification where applicable), 
	///		and all argument types provided on invocation.
	/// </para>
	/// <para> The remainder of invocation is then left to the dispatcher, and it is assumed that the dispatcher will invoke every listener on a call to operator(). </para>
	/// </typeparam>
	/// <typeparam name="Args_">Types of the arguments provided on invocation.</typeparam>
	template<class Listener_, class Dispatcher_, class...Args_>
	class Event
	{
	public:
		using listener_type = Listener_;
		static_assert
		(
			Dispatcher_::template valid_invocation<Listener_, Args_...>(),
			"Attempted to create an EmuCore Event with a listener type that cannot take the provided args using its underlying dispatcher."
		);

		using id_type = std::size_t;
		using dispatcher_type = Dispatcher_;
		using this_type = Event<listener_type, dispatcher_type>;

		template<typename = std::enable_if_t<std::is_default_constructible_v<dispatcher_type>>>
		Event() : next_id(_starting_id()), listeners(), dispatcher()
		{
		}
		template<class...DispatcherConstructionArgs_, typename = std::enable_if_t<std::is_constructible_v<dispatcher_type, DispatcherConstructionArgs_...>>>
		Event(DispatcherConstructionArgs_...dispatcher_construction_args) : next_id(_starting_id()), listeners(), dispatcher(dispatcher_construction_args...)
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
			if constexpr(ForwardArgsAsReferences_)
			{
				dispatcher.operator()<listeners_storage, Args_&...>(listeners, args_...);
			}
			else
			{
				dispatcher.operator()<listeners_storage, Args_...>(listeners, args_...);
			}
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
			if constexpr (ForwardArgsAsReferences_)
			{
				const_cast<this_type*>(this)->Invoke<ForwardArgsAsReferences_, Args_&...>(args_...);
			}
			else
			{
				const_cast<this_type*>(this)->Invoke<ForwardArgsAsReferences_, Args_&...>(args_...);
			}
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
			if constexpr(ForwardArgsAsReferences_)
			{
				dispatcher.operator()<const listeners_storage, Args_&...>(listeners, args_...);
			}
			else
			{
				dispatcher.operator()<const listeners_storage, Args_...>(listeners, args_...);
			}
		}

		/// <summary> Adds a new listener for this event and returns the ID that refers to said listener. </summary>
		/// <param name="listener_">Listener to await this event's invocation.</param>
		/// <returns>ID of the listener once it is linked to this event. If the listener's removal may be desired, it is important that this ID is recorded.</returns>
		inline id_type AddListener(listener_type& listener_)
		{
			id_type id_ = _get_next_id();
			listeners.emplace(id_type(id_), listener_);
			return id_;
		}
		template<typename = std::enable_if_t<!(std::is_const_v<listener_type> && std::is_reference_v<listener_type>)>>
		inline id_type AddListener(const listener_type& listener_)
		{
			id_type id_ = _get_next_id();
			listeners.emplace(id_type(id_), listener_);
			return id_;
		}

		/// <summary> Default constructs a new listener and adds it to wait for this event to be invoked, returning the ID once it is linked to this event. </summary>
		/// <returns>ID of the listener once it is linked to this event. If the listener's removal may be desired, it is important that this ID is recorded.</returns>
		template<typename = std::enable_if_t<std::is_default_constructible_v<listener_type>>>
		inline id_type ConstructListener()
		{
			static_assert
			(
				std::is_default_constructible_v<listener_type>,
				"Attempted to default-construct a listener for an EmuCore Event with invalid construction arguments."
			);
			if constexpr (std::is_default_constructible_v<listener_type>)
			{
				listener_type listener_ = listener_type();
				return AddListener(listener_);
			}
		}
		/// <summary>
		///		Constructs a new listener with the provided arguments and adds it to wait for this event to be invoked, returning the ID once it is linked to this event.
		/// </summary>
		/// <returns>ID of the listener once it is linked to this event. If the listener's removal may be desired, it is important that this ID is recorded.</returns>
		template<class FirstArg_, class...AdditionalArgs_, typename = std::enable_if_t<std::is_constructible_v<listener_type, FirstArg_, AdditionalArgs_...>>>
		inline id_type ConstructListener(FirstArg_ firstArg_, AdditionalArgs_...additionalArgs_)
		{
			static_assert
			(
				std::is_constructible_v<listener_type, FirstArg_, AdditionalArgs_...>,
				"Attempted to construct a listener for an EmuCore Event with invalid construction arguments."
			);
			if constexpr (std::is_constructible_v<listener_type, FirstArg_, AdditionalArgs_...>)
			{
				listener_type listener_ = listener_type(firstArg_, additionalArgs_...);
				return AddListener(listener_);
			}
		}

		/// <summary> 
		/// <para> Removes all listeners which match the provided listener, and returns the number of listeners removed. </para>
		/// <para> This function makes use of operator==. If the contained listeners may not be compared via operator==, this function may not be used. </para>
		/// </summary>
		/// <param name="listener_">Listener to remove from this event.</param>
		/// <returns>Total number of listeners removed by this function call.</returns>
		inline std::size_t RemoveMatchingListeners(const listener_type& listener_)
		{
			auto it_ = listeners.begin();
			std::size_t count_ = 0;
			while (it_ != listeners.end())
			{
				if (it_->second == listener_)
				{
					listeners.erase(it_);
					++count_;
				}
				++it_;
			}
			return count_;
		}

		/// <summary> Removes the listener of the passed ID within this event. Returns a boolean indicating if anything was removed. </summary>
		/// <param name="id_">ID of the listener to remove.</param>
		/// <returns>Boolean indicating if a listener was removed. If this is false, it means no listener with the provided ID existed for this event.</returns>
		inline bool RemoveListener(const id_type id_)
		{
			auto it_ = listeners.find(id_);
			if (it_ != listeners.end())
			{
				listeners.erase(it_);
				return true;
			}
			else
			{
				return false;
			}
		}

		/// <summary> Removes all listeners for this event and resets the IDs for this event. </summary>
		inline void RemoveAllListeners()
		{
			listeners = listeners_storage();
			next_id = _starting_id();
		}

	private:
		using listeners_storage = std::unordered_map<id_type, listener_type>;

		id_type next_id;
		listeners_storage listeners;
		dispatcher_type dispatcher;

		static constexpr id_type _starting_id()
		{
			return id_type(0);
		}
		inline id_type _get_next_id()
		{
			return next_id++;
		}
	};

	/// <summary> EmuCore Event with the default dispatcher. </summary>
	template<class Listener_, class...Args_>
	using DefaultEvent = EmuCore::Events::Event<Listener_, EmuCore::Events::EventDispatcher<EmuCore::Events::EventInvoker>, Args_...>;

	/// <summary> EmuCore Event with the default dispatcher, with contained listeners being std::function objects which take the provided arguments. </summary>
	template<class...Args_>
	using DefaultEventStdFuncs = EmuCore::Events::DefaultEvent<std::function<void(Args_...)>, Args_...>;
}

#endif
