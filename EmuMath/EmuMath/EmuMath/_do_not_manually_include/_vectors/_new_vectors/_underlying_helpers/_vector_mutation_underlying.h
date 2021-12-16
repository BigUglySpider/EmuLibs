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
						using get_non_contained_return_type = typename InVector_::value_type_uq;
						if constexpr (std::is_constructible_v<out_stored_type, get_non_contained_return_type>)
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
}

#endif
