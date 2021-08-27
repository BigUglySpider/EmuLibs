#ifndef EMU_MATH_VECTOR_T_HELPERS_UNDERLYING_H_INC_
#define EMU_MATH_VECTOR_T_HELPERS_UNDERLYING_H_INC_ 1

#include "../../EmuCore/TMPHelpers/TypeComparators.h"
#include "VectorTMP.h"

/// <summary> Underlying functions for performing vector operations. These should not be called directly. </summary>
namespace EmuMath::Helpers::_underlying_vector_funcs
{
#pragma region VALIDITY_CHECKS
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

	template<class LhsVector_, class RhsVector_>
	constexpr inline bool _validity_check_vector_arithmetic()
	{
		if constexpr (EmuMath::TMP::is_emu_vector_v<LhsVector_>)
		{
			if constexpr (EmuMath::TMP::is_emu_vector_v<RhsVector_>)
			{
				return true;
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

	template<class LhsVector_>
	constexpr inline bool _validity_check_vector_arithmetic_potential_scalar()
	{
		if constexpr (EmuMath::TMP::is_emu_vector_v<LhsVector_>)
		{
			return true;
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
	[[nodiscard]] constexpr inline typename Vector_::raw_value_type& _get_vector_data(Vector_& vector_)
	{
		return vector_.template at<Index_>();
	}
	template<std::size_t Index_, class Vector_>
	[[nodiscard]] constexpr inline const typename Vector_::raw_value_type& _get_vector_data(const Vector_& vector_)
	{
		return vector_.template at<Index_>();
	}

	template<class Vector_>
	[[nodiscard]] constexpr inline typename Vector_::raw_value_type& _get_vector_data(Vector_& vector_, const std::size_t index_)
	{
		return vector_.at(index_);
	}
	template<class Vector_>
	[[nodiscard]] constexpr inline const typename Vector_::raw_value_type& _get_vector_data(const Vector_& vector_, const std::size_t index_)
	{
		return vector_.at(index_);
	}
#pragma endregion

#pragma region SETS
	template<std::size_t Index_, class Vector_, class Data_>
	constexpr inline void _set_vector_data(Vector_& vector_, Data_& data_)
	{
		vector_.template Set<Index_>(data_);
	}
	template<class Vector_, class Data_>
	constexpr inline void _set_vector_data(Vector_& vector_, Data_& data_, const std::size_t index_)
	{
		vector_.template Set(data_, index_);
	}

	template<std::size_t Index_, class Vector_>
	constexpr inline void _copy_to_vector_via_scalar(Vector_& vector_, const typename Vector_::value_type& scalar_)
	{
		if constexpr (Index_ < Vector_::size)
		{
			_get_vector_data<Index_>(vector_) = scalar_;
			_copy_to_vector_via_scalar<Index_ + 1, Vector_>(vector_, scalar_);
		}
	}
	template<std::size_t Index_, class LhsVector_, class RhsVector_>
	constexpr inline void _copy_to_vector_via_vector(LhsVector_& lhs_, const RhsVector_& rhs_)
	{
		if constexpr (Index_ < LhsVector_::size)
		{
			if constexpr (Index_ < RhsVector_::size)
			{
				_get_vector_data<Index_>(lhs_) = static_cast<typename LhsVector_::value_type>(_get_vector_data<Index_>(rhs_));
				_copy_to_vector_via_vector<Index_ + 1, LhsVector_, RhsVector_>(lhs_, rhs_);
			}
			else
			{
				// Finish the vector off by assigning a scalar - done this way in case constructing a default value_type is noticeably expensive
				_copy_to_vector_via_scalar<Index_, LhsVector_>(lhs_, typename LhsVector_::value_type());
			}
		}
	}
	template<class LhsVector_, class Rhs_>
	constexpr inline void _copy_to_vector(LhsVector_& lhs_, const Rhs_& rhs_)
	{
		if constexpr (EmuMath::TMP::is_emu_vector_v<Rhs_>)
		{
			_copy_to_vector_via_vector<0, LhsVector_, Rhs_>(lhs_, rhs_);
		}
		else
		{
			_copy_to_vector_via_scalar<0, LhsVector_, Rhs_>(lhs_, rhs_);
		}
	}

	template<std::size_t Index_, class LhsVector_, class Rhs_>
	constexpr inline void _set_vector(LhsVector_& lhs_, Rhs_& rhs_)
	{
		if constexpr (Index_ < LhsVector_::size)
		{
			if constexpr (EmuMath::TMP::is_emu_vector_v<Rhs_>)
			{
				// Set explicitly only goes the size of the smallest vector (for the sake of reference assignment compatibility).
				if constexpr (Index_ < Rhs_::size)
				{
					_set_vector_data<Index_>(lhs_, _get_vector_data<Index_>(rhs_));
					_set_vector<Index_ + 1>(lhs_, rhs_);
				}
			}
			else
			{
				// All set to the same if vector only on lhs_, whether references or values
				_set_vector_data<Index_>(lhs_, rhs_);
				_set_vector<Index_ + 1>(lhs_, rhs_);
			}
		}
	}
	template<class LhsVector_, class Rhs_>
	constexpr inline void _set_vector(LhsVector_& lhs_, Rhs_& rhs_)
	{
		if constexpr (LhsVector_::contains_reference_wrappers)
		{
			if constexpr (LhsVector_::contains_const_reference_wrappers)
			{
				// No additional checks needed for const references since non-const will implicitly assigned as const
				_set_vector<0>(lhs_, rhs_);
			}
			else
			{
				if constexpr (!(std::is_const_v<Rhs_> || Rhs_::contains_const_reference_wrappers))
				{
					_set_vector<0>(lhs_, rhs_);
				}
				else
				{
					static_assert(false, "Attempted to set an EmuMath vector of non-const references via a vector that can only provide const references in its context.");
				}
			}
		}
		else
		{
			_set_vector<0>(lhs_, rhs_);
		}
	}
#pragma endregion

#pragma region VECTOR_OPERATIONS
	template<std::size_t Index_, class OutVector_, class Vector_, class Func_>
	constexpr inline void _vector_single_operand_func(const Vector_& vector_, OutVector_& out_, Func_& func_)
	{
		if constexpr (Index_ < OutVector_::size)
		{
			using out_value = typename OutVector_::value_type;
			if constexpr (Index_ < Vector_::size)
			{
				_get_vector_data<Index_>(out_) = static_cast<out_value>(func_(_get_vector_data<Index_>(vector_)));
				_vector_single_operand_func<Index_ + 1, OutVector_, Vector_, Func_>(vector_, out_, func_);
			}
			else
			{
				using vector_value = typename Vector_::value_type;
				_copy_to_vector_via_scalar<Index_, OutVector_>(out_, static_cast<out_value>(func_(vector_value())));
			}
		}
	}

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
	template<class Vector_, typename Out_>
	[[nodiscard]] constexpr inline typename Out_ _find_vector_min(const Vector_& vector_)
	{
		typename Vector_::value_type out_(_get_vector_data<0>(vector_));
		_find_vector_min<1, Vector_, typename Vector_::value_type>(vector_, out_);
		return static_cast<Out_>(out_);
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
	template<class Vector_, typename Out_>
	[[nodiscard]] constexpr inline typename Vector_::value_type _find_vector_max(const Vector_& vector_)
	{
		typename Vector_::value_type out_(_get_vector_data<0>(vector_));
		_find_vector_max<1, Vector_, typename Vector_::value_type>(vector_, out_);
		return static_cast<Out_>(out_);
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
	template<class Vector_, typename Out_>
	[[nodiscard]] constexpr inline EmuMath::Vector<2, Out_> _find_vector_min_max(const Vector_& vector_)
	{
		typename Vector_::value_type min_(_get_vector_data<0>(vector_));
		typename Vector_::value_type max_(min_);
		_find_vector_min_max<1, Vector_, typename Vector_::value_type>(vector_, min_, max_);
		return EmuMath::Vector<2, Out_>(min_, max_);
	}
	template<class Vector_, typename OutMin_, typename OutMax_>
	constexpr inline void _find_vector_min_max(const Vector_& vector_, typename OutMin_& outMin_, typename OutMax_& outMax_)
	{
		typename Vector_::value_type min_ = _get_vector_data<0>(vector_);
		typename Vector_::value_type max_ = min_;
		_find_vector_min_max<1, Vector_, typename Vector_::value_type>(vector_, min_, max_);
		outMin_ = static_cast<OutMin_>(min_);
		outMax_ = static_cast<OutMax_>(max_);
	}

	template<std::size_t Index_, class Vector_>
	constexpr inline void _find_vector_min_index(const Vector_& vector_, typename Vector_::value_type& min_, std::size_t& out_)
	{
		if constexpr (Index_ < Vector_::size)
		{
			const typename Vector_::value_type& val_ = _get_vector_data<Index_>(vector_);
			if (val_ < min_)
			{
				out_ = Index_;
				min_ = val_;
			}
			_find_vector_min_index<Index_ + 1, Vector_>(vector_, min_, out_);
		}
	}
	template<class Vector_>
	[[nodiscard]] constexpr inline std::size_t _find_vector_min_index(const Vector_& vector_)
	{
		typename Vector_::value_type min_(_get_vector_data<0>(vector_));
		std::size_t out_(0);
		_find_vector_min_index<1, Vector_>(vector_, min_, out_);
		return out_;
	}

	template<std::size_t Index_, class Vector_>
	constexpr inline void _find_vector_max_index(const Vector_& vector_, typename Vector_::value_type& max_, std::size_t& out_)
	{
		if constexpr (Index_ < Vector_::size)
		{
			const typename Vector_::value_type& val_ = _get_vector_data<Index_>(vector_);
			if (val_ > max_)
			{
				out_ = Index_;
				max_ = val_;
			}
			_find_vector_max_index<Index_ + 1, Vector_>(vector_, max_, out_);
		}
	}
	template<class Vector_>
	[[nodiscard]] constexpr inline std::size_t _find_vector_max_index(const Vector_& vector_)
	{
		typename Vector_::value_type max_(_get_vector_data<0>(vector_));
		std::size_t out_(0);
		_find_vector_max_index<1, Vector_>(vector_, max_, out_);
		return out_;
	}

	template<std::size_t Index_, class Vector_>
	constexpr inline void _find_vector_min_max_indices
	(
		const Vector_& vector_,
		typename Vector_::value_type& min_,
		typename Vector_::value_type& max_,
		std::size_t& outMin_,
		std::size_t& outMax_
	)
	{
		if constexpr (Index_ < Vector_::size)
		{
			const typename Vector_::value_type& val_ = _get_vector_data<Index_>(vector_);

			if (val_ < min_)
			{
				outMin_ = Index_;
				min_ = val_;
			}
			else if (val_ > max_)
			{
				outMax_ = Index_;
				max_ = val_;
			}
			_find_vector_min_max_indices<Index_ + 1, Vector_>(vector_, min_, max_, outMin_, outMax_);
		}
	}
	template<class Vector_>
	[[nodiscard]] constexpr inline EmuMath::Vector<2, std::size_t> _find_vector_min_max_indices(const Vector_& vector_)
	{
		typename Vector_::value_type min_(_get_vector_data<0>(vector_));
		typename Vector_::value_type max_(min_);
		EmuMath::Vector<2, std::size_t> out_(0, 0);
		_find_vector_min_max_indices<1, Vector_>(vector_, min_, max_, _get_vector_data<0>(out_), _get_vector_data<1>(out_));
		return out_;
	}
	template<class Vector_>
	constexpr inline void _find_vector_min_max_indices(const Vector_& vector_, std::size_t& outMinIndex_, std::size_t& outMaxIndex_)
	{
		typename Vector_::value_type min_(_get_vector_data<0>(vector_));
		typename Vector_::value_type max_(min_);
		_find_vector_min_max_indices<1, Vector_>(vector_, min_, max_, outMinIndex_, outMaxIndex_);
	}

	template<std::size_t Index_, class OutVector_, class VectorA_, class B_, class Func_>
	constexpr inline void _form_min_or_max_vector_b_vector(const VectorA_& a_, const B_& b_, OutVector_& out_, Func_& func_)
	{
		if constexpr (Index_ < OutVector_::size)
		{
			using out_value = typename OutVector_::value_type;
			if constexpr (Index_ < VectorA_::size)
			{
				if constexpr (Index_ < B_::size)
				{
					_get_vector_data<Index_>(out_) = static_cast<out_value>(func_(_get_vector_data<Index_>(a_), _get_vector_data<Index_>(b_)));
					_form_min_or_max_vector_b_vector<Index_ + 1, OutVector_, VectorA_, B_, Func_>(a_, b_, out_, func_);
				}
				else
				{
					_get_vector_data<Index_>(out_) = static_cast<out_value>(func_(_get_vector_data<Index_>(a_), typename B_::value_type()));
					_form_min_or_max_vector_b_vector<Index_ + 1, OutVector_, VectorA_, B_, Func_>(a_, b_, out_, func_);
				}
			}
			else
			{
				using a_value = typename VectorA_::value_type;
				if constexpr (Index_ < B_::size)
				{
					_get_vector_data<Index_>(out_) = static_cast<out_value>(func_(a_value(), _get_vector_data<Index_>(b_)));
					_form_min_or_max_vector_b_vector<Index_ + 1, OutVector_, VectorA_, B_, Func_>(a_, b_, out_, func_);
				}
				else
				{
					// Will be the same for all remaining indices, so just defer the rest of the formation to a copy of the result instead.
					_copy_to_vector_via_scalar<Index_, OutVector_>(out_, static_cast<out_value>(func_(a_value(), typename B_::value_type())));
				}
			}
		}
	}
	template<std::size_t Index_, class OutVector_, class VectorA_, class B_, class Func_>
	constexpr inline void _form_min_or_max_vector_b_scalar(const VectorA_& a_, const B_& b_, OutVector_& out_, Func_& func_)
	{
		if constexpr (Index_ < OutVector_::size)
		{
			using out_value = typename OutVector_::value_type;
			if constexpr (Index_ < VectorA_::size)
			{
				_get_vector_data<Index_>(out_) = static_cast<out_value>(func_(_get_vector_data<Index_>(a_), b_));
				_form_min_or_max_vector_b_scalar<Index_ + 1, OutVector_, VectorA_, B_, Func_>(a_, b_, out_, func_);
			}
			else
			{
				// Will be the same for all remaining indices, so just defer the rest of the formation to a copy of the result instead.
				_copy_to_vector_via_scalar<Index_>(out_, static_cast<out_value>(func_(typename VectorA_::value_type(), b_)));
			}
		}
	}
	template<class OutVector, class VectorA_, class B_>
	constexpr inline OutVector _form_min_vector(const VectorA_& a_, const B_& b_)
	{
		OutVector out_ = OutVector();
		if constexpr (EmuMath::TMP::is_emu_vector_v<B_>)
		{
			using Func_ = EmuCore::do_min<typename VectorA_::value_type, typename B_::value_type>;
			Func_ func_ = Func_();
			_form_min_or_max_vector_b_vector<0, OutVector, VectorA_, B_, Func_>(a_, b_, out_, func_);
		}
		else
		{
			using Func_ = EmuCore::do_min<typename VectorA_::value_type, B_>;
			Func_ func_ = Func_();
			_form_min_or_max_vector_b_scalar<0, OutVector, VectorA_, B_, Func_>(a_, b_, out_, func_);
		}
		return out_;
	}
	template<class OutVector, class VectorA_, class B_>
	constexpr inline OutVector _form_max_vector(const VectorA_& a_, const B_& b_)
	{
		OutVector out_ = OutVector();
		if constexpr (EmuMath::TMP::is_emu_vector_v<B_>)
		{
			using Func_ = EmuCore::do_max<typename VectorA_::value_type, typename B_::value_type>;
			Func_ func_ = Func_();
			_form_min_or_max_vector_b_vector<0, OutVector, VectorA_, B_, Func_>(a_, b_, out_, func_);
		}
		else
		{
			using Func_ = EmuCore::do_max<typename VectorA_::value_type, B_>;
			Func_ func_ = Func_();
			_form_min_or_max_vector_b_scalar<0, OutVector, VectorA_, B_, Func_>(a_, b_, out_, func_);
		}
		return out_;
	}

	template<std::size_t Index_, class OutVector_, class VectorA_, class B_, class MinFunc_, class MaxFunc_, bool FirstMinArg_, bool...RemainingMinArgs>
	struct _form_min_and_max_vector_b_vector
	{
		constexpr _form_min_and_max_vector_b_vector()
		{
		}

		constexpr inline void operator()(const VectorA_& a_, const B_& b_, OutVector_& out_, MinFunc_& min_, MaxFunc_& max_) const
		{
			if constexpr (Index_ < OutVector_::size)
			{
				_form_min_and_max_vector_b_vector<Index_, OutVector_, VectorA_, B_, MinFunc_, MaxFunc_, FirstMinArg_>()(a_, b_, out_, min_, max_);
				_form_min_and_max_vector_b_vector<Index_ + 1, OutVector_, VectorA_, B_, MinFunc_, MaxFunc_, RemainingMinArgs...>()(a_, b_, out_, min_, max_);
			}
		}
	};
	template<std::size_t Index_, class OutVector_, class VectorA_, class B_, class MinFunc_, class MaxFunc_, bool FirstMinArg_>
	struct _form_min_and_max_vector_b_vector<Index_, OutVector_, VectorA_, B_, MinFunc_, MaxFunc_, FirstMinArg_>
	{
		constexpr _form_min_and_max_vector_b_vector()
		{
		}

		constexpr inline void operator()(const VectorA_& a_, const B_& b_, OutVector_& out_, MinFunc_& min_, MaxFunc_& max_) const
		{
			// NOTE: This function is not recursive as it only takes one bool. As num bool args determines out vector size, this suggests we are at the end anyway
			// --- A recursive form of this function is the one found with a further variadic arg after FirstMinArg_.
			if constexpr (Index_ < OutVector_::size)
			{
				using out_value = typename OutVector_::value_type;
				if constexpr (Index_ < VectorA_::size)
				{
					if constexpr (Index_ < B_::size)
					{
						if constexpr (FirstMinArg_)
						{
							_get_vector_data<Index_>(out_) = static_cast<out_value>(min_(_get_vector_data<Index_>(a_), _get_vector_data<Index_>(b_)));
						}
						else
						{
							_get_vector_data<Index_>(out_) = static_cast<out_value>(max_(_get_vector_data<Index_>(a_), _get_vector_data<Index_>(b_)));
						}
					}
					else
					{
						using b_value = typename B_::value_type;
						if constexpr (FirstMinArg_)
						{
							_get_vector_data<Index_>(out_) = static_cast<out_value>(min_(_get_vector_data<Index_>(a_), b_value()));
						}
						else
						{
							_get_vector_data<Index_>(out_) = static_cast<out_value>(max_(_get_vector_data<Index_>(a_), b_value()));
						}
					}
				}
				else
				{
					using a_value = typename VectorA_::value_type;
					if constexpr (Index_ < B_::size)
					{
						if constexpr (FirstMinArg_)
						{
							_get_vector_data<Index_>(out_) = static_cast<out_value>(min_(a_value(), _get_vector_data<Index_>(b_)));
						}
						else
						{
							_get_vector_data<Index_>(out_) = static_cast<out_value>(max_(a_value(), _get_vector_data<Index_>(b_)));
						}
					}
					else
					{
						using b_value = typename B_::value_type;
						if constexpr (FirstMinArg_)
						{
							_get_vector_data<Index_>(out_) = static_cast<out_value>(min_(a_value(), b_value()));
						}
						else
						{
							_get_vector_data<Index_>(out_) = static_cast<out_value>(max_(a_value(), b_value()));
						}
					}
				}
			}
		}
	};
	template<std::size_t Index_, class OutVector_, class VectorA_, class B_, class MinFunc_, class MaxFunc_, bool FirstMinArg_, bool...RemainingMinArgs>
	struct _form_min_and_max_vector_b_scalar
	{
		constexpr _form_min_and_max_vector_b_scalar()
		{
		}
		constexpr inline void operator()(const VectorA_& a_, const B_& b_, OutVector_& out_, MinFunc_& min_, MaxFunc_& max_) const
		{
			if constexpr (Index_ < OutVector_::size)
			{
				_form_min_and_max_vector_b_scalar<Index_, OutVector_, VectorA_, B_, MinFunc_, MaxFunc_, FirstMinArg_>()(a_, b_, out_, min_, max_);
				_form_min_and_max_vector_b_scalar<Index_ + 1, OutVector_, VectorA_, B_, MinFunc_, MaxFunc_, RemainingMinArgs...>()(a_, b_, out_, min_, max_);
			}
		}
	};
	template<std::size_t Index_, class OutVector_, class VectorA_, class B_, class MinFunc_, class MaxFunc_, bool FirstMinArg_>
	struct _form_min_and_max_vector_b_scalar<Index_, OutVector_, VectorA_, B_, MinFunc_, MaxFunc_, FirstMinArg_>
	{
		constexpr _form_min_and_max_vector_b_scalar()
		{
		}
		constexpr inline void operator()(const VectorA_& a_, const B_& b_, OutVector_& out_, MinFunc_& min_, MaxFunc_& max_) const
		{
			// NOTE: This function is not recursive as it only takes one bool. As num bool args determines out vector size, this suggests we are at the end anyway
			// --- A recursive form of this function is the one found with a further variadic arg after FirstMinArg_.
			if constexpr (Index_ < OutVector_::size)
			{
				using out_value = typename OutVector_::value_type;
				if constexpr (Index_ < VectorA_::size)
				{
					if constexpr (FirstMinArg_)
					{
						_get_vector_data<Index_>(out_) = static_cast<out_value>(min_(_get_vector_data<Index_>(a_), b_));
					}
					else
					{
						_get_vector_data<Index_>(out_) = static_cast<out_value>(max_(_get_vector_data<Index_>(a_), b_));
					}
				}
				else
				{
					using a_value = typename VectorA_::value_type;
					if constexpr (FirstMinArg_)
					{
						_get_vector_data<Index_>(out_) = static_cast<out_value>(min_(a_value(), b_));
					}
					else
					{
						_get_vector_data<Index_>(out_) = static_cast<out_value>(max_(a_value(), b_));
					}
				}
			}
		}
	};
	template<class OutVector_, class VectorA_, class B_, bool...MinArgs_>
	constexpr inline OutVector_ _form_min_and_max_vector(const VectorA_& a_, const B_& b_)
	{
		OutVector_ out_ = OutVector_();
		if constexpr (EmuMath::TMP::is_emu_vector_v<B_>)
		{
			using MinFunc_ = EmuCore::do_min<typename VectorA_::value_type, typename B_::value_type>;
			using MaxFunc_ = EmuCore::do_max<typename VectorA_::value_type, typename B_::value_type>;
			MinFunc_ min_ = MinFunc_();
			MaxFunc_ max_ = MaxFunc_();
			_form_min_and_max_vector_b_vector<0, OutVector_, VectorA_, B_, MinFunc_, MaxFunc_, MinArgs_...>()(a_, b_, out_, min_, max_);
		}
		else
		{
			using MinFunc_ = EmuCore::do_min<typename VectorA_::value_type, B_>;
			using MaxFunc_ = EmuCore::do_max<typename VectorA_::value_type, B_>;
			MinFunc_ min_ = MinFunc_();
			MaxFunc_ max_ = MaxFunc_();
			_form_min_and_max_vector_b_scalar<0, OutVector_, VectorA_, B_, MinFunc_, MaxFunc_, MinArgs_...>()(a_, b_, out_, min_, max_);
		}
		return out_;
	}

	template<std::size_t Index_, class A_, class B_, class T_, class Out_>
	constexpr inline void _vector_lerp_vvv(const A_& a_, const B_& b_, const T_& t_, Out_& out_)
	{
		if constexpr (Index_ < Out_::size)
		{
			using out_value = typename Out_::value_type;
			using a_value = typename A_::value_type;
			if constexpr (Index_ < A_::size)
			{
				const a_value& a_val_ = _get_vector_data<Index_>(a_);
				if constexpr (Index_ < B_::size)
				{
					if constexpr (Index_ < T_::size)
					{
						_get_vector_data<Index_>(out_) = static_cast<out_value>
						(
							a_val_ + ((_get_vector_data<Index_>(b_) - a_val_) * _get_vector_data<Index_>(t_))
						);
					}
					else
					{
						_get_vector_data<Index_>(out_) = static_cast<out_value>
						(
							a_val_ + ((_get_vector_data<Index_>(b_) - a_val_) * typename T_::value_type())
						);
					}
				}
				else
				{
					using b_value = typename B_::value_type;
					if constexpr (Index_ < T_::size)
					{
						_get_vector_data<Index_>(out_) = static_cast<out_value>
						(
							a_val_ + ((b_value() - a_val_) * _get_vector_data<Index_>(t_))
						);
					}
					else
					{
						_get_vector_data<Index_>(out_) = static_cast<out_value>
						(
							a_val_ + ((b_value() - a_val_) * typename T_::value_type())
						);
					}
				};
			}
			else
			{
				const a_value a_val_ = a_value();
				if constexpr (Index_ < B_::size)
				{
					if constexpr (Index_ < T_::size)
					{
						_get_vector_data<Index_>(out_) = static_cast<out_value>
						(
							a_val_ + ((_get_vector_data<Index_>(b_) - a_val_) * _get_vector_data<Index_>(t_))
						);
					}
					else
					{
						_get_vector_data<Index_>(out_) = static_cast<out_value>
						(
							a_val_ + ((_get_vector_data<Index_>(b_) - a_val_) * typename T_::value_type())
						);
					}
				}
				else
				{
					using b_value = typename B_::value_type;
					if constexpr (Index_ < T_::size)
					{
						_get_vector_data<Index_>(out_) = static_cast<out_value>
						(
							a_val_ + ((b_value() - a_val_) * _get_vector_data<Index_>(t_))
						);
					}
					else
					{
						_get_vector_data<Index_>(out_) = static_cast<out_value>
						(
							a_val_ + ((b_value() - a_val_) * typename T_::value_type())
						);
					}
				}
			}
			_vector_lerp_vvv<Index_ + 1, A_, B_, T_, Out_>(a_, b_, t_, out_);
		}
	}
	template<std::size_t Index_, class A_, class B_, class T_, class Out_>
	constexpr inline void _vector_lerp_vvs(const A_& a_, const B_& b_, const T_& t_, Out_& out_)
	{
		if constexpr (Index_ < Out_::size)
		{
			using out_value = typename Out_::value_type;
			using a_value = typename A_::value_type;
			if constexpr (Index_ < A_::size)
			{
				const a_value& a_val_ = _get_vector_data<Index_>(a_);
				if constexpr (Index_ < B_::size)
				{
					_get_vector_data<Index_>(out_) = static_cast<out_value>(a_val_ + ((_get_vector_data<Index_>(b_) - a_val_) * t_));
				}
				else
				{
					_get_vector_data<Index_>(out_) = static_cast<out_value>(a_val_ + ((typename B_::value_type() - a_val_) * t_));
				}
			}
			else
			{
				const a_value a_val_ = a_value();
				if constexpr (Index_ < B_::size)
				{
					_get_vector_data<Index_>(out_) = static_cast<out_value>(a_val_ + ((_get_vector_data<Index_>(b_) - a_val_) * t_));
				}
				else
				{
					_get_vector_data<Index_>(out_) = static_cast<out_value>(a_val_ + ((typename B_::value_type() - a_val_) * t_));
				}
			}
			_vector_lerp_vvs<Index_ + 1, A_, B_, T_, Out_>(a_, b_, t_, out_);
		}
	}
	template<std::size_t Index_, class A_, class B_, class T_, class Out_>
	constexpr inline void _vector_lerp_vsv(const A_& a_, const B_& b_, const T_& t_, Out_& out_)
	{
		if constexpr (Index_ < Out_::size)
		{
			using out_value = typename Out_::value_type;
			using a_value = typename A_::value_type;
			if constexpr (Index_ < A_::size)
			{
				const a_value& a_val_ = _get_vector_data<Index_>(a_);
				if constexpr (Index_ < T_::size)
				{
					_get_vector_data<Index_>(out_) = static_cast<out_value>(a_val_ + ((b_ - a_val_) * _get_vector_data<Index_>(t_)));
				}
				else
				{
					_get_vector_data<Index_>(out_) = static_cast<out_value>(a_val_ + ((b_ - a_val_) * typename T_::value_type()));
				}
			}
			else
			{
				const a_value a_val_ = a_value();
				if constexpr (Index_ < T_::size)
				{
					_get_vector_data<Index_>(out_) = static_cast<out_value>(a_val_ + ((b_ - a_val_) * _get_vector_data<Index_>(t_)));
				}
				else
				{
					_get_vector_data<Index_>(out_) = static_cast<out_value>(a_val_ + ((b_ - a_val_) * typename T_::value_type()));
				}
			}
			_vector_lerp_vsv<Index_ + 1, A_, B_, T_, Out_>(a_, b_, t_, out_);
		}
	}
	template<std::size_t Index_, class A_, class B_, class T_, class Out_>
	constexpr inline void _vector_lerp_vss(const A_& a_, const B_& b_, const T_& t_, Out_& out_)
	{
		if constexpr (Index_ < Out_::size)
		{
			using out_value = typename Out_::value_type;
			if constexpr (Index_ < A_::size)
			{
				const typename A_::value_type& a_val_ = _get_vector_data<Index_>(a_);
				_get_vector_data<Index_>(out_) = static_cast<out_value>(a_val_ + ((b_ - a_val_) * t_));
			}
			else
			{
				const typename A_::value_type a_val_ = typename A_::value_type();
				_get_vector_data<Index_>(out_) = static_cast<out_value>(a_val_ + ((b_ - a_val_) * t_));
			}
			_vector_lerp_vss<Index_ + 1, A_, B_, T_, Out_>(a_, b_, t_, out_);
		}
	}
	template<class A_, class B_, class T_, class Out_>
	[[nodiscard]] constexpr inline Out_ _vector_lerp(const A_& a_, const B_& b_, const T_& t_)
	{
		Out_ out_ = Out_();
		if constexpr (EmuMath::TMP::is_emu_vector_v<B_>)
		{
			if constexpr (EmuMath::TMP::is_emu_vector_v<T_>)
			{
				// Lerp(vector, vector, vector)
				_vector_lerp_vvv<0, A_, B_, T_, Out_>(a_, b_, t_, out_);
			}
			else
			{
				// Lerp(vector, vector, scalar)
				_vector_lerp_vvs<0, A_, B_, T_, Out_>(a_, b_, t_, out_);
			}
		}
		else
		{
			if constexpr (EmuMath::TMP::is_emu_vector_v<T_>)
			{
				// Lerp(vector, scalar, vector)
				_vector_lerp_vsv<0, A_, B_, T_, Out_>(a_, b_, t_, out_);
			}
			else
			{
				// Lerp(vector, scalar, scalar)
				_vector_lerp_vss<0, A_, B_, T_, Out_>(a_, b_, t_, out_);
			}
		}
		return out_;
	}

	template<std::size_t Index_, class OutVector_, class Vector_>
	constexpr inline void _vector_reciprocal(const Vector_& vector_, OutVector_& out_)
	{
		if constexpr (Index_ < OutVector_::size)
		{
			using out_value = typename OutVector_::value_type;
			if constexpr (Index_ < Vector_::size)
			{
				_get_vector_data<Index_>(out_) = static_cast<out_value>(out_value(1) / static_cast<out_value>(_get_vector_data<Index_>(vector_)));
				_vector_reciprocal<Index_ + 1, OutVector_, Vector_>(vector_, out_);
			}
			else
			{
				// Don't force a div/0 situation, and instead set all to infinity as that is the expected result of dividing by 0 as per IEEE.
				_copy_to_vector_via_scalar<Index_, OutVector_>(out_, std::numeric_limits<out_value>::infinity());
			}
		}
	}
	template<class OutVector_, class Vector_>
	[[nodiscard]] constexpr inline OutVector_ _vector_reciprocal(const Vector_& vector_)
	{
		OutVector_ out_ = OutVector_();
		_vector_reciprocal<0, OutVector_, Vector_>(vector_, out_);
		return out_;
	}

	template<std::size_t Index_, class OutVector_, class Vector_, class ClampVector_, class CmpFunc_>
	constexpr inline void _vector_clamp_single_vector(const Vector_& vector_, const ClampVector_& clampVector_, OutVector_& out_, CmpFunc_& cmp_)
	{
		if constexpr (Index_ < OutVector_::size)
		{
			using out_value = typename OutVector_::value_type;
			using vector_value = typename Vector_::value_type;
			using clamp_value = typename ClampVector_::value_type;
			if constexpr (Index_ < Vector_::size)
			{
				const vector_value& val_ = _get_vector_data<Index_>(vector_);
				if constexpr (Index_ < ClampVector_::size)
				{
					const clamp_value& clamp_ = _get_vector_data<Index_>(clampVector_);
					_get_vector_data<Index_>(out_) = cmp_(val_, clamp_) ? static_cast<out_value>(clamp_) : static_cast<out_value>(val_);
				}
				else
				{
					const clamp_value clamp_ = clamp_value();
					_get_vector_data<Index_>(out_) = cmp_(val_, clamp_) ? static_cast<out_value>(clamp_) : static_cast<out_value>(val_);
				}
			}
			else
			{
				const vector_value val_ = vector_value();
				if constexpr (Index_ < ClampVector_::size)
				{
					const clamp_value& clamp_ = _get_vector_data<Index_>(clampVector_);
					_get_vector_data<Index_>(out_) = cmp_(val_, clamp_) ? static_cast<out_value>(clamp_) : static_cast<out_value>(val_);
				}
				else
				{
					const clamp_value clamp_ = clamp_value();
					_get_vector_data<Index_>(out_) = cmp_(val_, clamp_) ? static_cast<out_value>(clamp_) : static_cast<out_value>(val_);
				}
			}
			_vector_clamp_single_vector<Index_ + 1, OutVector_, Vector_, ClampVector_, CmpFunc_>(vector_, clampVector_, out_, cmp_);
		}
	}
	template<std::size_t Index_, class OutVector_, class Vector_, class ClampScalar_, class CmpFunc_>
	constexpr inline void _vector_clamp_single_scalar(const Vector_& vector_, const ClampScalar_& clampScalar_, OutVector_& out_, CmpFunc_& cmp_)
	{
		if constexpr (Index_ < OutVector_::size)
		{
			using out_value = typename OutVector_::value_type;
			using vector_value = typename Vector_::value_type;
			if constexpr (Index_ < Vector_::size)
			{
				const vector_value& val_ = _get_vector_data<Index_>(vector_);
				_get_vector_data<Index_>(out_) = cmp_(val_, clampScalar_) ? static_cast<out_value>(clampScalar_) : static_cast<out_value>(val_);
				_vector_clamp_single_scalar<Index_ + 1, OutVector_, Vector_, ClampScalar_, CmpFunc_>(vector_, clampScalar_, out_, cmp_);
			}
			else
			{
				const vector_value val_ = vector_value();
				_copy_to_vector_via_scalar<Index_, OutVector_>(out_, cmp_(val_, clampScalar_) ? static_cast<out_value>(clampScalar_) : static_cast<out_value>(val_));
			}
		}
	}

	template<class OutVector_, class Vector_, class Min_>
	[[nodiscard]] constexpr inline OutVector_ _vector_clamp_min(const Vector_& vector_, const Min_& min_)
	{
		OutVector_ out_ = OutVector_();
		std::less<void> cmp_ = std::less<void>();
		if constexpr (EmuMath::TMP::is_emu_vector_v<Min_>)
		{
			_vector_clamp_single_vector<0, OutVector_, Vector_, Min_, std::less<void>>(vector_, min_, out_, cmp_);
		}
		else
		{
			_vector_clamp_single_scalar<0, OutVector_, Vector_, Min_, std::less<void>>(vector_, min_, out_, cmp_);
		}
		return out_;
	}
	template<class OutVector_, class Vector_, class Max_>
	[[nodiscard]] constexpr inline OutVector_ _vector_clamp_max(const Vector_& vector_, const Max_& max_)
	{
		OutVector_ out_ = OutVector_();
		std::greater<void> cmp_ = std::greater<void>();
		if constexpr (EmuMath::TMP::is_emu_vector_v<Max_>)
		{
			_vector_clamp_single_vector<0, OutVector_, Vector_, Max_, std::greater<void>>(vector_, max_, out_, cmp_);
		}
		else
		{
			_vector_clamp_single_scalar<0, OutVector_, Vector_, Max_, std::greater<void>>(vector_, max_, out_, cmp_);
		}
		return out_;
	}

	template<std::size_t Index_, class OutVector_, typename vector_value_type, typename min_value_type, class Max_, class MinCmp_, class MaxCmp_>
	constexpr inline void _execute_vector_clamp_index_with_vector_and_min_value
	(
		const vector_value_type& val_,
		const min_value_type& min_val_,
		const Max_& max_,
		OutVector_& out_,
		MinCmp_& min_cmp_,
		MaxCmp_& max_cmp_
	)
	{
		using out_value = typename OutVector_::value_type;
		if (min_cmp_(val_, min_val_))
		{
			_get_vector_data<Index_>(out_) = static_cast<out_value>(min_val_);
		}
		else
		{
			if constexpr (EmuMath::TMP::is_emu_vector_v<Max_>)
			{
				using max_value_type = typename Max_::value_type;
				if constexpr (Index_ < Max_::size)
				{
					const max_value_type& max_val_ = _get_vector_data<Index_>(max_);
					_get_vector_data<Index_>(out_) = (max_cmp_(val_, max_val_)) ? static_cast<out_value>(max_val_) : static_cast<out_value>(val_);
				}
				else
				{
					const max_value_type max_val_ = max_value_type();
					_get_vector_data<Index_>(out_) = max_cmp_(val_, max_val_) ? static_cast<out_value>(max_val_) : static_cast<out_value>(val_);
				}
			}
			else
			{
				_get_vector_data<Index_>(out_) = max_cmp_(val_, max_) ? static_cast<out_value>(max_) : static_cast<out_value>(val_);
			}
		}
	}
	template<std::size_t Index_, class OutVector_, typename vector_value_type, class Min_, class Max_, class MinCmp_, class MaxCmp_>
	constexpr inline void _execute_vector_clamp_index_with_vector_value
	(
		const vector_value_type& val_,
		const Min_& min_,
		const Max_& max_,
		OutVector_& out_,
		MinCmp_& min_cmp_,
		MaxCmp_& max_cmp_
	)
	{
		if constexpr (EmuMath::TMP::is_emu_vector_v<Min_>)
		{
			if constexpr (Index_ < Min_::size)
			{
				_execute_vector_clamp_index_with_vector_and_min_value<Index_, OutVector_, vector_value_type, typename Min_::value_type, Max_, MinCmp_, MaxCmp_>
				(
					val_,
					_get_vector_data<Index_>(min_),
					max_,
					out_,
					min_cmp_,
					max_cmp_
				);
			}
			else
			{
				_execute_vector_clamp_index_with_vector_and_min_value<Index_, OutVector_, vector_value_type, typename Min_::value_type, Max_, MinCmp_, MaxCmp_>
				(
					val_,
					typename Min_::value_type(),
					max_,
					out_,
					min_cmp_,
					max_cmp_
				);
			}
		}
		else
		{
			_execute_vector_clamp_index_with_vector_and_min_value<Index_, OutVector_, vector_value_type, Min_, Max_, MinCmp_, MaxCmp_>
			(
				val_,
				min_,
				max_,
				out_,
				min_cmp_,
				max_cmp_
			);
		}
	}
	template<std::size_t Index_, class OutVector_, class Vector_, class Min_, class Max_, class MinCmp_, class MaxCmp_>
	constexpr inline void _vector_clamp(const Vector_& vector_, const Min_& min_, const Max_& max_, OutVector_& out_, MinCmp_& min_cmp_, MaxCmp_& max_cmp_)
	{
		if constexpr (Index_ < OutVector_::size)
		{
			if constexpr (Index_ < Vector_::size)
			{
				_execute_vector_clamp_index_with_vector_value<Index_, OutVector_, typename Vector_::value_type, Min_, Max_, MinCmp_, MaxCmp_>
				(
					_get_vector_data<Index_>(vector_),
					min_,
					max_,
					out_,
					min_cmp_,
					max_cmp_
				);
			}
			else
			{
				_execute_vector_clamp_index_with_vector_value<Index_, OutVector_, typename Vector_::value_type, Min_, Max_, MinCmp_, MaxCmp_>
				(
					typename Vector_::value_type(),
					min_,
					max_,
					out_,
					min_cmp_,
					max_cmp_
				);
			}
			_vector_clamp<Index_ + 1, OutVector_, Vector_, Min_, Max_, MinCmp_, MaxCmp_>(vector_, min_, max_, out_, min_cmp_, max_cmp_);
		}
	}
	template<class OutVector_, class Vector_, class Min_, class Max_>
	[[nodiscard]] constexpr inline OutVector_ _vector_clamp(const Vector_& vector_, const Min_& min_, const Max_& max_)
	{
		OutVector_ out_ = OutVector_();
		std::less<void> min_cmp_ = std::less<void>();
		std::greater<void> max_cmp_ = std::greater<void>();
		_vector_clamp<0, OutVector_, Vector_, Min_, Max_, std::less<void>, std::greater<void>>(vector_, min_, max_, out_, min_cmp_, max_cmp_);
		return out_;
	}

	template<class OutVector_, class Vector_, class Func_>
	[[nodiscard]] constexpr inline OutVector_ _vector_single_operand_func(const Vector_& vector_, Func_& func_)
	{
		OutVector_ out_ = OutVector_();
		_vector_single_operand_func<0, OutVector_, Vector_, Func_>(vector_, out_, func_);
		return out_;
	}
	template<class OutVector_, class Vector_, class Func_>
	[[nodiscard]] constexpr inline OutVector_ _vector_single_operand_func(const Vector_& vector_)
	{
		OutVector_ out_ = OutVector_();
		Func_ func_ = Func_();
		_vector_single_operand_func<0, OutVector_, Vector_, Func_>(vector_, out_, func_);
		return out_;
	}

	template<std::size_t Index_, class OutVector_, class Vector_, class Shift_, class Shifter_>
	constexpr inline void _vector_bitwise_shift_per_element_scalar_shifts(const Vector_& vector_, const Shift_& num_shifts_, OutVector_& out_, Shifter_& shifter_)
	{
		if constexpr (Index_ < OutVector_::size)
		{
			using out_value = typename OutVector_::value_type;
			if constexpr (Index_ < Vector_::size)
			{
				_get_vector_data<Index_>(out_) = static_cast<out_value>(shifter_(_get_vector_data<Index_>(vector_), num_shifts_));
				_vector_bitwise_shift_per_element_scalar_shifts<Index_ + 1, OutVector_, Vector_, Shift_, Shifter_>(vector_, num_shifts_, out_, shifter_);
			}
			else
			{
				using vector_value = typename Vector_::value_type;
				if constexpr (std::is_arithmetic_v<vector_value>)
				{
					_copy_to_vector_via_scalar<Index_, OutVector_>(out_, static_cast<out_value>(vector_value()));
				}
				else
				{
					_copy_to_vector_via_scalar<Index_, OutVector_>(out_, static_cast<out_value>(shifter_(vector_value(), num_shifts_)));
				}
			}
		}
	}
	template<std::size_t Index_, class OutVector_, class Vector_, class ShiftVector_, class Shifter_>
	constexpr inline void _vector_bitwise_shift_per_element_vector_shifts(const Vector_& vector_, const ShiftVector_& num_shifts_, OutVector_& out_, Shifter_& shifter_)
	{
		if constexpr (Index_ < OutVector_::size)
		{
			using out_value = typename OutVector_::value_type;
			if constexpr (Index_ < ShiftVector_::size)
			{
				using vector_value = typename Vector_::value_type;
				if constexpr (Index_ < Vector_::size)
				{
					_get_vector_data<Index_>(out_) = static_cast<out_value>
					(
						shifter_(_get_vector_data<Index_>(vector_), _get_vector_data<Index_>(num_shifts_))
					);
					_vector_bitwise_shift_per_element_vector_shifts<Index_ + 1, OutVector_, Vector_, ShiftVector_, Shifter_>(vector_, num_shifts_, out_, shifter_);
				}
				else
				{
					if constexpr (std::is_arithmetic_v<vector_value>)
					{
						// If arithmetic, we know any remaining shifts would lead to 0, so simply copy 0 into the remaining indices.
						_copy_to_vector_via_scalar<Index_, OutVector_>(out_, static_cast<out_value>(vector_value()));
					}
					else
					{
						// If not arithmetic type then perform a shift on the default value as we don't have a guarantee of what another arbitrary type may do here
						_get_vector_data<Index_>(out_) = static_cast<out_value>
						(
							shifter_(vector_value(), static_cast<std::size_t>(_get_vector_data<Index_>(num_shifts_)))
						);
						_vector_bitwise_shift_per_element_vector_shifts<Index_ + 1, OutVector_, Vector_, ShiftVector_, Shifter_>(vector_, num_shifts_, out_, shifter_);
					}
				}
			}
			else
			{
				// All shifts will be whatever shift_value's default translates to, so use that as a scalar for remaining iterations.
				using shift_value = typename ShiftVector_::value_type;
				_vector_bitwise_shift_per_element_scalar_shifts<Index_, OutVector_, Vector_, shift_value, Shifter_>(vector_, shift_value(), out_, shifter_);
			}
		}
	}
	template<class OutVector_, class Vector_, class Shifts_, template<class T__, class Shifts__> class ShifterTemplate_>
	[[nodiscard]] constexpr inline OutVector_ _vector_bitwise_shift_per_element(const Vector_& vector_, const Shifts_& num_shifts_)
	{
		OutVector_ out_ = OutVector_();
		if constexpr (EmuMath::TMP::is_emu_vector_v<Shifts_>)
		{
			using shift_value = typename Shifts_::value_type;
			using Shifter_ = ShifterTemplate_<typename Vector_::value_type, typename Shifts_::value_type>;
			Shifter_ shifter_ = Shifter_();
			_vector_bitwise_shift_per_element_vector_shifts<0, OutVector_, Vector_, Shifts_, Shifter_>(vector_, num_shifts_, out_, shifter_);
		}
		else
		{
			using Shifter_ = ShifterTemplate_<typename Vector_::value_type, Shifts_>;
			Shifter_ shifter_ = Shifter_();
			_vector_bitwise_shift_per_element_scalar_shifts<0, OutVector_, Vector_, Shifts_, Shifter_>(vector_, num_shifts_, out_, shifter_);
		}
		return out_;
	}

	template<std::size_t Index_, class OutVector_, class LhsVector_, class RhsScalar_, class Func_>
	constexpr inline void _vector_bitwise_non_shift_op_rhs_scalar(const LhsVector_& lhs_, const RhsScalar_& rhs_, OutVector_& out_, Func_& func_)
	{
		if constexpr (Index_ < OutVector_::size)
		{
			using out_value = typename OutVector_::value_type;
			if constexpr (Index_ < LhsVector_::size)
			{
				_get_vector_data<Index_>(out_) = static_cast<out_value>(func_(_get_vector_data<Index_>(lhs_), rhs_));
				_vector_bitwise_non_shift_op_rhs_scalar<Index_ + 1, OutVector_, LhsVector_, RhsScalar_, Func_>(lhs_, rhs_, out_, func_);
			}
			else
			{
				// All remaining results will be the same, so defer to assignment
				_copy_to_vector_via_scalar<Index_, OutVector_>(out_, static_cast<out_value>(func_(typename LhsVector_::value_type(), rhs_)));
			}
		}
	}
	template<std::size_t Index_, class OutVector_, class LhsVector_, class RhsVector_, class Func_>
	constexpr inline void _vector_bitwise_non_shift_op_rhs_vector(const LhsVector_& lhs_, const RhsVector_& rhs_, OutVector_& out_, Func_& func_)
	{
		if constexpr (Index_ < OutVector_::size)
		{
			using out_value = typename OutVector_::value_type;
			if constexpr (Index_ < LhsVector_::size)
			{
				if constexpr (Index_ < RhsVector_::size)
				{
					_get_vector_data<Index_>(out_) = static_cast<out_value>(func_(_get_vector_data<Index_>(lhs_), _get_vector_data<Index_>(rhs_)));
					_vector_bitwise_non_shift_op_rhs_vector<Index_ + 1, OutVector_, LhsVector_, RhsVector_, Func_>(lhs_, rhs_, out_, func_);
				}
				else
				{
					// Defer remaining calls to scalar variant since we'd just keep constructing a new rhs_value for remaining calls otherwise.
					using rhs_value = typename RhsVector_::value_type;
					_vector_bitwise_non_shift_op_rhs_scalar<Index_, OutVector_, LhsVector_, rhs_value, Func_>(lhs_, rhs_value(), out_, func_);
				}
			}
			else
			{
				if constexpr (Index_ < RhsVector_::size)
				{
					_get_vector_data<Index_>(out_) = static_cast<out_value>(func_(typename LhsVector_::value_type(), _get_vector_data<Index_>(rhs_)));
					_vector_bitwise_non_shift_op_rhs_vector<Index_ + 1, OutVector_, LhsVector_, RhsVector_, Func_>(lhs_, rhs_, out_, func_);
				}
				else
				{
					// Defer remaining calls to assignment, since the remaining values will all be the same result we can cut out the middleman here
					using lhs_value = typename LhsVector_::value_type;
					using rhs_value = typename RhsVector_::value_type;
					_copy_to_vector_via_scalar<Index_, OutVector_>(out_, static_cast<out_value>(func_(lhs_value(), rhs_value())));
				}
			}
		}
	}
	template<class OutVector_, class LhsVector_, class Rhs_, class Func_>
	[[nodiscard]] constexpr inline OutVector_ _vector_bitwise_non_shift_op(const LhsVector_& lhs_, const Rhs_& rhs_)
	{
		OutVector_ out_ = OutVector_();
		Func_ func_ = Func_();
		if constexpr (EmuMath::TMP::is_emu_vector_v<Rhs_>)
		{
			_vector_bitwise_non_shift_op_rhs_vector<0, OutVector_, LhsVector_, Rhs_, Func_>(lhs_, rhs_, out_, func_);
		}
		else
		{
			_vector_bitwise_non_shift_op_rhs_scalar<0, OutVector_, LhsVector_, Rhs_, Func_>(lhs_, rhs_, out_, func_);
		}
		return out_;
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
	template<template<typename Lhs__, typename Rhs__> class CmpTemplate_, class LhsVector_, class Rhs_>
	constexpr inline bool _vector_compare_magnitude(const LhsVector_& lhs_, const Rhs_& rhs_)
	{
		// Note: there is no direct magnitude calculation function as SqrMag(X) == Dot(X, X).
		if constexpr (EmuMath::TMP::is_emu_vector_v<Rhs_>)
		{
			using floating_point_type = EmuCore::TMPHelpers::highest_byte_size_t<typename LhsVector_::preferred_floating_point, typename Rhs_::preferred_floating_point>;
			using Comparator_ = CmpTemplate_<floating_point_type, floating_point_type>;
			const floating_point_type lhs_sqr_mag_ = _calculate_vector_dot_product(lhs_, lhs_);
			const floating_point_type rhs_sqr_mag_ = _calculate_vector_dot_product(rhs_, rhs_);
			return Comparator_()(lhs_sqr_mag_, rhs_sqr_mag_);
		}
		else
		{
			// Compare with final magnitude as we can't be sure the rhs_ arg is something we can square.
			// --- Further, floating point errors may make it so that (mag_ * mag_) != sqr_mag_, so better to err on the side of caution for such situations.

			using rhs_value = std::remove_cv_t<std::remove_reference_t<Rhs_>>;
			using floating_point_type = std::conditional_t
			<
				std::is_floating_point_v<rhs_value>,
				EmuCore::TMPHelpers::highest_byte_size_t<typename LhsVector_::preferred_floating_point, rhs_value>,
				typename LhsVector_::preferred_floating_point
			>;
			using Comparator_ = CmpTemplate_<floating_point_type, Rhs_>;

			const floating_point_type mag_ = EmuCore::do_sqrt_constexpr<floating_point_type>()(_calculate_vector_dot_product<floating_point_type>(lhs_, lhs_));
			return Comparator_()(mag_, rhs_);

		}
	}

	template<std::size_t Index_, class OutVector_, class Comparison_, class LhsVector_, class RhsScalar_>
	constexpr inline void _perform_vector_per_element_comparison_rhs_scalar
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
	constexpr inline void _perform_vector_per_element_comparison_rhs_vector
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
			_perform_vector_per_element_comparison_rhs_scalar<0, OutVector_, Comparison_, LhsVector_, Rhs_>(lhs_, rhs_, out_, cmpFunc_);
		}
		return out_;
	}
	template<std::size_t Index_, class LhsVector_, class Rhs_, class Comparator_, class Combiner_>
	[[nodiscard]] constexpr inline bool _vector_overall_comparison_scalar(const LhsVector_& lhs_, const Rhs_& rhs_, Comparator_& cmp_, Combiner_& combiner_, bool out_)
	{
		if constexpr (Index_ < LhsVector_::size)
		{
			return _vector_overall_comparison_scalar<Index_ + 1, LhsVector_, Rhs_, Comparator_, Combiner_>
			(
				lhs_,
				rhs_,
				cmp_,
				combiner_,
				combiner_(out_, cmp_(_get_vector_data<Index_>(lhs_), rhs_))
			);
		}
		else
		{
			return out_;
		}
	}
	template<std::size_t Index_, bool IncludeNonContained_, class LhsVector_, class RhsVector_, class Comparator_, class Combiner_>
	[[nodiscard]] constexpr inline bool _vector_overall_comparison(const LhsVector_& lhs_, const RhsVector_& rhs_, Comparator_& cmp_, Combiner_& combiner_, bool out_)
	{
		if constexpr (IncludeNonContained_)
		{
			// ALL ELEMENTS OF LHS AND RHS, NON-EXISTEND ASSUMED AS DEFAULT CONSTRUCTED
			if constexpr (Index_ < LhsVector_::size || Index_ < RhsVector_::size)
			{
				if constexpr (Index_ < LhsVector_::size)
				{
					if constexpr (Index_ < RhsVector_::size)
					{
						return _vector_overall_comparison<Index_ + 1, IncludeNonContained_, LhsVector_, RhsVector_, Comparator_, Combiner_>
						(
							lhs_,
							rhs_,
							cmp_,
							combiner_,
							combiner_(out_, static_cast<bool>(cmp_(_get_vector_data<Index_>(lhs_), _get_vector_data<Index_>(rhs_))))
						);
					}
					else
					{
						// Defer to comparing to scalar so we don't have to keep default constructing a rhs value in cases where lhs is significantly larger
						return _vector_overall_comparison_scalar<Index_, LhsVector_, typename RhsVector_::value_type, Comparator_, Combiner_>
						(
							lhs_,
							typename RhsVector_::value_type(),
							cmp_,
							combiner_,
							out_
						);
					}
				}
				else
				{
					// Only reach this point if RhsVector_ is in Index_ range but LhsVector_ is not.
					return _vector_overall_comparison<Index_ + 1, IncludeNonContained_, LhsVector_, RhsVector_, Comparator_, Combiner_>
					(
						lhs_,
						rhs_,
						cmp_,
						combiner_,
						combiner_(out_, static_cast<bool>(cmp_(typename LhsVector_::value_type(), _get_vector_data<Index_>(rhs_))))
					);
				}
			}
			else
			{
				return out_;
			}
		}
		else
		{
			// ONLY INCLUDING LHS ELEMENTS
			if constexpr (Index_ < LhsVector_::size)
			{
				if constexpr (Index_ < RhsVector_::size)
				{
					return _vector_overall_comparison<Index_ + 1, IncludeNonContained_, LhsVector_, RhsVector_, Comparator_, Combiner_>
					(
						lhs_,
						rhs_,
						cmp_,
						combiner_,
						combiner_(out_, static_cast<bool>(cmp_(_get_vector_data<Index_>(lhs_), _get_vector_data<Index_>(rhs_))))
					);
				}
				else
				{
					return out_;
				}
			}
			else
			{
				return out_;
			}
		}
	}
	/// <summary>
	/// <para> Performs an overall comparison of the elements of the passed lhs vector using the provided rhs. </para>
	/// <para>
	///		Only the lowest-indexed vector will be tested up to if IncludeNonContained_ is false, otherwise the highest index will be tested to against default value_types.
	/// </para>
	/// <para>
	///		If LogicalAND is true, resulting booleans will be combined with && (i.e. all must be true for a true return). 
	///		Otherwise, they will be combined with || (i.e. at least one must be true for a true return).
	/// </para>
	/// <para> If AllowScalar_ is false, this will perform a magnitude comparison in cases where Rhs_ is not an EmuMath vector. </para>
	/// </summary>
	/// <typeparam name="LhsVector_">Type of vector appearing as the left-hand argument for comparisons.</typeparam>
	/// <typeparam name="RhsVector_">Type of item appearing as the right-hand argument for comparisons.</typeparam>
	/// <typeparam name="Comparator_">Type used to perform comparisons.</typeparam>
	/// <param name="lhs_">Vector appearing as the left-hand argument for comparisons.</param>
	/// <param name="rhs_">Item appearing as the right-hand argument for comparisons.</param>
	template<bool IncludeNonContained_, bool LogicalAND_, bool AllowScalar_, template<typename Lhs__, typename Rhs__> class ComparatorTemplate_, class LhsVector_, class Rhs_>
	[[nodiscard]] constexpr inline bool _vector_overall_comparison(const LhsVector_& lhs_, const Rhs_& rhs_)
	{
		using Combiner_ = std::conditional_t<LogicalAND_, std::logical_and<void>, std::logical_or<void>>;

		if constexpr (EmuMath::TMP::is_emu_vector_v<Rhs_>)
		{
			using Comparator_ = ComparatorTemplate_<typename LhsVector_::value_type, typename Rhs_::value_type>;
			Combiner_ combiner_ = Combiner_();
			Comparator_ cmp_ = Comparator_();
			return _vector_overall_comparison<0, IncludeNonContained_, LhsVector_, Rhs_, Comparator_, Combiner_>(lhs_, rhs_, cmp_, combiner_, LogicalAND_);
		}
		else
		{
			if constexpr (AllowScalar_)
			{
				// If scalars are allowed for rhs, that means we're comparing each element to the same value
				using Comparator_ = ComparatorTemplate_<typename LhsVector_::value_type, Rhs_>;
				Combiner_ combiner_ = Combiner_();
				Comparator_ cmp_ = Comparator_();
				return _vector_overall_comparison_scalar<0, LhsVector_, Rhs_, Comparator_, Combiner_>(lhs_, rhs_, cmp_, combiner_, LogicalAND_);
			}
			else
			{
				// When comparing to a non-vector, we assume a scalar comparison.
				// --- We substitute lhs_ with its magnitude for this scalar comparison.
				return _vector_compare_magnitude<ComparatorTemplate_, LhsVector_, Rhs_>(lhs_, rhs_);
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
}

#endif
