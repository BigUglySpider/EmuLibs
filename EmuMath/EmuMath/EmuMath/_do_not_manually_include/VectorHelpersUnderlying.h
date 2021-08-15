#ifndef EMU_MATH_VECTOR_T_HELPERS_UNDERLYING_H_INC_
#define EMU_MATH_VECTOR_T_HELPERS_UNDERLYING_H_INC_

#include "VectorTMP.h"

/// <summary> Underlying functions for performing vector operations. These should not be called directly. </summary>
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

	template<class Vector_, std::size_t X_, std::size_t...OtherIndices_>
	constexpr inline bool _validity_check_vector_shuffle()
	{
		if constexpr (EmuMath::TMP::is_emu_vector_v<Vector_>)
		{
			if constexpr (EmuMath::TMP::valid_vector_indices_v<Vector_, X_, OtherIndices_...>)
			{
				return true;
			}
			else
			{
				static_assert(false, "Attempted to perform a shuffle on an EmuMath vector, but at least one provided index was out of the provided vector's range.");
				return false;
			}
		}
		else
		{
			static_assert(false, "Attempted to perform a shuffle on an EmuMath vector, but the provided item was not an EmuMath vector.");
			return false;
		}
	}

	template<class Vector_>
	constexpr inline bool _validity_check_vector_get()
	{
		if constexpr (EmuMath::TMP::is_emu_vector_v<Vector_>)
		{
			return true;
		}
		else
		{
			static_assert(false, "Attempted to get an element from an EmuMath vector, but the provided item was not a type of EmuMath vector.");
			return false;
		}
	}
	template<std::size_t Index_, class Vector_>
	constexpr inline bool _validity_check_vector_get()
	{
		if constexpr (_validity_check_vector_get<Vector_>())
		{
			if constexpr (EmuMath::TMP::valid_vector_indices_v<Vector_, Index_>)
			{
				return true;
			}
			else
			{
				static_assert(false, "Attempted to get an index from an EmuMath vector which exceeds its maximum index.");
				return false;
			}
		}
		else
		{
			return false;
		}
	}

	template<class OutVector_, class LhsVector_, class RhsVector_>
	constexpr inline bool _validity_check_vector_arithmetic()
	{
		if constexpr (EmuMath::TMP::is_emu_vector_v<LhsVector_>)
		{
			if constexpr (EmuMath::TMP::is_emu_vector_v<RhsVector_>)
			{
				if constexpr (EmuMath::TMP::is_emu_vector_v<OutVector_>)
				{
					return true;
				}
				else
				{
					static_assert(false, "Attempted to perform vector arithmetic with a non-EmuMath-vector output type.");
					return false;
				}
			}
			else
			{
				static_assert(false, "Attempted to perform vector arithmetic with a non-EmuMath-vector right-hand argument.");
				return false;
			}
		}
		else
		{
			static_assert(false, "Attempted to perform vector arithmetic with a non-EmuMath-vector left-hand argument.");
			return false;
		}
	}

	template<class OutVector_, class LhsVector_, class Rhs_>
	constexpr inline bool _validity_check_no_integral_divide_by_zero()
	{
		if constexpr (EmuMath::TMP::is_emu_vector_v<Rhs_>)
		{
			if constexpr (OutVector_::size <= Rhs_::size)
			{
				// Guaranteed safety since the output vector will restrict use to only safe divisions in rhs (logical errors aside)
				return true;
			}
			else
			{
				// If there is a guaranteed /0, we need to be sure inf can be stored in the output
				if constexpr (!OutVector_::has_integral_elements)
				{
					// As long as either lhs or rhs isn't integral, dividing by 0 will be assumed to equal infinity
					if constexpr (!LhsVector_::has_integral_elements || !Rhs_::has_integral_elements)
					{
						return true;
					}
					else
					{
						static_assert(false, "Attempted to perform vector division of two integral vectors, but an output size larger than the right-hand vector would result in an integral division by 0.");
						return false;
					}
				}
				else
				{
					static_assert(false, "Attempted to perform vector division with integral output, but the output size being larger than the right-hand vector would result in an integral division by 0. As x/0 casting to an integral type is undefined, this behaviour has been blocked.");
					return false;
				}
			}
		}
		else
		{
			// There will always be a rhs non-zero argument as we are using the scalar for all values
			return true;
		}
	}

	template<class OutVector_, class LhsVector_>
	constexpr inline bool _validity_check_vector_arithmetic_potential_scalar()
	{
		if constexpr (EmuMath::TMP::is_emu_vector_v<LhsVector_>)
		{
			if constexpr (EmuMath::TMP::is_emu_vector_v<OutVector_>)
			{
				return true;
			}
			else
			{
				static_assert(false, "Attempted to perform vector arithmetic with a non-EmuMath-vector output type.");
				return false;
			}
		}
		else
		{
			static_assert(false, "Attempted to perform vector arithmetic with a non-EmuMath-vector left-hand argument.");
			return false;
		}
	}

	template<class A_, class B_>
	constexpr inline bool _validity_check_vector_dot_product()
	{
		if constexpr (EmuMath::TMP::is_emu_vector_v<A_>)
		{
			if constexpr (EmuMath::TMP::is_emu_vector_v<B_>)
			{
				return true;
			}
			else
			{
				static_assert(false, "attempted to get the dot product of two vectors, but provided a non-EmuMath-vector type as argument B_.");
				return false;
			}
		}
		else
		{
			static_assert(false, "attempted to get the dot product of two vectors, but provided a non-EmuMath-vector type as argument A_.");
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

	template<class Vector_>
	[[nodiscard]] constexpr inline typename Vector_::value_type& _get_vector_data(Vector_& vector_, const std::size_t index_)
	{
		return vector_.at(index_);
	}
	template<class Vector_>
	[[nodiscard]] constexpr inline const typename Vector_::value_type& _get_vector_data(const Vector_& vector_, const std::size_t index_)
	{
		return vector_.at(index_);
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
				// Finish the vector off by assigning a scalar - done this way in case constructing a default value_type is noticeably expensive
				_assign_vector_via_scalar<Index_, LhsVector_>(lhs_, typename LhsVector_::value_type());
			}
		}
	}
#pragma endregion

#pragma region VECTOR_OPERATIONS
	template<std::size_t Index_, typename OutT_, class Vector_, class CombineFunc_>
	constexpr inline void _combine_all_vector_elements(const Vector_& vector_, OutT_& out_, CombineFunc_& func_)
	{
		if constexpr (Index_ < Vector_::size)
		{
			out_ = func_(out_, static_cast<OutT_>(_get_vector_data<Index_>(vector_)));
			_combine_all_vector_elements<Index_ + 1, OutT_, Vector_, CombineFunc_>(vector_, out_, func_);
		}
	}
	template<typename OutT_, class Vector_, class CombineFunc_>
	[[nodiscard]] constexpr inline OutT_ _combine_all_vector_elements(const Vector_& vector_)
	{
		OutT_ out_ = static_cast<OutT_>(_get_vector_data<0>(vector_));
		CombineFunc_ func_ = CombineFunc_();
		_combine_all_vector_elements<1, OutT_, Vector_, CombineFunc_>(vector_, out_, func_);
		return out_;
	}

	template<std::size_t Index_, typename OutT_, class A_, class B_>
	constexpr inline void _calculate_vector_dot_product(const A_& a_, const B_& b_, OutT_& out_)
	{
		// No need to loop if surpassing at least one vector's size as we will just be adding 0 from that point on
		if constexpr (Index_ < A_::size && Index_ < B_::size)
		{
			out_ = out_ + static_cast<OutT_>(_get_vector_data<Index_>(a_) * _get_vector_data<Index_>(b_));
			_calculate_vector_dot_product<Index_ + 1, OutT_, A_, B_>(a_, b_, out_);
		}
	}
	template<typename OutT_, class A_, class B_>
	[[nodiscard]] constexpr inline OutT_ _calculate_vector_dot_product(const A_& a_, const B_& b_)
	{
		OutT_ out_ = OutT_();
		_calculate_vector_dot_product<0, OutT_, A_, B_>(a_, b_, out_);
		return out_;
	}

	template<std::size_t Index_, class Vector_, class Out_>
	constexpr inline void _find_vector_min(const Vector_& vector_, Out_& out_)
	{
		if constexpr (Index_ < Vector_::size)
		{
			const typename Vector_::value_type& val_ = _get_vector_data<Index_>(vector_);
			if (val_ < out_)
			{
				out_ = val_;
			}
			_find_vector_min<Index_ + 1, Vector_, Out_>(vector_, out_);
		}
	}
	template<class Vector_>
	[[nodiscard]] constexpr inline typename Vector_::value_type _find_vector_min(const Vector_& vector_)
	{
		typename Vector_::value_type out_(_get_vector_data<0>(vector_));
		_find_vector_min<1, Vector_, typename Vector_::value_type>(vector_, out_);
		return out_;
	}

	template<std::size_t Index_, class Vector_, class Out_>
	constexpr inline void _find_vector_max(const Vector_& vector_, Out_& out_)
	{
		if constexpr (Index_ < Vector_::size)
		{
			const typename Vector_::value_type& val_ = _get_vector_data<Index_>(vector_);
			if (val_ > out_)
			{
				out_ = val_;
			}
			_find_vector_max<Index_ + 1, Vector_, Out_>(vector_, out_);
		}
	}
	template<class Vector_>
	[[nodiscard]] constexpr inline typename Vector_::value_type _find_vector_max(const Vector_& vector_)
	{
		typename Vector_::value_type out_(_get_vector_data<0>(vector_));
		_find_vector_max<1, Vector_, typename Vector_::value_type>(vector_, out_);
		return out_;
	}

	template<std::size_t Index_, class Vector_, class Out_>
	constexpr inline void _find_vector_min_max(const Vector_& vector_, Out_& min_, Out_& max_)
	{
		if constexpr (Index_ < Vector_::size)
		{
			const typename Vector_::value_type& val_ = _get_vector_data<Index_>(vector_);
			if (val_ < min_)
			{
				min_ = val_;
			}
			else if (val_ > max_)
			{
				max_ = val_;
			}
			_find_vector_min_max<Index_ + 1, Vector_, Out_>(vector_, min_, max_);
		}
	}
	template<class Vector_>
	[[nodiscard]] constexpr inline EmuMath::Vector<2, typename Vector_::value_type> _find_vector_min_max(const Vector_& vector_)
	{
		const typename Vector_::value_type& element_zero_ = _get_vector_data<0>(vector_);
		EmuMath::Vector<2, typename Vector_::value_type> out_(element_zero_, element_zero_);
		_find_vector_min_max<1, Vector_, typename Vector_::value_type>(vector_, _get_vector_data<0>(out_), _get_vector_data<1>(out_));
		return out_;
	}
	template<class Vector_>
	constexpr inline void _find_vector_min_max(const Vector_& vector_, typename Vector_::value_type& min_, typename Vector_::value_type& max_)
	{
		min_ = _get_vector_data<0>(vector_);
		max_ = min_;
		_find_vector_min_max<1, Vector_, typename Vector_::value_type>(vector_, min_, max_);
	}
#pragma endregion

#pragma region ARITHMETIC
	template<std::size_t Index_, class OutVector_, class LhsVector_, class RhsVector_, class ArithmeticFunc_>
	constexpr inline void _perform_vector_arithmetic(const LhsVector_& lhs_, const RhsVector_& rhs_, OutVector_& out_, ArithmeticFunc_& func_)
	{
		if constexpr (Index_ < OutVector_::size)
		{
			using out_value = typename OutVector_::value_type;
			if constexpr (Index_ < LhsVector_::size)
			{
				if constexpr (Index_ < RhsVector_::size)
				{
					_get_vector_data<Index_>(out_) = static_cast<out_value>(func_(_get_vector_data<Index_>(lhs_), _get_vector_data<Index_>(rhs_)));
				}
				else
				{
					using rhs_value = typename RhsVector_::value_type;
					_get_vector_data<Index_>(out_) = static_cast<out_value>(func_(_get_vector_data<Index_>(lhs_), rhs_value()));
				}
			}
			else
			{
				using lhs_value = typename LhsVector_::value_type;
				if constexpr (Index_ < RhsVector_::size)
				{
					_get_vector_data<Index_>(out_) = static_cast<out_value>(func_(lhs_value(), _get_vector_data<Index_>(rhs_)));
				}
				else
				{
					using rhs_value = typename RhsVector_::value_type;
					_get_vector_data<Index_>(out_) = static_cast<out_value>(func_(lhs_value(), rhs_value()));
				}
			}

			_perform_vector_arithmetic<Index_ + 1, OutVector_, LhsVector_, RhsVector_, ArithmeticFunc_>(lhs_, rhs_, out_, func_);
		}
	}
	template<std::size_t Index_, class OutVector_, class LhsVector_, class RhsScalar_, class ArithmeticFunc_>
	constexpr inline void _perform_vector_arithmetic_scalar(const LhsVector_& lhs_, const RhsScalar_& rhs_, OutVector_& out_, ArithmeticFunc_& func_)
	{
		if constexpr (Index_ < OutVector_::size)
		{
			if constexpr (Index_ < LhsVector_::size)
			{
				_get_vector_data<Index_>(out_) = static_cast<typename OutVector_::value_type>(func_(_get_vector_data<Index_>(lhs_), rhs_));
			}
			else
			{
				_get_vector_data<Index_>(out_) = static_cast<typename OutVector_::value_type>(func_(typename LhsVector_::value_type(), rhs_));
			}
			_perform_vector_arithmetic_scalar<Index_ + 1, OutVector_, LhsVector_, RhsScalar_, ArithmeticFunc_>(lhs_, rhs_, out_, func_);
		}
	}
	template<class OutVector_, class LhsVector_, class Rhs_, class ArithmeticFunc_>
	[[nodiscard]] constexpr inline OutVector_ _perform_vector_arithmetic(const LhsVector_& lhs_, const Rhs_& rhs_)
	{
		OutVector_ out_ = OutVector_();
		ArithmeticFunc_ func_ = ArithmeticFunc_();
		if constexpr (EmuMath::TMP::is_emu_vector_v<Rhs_>)
		{
			_perform_vector_arithmetic<0, OutVector_, LhsVector_, Rhs_, ArithmeticFunc_>(lhs_, rhs_, out_, func_);
		}
		else
		{
			_perform_vector_arithmetic_scalar<0, OutVector_, LhsVector_, Rhs_, ArithmeticFunc_>(lhs_, rhs_, out_, func_);
		}
		return out_;
	}
#pragma endregion

#pragma region COMPARISONS
	template<std::size_t Index_, class OutVector_, class Comparison_, class LhsVector_, class RhsScalar_>
	[[nodiscard]] constexpr inline void _perform_vector_per_element_comparison_rhs_scalar
	(
		const LhsVector_& lhs_,
		const RhsScalar_& rhs_,
		OutVector_& out_,
		Comparison_& cmpFunc_
	)
	{
		if constexpr (Index_ < OutVector_::size)
		{
			if constexpr (Index_ < LhsVector_::size)
			{
				_get_vector_data<Index_>(out_) = static_cast<typename OutVector_::value_type>(cmpFunc_(_get_vector_data<Index_>(lhs_), rhs_));
			}
			else
			{
				_get_vector_data<Index_>(out_) = static_cast<typename OutVector_::value_type>(cmpFunc_(typename LhsVector_::value_type(), rhs_));
			}
			_perform_vector_per_element_comparison_rhs_scalar<Index_ + 1, OutVector_, Comparison_, LhsVector_, RhsScalar_>(lhs_, rhs_, out_, cmpFunc_);
		}
	}
	template<std::size_t Index_, class OutVector_, class Comparison_, class LhsVector_, class RhsVector_>
	[[nodiscard]] constexpr inline void _perform_vector_per_element_comparison_rhs_vector
	(
		const LhsVector_& lhs_,
		const RhsVector_& rhs_,
		OutVector_& out_,
		Comparison_& cmpFunc_
	)
	{
		if constexpr (Index_ < OutVector_::size)
		{
			using out_value_type = typename OutVector_::value_type;
			if constexpr (Index_ < LhsVector_::size)
			{
				if constexpr (Index_ < RhsVector_::size)
				{
					_get_vector_data<Index_>(out_) = static_cast<out_value_type>(cmpFunc_(_get_vector_data<Index_>(lhs_), _get_vector_data<Index_>(rhs_)));
				}
				else
				{
					using rhs_value_type = typename RhsVector_::value_type;
					_get_vector_data<Index_>(out_) = static_cast<out_value_type>(cmpFunc_(_get_vector_data<Index_>(lhs_), rhs_value_type()));
				}
			}
			else
			{
				using lhs_value_type = typename LhsVector_::value_type;
				if constexpr (Index_ < RhsVector_::size)
				{
					_get_vector_data<Index_>(out_) = static_cast<out_value_type>(cmpFunc_(lhs_value_type(), _get_vector_data<Index_>(rhs_)));
				}
				else
				{
					using rhs_value_type = typename RhsVector_::value_type;
					_get_vector_data<Index_>(out_) = static_cast<out_value_type>(cmpFunc_(lhs_value_type(), rhs_value_type()));
				}
			}
			_perform_vector_per_element_comparison_rhs_vector<Index_ + 1, OutVector_, Comparison_, LhsVector_, RhsVector_>(lhs_, rhs_, out_, cmpFunc_);
		}
	}
	template<class OutVector_, class Comparison_, class LhsVector_, class Rhs_>
	[[nodiscard]] constexpr inline OutVector_ _perform_vector_per_element_comparison(const LhsVector_& lhs_, const Rhs_& rhs_, Comparison_& cmpFunc_)
	{
		OutVector_ out_ = OutVector_();
		if constexpr (EmuMath::TMP::is_emu_vector_v<Rhs_>)
		{
			_perform_vector_per_element_comparison_rhs_vector<0, OutVector_, Comparison_, LhsVector_, Rhs_>(lhs_, rhs_, out_, cmpFunc_);
		}
		else
		{

		}
		return out_;
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
}

#endif
