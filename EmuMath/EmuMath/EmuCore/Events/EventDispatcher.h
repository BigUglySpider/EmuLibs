#ifndef EMU_CORE_EVENT_DISPATCHER_H_INC_
#define EMU_CORE_EVENT_DISPATCHER_H_INC_ 1

#include "EventInvoker.h"

namespace EmuCore::Events
{
	/// <summary> Default functor used to dispatch an event to all listeners when an event is invoked. </summary>
	template<class EventInvoker_ = EmuCore::Events::EventInvoker>
	class EventDispatcher
	{
	public:
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
					invoker.operator()(id_listener_pair_.second, args_...);
				}
			}
			else
			{
				for (auto& id_listener_pair_ : listeners_)
				{
					invoker.operator()(id_listener_pair_.second, args_...);
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
		EventInvoker_ invoker;
	};
}

#endif
