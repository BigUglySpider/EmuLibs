#ifndef EMU_MATH_VECTOR_STREAM_APPEND_UNDERLYING_H_INC_
#define EMU_MATH_VECTOR_STREAM_APPEND_UNDERLYING_H_INC_ 1

#include "_vector_get_underlying.h"
#include "_vector_tmp.h"

namespace EmuMath::Helpers::_vector_underlying
{
	template<std::size_t Index_, std::size_t EndIndex_, bool IsWide_, class StreamType_, std::size_t Size_, typename T_>
	constexpr inline void _vector_append_to_stream(StreamType_& str_, const EmuMath::NewVector<Size_, T_>& vector_)
	{
		if constexpr (Index_ < EndIndex_)
		{
			// Append using additional _vector_append layer if the Vector contains more Vectors
			// --- Allows this template to work with itself
			using get_result = decltype(_vector_get<Index_>(std::declval<EmuMath::NewVector<Size_, T_>>()));
			if constexpr (EmuMath::TMP::is_emu_new_vector_v<get_result>)
			{
				using get_result_uq = EmuCore::TMP::remove_ref_cv_t<get_result>;
				_vector_append_to_stream<0, get_result_uq::size, IsWide_, StreamType_>(str_, _vector_get<Index_>(vector_));
			}
			else
			{
				str_ << _vector_get<Index_>(vector_);
			}
			
			if constexpr ((Index_ + 1) != EndIndex_)
			{
				// Append separator if this is not the end, and recursively call next iteration
				if constexpr (IsWide_)
				{
					str_ << L", ";
				}
				else
				{
					str_ << ", ";
				}

				_vector_append_to_stream<Index_ + 1, EndIndex_, IsWide_, StreamType_, Size_, T_>(str_, vector_);
			}
		}
	}

	template<std::size_t EndIndex_, bool IsWide_,class StreamType_, std::size_t Size_, typename T_>
	constexpr inline void _vector_append_to_stream(StreamType_& str_, const EmuMath::NewVector<Size_, T_>& vector_)
	{
		// Open brace to indicate next elements will be contained within the same Vector.
		if constexpr (IsWide_)
		{
			str_ << L"{ ";
		}
		else
		{
			str_ << "{ ";
		}

		_vector_append_to_stream<0, EndIndex_, IsWide_, StreamType_, Size_, T_>(str_, vector_);

		// Close brace to indicate end of Vector.
		if constexpr (IsWide_)
		{
			str_ << L" }";
		}
		else
		{
			str_ << " }";
		}
	}

	template<bool IsWide_, class StreamType_, std::size_t Size_, typename T_>
	constexpr inline void _vector_append_to_stream(StreamType_& str_, const EmuMath::NewVector<Size_, T_>& vector_)
	{
		_vector_append_to_stream<EmuMath::NewVector<Size_, T_>::size, IsWide_, StreamType_, Size_, T_>(str_, vector_);
	}
}

#endif
