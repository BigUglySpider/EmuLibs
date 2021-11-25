#ifndef EMU_THREADS_BIND_TMP_H_INC_
#define EMU_THREADS_BIND_TMP_H_INC_ 1

#include <type_traits>
#include <utility>

namespace EmuThreads::TMP
{
	/// <summary>
	/// <para> Type deducer for forming a suitable argument to pass to std::bind when allocating a task. For use with get_suitable_bind_arg. </para>
	/// <para> When Arg_ is an lvalue reference: reference represented as a std::reference_wrapper. </para>
	/// <para> When Arg_ is an rvalue reference: result of std::forward-ing the reference. </para>
	/// <para> When Arg_ is a move-constructible value: result of std::move-ing the value. </para>
	/// <para> When Arg_ is none of the above: reference to the Arg_. </para>
	/// </summary>
	/// <typeparam name="Arg_">Type of argument to deduce the suitable type of when passing to std::bind.</typeparam>
	template<class Arg_>
	struct _suitable_bind_arg_return
	{
		using type = std::conditional_t
		<
			std::is_lvalue_reference_v<Arg_>,
			std::reference_wrapper<std::remove_reference_t<Arg_>>, // LVAL REF: Return a wrapped std::ref to ensure reference state is maintained
			std::conditional_t
			<
				std::is_rvalue_reference_v<Arg_>,
				decltype(std::forward<Arg_>(std::declval<Arg_>())), // RVAL REF: Return a forwarded the reference
				std::conditional_t
				<
					!std::is_pointer_v<Arg_> && std::is_move_constructible_v<Arg_>,
					decltype(std::move<Arg_>(std::declval<Arg_>())), // MOVE-CONSTRUCTIBLE VALUE: Move the value to optimise argument passing
					Arg_&	// NONE OF THE ABOVE: Reference to the provided arg to at least avoid extra construction when passing args to bind
				>
			>
		>;
	};

	/// <summary>
	/// <para> Transforms the passed argument reference intended for std::bind to a suitable value to pass to std::bind, returning one of the following: </para>
	/// <para> When Arg_ is an lvalue reference (i.e. Arg_&amp;): reference represented as a std::reference_wrapper. </para>
	/// <para> When Arg_ is an rvalue reference (i.e. Arg_&amp;&amp;): result of std::forward-ing the reference. </para>
	/// <para> When Arg_ is a move-constructible value (i.e. Arg_): result of std::move-ing the value. </para>
	/// <para> When Arg_ is none of the above: reference to the Arg_. </para>
	/// <para> NOTE: It is important to provide the type of Arg_ that is being passed as a template argument in cases where the qualifiers of Arg_ may be ambiguous. </para>
	/// </summary>
	/// <typeparam name="Arg_">Type of argument being passed.</typeparam>
	/// <param name="arg_">Argument to pass, performing a transformation if necessary</param>
	/// <returns></returns>
	template<class Arg_>
	[[nodiscard]] inline typename _suitable_bind_arg_return<Arg_>::type get_suitable_bind_arg(Arg_& arg_)
	{
		if constexpr (std::is_lvalue_reference_v<Arg_>)
		{
			return std::ref(arg_);
		}
		else if constexpr(std::is_rvalue_reference_v<Arg_>)
		{
			return std::forward<Arg_>(arg_);
		}
		else if constexpr(!std::is_pointer_v<Arg_>)
		{
			return std::move(arg_);
		}
		else
		{
			return arg_;
		}
	}
}

#endif
