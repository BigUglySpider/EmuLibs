#ifndef EMU_MATH_VECTOR_MUTATION_UNDERLYING_H_INC_
#define EMU_MATH_VECTOR_MUTATION_UNDERLYING_H_INC_ 1

#include "_vector_copy_underlying.h"
#include "_vector_get_underlying.h"
#include "_vector_tmp.h"

namespace EmuMath::Helpers::_vector_underlying
{
	template<class Vector_, std::size_t FirstIndex_, std::size_t...RemainingIndices_>
	struct _is_any_index_not_contained
	{
		static_assert
		(
			EmuMath::TMP::is_emu_new_vector_v<Vector_>,
			"Attempted to find if any variadic indices refer to a non-contained index within an EmuMath Vector, but the provided Vector_ type is not an EmuMath Vector."
		);

		[[nodiscard]] static constexpr inline bool _get()
		{
			if constexpr (EmuMath::TMP::is_emu_new_vector_v<Vector_>)
			{
				if constexpr (FirstIndex_ < Vector_::size)
				{
					using next_check = _is_any_index_not_contained<Vector_, RemainingIndices_...>;
					return next_check::_get();
				}
				else
				{
					return true;
				}
			}
			else
			{
				return false;
			}
		}
		static constexpr bool value = _get();
	};
	template<class Vector_, std::size_t Index_>
	struct _is_any_index_not_contained<Vector_, Index_>
	{
		static_assert
		(
			EmuMath::TMP::is_emu_new_vector_v<Vector_>,
			"Attempted to find if any variadic indices refer to a non-contained index within an EmuMath Vector, but the provided Vector_ type is not an EmuMath Vector."
		);

		[[nodiscard]] static constexpr inline bool _get()
		{
			if constexpr (EmuMath::TMP::is_emu_new_vector_v<Vector_>)
			{
				return Index_ >= Vector_::size;
			}
			else
			{
				return false;
			}
		}
		static constexpr bool value = _get();
	};

	template<typename OutT_, bool UseTheoreticalIndices_, std::size_t...Indices_, class InVector_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<sizeof...(Indices_), OutT_> _vector_shuffle(InVector_& in_vector_)
	{
		if constexpr (EmuMath::TMP::is_emu_new_vector_v<InVector_>)
		{
			using out_vector = EmuMath::NewVector<sizeof...(Indices_), OutT_>;
			using out_stored_type = typename out_vector::stored_type;
			using get_return_type = EmuCore::TMP::conditional_const_t<std::is_const_v<InVector_>, typename InVector_::value_type>&;

			if constexpr (_is_any_index_not_contained<std::remove_reference_t<InVector_>, Indices_...>::value)
			{
				if constexpr (UseTheoreticalIndices_)
				{
					if constexpr (std::is_constructible_v<out_stored_type, get_return_type>)
					{
						if constexpr (std::is_constructible_v<out_stored_type, typename InVector_::value_type_uq>)
						{
							return out_vector(_vector_get_theoretical<Indices_>(in_vector_)...);
						}
						else
						{
							static_assert(false, "Attempted to shuffle an EmuMath Vector with theoretical indices, but the provided OutVector_ type cannot construct its stored_type from one of the passed Vector's non-contained elements.");
						}
					}
					else
					{
						static_assert(false, "Attempted to shuffle an EmuMath Vector with theoretical indices, but the provided OutVector_ type cannot construct its stored_type from one of the passed input Vector's contained elements.");
					}
				}
				else
				{
					static_assert(false, "Attempted to shuffle an EmuMath Vector, but one of the provided indices refers to a non-contained index within the input Vector. This behaviour is allowed, but you must explicitly state that you wish to use theoretical indices.");
				}
			}
			else
			{
				if constexpr (std::is_constructible_v<out_stored_type, get_return_type>)
				{
					return out_vector(_vector_get<Indices_>(in_vector_)...);
				}
				else
				{
					static_assert(false, "Attempted to shuffle an EmuMath Vector, but the provided OutVector_ type cannot construct its stored_type from one of the passed input Vector's elements.");
				}
			}
		}
		else
		{
			static_assert(false, "Attempted to shuffle an EmuMath Vector, but the provided input Vector is not recognised as an EmuMath Vector.");
		}
	}

	template<std::size_t Index_, std::size_t EndIndex_, std::size_t ArgIndex_, class Func_, class OutVector_, class...Args_>
	constexpr inline void _vector_mutate_execution(Func_& func_, OutVector_& out_vector_, Args_&&...args_)
	{
		if constexpr (Index_ < EndIndex_)
		{
			if constexpr (std::is_invocable_v<Func_, decltype(_vector_get_theoretical_if_vector<ArgIndex_>(std::declval<Args_>()))...>)
			{
				using invocation_result = std::invoke_result_t<Func_, decltype(_vector_get_theoretical_if_vector<ArgIndex_>(std::declval<Args_>()))...>;
				if constexpr (EmuCore::TMP::is_compatible_v<typename OutVector_::value_type, invocation_result>)
				{
					_vector_copy_index<Index_>(out_vector_, func_(_vector_get_theoretical_if_vector<ArgIndex_>(args_)...));
					_vector_mutate_execution<Index_ + 1, EndIndex_, ArgIndex_ + 1, Func_, OutVector_, Args_...>(func_, out_vector_, args_...);
				}
				else
				{
					static_assert(false, "Attempted to mutate an EmuMath Vector, but at least one iteration of mutation resulted in the mutation function providing a result that cannot be used to copy to the output Vector's value_type.");
				}
			}
			else
			{
				static_assert(false, "Attempted to mutate an EmuMath Vector, but at least one iteration of mutation resulted in arguments which the provided mutation function does not support.");
			}
		}
	}

	template<class Func_, class OutVector_, std::size_t BeginIndex_, std::size_t EndIndex_, std::size_t ArgIndex_, class...Args_>
	constexpr inline void _vector_mutate(Func_ func_, OutVector_& out_vector_, Args_&&...args_)
	{
		constexpr std::size_t clamped_end_index_ = (EndIndex_ <= OutVector_::size) ? EndIndex_ : OutVector_::size;
		if constexpr (BeginIndex_ <= clamped_end_index_)
		{
			_vector_mutate_execution<BeginIndex_, EndIndex_, ArgIndex_, Func_, OutVector_>(func_, out_vector_, std::forward<Args_>(args_)...);
		}
		else
		{
			static_assert(false, "Attempted to mutate an EmuMath Vector, but the provided BeginIndex_ is greater than the provided EndIndex_ after clamping.");
		}
	}

	template<class OutVector_, class Func_, std::size_t BeginIndex_, std::size_t EndIndex_, std::size_t ArgIndex_, class...Args_>
	[[nodiscard]] constexpr inline OutVector_ _vector_mutate_return_out(Func_ func_, Args_&&...args_)
	{
		if constexpr (std::is_default_constructible_v<OutVector_>)
		{
			OutVector_ out_vector_ = OutVector_();
			_vector_mutate<Func_, OutVector_, BeginIndex_, EndIndex_, ArgIndex_>(func_, out_vector_, std::forward<Args_>(args_)...);
			return out_vector_;
		}
		else
		{
			static_assert(false, "Attempted to mutate an EmuMath Vector without passing an out_vector_ to output to. This is only allowed where the provided output Vector is default-constructible.");
		}
	}

	template<class Func_, class OutVector_, std::size_t BeginIndex_, std::size_t EndIndex_, std::size_t ArgIndex_, class...Args_>
	constexpr inline void _vector_mutate_no_func_passed(OutVector_& out_vector_, Args_&&...args_)
	{
		if constexpr (std::is_default_constructible_v<Func_>)
		{
			Func_ func_ = Func_();
			_vector_mutate<Func_, OutVector_, BeginIndex_, EndIndex_, ArgIndex_>(func_, out_vector_, std::forward<Args_>(args_)...);
		}
		else
		{
			static_assert(false, "Attempted to mutate an EmuMath Vector without passing a func_ argument to perform mutation. This is only allowed where the provided Func_ type is default-constructible.");
		}
	}

	template<class Func_, class OutVector_, std::size_t BeginIndex_, std::size_t EndIndex_, std::size_t ArgIndex_, class...Args_>
	constexpr inline OutVector_ _vector_mutate_args_only(Args_&&...args_)
	{
		if constexpr (std::is_default_constructible_v<Func_>)
		{
			if constexpr (std::is_default_constructible_v<OutVector_>)
			{
				Func_ func_ = Func_();
				OutVector_ out_vector_ = OutVector_();
				_vector_mutate<Func_, OutVector_, BeginIndex_, EndIndex_, ArgIndex_>(func_, out_vector_, std::forward<Args_>(args_)...);
				return out_vector_;
			}
			else
			{

				static_assert(false, "Attempted to mutate an EmuMath Vector without passing an out_vector_ to output to. This is only allowed where the provided output Vector is default-constructible.");
			}
		}
		else
		{
			static_assert(false, "Attempted to mutate an EmuMath Vector without passing a func_ argument to perform mutation. This is only allowed where the provided Func_ type is default-constructible.");
		}
	}
}

#endif
