#ifndef EMU_MATH_VECTOR_T_HELPERS_H_INC_
#define EMU_MATH_VECTOR_T_HELPERS_H_INC_

#include "../GeneralMath.h"
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
		return static_cast<OutT_>(EmuMath::SqrtConstexpr<FloatingPoint_, FloatingPoint_>(VectorSquareMagnitude<FloatingPoint_, Vector_>(vector_)));
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
		return EmuMath::DoCorrectStandardSqrt<FloatingPoint_>(VectorSquareMagnitude<FloatingPoint_, Vector_>(vector_));
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

#pragma region COMPARISONS
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
}

#pragma region EMU_MATH_SPECIALISATIONS
namespace EmuMath
{
	/// <summary> do_lerp specialisation which defers the calculation to EmuMath::Helpers::VectorLerp. </summary>
	/// <typeparam name="a_value_type">Type contained within the vector used for argument A_.<typeparam>
	template<std::size_t ASize_, typename a_value_type, class B_, class T_>
	struct do_lerp<EmuMath::Vector<ASize_, a_value_type>, B_, T_>
	{
		constexpr do_lerp()
		{
		}
		template<std::size_t OutSize_ = ASize_, typename out_value_type = a_value_type>
		[[nodiscard]] constexpr inline EmuMath::Vector<OutSize_, out_value_type> operator()(const EmuMath::Vector<ASize_, a_value_type>& a_, const B_& b_, const T_& t_) const
		{
			return EmuMath::Helpers::VectorLerp<OutSize_, out_value_type, EmuMath::Vector<ASize_, a_value_type>, B_, T_>(a_, b_, t_);
		}
	};
}
#pragma endregion

#endif
