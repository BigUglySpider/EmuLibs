#ifndef EMU_CORE_EVENT_INVOKER_H_INC_
#define EMU_CORE_EVENT_INVOKER_H_INC_ 1

namespace EmuCore::Events
{
	/// <summary> Default functor used to invoke an individual listener when an event is invoked. </summary>
	struct EventInvoker
	{
		constexpr EventInvoker()
		{
		}
		template<class Listener_, class...Args_>
		constexpr inline void operator()(Listener_& listener_, Args_...args_) const
		{
			listener_(args_...);
		}
	};
}

#endif
