#ifndef EMU_MATH_VECTOR_COPY_UNDERLYING_H_INC_
#define EMU_MATH_VECTOR_COPY_UNDERLYING_H_INC_ 1

#include "_vector_tmp.h"
#include "_vector_get_underlying.h"
#include "../../../../EmuCore/TMPHelpers/VariadicHelpers.h"

namespace EmuMath::Helpers::_vector_underlying
{
	template<class OutVector_, class In_>
	[[nodiscard]] constexpr inline OutVector_ _vector_copy(In_&& in_)
	{
		if constexpr (std::is_constructible_v<OutVector_, decltype(std::forward<In_>(in_))>)
		{
			return OutVector_(std::forward<In_>(in_));
		}
		else
		{
			static_assert
			(
				EmuCore::TMP::get_false<In_>(),
				"Attempted to copy to a new EmuMath Vector, but the provided output Vector cannot be constructed from the provided In_ argument."
			);
		}
	}

#pragma region ASSIGNMENT_COPY
	template<std::size_t OutIndex_, std::size_t ArgIndex_, bool AllowScalarMove_, class OutVector_, class In_, bool DoAssertions_>
	[[nodiscard]] constexpr inline bool _vector_copy_index_is_valid()
	{
		if constexpr (OutIndex_ < EmuCore::TMP::remove_ref_cv_t<OutVector_>::size)
		{
			using in_uq = EmuCore::TMP::remove_ref_cv_t<In_>;
			using out_get_result = decltype(_vector_get<OutIndex_>(EmuCore::TMP::lval_ref_cast<OutVector_>(std::forward<OutVector_>(std::declval<OutVector_>()))));
			using out_get_result_uq = EmuCore::TMP::remove_ref_cv_t<out_get_result>;
			constexpr bool out_get_is_arithmetic_ = std::is_arithmetic_v<out_get_result_uq>;

			if constexpr (EmuMath::TMP::is_emu_vector_v<In_>)
			{
				using in_lval_ref_type = decltype(EmuCore::TMP::lval_ref_cast<In_>(std::forward<In_>(std::declval<In_>())));
				using in_get_result = decltype(_vector_get_theoretical<ArgIndex_>(EmuCore::TMP::lval_ref_cast<In_>(std::forward<In_>(std::declval<In_>()))));
				using in_get_result_uq = EmuCore::TMP::remove_ref_cv_t<in_get_result>;

				if constexpr (EmuMath::TMP::is_emu_vector_v<out_get_result> && !EmuMath::TMP::is_emu_vector_v<in_get_result>)
				{
					// Defer to deepest level of the output Vector to mimic construction
					if constexpr (AllowScalarMove_)
					{
						using forward_in_result = decltype(std::forward<In_>(std::declval<In_>()));
						return _vector_copy_index_is_valid<0, ArgIndex_, AllowScalarMove_, OutVector_, forward_in_result, DoAssertions_>();
					}
					else
					{
						return _vector_copy_index_is_valid<0, ArgIndex_, AllowScalarMove_, OutVector_, in_lval_ref_type, DoAssertions_>();
					}
				}
				else
				{
					using out_value_uq = typename EmuCore::TMP::remove_ref_cv_t<OutVector_>::value_type_uq;
					if constexpr (std::is_lvalue_reference_v<In_> || ArgIndex_ > in_uq::size)
					{
						if constexpr (EmuCore::TMP::valid_assign_direct_or_cast<out_value_uq, in_get_result, out_get_result>())
						{
							return true;
						}
						else
						{
							static_assert(!DoAssertions_, "Attempted to copy-assign to an existing EmuMath Vector via another EmuMath Vector, but at least one index could not be assigned from the element at the provided ArgIndex_ within the passed input Vector, and a conversion to assign via the output Vector's value_type_uq could not successfully be performed.");
							return false;
						}
					}
					else
					{
						// Moving values from Vector
						// --- We don't care about AllowScalarMove_ as this works iteratively and should not strike the same index twice;
						// --- it is purely for protecting the passed argument itself, not its contained data
						using move_in_result = decltype
						(
							std::move
							(
								_vector_get_theoretical<ArgIndex_>(EmuCore::TMP::lval_ref_cast<In_>(std::forward<In_>(std::declval<In_>())))
							)
						);
						if constexpr (EmuCore::TMP::valid_assign_direct_or_cast<out_value_uq, move_in_result, out_get_result>())
						{
							return true;
						}
						else
						{
							static_assert(!DoAssertions_, "Attempted to move/copy-assign to an existing EmuMath Vector via a moveable EmuMath Vector, but at least one index could not be assigned from the element (after moving) at the provided ArgIndex_ within the passed input Vector, and a conversion to assign via the output Vector's value_type_uq could not successfully be performed.");
							return false;
						}
					}
				}
			}
			else
			{
				constexpr bool both_arithmetic_ = out_get_is_arithmetic_ && std::is_arithmetic_v<in_uq>;
				if constexpr (std::is_lvalue_reference_v<In_> || !AllowScalarMove_)
				{
					using in_lval_ref_type = decltype(EmuCore::TMP::lval_ref_cast<In_>(std::forward<In_>(std::declval<In_>())));

					// Only allow copies
					if constexpr (std::is_assignable_v<out_get_result, in_lval_ref_type> && (!both_arithmetic_ || std::is_same_v<in_uq, out_get_result_uq>))
					{
						return true;
					}
					else
					{
						using out_value_uq = typename EmuCore::TMP::remove_ref_cv_t<OutVector_>::value_type_uq;
						if constexpr (std::is_assignable_v<out_get_result, out_value_uq>)
						{
							if constexpr (EmuCore::TMP::valid_construct_or_cast<out_value_uq, in_lval_ref_type>())
							{
								return true;
							}
							else
							{
								static_assert(!DoAssertions_, "Attempted to copy-assign to an existing EmuMath Vector, but at least one index could not be assigned from the provided non-Vector type, and the non-Vector type could not be used to construct or static_cast to the output Vector's value_type_uq.");
								return false;
							}
						}
						else
						{
							static_assert(!DoAssertions_, "Attempted to copy-assign to an existing EmuMath Vector, but at least one index could not be assigned from the provided non-Vector type, and it cannot be assigned from its own value_type_uq.");
							return false;
						}
					}
				}
				else
				{
					// Move, fallback to copy before value_type_uq fallback
					using move_result_type = decltype(std::move(std::declval<In_>()));
					constexpr bool allow_direct_assign_ = (!both_arithmetic_ || std::is_same_v<in_uq, out_get_result_uq>);
					if constexpr (std::is_assignable_v<out_get_result, move_result_type> && allow_direct_assign_)
					{
						return true;
					}
					else
					{
						using out_value_uq = typename EmuCore::TMP::remove_ref_cv_t<OutVector_>::value_type_uq;
						if constexpr (std::is_assignable_v<out_get_result, out_value_uq>)
						{
							if constexpr (EmuCore::TMP::valid_construct_or_cast<out_value_uq, move_result_type>())
							{
								return true;
							}
							else
							{
								static_assert(!DoAssertions_, "Attempted to move/copy-assign to an existing EmuMath Vector, but at least one index could not be assigned from the provided moveable non-Vector type after a std::move, and the moved result could not be used to construct or static_cast to the output Vector's value_type_uq.");
								return false;
							}
						}
						else
						{
							static_assert(!DoAssertions_, "Attempted to move/copy-assign to an existing EmuMath Vector, but at least one index could not be assigned from the provided moveable non-Vector type after a std::move, and it cannot be assigned via its own value_type_uq.");
							return false;
						}
					}
				}
			}
		}
		else
		{
			static_assert(!DoAssertions_, "Attempted to copy-assign to an existing EmuMath Vector, but one of the accessed indices is outside of the output Vector's valid range.");
			return false;
		}
	}

	template<std::size_t OutIndex_, std::size_t ArgIndex_ = 0, bool AllowScalarMove_ = true, class OutVector_, class In_>
	constexpr inline void _vector_copy_index(OutVector_& out_, In_&& in_)
	{
		if constexpr (OutIndex_ < EmuCore::TMP::remove_ref_cv_t<OutVector_>::size)
		{
			using in_uq = EmuCore::TMP::remove_ref_cv_t<In_>;
			using out_get_result = decltype(_vector_get<OutIndex_>(out_));
			using out_get_result_uq = EmuCore::TMP::remove_ref_cv_t<out_get_result>;
			constexpr bool out_get_is_arithmetic_ = std::is_arithmetic_v<out_get_result_uq>;

			if constexpr (EmuMath::TMP::is_emu_vector_v<In_>)
			{
				using in_lval_ref_type = decltype(EmuCore::TMP::lval_ref_cast<In_>(std::forward<In_>(in_)));
				in_lval_ref_type in_lval_ref_ = EmuCore::TMP::lval_ref_cast<In_>(std::forward<In_>(in_));
				using in_get_result = decltype(_vector_get_theoretical<ArgIndex_>(in_));
				using in_get_result_uq = EmuCore::TMP::remove_ref_cv_t<in_get_result>;

				if constexpr (EmuMath::TMP::is_emu_vector_v<out_get_result> && !EmuMath::TMP::is_emu_vector_v<in_get_result>)
				{
					// Defer to deepest level of the output Vector to mimic construction
					if constexpr (AllowScalarMove_)
					{
						_vector_copy_index<0, ArgIndex_, AllowScalarMove_>(_vector_get<OutIndex_>(out_), std::forward<In_>(in_));
					}
					else
					{
						_vector_copy_index<0, ArgIndex_, AllowScalarMove_>
						(
							_vector_get<OutIndex_>(out_),
							EmuCore::TMP::lval_ref_cast<In_>(std::forward<In_>(in_))
						);
					}
				}
				else
				{
					using out_value_uq = typename EmuCore::TMP::remove_ref_cv_t<OutVector_>::value_type_uq;
					if constexpr (std::is_lvalue_reference_v<In_> || ArgIndex_ > in_uq::size)
					{
						if constexpr (EmuCore::TMP::valid_assign_direct_or_cast<out_value_uq, in_get_result, out_get_result>())
						{
							EmuCore::TMP::assign_direct_or_cast<out_value_uq>
							(
								_vector_get<ArgIndex_>(out_),
								_vector_get_theoretical<ArgIndex_>(in_lval_ref_)
							);
						}
						else
						{
							static_assert
							(
								EmuCore::TMP::get_false<In_>(),
								"Attempted to copy-assign to an existing EmuMath Vector via another EmuMath Vector, but at least one index could not be assigned from the element at the provided ArgIndex_ within the passed input Vector, and a conversion to assign via the output Vector's value_type_uq could not successfully be performed."
							);
						}
					}
					else
					{
						// Moving values from Vector
						// --- We don't care about AllowScalarMove_ as this works iteratively and should not strike the same index twice;
						// --- it is purely for protecting the passed argument itself, not its contained data
						using move_in_result = decltype(std::move(_vector_get_theoretical<ArgIndex_>(in_lval_ref_)));
						if constexpr (EmuCore::TMP::valid_assign_direct_or_cast<out_value_uq, move_in_result, out_get_result>())
						{
							EmuCore::TMP::assign_direct_or_cast<out_value_uq>
							(
								_vector_get<ArgIndex_>(out_),
								std::move(_vector_get_theoretical<ArgIndex_>(in_lval_ref_))
							);
						}
						else
						{
							static_assert
							(
								EmuCore::TMP::get_false<In_>(),
								"Attempted to move/copy-assign to an existing EmuMath Vector via a moveable EmuMath Vector, but at least one index could not be assigned from the element (after moving) at the provided ArgIndex_ within the passed input Vector, and a conversion to assign via the output Vector's value_type_uq could not successfully be performed."
							);
						}
					}
				}
			}
			else
			{
				constexpr bool both_arithmetic_ = out_get_is_arithmetic_ && std::is_arithmetic_v<in_uq>;
				if constexpr (std::is_lvalue_reference_v<In_> || !AllowScalarMove_)
				{
					using in_lval_ref_type = decltype(EmuCore::TMP::lval_ref_cast<In_>(std::forward<In_>(in_)));
					in_lval_ref_type in_lval_ref_ = EmuCore::TMP::lval_ref_cast<In_>(std::forward<In_>(in_));

					// Only allow copies
					if constexpr (std::is_assignable_v<out_get_result, in_lval_ref_type> && (!both_arithmetic_ || std::is_same_v<in_uq, out_get_result_uq>))
					{
						_vector_get<OutIndex_>(out_) = in_lval_ref_;
					}
					else
					{
						using out_value_uq = typename EmuCore::TMP::remove_ref_cv_t<OutVector_>::value_type_uq;
						if constexpr (std::is_assignable_v<out_get_result, out_value_uq>)
						{
							if constexpr (EmuCore::TMP::valid_construct_or_cast<out_value_uq, in_lval_ref_type>())
							{
								_vector_get<OutIndex_>(out_) = EmuCore::TMP::construct_or_cast<out_value_uq, in_lval_ref_type>(in_lval_ref_);
							}
							else
							{
								static_assert
								(
									EmuCore::TMP::get_false<In_>(),
									"Attempted to copy-assign to an existing EmuMath Vector, but at least one index could not be assigned from the provided non-Vector type, and the non-Vector type could not be used to construct or static_cast to the output Vector's value_type_uq."
								);
							}
						}
						else
						{
							static_assert
							(
								EmuCore::TMP::get_false<In_>(),
								"Attempted to copy-assign to an existing EmuMath Vector, but at least one index could not be assigned from the provided non-Vector type, and it cannot be assigned from its own value_type_uq."
							);
						}
					}
				}
				else
				{
					// Move, fallback to copy before value_type_uq fallback
					using move_result_type = decltype(std::move(in_));
					constexpr bool allow_direct_assign_ = (!both_arithmetic_ || std::is_same_v<in_uq, out_get_result_uq>);
					if constexpr (std::is_assignable_v<out_get_result, move_result_type> && allow_direct_assign_)
					{
						_vector_get<OutIndex_>(out_) = std::move(in_);
					}
					else
					{
						using out_value_uq = typename EmuCore::TMP::remove_ref_cv_t<OutVector_>::value_type_uq;
						if constexpr (std::is_assignable_v<out_get_result, out_value_uq>)
						{
							if constexpr (EmuCore::TMP::valid_construct_or_cast<out_value_uq, move_result_type>())
							{
								_vector_get<OutIndex_>(out_) = EmuCore::TMP::construct_or_cast<out_value_uq, move_result_type>(std::move(in_));
							}
							else
							{
								static_assert
								(
									EmuCore::TMP::get_false<In_>(),
									"Attempted to move/copy-assign to an existing EmuMath Vector, but at least one index could not be assigned from the provided moveable non-Vector type after a std::move, and the moved result could not be used to construct or static_cast to the output Vector's value_type_uq."
								);
							}
						}
						else
						{
							static_assert
							(
								EmuCore::TMP::get_false<In_>(),
								"Attempted to move/copy-assign to an existing EmuMath Vector, but at least one index could not be assigned from the provided moveable non-Vector type after a std::move, and it cannot be assigned via its own value_type_uq."
							);
						}
					}
				}
			}
		}
		else
		{
			static_assert
			(
				EmuCore::TMP::get_false<std::size_t, OutIndex_>(),
				"Attempted to copy-assign to an existing EmuMath Vector, but one of the accessed indices is outside of the output Vector's valid range."
			);
		}
	}

	template<std::size_t Index_, std::size_t CopyBegin_, std::size_t CopyEnd_, std::size_t ReadOffset_, bool AllowScalarMove_, class OutVector_, class In_>
	constexpr inline void _vector_copy_index_in_range(OutVector_& out_, In_&& in_)
	{
		if constexpr (Index_ >= CopyBegin_ && Index_ < CopyEnd_)
		{
			_vector_copy_index<Index_, Index_ + ReadOffset_, AllowScalarMove_>(out_, std::forward<In_>(in_));
		}
	}

	template<std::size_t Index_, std::size_t CopyBegin_, std::size_t CopyEnd_, std::size_t ReadOffset_, bool AllowScalarMove_, class OutVector_, class In_, bool DoAssertions_>
	[[nodiscard]] constexpr inline bool _vector_copy_index_in_range_is_valid()
	{
		if constexpr (Index_ >= CopyBegin_ && Index_ < CopyEnd_)
		{
			return _vector_copy_index_is_valid<Index_, Index_ + ReadOffset_, AllowScalarMove_, OutVector_, In_, DoAssertions_>();
		}
		else
		{
			return true;
		}
	}

	template<std::size_t CopyBegin_, std::size_t CopyEnd_, std::size_t ReadOffset_, bool AllowScalarMove_, class OutVector_, class In_, bool DoAssertions_, std::size_t...Indices_>
	[[nodiscard]] constexpr inline bool _vector_copy_assign_execution_is_valid(std::index_sequence<Indices_...> indices_)
	{
		return EmuCore::TMP::variadic_and_v
		<
			_vector_copy_index_in_range_is_valid<Indices_, CopyBegin_, CopyEnd_, ReadOffset_, AllowScalarMove_, OutVector_, In_, DoAssertions_>()...
		>;
	}

	template<std::size_t CopyBegin_, std::size_t CopyEnd_, std::size_t ReadOffset_, bool AllowScalarMove_, class OutVector_, class In_, std::size_t...Indices_>
	constexpr inline void _vector_copy_assign_execution(std::index_sequence<Indices_...> indices_, OutVector_& out_, In_&& in_)
	{
		// We don't allow moves where a problem would occur, so silence false-positive VS warning here
#pragma warning(push)
#pragma warning(disable: 26800)
		(_vector_copy_index_in_range<Indices_, CopyBegin_, CopyEnd_, ReadOffset_, AllowScalarMove_>(out_, std::forward<In_>(in_)), ...);
#pragma warning(pop)
	}
	
	template<std::size_t CopyBegin_, std::size_t CopyEnd_, std::size_t ReadOffset_, class In_, std::size_t OutSize_, typename OutT_>
	constexpr inline void _vector_copy(EmuMath::Vector<OutSize_, OutT_>& out_, In_&& in_)
	{
		if constexpr (EmuMath::TMP::is_emu_vector_v<In_>)
		{
			constexpr bool allow_move_between_depths_ = EmuMath::Vector<OutSize_, OutT_>::depth <= EmuCore::TMP::remove_ref_cv_t<In_>::depth;
			_vector_copy_assign_execution<CopyBegin_, CopyEnd_, ReadOffset_, allow_move_between_depths_>(std::make_index_sequence<OutSize_>(), out_, std::forward<In_>(in_));
		}
		else
		{
			_vector_copy_assign_execution<CopyBegin_, CopyEnd_, ReadOffset_, false>(std::make_index_sequence<OutSize_>(), out_, std::forward<In_>(in_));
		}
	}

	template<std::size_t CopyBegin_, std::size_t CopyEnd_, std::size_t ReadOffset_, class In_, std::size_t OutSize_, typename OutT_, bool DoAssertions_>
	[[nodiscard]] constexpr inline bool _vector_copy_assign_is_valid()
	{
		using out_vector = EmuMath::Vector<OutSize_, OutT_>;
		using index_sequence = std::make_index_sequence<OutSize_>;
		if constexpr (EmuMath::TMP::is_emu_vector_v<In_>)
		{
			constexpr bool allow_move_between_depths_ = EmuMath::Vector<OutSize_, OutT_>::depth <= EmuCore::TMP::remove_ref_cv_t<In_>::depth;
			return _vector_copy_assign_execution_is_valid<CopyBegin_, CopyEnd_, ReadOffset_, allow_move_between_depths_, out_vector, In_, DoAssertions_>(index_sequence());
		}
		else
		{
			return _vector_copy_assign_execution_is_valid<CopyBegin_, CopyEnd_, ReadOffset_, false, out_vector, In_, DoAssertions_>(index_sequence());
		}
	}
#pragma endregion
}

#endif
