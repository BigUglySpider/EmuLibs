#ifndef EMU_MATH_VECTOR_MUTATION_UNDERLYING_H_INC_
#define EMU_MATH_VECTOR_MUTATION_UNDERLYING_H_INC_ 1

#include "_vector_copy_underlying.h"
#include "_vector_get_underlying.h"
#include "_vector_tmp.h"
#include "../../../../../EmuCore/TMPHelpers/VariadicHelpers.h"

namespace EmuMath::Helpers::_vector_underlying
{
#pragma region GET_HELPERS
	template<std::size_t Index_, class Arg_>
	[[nodiscard]] constexpr inline std::conditional_t
	<
		EmuMath::TMP::is_emu_new_vector_v<Arg_>,
		EmuMath::TMP::emu_vector_theoretical_return_t<Index_, Arg_>,
		Arg_&
	> _vector_mutate_get_theoretical_if_vector(Arg_& arg_)
	{
		if constexpr (EmuMath::TMP::is_emu_new_vector_v<Arg_>)
		{
			return _vector_get_theoretical<Index_>(arg_);
		}
		else
		{
			return arg_;
		}
	}
	template<std::size_t Index_, class Arg_>
	[[nodiscard]] constexpr inline std::conditional_t
	<
		EmuMath::TMP::is_emu_new_vector_v<Arg_>,
		EmuMath::TMP::emu_vector_theoretical_return_t<Index_, const Arg_>,
		const Arg_&
	> _vector_mutate_get_theoretical_if_vector(const Arg_& arg_)
	{
		if constexpr (EmuMath::TMP::is_emu_new_vector_v<Arg_>)
		{
			return _vector_get_theoretical<Index_>(arg_);
		}
		else
		{
			return arg_;
		}
	}

	template<std::size_t Index_, typename Arg_>
	struct _vector_mutate_get_theoretical_if_vector_result
	{
		using type = decltype(_vector_mutate_get_theoretical_if_vector<Index_>(std::declval<Arg_>()));
	};
	template<std::size_t Index_, typename Arg_>
	using _vector_mutate_get_theoretical_if_vector_result_t = typename _vector_mutate_get_theoretical_if_vector_result<Index_, Arg_>::type;
#pragma endregion

#pragma region CHECKING_FUNCS
	// Returns true if a the provided mutation Func_, when supplied with the provided Args_, is invocable and returns a type compatible with OutVector::value_type.
	// --- Additionally, triggers a static_assert if returning false
	template<std::size_t ArgIndex_, class OutVector_, class Func_, class...Args_>
	[[nodiscard]] constexpr inline bool _assert_vector_mutate_is_valid_invocation()
	{
		if constexpr (std::is_invocable_v<Func_, _vector_mutate_get_theoretical_if_vector_result_t<ArgIndex_, Args_>...>)
		{
			using invoke_result = std::invoke_result_t<Func_, _vector_mutate_get_theoretical_if_vector_result_t<ArgIndex_, Args_>...>;
			if constexpr (EmuCore::TMP::is_compatible_v<typename OutVector_::value_type, invoke_result>)
			{
				return true;
			}
			else
			{
				static_assert(false, "Attempted to mutate an EmuMath Vector, but at least one iteration of mutation resulted in the mutation function providing a result that cannot be used to copy to the output Vector's value_type.");
				return false;
			}
		}
		else
		{
			static_assert(false, "Attempted to mutate an EmuMath Vector, but at least one iteration of mutation resulted in arguments which the provided mutation function does not support.");
			return false;
		}
	}

	// Returns true if a the provided mutation Func_, when supplied with the provided Args_, 
	// is invocable and returns a type which OutVector::value_type can be constructed from.
	template<std::size_t ArgIndex_, class OutVector_, class Func_, class...Args_>
	[[nodiscard]] constexpr inline bool _vector_mutate_is_valid_invocation_for_construction()
	{
		if constexpr (std::is_invocable_v<Func_, _vector_mutate_get_theoretical_if_vector_result_t<ArgIndex_, Args_>...>)
		{
			using invoke_result = std::invoke_result_t<Func_, _vector_mutate_get_theoretical_if_vector_result_t<ArgIndex_, Args_>...>;
			if constexpr (std::is_constructible_v<typename OutVector_::stored_type, invoke_result>)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			return false;
		}
	}

	template<std::size_t ArgIndex_, class Func_, class...Args_>
	[[nodiscard]] constexpr inline std::invoke_result_t<Func_, _vector_mutate_get_theoretical_if_vector_result_t<ArgIndex_, Args_>...> _vector_mutate_invoke_func(Func_ func_, Args_&&...args_)
	{
		return func_(_vector_mutate_get_theoretical_if_vector<ArgIndex_>(std::forward<Args_>(args_))...);
	}


	template<class OutVector_, class Func_, std::size_t CurrentIndex_, std::size_t BeginIndex_, std::size_t EndIndex_, std::size_t ArgIndex_, class...Args_>
	[[nodiscard]] constexpr inline auto _vector_mutate_get_construction_arg(Func_ func_, Args_&&...args_)
	{
		if constexpr ((CurrentIndex_ >= BeginIndex_) && (CurrentIndex_ < EndIndex_))
		{
			if constexpr (_vector_mutate_is_valid_invocation_for_construction<ArgIndex_, OutVector_, Func_&, Args_...>())
			{
				return _vector_mutate_invoke_func<ArgIndex_, Func_&>(func_, std::forward<Args_>(args_)...);
			}
			else
			{
				static_assert(false, "Attempted to get an EmuMath Vector construction arg from mutation for an index which is to be mutated, but the output Vector's elements are not compatible with the result of mutation invocation.");
			}
		}
		else
		{
			using out_stored_type = typename OutVector_::stored_type;
			using out_value_uq = typename OutVector_::value_type_uq;
			if constexpr (std::is_constructible_v<out_stored_type, out_stored_type> && std::is_default_constructible_v<out_stored_type>)
			{
				return out_stored_type();
			}
			else if constexpr (std::is_constructible_v<out_stored_type, out_value_uq> && std::is_default_constructible_v<out_value_uq>)
			{
				return out_value_uq();
			}
			else
			{
				static_assert(false, "Attempted to get an EmuMath Vector construction arg from mutation for an index which will not be mutated, but the output Vector cannot have its stored_type constructed from the Vector's stored_type or value_type_uq, or if it can then neither of said types can be default-constructed.");
			}
		}
	}

	template<std::size_t OutIndex_, std::size_t ArgIndex_, std::size_t MutBeginIndex_, std::size_t MutEndIndex_, class OutVector_, class Func_, class...Args_>
	[[nodiscard]] constexpr inline bool _vector_mutate_valid_for_partial_construction()
	{
		if constexpr (OutIndex_ >= MutBeginIndex_ && OutIndex_ < MutEndIndex_)
		{
			return _vector_mutate_is_valid_invocation_for_construction<ArgIndex_, OutVector_, Func_&, Args_...>();
		}
		else
		{
			using out_stored_type = typename OutVector_::stored_type;
			using out_value_uq = typename OutVector_::value_type_uq;
			return
			(
				(std::is_constructible_v<out_stored_type, out_stored_type> && std::is_default_constructible_v<out_stored_type>) ||
				(std::is_constructible_v<out_stored_type, out_value_uq> && std::is_default_constructible_v<out_value_uq>)
			);
		}
	}
	template<class OutVector_, class Func_, std::size_t MutBeginIndex_, std::size_t MutEndIndex_, class...Args_, std::size_t...OutIndices_, std::size_t...ArgIndices_>
	[[nodiscard]] constexpr inline bool _vector_mutate_valid_for_partial_construction
	(
		std::index_sequence<OutIndices_...> out_indices_,
		std::index_sequence<ArgIndices_...> arg_indices_
	)
	{
		return EmuCore::TMP::variadic_and_v
		<
			_vector_mutate_valid_for_partial_construction<OutIndices_, ArgIndices_, MutBeginIndex_, MutEndIndex_, OutVector_, Func_&, Args_...>()...
		>;
	}

	template<class OutVector_, class Func_, std::size_t BeginIndex_, std::size_t EndIndex_, std::size_t ArgIndex_, class...Args_>
	[[nodiscard]] constexpr inline bool _vector_mutate_valid_for_partial_construction()
	{
		using out_vector_uq = EmuCore::TMP::remove_ref_cv_t<OutVector_>;
		if constexpr (BeginIndex_ < out_vector_uq::size)
		{
			// No need to check for 0-size since BeginIndex_ cannot be < 0.

			using arg_indices_before_mutation = EmuCore::TMP::make_duplicated_index_sequence<ArgIndex_, BeginIndex_>;
			using arg_indices_during_after_mutation = EmuCore::TMP::make_offset_index_sequence<BeginIndex_, out_vector_uq::size - BeginIndex_>;
			using all_arg_indices = EmuCore::TMP::splice_index_sequences_t<arg_indices_before_mutation, arg_indices_during_after_mutation>;
			return _vector_mutate_valid_for_partial_construction<OutVector_, Func_&, BeginIndex_, EndIndex_, Args_...>
			(
				std::make_index_sequence<out_vector_uq::size>(),
				all_arg_indices()
			);
		}
		else
		{
			// Can't produce a clear test due to invalid index, but no assertion as this isn't an _assert func
			return false;
		}
	}
#pragma endregion

#pragma region HELPER_TYPES
	// Type to check if any index in a full list of indices is not contained within the provided Vector_ type
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

	// Type used to check if a full sequence of mutation results can be used to construct the desired OutVector
	template<class OutVector_, class Func_, class ArgIndexSequence_, class...Args_>
	struct _is_constructible_from_mutation_results
	{
		static constexpr bool value = false;
	};
	template<class OutVector_, class Func_, std::size_t...ArgIndices_, class...Args_>
	struct _is_constructible_from_mutation_results<OutVector_, Func_, std::index_sequence<ArgIndices_...>, Args_...>
	{
	private:
		using out_stored_type = typename OutVector_::stored_type;

		template<std::size_t...AllIndices_>
		struct _valid_for_arg_indices
		{
			static constexpr bool value = false;
		};
		template<std::size_t FirstIndex_, std::size_t...RemainingIndices_>
		struct _valid_for_arg_indices<FirstIndex_, RemainingIndices_...>
		{
			static constexpr bool value = _valid_for_arg_indices<FirstIndex_>::value ? _valid_for_arg_indices<RemainingIndices_...>::value : false;
		};
		template<std::size_t Index_>
		struct _valid_for_arg_indices<Index_>
		{
			static constexpr bool value = _vector_mutate_is_valid_invocation_for_construction<Index_, OutVector_, Func_, Args_...>();
		};
		template<>
		struct _valid_for_arg_indices<>
		{
			static constexpr bool value = true;
		};

	public:
		static constexpr bool value = _valid_for_arg_indices<ArgIndices_...>::value;
	};
#pragma endregion

#pragma region SHUFFLES
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
#pragma endregion

#pragma region MUTATION_FUNCS
	template<std::size_t Index_, std::size_t EndIndex_, std::size_t ArgIndex_, class Func_, class OutVector_, class...Args_>
	constexpr inline void _vector_mutate_execution(Func_& func_, OutVector_& out_vector_, Args_&&...args_)
	{
		if constexpr (Index_ < EndIndex_)
		{
			if constexpr (_assert_vector_mutate_is_valid_invocation<ArgIndex_, OutVector_, Func_, Args_...>())
			{
				_vector_copy_index<Index_>(out_vector_, _vector_mutate_invoke_func<ArgIndex_, Func_&>(func_, std::forward<Args_>(args_)...));
				_vector_mutate_execution<Index_ + 1, EndIndex_, ArgIndex_ + 1, Func_, OutVector_>(func_, out_vector_, std::forward<Args_>(args_)...);
			}
			else
			{
				static_assert(false, "Unable to mutate an EmuMath Vector. Review previous assertions.");
			}
		}
	}

	template<class Func_, class OutVector_, std::size_t BeginIndex_, std::size_t EndIndex_, std::size_t ArgIndex_, class...Args_>
	constexpr inline void _vector_mutate(Func_ func_, OutVector_& out_vector_, Args_&&...args_)
	{
		if constexpr (BeginIndex_ < OutVector_::size)
		{
			constexpr std::size_t clamped_end_index_ = (EndIndex_ <= OutVector_::size) ? EndIndex_ : OutVector_::size;
			if constexpr (BeginIndex_ <= clamped_end_index_)
			{
				_vector_mutate_execution<BeginIndex_, clamped_end_index_, ArgIndex_, Func_, OutVector_>(func_, out_vector_, std::forward<Args_>(args_)...);
			}
			else
			{
				static_assert(false, "Attempted to mutate an EmuMath Vector, but the provided BeginIndex_ is greater than the provided EndIndex_ after clamping.");
			}
		}
		else
		{
			static_assert(false, "Attempted to mutate an EmuMath Vector, but the provided BeginIndex_ is greater than the highest valid index within the Vector. The inclusive valid index range is 0:size-1.");
		}
	}

	template<class OutVector_, class Func_, class...Args_, std::size_t...ArgIndices_>
	[[nodiscard]] constexpr inline OutVector_ _vector_mutate_return_out_from_construct
	(
		std::index_sequence<ArgIndices_...> arg_indices_,
		Func_ func_,
		Args_&&...args_
	)
	{
		// Args will be forwarded when passed on func invocation; knowing this, we can settle r-value references here
		return OutVector_(_vector_mutate_invoke_func<ArgIndices_, Func_&>(func_, std::forward<Args_>(args_)...)...);
	}

	template<class OutVector_, class Func_, std::size_t MutBeginIndex_, std::size_t MutEndIndex_, class...Args_, std::size_t...OutIndices_, std::size_t...ArgIndices_>
	[[nodiscard]] constexpr inline OutVector_ _vector_mutate_do_partial_mut_construction
	(
		std::index_sequence<OutIndices_...> out_indices_,
		std::index_sequence<ArgIndices_...> arg_indices_,
		Func_ func_,
		Args_&&...args_
	)
	{
		return OutVector_
		(
			_vector_mutate_get_construction_arg<OutVector_, Func_&, OutIndices_, MutBeginIndex_, MutEndIndex_, ArgIndices_>
			(
				func_,
				std::forward<Args_>(args_)...
			)...
		);
	}

	template<class OutVector_, class Func_, std::size_t BeginIndex_, std::size_t EndIndex_, std::size_t ArgIndex_, class...Args_>
	[[nodiscard]] constexpr inline OutVector_ _vector_mutate_return_out(Func_ func_, Args_&&...args_)
	{
		using out_vector_uq = EmuCore::TMP::remove_ref_cv_t<OutVector_>;
		if constexpr (BeginIndex_ == 0 && EndIndex_ >= out_vector_uq::size)
		{
			constexpr std::size_t clamped_end_index_ = out_vector_uq::size; // We already know clamped is this as we're doing a full mutation
			constexpr std::size_t num_calls_ = clamped_end_index_ - BeginIndex_;

			// Full mutation, so we can potentially output straight to a constructor
			using arg_index_sequence = EmuCore::TMP::make_offset_index_sequence<ArgIndex_, num_calls_>;
			if constexpr (_is_constructible_from_mutation_results<OutVector_, Func_&, arg_index_sequence, Args_...>::value)
			{
				return _vector_mutate_return_out_from_construct<OutVector_, Func_&>(arg_index_sequence(), func_, std::forward<Args_>(args_)...);
			}
			else if constexpr(std::is_default_constructible_v<OutVector_>)
			{
				// Default-copy-return approach; not preferable in terms of performance, but is the only option with minimal info
				OutVector_ out_vector_ = OutVector_();
				_vector_mutate<Func_&, OutVector_, BeginIndex_, EndIndex_, ArgIndex_>(func_, out_vector_, std::forward<Args_>(args_)...);
				return out_vector_;
			}
			else
			{
				static_assert(false, "Attempted to fully mutate an EmuMath Vector without passing an out_vector_ to output to. This is only allowed when the provided output Vector is constructible from all mutation function results, or is default-constructible.");
			}
		}
		else
		{
			// We output defaults to the constructor where no mutations are performed, 
			if constexpr (_vector_mutate_valid_for_partial_construction<OutVector_, Func_&, BeginIndex_, EndIndex_, ArgIndex_, Args_...>())
			{
				using arg_indices_before_mutation = EmuCore::TMP::make_duplicated_index_sequence<ArgIndex_, BeginIndex_>;
				using arg_indices_during_after_mutation = EmuCore::TMP::make_offset_index_sequence<ArgIndex_, OutVector_::size - BeginIndex_>;
				using all_arg_indices = EmuCore::TMP::splice_index_sequences_t<arg_indices_before_mutation, arg_indices_during_after_mutation>;
				return _vector_mutate_do_partial_mut_construction<OutVector_, Func_&, BeginIndex_, EndIndex_>
				(
					std::make_index_sequence<OutVector_::size>(),
					all_arg_indices(),
					func_,
					std::forward<Args_>(args_)...
				);
			}
			else if constexpr (std::is_default_constructible_v<OutVector_>)
			{
				OutVector_ out_vector_ = OutVector_();
				_vector_mutate<Func_&, OutVector_, BeginIndex_, EndIndex_, ArgIndex_>(func_, out_vector_, std::forward<Args_>(args_)...);
				return out_vector_;
			}
			else
			{
				static_assert(false, "Attempted to partially mutate an EmuMath Vector without passing an out_vector_ to output to. This is only allowed where the provided output Vector is default-constructible, or can be constructed from mutation results at the mutation indices and from default stored_type or value_type_uq items.");
			}
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
			Func_ func_ = Func_();
			return _vector_mutate_return_out<OutVector_, Func_&, BeginIndex_, EndIndex_, ArgIndex_>(func_, std::forward<Args_>(args_)...);
		}
		else
		{
			static_assert(false, "Attempted to mutate an EmuMath Vector without passing a func_ argument to perform mutation. This is only allowed where the provided Func_ type is default-constructible.");
		}
	}

	template<class Func_, class OutVector_, class InVector_, std::size_t BeginIndex_, std::size_t EndIndex_, std::size_t ArgIndex_, class...Args_>
	constexpr inline void _vector_partial_mutation_copy(Func_ func_, OutVector_& out_vector_, InVector_&& in_vector_, Args_&&...args_)
	{
		using out_vector_uq = EmuCore::TMP::remove_ref_cv_t<OutVector_>;
		if constexpr (BeginIndex_ != 0 || EndIndex_ < out_vector_uq::size)
		{
			// Copy 0:mutation_begin
			if constexpr (BeginIndex_ > 0)
			{
				_vector_copy<0, BeginIndex_, 0, InVector_>(out_vector_, in_vector_);
			}

			// Copy in mutated values
			// --- If BeginIndex_ == EndIndex_, no updates will be made.
			if constexpr (BeginIndex_ != EndIndex_)
			{
				_vector_mutate<Func_&, OutVector_, BeginIndex_, EndIndex_, ArgIndex_>(func_, out_vector_, std::forward<Args_>(args_)...);
			}

			// Copy EndIndex_:size values if there's anything left
			if constexpr (EndIndex_ < out_vector_uq::size)
			{
				_vector_copy<EndIndex_, out_vector_uq::size, EndIndex_, InVector_>(out_vector_, in_vector_);
			}
		}
		else
		{
			// Specified mutation range is the full range of our Vector, so we can just do a mutation instead
			_vector_mutate<Func_&, OutVector_, BeginIndex_, EndIndex_, ArgIndex_>(func_, out_vector_, std::forward<Args_>(args_)...);
		}
	}

	template<class Func_, class OutVector_, class InVector_, std::size_t BeginIndex_, std::size_t EndIndex_, std::size_t ArgIndex_, class...Args_>
	constexpr inline void _vector_partial_mutation_copy_no_func_passed(OutVector_& out_vector_, InVector_&& in_vector_, Args_&&...args_)
	{
		if constexpr (std::is_default_constructible_v<Func_>)
		{
			Func_ func_ = Func_();
			_vector_partial_mutation_copy<Func_&, OutVector_, InVector_, BeginIndex_, EndIndex_, ArgIndex_>
			(
				func_,
				out_vector_,
				std::forward<InVector_>(in_vector_),
				std::forward<Args_>(args_)...
			);
		}
		else
		{
			static_assert(false, "Attempted to perform a hybrid copy/mutate function on an EmuMath Vector without passing a func_ argument to perform mutation. This is only allowed where the provided Func_ type is default-constructible.");
		}
	}

	template<std::size_t OutSize_, typename OutT_, class Func_, class InVector_, std::size_t BeginIndex_, std::size_t EndIndex_, std::size_t ArgIndex_, class...Args_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> _vector_partial_mutation_copy_return_result(Func_ func_, InVector_&& in_vector_, Args_&&...args_)
	{
		using out_vector = EmuMath::NewVector<OutSize_, OutT_>;
		if constexpr ((BeginIndex_ == 0) && (EndIndex_ >= out_vector::size))
		{
			// Mutation range covers all indices, so we don't need to worry about copying and instead defer for mutation optimisations
			// --- in_vector_ is not considered an arg_; not forwarding it is intended
			return _vector_mutate_return_out<out_vector, Func_&, BeginIndex_, EndIndex_, ArgIndex_>(func_, std::forward<Args_>(args_)...);
		}
		else if constexpr (std::is_default_constructible_v<out_vector>)
		{
			// Defer to partial mutation copy as we can't optimise to just a mutation
			out_vector out_vector_ = out_vector();
			_vector_partial_mutation_copy<Func_&, out_vector, InVector_, BeginIndex_, EndIndex_, ArgIndex_>
			(
				func_,
				out_vector_,
				std::forward<InVector_>(in_vector_),
				std::forward<Args_>(args_)...
			);
			return out_vector_;
		}
		else
		{
			static_assert(false, "Attempted to create a new EmuMath Vector for output as a hybrid copy/mutate function, but the desired output type is not default-constructible. Output Vectors must be default-constructible.");
		}
	}

	template<std::size_t OutSize_, typename OutT_, class Func_, class InVector_, std::size_t BeginIndex_, std::size_t EndIndex_, std::size_t ArgIndex_, class...Args_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> _vector_partial_mutation_copy_args_only(InVector_&& in_vector_, Args_&&...args_)
	{
		using out_vector = EmuMath::NewVector<OutSize_, OutT_>;
		if constexpr ((BeginIndex_ == 0) && (EndIndex_ >= out_vector::size))
		{
			// Mutation range covers all indices, so we don't need to worry about copying and instead defer for mutation optimisations
			// --- in_vector_ is not considered an arg_; not forwarding it is intended
			return _vector_mutate_args_only<Func_, out_vector, BeginIndex_, EndIndex_, ArgIndex_>(std::forward<Args_>(args_)...);
		}
		else if constexpr (std::is_default_constructible_v<out_vector>)
		{
			if constexpr (std::is_default_constructible_v<Func_>)
			{
				out_vector out_vector_ = out_vector();
				Func_ func_ = Func_();
				_vector_partial_mutation_copy<Func_&, out_vector, InVector_, BeginIndex_, EndIndex_, ArgIndex_>
				(
					func_,
					out_vector_,
					std::forward<InVector_>(in_vector_),
					std::forward<Args_>(args_)...
				);
				return out_vector_;
			}
			else
			{
				static_assert(false, "Attempted to perform a hybrid copy/mutate function on an EmuMath Vector without passing a func_ argument to perform mutation. This is only allowed where the provided Func_ type is default-constructible.");
			}
		}
		else
		{
			static_assert(false, "Attempted to create a new EmuMath Vector for output as a hybrid copy/mutate function, but the desired output type is not default-constructible. Output Vectors must be default-constructible.");
		}
	}
#pragma endregion
}

#endif
