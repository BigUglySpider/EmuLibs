#ifndef EMU_THREADS_THREAD_SAFE_HELPERS_H_INC_
#define EMU_THREADS_THREAD_SAFE_HELPERS_H_INC_ 1

#include <sstream>

namespace EmuThreads
{
	namespace _underlying_thread_helpers
	{
		template<class Stream_, class Arg_>
		inline void _stream_append_iteration(Stream_& str_, Arg_& arg_)
		{
			str_ << arg_;
		}
		template<class Stream_, class FirstArg_, class...AdditionalArgs_>
		inline void _stream_append_iteration(Stream_& str_, FirstArg_& first_arg_, AdditionalArgs_&...additional_args_)
		{
			_stream_append_iteration(str_, first_arg_);
			_stream_append_iteration(str_, additional_args_...);
		}
	}

	/// <summary>
	/// <para> Helper to ensure that full appends are performed in a single &lt;&lt; operation. </para>
	/// <para> Provided args_ separated by commas are the same as args_ seperated by &lt;&lt; when appending to the passed stream. </para>
	/// <para> e.g. when supplied with a str_ and 2 args_, this is akin to an 'atomic' `str_ &lt;&lt; args_[0] &lt;&lt; args_[1];` </para>
	/// <para> This function assumes that a stream appends in blocks, where appending one large element instead of several smaller elements is performed in one go. </para>
	/// <para> 
	///		Uses an intermediate std::ostringstream to perform the all-in-one append.
	///		As such, this requires that all passed args may be appended to a std::ostringstream.
	/// </para>
	/// </summary>
	/// <param name="str_">Stream to append to.</param>
	/// <param name="args_">Arguments to append to the stream in the provided order.</param>
	/// <returns>Stream with the provided args_ appended to it.</returns>
	template<class OStream_, class...Args_>
	inline OStream_& stream_append_all_in_one(OStream_& str_, Args_...args_)
	{
		std::ostringstream temp_str_;
		_underlying_thread_helpers::_stream_append_iteration(temp_str_, args_...);
		return str_ << temp_str_.str();
	}
}

#endif
