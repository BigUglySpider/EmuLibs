#ifndef EMU_CORE_COMMON_ALGEBRA_H_INC_
#define EMU_CORE_COMMON_ALGEBRA_H_INC_ 1

#include "CommonMath.h"
#include "CommonValues.h"
#include "../Functors/Arithmetic.h"
#include "../TMPHelpers/DescriptiveEnableIf.h"
#include "../TMPHelpers/TypeObfuscation.h"

namespace EmuCore
{
	/// <summary>
	/// <para> Template function to calculate the dot product of any arbitrary number of values. </para>
	/// <para> Only invoked when at least 3 arguments are passed. </para>
	/// <para> Requires an output type as its first template argument. </para>
	/// </summary>
	/// <param name="values_">All values to be used in calculation of the dot product.</param>
	/// <returns>The dot product of all passed `values_`.</returns>
	template<typename Out_ = void, typename...Ts_, typename = EmuCore::TMP::enable_if_min_typeargs_t<3, Ts_...>>
	[[nodiscard]] constexpr inline decltype(auto) dot(Ts_&&...values_)
	{
		if constexpr (std::is_void_v<Out_>)
		{
			return 
			(
				Out_(0) + 
				... + 
				EmuCore::do_multiply<typename EmuCore::TMP::remove_ref_cv<Ts_>::type, typename EmuCore::TMP::remove_ref_cv<Ts_>::type>()
				(
					EmuCore::TMP::const_lval_ref_cast<Ts_>(values_),
					EmuCore::TMP::const_lval_ref_cast<Ts_>(values_)
				)
			);
		}
		else
		{
			return static_cast<Out_>
			(
				(
					Out_(0) + 
					... + 
					EmuCore::do_multiply<typename EmuCore::TMP::remove_ref_cv<Ts_>::type, typename EmuCore::TMP::remove_ref_cv<Ts_>::type>()
					(
						EmuCore::TMP::const_lval_ref_cast<Ts_>(values_),
						EmuCore::TMP::const_lval_ref_cast<Ts_>(values_)
					)
				)
			);
		}		
	}

	/// <summary>
	/// <para> Template function to calculate the dot product of 2 passed values of arbitrary types. </para>
	/// <para> This function may be specialised for special types which may produce dot products differently (such as mathematical vectors). </para>
	/// <para> Requires an output type as its first template argument. </para>
	/// </summary>
	/// <param name="a_">First item for calculating the dot product.</param>
	/// <param name="b_">Second item for calculating the dot product.</param>
	/// <returns>Dot product of `a_` and `b_`, which is equivalent to `(a_ * a_) + (b_ * b_)` for scalar types.</returns>
	template<typename Out_ = void, typename A_, typename B_>
	[[nodiscard]] constexpr inline decltype(auto) dot(A_&& a_, B_&& b_)
	{
		const auto& a_lval = EmuCore::TMP::const_lval_ref_cast<A_>(std::forward<A_>(a_));
		const auto& b_lval = EmuCore::TMP::const_lval_ref_cast<B_>(std::forward<B_>(b_));

		if constexpr(std::is_void_v<Out_>)
		{
			return EmuCore::do_add<void, void>()
			(
				EmuCore::do_multiply<typename EmuCore::TMP::remove_ref_cv<A_>::type, typename EmuCore::TMP::remove_ref_cv<A_>::type>()(a_lval, a_lval),
				EmuCore::do_multiply<typename EmuCore::TMP::remove_ref_cv<B_>::type, typename EmuCore::TMP::remove_ref_cv<B_>::type>()(b_lval, b_lval)
			);
		}
		else
		{
			return static_cast<Out_>
			(
				EmuCore::do_add<void, void>()
				(
					EmuCore::do_multiply<typename EmuCore::TMP::remove_ref_cv<A_>::type, typename EmuCore::TMP::remove_ref_cv<A_>::type>()(a_lval, a_lval),
					EmuCore::do_multiply<typename EmuCore::TMP::remove_ref_cv<B_>::type, typename EmuCore::TMP::remove_ref_cv<B_>::type>()(b_lval, b_lval)
				)
			);
		}
	}
}

#endif
