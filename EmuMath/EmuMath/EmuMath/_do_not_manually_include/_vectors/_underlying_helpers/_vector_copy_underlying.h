#ifndef EMU_MATH_vector_COPY_UNDERLYING_H_INC_
#define EMU_MATH_vector_COPY_UNDERLYING_H_INC_ 1

#include "_vector_tmp.h"
#include "_vector_get_underlying.h"

namespace EmuMath::Helpers::_vector_underlying
{
	template<std::size_t Index_, typename Arg_, std::size_t Size_, typename T_>
	constexpr inline void _vector_copy_index(EmuMath::Vector<Size_, T_>& to_copy_to_, Arg_&& arg_)
	{
		using value_type = typename EmuMath::Vector<Size_, T_>::value_type;
		if constexpr (std::is_assignable_v<value_type, Arg_>)
		{
			_vector_get<Index_>(to_copy_to_) = std::forward<Arg_>(arg_);
		}
		else if constexpr (EmuCore::TMP::is_static_castable_v<Arg_, value_type>)
		{
			_vector_get<Index_>(to_copy_to_) = static_cast<value_type>(std::forward<Arg_>(arg_));
		}
		else if constexpr (std::is_constructible_v<value_type, Arg_>)
		{
			_vector_get<Index_>(to_copy_to_) = value_type(std::forward<Arg_>(arg_));
		}
		else
		{
			static_assert
			(
				EmuCore::TMP::get_false<T_>(),
				"Attempted to copy a value into an EmuMath Vector at a specified index, but the provided Arg_ cannot be used to assign, convert-to, or construct the Vector's value_type."
			);
		}
	}

	template<std::size_t Index_, std::size_t EndIndex_, typename Arg_, std::size_t Size_, typename T_>
	constexpr inline void _vector_copy_scalar(EmuMath::Vector<Size_, T_>& vector_, Arg_& to_copy_)
	{
		if constexpr (Index_ < EndIndex_)
		{
			_vector_copy_index<Index_>(vector_, to_copy_);
			_vector_copy_scalar<Index_ + 1, EndIndex_, Arg_, Size_, T_>(vector_, to_copy_);
		}
	}

	template<std::size_t Index_, std::size_t EndIndex_, std::size_t ArgIndex_, class ArgVector_, std::size_t Size_, typename T_>
	constexpr inline void _vector_copy_vector(EmuMath::Vector<Size_, T_>& vector_, ArgVector_& to_copy_)
	{
		if constexpr (Index_ < EndIndex_)
		{
			if constexpr (EmuMath::TMP::is_emu_vector_v<ArgVector_>)
			{
				using lhs_value_type = typename EmuMath::Vector<Size_, T_>::value_type;
				using arg_vector_uq = EmuCore::TMP::remove_ref_cv_t<ArgVector_>;
				using arg_value_type_cq = EmuCore::TMP::conditional_const_t<std::is_const_v<ArgVector_>, typename arg_vector_uq::value_type>;
				if constexpr (EmuMath::TMP::is_emu_vector_v<lhs_value_type> && !EmuMath::TMP::is_emu_vector_v<arg_value_type_cq>)
				{
					// If vector_ contains Vectors, but to_copy_ does not, we want the containe Vectors to fully copy to_copy_.
					// --- E.g., a Vector<4, Vector<4, float>> copying  Vector<4, float>(1, 2, 3, 4) will be set to ({ 1, 2, 3, 4 }, { 1, 2, 3, 4 }, etc...)
					// ------ This is done to avoid likely undesired behaviour, such as above setting to ({ 1, 1, 1, 1 }, { 2, 2, 2, 2 }, { 3, 3, 3, 3 } { 4, 4, 4, 4 } )
					_vector_copy_vector<0, lhs_value_type::size, ArgIndex_, ArgVector_>
					(
						_vector_get<Index_>(vector_),
						to_copy_
					);
					_vector_copy_vector<Index_ + 1, EndIndex_, ArgIndex_, ArgVector_, Size_, T_>(vector_, to_copy_);
				}
				else
				{
					if constexpr (ArgIndex_ < arg_vector_uq::size)
					{
						_vector_copy_index<Index_>(vector_, _vector_get<ArgIndex_>(to_copy_));
						_vector_copy_vector<Index_ + 1, EndIndex_, ArgIndex_ + 1, ArgVector_, Size_, T_>(vector_, to_copy_);
					}
					else
					{
						auto implied_zero_ = _vector_get_non_contained_value<arg_vector_uq>();
						_vector_copy_scalar<Index_, EndIndex_, decltype(implied_zero_), Size_, T_>(vector_, implied_zero_);
					}
				}
			}
			else
			{
				static_assert
				(
					EmuCore::TMP::get_false<T_>(),
					"Attempted to copy an EmuMath Vector into another EmuMath Vector, but the provided to_copy_ argument was not an EmuMath Vector."
				);
			}
		}
	}

	template<std::size_t BeginIndex_, std::size_t EndIndex_, std::size_t ArgIndex_, typename Arg_, std::size_t Size_, typename T_>
	constexpr inline void _vector_copy(EmuMath::Vector<Size_, T_>& out_, Arg_& in_)
	{
		if constexpr (BeginIndex_ <= EndIndex_)
		{
			using lhs_vector_type = EmuMath::Vector<Size_, T_>;
			constexpr std::size_t end_index_ = (EndIndex_ <= lhs_vector_type::size) ? EndIndex_ : lhs_vector_type::size;

			if constexpr (EmuMath::TMP::is_emu_vector_v<Arg_>)
			{
				_vector_copy_vector<BeginIndex_, end_index_, ArgIndex_, Arg_, Size_, T_>(out_, in_);
			}
			else
			{
				_vector_copy_scalar<BeginIndex_, end_index_, Arg_, Size_, T_>(out_, in_);
			}
		}
		else
		{
			static_assert
			(
				EmuCore::TMP::get_false<T_>(),
				"Attempted to copy to an EmuMath Vector within a range of contiguous indices, but the provided BeginIndex_ is higher than the provided EndIndex_."
			);
		}
	}

	template<typename Arg_, std::size_t Size_, typename T_>
	constexpr inline void _vector_copy(EmuMath::Vector<Size_, T_>& out_, Arg_& in_)
	{
		_vector_copy<0, EmuMath::Vector<Size_, T_>::size, 0, Arg_, Size_, T_>(out_, in_);
	}

	template<bool CopyNonContained_, typename Arg_, std::size_t Size_, typename T_>
	constexpr inline void _vector_copy(EmuMath::Vector<Size_, T_>& out_, Arg_& in_)
	{
		using lhs_vector_type = EmuMath::Vector<Size_, T_>;
		if constexpr (CopyNonContained_)
		{
			_vector_copy<0, lhs_vector_type::size, 0, Arg_, Size_, T_>(out_, in_);
		}
		else
		{
			constexpr std::size_t end_index_ = EmuMath::TMP::smallest_vector_t<lhs_vector_type, Arg_>::size;
			_vector_copy<0, end_index_, 0, Arg_, Size_, T_>(out_, in_);
		}
	}

	template<std::size_t BeginIndex_, std::size_t EndIndex_, bool CopyNonContained_, typename Arg_, std::size_t Size_, typename T_>
	constexpr inline void _vector_copy_from_start(EmuMath::Vector<Size_, T_>& out_vector_, Arg_& in_arg_)
	{
		if constexpr (CopyNonContained_)
		{
			_vector_copy<BeginIndex_, EndIndex_, 0, Arg_, Size_, T_>(out_vector_, in_arg_);
		}
		else
		{
			if constexpr (EmuMath::TMP::is_emu_vector_v<Arg_>)
			{
				if constexpr (BeginIndex_ <= EndIndex_)
				{
					using lhs_vector = EmuMath::Vector<Size_, T_>;
					constexpr std::size_t clamped_end_index_ = (EndIndex_ < lhs_vector::size) ? EndIndex_ : lhs_vector::size;
					constexpr std::size_t arg_size_ = EmuCore::TMP::remove_ref_cv_t<Arg_>::size;
					constexpr std::size_t index_range_ = clamped_end_index_ - BeginIndex_;
					constexpr std::size_t final_end_index_ = (index_range_ <= arg_size_) ? clamped_end_index_ : BeginIndex_ + arg_size_;
					_vector_copy<BeginIndex_, final_end_index_, 0, Arg_, Size_, T_>(out_vector_, in_arg_);
				}
				else
				{
					static_assert
					(
						EmuCore::TMP::get_false<T_>(),
						"Attempted to copy to an EmuMath Vector within a range of contiguous indices, but the provided BeginIndex_ is higher than the provided EndIndex_."
					);
				}
			}
			else
			{
				// Not EmuMath Vector, so this is a blanket copy where we always go the specified length.
				_vector_copy<BeginIndex_, EndIndex_, 0, Arg_, Size_, T_>(out_vector_, in_arg_);
			}
		}
	}
}

#endif
