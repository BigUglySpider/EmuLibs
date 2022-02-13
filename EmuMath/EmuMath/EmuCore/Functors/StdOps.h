#ifndef EMU_CORE_FUNCTORS_STD_OPS_H_INC_
#define EMU_CORE_FUNCTORS_STD_OPS_H_INC_ 1

#include "../TMPHelpers/OperatorChecks.h"
#include "../TMPHelpers/Values.h"
#include <utility>


namespace EmuCore
{
	using std::swap;

	/// <summary>
	/// <para> Functor for performing a swap operation between two different operands. </para>
	/// <para> Performs one of 3 outcomes unless specialised, in which case the outcomes are defined by the specialisation: </para>
	/// <para> 1: Where a call to `swap` using ADL is possible with a reference to A_ and B_, this will call swap(a_, b_). </para>
	/// <para> 
	///		2: Where 1 is not met, A_ is constructible via a A_ reference, A_ is assignable with a B_ reference, and B_ is assignable with a std::moved A_ value,
	///		and A_ and B_ are the same types unqualified, a basic swap will be performed using a temporary copy of a_ which will be move-assigned to b_, after assigning b_ to a_.
	/// </para>
	/// <para>
	///		Where 1 and 2 are not met, A_ is constructible via a A_ reference, A_ is assignable with a B_ reference, and B_ is assignable with a std::moved A_ value,
	///		but A_ and B_ are different types unqualified, a basic swap will be performed as in 2, but the right-hand operands in assignment will be static_cast first.
	/// </para>
	/// </summary>
	/// <typeparam name="A_"></typeparam>
	/// <typeparam name="B_"></typeparam>
	template<class A_, class B_ = A_>
	struct do_swap
	{
	private:
		template<class ARef_, class BRef_, typename = void>
		struct _use_swap_func : std::false_type {};

		template<class ARef_, class BRef_>
		struct _use_swap_func<ARef_, BRef_, std::void_t<decltype(swap(std::declval<ARef_>(), std::declval<BRef_>()))>> : std::true_type {};

		static constexpr inline void _basic_assumption_backup_differing_types(A_& a_, B_& b_)
		{
			using a_uq = typename EmuCore::TMP::remove_ref_cv<A_>::type;
			using b_uq = typename EmuCore::TMP::remove_ref_cv<B_>::type;
			if constexpr (EmuCore::TMP::is_static_castable_v<decltype(std::move(std::declval<A_&>())), b_uq>)
			{
				if constexpr (EmuCore::TMP::is_static_castable_v<decltype(std::move(std::declval<B_&>())), a_uq>)
				{
					if constexpr (std::is_assignable_v<A_&, a_uq>)
					{
						if constexpr (std::is_assignable_v<B_&, decltype(std::move(std::declval<b_uq>()))>)
						{
							b_uq temp_a_ = static_cast<b_uq>(std::move(a_));
							a_ = static_cast<a_uq>(std::move(b_));
							b_ = std::move(temp_a_);
						}
						else
						{
							static_assert
							(
								EmuCore::TMP::get_false<A_, B_>(),
								"Attempted to perform a swap via EmuCore::do_swap functor, but the provided differing types could not be swapped via a call to `swap` using ADL, nor could a basic swap assumption be implemented due to a reference to B_ not being assignable via a moved unqualified instance of B_."
							);
						}
					}
					else
					{
						static_assert
						(
							EmuCore::TMP::get_false<A_, B_>(),
							"Attempted to perform a swap via EmuCore::do_swap functor, but the provided differing types could not be swapped via a call to `swap` using ADL, nor could a basic swap assumption be implemented due to a reference to A_ not being assignable via an unqualified instance of A_ resulting from a static_cast."
						);
					}
				}
				else
				{
					static_assert
					(
						EmuCore::TMP::get_false<A_, B_>(),
						"Attempted to perform a swap via EmuCore::do_swap functor, but the provided differing types could not be swapped via a call to `swap` using ADL, nor could a basic swap assumption be implemented due to a moved reference to B_ not being static_cast-able to an unqualified instance of A_."
					);
				}
			}
			else
			{
				static_assert
				(
					EmuCore::TMP::get_false<A_, B_>(),
					"Attempted to perform a swap via EmuCore::do_swap functor, but the provided differing types could not be swapped via a call to `swap` using ADL, nor could a basic swap assumption be implemented due to a moved value of A_ not being static_cast-able to an unqualified instance of B_."
				);
			}
		}

		static constexpr inline void _basic_assumption_backup(A_& a_, B_& b_)
		{
			using a_uq = typename EmuCore::TMP::remove_ref_cv<A_>::type;
			using b_uq = typename EmuCore::TMP::remove_ref_cv<B_>::type;
			if constexpr (std::is_constructible_v<b_uq, decltype(std::move(std::declval<A_&>()))>)
			{
				if constexpr (std::is_assignable_v<B_&, decltype(std::move(std::declval<b_uq>()))>)
				{
					if constexpr (std::is_assignable_v<A_&, decltype(std::move(std::declval<B_&>()))>)
					{

						if constexpr (std::is_same_v<a_uq, b_uq>)
						{
							b_uq temp_a_ = b_uq(std::move(a_));
							a_ = std::move(b_);
							b_ = std::move(temp_a_);
						}
						else
						{
							_basic_assumption_backup_differing_types(a_, b_);
						}
					}
					else
					{
						static_assert
						(
							EmuCore::TMP::get_false<A_, B_>(),
							"Attempted to perform a swap via EmuCore::do_swap functor, but the provided types could not be swapped via a call to `swap` using ADL, nor could a basic swap assumption be implemented due to a reference to A_ not being assignable via a moved reference to B_."
						);
					}
				}
				else
				{
					static_assert
					(
						EmuCore::TMP::get_false<A_, B_>(),
						"Attempted to perform a swap via EmuCore::do_swap functor, but the provided types could not be swapped via a call to `swap` using ADL, nor could a basic swap assumption be implemented due to a reference to B_ not being assignable via a moved unqualified B_."
					);
				}
			}
			else
			{
				static_assert
				(
					EmuCore::TMP::get_false<A_, B_>(),
					"Attempted to perform a swap via the EmuCore::do_swap functor, but the provided types could not be swapped via a call to `swap` using ADL, nor could a basic swap assumption be implemented due to a moved reference to A_ not being valid for constructing an instance of unqualified B_."
				);
			}
		}

	public:
		constexpr inline do_swap()
		{
		}

		constexpr inline void operator()(A_& a_, B_& b_) const
		{
			using std::swap;
			if constexpr (_use_swap_func<A_&, B_&>::value)
			{
				swap(a_, b_);
			}
			else
			{
				_basic_assumption_backup(a_, b_);
			}
		}
	};

	template<>
	struct do_swap<void, void>
	{
		constexpr inline do_swap()
		{
		}

		template<class A_, class B_>
		constexpr inline typename std::invoke_result<EmuCore::do_swap<A_, B_>, A_&, B_&>::type operator()(A_& a_, B_& b_) const
		{
			return EmuCore::do_swap<A_, B_>()(a_, b_);
		}
	};
}

#endif
