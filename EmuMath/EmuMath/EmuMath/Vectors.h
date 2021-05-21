#ifndef EMU_MATH_VECTOR_H_INC_
#define EMU_MATH_VECTOR_H_INC_

#include "_do_not_manually_include/EmuVector2T.h"
#include "_do_not_manually_include/EmuVector3T.h"
#include "_do_not_manually_include/EmuVector4T.h"
#include <ostream>

template<typename T>
std::ostream& operator<<(std::ostream& stream, const EmuMath::Vector2<T>& emuVector)
{
	stream << "{ " << emuVector.x << ", " << emuVector.y << " }";
	return stream;
}

template<typename T>
std::ostream& operator<<(std::ostream& stream, const EmuMath::Vector3<T>& emuVector)
{
	stream << "{ " << emuVector.x << ", " << emuVector.y << ", " << emuVector.z << " }";
	return stream;
}

template<typename T>
std::ostream& operator<<(std::ostream& stream, const EmuMath::Vector4<T>& emuVector)
{
	stream << "{ " << emuVector.x << ", " << emuVector.y << ", " << emuVector.z << ", " << emuVector.w << " }";
	return stream;
}

#endif
