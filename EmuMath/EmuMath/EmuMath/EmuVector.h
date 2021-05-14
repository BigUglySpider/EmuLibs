#ifndef EMU_MATH_VECTOR_H_INC_
#define EMU_MATH_VECTOR_H_INC_

#include "_do_not_manually_include/EmuVector2T.h"
#include <ostream>

namespace EmuMath
{
	/// <summary> 2-dimensional vector of floats. </summary>
	using Vector2f = EmuMath::Vector2<float>;
	/// <summary> 2-dimensional vector of doubles. </summary>
	using Vector2d = EmuMath::Vector2<double>;
	/// <summary> 2-dimensional vector of long doubles. </summary>
	using Vector2ld = EmuMath::Vector2<long double>;
	/// <summary> 2-dimensional vector of 8-bit signed integers. </summary>
	using Vector2si8 = EmuMath::Vector2<std::int8_t>;
	/// <summary> 2-dimensional vector of 16-bit signed integers. </summary>
	using Vector2si16 = EmuMath::Vector2<std::int16_t>;
	/// <summary> 2-dimensional vector of 32-bit signed integers. </summary>
	using Vector2si32 = EmuMath::Vector2<std::int32_t>;
	/// <summary> 2-dimensional vector of 64-bit signed integers. </summary>
	using Vector2si64 = EmuMath::Vector2<std::int64_t>;
	/// <summary> 2-dimensional vector of 8-bit unsigned integers. </summary>
	using Vector2ui8 = EmuMath::Vector2<std::uint8_t>;
	/// <summary> 2-dimensional vector of 16-bit unsigned integers. </summary>
	using Vector2ui16 = EmuMath::Vector2<std::uint16_t>;
	/// <summary> 2-dimensional vector of 32-bit unsigned integers. </summary>
	using Vector2ui32 = EmuMath::Vector2<std::uint32_t>;
	/// <summary> 2-dimensional vector of 64-bit unsigned integers. </summary>
	using Vector2ui64 = EmuMath::Vector2<std::uint64_t>;
	/// <summary> 2-dimensional vector of std::size_t elements. </summary>
	using Vector2size_t = EmuMath::Vector2<std::size_t>;
}

template<typename T>
std::ostream& operator<<(std::ostream& stream, const EmuMath::Vector2<T>& emuVector)
{
	stream << "{ " << emuVector.x << ", " << emuVector.y << " }";
	return stream;
}

#endif
