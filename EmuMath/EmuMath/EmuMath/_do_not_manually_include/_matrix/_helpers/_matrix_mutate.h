#ifndef EMU_MATH_MATRIX_MUTATE_H_INC_
#define EMU_MATH_MATRIX_MUTATE_H_INC_ 1

#include "_common_matrix_helper_includes.h"

namespace EmuMath::Helpers
{
	/// <summary>
	/// <para> Outputs an EmuMath Matrix resulting from invoking invocations of the provided Func_ with the provided Args_ for every index. </para>
	/// <para> If a provided Arg_ is an EmuMath Matrix: The respective theoretical column/row index will be used as an argument instead of the Matrix itself. </para>
	/// <para> If a provided Arg_ is none of the above: All function invocations will use the provided Arg_ as is. </para>
	/// </summary>
	/// <param name="func_">Function to invoke for each mutation. This is considered not explicitly provided if the first template parameter is the Func_ type.</param>
	/// <param name="args_"></param>
	/// <returns></returns>
	template<std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, bool OutColumnMajor_ = true, class Func_, class...Args_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_> matrix_mutate(Func_ func_, Args_&&...args_)
	{
		using func_ref = std::add_lvalue_reference_t<Func_>;
		return _matrix_underlying::_matrix_mutate_return_out<func_ref, OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_, 0, OutNumColumns_, 0, OutNumRows_>
		(
			func_,
			std::forward<Args_>(args_)...
		);
	}

	template<class Func_, std::size_t OutNumColumns_, std::size_t OutNumRows_, typename OutT_, bool OutColumnMajor_ = true, class...Args_>
	[[nodiscard]] constexpr inline EmuMath::Matrix<OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_> matrix_mutate(Args_&&...args_)
	{
		return _matrix_underlying::_matrix_mutate_return_out_no_func_passed<Func_, OutNumColumns_, OutNumRows_, OutT_, OutColumnMajor_, 0, OutNumColumns_, 0, OutNumRows_>
		(
			std::forward<Args_>(args_)...
		);
	}
}

#endif
