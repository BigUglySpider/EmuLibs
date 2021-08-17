#ifndef EMU_MATH_VECTOR_T_HELPERS_UNDERLYING_H_INC_
#define EMU_MATH_VECTOR_T_HELPERS_UNDERLYING_H_INC_ 1

#include "../../EmuCore/TMPHelpers/TypeComparators.h"
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
				_assign_vector_via_scalar<Index_, OutVector_>(out_, static_cast<out_value>(func_(vector_value())));
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
				_assign_vector_via_scalar<Index_, OutVector_>(out_, std::numeric_limits<out_value>::infinity());
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
				_assign_vector_via_scalar<Index_, OutVector_>(out_, cmp_(val_, clampScalar_) ? static_cast<out_value>(clampScalar_) : static_cast<out_value>(val_));
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

	template<std::size_t Index_, class OutVector_, class Vector_, class Shifter_>
	constexpr inline void _vector_bitwise_shift_per_element_scalar_shifts(const Vector_& vector_, const std::size_t num_shifts_, OutVector_& out_, Shifter_& shifter_)
	{
		if constexpr (Index_ < OutVector_::size)
		{
			using out_value = typename OutVector_::value_type;
			if constexpr (Index_ < Vector_::size)
			{
				_get_vector_data<Index_>(out_) = static_cast<out_value>(shifter_(_get_vector_data<Index_>(vector_), num_shifts_));
				_vector_bitwise_shift_per_element_scalar_shifts<Index_ + 1, OutVector_, Vector_, Shifter_>(vector_, num_shifts_, out_, shifter_);
			}
			else
			{
				using vector_value = typename Vector_::value_type;
				if constexpr (std::is_arithmetic_v<vector_value>)
				{
					_assign_vector_via_scalar<Index_, OutVector_>(out_, static_cast<out_value>(vector_value()));
				}
				else
				{
					_assign_vector_via_scalar<Index_, OutVector_>(out_, static_cast<out_value>(shifter_(vector_value(), num_shifts_)));
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
						shifter_(_get_vector_data<Index_>(vector_), static_cast<std::size_t>(_get_vector_data<Index_>(num_shifts_)))
					);
					_vector_bitwise_shift_per_element_vector_shifts<Index_ + 1, OutVector_, Vector_, ShiftVector_, Shifter_>(vector_, num_shifts_, out_, shifter_);
				}
				else
				{
					if constexpr (std::is_arithmetic_v<vector_value>)
					{
						// If arithmetic, we know any remaining shifts would lead to 0, so simply copy 0 into the remaining indices.
						_assign_vector_via_scalar<Index_, OutVector_>(out_, static_cast<out_value>(vector_value()));
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
				_vector_bitwise_shift_per_element_scalar_shifts<Index_, OutVector_, Vector_, Shifter_>(vector_, static_cast<std::size_t>(shift_value()), out_, shifter_);
			}
		}
	}
	template<class OutVector_, class Vector_, class Shifts_, class Shifter_>
	[[nodiscard]] constexpr inline OutVector_ _vector_bitwise_shift_per_element(const Vector_& vector_, const Shifts_& num_shifts_)
	{
		OutVector_ out_ = OutVector_();
		Shifter_ shifter_ = Shifter_();
		if constexpr (EmuMath::TMP::is_emu_vector_v<Shifts_>)
		{
			using shift_value = typename Shifts_::value_type;
			if constexpr (std::is_convertible_v<shift_value, std::size_t>)
			{
				_vector_bitwise_shift_per_element_vector_shifts<0, OutVector_, Vector_, Shifts_, Shifter_>(vector_, num_shifts_, out_, shifter_);
			}
			else
			{
				static_assert(false, "Attempted to perform a bitwise shift on each element of an EmuMath vector, but the provided vector of shift amounts did not contain types convertible to std::size_t.");
			}
		}
		else
		{
			_vector_bitwise_shift_per_element_scalar_shifts<0, OutVector_, Vector_, Shifter_>(vector_, static_cast<std::size_t>(num_shifts_), out_, shifter_);
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
