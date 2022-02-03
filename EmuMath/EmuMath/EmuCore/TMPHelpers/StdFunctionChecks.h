#ifndef EMU_CORE_TMP_STD_FUNCTION_CHECKS_H_INC_
#define EMU_CORE_TMP_STD_FUNCTION_CHECKS_H_INC_ 1

#include <cmath>
#include <type_traits>

namespace EmuCore::TMP
{
#pragma region CALL_CHECKS
	template<class X_, class Y_, class Z_, typename = void>
	struct valid_fma_args
	{
		static constexpr bool value = false;
	};

	template<class X_, class Y_, class Z_>
	struct valid_fma_args<X_, Y_, Z_, std::void_t<decltype(std::fma(std::declval<X_>(), std::declval<Y_>(), std::declval<Z_>()))>>
	{
		static constexpr bool value = true;
	};

	template<class X_, class Y_, class Z_>
	static constexpr bool valid_fma_args_v = valid_fma_args<X_, Y_, Z_>::value;
#pragma endregion

#pragma region INVOKE_RESULT_CHECKS
	/// <summary>
	/// <para> Determines the type that will result from invoke std::fma with the provided X_, Y_, Z_ argument types. </para>
	/// <para> If the call is invalid, the type will be void. This should not be used as a validity check; for such uses, use valid_fma_args_v. </para>
	/// </summary>
	template<class X_, class Y_, class Z_>
	struct fma_result
	{
	private:
		template<bool Valid_>
		struct _result_finder
		{
			using type = void;
		};

		template<>
		struct _result_finder<true>
		{
			using type = decltype(std::fma(std::declval<X_>(), std::declval<Y_>(), std::declval<Z_>()));
		};

	public:
		using type = typename _result_finder<valid_fma_args_v<X_, Y_, Z_>>::type;
	};

	template<class X_, class Y_, class Z_>
	using fma_result_t = typename fma_result<X_, Y_, Z_>::type;
#pragma endregion
}

#endif
