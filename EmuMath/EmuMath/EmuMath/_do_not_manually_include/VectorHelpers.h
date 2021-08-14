#ifndef EMU_MATH_VECTOR_T_HELPERS_H_INC_
#define EMU_MATH_VECTOR_T_HELPERS_H_INC_

#include "VectorHelpersUnderlying.h"

namespace EmuMath::Helpers
{
#pragma region SETS
	template<class LhsVector_, class RhsVector_>
	constexpr inline LhsVector_& VectorSet(LhsVector_& lhs_, const RhsVector_& rhs_)
	{
		if constexpr (_underlying_vector_funcs::_validity_check_vector_assignment<LhsVector_, RhsVector_>())
		{
			_underlying_vector_funcs::_assign_vector_via_vector<0, LhsVector_, RhsVector_>(lhs_, rhs_);
		}
		return lhs_;
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
		return EmuMath::Vector<sizeof...(RemainingShuffleIndices_) + 1, out_value_type>
		(
			_underlying_vector_funcs::_get_vector_data<X_>(vector_),
			_underlying_vector_funcs::_get_vector_data<RemainingShuffleIndices_>(vector_)...
		);
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
		return VectorShuffle<typename Vector_::value_type, X_, RemainingShuffleIndices_...>(vector_);
	}
#pragma endregion
}

#endif
