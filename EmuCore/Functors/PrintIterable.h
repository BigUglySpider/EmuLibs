#ifndef EMU_CORE_PRINT_ITERABLE_H_INC_
#define EMU_CORE_PRINT_ITERABLE_H_INC_ 1

namespace EmuCore
{
	template<class Iterator_, class Stream_>
	struct PrintIterable
	{
		constexpr inline Stream_& operator()(Stream_& stream_, Iterator_ iterator_, const Iterator_& end_) const
		{
			stream_ << '{';
			stream_ << ' ';

			if (iterator_ < end_)
			{
				stream_ << (*iterator_);

				++iterator_;
				for (; iterator_ != end_; ++iterator_)
				{
					stream_ << ", ";
					stream_ << (*iterator_);
				}
				stream_ << ' ';
			}

			stream_ << '}';
			return stream_;
		}
	};

	template<class Iterator_, class Stream_>
	inline Stream_& print_iterable(Stream_& stream_, Iterator_& iterator_, const Iterator_& end_)
	{
		return PrintIterable<Iterator_, Stream_>()(stream_, iterator_, end_);
	}

	template<class Iterator_, class Stream_>
	inline Stream_& print_iterable(Stream_& stream_, const Iterator_& iterator_, const Iterator_& end_)
	{
		return PrintIterable<Iterator_, Stream_>()(stream_, iterator_, end_);
	}

	template<class Iterator_, class Stream_>
	inline Stream_& print_iterable(Stream_& stream_, Iterator_&& iterator_, const Iterator_& end_)
	{
		return PrintIterable<Iterator_, Stream_>()(stream_, std::move(iterator_), end_);
	}
}

#endif
