#ifndef EMU_MATH_NEW_VECTOR_COPY_H_INC_
#define EMU_MATH_NEW_VECTOR_COPY_H_INC_ 1

#include "_common_vector_helpers.h"

namespace EmuMath::Helpers
{
	template<typename Arg_, std::size_t Size_, typename T_>
	constexpr inline void new_vector_copy(EmuMath::NewVector<Size_, T_>& out_vector_, Arg_& in_arg_)
	{
		_vector_underlying::_vector_copy<Arg_, Size_, T_>(out_vector_, in_arg_);
	}

	template<typename Arg_, std::size_t Size_, typename T_>
	constexpr inline void new_vector_copy(EmuMath::NewVector<Size_, T_>& out_vector_, const Arg_& in_arg_)
	{
		_vector_underlying::_vector_copy<const Arg_, Size_, T_>(out_vector_, in_arg_);
	}

	template<std::size_t BeginIndex_, std::size_t EndIndex_, typename Arg_, std::size_t Size_, typename T_>
	constexpr inline void new_vector_copy(EmuMath::NewVector<Size_, T_>& out_vector_, Arg_& in_arg_)
	{
		_vector_underlying::_vector_copy<BeginIndex_, EndIndex_, BeginIndex_, Arg_, Size_, T_>(out_vector_, in_arg_);
	}

	template<std::size_t BeginIndex_, std::size_t EndIndex_, typename Arg_, std::size_t Size_, typename T_>
	constexpr inline void new_vector_copy(EmuMath::NewVector<Size_, T_>& out_vector_, const Arg_& in_arg_)
	{
		_vector_underlying::_vector_copy<BeginIndex_, EndIndex_, BeginIndex_, const Arg_, Size_, T_>(out_vector_, in_arg_);
	}

	template<bool CopyNonContained_, typename Arg_, std::size_t Size_, typename T_>
	constexpr inline void new_vector_copy(EmuMath::NewVector<Size_, T_>& out_vector_, Arg_& in_arg_)
	{
		_vector_underlying::_vector_copy<CopyNonContained_, Arg_, Size_, T_>(out_vector_, in_arg_);
	}

	template<bool CopyNonContained_, typename Arg_, std::size_t Size_, typename T_>
	constexpr inline void new_vector_copy(EmuMath::NewVector<Size_, T_>& out_vector_, const Arg_& in_arg_)
	{
		_vector_underlying::_vector_copy<CopyNonContained_, const Arg_, Size_, T_>(out_vector_, in_arg_);
	}

	/// <summary>
	/// <para> Copies into the specified range within the provided out_vector_ via the provided in_arg_. </para>
	/// <para>
	///		If Arg_ is an EmuMath Vector: Copies iterating indices from in_arg_ to the current index of out_vector_. 
	///		The in_arg_ vector will begin reading from index 0. To instead begin reading from BeginIndex_, use `vector_copy` instead.
	/// </para>
	/// <para> If Arg_ is none of the above: Performs a normal copy of a scalar to all indices in the specified range. </para>
	/// <para> BeginIndex_ is the inclusive index to start writing to within out_vector_. This is a required template argument. </para>
	/// <para> EndIndex_ is the exclusive index at which to cease writing to out_vector_. This is optional, and defaults to the size of out_vector_. </para>
	/// <para> 
	///		If Arg_ is an EmuMath Vector and does not contain enough indices to fill the provided range, non-contained indices will be intepreted as implied-zeroes. 
	///		To only copy the contained indices within in_arg_, use `vector_copy_from_start_contained_only`.
	/// </para>
	/// </summary>
	/// <param name="out_vector_">EmuMath Vector to copy to.</param>
	/// <param name="in_arg_">EmuMath Vector or usable scalar to copy to value(s) from.</param>
	template<std::size_t BeginIndex_, std::size_t EndIndex_, typename Arg_, std::size_t Size_, typename T_>
	constexpr inline void new_vector_copy_from_start(EmuMath::NewVector<Size_, T_>& out_vector_, Arg_& in_arg_)
	{
		_vector_underlying::_vector_copy_from_start<BeginIndex_, EndIndex_, true, Arg_, Size_, T_>(out_vector_, in_arg_);
	}
	template<std::size_t BeginIndex_, typename Arg_, std::size_t Size_, typename T_>
	constexpr inline void new_vector_copy_from_start(EmuMath::NewVector<Size_, T_>& out_vector_, Arg_& in_arg_)
	{
		_vector_underlying::_vector_copy_from_start<BeginIndex_, EmuMath::NewVector<Size_, T_>::size, true, Arg_, Size_, T_>(out_vector_, in_arg_);
	}
	template<std::size_t BeginIndex_, std::size_t EndIndex_, typename Arg_, std::size_t Size_, typename T_>
	constexpr inline void new_vector_copy_from_start(EmuMath::NewVector<Size_, T_>& out_vector_, const Arg_& in_arg_)
	{
		_vector_underlying::_vector_copy_from_start<BeginIndex_, EndIndex_, true, const Arg_, Size_, T_>(out_vector_, in_arg_);
	}
	template<std::size_t BeginIndex_, typename Arg_, std::size_t Size_, typename T_>
	constexpr inline void new_vector_copy_from_start(EmuMath::NewVector<Size_, T_>& out_vector_, const Arg_& in_arg_)
	{
		_vector_underlying::_vector_copy_from_start<BeginIndex_, EmuMath::NewVector<Size_, T_>::size, true, const Arg_, Size_, T_>(out_vector_, in_arg_);
	}

	/// <summary>
	/// <para> Copies into the specified range within the provided out_vector_ via the provided in_arg_. </para>
	/// <para>
	///		If Arg_ is an EmuMath Vector: Copies iterating indices from in_arg_ to the current index of out_vector_. 
	///		The in_arg_ vector will begin reading from index 0. To instead begin reading from BeginIndex_, use `vector_copy` instead.
	/// </para>
	/// <para> If Arg_ is none of the above: Performs a normal copy of a scalar to all indices in the specified range. </para>
	/// <para> BeginIndex_ is the inclusive index to start writing to within out_vector_. This is a required template argument. </para>
	/// <para> EndIndex_ is the exclusive index at which to cease writing to out_vector_. This is optional, and defaults to the size of out_vector_. </para>
	/// <para> 
	///		If Arg_ is an EmuMath Vector and does not contain enough indices to fill the provided range, non-contained indices will be ignored. 
	///		To copy non-contained indices within in_arg_, use `vector_copy_from_start`.
	/// </para>
	/// </summary>
	/// <param name="out_vector_">EmuMath Vector to copy to.</param>
	/// <param name="in_arg_">EmuMath Vector or usable scalar to copy to value(s) from.</param>
	template<std::size_t BeginIndex_, std::size_t EndIndex_, typename Arg_, std::size_t Size_, typename T_>
	constexpr inline void new_vector_copy_from_start_contained_only(EmuMath::NewVector<Size_, T_>& out_vector_, Arg_& in_arg_)
	{
		_vector_underlying::_vector_copy_from_start<BeginIndex_, EndIndex_, false, Arg_, Size_, T_>(out_vector_, in_arg_);
	}
	template<std::size_t BeginIndex_, typename Arg_, std::size_t Size_, typename T_>
	constexpr inline void new_vector_copy_from_start_contained_only(EmuMath::NewVector<Size_, T_>& out_vector_, Arg_& in_arg_)
	{
		_vector_underlying::_vector_copy_from_start<BeginIndex_, EmuMath::NewVector<Size_, T_>::size, false, Arg_, Size_, T_>(out_vector_, in_arg_);
	}
	template<std::size_t BeginIndex_, std::size_t EndIndex_, typename Arg_, std::size_t Size_, typename T_>
	constexpr inline void new_vector_copy_from_start_contained_only(EmuMath::NewVector<Size_, T_>& out_vector_, const Arg_& in_arg_)
	{
		_vector_underlying::_vector_copy_from_start<BeginIndex_, EndIndex_, false, const Arg_, Size_, T_>(out_vector_, in_arg_);
	}
	template<std::size_t BeginIndex_, typename Arg_, std::size_t Size_, typename T_>
	constexpr inline void new_vector_copy_from_start_contained_only(EmuMath::NewVector<Size_, T_>& out_vector_, const Arg_& in_arg_)
	{
		_vector_underlying::_vector_copy_from_start<BeginIndex_, EmuMath::NewVector<Size_, T_>::size, false, const Arg_, Size_, T_>(out_vector_, in_arg_);
	}
}

#endif
