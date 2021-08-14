#ifndef EMU_MATH_VECTOR_T_HELPERS_UNDERLYING_H_INC_
#define EMU_MATH_VECTOR_T_HELPERS_UNDERLYING_H_INC_

#include "VectorTMP.h"

namespace EmuMath::Helpers::_underlying_vector_funcs
{
#pragma region VALIDITY_CHECKS
	template<class LhsVector_, class RhsVector_>
	[[nodiscard]] constexpr inline bool _validity_check_vector_assignment()
	{
		if constexpr (EmuMath::TMP::is_emu_vector_v<LhsVector_>)
		{
			if constexpr (EmuMath::TMP::is_emu_vector_v<RhsVector_>)
			{
				return true;
			}
			else
			{
				static_assert(false, "Attempted to perform an assignment to an EmuMath vector via another vector, but the provided item to assign from was not an EmuMath vector.");
				return false;
			}
		}
		else
		{
			static_assert(false, "Attempted to perform an assignment to an EmuMath vector, but the provided item to assign to was not an EmuMath vector.");
			return false;
		}
	}
#pragma endregion

#pragma region GETS
	/// <summary> Cleaner way to access a vector's at template member within underlying functions. </summary>
	/// <typeparam name="Vector_">Vector type to get the data from.</typeparam>
	/// <param name="vector_">Vector to get the data at the passed index of.</param>
	/// <returns>Result of calling Vector_::at&lt;Index_&gt; on the passed vector.</returns>
	template<std::size_t Index_, class Vector_>
	[[nodiscard]] constexpr inline typename Vector_::value_type& _get_vector_data(Vector_& vector_)
	{
		return vector_.template at<Index_>();
	}
	template<std::size_t Index_, class Vector_>
	[[nodiscard]] constexpr inline const typename Vector_::value_type& _get_vector_data(const Vector_& vector_)
	{
		return vector_.template at<Index_>();
	}
#pragma endregion

#pragma region SETS
	template<std::size_t Index_, class Vector_>
	void _assign_vector_via_scalar(Vector_& vector_, const typename Vector_::value_type& scalar_)
	{
		if constexpr (Index_ < Vector_::size)
		{
			_get_vector_data<Index_>(vector_) = scalar_;
			_assign_vector_via_scalar<Index_ + 1, Vector_>(vector_, scalar_);
		}
	}

	template<std::size_t Index_, class LhsVector_, class RhsVector_>
	void _assign_vector_via_vector(LhsVector_& lhs_, const RhsVector_& rhs_)
	{
		if constexpr (Index_ < LhsVector_::size)
		{
			if constexpr (Index_ < RhsVector_::size)
			{
				_get_vector_data<Index_>(lhs_) = static_cast<typename LhsVector_::value_type>(_get_vector_data<Index_>(rhs_));
				_assign_vector_via_vector<Index_ + 1, LhsVector_, RhsVector_>(lhs_, rhs_);
			}
			else
			{
				// Finish the vector off by assigning a scalar - done this way in case constructing a zeroed value_type is noticeably expensive
				_assign_vector_via_scalar<Index_, LhsVector_>(lhs_, typename LhsVector_::value_type(0));
			}
		}
	}
#pragma endregion

#pragma region STREAMS
	template<std::size_t Index_, class Stream_, class Vector_>
	void _append_vector_data_to_stream(Stream_& stream_, const Vector_& vector_)
	{
		if constexpr (Index_ < Vector_::size)
		{
			stream_ << ", " << _get_vector_data<Index_>(vector_);
			_append_vector_data_to_stream<Index_ + 1, Stream_, Vector_>(stream_, vector_);
		}
	}
	template<class Stream_, class Vector_>
	Stream_& _append_vector_to_stream(Stream_& stream_, const Vector_& vector_)
	{
		stream_ << "{ " << _get_vector_data<0>(vector_);
		_append_vector_data_to_stream<1, Stream_, Vector_>(stream_, vector_);
		stream_ << " }";
		return stream_;
	}

	template<std::size_t Index_, class WideStream_, class Vector_>
	void _append_vector_data_to_wide_stream(WideStream_& stream_, const Vector_& vector_)
	{
		if constexpr (Index_ < Vector_::size)
		{
			stream_ << L", " << _get_vector_data<Index_>(vector_);
			_append_vector_data_to_wide_stream<Index_ + 1, WideStream_, Vector_>(stream_, vector_);
		}
	}
	template<class WideStream_, class Vector_>
	WideStream_& _append_vector_to_wide_stream(WideStream_& stream_, const Vector_& vector_)
	{
		stream_ << L"{ " << _get_vector_data<0>(vector_);
		_append_vector_data_to_wide_stream<1, WideStream_, Vector_>(stream_, vector_);
		stream_ << L" }";
		return stream_;
	}
#pragma endregion

#pragma region PERMUTATIONS

#pragma endregion
}

#endif
