#ifndef EMU_MATH_NEW_VECTOR_MUTATION_H_INC_
#define EMU_MATH_NEW_VECTOR_MUTATION_H_INC_ 1

#include "_common_vector_helpers.h"

namespace EmuMath::Helpers
{
	/// <summary>
	/// <para> Creates a new EmuMath Vector, with the provided OutT_ used as the output Vector's T_ argument, via specified indices within the input vector_. </para>
	/// <para> The Size_ of the output Vector will be equal to the provided number of Indices_. </para>
	/// <para> OutT_ is optional, and defaults to the passed vector_'s value_type_uq. </para>
	/// <para> There is no upper limit for the amount of indices to be provided, but at least 1 argument must be provided for Indices_. </para>
	/// <para> This may not be used to access theoretical indices; for such behaviour, use `vector_shuffle_theoretical` instead. </para>
	/// </summary>
	/// <typeparam name="OutT_">T_ argument for the output Vector. Defaults to the passed vector_'s value_type_uq.</typeparam>
	/// <param name="vector_">EmuMath Vector to retrieve indices from.</param>
	/// <returns>EmuMath Vector with a number of elements equal to the number of Indices_ arguments, constructed from shuffled indices within the passed vector_.</returns>
	template<typename OutT_, std::size_t...Indices_, std::size_t Size_, typename T_, typename = std::enable_if_t<sizeof...(Indices_) != 0>>
	[[nodiscard]] constexpr inline EmuMath::NewVector<sizeof...(Indices_), OutT_> new_vector_shuffle(EmuMath::NewVector<Size_, T_>& vector_)
	{
		return _vector_underlying::_vector_shuffle<OutT_, false, Indices_...>(vector_);
	}
	template<std::size_t...Indices_, std::size_t Size_, typename T_, typename = std::enable_if_t<sizeof...(Indices_) != 0>>
	[[nodiscard]] constexpr inline EmuMath::NewVector<sizeof...(Indices_), typename EmuMath::NewVector<Size_, T_>::value_type_uq> new_vector_shuffle
	(
		EmuMath::NewVector<Size_, T_>& vector_
	)
	{
		return _vector_underlying::_vector_shuffle<typename EmuMath::NewVector<Size_, T_>::value_type_uq, false, Indices_...>(vector_);
	}

	template<typename OutT_, std::size_t...Indices_, std::size_t Size_, typename T_, typename = std::enable_if_t<sizeof...(Indices_) != 0>>
	[[nodiscard]] constexpr inline EmuMath::NewVector<sizeof...(Indices_), OutT_> new_vector_shuffle(const EmuMath::NewVector<Size_, T_>& vector_)
	{
		return _vector_underlying::_vector_shuffle<OutT_, false, Indices_...>(vector_);
	}
	template<std::size_t...Indices_, std::size_t Size_, typename T_, typename = std::enable_if_t<sizeof...(Indices_) != 0>>
	[[nodiscard]] constexpr inline EmuMath::NewVector<sizeof...(Indices_), typename EmuMath::NewVector<Size_, T_>::value_type_uq> new_vector_shuffle
	(
		const EmuMath::NewVector<Size_, T_>& vector_
	)
	{
		return _vector_underlying::_vector_shuffle<typename EmuMath::NewVector<Size_, T_>::value_type_uq, false, Indices_...>(vector_);
	}

	/// <summary>
	/// <para> Creates a new EmuMath Vector, with the provided OutT_ used as the output Vector's T_ argument, via specified theoretical indices within the input vector_. </para>
	/// <para> The Size_ of the output Vector will be equal to the provided number of Indices_. </para>
	/// <para> OutT_ is optional, and defaults to the passed vector_'s value_type_uq. </para>
	/// <para> There is no upper limit for the amount of indices to be provided, but at least 1 argument must be provided for Indices_. </para>
	/// <para> This may be used to access theoretical indices; to prohibit use of non-contained indices, use `vector_shuffle` instead. </para>
	/// </summary>
	/// <typeparam name="OutT_">T_ argument for the output Vector. Defaults to the passed vector_'s value_type_uq.</typeparam>
	/// <param name="vector_">EmuMath Vector to retrieve indices from.</param>
	/// <returns>EmuMath Vector with a number of elements equal to the number of Indices_ arguments, constructed from shuffled indices within the passed vector_.</returns>
	template<typename OutT_, std::size_t...Indices_, std::size_t Size_, typename T_, typename = std::enable_if_t<sizeof...(Indices_) != 0>>
	[[nodiscard]] constexpr inline EmuMath::NewVector<sizeof...(Indices_), OutT_> new_vector_shuffle_theoretical(EmuMath::NewVector<Size_, T_>& vector_)
	{
		return _vector_underlying::_vector_shuffle<OutT_, true, Indices_...>(vector_);
	}
	template<std::size_t...Indices_, std::size_t Size_, typename T_, typename = std::enable_if_t<sizeof...(Indices_) != 0>>
	[[nodiscard]] constexpr inline EmuMath::NewVector<sizeof...(Indices_), typename EmuMath::NewVector<Size_, T_>::value_type_uq> new_vector_shuffle_theoretical
	(
		EmuMath::NewVector<Size_, T_>& vector_
	)
	{
		return _vector_underlying::_vector_shuffle<typename EmuMath::NewVector<Size_, T_>::value_type_uq, true, Indices_...>(vector_);
	}

	template<typename OutT_, std::size_t...Indices_, std::size_t Size_, typename T_, typename = std::enable_if_t<sizeof...(Indices_) != 0>>
	[[nodiscard]] constexpr inline EmuMath::NewVector<sizeof...(Indices_), OutT_> new_vector_shuffle_theoretical(const EmuMath::NewVector<Size_, T_>& vector_)
	{
		return _vector_underlying::_vector_shuffle<OutT_, true, Indices_...>(vector_);
	}
	template<std::size_t...Indices_, std::size_t Size_, typename T_, typename = std::enable_if_t<sizeof...(Indices_) != 0>>
	[[nodiscard]] constexpr inline EmuMath::NewVector<sizeof...(Indices_), typename EmuMath::NewVector<Size_, T_>::value_type_uq> new_vector_shuffle_theoretical
	(
		const EmuMath::NewVector<Size_, T_>& vector_
	)
	{
		return _vector_underlying::_vector_shuffle<typename EmuMath::NewVector<Size_, T_>::value_type_uq, true, Indices_...>(vector_);
	}
}

#endif
