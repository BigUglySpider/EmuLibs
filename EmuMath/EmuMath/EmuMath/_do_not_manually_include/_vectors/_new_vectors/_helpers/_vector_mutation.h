#ifndef EMU_MATH_NEW_VECTOR_MUTATION_H_INC_
#define EMU_MATH_NEW_VECTOR_MUTATION_H_INC_ 1

#include "_common_vector_helpers.h"

namespace EmuMath::Helpers
{
	template<typename OutT_, std::size_t...Indices_, std::size_t Size_, typename T_, typename = std::enable_if_t<sizeof...(Indices_) != 0>>
	[[nodiscard]] constexpr inline EmuMath::NewVector<sizeof...(Indices_), OutT_> new_vector_shuffle(EmuMath::NewVector<Size_, T_>& vector_)
	{
		return _vector_underlying::_vector_shuffle<OutT_, false, Indices_...>(vector_);
	}
	template<std::size_t...Indices_, std::size_t Size_, typename T_, typename = std::enable_if_t<sizeof...(Indices_) != 0>>
	[[nodiscard]] constexpr inline EmuMath::NewVector<sizeof...(Indices_), T_> new_vector_shuffle(EmuMath::NewVector<Size_, T_>& vector_)
	{
		return _vector_underlying::_vector_shuffle<T_, false, Indices_...>(vector_);
	}

	template<typename OutT_, std::size_t...Indices_, std::size_t Size_, typename T_, typename = std::enable_if_t<sizeof...(Indices_) != 0>>
	[[nodiscard]] constexpr inline EmuMath::NewVector<sizeof...(Indices_), OutT_> new_vector_shuffle(const EmuMath::NewVector<Size_, T_>& vector_)
	{
		return _vector_underlying::_vector_shuffle<OutT_, false, Indices_...>(vector_);
	}
	template<std::size_t...Indices_, std::size_t Size_, typename T_, typename = std::enable_if_t<sizeof...(Indices_) != 0>>
	[[nodiscard]] constexpr inline EmuMath::NewVector<sizeof...(Indices_), T_> new_vector_shuffle(const EmuMath::NewVector<Size_, T_>& vector_)
	{
		return _vector_underlying::_vector_shuffle<T_, false, Indices_...>(vector_);
	}
}

#endif
