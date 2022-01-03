#ifndef EMU_MATH_NEW_VECTOR_SPECIAL_OPERATIONS_H_INC_
#define EMU_MATH_NEW_VECTOR_SPECIAL_OPERATIONS_H_INC_ 1

#include "_common_vector_helpers.h"

// CONTAINS:
// --- dot
// --- square_magnitude
// --- magnitude_constexpr

namespace EmuMath::Helpers
{
#pragma region DOT_FUNCS
	/// <summary>
	/// <para> Calculates the dot-product of the provided two EmuMath Vectors, outputting the result as the provided Out_ type. </para>
	/// <para> Out_ will default to the preferred_floating_point of vector_a_ if not provided. </para>
	/// </summary>
	/// <typeparam name="Out_">Type to output the dot-product as, defaulting to vector_a_'s preferred_floating_point.</typeparam>
	/// <param name="vector_a_">EmuMath Vector `a` for finding the dot product.</param>
	/// <param name="vector_b_">EmuMath Vector `b` for finding the dot product.</param>
	/// <returns>Dot product of the passed EmuMath Vectors.</returns>
	template<typename Out_, std::size_t SizeA_, typename TA_, std::size_t SizeB_, typename TB_>
	[[nodiscard]] constexpr inline Out_ new_vector_dot(const EmuMath::NewVector<SizeA_, TA_>& vector_a_, const EmuMath::NewVector<SizeB_, TB_>& vector_b_)
	{
		return _vector_underlying::_vector_dot<Out_>(vector_a_, vector_b_);
	}
	template<std::size_t SizeA_, typename TA_, std::size_t SizeB_, typename TB_>
	[[nodiscard]] constexpr inline typename EmuMath::NewVector<SizeA_, TA_>::preferred_floating_point new_vector_dot
	(
		const EmuMath::NewVector<SizeA_, TA_>& vector_a_,
		const EmuMath::NewVector<SizeB_, TB_>& vector_b_
	)
	{
		return _vector_underlying::_vector_dot<typename EmuMath::NewVector<SizeA_, TA_>::preferred_floating_point>(vector_a_, vector_b_);
	}

	/// <summary>
	/// <para> Calculates the dot-product of the provided two EmuMath Vectors, using indices within the specified range. </para>
	/// <para> Out_ will default to the preferred_floating_point of vector_a_ if not provided. </para>
	/// <para> BeginIndex_: Inclusive index at which to start reading from both Vectors to form a dot product. </para>
	/// <para> EndIndex_: Exclusive index at which to stop reading from both Vectors to form a dot product. </para>
	/// </summary>
	/// <typeparam name="Out_">Type to output the dot-product as, defaulting to vector_a_'s preferred_floating_point.</typeparam>
	/// <param name="vector_a_">EmuMath Vector `a` for finding the dot product.</param>
	/// <param name="vector_b_">EmuMath Vector `b` for finding the dot product.</param>
	/// <returns>Dot product of the passed EmuMath Vectors, using elements within the specified range.</returns>
	template<std::size_t BeginIndex_, std::size_t EndIndex_, typename Out_, std::size_t SizeA_, typename TA_, std::size_t SizeB_, typename TB_>
	[[nodiscard]] constexpr inline Out_ new_vector_dot(const EmuMath::NewVector<SizeA_, TA_>& vector_a_, const EmuMath::NewVector<SizeB_, TB_>& vector_b_)
	{
		return _vector_underlying::_vector_dot<BeginIndex_, EndIndex_, Out_>(vector_a_, vector_b_);
	}
	template<std::size_t BeginIndex_, std::size_t EndIndex_, std::size_t SizeA_, typename TA_, std::size_t SizeB_, typename TB_>
	[[nodiscard]] constexpr inline typename EmuMath::NewVector<SizeA_, TA_>::preferred_floating_point new_vector_dot
	(
		const EmuMath::NewVector<SizeA_, TA_>& vector_a_,
		const EmuMath::NewVector<SizeB_, TB_>& vector_b_
	)
	{
		return _vector_underlying::_vector_dot<BeginIndex_, EndIndex_, typename EmuMath::NewVector<SizeA_, TA_>::preferred_floating_point>(vector_a_, vector_b_);
	}
#pragma endregion

#pragma region SQUARE_MAGNITUDE_FUNCS
	/// <summary>
	/// <para> Calculates the squared magnitude of the passed EmuMath Vector. The magnitude of the Vector will be the square root of the returned value. </para>
	/// <para> This is equivalent to forming the dot product of the passed vector_ with itself. </para>
	/// <para> Out_ will default to the preferred_floating_point of the passed Vector if not provided. </para>
	/// </summary>
	/// <typeparam name="Out_">Type to output the square magnitude as, defaulting to the passed Vector's preferred_floating_point.</typeparam>
	/// <param name="vector_">EmuMath Vector to calculate the square magnitude of.</param>
	/// <returns>Squared magnitude of the passed EmuMath Vector.</returns>
	template<typename Out_, std::size_t Size_, typename T_>
	[[nodiscard]] constexpr inline Out_ new_vector_square_magnitude(const EmuMath::NewVector<Size_, T_>& vector_)
	{
		return _vector_underlying::_vector_square_mag<Out_>(vector_);
	}
	template<std::size_t Size_, typename T_>
	[[nodiscard]] constexpr inline typename EmuMath::NewVector<Size_, T_>::preferred_floating_point new_vector_square_magnitude(const EmuMath::NewVector<Size_, T_>& vector_)
	{
		return _vector_underlying::_vector_square_mag<typename EmuMath::NewVector<Size_, T_>::preferred_floating_point>(vector_);
	}

	/// <summary>
	/// <para> Calculates the squared magnitude of the passed EmuMath Vector, using indices within the provided range only. </para>
	/// <para> This is equivalent to forming the dot product of the passed vector_ with itself. </para>
	/// <para> Out_ will default to the preferred_floating_point of the passed Vector if not provided. </para>
	/// <para> BeginIndex_: Inclusive index at which to start reading from the passed Vector for calculations. </para>
	/// <para> EndIndex_: Exclusive index at which to stop reading from the passed Vector for calculations. </para>
	/// </summary>
	/// <typeparam name="Out_">Type to output the square magnitude as, defaulting to the passed Vector's preferred_floating_point.</typeparam>
	/// <param name="vector_">EmuMath Vector to calculate the square magnitude of.</param>
	/// <returns>Squared magnitude of the passed EmuMath Vector, using the provided index range.</returns>
	template<std::size_t BeginIndex_, std::size_t EndIndex_, typename Out_, std::size_t Size_, typename T_>
	[[nodiscard]] constexpr inline Out_ new_vector_square_magnitude(const EmuMath::NewVector<Size_, T_>& vector_)
	{
		return _vector_underlying::_vector_square_mag<BeginIndex_, EndIndex_, Out_>(vector_);
	}
	template<std::size_t BeginIndex_, std::size_t EndIndex_, std::size_t Size_, typename T_>
	[[nodiscard]] constexpr inline typename EmuMath::NewVector<Size_, T_>::preferred_floating_point new_vector_square_magnitude(const EmuMath::NewVector<Size_, T_>& vector_)
	{
		return _vector_underlying::_vector_square_mag<BeginIndex_, EndIndex_, typename EmuMath::NewVector<Size_, T_>::preferred_floating_point>(vector_);
	}
#pragma endregion

#pragma region MAGNITUDE_CONSTEXPR_FUNCS
	/// <summary>
	/// <para> Calculates the magnitude of the passed EmuMath Vector. </para>
	/// <para>
	///		Provides a guarantee to be constexpr-evaluable if possible. Note that this may make sacrifices to accuracy and/or performance, 
	///		and as a result one may prefer to use the non-constexpr variant of this function if it is guaranteed to be executed at runtime.
	/// </para>
	/// </summary>
	/// <typeparam name="Out_">Type to output the magnitude as, defaulting to the passed Vector's preferred_floating_point.</typeparam>
	/// <param name="vector_">EmuMath Vector to calculate the magnitude of.</param>
	/// <returns>Magnitude of the passed EmuMath Vector.</returns>
	template<typename Out_, std::size_t Size_, typename T_>
	[[nodiscard]] constexpr inline Out_ new_vector_magnitude_constexpr(const EmuMath::NewVector<Size_, T_>& vector_)
	{
		return _vector_underlying::_vector_mag<EmuCore::do_sqrt_constexpr, Out_>(vector_);
	}
	template<std::size_t Size_, typename T_>
	[[nodiscard]] constexpr inline typename EmuMath::NewVector<Size_, T_>::preferred_floating_point new_vector_magnitude_constexpr(const EmuMath::NewVector<Size_, T_>& vector_)
	{
		return _vector_underlying::_vector_mag<EmuCore::do_sqrt_constexpr, typename EmuMath::NewVector<Size_, T_>::preferred_floating_point>(vector_);
	}

	/// <summary>
	/// <para> Calculates the magnitude of the passed EmuMath Vector, using indices within the provided range only. </para>
	/// <para>
	///		Provides a guarantee to be constexpr-evaluable if possible. Note that this may make sacrifices to accuracy and/or performance, 
	///		and as a result one may prefer to use the non-constexpr variant of this function if it is guaranteed to be executed at runtime.
	/// </para>
	/// <para> BeginIndex_: Inclusive index at which to start reading from the passed Vector for calculations. </para>
	/// <para> EndIndex_: Exclusive index at which to stop reading from the passed Vector for calculations. </para>
	/// </summary>
	/// <typeparam name="Out_">Type to output the magnitude as, defaulting to the passed Vector's preferred_floating_point.</typeparam>
	/// <param name="vector_">EmuMath Vector to calculate the magnitude of.</param>
	/// <returns>Magnitude of the passed EmuMath Vector, using the provided index range.</returns>
	template<std::size_t BeginIndex_, std::size_t EndIndex_, typename Out_, std::size_t Size_, typename T_>
	[[nodiscard]] constexpr inline Out_ new_vector_magnitude_constexpr(const EmuMath::NewVector<Size_, T_>& vector_)
	{
		return _vector_underlying::_vector_mag<EmuCore::do_sqrt_constexpr, BeginIndex_, EndIndex_, Out_>(vector_);
	}
	template<std::size_t BeginIndex_, std::size_t EndIndex_, std::size_t Size_, typename T_>
	[[nodiscard]] constexpr inline typename EmuMath::NewVector<Size_, T_>::preferred_floating_point new_vector_magnitude_constexpr(const EmuMath::NewVector<Size_, T_>& vector_)
	{
		return _vector_underlying::_vector_mag<EmuCore::do_sqrt_constexpr, BeginIndex_, EndIndex_, typename EmuMath::NewVector<Size_, T_>::preferred_floating_point>(vector_);
	}
#pragma endregion

#pragma region MAGNITUDE_FUNCS
	/// <summary>
	/// <para> Calculates the magnitude of the passed EmuMath Vector. </para>
	/// <para> For a guarantee to produce a compile-time result if possible, use `vector_magnitude_constexpr` instead. </para>
	/// </summary>
	/// <typeparam name="Out_">Type to output the magnitude as, defaulting to the passed Vector's preferred_floating_point.</typeparam>
	/// <param name="vector_">EmuMath Vector to calculate the magnitude of.</param>
	/// <returns>Magnitude of the passed EmuMath Vector.</returns>
	template<typename Out_, std::size_t Size_, typename T_>
	[[nodiscard]] constexpr inline Out_ new_vector_magnitude(const EmuMath::NewVector<Size_, T_>& vector_)
	{
		return _vector_underlying::_vector_mag<EmuCore::do_sqrt, Out_>(vector_);
	}
	template<std::size_t Size_, typename T_>
	[[nodiscard]] constexpr inline typename EmuMath::NewVector<Size_, T_>::preferred_floating_point new_vector_magnitude(const EmuMath::NewVector<Size_, T_>& vector_)
	{
		return _vector_underlying::_vector_mag<EmuCore::do_sqrt, typename EmuMath::NewVector<Size_, T_>::preferred_floating_point>(vector_);
	}

	/// <summary>
	/// <para> Calculates the magnitude of the passed EmuMath Vector, using indices within the provided range only. </para>
	/// <para> For a guarantee to produce a compile-time result if possible, use `vector_magnitude_constexpr` instead. </para>
	/// <para> BeginIndex_: Inclusive index at which to start reading from the passed Vector for calculations. </para>
	/// <para> EndIndex_: Exclusive index at which to stop reading from the passed Vector for calculations. </para>
	/// </summary>
	/// <typeparam name="Out_">Type to output the magnitude as, defaulting to the passed Vector's preferred_floating_point.</typeparam>
	/// <param name="vector_">EmuMath Vector to calculate the magnitude of.</param>
	/// <returns>Magnitude of the passed EmuMath Vector, using the provided index range.</returns>
	template<std::size_t BeginIndex_, std::size_t EndIndex_, typename Out_, std::size_t Size_, typename T_>
	[[nodiscard]] constexpr inline Out_ new_vector_magnitude(const EmuMath::NewVector<Size_, T_>& vector_)
	{
		return _vector_underlying::_vector_mag<EmuCore::do_sqrt, BeginIndex_, EndIndex_, Out_>(vector_);
	}
	template<std::size_t BeginIndex_, std::size_t EndIndex_, std::size_t Size_, typename T_>
	[[nodiscard]] constexpr inline typename EmuMath::NewVector<Size_, T_>::preferred_floating_point new_vector_magnitude(const EmuMath::NewVector<Size_, T_>& vector_)
	{
		return _vector_underlying::_vector_mag<EmuCore::do_sqrt, BeginIndex_, EndIndex_, typename EmuMath::NewVector<Size_, T_>::preferred_floating_point>(vector_);
	}
#pragma endregion
}

#endif
