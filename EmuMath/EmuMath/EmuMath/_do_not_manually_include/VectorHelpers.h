#ifndef EMU_MATH_VECTOR_T_HELPERS_H_INC_
#define EMU_MATH_VECTOR_T_HELPERS_H_INC_

#include "../GeneralMath.h"
#include "VectorHelpersUnderlying.h"
#include <functional>

namespace EmuMath::Helpers
{
#pragma region GETS
	template<std::size_t Index_, class Vector_>
	[[nodiscard]] constexpr inline typename Vector_::value_type& VectorGet(Vector_& vector_)
	{
		if constexpr (_underlying_vector_funcs::_validity_check_vector_get<Index_, Vector_>())
		{
			return _underlying_vector_funcs::_get_vector_data<Index_, Vector_>(vector_);
		}
		else
		{
			static_assert
			(
				false,
				"A validity check on arguments provided for EmuMath::Helpers::VectorGet has failed. Review additional assertions from the file \"VectorHelpersUnderlying.h\" for more information."
			);
		}
	}
	template<std::size_t Index_, class Vector_>
	[[nodiscard]] constexpr inline const typename Vector_::value_type& VectorGet(const Vector_& vector_)
	{
		if constexpr (_underlying_vector_funcs::_validity_check_vector_get<Index_, Vector_>())
		{
			return _underlying_vector_funcs::_get_vector_data<Index_, Vector_>(vector_);
		}
		else
		{
			static_assert
			(
				false,
				"A validity check on arguments provided for EmuMath::Helpers::VectorGet has failed. Review additional assertions from the file \"VectorHelpersUnderlying.h\" for more information."
			);
		}
	}

	template<class Vector_>
	[[nodiscard]] constexpr inline typename Vector_::value_type& VectorGet(Vector_& vector_, const std::size_t index_)
	{
		if constexpr (_underlying_vector_funcs::_validity_check_vector_get<Vector_>())
		{
			return _underlying_vector_funcs::_get_vector_data<Vector_>(vector_, index_);
		}
		else
		{
			static_assert
			(
				false,
				"A validity check on arguments provided for EmuMath::Helpers::VectorGet has failed. Review additional assertions from the file \"VectorHelpersUnderlying.h\" for more information."
			);
		}
	}
	template<class Vector_>
	[[nodiscard]] constexpr inline const typename Vector_::value_type& VectorGet(const Vector_& vector_, const std::size_t index_)
	{
		if constexpr (_underlying_vector_funcs::_validity_check_vector_get<Vector_>())
		{
			return _underlying_vector_funcs::_get_vector_data<Vector_>(vector_, index_);
		}
		else
		{
			static_assert
			(
				false,
				"A validity check on arguments provided for EmuMath::Helpers::VectorGet has failed. Review additional assertions from the file \"VectorHelpersUnderlying.h\" for more information."
			);
		}
	}
#pragma endregion

#pragma region SETS
	template<class LhsVector_, class RhsVector_>
	constexpr inline LhsVector_& VectorSet(LhsVector_& lhs_, const RhsVector_& rhs_)
	{
		if constexpr (_underlying_vector_funcs::_validity_check_vector_assignment<LhsVector_, RhsVector_>())
		{
			_underlying_vector_funcs::_assign_vector_via_vector<0, LhsVector_, RhsVector_>(lhs_, rhs_);
			return lhs_;
		}
		else
		{
			static_assert
			(
				false,
				"A validity check on arguments provided for EmuMath::Helpers::VectorSet has failed. Review additional assertions from the file \"VectorHelpersUnderlying.h\" for more information."
			);
		}
	}
#pragma endregion

#pragma region PERMUTATIONS
	/// <summary>
	/// <para>
	///		Creates a vector consisting of a number of elements equal to the provided number of indices. 
	///		Each provided index references an index within the passed vector, which will be copied to the shuffled vector upon construction.
	/// </para>
	/// <para> out_value_type is an optional type param which may be used to output a vector containing a different type to that passed. </para>
	/// </summary>
	/// <typeparam name="Vector_">Type of vector to be shuffling.</typeparam>
	/// <typeparam name="out_value_type">Optional type to be contained within the output vector.</typeparam>
	/// <param name="vector_">EmuMath vector to shuffle. May be any size, but must support the range of indices provided as template arguments.</param>
	/// <returns>Shuffled EmuMath vector containing a number of elements equal to the number of indices provided, stored as the provided out_value_type.</returns>
	template<typename out_value_type, std::size_t X_, std::size_t...RemainingShuffleIndices_, class Vector_>
	[[nodiscard]] constexpr inline EmuMath::Vector<sizeof...(RemainingShuffleIndices_) + 1, out_value_type> VectorShuffle(const Vector_& vector_)
	{
		if constexpr(_underlying_vector_funcs::_validity_check_vector_shuffle<Vector_, X_, RemainingShuffleIndices_...>())
		{
			return EmuMath::Vector<sizeof...(RemainingShuffleIndices_) + 1, out_value_type>
			(
				_underlying_vector_funcs::_get_vector_data<X_>(vector_),
				_underlying_vector_funcs::_get_vector_data<RemainingShuffleIndices_>(vector_)...
			);
		}
		else
		{
			static_assert
			(
				false,
				"A validity check on arguments provided for EmuMath::Helpers::VectorShuffle has failed. Review additional assertions from the file \"VectorHelpersUnderlying.h\" for more information."
			);
		}
	}
	/// <summary>
	/// <para>
	///		Creates a vector consisting of a number of elements equal to the provided number of indices. 
	///		Each provided index references an index within the passed vector, which will be copied to the shuffled vector upon construction.
	/// </para>
	/// </summary>
	/// <typeparam name="Vector_">Type of vector to be shuffling.</typeparam>
	/// <param name="vector_">EmuMath vector to shuffle. May be any size, but must support the range of indices provided as template arguments.</param>
	/// <returns>Shuffled EmuMath vector containing a number of elements equal to the number of indices provided.</returns>
	template<std::size_t X_, std::size_t...RemainingShuffleIndices_, class Vector_>
	[[nodiscard]] constexpr inline EmuMath::Vector<sizeof...(RemainingShuffleIndices_) + 1, typename Vector_::value_type> VectorShuffle(const Vector_& vector_)
	{
		if constexpr (EmuMath::TMP::is_emu_vector_v<Vector_>)
		{
			return VectorShuffle<typename Vector_::value_type, X_, RemainingShuffleIndices_...>(vector_);
		}
		else
		{
			static_assert(false, "Failed to shuffle an EmuMath vector as the provided argument was not an EmuMath vector.");
		}
	}
#pragma endregion

#pragma region VECTOR_OPERATIONS
	template<typename OutT_, class Vector_>
	[[nodiscard]] constexpr inline OutT_ VectorElementProduct(const Vector_& vector_)
	{
		if constexpr (EmuMath::TMP::is_emu_vector_v<Vector_>)
		{
			return EmuMath::Helpers::_underlying_vector_funcs::_combine_all_vector_elements<OutT_, Vector_, std::multiplies<void>>(vector_);
		}
		else
		{
			static_assert(false, "Attempted to get the product of all elements within a non-EmuMath-vector type.");
		}
	}
	template<class Vector_>
	[[nodiscard]] constexpr inline typename Vector_::value_type VectorElementProduct(const Vector_& vector_)
	{
		return VectorElementProduct<typename Vector_::value_type, Vector_>(vector_);
	}

	template<typename OutT_, class Vector_>
	[[nodiscard]] constexpr inline OutT_ VectorElementSum(const Vector_& vector_)
	{
		if constexpr (EmuMath::TMP::is_emu_vector_v<Vector_>)
		{
			return _underlying_vector_funcs::_combine_all_vector_elements<OutT_, Vector_, std::plus<void>>(vector_);
		}
		else
		{
			static_assert(false, "Attempted to get the product of all elements within a non-EmuMath-vector type.");
		}
	}
	template<class Vector_>
	[[nodiscard]] constexpr inline typename Vector_::value_type VectorElementSum(const Vector_& vector_)
	{
		return VectorElementSum<typename Vector_::value_type, Vector_>(vector_);
	}

	template<typename OutT_ = float, class VectorA_, class VectorB_>
	[[nodiscard]] constexpr inline OutT_ VectorDotProduct(const VectorA_& a_, const VectorB_& b_)
	{
		if constexpr (_underlying_vector_funcs::_validity_check_vector_dot_product<VectorA_, VectorB_>())
		{
			return _underlying_vector_funcs::_calculate_vector_dot_product<OutT_, VectorA_, VectorB_>(a_, b_);
		}
		else
		{
			static_assert
			(
				false,
				"A validity check on arguments provided for EmuMath::Helpers::VectorDotProduct has failed. Review additional assertions from the file \"VectorHelpersUnderlying.h\" for more information."
			);
		}
	}

	template<typename OutT_, class Vector_>
	[[nodiscard]] constexpr inline OutT_ VectorSquareMagnitude(const Vector_& vector_)
	{
		if constexpr (EmuMath::TMP::is_emu_vector_v<Vector_>)
		{
			return _underlying_vector_funcs::_calculate_vector_dot_product<OutT_, Vector_, Vector_>(vector_, vector_);
		}
		else
		{
			static_assert(false, "Attempted to get the square magnitude of a vector, but passed a non-EmuMath-vector.");
		}
	}
	template<class Vector_>
	[[nodiscard]] constexpr inline typename Vector_::value_type VectorSquareMagnitude(const Vector_& vector_)
	{
		return VectorSquareMagnitude<typename Vector_::value_type, Vector_>(vector_);
	}

	template<typename OutT_ = float, class Vector_>
	[[nodiscard]] constexpr inline OutT_ VectorMagnitudeConstexpr(const Vector_& vector_)
	{
		using FloatingPoint_ = EmuCore::TMPHelpers::first_floating_point_t<OutT_, typename Vector_::value_type, float>;
		return static_cast<OutT_>(EmuMath::SqrtConstexpr<FloatingPoint_, FloatingPoint_>(VectorSquareMagnitude<FloatingPoint_, Vector_>(vector_)));
	}
	template<typename OutT_ = float, class Vector_>
	[[nodiscard]] inline OutT_ VectorMagnitude(const Vector_& vector_)
	{
		using FloatingPoint_ = EmuCore::TMPHelpers::first_floating_point_t<OutT_, typename Vector_::value_type, float>;
		return EmuMath::DoCorrectStandardSqrt<FloatingPoint_>(VectorSquareMagnitude<FloatingPoint_, Vector_>(vector_));
	}
#pragma endregion

#pragma region ARITHMETIC
	/// <summary>
	/// <para> Adds respective elements of the lhs_ vector to those of the rhs_ vector. </para>
	/// </summary>
	/// <typeparam name="OutVector_">Type of vector to output the results of addition as.</typeparam>
	/// <typeparam name="LhsVector_">Type of vector on the left-hand side of the addition.</typeparam>
	/// <typeparam name="Rhs_">Type of vector on the right-hand side of the addition.</typeparam>
	/// <param name="lhs_">Left-hand vector in the addition operation.</param>
	/// <param name="lhs_">Right-hand vector in the addition operation.</param>
	/// <returns>Vector of the provided type containing the results of the addition.</returns>
	template<class OutVector_, class LhsVector_, class RhsVector_>
	[[nodiscard]] constexpr inline OutVector_ VectorAdd(const LhsVector_& lhs_, const RhsVector_& rhs_)
	{
		if constexpr (_underlying_vector_funcs::_validity_check_vector_arithmetic<OutVector_, LhsVector_, RhsVector_>())
		{
			return _underlying_vector_funcs::_perform_vector_arithmetic<OutVector_, LhsVector_, RhsVector_, std::plus<void>>(lhs_, rhs_);
		}
		else
		{
			static_assert
			(
				false,
				"A validity check on arguments provided for EmuMath::Helpers::VectorAdd has failed. Review additional assertions from the file \"VectorHelpersUnderlying.h\" for more information."
			);
		}
	}
	template<std::size_t OutSize_, typename out_value_type, class LhsVector_, class RhsVector_>
	[[nodiscard]] constexpr inline auto VectorAdd(const LhsVector_& lhs_, const RhsVector_& rhs_)
	{
		return VectorAdd<EmuMath::Vector<OutSize_, out_value_type>, LhsVector_, RhsVector_>(lhs_, rhs_);
	}
	template<std::size_t OutSize_, class LhsVector_, class RhsVector_>
	[[nodiscard]] constexpr inline auto VectorAdd(const LhsVector_& lhs_, const RhsVector_& rhs_)
	{
		return VectorAdd<EmuMath::Vector<OutSize_, typename LhsVector_::value_type>, LhsVector_, RhsVector_>(lhs_, rhs_);
	}
	template<class LhsVector_, class RhsVector_>
	[[nodiscard]] constexpr inline LhsVector_ VectorAdd(const LhsVector_& lhs_, const RhsVector_& rhs_)
	{
		return VectorAdd<LhsVector_, LhsVector_, RhsVector_>(lhs_, rhs_);
	}

	/// <summary>
	/// <para> Subtracts respective elements of the lhs_ vector by those of the rhs_ vector. </para>
	/// </summary>
	/// <typeparam name="OutVector_">Type of vector to output the results of subtraction as.</typeparam>
	/// <typeparam name="LhsVector_">Type of vector on the left-hand side of the subtraction.</typeparam>
	/// <typeparam name="Rhs_">Type of vector on the right-hand side of the subtraction.</typeparam>
	/// <param name="lhs_">EmuMath vector to be subtracted from.</param>
	/// <param name="rhs_">EmuMath vector of amounts to subtract from respective elements.</param>
	/// <returns>Vector of the provided type containing the results of the subtraction.</returns>
	template<class OutVector_, class LhsVector_, class RhsVector_>
	[[nodiscard]] constexpr inline OutVector_ VectorSubtract(const LhsVector_& lhs_, const RhsVector_& rhs_)
	{
		if constexpr (_underlying_vector_funcs::_validity_check_vector_arithmetic<OutVector_, LhsVector_, RhsVector_>())
		{
			return _underlying_vector_funcs::_perform_vector_arithmetic<OutVector_, LhsVector_, RhsVector_, std::minus<void>>(lhs_, rhs_);
		}
		else
		{
			static_assert
			(
				false,
				"A validity check on arguments provided for EmuMath::Helpers::VectorSubtract has failed. Review additional assertions from the file \"VectorHelpersUnderlying.h\" for more information."
			);
		}
	}
	template<std::size_t OutSize_, typename out_value_type, class LhsVector_, class RhsVector_>
	[[nodiscard]] constexpr inline auto VectorSubtract(const LhsVector_& lhs_, const RhsVector_& rhs_)
	{
		return VectorSubtract<EmuMath::Vector<OutSize_, out_value_type>, LhsVector_, RhsVector_>(lhs_, rhs_);
	}
	template<std::size_t OutSize_, class LhsVector_, class RhsVector_>
	[[nodiscard]] constexpr inline auto VectorSubtract(const LhsVector_& lhs_, const RhsVector_& rhs_)
	{
		return VectorSubtract<EmuMath::Vector<OutSize_, typename LhsVector_::value_type>, LhsVector_, RhsVector_>(lhs_, rhs_);
	}
	template<class LhsVector_, class RhsVector_>
	[[nodiscard]] constexpr inline LhsVector_ VectorSubtract(const LhsVector_& lhs_, const RhsVector_& rhs_)
	{
		return VectorSubtract<LhsVector_, LhsVector_, RhsVector_>(lhs_, rhs_);
	}

	/// <summary>
	/// <para> Multiplies respective elements of the lhs_ vector by those of a rhs_ vector, or multiplies all elements of the lhs_ vector by a rhs_ scalar. </para>
	/// </summary>
	/// <typeparam name="OutVector_">Type of vector to output the results of multiplication as.</typeparam>
	/// <typeparam name="LhsVector_">Type of vector on the left-hand side of the multiplication.</typeparam>
	/// <typeparam name="Rhs_">Type of either vector or scalar on the right-hand side of the multiplication.</typeparam>
	/// <param name="lhs_">EmuMath vector to be multiplied.</param>
	/// <param name="rhs_">EmuMath vector to multiply respective elements by, or a scalar to multiply every element by.</param>
	/// <returns>Vector of the provided type containing the results of the multiplication.</returns>
	template<class OutVector_, class LhsVector_, class Rhs_>
	[[nodiscard]] constexpr inline OutVector_ VectorMultiply(const LhsVector_& lhs_, const Rhs_& rhs_)
	{
		if constexpr (_underlying_vector_funcs::_validity_check_vector_arithmetic_potential_scalar<OutVector_, LhsVector_>())
		{
			return _underlying_vector_funcs::_perform_vector_arithmetic<OutVector_, LhsVector_, Rhs_, std::multiplies<void>>(lhs_, rhs_);
		}
		else
		{
			static_assert
			(
				false,
				"A validity check on arguments provided for EmuMath::Helpers::VectorMultiply has failed. Review additional assertions from the file \"VectorHelpersUnderlying.h\" for more information."
			);
		}
	}
	template<std::size_t OutSize_, typename out_value_type, class LhsVector_, class Rhs_>
	[[nodiscard]] constexpr inline auto VectorMultiply(const LhsVector_& lhs_, const Rhs_& rhs_)
	{
		return VectorMultiply<EmuMath::Vector<OutSize_, out_value_type>, LhsVector_, Rhs_>(lhs_, rhs_);
	}
	template<std::size_t OutSize_, class LhsVector_, class Rhs_>
	[[nodiscard]] constexpr inline auto VectorMultiply(const LhsVector_& lhs_, const Rhs_& rhs_)
	{
		return VectorMultiply<EmuMath::Vector<OutSize_, typename LhsVector_::value_type>, LhsVector_, Rhs_>(lhs_, rhs_);
	}
	template<class LhsVector_, class Rhs_>
	[[nodiscard]] constexpr inline LhsVector_ VectorMultiply(const LhsVector_& lhs_, const Rhs_& rhs_)
	{
		return VectorMultiply<LhsVector_, LhsVector_, Rhs_>(lhs_, rhs_);
	}

	/// <summary>
	/// <para> Divides respective elements of the lhs_ vector by those of a rhs_ vector, or divides all elements of the lhs_ vector by a rhs_ scalar. </para>
	/// <para> There is an additional compile-time safety check to avoid guaranteed integral divides by 0, or casting divides by 0 to integral types. </para>
	/// <para> This function cannot provide a valid constexpr if the result requires a divide by 0, integral or not. </para>
	/// </summary>
	/// <typeparam name="OutVector_">Type of vector to output the results of division as.</typeparam>
	/// <typeparam name="LhsVector_">Type of vector on the left-hand side of the division.</typeparam>
	/// <typeparam name="Rhs_">Type of either vector or scalar on the right-hand side of the division.</typeparam>
	/// <param name="lhs_">EmuMath vector to be divided.</param>
	/// <param name="rhs_">EmuMath vector to divide respective elements by, or a scalar to divide every element by.</param>
	/// <returns>Vector of the provided type containing the results of the division.</returns>
	template<class OutVector_, class LhsVector_, class Rhs_>
	[[nodiscard]] constexpr inline OutVector_ VectorDivide(const LhsVector_& lhs_, const Rhs_& rhs_)
	{
		if constexpr
		(
			_underlying_vector_funcs::_validity_check_vector_arithmetic_potential_scalar<OutVector_, LhsVector_>() &&
			_underlying_vector_funcs::_validity_check_no_integral_divide_by_zero<OutVector_, LhsVector_, Rhs_>()
		)
		{
			return _underlying_vector_funcs::_perform_vector_arithmetic<OutVector_, LhsVector_, Rhs_, std::divides<void>>(lhs_, rhs_);
		}
		else
		{
			static_assert
			(
				false,
				"A validity check on arguments provided for EmuMath::Helpers::VectorDivide has failed. Review additional assertions from the file \"VectorHelpersUnderlying.h\" for more information."
			);
		}
	}
	template<std::size_t OutSize_, typename out_value_type, class LhsVector_, class Rhs_>
	[[nodiscard]] constexpr inline auto VectorDivide(const LhsVector_& lhs_, const Rhs_& rhs_)
	{
		return VectorDivide<EmuMath::Vector<OutSize_, out_value_type>, LhsVector_, Rhs_>(lhs_, rhs_);
	}
	template<std::size_t OutSize_, class LhsVector_, class Rhs_>
	[[nodiscard]] constexpr inline auto VectorDivide(const LhsVector_& lhs_, const Rhs_& rhs_)
	{
		return VectorDivide<EmuMath::Vector<OutSize_, typename LhsVector_::value_type>, LhsVector_, Rhs_>(lhs_, rhs_);
	}
	template<class LhsVector_, class Rhs_>
	[[nodiscard]] constexpr inline LhsVector_ VectorDivide(const LhsVector_& lhs_, const Rhs_& rhs_)
	{
		return VectorDivide<LhsVector_, LhsVector_, Rhs_>(lhs_, rhs_);
	}
#pragma endregion
}

#endif
