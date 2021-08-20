#ifndef EMU_MATH_VECTOR_T_HELPERS_H_INC_
#define EMU_MATH_VECTOR_T_HELPERS_H_INC_ 1

#include "../../EmuCore/Functors/Arithmetic.h"
#include "../../EmuCore/Functors/Bitwise.h"
#include "../../EmuCore/Functors/Comparators.h"
#include "../../EmuCore/TMPHelpers/TypeConvertors.h"
#include "VectorHelpersUnderlying.h"
#include <functional>

namespace EmuMath::Helpers
{
#pragma region GETS
	/// <summary> Accesses the element at the specified Index_ of the passed EmuMath vector. </summary>
	/// <typeparam name="Vector_">Type of vector to get an element from.</typeparam>
	/// <param name="vector_">EmuMath vector to retrieve the specified index of.</param>
	/// <returns>Reference to the element at the provided index of the passed EmuMath vector.</returns>
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
	/// <summary> Sets respective elements of a lhs_ EmuMath vector to match those of a rhs_ EmuMath vector. </summary>
	/// <typeparam name="LhsVector_">Type of vector to set the data of.</typeparam>
	/// <typeparam name="RhsVector_">Type of vector to copy the data of.</typeparam>
	/// <param name="lhs_">EmuMath vector to set the data of.</param>
	/// <param name="rhs_">EmuMath vector to copy the data of.</param>
	/// <returns>Reference to the lhs_ vector after setting.</returns>
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

	/// <summary>
	/// <para> Creates a vector containing a number of reference elements equal to the provided number of indices. </para>
	/// <para>
	///		Each provided index references an index within the passed vector, 
	///		which will be referenced in the output vector's index of the index's place in the provided indices.
	/// </para>
	/// </summary>
	/// <typeparam name="Vector_">Type of vector to create a shuffled reference vector of.</typeparam>
	/// <param name="vector_">EmuMath vector to create a shuffled reference vector of.</param>
	/// <returns>
	///		Shuffled constant reference vector containing a number of elements equal to the provided number of index arguments.
	///		Elements are references to the elements at specified indices within the passed vector.
	/// </returns>
	template<std::size_t X_, std::size_t...RemainingShuffleIndices_, class Vector_>
	[[nodiscard]] constexpr inline EmuMath::ConstRefVector<sizeof...(RemainingShuffleIndices_) + 1, typename Vector_::value_type> VectorShuffledConstReference
	(
		const Vector_& vector_
	)
	{
		if constexpr (EmuMath::TMP::is_emu_vector_v<Vector_>)
		{
			return EmuMath::ConstRefVector<sizeof...(RemainingShuffleIndices_) + 1, typename Vector_::value_type>
			(
				_underlying_vector_funcs::_get_vector_data<X_>(vector_),
				_underlying_vector_funcs::_get_vector_data<RemainingShuffleIndices_>(vector_)...
			);
		}
		else
		{
			static_assert(false, "Failed to retrieve a shuffled EmuMath vector constant reference as the provided argument was not an EmuMath vector.");
		}
	}

	/// <summary>
	/// <para> Creates a vector containing a number of reference elements equal to the provided number of indices. </para>
	/// <para>
	///		Each provided index references an index within the passed vector, 
	///		which will be referenced in the output vector's index of the index's place in the provided indices.
	/// </para>
	/// </summary>
	/// <typeparam name="Vector_">Type of vector to create a shuffled reference vector of.</typeparam>
	/// <param name="vector_">EmuMath vector to create a shuffled reference vector of.</param>
	/// <returns>
	///		Shuffled reference vector containing a number of elements equal to the provided number of index arguments.
	///		Elements are references to the elements at specified indices within the passed vector.
	/// </returns>
	template<std::size_t X_, std::size_t...RemainingShuffleIndices_, class Vector_>
	[[nodiscard]] constexpr inline EmuMath::RefVector<sizeof...(RemainingShuffleIndices_) + 1, typename Vector_::value_type> VectorShuffledReference
	(
		Vector_& vector_
	)
	{
		if constexpr (EmuMath::TMP::is_emu_vector_v<Vector_>)
		{
			return EmuMath::RefVector<sizeof...(RemainingShuffleIndices_) + 1, typename Vector_::value_type>
			(
				_underlying_vector_funcs::_get_vector_data<X_>(vector_),
				_underlying_vector_funcs::_get_vector_data<RemainingShuffleIndices_>(vector_)...
			);
		}
		else
		{
			static_assert(false, "Failed to retrieve a shuffled EmuMath vector reference as the provided argument was not an EmuMath vector.");
		}
	}
	template<std::size_t X_, std::size_t...RemainingShuffleIndices_, class Vector_>
	[[nodiscard]] constexpr inline EmuMath::ConstRefVector<sizeof...(RemainingShuffleIndices_) + 1, typename Vector_::value_type> VectorShuffledReference
	(
		const Vector_& vector_
	)
	{
		return VectorShuffledConstReference<X_, RemainingShuffleIndices_...>(vector_);
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
			using adder_type = EmuCore::do_add<typename LhsVector_::value_type, typename RhsVector_::value_type>;
			return _underlying_vector_funcs::_perform_vector_arithmetic<OutVector_, LhsVector_, RhsVector_, adder_type>(lhs_, rhs_);
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
			using subtractor_type = EmuCore::do_subtract<typename LhsVector_::value_type, typename RhsVector_::value_type>;
			return _underlying_vector_funcs::_perform_vector_arithmetic<OutVector_, LhsVector_, RhsVector_, subtractor_type>(lhs_, rhs_);
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
			if constexpr (EmuMath::TMP::is_emu_vector_v<Rhs_>)
			{
				using multiplier_type = EmuCore::do_multiply<typename LhsVector_::value_type, typename Rhs_::value_type>;
				return _underlying_vector_funcs::_perform_vector_arithmetic<OutVector_, LhsVector_, Rhs_, multiplier_type>(lhs_, rhs_);
			}
			else
			{
				using multiplier_type = EmuCore::do_multiply<typename LhsVector_::value_type, Rhs_>;
				return _underlying_vector_funcs::_perform_vector_arithmetic<OutVector_, LhsVector_, Rhs_, multiplier_type>(lhs_, rhs_);
			}
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
	[[nodiscard]] constexpr inline auto VectorMultiply(const LhsVector_& lhs_, const Rhs_& rhs_)
	{
		return VectorMultiply<LhsVector_::size, typename LhsVector_::value_type, LhsVector_, Rhs_>(lhs_, rhs_);
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
			if constexpr (EmuMath::TMP::is_emu_vector_v<Rhs_>)
			{
				using divider_type = EmuCore::do_divide<typename LhsVector_::value_type, typename Rhs_::value_type>;
				return _underlying_vector_funcs::_perform_vector_arithmetic<OutVector_, LhsVector_, Rhs_, divider_type>(lhs_, rhs_);
			}
			else
			{
				using divider_type = EmuCore::do_divide<typename LhsVector_::value_type, Rhs_>;
				return _underlying_vector_funcs::_perform_vector_arithmetic<OutVector_, LhsVector_, Rhs_, divider_type>(lhs_, rhs_);
			}
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

	/// <summary>
	/// <para> Negates the elements of the passed vector and returns the result in the output vector, where out[x] == -vector_[x]. </para>
	/// </summary>
	/// <typeparam name="out_value_type">Type to be contained in the output vector.</typeparam>
	/// <typeparam name="Vector_">Type of vector to negate the elements of.</typeparam>
	/// <param name="vector_">EmuMath vector to negate the elements of.</param>
	/// <returns>Vector whose elements are the negated form of the respective elements in the passed vector_.</returns>
	template<std::size_t OutSize_, typename out_value_type, class Vector_>
	[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, out_value_type> VectorNegate(const Vector_& vector_)
	{
		if constexpr (EmuMath::TMP::is_emu_vector_v<Vector_>)
		{
			using negator_type = EmuCore::do_negate<typename Vector_::value_type>;
			return _underlying_vector_funcs::_vector_single_operand_func<EmuMath::Vector<OutSize_, out_value_type>, Vector_, negator_type>(vector_);
		}
		else
		{
			static_assert(false, "Attempted to negate a vector, but passed a non-EmuMath-vector argument type.");
		}
	}
	template<typename out_value_type, class Vector_>
	[[nodiscard]] constexpr inline auto VectorNegate(const Vector_& vector_)
	{
		return VectorNegate<Vector_::size, out_value_type>(vector_);
	}
	template<std::size_t OutSize_, class Vector_>
	[[nodiscard]] constexpr inline auto VectorNegate(const Vector_& vector_)
	{
		return VectorNegate<OutSize_, typename Vector_::value_type>(vector_);
	}
	template<class Vector_>
	[[nodiscard]] constexpr inline auto VectorNegate(const Vector_& vector_)
	{
		return VectorNegate<Vector_::size, typename Vector_::value_type>(vector_);
	}
#pragma endregion

#pragma region VECTOR_OPERATIONS
	/// <summary> Calculates the product of multiplying all elements within the passed vector and returns it as the optional provided OutT_. </summary>
	/// <typeparam name="OutT_">Optional type to output as. If not provided, this will match the vector's value_type.</typeparam>
	/// <typeparam name="Vector_">Type of vector to multiply all elements of.</typeparam>
	/// <param name="vector_">EmuMath vector to multiply all elements of.</param>
	/// <returns>Product of all elements within the passed vector.</returns>
	template<typename OutT_, class Vector_>
	[[nodiscard]] constexpr inline OutT_ VectorElementProduct(const Vector_& vector_)
	{
		if constexpr (EmuMath::TMP::is_emu_vector_v<Vector_>)
		{
			using multiplier_type = EmuCore::do_multiply<typename Vector_::value_type, typename Vector_::value_type>;
			return EmuMath::Helpers::_underlying_vector_funcs::_combine_all_vector_elements<OutT_, Vector_, multiplier_type>(vector_);
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

	/// <summary> Calculates the sum of adding all elements within the passed vector and returns it as the optional provided OutT_. </summary>
	/// <typeparam name="OutT_">Optional type to output as. If not provided, this will match the vector's value_type.</typeparam>
	/// <typeparam name="Vector_">Type of vector to add all elements of.</typeparam>
	/// <param name="vector_">EmuMath vector to multiply all elements of.</param>
	/// <returns>Sum of all elements within the passed vector.</returns>
	template<typename OutT_, class Vector_>
	[[nodiscard]] constexpr inline OutT_ VectorElementSum(const Vector_& vector_)
	{
		if constexpr (EmuMath::TMP::is_emu_vector_v<Vector_>)
		{
			using adder_type = EmuCore::do_add<typename Vector_::value_type, typename Vector_::value_type>;
			return _underlying_vector_funcs::_combine_all_vector_elements<OutT_, Vector_, adder_type>(vector_);
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

	/// <summary>
	/// <para> Calculates the dot product of the vectors a_ and b_ and outputs it as the provided OutT_ type, which defaults to float. </para>
	/// </summary>
	/// <typeparam name="OutT_">Type to output the dot product as. Defaults to float.</typeparam>
	/// <typeparam name="VectorA_">Type of vector A in the equation A DOT B.</typeparam>
	/// <typeparam name="VectorB_">Type of vector B in the equation A DOT B.</typeparam>
	/// <param name="a_">EmuMath vector A in the equation A DOT B.</param>
	/// <param name="b_">EmuMath vector B in the equation A DOT B.</param>
	/// <returns>Dot product of the passed vectors, represented as the provided OutT_.</returns>
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

	/// <summary>
	/// <para> Calculates the squared magnitude of the passed vector, and outputs it as the optional provided OutT_ type. </para>
	/// <para> If OutT_ is not provided, the returned square magnitude will be of the same type as the passed vector's value_type. </para>
	/// <para> Note that a vector's square magnitude is equivalent to its dot product with itself (i.e. SQUARE_MAG(V) == V DOT V). </para>
	/// </summary>
	/// <typeparam name="OutT_">Type to output the square magnitude as. Optional.</typeparam>
	/// <typeparam name="Vector_">Type of vector to calculate the square magnitude of.</typeparam>
	/// <param name="vector_">EmuMath vector to calculate the square magnitude of.</param>
	/// <returns>Square magnitude of the passed vector, represented as OutT_ if provided, otherwise represented as the passed vector's value_type.</returns>
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

	/// <summary>
	/// <para>
	///		Calculates the passed vector's magnitude via means which may be evaluated at compile time for constant expressions, 
	///		and outputs it as the optional provided OutT_ type, which defaults to float.
	/// </para>
	/// <para> If this will be executed at runtime, it is recommended to use VectorMagnitude(vector_) instead as this function may sacrifice performance to be constexpr. </para>
	/// </summary>
	/// <typeparam name="Vector_">Type of vector to calculate the magnitude of.</typeparam>
	/// <typeparam name="OutT_">Optional type to output the magnitude as. Defaults to float.</typeparam>
	/// <param name="vector_">EmuMath vector to calculate the magnitude of.</param>
	/// <returns>Magnitude of the passed vector, represented as OutT_ if provided, otherwise represented as the passed vector's value_type.</returns>
	template<typename OutT_ = float, class Vector_>
	[[nodiscard]] constexpr inline OutT_ VectorMagnitudeConstexpr(const Vector_& vector_)
	{
		using FloatingPoint_ = EmuCore::TMPHelpers::first_floating_point_t<OutT_, typename Vector_::value_type, float>;
		return static_cast<OutT_>(EmuCore::SqrtConstexpr<FloatingPoint_, FloatingPoint_>(VectorSquareMagnitude<FloatingPoint_, Vector_>(vector_)));
	}
	/// <summary>
	/// <para>Calculates the passed vector's magnitude and outputs it as the optional provided OutT_ type. </para>
	/// </summary>
	/// <typeparam name="Vector_">Type of vector to calculate the magnitude of.</typeparam>
	/// <typeparam name="OutT_">Optional type to output the magnitude as. Defaults to float.</typeparam>
	/// <param name="vector_">EmuMath vector to calculate the magnitude of.</param>
	/// <returns>Magnitude of the passed vector, represented as OutT_ if provided, otherwise represented as the passed vector's value_type.</returns>
	template<typename OutT_ = float, class Vector_>
	[[nodiscard]] inline OutT_ VectorMagnitude(const Vector_& vector_)
	{
		using FloatingPoint_ = EmuCore::TMPHelpers::first_floating_point_t<OutT_, typename Vector_::value_type, float>;
		return EmuCore::DoMatchingStandardSqrt<FloatingPoint_>(VectorSquareMagnitude<FloatingPoint_, Vector_>(vector_));
	}

	/// <summary>
	/// <para> Calculates the reciprocal to the passed EmuMath vector's magnitude. </para>
	/// <para>
	///		To be executed at compile-time, this function may make some sacrifices. 
	///		As such, VectorMagnitudeReciprocal or VectorMagnitudeReciprocalQrsqrt are recommended to be used instead if this is being called at runtime.
	/// </para>
	/// </summary>
	/// <typeparam name="OutFloatingPoint_">Type to output the magnitude reciprocal as.</typeparam>
	/// <typeparam name="Vector_">Type of vector to find the reciprocal to the magnitude of.</typeparam>
	/// <param name="vector_">EmuMath vector to find the reciprocal to the magnitude of.</param>
	/// <returns>Reciprocal to the passed EmuMath vector's magnitude, represented as the provided OutFloatingPoint_ type.</returns>
	template<typename OutFloatingPoint_ = float, class Vector_>
	[[nodiscard]] constexpr inline OutFloatingPoint_ VectorMagnitudeReciprocalConstexpr(const Vector_& vector_)
	{
		if constexpr (std::is_floating_point_v<OutFloatingPoint_>)
		{
			return OutFloatingPoint_(1.0) / VectorMagnitudeConstexpr<OutFloatingPoint_, Vector_>(vector_);
		}
		else
		{
			static_assert(false, "Attempted to retrieve an EmuMath vector's magnitude reciprocal with a non-floating-point output type.");
		}
	}
	/// <summary>
	/// <para> Calculates the reciprocal to the passed EmuMath vector's magnitude. </para>
	/// </summary>
	/// <typeparam name="OutFloatingPoint_">Type to output the magnitude reciprocal as.</typeparam>
	/// <typeparam name="Vector_">Type of vector to find the reciprocal to the magnitude of.</typeparam>
	/// <param name="vector_">EmuMath vector to find the reciprocal to the magnitude of.</param>
	/// <returns>Reciprocal to the passed EmuMath vector's magnitude, represented as the provided OutFloatingPoint_ type.</returns>
	template<typename OutFloatingPoint_ = float, class Vector_>
	[[nodiscard]] inline OutFloatingPoint_ VectorMagnitudeReciprocal(const Vector_& vector_)
	{
		if constexpr (std::is_floating_point_v<OutFloatingPoint_>)
		{
			return OutFloatingPoint_(1.0) / VectorMagnitude<OutFloatingPoint_, Vector_>(vector_);
		}
		else
		{
			static_assert(false, "Attempted to retrieve an EmuMath vector's magnitude reciprocal with a non-floating-point output type.");
		}
	}
	/// <summary>
	/// <para> Calculates the reciprocal to the passed EmuMath vector's magnitude, using the Q_rsqrt method. </para>
	/// <para> A custom number of newton iterations may be provided to increase accuracy. Additionally, the magic constant may also be changed from 0x5F3759DF. </para>
	/// </summary>
	/// <typeparam name="OutFloatingPoint_">Type to output the magnitude reciprocal as.</typeparam>
	/// <typeparam name="Vector_">Type of vector to find the reciprocal to the magnitude of.</typeparam>
	/// <param name="vector_">EmuMath vector to find the reciprocal to the magnitude of.</param>
	/// <returns>Reciprocal to the passed EmuMath vector's magnitude, represented as the provided OutFloatingPoint_ type.</returns>
	template<typename OutFloatingPoint_ = float, std::size_t NumNewtonIterations_ = 1, std::int32_t MagicConstant_ = 0x5F3759DF, class Vector_>
	[[nodiscard]] inline OutFloatingPoint_ VectorMagnitudeReciprocalQrsqrt(const Vector_& vector_)
	{
		if constexpr (std::is_floating_point_v<OutFloatingPoint_>)
		{
			return EmuCore::Q_rsqrt<OutFloatingPoint_, NumNewtonIterations_, MagicConstant_, OutFloatingPoint_>
			(
				VectorSquareMagnitude<OutFloatingPoint_, Vector_>(vector_)
			);
		}
		else
		{
			static_assert(false, "Attempted to retrieve an EmuMath vector's magnitude reciprocal with a non-floating-point output type.");
		}
	}

	/// <summary> Returns a copy of the lowest value within the passed EmuMath vector. </summary>
	/// <typeparam name="Vector_">Type of vector to find the lowest value of.</typeparam>
	/// <param name="vector_">EmuMath vector to find the lowest value of.</param>
	/// <returns>Copy of the lowest value within the passed vector.</returns>
	template<class Vector_>
	[[nodiscard]] constexpr inline typename Vector_::value_type VectorMin(const Vector_& vector_)
	{
		if constexpr (EmuMath::TMP::is_emu_vector_v<Vector_>)
		{
			return _underlying_vector_funcs::_find_vector_min<Vector_>(vector_);
		}
		else
		{
			static_assert(false, "Attempted to get the lowest value within an EmuMath vector, but provided a non-EmuMath-vector argument.");
		}
	}

	/// <summary> Returns a copy of the highest value within the passed EmuMath vector. </summary>
	/// <typeparam name="Vector_">Type of vector to find the highest value of.</typeparam>
	/// <param name="vector_">EmuMath vector to find the highest value of.</param>
	/// <returns>Copy of the highest value within the passed vector.</returns>
	template<class Vector_>
	[[nodiscard]] constexpr inline typename Vector_::value_type VectorMax(const Vector_& vector_)
	{
		if constexpr (EmuMath::TMP::is_emu_vector_v<Vector_>)
		{
			return _underlying_vector_funcs::_find_vector_max<Vector_>(vector_);
		}
		else
		{
			static_assert(false, "Attempted to get the highest value within an EmuMath vector, but provided a non-EmuMath-vector argument.");
		}
	}

	/// <summary> Returns a vector containing a copy of the passed vector's lowest and highest values at indices 0 and 1, respectively. </summary>
	/// <typeparam name="Vector_">Type of vector to find the lowest and highest values of.</typeparam>
	/// <param name="vector_">EmuMath vector to find the lowest and highest values of.</param>
	/// <returns>EmuMath vector containing 2 elements; index 0 is a copy of the lowest value of the passed vector, and index 1 is a copy of the highest value.</returns>
	template<class Vector_>
	[[nodiscard]] constexpr inline EmuMath::Vector<2, typename Vector_::value_type> VectorMinMax(const Vector_& vector_)
	{
		if constexpr (EmuMath::TMP::is_emu_vector_v<Vector_>)
		{
			return _underlying_vector_funcs::_find_vector_min_max<Vector_>(vector_);
		}
		else
		{
			static_assert(false, "Attempted to get the lowest and highest values within an EmuMath vector, but provided a non-EmuMath-vector argument.");
		}
	}
	/// <summary> Finds the lowest and highest values within the passed vector, and outputs copies of them via the passed min_ and max_ arguments respectively. </summary>
	/// <typeparam name="Vector_">Type of vector to find the lowest and highest values of.</typeparam>
	/// <param name="vector_">EmuMath vector to find the lowest and highest values of.</param>
	/// <param name="min_">Reference to output a copy of the lowest value to.</param>
	/// <param name="max_">Reference to output a copy of the highest value to.</param>
	template<class Vector_>
	constexpr inline void VectorMinMax(const Vector_& vector_, typename Vector_::value_type& min_, typename Vector_::value_type& max_)
	{
		if constexpr (EmuMath::TMP::is_emu_vector_v<Vector_>)
		{
			_underlying_vector_funcs::_find_vector_min_max<Vector_>(vector_, min_, max_);
		}
		else
		{
			static_assert(false, "Attempted to get the lowest and highest values within an EmuMath vector, but provided a non-EmuMath-vector argument.");
		}
	}

	/// <summary> Finds the lowest value within the passed vector and returns its index within the vector. </summary>
	/// <typeparam name="Vector_">Type of vector to find the lowest-valued index of.</typeparam>
	/// <param name="vector_">EmuMath vector to find the lowest-valued index of.</param>
	/// <returns>Index within the passed vector of its lowest element.</returns>
	template<class Vector_>
	[[nodiscard]] constexpr inline std::size_t VectorMinIndex(const Vector_& vector_)
	{
		if constexpr (EmuMath::TMP::is_emu_vector_v<Vector_>)
		{
			return _underlying_vector_funcs::_find_vector_min_index<Vector_>(vector_);
		}
		else
		{
			static_assert(false, "Attempted to get the lowest-valued index within an EmuMath vector, but provided a non-EmuMath-vector argument.");
		}
	}

	/// <summary> Finds the highest value within the passed vector and returns its index within the vector. </summary>
	/// <typeparam name="Vector_">Type of vector to find the highest-valued index of.</typeparam>
	/// <param name="vector_">EmuMath vector to find the highest-valued index of.</param>
	/// <returns>Index within the passed vector of its highest element.</returns>
	template<class Vector_>
	[[nodiscard]] constexpr inline std::size_t VectorMaxIndex(const Vector_& vector_)
	{
		if constexpr (EmuMath::TMP::is_emu_vector_v<Vector_>)
		{
			return _underlying_vector_funcs::_find_vector_max_index<Vector_>(vector_);
		}
		else
		{
			static_assert(false, "Attempted to get the highest-valued index within an EmuMath vector, but provided a non-EmuMath-vector argument.");
		}
	}

	/// <summary> Returns a vector containing the indices of the passed vector's lowest and highest values at indices 0 and 1, respectively. </summary>
	/// <typeparam name="Vector_">Type of vector to find the lowest- and highest-valued indices of.</typeparam>
	/// <param name="vector_">EmuMath vector to find the lowest- and highest-valued indices of.</param>
	/// <returns>EmuMath vector containing 2 elements; index 0 is the index of the lowest value in the passed vector, and index 1 is the index of the highest value.</returns>
	template<class Vector_>
	[[nodiscard]] constexpr inline EmuMath::Vector<2, std::size_t> VectorMinMaxIndices(const Vector_& vector_)
	{
		if constexpr (EmuMath::TMP::is_emu_vector_v<Vector_>)
		{
			return _underlying_vector_funcs::_find_vector_min_max_indices<Vector_>(vector_);
		}
		else
		{
			static_assert(false, "Attempted to get the lowest- and highest-valued indices within an EmuMath vector, but provided a non-EmuMath-vector argument.");
		}
	}
	/// <summary>
	///		Finds the indices of lowest and highest values within the passed vector, 
	///		and outputs them via the passed outMinIndex_ and outMaxIndex_ reference arguments respectively.
	/// </summary>
	/// <typeparam name="Vector_">Type of vector to find the lowest- and highest-valued indices of.</typeparam>
	/// <param name="vector_">EmuMath vector to find the lowest- and highest-valued indices of.</param>
	/// <param name="min_">Reference to output the index of the lowest value to.</param>
	/// <param name="max_">Reference to output the index of the highest value to.</param>
	template<class Vector_>
	constexpr inline void VectorMinMaxIndices(const Vector_& vector_, std::size_t& outMinIndex_, std::size_t& outMaxIndex_)
	{
		if constexpr (EmuMath::TMP::is_emu_vector_v<Vector_>)
		{
			_underlying_vector_funcs::_find_vector_min_max_indices<Vector_>(vector_, outMinIndex_, outMaxIndex_);
		}
		else
		{
			static_assert(false, "Attempted to get the lowest- and highest-valued indices within an EmuMath vector, but provided a non-EmuMath-vector argument.");
		}
	}

	/// <summary>
	/// <para> Calculates the resulting vector from a linear interpolation of the passed vector and operands, which can be summarised as a_ + ((b_ - a_) * t_). </para>
	/// <para>
	///		B_ may be either a vector or a scalar. If it is a vector, all elements of a_ will be interpolated with their respective elements in b_. 
	///		Otherwise, all elements of a_ will be interpolated with the value of b_.
	/// </para>
	/// <para>
	///		T_ may be either a vector or a scalar. If it is a vector, all linear interpolations will be weighted by the value in the respective element in t_. 
	///		Otherwise, all linear interpolations will be weighted by the value of t_.
	/// </para>
	/// <para> If no OutSize_ is provided, the output vector size will be that of a_. </para>
	/// <para> If no out_value_type is provided, the output vector's contained type will be the same as that in a_. </para>
	/// </summary>
	/// <typeparam name="out_value_type">Type to be contained in the output vector.</typeparam>
	/// <typeparam name="AVector_">Type of the vector a in the equation a + ((b - a) * t).</typeparam>
	/// <typeparam name="B_">Type of b in the equation a + ((b - a) * t).</typeparam>
	/// <typeparam name="T_">Type of t in the equation a + ((b - a) * t).</typeparam>
	/// <param name="a_">EmuMath vector that acts as a in the equation a + ((b - a) * t).</param>
	/// <param name="b_">EmuMath vector or scalar that acts as b in the equation a + ((b - a) * t).</param>
	/// <param name="t_">EmuMath vector or scalar that acts as t in the equation a + ((b - a) * t).</param>
	/// <returns>Vector containing the result of linear interpolation with the provided arguments.</returns>
	template<std::size_t OutSize_, typename out_value_type, class AVector_, class B_, class T_>
	[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, out_value_type> VectorLerp(const AVector_& a_, const B_& b_, const T_& t_)
	{
		if constexpr (EmuMath::TMP::is_emu_vector_v<AVector_>)
		{
			return _underlying_vector_funcs::_vector_lerp<AVector_, B_, T_, EmuMath::Vector<OutSize_, out_value_type>>(a_, b_, t_);
		}
		else
		{
			static_assert(false, "Attempted to perform a vector lerp with a non-EmuMath-vector argument for a_.");
		}
	}
	template<typename out_value_type, class AVector_, class B_, class T_>
	[[nodiscard]] constexpr inline EmuMath::Vector<AVector_::size, out_value_type> VectorLerp(const AVector_& a_, const B_& b_, const T_& t_)
	{
		return VectorLerp<AVector_::size, out_value_type, AVector_, B_, T_>(a_, b_, t_);
	}
	template<std::size_t OutSize_, class AVector_, class B_, class T_>
	[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, typename AVector_::value_type> VectorLerp(const AVector_& a_, const B_& b_, const T_& t_)
	{
		return VectorLerp<OutSize_, typename AVector_::value_type, AVector_, B_, T_>(a_, b_, t_);
	}
	template<class AVector_, class B_, class T_>
	[[nodiscard]] constexpr inline EmuMath::Vector<AVector_::size, typename AVector_::value_type> VectorLerp(const AVector_& a_, const B_& b_, const T_& t_)
	{
		return VectorLerp<AVector_::size, typename AVector_::value_type, AVector_, B_, T_>(a_, b_, t_);
	}

	/// <summary>
	/// <para> Calculates the resulting vector from a bilinear interpolation using the passed operands. </para>
	/// <para> The underlying equation can be summarised as LERP(LERP(a, b, u), LERP(d, c, u), v). </para>
	/// <para> AVector_ and DVector_ are required to be EmuMath vectors. </para>
	/// <para> If no OutSize_ is provided, the output vector size will be that of a_. </para>
	/// <para> If no out_value_type is provided, the output vector's contained type will be the same as that in a_. </para>
	/// </summary>
	/// <typeparam name="out_value_type">Type to be contained in the output vector.</typeparam>
	/// <typeparam name="AVector_">Type of a in the equation LERP(LERP(a, b, u), LERP(d, c, u), v).</typeparam>
	/// <typeparam name="B_">Type of b in the equation LERP(LERP(a, b, u), LERP(d, c, u), v).</typeparam>
	/// <typeparam name="C_">Type of c in the equation LERP(LERP(a, b, u), LERP(d, c, u), v).</typeparam>
	/// <typeparam name="DVector_">Type of d in the equation LERP(LERP(a, b, u), LERP(d, c, u), v).</typeparam>
	/// <typeparam name="U_">Type of u in the equation LERP(LERP(a, b, u), LERP(d, c, u), v).</typeparam>
	/// <typeparam name="V_">Type of v in the equation LERP(LERP(a, b, u), LERP(d, c, u), v).</typeparam>
	/// <param name="a_">EmuMath vector representing a in the equation LERP(LERP(a, b, u), LERP(d, c, u), v).</param>
	/// <param name="b_">EmuMath vector or scalar representing b in the equation LERP(LERP(a, b, u), LERP(d, c, u), v).</param>
	/// <param name="c_">EmuMath vector or scalar representing c in the equation LERP(LERP(a, b, u), LERP(d, c, u), v).</param>
	/// <param name="d_">EmuMath vector representing d in the equation LERP(LERP(a, b, u), LERP(d, c, u), v).</param>
	/// <param name="u_">EmuMath vector or scalar representing u in the equation LERP(LERP(a, b, u), LERP(d, c, u), v).</param>
	/// <param name="v_">EmuMath vector or scalar representing v in the equation LERP(LERP(a, b, u), LERP(d, c, u), v).</param>
	/// <returns>Vector containing the result of bilinear interpolation with the provided arguments.</returns>
	template<std::size_t OutSize_, typename out_value_type, class AVector_, class B_, class C_, class DVector_, class U_, class V_>
	[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, out_value_type> VectorBlerp
	(
		const AVector_& a_,
		const B_& b_,
		const C_& c_,
		const DVector_& d_,
		const U_& u_,
		const V_& v_
	)
	{
		if constexpr(EmuMath::TMP::is_emu_vector_v<AVector_>)
		{
			if constexpr (EmuMath::TMP::is_emu_vector_v<DVector_>)
			{
				return VectorLerp<OutSize_, out_value_type, EmuMath::Vector<OutSize_, out_value_type>, EmuMath::Vector<OutSize_, out_value_type>, V_>
				(
					VectorLerp<OutSize_, out_value_type, AVector_, B_, U_>(a_, b_, u_),
					VectorLerp<OutSize_, out_value_type, DVector_, C_, U_>(d_, c_, u_),
					v_
				);
			}
			else
			{
				static_assert(false, "Attempted to perform bilinear interpolation with vectors, but provided a non-EmuMath-vector argument for D_.");
			}
		}
		else
		{
			static_assert(false, "Attempted to perform bilinear interpolation with vectors, but provided a non-EmuMath-vector argument for A_.");
		}
	}
	template<typename out_value_type, class AVector_, class B_, class C_, class DVector_, class U_, class V_>
	[[nodiscard]] constexpr inline EmuMath::Vector<AVector_::size, out_value_type> VectorBlerp
	(
		const AVector_& a_,
		const B_& b_,
		const C_& c_,
		const DVector_& d_,
		const U_& u_,
		const V_& v_
	)
	{
		return VectorBlerp<AVector_::size, out_value_type, AVector_, B_, C_, DVector_, U_, V_>(a_, b_, c_, d_, u_, v_);
	}
	template<std::size_t OutSize_, class AVector_, class B_, class C_, class DVector_, class U_, class V_>
	[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, typename AVector_::value_type> VectorBlerp
	(
		const AVector_& a_,
		const B_& b_,
		const C_& c_,
		const DVector_& d_,
		const U_& u_,
		const V_& v_
	)
	{
		return VectorBlerp<OutSize_, typename AVector_::value_type, AVector_, B_, C_, DVector_, U_, V_>(a_, b_, c_, d_, u_, v_);
	}
	template<class AVector_, class B_, class C_, class DVector_, class U_, class V_>
	[[nodiscard]] constexpr inline EmuMath::Vector<AVector_::size, typename AVector_::value_type> VectorBlerp
	(
		const AVector_& a_,
		const B_& b_,
		const C_& c_,
		const DVector_& d_,
		const U_& u_,
		const V_& v_
	)
	{
		return VectorBlerp<AVector_::size, typename AVector_::value_type, AVector_, B_, C_, DVector_, U_, V_>(a_, b_, c_, d_, u_, v_);
	}

	/// <summary>
	/// <para> Calculates the reciprocal of each element in the passed vector and returns the result as a floating-point vector. </para>
	/// <para>
	///		OutSize_ is an optional parameter which may be used to get the reciprocal of less or more elements than stored in the vector. 
	///		Indices exceeding the passed vector's storage will be set to infinity.
	/// </para>
	/// <para> The provided out_floating_point_value_type is optional and defaults to float, and must be a floating-point type for this function to be used. </para>
	/// </summary>
	/// <typeparam name="out_floating_point_value_type">Floating-point type to be contained within the output vector.</typeparam>
	/// <typeparam name="Vector_">Vector type to calculate the reciprocal of.</typeparam>
	/// <param name="vector_">EmuMath vector to calculate the reciprocal of.</param>
	/// <returns>Vector of floating-points containing reciprocals of respective elements in the passed vector, or infinity in indices exceeding those of said vector.</returns>
	template<std::size_t OutSize_, typename out_floating_point_value_type = float, class Vector_>
	[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, out_floating_point_value_type> VectorReciprocal(const Vector_& vector_)
	{
		if constexpr (std::is_floating_point_v<std::remove_cv_t<std::remove_reference_t<out_floating_point_value_type>>>)
		{
			if constexpr (EmuMath::TMP::is_emu_vector_v<Vector_>)
			{
				return _underlying_vector_funcs::_vector_reciprocal<EmuMath::Vector<OutSize_, out_floating_point_value_type>, Vector_>(vector_);
			}
			else
			{
				static_assert(false, "Attempted to retrieve the reciprocal of a vector, but provided a non-EmuMath-vector argument.");
			}
		}
		else
		{
			static_assert(false, "Attempted to retrieve the reciprocal of a vector, but provided a non-floating-point output value_type. This behaviour is blocked.");
		}
	}
	template<typename out_floating_point_value_type = float, class Vector_>
	[[nodiscard]] constexpr inline EmuMath::Vector<Vector_::size, out_floating_point_value_type> VectorReciprocal(const Vector_& vector_)
	{
		return VectorReciprocal<Vector_::size, out_floating_point_value_type, Vector_>(vector_);
	}

	template<std::size_t OutSize_, typename out_value_type, class Vector_, class Min_>
	[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, out_value_type> VectorClampMin(const Vector_& vector_, const Min_& min_)
	{
		if constexpr (EmuMath::TMP::is_emu_vector_v<Vector_>)
		{
			return _underlying_vector_funcs::_vector_clamp_min<EmuMath::Vector<OutSize_, out_value_type>, Vector_, Min_>(vector_, min_);
		}
		else
		{
			static_assert(false, "Attempted to clamp the minimum values of a vector, but provided a non-EmuMath-vector to clamp.");
		}
	}
	template<typename out_value_type, class Vector_, class Min_>
	[[nodiscard]] constexpr inline EmuMath::Vector<Vector_::size, out_value_type> VectorClampMin(const Vector_& vector_, const Min_& min_)
	{
		return VectorClampMin<Vector_::size, out_value_type, Vector_, Min_>(vector_, min_);
	}
	template<std::size_t OutSize_, class Vector_, class Min_>
	[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, typename Vector_::value_type> VectorClampMin(const Vector_& vector_, const Min_& min_)
	{
		return VectorClampMin<OutSize_, typename Vector_::value_type, Vector_, Min_>(vector_, min_);
	}
	template<class Vector_, class Min_>
	[[nodiscard]] constexpr inline EmuMath::Vector<Vector_::size, typename Vector_::value_type> VectorClampMin(const Vector_& vector_, const Min_& min_)
	{
		return VectorClampMin<Vector_::size, typename Vector_::value_type, Vector_, Min_>(vector_, min_);
	}

	template<std::size_t OutSize_, typename out_value_type, class Vector_, class Max_>
	[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, out_value_type> VectorClampMax(const Vector_& vector_, const Max_& max_)
	{
		if constexpr (EmuMath::TMP::is_emu_vector_v<Vector_>)
		{
			return _underlying_vector_funcs::_vector_clamp_max<EmuMath::Vector<OutSize_, out_value_type>, Vector_, Max_>(vector_, max_);
		}
		else
		{
			static_assert(false, "Attempted to clamp the maximum values of a vector, but provided a non-EmuMath-vector to clamp.");
		}
	}
	template<typename out_value_type, class Vector_, class Max_>
	[[nodiscard]] constexpr inline EmuMath::Vector<Vector_::size, out_value_type> VectorClampMax(const Vector_& vector_, const Max_& max_)
	{
		return VectorClampMax<Vector_::size, out_value_type, Vector_, Max_>(vector_, max_);
	}
	template<std::size_t OutSize_, class Vector_, class Max_>
	[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, typename Vector_::value_type> VectorClampMax(const Vector_& vector_, const Max_& max_)
	{
		return VectorClampMax<OutSize_, typename Vector_::value_type, Vector_, Max_>(vector_, max_);
	}
	template<class Vector_, class Max_>
	[[nodiscard]] constexpr inline EmuMath::Vector<Vector_::size, typename Vector_::value_type> VectorClampMax(const Vector_& vector_, const Max_& max_)
	{
		return VectorClampMax<Vector_::size, typename Vector_::value_type, Vector_, Max_>(vector_, max_);
	}

	template<std::size_t OutSize_, typename out_value_type, class Vector_, class Min_, class Max_>
	[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, out_value_type> VectorClamp(const Vector_& vector_, const Min_& min_, const Max_& max_)
	{
		if constexpr (EmuMath::TMP::is_emu_vector_v<Vector_>)
		{
			return _underlying_vector_funcs::_vector_clamp<EmuMath::Vector<OutSize_, out_value_type>, Vector_, Min_, Max_>(vector_, min_, max_);
		}
		else
		{
			static_assert(false, "Attempted to clamp the values of a vector, but provided a non-EmuMath-vector type to clamp.");
		}
	}
	template<typename out_value_type, class Vector_, class Min_, class Max_>
	[[nodiscard]] constexpr inline EmuMath::Vector<Vector_::size, out_value_type> VectorClamp(const Vector_& vector_, const Min_& min_, const Max_& max_)
	{
		return VectorClamp<Vector_::size, out_value_type, Vector_, Min_, Max_>(vector_, min_, max_);
	}
	template<std::size_t OutSize_, class Vector_, class Min_, class Max_>
	[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, typename Vector_::value_type> VectorClamp(const Vector_& vector_, const Min_& min_, const Max_& max_)
	{
		return VectorClamp<OutSize_, typename Vector_::value_type, Vector_, Min_, Max_>(vector_, min_, max_);
	}
	template<class Vector_, class Min_, class Max_>
	[[nodiscard]] constexpr inline EmuMath::Vector<Vector_::size, typename Vector_::value_type> VectorClamp(const Vector_& vector_, const Min_& min_, const Max_& max_)
	{
		return VectorClamp<Vector_::size, typename Vector_::value_type, Vector_, Min_, Max_>(vector_, min_, max_);
	}

	/// <summary> Mutates the elements of a vector with a provided function and outputs them via the returned vector. </summary>
	/// <typeparam name="out_value_type">Type to be contained within the output vector.</typeparam>
	/// <typeparam name="Vector_">Type of vector to mutate.</typeparam>
	/// <typeparam name="Func_">Type of invokable used to mutate the vector.</typeparam>
	/// <param name="vector_">Vector to mutate the elements of.</param>
	/// <param name="func_">
	///		Item invokable via the function operator() which can take a single argument of the passed vector's value_type, 
	///		and returns a value of out_value_type or which may be cast to out_value_type.
	/// </param>
	/// <returns>Vector containing the results of the mutation of the passed vector_ via the passed func_.</returns>
	template<std::size_t OutSize_, typename out_value_type, class Vector_, class Func_>
	[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, out_value_type> VectorMutate(const Vector_& vector_, Func_ func_)
	{
		if constexpr (EmuMath::TMP::is_emu_vector_v<Vector_>)
		{
			return _underlying_vector_funcs::_vector_single_operand_func<EmuMath::Vector<OutSize_, out_value_type>, Vector_, Func_>(vector_, func_);
		}
		else
		{
			static_assert(false, "Attempted to perform a round operation on a vector, but provided a non-EmuMath-vector type.");
		}
	}
	template<std::size_t OutSize_, typename out_value_type, class Vector_, class Func_>
	[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, out_value_type> VectorMutate(const Vector_& vector_)
	{
		return VectorMutate<OutSize_, out_value_type, Vector_, Func_>(vector_, Func_());
	}
	template<typename out_value_type, class Vector_, class Func_>
	[[nodiscard]] constexpr inline EmuMath::Vector<Vector_::size, out_value_type> VectorMutate(const Vector_& vector_, Func_ func_)
	{
		return VectorMutate<Vector_::size, out_value_type, Vector_, Func_&>(vector_, func_);
	}
	template<std::size_t OutSize_, class Vector_, class Func_>
	[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, typename Vector_::value_type> VectorMutate(const Vector_& vector_, Func_ func_)
	{
		return VectorMutate<OutSize_, typename Vector_::value_type, Vector_, Func_&>(vector_, func_);
	}
	template<class Vector_, class Func_>
	[[nodiscard]] constexpr inline EmuMath::Vector<Vector_::size, typename Vector_::value_type> VectorMutate(const Vector_& vector_, Func_ func_)
	{
		return VectorMutate<Vector_::size, typename Vector_::value_type, Vector_, Func_&>(vector_, func_);
	}
	template<typename out_value_type, class Vector_, class Func_>
	[[nodiscard]] constexpr inline EmuMath::Vector<Vector_::size, out_value_type> VectorMutate(const Vector_& vector_)
	{
		return VectorMutate<Vector_::size, out_value_type, Vector_, Func_>(vector_, Func_());
	}
	template<std::size_t OutSize_, class Vector_, class Func_>
	[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, typename Vector_::value_type> VectorMutate(const Vector_& vector_)
	{
		return VectorMutate<OutSize_, typename Vector_::value_type, Vector_, Func_>(vector_, Func_());
	}
	template<class Vector_, class Func_>
	[[nodiscard]] constexpr inline EmuMath::Vector<Vector_::size, typename Vector_::value_type> VectorMutate(const Vector_& vector_)
	{
		return VectorMutate<Vector_::size, typename Vector_::value_type, Vector_, Func_>(vector_, Func_());
	}

	/// <summary>
	///		Floors all elements within the passed vector (i.e. rounds them toward negative infinity) and stores the results in respective elements of the output vector.
	/// </summary>
	/// <typeparam name="out_value_type">Type to be contained within the output vector.</typeparam>
	/// <typeparam name="Vector_">Type of vector to round the elements of.</typeparam>
	/// <param name="vector_">EmuMath vector to round the elements of.</param>
	/// <returns>EmuMath vector containing the results of rounding respective elements in the passed vector_.</returns>
	template<std::size_t OutSize_, typename out_value_type, class Vector_>
	[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, out_value_type> VectorFloor(const Vector_& vector_)
	{
		if constexpr (EmuMath::TMP::is_emu_vector_v<Vector_>)
		{
			return _underlying_vector_funcs::_vector_single_operand_func<EmuMath::Vector<OutSize_, out_value_type>, Vector_, EmuCore::do_floor<typename Vector_::value_type>>
			(
				vector_
			);
		}
		else
		{
			static_assert(false, "Attempted to floor a vector, but provided a non-EmuMath-vector argument type.");
		}
	}
	template<typename out_value_type, class Vector_>
	[[nodiscard]] constexpr inline EmuMath::Vector<Vector_::size, out_value_type> VectorFloor(const Vector_& vector_)
	{
		return VectorFloor<Vector_::size, out_value_type, Vector_>(vector_);
	}
	template<std::size_t OutSize_, class Vector_>
	[[nodiscard]] constexpr inline EmuMath::Vector<Vector_::size, typename Vector_::value_type> VectorFloor(const Vector_& vector_)
	{
		return VectorFloor<OutSize_, typename Vector_::value_type, Vector_>(vector_);
	}
	template<class Vector_>
	[[nodiscard]] constexpr inline EmuMath::Vector<Vector_::size, typename Vector_::value_type> VectorFloor(const Vector_& vector_)
	{
		return VectorFloor<Vector_::size, typename Vector_::value_type, Vector_>(vector_);
	}

	/// <summary>
	///		Ceils all elements within the passed vector (i.e. rounds them toward positive infinity) and stores the results in respective elements of the output vector.
	/// </summary>
	/// <typeparam name="out_value_type">Type to be contained within the output vector.</typeparam>
	/// <typeparam name="Vector_">Type of vector to round the elements of.</typeparam>
	/// <param name="vector_">EmuMath vector to round the elements of.</param>
	/// <returns>EmuMath vector containing the results of rounding respective elements in the passed vector_.</returns>
	template<std::size_t OutSize_, typename out_value_type, class Vector_>
	[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, out_value_type> VectorCeil(const Vector_& vector_)
	{
		if constexpr (EmuMath::TMP::is_emu_vector_v<Vector_>)
		{
			return _underlying_vector_funcs::_vector_single_operand_func<EmuMath::Vector<OutSize_, out_value_type>, Vector_, EmuCore::do_ceil<typename Vector_::value_type>>
			(
				vector_
			);
		}
		else
		{
			static_assert(false, "Attempted to ceil a vector, but provided a non-EmuMath-vector argument type.");
		}
	}
	template<typename out_value_type, class Vector_>
	[[nodiscard]] constexpr inline EmuMath::Vector<Vector_::size, out_value_type> VectorCeil(const Vector_& vector_)
	{
		return VectorCeil<Vector_::size, out_value_type, Vector_>(vector_);
	}
	template<std::size_t OutSize_, class Vector_>
	[[nodiscard]] constexpr inline EmuMath::Vector<Vector_::size, typename Vector_::value_type> VectorCeil(const Vector_& vector_)
	{
		return VectorCeil<OutSize_, typename Vector_::value_type, Vector_>(vector_);
	}
	template<class Vector_>
	[[nodiscard]] constexpr inline EmuMath::Vector<Vector_::size, typename Vector_::value_type> VectorCeil(const Vector_& vector_)
	{
		return VectorCeil<Vector_::size, typename Vector_::value_type, Vector_>(vector_);
	}

	/// <summary>
	///		Truncates all elements within the passed vector (i.e. rounds them toward 0) and stores the results in respective elements of the output vector.
	/// </summary>
	/// <typeparam name="out_value_type">Type to be contained within the output vector.</typeparam>
	/// <typeparam name="Vector_">Type of vector to round the elements of.</typeparam>
	/// <param name="vector_">EmuMath vector to round the elements of.</param>
	/// <returns>EmuMath vector containing the results of rounding respective elements in the passed vector_.</returns>
	template<std::size_t OutSize_, typename out_value_type, class Vector_>
	[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, out_value_type> VectorTrunc(const Vector_& vector_)
	{
		if constexpr (EmuMath::TMP::is_emu_vector_v<Vector_>)
		{
			return _underlying_vector_funcs::_vector_single_operand_func<EmuMath::Vector<OutSize_, out_value_type>, Vector_, EmuCore::do_trunc<typename Vector_::value_type>>
			(
				vector_
			);
		}
		else
		{
			static_assert(false, "Attempted to trunc a vector, but provided a non-EmuMath-vector argument type.");
		}
	}
	template<typename out_value_type, class Vector_>
	[[nodiscard]] constexpr inline EmuMath::Vector<Vector_::size, out_value_type> VectorTrunc(const Vector_& vector_)
	{
		return VectorTrunc<Vector_::size, out_value_type, Vector_>(vector_);
	}
	template<std::size_t OutSize_, class Vector_>
	[[nodiscard]] constexpr inline EmuMath::Vector<Vector_::size, typename Vector_::value_type> VectorTrunc(const Vector_& vector_)
	{
		return VectorTrunc<OutSize_, typename Vector_::value_type, Vector_>(vector_);
	}
	template<class Vector_>
	[[nodiscard]] constexpr inline EmuMath::Vector<Vector_::size, typename Vector_::value_type> VectorTrunc(const Vector_& vector_)
	{
		return VectorTrunc<Vector_::size, typename Vector_::value_type, Vector_>(vector_);
	}

	/// <summary>
	/// <para> Performs a square root calculation of elements within the passed vector and returns the resulting vector. </para>
	/// <para> This calculation may make some sacrifices to be executable at compile time. If it is being called at runtime, it is recommended to use VectorSqrt instead. </para>
	/// <para> This function makes use of the EmuMath::do_sqrt_constexpr functor. The specialisation for the passed vector's value_type will be used, if one exists. </para>
	/// </summary>
	/// <typeparam name="out_value_type">Type to be stored in the output vector.</typeparam>
	/// <typeparam name="Vector_">Type of vector to calculate the square root of the elements of.</typeparam>
	/// <param name="vector_">EmuMath vector to calculate the square root of elements of.</param>
	/// <returns>EmuMath vector containing the results of the square root calculation for each respective element within the passed vector.</returns>
	template<std::size_t OutSize_, typename out_value_type, class Vector_>
	[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, out_value_type> VectorSqrtConstexpr(const Vector_& vector_)
	{
		if constexpr (EmuMath::TMP::is_emu_vector_v<Vector_>)
		{
			return _underlying_vector_funcs::_vector_single_operand_func
			<
				EmuMath::Vector<OutSize_, out_value_type>,
				Vector_,
				EmuCore::do_sqrt_constexpr<typename Vector_::value_type>
			>(vector_);
		}
		else
		{
			static_assert(false, "Attempted to calculate the square root of all elements within a vector, but provided a non-EmuMath-vector argument type.");
		}
	}
	template<typename out_value_type, class Vector_>
	[[nodiscard]] constexpr inline EmuMath::Vector<Vector_::size, out_value_type> VectorSqrtConstexpr(const Vector_& vector_)
	{
		return VectorSqrtConstexpr<Vector_::size, out_value_type, Vector_>(vector_);
	}
	template<std::size_t OutSize_, class Vector_>
	[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, typename Vector_::value_type> VectorSqrtConstexpr(const Vector_& vector_)
	{
		return VectorSqrtConstexpr<OutSize_, typename Vector_::value_type, Vector_>(vector_);
	}
	template<class Vector_>
	[[nodiscard]] constexpr inline EmuMath::Vector<Vector_::size, typename Vector_::value_type> VectorSqrtConstexpr(const Vector_& vector_)
	{
		return VectorSqrtConstexpr<Vector_::size, typename Vector_::value_type, Vector_>(vector_);
	}

	/// <summary>
	/// <para> Performs a square root calculation of elements within the passed vector and returns the resulting vector. </para>
	/// <para> This function makes use of the EmuMath::do_sqrt functor. The specialisation for the passed vector's value_type will be used, if one exists. </para>
	/// </summary>
	/// <typeparam name="out_value_type">Type to be stored in the output vector.</typeparam>
	/// <typeparam name="Vector_">Type of vector to calculate the square root of the elements of.</typeparam>
	/// <param name="vector_">EmuMath vector to calculate the square root of elements of.</param>
	/// <returns>EmuMath vector containing the results of the square root calculation for each respective element within the passed vector.</returns>
	template<std::size_t OutSize_, typename out_value_type, class Vector_>
	[[nodiscard]] inline EmuMath::Vector<OutSize_, out_value_type> VectorSqrt(const Vector_& vector_)
	{
		if constexpr (EmuMath::TMP::is_emu_vector_v<Vector_>)
		{
			return _underlying_vector_funcs::_vector_single_operand_func
			<
				EmuMath::Vector<OutSize_, out_value_type>,
				Vector_,
				EmuCore::do_sqrt<typename Vector_::value_type>
			>(vector_);
		}
		else
		{
			static_assert(false, "Attempted to calculate the square root of all elements within a vector, but provided a non-EmuMath-vector argument type.");
		}
	}
	template<typename out_value_type, class Vector_>
	[[nodiscard]] inline EmuMath::Vector<Vector_::size, out_value_type> VectorSqrt(const Vector_& vector_)
	{
		return VectorSqrt<Vector_::size, out_value_type, Vector_>(vector_);
	}
	template<std::size_t OutSize_, class Vector_>
	[[nodiscard]] inline EmuMath::Vector<OutSize_, typename Vector_::value_type> VectorSqrt(const Vector_& vector_)
	{
		return VectorSqrt<OutSize_, typename Vector_::value_type, Vector_>(vector_);
	}
	template<class Vector_>
	[[nodiscard]] inline EmuMath::Vector<Vector_::size, typename Vector_::value_type> VectorSqrt(const Vector_& vector_)
	{
		return VectorSqrt<Vector_::size, typename Vector_::value_type, Vector_>(vector_);
	}

	/// <summary>
	/// <para> Creates a copy of the passed vector with its elements normalised. </para>
	/// <para>
	///		This function may make some sacrifices to be evaluable at compile time. 
	///		If it is being called at compile time, it is recommended to use VectorNormalise or VectorNormaliseQrsqrt instead.
	/// </para>
	/// </summary>
	/// <typeparam name="MagFloatingPointType_">Type of floating-point to calculate the magnitude as and use for arithmetic in normalisation. Defaults to float.</typeparam>
	/// <typeparam name="Vector_">Type of vector to return a normalised copy of.</typeparam>
	/// <param name="vector_">EmuMath vector to calculate the normalised form of.</param>
	/// <returns>Copy of the passed EmuMath vector with its elements normalised.</returns>
	template<typename MagFloatingPointType_ = float, class Vector_>
	[[nodiscard]] constexpr inline typename Vector_::copy_type VectorNormaliseConstexpr(const Vector_& vector_)
	{
		if constexpr (EmuMath::TMP::is_emu_vector_v<Vector_>)
		{
			if constexpr (std::is_floating_point_v<MagFloatingPointType_>)
			{
				return VectorMultiply<Vector_, MagFloatingPointType_>(vector_, VectorMagnitudeReciprocalConstexpr<MagFloatingPointType_>(vector_));
			}
			else
			{
				static_assert(false, "Attempted to use a non-floating-point type for calculating the reciprocal to a vector's magnitude when normalising it.");
			}
		}
		else
		{
			static_assert(false, "Attempted to normalise a vector, but provided a non-EmuMath-vector argument.");
		}
	}

	/// <summary>
	/// <para> Creates a copy of the passed vector with its elements normalised. </para>
	/// </summary>
	/// <typeparam name="MagFloatingPointType_">Type of floating-point to calculate the magnitude as and use for arithmetic in normalisation. Defaults to float.</typeparam>
	/// <typeparam name="Vector_">Type of vector to return a normalised copy of.</typeparam>
	/// <param name="vector_">EmuMath vector to calculate the normalised form of.</param>
	/// <returns>Copy of the passed EmuMath vector with its elements normalised.</returns>
	template<typename MagFloatingPointType_ = float, class Vector_>
	[[nodiscard]] inline typename Vector_::copy_type VectorNormalise(const Vector_& vector_)
	{
		if constexpr (EmuMath::TMP::is_emu_vector_v<Vector_>)
		{
			if constexpr (std::is_floating_point_v<MagFloatingPointType_>)
			{
				return VectorMultiply<Vector_, MagFloatingPointType_>(vector_, VectorMagnitudeReciprocal<MagFloatingPointType_>(vector_));
			}
			else
			{
				static_assert(false, "Attempted to use a non-floating-point type for calculating the reciprocal to a vector's magnitude when normalising it.");
			}
		}
		else
		{
			static_assert(false, "Attempted to normalise a vector, but provided a non-EmuMath-vector argument.");
		}
	}

	/// <summary>
	/// <para> Creates a copy of the passed vector with its elements normalised. </para>
	/// <para> Uses Q_rsqrt to find the magnitude reciprocal to multiply all elements by. </para>
	///	<para> NumNewtonIterations_ can be increased to improve accuracy. </para>
	///	<para> MagicConstant_ may be changed to modify bitwise operations, but is recommended to be left to the default (0x5F3759DF) unless you know what you are doing. </para>
	/// </summary>
	/// <typeparam name="MagFloatingPointType_">Type of floating-point to calculate the magnitude as and use for arithmetic in normalisation. Defaults to float.</typeparam>
	/// <typeparam name="Vector_">Type of vector to return a normalised copy of.</typeparam>
	/// <param name="vector_">EmuMath vector to calculate the normalised form of.</param>
	/// <returns>Copy of the passed EmuMath vector with its elements normalised via the result of using Q_rsqrt to find the magnitude's reciprocal.</returns>
	template<typename MagFloatingPointType_ = float, std::size_t NumNewtonIterations_ = 1, std::int32_t MagicConstant_ = 0x5F3759DF, class Vector_>
	[[nodiscard]] inline typename Vector_::copy_type VectorNormaliseQrsqrt(const Vector_& vector_)
	{
		if constexpr (EmuMath::TMP::is_emu_vector_v<Vector_>)
		{
			if constexpr (std::is_floating_point_v<MagFloatingPointType_>)
			{
				return VectorMultiply<Vector_, MagFloatingPointType_>
				(
					vector_,
					VectorMagnitudeReciprocalQrsqrt<MagFloatingPointType_, NumNewtonIterations_, MagicConstant_, Vector_>(vector_)
				);
			}
			else
			{
				static_assert(false, "Attempted to use a non-floating-point type for calculating the reciprocal to a vector's magnitude when normalising it.");
			}
		}
		else
		{
			static_assert(false, "Attempted to normalise a vector, but provided a non-EmuMath-vector argument.");
		}
	}

	/// <summary>
	/// <para> Calculates the cosine of the angle between the two provided vectors. </para>
	/// <para> It is recommended, but not enforced, that you output the cosine as a floating-point type. It will default to float. </para>
	/// <para> This function may make sacrifices to be evaluable at compile time. If it is being used at runtime, it is recommended to use VectorAngleCosine. </para>
	/// </summary>
	/// <typeparam name="OutCosine_">Type to output the cosine as. Defaults to float.</typeparam>
	/// <typeparam name="LhsVector_">Type of vector appearing on the left-hand side of arguments.</typeparam>
	/// <typeparam name="RhsVector_">Type of vector appearing on the right-hand side of arguments.</typeparam>
	/// <param name="lhs_">First EmuMath vector in the calculation.</param>
	/// <param name="rhs_">Second EmuMath vector in the calculation.</param>
	/// <returns>Cosine of the angle between vectors lhs_ and rhs_, represented as the provided OutCosine_ type.</returns>
	template<typename OutCosine_ = float, class LhsVector_, class RhsVector_>
	[[nodiscard]] constexpr inline OutCosine_ VectorAngleCosineConstexpr(const LhsVector_& lhs_, const RhsVector_& rhs_)
	{
		if constexpr (EmuMath::TMP::is_emu_vector_v<LhsVector_>)
		{
			if constexpr (EmuMath::TMP::is_emu_vector_v<RhsVector_>)
			{
				return
				(
					VectorDotProduct<OutCosine_>(lhs_, rhs_) / 
					(
						VectorMagnitudeConstexpr<OutCosine_, LhsVector_>(lhs_) *
						VectorMagnitudeConstexpr<OutCosine_, RhsVector_>(rhs_)
					)
				);
			}
			else
			{
				static_assert(false, "Attempted to find the cosine of the angle between two vectors, but provided a non-EmuMath-vector right-hand argument.");
			}
		}
		else
		{
			static_assert(false, "Attempted to find the cosine of the angle between two vectors, but provided a non-EmuMath-vector left-hand argument.");
		}
	}
	/// <summary>
	/// <para> Calculates the cosine of the angle between the two provided vectors. </para>
	/// <para> It is recommended, but not enforced, that you output the cosine as a floating-point type. It will default to float. </para>
	/// </summary>
	/// <typeparam name="OutCosine_">Type to output the cosine as. Defaults to float.</typeparam>
	/// <typeparam name="LhsVector_">Type of vector appearing on the left-hand side of arguments.</typeparam>
	/// <typeparam name="RhsVector_">Type of vector appearing on the right-hand side of arguments.</typeparam>
	/// <param name="lhs_">First EmuMath vector in the calculation.</param>
	/// <param name="rhs_">Second EmuMath vector in the calculation.</param>
	/// <returns>Cosine of the angle between vectors lhs_ and rhs_, represented as the provided OutCosine_ type.</returns>
	template<typename OutCosine_ = float, class LhsVector_, class RhsVector_>
	[[nodiscard]] inline OutCosine_ VectorAngleCosine(const LhsVector_& lhs_, const RhsVector_& rhs_)
	{
		if constexpr (EmuMath::TMP::is_emu_vector_v<LhsVector_>)
		{
			if constexpr (EmuMath::TMP::is_emu_vector_v<RhsVector_>)
			{
				return 
				(
					VectorDotProduct<OutCosine_>(lhs_, rhs_) / 
					(
						VectorMagnitude<OutCosine_, LhsVector_>(lhs_) *
						VectorMagnitude<OutCosine_, RhsVector_>(rhs_)
					)
				);
			}
			else
			{
				static_assert(false, "Attempted to find the cosine of the angle between two vectors, but provided a non-EmuMath-vector right-hand argument.");
			}
		}
		else
		{
			static_assert(false, "Attempted to find the cosine of the angle between two vectors, but provided a non-EmuMath-vector left-hand argument.");
		}
	}

	/// <summary>
	/// <para> Calculates the angle between the passed vectors and outputs it in either radians or degrees. </para>
	/// <para> If Rads_ is true, output will be in radians, otherwise it will be in degrees. By default, output will be in radians. </para>
	/// </summary>
	/// <typeparam name="OutAngle_">Type to output the angle as.</typeparam>
	/// <typeparam name="VectorA_">Type of vector appearing on the left-hand side of arguments.</typeparam>
	/// <typeparam name="VectorB_">Type of vector appearing on the right-hand side of arguments.</typeparam>
	/// <param name="a_">First EmuMath vector in the calculation.</param>
	/// <param name="b_">Second EmuMath vector in the calculation.</param>
	/// <returns>The angle between the two vectors represented as the provided OutAngle_ type. Units will be radians if Rads_ is true, otherwise they will be degrees.</returns>
	template<bool Rads_ = true, typename OutAngle_ = float, class VectorA_, class VectorB_>
	[[nodiscard]] inline OutAngle_ VectorAngle(const VectorA_& a_, const VectorB_& b_)
	{
		using floating_point = EmuCore::TMPHelpers::first_floating_point_t<OutAngle_, float>;
		if constexpr (Rads_)
		{
			return static_cast<OutAngle_>(EmuCore::do_acos<floating_point>()(VectorAngleCosine<floating_point>(a_, b_)));
		}
		else
		{
			return static_cast<OutAngle_>(EmuCore::Pi::RadsToDegs(EmuCore::do_acos<floating_point>()(VectorAngleCosine<floating_point>(a_, b_))));
		}
	}

	/// <summary>
	/// <para> Returns a vector containing the distance that may be added to the vector from_ to reach the values of the vector to_. </para>
	/// <para> This is effectively syntactic sugar for VectorSubtract(to_, from_). </para>
	/// </summary>
	/// <typeparam name="out_contained_type">Type to be contained in the output vector.</typeparam>
	/// <typeparam name="FromVector_">Type of vector to calculate the distance from.</typeparam>
	/// <typeparam name="ToVector_">Type of vector to calculate the distance to.</typeparam>
	/// <param name="from_">EmuMath vector to calculate the distance from.</param>
	/// <param name="to_">EmuMath vector to calculate the distance to.</param>
	/// <returns>Vector that may be added to from_ to reach the respective elements of to_.</returns>
	template<std::size_t OutSize_, typename out_contained_type, class FromVector_, class ToVector_>
	[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, out_contained_type> VectorDistance(const FromVector_& from_, const ToVector_& to_)
	{
		if constexpr (EmuMath::TMP::is_emu_vector_v<FromVector_>)
		{
			if constexpr (EmuMath::TMP::is_emu_vector_v<FromVector_>)
			{
				return VectorSubtract<OutSize_, out_contained_type, ToVector_, FromVector_>(to_, from_);
			}
			else
			{
				static_assert(false, "Attempted to find the distance between two vectors, but provided a non-EmuMath-vector argument for to_.");
			}
		}
		else
		{
			static_assert(false, "Attempted to find the distance between two vectors, but provided a non-EmuMath-vector argument for from_.");
		}
	}
	template<typename out_contained_type, class FromVector_, class ToVector_>
	[[nodiscard]] constexpr inline EmuMath::Vector<FromVector_::size, out_contained_type> VectorDistance(const FromVector_& from_, const ToVector_& to_)
	{
		return VectorDistance<FromVector_::size, out_contained_type, FromVector_, ToVector_>(from_, to_);
	}
	template<std::size_t OutSize_, class FromVector_, class ToVector_>
	[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, typename FromVector_::value_type> VectorDistance(const FromVector_& from_, const ToVector_& to_)
	{
		return VectorDistance<OutSize_, typename FromVector_::value_type, FromVector_, ToVector_>(from_, to_);
	}
	template<class FromVector_, class ToVector_>
	[[nodiscard]] constexpr inline EmuMath::Vector<FromVector_::size, typename FromVector_::value_type> VectorDistance(const FromVector_& from_, const ToVector_& to_)
	{
		return VectorDistance<FromVector_::size, typename FromVector_::value_type, FromVector_, ToVector_>(from_, to_);
	}
#pragma endregion

#pragma region COMPARISONS
	/// <summary>
	/// <para> Returns a boolean indicating if any elements in the passed lhs_ vector are equal to rhs_, depending on the type of rhs_. </para>
	/// <para> If rhs_ is an EmuMath vector, respective elements will be compared. Otherwise, all lhs_ elements will be compared to the same rhs_ value. </para>
	/// <para> By default, all indices are tested. To test only up to the end of the smallest vector, pass false as the argument for TestAllIndices_. </para>
	/// </summary>
	/// <typeparam name="LhsVector_">Type of EmuMath vector that appears on the left-hand side of comparisons.</typeparam>
	/// <typeparam name="Rhs_">Type of EmuMath vector or scalar that appears on the right hand side of comparisons.</typeparam>
	/// <param name="lhs_">EmuMath vector that appears on the left-hand side of comparisons.</param>
	/// <param name="rhs_">EmuMath vector or scalar that appears on the right hand side of comparisons.</param>
	/// <returns>True if any executed comparisons returned true, otherwise false.</returns>
	template<bool TestAllIndices_ = true, class LhsVector_, class Rhs_>
	[[nodiscard]] constexpr inline bool VectorCmpAnyEqualTo(const LhsVector_& lhs_, const Rhs_& rhs_)
	{
		if constexpr (EmuMath::TMP::is_emu_vector_v<LhsVector_>)
		{
			return _underlying_vector_funcs::_vector_overall_comparison<TestAllIndices_, false, true, EmuCore::do_cmp_equal_to, LhsVector_, Rhs_>(lhs_, rhs_);
		}
		else
		{
			static_assert(false, "Attempted to compare the equality of any vector elements, but passed a non-EmuMath-vector left-hand operand.");
		}
	}

	/// <summary>
	/// <para> Returns a boolean indicating if any elements in the passed lhs_ vector are not equal to rhs_, depending on the type of rhs_. </para>
	/// <para> If rhs_ is an EmuMath vector, respective elements will be compared. Otherwise, all lhs_ elements will be compared to the same rhs_ value. </para>
	/// <para> By default, all indices are tested. To test only up to the end of the smallest vector, pass false as the argument for TestAllIndices_. </para>
	/// </summary>
	/// <typeparam name="LhsVector_">Type of EmuMath vector that appears on the left-hand side of comparisons.</typeparam>
	/// <typeparam name="Rhs_">Type of EmuMath vector or scalar that appears on the right hand side of comparisons.</typeparam>
	/// <param name="lhs_">EmuMath vector that appears on the left-hand side of comparisons.</param>
	/// <param name="rhs_">EmuMath vector or scalar that appears on the right hand side of comparisons.</param>
	/// <returns>True if any executed comparisons returned true, otherwise false.</returns>
	template<bool TestAllIndices_ = true, class LhsVector_, class Rhs_>
	[[nodiscard]] constexpr inline bool VectorCmpAnyNotEqualTo(const LhsVector_& lhs_, const Rhs_& rhs_)
	{
		if constexpr (EmuMath::TMP::is_emu_vector_v<LhsVector_>)
		{
			return _underlying_vector_funcs::_vector_overall_comparison<TestAllIndices_, false, true, EmuCore::do_cmp_not_equal_to, LhsVector_, Rhs_>(lhs_, rhs_);
		}
		else
		{
			static_assert(false, "Attempted to compare the inequality of any vector elements, but passed a non-EmuMath-vector left-hand operand.");
		}
	}

	/// <summary>
	/// <para> Returns a boolean indicating if any elements in the passed lhs_ vector are greater than rhs_, depending on the type of rhs_. </para>
	/// <para> If rhs_ is an EmuMath vector, respective elements will be compared. Otherwise, all lhs_ elements will be compared to the same rhs_ value. </para>
	/// <para> By default, all indices are tested. To test only up to the end of the smallest vector, pass false as the argument for TestAllIndices_. </para>
	/// </summary>
	/// <typeparam name="LhsVector_">Type of EmuMath vector that appears on the left-hand side of comparisons.</typeparam>
	/// <typeparam name="Rhs_">Type of EmuMath vector or scalar that appears on the right hand side of comparisons.</typeparam>
	/// <param name="lhs_">EmuMath vector that appears on the left-hand side of comparisons.</param>
	/// <param name="rhs_">EmuMath vector or scalar that appears on the right hand side of comparisons.</param>
	/// <returns>True if any executed comparisons returned true, otherwise false.</returns>
	template<bool TestAllIndices_ = true, class LhsVector_, class Rhs_>
	[[nodiscard]] constexpr inline bool VectorCmpAnyGreater(const LhsVector_& lhs_, const Rhs_& rhs_)
	{
		if constexpr (EmuMath::TMP::is_emu_vector_v<LhsVector_>)
		{
			return _underlying_vector_funcs::_vector_overall_comparison<TestAllIndices_, false, true, EmuCore::do_cmp_greater, LhsVector_, Rhs_>(lhs_, rhs_);
		}
		else
		{
			static_assert(false, "Attempted to compare the magnitude of any vector elements, but passed a non-EmuMath-vector left-hand operand.");
		}
	}

	/// <summary>
	/// <para> Returns a boolean indicating if any elements in the passed lhs_ vector are less than rhs_, depending on the type of rhs_. </para>
	/// <para> If rhs_ is an EmuMath vector, respective elements will be compared. Otherwise, all lhs_ elements will be compared to the same rhs_ value. </para>
	/// <para> By default, all indices are tested. To test only up to the end of the smallest vector, pass false as the argument for TestAllIndices_. </para>
	/// </summary>
	/// <typeparam name="LhsVector_">Type of EmuMath vector that appears on the left-hand side of comparisons.</typeparam>
	/// <typeparam name="Rhs_">Type of EmuMath vector or scalar that appears on the right hand side of comparisons.</typeparam>
	/// <param name="lhs_">EmuMath vector that appears on the left-hand side of comparisons.</param>
	/// <param name="rhs_">EmuMath vector or scalar that appears on the right hand side of comparisons.</param>
	/// <returns>True if any executed comparisons returned true, otherwise false.</returns>
	template<bool TestAllIndices_ = true, class LhsVector_, class Rhs_>
	[[nodiscard]] constexpr inline bool VectorCmpAnyLess(const LhsVector_& lhs_, const Rhs_& rhs_)
	{
		if constexpr (EmuMath::TMP::is_emu_vector_v<LhsVector_>)
		{
			return _underlying_vector_funcs::_vector_overall_comparison<TestAllIndices_, false, true, EmuCore::do_cmp_less, LhsVector_, Rhs_>(lhs_, rhs_);
		}
		else
		{
			static_assert(false, "Attempted to compare the magnitude of any vector elements, but passed a non-EmuMath-vector left-hand operand.");
		}
	}

	/// <summary>
	/// <para> Returns a boolean indicating if any elements in the passed lhs_ vector are greater than or equal to rhs_, depending on the type of rhs_. </para>
	/// <para> If rhs_ is an EmuMath vector, respective elements will be compared. Otherwise, all lhs_ elements will be compared to the same rhs_ value. </para>
	/// <para> By default, all indices are tested. To test only up to the end of the smallest vector, pass false as the argument for TestAllIndices_. </para>
	/// </summary>
	/// <typeparam name="LhsVector_">Type of EmuMath vector that appears on the left-hand side of comparisons.</typeparam>
	/// <typeparam name="Rhs_">Type of EmuMath vector or scalar that appears on the right hand side of comparisons.</typeparam>
	/// <param name="lhs_">EmuMath vector that appears on the left-hand side of comparisons.</param>
	/// <param name="rhs_">EmuMath vector or scalar that appears on the right hand side of comparisons.</param>
	/// <returns>True if any executed comparisons returned true, otherwise false.</returns>
	template<bool TestAllIndices_ = true, class LhsVector_, class Rhs_>
	[[nodiscard]] constexpr inline bool VectorCmpAnyGreaterEqual(const LhsVector_& lhs_, const Rhs_& rhs_)
	{
		if constexpr (EmuMath::TMP::is_emu_vector_v<LhsVector_>)
		{
			return _underlying_vector_funcs::_vector_overall_comparison<TestAllIndices_, false, true, EmuCore::do_cmp_greater_equal, LhsVector_, Rhs_>(lhs_, rhs_);
		}
		else
		{
			static_assert(false, "Attempted to compare the magnitude of any vector elements, but passed a non-EmuMath-vector left-hand operand.");
		}
	}

	/// <summary>
	/// <para> Returns a boolean indicating if any elements in the passed lhs_ vector are less than or equal to rhs_, depending on the type of rhs_. </para>
	/// <para> If rhs_ is an EmuMath vector, respective elements will be compared. Otherwise, all lhs_ elements will be compared to the same rhs_ value. </para>
	/// <para> By default, all indices are tested. To test only up to the end of the smallest vector, pass false as the argument for TestAllIndices_. </para>
	/// </summary>
	/// <typeparam name="LhsVector_">Type of EmuMath vector that appears on the left-hand side of comparisons.</typeparam>
	/// <typeparam name="Rhs_">Type of EmuMath vector or scalar that appears on the right hand side of comparisons.</typeparam>
	/// <param name="lhs_">EmuMath vector that appears on the left-hand side of comparisons.</param>
	/// <param name="rhs_">EmuMath vector or scalar that appears on the right hand side of comparisons.</param>
	/// <returns>True if any executed comparisons returned true, otherwise false.</returns>
	template<bool TestAllIndices_ = true, class LhsVector_, class Rhs_>
	[[nodiscard]] constexpr inline bool VectorCmpAnyLessEqual(const LhsVector_& lhs_, const Rhs_& rhs_)
	{
		if constexpr (EmuMath::TMP::is_emu_vector_v<LhsVector_>)
		{
			return _underlying_vector_funcs::_vector_overall_comparison<TestAllIndices_, false, true, EmuCore::do_cmp_less_equal, LhsVector_, Rhs_>(lhs_, rhs_);
		}
		else
		{
			static_assert(false, "Attempted to compare the magnitude of any vector elements, but passed a non-EmuMath-vector left-hand operand.");
		}
	}

	/// <summary>
	/// <para> Returns a boolean indicating if all elements in the passed lhs_ vector are equal to rhs_, depending on the type of rhs_. </para>
	/// <para> If rhs_ is an EmuMath vector, respective elements will be compared. Otherwise, all lhs_ elements will be compared to the same rhs_ value. </para>
	/// <para> By default, all indices are tested. To test only up to the end of the smallest vector, pass false as the argument for TestAllIndices_. </para>
	/// </summary>
	/// <typeparam name="LhsVector_">Type of EmuMath vector that appears on the left-hand side of comparisons.</typeparam>
	/// <typeparam name="Rhs_">Type of EmuMath vector or scalar that appears on the right hand side of comparisons.</typeparam>
	/// <param name="lhs_">EmuMath vector that appears on the left-hand side of comparisons.</param>
	/// <param name="rhs_">EmuMath vector or scalar that appears on the right hand side of comparisons.</param>
	/// <returns>True if all executed comparisons returned true, otherwise false.</returns>
	template<bool TestAllIndices_ = true, class LhsVector_, class Rhs_>
	[[nodiscard]] constexpr inline bool VectorCmpAllEqualTo(const LhsVector_& lhs_, const Rhs_& rhs_)
	{
		if constexpr (EmuMath::TMP::is_emu_vector_v<LhsVector_>)
		{
			return _underlying_vector_funcs::_vector_overall_comparison<TestAllIndices_, true, true, EmuCore::do_cmp_equal_to, LhsVector_, Rhs_>(lhs_, rhs_);
		}
		else
		{
			static_assert(false, "Attempted to compare the equality of all vector elements, but passed a non-EmuMath-vector left-hand operand.");
		}
	}

	/// <summary>
	/// <para> Returns a boolean indicating if all elements in the passed lhs_ vector are not equal to rhs_, depending on the type of rhs_. </para>
	/// <para> If rhs_ is an EmuMath vector, respective elements will be compared. Otherwise, all lhs_ elements will be compared to the same rhs_ value. </para>
	/// <para> By default, all indices are tested. To test only up to the end of the smallest vector, pass false as the argument for TestAllIndices_. </para>
	/// </summary>
	/// <typeparam name="LhsVector_">Type of EmuMath vector that appears on the left-hand side of comparisons.</typeparam>
	/// <typeparam name="Rhs_">Type of EmuMath vector or scalar that appears on the right hand side of comparisons.</typeparam>
	/// <param name="lhs_">EmuMath vector that appears on the left-hand side of comparisons.</param>
	/// <param name="rhs_">EmuMath vector or scalar that appears on the right hand side of comparisons.</param>
	/// <returns>True if all executed comparisons returned true, otherwise false.</returns>
	template<bool TestAllIndices_ = true, class LhsVector_, class Rhs_>
	[[nodiscard]] constexpr inline bool VectorCmpAllNotEqualTo(const LhsVector_& lhs_, const Rhs_& rhs_)
	{
		if constexpr (EmuMath::TMP::is_emu_vector_v<LhsVector_>)
		{
			return _underlying_vector_funcs::_vector_overall_comparison<TestAllIndices_, true, true, EmuCore::do_cmp_not_equal_to, LhsVector_, Rhs_>(lhs_, rhs_);
		}
		else
		{
			static_assert(false, "Attempted to compare the inequality of all vector elements, but passed a non-EmuMath-vector left-hand operand.");
		}
	}

	/// <summary>
	/// <para> Returns a boolean indicating if all elements in the passed lhs_ vector are greater than rhs_, depending on the type of rhs_. </para>
	/// <para> If rhs_ is an EmuMath vector, respective elements will be compared. Otherwise, all lhs_ elements will be compared to the same rhs_ value. </para>
	/// <para> By default, all indices are tested. To test only up to the end of the smallest vector, pass false as the argument for TestAllIndices_. </para>
	/// </summary>
	/// <typeparam name="LhsVector_">Type of EmuMath vector that appears on the left-hand side of comparisons.</typeparam>
	/// <typeparam name="Rhs_">Type of EmuMath vector or scalar that appears on the right hand side of comparisons.</typeparam>
	/// <param name="lhs_">EmuMath vector that appears on the left-hand side of comparisons.</param>
	/// <param name="rhs_">EmuMath vector or scalar that appears on the right hand side of comparisons.</param>
	/// <returns>True if all executed comparisons returned true, otherwise false.</returns>
	template<bool TestAllIndices_ = true, class LhsVector_, class Rhs_>
	[[nodiscard]] constexpr inline bool VectorCmpAllGreater(const LhsVector_& lhs_, const Rhs_& rhs_)
	{
		if constexpr (EmuMath::TMP::is_emu_vector_v<LhsVector_>)
		{
			return _underlying_vector_funcs::_vector_overall_comparison<TestAllIndices_, true, true, EmuCore::do_cmp_greater, LhsVector_, Rhs_>(lhs_, rhs_);
		}
		else
		{
			static_assert(false, "Attempted to compare the magnitude of all vector elements, but passed a non-EmuMath-vector left-hand operand.");
		}
	}

	/// <summary>
	/// <para> Returns a boolean indicating if all elements in the passed lhs_ vector are less than rhs_, depending on the type of rhs_. </para>
	/// <para> If rhs_ is an EmuMath vector, respective elements will be compared. Otherwise, all lhs_ elements will be compared to the same rhs_ value. </para>
	/// <para> By default, all indices are tested. To test only up to the end of the smallest vector, pass false as the argument for TestAllIndices_. </para>
	/// </summary>
	/// <typeparam name="LhsVector_">Type of EmuMath vector that appears on the left-hand side of comparisons.</typeparam>
	/// <typeparam name="Rhs_">Type of EmuMath vector or scalar that appears on the right hand side of comparisons.</typeparam>
	/// <param name="lhs_">EmuMath vector that appears on the left-hand side of comparisons.</param>
	/// <param name="rhs_">EmuMath vector or scalar that appears on the right hand side of comparisons.</param>
	/// <returns>True if all executed comparisons returned true, otherwise false.</returns>
	template<bool TestAllIndices_ = true, class LhsVector_, class Rhs_>
	[[nodiscard]] constexpr inline bool VectorCmpAllLess(const LhsVector_& lhs_, const Rhs_& rhs_)
	{
		if constexpr (EmuMath::TMP::is_emu_vector_v<LhsVector_>)
		{
			return _underlying_vector_funcs::_vector_overall_comparison<TestAllIndices_, true, true, EmuCore::do_cmp_less, LhsVector_, Rhs_>(lhs_, rhs_);
		}
		else
		{
			static_assert(false, "Attempted to compare the magnitude of all vector elements, but passed a non-EmuMath-vector left-hand operand.");
		}
	}

	/// <summary>
	/// <para> Returns a boolean indicating if all elements in the passed lhs_ vector are greater than or equal to rhs_, depending on the type of rhs_. </para>
	/// <para> If rhs_ is an EmuMath vector, respective elements will be compared. Otherwise, all lhs_ elements will be compared to the same rhs_ value. </para>
	/// <para> By default, all indices are tested. To test only up to the end of the smallest vector, pass false as the argument for TestAllIndices_. </para>
	/// </summary>
	/// <typeparam name="LhsVector_">Type of EmuMath vector that appears on the left-hand side of comparisons.</typeparam>
	/// <typeparam name="Rhs_">Type of EmuMath vector or scalar that appears on the right hand side of comparisons.</typeparam>
	/// <param name="lhs_">EmuMath vector that appears on the left-hand side of comparisons.</param>
	/// <param name="rhs_">EmuMath vector or scalar that appears on the right hand side of comparisons.</param>
	/// <returns>True if all executed comparisons returned true, otherwise false.</returns>
	template<bool TestAllIndices_ = true, class LhsVector_, class Rhs_>
	[[nodiscard]] constexpr inline bool VectorCmpAllGreaterEqual(const LhsVector_& lhs_, const Rhs_& rhs_)
	{
		if constexpr (EmuMath::TMP::is_emu_vector_v<LhsVector_>)
		{
			return _underlying_vector_funcs::_vector_overall_comparison<TestAllIndices_, true, true, EmuCore::do_cmp_greater_equal, LhsVector_, Rhs_>(lhs_, rhs_);
		}
		else
		{
			static_assert(false, "Attempted to compare the magnitude of all vector elements, but passed a non-EmuMath-vector left-hand operand.");
		}
	}

	/// <summary>
	/// <para> Returns a boolean indicating if all elements in the passed lhs_ vector are less than or equal to rhs_, depending on the type of rhs_. </para>
	/// <para> If rhs_ is an EmuMath vector, respective elements will be compared. Otherwise, all lhs_ elements will be compared to the same rhs_ value. </para>
	/// <para> By default, all indices are tested. To test only up to the end of the smallest vector, pass false as the argument for TestAllIndices_. </para>
	/// </summary>
	/// <typeparam name="LhsVector_">Type of EmuMath vector that appears on the left-hand side of comparisons.</typeparam>
	/// <typeparam name="Rhs_">Type of EmuMath vector or scalar that appears on the right hand side of comparisons.</typeparam>
	/// <param name="lhs_">EmuMath vector that appears on the left-hand side of comparisons.</param>
	/// <param name="rhs_">EmuMath vector or scalar that appears on the right hand side of comparisons.</param>
	/// <returns>True if all executed comparisons returned true, otherwise false.</returns>
	template<bool TestAllIndices_ = true, class LhsVector_, class Rhs_>
	[[nodiscard]] constexpr inline bool VectorCmpAllLessEqual(const LhsVector_& lhs_, const Rhs_& rhs_)
	{
		if constexpr (EmuMath::TMP::is_emu_vector_v<LhsVector_>)
		{
			return _underlying_vector_funcs::_vector_overall_comparison<TestAllIndices_, true, true, EmuCore::do_cmp_less_equal, LhsVector_, Rhs_>(lhs_, rhs_);
		}
		else
		{
			static_assert(false, "Attempted to compare the magnitude of all vector elements, but passed a non-EmuMath-vector left-hand operand.");
		}
	}

	/// <summary>
	/// <para> Performs an equality comparison with the type of comparison depending on the passed rhs_ argument. </para>
	/// <para>
	///		If the rhs_ argument is an EmuMath vector, this will compare respective elements of both vectors. 
	///		Otherwise, rhs_ will be assumed as scalar, and the magnitude of the lhs_ vector will be compared to rhs_.
	/// </para>
	/// <para>
	///		If TestAllIndices is true, comparisons will continue until both vector indices are exhausted. Otherwise, comparison will only go to the end of the smallest vector. 
	///		This argument is not used if rhs_ is not an EmuMath vector.
	/// </para>
	/// </summary>
	/// <typeparam name="LhsVector_">Type of EmuMath vector that appears on the left-hand side of comparisons.</typeparam>
	/// <typeparam name="Rhs_">
	///		Type of EmuMath vector that appears on the right-hand side of comparisons, or scalar that appears on the right-hand side of a magnitude comparison.
	/// </typeparam>
	/// <param name="lhs_">EmuMath vector that appears on the left-hand side of comparisons.</param>
	/// <param name="rhs_">EmuMath vector that appears on the right-hand side of comparisons, or scalar that appears on the right-hand side of a magnitude comparison.</param>
	/// <returns>
	///		<para>If rhs_ is an EmuMath vector: True if comparisons of all respective elements returned true, otherwise false.</para>
	///		<para>If rhs_ is NOT an EmuMath vector: Result of comparing the lhs_ vector's magnitude with the passed rhs_ value.</para>
	/// </returns>
	template<bool TestAllIndices_ = true, class LhsVector_, class Rhs_>
	[[nodiscard]] constexpr inline bool VectorCmpEqualTo(const LhsVector_& lhs_, const Rhs_& rhs_)
	{
		if constexpr (EmuMath::TMP::is_emu_vector_v<LhsVector_>)
		{
			return _underlying_vector_funcs::_vector_overall_comparison<TestAllIndices_, true, false, EmuCore::do_cmp_equal_to, LhsVector_, Rhs_>(lhs_, rhs_);
		}
		else
		{
			static_assert(false, "Attempted to perform a vector equality comparison, but the provided left-hand argument was not an EmuMath vector.");
		}
	}

	/// <summary>
	/// <para> Performs an inequality comparison with the type of comparison depending on the passed rhs_ argument. </para>
	/// <para>
	///		If the rhs_ argument is an EmuMath vector, this will compare respective elements of both vectors. 
	///		Otherwise, rhs_ will be assumed as scalar, and the magnitude of the lhs_ vector will be compared to rhs_.
	/// </para>
	/// <para>
	///		If TestAllIndices is true, comparisons will continue until both vector indices are exhausted. Otherwise, comparison will only go to the end of the smallest vector. 
	///		This argument is not used if rhs_ is not an EmuMath vector.
	/// </para>
	/// </summary>
	/// <typeparam name="LhsVector_">Type of EmuMath vector that appears on the left-hand side of comparisons.</typeparam>
	/// <typeparam name="Rhs_">
	///		Type of EmuMath vector that appears on the right-hand side of comparisons, or scalar that appears on the right-hand side of a magnitude comparison.
	/// </typeparam>
	/// <param name="lhs_">EmuMath vector that appears on the left-hand side of comparisons.</param>
	/// <param name="rhs_">EmuMath vector that appears on the right-hand side of comparisons, or scalar that appears on the right-hand side of a magnitude comparison.</param>
	/// <returns>
	///		<para>If rhs_ is an EmuMath vector: True if comparisons of at least one of the vectors' respective elements returned true, otherwise false.</para>
	///		<para>If rhs_ is NOT an EmuMath vector: Result of comparing the lhs_ vector's magnitude with the passed rhs_ value.</para>
	/// </returns>
	template<bool TestAllIndices_ = true, class LhsVector_, class Rhs_>
	[[nodiscard]] constexpr inline bool VectorCmpNotEqualTo(const LhsVector_& lhs_, const Rhs_& rhs_)
	{
		if constexpr (EmuMath::TMP::is_emu_vector_v<LhsVector_>)
		{
			return _underlying_vector_funcs::_vector_overall_comparison<TestAllIndices_, false, false, EmuCore::do_cmp_not_equal_to, LhsVector_, Rhs_>(lhs_, rhs_);
		}
		else
		{
			static_assert(false, "Attempted to perform a vector inequality comparison, but the provided left-hand argument was not an EmuMath vector.");
		}
	}

	/// <summary>
	/// <para> Compares the magnitude of the lhs_ vector with that of a rhs_ EmuMath vector, or directly with the value of rhs_ if it is not an EmuMath vector. </para>
	/// </summary>
	/// <typeparam name="LhsVector_">Type of EmuMath vector appearing on the left of the magnitude comparison.</typeparam>
	/// <typeparam name="Rhs_">Type of EmuMath vector or scalar appearing on the left of the magnitude comparison.</typeparam>
	/// <param name="lhs_">EmuMath vector appearing on the left of the magnitude comparison.</param>
	/// <param name="rhs_">EmuMath vector or scalar appearing on the left of the magnitude comparison.</param>
	/// <returns>True if the magnitude of lhs_ is greater than that of rhs_ if rhs_ is an EmuMath vector, or greater than rhs_ itself if it is a scalar.</returns>
	template<class LhsVector_, class Rhs_>
	[[nodiscard]] constexpr inline bool VectorCmpGreater(const LhsVector_& lhs_, const Rhs_& rhs_)
	{
		if constexpr (EmuMath::TMP::is_emu_vector_v<LhsVector_>)
		{
			return _underlying_vector_funcs::_vector_compare_magnitude<EmuCore::do_cmp_greater, LhsVector_, Rhs_>(lhs_, rhs_);
		}
		else
		{
			static_assert(false, "Attempted to perform a vector magnitude comparison, but the provided left-hand argument was not an EmuMath vector.");
		}
	}

	/// <summary>
	/// <para> Compares the magnitude of the lhs_ vector with that of a rhs_ EmuMath vector, or directly with the value of rhs_ if it is not an EmuMath vector. </para>
	/// </summary>
	/// <typeparam name="LhsVector_">Type of EmuMath vector appearing on the left of the magnitude comparison.</typeparam>
	/// <typeparam name="Rhs_">Type of EmuMath vector or scalar appearing on the left of the magnitude comparison.</typeparam>
	/// <param name="lhs_">EmuMath vector appearing on the left of the magnitude comparison.</param>
	/// <param name="rhs_">EmuMath vector or scalar appearing on the left of the magnitude comparison.</param>
	/// <returns>True if the magnitude of lhs_ is less than that of rhs_ if rhs_ is an EmuMath vector, or less than rhs_ itself if it is a scalar.</returns>
	template<class LhsVector_, class Rhs_>
	[[nodiscard]] constexpr inline bool VectorCmpLess(const LhsVector_& lhs_, const Rhs_& rhs_)
	{
		if constexpr (EmuMath::TMP::is_emu_vector_v<LhsVector_>)
		{
			return _underlying_vector_funcs::_vector_compare_magnitude<EmuCore::do_cmp_less, LhsVector_, Rhs_>(lhs_, rhs_);
		}
		else
		{
			static_assert(false, "Attempted to perform a vector magnitude comparison, but the provided left-hand argument was not an EmuMath vector.");
		}
	}

	/// <summary>
	/// <para> Compares the magnitude of the lhs_ vector with that of a rhs_ EmuMath vector, or directly with the value of rhs_ if it is not an EmuMath vector. </para>
	/// </summary>
	/// <typeparam name="LhsVector_">Type of EmuMath vector appearing on the left of the magnitude comparison.</typeparam>
	/// <typeparam name="Rhs_">Type of EmuMath vector or scalar appearing on the left of the magnitude comparison.</typeparam>
	/// <param name="lhs_">EmuMath vector appearing on the left of the magnitude comparison.</param>
	/// <param name="rhs_">EmuMath vector or scalar appearing on the left of the magnitude comparison.</param>
	/// <returns>True if the magnitude of lhs_ is greater than or equal to that of rhs_ if rhs_ is an EmuMath vector, or greater than or equal to rhs_ itself if it is a scalar.</returns>
	template<class LhsVector_, class Rhs_>
	[[nodiscard]] constexpr inline bool VectorCmpGreaterEqual(const LhsVector_& lhs_, const Rhs_& rhs_)
	{
		if constexpr (EmuMath::TMP::is_emu_vector_v<LhsVector_>)
		{
			return _underlying_vector_funcs::_vector_compare_magnitude<EmuCore::do_cmp_greater_equal, LhsVector_, Rhs_>(lhs_, rhs_);
		}
		else
		{
			static_assert(false, "Attempted to perform a vector magnitude comparison, but the provided left-hand argument was not an EmuMath vector.");
		}
	}

	/// <summary>
	/// <para> Compares the magnitude of the lhs_ vector with that of a rhs_ EmuMath vector, or directly with the value of rhs_ if it is not an EmuMath vector. </para>
	/// </summary>
	/// <typeparam name="LhsVector_">Type of EmuMath vector appearing on the left of the magnitude comparison.</typeparam>
	/// <typeparam name="Rhs_">Type of EmuMath vector or scalar appearing on the left of the magnitude comparison.</typeparam>
	/// <param name="lhs_">EmuMath vector appearing on the left of the magnitude comparison.</param>
	/// <param name="rhs_">EmuMath vector or scalar appearing on the left of the magnitude comparison.</param>
	/// <returns>True if the magnitude of lhs_ is less than or equal that of rhs_ if rhs_ is an EmuMath vector, or less than or equal to rhs_ itself if it is a scalar.</returns>
	template<class LhsVector_, class Rhs_>
	[[nodiscard]] constexpr inline bool VectorCmpLessEqual(const LhsVector_& lhs_, const Rhs_& rhs_)
	{
		if constexpr (EmuMath::TMP::is_emu_vector_v<LhsVector_>)
		{
			return _underlying_vector_funcs::_vector_compare_magnitude<EmuCore::do_cmp_less_equal, LhsVector_, Rhs_>(lhs_, rhs_);
		}
		else
		{
			static_assert(false, "Attempted to perform a vector magnitude comparison, but the provided left-hand argument was not an EmuMath vector.");
		}
	}

	/// <summary>
	/// <para> Returns a vector of booleans containing the results of comparing lhs_ with rhs_ via the provided cmpFunc_. </para>
	/// <para> If rhs_ is an EmuMath vector, respective elements will be compared. Otherwise (e.g. rhs_ is a scalar), all elements of lhs_ will be compared with rhs_. </para>
	/// <para> May provide an optional OutSize_ for the output vector to perform more or less comparisons than there are elements within the left-hand vector. </para>
	/// </summary>
	/// <typeparam name="Comparison_">Type to invoke to perform the comparison.</typeparam>
	/// <typeparam name="LhsVector_">EmuMath vector type of the left-hand argument.</typeparam>
	/// <typeparam name="Rhs_">EmuMath vector type or scalar type of the right-hand argument.</typeparam>
	/// <param name="lhs_">EmuMath vector which will have its elements compared on the left-hand side of the comparison.</param>
	/// <param name="rhs_">
	///		Either an EmuMath vector which will have its elements compared on the right-hand side of the comparison, 
	///		or a scalar that will always be used on the right-hand side of the comparison.
	/// </param>
	/// <param name="cmpFunc_">
	///		Function to perform the comparison. Requires an accessible function operator() which can take the two arguments. 
	///		If this argument is not provided, the default-constructed form of the Comparison_ will be used.
	/// </param>
	/// <returns>Vector of booleans containing the results of the comparison of respective elements within lhs_ with rhs_.</returns>
	template<std::size_t OutSize_, class Comparison_, class LhsVector_, class Rhs_>
	[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, bool> VectorPerElementComparison(const LhsVector_& lhs_, const Rhs_& rhs_, Comparison_ cmpFunc_)
	{
		if constexpr (EmuMath::TMP::is_emu_vector_v<LhsVector_>)
		{
			return _underlying_vector_funcs::_perform_vector_per_element_comparison<EmuMath::Vector<OutSize_, bool>, Comparison_, LhsVector_, Rhs_>(lhs_, rhs_, cmpFunc_);
		}
		else
		{
			static_assert(false, "Attempted to perform a comparison of each element of an EmuMath vector, but the left-hand operand was not an EmuMath vector.");
		}
	}
	template<std::size_t OutSize_, class Comparison_, class LhsVector_, class Rhs_>
	[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, bool> VectorPerElementComparison(const LhsVector_& lhs_, const Rhs_& rhs_)
	{
		return VectorPerElementComparison<OutSize_, Comparison_, LhsVector_, Rhs_>(lhs_, rhs_, Comparison_());
	}
	template<class Comparison_, class LhsVector_, class Rhs_>
	[[nodiscard]] constexpr inline EmuMath::Vector<LhsVector_::size, bool> VectorPerElementComparison(const LhsVector_& lhs_, const Rhs_& rhs_, Comparison_ cmpFunc_)
	{
		return VectorPerElementComparison<EmuMath::Vector<LhsVector_::size, bool>, Comparison_, LhsVector_, Rhs_>(lhs_, rhs_, cmpFunc_);
	}
	template<class Comparison_, class LhsVector_, class Rhs_>
	[[nodiscard]] constexpr inline EmuMath::Vector<LhsVector_::size, bool> VectorPerElementComparison(const LhsVector_& lhs_, const Rhs_& rhs_)
	{
		return VectorPerElementComparison<EmuMath::Vector<LhsVector_::size, bool>, Comparison_, LhsVector_, Rhs_>(lhs_, rhs_, Comparison_());
	}

	/// <summary>
	/// <para>
	///		Returns a vector of booleans containing the results of comparing the equality of respective elements of lhs_ with either those of the rhs_ vector,
	///		or a rhs_ scalar.
	/// </para>
	/// <para> If rhs_ is an EmuMath vector, it will be compared on a per-respective-element basis. If it is a scalar, all elements of lhs_ will be compared with it. </para>
	/// <para> May provide an optional OutSize_ for the output vector to perform more or less comparisons than there are elements within the left-hand vector. </para>
	/// <para> Operator equivalent: == </para>
	/// </summary>
	/// <typeparam name="LhsVector_">EmuMath vector type for the left-hand argument.</typeparam>
	/// <typeparam name="Rhs_">EmuMath vector or scalar type for the right-hand argument.</typeparam>
	/// <param name="lhs_">EmuMath vector to appear on the left-hand side of </param>
	/// <param name="rhs_">EmuMath vector to compare respective elements of the left-hand vector with, or scalar to compare all elements of the left-hand vector with.</param>
	/// <returns>Vector of booleans containing the results of the comparison of respective elements within lhs_ with rhs_.</returns>
	template<std::size_t OutSize_, class LhsVector_, class Rhs_>
	[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, bool> VectorPerElementCmpEqualTo(const LhsVector_& lhs_, const Rhs_& rhs_)
	{
		return VectorPerElementComparison<OutSize_, std::equal_to<void>, LhsVector_, Rhs_>(lhs_, rhs_, std::equal_to<void>());
	}
	template<class LhsVector_, class Rhs_>
	[[nodiscard]] constexpr inline EmuMath::Vector<LhsVector_::size, bool> VectorPerElementCmpEqualTo(const LhsVector_& lhs_, const Rhs_& rhs_)
	{
		return VectorPerElementCmpEqualTo<LhsVector_::size, LhsVector_, Rhs_>(lhs_, rhs_);
	}

	/// <summary>
	/// <para>
	///		Returns a vector of booleans containing the results of comparing the inequality of respective elements of lhs_ with either those of the rhs_ vector,
	///		or a rhs_ scalar.
	/// </para>
	/// <para> If rhs_ is an EmuMath vector, it will be compared on a per-respective-element basis. If it is a scalar, all elements of lhs_ will be compared with it. </para>
	/// <para> May provide an optional OutSize_ for the output vector to perform more or less comparisons than there are elements within the left-hand vector. </para>
	/// <para> Operator equivalent: != </para>
	/// </summary>
	/// <typeparam name="LhsVector_">EmuMath vector type for the left-hand argument.</typeparam>
	/// <typeparam name="Rhs_">EmuMath vector or scalar type for the right-hand argument.</typeparam>
	/// <param name="lhs_">EmuMath vector to appear on the left-hand side of </param>
	/// <param name="rhs_">EmuMath vector to compare respective elements of the left-hand vector with, or scalar to compare all elements of the left-hand vector with.</param>
	/// <returns>Vector of booleans containing the results of the comparison of respective elements within lhs_ with rhs_.</returns>
	template<std::size_t OutSize_, class LhsVector_, class Rhs_>
	[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, bool> VectorPerElementCmpNotEqualTo(const LhsVector_& lhs_, const Rhs_& rhs_)
	{
		return VectorPerElementComparison<OutSize_, std::not_equal_to<void>, LhsVector_, Rhs_>(lhs_, rhs_, std::not_equal_to<void>());
	}
	template<class LhsVector_, class Rhs_>
	[[nodiscard]] constexpr inline EmuMath::Vector<LhsVector_::size, bool> VectorPerElementCmpNotEqualTo(const LhsVector_& lhs_, const Rhs_& rhs_)
	{
		return VectorPerElementCmpNotEqualTo<LhsVector_::size, LhsVector_, Rhs_>(lhs_, rhs_);
	}

	/// <summary>
	/// <para>
	///		Returns a vector of booleans containing the results of comparing if respective elements of lhs_ are greater than either those of the rhs_ vector,
	///		or a rhs_ scalar.
	/// </para>
	/// <para> If rhs_ is an EmuMath vector, it will be compared on a per-respective-element basis. If it is a scalar, all elements of lhs_ will be compared with it. </para>
	/// <para> May provide an optional OutSize_ for the output vector to perform more or less comparisons than there are elements within the left-hand vector. </para>
	/// <para> Operator equivalent: &gt; </para>
	/// </summary>
	/// <typeparam name="LhsVector_">EmuMath vector type for the left-hand argument.</typeparam>
	/// <typeparam name="Rhs_">EmuMath vector or scalar type for the right-hand argument.</typeparam>
	/// <param name="lhs_">EmuMath vector to appear on the left-hand side of </param>
	/// <param name="rhs_">EmuMath vector to compare respective elements of the left-hand vector with, or scalar to compare all elements of the left-hand vector with.</param>
	/// <returns>Vector of booleans containing the results of the comparison of respective elements within lhs_ with rhs_.</returns>
	template<std::size_t OutSize_, class LhsVector_, class Rhs_>
	[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, bool> VectorPerElementCmpGreater(const LhsVector_& lhs_, const Rhs_& rhs_)
	{
		return VectorPerElementComparison<OutSize_, std::greater<void>, LhsVector_, Rhs_>(lhs_, rhs_, std::greater<void>());
	}
	template<class LhsVector_, class Rhs_>
	[[nodiscard]] constexpr inline EmuMath::Vector<LhsVector_::size, bool> VectorPerElementCmpGreater(const LhsVector_& lhs_, const Rhs_& rhs_)
	{
		return VectorPerElementCmpGreater<LhsVector_::size, LhsVector_, Rhs_>(lhs_, rhs_);
	}

	/// <summary>
	/// <para>
	///		Returns a vector of booleans containing the results of comparing if respective elements of lhs_ are less than either those of the rhs_ vector,
	///		or a rhs_ scalar.
	/// </para>
	/// <para> If rhs_ is an EmuMath vector, it will be compared on a per-respective-element basis. If it is a scalar, all elements of lhs_ will be compared with it. </para>
	/// <para> May provide an optional OutSize_ for the output vector to perform more or less comparisons than there are elements within the left-hand vector. </para>
	/// <para> Operator equivalent: &lt; </para>
	/// </summary>
	/// <typeparam name="LhsVector_">EmuMath vector type for the left-hand argument.</typeparam>
	/// <typeparam name="Rhs_">EmuMath vector or scalar type for the right-hand argument.</typeparam>
	/// <param name="lhs_">EmuMath vector to appear on the left-hand side of </param>
	/// <param name="rhs_">EmuMath vector to compare respective elements of the left-hand vector with, or scalar to compare all elements of the left-hand vector with.</param>
	/// <returns>Vector of booleans containing the results of the comparison of respective elements within lhs_ with rhs_.</returns>
	template<std::size_t OutSize_, class LhsVector_, class Rhs_>
	[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, bool> VectorPerElementCmpLess(const LhsVector_& lhs_, const Rhs_& rhs_)
	{
		return VectorPerElementComparison<OutSize_, std::less<void>, LhsVector_, Rhs_>(lhs_, rhs_, std::less<void>());
	}
	template<class LhsVector_, class Rhs_>
	[[nodiscard]] constexpr inline EmuMath::Vector<LhsVector_::size, bool> VectorPerElementCmpLess(const LhsVector_& lhs_, const Rhs_& rhs_)
	{
		return VectorPerElementCmpLess<LhsVector_::size, LhsVector_, Rhs_>(lhs_, rhs_);
	}

	/// <summary>
	/// <para>
	///		Returns a vector of booleans containing the results of comparing if respective elements of lhs_ are greater than or equal to either those of the rhs_ vector,
	///		or a rhs_ scalar.
	/// </para>
	/// <para> If rhs_ is an EmuMath vector, it will be compared on a per-respective-element basis. If it is a scalar, all elements of lhs_ will be compared with it. </para>
	/// <para> May provide an optional OutSize_ for the output vector to perform more or less comparisons than there are elements within the left-hand vector. </para>
	/// <para> Operator equivalent: &gt;= </para>
	/// </summary>
	/// <typeparam name="LhsVector_">EmuMath vector type for the left-hand argument.</typeparam>
	/// <typeparam name="Rhs_">EmuMath vector or scalar type for the right-hand argument.</typeparam>
	/// <param name="lhs_">EmuMath vector to appear on the left-hand side of </param>
	/// <param name="rhs_">EmuMath vector to compare respective elements of the left-hand vector with, or scalar to compare all elements of the left-hand vector with.</param>
	/// <returns>Vector of booleans containing the results of the comparison of respective elements within lhs_ with rhs_.</returns>
	template<std::size_t OutSize_, class LhsVector_, class Rhs_>
	[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, bool> VectorPerElementCmpGreaterEqual(const LhsVector_& lhs_, const Rhs_& rhs_)
	{
		return VectorPerElementComparison<OutSize_, std::greater_equal<void>, LhsVector_, Rhs_>(lhs_, rhs_, std::greater_equal<void>());
	}
	template<class LhsVector_, class Rhs_>
	[[nodiscard]] constexpr inline EmuMath::Vector<LhsVector_::size, bool> VectorPerElementCmpGreaterEqual(const LhsVector_& lhs_, const Rhs_& rhs_)
	{
		return VectorPerElementCmpGreaterEqual<LhsVector_::size, LhsVector_, Rhs_>(lhs_, rhs_);
	}

	/// <summary>
	/// <para>
	///		Returns a vector of booleans containing the results of comparing if respective elements of lhs_ are less than or equal to either those of the rhs_ vector,
	///		or a rhs_ scalar.
	/// </para>
	/// <para> If rhs_ is an EmuMath vector, it will be compared on a per-respective-element basis. If it is a scalar, all elements of lhs_ will be compared with it. </para>
	/// <para> May provide an optional OutSize_ for the output vector to perform more or less comparisons than there are elements within the left-hand vector. </para>
	/// <para> Operator equivalent: &lt;= </para>
	/// </summary>
	/// <typeparam name="LhsVector_">EmuMath vector type for the left-hand argument.</typeparam>
	/// <typeparam name="Rhs_">EmuMath vector or scalar type for the right-hand argument.</typeparam>
	/// <param name="lhs_">EmuMath vector to appear on the left-hand side of </param>
	/// <param name="rhs_">EmuMath vector to compare respective elements of the left-hand vector with, or scalar to compare all elements of the left-hand vector with.</param>
	/// <returns>Vector of booleans containing the results of the comparison of respective elements within lhs_ with rhs_.</returns>
	template<std::size_t OutSize_, class LhsVector_, class Rhs_>
	[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, bool> VectorPerElementCmpLessEqual(const LhsVector_& lhs_, const Rhs_& rhs_)
	{
		return VectorPerElementComparison<OutSize_, std::less_equal<void>, LhsVector_, Rhs_>(lhs_, rhs_, std::less_equal<void>());
	}
	template<class LhsVector_, class Rhs_>
	[[nodiscard]] constexpr inline EmuMath::Vector<LhsVector_::size, bool> VectorPerElementCmpLessEqual(const LhsVector_& lhs_, const Rhs_& rhs_)
	{
		return VectorPerElementCmpLessEqual<LhsVector_::size, LhsVector_, Rhs_>(lhs_, rhs_);
	}
#pragma endregion

#pragma region BITWISE
	/// <summary>
	/// <para> Shifts each element in the passed vector to the left the specified number of times, outputting the results in a new vector. </para>
	/// <para>
	///		The passed num_shifts_ may be a scalar type or an EmuMath vector. 
	///		If it is an EmuMath vector, shifts for each element will be performed a number of times equal to the value in the respective index of this vector. 
	///		Otherwise, all elements will be shifted by this value.
	/// </para>
	/// <para> This function uses an instantiation of EmuCore::do_left_shift&lt;Vector_::value_type, Shifts_&gt; to perform each shift. </para>
	/// </summary>
	/// <typeparam name="out_value_type">Type to be contained within the output vector.</typeparam>
	/// <typeparam name="Vector_">Type of vector to shift the elements of.</typeparam>
	/// <typeparam name="Shifts_">Scalar type or EmuMath vector used to represent the number of shifts.</typeparam>
	/// <param name="vector_">EmuMath vector to shift the elements of. Its value_type must be shiftable via the EmuCore::do_left_shift functor for said type.</param>
	/// <param name="num_shifts_">Scalar or EmuMath vector representing the number of shifts to apply to every element or to each respective element.</param>
	/// <returns>Result of left-shifting the elements of the passed EmuMath vector the specified number of times in num_shifts_.</returns>
	template<std::size_t OutSize_, typename out_value_type, class Vector_, class Shifts_>
	[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, out_value_type> VectorShiftLeft(const Vector_& vector_, const Shifts_& num_shifts_)
	{
		if constexpr (EmuMath::TMP::is_emu_vector_v<Vector_>)
		{
			if constexpr(EmuMath::TMP::is_emu_vector_v<Shifts_> || std::is_convertible_v<Shifts_, std::size_t>)
			{
				return _underlying_vector_funcs::_vector_bitwise_shift_per_element
				<
					EmuMath::Vector<OutSize_, out_value_type>,
					Vector_,
					Shifts_,
					EmuCore::do_left_shift
				>(vector_, num_shifts_);
			}
			else
			{
				static_assert(false, "Attempted to shift each element within a vector to the left, but the provided num_shifts_ was neither an EmuMath vector nor a type convertible to std::size_t.");
			}
		}
		else
		{
			static_assert(false, "Attempted to shift each element within a vector to the left, but the provided argument was not an EmuMath vector type.");
		}
	}
	template<typename out_value_type, class Vector_, class Shifts_>
	[[nodiscard]] constexpr inline EmuMath::Vector<Vector_::size, out_value_type> VectorShiftLeft(const Vector_& vector_, const Shifts_& num_shifts_)
	{
		return VectorShiftLeft<Vector_::size, out_value_type, Vector_, Shifts_>(vector_, num_shifts_);
	}
	template<std::size_t OutSize_, class Vector_, class Shifts_>
	[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, typename Vector_::value_type> VectorShiftLeft(const Vector_& vector_, const Shifts_& num_shifts_)
	{
		return VectorShiftLeft<OutSize_, typename Vector_::value_type, Vector_, Shifts_>(vector_, num_shifts_);
	}
	template<class Vector_, class Shifts_>
	[[nodiscard]] constexpr inline EmuMath::Vector<Vector_::size, typename Vector_::value_type> VectorShiftLeft(const Vector_& vector_, const Shifts_& num_shifts_)
	{
		return VectorShiftLeft<Vector_::size, typename Vector_::value_type, Vector_, Shifts_>(vector_, num_shifts_);
	}

	/// <summary>
	/// <para> Shifts each element in the passed vector to the right the specified number of times, outputting the results in a new vector. </para>
	/// <para>
	///		The passed num_shifts_ may be a scalar type or an EmuMath vector. 
	///		If it is an EmuMath vector, shifts for each element will be performed a number of times equal to the value in the respective index of this vector. 
	///		Otherwise, all elements will be shifted by this value.
	/// </para>
	/// <para> This function uses an instantiation of EmuCore::do_right_shift&lt;Vector_::value_type, Shifts_&gt; to perform each shift. </para>
	/// </summary>
	/// <typeparam name="out_value_type">Type to be contained within the output vector.</typeparam>
	/// <typeparam name="Vector_">Type of vector to shift the elements of.</typeparam>
	/// <typeparam name="Shifts_">Scalar type or EmuMath vector used to represent the number of shifts.</typeparam>
	/// <param name="vector_">EmuMath vector to shift the elements of. Its value_type must be shiftable via the EmuCore::do_right_shift functor for said type.</param>
	/// <param name="num_shifts_">Scalar or EmuMath vector representing the number of shifts to apply to every element or to each respective element.</param>
	/// <returns>Result of right-shifting the elements of the passed EmuMath vector the specified number of times in num_shifts_.</returns>
	template<std::size_t OutSize_, typename out_value_type, class Vector_, class Shifts_>
	[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, out_value_type> VectorShiftRight(const Vector_& vector_, const Shifts_& num_shifts_)
	{
		if constexpr (EmuMath::TMP::is_emu_vector_v<Vector_>)
		{
			if constexpr (EmuMath::TMP::is_emu_vector_v<Shifts_> || std::is_convertible_v<Shifts_, std::size_t>)
			{
				return _underlying_vector_funcs::_vector_bitwise_shift_per_element
				<
					EmuMath::Vector<OutSize_, out_value_type>,
					Vector_,
					Shifts_,
					EmuCore::do_right_shift
				>(vector_, num_shifts_);
			}
			else
			{
				static_assert(false, "Attempted to shift each element within a vector to the right, but the provided num_shifts_ was neither an EmuMath vector nor a type convertible to std::size_t.");
			}
		}
		else
		{
			static_assert(false, "Attempted to shift each element within a vector to the right, but the provided argument was not an EmuMath vector type.");
		}
	}
	template<typename out_value_type, class Vector_, class Shifts_>
	[[nodiscard]] constexpr inline EmuMath::Vector<Vector_::size, out_value_type> VectorShiftRight(const Vector_& vector_, const Shifts_& num_shifts_)
	{
		return VectorShiftRight<Vector_::size, out_value_type, Vector_, Shifts_>(vector_, num_shifts_);
	}
	template<std::size_t OutSize_, class Vector_, class Shifts_>
	[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, typename Vector_::value_type> VectorShiftRight(const Vector_& vector_, const Shifts_& num_shifts_)
	{
		return VectorShiftRight<OutSize_, typename Vector_::value_type, Vector_, Shifts_>(vector_, num_shifts_);
	}
	template<class Vector_, class Shifts_>
	[[nodiscard]] constexpr inline EmuMath::Vector<Vector_::size, typename Vector_::value_type> VectorShiftRight(const Vector_& vector_, const Shifts_& num_shifts_)
	{
		return VectorShiftRight<Vector_::size, typename Vector_::value_type, Vector_, Shifts_>(vector_, num_shifts_);
	}

	/// <summary>
	/// <para> Perform a bitwise AND with all elements of the lhs_ vector with the rhs_, depending on the type rhs_ is passed as. </para>
	/// <para> If rhs_ is an EmuMath vector, respective elements will be ANDed, otherwise all elements in lhs_ will be ANDed with the value of rhs_ itself. </para>
	/// <para> This operatoion is carried out by EmuCore::do_bitwise_and&lt;LhsVector_::value_type, Rhs_::value_type (or just Rhs_ if not a vector)&gt;. </para>
	/// </summary>
	/// <typeparam name="out_value_type">Type to be contained within the output vector.</typeparam>
	/// <typeparam name="LhsVector_">Type of vector appearing on the left-hand side of AND operations.</typeparam>
	/// <typeparam name="Rhs_">Type of vector or scalar appearing the the right-hand side of AND operations.</typeparam>
	/// <param name="lhs_">EmuMath vector appearing on the left-hand side of AND operations.</param>
	/// <param name="rhs_">EmuMath vector or scalar appearing on the left-hand side of AND operations.</param>
	/// <returns>EmuMath vector containing the results of bitwise ANDing the provided operands.</returns>
	template<std::size_t OutSize_, typename out_value_type, class LhsVector_, class Rhs_>
	[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, out_value_type> VectorAnd(const LhsVector_& lhs_, const Rhs_& rhs_)
	{
		if constexpr (EmuMath::TMP::is_emu_vector_v<LhsVector_>)
		{
			return _underlying_vector_funcs::_vector_bitwise_non_shift_op
			<
				EmuMath::Vector<OutSize_, out_value_type>,
				LhsVector_,
				Rhs_,
				EmuCore::do_bitwise_and<typename LhsVector_::value_type, EmuCore::TMPHelpers::get_value_type_t<Rhs_>>
			>
			(
				lhs_,
				rhs_
			);
		}
		else
		{
			static_assert(false, "Attempted to perform a bitwise AND on a vector, but the provided lhs_ argument was not an EmuMath vector.");
		}
	}
	template<typename out_value_type, class LhsVector_, class Rhs_>
	[[nodiscard]] constexpr inline EmuMath::Vector<LhsVector_::size, out_value_type> VectorAnd(const LhsVector_& lhs_, const Rhs_& rhs_)
	{
		return VectorAnd<LhsVector_::size, out_value_type, LhsVector_, Rhs_>(lhs_, rhs_);
	}
	template<std::size_t OutSize_, class LhsVector_, class Rhs_>
	[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, typename LhsVector_::value_type> VectorAnd(const LhsVector_& lhs_, const Rhs_& rhs_)
	{
		return VectorAnd<OutSize_, typename LhsVector_::value_type, LhsVector_, Rhs_>(lhs_, rhs_);
	}
	template<class LhsVector_, class Rhs_>
	[[nodiscard]] constexpr inline EmuMath::Vector<LhsVector_::size, typename LhsVector_::value_type> VectorAnd(const LhsVector_& lhs_, const Rhs_& rhs_)
	{
		return VectorAnd<LhsVector_::size, typename LhsVector_::value_type, LhsVector_, Rhs_>(lhs_, rhs_);
	}

	/// <summary>
	/// <para> Perform a bitwise OR with all elements of the lhs_ vector with the rhs_, depending on the type rhs_ is passed as. </para>
	/// <para> If rhs_ is an EmuMath vector, respective elements will be ORed, otherwise all elements in lhs_ will be ORed with the value of rhs_ itself. </para>
	/// <para> This operatoion is carried out by EmuCore::do_bitwise_or&lt;LhsVector_::value_type, Rhs_::value_type (or just Rhs_ if not a vector)&gt;. </para>
	/// </summary>
	/// <typeparam name="out_value_type">Type to be contained within the output vector.</typeparam>
	/// <typeparam name="LhsVector_">Type of vector appearing on the left-hand side of OR operations.</typeparam>
	/// <typeparam name="Rhs_">Type of vector or scalar appearing the the right-hand side of OR operations.</typeparam>
	/// <param name="lhs_">EmuMath vector appearing on the left-hand side of OR operations.</param>
	/// <param name="rhs_">EmuMath vector or scalar appearing on the left-hand side of OR operations.</param>
	/// <returns>EmuMath vector containing the results of bitwise ORing the provided operands.</returns>
	template<std::size_t OutSize_, typename out_value_type, class LhsVector_, class Rhs_>
	[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, out_value_type> VectorOr(const LhsVector_& lhs_, const Rhs_& rhs_)
	{
		if constexpr (EmuMath::TMP::is_emu_vector_v<LhsVector_>)
		{
			return _underlying_vector_funcs::_vector_bitwise_non_shift_op
			<
				EmuMath::Vector<OutSize_, out_value_type>,
				LhsVector_,
				Rhs_,
				EmuCore::do_bitwise_or<typename LhsVector_::value_type, EmuCore::TMPHelpers::get_value_type_t<Rhs_>>
			>
			(
				lhs_,
				rhs_
			);
		}
		else
		{
			static_assert(false, "Attempted to perform a bitwise OR on a vector, but the provided lhs_ argument was not an EmuMath vector.");
		}
	}
	template<typename out_value_type, class LhsVector_, class Rhs_>
	[[nodiscard]] constexpr inline EmuMath::Vector<LhsVector_::size, out_value_type> VectorOr(const LhsVector_& lhs_, const Rhs_& rhs_)
	{
		return VectorOr<LhsVector_::size, out_value_type, LhsVector_, Rhs_>(lhs_, rhs_);
	}
	template<std::size_t OutSize_, class LhsVector_, class Rhs_>
	[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, typename LhsVector_::value_type> VectorOr(const LhsVector_& lhs_, const Rhs_& rhs_)
	{
		return VectorOr<OutSize_, typename LhsVector_::value_type, LhsVector_, Rhs_>(lhs_, rhs_);
	}
	template<class LhsVector_, class Rhs_>
	[[nodiscard]] constexpr inline EmuMath::Vector<LhsVector_::size, typename LhsVector_::value_type> VectorOr(const LhsVector_& lhs_, const Rhs_& rhs_)
	{
		return VectorOr<LhsVector_::size, typename LhsVector_::value_type, LhsVector_, Rhs_>(lhs_, rhs_);
	}

	/// <summary>
	/// <para> Perform a bitwise XOR with all elements of the lhs_ vector with the rhs_, depending on the type rhs_ is passed as. </para>
	/// <para> If rhs_ is an EmuMath vector, respective elements will be XORed, otherwise all elements in lhs_ will be XORed with the value of rhs_ itself. </para>
	/// <para> This operatoion is carried out by EmuCore::do_bitwise_xor&lt;LhsVector_::value_type, Rhs_::value_type (or just Rhs_ if not a vector)&gt;. </para>
	/// </summary>
	/// <typeparam name="out_value_type">Type to be contained within the output vector.</typeparam>
	/// <typeparam name="LhsVector_">Type of vector appearing on the left-hand side of XOR operations.</typeparam>
	/// <typeparam name="Rhs_">Type of vector or scalar appearing the the right-hand side of XOR operations.</typeparam>
	/// <param name="lhs_">EmuMath vector appearing on the left-hand side of XOR operations.</param>
	/// <param name="rhs_">EmuMath vector or scalar appearing on the left-hand side of XOR operations.</param>
	/// <returns>EmuMath vector containing the results of bitwise XOR the provided operands.</returns>
	template<std::size_t OutSize_, typename out_value_type, class LhsVector_, class Rhs_>
	[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, out_value_type> VectorXor(const LhsVector_& lhs_, const Rhs_& rhs_)
	{
		if constexpr (EmuMath::TMP::is_emu_vector_v<LhsVector_>)
		{
			return _underlying_vector_funcs::_vector_bitwise_non_shift_op
			<
				EmuMath::Vector<OutSize_, out_value_type>,
				LhsVector_,
				Rhs_,
				EmuCore::do_bitwise_xor<typename LhsVector_::value_type, EmuCore::TMPHelpers::get_value_type_t<Rhs_>>
			>
			(
				lhs_,
				rhs_
			);
		}
		else
		{
			static_assert(false, "Attempted to perform a bitwise XOR on a vector, but the provided lhs_ argument was not an EmuMath vector.");
		}
	}
	template<typename out_value_type, class LhsVector_, class Rhs_>
	[[nodiscard]] constexpr inline EmuMath::Vector<LhsVector_::size, out_value_type> VectorXor(const LhsVector_& lhs_, const Rhs_& rhs_)
	{
		return VectorXor<LhsVector_::size, out_value_type, LhsVector_, Rhs_>(lhs_, rhs_);
	}
	template<std::size_t OutSize_, class LhsVector_, class Rhs_>
	[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, typename LhsVector_::value_type> VectorXor(const LhsVector_& lhs_, const Rhs_& rhs_)
	{
		return VectorXor<OutSize_, typename LhsVector_::value_type, LhsVector_, Rhs_>(lhs_, rhs_);
	}
	template<class LhsVector_, class Rhs_>
	[[nodiscard]] constexpr inline EmuMath::Vector<LhsVector_::size, typename LhsVector_::value_type> VectorXor(const LhsVector_& lhs_, const Rhs_& rhs_)
	{
		return VectorXor<LhsVector_::size, typename LhsVector_::value_type, LhsVector_, Rhs_>(lhs_, rhs_);
	}

	/// <summary>
	/// <para> Performs a bitwise NOT on all elements within the passed vector and outputs the results in the return vector. </para>
	/// <para> This operatoion is carried out by EmuCore::do_bitwise_not&lt;Vector_::value_type&gt;. </para>
	/// </summary>
	/// <typeparam name="out_value_type">Type to be contained within the output vector.</typeparam>
	/// <typeparam name="Vector_">Type of vector to perform the bitwise NOT operation on.</typeparam>
	/// <param name="vector_">EmuMath vector to perform the bitwise NOT operation on.</param>
	/// <returns>EmuMath vector containing the results of the bitwise NOT operation on the passed vector_.</returns>
	template<std::size_t OutSize_, typename out_value_type, class Vector_>
	[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, out_value_type> VectorNot(const Vector_& vector_)
	{
		if constexpr (EmuMath::TMP::is_emu_vector_v<Vector_>)
		{
			return _underlying_vector_funcs::_vector_single_operand_func
			<
				EmuMath::Vector<OutSize_, out_value_type>,
				Vector_,
				EmuCore::do_bitwise_not<typename Vector_::value_type>
			>(vector_);
		}
		else
		{
			static_assert(false, "Attempted to perform a bitwise NOT on a vector, but the provided lhs_ argument was not an EmuMath vector.");
		}
	}
	template<typename out_value_type, class Vector_>
	[[nodiscard]] constexpr inline EmuMath::Vector<Vector_::size, out_value_type> VectorNot(const Vector_& vector_)
	{
		return VectorNot<Vector_::size, out_value_type, Vector_>(vector_);
	}
	template<std::size_t OutSize_, class Vector_>
	[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, typename Vector_::value_type> VectorNot(const Vector_& vector_)
	{
		return VectorNot<OutSize_, typename Vector_::value_type, Vector_>(vector_);
	}
	template<class Vector_>
	[[nodiscard]] constexpr inline EmuMath::Vector<Vector_::size, typename Vector_::value_type> VectorNot(const Vector_& vector_)
	{
		return VectorNot<Vector_::size, typename Vector_::value_type, Vector_>(vector_);
	}
#pragma endregion
}

#pragma region EMU_CORE_SPECIALISATIONS
namespace EmuCore
{
#pragma region ARITHMETIC
	/// <summary> do_lerp specialisation which defers the calculation to EmuMath::Helpers::VectorLerp. Leaves room for specific vectors to be specialised. </summary>
	/// <typeparam name="a_value_type">Type contained within the vector used for argument A_.<typeparam>
	template<std::size_t ASize_, typename a_value_type, class B_, class T_>
	struct do_lerp<EmuMath::Vector<ASize_, a_value_type>, B_, T_>
	{
		constexpr do_lerp()
		{
		}
		[[nodiscard]] constexpr inline auto operator()(const EmuMath::Vector<ASize_, a_value_type>& a_, const B_& b_, const T_& t_) const
		{
			return EmuMath::Helpers::VectorLerp(a_, b_, t_);
		}
	};

	/// <summary> do_floor specialisation which defers a flooring calculation to EmuMath::Helpers::VectorFloor. Leaves room for specific vectors to be specialised. </summary>
	/// <typeparam name="T_">Type contained within the passed EmuMath vector.</typeparam>
	template<std::size_t Size_, typename T_>
	struct do_floor<EmuMath::Vector<Size_, T_>>
	{
		constexpr do_floor()
		{
		}
		[[nodiscard]] constexpr inline auto operator()(const EmuMath::Vector<Size_, T_>& vector_) const
		{
			return EmuMath::Helpers::VectorFloor(vector_);
		}
	};

	/// <summary> do_ceil specialisation which defers a ceiling calculation to EmuMath::Helpers::VectorCeil. Leaves room for specific vectors to be specialised. </summary>
	/// <typeparam name="T_">Type contained within the passed EmuMath vector.</typeparam>
	template<std::size_t Size_, typename T_>
	struct do_ceil<EmuMath::Vector<Size_, T_>>
	{
		constexpr do_ceil()
		{
		}
		[[nodiscard]] constexpr inline auto operator()(const EmuMath::Vector<Size_, T_>& vector_) const
		{
			return EmuMath::Helpers::VectorCeil(vector_);
		}
	};

	/// <summary> do_trunc specialisation which defers a truncating calculation to EmuMath::Helpers::VectorTrunc. Leaves room for specific vectors to be specialised. </summary>
	/// <typeparam name="T_">Type contained within the passed EmuMath vector.</typeparam>
	template<std::size_t Size_, typename T_>
	struct do_trunc<EmuMath::Vector<Size_, T_>>
	{
		constexpr do_trunc()
		{
		}
		[[nodiscard]] constexpr inline auto operator()(const EmuMath::Vector<Size_, T_>& vector_) const
		{
			return EmuMath::Helpers::VectorTrunc(vector_);
		}
	};

	/// <summary> 
	///		do_sqrt_constexpr specialisation which defers a constexpr sqrt calculation to EmuMath::Helpers::VectorSqrtConstexpr. 
	///		Leaves room for specific vectors to be specialised.
	/// </summary>
	/// <typeparam name="T_">Type contained within the passed EmuMath vector.</typeparam>
	template<std::size_t Size_, typename T_>
	struct do_sqrt_constexpr<EmuMath::Vector<Size_, T_>>
	{
		constexpr do_sqrt_constexpr()
		{
		}
		[[nodiscard]] constexpr inline auto operator()(const EmuMath::Vector<Size_, T_>& vector_) const
		{
			return EmuMath::Helpers::VectorSqrtConstexpr(vector_);
		}
	};

	/// <summary> do_sqrt specialisation which defers a square root calculation to EmuMath::Helpers::VectorSqrt. Leaves room for specific vectors to be specialised. </summary>
	/// <typeparam name="T_">Type contained within the passed EmuMath vector.</typeparam>
	template<std::size_t Size_, typename T_>
	struct do_sqrt<EmuMath::Vector<Size_, T_>>
	{
		constexpr do_sqrt()
		{
		}
		[[nodiscard]] inline auto operator()(const EmuMath::Vector<Size_, T_>& vector_) const
		{
			return EmuMath::Helpers::VectorSqrt(vector_);
		}
	};

	template<std::size_t Size_, typename T_, typename Rhs_>
	struct do_add<EmuMath::Vector<Size_, T_>, Rhs_>
	{
		constexpr do_add()
		{
		}
		constexpr inline auto operator()(const EmuMath::Vector<Size_, T_>& lhs_, const Rhs_& rhs_) const
		{
			return EmuMath::Helpers::VectorAdd(lhs_, rhs_);
		}
	};

	template<std::size_t Size_, typename T_, typename Rhs_>
	struct do_subtract<EmuMath::Vector<Size_, T_>, Rhs_>
	{
		constexpr do_subtract()
		{
		}
		constexpr inline auto operator()(const EmuMath::Vector<Size_, T_>& lhs_, const Rhs_& rhs_) const
		{
			return EmuMath::Helpers::VectorSubtract(lhs_, rhs_);
		}
	};

	template<std::size_t Size_, typename T_, typename Rhs_>
	struct do_multiply<EmuMath::Vector<Size_, T_>, Rhs_>
	{
		constexpr do_multiply()
		{
		}
		constexpr inline auto operator()(const EmuMath::Vector<Size_, T_>& lhs_, const Rhs_& rhs_) const
		{
			return EmuMath::Helpers::VectorMultiply(lhs_, rhs_);
		}
	};

	template<std::size_t Size_, typename T_, typename Rhs_>
	struct do_divide<EmuMath::Vector<Size_, T_>, Rhs_>
	{
		constexpr do_divide()
		{
		}
		constexpr inline auto operator()(const EmuMath::Vector<Size_, T_>& lhs_, const Rhs_& rhs_) const
		{
			return EmuMath::Helpers::VectorDivide(lhs_, rhs_);
		}
	};

	template<std::size_t Size_, typename T_>
	struct do_negate<EmuMath::Vector<Size_, T_>>
	{
		constexpr do_negate()
		{
		}
		constexpr inline auto operator()(const EmuMath::Vector<Size_, T_>& vector_) const
		{
			return EmuMath::Helpers::VectorNegate(vector_);
		}
	};
#pragma endregion

#pragma region BITWISE
	template<std::size_t Size_, typename T_, typename Rhs_>
	struct do_bitwise_and<EmuMath::Vector<Size_, T_>, Rhs_>
	{
		constexpr do_bitwise_and()
		{
		}
		[[nodiscard]] constexpr inline auto operator()(const EmuMath::Vector<Size_, T_>& lhs_, const Rhs_& rhs_)
		{
			return EmuMath::Helpers::VectorAnd<Size_, T_, EmuMath::Vector<Size_, T_>, Rhs_>(lhs_, rhs_);
		}
	};

	template<std::size_t Size_, typename T_, typename Rhs_>
	struct do_bitwise_or<EmuMath::Vector<Size_, T_>, Rhs_>
	{
		constexpr do_bitwise_or()
		{
		}
		[[nodiscard]] constexpr inline auto operator()(const EmuMath::Vector<Size_, T_>& lhs_, const Rhs_& rhs_)
		{
			return EmuMath::Helpers::VectorOr<Size_, T_, EmuMath::Vector<Size_, T_>, Rhs_>(lhs_, rhs_);
		}
	};

	template<std::size_t Size_, typename T_, typename Rhs_>
	struct do_bitwise_xor<EmuMath::Vector<Size_, T_>, Rhs_>
	{
		constexpr do_bitwise_xor()
		{
		}
		[[nodiscard]] constexpr inline auto operator()(const EmuMath::Vector<Size_, T_>& lhs_, const Rhs_& rhs_)
		{
			return EmuMath::Helpers::VectorXor<Size_, T_, EmuMath::Vector<Size_, T_>, Rhs_>(lhs_, rhs_);
		}
	};

	template<std::size_t Size_, typename T_>
	struct do_bitwise_not<EmuMath::Vector<Size_, T_>>
	{
		constexpr do_bitwise_not()
		{
		}
		[[nodiscard]] constexpr inline auto operator()(const EmuMath::Vector<Size_, T_>& vector_)
		{
			return EmuMath::Helpers::VectorNot<Size_, T_, EmuMath::Vector<Size_, T_>>(vector_);
		}
	};

	template<std::size_t Size_, typename T_, typename Shifts_>
	struct do_left_shift<EmuMath::Vector<Size_, T_>, Shifts_>
	{
		constexpr do_left_shift()
		{
		}
		[[nodiscard]] constexpr inline auto operator()(const EmuMath::Vector<Size_, T_>& vector_, const Shifts_& num_shifts_) const
		{
			if constexpr (std::is_arithmetic_v<Shifts_>)
			{
				return EmuMath::Helpers::VectorShiftLeft(vector_, static_cast<std::size_t>(num_shifts_));
			}
			else
			{
				return EmuMath::Helpers::VectorShiftLeft(vector_, num_shifts_);
			}
		}
	};

	template<std::size_t Size_, typename T_, typename Shifts_>
	struct do_right_shift<EmuMath::Vector<Size_, T_>, Shifts_>
	{
		constexpr do_right_shift()
		{
		}
		[[nodiscard]] constexpr inline auto operator()(const EmuMath::Vector<Size_, T_>& vector_, const Shifts_& num_shifts_) const
		{
			if constexpr (std::is_arithmetic_v<Shifts_>)
			{
				return EmuMath::Helpers::VectorShiftRight(vector_, static_cast<std::size_t>(num_shifts_));
			}
			else
			{
				return EmuMath::Helpers::VectorShiftRight(vector_, num_shifts_);
			}
		}
	};
#pragma endregion

#pragma region COMPARATORS
	template<std::size_t Size_, typename T_, typename Rhs_>
	struct do_cmp_equal_to<EmuMath::Vector<Size_, T_>, Rhs_>
	{
		constexpr do_cmp_equal_to()
		{
		}
		constexpr inline bool operator()(const EmuMath::Vector<Size_, T_> lhs_, Rhs_& rhs_) const
		{
			return EmuMath::Helpers::VectorCmpEqualTo(lhs_, rhs_);
		}
	};

	template<std::size_t Size_, typename T_, typename Rhs_>
	struct do_cmp_not_equal_to<EmuMath::Vector<Size_, T_>, Rhs_>
	{
		constexpr do_cmp_not_equal_to()
		{
		}
		constexpr inline bool operator()(const EmuMath::Vector<Size_, T_> lhs_, Rhs_& rhs_) const
		{
			return EmuMath::Helpers::VectorCmpNotEqualTo(lhs_, rhs_);
		}
	};

	template<std::size_t Size_, typename T_, typename Rhs_>
	struct do_cmp_greater<EmuMath::Vector<Size_, T_>, Rhs_>
	{
		constexpr do_cmp_greater()
		{
		}
		constexpr inline bool operator()(const EmuMath::Vector<Size_, T_> lhs_, Rhs_& rhs_) const
		{
			return EmuMath::Helpers::VectorCmpGreater(lhs_, rhs_);
		}
	};

	template<std::size_t Size_, typename T_, typename Rhs_>
	struct do_cmp_less<EmuMath::Vector<Size_, T_>, Rhs_>
	{
		constexpr do_cmp_less()
		{
		}
		constexpr inline bool operator()(const EmuMath::Vector<Size_, T_> lhs_, Rhs_& rhs_) const
		{
			return EmuMath::Helpers::VectorCmpLess(lhs_, rhs_);
		}
	};

	template<std::size_t Size_, typename T_, typename Rhs_>
	struct do_cmp_greater_equal<EmuMath::Vector<Size_, T_>, Rhs_>
	{
		constexpr do_cmp_greater_equal()
		{
		}
		constexpr inline bool operator()(const EmuMath::Vector<Size_, T_> lhs_, Rhs_& rhs_) const
		{
			return EmuMath::Helpers::VectorCmpGreaterEqual(lhs_, rhs_);
		}
	};

	template<std::size_t Size_, typename T_, typename Rhs_>
	struct do_cmp_less_equal<EmuMath::Vector<Size_, T_>, Rhs_>
	{
		constexpr do_cmp_less_equal()
		{
		}
		constexpr inline bool operator()(const EmuMath::Vector<Size_, T_> lhs_, Rhs_& rhs_) const
		{
			return EmuMath::Helpers::VectorCmpLessEqual(lhs_, rhs_);
		}
	};

	template<std::size_t Size_, typename T_>
	struct do_cos<EmuMath::Vector<Size_, T_>>
	{
		constexpr do_cos()
		{
		}
		constexpr inline auto operator()(const EmuMath::Vector<Size_, T_>& vector_) const
		{
			return EmuMath::Helpers::VectorMutate(vector_, EmuCore::do_cos<typename EmuMath::Vector<Size_, T_>::value_type>());
		}
	};

	template<std::size_t Size_, typename T_>
	struct do_acos<EmuMath::Vector<Size_, T_>>
	{
		constexpr do_acos()
		{
		}
		constexpr inline auto operator()(const EmuMath::Vector<Size_, T_>& vector_) const
		{
			return EmuMath::Helpers::VectorMutate(vector_, EmuCore::do_acos<typename EmuMath::Vector<Size_, T_>::value_type>());
		}
	};

	template<std::size_t Size_, typename T_>
	struct do_sin<EmuMath::Vector<Size_, T_>>
	{
		constexpr do_sin()
		{
		}
		constexpr inline auto operator()(const EmuMath::Vector<Size_, T_>& vector_) const
		{
			return EmuMath::Helpers::VectorMutate(vector_, EmuCore::do_sin<typename EmuMath::Vector<Size_, T_>::value_type>());
		}
	};

	template<std::size_t Size_, typename T_>
	struct do_asin<EmuMath::Vector<Size_, T_>>
	{
		constexpr do_asin()
		{
		}
		constexpr inline auto operator()(const EmuMath::Vector<Size_, T_>& vector_) const
		{
			return EmuMath::Helpers::VectorMutate(vector_, EmuCore::do_asin<typename EmuMath::Vector<Size_, T_>::value_type>());
		}
	};

	template<std::size_t Size_, typename T_>
	struct do_tan<EmuMath::Vector<Size_, T_>>
	{
		constexpr do_tan()
		{
		}
		constexpr inline auto operator()(const EmuMath::Vector<Size_, T_>& vector_) const
		{
			return EmuMath::Helpers::VectorMutate(vector_, EmuCore::do_tan<typename EmuMath::Vector<Size_, T_>::value_type>());
		}
	};

	template<std::size_t Size_, typename T_>
	struct do_atan<EmuMath::Vector<Size_, T_>>
	{
		constexpr do_atan()
		{
		}
		constexpr inline auto operator()(const EmuMath::Vector<Size_, T_>& vector_) const
		{
			return EmuMath::Helpers::VectorMutate(vector_, EmuCore::do_atan<typename EmuMath::Vector<Size_, T_>::value_type>());
		}
	};
#pragma endregion
}
#pragma endregion

#endif
