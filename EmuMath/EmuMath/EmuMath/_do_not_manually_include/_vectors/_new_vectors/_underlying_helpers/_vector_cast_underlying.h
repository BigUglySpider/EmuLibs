#ifndef EMU_MATH_NEW_VECTOR_CAST_UNDERLYING_H_INC_
#define EMU_MATH_NEW_VECTOR_CAST_UNDERLYING_H_INC_ 1

#include "_vector_tmp.h"
#include "_vector_get_underlying.h"
#include "../../../../../EmuCore/TMPHelpers/VariadicHelpers.h"

namespace EmuMath::Helpers::_vector_underlying
{
	template<std::size_t Index_, std::size_t OutSize_, typename OutT_, class InVector_>
	[[nodiscard]] constexpr inline typename EmuMath::NewVector<OutSize_, OutT_>::stored_type _vector_cast_make_stored_type(InVector_&& in_vector_)
	{
		using get_result = decltype(_vector_get_theoretical<Index_>(std::forward<InVector_>(in_vector_)));
		using out_stored_type = typename EmuMath::NewVector<OutSize_, OutT_>::stored_type;
		if constexpr (std::is_constructible_v<out_stored_type, get_result>)
		{
			return out_stored_type(_vector_get_theoretical<Index_>(std::forward<InVector_>(in_vector_)));
		}
		else if constexpr (EmuCore::TMP::is_static_castable_v<get_result, out_stored_type>)
		{
			return static_cast<out_stored_type>(_vector_get_theoretical<Index_>(std::forward<InVector_>(in_vector_)));
		}
		else
		{
			static_assert
			(
				EmuCore::TMP::get_false<OutT_>(),
				"Attempted to cast an EmuMath Vector to an alternative EmuMath Vector, but the output Vector's stored_type cannot be constructed from at least one of the input Vector's indices."
			);
		}
	}
	template<std::size_t OutSize_, typename OutT_, class InVector_, std::size_t...Indices_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> _vector_cast_execution(InVector_& in_vector_, std::index_sequence<Indices_...> indices_)
	{
		return EmuMath::NewVector<OutSize_, OutT_>
		(
			_vector_cast_make_stored_type<Indices_, OutSize_, OutT_, std::add_lvalue_reference_t<InVector_>>(in_vector_)...
		);
	}

	template<std::size_t OutSize_, typename OutT_, class InVector_, std::size_t Offset_>
	[[nodiscard]] constexpr inline EmuMath::NewVector<OutSize_, OutT_> _vector_cast(InVector_&& in_vector_)
	{
		constexpr bool in_is_lval_ref = std::is_lvalue_reference_v<InVector_>;
		constexpr bool out_contains_ref = EmuMath::NewVector<OutSize_, OutT_>::contains_ref;
		constexpr bool in_contains_ref = EmuCore::TMP::remove_ref_cv_t<InVector_>::contains_ref;

		// Only valid in the following circumstances:
		// --- 1: output does not contain references, meaning we don't need to worry about dangling references in the result
		// --- 2: input is an lvalue-reference, meaning we don't want to worry about temporaries
		// --- 3: output and input both contain references, meaning assignment from an rvalue Vector won't necessarily result in dangling references
		constexpr bool is_valid = !out_contains_ref || in_is_lval_ref || (out_contains_ref && in_contains_ref);

		if constexpr (is_valid)
		{
			// Safe to continue since the value is supposedly named, or we're not outputting references anyway
			return _vector_cast_execution<OutSize_, OutT_, decltype(EmuCore::TMP::lval_ref_cast<InVector_>(in_vector_))>
			(
				EmuCore::TMP::lval_ref_cast<InVector_>(in_vector_),
				EmuCore::TMP::make_offset_index_sequence<Offset_, OutSize_>()
			);
		}
		else
		{
			static_assert
			(
				EmuCore::TMP::get_false<InVector_>(),
				"Attempted to cast an EmuMath Vector rvalue-reference to a reference-containing EmuMath Vector. As an rvalue-reference is likely to be a temporary, this behaviour has been prohibited to prevent dangling references."
			);
		}
	}
}

#endif
