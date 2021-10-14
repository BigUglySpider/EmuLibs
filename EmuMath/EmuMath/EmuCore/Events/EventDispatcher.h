#ifndef EMU_CORE_EVENT_DISPATCHER_H_INC_
#define EMU_CORE_EVENT_DISPATCHER_H_INC_ 1

#include "EventInvoker.h"
#include "../TMPHelpers/TypeConvertors.h"

namespace EmuCore::Events
{
	/// <summary> 
	/// <para> Default functor used to dispatch an event to all listeners when an event is invoked. </para>
	/// <para>
	///		This dispatcher supports the provision of pointers to listeners. 
	///		Pointers will be dereferenced until only a normal reference is available, invoking said reference.
	/// </para>
	/// <para> When pointers are provided, nullptrs will be ignored and thus skipped in invocation. </para>
	/// <para> Invocation validity with this dispatcher may be checked for at compile time via EventDispatcher::valid_invocation&lt;Listener_, Args_...&gt;. </para>
	/// </summary>
	template<class EventInvoker_ = EmuCore::Events::EventInvoker>
	class EventDispatcher
	{
	public:
		template<class Listener_, class...Args_>
		constexpr static bool valid_invocation()
		{
			return std::is_invocable_v<typename EmuCore::TMPHelpers::remove_all_pointers<Listener_>::type, Args_...>;
		}

		template<typename = std::enable_if_t<std::is_default_constructible_v<EventInvoker_>>>
		constexpr EventDispatcher() : invoker()
		{
		}
		template<class...InvokerArgs_, typename = std::enable_if_t<std::is_constructible_v<EventInvoker_, InvokerArgs_...>>>
		constexpr EventDispatcher(InvokerArgs_...invoker_construction_args_) : invoker(invoker_construction_args_...)
		{
		}

		template<class Listeners_, class...Args_>
		constexpr inline void operator()(Listeners_& listeners_, Args_...args_) const
		{
			if constexpr (std::is_const_v<Listeners_>)
			{
				for (const auto& id_listener_pair_ : listeners_)
				{
					_invoke_listener<const decltype(id_listener_pair_.second), Args_...>(id_listener_pair_.second, args_...);
				}
			}
			else
			{
				for (auto& id_listener_pair_ : listeners_)
				{
					_invoke_listener<decltype(id_listener_pair_.second), Args_...>(id_listener_pair_.second, args_...);
				}
			}
		}

		EventDispatcher& operator=(EventDispatcher& rhs_)
		{
			invoker = rhs_.invoker;
			return *this;
		}
		EventDispatcher& operator=(const EventDispatcher& rhs_)
		{
			invoker = rhs_.invoker;
			return *this;
		}

	private:
		template<class Listener_, class...Args_>
		constexpr inline void _invoke_listener(Listener_& listener_, Args_&...args_) const
		{
			if constexpr (std::is_pointer_v<Listener_>)
			{
				if (listener_ != nullptr)
				{
					_invoke_listener<std::remove_pointer_t<Listener_>, Args_...>(*listener_, args_...);
				}
			}
			else
			{
				invoker(listener_, args_...);
			}
		}

		EventInvoker_ invoker;
	};
}

#endif
