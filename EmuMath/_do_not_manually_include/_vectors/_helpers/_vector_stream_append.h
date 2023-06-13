#ifndef EMU_MATH_VECTOR_STREAM_APPEND_H_INC_
#define EMU_MATH_VECTOR_STREAM_APPEND_H_INC_ 1

#include "_common_vector_helpers.h"
#include <ostream>

// CONTAINS:
// --- stream_append

namespace EmuMath::Helpers
{
	/// <summary>
	/// <para> Appends the provided EmuMath Vector to the provided ostream. </para>
	/// <para> Follows the format "{ sequential_elements..., }". There is no separator after the final element. </para>
	/// </summary>
	/// <param name="str_">Standard output stream to append to.</param>
	/// <param name="vector_">EmuMath Vector to append to the provided stream.</param>
	/// <returns>Reference to the passed str_.</returns>
	template<std::size_t Size_, typename T_>
	inline std::ostream& vector_stream_append(std::ostream& str_, const EmuMath::Vector<Size_, T_>& vector_)
	{
		_vector_underlying::_vector_append_to_stream<false>(str_, vector_);
		return str_;
	}

	/// <summary>
	/// <para> Appends the provided EmuMath Vector to the provided wostream. </para>
	/// <para> Follows the format L"{ sequential_elements..., }". There is no separator after the final element. </para>
	/// </summary>
	/// <param name="w_str_">Standard wide output stream to append to.</param>
	/// <param name="vector_">EmuMath Vector to append to the provided wide stream.</param>
	/// <returns>Reference to the passed w_str_.</returns>
	template<std::size_t Size_, typename T_>
	inline std::wostream& vector_stream_append(std::wostream& w_str_, const EmuMath::Vector<Size_, T_>& vector_)
	{
		_vector_underlying::_vector_append_to_stream<true>(w_str_, vector_);
		return w_str_;
	}
}

template<std::size_t Size_, typename T_>
inline std::ostream& operator<<(std::ostream& str_, const EmuMath::Vector<Size_, T_>& vector_)
{
	return EmuMath::Helpers::vector_stream_append(str_, vector_);
}

template<std::size_t Size_, typename T_>
inline std::wostream& operator<<(std::wostream& w_str_, const EmuMath::Vector<Size_, T_>& vector_)
{
	return EmuMath::Helpers::vector_stream_append(w_str_, vector_);
}

#endif
